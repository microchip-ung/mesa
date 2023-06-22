# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 2.8.12)

project(vtss_api)

include(CMakeParseArguments)
include(.cmake/common.cmake)

option(BUILD_ALL         "Enable all" OFF)
option(BUILD_STATIC_LIBS "Build static versions of the libraries" ON)
option(BUILD_SHARED_LIBS "Build shared versions of the libraries" ON)
option(BUILD_MESA_ALL    "Build the MESA libraries" OFF)
option(BUILD_DOXYGEN     "Build doxygen" OFF)
option(MESA_PRE_AG       "Use pre-generated mesa-ag layer if exist" ON)
option(BUILD_MESA_DEMO   "Build the MESA demo" ON)
option(MESA_OPSYS_LINUX  "Build the MESA for Linux" ON)
option(MESA_OPSYS_LMSTAX "Build the MESA for LMStaX" OFF)
option(MESA_WRAP         "Generate and build the MESA Wrapper" ON)

mark_as_advanced(BUILD_MESA_DEMO MESA_PRE_AG BUILD_DOXYGEN)

include(.cmake/doxygen.cmake)

add_subdirectory(mepa)

include_directories(me/include)
include_directories(mesa/include)
include_directories(meba/include)
include_directories(mepa/include)

set (OS_CNT 0)
if (${MESA_OPSYS_LINUX})
    MATH(EXPR OS_CNT "${OS_CNT} + 1")
endif ()

if (${MESA_OPSYS_LMSTAX})
    MATH(EXPR OS_CNT "${OS_CNT} + 1")
endif ()

if (NOT ${OS_CNT} EQUAL 1)
    message(FATAL_ERROR "Enable one and only one OS layer")
endif ()

# MEBA is only supported on Linux
if (${MESA_OPSYS_LINUX})
    add_subdirectory(meba)
endif ()

#find_program(CCACHE_FOUND ccache)
#if(CCACHE_FOUND)
#    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
#    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
#endif(CCACHE_FOUND)

INCLUDE (CheckIncludeFiles)
INCLUDE (CheckCSourceCompiles)

if (${MESA_OPSYS_LINUX})
    CHECK_INCLUDE_FILES("endian.h" VTSS_HAS_ENDIAN_H)
    IF(NOT VTSS_HAS_ENDIAN_H)
        message(FATAL_ERROR "endian.h was not found or did not compile. See CMakeFiles/CMakeError.log for more details.")
    ENDIF()

    CHECK_INCLUDE_FILES("asm/byteorder.h" VTSS_HAS_ASM_BYTEORDER_H)
    IF(NOT VTSS_HAS_ASM_BYTEORDER_H)
        message(FATAL_ERROR "asm/byteorder.h was not found or did not compile. See CMakeFiles/CMakeError.log for more details.")
    ENDIF()
endif ()

