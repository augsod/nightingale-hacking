include(SbLibrary)

project(sbStrings)

include_directories(
  ${CMAKE_BINARY_DIR}/components/moz/strings/components/public
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src)

sb_library(SHARED
  sbStringBundleService.cpp
  sbStringMap.cpp
  sbCharsetDetector.cpp
  sbStringsModule.cpp)

add_dependencies(${PROJECT_NAME}
  sbIStrings)

target_link_libraries(${PROJECT_NAME}
  sbMozStringUtils)