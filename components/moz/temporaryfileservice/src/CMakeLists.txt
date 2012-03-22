include(SbLibrary)

project(sbTemporaryFileService)

include_directories(
  ${CMAKE_BINARY_DIR}/components/moz/temporaryfileservice/public
  ${CMAKE_SOURCE_DIR}/components/moz/streams/src
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/fileutils/src)

sb_library(SHARED
  sbTemporaryFileFactory.cpp
  sbTemporaryFileService.cpp
  sbTemporaryFileServiceModule.cpp)

add_dependencies(${PROJECT_NAME}
  sbITemporaryFileService)

target_link_libraries(${PROJECT_NAME}
  sbMozStringUtils)