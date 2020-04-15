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

add_library(mesa_demo_lib STATIC trace.c cli.c port.c mac.c vlan.c ip.c debug.c symreg.c test.c spi.c uio.c ${MESA_RPC} json_rpc.c)
target_include_directories(mesa_demo_lib PUBLIC ${CMAKE_BINARY_DIR}/mesa-ag/)

# machine -> SOC family (currently don't care)
set(mfi_socfam_luton10  "luton26")
set(mfi_socfam_luton26  "luton26")
set(mfi_socfam_serval1  "serval1")
set(mfi_socfam_jaguar2  "jaguar2")
set(mfi_socfam_serval2  "jaguar2")
set(mfi_socfam_servalt  "servalt")
set(mfi_socfam_jaguar2c "jaguar2")
set(mfi_socfam_ocelot   "ocelot")

# machine -> Chip no.
set(mfi_chipno_luton10  "2")
set(mfi_chipno_luton26  "2")
set(mfi_chipno_serval1  "4")
set(mfi_chipno_jaguar2  "5")
set(mfi_chipno_serval2  "7")
set(mfi_chipno_servalt  "6")
set(mfi_chipno_jaguar2c "7")
set(mfi_chipno_ocelot   "8")

# machine -> kernel
set(mfi_kernel_luton10  "luton26")
set(mfi_kernel_luton26  "luton26")
set(mfi_kernel_serval1  "serval1")
set(mfi_kernel_jaguar2  "jaguar2")
set(mfi_kernel_serval2  "serval2")
set(mfi_kernel_servalt  "servalt")
set(mfi_kernel_jaguar2c "jaguar2c")
set(mfi_kernel_ocelot   "ocelot")

