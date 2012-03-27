macro(SB_JAR_MANIFEST)
  foreach(src ${ARGN})
    configure_file(
      ${CMAKE_CURRENT_SOURCE_DIR}/${src}
      ${CMAKE_CURRENT_BINARY_DIR}/${src})
  endforeach()
endmacro()

macro(SB_JAR_MANIFEST_PREPROCESS target)
  #TODO: Define these somewhere else
  set(definitions
    -DSB_APPNAME=Nightingale
    -DSB_MILESTONE=1.11.0b2
    -DSB_BUILD_ID=20120324204931
    -DSB_BUILD_NUMBER=0
    -DSB_CRASHREPORT_SERVER_URL=https://crashreports.songbirdnest.com/submit
    -DSB_UPDATE_CHANNEL=default)

  set(mozdep ${CMAKE_SOURCE_DIR}/dependencies)
  if(UNIX)
    set(mozdep ${mozdep}/linux-i686)
  endif()
  set(mozdep
    ${mozdep}/mozilla-1.9.2/release/scripts)

  set(preprocessor ${mozdep}/preprocessor.pl)
  set(jar-expander ${CMAKE_SOURCE_DIR}/tools/scripts/expand-jar-mn.pl)
  set(make-jars ${mozdep}/make-jars.pl)

  file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/dist/chrome)

  set(cmd perl ${preprocessor} ${definitions} -- ${CMAKE_CURRENT_SOURCE_DIR}/jar.mn.in | perl ${jar-expander} ${CMAKE_CURRENT_SOURCE_DIR} > ${CMAKE_CURRENT_BINARY_DIR}/jar.mn)

  add_custom_target(${target}.manifest ALL
    COMMAND ${cmd})

  set(cmd2 perl ${make-jars} -s ${CMAKE_CURRENT_SOURCE_DIR} -t ${CMAKE_SOURCE_DIR} -j ${CMAKE_BINARY_DIR}/dist/chrome -z zip -p ${preprocessor} -v ${definitions} -- < ${CMAKE_CURRENT_BINARY_DIR}/jar.mn)

  add_custom_target(${target}.jar ALL
    COMMAND ${cmd2})

  add_dependencies(${target}.jar
    ${target}.manifest)
endmacro()
