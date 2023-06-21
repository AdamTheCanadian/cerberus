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
  double scaleX = (double)src_width / dst_width;
  double scaleY = (double)src_height / dst_height;

  // Iterate over each pixel in the output image
  for (int y = 0; y < dst_height; y++) {
    for (int x = 0; x < dst_width; x++)
    {
      // Calculate the corresponding coordinates in the input image
      double inputX = x * scaleX;
      double inputY = y * scaleY;

      // Perform bilinear interpolation at the calculated coordinates
      unsigned char interpolatedValue = bilinear_interpolate(src,
                                                             inputX,
                                                             inputY);

      // Store the interpolated value in the output image
      dst->image[y * dst_width + x] = interpolatedValue;
    }
  }
}