#include "cv/io.h"
#include <assert.h>

#define STB_IMAGE_IMPLEMENTATION
#include "cv/stb_image.h"

void cv_io_read_imageu8(const char *filename,
                        cv_ImageU8 *dst) {
  assert(filename != NULL);
  assert(dst != NULL);
  assert(dst->image != NULL);

  int image_resolution_x = 0;
  int image_resolution_y = 0;
  int num_channels = 0;

  stbi_set_flip_vertically_on_load(0);
  uint8_t *tmp = stbi_load(filename, &image_resolution_x, &image_resolution_y, &num_channels, 1);

  const uint64_t capacity = (uint64_t)image_resolution_x * (uint64_t)image_resolution_y;
  // Need to check capacity before asserting so we can free image before asserting
  if (capacity > dst->capacity) {
    stbi_image_free(tmp);
    assert(capacity <= dst->capacity);
  }

  memcpy(dst->image, tmp, image_resolution_x * image_resolution_y);
  dst->height = (uint64_t)image_resolution_y;
  dst->width = (uint64_t)image_resolution_x;
  stbi_image_free(tmp);
}