#include "scres_err.h"

#include <stdio.h>
#include <inttypes.h>

const char *const SCRES_ERR_LVL_STRS[SCRES_ERR_LVL_COUNT] = {
    "warning",
    "error"
};

const scres_err_type_t SCRES_ERR_TYPE_ALLOC_FAILED = {
    .code = 1,
    .level = SCRES_ERR_LVL_ERR,
    .type_name = "SCRES_ERR_TYPE_ALLOC_FAILED"
};
    SCRES_ERR_TYPE_INIT(1, SCRES_ERR_LVL_ERR, "memory allocation failed");
const scres_err_type_t SCRES_ERR_TYPE_DOMAIN = 
    SCRES_ERR_TYPE_INIT(2, SCRES_ERR_LVL_ERR, "input outside of function domain");
const scres_err_type_t SCRES_ERR_TYPE_FILE_FORMAT_WRONG = 
    SCRES_ERR_TYPE_INIT(3, SCRES_ERR_LVL_ERR, "file format different from expected");
const scres_err_type_t SCRES_ERR_TYPE_FILE_IO_ERR = 
    SCRES_ERR_TYPE_INIT(4, SCRES_ERR_LVL_ERR, "file I/O error");
const scres_err_type_t SCRES_ERR_TYPE_MISMATCHED_BUFFER_SIZES =
    SCRES_ERR_TYPE_INIT(5, SCRES_ERR_LVL_ERR, "multiple buffers have "
    "mismatched sizes and must be the same size");

void scres_err_set_str(scres_err_t *self) {
    // Desired string:
    // 
    // <level str>: "<friendly_name>" (<code>) in <filename>::<function>::<line>
    snprintf(
        self->str,
        SCRES_ERR_STR_LEN,
        "%s: \"%s\" (%"PRIu32") in %s::%s::%d",
        SCRES_ERR_LVL_STRS[self->type->level],
        self->type->friendly_name,
        self->type->code,
        self->file,
        self->function,
        self->line
    );
}