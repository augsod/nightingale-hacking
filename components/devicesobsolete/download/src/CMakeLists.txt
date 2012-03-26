include(SbLibrary)
include(SbJSComponent)

project(sbDownloadDevice)

sb_js_component(
  sbAutoDownloader.js
  sbDownloadDeviceHelper.js
  sbDownloadDeviceServicePaneModule.js)

include_directories(
  ${CMAKE_BINARY_DIR}/components/devicesobsolete/base/public
  ${CMAKE_BINARY_DIR}/components/devicesobsolete/download/public
  ${CMAKE_BINARY_DIR}/components/dataremote/public
  ${CMAKE_BINARY_DIR}/components/job/public
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/library/localdatabase/public
  ${CMAKE_BINARY_DIR}/components/mediacore/metadata/manager/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_SOURCE_DIR}/components/devicesobsolete/base/src
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/xpcom/src
  ${CMAKE_SOURCE_DIR}/components/property/src)

sb_library(SHARED
  DownloadDevice.cpp
  DownloadDeviceComponent.cpp)

add_dependencies(${PROJECT_NAME}
  sbIDeviceBase
  sbIDownloadDevice
  sbIDataRemote
  sbIJob
  sbILibraryBase
  sbILocalDatabaseLibrary
  sbIMetadataModule
  sbIProperties)

target_link_libraries(${PROJECT_NAME}
  sbMozStringUtils
  devicebase)