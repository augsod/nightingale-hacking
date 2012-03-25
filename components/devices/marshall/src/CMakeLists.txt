include(SbLibrary)

project(sbDeviceMarshall)

include_directories(
  ${CMAKE_BINARY_DIR}/components/devices/device/public
  ${CMAKE_BINARY_DIR}/components/devices/marshall/public
  ${CMAKE_BINARY_DIR}/components/devices/controller/public
  ${CMAKE_BINARY_DIR}/components/devices/base/public
  ${CMAKE_BINARY_DIR}/components/dbengine/public
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/library/localdatabase/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_SOURCE_DIR}/components/library/localdatabase/src)

sb_library(STATIC
  sbBaseDeviceMarshall.cpp)

add_dependencies(${PROJECT_NAME}
  sbIDevice
  sbIDeviceMarshall
  sbIDeviceController
  sbIDeviceBase2
  sbIDBEngine
  sbILibraryBase
  sbILocalDatabaseLibrary
  sbIProperties)
