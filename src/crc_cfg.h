// Compile time configuration for crclib
#ifndef CRC_CFG_H_
#define CRC_CFG_H_

#ifdef __cplusplus
extern "C" {
#endif

// CRC32 polynomial
#ifndef CRC_INITIAL_VALUE32
#define CRC_INITIAL_VALUE32 (0xffffffffUL)
#endif

#ifndef CRC_POLYNOMIAL_32
#define CRC_POLYNOMIAL_32 (0x04c11db7UL)
#endif

#ifndef CRC_POLYNOMIAL_32_REFLECT
#define CRC_POLYNOMIAL_32_REFLECT (0xedb88320UL)
#endif

#ifndef CRC_FINAL_XOR_CRC32
#define CRC_FINAL_XOR_CRC32 (0xffffffffUL)
#endif

// the value has to be power of 2
#ifndef CRC_CYCLIC_TRIGGER_INTERVAL
#define CRC_CYCLIC_TRIGGER_INTERVAL (0x20U)
#endif

#ifdef __cplusplus
}
#endif

#endif  // CRC_CFG_H_
