include(SbLibrary)

project(sbImageParser)

include_directories(
  ${CMAKE_BINARY_DIR}/components/moz/image/public)

sb_library(SHARED
  sbImageParser.cpp
  sbImageParserModule.cpp)

add_dependencies(${PROJECT_NAME}
  sbIImageParser)
