# pgs2

Postgres extension for [S2 spherical geometry](https://s2geometry.io/).

## Fixed Length Types

These fixed length types are stored "flat" and only turned into S2
instances at the point of use.  They are stored very efficiently by
Postgres.

### S2Cell: Stored as a 64-bit cell id.

A cell is stored as an unsigned 64 id, but since Postgres doesn't have
unsigned integer types, it's SQL representation is an S2 "token":

```

```

### S2Point: Stored as 3 double precision floats.

### S2Cap: Point and radius stored as 4 doubles.

### S2LatLng: Stored as 2 doubles.

### S2LatLngRect: Stored as 4 doubles.

## Variable Length S2Region types TODO

These types are variable length "expanded" types, they are stored in a
flattened representation using S2 Encoder/Decoder and automatically
expanded into live objects as needed when loaded into memory.

### S2CellUnion

### S2Polyline

### S2Loop

### S2Polygon

## Aggregate S2Builder TODO

S2Builder is wrapped by an aggregate, any region can be added to the
builder.

  `select s2builder(region) from ... where ...;`

s2builder supports all current geometry types.

## Indexing

### S2Cell Token btree with text_pattern_ops

### S2CellId QuadTree with SP-GIST TODO

### S2RegionTermIndexer using GIN TODO
