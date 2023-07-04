#include <stdio.h>
#include <string.h>
#include "utils/kitti_data_reader.h"
#include "cv/orb.h"
#include "gui/main_window.h"
#include "gui/image_window.h"

cv_OrbFeatureExtractor left_orb;
cv_OrbFeatureExtractor right_orb;

int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("No input directory provided\n");
    printf("Usage: kitti_stereo </path/to/dir");
    return 1;
  }

  cv_orb_feature_extractor_init(&left_orb);
  cv_orb_feature_extractor_init(&right_orb);

  left_orb.num_levels = 8;
  right_orb.num_levels = 8;
  left_orb.scale_factor = 1.2;
  right_orb.scale_factor = 1.2;

  KittiDataReader data_reader;
  data_reader.sequence_num = 0;
  strncpy(data_reader.directory, argv[1], KITTI_DATA_READER_MAX_PATH_LENGTH);

  // Can read the incoming images directly into the first level of the image pyramid,
  // this avoids copying the images.
  kitti_data_reader_read_stereo(&data_reader,
                                &left_orb.image_pyramid[0],
                                &right_orb.image_pyramid[0]);

  cv_orb_feature_extractor_detect(&left_orb);
  cv_orb_feature_extractor_detect(&right_orb);

  gui_MainWindow main_window = {
      .title = "ORB",
      .background_color = {1, 1, 1, 1},
      .width = 1200,
      .height = 1200
  };

  gui_main_window_init(&main_window);

  while (gui_main_window_still_open(&main_window)) {
    gui_main_window_begin_frame(&main_window);

    for (int i = 0; i < 8; i++) {
      gui_ImageU8Window window = {
        .image = &left_orb.image_pyramid[i],
        .window_height = left_orb.image_pyramid[i].height,
        .window_width = left_orb.image_pyramid[i].width};

      snprintf(window.name, 128, "Image %d", i);
      gui_imageu8_window_init(&window);
      gui_imageu8_window_upload(&window);
      gui_imageu8_window_draw(&window);
    }

    gui_main_window_end_frame(&main_window);
  }
  // Compute pyramid
  //  - Define number of levels
  //  - for each level
  //    - Downsize the image by a scale factor
  //    - Add some edge/border factor (19 *2 )
  //    -
}