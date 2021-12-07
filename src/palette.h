#ifndef PALETTE_H
#define PALETTE_H

#include "color.h"

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

const int PALETTE_SIZE = 256;

typedef color_t palette_t[PALETTE_SIZE];

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

#endif // #ifndef PALETTE_H