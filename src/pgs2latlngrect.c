Datum
S2LatLngRect(PG_FUNCTION_ARGS) {
    pgs2_S2LatLngRect *l;
    pgs2_S2LatLng *lo, *hi;
    l = palloc0(sizeof(pgs2_S2LatLngRect));
    lo = PGS2_GETARG_S2LATLNG_P(0);
    hi = PGS2_GETARG_S2LATLNG_P(1);
    l->lo.lat = lo->lat;
    l->lo.lng = lo->lng;
    l->hi.lat = hi->lat;
    l->hi.lng = hi->lng;
    PGS2_RETURN_S2LATLNGRECT_P(l);
}

Datum
S2LatLngRect_in(PG_FUNCTION_ARGS) {
  bool has_delim;
  pgs2_S2LatLngRect *l;
  char *input, *orig_string;

  input = orig_string = PG_GETARG_CSTRING(0);
  l = palloc0(sizeof(pgs2_S2LatLngRect));

  while (isspace((unsigned char) *input))
      input++;

  if ((has_delim = (*input == LPAREN)))
      input++;

  l->lo.lat = float8in_internal(input, &input, "S2LatLngRect", orig_string);

  if (*input++ != DELIM)
      ereport(ERROR,
              (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
               errmsg("invalid delimiter after lo x in %s: \"%s\"",
                      "S2LatLngRect", orig_string)));

  l->lo.lng = float8in_internal(input, &input, "S2LatLngRect", orig_string);

  if (*input++ != COLON)
      ereport(ERROR,
              (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
               errmsg("invalid delimiter after lo y in %s: \"%s\"",
                      "S2LatLngRect", orig_string)));

  l->hi.lat = float8in_internal(input, &input, "S2LatLngRect", orig_string);

  if (*input++ != DELIM)
      ereport(ERROR,
              (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
               errmsg("invalid delimiter after hi x in %s: \"%s\"",
                      "S2LatLngRect", orig_string)));

  l->hi.lng = float8in_internal(input, &input, "S2LatLngRect", orig_string);

  if (has_delim)
      {
          if (*input++ != RPAREN)
              ereport(ERROR,
                      (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
                       errmsg("invalid ending delimter for %s: \"%s\"",
                              "S2LatLngRect", orig_string)));
          while (isspace((unsigned char) *input))
              input++;
      }

  if (*input != '\0')
      ereport(ERROR,
              (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
               errmsg("no null byte at end of %s: \"%s\"",
                      "S2LatLngRect", orig_string)));

  PGS2_RETURN_S2LATLNGRECT_P(l);
}

Datum
S2LatLngRect_out(PG_FUNCTION_ARGS)
{
    char *lo_xstr, *lo_ystr, *hi_xstr, *hi_ystr;
    StringInfoData str;

    pgs2_S2LatLngRect *l = PGS2_GETARG_S2LATLNGRECT_P(0);
    initStringInfo(&str);

    lo_xstr = float8out_internal(l->lo.lat);
    lo_ystr = float8out_internal(l->lo.lng);
    hi_xstr = float8out_internal(l->hi.lat);
    hi_ystr = float8out_internal(l->hi.lng);

    appendStringInfo(&str, "(%s,%s:%s,%s)", lo_xstr, lo_ystr, hi_xstr, hi_ystr);
    pfree(lo_xstr);
    pfree(lo_ystr);
    pfree(hi_xstr);
    pfree(hi_ystr);
    PG_RETURN_CSTRING(str.data);
}

Datum
S2LatLngRect_eq(PG_FUNCTION_ARGS) {
  pgs2_S2LatLngRect *A, *B;

  A = PGS2_GETARG_S2LATLNGRECT_P(0);
  B = PGS2_GETARG_S2LATLNGRECT_P(1);

  PG_RETURN_BOOL(A->lo.lat == B->lo.lat && A->lo.lng == B->lo.lng &&
                 A->hi.lat == B->hi.lat && A->hi.lng == B->hi.lng);
}
