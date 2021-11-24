
BASE_METHODS(s2c_S2CellUnion, uint64_t *cell_ids, size_t num_cells);

void s2c_S2CellUnion_cell_ids(s2c_S2CellUnion_t *cell, uint64_t *cell_ids, error_cb cb);
void s2c_cellunion_normalize(s2c_S2CellUnion_t*, s2c_S2CellUnion_t*, double*, error_cb cb);
