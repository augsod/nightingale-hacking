# - FindNSPR.cmake
# This module checks for NSPR library.
#
# The following variables will be defined:
#
#   NSPR_FOUND - Was NSPR found?
#   NSPR_INCLUDE_DIRS - All include directories
#   NSPR_LIBRARIES - All libraries

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
find_package(PkgConfig)

if(PKG_CONFIG_FOUND)
    pkg_check_modules(_NSPR_PKG xulrunner-nspr)
endif()

find_path(NSPR_INCLUDE_DIR nspr.h PATHS ${_NSPR_PKG_INCLUDE_DIRS} ${XUL_SDK_DIR} PATH_SUFFIXES "/include/nspr")

find_library(NSPR_PLDS4_LIBRARY plds4 PATHS ${_NSPR_PKG_LIBRARY_DIRS} ${XUL_SDK_DIR} PATH_SUFFIXES "/lib")
find_library(NSPR_PLC4_LIBRARY plc4 PATHS ${_NSPR_PKG_LIBRARY_DIRS} ${XUL_SDK_DIR} PATH_SUFFIXES "/lib")
find_library(NSPR_NSPR4_LIBRARY nspr4 PATHS ${_NSPR_PKG_LIBRARY_DIRS} ${XUL_SDK_DIR} PATH_SUFFIXES "/lib")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(NSPR DEFAULT_MSG NSPR_PLDS4_LIBRARY NSPR_PLC4_LIBRARY NSPR_NSPR4_LIBRARY NSPR_INCLUDE_DIR)

if (NSPR_FOUND)
    set(NSPR_LIBRARIES ${NSPR_PLDS4_LIBRARY} ${NSPR_PLC4_LIBRARY} ${NSPR_NSPR4_LIBRARY})
    set(NSPR_INCLUDE_DIRS ${NSPR_INCLUDE_DIR})
    include(FindPackageMessage)
    find_package_message(NSPR "Found NSPR" "[${NSPR_LIBRARIES}][${NSPR_INCLUDE_DIRS}]")
endif()
