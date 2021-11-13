Datum
S2Cap(PG_FUNCTION_ARGS) {
    pgs2_S2Cap *cap = palloc0(sizeof(cap));

    cap->center = *PGS2_GETARG_S2POINT_P(0);
    cap->radius = PG_GETARG_FLOAT8(2);
    PGS2_RETURN_S2CAP_P(cap);
}

Datum
S2Cap_in(PG_FUNCTION_ARGS) {
  bool has_delim;
  pgs2_S2Cap *cap;
  char *input, *orig_string;

  input = orig_string = PG_GETARG_CSTRING(0);
  cap = palloc0(sizeof(cap));

  while (isspace((unsigned char) *input))
      input++;

  if ((has_delim = (*input == LPAREN)))
      input++;

  cap->center.x = float8in_internal(input, &input, "S2Cap", orig_string);

  if (*input++ != DELIM)
      ereport(ERROR,
              (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
               errmsg("invalid delimiter after x in %s: \"%s\"",
                      "S2Cap", orig_string)));

  cap->center.y = float8in_internal(input, &input, "S2Cap", orig_string);

  if (*input++ != DELIM)
      ereport(ERROR,
              (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
               errmsg("invalid delimiter after y in %s: \"%s\"",
                      "S2Cap", orig_string)));

  cap->center.z = float8in_internal(input, &input, "S2Cap", orig_string);

  if (*input++ != COLON)
      ereport(ERROR,
              (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
               errmsg("invalid delimiter after z in %s: \"%s\"",
                      "S2Cap", orig_string)));

  cap->radius = float8in_internal(input, &input, "S2Cap", orig_string);

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

  PGS2_RETURN_S2CAP_P(cap);
}

Datum
S2Cap_out(PG_FUNCTION_ARGS)
{
    char *xstr, *ystr, *zstr, *rstr;
    StringInfoData str;
    pgs2_S2Cap *cap = PGS2_GETARG_S2CAP_P(0);
    initStringInfo(&str);

    xstr = float8out_internal(cap->center.x);
    ystr = float8out_internal(cap->center.y);
    zstr = float8out_internal(cap->center.z);
    rstr = float8out_internal(cap->radius);

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
    PG_RETURN_BOOL(A->center.x == B->center.x &&
                   A->center.y == B->center.y &&
                   A->center.z == B->center.z &&
                   A->radius == B->radius);
}
