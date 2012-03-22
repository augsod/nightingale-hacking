include(SbLibrary)

project(sbPrompter)

sb_library_idl_dependencies(
  sbIPrompter
  sbIWindowWatcher)

sb_library(SHARED
  sbPrompter.cpp
  sbPrompterModule.cpp)
