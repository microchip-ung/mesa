
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

#

#Compiles 1588-API, macsec API,10g,1G
gcc -Werror -Wall -Wextra -Wdeclaration-after-statement -Wunused-but-set-variable -I ../include -std=gnu89\
                                             appl/vtss_appl_board_viper_eval.c \
                                             appl/vtss_appl.c appl/vtss_appl_cli.c \
                                             ../base/ail/vtss_wis_api.c \
                                             ../base/ail/vtss_api.c \
                                             ../base/ail/vtss_port_api.c \
                                             ../base/ail/vtss_common.c  \
                                             ../base/phy/common/vtss_phy_common.c \
                                             appl/vtss_version.c \
                                             `find ../base/phy/phy_1g -name "*.c"` \
                                             `find ../base/phy/phy_10g -name "*.c"` \
                                             `find ../base/phy/ts -name "*.c"` \
                                             `find ../base/phy/macsec -name "*.c"` \
                                             -DVTSS_OPT_PORT_COUNT=4  \
                                             -DVTSS_OPSYS_LINUX=1\
                                             -DVTSS_CHIP_10G_PHY \
                                             -DVTSS_FEATURE_10G  \
                                             -DVTSS_FEATURE_10GBASE_KR \
                                             -DVTSS_OPT_PHY_TIMESTAMP \
                                             -DVTSS_USE_STDINT_H \
                                             -DVTSS_FEATURE_MACSEC \
                                             -DVIPER_EVAL_BOARD \
                                             -o vtss_api_10g
echo "############################################################################################################"
echo "Compiler version used"
gcc -v
echo "############################################################################################################"
