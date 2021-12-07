#ifndef ENDIAN_H
#define ENDIAN_H

#include "scres_err.h"

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

#include <inttypes.h>

typedef enum endian {
    ENDIAN_LITTLE,
    ENDIAN_BIG
} endian_t;

endian_t endian_get_host_endianness();

scres_err_t *endian_atoas(endian_t in_end, uint16_t in, endian_t out_end, uint16_t *out);
scres_err_t *endian_atoal(endian_t in_end, uint32_t in, endian_t out_end, uint32_t *out);
scres_err_t *endian_atoall(endian_t in_end, uint64_t in, endian_t out_end, uint64_t *out);

scres_err_t *endian_atohs(uint64_t in, endian_t target_endianness, uint64_t *out);
scres_err_t *endian_atohl(uint64_t in, endian_t target_endianness, uint64_t *out);
scres_err_t *endian_atohll(uint64_t in, endian_t target_endianness, uint64_t *out);

scres_err_t *endian_htoas(uint64_t in, endian_t target_endianness, uint64_t *out);
scres_err_t *endian_htoal(uint64_t in, endian_t target_endianness, uint64_t *out);
scres_err_t *endian_htoall(uint64_t in, endian_t target_endianness, uint64_t *out);



scres_err_t *endian_btohs(uint64_t in, endian_t target_endianness, uint64_t *out);
scres_err_t *endian_btohl(uint64_t in, endian_t target_endianness, uint64_t *out);
scres_err_t *endian_btohll(uint64_t in, endian_t target_endianness, uint64_t *out);
scres_err_t *endian_ltohs(uint64_t in, endian_t target_endianness, uint64_t *out);
scres_err_t *endian_ltohl(uint64_t in, endian_t target_endianness, uint64_t *out);
scres_err_t *endian_ltohll(uint64_t in, endian_t target_endianness, uint64_t *out);

scres_err_t *endian_htobs(uint64_t in, endian_t target_endianness, uint64_t *out);
scres_err_t *endian_htobl(uint64_t in, endian_t target_endianness, uint64_t *out);
scres_err_t *endian_htobll(uint64_t in, endian_t target_endianness, uint64_t *out);
scres_err_t *endian_htols(uint64_t in, endian_t target_endianness, uint64_t *out);
scres_err_t *endian_htoll(uint64_t in, endian_t target_endianness, uint64_t *out);
scres_err_t *endian_htolll(uint64_t in, endian_t target_endianness, uint64_t *out);

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

#endif // #ifndef ENDIAN_H