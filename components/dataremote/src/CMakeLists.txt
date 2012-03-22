include(SbLibrary)

project(sbDataRemote)

include_directories(
  ${CMAKE_BINARY_DIR}/components/dataremote/public
  ${CMAKE_BINARY_DIR}/components/remoteapi/public)

sb_library(SHARED
  sbDataRemoteWrapper.cpp
  sbDataRemoteModule.cpp)

add_dependencies(${PROJECT_NAME}
  sbIBrowserAPI
  sbIDataRemote)
