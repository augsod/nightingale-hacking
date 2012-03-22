include(XPIDL)

xpidl_include_directories(
  ${CMAKE_SOURCE_DIR}/components/library/base/public)

xpidl(sbIDeviceBase2
  sbIDevice
  sbIDeviceCapabilities
  sbIDeviceInfoRegistrar
  sbIDeviceCapsCompatibility
  sbIDeviceCompatibility
  sbIDeviceContent
  sbIDeviceControllerRegistrar
  sbIDeviceEvent
  sbIDeviceEventBeforeAddedData
  sbIDeviceEventListener
  sbIDeviceEventTarget
  sbIDeviceFirmwareHandler
  sbIDeviceFirmwareSupport
  sbIDeviceFirmwareUpdate
  sbIDeviceFirmwareUpdater
  sbIDeviceLibraryMediaSyncSettings
  sbIDeviceLibrarySyncDiff
  sbIDeviceLibrarySyncSettings
  sbIDeviceLibrary
  sbIDeviceProperties
  sbIDeviceRegistrar
  sbIDeviceManager
  sbIDeviceStatus
  sbIDeviceImage)

add_dependencies(${PROJECT_NAME}
  sbILibraryBase)