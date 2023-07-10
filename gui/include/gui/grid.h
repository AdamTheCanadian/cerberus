#ifndef CERBERUS_TOP_GUI_INCLUDE_GUI_GRID_H_
#define CERBERUS_TOP_GUI_INCLUDE_GUI_GRID_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui/shader.h"
#include "linear_algebra/matrix4f.h"
#include <stdint.h>

typedef struct {
  gui_Shader shader;
  uint32_t vao;
  uint32_t vbo;
  uint32_t max_vertices;
  uint32_t num_vertices;
  float *vertices;
} gui_Grid;

typedef struct {
  float x_min;
  float x_max;
  float y_min;
  float y_max;
} gui_GridLimits;

void gui_grid_setup_vertices(gui_Grid *grid,
                             float spacing,
                             gui_GridLimits gridLimits);

void gui_grid_init_gl(gui_Grid *grid);

void gui_grid_draw(gui_Grid const *grid,
                   Mat4f const *view,
                   Mat4f const *proj);
#ifdef __cplusplus
}
#endif
#endif
