#ifndef COLOR_H
#define COLOR_H

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

// stdint.h is a C header with no extern "C" {...} block.
#include <stdint.h>

typedef struct color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} color_t;

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

#endif // #define COLOR_H