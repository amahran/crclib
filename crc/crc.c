#include "crc.h"
#include <stddef.h>
#include <stdint.h>

#define CRC_TABLE_SIZE 256U
#define CRC_IDX_MASK 0xFFU
#define CRC_IDX_BITS 8U

/// @brief CRC 32 parameters
#define CRC32_INIT_VAL 0xFFFFFFFFUL
#define CRC32_POLYNOMIAL 0xEDB88320UL // IEEE-802.3
#define CRC32_FINAL_XOR 0xFFFFFFFFUL

#define CRC32_PARAMS_INIT()                                                    \
  (crc_param_t)                                                                \
  {                                                                            \
    .init_val = CRC32_INIT_VAL, .polynomial = CRC32_POLYNOMIAL,                \
    .final_xor = CRC32_FINAL_XOR                                               \
  }
static crc_param_t g_crc32_params;

static void
crc_gen_table(crc_ctx_t ctx[static 1]);

void
crc_init(crc_ctx_t ctx[static 1])
{
  g_crc32_params = CRC32_PARAMS_INIT();
  ctx->crc = g_crc32_params.init_val;
  crc_gen_table(ctx);
}

void
crc_update(crc_ctx_t ctx[static 1], const uint8_t data[static 1], size_t length)
{
  for (size_t i = 0; i != length; i++) {
    CRC_CYCLIC_TRIGGER(ctx->cyclicfn, i);

    uint8_t pos = (ctx->crc ^ data[i]) & CRC_IDX_MASK;
    ctx->crc = (ctx->crc >> CRC_IDX_BITS) ^ ctx->_crc_table[pos];
  }
}

void
crc_finalize(crc_ctx_t ctx[static 1])
{
  ctx->crc ^= (g_crc32_params.final_xor);
}

static void
crc_gen_table(crc_ctx_t ctx[static 1])
{
  crc_t crc;
  for (uint_fast32_t i = 0; i != CRC_TABLE_SIZE; ++i) {
    CRC_CYCLIC_TRIGGER(ctx->cyclicfn, i);

    crc = (crc_t)i;
    for (uint_fast8_t j = 0; j != CRC_IDX_BITS; ++j) {
      if (crc & 1U) {
        crc = (crc >> 1U) ^ (g_crc32_params.polynomial);
      } else {
        crc >>= 1U;
      }
    }
    ctx->_crc_table[i] = crc;
  }
}
