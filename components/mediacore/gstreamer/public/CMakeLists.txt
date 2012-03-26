include(XPIDL)

xpidl_include_directories(
  ${CMAKE_SOURCE_DIR}/components/property/public
  ${CMAKE_SOURCE_DIR}/components/mediacore/transcode/public)

xpidl(sbIGStreamerMediacore
  sbIGStreamerService
  sbIGStreamerMediacore
  sbIGStreamerRTPStreamer
  sbIGStreamerPipeline
  sbPIGstTranscodingConfigurator)
