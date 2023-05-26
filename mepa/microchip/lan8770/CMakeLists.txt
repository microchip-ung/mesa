# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

MEPA_DRV(LIB_NAME mepa_drv_lan8770
         SRCS     src/lan8770.c
         INCL_PUB ../../../me/include ../../include
         INCL_PRI lan8770)

option(MEPA_lan8770 "Add LAN8770 support in libmeba" OFF)
if (${MEPA_lan8770})
    set(mepa_drvs ${mepa_drvs} mepa_drv_lan8770 CACHE INTERNAL "")
    set(mepa_defs ${mepa_defs} -DMEPA_HAS_LAN8770 CACHE INTERNAL "")
endif()
