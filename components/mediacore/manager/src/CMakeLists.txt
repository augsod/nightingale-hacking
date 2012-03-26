include(SbLibrary)
include(SbJSComponent)

project(sbMediacoreManager)

sb_js_component(
  sbMediacoreErrorHandler.js)

include_directories(
  ${CMAKE_BINARY_DIR}/components/dataremote/public
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/mediacore/base/public
  ${CMAKE_BINARY_DIR}/components/mediacore/manager/public
  ${CMAKE_BINARY_DIR}/components/mediaimport/playlist/public
  ${CMAKE_BINARY_DIR}/components/moz/prompter/public
  ${CMAKE_BINARY_DIR}/components/moz/strings/components/public
  ${CMAKE_BINARY_DIR}/components/moz/windowwatcher/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_SOURCE_DIR}/components/mediacore/base/src
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${CMAKE_SOURCE_DIR}/components/moz/xpcom/src
  ${CMAKE_SOURCE_DIR}/components/property/src)

sb_library(SHARED
  sbMediacoreManager.cpp
  sbMediacoreManagerModule.cpp
  sbMediacoreShuffleSequenceGenerator.cpp
  sbMediacoreSequencer.cpp
  sbMediacoreTypeSniffer.cpp
  ../../base/src/sbMediacoreVotingChain.cpp
  ../../base/src/sbMediacoreEvent.cpp
  ../../base/src/sbMediacoreError.cpp
  ../../base/src/sbBaseMediacoreEventTarget.cpp
  ../../base/src/sbBaseMediacoreMultibandEqualizer.cpp
  ../../base/src/sbBaseMediacoreVolumeControl.cpp
  ../../base/src/sbMediacoreEqualizerBand.cpp
  ../../../moz/xpcom/src/sbWeakReference.cpp)

add_dependencies(${PROJECT_NAME}
  sbIDataRemote
  sbILibraryBase
  sbIMediacoreBase
  sbIMediacoreErrorHandler
  sbIPlaylistReader
  sbIPrompter
  sbIStrings
  sbIWindowWatcher
  sbIProperties)

target_link_libraries(${PROJECT_NAME}
  sbMozStringUtils
  sbMozThreads)