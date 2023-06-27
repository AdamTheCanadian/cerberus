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

TEST(Matrix3d, At) {
  Matrix3d mat = {{
    1, 2, 3,
    4, 5, 6,
    7, 8, 9}};

  EXPECT_EQ(mat3d_at(&mat, 0, 0), 1);
  EXPECT_EQ(mat3d_at(&mat, 1, 0), 4);
  EXPECT_EQ(mat3d_at(&mat, 2, 2), 9);
}

TEST(Matrix3d, MultiplyVec3) {
  Matrix3d mat = {{
                      1, 2, 3,
                      4, 5, 6,
                      7, 8, 9}};

  Vector3d vec = {.x = 10, .y = 11, .z = 12};

  Vector3d r = mat3d_multiply_vec3d(&mat, &vec);
  EXPECT_EQ(r.x, 68);
  EXPECT_EQ(r.y, 167);
  EXPECT_EQ(r.z, 266);
}

TEST(Matrix3d, Determinant) {
  Matrix3d mat = {.mat = {
      0.417022004702574, 0.302332572631840, 0.186260211377671,
      0.720324493442158, 0.146755890817113, 0.345560727043048,
      0.000114374817344887, 0.0923385947687978, 0.396767474230670}};

  double det = mat3d_determinant(&mat);
  EXPECT_NEAR(det, -0.0630336057475167, 1.0e-10);
}

TEST(Matrix3d, Inverse) {
  Matrix3d mat = {.mat = {
      0.417022004702574, 0.302332572631840, 0.186260211377671,
      0.720324493442158, 0.146755890817113, 0.345560727043048,
      0.000114374817344887, 0.0923385947687978, 0.396767474230670}};

  double true_inverse[9] = {
      -0.417545083664767, 1.63018954448581, -1.22378340011080,
      4.53348341818051, -2.62462320003506, 0.157672000690080,
      -1.05494466856528, 0.610351354850840, 2.48402609345886};

  Matrix3d inv = mat3d_inverse(&mat);
  for (int i = 0; i < 9; i++) {
    EXPECT_NEAR(inv.mat[i], true_inverse[i], 1.0e-10);
  }
}