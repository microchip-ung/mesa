
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

#
gcc -g -o vtss_api_nano_vsc8502ev -I ../include -DVTSS_OPSYS_LINUX=1  -DVTSS_OPT_PORT_COUNT=2  -DVTSS_CHIP_CU_PHY -DNANO_EVAL_BOARD -DVTSS_FEATURE_EEE -DVTSS_SW_OPTION_EEE -D_INCLUDE_DEBUG_TERM_PRINT_ appl/vtss_appl_board_nano_eval.c appl/vtss_appl_cu_phy.c ../base/ail/vtss_api.c  ../base/ail/vtss_common.c  `find ../base/phy/phy_1g -name "*.c"`
## Available Defines:
##  -DVTSS_OPSYS_LINUX=1  
##  -DVTSS_OPT_PORT_COUNT=2  
##  -DVTSS_CHIP_CU_PHY 
##  -DNANO_EVAL_BOARD 
##  -DVTSS_FEATURE_EEE
##  -DVTSS_SW_OPTION_EEE
##  -DVTSS_SW_OPTION_DEBUG // Turns on Register Checking
##  -D_INCLUDE_DEBUG_FILE_PRINT_
##  -D_INCLUDE_DEBUG_TERM_PRINT_

