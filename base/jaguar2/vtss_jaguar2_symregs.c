// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "vtss_api.h"

#if defined(VTSS_ARCH_JAGUAR_2_B) && !defined(VTSS_ARCH_SERVAL_T)
#ifdef VTSS_OPT_SYMREG
/*
 * Target offset base(s)
 */
#define VTSS_IO_ORIGIN1_OFFSET 0x70000000
#define VTSS_IO_ORIGIN1_SIZE   0x00200000
#define VTSS_IO_ORIGIN2_OFFSET 0x71000000
#define VTSS_IO_ORIGIN2_SIZE   0x01000000
#ifndef VTSS_IO_OFFSET1
#define VTSS_IO_OFFSET1(offset) (VTSS_IO_ORIGIN1_OFFSET + offset)
#endif
#ifndef VTSS_IO_OFFSET2
#define VTSS_IO_OFFSET2(offset) (VTSS_IO_ORIGIN2_OFFSET + offset)
#endif

static const vtss_symreg_reg_t regs_within_AFI_MISC[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"NEW_FRM_CTRL"                         , 0x00000000, 0x00000001, 0x00000001},
  {"NEW_FRM_INFO"                         , 0x00000001, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"ERR"                                  , 0x00000002, 0x00000001, 0x00000001},
#endif
  {"WARN"                                 , 0x00000003, 0x00000001, 0x00000001},
  {"STICKY_INFO"                          , 0x00000004, 0x00000001, 0x00000001},
  {"STICKY_INFO_ENA"                      , 0x00000005, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_AFI_FRM_TBL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"FRM_NEXT_AND_TYPE"                    , 0x00000000, 0x00000001, 0x00000001},
  {"FRM_ENTRY_PART0"                      , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_AFI_DTI_TBL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"DTI_MODE"                             , 0x00000000, 0x00000001, 0x00000001},
  {"DTI_PORT_QU"                          , 0x00000001, 0x00000001, 0x00000001},
  {"DTI_FRM"                              , 0x00000002, 0x00000001, 0x00000001},
  {"DTI_CNT"                              , 0x00000003, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_AFI_DTI_MISC[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"DTI_FC_CNT_DOWN"                      , 0x00000000, 0x00000001, 0x00000001},
#endif
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
#ifndef VTSS_RELEASE
  {"TTI_TICK_STATE"                       , 0x00000003, 0x00000008, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_AFI_TTI_MISC[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TTI_CAL_SLOT_PTRS"                    , 0x00000000, 0x00000004, 0x00000001},
  {"TTI_CAL_SLOT_CNT"                     , 0x00000004, 0x00000004, 0x00000001},
#ifndef VTSS_RELEASE
  {"TTI_CAL_STATE"                        , 0x00000008, 0x00000004, 0x00000001},
#endif
  {"TTI_CTRL"                             , 0x0000000c, 0x00000001, 0x00000001},
  {"TTI_INJ_CNT"                          , 0x0000000d, 0x00000001, 0x00000001},
  {"TTI_RAND_STATE"                       , 0x0000000e, 0x00000001, 0x00000001},
  {"TTI_PORT_FRM_OUT"                     , 0x0000000f, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_AFI_PORT_TBL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"PORT_FRM_OUT"                         , 0x00000000, 0x00000001, 0x00000001},
#endif
  {"PORT_CFG"                             , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_AFI[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"MISC"                                 , 0x0000a0f2, 0x00000001, 0x00000006, regs_within_AFI_MISC},
  {"FRM_TBL"                              , 0x00008000, 0x00001000, 0x00000002, regs_within_AFI_FRM_TBL},
  {"DTI_TBL"                              , 0x0000a000, 0x00000020, 0x00000004, regs_within_AFI_DTI_TBL},
  {"DTI_MISC"                             , 0x0000a0f8, 0x00000020, 0x00000003, regs_within_AFI_DTI_MISC},
  {"TTI_TBL"                              , 0x00000000, 0x00001000, 0x00000008, regs_within_AFI_TTI_TBL},
  {"TTI_TICKS"                            , 0x0000a158, 0x00000001, 0x0000000b, regs_within_AFI_TTI_TICKS},
  {"TTI_MISC"                             , 0x0000a163, 0x00000001, 0x00000010, regs_within_AFI_TTI_MISC},
  {"PORT_TBL"                             , 0x0000a080, 0x00000039, 0x00000002, regs_within_AFI_PORT_TBL},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_RAM_CTRL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"RAM_INIT"                             , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_ANA_AC_COREMEM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CM_ADDR"                              , 0x00000000, 0x00000001, 0x00000001},
  {"CM_DATA"                              , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_ANA_AC_PS_COMMON[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MISC_CTRL"                            , 0x00000000, 0x00000001, 0x00000001},
  {"PS_COMMON_CFG"                        , 0x00000001, 0x00000001, 0x00000001},
  {"SFLOW_CFG"                            , 0x00000002, 0x00000001, 0x00000001},
  {"SFLOW_RESET_CTRL"                     , 0x00000003, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"PHYS_SRC_AGGR_CFG"                    , 0x00000004, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PHYS_SRC_AGGR_CFG1"                   , 0x00000005, 0x00000001, 0x00000001},
#endif
  {"STACK_CFG"                            , 0x00000006, 0x00000001, 0x00000001},
  {"STACK_CFG1"                           , 0x00000007, 0x00000001, 0x00000001},
  {"STACK_A_CFG"                          , 0x00000008, 0x00000001, 0x00000001},
  {"STACK_A_CFG1"                         , 0x00000009, 0x00000001, 0x00000001},
  {"COMMON_VSTAX_CFG"                     , 0x0000000a, 0x00000001, 0x00000001},
  {"COMMON_EQUAL_STACK_LINK_TTL_CFG"      , 0x0000000b, 0x00000001, 0x00000001},
  {"VSTAX_CTRL"                           , 0x0000000c, 0x00000035, 0x00000001},
  {"VSTAX_GMIRROR_CFG"                    , 0x00000041, 0x00000001, 0x00000001},
  {"VSTAX_GMIRROR_CFG1"                   , 0x00000042, 0x00000001, 0x00000001},
  {"CPU_CFG"                              , 0x00000043, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"PS_DBG_CTRL"                          , 0x00000044, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_MIRROR_PROBE[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PROBE_CFG"                            , 0x00000000, 0x00000001, 0x00000001},
  {"PROBE_PORT_CFG"                       , 0x00000001, 0x00000001, 0x00000001},
  {"PROBE_PORT_CFG1"                      , 0x00000002, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_AGGR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"AGGR_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
  {"AGGR_CFG1"                            , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_SRC[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SRC_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
  {"SRC_CFG1"                             , 0x00000001, 0x00000001, 0x00000001},
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
  {"UPSID_CFG1"                           , 0x00000002, 0x00000001, 0x00000001},
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
  {"PGID_CFG1"                            , 0x00000001, 0x00000001, 0x00000001},
  {"PGID_MISC_CFG"                        , 0x00000002, 0x00000001, 0x00000001},
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
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_GLOBAL_CFG_PORT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"STAT_GLOBAL_EVENT_MASK"               , 0x00000000, 0x00000008, 0x00000001},
  {"STAT_RESET"                           , 0x00000008, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_CNT_CFG_PORT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"STAT_EVENTS_STICKY"                   , 0x00000000, 0x00000001, 0x00000001},
  {"STAT_CFG"                             , 0x00000001, 0x00000008, 0x00000001},
  {"STAT_LSB_CNT"                         , 0x00000009, 0x00000008, 0x00000001},
  {"STAT_MSB_CNT"                         , 0x00000011, 0x00000008, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_GLOBAL_CFG_ACL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"GLOBAL_CNT_FRM_TYPE_CFG"              , 0x00000000, 0x00000002, 0x00000001},
#endif
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
#ifndef VTSS_RELEASE
  {"GLOBAL_CNT_FRM_TYPE_CFG"              , 0x00000000, 0x00000002, 0x00000001},
#endif
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
#ifndef VTSS_RELEASE
  {"GLOBAL_CNT_FRM_TYPE_CFG"              , 0x00000000, 0x00000006, 0x00000001},
#endif
  {"STAT_GLOBAL_CFG"                      , 0x00000006, 0x00000006, 0x00000001},
  {"STAT_GLOBAL_EVENT_MASK"               , 0x0000000c, 0x00000006, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_CNT_CFG_ISDX[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"STAT_LSB_CNT"                         , 0x00000000, 0x00000006, 0x00000001},
  {"STAT_MSB_CNT"                         , 0x00000006, 0x00000003, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_STAT_GLOBAL_CFG_IRLEG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"GLOBAL_CNT_FRM_TYPE_CFG"              , 0x00000000, 0x00000008, 0x00000001},
#endif
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
#ifndef VTSS_RELEASE
  {"GLOBAL_CNT_FRM_TYPE_CFG"              , 0x00000000, 0x00000008, 0x00000001},
#endif
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
  {"RAM_CTRL"                             , 0x000210d6, 0x00000001, 0x00000001, regs_within_ANA_AC_RAM_CTRL},
#ifndef VTSS_RELEASE
  {"COREMEM"                              , 0x000210d4, 0x00000001, 0x00000002, regs_within_ANA_AC_COREMEM},
#endif
  {"PS_COMMON"                            , 0x0002136a, 0x00000001, 0x00000045, regs_within_ANA_AC_PS_COMMON},
  {"MIRROR_PROBE"                         , 0x000211e0, 0x00000003, 0x00000008, regs_within_ANA_AC_MIRROR_PROBE},
  {"AGGR"                                 , 0x000210e0, 0x00000010, 0x00000002, regs_within_ANA_AC_AGGR},
  {"SRC"                                  , 0x00021100, 0x00000059, 0x00000002, regs_within_ANA_AC_SRC},
  {"SFLOW"                                , 0x00021300, 0x00000035, 0x00000002, regs_within_ANA_AC_SFLOW},
  {"UPSID"                                , 0x00021200, 0x00000020, 0x00000004, regs_within_ANA_AC_UPSID},
  {"GLAG"                                 , 0x000211c0, 0x00000020, 0x00000001, regs_within_ANA_AC_GLAG},
  {"PGID"                                 , 0x00020000, 0x00000435, 0x00000004, regs_within_ANA_AC_PGID},
  {"PS_STICKY"                            , 0x000210d7, 0x00000001, 0x00000001, regs_within_ANA_AC_PS_STICKY},
  {"PS_STICKY_MASK"                       , 0x000213af, 0x00000004, 0x00000010, regs_within_ANA_AC_PS_STICKY_MASK},
  {"STAT_GLOBAL_CFG_PORT"                 , 0x000211b2, 0x00000001, 0x00000009, regs_within_ANA_AC_STAT_GLOBAL_CFG_PORT},
  {"STAT_CNT_CFG_PORT"                    , 0x00021800, 0x00000039, 0x00000020, regs_within_ANA_AC_STAT_CNT_CFG_PORT},
  {"STAT_GLOBAL_CFG_ACL"                  , 0x000210d8, 0x00000001, 0x00000006, regs_within_ANA_AC_STAT_GLOBAL_CFG_ACL},
  {"STAT_CNT_CFG_ACL"                     , 0x00021280, 0x00000020, 0x00000004, regs_within_ANA_AC_STAT_CNT_CFG_ACL},
  {"STAT_GLOBAL_CFG_QUEUE"                , 0x000211f8, 0x00000001, 0x00000006, regs_within_ANA_AC_STAT_GLOBAL_CFG_QUEUE},
  {"STAT_CNT_CFG_QUEUE"                   , 0x00024000, 0x000001c8, 0x00000004, regs_within_ANA_AC_STAT_CNT_CFG_QUEUE},
  {"STAT_GLOBAL_CFG_ISDX"                 , 0x000213ef, 0x00000001, 0x00000012, regs_within_ANA_AC_STAT_GLOBAL_CFG_ISDX},
  {"STAT_CNT_CFG_ISDX"                    , 0x00000000, 0x00002000, 0x00000010, regs_within_ANA_AC_STAT_CNT_CFG_ISDX},
  {"STAT_GLOBAL_CFG_IRLEG"                , 0x00021401, 0x00000001, 0x00000018, regs_within_ANA_AC_STAT_GLOBAL_CFG_IRLEG},
  {"STAT_CNT_CFG_IRLEG"                   , 0x00022000, 0x00000100, 0x00000010, regs_within_ANA_AC_STAT_CNT_CFG_IRLEG},
  {"STAT_GLOBAL_CFG_ERLEG"                , 0x00021419, 0x00000001, 0x00000018, regs_within_ANA_AC_STAT_GLOBAL_CFG_ERLEG},
  {"STAT_CNT_CFG_ERLEG"                   , 0x00023000, 0x00000100, 0x00000010, regs_within_ANA_AC_STAT_CNT_CFG_ERLEG},
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
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TEMP_CNT_REG"                         , 0x00000000, 0x00000001, 0x00000001},
  {"LM_CNT_FRAME"                         , 0x00000001, 0x00000001, 0x00000001},
  {"CCM_LM_INFO_REG"                      , 0x00000002, 0x00000001, 0x00000001},
  {"CCM_LM_TX_B_REG"                      , 0x00000003, 0x00000001, 0x00000001},
  {"CCM_LM_RX_B_REG"                      , 0x00000004, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_ANA_AC_OAM_MOD_PDU_MOD_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"DM_PTP_DOMAIN_CFG"                    , 0x00000000, 0x00000035, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_ANA_AC_OAM_MOD[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"VOE_SRV_LM_CNT"                       , 0x00000000, 0x00002000, 0x00000001, regs_within_ANA_AC_OAM_MOD_VOE_SRV_LM_CNT},
  {"VOE_PORT_LM_CNT"                      , 0x00002400, 0x000001a8, 0x00000001, regs_within_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT},
#ifndef VTSS_RELEASE
  {"OAM_PDU_MOD_CONT"                     , 0x00002000, 0x0000006e, 0x00000008, regs_within_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT},
#endif
  {"PDU_MOD_CFG"                          , 0x00002370, 0x00000001, 0x00000035, regs_within_ANA_AC_OAM_MOD_PDU_MOD_CFG},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_POL_POL_ALL_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"POL_STORM_RATE_CFG"                   , 0x00000000, 0x00000008, 0x00000001},
  {"POL_STORM_THRES_CFG"                  , 0x00000008, 0x00000008, 0x00000001},
  {"POL_STORM_CTRL"                       , 0x00000010, 0x00000008, 0x00000001},
  {"POL_ACL_RATE_CFG"                     , 0x00000018, 0x00000020, 0x00000001},
  {"POL_ACL_THRES_CFG"                    , 0x00000038, 0x00000020, 0x00000001},
  {"POL_ACL_CTRL"                         , 0x00000058, 0x00000020, 0x00000001},
  {"POL_PORT_FC_CFG"                      , 0x00000078, 0x00000039, 0x00000001},
  {"POL_ALL_CFG"                          , 0x000000b1, 0x00000001, 0x00000001},
  {"POL_STICKY"                           , 0x000000b2, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_POL_POL_PORT_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"POL_PORT_THRES_CFG_0"                 , 0x00000000, 0x000000e4, 0x00000001},
  {"POL_PORT_THRES_CFG_1"                 , 0x00000100, 0x000000e4, 0x00000001},
  {"POL_PORT_RATE_CFG"                    , 0x00000200, 0x000000e4, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_POL_POL_PORT_CTRL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"POL_PORT_GAP"                         , 0x00000000, 0x00000001, 0x00000001},
  {"POL_PORT_CFG"                         , 0x00000001, 0x00000004, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_POL_POL_PRIO_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"POL_PRIO_RATE_CFG"                    , 0x00000000, 0x000001c8, 0x00000001},
  {"POL_PRIO_THRES_CFG"                   , 0x00000200, 0x000001c8, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_POL_POL_PRIO_CTRL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"POL_PRIO_GAP"                         , 0x00000000, 0x00000001, 0x00000001},
  {"POL_PRIO_CFG"                         , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_POL_PORT_PT_CTRL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"ACTION_CTRL"                          , 0x00000000, 0x00000005, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_POL_COMMON_SDLB[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"DLB_CTRL"                             , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"BURST_CTRL"                           , 0x00000001, 0x00000001, 0x00000001},
#endif
  {"DLB_STICKY"                           , 0x00000002, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_POL_SDLB[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"DLB_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
  {"LB_CFG"                               , 0x00000001, 0x00000002, 0x00000001},
#ifndef VTSS_RELEASE
  {"LB_BUCKET_VAL"                        , 0x00000003, 0x00000002, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_ANA_AC_POL[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"POL_ALL_CFG"                          , 0x00008fc8, 0x00000001, 0x000000b3, regs_within_ANA_AC_POL_POL_ALL_CFG},
  {"POL_PORT_CFG"                         , 0x00008000, 0x00000001, 0x00000400, regs_within_ANA_AC_POL_POL_PORT_CFG},
  {"POL_PORT_CTRL"                        , 0x00008e00, 0x00000039, 0x00000008, regs_within_ANA_AC_POL_POL_PORT_CTRL},
  {"POL_PRIO_CFG"                         , 0x00008400, 0x00000001, 0x00000400, regs_within_ANA_AC_POL_POL_PRIO_CFG},
  {"POL_PRIO_CTRL"                        , 0x00008800, 0x000001c8, 0x00000002, regs_within_ANA_AC_POL_POL_PRIO_CTRL},
  {"PORT_PT_CTRL"                         , 0x00008c00, 0x00000040, 0x00000008, regs_within_ANA_AC_POL_PORT_PT_CTRL},
  {"COMMON_SDLB"                          , 0x00008b90, 0x00000001, 0x00000003, regs_within_ANA_AC_POL_COMMON_SDLB},
  {"SDLB"                                 , 0x00000000, 0x00001000, 0x00000008, regs_within_ANA_AC_POL_SDLB},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_ANA_ACL_PORT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"VCAP_S2_KEY_SEL"                      , 0x00000000, 0x00000002, 0x00000001},
  {"PTP_CFG"                              , 0x00000002, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_ACL_VCAP_S2[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"VCAP_S2_CFG"                          , 0x00000000, 0x00000039, 0x00000001},
  {"SWAP_SIP"                             , 0x00000039, 0x00000020, 0x00000001},
  {"PTP_MISC_CTRL"                        , 0x00000059, 0x00000001, 0x00000001},
  {"SWAP_IP_CTRL"                         , 0x0000005a, 0x00000001, 0x00000001},
  {"VCAP_S2_MISC_CTRL"                    , 0x0000005b, 0x00000001, 0x00000001},
  {"VCAP_S2_RNG_CTRL"                     , 0x0000005c, 0x00000008, 0x00000001},
  {"VCAP_S2_RNG_VALUE_CFG"                , 0x00000064, 0x00000008, 0x00000001},
  {"VCAP_S2_RNG_OFFSET_CFG"               , 0x0000006c, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_ACL_STICKY[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SEC_LOOKUP_STICKY"                    , 0x00000000, 0x00000002, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_ACL_CNT_TBL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CNT"                                  , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_ACL_PTP_DOM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PTP_CLOCK_ID_MSB"                     , 0x00000000, 0x00000001, 0x00000001},
  {"PTP_CLOCK_ID_LSB"                     , 0x00000001, 0x00000001, 0x00000001},
  {"PTP_SRC_PORT_CFG"                     , 0x00000002, 0x00000001, 0x00000001},
  {"PTP_MISC_CFG"                         , 0x00000003, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_ANA_ACL[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"PORT"                                 , 0x00001000, 0x00000039, 0x00000003, regs_within_ANA_ACL_PORT},
  {"VCAP_S2"                              , 0x000010ab, 0x00000001, 0x0000006d, regs_within_ANA_ACL_VCAP_S2},
  {"STICKY"                               , 0x00001118, 0x00000001, 0x00000002, regs_within_ANA_ACL_STICKY},
  {"CNT_TBL"                              , 0x00000000, 0x00001000, 0x00000001, regs_within_ANA_ACL_CNT_TBL},
  {"PTP_DOM"                              , 0x0000111a, 0x00000003, 0x00000004, regs_within_ANA_ACL_PTP_DOM},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_ANA_CL_PORT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"FILTER_CTRL"                          , 0x00000000, 0x00000001, 0x00000001},
  {"VLAN_FILTER_CTRL"                     , 0x00000001, 0x00000003, 0x00000001},
  {"STACKING_CTRL"                        , 0x00000004, 0x00000001, 0x00000001},
  {"VLAN_TPID_CTRL"                       , 0x00000005, 0x00000001, 0x00000001},
  {"VLAN_CTRL"                            , 0x00000006, 0x00000001, 0x00000001},
  {"PCP_DEI_TRANS_CFG"                    , 0x00000007, 0x00000010, 0x00000001},
  {"PORT_ID_CFG"                          , 0x00000017, 0x00000001, 0x00000001},
  {"PCP_DEI_MAP_CFG"                      , 0x00000018, 0x00000010, 0x00000001},
  {"QOS_CFG"                              , 0x00000028, 0x00000001, 0x00000001},
  {"CAPTURE_CFG"                          , 0x00000029, 0x00000001, 0x00000001},
  {"CAPTURE_Y1731_AG_CFG"                 , 0x0000002a, 0x00000001, 0x00000001},
  {"CAPTURE_GXRP_CFG"                     , 0x0000002b, 0x00000001, 0x00000001},
  {"CAPTURE_BPDU_CFG"                     , 0x0000002c, 0x00000001, 0x00000001},
  {"ADV_CL_CFG"                           , 0x0000002d, 0x00000006, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_CL_COMMON[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"UPSID_CFG"                            , 0x00000000, 0x00000001, 0x00000001},
  {"AGGR_CFG"                             , 0x00000001, 0x00000001, 0x00000001},
  {"VLAN_STAG_CFG"                        , 0x00000002, 0x00000003, 0x00000001},
  {"CPU_PROTO_QU_CFG"                     , 0x00000005, 0x00000001, 0x00000001},
  {"CPU_8021_QU_CFG"                      , 0x00000006, 0x00000010, 0x00000001},
  {"CPU_8021_QOS_CFG"                     , 0x00000016, 0x00000010, 0x00000001},
  {"VRAP_CFG"                             , 0x00000026, 0x00000001, 0x00000001},
  {"VRAP_HDR_DATA"                        , 0x00000027, 0x00000001, 0x00000001},
  {"VRAP_HDR_MASK"                        , 0x00000028, 0x00000001, 0x00000001},
  {"ADV_RNG_CTRL"                         , 0x00000029, 0x00000008, 0x00000001},
  {"ADV_RNG_VALUE_CFG"                    , 0x00000031, 0x00000008, 0x00000001},
#ifndef VTSS_RELEASE
  {"COMMON_VSTAX_CFG"                     , 0x00000039, 0x00000001, 0x00000001},
#endif
  {"CLM_MISC_CTRL"                        , 0x0000003a, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"HM_CFG"                               , 0x0000003b, 0x00000004, 0x00000001},
#endif
  {"DSCP_CFG"                             , 0x0000003f, 0x00000040, 0x00000001},
  {"QOS_MAP_CFG"                          , 0x0000007f, 0x00000020, 0x00000001},
  {"MPLS_RSV_LBL_CFG"                     , 0x0000009f, 0x00000010, 0x00000001},
  {"MPLS_MISC_CFG"                        , 0x000000af, 0x00000001, 0x00000001},
  {"MPLS_CFG"                             , 0x000000b0, 0x00000001, 0x00000001},
  {"OAM_CFG"                              , 0x000000b1, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_CL_MIP_TBL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MIP_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
  {"LBM_MAC_HIGH"                         , 0x00000001, 0x00000001, 0x00000001},
  {"LBM_MAC_LOW"                          , 0x00000002, 0x00000001, 0x00000001},
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
  {"VSI_CFG"                              , 0x00000001, 0x00000001, 0x00000001},
  {"OAM_MEP_CFG"                          , 0x00000002, 0x00000001, 0x00000001},
  {"IPT"                                  , 0x00000003, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_CL_PPT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PP_CFG"                               , 0x00000000, 0x00000010, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_CL_STICKY[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"FILTER_STICKY"                        , 0x00000000, 0x00000001, 0x00000001},
  {"VLAN_FILTER_STICKY"                   , 0x00000001, 0x00000003, 0x00000001},
  {"CLASS_STICKY"                         , 0x00000004, 0x00000001, 0x00000001},
  {"CAT_STICKY"                           , 0x00000005, 0x00000001, 0x00000001},
  {"ADV_CL_MPLS_STICKY"                   , 0x00000006, 0x00000001, 0x00000001},
  {"ADV_CL_STICKY"                        , 0x00000007, 0x00000001, 0x00000001},
  {"MIP_STICKY"                           , 0x00000008, 0x00000001, 0x00000001},
  {"IP_HDR_CHK_STICKY"                    , 0x00000009, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_CL_STICKY_MASK[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"FILTER_STICKY_MASK"                   , 0x00000000, 0x00000001, 0x00000001},
  {"VLAN_FILTER_STICKY_MASK"              , 0x00000001, 0x00000003, 0x00000001},
  {"CLASS_STICKY_MASK"                    , 0x00000004, 0x00000001, 0x00000001},
  {"CAT_STICKY_MASK"                      , 0x00000005, 0x00000001, 0x00000001},
  {"ADV_CL_MPLS_STICKY_MASK"              , 0x00000006, 0x00000001, 0x00000001},
  {"ADV_CL_STICKY_MASK"                   , 0x00000007, 0x00000001, 0x00000001},
  {"MIP_STICKY_MASK"                      , 0x00000008, 0x00000001, 0x00000001},
  {"IP_HDR_CHK_STICKY_MASK"               , 0x00000009, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_ANA_CL[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"PORT"                                 , 0x00008000, 0x00000039, 0x00000040, regs_within_ANA_CL_PORT},
  {"COMMON"                               , 0x00007ea0, 0x00000001, 0x000000b2, regs_within_ANA_CL_COMMON},
  {"MIP_TBL"                              , 0x00006000, 0x00000400, 0x00000004, regs_within_ANA_CL_MIP_TBL},
  {"L2CP_TBL"                             , 0x00007000, 0x00000ea0, 0x00000001, regs_within_ANA_CL_L2CP_TBL},
  {"MAP_TBL"                              , 0x00004000, 0x00000200, 0x00000010, regs_within_ANA_CL_MAP_TBL},
  {"IPT"                                  , 0x00000000, 0x00001000, 0x00000004, regs_within_ANA_CL_IPT},
  {"PPT"                                  , 0x00007f52, 0x00000001, 0x00000010, regs_within_ANA_CL_PPT},
  {"STICKY"                               , 0x00007f62, 0x00000001, 0x0000000a, regs_within_ANA_CL_STICKY},
  {"STICKY_MASK"                          , 0x00007f6c, 0x00000004, 0x0000000a, regs_within_ANA_CL_STICKY_MASK},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_ANA_L2_COMMON[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"FWD_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
  {"LRN_CFG"                              , 0x00000001, 0x00000001, 0x00000001},
  {"FILTER_OTHER_CTRL"                    , 0x00000002, 0x00000001, 0x00000001},
  {"FILTER_LOCAL_CTRL"                    , 0x00000003, 0x00000001, 0x00000001},
  {"FILTER_LOCAL_CTRL1"                   , 0x00000004, 0x00000001, 0x00000001},
  {"AUTO_LRN_CFG"                         , 0x00000005, 0x00000001, 0x00000001},
  {"AUTO_LRN_CFG1"                        , 0x00000006, 0x00000001, 0x00000001},
  {"LRN_SECUR_CFG"                        , 0x00000007, 0x00000001, 0x00000001},
  {"LRN_SECUR_CFG1"                       , 0x00000008, 0x00000001, 0x00000001},
  {"LRN_SECUR_LOCKED_CFG"                 , 0x00000009, 0x00000001, 0x00000001},
  {"LRN_SECUR_LOCKED_CFG1"                , 0x0000000a, 0x00000001, 0x00000001},
  {"LRN_COPY_CFG"                         , 0x0000000b, 0x00000001, 0x00000001},
  {"LRN_COPY_CFG1"                        , 0x0000000c, 0x00000001, 0x00000001},
  {"PORT_DLB_CFG"                         , 0x0000000d, 0x00000035, 0x00000001},
  {"SCAN_FID_CTRL"                        , 0x00000042, 0x00000001, 0x00000001},
  {"SCAN_FID_CFG"                         , 0x00000043, 0x00000010, 0x00000001},
  {"MOVELOG_STICKY"                       , 0x00000053, 0x00000001, 0x00000001},
  {"MOVELOG_STICKY1"                      , 0x00000054, 0x00000001, 0x00000001},
  {"VSTAX_CTRL"                           , 0x00000055, 0x00000001, 0x00000001},
  {"INTR"                                 , 0x00000056, 0x00000001, 0x00000001},
  {"INTR_ENA"                             , 0x00000057, 0x00000001, 0x00000001},
  {"INTR_IDENT"                           , 0x00000058, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L2_LRN_LIMIT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"FID_LIMIT_STATUS"                     , 0x00000000, 0x00000001, 0x00000001},
  {"FID_LIMIT_CTRL"                       , 0x00000001, 0x00000001, 0x00000001},
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
  {"PORT_MASK_CFG"                        , 0x00000000, 0x00000001, 0x00000001},
  {"PORT_MASK_CFG1"                       , 0x00000001, 0x00000001, 0x00000001},
  {"SERVICE_CTRL"                         , 0x00000002, 0x00000001, 0x00000001},
  {"DLB_CFG"                              , 0x00000003, 0x00000001, 0x00000001},
  {"DLB_COS_CFG"                          , 0x00000004, 0x00000008, 0x00000001},
  {"ISDX_BASE_CFG"                        , 0x0000000c, 0x00000001, 0x00000001},
  {"ISDX_COS_CFG"                         , 0x0000000d, 0x00000008, 0x00000001},
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
static const vtss_symreg_reggrp_t reggrps_within_ANA_L2[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"COMMON"                               , 0x000228aa, 0x00000001, 0x00000059, regs_within_ANA_L2_COMMON},
  {"LRN_LIMIT"                            , 0x00020000, 0x00001400, 0x00000002, regs_within_ANA_L2_LRN_LIMIT},
  {"PORT_LIMIT"                           , 0x00022800, 0x00000055, 0x00000002, regs_within_ANA_L2_PORT_LIMIT},
  {"ISDX"                                 , 0x00000000, 0x00001000, 0x00000020, regs_within_ANA_L2_ISDX},
  {"STICKY"                               , 0x00022903, 0x00000001, 0x00000001, regs_within_ANA_L2_STICKY},
  {"STICKY_MASK"                          , 0x00022904, 0x00000004, 0x00000001, regs_within_ANA_L2_STICKY_MASK},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_ANA_L3_COMMON[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"MISC_CTRL"                            , 0x00000000, 0x00000001, 0x00000001},
#endif
  {"VLAN_CTRL"                            , 0x00000001, 0x00000001, 0x00000001},
  {"L3_UC_ENA"                            , 0x00000002, 0x00000001, 0x00000001},
  {"L3_UC_ENA1"                           , 0x00000003, 0x00000001, 0x00000001},
  {"L3_MC_ENA"                            , 0x00000004, 0x00000001, 0x00000001},
  {"L3_MC_ENA1"                           , 0x00000005, 0x00000001, 0x00000001},
  {"PORT_FWD_CTRL"                        , 0x00000006, 0x00000001, 0x00000001},
  {"PORT_FWD_CTRL1"                       , 0x00000007, 0x00000001, 0x00000001},
  {"PORT_LRN_CTRL"                        , 0x00000008, 0x00000001, 0x00000001},
  {"PORT_LRN_CTRL1"                       , 0x00000009, 0x00000001, 0x00000001},
  {"VLAN_FILTER_CTRL"                     , 0x0000000a, 0x00000001, 0x00000001},
  {"VLAN_FILTER_CTRL1"                    , 0x0000000b, 0x00000001, 0x00000001},
  {"VLAN_ISOLATED_CFG"                    , 0x0000000c, 0x00000001, 0x00000001},
  {"VLAN_ISOLATED_CFG1"                   , 0x0000000d, 0x00000001, 0x00000001},
  {"VLAN_COMMUNITY_CFG"                   , 0x0000000e, 0x00000001, 0x00000001},
  {"VLAN_COMMUNITY_CFG1"                  , 0x0000000f, 0x00000001, 0x00000001},
  {"ROUTING_CFG"                          , 0x00000010, 0x00000001, 0x00000001},
  {"RLEG_CFG_0"                           , 0x00000011, 0x00000001, 0x00000001},
  {"RLEG_CFG_1"                           , 0x00000012, 0x00000001, 0x00000001},
  {"CPU_QU_CFG"                           , 0x00000013, 0x00000001, 0x00000001},
  {"VRRP_IP4_CFG_0"                       , 0x00000014, 0x00000001, 0x00000001},
  {"VRRP_IP4_CFG_1"                       , 0x00000015, 0x00000001, 0x00000001},
  {"VRRP_IP6_CFG_0"                       , 0x00000016, 0x00000001, 0x00000001},
  {"VRRP_IP6_CFG_1"                       , 0x00000017, 0x00000001, 0x00000001},
  {"SIP_SECURE_ENA"                       , 0x00000018, 0x00000001, 0x00000001},
  {"SIP_SECURE_ENA1"                      , 0x00000019, 0x00000001, 0x00000001},
  {"DIP_SECURE_ENA"                       , 0x0000001a, 0x00000001, 0x00000001},
  {"DIP_SECURE_ENA1"                      , 0x0000001b, 0x00000001, 0x00000001},
  {"SIP_RPF_ENA"                          , 0x0000001c, 0x00000001, 0x00000001},
  {"SIP_RPF_ENA1"                         , 0x0000001d, 0x00000001, 0x00000001},
  {"SERVICE_CFG"                          , 0x0000001e, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L3_TUPE[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TUPE_MISC"                            , 0x00000000, 0x00000001, 0x00000001},
  {"TUPE_ADDR"                            , 0x00000001, 0x00000001, 0x00000001},
  {"TUPE_CMD_PORT_MASK_CLR"               , 0x00000002, 0x00000001, 0x00000001},
  {"TUPE_CMD_PORT_MASK_CLR1"              , 0x00000003, 0x00000001, 0x00000001},
  {"TUPE_CMD_PORT_MASK_SET"               , 0x00000004, 0x00000001, 0x00000001},
  {"TUPE_CMD_PORT_MASK_SET1"              , 0x00000005, 0x00000001, 0x00000001},
  {"TUPE_CTRL_VAL"                        , 0x00000006, 0x00000001, 0x00000001},
  {"TUPE_CTRL_VAL_MASK"                   , 0x00000007, 0x00000001, 0x00000001},
  {"TUPE_CTRL_BIT_MASK"                   , 0x00000008, 0x00000001, 0x00000001},
  {"TUPE_PORT_MASK_A"                     , 0x00000009, 0x00000001, 0x00000001},
  {"TUPE_PORT_MASK_A1"                    , 0x0000000a, 0x00000001, 0x00000001},
  {"TUPE_PORT_MASK_B"                     , 0x0000000b, 0x00000001, 0x00000001},
  {"TUPE_PORT_MASK_B1"                    , 0x0000000c, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L3_VLAN[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"VMID_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
  {"VLAN_CFG"                             , 0x00000001, 0x00000001, 0x00000001},
  {"TUPE_CTRL"                            , 0x00000002, 0x00000001, 0x00000001},
  {"VLAN_MASK_CFG"                        , 0x00000003, 0x00000001, 0x00000001},
  {"VLAN_MASK_CFG1"                       , 0x00000004, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L3_MSTP[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MSTP_FWD_CFG"                         , 0x00000000, 0x00000001, 0x00000001},
  {"MSTP_FWD_CFG1"                        , 0x00000001, 0x00000001, 0x00000001},
  {"MSTP_LRN_CFG"                         , 0x00000002, 0x00000001, 0x00000001},
  {"MSTP_LRN_CFG1"                        , 0x00000003, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L3_VMID[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"RLEG_CTRL"                            , 0x00000000, 0x00000001, 0x00000001},
  {"VRRP_CFG"                             , 0x00000001, 0x00000002, 0x00000001},
  {"VMID_MC"                              , 0x00000003, 0x00000001, 0x00000001},
  {"SIP_RPF"                              , 0x00000004, 0x00000001, 0x00000001},
  {"MAX_LEN"                              , 0x00000005, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L3_ARP[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"ARP_CFG_0"                            , 0x00000000, 0x00000001, 0x00000001},
  {"ARP_CFG_1"                            , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_L3_L3MC[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"EVMID_MASK_CFG"                       , 0x00000000, 0x00000004, 0x00000001},
  {"L3MC_CTRL"                            , 0x00000004, 0x00000001, 0x00000001},
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
  {"COMMON"                               , 0x0000d508, 0x00000001, 0x0000001f, regs_within_ANA_L3_COMMON},
  {"TUPE"                                 , 0x0000d527, 0x00000001, 0x0000000d, regs_within_ANA_L3_TUPE},
  {"VLAN"                                 , 0x00000000, 0x00001400, 0x00000008, regs_within_ANA_L3_VLAN},
  {"MSTP"                                 , 0x0000d400, 0x00000042, 0x00000004, regs_within_ANA_L3_MSTP},
  {"VMID"                                 , 0x0000d000, 0x00000080, 0x00000008, regs_within_ANA_L3_VMID},
  {"ARP"                                  , 0x0000c000, 0x00000800, 0x00000002, regs_within_ANA_L3_ARP},
  {"L3MC"                                 , 0x0000a000, 0x00000400, 0x00000008, regs_within_ANA_L3_L3MC},
  {"LPM_REMAP_STICKY"                     , 0x0000d534, 0x00000001, 0x00000001, regs_within_ANA_L3_LPM_REMAP_STICKY},
  {"VLAN_ARP_L3MC_STICKY"                 , 0x0000d535, 0x00000001, 0x00000002, regs_within_ANA_L3_VLAN_ARP_L3MC_STICKY},
  {"L3_STICKY_MASK"                       , 0x0000d537, 0x00000004, 0x00000004, regs_within_ANA_L3_L3_STICKY_MASK},
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
  {"TX_MULTI_COLL_CNT"                    , 0x0000002a, 0x00000001, 0x00000001},
  {"TX_LATE_COLL_CNT"                     , 0x0000002b, 0x00000001, 0x00000001},
  {"TX_XCOLL_CNT"                         , 0x0000002c, 0x00000001, 0x00000001},
  {"TX_DEFER_CNT"                         , 0x0000002d, 0x00000001, 0x00000001},
  {"TX_XDEFER_CNT"                        , 0x0000002e, 0x00000001, 0x00000001},
  {"TX_BACKOFF1_CNT"                      , 0x0000002f, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"TX_CSENSE_CNT"                        , 0x00000030, 0x00000001, 0x00000001},
#endif
  {"RX_IN_BYTES_MSB_CNT"                  , 0x00000031, 0x00000001, 0x00000001},
  {"RX_OK_BYTES_MSB_CNT"                  , 0x00000032, 0x00000001, 0x00000001},
  {"RX_BAD_BYTES_MSB_CNT"                 , 0x00000033, 0x00000001, 0x00000001},
  {"TX_OUT_BYTES_MSB_CNT"                 , 0x00000034, 0x00000001, 0x00000001},
  {"TX_OK_BYTES_MSB_CNT"                  , 0x00000035, 0x00000001, 0x00000001},
  {"RX_SYNC_LOST_ERR_CNT"                 , 0x00000036, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ASM_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"STAT_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
  {"MAC_ADDR_HIGH_CFG"                    , 0x00000001, 0x00000037, 0x00000001},
  {"MAC_ADDR_LOW_CFG"                     , 0x00000038, 0x00000037, 0x00000001},
  {"PORT_CFG"                             , 0x0000006f, 0x00000037, 0x00000001},
#ifndef VTSS_RELEASE
  {"CPU_FC_CFG"                           , 0x000000a6, 0x00000001, 0x00000001},
#endif
  {"PAUSE_CFG"                            , 0x000000a7, 0x00000037, 0x00000001},
  {"INJ_VLAN_CFG"                         , 0x000000de, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_ASM_DBG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"DBG_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
  {"ERR_STICKY"                           , 0x00000001, 0x00000009, 0x00000001},
  {"PRE_CNT_OFLW_STICKY"                  , 0x0000000a, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_ASM_PORT_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PORT_STICKY"                          , 0x00000000, 0x00000037, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ASM_PFC[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PFC_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"PFC_TIMER"                            , 0x00000001, 0x00000008, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ASM_LBK_WM_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"VD_FC_WM"                             , 0x00000000, 0x00000002, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ASM_LBK_MISC_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"LBK_AGING_DIS"                        , 0x00000000, 0x00000002, 0x00000001},
#endif
  {"LBK_FIFO_CFG"                         , 0x00000002, 0x00000003, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ASM_LBK_STAT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"LBK_OVFLW_STICKY"                     , 0x00000000, 0x00000002, 0x00000001},
  {"LBK_AGING_STICKY"                     , 0x00000002, 0x00000002, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ASM_RAM_CTRL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"RAM_INIT"                             , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_ASM_COREMEM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CM_ADDR"                              , 0x00000000, 0x00000001, 0x00000001},
  {"CM_DATA"                              , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reggrp_t reggrps_within_ASM[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"DEV_STATISTICS"                       , 0x00000000, 0x00000035, 0x00000040, regs_within_ASM_DEV_STATISTICS},
  {"CFG"                                  , 0x00000d42, 0x00000001, 0x000000df, regs_within_ASM_CFG},
#ifndef VTSS_RELEASE
  {"DBG"                                  , 0x00000e21, 0x00000001, 0x0000000b, regs_within_ASM_DBG},
#endif
  {"PORT_STATUS"                          , 0x00000e2c, 0x00000001, 0x00000037, regs_within_ASM_PORT_STATUS},
  {"PFC"                                  , 0x00001000, 0x00000037, 0x00000010, regs_within_ASM_PFC},
  {"LBK_WM_CFG"                           , 0x00000e63, 0x00000001, 0x00000002, regs_within_ASM_LBK_WM_CFG},
  {"LBK_MISC_CFG"                         , 0x00000e65, 0x00000001, 0x00000005, regs_within_ASM_LBK_MISC_CFG},
  {"LBK_STAT"                             , 0x00000e6a, 0x00000001, 0x00000004, regs_within_ASM_LBK_STAT},
  {"RAM_CTRL"                             , 0x00000e6e, 0x00000001, 0x00000001, regs_within_ASM_RAM_CTRL},
#ifndef VTSS_RELEASE
  {"COREMEM"                              , 0x00000d40, 0x00000001, 0x00000002, regs_within_ASM_COREMEM},
#endif
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV1G_DEV_CFG_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"DEV_RST_CTRL"                         , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"DEV_STICKY"                           , 0x00000001, 0x00000001, 0x00000001},
#endif
  {"DEV_DBG_CFG"                          , 0x00000002, 0x00000001, 0x00000001},
  {"DEV_PORT_PROTECT"                     , 0x00000003, 0x00000001, 0x00000001},
  {"EEE_CFG"                              , 0x00000004, 0x00000001, 0x00000001},
  {"PTP_CFG"                              , 0x00000005, 0x00000001, 0x00000001},
  {"PTP_EVENTS"                           , 0x00000006, 0x00000001, 0x00000001},
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
#ifndef VTSS_RELEASE
  {"PCS1G_DBG_CFG"                        , 0x00000006, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PCS1G_CDET_CFG"                       , 0x00000007, 0x00000001, 0x00000001},
#endif
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
static const vtss_symreg_reg_t regs_within_DEV1G_DEV1G_INTR_CFG_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"DEV1G_INTR_CFG"                       , 0x00000000, 0x00000001, 0x00000001},
  {"DEV1G_INTR"                           , 0x00000001, 0x00000001, 0x00000001},
  {"DEV1G_INTR_IDENT"                     , 0x00000002, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV1G[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"DEV_CFG_STATUS"                       , 0x00000000, 0x00000001, 0x00000007, regs_within_DEV1G_DEV_CFG_STATUS},
  {"MAC_CFG_STATUS"                       , 0x00000007, 0x00000001, 0x00000009, regs_within_DEV1G_MAC_CFG_STATUS},
  {"PCS1G_CFG_STATUS"                     , 0x00000010, 0x00000001, 0x00000011, regs_within_DEV1G_PCS1G_CFG_STATUS},
  {"PCS1G_TSTPAT_CFG_STATUS"              , 0x00000021, 0x00000001, 0x00000002, regs_within_DEV1G_PCS1G_TSTPAT_CFG_STATUS},
  {"PCS_FX100_CONFIGURATION"              , 0x00000023, 0x00000001, 0x00000001, regs_within_DEV1G_PCS_FX100_CONFIGURATION},
  {"PCS_FX100_STATUS"                     , 0x00000024, 0x00000001, 0x00000001, regs_within_DEV1G_PCS_FX100_STATUS},
  {"DEV1G_INTR_CFG_STATUS"                , 0x00000025, 0x00000001, 0x00000003, regs_within_DEV1G_DEV1G_INTR_CFG_STATUS},
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
#ifndef VTSS_RELEASE
  {"MAC_RX_LANE_STICKY_0"                 , 0x0000000a, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"MAC_RX_LANE_STICKY_1"                 , 0x0000000b, 0x00000001, 0x00000001},
#endif
  {"MAC_TX_MONITOR_STICKY"                , 0x0000000c, 0x00000001, 0x00000001},
  {"MAC_STICKY"                           , 0x0000000d, 0x00000001, 0x00000001},
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
  {"RX_HIH_CKSM_ERR_CNT"                  , 0x00000025, 0x00000001, 0x00000001},
  {"RX_XGMII_PROT_ERR_CNT"                , 0x00000026, 0x00000001, 0x00000001},
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
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV10G_PCS_XAUI_CONFIGURATION[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PCS_XAUI_CFG"                         , 0x00000000, 0x00000001, 0x00000001},
  {"PCS_XAUI_EXT_CFG"                     , 0x00000001, 0x00000001, 0x00000001},
  {"PCS_XAUI_SD_CFG"                      , 0x00000002, 0x00000001, 0x00000001},
  {"PCS_XAUI_TX_SEQ_CFG"                  , 0x00000003, 0x00000001, 0x00000001},
  {"PCS_XAUI_RX_ERR_CNT_CFG"              , 0x00000004, 0x00000001, 0x00000001},
  {"PCS_XAUI_INTERLEAVE_MODE_CFG"         , 0x00000005, 0x00000001, 0x00000001},
  {"PCS_XAUI_LPI_CFG"                     , 0x00000006, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV10G_PCS_XAUI_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PCS_XAUI_RX_STATUS"                   , 0x00000000, 0x00000001, 0x00000001},
  {"PCS_XAUI_DESKEW_STATUS"               , 0x00000001, 0x00000001, 0x00000001},
  {"PCS_XAUI_CGALIGN_STATUS"              , 0x00000002, 0x00000001, 0x00000001},
  {"PCS_XAUI_RX_ERROR_STATUS"             , 0x00000003, 0x00000001, 0x00000001},
  {"PCS_XAUI_RX_SEQ_REC_STATUS"           , 0x00000004, 0x00000001, 0x00000001},
  {"PCS_XAUI_RX_FIFO_OF_ERR_L0_CNT_STATUS", 0x00000005, 0x00000001, 0x00000001},
  {"PCS_XAUI_RX_FIFO_UF_ERR_L1_CNT_STATUS", 0x00000006, 0x00000001, 0x00000001},
  {"PCS_XAUI_RX_FIFO_D_ERR_L2_CNT_STATUS" , 0x00000007, 0x00000001, 0x00000001},
  {"PCS_XAUI_RX_FIFO_CG_ERR_L3_CNT_STATUS", 0x00000008, 0x00000001, 0x00000001},
  {"PCS_XAUI_LPI_STATUS"                  , 0x00000009, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV10G_PCS_XAUI_TSTPAT_CONFIGURATION[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PCS_XAUI_TSTPAT_CFG"                  , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV10G_PCS_XAUI_TSTPAT_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PCS_XAUI_TSTPAT_RX_SEQ_CNT_STATUS"    , 0x00000000, 0x00000001, 0x00000001},
  {"PCS_XAUI_TSTPAT_TX_SEQ_CNT_STATUS"    , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV10G_PCS2X6G_CONFIGURATION[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PCS2X6G_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV10G_PCS2X6G_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PCS2X6G_STATUS"                       , 0x00000000, 0x00000001, 0x00000001},
  {"PCS2X6G_ERR_STATUS"                   , 0x00000001, 0x00000001, 0x00000001},
  {"PCS2X6G_ERR_CNT_STAT"                 , 0x00000002, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV10G_PCS2X6G_EXT_CONFIGURATION[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PCS2X6G_EXT_CFG"                      , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV10G_DEV_CFG_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"DEV_RST_CTRL"                         , 0x00000000, 0x00000001, 0x00000001},
  {"DEV_PORT_PROTECT"                     , 0x00000001, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"DEV_LB_CFG"                           , 0x00000002, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"DEV_MISC_CFG"                         , 0x00000003, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"DEV_STICKY"                           , 0x00000004, 0x00000001, 0x00000001},
#endif
  {"INTR"                                 , 0x00000005, 0x00000001, 0x00000001},
  {"INTR_ENA"                             , 0x00000006, 0x00000001, 0x00000001},
  {"INTR_IDENT"                           , 0x00000007, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"DEV_RX_STATUS"                        , 0x00000008, 0x00000001, 0x00000001},
#endif
  {"EEE_CFG"                              , 0x00000009, 0x00000001, 0x00000001},
  {"PFC_PAUSE_MODE_CTRL"                  , 0x0000000a, 0x00000001, 0x00000001},
  {"PTP_CFG"                              , 0x0000000b, 0x00000001, 0x00000001},
  {"PTP_CFG_BTDLY"                        , 0x0000000c, 0x00000001, 0x00000001},
  {"PTP_EVENTS"                           , 0x0000000d, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV10G[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"MAC_CFG_STATUS"                       , 0x00000000, 0x00000001, 0x0000000e, regs_within_DEV10G_MAC_CFG_STATUS},
  {"DEV_STATISTICS_32BIT"                 , 0x0000000e, 0x00000001, 0x00000027, regs_within_DEV10G_DEV_STATISTICS_32BIT},
  {"DEV_STATISTICS_40BIT"                 , 0x00000035, 0x00000001, 0x0000000a, regs_within_DEV10G_DEV_STATISTICS_40BIT},
  {"PCS_XAUI_CONFIGURATION"               , 0x0000003f, 0x00000001, 0x00000007, regs_within_DEV10G_PCS_XAUI_CONFIGURATION},
  {"PCS_XAUI_STATUS"                      , 0x00000046, 0x00000001, 0x0000000a, regs_within_DEV10G_PCS_XAUI_STATUS},
  {"PCS_XAUI_TSTPAT_CONFIGURATION"        , 0x00000050, 0x00000001, 0x00000001, regs_within_DEV10G_PCS_XAUI_TSTPAT_CONFIGURATION},
  {"PCS_XAUI_TSTPAT_STATUS"               , 0x00000051, 0x00000001, 0x00000002, regs_within_DEV10G_PCS_XAUI_TSTPAT_STATUS},
  {"PCS2X6G_CONFIGURATION"                , 0x00000053, 0x00000001, 0x00000001, regs_within_DEV10G_PCS2X6G_CONFIGURATION},
  {"PCS2X6G_STATUS"                       , 0x00000054, 0x00000001, 0x00000003, regs_within_DEV10G_PCS2X6G_STATUS},
  {"PCS2X6G_EXT_CONFIGURATION"            , 0x00000057, 0x00000001, 0x00000001, regs_within_DEV10G_PCS2X6G_EXT_CONFIGURATION},
  {"DEV_CFG_STATUS"                       , 0x00000058, 0x00000001, 0x0000000e, regs_within_DEV10G_DEV_CFG_STATUS},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_CHIP_REGS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CHIP_ID"                              , 0x00000000, 0x00000001, 0x00000001},
  {"GPR"                                  , 0x00000001, 0x00000001, 0x00000001},
  {"SOFT_RST"                             , 0x00000002, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"HW_CFG"                               , 0x00000003, 0x00000001, 0x00000001},
#endif
  {"HW_STAT"                              , 0x00000004, 0x00000001, 0x00000001},
  {"HW_SGPIO_SD_CFG"                      , 0x00000005, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"FEA_STAT"                             , 0x00000006, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"FEA_DIS"                              , 0x00000007, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_SW_REGS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"SW_INTR"                              , 0x00000000, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_VCORE_ACCESS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"VA_CTRL"                              , 0x00000000, 0x00000001, 0x00000001},
  {"VA_ADDR"                              , 0x00000001, 0x00000001, 0x00000001},
  {"VA_DATA"                              , 0x00000002, 0x00000001, 0x00000001},
  {"VA_DATA_INCR"                         , 0x00000003, 0x00000001, 0x00000001},
  {"VA_DATA_INERT"                        , 0x00000004, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_GPIO[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"GPIO_OUT_SET"                         , 0x00000000, 0x00000001, 0x00000001},
  {"GPIO_OUT_SET1"                        , 0x00000001, 0x00000001, 0x00000001},
  {"GPIO_OUT_CLR"                         , 0x00000002, 0x00000001, 0x00000001},
  {"GPIO_OUT_CLR1"                        , 0x00000003, 0x00000001, 0x00000001},
  {"GPIO_OUT"                             , 0x00000004, 0x00000001, 0x00000001},
  {"GPIO_OUT1"                            , 0x00000005, 0x00000001, 0x00000001},
  {"GPIO_IN"                              , 0x00000006, 0x00000001, 0x00000001},
  {"GPIO_IN1"                             , 0x00000007, 0x00000001, 0x00000001},
  {"GPIO_OE"                              , 0x00000008, 0x00000001, 0x00000001},
  {"GPIO_OE1"                             , 0x00000009, 0x00000001, 0x00000001},
  {"GPIO_INTR"                            , 0x0000000a, 0x00000001, 0x00000001},
  {"GPIO_INTR1"                           , 0x0000000b, 0x00000001, 0x00000001},
  {"GPIO_INTR_ENA"                        , 0x0000000c, 0x00000001, 0x00000001},
  {"GPIO_INTR_ENA1"                       , 0x0000000d, 0x00000001, 0x00000001},
  {"GPIO_INTR_IDENT"                      , 0x0000000e, 0x00000001, 0x00000001},
  {"GPIO_INTR_IDENT1"                     , 0x0000000f, 0x00000001, 0x00000001},
  {"GPIO_ALT"                             , 0x00000010, 0x00000002, 0x00000001},
  {"GPIO_ALT1"                            , 0x00000012, 0x00000002, 0x00000001},
  {"GPIO_SD_MAP"                          , 0x00000014, 0x00000010, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_MIIM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MII_STATUS"                           , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"MII_CFG_7226"                         , 0x00000001, 0x00000001, 0x00000001},
#endif
  {"MII_CMD"                              , 0x00000002, 0x00000001, 0x00000001},
  {"MII_DATA"                             , 0x00000003, 0x00000001, 0x00000001},
  {"MII_CFG"                              , 0x00000004, 0x00000001, 0x00000001},
  {"MII_SCAN_0"                           , 0x00000005, 0x00000001, 0x00000001},
  {"MII_SCAN_1"                           , 0x00000006, 0x00000001, 0x00000001},
  {"MII_SCAN_LAST_RSLTS"                  , 0x00000007, 0x00000001, 0x00000001},
  {"MII_SCAN_LAST_RSLTS_VLD"              , 0x00000008, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_MIIM_READ_SCAN[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MII_SCAN_RSLTS_STICKY"                , 0x00000000, 0x00000003, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_TEMP_SENSOR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TEMP_SENSOR_CTRL"                     , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"TEMP_SENSOR_CFG"                      , 0x00000001, 0x00000001, 0x00000001},
#endif
  {"TEMP_SENSOR_STAT"                     , 0x00000002, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_MIIM_SLAVE[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MIIM_SLAVE_CFG"                       , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_SIO_CTRL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SIO_INPUT_DATA"                       , 0x00000000, 0x00000004, 0x00000001},
  {"SIO_CFG"                              , 0x00000004, 0x00000001, 0x00000001},
  {"SIO_CLOCK"                            , 0x00000005, 0x00000001, 0x00000001},
  {"SIO_PORT_CFG"                         , 0x00000006, 0x00000020, 0x00000001},
  {"SIO_PORT_ENA"                         , 0x00000026, 0x00000001, 0x00000001},
  {"SIO_PWM_CFG"                          , 0x00000027, 0x00000003, 0x00000001},
  {"SIO_INTR_POL"                         , 0x0000002a, 0x00000004, 0x00000001},
  {"SIO_INTR_RAW"                         , 0x0000002e, 0x00000004, 0x00000001},
  {"SIO_INTR_TRIGGER0"                    , 0x00000032, 0x00000004, 0x00000001},
  {"SIO_INTR_TRIGGER1"                    , 0x00000036, 0x00000004, 0x00000001},
  {"SIO_INTR"                             , 0x0000003a, 0x00000004, 0x00000001},
  {"SIO_INTR_ENA"                         , 0x0000003e, 0x00000001, 0x00000001},
  {"SIO_INTR_IDENT"                       , 0x0000003f, 0x00000004, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_FAN_CTRL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"FAN_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
  {"FAN_CNT"                              , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_MEMITGR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MEMITGR_CTRL"                         , 0x00000000, 0x00000001, 0x00000001},
  {"MEMITGR_STAT"                         , 0x00000001, 0x00000001, 0x00000001},
  {"MEMITGR_INFO"                         , 0x00000002, 0x00000001, 0x00000001},
  {"MEMITGR_IDX"                          , 0x00000003, 0x00000001, 0x00000001},
  {"MEMITGR_DIV"                          , 0x00000004, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"MEMITGR_DBG"                          , 0x00000005, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_VRAP[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"VRAP_ACCESS_STAT"                     , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEVCPU_GCB[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"CHIP_REGS"                            , 0x00000000, 0x00000001, 0x00000008, regs_within_DEVCPU_GCB_CHIP_REGS},
#ifndef VTSS_RELEASE
  {"SW_REGS"                              , 0x00000008, 0x00000001, 0x00000001, regs_within_DEVCPU_GCB_SW_REGS},
#endif
  {"VCORE_ACCESS"                         , 0x00000009, 0x00000001, 0x00000005, regs_within_DEVCPU_GCB_VCORE_ACCESS},
  {"GPIO"                                 , 0x0000000e, 0x00000001, 0x00000024, regs_within_DEVCPU_GCB_GPIO},
  {"MIIM"                                 , 0x00000032, 0x00000003, 0x00000009, regs_within_DEVCPU_GCB_MIIM},
  {"MIIM_READ_SCAN"                       , 0x0000004d, 0x00000001, 0x00000003, regs_within_DEVCPU_GCB_MIIM_READ_SCAN},
  {"TEMP_SENSOR"                          , 0x00000050, 0x00000001, 0x00000003, regs_within_DEVCPU_GCB_TEMP_SENSOR},
  {"MIIM_SLAVE"                           , 0x00000053, 0x00000001, 0x00000001, regs_within_DEVCPU_GCB_MIIM_SLAVE},
  {"SIO_CTRL"                             , 0x00000054, 0x00000003, 0x00000043, regs_within_DEVCPU_GCB_SIO_CTRL},
  {"FAN_CTRL"                             , 0x0000011d, 0x00000001, 0x00000002, regs_within_DEVCPU_GCB_FAN_CTRL},
  {"MEMITGR"                              , 0x0000011f, 0x00000001, 0x00000006, regs_within_DEVCPU_GCB_MEMITGR},
  {"VRAP"                                 , 0x00000125, 0x00000001, 0x00000001, regs_within_DEVCPU_GCB_VRAP},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_ORG_DEVCPU_ORG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"IF_CTRL"                              , 0x00000000, 0x00000001, 0x00000001},
  {"IF_CFGSTAT"                           , 0x00000001, 0x00000001, 0x00000001},
  {"ORG_CFG"                              , 0x00000002, 0x00000001, 0x00000001},
  {"ERR_CNTS"                             , 0x00000003, 0x00000001, 0x00000001},
  {"TIMEOUT_CFG"                          , 0x00000004, 0x00000001, 0x00000001},
  {"GPR"                                  , 0x00000005, 0x00000001, 0x00000001},
  {"MAILBOX_SET"                          , 0x00000006, 0x00000001, 0x00000001},
  {"MAILBOX_CLR"                          , 0x00000007, 0x00000001, 0x00000001},
  {"MAILBOX"                              , 0x00000008, 0x00000001, 0x00000001},
  {"SEMA_CFG"                             , 0x00000009, 0x00000001, 0x00000001},
  {"SEMA0"                                , 0x0000000a, 0x00000001, 0x00000001},
  {"SEMA0_OWNER"                          , 0x0000000b, 0x00000001, 0x00000001},
  {"SEMA1"                                , 0x0000000c, 0x00000001, 0x00000001},
  {"SEMA1_OWNER"                          , 0x0000000d, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEVCPU_ORG[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"DEVCPU_ORG"                           , 0x00000000, 0x00000001, 0x0000000e, regs_within_DEVCPU_ORG_DEVCPU_ORG},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_PTP_PTP_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PTP_MISC_CFG"                         , 0x00000000, 0x00000001, 0x00000001},
  {"CLK_ADJ_CFG"                          , 0x00000001, 0x00000003, 0x00000001},
  {"CLK_ADJ_FRQ"                          , 0x00000004, 0x00000003, 0x00000001},
  {"PTP_PIN_INTR"                         , 0x00000007, 0x00000001, 0x00000001},
  {"PTP_PIN_INTR_ENA"                     , 0x00000008, 0x00000001, 0x00000001},
  {"PTP_INTR_IDENT"                       , 0x00000009, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_PTP_PTP_PINS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PTP_PIN_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
  {"PTP_TOD_SEC_MSB"                      , 0x00000001, 0x00000001, 0x00000001},
  {"PTP_TOD_SEC_LSB"                      , 0x00000002, 0x00000001, 0x00000001},
  {"PTP_TOD_NSEC"                         , 0x00000003, 0x00000001, 0x00000001},
  {"PTP_NSF"                              , 0x00000004, 0x00000001, 0x00000001},
  {"PIN_WF_HIGH_PERIOD"                   , 0x00000005, 0x00000001, 0x00000001},
  {"PIN_WF_LOW_PERIOD"                    , 0x00000006, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEVCPU_PTP[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"PTP_CFG"                              , 0x00000020, 0x00000001, 0x0000000a, regs_within_DEVCPU_PTP_PTP_CFG},
  {"PTP_PINS"                             , 0x00000000, 0x00000004, 0x00000008, regs_within_DEVCPU_PTP_PTP_PINS},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_QS_XTR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"XTR_GRP_CFG"                          , 0x00000000, 0x00000002, 0x00000001},
  {"XTR_RD"                               , 0x00000002, 0x00000002, 0x00000001},
  {"XTR_FRM_PRUNING"                      , 0x00000004, 0x00000002, 0x00000001},
  {"XTR_FLUSH"                            , 0x00000006, 0x00000001, 0x00000001},
  {"XTR_DATA_PRESENT"                     , 0x00000007, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"XTR_CFG"                              , 0x00000008, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_QS_INJ[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"INJ_GRP_CFG"                          , 0x00000000, 0x00000002, 0x00000001},
  {"INJ_WR"                               , 0x00000002, 0x00000002, 0x00000001},
  {"INJ_CTRL"                             , 0x00000004, 0x00000002, 0x00000001},
  {"INJ_STATUS"                           , 0x00000006, 0x00000001, 0x00000001},
  {"INJ_ERR"                              , 0x00000007, 0x00000002, 0x00000001},
#ifndef VTSS_RELEASE
  {"VTSS_DBG"                             , 0x00000009, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEVCPU_QS[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"XTR"                                  , 0x00000000, 0x00000001, 0x00000009, regs_within_DEVCPU_QS_XTR},
  {"INJ"                                  , 0x00000009, 0x00000001, 0x0000000a, regs_within_DEVCPU_QS_INJ},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DSM_RAM_CTRL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"RAM_INIT"                             , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_DSM_COREMEM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CM_ADDR"                              , 0x00000000, 0x00000001, 0x00000001},
  {"CM_DATA"                              , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_DSM_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"BUF_CFG"                              , 0x00000000, 0x00000037, 0x00000001},
  {"RATE_CTRL"                            , 0x00000037, 0x00000037, 0x00000001},
  {"IPG_SHRINK_CFG"                       , 0x0000006e, 0x00000037, 0x00000001},
  {"CLR_BUF"                              , 0x000000a5, 0x00000002, 0x00000001},
#ifndef VTSS_RELEASE
  {"SCH_STOP_WM_CFG"                      , 0x000000a7, 0x00000037, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"TX_START_WM_CFG"                      , 0x000000de, 0x00000037, 0x00000001},
#endif
  {"DEV_TX_STOP_WM_CFG"                   , 0x00000115, 0x00000037, 0x00000001},
  {"RX_PAUSE_CFG"                         , 0x0000014c, 0x00000037, 0x00000001},
  {"ETH_FC_CFG"                           , 0x00000183, 0x00000037, 0x00000001},
  {"ETH_PFC_CFG"                          , 0x000001ba, 0x00000037, 0x00000001},
  {"MAC_CFG"                              , 0x000001f1, 0x00000037, 0x00000001},
  {"MAC_ADDR_BASE_HIGH_CFG"               , 0x00000228, 0x00000035, 0x00000001},
  {"MAC_ADDR_BASE_LOW_CFG"                , 0x0000025d, 0x00000035, 0x00000001},
#ifndef VTSS_RELEASE
  {"DBG_CTRL"                             , 0x00000292, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DSM_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"AGED_FRMS"                            , 0x00000000, 0x00000037, 0x00000001},
#ifndef VTSS_RELEASE
  {"CELL_BUS_STICKY"                      , 0x00000037, 0x00000001, 0x00000001},
#endif
  {"BUF_OFLW_STICKY"                      , 0x00000038, 0x00000002, 0x00000001},
  {"BUF_UFLW_STICKY"                      , 0x0000003a, 0x00000002, 0x00000001},
#ifndef VTSS_RELEASE
  {"PRE_CNT_OFLW_STICKY"                  , 0x0000003c, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DSM_RATE_LIMIT_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TX_RATE_LIMIT_MODE"                   , 0x00000000, 0x00000037, 0x00000001},
  {"TX_IPG_STRETCH_RATIO_CFG"             , 0x00000037, 0x00000037, 0x00000001},
  {"TX_FRAME_RATE_START_CFG"              , 0x0000006e, 0x00000037, 0x00000001},
  {"TX_RATE_LIMIT_HDR_CFG"                , 0x000000a5, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DSM_RATE_LIMIT_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TX_RATE_LIMIT_STICKY"                 , 0x00000000, 0x00000002, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DSM[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"RAM_CTRL"                             , 0x00000002, 0x00000001, 0x00000001, regs_within_DSM_RAM_CTRL},
#ifndef VTSS_RELEASE
  {"COREMEM"                              , 0x00000000, 0x00000001, 0x00000002, regs_within_DSM_COREMEM},
#endif
  {"CFG"                                  , 0x00000003, 0x00000001, 0x00000293, regs_within_DSM_CFG},
  {"STATUS"                               , 0x00000296, 0x00000001, 0x0000003d, regs_within_DSM_STATUS},
  {"RATE_LIMIT_CFG"                       , 0x000002d3, 0x00000001, 0x000000a6, regs_within_DSM_RATE_LIMIT_CFG},
  {"RATE_LIMIT_STATUS"                    , 0x00000379, 0x00000001, 0x00000002, regs_within_DSM_RATE_LIMIT_STATUS},
  {NULL, 0, 0, 0, NULL}
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
#ifndef VTSS_RELEASE
  {"SE_STATE"                             , 0x00000002, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_HSCH_INP_STATE[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"INP_STATE"                            , 0x00000000, 0x00000001, 0x00000001},
  {"INP_STATE1"                           , 0x00000001, 0x00000001, 0x00000001},
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
  {"HSCH_CFG_CFG"                         , 0x00000001, 0x00000001, 0x00000001},
  {"PORT_MODE"                            , 0x00000002, 0x00000039, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_HSCH_LEAK_LISTS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"HSCH_LEAK_CFG"                        , 0x00000000, 0x00000004, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_MISC[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"EVENTS_CORE"                          , 0x00000000, 0x00000001, 0x00000001},
#endif
  {"EVENT_ENQ_ERR"                        , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_HSCH[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"HSCH_CFG"                             , 0x00000000, 0x00000fe1, 0x00000008, regs_within_HSCH_HSCH_CFG},
  {"HSCH_STATUS"                          , 0x00008000, 0x00000fe1, 0x00000004, regs_within_HSCH_HSCH_STATUS},
  {"HSCH_INP_STATE"                       , 0x0000c000, 0x00000fe1, 0x00000002, regs_within_HSCH_HSCH_INP_STATE},
  {"HSCH_DWRR"                            , 0x00007f40, 0x00000040, 0x00000001, regs_within_HSCH_HSCH_DWRR},
  {"HSCH_MISC"                            , 0x00007f80, 0x00000001, 0x0000003b, regs_within_HSCH_HSCH_MISC},
  {"HSCH_LEAK_LISTS"                      , 0x00007f08, 0x00000003, 0x00000004, regs_within_HSCH_HSCH_LEAK_LISTS},
  {"MISC"                                 , 0x00007f14, 0x00000001, 0x00000002, regs_within_HSCH_MISC},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_HSIO_PLL5G_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PLL5G_CFG0"                           , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"PLL5G_CFG1"                           , 0x00000001, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PLL5G_CFG2"                           , 0x00000002, 0x00000001, 0x00000001},
#endif
  {"PLL5G_CFG3"                           , 0x00000003, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"PLL5G_CFG4"                           , 0x00000004, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PLL5G_CFG5"                           , 0x00000005, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PLL5G_CFG6"                           , 0x00000006, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSIO_PLL5G_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PLL5G_STATUS0"                        , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"PLL5G_STATUS1"                        , 0x00000001, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_HSIO_PLL5G_BIST_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"PLL5G_BIST_CFG0A"                     , 0x00000000, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PLL5G_BIST_CFG0B"                     , 0x00000001, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PLL5G_BIST_CFG1"                      , 0x00000002, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PLL5G_BIST_CFG2"                      , 0x00000003, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#endif
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_HSIO_PLL5G_BIST_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"PLL5G_BIST_STAT0"                     , 0x00000000, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PLL5G_BIST_STAT1A"                    , 0x00000001, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PLL5G_BIST_STAT1B"                    , 0x00000002, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#endif
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_HSIO_RCOMP_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"RCOMP_CFG0"                           , 0x00000000, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_HSIO_RCOMP_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"RCOMP_STATUS"                         , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSIO_SYNC_ETH_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SYNC_ETH_CFG"                         , 0x00000000, 0x00000004, 0x00000001},
  {"SYNC_ETH_PLL2_CFG"                    , 0x00000004, 0x00000001, 0x00000001},
  {"SYNC_ETH_SD10G_CFG"                   , 0x00000005, 0x00000004, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSIO_SERDES1G_ANA_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SERDES1G_DES_CFG"                     , 0x00000000, 0x00000001, 0x00000001},
  {"SERDES1G_IB_CFG"                      , 0x00000001, 0x00000001, 0x00000001},
  {"SERDES1G_OB_CFG"                      , 0x00000002, 0x00000001, 0x00000001},
  {"SERDES1G_SER_CFG"                     , 0x00000003, 0x00000001, 0x00000001},
  {"SERDES1G_COMMON_CFG"                  , 0x00000004, 0x00000001, 0x00000001},
  {"SERDES1G_PLL_CFG"                     , 0x00000005, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_HSIO_SERDES1G_ANA_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"SERDES1G_PLL_STATUS"                  , 0x00000000, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_HSIO_SERDES1G_DIG_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"SERDES1G_DFT_CFG0"                    , 0x00000000, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SERDES1G_DFT_CFG1"                    , 0x00000001, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SERDES1G_DFT_CFG2"                    , 0x00000002, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SERDES1G_TP_CFG"                      , 0x00000003, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SERDES1G_RC_PLL_BIST_CFG"             , 0x00000004, 0x00000001, 0x00000001},
#endif
  {"SERDES1G_MISC_CFG"                    , 0x00000005, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSIO_SERDES1G_DIG_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SERDES1G_DFT_STATUS"                  , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"SERDES1G_MISC_STATUS"                 , 0x00000001, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSIO_MCB_SERDES1G_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MCB_SERDES1G_ADDR_CFG"                , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSIO_SERDES6G_DIG_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SERDES6G_DIG_CFG"                     , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"SERDES6G_DFT_CFG0"                    , 0x00000001, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SERDES6G_DFT_CFG1"                    , 0x00000002, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SERDES6G_DFT_CFG2"                    , 0x00000003, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SERDES6G_TP_CFG0"                     , 0x00000004, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SERDES6G_TP_CFG1"                     , 0x00000005, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SERDES6G_RC_PLL_BIST_CFG"             , 0x00000006, 0x00000001, 0x00000001},
#endif
  {"SERDES6G_MISC_CFG"                    , 0x00000007, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"SERDES6G_OB_ANEG_CFG"                 , 0x00000008, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_HSIO_SERDES6G_DIG_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"SERDES6G_DFT_STATUS"                  , 0x00000000, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SERDES6G_ERR_CNT"                     , 0x00000001, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SERDES6G_MISC_STATUS"                 , 0x00000002, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_HSIO_SERDES6G_ANA_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SERDES6G_DES_CFG"                     , 0x00000000, 0x00000001, 0x00000001},
  {"SERDES6G_IB_CFG"                      , 0x00000001, 0x00000001, 0x00000001},
  {"SERDES6G_IB_CFG1"                     , 0x00000002, 0x00000001, 0x00000001},
  {"SERDES6G_IB_CFG2"                     , 0x00000003, 0x00000001, 0x00000001},
  {"SERDES6G_IB_CFG3"                     , 0x00000004, 0x00000001, 0x00000001},
  {"SERDES6G_IB_CFG4"                     , 0x00000005, 0x00000001, 0x00000001},
  {"SERDES6G_IB_CFG5"                     , 0x00000006, 0x00000001, 0x00000001},
  {"SERDES6G_OB_CFG"                      , 0x00000007, 0x00000001, 0x00000001},
  {"SERDES6G_OB_CFG1"                     , 0x00000008, 0x00000001, 0x00000001},
  {"SERDES6G_SER_CFG"                     , 0x00000009, 0x00000001, 0x00000001},
  {"SERDES6G_COMMON_CFG"                  , 0x0000000a, 0x00000001, 0x00000001},
  {"SERDES6G_PLL_CFG"                     , 0x0000000b, 0x00000001, 0x00000001},
  {"SERDES6G_ACJTAG_CFG"                  , 0x0000000c, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"SERDES6G_GP_CFG"                      , 0x0000000d, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSIO_SERDES6G_ANA_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SERDES6G_IB_STATUS0"                  , 0x00000000, 0x00000001, 0x00000001},
  {"SERDES6G_IB_STATUS1"                  , 0x00000001, 0x00000001, 0x00000001},
  {"SERDES6G_ACJTAG_STATUS"               , 0x00000002, 0x00000001, 0x00000001},
  {"SERDES6G_PLL_STATUS"                  , 0x00000003, 0x00000001, 0x00000001},
  {"SERDES6G_REVID"                       , 0x00000004, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSIO_MCB_SERDES6G_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MCB_SERDES6G_ADDR_CFG"                , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSIO_HW_CFGSTAT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"HW_CFG"                               , 0x00000000, 0x00000001, 0x00000001},
  {"HW_QSGMII_CFG"                        , 0x00000001, 0x00000001, 0x00000001},
  {"HW_QSGMII_STAT"                       , 0x00000002, 0x0000000c, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_HSIO[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"PLL5G_CFG"                            , 0x00000000, 0x00000002, 0x00000007, regs_within_HSIO_PLL5G_CFG},
  {"PLL5G_STATUS"                         , 0x0000000e, 0x00000002, 0x00000002, regs_within_HSIO_PLL5G_STATUS},
#ifndef VTSS_RELEASE
  {"PLL5G_BIST_CFG"                       , 0x00000012, 0x00000002, 0x00000004, regs_within_HSIO_PLL5G_BIST_CFG},
#endif
#ifndef VTSS_RELEASE
  {"PLL5G_BIST_STATUS"                    , 0x0000001a, 0x00000002, 0x00000003, regs_within_HSIO_PLL5G_BIST_STATUS},
#endif
#ifndef VTSS_RELEASE
  {"RCOMP_CFG"                            , 0x00000020, 0x00000001, 0x00000001, regs_within_HSIO_RCOMP_CFG},
#endif
  {"RCOMP_STATUS"                         , 0x00000021, 0x00000001, 0x00000001, regs_within_HSIO_RCOMP_STATUS},
  {"SYNC_ETH_CFG"                         , 0x00000022, 0x00000001, 0x00000009, regs_within_HSIO_SYNC_ETH_CFG},
  {"SERDES1G_ANA_CFG"                     , 0x0000002b, 0x00000001, 0x00000006, regs_within_HSIO_SERDES1G_ANA_CFG},
#ifndef VTSS_RELEASE
  {"SERDES1G_ANA_STATUS"                  , 0x00000031, 0x00000001, 0x00000001, regs_within_HSIO_SERDES1G_ANA_STATUS},
#endif
  {"SERDES1G_DIG_CFG"                     , 0x00000032, 0x00000001, 0x00000006, regs_within_HSIO_SERDES1G_DIG_CFG},
  {"SERDES1G_DIG_STATUS"                  , 0x00000038, 0x00000001, 0x00000002, regs_within_HSIO_SERDES1G_DIG_STATUS},
  {"MCB_SERDES1G_CFG"                     , 0x0000003a, 0x00000001, 0x00000001, regs_within_HSIO_MCB_SERDES1G_CFG},
  {"SERDES6G_DIG_CFG"                     , 0x0000003b, 0x00000001, 0x00000009, regs_within_HSIO_SERDES6G_DIG_CFG},
#ifndef VTSS_RELEASE
  {"SERDES6G_DIG_STATUS"                  , 0x00000044, 0x00000001, 0x00000003, regs_within_HSIO_SERDES6G_DIG_STATUS},
#endif
  {"SERDES6G_ANA_CFG"                     , 0x00000047, 0x00000001, 0x0000000e, regs_within_HSIO_SERDES6G_ANA_CFG},
  {"SERDES6G_ANA_STATUS"                  , 0x00000055, 0x00000001, 0x00000005, regs_within_HSIO_SERDES6G_ANA_STATUS},
  {"MCB_SERDES6G_CFG"                     , 0x0000005a, 0x00000001, 0x00000001, regs_within_HSIO_MCB_SERDES6G_CFG},
  {"HW_CFGSTAT"                           , 0x0000005b, 0x00000001, 0x0000000e, regs_within_HSIO_HW_CFGSTAT},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_ICPU_CFG_CPU_SYSTEM_CTRL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"GPR"                                  , 0x00000000, 0x00000008, 0x00000001},
  {"RESET"                                , 0x00000008, 0x00000001, 0x00000001},
  {"GENERAL_CTRL"                         , 0x00000009, 0x00000001, 0x00000001},
  {"GENERAL_STAT"                         , 0x0000000a, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_ICPU_CFG_PI_MST[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"PI_MST_CFG"                           , 0x00000000, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PI_MST_CTRL"                          , 0x00000001, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PI_MST_STATUS"                        , 0x00000002, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PI_SLV_CFG"                           , 0x00000003, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_ICPU_CFG_SPI_MST[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SPI_MST_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"SPI_MST_STATUS"                       , 0x00000001, 0x00000004, 0x00000001},
#endif
  {"SW_MODE"                              , 0x00000005, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_ICPU_CFG_MPU8051[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"MPU8051_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
#endif
  {"MPU8051_STAT"                         , 0x00000001, 0x00000001, 0x00000001},
  {"MPU8051_MMAP"                         , 0x00000002, 0x00000001, 0x00000001},
  {"MEMACC_CTRL"                          , 0x00000003, 0x00000001, 0x00000001},
  {"MEMACC"                               , 0x00000004, 0x00000001, 0x00000001},
  {"MEMACC_SBA"                           , 0x00000005, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"MPU8051_IROM"                         , 0x00000006, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_ICPU_CFG_INTR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"INTR_RAW"                             , 0x00000000, 0x00000001, 0x00000001},
  {"INTR_TRIGGER"                         , 0x00000001, 0x00000002, 0x00000001},
  {"INTR_FORCE"                           , 0x00000003, 0x00000001, 0x00000001},
  {"INTR_STICKY"                          , 0x00000004, 0x00000001, 0x00000001},
  {"INTR_BYPASS"                          , 0x00000005, 0x00000001, 0x00000001},
  {"INTR_ENA"                             , 0x00000006, 0x00000001, 0x00000001},
  {"INTR_ENA_CLR"                         , 0x00000007, 0x00000001, 0x00000001},
  {"INTR_ENA_SET"                         , 0x00000008, 0x00000001, 0x00000001},
  {"INTR_IDENT"                           , 0x00000009, 0x00000001, 0x00000001},
  {"DST_INTR_MAP"                         , 0x0000000a, 0x00000004, 0x00000001},
  {"DST_INTR_IDENT"                       , 0x0000000e, 0x00000004, 0x00000001},
  {"EXT_SRC_INTR_POL"                     , 0x00000012, 0x00000001, 0x00000001},
  {"EXT_DST_INTR_POL"                     , 0x00000013, 0x00000001, 0x00000001},
  {"EXT_DST_INTR_DRV"                     , 0x00000014, 0x00000001, 0x00000001},
  {"DEV_INTR_POL"                         , 0x00000015, 0x00000001, 0x00000001},
  {"DEV_INTR_POL1"                        , 0x00000016, 0x00000001, 0x00000001},
  {"DEV_INTR_RAW"                         , 0x00000017, 0x00000001, 0x00000001},
  {"DEV_INTR_RAW1"                        , 0x00000018, 0x00000001, 0x00000001},
  {"DEV_INTR_TRIGGER"                     , 0x00000019, 0x00000002, 0x00000001},
  {"DEV_INTR_TRIGGER1"                    , 0x0000001b, 0x00000002, 0x00000001},
  {"DEV_INTR_STICKY"                      , 0x0000001d, 0x00000001, 0x00000001},
  {"DEV_INTR_STICKY1"                     , 0x0000001e, 0x00000001, 0x00000001},
  {"DEV_INTR_BYPASS"                      , 0x0000001f, 0x00000001, 0x00000001},
  {"DEV_INTR_BYPASS1"                     , 0x00000020, 0x00000001, 0x00000001},
  {"DEV_INTR_ENA"                         , 0x00000021, 0x00000001, 0x00000001},
  {"DEV_INTR_ENA1"                        , 0x00000022, 0x00000001, 0x00000001},
  {"DEV_INTR_IDENT"                       , 0x00000023, 0x00000001, 0x00000001},
  {"DEV_INTR_IDENT1"                      , 0x00000024, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ICPU_CFG_TIMERS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"WDT"                                  , 0x00000000, 0x00000001, 0x00000001},
  {"TIMER_TICK_DIV"                       , 0x00000001, 0x00000001, 0x00000001},
  {"TIMER_VALUE"                          , 0x00000002, 0x00000003, 0x00000001},
  {"TIMER_RELOAD_VALUE"                   , 0x00000005, 0x00000003, 0x00000001},
  {"TIMER_CTRL"                           , 0x00000008, 0x00000003, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ICPU_CFG_MEMCTRL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MEMCTRL_CTRL"                         , 0x00000000, 0x00000001, 0x00000001},
  {"MEMCTRL_CFG"                          , 0x00000001, 0x00000001, 0x00000001},
  {"MEMCTRL_STAT"                         , 0x00000002, 0x00000001, 0x00000001},
  {"MEMCTRL_REF_PERIOD"                   , 0x00000003, 0x00000001, 0x00000001},
  {"MEMCTRL_ZQCAL"                        , 0x00000004, 0x00000001, 0x00000001},
  {"MEMCTRL_TIMING0"                      , 0x00000005, 0x00000001, 0x00000001},
  {"MEMCTRL_TIMING1"                      , 0x00000006, 0x00000001, 0x00000001},
  {"MEMCTRL_TIMING2"                      , 0x00000007, 0x00000001, 0x00000001},
  {"MEMCTRL_TIMING3"                      , 0x00000008, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"MEMCTRL_TIMING4"                      , 0x00000009, 0x00000001, 0x00000001},
#endif
  {"MEMCTRL_MR0_VAL"                      , 0x0000000a, 0x00000001, 0x00000001},
  {"MEMCTRL_MR1_VAL"                      , 0x0000000b, 0x00000001, 0x00000001},
  {"MEMCTRL_MR2_VAL"                      , 0x0000000c, 0x00000001, 0x00000001},
  {"MEMCTRL_MR3_VAL"                      , 0x0000000d, 0x00000001, 0x00000001},
  {"MEMCTRL_TERMRES_CTRL"                 , 0x0000000e, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"MEMCTRL_DFT"                          , 0x0000000f, 0x00000001, 0x00000001},
#endif
  {"MEMCTRL_DQS_DLY"                      , 0x00000010, 0x00000002, 0x00000001},
#ifndef VTSS_RELEASE
  {"MEMCTRL_DQS_AUTO"                     , 0x00000012, 0x00000002, 0x00000001},
#endif
  {"MEMPHY_CFG"                           , 0x00000014, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"MEMPHY_DFT"                           , 0x00000015, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"MEMPHY_DLLCFG0"                       , 0x00000016, 0x00000003, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"MEMPHY_DLLCFG1"                       , 0x00000019, 0x00000003, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"MEMPHY_DQ_DLY_TRM"                    , 0x0000001c, 0x00000002, 0x00000001},
#endif
  {"MEMPHY_ZCAL"                          , 0x0000001e, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"MEMPHY_ZCAL_STAT"                     , 0x0000001f, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"MEMPHY_ZCAL_OVR"                      , 0x00000020, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"MEMPHY_ZCAL_FORCE"                    , 0x00000021, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ICPU_CFG_TWI_DELAY[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TWI_CONFIG"                           , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ICPU_CFG_TWI_SPIKE_FILTER[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TWI_SPIKE_FILTER_CFG"                 , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ICPU_CFG_FDMA[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"FDMA_DCB_LLP"                         , 0x00000000, 0x0000000a, 0x00000001},
  {"FDMA_DCB_DATAP"                       , 0x0000000a, 0x0000000a, 0x00000001},
  {"FDMA_DCB_DATAL"                       , 0x00000014, 0x0000000a, 0x00000001},
  {"FDMA_DCB_STAT"                        , 0x0000001e, 0x0000000a, 0x00000001},
  {"FDMA_DCB_LLP_PREV"                    , 0x00000028, 0x0000000a, 0x00000001},
  {"FDMA_CH_STAT"                         , 0x00000032, 0x00000001, 0x00000001},
  {"FDMA_CH_SAFE"                         , 0x00000033, 0x00000001, 0x00000001},
  {"FDMA_CH_ACTIVATE"                     , 0x00000034, 0x00000001, 0x00000001},
  {"FDMA_CH_DISABLE"                      , 0x00000035, 0x00000001, 0x00000001},
  {"FDMA_CH_FORCEDIS"                     , 0x00000036, 0x00000001, 0x00000001},
  {"FDMA_CH_CNT"                          , 0x00000037, 0x0000000a, 0x00000001},
  {"FDMA_CH_INJ_TOKEN_CNT"                , 0x00000041, 0x00000008, 0x00000001},
  {"FDMA_CH_INJ_TOKEN_TICK_RLD"           , 0x00000049, 0x00000008, 0x00000001},
  {"FDMA_CH_INJ_TOKEN_TICK_CNT"           , 0x00000051, 0x00000008, 0x00000001},
  {"FDMA_EVT_ERR"                         , 0x00000059, 0x00000001, 0x00000001},
  {"FDMA_EVT_ERR_CODE"                    , 0x0000005a, 0x00000001, 0x00000001},
  {"FDMA_INTR_LLP"                        , 0x0000005b, 0x00000001, 0x00000001},
  {"FDMA_INTR_LLP_ENA"                    , 0x0000005c, 0x00000001, 0x00000001},
  {"FDMA_INTR_FRM"                        , 0x0000005d, 0x00000001, 0x00000001},
  {"FDMA_INTR_FRM_ENA"                    , 0x0000005e, 0x00000001, 0x00000001},
  {"FDMA_INTR_SIG"                        , 0x0000005f, 0x00000001, 0x00000001},
  {"FDMA_INTR_SIG_ENA"                    , 0x00000060, 0x00000001, 0x00000001},
  {"FDMA_INTR_ENA"                        , 0x00000061, 0x00000001, 0x00000001},
  {"FDMA_INTR_IDENT"                      , 0x00000062, 0x00000001, 0x00000001},
  {"FDMA_CH_CFG"                          , 0x00000063, 0x0000000a, 0x00000001},
  {"FDMA_GCFG"                            , 0x0000006d, 0x00000001, 0x00000001},
  {"FDMA_GSTAT"                           , 0x0000006e, 0x00000001, 0x00000001},
  {"FDMA_IDLECNT"                         , 0x0000006f, 0x00000001, 0x00000001},
  {"FDMA_CONST"                           , 0x00000070, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ICPU_CFG_PCIE[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"PCIE_CTRL"                            , 0x00000000, 0x00000001, 0x00000001},
#endif
  {"PCIE_CFG"                             , 0x00000001, 0x00000001, 0x00000001},
  {"PCIE_STAT"                            , 0x00000002, 0x00000001, 0x00000001},
  {"PCIE_AUX_CFG"                         , 0x00000003, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"PCIE_DBG_STAT"                        , 0x00000004, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PCIEMST_REPLY_INFO"                   , 0x00000005, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PCIEMST_BAR1_OFFSET"                  , 0x00000006, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PCIEMST_BAR1_MASK"                    , 0x00000007, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PCIEMST_BAR2_OFFSET"                  , 0x00000008, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PCIEMST_BAR2_MASK"                    , 0x00000009, 0x00000001, 0x00000001},
#endif
  {"PCIESLV_FDMA"                         , 0x0000000a, 0x00000001, 0x00000001},
  {"PCIESLV_SBA"                          , 0x0000000b, 0x00000001, 0x00000001},
  {"PCIEPCS_CFG"                          , 0x0000000c, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"PCIEPCS_BEACON"                       , 0x0000000d, 0x00000001, 0x00000001},
#endif
  {"PCIE_INTR"                            , 0x0000000e, 0x00000001, 0x00000001},
  {"PCIE_INTR_ENA"                        , 0x0000000f, 0x00000001, 0x00000001},
  {"PCIE_INTR_IDENT"                      , 0x00000010, 0x00000001, 0x00000001},
  {"PCIE_INTR_COMMON_CFG"                 , 0x00000011, 0x00000001, 0x00000001},
  {"PCIE_INTR_CFG"                        , 0x00000012, 0x00000002, 0x00000001},
#ifndef VTSS_RELEASE
  {"PCIE_INTR_STAT"                       , 0x00000014, 0x00000002, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ICPU_CFG_MANUAL_XTRINJ[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MANUAL_XTR"                           , 0x00000000, 0x00001000, 0x00000001},
  {"MANUAL_INJ"                           , 0x00001000, 0x00001000, 0x00000001},
  {"MANUAL_CFG"                           , 0x00002000, 0x00000001, 0x00000001},
  {"MANUAL_INTR"                          , 0x00002001, 0x00000001, 0x00000001},
  {"MANUAL_INTR_ENA"                      , 0x00002002, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_ICPU_CFG[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"CPU_SYSTEM_CTRL"                      , 0x00000000, 0x00000001, 0x0000000b, regs_within_ICPU_CFG_CPU_SYSTEM_CTRL},
#ifndef VTSS_RELEASE
  {"PI_MST"                               , 0x0000000b, 0x00000001, 0x00000004, regs_within_ICPU_CFG_PI_MST},
#endif
  {"SPI_MST"                              , 0x0000000f, 0x00000001, 0x00000006, regs_within_ICPU_CFG_SPI_MST},
#ifndef VTSS_RELEASE
  {"MPU8051"                              , 0x00000015, 0x00000001, 0x00000007, regs_within_ICPU_CFG_MPU8051},
#endif
  {"INTR"                                 , 0x0000001c, 0x00000001, 0x00000025, regs_within_ICPU_CFG_INTR},
  {"TIMERS"                               , 0x00000041, 0x00000001, 0x0000000b, regs_within_ICPU_CFG_TIMERS},
  {"MEMCTRL"                              , 0x0000004c, 0x00000001, 0x00000022, regs_within_ICPU_CFG_MEMCTRL},
  {"TWI_DELAY"                            , 0x0000006e, 0x00000001, 0x00000001, regs_within_ICPU_CFG_TWI_DELAY},
  {"TWI_SPIKE_FILTER"                     , 0x0000006f, 0x00000001, 0x00000001, regs_within_ICPU_CFG_TWI_SPIKE_FILTER},
  {"FDMA"                                 , 0x00000070, 0x00000001, 0x00000071, regs_within_ICPU_CFG_FDMA},
  {"PCIE"                                 , 0x000000e1, 0x00000001, 0x00000016, regs_within_ICPU_CFG_PCIE},
  {"MANUAL_XTRINJ"                        , 0x00001000, 0x00000001, 0x00002003, regs_within_ICPU_CFG_MANUAL_XTRINJ},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_LRN_COMMON[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"COMMON_ACCESS_CTRL"                   , 0x00000000, 0x00000001, 0x00000001},
  {"MAC_ACCESS_CFG_0"                     , 0x00000001, 0x00000001, 0x00000001},
  {"MAC_ACCESS_CFG_1"                     , 0x00000002, 0x00000001, 0x00000001},
  {"MAC_ACCESS_CFG_2"                     , 0x00000003, 0x00000001, 0x00000001},
  {"SCAN_NEXT_CFG"                        , 0x00000004, 0x00000001, 0x00000001},
  {"SCAN_NEXT_CFG_1"                      , 0x00000005, 0x00000001, 0x00000001},
  {"SCAN_LAST_ROW_CFG"                    , 0x00000006, 0x00000001, 0x00000001},
  {"SCAN_NEXT_CNT"                        , 0x00000007, 0x00000001, 0x00000001},
  {"AUTOAGE_CFG"                          , 0x00000008, 0x00000004, 0x00000001},
  {"AUTOAGE_CFG_1"                        , 0x0000000c, 0x00000001, 0x00000001},
  {"AUTOAGE_CFG_2"                        , 0x0000000d, 0x00000001, 0x00000001},
  {"AUTO_LRN_CFG"                         , 0x0000000e, 0x00000001, 0x00000001},
  {"EVENT_STICKY"                         , 0x0000000f, 0x00000001, 0x00000001},
  {"LATEST_POS_STATUS"                    , 0x00000010, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_LRN[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"COMMON"                               , 0x00000000, 0x00000001, 0x00000011, regs_within_LRN_COMMON},
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
static const vtss_symreg_reg_t regs_within_PCIE_PCIE_TYPE0_HDR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"DEVICE_ID_VENDOR_ID"                  , 0x00000000, 0x00000001, 0x00000001},
  {"STATUS_COMMAND"                       , 0x00000001, 0x00000001, 0x00000001},
  {"CLASS_CODE_REVISION_ID"               , 0x00000002, 0x00000001, 0x00000001},
  {"BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE", 0x00000003, 0x00000001, 0x00000001},
  {"BAR0"                                 , 0x00000004, 0x00000001, 0x00000001},
  {"BAR1"                                 , 0x00000005, 0x00000001, 0x00000001},
  {"BAR2"                                 , 0x00000006, 0x00000001, 0x00000001},
  {"BAR3"                                 , 0x00000007, 0x00000001, 0x00000001},
  {"BAR4"                                 , 0x00000008, 0x00000001, 0x00000001},
  {"BAR5"                                 , 0x00000009, 0x00000001, 0x00000001},
  {"CARDBUS_CIS_PTR"                      , 0x0000000a, 0x00000001, 0x00000001},
  {"SUBSYSTEM_ID_SUBSYSTEM_VENDOR_ID"     , 0x0000000b, 0x00000001, 0x00000001},
  {"EXP_ROM_BASE_ADDR"                    , 0x0000000c, 0x00000001, 0x00000001},
  {"PCI_CAP_PTR"                          , 0x0000000d, 0x00000001, 0x00000001},
  {"MAX_LATENCY_MIN_GRANT_INTERRUPT_PIN_INTERRUPT_LINE", 0x0000000f, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PCIE_PCIE_PM_CAP[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CAP_ID_NXT_PTR"                       , 0x00000000, 0x00000001, 0x00000001},
  {"CON_STATUS"                           , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PCIE_PCIE_MSI_CAP[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PCI_MSI_CAP_ID_NEXT_CTRL"             , 0x00000000, 0x00000001, 0x00000001},
  {"MSI_LOWER_32"                         , 0x00000001, 0x00000001, 0x00000001},
  {"MSI_UPPER_32"                         , 0x00000002, 0x00000001, 0x00000001},
  {"MSI_PENDING_BIT"                      , 0x00000005, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PCIE_PCIE_CAP[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP", 0x00000000, 0x00000001, 0x00000001},
  {"DEVICE_CAPABILITIES"                  , 0x00000001, 0x00000001, 0x00000001},
  {"DEVICE_CONTROL_DEVICE_STATUS"         , 0x00000002, 0x00000001, 0x00000001},
  {"LINK_CAPABILITIES"                    , 0x00000003, 0x00000001, 0x00000001},
  {"LINK_CONTROL_LINK_STATUS"             , 0x00000004, 0x00000001, 0x00000001},
  {"DEVICE_CAPABILITIES2"                 , 0x00000009, 0x00000001, 0x00000001},
  {"DEVICE_CONTROL2_DEVICE_STATUS2"       , 0x0000000a, 0x00000001, 0x00000001},
  {"LINK_CAPABILITIES2"                   , 0x0000000b, 0x00000001, 0x00000001},
  {"LINK_CONTROL2_LINK_STATUS2"           , 0x0000000c, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PCIE_PCIE_AER_CAP[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"AER_EXT_CAP_HDR"                      , 0x00000000, 0x00000001, 0x00000001},
  {"UNCORR_ERR_STATUS"                    , 0x00000001, 0x00000001, 0x00000001},
  {"UNCORR_ERR_MASK"                      , 0x00000002, 0x00000001, 0x00000001},
  {"UNCORR_ERR_SEV"                       , 0x00000003, 0x00000001, 0x00000001},
  {"CORR_ERR_STATUS"                      , 0x00000004, 0x00000001, 0x00000001},
  {"CORR_ERR_MASK"                        , 0x00000005, 0x00000001, 0x00000001},
  {"ADV_ERR_CAP_CTRL"                     , 0x00000006, 0x00000001, 0x00000001},
  {"HDR_LOG_REG_0"                        , 0x00000007, 0x00000001, 0x00000001},
  {"HDR_LOG_REG_1"                        , 0x00000008, 0x00000001, 0x00000001},
  {"HDR_LOG_REG_2"                        , 0x00000009, 0x00000001, 0x00000001},
  {"HDR_LOG_REG_3"                        , 0x0000000a, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_PCIE_PCIE_PORT_LOGIC[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"ACK_LATENCY_TIMER"                    , 0x00000000, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"VENDOR_SPEC_DLLP"                     , 0x00000001, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PORT_FORCE"                           , 0x00000002, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"ACK_F_ASPM_CTRL"                      , 0x00000003, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PORT_LINK_CTRL"                       , 0x00000004, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"LANE_SKEW"                            , 0x00000005, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"TIMER_CTRL_MAX_FUNC_NUM"              , 0x00000006, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SYMBOL_TIMER_FILTER_1"                , 0x00000007, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"FILTER_MASK_REG_2"                    , 0x00000008, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL"   , 0x00000009, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"DEBUG_REG_0"                          , 0x0000000a, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"DEBUG_REG_1"                          , 0x0000000b, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"TX_P_FC_CREDIT_STATUS"                , 0x0000000c, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"TX_NP_FC_CREDIT_STATUS"               , 0x0000000d, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"TX_CPL_FC_CREDIT_STATUS"              , 0x0000000e, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"Q_STATUS"                             , 0x0000000f, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"VC_TX_ARBI_REG_1"                     , 0x00000010, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"VC_TX_ARBI_REG_2"                     , 0x00000011, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"VC0_P_RX_Q_CTRL"                      , 0x00000012, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"VC0_NP_RX_Q_CTRL"                     , 0x00000013, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"VC0_CPL_RX_Q_CTRL"                    , 0x00000014, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"GEN2_CTRL"                            , 0x00000043, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PHY_STATUS"                           , 0x00000044, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PHY_CONTROL"                          , 0x00000045, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"AXI_MASTER_CTRL_REG_0"                , 0x00000046, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"AXI_MASTER_CTRL_REG_1"                , 0x00000047, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"MISC_CONTROL_1"                       , 0x0000006f, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"AMBA_ERROR_RESPONSE_DEFAULT"          , 0x00000074, 0x00000001, 0x00000001},
#endif
  {"ATU_REGION"                           , 0x00000080, 0x00000001, 0x00000001},
  {"ATU_CFG1"                             , 0x00000081, 0x00000001, 0x00000001},
  {"ATU_CFG2"                             , 0x00000082, 0x00000001, 0x00000001},
  {"ATU_BASE_ADDR_LOW"                    , 0x00000083, 0x00000001, 0x00000001},
  {"ATU_BASE_ADDR_HIGH"                   , 0x00000084, 0x00000001, 0x00000001},
  {"ATU_LIMIT_ADDR"                       , 0x00000085, 0x00000001, 0x00000001},
  {"ATU_TGT_ADDR_LOW"                     , 0x00000086, 0x00000001, 0x00000001},
  {"ATU_TGT_ADDR_HIGH"                    , 0x00000087, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"ATU_CFG3"                             , 0x00000088, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"AUX_CLK_FREQ"                         , 0x00000110, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_PCIE[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"PCIE_TYPE0_HDR"                       , 0x00000000, 0x00000001, 0x00000003, regs_within_PCIE_PCIE_TYPE0_HDR},
  {"PCIE_PM_CAP"                          , 0x00000010, 0x00000001, 0x00000003, regs_within_PCIE_PCIE_PM_CAP},
  {"PCIE_MSI_CAP"                         , 0x00000014, 0x00000001, 0x00000003, regs_within_PCIE_PCIE_MSI_CAP},
  {"PCIE_CAP"                             , 0x0000001c, 0x00000001, 0x00000003, regs_within_PCIE_PCIE_CAP},
  {"PCIE_AER_CAP"                         , 0x00000040, 0x00000001, 0x00000003, regs_within_PCIE_PCIE_AER_CAP},
  {"PCIE_PORT_LOGIC"                      , 0x000001c0, 0x00000001, 0x00000003, regs_within_PCIE_PCIE_PORT_LOGIC},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_QFWD_SYSTEM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SWITCH_PORT_MODE"                     , 0x00000000, 0x00000039, 0x00000001},
  {"STAT_CNT_CFG"                         , 0x00000039, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"FWD_IDLE_CNT"                         , 0x0000003a, 0x00000001, 0x00000001},
#endif
  {"FRAME_COPY_CFG"                       , 0x0000003b, 0x0000000c, 0x00000001},
  {"FRAME_COPY_LRNA_CFG"                  , 0x00000047, 0x00000001, 0x00000001},
  {"FWD_DROP_EVENTS"                      , 0x00000048, 0x00000039, 0x00000001},
  {"FWD_CPU_DROP_CNT"                     , 0x00000081, 0x00000001, 0x00000001},
  {"FWD_PRESS_DROP_CNT"                   , 0x00000082, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"FWD_STAT_CNT"                         , 0x00000083, 0x00000003, 0x00000001},
#endif
  {"MIRROR_CFG"                           , 0x00000086, 0x00000001, 0x00000001},
  {"CPUQ_DISCARD"                         , 0x00000087, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QFWD_QMAP[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"QMAP_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
  {"QMAP_RANGES"                          , 0x00000001, 0x00000001, 0x00000001},
  {"QMAP_SE_CFG"                          , 0x00000002, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QFWD_QMAP_TBL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"QMAP_TBL_CFG"                         , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_QFWD[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"SYSTEM"                               , 0x000010e4, 0x00000001, 0x00000088, regs_within_QFWD_SYSTEM},
  {"QMAP"                                 , 0x00001000, 0x00000039, 0x00000004, regs_within_QFWD_QMAP},
  {"QMAP_TBL"                             , 0x00000000, 0x00001000, 0x00000001, regs_within_QFWD_QMAP_TBL},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_QRES_RES_WRED[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"WRED_PROFILE"                         , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QRES_RES_QOS_ADV[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"WRED_GROUP"                           , 0x00000000, 0x00000039, 0x00000001},
  {"RES_QOS_MODE"                         , 0x00000039, 0x00000001, 0x00000001},
  {"PFC_CFG"                              , 0x0000003a, 0x00000039, 0x00000001},
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
  {"RES_QOS_ADV"                          , 0x00005048, 0x00000001, 0x00000073, regs_within_QRES_RES_QOS_ADV},
  {"RES_CTRL"                             , 0x00000000, 0x00001400, 0x00000004, regs_within_QRES_RES_CTRL},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_QSYS_SYSTEM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"EEE_CFG"                              , 0x00000000, 0x00000039, 0x00000001},
  {"EEE_THRES"                            , 0x00000039, 0x00000001, 0x00000001},
  {"RESET_CFG"                            , 0x0000003a, 0x00000001, 0x00000001},
  {"PMEM_SIZE"                            , 0x0000003b, 0x00000001, 0x00000001},
  {"FRM_AGING"                            , 0x0000003c, 0x00000001, 0x00000001},
  {"STAT_CFG"                             , 0x0000003d, 0x00000001, 0x00000001},
  {"DP_MAP"                               , 0x0000003e, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_QSYS_MISC[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"EVENTS_CORE"                          , 0x00000000, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_QSYS_PAUSE_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PAUSE_CFG"                            , 0x00000000, 0x00000039, 0x00000001},
  {"PAUSE_TOT_CFG"                        , 0x00000039, 0x00000001, 0x00000001},
  {"ATOP"                                 , 0x0000003a, 0x00000039, 0x00000001},
  {"FWD_PRESSURE"                         , 0x00000073, 0x00000039, 0x00000001},
  {"ATOP_TOT_CFG"                         , 0x000000ac, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_MMGT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"EQ_STAT"                              , 0x00000000, 0x00000001, 0x00000001},
  {"MMGT"                                 , 0x00000001, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"MMGT_FAST"                            , 0x00000002, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_MMGT_PORT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MMGT_PORT_VIEW"                       , 0x00000000, 0x00000001, 0x00000001},
  {"MMGT_PORT_USE"                        , 0x00000001, 0x00000001, 0x00000001},
  {"MMGT_IQ_STAT"                         , 0x00000002, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_STAT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CNT"                                  , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_CALCFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CAL_AUTO"                             , 0x00000000, 0x00000004, 0x00000001},
  {"CAL_SEQ"                              , 0x00000004, 0x00000001, 0x00000001},
  {"CAL_CTRL"                             , 0x00000005, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_RAM_CTRL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"RAM_INIT"                             , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_QSYS_COREMEM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CM_ADDR"                              , 0x00000000, 0x00000001, 0x00000001},
  {"CM_DATA"                              , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reggrp_t reggrps_within_QSYS[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"SYSTEM"                               , 0x00000402, 0x00000001, 0x0000003f, regs_within_QSYS_SYSTEM},
#ifndef VTSS_RELEASE
  {"MISC"                                 , 0x00000441, 0x00000001, 0x00000001, regs_within_QSYS_MISC},
#endif
  {"PAUSE_CFG"                            , 0x00000442, 0x00000001, 0x000000ad, regs_within_QSYS_PAUSE_CFG},
  {"MMGT"                                 , 0x000004ef, 0x00000001, 0x00000003, regs_within_QSYS_MMGT},
  {"MMGT_PORT"                            , 0x000004f2, 0x00000001, 0x00000003, regs_within_QSYS_MMGT_PORT},
  {"STAT"                                 , 0x00000000, 0x00000400, 0x00000001, regs_within_QSYS_STAT},
  {"CALCFG"                               , 0x000004f5, 0x00000001, 0x00000006, regs_within_QSYS_CALCFG},
  {"RAM_CTRL"                             , 0x000004fb, 0x00000001, 0x00000001, regs_within_QSYS_RAM_CTRL},
#ifndef VTSS_RELEASE
  {"COREMEM"                              , 0x00000400, 0x00000001, 0x00000002, regs_within_QSYS_COREMEM},
#endif
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_REW_COMMON[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"COMMON_CTRL"                          , 0x00000000, 0x00000001, 0x00000001},
  {"PORT_CTRL"                            , 0x00000001, 0x00000035, 0x00000001},
  {"TPID_CFG"                             , 0x00000036, 0x00000003, 0x00000001},
  {"ES0_CTRL"                             , 0x00000039, 0x00000001, 0x00000001},
  {"MIRROR_PROBE_CFG"                     , 0x0000003a, 0x00000003, 0x00000001},
  {"MIRROR_TAG_A_CFG"                     , 0x0000003d, 0x00000003, 0x00000001},
  {"MIRROR_TAG_B_CFG"                     , 0x00000040, 0x00000003, 0x00000001},
  {"DP_MAP"                               , 0x00000043, 0x00000001, 0x00000001},
  {"DSCP_REMAP"                           , 0x00000044, 0x00000040, 0x00000001},
  {"RLEG_CFG_0"                           , 0x00000084, 0x00000001, 0x00000001},
  {"RLEG_CFG_1"                           , 0x00000085, 0x00000001, 0x00000001},
  {"CNT_CTRL"                             , 0x00000086, 0x00000001, 0x00000001},
  {"STICKY_EVENT_COUNT"                   , 0x00000087, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"STICKY_EVENT_CNT_MASK_CFG"            , 0x00000088, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"STICKY_EVENT"                         , 0x00000089, 0x00000001, 0x00000001},
#endif
  {"GCPU_CFG"                             , 0x0000008a, 0x00000008, 0x00000001},
  {"VSTAX_PORT_GRP_CFG"                   , 0x00000092, 0x00000002, 0x00000001},
  {"GCPU_TAG_CFG"                         , 0x00000094, 0x00000002, 0x00000001},
  {"HIH_DEV10G_CFG"                       , 0x00000096, 0x00000004, 0x00000001},
  {"HIH_DEF_CFG"                          , 0x0000009a, 0x00000001, 0x00000001},
  {"MIP_STICKY_EVENT"                     , 0x0000009b, 0x00000001, 0x00000001},
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
  {"PTP_IDLY1_CFG"                        , 0x00000027, 0x00000001, 0x00000001},
  {"PTP_IDLY2_CFG"                        , 0x00000028, 0x00000001, 0x00000001},
  {"PTP_SMAC_LOW"                         , 0x00000029, 0x00000001, 0x00000001},
  {"PTP_SMAC_HIGH"                        , 0x0000002a, 0x00000001, 0x00000001},
  {"HIH_CTRL"                             , 0x0000002b, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_MIP_TBL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MIP_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
  {"LBM_MAC_HIGH"                         , 0x00000001, 0x00000001, 0x00000001},
  {"LBM_MAC_LOW"                          , 0x00000002, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_PTP_CTRL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PTP_TWOSTEP_CTRL"                     , 0x00000000, 0x00000001, 0x00000001},
  {"PTP_TWOSTEP_STAMP"                    , 0x00000001, 0x00000001, 0x00000001},
  {"PTP_CPUVD_MODE_CFG"                   , 0x00000002, 0x00000004, 0x00000001},
  {"PTP_RSRV_NOT_ZERO"                    , 0x00000006, 0x00000001, 0x00000001},
  {"PTP_RSRV_NOT_ZERO_1"                  , 0x00000007, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_ENCAP[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"LL_DMAC_MSB"                          , 0x00000000, 0x00000001, 0x00000001},
  {"LL_DMAC_LSB"                          , 0x00000001, 0x00000001, 0x00000001},
  {"LL_SMAC_MSB"                          , 0x00000002, 0x00000001, 0x00000001},
  {"LL_SMAC_LSB"                          , 0x00000003, 0x00000001, 0x00000001},
  {"LL_ETYPE"                             , 0x00000004, 0x00000001, 0x00000001},
  {"MPLS_LABEL_CFG"                       , 0x00000005, 0x00000001, 0x00000001},
  {"CW_VAL"                               , 0x00000006, 0x00000001, 0x00000001},
  {"LABEL_VAL"                            , 0x00000007, 0x00000003, 0x00000001},
  {"MPLS_REMARK_CFG"                      , 0x0000000a, 0x00000003, 0x00000001},
  {"LL_TAG_CFG"                           , 0x0000000d, 0x00000001, 0x00000001},
  {"LL_TAG_VAL"                           , 0x0000000e, 0x00000002, 0x00000001},
  {"LL_TAG_REMARK_CFG"                    , 0x00000010, 0x00000002, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_ENCAP_ID[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"ENCAP_ID_CFG"                         , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_VMID[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"RLEG_CTRL"                            , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_PTP_SEQ_NO[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PTP_SEQ_NO"                           , 0x00000000, 0x00000100, 0x00000001},
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
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_REW_OAM_PDU_MOD_CONT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TEMP_CNT_REG"                         , 0x00000000, 0x00000001, 0x00000001},
  {"LM_CNT_FRAME"                         , 0x00000001, 0x00000001, 0x00000001},
  {"CCM_LM_INFO_REG"                      , 0x00000002, 0x00000001, 0x00000001},
  {"CCM_LM_TX_B_REG"                      , 0x00000003, 0x00000001, 0x00000001},
  {"CCM_LM_RX_B_REG"                      , 0x00000004, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_REW_PDU_MOD_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"DM_PTP_DOMAIN_CFG"                    , 0x00000000, 0x00000035, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_RAM_CTRL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"RAM_INIT"                             , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_REW_COREMEM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CM_ADDR"                              , 0x00000000, 0x00000001, 0x00000001},
  {"CM_DATA"                              , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reggrp_t reggrps_within_REW[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"COMMON"                               , 0x00010750, 0x00000001, 0x0000009c, regs_within_REW_COMMON},
  {"MAP_RES_A"                            , 0x00008000, 0x00001000, 0x00000002, regs_within_REW_MAP_RES_A},
  {"MAP_RES_B"                            , 0x0000a000, 0x00001000, 0x00000002, regs_within_REW_MAP_RES_B},
  {"PORT"                                 , 0x0000f000, 0x00000035, 0x00000040, regs_within_REW_PORT},
  {"MIP_TBL"                              , 0x0000e000, 0x00000400, 0x00000004, regs_within_REW_MIP_TBL},
  {"PTP_CTRL"                             , 0x0000fd42, 0x00000001, 0x00000008, regs_within_REW_PTP_CTRL},
  {"ENCAP"                                , 0x00000000, 0x00000400, 0x00000020, regs_within_REW_ENCAP},
  {"ENCAP_ID"                             , 0x00010000, 0x00000400, 0x00000001, regs_within_REW_ENCAP_ID},
  {"VMID"                                 , 0x0000fd80, 0x00000080, 0x00000001, regs_within_REW_VMID},
  {"PTP_SEQ_NO"                           , 0x00010800, 0x00000001, 0x00000100, regs_within_REW_PTP_SEQ_NO},
  {"VOE_SRV_LM_CNT"                       , 0x0000c000, 0x00002000, 0x00000001, regs_within_REW_VOE_SRV_LM_CNT},
  {"VOE_PORT_LM_CNT"                      , 0x0000fe00, 0x000001a8, 0x00000001, regs_within_REW_VOE_PORT_LM_CNT},
#ifndef VTSS_RELEASE
  {"OAM_PDU_MOD_CONT"                     , 0x00010400, 0x0000006a, 0x00000008, regs_within_REW_OAM_PDU_MOD_CONT},
#endif
  {"PDU_MOD_CFG"                          , 0x0000fd4a, 0x00000001, 0x00000035, regs_within_REW_PDU_MOD_CFG},
  {"RAM_CTRL"                             , 0x0000fd7f, 0x00000001, 0x00000001, regs_within_REW_RAM_CTRL},
#ifndef VTSS_RELEASE
  {"COREMEM"                              , 0x0000fd40, 0x00000001, 0x00000002, regs_within_REW_COREMEM},
#endif
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_SBA_SBA[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PL_CPU"                               , 0x00000000, 0x00000001, 0x00000001},
  {"PL_PCIE"                              , 0x00000001, 0x00000001, 0x00000001},
  {"PL_CSR"                               , 0x00000002, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"RESERVED1"                            , 0x00000003, 0x0000000c, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"EBT_COUNT"                            , 0x0000000f, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"EBT_EN"                               , 0x00000010, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"EBT"                                  , 0x00000011, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"DFT_MST"                              , 0x00000012, 0x00000001, 0x00000001},
#endif
  {"WT_EN"                                , 0x00000013, 0x00000001, 0x00000001},
  {"WT_TCL"                               , 0x00000014, 0x00000001, 0x00000001},
  {"WT_CPU"                               , 0x00000015, 0x00000001, 0x00000001},
  {"WT_PCIE"                              , 0x00000016, 0x00000001, 0x00000001},
  {"WT_CSR"                               , 0x00000017, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_SBA[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"SBA"                                  , 0x00000000, 0x00000001, 0x00000018, regs_within_SBA_SBA},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_SIMC_SIMC[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CTRLR0"                               , 0x00000000, 0x00000001, 0x00000001},
  {"CTRLR1"                               , 0x00000001, 0x00000001, 0x00000001},
  {"SIMCEN"                               , 0x00000002, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"MWCR"                                 , 0x00000003, 0x00000001, 0x00000001},
#endif
  {"SER"                                  , 0x00000004, 0x00000001, 0x00000001},
  {"BAUDR"                                , 0x00000005, 0x00000001, 0x00000001},
  {"TXFTLR"                               , 0x00000006, 0x00000001, 0x00000001},
  {"RXFTLR"                               , 0x00000007, 0x00000001, 0x00000001},
  {"TXFLR"                                , 0x00000008, 0x00000001, 0x00000001},
  {"RXFLR"                                , 0x00000009, 0x00000001, 0x00000001},
  {"SR"                                   , 0x0000000a, 0x00000001, 0x00000001},
  {"IMR"                                  , 0x0000000b, 0x00000001, 0x00000001},
  {"ISR"                                  , 0x0000000c, 0x00000001, 0x00000001},
  {"RISR"                                 , 0x0000000d, 0x00000001, 0x00000001},
  {"TXOICR"                               , 0x0000000e, 0x00000001, 0x00000001},
  {"RXOICR"                               , 0x0000000f, 0x00000001, 0x00000001},
  {"RXUICR"                               , 0x00000010, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"MSTICR"                               , 0x00000011, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"ICR"                                  , 0x00000012, 0x00000001, 0x00000001},
#endif
  {"DR"                                   , 0x00000018, 0x00000024, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_SIMC[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"SIMC"                                 , 0x00000000, 0x00000001, 0x00000003, regs_within_SIMC_SIMC},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_TWI_TWI[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CFG"                                  , 0x00000000, 0x00000001, 0x00000001},
  {"TAR"                                  , 0x00000001, 0x00000001, 0x00000001},
  {"SAR"                                  , 0x00000002, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"RESERVED1"                            , 0x00000003, 0x00000001, 0x00000001},
#endif
  {"DATA_CMD"                             , 0x00000004, 0x00000001, 0x00000001},
  {"SS_SCL_HCNT"                          , 0x00000005, 0x00000001, 0x00000001},
  {"SS_SCL_LCNT"                          , 0x00000006, 0x00000001, 0x00000001},
  {"FS_SCL_HCNT"                          , 0x00000007, 0x00000001, 0x00000001},
  {"FS_SCL_LCNT"                          , 0x00000008, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"RESERVED2"                            , 0x00000009, 0x00000002, 0x00000001},
#endif
  {"INTR_STAT"                            , 0x0000000b, 0x00000001, 0x00000001},
  {"INTR_MASK"                            , 0x0000000c, 0x00000001, 0x00000001},
  {"RAW_INTR_STAT"                        , 0x0000000d, 0x00000001, 0x00000001},
  {"RX_TL"                                , 0x0000000e, 0x00000001, 0x00000001},
  {"TX_TL"                                , 0x0000000f, 0x00000001, 0x00000001},
  {"CLR_INTR"                             , 0x00000010, 0x00000001, 0x00000001},
  {"CLR_RX_UNDER"                         , 0x00000011, 0x00000001, 0x00000001},
  {"CLR_RX_OVER"                          , 0x00000012, 0x00000001, 0x00000001},
  {"CLR_TX_OVER"                          , 0x00000013, 0x00000001, 0x00000001},
  {"CLR_RD_REQ"                           , 0x00000014, 0x00000001, 0x00000001},
  {"CLR_TX_ABRT"                          , 0x00000015, 0x00000001, 0x00000001},
  {"CLR_RX_DONE"                          , 0x00000016, 0x00000001, 0x00000001},
  {"CLR_ACTIVITY"                         , 0x00000017, 0x00000001, 0x00000001},
  {"CLR_STOP_DET"                         , 0x00000018, 0x00000001, 0x00000001},
  {"CLR_START_DET"                        , 0x00000019, 0x00000001, 0x00000001},
  {"CLR_GEN_CALL"                         , 0x0000001a, 0x00000001, 0x00000001},
  {"CTRL"                                 , 0x0000001b, 0x00000001, 0x00000001},
  {"STAT"                                 , 0x0000001c, 0x00000001, 0x00000001},
  {"TXFLR"                                , 0x0000001d, 0x00000001, 0x00000001},
  {"RXFLR"                                , 0x0000001e, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"RESERVED3"                            , 0x0000001f, 0x00000001, 0x00000001},
#endif
  {"TX_ABRT_SOURCE"                       , 0x00000020, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"RESERVED8"                            , 0x00000021, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"RESERVED4"                            , 0x00000022, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"RESERVED5"                            , 0x00000023, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"RESERVED6"                            , 0x00000024, 0x00000001, 0x00000001},
#endif
  {"SDA_SETUP"                            , 0x00000025, 0x00000001, 0x00000001},
  {"ACK_GEN_CALL"                         , 0x00000026, 0x00000001, 0x00000001},
  {"ENABLE_STATUS"                        , 0x00000027, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"RESERVED7"                            , 0x00000028, 0x00000015, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"COMP_PARAM_1"                         , 0x0000003d, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"COMP_VERSION"                         , 0x0000003e, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"COMP_TYPE"                            , 0x0000003f, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_TWI[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"TWI"                                  , 0x00000000, 0x00000001, 0x00000040, regs_within_TWI_TWI},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_UART_UART[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"RBR_THR"                              , 0x00000000, 0x00000001, 0x00000001},
  {"IER"                                  , 0x00000001, 0x00000001, 0x00000001},
  {"IIR_FCR"                              , 0x00000002, 0x00000001, 0x00000001},
  {"LCR"                                  , 0x00000003, 0x00000001, 0x00000001},
  {"MCR"                                  , 0x00000004, 0x00000001, 0x00000001},
  {"LSR"                                  , 0x00000005, 0x00000001, 0x00000001},
  {"MSR"                                  , 0x00000006, 0x00000001, 0x00000001},
  {"SCR"                                  , 0x00000007, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"RESERVED1"                            , 0x00000008, 0x00000017, 0x00000001},
#endif
  {"USR"                                  , 0x0000001f, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"RESERVED2"                            , 0x00000020, 0x00000009, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"HTX"                                  , 0x00000029, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_UART[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"UART"                                 , 0x00000000, 0x00000001, 0x0000002a, regs_within_UART_UART},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_VAUI_CHANNEL_VAUI_CHANNEL_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"VAUI_CHANNEL_CFG"                     , 0x00000000, 0x00000002, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VAUI_CHANNEL_ANEG_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"ANEG_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
  {"ANEG_ADV_ABILITY_0"                   , 0x00000001, 0x00000001, 0x00000001},
  {"ANEG_ADV_ABILITY_1"                   , 0x00000002, 0x00000001, 0x00000001},
  {"ANEG_NEXT_PAGE_0"                     , 0x00000003, 0x00000001, 0x00000001},
  {"ANEG_NEXT_PAGE_1"                     , 0x00000004, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VAUI_CHANNEL_ANEG_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"ANEG_LP_ADV_ABILITY_0"                , 0x00000000, 0x00000001, 0x00000001},
  {"ANEG_LP_ADV_ABILITY_1"                , 0x00000001, 0x00000001, 0x00000001},
  {"ANEG_STATUS"                          , 0x00000002, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_VAUI_CHANNEL[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"VAUI_CHANNEL_CFG"                     , 0x00000000, 0x00000001, 0x00000002, regs_within_VAUI_CHANNEL_VAUI_CHANNEL_CFG},
  {"ANEG_CFG"                             , 0x00000002, 0x00000008, 0x00000005, regs_within_VAUI_CHANNEL_ANEG_CFG},
  {"ANEG_STATUS"                          , 0x0000002a, 0x00000008, 0x00000003, regs_within_VAUI_CHANNEL_ANEG_STATUS},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_VCAP_CORE_VCAP_CORE_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"VCAP_UPDATE_CTRL"                     , 0x00000000, 0x00000001, 0x00000001},
  {"VCAP_MV_CFG"                          , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_CORE_VCAP_CORE_CACHE[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"VCAP_ENTRY_DAT"                       , 0x00000000, 0x00000040, 0x00000001},
  {"VCAP_MASK_DAT"                        , 0x00000040, 0x00000040, 0x00000001},
  {"VCAP_ACTION_DAT"                      , 0x00000080, 0x00000040, 0x00000001},
  {"VCAP_CNT_DAT"                         , 0x000000c0, 0x00000020, 0x00000001},
  {"VCAP_RULE_ENA"                        , 0x000000e0, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_CORE_VCAP_CORE_MAP[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"VCAP_CORE_IDX"                        , 0x00000000, 0x00000001, 0x00000001},
  {"VCAP_CORE_MAP"                        , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_VCAP_CORE_VCAP_CORE_STICKY[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"VCAP_STICKY"                          , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#endif
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_VCAP_CORE_VCAP_CONST[] = {
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
#endif
static const vtss_symreg_reg_t regs_within_VCAP_CORE_TCAM_BIST[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TCAM_CTRL"                            , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"TCAM_CFG"                             , 0x00000001, 0x00000001, 0x00000001},
#endif
  {"TCAM_STAT"                            , 0x00000002, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_VCAP_CORE[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"VCAP_CORE_CFG"                        , 0x00000000, 0x00000001, 0x00000002, regs_within_VCAP_CORE_VCAP_CORE_CFG},
  {"VCAP_CORE_CACHE"                      , 0x00000002, 0x00000001, 0x000000e1, regs_within_VCAP_CORE_VCAP_CORE_CACHE},
  {"VCAP_CORE_MAP"                        , 0x000000e3, 0x00000001, 0x00000002, regs_within_VCAP_CORE_VCAP_CORE_MAP},
#ifndef VTSS_RELEASE
  {"VCAP_CORE_STICKY"                     , 0x000000e5, 0x00000001, 0x00000001, regs_within_VCAP_CORE_VCAP_CORE_STICKY},
#endif
#ifndef VTSS_RELEASE
  {"VCAP_CONST"                           , 0x000000e6, 0x00000001, 0x0000000a, regs_within_VCAP_CORE_VCAP_CONST},
#endif
  {"TCAM_BIST"                            , 0x000000f0, 0x00000001, 0x00000003, regs_within_VCAP_CORE_TCAM_BIST},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_VOP_COMMON[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"VOP_CTRL"                             , 0x00000000, 0x00000001, 0x00000001},
  {"CPU_EXTR_CFG"                         , 0x00000001, 0x00000001, 0x00000001},
  {"CPU_EXTR_CFG_1"                       , 0x00000002, 0x00000001, 0x00000001},
  {"CPU_EXTR_MPLS"                        , 0x00000003, 0x00000001, 0x00000001},
  {"VERSION_CTRL"                         , 0x00000004, 0x00000001, 0x00000001},
  {"VERSION_CTRL_2"                       , 0x00000005, 0x00000001, 0x00000001},
  {"VERSION_CTRL_MPLS"                    , 0x00000006, 0x00000001, 0x00000001},
  {"OAM_GENERIC_CFG"                      , 0x00000007, 0x00000008, 0x00000001},
  {"MPLS_GENERIC_CODEPOINT"               , 0x0000000f, 0x00000008, 0x00000001},
  {"LOC_PERIOD_CFG"                       , 0x00000017, 0x00000007, 0x00000001},
  {"LOC_CTRL"                             , 0x0000001e, 0x00000001, 0x00000001},
  {"LOC_SCAN_STICKY"                      , 0x0000001f, 0x00000001, 0x00000001},
  {"MASTER_INTR_CTRL"                     , 0x00000020, 0x00000001, 0x00000001},
  {"INTR"                                 , 0x00000021, 0x00000022, 0x00000001},
  {"COMMON_MEP_MC_MAC_LSB"                , 0x00000043, 0x00000001, 0x00000001},
  {"COMMON_MEP_MC_MAC_MSB"                , 0x00000044, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_VOE_CONF_REG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"VOE_MISC_CONFIG"                      , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_VOE_CONF[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"VOE_CTRL"                             , 0x00000000, 0x00000001, 0x00000001},
  {"SAM_COSID_SEQ_CFG"                    , 0x00000001, 0x00000001, 0x00000001},
  {"SAM_NON_OAM_SEQ_CFG"                  , 0x00000002, 0x00000001, 0x00000001},
  {"PATH_VOE_CFG"                         , 0x00000003, 0x00000001, 0x00000001},
  {"OAM_CPU_COPY_CTRL"                    , 0x00000004, 0x00000001, 0x00000001},
  {"PDU_VOE_PASS"                         , 0x00000005, 0x00000001, 0x00000001},
  {"OAM_CNT_OAM_CTRL"                     , 0x00000006, 0x00000001, 0x00000001},
  {"OAM_CNT_DATA_CTRL"                    , 0x00000007, 0x00000001, 0x00000001},
  {"MEP_UC_MAC_LSB"                       , 0x00000008, 0x00000001, 0x00000001},
  {"MEP_UC_MAC_MSB"                       , 0x00000009, 0x00000001, 0x00000001},
  {"OAM_HW_CTRL"                          , 0x0000000a, 0x00000001, 0x00000001},
  {"LOOPBACK_ENA"                         , 0x0000000b, 0x00000001, 0x00000001},
  {"LOOPBACK_CFG"                         , 0x0000000c, 0x00000001, 0x00000001},
  {"TX_TRANSID_UPDATE"                    , 0x0000000d, 0x00000001, 0x00000001},
  {"CCM_CFG"                              , 0x0000000e, 0x00000001, 0x00000001},
  {"CCM_MEPID_CFG"                        , 0x0000000f, 0x00000001, 0x00000001},
  {"CCM_MEGID_CFG"                        , 0x00000010, 0x0000000c, 0x00000001},
  {"SLM_CONFIG"                           , 0x0000001c, 0x00000001, 0x00000001},
  {"SLM_TEST_ID"                          , 0x0000001d, 0x00000001, 0x00000001},
  {"SLM_PEER_LIST"                        , 0x0000001e, 0x00000008, 0x00000001},
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
  {"SYNLM_EXTRACT"                        , 0x00000014, 0x00000001, 0x00000001},
  {"OAM_TX_STICKY"                        , 0x00000015, 0x00000001, 0x00000001},
  {"OAM_RX_STICKY"                        , 0x00000016, 0x00000001, 0x00000001},
  {"OAM_RX_STICKY2"                       , 0x00000017, 0x00000001, 0x00000001},
  {"CCM_STAT"                             , 0x00000018, 0x00000001, 0x00000001},
  {"CCM_RX_LAST"                          , 0x00000019, 0x00000001, 0x00000001},
  {"INTR_STICKY"                          , 0x0000001a, 0x00000001, 0x00000001},
  {"INTR_ENA"                             , 0x0000001b, 0x00000001, 0x00000001},
  {"SLM_TX_FRM_CNT"                       , 0x0000001c, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VOP_VOE_CCM_LM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CCM_TX_FCB_CFG"                       , 0x00000000, 0x00000001, 0x00000001},
  {"CCM_RX_FCB_CFG"                       , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_VOP_VOE_CONTEXT_REW[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CT_OAM_INFO_REW"                      , 0x00000000, 0x00000001, 0x00000001},
  {"CT_OAM_STICKY_REW"                    , 0x00000001, 0x00000001, 0x00000001},
  {"CT_OAM_DATA_REW"                      , 0x00000002, 0x00000001, 0x00000001},
  {"CT_OAM_DATA1_REW"                     , 0x00000003, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#endif
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_VOP_VOE_CONTEXT_ANA[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CT_OAM_INFO_ANA"                      , 0x00000000, 0x00000001, 0x00000001},
  {"CT_OAM_STICKY_ANA"                    , 0x00000001, 0x00000001, 0x00000001},
  {"CT_OAM_DATA_ANA"                      , 0x00000002, 0x00000001, 0x00000001},
  {"CT_OAM_DATA1_ANA"                     , 0x00000003, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#endif
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
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_VOP_COREMEM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CM_ADDR"                              , 0x00000000, 0x00000001, 0x00000001},
  {"CM_DATA"                              , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reggrp_t reggrps_within_VOP[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"COMMON"                               , 0x00010d42, 0x00000001, 0x00000045, regs_within_VOP_COMMON},
  {"VOE_CONF_REG"                         , 0x00013800, 0x00000435, 0x00000001, regs_within_VOP_VOE_CONF_REG},
  {"VOE_CONF"                             , 0x00000000, 0x00000435, 0x00000040, regs_within_VOP_VOE_CONF},
  {"VOE_STAT"                             , 0x00020000, 0x00000435, 0x00000020, regs_within_VOP_VOE_STAT},
  {"VOE_CCM_LM"                           , 0x00011000, 0x00000435, 0x00000002, regs_within_VOP_VOE_CCM_LM},
#ifndef VTSS_RELEASE
  {"VOE_CONTEXT_REW"                      , 0x00011900, 0x00000035, 0x00000004, regs_within_VOP_VOE_CONTEXT_REW},
#endif
#ifndef VTSS_RELEASE
  {"VOE_CONTEXT_ANA"                      , 0x00010e00, 0x0000006a, 0x00000004, regs_within_VOP_VOE_CONTEXT_ANA},
#endif
  {"VOE_CRC_ERR"                          , 0x00014000, 0x00000435, 0x00000001, regs_within_VOP_VOE_CRC_ERR},
  {"ANA_COSID_MAP_CONF"                   , 0x00012000, 0x00000400, 0x00000002, regs_within_VOP_ANA_COSID_MAP_CONF},
  {"REW_COSID_MAP_CONF"                   , 0x00012800, 0x00000400, 0x00000002, regs_within_VOP_REW_COSID_MAP_CONF},
  {"PORT_COSID_MAP_CONF"                  , 0x00011a00, 0x00000035, 0x00000004, regs_within_VOP_PORT_COSID_MAP_CONF},
  {"SAM_COSID_SEQ_CNT"                    , 0x00013000, 0x00000020, 0x00000040, regs_within_VOP_SAM_COSID_SEQ_CNT},
  {"RAM_CTRL"                             , 0x00010d87, 0x00000001, 0x00000001, regs_within_VOP_RAM_CTRL},
#ifndef VTSS_RELEASE
  {"COREMEM"                              , 0x00010d40, 0x00000001, 0x00000002, regs_within_VOP_COREMEM},
#endif
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_VOP_MPLS_VOE_CONF_MPLS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"VOE_CTRL_MPLS"                        , 0x00000000, 0x00000001, 0x00000001},
  {"CPU_COPY_CTRL_MPLS"                   , 0x00000001, 0x00000001, 0x00000001},
  {"OAM_HW_CTRL_MPLS"                     , 0x00000002, 0x00000001, 0x00000001},
  {"OAM_CNT_SEL_MPLS"                     , 0x00000003, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"OAM_CNT_DATA_MPLS"                    , 0x00000004, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PATH_VOE_MPLS"                        , 0x00000005, 0x00000001, 0x00000001},
#endif
  {"BFD_CONFIG"                           , 0x00000006, 0x00000001, 0x00000001},
  {"BFD_LOCAL_DISCR_SRC"                  , 0x00000007, 0x00000001, 0x00000001},
  {"BFD_REMOTE_DISCR_SRC"                 , 0x00000008, 0x00000001, 0x00000001},
  {"BFD_LOCAL_DISCR_SINK"                 , 0x00000009, 0x00000001, 0x00000001},
  {"BFD_REMOTE_DISCR_SINK"                , 0x0000000a, 0x00000001, 0x00000001},
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
  {"VOE_CONF_MPLS"                        , 0x00010000, 0x00000435, 0x00000010, regs_within_VOP_MPLS_VOE_CONF_MPLS},
  {"VOE_STAT_MPLS"                        , 0x00000000, 0x00000435, 0x00000020, regs_within_VOP_MPLS_VOE_STAT_MPLS},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_SD10G65_SD10G65_DES[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SD10G65_DES_CFG0"                     , 0x00000000, 0x00000001, 0x00000001},
  {"SD10G65_MOEBDIV_CFG0"                 , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G65_SD10G65_OB[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SD10G65_OB_CFG0"                      , 0x00000000, 0x00000001, 0x00000001},
  {"SD10G65_OB_CFG1"                      , 0x00000001, 0x00000001, 0x00000001},
  {"SD10G65_OB_CFG2"                      , 0x00000002, 0x00000001, 0x00000001},
  {"SD10G65_OB_CFG3"                      , 0x00000003, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"SD10G65_SBUS_TX_CFG"                  , 0x00000004, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SD10G65_TX_SVN_ID"                    , 0x00000005, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SD10G65_TX_REV_ID"                    , 0x00000006, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G65_SD10G65_IB[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SD10G65_IB_CFG0"                      , 0x00000000, 0x00000001, 0x00000001},
  {"SD10G65_IB_CFG1"                      , 0x00000001, 0x00000001, 0x00000001},
  {"SD10G65_IB_CFG2"                      , 0x00000002, 0x00000001, 0x00000001},
  {"SD10G65_IB_CFG3"                      , 0x00000003, 0x00000001, 0x00000001},
  {"SD10G65_IB_CFG4"                      , 0x00000004, 0x00000001, 0x00000001},
  {"SD10G65_IB_CFG5"                      , 0x00000005, 0x00000001, 0x00000001},
  {"SD10G65_IB_CFG6"                      , 0x00000006, 0x00000001, 0x00000001},
  {"SD10G65_IB_CFG7"                      , 0x00000007, 0x00000001, 0x00000001},
  {"SD10G65_IB_CFG8"                      , 0x00000008, 0x00000001, 0x00000001},
  {"SD10G65_IB_CFG9"                      , 0x00000009, 0x00000001, 0x00000001},
  {"SD10G65_IB_CFG10"                     , 0x0000000a, 0x00000001, 0x00000001},
  {"SD10G65_IB_CFG11"                     , 0x0000000b, 0x00000001, 0x00000001},
  {"SD10G65_SBUS_RX_CFG"                  , 0x0000000c, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"SD10G65_RX_SVN_ID"                    , 0x0000000d, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SD10G65_RX_REV_ID"                    , 0x0000000e, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G65_SD10G65_RX_RCPLL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SD10G65_RX_RCPLL_CFG0"                , 0x00000000, 0x00000001, 0x00000001},
  {"SD10G65_RX_RCPLL_CFG1"                , 0x00000001, 0x00000001, 0x00000001},
  {"SD10G65_RX_RCPLL_CFG2"                , 0x00000002, 0x00000001, 0x00000001},
  {"SD10G65_RX_RCPLL_STAT0"               , 0x00000003, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"SD10G65_RX_RCPLL_STAT1"               , 0x00000004, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G65_SD10G65_RX_SYNTH[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SD10G65_RX_SYNTH_CFG0"                , 0x00000000, 0x00000001, 0x00000001},
  {"SD10G65_RX_SYNTH_CFG1"                , 0x00000001, 0x00000001, 0x00000001},
  {"SD10G65_RX_SYNTH_CFG2"                , 0x00000002, 0x00000001, 0x00000001},
  {"SD10G65_RX_SYNTH_CFG3"                , 0x00000003, 0x00000001, 0x00000001},
  {"SD10G65_RX_SYNTH_CFG4"                , 0x00000004, 0x00000001, 0x00000001},
  {"SD10G65_RX_SYNTH_CDRLF"               , 0x00000005, 0x00000001, 0x00000001},
  {"SD10G65_RX_SYNTH_QUALIFIER0"          , 0x00000006, 0x00000001, 0x00000001},
  {"SD10G65_RX_SYNTH_QUALIFIER1"          , 0x00000007, 0x00000001, 0x00000001},
  {"SD10G65_RX_SYNTH_SYNC_CTRL"           , 0x00000008, 0x00000001, 0x00000001},
  {"F2DF_CFG_STAT"                        , 0x00000009, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G65_SD10G65_TX_SYNTH[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SD10G65_TX_SYNTH_CFG0"                , 0x00000000, 0x00000001, 0x00000001},
  {"SD10G65_TX_SYNTH_CFG1"                , 0x00000001, 0x00000001, 0x00000001},
  {"SD10G65_TX_SYNTH_CFG3"                , 0x00000002, 0x00000001, 0x00000001},
  {"SD10G65_TX_SYNTH_CFG4"                , 0x00000003, 0x00000001, 0x00000001},
  {"SD10G65_SSC_CFG0"                     , 0x00000004, 0x00000001, 0x00000001},
  {"SD10G65_SSC_CFG1"                     , 0x00000005, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G65_SD10G65_TX_RCPLL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SD10G65_TX_RCPLL_CFG0"                , 0x00000000, 0x00000001, 0x00000001},
  {"SD10G65_TX_RCPLL_CFG1"                , 0x00000001, 0x00000001, 0x00000001},
  {"SD10G65_TX_RCPLL_CFG2"                , 0x00000002, 0x00000001, 0x00000001},
  {"SD10G65_TX_RCPLL_STAT0"               , 0x00000003, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"SD10G65_TX_RCPLL_STAT1"               , 0x00000004, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_SD10G65[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"SD10G65_DES"                          , 0x00000000, 0x00000001, 0x00000002, regs_within_SD10G65_SD10G65_DES},
  {"SD10G65_OB"                           , 0x00000010, 0x00000001, 0x00000007, regs_within_SD10G65_SD10G65_OB},
  {"SD10G65_IB"                           , 0x00000020, 0x00000001, 0x0000000f, regs_within_SD10G65_SD10G65_IB},
  {"SD10G65_RX_RCPLL"                     , 0x00000030, 0x00000001, 0x00000005, regs_within_SD10G65_SD10G65_RX_RCPLL},
  {"SD10G65_RX_SYNTH"                     , 0x00000040, 0x00000001, 0x0000000a, regs_within_SD10G65_SD10G65_RX_SYNTH},
  {"SD10G65_TX_SYNTH"                     , 0x00000050, 0x00000001, 0x00000006, regs_within_SD10G65_SD10G65_TX_SYNTH},
  {"SD10G65_TX_RCPLL"                     , 0x00000060, 0x00000001, 0x00000005, regs_within_SD10G65_SD10G65_TX_RCPLL},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_SD10G65_DIG_SD10G65_APC[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"APC_TOP_CTRL_CFG"                     , 0x00000000, 0x00000001, 0x00000001},
  {"APC_COMMON_CFG0"                      , 0x00000001, 0x00000001, 0x00000001},
  {"APC_PARCTRL_SYNC_CFG"                 , 0x00000002, 0x00000001, 0x00000001},
  {"APC_PARCTRL_FSM1_TIMER_CFG"           , 0x00000003, 0x00000001, 0x00000001},
  {"APC_PARCTRL_FSM2_TIMER_CFG"           , 0x00000004, 0x00000001, 0x00000001},
  {"APC_FLEXCTRL_CNT_STATUS"              , 0x00000005, 0x00000001, 0x00000001},
  {"APC_LD_CAL_CFG"                       , 0x00000006, 0x00000001, 0x00000001},
  {"APC_IS_CAL_CFG0"                      , 0x00000007, 0x00000001, 0x00000001},
  {"APC_IS_CAL_CFG1"                      , 0x00000008, 0x00000001, 0x00000001},
  {"APC_EQZ_COMMON_CFG"                   , 0x00000009, 0x00000001, 0x00000001},
  {"APC_EQZ_GAIN_CTRL_CFG"                , 0x0000000a, 0x00000001, 0x00000001},
  {"APC_EQZ_GAIN_ADJ_CTRL_CFG"            , 0x0000000b, 0x00000001, 0x00000001},
  {"APC_EQZ_CTRL_STATUS"                  , 0x0000000c, 0x00000001, 0x00000001},
  {"APC_EQZ_LD_CTRL"                      , 0x0000000d, 0x00000001, 0x00000001},
  {"APC_EQZ_LD_CTRL_CFG0"                 , 0x0000000e, 0x00000001, 0x00000001},
  {"APC_EQZ_LD_CTRL_CFG1"                 , 0x0000000f, 0x00000001, 0x00000001},
  {"APC_EQZ_PAT_MATCH_CFG0"               , 0x00000010, 0x00000001, 0x00000001},
  {"APC_EQZ_PAT_MATCH_CFG1"               , 0x00000011, 0x00000001, 0x00000001},
  {"APC_EQZ_OFFS_CTRL"                    , 0x00000012, 0x00000001, 0x00000001},
  {"APC_EQZ_OFFS_TIMER_CFG"               , 0x00000013, 0x00000001, 0x00000001},
  {"APC_EQZ_OFFS_PAR_CFG"                 , 0x00000014, 0x00000001, 0x00000001},
  {"APC_EQZ_C_CTRL"                       , 0x00000015, 0x00000001, 0x00000001},
  {"APC_EQZ_C_TIMER_CFG"                  , 0x00000016, 0x00000001, 0x00000001},
  {"APC_EQZ_C_PAR_CFG"                    , 0x00000017, 0x00000001, 0x00000001},
  {"APC_EQZ_L_CTRL"                       , 0x00000018, 0x00000001, 0x00000001},
  {"APC_EQZ_L_TIMER_CFG"                  , 0x00000019, 0x00000001, 0x00000001},
  {"APC_EQZ_L_PAR_CFG"                    , 0x0000001a, 0x00000001, 0x00000001},
  {"APC_EQZ_AGC_CTRL"                     , 0x0000001b, 0x00000001, 0x00000001},
  {"APC_EQZ_AGC_TIMER_CFG"                , 0x0000001c, 0x00000001, 0x00000001},
  {"APC_EQZ_AGC_PAR_CFG"                  , 0x0000001d, 0x00000001, 0x00000001},
  {"APC_DFE1_CTRL"                        , 0x0000001e, 0x00000001, 0x00000001},
  {"APC_DFE1_TIMER_CFG"                   , 0x0000001f, 0x00000001, 0x00000001},
  {"APC_DFE1_PAR_CFG"                     , 0x00000020, 0x00000001, 0x00000001},
  {"APC_DFE2_CTRL"                        , 0x00000021, 0x00000001, 0x00000001},
  {"APC_DFE2_TIMER_CFG"                   , 0x00000022, 0x00000001, 0x00000001},
  {"APC_DFE2_PAR_CFG"                     , 0x00000023, 0x00000001, 0x00000001},
  {"APC_DFE3_CTRL"                        , 0x00000024, 0x00000001, 0x00000001},
  {"APC_DFE3_TIMER_CFG"                   , 0x00000025, 0x00000001, 0x00000001},
  {"APC_DFE3_PAR_CFG"                     , 0x00000026, 0x00000001, 0x00000001},
  {"APC_DFE4_CTRL"                        , 0x00000027, 0x00000001, 0x00000001},
  {"APC_DFE4_TIMER_CFG"                   , 0x00000028, 0x00000001, 0x00000001},
  {"APC_DFE4_PAR_CFG"                     , 0x00000029, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G65_DIG_SD10G65_VSCOPE2[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"VSCOPE_MAIN_CFG"                      , 0x00000000, 0x00000001, 0x00000001},
  {"VSCOPE_PAT_LOCK_CFG"                  , 0x00000001, 0x00000001, 0x00000001},
  {"VSCOPE_HW_SCAN_CFG1"                  , 0x00000002, 0x00000001, 0x00000001},
  {"VSCOPE_HW_SCAN_CFG2"                  , 0x00000003, 0x00000001, 0x00000001},
  {"VSCOPE_STAT"                          , 0x00000004, 0x00000001, 0x00000001},
  {"VSCOPE_CNT"                           , 0x00000005, 0x00000001, 0x00000001},
  {"VSCOPE_DBG_LSB"                       , 0x00000006, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G65_DIG_SD10G65_DFT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"DFT_RX_CFG"                           , 0x00000000, 0x00000001, 0x00000001},
  {"DFT_RX_MASK_CFG"                      , 0x00000001, 0x00000001, 0x00000001},
  {"DFT_RX_PAT_CFG"                       , 0x00000002, 0x00000001, 0x00000001},
  {"DFT_BIST_CFG0"                        , 0x00000003, 0x00000001, 0x00000001},
  {"DFT_BIST_CFG1"                        , 0x00000004, 0x00000001, 0x00000001},
  {"DFT_BIST_CFG2"                        , 0x00000005, 0x00000001, 0x00000001},
  {"DFT_BIST_CFG3"                        , 0x00000006, 0x00000001, 0x00000001},
  {"DFT_ERR_STAT"                         , 0x00000007, 0x00000001, 0x00000001},
  {"DFT_PRBS_STAT"                        , 0x00000008, 0x00000001, 0x00000001},
  {"DFT_MAIN_STAT"                        , 0x00000009, 0x00000001, 0x00000001},
  {"DFT_TX_CFG"                           , 0x0000000a, 0x00000001, 0x00000001},
  {"DFT_TX_PAT_CFG"                       , 0x0000000b, 0x00000001, 0x00000001},
  {"DFT_TX_CMP_DAT_STAT"                  , 0x0000000c, 0x00000001, 0x00000001},
  {"DFT_CLK_CMP_CFG"                      , 0x0000000d, 0x00000001, 0x00000001},
  {"DFT_CLK_CMP_TIMER"                    , 0x0000000e, 0x00000001, 0x00000001},
  {"DFT_CLK_CMP_VALUE"                    , 0x0000000f, 0x00000001, 0x00000001},
  {"DFT_CLK_CMP_MAXVAL"                   , 0x00000010, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G65_DIG_SD10G65_SYNC_CTRL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SYNC_CTRL_CFG"                        , 0x00000000, 0x00000001, 0x00000001},
  {"SYNC_CTRL_STAT"                       , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_SD10G65_DIG_SD10G65_RCPLL_BIST[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"SD10G65_RCPLL_BIST_CFG0"              , 0x00000000, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SD10G65_RCPLL_BIST_CFG1"              , 0x00000001, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SD10G65_RCPLL_BIST_CFG2"              , 0x00000002, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SD10G65_RCPLL_BIST_CFG3"              , 0x00000003, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SD10G65_RX_RCPLL_BIST_CFG4"           , 0x00000004, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SD10G65_RCPLL_BIST_STAT0"             , 0x00000005, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"SD10G65_RCPLL_BIST_STAT1"             , 0x00000006, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reggrp_t reggrps_within_SD10G65_DIG[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"SD10G65_APC"                          , 0x00000000, 0x00000001, 0x0000002a, regs_within_SD10G65_DIG_SD10G65_APC},
  {"SD10G65_VSCOPE2"                      , 0x0000002a, 0x00000001, 0x00000007, regs_within_SD10G65_DIG_SD10G65_VSCOPE2},
  {"SD10G65_DFT"                          , 0x00000031, 0x00000001, 0x00000011, regs_within_SD10G65_DIG_SD10G65_DFT},
  {"SD10G65_SYNC_CTRL"                    , 0x00000042, 0x00000001, 0x00000002, regs_within_SD10G65_DIG_SD10G65_SYNC_CTRL},
#ifndef VTSS_RELEASE
  {"SD10G65_RCPLL_BIST"                   , 0x00000044, 0x00000001, 0x00000007, regs_within_SD10G65_DIG_SD10G65_RCPLL_BIST},
#endif
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_KR_1X0096[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"KR_1X0096"                            , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_KR_1X0097[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"KR_1X0097"                            , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_KR_1X0098[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"KR_1X0098"                            , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_KR_1X0099[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"KR_1X0099"                            , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_KR_1X009A[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"KR_1X009A"                            , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_KR_1X009B[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"KR_1X009B"                            , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_CFG0[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_CFG0"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_CFG1[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_CFG1"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_CFG2[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_CFG2"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_CFG3[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_CFG3"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_CFG4[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_CFG4"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_CFG5[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_CFG5"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_CFG6[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_CFG6"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_CFG7[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_CFG7"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_CFG8[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_CFG8"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_CFG9[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_CFG9"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_GAIN[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_GAIN"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_COEF_OVRD[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_COEF_OVRD"                         , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_STAT_OVRD[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_STAT_OVRD"                         , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_OVRD[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_OVRD"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_STEP[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_STEP"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_MTHD[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_MTHD"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_BER_THR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_BER_THR"                           , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_BER_OFS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_BER_OFS"                           , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_LUTSEL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_LUTSEL"                            , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_BRKMASK[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"BRKMASK_LSW"                          , 0x00000000, 0x00000001, 0x00000001},
  {"TR_BRKMASK_MSW"                       , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_ROMADR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"ROMADR1"                              , 0x00000000, 0x00000001, 0x00000001},
  {"ROMADR2"                              , 0x00000001, 0x00000001, 0x00000001},
  {"ROMADR3"                              , 0x00000002, 0x00000001, 0x00000001},
  {"ROMADR4"                              , 0x00000003, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_OBCFG_ADDR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"OBCFG_ADDR"                           , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_APC_TMR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"APC_TMR"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_WT_TMR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"WT_TMR"                               , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_MW_TMR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MW_TMR_LSW"                           , 0x00000000, 0x00000001, 0x00000001},
  {"MW_TMR_MSW"                           , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_STS1[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_STS1"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_STS2[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_STS2"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_TAPVAL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_CMVAL"                             , 0x00000000, 0x00000001, 0x00000001},
  {"TR_C0VAL"                             , 0x00000001, 0x00000001, 0x00000001},
  {"TR_CPVAL"                             , 0x00000002, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_FRAMES_SENT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"FRSENT_LSW"                           , 0x00000000, 0x00000001, 0x00000001},
  {"FRSENT_MSW"                           , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_LUT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"LUT_LSW"                              , 0x00000000, 0x00000001, 0x00000001},
  {"LUT_MSW"                              , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV1_TR_ERRCNT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TR_ERRCNT"                            , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_KR_DEV1[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"KR_1X0096"                            , 0x00000006, 0x00000001, 0x00000001, regs_within_KR_DEV1_KR_1X0096},
  {"KR_1X0097"                            , 0x0000000f, 0x00000001, 0x00000001, regs_within_KR_DEV1_KR_1X0097},
  {"KR_1X0098"                            , 0x00000007, 0x00000001, 0x00000001, regs_within_KR_DEV1_KR_1X0098},
  {"KR_1X0099"                            , 0x00000008, 0x00000001, 0x00000001, regs_within_KR_DEV1_KR_1X0099},
  {"KR_1X009A"                            , 0x00000009, 0x00000001, 0x00000001, regs_within_KR_DEV1_KR_1X009A},
  {"KR_1X009B"                            , 0x0000000a, 0x00000001, 0x00000001, regs_within_KR_DEV1_KR_1X009B},
  {"TR_CFG0"                              , 0x00000010, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_CFG0},
  {"TR_CFG1"                              , 0x00000011, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_CFG1},
  {"TR_CFG2"                              , 0x00000012, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_CFG2},
  {"TR_CFG3"                              , 0x00000013, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_CFG3},
  {"TR_CFG4"                              , 0x00000014, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_CFG4},
  {"TR_CFG5"                              , 0x00000015, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_CFG5},
  {"TR_CFG6"                              , 0x00000016, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_CFG6},
  {"TR_CFG7"                              , 0x00000017, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_CFG7},
  {"TR_CFG8"                              , 0x00000018, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_CFG8},
  {"TR_CFG9"                              , 0x00000019, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_CFG9},
  {"TR_GAIN"                              , 0x0000001a, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_GAIN},
  {"TR_COEF_OVRD"                         , 0x0000001b, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_COEF_OVRD},
  {"TR_STAT_OVRD"                         , 0x0000001c, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_STAT_OVRD},
  {"TR_OVRD"                              , 0x0000000b, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_OVRD},
  {"TR_STEP"                              , 0x0000000c, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_STEP},
  {"TR_MTHD"                              , 0x0000001d, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_MTHD},
  {"TR_BER_THR"                           , 0x0000001e, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_BER_THR},
  {"TR_BER_OFS"                           , 0x0000001f, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_BER_OFS},
  {"TR_LUTSEL"                            , 0x00000020, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_LUTSEL},
  {"TR_BRKMASK"                           , 0x00000021, 0x00000001, 0x00000002, regs_within_KR_DEV1_TR_BRKMASK},
  {"TR_ROMADR"                            , 0x00000000, 0x00000001, 0x00000004, regs_within_KR_DEV1_TR_ROMADR},
  {"OBCFG_ADDR"                           , 0x00000023, 0x00000001, 0x00000001, regs_within_KR_DEV1_OBCFG_ADDR},
  {"APC_TMR"                              , 0x00000024, 0x00000001, 0x00000001, regs_within_KR_DEV1_APC_TMR},
  {"WT_TMR"                               , 0x00000025, 0x00000001, 0x00000001, regs_within_KR_DEV1_WT_TMR},
  {"MW_TMR"                               , 0x00000026, 0x00000001, 0x00000002, regs_within_KR_DEV1_MW_TMR},
  {"TR_STS1"                              , 0x0000000d, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_STS1},
  {"TR_STS2"                              , 0x0000000e, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_STS2},
  {"TR_TAPVAL"                            , 0x00000028, 0x00000001, 0x00000003, regs_within_KR_DEV1_TR_TAPVAL},
  {"TR_FRAMES_SENT"                       , 0x00000004, 0x00000001, 0x00000002, regs_within_KR_DEV1_TR_FRAMES_SENT},
  {"TR_LUT"                               , 0x0000002b, 0x00000001, 0x00000002, regs_within_KR_DEV1_TR_LUT},
  {"TR_ERRCNT"                            , 0x0000002d, 0x00000001, 0x00000001, regs_within_KR_DEV1_TR_ERRCNT},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_KR_7X0000[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"KR_7X0000"                            , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_KR_7X0001[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"KR_7X0001"                            , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_LD_ADV[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"KR_7X0010"                            , 0x00000000, 0x00000001, 0x00000001},
  {"KR_7X0011"                            , 0x00000001, 0x00000001, 0x00000001},
  {"KR_7X0012"                            , 0x00000002, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_LP_BASE_PAGE_0[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"KR_7X0013"                            , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_LP_BASE_PAGE_1[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"KR_7X0014"                            , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_LP_BASE_PAGE_2[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"KR_7X0015"                            , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_LD_NEXT_PAGE[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"KR_7X0016"                            , 0x00000000, 0x00000001, 0x00000001},
  {"KR_7X0017"                            , 0x00000001, 0x00000001, 0x00000001},
  {"KR_7X0018"                            , 0x00000002, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_LP_NEXT_PAGE[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"KR_7X0019"                            , 0x00000000, 0x00000001, 0x00000001},
  {"KR_7X001A"                            , 0x00000001, 0x00000001, 0x00000001},
  {"KR_7X001B"                            , 0x00000002, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_KR_7X0030[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"KR_7X0030"                            , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_AN_CFG0[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"AN_CFG0"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_BL_TMR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"BL_LSW"                               , 0x00000000, 0x00000001, 0x00000001},
  {"BL_MSW"                               , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_AW_TMR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"AW_LSW"                               , 0x00000000, 0x00000001, 0x00000001},
  {"AW_MSW"                               , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_LFLONG_TMR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"LFLONG_LSW"                           , 0x00000000, 0x00000001, 0x00000001},
  {"LFLONG_MSW"                           , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_LFSHORT_TMR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"LFSHORT_LSW"                          , 0x00000000, 0x00000001, 0x00000001},
  {"LFSHORT_MSW"                          , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_LP_TMR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"LP_LSW"                               , 0x00000000, 0x00000001, 0x00000001},
  {"LP_MSW"                               , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_PD_TMR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PD_LSW"                               , 0x00000000, 0x00000001, 0x00000001},
  {"PD_MSW"                               , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_KR10G_TMR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"KR10G_LSW"                            , 0x00000000, 0x00000001, 0x00000001},
  {"KR10G_MSW"                            , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_KR3G_TMR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"KR3G_LSW"                             , 0x00000000, 0x00000001, 0x00000001},
  {"KR3G_MSW"                             , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_KR1G_TMR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"KR1G_LSW"                             , 0x00000000, 0x00000001, 0x00000001},
  {"KR1G_MSW"                             , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_AN_HIST[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"AN_HIST"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_AN_SM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"AN_SM"                                , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_AN_STS0[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"AN_STS0"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_IROM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"IROM_LSW"                             , 0x00000000, 0x00000020, 0x00000001},
  {"IROM_MSW"                             , 0x00000020, 0x00000020, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_KR_DEV7_DROM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"DROM_LSW"                             , 0x00000000, 0x00000020, 0x00000001},
  {"DROM_MSW"                             , 0x00000020, 0x00000020, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_KR_DEV7[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"KR_7X0000"                            , 0x00000084, 0x00000001, 0x00000001, regs_within_KR_DEV7_KR_7X0000},
  {"KR_7X0001"                            , 0x00000085, 0x00000001, 0x00000001, regs_within_KR_DEV7_KR_7X0001},
  {"LD_ADV"                               , 0x0000008b, 0x00000001, 0x00000003, regs_within_KR_DEV7_LD_ADV},
  {"LP_BASE_PAGE_0"                       , 0x00000086, 0x00000001, 0x00000001, regs_within_KR_DEV7_LP_BASE_PAGE_0},
  {"LP_BASE_PAGE_1"                       , 0x00000087, 0x00000001, 0x00000001, regs_within_KR_DEV7_LP_BASE_PAGE_1},
  {"LP_BASE_PAGE_2"                       , 0x00000088, 0x00000001, 0x00000001, regs_within_KR_DEV7_LP_BASE_PAGE_2},
  {"LD_NEXT_PAGE"                         , 0x0000008e, 0x00000001, 0x00000003, regs_within_KR_DEV7_LD_NEXT_PAGE},
  {"LP_NEXT_PAGE"                         , 0x00000080, 0x00000001, 0x00000004, regs_within_KR_DEV7_LP_NEXT_PAGE},
  {"KR_7X0030"                            , 0x00000091, 0x00000001, 0x00000001, regs_within_KR_DEV7_KR_7X0030},
  {"AN_CFG0"                              , 0x00000092, 0x00000001, 0x00000001, regs_within_KR_DEV7_AN_CFG0},
  {"BL_TMR"                               , 0x00000093, 0x00000001, 0x00000002, regs_within_KR_DEV7_BL_TMR},
  {"AW_TMR"                               , 0x00000095, 0x00000001, 0x00000002, regs_within_KR_DEV7_AW_TMR},
  {"LFLONG_TMR"                           , 0x00000097, 0x00000001, 0x00000002, regs_within_KR_DEV7_LFLONG_TMR},
  {"LFSHORT_TMR"                          , 0x00000099, 0x00000001, 0x00000002, regs_within_KR_DEV7_LFSHORT_TMR},
  {"LP_TMR"                               , 0x0000009b, 0x00000001, 0x00000002, regs_within_KR_DEV7_LP_TMR},
  {"PD_TMR"                               , 0x0000009d, 0x00000001, 0x00000002, regs_within_KR_DEV7_PD_TMR},
  {"KR10G_TMR"                            , 0x0000009f, 0x00000001, 0x00000002, regs_within_KR_DEV7_KR10G_TMR},
  {"KR3G_TMR"                             , 0x000000a1, 0x00000001, 0x00000002, regs_within_KR_DEV7_KR3G_TMR},
  {"KR1G_TMR"                             , 0x000000a3, 0x00000001, 0x00000002, regs_within_KR_DEV7_KR1G_TMR},
  {"AN_HIST"                              , 0x000000a5, 0x00000001, 0x00000001, regs_within_KR_DEV7_AN_HIST},
  {"AN_SM"                                , 0x00000089, 0x00000001, 0x00000001, regs_within_KR_DEV7_AN_SM},
  {"AN_STS0"                              , 0x0000008a, 0x00000001, 0x00000001, regs_within_KR_DEV7_AN_STS0},
  {"IROM"                                 , 0x00000000, 0x00000001, 0x00000040, regs_within_KR_DEV7_IROM},
  {"DROM"                                 , 0x00000040, 0x00000001, 0x00000040, regs_within_KR_DEV7_DROM},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_XFI_SHELL_XFI_CONTROL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"KR_CONTROL"                           , 0x00000000, 0x00000001, 0x00000001},
  {"XFI_MODE"                             , 0x00000001, 0x00000001, 0x00000001},
  {"XFI_STATUS"                           , 0x00000002, 0x00000001, 0x00000001},
  {"INT_CTRL"                             , 0x00000003, 0x00000001, 0x00000001},
  {"SSF_HYST_ENA_CTRL"                    , 0x00000004, 0x00000001, 0x00000001},
  {"SSF_HYST_TIMING_CTRL"                 , 0x00000005, 0x00000001, 0x00000001},
  {"HSS_STICKY"                           , 0x00000006, 0x00000001, 0x00000001},
  {"HSS_MASK"                             , 0x00000007, 0x00000001, 0x00000001},
  {"HSS_STATUS"                           , 0x00000008, 0x00000001, 0x00000001},
  {"DATA_VALID_DETECT_CTRL"               , 0x00000009, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_XFI_SHELL[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"XFI_CONTROL"                          , 0x00000000, 0x00000001, 0x0000000a, regs_within_XFI_SHELL_XFI_CONTROL},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_target_t vtss_symreg_targets[] = {
  //target name         , repl, tgt_id    , base_addr                  , register group list
  {"AFI"                ,   -1, 0x000000a8, VTSS_IO_OFFSET2(0x00a80000), reggrps_within_AFI},
  {"ANA_AC"             ,   -1, 0x000000f0, VTSS_IO_OFFSET2(0x00f00000), reggrps_within_ANA_AC},
  {"ANA_AC_OAM_MOD"     ,   -1, 0x000000b8, VTSS_IO_OFFSET2(0x00b80000), reggrps_within_ANA_AC_OAM_MOD},
  {"ANA_AC_POL"         ,   -1, 0x00000098, VTSS_IO_OFFSET2(0x00980000), reggrps_within_ANA_AC_POL},
  {"ANA_ACL"            ,   -1, 0x00000043, VTSS_IO_OFFSET2(0x00430000), reggrps_within_ANA_ACL},
  {"ANA_CL"             ,   -1, 0x000000d0, VTSS_IO_OFFSET2(0x00d00000), reggrps_within_ANA_CL},
  {"ANA_L2"             ,   -1, 0x000000e0, VTSS_IO_OFFSET2(0x00e00000), reggrps_within_ANA_L2},
  {"ANA_L3"             ,   -1, 0x00000080, VTSS_IO_OFFSET2(0x00800000), reggrps_within_ANA_L3},
  {"ASM"                ,   -1, 0x00000041, VTSS_IO_OFFSET2(0x00410000), reggrps_within_ASM},
  {"DEV1G"              ,    0, 0x00000004, VTSS_IO_OFFSET2(0x00040000), reggrps_within_DEV1G},
  {"DEV1G"              ,    1, 0x00000005, VTSS_IO_OFFSET2(0x00050000), reggrps_within_DEV1G},
  {"DEV1G"              ,    2, 0x00000006, VTSS_IO_OFFSET2(0x00060000), reggrps_within_DEV1G},
  {"DEV1G"              ,    3, 0x00000007, VTSS_IO_OFFSET2(0x00070000), reggrps_within_DEV1G},
  {"DEV1G"              ,    4, 0x00000008, VTSS_IO_OFFSET2(0x00080000), reggrps_within_DEV1G},
  {"DEV1G"              ,    5, 0x00000009, VTSS_IO_OFFSET2(0x00090000), reggrps_within_DEV1G},
  {"DEV1G"              ,    6, 0x0000000a, VTSS_IO_OFFSET2(0x000a0000), reggrps_within_DEV1G},
  {"DEV1G"              ,    7, 0x0000000b, VTSS_IO_OFFSET2(0x000b0000), reggrps_within_DEV1G},
  {"DEV1G"              ,    8, 0x0000000c, VTSS_IO_OFFSET2(0x000c0000), reggrps_within_DEV1G},
  {"DEV1G"              ,    9, 0x0000000d, VTSS_IO_OFFSET2(0x000d0000), reggrps_within_DEV1G},
  {"DEV1G"              ,   10, 0x0000000e, VTSS_IO_OFFSET2(0x000e0000), reggrps_within_DEV1G},
  {"DEV1G"              ,   11, 0x0000000f, VTSS_IO_OFFSET2(0x000f0000), reggrps_within_DEV1G},
  {"DEV1G"              ,   12, 0x00000010, VTSS_IO_OFFSET2(0x00100000), reggrps_within_DEV1G},
  {"DEV1G"              ,   13, 0x00000011, VTSS_IO_OFFSET2(0x00110000), reggrps_within_DEV1G},
  {"DEV1G"              ,   14, 0x00000012, VTSS_IO_OFFSET2(0x00120000), reggrps_within_DEV1G},
  {"DEV1G"              ,   15, 0x00000013, VTSS_IO_OFFSET2(0x00130000), reggrps_within_DEV1G},
  {"DEV1G"              ,   16, 0x00000014, VTSS_IO_OFFSET2(0x00140000), reggrps_within_DEV1G},
  {"DEV1G"              ,   17, 0x00000015, VTSS_IO_OFFSET2(0x00150000), reggrps_within_DEV1G},
  {"DEV1G"              ,   18, 0x00000016, VTSS_IO_OFFSET2(0x00160000), reggrps_within_DEV1G},
  {"DEV1G"              ,   19, 0x00000017, VTSS_IO_OFFSET2(0x00170000), reggrps_within_DEV1G},
  {"DEV1G"              ,   20, 0x00000018, VTSS_IO_OFFSET2(0x00180000), reggrps_within_DEV1G},
  {"DEV1G"              ,   21, 0x00000019, VTSS_IO_OFFSET2(0x00190000), reggrps_within_DEV1G},
  {"DEV1G"              ,   22, 0x0000001a, VTSS_IO_OFFSET2(0x001a0000), reggrps_within_DEV1G},
  {"DEV1G"              ,   23, 0x0000001b, VTSS_IO_OFFSET2(0x001b0000), reggrps_within_DEV1G},
  {"DEV2G5"             ,    0, 0x0000001c, VTSS_IO_OFFSET2(0x001c0000), reggrps_within_DEV1G},
  {"DEV2G5"             ,    1, 0x0000001d, VTSS_IO_OFFSET2(0x001d0000), reggrps_within_DEV1G},
  {"DEV2G5"             ,    2, 0x0000001e, VTSS_IO_OFFSET2(0x001e0000), reggrps_within_DEV1G},
  {"DEV2G5"             ,    3, 0x0000001f, VTSS_IO_OFFSET2(0x001f0000), reggrps_within_DEV1G},
  {"DEV2G5"             ,    4, 0x00000020, VTSS_IO_OFFSET2(0x00200000), reggrps_within_DEV1G},
  {"DEV2G5"             ,    5, 0x00000021, VTSS_IO_OFFSET2(0x00210000), reggrps_within_DEV1G},
  {"DEV2G5"             ,    6, 0x00000022, VTSS_IO_OFFSET2(0x00220000), reggrps_within_DEV1G},
  {"DEV2G5"             ,    7, 0x00000023, VTSS_IO_OFFSET2(0x00230000), reggrps_within_DEV1G},
  {"DEV2G5"             ,    8, 0x00000024, VTSS_IO_OFFSET2(0x00240000), reggrps_within_DEV1G},
  {"DEV2G5"             ,    9, 0x00000025, VTSS_IO_OFFSET2(0x00250000), reggrps_within_DEV1G},
  {"DEV2G5"             ,   10, 0x00000026, VTSS_IO_OFFSET2(0x00260000), reggrps_within_DEV1G},
  {"DEV2G5"             ,   11, 0x00000027, VTSS_IO_OFFSET2(0x00270000), reggrps_within_DEV1G},
  {"DEV2G5"             ,   12, 0x00000028, VTSS_IO_OFFSET2(0x00280000), reggrps_within_DEV1G},
  {"DEV2G5"             ,   13, 0x00000029, VTSS_IO_OFFSET2(0x00290000), reggrps_within_DEV1G},
  {"DEV2G5"             ,   14, 0x0000002a, VTSS_IO_OFFSET2(0x002a0000), reggrps_within_DEV1G},
  {"DEV2G5"             ,   15, 0x0000002b, VTSS_IO_OFFSET2(0x002b0000), reggrps_within_DEV1G},
  {"DEV2G5"             ,   16, 0x0000002c, VTSS_IO_OFFSET2(0x002c0000), reggrps_within_DEV1G},
  {"DEV2G5"             ,   17, 0x0000002d, VTSS_IO_OFFSET2(0x002d0000), reggrps_within_DEV1G},
  {"DEV2G5"             ,   18, 0x0000002e, VTSS_IO_OFFSET2(0x002e0000), reggrps_within_DEV1G},
  {"DEV2G5"             ,   19, 0x0000002f, VTSS_IO_OFFSET2(0x002f0000), reggrps_within_DEV1G},
  {"DEV2G5"             ,   20, 0x00000030, VTSS_IO_OFFSET2(0x00300000), reggrps_within_DEV1G},
  {"DEV2G5"             ,   21, 0x00000031, VTSS_IO_OFFSET2(0x00310000), reggrps_within_DEV1G},
  {"DEV2G5"             ,   22, 0x00000032, VTSS_IO_OFFSET2(0x00320000), reggrps_within_DEV1G},
  {"DEV2G5"             ,   23, 0x00000033, VTSS_IO_OFFSET2(0x00330000), reggrps_within_DEV1G},
  {"DEV2G5"             ,   25, 0x00000035, VTSS_IO_OFFSET2(0x00350000), reggrps_within_DEV1G},
  {"DEV2G5"             ,   26, 0x00000036, VTSS_IO_OFFSET2(0x00360000), reggrps_within_DEV1G},
  {"DEV2G5"             ,   27, 0x00000037, VTSS_IO_OFFSET2(0x00370000), reggrps_within_DEV1G},
  {"DEV2G5"             ,   28, 0x00000038, VTSS_IO_OFFSET2(0x00380000), reggrps_within_DEV1G},
  {"DEV10G"             ,    0, 0x00000039, VTSS_IO_OFFSET2(0x00390000), reggrps_within_DEV10G},
  {"DEV10G"             ,    1, 0x0000003a, VTSS_IO_OFFSET2(0x003a0000), reggrps_within_DEV10G},
  {"DEV10G"             ,    2, 0x0000003b, VTSS_IO_OFFSET2(0x003b0000), reggrps_within_DEV10G},
  {"DEV10G"             ,    3, 0x0000003c, VTSS_IO_OFFSET2(0x003c0000), reggrps_within_DEV10G},
  {"DEVCPU_GCB"         ,   -1, 0x00000001, VTSS_IO_OFFSET2(0x00010000), reggrps_within_DEVCPU_GCB},
  {"DEVCPU_ORG"         ,   -1, 0x00000000, VTSS_IO_OFFSET2(0x00000000), reggrps_within_DEVCPU_ORG},
  {"DEVCPU_PTP"         ,   -1, 0x0000007f, VTSS_IO_OFFSET2(0x007f0000), reggrps_within_DEVCPU_PTP},
  {"DEVCPU_QS"          ,   -1, 0x00000002, VTSS_IO_OFFSET2(0x00020000), reggrps_within_DEVCPU_QS},
  {"DEV2G5"             ,   24, 0x00000034, VTSS_IO_OFFSET2(0x00340000), reggrps_within_DEV1G},
  {"DSM"                ,   -1, 0x00000045, VTSS_IO_OFFSET2(0x00450000), reggrps_within_DSM},
  {"HSCH"               ,   -1, 0x00000088, VTSS_IO_OFFSET2(0x00880000), reggrps_within_HSCH},
  {"HSIO"               ,   -1, 0x00000046, VTSS_IO_OFFSET2(0x00460000), reggrps_within_HSIO},
  {"ICPU_CFG"           ,   -1, 0x000000f1, VTSS_IO_OFFSET1(0x00000000), reggrps_within_ICPU_CFG},
  {"LRN"                ,   -1, 0x00000042, VTSS_IO_OFFSET2(0x00420000), reggrps_within_LRN},
  {"PCS10G_BR"          ,    0, 0x0000003d, VTSS_IO_OFFSET2(0x003d0000), reggrps_within_PCS_10GBASE_R},
  {"PCS10G_BR"          ,    1, 0x0000003e, VTSS_IO_OFFSET2(0x003e0000), reggrps_within_PCS_10GBASE_R},
  {"PCS10G_BR"          ,    2, 0x0000003f, VTSS_IO_OFFSET2(0x003f0000), reggrps_within_PCS_10GBASE_R},
  {"PCS10G_BR"          ,    3, 0x00000040, VTSS_IO_OFFSET2(0x00400000), reggrps_within_PCS_10GBASE_R},
  {"PCIE"               ,   -1, 0x000000f5, VTSS_IO_OFFSET1(0x00111000), reggrps_within_PCIE},
  {"QFWD"               ,   -1, 0x0000007d, VTSS_IO_OFFSET2(0x007d0000), reggrps_within_QFWD},
  {"QRES"               ,   -1, 0x00000090, VTSS_IO_OFFSET2(0x00900000), reggrps_within_QRES},
  {"QSYS"               ,   -1, 0x0000007e, VTSS_IO_OFFSET2(0x007e0000), reggrps_within_QSYS},
  {"REW"                ,   -1, 0x000000b0, VTSS_IO_OFFSET2(0x00b00000), reggrps_within_REW},
  {"SBA"                ,   -1, 0x000000f4, VTSS_IO_OFFSET1(0x00110000), reggrps_within_SBA},
  {"SIMC"               ,   -1, 0x000000f8, VTSS_IO_OFFSET1(0x00101000), reggrps_within_SIMC},
  {"TWI"                ,   -1, 0x000000f3, VTSS_IO_OFFSET1(0x00100400), reggrps_within_TWI},
  {"TWI2"               ,   -1, 0x000000f7, VTSS_IO_OFFSET1(0x00100c00), reggrps_within_TWI},
  {"UART"               ,   -1, 0x000000f2, VTSS_IO_OFFSET1(0x00100000), reggrps_within_UART},
  {"UART2"              ,   -1, 0x000000f6, VTSS_IO_OFFSET1(0x00100800), reggrps_within_UART},
  {"VAUI0"              ,   -1, 0x0000007b, VTSS_IO_OFFSET2(0x007b0000), reggrps_within_VAUI_CHANNEL},
  {"VAUI1"              ,   -1, 0x0000007c, VTSS_IO_OFFSET2(0x007c0000), reggrps_within_VAUI_CHANNEL},
  {"VCAP_ES0"           ,   -1, 0x00000047, VTSS_IO_OFFSET2(0x00470000), reggrps_within_VCAP_CORE},
  {"VCAP_SUPER"         ,   -1, 0x00000044, VTSS_IO_OFFSET2(0x00440000), reggrps_within_VCAP_CORE},
  {"VOP"                ,   -1, 0x000000c0, VTSS_IO_OFFSET2(0x00c00000), reggrps_within_VOP},
  {"VOP_MPLS"           ,   -1, 0x000000a0, VTSS_IO_OFFSET2(0x00a00000), reggrps_within_VOP_MPLS},
  {"XGANA"              ,    0, 0x00000048, VTSS_IO_OFFSET2(0x00480000), reggrps_within_SD10G65},
  {"XGANA"              ,    1, 0x00000049, VTSS_IO_OFFSET2(0x00490000), reggrps_within_SD10G65},
  {"XGANA"              ,    2, 0x0000004a, VTSS_IO_OFFSET2(0x004a0000), reggrps_within_SD10G65},
  {"XGANA"              ,    3, 0x0000004b, VTSS_IO_OFFSET2(0x004b0000), reggrps_within_SD10G65},
  {"XGDIG"              ,    0, 0x0000004c, VTSS_IO_OFFSET2(0x004c0000), reggrps_within_SD10G65_DIG},
  {"XGDIG"              ,    1, 0x0000004d, VTSS_IO_OFFSET2(0x004d0000), reggrps_within_SD10G65_DIG},
  {"XGDIG"              ,    2, 0x0000004e, VTSS_IO_OFFSET2(0x004e0000), reggrps_within_SD10G65_DIG},
  {"XGDIG"              ,    3, 0x0000004f, VTSS_IO_OFFSET2(0x004f0000), reggrps_within_SD10G65_DIG},
  {"XGKR0"              ,    0, 0x00000054, VTSS_IO_OFFSET2(0x00540000), reggrps_within_KR_DEV1},
  {"XGKR0"              ,    1, 0x00000055, VTSS_IO_OFFSET2(0x00550000), reggrps_within_KR_DEV1},
  {"XGKR0"              ,    2, 0x00000056, VTSS_IO_OFFSET2(0x00560000), reggrps_within_KR_DEV1},
  {"XGKR0"              ,    3, 0x00000057, VTSS_IO_OFFSET2(0x00570000), reggrps_within_KR_DEV1},
  {"XGKR1"              ,    0, 0x00000058, VTSS_IO_OFFSET2(0x00580000), reggrps_within_KR_DEV7},
  {"XGKR1"              ,    1, 0x00000059, VTSS_IO_OFFSET2(0x00590000), reggrps_within_KR_DEV7},
  {"XGKR1"              ,    2, 0x0000005a, VTSS_IO_OFFSET2(0x005a0000), reggrps_within_KR_DEV7},
  {"XGKR1"              ,    3, 0x0000005b, VTSS_IO_OFFSET2(0x005b0000), reggrps_within_KR_DEV7},
  {"XGXFI"              ,    0, 0x00000050, VTSS_IO_OFFSET2(0x00500000), reggrps_within_XFI_SHELL},
  {"XGXFI"              ,    1, 0x00000051, VTSS_IO_OFFSET2(0x00510000), reggrps_within_XFI_SHELL},
  {"XGXFI"              ,    2, 0x00000052, VTSS_IO_OFFSET2(0x00520000), reggrps_within_XFI_SHELL},
  {"XGXFI"              ,    3, 0x00000053, VTSS_IO_OFFSET2(0x00530000), reggrps_within_XFI_SHELL},
};

#define SYMREG_REPL_CNT_MAX 8192
#define SYMREG_NAME_LEN_MAX 50

vtss_rc vtss_symreg_data_get(const vtss_inst_t         inst,
                             vtss_symreg_data_t *const data) {
    data->targets = vtss_symreg_targets;
    data->targets_cnt = sizeof(vtss_symreg_targets) / sizeof(vtss_symreg_targets[0]);
    data->io_origin1_offset = VTSS_IO_ORIGIN1_OFFSET;
    data->repl_cnt_max = SYMREG_REPL_CNT_MAX;
    data->name_len_max = SYMREG_NAME_LEN_MAX;
    return VTSS_RC_OK;
}

#else /* VTSS_OPT_SYMREG */
vtss_rc vtss_symreg_data_get(const vtss_inst_t         inst,
                             vtss_symreg_data_t *const data) {
    return VTSS_RC_ERROR;
}
#endif /* VTSS_OPT_SYMREG */
#endif /* defined(VTSS_ARCH_JAGUAR_2_B) && !defined(VTSS_ARCH_SERVAL_T) */

