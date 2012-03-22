include(SbLibrary)

project(sbWindowWatcher)

include_directories(
  ${CMAKE_BINARY_DIR}/components/moz/prompter/public
  ${CMAKE_BINARY_DIR}/components/moz/windowwatcher/public
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${CMAKE_SOURCE_DIR}/components/moz/xpcom/src)

sb_library(SHARED
  sbWindowWatcher.cpp
  sbWindowWatcherModule.cpp
  ../../xpcom/src/sbWeakReference.cpp)

add_dependencies(${PROJECT_NAME}
  sbIPrompter
  sbIWindowWatcher)

target_link_libraries(${PROJECT_NAME}
  sbMozThreads)