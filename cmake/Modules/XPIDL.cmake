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
