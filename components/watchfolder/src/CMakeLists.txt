include(SbLibrary)

project(sbWatchFolderService)

include_directories(
  ${CMAKE_BINARY_DIR}/components/filesystemevents/base/public
  ${CMAKE_BINARY_DIR}/components/watchfolder/public
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/job/public
  ${CMAKE_BINARY_DIR}/components/mediacore/metadata/manager/public
  ${CMAKE_BINARY_DIR}/components/mediacore/base/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_BINARY_DIR}/components/mediaimport/directory/public
  ${CMAKE_BINARY_DIR}/components/controller/public
  ${CMAKE_BINARY_DIR}/components/moz/strings/components/public
  ${CMAKE_BINARY_DIR}/components/moz/prompter/public
  ${CMAKE_SOURCE_DIR}/components/property/src
  ${CMAKE_SOURCE_DIR}/components/include
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src)

sb_library(SHARED
  sbWatchFolderService.cpp
  sbWatchFolderPrefMgr.cpp
  sbWatchFolderComponent.cpp)

add_dependencies(${PROJECT_NAME}
  sbIFileSystem
  sbIWatchFolderService
  sbILibraryBase
  sbIJob
  sbIMetadataModule
  sbIMediacoreBase
  sbIProperties
  sbIDirectoryImportService
  sbIController
  sbIStrings
  sbIPrompter)

target_link_libraries(${PROJECT_NAME}
  sbMozStringUtils
  sbMozThreads)