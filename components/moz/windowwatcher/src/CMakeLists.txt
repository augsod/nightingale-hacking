project(sbWindowWatcher)

include_directories(
  ${CMAKE_BINARY_DIR}/components/moz/windowwatcher/public
  ${CMAKE_BINARY_DIR}/components/moz/prompter/public
  ${CMAKE_SOURCE_DIR}/components/include
  ${CMAKE_SOURCE_DIR}/components/moz/threads/src
  ${CMAKE_SOURCE_DIR}/components/moz/xpcom/src
  ${XUL_INCLUDE_DIRS})

add_definitions(${XUL_CFLAGS})

add_library(${PROJECT_NAME} SHARED
  sbWindowWatcher.cpp
  sbWindowWatcherModule.cpp
  ../../xpcom/src/sbWeakReference.cpp)

add_dependencies(${PROJECT_NAME}
  sbIPrompter
  sbIWindowWatcher)

target_link_libraries(${PROJECT_NAME}
  sbMozThreads
  ${XUL_LIBRARIES})
