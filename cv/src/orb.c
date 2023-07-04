#include "cv/orb.h"

void cv_orb_feature_extractor_init(cv_OrbFeatureExtractor *orb) {
  // Setup the image pyramids
  for (int i = 0; i < ORB_MAX_LEVELS; i++) {
    orb->image_pyramid[i].capacity = ORB_MAX_IMAGE_HEIGHT * ORB_MAX_IMAGE_WIDTH;
    orb->image_pyramid[i].image = orb->image_buffer[i];
  }
}

void cv_orb_feature_extractor_detect(cv_OrbFeatureExtractor *orb) {

  const double inv_scale = 1.0 / orb->scale_factor;
  // first need to generate the image pyramid, we assume the first level of the pyramid
  // is already set to the image that features are being detected in
  for (int i = 1; i < orb->num_levels; i++) {
    orb->image_pyramid[i].height = (uint64_t)(inv_scale * (double)orb->image_pyramid[i - 1].height);
    orb->image_pyramid[i].width = (uint64_t)(inv_scale * (double)orb->image_pyramid[i - 1].width);
    cv_imageu8_resize(&orb->image_pyramid[i - 1], &orb->image_pyramid[i]);
  }
}