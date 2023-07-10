#ifndef CERBERUS_TOP_GUI_INCLUDE_GUI_CAMERA3D_H_
#define CERBERUS_TOP_GUI_INCLUDE_GUI_CAMERA3D_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "linear_algebra/vector3f.h"
#include "linear_algebra/matrix4f.h"

typedef struct {
  Mat4f view;
  Mat4f rotation;

  Vec3f position;
  Vec3f target;
  Vec3f up;

  Vec3f angle;
  double distance_to_target;
} gui_Camera3D;

void gui_cam3d_init(gui_Camera3D *cam);

void gui_cam3d_set_cam_pos(gui_Camera3D *cam,
                           Vec3f pos);
#ifdef __cplusplus
}
#endif
#endif
