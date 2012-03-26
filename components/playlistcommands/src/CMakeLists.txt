include(SbLibrary)
include(SbJSComponent)
include(SbJSModule)

project(sbPlaylistCommands)

sb_js_component(
  sbPlaylistCommandsBuilder.js
  sbPublicPlaylistCommands.js
  sbAddToPlaylist.jsm
  kPlaylistCommands.jsm)

sb_js_module(
  sbAddToPlaylist.jsm
  sbAddToDevice.jsm
  sbAddToLibrary.jsm
  kPlaylistCommands.jsm)

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
