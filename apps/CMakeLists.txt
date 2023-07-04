project(apps)

add_executable(stereo_kitti stereo_kitti/stereo_kitti.c)
target_link_libraries(stereo_kitti utils cv gui)

add_executable(gui_playground gui_playground/main.c)
target_link_libraries(gui_playground utils gui)

add_executable(inertial_simulation inertial_simulation/main.c)
target_link_libraries(inertial_simulation types inertial geodetic gui)