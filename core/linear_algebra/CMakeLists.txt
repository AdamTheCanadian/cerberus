cmake_minimum_required(VERSION 3.0)
project(linear_algebra)

include_directories(include)
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)