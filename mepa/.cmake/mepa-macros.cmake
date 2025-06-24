# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

macro(MEPA_DRV)
    set(oneValueArgs   LIB_NAME)
    set(multiValueArgs SRCS DEFS INCL_PUB INCL_PRI)

    cmake_parse_arguments(A "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    option(BUILD_${A_LIB_NAME} "Build the STATIC MEPA layer for ${A_LIB_NAME}" OFF)
    mark_as_advanced(BUILD_${A_LIB_NAME})

    add_library(${A_LIB_NAME} STATIC ${A_SRCS})
    target_include_directories(${A_LIB_NAME} PUBLIC ${A_INCL_PUB} ${MEPA_SOURCE_DIR}/microchip/lan80xx/include PRIVATE ${A_INCL_PRI})

    if (${MEPA_OPSYS_VELOCITYSP})
        list(APPEND A_DEFS -DMEPA_OPSYS_VELOCITYSP=1)
    endif()
    target_compile_definitions(${A_LIB_NAME} PUBLIC ${A_DEFS})

    if (${BUILD_ALL})
        set(BUILD_${A_LIB_NAME} ON CACHE BOOL "" FORCE)
    endif()

    if (${BUILD_MEPA_ALL})
        set(BUILD_${A_LIB_NAME} ON CACHE BOOL "" FORCE)
    endif()

    if (${BUILD_${A_LIB_NAME}})
        message(STATUS "Build ${A_LIB_NAME} including ${A_MEPA_DEFINES}")
        set_target_properties(${A_LIB_NAME} PROPERTIES EXCLUDE_FROM_ALL FALSE)
    else()
        set_target_properties(${A_LIB_NAME} PROPERTIES EXCLUDE_FROM_ALL TRUE)
    endif()
endmacro()

macro(mepa_merge_static_libs)
    set(oneValueArgs   TARGET FILENAME)
    set(multiValueArgs LIBRARIES)

    cmake_parse_arguments(A "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${A_TARGET}.ar.in "CREATE ${A_FILENAME}\n" )
    foreach(e ${A_LIBRARIES})
        file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${A_TARGET}.ar.in
            "ADDLIB $<TARGET_FILE:${e}>\n")
    endforeach()
    file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${A_TARGET}.ar.in "SAVE\n")
    file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${A_TARGET}.ar.in "END\n")
    file(GENERATE
         OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${A_TARGET}.ar
         INPUT ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${A_TARGET}.ar.in)

    add_custom_command(
        COMMAND ${CMAKE_AR} -Ms < ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${A_TARGET}.ar
        OUTPUT  ${A_FILENAME}
        DEPENDS ${A_LIBRARIES}
        COMMENT "Bundling ${A_TARGET}"
        VERBATIM
    )

    add_custom_target(${A_TARGET}_target DEPENDS ${A_FILENAME})
    add_dependencies(${A_TARGET}_target ${A_LIBRARIES})
    add_library(${A_TARGET} STATIC IMPORTED GLOBAL)
    add_dependencies(${A_TARGET} ${A_TARGET}_target)

    set_target_properties(${A_TARGET} PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/${A_FILENAME}
    )
endmacro(mepa_merge_static_libs)

macro(MEPA_LIB)
    set(options        ADVANCED)
    set(oneValueArgs   LIB_NAME)
    set(multiValueArgs DEFS DRVS)
    cmake_parse_arguments(A "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    if (A_ADVANCED)
        option(BUILD_${A_LIB_NAME} "Build ${A_LIB_NAME} with ${A_DRVS}" OFF)
        mark_as_advanced(BUILD_${A_LIB_NAME})
    else()
        option(BUILD_${A_LIB_NAME} "Build ${A_LIB_NAME} with ${A_DRVS}" ON)
    endif()

    set(lib_common ${A_LIB_NAME}_common)
    add_library(${lib_common} STATIC EXCLUDE_FROM_ALL ${MEPA_SOURCE_DIR}/common/src/phy.c)
    set(lib_stub ${A_LIB_NAME}_stub)
    add_library(${lib_stub} STATIC ${MEPA_SOURCE_DIR}/microchip/lan_stubs.c)
    if (${MEPA_OPSYS_VELOCITYSP})
        list(APPEND A_DEFS -DMEPA_OPSYS_VELOCITYSP=1)
    endif()
    target_compile_definitions(${lib_stub} PRIVATE ${A_DEFS})
    target_include_directories(${lib_stub}
                               PUBLIC  ${MEPA_SOURCE_DIR}/../sw-mesa/me/include
                                       ${MEPA_SOURCE_DIR}/../me/include
                                       ${MEPA_SOURCE_DIR}/include
                                       ${MEPA_SOURCE_DIR}/microchip/lan80xx/include
                               PRIVATE ${MEPA_SOURCE_DIR}/common/src)

    target_compile_definitions(${lib_common} PRIVATE ${A_DEFS})
    target_include_directories(${lib_common}
                               PUBLIC  ${MEPA_SOURCE_DIR}/../me/include
                                       ${MEPA_SOURCE_DIR}/include
				       ${MEPA_SOURCE_DIR}/microchip/lan80xx/include
                               PRIVATE ${MEPA_SOURCE_DIR}/common/src)

    mepa_merge_static_libs(TARGET    ${A_LIB_NAME}
                           FILENAME  lib${A_LIB_NAME}.a
                           LIBRARIES ${lib_common} ${A_DRVS} ${lib_stub})

    if (${BUILD_ALL})
        set(BUILD_${A_LIB_NAME} ON CACHE BOOL "" FORCE)
    endif()

    if (${BUILD_MEPA_ALL})
        set(BUILD_${A_LIB_NAME} ON CACHE BOOL "" FORCE)
    endif()

    if (${BUILD_${A_LIB_NAME}})
        message(STATUS "Build ${A_LIB_NAME} including ${A_DRVS}")
        set_target_properties(${A_LIB_NAME}_target PROPERTIES EXCLUDE_FROM_ALL FALSE)
    else()
        set_target_properties(${A_LIB_NAME}_target PROPERTIES EXCLUDE_FROM_ALL TRUE)
    endif()
endmacro()
