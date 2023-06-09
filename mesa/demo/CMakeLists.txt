# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

message(STATUS "CMAKE_TOOLCHAIN_FILE='${CMAKE_TOOLCHAIN_FILE}'")

option(BUILD_MESA_APP_ALL "Build all defined mesa demo applications" OFF)
option(BUILD_MESA_IMG_ALL "Build all defined mesa demo firmware images" OFF)
mark_as_advanced(BUILD_MESA_APP_ALL)

find_library(JSON_LIB json-c)
if(NOT JSON_LIB)
      message(FATAL_ERROR "json-c not found")
endif()
add_library(json-c SHARED IMPORTED GLOBAL) # GLOBAL -> if outside src tree
set_property(TARGET json-c PROPERTY IMPORTED_LOCATION ${JSON_LIB})

add_executable(base64decode base64decode.c)

add_executable(cli cmd.c)
set_target_properties(cli PROPERTIES OUTPUT_NAME "mesa-cmd")
add_library(btsig SHARED btsig.c)

add_executable(er easy_run.c)
add_executable(spi_reg_read spi_reg_read.c)

add_executable(init initramfs/main.c)
target_link_libraries(init PUBLIC "-static")

# TODO, delete these once we do not need them any more
add_executable(fa_board_fpga_init fa_board_fpga_init.c)

include_directories(../../meba/include)
include_directories(../../mepa/vtss/include)

if (EXISTS ag/mesa-rpc.c AND EXISTS ag/mesa-rpc.h AND ${MESA_PRE_AG})
set(MESA_RPC ag/mesa-rpc.c)
include_directories(ag)
else()
set(API_MEBA_CACHE_IN)
list(APPEND API_MEBA_CACHE_IN meba/include/microchip/ethernet/board/api/types.h)
list(APPEND API_MEBA_CACHE_IN meba/include/microchip/ethernet/board/api/phy.h)
list(APPEND API_MEBA_CACHE_IN meba/include/microchip/ethernet/board/api/phy_macsec.h)
list(APPEND API_MEBA_CACHE_IN meba/include/microchip/ethernet/board/api/phy_ts.h)
list(APPEND API_MEBA_CACHE_IN mepa/include/microchip/ethernet/phy/api/types.h)
list(APPEND API_MEBA_CACHE_IN mepa/include/microchip/ethernet/phy/api/phy.h)
list(APPEND API_MEBA_CACHE_IN mepa/include/microchip/ethernet/phy/api/phy_macsec.h)
list(APPEND API_MEBA_CACHE_IN mepa/include/microchip/ethernet/phy/api/phy_ts.h)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag/mesa-rpc.h ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag/mesa-rpc.c
                   COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../../mesa/scripts/ag2.rb -b ${CMAKE_CURRENT_SOURCE_DIR}/../.. -o ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag ${API_MESA_CACHE_IN} ${API_MEBA_CACHE_IN} ${API_ME_CACHE_IN}
                   DEPENDS mesa_cache
                   COMMENT "Generate mesa-rpc.h/mesa-rpc.c")
add_custom_target(mesa_rpc_src DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag/mesa-rpc.h ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag/mesa-rpc.c)
set(MESA_RPC ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag/mesa-rpc.c)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/mesa-ag)
endif()

include_directories(.)

add_library(mesa_demo_lib STATIC trace.c cli.c port.c mac.c vlan.c packet.c ip.c
                                 debug.c symreg.c test.c spi.c uio.c ${MESA_RPC} json_rpc.c
                                 example.c kr.c intr.c)
target_include_directories(mesa_demo_lib PUBLIC ${CMAKE_BINARY_DIR}/mesa-ag/)

file(GLOB_RECURSE EXAMPLE_SRC
     LIST_DIRECTORIES false
     CONFIGURE_DEPENDS
     #RELATIVE ""
     "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.c")

add_library(mesa_demo_examples_lib INTERFACE)
target_sources(mesa_demo_examples_lib INTERFACE ${EXAMPLE_SRC})
#target_include_directories(mesa_demo_examples_lib PUBLIC ${CMAKE_BINARY_DIR}/mesa-ag/)

