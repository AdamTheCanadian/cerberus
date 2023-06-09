#ifndef CERBERUS_TOP_GUI_INCLUDE_GUI_IMAGE_WINDOW_H_
#define CERBERUS_TOP_GUI_INCLUDE_GUI_IMAGE_WINDOW_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "cv/image.h"

typedef struct {
  cv_ImageU8 *image;
  char name[128];
  uint64_t window_width;
  uint64_t window_height;
  uint64_t shader;
  uint32_t vao;
  uint32_t texture;
  uint32_t first_render;
} gui_ImageU8Window;

void gui_imageu8_window_init(gui_ImageU8Window *window);

/**
 * Upload the current set image to the GPU, needs to be called before drawing, or if the image
 * changes
 * \param window
 */
void gui_imageu8_window_upload(gui_ImageU8Window *window);

void gui_imageu8_window_draw(gui_ImageU8Window *window);

#ifdef __cplusplus
}
#endif
#endif
