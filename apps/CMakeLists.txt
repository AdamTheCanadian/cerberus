project(apps)

add_executable(stereo_kitti stereo_kitti.c)
target_link_libraries(stereo_kitti utils)