
Datum
S2Cell_in(PG_FUNCTION_ARGS) {
    char *token;
    pgs2_S2Cell *p;
    
    token = PG_GETARG_CSTRING(0);
    p = palloc0(sizeof(pgs2_S2Cell));
    p->id = s2c_S2Cell_token_to_id(token);
    PGS2_RETURN_S2CELL_P(p);
}

Datum
S2Cell_out(PG_FUNCTION_ARGS)
{
    const char *token;
    StringInfoData str;

    pgs2_S2Cell *p = PGS2_GETARG_S2CELL_P(0);
    initStringInfo(&str);
    token = s2c_S2Cell_id_to_token(p->id);
    PG_RETURN_CSTRING(token);
}

Datum
S2Cell_eq(PG_FUNCTION_ARGS) {
  pgs2_S2Cell *A, *B;

  A = PGS2_GETARG_S2CELL_P(0);
  B = PGS2_GETARG_S2CELL_P(1);

  PG_RETURN_BOOL(A->id == B->id);
}
