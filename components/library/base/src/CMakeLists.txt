include(SbLibrary)

add_subdirectory(static)

project(sbLibraryManager)

include_directories(
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/library/localdatabase/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_SOURCE_DIR}/components/library/base/src/static
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${CMAKE_SOURCE_DIR}/components/moz/xpcom/src
  ${CMAKE_SOURCE_DIR}/components/library/base/src
  ${CMAKE_SOURCE_DIR}/components/library/localdatabase/src
  ${CMAKE_SOURCE_DIR}/components/property/src)

sb_library(SHARED
  sbLibraryConstraints.cpp
  sbLibraryManager.cpp
  sbLibraryManagerModule.cpp
  sbMediaItemControllerCleanup.cpp
  sbMediaItemWatcher.cpp
  sbMediaListDuplicateFilter.cpp
  sbMediaListEnumeratorWrapper.cpp
  sbMediaListViewMap.cpp
  sbTemporaryMediaItem.cpp
  ../../../moz/xpcom/src/sbWeakReference.cpp)

add_dependencies(${PROJECT_NAME}
  sbILibraryBase
  sbILocalDatabaseLibrary
  sbIProperties)

target_link_libraries(${PROJECT_NAME}
  sbLibraryUtils
  sbMozStreams
  sbMozStringUtils
  sbMozThreads)
