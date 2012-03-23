include(XPIDL)

xpidl_include_directories(
  ${CMAKE_SOURCE_DIR}/components/job/public)

xpidl(sbIMediaManager
  sbIMediaFileManager)
