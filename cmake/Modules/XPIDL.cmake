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

macro(XPIDL_INCLUDE_DIRECTORIES)
  foreach(dir ${ARGN})
    set(XUL_IDL_INCLUDE_DIRS ${XUL_IDL_INCLUDE_DIRS} -I${dir})
  endforeach()
endmacro()