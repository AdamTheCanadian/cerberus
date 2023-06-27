#ifndef CERBERUS_TOP_CORE_LINEAR_ALGEBRA_INCLUDE_LINEAR_ALGEBRA_MATRIX3D_H_
#define CERBERUS_TOP_CORE_LINEAR_ALGEBRA_INCLUDE_LINEAR_ALGEBRA_MATRIX3D_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "linear_algebra/vector3d.h"

typedef struct {
  double mat[9];
} Matrix3d;

Matrix3d mat3d_multiply_mat3d(Matrix3d const *mat1,
                              Matrix3d const *mat2);

Matrix3d mat3d_transpose(Matrix3d const *mat1);

Matrix3d mat3d_identity();

/**
 * \return mat * s
 */
Matrix3d mat3d_scale(Matrix3d const *mat,
                     double s);

/**
 * \return mat1 - mat2
 */
Matrix3d mat3d_subtract(Matrix3d const *mat1,
                        Matrix3d const *mat2);

/**
 * Helper to work with 2D indices
 * \return mat[i, j]
 */
static inline double mat3d_at(Matrix3d const *mat,
                              int i,
                              int j) {
  return mat->mat[i * 3 + j];
}

double mat3d_trace(Matrix3d const *mat);

/**
 * \return mat * vec
 */
Vector3d mat3d_multiply_vec3d(Matrix3d const *mat,
                              Vector3d const *vec);

Matrix3d mat3d_inverse(Matrix3d const *mat);

double mat3d_determinant(Matrix3d const *mat);

#ifdef __cplusplus
}
#endif
#endif
