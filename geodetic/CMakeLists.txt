cmake_minimum_required(VERSION 3.0)
project(geodetic)

include_directories(include)
add_library(${PROJECT_NAME}
        src/geodetic.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(tests)