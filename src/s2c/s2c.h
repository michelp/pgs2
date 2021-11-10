#ifndef __S2C_H__
#define __S2C_H__


#ifdef __cplusplus
extern "C" {
#endif

#define T_t(T) T ## _t

#define STRUCTS(T)                              \
    struct T;                                   \
    typedef struct T T_t(T);

#define BASE_METHODS(T, ...)                                 \
    T_t(T)* T ## _new(__VA_ARGS__);                          \
    void T ## _free(T_t(T) *A);                              \
    bool T ## _eq(T_t(T) *A, T_t(T) *B);                     \

// S2Point

STRUCTS(s2c_S2Point);
BASE_METHODS(s2c_S2Point, double x, double y, double z);
void s2c_S2Point_xyz(s2c_S2Point_t *m, double *x, double *y, double *z);

#ifdef __cplusplus
}
#endif

#endif /* __S2C_H__ */
