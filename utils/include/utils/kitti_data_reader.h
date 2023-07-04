#ifndef CERBERUS_UTILS_INCLUDE_UTILS_KITTI_DATA_READER_H_
#define CERBERUS_UTILS_INCLUDE_UTILS_KITTI_DATA_READER_H_

#include <stdint.h>
#include "cv/image.h"

#define KITTI_DATA_READER_MAX_PATH_LENGTH 256

typedef struct {
  char directory[KITTI_DATA_READER_MAX_PATH_LENGTH];
  uint16_t sequence_num;
} KittiDataReader;

void kitti_data_reader_read_stereo(const KittiDataReader *reader,
                                   cv_ImageU8 *left,
                                   cv_ImageU8 *right);

#endif
