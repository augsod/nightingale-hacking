include(SbLibrary)

project(sbIdentityServiceComponent)

include_directories(
  ${CMAKE_BINARY_DIR}/components/library/identity/public
  ${CMAKE_BINARY_DIR}/components/library/base/public
  ${CMAKE_BINARY_DIR}/components/library/localdatabase/public
  ${CMAKE_BINARY_DIR}/components/property/public
  ${CMAKE_SOURCE_DIR}/components/property/src
  ${CMAKE_SOURCE_DIR}/components/moz/strings/src)

sb_library(SHARED
  sbIdentityService.cpp
  sbIdentityServiceComponent.cpp)

add_dependencies(${PROJECT_NAME}
  sbILibraryBase
  sbILocalDatabaseLibrary
  sbIProperties)

target_link_libraries(${PROJECT_NAME}
  sbMozStringUtils)
