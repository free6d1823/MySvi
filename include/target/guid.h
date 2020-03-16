#ifndef __TARGET_GUID_H_INCLUDE__
#define __TARGET_GUID_H_INCLUDE__

#include <stdint.h>

/*
 128 bit buffer containing a unique identifier value.
 Unless otherwise specified, aligned on a 64 bit boundary.
*/

typedef struct {
  uint32_t  Data1;
  uint16_t  Data2;
  uint16_t  Data3;
  uint8_t   Data4[8];
} GUID;

#endif /* __TARGET_GUID_H_INCLUDE__ */
