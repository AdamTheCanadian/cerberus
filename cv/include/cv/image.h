#ifndef CERBERUS_TOP_CV_INCLUDE_CV_IMAGE_H_
#define CERBERUS_TOP_CV_INCLUDE_CV_IMAGE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * Single channel 8 bit image, typically used for greyscale/intensity images
 */
typedef struct {
  // This is width * height, the max number of bytes that *image can hold.
  // This allows an image to be pre-allocated and repurposed/resized, as long as
  // the size is <= capacity
  uint64_t capacity;
  // The current width of image
  uint64_t width;
  // The current height of image
  uint64_t height;
  // Image is represented as a 1D array of size [width * height]
  uint8_t *image;
} cv_ImageU8;

/**
 * Resize a image
 * Uses the width x height of src and width x height of dst to define scaling factors
 * \param src the source image being resized
 * \param dst the resized source image
 */
void cv_imageu8_resize(cv_ImageU8 const *src,
                       cv_ImageU8 *dst);

static inline uint8_t cv_imageu8_at(cv_ImageU8 const *img,
                                    int col,
                                    int row) {
  return img->image[(int)img->width * row + col];
}

#ifdef __cplusplus
}
#endif
#endif
