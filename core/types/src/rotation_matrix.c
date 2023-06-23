#include "types/rotation_matrix.h"

Rotation3d rotation_x(Radians x) {
  const double c = cos_rad(x);
  const double s = sin_rad(x);
  const Rotation3d r = {
      .mat = {
          1, 0, 0,
          0, c, s,
          0, -s, c}};
  return r;
}