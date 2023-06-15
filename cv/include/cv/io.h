#ifndef CERBERUS_TOP_CV_INCLUDE_CV_IO_H_
#define CERBERUS_TOP_CV_INCLUDE_CV_IO_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "cv/image.h"

/**
 * Read an image from disk
 * This will allocate memory temporarily and then release it, until a better way is found...
 * \param filename /path/to/some/image.png
 * \param dst where image data will be set into
 */
void cv_io_read_imageu8(const char *filename,
                        cv_ImageU8 *dst);

#ifdef __cplusplus
}
#endif
#endif
