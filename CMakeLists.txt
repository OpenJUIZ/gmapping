message("---------------------- GridMapping project --------------------------")

cmake_minimum_required(VERSION 3.10)

project(GridMapping LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CONTAINERS GridMapping)
set(CONTAINER_OPERATIONS GridMapping_getMap GridMapping_resetMap GridMapping_setSensorReading GridMapping_updateMap GridMapping_updatePose GridMapping_getPose)
set(OPERATIONS)

find_package(juiz)

message("- juiz_ROOT_DIR   : " ${juiz_ROOT_DIR})
message("- juiz_INCLUDE_DIR: " ${juiz_INCLUDE_DIR})
message("- juiz_LIB_DIR    : " ${juiz_LIB_DIR})
message("- juiz_LIBRARIES  : " ${juiz_LIBRARIES})


include(juiz_component.cmake)

set(JUIZ_LIBS ${juiz_LIBRARIES})
set(EXT_LIBS gmapping_gridfastslam)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${juiz_INCLUDE_DIR})


link_directories(${juiz_LIB_DIR})

# Output basic information of this project.
message("- CMakeLists.txt    : " ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt)
message("- JUIZ_LIBS         : " ${JUIZ_LIBS})
message("- EXT_LIBS          : " ${EXT_LIBS})

# ----- IMPLEMENTATION AREA ------

# Add projects to target
add_containers(CONTAINERS)
add_container_operations(CONTAINER_OPERATIONS)
add_operations(OPERATIONS)

# Define modules for install
set(GMAPPING_MODULES ${OPERATIONS} ${CONTAINERS} ${ECS} PARENT_SCOPE)

# Installing files for targets
INSTALL(TARGETS ${CONTAINERS} ${CONTAINER_OPERATIONS} ${OPERATIONS} DESTINATION ${juiz_ROOT_DIR}/share/juiz/components/GridMapping)
INSTALL(FILES GridMapping.jshelf DESTINATION ${juiz_ROOT_DIR}/share/juiz/components/GridMapping)



message("-----------------------------------------------------------------------")
