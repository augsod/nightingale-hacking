include(SbLibrary)

project(sbMozStreams)

include_directories(
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${CMAKE_SOURCE_DIR}/components/moz/uri/src)

sb_library(STATIC
  sbFileObjectStreams.cpp
  sbFileUtils.cpp)
