include(SbLibrary)

project(sbIntl)

if(UNIX)
  find_package(GLIB2)
endif()

set(includes
  ${CMAKE_BINARY_DIR}/components/intl/public)

if(UNIX)
  set(includes ${includes}
    ${CMAKE_CURRENT_SOURCE_DIR}/linux
    ${GLIB2_INCLUDE_DIR})
endif()

include_directories(${includes})

set(sources
  sbStringTransform.cpp
  sbIntlModule.cpp
  sbArticlesData.cpp)

if(UNIX)
  set(sources ${sources}
    linux/sbStringTransformImpl.cpp)
endif()

sb_library(SHARED
  ${sources})

add_dependencies(${PROJECT_NAME}
  sbIIntl)

if(UNIX)
  target_link_libraries(${PROJECT_NAME}
    ${GLIB2_LIBRARIES})
endif()