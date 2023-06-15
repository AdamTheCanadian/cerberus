#include "cv/image.h"
#include <assert.h>
#include <stdlib.h>

void cv_imageu8_resize(cv_ImageU8 const *src,
                       cv_ImageU8 *dst) {
  assert((src != NULL && dst != NULL));
  assert((src->image != NULL && dst->image != NULL));
  assert((dst->height * dst->width) <= dst->capacity);

  const uint64_t src_width = src->width;
  const uint64_t src_height = src->height;
  const uint64_t dst_width = dst->width;
  const uint64_t dst_height = dst->height;
  // Calculate the ratio between source and destination widths/heights
  uint64_t x_ratio = (uint64_t)((src_width << 16) / dst_width) + 1;
  uint64_t y_ratio = (uint64_t)((src_height << 16) / dst_height) + 1;

  uint64_t x2, y2, x, y, index;
  uint8_t a, b, c, d;

  // Iterate over each pixel in the destination image
  for (uint64_t i = 0; i < dst->height; i++) {
    for (uint64_t j = 0; j < dst->width; j++) {
      // Calculate the corresponding position in the source image
      x = ((j * x_ratio) >> 16);
      y = ((i * y_ratio) >> 16);
      x2 = (x == src_width - 1) ? x : x + 1;
      y2 = (y == src_height - 1) ? y : y + 1;
      index = (y * src_width) + x;

      // Perform linear interpolation between neighboring pixels
      a = src->image[index];
      b = src->image[index + 1];
      c = src->image[index + src_width];
      d = src->image[index + src_width + 1];

      uint8_t val =  (uint8_t)(
          ((a * (x2 - x) * (y2 - y)) + (b * (x - x2) * (y2 - y)) + (c * (x2 - x) * (y - y2)) + (d * (x - x2) * (y - y2))) >> 16;
      dst->image[(i * dst_width) + j] = (uint8_t)(
          ((a * (x2 - x) * (y2 - y)) + (b * (x - x2) * (y2 - y)) + (c * (x2 - x) * (y - y2)) + (d * (x - x2) * (y - y2))) >> 16
      );
    }
  }
}