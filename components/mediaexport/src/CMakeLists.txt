include(SbLibrary)

project(sbMediaExport)

include_directories(
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/library/localdatabase/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_BINARY_DIR}/components/job/public
  ${CMAKE_BINARY_DIR}/components/moz/strings/components/public
  ${CMAKE_BINARY_DIR}/components/mediaexport/public
  ${CMAKE_SOURCE_DIR}/components/moz/threadpoolservice/src
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${CMAKE_SOURCE_DIR}/components/property/src
  ${CMAKE_SOURCE_DIR}/components/library/base/src/static)

sb_library(SHARED
  sbMediaExportPrefController.cpp
  sbMediaExportTaskWriter.cpp
  sbMediaExportService.cpp
  sbMediaExportComponent.cpp)

add_dependencies(${PROJECT_NAME}
  sbILibraryBase
  sbILocalDatabaseLibrary
  sbIProperties
  sbIJob
  sbIStrings
  sbIMediaExportService)

target_link_libraries(${PROJECT_NAME}
  sbLibraryUtils
  sbMozStringUtils
  sbMozThreads)