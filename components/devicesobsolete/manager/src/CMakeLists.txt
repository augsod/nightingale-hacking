include(SbLibrary)

project(sbDeviceManager)

include_directories(
  ${CMAKE_BINARY_DIR}/components/devicesobsolete/base/public
  ${CMAKE_BINARY_DIR}/components/devicesobsolete/manager/public
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/library/localdatabase/public
  ${CMAKE_SOURCE_DIR}/components/devicesobsolete/base/src)

sb_library(SHARED
  DeviceManager.cpp
  DeviceManagerComponent.cpp)

add_dependencies(${PROJECT_NAME}
  sbIDeviceBase
  sbIDeviceManager
  sbILibraryBase
  sbILocalDatabaseLibrary)
