include(SbLibrary)

project(sbMediacoreBase)

include_directories(
  ${CMAKE_BINARY_DIR}/components/integration/public
  ${CMAKE_BINARY_DIR}/components/mediacore/base/public
  ${CMAKE_BINARY_DIR}/components/moz/prompter/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_SOURCE_DIR}/components/mediacore/base/src
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${CMAKE_SOURCE_DIR}/components/moz/xpcom/src)

sb_library(SHARED
  sbBaseMediacore.cpp
  sbBaseMediacoreEventTarget.cpp
  sbBaseMediacoreModule.cpp
  sbBaseMediacoreMultibandEqualizer.cpp
  sbBaseMediacoreFactory.cpp
  sbBaseMediacorePlaybackControl.cpp
  sbBaseMediacoreVolumeControl.cpp
  sbMediacoreCapabilities.cpp
  sbMediacoreEqualizerBand.cpp
  sbMediacoreError.cpp
  sbMediacoreEvent.cpp
  sbMediacoreFactoryWrapper.cpp
  sbMediacoreVotingChain.cpp
  sbMediacoreWrapper.cpp
  sbMediaInspector.cpp
  sbVideoBox.cpp)

add_dependencies(${PROJECT_NAME}
  sbIIntegration
  sbIMediacoreBase
  sbIPrompter
  sbIProperties)

target_link_libraries(${PROJECT_NAME}
  sbMozStringUtils
  sbMozThreads)