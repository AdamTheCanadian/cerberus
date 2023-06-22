#include "geodetic/geodetic.h"
#include <math.h>

static const double WGS84_SEMI_MAJOR = 6378137;
static const double WGS84_ECCENTRICITY = 0.0818191908425;
static const double WGS84_ECCENTRICITY_SQR = WGS84_ECCENTRICITY * WGS84_ECCENTRICITY;

geodetic_Radii geodetic_radii_calculate(double latitude) {
  double sin_lat = sin(latitude);
  double e = (WGS84_ECCENTRICITY * sin_lat);
  double temp = 1.0 - (e * e);

  geodetic_Radii radii;
  radii.meridian = WGS84_SEMI_MAJOR * (1.0 - WGS84_ECCENTRICITY_SQR) / pow(temp, 1.5);
  radii.transverse = WGS84_SEMI_MAJOR / sqrt(temp);
  return radii;
}