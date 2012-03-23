include(SbLibrary)

project(sbMediaManager)

include_directories(
  ${CMAKE_BINARY_DIR}/components/mediamanager/public
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_BINARY_DIR}/components/job/public
  ${CMAKE_BINARY_DIR}/components/watchfolder/public
  ${CMAKE_BINARY_DIR}/components/controller/public
  ${CMAKE_BINARY_DIR}/components/mediacore/metadata/manager/public
  ${CMAKE_BINARY_DIR}/components/moz/prompter/public
  ${CMAKE_BINARY_DIR}/components/moz/strings/components/public
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${CMAKE_SOURCE_DIR}/components/moz/uri/src
  ${CMAKE_SOURCE_DIR}/components/library/base/src/static
  ${CMAKE_SOURCE_DIR}/components/property/src)

sb_library(SHARED
  sbMediaManagerModule.cpp
  sbMediaFileManager.cpp)

add_dependencies(${PROJECT_NAME}
  sbIMediaManager
  sbILibraryBase
  sbIProperties
  sbIJob
  sbIWatchFolderService
  sbIController
  sbIMetadataModule
  sbIPrompter
  sbIStrings)

target_link_libraries(${PROJECT_NAME}
  sbLibraryUtils
  sbMozStreams
  sbMozStringUtils
  sbMozThreads)