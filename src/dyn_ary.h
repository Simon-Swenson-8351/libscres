#ifndef DYN_ARY_H
#define DYN_ARY_H

#include "scres_err.h"

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

#include <stddef.h>
#include <inttypes.h>
#include <stdbool.h>

typedef struct dyn_ary {
    size_t datatype_size;
    size_t count;
    size_t cap;
    uint8_t *data_buf;
} dyn_ary_t;

scres_err_t *dyn_ary_init(
    dyn_ary_t *ary_to_init,
    size_t datatype_size,
    size_t init_ary_cap_exp // actual initial cap is 2^init_ary_cap_exp
);

scres_err_t *dyn_ary_insert_many(
    dyn_ary_t *self,
    const uint8_t *buf_to_insert,
    size_t count_to_insert,
    size_t position_in_ary
);

scres_err_t *dyn_ary_insert(
    dyn_ary_t *self,
    const uint8_t *buf_to_insert,
    size_t position_in_ary
);

scres_err_t *dyn_ary_append(
    dyn_ary_t *self,
    const uint8_t *buf_to_insert
);

scres_err_t *dyn_ary_prepend(
    dyn_ary_t *self,
    const uint8_t *buf_to_insert
);

scres_err_t *dyn_ary_get_many(
    const dyn_ary_t *self,
    size_t idx,
    size_t count,
    uint8_t *out_buf
);

scres_err_t *dyn_ary_get(
    const dyn_ary_t *self,
    size_t idx,
    uint8_t *out_buf
);

scres_err_t *dyn_ary_set_many(
    dyn_ary_t *self,
    size_t idx,
    size_t count,
    const uint8_t *in_buf,
    bool retrieve_old_val,
    uint8_t *old_val_buf
);

scres_err_t *dyn_ary_set(
    dyn_ary_t *self,
    size_t idx,
    const uint8_t *in_buf,
    bool retrieve_old_val,
    uint8_t *old_val_buf
);

scres_err_t *dyn_ary_remove_many(
    dyn_ary_t *self,
    size_t idx,
    size_t count,
    bool retrieve_old_vals,
    const uint8_t *old_vals_buf
);

scres_err_t *dyn_ary_remove(
    dyn_ary_t *self,
    size_t idx,
    bool retrieve_old_val,
    const uint8_t *old_val_buf
);

scres_err_t *dyn_ary_pop(
    dyn_ary_t *self,
    bool retrieve_old_val,
    const uint8_t *old_val_buf
);

scres_err_t *dyn_ary_pop_front(
    dyn_ary_t *self,
    bool retrieve_old_val,
    const uint8_t *old_val_buf
);

scres_err_t *dyn_ary_clear(dyn_ary_t *ary_to_clear);

size_t dyn_ary_best_cap_exp(size_t count);

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

#endif // #ifndef DYN_ARY_H