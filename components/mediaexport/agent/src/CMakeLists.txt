include(SbLibrary)

project(sbMediaExportAgentService)

include_directories(
  ${CMAKE_BINARY_DIR}/components/mediaexport/public)

sb_library(SHARED
  sbMediaExportITunesAgentComponent.cpp
  sbMediaExportITunesAgentService.cpp)

add_dependencies(${PROJECT_NAME}
  sbIMediaExportService)
