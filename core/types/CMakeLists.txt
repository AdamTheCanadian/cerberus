cmake_minimum_required(VERSION 3.0)
project(types)

include_directories(include)
add_library(${PROJECT_NAME}
        src/rotation_matrix.c
        src/orientation_conversions.c)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} linear_algebra)

add_subdirectory(tests)