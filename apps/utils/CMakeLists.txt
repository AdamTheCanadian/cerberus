project(utils)

include_directories(include)
add_library(${PROJECT_NAME}
        src/program_arguments.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)