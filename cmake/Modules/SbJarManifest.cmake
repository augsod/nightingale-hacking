#------------------------------------------------------------------------------
# Rules for chrome jar files
#------------------------------------------------------------------------------
#
# This macro will look for a manifest file named either jar.mn or jar.mn.in in
# the current source directory. If it is jar.mn.in the file will be preprocessed
# first.
#
# This also defines two targets for which dependencies can be added:
#   * ${PROJECT_NAME}.manifest
#   * ${PROJECT_NAME}.jar
#
# FORCE_JARS - Force use of JAR files. Default is undefined.
#
# PREVENT_JARS - Prevent use of JAR files. Default is undefined.
#
# FLAT_JARS - Force use of flat JARs (defaults to true in debug builds). Default
#   is undefined.
#
# MAKE_JAR_FLAGS - An override to the flags passed to the make-jars.pl command
#
# MAKE_JAR_EXTRA_FLAGS - Extra flags to pass to the make-jars.pl command
#
# JAR_TARGET_DIR - An overide to the directory to create the jar in. The default
#   is ${CMAKE_BINARY_DIR}/dist/chrome
#
macro(SB_JAR_MANIFEST)
  # TODO: include this definition
  set(mozdep ${CMAKE_SOURCE_DIR}/dependencies)
  if(UNIX)
    set(mozdep ${mozdep}/linux-i686)
  endif()
  set(mozdep
    ${mozdep}/mozilla-1.9.2/release/scripts)

  #TODO: Define these somewhere else
  set(definitions
    -DSB_APPNAME=Nightingale
    -DSB_MILESTONE=1.11.0b2
    -DSB_BUILD_ID=20120324204931
    -DSB_BUILD_NUMBER=0
    -DSB_CRASHREPORT_SERVER_URL=
    -DSB_UPDATE_CHANNEL=default)

  set(preprocessor ${mozdep}/preprocessor.pl)
  set(jar-expander ${CMAKE_SOURCE_DIR}/tools/scripts/expand-jar-mn.pl)
  set(make-jars ${mozdep}/make-jars.pl)

  # We use flat jars (i.e. plain directories) if any of the following
  # conditions are met:
  #   * We are doing a debug build, MAKE_JARS is _not_ defined, and FLAT_JARS is
  #     _not_ defined
  #   * We are doing a release build,PREVENT_JARS _is_ defined, and FLAT_JARS is
  #   * _not_ defined.
  #   * FLAT_JARS _is_ defined
  if(FLAT_JARS)
    set(_FLAT_JARS ${FLAT_JARS})
  elseif(${CMAKE_BUILD_TYPE} MATCHES Debug)
    if(FORCE_JARS)
      set(_FLAT_JARS TRUE)
    endif()
  else()
    if(PREVENT_JARS)
      set(_FLAT_JARS TRUE)
    endif()
  endif()

  # If JAR_TARGET_DIR is defined, use it instead of the default.
  if(JAR_TARGET_DIR)
    set(_JAR_TARGET_DIR ${JAR_TARGET_DIR})
  else()
    set(_JAR_TARGET_DIR ${CMAKE_BINARY_DIR}/dist/chrome)
  endif()

  # If MAKE_JARS_FLAGS is defined, use it instead of the default.
  if(MAKE_JARS_FLAGS)
    set(_MAKE_JARS_FLAGS ${MAKE_JARS_FLAGS})
  else()
    set(_MAKE_JARS_FLAGS
      -s ${CMAKE_CURRENT_SOURCE_DIR}
      -t ${CMAKE_SOURCE_DIR}
      -j ${_JAR_TARGET_DIR}
      -z zip
      -p ${mozdep}/preprocessor.pl
      -v
      ${EXTRA_MAKE_JARS_FLAGS})

    if(_FLAT_JARS)
      set(_MAKE_JARS_FLAGS ${_MAKE_JARS_FLAGS}
	-f flat -d ${_JAR_TARGET_DIR})
    else()
      set(_MAKE_JARS_FLAGS ${_MAKE_JARS_FLAGS}
	-d ${_JAR_TARGET_DIR}/stage)
    endif()
  endif()

  if(_FLAT_JARS)
    set(_PPDEFINES -DUSING_FLAT_JARS=${_FLAT_JARS})
  endif()

  # Check to see if the manifest file exists in the source dir. If not then
  # we're going to assume it needs to be generated through preprocessing. The
  # postprocessed file will be generated in the object directory.
  set(_JAR_MN ${CMAKE_CURRENT_BINARY_DIR}/jar.mn)
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/jar.mn.in)
    set(_JAR_MN_IN ${CMAKE_CURRENT_SOURCE_DIR}/jar.mn.in)
  elseif(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/jar.mn)
    set(_JAR_MN_IN ${CMAKE_CURRENT_SOURCE_DIR}/jar.mn)
  endif()

  file(MAKE_DIRECTORY ${_JAR_TARGET_DIR})
  file(MAKE_DIRECTORY ${_JAR_TARGET_DIR}/stage)

  set(cmd perl ${preprocessor}
    ${_PPDEFINES} ${definitions} -- ${_JAR_MN_IN} |
    perl ${jar-expander} ${CMAKE_CURRENT_SOURCE_DIR} > ${_JAR_MN})

  add_custom_target(${PROJECT_NAME}.manifest ALL
    COMMAND ${cmd})

  set(cmd2 perl -I${mozdep} -I${CMAKE_CURRENT_BINARY_DIR}
    ${make-jars} ${_MAKE_JARS_FLAGS} --
    ${_PPDEFINES} ${definitions} < ${_JAR_MN})

  add_custom_target(${PROJECT_NAME}.jar ALL
    COMMAND ${cmd2})

  add_dependencies(${PROJECT_NAME}.jar
    ${PROJECT_NAME}.manifest)
endmacro()
