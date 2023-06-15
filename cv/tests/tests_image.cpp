#include "gtest/gtest.h"
#include "cv/image.h"
#include "cv/io.h"
#include "tests_image.h"

TEST(cvImageU8, Resize) {
  uint8_t image_buffer[1400 * 1400];

  cv_ImageU8 img;
  img.capacity = 1400 * 1400;
  img.image = image_buffer;

  cv_io_read_imageu8("/Users/adamclare/data/2011_10_03/2011_10_03_drive_0027_sync/image_00/data/0000000000.png",
                     &img);

  uint8_t resize_buffer[1400 * 1400] = {0};
  cv_ImageU8 resized_img;
  resized_img.capacity = 1400 * 1400;
  resized_img.image = resize_buffer;
  resized_img.width = 1035;
  resized_img.height = 314;

  cv_imageu8_resize(&img, &resized_img);

  uint64_t s = resized_img.height * resized_img.width;
  for (uint64_t i = 0; i < s; i++) {
    EXPECT_EQ((int)resized_img.image[i], (int)true_imageu8_resize[i]);
  }
}
