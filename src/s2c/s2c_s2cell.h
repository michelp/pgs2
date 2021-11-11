STRUCTS(s2c_S2Cell);
BASE_METHODS(s2c_S2Cell, uint64_t id);

uint64_t s2c_S2Cell_id(s2c_S2Cell_t *m);
uint64_t s2c_S2Cell_token_to_id(char*);
const char* s2c_S2Cell_id_to_token(uint64_t);
