#include "gui/camera3d.h"
#include <math.h>

static void update_look_at(gui_Camera3D *cam);

static void update_angle(gui_Camera3D *cam);

static void update_orientation_angle(gui_Camera3D *cam,
                                     Vec3f angles);

static void compute_matrix(gui_Camera3D *cam);

void gui_cam3d_init(gui_Camera3D *cam) {
  vec3f_set_to_zero(&cam->position);
  vec3f_set_to_zero(&cam->target);
  vec3f_set_to_zero(&cam->up);
  vec3f_set_to_zero(&cam->angle);
  mat4f_set_to_identity(&cam->view);
  mat4f_set_to_identity(&cam->rotation);

  /* We assume by default the Y axis the global Up axis */
  cam->up.y = 1.0f;

  /* Our camera is centered in the origin (0 distance to target) */
  cam->distance_to_target = 0.0;

  update_look_at(cam);
}

void gui_cam3d_set_cam_pos(gui_Camera3D *cam,
                           Vec3f pos) {
  cam->position.x = pos.x;
  cam->position.y = pos.y;
  cam->position.z = pos.z;
  update_look_at(cam);
}

void gui_cam3d_rotate_increment(gui_Camera3D *cam,
                                double x,
                                double y,
                                double z) {
  /* Get the current rotation/orientation angles from the view matrix,
   * then will update the angles, and recompute the matrix */
  Vec3f angle = {
      .x = cam->angle.x + (float)x,
      .y = cam->angle.y + (float)y,
      .z = cam->angle.z + (float)z};

  update_orientation_angle(cam, angle);
}

void update_look_at(gui_Camera3D *cam) {

  mat4f_set_to_zero(&cam->view);
  /* If the camera is located at the target we only need to translate, no rotation is needed */
  if (vec3f_is_equal(&cam->position, &cam->target)) {
    mat4f_set_to_identity(&cam->view);
    mat4f_set_to_identity(&cam->rotation);
    Vec3f translation = (Vec3f) {
        .x = -cam->position.x,
        .y = -cam->position.y,
        .z = -cam->position.z};
    cam->view.mat[12] = translation.x;
    cam->view.mat[13] = translation.y;
    cam->view.mat[14] = translation.z;
    return;
  }

  Vec3f forward, right, up;
  vec3f_set_to_zero(&forward);
  vec3f_set_to_zero(&right);
  vec3f_set_to_zero(&up);

  /* Calculate the camera coordinate system Z axis (the direction vector) */
  forward = vec3f_subtract_vec3f(&cam->position, &cam->target);
  cam->distance_to_target = (double)vec3f_length(&forward);
  vec3f_normalize(&forward);

  /* By default assume Y axis is up, will correct this later as we determine the right
   * and forward axes */
  up.y = 1.0f;

  /* If we are looking down/up on the Y axis (90 degrees) we need to change the up vector */
  if (fabsf(forward.x) < 1.0e-5f && fabsf(forward.z) < 1.0e-5f) {
    if (forward.y > 0) {
      /* Forward vector is pointing along the +Y axis */
      up = (Vec3f){.x = 0.0f, .y = 0.0f, .z = -1.0f};
    }
    else {
      /* Foward vector is pointing along the -Y axis */
      up = (Vec3f){.x = 0.0f, .y = 0.0f, .z = 1.0f};
    }
  }

  /* Calculate the cameras right axis. */
  right = vec3f_cross(&up, &forward);

  /* In theory up and direction should already be normalized, meaning the cross
   * product is normalized but just to be safe going to normalize */
  vec3f_normalize(&right);

  /* Calculate the new up vector */
  up = vec3f_cross(&forward, &right);

  mat4f_set_to_identity(&cam->rotation);
  cam->rotation.mat[0] = right.x;
  cam->rotation.mat[4] = right.y;
  cam->rotation.mat[8] = right.z;

  cam->rotation.mat[1] = up.x;
  cam->rotation.mat[5] = up.y;
  cam->rotation.mat[9] = up.z;

  cam->rotation.mat[2] = forward.x;
  cam->rotation.mat[6] = forward.y;
  cam->rotation.mat[10] = forward.z;

  mat4f_set_to_identity(&cam->view);
  cam->view.mat[0] = right.x;
  cam->view.mat[4] = right.y;
  cam->view.mat[8] = right.z;

  cam->view.mat[1] = up.x;
  cam->view.mat[5] = up.y;
  cam->view.mat[9] = up.z;

  cam->view.mat[2] = forward.x;
  cam->view.mat[6] = forward.y;
  cam->view.mat[10] = forward.z;

  /* Translational components (note there is a negative sign) */
  Vec3f translation = (Vec3f) {
      .x = -vec3f_dot(&right, &cam->position),
      .y = -vec3f_dot(&up, &cam->position),
      .z = -vec3f_dot(&forward, &cam->position)
  };
  cam->view.mat[12] = translation.x;
  cam->view.mat[13] = translation.y;
  cam->view.mat[14] = translation.z;
  update_angle(cam);
}

