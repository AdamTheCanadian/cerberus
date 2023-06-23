#include "gtest/gtest.h"
#include "geodetic/geodetic.h"

TEST(Geodetic, Radii) {
  auto radii = geodetic_radii_calculate(Radians{.rad = 0.890117918520000});
  EXPECT_NEAR(radii.transverse.m, 6391069.98485808, 1.0e-8);
  EXPECT_NEAR(radii.meridian.m, 6374056.74593718, 1.0e-8);
}

TEST(Geodetic, IncrementPosition) {
  geodetic_Position pos {
    .latitude = Radians{.rad = 0.890117918520000},
    .longitude = Radians{.rad = 0},
    .height = Metres{.m = 10}
  };

  Metres e = Metres{.m = 1.2};
  Metres n = Metres{.m = -3.4};
  Metres u = Metres{.m = 5.6};

  // Test the increment that returns a new position
  geodetic_Position new_pos = geodetic_position_add_enu(&pos, e, n, u);
  EXPECT_NEAR(new_pos.latitude.rad, 0.890117385108579, 1.0e-10);
  EXPECT_NEAR(new_pos.longitude.rad, 2.98356283977574e-07, 1.0e-10);
  EXPECT_NEAR(new_pos.height.m, 15.6, 1.0e-10);

  // Test the increment that modifies in place
  geodetic_position_add_enu_in_place(&pos, e, n, u);
  EXPECT_NEAR(pos.latitude.rad, 0.890117385108579, 1.0e-10);
  EXPECT_NEAR(pos.longitude.rad, 2.98356283977574e-07, 1.0e-10);
  EXPECT_NEAR(pos.height.m, 15.6, 1.0e-10);
}