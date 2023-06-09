#ifndef CERBERUS_TOP_GEODETIC_INCLUDE_GEODETIC_GEODETIC_H_
#define CERBERUS_TOP_GEODETIC_INCLUDE_GEODETIC_GEODETIC_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "linear_algebra/vector3d.h"
#include "types/units.h"
#include "types/rotation_matrix.h"

typedef struct {
  // Typically denoted as R_N
  Metres meridian;
  // Typically denoted as R_E
  Metres transverse;
} geodetic_Radii;

typedef struct {
  Radians latitude;
  Radians longitude;
  Metres height;
} geodetic_PositionLLH;

typedef struct {
  geodetic_PositionLLH pos;
  Vector3d vel_ned;
  Rotation3d att;
} geodetic_PoseLLH;

typedef struct {
  Metres x;
  Metres y;
  Metres z;
} geodetic_PositionXYZ;

/**
 * Calculate the radii of curvature for a given latitude
 * Assumes WGS84 ellipsoid
 * \param latitude in radians
 * \return radii for given latitude
 */
geodetic_Radii geodetic_radii_calculate(Radians latitude);

/**
 * Add [east, north, up] components to a geodetic position
 * Assumes WGS84 ellipsoid
 * \param pos the original position
 * \param e east vector component in metres
 * \param n north vector component in metres
 * \param u up vector component in metres
 * \return A new geodetic position that is [pos] offset by [e, n, u]
 */
geodetic_PositionLLH geodetic_position_llh_add_enu(geodetic_PositionLLH const *pos,
                                                   Metres e,
                                                   Metres n,
                                                   Metres u);
/**
 * Add [east, north, up] components to a geodetic position, modifies input position in place
 * Assumes WGS84 ellipsoid
 * \param pos the position being offset, done in place
 * \param e east vector component in metres
 * \param n north vector component in metres
 * \param u up vector component in metres
 */
void geodetic_position_llh_add_enu_in_place(geodetic_PositionLLH *pos,
                                            Metres e,
                                            Metres n,
                                            Metres u);

/**
 * Convert a latitude longitude height position into an X Y Z (ECEF) position
 * Assumes WGS84 ellipsoid
 * \param pos
 * \return converted position
 */
geodetic_PositionXYZ geodetic_position_llh_convert_to_xyz(const geodetic_PositionLLH *pos);

/**
 *
 * \param pos
 * \return
 */
Vector3d geodetic_calculate_gravity_ned(const geodetic_PositionLLH *pos);

/**
 * Calculate the angular rate of the ECEF frame resolved about the NED frame
 */
Vector3d geodetic_calculate_angular_rate_ecef_ned(geodetic_PositionLLH const *pos);

Vector3d geodetic_calculate_angular_rate_ned(geodetic_PoseLLH const *pose);

#ifdef __cplusplus
}
#endif
#endif
