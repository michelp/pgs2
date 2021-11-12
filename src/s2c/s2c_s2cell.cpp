
void s2c_token_to_id(char* token, uint64_t *id, error_cb cb) {
    try {
        *id = S2CellId::FromToken(token, strlen(token)).id();
    } CATCH_ALL(cb)
}

void s2c_id_to_token(uint64_t id, char **token, error_cb cb) {
    try {
        *token =  strdup(S2CellId(id).ToToken().c_str());
    } CATCH_ALL(cb)
}

void s2c_id_to_xyz(uint64_t id, double *x, double *y, double *z, error_cb cb) {
    try {
        S2Cell cell = S2Cell(S2CellId(id));
        S2Point point = cell.GetCenter();
        *x = point.x();
        *y = point.y();
        *z = point.z();
    } CATCH_ALL(cb)
}

