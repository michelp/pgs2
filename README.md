# pgS2

Postgres extension for [S2 spherical coordinates](https://s2geometry.io/).

## Fixed Length Types

  - S2Cell: Stored as a 64-bit cell id.

  - S2Point: Stored as 3 double precision floats.

  - S2LatLng: Stored as 2 double precision floats.

  - S2LatLngRect: Stored as

## Supported S2Region types:

  - S2Point points are internally promoted to regions when necessary.
    But stored and indexed as points.

  - S2LatLngRect

  - S2Cap

  - S2Polyline

  - S2Loop

  - S2Polygon


## Aggregate S2Builder

S2Builder is wrapped by an aggregate, any region can be added to the
builder.

  `select s2builder(region) from ... where ...;`
