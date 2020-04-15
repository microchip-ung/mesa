
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
                                             -DVTSS_FEATURE_PHY_TIMESTAMP \
                                             -DVTSS_USE_STDINT_H \
                                             -DVTSS_FEATURE_MACSEC \
                                             -DVIPER_EVAL_BOARD \
                                             -o vtss_api_10g
echo "############################################################################################################"
echo "Compiler version used"
gcc -v
echo "############################################################################################################"
