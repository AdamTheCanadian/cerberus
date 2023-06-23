#ifndef CERBERUS_TOP_CORE_TYPES_INCLUDE_TYPES_UNITS_H_
#define CERBERUS_TOP_CORE_TYPES_INCLUDE_TYPES_UNITS_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>

#define UNITS_DEG_TO_RAD_D 0.0174532925199433
#define UNITS_RAD_TO_DEG_D 57.2957795130823

typedef struct {
  double rad;
} Radians;

typedef struct {
  double deg;
} Degrees;

typedef struct {
  double m;
} Metres;

inline Radians deg_to_rad(Degrees d) {
  return (Radians){.rad = d.deg * UNITS_DEG_TO_RAD_D};
}

inline Degrees rad_to_deg(Radians r) {
  return (Degrees){.deg = r.rad * UNITS_RAD_TO_DEG_D};
}

/**
 * \return cos(r)
 */
inline double cos_rad(Radians r) {
  return cos(r.rad);
}
/**
 * \return cos(r)
 */
inline double sin_rad(Radians r) {
  return sin(r.rad);
}

#ifdef __cplusplus
}
#endif
#endif
