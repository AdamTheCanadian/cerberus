cmake_minimum_required(VERSION 3.0)
project(utils)

include_directories(include)
add_library(${PROJECT_NAME}
        src/kitti_data_reader.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} cv)