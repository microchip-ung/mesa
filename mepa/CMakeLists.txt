# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

project(MEPA)

cmake_minimum_required(VERSION 2.8.12)

option(BUILD_MEPA_ALL "Build all MEPA libraries" OFF)
mark_as_advanced(BUILD_MEPA_ALL)

set(inc_mepa ../me/include include)

set(src_vtss vtss/src/vtss.c
             vtss/src/vtss_ts.c
             vtss/src/common/vtss_phy_common.c
             vtss/src/phy_1g/vtss_phy_init_scripts.c
             vtss/src/phy_1g/vtss_phy_veriphy.c
             vtss/src/phy_1g/vtss_phy.c
             vtss/src/macsec/vtss_macsec_api.c
             vtss/src/phy_10g/vtss_venice_c_sd10g65_setup.c
             vtss/src/phy_10g/vtss_phy_10g_malibu.c
             vtss/src/phy_10g/vtss_malibu_b_f2df_df2f_sd10g65_setup.c
             vtss/src/phy_10g/vtss_venice_c_f2df_sd10g65_setup.c
             vtss/src/phy_10g/vtss_malibu_b_host_pma_sd10g65_setup.c
             vtss/src/phy_10g/vtss_malibu_line_pma_sd10g65_setup.c
             vtss/src/phy_10g/vtss_phy_10g.c
             vtss/src/phy_10g/vtss_phy_10g_api.c
             vtss/src/phy_10g/vtss_wis_api.c
             vtss/src/phy_10g/vtss_malibu_b_pll5g_setup.c
             vtss/src/phy_10g/vtss_malibu_f2df_df2f_sd10g65_setup.c
             vtss/src/phy_10g/vtss_malibu_host_pma_sd10g65_setup.c
             vtss/src/phy_10g/vtss_phy_10g_venice.c
             vtss/src/phy_10g/vtss_malibu_b_line_pma_sd10g65_setup.c
             vtss/src/phy_10g/vtss_venice_f2df_sd10g65_setup.c
             vtss/src/phy_10g/vtss_pll5g_procs.c
             vtss/src/phy_10g/vtss_sd10g65_procs.c
             vtss/src/phy_10g/vtss_sd10g65_apc_procs.c
             vtss/src/ts/vtss_phy_ts_api.c
             vtss/src/ts/vtss_phy_ewis.c
             vtss/src/ts/vtss_phy_ts_util.c
             vtss/src/mesa_phy.c)
set(inc_vtss vtss/include)

add_library(mepa_vtss        SHARED ${src_vtss})
add_library(mepa_vtss_static STATIC ${src_vtss})
set_target_properties(mepa_vtss_static PROPERTIES OUTPUT_NAME mepa_vtss)
target_include_directories(mepa_vtss        PUBLIC ${inc_mepa} PRIVATE ${inc_vtss})
target_include_directories(mepa_vtss_static PUBLIC ${inc_mepa} PRIVATE ${inc_vtss})

set(def_vtss_10g_only -DVTSS_OPT_PHY_1G=0
                      -DVTSS_OPT_PHY_10G=1)
add_library(mepa_vtss_10g_only        SHARED ${src_vtss})
add_library(mepa_vtss_10g_only_static STATIC ${src_vtss})
set_target_properties(mepa_vtss_10g_only_static PROPERTIES OUTPUT_NAME mepa_10g_only_vtss)
target_include_directories(mepa_vtss_10g_only        PUBLIC ${inc_mepa} PRIVATE ${inc_vtss})
target_include_directories(mepa_vtss_10g_only_static PUBLIC ${inc_mepa} PRIVATE ${inc_vtss})
target_compile_definitions(mepa_vtss_10g_only        PUBLIC ${def_vtss_10g_only})
target_compile_definitions(mepa_vtss_10g_only_static PUBLIC ${def_vtss_10g_only})

set(def_vtss_ts -DVTSS_OPT_PHY_TIMESTAMP=1)
add_library(mepa_vtss_ts        SHARED ${src_vtss})
add_library(mepa_vtss_ts_static STATIC ${src_vtss})
set_target_properties(mepa_vtss_ts_static PROPERTIES OUTPUT_NAME mepa_vtss_ts)
target_include_directories(mepa_vtss_ts        PUBLIC ${inc_mepa} PRIVATE ${inc_vtss})
target_include_directories(mepa_vtss_ts_static PUBLIC ${inc_mepa} PRIVATE ${inc_vtss})
target_compile_definitions(mepa_vtss_ts        PUBLIC ${def_vtss_ts})
target_compile_definitions(mepa_vtss_ts_static PUBLIC ${def_vtss_ts})

set(def_vtss_10g_ts -DVTSS_OPT_PHY_10G=1
                    -DVTSS_OPT_PHY_TIMESTAMP=1)
