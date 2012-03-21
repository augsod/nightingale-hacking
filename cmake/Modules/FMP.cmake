# - FMP.cmake
# This module provides the find_multiple_paths macro.
#
# find_multiple_paths(
#     <VAR>
#     name1 [name2 ...]
#     PATHS path1_1 [path1_2 ...]
#     [ PATH_SUFFIXES suffix1_1 [suffix1_2 ...] ]
#     [ PATHS path2_1 [path2_2 ...]
#       [ PATH_SUFFIXES suffix2_1 [suffix2_2 ...] ]
#       ... ]
#
# Search for name1, name2, ... in each of the groups defined by the different
# PATHS and PATH_SUFFIXES definitions. If all files are found in a group, VAR
# is set to the list of paths where the files were found.
#
# find_multiple_paths(
#     FIND <VAR1> name1_1 [name1_2 ...]
#     [ FIND <VAR1> name2_1 [name2_2 ...] ]
#     PATHS path1_1 [path1_2 ...]
#     [ PATH_SUFFIXES suffix1_1 [suffix1_2 ...] ]
#     [ PATHS path2_1 [path2_2 ...]
#       [ PATH_SUFFIXES suffix2_1 [suffix2_2 ...] ]
#       ... ]
#
# Search for name1_1, name1_2, name2_1, ... in each of the groups defined by the different
# PATHS and PATH_SUFFIXES definitions. If all files are found in a group, VAR1
# is set to the list of paths where the files name1_1, name1_2 were found, VAR2 to the
# list of paths where name2_1 were found, etc.

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

macro(FMP_PARSE_ARGS)
    set(FIRST_ARG true)

    set(FIND_IDX 1)
    list(APPEND FIND_IDX_LIST ${FIND_IDX})
    set(ARG_TYPE "VAR")

    set(PATHS_MAX_IDX 0)

    foreach(ARG ${ARGN})
        if (${ARG} STREQUAL "FIND")
            if (NOT FIRST_ARG)
                math(EXPR FIND_IDX "${FIND_IDX} + 1")
                list(APPEND FIND_IDX_LIST ${FIND_IDX})
                set(ARG_TYPE "VAR")
            endif()
        elseif(${ARG} STREQUAL "PATHS")
            set(PATHS_IDX ${PATHS_MAX_IDX})
            math(EXPR PATHS_MAX_IDX "${PATHS_MAX_IDX} + 1")
            set(ARG_TYPE "PATH")
        elseif(${ARG} STREQUAL "PATH_SUFFIXES")
            set(ARG_TYPE "SUFFIX")
        elseif (${ARG_TYPE} STREQUAL "VAR")
            set(VAR_${FIND_IDX} ${ARG})
            set(ARG_TYPE "FILE")
        elseif (${ARG_TYPE} STREQUAL "FILE")
            set(FILES_${FIND_IDX} ${FILES_${FIND_IDX}} ${ARG})
        elseif (${ARG_TYPE} STREQUAL "PATH")
            set(PATHS_${PATHS_IDX} ${PATHS_${PATHS_IDX}} ${ARG})
        elseif (${ARG_TYPE} STREQUAL "SUFFIX")
            set(SUFFIXES_${PATHS_IDX} ${SUFFIXES_${PATHS_IDX}} ${ARG})
        endif()
        set(FIRST_ARG false)
    endforeach()
endmacro()

macro(FIND_MULTIPLE_PATHS)
    fmp_parse_args(${ARGN})

    set(FMP_IDX 1)
    set(PATHS_IDX 0)
    set(LOOP_END false)
    if (PATHS_IDX EQUAL PATHS_MAX_IDX)
        set(LOOP_END true)
    endif()
    while(NOT LOOP_END)
        set(FMP_FOUND true)
        foreach(FIND_IDX IN LISTS FIND_IDX_LIST)
            set(FMP_${PATHS_IDX}_${FIND_IDX} "")
            foreach(FILE ${FILES_${FIND_IDX}})
                find_path(FMP_${FMP_IDX} ${FILE} PATHS ${PATHS_${PATHS_IDX}} PATH_SUFFIXES ${SUFFIXES_${PATHS_IDX}} NO_DEFAULT_PATH)
                set_property(CACHE FMP_${FMP_IDX} PROPERTY TYPE INTERNAL)
                if (NOT FMP_${FMP_IDX})
                    set(FMP_FOUND false)
                else ()
                    set(FMP_${PATHS_IDX}_${FIND_IDX} ${FMP_${PATHS_IDX}_${FIND_IDX}} ${FMP_${FMP_IDX}})
                endif()
                math(EXPR FMP_IDX "${FMP_IDX} + 1")
            endforeach()
        endforeach()
        if (FMP_FOUND)
            set(LOOP_END true)
            set(FOUND_AT ${PATHS_IDX})
        endif()
        math(EXPR PATHS_IDX "${PATHS_IDX} + 1")
        if (PATHS_IDX EQUAL PATHS_MAX_IDX)
            set(LOOP_END true)
        endif()
    endwhile()

    if (FMP_FOUND)
        foreach(FIND_IDX IN LISTS FIND_IDX_LIST)
            list(REMOVE_DUPLICATES FMP_${FOUND_AT}_${FIND_IDX})
            set(${VAR_${FIND_IDX}} ${FMP_${FOUND_AT}_${FIND_IDX}} CACHE PATH "")
        endforeach()
    endif()
endmacro()
