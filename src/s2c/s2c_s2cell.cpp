
void s2c_token_to_cell(char* token, pgs2_S2Cell *cell, error_cb cb) {
    try {
        cell->id = S2CellId::FromToken(token, strlen(token)).id();
    } CATCH_ALL(cb)
}

void s2c_cell_to_token(pgs2_S2Cell *cell, char **token, error_cb cb) {
    try {
        *token =  strdup(S2CellId(cell->id).ToToken().c_str());
    } CATCH_ALL(cb)
}

void s2c_cell_to_point(pgs2_S2Cell *cell, pgs2_S2Point *point, error_cb cb) {
    try {
        S2Cell C = S2Cell(S2CellId(cell->id));
        S2Point P = C.GetCenter();
        point->x = P.x();
        point->y = P.y();
        point->z = P.z();
    } CATCH_ALL(cb)
}
