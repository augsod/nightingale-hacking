include(SbLibrary)

project(sbMozThreads)

sb_library(STATIC
  sbProxiedComponentManager.cpp
  sbThreadUtils.cpp)
