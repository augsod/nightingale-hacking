include(SbJSComponent)
include(SbJSModule)

sb_js_component(
  sbServicePaneService.js
  sbDeviceServicePaneService.js
  sbLibraryServicePaneService.js)

sb_js_module(
  ServicePaneHelper.jsm)
