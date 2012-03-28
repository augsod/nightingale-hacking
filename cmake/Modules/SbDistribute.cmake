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
    -DPACKAGE_NAME=""
    -DPACKAGE_TARNAME=""
    -DPACKAGE_VERSION=""
    -DPACKAGE_STRING=""
    -DPACKAGE_BUGREPORT=""
    -DPACKAGE_URL=""
    -DNDEBUG=1
    -DXP_UNIX=1
    -D_REENTRANT=1
    -DSB_PLATFORM="linux"
    -DSB_APPNAME="Nightingale"
    -DSB_BRANCHNAME="Songbird1.11"
    -DSB_BUILD_ID="20120327002039"
    -DSB_BUILD_NUMBER="0"
    -DSB_MILESTONE="1.11.0b2"
    -DSB_MILESTONE_WINDOWS="1.10.99.2"
    -DSB_PROFILE_VERSION="2"
    -DSB_MOZILLA_VERSION="1.9.2.3"
    -DSB_UPDATE_CHANNEL="default"
    -DSB_CRASHREPORT_SERVER_URL=https://crashreports.songbirdnest.com/submit
    -DMEDIA_CORE_GST_SYSTEM=1)

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

    add_custom_target(${PROJECT_NAME}.${src} ALL
      COMMAND ${cmd} ${outdir}/${src})
  endforeach()
endmacro()