macro(APP_TARGET)
    set(options )
    set(oneValueArgs NAME MESA MEBA)
    set(multiValueArgs )
    cmake_parse_arguments(A "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    option(${A_NAME} "Build the MESA DEMO application for ${MESA}" OFF)
    mark_as_advanced(${A_NAME})
    if (${BUILD_MESA_APP_ALL} OR ${BUILD_ALL})
        set(${A_NAME} ON CACHE BOOL "" FORCE)
    endif()

    add_executable(${A_NAME} main.c)
    target_link_libraries(${A_NAME}
        mesa_demo_lib
        mesa_demo_examples_lib
        json-c
        ${A_MESA}
        ${A_MEBA}_static
    )
    set_target_properties(${A_NAME} PROPERTIES OUTPUT_NAME "mesa-demo-${A_MESA}")

    if (${A_NAME})
        set_target_properties(${A_NAME} PROPERTIES EXCLUDE_FROM_ALL FALSE)
    else()
        set_target_properties(${A_NAME} PROPERTIES EXCLUDE_FROM_ALL TRUE)
    endif()
endmacro()

macro(IMG_TARGET)
    set(options MERA)
    set(oneValueArgs NAME APP MACHINE TYPE)
    set(multiValueArgs )
    cmake_parse_arguments(A "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64" AND A_MACHINE STREQUAL "ls1046a")
        set(KERNEL "${RELOCATED_HOST_DIR}/../mscc-linux-kernel.bin.xz")
    elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
        set(KERNEL "${RELOCATED_HOST_DIR}/../mscc-linux-kernel.bin.gz")
    elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "armv7l" AND A_MACHINE STREQUAL "BeagleBoneBlack")
        set(KERNEL "${RELOCATED_HOST_DIR}/../mscc-linux-kernel.bin.gz")
    endif()

    option(IMG_${A_NAME}_${A_TYPE} "Build the MESA DEMO firmware image for ${A_MESA}/${A_MEBA}" OFF)
    if (${BUILD_MESA_IMG_ALL} OR ${BUILD_ALL})
        set(IMG_${A_NAME}_${A_TYPE} ON CACHE BOOL "" FORCE)
    endif()

    # Building up the imggen.rb command
    set(cmd ${CMAKE_CURRENT_SOURCE_DIR}/imggen.rb)
    set(cmd ${cmd} -p ${CMAKE_CURRENT_SOURCE_DIR})
    set(cmd ${cmd} -n ${A_NAME})
    set(cmd ${cmd} -m ${A_MACHINE})
    set(cmd ${cmd} -b ${RELOCATED_HOST_DIR}/../../../../)
    set(cmd ${cmd} -s ${CMAKE_STRIP})

    # List of executables to install on target
    set(EXECUTABLES ${A_APP} cli er fa_board_fpga_init spi_reg_read base64decode)

    if (${A_MERA})
        set(EXECUTABLES ${EXECUTABLES} mera-demo mera-cmd mera-sram-rw)
    endif ()

    # Add library dependencies
    set(SOLIBS  "")

    # Find all the libraries needed by the list of executable
    foreach(E ${EXECUTABLES})
        set(cmd ${cmd} -i $<TARGET_FILE:${E}>)

        get_target_property(DEPS ${E} LINK_LIBRARIES)
        foreach(dep ${DEPS})
            #message(STATUS "${E}: ${dep}")
            if (NOT ${dep} STREQUAL "DEPS-NOTFOUND")
                get_target_property(dep_type ${dep} TYPE)
                if(${dep_type} STREQUAL "SHARED_LIBRARY")
                    set(cmd ${cmd} -i $<TARGET_FILE:${dep}>)
                    list(APPEND SOLIBS "${dep}")
                endif()
            endif()
        endforeach()
    endforeach()

    set(cmd ${cmd} -l $<TARGET_FILE_NAME:${A_APP}>@/usr/bin/mesa-demo)

    # Add overlays
    set(cmd ${cmd} -i ${CMAKE_CURRENT_SOURCE_DIR}/overlay)

    # Make sure the 'init' program is installed, even though it is not always needed
    list(APPEND EXECUTABLES init)

    if (IMG_${A_NAME}_${A_TYPE})
        if (${A_TYPE} STREQUAL "fit")
            add_custom_command(
                OUTPUT ${A_NAME}.itb
                DEPENDS ${KERNEL} ${EXECUTABLES} ${SOLIBS} ${CMAKE_CURRENT_SOURCE_DIR}/imggen.rb
                COMMAND ${CMAKE_COMMAND} -E env "PATH=\"${RELOCATED_HOST_DIR}/bin:${RELOCATED_HOST_DIR}/sbin:$ENV{PATH}\"" ${cmd} -t fit
                COMMAND touch ${CMAKE_CURRENT_SOURCE_DIR}/imggen.rb
            )
            add_custom_target(${A_NAME}_itb ALL DEPENDS ${A_NAME}.itb)

        elseif (${A_TYPE} STREQUAL "ext4")
            # When building ext4 image, also build a fit as we need this for ramloading
            add_custom_command(
                OUTPUT ${A_NAME}.itb
                DEPENDS ${KERNEL} ${EXECUTABLES} ${SOLIBS} ${CMAKE_CURRENT_SOURCE_DIR}/imggen.rb
                COMMAND ${CMAKE_COMMAND} -E env "PATH=\"${RELOCATED_HOST_DIR}/bin:${RELOCATED_HOST_DIR}/sbin:$ENV{PATH}\"" ${cmd} -t fit
                COMMAND touch ${CMAKE_CURRENT_SOURCE_DIR}/imggen.rb
            )
            add_custom_target(${A_NAME}_itb ALL DEPENDS ${A_NAME}.itb)

            add_custom_command(
                OUTPUT ${A_NAME}.ext4.gz ${A_NAME}.ubifs
                DEPENDS ${KERNEL} ${EXECUTABLES} ${SOLIBS} ${CMAKE_CURRENT_SOURCE_DIR}/imggen.rb
                COMMAND ${CMAKE_COMMAND} -E env "PATH=\"${RELOCATED_HOST_DIR}/bin:${RELOCATED_HOST_DIR}/sbin:$ENV{PATH}\"" ${cmd} -t ext4
                COMMAND touch ${CMAKE_CURRENT_SOURCE_DIR}/imggen.rb
            )
            add_custom_target(${A_NAME}_ext4 ALL DEPENDS ${A_NAME}.ext4.gz ${A_NAME}.ubifs)

        elseif (${A_TYPE} STREQUAL "mfi")
            add_custom_command(
                OUTPUT ${A_NAME}.mfi
                DEPENDS ${KERNEL} ${EXECUTABLES} ${SOLIBS} ${CMAKE_CURRENT_SOURCE_DIR}/imggen.rb
                COMMAND ${CMAKE_COMMAND} -E env "PATH=${RELOCATED_HOST_DIR}/bin:${RELOCATED_HOST_DIR}/sbin:$ENV{PATH}" ${cmd} -t mfi
                COMMAND touch ${CMAKE_CURRENT_SOURCE_DIR}/imggen.rb
            )
            add_custom_target(${A_NAME}_mfi ALL DEPENDS ${A_NAME}.mfi)

        endif()
    endif()
