include(SbLibrary)

project(sbMediaItemDownloadService)

include_directories(
  ${CMAKE_BINARY_DIR}/components/library/download/public
  ${CMAKE_BINARY_DIR}/components/job/public
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/moz/filedownloader/public
  ${CMAKE_BINARY_DIR}/components/moz/temporaryfileservice/public
  ${CMAKE_BINARY_DIR}/components/moz/xpcom/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_SOURCE_DIR}/components/moz/streams/src
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${CMAKE_SOURCE_DIR}/components/moz/xpcom/src
  ${CMAKE_SOURCE_DIR}/components/property/src)

sb_library(SHARED
  sbBaseMediaItemDownloadJob.cpp
  sbHTTPMediaItemDownloader.cpp
  sbHTTPMediaItemDownloadJob.cpp
  sbMediaItemDownloadService.cpp
  sbMediaItemDownloadModule.cpp)

add_dependencies(${PROJECT_NAME}
  sbIMediaItemDownloadService
  sbIJob
  sbILibraryBase
  sbIFileDownloader
  sbITemporaryFileService
  sbIXPCOM
  sbIProperties)

target_link_libraries(${PROJECT_NAME}
  sbMozStringUtils
  sbMozThreads)