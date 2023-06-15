cmake_minimum_required(VERSION 3.0)
project(cv)

include_directories(include)
add_library(${PROJECT_NAME}
        src/image.c
        src/io.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(tests)