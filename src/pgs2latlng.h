#ifndef PGS2LATLNG_H
#define PGS2LATLNG_H

#define DatumGetS2LatLngP(X) ((pgs2_S2LatLng *)DatumGetPointer(X))
#define S2LatLngPGetDatum(X) PointerGetDatum(X)
#define PGS2_GETARG_S2LATLNG_P(n) DatumGetS2LatLngP(PG_GETARG_DATUM(n))
#define PGS2_RETURN_S2LATLNG_P(x) return S2LatLngPGetDatum(x)

PG_FUNCTION_INFO_V1(S2LatLng);
PG_FUNCTION_INFO_V1(S2LatLng_in);
PG_FUNCTION_INFO_V1(S2LatLng_out);
PG_FUNCTION_INFO_V1(S2LatLng_eq);

#endif
