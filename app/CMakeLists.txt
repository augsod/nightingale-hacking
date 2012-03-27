include(SbDistribute)

add_subdirectory(preferences)

sb_distribute(${CMAKE_BINARY_DIR}/dist
  blocklist.xml
  updater.ini)

sb_distribute_preprocess(${CMAKE_BINARY_DIR}/dist
  application.ini
  nightingale.ini)
