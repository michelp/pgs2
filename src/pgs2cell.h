#ifndef PGS2CELL_H
#define PGS2CELL_H

#define DatumGetS2CellP(X) ((pgs2_S2Cell *)DatumGetPointer(X))
#define S2CellPGetDatum(X) PointerGetDatum(X)
#define PGS2_GETARG_S2CELL_P(n) DatumGetS2CellP(PG_GETARG_DATUM(n))
#define PGS2_RETURN_S2CELL_P(x) return S2CellPGetDatum(x)

int32 S2Cell_cmp_internal(pgs2_S2Cell *A, pgs2_S2Cell *B);
PG_FUNCTION_INFO_V1(S2Cell);
PG_FUNCTION_INFO_V1(S2Cell_in);
PG_FUNCTION_INFO_V1(S2Cell_out);
PG_FUNCTION_INFO_V1(S2Cell_eq);
PG_FUNCTION_INFO_V1(S2Cell_lt);
PG_FUNCTION_INFO_V1(S2Cell_gt);
PG_FUNCTION_INFO_V1(S2Cell_le);
PG_FUNCTION_INFO_V1(S2Cell_ge);
PG_FUNCTION_INFO_V1(S2Cell_cmp);
PG_FUNCTION_INFO_V1(S2Cell_distance);
PG_FUNCTION_INFO_V1(btS2Cellsortsupport);

#endif
