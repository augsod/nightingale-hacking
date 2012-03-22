macro(SB_LIBRARY type)
  include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/components/include
    ${XUL_INCLUDE_DIRS})

  add_definitions(${XUL_CFLAGS})

  foreach(src ${ARGN})
    set(srcs ${srcs} ${${PROJECT_NAME}_SOURCE_DIR}/${src})
  endforeach()

  add_library(${PROJECT_NAME} ${type} ${srcs})

  target_link_libraries(${PROJECT_NAME}
    ${XUL_LIBRARIES})
endmacro()
