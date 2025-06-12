// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "vtss_api.h"
#ifdef VTSS_ARCH_MALIBU25G
#ifdef VTSS_OPT_SYMREG
static const vtss_symreg_reg_t regs_within_HOST_PMA_SD_RESET[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_SER_RST", 0x00000000, 0x00000001, 0x00000001},
    {"SD_DES_RST", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PMA_SD_LANE_CFG_STAT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_LANE_CFG_0", 0x00000000, 0x00000001, 0x00000001},
    {"SD_LANE_CFG_1", 0x00000001, 0x00000001, 0x00000001},
    {"SD_LANE_CFG_2", 0x00000002, 0x00000001, 0x00000001},
    {"SD_LANE_CFG_3", 0x00000003, 0x00000001, 0x00000001},
    {"SD_LANE_STAT_0", 0x00000004, 0x00000001, 0x00000001},
    {"SD_LANE_STAT_1", 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PMA_SD_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_CFG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PMA_SD_CLK_GATE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_CLK_GATE", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PMA_SD_PWR_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"NORMAL_MODE_0", 0x00000000, 0x00000001, 0x00000001},
    {"NORMAL_MODE_1", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PMA_SD_ANEG_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_KR_ANEG_MODE", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PMA_SD_EXTCFG_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_EXTCFG_CFG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PMA_SD_FIFO_DELAY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_DELAY_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"SD_RX_DELAY_VAR", 0x00000001, 0x00000001, 0x00000001},
    {"SD_TX_DELAY_VAR", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PMA_HW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"KR_DATA_CFG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PMA_PMA_INT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PMA_IRQ_VEC", 0x00000000, 0x00000001, 0x00000001},
    {"PMA_IRQ_MASK", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PMA_HOST_PMA_DEBUG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"HOST_PMA_DEBUG_REG_7", 0x00000000, 0x00000001, 0x00000001},
    {"HOST_PMA_DEBUG_REG_6", 0x00000001, 0x00000001, 0x00000001},
    {"HOST_PMA_DEBUG_REG_5", 0x00000002, 0x00000001, 0x00000001},
    {"HOST_PMA_DEBUG_REG_4", 0x00000003, 0x00000001, 0x00000001},
    {"HOST_PMA_DEBUG_REG_3", 0x00000004, 0x00000001, 0x00000001},
    {"HOST_PMA_DEBUG_REG_2", 0x00000005, 0x00000001, 0x00000001},
    {"HOST_PMA_DEBUG_REG_1", 0x00000006, 0x00000001, 0x00000001},
    {"HOST_PMA_DEBUG_REG_0", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_HOST_PMA[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"SD_RESET", 0x00008000, 0x00000001, 0x00000002, regs_within_HOST_PMA_SD_RESET},
    {"SD_LANE_CFG_STAT", 0x00008002, 0x00000001, 0x00000006, regs_within_HOST_PMA_SD_LANE_CFG_STAT},
    {"SD_CFG", 0x00008008, 0x00000001, 0x00000001, regs_within_HOST_PMA_SD_CFG},
    {"SD_CLK_GATE", 0x00008009, 0x00000001, 0x00000001, regs_within_HOST_PMA_SD_CLK_GATE},
    {"SD_PWR_CFG", 0x0000800a, 0x00000001, 0x00000002, regs_within_HOST_PMA_SD_PWR_CFG},
#ifndef VTSS_RELEASE
    {"SD_ANEG_CFG", 0x00008010, 0x00000001, 0x00000001, regs_within_HOST_PMA_SD_ANEG_CFG},
#endif
    {"SD_EXTCFG_CFG", 0x00008011, 0x00000001, 0x00000001, regs_within_HOST_PMA_SD_EXTCFG_CFG},
    {"SD_FIFO_DELAY", 0x00008012, 0x00000001, 0x00000003, regs_within_HOST_PMA_SD_FIFO_DELAY},
#ifndef VTSS_RELEASE
    {"HW_CFG", 0x00008016, 0x00000001, 0x00000001, regs_within_HOST_PMA_HW_CFG},
#endif
#ifndef VTSS_RELEASE
    {"PMA_INT", 0x00008018, 0x00000001, 0x00000002, regs_within_HOST_PMA_PMA_INT},
#endif
#ifndef VTSS_RELEASE
    {"HOST_PMA_DEBUG", 0x000080f8, 0x00000001, 0x00000008, regs_within_HOST_PMA_HOST_PMA_DEBUG},
#endif
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_PMA_PMD_CONTROL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PMA_PMD_CONTROL_1", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_PMA_PMD_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PMA_PMD_STATUS_1", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_PMA_PMD_DEVICE_ID[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PMA_PMD_DEVICE_ID_1", 0x00000000, 0x00000001, 0x00000001},
    {"PMA_PMD_DEVICE_ID_2", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_PMA_PMD_SPEED_ABILITY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PMA_PMD_SPEED_ABILITY", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_PMA_PMD_DEV_IN_PACKAGE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PMA_PMD_DEV_IN_PACKAGE_1", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_PMA_PMD_CONTROL_2[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PMA_PMD_CONTROL_2", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_PMA_PMD_STATUS_2[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PMA_PMD_STATUS_2", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_PMA_PMD_PACKAGE_ID[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PMA_PMD_PACKAGE_ID_1", 0x00000000, 0x00000001, 0x00000001},
    {"PMA_PMD_PACKAGE_ID_2", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_SD_RESET[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_SER_RST", 0x00000000, 0x00000001, 0x00000001},
    {"SD_DES_RST", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_SD_LANE_CFG_STAT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_LANE_CFG_0", 0x00000000, 0x00000001, 0x00000001},
    {"SD_LANE_CFG_1", 0x00000001, 0x00000001, 0x00000001},
    {"SD_LANE_CFG_2", 0x00000002, 0x00000001, 0x00000001},
    {"SD_LANE_CFG_3", 0x00000003, 0x00000001, 0x00000001},
    {"SD_LANE_STAT_0", 0x00000004, 0x00000001, 0x00000001},
    {"SD_LANE_STAT_1", 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_SD_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_CFG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_SD_CLK_GATE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_CLK_GATE", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_SD_PWR_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"NORMAL_MODE_0", 0x00000000, 0x00000001, 0x00000001},
    {"NORMAL_MODE_1", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_SD_ANEG_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_KR_ANEG_MODE", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_SD_EXTCFG_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_EXTCFG_CFG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_SD_FIFO_DELAY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_DELAY_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"SD_RX_DELAY_VAR", 0x00000001, 0x00000001, 0x00000001},
    {"SD_TX_DELAY_VAR", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_HW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"KR_DATA_CFG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_PMA_INT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PMA_IRQ_VEC", 0x00000000, 0x00000001, 0x00000001},
    {"PMA_IRQ_MASK", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_LINE_PMA_DEBUG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LINE_PMA_DEBUG_REG_7", 0x00000000, 0x00000001, 0x00000001},
    {"LINE_PMA_DEBUG_REG_6", 0x00000001, 0x00000001, 0x00000001},
    {"LINE_PMA_DEBUG_REG_5", 0x00000002, 0x00000001, 0x00000001},
    {"LINE_PMA_DEBUG_REG_4", 0x00000003, 0x00000001, 0x00000001},
    {"LINE_PMA_DEBUG_REG_3", 0x00000004, 0x00000001, 0x00000001},
    {"LINE_PMA_DEBUG_REG_2", 0x00000005, 0x00000001, 0x00000001},
    {"LINE_PMA_DEBUG_REG_1", 0x00000006, 0x00000001, 0x00000001},
    {"LINE_PMA_DEBUG_REG_0", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_LINE_PMA[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"PMA_PMD_CONTROL", 0x00000000, 0x00000001, 0x00000001, regs_within_LINE_PMA_PMA_PMD_CONTROL},
    {"PMA_PMD_STATUS", 0x00000001, 0x00000001, 0x00000001, regs_within_LINE_PMA_PMA_PMD_STATUS},
    {"PMA_PMD_DEVICE_ID", 0x00000002, 0x00000001, 0x00000002, regs_within_LINE_PMA_PMA_PMD_DEVICE_ID},
    {"PMA_PMD_SPEED_ABILITY", 0x00000004, 0x00000001, 0x00000001, regs_within_LINE_PMA_PMA_PMD_SPEED_ABILITY},
    {"PMA_PMD_DEV_IN_PACKAGE", 0x00000005, 0x00000001, 0x00000001, regs_within_LINE_PMA_PMA_PMD_DEV_IN_PACKAGE},
    {"PMA_PMD_CONTROL_2", 0x00000007, 0x00000001, 0x00000001, regs_within_LINE_PMA_PMA_PMD_CONTROL_2},
    {"PMA_PMD_STATUS_2", 0x00000008, 0x00000001, 0x00000001, regs_within_LINE_PMA_PMA_PMD_STATUS_2},
    {"PMA_PMD_PACKAGE_ID", 0x0000000e, 0x00000001, 0x00000002, regs_within_LINE_PMA_PMA_PMD_PACKAGE_ID},
    {"SD_RESET", 0x00008000, 0x00000001, 0x00000002, regs_within_LINE_PMA_SD_RESET},
    {"SD_LANE_CFG_STAT", 0x00008002, 0x00000001, 0x00000006, regs_within_LINE_PMA_SD_LANE_CFG_STAT},
    {"SD_CFG", 0x00008008, 0x00000001, 0x00000001, regs_within_LINE_PMA_SD_CFG},
    {"SD_CLK_GATE", 0x00008009, 0x00000001, 0x00000001, regs_within_LINE_PMA_SD_CLK_GATE},
    {"SD_PWR_CFG", 0x0000800a, 0x00000001, 0x00000002, regs_within_LINE_PMA_SD_PWR_CFG},
#ifndef VTSS_RELEASE
    {"SD_ANEG_CFG", 0x00008010, 0x00000001, 0x00000001, regs_within_LINE_PMA_SD_ANEG_CFG},
#endif
    {"SD_EXTCFG_CFG", 0x00008011, 0x00000001, 0x00000001, regs_within_LINE_PMA_SD_EXTCFG_CFG},
    {"SD_FIFO_DELAY", 0x00008012, 0x00000001, 0x00000003, regs_within_LINE_PMA_SD_FIFO_DELAY},
#ifndef VTSS_RELEASE
    {"HW_CFG", 0x00008016, 0x00000001, 0x00000001, regs_within_LINE_PMA_HW_CFG},
#endif
#ifndef VTSS_RELEASE
    {"PMA_INT", 0x00008018, 0x00000001, 0x00000002, regs_within_LINE_PMA_PMA_INT},
#endif
#ifndef VTSS_RELEASE
    {"LINE_PMA_DEBUG", 0x000080f8, 0x00000001, 0x00000008, regs_within_LINE_PMA_LINE_PMA_DEBUG},
#endif
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_HOST_PMA_8BIT_CMU_GRP_0[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CMU_00", 0x00000000, 0x00000001, 0x00000001},
    {"CMU_01", 0x00000001, 0x00000001, 0x00000001},
    {"CMU_02", 0x00000002, 0x00000001, 0x00000001},
    {"CMU_03", 0x00000003, 0x00000001, 0x00000001},
    {"CMU_04", 0x00000004, 0x00000001, 0x00000001},
    {"CMU_05", 0x00000005, 0x00000001, 0x00000001},
    {"CMU_06", 0x00000006, 0x00000001, 0x00000001},
    {"CMU_07", 0x00000007, 0x00000001, 0x00000001},
    {"CMU_08", 0x00000008, 0x00000001, 0x00000001},
    {"CMU_09", 0x00000009, 0x00000001, 0x00000001},
    {"CMU_0A", 0x0000000a, 0x00000001, 0x00000001},
    {"CMU_0B", 0x0000000b, 0x00000001, 0x00000001},
    {"CMU_0C", 0x0000000c, 0x00000001, 0x00000001},
    {"CMU_0D", 0x0000000d, 0x00000001, 0x00000001},
    {"CMU_0E", 0x0000000e, 0x00000001, 0x00000001},
    {"CMU_0F", 0x0000000f, 0x00000001, 0x00000001},
    {"CMU_10", 0x00000010, 0x00000001, 0x00000001},
    {"CMU_11", 0x00000011, 0x00000001, 0x00000001},
    {"CMU_12", 0x00000012, 0x00000001, 0x00000001},
    {"CMU_13", 0x00000013, 0x00000001, 0x00000001},
    {"CMU_14", 0x00000014, 0x00000001, 0x00000001},
    {"CMU_15", 0x00000015, 0x00000001, 0x00000001},
    {"CMU_16", 0x00000016, 0x00000001, 0x00000001},
    {"CMU_17", 0x00000017, 0x00000001, 0x00000001},
    {"CMU_18", 0x00000018, 0x00000001, 0x00000001},
    {"CMU_19", 0x00000019, 0x00000001, 0x00000001},
    {"CMU_1A", 0x0000001a, 0x00000001, 0x00000001},
    {"CMU_1B", 0x0000001b, 0x00000001, 0x00000001},
    {"CMU_1C", 0x0000001c, 0x00000001, 0x00000001},
    {"CMU_1D", 0x0000001d, 0x00000001, 0x00000001},
    {"CMU_1E", 0x0000001e, 0x00000001, 0x00000001},
    {"CMU_1F", 0x0000001f, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PMA_8BIT_CMU_GRP_1[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CMU_21", 0x00000000, 0x00000001, 0x00000001},
    {"CMU_22", 0x00000001, 0x00000001, 0x00000001},
    {"CMU_23", 0x00000002, 0x00000001, 0x00000001},
    {"CMU_24", 0x00000003, 0x00000001, 0x00000001},
    {"CMU_25", 0x00000004, 0x00000001, 0x00000001},
    {"CMU_26", 0x00000005, 0x00000001, 0x00000001},
    {"CMU_27", 0x00000006, 0x00000001, 0x00000001},
    {"CMU_28", 0x00000007, 0x00000001, 0x00000001},
    {"CMU_29", 0x00000008, 0x00000001, 0x00000001},
    {"CMU_2A", 0x00000009, 0x00000001, 0x00000001},
    {"CMU_2B", 0x0000000a, 0x00000001, 0x00000001},
    {"CMU_2C", 0x0000000b, 0x00000001, 0x00000001},
    {"CMU_2D", 0x0000000c, 0x00000001, 0x00000001},
    {"CMU_2E", 0x0000000d, 0x00000001, 0x00000001},
    {"CMU_2F", 0x0000000e, 0x00000001, 0x00000001},
    {"CMU_30", 0x0000000f, 0x00000001, 0x00000001},
    {"CMU_31", 0x00000010, 0x00000001, 0x00000001},
    {"CMU_32", 0x00000011, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PMA_8BIT_CMU_GRP_2[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CMU_40", 0x00000000, 0x00000001, 0x00000001},
    {"CMU_41", 0x00000001, 0x00000001, 0x00000001},
    {"CMU_42", 0x00000002, 0x00000001, 0x00000001},
    {"CMU_43", 0x00000003, 0x00000001, 0x00000001},
    {"CMU_44", 0x00000004, 0x00000001, 0x00000001},
    {"CMU_45", 0x00000005, 0x00000001, 0x00000001},
    {"CMU_46", 0x00000006, 0x00000001, 0x00000001},
    {"CMU_47", 0x00000007, 0x00000001, 0x00000001},
    {"CMU_48", 0x00000008, 0x00000001, 0x00000001},
    {"CMU_49", 0x00000009, 0x00000001, 0x00000001},
    {"CMU_4A", 0x0000000a, 0x00000001, 0x00000001},
    {"CMU_4B", 0x0000000b, 0x00000001, 0x00000001},
    {"CMU_4C", 0x0000000c, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PMA_8BIT_CMU_GRP_3[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CMU_C0", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PMA_8BIT_CMU_GRP_4[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CMU_FF", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PMA_8BIT_LANE_GRP_0[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LANE_00", 0x00000000, 0x00000001, 0x00000001},
    {"LANE_01", 0x00000001, 0x00000001, 0x00000001},
    {"LANE_02", 0x00000002, 0x00000001, 0x00000001},
    {"LANE_03", 0x00000003, 0x00000001, 0x00000001},
    {"LANE_04", 0x00000004, 0x00000001, 0x00000001},
    {"LANE_05", 0x00000005, 0x00000001, 0x00000001},
    {"LANE_06", 0x00000006, 0x00000001, 0x00000001},
    {"LANE_07", 0x00000007, 0x00000001, 0x00000001},
    {"LANE_08", 0x00000008, 0x00000001, 0x00000001},
    {"LANE_09", 0x00000009, 0x00000001, 0x00000001},
    {"LANE_0A", 0x0000000a, 0x00000001, 0x00000001},
    {"LANE_0B", 0x0000000b, 0x00000001, 0x00000001},
    {"LANE_0C", 0x0000000c, 0x00000001, 0x00000001},
    {"LANE_0D", 0x0000000d, 0x00000001, 0x00000001},
    {"LANE_0E", 0x0000000e, 0x00000001, 0x00000001},
    {"LANE_0F", 0x0000000f, 0x00000001, 0x00000001},
    {"LANE_10", 0x00000010, 0x00000001, 0x00000001},
    {"LANE_11", 0x00000011, 0x00000001, 0x00000001},
    {"LANE_12", 0x00000012, 0x00000001, 0x00000001},
    {"LANE_13", 0x00000013, 0x00000001, 0x00000001},
    {"LANE_14", 0x00000014, 0x00000001, 0x00000001},
    {"LANE_15", 0x00000015, 0x00000001, 0x00000001},
    {"LANE_16", 0x00000016, 0x00000001, 0x00000001},
    {"LANE_17", 0x00000017, 0x00000001, 0x00000001},
    {"LANE_18", 0x00000018, 0x00000001, 0x00000001},
    {"LANE_19", 0x00000019, 0x00000001, 0x00000001},
    {"LANE_1A", 0x0000001a, 0x00000001, 0x00000001},
    {"LANE_1B", 0x0000001b, 0x00000001, 0x00000001},
    {"LANE_1C", 0x0000001c, 0x00000001, 0x00000001},
    {"LANE_1D", 0x0000001d, 0x00000001, 0x00000001},
    {"LANE_1E", 0x0000001e, 0x00000001, 0x00000001},
    {"LANE_1F", 0x0000001f, 0x00000001, 0x00000001},
    {"LANE_20", 0x00000020, 0x00000001, 0x00000001},
    {"LANE_21", 0x00000021, 0x00000001, 0x00000001},
    {"LANE_22", 0x00000022, 0x00000001, 0x00000001},
    {"LANE_23", 0x00000023, 0x00000001, 0x00000001},
    {"LANE_24", 0x00000024, 0x00000001, 0x00000001},
    {"LANE_25", 0x00000025, 0x00000001, 0x00000001},
    {"LANE_26", 0x00000026, 0x00000001, 0x00000001},
    {"LANE_27", 0x00000027, 0x00000001, 0x00000001},
    {"LANE_28", 0x00000028, 0x00000001, 0x00000001},
    {"LANE_29", 0x00000029, 0x00000001, 0x00000001},
    {"LANE_2A", 0x0000002a, 0x00000001, 0x00000001},
    {"LANE_2B", 0x0000002b, 0x00000001, 0x00000001},
    {"LANE_2C", 0x0000002c, 0x00000001, 0x00000001},
    {"LANE_2D", 0x0000002d, 0x00000001, 0x00000001},
    {"LANE_2E", 0x0000002e, 0x00000001, 0x00000001},
    {"LANE_2F", 0x0000002f, 0x00000001, 0x00000001},
    {"LANE_30", 0x00000030, 0x00000001, 0x00000001},
    {"LANE_31", 0x00000031, 0x00000001, 0x00000001},
    {"LANE_32", 0x00000032, 0x00000001, 0x00000001},
    {"LANE_33", 0x00000033, 0x00000001, 0x00000001},
    {"LANE_34", 0x00000034, 0x00000001, 0x00000001},
    {"LANE_35", 0x00000035, 0x00000001, 0x00000001},
    {"LANE_36", 0x00000036, 0x00000001, 0x00000001},
    {"LANE_37", 0x00000037, 0x00000001, 0x00000001},
    {"LANE_38", 0x00000038, 0x00000001, 0x00000001},
    {"LANE_39", 0x00000039, 0x00000001, 0x00000001},
    {"LANE_3A", 0x0000003a, 0x00000001, 0x00000001},
    {"LANE_3B", 0x0000003b, 0x00000001, 0x00000001},
    {"LANE_3C", 0x0000003c, 0x00000001, 0x00000001},
    {"LANE_3D", 0x0000003d, 0x00000001, 0x00000001},
    {"LANE_3E", 0x0000003e, 0x00000001, 0x00000001},
    {"LANE_3F", 0x0000003f, 0x00000001, 0x00000001},
    {"LANE_40", 0x00000040, 0x00000001, 0x00000001},
    {"LANE_41", 0x00000041, 0x00000001, 0x00000001},
    {"LANE_42", 0x00000042, 0x00000001, 0x00000001},
    {"LANE_43", 0x00000043, 0x00000001, 0x00000001},
    {"LANE_44", 0x00000044, 0x00000001, 0x00000001},
    {"LANE_45", 0x00000045, 0x00000001, 0x00000001},
    {"LANE_46", 0x00000046, 0x00000001, 0x00000001},
    {"LANE_47", 0x00000047, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PMA_8BIT_LANE_GRP_1[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LANE_C0", 0x00000000, 0x00000001, 0x00000001},
    {"LANE_C1", 0x00000001, 0x00000001, 0x00000001},
    {"LANE_C2", 0x00000002, 0x00000001, 0x00000001},
    {"LANE_C3", 0x00000003, 0x00000001, 0x00000001},
    {"LANE_C4", 0x00000004, 0x00000001, 0x00000001},
    {"LANE_C5", 0x00000005, 0x00000001, 0x00000001},
    {"LANE_C6", 0x00000006, 0x00000001, 0x00000001},
    {"LANE_C7", 0x00000007, 0x00000001, 0x00000001},
    {"LANE_C8", 0x00000008, 0x00000001, 0x00000001},
    {"LANE_C9", 0x00000009, 0x00000001, 0x00000001},
    {"LANE_CA", 0x0000000a, 0x00000001, 0x00000001},
    {"LANE_CB", 0x0000000b, 0x00000001, 0x00000001},
    {"LANE_CC", 0x0000000c, 0x00000001, 0x00000001},
    {"LANE_CD", 0x0000000d, 0x00000001, 0x00000001},
    {"LANE_CE", 0x0000000e, 0x00000001, 0x00000001},
    {"LANE_CF", 0x0000000f, 0x00000001, 0x00000001},
    {"LANE_D0", 0x00000010, 0x00000001, 0x00000001},
    {"LANE_D1", 0x00000011, 0x00000001, 0x00000001},
    {"LANE_D2", 0x00000012, 0x00000001, 0x00000001},
    {"LANE_D3", 0x00000013, 0x00000001, 0x00000001},
    {"LANE_D4", 0x00000014, 0x00000001, 0x00000001},
    {"LANE_D5", 0x00000015, 0x00000001, 0x00000001},
    {"LANE_D6", 0x00000016, 0x00000001, 0x00000001},
    {"LANE_D7", 0x00000017, 0x00000001, 0x00000001},
    {"LANE_D8", 0x00000018, 0x00000001, 0x00000001},
    {"LANE_D9", 0x00000019, 0x00000001, 0x00000001},
    {"LANE_DA", 0x0000001a, 0x00000001, 0x00000001},
    {"LANE_DB", 0x0000001b, 0x00000001, 0x00000001},
    {"LANE_DC", 0x0000001c, 0x00000001, 0x00000001},
    {"LANE_DD", 0x0000001d, 0x00000001, 0x00000001},
    {"LANE_DE", 0x0000001e, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PMA_8BIT_LANE_GRP_2[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LANE_E0", 0x00000000, 0x00000001, 0x00000001},
    {"LANE_E1", 0x00000001, 0x00000001, 0x00000001},
    {"LANE_E2", 0x00000002, 0x00000001, 0x00000001},
    {"LANE_E3", 0x00000003, 0x00000001, 0x00000001},
    {"LANE_E4", 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_HOST_PMA_8BIT[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"CMU_GRP_0", 0x0000f000, 0x00000001, 0x00000021, regs_within_HOST_PMA_8BIT_CMU_GRP_0},
    {"CMU_GRP_1", 0x0000f021, 0x00000001, 0x0000001f, regs_within_HOST_PMA_8BIT_CMU_GRP_1},
    {"CMU_GRP_2", 0x0000f040, 0x00000001, 0x00000080, regs_within_HOST_PMA_8BIT_CMU_GRP_2},
    {"CMU_GRP_3", 0x0000f0c0, 0x00000001, 0x0000003f, regs_within_HOST_PMA_8BIT_CMU_GRP_3},
    {"CMU_GRP_4", 0x0000f0ff, 0x00000001, 0x00000001, regs_within_HOST_PMA_8BIT_CMU_GRP_4},
    {"LANE_GRP_0", 0x0000f100, 0x00000001, 0x000000c0, regs_within_HOST_PMA_8BIT_LANE_GRP_0},
    {"LANE_GRP_1", 0x0000f1c0, 0x00000001, 0x00000020, regs_within_HOST_PMA_8BIT_LANE_GRP_1},
    {"LANE_GRP_2", 0x0000f1e0, 0x00000001, 0x00000005, regs_within_HOST_PMA_8BIT_LANE_GRP_2},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_8BIT_CMU_GRP_0[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CMU_00", 0x00000000, 0x00000001, 0x00000001},
    {"CMU_01", 0x00000001, 0x00000001, 0x00000001},
    {"CMU_02", 0x00000002, 0x00000001, 0x00000001},
    {"CMU_03", 0x00000003, 0x00000001, 0x00000001},
    {"CMU_04", 0x00000004, 0x00000001, 0x00000001},
    {"CMU_05", 0x00000005, 0x00000001, 0x00000001},
    {"CMU_06", 0x00000006, 0x00000001, 0x00000001},
    {"CMU_07", 0x00000007, 0x00000001, 0x00000001},
    {"CMU_08", 0x00000008, 0x00000001, 0x00000001},
    {"CMU_09", 0x00000009, 0x00000001, 0x00000001},
    {"CMU_0A", 0x0000000a, 0x00000001, 0x00000001},
    {"CMU_0B", 0x0000000b, 0x00000001, 0x00000001},
    {"CMU_0C", 0x0000000c, 0x00000001, 0x00000001},
    {"CMU_0D", 0x0000000d, 0x00000001, 0x00000001},
    {"CMU_0E", 0x0000000e, 0x00000001, 0x00000001},
    {"CMU_0F", 0x0000000f, 0x00000001, 0x00000001},
    {"CMU_10", 0x00000010, 0x00000001, 0x00000001},
    {"CMU_11", 0x00000011, 0x00000001, 0x00000001},
    {"CMU_12", 0x00000012, 0x00000001, 0x00000001},
    {"CMU_13", 0x00000013, 0x00000001, 0x00000001},
    {"CMU_14", 0x00000014, 0x00000001, 0x00000001},
    {"CMU_15", 0x00000015, 0x00000001, 0x00000001},
    {"CMU_16", 0x00000016, 0x00000001, 0x00000001},
    {"CMU_17", 0x00000017, 0x00000001, 0x00000001},
    {"CMU_18", 0x00000018, 0x00000001, 0x00000001},
    {"CMU_19", 0x00000019, 0x00000001, 0x00000001},
    {"CMU_1A", 0x0000001a, 0x00000001, 0x00000001},
    {"CMU_1B", 0x0000001b, 0x00000001, 0x00000001},
    {"CMU_1C", 0x0000001c, 0x00000001, 0x00000001},
    {"CMU_1D", 0x0000001d, 0x00000001, 0x00000001},
    {"CMU_1E", 0x0000001e, 0x00000001, 0x00000001},
    {"CMU_1F", 0x0000001f, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_8BIT_CMU_GRP_1[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CMU_21", 0x00000000, 0x00000001, 0x00000001},
    {"CMU_22", 0x00000001, 0x00000001, 0x00000001},
    {"CMU_23", 0x00000002, 0x00000001, 0x00000001},
    {"CMU_24", 0x00000003, 0x00000001, 0x00000001},
    {"CMU_25", 0x00000004, 0x00000001, 0x00000001},
    {"CMU_26", 0x00000005, 0x00000001, 0x00000001},
    {"CMU_27", 0x00000006, 0x00000001, 0x00000001},
    {"CMU_28", 0x00000007, 0x00000001, 0x00000001},
    {"CMU_29", 0x00000008, 0x00000001, 0x00000001},
    {"CMU_2A", 0x00000009, 0x00000001, 0x00000001},
    {"CMU_2B", 0x0000000a, 0x00000001, 0x00000001},
    {"CMU_2C", 0x0000000b, 0x00000001, 0x00000001},
    {"CMU_2D", 0x0000000c, 0x00000001, 0x00000001},
    {"CMU_2E", 0x0000000d, 0x00000001, 0x00000001},
    {"CMU_2F", 0x0000000e, 0x00000001, 0x00000001},
    {"CMU_30", 0x0000000f, 0x00000001, 0x00000001},
    {"CMU_31", 0x00000010, 0x00000001, 0x00000001},
    {"CMU_32", 0x00000011, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_8BIT_CMU_GRP_2[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CMU_40", 0x00000000, 0x00000001, 0x00000001},
    {"CMU_41", 0x00000001, 0x00000001, 0x00000001},
    {"CMU_42", 0x00000002, 0x00000001, 0x00000001},
    {"CMU_43", 0x00000003, 0x00000001, 0x00000001},
    {"CMU_44", 0x00000004, 0x00000001, 0x00000001},
    {"CMU_45", 0x00000005, 0x00000001, 0x00000001},
    {"CMU_46", 0x00000006, 0x00000001, 0x00000001},
    {"CMU_47", 0x00000007, 0x00000001, 0x00000001},
    {"CMU_48", 0x00000008, 0x00000001, 0x00000001},
    {"CMU_49", 0x00000009, 0x00000001, 0x00000001},
    {"CMU_4A", 0x0000000a, 0x00000001, 0x00000001},
    {"CMU_4B", 0x0000000b, 0x00000001, 0x00000001},
    {"CMU_4C", 0x0000000c, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_8BIT_CMU_GRP_3[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CMU_C0", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_8BIT_CMU_GRP_4[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CMU_FF", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_8BIT_LANE_GRP_0[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LANE_00", 0x00000000, 0x00000001, 0x00000001},
    {"LANE_01", 0x00000001, 0x00000001, 0x00000001},
    {"LANE_02", 0x00000002, 0x00000001, 0x00000001},
    {"LANE_03", 0x00000003, 0x00000001, 0x00000001},
    {"LANE_04", 0x00000004, 0x00000001, 0x00000001},
    {"LANE_05", 0x00000005, 0x00000001, 0x00000001},
    {"LANE_06", 0x00000006, 0x00000001, 0x00000001},
    {"LANE_07", 0x00000007, 0x00000001, 0x00000001},
    {"LANE_08", 0x00000008, 0x00000001, 0x00000001},
    {"LANE_09", 0x00000009, 0x00000001, 0x00000001},
    {"LANE_0A", 0x0000000a, 0x00000001, 0x00000001},
    {"LANE_0B", 0x0000000b, 0x00000001, 0x00000001},
    {"LANE_0C", 0x0000000c, 0x00000001, 0x00000001},
    {"LANE_0D", 0x0000000d, 0x00000001, 0x00000001},
    {"LANE_0E", 0x0000000e, 0x00000001, 0x00000001},
    {"LANE_0F", 0x0000000f, 0x00000001, 0x00000001},
    {"LANE_10", 0x00000010, 0x00000001, 0x00000001},
    {"LANE_11", 0x00000011, 0x00000001, 0x00000001},
    {"LANE_12", 0x00000012, 0x00000001, 0x00000001},
    {"LANE_13", 0x00000013, 0x00000001, 0x00000001},
    {"LANE_14", 0x00000014, 0x00000001, 0x00000001},
    {"LANE_15", 0x00000015, 0x00000001, 0x00000001},
    {"LANE_16", 0x00000016, 0x00000001, 0x00000001},
    {"LANE_17", 0x00000017, 0x00000001, 0x00000001},
    {"LANE_18", 0x00000018, 0x00000001, 0x00000001},
    {"LANE_19", 0x00000019, 0x00000001, 0x00000001},
    {"LANE_1A", 0x0000001a, 0x00000001, 0x00000001},
    {"LANE_1B", 0x0000001b, 0x00000001, 0x00000001},
    {"LANE_1C", 0x0000001c, 0x00000001, 0x00000001},
    {"LANE_1D", 0x0000001d, 0x00000001, 0x00000001},
    {"LANE_1E", 0x0000001e, 0x00000001, 0x00000001},
    {"LANE_1F", 0x0000001f, 0x00000001, 0x00000001},
    {"LANE_20", 0x00000020, 0x00000001, 0x00000001},
    {"LANE_21", 0x00000021, 0x00000001, 0x00000001},
    {"LANE_22", 0x00000022, 0x00000001, 0x00000001},
    {"LANE_23", 0x00000023, 0x00000001, 0x00000001},
    {"LANE_24", 0x00000024, 0x00000001, 0x00000001},
    {"LANE_25", 0x00000025, 0x00000001, 0x00000001},
    {"LANE_26", 0x00000026, 0x00000001, 0x00000001},
    {"LANE_27", 0x00000027, 0x00000001, 0x00000001},
    {"LANE_28", 0x00000028, 0x00000001, 0x00000001},
    {"LANE_29", 0x00000029, 0x00000001, 0x00000001},
    {"LANE_2A", 0x0000002a, 0x00000001, 0x00000001},
    {"LANE_2B", 0x0000002b, 0x00000001, 0x00000001},
    {"LANE_2C", 0x0000002c, 0x00000001, 0x00000001},
    {"LANE_2D", 0x0000002d, 0x00000001, 0x00000001},
    {"LANE_2E", 0x0000002e, 0x00000001, 0x00000001},
    {"LANE_2F", 0x0000002f, 0x00000001, 0x00000001},
    {"LANE_30", 0x00000030, 0x00000001, 0x00000001},
    {"LANE_31", 0x00000031, 0x00000001, 0x00000001},
    {"LANE_32", 0x00000032, 0x00000001, 0x00000001},
    {"LANE_33", 0x00000033, 0x00000001, 0x00000001},
    {"LANE_34", 0x00000034, 0x00000001, 0x00000001},
    {"LANE_35", 0x00000035, 0x00000001, 0x00000001},
    {"LANE_36", 0x00000036, 0x00000001, 0x00000001},
    {"LANE_37", 0x00000037, 0x00000001, 0x00000001},
    {"LANE_38", 0x00000038, 0x00000001, 0x00000001},
    {"LANE_39", 0x00000039, 0x00000001, 0x00000001},
    {"LANE_3A", 0x0000003a, 0x00000001, 0x00000001},
    {"LANE_3B", 0x0000003b, 0x00000001, 0x00000001},
    {"LANE_3C", 0x0000003c, 0x00000001, 0x00000001},
    {"LANE_3D", 0x0000003d, 0x00000001, 0x00000001},
    {"LANE_3E", 0x0000003e, 0x00000001, 0x00000001},
    {"LANE_3F", 0x0000003f, 0x00000001, 0x00000001},
    {"LANE_40", 0x00000040, 0x00000001, 0x00000001},
    {"LANE_41", 0x00000041, 0x00000001, 0x00000001},
    {"LANE_42", 0x00000042, 0x00000001, 0x00000001},
    {"LANE_43", 0x00000043, 0x00000001, 0x00000001},
    {"LANE_44", 0x00000044, 0x00000001, 0x00000001},
    {"LANE_45", 0x00000045, 0x00000001, 0x00000001},
    {"LANE_46", 0x00000046, 0x00000001, 0x00000001},
    {"LANE_47", 0x00000047, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_8BIT_LANE_GRP_1[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LANE_C0", 0x00000000, 0x00000001, 0x00000001},
    {"LANE_C1", 0x00000001, 0x00000001, 0x00000001},
    {"LANE_C2", 0x00000002, 0x00000001, 0x00000001},
    {"LANE_C3", 0x00000003, 0x00000001, 0x00000001},
    {"LANE_C4", 0x00000004, 0x00000001, 0x00000001},
    {"LANE_C5", 0x00000005, 0x00000001, 0x00000001},
    {"LANE_C6", 0x00000006, 0x00000001, 0x00000001},
    {"LANE_C7", 0x00000007, 0x00000001, 0x00000001},
    {"LANE_C8", 0x00000008, 0x00000001, 0x00000001},
    {"LANE_C9", 0x00000009, 0x00000001, 0x00000001},
    {"LANE_CA", 0x0000000a, 0x00000001, 0x00000001},
    {"LANE_CB", 0x0000000b, 0x00000001, 0x00000001},
    {"LANE_CC", 0x0000000c, 0x00000001, 0x00000001},
    {"LANE_CD", 0x0000000d, 0x00000001, 0x00000001},
    {"LANE_CE", 0x0000000e, 0x00000001, 0x00000001},
    {"LANE_CF", 0x0000000f, 0x00000001, 0x00000001},
    {"LANE_D0", 0x00000010, 0x00000001, 0x00000001},
    {"LANE_D1", 0x00000011, 0x00000001, 0x00000001},
    {"LANE_D2", 0x00000012, 0x00000001, 0x00000001},
    {"LANE_D3", 0x00000013, 0x00000001, 0x00000001},
    {"LANE_D4", 0x00000014, 0x00000001, 0x00000001},
    {"LANE_D5", 0x00000015, 0x00000001, 0x00000001},
    {"LANE_D6", 0x00000016, 0x00000001, 0x00000001},
    {"LANE_D7", 0x00000017, 0x00000001, 0x00000001},
    {"LANE_D8", 0x00000018, 0x00000001, 0x00000001},
    {"LANE_D9", 0x00000019, 0x00000001, 0x00000001},
    {"LANE_DA", 0x0000001a, 0x00000001, 0x00000001},
    {"LANE_DB", 0x0000001b, 0x00000001, 0x00000001},
    {"LANE_DC", 0x0000001c, 0x00000001, 0x00000001},
    {"LANE_DD", 0x0000001d, 0x00000001, 0x00000001},
    {"LANE_DE", 0x0000001e, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PMA_8BIT_LANE_GRP_2[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LANE_E0", 0x00000000, 0x00000001, 0x00000001},
    {"LANE_E1", 0x00000001, 0x00000001, 0x00000001},
    {"LANE_E2", 0x00000002, 0x00000001, 0x00000001},
    {"LANE_E3", 0x00000003, 0x00000001, 0x00000001},
    {"LANE_E4", 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_LINE_PMA_8BIT[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"CMU_GRP_0", 0x0000f000, 0x00000001, 0x00000021, regs_within_LINE_PMA_8BIT_CMU_GRP_0},
    {"CMU_GRP_1", 0x0000f021, 0x00000001, 0x0000001f, regs_within_LINE_PMA_8BIT_CMU_GRP_1},
    {"CMU_GRP_2", 0x0000f040, 0x00000001, 0x00000080, regs_within_LINE_PMA_8BIT_CMU_GRP_2},
    {"CMU_GRP_3", 0x0000f0c0, 0x00000001, 0x0000003f, regs_within_LINE_PMA_8BIT_CMU_GRP_3},
    {"CMU_GRP_4", 0x0000f0ff, 0x00000001, 0x00000001, regs_within_LINE_PMA_8BIT_CMU_GRP_4},
    {"LANE_GRP_0", 0x0000f100, 0x00000001, 0x000000c0, regs_within_LINE_PMA_8BIT_LANE_GRP_0},
    {"LANE_GRP_1", 0x0000f1c0, 0x00000001, 0x00000020, regs_within_LINE_PMA_8BIT_LANE_GRP_1},
    {"LANE_GRP_2", 0x0000f1e0, 0x00000001, 0x00000005, regs_within_LINE_PMA_8BIT_LANE_GRP_2},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_HOST_PCS_CFG_PCS1G_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS1G_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"PCS1G_MODE_CFG", 0x00000001, 0x00000001, 0x00000001},
    {"PCS1G_SD_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"PCS1G_ANEG_CFG_0", 0x00000003, 0x00000001, 0x00000001},
    {"PCS1G_ANEG_CFG_1", 0x00000004, 0x00000001, 0x00000001},
    {"PCS1G_ANEG_NP_CFG_0", 0x00000005, 0x00000001, 0x00000001},
    {"PCS1G_ANEG_NP_CFG_1", 0x00000006, 0x00000001, 0x00000001},
    {"PCS1G_LB_CFG", 0x00000007, 0x00000001, 0x00000001},
    {"PCS1G_DBG_CFG", 0x00000008, 0x00000001, 0x00000001},
    {"PCS1G_CDET_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"PCS1G_ANEG_STATUS_0", 0x0000000a, 0x00000001, 0x00000001},
    {"PCS1G_ANEG_STATUS_1", 0x0000000b, 0x00000001, 0x00000001},
    {"PCS1G_ANEG_NP_STATUS", 0x0000000c, 0x00000001, 0x00000001},
    {"PCS1G_LINK_STATUS", 0x0000000d, 0x00000001, 0x00000001},
    {"PCS1G_LINK_DOWN_CNT", 0x0000000e, 0x00000001, 0x00000001},
    {"PCS1G_STICKY", 0x0000000f, 0x00000001, 0x00000001},
    {"PCS1G_STICKY_MASK", 0x00000010, 0x00000001, 0x00000001},
    {"PCS1G_LPI_CFG", 0x00000011, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PCS_CFG_PCS1G_TSTPAT_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS1G_TSTPAT_MODE_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"PCS1G_TSTPAT_STATUS", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PCS_CFG_PCS1G_XGMII_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS1G_XGMII_CFG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PCS_CFG_PCS25G_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS25G_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"PCS25G_SD_CFG", 0x00000001, 0x00000001, 0x00000001},
    {"PCS25G_STATUS", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PCS_CFG_PCS25G_FEC74[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS25G_BASE_R_FEC_ABILITY", 0x00000000, 0x00000001, 0x00000001},
    {"PCS25G_BASE_R_FEC_CONTROL", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PCS_CFG_PCS25G_FEC74_ERROR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS25G_FEC74_CERR_CNT_L", 0x00000000, 0x00000001, 0x00000001},
    {"PCS25G_FEC74_CERR_CNT_H", 0x00000001, 0x00000001, 0x00000001},
    {"PCS25G_FEC74_NCERR_CNT_L", 0x00000002, 0x00000001, 0x00000001},
    {"PCS25G_FEC74_NCERR_CNT_H", 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PCS_CFG_PCS25G_FEC74_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS25G_FEC74_STATUS", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PCS_CFG_PCS25G_RSFEC_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS25G_RSFEC_CFG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PCS_CFG_PCS25G_STICKY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS25G_STICKY_SIG", 0x00000000, 0x00000001, 0x00000001},
    {"PCS25G_STICKY_SIG_MASK", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PCS_CFG_PCS25G_DEBUG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS25G_DEBUG_REG_7", 0x00000000, 0x00000001, 0x00000001},
    {"PCS25G_DEBUG_REG_6", 0x00000001, 0x00000001, 0x00000001},
    {"PCS25G_DEBUG_REG_5", 0x00000002, 0x00000001, 0x00000001},
    {"PCS25G_DEBUG_REG_4", 0x00000003, 0x00000001, 0x00000001},
    {"PCS25G_DEBUG_REG_3", 0x00000004, 0x00000001, 0x00000001},
    {"PCS25G_DEBUG_REG_2", 0x00000005, 0x00000001, 0x00000001},
    {"PCS25G_DEBUG_REG_1", 0x00000006, 0x00000001, 0x00000001},
    {"PCS25G_DEBUG_REG_0", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PCS_CFG_PCS25G_CWM_RADAPT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CWM_RADAPT_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"CWM_RADAPT_STICKY", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_STAT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"XGMII_H2L_RA_FIFO_MASK", 0x00000000, 0x00000001, 0x00000001},
    {"XGMII_H2L_RA_FIFO_SIGNAL", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_IDLE_COUNTS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"XGMII_H2L_RA_FIFO_IDLE_ADD_COUNT", 0x00000000, 0x00000001, 0x00000001},
    {"XGMII_H2L_RA_FIFO_IDLE_DROP_COUNT", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_HOST_PCS_CFG[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"PCS1G_CFG_STATUS", 0x0000e002, 0x00000001, 0x00000012, regs_within_HOST_PCS_CFG_PCS1G_CFG_STATUS},
    {"PCS1G_TSTPAT_CFG_STATUS", 0x0000e016, 0x00000001, 0x00000002, regs_within_HOST_PCS_CFG_PCS1G_TSTPAT_CFG_STATUS},
    {"PCS1G_XGMII_CFG_STATUS", 0x0000e018, 0x00000001, 0x00000001, regs_within_HOST_PCS_CFG_PCS1G_XGMII_CFG_STATUS},
    {"PCS25G_CFG_STATUS", 0x0000e019, 0x00000001, 0x00000003, regs_within_HOST_PCS_CFG_PCS25G_CFG_STATUS},
    {"PCS25G_FEC74", 0x000000aa, 0x00000001, 0x00000002, regs_within_HOST_PCS_CFG_PCS25G_FEC74},
    {"PCS25G_FEC74_ERROR", 0x000000ac, 0x00000001, 0x00000004, regs_within_HOST_PCS_CFG_PCS25G_FEC74_ERROR},
    {"PCS25G_FEC74_STATUS", 0x0000e021, 0x00000001, 0x00000001, regs_within_HOST_PCS_CFG_PCS25G_FEC74_STATUS},
    {"PCS25G_RSFEC_CFG", 0x0000e022, 0x00000001, 0x00000001, regs_within_HOST_PCS_CFG_PCS25G_RSFEC_CFG},
    {"PCS25G_STICKY", 0x0000e02d, 0x00000001, 0x00000002, regs_within_HOST_PCS_CFG_PCS25G_STICKY},
#ifndef VTSS_RELEASE
    {"PCS25G_DEBUG", 0x0000e0f8, 0x00000001, 0x00000008, regs_within_HOST_PCS_CFG_PCS25G_DEBUG},
#endif
    {"PCS25G_CWM_RADAPT", 0x0000e023, 0x00000001, 0x00000002, regs_within_HOST_PCS_CFG_PCS25G_CWM_RADAPT},
    {"XGMII_H2L_RA_FIFO_STAT", 0x0000e025, 0x00000001, 0x00000002, regs_within_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_STAT},
    {"XGMII_H2L_RA_FIFO_IDLE_COUNTS", 0x0000e027, 0x00000001, 0x00000002, regs_within_HOST_PCS_CFG_XGMII_H2L_RA_FIFO_IDLE_COUNTS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_LINE_PCS_CFG_PCS1G_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS1G_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"PCS1G_MODE_CFG", 0x00000001, 0x00000001, 0x00000001},
    {"PCS1G_SD_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"PCS1G_ANEG_CFG_0", 0x00000003, 0x00000001, 0x00000001},
    {"PCS1G_ANEG_CFG_1", 0x00000004, 0x00000001, 0x00000001},
    {"PCS1G_ANEG_NP_CFG_0", 0x00000005, 0x00000001, 0x00000001},
    {"PCS1G_ANEG_NP_CFG_1", 0x00000006, 0x00000001, 0x00000001},
    {"PCS1G_LB_CFG", 0x00000007, 0x00000001, 0x00000001},
    {"PCS1G_DBG_CFG", 0x00000008, 0x00000001, 0x00000001},
    {"PCS1G_CDET_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"PCS1G_ANEG_STATUS_0", 0x0000000a, 0x00000001, 0x00000001},
    {"PCS1G_ANEG_STATUS_1", 0x0000000b, 0x00000001, 0x00000001},
    {"PCS1G_ANEG_NP_STATUS", 0x0000000c, 0x00000001, 0x00000001},
    {"PCS1G_LINK_STATUS", 0x0000000d, 0x00000001, 0x00000001},
    {"PCS1G_LINK_DOWN_CNT", 0x0000000e, 0x00000001, 0x00000001},
    {"PCS1G_STICKY", 0x0000000f, 0x00000001, 0x00000001},
    {"PCS1G_STICKY_MASK", 0x00000010, 0x00000001, 0x00000001},
    {"PCS1G_LPI_CFG", 0x00000011, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PCS_CFG_PCS1G_TSTPAT_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS1G_TSTPAT_MODE_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"PCS1G_TSTPAT_STATUS", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PCS_CFG_PCS1G_XGMII_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS1G_XGMII_CFG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PCS_CFG_PCS25G_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS25G_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"PCS25G_SD_CFG", 0x00000001, 0x00000001, 0x00000001},
    {"PCS25G_STATUS", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PCS_CFG_PCS25G_FEC74[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS25G_BASE_R_FEC_ABILITY", 0x00000000, 0x00000001, 0x00000001},
    {"PCS25G_BASE_R_FEC_CONTROL", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PCS_CFG_PCS25G_FEC74_ERROR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS25G_FEC74_CERR_CNT_L", 0x00000000, 0x00000001, 0x00000001},
    {"PCS25G_FEC74_CERR_CNT_H", 0x00000001, 0x00000001, 0x00000001},
    {"PCS25G_FEC74_NCERR_CNT_L", 0x00000002, 0x00000001, 0x00000001},
    {"PCS25G_FEC74_NCERR_CNT_H", 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PCS_CFG_PCS25G_FEC74_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS25G_FEC74_STATUS", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PCS_CFG_PCS25G_RSFEC_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS25G_RSFEC_CFG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PCS_CFG_PCS25G_STICKY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS25G_STICKY_SIG", 0x00000000, 0x00000001, 0x00000001},
    {"PCS25G_STICKY_SIG_MASK", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PCS_CFG_PCS25G_DEBUG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS25G_DEBUG_REG_7", 0x00000000, 0x00000001, 0x00000001},
    {"PCS25G_DEBUG_REG_6", 0x00000001, 0x00000001, 0x00000001},
    {"PCS25G_DEBUG_REG_5", 0x00000002, 0x00000001, 0x00000001},
    {"PCS25G_DEBUG_REG_4", 0x00000003, 0x00000001, 0x00000001},
    {"PCS25G_DEBUG_REG_3", 0x00000004, 0x00000001, 0x00000001},
    {"PCS25G_DEBUG_REG_2", 0x00000005, 0x00000001, 0x00000001},
    {"PCS25G_DEBUG_REG_1", 0x00000006, 0x00000001, 0x00000001},
    {"PCS25G_DEBUG_REG_0", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PCS_CFG_PCS25G_CWM_RADAPT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CWM_RADAPT_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"CWM_RADAPT_STICKY", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_LINE_PCS_CFG[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"PCS1G_CFG_STATUS", 0x0000e002, 0x00000001, 0x00000012, regs_within_LINE_PCS_CFG_PCS1G_CFG_STATUS},
    {"PCS1G_TSTPAT_CFG_STATUS", 0x0000e016, 0x00000001, 0x00000002, regs_within_LINE_PCS_CFG_PCS1G_TSTPAT_CFG_STATUS},
    {"PCS1G_XGMII_CFG_STATUS", 0x0000e018, 0x00000001, 0x00000001, regs_within_LINE_PCS_CFG_PCS1G_XGMII_CFG_STATUS},
    {"PCS25G_CFG_STATUS", 0x0000e019, 0x00000001, 0x00000003, regs_within_LINE_PCS_CFG_PCS25G_CFG_STATUS},
    {"PCS25G_FEC74", 0x000000aa, 0x00000001, 0x00000002, regs_within_LINE_PCS_CFG_PCS25G_FEC74},
    {"PCS25G_FEC74_ERROR", 0x000000ac, 0x00000001, 0x00000004, regs_within_LINE_PCS_CFG_PCS25G_FEC74_ERROR},
    {"PCS25G_FEC74_STATUS", 0x0000e021, 0x00000001, 0x00000001, regs_within_LINE_PCS_CFG_PCS25G_FEC74_STATUS},
    {"PCS25G_RSFEC_CFG", 0x0000e022, 0x00000001, 0x00000001, regs_within_LINE_PCS_CFG_PCS25G_RSFEC_CFG},
    {"PCS25G_STICKY", 0x0000e02d, 0x00000001, 0x00000002, regs_within_LINE_PCS_CFG_PCS25G_STICKY},
#ifndef VTSS_RELEASE
    {"PCS25G_DEBUG", 0x0000e0f8, 0x00000001, 0x00000008, regs_within_LINE_PCS_CFG_PCS25G_DEBUG},
#endif
    {"PCS25G_CWM_RADAPT", 0x0000e023, 0x00000001, 0x00000002, regs_within_LINE_PCS_CFG_PCS25G_CWM_RADAPT},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_HOST_PCS25G_PCS_REGISTERS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CONTROL1", 0x00000000, 0x00000001, 0x00000001},
    {"STATUS1", 0x00000001, 0x00000001, 0x00000001},
    {"DEVICE_ID0", 0x00000002, 0x00000001, 0x00000001},
    {"DEVICE_ID1", 0x00000003, 0x00000001, 0x00000001},
    {"SPEED_ABILITY", 0x00000004, 0x00000001, 0x00000001},
    {"DEVICES_IN_PKG1", 0x00000005, 0x00000001, 0x00000001},
    {"CONTROL2", 0x00000007, 0x00000001, 0x00000001},
    {"STATUS2", 0x00000008, 0x00000001, 0x00000001},
    {"PKG_ID0", 0x0000000e, 0x00000001, 0x00000001},
    {"PKG_ID1", 0x0000000f, 0x00000001, 0x00000001},
    {"EEE_CTRL_CAPABILITY", 0x00000014, 0x00000001, 0x00000001},
    {"BASER_STATUS1", 0x00000020, 0x00000001, 0x00000001},
    {"BASER_STATUS2", 0x00000021, 0x00000001, 0x00000001},
    {"SEED_A0", 0x00000022, 0x00000001, 0x00000001},
    {"SEED_A1", 0x00000023, 0x00000001, 0x00000001},
    {"SEED_A2", 0x00000024, 0x00000001, 0x00000001},
    {"SEED_A3", 0x00000025, 0x00000001, 0x00000001},
    {"SEED_B0", 0x00000026, 0x00000001, 0x00000001},
    {"SEED_B1", 0x00000027, 0x00000001, 0x00000001},
    {"SEED_B2", 0x00000028, 0x00000001, 0x00000001},
    {"SEED_B3", 0x00000029, 0x00000001, 0x00000001},
    {"BASER_TEST_CONTROL", 0x0000002a, 0x00000001, 0x00000001},
    {"BASER_TEST_ERR_CNT", 0x0000002b, 0x00000001, 0x00000001},
    {"BER_HIGH_ORDER_CNT", 0x0000002c, 0x00000001, 0x00000001},
    {"ERR_BLK_HIGH_ORDER_CNT", 0x0000002d, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_PCS25G_VENDOR_PCS_REGISTERS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VENDOR_SCRATCH", 0x00000000, 0x00000001, 0x00000001},
    {"VENDOR_CORE_REV", 0x00000001, 0x00000001, 0x00000001},
    {"VENDOR_VL_INTVL", 0x00000002, 0x00000001, 0x00000001},
    {"VENDOR_TXLANE_THRESH", 0x00000003, 0x00000001, 0x00000001},
    {"VENDOR_VL0_0", 0x00000008, 0x00000001, 0x00000001},
    {"VENDOR_VL0_1", 0x00000009, 0x00000001, 0x00000001},
    {"VENDOR_PCS_MODE", 0x00000010, 0x00000001, 0x00000001},
    {"GB_SHIFT", 0x00000011, 0x00000001, 0x00000001},
    {"LATENCY", 0x00000012, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_HOST_PCS25G[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"PCS_REGISTERS", 0x00000000, 0x00000001, 0x00000200, regs_within_HOST_PCS25G_PCS_REGISTERS},
    {"VENDOR_PCS_REGISTERS", 0x00008000, 0x00000001, 0x00000200, regs_within_HOST_PCS25G_VENDOR_PCS_REGISTERS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_LINE_PCS25G_PCS_REGISTERS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CONTROL1", 0x00000000, 0x00000001, 0x00000001},
    {"STATUS1", 0x00000001, 0x00000001, 0x00000001},
    {"DEVICE_ID0", 0x00000002, 0x00000001, 0x00000001},
    {"DEVICE_ID1", 0x00000003, 0x00000001, 0x00000001},
    {"SPEED_ABILITY", 0x00000004, 0x00000001, 0x00000001},
    {"DEVICES_IN_PKG1", 0x00000005, 0x00000001, 0x00000001},
    {"CONTROL2", 0x00000007, 0x00000001, 0x00000001},
    {"STATUS2", 0x00000008, 0x00000001, 0x00000001},
    {"PKG_ID0", 0x0000000e, 0x00000001, 0x00000001},
    {"PKG_ID1", 0x0000000f, 0x00000001, 0x00000001},
    {"EEE_CTRL_CAPABILITY", 0x00000014, 0x00000001, 0x00000001},
    {"BASER_STATUS1", 0x00000020, 0x00000001, 0x00000001},
    {"BASER_STATUS2", 0x00000021, 0x00000001, 0x00000001},
    {"SEED_A0", 0x00000022, 0x00000001, 0x00000001},
    {"SEED_A1", 0x00000023, 0x00000001, 0x00000001},
    {"SEED_A2", 0x00000024, 0x00000001, 0x00000001},
    {"SEED_A3", 0x00000025, 0x00000001, 0x00000001},
    {"SEED_B0", 0x00000026, 0x00000001, 0x00000001},
    {"SEED_B1", 0x00000027, 0x00000001, 0x00000001},
    {"SEED_B2", 0x00000028, 0x00000001, 0x00000001},
    {"SEED_B3", 0x00000029, 0x00000001, 0x00000001},
    {"BASER_TEST_CONTROL", 0x0000002a, 0x00000001, 0x00000001},
    {"BASER_TEST_ERR_CNT", 0x0000002b, 0x00000001, 0x00000001},
    {"BER_HIGH_ORDER_CNT", 0x0000002c, 0x00000001, 0x00000001},
    {"ERR_BLK_HIGH_ORDER_CNT", 0x0000002d, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_PCS25G_VENDOR_PCS_REGISTERS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VENDOR_SCRATCH", 0x00000000, 0x00000001, 0x00000001},
    {"VENDOR_CORE_REV", 0x00000001, 0x00000001, 0x00000001},
    {"VENDOR_VL_INTVL", 0x00000002, 0x00000001, 0x00000001},
    {"VENDOR_TXLANE_THRESH", 0x00000003, 0x00000001, 0x00000001},
    {"VENDOR_VL0_0", 0x00000008, 0x00000001, 0x00000001},
    {"VENDOR_VL0_1", 0x00000009, 0x00000001, 0x00000001},
    {"VENDOR_PCS_MODE", 0x00000010, 0x00000001, 0x00000001},
    {"GB_SHIFT", 0x00000011, 0x00000001, 0x00000001},
    {"LATENCY", 0x00000012, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_LINE_PCS25G[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"PCS_REGISTERS", 0x00000000, 0x00000001, 0x00000200, regs_within_LINE_PCS25G_PCS_REGISTERS},
    {"VENDOR_PCS_REGISTERS", 0x00008000, 0x00000001, 0x00000200, regs_within_LINE_PCS25G_VENDOR_PCS_REGISTERS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_HOST_RSFEC_RS_FEC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RS_FEC_CONTROL", 0x00000000, 0x00000001, 0x00000001},
    {"RS_FEC_STATUS", 0x00000001, 0x00000001, 0x00000001},
    {"RS_FEC_CCW_LO", 0x00000002, 0x00000001, 0x00000001},
    {"RS_FEC_CCW_HI", 0x00000003, 0x00000001, 0x00000001},
    {"RS_FEC_NCCW_LO", 0x00000004, 0x00000001, 0x00000001},
    {"RS_FEC_NCCW_HI", 0x00000005, 0x00000001, 0x00000001},
    {"RS_FEC_LANEMAP", 0x00000006, 0x00000001, 0x00000001},
    {"RS_FEC_SYMBLERR0_LO", 0x0000000a, 0x00000001, 0x00000001},
    {"RS_FEC_SYMBLERR0_HI", 0x0000000b, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_RSFEC_RS_FEC_VENDOR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RS_FEC_VENDOR_CONTROL", 0x00000000, 0x00000001, 0x00000001},
    {"RS_FEC_VENDOR_INFO1", 0x00000001, 0x00000001, 0x00000001},
    {"RS_FEC_VENDOR_INFO2", 0x00000002, 0x00000001, 0x00000001},
    {"RS_FEC_VENDOR_REVISION", 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_HOST_RSFEC[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"RS_FEC", 0x000000c8, 0x00000001, 0x00000200, regs_within_HOST_RSFEC_RS_FEC},
    {"RS_FEC_VENDOR", 0x00008200, 0x00000001, 0x00000200, regs_within_HOST_RSFEC_RS_FEC_VENDOR},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_LINE_RSFEC_RS_FEC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RS_FEC_CONTROL", 0x00000000, 0x00000001, 0x00000001},
    {"RS_FEC_STATUS", 0x00000001, 0x00000001, 0x00000001},
    {"RS_FEC_CCW_LO", 0x00000002, 0x00000001, 0x00000001},
    {"RS_FEC_CCW_HI", 0x00000003, 0x00000001, 0x00000001},
    {"RS_FEC_NCCW_LO", 0x00000004, 0x00000001, 0x00000001},
    {"RS_FEC_NCCW_HI", 0x00000005, 0x00000001, 0x00000001},
    {"RS_FEC_LANEMAP", 0x00000006, 0x00000001, 0x00000001},
    {"RS_FEC_SYMBLERR0_LO", 0x0000000a, 0x00000001, 0x00000001},
    {"RS_FEC_SYMBLERR0_HI", 0x0000000b, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_RSFEC_RS_FEC_VENDOR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RS_FEC_VENDOR_CONTROL", 0x00000000, 0x00000001, 0x00000001},
    {"RS_FEC_VENDOR_INFO1", 0x00000001, 0x00000001, 0x00000001},
    {"RS_FEC_VENDOR_INFO2", 0x00000002, 0x00000001, 0x00000001},
    {"RS_FEC_VENDOR_REVISION", 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_LINE_RSFEC[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"RS_FEC", 0x000000c8, 0x00000001, 0x00000200, regs_within_LINE_RSFEC_RS_FEC},
    {"RS_FEC_VENDOR", 0x00008200, 0x00000001, 0x00000200, regs_within_LINE_RSFEC_RS_FEC_VENDOR},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_KR_PMD_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"KR_PMD_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_KR_PMD_STS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"KR_PMD_STS", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_LP_COEF_UPD[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LP_COEF_UPD", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_LP_STS_RPT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LP_STS_RPT", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_LD_COEF_UPD[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LD_COEF_UPD", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_LD_STS_RPT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LD_STS_RPT", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_CLK_EN[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CLK_EN", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_TMR_HOLD[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TMR_HOLD", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_TR_CFG0[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TR_CFG0", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_TR_CFG1[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TR_CFG1", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_FRCNT_BER[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FRCNT_BER", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_TR_FRSENT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TR_FRSENT_L", 0x00000000, 0x00000001, 0x00000001},
    {"TR_FRSENT_H", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_TR_ERRCNT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TR_ERRCNT", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_AN_CFG0[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AN_CFG0", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_AN_STS0[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AN_STS0", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_LD_ADV[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LD_ADV0", 0x00000000, 0x00000001, 0x00000001},
    {"LD_ADV1", 0x00000001, 0x00000001, 0x00000001},
    {"LD_ADV2", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_LP_BP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LP_BP0", 0x00000000, 0x00000001, 0x00000001},
    {"LP_BP1", 0x00000001, 0x00000001, 0x00000001},
    {"LP_BP2", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_LD_NP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LD_NP0", 0x00000000, 0x00000001, 0x00000001},
    {"LD_NP1", 0x00000001, 0x00000001, 0x00000001},
    {"LD_NP2", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_LP_NP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LP_NP0", 0x00000000, 0x00000001, 0x00000001},
    {"LP_NP1", 0x00000001, 0x00000001, 0x00000001},
    {"LP_NP2", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_BP_ETH_STS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"BP_ETH_STS", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_AN_CFG1[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AN_CFG1", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_AN_CFG2[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AN_CFG2", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_BL_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"BL_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"BL_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_AW_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AW_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"AW_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_LF_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LF_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"LF_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_FR_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FR_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"FR_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_LP_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LP_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"LP_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_TR_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TR_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"TR_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_PD_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PD_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"PD_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_RD_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RD_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"RD_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_WT_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"WT_TMR", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_MW_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MW_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"MW_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_GEN0_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GEN0_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"GEN0_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_GEN1_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GEN1_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"GEN1_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_AN_HIST[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AN_HIST", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_AN_SM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AN_SM", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_AN_STS1[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AN_STS1", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_FW_MSG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FW_MSG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_FW_REQ[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FW_REQ", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_IRQ_VEC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IRQ_VEC_0", 0x00000000, 0x00000001, 0x00000001},
    {"IRQ_VEC_1", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_KR_IRQ_MASK[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IRQ_MASK_0", 0x00000000, 0x00000001, 0x00000001},
    {"IRQ_MASK_1", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_HOST_KR[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"KR_PMD_CTRL", 0x00000096, 0x00000001, 0x00000001, regs_within_HOST_KR_KR_PMD_CTRL},
    {"KR_PMD_STS", 0x00000097, 0x00000001, 0x00000001, regs_within_HOST_KR_KR_PMD_STS},
    {"LP_COEF_UPD", 0x00000098, 0x00000001, 0x00000001, regs_within_HOST_KR_LP_COEF_UPD},
    {"LP_STS_RPT", 0x00000099, 0x00000001, 0x00000001, regs_within_HOST_KR_LP_STS_RPT},
    {"LD_COEF_UPD", 0x0000009a, 0x00000001, 0x00000001, regs_within_HOST_KR_LD_COEF_UPD},
    {"LD_STS_RPT", 0x0000009b, 0x00000001, 0x00000001, regs_within_HOST_KR_LD_STS_RPT},
    {"CLK_EN", 0x00009100, 0x00000001, 0x00000001, regs_within_HOST_KR_CLK_EN},
    {"TMR_HOLD", 0x00009101, 0x00000001, 0x00000001, regs_within_HOST_KR_TMR_HOLD},
    {"TR_CFG0", 0x00009102, 0x00000001, 0x00000001, regs_within_HOST_KR_TR_CFG0},
    {"TR_CFG1", 0x00009103, 0x00000001, 0x00000001, regs_within_HOST_KR_TR_CFG1},
    {"FRCNT_BER", 0x00009104, 0x00000001, 0x00000001, regs_within_HOST_KR_FRCNT_BER},
    {"TR_FRSENT", 0x00009105, 0x00000001, 0x00000002, regs_within_HOST_KR_TR_FRSENT},
    {"TR_ERRCNT", 0x00009107, 0x00000001, 0x00000001, regs_within_HOST_KR_TR_ERRCNT},
    {"AN_CFG0", 0x00000000, 0x00000001, 0x00000001, regs_within_HOST_KR_AN_CFG0},
    {"AN_STS0", 0x00000001, 0x00000001, 0x00000001, regs_within_HOST_KR_AN_STS0},
    {"LD_ADV", 0x00000010, 0x00000001, 0x00000003, regs_within_HOST_KR_LD_ADV},
    {"LP_BP", 0x00000013, 0x00000001, 0x00000004, regs_within_HOST_KR_LP_BP},
    {"LD_NP", 0x00000016, 0x00000001, 0x00000003, regs_within_HOST_KR_LD_NP},
    {"LP_NP", 0x00000019, 0x00000001, 0x00000004, regs_within_HOST_KR_LP_NP},
    {"BP_ETH_STS", 0x00000030, 0x00000001, 0x00000001, regs_within_HOST_KR_BP_ETH_STS},
    {"AN_CFG1", 0x00008000, 0x00000001, 0x00000001, regs_within_HOST_KR_AN_CFG1},
    {"AN_CFG2", 0x00008002, 0x00000001, 0x00000001, regs_within_HOST_KR_AN_CFG2},
    {"BL_TMR", 0x00008010, 0x00000001, 0x00000002, regs_within_HOST_KR_BL_TMR},
    {"AW_TMR", 0x00008012, 0x00000001, 0x00000002, regs_within_HOST_KR_AW_TMR},
    {"LF_TMR", 0x00008014, 0x00000001, 0x00000002, regs_within_HOST_KR_LF_TMR},
    {"FR_TMR", 0x00008016, 0x00000001, 0x00000002, regs_within_HOST_KR_FR_TMR},
    {"LP_TMR", 0x00008018, 0x00000001, 0x00000002, regs_within_HOST_KR_LP_TMR},
    {"TR_TMR", 0x0000801a, 0x00000001, 0x00000002, regs_within_HOST_KR_TR_TMR},
    {"PD_TMR", 0x0000801c, 0x00000001, 0x00000002, regs_within_HOST_KR_PD_TMR},
    {"RD_TMR", 0x0000801e, 0x00000001, 0x00000002, regs_within_HOST_KR_RD_TMR},
    {"WT_TMR", 0x00008024, 0x00000001, 0x00000001, regs_within_HOST_KR_WT_TMR},
    {"MW_TMR", 0x00008026, 0x00000001, 0x00000002, regs_within_HOST_KR_MW_TMR},
    {"GEN0_TMR", 0x00008028, 0x00000001, 0x00000002, regs_within_HOST_KR_GEN0_TMR},
    {"GEN1_TMR", 0x0000802a, 0x00000001, 0x00000002, regs_within_HOST_KR_GEN1_TMR},
#ifndef VTSS_RELEASE
    {"AN_HIST", 0x00008030, 0x00000001, 0x00000001, regs_within_HOST_KR_AN_HIST},
#endif
    {"AN_SM", 0x00008031, 0x00000001, 0x00000001, regs_within_HOST_KR_AN_SM},
    {"AN_STS1", 0x00008032, 0x00000001, 0x00000001, regs_within_HOST_KR_AN_STS1},
    {"FW_MSG", 0x00008040, 0x00000001, 0x00000001, regs_within_HOST_KR_FW_MSG},
    {"FW_REQ", 0x00008041, 0x00000001, 0x00000001, regs_within_HOST_KR_FW_REQ},
    {"IRQ_VEC", 0x00008042, 0x00000001, 0x00000002, regs_within_HOST_KR_IRQ_VEC},
    {"IRQ_MASK", 0x00008044, 0x00000001, 0x00000002, regs_within_HOST_KR_IRQ_MASK},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_KR_PMD_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"KR_PMD_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_KR_PMD_STS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"KR_PMD_STS", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_LP_COEF_UPD[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LP_COEF_UPD", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_LP_STS_RPT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LP_STS_RPT", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_LD_COEF_UPD[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LD_COEF_UPD", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_LD_STS_RPT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LD_STS_RPT", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_CLK_EN[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CLK_EN", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_TMR_HOLD[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TMR_HOLD", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_TR_CFG0[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TR_CFG0", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_TR_CFG1[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TR_CFG1", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_FRCNT_BER[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FRCNT_BER", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_TR_FRSENT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TR_FRSENT_L", 0x00000000, 0x00000001, 0x00000001},
    {"TR_FRSENT_H", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_TR_ERRCNT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TR_ERRCNT", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_AN_CFG0[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AN_CFG0", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_AN_STS0[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AN_STS0", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_LD_ADV[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LD_ADV0", 0x00000000, 0x00000001, 0x00000001},
    {"LD_ADV1", 0x00000001, 0x00000001, 0x00000001},
    {"LD_ADV2", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_LP_BP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LP_BP0", 0x00000000, 0x00000001, 0x00000001},
    {"LP_BP1", 0x00000001, 0x00000001, 0x00000001},
    {"LP_BP2", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_LD_NP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LD_NP0", 0x00000000, 0x00000001, 0x00000001},
    {"LD_NP1", 0x00000001, 0x00000001, 0x00000001},
    {"LD_NP2", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_LP_NP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LP_NP0", 0x00000000, 0x00000001, 0x00000001},
    {"LP_NP1", 0x00000001, 0x00000001, 0x00000001},
    {"LP_NP2", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_BP_ETH_STS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"BP_ETH_STS", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_AN_CFG1[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AN_CFG1", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_AN_CFG2[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AN_CFG2", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_BL_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"BL_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"BL_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_AW_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AW_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"AW_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_LF_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LF_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"LF_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_FR_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FR_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"FR_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_LP_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LP_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"LP_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_TR_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TR_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"TR_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_PD_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PD_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"PD_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_RD_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RD_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"RD_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_WT_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"WT_TMR", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_MW_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MW_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"MW_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_GEN0_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GEN0_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"GEN0_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_GEN1_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GEN1_TMR_LOW", 0x00000000, 0x00000001, 0x00000001},
    {"GEN1_TMR_HIGH", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_AN_HIST[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AN_HIST", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_AN_SM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AN_SM", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_AN_STS1[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AN_STS1", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_FW_MSG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FW_MSG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_FW_REQ[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FW_REQ", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_IRQ_VEC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IRQ_VEC_0", 0x00000000, 0x00000001, 0x00000001},
    {"IRQ_VEC_1", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_KR_IRQ_MASK[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IRQ_MASK_0", 0x00000000, 0x00000001, 0x00000001},
    {"IRQ_MASK_1", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_LINE_KR[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"KR_PMD_CTRL", 0x00000096, 0x00000001, 0x00000001, regs_within_LINE_KR_KR_PMD_CTRL},
    {"KR_PMD_STS", 0x00000097, 0x00000001, 0x00000001, regs_within_LINE_KR_KR_PMD_STS},
    {"LP_COEF_UPD", 0x00000098, 0x00000001, 0x00000001, regs_within_LINE_KR_LP_COEF_UPD},
    {"LP_STS_RPT", 0x00000099, 0x00000001, 0x00000001, regs_within_LINE_KR_LP_STS_RPT},
    {"LD_COEF_UPD", 0x0000009a, 0x00000001, 0x00000001, regs_within_LINE_KR_LD_COEF_UPD},
    {"LD_STS_RPT", 0x0000009b, 0x00000001, 0x00000001, regs_within_LINE_KR_LD_STS_RPT},
    {"CLK_EN", 0x00009100, 0x00000001, 0x00000001, regs_within_LINE_KR_CLK_EN},
    {"TMR_HOLD", 0x00009101, 0x00000001, 0x00000001, regs_within_LINE_KR_TMR_HOLD},
    {"TR_CFG0", 0x00009102, 0x00000001, 0x00000001, regs_within_LINE_KR_TR_CFG0},
    {"TR_CFG1", 0x00009103, 0x00000001, 0x00000001, regs_within_LINE_KR_TR_CFG1},
    {"FRCNT_BER", 0x00009104, 0x00000001, 0x00000001, regs_within_LINE_KR_FRCNT_BER},
    {"TR_FRSENT", 0x00009105, 0x00000001, 0x00000002, regs_within_LINE_KR_TR_FRSENT},
    {"TR_ERRCNT", 0x00009107, 0x00000001, 0x00000001, regs_within_LINE_KR_TR_ERRCNT},
    {"AN_CFG0", 0x00000000, 0x00000001, 0x00000001, regs_within_LINE_KR_AN_CFG0},
    {"AN_STS0", 0x00000001, 0x00000001, 0x00000001, regs_within_LINE_KR_AN_STS0},
    {"LD_ADV", 0x00000010, 0x00000001, 0x00000003, regs_within_LINE_KR_LD_ADV},
    {"LP_BP", 0x00000013, 0x00000001, 0x00000004, regs_within_LINE_KR_LP_BP},
    {"LD_NP", 0x00000016, 0x00000001, 0x00000003, regs_within_LINE_KR_LD_NP},
    {"LP_NP", 0x00000019, 0x00000001, 0x00000004, regs_within_LINE_KR_LP_NP},
    {"BP_ETH_STS", 0x00000030, 0x00000001, 0x00000001, regs_within_LINE_KR_BP_ETH_STS},
    {"AN_CFG1", 0x00008000, 0x00000001, 0x00000001, regs_within_LINE_KR_AN_CFG1},
    {"AN_CFG2", 0x00008002, 0x00000001, 0x00000001, regs_within_LINE_KR_AN_CFG2},
    {"BL_TMR", 0x00008010, 0x00000001, 0x00000002, regs_within_LINE_KR_BL_TMR},
    {"AW_TMR", 0x00008012, 0x00000001, 0x00000002, regs_within_LINE_KR_AW_TMR},
    {"LF_TMR", 0x00008014, 0x00000001, 0x00000002, regs_within_LINE_KR_LF_TMR},
    {"FR_TMR", 0x00008016, 0x00000001, 0x00000002, regs_within_LINE_KR_FR_TMR},
    {"LP_TMR", 0x00008018, 0x00000001, 0x00000002, regs_within_LINE_KR_LP_TMR},
    {"TR_TMR", 0x0000801a, 0x00000001, 0x00000002, regs_within_LINE_KR_TR_TMR},
    {"PD_TMR", 0x0000801c, 0x00000001, 0x00000002, regs_within_LINE_KR_PD_TMR},
    {"RD_TMR", 0x0000801e, 0x00000001, 0x00000002, regs_within_LINE_KR_RD_TMR},
    {"WT_TMR", 0x00008024, 0x00000001, 0x00000001, regs_within_LINE_KR_WT_TMR},
    {"MW_TMR", 0x00008026, 0x00000001, 0x00000002, regs_within_LINE_KR_MW_TMR},
    {"GEN0_TMR", 0x00008028, 0x00000001, 0x00000002, regs_within_LINE_KR_GEN0_TMR},
    {"GEN1_TMR", 0x0000802a, 0x00000001, 0x00000002, regs_within_LINE_KR_GEN1_TMR},
#ifndef VTSS_RELEASE
    {"AN_HIST", 0x00008030, 0x00000001, 0x00000001, regs_within_LINE_KR_AN_HIST},
#endif
    {"AN_SM", 0x00008031, 0x00000001, 0x00000001, regs_within_LINE_KR_AN_SM},
    {"AN_STS1", 0x00008032, 0x00000001, 0x00000001, regs_within_LINE_KR_AN_STS1},
    {"FW_MSG", 0x00008040, 0x00000001, 0x00000001, regs_within_LINE_KR_FW_MSG},
    {"FW_REQ", 0x00008041, 0x00000001, 0x00000001, regs_within_LINE_KR_FW_REQ},
    {"IRQ_VEC", 0x00008042, 0x00000001, 0x00000002, regs_within_LINE_KR_IRQ_VEC},
    {"IRQ_MASK", 0x00008044, 0x00000001, 0x00000002, regs_within_LINE_KR_IRQ_MASK},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_HOST_INTR_CTRL_H_INTR_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"HOST_INTR_EN", 0x00000000, 0x00000002, 0x00000001},
    {"HOST_INTR_STAT", 0x00000002, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_HOST_INTR_CTRL[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"H_INTR_CTRL", 0x0000c010, 0x00000001, 0x00000004, regs_within_HOST_INTR_CTRL_H_INTR_CTRL},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_LINE_INTR_CTRL_L_INTR_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LINE_INTR_EN", 0x00000000, 0x00000002, 0x00000001},
    {"LINE_INTR_STAT", 0x00000002, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_LINE_INTR_CTRL[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"L_INTR_CTRL", 0x0000c010, 0x00000001, 0x00000004, regs_within_LINE_INTR_CTRL_L_INTR_CTRL},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_HOST_SLICE_HOST_SLICE_SOFTWARE_RESET[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"HOST_SD25G_RESET", 0x00000000, 0x00000001, 0x00000001},
    {"HOST_KR_RESET", 0x00000001, 0x00000001, 0x00000001},
    {"HOST_PCS1G_RESET", 0x00000002, 0x00000001, 0x00000001},
    {"HOST_PCS25G_RESET", 0x00000003, 0x00000001, 0x00000001},
    {"HOST_XC_RESET", 0x00000004, 0x00000001, 0x00000001},
    {"XGMII_H2L_RA_FIFO_EGR_RST", 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_SLICE_HOST_PMA_PCS_LPBK[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"L2_LPBK", 0x00000000, 0x00000001, 0x00000001},
    {"L3P_LPBK", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_SLICE_SERDES_LOS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SERDES_LOS", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_SLICE_PKTBIST_DATAPATH_CONTROL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DATAPATH_CONTROL", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_SLICE_SPARE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SPARE_RW_0", 0x00000000, 0x00000001, 0x00000001},
    {"SPARE_RW_1", 0x00000001, 0x00000001, 0x00000001},
    {"SPARE_RW_2", 0x00000002, 0x00000001, 0x00000001},
    {"SPARE_RW_3", 0x00000003, 0x00000001, 0x00000001},
    {"SPARE_RO_0", 0x00000004, 0x00000001, 0x00000001},
    {"SPARE_RO_1", 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_HOST_SLICE[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"HOST_SLICE_SOFTWARE_RESET", 0x00010200, 0x00000001, 0x00000006, regs_within_HOST_SLICE_HOST_SLICE_SOFTWARE_RESET},
    {"HOST_PMA_PCS_LPBK", 0x00010206, 0x00000001, 0x00000002, regs_within_HOST_SLICE_HOST_PMA_PCS_LPBK},
    {"SERDES_LOS", 0x00010208, 0x00000001, 0x00000001, regs_within_HOST_SLICE_SERDES_LOS},
    {"PKTBIST_DATAPATH_CONTROL", 0x00010209, 0x00000001, 0x00000001, regs_within_HOST_SLICE_PKTBIST_DATAPATH_CONTROL},
    {"SPARE", 0x00010210, 0x00000001, 0x00000006, regs_within_HOST_SLICE_SPARE},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_LINE_SLICE_LINE_SLICE_BLOCK_SOFTWARE_RESET[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LINE_SD25G_RESET", 0x00000000, 0x00000001, 0x00000001},
    {"LINE_KR_RESET", 0x00000001, 0x00000001, 0x00000001},
    {"LINE_PCS1G_RESET", 0x00000002, 0x00000001, 0x00000001},
    {"LINE_PCS25G_RESET", 0x00000003, 0x00000001, 0x00000001},
    {"LINE_XC_RESET", 0x00000004, 0x00000001, 0x00000001},
    {"MISC_BLOCKS_RESET", 0x00000005, 0x00000001, 0x00000001},
    {"LINE_MACSEC_RESET", 0x00000006, 0x00000001, 0x00000001},
    {"LINE_IP1588_RESET", 0x00000007, 0x00000001, 0x00000001},
    {"LINE_FIFO_RESET", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_SLICE_LINE_PMA_PCS_LPBK[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"H2_LPBK", 0x00000000, 0x00000001, 0x00000001},
    {"H3P_LPBK", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_SLICE_LINE_LED_AND_SERDES_LOS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SERDES_LOS", 0x00000000, 0x00000001, 0x00000001},
    {"LED_CONTROL", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_SLICE_H2L_RA_FIFO_INT_MASK[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"H2L_RA_FIFO_INT_MASK", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_SLICE_H2L_RA_FIFO_INFO[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"H2L_RA_FIFO_STATUS", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_SLICE_H2L_RA_FIFO_IDLE_INFO[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"H2L_RA_FIFO_IDLE_ADD_COUNT", 0x00000000, 0x00000001, 0x00000001},
    {"H2L_RA_FIFO_IDLE_DROP_COUNT", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_SLICE_L2H_RA_FIFO_INT_MASK[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"L2H_RA_FIFO_INT_MASK", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_SLICE_L2H_RA_FIFO_INFO[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"L2H_RA_FIFO_STATUS", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_SLICE_L2H_RA_FIFO_IDLE_INFO[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"L2H_RA_FIFO_IDLE_ADD_COUNT", 0x00000000, 0x00000001, 0x00000001},
    {"L2H_RA_FIFO_IDLE_DROP_COUNT", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_SLICE_LINE_CORE_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SLICE_CONFIG", 0x00000000, 0x00000001, 0x00000001},
    {"DUMMY_SECTAG_INS_PATTERN_0", 0x00000001, 0x00000001, 0x00000001},
    {"DUMMY_SECTAG_INS_PATTERN_1", 0x00000002, 0x00000001, 0x00000001},
    {"DUMMY_SECTAG_INS_PATTERN_2", 0x00000003, 0x00000001, 0x00000001},
    {"DUMMY_SECTAG_INS_PATTERN_3", 0x00000004, 0x00000001, 0x00000001},
    {"DUMMY_SECTAG_INS_PATTERN_4", 0x00000005, 0x00000001, 0x00000001},
    {"DUMMY_SECTAG_INS_PATTERN_5", 0x00000006, 0x00000001, 0x00000001},
    {"DUMMY_SECTAG_INS_PATTERN_6", 0x00000007, 0x00000001, 0x00000001},
    {"DUMMY_SECTAG_INS_PATTERN_7", 0x00000008, 0x00000001, 0x00000001},
    {"DUMMY_ICV_INS_PATTERN_0", 0x00000009, 0x00000001, 0x00000001},
    {"DUMMY_ICV_INS_PATTERN_1", 0x0000000a, 0x00000001, 0x00000001},
    {"DUMMY_ICV_INS_PATTERN_2", 0x0000000b, 0x00000001, 0x00000001},
    {"DUMMY_ICV_INS_PATTERN_3", 0x0000000c, 0x00000001, 0x00000001},
    {"DUMMY_ICV_INS_PATTERN_4", 0x0000000d, 0x00000001, 0x00000001},
    {"DUMMY_ICV_INS_PATTERN_5", 0x0000000e, 0x00000001, 0x00000001},
    {"DUMMY_ICV_INS_PATTERN_6", 0x0000000f, 0x00000001, 0x00000001},
    {"DUMMY_ICV_INS_PATTERN_7", 0x00000010, 0x00000001, 0x00000001},
    {"RM_DUMMY_PATTERN0_0", 0x00000011, 0x00000001, 0x00000001},
    {"RM_DUMMY_PATTERN0_1", 0x00000012, 0x00000001, 0x00000001},
    {"RM_DUMMY_PATTERN1_0", 0x00000013, 0x00000001, 0x00000001},
    {"RM_DUMMY_PATTERN1_1", 0x00000014, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_SLICE_LINE_CORE_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MACSEC_STATUS", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_SLICE_SPARE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SPARE_RW_0", 0x00000000, 0x00000001, 0x00000001},
    {"SPARE_RW_1", 0x00000001, 0x00000001, 0x00000001},
    {"SPARE_RW_2", 0x00000002, 0x00000001, 0x00000001},
    {"SPARE_RW_3", 0x00000003, 0x00000001, 0x00000001},
    {"SPARE_RO_0", 0x00000004, 0x00000001, 0x00000001},
    {"SPARE_RO_1", 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_SLICE_BIST1_REG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"BIST1_GO", 0x00000000, 0x00000001, 0x00000001},
    {"BIST1_STATUS", 0x00000001, 0x00000001, 0x00000001},
    {"BIST1_RESULT", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_LINE_SLICE[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"LINE_SLICE_BLOCK_SOFTWARE_RESET", 0x00008100, 0x00000001, 0x00000009, regs_within_LINE_SLICE_LINE_SLICE_BLOCK_SOFTWARE_RESET},
    {"LINE_PMA_PCS_LPBK", 0x00008110, 0x00000001, 0x00000002, regs_within_LINE_SLICE_LINE_PMA_PCS_LPBK},
    {"LINE_LED_AND_SERDES_LOS", 0x00008112, 0x00000001, 0x00000002, regs_within_LINE_SLICE_LINE_LED_AND_SERDES_LOS},
    {"H2L_RA_FIFO_INT_MASK", 0x00008114, 0x00000001, 0x00000001, regs_within_LINE_SLICE_H2L_RA_FIFO_INT_MASK},
    {"H2L_RA_FIFO_INFO", 0x00008115, 0x00000001, 0x00000001, regs_within_LINE_SLICE_H2L_RA_FIFO_INFO},
    {"H2L_RA_FIFO_IDLE_INFO", 0x0000810a, 0x00000001, 0x00000002, regs_within_LINE_SLICE_H2L_RA_FIFO_IDLE_INFO},
    {"L2H_RA_FIFO_INT_MASK", 0x00008118, 0x00000001, 0x00000001, regs_within_LINE_SLICE_L2H_RA_FIFO_INT_MASK},
    {"L2H_RA_FIFO_INFO", 0x00008119, 0x00000001, 0x00000001, regs_within_LINE_SLICE_L2H_RA_FIFO_INFO},
    {"L2H_RA_FIFO_IDLE_INFO", 0x0000810c, 0x00000001, 0x00000002, regs_within_LINE_SLICE_L2H_RA_FIFO_IDLE_INFO},
    {"LINE_CORE_CFG", 0x00008120, 0x00000001, 0x00000015, regs_within_LINE_SLICE_LINE_CORE_CFG},
    {"LINE_CORE_STATUS", 0x00008140, 0x00000001, 0x00000001, regs_within_LINE_SLICE_LINE_CORE_STATUS},
    {"SPARE", 0x00008150, 0x00000001, 0x00000006, regs_within_LINE_SLICE_SPARE},
    {"BIST1_REG", 0x00008160, 0x00000001, 0x00000003, regs_within_LINE_SLICE_BIST1_REG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_GEN_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GEN_CFG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_UPDATE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"UPDATE", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_GEN_PKTLEN[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GEN_PKTLEN", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_GEN_IPGLEN[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GEN_IPGLEN_LSW", 0x00000000, 0x00000001, 0x00000001},
    {"GEN_IPGLEN_MSW", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_GEN_TIME[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GEN_TIME", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_GEN_ETYPE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GEN_ETYPE", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_GEN_SA[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GEN_SA0", 0x00000000, 0x00000001, 0x00000001},
    {"GEN_SA1", 0x00000001, 0x00000001, 0x00000001},
    {"GEN_SA2", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_GEN_DA[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GEN_DA0", 0x00000000, 0x00000001, 0x00000001},
    {"GEN_DA1", 0x00000001, 0x00000001, 0x00000001},
    {"GEN_DA2", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_GEN_SENT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GEN_SENT_LSW", 0x00000000, 0x00000001, 0x00000001},
    {"GEN_SENT_MSW", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_TRANSPORT_SPECIFIC_MAJOR_SDOID[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TRANSPORT_SPECIFIC_MAJOR_SDOID", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_MINOR_VERSION_PTP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MINOR_VERSION", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_MINOR_SDOID[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MINOR_SDOID", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_MESSAGE_TYPE_SPECIFIC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MESSAGE_TYPE_SPECIFIC_HI", 0x00000000, 0x00000001, 0x00000001},
    {"MESSAGE_TYPE_SPECIFIC_LO", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_MON_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MON_CFG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_MON_RST[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MON_RST", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_MON_GOODCRC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MON_GOOD_LSW", 0x00000000, 0x00000001, 0x00000001},
    {"MON_GOOD_MSW", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_MON_BADCRC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MON_BAD_LSW", 0x00000000, 0x00000001, 0x00000001},
    {"MON_BAD_MSW", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_MON_FRAG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MON_FRAG_LSW", 0x00000000, 0x00000001, 0x00000001},
    {"MON_FRAG_MSW", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_MON_LFAULT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MON_LFAULT_LSW", 0x00000000, 0x00000001, 0x00000001},
    {"MON_LFAULT_MSW", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_MON_BER[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MON_BER_LSW", 0x00000000, 0x00000001, 0x00000001},
    {"MON_BER_MSW", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_MON_TSTAMP0[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MON_TSTAMP0_0", 0x00000000, 0x00000001, 0x00000001},
    {"MON_TSTAMP0_1", 0x00000001, 0x00000001, 0x00000001},
    {"MON_TSTAMP0_2", 0x00000002, 0x00000001, 0x00000001},
    {"MON_TSTAMP0_3", 0x00000003, 0x00000001, 0x00000001},
    {"MON_TSTAMP0_4", 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_MON_TSTAMP1[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MON_TSTAMP1_0", 0x00000000, 0x00000001, 0x00000001},
    {"MON_TSTAMP1_1", 0x00000001, 0x00000001, 0x00000001},
    {"MON_TSTAMP1_2", 0x00000002, 0x00000001, 0x00000001},
    {"MON_TSTAMP1_3", 0x00000003, 0x00000001, 0x00000001},
    {"MON_TSTAMP1_4", 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_MON_TSTAMP2[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MON_TSTAMP2_0", 0x00000000, 0x00000001, 0x00000001},
    {"MON_TSTAMP2_1", 0x00000001, 0x00000001, 0x00000001},
    {"MON_TSTAMP2_2", 0x00000002, 0x00000001, 0x00000001},
    {"MON_TSTAMP2_3", 0x00000003, 0x00000001, 0x00000001},
    {"MON_TSTAMP2_4", 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_MON_TSTAMP3[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MON_TSTAMP3_0", 0x00000000, 0x00000001, 0x00000001},
    {"MON_TSTAMP3_1", 0x00000001, 0x00000001, 0x00000001},
    {"MON_TSTAMP3_2", 0x00000002, 0x00000001, 0x00000001},
    {"MON_TSTAMP3_3", 0x00000003, 0x00000001, 0x00000001},
    {"MON_TSTAMP3_4", 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_MON_TSTAMP4[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MON_TSTAMP4_0", 0x00000000, 0x00000001, 0x00000001},
    {"MON_TSTAMP4_1", 0x00000001, 0x00000001, 0x00000001},
    {"MON_TSTAMP4_2", 0x00000002, 0x00000001, 0x00000001},
    {"MON_TSTAMP4_3", 0x00000003, 0x00000001, 0x00000001},
    {"MON_TSTAMP4_4", 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_MON_TSTAMP5[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MON_TSTAMP5_0", 0x00000000, 0x00000001, 0x00000001},
    {"MON_TSTAMP5_1", 0x00000001, 0x00000001, 0x00000001},
    {"MON_TSTAMP5_2", 0x00000002, 0x00000001, 0x00000001},
    {"MON_TSTAMP5_3", 0x00000003, 0x00000001, 0x00000001},
    {"MON_TSTAMP5_4", 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_MON_TSTAMP6[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MON_TSTAMP6_0", 0x00000000, 0x00000001, 0x00000001},
    {"MON_TSTAMP6_1", 0x00000001, 0x00000001, 0x00000001},
    {"MON_TSTAMP6_2", 0x00000002, 0x00000001, 0x00000001},
    {"MON_TSTAMP6_3", 0x00000003, 0x00000001, 0x00000001},
    {"MON_TSTAMP6_4", 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_MON_TSTAMP7[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MON_TSTAMP7_0", 0x00000000, 0x00000001, 0x00000001},
    {"MON_TSTAMP7_1", 0x00000001, 0x00000001, 0x00000001},
    {"MON_TSTAMP7_2", 0x00000002, 0x00000001, 0x00000001},
    {"MON_TSTAMP7_3", 0x00000003, 0x00000001, 0x00000001},
    {"MON_TSTAMP7_4", 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_MON_TSTAMP8[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MON_TSTAMP8_0", 0x00000000, 0x00000001, 0x00000001},
    {"MON_TSTAMP8_1", 0x00000001, 0x00000001, 0x00000001},
    {"MON_TSTAMP8_2", 0x00000002, 0x00000001, 0x00000001},
    {"MON_TSTAMP8_3", 0x00000003, 0x00000001, 0x00000001},
    {"MON_TSTAMP8_4", 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PKT_BIST_MON_TSTAMP9[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MON_TSTAMP9_0", 0x00000000, 0x00000001, 0x00000001},
    {"MON_TSTAMP9_1", 0x00000001, 0x00000001, 0x00000001},
    {"MON_TSTAMP9_2", 0x00000002, 0x00000001, 0x00000001},
    {"MON_TSTAMP9_3", 0x00000003, 0x00000001, 0x00000001},
    {"MON_TSTAMP9_4", 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_PKT_BIST[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"GEN_CFG", 0x0000e900, 0x00000001, 0x00000001, regs_within_PKT_BIST_GEN_CFG},
    {"UPDATE", 0x0000e901, 0x00000001, 0x00000001, regs_within_PKT_BIST_UPDATE},
    {"GEN_PKTLEN", 0x0000e902, 0x00000001, 0x00000001, regs_within_PKT_BIST_GEN_PKTLEN},
    {"GEN_IPGLEN", 0x0000e903, 0x00000001, 0x00000002, regs_within_PKT_BIST_GEN_IPGLEN},
    {"GEN_TIME", 0x0000e905, 0x00000001, 0x00000001, regs_within_PKT_BIST_GEN_TIME},
    {"GEN_ETYPE", 0x0000e906, 0x00000001, 0x00000001, regs_within_PKT_BIST_GEN_ETYPE},
    {"GEN_SA", 0x0000e907, 0x00000001, 0x00000003, regs_within_PKT_BIST_GEN_SA},
    {"GEN_DA", 0x0000e90a, 0x00000001, 0x00000003, regs_within_PKT_BIST_GEN_DA},
    {"GEN_SENT", 0x0000e90d, 0x00000001, 0x00000002, regs_within_PKT_BIST_GEN_SENT},
    {"TRANSPORT_SPECIFIC_MAJOR_SDOID", 0x0000e90f, 0x00000001, 0x00000001, regs_within_PKT_BIST_TRANSPORT_SPECIFIC_MAJOR_SDOID},
    {"MINOR_VERSION_PTP", 0x0000e910, 0x00000001, 0x00000001, regs_within_PKT_BIST_MINOR_VERSION_PTP},
    {"MINOR_SDOID", 0x0000e911, 0x00000001, 0x00000001, regs_within_PKT_BIST_MINOR_SDOID},
    {"MESSAGE_TYPE_SPECIFIC", 0x0000e912, 0x00000001, 0x00000002, regs_within_PKT_BIST_MESSAGE_TYPE_SPECIFIC},
    {"MON_CFG", 0x0000e914, 0x00000001, 0x00000001, regs_within_PKT_BIST_MON_CFG},
    {"MON_RST", 0x0000e915, 0x00000001, 0x00000001, regs_within_PKT_BIST_MON_RST},
    {"MON_GOODCRC", 0x0000e916, 0x00000001, 0x00000002, regs_within_PKT_BIST_MON_GOODCRC},
    {"MON_BADCRC", 0x0000e918, 0x00000001, 0x00000002, regs_within_PKT_BIST_MON_BADCRC},
    {"MON_FRAG", 0x0000e91a, 0x00000001, 0x00000002, regs_within_PKT_BIST_MON_FRAG},
    {"MON_LFAULT", 0x0000e91c, 0x00000001, 0x00000002, regs_within_PKT_BIST_MON_LFAULT},
    {"MON_BER", 0x0000e91e, 0x00000001, 0x00000002, regs_within_PKT_BIST_MON_BER},
    {"MON_TSTAMP0", 0x0000e920, 0x00000001, 0x00000005, regs_within_PKT_BIST_MON_TSTAMP0},
    {"MON_TSTAMP1", 0x0000e925, 0x00000001, 0x00000005, regs_within_PKT_BIST_MON_TSTAMP1},
    {"MON_TSTAMP2", 0x0000e92a, 0x00000001, 0x00000005, regs_within_PKT_BIST_MON_TSTAMP2},
    {"MON_TSTAMP3", 0x0000e92f, 0x00000001, 0x00000005, regs_within_PKT_BIST_MON_TSTAMP3},
    {"MON_TSTAMP4", 0x0000e934, 0x00000001, 0x00000005, regs_within_PKT_BIST_MON_TSTAMP4},
    {"MON_TSTAMP5", 0x0000e939, 0x00000001, 0x00000005, regs_within_PKT_BIST_MON_TSTAMP5},
    {"MON_TSTAMP6", 0x0000e93e, 0x00000001, 0x00000005, regs_within_PKT_BIST_MON_TSTAMP6},
    {"MON_TSTAMP7", 0x0000e943, 0x00000001, 0x00000005, regs_within_PKT_BIST_MON_TSTAMP7},
    {"MON_TSTAMP8", 0x0000e948, 0x00000001, 0x00000005, regs_within_PKT_BIST_MON_TSTAMP8},
    {"MON_TSTAMP9", 0x0000e94d, 0x00000001, 0x00000005, regs_within_PKT_BIST_MON_TSTAMP9},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_SFP_TWS_TWI_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TWI_CLIENT_ID", 0x00000000, 0x00000001, 0x00000001},
    {"TWI_PRESCALE", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SFP_TWS_TWI_WRITE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TWI_WRITE_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SFP_TWS_TWI_BUS_STAT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TWI_BUS_STATUS", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SFP_TWS_TWI_READ_ADDRESS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TWI_READ_ADDR", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SFP_TWS_TWI_READ_STATUS_AND_DATA[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TWI_READ_STATUS_DATA", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SFP_TWS_TWI_RESET_SEQUENCE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TWI_RESET_SEQ", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_SFP_TWS[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"TWI_CFG", 0x0000c000, 0x00000001, 0x00000002, regs_within_SFP_TWS_TWI_CFG},
    {"TWI_WRITE", 0x0000c002, 0x00000001, 0x00000001, regs_within_SFP_TWS_TWI_WRITE},
    {"TWI_BUS_STAT", 0x0000c003, 0x00000001, 0x00000001, regs_within_SFP_TWS_TWI_BUS_STAT},
    {"TWI_READ_ADDRESS", 0x0000c004, 0x00000001, 0x00000001, regs_within_SFP_TWS_TWI_READ_ADDRESS},
    {"TWI_READ_STATUS_AND_DATA", 0x0000c005, 0x00000001, 0x00000001, regs_within_SFP_TWS_TWI_READ_STATUS_AND_DATA},
    {"TWI_RESET_SEQUENCE", 0x0000c006, 0x00000001, 0x00000001, regs_within_SFP_TWS_TWI_RESET_SEQUENCE},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_IP_1588_TOP_CFG_STAT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INTERFACE_CTL", 0x00000000, 0x00000001, 0x00000001},
    {"ANALYZER_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"MODE_CTL", 0x00000002, 0x00000001, 0x00000001},
    {"VERSION_CODE", 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_INGR_IP_1588_CFG_STAT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR_CFG_OPERATION_MODE", 0x00000000, 0x00000001, 0x00000001},
    {"INGR_INT_STATUS", 0x00000001, 0x00000001, 0x00000001},
    {"INGR_INT_MASK", 0x00000002, 0x00000001, 0x00000001},
    {"INGR_CFG_STALL_LATENCY", 0x00000003, 0x00000001, 0x00000001},
    {"INGR_CFG_STALL_LATENCY_SNS", 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_INGR_IP_1588_TSP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR_TSP_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"INGR_TSP_STAT", 0x00000001, 0x00000001, 0x00000001},
    {"INGR_LOCAL_LATENCY", 0x00000002, 0x00000001, 0x00000001},
    {"INGR_LOCAL_LATENCY_SNS", 0x00000003, 0x00000001, 0x00000001},
    {"INGR_PCS_SERDES_LOCAL_LATENCY", 0x00000004, 0x00000001, 0x00000001},
    {"INGR_PCS_SERDES_LOCAL_LATENCY_SNS", 0x00000005, 0x00000001, 0x00000001},
    {"INGR_PATH_DELAY", 0x00000006, 0x00000001, 0x00000001},
    {"INGR_PATH_DELAY_SNS", 0x00000007, 0x00000001, 0x00000001},
    {"INGR_DELAY_ASYMMETRY", 0x00000008, 0x00000001, 0x00000001},
    {"INGR_RADPT_DROP_IDLE_PIF", 0x00000009, 0x00000001, 0x00000001},
    {"INGR_RADPT_DROP_IDLE_XIF", 0x0000000a, 0x00000001, 0x00000001},
    {"INGR_CWM_EARLY_NOTICE_PIF", 0x0000000b, 0x00000001, 0x00000001},
    {"INGR_CWM_EARLY_NOTICE_XIF", 0x0000000c, 0x00000001, 0x00000001},
    {"INGR_PCS_PREDICTOR_CTRL", 0x0000000d, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_INGR_IP_1588_DF[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR_DF_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_INGR_IP_1588_TSFIFO[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR_TSFIFO_CSR", 0x00000000, 0x00000001, 0x00000001},
    {"INGR_TSFIFO_0", 0x00000001, 0x00000001, 0x00000001},
    {"INGR_TSFIFO_1", 0x00000002, 0x00000001, 0x00000001},
    {"INGR_TSFIFO_2", 0x00000003, 0x00000001, 0x00000001},
    {"INGR_TSFIFO_3", 0x00000004, 0x00000001, 0x00000001},
    {"INGR_TSFIFO_4", 0x00000005, 0x00000001, 0x00000001},
    {"INGR_TSFIFO_5", 0x00000006, 0x00000001, 0x00000001},
    {"INGR_TSFIFO_6", 0x00000007, 0x00000001, 0x00000001},
    {"INGR_TSFIFO_7", 0x00000008, 0x00000001, 0x00000001},
    {"INGR_TSFIFO_8", 0x00000009, 0x00000001, 0x00000001},
    {"INGR_TSFIFO_9", 0x0000000a, 0x00000001, 0x00000001},
    {"INGR_TSFIFO_DROP_CNT", 0x0000000b, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_INGR_IP_1588_RW[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR_RW_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"INGR_RW_MODFRM_CNT", 0x00000001, 0x00000001, 0x00000001},
    {"INGR_RW_FCS_ERR_CNT", 0x00000002, 0x00000001, 0x00000001},
    {"INGR_RW_PREAMBLE_ERR_CNT", 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_INGR_IP_ANALYZER_STAT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR_ANALYZER_MOD_FRAMES_CNT", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_INGR_IP_1588_MCH[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR_MCH_CRC_ERR_CNTR", 0x00000000, 0x00000001, 0x00000001},
    {"INGR_MCH_EXTTY_MISMATCH_CNTR", 0x00000001, 0x00000001, 0x00000001},
    {"INGR_MCH_CTRL", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_INGR_IP_1588_RSFEC_PHAD[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR_RSFEC_PHAD_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"INGR_RSFEC_PHAD_CYC_TIME", 0x00000001, 0x00000001, 0x00000001},
    {"INGR_RSFEC_PHAD_ERR_STATE", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_INGR_IP_1588_SOF_PHAD[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR_SOF_PHAD_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"INGR_SOF_PHAD_CYC_TIME", 0x00000001, 0x00000001, 0x00000001},
    {"INGR_SOF_PHAD_ERR_STATE", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_EGR_IP_1588_CFG_STAT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR_CFG_OPERATION_MODE", 0x00000000, 0x00000001, 0x00000001},
    {"EGR_INT_STATUS", 0x00000001, 0x00000001, 0x00000001},
    {"EGR_INT_MASK", 0x00000002, 0x00000001, 0x00000001},
    {"EGR_CFG_STALL_LATENCY", 0x00000003, 0x00000001, 0x00000001},
    {"EGR_CFG_STALL_LATENCY_SNS", 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_EGR_IP_1588_TSP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR_TSP_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"EGR_TSP_STAT", 0x00000001, 0x00000001, 0x00000001},
    {"EGR_LOCAL_LATENCY", 0x00000002, 0x00000001, 0x00000001},
    {"EGR_LOCAL_LATENCY_SNS", 0x00000003, 0x00000001, 0x00000001},
    {"EGR_PCS_SERDES_LOCAL_LATENCY", 0x00000004, 0x00000001, 0x00000001},
    {"EGR_PCS_SERDES_LOCAL_LATENCY_SNS", 0x00000005, 0x00000001, 0x00000001},
    {"EGR_PATH_DELAY", 0x00000006, 0x00000001, 0x00000001},
    {"EGR_PATH_DELAY_SNS", 0x00000007, 0x00000001, 0x00000001},
    {"EGR_DELAY_ASYMMETRY", 0x00000008, 0x00000001, 0x00000001},
    {"EGR_RADPT_DROP_IDLE_PIF", 0x00000009, 0x00000001, 0x00000001},
    {"EGR_RADPT_DROP_IDLE_XIF", 0x0000000a, 0x00000001, 0x00000001},
    {"EGR_CWM_EARLY_NOTICE_PIF", 0x0000000b, 0x00000001, 0x00000001},
    {"EGR_CWM_EARLY_NOTICE_XIF", 0x0000000c, 0x00000001, 0x00000001},
    {"EGR_PCS_PREDICTOR_CTRL", 0x0000000d, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_EGR_IP_1588_DF[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR_DF_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_EGR_IP_1588_TSFIFO[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR_TSFIFO_CSR", 0x00000000, 0x00000001, 0x00000001},
    {"EGR_TSFIFO_0", 0x00000001, 0x00000001, 0x00000001},
    {"EGR_TSFIFO_1", 0x00000002, 0x00000001, 0x00000001},
    {"EGR_TSFIFO_2", 0x00000003, 0x00000001, 0x00000001},
    {"EGR_TSFIFO_3", 0x00000004, 0x00000001, 0x00000001},
    {"EGR_TSFIFO_4", 0x00000005, 0x00000001, 0x00000001},
    {"EGR_TSFIFO_5", 0x00000006, 0x00000001, 0x00000001},
    {"EGR_TSFIFO_6", 0x00000007, 0x00000001, 0x00000001},
    {"EGR_TSFIFO_7", 0x00000008, 0x00000001, 0x00000001},
    {"EGR_TSFIFO_8", 0x00000009, 0x00000001, 0x00000001},
    {"EGR_TSFIFO_9", 0x0000000a, 0x00000001, 0x00000001},
    {"EGR_TSFIFO_DROP_CNT", 0x0000000b, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_EGR_IP_1588_RW[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR_RW_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"EGR_RW_MODFRM_CNT", 0x00000001, 0x00000001, 0x00000001},
    {"EGR_RW_FCS_ERR_CNT", 0x00000002, 0x00000001, 0x00000001},
    {"EGR_RW_PREAMBLE_ERR_CNT", 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_EGR_IP_ANALYZER_STAT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR_ANALYZER_MOD_FRAMES_CNT", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_EGR_IP_1588_MCH[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR_MCH_CRC_ERR_CNTR", 0x00000000, 0x00000001, 0x00000001},
    {"EGR_MCH_EXTTY_MISMATCH_CNTR", 0x00000001, 0x00000001, 0x00000001},
    {"EGR_MCH_CTRL", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_EGR_IP_1588_RSFEC_PHAD[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR_RSFEC_PHAD_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"EGR_RSFEC_PHAD_CYC_TIME", 0x00000001, 0x00000001, 0x00000001},
    {"EGR_RSFEC_PHAD_ERR_STATE", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_EGR_IP_1588_SOF_PHAD[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR_SOF_PHAD_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"EGR_SOF_PHAD_CYC_TIME", 0x00000001, 0x00000001, 0x00000001},
    {"EGR_SOF_PHAD_ERR_STATE", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_INGR_IP_1588_DEBUG_REGISTERS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR_ANA_CMD_FIFO_DATA1", 0x00000000, 0x00000001, 0x00000001},
    {"INGR_ANA_CMD_FIFO_DATA2", 0x00000001, 0x00000001, 0x00000001},
    {"INGR_ANALYZER_STATUS", 0x00000002, 0x00000001, 0x00000001},
    {"INGR_PREDICTOR_VAR_DELAY1", 0x00000003, 0x00000001, 0x00000001},
    {"INGR_PREDICTOR_VAR_DELAY2", 0x00000004, 0x00000001, 0x00000001},
    {"INGR_PREDICTOR_VAR_DELAY3", 0x00000005, 0x00000001, 0x00000001},
    {"INGR_REWRITER_OPMODE", 0x00000006, 0x00000001, 0x00000001},
    {"INGR_CORRECTION_FIELD_VLD", 0x00000007, 0x00000001, 0x00000001},
    {"INGR_CORRECTION_FIELD_VALUE1", 0x00000008, 0x00000001, 0x00000001},
    {"INGR_CORRECTION_FIELD_VALUE2", 0x00000009, 0x00000001, 0x00000001},
    {"INGR_TIMESTAMP_VALUE1", 0x0000000a, 0x00000001, 0x00000001},
    {"INGR_TIMESTAMP_VALUE2", 0x0000000b, 0x00000001, 0x00000001},
    {"INGR_TIMESTAMP_VALUE3", 0x0000000c, 0x00000001, 0x00000001},
    {"INGR_LTC_READ", 0x0000000d, 0x00000001, 0x00000001},
    {"INGR_LTC_SEC_H", 0x0000000e, 0x00000001, 0x00000001},
    {"INGR_LTC_SEC_L", 0x0000000f, 0x00000001, 0x00000001},
    {"INGR_LTC_NS", 0x00000010, 0x00000001, 0x00000001},
    {"INGR_LTC_SNS", 0x00000011, 0x00000001, 0x00000001},
    {"INGR_EXTRACTED_CF1", 0x00000012, 0x00000001, 0x00000001},
    {"INGR_EXTRACTED_CF2", 0x00000013, 0x00000001, 0x00000001},
    {"INGR_STORED_TIMESTAMP", 0x00000014, 0x00000001, 0x00000001},
    {"INGR_ACTIVE_TIMESTAMP0", 0x00000015, 0x00000001, 0x00000001},
    {"INGR_ACTIVE_TIMESTAMP1", 0x00000016, 0x00000001, 0x00000001},
    {"INGR_ACTIVE_TIMESTAMP2", 0x00000017, 0x00000001, 0x00000001},
    {"INGR_PREDICTOR_VALUES", 0x00000018, 0x00000001, 0x00000001},
    {"INGR_REWRITER_FSM_STATES", 0x00000019, 0x00000001, 0x00000001},
    {"INGR_SW_POP_FIFO", 0x0000001a, 0x00000001, 0x00000001},
    {"INGR_ANA_CMD_FIFO_DATA_OUT1", 0x0000001b, 0x00000001, 0x00000001},
    {"INGR_ANA_CMD_FIFO_DATA_OUT2", 0x0000001c, 0x00000001, 0x00000001},
    {"INGR_TIMESTAMP_VALUE_FIFO_INPUT1", 0x0000001d, 0x00000001, 0x00000001},
    {"INGR_TIMESTAMP_VALUE_FIFO_INPUT2", 0x0000001e, 0x00000001, 0x00000001},
    {"INGR_TIMESTAMP_VALUE_FIFO_INPUT3", 0x0000001f, 0x00000001, 0x00000001},
    {"INGR_CORRECTION_FIELD_VLD_FIFO_INPUT", 0x00000020, 0x00000001, 0x00000001},
    {"INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1", 0x00000021, 0x00000001, 0x00000001},
    {"INGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2", 0x00000022, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PROC_EGR_IP_1588_DEBUG_REGISTERS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR_ANA_CMD_FIFO_DATA1", 0x00000000, 0x00000001, 0x00000001},
    {"EGR_ANA_CMD_FIFO_DATA2", 0x00000001, 0x00000001, 0x00000001},
    {"EGR_ANALYZER_STATUS", 0x00000002, 0x00000001, 0x00000001},
    {"EGR_PREDICTOR_VAR_DELAY1", 0x00000003, 0x00000001, 0x00000001},
    {"EGR_PREDICTOR_VAR_DELAY2", 0x00000004, 0x00000001, 0x00000001},
    {"EGR_PREDICTOR_VAR_DELAY3", 0x00000005, 0x00000001, 0x00000001},
    {"EGR_REWRITER_OPMODE", 0x00000006, 0x00000001, 0x00000001},
    {"EGR_CORRECTION_FIELD_VLD", 0x00000007, 0x00000001, 0x00000001},
    {"EGR_CORRECTION_FIELD_VALUE1", 0x00000008, 0x00000001, 0x00000001},
    {"EGR_CORRECTION_FIELD_VALUE2", 0x00000009, 0x00000001, 0x00000001},
    {"EGR_TIMESTAMP_VALUE1", 0x0000000a, 0x00000001, 0x00000001},
    {"EGR_TIMESTAMP_VALUE2", 0x0000000b, 0x00000001, 0x00000001},
    {"EGR_TIMESTAMP_VALUE3", 0x0000000c, 0x00000001, 0x00000001},
    {"EGR_LTC_READ", 0x0000000d, 0x00000001, 0x00000001},
    {"EGR_LTC_SEC_H", 0x0000000e, 0x00000001, 0x00000001},
    {"EGR_LTC_SEC_L", 0x0000000f, 0x00000001, 0x00000001},
    {"EGR_LTC_NS", 0x00000010, 0x00000001, 0x00000001},
    {"EGR_LTC_SNS", 0x00000011, 0x00000001, 0x00000001},
    {"EGR_EXTRACTED_CF1", 0x00000012, 0x00000001, 0x00000001},
    {"EGR_EXTRACTED_CF2", 0x00000013, 0x00000001, 0x00000001},
    {"EGR_STORED_TIMESTAMP", 0x00000014, 0x00000001, 0x00000001},
    {"EGR_ACTIVE_TIMESTAMP0", 0x00000015, 0x00000001, 0x00000001},
    {"EGR_ACTIVE_TIMESTAMP1", 0x00000016, 0x00000001, 0x00000001},
    {"EGR_ACTIVE_TIMESTAMP2", 0x00000017, 0x00000001, 0x00000001},
    {"EGR_PREDICTOR_VALUES", 0x00000018, 0x00000001, 0x00000001},
    {"EGR_REWRITER_FSM_STATES", 0x00000019, 0x00000001, 0x00000001},
    {"EGR_SW_POP_FIFO", 0x0000001a, 0x00000001, 0x00000001},
    {"EGR_ANA_CMD_FIFO_DATA_OUT1", 0x0000001b, 0x00000001, 0x00000001},
    {"EGR_ANA_CMD_FIFO_DATA_OUT2", 0x0000001c, 0x00000001, 0x00000001},
    {"EGR_TIMESTAMP_VALUE_FIFO_INPUT1", 0x0000001d, 0x00000001, 0x00000001},
    {"EGR_TIMESTAMP_VALUE_FIFO_INPUT2", 0x0000001e, 0x00000001, 0x00000001},
    {"EGR_TIMESTAMP_VALUE_FIFO_INPUT3", 0x0000001f, 0x00000001, 0x00000001},
    {"EGR_CORRECTION_FIELD_VLD_FIFO_INPUT", 0x00000020, 0x00000001, 0x00000001},
    {"EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT1", 0x00000021, 0x00000001, 0x00000001},
    {"EGR_CORRECTION_FIELD_VALUE_FIFO_INPUT2", 0x00000022, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_PTP_PROC[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"IP_1588_TOP_CFG_STAT", 0x00009000, 0x00000001, 0x00000010, regs_within_PTP_PROC_IP_1588_TOP_CFG_STAT},
    {"INGR_IP_1588_CFG_STAT", 0x00009020, 0x00000001, 0x00000008, regs_within_PTP_PROC_INGR_IP_1588_CFG_STAT},
    {"INGR_IP_1588_TSP", 0x00009028, 0x00000001, 0x0000000e, regs_within_PTP_PROC_INGR_IP_1588_TSP},
    {"INGR_IP_1588_DF", 0x00009036, 0x00000001, 0x00000001, regs_within_PTP_PROC_INGR_IP_1588_DF},
    {"INGR_IP_1588_TSFIFO", 0x00009037, 0x00000001, 0x0000000c, regs_within_PTP_PROC_INGR_IP_1588_TSFIFO},
    {"INGR_IP_1588_RW", 0x00009043, 0x00000001, 0x00000008, regs_within_PTP_PROC_INGR_IP_1588_RW},
    {"INGR_IP_ANALYZER_STAT", 0x0000904b, 0x00000001, 0x00000001, regs_within_PTP_PROC_INGR_IP_ANALYZER_STAT},
    {"INGR_IP_1588_MCH", 0x0000904c, 0x00000001, 0x00000003, regs_within_PTP_PROC_INGR_IP_1588_MCH},
    {"INGR_IP_1588_RSFEC_PHAD", 0x0000904f, 0x00000001, 0x00000003, regs_within_PTP_PROC_INGR_IP_1588_RSFEC_PHAD},
    {"INGR_IP_1588_SOF_PHAD", 0x00009052, 0x00000001, 0x00000003, regs_within_PTP_PROC_INGR_IP_1588_SOF_PHAD},
    {"EGR_IP_1588_CFG_STAT", 0x00009055, 0x00000001, 0x00000008, regs_within_PTP_PROC_EGR_IP_1588_CFG_STAT},
    {"EGR_IP_1588_TSP", 0x0000905d, 0x00000001, 0x0000000e, regs_within_PTP_PROC_EGR_IP_1588_TSP},
    {"EGR_IP_1588_DF", 0x0000906b, 0x00000001, 0x00000001, regs_within_PTP_PROC_EGR_IP_1588_DF},
    {"EGR_IP_1588_TSFIFO", 0x0000906c, 0x00000001, 0x0000000c, regs_within_PTP_PROC_EGR_IP_1588_TSFIFO},
    {"EGR_IP_1588_RW", 0x00009078, 0x00000001, 0x00000008, regs_within_PTP_PROC_EGR_IP_1588_RW},
    {"EGR_IP_ANALYZER_STAT", 0x00009080, 0x00000001, 0x00000001, regs_within_PTP_PROC_EGR_IP_ANALYZER_STAT},
    {"EGR_IP_1588_MCH", 0x00009081, 0x00000001, 0x00000003, regs_within_PTP_PROC_EGR_IP_1588_MCH},
    {"EGR_IP_1588_RSFEC_PHAD", 0x00009084, 0x00000001, 0x00000003, regs_within_PTP_PROC_EGR_IP_1588_RSFEC_PHAD},
    {"EGR_IP_1588_SOF_PHAD", 0x00009087, 0x00000001, 0x00000003, regs_within_PTP_PROC_EGR_IP_1588_SOF_PHAD},
#ifndef VTSS_RELEASE
    {"INGR_IP_1588_DEBUG_REGISTERS", 0x000090a4, 0x00000001, 0x00000023, regs_within_PTP_PROC_INGR_IP_1588_DEBUG_REGISTERS},
#endif
#ifndef VTSS_RELEASE
    {"EGR_IP_1588_DEBUG_REGISTERS", 0x000090c7, 0x00000001, 0x00000023, regs_within_PTP_PROC_EGR_IP_1588_DEBUG_REGISTERS},
#endif
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_INGR_CFG_INGR0_ETH1_NXT_PROTOCOL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR0_ETH1_NXT_PROTOCOL_REG", 0x00000000, 0x00000001, 0x00000001},
    {"INGR0_ETH1_VLAN_TPID_CFG", 0x00000001, 0x00000001, 0x00000001},
    {"INGR0_ETH1_TAG_MODE", 0x00000002, 0x00000001, 0x00000001},
    {"INGR0_ETH1_ETYPE_MATCH", 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_INGR_CFG_INGR0_ETH1_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR0_ETH1_FLOW_ENABLE", 0x00000000, 0x00000001, 0x00000001},
    {"INGR0_ETH1_MATCH_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"INGR0_ETH1_ADDR_MATCH_1", 0x00000002, 0x00000001, 0x00000001},
    {"INGR0_ETH1_ADDR_MATCH_2", 0x00000003, 0x00000001, 0x00000001},
    {"INGR0_ETH1_VLAN_TAG_RANGE_I_TAG", 0x00000004, 0x00000001, 0x00000001},
    {"INGR0_ETH1_VLAN_TAG1", 0x00000005, 0x00000001, 0x00000001},
    {"INGR0_ETH1_VLAN_TAG2_I_TAG", 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_INGR_CFG_INGR0_ETH2_NXT_PROTOCOL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR0_ETH2_NXT_PROTOCOL_REG", 0x00000000, 0x00000001, 0x00000001},
    {"INGR0_ETH2_VLAN_TPID_CFG", 0x00000001, 0x00000001, 0x00000001},
    {"INGR0_ETH2_ETYPE_MATCH", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_INGR_CFG_INGR0_ETH2_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR0_ETH2_FLOW_ENABLE", 0x00000000, 0x00000001, 0x00000001},
    {"INGR0_ETH2_MATCH_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"INGR0_ETH2_ADDR_MATCH_1", 0x00000002, 0x00000001, 0x00000001},
    {"INGR0_ETH2_ADDR_MATCH_2", 0x00000003, 0x00000001, 0x00000001},
    {"INGR0_ETH2_VLAN_TAG_RANGE_I_TAG", 0x00000004, 0x00000001, 0x00000001},
    {"INGR0_ETH2_VLAN_TAG1", 0x00000005, 0x00000001, 0x00000001},
    {"INGR0_ETH2_VLAN_TAG2_I_TAG", 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_INGR_CFG_INGR0_MPLS_NXT_COMPARATOR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR0_MPLS_NXT_COMPARATOR", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_INGR_CFG_INGR0_MPLS_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR0_MPLS_FLOW_CONTROL", 0x00000000, 0x00000001, 0x00000001},
    {"INGR0_MPLS_FLOW_MATCH_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"INGR0_MPLS_LABEL_RANGE_LOWER_0", 0x00000002, 0x00000001, 0x00000001},
    {"INGR0_MPLS_LABEL_RANGE_UPPER_0", 0x00000003, 0x00000001, 0x00000001},
    {"INGR0_MPLS_LABEL_RANGE_LOWER_1", 0x00000004, 0x00000001, 0x00000001},
    {"INGR0_MPLS_LABEL_RANGE_UPPER_1", 0x00000005, 0x00000001, 0x00000001},
    {"INGR0_MPLS_LABEL_RANGE_LOWER_2", 0x00000006, 0x00000001, 0x00000001},
    {"INGR0_MPLS_LABEL_RANGE_UPPER_2", 0x00000007, 0x00000001, 0x00000001},
    {"INGR0_MPLS_LABEL_RANGE_LOWER_3", 0x00000008, 0x00000001, 0x00000001},
    {"INGR0_MPLS_LABEL_RANGE_UPPER_3", 0x00000009, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_INGR_CFG_INGR0_IP1_NXT_PROTOCOL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR0_IP1_NXT_COMPARATOR", 0x00000000, 0x00000001, 0x00000001},
    {"INGR0_IP1_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"INGR0_IP1_PROT_MATCH_1", 0x00000002, 0x00000001, 0x00000001},
    {"INGR0_IP1_PROT_MATCH_2_UPPER", 0x00000003, 0x00000001, 0x00000001},
    {"INGR0_IP1_PROT_MATCH_2_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"INGR0_IP1_PROT_MASK_2_UPPER", 0x00000005, 0x00000001, 0x00000001},
    {"INGR0_IP1_PROT_MASK_2_LOWER", 0x00000006, 0x00000001, 0x00000001},
    {"INGR0_IP1_PROT_OFFSET_2", 0x00000007, 0x00000001, 0x00000001},
    {"INGR0_IP1_UDP_CHKSUM_CFG", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_INGR_CFG_INGR0_IP1_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR0_IP1_FLOW_ENA", 0x00000000, 0x00000001, 0x00000001},
    {"INGR0_IP1_FLOW_MATCH_UPPER", 0x00000001, 0x00000001, 0x00000001},
    {"INGR0_IP1_FLOW_MATCH_UPPER_MID", 0x00000002, 0x00000001, 0x00000001},
    {"INGR0_IP1_FLOW_MATCH_LOWER_MID", 0x00000003, 0x00000001, 0x00000001},
    {"INGR0_IP1_FLOW_MATCH_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"INGR0_IP1_FLOW_MASK_UPPER", 0x00000005, 0x00000001, 0x00000001},
    {"INGR0_IP1_FLOW_MASK_UPPER_MID", 0x00000006, 0x00000001, 0x00000001},
    {"INGR0_IP1_FLOW_MASK_LOWER_MID", 0x00000007, 0x00000001, 0x00000001},
    {"INGR0_IP1_FLOW_MASK_LOWER", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_INGR_CFG_INGR0_IP2_NXT_PROTOCOL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR0_IP2_NXT_COMPARATOR", 0x00000000, 0x00000001, 0x00000001},
    {"INGR0_IP2_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"INGR0_IP2_PROT_MATCH_1", 0x00000002, 0x00000001, 0x00000001},
    {"INGR0_IP2_PROT_MATCH_2_UPPER", 0x00000003, 0x00000001, 0x00000001},
    {"INGR0_IP2_PROT_MATCH_2_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"INGR0_IP2_PROT_MASK_2_UPPER", 0x00000005, 0x00000001, 0x00000001},
    {"INGR0_IP2_PROT_MASK_2_LOWER", 0x00000006, 0x00000001, 0x00000001},
    {"INGR0_IP2_PROT_OFFSET_2", 0x00000007, 0x00000001, 0x00000001},
    {"INGR0_IP2_UDP_CHKSUM_CFG", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_INGR_CFG_INGR0_IP2_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR0_IP2_FLOW_ENA", 0x00000000, 0x00000001, 0x00000001},
    {"INGR0_IP2_FLOW_MATCH_UPPER", 0x00000001, 0x00000001, 0x00000001},
    {"INGR0_IP2_FLOW_MATCH_UPPER_MID", 0x00000002, 0x00000001, 0x00000001},
    {"INGR0_IP2_FLOW_MATCH_LOWER_MID", 0x00000003, 0x00000001, 0x00000001},
    {"INGR0_IP2_FLOW_MATCH_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"INGR0_IP2_FLOW_MASK_UPPER", 0x00000005, 0x00000001, 0x00000001},
    {"INGR0_IP2_FLOW_MASK_UPPER_MID", 0x00000006, 0x00000001, 0x00000001},
    {"INGR0_IP2_FLOW_MASK_LOWER_MID", 0x00000007, 0x00000001, 0x00000001},
    {"INGR0_IP2_FLOW_MASK_LOWER", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_INGR_CFG_INGR0_PTP_FLOW[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR0_PTP_FLOW_ENA", 0x00000000, 0x00000001, 0x00000001},
    {"INGR0_PTP_FLOW_MATCH_UPPER", 0x00000001, 0x00000001, 0x00000001},
    {"INGR0_PTP_FLOW_MATCH_LOWER", 0x00000002, 0x00000001, 0x00000001},
    {"INGR0_PTP_FLOW_MASK_UPPER", 0x00000003, 0x00000001, 0x00000001},
    {"INGR0_PTP_FLOW_MASK_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"INGR0_PTP_DOMAIN_RANGE", 0x00000005, 0x00000001, 0x00000001},
    {"INGR0_PTP_ACTION", 0x00000006, 0x00000001, 0x00000001},
    {"INGR0_PTP_ACTION_2", 0x00000007, 0x00000001, 0x00000001},
    {"INGR0_PTP_ZERO_FIELD_CTL", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_INGR_CFG_INGR0_PTP_IP_CHKSUM_CTL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR0_PTP_IP_CKSUM_SEL", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_PTP_ANA0_INGR_CFG[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"INGR0_ETH1_NXT_PROTOCOL", 0x0000a000, 0x00000001, 0x00000010, regs_within_PTP_ANA0_INGR_CFG_INGR0_ETH1_NXT_PROTOCOL},
    {"INGR0_ETH1_FLOW_CFG", 0x0000a010, 0x00000008, 0x00000010, regs_within_PTP_ANA0_INGR_CFG_INGR0_ETH1_FLOW_CFG},
    {"INGR0_ETH2_NXT_PROTOCOL", 0x0000a090, 0x00000001, 0x00000010, regs_within_PTP_ANA0_INGR_CFG_INGR0_ETH2_NXT_PROTOCOL},
    {"INGR0_ETH2_FLOW_CFG", 0x0000a0a0, 0x00000008, 0x00000010, regs_within_PTP_ANA0_INGR_CFG_INGR0_ETH2_FLOW_CFG},
    {"INGR0_MPLS_NXT_COMPARATOR", 0x0000a120, 0x00000001, 0x00000010, regs_within_PTP_ANA0_INGR_CFG_INGR0_MPLS_NXT_COMPARATOR},
    {"INGR0_MPLS_FLOW_CFG", 0x0000a130, 0x00000008, 0x00000010, regs_within_PTP_ANA0_INGR_CFG_INGR0_MPLS_FLOW_CFG},
    {"INGR0_IP1_NXT_PROTOCOL", 0x0000a1b0, 0x00000001, 0x00000010, regs_within_PTP_ANA0_INGR_CFG_INGR0_IP1_NXT_PROTOCOL},
    {"INGR0_IP1_FLOW_CFG", 0x0000a1c0, 0x00000008, 0x00000010, regs_within_PTP_ANA0_INGR_CFG_INGR0_IP1_FLOW_CFG},
    {"INGR0_IP2_NXT_PROTOCOL", 0x0000a240, 0x00000001, 0x00000010, regs_within_PTP_ANA0_INGR_CFG_INGR0_IP2_NXT_PROTOCOL},
    {"INGR0_IP2_FLOW_CFG", 0x0000a250, 0x00000008, 0x00000010, regs_within_PTP_ANA0_INGR_CFG_INGR0_IP2_FLOW_CFG},
    {"INGR0_PTP_FLOW", 0x0000a2d0, 0x00000006, 0x00000010, regs_within_PTP_ANA0_INGR_CFG_INGR0_PTP_FLOW},
    {"INGR0_PTP_IP_CHKSUM_CTL", 0x0000a330, 0x00000001, 0x00000001, regs_within_PTP_ANA0_INGR_CFG_INGR0_PTP_IP_CHKSUM_CTL},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_EGR_CFG_EGR0_ETH1_NXT_PROTOCOL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR0_ETH1_NXT_PROTOCOL_REG", 0x00000000, 0x00000001, 0x00000001},
    {"EGR0_ETH1_VLAN_TPID_CFG", 0x00000001, 0x00000001, 0x00000001},
    {"EGR0_ETH1_TAG_MODE", 0x00000002, 0x00000001, 0x00000001},
    {"EGR0_ETH1_ETYPE_MATCH", 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_EGR_CFG_EGR0_ETH1_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR0_ETH1_FLOW_ENABLE", 0x00000000, 0x00000001, 0x00000001},
    {"EGR0_ETH1_MATCH_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"EGR0_ETH1_ADDR_MATCH_1", 0x00000002, 0x00000001, 0x00000001},
    {"EGR0_ETH1_ADDR_MATCH_2", 0x00000003, 0x00000001, 0x00000001},
    {"EGR0_ETH1_VLAN_TAG_RANGE_I_TAG", 0x00000004, 0x00000001, 0x00000001},
    {"EGR0_ETH1_VLAN_TAG1", 0x00000005, 0x00000001, 0x00000001},
    {"EGR0_ETH1_VLAN_TAG2_I_TAG", 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_EGR_CFG_EGR0_ETH2_NXT_PROTOCOL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR0_ETH2_NXT_PROTOCOL_REG", 0x00000000, 0x00000001, 0x00000001},
    {"EGR0_ETH2_VLAN_TPID_CFG", 0x00000001, 0x00000001, 0x00000001},
    {"EGR0_ETH2_ETYPE_MATCH", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_EGR_CFG_EGR0_ETH2_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR0_ETH2_FLOW_ENABLE", 0x00000000, 0x00000001, 0x00000001},
    {"EGR0_ETH2_MATCH_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"EGR0_ETH2_ADDR_MATCH_1", 0x00000002, 0x00000001, 0x00000001},
    {"EGR0_ETH2_ADDR_MATCH_2", 0x00000003, 0x00000001, 0x00000001},
    {"EGR0_ETH2_VLAN_TAG_RANGE_I_TAG", 0x00000004, 0x00000001, 0x00000001},
    {"EGR0_ETH2_VLAN_TAG1", 0x00000005, 0x00000001, 0x00000001},
    {"EGR0_ETH2_VLAN_TAG2_I_TAG", 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_EGR_CFG_EGR0_MPLS_NXT_COMPARATOR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR0_MPLS_NXT_COMPARATOR", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_EGR_CFG_EGR0_MPLS_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR0_MPLS_FLOW_CONTROL", 0x00000000, 0x00000001, 0x00000001},
    {"EGR0_MPLS_FLOW_MATCH_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"EGR0_MPLS_LABEL_RANGE_LOWER_0", 0x00000002, 0x00000001, 0x00000001},
    {"EGR0_MPLS_LABEL_RANGE_UPPER_0", 0x00000003, 0x00000001, 0x00000001},
    {"EGR0_MPLS_LABEL_RANGE_LOWER_1", 0x00000004, 0x00000001, 0x00000001},
    {"EGR0_MPLS_LABEL_RANGE_UPPER_1", 0x00000005, 0x00000001, 0x00000001},
    {"EGR0_MPLS_LABEL_RANGE_LOWER_2", 0x00000006, 0x00000001, 0x00000001},
    {"EGR0_MPLS_LABEL_RANGE_UPPER_2", 0x00000007, 0x00000001, 0x00000001},
    {"EGR0_MPLS_LABEL_RANGE_LOWER_3", 0x00000008, 0x00000001, 0x00000001},
    {"EGR0_MPLS_LABEL_RANGE_UPPER_3", 0x00000009, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_EGR_CFG_EGR0_IP1_NXT_PROTOCOL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR0_IP1_NXT_COMPARATOR", 0x00000000, 0x00000001, 0x00000001},
    {"EGR0_IP1_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"EGR0_IP1_PROT_MATCH_1", 0x00000002, 0x00000001, 0x00000001},
    {"EGR0_IP1_PROT_MATCH_2_UPPER", 0x00000003, 0x00000001, 0x00000001},
    {"EGR0_IP1_PROT_MATCH_2_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"EGR0_IP1_PROT_MASK_2_UPPER", 0x00000005, 0x00000001, 0x00000001},
    {"EGR0_IP1_PROT_MASK_2_LOWER", 0x00000006, 0x00000001, 0x00000001},
    {"EGR0_IP1_PROT_OFFSET_2", 0x00000007, 0x00000001, 0x00000001},
    {"EGR0_IP1_UDP_CHKSUM_CFG", 0x00000008, 0x00000001, 0x00000001},
    {"EGR0_IP1_FRAME_SIG_CFG", 0x00000009, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_EGR_CFG_EGR0_IP1_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR0_IP1_FLOW_ENA", 0x00000000, 0x00000001, 0x00000001},
    {"EGR0_IP1_FLOW_MATCH_UPPER", 0x00000001, 0x00000001, 0x00000001},
    {"EGR0_IP1_FLOW_MATCH_UPPER_MID", 0x00000002, 0x00000001, 0x00000001},
    {"EGR0_IP1_FLOW_MATCH_LOWER_MID", 0x00000003, 0x00000001, 0x00000001},
    {"EGR0_IP1_FLOW_MATCH_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"EGR0_IP1_FLOW_MASK_UPPER", 0x00000005, 0x00000001, 0x00000001},
    {"EGR0_IP1_FLOW_MASK_UPPER_MID", 0x00000006, 0x00000001, 0x00000001},
    {"EGR0_IP1_FLOW_MASK_LOWER_MID", 0x00000007, 0x00000001, 0x00000001},
    {"EGR0_IP1_FLOW_MASK_LOWER", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_EGR_CFG_EGR0_IP2_NXT_PROTOCOL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR0_IP2_NXT_COMPARATOR", 0x00000000, 0x00000001, 0x00000001},
    {"EGR0_IP2_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"EGR0_IP2_PROT_MATCH_1", 0x00000002, 0x00000001, 0x00000001},
    {"EGR0_IP2_PROT_MATCH_2_UPPER", 0x00000003, 0x00000001, 0x00000001},
    {"EGR0_IP2_PROT_MATCH_2_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"EGR0_IP2_PROT_MASK_2_UPPER", 0x00000005, 0x00000001, 0x00000001},
    {"EGR0_IP2_PROT_MASK_2_LOWER", 0x00000006, 0x00000001, 0x00000001},
    {"EGR0_IP2_PROT_OFFSET_2", 0x00000007, 0x00000001, 0x00000001},
    {"EGR0_IP2_UDP_CHKSUM_CFG", 0x00000008, 0x00000001, 0x00000001},
    {"EGR0_IP2_FRAME_SIG_CFG", 0x00000009, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_EGR_CFG_EGR0_IP2_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR0_IP2_FLOW_ENA", 0x00000000, 0x00000001, 0x00000001},
    {"EGR0_IP2_FLOW_MATCH_UPPER", 0x00000001, 0x00000001, 0x00000001},
    {"EGR0_IP2_FLOW_MATCH_UPPER_MID", 0x00000002, 0x00000001, 0x00000001},
    {"EGR0_IP2_FLOW_MATCH_LOWER_MID", 0x00000003, 0x00000001, 0x00000001},
    {"EGR0_IP2_FLOW_MATCH_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"EGR0_IP2_FLOW_MASK_UPPER", 0x00000005, 0x00000001, 0x00000001},
    {"EGR0_IP2_FLOW_MASK_UPPER_MID", 0x00000006, 0x00000001, 0x00000001},
    {"EGR0_IP2_FLOW_MASK_LOWER_MID", 0x00000007, 0x00000001, 0x00000001},
    {"EGR0_IP2_FLOW_MASK_LOWER", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_EGR_CFG_EGR0_PTP_FLOW[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR0_PTP_FLOW_ENA", 0x00000000, 0x00000001, 0x00000001},
    {"EGR0_PTP_FLOW_MATCH_UPPER", 0x00000001, 0x00000001, 0x00000001},
    {"EGR0_PTP_FLOW_MATCH_LOWER", 0x00000002, 0x00000001, 0x00000001},
    {"EGR0_PTP_FLOW_MASK_UPPER", 0x00000003, 0x00000001, 0x00000001},
    {"EGR0_PTP_FLOW_MASK_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"EGR0_PTP_DOMAIN_RANGE", 0x00000005, 0x00000001, 0x00000001},
    {"EGR0_PTP_ACTION", 0x00000006, 0x00000001, 0x00000001},
    {"EGR0_PTP_ACTION_2", 0x00000007, 0x00000001, 0x00000001},
    {"EGR0_PTP_ZERO_FIELD_CTL", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_EGR_CFG_EGR0_PTP_IP_CHKSUM_CTL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR0_PTP_IP_CKSUM_SEL", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA0_EGR_CFG_EGR0_FRAME_SIG_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR0_FSB_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"EGR0_FSB_MAP_REG_0", 0x00000001, 0x00000001, 0x00000001},
    {"EGR0_FSB_MAP_REG_1", 0x00000002, 0x00000001, 0x00000001},
    {"EGR0_FSB_MAP_REG_2", 0x00000003, 0x00000001, 0x00000001},
    {"EGR0_FSB_MAP_REG_3", 0x00000004, 0x00000001, 0x00000001},
    {"EGR0_FSB_MAP_REG_4", 0x00000005, 0x00000001, 0x00000001},
    {"EGR0_FSB_MAP_REG_5", 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_PTP_ANA0_EGR_CFG[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"EGR0_ETH1_NXT_PROTOCOL", 0x0000a800, 0x00000001, 0x00000010, regs_within_PTP_ANA0_EGR_CFG_EGR0_ETH1_NXT_PROTOCOL},
    {"EGR0_ETH1_FLOW_CFG", 0x0000a810, 0x00000008, 0x00000010, regs_within_PTP_ANA0_EGR_CFG_EGR0_ETH1_FLOW_CFG},
    {"EGR0_ETH2_NXT_PROTOCOL", 0x0000a890, 0x00000001, 0x00000010, regs_within_PTP_ANA0_EGR_CFG_EGR0_ETH2_NXT_PROTOCOL},
    {"EGR0_ETH2_FLOW_CFG", 0x0000a8a0, 0x00000008, 0x00000010, regs_within_PTP_ANA0_EGR_CFG_EGR0_ETH2_FLOW_CFG},
    {"EGR0_MPLS_NXT_COMPARATOR", 0x0000a920, 0x00000001, 0x00000010, regs_within_PTP_ANA0_EGR_CFG_EGR0_MPLS_NXT_COMPARATOR},
    {"EGR0_MPLS_FLOW_CFG", 0x0000a930, 0x00000008, 0x00000010, regs_within_PTP_ANA0_EGR_CFG_EGR0_MPLS_FLOW_CFG},
    {"EGR0_IP1_NXT_PROTOCOL", 0x0000a9b0, 0x00000001, 0x00000010, regs_within_PTP_ANA0_EGR_CFG_EGR0_IP1_NXT_PROTOCOL},
    {"EGR0_IP1_FLOW_CFG", 0x0000a9c0, 0x00000008, 0x00000010, regs_within_PTP_ANA0_EGR_CFG_EGR0_IP1_FLOW_CFG},
    {"EGR0_IP2_NXT_PROTOCOL", 0x0000aa40, 0x00000001, 0x00000010, regs_within_PTP_ANA0_EGR_CFG_EGR0_IP2_NXT_PROTOCOL},
    {"EGR0_IP2_FLOW_CFG", 0x0000aa50, 0x00000008, 0x00000010, regs_within_PTP_ANA0_EGR_CFG_EGR0_IP2_FLOW_CFG},
    {"EGR0_PTP_FLOW", 0x0000aad0, 0x00000006, 0x00000010, regs_within_PTP_ANA0_EGR_CFG_EGR0_PTP_FLOW},
    {"EGR0_PTP_IP_CHKSUM_CTL", 0x0000ab30, 0x00000001, 0x00000001, regs_within_PTP_ANA0_EGR_CFG_EGR0_PTP_IP_CHKSUM_CTL},
    {"EGR0_FRAME_SIG_CFG", 0x0000ab31, 0x00000001, 0x00000007, regs_within_PTP_ANA0_EGR_CFG_EGR0_FRAME_SIG_CFG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_INGR_CFG_INGR1_ETH1_NXT_PROTOCOL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR1_ETH1_NXT_PROTOCOL_REG", 0x00000000, 0x00000001, 0x00000001},
    {"INGR1_ETH1_VLAN_TPID_CFG", 0x00000001, 0x00000001, 0x00000001},
    {"INGR1_ETH1_TAG_MODE", 0x00000002, 0x00000001, 0x00000001},
    {"INGR1_ETH1_ETYPE_MATCH", 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_INGR_CFG_INGR1_ETH1_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR1_ETH1_FLOW_ENABLE", 0x00000000, 0x00000001, 0x00000001},
    {"INGR1_ETH1_MATCH_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"INGR1_ETH1_ADDR_MATCH_1", 0x00000002, 0x00000001, 0x00000001},
    {"INGR1_ETH1_ADDR_MATCH_2", 0x00000003, 0x00000001, 0x00000001},
    {"INGR1_ETH1_VLAN_TAG_RANGE_I_TAG", 0x00000004, 0x00000001, 0x00000001},
    {"INGR1_ETH1_VLAN_TAG1", 0x00000005, 0x00000001, 0x00000001},
    {"INGR1_ETH1_VLAN_TAG2_I_TAG", 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_INGR_CFG_INGR1_ETH2_NXT_PROTOCOL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR1_ETH2_NXT_PROTOCOL_REG", 0x00000000, 0x00000001, 0x00000001},
    {"INGR1_ETH2_VLAN_TPID_CFG", 0x00000001, 0x00000001, 0x00000001},
    {"INGR1_ETH2_ETYPE_MATCH", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_INGR_CFG_INGR1_ETH2_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR1_ETH2_FLOW_ENABLE", 0x00000000, 0x00000001, 0x00000001},
    {"INGR1_ETH2_MATCH_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"INGR1_ETH2_ADDR_MATCH_1", 0x00000002, 0x00000001, 0x00000001},
    {"INGR1_ETH2_ADDR_MATCH_2", 0x00000003, 0x00000001, 0x00000001},
    {"INGR1_ETH2_VLAN_TAG_RANGE_I_TAG", 0x00000004, 0x00000001, 0x00000001},
    {"INGR1_ETH2_VLAN_TAG1", 0x00000005, 0x00000001, 0x00000001},
    {"INGR1_ETH2_VLAN_TAG2_I_TAG", 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_INGR_CFG_INGR1_MPLS_NXT_COMPARATOR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR1_MPLS_NXT_COMPARATOR", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_INGR_CFG_INGR1_MPLS_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR1_MPLS_FLOW_CONTROL", 0x00000000, 0x00000001, 0x00000001},
    {"INGR1_MPLS_FLOW_MATCH_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"INGR1_MPLS_LABEL_RANGE_LOWER_0", 0x00000002, 0x00000001, 0x00000001},
    {"INGR1_MPLS_LABEL_RANGE_UPPER_0", 0x00000003, 0x00000001, 0x00000001},
    {"INGR1_MPLS_LABEL_RANGE_LOWER_1", 0x00000004, 0x00000001, 0x00000001},
    {"INGR1_MPLS_LABEL_RANGE_UPPER_1", 0x00000005, 0x00000001, 0x00000001},
    {"INGR1_MPLS_LABEL_RANGE_LOWER_2", 0x00000006, 0x00000001, 0x00000001},
    {"INGR1_MPLS_LABEL_RANGE_UPPER_2", 0x00000007, 0x00000001, 0x00000001},
    {"INGR1_MPLS_LABEL_RANGE_LOWER_3", 0x00000008, 0x00000001, 0x00000001},
    {"INGR1_MPLS_LABEL_RANGE_UPPER_3", 0x00000009, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_INGR_CFG_INGR1_IP1_NXT_PROTOCOL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR1_IP1_NXT_COMPARATOR", 0x00000000, 0x00000001, 0x00000001},
    {"INGR1_IP1_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"INGR1_IP1_PROT_MATCH_1", 0x00000002, 0x00000001, 0x00000001},
    {"INGR1_IP1_PROT_MATCH_2_UPPER", 0x00000003, 0x00000001, 0x00000001},
    {"INGR1_IP1_PROT_MATCH_2_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"INGR1_IP1_PROT_MASK_2_UPPER", 0x00000005, 0x00000001, 0x00000001},
    {"INGR1_IP1_PROT_MASK_2_LOWER", 0x00000006, 0x00000001, 0x00000001},
    {"INGR1_IP1_PROT_OFFSET_2", 0x00000007, 0x00000001, 0x00000001},
    {"INGR1_IP1_UDP_CHKSUM_CFG", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_INGR_CFG_INGR1_IP1_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR1_IP1_FLOW_ENA", 0x00000000, 0x00000001, 0x00000001},
    {"INGR1_IP1_FLOW_MATCH_UPPER", 0x00000001, 0x00000001, 0x00000001},
    {"INGR1_IP1_FLOW_MATCH_UPPER_MID", 0x00000002, 0x00000001, 0x00000001},
    {"INGR1_IP1_FLOW_MATCH_LOWER_MID", 0x00000003, 0x00000001, 0x00000001},
    {"INGR1_IP1_FLOW_MATCH_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"INGR1_IP1_FLOW_MASK_UPPER", 0x00000005, 0x00000001, 0x00000001},
    {"INGR1_IP1_FLOW_MASK_UPPER_MID", 0x00000006, 0x00000001, 0x00000001},
    {"INGR1_IP1_FLOW_MASK_LOWER_MID", 0x00000007, 0x00000001, 0x00000001},
    {"INGR1_IP1_FLOW_MASK_LOWER", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_INGR_CFG_INGR1_IP2_NXT_PROTOCOL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR1_IP2_NXT_COMPARATOR", 0x00000000, 0x00000001, 0x00000001},
    {"INGR1_IP2_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"INGR1_IP2_PROT_MATCH_1", 0x00000002, 0x00000001, 0x00000001},
    {"INGR1_IP2_PROT_MATCH_2_UPPER", 0x00000003, 0x00000001, 0x00000001},
    {"INGR1_IP2_PROT_MATCH_2_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"INGR1_IP2_PROT_MASK_2_UPPER", 0x00000005, 0x00000001, 0x00000001},
    {"INGR1_IP2_PROT_MASK_2_LOWER", 0x00000006, 0x00000001, 0x00000001},
    {"INGR1_IP2_PROT_OFFSET_2", 0x00000007, 0x00000001, 0x00000001},
    {"INGR1_IP2_UDP_CHKSUM_CFG", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_INGR_CFG_INGR1_IP2_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR1_IP2_FLOW_ENA", 0x00000000, 0x00000001, 0x00000001},
    {"INGR1_IP2_FLOW_MATCH_UPPER", 0x00000001, 0x00000001, 0x00000001},
    {"INGR1_IP2_FLOW_MATCH_UPPER_MID", 0x00000002, 0x00000001, 0x00000001},
    {"INGR1_IP2_FLOW_MATCH_LOWER_MID", 0x00000003, 0x00000001, 0x00000001},
    {"INGR1_IP2_FLOW_MATCH_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"INGR1_IP2_FLOW_MASK_UPPER", 0x00000005, 0x00000001, 0x00000001},
    {"INGR1_IP2_FLOW_MASK_UPPER_MID", 0x00000006, 0x00000001, 0x00000001},
    {"INGR1_IP2_FLOW_MASK_LOWER_MID", 0x00000007, 0x00000001, 0x00000001},
    {"INGR1_IP2_FLOW_MASK_LOWER", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_INGR_CFG_INGR1_PTP_FLOW[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR1_PTP_FLOW_ENA", 0x00000000, 0x00000001, 0x00000001},
    {"INGR1_PTP_FLOW_MATCH_UPPER", 0x00000001, 0x00000001, 0x00000001},
    {"INGR1_PTP_FLOW_MATCH_LOWER", 0x00000002, 0x00000001, 0x00000001},
    {"INGR1_PTP_FLOW_MASK_UPPER", 0x00000003, 0x00000001, 0x00000001},
    {"INGR1_PTP_FLOW_MASK_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"INGR1_PTP_DOMAIN_RANGE", 0x00000005, 0x00000001, 0x00000001},
    {"INGR1_PTP_ACTION", 0x00000006, 0x00000001, 0x00000001},
    {"INGR1_PTP_ACTION_2", 0x00000007, 0x00000001, 0x00000001},
    {"INGR1_PTP_ZERO_FIELD_CTL", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_INGR_CFG_INGR1_PTP_IP_CHKSUM_CTL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR1_PTP_IP_CKSUM_SEL", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_PTP_ANA1_INGR_CFG[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"INGR1_ETH1_NXT_PROTOCOL", 0x0000b000, 0x00000001, 0x00000010, regs_within_PTP_ANA1_INGR_CFG_INGR1_ETH1_NXT_PROTOCOL},
    {"INGR1_ETH1_FLOW_CFG", 0x0000b010, 0x00000008, 0x00000010, regs_within_PTP_ANA1_INGR_CFG_INGR1_ETH1_FLOW_CFG},
    {"INGR1_ETH2_NXT_PROTOCOL", 0x0000b090, 0x00000001, 0x00000010, regs_within_PTP_ANA1_INGR_CFG_INGR1_ETH2_NXT_PROTOCOL},
    {"INGR1_ETH2_FLOW_CFG", 0x0000b0a0, 0x00000008, 0x00000010, regs_within_PTP_ANA1_INGR_CFG_INGR1_ETH2_FLOW_CFG},
    {"INGR1_MPLS_NXT_COMPARATOR", 0x0000b120, 0x00000001, 0x00000010, regs_within_PTP_ANA1_INGR_CFG_INGR1_MPLS_NXT_COMPARATOR},
    {"INGR1_MPLS_FLOW_CFG", 0x0000b130, 0x00000008, 0x00000010, regs_within_PTP_ANA1_INGR_CFG_INGR1_MPLS_FLOW_CFG},
    {"INGR1_IP1_NXT_PROTOCOL", 0x0000b1b0, 0x00000001, 0x00000010, regs_within_PTP_ANA1_INGR_CFG_INGR1_IP1_NXT_PROTOCOL},
    {"INGR1_IP1_FLOW_CFG", 0x0000b1c0, 0x00000008, 0x00000010, regs_within_PTP_ANA1_INGR_CFG_INGR1_IP1_FLOW_CFG},
    {"INGR1_IP2_NXT_PROTOCOL", 0x0000b240, 0x00000001, 0x00000010, regs_within_PTP_ANA1_INGR_CFG_INGR1_IP2_NXT_PROTOCOL},
    {"INGR1_IP2_FLOW_CFG", 0x0000b250, 0x00000008, 0x00000010, regs_within_PTP_ANA1_INGR_CFG_INGR1_IP2_FLOW_CFG},
    {"INGR1_PTP_FLOW", 0x0000b2d0, 0x00000006, 0x00000010, regs_within_PTP_ANA1_INGR_CFG_INGR1_PTP_FLOW},
    {"INGR1_PTP_IP_CHKSUM_CTL", 0x0000b330, 0x00000001, 0x00000001, regs_within_PTP_ANA1_INGR_CFG_INGR1_PTP_IP_CHKSUM_CTL},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_EGR_CFG_EGR1_ETH1_NXT_PROTOCOL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR1_ETH1_NXT_PROTOCOL_REG", 0x00000000, 0x00000001, 0x00000001},
    {"EGR1_ETH1_VLAN_TPID_CFG", 0x00000001, 0x00000001, 0x00000001},
    {"EGR1_ETH1_TAG_MODE", 0x00000002, 0x00000001, 0x00000001},
    {"EGR1_ETH1_ETYPE_MATCH", 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_EGR_CFG_EGR1_ETH1_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR1_ETH1_FLOW_ENABLE", 0x00000000, 0x00000001, 0x00000001},
    {"EGR1_ETH1_MATCH_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"EGR1_ETH1_ADDR_MATCH_1", 0x00000002, 0x00000001, 0x00000001},
    {"EGR1_ETH1_ADDR_MATCH_2", 0x00000003, 0x00000001, 0x00000001},
    {"EGR1_ETH1_VLAN_TAG_RANGE_I_TAG", 0x00000004, 0x00000001, 0x00000001},
    {"EGR1_ETH1_VLAN_TAG1", 0x00000005, 0x00000001, 0x00000001},
    {"EGR1_ETH1_VLAN_TAG2_I_TAG", 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_EGR_CFG_EGR1_ETH2_NXT_PROTOCOL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR1_ETH2_NXT_PROTOCOL_REG", 0x00000000, 0x00000001, 0x00000001},
    {"EGR1_ETH2_VLAN_TPID_CFG", 0x00000001, 0x00000001, 0x00000001},
    {"EGR1_ETH2_ETYPE_MATCH", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_EGR_CFG_EGR1_ETH2_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR1_ETH2_FLOW_ENABLE", 0x00000000, 0x00000001, 0x00000001},
    {"EGR1_ETH2_MATCH_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"EGR1_ETH2_ADDR_MATCH_1", 0x00000002, 0x00000001, 0x00000001},
    {"EGR1_ETH2_ADDR_MATCH_2", 0x00000003, 0x00000001, 0x00000001},
    {"EGR1_ETH2_VLAN_TAG_RANGE_I_TAG", 0x00000004, 0x00000001, 0x00000001},
    {"EGR1_ETH2_VLAN_TAG1", 0x00000005, 0x00000001, 0x00000001},
    {"EGR1_ETH2_VLAN_TAG2_I_TAG", 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_EGR_CFG_EGR1_MPLS_NXT_COMPARATOR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR1_MPLS_NXT_COMPARATOR", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_EGR_CFG_EGR1_MPLS_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR1_MPLS_FLOW_CONTROL", 0x00000000, 0x00000001, 0x00000001},
    {"EGR1_MPLS_FLOW_MATCH_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"EGR1_MPLS_LABEL_RANGE_LOWER_0", 0x00000002, 0x00000001, 0x00000001},
    {"EGR1_MPLS_LABEL_RANGE_UPPER_0", 0x00000003, 0x00000001, 0x00000001},
    {"EGR1_MPLS_LABEL_RANGE_LOWER_1", 0x00000004, 0x00000001, 0x00000001},
    {"EGR1_MPLS_LABEL_RANGE_UPPER_1", 0x00000005, 0x00000001, 0x00000001},
    {"EGR1_MPLS_LABEL_RANGE_LOWER_2", 0x00000006, 0x00000001, 0x00000001},
    {"EGR1_MPLS_LABEL_RANGE_UPPER_2", 0x00000007, 0x00000001, 0x00000001},
    {"EGR1_MPLS_LABEL_RANGE_LOWER_3", 0x00000008, 0x00000001, 0x00000001},
    {"EGR1_MPLS_LABEL_RANGE_UPPER_3", 0x00000009, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_EGR_CFG_EGR1_IP1_NXT_PROTOCOL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR1_IP1_NXT_COMPARATOR", 0x00000000, 0x00000001, 0x00000001},
    {"EGR1_IP1_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"EGR1_IP1_PROT_MATCH_1", 0x00000002, 0x00000001, 0x00000001},
    {"EGR1_IP1_PROT_MATCH_2_UPPER", 0x00000003, 0x00000001, 0x00000001},
    {"EGR1_IP1_PROT_MATCH_2_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"EGR1_IP1_PROT_MASK_2_UPPER", 0x00000005, 0x00000001, 0x00000001},
    {"EGR1_IP1_PROT_MASK_2_LOWER", 0x00000006, 0x00000001, 0x00000001},
    {"EGR1_IP1_PROT_OFFSET_2", 0x00000007, 0x00000001, 0x00000001},
    {"EGR1_IP1_UDP_CHKSUM_CFG", 0x00000008, 0x00000001, 0x00000001},
    {"EGR1_IP1_FRAME_SIG_CFG", 0x00000009, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_EGR_CFG_EGR1_IP1_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR1_IP1_FLOW_ENA", 0x00000000, 0x00000001, 0x00000001},
    {"EGR1_IP1_FLOW_MATCH_UPPER", 0x00000001, 0x00000001, 0x00000001},
    {"EGR1_IP1_FLOW_MATCH_UPPER_MID", 0x00000002, 0x00000001, 0x00000001},
    {"EGR1_IP1_FLOW_MATCH_LOWER_MID", 0x00000003, 0x00000001, 0x00000001},
    {"EGR1_IP1_FLOW_MATCH_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"EGR1_IP1_FLOW_MASK_UPPER", 0x00000005, 0x00000001, 0x00000001},
    {"EGR1_IP1_FLOW_MASK_UPPER_MID", 0x00000006, 0x00000001, 0x00000001},
    {"EGR1_IP1_FLOW_MASK_LOWER_MID", 0x00000007, 0x00000001, 0x00000001},
    {"EGR1_IP1_FLOW_MASK_LOWER", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_EGR_CFG_EGR1_IP2_NXT_PROTOCOL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR1_IP2_NXT_COMPARATOR", 0x00000000, 0x00000001, 0x00000001},
    {"EGR1_IP2_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"EGR1_IP2_PROT_MATCH_1", 0x00000002, 0x00000001, 0x00000001},
    {"EGR1_IP2_PROT_MATCH_2_UPPER", 0x00000003, 0x00000001, 0x00000001},
    {"EGR1_IP2_PROT_MATCH_2_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"EGR1_IP2_PROT_MASK_2_UPPER", 0x00000005, 0x00000001, 0x00000001},
    {"EGR1_IP2_PROT_MASK_2_LOWER", 0x00000006, 0x00000001, 0x00000001},
    {"EGR1_IP2_PROT_OFFSET_2", 0x00000007, 0x00000001, 0x00000001},
    {"EGR1_IP2_UDP_CHKSUM_CFG", 0x00000008, 0x00000001, 0x00000001},
    {"EGR1_IP2_FRAME_SIG_CFG", 0x00000009, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_EGR_CFG_EGR1_IP2_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR1_IP2_FLOW_ENA", 0x00000000, 0x00000001, 0x00000001},
    {"EGR1_IP2_FLOW_MATCH_UPPER", 0x00000001, 0x00000001, 0x00000001},
    {"EGR1_IP2_FLOW_MATCH_UPPER_MID", 0x00000002, 0x00000001, 0x00000001},
    {"EGR1_IP2_FLOW_MATCH_LOWER_MID", 0x00000003, 0x00000001, 0x00000001},
    {"EGR1_IP2_FLOW_MATCH_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"EGR1_IP2_FLOW_MASK_UPPER", 0x00000005, 0x00000001, 0x00000001},
    {"EGR1_IP2_FLOW_MASK_UPPER_MID", 0x00000006, 0x00000001, 0x00000001},
    {"EGR1_IP2_FLOW_MASK_LOWER_MID", 0x00000007, 0x00000001, 0x00000001},
    {"EGR1_IP2_FLOW_MASK_LOWER", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_EGR_CFG_EGR1_PTP_FLOW[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR1_PTP_FLOW_ENA", 0x00000000, 0x00000001, 0x00000001},
    {"EGR1_PTP_FLOW_MATCH_UPPER", 0x00000001, 0x00000001, 0x00000001},
    {"EGR1_PTP_FLOW_MATCH_LOWER", 0x00000002, 0x00000001, 0x00000001},
    {"EGR1_PTP_FLOW_MASK_UPPER", 0x00000003, 0x00000001, 0x00000001},
    {"EGR1_PTP_FLOW_MASK_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"EGR1_PTP_DOMAIN_RANGE", 0x00000005, 0x00000001, 0x00000001},
    {"EGR1_PTP_ACTION", 0x00000006, 0x00000001, 0x00000001},
    {"EGR1_PTP_ACTION_2", 0x00000007, 0x00000001, 0x00000001},
    {"EGR1_PTP_ZERO_FIELD_CTL", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_EGR_CFG_EGR1_PTP_IP_CHKSUM_CTL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR1_PTP_IP_CKSUM_SEL", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA1_EGR_CFG_EGR1_FRAME_SIG_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR1_FSB_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"EGR1_FSB_MAP_REG_0", 0x00000001, 0x00000001, 0x00000001},
    {"EGR1_FSB_MAP_REG_1", 0x00000002, 0x00000001, 0x00000001},
    {"EGR1_FSB_MAP_REG_2", 0x00000003, 0x00000001, 0x00000001},
    {"EGR1_FSB_MAP_REG_3", 0x00000004, 0x00000001, 0x00000001},
    {"EGR1_FSB_MAP_REG_4", 0x00000005, 0x00000001, 0x00000001},
    {"EGR1_FSB_MAP_REG_5", 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_PTP_ANA1_EGR_CFG[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"EGR1_ETH1_NXT_PROTOCOL", 0x0000b800, 0x00000001, 0x00000010, regs_within_PTP_ANA1_EGR_CFG_EGR1_ETH1_NXT_PROTOCOL},
    {"EGR1_ETH1_FLOW_CFG", 0x0000b810, 0x00000008, 0x00000010, regs_within_PTP_ANA1_EGR_CFG_EGR1_ETH1_FLOW_CFG},
    {"EGR1_ETH2_NXT_PROTOCOL", 0x0000b890, 0x00000001, 0x00000010, regs_within_PTP_ANA1_EGR_CFG_EGR1_ETH2_NXT_PROTOCOL},
    {"EGR1_ETH2_FLOW_CFG", 0x0000b8a0, 0x00000008, 0x00000010, regs_within_PTP_ANA1_EGR_CFG_EGR1_ETH2_FLOW_CFG},
    {"EGR1_MPLS_NXT_COMPARATOR", 0x0000b920, 0x00000001, 0x00000010, regs_within_PTP_ANA1_EGR_CFG_EGR1_MPLS_NXT_COMPARATOR},
    {"EGR1_MPLS_FLOW_CFG", 0x0000b930, 0x00000008, 0x00000010, regs_within_PTP_ANA1_EGR_CFG_EGR1_MPLS_FLOW_CFG},
    {"EGR1_IP1_NXT_PROTOCOL", 0x0000b9b0, 0x00000001, 0x00000010, regs_within_PTP_ANA1_EGR_CFG_EGR1_IP1_NXT_PROTOCOL},
    {"EGR1_IP1_FLOW_CFG", 0x0000b9c0, 0x00000008, 0x00000010, regs_within_PTP_ANA1_EGR_CFG_EGR1_IP1_FLOW_CFG},
    {"EGR1_IP2_NXT_PROTOCOL", 0x0000ba40, 0x00000001, 0x00000010, regs_within_PTP_ANA1_EGR_CFG_EGR1_IP2_NXT_PROTOCOL},
    {"EGR1_IP2_FLOW_CFG", 0x0000ba50, 0x00000008, 0x00000010, regs_within_PTP_ANA1_EGR_CFG_EGR1_IP2_FLOW_CFG},
    {"EGR1_PTP_FLOW", 0x0000bad0, 0x00000006, 0x00000010, regs_within_PTP_ANA1_EGR_CFG_EGR1_PTP_FLOW},
    {"EGR1_PTP_IP_CHKSUM_CTL", 0x0000bb30, 0x00000001, 0x00000001, regs_within_PTP_ANA1_EGR_CFG_EGR1_PTP_IP_CHKSUM_CTL},
    {"EGR1_FRAME_SIG_CFG", 0x0000bb31, 0x00000001, 0x00000007, regs_within_PTP_ANA1_EGR_CFG_EGR1_FRAME_SIG_CFG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_INGR_CFG_INGR2_ETH1_NXT_PROTOCOL_A[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR2_ETH1_NXT_PROTOCOL_A_REG", 0x00000000, 0x00000001, 0x00000001},
    {"INGR2_ETH1_VLAN_TPID_CFG_A", 0x00000001, 0x00000001, 0x00000001},
    {"INGR2_ETH1_TAG_MODE_A", 0x00000002, 0x00000001, 0x00000001},
    {"INGR2_ETH1_ETYPE_MATCH_A", 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_INGR_CFG_INGR2_ETH1_NXT_PROTOCOL_B[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR2_ETH1_NXT_PROTOCOL_B_REG", 0x00000000, 0x00000001, 0x00000001},
    {"INGR2_ETH1_VLAN_TPID_CFG_B", 0x00000001, 0x00000001, 0x00000001},
    {"INGR2_ETH1_TAG_MODE_B", 0x00000002, 0x00000001, 0x00000001},
    {"INGR2_ETH1_ETYPE_MATCH_B", 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_INGR_CFG_INGR2_ETH1_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR2_ETH1_FLOW_ENABLE", 0x00000000, 0x00000001, 0x00000001},
    {"INGR2_ETH1_MATCH_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"INGR2_ETH1_ADDR_MATCH_1", 0x00000002, 0x00000001, 0x00000001},
    {"INGR2_ETH1_ADDR_MATCH_2", 0x00000003, 0x00000001, 0x00000001},
    {"INGR2_ETH1_VLAN_TAG_RANGE_I_TAG", 0x00000004, 0x00000001, 0x00000001},
    {"INGR2_ETH1_VLAN_TAG1", 0x00000005, 0x00000001, 0x00000001},
    {"INGR2_ETH1_VLAN_TAG2_I_TAG", 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_INGR_CFG_INGR2_ETH2_NXT_PROTOCOL_A[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR2_ETH2_NXT_PROTOCOL_A_REG", 0x00000000, 0x00000001, 0x00000001},
    {"INGR2_ETH2_VLAN_TPID_CFG_A", 0x00000001, 0x00000001, 0x00000001},
    {"INGR2_ETH2_ETYPE_MATCH_A", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_INGR_CFG_INGR2_ETH2_NXT_PROTOCOL_B[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR2_ETH2_NXT_PROTOCOL_B_REG", 0x00000000, 0x00000001, 0x00000001},
    {"INGR2_ETH2_VLAN_TPID_CFG_B", 0x00000001, 0x00000001, 0x00000001},
    {"INGR2_ETH2_ETYPE_MATCH_B", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_INGR_CFG_INGR2_ETH2_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR2_ETH2_FLOW_ENABLE", 0x00000000, 0x00000001, 0x00000001},
    {"INGR2_ETH2_MATCH_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"INGR2_ETH2_ADDR_MATCH_1", 0x00000002, 0x00000001, 0x00000001},
    {"INGR2_ETH2_ADDR_MATCH_2", 0x00000003, 0x00000001, 0x00000001},
    {"INGR2_ETH2_VLAN_TAG_RANGE_I_TAG", 0x00000004, 0x00000001, 0x00000001},
    {"INGR2_ETH2_VLAN_TAG1", 0x00000005, 0x00000001, 0x00000001},
    {"INGR2_ETH2_VLAN_TAG2_I_TAG", 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_INGR_CFG_INGR2_MPLS_NXT_COMPARATOR_A[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR2_MPLS_NXT_COMPARATOR_A", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_INGR_CFG_INGR2_MPLS_NXT_COMPARATOR_B[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR2_MPLS_NXT_COMPARATOR_B", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_INGR_CFG_INGR2_MPLS_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR2_MPLS_FLOW_CONTROL", 0x00000000, 0x00000001, 0x00000001},
    {"INGR2_MPLS_LABEL_RANGE_LOWER_0", 0x00000001, 0x00000001, 0x00000001},
    {"INGR2_MPLS_LABEL_RANGE_UPPER_0", 0x00000002, 0x00000001, 0x00000001},
    {"INGR2_MPLS_LABEL_RANGE_LOWER_1", 0x00000003, 0x00000001, 0x00000001},
    {"INGR2_MPLS_LABEL_RANGE_UPPER_1", 0x00000004, 0x00000001, 0x00000001},
    {"INGR2_MPLS_LABEL_RANGE_LOWER_2", 0x00000005, 0x00000001, 0x00000001},
    {"INGR2_MPLS_LABEL_RANGE_UPPER_2", 0x00000006, 0x00000001, 0x00000001},
    {"INGR2_MPLS_LABEL_RANGE_LOWER_3", 0x00000007, 0x00000001, 0x00000001},
    {"INGR2_MPLS_LABEL_RANGE_UPPER_3", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_INGR_CFG_INGR2_PTP_FLOW[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR2_PTP_FLOW_ENA", 0x00000000, 0x00000001, 0x00000001},
    {"INGR2_PTP_FLOW_MATCH_UPPER", 0x00000001, 0x00000001, 0x00000001},
    {"INGR2_PTP_FLOW_MATCH_LOWER", 0x00000002, 0x00000001, 0x00000001},
    {"INGR2_PTP_FLOW_MASK_UPPER", 0x00000003, 0x00000001, 0x00000001},
    {"INGR2_PTP_FLOW_MASK_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"INGR2_PTP_DOMAIN_RANGE", 0x00000005, 0x00000001, 0x00000001},
    {"INGR2_PTP_ACTION", 0x00000006, 0x00000001, 0x00000001},
    {"INGR2_PTP_ACTION_2", 0x00000007, 0x00000001, 0x00000001},
    {"INGR2_PTP_ZERO_FIELD_CTL", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_INGR_CFG_INGR2_FRAME_SIG_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR2_FSB_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"INGR2_FSB_MAP_REG_0", 0x00000001, 0x00000001, 0x00000001},
    {"INGR2_FSB_MAP_REG_1", 0x00000002, 0x00000001, 0x00000001},
    {"INGR2_FSB_MAP_REG_2", 0x00000003, 0x00000001, 0x00000001},
    {"INGR2_FSB_MAP_REG_3", 0x00000004, 0x00000001, 0x00000001},
    {"INGR2_FSB_MAP_REG_4", 0x00000005, 0x00000001, 0x00000001},
    {"INGR2_FSB_MAP_REG_5", 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_INGR_CFG_INGR2_ACH_COMPARATOR_A[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INGR2_ACH_PROT_MATCH_UPPER_A", 0x00000000, 0x00000001, 0x00000001},
    {"INGR2_ACH_PROT_MATCH_LOWER_A", 0x00000001, 0x00000001, 0x00000001},
    {"INGR2_ACH_PROT_MASK_UPPER_A", 0x00000002, 0x00000001, 0x00000001},
    {"INGR2_ACH_PROT_MASK_LOWER_A", 0x00000003, 0x00000001, 0x00000001},
    {"INGR2_ACH_PROT_OFFSET_A", 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_PTP_ANA2_INGR_CFG[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"INGR2_ETH1_NXT_PROTOCOL_A", 0x0000c000, 0x00000001, 0x00000010, regs_within_PTP_ANA2_INGR_CFG_INGR2_ETH1_NXT_PROTOCOL_A},
    {"INGR2_ETH1_NXT_PROTOCOL_B", 0x0000c010, 0x00000001, 0x00000010, regs_within_PTP_ANA2_INGR_CFG_INGR2_ETH1_NXT_PROTOCOL_B},
    {"INGR2_ETH1_FLOW_CFG", 0x0000c020, 0x00000008, 0x00000010, regs_within_PTP_ANA2_INGR_CFG_INGR2_ETH1_FLOW_CFG},
    {"INGR2_ETH2_NXT_PROTOCOL_A", 0x0000c0a0, 0x00000001, 0x00000010, regs_within_PTP_ANA2_INGR_CFG_INGR2_ETH2_NXT_PROTOCOL_A},
#ifndef VTSS_RELEASE
    {"INGR2_ETH2_NXT_PROTOCOL_B", 0x0000c0b0, 0x00000001, 0x00000010, regs_within_PTP_ANA2_INGR_CFG_INGR2_ETH2_NXT_PROTOCOL_B},
#endif
    {"INGR2_ETH2_FLOW_CFG", 0x0000c0c0, 0x00000008, 0x00000010, regs_within_PTP_ANA2_INGR_CFG_INGR2_ETH2_FLOW_CFG},
    {"INGR2_MPLS_NXT_COMPARATOR_A", 0x0000c140, 0x00000001, 0x00000010, regs_within_PTP_ANA2_INGR_CFG_INGR2_MPLS_NXT_COMPARATOR_A},
#ifndef VTSS_RELEASE
    {"INGR2_MPLS_NXT_COMPARATOR_B", 0x0000c150, 0x00000001, 0x00000010, regs_within_PTP_ANA2_INGR_CFG_INGR2_MPLS_NXT_COMPARATOR_B},
#endif
    {"INGR2_MPLS_FLOW_CFG", 0x0000c160, 0x00000008, 0x00000010, regs_within_PTP_ANA2_INGR_CFG_INGR2_MPLS_FLOW_CFG},
    {"INGR2_PTP_FLOW", 0x0000c1e0, 0x00000006, 0x00000010, regs_within_PTP_ANA2_INGR_CFG_INGR2_PTP_FLOW},
    {"INGR2_FRAME_SIG_CFG", 0x0000c240, 0x00000001, 0x00000007, regs_within_PTP_ANA2_INGR_CFG_INGR2_FRAME_SIG_CFG},
#ifndef VTSS_RELEASE
    {"INGR2_ACH_COMPARATOR_A", 0x0000c247, 0x00000001, 0x00000005, regs_within_PTP_ANA2_INGR_CFG_INGR2_ACH_COMPARATOR_A},
#endif
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_EGR_CFG_EGR2_ETH1_NXT_PROTOCOL_A[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR2_ETH1_NXT_PROTOCOL_A_REG", 0x00000000, 0x00000001, 0x00000001},
    {"EGR2_ETH1_VLAN_TPID_CFG_A", 0x00000001, 0x00000001, 0x00000001},
    {"EGR2_ETH1_TAG_MODE_A", 0x00000002, 0x00000001, 0x00000001},
    {"EGR2_ETH1_ETYPE_MATCH_A", 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_EGR_CFG_EGR2_ETH1_NXT_PROTOCOL_B[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR2_ETH1_NXT_PROTOCOL_B_REG", 0x00000000, 0x00000001, 0x00000001},
    {"EGR2_ETH1_VLAN_TPID_CFG_B", 0x00000001, 0x00000001, 0x00000001},
    {"EGR2_ETH1_TAG_MODE_B", 0x00000002, 0x00000001, 0x00000001},
    {"EGR2_ETH1_ETYPE_MATCH_B", 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_EGR_CFG_EGR2_ETH1_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR2_ETH1_FLOW_ENABLE", 0x00000000, 0x00000001, 0x00000001},
    {"EGR2_ETH1_MATCH_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"EGR2_ETH1_ADDR_MATCH_1", 0x00000002, 0x00000001, 0x00000001},
    {"EGR2_ETH1_ADDR_MATCH_2", 0x00000003, 0x00000001, 0x00000001},
    {"EGR2_ETH1_VLAN_TAG_RANGE_I_TAG", 0x00000004, 0x00000001, 0x00000001},
    {"EGR2_ETH1_VLAN_TAG1", 0x00000005, 0x00000001, 0x00000001},
    {"EGR2_ETH1_VLAN_TAG2_I_TAG", 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_EGR_CFG_EGR2_ETH2_NXT_PROTOCOL_A[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR2_ETH2_NXT_PROTOCOL_A_REG", 0x00000000, 0x00000001, 0x00000001},
    {"EGR2_ETH2_VLAN_TPID_CFG_A", 0x00000001, 0x00000001, 0x00000001},
    {"EGR2_ETH2_ETYPE_MATCH_A", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_EGR_CFG_EGR2_ETH2_NXT_PROTOCOL_B[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR2_ETH2_NXT_PROTOCOL_B_REG", 0x00000000, 0x00000001, 0x00000001},
    {"EGR2_ETH2_VLAN_TPID_CFG_B", 0x00000001, 0x00000001, 0x00000001},
    {"EGR2_ETH2_ETYPE_MATCH_B", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_EGR_CFG_EGR2_ETH2_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR2_ETH2_FLOW_ENABLE", 0x00000000, 0x00000001, 0x00000001},
    {"EGR2_ETH2_MATCH_MODE", 0x00000001, 0x00000001, 0x00000001},
    {"EGR2_ETH2_ADDR_MATCH_1", 0x00000002, 0x00000001, 0x00000001},
    {"EGR2_ETH2_ADDR_MATCH_2", 0x00000003, 0x00000001, 0x00000001},
    {"EGR2_ETH2_VLAN_TAG_RANGE_I_TAG", 0x00000004, 0x00000001, 0x00000001},
    {"EGR2_ETH2_VLAN_TAG1", 0x00000005, 0x00000001, 0x00000001},
    {"EGR2_ETH2_VLAN_TAG2_I_TAG", 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_EGR_CFG_EGR2_MPLS_NXT_COMPARATOR_A[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR2_MPLS_NXT_COMPARATOR_A", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_EGR_CFG_EGR2_MPLS_NXT_COMPARATOR_B[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR2_MPLS_NXT_COMPARATOR_B", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_EGR_CFG_EGR2_MPLS_FLOW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR2_MPLS_FLOW_CONTROL", 0x00000000, 0x00000001, 0x00000001},
    {"EGR2_MPLS_LABEL_RANGE_LOWER_0", 0x00000001, 0x00000001, 0x00000001},
    {"EGR2_MPLS_LABEL_RANGE_UPPER_0", 0x00000002, 0x00000001, 0x00000001},
    {"EGR2_MPLS_LABEL_RANGE_LOWER_1", 0x00000003, 0x00000001, 0x00000001},
    {"EGR2_MPLS_LABEL_RANGE_UPPER_1", 0x00000004, 0x00000001, 0x00000001},
    {"EGR2_MPLS_LABEL_RANGE_LOWER_2", 0x00000005, 0x00000001, 0x00000001},
    {"EGR2_MPLS_LABEL_RANGE_UPPER_2", 0x00000006, 0x00000001, 0x00000001},
    {"EGR2_MPLS_LABEL_RANGE_LOWER_3", 0x00000007, 0x00000001, 0x00000001},
    {"EGR2_MPLS_LABEL_RANGE_UPPER_3", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_EGR_CFG_EGR2_PTP_FLOW[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR2_PTP_FLOW_ENA", 0x00000000, 0x00000001, 0x00000001},
    {"EGR2_PTP_FLOW_MATCH_UPPER", 0x00000001, 0x00000001, 0x00000001},
    {"EGR2_PTP_FLOW_MATCH_LOWER", 0x00000002, 0x00000001, 0x00000001},
    {"EGR2_PTP_FLOW_MASK_UPPER", 0x00000003, 0x00000001, 0x00000001},
    {"EGR2_PTP_FLOW_MASK_LOWER", 0x00000004, 0x00000001, 0x00000001},
    {"EGR2_PTP_DOMAIN_RANGE", 0x00000005, 0x00000001, 0x00000001},
    {"EGR2_PTP_ACTION", 0x00000006, 0x00000001, 0x00000001},
    {"EGR2_PTP_ACTION_2", 0x00000007, 0x00000001, 0x00000001},
    {"EGR2_PTP_ZERO_FIELD_CTL", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_EGR_CFG_EGR2_FRAME_SIG_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR2_FSB_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"EGR2_FSB_MAP_REG_0", 0x00000001, 0x00000001, 0x00000001},
    {"EGR2_FSB_MAP_REG_1", 0x00000002, 0x00000001, 0x00000001},
    {"EGR2_FSB_MAP_REG_2", 0x00000003, 0x00000001, 0x00000001},
    {"EGR2_FSB_MAP_REG_3", 0x00000004, 0x00000001, 0x00000001},
    {"EGR2_FSB_MAP_REG_4", 0x00000005, 0x00000001, 0x00000001},
    {"EGR2_FSB_MAP_REG_5", 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_ANA2_EGR_CFG_EGR2_ACH_COMPARATOR_A[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EGR2_ACH_PROT_MATCH_UPPER_A", 0x00000000, 0x00000001, 0x00000001},
    {"EGR2_ACH_PROT_MATCH_LOWER_A", 0x00000001, 0x00000001, 0x00000001},
    {"EGR2_ACH_PROT_MASK_UPPER_A", 0x00000002, 0x00000001, 0x00000001},
    {"EGR2_ACH_PROT_MASK_LOWER_A", 0x00000003, 0x00000001, 0x00000001},
    {"EGR2_ACH_PROT_OFFSET_A", 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_PTP_ANA2_EGR_CFG[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"EGR2_ETH1_NXT_PROTOCOL_A", 0x0000c800, 0x00000001, 0x00000010, regs_within_PTP_ANA2_EGR_CFG_EGR2_ETH1_NXT_PROTOCOL_A},
    {"EGR2_ETH1_NXT_PROTOCOL_B", 0x0000c810, 0x00000001, 0x00000010, regs_within_PTP_ANA2_EGR_CFG_EGR2_ETH1_NXT_PROTOCOL_B},
    {"EGR2_ETH1_FLOW_CFG", 0x0000c820, 0x00000008, 0x00000010, regs_within_PTP_ANA2_EGR_CFG_EGR2_ETH1_FLOW_CFG},
    {"EGR2_ETH2_NXT_PROTOCOL_A", 0x0000c8a0, 0x00000001, 0x00000010, regs_within_PTP_ANA2_EGR_CFG_EGR2_ETH2_NXT_PROTOCOL_A},
#ifndef VTSS_RELEASE
    {"EGR2_ETH2_NXT_PROTOCOL_B", 0x0000c8b0, 0x00000001, 0x00000010, regs_within_PTP_ANA2_EGR_CFG_EGR2_ETH2_NXT_PROTOCOL_B},
#endif
    {"EGR2_ETH2_FLOW_CFG", 0x0000c8c0, 0x00000008, 0x00000010, regs_within_PTP_ANA2_EGR_CFG_EGR2_ETH2_FLOW_CFG},
    {"EGR2_MPLS_NXT_COMPARATOR_A", 0x0000c940, 0x00000001, 0x00000010, regs_within_PTP_ANA2_EGR_CFG_EGR2_MPLS_NXT_COMPARATOR_A},
#ifndef VTSS_RELEASE
    {"EGR2_MPLS_NXT_COMPARATOR_B", 0x0000c950, 0x00000001, 0x00000010, regs_within_PTP_ANA2_EGR_CFG_EGR2_MPLS_NXT_COMPARATOR_B},
#endif
    {"EGR2_MPLS_FLOW_CFG", 0x0000c960, 0x00000008, 0x00000010, regs_within_PTP_ANA2_EGR_CFG_EGR2_MPLS_FLOW_CFG},
    {"EGR2_PTP_FLOW", 0x0000c9e0, 0x00000006, 0x00000010, regs_within_PTP_ANA2_EGR_CFG_EGR2_PTP_FLOW},
    {"EGR2_FRAME_SIG_CFG", 0x0000ca40, 0x00000001, 0x00000007, regs_within_PTP_ANA2_EGR_CFG_EGR2_FRAME_SIG_CFG},
#ifndef VTSS_RELEASE
    {"EGR2_ACH_COMPARATOR_A", 0x0000ca47, 0x00000001, 0x00000005, regs_within_PTP_ANA2_EGR_CFG_EGR2_ACH_COMPARATOR_A},
#endif
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_CROSS_CONNECT_EXP_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CFG1", 0x00000000, 0x00000001, 0x00000001},
    {"COND_CFG", 0x00000001, 0x00000001, 0x00000001},
    {"RESET", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CROSS_CONNECT_EXP_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STAT1", 0x00000000, 0x00000001, 0x00000001},
    {"INTR_EN", 0x00000001, 0x00000001, 0x00000001},
    {"INTR", 0x00000002, 0x00000001, 0x00000001},
    {"INTR_EN2", 0x00000003, 0x00000001, 0x00000001},
    {"INTR2", 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CROSS_CONNECT_HOST0_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"H0_SRC_SEL", 0x00000000, 0x00000001, 0x00000001},
    {"H0_FILTER", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CROSS_CONNECT_HOST1_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"H1_SRC_SEL", 0x00000000, 0x00000001, 0x00000001},
    {"H1_FILTER", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CROSS_CONNECT_HOST2_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"H2_SRC_SEL", 0x00000000, 0x00000001, 0x00000001},
    {"H2_FILTER", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CROSS_CONNECT_HOST3_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"H3_SRC_SEL", 0x00000000, 0x00000001, 0x00000001},
    {"H3_FILTER", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CROSS_CONNECT_LINE0_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"L0_SRC_SEL", 0x00000000, 0x00000001, 0x00000001},
    {"L0_FILTER", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CROSS_CONNECT_LINE1_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"L1_SRC_SEL", 0x00000000, 0x00000001, 0x00000001},
    {"L1_FILTER", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CROSS_CONNECT_LINE2_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"L2_SRC_SEL", 0x00000000, 0x00000001, 0x00000001},
    {"L2_FILTER", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CROSS_CONNECT_LINE3_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"L3_SRC_SEL", 0x00000000, 0x00000001, 0x00000001},
    {"L3_FILTER", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CROSS_CONNECT_W_P_SWITCH_0[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"WPS0_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"WPS0_FAILOVER_CTRL", 0x00000001, 0x00000001, 0x00000001},
    {"WPS0_STATUS", 0x00000002, 0x00000001, 0x00000001},
    {"WPS0_FAULT_COND", 0x00000003, 0x00000001, 0x00000001},
    {"WPS0_FILTER_COUNTB_MSB", 0x00000004, 0x00000001, 0x00000001},
    {"WPS0_FILTER_COUNTB_LSB", 0x00000005, 0x00000001, 0x00000001},
    {"WPS0_FILTER_COUNTA_MSB", 0x00000006, 0x00000001, 0x00000001},
    {"WPS0_FILTER_COUNTA_LSB", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CROSS_CONNECT_W_P_SWITCH_1[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"WPS1_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"WPS1_FAILOVER_CTRL", 0x00000001, 0x00000001, 0x00000001},
    {"WPS1_STATUS", 0x00000002, 0x00000001, 0x00000001},
    {"WPS1_FAULT_COND", 0x00000003, 0x00000001, 0x00000001},
    {"WPS1_FILTER_COUNTB_MSB", 0x00000004, 0x00000001, 0x00000001},
    {"WPS1_FILTER_COUNTB_LSB", 0x00000005, 0x00000001, 0x00000001},
    {"WPS1_FILTER_COUNTA_MSB", 0x00000006, 0x00000001, 0x00000001},
    {"WPS1_FILTER_COUNTA_LSB", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CROSS_CONNECT_EXP_DEBUG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EXP_DEBUG0", 0x00000000, 0x00000001, 0x00000001},
    {"EXP_DEBUG1", 0x00000001, 0x00000001, 0x00000001},
    {"EXP_DEBUG2", 0x00000002, 0x00000001, 0x00000001},
    {"EXP_DEBUG3", 0x00000003, 0x00000001, 0x00000001},
    {"EXP_DEBUG4", 0x00000004, 0x00000001, 0x00000001},
    {"EXP_DEBUG5", 0x00000005, 0x00000001, 0x00000001},
    {"EXP_DEBUG6", 0x00000006, 0x00000001, 0x00000001},
    {"EXP_DEBUG7", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_CROSS_CONNECT[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"EXP_CFG", 0x0000f100, 0x00000001, 0x00000003, regs_within_CROSS_CONNECT_EXP_CFG},
    {"EXP_STATUS", 0x0000f103, 0x00000001, 0x00000005, regs_within_CROSS_CONNECT_EXP_STATUS},
    {"HOST0_CFG", 0x0000f108, 0x00000001, 0x00000002, regs_within_CROSS_CONNECT_HOST0_CFG},
    {"HOST1_CFG", 0x0000f10a, 0x00000001, 0x00000002, regs_within_CROSS_CONNECT_HOST1_CFG},
    {"HOST2_CFG", 0x0000f10c, 0x00000001, 0x00000002, regs_within_CROSS_CONNECT_HOST2_CFG},
    {"HOST3_CFG", 0x0000f10e, 0x00000001, 0x00000002, regs_within_CROSS_CONNECT_HOST3_CFG},
    {"LINE0_CFG", 0x0000f110, 0x00000001, 0x00000002, regs_within_CROSS_CONNECT_LINE0_CFG},
    {"LINE1_CFG", 0x0000f112, 0x00000001, 0x00000002, regs_within_CROSS_CONNECT_LINE1_CFG},
    {"LINE2_CFG", 0x0000f114, 0x00000001, 0x00000002, regs_within_CROSS_CONNECT_LINE2_CFG},
    {"LINE3_CFG", 0x0000f116, 0x00000001, 0x00000002, regs_within_CROSS_CONNECT_LINE3_CFG},
    {"W_P_SWITCH_0", 0x0000f118, 0x00000001, 0x00000008, regs_within_CROSS_CONNECT_W_P_SWITCH_0},
    {"W_P_SWITCH_1", 0x0000f120, 0x00000001, 0x00000008, regs_within_CROSS_CONNECT_W_P_SWITCH_1},
    {"EXP_DEBUG", 0x0000f178, 0x00000001, 0x00000008, regs_within_CROSS_CONNECT_EXP_DEBUG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_GPIO_CTRL_GPIO_CFG_STAT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GPIO_CFG1", 0x00000000, 0x00000001, 0x00000001},
    {"GPIO_CFG0", 0x00000001, 0x00000001, 0x00000001},
    {"GPIO_OUT_INV_CFG1", 0x00000002, 0x00000001, 0x00000001},
    {"GPIO_OUT_INV_CFG0", 0x00000003, 0x00000001, 0x00000001},
    {"GPIO_STAT1", 0x00000004, 0x00000001, 0x00000001},
    {"GPIO_STAT0", 0x00000005, 0x00000001, 0x00000001},
    {"GPIO_OUT_STAT1", 0x00000006, 0x00000001, 0x00000001},
    {"GPIO_OUT_STAT0", 0x00000007, 0x00000001, 0x00000001},
    {"GPIO_CHANGE1", 0x00000008, 0x00000001, 0x00000001},
    {"GPIO_CHANGE0", 0x00000009, 0x00000001, 0x00000001},
    {"GPIO_FUN_SEL1", 0x0000000a, 0x00000001, 0x00000001},
    {"GPIO_FUN_SEL0", 0x0000000b, 0x00000001, 0x00000001},
    {"GPIO_OUT_PP1", 0x0000000c, 0x00000001, 0x00000001},
    {"GPIO_OUT_PP0", 0x0000000d, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_GPIO_CTRL_INTR_CFG_STAT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INTR_SRC_EN", 0x00000000, 0x00000002, 0x00000001},
    {"INTR_STAT", 0x00000002, 0x00000002, 0x00000001},
    {"GPIO_INTR_SRC_EN1", 0x00000004, 0x00000002, 0x00000001},
    {"GPIO_INTR_SRC_EN", 0x00000006, 0x00000002, 0x00000001},
    {"GPIO_INTR_STAT1", 0x00000008, 0x00000002, 0x00000001},
    {"GPIO_INTR_STAT0", 0x0000000a, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_GPIO_CTRL[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"GPIO_CFG_STAT", 0x0000f200, 0x00000001, 0x0000000e, regs_within_GPIO_CTRL_GPIO_CFG_STAT},
    {"INTR_CFG_STAT", 0x0000f20e, 0x00000001, 0x0000000c, regs_within_GPIO_CTRL_INTR_CFG_STAT},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_MCU_IO_MNGT_MISC_DEVICE_INFO[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DEVICE_ID_REG", 0x00000000, 0x00000001, 0x00000001},
    {"DEVICE_OTP_REVISION_REG", 0x00000001, 0x00000001, 0x00000001},
    {"DEVICE_SILICON_REVISION_REG", 0x00000002, 0x00000001, 0x00000001},
    {"DEVICE_FEATURE_DISABLE_REG", 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MCU_IO_MNGT_MISC_MIM_SPARE_RW_REG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MIM_SPARE_RW_REG", 0x00000000, 0x00000004, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MCU_IO_MNGT_MISC_MIM_SPARE_STS_REG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MIM_SPARE_STS_REG", 0x00000000, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MCU_IO_MNGT_MISC_MCU_RESET_INFO[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MCU_RESET_REASON_STATUS", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MCU_IO_MNGT_MISC_MCU_WDT_STS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MCU_WDT_STS", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MCU_IO_MNGT_MISC_MCU_WDT_INTR_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MCU_WDT_INTR_EN_REG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MCU_IO_MNGT_MISC_BIST0_REG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"BIST0_GO", 0x00000000, 0x00000001, 0x00000001},
    {"BIST0_STATUS", 0x00000001, 0x00000001, 0x00000001},
    {"BIST0_RESULT", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MCU_IO_MNGT_MISC_POST0_REG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"POST0_STATUS", 0x00000000, 0x00000001, 0x00000001},
    {"P0_BIST_STATUS", 0x00000001, 0x00000001, 0x00000001},
    {"P0_BIST_RESULT", 0x00000002, 0x00000001, 0x00000001},
    {"P0_INIT_STATUS", 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MCU_IO_MNGT_MISC_POST1_REG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"POST1_POST_STATUS", 0x00000000, 0x00000001, 0x00000001},
    {"POST1_SLICE0_BIST_STATUS", 0x00000001, 0x00000001, 0x00000001},
    {"POST1_SLICE1_BIST_STATUS", 0x00000002, 0x00000001, 0x00000001},
    {"POST1_SLICE2_BIST_STATUS", 0x00000003, 0x00000001, 0x00000001},
    {"POST1_SLICE3_BIST_STATUS", 0x00000004, 0x00000001, 0x00000001},
    {"POST1_SLICE0_BIST_RESULT", 0x00000005, 0x00000001, 0x00000001},
    {"POST1_SLICE1_BIST_RESULT", 0x00000006, 0x00000001, 0x00000001},
    {"POST1_SLICE2_BIST_RESULT", 0x00000007, 0x00000001, 0x00000001},
    {"POST1_SLICE3_BIST_RESULT", 0x00000008, 0x00000001, 0x00000001},
    {"POST1_SLICE0_INIT_STATUS", 0x00000009, 0x00000001, 0x00000001},
    {"POST1_SLICE1_INIT_STATUS", 0x0000000a, 0x00000001, 0x00000001},
    {"POST1_SLICE2_INIT_STATUS", 0x0000000b, 0x00000001, 0x00000001},
    {"POST1_SLICE3_INIT_STATUS", 0x0000000c, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MCU_IO_MNGT_MISC_IRAM_ECC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IRAM_ECC_CTL", 0x00000000, 0x00000001, 0x00000001},
    {"IRAM_ECC_SR", 0x00000001, 0x00000001, 0x00000001},
    {"IRAM_ECC_INIT_DONE_INTR_EN", 0x00000004, 0x00000001, 0x00000001},
    {"IRAM_ECC_INIT_DONE_INTR_STS", 0x00000005, 0x00000001, 0x00000001},
    {"IRAM_ECC_INTR_EN", 0x00000006, 0x00000001, 0x00000001},
    {"IRAM_ECC_INTR_STS", 0x00000007, 0x00000001, 0x00000001},
    {"IRAM_ECC_LANE_FCR", 0x00000010, 0x00000004, 0x00000010},
    {"IRAM_ECC_LANE_EADDR", 0x00000014, 0x00000004, 0x00000010},
    {"IRAM_ECC_LANE_EDPTR", 0x00000015, 0x00000004, 0x00000010},
    {"IRAM_ECC_LANE_SCNT", 0x00000016, 0x00000004, 0x00000010},
    {"IRAM_ECC_LANE_DCNT", 0x00000017, 0x00000004, 0x00000010},
    {"IRAM_ECC_LANE_INTR_EN", 0x00000018, 0x00000004, 0x00000010},
    {"IRAM_ECC_LANE_INTR_STS", 0x00000019, 0x00000004, 0x00000010},
    {"IRAM_ECC_LANE_FADDR", 0x0000001c, 0x00000004, 0x00000010},
    {"IRAM_ECC_LANE_FDPTR", 0x0000001d, 0x00000004, 0x00000010},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MCU_IO_MNGT_MISC_DRAM_ECC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DRAM_ECC_CTL", 0x00000000, 0x00000001, 0x00000001},
    {"DRAM_ECC_SR", 0x00000001, 0x00000001, 0x00000001},
    {"DRAM_ECC_INIT_DONE_INTR_EN", 0x00000004, 0x00000001, 0x00000001},
    {"DRAM_ECC_INIT_DONE_INTR_STS", 0x00000005, 0x00000001, 0x00000001},
    {"DRAM_ECC_INTR_EN", 0x00000006, 0x00000001, 0x00000001},
    {"DRAM_ECC_INTR_STS", 0x00000007, 0x00000001, 0x00000001},
    {"DRAM_ECC_LANE_FCR", 0x00000010, 0x00000004, 0x00000010},
    {"DRAM_ECC_LANE_EADDR", 0x00000014, 0x00000004, 0x00000010},
    {"DRAM_ECC_LANE_EDPTR", 0x00000015, 0x00000004, 0x00000010},
    {"DRAM_ECC_LANE_SCNT", 0x00000016, 0x00000004, 0x00000010},
    {"DRAM_ECC_LANE_DCNT", 0x00000017, 0x00000004, 0x00000010},
    {"DRAM_ECC_LANE_INTR_EN", 0x00000018, 0x00000004, 0x00000010},
    {"DRAM_ECC_LANE_INTR_STS", 0x00000019, 0x00000004, 0x00000010},
    {"DRAM_ECC_LANE_FADDR", 0x0000001c, 0x00000004, 0x00000010},
    {"DRAM_ECC_LANE_FDPTR", 0x0000001d, 0x00000004, 0x00000010},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MCU_IO_MNGT_MISC_MBOX_ECC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MBOX_ECC_CTL", 0x00000000, 0x00000001, 0x00000001},
    {"MBOX_ECC_SR", 0x00000001, 0x00000001, 0x00000001},
    {"MBOX_ECC_INIT_DONE_INTR_EN", 0x00000004, 0x00000001, 0x00000001},
    {"MBOX_ECC_INIT_DONE_INTR_STS", 0x00000005, 0x00000001, 0x00000001},
    {"MBOX_ECC_FCR", 0x00000010, 0x00000001, 0x00000001},
    {"MBOX_ECC_EADDR", 0x00000014, 0x00000001, 0x00000001},
    {"MBOX_ECC_EDPTR", 0x00000015, 0x00000001, 0x00000001},
    {"MBOX_ECC_SCNT", 0x00000016, 0x00000001, 0x00000001},
    {"MBOX_ECC_DCNT", 0x00000017, 0x00000001, 0x00000001},
    {"MBOX_ECC_INTR_EN", 0x00000018, 0x00000001, 0x00000001},
    {"MBOX_ECC_INTR_STS", 0x00000019, 0x00000001, 0x00000001},
    {"MBOX_ECC_FADDR", 0x0000001c, 0x00000001, 0x00000001},
    {"MBOX_ECC_FDPTR", 0x0000001d, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MCU_IO_MNGT_MISC_MCU_BOOT_INFO[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MCU_BOOT_STATUS_REG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MCU_IO_MNGT_MISC_MCU_CONFIG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MCU_SS_CLK_CFG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MCU_IO_MNGT_MISC_MIM_DEBUG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MIM_DEBUG_REG_7", 0x00000000, 0x00000001, 0x00000001},
    {"MIM_DEBUG_REG_6", 0x00000001, 0x00000001, 0x00000001},
    {"MIM_DEBUG_REG_5", 0x00000002, 0x00000001, 0x00000001},
    {"MIM_DEBUG_REG_4", 0x00000003, 0x00000001, 0x00000001},
    {"MIM_DEBUG_REG_3", 0x00000004, 0x00000001, 0x00000001},
    {"MIM_DEBUG_REG_2", 0x00000005, 0x00000001, 0x00000001},
    {"MIM_DEBUG_REG_1", 0x00000006, 0x00000001, 0x00000001},
    {"MIM_DEBUG_REG_0", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_MCU_IO_MNGT_MISC[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEVICE_INFO", 0x00000000, 0x00000001, 0x00000004, regs_within_MCU_IO_MNGT_MISC_DEVICE_INFO},
    {"MIM_SPARE_RW_REG", 0x00000004, 0x00000001, 0x00000004, regs_within_MCU_IO_MNGT_MISC_MIM_SPARE_RW_REG},
    {"MIM_SPARE_STS_REG", 0x00000008, 0x00000001, 0x00000002, regs_within_MCU_IO_MNGT_MISC_MIM_SPARE_STS_REG},
    {"MCU_RESET_INFO", 0x0000000a, 0x00000001, 0x00000001, regs_within_MCU_IO_MNGT_MISC_MCU_RESET_INFO},
    {"MCU_WDT_STS", 0x00000010, 0x00000001, 0x00000001, regs_within_MCU_IO_MNGT_MISC_MCU_WDT_STS},
    {"MCU_WDT_INTR_CFG", 0x00000011, 0x00000001, 0x00000001, regs_within_MCU_IO_MNGT_MISC_MCU_WDT_INTR_CFG},
    {"BIST0_REG", 0x00000020, 0x00000001, 0x00000003, regs_within_MCU_IO_MNGT_MISC_BIST0_REG},
    {"POST0_REG", 0x00000040, 0x00000001, 0x00000004, regs_within_MCU_IO_MNGT_MISC_POST0_REG},
    {"POST1_REG", 0x00000080, 0x00000001, 0x00000010, regs_within_MCU_IO_MNGT_MISC_POST1_REG},
    {"IRAM_ECC", 0x00000100, 0x00000001, 0x0000004e, regs_within_MCU_IO_MNGT_MISC_IRAM_ECC},
    {"DRAM_ECC", 0x00000150, 0x00000001, 0x0000004e, regs_within_MCU_IO_MNGT_MISC_DRAM_ECC},
    {"MBOX_ECC", 0x000001a0, 0x00000001, 0x0000001e, regs_within_MCU_IO_MNGT_MISC_MBOX_ECC},
    {"MCU_BOOT_INFO", 0x000001e0, 0x00000001, 0x00000001, regs_within_MCU_IO_MNGT_MISC_MCU_BOOT_INFO},
    {"MCU_CONFIG", 0x000001f0, 0x00000001, 0x00000001, regs_within_MCU_IO_MNGT_MISC_MCU_CONFIG},
#ifndef VTSS_RELEASE
    {"MIM_DEBUG", 0x000001f8, 0x00000001, 0x00000008, regs_within_MCU_IO_MNGT_MISC_MIM_DEBUG},
#endif
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_MCU_MAILBOX_MAILBOX_FLAG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MAILBOX_FLAG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MCU_MAILBOX_MAILBOX_INT_MASK[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MAILBOX_MCU_INT_MASK", 0x00000000, 0x00000001, 0x00000001},
    {"MAILBOX_HOST_INT_MASK", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MCU_MAILBOX_MAILBOX_DATA[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MAILBOX_DATA_REG", 0x00000000, 0x00000200, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_MCU_MAILBOX[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"MAILBOX_FLAG", 0x0000da00, 0x00000001, 0x00000001, regs_within_MCU_MAILBOX_MAILBOX_FLAG},
    {"MAILBOX_INT_MASK", 0x0000da01, 0x00000001, 0x00000002, regs_within_MCU_MAILBOX_MAILBOX_INT_MASK},
    {"MAILBOX_DATA", 0x0000d800, 0x00000001, 0x00000200, regs_within_MCU_MAILBOX_MAILBOX_DATA},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_GLOBAL_STRAP_INFO[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STRAP_READ_REG", 0x00000000, 0x00000001, 0x00000001},
    {"STRAP_OVERRIDE_REG", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"BLOCK_LEVEL_SOFTWARE_RESET1", 0x00000000, 0x00000001, 0x00000001},
    {"BLOCK_LEVEL_SOFTWARE_RESET2", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_GLOBAL_TEMP_SENSOR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TEMP_SENSOR_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"TEMP_SENSOR_CFG_0", 0x00000001, 0x00000001, 0x00000001},
    {"TEMP_SENSOR_CFG_1", 0x00000002, 0x00000001, 0x00000001},
    {"TEMP_SENSOR_STAT", 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_GLOBAL_WARM_RESTART_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"WARM_RESTART_REG", 0x00000000, 0x00000004, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_GLOBAL_SPI_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SPI_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_GLOBAL_ROSC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"ROSC_CFG", 0x00000000, 0x00000006, 0x00000001},
    {"ROSC_MEASURE_CFG_0", 0x00000008, 0x00000001, 0x00000001},
    {"ROSC_MEASURE_CFG_1", 0x00000009, 0x00000001, 0x00000001},
    {"ROSC_FREQ_CNT", 0x0000000a, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_GLOBAL_PAD[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IO_PAD_CTRL", 0x00000000, 0x00000050, 0x00000001},
    {"LVDS_PAD_CTRL", 0x00000050, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_GLOBAL_TEST_STRAP_INFO[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TEST_STRAP_READ", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_GLOBAL_GLB_SPARE_REG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GLB_SPARE_RW_REG", 0x00000000, 0x00000004, 0x00000001},
    {"GLB_SPARE_STS_REG", 0x00000004, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_GLOBAL_FPGA_REVISION[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TYPE_A_FPGA_REV_H_REG", 0x00000000, 0x00000001, 0x00000001},
    {"TYPE_A_FPGA_REV_L_REG", 0x00000001, 0x00000001, 0x00000001},
    {"TYPE_B_FPGA_REV_H_REG", 0x00000002, 0x00000001, 0x00000001},
    {"TYPE_B_FPGA_REV_L_REG", 0x00000003, 0x00000001, 0x00000001},
    {"TYPE_C_FPGA_REV_H_REG", 0x00000004, 0x00000001, 0x00000001},
    {"TYPE_C_FPGA_REV_L_REG", 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_GLOBAL[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"STRAP_INFO", 0x00000200, 0x00000001, 0x00000002, regs_within_GLOBAL_STRAP_INFO},
    {"BLOCK_LEVEL_SOFTWARE_RESET", 0x00000202, 0x00000001, 0x00000002, regs_within_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET},
    {"TEMP_SENSOR", 0x00000204, 0x00000001, 0x00000004, regs_within_GLOBAL_TEMP_SENSOR},
    {"WARM_RESTART_REGS", 0x00000208, 0x00000001, 0x00000004, regs_within_GLOBAL_WARM_RESTART_REGS},
    {"SPI_CTRL", 0x0000020d, 0x00000001, 0x00000001, regs_within_GLOBAL_SPI_CTRL},
#ifndef VTSS_RELEASE
    {"ROSC", 0x00000240, 0x00000001, 0x0000000b, regs_within_GLOBAL_ROSC},
#endif
    {"PAD", 0x00000280, 0x00000001, 0x00000051, regs_within_GLOBAL_PAD},
    {"TEST_STRAP_INFO", 0x00000380, 0x00000001, 0x00000001, regs_within_GLOBAL_TEST_STRAP_INFO},
    {"GLB_SPARE_REG", 0x000003f0, 0x00000001, 0x00000006, regs_within_GLOBAL_GLB_SPARE_REG},
    {"FPGA_REVISION", 0x000003f8, 0x00000001, 0x00000006, regs_within_GLOBAL_FPGA_REVISION},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_CLK_CFG_SYSPLL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SYSPLL_CMD_REG", 0x00000000, 0x00000001, 0x00000001},
    {"SYSPLL_RANGE_REG", 0x00000001, 0x00000001, 0x00000001},
    {"SYSPLL_DIVR_REG", 0x00000002, 0x00000001, 0x00000001},
    {"SYSPLL_DIVQ_REG", 0x00000003, 0x00000001, 0x00000001},
    {"SYSPLL_DIVFF_HI_REG", 0x00000004, 0x00000001, 0x00000001},
    {"SYSPLL_DIVFF_LO_REG", 0x00000005, 0x00000001, 0x00000001},
    {"SYSPLL_DIVFI_REG", 0x00000006, 0x00000001, 0x00000001},
    {"SYSPLL_STS_REG", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CLK_CFG_LTCPLL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LTCPLL_CMD_REG", 0x00000000, 0x00000001, 0x00000001},
    {"LTCPLL_RANGE_REG", 0x00000001, 0x00000001, 0x00000001},
    {"LTCPLL_DIVR_REG", 0x00000002, 0x00000001, 0x00000001},
    {"LTCPLL_DIVQ_REG", 0x00000003, 0x00000001, 0x00000001},
    {"LTCPLL_DIVFF_HI_REG", 0x00000004, 0x00000001, 0x00000001},
    {"LTCPLL_DIVFF_LO_REG", 0x00000005, 0x00000001, 0x00000001},
    {"LTCPLL_DIVFI_REG", 0x00000006, 0x00000001, 0x00000001},
    {"LTCPLL_STS_REG", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CLK_CFG_RCVRD_CLK_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RCVRD_CLKA_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"RCVRD_CLKB_CFG", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CLK_CFG_LTC_CLK_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LTC_CLK_CFG_REG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_CLK_CFG[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"SYSPLL", 0x00000600, 0x00000001, 0x00000008, regs_within_CLK_CFG_SYSPLL},
    {"LTCPLL", 0x00000608, 0x00000001, 0x00000008, regs_within_CLK_CFG_LTCPLL},
    {"RCVRD_CLK_CFG", 0x00000610, 0x00000001, 0x00000002, regs_within_CLK_CFG_RCVRD_CLK_CFG},
    {"LTC_CLK_CFG", 0x00000612, 0x00000001, 0x00000001, regs_within_CLK_CFG_LTC_CLK_CFG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_PTP_LTC_PHASE_DETECTOR_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PHAD_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"PHAD_CYC_STAT", 0x00000001, 0x00000001, 0x00000001},
    {"PHAD_ERR_STAT", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_LTC_PTP_PINS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PTP_PIN_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"PTP_TOD_SEC_MSB", 0x00000001, 0x00000001, 0x00000001},
    {"PTP_TOD_SEC_LSB", 0x00000002, 0x00000001, 0x00000001},
    {"PTP_TOD_NSEC", 0x00000003, 0x00000001, 0x00000001},
    {"PTP_TOD_NSEC_FRAC", 0x00000004, 0x00000001, 0x00000001},
    {"NTP_NSEC", 0x00000005, 0x00000001, 0x00000001},
    {"PIN_WF_HIGH_PERIOD", 0x00000006, 0x00000001, 0x00000001},
    {"PIN_WF_LOW_PERIOD", 0x00000007, 0x00000001, 0x00000001},
    {"PIN_IOBOUNCH_DELAY", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_LTC_PTP_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PTP_DOM_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"PTP_CLK_REF_CFG", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_LTC_PTP_INTR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PTP_PIN_INTR", 0x00000000, 0x00000001, 0x00000001},
    {"PTP_PIN_INTR_ENA", 0x00000001, 0x00000001, 0x00000001},
    {"LTC_MEAS_INTR", 0x00000002, 0x00000001, 0x00000001},
    {"LTC_MEAS_INTR_ENA", 0x00000003, 0x00000001, 0x00000001},
    {"SER_TOD_STORE_INTR", 0x00000004, 0x00000001, 0x00000001},
    {"SER_TOD_STORE_INT_ENA", 0x00000005, 0x00000001, 0x00000001},
    {"SER_TOD_LOAD_INTR", 0x00000006, 0x00000001, 0x00000001},
    {"SER_TOD_LOAD_INT_ENA", 0x00000007, 0x00000001, 0x00000001},
    {"PTP_INTR_IDENT", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_LTC_PTP_TOD_DOMAINS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CLK_PER_CFG", 0x00000000, 0x00000002, 0x00000001},
    {"PTP_CUR_NSEC", 0x00000002, 0x00000001, 0x00000001},
    {"PTP_CUR_NSEC_FRAC", 0x00000003, 0x00000001, 0x00000001},
    {"PTP_CUR_SEC_LSB", 0x00000004, 0x00000001, 0x00000001},
    {"PTP_CUR_SEC_MSB", 0x00000005, 0x00000001, 0x00000001},
    {"NTP_CUR_NSEC", 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_LTC_PTP_LOAD_STORE_DELAY_CONFIGURATION[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PIN_LOAD_DELAY_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"PIN_STORE_DELAY_CFG", 0x00000001, 0x00000004, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_LTC_PTP_SER_TOD_LOAD_STORE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PTP_SER_TOD_LOAD_STORE_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"PTP_SER_TOD_LOAD_PERIOD_CFG", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_LTC_DRIFT_MEAS_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LTC_MEAS_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"MEAS_COUNT", 0x00000001, 0x00000002, 0x00000001},
    {"MEAS_THRESHOLD", 0x00000003, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_LTC_DRIFT_MEAS_TOD[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PTP_TOD_1_SEC_MSB", 0x00000000, 0x00000001, 0x00000001},
    {"PTP_TOD_1_SEC_LSB", 0x00000001, 0x00000001, 0x00000001},
    {"PTP_TOD_1_NSEC", 0x00000002, 0x00000001, 0x00000001},
    {"PTP_TOD_1_NSEC_FRAC", 0x00000003, 0x00000001, 0x00000001},
    {"PTP_TOD_2_SEC_MSB", 0x00000004, 0x00000001, 0x00000001},
    {"PTP_TOD_2_SEC_LSB", 0x00000005, 0x00000001, 0x00000001},
    {"PTP_TOD_2_NSEC", 0x00000006, 0x00000001, 0x00000001},
    {"PTP_TOD_2_NSEC_FRAC", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_LTC_DRIFT_PHASE_DETECTOR_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DF_PHAD_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"DF_PHAD_CYC_STAT", 0x00000001, 0x00000001, 0x00000001},
    {"DF_PHAD_ERR_STAT", 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_LTC_LTC_SPARE_REG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LTC_SPARE_REG_CFG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_LTC_LTC_DEBUG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LTC_DEBUG0_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"LTC_DEBUG1_CFG", 0x00000001, 0x00000001, 0x00000001},
    {"LTC_DEBUG2_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"LTC_DEBUG3_CFG", 0x00000003, 0x00000001, 0x00000001},
    {"LTC_DEBUG4_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"LTC_DEBUG5_CFG", 0x00000005, 0x00000001, 0x00000001},
    {"LTC_DEBUG6_CFG", 0x00000006, 0x00000001, 0x00000001},
    {"LTC_DEBUG7_CFG", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_PTP_LTC[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"PHASE_DETECTOR_CTRL", 0x0000d040, 0x00000004, 0x00000003, regs_within_PTP_LTC_PHASE_DETECTOR_CTRL},
    {"PTP_PINS", 0x0000d000, 0x00000004, 0x00000010, regs_within_PTP_LTC_PTP_PINS},
    {"PTP_CFG", 0x0000d04c, 0x00000001, 0x00000002, regs_within_PTP_LTC_PTP_CFG},
    {"PTP_INTR", 0x0000d04e, 0x00000001, 0x00000009, regs_within_PTP_LTC_PTP_INTR},
    {"PTP_TOD_DOMAINS", 0x0000d057, 0x00000001, 0x00000007, regs_within_PTP_LTC_PTP_TOD_DOMAINS},
    {"PTP_LOAD_STORE_DELAY_CONFIGURATION", 0x0000d05e, 0x00000001, 0x00000005, regs_within_PTP_LTC_PTP_LOAD_STORE_DELAY_CONFIGURATION},
    {"PTP_SER_TOD_LOAD_STORE", 0x0000d063, 0x00000001, 0x00000002, regs_within_PTP_LTC_PTP_SER_TOD_LOAD_STORE},
    {"DRIFT_MEAS_CTRL", 0x0000d065, 0x00000001, 0x00000005, regs_within_PTP_LTC_DRIFT_MEAS_CTRL},
    {"DRIFT_MEAS_TOD", 0x0000d06a, 0x00000001, 0x00000008, regs_within_PTP_LTC_DRIFT_MEAS_TOD},
    {"DRIFT_PHASE_DETECTOR_CTRL", 0x0000d072, 0x00000001, 0x00000003, regs_within_PTP_LTC_DRIFT_PHASE_DETECTOR_CTRL},
    {"LTC_SPARE_REG", 0x0000d075, 0x00000001, 0x00000001, regs_within_PTP_LTC_LTC_SPARE_REG},
    {"LTC_DEBUG", 0x0000d0f8, 0x00000001, 0x00000008, regs_within_PTP_LTC_LTC_DEBUG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_PTP_STI_TS_FIFO_SI[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TS_FIFO_SI_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"TS_FIFO_SI_TX_CNT", 0x00000001, 0x00000004, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_STI_STI_SPARE_REG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STI_SPARE_REG_CFG", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_STI_STI_DEBUG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STI_DEBUG0_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"STI_DEBUG1_CFG", 0x00000001, 0x00000001, 0x00000001},
    {"STI_DEBUG2_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"STI_DEBUG3_CFG", 0x00000003, 0x00000001, 0x00000001},
    {"STI_DEBUG4_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"STI_DEBUG5_CFG", 0x00000005, 0x00000001, 0x00000001},
    {"STI_DEBUG6_CFG", 0x00000006, 0x00000001, 0x00000001},
    {"STI_DEBUG7_CFG", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_PTP_STI[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"TS_FIFO_SI", 0x0000d200, 0x00000001, 0x00000005, regs_within_PTP_STI_TS_FIFO_SI},
    {"STI_SPARE_REG", 0x0000d205, 0x00000001, 0x00000001, regs_within_PTP_STI_STI_SPARE_REG},
    {"STI_DEBUG", 0x0000d2f8, 0x00000001, 0x00000008, regs_within_PTP_STI_STI_DEBUG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_GLOBAL_FAST_RESET_FAST_ACCESS_RESET[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GLOBAL_FAST_RESET_0", 0x00000000, 0x00000001, 0x00000001},
    {"GLOBAL_FAST_RESET_1", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_GLOBAL_FAST_RESET[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"FAST_ACCESS_RESET", 0x00008000, 0x00000001, 0x00000002, regs_within_GLOBAL_FAST_RESET_FAST_ACCESS_RESET},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_ORG_VER2_0_DEVCPU_ORG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"IF_CFGSTAT", 0x00000001, 0x00000001, 0x00000001},
    {"ORG_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"ERR_CNTS", 0x00000003, 0x00000001, 0x00000001},
    {"TIMEOUT_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"GPR", 0x00000005, 0x00000001, 0x00000001},
    {"MAILBOX_SET", 0x00000006, 0x00000001, 0x00000001},
    {"MAILBOX_CLR", 0x00000007, 0x00000001, 0x00000001},
    {"MAILBOX", 0x00000008, 0x00000001, 0x00000001},
    {"SEMA_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"SEMA", 0x0000000a, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV_ORG_VER2_0[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEVCPU_ORG", 0x0000f800, 0x00000001, 0x00000012, regs_within_DEV_ORG_VER2_0_DEVCPU_ORG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_ORG_VER2_1_DEVCPU_ORG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"IF_CFGSTAT", 0x00000001, 0x00000001, 0x00000001},
    {"ORG_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"ERR_CNTS", 0x00000003, 0x00000001, 0x00000001},
    {"TIMEOUT_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"GPR", 0x00000005, 0x00000001, 0x00000001},
    {"MAILBOX_SET", 0x00000006, 0x00000001, 0x00000001},
    {"MAILBOX_CLR", 0x00000007, 0x00000001, 0x00000001},
    {"MAILBOX", 0x00000008, 0x00000001, 0x00000001},
    {"SEMA_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"SEMA", 0x0000000a, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV_ORG_VER2_1[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEVCPU_ORG", 0x0000f840, 0x00000001, 0x00000012, regs_within_DEV_ORG_VER2_1_DEVCPU_ORG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_ORG_VER2_2_DEVCPU_ORG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"IF_CFGSTAT", 0x00000001, 0x00000001, 0x00000001},
    {"ORG_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"ERR_CNTS", 0x00000003, 0x00000001, 0x00000001},
    {"TIMEOUT_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"GPR", 0x00000005, 0x00000001, 0x00000001},
    {"MAILBOX_SET", 0x00000006, 0x00000001, 0x00000001},
    {"MAILBOX_CLR", 0x00000007, 0x00000001, 0x00000001},
    {"MAILBOX", 0x00000008, 0x00000001, 0x00000001},
    {"SEMA_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"SEMA", 0x0000000a, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV_ORG_VER2_2[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEVCPU_ORG", 0x0000f880, 0x00000001, 0x00000012, regs_within_DEV_ORG_VER2_2_DEVCPU_ORG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_ORG_VER2_3_DEVCPU_ORG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"IF_CFGSTAT", 0x00000001, 0x00000001, 0x00000001},
    {"ORG_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"ERR_CNTS", 0x00000003, 0x00000001, 0x00000001},
    {"TIMEOUT_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"GPR", 0x00000005, 0x00000001, 0x00000001},
    {"MAILBOX_SET", 0x00000006, 0x00000001, 0x00000001},
    {"MAILBOX_CLR", 0x00000007, 0x00000001, 0x00000001},
    {"MAILBOX", 0x00000008, 0x00000001, 0x00000001},
    {"SEMA_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"SEMA", 0x0000000a, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV_ORG_VER2_3[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEVCPU_ORG", 0x0000f8c0, 0x00000001, 0x00000012, regs_within_DEV_ORG_VER2_3_DEVCPU_ORG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_ORG_VER2_4_DEVCPU_ORG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"IF_CFGSTAT", 0x00000001, 0x00000001, 0x00000001},
    {"ORG_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"ERR_CNTS", 0x00000003, 0x00000001, 0x00000001},
    {"TIMEOUT_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"GPR", 0x00000005, 0x00000001, 0x00000001},
    {"MAILBOX_SET", 0x00000006, 0x00000001, 0x00000001},
    {"MAILBOX_CLR", 0x00000007, 0x00000001, 0x00000001},
    {"MAILBOX", 0x00000008, 0x00000001, 0x00000001},
    {"SEMA_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"SEMA", 0x0000000a, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV_ORG_VER2_4[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEVCPU_ORG", 0x0000f900, 0x00000001, 0x00000012, regs_within_DEV_ORG_VER2_4_DEVCPU_ORG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_ORG_VER2_5_DEVCPU_ORG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"IF_CFGSTAT", 0x00000001, 0x00000001, 0x00000001},
    {"ORG_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"ERR_CNTS", 0x00000003, 0x00000001, 0x00000001},
    {"TIMEOUT_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"GPR", 0x00000005, 0x00000001, 0x00000001},
    {"MAILBOX_SET", 0x00000006, 0x00000001, 0x00000001},
    {"MAILBOX_CLR", 0x00000007, 0x00000001, 0x00000001},
    {"MAILBOX", 0x00000008, 0x00000001, 0x00000001},
    {"SEMA_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"SEMA", 0x0000000a, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV_ORG_VER2_5[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEVCPU_ORG", 0x0000f940, 0x00000001, 0x00000012, regs_within_DEV_ORG_VER2_5_DEVCPU_ORG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_ORG_VER2_6_DEVCPU_ORG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"IF_CFGSTAT", 0x00000001, 0x00000001, 0x00000001},
    {"ORG_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"ERR_CNTS", 0x00000003, 0x00000001, 0x00000001},
    {"TIMEOUT_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"GPR", 0x00000005, 0x00000001, 0x00000001},
    {"MAILBOX_SET", 0x00000006, 0x00000001, 0x00000001},
    {"MAILBOX_CLR", 0x00000007, 0x00000001, 0x00000001},
    {"MAILBOX", 0x00000008, 0x00000001, 0x00000001},
    {"SEMA_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"SEMA", 0x0000000a, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV_ORG_VER2_6[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEVCPU_ORG", 0x0000f980, 0x00000001, 0x00000012, regs_within_DEV_ORG_VER2_6_DEVCPU_ORG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_ORG_VER2_7_DEVCPU_ORG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"IF_CFGSTAT", 0x00000001, 0x00000001, 0x00000001},
    {"ORG_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"ERR_CNTS", 0x00000003, 0x00000001, 0x00000001},
    {"TIMEOUT_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"GPR", 0x00000005, 0x00000001, 0x00000001},
    {"MAILBOX_SET", 0x00000006, 0x00000001, 0x00000001},
    {"MAILBOX_CLR", 0x00000007, 0x00000001, 0x00000001},
    {"MAILBOX", 0x00000008, 0x00000001, 0x00000001},
    {"SEMA_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"SEMA", 0x0000000a, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV_ORG_VER2_7[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEVCPU_ORG", 0x0000f9c0, 0x00000001, 0x00000012, regs_within_DEV_ORG_VER2_7_DEVCPU_ORG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_ORG_VER2_8_DEVCPU_ORG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"IF_CFGSTAT", 0x00000001, 0x00000001, 0x00000001},
    {"ORG_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"ERR_CNTS", 0x00000003, 0x00000001, 0x00000001},
    {"TIMEOUT_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"GPR", 0x00000005, 0x00000001, 0x00000001},
    {"MAILBOX_SET", 0x00000006, 0x00000001, 0x00000001},
    {"MAILBOX_CLR", 0x00000007, 0x00000001, 0x00000001},
    {"MAILBOX", 0x00000008, 0x00000001, 0x00000001},
    {"SEMA_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"SEMA", 0x0000000a, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV_ORG_VER2_8[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEVCPU_ORG", 0x0000fa00, 0x00000001, 0x00000012, regs_within_DEV_ORG_VER2_8_DEVCPU_ORG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_ORG_VER2_9_DEVCPU_ORG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"IF_CFGSTAT", 0x00000001, 0x00000001, 0x00000001},
    {"ORG_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"ERR_CNTS", 0x00000003, 0x00000001, 0x00000001},
    {"TIMEOUT_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"GPR", 0x00000005, 0x00000001, 0x00000001},
    {"MAILBOX_SET", 0x00000006, 0x00000001, 0x00000001},
    {"MAILBOX_CLR", 0x00000007, 0x00000001, 0x00000001},
    {"MAILBOX", 0x00000008, 0x00000001, 0x00000001},
    {"SEMA_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"SEMA", 0x0000000a, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV_ORG_VER2_9[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEVCPU_ORG", 0x0000fa40, 0x00000001, 0x00000012, regs_within_DEV_ORG_VER2_9_DEVCPU_ORG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_ORG_VER2_10_DEVCPU_ORG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"IF_CFGSTAT", 0x00000001, 0x00000001, 0x00000001},
    {"ORG_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"ERR_CNTS", 0x00000003, 0x00000001, 0x00000001},
    {"TIMEOUT_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"GPR", 0x00000005, 0x00000001, 0x00000001},
    {"MAILBOX_SET", 0x00000006, 0x00000001, 0x00000001},
    {"MAILBOX_CLR", 0x00000007, 0x00000001, 0x00000001},
    {"MAILBOX", 0x00000008, 0x00000001, 0x00000001},
    {"SEMA_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"SEMA", 0x0000000a, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV_ORG_VER2_10[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEVCPU_ORG", 0x0000fa80, 0x00000001, 0x00000012, regs_within_DEV_ORG_VER2_10_DEVCPU_ORG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_ORG_VER2_11_DEVCPU_ORG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"IF_CFGSTAT", 0x00000001, 0x00000001, 0x00000001},
    {"ORG_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"ERR_CNTS", 0x00000003, 0x00000001, 0x00000001},
    {"TIMEOUT_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"GPR", 0x00000005, 0x00000001, 0x00000001},
    {"MAILBOX_SET", 0x00000006, 0x00000001, 0x00000001},
    {"MAILBOX_CLR", 0x00000007, 0x00000001, 0x00000001},
    {"MAILBOX", 0x00000008, 0x00000001, 0x00000001},
    {"SEMA_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"SEMA", 0x0000000a, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV_ORG_VER2_11[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEVCPU_ORG", 0x0000fac0, 0x00000001, 0x00000012, regs_within_DEV_ORG_VER2_11_DEVCPU_ORG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_ORG_VER2_12_DEVCPU_ORG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"IF_CFGSTAT", 0x00000001, 0x00000001, 0x00000001},
    {"ORG_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"ERR_CNTS", 0x00000003, 0x00000001, 0x00000001},
    {"TIMEOUT_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"GPR", 0x00000005, 0x00000001, 0x00000001},
    {"MAILBOX_SET", 0x00000006, 0x00000001, 0x00000001},
    {"MAILBOX_CLR", 0x00000007, 0x00000001, 0x00000001},
    {"MAILBOX", 0x00000008, 0x00000001, 0x00000001},
    {"SEMA_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"SEMA", 0x0000000a, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV_ORG_VER2_12[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEVCPU_ORG", 0x0000fb00, 0x00000001, 0x00000012, regs_within_DEV_ORG_VER2_12_DEVCPU_ORG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_ORG_VER2_13_DEVCPU_ORG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"IF_CFGSTAT", 0x00000001, 0x00000001, 0x00000001},
    {"ORG_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"ERR_CNTS", 0x00000003, 0x00000001, 0x00000001},
    {"TIMEOUT_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"GPR", 0x00000005, 0x00000001, 0x00000001},
    {"MAILBOX_SET", 0x00000006, 0x00000001, 0x00000001},
    {"MAILBOX_CLR", 0x00000007, 0x00000001, 0x00000001},
    {"MAILBOX", 0x00000008, 0x00000001, 0x00000001},
    {"SEMA_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"SEMA", 0x0000000a, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV_ORG_VER2_13[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEVCPU_ORG", 0x0000fb40, 0x00000001, 0x00000012, regs_within_DEV_ORG_VER2_13_DEVCPU_ORG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_ORG_VER2_14_DEVCPU_ORG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"IF_CFGSTAT", 0x00000001, 0x00000001, 0x00000001},
    {"ORG_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"ERR_CNTS", 0x00000003, 0x00000001, 0x00000001},
    {"TIMEOUT_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"GPR", 0x00000005, 0x00000001, 0x00000001},
    {"MAILBOX_SET", 0x00000006, 0x00000001, 0x00000001},
    {"MAILBOX_CLR", 0x00000007, 0x00000001, 0x00000001},
    {"MAILBOX", 0x00000008, 0x00000001, 0x00000001},
    {"SEMA_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"SEMA", 0x0000000a, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV_ORG_VER2_14[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEVCPU_ORG", 0x0000fb80, 0x00000001, 0x00000012, regs_within_DEV_ORG_VER2_14_DEVCPU_ORG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_ORG_VER2_15_DEVCPU_ORG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"IF_CFGSTAT", 0x00000001, 0x00000001, 0x00000001},
    {"ORG_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"ERR_CNTS", 0x00000003, 0x00000001, 0x00000001},
    {"TIMEOUT_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"GPR", 0x00000005, 0x00000001, 0x00000001},
    {"MAILBOX_SET", 0x00000006, 0x00000001, 0x00000001},
    {"MAILBOX_CLR", 0x00000007, 0x00000001, 0x00000001},
    {"MAILBOX", 0x00000008, 0x00000001, 0x00000001},
    {"SEMA_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"SEMA", 0x0000000a, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV_ORG_VER2_15[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEVCPU_ORG", 0x0000fbc0, 0x00000001, 0x00000012, regs_within_DEV_ORG_VER2_15_DEVCPU_ORG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_ORG_VER2_16_DEVCPU_ORG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"IF_CFGSTAT", 0x00000001, 0x00000001, 0x00000001},
    {"ORG_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"ERR_CNTS", 0x00000003, 0x00000001, 0x00000001},
    {"TIMEOUT_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"GPR", 0x00000005, 0x00000001, 0x00000001},
    {"MAILBOX_SET", 0x00000006, 0x00000001, 0x00000001},
    {"MAILBOX_CLR", 0x00000007, 0x00000001, 0x00000001},
    {"MAILBOX", 0x00000008, 0x00000001, 0x00000001},
    {"SEMA_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"SEMA", 0x0000000a, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV_ORG_VER2_16[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEVCPU_ORG", 0x0000fc00, 0x00000001, 0x00000012, regs_within_DEV_ORG_VER2_16_DEVCPU_ORG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_ORG_VER2_17_DEVCPU_ORG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_CTRL", 0x00000000, 0x00000001, 0x00000001},
    {"IF_CFGSTAT", 0x00000001, 0x00000001, 0x00000001},
    {"ORG_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"ERR_CNTS", 0x00000003, 0x00000001, 0x00000001},
    {"TIMEOUT_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"GPR", 0x00000005, 0x00000001, 0x00000001},
    {"MAILBOX_SET", 0x00000006, 0x00000001, 0x00000001},
    {"MAILBOX_CLR", 0x00000007, 0x00000001, 0x00000001},
    {"MAILBOX", 0x00000008, 0x00000001, 0x00000001},
    {"SEMA_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"SEMA", 0x0000000a, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV_ORG_VER2_17[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEVCPU_ORG", 0x0000fc40, 0x00000001, 0x00000012, regs_within_DEV_ORG_VER2_17_DEVCPU_ORG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_MCU_OTP_OTP_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"OTP_PWR_DN", 0x00000000, 0x00000001, 0x00000001},
    {"OTP_ADDR_HI", 0x00000001, 0x00000001, 0x00000001},
    {"OTP_ADDR_LO", 0x00000002, 0x00000001, 0x00000001},
    {"OTP_ADDR_BITS", 0x00000003, 0x00000001, 0x00000001},
    {"OTP_PRGM_DATA", 0x00000004, 0x00000001, 0x00000001},
    {"OTP_PRGM_MODE", 0x00000005, 0x00000001, 0x00000001},
    {"OTP_RD_DATA", 0x00000006, 0x00000001, 0x00000001},
    {"OTP_FUNC_CMD", 0x00000008, 0x00000001, 0x00000001},
    {"OTP_TEST_CMD", 0x00000009, 0x00000001, 0x00000001},
    {"OTP_CMD_GO", 0x0000000a, 0x00000001, 0x00000001},
    {"OTP_PASS_FAIL", 0x0000000b, 0x00000001, 0x00000001},
    {"OTP_STATUS", 0x0000000c, 0x00000001, 0x00000001},
    {"OTP_MAX_PRG", 0x0000000d, 0x00000001, 0x00000001},
    {"OTP_INTR_STATUS", 0x0000000e, 0x00000001, 0x00000001},
    {"OTP_INTR_MASK", 0x0000000f, 0x00000001, 0x00000001},
    {"OTP_BLANK_FAIL_COUNT", 0x00000010, 0x00000001, 0x00000001},
    {"OTP_BLANK_FAIL_COUNT_ADDR_IDX", 0x00000011, 0x00000001, 0x00000001},
    {"OTP_BLANK_FAIL_ADDR_HI", 0x00000012, 0x00000001, 0x00000001},
    {"OTP_BLANK_FAIL_ADDR_LO", 0x00000013, 0x00000001, 0x00000001},
    {"OTP_RSTB_PW_HI", 0x00000014, 0x00000001, 0x00000001},
    {"OTP_RSTB_PW_LO", 0x00000015, 0x00000001, 0x00000001},
    {"OTP_PGM_PW_HI", 0x00000018, 0x00000001, 0x00000001},
    {"OTP_PGM_PW_LO", 0x00000019, 0x00000001, 0x00000001},
    {"OTP_READ_PW_HI", 0x0000001c, 0x00000001, 0x00000001},
    {"OTP_READ_PW_LO", 0x0000001d, 0x00000001, 0x00000001},
    {"OTP_TCRST_VAL", 0x00000020, 0x00000001, 0x00000001},
    {"OTP_TRSRD_VAL", 0x00000021, 0x00000001, 0x00000001},
    {"OTP_TREADEN_VAL", 0x00000022, 0x00000001, 0x00000001},
    {"OTP_TDLES_VAL", 0x00000023, 0x00000001, 0x00000001},
    {"OTP_TWWL_VAL", 0x00000024, 0x00000001, 0x00000001},
    {"OTP_TDLEH_VAL", 0x00000025, 0x00000001, 0x00000001},
    {"OTP_TWPED_VAL", 0x00000026, 0x00000001, 0x00000001},
    {"OTP_TPES_VAL", 0x00000027, 0x00000001, 0x00000001},
    {"OTP_TCPS_VAL", 0x00000028, 0x00000001, 0x00000001},
    {"OTP_TCPH_VAL", 0x00000029, 0x00000001, 0x00000001},
    {"OTP_TPGMVFY_VAL", 0x0000002a, 0x00000001, 0x00000001},
    {"OTP_TPEH_VAL", 0x0000002b, 0x00000001, 0x00000001},
    {"OTP_TPGRST_VAL", 0x0000002c, 0x00000001, 0x00000001},
    {"OTP_TCLES_VAL", 0x0000002d, 0x00000001, 0x00000001},
    {"OTP_TCLEH_VAL", 0x0000002e, 0x00000001, 0x00000001},
    {"OTP_TRDES_VAL", 0x0000002f, 0x00000001, 0x00000001},
    {"OTP_TBCAAC_VAL", 0x00000030, 0x00000001, 0x00000001},
    {"OTP_TAAC_VAL", 0x00000031, 0x00000001, 0x00000001},
    {"OTP_TACCT_VAL", 0x00000032, 0x00000001, 0x00000001},
    {"OTP_TPRYCEB_VAL", 0x00000033, 0x00000001, 0x00000001},
    {"OTP_TCEBPRY_VAL", 0x00000034, 0x00000001, 0x00000001},
    {"OTP_TPGMAS_VAL", 0x0000003c, 0x00000001, 0x00000001},
    {"OTP_TCPRD_VAL", 0x00000040, 0x00000001, 0x00000001},
    {"OTP_TRDCP_VAL", 0x00000041, 0x00000001, 0x00000001},
    {"OTP_NP1_VAL", 0x00000045, 0x00000001, 0x00000001},
    {"OTP_NP2_VAL", 0x00000046, 0x00000001, 0x00000001},
    {"OTP_READ_PROTECT0", 0x00000080, 0x00000001, 0x00000001},
    {"OTP_READ_PROTECT1", 0x00000081, 0x00000001, 0x00000001},
    {"OTP_READ_PROTECT2", 0x00000082, 0x00000001, 0x00000001},
    {"OTP_READ_PROTECT3", 0x00000083, 0x00000001, 0x00000001},
    {"OTP_FPGA_PROM_CTL", 0x000000c0, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_MCU_OTP[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"OTP_REGS", 0x00000000, 0x00000001, 0x000000c1, regs_within_MCU_OTP_OTP_REGS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_MCU_UART_UART[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"UART_RX_TX_DATA_DLL", 0x00000000, 0x00000001, 0x00000001},
    {"UART_IER_DHL", 0x00000001, 0x00000001, 0x00000001},
    {"UART_IIR_FCR", 0x00000002, 0x00000001, 0x00000001},
    {"UART_LCR", 0x00000003, 0x00000001, 0x00000001},
    {"UART_MCR", 0x00000004, 0x00000001, 0x00000001},
    {"UART_LSR", 0x00000005, 0x00000001, 0x00000001},
    {"UART_MSR", 0x00000006, 0x00000001, 0x00000001},
    {"UART_SCR", 0x00000007, 0x00000001, 0x00000001},
    {"UART_CTL", 0x000003f0, 0x00000001, 0x00000001},
    {"UART_ACTV", 0x00000330, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_MCU_UART[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"UART", 0x00000000, 0x00000001, 0x000003f1, regs_within_MCU_UART_UART},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_MCU_WDT_WDT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"WDT_LOAD", 0x00000000, 0x00000001, 0x00000001},
    {"WDT_CONTROL", 0x00000001, 0x00000001, 0x00000001},
    {"WDT_KICK", 0x00000002, 0x00000001, 0x00000001},
    {"WDT_COUNT", 0x00000003, 0x00000001, 0x00000001},
    {"WDT_LOCK", 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_MCU_WDT[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"WDT", 0x00000000, 0x00000001, 0x00000005, regs_within_MCU_WDT_WDT},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_MCU_TIMER_TIMER[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TIMER_CTL", 0x00000000, 0x00000001, 0x00000001},
    {"TIMER_CLK_EVT_CTL", 0x00000001, 0x00000001, 0x00000001},
    {"TIMER_RELOAD", 0x00000002, 0x00000001, 0x00000001},
    {"TIMER_CNT", 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_MCU_TIMER[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"TIMER", 0x00000000, 0x00000004, 0x00000020, regs_within_MCU_TIMER_TIMER},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_MCU_SPI_MSTR_SPI_MSTR_AHB[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MCU_SPI_MSTR_CONFIG", 0x00000000, 0x00000001, 0x00000001},
    {"MCU_SPI_MSTR_CMD_BUFA", 0x00000002, 0x00000001, 0x00000001},
    {"MCU_SPI_MSTR_CMD_BUFB", 0x00000003, 0x00000001, 0x00000001},
    {"MCU_SPI_MSTR_RSP_BUFA", 0x00000004, 0x00000001, 0x00000001},
    {"MCU_SPI_MSTR_RSP_BUFB", 0x00000005, 0x00000001, 0x00000001},
    {"MCU_SPI_MSTR_PAD_CTL", 0x00000006, 0x00000001, 0x00000001},
    {"MCU_SPI_MSTR_TRFIFO_WR", 0x00002fff, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_MCU_SPI_MSTR[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"SPI_MSTR_AHB", 0x00000000, 0x00000001, 0x00003000, regs_within_MCU_SPI_MSTR_SPI_MSTR_AHB},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_MCU_MISC_REG_MIM_MISC_REG_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SCRATCH_PAD_0", 0x00000000, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_1", 0x00000001, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_2", 0x00000002, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_3", 0x00000003, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_4", 0x00000004, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_5", 0x00000005, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_6", 0x00000006, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_7", 0x00000007, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_8", 0x00000008, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_9", 0x00000009, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_10", 0x0000000a, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_11", 0x0000000b, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_12", 0x0000000c, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_13", 0x0000000d, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_14", 0x0000000e, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_15", 0x0000000f, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_16", 0x00000010, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_17", 0x00000011, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_18", 0x00000012, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_19", 0x00000013, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_20", 0x00000014, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_21", 0x00000015, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_22", 0x00000016, 0x00000001, 0x00000001},
    {"SCRATCH_PAD_23", 0x00000017, 0x00000001, 0x00000001},
    {"ENVIRONMENT", 0x00000020, 0x00000001, 0x00000001},
    {"TYPE_A_FPGA_REV", 0x00000021, 0x00000001, 0x00000001},
    {"TYPE_B_FPGA_REV", 0x00000022, 0x00000001, 0x00000001},
    {"TYPE_C_FPGA_REV", 0x00000023, 0x00000001, 0x00000001},
    {"MCU_RESET_REASON", 0x00000024, 0x00000001, 0x00000001},
    {"MCU_SRESET_PROTECT", 0x00000025, 0x00000001, 0x00000001},
    {"SRESET_SCALE", 0x00000026, 0x00000001, 0x00000001},
    {"SPARE_RW", 0x00000027, 0x00000001, 0x00000001},
    {"SPARE_RO", 0x00000028, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_MCU_MISC_REG[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"MIM_MISC_REG_REGS", 0x00000000, 0x00000001, 0x00000029, regs_within_MCU_MISC_REG_MIM_MISC_REG_REGS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_MACSEC_INGR_MACSEC_INGR_MACSEC_CTL_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MACSEC_INGR_MACSEC_ENA_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"MACSEC_INGR_MACSEC_CTL_CFG", 0x00000001, 0x00000001, 0x00000001},
    {"MACSEC_INGR_MACSEC_STICKY", 0x00000002, 0x00000001, 0x00000001},
    {"MACSEC_INGR_MACSEC_STICKY_MASK", 0x00000003, 0x00000001, 0x00000001},
    {"MACSEC_INGR_MACSEC_IGR_LATENCY_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"MACSEC_INGR_MACSEC_DEBUG_REG_ADDR", 0x00000005, 0x00000001, 0x00000001},
    {"MACSEC_INGR_MACSEC_DEBUG_REG_DATA", 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MACSEC_INGR_MACSEC_DEBUG0", 0x00000000, 0x00000001, 0x00000001},
    {"MACSEC_INGR_MACSEC_DEBUG1", 0x00000001, 0x00000001, 0x00000001},
    {"MACSEC_INGR_MACSEC_DEBUG2", 0x00000002, 0x00000001, 0x00000001},
    {"MACSEC_INGR_MACSEC_DEBUG3", 0x00000003, 0x00000001, 0x00000001},
    {"MACSEC_INGR_MACSEC_DEBUG4", 0x00000004, 0x00000001, 0x00000001},
    {"MACSEC_INGR_MACSEC_DEBUG5", 0x00000005, 0x00000001, 0x00000001},
    {"MACSEC_INGR_MACSEC_DEBUG6", 0x00000006, 0x00000001, 0x00000001},
    {"MACSEC_INGR_MACSEC_DEBUG7", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MACSEC_INGR_MACSEC_ECC_CTL", 0x00000000, 0x00000001, 0x00000001},
    {"MACSEC_INGR_MACSEC_ECC_SR", 0x00000001, 0x00000001, 0x00000001},
    {"MACSEC_INGR_MACSEC_ECC_INIT_DONE_INTR_EN", 0x00000004, 0x00000001, 0x00000001},
    {"MACSEC_INGR_MACSEC_ECC_INIT_DONE_INTR_STS", 0x00000005, 0x00000001, 0x00000001},
    {"MACSEC_INGR_MACSEC_ECC_INTR_EN", 0x00000006, 0x00000001, 0x00000001},
    {"MACSEC_INGR_MACSEC_ECC_INTR_STS", 0x00000007, 0x00000001, 0x00000001},
    {"MACSEC_INGR_MACSEC_ECC_LANE_FCR", 0x00000010, 0x00000004, 0x00000010},
    {"MACSEC_INGR_MACSEC_ECC_LANE_EADDR", 0x00000014, 0x00000004, 0x00000010},
    {"MACSEC_INGR_MACSEC_ECC_LANE_EDPTR", 0x00000015, 0x00000004, 0x00000010},
    {"MACSEC_INGR_MACSEC_ECC_LANE_SCNT", 0x00000016, 0x00000004, 0x00000010},
    {"MACSEC_INGR_MACSEC_ECC_LANE_DCNT", 0x00000017, 0x00000004, 0x00000010},
    {"MACSEC_INGR_MACSEC_ECC_LANE_INTR_EN", 0x00000018, 0x00000004, 0x00000010},
    {"MACSEC_INGR_MACSEC_ECC_LANE_INTR_STS", 0x00000019, 0x00000004, 0x00000010},
    {"MACSEC_INGR_MACSEC_ECC_LANE_FADDR", 0x0000001c, 0x00000004, 0x00000010},
    {"MACSEC_INGR_MACSEC_ECC_LANE_FDPTR", 0x0000001d, 0x00000004, 0x00000010},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_MACSEC_INGR[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"MACSEC_INGR_MACSEC_CTL_REGS", 0x00000c40, 0x00000001, 0x00000007, regs_within_MACSEC_INGR_MACSEC_INGR_MACSEC_CTL_REGS},
    {"MACSEC_INGR_MACSEC_DEBUG", 0x00000c48, 0x00000001, 0x00000008, regs_within_MACSEC_INGR_MACSEC_INGR_MACSEC_DEBUG},
    {"MACSEC_INGR_MACSEC_ECC", 0x00000c50, 0x00000001, 0x0000004e, regs_within_MACSEC_INGR_MACSEC_INGR_MACSEC_ECC},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_MACSEC_EGR_MACSEC_EGR_MACSEC_CTL_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MACSEC_EGR_MACSEC_ENA_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"MACSEC_EGR_MACSEC_CTL_CFG", 0x00000001, 0x00000001, 0x00000001},
    {"MACSEC_EGR_MACSEC_STICKY", 0x00000002, 0x00000001, 0x00000001},
    {"MACSEC_EGR_MACSEC_STICKY_MASK", 0x00000003, 0x00000001, 0x00000001},
    {"MACSEC_EGR_MACSEC_FC_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"MACSEC_EGR_MACSEC_PTP_STALL_CFG", 0x00000005, 0x00000001, 0x00000001},
    {"MACSEC_EGR_MACSEC_DEBUG_REG_ADDR", 0x00000006, 0x00000001, 0x00000001},
    {"MACSEC_EGR_MACSEC_DEBUG_REG_DATA", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MACSEC_EGR_MACSEC_EGR_MACSEC_DEBUG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MACSEC_EGR_MACSEC_DEBUG0", 0x00000000, 0x00000001, 0x00000001},
    {"MACSEC_EGR_MACSEC_DEBUG1", 0x00000001, 0x00000001, 0x00000001},
    {"MACSEC_EGR_MACSEC_DEBUG2", 0x00000002, 0x00000001, 0x00000001},
    {"MACSEC_EGR_MACSEC_DEBUG3", 0x00000003, 0x00000001, 0x00000001},
    {"MACSEC_EGR_MACSEC_DEBUG4", 0x00000004, 0x00000001, 0x00000001},
    {"MACSEC_EGR_MACSEC_DEBUG5", 0x00000005, 0x00000001, 0x00000001},
    {"MACSEC_EGR_MACSEC_DEBUG6", 0x00000006, 0x00000001, 0x00000001},
    {"MACSEC_EGR_MACSEC_DEBUG7", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MACSEC_EGR_CAPT_DEBUG_DATA", 0x00000000, 0x00000080, 0x00000001},
    {"MACSEC_EGR_CAPT_DEBUG_CTRL", 0x00000080, 0x00000001, 0x00000001},
    {"MACSEC_EGR_CAPT_DEBUG_STATUS", 0x00000081, 0x00000001, 0x00000001},
    {"MACSEC_EGR_CAPT_DEBUG_TRIGGER_SA1", 0x00000082, 0x00000001, 0x00000001},
    {"MACSEC_EGR_CAPT_DEBUG_TRIGGER_SA2", 0x00000083, 0x00000001, 0x00000001},
    {"MACSEC_EGR_CAPT_DEBUG_TRIGGER", 0x00000084, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MACSEC_EGR_MACSEC_EGR_MACSEC_ECC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MACSEC_EGR_MACSEC_ECC_CTL", 0x00000000, 0x00000001, 0x00000001},
    {"MACSEC_EGR_MACSEC_ECC_SR", 0x00000001, 0x00000001, 0x00000001},
    {"MACSEC_EGR_MACSEC_ECC_INIT_DONE_INTR_EN", 0x00000004, 0x00000001, 0x00000001},
    {"MACSEC_EGR_MACSEC_ECC_INIT_DONE_INTR_STS", 0x00000005, 0x00000001, 0x00000001},
    {"MACSEC_EGR_MACSEC_ECC_INTR_EN", 0x00000006, 0x00000001, 0x00000001},
    {"MACSEC_EGR_MACSEC_ECC_INTR_STS", 0x00000007, 0x00000001, 0x00000001},
    {"MACSEC_EGR_MACSEC_ECC_LANE_FCR", 0x00000010, 0x00000004, 0x00000010},
    {"MACSEC_EGR_MACSEC_ECC_LANE_EADDR", 0x00000014, 0x00000004, 0x00000010},
    {"MACSEC_EGR_MACSEC_ECC_LANE_EDPTR", 0x00000015, 0x00000004, 0x00000010},
    {"MACSEC_EGR_MACSEC_ECC_LANE_SCNT", 0x00000016, 0x00000004, 0x00000010},
    {"MACSEC_EGR_MACSEC_ECC_LANE_DCNT", 0x00000017, 0x00000004, 0x00000010},
    {"MACSEC_EGR_MACSEC_ECC_LANE_INTR_EN", 0x00000018, 0x00000004, 0x00000010},
    {"MACSEC_EGR_MACSEC_ECC_LANE_INTR_STS", 0x00000019, 0x00000004, 0x00000010},
    {"MACSEC_EGR_MACSEC_ECC_LANE_FADDR", 0x0000001c, 0x00000004, 0x00000010},
    {"MACSEC_EGR_MACSEC_ECC_LANE_FDPTR", 0x0000001d, 0x00000004, 0x00000010},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_MACSEC_EGR[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"MACSEC_EGR_MACSEC_CTL_REGS", 0x00000c40, 0x00000001, 0x00000008, regs_within_MACSEC_EGR_MACSEC_EGR_MACSEC_CTL_REGS},
    {"MACSEC_EGR_MACSEC_DEBUG", 0x00000c48, 0x00000001, 0x00000008, regs_within_MACSEC_EGR_MACSEC_EGR_MACSEC_DEBUG},
    {"MACSEC_EGR_CAPT_DEBUG_REGS", 0x00000c50, 0x00000001, 0x00000085, regs_within_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_REGS},
    {"MACSEC_EGR_MACSEC_ECC", 0x00000d00, 0x00000001, 0x0000004e, regs_within_MACSEC_EGR_MACSEC_EGR_MACSEC_ECC},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_MAC_FC_BUFFER_MAC_FC_BUFFER_CONFIG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MAC_FC_BUFFER_FC_ENA_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_FC_MODE_CFG", 0x00000001, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_PPM_RATE_ADAPT_THRESH_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_TX_CTRL_QUEUE_CFG", 0x00000003, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_TX_DATA_QUEUE_CFG", 0x00000004, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_RX_DATA_QUEUE_CFG", 0x00000005, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_TX_BUFF_XON_XOFF_THRESH_CFG", 0x00000006, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_FC_READ_THRESH_CFG", 0x00000007, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_TX_FRM_GAP_COMP", 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MAC_FC_BUFFER_MAC_FC_BUFFER_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MAC_FC_BUFFER_STICKY", 0x00000000, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_STICKY_MASK", 0x00000001, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_TX_CTRL_QUEUE_OVERFLOW_DROP_CNT", 0x00000002, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_TX_CTRL_QUEUE_UNDERFLOW_DROP_CNT", 0x00000003, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_TX_CTRL_UNCORRECTED_FRM_DROP_CNT", 0x00000004, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_TX_DATA_QUEUE_OVERFLOW_DROP_CNT", 0x00000005, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_TX_DATA_QUEUE_UNDERFLOW_DROP_CNT", 0x00000006, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_TX_DATA_UNCORRECTED_FRM_DROP_CNT", 0x00000007, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_RX_OVERFLOW_DROP_CNT", 0x00000008, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_RX_UNDERFLOW_DROP_CNT", 0x00000009, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_RX_UNCORRECTED_FRM_DROP_CNT", 0x0000000a, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MAC_FC_BUFFER_MAC_FC_BUFFER_INGR_FC_BUFFER_ECC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_CTL", 0x00000000, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_SR", 0x00000001, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INIT_DONE_INTR_EN", 0x00000004, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INIT_DONE_INTR_STS", 0x00000005, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_FCR", 0x00000010, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_EADDR", 0x00000014, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_EDPTR", 0x00000015, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_SCNT", 0x00000016, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_DCNT", 0x00000017, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INTR_EN", 0x00000018, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INTR_STS", 0x00000019, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_FADDR", 0x0000001c, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_FDPTR", 0x0000001d, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MAC_FC_BUFFER_MAC_FC_BUFFER_EGR_FC_BUFFER_ECC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_CTL", 0x00000000, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_SR", 0x00000001, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INIT_DONE_INTR_EN", 0x00000004, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INIT_DONE_INTR_STS", 0x00000005, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_FCR", 0x00000010, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_EADDR", 0x00000014, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_EDPTR", 0x00000015, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_SCNT", 0x00000016, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_DCNT", 0x00000017, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INTR_EN", 0x00000018, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INTR_STS", 0x00000019, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_FADDR", 0x0000001c, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_FDPTR", 0x0000001d, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MAC_FC_BUFFER_MAC_FC_BUFFER_MAC_FC_BUFFER_DEBUG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MAC_FC_BUFFER_MAC_FC_BUFFER_DEBUG0", 0x00000000, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_MAC_FC_BUFFER_DEBUG1", 0x00000001, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_MAC_FC_BUFFER_DEBUG2", 0x00000002, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_MAC_FC_BUFFER_DEBUG3", 0x00000003, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_MAC_FC_BUFFER_DEBUG4", 0x00000004, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_MAC_FC_BUFFER_DEBUG5", 0x00000005, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_MAC_FC_BUFFER_DEBUG6", 0x00000006, 0x00000001, 0x00000001},
    {"MAC_FC_BUFFER_MAC_FC_BUFFER_DEBUG7", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_MAC_FC_BUFFER[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"MAC_FC_BUFFER_CONFIG", 0x0000f000, 0x00000001, 0x00000009, regs_within_MAC_FC_BUFFER_MAC_FC_BUFFER_CONFIG},
    {"MAC_FC_BUFFER_STATUS", 0x0000f009, 0x00000001, 0x0000000b, regs_within_MAC_FC_BUFFER_MAC_FC_BUFFER_STATUS},
    {"MAC_FC_BUFFER_INGR_FC_BUFFER_ECC", 0x0000f020, 0x00000001, 0x0000001e, regs_within_MAC_FC_BUFFER_MAC_FC_BUFFER_INGR_FC_BUFFER_ECC},
    {"MAC_FC_BUFFER_EGR_FC_BUFFER_ECC", 0x0000f040, 0x00000001, 0x0000001e, regs_within_MAC_FC_BUFFER_MAC_FC_BUFFER_EGR_FC_BUFFER_ECC},
    {"MAC_FC_BUFFER_MAC_FC_BUFFER_DEBUG", 0x0000f078, 0x00000001, 0x00000008, regs_within_MAC_FC_BUFFER_MAC_FC_BUFFER_MAC_FC_BUFFER_DEBUG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_LINE_MAC_LINE_MAC_CONFIG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LINE_MAC_MAC_ENA_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"LINE_MAC_MAC_MODE_CFG", 0x00000001, 0x00000001, 0x00000001},
    {"LINE_MAC_MAC_MAXLEN_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"LINE_MAC_MAC_NUM_TAGS_CFG", 0x00000003, 0x00000001, 0x00000001},
    {"LINE_MAC_MAC_TAGS_CFG", 0x00000004, 0x00000003, 0x00000001},
    {"LINE_MAC_MAC_ADV_CHK_CFG", 0x00000007, 0x00000001, 0x00000001},
    {"LINE_MAC_MAC_LFS_CFG", 0x00000008, 0x00000001, 0x00000001},
    {"LINE_MAC_MAC_LB_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"LINE_MAC_MAC_PKTINF_CFG", 0x0000000a, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_MAC_LINE_MAC_PAUSE_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LINE_MAC_PAUSE_TX_FRAME_CONTROL", 0x00000000, 0x00000001, 0x00000001},
    {"LINE_MAC_PAUSE_TX_FRAME_CONTROL_2", 0x00000001, 0x00000001, 0x00000001},
    {"LINE_MAC_PAUSE_RX_FRAME_CONTROL", 0x00000002, 0x00000001, 0x00000001},
    {"LINE_MAC_PAUSE_STATE", 0x00000003, 0x00000001, 0x00000001},
    {"LINE_MAC_MAC_ADDRESS_LSB", 0x00000004, 0x00000001, 0x00000001},
    {"LINE_MAC_MAC_ADDRESS_MSB", 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_MAC_LINE_MAC_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LINE_MAC_MAC_RX_LANE_STICKY_0", 0x00000000, 0x00000001, 0x00000001},
    {"LINE_MAC_MAC_RX_LANE_STICKY_1", 0x00000001, 0x00000001, 0x00000001},
    {"LINE_MAC_MAC_TX_MONITOR_STICKY", 0x00000002, 0x00000001, 0x00000001},
    {"LINE_MAC_MAC_TX_MONITOR_STICKY_MASK", 0x00000003, 0x00000001, 0x00000001},
    {"LINE_MAC_MAC_STICKY", 0x00000004, 0x00000001, 0x00000001},
    {"LINE_MAC_MAC_STICKY_MASK", 0x00000005, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_STICKY", 0x00000006, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_MAC_STICKY_MASK", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_MAC_LINE_MAC_STATISTICS_32BIT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LINE_MAC_RX_XGMII_PROT_ERR_CNT", 0x00000000, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_SYMBOL_ERR_CNT", 0x00000001, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_PAUSE_CNT", 0x00000002, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_UNSUP_OPCODE_CNT", 0x00000003, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_UC_CNT", 0x00000004, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_MC_CNT", 0x00000005, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_BC_CNT", 0x00000006, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_CRC_ERR_CNT", 0x00000007, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_UNDERSIZE_CNT", 0x00000008, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_FRAGMENTS_CNT", 0x00000009, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_IN_RANGE_LEN_ERR_CNT", 0x0000000a, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_OUT_OF_RANGE_LEN_ERR_CNT", 0x0000000b, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_OVERSIZE_CNT", 0x0000000c, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_JABBERS_CNT", 0x0000000d, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_SIZE64_CNT", 0x0000000e, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_SIZE65TO127_CNT", 0x0000000f, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_SIZE128TO255_CNT", 0x00000010, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_SIZE256TO511_CNT", 0x00000011, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_SIZE512TO1023_CNT", 0x00000012, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_SIZE1024TO1518_CNT", 0x00000013, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_SIZE1519TOMAX_CNT", 0x00000014, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_IPG_SHRINK_CNT", 0x00000015, 0x00000001, 0x00000001},
    {"LINE_MAC_TX_PAUSE_CNT", 0x00000016, 0x00000001, 0x00000001},
    {"LINE_MAC_TX_UC_CNT", 0x00000017, 0x00000001, 0x00000001},
    {"LINE_MAC_TX_MC_CNT", 0x00000018, 0x00000001, 0x00000001},
    {"LINE_MAC_TX_BC_CNT", 0x00000019, 0x00000001, 0x00000001},
    {"LINE_MAC_TX_SIZE64_CNT", 0x0000001a, 0x00000001, 0x00000001},
    {"LINE_MAC_TX_SIZE65TO127_CNT", 0x0000001b, 0x00000001, 0x00000001},
    {"LINE_MAC_TX_SIZE128TO255_CNT", 0x0000001c, 0x00000001, 0x00000001},
    {"LINE_MAC_TX_SIZE256TO511_CNT", 0x0000001d, 0x00000001, 0x00000001},
    {"LINE_MAC_TX_SIZE512TO1023_CNT", 0x0000001e, 0x00000001, 0x00000001},
    {"LINE_MAC_TX_SIZE1024TO1518_CNT", 0x0000001f, 0x00000001, 0x00000001},
    {"LINE_MAC_TX_SIZE1519TOMAX_CNT", 0x00000020, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_ALIGNMENT_LOST_CNT", 0x00000021, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_TAGGED_FRMS_CNT", 0x00000022, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_UNTAGGED_FRMS_CNT", 0x00000023, 0x00000001, 0x00000001},
    {"LINE_MAC_TX_TAGGED_FRMS_CNT", 0x00000024, 0x00000001, 0x00000001},
    {"LINE_MAC_TX_UNTAGGED_FRMS_CNT", 0x00000025, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_XGMII_PROT_ERR_CNT", 0x00000026, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_SYMBOL_ERR_CNT", 0x00000027, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_PAUSE_CNT", 0x00000028, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_UNSUP_OPCODE_CNT", 0x00000029, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_UC_CNT", 0x0000002a, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_MC_CNT", 0x0000002b, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_BC_CNT", 0x0000002c, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_CRC_ERR_CNT", 0x0000002d, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_UNDERSIZE_CNT", 0x0000002e, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_FRAGMENTS_CNT", 0x0000002f, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_IN_RANGE_LEN_ERR_CNT", 0x00000030, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT", 0x00000031, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_OVERSIZE_CNT", 0x00000032, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_JABBERS_CNT", 0x00000033, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_SIZE64_CNT", 0x00000034, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_SIZE65TO127_CNT", 0x00000035, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_SIZE128TO255_CNT", 0x00000036, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_SIZE256TO511_CNT", 0x00000037, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_SIZE512TO1023_CNT", 0x00000038, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_SIZE1024TO1518_CNT", 0x00000039, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_SIZE1519TOMAX_CNT", 0x0000003a, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_TX_PAUSE_CNT", 0x0000003b, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_TX_UC_CNT", 0x0000003c, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_TX_MC_CNT", 0x0000003d, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_TX_BC_CNT", 0x0000003e, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_TX_SIZE64_CNT", 0x0000003f, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_TX_SIZE65TO127_CNT", 0x00000040, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_TX_SIZE128TO255_CNT", 0x00000041, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_TX_SIZE256TO511_CNT", 0x00000042, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_TX_SIZE512TO1023_CNT", 0x00000043, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_TX_SIZE1024TO1518_CNT", 0x00000044, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_TX_SIZE1519TOMAX_CNT", 0x00000045, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_ALIGNMENT_LOST_CNT", 0x00000046, 0x00000001, 0x00000001},
    {"LINE_MAC_MM_RX_ASSEMBLY_ERR_CNT", 0x00000047, 0x00000001, 0x00000001},
    {"LINE_MAC_MM_RX_SMD_ERR_CNT", 0x00000048, 0x00000001, 0x00000001},
    {"LINE_MAC_MM_RX_ASSEMBLY_OK_CNT", 0x00000049, 0x00000001, 0x00000001},
    {"LINE_MAC_MM_RX_MERGE_FRAG_CNT", 0x0000004a, 0x00000001, 0x00000001},
    {"LINE_MAC_MM_TX_PFRAGMENT_CNT", 0x0000004b, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_MAC_LINE_MAC_STATISTICS_64BIT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LINE_MAC_RX_BAD_BYTES_CNT", 0x00000000, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_BAD_BYTES_MSB_CNT", 0x00000001, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_OK_BYTES_CNT", 0x00000002, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_OK_BYTES_MSB_CNT", 0x00000003, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_IN_BYTES_CNT", 0x00000004, 0x00000001, 0x00000001},
    {"LINE_MAC_RX_IN_BYTES_MSB_CNT", 0x00000005, 0x00000001, 0x00000001},
    {"LINE_MAC_TX_OK_BYTES_CNT", 0x00000006, 0x00000001, 0x00000001},
    {"LINE_MAC_TX_OK_BYTES_MSB_CNT", 0x00000007, 0x00000001, 0x00000001},
    {"LINE_MAC_TX_OUT_BYTES_CNT", 0x00000008, 0x00000001, 0x00000001},
    {"LINE_MAC_TX_OUT_BYTES_MSB_CNT", 0x00000009, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_OK_BYTES_CNT", 0x0000000a, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_OK_BYTES_MSB_CNT", 0x0000000b, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_BAD_BYTES_CNT", 0x0000000c, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_RX_BAD_BYTES_MSB_CNT", 0x0000000d, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_TX_OK_BYTES_CNT", 0x0000000e, 0x00000001, 0x00000001},
    {"LINE_MAC_PMAC_TX_OK_BYTES_MSB_CNT", 0x0000000f, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_MAC_LINE_MAC_MM_CONFIG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LINE_MAC_ENABLE_CONFIG", 0x00000000, 0x00000001, 0x00000001},
    {"LINE_MAC_VERIF_CONFIG", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_MAC_LINE_MAC_MM_STATISTICS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LINE_MAC_MM_STATUS", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_LINE_MAC_LINE_MAC_DEBUG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LINE_MAC_DEBUG_RO_0", 0x00000000, 0x00000001, 0x00000001},
    {"LINE_MAC_DEBUG_RO_1", 0x00000001, 0x00000001, 0x00000001},
    {"LINE_MAC_DEBUG_RO_2", 0x00000002, 0x00000001, 0x00000001},
    {"LINE_MAC_DEBUG_RO_3", 0x00000003, 0x00000001, 0x00000001},
    {"LINE_MAC_DEBUG_RO_4", 0x00000004, 0x00000001, 0x00000001},
    {"LINE_MAC_DEBUG_RO_5", 0x00000005, 0x00000001, 0x00000001},
    {"LINE_MAC_DEBUG_RO_6", 0x00000006, 0x00000001, 0x00000001},
    {"LINE_MAC_DEBUG_RW", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_LINE_MAC[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"LINE_MAC_CONFIG", 0x0000f300, 0x00000001, 0x0000000b, regs_within_LINE_MAC_LINE_MAC_CONFIG},
    {"LINE_MAC_PAUSE_CFG", 0x0000f30b, 0x00000001, 0x00000006, regs_within_LINE_MAC_LINE_MAC_PAUSE_CFG},
    {"LINE_MAC_STATUS", 0x0000f311, 0x00000001, 0x00000008, regs_within_LINE_MAC_LINE_MAC_STATUS},
    {"LINE_MAC_STATISTICS_32BIT", 0x0000f319, 0x00000001, 0x0000004c, regs_within_LINE_MAC_LINE_MAC_STATISTICS_32BIT},
    {"LINE_MAC_STATISTICS_64BIT", 0x0000f365, 0x00000001, 0x00000010, regs_within_LINE_MAC_LINE_MAC_STATISTICS_64BIT},
    {"LINE_MAC_MM_CONFIG", 0x0000f375, 0x00000001, 0x00000002, regs_within_LINE_MAC_LINE_MAC_MM_CONFIG},
    {"LINE_MAC_MM_STATISTICS", 0x0000f377, 0x00000001, 0x00000001, regs_within_LINE_MAC_LINE_MAC_MM_STATISTICS},
    {"LINE_MAC_DEBUG", 0x0000f378, 0x00000001, 0x00000008, regs_within_LINE_MAC_LINE_MAC_DEBUG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_HOST_MAC_HOST_MAC_CONFIG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"HOST_MAC_MAC_ENA_CFG", 0x00000000, 0x00000001, 0x00000001},
    {"HOST_MAC_MAC_MODE_CFG", 0x00000001, 0x00000001, 0x00000001},
    {"HOST_MAC_MAC_MAXLEN_CFG", 0x00000002, 0x00000001, 0x00000001},
    {"HOST_MAC_MAC_NUM_TAGS_CFG", 0x00000003, 0x00000001, 0x00000001},
    {"HOST_MAC_MAC_TAGS_CFG", 0x00000004, 0x00000003, 0x00000001},
    {"HOST_MAC_MAC_ADV_CHK_CFG", 0x00000007, 0x00000001, 0x00000001},
    {"HOST_MAC_MAC_LFS_CFG", 0x00000008, 0x00000001, 0x00000001},
    {"HOST_MAC_MAC_LB_CFG", 0x00000009, 0x00000001, 0x00000001},
    {"HOST_MAC_MAC_PKTINF_CFG", 0x0000000a, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_MAC_HOST_MAC_PAUSE_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"HOST_MAC_PAUSE_TX_FRAME_CONTROL", 0x00000000, 0x00000001, 0x00000001},
    {"HOST_MAC_PAUSE_TX_FRAME_CONTROL_2", 0x00000001, 0x00000001, 0x00000001},
    {"HOST_MAC_PAUSE_RX_FRAME_CONTROL", 0x00000002, 0x00000001, 0x00000001},
    {"HOST_MAC_PAUSE_STATE", 0x00000003, 0x00000001, 0x00000001},
    {"HOST_MAC_MAC_ADDRESS_LSB", 0x00000004, 0x00000001, 0x00000001},
    {"HOST_MAC_MAC_ADDRESS_MSB", 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_MAC_HOST_MAC_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"HOST_MAC_MAC_RX_LANE_STICKY_0", 0x00000000, 0x00000001, 0x00000001},
    {"HOST_MAC_MAC_RX_LANE_STICKY_1", 0x00000001, 0x00000001, 0x00000001},
    {"HOST_MAC_MAC_TX_MONITOR_STICKY", 0x00000002, 0x00000001, 0x00000001},
    {"HOST_MAC_MAC_TX_MONITOR_STICKY_MASK", 0x00000003, 0x00000001, 0x00000001},
    {"HOST_MAC_MAC_STICKY", 0x00000004, 0x00000001, 0x00000001},
    {"HOST_MAC_MAC_STICKY_MASK", 0x00000005, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_STICKY", 0x00000006, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_MAC_STICKY_MASK", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_MAC_HOST_MAC_STATISTICS_32BIT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"HOST_MAC_RX_XGMII_PROT_ERR_CNT", 0x00000000, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_SYMBOL_ERR_CNT", 0x00000001, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_PAUSE_CNT", 0x00000002, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_UNSUP_OPCODE_CNT", 0x00000003, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_UC_CNT", 0x00000004, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_MC_CNT", 0x00000005, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_BC_CNT", 0x00000006, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_CRC_ERR_CNT", 0x00000007, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_UNDERSIZE_CNT", 0x00000008, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_FRAGMENTS_CNT", 0x00000009, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_IN_RANGE_LEN_ERR_CNT", 0x0000000a, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_OUT_OF_RANGE_LEN_ERR_CNT", 0x0000000b, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_OVERSIZE_CNT", 0x0000000c, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_JABBERS_CNT", 0x0000000d, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_SIZE64_CNT", 0x0000000e, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_SIZE65TO127_CNT", 0x0000000f, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_SIZE128TO255_CNT", 0x00000010, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_SIZE256TO511_CNT", 0x00000011, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_SIZE512TO1023_CNT", 0x00000012, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_SIZE1024TO1518_CNT", 0x00000013, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_SIZE1519TOMAX_CNT", 0x00000014, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_IPG_SHRINK_CNT", 0x00000015, 0x00000001, 0x00000001},
    {"HOST_MAC_TX_PAUSE_CNT", 0x00000016, 0x00000001, 0x00000001},
    {"HOST_MAC_TX_UC_CNT", 0x00000017, 0x00000001, 0x00000001},
    {"HOST_MAC_TX_MC_CNT", 0x00000018, 0x00000001, 0x00000001},
    {"HOST_MAC_TX_BC_CNT", 0x00000019, 0x00000001, 0x00000001},
    {"HOST_MAC_TX_SIZE64_CNT", 0x0000001a, 0x00000001, 0x00000001},
    {"HOST_MAC_TX_SIZE65TO127_CNT", 0x0000001b, 0x00000001, 0x00000001},
    {"HOST_MAC_TX_SIZE128TO255_CNT", 0x0000001c, 0x00000001, 0x00000001},
    {"HOST_MAC_TX_SIZE256TO511_CNT", 0x0000001d, 0x00000001, 0x00000001},
    {"HOST_MAC_TX_SIZE512TO1023_CNT", 0x0000001e, 0x00000001, 0x00000001},
    {"HOST_MAC_TX_SIZE1024TO1518_CNT", 0x0000001f, 0x00000001, 0x00000001},
    {"HOST_MAC_TX_SIZE1519TOMAX_CNT", 0x00000020, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_ALIGNMENT_LOST_CNT", 0x00000021, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_TAGGED_FRMS_CNT", 0x00000022, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_UNTAGGED_FRMS_CNT", 0x00000023, 0x00000001, 0x00000001},
    {"HOST_MAC_TX_TAGGED_FRMS_CNT", 0x00000024, 0x00000001, 0x00000001},
    {"HOST_MAC_TX_UNTAGGED_FRMS_CNT", 0x00000025, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_XGMII_PROT_ERR_CNT", 0x00000026, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_SYMBOL_ERR_CNT", 0x00000027, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_PAUSE_CNT", 0x00000028, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_UNSUP_OPCODE_CNT", 0x00000029, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_UC_CNT", 0x0000002a, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_MC_CNT", 0x0000002b, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_BC_CNT", 0x0000002c, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_CRC_ERR_CNT", 0x0000002d, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_UNDERSIZE_CNT", 0x0000002e, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_FRAGMENTS_CNT", 0x0000002f, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_IN_RANGE_LEN_ERR_CNT", 0x00000030, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT", 0x00000031, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_OVERSIZE_CNT", 0x00000032, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_JABBERS_CNT", 0x00000033, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_SIZE64_CNT", 0x00000034, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_SIZE65TO127_CNT", 0x00000035, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_SIZE128TO255_CNT", 0x00000036, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_SIZE256TO511_CNT", 0x00000037, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_SIZE512TO1023_CNT", 0x00000038, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_SIZE1024TO1518_CNT", 0x00000039, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_SIZE1519TOMAX_CNT", 0x0000003a, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_TX_PAUSE_CNT", 0x0000003b, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_TX_UC_CNT", 0x0000003c, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_TX_MC_CNT", 0x0000003d, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_TX_BC_CNT", 0x0000003e, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_TX_SIZE64_CNT", 0x0000003f, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_TX_SIZE65TO127_CNT", 0x00000040, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_TX_SIZE128TO255_CNT", 0x00000041, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_TX_SIZE256TO511_CNT", 0x00000042, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_TX_SIZE512TO1023_CNT", 0x00000043, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_TX_SIZE1024TO1518_CNT", 0x00000044, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_TX_SIZE1519TOMAX_CNT", 0x00000045, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_ALIGNMENT_LOST_CNT", 0x00000046, 0x00000001, 0x00000001},
    {"HOST_MAC_MM_RX_ASSEMBLY_ERR_CNT", 0x00000047, 0x00000001, 0x00000001},
    {"HOST_MAC_MM_RX_SMD_ERR_CNT", 0x00000048, 0x00000001, 0x00000001},
    {"HOST_MAC_MM_RX_ASSEMBLY_OK_CNT", 0x00000049, 0x00000001, 0x00000001},
    {"HOST_MAC_MM_RX_MERGE_FRAG_CNT", 0x0000004a, 0x00000001, 0x00000001},
    {"HOST_MAC_MM_TX_PFRAGMENT_CNT", 0x0000004b, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_MAC_HOST_MAC_STATISTICS_64BIT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"HOST_MAC_RX_BAD_BYTES_CNT", 0x00000000, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_BAD_BYTES_MSB_CNT", 0x00000001, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_OK_BYTES_CNT", 0x00000002, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_OK_BYTES_MSB_CNT", 0x00000003, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_IN_BYTES_CNT", 0x00000004, 0x00000001, 0x00000001},
    {"HOST_MAC_RX_IN_BYTES_MSB_CNT", 0x00000005, 0x00000001, 0x00000001},
    {"HOST_MAC_TX_OK_BYTES_CNT", 0x00000006, 0x00000001, 0x00000001},
    {"HOST_MAC_TX_OK_BYTES_MSB_CNT", 0x00000007, 0x00000001, 0x00000001},
    {"HOST_MAC_TX_OUT_BYTES_CNT", 0x00000008, 0x00000001, 0x00000001},
    {"HOST_MAC_TX_OUT_BYTES_MSB_CNT", 0x00000009, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_OK_BYTES_CNT", 0x0000000a, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_OK_BYTES_MSB_CNT", 0x0000000b, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_BAD_BYTES_CNT", 0x0000000c, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_RX_BAD_BYTES_MSB_CNT", 0x0000000d, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_TX_OK_BYTES_CNT", 0x0000000e, 0x00000001, 0x00000001},
    {"HOST_MAC_PMAC_TX_OK_BYTES_MSB_CNT", 0x0000000f, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_MAC_HOST_MAC_MM_CONFIG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"HOST_MAC_ENABLE_CONFIG", 0x00000000, 0x00000001, 0x00000001},
    {"HOST_MAC_VERIF_CONFIG", 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_MAC_HOST_MAC_MM_STATISTICS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"HOST_MAC_MM_STATUS", 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HOST_MAC_HOST_MAC_DEBUG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"HOST_MAC_DEBUG_RO_0", 0x00000000, 0x00000001, 0x00000001},
    {"HOST_MAC_DEBUG_RO_1", 0x00000001, 0x00000001, 0x00000001},
    {"HOST_MAC_DEBUG_RO_2", 0x00000002, 0x00000001, 0x00000001},
    {"HOST_MAC_DEBUG_RO_3", 0x00000003, 0x00000001, 0x00000001},
    {"HOST_MAC_DEBUG_RO_4", 0x00000004, 0x00000001, 0x00000001},
    {"HOST_MAC_DEBUG_RO_5", 0x00000005, 0x00000001, 0x00000001},
    {"HOST_MAC_DEBUG_RO_6", 0x00000006, 0x00000001, 0x00000001},
    {"HOST_MAC_DEBUG_RW", 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_HOST_MAC[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"HOST_MAC_CONFIG", 0x0000f100, 0x00000001, 0x0000000b, regs_within_HOST_MAC_HOST_MAC_CONFIG},
    {"HOST_MAC_PAUSE_CFG", 0x0000f10b, 0x00000001, 0x00000006, regs_within_HOST_MAC_HOST_MAC_PAUSE_CFG},
    {"HOST_MAC_STATUS", 0x0000f111, 0x00000001, 0x00000008, regs_within_HOST_MAC_HOST_MAC_STATUS},
    {"HOST_MAC_STATISTICS_32BIT", 0x0000f119, 0x00000001, 0x0000004c, regs_within_HOST_MAC_HOST_MAC_STATISTICS_32BIT},
    {"HOST_MAC_STATISTICS_64BIT", 0x0000f165, 0x00000001, 0x00000010, regs_within_HOST_MAC_HOST_MAC_STATISTICS_64BIT},
    {"HOST_MAC_MM_CONFIG", 0x0000f175, 0x00000001, 0x00000002, regs_within_HOST_MAC_HOST_MAC_MM_CONFIG},
    {"HOST_MAC_MM_STATISTICS", 0x0000f177, 0x00000001, 0x00000001, regs_within_HOST_MAC_HOST_MAC_MM_STATISTICS},
    {"HOST_MAC_DEBUG", 0x0000f178, 0x00000001, 0x00000008, regs_within_HOST_MAC_HOST_MAC_DEBUG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_target_t vtss_symreg_targets[] = {
    //target name         , repl, tgt_id    , base_addr                  , register group list
    {"HOST_PMA",   -1, 0x00000041, VTSS_IO_OFFSET0(0x00000000), reggrps_within_HOST_PMA},
    {"LINE_PMA",   -1, 0x00000001, VTSS_IO_OFFSET0(0x00000000), reggrps_within_LINE_PMA},
    {"HOST_PMA_8BIT",   -1, 0x00000050, VTSS_IO_OFFSET0(0x00000000), reggrps_within_HOST_PMA_8BIT},
    {"LINE_PMA_8BIT",   -1, 0x00000010, VTSS_IO_OFFSET0(0x00000000), reggrps_within_LINE_PMA_8BIT},
    {"HOST_PCS_CFG",   -1, 0x00000047, VTSS_IO_OFFSET0(0x00000000), reggrps_within_HOST_PCS_CFG},
    {"LINE_PCS_CFG",   -1, 0x00000007, VTSS_IO_OFFSET0(0x00000000), reggrps_within_LINE_PCS_CFG},
    {"HOST_PCS25G",   -1, 0x00000043, VTSS_IO_OFFSET0(0x00000000), reggrps_within_HOST_PCS25G},
    {"LINE_PCS25G",   -1, 0x00000003, VTSS_IO_OFFSET0(0x00000000), reggrps_within_LINE_PCS25G},
    {"HOST_RSFEC",   -1, 0x00000053, VTSS_IO_OFFSET0(0x00000000), reggrps_within_HOST_RSFEC},
    {"LINE_RSFEC",   -1, 0x00000013, VTSS_IO_OFFSET0(0x00000000), reggrps_within_LINE_RSFEC},
    {"HOST_KR",   -1, 0x00000048, VTSS_IO_OFFSET0(0x00000000), reggrps_within_HOST_KR},
    {"LINE_KR",   -1, 0x00000008, VTSS_IO_OFFSET0(0x00000000), reggrps_within_LINE_KR},
    {"HOST_INTR_CTRL",   -1, 0x00000049, VTSS_IO_OFFSET0(0x00000000), reggrps_within_HOST_INTR_CTRL},
    {"LINE_INTR_CTRL",   -1, 0x00000009, VTSS_IO_OFFSET0(0x00000000), reggrps_within_LINE_INTR_CTRL},
    {"HOST_SLICE",   -1, 0x00000052, VTSS_IO_OFFSET0(0x00000000), reggrps_within_HOST_SLICE},
    {"LINE_SLICE",   -1, 0x00000012, VTSS_IO_OFFSET0(0x00000000), reggrps_within_LINE_SLICE},
    {"PKT_BIST",   -1, 0x00000011, VTSS_IO_OFFSET0(0x00000000), reggrps_within_PKT_BIST},
    {"SFP_TWS",   -1, 0x0000000f, VTSS_IO_OFFSET0(0x00000000), reggrps_within_SFP_TWS},
    {"PTP_PROC",   -1, 0x00000062, VTSS_IO_OFFSET0(0x00000000), reggrps_within_PTP_PROC},
    {"PTP_ANA0_INGR_CFG",   -1, 0x00000064, VTSS_IO_OFFSET0(0x00000000), reggrps_within_PTP_ANA0_INGR_CFG},
    {"PTP_ANA0_EGR_CFG",   -1, 0x00000065, VTSS_IO_OFFSET0(0x00000000), reggrps_within_PTP_ANA0_EGR_CFG},
    {"PTP_ANA1_INGR_CFG",   -1, 0x00000066, VTSS_IO_OFFSET0(0x00000000), reggrps_within_PTP_ANA1_INGR_CFG},
    {"PTP_ANA1_EGR_CFG",   -1, 0x00000067, VTSS_IO_OFFSET0(0x00000000), reggrps_within_PTP_ANA1_EGR_CFG},
    {"PTP_ANA2_INGR_CFG",   -1, 0x00000068, VTSS_IO_OFFSET0(0x00000000), reggrps_within_PTP_ANA2_INGR_CFG},
    {"PTP_ANA2_EGR_CFG",   -1, 0x00000069, VTSS_IO_OFFSET0(0x00000000), reggrps_within_PTP_ANA2_EGR_CFG},
    {"CROSS_CONNECT",   -1, 0x0000006d, VTSS_IO_OFFSET0(0x00000000), reggrps_within_CROSS_CONNECT},
    {"GPIO_CTRL",   -1, 0x0000006e, VTSS_IO_OFFSET0(0x00000000), reggrps_within_GPIO_CTRL},
    {"MCU_IO_MNGT_MISC",   -1, 0x0000007e, VTSS_IO_OFFSET0(0x00000000), reggrps_within_MCU_IO_MNGT_MISC},
    {"MCU_MAILBOX",   -1, 0x0000007f, VTSS_IO_OFFSET0(0x00000000), reggrps_within_MCU_MAILBOX},
    {"GLOBAL",   -1, 0x00000061, VTSS_IO_OFFSET0(0x00000000), reggrps_within_GLOBAL},
    {"CLK_CFG",   -1, 0x00000070, VTSS_IO_OFFSET0(0x00000000), reggrps_within_CLK_CFG},
    {"PTP_LTC",   -1, 0x00000060, VTSS_IO_OFFSET0(0x00000000), reggrps_within_PTP_LTC},
    {"PTP_STI",   -1, 0x00000063, VTSS_IO_OFFSET0(0x00000000), reggrps_within_PTP_STI},
    {"GLOBAL_FAST_RESET",   -1, 0x000000ff, VTSS_IO_OFFSET0(0x00000000), reggrps_within_GLOBAL_FAST_RESET},
    {"DEV_ORG_VER2",    0, 0x00000000, VTSS_IO_OFFSET0(0x00000000), reggrps_within_DEV_ORG_VER2_0},
    {"DEV_ORG_VER2",    1, 0x00000000, VTSS_IO_OFFSET0(0x00000000), reggrps_within_DEV_ORG_VER2_1},
    {"DEV_ORG_VER2",    2, 0x00000000, VTSS_IO_OFFSET0(0x00000000), reggrps_within_DEV_ORG_VER2_2},
    {"DEV_ORG_VER2",    3, 0x00000000, VTSS_IO_OFFSET0(0x00000000), reggrps_within_DEV_ORG_VER2_3},
    {"DEV_ORG_VER2",    4, 0x00000000, VTSS_IO_OFFSET0(0x00000000), reggrps_within_DEV_ORG_VER2_4},
    {"DEV_ORG_VER2",    5, 0x00000000, VTSS_IO_OFFSET0(0x00000000), reggrps_within_DEV_ORG_VER2_5},
    {"DEV_ORG_VER2",    6, 0x00000000, VTSS_IO_OFFSET0(0x00000000), reggrps_within_DEV_ORG_VER2_6},
    {"DEV_ORG_VER2",    7, 0x00000000, VTSS_IO_OFFSET0(0x00000000), reggrps_within_DEV_ORG_VER2_7},
    {"DEV_ORG_VER2",    8, 0x00000000, VTSS_IO_OFFSET0(0x00000000), reggrps_within_DEV_ORG_VER2_8},
    {"DEV_ORG_VER2",    9, 0x00000000, VTSS_IO_OFFSET0(0x00000000), reggrps_within_DEV_ORG_VER2_9},
    {"DEV_ORG_VER2",   10, 0x00000000, VTSS_IO_OFFSET0(0x00000000), reggrps_within_DEV_ORG_VER2_10},
    {"DEV_ORG_VER2",   11, 0x00000000, VTSS_IO_OFFSET0(0x00000000), reggrps_within_DEV_ORG_VER2_11},
    {"DEV_ORG_VER2",   12, 0x00000000, VTSS_IO_OFFSET0(0x00000000), reggrps_within_DEV_ORG_VER2_12},
    {"DEV_ORG_VER2",   13, 0x00000000, VTSS_IO_OFFSET0(0x00000000), reggrps_within_DEV_ORG_VER2_13},
    {"DEV_ORG_VER2",   14, 0x00000000, VTSS_IO_OFFSET0(0x00000000), reggrps_within_DEV_ORG_VER2_14},
    {"DEV_ORG_VER2",   15, 0x00000000, VTSS_IO_OFFSET0(0x00000000), reggrps_within_DEV_ORG_VER2_15},
    {"DEV_ORG_VER2",   16, 0x00000000, VTSS_IO_OFFSET0(0x00000000), reggrps_within_DEV_ORG_VER2_16},
    {"DEV_ORG_VER2",   17, 0x00000000, VTSS_IO_OFFSET0(0x00000000), reggrps_within_DEV_ORG_VER2_17},
    {"MCU_OTP",   -1, 0x000000fd, VTSS_IO_OFFSET0(0x00000000), reggrps_within_MCU_OTP},
    {"MCU_UART",   -1, 0x000000fe, VTSS_IO_OFFSET0(0x00000000), reggrps_within_MCU_UART},
    {"MCU_WDT",   -1, 0x000000fb, VTSS_IO_OFFSET0(0x00000000), reggrps_within_MCU_WDT},
    {"MCU_TIMER",   -1, 0x000000fc, VTSS_IO_OFFSET0(0x00000000), reggrps_within_MCU_TIMER},
    {"MCU_SPI_MSTR",   -1, 0x000000f9, VTSS_IO_OFFSET0(0x00000000), reggrps_within_MCU_SPI_MSTR},
    {"MCU_MISC_REG",   -1, 0x000000fa, VTSS_IO_OFFSET0(0x00000000), reggrps_within_MCU_MISC_REG},
    {"MACSEC_INGR",   -1, 0x0000000a, VTSS_IO_OFFSET0(0x00000000), reggrps_within_MACSEC_INGR},
    {"MACSEC_EGR",   -1, 0x0000000b, VTSS_IO_OFFSET0(0x00000000), reggrps_within_MACSEC_EGR},
    {"MAC_FC_BUFFER",   -1, 0x0000000c, VTSS_IO_OFFSET0(0x00000000), reggrps_within_MAC_FC_BUFFER},
    {"LINE_MAC",   -1, 0x0000000e, VTSS_IO_OFFSET0(0x00000000), reggrps_within_LINE_MAC},
    {"HOST_MAC",   -1, 0x0000000d, VTSS_IO_OFFSET0(0x00000000), reggrps_within_HOST_MAC},
};

#define SYMREG_REPL_CNT_MAX 512
#define SYMREG_NAME_LEN_MAX 51
vtss_rc vtss_symreg_data_get(const vtss_inst_t inst, vtss_symreg_data_t *const data)
{
    data->targets = vtss_symreg_targets;
    data->targets_cnt = sizeof(vtss_symreg_targets) / sizeof(vtss_symreg_targets[0]);
    data->io_origin1_offset = VTSS_IO_ORIGIN1_OFFSET;
    data->repl_cnt_max = SYMREG_REPL_CNT_MAX;
    data->name_len_max = SYMREG_NAME_LEN_MAX;
    return VTSS_RC_OK;
}

#else /* VTSS_OPT_SYMREG */
vtss_rc vtss_symreg_data_get(const vtss_inst_t inst, vtss_symreg_data_t *const data)
{
    return VTSS_RC_ERROR;
}
#endif /* VTSS_OPT_SYMREG */
#endif /* VTSS_ARCH_MALIBU25G */
