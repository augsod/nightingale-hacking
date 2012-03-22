include(SbLibrary)

project(sbLibraryUtils)

include_directories(
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/library/localdatabase/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_BINARY_DIR}/components/devices/base/public
  ${CMAKE_SOURCE_DIR}/components/moz/streams/src
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${CMAKE_SOURCE_DIR}/components/library/base/src
  ${CMAKE_SOURCE_DIR}/components/property/src)

sb_library(STATIC
  sbLibraryUtils.cpp
  sbMediaListEnumSingleItemHelper.cpp
  sbMediaListEnumArrayHelper.cpp)

add_dependencies(${PROJECT_NAME}
  sbILibraryBase
  sbILocalDatabaseLibrary
  sbIProperties
  sbIDeviceBase2)
