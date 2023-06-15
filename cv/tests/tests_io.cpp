#include "gtest/gtest.h"
#include "cv/io.h"
#include "tests_io.h"

TEST(cvIO, ReadU8) {
  uint8_t image_buffer[1400 * 1400];

  cv_ImageU8 img;
  img.capacity = 1400 * 1400;
  img.image = image_buffer;

  cv_io_read_imageu8("/Users/adamclare/data/2011_10_03/2011_10_03_drive_0027_sync/image_00/data/0000000000.png",
                     &img);
  EXPECT_EQ(img.width, 1241);
  EXPECT_EQ(img.height, 376);

  uint64_t s = img.height * img.width;
  for (uint64_t i = 0; i < s; i++) {
      EXPECT_EQ((int)img.image[i], (int)true_read_u8[i]);
  }
}