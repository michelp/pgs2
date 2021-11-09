-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION pgs2" to load this file. \quit

CREATE TYPE s2point;

CREATE FUNCTION s2point(x float8, y float8, z float8 = 0.0)
RETURNS s2point
AS '$libdir/pgs2', 's2point'
LANGUAGE C STRICT;

CREATE FUNCTION s2point_in(cstring)
RETURNS s2point
AS '$libdir/pgs2', 's2point_in'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION s2point_out(s2point)
RETURNS cstring
AS '$libdir/pgs2', 's2point_out'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION s2point_eq(A s2point, B s2point)
RETURNS bool
AS '$libdir/pgs2', 's2point_eq'
LANGUAGE C STABLE;

CREATE TYPE s2point (
    input = s2point_in,
    output = s2point_out,
    alignment = double,
    storage = 'plain',
    internallength = 24,
    category = 'G'
);

CREATE OPERATOR = (
    leftarg = s2point,
    rightarg = s2point,
    procedure = s2point_eq,
    negator = <>
);

    

