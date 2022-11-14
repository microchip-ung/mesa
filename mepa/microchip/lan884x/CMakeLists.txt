
MEPA_DRV(LIB_NAME mepa_drv_lan884x
         SRCS     src/lan884x.c
         INCL_PUB ../../../me/include ../../include
         INCL_PRI lan884x)

option(MEPA_lan884x "Add LAN884x support in libmeba" OFF)
if (${MEPA_lan884x})
    set(mepa_drvs ${mepa_drvs} mepa_drv_lan884x CACHE INTERNAL "")
    set(mepa_defs ${mepa_defs} -DMEPA_HAS_LAN884x CACHE INTERNAL "")
endif()
