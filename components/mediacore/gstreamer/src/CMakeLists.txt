include(SbJSComponent)

add_subdirectory(metadata)

sb_js_component(
  sbAboutGStreamer.js)

project(sbGStreamerMediacore)

find_package(GStreamer)
#TODO: is this only required on linux?
find_package(GTK2)

include_directories(
  ${CMAKE_BINARY_DIR}/components/devices/base/public
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/mediacore/base/public
  ${CMAKE_BINARY_DIR}/components/mediacore/gstreamer/public
  ${CMAKE_BINARY_DIR}/components/mediacore/metadata/manager/public
  ${CMAKE_BINARY_DIR}/components/mediacore/transcode/public
  ${CMAKE_BINARY_DIR}/components/moz/strings/components/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_BINARY_DIR}/components/job/public
  ${CMAKE_SOURCE_DIR}/components/job/src
  ${CMAKE_SOURCE_DIR}/components/mediacore/base/src
  ${CMAKE_SOURCE_DIR}/components/mediacore/gstreamer/src
  ${CMAKE_SOURCE_DIR}/components/mediacore/transcode/src
  ${CMAKE_SOURCE_DIR}/components/moz/streams/src
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${CMAKE_SOURCE_DIR}/components/property/src
  ${CMAKE_SOURCE_DIR}/components/moz/errorconsole/src
  ${GTK2_INCLUDE_DIRS}
  ${GSTREAMER_INCLUDE_DIR})

add_definitions(
  ${GSTREAMER_DEFINITIONS})

set(sources
  sbGStreamerService.cpp
  sbGStreamerAudioProcessor.cpp
  sbGStreamerMediaContainer.cpp
  sbGStreamerMediacore.cpp
  sbGStreamerMediacoreFactory.cpp
  sbGStreamerMediacoreModule.cpp
  sbGStreamerMediacoreUtils.cpp
  sbGStreamerMediaInspector.cpp
  sbGStreamerPlatformBase.cpp
  sbGStreamerPipeline.cpp
  sbGStreamerRTPStreamer.cpp
  sbGStreamerTranscode.cpp
  sbGStreamerVideoTranscode.cpp
  sbGStreamerTranscodeAudioConfigurator.cpp
  sbGStreamerTranscodeDeviceConfigurator.cpp
  ../../base/src/sbBaseMediacore.cpp
  ../../base/src/sbBaseMediacoreEventTarget.cpp
  ../../base/src/sbBaseMediacoreFactory.cpp
  ../../base/src/sbBaseMediacorePlaybackControl.cpp
  ../../base/src/sbBaseMediacoreVolumeControl.cpp
  ../../base/src/sbBaseMediacoreMultibandEqualizer.cpp
  ../../base/src/sbMediacoreCapabilities.cpp
  ../../base/src/sbMediacoreEvent.cpp
  ../../base/src/sbMediacoreEqualizerBand.cpp
  ../../base/src/sbMediacoreError.cpp
  ../../base/src/sbVideoBox.cpp
  ../../transcode/src/sbTranscodingConfigurator.cpp)

if(UNIX)
  set(sources ${sources}
    sbGStreamerPlatformGDK.cpp)
endif()

sb_library(SHARED ${sources})

add_dependencies(${PROJECT_NAME}
  sbIDeviceBase2
  sbILibraryBase
  sbIMediacoreBase
  sbIGStreamerMediacore
  sbIMetadataModule
  sbITranscodeModule
  sbIStrings
  sbIProperties
  sbIJob)

target_link_libraries(${PROJECT_NAME}
  sbMozStringUtils
  sbMozThreads
  sbErrorConsole
  ${GTK2_LIBRARIES}
  ${GSTREAMER_LIBRARIES})
