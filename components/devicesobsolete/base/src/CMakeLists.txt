include(SbLibrary)

project(devicebase)

include_directories(
  ${CMAKE_BINARY_DIR}/components/devicesobsolete/base/public
  ${CMAKE_BINARY_DIR}/components/dbengine/public
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/library/localdatabase/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_SOURCE_DIR}/components/property/src
  ${CMAKE_SOURCE_DIR}/components/library/localdatabase/src)

sb_library(STATIC
  DeviceBase.cpp)

add_dependencies(${PROJECT_NAME}
  sbIDeviceBase
  sbIDBEngine
  sbILibraryBase
  sbILocalDatabaseLibrary
  sbIProperties)
