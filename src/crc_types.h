// CRC lib types
#ifndef CRC_TYPES_H_
#define CRC_TYPES_H_

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CRC_TABLE_SIZE 256U

// CRC-32
typedef u32 Crc_t;
typedef void (*Crc_CyclicFn)(void);

typedef struct {
    Crc_t init_val;
    Crc_t polynomial;
    Crc_t final_xor;
} Crc_Params;

typedef struct {
    // public
    Crc_t crc;
    Crc_CyclicFn cyclic_fn;
    Crc_Params params;
    // private
    Crc_t _crc_table[CRC_TABLE_SIZE];
} Crc_Ctx;

#define CRC_CYCLIC_TRIGGER(function, cycle)                      \
    if (NULL != (function) &&                                    \
        (((cycle) & (CRC_CYCLIC_TRIGGER_INTERVAL - 1u)) == 0)) { \
        (function)();                                            \
    }

#ifdef __cplusplus
}
#endif

#endif  // CRC_TYPES_H_
