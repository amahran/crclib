// Compile time configuration for crclib
#ifndef CRC_CFG_H
#define CRC_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

// CRC32 polynomial
#define CRC_INITIAL_VALUE32 (0xFFFFFFFFUL)
#define CRC_POLYNOMIAL_32 (0x04C11DB7UL)
#define CRC_POLYNOMIAL_32_REFLECT (0xEDB88320UL)
#define CRC_FINAL_XOR_CRC32 (0xFFFFFFFFUL)

// the value has to be power of 2
#define CRC_CYCLIC_TRIGGER_INTERVAL (0x20U)

#ifdef __cplusplus
}
#endif

#endif  // CRC_CFG_H
