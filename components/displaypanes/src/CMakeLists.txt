include(SbJSComponent)

sb_js_component(
  sbDisplayPanes.js)

# TODO: only build this when testing
sb_js_component(
  sbTestDisplayPaneProvider.js)
