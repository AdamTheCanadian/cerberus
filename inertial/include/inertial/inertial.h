#ifndef CERBERUS_TOP_INERTIAL_INCLUDE_INERTIAL_INERTIAL_H_
#define CERBERUS_TOP_INERTIAL_INCLUDE_INERTIAL_INERTIAL_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "linear_algebra/vector3d.h"
#include "geodetic/geodetic.h"

typedef struct {
  double time;
  Vector3d acc;
  Vector3d gyro;
} IMUData;

geodetic_PoseLLH inertial_update_ned(geodetic_PoseLLH const *prevPose,
                                     double timePrevPose,
                                     IMUData const *imu_data);

#ifdef __cplusplus
}
#endif
#endif
