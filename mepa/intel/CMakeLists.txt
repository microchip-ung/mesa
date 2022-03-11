
MEPA_DRV(LIB_NAME mepa_drv_intel
         SRCS     phy_driver.c
                  GPY_API_v2.7.1.1/src/api/phy/gpy211_chip.c
                  GPY_API_v2.7.1.1/src/api/phy/gpy211_phy.c
         DEFS     -DP31G_B0=1 -DSAFE_C_LIB=0
         INCL_PUB ../../me/include ../include
         INCL_PRI GPY_API_v2.7.1.1/src/os/linux
                  GPY_API_v2.7.1.1/src/inc)

option(MEPA_gpy211 "Add GPY211 phy support in libmeba" OFF)
if (${MEPA_gpy211})
    set(mepa_drvs ${mepa_drvs} mepa_drv_intel CACHE INTERNAL "")
    set(mepa_defs ${mepa_defs} -DMEPA_HAS_GPY2211 CACHE INTERNAL "")
endif()

