cmake_minimum_required(VERSION 3.0)
project(inertial)

include_directories(include)
add_library(${PROJECT_NAME}
        src/inertial.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} geodetic)