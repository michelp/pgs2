
struct s2c_S2Cell {
	void *obj;
};

s2c_S2Cell_t *s2c_S2Cell_new(uint64_t id) {
	s2c_S2Cell_t *m;
    S2Cell *obj;
    
	m = (typeof(m))malloc(sizeof(*m));
	obj = new S2Cell(S2CellId(id));
	m->obj = obj;

	return m;
}

#define CAST_CELL(p) (static_cast<S2Cell *>((p)->obj))

void s2c_S2Cell_free(s2c_S2Cell_t *m) {
    if (m == NULL)
		return;
	delete CAST_CELL(m);
	free(m);    
}

bool s2c_S2Cell_eq(s2c_S2Cell_t *A, s2c_S2Cell_t *B) {
    return (CAST_CELL(A)->id() == CAST_CELL(B)->id());
}

uint64_t s2c_S2Cell_id(s2c_S2Cell_t *m) {
    return CAST_CELL(m)->id().id();
}

uint64_t s2c_S2Cell_token_to_id(char* token) {
    return S2CellId::FromToken(token, strlen(token)).id();
}

const char* s2c_S2Cell_id_to_token(uint64_t id) {
    return S2CellId(id).ToToken().c_str();
}

