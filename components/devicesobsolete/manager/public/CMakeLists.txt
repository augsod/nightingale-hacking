include(XPIDL)

xpidl_include_directories(
  ${CMAKE_SOURCE_DIR}/components/devicesobsolete/base/public)

xpidl(sbIDeviceManager
  sbIDeviceManager)

add_dependencies(${PROJECT_NAME}
  sbIDeviceBase)