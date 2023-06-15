project(apps)

add_executable(stereo_kitti stereo_kitti/stereo_kitti.c)
target_link_libraries(stereo_kitti utils vis)

add_executable(gui_playground gui_playground/main.c)
target_link_libraries(gui_playground utils vis)