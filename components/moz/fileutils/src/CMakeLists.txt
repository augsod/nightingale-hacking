include(SbLibrary)

project(sbFileUtils)

include_directories(
  ${CMAKE_BINARY_DIR}/components/moz/fileutils/public
  ${CMAKE_SOURCE_DIR}/components/threads/src)

sb_library(SHARED
  sbDirectoryEnumerator.cpp
  sbFileUtils.cpp
  sbFileUtilsModule.cpp)

add_dependencies(${PROJECT_NAME}
  sbIFileUtils)

target_link_libraries(${PROJECT_NAME}
  sbMozThreads)