#include "types/orientation_conversions.h"

Rotation3d euler_to_rotation3d(const Euler *e) {
  const double cos_x = cos_rad(e->x);
  const double cos_y = cos_rad(e->y);
  const double cos_z = cos_rad(e->z);
  const double sin_x = sin_rad(e->x);
  const double sin_y = sin_rad(e->y);
  const double sin_z = sin_rad(e->z);

  return (Rotation3d) {.mat = {
      cos_y * cos_z,                          cos_y * sin_z,                         -sin_y,
      -cos_x * sin_z + sin_x * sin_y * cos_z, cos_x * cos_z + sin_x * sin_y * sin_z, sin_x * cos_y,
      sin_x * sin_z + cos_x * sin_y * cos_z, -sin_x * cos_z + cos_x * sin_y * sin_z, cos_x * cos_y}};
}

Rotation3d skew_symmetric(Vector3d const *v) {
  return (Rotation3d) {.mat = {
      0, -v->z, v->y,
      v->z, 0, -v->x,
      -v->y, v->x, 0}};
}