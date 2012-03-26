include(SbLibrary)
include(SbJSComponent)

project(sbProperties)

sb_js_component(
  sbSmartPlaylistPropertyRegistrar.js)

include_directories(
  ${CMAKE_BINARY_DIR}/components/intl/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src
  ${CMAKE_SOURCE_DIR}/components/moz/xpcom/src)

sb_library(SHARED
  sbPropertyManager.cpp
  sbSimpleProperty.cpp
  sbPropertyArray.cpp
  sbPropertyFactory.cpp
  sbPropertyInfo.cpp
  sbTextPropertyInfo.cpp
  sbTrackTypeImageLabelPropertyInfo.cpp
  sbNumberPropertyInfo.cpp
  sbURIPropertyInfo.cpp
  sbDatetimePropertyInfo.cpp
  sbDurationPropertyInfo.cpp
  sbPropertiesModule.cpp
  sbDownloadButtonPropertyBuilder.cpp
  sbDownloadButtonPropertyInfo.cpp
  sbOriginPageImagePropertyBuilder.cpp
  sbOriginPageImagePropertyInfo.cpp
  sbImmutablePropertyInfo.cpp
  sbSimpleButtonPropertyBuilder.cpp
  sbSimpleButtonPropertyInfo.cpp
  sbImagePropertyBuilder.cpp
  sbImagePropertyInfo.cpp
  sbBooleanPropertyInfo.cpp
  sbRatingPropertyBuilder.cpp
  sbRatingPropertyInfo.cpp
  sbAbstractPropertyBuilder.cpp
  sbPropertyUnitConverter.cpp
  sbDurationPropertyUnitConverter.cpp
  sbStoragePropertyUnitConverter.cpp
  sbFrequencyPropertyUnitConverter.cpp
  sbBitratePropertyUnitConverter.cpp
  sbDummyPropertyInfo.cpp
  sbDummyPlaylistPropertyInfo.cpp
  sbDummyContentTypePropertyInfo.cpp
  sbImageLinkPropertyInfo.cpp
  sbImageLabelLinkPropertyBuilder.cpp
  sbImageLabelLinkPropertyInfo.cpp
  sbStatusPropertyBuilder.cpp
  sbStatusPropertyInfo.cpp
  ../../moz/xpcom/src/sbWeakReference.cpp)

add_dependencies(${PROJECT_NAME}
  sbIIntl
  sbIProperties)

target_link_libraries(${PROJECT_NAME}
  sbMozStringUtils)

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND perl
  ${CMAKE_CURRENT_SOURCE_DIR}/sbStandardProperties.pl
  ${CMAKE_CURRENT_SOURCE_DIR}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/dist/jsmodules/)
