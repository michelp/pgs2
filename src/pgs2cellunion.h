#ifndef PGS2CELLUNION_H
#define PGS2CELLUNION_H

#define S2CellUnion_MAGIC 689276813

typedef struct pgs2_FlatS2CellUnion {
  int32 vl_len_;
  int32 nvals;
} pgs2_FlatS2CellUnion;

typedef struct pgs2_S2CellUnion {
  ExpandedObjectHeader hdr;
  int em_magic;
  s2c_S2CellUnion_t *cell_union;
  int32 nvals;
  Size flat_size;
} pgs2_S2CellUnion;

static void context_callback_S2CellUnion_free(void *);

static Size S2CellUnion_get_flat_size(ExpandedObjectHeader *eohptr);

static void S2CellUnion_flatten_into(ExpandedObjectHeader *eohptr, void *result,
                                     Size allocated_size);

static const ExpandedObjectMethods S2CellUnion_methods = {
    S2CellUnion_get_flat_size, S2CellUnion_flatten_into};

Datum expand_flat_S2CellUnion(pgs2_FlatS2CellUnion *flat,
                              MemoryContext parentcontext);

pgs2_S2CellUnion *
construct_empty_expanded_S2CellUnion(uint64_t nvals,
                                     MemoryContext parentcontext);

pgs2_S2CellUnion *DatumGetS2CellUnion(Datum d);

pgs2_FlatS2CellUnion *construct_empty_flat_S2CellUnion();

#define PGS2_GETARG_S2CELLUNION(n) DatumGetS2CellUnion(PG_GETARG_DATUM(n))

#define PGS2_RETURN_S2CELLUNION(A) return EOHPGetRWDatum(&(A)->hdr)

#define PGS2_S2CELLUNION_OVERHEAD() MAXALIGN(sizeof(pgs2_FlatS2CellUnion))

#define PGS2_S2CELLUNION_DATA(a)                                               \
  ((uint64_t *)(((char *)(a)) + PGS2_S2CELLUNION_OVERHEAD()))

#define S2CellUnionGetEOHP(d) (pgs2_S2CellUnion *)DatumGetEOHP(d);

PG_FUNCTION_INFO_V1(S2CellUnion);
PG_FUNCTION_INFO_V1(S2CellUnion_in);
PG_FUNCTION_INFO_V1(S2CellUnion_out);

PG_FUNCTION_INFO_V1(S2CellUnion_Normalize);

#endif