endmacro()

APP_TARGET(NAME app_vsc7410            MESA vsc7410            MEBA meba_servalt)
APP_TARGET(NAME app_vsc7415            MESA vsc7415            MEBA meba_servalt)
APP_TARGET(NAME app_vsc7423            MESA vsc7423            MEBA meba_caracal)
APP_TARGET(NAME app_vsc7424            MESA vsc7424            MEBA meba_caracal)
APP_TARGET(NAME app_vsc7425            MESA vsc7425            MEBA meba_caracal)
APP_TARGET(NAME app_vsc7426            MESA vsc7426            MEBA meba_caracal)
APP_TARGET(NAME app_vsc7427            MESA vsc7427            MEBA meba_caracal)
APP_TARGET(NAME app_vsc7428            MESA vsc7428            MEBA meba_caracal)
APP_TARGET(NAME app_vsc7429            MESA vsc7429            MEBA meba_caracal)
APP_TARGET(NAME app_vsc7430            MESA vsc7430            MEBA meba_servalt)
APP_TARGET(NAME app_vsc7435            MESA vsc7435            MEBA meba_servalt)
APP_TARGET(NAME app_vsc7436            MESA vsc7436            MEBA meba_servalt)
APP_TARGET(NAME app_vsc7437            MESA vsc7437            MEBA meba_servalt)
APP_TARGET(NAME app_vsc7438            MESA vsc7438            MEBA meba_jr2)
APP_TARGET(NAME app_vsc7440            MESA vsc7440            MEBA meba_servalt)
APP_TARGET(NAME app_vsc7442            MESA vsc7442            MEBA meba_jr2)
APP_TARGET(NAME app_vsc7444            MESA vsc7444            MEBA meba_jr2)
APP_TARGET(NAME app_vsc7448            MESA vsc7448            MEBA meba_jr2)
APP_TARGET(NAME app_vsc7449            MESA vsc7449            MEBA meba_jr2)
APP_TARGET(NAME app_vsc7464            MESA vsc7464            MEBA meba_jr2)
APP_TARGET(NAME app_vsc7468            MESA vsc7468            MEBA meba_jr2)
APP_TARGET(NAME app_vsc7512            MESA vsc7512            MEBA meba_ocelot_pcb121 )
APP_TARGET(NAME app_vsc7513            MESA vsc7513            MEBA meba_ocelot)
APP_TARGET(NAME app_vsc7514            MESA vsc7514            MEBA meba_ocelot)
#APP_TARGET(NAME app_vsc7546            MESA vsc7546            MEBA meba_sparx5)
#APP_TARGET(NAME app_vsc7549            MESA vsc7549            MEBA meba_sparx5)
#APP_TARGET(NAME app_vsc7552            MESA vsc7552            MEBA meba_sparx5)
#APP_TARGET(NAME app_vsc7556            MESA vsc7556            MEBA meba_sparx5)
APP_TARGET(NAME app_vsc7558            MESA vsc7558            MEBA meba_sparx5)
#APP_TARGET(NAME app_vsc7546TSN         MESA vsc7546TSN         MEBA meba_sparx5)
APP_TARGET(NAME app_vsc7552TSN         MESA vsc7552TSN         MEBA meba_sparx5)
#APP_TARGET(NAME app_vsc7556TSN         MESA vsc7556TSN         MEBA meba_sparx5)
APP_TARGET(NAME app_vsc7549TSN         MESA vsc7549TSN         MEBA meba_sparx5)
APP_TARGET(NAME app_vsc7546TSN         MESA vsc7546TSN         MEBA meba_sparx5)
APP_TARGET(NAME app_vsc7558TSN         MESA vsc7558TSN         MEBA meba_sparx5)
APP_TARGET(NAME app_vsc7558MSEC        MESA vsc7558TSN         MEBA meba_sparx5_macsec)
APP_TARGET(NAME app_vsc7556            MESA vsc7556            MEBA meba_sparx5)
APP_TARGET(NAME app_lan966x            MESA lan966x            MEBA meba_lan966x)
APP_TARGET(NAME app_lan966x_lm         MESA lan966x_lm         MEBA meba_lan966x)
APP_TARGET(NAME app_lan966x_ad         MESA lan966x_ad         MEBA meba_lan966x)


