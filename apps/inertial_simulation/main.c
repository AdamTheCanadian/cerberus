#include "geodetic/geodetic.h"
#include "types/units.h"
#include "types/orientation_conversions.h"
#include <stdio.h>

typedef struct {
  double time;
  geodetic_PoseLLH pose;
} MotionProfile;

#define MAX_PROFILE_SIZE 10000
MotionProfile true_sim_motion_profile[MAX_PROFILE_SIZE];
// The profile after applying IMU model parameters
MotionProfile imu_sim_profile[MAX_PROFILE_SIZE];

int main(int argc, char *argv[]) {

  // Create simulated trajectory, for now just a static imu
  double current_time = 0;
  double sim_duration = 60;
  double sim_time_step = 0.01;
  int idx = 0;
  while (current_time < sim_duration) {
    true_sim_motion_profile[idx].time = current_time;
    true_sim_motion_profile[idx].pose.pos.latitude = deg_to_rad((Degrees){.deg = 51});
    true_sim_motion_profile[idx].pose.pos.longitude.rad = 0;
    true_sim_motion_profile[idx].pose.pos.height.m = 10;
    true_sim_motion_profile[idx].pose.vel_ned[0] = 0;
    true_sim_motion_profile[idx].pose.vel_ned[1] = 0;
    true_sim_motion_profile[idx].pose.vel_ned[2] = 0;
    Euler e = {.x.rad = 0, .y.rad = 0, .z.rad = 0};
    true_sim_motion_profile[idx].pose.att = euler_to_rotation3d(&e);
    idx++;
    current_time += sim_time_step;
  }

  static const double omega_ie = 7.292115e-5;
  for (int i = 1; i < idx; i++) {
    const double dt = true_sim_motion_profile[i].time - true_sim_motion_profile[i - 1].time;
    const geodetic_PoseLLH *prev_pose = &true_sim_motion_profile[i - 1].pose;
    const geodetic_PoseLLH *curr_pose = &true_sim_motion_profile[i].pose;

    // Angular rate of ecef frame, resolved about NED frame
    const Vector3d omega_ie_n = geodetic_calculate_angular_rate_ecef_ned(&prev_pose->pos);

    const geodetic_Radii prev_radii = geodetic_radii_calculate(prev_pose->pos.latitude);
    const geodetic_Radii curr_radii = geodetic_radii_calculate(curr_pose->pos.latitude);

    // Angular rate of NED frame w.r.t to ECEF frame
    const Vector3d prev_omega_en_n = geodetic_calculate_angular_rate_ned(prev_pose);
    const Vector3d curr_omega_en_n = geodetic_calculate_angular_rate_ned(curr_pose);

    // Initialize the coordinate transformation, but will be updating over several steps
    Rotation3d prev_to_new = mat3d_transpose(&prev_pose->att);
    Vector3d tmp = {.vec = {
        omega_ie_n.vec[0] + 0.5 * curr_omega_en_n.vec[0] + 0.5 * prev_omega_en_n.vec[0],
        omega_ie_n.vec[1] + 0.5 * curr_omega_en_n.vec[1] + 0.5 * prev_omega_en_n.vec[1],
        omega_ie_n.vec[2] + 0.5 * curr_omega_en_n.vec[2] + 0.5 * prev_omega_en_n.vec[2]}};

    Matrix3d skew = skew_symmetric(&tmp);
    skew = mat3d_scale(&skew, dt);

    const Matrix3d I = mat3d_identity();

    skew = mat3d_subtract(&I, &skew);
    prev_to_new = mat3d_multiply_mat3d(&prev_to_new, &skew);
    prev_to_new = mat3d_multiply_mat3d(&prev_to_new, &prev_pose->att);

    // Approximate angular rate with respect to inertial frame
    Vector3d alpha_ib_b = {.vec = {
        0.5 * (mat3d_at(&prev_to_new, 1, 2) - mat3d_at(&prev_to_new, 2, 1)),
        0.5 * (mat3d_at(&prev_to_new, 2, 0) - mat3d_at(&prev_to_new, 0, 2)),
        0.5 * (mat3d_at(&prev_to_new, 0, 1) - mat3d_at(&prev_to_new, 1, 0))}};

    double temp = acos(0.5 * (mat3d_trace(&prev_to_new) - 1));
    if (temp > 2e-5) {
      const double s = temp / sin(temp);
      alpha_ib_b.vec[0] *= s;
      alpha_ib_b.vec[1] *= s;
      alpha_ib_b.vec[2] *= s;
    }
    // Angular rate
    double omega_ib_b[3] = {
        alpha_ib_b.vec[0] / dt,
        alpha_ib_b.vec[1] / dt,
        alpha_ib_b.vec[2] / dt};

    const Vector3d gravity = geodetic_calculate_gravity_ned(&prev_pose->pos);
    const Vector3d tmp_omega = {
        .x = prev_omega_en_n.vec[0] + 2.0 * omega_ie_n.vec[0],
        .y = prev_omega_en_n.vec[1] + 2.0 * omega_ie_n.vec[1],
        .z = prev_omega_en_n.vec[2] + 2.0 * omega_ie_n.vec[2]};
    const Matrix3d skew_omega = skew_symmetric(&tmp_omega);
    const Vector3d vec_omega = mat3d_multiply_vec3d(&skew_omega, &tmp_omega);

    const double acc[3] = {
        (curr_pose->vel_ned[0] - prev_pose->vel_ned[0]) / dt,
        (curr_pose->vel_ned[1] - prev_pose->vel_ned[1]) / dt,
        (curr_pose->vel_ned[2] - prev_pose->vel_ned[2]) / dt};
    // specific force resolved about ecef axes, this will be updated over several steps
    Vector3d f_ib_n = {.vec = {
      acc[0] - gravity.vec[0] + vec_omega.vec[0],
      acc[1] - gravity.vec[1] + vec_omega.vec[2],
      acc[2] - gravity.vec[2] + vec_omega.vec[2]}};

    double mag_alpha = vec3d_dot(&f_ib_n, &f_ib_n);
    Matrix3d skew_alpha = skew_symmetric(&alpha_ib_b);

    tmp.vec[0] = prev_omega_en_n.vec[0] + omega_ie_n.vec[0];
    tmp.vec[1] = prev_omega_en_n.vec[1] + omega_ie_n.vec[1];
    tmp.vec[2] = prev_omega_en_n.vec[2] + omega_ie_n.vec[2];
    skew = skew_symmetric(&tmp);
    skew = mat3d_multiply_mat3d(&skew, &prev_pose->att);
    skew = mat3d_scale(&skew, 0.5);

    Matrix3d avg_C_b_n;
    if (mag_alpha > 1.0e-8) {
      const double mag_alpha2 = mag_alpha * mag_alpha;
      const double cos_alpha = (1.0 - cos(mag_alpha)) / mag_alpha2;
      const double sin_alpha = (1.0 - sin(mag_alpha) / mag_alpha) / mag_alpha2;
      const Matrix3d tmp2 = mat3d_scale(&skew_alpha, cos_alpha);
      Matrix3d skew_alpha_sqr = mat3d_multiply_mat3d(&skew_alpha, &skew_alpha);
      skew_alpha_sqr = mat3d_scale(&skew_alpha_sqr, sin_alpha);

      // I + tmp2 + skew_alpha_sqr
      Matrix3d tmp3 = {.mat = {
          1 + tmp2.mat[0] + skew_alpha_sqr.mat[0], 0 + tmp2.mat[1] + skew_alpha_sqr.mat[1], 0 + tmp2.mat[2] + skew_alpha_sqr.mat[2],
          0 + tmp2.mat[3] + skew_alpha_sqr.mat[3], 1 + tmp2.mat[4] + skew_alpha_sqr.mat[4], 0 + tmp2.mat[5] + skew_alpha_sqr.mat[5],
          0 + tmp2.mat[6] + skew_alpha_sqr.mat[6], 1 + tmp2.mat[7] + skew_alpha_sqr.mat[7], 1 + tmp2.mat[8] + skew_alpha_sqr.mat[8]}};

      tmp3 = mat3d_multiply_mat3d(&prev_pose->att, &tmp3);
      avg_C_b_n = mat3d_multiply_mat3d(&tmp3, &skew);
    }
    else {
      for (int i = 0; i < 9; i++) {
        avg_C_b_n.mat[i] = prev_pose->att.mat[i] - skew.mat[i];
      }
    }
    Matrix3d inv_prev_att = mat3d_inverse(&prev_pose->att);
    f_ib_n = mat3d_multiply_vec3d(&inv_prev_att, &f_ib_n);

    printf("f_ib_n: %.3f %.3f %.3f\n", f_ib_n.vec[0], f_ib_n.vec[1], f_ib_n.vec[2]);
    printf("omega_ib_b: %.7f %.7f %.7f\n", omega_ib_b[0], omega_ib_b[1], omega_ib_b[2]);
  }
}