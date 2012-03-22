include(SbLibrary)

project(sbPrompter)

include_directories(
  ${CMAKE_BINARY_DIR}/components/moz/prompter/public
  ${CMAKE_BINARY_DIR}/components/moz/windowwatcher/public)

sb_library(SHARED
  sbPrompter.cpp
  sbPrompterModule.cpp)

add_dependencies(${PROJECT_NAME}
  sbIPrompter
  sbIWindowWatcher)