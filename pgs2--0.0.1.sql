-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION pgs2" to load this file. \quit

CREATE TYPE S2Point;

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

-- CREATE TYPE S2LatLng;

-- CREATE FUNCTION S2LatLng(lat float8, lng float8)
-- RETURNS S2LatLng
-- AS '$libdir/pgs2', 'S2LatLng'
-- LANGUAGE C STRICT;

-- CREATE FUNCTION S2LatLng_in(cstring)
-- RETURNS S2LatLng
-- AS '$libdir/pgs2', 'S2LatLng_in'
-- LANGUAGE C IMMUTABLE STRICT;

-- CREATE FUNCTION S2LatLng_out(S2LatLng)
-- RETURNS cstring
-- AS '$libdir/pgs2', 'S2LatLng_out'
-- LANGUAGE C IMMUTABLE STRICT;

-- CREATE FUNCTION S2LatLng_eq(A S2LatLng, B S2LatLng)
-- RETURNS bool
-- AS '$libdir/pgs2', 'S2LatLng_eq'
-- LANGUAGE C STABLE;

-- CREATE TYPE S2LatLng (
--     input = S2LatLng_in,
--     output = S2LatLng_out,
--     alignment = double,
--     storage = 'extended',
--     internallength = variable,
--     category = 'G'
-- );

-- CREATE OPERATOR = (
--     leftarg = S2LatLng,
--     rightarg = S2LatLng,
--     procedure = S2LatLng_eq,
--     negator = <>
-- );
    
    

