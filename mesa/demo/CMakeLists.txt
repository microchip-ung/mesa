# Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

message(STATUS "CMAKE_TOOLCHAIN_FILE='${CMAKE_TOOLCHAIN_FILE}'")

option(BUILD_MESA_APP_ALL "Build all defined mesa demo applications" OFF)
option(BUILD_MESA_IMG_ALL "Build all defined mesa demo firmware images" OFF)

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

add_executable(init initramfs/main.c)
target_link_libraries(init PUBLIC "-static")

# TODO, delete these once we do not need them any more
add_executable(fa_board_fpga_init fa_board_fpga_init.c)
add_executable(fa_spi_chip_id     fa_spi_chip_id.c)

if (EXISTS ag/mesa-rpc.c AND EXISTS ag/mesa-rpc.h AND ${MESA_PRE_AG})
set(MESA_RPC ag/mesa-rpc.c)
include_directories(ag)
else()
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag/mesa-rpc.h ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag/mesa-rpc.c
                   COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../../mesa/scripts/ag2.rb -b ${CMAKE_CURRENT_SOURCE_DIR}/../.. -o ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag ${API_MESA_CACHE_IN}
                   DEPENDS mesa_cache
                   COMMENT "Generate mesa-rpc.h/mesa-rpc.c")
add_custom_target(mesa_rpc_src DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag/mesa-rpc.h ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag/mesa-rpc.c)
set(MESA_RPC ${CMAKE_CURRENT_BINARY_DIR}/mesa-ag/mesa-rpc.c)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/mesa-ag)
endif()

include_directories(.)

add_library(mesa_demo_lib STATIC trace.c cli.c port.c mac.c vlan.c packet.c ip.c
                                 debug.c symreg.c test.c spi.c uio.c ${MESA_RPC} json_rpc.c
                                 example.c )
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
    if (${BUILD_MESA_APP_ALL} OR ${BUILD_ALL})
        set(${A_NAME} ON CACHE BOOL "" FORCE)
    endif()

    add_executable(${A_NAME} main.c)
    target_link_libraries(${A_NAME} mesa_demo_lib mesa_demo_examples_lib ${A_MESA} ${A_MEBA} json-c)
    set_target_properties(${A_NAME} PROPERTIES OUTPUT_NAME "mesa-demo-${A_MESA}")

    if (${A_NAME})
        set_target_properties(${A_NAME} PROPERTIES EXCLUDE_FROM_ALL FALSE)
    else()
        set_target_properties(${A_NAME} PROPERTIES EXCLUDE_FROM_ALL TRUE)
    endif()
endmacro()

add_custom_command(
    OUTPUT ls1046-kernel.img
    DEPENDS ${RELOCATED_HOST_DIR}/../../ls1046/mscc-linux-ls1046.bin.xz
    COMMAND xz -d -c ${RELOCATED_HOST_DIR}/../../ls1046/mscc-linux-ls1046.bin.xz | gzip -f -c > ls1046-kernel.img
)

add_custom_command(
    OUTPUT bbb-kernel.img
    DEPENDS ${RELOCATED_HOST_DIR}/../mscc-linux-beaglebone.bin.xz
    COMMAND xz -d -c ${RELOCATED_HOST_DIR}/../mscc-linux-beaglebone.bin.xz | gzip -f -c > bbb-kernel.img
)

add_custom_command(
    OUTPUT fireant-kernel.img
    DEPENDS ${RELOCATED_HOST_DIR}/../mscc-linux-fireant.bin.xz
    COMMAND xz -d -c ${RELOCATED_HOST_DIR}/../mscc-linux-fireant.bin.xz | gzip -f -c > fireant-kernel.img

)