void update_angle(gui_Camera3D *cam) {
  float yaw = 0.0f;
  float pitch = 0.0f;
  float roll = 0.0f;

  static const float RAD_TO_DEG = 180.0f / (float)M_PI;
  yaw = RAD_TO_DEG * asinf(cam->rotation.mat[8]);
  if (cam->rotation.mat[10] < 0) {
    if (yaw >= 0) {
      yaw = 180.0f - yaw;
    }
    else {
      yaw = -180.0f - yaw;
    }
  }

  if (cam->rotation.mat[0] > -1.0e-5f && cam->rotation.mat[0] < 1.0e-5f) {
    roll = 0.0f;
    pitch = RAD_TO_DEG * atan2f(cam->rotation.mat[1], cam->rotation.mat[5]);
  }
  else {
    roll = RAD_TO_DEG * atan2f(-cam->rotation.mat[4], cam->rotation.mat[0]);
    pitch = RAD_TO_DEG * atan2f(-cam->rotation.mat[9], cam->rotation.mat[10]);
  }
  /* Remember in open gl Y is up, so a yaw rotation is rotating around Y */
  cam->angle.x = pitch;
  cam->angle.y = -yaw;
  cam->angle.z = roll;
}

static void update_orientation_angle(gui_Camera3D *cam,
                                     Vec3f angles) {
  cam->angle.x = angles.x;
  cam->angle.y = angles.y;
  cam->angle.z = angles.z;
  mat4f_set_to_identity(&cam->rotation);
  static const float DEG_TO_RAD_F = (float)(M_PI / 180.0);

  /* Convert euler to rotation matrix */
  const float sx = sinf(angles.x * DEG_TO_RAD_F);
  const float cx = cosf(angles.x * DEG_TO_RAD_F);
  const float sy = sinf(-angles.y * DEG_TO_RAD_F);
  const float cy = cosf(-angles.y * DEG_TO_RAD_F);
  const float sz = sinf(angles.z * DEG_TO_RAD_F);
  const float cz = cosf(angles.z * DEG_TO_RAD_F);

  cam->rotation.mat[0] = cy * cz;
  cam->rotation.mat[1] = sx * sy * cz + cx * sz;
  cam->rotation.mat[2] = -cx * sy * cz + sx * sz;

  cam->rotation.mat[4] = -cy * sz;
  cam->rotation.mat[5] = -sx * sy * sz + cx * cz;
  cam->rotation.mat[6] = cx * sy * sz + sx * cz;

  cam->rotation.mat[8] = sy;
  cam->rotation.mat[9] = -sx * cy;
  cam->rotation.mat[10] = cx * cy;

  compute_matrix(cam);
}

void compute_matrix(gui_Camera3D *cam) {
  /* Extract the previous rotation matrix (orientation of the camera) */
  Vec3f right = (Vec3f) {
      .x = cam->rotation.mat[0],
      .y = cam->rotation.mat[1],
      .z = cam->rotation.mat[2]};
  Vec3f up = (Vec3f) {
      .x = cam->rotation.mat[4],
      .y = cam->rotation.mat[5],
      .z = cam->rotation.mat[6]};
  Vec3f forward = (Vec3f) {
      .x = cam->rotation.mat[8],
      .y = cam->rotation.mat[9],
      .z = cam->rotation.mat[10]};

  Vec3f translation = (Vec3f) {
      .x = right.x * -cam->target.x + up.x * -cam->target.y + forward.x * -cam->target.z,
      .y = right.y * -cam->target.x + up.y * -cam->target.y + forward.y * -cam->target.z,
      .z = right.z * -cam->target.x + up.z * -cam->target.y + forward.z * -cam->target.z - (float)cam->distance_to_target};

  mat4f_set_to_identity(&cam->view);

  cam->view.mat[0] = right.x;
  cam->view.mat[1] = right.y;
  cam->view.mat[2] = right.z;

  cam->view.mat[4] = up.x;
  cam->view.mat[5] = up.y;
  cam->view.mat[6] = up.z;

  cam->view.mat[8] = forward.x;
  cam->view.mat[9] = forward.y;
  cam->view.mat[10] = forward.z;

  cam->view.mat[12] = translation.x;
  cam->view.mat[13] = translation.y;
  cam->view.mat[14] = translation.z;

  /* Recompute the camera position */
  forward = (Vec3f) {
      .x = -cam->view.mat[2],
      .y = -cam->view.mat[6],
      .z = -cam->view.mat[10]};
  cam->position = (Vec3f){
      .x = cam->target.x - (float)cam->distance_to_target * forward.x,
      .y = cam->target.y - (float)cam->distance_to_target * forward.y,
      .z = cam->target.z - (float)cam->distance_to_target * forward.z};
}