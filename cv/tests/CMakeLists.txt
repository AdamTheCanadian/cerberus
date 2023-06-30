project(cv_tests)

add_executable(${PROJECT_NAME}
        main.cpp
        tests_image.cpp
        tests_io.cpp)

target_link_libraries(${PROJECT_NAME}
        cv
        gtest
        pthread)
# This command will run the unit tests as part of the build
add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Running ${PROJECT_NAME} tests"
        POST_BUILD
        COMMAND ${PROJECT_NAME})