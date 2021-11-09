#define LDELIM			'('
#define RDELIM			')'
#define DELIM			','
#define LDELIM_EP		'['
#define RDELIM_EP		']'
#define LDELIM_C		'<'
#define RDELIM_C		'>'
#define LDELIM_L		'{'
#define RDELIM_L		'}'

static void
context_callback_s2point_free(void* ptr) {
    pgs2_S2point *A = (pgs2_S2point *) ptr;
    s2c_S2Point_free(A->point);
}

/* Compute flattened size of storage needed for a s2point */
static Size
s2point_get_flat_size(ExpandedObjectHeader *eohptr) {
    pgs2_S2point *A = (pgs2_S2point*) eohptr;
    Size nbytes;

    /* This is a sanity check that the object is initialized */
    Assert(A->em_magic == s2point_MAGIC);

    /* Use cached value if already computed */
    if (A->flat_size) {
        return A->flat_size;
    }
    nbytes = PGS2_S2POINT_OVERHEAD() + (sizeof(double) * 3);
    /* Cache this value in the s2 object */
    A->flat_size = nbytes;
    return nbytes;
}

/* Flatten s2point into a pre-allocated result buffer that is
   allocated_size in bytes.  */
static void
s2point_flatten_into(ExpandedObjectHeader *eohptr,
                    void *result, Size allocated_size)  {

    /* Cast EOH pointer to s2 object, and result pointer to flat
       object */
    pgs2_S2point *A = (pgs2_S2point *) eohptr;
    pgs2_FlatS2point *flat = (pgs2_FlatS2point *) result;

    /* Sanity check the object is valid */
    Assert(A->em_magic == s2point_MAGIC);
    Assert(allocated_size == A->flat_size);

    /* Zero out the whole allocated buffer */
    memset(flat, 0, allocated_size);
    s2c_S2Point_xyz(A->point, &(flat->x), &(flat->y), &(flat->z));
}

/* Expand a flat s2point in to an S2 one, return as Postgres Datum. */
Datum
expand_flat_s2point(pgs2_FlatS2point *flat,
                    MemoryContext parentcontext) {
  pgs2_S2point *A;

  MemoryContext objcxt, oldcxt;
  MemoryContextCallback *ctxcb;

  /* Create a new context that will hold the s2 object. */
  objcxt = AllocSetContextCreate(parentcontext,
                                 "s2 s2point",
                                 ALLOCSET_DEFAULT_SIZES);

  /* Allocate a new s2 s2point */
  A = (pgs2_S2point*)MemoryContextAlloc(objcxt,
                                        sizeof(pgs2_S2point));

  /* Initialize the S2ObjectHeader member with flattening
   * methods and the new object context */
  EOH_init_header(&A->hdr, &s2point_methods, objcxt);

  /* Used for debugging checks */
  A->em_magic = s2point_MAGIC;

  /* Switch to new object context */
  oldcxt = MemoryContextSwitchTo(objcxt);

  A->flat_size = 0;

  /* Create a context callback to free s2point when context is cleared */
  ctxcb = MemoryContextAlloc(objcxt, sizeof(MemoryContextCallback));

  ctxcb->func = context_callback_s2point_free;
  ctxcb->arg = A;
  MemoryContextRegisterResetCallback(objcxt, ctxcb);

  A->point = s2c_S2Point_new(flat->x, flat->y, flat->z);

  /* Switch back to old context */
  MemoryContextSwitchTo(oldcxt);
  PGS2_RETURN_S2POINT(A);
}

/* This is used by PG_GETARG_S2POINT */
pgs2_S2point *
DatumGetS2point(Datum d) {
  pgs2_S2point *A;
  pgs2_FlatS2point *flat;

  if (VARATT_IS_EXTERNAL_EXPANDED(DatumGetPointer(d))) {
    A = S2pointGetEOHP(d);
    Assert(A->em_magic == s2point_MAGIC);
    return A;
  }
  flat = (pgs2_FlatS2point*)PG_DETOAST_DATUM(d);
  expand_flat_s2point(flat, CurrentMemoryContext);
  return S2pointGetEOHP(d);
}

Datum
s2point_in(PG_FUNCTION_ARGS) {
  bool has_delim;
  pgs2_FlatS2point *flat;
  char *input, *orig_string;

  input = orig_string = PG_GETARG_CSTRING(0);
  flat = palloc0(sizeof(pgs2_FlatS2point));

  while (isspace((unsigned char) *input))
      input++;

  if ((has_delim = (*input == LDELIM)))
      input++;

  flat->x = float8in_internal(input, &input, "s2point", orig_string);

  if (*input++ != DELIM)
      ereport(ERROR,
              (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
               errmsg("invalid delimiter after x in %s: \"%s\"",
                      "s2point", orig_string)));

  flat->y = float8in_internal(input, &input, "s2point", orig_string);

  if (*input++ != DELIM)
      ereport(ERROR,
              (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
               errmsg("invalid delimiter after y in %s: \"%s\"",
                      "s2point", orig_string)));

  flat->z = float8in_internal(input, &input, "s2point", orig_string);

  if (has_delim)
      {
          if (*input++ != RDELIM)
              ereport(ERROR,
                      (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
                       errmsg("invalid ending delimter for %s: \"%s\"",
                              "s2point", orig_string)));
          while (isspace((unsigned char) *input))
              input++;
      }

  if (*input != '\0')
      ereport(ERROR,
              (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
               errmsg("no null byte at end of %s: \"%s\"",
                      "s2point", orig_string)));

  return expand_flat_s2point(flat, CurrentMemoryContext);
}

Datum
s2point_out(PG_FUNCTION_ARGS)
{
  double x, y, z;
  char *xstr, *ystr, *zstr;
  StringInfoData str;

  pgs2_S2point *A = PGS2_GETARG_S2POINT(0);
  s2c_S2Point_xyz(A->point, &x, &y, &z);
  initStringInfo(&str);

  xstr = float8out_internal(x);
  ystr = float8out_internal(y);
  zstr = float8out_internal(z);

  appendStringInfo(&str, "%s,%s,%s", xstr, ystr, zstr);
  pfree(xstr);
  pfree(ystr);
  pfree(zstr);
  PG_RETURN_CSTRING(str.data);
}
