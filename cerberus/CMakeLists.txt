cmake_minimum_required(VERSION 3.0)
project(cerberus)

include_directories(include)
add_library(${PROJECT_NAME}
        src/orb.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)


add_executable(${PROJECT_NAME}_tests
        tests/main.cpp)

target_link_libraries(${PROJECT_NAME}_tests
        cerberus
        gtest
        pthread)
# This command will run the unit tests as part of the build
add_custom_command(
        TARGET ${PROJECT_NAME}_tests
        COMMENT "Run tests"
        POST_BUILD
        COMMAND ${PROJECT_NAME}_tests)