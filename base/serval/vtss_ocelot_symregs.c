// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "vtss_api.h"

#ifdef VTSS_ARCH_OCELOT
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

static const vtss_symreg_reg_t regs_within_ANA_ANA[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"ADVLEARN"                             , 0x00000000, 0x00000001, 0x00000001},
  {"VLANMASK"                             , 0x00000001, 0x00000001, 0x00000001},
  {"PORT_B_DOMAIN"                        , 0x00000002, 0x00000001, 0x00000001},
  {"ANAGEFIL"                             , 0x00000003, 0x00000001, 0x00000001},
  {"ANEVENTS"                             , 0x00000004, 0x00000001, 0x00000001},
  {"STORMLIMIT_BURST"                     , 0x00000005, 0x00000001, 0x00000001},
  {"STORMLIMIT_CFG"                       , 0x00000006, 0x00000004, 0x00000001},
  {"ISOLATED_PORTS"                       , 0x0000000a, 0x00000001, 0x00000001},
  {"COMMUNITY_PORTS"                      , 0x0000000b, 0x00000001, 0x00000001},
  {"AUTOAGE"                              , 0x0000000c, 0x00000001, 0x00000001},
  {"MACTOPTIONS"                          , 0x0000000d, 0x00000001, 0x00000001},
  {"LEARNDISC"                            , 0x0000000e, 0x00000001, 0x00000001},
  {"AGENCTRL"                             , 0x0000000f, 0x00000001, 0x00000001},
  {"MIRRORPORTS"                          , 0x00000010, 0x00000001, 0x00000001},
  {"EMIRRORPORTS"                         , 0x00000011, 0x00000001, 0x00000001},
  {"FLOODING"                             , 0x00000012, 0x00000001, 0x00000001},
  {"FLOODING_IPMC"                        , 0x00000013, 0x00000001, 0x00000001},
  {"SFLOW_CFG"                            , 0x00000014, 0x0000000c, 0x00000001},
  {"PORT_MODE"                            , 0x00000020, 0x0000000d, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_PGID[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PGID"                                 , 0x00000000, 0x0000005c, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_ANA_TABLES[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"ANMOVED"                              , 0x0000000c, 0x00000001, 0x00000001},
  {"MACHDATA"                             , 0x0000000d, 0x00000001, 0x00000001},
  {"MACLDATA"                             , 0x0000000e, 0x00000001, 0x00000001},
  {"MACACCESS"                            , 0x0000000f, 0x00000001, 0x00000001},
  {"MACTINDX"                             , 0x00000010, 0x00000001, 0x00000001},
  {"VLANACCESS"                           , 0x00000011, 0x00000001, 0x00000001},
  {"VLANTIDX"                             , 0x00000012, 0x00000001, 0x00000001},
  {"ISDXACCESS"                           , 0x00000013, 0x00000001, 0x00000001},
  {"ISDXTIDX"                             , 0x00000014, 0x00000001, 0x00000001},
  {"ENTRYLIM"                             , 0x00000000, 0x0000000c, 0x00000001},
  {"PTP_ID_HIGH"                          , 0x00000015, 0x00000001, 0x00000001},
  {"PTP_ID_LOW"                           , 0x00000016, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_MSTI_STATE[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MSTI_STATE"                           , 0x00000000, 0x00000080, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_OAM_UPM_LM_CNT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"OAM_UPM_LM_CNT"                       , 0x00000000, 0x00000100, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_PORT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"VLAN_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
  {"DROP_CFG"                             , 0x00000001, 0x00000001, 0x00000001},
  {"QOS_CFG"                              , 0x00000002, 0x00000001, 0x00000001},
  {"VCAP_CFG"                             , 0x00000003, 0x00000001, 0x00000001},
  {"VCAP_S1_KEY_CFG"                      , 0x00000004, 0x00000003, 0x00000001},
  {"VCAP_S2_CFG"                          , 0x00000007, 0x00000001, 0x00000001},
  {"QOS_PCP_DEI_MAP_CFG"                  , 0x00000008, 0x00000010, 0x00000001},
  {"CPU_FWD_CFG"                          , 0x00000018, 0x00000001, 0x00000001},
  {"CPU_FWD_BPDU_CFG"                     , 0x00000019, 0x00000001, 0x00000001},
  {"CPU_FWD_GARP_CFG"                     , 0x0000001a, 0x00000001, 0x00000001},
  {"CPU_FWD_CCM_CFG"                      , 0x0000001b, 0x00000001, 0x00000001},
  {"PORT_CFG"                             , 0x0000001c, 0x00000001, 0x00000001},
  {"POL_CFG"                              , 0x0000001d, 0x00000001, 0x00000001},
  {"PTP_CFG"                              , 0x0000001e, 0x00000001, 0x00000001},
  {"PTP_DLY1_CFG"                         , 0x0000001f, 0x00000001, 0x00000001},
  {"PTP_DLY2_CFG"                         , 0x00000020, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_PFC[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PFC_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"PFC_TIMER"                            , 0x00000001, 0x00000008, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_IPT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"OAM_MEP_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
  {"IPT"                                  , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_PPT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PPT"                                  , 0x00000000, 0x00000003, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_FID_MAP[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"FID_MAP"                              , 0x00000000, 0x00001000, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_COMMON[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"AGGR_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
  {"CPUQ_CFG"                             , 0x00000001, 0x00000001, 0x00000001},
  {"CPUQ_CFG2"                            , 0x00000002, 0x00000001, 0x00000001},
  {"CPUQ_8021_CFG"                        , 0x00000003, 0x00000010, 0x00000001},
  {"DSCP_CFG"                             , 0x00000013, 0x00000040, 0x00000001},
  {"DSCP_REWR_CFG"                        , 0x00000053, 0x00000010, 0x00000001},
  {"VCAP_RNG_TYPE_CFG"                    , 0x00000063, 0x00000008, 0x00000001},
  {"VCAP_RNG_VAL_CFG"                     , 0x0000006b, 0x00000008, 0x00000001},
  {"VRAP_CFG"                             , 0x00000073, 0x00000001, 0x00000001},
  {"VRAP_HDR_DATA"                        , 0x00000074, 0x00000001, 0x00000001},
  {"VRAP_HDR_MASK"                        , 0x00000075, 0x00000001, 0x00000001},
  {"DISCARD_CFG"                          , 0x00000076, 0x00000001, 0x00000001},
  {"FID_CFG"                              , 0x00000077, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_POL[] = {
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
static const vtss_symreg_reg_t regs_within_ANA_POL_MISC[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"POL_FLOWC"                            , 0x00000000, 0x0000001b, 0x00000001},
  {"POL_HYST"                             , 0x0000001b, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"POL_MISC_CFG"                         , 0x0000001c, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_ANA[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"ANA"                                  , 0x00002400, 0x00000001, 0x0000002d, regs_within_ANA_ANA},
  {"PGID"                                 , 0x00002300, 0x00000001, 0x00000080, regs_within_ANA_PGID},
  {"ANA_TABLES"                           , 0x000022c0, 0x00000001, 0x00000020, regs_within_ANA_ANA_TABLES},
  {"MSTI_STATE"                           , 0x00002380, 0x00000001, 0x00000080, regs_within_ANA_MSTI_STATE},
  {"OAM_UPM_LM_CNT"                       , 0x00001f00, 0x00000001, 0x00000100, regs_within_ANA_OAM_UPM_LM_CNT},
  {"PORT"                                 , 0x00001c00, 0x0000000c, 0x00000040, regs_within_ANA_PORT},
  {"PFC"                                  , 0x00002200, 0x0000000b, 0x00000010, regs_within_ANA_PFC},
  {"IPT"                                  , 0x00002000, 0x00000100, 0x00000002, regs_within_ANA_IPT},
  {"PPT"                                  , 0x000022b0, 0x00000001, 0x00000004, regs_within_ANA_PPT},
  {"FID_MAP"                              , 0x00000000, 0x00000001, 0x00001000, regs_within_ANA_FID_MAP},
  {"COMMON"                               , 0x0000242d, 0x00000001, 0x00000078, regs_within_ANA_COMMON},
  {"POL"                                  , 0x00001000, 0x00000180, 0x00000008, regs_within_ANA_POL},
  {"POL_MISC"                             , 0x000022e0, 0x00000001, 0x0000001d, regs_within_ANA_POL_MISC},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV_PORT_MODE[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CLOCK_CFG"                            , 0x00000000, 0x00000001, 0x00000001},
  {"PORT_MISC"                            , 0x00000001, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"EVENTS"                               , 0x00000002, 0x00000001, 0x00000001},
#endif
  {"EEE_CFG"                              , 0x00000003, 0x00000001, 0x00000001},
  {"RX_PATH_DELAY"                        , 0x00000004, 0x00000001, 0x00000001},
  {"TX_PATH_DELAY"                        , 0x00000005, 0x00000001, 0x00000001},
  {"PTP_PREDICT_CFG"                      , 0x00000006, 0x00000001, 0x00000001},
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
  {"MAC_FC_MAC_LOW_CFG"                   , 0x00000008, 0x00000001, 0x00000001},
  {"MAC_FC_MAC_HIGH_CFG"                  , 0x00000009, 0x00000001, 0x00000001},
  {"MAC_STICKY"                           , 0x0000000a, 0x00000001, 0x00000001},
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
  {"PCS1G_DEBUG_STATUS"                   , 0x0000000d, 0x00000001, 0x00000001},
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
  {"PORT_MODE"                            , 0x00000000, 0x00000001, 0x00000007, regs_within_DEV_PORT_MODE},
  {"MAC_CFG_STATUS"                       , 0x00000007, 0x00000001, 0x0000000b, regs_within_DEV_MAC_CFG_STATUS},
  {"PCS1G_CFG_STATUS"                     , 0x00000012, 0x00000001, 0x00000011, regs_within_DEV_PCS1G_CFG_STATUS},
  {"PCS1G_TSTPAT_CFG_STATUS"              , 0x00000023, 0x00000001, 0x00000002, regs_within_DEV_PCS1G_TSTPAT_CFG_STATUS},
  {"PCS_FX100_CONFIGURATION"              , 0x00000025, 0x00000001, 0x00000001, regs_within_DEV_PCS_FX100_CONFIGURATION},
  {"PCS_FX100_STATUS"                     , 0x00000026, 0x00000001, 0x00000001, regs_within_DEV_PCS_FX100_STATUS},
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
#ifndef VTSS_RELEASE
  {"FEA_STAT"                             , 0x00000005, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"FEA_DIS"                              , 0x00000006, 0x00000001, 0x00000001},
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
  {"GPIO_OUT_CLR"                         , 0x00000001, 0x00000001, 0x00000001},
  {"GPIO_OUT"                             , 0x00000002, 0x00000001, 0x00000001},
  {"GPIO_IN"                              , 0x00000003, 0x00000001, 0x00000001},
  {"GPIO_OE"                              , 0x00000004, 0x00000001, 0x00000001},
  {"GPIO_INTR"                            , 0x00000005, 0x00000001, 0x00000001},
  {"GPIO_INTR_ENA"                        , 0x00000006, 0x00000001, 0x00000001},
  {"GPIO_INTR_IDENT"                      , 0x00000007, 0x00000001, 0x00000001},
  {"GPIO_ALT"                             , 0x00000008, 0x00000002, 0x00000001},
  {"GPIO_SD_MAP"                          , 0x0000000a, 0x00000010, 0x00000001},
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
  {"MII_SCAN_RSLTS_STICKY"                , 0x00000000, 0x00000002, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_MIIM_SLAVE[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MIIM_SLAVE_CFG"                       , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_PHY[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PHY_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
  {"PHY_STAT"                             , 0x00000001, 0x00000001, 0x00000001},
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
  {"PWM_FREQ"                             , 0x00000001, 0x00000001, 0x00000001},
  {"FAN_CNT"                              , 0x00000002, 0x00000001, 0x00000001},
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
  {"CHIP_REGS"                            , 0x00000000, 0x00000001, 0x00000007, regs_within_DEVCPU_GCB_CHIP_REGS},
#ifndef VTSS_RELEASE
  {"SW_REGS"                              , 0x00000007, 0x00000001, 0x00000001, regs_within_DEVCPU_GCB_SW_REGS},
#endif
  {"VCORE_ACCESS"                         , 0x00000008, 0x00000001, 0x00000005, regs_within_DEVCPU_GCB_VCORE_ACCESS},
  {"GPIO"                                 , 0x0000000d, 0x00000001, 0x0000001a, regs_within_DEVCPU_GCB_GPIO},
  {"MIIM"                                 , 0x00000027, 0x00000002, 0x00000009, regs_within_DEVCPU_GCB_MIIM},
  {"MIIM_READ_SCAN"                       , 0x00000039, 0x00000001, 0x00000002, regs_within_DEVCPU_GCB_MIIM_READ_SCAN},
  {"MIIM_SLAVE"                           , 0x0000003b, 0x00000001, 0x00000001, regs_within_DEVCPU_GCB_MIIM_SLAVE},
  {"PHY"                                  , 0x0000003c, 0x00000001, 0x00000002, regs_within_DEVCPU_GCB_PHY},
  {"SIO_CTRL"                             , 0x0000003e, 0x00000001, 0x00000043, regs_within_DEVCPU_GCB_SIO_CTRL},
  {"FAN_CTRL"                             , 0x00000081, 0x00000001, 0x00000003, regs_within_DEVCPU_GCB_FAN_CTRL},
  {"MEMITGR"                              , 0x00000084, 0x00000001, 0x00000006, regs_within_DEVCPU_GCB_MEMITGR},
  {"VRAP"                                 , 0x0000008a, 0x00000001, 0x00000001, regs_within_DEVCPU_GCB_VRAP},
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
  {"CLK_ADJ_CFG"                          , 0x00000001, 0x00000001, 0x00000001},
  {"CLK_ADJ_FRQ"                          , 0x00000002, 0x00000001, 0x00000001},
  {"PTP_PIN_INTR"                         , 0x00000003, 0x00000001, 0x00000001},
  {"PTP_PIN_INTR_ENA"                     , 0x00000004, 0x00000001, 0x00000001},
  {"PTP_INTR_IDENT"                       , 0x00000005, 0x00000001, 0x00000001},
  {"PTP_SYS_CLK_CFG"                      , 0x00000006, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_PTP_PTP_STATUS[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PTP_CUR_NSF"                          , 0x00000000, 0x00000001, 0x00000001},
  {"PTP_CUR_NSEC"                         , 0x00000001, 0x00000001, 0x00000001},
  {"PTP_CUR_SEC_LSB"                      , 0x00000002, 0x00000001, 0x00000001},
  {"PTP_CUR_SEC_MSB"                      , 0x00000003, 0x00000001, 0x00000001},
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
  {"PTP_CFG"                              , 0x00000028, 0x00000001, 0x00000007, regs_within_DEVCPU_PTP_PTP_CFG},
  {"PTP_STATUS"                           , 0x0000002f, 0x00000001, 0x00000004, regs_within_DEVCPU_PTP_PTP_STATUS},
  {"PTP_PINS"                             , 0x00000000, 0x00000005, 0x00000008, regs_within_DEVCPU_PTP_PTP_PINS},
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
  {"VCAP_TG_DAT"                          , 0x000000e0, 0x00000001, 0x00000001},
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
static const vtss_symreg_reg_t regs_within_HSIO_PLL5G_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"PLL5G_CFG0"                           , 0x00000000, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PLL5G_CFG1"                           , 0x00000001, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PLL5G_CFG2"                           , 0x00000002, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PLL5G_CFG3"                           , 0x00000003, 0x00000001, 0x00000001},
#endif
  {"PLL5G_CFG4"                           , 0x00000004, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"PLL5G_CFG5"                           , 0x00000005, 0x00000001, 0x00000001},
#endif
  {"PLL5G_CFG6"                           , 0x00000006, 0x00000001, 0x00000001},
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
  {"PLL5G_BIST_CFG0"                      , 0x00000000, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PLL5G_BIST_CFG1"                      , 0x00000001, 0x00000001, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"PLL5G_BIST_CFG2"                      , 0x00000002, 0x00000001, 0x00000001},
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
  {"PLL5G_BIST_STAT1"                     , 0x00000001, 0x00000001, 0x00000001},
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
  {"SYNC_ETH_CFG"                         , 0x00000000, 0x00000002, 0x00000001},
  {"SYNC_ETH_PLL_CFG"                     , 0x00000002, 0x00000001, 0x00000001},
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
  {"HW_QSGMII_STAT"                       , 0x00000002, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"CLK_CFG"                              , 0x00000003, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSIO_TEMP_SENSOR[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TEMP_SENSOR_CTRL"                     , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"TEMP_SENSOR_CFG"                      , 0x00000001, 0x00000001, 0x00000001},
#endif
  {"TEMP_SENSOR_STAT"                     , 0x00000002, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_HSIO[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"PLL5G_CFG"                            , 0x00000000, 0x00000001, 0x00000007, regs_within_HSIO_PLL5G_CFG},
  {"PLL5G_STATUS"                         , 0x00000007, 0x00000001, 0x00000002, regs_within_HSIO_PLL5G_STATUS},
#ifndef VTSS_RELEASE
  {"PLL5G_BIST_CFG"                       , 0x00000009, 0x00000001, 0x00000003, regs_within_HSIO_PLL5G_BIST_CFG},
#endif
#ifndef VTSS_RELEASE
  {"PLL5G_BIST_STATUS"                    , 0x0000000c, 0x00000001, 0x00000002, regs_within_HSIO_PLL5G_BIST_STATUS},
#endif
#ifndef VTSS_RELEASE
  {"RCOMP_CFG"                            , 0x0000000e, 0x00000001, 0x00000001, regs_within_HSIO_RCOMP_CFG},
#endif
  {"RCOMP_STATUS"                         , 0x0000000f, 0x00000001, 0x00000001, regs_within_HSIO_RCOMP_STATUS},
  {"SYNC_ETH_CFG"                         , 0x00000010, 0x00000001, 0x00000003, regs_within_HSIO_SYNC_ETH_CFG},
  {"SERDES1G_ANA_CFG"                     , 0x00000013, 0x00000001, 0x00000006, regs_within_HSIO_SERDES1G_ANA_CFG},
#ifndef VTSS_RELEASE
  {"SERDES1G_ANA_STATUS"                  , 0x00000019, 0x00000001, 0x00000001, regs_within_HSIO_SERDES1G_ANA_STATUS},
#endif
  {"SERDES1G_DIG_CFG"                     , 0x0000001a, 0x00000001, 0x00000006, regs_within_HSIO_SERDES1G_DIG_CFG},
  {"SERDES1G_DIG_STATUS"                  , 0x00000020, 0x00000001, 0x00000002, regs_within_HSIO_SERDES1G_DIG_STATUS},
  {"MCB_SERDES1G_CFG"                     , 0x00000022, 0x00000001, 0x00000001, regs_within_HSIO_MCB_SERDES1G_CFG},
  {"SERDES6G_DIG_CFG"                     , 0x00000023, 0x00000001, 0x00000009, regs_within_HSIO_SERDES6G_DIG_CFG},
#ifndef VTSS_RELEASE
  {"SERDES6G_DIG_STATUS"                  , 0x0000002c, 0x00000001, 0x00000003, regs_within_HSIO_SERDES6G_DIG_STATUS},
#endif
  {"SERDES6G_ANA_CFG"                     , 0x0000002f, 0x00000001, 0x0000000e, regs_within_HSIO_SERDES6G_ANA_CFG},
  {"SERDES6G_ANA_STATUS"                  , 0x0000003d, 0x00000001, 0x00000005, regs_within_HSIO_SERDES6G_ANA_STATUS},
  {"MCB_SERDES6G_CFG"                     , 0x00000042, 0x00000001, 0x00000001, regs_within_HSIO_MCB_SERDES6G_CFG},
  {"HW_CFGSTAT"                           , 0x00000043, 0x00000001, 0x00000004, regs_within_HSIO_HW_CFGSTAT},
  {"TEMP_SENSOR"                          , 0x00000047, 0x00000001, 0x00000003, regs_within_HSIO_TEMP_SENSOR},
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
  {"DEV_INTR_RAW"                         , 0x00000016, 0x00000001, 0x00000001},
  {"DEV_INTR_TRIGGER"                     , 0x00000017, 0x00000002, 0x00000001},
  {"DEV_INTR_STICKY"                      , 0x00000019, 0x00000001, 0x00000001},
  {"DEV_INTR_BYPASS"                      , 0x0000001a, 0x00000001, 0x00000001},
  {"DEV_INTR_ENA"                         , 0x0000001b, 0x00000001, 0x00000001},
  {"DEV_INTR_IDENT"                       , 0x0000001c, 0x00000001, 0x00000001},
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
  {"MPU8051"                              , 0x00000015, 0x00000001, 0x00000007, regs_within_ICPU_CFG_MPU8051},
  {"INTR"                                 , 0x0000001c, 0x00000001, 0x0000001d, regs_within_ICPU_CFG_INTR},
  {"TIMERS"                               , 0x00000039, 0x00000001, 0x0000000b, regs_within_ICPU_CFG_TIMERS},
  {"MEMCTRL"                              , 0x00000044, 0x00000001, 0x00000022, regs_within_ICPU_CFG_MEMCTRL},
  {"TWI_DELAY"                            , 0x00000066, 0x00000001, 0x00000001, regs_within_ICPU_CFG_TWI_DELAY},
  {"TWI_SPIKE_FILTER"                     , 0x00000067, 0x00000001, 0x00000001, regs_within_ICPU_CFG_TWI_SPIKE_FILTER},
  {"FDMA"                                 , 0x00000068, 0x00000001, 0x00000071, regs_within_ICPU_CFG_FDMA},
  {"PCIE"                                 , 0x000000d9, 0x00000001, 0x00000016, regs_within_ICPU_CFG_PCIE},
  {"MANUAL_XTRINJ"                        , 0x00001000, 0x00000001, 0x00002003, regs_within_ICPU_CFG_MANUAL_XTRINJ},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_OAM_MEP_COMMON[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MEP_CTRL"                             , 0x00000000, 0x00000001, 0x00000001},
  {"CPU_CFG"                              , 0x00000001, 0x00000001, 0x00000001},
  {"CPU_CFG_1"                            , 0x00000002, 0x00000001, 0x00000001},
  {"OAM_SDLB_CPU_COPY"                    , 0x00000003, 0x00000001, 0x00000001},
  {"OAM_GENERIC_CFG"                      , 0x00000004, 0x00000008, 0x00000001},
  {"CCM_PERIOD_CFG"                       , 0x0000000c, 0x00000007, 0x00000001},
  {"CCM_CTRL"                             , 0x00000013, 0x00000001, 0x00000001},
  {"CCM_SCAN_STICKY"                      , 0x00000014, 0x00000001, 0x00000001},
  {"MASTER_INTR_CTRL"                     , 0x00000015, 0x00000001, 0x00000001},
  {"INTR"                                 , 0x00000016, 0x00000002, 0x00000001},
  {"VOE_CFG"                              , 0x00000018, 0x00000020, 0x00000001},
  {"UPMEP_LM_CNT_VLD"                     , 0x00000038, 0x00000020, 0x00000001},
  {"VOE_MAP_CTRL"                         , 0x00000058, 0x00000020, 0x00000001},
  {"VOE_CNT_CTRL"                         , 0x00000078, 0x0000002b, 0x00000001},
  {"COMMON_MEP_MC_MAC_LSB"                , 0x000000a3, 0x00000001, 0x00000001},
  {"COMMON_MEP_MC_MAC_MSB"                , 0x000000a4, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_OAM_MEP_VOE[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"BASIC_CTRL"                           , 0x00000000, 0x00000001, 0x00000001},
  {"MEL_CTRL"                             , 0x00000001, 0x00000001, 0x00000001},
  {"OAM_CPU_COPY_CTRL"                    , 0x00000002, 0x00000001, 0x00000001},
  {"OAM_FWD_CTRL"                         , 0x00000003, 0x00000001, 0x00000001},
  {"OAM_SDLB_CTRL"                        , 0x00000004, 0x00000001, 0x00000001},
  {"OAM_CNT_OAM_CTRL"                     , 0x00000005, 0x00000001, 0x00000001},
  {"OAM_CNT_DATA_CTRL"                    , 0x00000006, 0x00000001, 0x00000001},
  {"MEP_UC_MAC_LSB"                       , 0x00000007, 0x00000001, 0x00000001},
  {"MEP_UC_MAC_MSB"                       , 0x00000008, 0x00000001, 0x00000001},
  {"OAM_HW_CTRL"                          , 0x00000009, 0x00000001, 0x00000001},
  {"LOOPBACK_CTRL"                        , 0x0000000a, 0x00000001, 0x00000001},
  {"LBR_RX_FRM_CNT"                       , 0x0000000b, 0x00000001, 0x00000001},
  {"LBR_RX_TRANSID_CFG"                   , 0x0000000c, 0x00000001, 0x00000001},
  {"LBM_TX_TRANSID_UPDATE"                , 0x0000000d, 0x00000001, 0x00000001},
  {"LBM_TX_TRANSID_CFG"                   , 0x0000000e, 0x00000001, 0x00000001},
  {"CCM_CFG"                              , 0x0000000f, 0x00000001, 0x00000001},
  {"CCM_RX_VLD_FC_CNT"                    , 0x00000010, 0x00000001, 0x00000001},
  {"CCM_RX_INVLD_FC_CNT"                  , 0x00000011, 0x00000001, 0x00000001},
  {"CCM_CAP_TX_FCF"                       , 0x00000012, 0x00000001, 0x00000001},
  {"CCM_CAP_RX_FCL"                       , 0x00000013, 0x00000001, 0x00000001},
  {"UPMEP_LMR_RX_LM_CNT"                  , 0x00000014, 0x00000001, 0x00000001},
  {"CCM_TX_SEQ_CFG"                       , 0x00000015, 0x00000001, 0x00000001},
  {"CCM_RX_SEQ_CFG"                       , 0x00000016, 0x00000001, 0x00000001},
  {"CCM_MEPID_CFG"                        , 0x00000017, 0x00000001, 0x00000001},
  {"CCM_MEGID_CFG"                        , 0x00000018, 0x0000000c, 0x00000001},
  {"OAM_RX_STICKY"                        , 0x00000024, 0x00000001, 0x00000001},
  {"STICKY"                               , 0x00000025, 0x00000001, 0x00000001},
  {"UPMEP_LM_CNT_STICKY"                  , 0x00000026, 0x00000001, 0x00000001},
  {"INTR_ENA"                             , 0x00000027, 0x00000001, 0x00000001},
  {"RX_SEL_OAM_CNT"                       , 0x00000028, 0x00000001, 0x00000001},
  {"RX_OAM_FRM_CNT"                       , 0x00000029, 0x00000001, 0x00000001},
  {"TX_SEL_OAM_CNT"                       , 0x0000002a, 0x00000001, 0x00000001},
  {"TX_OAM_FRM_CNT"                       , 0x0000002b, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_OAM_MEP_PORT_PM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PORT_RX_FRM_CNT"                      , 0x00000000, 0x00000001, 0x00000001},
  {"PORT_TX_FRM_CNT"                      , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_OAM_MEP_RX_VOE_PM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MEP_RX_FRM_CNT"                       , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_OAM_MEP_TX_VOE_PM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MEP_TX_FRM_CNT"                       , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_OAM_MEP[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"COMMON"                               , 0x00000db0, 0x00000001, 0x000000a5, regs_within_OAM_MEP_COMMON},
  {"VOE"                                  , 0x00000000, 0x0000002b, 0x00000040, regs_within_OAM_MEP_VOE},
  {"PORT_PM"                              , 0x00000d00, 0x00000058, 0x00000002, regs_within_OAM_MEP_PORT_PM},
  {"RX_VOE_PM"                            , 0x00000b00, 0x00000100, 0x00000001, regs_within_OAM_MEP_RX_VOE_PM},
  {"TX_VOE_PM"                            , 0x00000c00, 0x00000100, 0x00000001, regs_within_OAM_MEP_TX_VOE_PM},
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
static const vtss_symreg_reg_t regs_within_QSYS_SYSTEM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PORT_MODE"                            , 0x00000000, 0x0000000d, 0x00000001},
  {"SWITCH_PORT_MODE"                     , 0x0000000d, 0x0000000c, 0x00000001},
  {"STAT_CNT_CFG"                         , 0x00000019, 0x00000001, 0x00000001},
  {"EEE_CFG"                              , 0x0000001a, 0x0000000b, 0x00000001},
  {"EEE_THRES"                            , 0x00000025, 0x00000001, 0x00000001},
  {"IGR_NO_SHARING"                       , 0x00000026, 0x00000001, 0x00000001},
  {"EGR_NO_SHARING"                       , 0x00000027, 0x00000001, 0x00000001},
  {"SW_STATUS"                            , 0x00000028, 0x0000000c, 0x00000001},
  {"EXT_CPU_CFG"                          , 0x00000034, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"PAD_CFG"                              , 0x00000035, 0x00000001, 0x00000001},
#endif
  {"CPU_GROUP_MAP"                        , 0x00000036, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_QMAP[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"QMAP"                                 , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_SGRP[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"ISDX_SGRP"                            , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_QSYS_TIMED_FRAME_DB[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TIMED_FRAME_ENTRY"                    , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_QSYS_TIMED_FRAME_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"TFRM_MISC"                            , 0x00000000, 0x00000001, 0x00000001},
  {"TFRM_PORT_DLY"                        , 0x00000001, 0x00000001, 0x00000001},
  {"TFRM_TIMER_CFG_1"                     , 0x00000002, 0x00000001, 0x00000001},
  {"TFRM_TIMER_CFG_2"                     , 0x00000003, 0x00000001, 0x00000001},
  {"TFRM_TIMER_CFG_3"                     , 0x00000004, 0x00000001, 0x00000001},
  {"TFRM_TIMER_CFG_4"                     , 0x00000005, 0x00000001, 0x00000001},
  {"TFRM_TIMER_CFG_5"                     , 0x00000006, 0x00000001, 0x00000001},
  {"TFRM_TIMER_CFG_6"                     , 0x00000007, 0x00000001, 0x00000001},
  {"TFRM_TIMER_CFG_7"                     , 0x00000008, 0x00000001, 0x00000001},
  {"TFRM_TIMER_CFG_8"                     , 0x00000009, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_RES_QOS_ADV[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"RED_PROFILE"                          , 0x00000000, 0x00000010, 0x00000001},
  {"RES_QOS_MODE"                         , 0x00000010, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_RES_CTRL[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"RES_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
  {"RES_STAT"                             , 0x00000001, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_DROP_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"EGR_DROP_MODE"                        , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_MMGT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"EQ_CTRL"                              , 0x00000000, 0x00000001, 0x00000001},
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
static const vtss_symreg_reg_t regs_within_QSYS_HSCH[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CIR_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
  {"EIR_CFG"                              , 0x00000001, 0x00000001, 0x00000001},
  {"SE_CFG"                               , 0x00000002, 0x00000001, 0x00000001},
  {"SE_DWRR_CFG"                          , 0x00000003, 0x0000000c, 0x00000001},
  {"SE_CONNECT"                           , 0x0000000f, 0x00000001, 0x00000001},
  {"SE_DLB_SENSE"                         , 0x00000010, 0x00000001, 0x00000001},
  {"CIR_STATE"                            , 0x00000011, 0x00000001, 0x00000001},
  {"EIR_STATE"                            , 0x00000012, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"SE_STATE"                             , 0x00000013, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_HSCH_MISC[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"HSCH_MISC_CFG"                        , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_QSYS[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"SYSTEM"                               , 0x00004480, 0x00000001, 0x00000037, regs_within_QSYS_SYSTEM},
  {"QMAP"                                 , 0x000044b7, 0x0000000d, 0x00000001, regs_within_QSYS_QMAP},
  {"SGRP"                                 , 0x00004500, 0x00000100, 0x00000001, regs_within_QSYS_SGRP},
#ifndef VTSS_RELEASE
  {"TIMED_FRAME_DB"                       , 0x00005000, 0x00000400, 0x00000001, regs_within_QSYS_TIMED_FRAME_DB},
#endif
  {"TIMED_FRAME_CFG"                      , 0x000044c4, 0x00000001, 0x0000000a, regs_within_QSYS_TIMED_FRAME_CFG},
  {"RES_QOS_ADV"                          , 0x000044ce, 0x00000001, 0x00000011, regs_within_QSYS_RES_QOS_ADV},
  {"RES_CTRL"                             , 0x00004800, 0x00000400, 0x00000002, regs_within_QSYS_RES_CTRL},
  {"DROP_CFG"                             , 0x000044df, 0x00000001, 0x00000001, regs_within_QSYS_DROP_CFG},
  {"MMGT"                                 , 0x000044e0, 0x00000001, 0x00000001, regs_within_QSYS_MMGT},
#ifndef VTSS_RELEASE
  {"MISC"                                 , 0x000044e1, 0x00000001, 0x00000001, regs_within_QSYS_MISC},
#endif
  {"HSCH"                                 , 0x00000000, 0x00000224, 0x00000020, regs_within_QSYS_HSCH},
  {"HSCH_MISC"                            , 0x000044e2, 0x00000001, 0x00000001, regs_within_QSYS_HSCH_MISC},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_REW_PORT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PORT_VLAN_CFG"                        , 0x00000000, 0x00000001, 0x00000001},
  {"TAG_CFG"                              , 0x00000001, 0x00000001, 0x00000001},
  {"PORT_CFG"                             , 0x00000002, 0x00000001, 0x00000001},
  {"DSCP_CFG"                             , 0x00000003, 0x00000001, 0x00000001},
  {"PCP_DEI_QOS_MAP_CFG"                  , 0x00000004, 0x00000010, 0x00000001},
  {"PTP_CFG"                              , 0x00000014, 0x00000001, 0x00000001},
  {"PTP_DLY1_CFG"                         , 0x00000015, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_COMMON[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"DSCP_REMAP_DP1_CFG"                   , 0x00000000, 0x00000040, 0x00000001},
  {"DSCP_REMAP_CFG"                       , 0x00000040, 0x00000040, 0x00000001},
  {"STAT_CFG"                             , 0x00000080, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_REW_PPT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PPT"                                  , 0x00000000, 0x00000003, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_REW[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"PORT"                                 , 0x00000000, 0x0000000d, 0x00000020, regs_within_REW_PORT},
  {"COMMON"                               , 0x000001a4, 0x00000001, 0x00000081, regs_within_REW_COMMON},
  {"PPT"                                  , 0x000001a0, 0x00000001, 0x00000004, regs_within_REW_PPT},
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
  {"RX_SAMPLE_DLY"                        , 0x0000003c, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_SIMC[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"SIMC"                                 , 0x00000000, 0x00000001, 0x00000003, regs_within_SIMC_SIMC},
  {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_SYS_SYSTEM[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"RESET_CFG"                            , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"CMID"                                 , 0x00000001, 0x00000001, 0x00000001},
#endif
  {"VLAN_ETYPE_CFG"                       , 0x00000002, 0x00000001, 0x00000001},
  {"PORT_MODE"                            , 0x00000003, 0x0000000d, 0x00000001},
  {"FRONT_PORT_MODE"                      , 0x00000010, 0x0000000b, 0x00000001},
  {"FRM_AGING"                            , 0x0000001b, 0x00000001, 0x00000001},
  {"STAT_CFG"                             , 0x0000001c, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"SW_STATUS"                            , 0x0000001d, 0x0000000c, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"MISC_CFG"                             , 0x00000029, 0x00000001, 0x00000001},
#endif
  {"REW_MAC_HIGH_CFG"                     , 0x0000002a, 0x0000000b, 0x00000001},
  {"REW_MAC_LOW_CFG"                      , 0x00000035, 0x0000000b, 0x00000001},
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
static const vtss_symreg_reg_t regs_within_SYS_PAUSE_CFG[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PAUSE_CFG"                            , 0x00000000, 0x0000000c, 0x00000001},
  {"PAUSE_TOT_CFG"                        , 0x0000000c, 0x00000001, 0x00000001},
  {"ATOP"                                 , 0x0000000d, 0x0000000c, 0x00000001},
  {"ATOP_TOT_CFG"                         , 0x00000019, 0x00000001, 0x00000001},
  {"MAC_FC_CFG"                           , 0x0000001a, 0x0000000b, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SYS_MMGT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"MMGT"                                 , 0x00000000, 0x00000001, 0x00000001},
#ifndef VTSS_RELEASE
  {"MMGT_FAST"                            , 0x00000001, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#ifndef VTSS_RELEASE
static const vtss_symreg_reg_t regs_within_SYS_MISC[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
#ifndef VTSS_RELEASE
  {"EVENTS_DIF"                           , 0x00000000, 0x00000004, 0x00000001},
#endif
#ifndef VTSS_RELEASE
  {"EVENTS_CORE"                          , 0x00000004, 0x00000001, 0x00000001},
#endif
  {NULL, 0, 0, 0}
};
#endif
static const vtss_symreg_reg_t regs_within_SYS_STAT[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"CNT"                                  , 0x00000000, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SYS_PTP[] = {
  //reg name                              , addr      , repl_cnt  , repl_width
  {"PTP_STATUS"                           , 0x00000000, 0x00000001, 0x00000001},
  {"PTP_TXSTAMP"                          , 0x00000001, 0x00000001, 0x00000001},
  {"PTP_NXT"                              , 0x00000002, 0x00000001, 0x00000001},
  {"PTP_CFG"                              , 0x00000003, 0x00000001, 0x00000001},
  {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_SYS[] = {
  //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
  {"SYSTEM"                               , 0x00000142, 0x00000001, 0x00000040, regs_within_SYS_SYSTEM},
#ifndef VTSS_RELEASE
  {"COREMEM"                              , 0x00000140, 0x00000001, 0x00000002, regs_within_SYS_COREMEM},
#endif
  {"PAUSE_CFG"                            , 0x00000182, 0x00000001, 0x00000025, regs_within_SYS_PAUSE_CFG},
  {"MMGT"                                 , 0x000001a7, 0x00000001, 0x00000002, regs_within_SYS_MMGT},
#ifndef VTSS_RELEASE
  {"MISC"                                 , 0x000001a9, 0x00000001, 0x00000005, regs_within_SYS_MISC},
#endif
  {"STAT"                                 , 0x00000000, 0x00000140, 0x00000001, regs_within_SYS_STAT},
  {"PTP"                                  , 0x000001ae, 0x00000001, 0x00000004, regs_within_SYS_PTP},
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
static const vtss_symreg_target_t vtss_symreg_targets[] = {
  //target name         , repl, tgt_id    , base_addr                  , register group list
  {"ANA"                ,   -1, 0x00000088, VTSS_IO_OFFSET2(0x00880000), reggrps_within_ANA},
  {"DEV"                ,    0, 0x0000001e, VTSS_IO_OFFSET2(0x001e0000), reggrps_within_DEV},
  {"DEV"                ,    1, 0x0000001f, VTSS_IO_OFFSET2(0x001f0000), reggrps_within_DEV},
  {"DEV"                ,    2, 0x00000020, VTSS_IO_OFFSET2(0x00200000), reggrps_within_DEV},
  {"DEV"                ,    3, 0x00000021, VTSS_IO_OFFSET2(0x00210000), reggrps_within_DEV},
  {"DEV"                ,    4, 0x00000022, VTSS_IO_OFFSET2(0x00220000), reggrps_within_DEV},
  {"DEV"                ,    5, 0x00000023, VTSS_IO_OFFSET2(0x00230000), reggrps_within_DEV},
  {"DEV"                ,    6, 0x00000024, VTSS_IO_OFFSET2(0x00240000), reggrps_within_DEV},
  {"DEV"                ,    7, 0x00000025, VTSS_IO_OFFSET2(0x00250000), reggrps_within_DEV},
  {"DEV"                ,    8, 0x00000026, VTSS_IO_OFFSET2(0x00260000), reggrps_within_DEV},
  {"DEV"                ,    9, 0x00000027, VTSS_IO_OFFSET2(0x00270000), reggrps_within_DEV},
  {"DEV"                ,   10, 0x00000028, VTSS_IO_OFFSET2(0x00280000), reggrps_within_DEV},
  {"DEVCPU_GCB"         ,   -1, 0x00000007, VTSS_IO_OFFSET2(0x00070000), reggrps_within_DEVCPU_GCB},
  {"DEVCPU_ORG"         ,   -1, 0x00000000, VTSS_IO_OFFSET2(0x00000000), reggrps_within_DEVCPU_ORG},
  {"DEVCPU_PTP"         ,   -1, 0x0000000e, VTSS_IO_OFFSET2(0x000e0000), reggrps_within_DEVCPU_PTP},
  {"DEVCPU_QS"          ,   -1, 0x00000008, VTSS_IO_OFFSET2(0x00080000), reggrps_within_DEVCPU_QS},
  {"ES0"                ,   -1, 0x00000004, VTSS_IO_OFFSET2(0x00040000), reggrps_within_VCAP_CORE},
  {"HSIO"               ,   -1, 0x0000000d, VTSS_IO_OFFSET2(0x000d0000), reggrps_within_HSIO},
  {"ICPU_CFG"           ,   -1, 0x000000f1, VTSS_IO_OFFSET1(0x00000000), reggrps_within_ICPU_CFG},
  {"S1"                 ,   -1, 0x00000005, VTSS_IO_OFFSET2(0x00050000), reggrps_within_VCAP_CORE},
  {"S2"                 ,   -1, 0x00000006, VTSS_IO_OFFSET2(0x00060000), reggrps_within_VCAP_CORE},
  {"OAM_MEP"            ,   -1, 0x0000000c, VTSS_IO_OFFSET2(0x000c0000), reggrps_within_OAM_MEP},
  {"PCIE"               ,   -1, 0x000000f5, VTSS_IO_OFFSET1(0x00111000), reggrps_within_PCIE},
  {"QSYS"               ,   -1, 0x00000080, VTSS_IO_OFFSET2(0x00800000), reggrps_within_QSYS},
  {"REW"                ,   -1, 0x00000003, VTSS_IO_OFFSET2(0x00030000), reggrps_within_REW},
  {"SBA"                ,   -1, 0x000000f4, VTSS_IO_OFFSET1(0x00110000), reggrps_within_SBA},
  {"SIMC"               ,   -1, 0x000000f8, VTSS_IO_OFFSET1(0x00101000), reggrps_within_SIMC},
  {"SYS"                ,   -1, 0x00000001, VTSS_IO_OFFSET2(0x00010000), reggrps_within_SYS},
  {"TWI"                ,   -1, 0x000000f3, VTSS_IO_OFFSET1(0x00100400), reggrps_within_TWI},
  {"UART"               ,   -1, 0x000000f2, VTSS_IO_OFFSET1(0x00100000), reggrps_within_UART},
  {"UART2"              ,   -1, 0x000000f6, VTSS_IO_OFFSET1(0x00100800), reggrps_within_UART},
};

#define SYMREG_REPL_CNT_MAX 4096
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
#endif /* VTSS_ARCH_OCELOT */
