#include "gui/image_window.h"
#include "gui/main_window.h"
#include <assert.h>

static const char* vs = "#version 330 core \n"
                 "layout (location = 0) in vec3 aPos;\n"
                 "layout (location = 1) in vec2 aTexCoord;\n"
                 "out vec2 TexCoord;\n"
                 "void main()\n"
                 "{\n"
                 "gl_Position = vec4(aPos, 1.0);\n"
                 "TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
                 "}\n";
static const char* fs = "#version 330 core \n"
                 "out vec4 FragColor; \n"
                 "in vec2 TexCoord; \n"
                 "uniform sampler2D texture1; \n"
                 "void main() \n"
                 "{ \n"
                 "FragColor = texture(texture1, TexCoord); \n"
                 "} \n";

void gui_imageu8_window_init(gui_ImageU8Window *window) {
  assert(window != NULL);
  assert(window->image != NULL);

  unsigned int vertex, fragment;
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vs, NULL);
  glCompileShader(vertex);
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fs, NULL);
  glCompileShader(fragment);

  window->shader = glCreateProgram();
  glAttachShader(window->shader, vertex);
  glAttachShader(window->shader, fragment);

  glLinkProgram(window->shader);
  // delete the shaders as they're linked into our program now and no longer necessery
  glDeleteShader(vertex);
  glDeleteShader(fragment);

  /* Render/display the image in the full context of the subwindow */
  float vertices[] = {
      1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
      1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
      -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,
      -1.0f, 1.0f, 0.0f,   0.0f, 1.0f};
  unsigned int indices[] = {0, 1, 3, 1, 2, 3};
  unsigned int vbo, ebo;
  glGenVertexArrays(1, &window->vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(window->vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // load and create a texture
  // -------------------------
  glGenTextures(1, &window->texture);
  glBindTexture(GL_TEXTURE_2D, window->texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_RED);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_RED);
  glBindVertexArray(0);

  window->first_render = 1;
}

void gui_imageu8_window_upload(gui_ImageU8Window *window) {
  glBindTexture(GL_TEXTURE_2D, window->texture);
  if (window->first_render == 1) {
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RED,
                 window->image->width,
                 window->image->height,
                 0,
                 GL_RED,
                 GL_UNSIGNED_BYTE,
                 window->image->image);
    window->first_render = 0;
  }
  else {
    glTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    0,
                    0,
                    window->image->width,
                    window->image->height,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    window->image->image);
  }
}

void gui_imageu8_window_draw(gui_ImageU8Window *window) {
  ImVec2 size = {.x = window->image->width, .y = window->image->height};
  ImVec2 uv0 = {.x = 0, .y = 0};
  ImVec2 uv1 = {.x = 1, .y = -1};
  ImVec4 tint = {1, 1, 1, 1};
  ImVec4 border = {0, 0, 0, 0};

  igBegin(window->name, NULL, 0);
  igImage(window->texture, size, uv0, uv1, tint, border);
  igEnd();
}