#ifndef UTIL_H
#define UTIL_H

#include "scres_err.h"

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

#include <inttypes.h>

// allocates a new buffer with the file contents and assigns it to *buf
scres_err_t *util_file_to_buf(char *filename, uint8_t **buf, size_t *buf_size);

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

#endif // #ifndef UTIL_H