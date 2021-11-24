
s2c_S2CellUnion_t *s2c_S2CellUnion_new(uint64_t *cell_ids, size_t num_cells,
                                       error_cb cb) {
  try {
    s2c_S2CellUnion_t *U;
    std::vector<uint64> v;
    v.assign(cell_ids, cell_ids + num_cells);
    U = (s2c_S2CellUnion_t *)malloc(sizeof(*U));
    U->obj = new S2CellUnion(v);
    return U;
  }
  CATCH_ALL(cb)
  return NULL;
}

void s2c_S2CellUnion_cell_ids(s2c_S2CellUnion_t *cell, uint64_t *cell_ids,
                              error_cb cb) {
  try {
    S2CellUnion *cell_union;
    cell_union = static_cast<S2CellUnion *>(cell->obj);
    memcpy(cell_ids, cell_union->cell_ids().data(),
           cell_union->size() * sizeof(uint64_t));
  }
  CATCH_ALL(cb)
}

void s2c_S2CellUnion_free(s2c_S2CellUnion_t *U, error_cb cb) {
  if (U == NULL)
    return;
  try {
    delete static_cast<S2CellUnion *>(U->obj);
    free(U);
  }
  CATCH_ALL(cb)
}
