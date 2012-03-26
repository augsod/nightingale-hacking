# - FindTaglib.cmake
# This module can find the Taglib library.
#
# The following variables will be defined:
#
#   TAGLIB_FOUND - Were all of your specified components found?
#   TAGLIB_INCLUDE_DIRS - All include directories
#   TAGLIB_LIBRARIES - All libraries
#   TAGLIB_CFLAGS - Definitions needed to compile.
#=============================================================================

set(TAGLIB_DIR ${CMAKE_SOURCE_DIR}/dependencies)
if(UNIX)
  set(TAGLIB_DIR ${TAGLIB_DIR}/linux-i686)
endif()
set(TAGLIB_DIR ${TAGLIB_DIR}/taglib/release)

set(TAGLIB_INCLUDE_DIRS ${TAGLIB_DIR}/include/taglib)

find_library(TAGLIB_LIBRARIES NAME tag
  PATHS ${TAGLIB_DIR} PATH_SUFFIXES "lib")