macro(TAR_TARGET)
    set(options )
    set(oneValueArgs NAME MESA_DEMO_SYMLINK)
    set(multiValueArgs EXECUTABLES)
    cmake_parse_arguments(TAR "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(solibs  "")
    set(sofiles "")
    set(efiles  "")

    foreach(E ${TAR_EXECUTABLES})
        list(APPEND efiles "$<TARGET_FILE:${E}>")

        get_target_property(DEPS ${E} LINK_LIBRARIES)
        foreach(dep ${DEPS})
            #message(STATUS "${E}: ${dep}")
            if (NOT ${dep} STREQUAL "DEPS-NOTFOUND")
                get_target_property(dep_type ${dep} TYPE)
                if(${dep_type} STREQUAL "SHARED_LIBRARY")
                    list(APPEND sofiles "$<TARGET_FILE:${dep}>")
                    list(APPEND solibs "${dep}")
                endif()
            endif()
        endforeach()
    endforeach()

    set(install_dir "${TAR_NAME}_")
    add_custom_command(
        OUTPUT ${TAR_NAME}
        DEPENDS ${TAR_EXECUTABLES} ${solibs}
        COMMAND rm -rf ${install_dir} ${TAR_NAME}.tar
        COMMAND mkdir -p ${install_dir}/usr/bin
        COMMAND mkdir -p ${install_dir}/usr/lib
        COMMAND install -D -t ${install_dir}/usr/bin ${efiles}
        COMMAND install -D -t ${install_dir}/usr/lib ${sofiles}
        COMMAND ${CMAKE_STRIP} -s ${install_dir}/usr/bin/*
        COMMAND ${CMAKE_STRIP}    ${install_dir}/usr/lib/*
        COMMAND ln -s ${TAR_MESA_DEMO_SYMLINK} ${install_dir}/usr/bin/mesa-demo
        COMMAND tar --owner=root --group=root -C ${install_dir} -cf ${TAR_NAME} .
    )
endmacro()

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
    target_link_libraries(${A_NAME} mesa_demo_lib ${A_MESA} ${A_MEBA} json-c)
    set_target_properties(${A_NAME} PROPERTIES OUTPUT_NAME "mesa-demo-${A_MESA}")

    TAR_TARGET(NAME ${A_NAME}.tar EXECUTABLES ${A_NAME} cli er base64decode MESA_DEMO_SYMLINK "mesa-demo-${A_MESA}")

    if (${A_NAME})
        set_target_properties(${A_NAME} PROPERTIES EXCLUDE_FROM_ALL FALSE)
    else()
        set_target_properties(${A_NAME} PROPERTIES EXCLUDE_FROM_ALL TRUE)
    endif()
endmacro()

macro(MFI_TARGET)
    set(options )
    set(oneValueArgs NAME APP KMOD MACHINE)
    set(multiValueArgs )
    cmake_parse_arguments(MFI "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(MFI_SOCFAM ${mfi_socfam_${MFI_MACHINE}})
    set(MFI_CHIPNO ${mfi_chipno_${MFI_MACHINE}})
    set(MFI_KERNEL ${mfi_kernel_${MFI_MACHINE}})

    option(${MFI_NAME} "Build the MESA DEMO for ${MFI_MESA}/${MFI_MEBA}" OFF)
    if (${BUILD_MESA_IMG_ALL} OR ${BUILD_ALL})
        set(${MFI_NAME} ON CACHE BOOL "" FORCE)
    endif()

    set(BSP "${RELOCATED_HOST_DIR}/../../..")
    set(MFI "${BSP}/mipsel-mips32r2-linux-uclibc/${MFI_KERNEL}/x86_64-linux/usr/bin/mfi.rb")

    set(MFI_STAGE1 ${MFI} -o ${MFI_NAME}.mfi)
    set(MFI_STAGE1 ${MFI_STAGE1} stage1)
    set(MFI_STAGE1 ${MFI_STAGE1} --kernel-set ${BSP}/mipsel-mips32r2-linux-uclibc/${MFI_KERNEL}/mscc-linux-${MFI_KERNEL}.bin.xz)
    set(MFI_STAGE1 ${MFI_STAGE1} --initrd-set ${MFI_NAME}.squashfs)
    set(MFI_STAGE1 ${MFI_STAGE1} --kernel-command "init=/sbin/init loglevel=4")
    set(MFI_STAGE1 ${MFI_STAGE1} --machine ${MFI_MACHINE})
    set(MFI_STAGE1 ${MFI_STAGE1} --soc-name ${MFI_SOCFAM})
    set(MFI_STAGE1 ${MFI_STAGE1} --soc-no ${MFI_CHIPNO})

    # TODO, install target, and dependent targets
    add_custom_command(
        OUTPUT ${MFI_NAME}.mfi
        DEPENDS kernel_module_${MFI_KMOD} ${MFI_APP}.tar

        COMMAND rm -rf install_${MFI_NAME} ${MFI_NAME}.squashfs ${MFI_NAME}.mfi
        COMMAND mkdir -p install_${MFI_NAME}/switch
        COMMAND mkdir -p install_${MFI_NAME}/lib/modules/board
        COMMAND tar   -C install_${MFI_NAME} -xf ${MFI_APP}.tar
        COMMAND tar   -C install_${MFI_NAME} -xf ${BSP}/mipsel-mips32r2-linux-gnu/smb/rootfs.tar
        COMMAND cp ${CMAKE_BINARY_DIR}/meba/linux_kernel_modules/${MFI_KMOD}/mscc_board.ko install_${MFI_NAME}/lib/modules/board/mscc_board.ko
        COMMAND mksquashfs install_${MFI_NAME}/* ${MFI_NAME}.squashfs -comp xz -all-root > /dev/null

        COMMAND ${MFI_STAGE1}
    )

    if (${MFI_NAME})
        add_custom_target(${MFI_NAME}_mfi ALL DEPENDS ${MFI_NAME}.mfi)
        message(STATUS "Adding: ${MFI_NAME} [machine: ${MFI_MACHINE} socfam: ${MFI_SOCFAM} chipno: ${MFI_CHIPNO} kernel: ${MFI_KERNEL} kmod ${MFI_KMOD}]")
    endif()
endmacro()

add_custom_command(
    OUTPUT ls1046-kernel.img
    DEPENDS ${RELOCATED_HOST_DIR}/../mscc-linux-ls1046.bin.xz
    COMMAND xz -d -c ${RELOCATED_HOST_DIR}/../mscc-linux-ls1046.bin.xz | gzip -f -c > ls1046-kernel.img
)

add_custom_command(
    OUTPUT bbb-kernel.img
    DEPENDS ${RELOCATED_HOST_DIR}/../mscc-linux-beaglebone.bin.xz
    COMMAND xz -d -c ${RELOCATED_HOST_DIR}/../mscc-linux-beaglebone.bin.xz | gzip -f -c > bbb-kernel.img
)

macro(FIT_TARGET)
    set(options )
    set(oneValueArgs NAME APP MACHINE)
    set(multiValueArgs )
    cmake_parse_arguments(A "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(ARCH "")
    if (CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64" AND A_MACHINE STREQUAL "ls1046a")
        set(ARCH "arm64")
        set(KERNEL "ls1046-kernel.img")
        set(KCOMP "gzip")
        set(FDT "mscc-ls1046a-jaguar2-pcb110.dtb")
        set(FDTADDR "0x90000000")

    elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "armv7l" AND A_MACHINE STREQUAL "BeagleBoneBlack")
        set(ARCH "arm")
        set(KERNEL "bbb-kernel.img")
        set(KCOMP "gzip")
        set(FDT "am335x-boneblack-mscc.dtb")
        set(FDTLOAD "#")
    endif()

    option(${A_NAME} "Build the MESA-FIT DEMO for ${A_MESA}/${A_MEBA}" OFF)
    if (${BUILD_MESA_IMG_ALL} OR ${BUILD_ALL})
        set(${A_NAME} ON CACHE BOOL "" FORCE)
    endif()

    if (ARCH STREQUAL "")
        message(FATAL_ERROR "${CMAKE_SYSTEM_PROCESSOR} does not support the ${A_MACHINE} target")
        set(${A_NAME} OFF CACHE BOOL "" FORCE)
    endif()

    set(its_src "")
    set(its_src "${its_src}/dts-v1/\n;")
    set(its_src "${its_src}/ {\n")
    set(its_src "${its_src}        description = \"Image file for the MESA SDK Demo on target ${A_MACHINE}\";\n")
    set(its_src "${its_src}\n")
    set(its_src "${its_src}        images {\n")
    set(its_src "${its_src}                kernel {\n")
    set(its_src "${its_src}                        description = \"${CMAKE_SYSTEM_PROCESSOR} Linux kernel\";\n")
    set(its_src "${its_src}                        data = /incbin/(\"${KERNEL}\");\n")
    set(its_src "${its_src}                        type = \"kernel\";\n")
    set(its_src "${its_src}                        arch = \"${ARCH}\";\n")
    set(its_src "${its_src}                        os = \"linux\";\n")
    set(its_src "${its_src}                        compression = \"${KCOMP}\";\n")
    set(its_src "${its_src}                        load = <0x80080000>;\n")
    set(its_src "${its_src}                        entry = <0x80080000>;\n")
    set(its_src "${its_src}                };\n")
    set(its_src "${its_src}                ramdisk {\n")
    set(its_src "${its_src}                        description = \"ramdisk\";\n")
    set(its_src "${its_src}                        data = /incbin/(\"${CMAKE_BINARY_DIR}/mesa/demo/${A_NAME}.rootfs\");\n")
    set(its_src "${its_src}                        type = \"ramdisk\";\n")
    set(its_src "${its_src}                        arch = \"${ARCH}\";\n")
    set(its_src "${its_src}                        os = \"linux\";\n")
    set(its_src "${its_src}                        load = <0x88080000>;\n")
    set(its_src "${its_src}                        compression = \"none\";\n")
    set(its_src "${its_src}                };\n")
    set(its_src "${its_src}                fdt {\n")
    set(its_src "${its_src}                        description = \"Flattened Device Tree blob\";\n")
    set(its_src "${its_src}                        data = /incbin/(\"${RELOCATED_HOST_DIR}/../${FDT}\");\n")
    set(its_src "${its_src}                        type = \"flat_dt\";\n")
    set(its_src "${its_src}                        arch = \"${ARCH}\";\n")
    set(its_src "${its_src}                        ${FDTLOAD}load = <${FDTADDR}>;\n")
    set(its_src "${its_src}                        compression = \"none\";\n")
    set(its_src "${its_src}                };\n")
    set(its_src "${its_src}        };\n")
    set(its_src "${its_src}\n")
    set(its_src "${its_src}        configurations {\n")
    set(its_src "${its_src}                default = \"${A_MACHINE}\";\n")
    set(its_src "${its_src}                ${A_MACHINE} {\n")
    set(its_src "${its_src}                        description = \"Boot Linux kernel\";\n")
    set(its_src "${its_src}                        kernel = \"kernel\";\n")
    set(its_src "${its_src}                        fdt = \"fdt\";\n")
    set(its_src "${its_src}                        ramdisk = \"ramdisk\";\n")
    set(its_src "${its_src}                };\n")
    set(its_src "${its_src}        };\n")
    set(its_src "${its_src}};\n")

    file(GENERATE OUTPUT "mesa/demo/${A_NAME}.its" CONTENT "${its_src}")
    set(install_dir "install_${A_NAME}")
    add_custom_command(
        OUTPUT ${A_NAME}.itb
        DEPENDS ${KERNEL} ${A_APP}.tar
        COMMAND rm -rf ${install_dir} ${A_NAME}.rootfs
        COMMAND mkdir -p ${install_dir}
        COMMAND tar -C ${install_dir} -xf ${RELOCATED_HOST_DIR}/../rootfs.tar
        COMMAND tar -C ${install_dir} -xf ${A_APP}.tar
        COMMAND ${CMAKE_COMMAND} -E env "PATH=${RELOCATED_HOST_DIR}/bin:$ENV{PATH}" mksquashfs ${install_dir}/* ${A_NAME}.rootfs -comp xz -all-root
        COMMAND ${CMAKE_COMMAND} -E env "PATH=${RELOCATED_HOST_DIR}/bin:$ENV{PATH}" mkimage -f ${A_NAME}.its ${A_NAME}.itb
    )

    if (${A_NAME})
        add_custom_target(${A_NAME} ALL DEPENDS ${A_NAME}.itb)
    endif()
endmacro()

APP_TARGET(NAME app_vsc7410            MESA vsc7410            MEBA meba_servalt)
APP_TARGET(NAME app_vsc7414_afiot      MESA vsc7414_afiot      MEBA meba_serval1)
APP_TARGET(NAME app_vsc7415            MESA vsc7415            MEBA meba_servalt)
APP_TARGET(NAME app_vsc7416_afiot      MESA vsc7416_afiot      MEBA meba_serval1)
APP_TARGET(NAME app_vsc7418_afiot      MESA vsc7418_afiot      MEBA meba_serval1)
APP_TARGET(NAME app_vsc7418_afiot_ts   MESA vsc7418_afiot_ts   MEBA meba_serval1)
APP_TARGET(NAME app_vsc7423            MESA vsc7423            MEBA meba_caracal)
APP_TARGET(NAME app_vsc7424            MESA vsc7424            MEBA meba_caracal)
APP_TARGET(NAME app_vsc7425            MESA vsc7425            MEBA meba_caracal)
APP_TARGET(NAME app_vsc7426            MESA vsc7426            MEBA meba_caracal)
APP_TARGET(NAME app_vsc7427            MESA vsc7427            MEBA meba_caracal)
APP_TARGET(NAME app_vsc7428_pcnt10     MESA vsc7428_pcnt10     MEBA meba_caracal)
APP_TARGET(NAME app_vsc7429            MESA vsc7429            MEBA meba_caracal)
APP_TARGET(NAME app_vsc7430            MESA vsc7430            MEBA meba_servalt)
APP_TARGET(NAME app_vsc7435            MESA vsc7435            MEBA meba_servalt)
APP_TARGET(NAME app_vsc7436_pcnt9      MESA vsc7436_pcnt9      MEBA meba_servalt)
APP_TARGET(NAME app_vsc7437            MESA vsc7437            MEBA meba_servalt)
APP_TARGET(NAME app_vsc7438            MESA vsc7438            MEBA meba_jr2)
APP_TARGET(NAME app_vsc7438_ts         MESA vsc7438_ts         MEBA meba_jr2)
APP_TARGET(NAME app_vsc7440_pcnt9      MESA vsc7440_pcnt9      MEBA meba_servalt)
APP_TARGET(NAME app_vsc7442            MESA vsc7442            MEBA meba_jr2)
APP_TARGET(NAME app_vsc7444            MESA vsc7444            MEBA meba_jr2)
APP_TARGET(NAME app_vsc7448_pcnt29     MESA vsc7448_pcnt29     MEBA meba_jr2)
APP_TARGET(NAME app_vsc7448_pcnt51     MESA vsc7448_pcnt51     MEBA meba_jr2)
APP_TARGET(NAME app_vsc7449            MESA vsc7449            MEBA meba_jr2)
APP_TARGET(NAME app_vsc7464            MESA vsc7464            MEBA meba_jr2)
APP_TARGET(NAME app_vsc7468_pcnt26     MESA vsc7468_pcnt26     MEBA meba_jr2)
APP_TARGET(NAME app_vsc7468_pcnt29_st  MESA vsc7468_pcnt29_static     MEBA meba_jr2)
APP_TARGET(NAME app_vsc7468_pcnt29     MESA vsc7468_pcnt29     MEBA meba_jr2)
APP_TARGET(NAME app_vsc7468_pcnt29_ts  MESA vsc7468_pcnt29_ts  MEBA meba_jr2)
APP_TARGET(NAME app_vsc7468_pcnt51     MESA vsc7468_pcnt51     MEBA meba_jr2)
APP_TARGET(NAME app_vsc7512            MESA vsc7512            MEBA meba_ocelot_pcb121 )
APP_TARGET(NAME app_vsc7513            MESA vsc7513            MEBA meba_ocelot)
APP_TARGET(NAME app_vsc7513_afiot_ts   MESA vsc7513_afiot_ts   MEBA meba_ocelot)
APP_TARGET(NAME app_vsc7514            MESA vsc7514            MEBA meba_ocelot)
APP_TARGET(NAME app_vsc7514_afiot_ts   MESA vsc7514_afiot_ts   MEBA meba_ocelot)
APP_TARGET(NAME app_vsc7546_pcnt7      MESA vsc7546_pcnt7      MEBA meba_jag3s5)
APP_TARGET(NAME app_vsc7549_pcnt10     MESA vsc7549_pcnt10     MEBA meba_jag3s5)
APP_TARGET(NAME app_vsc7552_pcnt13     MESA vsc7552_pcnt13     MEBA meba_jag3s5)
APP_TARGET(NAME app_vsc7556_pcnt57     MESA vsc7556_pcnt57     MEBA meba_jag3s5)
APP_TARGET(NAME app_vsc7558_pcnt21     MESA vsc7558_pcnt21     MEBA meba_jag3s5)
APP_TARGET(NAME app_vsc7546_04_pcnt7   MESA vsc7546_04_pcnt7   MEBA meba_jag3s5)
APP_TARGET(NAME app_vsc7549_04_pcnt10  MESA vsc7549_04_pcnt10  MEBA meba_jag3s5)
APP_TARGET(NAME app_vsc7552_04_pcnt13  MESA vsc7552_04_pcnt13  MEBA meba_jag3s5)
APP_TARGET(NAME app_vsc7556_04_pcnt57  MESA vsc7556_04_pcnt57  MEBA meba_jag3s5)
APP_TARGET(NAME app_vsc7558_04_pcnt21  MESA vsc7558_04_pcnt21  MEBA meba_jag3s5)


if (CMAKE_SYSTEM_PROCESSOR STREQUAL "mipsel")
    MFI_TARGET(NAME mfi_vsc7428_pcnt10    APP  app_vsc7428_pcnt10    KMOD  luton26       MACHINE luton10  )
    MFI_TARGET(NAME mfi_vsc7429           APP  app_vsc7429           KMOD  luton26       MACHINE luton26  )
    MFI_TARGET(NAME mfi_vsc7423           APP  app_vsc7423           KMOD  luton26       MACHINE luton10  )
    MFI_TARGET(NAME mfi_vsc7468_pcnt29    APP  app_vsc7468_pcnt29    KMOD  jaguar2       MACHINE jaguar2c )
    MFI_TARGET(NAME mfi_vsc7468_pcnt29_st APP  app_vsc7468_pcnt29_st KMOD  jaguar2       MACHINE jaguar2c )
    MFI_TARGET(NAME mfi_vsc7468_pcnt29_ts APP  app_vsc7468_pcnt29_ts KMOD  jaguar2       MACHINE jaguar2c )
    #MFI_TARGET(NAME mfi_vsc7468_pcnt26    APP  app_vsc7468_pcnt26    KMOD  jaguar2-aqr   MACHINE jaguar2c )
    MFI_TARGET(NAME mfi_vsc7468_pcnt51    APP  app_vsc7468_pcnt51    KMOD  jaguar2-cu48  MACHINE jaguar2c )
    MFI_TARGET(NAME mfi_vsc7464           APP  app_vsc7464           KMOD  jaguar2       MACHINE jaguar2c )
    MFI_TARGET(NAME mfi_vsc7514           APP  app_vsc7514           KMOD  ocelot        MACHINE ocelot   )
    MFI_TARGET(NAME mfi_vsc7514_afiot_ts  APP  app_vsc7514_afiot_ts  KMOD  ocelot        MACHINE ocelot   )
    MFI_TARGET(NAME mfi_vsc7513           APP  app_vsc7513           KMOD  ocelot        MACHINE ocelot   )
    MFI_TARGET(NAME mfi_vsc7513_afiot_ts  APP  app_vsc7513_afiot_ts  KMOD  ocelot        MACHINE ocelot   )
    MFI_TARGET(NAME mfi_vsc7418_afiot     APP  app_vsc7418_afiot     KMOD  serval1       MACHINE serval1  )
    MFI_TARGET(NAME mfi_vsc7418_afiot_ts  APP  app_vsc7418_afiot_ts  KMOD  serval1       MACHINE serval1  )
    MFI_TARGET(NAME mfi_vsc7438           APP  app_vsc7438           KMOD  serval2       MACHINE serval2  )
    MFI_TARGET(NAME mfi_vsc7438_ts        APP  app_vsc7438_ts        KMOD  serval2       MACHINE serval2  )
    MFI_TARGET(NAME mfi_vsc7436_pcnt9     APP  app_vsc7436_pcnt9     KMOD  servalt       MACHINE servalt  )
    MFI_TARGET(NAME mfi_vsc7416_afiot     APP  app_vsc7416_afiot     KMOD  serval1       MACHINE serval1  )
    MFI_TARGET(NAME mfi_vsc7410           APP  app_vsc7410           KMOD  servalt       MACHINE servalt  )
    MFI_TARGET(NAME mfi_vsc7430           APP  app_vsc7430           KMOD  servalt       MACHINE servalt  )
    MFI_TARGET(NAME mfi_vsc7437           APP  app_vsc7437           KMOD  servalt       MACHINE servalt  )
    MFI_TARGET(NAME mfi_vsc7435           APP  app_vsc7435           KMOD  servalt       MACHINE servalt  )
    MFI_TARGET(NAME mfi_vsc7415           APP  app_vsc7415           KMOD  servalt       MACHINE servalt  )
    MFI_TARGET(NAME mfi_vsc7424           APP  app_vsc7424           KMOD  luton26       MACHINE luton10  )
    MFI_TARGET(NAME mfi_vsc7414_afiot     APP  app_vsc7414_afiot     KMOD  serval1       MACHINE serval1  )
    MFI_TARGET(NAME mfi_vsc7425           APP  app_vsc7425           KMOD  luton26       MACHINE luton26  )
    MFI_TARGET(NAME mfi_vsc7426           APP  app_vsc7426           KMOD  luton26       MACHINE luton26  )
    MFI_TARGET(NAME mfi_vsc7427           APP  app_vsc7427           KMOD  luton26       MACHINE luton26  )
    MFI_TARGET(NAME mfi_vsc7440_pcnt9     APP  app_vsc7440_pcnt9     KMOD  servalt       MACHINE servalt  )
    MFI_TARGET(NAME mfi_vsc7444           APP  app_vsc7444           KMOD  jaguar2       MACHINE jaguar2c )
    #MFI_TARGET(NAME mfi_vsc7442           APP  app_vsc7442           KMOD  jaguar2-cu48  MACHINE jaguar2c )
    MFI_TARGET(NAME mfi_vsc7448_pcnt29    APP  app_vsc7448_pcnt29    KMOD  jaguar2       MACHINE jaguar2c )
    MFI_TARGET(NAME mfi_vsc7448_pcnt51    APP  app_vsc7448_pcnt51    KMOD  jaguar2-cu48  MACHINE jaguar2c )
    #MFI_TARGET(NAME mfi_vsc7449           APP  app_vsc7449           KMOD  jaguar2-cu48  MACHINE jaguar2c )

elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
    FIT_TARGET(NAME fit_ls1046_vsc7468_pcnt29  APP app_vsc7468_pcnt29  MACHINE ls1046a)
    # FIT_TARGET(NAME fit_ls1046_vsc7468_pcnt29_st  APP app_vsc7468_pcnt29_st  MACHINE ls1046a)
    # FIT_TARGET(NAME fit_ls1046_vsc7449         APP app_vsc7449         MACHINE ls1046a)
    # FIT_TARGET(NAME fit_ls1046_vsc7437         APP app_vsc7437         MACHINE ls1046a)
    # FIT_TARGET(NAME fit_ls1046_vsc7438         APP app_vsc7438         MACHINE ls1046a)
    # FIT_TARGET(NAME fit_ls1046_vsc7514         APP app_vsc7514         MACHINE ls1046a)
    # FIT_TARGET(NAME fit_ls1046_vsc7512         APP app_vsc7512         MACHINE ls1046a)

elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "armv7l")
    FIT_TARGET(NAME fit_bbb_vsc7428_pcnt10  APP app_vsc7428_pcnt10  MACHINE BeagleBoneBlack)
    FIT_TARGET(NAME fit_bbb_vsc7429         APP app_vsc7429         MACHINE BeagleBoneBlack)
    FIT_TARGET(NAME fit_bbb_vsc7418_afiot   APP app_vsc7418_afiot   MACHINE BeagleBoneBlack)
    FIT_TARGET(NAME fit_bbb_vsc7468_pcnt29  APP app_vsc7468_pcnt29  MACHINE BeagleBoneBlack)
    FIT_TARGET(NAME fit_bbb_vsc7449         APP app_vsc7449         MACHINE BeagleBoneBlack)
    FIT_TARGET(NAME fit_bbb_vsc7436_pcnt9   APP app_vsc7436_pcnt9   MACHINE BeagleBoneBlack)
    FIT_TARGET(NAME fit_bbb_vsc7437         APP app_vsc7437         MACHINE BeagleBoneBlack)
    FIT_TARGET(NAME fit_bbb_vsc7438         APP app_vsc7438         MACHINE BeagleBoneBlack)
    FIT_TARGET(NAME fit_bbb_vsc7514         APP app_vsc7514         MACHINE BeagleBoneBlack)
    FIT_TARGET(NAME fit_bbb_vsc7512         APP app_vsc7512         MACHINE BeagleBoneBlack)
    FIT_TARGET(NAME fit_bbb_vsc7558_04_pcnt21 APP app_vsc7558_04_pcnt21 MACHINE BeagleBoneBlack)

endif()
