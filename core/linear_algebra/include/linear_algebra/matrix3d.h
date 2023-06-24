#ifndef CERBERUS_TOP_CORE_LINEAR_ALGEBRA_INCLUDE_LINEAR_ALGEBRA_MATRIX3D_H_
#define CERBERUS_TOP_CORE_LINEAR_ALGEBRA_INCLUDE_LINEAR_ALGEBRA_MATRIX3D_H_
#ifdef __cplusplus
extern "C" {
#endif

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
#ifdef __cplusplus
}
#endif
#endif
