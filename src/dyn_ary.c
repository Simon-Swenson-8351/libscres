#include "dyn_ary.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

static const scres_err_type_t WARN_INS_0_ELEMS = 
    SCRES_ERR_TYPE_INIT(64, SCRES_ERR_LVL_WARN, "inserted 0 elements");

static uint8_t idx_to_byte_ptr(dyn_ary_t *self, size_t idx)
{
    return self->data_buf + (idx * self->datatype_size);
}

static size_t num_bytes(dyn_ary_t *self, size_t num_elems) {
    return num_elems * self->datatype_size;
}

static bool should_grow(size_t count, size_t cap)
{
    return count > cap;
}

static size_t grow_cap(size_t count, size_t cap)
{
    while(count > cap)
    {
        cap <<= 1;
    }
    return cap;
}

static bool should_shrink(size_t count, size_t cap)
{
    if(count == 0 && cap > 1) return true;
    if(cap < 4) return false;
    // array is <= a quarter full
    return count <= cap >> 2;
}

static size_t shrink_cap(size_t count, size_t cap)
{
    if(count == 0) return 1;
    while(count < cap >> 1)
    {
        // if the capacity is less than half filled
        cap >>= 1;
    }
    return cap;
}

scres_err_t *dyn_ary_init(
    dyn_ary_t *ary_to_init,
    size_t datatype_size,
    size_t init_ary_cap_exp
) {
    if(datatype_size == 0)
        SCRES_ERR_RETURN(&SCRES_ERR_TYPE_DOMAIN, __FILE__, __func__, __LINE__);
    ary_to_init->datatype_size = datatype_size;
    ary_to_init->count = 0;
    ary_to_init->cap = 1 << init_ary_cap_exp;
    if(!(ary_to_init->data_buf = malloc(num_bytes(ary_to_init, ary_to_init->cap))))
    {
        ary_to_init->cap = 0;
        SCRES_ERR_RETURN(&SCRES_ERR_TYPE_ALLOC_FAILED, __FILE__, __func__, __LINE__);
    }
    return NULL;
}

scres_err_t *dyn_ary_insert_many(
    dyn_ary_t *self,
    const uint8_t *buf_to_insert,
    size_t count_to_insert,
    size_t position_in_ary
) {
    if(count_to_insert == 0)
        SCRES_ERR_RETURN(&WARN_INS_0_ELEMS, __FILE__, __func__, __LINE__);
    if(position_in_ary > self->count)
        SCRES_ERR_RETURN(&SCRES_ERR_TYPE_DOMAIN, __FILE__, __func__, __LINE__);
    size_t new_count = self->count + count_to_insert;
    if(should_grow(new_count, self->cap)) {
        // cap must be expanded
        size_t new_cap = grow_cap(new_count, self->cap);
        uint8_t *new_buf;
        if(!(new_buf = realloc(self->data_buf, num_bytes(self, new_cap))))
            SCRES_ERR_RETURN(&SCRES_ERR_TYPE_ALLOC_FAILED, __FILE__, __func__, __LINE__);
        self->data_buf = new_buf;
        self->cap = new_cap;
    }
    if(position_in_ary < self->count) {
        // elements must be moved
        size_t elems_to_move = self->count - position_in_ary;
        size_t to_pos = new_count - elems_to_move;
        memmove(
            idx_to_byte_ptr(self, to_pos),
            idx_to_byte_ptr(self, position_in_ary),
            num_bytes(self, elems_to_move)
        );
    }
    // do the insertion
    memcpy(
        idx_to_byte_ptr(self, position_in_ary),
        buf_to_insert,
        num_bytes(self, position_in_ary)
    );
    self->count = new_count;
    return NULL;
}

scres_err_t *dyn_ary_insert(
    dyn_ary_t *self,
    const uint8_t *buf_to_insert,
    size_t position_in_ary
) {
    return dyn_ary_insert_many(self, buf_to_insert, 1, position_in_ary);
}

scres_err_t *dyn_ary_append(
    dyn_ary_t *self,
    const uint8_t *buf_to_insert
) {
    return dyn_ary_insert(self, buf_to_insert, self->count);
}

scres_err_t *dyn_ary_prepend(
    dyn_ary_t *self,
    const uint8_t *buf_to_insert
) {
    return dyn_ary_insert(self, buf_to_insert, 0);
}

