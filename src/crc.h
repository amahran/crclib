// CRC public header
#ifndef CRC_H
#define CRC_H

#include <stddef.h>
#include <stdint.h>

#include "crc_cfg.h"
#include "crc_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __cplusplus
void crc_init(struct crc_ctx ctx[static 1]);
#else
void crc_init(struct crc_ctx* ctx);
#endif  // __cplusplus

#ifndef __cplusplus
void crc_update(struct crc_ctx ctx[static 1], const uint8_t data[static 1],
                size_t length);
#else
void crc_update(struct crc_ctx* ctx, const uint8_t* data, size_t length);
#endif  // __cplusplus

#ifndef __cplusplus
void crc_finalize(struct crc_ctx ctx[static 1]);
#else
void crc_finalize(struct crc_ctx* ctx);
#endif  // __cplusplus

#ifdef __cplusplus
}
#endif

#endif  // CRC_H
