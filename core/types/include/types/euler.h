#ifndef CERBERUS_TOP_CORE_TYPES_INCLUDE_TYPES_EULER_H_
#define CERBERUS_TOP_CORE_TYPES_INCLUDE_TYPES_EULER_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "types/units.h"

typedef union {
  struct {
    Radians x;
    Radians y;
    Radians z;
  };
  Radians xyz[3];
} Euler;

#ifdef __cplusplus
}
#endif
#endif
