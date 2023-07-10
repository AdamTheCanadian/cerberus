#ifndef CERBERUS_TOP_CORE_LINEAR_ALGEBRA_INCLUDE_LINEAR_ALGEBRA_MATRIX4F_H_
#define CERBERUS_TOP_CORE_LINEAR_ALGEBRA_INCLUDE_LINEAR_ALGEBRA_MATRIX4F_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "linear_algebra/vector4f.h"

#define MATRIX4F_SIZE 16

typedef struct {
  float mat[MATRIX4F_SIZE];
} Mat4f;

void mat4f_set_to_zero(Mat4f *mat);

void mat4f_set_to_identity(Mat4f* mat);

Mat4f mat4f_multiply_mat4f(const Mat4f *mat1,
                          const Mat4f *mat2);

Vec4f mat4f_multiply_vec4f(const Mat4f *mat,
                          const Vec4f *vec);

static inline float mat4f_at(const Mat4f *mat,
                             int i,
                             int j) {
  return mat->mat[i * 4 + j];
}

static inline void mat4f_set(Mat4f *mat,
                             int i,
                             int j,
                             float value) {
  mat->mat[i * 4 + j] = value;
}

#ifdef __cplusplus
}
#endif
#endif
