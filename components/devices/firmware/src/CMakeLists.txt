include(SbLibrary)
include(SbJSComponent)

project(sbDeviceFirmwareUpdater)

sb_js_component(
  sbDeviceFirmwareAutoCheckForUpdate.js)

include_directories(
  ${CMAKE_BINARY_DIR}/components/devices/base/public
  ${CMAKE_BINARY_DIR}/components/devices/device/public
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/library/localdatabase/public
  ${CMAKE_BINARY_DIR}/components/moz/filedownloader/public
  ${CMAKE_BINARY_DIR}/components/moz/prompter/public
  ${CMAKE_BINARY_DIR}/components/moz/strings/components/public
  ${CMAKE_BINARY_DIR}/components/moz/windowwatcher/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_SOURCE_DIR}/components/devices/base/src
  ${CMAKE_SOURCE_DIR}/components/library/base/src/static
  ${CMAKE_SOURCE_DIR}/components/library/localdatabase/src/
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${CMAKE_SOURCE_DIR}/components/property/src)

sb_library(SHARED
  sbDeviceFirmwareDownloader.cpp
  sbDeviceFirmwareModule.cpp
  sbDeviceFirmwareSupport.cpp
  sbDeviceFirmwareUpdate.cpp
  sbDeviceFirmwareUpdater.cpp
  sbBaseDeviceFirmwareHandler.cpp)

add_dependencies(${PROJECT_NAME}
  sbIDeviceBase2
  sbIDevice
  sbILibraryBase
  sbILocalDatabaseLibrary
  sbIFileDownloader
  sbIPrompter
  sbIStrings
  sbIWindowWatcher
  sbIProperties)
