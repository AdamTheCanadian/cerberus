#include "gtest/gtest.h"
#include "types/orientation_conversions.h"

TEST(OrientationConversions, EulerToRotation) {
  Euler e = {
      .x = deg_to_rad((Degrees){.deg = -30}),
      .y = deg_to_rad((Degrees){.deg = 30}),
      .z = deg_to_rad((Degrees){.deg = 45})};

  Rotation3d rot = euler_to_rotation3d(&e);

  double true_mat[9] = {
  0.6123724357, 0.6123724357, -0.5,
  -0.789149131, 0.4355957404, -0.4330127019,
  -0.04736717275, 0.6597396084, 0.75};

  for (int i = 0; i < 9; i++) {
    EXPECT_NEAR(rot.mat[i], true_mat[i], 1.0e-10);
  }
}