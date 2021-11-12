
void s2c_token_to_id(char* token, uint64_t *id) {
    *id = S2CellId::FromToken(token, strlen(token)).id();
}

void s2c_id_to_token(uint64_t id, char **token) {
    *token =  strdup(S2CellId(id).ToToken().c_str());
}

void s2c_id_to_xyz(uint64_t id, double *x, double *y, double *z) {
    S2Cell cell = S2Cell(S2CellId(id));
    S2Point point = cell.GetCenter();
    *x = point.x();
    *y = point.y();
    *z = point.z();
}

