-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION pgs2" to load this file. \quit

CREATE TYPE s2point;

CREATE FUNCTION s2point_in(cstring)
RETURNS s2point
AS '$libdir/pgs2', 's2point_in'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION s2point_out(s2point)
RETURNS cstring
AS '$libdir/pgs2', 's2point_out'
LANGUAGE C IMMUTABLE STRICT;

CREATE TYPE s2point (
    input = s2point_in,
    output = s2point_out,
    alignment = int4,
    storage = 'extended',
    internallength = -1
);

