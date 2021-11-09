#include <stdlib.h>
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include "s2c.h"
#include "s2/base/commandlineflags.h"
#include "s2/s2earth.h"
#include "s2/s1chord_angle.h"
#include "s2/s2closest_point_query.h"
#include "s2/s2point_index.h"
#include "s2/s2testing.h"


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

void s2c_S2Point_free(s2c_S2Point_t *m) {
    if (m == NULL)
		return;
	delete static_cast<S2Point *>(m->obj);
	free(m);    
}

void s2c_S2Point_xyz(s2c_S2Point_t *m, double *x, double *y, double *z) {
    *x = static_cast<S2Point *>(m->obj)->x();
    *y = static_cast<S2Point *>(m->obj)->y();
    *z = static_cast<S2Point *>(m->obj)->z();
}
