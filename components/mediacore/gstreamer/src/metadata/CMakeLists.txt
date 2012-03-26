include(SbLibrary)

project(sbMetadataGstreamer)

find_package(GStreamer)

include_directories(
  ${CMAKE_BINARY_DIR}/components/mediacore/metadata/manager/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_BINARY_DIR}/components/mediacore/base/public
  ${CMAKE_BINARY_DIR}/components/mediacore/gstreamer/public
  ${CMAKE_SOURCE_DIR}/components/property/src
  ${CMAKE_SOURCE_DIR}/components/mediacore/base/src
  ${CMAKE_SOURCE_DIR}/components/mediacore/gstreamer/src
  ${GSTREAMER_INCLUDE_DIR})

add_definitions(
  ${GSTREAMER_DEFINITIONS})

sb_library(STATIC
  sbGStreamerMetadataHandler.cpp)

add_dependencies(${PROJECT_NAME}
  sbIMetadataModule
  sbIProperties
  sbIMediacoreBase
  sbIGStreamerMediacore)

target_link_libraries(${PROJECT_NAME}
  ${GSTREAMER_LIBRARIES})
