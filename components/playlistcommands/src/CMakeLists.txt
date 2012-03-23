include(SbLibrary)

project(sbPlaylistCommands)

include_directories(
  ${CMAKE_BINARY_DIR}/components/playlistcommands/public
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/property/src)

sb_library(SHARED
  PlaylistCommandsManager.cpp
  PlaylistCommandsComponent.cpp
  sbPlaylistCommandsHelper.cpp)

add_dependencies(${PROJECT_NAME}
  sbIPlaylistCommands
  sbILibraryBase
  sbIProperties)
