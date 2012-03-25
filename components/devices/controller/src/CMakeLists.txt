include(SbLibrary)

project(sbDeviceController)

include_directories(
  ${CMAKE_BINARY_DIR}/components/devices/base/public
  ${CMAKE_BINARY_DIR}/components/devices/controller/public
  ${CMAKE_BINARY_DIR}/components/devices/manager/public
  ${CMAKE_BINARY_DIR}/components/devices/marshall/public
  ${CMAKE_SOURCE_DIR}/components/devices/base/src)

sb_library(STATIC
  sbBaseDeviceController.cpp)

add_dependencies(${PROJECT_NAME}
  sbIDeviceBase2
  sbIDeviceController
  sbIDeviceMarshall)
