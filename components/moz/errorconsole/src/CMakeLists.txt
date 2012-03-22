include(SbLibrary)

project(sbErrorConsole)

include_directories(
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src)

sb_library(SHARED
  sbErrorConsole.cpp)

target_link_libraries(${PROJECT_NAME}
  sbMozThreads)