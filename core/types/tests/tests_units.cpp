#include "gtest/gtest.h"
#include "types/units.h"

TEST(Units, RadToDeg) {
  Radians r = {.rad = 3.14159265358979};
  EXPECT_NEAR(rad_to_deg(r).deg, 180.0, 1.0e-10);
}

TEST(Units, DegToRad) {
  Degrees d = {.deg = 180};
  EXPECT_NEAR(deg_to_rad(d).rad, 3.14159265358979, 1.0e-10);
}

TEST(Units, CosRad) {
  Radians r = {.rad = 3.14159265358979};
  EXPECT_NEAR(cos_rad(r), -1, 1.0e-10);
  r.rad = 0;
  EXPECT_NEAR(cos_rad(r), 1, 1.0e-10);
}

TEST(Units, SinRad) {
  Radians r = {.rad = 3.14159265358979};
  EXPECT_NEAR(sin_rad(r), 0, 1.0e-10);
  r.rad = 0;
  EXPECT_NEAR(sin_rad(r), 0, 1.0e-10);
}