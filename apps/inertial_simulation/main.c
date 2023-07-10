#include "geodetic/geodetic.h"
#include "types/units.h"
#include "types/orientation_conversions.h"
#include "inertial/inertial.h"
#include "gui/main_window.h"
#include "gui/grid.h"
#include "gui/camera3d.h"
#include "trajectory.h"
#include <stdio.h>
#include <string.h>

/**
 * Simulation:
 * - Create trajectory from waypoints
 *  - allow clicking on screen to set waypoint
 *  - Allow modification of waypoint from gui
 *  - Allow copying of waypoints
 * - Set velocity of each waypoint
 *   - Allow modification of waypoint
 *   - Linearly interpolate between waypoints to create velocities
 * - Plot change of N / E / D directions
 * - Plot velocity over time in each direction
 * - Draw coordinate axis
 * - Draw grid
 * - Add IMU sensor
 *   - Create GUI to change model parameters
 *   - Change lever arm of IMU
 * - Add GNSS sensor
 *   - Create GUI to change model parameters
 *   - Change lever arm of phase center
 */

typedef struct {
  double time;
  geodetic_PoseLLH pose;
} MotionProfile;

#define MAX_PROFILE_SIZE 10000
MotionProfile true_sim_motion_profile[MAX_PROFILE_SIZE] = {0};
IMUData all_imu_data[MAX_PROFILE_SIZE] = {0};
// The profile after using the imu generated measurements to compute the updated position
MotionProfile imu_profile[MAX_PROFILE_SIZE] = {0};

float grid_vertices[10000];
gui_Grid grid = {
    .num_vertices = 0,
    .max_vertices = 10000,
    .vertices = grid_vertices};

int main(int argc, char *argv[]) {

  gui_MainWindow main_window;
  strncpy(main_window.title, "IMU Simulation", GUI_MAIN_WINDOW_TITLE_MAX_LENGTH);
  main_window.height = 800;
  main_window.width = 1200;
  main_window.background_color[0] = 1.0f;
  main_window.background_color[1] = 1.0f;
  main_window.background_color[2] = 1.0f;
  main_window.background_color[3] = 1.0f;

  gui_Camera3D cam;
  gui_cam3d_init(&cam);
  gui_cam3d_set_cam_pos(&cam, (Vec3f){.x = 0, .y = 0, .z = 10});
  gui_main_window_init(&main_window);

  gui_grid_setup_vertices(&grid, 1, (gui_GridLimits){.x_min = -10, .x_max = 10, .y_min = -10, .y_max = 10});
  gui_grid_init_gl(&grid);

  while (gui_main_window_still_open(&main_window)) {
    gui_main_window_begin_frame(&main_window);

    gui_grid_draw(&grid, &cam.view, &main_window.projection);
    gui_main_window_end_frame(&main_window);
  }
}