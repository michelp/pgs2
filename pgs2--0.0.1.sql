-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION pgs2" to load this file. \quit

CREATE TYPE S2Point;
CREATE TYPE S2Cell;
CREATE TYPE S2LatLng;
CREATE TYPE S2Cap;

CREATE OPERATOR FAMILY S2_ops USING btree;

-- S2Cell

CREATE FUNCTION S2Cell_in(cstring)
RETURNS S2Cell
AS '$libdir/pgs2', 'S2Cell_in'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION S2Cell_out(S2Cell)
RETURNS cstring
AS '$libdir/pgs2', 'S2Cell_out'
LANGUAGE C IMMUTABLE STRICT;

CREATE TYPE S2Cell (
    input = S2Cell_in,
    output = S2Cell_out,
    alignment = double,
    storage = 'plain',
    internallength = 8,
    category = 'G'
);

CREATE FUNCTION S2Cell_eq(A S2Cell, B S2Cell)
RETURNS bool
AS '$libdir/pgs2', 'S2Cell_eq'
LANGUAGE C STABLE;

CREATE OPERATOR = (
    leftarg = S2Cell,
    rightarg = S2Cell,
    procedure = S2Cell_eq,
    negator = <>
);

CREATE FUNCTION S2Cell_lt(A S2Cell, B S2Cell)
RETURNS bool
AS '$libdir/pgs2', 'S2Cell_lt'
LANGUAGE C STABLE;

CREATE OPERATOR < (
    leftarg = S2Cell,
    rightarg = S2Cell,
    procedure = S2Cell_lt,
    negator = >=,
    commutator = >,
    restrict = scalarltsel,
    join = scalarltjoinsel
);

CREATE FUNCTION S2Cell_gt(A S2Cell, B S2Cell)
RETURNS bool
AS '$libdir/pgs2', 'S2Cell_gt'
LANGUAGE C STABLE;

CREATE OPERATOR > (
    leftarg = S2Cell,
    rightarg = S2Cell,
    procedure = S2Cell_gt,
    negator = <=,
    commutator = <,
    restrict = scalargtsel,
    join = scalargtjoinsel
);

CREATE FUNCTION S2Cell_le(A S2Cell, B S2Cell)
RETURNS bool
AS '$libdir/pgs2', 'S2Cell_le'
LANGUAGE C STABLE;

CREATE OPERATOR <= (
    leftarg = S2Cell,
    rightarg = S2Cell,
    procedure = S2Cell_le,
    negator = >,
    commutator = >=,
    restrict = scalarltsel,
    join = scalarltjoinsel
);

CREATE FUNCTION S2Cell_ge(A S2Cell, B S2Cell)
RETURNS bool
AS '$libdir/pgs2', 'S2Cell_ge'
LANGUAGE C STABLE;

CREATE OPERATOR >= (
    leftarg = S2Cell,
    rightarg = S2Cell,
    procedure = S2Cell_ge,
    negator = <,
    commutator = <=,
    restrict = scalargtsel,
    join = scalargtjoinsel
);

CREATE FUNCTION S2Cell_cmp(A S2Cell, B S2Cell)
RETURNS int
AS '$libdir/pgs2', 'S2Cell_cmp'
LANGUAGE C STABLE;

CREATE FUNCTION S2Cell_distance(A S2Cell, B S2Cell)
RETURNS float8
AS '$libdir/pgs2', 'S2Cell_distance'
LANGUAGE C STABLE;

CREATE OPERATOR <-> (
    leftarg = S2Cell,
    rightarg = S2Cell,
    procedure = S2Cell_distance
);

CREATE FUNCTION btS2Cellsortsupport(internal)
RETURNS void
AS '$libdir/pgs2', 'btS2Cellsortsupport'
LANGUAGE C STABLE;

CREATE OPERATOR CLASS S2Cell_ops
    DEFAULT FOR TYPE S2Cell USING btree FAMILY S2_ops AS
    OPERATOR 1 <  (S2Cell, S2Cell),
    OPERATOR 2 <= (S2Cell, S2Cell),
    OPERATOR 3 =  (S2Cell, S2Cell),
    OPERATOR 4 >= (S2Cell, S2Cell),
    OPERATOR 5 >  (S2Cell, S2Cell),
    FUNCTION 1 S2Cell_cmp (S2Cell, S2Cell),
    FUNCTION 2 btS2Cellsortsupport(internal),
    FUNCTION 4 btequalimage(oid);

-- S2Point

CREATE FUNCTION S2Point(x float8, y float8, z float8 = 0.0)
RETURNS S2Point
AS '$libdir/pgs2', 'S2Point'
LANGUAGE C STRICT;

CREATE FUNCTION S2Point_in(cstring)
RETURNS S2Point
AS '$libdir/pgs2', 'S2Point_in'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION S2Point_out(S2Point)
RETURNS cstring
AS '$libdir/pgs2', 'S2Point_out'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION S2Point_eq(A S2Point, B S2Point)
RETURNS bool
AS '$libdir/pgs2', 'S2Point_eq'
LANGUAGE C STABLE;

CREATE TYPE S2Point (
    input = S2Point_in,
    output = S2Point_out,
    alignment = double,
    storage = 'plain',
    internallength = 24,
    element = float8,
    category = 'G'
);

CREATE OPERATOR = (
    leftarg = S2Point,
    rightarg = S2Point,
    procedure = S2Point_eq,
    negator = <>
);

-- LatLng

