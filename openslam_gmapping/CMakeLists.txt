cmake_minimum_required(VERSION 2.8)
project(openslam_gmapping)


if(WIN32 AND NOT CYGWIN)
  set(INC_INSTALL_DIR "/gmapping/include")
  set(LIB_INSTALL_DIR "/gmapping/lib")
else()
  set(INC_INSTALL_DIR "/usr/local/include")
  set(LIB_INSTALL_DIR "/usr/local/lib")
endif()



include_directories(include)

add_subdirectory(utils)
add_subdirectory(sensor)
add_subdirectory(gridfastslam)
add_subdirectory(scanmatcher)

install(DIRECTORY include/
   DESTINATION ${INC_INSTALL_DIR}
   FILES_MATCHING PATTERN "*.h"
                  PATTERN "*.hxx"
   PATTERN ".svn" EXCLUDE
)
install(
   EXPORT openslam_gmapping DESTINATION ${LIB_INSTALL_DIR}
)
