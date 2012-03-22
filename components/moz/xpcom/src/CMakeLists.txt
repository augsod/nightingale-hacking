include(SbLibrary)

project(sbXPCOM)

sb_library_dependencies(
  sbMozThreads)

sb_library_idl_dependencies(
  sbIXPCOM)

sb_library(SHARED
  sbCOMArray.cpp
  sbArray.cpp
  sbPropertyBag.cpp
  sbServiceManager.cpp
  sbWeakReference.cpp
  sbXPCOMModule.cpp)
