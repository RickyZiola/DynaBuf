#pragma once

#include <stdint.h>
#include <stdio.h>

typedef enum {
    ERR_OK,
    ERR_INSUFFICIENT_MEM,
    ERR_FAILED_WRITE
} DynabufErr;

#define decodeErr(err) ({                                          \
    char *out;                                                     \
    switch ((DynabufErr)(err)) {                                 \
        case (ERR_OK): out = "ERR_OK";                             \
            break;                                                 \
        case (ERR_INSUFFICIENT_MEM): out = "ERR_INSUFFICIENT_MEM"; \
            break;                                                 \
        case (ERR_FAILED_WRITE): out = "ERR_FAILED_WRITE";         \
            break;                                                 \
        default:                                                   \
            out = "ERR_UNKNOWN";                                   \
    } out; })

#define printErr(err) printf("%s\n", decodeErr(err));