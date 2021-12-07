#include "util.h"

#include <stdio.h>

scres_err_t *util_file_to_buf(char *filename, uint8_t **buf, size_t *buf_size) {
    scres_err_t *e = NULL;
    FILE *f;
    if(!(f = fopen(filename, "r"))) {
        SCRES_ERR_SET(e, &SCRES_ERR_TYPE_FILE_IO_ERR, __FILE__, __func__, __LINE__);
        goto end;
    }
    fseek(f, 0, SEEK_END);
    *buf_size = ftell(f);
    fseek(f, 0, SEEK_SET);
    if(!(*buf = malloc(buf_size))) {
        SCRES_ERR_SET(e, &SCRES_ERR_TYPE_ALLOC_FAILED, __FILE__, __func__, __LINE__);
        goto cleanup_file;
    }
    fread(*buf, buf_size, 1, f);
cleanup_file:
    fclose(f);
end:
    return e;
}