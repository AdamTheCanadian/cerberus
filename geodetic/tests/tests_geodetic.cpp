#include "gtest/gtest.h"
#include "geodetic/geodetic.h"

TEST(Geodetic, Radii) {
  auto radii = geodetic_radii_calculate(Radians{.rad = 0.890117918520000});
  EXPECT_NEAR(radii.transverse.m, 6391069.98485808, 1.0e-8);
  EXPECT_NEAR(radii.meridian.m, 6374056.74593718, 1.0e-8);
}

TEST(Geodetic, IncrementPosition) {
  geodetic_PositionLLH pos {
    .latitude = Radians{.rad = 0.890117918520000},
    .longitude = Radians{.rad = 0},
    .height = Metres{.m = 10}
  };

  Metres e = Metres{.m = 1.2};
  Metres n = Metres{.m = -3.4};
  Metres u = Metres{.m = 5.6};

  // Test the increment that returns a new position
  geodetic_PositionLLH new_pos = geodetic_position_llh_add_enu(&pos, e, n, u);
  EXPECT_NEAR(new_pos.latitude.rad, 0.890117385108579, 1.0e-10);
  EXPECT_NEAR(new_pos.longitude.rad, 2.98356283977574e-07, 1.0e-10);
  EXPECT_NEAR(new_pos.height.m, 15.6, 1.0e-10);

  // Test the increment that modifies in place
  geodetic_position_llh_add_enu_in_place(&pos, e, n, u);
  EXPECT_NEAR(pos.latitude.rad, 0.890117385108579, 1.0e-10);
  EXPECT_NEAR(pos.longitude.rad, 2.98356283977574e-07, 1.0e-10);
  EXPECT_NEAR(pos.height.m, 15.6, 1.0e-10);
}

TEST(Geodetic, LLHToXYZ) {
  geodetic_PositionLLH pos {
      .latitude = Radians{.rad = 0.890117918520000},
      .longitude = Radians{.rad = 0},
      .height = Metres{.m = 10}
  };

  auto xyz = geodetic_position_llh_convert_to_xyz(&pos);
  EXPECT_NEAR(xyz.x.m, 4022036.95528731, 1.0e-8);
  EXPECT_NEAR(xyz.y.m, 0, 1.0e-8);
  EXPECT_NEAR(xyz.z.m, 4933552.39169670, 1.0e-8);
}

TEST(Geodetic, Gravity) {
  geodetic_PositionLLH pos {
      .latitude = Radians{.rad = 0.890117918520000},
      .longitude = Radians{.rad = 0},
      .height = Metres{.m = 10}
  };
  Vector3d g = geodetic_calculate_gravity_ned(&pos);
  EXPECT_NEAR(g.x, -7.90343261391943e-08, 1.0e-10);
  EXPECT_NEAR(g.y, 0, 1.0e-10);
  EXPECT_NEAR(g.z, 9.811560478021, 1.0e-6);
}

TEST(Geodetic, AngularRateECEF) {
  geodetic_PositionLLH pos {
      .latitude = Radians{.rad = 0.890117918520000},
      .longitude = Radians{.rad = 0},
      .height = Metres{.m = 10}
  };
  Vector3d angular_rate = geodetic_calculate_angular_rate_ecef_ned(&pos);
  EXPECT_NEAR(angular_rate.x, 4.58907666336400e-05, 1.0e-10);
  EXPECT_NEAR(angular_rate.y, 0, 1.0e-10);
  EXPECT_NEAR(angular_rate.z, -5.66703772274307e-05, 1.0e-10);
}

TEST(Geodetic, AngularRateNED) {
  geodetic_PositionLLH pos {
      .latitude = Radians{.rad = 0.890117918520000},
      .longitude = Radians{.rad = 0},
      .height = Metres{.m = 10}
  };
  geodetic_PoseLLH pose = {
      .pos = pos,
      .vel_ned = {0, 0, 0},
      .att = {.mat = {1, 0, 0,
                      0, 1, 0,
                      0, 0, 1}}
  };
  Vector3d angular_rate = geodetic_calculate_angular_rate_ned(&pose);
  EXPECT_NEAR(angular_rate.x, 0, 1.0e-10);
  EXPECT_NEAR(angular_rate.y, 0, 1.0e-10);
  EXPECT_NEAR(angular_rate.z, 0, 1.0e-10);
}