# Copyright (c) 2021-2022 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.27)

project(lm_utils C ASM)
enable_language(C ASM)

option(LM_UTILS_LIBRARY_TYPE_OBJECT "Create an object library instead of static/shared library" OFF)

if (${LM_TEST_ENABLE})
    include_directories(${acutest_SOURCE_DIR})
endif()

set(lm_utils_src src/lm_utils.c src/lm_utils_trace_conf.c)
if (NOT (CMAKE_SYSTEM_NAME STREQUAL "Linux"))
    if (CMAKE_SYSTEM_PROCESSOR STREQUAL "armv8")
        include_directories(src/arm-optimized-routines/string/aarch64)
        include_directories(src/arm-optimized-routines/string/include)
        list(APPEND lm_utils_src src/arm-optimized-routines/string/aarch64/memcmp.S)
        list(APPEND lm_utils_src src/arm-optimized-routines/string/aarch64/memcpy.S)
        list(APPEND lm_utils_src src/arm-optimized-routines/string/aarch64/memset.S)

    elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "armv7l")
        include_directories(src/arm-optimized-routines/string/arm)
        include_directories(src/arm-optimized-routines/string/include)
        list(APPEND lm_utils_src src/arm-optimized-routines/string/arm/memcpy.S)
        list(APPEND lm_utils_src src/arm-optimized-routines/string/arm/memset.S)

    endif ()
endif ()

list(APPEND lm_utils_src src/lm_utils_memcmp.c)
list(APPEND lm_utils_src src/lm_utils_memcpy.c)
list(APPEND lm_utils_src src/lm_utils_memmove.c)
list(APPEND lm_utils_src src/lm_utils_memset.c)

if (${LM_UTILS_LIBRARY_TYPE_OBJECT})
    add_library(lm_utils OBJECT ${lm_utils_src})
    target_compile_options(lm_utils PRIVATE -fPIC)
else ()
    add_library(lm_utils ${lm_utils_src})
endif ()

target_include_directories(lm_utils PRIVATE ${lm_utils_SOURCE_DIR}/include)
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(lm_utils PRIVATE -DLMU_OS_LINUX)
endif ()

if (${LM_TEST_ENABLE})
    add_subdirectory(test)
endif()
