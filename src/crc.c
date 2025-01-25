#include "crc.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define CRC_IDX_MASK 0xFFU
#define CRC_IDX_BITS 8U

static void crc_generate_table(struct crc_ctx ctx[static 1]);

void crc_init(struct crc_ctx ctx[static 1]) {
    ctx->crc = ctx->params.init_val;
    crc_generate_table(ctx);
}

void crc_update(struct crc_ctx ctx[static 1], const uint8_t data[static 1],
                size_t length) {
    for (size_t i = 0; i != length; i++) {
        CRC_CYCLIC_TRIGGER(ctx->cyclic_fn, i);

        uint8_t pos = (ctx->crc ^ data[i]) & CRC_IDX_MASK;
        ctx->crc = (ctx->crc >> CRC_IDX_BITS) ^ ctx->crc_table_[pos];
    }
}

void crc_finalize(struct crc_ctx ctx[static 1]) {
    ctx->crc ^= (ctx->params.final_xor);
}

static void crc_generate_table(struct crc_ctx ctx[static 1]) {
    crc_t crc;
    for (uint_fast32_t i = 0; i != CRC_TABLE_SIZE; ++i) {
        CRC_CYCLIC_TRIGGER(ctx->cyclic_fn, i);

        crc = (crc_t)i;
        for (uint_fast8_t j = 0; j != CRC_IDX_BITS; ++j) {
            if (crc & 1U) {
                crc = (crc >> 1U) ^ (ctx->params.polynomial);
            } else {
                crc >>= 1U;
            }
        }
        ctx->crc_table_[i] = crc;
    }
}
