#ifndef CERBERUS_TOP_CERBERUS_INCLUDE_CERBERUS_IMAGE_H_
#define CERBERUS_TOP_CERBERUS_INCLUDE_CERBERUS_IMAGE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct ImageGrey {
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
} ImageGrey;

#ifdef __cplusplus
}
#endif
#endif
