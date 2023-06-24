#include "gtest/gtest.h"
#include "linear_algebra/matrix3d.h"

TEST(Matrix3d, MultiplyMat3d) {
  Matrix3d mat1 = {.mat = {
      0.417022004702574, 0.302332572631840, 0.186260211377671,
      0.720324493442158, 0.146755890817113, 0.345560727043048,
      0.000114374817344887, 0.0923385947687978, 0.396767474230670}};
  Matrix3d mat2 = {.mat = {
      0.538816734003357, 0.204452249731517, 0.670467510178402,
      0.419194514403295, 0.878117436390945, 0.417304802367127,
      0.685219500396760, 0.0273875931979262, 0.558689828445752}};

  double true_result[9] = {
      0.479063719538079, 0.355845809564111, 0.509826225194676,
      0.686427104107207, 0.285604946457992, 0.737257370961599,
      0.310642269926347, 0.0919740204854361, 0.260279975750651};

  Matrix3d r = mat3d_multiply_mat3d(&mat1, &mat2);
  for (int i = 0; i < 9; i++) {
    EXPECT_NEAR(r.mat[i], true_result[i], 1.0e-10);
  }
}

TEST(Matrix3d, Transpose) {
  Matrix3d mat = {.mat = {
      1, 2, 3,
      4, 5, 6,
      7, 8, 9}};

  double true_result[9] = {
      1, 4, 7,
      2, 5, 8,
      3, 6, 9};

  Matrix3d T = mat3d_transpose(&mat);
  for (int i = 0; i < 9; i++) {
    EXPECT_NEAR(T.mat[i], true_result[i], 1.0e-10);
  }
}

TEST(Matrix3d, Idenity) {

  double true_result[9] = {
      1, 0, 0,
      0, 1, 0,
      0, 0, 1};

  Matrix3d I = mat3d_identity();
  for (int i = 0; i < 9; i++) {
    EXPECT_NEAR(I.mat[i], true_result[i], 1.0e-10);
  }
}

TEST(Matrix3d, Scale) {

  double true_result[9] = {
      2, 0, 0,
      0, 2, 0,
      0, 0, 2};

  Matrix3d I = mat3d_identity();
  Matrix3d r = mat3d_scale(&I, 2);
  for (int i = 0; i < 9; i++) {
    EXPECT_NEAR(r.mat[i], true_result[i], 1.0e-10);
  }
}