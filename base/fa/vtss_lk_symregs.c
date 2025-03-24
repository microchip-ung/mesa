// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "vtss_fa_cil.h"

#ifdef VTSS_ARCH_LAIKA
#ifdef VTSS_OPT_SYMREG

#define VTSS_IO_ORIGIN1_OFFSET 0x06000000 /*! default region*/
#define VTSS_IO_OFFSET1(offset) (VTSS_IO_ORIGIN1_OFFSET + offset)

static const vtss_symreg_reg_t regs_within_AFI_MISC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MISC_CTRL"                            , 0x00000000, 0x00000001, 0x00000001},
    {"NEW_FRM_CTRL"                         , 0x00000001, 0x00000001, 0x00000001},
    {"NEW_FRM_INFO"                         , 0x00000002, 0x00000001, 0x00000001},
    {"ERR"                                  , 0x00000003, 0x00000001, 0x00000001},
    {"WARN"                                 , 0x00000004, 0x00000001, 0x00000001},
    {"STICKY_INFO"                          , 0x00000005, 0x00000001, 0x00000001},
    {"STICKY_INFO_ENA"                      , 0x00000006, 0x00000001, 0x00000001},
    {"DTI_DURATION_TICK_LEN"                , 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_AFI_FRM_TBL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FRM_NEXT_AND_TYPE"                    , 0x00000000, 0x00000001, 0x00000001},
    {"FRM_ENTRY_PART0"                      , 0x00000001, 0x00000001, 0x00000001},
    {"FRM_ENTRY_PART1"                      , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_AFI_DTI_TBL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DTI_MODE"                             , 0x00000000, 0x00000001, 0x00000001},
    {"DTI_PORT_QU"                          , 0x00000001, 0x00000001, 0x00000001},
    {"DTI_FRM"                              , 0x00000002, 0x00000001, 0x00000001},
    {"DTI_CNT"                              , 0x00000003, 0x00000001, 0x00000001},
    {"DTI_DURATION"                         , 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_AFI_DTI_MISC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DTI_FC_CNT_DOWN"                      , 0x00000000, 0x00000001, 0x00000001},
    {"DTI_CNT_DOWN"                         , 0x00000001, 0x00000001, 0x00000001},
    {"DTI_CTRL"                             , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_AFI_TTI_TBL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TTI_PORT_QU"                          , 0x00000000, 0x00000001, 0x00000001},
    {"TTI_TIMER"                            , 0x00000001, 0x00000001, 0x00000001},
    {"TTI_FRM"                              , 0x00000002, 0x00000001, 0x00000001},
    {"TTI_TICKS"                            , 0x00000003, 0x00000001, 0x00000001},
    {"TTI_MISC_CFG"                         , 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_AFI_TTI_TICKS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TTI_TICK_BASE"                        , 0x00000000, 0x00000001, 0x00000001},
    {"TTI_TICK_LEN_0_3"                     , 0x00000001, 0x00000001, 0x00000001},
    {"TTI_TICK_LEN_4_7"                     , 0x00000002, 0x00000001, 0x00000001},
    {"TTI_TICK_STATE"                       , 0x00000003, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_AFI_TTI_MISC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TTI_CAL_SLOT_PTRS"                    , 0x00000000, 0x00000004, 0x00000001},
    {"TTI_CAL_SLOT_CNT"                     , 0x00000004, 0x00000004, 0x00000001},
    {"TTI_CAL_STATE"                        , 0x00000008, 0x00000004, 0x00000001},
    {"TTI_CTRL"                             , 0x0000000c, 0x00000001, 0x00000001},
    {"TTI_INJ_CNT"                          , 0x0000000e, 0x00000001, 0x00000001},
    {"TTI_RAND_STATE"                       , 0x0000000f, 0x00000001, 0x00000001},
    {"TTI_PORT_FRM_OUT"                     , 0x00000010, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_AFI_PORT_TBL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PORT_FRM_OUT"                         , 0x00000000, 0x00000001, 0x00000001},
    {"PORT_CFG"                             , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_AFI[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"MISC"                                 , 0x000018ca, 0x00000001, 0x00000008, regs_within_AFI_MISC},
    {"FRM_TBL"                              , 0x00001000, 0x00000200, 0x00000004, regs_within_AFI_FRM_TBL},
    {"DTI_TBL"                              , 0x00001800, 0x00000010, 0x00000008, regs_within_AFI_DTI_TBL},
    {"DTI_MISC"                             , 0x000018d2, 0x00000010, 0x00000003, regs_within_AFI_DTI_MISC},
    {"TTI_TBL"                              , 0x00000000, 0x00000200, 0x00000008, regs_within_AFI_TTI_TBL},
    {"TTI_TICKS"                            , 0x00001902, 0x00000001, 0x0000000b, regs_within_AFI_TTI_TICKS},
    {"TTI_MISC"                             , 0x0000190d, 0x00000001, 0x00000011, regs_within_AFI_TTI_MISC},
    {"PORT_TBL"                             , 0x00001880, 0x00000025, 0x00000002, regs_within_AFI_PORT_TBL},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_RAM_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RAM_INIT"                             , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_COREMEM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CM_ADDR"                              , 0x00000000, 0x00000001, 0x00000001},
    {"CM_DATA_WR"                           , 0x00000001, 0x00000001, 0x00000001},
    {"CM_DATA_RD"                           , 0x00000002, 0x00000001, 0x00000001},
    {"CM_OP"                                , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_PS_COMMON[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MISC_CTRL"                            , 0x00000000, 0x00000001, 0x00000001},
    {"PS_COMMON_CFG"                        , 0x00000001, 0x00000001, 0x00000001},
    {"SFLOW_CFG"                            , 0x00000002, 0x00000001, 0x00000001},
    {"SFLOW_RESET_CTRL"                     , 0x00000003, 0x00000001, 0x00000001},
    {"PHYS_SRC_AGGR_CFG"                    , 0x00000004, 0x00000001, 0x00000001},
    {"STACK_CFG"                            , 0x00000007, 0x00000001, 0x00000001},
    {"STACK_A_CFG"                          , 0x0000000a, 0x00000001, 0x00000001},
    {"OWN_UPSID"                            , 0x0000000d, 0x00000001, 0x00000001},
    {"COMMON_VSTAX_CFG"                     , 0x00000010, 0x00000001, 0x00000001},
    {"COMMON_EQUAL_STACK_LINK_TTL_CFG"      , 0x00000011, 0x00000001, 0x00000001},
    {"VSTAX_CTRL"                           , 0x00000012, 0x00000020, 0x00000001},
    {"VSTAX_GMIRROR_CFG"                    , 0x00000053, 0x00000001, 0x00000001},
    {"CPU_CFG"                              , 0x00000056, 0x00000001, 0x00000001},
    {"PS_DBG_CTRL"                          , 0x00000057, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_MIRROR_PROBE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PROBE_CFG"                            , 0x00000000, 0x00000001, 0x00000001},
    {"PROBE_CFG2"                           , 0x00000001, 0x00000001, 0x00000001},
    {"PROBE_PORT_CFG"                       , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_AGGR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AGGR_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_SRC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SRC_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_SFLOW[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SFLOW_CTRL"                           , 0x00000000, 0x00000001, 0x00000001},
    {"SFLOW_CNT"                            , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_UPSID[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STACK_LINK_EQUAL_COST_CFG"            , 0x00000000, 0x00000001, 0x00000001},
    {"UPSID_CFG"                            , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_GLAG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MBR_CNT_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_PGID[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PGID_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
    {"PGID_MISC_CFG"                        , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_CSD[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CSD_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_LAG_RST[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LAG_RST_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_PS_STICKY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STICKY"                               , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_PS_STICKY_MASK[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STICKY_MASK"                          , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_FRER_GEN[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FRER_GEN"                             , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_FRER_GEN_STATE_ACC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FRER_GEN_STATE_ACC"                   , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_FRER_GEN_STATE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FRER_GEN_STATE"                       , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_TSN_SF[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TSN_SF"                               , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_TSN_SF_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TSN_SF_CFG"                           , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_TSN_SF_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TSN_SF_STATUS"                        , 0x00000000, 0x00000001, 0x00000001},
    {"TSTAMP_LO"                            , 0x00000001, 0x00000001, 0x00000001},
    {"TSTAMP_HI"                            , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_SG_ACCESS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SG_ACCESS_CTRL"                       , 0x00000000, 0x00000001, 0x00000001},
    {"SG_PTP_DOMAIN_CFG"                    , 0x00000001, 0x00000001, 0x00000001},
    {"SG_CYCLETIME_UPDATE_PERIOD"           , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_SG_CONFIG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SG_CONFIG_REG_1"                      , 0x0000000c, 0x00000001, 0x00000001},
    {"SG_CONFIG_REG_2"                      , 0x0000000d, 0x00000001, 0x00000001},
    {"SG_CONFIG_REG_3"                      , 0x0000000e, 0x00000001, 0x00000001},
    {"SG_CONFIG_REG_4"                      , 0x0000000f, 0x00000001, 0x00000001},
    {"SG_CONFIG_REG_5"                      , 0x00000010, 0x00000001, 0x00000001},
    {"SG_GCL_GS_CONFIG"                     , 0x00000000, 0x00000004, 0x00000001},
    {"SG_GCL_TI_CONFIG"                     , 0x00000004, 0x00000004, 0x00000001},
    {"SG_GCL_OCT_CONFIG"                    , 0x00000008, 0x00000004, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_SG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SG_STATUS_REG_1"                      , 0x00000000, 0x00000001, 0x00000001},
    {"SG_STATUS_REG_2"                      , 0x00000001, 0x00000001, 0x00000001},
    {"SG_STATUS_REG_3"                      , 0x00000002, 0x00000001, 0x00000001},
    {"SG_STATUS_REG_4"                      , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_SG_STATUS_STICKY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SG_STICKY"                            , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_GLOBAL_CFG_PORT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STAT_GLOBAL_EVENT_MASK"               , 0x00000000, 0x00000004, 0x00000001},
    {"STAT_RESET"                           , 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_CNT_CFG_PORT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STAT_EVENTS_STICKY"                   , 0x00000000, 0x00000001, 0x00000001},
    {"STAT_CFG"                             , 0x00000001, 0x00000004, 0x00000001},
    {"STAT_LSB_CNT"                         , 0x00000005, 0x00000004, 0x00000001},
    {"STAT_MSB_CNT"                         , 0x00000009, 0x00000004, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_GLOBAL_CFG_ACL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GLOBAL_CNT_FRM_TYPE_CFG"              , 0x00000000, 0x00000002, 0x00000001},
    {"STAT_GLOBAL_CFG"                      , 0x00000002, 0x00000002, 0x00000001},
    {"STAT_GLOBAL_EVENT_MASK"               , 0x00000004, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_CNT_CFG_ACL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STAT_LSB_CNT"                         , 0x00000000, 0x00000002, 0x00000001},
    {"STAT_MSB_CNT"                         , 0x00000002, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_GLOBAL_CFG_QUEUE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GLOBAL_CNT_FRM_TYPE_CFG"              , 0x00000000, 0x00000002, 0x00000001},
    {"STAT_GLOBAL_CFG"                      , 0x00000002, 0x00000002, 0x00000001},
    {"STAT_GLOBAL_EVENT_MASK"               , 0x00000004, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_CNT_CFG_QUEUE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STAT_LSB_CNT"                         , 0x00000000, 0x00000002, 0x00000001},
    {"STAT_MSB_CNT"                         , 0x00000002, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_GLOBAL_CFG_ISDX[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GLOBAL_CNT_FRM_TYPE_CFG"              , 0x00000000, 0x00000007, 0x00000001},
    {"STAT_GLOBAL_CFG"                      , 0x00000007, 0x00000007, 0x00000001},
    {"STAT_GLOBAL_EVENT_MASK"               , 0x0000000e, 0x00000007, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_CNT_CFG_ISDX[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STAT_LSB_CNT"                         , 0x00000000, 0x00000007, 0x00000001},
    {"STAT_MSB_CNT"                         , 0x00000007, 0x00000003, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_GLOBAL_CFG_BDLB[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GLOBAL_CNT_FRM_TYPE_CFG"              , 0x00000000, 0x00000002, 0x00000001},
    {"STAT_GLOBAL_CFG"                      , 0x00000002, 0x00000002, 0x00000001},
    {"STAT_GLOBAL_EVENT_MASK"               , 0x00000004, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_CNT_CFG_BDLB[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STAT_LSB_CNT"                         , 0x00000000, 0x00000002, 0x00000001},
    {"STAT_MSB_CNT"                         , 0x00000002, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_GLOBAL_CFG_BUM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GLOBAL_CNT_FRM_TYPE_CFG"              , 0x00000000, 0x00000006, 0x00000001},
    {"STAT_GLOBAL_CFG"                      , 0x00000006, 0x00000006, 0x00000001},
    {"STAT_GLOBAL_EVENT_MASK"               , 0x0000000c, 0x00000006, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_CNT_CFG_BUM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STAT_LSB_CNT"                         , 0x00000000, 0x00000006, 0x00000001},
    {"STAT_MSB_CNT"                         , 0x00000006, 0x00000006, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_GLOBAL_CFG_IRLEG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GLOBAL_CNT_FRM_TYPE_CFG"              , 0x00000000, 0x00000008, 0x00000001},
    {"STAT_GLOBAL_CFG"                      , 0x00000008, 0x00000008, 0x00000001},
    {"STAT_GLOBAL_EVENT_MASK"               , 0x00000010, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_CNT_CFG_IRLEG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STAT_LSB_CNT"                         , 0x00000000, 0x00000008, 0x00000001},
    {"STAT_MSB_CNT"                         , 0x00000008, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_GLOBAL_CFG_ERLEG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GLOBAL_CNT_FRM_TYPE_CFG"              , 0x00000000, 0x00000008, 0x00000001},
    {"STAT_GLOBAL_CFG"                      , 0x00000008, 0x00000008, 0x00000001},
    {"STAT_GLOBAL_EVENT_MASK"               , 0x00000010, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_CNT_CFG_ERLEG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STAT_LSB_CNT"                         , 0x00000000, 0x00000008, 0x00000001},
    {"STAT_MSB_CNT"                         , 0x00000008, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_ANA_AC[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"RAM_CTRL"                             , 0x0000d659, 0x00000001, 0x00000001, regs_within_ANA_AC_RAM_CTRL},
#ifndef VTSS_RELEASE
    {"COREMEM"                              , 0x0000d65a, 0x00000001, 0x00000004, regs_within_ANA_AC_COREMEM},
#endif
    {"PS_COMMON"                            , 0x00010cc0, 0x00000001, 0x00000058, regs_within_ANA_AC_PS_COMMON},
    {"MIRROR_PROBE"                         , 0x0000d745, 0x00000003, 0x00000008, regs_within_ANA_AC_MIRROR_PROBE},
    {"AGGR"                                 , 0x0000d780, 0x00000010, 0x00000004, regs_within_ANA_AC_AGGR},
    {"SRC"                                  , 0x0000d700, 0x00000045, 0x00000001, regs_within_ANA_AC_SRC},
    {"SFLOW"                                , 0x0000d7c0, 0x00000020, 0x00000002, regs_within_ANA_AC_SFLOW},
    {"UPSID"                                , 0x0000d080, 0x00000020, 0x00000004, regs_within_ANA_AC_UPSID},
    {"GLAG"                                 , 0x0000d660, 0x00000020, 0x00000001, regs_within_ANA_AC_GLAG},
    {"PGID"                                 , 0x0000c000, 0x00000420, 0x00000004, regs_within_ANA_AC_PGID},
    {"CSD"                                  , 0x00008000, 0x00001000, 0x00000004, regs_within_ANA_AC_CSD},
    {"LAG_RST"                              , 0x0000d760, 0x00000008, 0x00000004, regs_within_ANA_AC_LAG_RST},
    {"PS_STICKY"                            , 0x0000d65e, 0x00000001, 0x00000001, regs_within_ANA_AC_PS_STICKY},
    {"PS_STICKY_MASK"                       , 0x00010d18, 0x00000004, 0x00000010, regs_within_ANA_AC_PS_STICKY_MASK},
    {"FRER_GEN"                             , 0x0000d800, 0x00000800, 0x00000001, regs_within_ANA_AC_FRER_GEN},
#ifndef VTSS_RELEASE
    {"FRER_GEN_STATE_ACC"                   , 0x0000d65f, 0x00000001, 0x00000001, regs_within_ANA_AC_FRER_GEN_STATE_ACC},
#endif
#ifndef VTSS_RELEASE
    {"FRER_GEN_STATE"                       , 0x0000d658, 0x00000001, 0x00000001, regs_within_ANA_AC_FRER_GEN_STATE},
#endif
    {"TSN_SF"                               , 0x0000d75d, 0x00000001, 0x00000001, regs_within_ANA_AC_TSN_SF},
    {"TSN_SF_CFG"                           , 0x0000d100, 0x00000100, 0x00000001, regs_within_ANA_AC_TSN_SF_CFG},
#ifndef VTSS_RELEASE
    {"TSN_SF_STATUS"                        , 0x0000d650, 0x00000001, 0x00000004, regs_within_ANA_AC_TSN_SF_STATUS},
#endif
    {"SG_ACCESS"                            , 0x00010d58, 0x00000001, 0x00000003, regs_within_ANA_AC_SG_ACCESS},
    {"SG_CONFIG"                            , 0x00010ca0, 0x00000001, 0x00000020, regs_within_ANA_AC_SG_CONFIG},
    {"SG_STATUS"                            , 0x0000d654, 0x00000001, 0x00000004, regs_within_ANA_AC_SG_STATUS},
    {"SG_STATUS_STICKY"                     , 0x0000d75e, 0x00000001, 0x00000001, regs_within_ANA_AC_SG_STATUS_STICKY},
    {"STAT_GLOBAL_CFG_PORT"                 , 0x00010d5b, 0x00000001, 0x00000005, regs_within_ANA_AC_STAT_GLOBAL_CFG_PORT},
    {"STAT_CNT_CFG_PORT"                    , 0x0000d400, 0x00000025, 0x00000010, regs_within_ANA_AC_STAT_CNT_CFG_PORT},
    {"STAT_GLOBAL_CFG_ACL"                  , 0x00010d60, 0x00000001, 0x00000006, regs_within_ANA_AC_STAT_GLOBAL_CFG_ACL},
    {"STAT_CNT_CFG_ACL"                     , 0x0000d680, 0x00000020, 0x00000004, regs_within_ANA_AC_STAT_CNT_CFG_ACL},
    {"STAT_GLOBAL_CFG_QUEUE"                , 0x00010d66, 0x00000001, 0x00000006, regs_within_ANA_AC_STAT_GLOBAL_CFG_QUEUE},
    {"STAT_CNT_CFG_QUEUE"                   , 0x00010800, 0x00000128, 0x00000004, regs_within_ANA_AC_STAT_CNT_CFG_QUEUE},
    {"STAT_GLOBAL_CFG_ISDX"                 , 0x00010d6c, 0x00000001, 0x00000015, regs_within_ANA_AC_STAT_GLOBAL_CFG_ISDX},
    {"STAT_CNT_CFG_ISDX"                    , 0x00000000, 0x00000800, 0x00000010, regs_within_ANA_AC_STAT_CNT_CFG_ISDX},
    {"STAT_GLOBAL_CFG_BDLB"                 , 0x00010d81, 0x00000001, 0x00000006, regs_within_ANA_AC_STAT_GLOBAL_CFG_BDLB},
    {"STAT_CNT_CFG_BDLB"                    , 0x0000d200, 0x00000080, 0x00000004, regs_within_ANA_AC_STAT_CNT_CFG_BDLB},
    {"STAT_GLOBAL_CFG_BUM"                  , 0x00010d87, 0x00000001, 0x00000012, regs_within_ANA_AC_STAT_GLOBAL_CFG_BUM},
    {"STAT_CNT_CFG_BUM"                     , 0x00010000, 0x00000080, 0x00000010, regs_within_ANA_AC_STAT_CNT_CFG_BUM},
    {"STAT_GLOBAL_CFG_IRLEG"                , 0x00010d99, 0x00000001, 0x00000018, regs_within_ANA_AC_STAT_GLOBAL_CFG_IRLEG},
    {"STAT_CNT_CFG_IRLEG"                   , 0x0000e000, 0x00000100, 0x00000010, regs_within_ANA_AC_STAT_CNT_CFG_IRLEG},
    {"STAT_GLOBAL_CFG_ERLEG"                , 0x00010db1, 0x00000001, 0x00000018, regs_within_ANA_AC_STAT_GLOBAL_CFG_ERLEG},
    {"STAT_CNT_CFG_ERLEG"                   , 0x0000f000, 0x00000100, 0x00000010, regs_within_ANA_AC_STAT_CNT_CFG_ERLEG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_OAM_MOD_VOE_SRV_LM_CNT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SRV_LM_CNT_LSB"                       , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PORT_LM_CNT_LSB"                      , 0x00000000, 0x00000001, 0x00000001},
    {"PORT_FRM_CNT_LSB"                     , 0x00000001, 0x00000001, 0x00000001},
    {"PORT_BYTE_CNT_MSB"                    , 0x00000002, 0x00000001, 0x00000001},
    {"PORT_BYTE_CNT_LSB"                    , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TEMP_CNT_REG"                         , 0x00000000, 0x00000001, 0x00000001},
    {"LM_CNT_FRAME"                         , 0x00000001, 0x00000001, 0x00000001},
    {"CCM_LM_INFO_REG"                      , 0x00000002, 0x00000001, 0x00000001},
    {"CCM_LM_TX_B_REG"                      , 0x00000003, 0x00000001, 0x00000001},
    {"CCM_LM_RX_B_REG"                      , 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_OAM_MOD_PDU_MOD_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DM_PTP_DOMAIN_CFG"                    , 0x00000000, 0x00000020, 0x00000001},
    {"PTP_NTP_OFFSET_CFG"                   , 0x00000041, 0x00000003, 0x00000001},
    {"RD_LAST_PORT_LM_CNT_LSB"              , 0x00000044, 0x00000001, 0x00000001},
    {"RD_LAST_PORT_FRM_CNT_LSB"             , 0x00000045, 0x00000001, 0x00000001},
    {"RD_LAST_PORT_BYTE_CNT_MSB"            , 0x00000046, 0x00000001, 0x00000001},
    {"RD_LAST_PORT_BYTE_CNT_LSB"            , 0x00000047, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_ANA_AC_OAM_MOD[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"VOE_SRV_LM_CNT"                       , 0x00000500, 0x00000100, 0x00000001, regs_within_ANA_AC_OAM_MOD_VOE_SRV_LM_CNT},
    {"VOE_PORT_LM_CNT"                      , 0x00000800, 0x00000100, 0x00000004, regs_within_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT},
#ifndef VTSS_RELEASE
    {"OAM_PDU_MOD_CONT"                     , 0x00000000, 0x00000085, 0x00000008, regs_within_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT},
#endif
    {"PDU_MOD_CFG"                          , 0x00000428, 0x00000001, 0x00000048, regs_within_ANA_AC_OAM_MOD_PDU_MOD_CFG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_POL_POL_ALL_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"POL_STORM_RATE_CFG"                   , 0x00000000, 0x00000008, 0x00000001},
    {"POL_STORM_THRES_CFG"                  , 0x00000008, 0x00000008, 0x00000001},
    {"POL_STORM_CTRL"                       , 0x00000010, 0x00000008, 0x00000001},
    {"POL_ACL_RATE_CFG"                     , 0x00000018, 0x00000020, 0x00000001},
    {"POL_ACL_THRES_CFG"                    , 0x00000058, 0x00000020, 0x00000001},
    {"POL_ACL_CTRL"                         , 0x00000098, 0x00000020, 0x00000001},
    {"POL_PORT_FC_CFG"                      , 0x000000d8, 0x00000025, 0x00000001},
    {"POL_ALL_CFG"                          , 0x0000011e, 0x00000001, 0x00000001},
    {"POL_UPD_INT_CFG"                      , 0x0000011f, 0x00000001, 0x00000001},
    {"POL_STICKY"                           , 0x00000120, 0x00000001, 0x00000001},
    {"POL_STICKY1"                          , 0x00000121, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_POL_POL_PORT_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"POL_PORT_THRES_CFG_0"                 , 0x00000000, 0x00000094, 0x00000001},
    {"POL_PORT_THRES_CFG_1"                 , 0x00000200, 0x00000094, 0x00000001},
    {"POL_PORT_RATE_CFG"                    , 0x00000400, 0x00000094, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_POL_POL_PORT_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"POL_PORT_GAP"                         , 0x00000000, 0x00000001, 0x00000001},
    {"POL_PORT_CFG"                         , 0x00000001, 0x00000004, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_POL_PORT_PT_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"ACTION_CTRL"                          , 0x00000000, 0x00000005, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_POL_COMMON_BDLB[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DLB_CTRL"                             , 0x00000000, 0x00000001, 0x00000001},
    {"DLB_STICKY"                           , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_POL_BDLB[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MISC_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
    {"DLB_CFG"                              , 0x00000001, 0x00000001, 0x00000001},
    {"LB_CFG"                               , 0x00000002, 0x00000002, 0x00000001},
    {"LB_BUCKET_VAL"                        , 0x00000004, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_POL_COMMON_BUM_SLB[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DLB_CTRL"                             , 0x00000000, 0x00000001, 0x00000001},
    {"TRAFFIC_MASK_CFG"                     , 0x00000001, 0x00000003, 0x00000001},
    {"SLB_STICKY"                           , 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_POL_BUM_SLB[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MISC_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
    {"SLB_CFG"                              , 0x00000001, 0x00000001, 0x00000001},
    {"LB_CFG"                               , 0x00000002, 0x00000003, 0x00000001},
    {"LB_BUCKET_VAL"                        , 0x00000005, 0x00000003, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_ANA_AC_POL[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"POL_ALL_CFG"                          , 0x00001128, 0x00000001, 0x00000122, regs_within_ANA_AC_POL_POL_ALL_CFG},
    {"POL_PORT_CFG"                         , 0x00000000, 0x00000001, 0x00000800, regs_within_ANA_AC_POL_POL_PORT_CFG},
    {"POL_PORT_CTRL"                        , 0x00001000, 0x00000025, 0x00000008, regs_within_ANA_AC_POL_POL_PORT_CTRL},
    {"PORT_PT_CTRL"                         , 0x0000124a, 0x00000028, 0x00000005, regs_within_ANA_AC_POL_PORT_PT_CTRL},
    {"COMMON_BDLB"                          , 0x00001312, 0x00000001, 0x00000002, regs_within_ANA_AC_POL_COMMON_BDLB},
    {"BDLB"                                 , 0x00000800, 0x00000080, 0x00000008, regs_within_ANA_AC_POL_BDLB},
    {"COMMON_BUM_SLB"                       , 0x00001314, 0x00000001, 0x00000005, regs_within_ANA_AC_POL_COMMON_BUM_SLB},
    {"BUM_SLB"                              , 0x00000c00, 0x00000080, 0x00000008, regs_within_ANA_AC_POL_BUM_SLB},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_SDLB_MISC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"XLB_NEXT_TR_CTRL"                     , 0x00000000, 0x00000001, 0x00000001},
    {"XLB_NEXT_TR_ORG"                      , 0x00000001, 0x00000001, 0x00000001},
    {"XLB_NEXT_TR_NEW"                      , 0x00000002, 0x00000001, 0x00000001},
    {"MISC_CTRL"                            , 0x00000003, 0x00000001, 0x00000001},
    {"MISC_RATE_CTRL"                       , 0x00000004, 0x00000001, 0x00000001},
    {"MARK_ALL_FRMS_RED_SET"                , 0x00000005, 0x00000001, 0x00000001},
    {"MARK_ALL_FRMS_RED_CLR"                , 0x00000006, 0x00000001, 0x00000001},
    {"WARN"                                 , 0x00000007, 0x00000001, 0x00000001},
    {"FAIL"                                 , 0x00000008, 0x00000001, 0x00000001},
    {"TBL_ACC_CTRL"                         , 0x00000009, 0x00000001, 0x00000001},
    {"TBL_ACC_VAL"                          , 0x0000000a, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_SDLB_LBGRP_TBL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"XLB_START"                            , 0x00000000, 0x00000001, 0x00000001},
    {"PUP_INTERVAL"                         , 0x00000001, 0x00000001, 0x00000001},
    {"PUP_CTRL"                             , 0x00000002, 0x00000001, 0x00000001},
    {"LBGRP_MISC"                           , 0x00000003, 0x00000001, 0x00000001},
    {"FRM_RATE_TOKENS"                      , 0x00000004, 0x00000001, 0x00000001},
    {"LBGRP_STATE_TBL"                      , 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_SDLB_LBSET_TBL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PUP_TOKENS"                           , 0x00000000, 0x00000002, 0x00000001},
    {"THRES"                                , 0x00000002, 0x00000002, 0x00000001},
    {"XLB_NEXT"                             , 0x00000004, 0x00000001, 0x00000001},
    {"INH_CTRL"                             , 0x00000005, 0x00000002, 0x00000001},
    {"INH_LBSET_ADDR"                       , 0x00000007, 0x00000001, 0x00000001},
    {"DLB_MISC"                             , 0x00000008, 0x00000001, 0x00000001},
    {"DLB_CFG"                              , 0x00000009, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_ANA_AC_SDLB[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"MISC"                                 , 0x00002000, 0x00000001, 0x0000000b, regs_within_ANA_AC_SDLB_MISC},
    {"LBGRP_TBL"                            , 0x0000200b, 0x00000006, 0x00000006, regs_within_ANA_AC_SDLB_LBGRP_TBL},
    {"LBSET_TBL"                            , 0x00000000, 0x00000200, 0x00000010, regs_within_ANA_AC_SDLB_LBSET_TBL},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_ANA_ACL_COMMON[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_S2_CFG"                          , 0x00000000, 0x00000025, 0x00000001},
    {"SWAP_SIP"                             , 0x00000046, 0x00000020, 0x00000001},
    {"PTP_MISC_CTRL"                        , 0x00000066, 0x00000001, 0x00000001},
    {"SWAP_IP_CTRL"                         , 0x00000067, 0x00000001, 0x00000001},
    {"VCAP_S2_MISC_CTRL"                    , 0x00000068, 0x00000001, 0x00000001},
    {"VCAP_S2_MISC_CTRL2"                   , 0x00000069, 0x00000001, 0x00000001},
    {"VCAP_S2_RLEG_STAT"                    , 0x0000006a, 0x00000004, 0x00000001},
    {"VCAP_S2_FRAGMENT_CFG"                 , 0x0000006e, 0x00000001, 0x00000001},
    {"VCAP_S2_RNG_CTRL"                     , 0x0000006f, 0x00000010, 0x00000001},
    {"VCAP_S2_RNG_VALUE_CFG"                , 0x0000007f, 0x00000010, 0x00000001},
    {"VCAP_S2_RNG_OFFSET_CFG"               , 0x0000008f, 0x00000001, 0x00000001},
    {"VOE_LOOPBACK_CFG"                     , 0x00000090, 0x00000001, 0x00000001},
    {"OWN_UPSID"                            , 0x00000091, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_ACL_PORT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PTP_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
    {"MAPPED_PORT_CFG"                      , 0x00000001, 0x00000001, 0x00000001},
    {"MISC_CFG"                             , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_ACL_KEY_SEL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_S2_KEY_SEL"                      , 0x00000000, 0x00000004, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_ACL_CNT_A[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CNT_A"                                , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_ACL_CNT_B[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CNT_B"                                , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_ACL_PTP_MASTER_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PTP_CLOCK_ID_MSB"                     , 0x00000000, 0x00000001, 0x00000001},
    {"PTP_CLOCK_ID_LSB"                     , 0x00000001, 0x00000001, 0x00000001},
    {"PTP_SRC_PORT_CFG"                     , 0x00000002, 0x00000001, 0x00000001},
    {"PTP_MISC_CFG"                         , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_ACL_STICKY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SEC_LOOKUP_STICKY"                    , 0x00000000, 0x00000004, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_ANA_ACL[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"COMMON"                               , 0x00000800, 0x00000001, 0x00000094, regs_within_ANA_ACL_COMMON},
    {"PORT"                                 , 0x00000894, 0x00000025, 0x00000003, regs_within_ANA_ACL_PORT},
    {"KEY_SEL"                              , 0x00000903, 0x00000065, 0x00000004, regs_within_ANA_ACL_KEY_SEL},
    {"CNT_A"                                , 0x00000000, 0x00000400, 0x00000001, regs_within_ANA_ACL_CNT_A},
    {"CNT_B"                                , 0x00000400, 0x00000400, 0x00000001, regs_within_ANA_ACL_CNT_B},
    {"PTP_MASTER_CFG"                       , 0x00000a97, 0x00000004, 0x00000004, regs_within_ANA_ACL_PTP_MASTER_CFG},
    {"STICKY"                               , 0x00000aa7, 0x00000001, 0x00000004, regs_within_ANA_ACL_STICKY},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_ANA_CL_PORT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CSC_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
    {"FILTER_CTRL"                          , 0x00000001, 0x00000001, 0x00000001},
    {"VLAN_FILTER_CTRL"                     , 0x00000002, 0x00000003, 0x00000001},
    {"ETAG_FILTER_CTRL"                     , 0x00000005, 0x00000001, 0x00000001},
    {"STACKING_CTRL"                        , 0x00000006, 0x00000001, 0x00000001},
    {"VLAN_TPID_CTRL"                       , 0x00000007, 0x00000001, 0x00000001},
    {"VLAN_CTRL"                            , 0x00000008, 0x00000001, 0x00000001},
    {"VLAN_CTRL_2"                          , 0x00000009, 0x00000001, 0x00000001},
    {"PCP_DEI_TRANS_CFG"                    , 0x0000000a, 0x00000010, 0x00000001},
    {"PORT_ID_CFG"                          , 0x0000001a, 0x00000001, 0x00000001},
    {"PCP_DEI_MAP_CFG"                      , 0x0000001b, 0x00000010, 0x00000001},
    {"QOS_CFG"                              , 0x0000002b, 0x00000001, 0x00000001},
    {"MAP_CFG"                              , 0x0000002c, 0x00000002, 0x00000001},
    {"CAPTURE_CFG"                          , 0x0000002e, 0x00000001, 0x00000001},
    {"CAPTURE_Y1731_AG_CFG"                 , 0x0000002f, 0x00000001, 0x00000001},
    {"CAPTURE_GXRP_CFG"                     , 0x00000030, 0x00000001, 0x00000001},
    {"CAPTURE_BPDU_CFG"                     , 0x00000031, 0x00000001, 0x00000001},
    {"ADV_CL_CFG_2"                         , 0x00000032, 0x00000006, 0x00000001},
    {"ADV_CL_CFG"                           , 0x00000038, 0x00000006, 0x00000001},
    {"ADV_PORT_RNG_CTRL"                    , 0x0000003e, 0x00000008, 0x00000001},
    {"ADV_PORT_RNG_VALUE_CFG"               , 0x00000046, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_CL_COMMON[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"OWN_UPSID"                            , 0x00000000, 0x00000001, 0x00000001},
    {"AGGR_CFG"                             , 0x00000003, 0x00000001, 0x00000001},
    {"VLAN_STAG_CFG"                        , 0x00000004, 0x00000003, 0x00000001},
    {"ETAG_CFG"                             , 0x00000007, 0x00000001, 0x00000001},
    {"RTAG_CFG"                             , 0x00000008, 0x00000001, 0x00000001},
    {"CPU_PROTO_QU_CFG"                     , 0x00000009, 0x00000001, 0x00000001},
    {"CPU_8021_QU_CFG"                      , 0x0000000a, 0x00000010, 0x00000001},
    {"CPU_8021_QOS_CFG"                     , 0x0000001a, 0x00000010, 0x00000001},
    {"VRAP_CFG"                             , 0x0000002a, 0x00000001, 0x00000001},
    {"VRAP_HDR_DATA"                        , 0x0000002b, 0x00000001, 0x00000001},
    {"VRAP_HDR_MASK"                        , 0x0000002c, 0x00000001, 0x00000001},
    {"ADV_RNG_CTRL"                         , 0x0000002d, 0x00000008, 0x00000001},
    {"ADV_RNG_VALUE_CFG"                    , 0x00000035, 0x00000008, 0x00000001},
    {"COMMON_VSTAX_CFG"                     , 0x0000003d, 0x00000001, 0x00000001},
    {"CLM_MISC_CTRL"                        , 0x0000003e, 0x00000001, 0x00000001},
    {"CLM_FRAGMENT_CFG"                     , 0x0000003f, 0x00000001, 0x00000001},
    {"DSCP_CFG"                             , 0x00000040, 0x00000040, 0x00000001},
    {"QOS_MAP_CFG"                          , 0x00000080, 0x00000020, 0x00000001},
    {"MPLS_RSV_LBL_CFG"                     , 0x000000a0, 0x00000010, 0x00000001},
    {"CLM_KEY_CFG"                          , 0x000000b0, 0x00000006, 0x00000001},
    {"MPLS_MISC_CFG"                        , 0x000000b6, 0x00000001, 0x00000001},
    {"MPLS_LM_CFG"                          , 0x000000b7, 0x00000001, 0x00000001},
    {"MPLS_CFG"                             , 0x000000b8, 0x00000001, 0x00000001},
    {"OAM_CFG"                              , 0x000000b9, 0x00000001, 0x00000001},
    {"MIP_CTRL"                             , 0x000000ba, 0x00000001, 0x00000001},
    {"GRE_MISC_CFG"                         , 0x000000bb, 0x00000001, 0x00000001},
    {"MISC_CFG"                             , 0x000000bc, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_CL_MPLS_PROFILE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PROFILE_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_CL_MIP_TBL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MIP_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
    {"CCM_HMO_CTRL"                         , 0x00000001, 0x00000001, 0x00000001},
    {"MIP_CL_VID_CTRL"                      , 0x00000002, 0x00000001, 0x00000001},
    {"LBM_MAC_HIGH"                         , 0x00000003, 0x00000001, 0x00000001},
    {"LBM_MAC_LOW"                          , 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_CL_L2CP_TBL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"L2CP_ENTRY_CFG"                       , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_CL_MAP_TBL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SET_CTRL"                             , 0x00000000, 0x00000001, 0x00000001},
    {"MAP_ENTRY"                            , 0x00000001, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_CL_IPT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"ISDX_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
    {"OAM_MEP_CFG"                          , 0x00000001, 0x00000001, 0x00000001},
    {"IPT"                                  , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_CL_PPT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PP_CFG"                               , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_CL_VMID[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LPM_AFFIX"                            , 0x00000000, 0x00000001, 0x00000001},
    {"VD2_CAPTURE_CFG"                      , 0x00000001, 0x00000001, 0x00000001},
    {"VD2_QOS_CFG"                          , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_CL_CSC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CSC_DISC_CFG"                         , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_CL_STICKY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FILTER_STICKY"                        , 0x00000000, 0x00000001, 0x00000001},
    {"VLAN_FILTER_STICKY"                   , 0x00000001, 0x00000003, 0x00000001},
    {"ETAG_FILTER_STICKY"                   , 0x00000004, 0x00000001, 0x00000001},
    {"CLASS_STICKY"                         , 0x00000005, 0x00000001, 0x00000001},
    {"CAT_STICKY"                           , 0x00000006, 0x00000001, 0x00000001},
    {"ADV_CL_MPLS_STICKY"                   , 0x00000007, 0x00000001, 0x00000001},
    {"ADV_CL_STICKY"                        , 0x00000008, 0x00000001, 0x00000001},
    {"MIP_STICKY"                           , 0x00000009, 0x00000001, 0x00000001},
    {"IP_HDR_CHK_STICKY"                    , 0x0000000a, 0x00000001, 0x00000001},
    {"GRE_HDR_CHK_STICKY"                   , 0x0000000b, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_CL_STICKY_MASK[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FILTER_STICKY_MASK"                   , 0x00000000, 0x00000001, 0x00000001},
    {"VLAN_FILTER_STICKY_MASK"              , 0x00000001, 0x00000003, 0x00000001},
    {"ETAG_FILTER_STICKY_MASK"              , 0x00000004, 0x00000001, 0x00000001},
    {"CLASS_STICKY_MASK"                    , 0x00000005, 0x00000001, 0x00000001},
    {"CAT_STICKY_MASK"                      , 0x00000006, 0x00000001, 0x00000001},
    {"MIP_STICKY_MASK"                      , 0x00000007, 0x00000001, 0x00000001},
    {"IP_HDR_CHK_STICKY_MASK"               , 0x00000008, 0x00000001, 0x00000001},
    {"GRE_HDR_CHK_STICKY_MASK"              , 0x00000009, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_ANA_CL[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"PORT"                                 , 0x00006000, 0x00000025, 0x00000080, regs_within_ANA_CL_PORT},
    {"COMMON"                               , 0x000075fc, 0x00000001, 0x000000bd, regs_within_ANA_CL_COMMON},
    {"MPLS_PROFILE"                         , 0x00007280, 0x00000012, 0x00000001, regs_within_ANA_CL_MPLS_PROFILE},
    {"MIP_TBL"                              , 0x00007300, 0x00000020, 0x00000008, regs_within_ANA_CL_MIP_TBL},
    {"L2CP_TBL"                             , 0x00008000, 0x00000600, 0x00000001, regs_within_ANA_CL_L2CP_TBL},
    {"MAP_TBL"                              , 0x00007800, 0x00000080, 0x00000010, regs_within_ANA_CL_MAP_TBL},
    {"IPT"                                  , 0x00004000, 0x00000800, 0x00000004, regs_within_ANA_CL_IPT},
    {"PPT"                                  , 0x00007292, 0x00000001, 0x00000010, regs_within_ANA_CL_PPT},
    {"VMID"                                 , 0x00007400, 0x0000007f, 0x00000004, regs_within_ANA_CL_VMID},
    {"CSC"                                  , 0x00000000, 0x00001000, 0x00000004, regs_within_ANA_CL_CSC},
    {"STICKY"                               , 0x000072a2, 0x00000001, 0x0000000c, regs_within_ANA_CL_STICKY},
    {"STICKY_MASK"                          , 0x000072ae, 0x00000004, 0x0000000a, regs_within_ANA_CL_STICKY_MASK},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_ANA_L2_COMMON[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FWD_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
    {"LRN_CFG"                              , 0x00000001, 0x00000001, 0x00000001},
    {"FILTER_OTHER_CTRL"                    , 0x00000002, 0x00000001, 0x00000001},
    {"FILTER_LOCAL_CTRL"                    , 0x00000003, 0x00000001, 0x00000001},
    {"AUTO_LRN_CFG"                         , 0x00000006, 0x00000001, 0x00000001},
    {"LRN_SECUR_CFG"                        , 0x00000009, 0x00000001, 0x00000001},
    {"LRN_SECUR_LOCKED_CFG"                 , 0x0000000c, 0x00000001, 0x00000001},
    {"LRN_COPY_CFG"                         , 0x0000000f, 0x00000001, 0x00000001},
    {"PORT_DLB_CFG"                         , 0x00000012, 0x00000020, 0x00000001},
    {"PORT_ISDX_LIMIT_CFG"                  , 0x00000053, 0x00000020, 0x00000001},
    {"SCAN_FID_CTRL"                        , 0x00000094, 0x00000001, 0x00000001},
    {"SCAN_FID_CFG"                         , 0x00000095, 0x00000010, 0x00000001},
    {"MOVELOG_STICKY"                       , 0x000000a5, 0x00000001, 0x00000001},
    {"OWN_UPSID"                            , 0x000000a8, 0x00000001, 0x00000001},
    {"VSTAX_CTRL"                           , 0x000000ab, 0x00000001, 0x00000001},
    {"INTR"                                 , 0x000000ac, 0x00000001, 0x00000001},
    {"INTR_ENA"                             , 0x000000ad, 0x00000001, 0x00000001},
    {"INTR_IDENT"                           , 0x000000ae, 0x00000001, 0x00000001},
    {"LRN_SECUR_LOCKED_COPY_CFG"            , 0x000000af, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L2_LRN_LIMIT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FID_LIMIT_STATUS"                     , 0x00000000, 0x00000001, 0x00000001},
    {"FID_LIMIT_CTRL"                       , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L2_ISDX_LIMIT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"ISDX_LIMIT_STATUS"                    , 0x00000000, 0x00000001, 0x00000001},
    {"ISDX_LIMIT_CTRL"                      , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L2_PORT_LIMIT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PORT_LIMIT_STATUS"                    , 0x00000000, 0x00000001, 0x00000001},
    {"PORT_LIMIT_CTRL"                      , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L2_ISDX[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SERVICE_CTRL"                         , 0x00000000, 0x00000001, 0x00000001},
    {"PORT_MASK_CFG"                        , 0x00000001, 0x00000001, 0x00000001},
    {"QGRP_CFG"                             , 0x00000004, 0x00000001, 0x00000001},
    {"MISC_CFG"                             , 0x00000005, 0x00000001, 0x00000001},
    {"DLB_COS_CFG"                          , 0x00000006, 0x00000008, 0x00000001},
    {"DLB_CFG"                              , 0x0000000e, 0x00000001, 0x00000001},
    {"ISDX_BASE_CFG"                        , 0x0000000f, 0x00000001, 0x00000001},
    {"ISDX_COS_CFG"                         , 0x00000010, 0x00000008, 0x00000001},
    {"ISDX_LIMIT_CFG"                       , 0x00000018, 0x00000001, 0x00000001},
    {"TSN_CFG"                              , 0x00000019, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L2_STICKY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STICKY"                               , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L2_STICKY_MASK[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STICKY_MASK"                          , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L2_PMAC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PMAC_ACCESS_CTRL"                     , 0x00000000, 0x00000001, 0x00000001},
    {"PMAC_INDEX"                           , 0x00000001, 0x00000001, 0x00000001},
    {"PMAC_ACCESS_CFG_2"                    , 0x00000002, 0x00000001, 0x00000001},
    {"PMAC_CFG"                             , 0x00000003, 0x00000001, 0x00000001},
    {"PMAC_CFG_2"                           , 0x00000004, 0x00000001, 0x00000001},
    {"PMAC_VLAN_CFG"                        , 0x00000005, 0x00000004, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_ANA_L2[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"COMMON"                               , 0x000224c2, 0x00000001, 0x000000b2, regs_within_ANA_L2_COMMON},
    {"LRN_LIMIT"                            , 0x00020000, 0x00001200, 0x00000002, regs_within_ANA_L2_LRN_LIMIT},
    {"ISDX_LIMIT"                           , 0x00023000, 0x00000100, 0x00000002, regs_within_ANA_L2_ISDX_LIMIT},
    {"PORT_LIMIT"                           , 0x00022400, 0x00000040, 0x00000002, regs_within_ANA_L2_PORT_LIMIT},
    {"ISDX"                                 , 0x00000000, 0x00000800, 0x00000020, regs_within_ANA_L2_ISDX},
    {"STICKY"                               , 0x00022574, 0x00000001, 0x00000001, regs_within_ANA_L2_STICKY},
    {"STICKY_MASK"                          , 0x00022575, 0x00000004, 0x00000001, regs_within_ANA_L2_STICKY_MASK},
    {"PMAC"                                 , 0x00022579, 0x00000001, 0x00000009, regs_within_ANA_L2_PMAC},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_ANA_L3_COMMON[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MISC_CTRL"                            , 0x00000000, 0x00000001, 0x00000001},
    {"VLAN_CTRL"                            , 0x00000001, 0x00000001, 0x00000001},
    {"L3_UC_ENA"                            , 0x00000002, 0x00000001, 0x00000001},
    {"L3_MC_ENA"                            , 0x00000005, 0x00000001, 0x00000001},
    {"SKIP_RLEG_DMAC_CHK"                   , 0x00000008, 0x00000001, 0x00000001},
    {"PORT_FWD_CTRL"                        , 0x0000000b, 0x00000001, 0x00000001},
    {"PORT_LRN_CTRL"                        , 0x0000000e, 0x00000001, 0x00000001},
    {"VLAN_FILTER_CTRL"                     , 0x00000011, 0x00000001, 0x00000001},
    {"VLAN_ISOLATED_CFG"                    , 0x00000014, 0x00000001, 0x00000001},
    {"VLAN_COMMUNITY_CFG"                   , 0x00000017, 0x00000001, 0x00000001},
    {"ROUTING_CFG"                          , 0x0000001a, 0x00000001, 0x00000001},
    {"ROUTING_CFG2"                         , 0x0000001b, 0x00000001, 0x00000001},
    {"RLEG_CFG_0"                           , 0x0000001c, 0x00000001, 0x00000001},
    {"RLEG_CFG_1"                           , 0x0000001d, 0x00000001, 0x00000001},
    {"CPU_QU_CFG"                           , 0x0000001e, 0x00000001, 0x00000001},
    {"CPU_QU_CFG2"                          , 0x0000001f, 0x00000001, 0x00000001},
    {"VRRP_IP4_CFG_0"                       , 0x00000020, 0x00000001, 0x00000001},
    {"VRRP_IP4_CFG_1"                       , 0x00000021, 0x00000001, 0x00000001},
    {"VRRP_IP6_CFG_0"                       , 0x00000022, 0x00000001, 0x00000001},
    {"VRRP_IP6_CFG_1"                       , 0x00000023, 0x00000001, 0x00000001},
    {"SIP_SECURE_ENA"                       , 0x00000024, 0x00000001, 0x00000001},
    {"SIP_SECURE_ENA1"                      , 0x00000025, 0x00000001, 0x00000001},
    {"DIP_SECURE_ENA"                       , 0x00000027, 0x00000001, 0x00000001},
    {"SIP_RPF_ENA"                          , 0x0000002a, 0x00000001, 0x00000001},
    {"SIP_RPF_ENA1"                         , 0x0000002b, 0x00000001, 0x00000001},
    {"SERVICE_CFG"                          , 0x0000002d, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L3_VLAN[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VMID_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
    {"BUM_CFG"                              , 0x00000001, 0x00000001, 0x00000001},
    {"VLAN_CFG"                             , 0x00000002, 0x00000001, 0x00000001},
    {"TUPE_CTRL"                            , 0x00000003, 0x00000001, 0x00000001},
    {"VLAN_MASK_CFG"                        , 0x00000004, 0x00000001, 0x00000001},
    {"QGRP_CFG"                             , 0x00000007, 0x00000001, 0x00000001},
    {"MISC"                                 , 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L3_MSTP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MSTP_FWD_CFG"                         , 0x00000000, 0x00000001, 0x00000001},
    {"MSTP_LRN_CFG"                         , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L3_VMID[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RLEG_CTRL"                            , 0x00000000, 0x00000001, 0x00000001},
    {"VRRP_CFG"                             , 0x00000001, 0x00000004, 0x00000001},
    {"VMID_MC"                              , 0x00000005, 0x00000001, 0x00000001},
    {"SIP_RPF"                              , 0x00000006, 0x00000001, 0x00000001},
    {"MAX_LEN"                              , 0x00000007, 0x00000001, 0x00000001},
    {"VMID_ENCAP"                           , 0x00000008, 0x00000001, 0x00000001},
    {"VMID_MISC"                            , 0x00000009, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L3_ARP_PTR_REMAP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"ARP_PTR_REMAP_CFG"                    , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L3_ARP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"ARP_CFG_0"                            , 0x00000000, 0x00000001, 0x00000001},
    {"ARP_CFG_1"                            , 0x00000001, 0x00000001, 0x00000001},
    {"ARP_CFG_2"                            , 0x00000002, 0x00000001, 0x00000001},
    {"ARP_ENCAP"                            , 0x00000003, 0x00000001, 0x00000001},
    {"ARP_MISC"                             , 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L3_L3MC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EVMID_MASK_CFG"                       , 0x00000000, 0x00000004, 0x00000001},
    {"L3MC_CTRL"                            , 0x00000004, 0x00000001, 0x00000001},
    {"L3MC_NEXT_PTR"                        , 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L3_LPM_REMAP_STICKY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"L3_LPM_REMAP_STICKY"                  , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L3_VLAN_ARP_L3MC_STICKY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VLAN_STICKY"                          , 0x00000000, 0x00000001, 0x00000001},
    {"L3_ARP_IPMC_STICKY"                   , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L3_L3_STICKY_MASK[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RLEG_STICKY_MASK"                     , 0x00000000, 0x00000001, 0x00000001},
    {"ROUT_STICKY_MASK"                     , 0x00000001, 0x00000001, 0x00000001},
    {"SECUR_STICKY_MASK"                    , 0x00000002, 0x00000001, 0x00000001},
    {"VLAN_MSTP_STICKY_MASK"                , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_ANA_L3[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"COMMON"                               , 0x00016a10, 0x00000001, 0x0000002e, regs_within_ANA_L3_COMMON},
    {"VLAN"                                 , 0x00000000, 0x00001200, 0x00000010, regs_within_ANA_L3_VLAN},
    {"MSTP"                                 , 0x00016800, 0x00000042, 0x00000008, regs_within_ANA_L3_MSTP},
    {"VMID"                                 , 0x00016000, 0x0000007f, 0x00000010, regs_within_ANA_L3_VMID},
    {"ARP_PTR_REMAP"                        , 0x00016a40, 0x00000040, 0x00000001, regs_within_ANA_L3_ARP_PTR_REMAP},
    {"ARP"                                  , 0x00012000, 0x00000400, 0x00000008, regs_within_ANA_L3_ARP},
    {"L3MC"                                 , 0x00014000, 0x00000400, 0x00000008, regs_within_ANA_L3_L3MC},
    {"LPM_REMAP_STICKY"                     , 0x000167f0, 0x00000001, 0x00000001, regs_within_ANA_L3_LPM_REMAP_STICKY},
    {"VLAN_ARP_L3MC_STICKY"                 , 0x000167f1, 0x00000001, 0x00000002, regs_within_ANA_L3_VLAN_ARP_L3MC_STICKY},
    {"L3_STICKY_MASK"                       , 0x00016a80, 0x00000004, 0x00000004, regs_within_ANA_L3_L3_STICKY_MASK},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_ASM_DEV_STATISTICS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RX_IN_BYTES_CNT"                      , 0x00000000, 0x00000001, 0x00000001},
    {"RX_SYMBOL_ERR_CNT"                    , 0x00000001, 0x00000001, 0x00000001},
    {"RX_PAUSE_CNT"                         , 0x00000002, 0x00000001, 0x00000001},
    {"RX_UNSUP_OPCODE_CNT"                  , 0x00000003, 0x00000001, 0x00000001},
    {"RX_OK_BYTES_CNT"                      , 0x00000004, 0x00000001, 0x00000001},
    {"RX_BAD_BYTES_CNT"                     , 0x00000005, 0x00000001, 0x00000001},
    {"RX_UC_CNT"                            , 0x00000006, 0x00000001, 0x00000001},
    {"RX_MC_CNT"                            , 0x00000007, 0x00000001, 0x00000001},
    {"RX_BC_CNT"                            , 0x00000008, 0x00000001, 0x00000001},
    {"RX_CRC_ERR_CNT"                       , 0x00000009, 0x00000001, 0x00000001},
    {"RX_UNDERSIZE_CNT"                     , 0x0000000a, 0x00000001, 0x00000001},
    {"RX_FRAGMENTS_CNT"                     , 0x0000000b, 0x00000001, 0x00000001},
    {"RX_IN_RANGE_LEN_ERR_CNT"              , 0x0000000c, 0x00000001, 0x00000001},
    {"RX_OUT_OF_RANGE_LEN_ERR_CNT"          , 0x0000000d, 0x00000001, 0x00000001},
    {"RX_OVERSIZE_CNT"                      , 0x0000000e, 0x00000001, 0x00000001},
    {"RX_JABBERS_CNT"                       , 0x0000000f, 0x00000001, 0x00000001},
    {"RX_SIZE64_CNT"                        , 0x00000010, 0x00000001, 0x00000001},
    {"RX_SIZE65TO127_CNT"                   , 0x00000011, 0x00000001, 0x00000001},
    {"RX_SIZE128TO255_CNT"                  , 0x00000012, 0x00000001, 0x00000001},
    {"RX_SIZE256TO511_CNT"                  , 0x00000013, 0x00000001, 0x00000001},
    {"RX_SIZE512TO1023_CNT"                 , 0x00000014, 0x00000001, 0x00000001},
    {"RX_SIZE1024TO1518_CNT"                , 0x00000015, 0x00000001, 0x00000001},
    {"RX_SIZE1519TOMAX_CNT"                 , 0x00000016, 0x00000001, 0x00000001},
    {"RX_IPG_SHRINK_CNT"                    , 0x00000017, 0x00000001, 0x00000001},
    {"TX_OUT_BYTES_CNT"                     , 0x00000018, 0x00000001, 0x00000001},
    {"TX_PAUSE_CNT"                         , 0x00000019, 0x00000001, 0x00000001},
    {"TX_OK_BYTES_CNT"                      , 0x0000001a, 0x00000001, 0x00000001},
    {"TX_UC_CNT"                            , 0x0000001b, 0x00000001, 0x00000001},
    {"TX_MC_CNT"                            , 0x0000001c, 0x00000001, 0x00000001},
    {"TX_BC_CNT"                            , 0x0000001d, 0x00000001, 0x00000001},
    {"TX_SIZE64_CNT"                        , 0x0000001e, 0x00000001, 0x00000001},
    {"TX_SIZE65TO127_CNT"                   , 0x0000001f, 0x00000001, 0x00000001},
    {"TX_SIZE128TO255_CNT"                  , 0x00000020, 0x00000001, 0x00000001},
    {"TX_SIZE256TO511_CNT"                  , 0x00000021, 0x00000001, 0x00000001},
    {"TX_SIZE512TO1023_CNT"                 , 0x00000022, 0x00000001, 0x00000001},
    {"TX_SIZE1024TO1518_CNT"                , 0x00000023, 0x00000001, 0x00000001},
    {"TX_SIZE1519TOMAX_CNT"                 , 0x00000024, 0x00000001, 0x00000001},
    {"RX_ALIGNMENT_LOST_CNT"                , 0x00000025, 0x00000001, 0x00000001},
    {"RX_TAGGED_FRMS_CNT"                   , 0x00000026, 0x00000001, 0x00000001},
    {"RX_UNTAGGED_FRMS_CNT"                 , 0x00000027, 0x00000001, 0x00000001},
    {"TX_TAGGED_FRMS_CNT"                   , 0x00000028, 0x00000001, 0x00000001},
    {"TX_UNTAGGED_FRMS_CNT"                 , 0x00000029, 0x00000001, 0x00000001},
    {"PMAC_RX_SYMBOL_ERR_CNT"               , 0x0000002a, 0x00000001, 0x00000001},
    {"PMAC_RX_PAUSE_CNT"                    , 0x0000002b, 0x00000001, 0x00000001},
    {"PMAC_RX_UNSUP_OPCODE_CNT"             , 0x0000002c, 0x00000001, 0x00000001},
    {"PMAC_RX_OK_BYTES_CNT"                 , 0x0000002d, 0x00000001, 0x00000001},
    {"PMAC_RX_BAD_BYTES_CNT"                , 0x0000002e, 0x00000001, 0x00000001},
    {"PMAC_RX_UC_CNT"                       , 0x0000002f, 0x00000001, 0x00000001},
    {"PMAC_RX_MC_CNT"                       , 0x00000030, 0x00000001, 0x00000001},
    {"PMAC_RX_BC_CNT"                       , 0x00000031, 0x00000001, 0x00000001},
    {"PMAC_RX_CRC_ERR_CNT"                  , 0x00000032, 0x00000001, 0x00000001},
    {"PMAC_RX_UNDERSIZE_CNT"                , 0x00000033, 0x00000001, 0x00000001},
    {"PMAC_RX_FRAGMENTS_CNT"                , 0x00000034, 0x00000001, 0x00000001},
    {"PMAC_RX_IN_RANGE_LEN_ERR_CNT"         , 0x00000035, 0x00000001, 0x00000001},
    {"PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT"     , 0x00000036, 0x00000001, 0x00000001},
    {"PMAC_RX_OVERSIZE_CNT"                 , 0x00000037, 0x00000001, 0x00000001},
    {"PMAC_RX_JABBERS_CNT"                  , 0x00000038, 0x00000001, 0x00000001},
    {"PMAC_RX_SIZE64_CNT"                   , 0x00000039, 0x00000001, 0x00000001},
    {"PMAC_RX_SIZE65TO127_CNT"              , 0x0000003a, 0x00000001, 0x00000001},
    {"PMAC_RX_SIZE128TO255_CNT"             , 0x0000003b, 0x00000001, 0x00000001},
    {"PMAC_RX_SIZE256TO511_CNT"             , 0x0000003c, 0x00000001, 0x00000001},
    {"PMAC_RX_SIZE512TO1023_CNT"            , 0x0000003d, 0x00000001, 0x00000001},
    {"PMAC_RX_SIZE1024TO1518_CNT"           , 0x0000003e, 0x00000001, 0x00000001},
    {"PMAC_RX_SIZE1519TOMAX_CNT"            , 0x0000003f, 0x00000001, 0x00000001},
    {"PMAC_TX_PAUSE_CNT"                    , 0x00000040, 0x00000001, 0x00000001},
    {"PMAC_TX_OK_BYTES_CNT"                 , 0x00000041, 0x00000001, 0x00000001},
    {"PMAC_TX_UC_CNT"                       , 0x00000042, 0x00000001, 0x00000001},
    {"PMAC_TX_MC_CNT"                       , 0x00000043, 0x00000001, 0x00000001},
    {"PMAC_TX_BC_CNT"                       , 0x00000044, 0x00000001, 0x00000001},
    {"PMAC_TX_SIZE64_CNT"                   , 0x00000045, 0x00000001, 0x00000001},
    {"PMAC_TX_SIZE65TO127_CNT"              , 0x00000046, 0x00000001, 0x00000001},
    {"PMAC_TX_SIZE128TO255_CNT"             , 0x00000047, 0x00000001, 0x00000001},
    {"PMAC_TX_SIZE256TO511_CNT"             , 0x00000048, 0x00000001, 0x00000001},
    {"PMAC_TX_SIZE512TO1023_CNT"            , 0x00000049, 0x00000001, 0x00000001},
    {"PMAC_TX_SIZE1024TO1518_CNT"           , 0x0000004a, 0x00000001, 0x00000001},
    {"PMAC_TX_SIZE1519TOMAX_CNT"            , 0x0000004b, 0x00000001, 0x00000001},
    {"PMAC_RX_ALIGNMENT_LOST_CNT"           , 0x0000004c, 0x00000001, 0x00000001},
    {"MM_RX_ASSEMBLY_ERR_CNT"               , 0x0000004d, 0x00000001, 0x00000001},
    {"MM_RX_SMD_ERR_CNT"                    , 0x0000004e, 0x00000001, 0x00000001},
    {"MM_RX_ASSEMBLY_OK_CNT"                , 0x0000004f, 0x00000001, 0x00000001},
    {"MM_RX_MERGE_FRAG_CNT"                 , 0x00000050, 0x00000001, 0x00000001},
    {"MM_TX_PFRAGMENT_CNT"                  , 0x00000051, 0x00000001, 0x00000001},
    {"TX_MULTI_COLL_CNT"                    , 0x00000052, 0x00000001, 0x00000001},
    {"TX_LATE_COLL_CNT"                     , 0x00000053, 0x00000001, 0x00000001},
    {"TX_XCOLL_CNT"                         , 0x00000054, 0x00000001, 0x00000001},
    {"TX_DEFER_CNT"                         , 0x00000055, 0x00000001, 0x00000001},
    {"TX_XDEFER_CNT"                        , 0x00000056, 0x00000001, 0x00000001},
    {"TX_BACKOFF1_CNT"                      , 0x00000057, 0x00000001, 0x00000001},
    {"TX_CSENSE_CNT"                        , 0x00000058, 0x00000001, 0x00000001},
    {"RX_IN_BYTES_MSB_CNT"                  , 0x00000059, 0x00000001, 0x00000001},
    {"RX_OK_BYTES_MSB_CNT"                  , 0x0000005a, 0x00000001, 0x00000001},
    {"PMAC_RX_OK_BYTES_MSB_CNT"             , 0x0000005b, 0x00000001, 0x00000001},
    {"RX_BAD_BYTES_MSB_CNT"                 , 0x0000005c, 0x00000001, 0x00000001},
    {"PMAC_RX_BAD_BYTES_MSB_CNT"            , 0x0000005d, 0x00000001, 0x00000001},
    {"TX_OUT_BYTES_MSB_CNT"                 , 0x0000005e, 0x00000001, 0x00000001},
    {"TX_OK_BYTES_MSB_CNT"                  , 0x0000005f, 0x00000001, 0x00000001},
    {"PMAC_TX_OK_BYTES_MSB_CNT"             , 0x00000060, 0x00000001, 0x00000001},
    {"RX_SYNC_LOST_ERR_CNT"                 , 0x00000061, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ASM_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STAT_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
    {"MAC_ADDR_HIGH_CFG"                    , 0x00000001, 0x00000022, 0x00000001},
    {"MAC_ADDR_LOW_CFG"                     , 0x00000044, 0x00000022, 0x00000001},
    {"PORT_CFG"                             , 0x00000087, 0x00000022, 0x00000001},
    {"CPU_FC_CFG"                           , 0x000000ca, 0x00000001, 0x00000001},
    {"PAUSE_CFG"                            , 0x000000cb, 0x00000022, 0x00000001},
    {"INJ_VLAN_CFG"                         , 0x0000010e, 0x00000001, 0x00000001},
    {"TIME_TICK_CFG"                        , 0x0000010f, 0x00000001, 0x00000001},
    {"FIFO_FULL_WM_CFG"                     , 0x00000110, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ASM_DBG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DBG_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
    {"ERR_STICKY"                           , 0x00000001, 0x00000005, 0x00000001},
    {"PRE_CNT_OFLW_STICKY"                  , 0x0000000a, 0x00000001, 0x00000001},
    {"CELLBUF_STAT"                         , 0x0000000b, 0x00000005, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ASM_PORT_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PORT_STICKY"                          , 0x00000000, 0x00000022, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ASM_PFC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PFC_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
    {"PFC_TIMER"                            , 0x00000001, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ASM_PFC_TIMER_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PFC_TIMER_MAX"                        , 0x00000000, 0x00000007, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ASM_LBK_WM_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VD_FC_WM"                             , 0x00000000, 0x00000003, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ASM_LBK_MISC_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LBK_AGING_DIS"                        , 0x00000000, 0x00000003, 0x00000001},
    {"LBK_FIFO_CFG"                         , 0x00000005, 0x00000004, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ASM_LBK_STAT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LBK_OVFLW_STICKY"                     , 0x00000000, 0x00000003, 0x00000001},
    {"LBK_AGING_STICKY"                     , 0x00000005, 0x00000003, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ASM_RAM_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RAM_INIT"                             , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ASM_COREMEM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CM_ADDR"                              , 0x00000000, 0x00000001, 0x00000001},
    {"CM_DATA_WR"                           , 0x00000001, 0x00000001, 0x00000001},
    {"CM_DATA_RD"                           , 0x00000002, 0x00000001, 0x00000001},
    {"CM_OP"                                , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_ASM[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEV_STATISTICS"                       , 0x00000000, 0x00000020, 0x00000080, regs_within_ASM_DEV_STATISTICS},
    {"CFG"                                  , 0x00001200, 0x00000001, 0x00000111, regs_within_ASM_CFG},
#ifndef VTSS_RELEASE
    {"DBG"                                  , 0x00001311, 0x00000001, 0x00000014, regs_within_ASM_DBG},
#endif
    {"PORT_STATUS"                          , 0x00001325, 0x00000001, 0x00000022, regs_within_ASM_PORT_STATUS},
    {"PFC"                                  , 0x00001000, 0x00000020, 0x00000010, regs_within_ASM_PFC},
    {"PFC_TIMER_CFG"                        , 0x00001347, 0x00000001, 0x00000007, regs_within_ASM_PFC_TIMER_CFG},
    {"LBK_WM_CFG"                           , 0x0000134e, 0x00000001, 0x00000003, regs_within_ASM_LBK_WM_CFG},
    {"LBK_MISC_CFG"                         , 0x00001351, 0x00000001, 0x00000009, regs_within_ASM_LBK_MISC_CFG},
    {"LBK_STAT"                             , 0x0000135a, 0x00000001, 0x0000000a, regs_within_ASM_LBK_STAT},
    {"RAM_CTRL"                             , 0x00001364, 0x00000001, 0x00000001, regs_within_ASM_RAM_CTRL},
#ifndef VTSS_RELEASE
    {"COREMEM"                              , 0x00001365, 0x00000001, 0x00000004, regs_within_ASM_COREMEM},
#endif
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV1G_DEV_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DEV_RST_CTRL"                         , 0x00000000, 0x00000001, 0x00000001},
    {"DEV_STICKY"                           , 0x00000001, 0x00000001, 0x00000001},
    {"DEV_DBG_CFG"                          , 0x00000002, 0x00000001, 0x00000001},
    {"DEV_PORT_PROTECT"                     , 0x00000003, 0x00000001, 0x00000001},
    {"DEV_LB_CFG"                           , 0x00000004, 0x00000001, 0x00000001},
    {"EEE_CFG"                              , 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV1G_MAC_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MAC_ENA_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
    {"MAC_MODE_CFG"                         , 0x00000001, 0x00000001, 0x00000001},
    {"MAC_MAXLEN_CFG"                       , 0x00000002, 0x00000001, 0x00000001},
    {"MAC_TAGS_CFG"                         , 0x00000003, 0x00000001, 0x00000001},
    {"MAC_TAGS_CFG2"                        , 0x00000004, 0x00000001, 0x00000001},
    {"MAC_ADV_CHK_CFG"                      , 0x00000005, 0x00000001, 0x00000001},
    {"MAC_IFG_CFG"                          , 0x00000006, 0x00000001, 0x00000001},
    {"MAC_HDX_CFG"                          , 0x00000007, 0x00000001, 0x00000001},
    {"MAC_STICKY"                           , 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV1G_PCS1G_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS1G_CFG"                            , 0x00000000, 0x00000001, 0x00000001},
    {"PCS1G_MODE_CFG"                       , 0x00000001, 0x00000001, 0x00000001},
    {"PCS1G_SD_CFG"                         , 0x00000002, 0x00000001, 0x00000001},
    {"PCS1G_ANEG_CFG"                       , 0x00000003, 0x00000001, 0x00000001},
    {"PCS1G_ANEG_NP_CFG"                    , 0x00000004, 0x00000001, 0x00000001},
    {"PCS1G_LB_CFG"                         , 0x00000005, 0x00000001, 0x00000001},
    {"PCS1G_DBG_CFG"                        , 0x00000006, 0x00000001, 0x00000001},
    {"PCS1G_CDET_CFG"                       , 0x00000007, 0x00000001, 0x00000001},
    {"PCS1G_ANEG_STATUS"                    , 0x00000008, 0x00000001, 0x00000001},
    {"PCS1G_ANEG_NP_STATUS"                 , 0x00000009, 0x00000001, 0x00000001},
    {"PCS1G_LINK_STATUS"                    , 0x0000000a, 0x00000001, 0x00000001},
    {"PCS1G_LINK_DOWN_CNT"                  , 0x0000000b, 0x00000001, 0x00000001},
    {"PCS1G_STICKY"                         , 0x0000000c, 0x00000001, 0x00000001},
    {"PCS1G_DEBUG_STATUS"                   , 0x0000000d, 0x00000001, 0x00000001},
    {"PCS1G_LPI_CFG"                        , 0x0000000e, 0x00000001, 0x00000001},
    {"PCS1G_LPI_WAKE_ERROR_CNT"             , 0x0000000f, 0x00000001, 0x00000001},
    {"PCS1G_LPI_STATUS"                     , 0x00000010, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV1G_PCS1G_TSTPAT_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS1G_TSTPAT_MODE_CFG"                , 0x00000000, 0x00000001, 0x00000001},
    {"PCS1G_TSTPAT_STATUS"                  , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV1G_PCS_FX100_CONFIGURATION[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS_FX100_CFG"                        , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV1G_PCS_FX100_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS_FX100_STATUS"                     , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV1G_PTP_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PTP_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
    {"PTP_RXDLY_CFG"                        , 0x00000001, 0x00000001, 0x00000001},
    {"PTP_TXDLY_CFG"                        , 0x00000002, 0x00000001, 0x00000001},
    {"PTP_EVENTS"                           , 0x00000003, 0x00000001, 0x00000001},
    {"DEV_TX_CFG"                           , 0x00000004, 0x00000001, 0x00000001},
    {"DEV_PFRAME_CFG"                       , 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV1G_PHASE_DETECTOR_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PHAD_CTRL"                            , 0x00000000, 0x00000001, 0x00000001},
    {"PHAD_CYC_STAT"                        , 0x00000001, 0x00000001, 0x00000001},
    {"PHAD_ERR_STAT"                        , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV1G_MM_CONFIG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"ENABLE_CONFIG"                        , 0x00000000, 0x00000001, 0x00000001},
    {"VERIF_CONFIG"                         , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV1G_MM_STATISTICS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MM_STATUS"                            , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV1G_DEV2G5_INTR_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DEV2G5_INTR_CFG"                      , 0x00000000, 0x00000001, 0x00000001},
    {"DEV2G5_INTR"                          , 0x00000001, 0x00000001, 0x00000001},
    {"DEV2G5_INTR_IDENT"                    , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV1G[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEV_CFG_STATUS"                       , 0x00000000, 0x00000001, 0x00000006, regs_within_DEV1G_DEV_CFG_STATUS},
    {"MAC_CFG_STATUS"                       , 0x00000006, 0x00000001, 0x00000009, regs_within_DEV1G_MAC_CFG_STATUS},
    {"PCS1G_CFG_STATUS"                     , 0x0000000f, 0x00000001, 0x00000011, regs_within_DEV1G_PCS1G_CFG_STATUS},
    {"PCS1G_TSTPAT_CFG_STATUS"              , 0x00000020, 0x00000001, 0x00000002, regs_within_DEV1G_PCS1G_TSTPAT_CFG_STATUS},
    {"PCS_FX100_CONFIGURATION"              , 0x00000022, 0x00000001, 0x00000001, regs_within_DEV1G_PCS_FX100_CONFIGURATION},
    {"PCS_FX100_STATUS"                     , 0x00000023, 0x00000001, 0x00000001, regs_within_DEV1G_PCS_FX100_STATUS},
    {"PTP_CFG_STATUS"                       , 0x00000024, 0x00000001, 0x00000006, regs_within_DEV1G_PTP_CFG_STATUS},
    {"PHASE_DETECTOR_CTRL"                  , 0x0000002a, 0x00000002, 0x00000003, regs_within_DEV1G_PHASE_DETECTOR_CTRL},
    {"MM_CONFIG"                            , 0x00000030, 0x00000001, 0x00000002, regs_within_DEV1G_MM_CONFIG},
    {"MM_STATISTICS"                        , 0x00000032, 0x00000001, 0x00000001, regs_within_DEV1G_MM_STATISTICS},
    {"DEV2G5_INTR_CFG_STATUS"               , 0x00000033, 0x00000001, 0x00000003, regs_within_DEV1G_DEV2G5_INTR_CFG_STATUS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV10G_MAC_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MAC_ENA_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
    {"MAC_MODE_CFG"                         , 0x00000001, 0x00000001, 0x00000001},
    {"MAC_MAXLEN_CFG"                       , 0x00000002, 0x00000001, 0x00000001},
    {"MAC_NUM_TAGS_CFG"                     , 0x00000003, 0x00000001, 0x00000001},
    {"MAC_TAGS_CFG"                         , 0x00000004, 0x00000003, 0x00000001},
    {"MAC_ADV_CHK_CFG"                      , 0x00000007, 0x00000001, 0x00000001},
    {"MAC_LFS_CFG"                          , 0x00000008, 0x00000001, 0x00000001},
    {"MAC_LB_CFG"                           , 0x00000009, 0x00000001, 0x00000001},
    {"MAC_RX_LANE_STICKY_0"                 , 0x0000000a, 0x00000001, 0x00000001},
    {"MAC_RX_LANE_STICKY_1"                 , 0x0000000b, 0x00000001, 0x00000001},
    {"MAC_TX_MONITOR_STICKY"                , 0x0000000c, 0x00000001, 0x00000001},
    {"MAC_STICKY"                           , 0x0000000d, 0x00000001, 0x00000001},
    {"PMAC_STICKY"                          , 0x0000000e, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV10G_DEV_STATISTICS_32BIT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RX_SYMBOL_ERR_CNT"                    , 0x00000000, 0x00000001, 0x00000001},
    {"RX_PAUSE_CNT"                         , 0x00000001, 0x00000001, 0x00000001},
    {"RX_UNSUP_OPCODE_CNT"                  , 0x00000002, 0x00000001, 0x00000001},
    {"RX_UC_CNT"                            , 0x00000003, 0x00000001, 0x00000001},
    {"RX_MC_CNT"                            , 0x00000004, 0x00000001, 0x00000001},
    {"RX_BC_CNT"                            , 0x00000005, 0x00000001, 0x00000001},
    {"RX_CRC_ERR_CNT"                       , 0x00000006, 0x00000001, 0x00000001},
    {"RX_UNDERSIZE_CNT"                     , 0x00000007, 0x00000001, 0x00000001},
    {"RX_FRAGMENTS_CNT"                     , 0x00000008, 0x00000001, 0x00000001},
    {"RX_IN_RANGE_LEN_ERR_CNT"              , 0x00000009, 0x00000001, 0x00000001},
    {"RX_OUT_OF_RANGE_LEN_ERR_CNT"          , 0x0000000a, 0x00000001, 0x00000001},
    {"RX_OVERSIZE_CNT"                      , 0x0000000b, 0x00000001, 0x00000001},
    {"RX_JABBERS_CNT"                       , 0x0000000c, 0x00000001, 0x00000001},
    {"RX_SIZE64_CNT"                        , 0x0000000d, 0x00000001, 0x00000001},
    {"RX_SIZE65TO127_CNT"                   , 0x0000000e, 0x00000001, 0x00000001},
    {"RX_SIZE128TO255_CNT"                  , 0x0000000f, 0x00000001, 0x00000001},
    {"RX_SIZE256TO511_CNT"                  , 0x00000010, 0x00000001, 0x00000001},
    {"RX_SIZE512TO1023_CNT"                 , 0x00000011, 0x00000001, 0x00000001},
    {"RX_SIZE1024TO1518_CNT"                , 0x00000012, 0x00000001, 0x00000001},
    {"RX_SIZE1519TOMAX_CNT"                 , 0x00000013, 0x00000001, 0x00000001},
    {"RX_IPG_SHRINK_CNT"                    , 0x00000014, 0x00000001, 0x00000001},
    {"TX_PAUSE_CNT"                         , 0x00000015, 0x00000001, 0x00000001},
    {"TX_UC_CNT"                            , 0x00000016, 0x00000001, 0x00000001},
    {"TX_MC_CNT"                            , 0x00000017, 0x00000001, 0x00000001},
    {"TX_BC_CNT"                            , 0x00000018, 0x00000001, 0x00000001},
    {"TX_SIZE64_CNT"                        , 0x00000019, 0x00000001, 0x00000001},
    {"TX_SIZE65TO127_CNT"                   , 0x0000001a, 0x00000001, 0x00000001},
    {"TX_SIZE128TO255_CNT"                  , 0x0000001b, 0x00000001, 0x00000001},
    {"TX_SIZE256TO511_CNT"                  , 0x0000001c, 0x00000001, 0x00000001},
    {"TX_SIZE512TO1023_CNT"                 , 0x0000001d, 0x00000001, 0x00000001},
    {"TX_SIZE1024TO1518_CNT"                , 0x0000001e, 0x00000001, 0x00000001},
    {"TX_SIZE1519TOMAX_CNT"                 , 0x0000001f, 0x00000001, 0x00000001},
    {"RX_ALIGNMENT_LOST_CNT"                , 0x00000020, 0x00000001, 0x00000001},
    {"RX_TAGGED_FRMS_CNT"                   , 0x00000021, 0x00000001, 0x00000001},
    {"RX_UNTAGGED_FRMS_CNT"                 , 0x00000022, 0x00000001, 0x00000001},
    {"TX_TAGGED_FRMS_CNT"                   , 0x00000023, 0x00000001, 0x00000001},
    {"TX_UNTAGGED_FRMS_CNT"                 , 0x00000024, 0x00000001, 0x00000001},
    {"PMAC_RX_SYMBOL_ERR_CNT"               , 0x00000025, 0x00000001, 0x00000001},
    {"PMAC_RX_PAUSE_CNT"                    , 0x00000026, 0x00000001, 0x00000001},
    {"PMAC_RX_UNSUP_OPCODE_CNT"             , 0x00000027, 0x00000001, 0x00000001},
    {"PMAC_RX_UC_CNT"                       , 0x00000028, 0x00000001, 0x00000001},
    {"PMAC_RX_MC_CNT"                       , 0x00000029, 0x00000001, 0x00000001},
    {"PMAC_RX_BC_CNT"                       , 0x0000002a, 0x00000001, 0x00000001},
    {"PMAC_RX_CRC_ERR_CNT"                  , 0x0000002b, 0x00000001, 0x00000001},
    {"PMAC_RX_UNDERSIZE_CNT"                , 0x0000002c, 0x00000001, 0x00000001},
    {"PMAC_RX_FRAGMENTS_CNT"                , 0x0000002d, 0x00000001, 0x00000001},
    {"PMAC_RX_IN_RANGE_LEN_ERR_CNT"         , 0x0000002e, 0x00000001, 0x00000001},
    {"PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT"     , 0x0000002f, 0x00000001, 0x00000001},
    {"PMAC_RX_OVERSIZE_CNT"                 , 0x00000030, 0x00000001, 0x00000001},
    {"PMAC_RX_JABBERS_CNT"                  , 0x00000031, 0x00000001, 0x00000001},
    {"PMAC_RX_SIZE64_CNT"                   , 0x00000032, 0x00000001, 0x00000001},
    {"PMAC_RX_SIZE65TO127_CNT"              , 0x00000033, 0x00000001, 0x00000001},
    {"PMAC_RX_SIZE128TO255_CNT"             , 0x00000034, 0x00000001, 0x00000001},
    {"PMAC_RX_SIZE256TO511_CNT"             , 0x00000035, 0x00000001, 0x00000001},
    {"PMAC_RX_SIZE512TO1023_CNT"            , 0x00000036, 0x00000001, 0x00000001},
    {"PMAC_RX_SIZE1024TO1518_CNT"           , 0x00000037, 0x00000001, 0x00000001},
    {"PMAC_RX_SIZE1519TOMAX_CNT"            , 0x00000038, 0x00000001, 0x00000001},
    {"PMAC_TX_PAUSE_CNT"                    , 0x00000039, 0x00000001, 0x00000001},
    {"PMAC_TX_UC_CNT"                       , 0x0000003a, 0x00000001, 0x00000001},
    {"PMAC_TX_MC_CNT"                       , 0x0000003b, 0x00000001, 0x00000001},
    {"PMAC_TX_BC_CNT"                       , 0x0000003c, 0x00000001, 0x00000001},
    {"PMAC_TX_SIZE64_CNT"                   , 0x0000003d, 0x00000001, 0x00000001},
    {"PMAC_TX_SIZE65TO127_CNT"              , 0x0000003e, 0x00000001, 0x00000001},
    {"PMAC_TX_SIZE128TO255_CNT"             , 0x0000003f, 0x00000001, 0x00000001},
    {"PMAC_TX_SIZE256TO511_CNT"             , 0x00000040, 0x00000001, 0x00000001},
    {"PMAC_TX_SIZE512TO1023_CNT"            , 0x00000041, 0x00000001, 0x00000001},
    {"PMAC_TX_SIZE1024TO1518_CNT"           , 0x00000042, 0x00000001, 0x00000001},
    {"PMAC_TX_SIZE1519TOMAX_CNT"            , 0x00000043, 0x00000001, 0x00000001},
    {"PMAC_RX_ALIGNMENT_LOST_CNT"           , 0x00000044, 0x00000001, 0x00000001},
    {"MM_RX_ASSEMBLY_ERR_CNT"               , 0x00000045, 0x00000001, 0x00000001},
    {"MM_RX_SMD_ERR_CNT"                    , 0x00000046, 0x00000001, 0x00000001},
    {"MM_RX_ASSEMBLY_OK_CNT"                , 0x00000047, 0x00000001, 0x00000001},
    {"MM_RX_MERGE_FRAG_CNT"                 , 0x00000048, 0x00000001, 0x00000001},
    {"MM_TX_PFRAGMENT_CNT"                  , 0x00000049, 0x00000001, 0x00000001},
    {"RX_HIH_CKSM_ERR_CNT"                  , 0x0000004a, 0x00000001, 0x00000001},
    {"RX_XGMII_PROT_ERR_CNT"                , 0x0000004b, 0x00000001, 0x00000001},
    {"PMAC_RX_HIH_CKSM_ERR_CNT"             , 0x0000004c, 0x00000001, 0x00000001},
    {"PMAC_RX_XGMII_PROT_ERR_CNT"           , 0x0000004d, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV10G_DEV_STATISTICS_40BIT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RX_IN_BYTES_CNT"                      , 0x00000000, 0x00000001, 0x00000001},
    {"RX_IN_BYTES_MSB_CNT"                  , 0x00000001, 0x00000001, 0x00000001},
    {"RX_OK_BYTES_CNT"                      , 0x00000002, 0x00000001, 0x00000001},
    {"RX_OK_BYTES_MSB_CNT"                  , 0x00000003, 0x00000001, 0x00000001},
    {"RX_BAD_BYTES_CNT"                     , 0x00000004, 0x00000001, 0x00000001},
    {"RX_BAD_BYTES_MSB_CNT"                 , 0x00000005, 0x00000001, 0x00000001},
    {"TX_OUT_BYTES_CNT"                     , 0x00000006, 0x00000001, 0x00000001},
    {"TX_OUT_BYTES_MSB_CNT"                 , 0x00000007, 0x00000001, 0x00000001},
    {"TX_OK_BYTES_CNT"                      , 0x00000008, 0x00000001, 0x00000001},
    {"TX_OK_BYTES_MSB_CNT"                  , 0x00000009, 0x00000001, 0x00000001},
    {"PMAC_RX_OK_BYTES_CNT"                 , 0x0000000a, 0x00000001, 0x00000001},
    {"PMAC_RX_OK_BYTES_MSB_CNT"             , 0x0000000b, 0x00000001, 0x00000001},
    {"PMAC_RX_BAD_BYTES_CNT"                , 0x0000000c, 0x00000001, 0x00000001},
    {"PMAC_RX_BAD_BYTES_MSB_CNT"            , 0x0000000d, 0x00000001, 0x00000001},
    {"PMAC_TX_OK_BYTES_CNT"                 , 0x0000000e, 0x00000001, 0x00000001},
    {"PMAC_TX_OK_BYTES_MSB_CNT"             , 0x0000000f, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV10G_DEV_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DEV_RST_CTRL"                         , 0x00000000, 0x00000001, 0x00000001},
    {"DEV_PORT_PROTECT"                     , 0x00000001, 0x00000001, 0x00000001},
    {"DEV_LB_CFG"                           , 0x00000002, 0x00000001, 0x00000001},
    {"USXGMII_TX_RADAPT_CFG"                , 0x00000003, 0x00000001, 0x00000001},
    {"DEV_MISC_CFG"                         , 0x00000004, 0x00000001, 0x00000001},
    {"PTP_STAMPER_CFG"                      , 0x00000005, 0x00000001, 0x00000001},
    {"DEV_STICKY"                           , 0x00000006, 0x00000001, 0x00000001},
    {"INTR"                                 , 0x00000007, 0x00000001, 0x00000001},
    {"INTR_ENA"                             , 0x00000008, 0x00000001, 0x00000001},
    {"INTR_IDENT"                           , 0x00000009, 0x00000001, 0x00000001},
    {"DEV_RX_STATUS"                        , 0x0000000a, 0x00000001, 0x00000001},
    {"EEE_CFG"                              , 0x0000000b, 0x00000001, 0x00000001},
    {"PFC_PAUSE_MODE_CTRL"                  , 0x0000000c, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV10G_PCS25G_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS25G_CFG"                           , 0x00000000, 0x00000001, 0x00000001},
    {"PCS25G_SD_CFG"                        , 0x00000001, 0x00000001, 0x00000001},
    {"PCS25G_STATUS"                        , 0x00000002, 0x00000001, 0x00000001},
    {"PCS25G_FEC74_CFG"                     , 0x00000003, 0x00000001, 0x00000001},
    {"PCS25G_FEC74_STATUS"                  , 0x00000004, 0x00000001, 0x00000001},
    {"PCS25G_FEC74_CERR_CNT"                , 0x00000005, 0x00000001, 0x00000001},
    {"PCS25G_FEC74_NCERR_CNT"               , 0x00000006, 0x00000001, 0x00000001},
    {"PCS25G_RSFEC_CFG"                     , 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV10G_MM_CONFIG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"ENABLE_CONFIG"                        , 0x00000000, 0x00000001, 0x00000001},
    {"VERIF_CONFIG"                         , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV10G_MM_STATISTICS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MM_STATUS"                            , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV10G_USXGMII_ANEG_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"USXGMII_ANEG_CFG"                     , 0x00000000, 0x00000001, 0x00000001},
    {"USXGMII_ANEG_STATUS"                  , 0x00000001, 0x00000001, 0x00000001},
    {"USXGMII_PCS_SD_CFG"                   , 0x00000002, 0x00000001, 0x00000001},
    {"USXGMII_PCS_STATUS"                   , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV10G_PTP_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PTP_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
    {"PTP_RXDLY_CFG"                        , 0x00000001, 0x00000001, 0x00000001},
    {"PTP_TXDLY_CFG"                        , 0x00000002, 0x00000001, 0x00000001},
    {"PTP_EVENTS"                           , 0x00000003, 0x00000001, 0x00000001},
    {"DEV_TX_CFG"                           , 0x00000004, 0x00000001, 0x00000001},
    {"DEV_PFRAME_CFG"                       , 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV10G_PHASE_DETECTOR_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PHAD_CTRL"                            , 0x00000000, 0x00000001, 0x00000001},
    {"PHAD_CYC_STAT"                        , 0x00000001, 0x00000001, 0x00000001},
    {"PHAD_ERR_STAT"                        , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV10G[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"MAC_CFG_STATUS"                       , 0x00000000, 0x00000001, 0x0000000f, regs_within_DEV10G_MAC_CFG_STATUS},
    {"DEV_STATISTICS_32BIT"                 , 0x0000000f, 0x00000001, 0x0000004e, regs_within_DEV10G_DEV_STATISTICS_32BIT},
    {"DEV_STATISTICS_40BIT"                 , 0x0000005d, 0x00000001, 0x00000010, regs_within_DEV10G_DEV_STATISTICS_40BIT},
    {"DEV_CFG_STATUS"                       , 0x0000006d, 0x00000001, 0x0000000d, regs_within_DEV10G_DEV_CFG_STATUS},
    {"PCS25G_CFG_STATUS"                    , 0x0000007a, 0x00000001, 0x00000008, regs_within_DEV10G_PCS25G_CFG_STATUS},
    {"MM_CONFIG"                            , 0x00000082, 0x00000001, 0x00000002, regs_within_DEV10G_MM_CONFIG},
    {"MM_STATISTICS"                        , 0x00000084, 0x00000001, 0x00000001, regs_within_DEV10G_MM_STATISTICS},
    {"USXGMII_ANEG_CFG_STATUS"              , 0x00000085, 0x00000001, 0x00000004, regs_within_DEV10G_USXGMII_ANEG_CFG_STATUS},
    {"PTP_CFG_STATUS"                       , 0x00000089, 0x00000001, 0x00000006, regs_within_DEV10G_PTP_CFG_STATUS},
    {"PHASE_DETECTOR_CTRL"                  , 0x0000008f, 0x00000002, 0x00000003, regs_within_DEV10G_PHASE_DETECTOR_CTRL},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_PCS_10GBASE_R_PCS_10GBR_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
    {"PCS_SD_CFG"                           , 0x00000001, 0x00000001, 0x00000001},
    {"TX_SEEDA_MSB"                         , 0x00000002, 0x00000001, 0x00000001},
    {"TX_SEEDA_LSB"                         , 0x00000003, 0x00000001, 0x00000001},
    {"TX_SEEDB_MSB"                         , 0x00000004, 0x00000001, 0x00000001},
    {"TX_SEEDB_LSB"                         , 0x00000005, 0x00000001, 0x00000001},
    {"RX_PRBS31_INIT"                       , 0x00000006, 0x00000001, 0x00000001},
    {"TX_DATAPAT_MSB"                       , 0x00000007, 0x00000001, 0x00000001},
    {"TX_DATAPAT_LSB"                       , 0x00000008, 0x00000001, 0x00000001},
    {"RX_DATAPAT_MSB"                       , 0x00000009, 0x00000001, 0x00000001},
    {"RX_DATAPAT_LSB"                       , 0x0000000a, 0x00000001, 0x00000001},
    {"TEST_CFG"                             , 0x0000000b, 0x00000001, 0x00000001},
    {"PCS_INTR_MASK"                        , 0x0000000c, 0x00000001, 0x00000001},
    {"TIMER_125"                            , 0x0000000d, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PCS_10GBASE_R_PCS_10GBR_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PCS_INTR_STAT"                        , 0x00000000, 0x00000001, 0x00000001},
    {"PCS_STATUS"                           , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PCS_10GBASE_R_PCS_10GBR_HA_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TEST_ERR_CNT"                         , 0x00000000, 0x00000001, 0x00000001},
    {"TX_ERRBLK_CNT"                        , 0x00000001, 0x00000001, 0x00000001},
    {"TX_CHARERR_CNT"                       , 0x00000002, 0x00000001, 0x00000001},
    {"RX_BER_CNT"                           , 0x00000003, 0x00000001, 0x00000001},
    {"RX_ERRBLK_CNT"                        , 0x00000004, 0x00000001, 0x00000001},
    {"RX_CHARERR_CNT"                       , 0x00000005, 0x00000001, 0x00000001},
    {"RX_OSET_FIFO_STAT"                    , 0x00000006, 0x00000001, 0x00000001},
    {"RX_OSET_FIFO_DATA"                    , 0x00000007, 0x00000001, 0x00000001},
    {"RX_FSET_FIFO_STAT"                    , 0x00000008, 0x00000001, 0x00000001},
    {"RX_FSET_FIFO_DATA"                    , 0x00000009, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PCS_10GBASE_R_KR_FEC_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"KR_FEC_CFG"                           , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PCS_10GBASE_R_KR_FEC_THRESHOLD_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FIXED_ERROR_COUNT_THRESHOLD"          , 0x00000000, 0x00000001, 0x00000001},
    {"UNFIXABLE_ERROR_COUNT_THRESHOLD"      , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PCS_10GBASE_R_KR_FEC_HA_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"KR_FEC_CORRECTED"                     , 0x00000000, 0x00000001, 0x00000001},
    {"KR_FEC_UNCORRECTED"                   , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PCS_10GBASE_R_KR_FEC_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"KR_FEC_STICKY"                        , 0x00000000, 0x00000001, 0x00000001},
    {"KR_FEC_STICKY_MASK"                   , 0x00000001, 0x00000001, 0x00000001},
    {"KR_FEC_STATUS"                        , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PCS_10GBASE_R_KR_FEC_CAPABILITY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"KR_FEC_CAPABILITY"                    , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PCS_10GBASE_R_EEE_TIMER_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"ONE_US_TIMER_REG"                     , 0x00000000, 0x00000001, 0x00000001},
    {"TX_TS_TIMER_REG"                      , 0x00000001, 0x00000001, 0x00000001},
    {"TX_TQ_TIMER_REG"                      , 0x00000002, 0x00000001, 0x00000001},
    {"TX_TW_TIMER_REG"                      , 0x00000003, 0x00000001, 0x00000001},
    {"RX_TQ_TIMER_REG"                      , 0x00000004, 0x00000001, 0x00000001},
    {"RX_TW_TIMER_REG"                      , 0x00000005, 0x00000001, 0x00000001},
    {"RX_WF_TIMER_REG"                      , 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PCS_10GBASE_R_EEE_STATS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"WAKE_ERR_CNT"                         , 0x00000000, 0x00000001, 0x00000001},
    {"EEE_STATUS"                           , 0x00000001, 0x00000001, 0x00000001},
    {"EEE_INTR_MASK"                        , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_PCS_10GBASE_R[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"PCS_10GBR_CFG"                        , 0x00000000, 0x00000001, 0x0000000e, regs_within_PCS_10GBASE_R_PCS_10GBR_CFG},
    {"PCS_10GBR_STATUS"                     , 0x0000000e, 0x00000001, 0x00000002, regs_within_PCS_10GBASE_R_PCS_10GBR_STATUS},
    {"PCS_10GBR_HA_STATUS"                  , 0x00000010, 0x00000001, 0x0000000a, regs_within_PCS_10GBASE_R_PCS_10GBR_HA_STATUS},
    {"KR_FEC_CFG"                           , 0x0000001a, 0x00000001, 0x00000001, regs_within_PCS_10GBASE_R_KR_FEC_CFG},
    {"KR_FEC_THRESHOLD_CFG"                 , 0x0000001b, 0x00000001, 0x00000002, regs_within_PCS_10GBASE_R_KR_FEC_THRESHOLD_CFG},
    {"KR_FEC_HA_STATUS"                     , 0x0000001d, 0x00000001, 0x00000002, regs_within_PCS_10GBASE_R_KR_FEC_HA_STATUS},
    {"KR_FEC_STATUS"                        , 0x0000001f, 0x00000001, 0x00000003, regs_within_PCS_10GBASE_R_KR_FEC_STATUS},
    {"KR_FEC_CAPABILITY"                    , 0x00000022, 0x00000001, 0x00000001, regs_within_PCS_10GBASE_R_KR_FEC_CAPABILITY},
    {"EEE_TIMER_CFG"                        , 0x00000023, 0x00000001, 0x00000007, regs_within_PCS_10GBASE_R_EEE_TIMER_CFG},
    {"EEE_STATS"                            , 0x0000002a, 0x00000001, 0x00000003, regs_within_PCS_10GBASE_R_EEE_STATS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_CHIP_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GPR"                                  , 0x00000002, 0x00000001, 0x00000001},
    {"BUILDID"                              , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_SI_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_CTRL"                              , 0x00000000, 0x00000001, 0x00000001},
    {"IF_CFGSTAT"                           , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_MEMITGR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MEMITGR_CTRL"                         , 0x00000000, 0x00000001, 0x00000001},
    {"MEMITGR_STAT"                         , 0x00000001, 0x00000001, 0x00000001},
    {"MEMITGR_INFO"                         , 0x00000002, 0x00000001, 0x00000001},
    {"MEMITGR_IDX"                          , 0x00000003, 0x00000001, 0x00000001},
    {"MEMITGR_DIV"                          , 0x00000004, 0x00000001, 0x00000001},
    {"MEMITGR_DBG"                          , 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEVCPU_GCB[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"CHIP_REGS"                            , 0x00000000, 0x00000001, 0x00000003, regs_within_DEVCPU_GCB_CHIP_REGS},
    {"SI_REGS"                              , 0x00000003, 0x00000001, 0x00000002, regs_within_DEVCPU_GCB_SI_REGS},
    {"MEMITGR"                              , 0x00000005, 0x00000001, 0x00000006, regs_within_DEVCPU_GCB_MEMITGR},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_PTP_PTP_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PTP_PIN_INTR"                         , 0x00000000, 0x00000001, 0x00000001},
    {"PTP_PIN_INTR_ENA"                     , 0x00000001, 0x00000001, 0x00000001},
    {"PTP_INTR_IDENT"                       , 0x00000002, 0x00000001, 0x00000001},
    {"PTP_DOM_CFG"                          , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PTP_TOD_DOMAINS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CLK_PER_CFG"                          , 0x00000000, 0x00000002, 0x00000001},
    {"PTP_CUR_NSEC"                         , 0x00000002, 0x00000001, 0x00000001},
    {"PTP_CUR_NSEC_FRAC"                    , 0x00000003, 0x00000001, 0x00000001},
    {"PTP_CUR_SEC_LSB"                      , 0x00000004, 0x00000001, 0x00000001},
    {"PTP_CUR_SEC_MSB"                      , 0x00000005, 0x00000001, 0x00000001},
    {"NTP_CUR_NSEC"                         , 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PTP_PINS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PTP_PIN_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
    {"PTP_TOD_SEC_MSB"                      , 0x00000001, 0x00000001, 0x00000001},
    {"PTP_TOD_SEC_LSB"                      , 0x00000002, 0x00000001, 0x00000001},
    {"PTP_TOD_NSEC"                         , 0x00000003, 0x00000001, 0x00000001},
    {"PTP_TOD_NSEC_FRAC"                    , 0x00000004, 0x00000001, 0x00000001},
    {"NTP_NSEC"                             , 0x00000005, 0x00000001, 0x00000001},
    {"PIN_WF_HIGH_PERIOD"                   , 0x00000006, 0x00000001, 0x00000001},
    {"PIN_WF_LOW_PERIOD"                    , 0x00000007, 0x00000001, 0x00000001},
    {"PIN_IOBOUNCH_DELAY"                   , 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PTP_TS_FIFO[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PTP_TWOSTEP_CTRL"                     , 0x00000000, 0x00000001, 0x00000001},
    {"PTP_TWOSTEP_STAMP_NSEC"               , 0x00000001, 0x00000001, 0x00000001},
    {"PTP_TWOSTEP_STAMP_SUBNS"              , 0x00000002, 0x00000001, 0x00000001},
    {"PTP_WRP"                              , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PTP_PHASE_DETECTOR_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PHAD_CTRL"                            , 0x00000000, 0x00000001, 0x00000001},
    {"PHAD_CYC_STAT"                        , 0x00000001, 0x00000001, 0x00000001},
    {"PHAD_ERR_STAT"                        , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_PTP[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"PTP_CFG"                              , 0x00000080, 0x00000001, 0x00000004, regs_within_PTP_PTP_CFG},
    {"PTP_TOD_DOMAINS"                      , 0x00000084, 0x00000003, 0x00000007, regs_within_PTP_PTP_TOD_DOMAINS},
    {"PTP_PINS"                             , 0x00000000, 0x00000008, 0x00000010, regs_within_PTP_PTP_PINS},
    {"PTP_TS_FIFO"                          , 0x00000099, 0x00000001, 0x00000004, regs_within_PTP_PTP_TS_FIFO},
    {"PHASE_DETECTOR_CTRL"                  , 0x0000009d, 0x00000008, 0x00000003, regs_within_PTP_PHASE_DETECTOR_CTRL},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DSM_RAM_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RAM_INIT"                             , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DSM_COREMEM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CM_ADDR"                              , 0x00000000, 0x00000001, 0x00000001},
    {"CM_DATA_WR"                           , 0x00000001, 0x00000001, 0x00000001},
    {"CM_DATA_RD"                           , 0x00000002, 0x00000001, 0x00000001},
    {"CM_OP"                                , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DSM_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"BUF_CFG"                              , 0x00000000, 0x00000022, 0x00000001},
    {"RATE_CTRL"                            , 0x00000043, 0x00000022, 0x00000001},
    {"IPG_SHRINK_CFG"                       , 0x00000086, 0x00000022, 0x00000001},
    {"CLR_BUF"                              , 0x000000c9, 0x00000003, 0x00000001},
    {"SCH_STOP_WM_CFG"                      , 0x000000ce, 0x00000022, 0x00000001},
    {"TX_START_WM_CFG"                      , 0x00000111, 0x00000022, 0x00000001},
    {"DEV_TX_STOP_WM_CFG"                   , 0x00000154, 0x00000022, 0x00000001},
    {"RX_PAUSE_CFG"                         , 0x00000197, 0x00000022, 0x00000001},
    {"ETH_FC_CFG"                           , 0x000001da, 0x00000022, 0x00000001},
    {"ETH_PFC_CFG"                          , 0x0000021d, 0x00000022, 0x00000001},
    {"MAC_CFG"                              , 0x00000260, 0x00000022, 0x00000001},
    {"MAC_ADDR_BASE_HIGH_CFG"               , 0x000002a3, 0x00000020, 0x00000001},
    {"MAC_ADDR_BASE_LOW_CFG"                , 0x000002e4, 0x00000020, 0x00000001},
    {"DBG_CTRL"                             , 0x00000325, 0x00000001, 0x00000001},
    {"TAXI_CAL_CFG"                         , 0x00000326, 0x00000005, 0x00000001},
    {"PREEMPT_CFG"                          , 0x0000032f, 0x00000022, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DSM_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AGED_FRMS"                            , 0x00000000, 0x00000045, 0x00000001},
    {"CELL_BUS_STICKY"                      , 0x00000087, 0x00000001, 0x00000001},
    {"BUF_OFLW_STICKY"                      , 0x00000088, 0x00000003, 0x00000001},
    {"BUF_UFLW_STICKY"                      , 0x0000008d, 0x00000003, 0x00000001},
    {"PRE_CNT_OFLW_STICKY"                  , 0x00000092, 0x00000001, 0x00000001},
    {"BUF_MAX_FILL"                         , 0x00000093, 0x00000045, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DSM_RATE_LIMIT_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TX_RATE_LIMIT_MODE"                   , 0x00000000, 0x00000022, 0x00000001},
    {"TX_IPG_STRETCH_RATIO_CFG"             , 0x00000043, 0x00000022, 0x00000001},
    {"TX_FRAME_RATE_START_CFG"              , 0x00000086, 0x00000022, 0x00000001},
    {"TX_RATE_LIMIT_HDR_CFG"                , 0x000000c9, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DSM_RATE_LIMIT_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TX_RATE_LIMIT_STICKY"                 , 0x00000000, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DSM[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"RAM_CTRL"                             , 0x00000000, 0x00000001, 0x00000001, regs_within_DSM_RAM_CTRL},
#ifndef VTSS_RELEASE
    {"COREMEM"                              , 0x00000001, 0x00000001, 0x00000004, regs_within_DSM_COREMEM},
#endif
    {"CFG"                                  , 0x00000005, 0x00000001, 0x00000372, regs_within_DSM_CFG},
    {"STATUS"                               , 0x00000377, 0x00000001, 0x0000011a, regs_within_DSM_STATUS},
    {"RATE_LIMIT_CFG"                       , 0x00000491, 0x00000001, 0x000000ca, regs_within_DSM_RATE_LIMIT_CFG},
    {"RATE_LIMIT_STATUS"                    , 0x0000055b, 0x00000001, 0x00000003, regs_within_DSM_RATE_LIMIT_STATUS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_EACL_COMMON[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"OPTIONS"                              , 0x00000000, 0x00000001, 0x00000001},
    {"TPID_CFG"                             , 0x00000001, 0x00000003, 0x00000001},
    {"ETAG_CFG"                             , 0x00000004, 0x00000001, 0x00000001},
    {"RTAG_CFG"                             , 0x00000005, 0x00000001, 0x00000001},
    {"ES2_CTRL"                             , 0x00000006, 0x00000001, 0x00000001},
    {"DP_MAP"                               , 0x00000007, 0x00000001, 0x00000001},
    {"GCPU_CFG"                             , 0x00000008, 0x00000008, 0x00000001},
    {"RLEG_CFG_0"                           , 0x00000010, 0x00000001, 0x00000001},
    {"RLEG_CFG_1"                           , 0x00000011, 0x00000001, 0x00000001},
    {"VCAP_ES2_FRAGMENT_CFG"                , 0x00000012, 0x00000001, 0x00000001},
    {"VCAP_ES2_RNG_CTRL"                    , 0x00000013, 0x00000010, 0x00000001},
    {"VCAP_ES2_RNG_VALUE_CFG"               , 0x00000023, 0x00000010, 0x00000001},
    {"INTR"                                 , 0x00000033, 0x00000001, 0x00000001},
    {"INTR_ENA"                             , 0x00000034, 0x00000001, 0x00000001},
    {"INTR_IDENT"                           , 0x00000035, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_EACL_INTERFACE_MAP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_MAP_TBL"                           , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_EACL_ES2_KEY_SELECT_PROFILE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_ES2_KEY_SEL"                     , 0x00000000, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_EACL_CNT_TBL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"ES2_CNT"                              , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_EACL_POL_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"POL_EACL_RATE_CFG"                    , 0x00000000, 0x00000020, 0x00000001},
    {"POL_EACL_THRES_CFG"                   , 0x00000040, 0x00000020, 0x00000001},
    {"POL_EACL_CTRL"                        , 0x00000080, 0x00000020, 0x00000001},
    {"POL_EACL_CFG"                         , 0x000000c0, 0x00000001, 0x00000001},
    {"POL_UPD_INT_CFG"                      , 0x000000c1, 0x00000001, 0x00000001},
    {"POL_EACL_STICKY"                      , 0x000000c2, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_EACL_ES2_STICKY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SEC_LOOKUP_STICKY"                    , 0x00000000, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_EACL_DBG_STICKY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DBG_STICKY"                           , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_EACL_FRER_MAP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FRER_FIRST_MEMBER"                    , 0x00000000, 0x00000001, 0x00000001},
    {"FRER_EGR_PORT"                        , 0x00000001, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_EACL_FRER_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FRER_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_EACL_FRER_CFG_COMPOUND[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FRER_CFG_COMPOUND"                    , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_EACL_FRER_CFG_MEMBER[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FRER_CFG_MEMBER"                      , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_EACL_FRER_STA_COMPOUND[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FRER_STA_COMPOUND"                    , 0x00000000, 0x00000001, 0x00000001},
    {"FRER_HST_COMPOUND"                    , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_EACL_FRER_STA_MEMBER[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FRER_STA_MEMBER"                      , 0x00000000, 0x00000001, 0x00000001},
    {"FRER_HST_MEMBER"                      , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_EACL_FRER_CNT_COMPOUND[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CNT_COMPOUND_RESETS"                  , 0x00000000, 0x00000001, 0x00000001},
    {"CNT_COMPOUND_TAGLESS"                 , 0x00000001, 0x00000001, 0x00000001},
    {"CNT_COMPOUND_PASSED"                  , 0x00000002, 0x00000001, 0x00000001},
    {"CNT_COMPOUND_DISCARDED"               , 0x00000003, 0x00000001, 0x00000001},
    {"CNT_COMPOUND_OUTOFORDER"              , 0x00000004, 0x00000001, 0x00000001},
    {"CNT_COMPOUND_ROGUE"                   , 0x00000005, 0x00000001, 0x00000001},
    {"CNT_COMPOUND_LOST"                    , 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_EACL_FRER_CNT_MEMBER[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CNT_MEMBER_RESETS"                    , 0x00000000, 0x00000001, 0x00000001},
    {"CNT_MEMBER_TAGLESS"                   , 0x00000001, 0x00000001, 0x00000001},
    {"CNT_MEMBER_PASSED"                    , 0x00000002, 0x00000001, 0x00000001},
    {"CNT_MEMBER_DISCARDED"                 , 0x00000003, 0x00000001, 0x00000001},
    {"CNT_MEMBER_OUTOFORDER"                , 0x00000004, 0x00000001, 0x00000001},
    {"CNT_MEMBER_ROGUE"                     , 0x00000005, 0x00000001, 0x00000001},
    {"CNT_MEMBER_LOST"                      , 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_EACL_STAT_GLOBAL_CFG_EACL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GLOBAL_CNT_FRM_TYPE_CFG"              , 0x00000000, 0x00000002, 0x00000001},
    {"STAT_GLOBAL_CFG"                      , 0x00000002, 0x00000002, 0x00000001},
    {"STAT_GLOBAL_EVENT_MASK"               , 0x00000004, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_EACL_STAT_CNT_CFG_EACL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STAT_LSB_CNT"                         , 0x00000000, 0x00000002, 0x00000001},
    {"STAT_MSB_CNT"                         , 0x00000002, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_EACL_RAM_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RAM_INIT"                             , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_EACL_COREMEM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CM_ADDR"                              , 0x00000000, 0x00000001, 0x00000001},
    {"CM_DATA_WR"                           , 0x00000001, 0x00000001, 0x00000001},
    {"CM_DATA_RD"                           , 0x00000002, 0x00000001, 0x00000001},
    {"CM_OP"                                , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_EACL[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"COMMON"                               , 0x00003590, 0x00000001, 0x00000036, regs_within_EACL_COMMON},
    {"INTERFACE_MAP"                        , 0x00002800, 0x000005c8, 0x00000001, regs_within_EACL_INTERFACE_MAP},
    {"ES2_KEY_SELECT_PROFILE"               , 0x00003500, 0x00000048, 0x00000002, regs_within_EACL_ES2_KEY_SELECT_PROFILE},
    {"CNT_TBL"                              , 0x00002e00, 0x00000200, 0x00000001, regs_within_EACL_CNT_TBL},
    {"POL_CFG"                              , 0x00003700, 0x00000001, 0x000000c3, regs_within_EACL_POL_CFG},
    {"ES2_STICKY"                           , 0x00002dcc, 0x00000001, 0x00000002, regs_within_EACL_ES2_STICKY},
#ifndef VTSS_RELEASE
    {"DBG_STICKY"                           , 0x00002dce, 0x00000001, 0x00000001, regs_within_EACL_DBG_STICKY},
#endif
    {"FRER_MAP"                             , 0x00000000, 0x00000800, 0x00000004, regs_within_EACL_FRER_MAP},
    {"FRER_CFG"                             , 0x00002dcf, 0x00000001, 0x00000001, regs_within_EACL_FRER_CFG},
    {"FRER_CFG_COMPOUND"                    , 0x00003600, 0x00000080, 0x00000001, regs_within_EACL_FRER_CFG_COMPOUND},
    {"FRER_CFG_MEMBER"                      , 0x00003400, 0x00000100, 0x00000001, regs_within_EACL_FRER_CFG_MEMBER},
#ifndef VTSS_RELEASE
    {"FRER_STA_COMPOUND"                    , 0x00002dc8, 0x00000001, 0x00000002, regs_within_EACL_FRER_STA_COMPOUND},
#endif
#ifndef VTSS_RELEASE
    {"FRER_STA_MEMBER"                      , 0x00002dca, 0x00000001, 0x00000002, regs_within_EACL_FRER_STA_MEMBER},
#endif
    {"FRER_CNT_COMPOUND"                    , 0x00003000, 0x00000080, 0x00000008, regs_within_EACL_FRER_CNT_COMPOUND},
    {"FRER_CNT_MEMBER"                      , 0x00002000, 0x00000100, 0x00000008, regs_within_EACL_FRER_CNT_MEMBER},
    {"STAT_GLOBAL_CFG_EACL"                 , 0x00002dd0, 0x00000001, 0x00000006, regs_within_EACL_STAT_GLOBAL_CFG_EACL},
    {"STAT_CNT_CFG_EACL"                    , 0x00003680, 0x00000020, 0x00000004, regs_within_EACL_STAT_CNT_CFG_EACL},
    {"RAM_CTRL"                             , 0x00002dd6, 0x00000001, 0x00000001, regs_within_EACL_RAM_CTRL},
#ifndef VTSS_RELEASE
    {"COREMEM"                              , 0x00002dd7, 0x00000001, 0x00000004, regs_within_EACL_COREMEM},
#endif
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_HSCH_HSCH_L0_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"HSCH_L0_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_HSCH_L1_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"HSCH_L1_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_HSCH_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CIR_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
    {"EIR_CFG"                              , 0x00000001, 0x00000001, 0x00000001},
    {"SE_CFG"                               , 0x00000002, 0x00000001, 0x00000001},
    {"SE_CONNECT"                           , 0x00000003, 0x00000001, 0x00000001},
    {"SE_DLB_SENSE"                         , 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_HSCH_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CIR_STATE"                            , 0x00000000, 0x00000001, 0x00000001},
    {"EIR_STATE"                            , 0x00000001, 0x00000001, 0x00000001},
    {"SE_STATE"                             , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_QSHP_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"QSHP_CIR_CFG"                         , 0x00000000, 0x00000001, 0x00000001},
    {"QSHP_CFG"                             , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_QSHP_ALLOC_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"QSHP_ALLOC_CFG"                       , 0x00000000, 0x00000001, 0x00000001},
    {"QSHP_CONNECT"                         , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_QSHP_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"QSHP_CIR_STATE"                       , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_HSCH_INP_STATE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INP_STATE"                            , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_HSCH_DWRR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DWRR_ENTRY"                           , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_HSCH_MISC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"HSCH_MISC_CFG"                        , 0x00000000, 0x00000001, 0x00000001},
    {"HSCH_MISC_PORT_CFG"                   , 0x00000001, 0x00000025, 0x00000001},
    {"HSCH_CFG_CFG"                         , 0x00000047, 0x00000001, 0x00000001},
    {"PFC_CFG"                              , 0x00000048, 0x00000025, 0x00000001},
    {"HSCH_LARGE_ENA"                       , 0x00000089, 0x00000009, 0x00000001},
    {"EVENTS_CORE"                          , 0x0000009d, 0x00000001, 0x00000001},
    {"DEBUG_CTRL"                           , 0x0000009e, 0x00000001, 0x00000001},
    {"HSCH_UPDATE_STAT"                     , 0x0000009f, 0x00000001, 0x00000001},
    {"HSCH_FORCE_CTRL"                      , 0x000000a1, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_HSCH_LEAK_LISTS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"HSCH_TIMER_CFG"                       , 0x00000000, 0x00000004, 0x00000001},
    {"HSCH_LEAK_CFG"                        , 0x00000004, 0x00000004, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_SYSTEM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EQ_STAT"                              , 0x00000000, 0x00000001, 0x00000001},
    {"FLUSH_CTRL"                           , 0x00000001, 0x00000001, 0x00000001},
    {"PORT_MODE"                            , 0x00000002, 0x00000025, 0x00000001},
    {"OUTB_SHARE_ENA"                       , 0x00000048, 0x00000005, 0x00000001},
    {"OUTB_CPU_SHARE_ENA"                   , 0x0000004d, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_MMGT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MMGT"                                 , 0x00000000, 0x00000001, 0x00000001},
    {"MMGT_FAST"                            , 0x00000001, 0x00000001, 0x00000001},
    {"RESET_CFG"                            , 0x00000002, 0x00000001, 0x00000001},
    {"PMEM_SIZE"                            , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_TAS_CONFIG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TAS_CFG_CTRL"                         , 0x00000000, 0x00000001, 0x00000001},
    {"TAS_GATE_STATE_CTRL"                  , 0x00000001, 0x00000001, 0x00000001},
    {"TAS_STATEMACHINE_CFG"                 , 0x00000002, 0x00000001, 0x00000001},
    {"TAS_CFG_CTRL2"                        , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_TAS_PROFILE_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TAS_QMAXSDU_CFG"                      , 0x00000000, 0x00000008, 0x00000001},
    {"TAS_PROFILE_CONFIG"                   , 0x00000008, 0x00000001, 0x00000001},
    {"QMAXSDU_DISC_CFG"                     , 0x00000009, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_TAS_LIST_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TAS_BASE_TIME_NSEC"                   , 0x00000000, 0x00000001, 0x00000001},
    {"TAS_BASE_TIME_SEC_LSB"                , 0x00000001, 0x00000001, 0x00000001},
    {"TAS_BASE_TIME_SEC_MSB"                , 0x00000002, 0x00000001, 0x00000001},
    {"TAS_NEXT_OPER_TIME_NSEC"              , 0x00000003, 0x00000001, 0x00000001},
    {"TAS_NEXT_OPER_TIME_SEC_LSB"           , 0x00000004, 0x00000001, 0x00000001},
    {"TAS_NEXT_OPER_TIME_SEC_MSB"           , 0x00000005, 0x00000001, 0x00000001},
    {"TAS_CYCLE_TIME_CFG"                   , 0x00000006, 0x00000001, 0x00000001},
    {"TAS_STARTUP_CFG"                      , 0x00000007, 0x00000001, 0x00000001},
    {"TAS_LIST_CFG"                         , 0x00000008, 0x00000001, 0x00000001},
    {"TAS_LIST_STATE"                       , 0x00000009, 0x00000001, 0x00000001},
    {"TAS_LIST_STATE_INT"                   , 0x0000000a, 0x00000001, 0x00000001},
    {"TAS_LIST_PTR_STATE"                   , 0x0000000b, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_TAS_GCL_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TAS_GCL_CTRL_CFG"                     , 0x00000000, 0x00000001, 0x00000001},
    {"TAS_GCL_TIME_CFG"                     , 0x00000001, 0x00000001, 0x00000001},
    {"TAS_GCL_CTRL_CFG2"                    , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_HSCH_TAS_STATE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TAS_GATE_STATE"                       , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_HSCH[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"HSCH_L0_CFG"                          , 0x00005800, 0x000005c8, 0x00000001, regs_within_HSCH_HSCH_L0_CFG},
    {"HSCH_L1_CFG"                          , 0x00002f40, 0x00000025, 0x00000001, regs_within_HSCH_HSCH_L1_CFG},
    {"HSCH_CFG"                             , 0x00000000, 0x000005c8, 0x00000008, regs_within_HSCH_HSCH_CFG},
    {"HSCH_STATUS"                          , 0x00004000, 0x000005c8, 0x00000004, regs_within_HSCH_HSCH_STATUS},
    {"QSHP_CFG"                             , 0x00002e80, 0x00000028, 0x00000002, regs_within_HSCH_QSHP_CFG},
    {"QSHP_ALLOC_CFG"                       , 0x00003000, 0x000005c8, 0x00000002, regs_within_HSCH_QSHP_ALLOC_CFG},
    {"QSHP_STATUS"                          , 0x00002e40, 0x00000028, 0x00000001, regs_within_HSCH_QSHP_STATUS},
    {"HSCH_INP_STATE"                       , 0x00002e6c, 0x00000002, 0x00000001, regs_within_HSCH_HSCH_INP_STATE},
    {"HSCH_DWRR"                            , 0x00002f00, 0x00000028, 0x00000001, regs_within_HSCH_HSCH_DWRR},
    {"HSCH_MISC"                            , 0x00003b90, 0x00000001, 0x000000a2, regs_within_HSCH_HSCH_MISC},
    {"HSCH_LEAK_LISTS"                      , 0x00002ed0, 0x00000004, 0x00000008, regs_within_HSCH_HSCH_LEAK_LISTS},
    {"SYSTEM"                               , 0x00002f65, 0x00000001, 0x0000004e, regs_within_HSCH_SYSTEM},
    {"MMGT"                                 , 0x00002ef0, 0x00000001, 0x00000004, regs_within_HSCH_MMGT},
    {"TAS_CONFIG"                           , 0x00002ef4, 0x00000001, 0x00000004, regs_within_HSCH_TAS_CONFIG},
    {"TAS_PROFILE_CFG"                      , 0x00003c32, 0x00000020, 0x00000011, regs_within_HSCH_TAS_PROFILE_CFG},
    {"TAS_LIST_CFG"                         , 0x00002e70, 0x00000001, 0x00000010, regs_within_HSCH_TAS_LIST_CFG},
    {"TAS_GCL_CFG"                          , 0x00002e68, 0x00000001, 0x00000004, regs_within_HSCH_TAS_GCL_CFG},
    {"HSCH_TAS_STATE"                       , 0x00002e6e, 0x00000001, 0x00000001, regs_within_HSCH_HSCH_TAS_STATE},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_LRN_COMMON[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"COMMON_ACCESS_CTRL"                   , 0x00000000, 0x00000001, 0x00000001},
    {"MAC_ACCESS_CFG_0"                     , 0x00000001, 0x00000001, 0x00000001},
    {"MAC_ACCESS_CFG_1"                     , 0x00000002, 0x00000001, 0x00000001},
    {"MAC_ACCESS_CFG_2"                     , 0x00000003, 0x00000001, 0x00000001},
    {"MAC_ACCESS_CFG_3"                     , 0x00000004, 0x00000001, 0x00000001},
    {"SCAN_NEXT_CFG"                        , 0x00000005, 0x00000001, 0x00000001},
    {"SCAN_NEXT_CFG_1"                      , 0x00000006, 0x00000001, 0x00000001},
    {"SCAN_LAST_ROW_CFG"                    , 0x00000007, 0x00000001, 0x00000001},
    {"SCAN_NEXT_CNT"                        , 0x00000008, 0x00000001, 0x00000001},
    {"AUTOAGE_CFG"                          , 0x00000009, 0x00000004, 0x00000001},
    {"AUTOAGE_CFG_1"                        , 0x0000000d, 0x00000001, 0x00000001},
    {"AUTOAGE_CFG_2"                        , 0x0000000e, 0x00000001, 0x00000001},
    {"AUTO_LRN_CFG"                         , 0x0000000f, 0x00000001, 0x00000001},
    {"EVENT_STICKY"                         , 0x00000010, 0x00000001, 0x00000001},
    {"LATEST_POS_STATUS"                    , 0x00000011, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_LRN[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"COMMON"                               , 0x00000000, 0x00000001, 0x00000012, regs_within_LRN_COMMON},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_PORT_CONF_HW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DEV10G_MODES"                         , 0x00000000, 0x00000001, 0x00000001},
    {"QSGMII_ENA"                           , 0x00000002, 0x00000001, 0x00000001},
    {"USXGMII_ENA"                          , 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PORT_CONF_QSGMII_CFG_STAT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"QSGMII_CFG"                           , 0x00000000, 0x00000001, 0x00000001},
    {"QSGMII_STAT"                          , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PORT_CONF_USXGMII_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"USXGMII_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
    {"USXGMII_AM_CFG"                       , 0x00000001, 0x00000001, 0x00000001},
    {"USXGMII_LFRF_SEQ"                     , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PORT_CONF_USXGMII_STAT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"USXGMII_RX_STATUS"                    , 0x00000000, 0x00000001, 0x00000001},
    {"USXGMII_RX_ERR_STATUS"                , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_PORT_CONF[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"HW_CFG"                               , 0x00000000, 0x00000001, 0x00000005, regs_within_PORT_CONF_HW_CFG},
    {"QSGMII_CFG_STAT"                      , 0x00000005, 0x00000008, 0x00000002, regs_within_PORT_CONF_QSGMII_CFG_STAT},
    {"USXGMII_CFG"                          , 0x00000015, 0x00000010, 0x00000003, regs_within_PORT_CONF_USXGMII_CFG},
    {"USXGMII_STAT"                         , 0x00000045, 0x00000010, 0x00000002, regs_within_PORT_CONF_USXGMII_STAT},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_QFWD_SYSTEM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SWITCH_PORT_MODE"                     , 0x00000000, 0x00000025, 0x00000001},
    {"FWD_CTRL"                             , 0x00000046, 0x00000001, 0x00000001},
    {"FRAME_COPY_CFG"                       , 0x00000047, 0x0000000c, 0x00000001},
    {"FWD_PRESS_DROP_CNT"                   , 0x00000053, 0x00000001, 0x00000001},
    {"AFWD_PRESS_DROP_CNT"                  , 0x00000054, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_QFWD[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"SYSTEM"                               , 0x00000000, 0x00000001, 0x00000055, regs_within_QFWD_SYSTEM},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_QRES_RES_WRED[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"WRED_PROFILE"                         , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QRES_RES_QOS_ADV[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"WRED_GROUP"                           , 0x00000000, 0x00000025, 0x00000001},
    {"RES_QOS_MODE"                         , 0x00000046, 0x00000001, 0x00000001},
    {"RES_DLB_OFFSET"                       , 0x00000047, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QRES_RES_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RES_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
    {"RES_STAT"                             , 0x00000001, 0x00000001, 0x00000001},
    {"RES_STAT_CUR"                         , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_QRES[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"RES_WRED"                             , 0x00005000, 0x00000048, 0x00000001, regs_within_QRES_RES_WRED},
    {"RES_QOS_ADV"                          , 0x00005048, 0x00000001, 0x00000048, regs_within_QRES_RES_QOS_ADV},
    {"RES_CTRL"                             , 0x00000000, 0x00001400, 0x00000004, regs_within_QRES_RES_CTRL},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_QSYS_SYSTEM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EEE_CFG"                              , 0x00000000, 0x00000020, 0x00000001},
    {"EEE_THRES"                            , 0x00000041, 0x00000001, 0x00000001},
    {"FRM_AGING"                            , 0x00000042, 0x00000001, 0x00000001},
    {"DP_MAP"                               , 0x00000043, 0x00000001, 0x00000001},
    {"STAT_CFG"                             , 0x00000044, 0x00000001, 0x00000001},
    {"IQUEUE_CFG"                           , 0x00000045, 0x00000020, 0x00000001},
    {"DBG_UTIL"                             , 0x00000086, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_MISC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EVENTS_CORE"                          , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_PAUSE_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PAUSE_CFG"                            , 0x00000000, 0x00000025, 0x00000001},
    {"PAUSE_TOT_CFG"                        , 0x00000046, 0x00000001, 0x00000001},
    {"ATOP"                                 , 0x00000047, 0x00000025, 0x00000001},
    {"FWD_PRESSURE"                         , 0x0000008d, 0x00000025, 0x00000001},
    {"ATOP_TOT_CFG"                         , 0x000000d3, 0x00000001, 0x00000001},
    {"PFC_CFG"                              , 0x000000d4, 0x00000025, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_MMGT_PORT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MMGT_PORT_VIEW"                       , 0x00000000, 0x00000001, 0x00000001},
    {"MMGT_PORT_USE"                        , 0x00000001, 0x00000001, 0x00000001},
    {"MMGT_PRIO_USE"                        , 0x00000002, 0x00000008, 0x00000001},
    {"MMGT_IQ_STAT"                         , 0x0000000a, 0x00000001, 0x00000001},
    {"MMGT_TAILDROP_CNT"                    , 0x0000000b, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_SOFDATA_POOL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SOFDATA_STAT_SHR"                     , 0x00000000, 0x00000001, 0x00000001},
    {"SOFDATA_STAT"                         , 0x00000001, 0x00000025, 0x00000001},
    {"SOFDATA_CFG"                          , 0x00000047, 0x00000025, 0x00000001},
    {"SOFDATA_WM_VAL"                       , 0x0000008d, 0x00000005, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_CALCFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CAL_AUTO"                             , 0x00000000, 0x00000004, 0x00000001},
    {"CAL_SEQ"                              , 0x00000007, 0x00000001, 0x00000001},
    {"CAL_SEQ_SEL_CFG"                      , 0x00000008, 0x00000001, 0x00000001},
    {"CAL_CTRL"                             , 0x00000009, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_RAM_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RAM_INIT"                             , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_COREMEM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CM_ADDR"                              , 0x00000000, 0x00000001, 0x00000001},
    {"CM_DATA_WR"                           , 0x00000001, 0x00000001, 0x00000001},
    {"CM_DATA_RD"                           , 0x00000002, 0x00000001, 0x00000001},
    {"CM_OP"                                , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_QSYS[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"SYSTEM"                               , 0x00000000, 0x00000001, 0x00000087, regs_within_QSYS_SYSTEM},
#ifndef VTSS_RELEASE
    {"MISC"                                 , 0x00000087, 0x00000001, 0x00000001, regs_within_QSYS_MISC},
#endif
    {"PAUSE_CFG"                            , 0x00000088, 0x00000001, 0x000000f9, regs_within_QSYS_PAUSE_CFG},
    {"MMGT_PORT"                            , 0x00000181, 0x00000001, 0x0000000c, regs_within_QSYS_MMGT_PORT},
    {"SOFDATA_POOL"                         , 0x0000018d, 0x00000001, 0x00000092, regs_within_QSYS_SOFDATA_POOL},
    {"CALCFG"                               , 0x0000021f, 0x00000001, 0x0000000a, regs_within_QSYS_CALCFG},
    {"RAM_CTRL"                             , 0x00000229, 0x00000001, 0x00000001, regs_within_QSYS_RAM_CTRL},
#ifndef VTSS_RELEASE
    {"COREMEM"                              , 0x0000022a, 0x00000001, 0x00000004, regs_within_QSYS_COREMEM},
#endif
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_REW_COMMON[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"OWN_UPSID"                            , 0x00000000, 0x00000001, 0x00000001},
    {"COMMON_CTRL"                          , 0x00000003, 0x00000001, 0x00000001},
    {"IFH_CTRL"                             , 0x00000004, 0x00000020, 0x00000001},
    {"IFH_CTRL_CPUVD"                       , 0x00000045, 0x00000001, 0x00000001},
    {"PORT_CTRL"                            , 0x00000046, 0x00000025, 0x00000001},
    {"RTAG_ETAG_CTRL"                       , 0x0000008c, 0x00000025, 0x00000001},
    {"TPID_CFG"                             , 0x000000d2, 0x00000003, 0x00000001},
    {"ES0_CTRL"                             , 0x000000d5, 0x00000001, 0x00000001},
    {"MIP_CTRL"                             , 0x000000d6, 0x00000001, 0x00000001},
    {"MIRROR_PROBE_CFG"                     , 0x000000d7, 0x00000003, 0x00000001},
    {"MIRROR_TAG_A_CFG"                     , 0x000000da, 0x00000003, 0x00000001},
    {"MIRROR_TAG_B_CFG"                     , 0x000000dd, 0x00000003, 0x00000001},
    {"DP_MAP"                               , 0x000000e0, 0x00000001, 0x00000001},
    {"DSCP_REMAP"                           , 0x000000e1, 0x00000040, 0x00000001},
    {"RLEG_CFG_0"                           , 0x00000121, 0x00000001, 0x00000001},
    {"RLEG_CFG_1"                           , 0x00000122, 0x00000001, 0x00000001},
    {"CNT_CTRL"                             , 0x00000123, 0x00000001, 0x00000001},
    {"STICKY_EVENT_COUNT"                   , 0x00000124, 0x00000001, 0x00000001},
    {"STICKY_EVENT_CNT_MASK_CFG"            , 0x00000125, 0x00000001, 0x00000001},
    {"STICKY_EVENT"                         , 0x00000126, 0x00000001, 0x00000001},
    {"GCPU_CFG"                             , 0x00000127, 0x00000008, 0x00000001},
    {"VSTAX_PORT_GRP_CFG"                   , 0x0000012f, 0x00000002, 0x00000001},
    {"GCPU_TAG_CFG"                         , 0x00000131, 0x00000002, 0x00000001},
    {"MIP_STICKY_EVENT"                     , 0x00000133, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_MAP_RES_A[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MAP_VAL_A"                            , 0x00000000, 0x00000001, 0x00000001},
    {"MAP_LBL_A"                            , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_MAP_RES_B[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MAP_VAL_B"                            , 0x00000000, 0x00000001, 0x00000001},
    {"MAP_LBL_B"                            , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_PORT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PORT_VLAN_CFG"                        , 0x00000000, 0x00000001, 0x00000001},
    {"PCP_MAP_DE0"                          , 0x00000001, 0x00000008, 0x00000001},
    {"PCP_MAP_DE1"                          , 0x00000009, 0x00000008, 0x00000001},
    {"DEI_MAP_DE0"                          , 0x00000011, 0x00000008, 0x00000001},
    {"DEI_MAP_DE1"                          , 0x00000019, 0x00000008, 0x00000001},
    {"TAG_CTRL"                             , 0x00000021, 0x00000001, 0x00000001},
    {"DSCP_MAP"                             , 0x00000022, 0x00000001, 0x00000001},
    {"PTP_MODE_CFG"                         , 0x00000023, 0x00000002, 0x00000001},
    {"PTP_MISC_CFG"                         , 0x00000025, 0x00000001, 0x00000001},
    {"PTP_EDLY_CFG"                         , 0x00000026, 0x00000001, 0x00000001},
    {"PTP_EDLY_CFG1"                        , 0x00000027, 0x00000001, 0x00000001},
    {"PTP_IDLY1_CFG"                        , 0x00000028, 0x00000001, 0x00000001},
    {"PTP_IDLY1_CFG1"                       , 0x00000029, 0x00000001, 0x00000001},
    {"PTP_IDLY2_CFG"                        , 0x0000002a, 0x00000001, 0x00000001},
    {"PTP_IDLY2_CFG1"                       , 0x0000002b, 0x00000001, 0x00000001},
    {"PTP_SMAC_LOW"                         , 0x0000002c, 0x00000001, 0x00000001},
    {"PTP_SMAC_HIGH"                        , 0x0000002d, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_MIP_TBL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MIP_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
    {"CCM_HMO_CTRL"                         , 0x00000001, 0x00000001, 0x00000001},
    {"MIP_VID_CTRL"                         , 0x00000002, 0x00000001, 0x00000001},
    {"LBM_MAC_HIGH"                         , 0x00000003, 0x00000001, 0x00000001},
    {"LBM_MAC_LOW"                          , 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_MAC_TBL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MAC_TBL_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
    {"EACL_MAC_HIGH"                        , 0x00000001, 0x00000001, 0x00000001},
    {"EACL_MAC_LOW"                         , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_ISDX_TBL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"COS_CTRL"                             , 0x00000000, 0x00000003, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_PTP_MISC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CF_TOO_BIG_STICKY"                    , 0x00000000, 0x00000001, 0x00000001},
    {"CF_TOO_BIG_STICKY1"                   , 0x00000001, 0x00000001, 0x00000001},
    {"PTP_RSRV_NOT_ZERO"                    , 0x00000003, 0x00000001, 0x00000001},
    {"PTP_RSRV_NOT_ZERO1"                   , 0x00000004, 0x00000001, 0x00000001},
    {"PTP_GEN_STAMP_FMT"                    , 0x00000006, 0x00000004, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_ENCAP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MPLS_ENCAP_CFG"                       , 0x00000000, 0x00000001, 0x00000001},
    {"LL_DMAC_MSB"                          , 0x00000001, 0x00000001, 0x00000001},
    {"LL_DMAC_LSB"                          , 0x00000002, 0x00000001, 0x00000001},
    {"LL_SMAC_MSB"                          , 0x00000003, 0x00000001, 0x00000001},
    {"LL_SMAC_LSB"                          , 0x00000004, 0x00000001, 0x00000001},
    {"LL_ETYPE"                             , 0x00000005, 0x00000001, 0x00000001},
    {"MPLS_LABEL_CFG"                       , 0x00000006, 0x00000001, 0x00000001},
    {"RSV_LABEL_CFG"                        , 0x00000007, 0x00000001, 0x00000001},
    {"CW_VAL"                               , 0x00000008, 0x00000001, 0x00000001},
    {"LABEL_VAL"                            , 0x00000009, 0x00000004, 0x00000001},
    {"RSV_LABEL_VAL"                        , 0x0000000d, 0x00000001, 0x00000001},
    {"MPLS_REMARK_CFG"                      , 0x0000000e, 0x00000004, 0x00000001},
    {"LL_TAG_CFG"                           , 0x00000012, 0x00000001, 0x00000001},
    {"LL_TAG_VAL"                           , 0x00000013, 0x00000002, 0x00000001},
    {"LL_TAG_REMARK_CFG"                    , 0x00000015, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_ENCAP_IP4[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IPV4_ENCAP_CFG"                       , 0x00000000, 0x00000001, 0x00000001},
    {"IP_HDR_CFG"                           , 0x00000001, 0x00000001, 0x00000001},
    {"GRE_PROTOCOL_CFG"                     , 0x00000002, 0x00000001, 0x00000001},
    {"SIP_CFG"                              , 0x00000003, 0x00000001, 0x00000001},
    {"DIP_CFG"                              , 0x00000004, 0x00000001, 0x00000001},
    {"IRLEG_CFG"                            , 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_VMID[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RLEG_CTRL"                            , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_PTP_SEQ_NO[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PTP_SEQ_NO"                           , 0x00000000, 0x00000400, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_VOE_SRV_LM_CNT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SRV_LM_CNT_LSB"                       , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_VOE_PORT_LM_CNT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PORT_LM_CNT_LSB"                      , 0x00000000, 0x00000001, 0x00000001},
    {"PORT_FRM_CNT_LSB"                     , 0x00000001, 0x00000001, 0x00000001},
    {"PORT_BYTE_CNT_MSB"                    , 0x00000002, 0x00000001, 0x00000001},
    {"PORT_BYTE_CNT_LSB"                    , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_OAM_PDU_MOD_CONT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TEMP_CNT_REG"                         , 0x00000000, 0x00000001, 0x00000001},
    {"LM_CNT_FRAME"                         , 0x00000001, 0x00000001, 0x00000001},
    {"CCM_LM_INFO_REG"                      , 0x00000002, 0x00000001, 0x00000001},
    {"CCM_LM_TX_B_REG"                      , 0x00000003, 0x00000001, 0x00000001},
    {"CCM_LM_RX_B_REG"                      , 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_PDU_MOD_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DM_PTP_DOMAIN_CFG"                    , 0x00000000, 0x00000020, 0x00000001},
    {"PTP_NTP_OFFSET_CFG"                   , 0x00000041, 0x00000003, 0x00000001},
    {"RD_LAST_PORT_LM_CNT_LSB"              , 0x00000044, 0x00000001, 0x00000001},
    {"RD_LAST_PORT_FRM_CNT_LSB"             , 0x00000045, 0x00000001, 0x00000001},
    {"RD_LAST_PORT_BYTE_CNT_MSB"            , 0x00000046, 0x00000001, 0x00000001},
    {"RD_LAST_PORT_BYTE_CNT_LSB"            , 0x00000047, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_RAM_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RAM_INIT"                             , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_COREMEM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CM_ADDR"                              , 0x00000000, 0x00000001, 0x00000001},
    {"CM_DATA_WR"                           , 0x00000001, 0x00000001, 0x00000001},
    {"CM_DATA_RD"                           , 0x00000002, 0x00000001, 0x00000001},
    {"CM_OP"                                , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_GPTP_DOM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GM_ITS"                               , 0x00000000, 0x00000001, 0x00000001},
    {"GM_IORG_SEC_MSB"                      , 0x00000001, 0x00000001, 0x00000001},
    {"GM_IORG_SEC_LSB"                      , 0x00000002, 0x00000001, 0x00000001},
    {"GM_IORG_NSEC"                         , 0x00000003, 0x00000001, 0x00000001},
    {"GM_ICF_MSB"                           , 0x00000004, 0x00000001, 0x00000001},
    {"GM_ICF_LSB"                           , 0x00000005, 0x00000001, 0x00000001},
    {"GM_ICF_SUB"                           , 0x00000006, 0x00000001, 0x00000001},
    {"GM_RATERATIO"                         , 0x00000007, 0x00000001, 0x00000001},
    {"PTP_CLOCK_ID_MSB"                     , 0x00000008, 0x00000001, 0x00000001},
    {"PTP_CLOCK_ID_LSB"                     , 0x00000009, 0x00000001, 0x00000001},
    {"PTP_SRC_PORT_CFG"                     , 0x0000000a, 0x00000001, 0x00000001},
    {"GM_DELAY"                             , 0x0000000b, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_GPTP_COMMON_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GPTP_NRR_CFG"                         , 0x00000000, 0x00000022, 0x00000001},
    {"GPTP_PORTID_CFG"                      , 0x00000022, 0x00000022, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_REW[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"COMMON"                               , 0x00004e00, 0x00000001, 0x00000134, regs_within_REW_COMMON},
    {"MAP_RES_A"                            , 0x00003000, 0x00000400, 0x00000002, regs_within_REW_MAP_RES_A},
    {"MAP_RES_B"                            , 0x00003800, 0x00000400, 0x00000002, regs_within_REW_MAP_RES_B},
    {"PORT"                                 , 0x00002000, 0x00000025, 0x00000040, regs_within_REW_PORT},
    {"MIP_TBL"                              , 0x00004b00, 0x00000020, 0x00000008, regs_within_REW_MIP_TBL},
    {"MAC_TBL"                              , 0x00002a00, 0x00000080, 0x00000004, regs_within_REW_MAC_TBL},
    {"ISDX_TBL"                             , 0x00000000, 0x00000800, 0x00000004, regs_within_REW_ISDX_TBL},
    {"PTP_MISC"                             , 0x00004a28, 0x00000001, 0x0000000a, regs_within_REW_PTP_MISC},
    {"ENCAP"                                , 0x00002c00, 0x00000020, 0x00000020, regs_within_REW_ENCAP},
    {"ENCAP_IP4"                            , 0x00004c00, 0x00000020, 0x00000008, regs_within_REW_ENCAP_IP4},
    {"VMID"                                 , 0x00002980, 0x0000007f, 0x00000001, regs_within_REW_VMID},
    {"PTP_SEQ_NO"                           , 0x00004000, 0x00000001, 0x00000400, regs_within_REW_PTP_SEQ_NO},
    {"VOE_SRV_LM_CNT"                       , 0x00004d00, 0x00000100, 0x00000001, regs_within_REW_VOE_SRV_LM_CNT},
    {"VOE_PORT_LM_CNT"                      , 0x00004400, 0x00000100, 0x00000004, regs_within_REW_VOE_PORT_LM_CNT},
#ifndef VTSS_RELEASE
    {"OAM_PDU_MOD_CONT"                     , 0x00004800, 0x00000045, 0x00000008, regs_within_REW_OAM_PDU_MOD_CONT},
#endif
    {"PDU_MOD_CFG"                          , 0x00004a32, 0x00000001, 0x00000048, regs_within_REW_PDU_MOD_CFG},
    {"RAM_CTRL"                             , 0x000029ff, 0x00000001, 0x00000001, regs_within_REW_RAM_CTRL},
#ifndef VTSS_RELEASE
    {"COREMEM"                              , 0x00004a7a, 0x00000001, 0x00000004, regs_within_REW_COREMEM},
#endif
    {"GPTP_DOM"                             , 0x00002940, 0x00000004, 0x00000010, regs_within_REW_GPTP_DOM},
    {"GPTP_COMMON_CFG"                      , 0x00004a7e, 0x00000001, 0x00000044, regs_within_REW_GPTP_COMMON_CFG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_VCAP_ES0_VCAP_CORE_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_UPDATE_CTRL"                     , 0x00000000, 0x00000001, 0x00000001},
    {"VCAP_MV_CFG"                          , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_ES0_VCAP_CORE_CACHE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_ENTRY_DAT"                       , 0x00000000, 0x00000040, 0x00000001},
    {"VCAP_MASK_DAT"                        , 0x00000040, 0x00000040, 0x00000001},
    {"VCAP_ACTION_DAT"                      , 0x00000080, 0x00000040, 0x00000001},
    {"VCAP_CNT_DAT"                         , 0x000000c0, 0x00000020, 0x00000001},
    {"VCAP_CNT_FW_DAT"                      , 0x000000e0, 0x00000001, 0x00000001},
    {"VCAP_TG_DAT"                          , 0x000000e1, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_ES0_VCAP_CORE_MAP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_CORE_IDX"                        , 0x00000000, 0x00000001, 0x00000001},
    {"VCAP_CORE_MAP"                        , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_ES0_VCAP_CORE_STICKY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_STICKY"                          , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_ES0_VCAP_CONST[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_VER"                             , 0x00000000, 0x00000001, 0x00000001},
    {"ENTRY_WIDTH"                          , 0x00000001, 0x00000001, 0x00000001},
    {"ENTRY_CNT"                            , 0x00000002, 0x00000001, 0x00000001},
    {"ENTRY_SWCNT"                          , 0x00000003, 0x00000001, 0x00000001},
    {"ENTRY_TG_WIDTH"                       , 0x00000004, 0x00000001, 0x00000001},
    {"ACTION_DEF_CNT"                       , 0x00000005, 0x00000001, 0x00000001},
    {"ACTION_WIDTH"                         , 0x00000006, 0x00000001, 0x00000001},
    {"CNT_WIDTH"                            , 0x00000007, 0x00000001, 0x00000001},
    {"CORE_CNT"                             , 0x00000008, 0x00000001, 0x00000001},
    {"IF_CNT"                               , 0x00000009, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_ES0_TCAM_BIST[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TCAM_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
    {"TCAM_CTRL"                            , 0x00000001, 0x00000001, 0x00000001},
    {"BIST_CTRL"                            , 0x00000002, 0x00000001, 0x00000001},
    {"BIST_CFG"                             , 0x00000003, 0x00000001, 0x00000001},
    {"BIST_STAT"                            , 0x00000004, 0x00000001, 0x00000001},
    {"BIST_FAIL_STAT"                       , 0x00000005, 0x00000010, 0x00000001},
    {"BIST_DIAG_CTRL"                       , 0x00000015, 0x00000001, 0x00000001},
    {"BIST_DIAG_STAT"                       , 0x00000016, 0x00000001, 0x00000001},
    {"BIST_DIAG_BITMAPA_STAT"               , 0x00000017, 0x00000002, 0x00000001},
    {"BIST_DIAG_BITMAPB_STAT"               , 0x00000019, 0x00000002, 0x00000001},
    {"RCR_CTRL"                             , 0x0000001b, 0x00000001, 0x00000001},
    {"RCR_STAT"                             , 0x0000001c, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_ES0_ECC_CHK[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"ECC_CTRL"                             , 0x00000000, 0x00000001, 0x00000001},
    {"ECC_STAT"                             , 0x00000001, 0x00000001, 0x00000001},
    {"ECC_BLK_DLY"                          , 0x00000002, 0x00000001, 0x00000001},
    {"ECC_INV"                              , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_ES0_MEMITGR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MEMITGR_CTRL"                         , 0x00000000, 0x00000001, 0x00000001},
    {"MEMITGR_STAT"                         , 0x00000001, 0x00000001, 0x00000001},
    {"MEMITGR_INFO"                         , 0x00000002, 0x00000001, 0x00000001},
    {"MEMITGR_IDX"                          , 0x00000003, 0x00000001, 0x00000001},
    {"MEMITGR_DIV"                          , 0x00000004, 0x00000001, 0x00000001},
    {"MEMITGR_DBG"                          , 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_VCAP_ES0[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"VCAP_CORE_CFG"                        , 0x00000000, 0x00000001, 0x00000002, regs_within_VCAP_ES0_VCAP_CORE_CFG},
    {"VCAP_CORE_CACHE"                      , 0x00000002, 0x00000001, 0x000000e2, regs_within_VCAP_ES0_VCAP_CORE_CACHE},
    {"VCAP_CORE_MAP"                        , 0x000000e4, 0x00000001, 0x00000002, regs_within_VCAP_ES0_VCAP_CORE_MAP},
#ifndef VTSS_RELEASE
    {"VCAP_CORE_STICKY"                     , 0x000000e6, 0x00000001, 0x00000001, regs_within_VCAP_ES0_VCAP_CORE_STICKY},
#endif
    {"VCAP_CONST"                           , 0x000000e7, 0x00000001, 0x0000000a, regs_within_VCAP_ES0_VCAP_CONST},
    {"TCAM_BIST"                            , 0x000000f1, 0x00000001, 0x0000001d, regs_within_VCAP_ES0_TCAM_BIST},
    {"ECC_CHK"                              , 0x0000010e, 0x00000001, 0x00000004, regs_within_VCAP_ES0_ECC_CHK},
    {"MEMITGR"                              , 0x00000112, 0x00000001, 0x00000006, regs_within_VCAP_ES0_MEMITGR},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_VCAP_ES2_VCAP_CORE_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_UPDATE_CTRL"                     , 0x00000000, 0x00000001, 0x00000001},
    {"VCAP_MV_CFG"                          , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_ES2_VCAP_CORE_CACHE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_ENTRY_DAT"                       , 0x00000000, 0x00000040, 0x00000001},
    {"VCAP_MASK_DAT"                        , 0x00000040, 0x00000040, 0x00000001},
    {"VCAP_ACTION_DAT"                      , 0x00000080, 0x00000040, 0x00000001},
    {"VCAP_CNT_DAT"                         , 0x000000c0, 0x00000020, 0x00000001},
    {"VCAP_CNT_FW_DAT"                      , 0x000000e0, 0x00000001, 0x00000001},
    {"VCAP_TG_DAT"                          , 0x000000e1, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_ES2_VCAP_CORE_MAP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_CORE_IDX"                        , 0x00000000, 0x00000001, 0x00000001},
    {"VCAP_CORE_MAP"                        , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_ES2_VCAP_CORE_STICKY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_STICKY"                          , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_ES2_VCAP_CONST[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_VER"                             , 0x00000000, 0x00000001, 0x00000001},
    {"ENTRY_WIDTH"                          , 0x00000001, 0x00000001, 0x00000001},
    {"ENTRY_CNT"                            , 0x00000002, 0x00000001, 0x00000001},
    {"ENTRY_SWCNT"                          , 0x00000003, 0x00000001, 0x00000001},
    {"ENTRY_TG_WIDTH"                       , 0x00000004, 0x00000001, 0x00000001},
    {"ACTION_DEF_CNT"                       , 0x00000005, 0x00000001, 0x00000001},
    {"ACTION_WIDTH"                         , 0x00000006, 0x00000001, 0x00000001},
    {"CNT_WIDTH"                            , 0x00000007, 0x00000001, 0x00000001},
    {"CORE_CNT"                             , 0x00000008, 0x00000001, 0x00000001},
    {"IF_CNT"                               , 0x00000009, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_ES2_TCAM_BIST[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TCAM_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
    {"TCAM_CTRL"                            , 0x00000001, 0x00000001, 0x00000001},
    {"BIST_CTRL"                            , 0x00000002, 0x00000001, 0x00000001},
    {"BIST_CFG"                             , 0x00000003, 0x00000001, 0x00000001},
    {"BIST_STAT"                            , 0x00000004, 0x00000001, 0x00000001},
    {"BIST_FAIL_STAT"                       , 0x00000005, 0x00000010, 0x00000001},
    {"BIST_DIAG_CTRL"                       , 0x00000015, 0x00000001, 0x00000001},
    {"BIST_DIAG_STAT"                       , 0x00000016, 0x00000001, 0x00000001},
    {"BIST_DIAG_BITMAPA_STAT"               , 0x00000017, 0x00000002, 0x00000001},
    {"BIST_DIAG_BITMAPB_STAT"               , 0x00000019, 0x00000002, 0x00000001},
    {"RCR_CTRL"                             , 0x0000001b, 0x00000001, 0x00000001},
    {"RCR_STAT"                             , 0x0000001c, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_ES2_ECC_CHK[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"ECC_CTRL"                             , 0x00000000, 0x00000001, 0x00000001},
    {"ECC_STAT"                             , 0x00000001, 0x00000001, 0x00000001},
    {"ECC_BLK_DLY"                          , 0x00000002, 0x00000001, 0x00000001},
    {"ECC_INV"                              , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_ES2_MEMITGR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MEMITGR_CTRL"                         , 0x00000000, 0x00000001, 0x00000001},
    {"MEMITGR_STAT"                         , 0x00000001, 0x00000001, 0x00000001},
    {"MEMITGR_INFO"                         , 0x00000002, 0x00000001, 0x00000001},
    {"MEMITGR_IDX"                          , 0x00000003, 0x00000001, 0x00000001},
    {"MEMITGR_DIV"                          , 0x00000004, 0x00000001, 0x00000001},
    {"MEMITGR_DBG"                          , 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_VCAP_ES2[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"VCAP_CORE_CFG"                        , 0x00000000, 0x00000001, 0x00000002, regs_within_VCAP_ES2_VCAP_CORE_CFG},
    {"VCAP_CORE_CACHE"                      , 0x00000002, 0x00000001, 0x000000e2, regs_within_VCAP_ES2_VCAP_CORE_CACHE},
    {"VCAP_CORE_MAP"                        , 0x000000e4, 0x00000001, 0x00000002, regs_within_VCAP_ES2_VCAP_CORE_MAP},
#ifndef VTSS_RELEASE
    {"VCAP_CORE_STICKY"                     , 0x000000e6, 0x00000001, 0x00000001, regs_within_VCAP_ES2_VCAP_CORE_STICKY},
#endif
    {"VCAP_CONST"                           , 0x000000e7, 0x00000001, 0x0000000a, regs_within_VCAP_ES2_VCAP_CONST},
    {"TCAM_BIST"                            , 0x000000f1, 0x00000001, 0x0000001d, regs_within_VCAP_ES2_TCAM_BIST},
    {"ECC_CHK"                              , 0x0000010e, 0x00000001, 0x00000004, regs_within_VCAP_ES2_ECC_CHK},
    {"MEMITGR"                              , 0x00000112, 0x00000001, 0x00000006, regs_within_VCAP_ES2_MEMITGR},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_VCAP_IP6PFX_VCAP_CORE_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_UPDATE_CTRL"                     , 0x00000000, 0x00000001, 0x00000001},
    {"VCAP_MV_CFG"                          , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_IP6PFX_VCAP_CORE_CACHE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_ENTRY_DAT"                       , 0x00000000, 0x00000040, 0x00000001},
    {"VCAP_MASK_DAT"                        , 0x00000040, 0x00000040, 0x00000001},
    {"VCAP_ACTION_DAT"                      , 0x00000080, 0x00000040, 0x00000001},
    {"VCAP_CNT_DAT"                         , 0x000000c0, 0x00000020, 0x00000001},
    {"VCAP_CNT_FW_DAT"                      , 0x000000e0, 0x00000001, 0x00000001},
    {"VCAP_TG_DAT"                          , 0x000000e1, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_IP6PFX_VCAP_CORE_MAP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_CORE_IDX"                        , 0x00000000, 0x00000001, 0x00000001},
    {"VCAP_CORE_MAP"                        , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_IP6PFX_VCAP_CORE_STICKY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_STICKY"                          , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_IP6PFX_VCAP_CONST[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_VER"                             , 0x00000000, 0x00000001, 0x00000001},
    {"ENTRY_WIDTH"                          , 0x00000001, 0x00000001, 0x00000001},
    {"ENTRY_CNT"                            , 0x00000002, 0x00000001, 0x00000001},
    {"ENTRY_SWCNT"                          , 0x00000003, 0x00000001, 0x00000001},
    {"ENTRY_TG_WIDTH"                       , 0x00000004, 0x00000001, 0x00000001},
    {"ACTION_DEF_CNT"                       , 0x00000005, 0x00000001, 0x00000001},
    {"ACTION_WIDTH"                         , 0x00000006, 0x00000001, 0x00000001},
    {"CNT_WIDTH"                            , 0x00000007, 0x00000001, 0x00000001},
    {"CORE_CNT"                             , 0x00000008, 0x00000001, 0x00000001},
    {"IF_CNT"                               , 0x00000009, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_IP6PFX_TCAM_BIST[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TCAM_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
    {"TCAM_CTRL"                            , 0x00000001, 0x00000001, 0x00000001},
    {"BIST_CTRL"                            , 0x00000002, 0x00000001, 0x00000001},
    {"BIST_CFG"                             , 0x00000003, 0x00000001, 0x00000001},
    {"BIST_STAT"                            , 0x00000004, 0x00000001, 0x00000001},
    {"BIST_FAIL_STAT"                       , 0x00000005, 0x00000010, 0x00000001},
    {"BIST_DIAG_CTRL"                       , 0x00000015, 0x00000001, 0x00000001},
    {"BIST_DIAG_STAT"                       , 0x00000016, 0x00000001, 0x00000001},
    {"BIST_DIAG_BITMAPA_STAT"               , 0x00000017, 0x00000002, 0x00000001},
    {"BIST_DIAG_BITMAPB_STAT"               , 0x00000019, 0x00000002, 0x00000001},
    {"RCR_CTRL"                             , 0x0000001b, 0x00000001, 0x00000001},
    {"RCR_STAT"                             , 0x0000001c, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_IP6PFX_ECC_CHK[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"ECC_CTRL"                             , 0x00000000, 0x00000001, 0x00000001},
    {"ECC_STAT"                             , 0x00000001, 0x00000001, 0x00000001},
    {"ECC_BLK_DLY"                          , 0x00000002, 0x00000001, 0x00000001},
    {"ECC_INV"                              , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_IP6PFX_MEMITGR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MEMITGR_CTRL"                         , 0x00000000, 0x00000001, 0x00000001},
    {"MEMITGR_STAT"                         , 0x00000001, 0x00000001, 0x00000001},
    {"MEMITGR_INFO"                         , 0x00000002, 0x00000001, 0x00000001},
    {"MEMITGR_IDX"                          , 0x00000003, 0x00000001, 0x00000001},
    {"MEMITGR_DIV"                          , 0x00000004, 0x00000001, 0x00000001},
    {"MEMITGR_DBG"                          , 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_VCAP_IP6PFX[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"VCAP_CORE_CFG"                        , 0x00000000, 0x00000001, 0x00000002, regs_within_VCAP_IP6PFX_VCAP_CORE_CFG},
    {"VCAP_CORE_CACHE"                      , 0x00000002, 0x00000001, 0x000000e2, regs_within_VCAP_IP6PFX_VCAP_CORE_CACHE},
    {"VCAP_CORE_MAP"                        , 0x000000e4, 0x00000001, 0x00000002, regs_within_VCAP_IP6PFX_VCAP_CORE_MAP},
#ifndef VTSS_RELEASE
    {"VCAP_CORE_STICKY"                     , 0x000000e6, 0x00000001, 0x00000001, regs_within_VCAP_IP6PFX_VCAP_CORE_STICKY},
#endif
    {"VCAP_CONST"                           , 0x000000e7, 0x00000001, 0x0000000a, regs_within_VCAP_IP6PFX_VCAP_CONST},
    {"TCAM_BIST"                            , 0x000000f1, 0x00000001, 0x0000001d, regs_within_VCAP_IP6PFX_TCAM_BIST},
    {"ECC_CHK"                              , 0x0000010e, 0x00000001, 0x00000004, regs_within_VCAP_IP6PFX_ECC_CHK},
    {"MEMITGR"                              , 0x00000112, 0x00000001, 0x00000006, regs_within_VCAP_IP6PFX_MEMITGR},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_VCAP_SUPER_VCAP_CORE_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_UPDATE_CTRL"                     , 0x00000000, 0x00000001, 0x00000001},
    {"VCAP_MV_CFG"                          , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_SUPER_VCAP_CORE_CACHE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_ENTRY_DAT"                       , 0x00000000, 0x00000040, 0x00000001},
    {"VCAP_MASK_DAT"                        , 0x00000040, 0x00000040, 0x00000001},
    {"VCAP_ACTION_DAT"                      , 0x00000080, 0x00000040, 0x00000001},
    {"VCAP_CNT_DAT"                         , 0x000000c0, 0x00000020, 0x00000001},
    {"VCAP_CNT_FW_DAT"                      , 0x000000e0, 0x00000001, 0x00000001},
    {"VCAP_TG_DAT"                          , 0x000000e1, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_SUPER_VCAP_CORE_MAP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_CORE_IDX"                        , 0x00000000, 0x00000001, 0x00000001},
    {"VCAP_CORE_MAP"                        , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_SUPER_VCAP_CORE_STICKY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_STICKY"                          , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_SUPER_VCAP_CONST[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_VER"                             , 0x00000000, 0x00000001, 0x00000001},
    {"ENTRY_WIDTH"                          , 0x00000001, 0x00000001, 0x00000001},
    {"ENTRY_CNT"                            , 0x00000002, 0x00000001, 0x00000001},
    {"ENTRY_SWCNT"                          , 0x00000003, 0x00000001, 0x00000001},
    {"ENTRY_TG_WIDTH"                       , 0x00000004, 0x00000001, 0x00000001},
    {"ACTION_DEF_CNT"                       , 0x00000005, 0x00000001, 0x00000001},
    {"ACTION_WIDTH"                         , 0x00000006, 0x00000001, 0x00000001},
    {"CNT_WIDTH"                            , 0x00000007, 0x00000001, 0x00000001},
    {"CORE_CNT"                             , 0x00000008, 0x00000001, 0x00000001},
    {"IF_CNT"                               , 0x00000009, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_SUPER_TCAM_BIST[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TCAM_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
    {"TCAM_CTRL"                            , 0x00000001, 0x00000001, 0x00000001},
    {"BIST_CTRL"                            , 0x00000002, 0x00000001, 0x00000001},
    {"BIST_CFG"                             , 0x00000003, 0x00000001, 0x00000001},
    {"BIST_STAT"                            , 0x00000004, 0x00000001, 0x00000001},
    {"BIST_FAIL_STAT"                       , 0x00000005, 0x00000010, 0x00000001},
    {"BIST_DIAG_CTRL"                       , 0x00000015, 0x00000001, 0x00000001},
    {"BIST_DIAG_STAT"                       , 0x00000016, 0x00000001, 0x00000001},
    {"BIST_DIAG_BITMAPA_STAT"               , 0x00000017, 0x00000002, 0x00000001},
    {"BIST_DIAG_BITMAPB_STAT"               , 0x00000019, 0x00000002, 0x00000001},
    {"RCR_CTRL"                             , 0x0000001b, 0x00000001, 0x00000001},
    {"RCR_STAT"                             , 0x0000001c, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_SUPER_ECC_CHK[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"ECC_CTRL"                             , 0x00000000, 0x00000001, 0x00000001},
    {"ECC_STAT"                             , 0x00000001, 0x00000001, 0x00000001},
    {"ECC_BLK_DLY"                          , 0x00000002, 0x00000001, 0x00000001},
    {"ECC_INV"                              , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_SUPER_MEMITGR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MEMITGR_CTRL"                         , 0x00000000, 0x00000001, 0x00000001},
    {"MEMITGR_STAT"                         , 0x00000001, 0x00000001, 0x00000001},
    {"MEMITGR_INFO"                         , 0x00000002, 0x00000001, 0x00000001},
    {"MEMITGR_IDX"                          , 0x00000003, 0x00000001, 0x00000001},
    {"MEMITGR_DIV"                          , 0x00000004, 0x00000001, 0x00000001},
    {"MEMITGR_DBG"                          , 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_SUPER_RAM_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RAM_INIT"                             , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_SUPER_COREMEM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CM_ADDR"                              , 0x00000000, 0x00000001, 0x00000001},
    {"CM_DATA_WR"                           , 0x00000001, 0x00000001, 0x00000001},
    {"CM_DATA_RD"                           , 0x00000002, 0x00000001, 0x00000001},
    {"CM_OP"                                , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_VCAP_SUPER[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"VCAP_CORE_CFG"                        , 0x00000000, 0x00000001, 0x00000002, regs_within_VCAP_SUPER_VCAP_CORE_CFG},
    {"VCAP_CORE_CACHE"                      , 0x00000002, 0x00000001, 0x000000e2, regs_within_VCAP_SUPER_VCAP_CORE_CACHE},
    {"VCAP_CORE_MAP"                        , 0x000000e4, 0x00000001, 0x00000002, regs_within_VCAP_SUPER_VCAP_CORE_MAP},
#ifndef VTSS_RELEASE
    {"VCAP_CORE_STICKY"                     , 0x000000e6, 0x00000001, 0x00000001, regs_within_VCAP_SUPER_VCAP_CORE_STICKY},
#endif
    {"VCAP_CONST"                           , 0x000000e7, 0x00000001, 0x0000000a, regs_within_VCAP_SUPER_VCAP_CONST},
    {"TCAM_BIST"                            , 0x000000f1, 0x00000001, 0x0000001d, regs_within_VCAP_SUPER_TCAM_BIST},
    {"ECC_CHK"                              , 0x0000010e, 0x00000001, 0x00000004, regs_within_VCAP_SUPER_ECC_CHK},
    {"MEMITGR"                              , 0x00000112, 0x00000001, 0x00000006, regs_within_VCAP_SUPER_MEMITGR},
    {"RAM_CTRL"                             , 0x00000118, 0x00000001, 0x00000001, regs_within_VCAP_SUPER_RAM_CTRL},
#ifndef VTSS_RELEASE
    {"COREMEM"                              , 0x00000119, 0x00000001, 0x00000004, regs_within_VCAP_SUPER_COREMEM},
#endif
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_VOP_COMMON[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VOP_CTRL"                             , 0x00000000, 0x00000001, 0x00000001},
    {"CPU_EXTR_CFG"                         , 0x00000001, 0x00000001, 0x00000001},
    {"CPU_EXTR_CFG_1"                       , 0x00000002, 0x00000001, 0x00000001},
    {"CPU_EXTR_CFG_2"                       , 0x00000003, 0x00000001, 0x00000001},
    {"CPU_EXTR_MPLS"                        , 0x00000004, 0x00000001, 0x00000001},
    {"CPU_EXTR_L3"                          , 0x00000005, 0x00000001, 0x00000001},
    {"VERSION_CTRL"                         , 0x00000006, 0x00000001, 0x00000001},
    {"VERSION_CTRL_2"                       , 0x00000007, 0x00000001, 0x00000001},
    {"VERSION_CTRL_3"                       , 0x00000008, 0x00000001, 0x00000001},
    {"VERSION_CTRL_MPLS"                    , 0x00000009, 0x00000001, 0x00000001},
    {"OAM_GENERIC_CFG"                      , 0x0000000a, 0x00000010, 0x00000001},
    {"MPLS_GENERIC_CODEPOINT"               , 0x0000001a, 0x00000010, 0x00000001},
    {"SAM_SEQ_TS_CFG"                       , 0x0000002a, 0x00000001, 0x00000001},
    {"SAM_SEQ_TS_CFG_2"                     , 0x0000002b, 0x00000001, 0x00000001},
    {"LOC_CTRL"                             , 0x0000002c, 0x00000001, 0x00000001},
    {"LOC_PERIOD_CFG"                       , 0x0000002d, 0x0000001b, 0x00000001},
    {"HMO_PERIOD_CFG"                       , 0x00000048, 0x00000002, 0x00000001},
    {"HMO_FORCE_SLOT_CFG"                   , 0x0000004a, 0x00000002, 0x00000001},
    {"HMO_TIMER_CFG"                        , 0x0000004c, 0x00000001, 0x00000001},
    {"LOC_SCAN_STICKY"                      , 0x0000004d, 0x00000001, 0x00000001},
    {"MASTER_INTR_CTRL"                     , 0x0000004e, 0x00000001, 0x00000001},
    {"VOE32_INTR"                           , 0x0000004f, 0x00000001, 0x00000001},
    {"INTR"                                 , 0x00000051, 0x00000002, 0x00000001},
    {"COMMON_MEP_MC_MAC_LSB"                , 0x00000074, 0x00000001, 0x00000001},
    {"COMMON_MEP_MC_MAC_MSB"                , 0x00000075, 0x00000001, 0x00000001},
    {"LOC_CTRL_2"                           , 0x00000076, 0x00000001, 0x00000001},
    {"CPU_EXTR_MRP"                         , 0x00000077, 0x00000001, 0x00000001},
    {"CPU_EXTR_DLR"                         , 0x00000078, 0x00000001, 0x00000001},
    {"TICK_CFG"                             , 0x00000079, 0x00000001, 0x00000001},
    {"MRP_TS_CFG"                           , 0x0000007a, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_VOE_CONF_REG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VOE_MISC_CONFIG"                      , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_VOE_CONF[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VOE_COMMON_CFG"                       , 0x00000000, 0x00000001, 0x00000001},
    {"VOE_CTRL"                             , 0x00000001, 0x00000001, 0x00000001},
    {"VOE_MEPID_CFG"                        , 0x00000002, 0x00000001, 0x00000001},
    {"PEER_MEPID_CFG"                       , 0x00000003, 0x00000001, 0x00000001},
    {"SAM_COSID_SEQ_CFG"                    , 0x00000004, 0x00000001, 0x00000001},
    {"SAM_NON_OAM_SEQ_CFG"                  , 0x00000005, 0x00000001, 0x00000001},
    {"OAM_CPU_COPY_CTRL"                    , 0x00000006, 0x00000001, 0x00000001},
    {"OAM_CPU_COPY_CTRL_2"                  , 0x00000007, 0x00000001, 0x00000001},
    {"PDU_VOE_PASS"                         , 0x00000008, 0x00000001, 0x00000001},
    {"OAM_CNT_OAM_CTRL"                     , 0x00000009, 0x00000001, 0x00000001},
    {"OAM_CNT_DATA_CTRL"                    , 0x0000000a, 0x00000001, 0x00000001},
    {"OAM_CNT_DATA_CTRL_2"                  , 0x0000000b, 0x00000001, 0x00000001},
    {"MEP_UC_MAC_LSB"                       , 0x0000000c, 0x00000001, 0x00000001},
    {"MEP_UC_MAC_MSB"                       , 0x0000000d, 0x00000001, 0x00000001},
    {"OAM_HW_CTRL"                          , 0x0000000e, 0x00000001, 0x00000001},
    {"LOOPBACK_ENA"                         , 0x0000000f, 0x00000001, 0x00000001},
    {"LOOPBACK_CFG"                         , 0x00000010, 0x00000001, 0x00000001},
    {"TX_TRANSID_UPDATE"                    , 0x00000011, 0x00000001, 0x00000001},
    {"CCM_CFG"                              , 0x00000012, 0x00000001, 0x00000001},
    {"CCM_MEGID_CFG"                        , 0x00000013, 0x0000000c, 0x00000001},
    {"SLM_CONFIG"                           , 0x0000001f, 0x00000001, 0x00000001},
    {"SLM_TEST_ID"                          , 0x00000020, 0x00000001, 0x00000001},
    {"SLM_PEER_LIST"                        , 0x00000021, 0x00000008, 0x00000001},
    {"G_8113_1_CFG"                         , 0x00000029, 0x00000001, 0x00000001},
    {"G_8113_1_REMOTE_MIPID"                , 0x0000002a, 0x00000001, 0x00000001},
    {"G_8113_1_REMOTE_MIPID1"               , 0x0000002b, 0x00000001, 0x00000001},
    {"G_8113_1_REMOTE_MIPID2"               , 0x0000002c, 0x00000001, 0x00000001},
    {"G_8113_1_REMOTE_MIPID3"               , 0x0000002d, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_VOE_STAT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RX_SEL_OAM_CNT"                       , 0x00000000, 0x00000001, 0x00000001},
    {"RX_OAM_FRM_CNT"                       , 0x00000001, 0x00000001, 0x00000001},
    {"TX_SEL_OAM_CNT"                       , 0x00000002, 0x00000001, 0x00000001},
    {"TX_OAM_FRM_CNT"                       , 0x00000003, 0x00000001, 0x00000001},
    {"CCM_RX_FRM_CNT"                       , 0x00000004, 0x00000001, 0x00000001},
    {"CCM_TX_SEQ_CFG"                       , 0x00000005, 0x00000001, 0x00000001},
    {"CCM_RX_SEQ_CFG"                       , 0x00000006, 0x00000001, 0x00000001},
    {"CCM_RX_WARNING"                       , 0x00000007, 0x00000001, 0x00000001},
    {"CCM_ERR"                              , 0x00000008, 0x00000001, 0x00000001},
    {"CCM_RX_ERR_1"                         , 0x00000009, 0x00000001, 0x00000001},
    {"LBM_TX_TRANSID_CFG"                   , 0x0000000a, 0x00000001, 0x00000001},
    {"LBR_TX_FRM_CNT"                       , 0x0000000b, 0x00000001, 0x00000001},
    {"LBR_RX_TRANSID_CFG"                   , 0x0000000c, 0x00000001, 0x00000001},
    {"LBR_RX_FRM_CNT"                       , 0x0000000d, 0x00000001, 0x00000001},
    {"LBR_RX_TRANSID_ERR_CNT"               , 0x0000000e, 0x00000001, 0x00000001},
    {"DM_PDU_CNT"                           , 0x0000000f, 0x00000001, 0x00000001},
    {"LM_PDU_CNT"                           , 0x00000010, 0x00000001, 0x00000001},
    {"TX_OAM_DISCARD"                       , 0x00000011, 0x00000001, 0x00000001},
    {"RX_OAM_DISCARD"                       , 0x00000012, 0x00000001, 0x00000001},
    {"PDU_EXTRACT"                          , 0x00000013, 0x00000001, 0x00000001},
    {"AUTO_HIT_ME_ONCE"                     , 0x00000014, 0x00000001, 0x00000001},
    {"SYNLM_EXTRACT"                        , 0x00000015, 0x00000001, 0x00000001},
    {"OAM_TX_STICKY"                        , 0x00000016, 0x00000001, 0x00000001},
    {"OAM_RX_STICKY"                        , 0x00000017, 0x00000001, 0x00000001},
    {"OAM_RX_STICKY2"                       , 0x00000018, 0x00000001, 0x00000001},
    {"CCM_STAT"                             , 0x00000019, 0x00000001, 0x00000001},
    {"CCM_STAT_2"                           , 0x0000001a, 0x00000001, 0x00000001},
    {"CCM_RX_LAST"                          , 0x0000001b, 0x00000001, 0x00000001},
    {"AIS_STAT"                             , 0x0000001c, 0x00000001, 0x00000001},
    {"AIS_RX_LAST"                          , 0x0000001d, 0x00000001, 0x00000001},
    {"LCK_STAT"                             , 0x0000001e, 0x00000001, 0x00000001},
    {"LCK_RX_LAST"                          , 0x0000001f, 0x00000001, 0x00000001},
    {"CSF_STAT"                             , 0x00000020, 0x00000001, 0x00000001},
    {"CSF_RX_LAST"                          , 0x00000021, 0x00000001, 0x00000001},
    {"INTR_STICKY"                          , 0x00000022, 0x00000001, 0x00000001},
    {"INTR_ENA"                             , 0x00000023, 0x00000001, 0x00000001},
    {"SLM_TX_FRM_CNT"                       , 0x00000024, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_VOE_STAT_REG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"BLK_STICKY"                           , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_VOE_CCM_LM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CCM_TX_FCB_CFG"                       , 0x00000000, 0x00000001, 0x00000001},
    {"CCM_RX_FCB_CFG"                       , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_VOE_CONTEXT_ANA[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CT_OAM_COMMON_ANA"                    , 0x00000000, 0x00000001, 0x00000001},
    {"CT_OAM_COMMON1_ANA"                   , 0x00000001, 0x00000001, 0x00000001},
    {"CT_OAM_INFO_ANA"                      , 0x00000002, 0x00000001, 0x00000001},
    {"CT_OAM_INFO1_ANA"                     , 0x00000003, 0x00000001, 0x00000001},
    {"CT_OAM_CCM_TLV_INFO_ANA"              , 0x00000004, 0x00000001, 0x00000001},
    {"CT_OAM_MPLS_INFO_ANA"                 , 0x00000005, 0x00000001, 0x00000001},
    {"CT_OAM_L3_INFO_ANA"                   , 0x00000006, 0x00000001, 0x00000001},
    {"CT_OAM_DATA_ANA"                      , 0x00000007, 0x00000001, 0x00000001},
    {"CT_OAM_DATA1_ANA"                     , 0x00000008, 0x00000001, 0x00000001},
    {"CT_OAM_MRP_DELTA_TS_ANA"              , 0x00000009, 0x00000001, 0x00000001},
    {"CT_OAM_MRP_SEQ_ANA"                   , 0x0000000a, 0x00000001, 0x00000001},
    {"CT_OAM_MRP_INFO_ANA"                  , 0x0000000b, 0x00000001, 0x00000001},
    {"CT_OAM_DLR_INFO_ANA"                  , 0x0000000c, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_VOE_CONTEXT_REW[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CT_OAM_COMMON_REW"                    , 0x00000000, 0x00000001, 0x00000001},
    {"CT_OAM_COMMON1_REW"                   , 0x00000001, 0x00000001, 0x00000001},
    {"CT_OAM_INFO_REW"                      , 0x00000002, 0x00000001, 0x00000001},
    {"CT_OAM_INTO1_REW"                     , 0x00000003, 0x00000001, 0x00000001},
    {"CT_OAM_CCM_TLV_INFO_REW"              , 0x00000004, 0x00000001, 0x00000001},
    {"CT_OAM_MPLS_INFO_REW"                 , 0x00000005, 0x00000001, 0x00000001},
    {"CT_OAM_L3_INFO_REW"                   , 0x00000006, 0x00000001, 0x00000001},
    {"CT_OAM_DATA_REW"                      , 0x00000007, 0x00000001, 0x00000001},
    {"CT_OAM_DATA1_REW"                     , 0x00000008, 0x00000001, 0x00000001},
    {"CT_OAM_MRP_INFO_REW"                  , 0x00000009, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_VOE_CRC_ERR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LBR_CRC_ERR_CNT"                      , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_ANA_COSID_MAP_CONF[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"COSID_MAP_TABLE_ANA"                  , 0x00000000, 0x00000001, 0x00000001},
    {"COSID_MAP_CFG_ANA"                    , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_REW_COSID_MAP_CONF[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"COSID_MAP_TABLE_REW"                  , 0x00000000, 0x00000001, 0x00000001},
    {"COSID_MAP_CFG_REW"                    , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_PORT_COSID_MAP_CONF[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PORT_RX_COSID_MAP"                    , 0x00000000, 0x00000001, 0x00000001},
    {"PORT_RX_COSID_MAP1"                   , 0x00000001, 0x00000001, 0x00000001},
    {"PORT_TX_COSID_MAP"                    , 0x00000002, 0x00000001, 0x00000001},
    {"PORT_TX_COSID_MAP1"                   , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_SAM_COSID_SEQ_CNT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SAM_LBM_TX_TRANSID"                   , 0x00000000, 0x00000007, 0x00000001},
    {"SAM_LBR_TX_FRM_CNT"                   , 0x00000007, 0x00000007, 0x00000001},
    {"SAM_LBR_RX_FRM_CNT"                   , 0x0000000e, 0x00000007, 0x00000001},
    {"SAM_LBR_RX_TRANSID"                   , 0x00000015, 0x00000007, 0x00000001},
    {"SAM_LBR_RX_TRANSID_ERR_CNT"           , 0x0000001c, 0x00000007, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_RAM_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RAM_INIT"                             , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_COREMEM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CM_ADDR"                              , 0x00000000, 0x00000001, 0x00000001},
    {"CM_DATA_WR"                           , 0x00000001, 0x00000001, 0x00000001},
    {"CM_DATA_RD"                           , 0x00000002, 0x00000001, 0x00000001},
    {"CM_OP"                                , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_VOP[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"COMMON"                               , 0x00002ac0, 0x00000001, 0x0000007b, regs_within_VOP_COMMON},
    {"VOE_CONF_REG"                         , 0x00002980, 0x00000040, 0x00000001, regs_within_VOP_VOE_CONF_REG},
    {"VOE_CONF"                             , 0x00000000, 0x00000040, 0x00000040, regs_within_VOP_VOE_CONF},
    {"VOE_STAT"                             , 0x00001000, 0x00000040, 0x00000040, regs_within_VOP_VOE_STAT},
    {"VOE_STAT_REG"                         , 0x000029c0, 0x00000040, 0x00000001, regs_within_VOP_VOE_STAT_REG},
    {"VOE_CCM_LM"                           , 0x00002880, 0x00000040, 0x00000002, regs_within_VOP_VOE_CCM_LM},
#ifndef VTSS_RELEASE
    {"VOE_CONTEXT_ANA"                      , 0x00002000, 0x00000085, 0x00000010, regs_within_VOP_VOE_CONTEXT_ANA},
#endif
#ifndef VTSS_RELEASE
    {"VOE_CONTEXT_REW"                      , 0x00003800, 0x00000045, 0x00000010, regs_within_VOP_VOE_CONTEXT_REW},
#endif
    {"VOE_CRC_ERR"                          , 0x00002a00, 0x00000040, 0x00000001, regs_within_VOP_VOE_CRC_ERR},
    {"ANA_COSID_MAP_CONF"                   , 0x00002a40, 0x00000020, 0x00000002, regs_within_VOP_ANA_COSID_MAP_CONF},
    {"REW_COSID_MAP_CONF"                   , 0x00002a80, 0x00000020, 0x00000002, regs_within_VOP_REW_COSID_MAP_CONF},
    {"PORT_COSID_MAP_CONF"                  , 0x00002900, 0x00000020, 0x00000004, regs_within_VOP_PORT_COSID_MAP_CONF},
    {"SAM_COSID_SEQ_CNT"                    , 0x00003000, 0x00000020, 0x00000040, regs_within_VOP_SAM_COSID_SEQ_CNT},
    {"RAM_CTRL"                             , 0x00002850, 0x00000001, 0x00000001, regs_within_VOP_RAM_CTRL},
#ifndef VTSS_RELEASE
    {"COREMEM"                              , 0x00002851, 0x00000001, 0x00000004, regs_within_VOP_COREMEM},
#endif
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_VOP_L3_VOE_CONF_L3[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VOE_COMMON_CFG"                       , 0x00000000, 0x00000001, 0x00000001},
    {"VOE_CTRL_L3"                          , 0x00000001, 0x00000001, 0x00000001},
    {"VOE_MAC_CFG"                          , 0x00000002, 0x00000001, 0x00000001},
    {"VOE_MAC_CFG1"                         , 0x00000003, 0x00000001, 0x00000001},
    {"VOE_IP_CFG"                           , 0x00000004, 0x00000001, 0x00000001},
    {"VOE_IP_CFG1"                          , 0x00000005, 0x00000001, 0x00000001},
    {"VOE_IP_CFG2"                          , 0x00000006, 0x00000001, 0x00000001},
    {"VOE_IP_CFG3"                          , 0x00000007, 0x00000001, 0x00000001},
    {"PEER_IP_SESSION_CFG"                  , 0x00000008, 0x00000003, 0x00000001},
    {"PEER_IP_SESSION_CFG1"                 , 0x0000000b, 0x00000003, 0x00000001},
    {"PEER_IP_SESSION_CFG2"                 , 0x0000000e, 0x00000003, 0x00000001},
    {"PEER_IP_SESSION_CFG3"                 , 0x00000011, 0x00000003, 0x00000001},
    {"UDP_SESSION_CFG"                      , 0x00000014, 0x00000003, 0x00000001},
    {"TCP_CFG"                              , 0x00000017, 0x00000001, 0x00000001},
    {"TWAMP_CFG"                            , 0x00000018, 0x00000001, 0x00000001},
    {"TWAMP_SESSION_CFG"                    , 0x00000019, 0x00000003, 0x00000001},
    {"LOOPBACK_SESSION_CFG"                 , 0x0000001c, 0x00000003, 0x00000001},
    {"LOOPBACK_SESSION_CFG1"                , 0x0000001f, 0x00000003, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_L3_VOE_STAT_L3[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TCP_RX_CNT"                           , 0x00000000, 0x00000001, 0x00000001},
    {"TCP_TX_CNT"                           , 0x00000001, 0x00000001, 0x00000001},
    {"UDP_SESSION_RX_CNT"                   , 0x00000002, 0x00000003, 0x00000001},
    {"UDP_SESSION_TX_CNT"                   , 0x00000005, 0x00000003, 0x00000001},
    {"INTR_STICKY_L3"                       , 0x00000008, 0x00000001, 0x00000001},
    {"INTR_ENA_L3"                          , 0x00000009, 0x00000001, 0x00000001},
    {"EXTRACT_L3"                           , 0x0000000a, 0x00000001, 0x00000001},
    {"INTR_STICKY_SESSION_L3"               , 0x0000000b, 0x00000003, 0x00000001},
    {"INTR_ENA_SESSION_L3"                  , 0x0000000e, 0x00000003, 0x00000001},
    {"EXTRACT_SESSION_L3"                   , 0x00000011, 0x00000003, 0x00000001},
    {"TWAMP_RX_SEQ_NUM"                     , 0x00000014, 0x00000003, 0x00000001},
    {"TWAMP_TX_SEQ_NUM"                     , 0x00000017, 0x00000003, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_VOP_L3[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"VOE_CONF_L3"                          , 0x00000000, 0x00000040, 0x00000040, regs_within_VOP_L3_VOE_CONF_L3},
    {"VOE_STAT_L3"                          , 0x00001000, 0x00000040, 0x00000020, regs_within_VOP_L3_VOE_STAT_L3},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_VOP_MRP_VOE_CONF_MRP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VOE_COMMON_CFG"                       , 0x00000000, 0x00000001, 0x00000001},
    {"MRP_CTRL"                             , 0x00000001, 0x00000001, 0x00000001},
    {"MRP_FWD_CTRL"                         , 0x00000002, 0x00000001, 0x00000001},
    {"RING_MASK_CFG"                        , 0x00000003, 0x00000001, 0x00000001},
    {"ICON_MASK_CFG"                        , 0x00000004, 0x00000001, 0x00000001},
    {"TST_FWD_CTRL"                         , 0x00000005, 0x00000001, 0x00000001},
    {"TST_CFG"                              , 0x00000006, 0x00000001, 0x00000001},
    {"TST_PRIO_CFG"                         , 0x00000007, 0x00000001, 0x00000001},
    {"ITST_FWD_CTRL"                        , 0x00000008, 0x00000001, 0x00000001},
    {"ITST_CFG"                             , 0x00000009, 0x00000001, 0x00000001},
    {"MRP_MAC_LSB"                          , 0x0000000a, 0x00000001, 0x00000001},
    {"MRP_MAC_MSB"                          , 0x0000000b, 0x00000001, 0x00000001},
    {"BEST_MAC_LSB"                         , 0x0000000c, 0x00000001, 0x00000001},
    {"BEST_MAC_MSB"                         , 0x0000000d, 0x00000001, 0x00000001},
    {"MRP_TX_CFG"                           , 0x0000000e, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_MRP_VOE_STAT_MRP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TST_RX_CNT"                           , 0x00000000, 0x00000001, 0x00000001},
    {"TST_DELTA_TS"                         , 0x00000001, 0x00000001, 0x00000001},
    {"TST_STAT"                             , 0x00000002, 0x00000001, 0x00000001},
    {"NXT_LOC_HMO"                          , 0x00000003, 0x00000001, 0x00000001},
    {"TST_PRIO_STAT"                        , 0x00000004, 0x00000001, 0x00000001},
    {"ITST_STAT"                            , 0x00000005, 0x00000001, 0x00000001},
    {"ITST_NXT_LOC_HMO"                     , 0x00000006, 0x00000001, 0x00000001},
    {"ITST_RX_CNT"                          , 0x00000007, 0x00000001, 0x00000001},
    {"ITST_DELTA_TS"                        , 0x00000008, 0x00000001, 0x00000001},
    {"MRP_RX_SEQ"                           , 0x00000009, 0x00000002, 0x00000001},
    {"MRP_TX_SEQ"                           , 0x0000000b, 0x00000002, 0x00000001},
    {"MRP_STICKY"                           , 0x0000000d, 0x00000001, 0x00000001},
    {"MRP_INTR_ENA"                         , 0x0000000e, 0x00000001, 0x00000001},
    {"TST_RX_LOC_CNT"                       , 0x0000000f, 0x00000001, 0x00000001},
    {"ITST_RX_LOC_CNT"                      , 0x00000010, 0x00000001, 0x00000001},
    {"TST_RX_TS"                            , 0x00000011, 0x00000001, 0x00000001},
    {"TST_TX_TS"                            , 0x00000012, 0x00000001, 0x00000001},
    {"ITST_RX_TS"                           , 0x00000013, 0x00000001, 0x00000001},
    {"ITST_TX_TS"                           , 0x00000014, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_VOP_MRP[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"VOE_CONF_MRP"                         , 0x00000800, 0x00000040, 0x00000010, regs_within_VOP_MRP_VOE_CONF_MRP},
    {"VOE_STAT_MRP"                         , 0x00000000, 0x00000040, 0x00000020, regs_within_VOP_MRP_VOE_STAT_MRP},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_VOP_DLR_VOE_CONF_DLR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VOE_COMMON_CFG"                       , 0x00000000, 0x00000001, 0x00000001},
    {"DLR_CTRL"                             , 0x00000001, 0x00000001, 0x00000001},
    {"DLR_FWD_CTRL"                         , 0x00000002, 0x00000001, 0x00000001},
    {"DLR_MASK_CFG"                         , 0x00000003, 0x00000001, 0x00000001},
    {"BCN_FWD_CTRL"                         , 0x00000004, 0x00000001, 0x00000001},
    {"BCN_CFG"                              , 0x00000005, 0x00000001, 0x00000001},
    {"ADV_FWD_CTRL"                         , 0x00000006, 0x00000001, 0x00000001},
    {"ADV_CFG"                              , 0x00000007, 0x00000001, 0x00000001},
    {"DLR_PREC_CFG"                         , 0x00000008, 0x00000001, 0x00000001},
    {"DLR_MAC_LSB"                          , 0x00000009, 0x00000001, 0x00000001},
    {"DLR_MAC_MSB"                          , 0x0000000a, 0x00000001, 0x00000001},
    {"GW_MAC_LSB"                           , 0x0000000b, 0x00000001, 0x00000001},
    {"GW_MAC_MSB"                           , 0x0000000c, 0x00000001, 0x00000001},
    {"DLR_TX_CFG"                           , 0x0000000d, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_DLR_VOE_STAT_DLR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DLR_RX_SEQ"                           , 0x00000000, 0x00000002, 0x00000001},
    {"DLR_TX_SEQ"                           , 0x00000002, 0x00000002, 0x00000001},
    {"BCN_STAT"                             , 0x00000004, 0x00000001, 0x00000001},
    {"BCN_FAULT_HMO"                        , 0x00000005, 0x00000001, 0x00000001},
    {"BCN_LOC_HMO"                          , 0x00000006, 0x00000001, 0x00000001},
    {"BCN_RX_CNT"                           , 0x00000007, 0x00000001, 0x00000001},
    {"BCN_RX_LOC_CNT"                       , 0x00000008, 0x00000001, 0x00000001},
    {"ADV_STAT"                             , 0x00000009, 0x00000001, 0x00000001},
    {"ADV_LOC_HMO"                          , 0x0000000a, 0x00000001, 0x00000001},
    {"ADV_RX_CNT"                           , 0x0000000b, 0x00000001, 0x00000001},
    {"ADV_RX_LOC_CNT"                       , 0x0000000c, 0x00000001, 0x00000001},
    {"DLR_STICKY"                           , 0x0000000d, 0x00000001, 0x00000001},
    {"DLR_INTR_ENA"                         , 0x0000000e, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_VOP_DLR[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"VOE_CONF_DLR"                         , 0x00000000, 0x00000040, 0x00000010, regs_within_VOP_DLR_VOE_CONF_DLR},
    {"VOE_STAT_DLR"                         , 0x00000400, 0x00000040, 0x00000010, regs_within_VOP_DLR_VOE_STAT_DLR},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_VOP_MPLS_VOE_CONF_MPLS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VOE_COMMON_CFG"                       , 0x00000000, 0x00000001, 0x00000001},
    {"CPU_COPY_CTRL_MPLS"                   , 0x00000001, 0x00000001, 0x00000001},
    {"OAM_HW_CTRL_MPLS"                     , 0x00000002, 0x00000001, 0x00000001},
    {"OAM_CNT_SEL_MPLS"                     , 0x00000003, 0x00000001, 0x00000001},
    {"OAM_CNT_DATA_MPLS"                    , 0x00000004, 0x00000001, 0x00000001},
    {"BFD_CONFIG"                           , 0x00000005, 0x00000001, 0x00000001},
    {"BFD_LOCAL_DISCR_SRC"                  , 0x00000006, 0x00000001, 0x00000001},
    {"BFD_REMOTE_DISCR_SRC"                 , 0x00000007, 0x00000001, 0x00000001},
    {"BFD_LOCAL_DISCR_SINK"                 , 0x00000008, 0x00000001, 0x00000001},
    {"BFD_REMOTE_DISCR_SINK"                , 0x00000009, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_MPLS_VOE_STAT_MPLS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RX_CNT_SEL_OAM_MPLS"                  , 0x00000000, 0x00000001, 0x00000001},
    {"RX_CNT_NON_SEL_OAM_MPLS"              , 0x00000001, 0x00000001, 0x00000001},
    {"TX_CNT_SEL_OAM_MPLS"                  , 0x00000002, 0x00000001, 0x00000001},
    {"TX_CNT_NON_SEL_OAM_MPLS"              , 0x00000003, 0x00000001, 0x00000001},
    {"BFD_SRC_INFO"                         , 0x00000004, 0x00000001, 0x00000001},
    {"BFD_SINK_INFO"                        , 0x00000005, 0x00000001, 0x00000001},
    {"BFD_STAT"                             , 0x00000006, 0x00000001, 0x00000001},
    {"BFD_RX_LAST"                          , 0x00000007, 0x00000001, 0x00000001},
    {"INTR_STICKY_MPLS"                     , 0x00000008, 0x00000001, 0x00000001},
    {"INTR_ENA_MPLS"                        , 0x00000009, 0x00000001, 0x00000001},
    {"CPT_RX_STICKY_MPLS"                   , 0x0000000a, 0x00000001, 0x00000001},
    {"PDU_EXTRACT_MPLS"                     , 0x0000000b, 0x00000001, 0x00000001},
    {"BFD_RX_STICKY"                        , 0x0000000c, 0x00000001, 0x00000001},
    {"BFD_TX_STICKY"                        , 0x0000000d, 0x00000001, 0x00000001},
    {"BFD_CC_TX_CNT_REG"                    , 0x0000000e, 0x00000001, 0x00000001},
    {"BFD_CV_TX_CNT_REG"                    , 0x0000000f, 0x00000001, 0x00000001},
    {"BFD_CC_RX_VLD_CNT_REG"                , 0x00000010, 0x00000001, 0x00000001},
    {"BFD_CV_RX_VLD_CNT_REG"                , 0x00000011, 0x00000001, 0x00000001},
    {"BFD_CC_RX_INVLD_CNT_REG"              , 0x00000012, 0x00000001, 0x00000001},
    {"BFD_CV_RX_INVLD_CNT_REG"              , 0x00000013, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_VOP_MPLS[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"VOE_CONF_MPLS"                        , 0x00000800, 0x00000040, 0x00000010, regs_within_VOP_MPLS_VOE_CONF_MPLS},
    {"VOE_STAT_MPLS"                        , 0x00000000, 0x00000040, 0x00000020, regs_within_VOP_MPLS_VOE_STAT_MPLS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_XQS_SYSTEM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STAT_CNT_CFG"                         , 0x00000000, 0x00000001, 0x00000001},
    {"MAP_CFG_CFG"                          , 0x00000001, 0x00000001, 0x00000001},
    {"FWD_CTRL"                             , 0x00000002, 0x00000001, 0x00000001},
    {"FWD_DROP_EVENTS"                      , 0x00000003, 0x00000025, 0x00000001},
    {"FWD_STAT_CNT"                         , 0x00000049, 0x00000005, 0x00000001},
    {"FWD_CPU_DROP_CNT"                     , 0x0000004e, 0x00000001, 0x00000001},
    {"FWD_CT_CFG"                           , 0x0000004f, 0x00000020, 0x00000001},
    {"QMAP_PORT_MODE"                       , 0x00000090, 0x00000025, 0x00000001},
    {"QMAP_EACL"                            , 0x000000d6, 0x00000001, 0x00000001},
    {"STAT_CFG"                             , 0x000000d7, 0x00000001, 0x00000001},
    {"MIRROR_CFG"                           , 0x000000d8, 0x00000001, 0x00000001},
    {"CPUQ_DISCARD"                         , 0x000000d9, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_XQS_QMAP_VPORT_TBL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"QMAP_VPORT_TBL"                       , 0x00000000, 0x00000025, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_XQS_QMAP_SE_TBL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"QMAP_SE_TBL"                          , 0x00000000, 0x00000001, 0x00000001},
    {"QMAP_CT_ESP"                          , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_XQS_QMAP_QOS_TBL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"QMAP_QOS_TBL"                         , 0x00000000, 0x00000001, 0x00000001},
    {"QMAP_QOS_SIZE"                        , 0x00000001, 0x00000001, 0x00000001},
    {"DROP_STAT_CTRL"                       , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_XQS_QLIMIT_QUEUE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"QUEUE_SIZE"                           , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_XQS_QLIMIT_SE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"QLIMIT_SE_CFG"                        , 0x00000000, 0x00000001, 0x00000001},
    {"QLIMIT_SE_USE"                        , 0x00000001, 0x00000005, 0x00000001},
    {"QLIMIT_CONG_CNT"                      , 0x0000000a, 0x00000005, 0x00000001},
    {"QLIMIT_SE_SHR"                        , 0x00000013, 0x00000005, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_XQS_QLIMIT_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"QLIMIT_PORT_CFG"                      , 0x00000000, 0x00000025, 0x00000001},
    {"QLIMIT_DP_CFG"                        , 0x00000046, 0x00000004, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_XQS_QLIMIT_SHR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"QLIMIT_SHR_TOP_CFG"                   , 0x00000000, 0x00000001, 0x00000001},
    {"QLIMIT_SHR_ATOP_CFG"                  , 0x00000001, 0x00000001, 0x00000001},
    {"QLIMIT_SHR_CTOP_CFG"                  , 0x00000002, 0x00000001, 0x00000001},
    {"QLIMIT_SHR_QLIM_CFG"                  , 0x00000003, 0x00000001, 0x00000001},
    {"QLIMIT_SHR_QDIV_CFG"                  , 0x00000004, 0x00000001, 0x00000001},
    {"QLIMIT_QUE_CONG_CFG"                  , 0x00000005, 0x00000001, 0x00000001},
    {"QLIMIT_SE_CONG_CFG"                   , 0x00000006, 0x00000001, 0x00000001},
    {"QLIMIT_SHR_QDIVMAX_CFG"               , 0x00000007, 0x00000001, 0x00000001},
    {"QLIMIT_SE_EIR_CFG"                    , 0x00000008, 0x00000001, 0x00000001},
    {"QLIMIT_CONG_CNT_STAT"                 , 0x00000009, 0x00000001, 0x00000001},
    {"QLIMIT_SHR_FILL_STAT"                 , 0x0000000a, 0x00000001, 0x00000001},
    {"QLIMIT_SHR_WM_STAT"                   , 0x0000000b, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_XQS_QLIMIT_MON[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"QLIMIT_MON_CFG"                       , 0x00000000, 0x00000001, 0x00000001},
    {"QLIMIT_CONG_CNT_MAX_STAT"             , 0x00000001, 0x00000001, 0x00000001},
    {"QLIMIT_SHR_FILL_MAX_STAT"             , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_XQS_STAT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CNT"                                  , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_XQS[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"SYSTEM"                               , 0x0000059c, 0x00000001, 0x000000da, regs_within_XQS_SYSTEM},
    {"QMAP_VPORT_TBL"                       , 0x00000400, 0x00000004, 0x00000040, regs_within_XQS_QMAP_VPORT_TBL},
    {"QMAP_SE_TBL"                          , 0x00000590, 0x00000004, 0x00000002, regs_within_XQS_QMAP_SE_TBL},
    {"QMAP_QOS_TBL"                         , 0x00000580, 0x00000004, 0x00000004, regs_within_XQS_QMAP_QOS_TBL},
    {"QLIMIT_QUEUE"                         , 0x00000598, 0x00000004, 0x00000001, regs_within_XQS_QLIMIT_QUEUE},
    {"QLIMIT_SE"                            , 0x00000500, 0x00000004, 0x00000020, regs_within_XQS_QLIMIT_SE},
    {"QLIMIT_CFG"                           , 0x00000676, 0x00000001, 0x0000004a, regs_within_XQS_QLIMIT_CFG},
    {"QLIMIT_SHR"                           , 0x000006c0, 0x00000004, 0x0000000c, regs_within_XQS_QLIMIT_SHR},
    {"QLIMIT_MON"                           , 0x000006f0, 0x00000004, 0x00000003, regs_within_XQS_QLIMIT_MON},
    {"STAT"                                 , 0x00000000, 0x00000400, 0x00000001, regs_within_XQS_STAT},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_target_t vtss_symreg_targets[] = {
    //target name         , repl, tgt_id    , base_addr                  , register group list
    {"AFI"                ,   -1, 0x00000090, VTSS_IO_OFFSET1(0x00240000), reggrps_within_AFI},
    {"ANA_AC"             ,   -1, 0x00000240, VTSS_IO_OFFSET1(0x00900000), reggrps_within_ANA_AC},
    {"ANA_AC_OAM_MOD"     ,   -1, 0x0000001c, VTSS_IO_OFFSET1(0x00070000), reggrps_within_ANA_AC_OAM_MOD},
    {"ANA_AC_POL"         ,   -1, 0x00000080, VTSS_IO_OFFSET1(0x00200000), reggrps_within_ANA_AC_POL},
    {"ANA_AC_SDLB"        ,   -1, 0x00000140, VTSS_IO_OFFSET1(0x00500000), reggrps_within_ANA_AC_SDLB},
    {"ANA_ACL"            ,   -1, 0x00000014, VTSS_IO_OFFSET1(0x00050000), reggrps_within_ANA_ACL},
    {"ANA_CL"             ,   -1, 0x00000100, VTSS_IO_OFFSET1(0x00400000), reggrps_within_ANA_CL},
    {"ANA_L2"             ,   -1, 0x00000200, VTSS_IO_OFFSET1(0x00800000), reggrps_within_ANA_L2},
    {"ANA_L3"             ,   -1, 0x00000120, VTSS_IO_OFFSET1(0x00480000), reggrps_within_ANA_L3},
    {"ASM"                ,   -1, 0x00000480, VTSS_IO_OFFSET1(0x01200000), reggrps_within_ASM},
    {"DEV2G5"             ,    1, 0x00000404, VTSS_IO_OFFSET1(0x01010000), reggrps_within_DEV1G},
    {"DEV2G5"             ,    3, 0x00000408, VTSS_IO_OFFSET1(0x01020000), reggrps_within_DEV1G},
    {"DEV2G5"             ,    5, 0x0000040c, VTSS_IO_OFFSET1(0x01030000), reggrps_within_DEV1G},
    {"DEV2G5"             ,    7, 0x00000410, VTSS_IO_OFFSET1(0x01040000), reggrps_within_DEV1G},
    {"DEV2G5"             ,    9, 0x00000414, VTSS_IO_OFFSET1(0x01050000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   11, 0x00000418, VTSS_IO_OFFSET1(0x01060000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   13, 0x0000041c, VTSS_IO_OFFSET1(0x01070000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   15, 0x00000420, VTSS_IO_OFFSET1(0x01080000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   17, 0x00000424, VTSS_IO_OFFSET1(0x01090000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   19, 0x00000428, VTSS_IO_OFFSET1(0x010a0000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   21, 0x0000042c, VTSS_IO_OFFSET1(0x010b0000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   23, 0x00000430, VTSS_IO_OFFSET1(0x010c0000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   25, 0x00000434, VTSS_IO_OFFSET1(0x010d0000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   27, 0x00000438, VTSS_IO_OFFSET1(0x010e0000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   29, 0x0000043c, VTSS_IO_OFFSET1(0x010f0000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   31, 0x00000440, VTSS_IO_OFFSET1(0x01100000), reggrps_within_DEV1G},
    {"DEV2G5"             ,    0, 0x00000401, VTSS_IO_OFFSET1(0x01004000), reggrps_within_DEV1G},
    {"DEV2G5"             ,    2, 0x00000405, VTSS_IO_OFFSET1(0x01014000), reggrps_within_DEV1G},
    {"DEV2G5"             ,    4, 0x00000409, VTSS_IO_OFFSET1(0x01024000), reggrps_within_DEV1G},
    {"DEV2G5"             ,    6, 0x0000040d, VTSS_IO_OFFSET1(0x01034000), reggrps_within_DEV1G},
    {"DEV2G5"             ,    8, 0x00000411, VTSS_IO_OFFSET1(0x01044000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   10, 0x00000415, VTSS_IO_OFFSET1(0x01054000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   12, 0x00000419, VTSS_IO_OFFSET1(0x01064000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   14, 0x0000041d, VTSS_IO_OFFSET1(0x01074000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   16, 0x00000421, VTSS_IO_OFFSET1(0x01084000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   18, 0x00000425, VTSS_IO_OFFSET1(0x01094000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   20, 0x00000429, VTSS_IO_OFFSET1(0x010a4000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   22, 0x0000042d, VTSS_IO_OFFSET1(0x010b4000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   24, 0x00000431, VTSS_IO_OFFSET1(0x010c4000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   26, 0x00000435, VTSS_IO_OFFSET1(0x010d4000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   28, 0x00000439, VTSS_IO_OFFSET1(0x010e4000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   30, 0x0000043d, VTSS_IO_OFFSET1(0x010f4000), reggrps_within_DEV1G},
    {"DEV10G"             ,    0, 0x00000402, VTSS_IO_OFFSET1(0x01008000), reggrps_within_DEV10G},
    {"DEV10G"             ,    1, 0x00000406, VTSS_IO_OFFSET1(0x01018000), reggrps_within_DEV10G},
    {"DEV10G"             ,    2, 0x0000040a, VTSS_IO_OFFSET1(0x01028000), reggrps_within_DEV10G},
    {"DEV10G"             ,    3, 0x0000040e, VTSS_IO_OFFSET1(0x01038000), reggrps_within_DEV10G},
    {"DEV10G"             ,    4, 0x00000412, VTSS_IO_OFFSET1(0x01048000), reggrps_within_DEV10G},
    {"DEV10G"             ,    5, 0x00000416, VTSS_IO_OFFSET1(0x01058000), reggrps_within_DEV10G},
    {"DEV10G"             ,    6, 0x0000041a, VTSS_IO_OFFSET1(0x01068000), reggrps_within_DEV10G},
    {"DEV10G"             ,    7, 0x0000041e, VTSS_IO_OFFSET1(0x01078000), reggrps_within_DEV10G},
    {"DEV10G"             ,    8, 0x00000422, VTSS_IO_OFFSET1(0x01088000), reggrps_within_DEV10G},
    {"DEV10G"             ,    9, 0x00000426, VTSS_IO_OFFSET1(0x01098000), reggrps_within_DEV10G},
    {"DEV10G"             ,   10, 0x0000042a, VTSS_IO_OFFSET1(0x010a8000), reggrps_within_DEV10G},
    {"DEV10G"             ,   11, 0x0000042e, VTSS_IO_OFFSET1(0x010b8000), reggrps_within_DEV10G},
    {"DEV10G"             ,   12, 0x00000432, VTSS_IO_OFFSET1(0x010c8000), reggrps_within_DEV10G},
    {"DEV10G"             ,   13, 0x00000436, VTSS_IO_OFFSET1(0x010d8000), reggrps_within_DEV10G},
    {"DEV10G"             ,   14, 0x0000043a, VTSS_IO_OFFSET1(0x010e8000), reggrps_within_DEV10G},
    {"DEV10G"             ,   15, 0x0000043e, VTSS_IO_OFFSET1(0x010f8000), reggrps_within_DEV10G},
    {"PCS10G_BR"          ,    0, 0x00000403, VTSS_IO_OFFSET1(0x0100c000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,    1, 0x00000407, VTSS_IO_OFFSET1(0x0101c000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,    2, 0x0000040b, VTSS_IO_OFFSET1(0x0102c000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,    3, 0x0000040f, VTSS_IO_OFFSET1(0x0103c000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,    4, 0x00000413, VTSS_IO_OFFSET1(0x0104c000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,    5, 0x00000417, VTSS_IO_OFFSET1(0x0105c000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,    6, 0x0000041b, VTSS_IO_OFFSET1(0x0106c000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,    7, 0x0000041f, VTSS_IO_OFFSET1(0x0107c000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,    8, 0x00000423, VTSS_IO_OFFSET1(0x0108c000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,    9, 0x00000427, VTSS_IO_OFFSET1(0x0109c000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,   10, 0x0000042b, VTSS_IO_OFFSET1(0x010ac000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,   11, 0x0000042f, VTSS_IO_OFFSET1(0x010bc000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,   12, 0x00000433, VTSS_IO_OFFSET1(0x010cc000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,   13, 0x00000437, VTSS_IO_OFFSET1(0x010dc000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,   14, 0x0000043b, VTSS_IO_OFFSET1(0x010ec000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,   15, 0x0000043f, VTSS_IO_OFFSET1(0x010fc000), reggrps_within_PCS_10GBASE_R},
    {"DEVCPU_GCB"         ,   -1, 0x00000004, VTSS_IO_OFFSET1(0x00010000), reggrps_within_DEVCPU_GCB},
    {"PTP"                ,   -1, 0x00000010, VTSS_IO_OFFSET1(0x00040000), reggrps_within_PTP},
    {"DSM"                ,   -1, 0x00000441, VTSS_IO_OFFSET1(0x01104000), reggrps_within_DSM},
    {"EACL"               ,   -1, 0x000000b0, VTSS_IO_OFFSET1(0x002c0000), reggrps_within_EACL},
    {"HSCH"               ,   -1, 0x00000160, VTSS_IO_OFFSET1(0x00580000), reggrps_within_HSCH},
    {"LRN"                ,   -1, 0x00000018, VTSS_IO_OFFSET1(0x00060000), reggrps_within_LRN},
    {"PORT_CONF"          ,   -1, 0x00000442, VTSS_IO_OFFSET1(0x01108000), reggrps_within_PORT_CONF},
    {"QFWD"               ,   -1, 0x0000002c, VTSS_IO_OFFSET1(0x000b0000), reggrps_within_QFWD},
    {"QRES"               ,   -1, 0x000000a0, VTSS_IO_OFFSET1(0x00280000), reggrps_within_QRES},
    {"QSYS"               ,   -1, 0x00000028, VTSS_IO_OFFSET1(0x000a0000), reggrps_within_QSYS},
    {"REW"                ,   -1, 0x00000180, VTSS_IO_OFFSET1(0x00600000), reggrps_within_REW},
    {"VCAP_ES0"           ,   -1, 0x00000038, VTSS_IO_OFFSET1(0x000e0000), reggrps_within_VCAP_ES0},
    {"VCAP_ES2"           ,   -1, 0x00000034, VTSS_IO_OFFSET1(0x000d0000), reggrps_within_VCAP_ES2},
    {"VCAP_IP6PFX"        ,   -1, 0x00000024, VTSS_IO_OFFSET1(0x00090000), reggrps_within_VCAP_IP6PFX},
    {"VCAP_SUPER"         ,   -1, 0x00000020, VTSS_IO_OFFSET1(0x00080000), reggrps_within_VCAP_SUPER},
    {"VOP"                ,   -1, 0x00000280, VTSS_IO_OFFSET1(0x00a00000), reggrps_within_VOP},
    {"VOP_L3"             ,   -1, 0x000002c0, VTSS_IO_OFFSET1(0x00b00000), reggrps_within_VOP_L3},
    {"VOP_MRP"            ,   -1, 0x000001c0, VTSS_IO_OFFSET1(0x00700000), reggrps_within_VOP_MRP},
    {"VOP_DLR"            ,   -1, 0x000001e0, VTSS_IO_OFFSET1(0x00780000), reggrps_within_VOP_DLR},
    {"VOP_MPLS"           ,   -1, 0x000001a0, VTSS_IO_OFFSET1(0x00680000), reggrps_within_VOP_MPLS},
    {"XQS"                ,   -1, 0x00000030, VTSS_IO_OFFSET1(0x000c0000), reggrps_within_XQS},
};

#define SYMREG_REPL_CNT_MAX 5120
#define SYMREG_NAME_LEN_MAX 32
vtss_rc vtss_symreg_data_get(const vtss_inst_t inst, vtss_symreg_data_t *const data) {
    data->targets = vtss_symreg_targets;
    data->targets_cnt = sizeof(vtss_symreg_targets) / sizeof(vtss_symreg_targets[0]);
    data->io_origin1_offset = VTSS_IO_ORIGIN1_OFFSET;
    data->repl_cnt_max = SYMREG_REPL_CNT_MAX;
    data->name_len_max = SYMREG_NAME_LEN_MAX;
    return VTSS_RC_OK;
}

#else /* VTSS_OPT_SYMREG */
vtss_rc vtss_symreg_data_get(const vtss_inst_t inst, vtss_symreg_data_t *const data) {
    return VTSS_RC_ERROR;
}
#endif /* VTSS_OPT_SYMREG */
#endif /* VTSS_ARCH_LAIKA */
