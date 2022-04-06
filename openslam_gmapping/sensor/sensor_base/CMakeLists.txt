include_directories(./)
add_library(gmapping_sensor_base sensor.cpp sensorreading.cpp)
install(TARGETS gmapping_sensor_base DESTINATION ${LIB_INSTALL_DIR}
        EXPORT openslam_gmapping)
