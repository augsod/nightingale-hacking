#
#
#
#
macro(XPIDL target)
  project(${target})

  xul_wrap_idl(${target} ${target}_HEADERS ${target}_TYPELIB ${ARGN})

  add_custom_target(${target} ALL DEPENDS
    ${${target}_HEADERS}
    ${${target}_TYPELIB})
endmacro()

macro(XPIDL_DEPENDENCIES)
  add_dependencies(${PROJECT_NAME} ${ARGN})

  foreach(dep ${ARGN})
    set(XUL_IDL_INCLUDE_DIRS ${XUL_IDL_INCLUDE_DIRS} -I${${dep}_BINARY_DIR})
  endforeach()
endmacro()