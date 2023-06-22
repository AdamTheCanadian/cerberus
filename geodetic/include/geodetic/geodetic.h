#ifndef CERBERUS_TOP_GEODETIC_INCLUDE_GEODETIC_GEODETIC_H_
#define CERBERUS_TOP_GEODETIC_INCLUDE_GEODETIC_GEODETIC_H_
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  // Typically denoted as R_N
  double meridian;
  // Typically denoted as R_E
  double transverse;
} geodetic_Radii;

/**
 * Calculate the radii of curvature for a given latitude
 * Assumes WGS84 ellipsoid
 * \param latitude in radians
 * \return radii for given latitude
 */
geodetic_Radii geodetic_radii_calculate(double latitude);

#ifdef __cplusplus
}
#endif
#endif
