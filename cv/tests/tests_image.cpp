#include "gtest/gtest.h"
#include "cv/image.h"
#include "cv/io.h"
#include "tests_image.h"

TEST(cvImageU8, At) {
  uint8_t image_buffer[] = {
      1, 2, 3, 4,
      5, 6, 7, 8,
      9, 10, 11, 12};
  cv_ImageU8 img;
  img.height = 3;
  img.width = 4;
  img.capacity = 12;
  img.image = image_buffer;

  EXPECT_EQ(cv_imageu8_at(&img, 1, 1), 6);
  EXPECT_EQ(cv_imageu8_at(&img, 3, 2), 12);
}

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
  resized_img.width = 1034;
  resized_img.height = 313;

  cv_imageu8_resize(&img, &resized_img);

  uint64_t s = resized_img.height * resized_img.width;
  for (uint64_t i = 0; i < s; i++) {
    EXPECT_EQ((int)resized_img.image[i], (int)true_imageu8_resize[i]) << "i: " << i << std::endl;
  }
}
