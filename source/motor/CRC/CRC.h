#ifndef __CRC_H_
#define __CRC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>


uint16_t CRC16(uint8_t *nData, uint16_t wLength);

#ifdef __cplusplus
}
#endif

#endif
