/* stdint.h
 * Standard integer datatypes - system independent */

#ifndef stdint_h
#define stdint_h

typedef signed char          int8_t;
typedef unsigned char        uint8_t;
typedef short                int16_t;
typedef unsigned short       uint16_t;
typedef int                  int32_t;
typedef unsigned             uint32_t;
typedef long long            int64_t;
typedef unsigned long long   uint64_t;

/* 7.18.1.4  Integer types capable of holding object pointers */
typedef int intptr_t;
typedef unsigned uintptr_t;

#endif