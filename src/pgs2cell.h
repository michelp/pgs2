#ifndef PGS2CELL_H
#define PGS2CELL_H

#define DatumGetS2cellP(X)    ((pgs2_S2Cell *) DatumGetPointer(X))
#define S2cellPGetDatum(X)    PointerGetDatum(X)
#define PGS2_GETARG_S2CELL_P(n) DatumGetS2cellP(PG_GETARG_DATUM(n))
#define PGS2_RETURN_S2CELL_P(x) return S2cellPGetDatum(x)

PG_FUNCTION_INFO_V1(S2Cell);
PG_FUNCTION_INFO_V1(S2Cell_in);
PG_FUNCTION_INFO_V1(S2Cell_out);
PG_FUNCTION_INFO_V1(S2Cell_eq);

#endif
