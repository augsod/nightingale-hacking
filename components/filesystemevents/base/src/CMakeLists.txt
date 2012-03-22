include(SbLibrary)

project(sbFileSystemEventsBase)

include_directories(
  ${CMAKE_BINARY_DIR}/components/filesystemevents/base/public
  ${CMAKE_SOURCE_DIR}/components/filesystemevents
  ${CMAKE_SOURCE_DIR}/components/moz/streams/src
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src)

sb_library(SHARED
  sbFileSystemNode.cpp
  sbFileSystemTree.cpp
  sbFileSystemTreeState.cpp
  sbBaseFileSystemWatcher.cpp
  sbFileSystemChange.cpp)

add_dependencies(${PROJECT_NAME}
  sbIFileSystem)

target_link_libraries(${PROJECT_NAME}
  sbMozStreams
  sbMozStringUtils
  sbMozThreads)