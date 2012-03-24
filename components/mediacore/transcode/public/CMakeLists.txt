include(XPIDL)

xpidl_include_directories(
  ${CMAKE_SOURCE_DIR}/components/property/public
  ${CMAKE_SOURCE_DIR}/components/job/public)

xpidl(sbITranscodeModule
  sbITranscodeAlbumArt
  sbITranscodeError
  sbITranscodeJob
  sbITranscodeProfile
  sbITranscodeManager
  sbITranscodingConfigurator
  sbITranscodeVideoJob)

add_dependencies(${PROJECT_NAME}
  sbIProperties
  sbIJob)