file(GLOB_RECURSE API_UNI_SRC  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "base/*.c")
file(GLOB_RECURSE API_UNI_HDR  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/include" "include/**.h")
file(GLOB_RECURSE API_UNI_HDR_ABS "include/**.h")

if (${MESA_WRAP})
    file(GLOB_RECURSE API_MESA_SRC RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "mesa/src/**.c")
    file(GLOB_RECURSE API_MESA_HDR RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/mesa/include" "mesa/include/**.h")
    file(GLOB_RECURSE API_MEBA_HDR RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/meba/include" "meba/include/**.h")
endif ()
file(GLOB_RECURSE API_MEPA_HDR RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/mepa/include" "mepa/include/**.h")
file(GLOB_RECURSE API_MEPA_VTSS_HDR RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/mepa/vtss/include" "mepa/vtss/include/*.h")
file(GLOB_RECURSE API_ME_HDR RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/me/include" "me/include/**.h")

list(REMOVE_ITEM API_MESA_SRC mesa/src/capability_dumper.c)

### MESA-PROCESSING START #####################################################################################################################################
if (${MESA_WRAP})
if (EXISTS mesa/ag/mesa.c AND EXISTS mesa/ag/mesa.h AND ${MESA_PRE_AG})

message(STATUS "Using pre-generated mesa-ag layer")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/masa/ag/)
list(APPEND API_MESA_SRC ${CMAKE_CURRENT_SOURCE_DIR}/masa/ag/mesa.c)
list(APPEND API_MESA_SRC ${CMAKE_CURRENT_SOURCE_DIR}/masa/ag/mesa.h)

else()

set(API_MESA_CACHE_IN)
set(API_MESA_CACHE_OUT)

set(API_ME_CACHE_IN)
list(APPEND API_ME_CACHE_IN me/include/microchip/ethernet/common.h)

# List of header files to exclude from the mesa-hdr processing
set(MESA_CACHE_DENY_LIST include/vtss_os_linux.h
                          include/vtss_os_ecos.h
                          include/vtss_ae_api.h
                          mesa/include/microchip/ethernet/hdr_end.h
                          mesa/include/microchip/ethernet/hdr_start.h
                          mesa/include/microchip/ethernet/switch/api/port_list.h)

# Macro to produce the mesa processing cache
macro(MESA_CACHE)
    list(FIND MESA_CACHE_DENY_LIST ${ARGV0} BL)
    if(-1 EQUAL ${BL})
        #message(STATUS "mesa_cache: ${ARGV0}")
        add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag/${ARGV0}.cache
                           COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/mesa/scripts/ag.rb -b ${CMAKE_CURRENT_SOURCE_DIR} -o ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag --cache-only ${ARGV0}
                           DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${ARGV0}
                           COMMENT "AG: Parsing/caching ${ARGV0}")
        list(APPEND API_MESA_CACHE_IN  ${ARGV0})
        list(APPEND API_MESA_CACHE_OUT ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag/${ARGV0}.cache)
    else()
        #message(STATUS "skipping: ${ARGV0}")
    endif()
endmacro(MESA_CACHE)

FOREACH(f ${API_UNI_HDR})
    # Add header to mesa processing
    MESA_CACHE("include/${f}")
ENDFOREACH()

FOREACH(f ${API_MESA_HDR})
    # Install all mesa headers
    configure_file("mesa/include/${f}" "${CMAKE_CURRENT_BINARY_DIR}/include_common/${f}" COPYONLY)
    # Add header to mesa processing
    MESA_CACHE("mesa/include/${f}")
ENDFOREACH()

FOREACH(f ${API_MEBA_HDR})
    configure_file("meba/include/${f}" "${CMAKE_CURRENT_BINARY_DIR}/include_common/${f}" COPYONLY)
ENDFOREACH()

FOREACH(f ${API_MEPA_HDR})
    # Add all mepa headers
    configure_file("mepa/include/${f}" "${CMAKE_CURRENT_BINARY_DIR}/include_common/${f}" COPYONLY)
ENDFOREACH()

FOREACH(f ${API_MEPA_VTSS_HDR})
    configure_file("mepa/vtss/include/${f}" "${CMAKE_CURRENT_BINARY_DIR}/include_common/${f}" COPYONLY)
ENDFOREACH()

FOREACH(f ${API_ME_HDR})
    # Add all me headers
    configure_file("me/include/${f}" "${CMAKE_CURRENT_BINARY_DIR}/include_common/${f}" COPYONLY)
ENDFOREACH()

# Target to drive the mesa-cache processing
add_custom_target(mesa_cache DEPENDS ${API_MESA_CACHE_OUT})

# Create the auto generated mesa header/src (using the earlier created cache).
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag/mesa.h ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag/mesa.c
                   COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/mesa/scripts/ag.rb -b ${CMAKE_CURRENT_SOURCE_DIR} -o ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag ${API_MESA_CACHE_IN} ${API_ME_CACHE_IN}
                   DEPENDS mesa_cache ${CMAKE_CURRENT_SOURCE_DIR}/mesa/scripts/ag.rb
                   COMMENT "Generate mesa.h/mesa.c")
add_custom_target(mesa_src DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag/mesa.h ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag/mesa.c)
list(APPEND API_MESA_SRC ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag/mesa.c)
list(APPEND API_MESA_SRC ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag/mesa.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/mesa-ag/)
### MESA-PROCESSING END #######################################################################################################################################
endif()
endif()

include_directories(include)

################################################################################

set(LIST_OF_API_TARGETS)

if (${MESA_OPSYS_LINUX})
    set(GLOBAL_DEFS -DVTSS_OPSYS_LINUX -DVTSS_OPT_SYMREG=1)
elseif (${MESA_OPSYS_LMSTAX})
    set(GLOBAL_DEFS -DVTSS_OPSYS_LMSTAX -DVTSS_OPT_SYMREG=0)
endif ()

macro(API_TARGET)
  set(oneValueArgs LIB CHIP)
  set(multiValueArgs DEFS)

  cmake_parse_arguments(A "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  option(${A_LIB}        "Build the API for ${A_CHIP} (${A_LIB})" OFF)
  option(${A_LIB}_static "Build the static API for ${A_CHIP} (${A_LIB})" OFF)
  if (${BUILD_MESA_ALL} OR ${BUILD_ALL})
      if (${BUILD_SHARED_LIBS})
          set(${A_LIB} ON CACHE BOOL "" FORCE)
      endif()

      if (${BUILD_STATIC_LIBS})
          set(${A_LIB}_static ON CACHE BOOL "" FORCE)
      endif()
  endif()

  set(DEFS ${GLOBAL_DEFS} -DVTSS_CHIP_${A_CHIP} ${A_DEFS})

  add_library(${A_LIB} SHARED ${API_UNI_SRC} ${API_MESA_SRC})
  target_compile_options(${A_LIB} PUBLIC ${DEFS})

  add_library(${A_LIB}_static STATIC ${API_UNI_SRC} ${API_MESA_SRC})
  set_target_properties(${A_LIB}_static PROPERTIES OUTPUT_NAME "${A_LIB}")
  target_compile_options(${A_LIB}_static PUBLIC ${DEFS})

  if (${A_LIB})
      message(STATUS "Adding ${A_LIB} (${A_CHIP}) MESA=${has_mesa} Defines: [${DEFS}]")
      set_target_properties(${A_LIB} PROPERTIES EXCLUDE_FROM_ALL FALSE)
  else()
      set_target_properties(${A_LIB} PROPERTIES EXCLUDE_FROM_ALL TRUE)
  endif()

  if (${A_LIB}_static)
      message(STATUS "Adding ${A_LIB}_static (${A_CHIP}) MESA=${has_mesa} Defines: [${DEFS}]")
      set_target_properties(${A_LIB}_static PROPERTIES EXCLUDE_FROM_ALL FALSE)
  else()
      set_target_properties(${A_LIB}_static PROPERTIES EXCLUDE_FROM_ALL TRUE)
  endif()

  add_custom_command(
      OUTPUT "include_${A_LIB}/vtss/api/options.h"
      COMMAND mkdir -p include_${A_LIB}/vtss/api
      COMMAND gcc -dM -E ${CMAKE_CURRENT_SOURCE_DIR}/include/vtss/api/options.h ${DEFS} | grep VTSS > include_${A_LIB}/vtss/api/options.h
      DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/vtss/api/options.h"
      WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
      COMMENT "Preprocessing options.h for ${A_LIB}"
  )

  list(APPEND LIST_OF_API_TARGETS ${A_LIB})
endmacro(API_TARGET)

API_TARGET(LIB vsc7410               CHIP SERVAL_T)
API_TARGET(LIB vsc7415               CHIP SERVAL_TP)
API_TARGET(LIB vsc7423               CHIP CARACAL_LITE)
API_TARGET(LIB vsc7424               CHIP SPARX_III_10)
API_TARGET(LIB vsc7425               CHIP SPARX_III_18)
API_TARGET(LIB vsc7426               CHIP SPARX_III_24)
API_TARGET(LIB vsc7427               CHIP SPARX_III_26)
API_TARGET(LIB vsc7428               CHIP CARACAL_1     DEFS -DVTSS_OPT_PORT_COUNT=10)
API_TARGET(LIB vsc7429               CHIP CARACAL_2)
API_TARGET(LIB vsc7430               CHIP SERVAL_TE)
API_TARGET(LIB vsc7435               CHIP SERVAL_TEP)
API_TARGET(LIB vsc7436               CHIP SERVAL_2_LITE DEFS -DVTSS_OPT_PORT_COUNT=9)
API_TARGET(LIB vsc7437               CHIP SERVAL_TE10)
API_TARGET(LIB vsc7438               CHIP SERVAL_2)
API_TARGET(LIB vsc7440               CHIP SPARX_IV_34   DEFS -DVTSS_OPT_PORT_COUNT=9)
API_TARGET(LIB vsc7442               CHIP SPARX_IV_52)
API_TARGET(LIB vsc7444               CHIP SPARX_IV_44)
API_TARGET(LIB vsc7448               CHIP SPARX_IV_80   DEFS -DVTSS_OPT_PORT_COUNT=51)
API_TARGET(LIB vsc7449               CHIP SPARX_IV_90)
API_TARGET(LIB vsc7464               CHIP LYNX_2)
API_TARGET(LIB vsc7468               CHIP JAGUAR_2      DEFS -DVTSS_OPT_PORT_COUNT=51)
API_TARGET(LIB vsc7511               CHIP 7511          DEFS -DVTSS_OPT_PORT_COUNT=8)
API_TARGET(LIB vsc7512               CHIP 7512)
API_TARGET(LIB vsc7513               CHIP 7513          DEFS -DVTSS_OPT_AFI_OPTIMIZE_FOR_TIMERS=1)
API_TARGET(LIB vsc7514               CHIP 7514          DEFS -DVTSS_OPT_AFI_OPTIMIZE_FOR_TIMERS=1)
API_TARGET(LIB vsc7546               CHIP 7546          DEFS -DVTSS_OPT_PORT_COUNT=29)
API_TARGET(LIB vsc7549               CHIP 7549          DEFS -DVTSS_OPT_PORT_COUNT=53)
API_TARGET(LIB vsc7552               CHIP 7552          DEFS -DVTSS_OPT_PORT_COUNT=57)
API_TARGET(LIB vsc7556               CHIP 7556          DEFS -DVTSS_OPT_PORT_COUNT=57)
API_TARGET(LIB vsc7558               CHIP 7558          DEFS -DVTSS_OPT_PORT_COUNT=57)
API_TARGET(LIB vsc7546TSN            CHIP 7546TSN       DEFS -DVTSS_OPT_PORT_COUNT=29)
API_TARGET(LIB vsc7549TSN            CHIP 7549TSN       DEFS -DVTSS_OPT_PORT_COUNT=53)
API_TARGET(LIB vsc7552TSN            CHIP 7552TSN       DEFS -DVTSS_OPT_PORT_COUNT=57)
API_TARGET(LIB vsc7556TSN            CHIP 7556TSN       DEFS -DVTSS_OPT_PORT_COUNT=57)
API_TARGET(LIB vsc7558TSN            CHIP 7558TSN       DEFS -DVTSS_OPT_PORT_COUNT=57)
API_TARGET(LIB vsc7558MSEC           CHIP 7558TSN       DEFS -DVTSS_OPT_PORT_COUNT=57)
API_TARGET(LIB lan966x               CHIP 966X)
API_TARGET(LIB lan966x_lm            CHIP 966X          DEFS -DVTSS_OPT_LIGHT=1 -DVTSS_OPT_TRACE=1 -DVTSS_OPT_DEBUG_PRINT=1)
API_TARGET(LIB lan966x_ad            CHIP 966X          DEFS -DVTSS_OPT_FPGA=2)

option(BUILD_MESA_CAPABILITY_DUMPER "Build all the mesa capability dumper function" OFF)
mark_as_advanced(BUILD_MESA_CAPABILITY_DUMPER)
if (${BUILD_MESA_CAPABILITY_DUMPER})
    add_executable(capability_dumper mesa/src/capability_dumper.c)
    target_link_libraries(capability_dumper dl)
endif()

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/sw-mera/CMakeLists.txt)
    set(HAS_RTE ON)
    add_subdirectory(sw-mera)
else()
    set(HAS_RTE OFF)
endif()

if (${BUILD_MESA_DEMO})
    find_library(JSON_LIB json-c)
    mark_as_advanced(JSON_LIB)
    if (JSON_LIB)
        add_subdirectory(mesa/demo)
    endif()
endif()

