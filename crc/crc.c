#include "crc.h"
#include <stddef.h>
#include <stdint.h>

#define CRC_TABLE_SIZE 256u

static crc_t g_crc_table[CRC_TABLE_SIZE];

static void
crc_gen_table(crc_ctx_t ctx[static 1]);

void
crc_init(crc_ctx_t* ctx)
{
  ctx->crc = ctx->params.init_val;
  crc_gen_table(ctx);
}

void
crc_update(crc_ctx_t* ctx, const uint8_t* data, size_t length)
{
  if ((NULL == data) || (0 == length)) {
    return;
  }

  for (size_t i = 0; i < length; i++) {
    CRC_CYCLIC_TRIGGER(ctx->cyclicfn, i);

    uint8_t pos = (ctx->crc ^ data[i]) & 0xFF;
    ctx->crc = (ctx->crc >> 8) ^ g_crc_table[pos];
  }
}

void
crc_finalize(crc_ctx_t* ctx)
{
  ctx->crc ^= (ctx->params.final_xor);
}

static void
crc_gen_table(crc_ctx_t ctx[static 1])
{
  crc_t crc;
  for (size_t i = 0; i < CRC_TABLE_SIZE; i++) {
    CRC_CYCLIC_TRIGGER(ctx->cyclicfn, i);

    crc = i;
    for (uint_fast8_t j = 0; j < 8; j++) {
      if (crc & 1) {
        crc = (crc >> 1) ^ (ctx->params.polynomial);
      } else {
        crc >>= 1;
      }
    }
    g_crc_table[i] = crc;
  }
}
