
# Copyright (c) 2004-2018 Microsemi Corporation "Microsemi".
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

#
##
## TIMESTAMPING & MACSEC ENABLED ON EVAL BOARD - vtss_appl_cli DEMO code
gcc -g -o vtss_api_tesla_cli  -I ../include -I boards -DVTSS_OPSYS_LINUX=1  -DVTSS_OPT_PORT_COUNT=4  -DVTSS_CHIP_CU_PHY -DTESLA_EVAL_BOARD -DVTSS_FEATURE_EEE -DVTSS_SW_OPTION_EEE -DVTSS_FEATURE_PHY_TIMESTAMP appl/vtss_appl_board_tesla_eval.c appl/vtss_version.c appl/vtss_appl.c appl/vtss_appl_cli.c ../base/ail/vtss_api.c  ../base/ail/vtss_common.c  ../base/phy/common/vtss_phy_common.c ../base/phy/ts/vtss_phy_ts_api.c `find ../base/phy/phy_1g -name "*.c"`
##
## TIMESTAMPING & MACSEC ENABLED ON EVAL BOARD - vtss_appl_cu_phy DEMO code
## gcc -g -o vtss_api_viper.exe  -I ../include -I boards -DVTSS_OPSYS_LINUX=1  -DVTSS_OPT_PORT_COUNT=4  -DVTSS_CHIP_CU_PHY -DVIPER_EVAL_BOARD -DVTSS_FEATURE_EEE -DVTSS_SW_OPTION_EEE -DVTSS_FEATURE_PHY_TIMESTAMP -DVTSS_FEATURE_MACSEC appl/vtss_appl_board_viper_eval.c appl/vtss_appl_cu_phy.c ../base/ail/vtss_api.c  ../base/ail/vtss_common.c  ../base/phy/common/vtss_phy_common.c ../base/phy/ts/vtss_phy_ts_api.c ../base/phy/macsec/vtss_macsec_api.c `find ../base/phy/phy_1g -name "*.c"`
##
## TIMESTAMPING & MACSEC NOT ENABLED ON EVAL BOARD
##gcc -g -o vtss_api_viper.exe  -I ../include -I ../base/phy/common -DVTSS_OPSYS_LINUX=1  -DVTSS_OPT_PORT_COUNT=4  -DVTSS_CHIP_CU_PHY -DVIPER_EVAL_BOARD -DVTSS_FEATURE_MACSEC -DVTSS_FEATURE_EEE -DVTSS_SW_OPTION_EEE appl/vtss_appl_board_viper_eval.c appl/vtss_appl_cu_phy.c ../base/ail/vtss_api.c  ../base/ail/vtss_common.c  ../base/phy/common/vtss_phy_common.c ../base/phy/macsec/vtss_macsec_api.c `find ../base/phy/phy_1g -name "*.c"` 
## Available Defines:
##  -DVTSS_OPSYS_LINUX=1
##  -DVTSS_OPT_PORT_COUNT=4
##  -DVTSS_CHIP_CU_PHY
##  -DVIPER_EVAL_BOARD
##  -DVTSS_FEATURE_PHY_TIMESTAMP
##  -DVTSS_FEATURE_MACSEC
##  -DVTSS_FEATURE_EEE
##  -DVTSS_SW_OPTION_EEE
##  -D_INCLUDE_DEBUG_FILE_PRINT_
##  -D_INCLUDE_DEBUG_TERM_PRINT_
##  -DVTSS_SW_OPTION_DEBUG
##  -DVTSS_PHY_OPT_CAP_FE_ONLY
##  -DVTSS_PHY_OPT_CAP_GE_ONLY

