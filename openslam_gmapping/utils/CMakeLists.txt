include_directories(./)
add_library(gmapping_utils movement.cpp stat.cpp)
install(TARGETS gmapping_utils DESTINATION ${LIB_INSTALL_DIR}
        EXPORT openslam_gmapping)
