include(SbLibrary)

project(sbThreadPoolService)

sb_library(SHARED
  sbThreadPoolService.cpp
  sbThreadPoolServiceModule.cpp)
