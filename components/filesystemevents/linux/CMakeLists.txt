include(SbLibrary)

project(sbLinuxFileSystemEvents)

find_package(GLIB2)

include_directories(
  ${CMAKE_BINARY_DIR}/components/filesystemevents/base/public
  ${CMAKE_SOURCE_DIR}/components/filesystemevents
  ${CMAKE_SOURCE_DIR}/components/filesystemevents/base/src
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/streams/src
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${GLIB2_INCLUDE_DIR})

sb_library(SHARED
  sbLinuxFileSystemWatcher.cpp
  ../FileSystemComponent.cpp
  ../base/src/sbBaseFileSystemWatcher.cpp
  ../base/src/sbFileSystemNode.cpp
  ../base/src/sbFileSystemTree.cpp
  ../base/src/sbFileSystemTreeState.cpp
  ../base/src/sbFileSystemChange.cpp)

add_dependencies(${PROJECT_NAME}
  sbIFileSystem)

target_link_libraries(${PROJECT_NAME}
  ${GLIB2_LIBRARIES}
  sbMozStreams
  sbMozStringUtils
  sbMozThreads)