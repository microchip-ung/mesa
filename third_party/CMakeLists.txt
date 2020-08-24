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

include_directories("phy/intl/GPY_API_v251/src/os/linux")
include_directories("phy/intl/GPY_API_v251/src/inc")

set(src_intl phy/intl/phy_driver.c
            phy/intl/GPY_API_v251/src/api/phy/gpy211_chip.c
            phy/intl/GPY_API_v251/src/api/phy/gpy211_phy.c)

set(CMAKE_C_FLAGS "-DP31G_B0=1 -DSAFE_C_LIB=0")
add_library(phy_intl SHARED ${src_intl})
