include(SbLibrary)

project(sbClipboardHelper)

include_directories(
  ${CMAKE_BINARY_DIR}/components/moz/clipboard/public)

sb_library(SHARED
  sbClipboardHelper.cpp
  sbClipboardHelperModule.cpp)

add_dependencies(${PROJECT_NAME}
  sbIClipboardHelper)
