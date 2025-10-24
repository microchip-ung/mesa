# Copyright (c) 2024 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

##
## setup sources
##
set(src_lan8x8x         ../common/src/phy_lib.c
                        src/lan8x8x.c)
set(inc_mepa            ../../../me/include
                        ../../include
                        ../common/include)
set(inc_lan8x8x         lan8x8x)

##
## setup feature flags
##
set(MEPA_lan8x8x_defs)
list(APPEND MEPA_lan8x8x_defs -DMEPA_HAS_LAN8X8X)

set(MEPA_lan8x8x_custom_defs)
list(APPEND MEPA_lan8x8x_custom_defs ${MEPA_lan8x8x_defs})

set(MEPA_lan8x8x_phy_max 4 CACHE STRING "LAN8X8X static memory")
list(APPEND MEPA_lan8x8x_custom_defs -DMEPA_lan8x8x_phy_max=${MEPA_lan8x8x_phy_max})

option(MEPA_lan8x8x_static_mem "LAN8X8X static memory" OFF)
if (${MEPA_lan8x8x_static_mem})
    list(APPEND MEPA_lan8x8x_custom_defs -DMEPA_lan8x8x_static_mem)
endif()

##
## Driver combinations
##
MEPA_DRV(LIB_NAME mepa_drv_lan8x8x
         DEFS	  ${MEPA_lan8x8x_custom_defs}
         SRCS     ${src_lan8x8x}
         INCL_PUB ${inc_mepa}
         INCL_PRI ${inc_lan8x8x})

##
## driver modules are mutually exclusive
##
option(MEPA_lan8x8x "Add LAN8X8X support in libmeba" OFF)
if (${MEPA_lan8x8x})
    set(mepa_drvs ${mepa_drvs} mepa_drv_lan8x8x CACHE INTERNAL "")
    set(mepa_defs ${mepa_defs} ${MEPA_lan8x8x_defs} CACHE INTERNAL "")
endif()
