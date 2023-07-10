#ifndef CERBERUS_TOP_CORE_LINEAR_ALGEBRA_INCLUDE_LINEAR_ALGEBRA_VECTOR4F_H_
#define CERBERUS_TOP_CORE_LINEAR_ALGEBRA_INCLUDE_LINEAR_ALGEBRA_VECTOR4F_H_
#ifdef __cplusplus
extern "C" {
#endif

typedef union {
  struct {
    float x;
    float y;
    float z;
    float w;
  };
  float vec[4];
} Vec4f;

#ifdef __cplusplus
}
#endif
#endif
