/*
 Copyright (c) 2004-2017 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include "vtss_api.h"

#ifdef VTSS_ARCH_LUTON26
#ifdef VTSS_OPT_SYMREG
/*
 * Target offset base(s)
 */
#define VTSS_IO_ORIGIN1_OFFSET 0x60000000
#define VTSS_IO_ORIGIN1_SIZE   0x01000000
#define VTSS_IO_ORIGIN2_OFFSET 0x70000000
#define VTSS_IO_ORIGIN2_SIZE   0x00200000
#ifndef VTSS_IO_OFFSET1
#define VTSS_IO_OFFSET1(offset) (VTSS_IO_ORIGIN1_OFFSET + offset)
#endif
#ifndef VTSS_IO_OFFSET2
#define VTSS_IO_OFFSET2(offset) (VTSS_IO_ORIGIN2_OFFSET + offset)
#endif

static const vtss_symreg_reg_t regs_within_DEVCPU_ORG_ORG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"ERR_ACCESS_DROP"                      , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"ACCESS_TABLE"                         , 0x00000001, 0x00000001, 0x00000001},
#endif
  {"ERR_TGT"                              , 0x00000002, 0x00000001, 0x00000001},
  {"ERR_CNTS"                             , 0x00000003, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"LAST_REPLY_0"                         , 0x00000004, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"LAST_REPLY_1"                         , 0x00000005, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"LAST_REPLY_2"                         , 0x00000006, 0x00000001, 0x00000001},
#endif
  {"CFG_STATUS"                           , 0x00000007, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEVCPU_ORG[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"ORG"                                  , 0x00000000, 0x00000001, 0x00000008, regs_within_DEVCPU_ORG_ORG},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_SYS_SYSTEM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"RESET_CFG"                            , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"CMID"                                 , 0x00000001, 0x00000001, 0x00000001},
