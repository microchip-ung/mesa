# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

string (REPLACE " -" ";-" SHARED_LINKER_FLAGS   "${CMAKE_SHARED_LINKER_FLAGS}")
string (REPLACE " -" ";-" C_FLAGS               "${CMAKE_C_FLAGS}")
string (REPLACE " -" ";-" EXE_LINKER_FLAGS      "${CMAKE_EXE_LINKER_FLAGS}")

LIST(APPEND C_FLAGS   "-Wall -Wno-array-bounds -Wno-stringop-overflow -fasynchronous-unwind-tables -std=c99 -D_POSIX_C_SOURCE=200809L -D_BSD_SOURCE -D_DEFAULT_SOURCE -ldl")

# This is always set by buildroot - not sure why
LIST(REMOVE_ITEM C_FLAGS   "-Os")
LIST(REMOVE_ITEM C_FLAGS   "-DNDEBUG")

option(BUILD_ASAN "Enable address sanatizer" OFF)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    LIST(APPEND C_FLAGS "-O3 -DNDEBUG")
elseif (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    LIST(APPEND C_FLAGS "-O0 -g")
elseif (${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel")
    LIST(APPEND C_FLAGS "-Os")
elseif (${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
    LIST(APPEND C_FLAGS "-Os -g -DNDEBUG")
endif()

if (${BUILD_ASAN})
    LIST(APPEND C_FLAGS             "-fsanitize=address")
    LIST(APPEND EXE_LINKER_FLAGS    "-fsanitize=address")
    LIST(APPEND SHARED_LINKER_FLAGS "-fsanitize=address")
endif()

list(REMOVE_DUPLICATES C_FLAGS)
list(REMOVE_DUPLICATES EXE_LINKER_FLAGS)
list(REMOVE_DUPLICATES SHARED_LINKER_FLAGS)

string (REPLACE ";-" " -" SHARED_LINKER_FLAGS "${SHARED_LINKER_FLAGS}")
string (REPLACE ";-" " -" C_FLAGS             "${C_FLAGS}")
string (REPLACE ";-" " -" EXE_LINKER_FLAGS    "${EXE_LINKER_FLAGS}")

SET(CMAKE_SHARED_LINKER_FLAGS "${SHARED_LINKER_FLAGS}" CACHE STRING "" FORCE)
SET(CMAKE_C_FLAGS             "${C_FLAGS}"             CACHE STRING "" FORCE)
SET(CMAKE_EXE_LINKER_FLAGS    "${EXE_LINKER_FLAGS}"    CACHE STRING "" FORCE)

message(STATUS "Project name          = ${PROJECT_NAME}")
message(STATUS "  Type                = ${CMAKE_BUILD_TYPE}")
message(STATUS "  c_flags             = ${CMAKE_C_FLAGS}")
message(STATUS "  EXE_LINKER_FLAGS    = ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "  shared_linker_flags = ${CMAKE_SHARED_LINKER_FLAGS}")
