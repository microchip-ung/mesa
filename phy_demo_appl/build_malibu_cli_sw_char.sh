
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

##    -DRPI_MIIM \
##    -DVTSS_ARCH_VENICE_C=TRUE \     // Compile in support for Venice C and later
##    -DVTSS_CHIP_CU_PHY \            // Compile in support for 1G PHY Families in API
##    -DVTSS_CHIP_10G_PHY \           // Compile in support for 10G PHY Families in API
##    -DVTSS_OPT_PORT_COUNT=2  \      // Compile for MAX Number of Ports in this PHY_INST
##    -DVTSS_OPSYS_LINUX=1 \          // Compile in Linux OS Support <Default OS>
##    -DVTSS_FEATURE_10G  \           // Include 10G Capability, used in MESA builds
##    -DVTSS_FEATURE_10GBASE_KR \     // Compile in Support for 10G Base-KR
##    -DVTSS_USE_STDINT_H \           // Compile to Use Linux Std INT types as defined in stdint.h
##    -D_INCLUDE_DEBUG_TERM_PRINT_ \  // Include Debug Output to Console (EVB/Char Board Setup, in Sample Application Code)
##    -DVENICE_CHAR_BOARD \           // Compile in support for EVB/CHAR BOARD setup
##    -DVTSS_FEATURE_MACSEC \         // Compile in support for MACSEC Block
##    -DVTSS_OPT_PHY_TIMESTAMP \      // Compile in support for IEEE-1588 Timestamp Block
##    `find base/phy/phy_1g -name "*.c"` \    // Compile all files in the phy_1g Directory for 1G PHY Support
##
## TIMESTAMPING & MACSEC ENABLED ON EVAL BOARD - vtss_appl_cli DEMO code
gcc -I ../include -I ../base/phy/phy_10g -std=gnu89 \
    appl/vtss_appl_board_malibu.c \
    appl/vtss_appl_10g_phy_malibu.c \
    appl/vtss_appl_macsec_demo.c \
    appl/vtss_appl_ts_demo.c \
    ../base/ail/vtss_wis_api.c \
    ../base/ail/vtss_api.c \
    ../base/ail/vtss_port_api.c \
    ../base/ail/vtss_common.c  \
    ../base/ail/vtss_sd10g65_procs.c  \
    ../base/ail/vtss_sd10g65_apc_procs.c  \
    ../base/ail/vtss_pll5g_procs.c  \
    ../base/phy/common/vtss_phy_common.c \
    appl/vtss_version.c \
    `find ../base/phy/phy_10g -name "*.c"` \
    `find ../base/phy/ts -name "*.c"` \
    `find ../base/phy/macsec -name "*.c"` \
    -DVTSS_OPT_PORT_COUNT=4  \
    -DVTSS_OPSYS_LINUX=1 \
    -DVTSS_FEATURE_10G  \
    -DVTSS_FEATURE_10GBASE_KR \
    -DVTSS_FEATURE_SERDES_MACRO_SETTINGS \
    -DVTSS_USE_STDINT_H \
    -D_INCLUDE_DEBUG_TERM_PRINT_ \
    -DMALIBU_CHAR_BOARD \
    -DVTSS_FEATURE_MACSEC \
    -DVTSS_OPT_PHY_TIMESTAMP \
    -o malibu_char

