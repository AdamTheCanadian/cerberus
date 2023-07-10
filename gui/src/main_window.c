#include "gui/main_window.h"
#include "glad/glad.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

static void update_projection(gui_MainWindow *window);

void gui_main_window_init(gui_MainWindow *window) {
  assert(window != NULL);

  #if defined(__APPLE__)
    glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);
  #endif
  if (!glfwInit()) {
    printf("GLFW ERROR: Failed to initialize\n");
    return;
  }
  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  #if defined(__APPLE__)
    /* OSX Requires fordward compatibility */
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  #endif

  window->glfw_window = glfwCreateWindow(window->width,
                                         window->height,
                                         window->title,
                                         NULL,
                                         NULL);
  if (window->glfw_window == NULL) {
    printf("GLFW ERROR: Failed to create window\n");
    return;
  }
  glfwMakeContextCurrent(window->glfw_window);
  /* Enable vsync, when this is disabled was getting high cpu usage */
  glfwSwapInterval(1);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("GLAD ERROR: Failed to initialize\n");
    return;
  }
  igCreateContext(NULL);
  const char* glsl_version = "#version 330 core";
  ImGui_ImplGlfw_InitForOpenGL(window->glfw_window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
  igStyleColorsDark(NULL);
  ImPlot_CreateContext();

  update_projection(window);
}

bool gui_main_window_still_open(gui_MainWindow *window) {
  assert(window != NULL);
  assert(window->glfw_window != NULL);
  return !glfwWindowShouldClose(window->glfw_window);
}

void gui_main_window_begin_frame(gui_MainWindow *window) {
  assert(window != NULL);
  assert(window->glfw_window != NULL);
  glfwPollEvents();
  glClearColor(window->background_color[0],
               window->background_color[1],
               window->background_color[2],
               window->background_color[3]);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  igNewFrame();
}

void gui_main_window_end_frame(gui_MainWindow *window) {
  assert(window != NULL);
  assert(window->glfw_window != NULL);
  igRender();
  ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
  glfwSwapBuffers(window->glfw_window);
}

void update_projection(gui_MainWindow *window) {
  // Breaking out projection to make code cleaner
  Mat4f *proj = &window->projection;

  mat4f_set_to_zero(proj);
  static const float near_plane = 0.01f;
  static const float far_plane = 1000.0f;
  static const float fov = 45;
  const double aspect_ratio = (double)window->width / (double)window->height;

  const double top = near_plane * tan(fov * 0.5 * M_PI / 180.0);
  const double right = top * aspect_ratio;
  const double left = -right;
  const double bottom = -top;
  const double znear = near_plane;
  const double zfar = far_plane;

  /* Right left distance */
  const float rl = (float)(right - left);
  /* Top bottom distance */
  const float tb = (float)(top - bottom);
  /* Far near distance */
  const float fn = (float)(zfar - znear);

  proj->mat[0] = (float)(znear * 2.0f) / rl;
  proj->mat[5] = (float)(znear * 2.0f) / tb;
  proj->mat[8] = (float)(right + left) / rl;
  proj->mat[9] = (float)(top + bottom) / tb;
  proj->mat[10] = -(float)(zfar + znear) / fn;
  proj->mat[11] = -1.0f;
  proj->mat[14] = -(float)(zfar * znear * 2.0f) / fn;
}