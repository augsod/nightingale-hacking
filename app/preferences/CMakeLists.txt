include(SbDistribute)

sb_distribute_preprocess(${CMAKE_BINARY_DIR}/dist/defaults/preferences
  songbird-prefs.js
  songbird-channel-prefs.js)

sb_distribute(${CMAKE_BINARY_DIR}/dist/defaults/preferences
  browser-prefs.js)
