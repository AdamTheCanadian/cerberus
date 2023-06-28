#include "inertial/inertial.h"
#include "types/orientation_conversions.h"

geodetic_PoseLLH inertial_update_ned(geodetic_PoseLLH const *prevPose,
                                     double timePrevPose,
                                     IMUData const *imu_data) {
  const double dt = imu_data->time - timePrevPose;
  // TODO: assert/error if dt <= 0?

  // Breaking out previous data to make code shorter/cleaner
  const geodetic_PositionLLH *prev_pos = &prevPose->pos;
  const Vector3d *prev_vel = &prevPose->vel_ned;
  const Rotation3d *prev_att = &prevPose->att;

  geodetic_PoseLLH curr_pose;
  geodetic_PositionLLH *curr_pos = &curr_pose.pos;
  Vector3d *curr_vel = &curr_pose.vel_ned;
  Rotation3d *curr_att = &curr_pose.att;

  const Vector3d alpha_ib_b = {
      .x = imu_data->gyro.x * dt,
      .y = imu_data->gyro.y * dt,
      .z = imu_data->gyro.z * dt};

  const double mag_alpha_ib_b = vec3d_dot(&alpha_ib_b, &alpha_ib_b);
  const Matrix3d skew_alpha_ib_b = skew_symmetric(&alpha_ib_b);

  const Vector3d omega_ie_n = geodetic_calculate_angular_rate_ecef_ned(prev_pos);
  const Vector3d omega_en_n = geodetic_calculate_angular_rate_ned(prevPose);

  // Attitude update
  Rotation3d avg_C_b_n = skew_symmetric_sum_two_vectors(&omega_ie_n, &omega_en_n);
  avg_C_b_n = mat3d_scale(&avg_C_b_n, 0.5);
  avg_C_b_n = mat3d_multiply_mat3d(&avg_C_b_n, prev_att);

  if (mag_alpha_ib_b > 1.0e-8) {
    const double mag_alpha2 = mag_alpha_ib_b * mag_alpha_ib_b;
    const double cos_alpha = (1.0 - cos(mag_alpha_ib_b)) / mag_alpha2;
    const double sin_alpha = (1.0 - sin(mag_alpha_ib_b) / mag_alpha_ib_b) / mag_alpha2;
    const Matrix3d tmp2 = mat3d_scale(&skew_alpha_ib_b, cos_alpha);
    Matrix3d skew_alpha_sqr = mat3d_multiply_mat3d(&skew_alpha_ib_b, &skew_alpha_ib_b);
    skew_alpha_sqr = mat3d_scale(&skew_alpha_sqr, sin_alpha);

    // I + tmp2 + skew_alpha_sqr
    Matrix3d tmp3 = {.mat = {
        1 + tmp2.mat[0] + skew_alpha_sqr.mat[0], 0 + tmp2.mat[1] + skew_alpha_sqr.mat[1], 0 + tmp2.mat[2] + skew_alpha_sqr.mat[2],
        0 + tmp2.mat[3] + skew_alpha_sqr.mat[3], 1 + tmp2.mat[4] + skew_alpha_sqr.mat[4], 0 + tmp2.mat[5] + skew_alpha_sqr.mat[5],
        0 + tmp2.mat[6] + skew_alpha_sqr.mat[6], 1 + tmp2.mat[7] + skew_alpha_sqr.mat[7], 1 + tmp2.mat[8] + skew_alpha_sqr.mat[8]}};

    tmp3 = mat3d_multiply_mat3d(prev_att, &tmp3);
    avg_C_b_n = mat3d_multiply_mat3d(&tmp3, &avg_C_b_n);
  }
  else {
    for (int j = 0; j < 9; j++) {
      avg_C_b_n.mat[j] = prev_att->mat[j] - avg_C_b_n.mat[j];
    }
  }

  const Vector3d gravity = geodetic_calculate_gravity_ned(prev_pos);
  // old_omega_en_n + 2 * omega_ie_n
  Vector3d tmp = {
      .x = omega_en_n.x + 2.0 * omega_ie_n.x,
      .y = omega_en_n.y + 2.0 * omega_ie_n.y,
      .z = omega_en_n.z + 2.0 * omega_ie_n.z};

  Matrix3d skew = skew_symmetric(&tmp);
  tmp = mat3d_multiply_vec3d(&skew, prev_vel);

  for (int i = 0; i < 3; i++) {
    curr_vel->vec[i] = prev_vel->vec[i] + dt * (imu_data->acc.vec[i] + gravity.vec[i] - tmp.vec[i]);
  }
  const double half_dt = 0.5 * dt;
  curr_pos->height.m = prev_pos->height.m -
      half_dt * (curr_vel->vec[2] + prev_vel->vec[2]);

  const geodetic_Radii prev_radii = geodetic_radii_calculate(prev_pos->latitude);

  curr_pos->latitude.rad = prev_pos->latitude.rad +
      half_dt * (prev_vel->vec[0] / (prev_radii.meridian.m + prev_pos->height.m) +
      curr_vel->vec[0] / (prev_radii.meridian.m + curr_pos->height.m));

  const geodetic_Radii curr_radii = geodetic_radii_calculate(curr_pos->latitude);

  curr_pos->longitude.rad = prev_pos->longitude.rad +
      half_dt * (prev_vel->vec[1] / ((prev_radii.transverse.m + prev_pos->height.m) * cos_rad(prev_pos->latitude)) +
          curr_vel->vec[1] / ((curr_radii.transverse.m + curr_pos->height.m) * cos_rad(curr_pos->latitude)));

  Vector3d curr_omega_en_n = geodetic_calculate_angular_rate_ned(&curr_pose);
  Rotation3d C_new_old;
  const Matrix3d I = mat3d_identity();
  if (mag_alpha_ib_b > 1.0e-8) {
    const double mag_alpha2 = mag_alpha_ib_b * mag_alpha_ib_b;
    const double sin_alpha = sin(mag_alpha_ib_b) / mag_alpha_ib_b;
    const double cos_alpha = (1.0 - cos(mag_alpha_ib_b)) / mag_alpha2;
    const Matrix3d skew2 = mat3d_multiply_mat3d(&skew_alpha_ib_b, &skew_alpha_ib_b);

    for (int i = 0; i < 9; i++) {
      C_new_old.mat[i] = I.mat[i] + sin_alpha * skew_alpha_ib_b.mat[i] + cos_alpha * skew2.mat[i];
    }
  }
  else {
    for (int i = 0; i < 9; i++) {
      C_new_old.mat[i] = I.mat[i] + skew_alpha_ib_b.mat[i];
    }
  }

  const Vector3d tmp2 = {.vec = {
      omega_ie_n.x + 0.5 * curr_omega_en_n.x + 0.5 * omega_en_n.x,
      omega_ie_n.y + 0.5 * curr_omega_en_n.y + 0.5 * omega_en_n.y,
      omega_ie_n.z + 0.5 * curr_omega_en_n.z + 0.5 * omega_en_n.z}};

  const Matrix3d skew2 = skew_symmetric(&tmp2);
  for (int i = 0; i < 9; i++) {
    curr_att->mat[i] = I.mat[i] - skew2.mat[i] * dt;
  }
  *curr_att = mat3d_multiply_mat3d(curr_att, prev_att);
  *curr_att = mat3d_multiply_mat3d(curr_att, &C_new_old);

  return curr_pose;
}