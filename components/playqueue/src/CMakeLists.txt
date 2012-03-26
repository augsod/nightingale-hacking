include(SbLibrary)
include(SbJSComponent)

project(sbPlayQueueService)

sb_js_component(
  sbPlayQueueContentInfo.js)

include_directories(
  ${CMAKE_BINARY_DIR}/components/dataremote/public
  ${CMAKE_BINARY_DIR}/components/playqueue/public
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/library/localdatabase/public
  ${CMAKE_BINARY_DIR}/components/mediacore/base/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_SOURCE_DIR}/components/library/base/src
  ${CMAKE_SOURCE_DIR}/components/library/base/src/static
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/xpcom/src
  ${CMAKE_SOURCE_DIR}/components/property/src)

sb_library(SHARED
  sbPlayQueueLibraryListener.cpp
  sbPlayQueueExternalLibraryListener.cpp
  sbPlayQueueService.cpp
  sbPlayQueueServiceComponent.cpp)

add_dependencies(${PROJECT_NAME}
  sbIDataRemote
  sbIPlayQueueService
  sbILibraryBase
  sbILocalDatabaseLibrary
  sbIMediacoreBase
  sbIProperties)

target_link_libraries(${PROJECT_NAME}
  sbLibraryUtils
  sbMozStreams
  sbMozStringUtils
  sbMozThreads)