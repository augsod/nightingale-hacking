include(SbLibrary)

project(sbPlaybackHistoryService)

find_package(Sqlite3)

include_directories(
  ${CMAKE_BINARY_DIR}/components/dbengine/public
  ${CMAKE_BINARY_DIR}/components/sqlbuilder/public
  ${CMAKE_BINARY_DIR}/components/mediacore/base/public
  ${CMAKE_BINARY_DIR}/components/mediacore/playback/history/public
  ${CMAKE_BINARY_DIR}/components/metrics/public
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_SOURCE_DIR}/components/dbengine/src
  ${CMAKE_SOURCE_DIR}/components/library/base/src
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/xpcom/src
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${CMAKE_SOURCE_DIR}/components/property/src
  ${CMAKE_SOURCE_DIR}/components/sqlbuilder/src
  ${SQLITE3_INCLUDE_DIR})

sb_library(SHARED
  sbPlaybackHistoryEntry.cpp
  sbPlaybackHistoryService.cpp
  sbPlaybackHistoryModule.cpp)

add_dependencies(${PROJECT_NAME}
  sbIDBEngine
  sbISQLBuilder
  sbIMediacoreBase
  sbIPlaybackHistoryService
  sbIMetrics
  sbILibraryBase
  sbIProperties)

target_link_libraries(${PROJECT_NAME}
  sbMozStringUtils
  sbMozThreads)