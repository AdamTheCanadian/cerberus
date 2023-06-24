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