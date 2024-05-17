
MEPA_DRV(LIB_NAME mepa_drv_dummy_phy
         SRCS     src/dummy_phy.c
         INCL_PUB ../../me/include ../include)

option(MEPA_dummy_phy "Add dummy sw phy in libmeba" OFF)
if (${MEPA_dummy_phy})
    set(mepa_drvs ${mepa_drvs} mepa_dummy_phy CACHE INTERNAL "")
    set(mepa_defs ${mepa_defs} -DMEPA_HAS_DUMMY_PHY CACHE INTERNAL "")
endif()
