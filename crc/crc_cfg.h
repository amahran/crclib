// Compile time configuration for crclib
#ifndef CRC_CFG_H
#define CRC_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

// the value has to be power of 2
#define CRC_CYCLIC_TRIGGER_INTERVAL (0x20U)

#ifdef __cplusplus
}
#endif

#endif // CRC_CFG_H
