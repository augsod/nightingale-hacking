macro(SB_DISTRIBUTE)
  # When we start linking more of this together, see if we can just put this
  # all in ${CMAKE_CURRENT_BINARY_DIR}
  file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/dist)
  foreach(src ${ARGN})
    configure_file(
      ${CMAKE_CURRENT_SOURCE_DIR}/${src}
      ${CMAKE_BINARY_DIR}/dist/${src})
  endforeach()
endmacro()
