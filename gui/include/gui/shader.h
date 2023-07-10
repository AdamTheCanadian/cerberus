#ifndef CERBERUS_TOP_GUI_INCLUDE_GUI_SHADER_H_
#define CERBERUS_TOP_GUI_INCLUDE_GUI_SHADER_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef uint32_t gui_Shader;

gui_Shader gui_shader_load_from_file(const char *vertexFile,
                                     const char *fragmentFile);

#ifdef __cplusplus
}
#endif
#endif
