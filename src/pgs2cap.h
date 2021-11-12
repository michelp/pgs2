#ifndef PGS2CAP_H
#define PGS2CAP_H

typedef struct pgs2_S2Cap {
    double x, y, z, r;
} pgs2_S2Cap;

#define DatumGetS2CapP(X)    ((pgs2_S2Cap *) DatumGetPointer(X))
#define S2CapPGetDatum(X)    PointerGetDatum(X)
#define PGS2_GETARG_S2CAP_P(n) DatumGetS2CapP(PG_GETARG_DATUM(n))
#define PGS2_RETURN_S2CAP_P(x) return S2CapPGetDatum(x)

PG_FUNCTION_INFO_V1(S2Cap);
PG_FUNCTION_INFO_V1(S2Cap_in);
PG_FUNCTION_INFO_V1(S2Cap_out);
PG_FUNCTION_INFO_V1(S2Cap_eq);

#endif
