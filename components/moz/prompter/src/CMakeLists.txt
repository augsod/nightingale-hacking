project(sbPrompter)

include_directories(
  ${CMAKE_BINARY_DIR}/components/moz/prompter/public
  ${CMAKE_BINARY_DIR}/components/moz/windowwatcher/public
  ${CMAKE_SOURCE_DIR}/components/include
  ${XUL_INCLUDE_DIRS})

add_definitions(${XUL_CFLAGS})

add_library(${PROJECT_NAME} SHARED
  sbPrompter.cpp
  sbPrompterModule.cpp)

add_dependencies(${PROJECT_NAME}
  sbIPrompter
  sbIWindowWatcher)

target_link_libraries(${PROJECT_NAME}
  ${XUL_LIBRARIES})
