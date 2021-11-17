
MEPA_DRV(LIB_NAME mepa_drv_lan8814
         SRCS     src/lan8814.c
                  src/lan8814_ts.c
         INCL_PUB ../../../me/include ../../include
         INCL_PRI lan8814)

option(MEPA_lan8814 "Add LAN8814 support in libmeba" OFF)
if (${MEPA_lan8814})
    set(mepa_drvs ${mepa_drvs} mepa_drv_lan8814 CACHE INTERNAL "")
    set(mepa_defs ${mepa_defs} -DMEPA_HAS_LAN8814 CACHE INTERNAL "")
endif()