scres_err_t *dyn_ary_get_many(
    const dyn_ary_t *self,
    size_t idx,
    size_t count,
    uint8_t *out_buf
) {
    if(idx + count > self->count)
        SCRES_ERR_RETURN(&SCRES_ERR_TYPE_DOMAIN, __FILE__, __func__, __LINE__);
    memcpy(out_buf, idx_to_byte_ptr(self, idx), num_bytes(self, count));
    return NULL;
}

scres_err_t *dyn_ary_get(
    const dyn_ary_t *self,
    size_t idx,
    uint8_t *out_buf
) {
    return dyn_ary_get_many(self, idx, 1, out_buf);
}

scres_err_t *dyn_ary_set_many(
    dyn_ary_t *self,
    size_t idx,
    size_t count,
    const uint8_t *in_buf,
    bool retrieve_old_val,
    uint8_t *old_val_buf
) {
    if(idx + count > self->count)
        SCRES_ERR_RETURN(&SCRES_ERR_TYPE_DOMAIN, __FILE__, __func__, __LINE__);
    if(retrieve_old_val)
        memcpy(old_val_buf, idx_to_byte_ptr(self, idx), num_bytes(self, count));
    memcpy(idx_to_byte_ptr(self, idx), in_buf, num_bytes(self, count));
    return NULL;
}

scres_err_t *dyn_ary_set(
    dyn_ary_t *self,
    size_t idx,
    const uint8_t *in_buf,
    bool retrieve_old_val,
    uint8_t *old_val_buf
) {
    return dyn_ary_set_many(self, idx, 1, in_buf, retrieve_old_val, old_val_buf);
}

scres_err_t *dyn_ary_remove_many(
    dyn_ary_t *self,
    size_t idx,
    size_t count,
    bool retrieve_old_vals,
    const uint8_t *old_vals_buf
) {
    if(idx + count > self->count)
        SCRES_ERR_RETURN(&SCRES_ERR_TYPE_DOMAIN, __FILE__, __func__, __LINE__);
    if(retrieve_old_vals)
        memcpy(old_vals_buf, idx_to_byte_ptr(self, idx), num_bytes(self, count));
    if(idx + count < self->count) {
        // need to move elements from the end
        size_t from_pos = idx + count;
        size_t num_elems = self->count - from_pos;
        memmove(
            idx_to_byte_ptr(self, idx),
            idx_to_byte_ptr(self, from_pos),
            num_bytes(self, num_elems)
        );
    }
    self->count -= count;
    if(should_shrink(self->count, self->cap))
    {
        // shrink the memory
        size_t new_cap = shrink_cap(self->count, self->cap);
        uint8_t *new_buf;
        if(!(new_buf = realloc(self->data_buf, num_bytes(self, new_cap))))
            SCRES_ERR_RETURN(&SCRES_ERR_TYPE_ALLOC_FAILED, __FILE__, __func__, __LINE__);
        self->data_buf = new_buf;
        self->cap = new_cap;
    }
    return NULL;
}

scres_err_t *dyn_ary_remove(
    dyn_ary_t *self,
    size_t idx,
    bool retrieve_old_val,
    const uint8_t *old_val_buf
) {
    return dyn_ary_remove_many(self, idx, 1, retrieve_old_val, old_val_buf);
}

scres_err_t *dyn_ary_pop(
    dyn_ary_t *self,
    bool retrieve_old_val,
    const uint8_t *old_val_buf
) {
    return dyn_ary_remove(self, self->count - 1, retrieve_old_val, old_val_buf);
}

scres_err_t *dyn_ary_pop_front(
    dyn_ary_t *self,
    bool retrieve_old_val,
    const uint8_t *old_val_buf
) {
    return dyn_ary_remove(self, 0, retrieve_old_val, old_val_buf);
}

scres_err_t *dyn_ary_clear(dyn_ary_t *ary_to_clear) {
    free(ary_to_clear->data_buf);
}

size_t dyn_ary_best_cap_exp(size_t count) {
    size_t cap_exp = 0;
    size_t cap = 1;
    while(count > cap) {
        cap_exp += 1;
        cap <<= 1;
    }
    return cap_exp;
}