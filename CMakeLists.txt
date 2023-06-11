cmake_minimum_required(VERSION 3.19)
project(cerberus)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wconversion")

add_subdirectory(external)

add_subdirectory(utils)
add_subdirectory(apps)