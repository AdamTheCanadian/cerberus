#ifndef CERBERUS_TOP_GUI_INCLUDE_GUI_MAIN_WINDOW_H_
#define CERBERUS_TOP_GUI_INCLUDE_GUI_MAIN_WINDOW_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <stdbool.h>

/* Include ImGui here so any users of main_window.h automatically get imgui functionality */
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
#include "cimgui_impl.h"

#define GUI_MAIN_WINDOW_TITLE_MAX_LENGTH 128

typedef struct {
  // Will be displayed at the top of the window, the title bar
  char title[GUI_MAIN_WINDOW_TITLE_MAX_LENGTH];

  // Set by calling init() function, will be NULL if something went wrong
  GLFWwindow *glfw_window;

  int height;
  int width;

  // The background or clear color [R G B A]. Values in range of [0, 1]
  float background_color[4];
} gui_MainWindow;

/**
 * Initializes OpenGL, GLFW, etc (all the backend stuff needed for rendering)
 * \param window
 */
void gui_main_window_init(gui_MainWindow *window);

/**
 * \return true if the window is still open
 * \return false if the user closed the window, usually indicates closing of application
 */
bool gui_main_window_still_open(gui_MainWindow *window);

void gui_main_window_begin_frame(gui_MainWindow *window);

void gui_main_window_end_frame(gui_MainWindow *window);
#ifdef __cplusplus
}
#endif
#endif
