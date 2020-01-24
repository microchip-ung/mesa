# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

include_directories("AQR_API_2.6.1/include")
include_directories("AQR_API_2.6.1/include/registerMap")
include_directories("AQR_API_2.6.1/include/registerMap/APPIA")
include_directories("AQR_API_2.6.1/include/registerMap/EUR")
include_directories("AQR_API_2.6.1/include/registerMap/HHD")
include_directories("aqr_phy_fw")

set(src_aqr phy_driver.c
	    vtss_platform/AQ_PhyInterface.c
	    vtss_platform/AQ_PlatformRoutines.c
	    AQR_API_2.6.1/src/AQ_API.c
	    AQR_API_2.6.1/src/AQ_API_flash.c)

add_library(phy_aqr SHARED ${src_aqr})
