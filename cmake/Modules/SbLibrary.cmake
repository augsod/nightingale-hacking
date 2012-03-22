macro(SB_LIBRARY type)
  include_directories(
    ${CMAKE_SOURCE_DIR}/components/include
    ${${PROJECT_NAME}_INCLUDE_DIRS}
    ${${PROJECT_NAME}_IDL_INCLUDE_DIRS}
    ${XUL_INCLUDE_DIRS})

  add_definitions(${XUL_CFLAGS})

  foreach(src ${ARGN})
    set(srcs ${srcs} ${${PROJECT_NAME}_SOURCE_DIR}/${src})
  endforeach()

  add_library(${PROJECT_NAME} ${type} ${srcs})

  if(DEFINED ${PROJECT_NAME}_IDL_DEPENDENCIES)
    add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_IDL_DEPENDENCIES})
  endif()

  target_link_libraries(${PROJECT_NAME}
    ${${PROJECT_NAME}_DEPENDENCIES}
    ${XUL_LIBRARIES})
endmacro()

macro(SB_LIBRARY_IDL_DEPENDENCIES)
  foreach(dep ${ARGN})
    set(dirs ${dirs} ${${dep}_BINARY_DIR})
  endforeach()
  set(${PROJECT_NAME}_IDL_INCLUDE_DIRS ${dirs})
  set(${PROJECT_NAME}_IDL_DEPENDENCIES ${ARGN})
endmacro()

macro(SB_LIBRARY_DEPENDENCIES)
  foreach(dep ${ARGN})
    set(dirs ${dirs} ${${dep}_SOURCE_DIR})
  endforeach()
  set(${PROJECT_NAME}_INCLUDE_DIRS ${dirs})
  set(${PROJECT_NAME}_DEPENDENCIES ${ARGN})
endmacro()
