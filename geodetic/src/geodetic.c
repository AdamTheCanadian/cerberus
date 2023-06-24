#include "geodetic/geodetic.h"
#include <math.h>

static const double WGS84_SEMI_MAJOR = 6378137;
static const double WGS84_ECCENTRICITY = 0.0818191908425;
static const double WGS84_ECCENTRICITY_SQR = WGS84_ECCENTRICITY * WGS84_ECCENTRICITY;
static const double WGS84_ONE_MINUS_ECCENTRICITY_SQR = 1.0 - WGS84_ECCENTRICITY_SQR;

geodetic_Radii geodetic_radii_calculate(Radians latitude) {
  double sin_lat = sin(latitude.rad);
  double e = (WGS84_ECCENTRICITY * sin_lat);
  double temp = 1.0 - (e * e);

  geodetic_Radii radii;
  radii.meridian.m = WGS84_SEMI_MAJOR * (1.0 - WGS84_ECCENTRICITY_SQR) / pow(temp, 1.5);
  radii.transverse.m = WGS84_SEMI_MAJOR / sqrt(temp);
  return radii;
}

geodetic_PositionLLH geodetic_position_llh_add_enu(geodetic_PositionLLH const *pos,
                                                   Metres e,
                                                   Metres n,
                                                   Metres u) {
  geodetic_PositionLLH return_pos;
  geodetic_Radii radii = geodetic_radii_calculate(pos->latitude);
  return_pos.latitude.rad = pos->latitude.rad + (n.m / (radii.meridian.m + pos->height.m));
  return_pos.longitude.rad = pos->longitude.rad +
      e.m / ((radii.transverse.m + pos->height.m) * cos(pos->latitude.rad));
  return_pos.height.m = pos->height.m + u.m;
  return return_pos;
}

void geodetic_position_llh_add_enu_in_place(geodetic_PositionLLH *pos,
                                            Metres e,
                                            Metres n,
                                            Metres u) {
  geodetic_Radii radii = geodetic_radii_calculate(pos->latitude);
  pos->latitude.rad = pos->latitude.rad + (n.m / (radii.meridian.m + pos->height.m));
  pos->longitude.rad = pos->longitude.rad +
      e.m / ((radii.transverse.m + pos->height.m) * cos(pos->latitude.rad));
  pos->height.m = pos->height.m + u.m;
}

geodetic_PositionXYZ geodetic_position_llh_convert_to_xyz(const geodetic_PositionLLH *pos) {
  const geodetic_Radii radii = geodetic_radii_calculate(pos->latitude);
  const double cos_lat = cos_rad(pos->latitude);
  const double cos_lon = cos_rad(pos->longitude);
  const double sin_lat = sin_rad(pos->latitude);
  const double sin_lon = sin_rad(pos->longitude);
  const double r_h = radii.transverse.m + pos->height.m;

  const geodetic_PositionXYZ return_pos = {
      .x.m = r_h * cos_lat * cos_lon,
      .y.m = r_h * cos_lat * sin_lon,
      .z.m = (WGS84_ONE_MINUS_ECCENTRICITY_SQR * radii.transverse.m + pos->height.m) * sin_lat};
  return return_pos;
}