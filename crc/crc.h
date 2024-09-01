// CRC public header
#ifndef CRC_H
#define CRC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "crc_types.h"
#include <stddef.h>
#include <stdint.h>

#ifndef __cplusplus
void
crc_init(crc_ctx_t ctx[static 1]);
#else
void
crc_init(crc_ctx_t* ctx);
#endif // __cplusplus

#ifndef __cplusplus
void
crc_update(crc_ctx_t ctx[static 1],
           const uint8_t data[static 1],
           size_t length);
#else
void
crc_update(crc_ctx_t* ctx, const uint8_t* data, size_t length);
#endif // __cplusplus

#ifndef __cplusplus
void
crc_finalize(crc_ctx_t ctx[static 1]);
#else
void
crc_finalize(crc_ctx_t* ctx);
#endif // __cplusplus

#ifdef __cplusplus
}
#endif

#endif // CRC_H
