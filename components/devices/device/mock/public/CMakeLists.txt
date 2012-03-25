include(XPIDL)

xpidl_include_directories(
  ${CMAKE_SOURCE_DIR}/components/devices/base/public)

xpidl(sbIDeviceDeviceTester
  sbDeviceDeviceTesterInterfaces
  sbIMockDevice)
