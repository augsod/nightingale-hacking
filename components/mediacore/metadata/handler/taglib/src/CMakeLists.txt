include(SbLibrary)

project(sbMetadataHandlerTagLib)

find_package(Taglib)

include_directories(
  ${CMAKE_BINARY_DIR}/components/mediacore/metadata/manager/public
  ${CMAKE_BINARY_DIR}/components/mediacore/metadata/handler/taglib/public
  ${CMAKE_BINARY_DIR}/components/albumart/public
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_SOURCE_DIR}/components/mediacore/metadata/manager/src
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${CMAKE_SOURCE_DIR}/components/property/src
  ${TAGLIB_INCLUDE_DIRS})

add_definitions(
  ${TAGLIB_CFLAGS})

sb_library(SHARED
  MetadataHandlerTaglib.cpp
  MetadataHandlerTaglibComponent.cpp
  SeekableChannel.cpp
  TaglibChannelFileIO.cpp
  TaglibChannelFileIOManager.cpp)

add_dependencies(${PROJECT_NAME}
  sbIMetadataModule
  sbIMetadataHandlerTaglib
  sbIAlbumArt
  sbILibraryBase
  sbIProperties)

target_link_libraries(${PROJECT_NAME}
  sbMozStringUtils
  sbMozThreads
  ${TAGLIB_LIBRARIES})