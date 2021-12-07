#include "endian.h"

#include <features.h>
#include <pthread.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>

#include "scres_err.h"

static void flip_bytes(
    uint8_t *buf,
    size_t buf_size
) {
    if(buf_size < 2) return;
    for(size_t i = 0; i < buf_size >> 1; i++) {
        uint8_t tmp = buf[buf_size - i - 1];
        buf[buf_size - i - 1] = buf[i];
        buf[i] = tmp;
    }
}

scres_err_t *atoabuf(
    endian_t in_end,
    uint8_t *in_buf,
    size_t in_buf_size_exp,
    endian_t out_end,
    uint8_t *out_buf,
    size_t out_buf_size_exp
) {
    if(in_buf_size_exp != out_buf_size_exp)
        SCRES_ERR_RETURN(&SCRES_ERR_TYPE_MISMATCHED_BUFFER_SIZES, __FILE__, __FUNCTION__, __LINE__);
    if(in_buf_size_exp > sizeof(size_t) * 8 - 1)
        // too many shifts
        SCRES_ERR_RETURN(&SCRES_ERR_TYPE_DOMAIN, __FILE__, __FUNCTION__, __LINE__);
    size_t buf_size = 1 << in_buf_size_exp;
    if(in_buf != out_buf) {
        if(in_end == out_end) {
            memcpy(out_buf, in_buf, buf_size);
        } else {
            for(size_t i = 0; i < buf_size; i++) {
                out_buf[i] = in_buf[buf_size - 1 - i];
            }
        }
    }
    else if(in_end != out_end)
        flip_bytes(in_buf, buf_size);
    return NULL;
}

endian_t endian_get_host_endianness() {
    static const pthread_rwlock_t ENDIAN_TEST_LOCK = PTHREAD_RWLOCK_INITIALIZER;
    static bool tested = false;
    static endian_t host_endianness;
    static const uint16_t TEST_VAL = 0x3210;
    pthread_rwlock_rdlock(&ENDIAN_TEST_LOCK);
    if(!tested) {
        pthread_rwlock_unlock(&ENDIAN_TEST_LOCK);
        pthread_rwlock_wrlock(&ENDIAN_TEST_LOCK);
        if(!tested) {
            // Double-check "tested" again in case we got preempted between 
            // the unlock and lock, and another thread acquired the lock and 
            // tested endianness.
            uint8_t *as_ary = &TEST_VAL;
            if(as_ary[0] == 0x10) {
                // first byte is low value -- little endian
                host_endianness = ENDIAN_LITTLE;
            } else {
                host_endianness = ENDIAN_BIG;
            }
            tested = true;
        }
    }
    endian_t r = host_endianness;
    pthread_rwlock_unlock(&ENDIAN_TEST_LOCK);
    return r;
}

scres_err *endian_atoas(endian_t in_end, uint16_t in, endian_t out_end, uint16_t *out);
scres_err *endian_atoal(endian_t in_end, uint32_t in, endian_t out_end, uint32_t *out);
scres_err *endian_atoall(endian_t in_end, uint64_t in, endian_t out_end, uint64_t *out);