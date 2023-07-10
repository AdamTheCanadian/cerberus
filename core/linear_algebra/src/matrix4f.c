#include "linear_algebra/matrix4f.h"

/* Matrix layout for row major ordering
 * Just a helper comment to remember the indices of a 4x4 matrix
 *
 *  0  1  2  3
 *  4  5  6  7
 *  8  9 10 11
 * 12 13 14 15
 */

void mat4f_set_to_zero(Mat4f *mat) {
  for (int i = 0; i < MATRIX4F_SIZE; i++) {
    mat->mat[i] = 0.0f;
  }
}

void mat4f_set_to_identity(Mat4f* mat) {
  mat4f_set_to_zero(mat);
  mat->mat[0] = 1.0f;
  mat->mat[5] = 1.0f;
  mat->mat[10] = 1.0f;
  mat->mat[15] = 1.0f;
}

Mat4f mat4f_multiply_mat4f(const Mat4f *mat1,
                           const Mat4f *mat2) {
  Mat4f result = {0};
  for (int i = 0; i < 4; i++) {
    for (int k = 0; k < 4; k++) {
      for (int j = 0; j < 4; j++) {
        result.mat[i * 4 + j] += mat1->mat[i * 4 + k] * mat2->mat[k * 4 + j];
      }
    }
  }
  return result;
}


Vec4f mat4f_multiply_vec4f(const Mat4f *mat,
                           const Vec4f *vec) {
  Vec4f result = {0};
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      result.vec[i] += mat4f_at(mat, i, j) * vec->vec[j];
    }
  }
  return result;
}
