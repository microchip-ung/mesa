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

add_library(mepa_vtss SHARED src/vtss.c)
add_library(mepa_vtss_static STATIC src/vtss.c)
set_target_properties(mepa_vtss_static PROPERTIES OUTPUT_NAME mepa_vtss)

add_library(mepa_lan8814 SHARED src/microchip/lan8814.c)
add_library(mepa_lan8814_static STATIC src/microchip/lan8814.c)
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
