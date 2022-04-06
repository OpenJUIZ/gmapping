add_library(gmapping_sensor_range rangereading.cpp rangesensor.cpp)
target_link_libraries(gmapping_sensor_range gmapping_sensor_base)

install(TARGETS gmapping_sensor_range DESTINATION ${LIB_INSTALL_DIR}
	EXPORT openslam_gmapping)
