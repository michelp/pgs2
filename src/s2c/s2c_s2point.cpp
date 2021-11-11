
struct s2c_S2Point {
	void *obj;
};

s2c_S2Point_t *s2c_S2Point_new(double x, double y, double z) {
	s2c_S2Point_t *m;
    S2Point *obj;
    
	m = (typeof(m))malloc(sizeof(*m));
	obj = new S2Point(x, y, z);
	m->obj = obj;

	return m;
}

#define CAST_POINT(p) (static_cast<S2Point *>((p)->obj))


void s2c_S2Point_free(s2c_S2Point_t *m) {
    if (m == NULL)
		return;
	delete CAST_POINT(m);
	free(m);    
}

void s2c_S2Point_xyz(s2c_S2Point_t *m, double *x, double *y, double *z) {
    *x = CAST_POINT(m)->x();
    *y = CAST_POINT(m)->y();
    *z = CAST_POINT(m)->z();
}

bool s2c_S2Point_eq(s2c_S2Point_t *A, s2c_S2Point_t *B) {
    return (CAST_POINT(A)->x() == CAST_POINT(B)->x() &&
            CAST_POINT(A)->y() == CAST_POINT(B)->y() &&
            CAST_POINT(A)->z() == CAST_POINT(B)->z());
}
