#ifndef CERBERUS_TOP_CORE_LINEAR_ALGEBRA_INCLUDE_LINEAR_ALGEBRA_VECTOR3F_H_
#define CERBERUS_TOP_CORE_LINEAR_ALGEBRA_INCLUDE_LINEAR_ALGEBRA_VECTOR3F_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef union {
  struct {
    float x;
    float y;
    float z;
  };
  float vec[3];
} Vec3f;

void vec3f_set_to_zero(Vec3f *vec);

bool vec3f_is_equal(Vec3f const *vec1,
                    Vec3f const *vec2);

Vec3f vec3f_subtract_vec3f(Vec3f const *vec1,
                           Vec3f const *vec2);

float vec3f_length(Vec3f const *vec);

void vec3f_normalize(Vec3f *vec);

Vec3f vec3f_cross(Vec3f const *vec1,
                  Vec3f const *vec2);

float vec3f_dot(Vec3f const *vec1,
                Vec3f const *vec2);
#ifdef __cplusplus
}
#endif
#endif
