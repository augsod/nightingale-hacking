include(SbDistribute)

add_subdirectory(branding)
add_subdirectory(content)
add_subdirectory(preferences)
add_subdirectory(skin)

sb_distribute(${CMAKE_BINARY_DIR}/dist
  blocklist.xml
  updater.ini)

sb_distribute_preprocess(${CMAKE_BINARY_DIR}/dist
  application.ini
  nightingale.ini)
