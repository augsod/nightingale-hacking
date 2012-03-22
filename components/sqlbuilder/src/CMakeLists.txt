include(SbLibrary)

project(sbSQLBuilder)

include_directories(
  ${CMAKE_BINARY_DIR}/components/sqlbuilder/public)

sb_library(SHARED
  sbSQLBuilderModule.cpp
  sbSQLBuilderBase.cpp
  sbSQLWhereBuilder.cpp
  sbSQLSelectBuilder.cpp
  sbSQLInsertBuilder.cpp
  sbSQLUpdateBuilder.cpp
  sbSQLDeleteBuilder.cpp
  sbSQLBuilderCriterion.cpp)

add_dependencies(${PROJECT_NAME}
  sbISQLBuilder)
