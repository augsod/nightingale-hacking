project(sbMozThreads)

include_directories(
  ${CMAKE_SOURCE_DIR}/components/include
  ${XUL_INCLUDE_DIRS})

add_definitions(${XUL_CFLAGS})

add_library(${PROJECT_NAME} STATIC
  sbProxiedComponentManager.cpp
  sbThreadUtils.cpp)

target_link_libraries(${PROJECT_NAME}
  ${XUL_LIBRARIES})
