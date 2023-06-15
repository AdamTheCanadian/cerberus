/**
* \file This is just a test application used for gui development
*/

#include "utils/kitti_data_reader.h"
#include "vis/main_window.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  vis_MainWindow main_window;
  strncpy(main_window.title, "GUI Test", VIS_MAIN_WINDOW_TITLE_MAX_LENGTH);
  main_window.height = 800;
  main_window.width = 1200;
  main_window.background_color[0] = 1.0;
  main_window.background_color[1] = 1.0;
  main_window.background_color[2] = 0.0;
  main_window.background_color[3] = 1.0;

  vis_main_window_init(&main_window);

  while (vis_main_window_still_open(&main_window)) {
    vis_main_window_begin_frame(&main_window);
    igShowDemoWindow(NULL);
    vis_main_window_end_frame(&main_window);
  }
}