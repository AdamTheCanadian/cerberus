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

static inline float determinant3(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
  return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
}

Mat4f mat4f_inverse(Mat4f const *mat) {
  
  const float det =
      mat->mat[0] * determinant3(mat->mat[5], mat->mat[6], mat->mat[7], mat->mat[9], mat->mat[10], mat->mat[11], mat->mat[13], mat->mat[14], mat->mat[15]) -
      mat->mat[1] * determinant3(mat->mat[4], mat->mat[6], mat->mat[7], mat->mat[8], mat->mat[10], mat->mat[11], mat->mat[12], mat->mat[14], mat->mat[15]) +
      mat->mat[2] * determinant3(mat->mat[4], mat->mat[5], mat->mat[7], mat->mat[8], mat->mat[9], mat->mat[11], mat->mat[12], mat->mat[13], mat->mat[15]) -
      mat->mat[3] * determinant3(mat->mat[4], mat->mat[5], mat->mat[6], mat->mat[8], mat->mat[9], mat->mat[10], mat->mat[12], mat->mat[13], mat->mat[14]);
  const float det_inv = 1.0f / det;

  Mat4f temp;
  temp.mat[0] = det_inv * determinant3(mat->mat[5], mat->mat[6], mat->mat[7], mat->mat[9], mat->mat[10], mat->mat[11], mat->mat[13], mat->mat[14], mat->mat[15]);
  temp.mat[1] = det_inv * -determinant3(mat->mat[1], mat->mat[2], mat->mat[3], mat->mat[9], mat->mat[10], mat->mat[11], mat->mat[13], mat->mat[14], mat->mat[15]);
  temp.mat[2] = det_inv * determinant3(mat->mat[1], mat->mat[2], mat->mat[3], mat->mat[5], mat->mat[6], mat->mat[7], mat->mat[13], mat->mat[14], mat->mat[15]);
  temp.mat[3] = det_inv * -determinant3(mat->mat[1], mat->mat[2], mat->mat[3], mat->mat[5], mat->mat[6], mat->mat[7], mat->mat[9], mat->mat[10], mat->mat[11]);

  temp.mat[4] = det_inv * -determinant3(mat->mat[4], mat->mat[6], mat->mat[7], mat->mat[8], mat->mat[10], mat->mat[11], mat->mat[12], mat->mat[14], mat->mat[15]);
  temp.mat[5] = det_inv * determinant3(mat->mat[0], mat->mat[2], mat->mat[3], mat->mat[8], mat->mat[10], mat->mat[11], mat->mat[12], mat->mat[14], mat->mat[15]);
  temp.mat[6] = det_inv * -determinant3(mat->mat[0], mat->mat[2], mat->mat[3], mat->mat[4], mat->mat[6], mat->mat[7], mat->mat[12], mat->mat[14], mat->mat[15]);
  temp.mat[7] = det_inv * determinant3(mat->mat[0], mat->mat[2], mat->mat[3], mat->mat[4], mat->mat[6], mat->mat[7], mat->mat[8], mat->mat[10], mat->mat[11]);

  temp.mat[8] = det_inv * determinant3(mat->mat[4], mat->mat[5], mat->mat[7], mat->mat[8], mat->mat[9], mat->mat[11], mat->mat[12], mat->mat[13], mat->mat[15]);
  temp.mat[9] = det_inv * -determinant3(mat->mat[0], mat->mat[1], mat->mat[3], mat->mat[8], mat->mat[9], mat->mat[11], mat->mat[12], mat->mat[13], mat->mat[15]);
  temp.mat[10] = det_inv * determinant3(mat->mat[0], mat->mat[1], mat->mat[3], mat->mat[4], mat->mat[5], mat->mat[7], mat->mat[12], mat->mat[13], mat->mat[15]);
  temp.mat[11] = det_inv * -determinant3(mat->mat[0], mat->mat[1], mat->mat[3], mat->mat[4], mat->mat[5], mat->mat[7], mat->mat[8], mat->mat[9], mat->mat[11]);

  temp.mat[12] = det_inv * -determinant3(mat->mat[4], mat->mat[5], mat->mat[6], mat->mat[8], mat->mat[9], mat->mat[10], mat->mat[12], mat->mat[13], mat->mat[14]);
  temp.mat[13] = det_inv * determinant3(mat->mat[0], mat->mat[1], mat->mat[2], mat->mat[8], mat->mat[9], mat->mat[10], mat->mat[12], mat->mat[13], mat->mat[14]);
  temp.mat[14] = det_inv * -determinant3(mat->mat[0], mat->mat[1], mat->mat[2], mat->mat[4], mat->mat[5], mat->mat[6], mat->mat[12], mat->mat[13], mat->mat[14]);
  temp.mat[15] = det_inv * determinant3(mat->mat[0], mat->mat[1], mat->mat[2], mat->mat[4], mat->mat[5], mat->mat[6], mat->mat[8], mat->mat[9], mat->mat[10]);

  return temp;
}