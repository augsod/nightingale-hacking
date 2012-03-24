include(SbLibrary)

project(sbTranscodeModule)

include_directories(
  ${CMAKE_BINARY_DIR}/components/albumart/public
  ${CMAKE_BINARY_DIR}/components/devices/base/public
  ${CMAKE_BINARY_DIR}/components/job/public
  ${CMAKE_BINARY_DIR}/components/mediacore/base/public
  ${CMAKE_BINARY_DIR}/components/mediacore/metadata/manager/public
  ${CMAKE_BINARY_DIR}/components/mediacore/transcode/public
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${CMAKE_SOURCE_DIR}/components/property/src)

sb_library(SHARED
  sbTranscodeAlbumArt.cpp
  sbTranscodeError.cpp
  sbTranscodeManager.cpp
  sbTranscodeModule.cpp
  sbTranscodeProfile.cpp
  sbTranscodeProfileLoader.cpp
  sbTranscodeProfileProperty.cpp
  sbTranscodeProfileAttribute.cpp
  sbImageTools.cpp
  sbTranscodingConfigurator.cpp)

add_dependencies(${PROJECT_NAME}
  sbIAlbumArt
  sbIDeviceBase2
  sbIJob
  sbIMediacoreBase
  sbIMetadataModule
  sbITranscodeModule
  sbILibraryBase
  sbIProperties)

target_link_libraries(${PROJECT_NAME}
  sbMozStringUtils
  sbMozThreads)