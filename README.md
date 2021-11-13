# pgs2

Postgres extension for [S2 spherical geometry](https://s2geometry.io/).

## Fixed Length Types

These fixed length types are stored "flat" and only turned into S2
instances at the point of use.  They are stored very efficiently by
Postgres.

### S2Point

Stored as 3 double precision floats.

### S2Cap

Point and radius stored as 4 doubles.

### S2LatLng

Stored as 2 doubles.

### S2LatLngRect

Stored as 4 doubles.

### S2Cell

An S2CellId is an unsigned 64bit integer, but since Postgres doesn't
have unsigned integer types, it's SQL literal representation is an
S2Cell "token" string.  The token is decoded into an unsigned int64
and stored optimally.

Cells can be cast to S2Point and S2LatLng by returning their center
point.  S2Point and S2LatLng can be cast to a cell.  Normally there is
exactly one such cell for a given point, but for points along cell
boundaries one cell id detiministically chosen:

```

```


## TODO Variable Length S2Region Types

These types are variable length "expanded" types, they are stored in a
flattened representation using S2 Encoder/Decoder and automatically
expanded into live objects as needed when loaded into memory.

### S2CellUnion

### S2Polyline

### S2Loop

### S2Polygon

## TODO Aggregate S2Builder

S2Builder is wrapped by an aggregate, any region can be added to the
builder.

  `select s2builder(region, layer_name) as from ... where ...;`

s2builder supports all current geometry types.

## TODO Indexing

### S2Cell Token btree with text_pattern_ops

### S2CellId QuadTree with SP-GIST TODO

### S2RegionTermIndexer using GIN TODO
