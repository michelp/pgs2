#ifndef PGS2LATLNGRECT_H
#define PGS2LATLNGRECT_H

typedef struct pgs2_S2LatLngRect {
    pgs2_S2Point lo, hi;
} pgs2_S2LatLngRect;

#define DatumGetS2LatLngRectP(X)    ((pgs2_S2LatLngRect *) DatumGetPointer(X))
#define S2LatLngRectPGetDatum(X)    PointerGetDatum(X)
#define PGS2_GETARG_S2LATLNGRECT_P(n) DatumGetS2LatLngRectP(PG_GETARG_DATUM(n))
#define PGS2_RETURN_S2LATLNGRECT_P(x) return S2LatLngRectPGetDatum(x)

PG_FUNCTION_INFO_V1(S2LatLngRect);
PG_FUNCTION_INFO_V1(S2LatLngRect_in);
PG_FUNCTION_INFO_V1(S2LatLngRect_out);
PG_FUNCTION_INFO_V1(S2LatLngRect_eq);

#endif
