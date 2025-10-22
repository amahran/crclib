#include <stdio.h>
#include <stdlib.h>

#include "crc.h"

static void wd_trigger(void)
{
    // function to check and trigger watchdog if needed
}

int main(void)
{
    // example usage
    u8 data[4] = {0x31U, 0x32U, 0x33U, 0x34U};
    Crc_Ctx crc_ctx = {.cyclic_fn = wd_trigger,
                       .params = {.init_val = CRC_INITIAL_VALUE32,
                                  .polynomial = CRC_POLYNOMIAL_32_REFLECT,
                                  .final_xor = CRC_FINAL_XOR_CRC32}};

    crc_init(&crc_ctx);
    crc_update(&crc_ctx, data, sizeof(data));
    crc_finalize(&crc_ctx);

    printf("CRC value = 0x%X\n", crc_ctx.crc);

    return EXIT_SUCCESS;
}
