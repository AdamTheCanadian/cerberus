cmake_minimum_required(VERSION 3.0)
project(linear_algebra)

include_directories(include)
add_library(${PROJECT_NAME}
        src/matrix3d.c
        src/matrix4f.c
        src/vector3d.c
        src/vector3f.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(tests)