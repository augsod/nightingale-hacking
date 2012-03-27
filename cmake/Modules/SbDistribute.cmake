macro(SB_DISTRIBUTE outdir)
  # When we start linking more of this together, see if we can just put this
  # all in ${CMAKE_CURRENT_BINARY_DIR}
  file(MAKE_DIRECTORY ${outdir})
  foreach(src ${ARGN})
    configure_file(
      ${CMAKE_CURRENT_SOURCE_DIR}/${src}
      ${outdir}/${src})
  endforeach()
endmacro()

macro(SB_DISTRIBUTE_PREPROCESS outdir)
  #TODO: Define these somewhere else
  set(definitions
    -DSB_APPNAME=Nightingale
    -DSB_MILESTONE=1.11.0b2
    -DSB_BUILD_ID=20120324204931
    -DSB_BUILD_NUMBER=0
    -DSB_CRASHREPORT_SERVER_URL=https://crashreports.songbirdnest.com/submit
    -DSB_UPDATE_CHANNEL=default)

  set(preprocessor ${CMAKE_SOURCE_DIR}/dependencies)
  if(UNIX)
    set(preprocessor ${preprocessor}/linux-i686)
  endif()
  set(preprocessor
    ${preprocessor}/mozilla-1.9.2/release/scripts/preprocessor.pl)

  file(MAKE_DIRECTORY ${outdir})
  foreach(src ${ARGN})
    set(cmd perl ${preprocessor} ${definitions}
      ${CMAKE_CURRENT_SOURCE_DIR}/${src}.in >)

    add_custom_target(${src} ALL
      COMMAND ${cmd} ${outdir}/${src})
  endforeach()
endmacro()
