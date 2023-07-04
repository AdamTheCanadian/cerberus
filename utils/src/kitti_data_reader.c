#include "utils/kitti_data_reader.h"
#include <stdio.h>
#include <assert.h>

#define STB_IMAGE_IMPLEMENTATION
#include "utils/stb_image.h"

void kitti_data_reader_read_stereo(const KittiDataReader *reader,
                                   cv_ImageU8 *left,
                                   cv_ImageU8 *right) {
  stbi_set_flip_vertically_on_load(1);

  // Kitti image files are stored as 10 character long file names, where the file name
  // is something like 0000001234.png where 1234 is the sequence number, padded with some zeros
  // So we need 10 characters + 4 for the '.png' plus 1 for '\0'
  char seq_buffer[15];
  snprintf(seq_buffer, 15, "%010d.png", reader->sequence_num);

  // Need a larger buffer to hold the directory + 'image_00/data/0000001234.png'
  static const size_t buffer_size = KITTI_DATA_READER_MAX_PATH_LENGTH + 50;
  char left_image_buffer[buffer_size];
  char right_image_buffer[buffer_size];

  snprintf(left_image_buffer, buffer_size, "%s/image_00/data/%s", reader->directory, seq_buffer);
  snprintf(right_image_buffer, buffer_size, "%s/image_01/data/%s", reader->directory, seq_buffer);

  int image_resolution_x = 0;
  int image_resolution_y = 0;
  int num_channels = 0;
  uint8_t *tmp_left = stbi_load(left_image_buffer, &image_resolution_x, &image_resolution_y, &num_channels, 1);
  printf("num_channels %d\n", num_channels);
  assert(num_channels == 1);
  assert((image_resolution_x * image_resolution_y) < (int)left->capacity);

  uint8_t *tmp_right = stbi_load(right_image_buffer, &image_resolution_x, &image_resolution_y, &num_channels, 1);
  printf("num_channels %d\n", num_channels);
  assert(num_channels == 1);
  assert((image_resolution_x * image_resolution_y) < (int)right->capacity);

  memcpy(left->image, tmp_left, image_resolution_x * image_resolution_y);
  left->width = image_resolution_x;
  left->height = image_resolution_y;
  memcpy(right->image, tmp_right, image_resolution_x * image_resolution_y);
  right->width = image_resolution_x;
  right->height = image_resolution_y;

  stbi_image_free(tmp_left);
  stbi_image_free(tmp_right);
}