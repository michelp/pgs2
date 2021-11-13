Datum
S2LatLng(PG_FUNCTION_ARGS) {
    pgs2_S2LatLng *l;
    l = palloc0(sizeof(pgs2_S2LatLng));
    l->x = PG_GETARG_FLOAT8(0);
    l->y = PG_GETARG_FLOAT8(1);
    PGS2_RETURN_S2LATLNG_P(l);
}

Datum
S2LatLng_in(PG_FUNCTION_ARGS) {
  bool has_delim;
  pgs2_S2LatLng *l;
  char *input, *orig_string;

  input = orig_string = PG_GETARG_CSTRING(0);

  l = palloc0(sizeof(pgs2_S2LatLng));

  while (isspace((unsigned char) *input))
      input++;

  if ((has_delim = (*input == LDELIM)))
      input++;

  l->x = float8in_internal(input, &input, "S2LatLng", orig_string);

  if (*input++ != DELIM)
      ereport(ERROR,
              (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
               errmsg("invalid delimiter after x in %s: \"%s\"",
                      "S2LatLng", orig_string)));

  l->y = float8in_internal(input, &input, "S2LatLng", orig_string);

  if (has_delim)
      {
          if (*input++ != RDELIM)
              ereport(ERROR,
                      (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
                       errmsg("invalid ending delimter for %s: \"%s\"",
                              "S2LatLng", orig_string)));
          while (isspace((unsigned char) *input))
              input++;
      }

  if (*input != '\0')
      ereport(ERROR,
              (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
               errmsg("no null byte at end of %s: \"%s\"",
                      "S2LatLng", orig_string)));

  PGS2_RETURN_S2LATLNG_P(l);
}

Datum
S2LatLng_out(PG_FUNCTION_ARGS)
{
  char *xstr, *ystr;
  StringInfoData str;

  pgs2_S2LatLng *l = PGS2_GETARG_S2LATLNG_P(0);
  initStringInfo(&str);

  xstr = float8out_internal(l->x);
  ystr = float8out_internal(l->y);

  appendStringInfo(&str, "(%s,%s)", xstr, ystr);
  pfree(xstr);
  pfree(ystr);
  PG_RETURN_CSTRING(str.data);
}

Datum
S2LatLng_eq(PG_FUNCTION_ARGS) {
  pgs2_S2LatLng *A, *B;

  A = PGS2_GETARG_S2LATLNG_P(0);
  B = PGS2_GETARG_S2LATLNG_P(1);

  PG_RETURN_BOOL(A->x == B->x && A->y == B->y);
}
