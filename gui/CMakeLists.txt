cmake_minimum_required(VERSION 3.0)
project(gui)

include_directories(include)
add_library(${PROJECT_NAME}
        src/main_window.c
        src/image_window.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} glad glfw cimgui cv)