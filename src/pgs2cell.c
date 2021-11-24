Datum S2Cell_in(PG_FUNCTION_ARGS) {
  char *token;
  pgs2_S2Cell *cell;
  token = PG_GETARG_CSTRING(0);
  cell = palloc0(sizeof(pgs2_S2Cell));
  s2c_token_to_cell(token, cell, error_callback);
  PGS2_RETURN_S2CELL_P(cell);
}

Datum S2Cell_out(PG_FUNCTION_ARGS) {
  char *token, *result;
  StringInfoData str;
  pgs2_S2Cell *cell = PGS2_GETARG_S2CELL_P(0);
  initStringInfo(&str);
  s2c_cell_to_token(cell, &token, error_callback);
  result = pstrdup(token);
  free(token);
  PG_RETURN_CSTRING(result);
}

int32 S2Cell_cmp_internal(pgs2_S2Cell *A, pgs2_S2Cell *B) {
  if (A->id < B->id)
    return -1;
  if (A->id > B->id)
    return 1;
  return 0;
}

Datum S2Cell_eq(PG_FUNCTION_ARGS) {
  pgs2_S2Cell *A, *B;
  A = PGS2_GETARG_S2CELL_P(0);
  B = PGS2_GETARG_S2CELL_P(1);
  PG_RETURN_BOOL(S2Cell_cmp_internal(A, B) == 0);
}

Datum S2Cell_lt(PG_FUNCTION_ARGS) {
  pgs2_S2Cell *A, *B;
  A = PGS2_GETARG_S2CELL_P(0);
  B = PGS2_GETARG_S2CELL_P(1);
  PG_RETURN_BOOL(S2Cell_cmp_internal(A, B) < 0);
}

Datum S2Cell_gt(PG_FUNCTION_ARGS) {
  pgs2_S2Cell *A, *B;
  A = PGS2_GETARG_S2CELL_P(0);
  B = PGS2_GETARG_S2CELL_P(1);
  PG_RETURN_BOOL(S2Cell_cmp_internal(A, B) > 0);
}

Datum S2Cell_le(PG_FUNCTION_ARGS) {
  pgs2_S2Cell *A, *B;
  A = PGS2_GETARG_S2CELL_P(0);
  B = PGS2_GETARG_S2CELL_P(1);
  PG_RETURN_BOOL(S2Cell_cmp_internal(A, B) <= 0);
}

Datum S2Cell_ge(PG_FUNCTION_ARGS) {
  pgs2_S2Cell *A, *B;
  A = PGS2_GETARG_S2CELL_P(0);
  B = PGS2_GETARG_S2CELL_P(1);
  PG_RETURN_BOOL(S2Cell_cmp_internal(A, B) >= 0);
}

Datum S2Cell_cmp(PG_FUNCTION_ARGS) {
  pgs2_S2Cell *A, *B;
  A = PGS2_GETARG_S2CELL_P(0);
  B = PGS2_GETARG_S2CELL_P(1);
  PG_RETURN_INT32(S2Cell_cmp_internal(A, B));
}

Datum S2Cell_distance(PG_FUNCTION_ARGS) {
  pgs2_S2Cell *A, *B;
  double distance;
  A = PGS2_GETARG_S2CELL_P(0);
  B = PGS2_GETARG_S2CELL_P(1);
  s2c_cell_to_cell_distance(A, B, &distance, error_callback);
  PG_RETURN_FLOAT8(distance);
}

static int btS2Cellfastcmp(Datum x, Datum y, SortSupport ssup) {
  pgs2_S2Cell *A, *B;
  uint64_t a, b;
  A = DatumGetS2CellP(x);
  B = DatumGetS2CellP(y);
  a = A->id;
  b = B->id;
  if (a > b)
    return 1;
  else if (a == b)
    return 0;
  else
    return -1;
}

Datum btS2Cellsortsupport(PG_FUNCTION_ARGS) {
  SortSupport ssup = (SortSupport)PG_GETARG_POINTER(0);
  ssup->comparator = btS2Cellfastcmp;
  PG_RETURN_VOID();
}
