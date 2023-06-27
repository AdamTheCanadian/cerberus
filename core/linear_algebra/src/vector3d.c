#include "linear_algebra/vector3d.h"
#include <math.h>

Vector3d vec3d_subtract_vec3d(Vector3d const *vec1,
                              Vector3d const *vec2) {
  return (Vector3d){.x = vec1->x - vec2->x,
                    .y = vec1->y - vec2->y,
                    .z = vec1->z - vec2->z};
}

double vec3d_dot(Vector3d const *vec1,
                 Vector3d const *vec2) {
  return sqrt(vec1->vec[0] * vec2->vec[0] +
      vec1->vec[1] * vec2->vec[1] +
      vec1->vec[2] * vec2->vec[2]);
}