#endif
  {"VLAN_ETYPE_CFG"                       , 0x00000002, 0x00000001, 0x00000001},
  {"PORT_MODE"                            , 0x00000003, 0x0000001c, 0x00000001},
  {"FRONT_PORT_MODE"                      , 0x0000001f, 0x0000001a, 0x00000001},
  {"SWITCH_PORT_MODE"                     , 0x00000039, 0x0000001b, 0x00000001},
  {"FRM_AGING"                            , 0x00000054, 0x00000001, 0x00000001},
  {"STAT_CFG"                             , 0x00000055, 0x00000001, 0x00000001},
  {"EEE_CFG"                              , 0x00000056, 0x0000001a, 0x00000001},
  {"EEE_THRES"                            , 0x00000070, 0x00000001, 0x00000001},
  {"IGR_NO_SHARING"                       , 0x00000071, 0x00000001, 0x00000001},
  {"EGR_NO_SHARING"                       , 0x00000072, 0x00000001, 0x00000001},
  {"SW_STATUS"                            , 0x00000073, 0x0000001b, 0x00000001},
  {"EQ_TRUNCATE"                          , 0x0000008e, 0x0000001b, 0x00000001},
  {"EQ_PREFER_SRC"                        , 0x000000a9, 0x00000001, 0x00000001},
  {"EXT_CPU_CFG"                          , 0x000000aa, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SYS_SCH[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"LB_DWRR_FRM_ADJ"                      , 0x00000000, 0x00000001, 0x00000001},
  {"LB_DWRR_CFG"                          , 0x00000001, 0x0000001a, 0x00000001},
  {"SCH_DWRR_CFG"                         , 0x0000001b, 0x0000001a, 0x00000001},
#ifndef VTSS_RELEASE
  {"SCH_DWRR_CTRL"                        , 0x00000035, 0x00000001, 0x00000001},
#endif
  {"SCH_SHAPING_CTRL"                     , 0x00000036, 0x0000001a, 0x00000001},
  {"SCH_LB_CTRL"                          , 0x00000050, 0x00000001, 0x00000001},
  {"SCH_CPU"                              , 0x00000051, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SYS_SCH_LB[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"LB_THRES"                             , 0x00000000, 0x000000ea, 0x00000001},
  {"LB_RATE"                              , 0x00000100, 0x000000ea, 0x00000001},
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_SYS_COREMEM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CM_ADDR"                              , 0x00000000, 0x00000001, 0x00000001},
  {"CM_DATA"                              , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_SYS_RES_CTRL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"RES_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
  {"RES_STAT"                             , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SYS_PAUSE_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PAUSE_CFG"                            , 0x00000000, 0x0000001b, 0x00000001},
  {"PAUSE_TOT_CFG"                        , 0x0000001b, 0x00000001, 0x00000001},
  {"ATOP"                                 , 0x0000001c, 0x0000001b, 0x00000001},
  {"ATOP_TOT_CFG"                         , 0x00000037, 0x00000001, 0x00000001},
  {"EGR_DROP_FORCE"                       , 0x00000038, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SYS_MMGT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MMGT"                                 , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"FD_CTRL"                              , 0x00000001, 0x00000001, 0x00000001},
#endif
  {"EQ_CTRL"                              , 0x00000002, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SYS_MISC[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"PAD_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"EVENTS_DIF"                           , 0x00000001, 0x00000004, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"EVENTS_CORE"                          , 0x00000005, 0x00000001, 0x00000001},
#endif
  {"REPEATER"                             , 0x00000006, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SYS_STAT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CNT"                                  , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SYS_PTP[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PTP_STATUS"                           , 0x00000000, 0x00000001, 0x00000001},
  {"PTP_DELAY"                            , 0x00000001, 0x00000001, 0x00000001},
  {"PTP_CFG"                              , 0x00000002, 0x0000001c, 0x00000001},
  {"PTP_NXT"                              , 0x0000001e, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SYS_POL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"POL_PIR_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
  {"POL_CIR_CFG"                          , 0x00000001, 0x00000001, 0x00000001},
  {"POL_MODE_CFG"                         , 0x00000002, 0x00000001, 0x00000001},
  {"POL_PIR_STATE"                        , 0x00000003, 0x00000001, 0x00000001},
  {"POL_CIR_STATE"                        , 0x00000004, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"POL_STATE"                            , 0x00000005, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SYS_POL_MISC[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"POL_FLOWC"                            , 0x00000000, 0x0000001b, 0x00000001},
  {"POL_HYST"                             , 0x0000001b, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"POL_MISC_CFG"                         , 0x0000001c, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SYS_ISHP[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"ISHP_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
  {"ISHP_MODE_CFG"                        , 0x00000001, 0x00000001, 0x00000001},
  {"ISHP_STATE"                           , 0x00000002, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_SYS[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"SYSTEM"                               , 0x0000206c, 0x00000001, 0x000000ab, regs_within_SYS_SYSTEM},
  {"SCH"                                  , 0x00002117, 0x00000001, 0x00000052, regs_within_SYS_SCH},
  {"SCH_LB"                               , 0x00000e00, 0x00000001, 0x00000200, regs_within_SYS_SCH_LB},
#ifndef VTSS_RELEASE
  {"COREMEM"                              , 0x00000de6, 0x00000001, 0x00000002, regs_within_SYS_COREMEM},
#endif
  {"RES_CTRL"                             , 0x00001000, 0x00000400, 0x00000002, regs_within_SYS_RES_CTRL},
  {"PAUSE_CFG"                            , 0x00002169, 0x00000001, 0x00000039, regs_within_SYS_PAUSE_CFG},
  {"MMGT"                                 , 0x00000de8, 0x00000001, 0x00000003, regs_within_SYS_MMGT},
  {"MISC"                                 , 0x00000deb, 0x00000001, 0x00000007, regs_within_SYS_MISC},
  {"STAT"                                 , 0x00000000, 0x00000de6, 0x00000001, regs_within_SYS_STAT},
  {"PTP"                                  , 0x000021a2, 0x00000001, 0x0000001f, regs_within_SYS_PTP},
  {"POL"                                  , 0x00001800, 0x00000100, 0x00000008, regs_within_SYS_POL},
  {"POL_MISC"                             , 0x000021c1, 0x00000001, 0x0000001d, regs_within_SYS_POL_MISC},
  {"ISHP"                                 , 0x00002000, 0x0000001b, 0x00000004, regs_within_SYS_ISHP},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_ANA_ANA[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"ADVLEARN"                             , 0x00000000, 0x00000001, 0x00000001},
  {"VLANMASK"                             , 0x00000001, 0x00000001, 0x00000001},
  {"ANAGEFIL"                             , 0x00000002, 0x00000001, 0x00000001},
  {"ANEVENTS"                             , 0x00000003, 0x00000001, 0x00000001},
  {"STORMLIMIT_BURST"                     , 0x00000004, 0x00000001, 0x00000001},
  {"STORMLIMIT_CFG"                       , 0x00000005, 0x00000004, 0x00000001},
  {"ISOLATED_PORTS"                       , 0x00000009, 0x00000001, 0x00000001},
  {"COMMUNITY_PORTS"                      , 0x0000000a, 0x00000001, 0x00000001},
  {"AUTOAGE"                              , 0x0000000b, 0x00000001, 0x00000001},
  {"MACTOPTIONS"                          , 0x0000000c, 0x00000001, 0x00000001},
  {"LEARNDISC"                            , 0x0000000d, 0x00000001, 0x00000001},
  {"AGENCTRL"                             , 0x0000000e, 0x00000001, 0x00000001},
  {"MIRRORPORTS"                          , 0x0000000f, 0x00000001, 0x00000001},
  {"EMIRRORPORTS"                         , 0x00000010, 0x00000001, 0x00000001},
  {"FLOODING"                             , 0x00000011, 0x00000001, 0x00000001},
  {"FLOODING_IPMC"                        , 0x00000012, 0x00000001, 0x00000001},
  {"SFLOW_CFG"                            , 0x00000013, 0x0000001b, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_ANA_TABLES[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"ANMOVED"                              , 0x0000006b, 0x00000001, 0x00000001},
  {"MACHDATA"                             , 0x0000006c, 0x00000001, 0x00000001},
  {"MACLDATA"                             , 0x0000006d, 0x00000001, 0x00000001},
  {"MACACCESS"                            , 0x0000006e, 0x00000001, 0x00000001},
  {"MACTINDX"                             , 0x0000006f, 0x00000001, 0x00000001},
  {"VLANACCESS"                           , 0x00000070, 0x00000001, 0x00000001},
  {"VLANTIDX"                             , 0x00000071, 0x00000001, 0x00000001},
  {"PGID"                                 , 0x00000000, 0x0000006b, 0x00000001},
  {"ENTRYLIM"                             , 0x00000080, 0x0000001b, 0x00000001},
  {"PTP_ID_HIGH"                          , 0x00000072, 0x00000001, 0x00000001},
  {"PTP_ID_LOW"                           , 0x00000073, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_PORT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"VLAN_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
  {"DROP_CFG"                             , 0x00000001, 0x00000001, 0x00000001},
  {"QOS_CFG"                              , 0x00000002, 0x00000001, 0x00000001},
  {"VCAP_CFG"                             , 0x00000003, 0x00000001, 0x00000001},
  {"QOS_PCP_DEI_MAP_CFG"                  , 0x00000004, 0x00000010, 0x00000001},
  {"CPU_FWD_CFG"                          , 0x00000014, 0x00000001, 0x00000001},
  {"CPU_FWD_BPDU_CFG"                     , 0x00000015, 0x00000001, 0x00000001},
  {"CPU_FWD_GARP_CFG"                     , 0x00000016, 0x00000001, 0x00000001},
  {"CPU_FWD_CCM_CFG"                      , 0x00000017, 0x00000001, 0x00000001},
  {"PORT_CFG"                             , 0x00000018, 0x00000001, 0x00000001},
  {"POL_CFG"                              , 0x00000019, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_COMMON[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"AGGR_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
  {"CPUQ_CFG"                             , 0x00000001, 0x00000001, 0x00000001},
  {"CPUQ_8021_CFG"                        , 0x00000002, 0x00000010, 0x00000001},
  {"DSCP_CFG"                             , 0x00000012, 0x00000040, 0x00000001},
  {"DSCP_REWR_CFG"                        , 0x00000052, 0x00000010, 0x00000001},
  {"VCAP_RNG_TYPE_CFG"                    , 0x00000062, 0x00000008, 0x00000001},
  {"VCAP_RNG_VAL_CFG"                     , 0x0000006a, 0x00000008, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_ANA[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"ANA"                                  , 0x00000360, 0x00000001, 0x0000002e, regs_within_ANA_ANA},
  {"ANA_TABLES"                           , 0x00000400, 0x00000001, 0x00000100, regs_within_ANA_ANA_TABLES},
  {"PORT"                                 , 0x00000000, 0x0000001b, 0x00000020, regs_within_ANA_PORT},
  {"COMMON"                               , 0x0000038e, 0x00000001, 0x00000072, regs_within_ANA_COMMON},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_REW_PORT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PORT_VLAN_CFG"                        , 0x00000000, 0x00000001, 0x00000001},
  {"TAG_CFG"                              , 0x00000001, 0x00000001, 0x00000001},
  {"PORT_CFG"                             , 0x00000002, 0x00000001, 0x00000001},
  {"DSCP_CFG"                             , 0x00000003, 0x00000001, 0x00000001},
  {"PCP_DEI_QOS_MAP_CFG"                  , 0x00000004, 0x00000010, 0x00000001},
#ifndef VTSS_RELEASE
  {"PTP_CFG"                              , 0x00000014, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_COMMON[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"DSCP_REMAP_DP1_CFG"                   , 0x00000000, 0x00000040, 0x00000001},
  {"DSCP_REMAP_CFG"                       , 0x00000040, 0x00000040, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_REW[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"PORT"                                 , 0x00000000, 0x0000001c, 0x00000020, regs_within_REW_PORT},
  {"COMMON"                               , 0x00000380, 0x00000001, 0x00000080, regs_within_REW_COMMON},
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
  {"VCAP_ENTRY_DAT"                       , 0x00000000, 0x00000020, 0x00000001},
  {"VCAP_MASK_DAT"                        , 0x00000020, 0x00000020, 0x00000001},
  {"VCAP_ACTION_DAT"                      , 0x00000040, 0x00000020, 0x00000001},
  {"VCAP_CNT_DAT"                         , 0x00000060, 0x00000020, 0x00000001},
  {"VCAP_TG_DAT"                          , 0x00000080, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_CORE_VCAP_CORE_STICKY[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"VCAP_STICKY"                          , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_CORE_VCAP_CONST[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"ENTRY_WIDTH"                          , 0x00000000, 0x00000001, 0x00000001},
  {"ENTRY_CNT"                            , 0x00000001, 0x00000001, 0x00000001},
  {"ENTRY_SWCNT"                          , 0x00000002, 0x00000001, 0x00000001},
  {"ENTRY_TG_WIDTH"                       , 0x00000003, 0x00000001, 0x00000001},
  {"ACTION_DEF_CNT"                       , 0x00000004, 0x00000001, 0x00000001},
  {"ACTION_WIDTH"                         , 0x00000005, 0x00000001, 0x00000001},
  {"CNT_WIDTH"                            , 0x00000006, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_VCAP_CORE_TCAM_BIST[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TCAM_CTRL"                            , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"TCAM_CFG"                             , 0x00000001, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"TCAM_CLK_SKEW"                        , 0x00000002, 0x00000001, 0x00000001},
#endif
  {"TCAM_STAT"                            , 0x00000003, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_VCAP_CORE[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"VCAP_CORE_CFG"                        , 0x00000000, 0x00000001, 0x00000002, regs_within_VCAP_CORE_VCAP_CORE_CFG},
  {"VCAP_CORE_CACHE"                      , 0x00000002, 0x00000001, 0x00000081, regs_within_VCAP_CORE_VCAP_CORE_CACHE},
  {"VCAP_CORE_STICKY"                     , 0x00000083, 0x00000001, 0x00000001, regs_within_VCAP_CORE_VCAP_CORE_STICKY},
  {"VCAP_CONST"                           , 0x00000084, 0x00000001, 0x00000007, regs_within_VCAP_CORE_VCAP_CONST},
  {"TCAM_BIST"                            , 0x0000008b, 0x00000001, 0x00000004, regs_within_VCAP_CORE_TCAM_BIST},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_CHIP_REGS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"GENERAL_PURPOSE"                      , 0x00000000, 0x00000001, 0x00000001},
  {"SI"                                   , 0x00000001, 0x00000001, 0x00000001},
  {"CHIP_ID"                              , 0x00000002, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"HW_STAT"                              , 0x00000003, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_DBG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"QS_DBG"                               , 0x00000000, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_SW_REGS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SEMA_INTR_ENA"                        , 0x00000000, 0x00000001, 0x00000001},
  {"SEMA_INTR_ENA_CLR"                    , 0x00000001, 0x00000001, 0x00000001},
  {"SEMA_INTR_ENA_SET"                    , 0x00000002, 0x00000001, 0x00000001},
  {"SEMA"                                 , 0x00000003, 0x00000008, 0x00000001},
  {"SEMA_FREE"                            , 0x0000000b, 0x00000001, 0x00000001},
  {"SW_INTR"                              , 0x0000000c, 0x00000001, 0x00000001},
  {"MAILBOX"                              , 0x0000000d, 0x00000001, 0x00000001},
  {"MAILBOX_CLR"                          , 0x0000000e, 0x00000001, 0x00000001},
  {"MAILBOX_SET"                          , 0x0000000f, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
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
  {"GPIO_OUT_CLR"                         , 0x00000001, 0x00000001, 0x00000001},
  {"GPIO_OUT"                             , 0x00000002, 0x00000001, 0x00000001},
  {"GPIO_IN"                              , 0x00000003, 0x00000001, 0x00000001},
  {"GPIO_OE"                              , 0x00000004, 0x00000001, 0x00000001},
  {"GPIO_INTR"                            , 0x00000005, 0x00000001, 0x00000001},
  {"GPIO_INTR_ENA"                        , 0x00000006, 0x00000001, 0x00000001},
  {"GPIO_INTR_IDENT"                      , 0x00000007, 0x00000001, 0x00000001},
  {"GPIO_ALT"                             , 0x00000008, 0x00000002, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_DEVCPU_RST_REGS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SOFT_CHIP_RST"                        , 0x00000000, 0x00000001, 0x00000001},
  {"SOFT_DEVCPU_RST"                      , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_ALIGN[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"WD_SETUP"                             , 0x00000000, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"DBG"                                  , 0x00000001, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#endif
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
  {"MII_SCAN_RSLTS_STICKY"                , 0x00000000, 0x00000002, 0x00000001},
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_FEATURES[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"FEA_STAT"                             , 0x00000000, 0x00000008, 0x00000001},
#ifndef VTSS_RELEASE
  {"FEA_DIS"                              , 0x00000008, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_RAM_STAT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"RAM_INTEGRITY_ERR_STICKY"             , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_MISC[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MISC_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
  {"MISC_STAT"                            , 0x00000001, 0x00000001, 0x00000001},
  {"PHY_SPEED_1000_STAT"                  , 0x00000002, 0x00000001, 0x00000001},
  {"PHY_SPEED_100_STAT"                   , 0x00000003, 0x00000001, 0x00000001},
  {"PHY_SPEED_10_STAT"                    , 0x00000004, 0x00000001, 0x00000001},
  {"DUPLEXC_PORT_STAT"                    , 0x00000005, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_SIO_CTRL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SIO_INPUT_DATA"                       , 0x00000000, 0x00000004, 0x00000001},
  {"SIO_INT_POL"                          , 0x00000004, 0x00000004, 0x00000001},
  {"SIO_PORT_INT_ENA"                     , 0x00000008, 0x00000001, 0x00000001},
  {"SIO_PORT_CONFIG"                      , 0x00000009, 0x00000020, 0x00000001},
  {"SIO_PORT_ENABLE"                      , 0x00000029, 0x00000001, 0x00000001},
  {"SIO_CONFIG"                           , 0x0000002a, 0x00000001, 0x00000001},
  {"SIO_CLOCK"                            , 0x0000002b, 0x00000001, 0x00000001},
  {"SIO_INT_REG"                          , 0x0000002c, 0x00000004, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_FAN_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"FAN_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_FAN_STAT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"FAN_CNT"                              , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_PTP_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PTP_MISC_CFG"                         , 0x00000000, 0x00000001, 0x00000001},
  {"PTP_UPPER_LIMIT_CFG"                  , 0x00000001, 0x00000001, 0x00000001},
  {"PTP_UPPER_LIMIT_1_TIME_ADJ_CFG"       , 0x00000002, 0x00000001, 0x00000001},
  {"PTP_SYNC_INTR_ENA_CFG"                , 0x00000003, 0x00000001, 0x00000001},
  {"GEN_EXT_CLK_HIGH_PERIOD_CFG"          , 0x00000004, 0x00000001, 0x00000001},
  {"GEN_EXT_CLK_LOW_PERIOD_CFG"           , 0x00000005, 0x00000001, 0x00000001},
  {"GEN_EXT_CLK_CFG"                      , 0x00000006, 0x00000001, 0x00000001},
  {"CLK_ADJ_CFG"                          , 0x00000007, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_PTP_STAT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PTP_CURRENT_TIME_STAT"                , 0x00000000, 0x00000001, 0x00000001},
  {"EXT_SYNC_CURRENT_TIME_STAT"           , 0x00000001, 0x00000001, 0x00000001},
  {"PTP_EVT_STAT"                         , 0x00000002, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_PTP_TIMERS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PTP_TOD_SECS"                         , 0x00000000, 0x00000001, 0x00000001},
  {"PTP_TOD_NANOSECS"                     , 0x00000001, 0x00000001, 0x00000001},
  {"PTP_DELAY"                            , 0x00000002, 0x00000001, 0x00000001},
  {"PTP_TIMER_CTRL"                       , 0x00000003, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_MEMITGR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MEMITGR_CTRL"                         , 0x00000000, 0x00000001, 0x00000001},
  {"MEMITGR_STAT"                         , 0x00000001, 0x00000001, 0x00000001},
  {"MEMITGR_INFO"                         , 0x00000002, 0x00000001, 0x00000001},
  {"MEMITGR_IDX"                          , 0x00000003, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"MEMITGR_DIV"                          , 0x00000004, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"MEMITGR_DBG"                          , 0x00000005, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEVCPU_GCB[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"CHIP_REGS"                            , 0x00000000, 0x00000001, 0x00000004, regs_within_DEVCPU_GCB_CHIP_REGS},
#ifndef VTSS_RELEASE
  {"DBG"                                  , 0x00000004, 0x00000001, 0x00000001, regs_within_DEVCPU_GCB_DBG},
#endif
  {"SW_REGS"                              , 0x00000005, 0x00000001, 0x00000010, regs_within_DEVCPU_GCB_SW_REGS},
  {"VCORE_ACCESS"                         , 0x00000015, 0x00000001, 0x00000005, regs_within_DEVCPU_GCB_VCORE_ACCESS},
  {"GPIO"                                 , 0x0000001a, 0x00000001, 0x0000000a, regs_within_DEVCPU_GCB_GPIO},
  {"DEVCPU_RST_REGS"                      , 0x00000024, 0x00000001, 0x00000002, regs_within_DEVCPU_GCB_DEVCPU_RST_REGS},
#ifndef VTSS_RELEASE
  {"ALIGN"                                , 0x00000026, 0x00000001, 0x00000002, regs_within_DEVCPU_GCB_ALIGN},
#endif
  {"MIIM"                                 , 0x00000028, 0x00000002, 0x00000009, regs_within_DEVCPU_GCB_MIIM},
  {"MIIM_READ_SCAN"                       , 0x0000003a, 0x00000001, 0x00000002, regs_within_DEVCPU_GCB_MIIM_READ_SCAN},
#ifndef VTSS_RELEASE
  {"FEATURES"                             , 0x0000003c, 0x00000001, 0x00000009, regs_within_DEVCPU_GCB_FEATURES},
#endif
  {"RAM_STAT"                             , 0x00000045, 0x00000001, 0x00000001, regs_within_DEVCPU_GCB_RAM_STAT},
  {"MISC"                                 , 0x00000046, 0x00000001, 0x00000006, regs_within_DEVCPU_GCB_MISC},
  {"SIO_CTRL"                             , 0x0000004c, 0x00000001, 0x00000030, regs_within_DEVCPU_GCB_SIO_CTRL},
  {"FAN_CFG"                              , 0x0000007c, 0x00000001, 0x00000001, regs_within_DEVCPU_GCB_FAN_CFG},
  {"FAN_STAT"                             , 0x0000007d, 0x00000001, 0x00000001, regs_within_DEVCPU_GCB_FAN_STAT},
  {"PTP_CFG"                              , 0x0000007e, 0x00000001, 0x00000008, regs_within_DEVCPU_GCB_PTP_CFG},
  {"PTP_STAT"                             , 0x00000086, 0x00000001, 0x00000003, regs_within_DEVCPU_GCB_PTP_STAT},
  {"PTP_TIMERS"                           , 0x00000089, 0x00000001, 0x00000004, regs_within_DEVCPU_GCB_PTP_TIMERS},
  {"MEMITGR"                              , 0x0000008d, 0x00000001, 0x00000006, regs_within_DEVCPU_GCB_MEMITGR},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_QS_XTR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"XTR_FRM_PRUNING"                      , 0x00000000, 0x00000002, 0x00000001},
  {"XTR_GRP_CFG"                          , 0x00000002, 0x00000002, 0x00000001},
  {"XTR_MAP"                              , 0x00000004, 0x00000002, 0x00000001},
  {"XTR_RD"                               , 0x00000006, 0x00000002, 0x00000001},
#ifndef VTSS_RELEASE
  {"XTR_QU_SEL"                           , 0x00000008, 0x00000002, 0x00000001},
#endif
  {"XTR_QU_FLUSH"                         , 0x0000000a, 0x00000001, 0x00000001},
  {"XTR_DATA_PRESENT"                     , 0x0000000b, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"XTR_QU_DBG"                           , 0x0000000c, 0x00000001, 0x00000001},
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
  {"XTR"                                  , 0x00000000, 0x00000001, 0x0000000d, regs_within_DEVCPU_QS_XTR},
  {"INJ"                                  , 0x0000000d, 0x00000001, 0x0000000a, regs_within_DEVCPU_QS_INJ},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_PI_PI[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PI_CTRL"                              , 0x00000000, 0x00000001, 0x00000001},
  {"PI_CFG"                               , 0x00000001, 0x00000001, 0x00000001},
  {"PI_STAT"                              , 0x00000002, 0x00000001, 0x00000001},
  {"PI_MODE"                              , 0x00000003, 0x00000001, 0x00000001},
  {"PI_SLOW_DATA"                         , 0x00000004, 0x00000002, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEVCPU_PI[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"PI"                                   , 0x00000000, 0x00000001, 0x00000006, regs_within_DEVCPU_PI_PI},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_MACRO_CTRL_PLL5G_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PLL5G_CFG0"                           , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"PLL5G_CFG1"                           , 0x00000001, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PLL5G_CFG2"                           , 0x00000002, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PLL5G_CFG3"                           , 0x00000003, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PLL5G_CFG4"                           , 0x00000004, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PLL5G_CFG5"                           , 0x00000005, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MACRO_CTRL_PLL5G_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PLL5G_STATUS0"                        , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"PLL5G_STATUS1"                        , 0x00000001, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_MACRO_CTRL_RCOMP_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"RCOMP_CFG0"                           , 0x00000000, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_MACRO_CTRL_RCOMP_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"RCOMP_STATUS"                         , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MACRO_CTRL_SYNC_ETH_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SYNC_ETH_CFG"                         , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MACRO_CTRL_SERDES1G_ANA_CFG[] = {
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
static const vtss_symreg_reg_t regs_within_MACRO_CTRL_SERDES1G_ANA_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"SERDES1G_PLL_STATUS"                  , 0x00000000, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_MACRO_CTRL_SERDES1G_DIG_CFG[] = {
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
  {"SERDES1G_MISC_CFG"                    , 0x00000004, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MACRO_CTRL_SERDES1G_DIG_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SERDES1G_DFT_STATUS"                  , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MACRO_CTRL_MCB_SERDES1G_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MCB_SERDES1G_ADDR_CFG"                , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MACRO_CTRL_SERDES6G_ANA_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SERDES6G_DES_CFG"                     , 0x00000000, 0x00000001, 0x00000001},
  {"SERDES6G_IB_CFG"                      , 0x00000001, 0x00000001, 0x00000001},
  {"SERDES6G_IB_CFG1"                     , 0x00000002, 0x00000001, 0x00000001},
  {"SERDES6G_OB_CFG"                      , 0x00000003, 0x00000001, 0x00000001},
  {"SERDES6G_OB_CFG1"                     , 0x00000004, 0x00000001, 0x00000001},
  {"SERDES6G_SER_CFG"                     , 0x00000005, 0x00000001, 0x00000001},
  {"SERDES6G_COMMON_CFG"                  , 0x00000006, 0x00000001, 0x00000001},
  {"SERDES6G_PLL_CFG"                     , 0x00000007, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_MACRO_CTRL_SERDES6G_ANA_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"SERDES6G_PLL_STATUS"                  , 0x00000000, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_MACRO_CTRL_SERDES6G_DIG_CFG[] = {
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
  {"SERDES6G_MISC_CFG"                    , 0x00000006, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"SERDES6G_OB_ANEG_CFG"                 , 0x00000007, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_MACRO_CTRL_SERDES6G_DIG_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"SERDES6G_DFT_STATUS"                  , 0x00000000, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_MACRO_CTRL_MCB_SERDES6G_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MCB_SERDES6G_ADDR_CFG"                , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_MACRO_CTRL[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"PLL5G_CFG"                            , 0x00000000, 0x00000001, 0x00000006, regs_within_MACRO_CTRL_PLL5G_CFG},
  {"PLL5G_STATUS"                         , 0x00000006, 0x00000001, 0x00000002, regs_within_MACRO_CTRL_PLL5G_STATUS},
#ifndef VTSS_RELEASE
  {"RCOMP_CFG"                            , 0x00000008, 0x00000001, 0x00000001, regs_within_MACRO_CTRL_RCOMP_CFG},
#endif
  {"RCOMP_STATUS"                         , 0x00000009, 0x00000001, 0x00000001, regs_within_MACRO_CTRL_RCOMP_STATUS},
  {"SYNC_ETH_CFG"                         , 0x0000000a, 0x00000001, 0x00000001, regs_within_MACRO_CTRL_SYNC_ETH_CFG},
  {"SERDES1G_ANA_CFG"                     , 0x0000000b, 0x00000001, 0x00000006, regs_within_MACRO_CTRL_SERDES1G_ANA_CFG},
#ifndef VTSS_RELEASE
  {"SERDES1G_ANA_STATUS"                  , 0x00000011, 0x00000001, 0x00000001, regs_within_MACRO_CTRL_SERDES1G_ANA_STATUS},
#endif
  {"SERDES1G_DIG_CFG"                     , 0x00000012, 0x00000001, 0x00000005, regs_within_MACRO_CTRL_SERDES1G_DIG_CFG},
  {"SERDES1G_DIG_STATUS"                  , 0x00000017, 0x00000001, 0x00000001, regs_within_MACRO_CTRL_SERDES1G_DIG_STATUS},
  {"MCB_SERDES1G_CFG"                     , 0x00000018, 0x00000001, 0x00000001, regs_within_MACRO_CTRL_MCB_SERDES1G_CFG},
  {"SERDES6G_ANA_CFG"                     , 0x00000019, 0x00000001, 0x00000008, regs_within_MACRO_CTRL_SERDES6G_ANA_CFG},
#ifndef VTSS_RELEASE
  {"SERDES6G_ANA_STATUS"                  , 0x00000021, 0x00000001, 0x00000001, regs_within_MACRO_CTRL_SERDES6G_ANA_STATUS},
#endif
  {"SERDES6G_DIG_CFG"                     , 0x00000022, 0x00000001, 0x00000008, regs_within_MACRO_CTRL_SERDES6G_DIG_CFG},
#ifndef VTSS_RELEASE
  {"SERDES6G_DIG_STATUS"                  , 0x0000002a, 0x00000001, 0x00000001, regs_within_MACRO_CTRL_SERDES6G_DIG_STATUS},
#endif
  {"MCB_SERDES6G_CFG"                     , 0x0000002b, 0x00000001, 0x00000001, regs_within_MACRO_CTRL_MCB_SERDES6G_CFG},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_GMII_PORT_MODE[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CLOCK_CFG"                            , 0x00000000, 0x00000001, 0x00000001},
  {"PORT_MISC"                            , 0x00000001, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"EVENTS"                               , 0x00000002, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV_GMII_MAC_CFG_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MAC_ENA_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
  {"MAC_MODE_CFG"                         , 0x00000001, 0x00000001, 0x00000001},
  {"MAC_MAXLEN_CFG"                       , 0x00000002, 0x00000001, 0x00000001},
  {"MAC_TAGS_CFG"                         , 0x00000003, 0x00000001, 0x00000001},
  {"MAC_ADV_CHK_CFG"                      , 0x00000004, 0x00000001, 0x00000001},
  {"MAC_IFG_CFG"                          , 0x00000005, 0x00000001, 0x00000001},
  {"MAC_HDX_CFG"                          , 0x00000006, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"MAC_DBG_CFG"                          , 0x00000007, 0x00000001, 0x00000001},
#endif
  {"MAC_FC_CFG"                           , 0x00000008, 0x00000001, 0x00000001},
  {"MAC_FC_MAC_LOW_CFG"                   , 0x00000009, 0x00000001, 0x00000001},
  {"MAC_FC_MAC_HIGH_CFG"                  , 0x0000000a, 0x00000001, 0x00000001},
  {"MAC_STICKY"                           , 0x0000000b, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV_GMII[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"PORT_MODE"                            , 0x00000000, 0x00000001, 0x00000003, regs_within_DEV_GMII_PORT_MODE},
  {"MAC_CFG_STATUS"                       , 0x00000003, 0x00000001, 0x0000000c, regs_within_DEV_GMII_MAC_CFG_STATUS},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_DEV_CFG_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"DEV_IF_CFG"                           , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV_PORT_MODE[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CLOCK_CFG"                            , 0x00000000, 0x00000001, 0x00000001},
  {"PORT_MISC"                            , 0x00000001, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"EVENTS"                               , 0x00000002, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV_MAC_CFG_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MAC_ENA_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
  {"MAC_MODE_CFG"                         , 0x00000001, 0x00000001, 0x00000001},
  {"MAC_MAXLEN_CFG"                       , 0x00000002, 0x00000001, 0x00000001},
  {"MAC_TAGS_CFG"                         , 0x00000003, 0x00000001, 0x00000001},
  {"MAC_ADV_CHK_CFG"                      , 0x00000004, 0x00000001, 0x00000001},
  {"MAC_IFG_CFG"                          , 0x00000005, 0x00000001, 0x00000001},
  {"MAC_HDX_CFG"                          , 0x00000006, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"MAC_DBG_CFG"                          , 0x00000007, 0x00000001, 0x00000001},
#endif
  {"MAC_FC_CFG"                           , 0x00000008, 0x00000001, 0x00000001},
  {"MAC_FC_MAC_LOW_CFG"                   , 0x00000009, 0x00000001, 0x00000001},
  {"MAC_FC_MAC_HIGH_CFG"                  , 0x0000000a, 0x00000001, 0x00000001},
  {"MAC_STICKY"                           , 0x0000000b, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV_PCS1G_CFG_STATUS[] = {
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
#ifndef VTSS_RELEASE
  {"PCS1G_DEBUG_STATUS"                   , 0x0000000d, 0x00000001, 0x00000001},
#endif
  {"PCS1G_LPI_CFG"                        , 0x0000000e, 0x00000001, 0x00000001},
  {"PCS1G_LPI_WAKE_ERROR_CNT"             , 0x0000000f, 0x00000001, 0x00000001},
  {"PCS1G_LPI_STATUS"                     , 0x00000010, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV_PCS1G_TSTPAT_CFG_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PCS1G_TSTPAT_MODE_CFG"                , 0x00000000, 0x00000001, 0x00000001},
  {"PCS1G_TSTPAT_STATUS"                  , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV_PCS_FX100_CONFIGURATION[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PCS_FX100_CFG"                        , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV_PCS_FX100_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PCS_FX100_STATUS"                     , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"DEV_CFG_STATUS"                       , 0x00000000, 0x00000001, 0x00000001, regs_within_DEV_DEV_CFG_STATUS},
  {"PORT_MODE"                            , 0x00000001, 0x00000001, 0x00000003, regs_within_DEV_PORT_MODE},
  {"MAC_CFG_STATUS"                       , 0x00000004, 0x00000001, 0x0000000c, regs_within_DEV_MAC_CFG_STATUS},
  {"PCS1G_CFG_STATUS"                     , 0x00000010, 0x00000001, 0x00000011, regs_within_DEV_PCS1G_CFG_STATUS},
  {"PCS1G_TSTPAT_CFG_STATUS"              , 0x00000021, 0x00000001, 0x00000002, regs_within_DEV_PCS1G_TSTPAT_CFG_STATUS},
  {"PCS_FX100_CONFIGURATION"              , 0x00000023, 0x00000001, 0x00000001, regs_within_DEV_PCS_FX100_CONFIGURATION},
  {"PCS_FX100_STATUS"                     , 0x00000024, 0x00000001, 0x00000001, regs_within_DEV_PCS_FX100_STATUS},
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
static const vtss_symreg_reg_t regs_within_ICPU_CFG_PI_MST[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PI_MST_CFG"                           , 0x00000000, 0x00000001, 0x00000001},
  {"PI_MST_CTRL"                          , 0x00000001, 0x00000004, 0x00000001},
  {"PI_MST_STATUS"                        , 0x00000005, 0x00000004, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ICPU_CFG_SPI_MST[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SPI_MST_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"SPI_MST_STATUS"                       , 0x00000001, 0x00000004, 0x00000001},
#endif
  {"SW_MODE"                              , 0x00000005, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
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
  {"MPU8051_TIMER_CLK_DIV"                , 0x00000006, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ICPU_CFG_INTR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"INTR"                                 , 0x00000000, 0x00000001, 0x00000001},
  {"INTR_ENA"                             , 0x00000001, 0x00000001, 0x00000001},
  {"INTR_ENA_CLR"                         , 0x00000002, 0x00000001, 0x00000001},
  {"INTR_ENA_SET"                         , 0x00000003, 0x00000001, 0x00000001},
  {"INTR_RAW"                             , 0x00000004, 0x00000001, 0x00000001},
  {"ICPU_IRQ0_ENA"                        , 0x00000005, 0x00000001, 0x00000001},
  {"ICPU_IRQ0_IDENT"                      , 0x00000006, 0x00000001, 0x00000001},
  {"ICPU_IRQ1_ENA"                        , 0x00000007, 0x00000001, 0x00000001},
  {"ICPU_IRQ1_IDENT"                      , 0x00000008, 0x00000001, 0x00000001},
  {"EXT_IRQ0_ENA"                         , 0x00000009, 0x00000001, 0x00000001},
  {"EXT_IRQ0_IDENT"                       , 0x0000000a, 0x00000001, 0x00000001},
  {"EXT_IRQ1_ENA"                         , 0x0000000b, 0x00000001, 0x00000001},
  {"EXT_IRQ1_IDENT"                       , 0x0000000c, 0x00000001, 0x00000001},
  {"DEV_IDENT"                            , 0x0000000d, 0x00000001, 0x00000001},
  {"EXT_IRQ0_INTR_CFG"                    , 0x0000000e, 0x00000001, 0x00000001},
  {"EXT_IRQ1_INTR_CFG"                    , 0x0000000f, 0x00000001, 0x00000001},
  {"SW0_INTR_CFG"                         , 0x00000010, 0x00000001, 0x00000001},
  {"SW1_INTR_CFG"                         , 0x00000011, 0x00000001, 0x00000001},
  {"MIIM1_INTR_CFG"                       , 0x00000012, 0x00000001, 0x00000001},
  {"MIIM0_INTR_CFG"                       , 0x00000013, 0x00000001, 0x00000001},
  {"PI_SD0_INTR_CFG"                      , 0x00000014, 0x00000001, 0x00000001},
  {"PI_SD1_INTR_CFG"                      , 0x00000015, 0x00000001, 0x00000001},
  {"UART_INTR_CFG"                        , 0x00000016, 0x00000001, 0x00000001},
  {"TIMER0_INTR_CFG"                      , 0x00000017, 0x00000001, 0x00000001},
  {"TIMER1_INTR_CFG"                      , 0x00000018, 0x00000001, 0x00000001},
  {"TIMER2_INTR_CFG"                      , 0x00000019, 0x00000001, 0x00000001},
  {"FDMA_INTR_CFG"                        , 0x0000001a, 0x00000001, 0x00000001},
  {"TWI_INTR_CFG"                         , 0x0000001b, 0x00000001, 0x00000001},
  {"GPIO_INTR_CFG"                        , 0x0000001c, 0x00000001, 0x00000001},
  {"SGPIO_INTR_CFG"                       , 0x0000001d, 0x00000001, 0x00000001},
  {"DEV_ALL_INTR_CFG"                     , 0x0000001e, 0x00000001, 0x00000001},
  {"BLK_ANA_INTR_CFG"                     , 0x0000001f, 0x00000001, 0x00000001},
  {"XTR_RDY0_INTR_CFG"                    , 0x00000020, 0x00000001, 0x00000001},
  {"XTR_RDY1_INTR_CFG"                    , 0x00000021, 0x00000001, 0x00000001},
  {"XTR_RDY2_INTR_CFG"                    , 0x00000022, 0x00000001, 0x00000001},
  {"XTR_RDY3_INTR_CFG"                    , 0x00000023, 0x00000001, 0x00000001},
  {"INJ_RDY0_INTR_CFG"                    , 0x00000024, 0x00000001, 0x00000001},
  {"INJ_RDY1_INTR_CFG"                    , 0x00000025, 0x00000001, 0x00000001},
  {"INJ_RDY2_INTR_CFG"                    , 0x00000026, 0x00000001, 0x00000001},
  {"INJ_RDY3_INTR_CFG"                    , 0x00000027, 0x00000001, 0x00000001},
  {"INJ_RDY4_INTR_CFG"                    , 0x00000028, 0x00000001, 0x00000001},
  {"INTEGRITY_INTR_CFG"                   , 0x00000029, 0x00000001, 0x00000001},
  {"PTP_SYNC_INTR_CFG"                    , 0x0000002a, 0x00000001, 0x00000001},
  {"DEV_ENA"                              , 0x0000002b, 0x00000001, 0x00000001},
  {"DEV_POL"                              , 0x0000002c, 0x00000001, 0x00000001},
  {"DEV_IDENT_STICKY"                     , 0x0000002d, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ICPU_CFG_GPDMA[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"FDMA_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"FDMA_STAT"                            , 0x00000001, 0x00000001, 0x00000001},
#endif
  {"FDMA_CH_CFG"                          , 0x00000002, 0x00000008, 0x00000001},
  {"FDMA_INJ_CFG"                         , 0x0000000a, 0x00000002, 0x00000001},
  {"FDMA_XTR_CFG"                         , 0x0000000c, 0x00000002, 0x00000001},
  {"FDMA_XTR_STAT_LAST_DCB"               , 0x0000000e, 0x00000002, 0x00000001},
  {"FDMA_FRM_CNT"                         , 0x00000010, 0x00000001, 0x00000001},
  {"FDMA_BP_TO_INT"                       , 0x00000011, 0x00000001, 0x00000001},
  {"FDMA_BP_TO_DIV"                       , 0x00000012, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ICPU_CFG_INJ_FRM_SPC[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"INJ_FRM_SPC_TMR"                      , 0x00000000, 0x00000001, 0x00000001},
  {"INJ_FRM_SPC_TMR_CFG"                  , 0x00000001, 0x00000001, 0x00000001},
  {"INJ_FRM_SPC_LACK_CNTR"                , 0x00000002, 0x00000001, 0x00000001},
  {"INJ_FRM_SPC_CFG"                      , 0x00000003, 0x00000001, 0x00000001},
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
#ifndef VTSS_RELEASE
  {"MEMCTRL_ZQCAL"                        , 0x00000004, 0x00000001, 0x00000001},
#endif
  {"MEMCTRL_TIMING0"                      , 0x00000005, 0x00000001, 0x00000001},
  {"MEMCTRL_TIMING1"                      , 0x00000006, 0x00000001, 0x00000001},
  {"MEMCTRL_TIMING2"                      , 0x00000007, 0x00000001, 0x00000001},
  {"MEMCTRL_TIMING3"                      , 0x00000008, 0x00000001, 0x00000001},
  {"MEMCTRL_MR0_VAL"                      , 0x00000009, 0x00000001, 0x00000001},
  {"MEMCTRL_MR1_VAL"                      , 0x0000000a, 0x00000001, 0x00000001},
  {"MEMCTRL_MR2_VAL"                      , 0x0000000b, 0x00000001, 0x00000001},
  {"MEMCTRL_MR3_VAL"                      , 0x0000000c, 0x00000001, 0x00000001},
  {"MEMCTRL_TERMRES_CTRL"                 , 0x0000000d, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"MEMCTRL_DFT"                          , 0x0000000e, 0x00000001, 0x00000001},
#endif
  {"MEMCTRL_DQS_DLY"                      , 0x0000000f, 0x00000001, 0x00000001},
  {"MEMCTRL_DQS_AUTO"                     , 0x00000010, 0x00000001, 0x00000001},
  {"MEMPHY_CFG"                           , 0x00000011, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"MEMPHY_DFT"                           , 0x00000012, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"MEMPHY_DLLCFG0"                       , 0x00000013, 0x00000002, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"MEMPHY_DLLCFG1"                       , 0x00000015, 0x00000002, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"MEMPHY_DQ_DLY_TRM"                    , 0x00000017, 0x00000001, 0x00000001},
#endif
  {"MEMPHY_ZCAL"                          , 0x00000018, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"MEMPHY_ZCAL_STAT"                     , 0x00000019, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"MEMPHY_ZCAL_OVR"                      , 0x0000001a, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"MEMPHY_ZCAL_FORCE"                    , 0x0000001b, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ICPU_CFG_TWI_DELAY[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TWI_CONFIG"                           , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_ICPU_CFG[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"CPU_SYSTEM_CTRL"                      , 0x00000000, 0x00000001, 0x0000000b, regs_within_ICPU_CFG_CPU_SYSTEM_CTRL},
  {"PI_MST"                               , 0x0000000b, 0x00000001, 0x00000009, regs_within_ICPU_CFG_PI_MST},
  {"SPI_MST"                              , 0x00000014, 0x00000001, 0x00000006, regs_within_ICPU_CFG_SPI_MST},
  {"MPU8051"                              , 0x0000001a, 0x00000001, 0x00000007, regs_within_ICPU_CFG_MPU8051},
  {"INTR"                                 , 0x00000021, 0x00000001, 0x0000002e, regs_within_ICPU_CFG_INTR},
  {"GPDMA"                                , 0x0000004f, 0x00000001, 0x00000013, regs_within_ICPU_CFG_GPDMA},
  {"INJ_FRM_SPC"                          , 0x00000062, 0x00000008, 0x00000004, regs_within_ICPU_CFG_INJ_FRM_SPC},
  {"TIMERS"                               , 0x00000082, 0x00000001, 0x0000000b, regs_within_ICPU_CFG_TIMERS},
  {"MEMCTRL"                              , 0x0000008d, 0x00000001, 0x0000001c, regs_within_ICPU_CFG_MEMCTRL},
  {"TWI_DELAY"                            , 0x000000a9, 0x00000001, 0x00000001, regs_within_ICPU_CFG_TWI_DELAY},
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
static const vtss_symreg_reg_t regs_within_SBA_SBA[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PL1"                                  , 0x00000000, 0x00000001, 0x00000001},
  {"PL2"                                  , 0x00000001, 0x00000001, 0x00000001},
  {"PL3"                                  , 0x00000002, 0x00000001, 0x00000001},
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
  {"WT_CL1"                               , 0x00000015, 0x00000001, 0x00000001},
  {"WT_CL2"                               , 0x00000016, 0x00000001, 0x00000001},
  {"WT_CL3"                               , 0x00000017, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_SBA[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"SBA"                                  , 0x00000000, 0x00000001, 0x00000018, regs_within_SBA_SBA},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_FDMA_CH[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"SAR"                                  , 0x00000000, 0x00000001, 0x00000001},
  {"DAR"                                  , 0x00000002, 0x00000001, 0x00000001},
  {"LLP"                                  , 0x00000004, 0x00000001, 0x00000001},
  {"CTL0"                                 , 0x00000006, 0x00000001, 0x00000001},
  {"CTL1"                                 , 0x00000007, 0x00000001, 0x00000001},
  {"DSTAT"                                , 0x0000000a, 0x00000001, 0x00000001},
  {"DSTATAR"                              , 0x0000000e, 0x00000001, 0x00000001},
  {"CFG0"                                 , 0x00000010, 0x00000001, 0x00000001},
  {"CFG1"                                 , 0x00000011, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_FDMA_INTR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"RAW_TFR"                              , 0x00000000, 0x00000001, 0x00000001},
  {"RAW_BLOCK"                            , 0x00000002, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"RAW_SRC_TRAN"                         , 0x00000004, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"RAW_DST_TRAN"                         , 0x00000006, 0x00000001, 0x00000001},
#endif
  {"RAW_ERR"                              , 0x00000008, 0x00000001, 0x00000001},
  {"STATUS_TFR"                           , 0x0000000a, 0x00000001, 0x00000001},
  {"STATUS_BLOCK"                         , 0x0000000c, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"STATUS_SRC_TRAN"                      , 0x0000000e, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"STATUS_DST_TRAN"                      , 0x00000010, 0x00000001, 0x00000001},
#endif
  {"STATUS_ERR"                           , 0x00000012, 0x00000001, 0x00000001},
  {"MASK_TFR"                             , 0x00000014, 0x00000001, 0x00000001},
  {"MASK_BLOCK"                           , 0x00000016, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"MASK_SRC_TRAN"                        , 0x00000018, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"MASK_DST_TRAN"                        , 0x0000001a, 0x00000001, 0x00000001},
#endif
  {"MASK_ERR"                             , 0x0000001c, 0x00000001, 0x00000001},
  {"STATUSINT"                            , 0x00000028, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_FDMA_HS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"REQ_SRC_REG"                          , 0x00000000, 0x00000001, 0x00000001},
  {"REQ_DST_REG"                          , 0x00000002, 0x00000001, 0x00000001},
  {"SGL_REQ_SRC_REG"                      , 0x00000004, 0x00000001, 0x00000001},
  {"SGL_REQ_DST_REG"                      , 0x00000006, 0x00000001, 0x00000001},
  {"LST_SRC_REG"                          , 0x00000008, 0x00000001, 0x00000001},
  {"LST_DST_REG"                          , 0x0000000a, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_FDMA_MISC[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"DMA_CFG_REG"                          , 0x00000000, 0x00000001, 0x00000001},
  {"CH_EN_REG"                            , 0x00000002, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"DMA_ID_REG"                           , 0x00000004, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"DMA_TEST_REG"                         , 0x00000006, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"DMA_COMP_PARAMS_CH7"                  , 0x0000000d, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"DMA_COMP_PARAMS_CH6"                  , 0x0000000e, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"DMA_COMP_PARAMS_CH5"                  , 0x0000000f, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"DMA_COMP_PARAMS_CH4"                  , 0x00000010, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"DMA_COMP_PARAMS_CH3"                  , 0x00000011, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"DMA_COMP_PARAMS_CH2"                  , 0x00000012, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"DMA_COMP_PARAMS_CH1"                  , 0x00000013, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"DMA_COMP_PARAMS_CH0"                  , 0x00000014, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"DMA_COMP_PARAMS_MULTI_BLK_TYPE"       , 0x00000015, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"DMA_COMP_PARAMS_MAX_BLK_SIZE"         , 0x00000016, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"DMA_COMP_PARAMS_OVERALL"              , 0x00000017, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"DMA_COMP_TYPE"                        , 0x00000018, 0x00000001, 0x00000001},
#endif
  {"DMA_COMP_VERSION"                     , 0x00000019, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_FDMA[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"CH"                                   , 0x00000000, 0x00000008, 0x00000016, regs_within_FDMA_CH},
  {"INTR"                                 , 0x000000b0, 0x00000001, 0x0000002a, regs_within_FDMA_INTR},
#ifndef VTSS_RELEASE
  {"HS"                                   , 0x000000da, 0x00000001, 0x0000000c, regs_within_FDMA_HS},
#endif
  {"MISC"                                 , 0x000000e6, 0x00000001, 0x0000001a, regs_within_FDMA_MISC},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_target_t vtss_symreg_targets[] = {
  //target name         , repl, tgt_id    , base_addr                  , register group list
  {"DEVCPU_ORG"         ,   -1, 0x00000000, VTSS_IO_OFFSET1(0x00000000), reggrps_within_DEVCPU_ORG},
  {"SYS"                ,   -1, 0x00000001, VTSS_IO_OFFSET1(0x00010000), reggrps_within_SYS},
  {"ANA"                ,   -1, 0x00000002, VTSS_IO_OFFSET1(0x00020000), reggrps_within_ANA},
  {"REW"                ,   -1, 0x00000003, VTSS_IO_OFFSET1(0x00030000), reggrps_within_REW},
  {"VCAP_CORE"          ,   -1, 0x00000004, VTSS_IO_OFFSET1(0x00040000), reggrps_within_VCAP_CORE},
  {"VCAP_CORE"          ,   -1, 0x00000005, VTSS_IO_OFFSET1(0x00050000), reggrps_within_VCAP_CORE},
  {"VCAP_CORE"          ,   -1, 0x00000006, VTSS_IO_OFFSET1(0x00060000), reggrps_within_VCAP_CORE},
  {"DEVCPU_GCB"         ,   -1, 0x00000007, VTSS_IO_OFFSET1(0x00070000), reggrps_within_DEVCPU_GCB},
  {"DEVCPU_QS"          ,   -1, 0x00000008, VTSS_IO_OFFSET1(0x00080000), reggrps_within_DEVCPU_QS},
  {"DEVCPU_PI"          ,   -1, 0x00000009, VTSS_IO_OFFSET1(0x00090000), reggrps_within_DEVCPU_PI},
  {"MACRO_CTRL"         ,   -1, 0x0000000a, VTSS_IO_OFFSET1(0x000a0000), reggrps_within_MACRO_CTRL},
  {"DEV"                ,    0, 0x0000001e, VTSS_IO_OFFSET1(0x001e0000), reggrps_within_DEV_GMII},
  {"DEV"                ,    1, 0x0000001f, VTSS_IO_OFFSET1(0x001f0000), reggrps_within_DEV_GMII},
  {"DEV"                ,    2, 0x00000020, VTSS_IO_OFFSET1(0x00200000), reggrps_within_DEV_GMII},
  {"DEV"                ,    3, 0x00000021, VTSS_IO_OFFSET1(0x00210000), reggrps_within_DEV_GMII},
  {"DEV"                ,    4, 0x00000022, VTSS_IO_OFFSET1(0x00220000), reggrps_within_DEV_GMII},
  {"DEV"                ,    5, 0x00000023, VTSS_IO_OFFSET1(0x00230000), reggrps_within_DEV_GMII},
  {"DEV"                ,    6, 0x00000024, VTSS_IO_OFFSET1(0x00240000), reggrps_within_DEV_GMII},
  {"DEV"                ,    7, 0x00000025, VTSS_IO_OFFSET1(0x00250000), reggrps_within_DEV_GMII},
  {"DEV"                ,    8, 0x00000026, VTSS_IO_OFFSET1(0x00260000), reggrps_within_DEV_GMII},
  {"DEV"                ,    9, 0x00000027, VTSS_IO_OFFSET1(0x00270000), reggrps_within_DEV_GMII},
  {"DEV"                ,   10, 0x00000028, VTSS_IO_OFFSET1(0x00280000), reggrps_within_DEV},
  {"DEV"                ,   11, 0x00000029, VTSS_IO_OFFSET1(0x00290000), reggrps_within_DEV},
  {"DEV"                ,   12, 0x0000002a, VTSS_IO_OFFSET1(0x002a0000), reggrps_within_DEV},
  {"DEV"                ,   13, 0x0000002b, VTSS_IO_OFFSET1(0x002b0000), reggrps_within_DEV},
  {"DEV"                ,   14, 0x0000002c, VTSS_IO_OFFSET1(0x002c0000), reggrps_within_DEV},
  {"DEV"                ,   15, 0x0000002d, VTSS_IO_OFFSET1(0x002d0000), reggrps_within_DEV},
  {"DEV"                ,   16, 0x0000002e, VTSS_IO_OFFSET1(0x002e0000), reggrps_within_DEV},
  {"DEV"                ,   17, 0x0000002f, VTSS_IO_OFFSET1(0x002f0000), reggrps_within_DEV},
  {"DEV"                ,   18, 0x00000030, VTSS_IO_OFFSET1(0x00300000), reggrps_within_DEV},
  {"DEV"                ,   19, 0x00000031, VTSS_IO_OFFSET1(0x00310000), reggrps_within_DEV},
  {"DEV"                ,   20, 0x00000032, VTSS_IO_OFFSET1(0x00320000), reggrps_within_DEV},
  {"DEV"                ,   21, 0x00000033, VTSS_IO_OFFSET1(0x00330000), reggrps_within_DEV},
  {"DEV"                ,   22, 0x00000034, VTSS_IO_OFFSET1(0x00340000), reggrps_within_DEV},
  {"DEV"                ,   23, 0x00000035, VTSS_IO_OFFSET1(0x00350000), reggrps_within_DEV},
  {"DEV"                ,   24, 0x00000036, VTSS_IO_OFFSET1(0x00360000), reggrps_within_DEV},
  {"DEV"                ,   25, 0x00000037, VTSS_IO_OFFSET1(0x00370000), reggrps_within_DEV},
  {"ICPU_CFG"           ,   -1, 0x0000007f, VTSS_IO_OFFSET2(0x00000000), reggrps_within_ICPU_CFG},
  {"UART"               ,   -1, 0x0000007e, VTSS_IO_OFFSET2(0x00100000), reggrps_within_UART},
  {"TWI"                ,   -1, 0x0000007c, VTSS_IO_OFFSET2(0x00100400), reggrps_within_TWI},
  {"SBA"                ,   -1, 0x0000007b, VTSS_IO_OFFSET2(0x00110000), reggrps_within_SBA},
  {"FDMA"               ,   -1, 0x0000007a, VTSS_IO_OFFSET2(0x00110800), reggrps_within_FDMA},
};

#define SYMREG_REPL_CNT_MAX 3558
#define SYMREG_NAME_LEN_MAX 30

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
#endif /* VTSS_ARCH_LUTON26 */
