
static Size S2CellUnion_get_flat_size(ExpandedObjectHeader *eohptr) {
  pgs2_S2CellUnion *A = (pgs2_S2CellUnion *)eohptr;
  Size nbytes;
  uint64_t nvals;

  Assert(A->em_magic == S2CellUnion_MAGIC);

  if (A->flat_size)
    return A->flat_size;

  nvals = A->nvals;
  nbytes = PGS2_S2CELLUNION_OVERHEAD();
  nbytes += nvals * sizeof(uint64_t);
  A->flat_size = nbytes;
  return nbytes;
}

static void S2CellUnion_flatten_into(ExpandedObjectHeader *eohptr, void *result,
                                     Size allocated_size) {

  pgs2_S2CellUnion *A = (pgs2_S2CellUnion *)eohptr;
  pgs2_FlatS2CellUnion *flat = (pgs2_FlatS2CellUnion *)result;

  Assert(A->em_magic == S2CellUnion_MAGIC);
  Assert(allocated_size == A->flat_size);

  memset(flat, 0, allocated_size);

  flat->nvals = A->nvals;

  if (A->nvals > 0)
    s2c_S2CellUnion_cell_ids(A->cell_union, PGS2_S2CELLUNION_DATA(flat),
                             error_callback);

  SET_VARSIZE(flat, allocated_size);
}

Datum expand_flat_S2CellUnion(pgs2_FlatS2CellUnion *flat,
                              MemoryContext parentcontext) {
  pgs2_S2CellUnion *A;

  MemoryContext objcxt, oldcxt;
  MemoryContextCallback *ctxcb;
  uint64_t *cell_ids;

  uint64_t nvals;
  objcxt = AllocSetContextCreate(parentcontext, "expanded S2CellUnion",
                                 ALLOCSET_DEFAULT_SIZES);

  A = (pgs2_S2CellUnion *)MemoryContextAlloc(objcxt, sizeof(pgs2_S2CellUnion));

  EOH_init_header(&A->hdr, &S2CellUnion_methods, objcxt);

  A->em_magic = S2CellUnion_MAGIC;

  oldcxt = MemoryContextSwitchTo(objcxt);

  A->nvals = nvals = flat->nvals;

  cell_ids = PGS2_S2CELLUNION_DATA(flat);

  A->cell_union = s2c_S2CellUnion_new(cell_ids, nvals, error_callback);

  A->flat_size = 0;

  ctxcb = MemoryContextAlloc(objcxt, sizeof(MemoryContextCallback));

  ctxcb->func = context_callback_S2CellUnion_free;
  ctxcb->arg = A;
  MemoryContextRegisterResetCallback(objcxt, ctxcb);

  MemoryContextSwitchTo(oldcxt);
  PGS2_RETURN_S2CELLUNION(A);
}

static void context_callback_S2CellUnion_free(void *ptr) {
  pgs2_S2CellUnion *A = (pgs2_S2CellUnion *)ptr;
  s2c_S2CellUnion_free(A->cell_union, error_callback);
}

pgs2_S2CellUnion *
construct_empty_expanded_S2CellUnion(uint64_t nvals,
                                     MemoryContext parentcontext) {
  pgs2_FlatS2CellUnion *flat;
  Datum d;
  flat = construct_empty_flat_S2CellUnion();
  d = expand_flat_S2CellUnion(flat, parentcontext);
  pfree(flat);
  return (pgs2_S2CellUnion *)DatumGetEOHP(d);
}

pgs2_FlatS2CellUnion *construct_empty_flat_S2CellUnion() {
  pgs2_FlatS2CellUnion *result;
  result = (pgs2_FlatS2CellUnion *)palloc0(sizeof(pgs2_FlatS2CellUnion));
  SET_VARSIZE(result, sizeof(pgs2_FlatS2CellUnion));
  result->nvals = 0;
  return result;
}

pgs2_S2CellUnion *DatumGetS2CellUnion(Datum d) {
  pgs2_S2CellUnion *A;
  pgs2_FlatS2CellUnion *flat;

  if (VARATT_IS_EXTERNAL_EXPANDED(DatumGetPointer(d))) {
    A = S2CellUnionGetEOHP(d);
    Assert(A->em_magic == S2CellUnion_MAGIC);
    return A;
  }

  flat = (pgs2_FlatS2CellUnion *)PG_DETOAST_DATUM(d);
  expand_flat_S2CellUnion(flat, CurrentMemoryContext);
  return S2CellUnionGetEOHP(d);
}

Datum S2CellUnion_Normalize(PG_FUNCTION_ARGS) {}
