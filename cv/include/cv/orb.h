#ifndef CERBERUS_TOP_CV_INCLUDE_CV_ORB_H_
#define CERBERUS_TOP_CV_INCLUDE_CV_ORB_H_
#ifdef __cplusplus
#extern "C" {
#endif

#include "cv/image.h"

#define ORB_MAX_IMAGE_WIDTH 1400
#define ORB_MAX_IMAGE_HEIGHT 600
// The max number of levels for detecting orb features, needed for the image pyramid(s)
#define ORB_MAX_LEVELS 10

typedef struct {
  cv_ImageU8 image_pyramid[ORB_MAX_LEVELS];
  uint8_t image_buffer[ORB_MAX_LEVELS][ORB_MAX_IMAGE_WIDTH * ORB_MAX_IMAGE_HEIGHT];
  // The scale factor for each level of the pyramid
  double scale_factor;
  // The actual number of levels to use, must be <= ORB_MAX_LEVELS
  int num_levels;
} cv_OrbFeatureExtractor;

void cv_orb_feature_extractor_init(cv_OrbFeatureExtractor *orb);

void cv_orb_feature_extractor_detect(cv_OrbFeatureExtractor *orb);

#ifdef __cplusplus
}
#endif

#endif
