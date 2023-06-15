#include <stdio.h>
#include <string.h>
#include "utils/kitti_data_reader.h"
#include "vis/main_window.h"
// Most KITTI data sets contain images in the range of 1200-1400 x 300-500
#define MAX_IMAGE_WIDTH 1400
#define MAX_IMAGE_HEIGHT 600
// The max number of levels for detecting orb features, needed for the image pyramid(s)
#define MAX_ORB_LEVELS 10

uint8_t image_pyramid_buffer[MAX_ORB_LEVELS][MAX_IMAGE_WIDTH * MAX_IMAGE_HEIGHT];

int main(int argc, char *argv[]) {

  vis_MainWindow main_window;
  strncpy(main_window.title, "Stereo Kitti", VIS_MAIN_WINDOW_TITLE_MAX_LENGTH);
  main_window.height = 800;
  main_window.width = 1200;
  main_window.background_color[0] = 1.0;
  main_window.background_color[1] = 1.0;
  main_window.background_color[2] = 0.0;
  main_window.background_color[3] = 1.0;

  vis_main_window_init(&main_window);

  while (vis_main_window_still_open(&main_window)) {
    vis_main_window_begin_frame(&main_window);
    vis_main_window_end_frame(&main_window);
  }

  if (argc < 2) {
    printf("No input directory provided\n");
    printf("Usage: kitti_stereo </path/to/dir");
    return 1;
  }

  KittiDataReader data_reader;
  data_reader.sequence_num = 0;
  strncpy(data_reader.directory, argv[1], KITTI_DATA_READER_MAX_PATH_LENGTH);

  uint8_t left_image[1392 * 512] = {0};
  uint8_t right_image[1392 * 512] = {0};
  kitti_data_reader_read_stereo(&data_reader, left_image, right_image);

  // Compute pyramid
  //  - Define number of levels
  //  - for each level
  //    - Downsize the image by a scale factor
  //    - Add some edge/border factor (19 *2 )
  //    -
}