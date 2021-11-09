#ifndef PGS2POINT_H
#define PGS2POINT_H

/* ID for debugging crosschecks */
#define s2point_MAGIC 689276813

/* Flattened representation of s2point, used to store to disk.

The first 32 bits must the length of the data.  Actual array data is
appended after this struct and cannot exceed 1GB.
*/
typedef struct pgs2_FlatS2point {
    int32 vl_len_;
    double x;
    double y;
    double z;
} pgs2_FlatS2point;

/* S2 representation of s2point.

When loaded from storage, the flattened representation is used to
build the s2point.

This is a simple coordinate storage format of 3 equal sized unsigned
integer arrays.
*/
typedef struct pgs2_S2point  {
    ExpandedObjectHeader hdr;
    int em_magic;
    s2c_S2Point_t *point;    
    Size flat_size;
} pgs2_S2point;

/* Callback function for freeing s2point arrays. */
static void
context_callback_s2point_free(void*);

/* S2 Object Header "methods" for flattening matrices for storage */
static Size
s2point_get_flat_size(ExpandedObjectHeader *eohptr);

static void
s2point_flatten_into(ExpandedObjectHeader *eohptr,
                     void *result, Size allocated_size);

static const ExpandedObjectMethods s2point_methods = {
     s2point_get_flat_size,
     s2point_flatten_into
    };

/* Utility function that expands a flattened s2point datum. */
Datum
expand_flat_s2point(pgs2_FlatS2point *flat,
                   MemoryContext parentcontext);

pgs2_S2point *
construct_empty_s2_s2point(uint64_t nrows,
                                uint64_t ncols,
                                MemoryContext parentcontext);

/* Helper function that either detoasts or expands matrices. */
pgs2_S2point *
DatumGetS2point(Datum d);

/* Helper function to create an empty flattened s2point. */
pgs2_FlatS2point *
construct_empty_flat_s2point(uint64_t nrows, uint64_t ncols);

/* Helper macro to detoast and expand s2points arguments */
#define PGS2_GETARG_S2POINT(n)  DatumGetS2point(PG_GETARG_DATUM(n))

/* Helper macro to return S2 Object Header Pointer from s2point. */
#define PGS2_RETURN_S2POINT(A) return EOHPGetRWDatum(&(A)->hdr)

/* Helper macro to compute flat s2point header size */
#define PGS2_S2POINT_OVERHEAD() MAXALIGN(sizeof(pgs2_FlatS2point))

/* Helper macro to get pointer to beginning of s2point data. */
#define PGS2_S2POINT_DATA(a) ((uint64_t *)(((char *) (a)) + PGS2_S2POINT_OVERHEAD()))

/* Help macro to cast generic Datum header pointer to s2 S2point */
#define S2pointGetEOHP(d) (pgs2_S2point *) DatumGetEOHP(d);

/* Public API functions */

PG_FUNCTION_INFO_V1(s2point);
PG_FUNCTION_INFO_V1(s2point_in);
PG_FUNCTION_INFO_V1(s2point_out);
PG_FUNCTION_INFO_V1(s2point_eq);

#endif /* PGS2POINT_H */
