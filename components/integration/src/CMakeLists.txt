include(SbJSComponent)

if(UNIX)
  add_subdirectory(linux)
endif()

sb_js_component(
  sbGlobalHotkeys.js
  sbHotkeyActions.js)
