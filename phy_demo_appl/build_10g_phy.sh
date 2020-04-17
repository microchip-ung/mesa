#!/usr/bin/env bash

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

gcc -g -o vtss_api_10g  -I ../include appl/vtss_appl_board_atom12_eval.c appl/vtss_appl_cu_phy.c ../base/ail/vtss_api.c  ../base/ail/vtss_common.c  `find ../base/phy/phy_1g -name "*.c"` `find ../base/phy/phy_10g -name "*.c"` ../base/phy/ts/vtss_phy_ewis.c -DVTSS_OPSYS_LINUX=1  -DVTSS_OPT_PORT_COUNT=4  -DVTSS_CHIP_CU_PHY -DVTSS_CHIP_10G_PHY -DATOM12_EVAL_BOARD
