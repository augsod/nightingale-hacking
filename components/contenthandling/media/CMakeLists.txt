include(SbLibrary)
include(SbJSComponent)

project(sbMediaSniffer)

sb_js_component(
  sbMediaContentListener.js)

include_directories(
  ${CMAKE_BINARY_DIR}/components/mediacore/base/public
  ${CMAKE_BINARY_DIR}/components/mediaimport/playlist/public)

sb_library(SHARED
  sbMediaSniffer.cpp
  sbMediaSnifferModule.cpp)

add_dependencies(${PROJECT_NAME}
  sbIMediacoreBase
  sbIPlaylistReader)
