add_library(gmapping_gridfastslam
    gfsreader.cpp
    gridslamprocessor.cpp
    gridslamprocessor_tree.cpp
    motionmodel.cpp
)
target_link_libraries(gmapping_gridfastslam gmapping_scanmatcher gmapping_sensor_range)

install(TARGETS gmapping_gridfastslam DESTINATION ${LIB_INSTALL_DIR}
        EXPORT openslam_gmapping)
