cmake_minimum_required(VERSION 2.8)

include_directories(".")
include_directories("phy/aqr/AQR_API_2.6.1/include")
include_directories("phy/aqr/AQR_API_2.6.1/include/registerMap")
include_directories("phy/aqr/AQR_API_2.6.1/include/registerMap/APPIA")
include_directories("phy/aqr/AQR_API_2.6.1/include/registerMap/EUR")
include_directories("phy/aqr/AQR_API_2.6.1/include/registerMap/HHD")
include_directories("phy/aqr/aqr_phy_fw")

set(src_aqr phy/aqr/phy_driver.c
	    phy/aqr/vtss_platform/AQ_PhyInterface.c
	    phy/aqr/vtss_platform/AQ_PlatformRoutines.c
	    phy/aqr/AQR_API_2.6.1/src/AQ_API.c
	    phy/aqr/AQR_API_2.6.1/src/AQ_API_flash.c)


add_library(phy_aqr SHARED ${src_aqr})