macro(IMG_TARGET)
    set(options )
    set(oneValueArgs NAME APP MACHINE TYPE KMOD)
    set(multiValueArgs )
    cmake_parse_arguments(A "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64" AND A_MACHINE STREQUAL "ls1046a")
        set(KERNEL "ls1046-kernel.img")
    elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64" AND (A_MACHINE STREQUAL "fireant"))
        set(KERNEL "fireant-kernel.img")
    elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "armv7l" AND A_MACHINE STREQUAL "BeagleBoneBlack")
        set(KERNEL "bbb-kernel.img")
    endif()

    option(${A_NAME} "Build the MESA-FIT DEMO for ${A_MESA}/${A_MEBA}" OFF)
    if (${BUILD_MESA_IMG_ALL} OR ${BUILD_ALL})
        set(${A_NAME} ON CACHE BOOL "" FORCE)
    endif()

    # Building up the imggen.rb command
    set(cmd ${CMAKE_CURRENT_SOURCE_DIR}/imggen.rb)
    set(cmd ${cmd} -p ${CMAKE_CURRENT_SOURCE_DIR})
    set(cmd ${cmd} -n ${A_NAME})
    set(cmd ${cmd} -m ${A_MACHINE})
    set(cmd ${cmd} -b ${RELOCATED_HOST_DIR})
    set(cmd ${cmd} -s ${CMAKE_STRIP})

    # List of executables to install on target
    set(EXECUTABLES ${A_APP} cli er fa_board_fpga_init fa_spi_chip_id base64decode)

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

    # If a kernel module is specified, then add it
    if (DEFINED A_KMOD)
        list(APPEND SOLIBS kernel_module_${A_KMOD})
        set(cmd ${cmd} -i ../../meba/linux_kernel_modules/${A_KMOD}/mscc_board.ko@/lib/modules/board/)
    endif()

    set(cmd ${cmd} -l $<TARGET_FILE_NAME:${A_APP}>@/usr/bin/mesa-demo)

    # Add overlays
    set(cmd ${cmd} -i ${CMAKE_CURRENT_SOURCE_DIR}/overlay)

    # Install the PHY drivers
    list(APPEND SOLIBS phy_aqr)
    set(cmd ${cmd} -i $<TARGET_FILE:phy_aqr>@lib/phy_drivers/)

    # Make sure the 'init' program is installed, even though it is not always needed
    list(APPEND EXECUTABLES init)

    if (${A_NAME})
        if (${A_TYPE} STREQUAL "fit")
            add_custom_command(
                OUTPUT ${A_NAME}.itb
                DEPENDS ${KERNEL} ${EXECUTABLES} ${SOLIBS} ${CMAKE_CURRENT_SOURCE_DIR}/imggen.rb
                COMMAND ${CMAKE_COMMAND} -E env "PATH=${RELOCATED_HOST_DIR}/bin:$ENV{PATH}" ${cmd} -t fit
                COMMAND touch ${CMAKE_CURRENT_SOURCE_DIR}/imggen.rb
            )
            add_custom_target(${A_NAME}_itb ALL DEPENDS ${A_NAME}.itb)

        elseif (${A_TYPE} STREQUAL "ext4")
            # When building ext4 image, also build a fit as we need this for ramloading
            add_custom_command(
                OUTPUT ${A_NAME}.itb
                DEPENDS ${KERNEL} ${EXECUTABLES} ${SOLIBS} ${CMAKE_CURRENT_SOURCE_DIR}/imggen.rb
                COMMAND ${CMAKE_COMMAND} -E env "PATH=${RELOCATED_HOST_DIR}/bin:$ENV{PATH}" ${cmd} -t fit
                COMMAND touch ${CMAKE_CURRENT_SOURCE_DIR}/imggen.rb
            )
            add_custom_target(${A_NAME}_itb ALL DEPENDS ${A_NAME}.itb)

            add_custom_command(
                OUTPUT ${A_NAME}.ext4.gz
                DEPENDS ${KERNEL} ${EXECUTABLES} ${SOLIBS} ${CMAKE_CURRENT_SOURCE_DIR}/imggen.rb
                COMMAND ${CMAKE_COMMAND} -E env "PATH=${RELOCATED_HOST_DIR}/bin:$ENV{PATH}" ${cmd} -t ext4
                COMMAND touch ${CMAKE_CURRENT_SOURCE_DIR}/imggen.rb
            )
            add_custom_target(${A_NAME}_ext4 ALL DEPENDS ${A_NAME}.ext4.gz)

        elseif (${A_TYPE} STREQUAL "mfi")
            add_custom_command(
                OUTPUT ${A_NAME}.mfi
                DEPENDS ${KERNEL} ${EXECUTABLES} ${SOLIBS} ${CMAKE_CURRENT_SOURCE_DIR}/imggen.rb
                COMMAND ${CMAKE_COMMAND} -E env "PATH=${RELOCATED_HOST_DIR}/bin:$ENV{PATH}" ${cmd} -t mfi
                COMMAND touch ${CMAKE_CURRENT_SOURCE_DIR}/imggen.rb
            )
            add_custom_target(${A_NAME}_mfi ALL DEPENDS ${A_NAME}.mfi)

        endif()
    endif()
