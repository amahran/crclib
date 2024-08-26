// CRC lib types
#ifndef CRC_TYPES_H
#define CRC_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "crc_cfg.h"
#include <stdint.h>

typedef uint32_t crc_t;
typedef void (*crc_cyclicfn_t)(void);

typedef struct
{
  crc_t init_val;
  crc_t polynomial;
  crc_t final_xor;
} crc_param_t;

typedef struct
{
  crc_t crc;
  crc_param_t params;
  crc_cyclicfn_t cyclicfn;
} crc_ctx_t;

#define CRC_CYCLIC_TRIGGER(function, cycle)                                    \
  if (NULL != (function) &&                                                    \
      (((cycle) & (CRC_CYCLIC_TRIGGER_INTERVAL - 1u)) == 0)) {                 \
    (function)();                                                              \
  }

#ifdef __cplusplus
}
#endif

#endif // CRC_TYPES_H
