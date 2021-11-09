#ifndef __S2C_H__
#define __S2C_H__


#ifdef __cplusplus
extern "C" {
#endif

struct s2c_S2Point;
typedef struct s2c_S2Point s2c_S2Point_t;

s2c_S2Point_t *s2c_S2Point_new(double x, double y, double z);
void s2c_S2Point_free(s2c_S2Point_t *m);
void s2c_S2Point_xyz(s2c_S2Point_t *m, double *x, double *y, double *z);

#ifdef __cplusplus
}
#endif

#endif /* __S2C_H__ */
