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

macro(SB_DISTRIBUTE_PREPROCESS)
  #TODO: Define these somewhere else
  set(definitions
    -DSB_APPNAME=Nightingale
    -DSB_MILESTONE=1.11.0b2
    -DSB_BUILD_ID=20120314113350
    -DSB_BUILD_NUMBER=2237
    -DSB_CRASHREPORT_SERVER_URL=https://crashreports.songbirdnest.com/submit)

  set(preprocessor ${CMAKE_SOURCE_DIR}/dependencies)
  if(UNIX)
    set(preprocessor ${preprocessor}/linux-i686)
  endif()
  set(preprocessor
    ${preprocessor}/mozilla-1.9.2/release/scripts/preprocessor.pl)

  file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/dist)
  foreach(src ${ARGN})
    set(cmd perl ${preprocessor} ${definitions}
      ${CMAKE_CURRENT_SOURCE_DIR}/${src}.in > ${CMAKE_BINARY_DIR}/dist/${src})

    add_custom_target(${src} ALL
      COMMAND ${cmd})
  endforeach()
endmacro()
