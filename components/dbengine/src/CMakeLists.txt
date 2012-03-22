include(SbLibrary)

find_package(GLIB2)
find_package(Sqlite3)

project(sbDBEngine)

include_directories(
  ${CMAKE_BINARY_DIR}/components/dbengine/public
  ${CMAKE_BINARY_DIR}/components/moz/strings/components/public
  ${CMAKE_BINARY_DIR}/components/moz/prompter/public
  ${CMAKE_BINARY_DIR}/components/metrics/public
  ${CMAKE_SOURCE_DIR}/components/intl/src
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/threadpoolservice/src
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${GLIB2_INCLUDE_DIR}
  ${SQLITE3_INCLUDE_DIR})

sb_library(SHARED
  DatabaseEngineComponent.cpp
  DatabaseEngine.cpp
  DatabaseQuery.cpp
  DatabasePreparedStatement.cpp
  DatabaseResult.cpp)

add_dependencies(${PROJECT_NAME}
  sbIDBEngine
  sbIStrings
  sbIPrompter
  sbIMetrics)

target_link_libraries(${PROJECT_NAME}
  sbMozStringUtils
  sbMozThreads
  ${GLIB2_LIBRARIES}
  ${SQLITE3_LIBRARIES})