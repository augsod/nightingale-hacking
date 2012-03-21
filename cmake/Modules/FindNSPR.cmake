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

find_path(NSPR_INCLUDE_DIR nspr.h PATHS ${XUL_DIR} PATH_SUFFIXES "/include/nspr")

find_library(NSPR_PLDS4_LIBRARY plds4 PATHS ${XUL_DIR} PATH_SUFFIXES "/lib")
find_library(NSPR_PLC4_LIBRARY plc4 PATHS ${XUL_DIR} PATH_SUFFIXES "/lib")
find_library(NSPR_NSPR4_LIBRARY nspr4 PATHS ${XUL_DIR} PATH_SUFFIXES "/lib")

set(NSPR_LIBRARIES ${NSPR_PLDS4_LIBRARY} ${NSPR_PLC4_LIBRARY} ${NSPR_NSPR4_LIBRARY})
set(NSPR_INCLUDE_DIRS ${NSPR_INCLUDE_DIR})
