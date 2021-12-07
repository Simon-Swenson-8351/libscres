#ifndef SC_TBL_H
#define SC_TBL_H

#include "scres_err.h"
#include "dyn_ary.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

typedef dyn_ary_t sc_tbl_t;

scres_err_t *sc_tbl_init_from_file(char *filename, sc_tbl_t *tbl);
scres_err_t *sc_tbl_init_from_buf(uint8_t *buf, size_t buf_size, sc_tbl_t *tbl);

// TODO write routines

scres_err_t *sc_tbl_clear(sc_tbl_t *tbl);

#ifdef __cplusplus
}
#endif

#endif // #ifndef TBL_H