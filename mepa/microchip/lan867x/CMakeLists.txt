# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

set(MEPA_LAN867X_ADD_DEFS)

option(MEPA_LAN867X_STATIC_MEM "LAN867X static memory" OFF)
set(MEPA_LAN867X_PHY_MAX 4 CACHE STRING "Max LAN867X phys")
set(MEPA_LAN867X_ADD_DEFS ${MEPA_LAN867X_ADD_DEFS} -DMEPA_LAN867X_PHY_MAX=${MEPA_LAN867X_PHY_MAX})

if (${MEPA_LAN867X_STATIC_MEM})
	set(MEPA_LAN867X_ADD_DEFS ${MEPA_LAN867X_ADD_DEFS} -DMEPA_LAN867X_STATIC_MEM)
endif()

MEPA_DRV(LIB_NAME mepa_drv_lan867x
         SRCS     src/lan867x.c src/lan867x_private.c src/lan867x_t1s.c
		 DEFS	  ${MEPA_LAN867X_ADD_DEFS}
         INCL_PUB ../../../me/include ../../include
         INCL_PRI ./src)

option(MEPA_lan867x "Add LAN867X support in libmeba" OFF)
if (${MEPA_lan867x})
    set(mepa_drvs ${mepa_drvs} mepa_drv_lan867x CACHE INTERNAL "")
    set(mepa_defs ${mepa_defs} -DMEPA_HAS_LAN867X CACHE INTERNAL "")
endif()
