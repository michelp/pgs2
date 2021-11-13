Datum
S2Cap(PG_FUNCTION_ARGS) {
    pgs2_S2Cap *p;
    p = palloc0(sizeof(pgs2_S2Cap));
    p->x = PG_GETARG_FLOAT8(0);
    p->y = PG_GETARG_FLOAT8(1);
    p->z = PG_GETARG_FLOAT8(2);
    p->r = PG_GETARG_FLOAT8(3);
    PGS2_RETURN_S2CAP_P(p);
}

Datum
S2Cap_in(PG_FUNCTION_ARGS) {
  bool has_delim;
  pgs2_S2Cap *p;
  char *input, *orig_string;

  input = orig_string = PG_GETARG_CSTRING(0);
  p = palloc0(sizeof(pgs2_S2Cap));

  while (isspace((unsigned char) *input))
      input++;

  if ((has_delim = (*input == LPAREN)))
      input++;

  p->x = float8in_internal(input, &input, "S2Cap", orig_string);

  if (*input++ != DELIM)
      ereport(ERROR,
              (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
               errmsg("invalid delimiter after x in %s: \"%s\"",
                      "S2Cap", orig_string)));

  p->y = float8in_internal(input, &input, "S2Cap", orig_string);

  if (*input++ != DELIM)
      ereport(ERROR,
              (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
               errmsg("invalid delimiter after y in %s: \"%s\"",
                      "S2Cap", orig_string)));

  p->z = float8in_internal(input, &input, "S2Cap", orig_string);

  if (*input++ != COLON)
      ereport(ERROR,
              (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
               errmsg("invalid delimiter after z in %s: \"%s\"",
                      "S2Cap", orig_string)));

  p->r = float8in_internal(input, &input, "S2Cap", orig_string);
  
  if (has_delim)
      {
          if (*input++ != RPAREN)
              ereport(ERROR,
                      (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
                       errmsg("invalid ending delimter for %s: \"%s\"",
                              "S2Cap", orig_string)));
          while (isspace((unsigned char) *input))
              input++;
      }

  if (*input != '\0')
      ereport(ERROR,
              (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
               errmsg("no null byte at end of %s: \"%s\"",
                      "S2Cap", orig_string)));

  PGS2_RETURN_S2CAP_P(p);
}

Datum
S2Cap_out(PG_FUNCTION_ARGS)
{
    char *xstr, *ystr, *zstr, *rstr;
    StringInfoData str;
    pgs2_S2Cap *p = PGS2_GETARG_S2CAP_P(0);
    initStringInfo(&str);
    
    xstr = float8out_internal(p->x);
    ystr = float8out_internal(p->y);
    zstr = float8out_internal(p->z);
    rstr = float8out_internal(p->r);
    
    appendStringInfo(&str, "(%s,%s,%s:%s)", xstr, ystr, zstr, rstr);
    pfree(xstr);
    pfree(ystr);
    pfree(zstr);
    pfree(rstr);
    PG_RETURN_CSTRING(str.data);
}

Datum
S2Cap_eq(PG_FUNCTION_ARGS) {
    pgs2_S2Cap *A, *B;
    A = PGS2_GETARG_S2CAP_P(0);
    B = PGS2_GETARG_S2CAP_P(1);
    PG_RETURN_BOOL(A->x == B->x && A->y == B->y &&
                   A->z == B->z && A->r == B->r);
}
