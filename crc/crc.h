// CRC public header
#ifndef CRC_H
#define CRC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "crc_types.h"
#include <stddef.h>
#include <stdint.h>

void
crc_init(crc_ctx_t* ctx);
void
crc_update(crc_ctx_t* ctx, const uint8_t* data, size_t length);
void
crc_finalize(crc_ctx_t* ctx);

#ifdef __cplusplus
}
#endif

#endif // CRC_H
