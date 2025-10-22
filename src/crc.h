// CRC public header
#ifndef CRC_H_
#define CRC_H_

#include <stddef.h>
#include <stdint.h>

#include "crc_cfg.h"
#include "crc_types.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void crc_init(Crc_Ctx* ctx);

void crc_update(Crc_Ctx* ctx, const u8* data, usize len);

void crc_finalize(Crc_Ctx* ctx);

#ifdef __cplusplus
}
#endif

#endif  // CRC_H_
