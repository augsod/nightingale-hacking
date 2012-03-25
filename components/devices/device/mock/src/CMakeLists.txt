include(SbLibrary)

project(sbDeviceDeviceTester)

include_directories(
  ${CMAKE_BINARY_DIR}/components/devices/device/mock/public
  ${CMAKE_BINARY_DIR}/components/devices/base/public
  ${CMAKE_BINARY_DIR}/components/devices/device/public
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/library/localdatabase/public
  ${CMAKE_BINARY_DIR}/components/mediacore/transcode/public
  ${CMAKE_BINARY_DIR}/components/moz/prompter/public
  ${CMAKE_BINARY_DIR}/components/moz/temporaryfileservice/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_SOURCE_DIR}/components/devices/base/src
  ${CMAKE_SOURCE_DIR}/components/devices/device/src
  ${CMAKE_SOURCE_DIR}/components/library/base/src/static
  ${CMAKE_SOURCE_DIR}/components/library/base/src
  ${CMAKE_SOURCE_DIR}/components/library/localdatabase/src
  ${CMAKE_SOURCE_DIR}/components/moz/errorconsole/src
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${CMAKE_SOURCE_DIR}/components/moz/xpcom/src
  ${CMAKE_SOURCE_DIR}/components/property/src)

sb_library(SHARED
  sbDeviceDeviceTesterModule.cpp
  sbDeviceDeviceTesterUtils.cpp
  sbMockDevice.cpp
  ../../../base/src/sbBaseDeviceEventTarget.cpp
  ../../../base/src/sbDeviceEvent.cpp
  ../../../base/src/sbDeviceLibrary.cpp
  ../../../base/src/sbDeviceLibraryHelpers.cpp
  ../../../base/src/sbDeviceLibraryMediaSyncSettings.cpp
  ../../../base/src/sbDeviceLibrarySyncSettings.cpp
  ../../../base/src/sbDeviceContent.cpp
  ../../../base/src/sbDeviceProperties.cpp)

add_dependencies(${PROJECT_NAME}
  sbIDeviceDeviceTester
  sbIDeviceBase2
  sbIDevice
  sbILibraryBase
  sbILocalDatabseLibrary
  sbITranscodeModule
  sbIPrompter
  sbITemporaryFileService
  sbIProperties)

target_link_libraries(${PROJECT_NAME}
  sbDeviceCore
  sbLibraryUtils
  sbErrorConsole
  sbMozStreams
  sbMozStringUtils
  sbMozThreads
  sbMozVariantUtils)
