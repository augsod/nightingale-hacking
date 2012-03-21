# - FindXUL.cmake
# This module can find the XUL framework. Also checks for xpidl
# program.
#
# Both the stable and unstable version of the framework can be
# detected, the stable being the default one. If you need
# unstable components, specify them when calling this module.
# For instance:
# find_package(XUL REQUIRED nsIRunnable)
# will check for a XUL installation providing the nsIRunnable.idl
# and nsIRunnable.h files.
#
# The following variables will be defined:
#
#   XUL_FOUND - Were all of your specified components found?
#   XUL_INCLUDE_DIRS - All include directories
#   XUL_LIBRARIES - All libraries
#   XUL_CFLAGS - Definitions needed to compile.
#   XUL_IDL_INCLUDE_DIRS - IDL files include directories
#   XUL_XPIDL_EXECUTABLE - Path to xpidl
#
# Three utility functions are provided:
#
#  function XUL_GENERATE_TYPELIB(idlfile)
#        creates a rule to run xpidl on idlfile.idl and create idlfile.xpt.
#
#  function XUL_GENERATE_HEADER(idlfile)
#        creates a rule to run xpidl on idlfile.idl and create idlfile.h.
#
#  function XUL_WRAP_IDL(idlfile)
#        creates a rule to run xpidl on idlfile.idl and create both idlfile.xpt and idlfile.h.

#=============================================================================
# Copyright 2010 Guillaume Duhamel <guillaume.duhamel@gmail.com>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================

set(XUL_SDK_DIR CACHE PATH "Location of XUL SDK")

find_package(NSPR)

set(XUL_DIR ${CMAKE_SOURCE_DIR}/dependencies)
if(UNIX)
  set(XUL_DIR ${XUL_DIR}/linux-i686)
endif()
set(XUL_DIR ${XUL_DIR}/mozilla-1.9.2/release)

find_program(XPIDL_EXECUTABLE xpidl PATHS ${XUL_DIR} PATH_SUFFIXES bin)

foreach(_XUL_COMPONENT ${XUL_FIND_COMPONENTS})
    set(_XUL_EXTRA_IDLS ${_XUL_EXTRA_IDLS} ${_XUL_COMPONENT}.idl)
    set(_XUL_EXTRA_HEADERS ${_XUL_EXTRA_HEADERS} ${_XUL_COMPONENT}.h)
endforeach()

include(FMP)
find_multiple_paths(
    FIND IDL_INCLUDE_DIR nsISupports.idl ${_XUL_EXTRA_IDLS}
    FIND XUL_INCLUDE_DIR nsISupports.h nsEmbedString.h nsIURI.h ${_XUL_EXTRA_HEADERS}
    PATHS ${XUL_DIR}
    PATH_SUFFIXES "idl" "include" "include/xpcom" "include/string" "include/necko"
)

find_library(XUL_GLUE_LIBRARY xpcomglue_s PATHS ${XUL_DIR} PATH_SUFFIXES "lib")
find_library(XUL_XPCOM_LIBRARY xpcom PATHS ${XUL_DIR} PATH_SUFFIXES "lib")

set(XUL_LIBRARIES ${XUL_GLUE_LIBRARY} ${XUL_XPCOM_LIBRARY} ${NSPR_LIBRARIES})
set(XUL_INCLUDE_DIRS ${XUL_INCLUDE_DIR} ${NSPR_INCLUDE_DIRS})
set(XUL_IDL_INCLUDE_DIRS ${IDL_INCLUDE_DIR})
set(XUL_XPIDL_EXECUTABLE ${XPIDL_EXECUTABLE})
set(XUL_CFLAGS "-fshort-wchar")

macro(XUL_GENERATE_TYPELIB outfile)
    add_custom_command(
        OUTPUT ${outfile}
        COMMAND ${XUL_XPIDL_EXECUTABLE} -m typelib -I${XUL_IDL_INCLUDE_DIRS} -I${CMAKE_CURRENT_SOURCE_DIR} ${ARGN} -e ${outfile})
endmacro()

macro(XUL_GENERATE_HEADER infile outfile)
    add_custom_command(
        OUTPUT ${outfile}
        COMMAND ${XUL_XPIDL_EXECUTABLE} -m header -I${XUL_IDL_INCLUDE_DIRS} -I${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${infile} -e ${outfile})
endmacro()

macro(XUL_WRAP_IDL target headers typelib)
  foreach(idlfile ${ARGN})
    set(idlfiles ${idlfiles} ${CMAKE_CURRENT_SOURCE_DIR}/${idlfile}.idl)

    set(${headers} ${${headers}} ${idlfile}.h)
    xul_generate_header(${idlfile}.idl ${idlfile}.h)
  endforeach()

  xul_generate_typelib(${target}.xpt ${idlfiles})
  set(${typelib} ${${typelib}} ${target}.xpt)
endmacro()