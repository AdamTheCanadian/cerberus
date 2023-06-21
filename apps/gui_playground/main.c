/**
* \file This is just a test application used for gui development
*/

#include "utils/kitti_data_reader.h"
#include "gui/main_window.h"
#include "gui/image_window.h"
#include "cv/image.h"
#include "cv/io.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  gui_MainWindow main_window;
  strncpy(main_window.title, "GUI Test", GUI_MAIN_WINDOW_TITLE_MAX_LENGTH);
  main_window.height = 800;
  main_window.width = 1200;
  main_window.background_color[0] = 1.0;
  main_window.background_color[1] = 1.0;
  main_window.background_color[2] = 0.0;
  main_window.background_color[3] = 1.0;

  gui_main_window_init(&main_window);
  uint8_t image_buffer[1400 * 1400];
  cv_ImageU8 img;
  img.capacity = 1400 * 1400;
  img.image = image_buffer;

  cv_io_read_imageu8("/Users/adamclare/data/2011_10_03/2011_10_03_drive_0027_sync/image_00/data/0000000000.png",
                     &img);

  gui_ImageU8Window image_window;
  image_window.image = &img;

  gui_imageu8_window_init(&image_window);
  gui_imageu8_window_upload(&image_window);

  while (gui_main_window_still_open(&main_window)) {
    gui_main_window_begin_frame(&main_window);
    gui_imageu8_window_draw(&image_window);
    igShowDemoWindow(NULL);
    gui_main_window_end_frame(&main_window);
  }
}