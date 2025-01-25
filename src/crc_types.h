// CRC lib types
#ifndef CRC_TYPES_H
#define CRC_TYPES_H

#include <stdalign.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CRC_TABLE_SIZE 256U

typedef uint32_t crc_t;
typedef void (*crc_cyclic_fn)(void);

struct crc_params {
    crc_t init_val;
    crc_t polynomial;
    crc_t final_xor;
};

struct crc_ctx {
    // public
    crc_t crc;
    crc_cyclic_fn cyclic_fn;
    struct crc_params params;
    // private
    crc_t crc_table_[CRC_TABLE_SIZE];
};

#define CRC_CYCLIC_TRIGGER(function, cycle)                      \
    if (NULL != (function) &&                                    \
        (((cycle) & (CRC_CYCLIC_TRIGGER_INTERVAL - 1u)) == 0)) { \
        (function)();                                            \
    }

#ifdef __cplusplus
}
#endif

#endif  // CRC_TYPES_H