endmacro()

APP_TARGET(NAME app_vsc7410            MESA vsc7410            MEBA meba_servalt)
APP_TARGET(NAME app_vsc7414            MESA vsc7414            MEBA meba_serval1)
APP_TARGET(NAME app_vsc7415            MESA vsc7415            MEBA meba_servalt)
APP_TARGET(NAME app_vsc7416            MESA vsc7416            MEBA meba_serval1)
APP_TARGET(NAME app_vsc7418            MESA vsc7418            MEBA meba_serval1)
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
APP_TARGET(NAME app_vsc7558TSN         MESA vsc7558TSN         MEBA meba_sparx5)


if (CMAKE_SYSTEM_PROCESSOR STREQUAL "mipsel")
    IMG_TARGET(NAME mfi_vsc7428     TYPE mfi      APP  app_vsc7428           KMOD  luton26       MACHINE luton10  )
    IMG_TARGET(NAME mfi_vsc7429     TYPE mfi      APP  app_vsc7429           KMOD  luton26       MACHINE luton26  )
    IMG_TARGET(NAME mfi_vsc7423     TYPE mfi      APP  app_vsc7423           KMOD  luton26       MACHINE luton10  )
    IMG_TARGET(NAME mfi_vsc7468     TYPE mfi      APP  app_vsc7468           KMOD  jaguar2       MACHINE jaguar2c )
    IMG_TARGET(NAME mfi_vsc7468_48  TYPE mfi      APP  app_vsc7468           KMOD  jaguar2-cu48  MACHINE jaguar2c )
    IMG_TARGET(NAME mfi_vsc7464     TYPE mfi      APP  app_vsc7464           KMOD  jaguar2       MACHINE jaguar2c )
    IMG_TARGET(NAME mfi_vsc7514     TYPE mfi      APP  app_vsc7514           KMOD  ocelot        MACHINE ocelot   )
    IMG_TARGET(NAME mfi_vsc7513     TYPE mfi      APP  app_vsc7513           KMOD  ocelot        MACHINE ocelot   )
    IMG_TARGET(NAME mfi_vsc7418     TYPE mfi      APP  app_vsc7418           KMOD  serval1       MACHINE serval1  )
    IMG_TARGET(NAME mfi_vsc7438     TYPE mfi      APP  app_vsc7438           KMOD  serval2       MACHINE serval2  )
    IMG_TARGET(NAME mfi_vsc7436     TYPE mfi      APP  app_vsc7436           KMOD  servalt       MACHINE servalt  )
    IMG_TARGET(NAME mfi_vsc7416     TYPE mfi      APP  app_vsc7416           KMOD  serval1       MACHINE serval1  )
    IMG_TARGET(NAME mfi_vsc7410     TYPE mfi      APP  app_vsc7410           KMOD  servalt       MACHINE servalt  )
    IMG_TARGET(NAME mfi_vsc7430     TYPE mfi      APP  app_vsc7430           KMOD  servalt       MACHINE servalt  )
    IMG_TARGET(NAME mfi_vsc7437     TYPE mfi      APP  app_vsc7437           KMOD  servalt       MACHINE servalt  )
    IMG_TARGET(NAME mfi_vsc7435     TYPE mfi      APP  app_vsc7435           KMOD  servalt       MACHINE servalt  )
    IMG_TARGET(NAME mfi_vsc7415     TYPE mfi      APP  app_vsc7415           KMOD  servalt       MACHINE servalt  )
    IMG_TARGET(NAME mfi_vsc7424     TYPE mfi      APP  app_vsc7424           KMOD  luton26       MACHINE luton10  )
    IMG_TARGET(NAME mfi_vsc7414     TYPE mfi      APP  app_vsc7414           KMOD  serval1       MACHINE serval1  )
    IMG_TARGET(NAME mfi_vsc7425     TYPE mfi      APP  app_vsc7425           KMOD  luton26       MACHINE luton26  )
    IMG_TARGET(NAME mfi_vsc7426     TYPE mfi      APP  app_vsc7426           KMOD  luton26       MACHINE luton26  )
    IMG_TARGET(NAME mfi_vsc7427     TYPE mfi      APP  app_vsc7427           KMOD  luton26       MACHINE luton26  )
    IMG_TARGET(NAME mfi_vsc7440     TYPE mfi      APP  app_vsc7440           KMOD  servalt       MACHINE servalt  )
    IMG_TARGET(NAME mfi_vsc7444     TYPE mfi      APP  app_vsc7444           KMOD  jaguar2       MACHINE jaguar2c )
    #IMG_TARGET(NAME mfi_vsc7442     TYPE mfi      APP  app_vsc7442           KMOD  jaguar2-cu48  MACHINE jaguar2c )
    IMG_TARGET(NAME mfi_vsc7448     TYPE mfi      APP  app_vsc7448           KMOD  jaguar2       MACHINE jaguar2c )
    IMG_TARGET(NAME mfi_vsc7448_48  TYPE mfi      APP  app_vsc7448           KMOD  jaguar2-cu48  MACHINE jaguar2c )
    #IMG_TARGET(NAME mfi_vsc7449     TYPE mfi      APP  app_vsc7449           KMOD  jaguar2-cu48  MACHINE jaguar2c )

elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
    IMG_TARGET(NAME fit_ls1046_vsc7468  TYPE fit      APP app_vsc7468         MACHINE ls1046a)
    IMG_TARGET(NAME fit_vsc7558TSN      TYPE ext4     APP app_vsc7558TSN      MACHINE fireant)
    IMG_TARGET(NAME fit_vsc7552TSN      TYPE ext4     APP app_vsc7552TSN      MACHINE fireant)
    IMG_TARGET(NAME fit_vsc7549TSN      TYPE ext4     APP app_vsc7549TSN      MACHINE fireant)
    # IMG_TARGET(NAME fit_ls1046_vsc7449  TYPE fit       APP app_vsc7449         MACHINE ls1046a)
    # IMG_TARGET(NAME fit_ls1046_vsc7437  TYPE fit       APP app_vsc7437         MACHINE ls1046a)
    # IMG_TARGET(NAME fit_ls1046_vsc7438  TYPE fit       APP app_vsc7438         MACHINE ls1046a)
    # IMG_TARGET(NAME fit_ls1046_vsc7514  TYPE fit       APP app_vsc7514         MACHINE ls1046a)
    # IMG_TARGET(NAME fit_ls1046_vsc7512  TYPE fit       APP app_vsc7512         MACHINE ls1046a)

elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "armv7l")
    IMG_TARGET(NAME fit_bbb_vsc7428     TYPE fit    APP app_vsc7428         MACHINE BeagleBoneBlack)
    IMG_TARGET(NAME fit_bbb_vsc7429     TYPE fit    APP app_vsc7429         MACHINE BeagleBoneBlack)
    IMG_TARGET(NAME fit_bbb_vsc7418     TYPE fit    APP app_vsc7418         MACHINE BeagleBoneBlack)
    IMG_TARGET(NAME fit_bbb_vsc7468     TYPE fit    APP app_vsc7468         MACHINE BeagleBoneBlack)
    IMG_TARGET(NAME fit_bbb_vsc7449     TYPE fit    APP app_vsc7449         MACHINE BeagleBoneBlack)
    IMG_TARGET(NAME fit_bbb_vsc7436     TYPE fit    APP app_vsc7436         MACHINE BeagleBoneBlack)
    IMG_TARGET(NAME fit_bbb_vsc7437     TYPE fit    APP app_vsc7437         MACHINE BeagleBoneBlack)
    IMG_TARGET(NAME fit_bbb_vsc7438     TYPE fit    APP app_vsc7438         MACHINE BeagleBoneBlack)
    IMG_TARGET(NAME fit_bbb_vsc7514     TYPE fit    APP app_vsc7514         MACHINE BeagleBoneBlack)
    IMG_TARGET(NAME fit_bbb_vsc7512     TYPE fit    APP app_vsc7512         MACHINE BeagleBoneBlack)
    IMG_TARGET(NAME fit_bbb_vsc7558TSN  TYPE fit    APP app_vsc7558TSN      MACHINE BeagleBoneBlack)

endif()
