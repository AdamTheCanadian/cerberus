#ifndef CERBERUS_TOP_CORE_TYPES_INCLUDE_TYPES_ROTATION_MATRIX_H_
#define CERBERUS_TOP_CORE_TYPES_INCLUDE_TYPES_ROTATION_MATRIX_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "linear_algebra/matrix3d.h"
#include "types/units.h"

// The 3 indicates 3-dimensional, the d is for double
typedef Matrix3d Rotation3d;

Rotation3d rotation_x(Radians x);

#ifdef __cplusplus
}
#endif
#endif
