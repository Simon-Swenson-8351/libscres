#include "sc_tbl.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "util.h"

scres_err_t *sc_tbl_init_from_file(char *filename, sc_tbl_t *tbl)
{
    scres_err_t *e = NULL;
    char *ext = filename + strlen(filename) - 4;
    if(strcmp(ext, ".tbl")) {
        SCRES_ERR_SET(e, &SCRES_ERR_TYPE_FILE_FORMAT_WRONG, __FILE__, __func__, __LINE__);
        goto end;
    }
    uint8_t *buf;
    size_t buf_size;
    if(e = util_file_to_buf(filename, &buf, &buf_size) &&
        e->type->code == SCRES_ERR_TYPE_ALLOC_FAILED.code)
    {
        goto end;
    }
    e = sc_tbl_init_from_buf(buf, buf_size, tbl);
    free(buf);
end:
    return e;
}

scres_err_t *sc_tbl_init_from_buf(uint8_t *buf, size_t buf_size, sc_tbl_t *tbl)
{
    scres_err_t *e = NULL;
    size_t num_entries = (size_t)(*((uint16_t *)buf));
    if(e = dyn_ary_init(tbl, sizeof(char *), dyn_ary_best_cap_exp(num_entries))) goto end;
    uint16_t *offsets = (uint16_t *)(buf + 2);
    for(size_t i = 0; i < num_entries; i++)
    {
        char *file_str = (char *)(buf + offsets[i]);
        char *to_add;
        if(!(to_add = malloc(strlen(file_str) + 1)))
        {
            SCRES_ERR_SET(e, &SCRES_ERR_TYPE_ALLOC_FAILED, __FILE__, __func__, __LINE__);
            goto end;
        }
        memcpy(to_add, file_str, len(file_str) + 1);
        if(e = dyn_ary_append(tbl, (uint8_t *)(&to_add))) goto end;
    }
end:
    return e;
}

scres_err_t *sc_tbl_clear(sc_tbl_t *tbl)
{
    for(size_t i = 0; i < tbl->count; i++) {
        char *s;
        dyn_ary_get(tbl, i, (uint8_t *)(&s));
        free(s);
    }
    dyn_ary_clear(tbl);
    return NULL;
}