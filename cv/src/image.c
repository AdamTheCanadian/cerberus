#include "cv/image.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>

static uint8_t bilinear_interpolate(cv_ImageU8 const *img,
                                    double x,
                                    double y) {

  const double w = (double)img->width;
  const double h = (double)img->height;

  static const uint8_t default_return_value = 0;
  if (x < 0 || x >= (w -1)) {
    return default_return_value;
  }
  if (y < 0 || y >= (h - 1)) {
    return default_return_value;
  }

  const double x_floor = floor(x);
  const double x_ceil = ceil(x);
  const double y_floor = floor(y);
  const double y_ceil = ceil(y);

  const double x_fraction = x - x_floor;
  const double y_fraction = y - y_floor;

  const double x1 = 1.0 - x_fraction;
  const double y1 = 1.0 - y_fraction;

  uint64_t temp = (uint64_t)(h * y_floor + x_floor);
  const double tmp1 = x1 *
      (double)(img->image[(uint64_t)(h * y_floor + x_floor)]) +
      x_fraction * (double)(img->image[(uint64_t)(h * y_floor + x_ceil)]);

  const double tmp2 = x1 *
      (double)(img->image[(uint64_t)(h * y_ceil + x_floor)]) +
      x_fraction * (double)(img->image[(uint64_t)(h * y_ceil + x_ceil)]);

  const double tmp3 = y1 * tmp1 + y_fraction * tmp2;
  return (uint8_t)tmp3;
}

void cv_imageu8_resize(cv_ImageU8 const *src,
                       cv_ImageU8 *dst) {
  assert((src != NULL && dst != NULL));
  assert((src->image != NULL && dst->image != NULL));
  assert((dst->height * dst->width) <= dst->capacity);

  const uint64_t src_width = src->width;
  const uint64_t src_height = src->height;
  const uint64_t dst_width = dst->width;
  const uint64_t dst_height = dst->height;
  // Calculate the scaling factors in both dimensions
  const double x_scale = (double)(src_width - 1) / (double)(dst_width - 1);
  const double y_scale = (double)(src_height - 1) / (double)(dst_height - 1);

  // Iterate over each pixel in the output image
  for (int y = 0; y < dst_height; y++) {
    for (int x = 0; x < dst_width; x++) {

      const double x_l = floor(x_scale * x);
      const double x_h = ceil(x_scale * x);
      const double y_l = floor(y_scale * y);
      const double y_h = ceil(y_scale * y);

      const double x_weight = (x_scale * x) - x_l;
      const double y_weight = (y_scale * y) - y_l;

      const uint8_t a = cv_imageu8_at(src, x_l, y_l);
      const uint8_t b = cv_imageu8_at(src, x_h, y_l);
      const uint8_t c = cv_imageu8_at(src, x_l, y_h);
      const uint8_t d = cv_imageu8_at(src, x_h, y_h);

      // Store the interpolated value in the output image
      dst->image[y * dst_width + x] = (uint8_t)(a * (1.0 - x_weight) * (1.0 - y_weight) +
          b * x_weight * (1.0 - y_weight) +
          c * y_weight * (1.0 - x_weight) +
          d * x_weight * y_weight);
    }
  }
}