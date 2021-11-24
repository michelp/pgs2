#ifndef PGS2POINT_H
#define PGS2POINT_H

#define DatumGetS2PointP(X) ((pgs2_S2Point *)DatumGetPointer(X))
#define S2PointPGetDatum(X) PointerGetDatum(X)
#define PGS2_GETARG_S2POINT_P(n) DatumGetS2PointP(PG_GETARG_DATUM(n))
#define PGS2_RETURN_S2POINT_P(x) return S2PointPGetDatum(x)

PG_FUNCTION_INFO_V1(S2Point);
PG_FUNCTION_INFO_V1(S2Point_in);
PG_FUNCTION_INFO_V1(S2Point_out);
PG_FUNCTION_INFO_V1(S2Point_eq);

#endif
