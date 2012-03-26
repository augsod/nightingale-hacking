include(SbLibrary)
include(SbJSComponent)

project(sbUpdate)

sb_js_component(
  sbAddOnBundleUpdateService.js)

sb_library(SHARED
  sbDistHelperEnvWriter.cpp
  sbUpdateModule.cpp)
