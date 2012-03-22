include(SbLibrary)

project(sbMozStringUtils)

include_directories(
  ${CMAKE_BINARY_DIR}/components/moz/strings/components/public)

sb_library(STATIC
  sbTArrayStringEnumerator.cpp
  sbStringBundle.cpp
  sbStringUtils.cpp)

add_dependencies(${PROJECT_NAME}
  sbIStrings)