#include "gui/grid.h"
#include "glad/glad.h"

void gui_grid_setup_vertices(gui_Grid *grid,
                             float spacing,
                             gui_GridLimits gridLimits) {
  /* Setup the horizontal spanning lines */
  float curr_val = gridLimits.y_min;
  while (curr_val <= gridLimits.y_max && grid->num_vertices < grid->max_vertices) {

    grid->vertices[grid->num_vertices] = gridLimits.x_min;
    grid->vertices[grid->num_vertices + 1] = curr_val;

    grid->vertices[grid->num_vertices + 3] = gridLimits.x_max;
    grid->vertices[grid->num_vertices + 4] = curr_val;

    curr_val += spacing;
    grid->num_vertices += 6;
  }

  /* Setup the vertical spanning lines */
  curr_val = gridLimits.x_min;
  while (curr_val <= gridLimits.x_max && grid->num_vertices < grid->max_vertices) {

    grid->vertices[grid->num_vertices] = curr_val;
    grid->vertices[grid->num_vertices + 1] = gridLimits.y_min;

    grid->vertices[grid->num_vertices + 3] = curr_val;
    grid->vertices[grid->num_vertices + 4] = gridLimits.y_max;

    curr_val += spacing;
    grid->num_vertices += 6;
  }
}

void gui_grid_init_gl(gui_Grid *grid) {
  grid->shader = gui_shader_load_from_file("/Users/adamclare/projects/cerberus/gui/shaders/grid_shader.vs",
                                           "/Users/adamclare/projects/cerberus/gui/shaders/grid_shader.fs");
  glGenVertexArrays(1, &grid->vao);
  glGenBuffers(1, &grid->vbo);
  glBindVertexArray(grid->vao);

  glBindBuffer(GL_ARRAY_BUFFER, grid->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * grid->num_vertices, grid->vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void gui_grid_draw(gui_Grid const *grid,
                   Mat4f const *view,
                   Mat4f const *proj) {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glUseProgram(grid->shader);
  // Grid default color is black
  float grid_color[4] = {0, 0, 0, 1};
  glUniform4f(glGetUniformLocation(grid->shader, "color"),
              grid_color[0],
              grid_color[1],
              grid_color[2],
              grid_color[3]);
  glUniformMatrix4fv(glGetUniformLocation(grid->shader, "view"), 1, GL_FALSE, &view->mat[0]);
  glUniformMatrix4fv(glGetUniformLocation(grid->shader, "projection"), 1, GL_FALSE, &proj->mat[0]);

  glBindVertexArray(grid->vao);
  glDrawArrays(GL_LINES, 0, (GLsizei)(grid->num_vertices * sizeof(float)) / 6);
}
