#ifndef CERBERUS_TOP_CORE_LINEAR_ALGEBRA_INCLUDE_LINEAR_ALGEBRA_VECTOR3D_H_
#define CERBERUS_TOP_CORE_LINEAR_ALGEBRA_INCLUDE_LINEAR_ALGEBRA_VECTOR3D_H_
#ifdef __cplusplus
extern "C" {
#endif

typedef union {
  struct {
    double x;
    double y;
    double z;
  };
  double vec[3];
} Vector3d;

Vector3d vec3d_subtract_vec3d(Vector3d const *vec1,
                              Vector3d const *vec2);

double vec3d_dot(Vector3d const *vec1,
                 Vector3d const *vec2);

#ifdef __cplusplus
}
#endif
#endif
