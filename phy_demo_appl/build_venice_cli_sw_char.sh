#
#
# Copyright (c) 2002-2017 Microsemi Corporation "Microsemi". All Rights Reserved.
#
# Unpublished rights reserved under the copyright laws of the United States of
# America, other countries and international treaties. Permission to use, copy,
# store and modify, the software and its source code is granted but only in
# connection with products utilizing the Microsemi switch and PHY products.
# Permission is also granted for you to integrate into other products, disclose,
# transmit and distribute the software only in an absolute machine readable format
# (e.g. HEX file) and only in or with products utilizing the Microsemi switch and
# PHY products.  The source code of the software may not be disclosed, transmitted
# or distributed without the prior written permission of Microsemi.
#
# This copyright notice must appear in any copy, modification, disclosure,
# transmission or distribution of the software.  Microsemi retains all ownership,
# copyright, trade secret and proprietary rights in the software and its source code,
# including all modifications thereto.
#
# THIS SOFTWARE HAS BEEN PROVIDED "AS IS". MICROSEMI HEREBY DISCLAIMS ALL WARRANTIES
# OF ANY KIND WITH RESPECT TO THE SOFTWARE, WHETHER SUCH WARRANTIES ARE EXPRESS,
# IMPLIED, STATUTORY OR OTHERWISE INCLUDING, WITHOUT LIMITATION, WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR USE OR PURPOSE AND NON-INFRINGEMENT.
#
##    -DRPI_MIIM \
##    -DVTSS_FEATURE_PHY_TIMESTAMP \
##    -DVTSS_ARCH_VENICE_C=TRUE \
##    -DVTSS_CHIP_CU_PHY \
#3    -DVTSS_CHIP_10G_PHY \
##    `find base/phy/phy_1g -name "*.c"` \
##
## TIMESTAMPING & MACSEC ENABLED ON EVAL BOARD - vtss_appl_cli DEMO code
gcc -I ../include -std=gnu89 \
    appl/vtss_appl_board_venice.c \
    appl/vtss_appl_10g_phy_venice.c \
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
    -DVTSS_OPT_PORT_COUNT=2  \
    -DVTSS_OPSYS_LINUX=1 \
    -DVTSS_FEATURE_10G  \
    -DVTSS_FEATURE_10GBASE_KR \
    -DVTSS_USE_STDINT_H \
    -D_INCLUDE_DEBUG_TERM_PRINT_ \
    -DVENICE_CHAR_BOARD \
    -DVTSS_FEATURE_MACSEC \
    -DVTSS_OPT_PHY_TIMESTAMP \
    -o venice_char

