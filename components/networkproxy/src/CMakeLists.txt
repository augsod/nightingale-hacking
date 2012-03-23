include(SbLibrary)

project(sbNetworkProxy)

include_directories(
  ${CMAKE_BINARY_DIR}/components/networkproxy/public)

sb_library(SHARED
  NetworkProxyImport.cpp
  NetworkProxyImportComponent.cpp)

add_dependencies(${PROJECT_NAME}
  sbINetworkProxyImport)
