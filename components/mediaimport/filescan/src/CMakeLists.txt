include(SbLibrary)

project(sbFileScan)

include_directories(
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/mediaimport/filescan/public
  ${CMAKE_BINARY_DIR}/components/moz/fileutils/public)

sb_library(SHARED
  sbFileScan.cpp
  sbFileScanComponent.cpp)

add_dependencies(${PROJECT_NAME}
  sbILibraryBase
  sbIFileScan
  sbIFileUtils)
