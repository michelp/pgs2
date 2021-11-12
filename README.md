# pgs2

Postgres extension for [S2 spherical geometry](https://s2geometry.io/).

## Fixed Length Types

These fixed length types are stored "flat" and only turned into S2
instances at the point of use.  They are stored very efficiently by
Postgres.

  - S2Cell: Stored as a 64-bit cell id.
  
  - S2Point: Stored as 3 double precision floats.

  - S2LatLng: Stored as 2 double precision floats.

  - S2Cap: TODO

  - S2LatLngRect: TODO

## Variable Length S2Region types

These types are variable length "expanded" types, they are stored in a
flattened representation using S2 Encoder/Decoder and automatically
expanded into live objects as needed when loaded into memory.

  - S2Polyline

  - S2Loop

  - S2Polygon

  - S2CellUnion

## Aggregate S2Builder

S2Builder is wrapped by an aggregate, any region can be added to the
builder.

  `select s2builder(region) from ... where ...;`

## Indexing

  - S2CellId QuadTree with sp-gist
  
  - S2Cell Token btree with text_pattern_ops?
  
