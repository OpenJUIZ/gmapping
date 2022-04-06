add_library(gmapping_sensor_odometry odometryreading.cpp odometrysensor.cpp)
target_link_libraries(gmapping_sensor_odometry gmapping_sensor_base)

install(TARGETS gmapping_sensor_odometry DESTINATION ${LIB_INSTALL_DIR}
        EXPORT openslam_gmapping)
