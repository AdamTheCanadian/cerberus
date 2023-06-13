#include "vis/main_window.h"
#include "glad/glad.h"
#include <assert.h>
#include <stdio.h>

void vis_main_window_init(vis_MainWindow *window) {
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
}

bool vis_main_window_still_open(vis_MainWindow *window) {
  assert(window != NULL);
  assert(window->glfw_window != NULL);
  return !glfwWindowShouldClose(window->glfw_window);
}

void vis_main_window_begin_frame(vis_MainWindow *window) {
  assert(window != NULL);
  assert(window->glfw_window != NULL);
  glfwPollEvents();
  glClearColor(window->background_color[0],
               window->background_color[1],
               window->background_color[2],
               window->background_color[3]);
  glClear(GL_COLOR_BUFFER_BIT);
}

void vis_main_window_end_frame(vis_MainWindow *window) {
  assert(window != NULL);
  assert(window->glfw_window != NULL);
  glfwSwapBuffers(window->glfw_window);
}