add_library(mepa_vtss_10g_ts        SHARED ${src_vtss})
add_library(mepa_vtss_10g_ts_static STATIC ${src_vtss})
set_target_properties(mepa_vtss_10g_ts_static PROPERTIES OUTPUT_NAME mepa_10g_ts_vtss)
target_include_directories(mepa_vtss_10g_ts        PUBLIC ${inc_mepa} PRIVATE ${inc_vtss})
target_include_directories(mepa_vtss_10g_ts_static PUBLIC ${inc_mepa} PRIVATE ${inc_vtss})
target_compile_definitions(mepa_vtss_10g_ts        PUBLIC ${def_vtss_10g_ts})
target_compile_definitions(mepa_vtss_10g_ts_static PUBLIC ${def_vtss_10g_ts})

set(def_vtss_10g_macsec_ts -DVTSS_OPT_PHY_10G=1
                           -DVTSS_OPT_PHY_MACSEC=1
                           -DVTSS_OPT_PHY_TIMESTAMP=1)
add_library(mepa_vtss_10g_macsec_ts        SHARED ${src_vtss})
add_library(mepa_vtss_10g_macsec_ts_static STATIC ${src_vtss})
set_target_properties(mepa_vtss_10g_macsec_ts_static PROPERTIES OUTPUT_NAME mepa_vtss_10g_macsec_ts)
target_include_directories(mepa_vtss_10g_macsec_ts        PUBLIC ${inc_mepa} PRIVATE ${inc_vtss})
target_include_directories(mepa_vtss_10g_macsec_ts_static PUBLIC ${inc_mepa} PRIVATE ${inc_vtss})
target_compile_definitions(mepa_vtss_10g_macsec_ts        PUBLIC ${def_vtss_10g_macsec_ts})
target_compile_definitions(mepa_vtss_10g_macsec_ts_static PUBLIC ${def_vtss_10g_macsec_ts})

set(src_lan8814 microchip/lan8814/src/lan8814.c
                microchip/lan8814/src/lan8814_ts.c)
set(inc_lan8814 mepa/microchip/lan8814)
add_library(mepa_lan8814        SHARED ${src_lan8814})
add_library(mepa_lan8814_static STATIC ${src_lan8814})
set_target_properties(mepa_lan8814_static PROPERTIES OUTPUT_NAME mepa_lan8814)
target_include_directories(mepa_lan8814        PUBLIC ${inc_mepa} PRIVATE ${inc_lan8814})
target_include_directories(mepa_lan8814_static PUBLIC ${inc_mepa} PRIVATE ${inc_lan8814})

include_directories(".")

set(src_aqr aqr/phy_driver.c
            aqr/vtss_platform/AQ_PhyInterface.c
            aqr/vtss_platform/AQ_PlatformRoutines.c
            aqr/AQR_API_2.6.1/src/AQ_API.c
            aqr/AQR_API_2.6.1/src/AQ_API_flash.c)
set(inc_aqr aqr/AQR_API_2.6.1/include
            aqr/AQR_API_2.6.1/include/registerMap
            aqr/AQR_API_2.6.1/include/registerMap/APPIA
            aqr/AQR_API_2.6.1/include/registerMap/EUR
            aqr/AQR_API_2.6.1/include/registerMap/HHD
            aqr/aqr_phy_fw
            ../mesa/include
            ../meba/include)
add_library(mepa_aqr        SHARED ${src_aqr})
add_library(mepa_aqr_static STATIC ${src_aqr})
set_target_properties(mepa_aqr_static PROPERTIES OUTPUT_NAME mepa_aqr)
target_include_directories(mepa_aqr        PUBLIC ${inc_mepa} PRIVATE ${inc_aqr})
target_include_directories(mepa_aqr_static PUBLIC ${inc_mepa} PRIVATE ${inc_aqr})


set(CMAKE_C_FLAGS "-DP31G_B0=1 -DSAFE_C_LIB=0")
set(src_intel intel/phy_driver.c
              intel/GPY_API_v251/src/api/phy/gpy211_chip.c
              intel/GPY_API_v251/src/api/phy/gpy211_phy.c)
set(inc_intel intel/GPY_API_v251/src/os/linux
              intel/GPY_API_v251/src/inc)
add_library(mepa_intel SHARED ${src_intel})
add_library(mepa_intel_static STATIC ${src_intel})
set_target_properties(mepa_intel_static PROPERTIES OUTPUT_NAME mepa_intel)
target_include_directories(mepa_intel        PUBLIC ${inc_mepa} PRIVATE ${inc_intel})
target_include_directories(mepa_intel_static PUBLIC ${inc_mepa} PRIVATE ${inc_intel})

set(CMAKE_C_FLAGS "-DP31G_B0=1 -DSAFE_C_LIB=0")
set(src_ksz9031 ksz9031/phy_driver.c )
set(inc_ksz9031 ksz9031)
add_library(mepa_ksz9031 SHARED ${src_ksz9031})
add_library(mepa_ksz9031_static STATIC ${src_ksz9031})
set_target_properties(mepa_ksz9031_static PROPERTIES OUTPUT_NAME mepa_ksz9031)
target_include_directories(mepa_ksz9031        PUBLIC ${inc_mepa} PRIVATE ${inc_ksz9031})
target_include_directories(mepa_ksz9031_static PUBLIC ${inc_mepa} PRIVATE ${inc_ksz9031})
