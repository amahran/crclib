#include "crc.h"
#include <stdio.h>
#include <stdlib.h>

static void
wd_trigger(void)
{
}

int
main(void)
{
  // example usage
  crc_ctx_t crc_ctx = { .cyclicfn = wd_trigger };
  crc_init(&crc_ctx);
  uint8_t data[4] = { 0x31U, 0x32U, 0x33U, 0x34U };
  crc_update(&crc_ctx, data, sizeof(data));
  crc_finalize(&crc_ctx);

  printf("CRC value = 0x%X\n", crc_ctx.crc);

  return EXIT_SUCCESS;
}
