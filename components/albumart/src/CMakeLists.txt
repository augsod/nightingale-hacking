include(SbLibrary)
include(SbJSModule)

project(sbAlbumArt)

sb_js_module(
  sbCoverHelper.jsm)

include_directories(
  ${CMAKE_BINARY_DIR}/components/albumart/public
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_BINARY_DIR}/components/job/public
  ${CMAKE_BINARY_DIR}/components/mediacore/metadata/manager/public
  ${CMAKE_BINARY_DIR}/components/moz/strings/components/public
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${CMAKE_SOURCE_DIR}/components/property/src
  ${CMAKE_SOURCE_DIR}/components/library/base/src/static)

sb_library(SHARED
  sbAlbumArtCommon.cpp
  sbAlbumArtFetcherSet.cpp
  sbAlbumArtModule.cpp
  sbAlbumArtService.cpp
  sbFileAlbumArtFetcher.cpp
  sbAlbumArtScanner.cpp
  sbMetadataAlbumArtFetcher.cpp)

add_dependencies(${PROJECT_NAME}
  sbIAlbumArt
  sbIJob
  sbILibraryBase
  sbIMetadataModule
  sbIProperties)

target_link_libraries(${PROJECT_NAME}
  sbMozStringUtils
  sbMozThreads)