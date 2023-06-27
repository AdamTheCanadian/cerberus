#ifndef CERBERUS_TOP_CORE_TYPES_INCLUDE_TYPES_ORIENTATION_CONVERSIONS_H_
#define CERBERUS_TOP_CORE_TYPES_INCLUDE_TYPES_ORIENTATION_CONVERSIONS_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "types/euler.h"
#include "types/rotation_matrix.h"
#include "linear_algebra/vector3d.h"

/**
 * Convert a set of euler angles into a 3D rotation matrix
 * \param e
 * \return
 */
Rotation3d euler_to_rotation3d(const Euler *e);

/**
 * Convert a 3D vector into a skew symmetric matrix
 */
Rotation3d skew_symmetric(Vector3d const *v);

#ifdef __cplusplus
}
#endif
#endif
