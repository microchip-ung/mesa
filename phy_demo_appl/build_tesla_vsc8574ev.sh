
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

#
# Note: When compiling for an EVAL BOARD with a PHY ADDR that is NOT 0,
#       The PHY has 4 physical ports
#       The VTSS_OPT_PORT_COUNT has to be compensated/offset for the difference.
##
## TIMESTAMPING ENABLED ON EVAL BOARD, Board Addr = 0
gcc -g -o vtss_api_tesla_vsc8574ev -I ../include -DVTSS_OPSYS_LINUX=1  -DVTSS_OPT_PORT_COUNT=4  -DVTSS_CHIP_CU_PHY -DTESLA_EVAL_BOARD  -D_INCLUDE_DEBUG_TERM_PRINT_  -DVTSS_FEATURE_EEE -DVTSS_SW_OPTION_EEE -DVTSS_FEATURE_SERDES_MACRO_SETTINGS -DVTSS_OPT_PHY_TIMESTAMP appl/vtss_appl_board_tesla_eval.c appl/vtss_appl_cu_phy.c ../base/ail/vtss_api.c  ../base/ail/vtss_common.c  ../base/phy/common/vtss_phy_common.c ../base/phy/ts/vtss_phy_ts_util.c ../base/phy/ts/vtss_phy_ts_api.c  `find ../base/phy/phy_1g -name "*.c"`
## TIMESTAMPING ENABLED ON EVAL BOARD, Board Addr = 4
##gcc -g -o vtss_api_tesla_vsc8574ev -I ../include -DVTSS_OPSYS_LINUX=1  -DVTSS_OPT_PORT_COUNT=8  -DVTSS_CHIP_CU_PHY -DTESLA_EVAL_BOARD -D_INCLUDE_DEBUG_TERM_PRINT_ -DVTSS_FEATURE_EEE -DVTSS_SW_OPTION_EEE -DVTSS_FEATURE_SERDES_MACRO_SETTINGS -DVTSS_OPT_PHY_TIMESTAMP appl/vtss_appl_board_tesla_eval.c appl/vtss_appl_cu_phy.c ../base/ail/vtss_api.c  ../base/ail/vtss_common.c  ../base/phy/common/vtss_phy_common.c ../base/phy/ts/vtss_phy_ts_api.c  `find ../base/phy/phy_1g -name "*.c"`
##
## NO TIMESTAMPING ENABLED ON EVAL BOARD
##gcc  -g -o vtss_api_tesla.exe  -I ../include -DVTSS_OPSYS_LINUX=1  -DVTSS_OPT_PORT_COUNT=4  -DVTSS_CHIP_CU_PHY -DTESLA_EVAL_BOARD -DVTSS_FEATURE_EEE -DVTSS_SW_OPTION_EEE -D_INCLUDE_DEBUG_TERM_PRINT_ appl/vtss_appl_board_tesla_eval.c appl/vtss_appl_cu_phy.c ../base/ail/vtss_api.c  ../base/ail/vtss_common.c  `find ../base/phy/phy_1g -name "*.c"` 
##
## Available Defines:
##  -DVTSS_API_INIT_SEQ_NORMAL /* Customer environment based PHY Init Seq */
##  -DVTSS_API_INIT_SEQ_WARM   /* Customer environment based Warmstart */
##  -DVTSS_OPSYS_LINUX=1
##  -DVTSS_OPT_PORT_COUNT=4
##  -DVTSS_CHIP_CU_PHY
##  -DTESLA_EVAL_BOARD
##  -DVTSS_FEATURE_EEE
##  -DVTSS_SW_OPTION_EEE
##  -D_INCLUDE_DEBUG_FILE_PRINT_
##  -D_INCLUDE_DEBUG_TERM_PRINT_
##  -DVTSS_PHY_OPT_CAP_FE_ONLY
##  -DVTSS_PHY_OPT_CAP_GE_ONLY
##  -DVTSS_FEATURE_SERDES_MACRO_SETTINGS
