#include "crc.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "types.h"

#define CRC_IDX_MASK 0xFFu
#define CRC_IDX_BITS 8u

static void generate_table(Crc_Ctx *ctx);

void crc_init(Crc_Ctx *ctx)
{
    assert(NULL != ctx);
    ctx->crc = ctx->params.init_val;
    generate_table(ctx);
}

void crc_update(Crc_Ctx *ctx, const u8 *data, usize len)
{
    if (len == 0) return;
    assert((ctx != NULL) && (data != NULL));

    for (usize i = 0; i != len; ++i) {
        CRC_CYCLIC_TRIGGER(ctx->cyclic_fn, i);

        u8 pos = (ctx->crc ^ data[i]) & CRC_IDX_MASK;
        ctx->crc = (ctx->crc >> CRC_IDX_BITS) ^ ctx->_crc_table[pos];
    }
}

void crc_finalize(Crc_Ctx *ctx)
{
    assert(ctx != NULL);
    ctx->crc ^= (ctx->params.final_xor);
}

static void generate_table(Crc_Ctx *ctx)
{
    Crc_t crc;
    for (usize i = 0; i != CRC_TABLE_SIZE; ++i) {
        CRC_CYCLIC_TRIGGER(ctx->cyclic_fn, i);

        crc = (Crc_t)i;
        for (uint_fast8_t j = 0; j != CRC_IDX_BITS; ++j) {
            if (crc & 1U) {
                crc = (crc >> 1U) ^ (ctx->params.polynomial);
            } else {
                crc >>= 1U;
            }
        }
        ctx->_crc_table[i] = crc;
    }
}
