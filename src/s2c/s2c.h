#ifndef __S2C_H__
#define __S2C_H__


#ifdef __cplusplus
extern "C" {
#endif

typedef void (*error_cb)(const char *msg);

#define T_t(T) T ## _t

#define STRUCTS(T)                              \
    struct T {                                  \
        void *obj;                              \
    };                                          \
    typedef struct T T_t(T)

#define BASE_METHODS(T, ...)                                    \
    T_t(T)* T ## _new(__VA_ARGS__ __VA_OPT__(,) error_cb cb);   \
    void T ## _free(T_t(T) *A, error_cb cb);                    \
    bool T ## _eq(T_t(T) *A, T_t(T) *B, error_cb cb);           \

#define CATCH_ALL(E) catch (const std::exception& ex) { \
        E(ex.what());                                   \
    }

#include "src/s2types.h"
#include "s2c_s2point.h"
#include "s2c_s2cell.h"
#include "s2c_s2cell_union.h"
#include "s2c_s2latlng.h"

#ifdef __cplusplus
}
#endif

#endif /* __S2C_H__ */
