include(SbLibrary)

project(sbUpdate)

sb_library(SHARED
  sbDistHelperEnvWriter.cpp
  sbUpdateModule.cpp)
