
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

#
##
## -D_INCLUDE_DEBUG_TERM_PRINT_
## TIMESTAMPING & MACSEC ENABLED ON EVAL BOARD - vtss_appl_cu_phy DEMO code
gcc -g -o vtss_api_viper_vsc8584ev -I ../include -I boards -DVTSS_OPSYS_LINUX=1  -DVTSS_OPT_PORT_COUNT=4 -DKAT_TEST_ENABLE_1G -DVTSS_CHIP_CU_PHY -DVIPER_EVAL_BOARD -D_INCLUDE_DEBUG_TERM_PRINT_ -DVTSS_FEATURE_EEE -DVTSS_SW_OPTION_EEE -DVTSS_FEATURE_SERDES_MACRO_SETTINGS -DVTSS_OPT_PHY_TIMESTAMP -DVTSS_FEATURE_MACSEC appl/vtss_appl_board_viper_eval.c appl/vtss_appl_cu_phy.c appl/vtss_appl_macsec_kat_test.c ../base/ail/vtss_api.c  ../base/ail/vtss_common.c  ../base/phy/common/vtss_phy_common.c ../base/phy/ts/vtss_phy_ts_api.c ../base/phy/ts/vtss_phy_ts_util.c ../base/phy/macsec/vtss_macsec_api.c `find ../base/phy/phy_1g -name "*.c"`
## NO -DVTSS_FEATURE_SERDES_MACRO_SETTINGS;  TIMESTAMPING & MACSEC ENABLED ON EVAL BOARD - vtss_appl_cu_phy DEMO code
##gcc -g -o vtss_api_viper_vsc8584ev -I ../include -I boards -DVTSS_OPSYS_LINUX=1  -DVTSS_OPT_PORT_COUNT=4  -DVTSS_CHIP_CU_PHY -DVIPER_EVAL_BOARD -D_INCLUDE_DEBUG_TERM_PRINT_ -DVTSS_FEATURE_EEE -DVTSS_SW_OPTION_EEE -DVTSS_OPT_PHY_TIMESTAMP -DVTSS_FEATURE_MACSEC appl/vtss_appl_board_viper_eval.c appl/vtss_appl_cu_phy.c ../base/ail/vtss_api.c  ../base/ail/vtss_common.c  ../base/phy/common/vtss_phy_common.c ../base/phy/ts/vtss_phy_ts_api.c ../base/phy/macsec/vtss_macsec_api.c `find ../base/phy/phy_1g -name "*.c"`
##
##
## TIMESTAMPING & MACSEC ENABLED ON EVAL BOARD - vtss_appl_cu_phy DEMO code
##gcc -g -o vtss_api_viper_vsc8584ev -I ../include -I boards -DVTSS_OPSYS_LINUX=1  -DVTSS_OPT_PORT_COUNT=4  -DVTSS_CHIP_CU_PHY -DVIPER_EVAL_BOARD -D_INCLUDE_DEBUG_TERM_PRINT_ -DVTSS_FEATURE_EEE -DVTSS_SW_OPTION_EEE -DVTSS_FEATURE_SERDES_MACRO_SETTINGS -DVTSS_OPT_PHY_TIMESTAMP -DVTSS_FEATURE_MACSEC appl/vtss_appl_board_viper_eval.c appl/vtss_appl_cu_phy.c ../base/ail/vtss_api.c  ../base/ail/vtss_common.c  ../base/phy/common/vtss_phy_common.c ../base/phy/ts/vtss_phy_ts_api.c ../base/phy/macsec/vtss_macsec_api.c `find ../base/phy/phy_1g -name "*.c"`
##
##
## TIMESTAMPING & MACSEC NOT ENABLED ON EVAL BOARD
##gcc -g -o vtss_api_viper.exe  -I ../include -I ../base/phy/common -DVTSS_OPSYS_LINUX=1  -DVTSS_OPT_PORT_COUNT=4  -DVTSS_CHIP_CU_PHY -DVIPER_EVAL_BOARD -DVTSS_FEATURE_MACSEC -DVTSS_FEATURE_EEE -DVTSS_SW_OPTION_EEE appl/vtss_appl_board_viper_eval.c appl/vtss_appl_cu_phy.c ../base/ail/vtss_api.c  ../base/ail/vtss_common.c  ../base/phy/common/vtss_phy_common.c ../base/phy/macsec/vtss_macsec_api.c `find ../base/phy/phy_1g -name "*.c"` 
##
## Available Defines:
##  -DVTSS_OPSYS_LINUX=1
##  -DVTSS_OPT_PORT_COUNT=4
##  -DVTSS_CHIP_CU_PHY
##  -DVIPER_EVAL_BOARD
##  -DVTSS_OPT_PHY_TIMESTAMP
##  -DVTSS_FEATURE_MACSEC
##  -DVTSS_FEATURE_EEE
##  -DVTSS_SW_OPTION_EEE
##  -D_INCLUDE_DEBUG_FILE_PRINT_
##  -D_INCLUDE_DEBUG_TERM_PRINT_
##  -DVTSS_SW_OPTION_DEBUG
##  -DVTSS_PHY_OPT_CAP_FE_ONLY
##  -DVTSS_PHY_OPT_CAP_GE_ONLY
##  -DVTSS_FEATURE_SERDES_MACRO_SETTINGS
