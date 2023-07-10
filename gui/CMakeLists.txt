cmake_minimum_required(VERSION 3.0)
project(gui)

include_directories(include)
add_library(${PROJECT_NAME}
        src/camera3d.c
        src/grid.c
        src/main_window.c
        src/image_window.c
        src/shader.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} linear_algebra glad glfw cimgui cv)