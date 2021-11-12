Datum
S2Cell_in(PG_FUNCTION_ARGS) {
    char *token;
    pgs2_S2Cell *cell;
    
    token = PG_GETARG_CSTRING(0);
    cell = palloc0(sizeof(pgs2_S2Cell));
    s2c_token_to_id(token, &(cell->id));
    PGS2_RETURN_S2CELL_P(cell);
}

Datum
S2Cell_out(PG_FUNCTION_ARGS)
{
    char *token, *result;
    StringInfoData str;

    pgs2_S2Cell *p = PGS2_GETARG_S2CELL_P(0);
    initStringInfo(&str);
    s2c_id_to_token(p->id, &token);
    result = pstrdup(token);
    free(token);
    PG_RETURN_CSTRING(result);
}

Datum
S2Cell_eq(PG_FUNCTION_ARGS) {
    pgs2_S2Cell *A, *B;
    A = PGS2_GETARG_S2CELL_P(0);
    B = PGS2_GETARG_S2CELL_P(1);
    PG_RETURN_BOOL(A->id == B->id);
}