if (CMAKE_SYSTEM_PROCESSOR STREQUAL "mipsel")
    IMG_TARGET(NAME mipsel_vsc7428         TYPE mfi  APP app_vsc7428  MACHINE luton_pcb091   )
    IMG_TARGET(NAME mipsel_vsc7429         TYPE mfi  APP app_vsc7429  MACHINE luton_pcb090   )
    IMG_TARGET(NAME mipsel_vsc7423         TYPE mfi  APP app_vsc7423  MACHINE luton_pcb091   )
    IMG_TARGET(NAME mipsel_vsc7468_pcb110  TYPE mfi  APP app_vsc7468  MACHINE jaguar2_pcb110 )
    IMG_TARGET(NAME mipsel_vsc7468_pcb111  TYPE mfi  APP app_vsc7468  MACHINE jaguar2_pcb111 )
    IMG_TARGET(NAME mipsel_vsc7464         TYPE mfi  APP app_vsc7464  MACHINE jaguar2_pcb110 )
    IMG_TARGET(NAME mipsel_vsc7514_pcb120  TYPE mfi  APP app_vsc7514  MACHINE ocelot_pcb120  )
    IMG_TARGET(NAME mipsel_vsc7514_pcb123  TYPE mfi  APP app_vsc7514  MACHINE ocelot_pcb123  )
    IMG_TARGET(NAME mipsel_vsc7513_pcb120  TYPE mfi  APP app_vsc7513  MACHINE ocelot_pcb120  )
    IMG_TARGET(NAME mipsel_vsc7513_pcb123  TYPE mfi  APP app_vsc7513  MACHINE ocelot_pcb123  )
    IMG_TARGET(NAME mipsel_vsc7438         TYPE mfi  APP app_vsc7438  MACHINE serval2_pcb112 )
    IMG_TARGET(NAME mipsel_vsc7436         TYPE mfi  APP app_vsc7436  MACHINE servalt_pcb116 )
    IMG_TARGET(NAME mipsel_vsc7410         TYPE mfi  APP app_vsc7410  MACHINE servalt_pcb116 )
    IMG_TARGET(NAME mipsel_vsc7430         TYPE mfi  APP app_vsc7430  MACHINE servalt_pcb116 )
    IMG_TARGET(NAME mipsel_vsc7437         TYPE mfi  APP app_vsc7437  MACHINE servalt_pcb116 )
    IMG_TARGET(NAME mipsel_vsc7435         TYPE mfi  APP app_vsc7435  MACHINE servalt_pcb116 )
    IMG_TARGET(NAME mipsel_vsc7415         TYPE mfi  APP app_vsc7415  MACHINE servalt_pcb116 )
    IMG_TARGET(NAME mipsel_vsc7424         TYPE mfi  APP app_vsc7424  MACHINE luton_pcb091   )
    IMG_TARGET(NAME mipsel_vsc7425_pcb091  TYPE mfi  APP app_vsc7425  MACHINE luton_pcb091   )
    IMG_TARGET(NAME mipsel_vsc7425_pcb090  TYPE mfi  APP app_vsc7425  MACHINE luton_pcb090   )
    IMG_TARGET(NAME mipsel_vsc7426         TYPE mfi  APP app_vsc7426  MACHINE luton_pcb090   )
    IMG_TARGET(NAME mipsel_vsc7427         TYPE mfi  APP app_vsc7427  MACHINE luton_pcb090   )
    IMG_TARGET(NAME mipsel_vsc7440         TYPE mfi  APP app_vsc7440  MACHINE servalt_pcb116 )
    IMG_TARGET(NAME mipsel_vsc7444         TYPE mfi  APP app_vsc7444  MACHINE jaguar2_pcb110 )
    #IMG_TARGET(NAME mipsel_vsc7442        TYPE mfi  APP app_vsc7442  MACHINE jaguar2_pcb111 )
    IMG_TARGET(NAME mipsel_vsc7448_pcb110  TYPE mfi  APP app_vsc7448  MACHINE jaguar2_pcb110 )
    IMG_TARGET(NAME mipsel_vsc7448_pcb111  TYPE mfi  APP app_vsc7448  MACHINE jaguar2_pcb111 )
    #IMG_TARGET(NAME mipsel_vsc7449        TYPE mfi  APP app_vsc7449  MACHINE jaguar2_pcb111 )

elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
        #IMG_TARGET(NAME arm64_ls1046_lan966x     TYPE fit      APP app_lan966x         MACHINE ls1046a)
        #IMG_TARGET(NAME arm64_ls1046_lan966x_ad  TYPE fit      APP app_lan966x_ad      MACHINE ls1046a)

        #IMG_TARGET(NAME arm64_ls1046_vsc7468     TYPE fit      APP app_vsc7468         MACHINE ls1046a)
        IMG_TARGET(NAME arm64_vsc7558TSN         TYPE ext4     APP app_vsc7558TSN      MACHINE fireant)
        IMG_TARGET(NAME arm64_vsc7558MSEC        TYPE ext4     APP app_vsc7558MSEC     MACHINE fireant)
        IMG_TARGET(NAME arm64_vsc7552TSN         TYPE ext4     APP app_vsc7552TSN      MACHINE fireant)
        IMG_TARGET(NAME arm64_vsc7549TSN         TYPE ext4     APP app_vsc7549TSN      MACHINE fireant)
        IMG_TARGET(NAME arm64_vsc7546TSN         TYPE ext4     APP app_vsc7546TSN      MACHINE fireant)
        IMG_TARGET(NAME arm64_vsc7556            TYPE ext4     APP app_vsc7556         MACHINE fireant)
        #IMG_TARGET(NAME arm64_ls1046_vsc7449     TYPE fit      APP app_vsc7449         MACHINE ls1046a)
        #IMG_TARGET(NAME arm64_ls1046_vsc7437     TYPE fit      APP app_vsc7437         MACHINE ls1046a)
        #IMG_TARGET(NAME arm64_ls1046_vsc7438     TYPE fit      APP app_vsc7438         MACHINE ls1046a)
        #IMG_TARGET(NAME arm64_ls1046_vsc7514     TYPE fit      APP app_vsc7514         MACHINE ls1046a)
        #IMG_TARGET(NAME arm64_ls1046_vsc7512     TYPE fit      APP app_vsc7512         MACHINE ls1046a)
        IMG_TARGET(NAME ls1046_vsc7512           TYPE fit      APP app_vsc7512         MACHINE ocelot_pcb121)

elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "armv7l")
    # TODO, need to merge the BBB and none BBB versions
    if (${HAS_RTE})
        IMG_TARGET(NAME armv7_lan9662     TYPE fit    APP app_lan966x         MACHINE lan966x MERA)
    else ()
        IMG_TARGET(NAME armv7_lan9662     TYPE fit    APP app_lan966x         MACHINE lan966x)
    endif ()

    IMG_TARGET(NAME armv7_lan966x         TYPE fit    APP app_lan966x         MACHINE lan966x)
    IMG_TARGET(NAME armv7_lan966x_lm      TYPE fit    APP app_lan966x_lm      MACHINE lan966x)
    IMG_TARGET(NAME armv7_lan966x_ad      TYPE fit    APP app_lan966x_ad      MACHINE lan966x)

    IMG_TARGET(NAME armv7_lan966x_bbb     TYPE fit    APP app_lan966x         MACHINE BeagleBoneBlack)
    IMG_TARGET(NAME armv7_lan966x_ad_bbb  TYPE fit    APP app_lan966x_ad      MACHINE BeagleBoneBlack)


    IMG_TARGET(NAME armv7_vsc7428         TYPE fit    APP app_vsc7428         MACHINE BeagleBoneBlack)
    IMG_TARGET(NAME armv7_vsc7429         TYPE fit    APP app_vsc7429         MACHINE BeagleBoneBlack)
    IMG_TARGET(NAME armv7_vsc7468         TYPE fit    APP app_vsc7468         MACHINE BeagleBoneBlack)
    IMG_TARGET(NAME armv7_vsc7449         TYPE fit    APP app_vsc7449         MACHINE BeagleBoneBlack)
    IMG_TARGET(NAME armv7_vsc7436         TYPE fit    APP app_vsc7436         MACHINE BeagleBoneBlack)
    IMG_TARGET(NAME armv7_vsc7437         TYPE fit    APP app_vsc7437         MACHINE BeagleBoneBlack)
    IMG_TARGET(NAME armv7_vsc7438         TYPE fit    APP app_vsc7438         MACHINE BeagleBoneBlack)
    IMG_TARGET(NAME armv7_vsc7514         TYPE fit    APP app_vsc7514         MACHINE BeagleBoneBlack)
    IMG_TARGET(NAME armv7_vsc7512         TYPE fit    APP app_vsc7512         MACHINE BeagleBoneBlack)
    IMG_TARGET(NAME armv7_vsc7558TSN      TYPE fit    APP app_vsc7558TSN      MACHINE BeagleBoneBlack)

endif()

