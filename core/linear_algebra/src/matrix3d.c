#include "linear_algebra/matrix3d.h"

Matrix3d mat3d_multiply_mat3d(Matrix3d const *mat1,
                              Matrix3d const *mat2) {
  Matrix3d result;
  result.mat[0] = mat1->mat[0] * mat2->mat[0] + mat1->mat[1] * mat2->mat[3] + mat1->mat[2] * mat2->mat[6];
  result.mat[1] = mat1->mat[0] * mat2->mat[1] + mat1->mat[1] * mat2->mat[4] + mat1->mat[2] * mat2->mat[7];
  result.mat[2] = mat1->mat[0] * mat2->mat[2] + mat1->mat[1] * mat2->mat[5] + mat1->mat[2] * mat2->mat[8];

  result.mat[3] = mat1->mat[3] * mat2->mat[0] + mat1->mat[4] * mat2->mat[3] + mat1->mat[5] * mat2->mat[6];
  result.mat[4] = mat1->mat[3] * mat2->mat[1] + mat1->mat[4] * mat2->mat[4] + mat1->mat[5] * mat2->mat[7];
  result.mat[5] = mat1->mat[3] * mat2->mat[2] + mat1->mat[4] * mat2->mat[5] + mat1->mat[5] * mat2->mat[8];

  result.mat[6] = mat1->mat[6] * mat2->mat[0] + mat1->mat[7] * mat2->mat[3] + mat1->mat[8] * mat2->mat[6];
  result.mat[7] = mat1->mat[6] * mat2->mat[1] + mat1->mat[7] * mat2->mat[4] + mat1->mat[8] * mat2->mat[7];
  result.mat[8] = mat1->mat[6] * mat2->mat[2] + mat1->mat[7] * mat2->mat[5] + mat1->mat[8] * mat2->mat[8];

  return result;
}

Matrix3d mat3d_transpose(Matrix3d const *mat1) {
  return (Matrix3d){
      mat1->mat[0], mat1->mat[3], mat1->mat[6],
      mat1->mat[1], mat1->mat[4], mat1->mat[7],
      mat1->mat[2], mat1->mat[5], mat1->mat[8]};
}

Matrix3d mat3d_identity() {
  return (Matrix3d) {
    1, 0, 0,
    0, 1, 0,
    0, 0,1};
}

Matrix3d mat3d_scale(Matrix3d const *mat,
                     double s) {
  return (Matrix3d){
      s * mat->mat[0], s * mat->mat[1], s * mat->mat[2],
      s * mat->mat[3], s * mat->mat[4], s * mat->mat[5],
      s * mat->mat[6], s * mat->mat[7], s * mat->mat[8]};
}

Matrix3d mat3d_subtract(Matrix3d const *mat1,
                        Matrix3d const *mat2) {
  return (Matrix3d) {.mat = {
      mat1->mat[0] - mat2->mat[0], mat1->mat[1] - mat2->mat[1], mat1->mat[2] - mat2->mat[2],
      mat1->mat[3] - mat2->mat[3], mat1->mat[4] - mat2->mat[4], mat1->mat[5] - mat2->mat[5],
      mat1->mat[6] - mat2->mat[6], mat1->mat[7] - mat2->mat[7], mat1->mat[8] - mat2->mat[8]}};
}

double mat3d_trace(Matrix3d const *mat) {
  return mat->mat[0] + mat->mat[4] + mat->mat[8];
}

Vector3d mat3d_multiply_vec3d(Matrix3d const *mat,
                              Vector3d const *vec) {
  return (Vector3d) {
    .x = mat->mat[0] * vec->x + mat->mat[1] * vec->y + mat->mat[2] * vec->z,
    .y = mat->mat[3] * vec->x + mat->mat[4] * vec->y + mat->mat[5] * vec->z,
    .z = mat->mat[6] * vec->x + mat->mat[7] * vec->y + mat->mat[8] * vec->z};
}

static double determinant_2x2(double a,
                              double b,
                              double c,
                              double d) {
  return (a * d) - (b * c);
}

double mat3d_determinant(Matrix3d const *mat) {
  const double a = mat->mat[0];
  const double b = mat->mat[1];
  const double c = mat->mat[2];
  const double d = mat->mat[3];
  const double e = mat->mat[4];
  const double f = mat->mat[5];
  const double g = mat->mat[6];
  const double h = mat->mat[7];
  const double i = mat->mat[8];

  const double determinant = (a * determinant_2x2(e, f, h, i))
      - (b * determinant_2x2(d, f, g, i))
      + (c * determinant_2x2(d, e, g, h));

  return determinant;
}

Matrix3d mat3d_inverse(Matrix3d const *mat) {
  const double determinant = mat3d_determinant(mat);
  // TODO: Check determinant != 0

  // To compute inverse we are supposed to transpose the matrix, find the determinants
  // of 2x2 blocks (the cofactors), and divide the cofactors by the determinant
  // We can do (and are doing) all those in one step

  /** Helper lookup indices of original/input 3x3 matrix
   * 0 1 2
   * 3 4 5
   * 6 7 8
   * The transpose indices
   * 0 3 6
   * 1 4 7
   * 2 5 8
  */

  // Will be dividing by determinant a lot, so instead multiply by inverse
  const double det_inv = 1.0 / determinant;
  // breaking out the matrix array to shorten code lines
  const double *m = mat->mat;
  // Each section set of brackets, like this: (m[4] * m[8] - m[7] * m[5]) is the
  // 2x2 determinant of a certain block in the matrix transpose
  const Matrix3d inv = {.mat = {
      (m[4] * m[8] - m[7] * m[5]) * det_inv, -(m[1] * m[8] - m[7] * m[2]) * det_inv, (m[1] * m[5] - m[2] * m[4]) * det_inv,
      -(m[3] * m[8] - m[6] * m[5]) * det_inv, (m[0] * m[8] - m[6] * m[2]) * det_inv, -(m[0] * m[5] - m[3] * m[2]) * det_inv,
      (m[3] * m[7] - m[6] * m[4]) * det_inv, -(m[0] * m[7] - m[6] * m[1]) * det_inv, (m[0] * m[4] - m[3] * m[1]) * det_inv,
  }};
  return inv;
}