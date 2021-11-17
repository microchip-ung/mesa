MEPA_DRV(LIB_NAME mepa_drv_aqr
         SRCS     phy_driver.c
                  vtss_platform/AQ_PhyInterface.c
                  vtss_platform/AQ_PlatformRoutines.c
                  AQR_API_2.6.1/src/AQ_API.c
                  AQR_API_2.6.1/src/AQ_API_flash.c
         INCL_PUB ../../me/include ../include
         INCL_PRI AQR_API_2.6.1/include
                  AQR_API_2.6.1/include/registerMap
                  AQR_API_2.6.1/include/registerMap/APPIA
                  AQR_API_2.6.1/include/registerMap/EUR
                  AQR_API_2.6.1/include/registerMap/HHD
                  aqr_phy_fw)

option(MEPA_aqr "Add AQR family support in libmeba" OFF)
if (${MEPA_aqr})
    set(mepa_drvs ${mepa_drvs} mepa_drv_aqr CACHE INTERNAL "")
    set(mepa_defs ${mepa_defs} -DMEPA_HAS_AQR CACHE INTERNAL "")
endif()

