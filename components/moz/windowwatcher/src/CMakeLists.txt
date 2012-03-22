include(SbLibrary)

project(sbWindowWatcher)

include_directories(
  ${sbXPCOM_SOURCE_DIR})

sb_library_idl_dependencies(
  sbIPrompter
  sbIWindowWatcher)

sb_library_dependencies(
  sbMozThreads)

sb_library(SHARED
  sbWindowWatcher.cpp
  sbWindowWatcherModule.cpp
  ../../xpcom/src/sbWeakReference.cpp)
