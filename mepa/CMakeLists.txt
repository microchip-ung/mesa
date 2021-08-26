# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

project(MEPA)

cmake_minimum_required(VERSION 2.8.12)

option(BUILD_MEPA_ALL "Build all MEPA libraries" OFF)
mark_as_advanced(BUILD_MEPA_ALL)

include_directories(../me/include)
include_directories(../mesa/include)
include_directories(../meba/include)
include_directories(include)
include_directories(src/vtss/include)

set(src_vtss src/vtss.c
             src/vtss_ts.c
             src/vtss/src/common/vtss_phy_common.c
             src/vtss/src/phy_1g/vtss_phy_init_scripts.c
             src/vtss/src/phy_1g/vtss_phy_veriphy.c
             src/vtss/src/phy_1g/vtss_phy.c
             src/vtss/src/macsec/vtss_macsec_api.c
             src/vtss/src/phy_10g/vtss_venice_c_sd10g65_setup.c
             src/vtss/src/phy_10g/vtss_phy_10g_malibu.c
             src/vtss/src/phy_10g/vtss_malibu_b_f2df_df2f_sd10g65_setup.c
             src/vtss/src/phy_10g/vtss_venice_c_f2df_sd10g65_setup.c
             src/vtss/src/phy_10g/vtss_malibu_b_host_pma_sd10g65_setup.c
             src/vtss/src/phy_10g/vtss_malibu_line_pma_sd10g65_setup.c
             src/vtss/src/phy_10g/vtss_phy_10g.c
             src/vtss/src/phy_10g/vtss_phy_10g_api.c
             src/vtss/src/phy_10g/vtss_wis_api.c
             src/vtss/src/phy_10g/vtss_malibu_b_pll5g_setup.c
             src/vtss/src/phy_10g/vtss_malibu_f2df_df2f_sd10g65_setup.c
             src/vtss/src/phy_10g/vtss_malibu_host_pma_sd10g65_setup.c
             src/vtss/src/phy_10g/vtss_phy_10g_venice.c
             src/vtss/src/phy_10g/vtss_malibu_b_line_pma_sd10g65_setup.c
             src/vtss/src/phy_10g/vtss_venice_f2df_sd10g65_setup.c
             src/vtss/src/phy_10g/vtss_pll5g_procs.c
             src/vtss/src/phy_10g/vtss_sd10g65_procs.c
             src/vtss/src/phy_10g/vtss_sd10g65_apc_procs.c
             src/vtss/src/ts/vtss_phy_ts_api.c
             src/vtss/src/ts/vtss_phy_ewis.c
             src/vtss/src/ts/vtss_phy_ts_util.c
             src/vtss/src/mesa_phy.c)

add_library(mepa_vtss SHARED ${src_vtss})
add_library(mepa_vtss_static STATIC ${src_vtss})
set_target_properties(mepa_vtss_static PROPERTIES OUTPUT_NAME mepa_vtss)

add_library(mepa_lan8814 SHARED src/microchip/lan8814.c src/microchip/lan8814_ts.c)
add_library(mepa_lan8814_static STATIC src/microchip/lan8814.c src/microchip/lan8814_ts.c)
set_target_properties(mepa_lan8814_static PROPERTIES OUTPUT_NAME mepa_lan8814)

include_directories(".")
include_directories("src/aqr/AQR_API_2.6.1/include")
include_directories("src/aqr/AQR_API_2.6.1/include/registerMap")
include_directories("src/aqr/AQR_API_2.6.1/include/registerMap/APPIA")
include_directories("src/aqr/AQR_API_2.6.1/include/registerMap/EUR")
include_directories("src/aqr/AQR_API_2.6.1/include/registerMap/HHD")
include_directories("src/aqr/aqr_phy_fw")

set(src_aqr src/aqr/phy_driver.c
	    src/aqr/vtss_platform/AQ_PhyInterface.c
	    src/aqr/vtss_platform/AQ_PlatformRoutines.c
	    src/aqr/AQR_API_2.6.1/src/AQ_API.c
	    src/aqr/AQR_API_2.6.1/src/AQ_API_flash.c)


add_library(mepa_aqr SHARED ${src_aqr})
add_library(mepa_aqr_static STATIC ${src_aqr})
set_target_properties(mepa_aqr_static PROPERTIES OUTPUT_NAME mepa_aqr)

include_directories("src/intel/GPY_API_v251/src/os/linux")
include_directories("src/intel/GPY_API_v251/src/inc")

set(src_intel src/intel/phy_driver.c
              src/intel/GPY_API_v251/src/api/phy/gpy211_chip.c
              src/intel/GPY_API_v251/src/api/phy/gpy211_phy.c)

set(CMAKE_C_FLAGS "-DP31G_B0=1 -DSAFE_C_LIB=0")
add_library(mepa_intel SHARED ${src_intel})
add_library(mepa_intel_static STATIC ${src_intel})
set_target_properties(mepa_intel_static PROPERTIES OUTPUT_NAME mepa_intel)


include_directories("src/ksz9031")

set(src_ksz9031 src/ksz9031/phy_driver.c )

set(CMAKE_C_FLAGS "-DP31G_B0=1 -DSAFE_C_LIB=0")
add_library(mepa_ksz9031 SHARED ${src_ksz9031})
add_library(mepa_ksz9031_static STATIC ${src_ksz9031})
set_target_properties(mepa_ksz9031_static PROPERTIES OUTPUT_NAME mepa_ksz9031)
