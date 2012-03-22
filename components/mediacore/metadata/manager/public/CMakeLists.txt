include(XPIDL)

xpidl_include_directories(
  ${CMAKE_SOURCE_DIR}/components/job/public
  ${CMAKE_SOURCE_DIR}/components/property/public)

xpidl(sbIMetadataModule
  sbIMetadataHandler
  sbIMetadataManager
  sbIMetadataChannel
  sbIFileMetadataService
  sbPIFileMetadataService)

add_dependencies(${PROJECT_NAME}
  sbIJob
  sbIProperties)