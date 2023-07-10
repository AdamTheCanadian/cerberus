#include "linear_algebra/vector3f.h"
#include <math.h>

static const float EPSILON_FLOAT = 1.0e-5f;

void vec3f_set_to_zero(Vec3f *vec) {
  vec->x = 0;
  vec->y = 0;
  vec->z = 0;
}

bool vec3f_is_equal(Vec3f const *vec1,
                    Vec3f const *vec2) {
  const float diff_x = fabsf(vec1->x - vec2->x);
  const float diff_y = fabsf(vec1->y - vec2->y);
  const float diff_z = fabsf(vec1->z - vec2->z);
  return diff_x < EPSILON_FLOAT && diff_y < EPSILON_FLOAT && diff_z < EPSILON_FLOAT;
}

Vec3f vec3f_subtract_vec3f(Vec3f const *vec1,
                           Vec3f const *vec2) {
  return (Vec3f){
      .x = vec1->x - vec2->x,
      .y = vec1->y - vec2->y,
      .z = vec1->z - vec2->z};
}

float vec3f_length(Vec3f const *vec) {
  return sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

void vec3f_normalize(Vec3f *vec) {
  float length = vec3f_length(vec);
  /* Length is 0 (or near 0), so dont do anything */
  if (length < EPSILON_FLOAT) {
    return;
  }
  vec->vec[0] /= length;
  vec->vec[1] /= length;
  vec->vec[2] /= length;
}

Vec3f vec3f_cross(Vec3f const *vec1,
                  Vec3f const *vec2) {
  return (Vec3f) {
      .x = vec1->vec[1] * vec2->vec[2] - vec1->vec[2] * vec2->vec[1],
      .y = vec1->vec[2] * vec2->vec[0] - vec1->vec[0] * vec2->vec[2],
      .z = vec1->vec[0] * vec2->vec[1] - vec1->vec[1] * vec2->vec[0]};
}

float vec3f_dot(Vec3f const *vec1,
                Vec3f const *vec2) {
  return vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z;
}