cmake_minimum_required(VERSION 3.19)
project(cerberus)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(apps)

add_executable(cerberus main.cpp)