#ifndef CERBERUS_TOP_APPS_INERTIAL_SIMULATION_TRAJECTORY_H_
#define CERBERUS_TOP_APPS_INERTIAL_SIMULATION_TRAJECTORY_H_
#ifdef __cplusplus
extern "C" {
#endif

#define TRAJ_MAX_WAYPOINTS 100

typedef struct {
  double north_pos;
  double east_pos;
  double down_pos;
  double north_vel;
  double east_vel;
  double down_vel;
} Waypoint;

typedef struct {
  Waypoint waypoints[TRAJ_MAX_WAYPOINTS];
} Trajectory;

#ifdef __cplusplus
}
#endif
#endif
