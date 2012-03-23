include(SbLibrary)

project(sbWatchFolderUtils)

include_directories(
  ${CMAKE_BINARY_DIR}/components/watchfolder/public)

sb_library(STATIC
  sbWatchFolderUtils.cpp)

add_dependencies(${PROJECT_NAME}
  sbIWatchFolderService)
