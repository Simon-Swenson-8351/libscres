#ifndef SC_DAT_H
#define SC_DAT_H

#include "scres_err.h"

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

#include <stddef.h>
#include <inttypes.h>

typedef struct sc_dat_field_domain_explicit {
    size_t valid_elems_count;
    uint32_t *valid_elems;
} sc_dat_field_domain_explicit_t;

typedef struct sc_dat_field_domain_range {
    uint32_t min;
    uint32_t max; // exclusive
} sc_dat_field_domain_range_t;

typedef enum sc_dat_field_domain_type {
    SC_DAT_FIELD_DOMAIN_TYPE_EXPLICIT,
    SC_DAT_FIELD_DOMAIN_TYPE_RANGE,
    SC_DAT_FIELD_DOMAIN_TYPE_ANY // any value from 0..2^(size * 8) - 1 is valid
} sc_dat_field_domain_type_t;

typedef struct sc_dat_field_domain {
    sc_dat_field_domain_type_t type;
    union {
        sc_dat_field_domain_explicit_t expl;
        sc_dat_field_domain_range_t range;
    } u;
} sc_dat_field_domain_t;

typedef struct sc_dat_field {
    size_t idx;
    size_t size;
    size_t offset_in_struct;

    char *var_name;
    char *friendly_name;
    char *descr;
} sc_dat_field_t;

typedef struct sc_dat_record_type {
    size_t start_idx;
    size_t end_idx;
    size_t num_fields;
    sc_dat_field_t *fields;
} sc_dat_record_type_t;

typedef struct sc_dat_file_layout {
    size_t num_records;
    size_t num_record_types;
    sc_dat_record_type_t *record_types;
} sc_dat_file_layout_t;

scres_err_t *sc_dat_read_record(
    uint8_t *file_buf,
    size_t file_buf_size,
    sc_dat_file_layout_t *file_layout,
    size_t record_idx,
    uint8_t *struct_buf,
    size_t struct_buf_size
);

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

#endif // #ifndef SC_DAT_H