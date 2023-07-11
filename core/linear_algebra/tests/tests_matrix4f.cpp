#include "gtest/gtest.h"
#include "linear_algebra/matrix4f.h"

TEST(Matrix4f, SetToZero) {
  Mat4f mat;
  // Initialize to non zero
  for (int i = 0; i < MATRIX4F_SIZE; i++) {
    mat.mat[i] = 100;
  }
  mat4f_set_to_zero(&mat);
  for (int i = 0; i < MATRIX4F_SIZE; i++) {
    EXPECT_EQ(mat.mat[i], 0);
  }
}

TEST(Matrix4f, SetToIdentity) {
  Mat4f mat;
  // Initialize to non zero
  for (int i = 0; i < MATRIX4F_SIZE; i++) {
    mat.mat[i] = 100;
  }
  mat4f_set_to_identity(&mat);
  float true_mat[] = {
      1.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f
  };
  for (int i = 0; i < MATRIX4F_SIZE; i++) {
    EXPECT_EQ(mat.mat[i], true_mat[i]);
  }
}

TEST(Matrix4f, At) {
  Mat4f mat;
  mat4f_set_to_identity(&mat);
  EXPECT_EQ(mat4f_at(&mat, 0, 0), 1.0f);
  EXPECT_EQ(mat4f_at(&mat, 1, 1), 1.0f);
  EXPECT_EQ(mat4f_at(&mat, 2, 2), 1.0f);
  EXPECT_EQ(mat4f_at(&mat, 3, 3), 1.0f);
  EXPECT_EQ(mat4f_at(&mat, 0, 3), 0.0f);
  EXPECT_EQ(mat4f_at(&mat, 3, 0), 0.0f);
}

TEST(Matrix4f, MultiplyMat4f) {
  Mat4f mat = (Mat4f){.mat =
      {
          1, 2, 3, 4,
          5, 6, 7, 8,
          9, 10, 11, 12,
          13, 14, 15, 16
      }};

  Mat4f result = mat4f_multiply_mat4f(&mat, &mat);

  float true_result[] = {
      90, 100, 110, 120,
      202, 228, 254, 280,
      314, 356, 398, 440,
      426, 484, 542, 600,
  };
  for (int i = 0; i < MATRIX4F_SIZE; i++) {
    EXPECT_EQ(result.mat[i], true_result[i]);
  }
}

TEST(Matrix4f, MultiplyVec4f) {
  Mat4f mat = {.mat = {
      0.0357116785741896f, 0.757740130578333f, 0.171186687811562f, 0.0461713906311539f,
      0.849129305868777f, 0.743132468124916f, 0.706046088019609f, 0.0971317812358475f,
      0.933993247757551f, 0.392227019534168f, 0.0318328463774207f, 0.823457828327293f,
      0.678735154857774f, 0.655477890177557f, 0.276922984960890f, 0.694828622975817f
  }};
  Vec4f vec = {
      .x = 0.317099480060861f,
      .y = 0.950222048838355f,
      .z = 0.0344460805029088f,
      .w = 0.438744359656398f
  };
  Vec4f result = mat4f_multiply_vec4f(&mat, &vec);

  Vec4f true_result = {
      .x = 0.757499681719457f,
      .y = 1.04233585936268f,
      .z = 1.03125552973825f,
      .w = 1.15246715916872f,
  };

  EXPECT_NEAR(result.x, true_result.x, 1.0e-6f);
  EXPECT_NEAR(result.y, true_result.y, 1.0e-6f);
  EXPECT_NEAR(result.z, true_result.z, 1.0e-6f);
  EXPECT_NEAR(result.w, true_result.w, 1.0e-6f);
}

TEST(Matrix4f, Inverse) {

  Mat4f mat = { .mat = {
      0.814723686393179, 0.632359246225410, 0.957506835434298, 0.957166948242946,
      0.905791937075619, 0.0975404049994095, 0.964888535199277, 0.485375648722841,
      0.126986816293506, 0.278498218867048, 0.157613081677548, 0.800280468888800,
      0.913375856139019, 0.546881519204984, 0.970592781760616, 0.141886338627215}};

  float true_result[16] = {
      -15.2996959547194, 3.07606079612646, 14.7234544997318, 9.64451704177082,
      -0.208808422147492, -1.84423560805176, 1.03655271219096, 1.87106586073514,
      14.5693682655858, -1.93373020704230, -14.6497282774008, -9.04132705361370,
      -0.369008852162959, 0.534535526584963, 1.43777858938291, -0.400838976479567};

  Mat4f inverse = mat4f_inverse(&mat);
  for (int i = 0; i < MATRIX4F_SIZE; i++) {
    EXPECT_NEAR(inverse.mat[i], true_result[i], 1.0e-4) << i;
  }
}