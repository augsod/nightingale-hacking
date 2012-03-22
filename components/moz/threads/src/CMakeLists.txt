include(SbLibrary)

project(sbMozThreads)

include_directories(
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src)

sb_library(STATIC
  sbProxiedComponentManager.cpp
  sbThreadUtils.cpp)
