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

project(meba)

cmake_minimum_required(VERSION 2.8.12)

include_directories(include)
include_directories(../mesa/include)
include_directories(../include)
include_directories(./src)
include_directories(./src/drivers)

option(BUILD_MEBA_ALL "Build all MEBA layers" OFF)
option(BUILD_MEBA_KERNEL_BOARD_MODULE_ALL "Build all MEBA kernel board modules" OFF)

macro(MEBA_LIB)
    set(LIST_OF_MEBA_TARGETS ${ARGN})

    foreach(arg ${ARGN})
        option(BUILD_MEBA_${arg} "Build the MEBA layer for ${arg}" OFF)
        FILE(GLOB c_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/src/${arg}/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/*.c")

        add_library(meba_${arg} SHARED ${c_files})

        if (${BUILD_ALL} OR ${BUILD_MEBA_ALL})
            set(BUILD_MEBA_${arg} ON CACHE BOOL "" FORCE)
        endif()

        if (${BUILD_MEBA_${arg}})
            message(STATUS "Build MEBA layer for ${arg}")
            set_target_properties(meba_${arg} PROPERTIES EXCLUDE_FROM_ALL FALSE)
        else()
            set_target_properties(meba_${arg} PROPERTIES EXCLUDE_FROM_ALL TRUE)
        endif()
    endforeach()
endmacro()

MEBA_LIB(serval1 caracal jr2 servalt ocelot ocelot_pcb121 jag3s5)

file(GLOB_RECURSE MEBA_HDRS "include/**.h")
doxygen_target(TARGET meba NAME "MEBA" FILES ${MEBA_HDRS} INCLUDES -I${CMAKE_CURRENT_SOURCE_DIR}/include)

macro(MEBA_KERNEL_BOARD_MODULE KMOD KARCH)
    option(BUILD_MEBA_KERNEL_BOARD_MODULE_${KMOD} "Build the MEBA kernel board module for ${KMOD}" OFF)

    if (${BUILD_MEBA_KERNEL_BOARD_MODULE_ALL})
        set(BUILD_MEBA_KERNEL_BOARD_MODULE_${KMOD} ON CACHE BOOL "" FORCE)
    endif()

    set(BSP "${RELOCATED_HOST_DIR}/../../..")
    set(MFI "${BSP}/mipsel-mips32r2-linux-uclibc/${KARCH}/x86_64-linux/usr/bin/mfi.rb")
    set(KSRC "${BSP}/mipsel-mips32r2-linux-uclibc/${KARCH}/x86_64-linux/usr/mipsel-buildroot-linux-uclibc/sysroot/usr/src")
    set(KMODSRC "${CMAKE_SOURCE_DIR}/meba/linux_kernel_modules")
    set(KMOD_BUILD "${CMAKE_BINARY_DIR}/meba/linux_kernel_modules/${KMOD}")
    set(KOPT ARCH=mips CROSS_COMPILE=${BSP}/mipsel-mips32r2-linux-gnu/smb/x86_64-linux/usr/bin/mipsel-linux-)
    set(MSCC_PRODUCT_HW "BOARD_OCELOT_REF")

    SET(KBUILD_CMD $(MAKE))
    SET(KBUILD_CMD ${KBUILD_CMD} -C ${KSRC}/mscc-linux-${KARCH})
    SET(KBUILD_CMD ${KBUILD_CMD} ${KOPT})
    SET(KBUILD_CMD ${KBUILD_CMD} M=${KMOD_BUILD})
    SET(KBUILD_CMD ${KBUILD_CMD} src=${KMODSRC})
    SET(KBUILD_CMD ${KBUILD_CMD} BOARD_DIR=${KMOD})
    SET(KBUILD_CMD ${KBUILD_CMD} EXTRA_CFLAGS="-DVTSS_${MSCC_PRODUCT_HW}")

    #message(STATUS "${KBUILD_CMD}")

    add_custom_command(
        OUTPUT  linux_kernel_modules/${KMOD}/mscc_board.ko
        COMMAND mkdir -p ${KMOD_BUILD}/${KARCH}
        COMMAND touch ${KMOD_BUILD}/Makefile
        COMMAND ${KBUILD_CMD}
    )

    if (${BUILD_MEBA_KERNEL_BOARD_MODULE_${KMOD}})
        add_custom_target(kernel_module_${KMOD} ALL DEPENDS linux_kernel_modules/${KMOD}/mscc_board.ko)
    else()
        add_custom_target(kernel_module_${KMOD} DEPENDS linux_kernel_modules/${KMOD}/mscc_board.ko)
    endif()
endmacro()

if (CMAKE_SYSTEM_PROCESSOR STREQUAL "mipsel")
    MEBA_KERNEL_BOARD_MODULE(jaguar2 jaguar2c)
    MEBA_KERNEL_BOARD_MODULE(jaguar2-cu48 jaguar2c)
    MEBA_KERNEL_BOARD_MODULE(luton26 luton26)
    MEBA_KERNEL_BOARD_MODULE(ocelot ocelot)
    MEBA_KERNEL_BOARD_MODULE(serval1 serval1)
    MEBA_KERNEL_BOARD_MODULE(serval2 serval2)
    MEBA_KERNEL_BOARD_MODULE(servalt servalt)
endif()

