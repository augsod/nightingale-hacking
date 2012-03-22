include(SbLibrary)

project(sbXPCOM)

include_directories(
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${CMAKE_BINARY_DIR}/components/moz/xpcom/public)

sb_library(SHARED
  sbCOMArray.cpp
  sbArray.cpp
  sbPropertyBag.cpp
  sbServiceManager.cpp
  sbWeakReference.cpp
  sbXPCOMModule.cpp)

add_dependencies(${PROJECT_NAME}
  sbIXPCOM)

target_link_libraries(${PROJECT_NAME}
  sbMozThreads)
