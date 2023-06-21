#include <stdio.h>
#include <string.h>
#include "utils/kitti_data_reader.h"
// Most KITTI data sets contain images in the range of 1200-1400 x 300-500
#define MAX_IMAGE_WIDTH 1400
#define MAX_IMAGE_HEIGHT 600
// The max number of levels for detecting orb features, needed for the image pyramid(s)
#define MAX_ORB_LEVELS 10

uint8_t image_pyramid_buffer[MAX_ORB_LEVELS][MAX_IMAGE_WIDTH * MAX_IMAGE_HEIGHT];

int main(int argc, char *argv[]) {

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