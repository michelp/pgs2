#ifndef PGS2TYPES_H
#define PGS2TYPES_H

typedef struct pgs2_S2Cell {
    uint64_t id;
} pgs2_S2Cell;

typedef struct pgs2_S2Point {
    double x, y, z;
} pgs2_S2Point;

typedef struct pgs2_S2Cap {
    pgs2_S2Point center;
    double radius;
} pgs2_S2Cap;

typedef struct pgs2_S2LatLng {
    double lat, lng;
} pgs2_S2LatLng;

typedef struct pgs2_S2LatLngRect {
    pgs2_S2LatLng lo, hi;
} pgs2_S2LatLngRect;

// cell union varlena types

STRUCTS(s2c_S2CellUnion);

#endif