CREATE FUNCTION S2LatLng(x float8, y float8, degrees bool = False)
RETURNS S2LatLng
AS '$libdir/pgs2', 'S2LatLng'
LANGUAGE C STRICT;

CREATE FUNCTION S2LatLng_in(cstring)
RETURNS S2LatLng
AS '$libdir/pgs2', 'S2LatLng_in'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION S2LatLng_out(S2LatLng)
RETURNS cstring
AS '$libdir/pgs2', 'S2LatLng_out'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION S2LatLng_eq(A S2LatLng, B S2LatLng)
RETURNS bool
AS '$libdir/pgs2', 'S2LatLng_eq'
LANGUAGE C STABLE;

CREATE TYPE S2LatLng (
    input = S2LatLng_in,
    output = S2LatLng_out,
    alignment = double,
    storage = 'plain',
    internallength = 16,
    element = float8,
    category = 'G'
);

CREATE OPERATOR = (
    leftarg = S2LatLng,
    rightarg = S2LatLng,
    procedure = S2LatLng_eq,
    negator = <>
);

-- S2Cap

CREATE FUNCTION S2Cap(center S2Point, radium float8 = 0.0)
RETURNS S2Cap
AS '$libdir/pgs2', 'S2Cap'
LANGUAGE C STRICT;

CREATE FUNCTION S2Cap_in(cstring)
RETURNS S2Cap
AS '$libdir/pgs2', 'S2Cap_in'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION S2Cap_out(S2Cap)
RETURNS cstring
AS '$libdir/pgs2', 'S2Cap_out'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION S2Cap_eq(A S2Cap, B S2Cap)
RETURNS bool
AS '$libdir/pgs2', 'S2Cap_eq'
LANGUAGE C STABLE;

CREATE TYPE S2Cap (
    input = S2Cap_in,
    output = S2Cap_out,
    alignment = double,
    storage = 'plain',
    internallength = 32,
    category = 'G'
);

CREATE OPERATOR = (
    leftarg = S2Cap,
    rightarg = S2Cap,
    procedure = S2Cap_eq,
    negator = <>
);

-- LatLngRect

CREATE FUNCTION S2LatLngRect(lo S2Point, hi S2Point)
RETURNS S2LatLngRect
AS '$libdir/pgs2', 'S2LatLngRect'
LANGUAGE C STRICT;

CREATE FUNCTION S2LatLngRect_in(cstring)
RETURNS S2LatLngRect
AS '$libdir/pgs2', 'S2LatLngRect_in'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION S2LatLngRect_out(S2LatLngRect)
RETURNS cstring
AS '$libdir/pgs2', 'S2LatLngRect_out'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION S2LatLngRect_eq(A S2LatLngRect, B S2LatLngRect)
RETURNS bool
AS '$libdir/pgs2', 'S2LatLngRect_eq'
LANGUAGE C STABLE;

CREATE TYPE S2LatLngRect (
    input = S2LatLngRect_in,
    output = S2LatLngRect_out,
    alignment = double,
    storage = 'plain',
    internallength = 32,
    element = s2latlng,
    category = 'G'
);

CREATE OPERATOR = (
    leftarg = S2LatLngRect,
    rightarg = S2LatLngRect,
    procedure = S2LatLngRect_eq,
    negator = <>
);

-- casts

CREATE FUNCTION S2Point_as_S2Cell(p S2Point)
RETURNS S2Cell
AS '$libdir/pgs2', 'S2Point_as_S2Cell'
LANGUAGE C STRICT;

CREATE CAST (S2Point AS S2Cell) WITH FUNCTION S2Point_as_S2Cell(S2Point) AS ASSIGNMENT;

CREATE FUNCTION S2Point_as_S2LatLng(p S2Point)
RETURNS S2LatLng
AS '$libdir/pgs2', 'S2Point_as_S2LatLng'
LANGUAGE C STRICT;

CREATE CAST (S2Point AS S2LatLng) WITH FUNCTION S2Point_as_S2LatLng(S2Point) AS ASSIGNMENT;

CREATE FUNCTION S2Cell_as_S2Point(c S2Cell)
RETURNS S2Point
AS '$libdir/pgs2', 'S2Cell_as_S2Point'
LANGUAGE C STRICT;

CREATE CAST (S2Cell AS S2Point) WITH FUNCTION S2Cell_as_S2Point(S2Cell) AS ASSIGNMENT;

CREATE FUNCTION S2Cell_as_S2LatLng(c S2Cell)
RETURNS S2LatLng
AS '$libdir/pgs2', 'S2Cell_as_S2LatLng'
LANGUAGE C STRICT;

CREATE CAST (S2Cell AS S2LatLng) WITH FUNCTION S2Cell_as_S2LatLng(S2Cell) AS ASSIGNMENT;


CREATE FUNCTION S2LatLng_as_S2Point(ll S2LatLng)
RETURNS S2Point
AS '$libdir/pgs2', 'S2LatLng_as_S2Point'
LANGUAGE C STRICT;

CREATE CAST (S2LatLng AS S2Point) WITH FUNCTION S2LatLng_as_S2Point(S2LatLng) AS ASSIGNMENT;


CREATE FUNCTION S2LatLng_as_S2Cell(p S2LatLng)
RETURNS S2Cell
AS '$libdir/pgs2', 'S2LatLng_as_S2Cell'
LANGUAGE C STRICT;

CREATE CAST (S2LatLng AS S2Cell) WITH FUNCTION S2LatLng_as_S2Cell(S2LatLng) AS ASSIGNMENT;
