include(SbLibrary)
include(SbJSModule)

project(sbMetadataModule)

sb_js_module(
  sbMetadataUtils.jsm)

include_directories(
  ${CMAKE_BINARY_DIR}/components/albumart/public
  ${CMAKE_BINARY_DIR}/components/mediacore/base/public
  ${CMAKE_BINARY_DIR}/components/mediacore/metadata/manager/public
  ${CMAKE_BINARY_DIR}/components/dataremote/public
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/library/localdatabase/public
  ${CMAKE_BINARY_DIR}/components/dbengine/public
  ${CMAKE_BINARY_DIR}/components/sqlbuilder/public
  ${CMAKE_BINARY_DIR}/components/job/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_BINARY_DIR}/components/watchfolder/public
  ${CMAKE_BINARY_DIR}/components/moz/strings/components/public
  ${CMAKE_SOURCE_DIR}/components/library/base/src
  ${CMAKE_SOURCE_DIR}/components/library/base/src/static
  ${CMAKE_SOURCE_DIR}/components/property/src
  ${CMAKE_SOURCE_DIR}/components/sqlbuilder/src
  ${CMAKE_SOURCE_DIR}/components/albumart/src
  ${CMAKE_SOURCE_DIR}/components/library/localdatabase/src
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/dbengine/src
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${CMAKE_SOURCE_DIR}/components/moz/xpcom/src)

sb_library(SHARED
  sbMetadataManager.cpp
  sbMetadataChannel.cpp
  sbMetadataCrashTracker.cpp
  sbFileMetadataService.cpp
  sbMetadataJobItem.cpp
  sbMainThreadMetadataProcessor.cpp
  sbBackgroundThreadMetadataProcessor.cpp
  sbMetadataJob.cpp
  sbMetadataModule.cpp)

add_dependencies(${PROJECT_NAME}
  sbIAlbumArt
  sbIMediacoreBase
  sbIMetadataModule
  sbIDataRemote
  sbILibraryBase
  sbILocalDatabaseLibrary
  sbIDBEngine
  sbISQLBuilder
  sbIJob
  sbIProperties
  sbIWatchFolderService
  sbIStrings)

target_link_libraries(${PROJECT_NAME}
  sbMozStringUtils
  sbMozThreads)