# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

set(MEPA_lan887x_custom_defs)

option(MEPA_lan887x_static_mem "LAN887X static memory" OFF)
set(MEPA_lan887x_phy_max 4 CACHE STRING "LAN887X static memory")
set(MEPA_lan887x_custom_defs ${MEPA_lan887x_custom_defs} -DMEPA_lan887x_phy_max=${MEPA_lan887x_phy_max})

if (${MEPA_lan887x_static_mem})
	set(MEPA_lan887x_custom_defs ${MEPA_lan887x_custom_defs} -DMEPA_lan887x_static_mem)
endif()

MEPA_DRV(LIB_NAME mepa_drv_lan887x
         SRCS     src/lan887x.c src/lan887x_private.c src/lan887x_tc10.c
		 DEFS	  ${MEPA_lan887x_custom_defs}
         INCL_PUB ../../../me/include ../../include
         INCL_PRI lan887x)

option(MEPA_lan887x "Add LAN887X support in libmeba" OFF)
if (${MEPA_lan887x})
    set(mepa_drvs ${mepa_drvs} mepa_drv_lan887x CACHE INTERNAL "")
    set(mepa_defs ${mepa_defs} -DMEPA_HAS_LAN887x CACHE INTERNAL "")
endif()
