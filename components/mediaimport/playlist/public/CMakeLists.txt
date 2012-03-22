include(XPIDL)

xpidl_include_directories(
  ${CMAKE_SOURCE_DIR}/components/library/base/public)

xpidl(sbIPlaylistReader
  sbIPlaylistReader)

add_dependencies(${PROJECT_NAME}
  sbILibraryBase)