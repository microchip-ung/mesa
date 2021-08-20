/*
 Copyright (c) 2004-2018 Microsemi Corporation "Microsemi".

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
#ifdef VTSS_ARCH_LAGUNA
#ifdef VTSS_OPT_SYMREG
#define VTSS_IO_ORIGIN1_OFFSET 0x0e2000000 /*! default region*/
#define VTSS_IO_ORIGIN1_SIZE 0x010000000
#ifndef VTSS_IO_OFFSET1
#define VTSS_IO_OFFSET1(offset) (VTSS_IO_ORIGIN1_OFFSET + offset)
#endif
#define VTSS_IO_ORIGIN2_OFFSET 0x0e0000000 /*! amba_axi_top region*/
#define VTSS_IO_ORIGIN2_SIZE 0x000000000
#ifndef VTSS_IO_OFFSET2
#define VTSS_IO_OFFSET2(offset) (VTSS_IO_ORIGIN2_OFFSET + offset)
#endif
static const vtss_symreg_reg_t regs_within_AES_AES_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AES_CR"                               , 0x00000000, 0x00000001, 0x00000001},
    {"AES_MR"                               , 0x00000001, 0x00000001, 0x00000001},
    {"AES_IER"                              , 0x00000004, 0x00000001, 0x00000001},
    {"AES_IDR"                              , 0x00000005, 0x00000001, 0x00000001},
    {"AES_IMR"                              , 0x00000006, 0x00000001, 0x00000001},
    {"AES_ISR"                              , 0x00000007, 0x00000001, 0x00000001},
    {"AES_KEYWR0"                           , 0x00000008, 0x00000001, 0x00000001},
    {"AES_KEYWR1"                           , 0x00000009, 0x00000001, 0x00000001},
    {"AES_KEYWR2"                           , 0x0000000a, 0x00000001, 0x00000001},
    {"AES_KEYWR3"                           , 0x0000000b, 0x00000001, 0x00000001},
    {"AES_KEYWR4"                           , 0x0000000c, 0x00000001, 0x00000001},
    {"AES_KEYWR5"                           , 0x0000000d, 0x00000001, 0x00000001},
    {"AES_KEYWR6"                           , 0x0000000e, 0x00000001, 0x00000001},
    {"AES_KEYWR7"                           , 0x0000000f, 0x00000001, 0x00000001},
    {"AES_IDATAR0"                          , 0x00000010, 0x00000001, 0x00000001},
    {"AES_IDATAR1"                          , 0x00000011, 0x00000001, 0x00000001},
    {"AES_IDATAR2"                          , 0x00000012, 0x00000001, 0x00000001},
    {"AES_IDATAR3"                          , 0x00000013, 0x00000001, 0x00000001},
    {"AES_ODATAR0"                          , 0x00000014, 0x00000001, 0x00000001},
    {"AES_ODATAR1"                          , 0x00000015, 0x00000001, 0x00000001},
    {"AES_ODATAR2"                          , 0x00000016, 0x00000001, 0x00000001},
    {"AES_ODATAR3"                          , 0x00000017, 0x00000001, 0x00000001},
    {"AES_IVR0"                             , 0x00000018, 0x00000001, 0x00000001},
    {"AES_IVR1"                             , 0x00000019, 0x00000001, 0x00000001},
    {"AES_IVR2"                             , 0x0000001a, 0x00000001, 0x00000001},
    {"AES_IVR3"                             , 0x0000001b, 0x00000001, 0x00000001},
    {"AES_AADLENR"                          , 0x0000001c, 0x00000001, 0x00000001},
    {"AES_CLENR"                            , 0x0000001d, 0x00000001, 0x00000001},
    {"AES_GHASHR0"                          , 0x0000001e, 0x00000001, 0x00000001},
    {"AES_GHASHR1"                          , 0x0000001f, 0x00000001, 0x00000001},
    {"AES_GHASHR2"                          , 0x00000020, 0x00000001, 0x00000001},
    {"AES_GHASHR3"                          , 0x00000021, 0x00000001, 0x00000001},
    {"AES_TAGR0"                            , 0x00000022, 0x00000001, 0x00000001},
    {"AES_TAGR1"                            , 0x00000023, 0x00000001, 0x00000001},
    {"AES_TAGR2"                            , 0x00000024, 0x00000001, 0x00000001},
    {"AES_TAGR3"                            , 0x00000025, 0x00000001, 0x00000001},
    {"AES_CTRR"                             , 0x00000026, 0x00000001, 0x00000001},
    {"AES_GCMHR0"                           , 0x00000027, 0x00000001, 0x00000001},
    {"AES_GCMHR1"                           , 0x00000028, 0x00000001, 0x00000001},
    {"AES_GCMHR2"                           , 0x00000029, 0x00000001, 0x00000001},
    {"AES_GCMHR3"                           , 0x0000002a, 0x00000001, 0x00000001},
    {"AES_EMR"                              , 0x0000002c, 0x00000001, 0x00000001},
    {"AES_BCNT"                             , 0x0000002d, 0x00000001, 0x00000001},
    {"AES_TWR0"                             , 0x00000030, 0x00000001, 0x00000001},
    {"AES_TWR1"                             , 0x00000031, 0x00000001, 0x00000001},
    {"AES_TWR2"                             , 0x00000032, 0x00000001, 0x00000001},
    {"AES_TWR3"                             , 0x00000033, 0x00000001, 0x00000001},
    {"AES_ALPHAR0"                          , 0x00000034, 0x00000001, 0x00000001},
    {"AES_ALPHAR1"                          , 0x00000035, 0x00000001, 0x00000001},
    {"AES_ALPHAR2"                          , 0x00000036, 0x00000001, 0x00000001},
    {"AES_ALPHAR3"                          , 0x00000037, 0x00000001, 0x00000001},
    {"AES_WPMR"                             , 0x00000039, 0x00000001, 0x00000001},
    {"AES_WPSR"                             , 0x0000003a, 0x00000001, 0x00000001},
    {"AES_VERSION"                          , 0x0000003f, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_AES[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"AES_REGS"                             , 0x00000000, 0x00000001, 0x00000040, regs_within_AES_AES_REGS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_AESB_ASC_AESB_ASC_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TZAESBASC_RBAR0"                      , 0x00000000, 0x00000001, 0x00000001},
    {"TZAESBASC_RTAR0"                      , 0x00000001, 0x00000001, 0x00000001},
    {"TZAESBASC_RBAR1"                      , 0x00000002, 0x00000001, 0x00000001},
    {"TZAESBASC_RTAR1"                      , 0x00000003, 0x00000001, 0x00000001},
    {"TZAESBASC_RBAR2"                      , 0x00000004, 0x00000001, 0x00000001},
    {"TZAESBASC_RTAR2"                      , 0x00000005, 0x00000001, 0x00000001},
    {"TZAESBASC_RBAR3"                      , 0x00000006, 0x00000001, 0x00000001},
    {"TZAESBASC_RTAR3"                      , 0x00000007, 0x00000001, 0x00000001},
    {"TZAESBASC_RBAR4"                      , 0x00000008, 0x00000001, 0x00000001},
    {"TZAESBASC_RTAR4"                      , 0x00000009, 0x00000001, 0x00000001},
    {"TZAESBASC_RBAR5"                      , 0x0000000a, 0x00000001, 0x00000001},
    {"TZAESBASC_RTAR5"                      , 0x0000000b, 0x00000001, 0x00000001},
    {"TZAESBASC_RBAR6"                      , 0x0000000c, 0x00000001, 0x00000001},
    {"TZAESBASC_RTAR6"                      , 0x0000000d, 0x00000001, 0x00000001},
    {"TZAESBASC_RBAR7"                      , 0x0000000e, 0x00000001, 0x00000001},
    {"TZAESBASC_RTAR7"                      , 0x0000000f, 0x00000001, 0x00000001},
    {"TZAESBASC_RSECR"                      , 0x00000020, 0x00000001, 0x00000001},
    {"TZAESBASC_RER"                        , 0x00000021, 0x00000001, 0x00000001},
    {"TZAESBASC_RDR"                        , 0x00000022, 0x00000001, 0x00000001},
    {"TZAESBASC_RSR"                        , 0x00000023, 0x00000001, 0x00000001},
    {"TZAESBASC_RESR"                       , 0x00000024, 0x00000001, 0x00000001},
    {"TZAESBASC_RSSR"                       , 0x00000025, 0x00000001, 0x00000001},
    {"TZAESBASC_WPMR"                       , 0x00000039, 0x00000001, 0x00000001},
    {"TZAESBASC_WPSR"                       , 0x0000003a, 0x00000001, 0x00000001},
    {"TZAESBASC_VERSION"                    , 0x0000003f, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_AESB_ASC[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"AESB_ASC_REGS"                        , 0x00000000, 0x00000001, 0x00000040, regs_within_AESB_ASC_AESB_ASC_REGS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_CPU_CPU_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GPR"                                  , 0x00000000, 0x00000020, 0x00000001},
    {"BUILDID"                              , 0x00000020, 0x00000001, 0x00000001},
    {"RESET"                                , 0x00000021, 0x00000001, 0x00000001},
    {"RESET_PROT_STAT"                      , 0x00000022, 0x00000001, 0x00000001},
    {"GENERAL_CTRL"                         , 0x00000023, 0x00000001, 0x00000001},
    {"GENERAL_STAT"                         , 0x00000024, 0x00000001, 0x00000001},
    {"OTP_STAT"                             , 0x00000025, 0x00000001, 0x00000001},
    {"CPU_DBG"                              , 0x00000026, 0x00000001, 0x00000001},
    {"ENDIANNESS"                           , 0x00000027, 0x00000001, 0x00000001},
    {"PROC_CTRL"                            , 0x00000028, 0x00000001, 0x00000001},
    {"PROC_STAT"                            , 0x00000029, 0x00000001, 0x00000001},
    {"CPU0_RVBAR_LSB"                       , 0x0000002a, 0x00000001, 0x00000001},
    {"CPU0_RVBAR_MSB"                       , 0x0000002b, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CPU_GCK_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GCK_CFG"                              , 0x00000000, 0x0000000e, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CPU_USB_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"USB_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
    {"USB_CTRL"                             , 0x00000001, 0x00000001, 0x00000001},
    {"USB_STAT"                             , 0x00000002, 0x00000001, 0x00000001},
    {"USB_INTR"                             , 0x00000003, 0x00000001, 0x00000001},
    {"USB_INTR_ENA"                         , 0x00000004, 0x00000001, 0x00000001},
    {"USB_INTR_IDENT"                       , 0x00000005, 0x00000001, 0x00000001},
    {"USB_DEBUG1"                           , 0x00000006, 0x00000001, 0x00000001},
    {"USB_DEBUG2"                           , 0x00000007, 0x00000001, 0x00000001},
    {"USB_DEBUG3"                           , 0x00000008, 0x00000001, 0x00000001},
    {"USB_LA_TRACE1"                        , 0x00000009, 0x00000001, 0x00000001},
    {"USB_LA_TRACE2"                        , 0x0000000a, 0x00000001, 0x00000001},
    {"USB_GGPIO"                            , 0x0000000b, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CPU_MIIM_TARGET[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MIIM_TARGET_CFG"                      , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CPU_VCORE_ACC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCORE_ACC_CFG"                        , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CPU_MSIX_ACC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MSIX_ACC_CFG"                         , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CPU_EXT_IF_ACC_STAT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EXT_IF_ACC_STAT"                      , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CPU_INTR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INTR_RAW"                             , 0x00000000, 0x00000001, 0x00000001},
    {"INTR_RAW1"                            , 0x00000001, 0x00000001, 0x00000001},
    {"INTR_RAW2"                            , 0x00000002, 0x00000001, 0x00000001},
    {"INTR_TRIGGER"                         , 0x00000003, 0x00000002, 0x00000001},
    {"INTR_TRIGGER1"                        , 0x00000005, 0x00000002, 0x00000001},
    {"INTR_TRIGGER2"                        , 0x00000007, 0x00000002, 0x00000001},
    {"INTR_FORCE"                           , 0x00000009, 0x00000001, 0x00000001},
    {"INTR_FORCE1"                          , 0x0000000a, 0x00000001, 0x00000001},
    {"INTR_FORCE2"                          , 0x0000000b, 0x00000001, 0x00000001},
    {"INTR_STICKY"                          , 0x0000000c, 0x00000001, 0x00000001},
    {"INTR_STICKY1"                         , 0x0000000d, 0x00000001, 0x00000001},
    {"INTR_STICKY2"                         , 0x0000000e, 0x00000001, 0x00000001},
    {"INTR_BYPASS"                          , 0x0000000f, 0x00000001, 0x00000001},
    {"INTR_BYPASS1"                         , 0x00000010, 0x00000001, 0x00000001},
    {"INTR_BYPASS2"                         , 0x00000011, 0x00000001, 0x00000001},
    {"INTR_ENA"                             , 0x00000012, 0x00000001, 0x00000001},
    {"INTR_ENA1"                            , 0x00000013, 0x00000001, 0x00000001},
    {"INTR_ENA2"                            , 0x00000014, 0x00000001, 0x00000001},
    {"INTR_ENA_CLR"                         , 0x00000015, 0x00000001, 0x00000001},
    {"INTR_ENA_CLR1"                        , 0x00000016, 0x00000001, 0x00000001},
    {"INTR_ENA_CLR2"                        , 0x00000017, 0x00000001, 0x00000001},
    {"INTR_ENA_SET"                         , 0x00000018, 0x00000001, 0x00000001},
    {"INTR_ENA_SET1"                        , 0x00000019, 0x00000001, 0x00000001},
    {"INTR_ENA_SET2"                        , 0x0000001a, 0x00000001, 0x00000001},
    {"INTR_IDENT"                           , 0x0000001b, 0x00000001, 0x00000001},
    {"INTR_IDENT1"                          , 0x0000001c, 0x00000001, 0x00000001},
    {"INTR_IDENT2"                          , 0x0000001d, 0x00000001, 0x00000001},
    {"DST_INTR_MAP"                         , 0x0000001e, 0x00000009, 0x00000001},
    {"DST_INTR_MAP1"                        , 0x00000027, 0x00000009, 0x00000001},
    {"DST_INTR_MAP2"                        , 0x00000030, 0x00000009, 0x00000001},
    {"DST_INTR_IDENT"                       , 0x00000039, 0x00000009, 0x00000001},
    {"DST_INTR_IDENT1"                      , 0x00000042, 0x00000009, 0x00000001},
    {"DST_INTR_IDENT2"                      , 0x0000004b, 0x00000009, 0x00000001},
    {"EXT_SRC_INTR_POL"                     , 0x00000054, 0x00000001, 0x00000001},
    {"EXT_DST_INTR_POL"                     , 0x00000055, 0x00000001, 0x00000001},
    {"EXT_DST_INTR_DRV"                     , 0x00000056, 0x00000001, 0x00000001},
    {"DEV_INTR_POL"                         , 0x00000057, 0x00000001, 0x00000001},
    {"DEV_INTR_RAW"                         , 0x00000058, 0x00000001, 0x00000001},
    {"DEV_INTR_TRIGGER"                     , 0x00000059, 0x00000002, 0x00000001},
    {"DEV_INTR_STICKY"                      , 0x0000005b, 0x00000001, 0x00000001},
    {"DEV_INTR_BYPASS"                      , 0x0000005c, 0x00000001, 0x00000001},
    {"DEV_INTR_ENA"                         , 0x0000005d, 0x00000001, 0x00000001},
    {"DEV_INTR_IDENT"                       , 0x0000005e, 0x00000001, 0x00000001},
    {"MSIX_CFG"                             , 0x0000005f, 0x00000001, 0x00000001},
    {"MSIX_DOORBELL_ADDR"                   , 0x00000060, 0x00000001, 0x00000001},
    {"MSIX_INTR_PENDING"                    , 0x00000061, 0x00000001, 0x00000001},
    {"MSIX_INTR_PENDING1"                   , 0x00000062, 0x00000001, 0x00000001},
    {"MSIX_INTR_PENDING2"                   , 0x00000063, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CPU_DDRCTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DDRCTRL_CLK"                          , 0x00000000, 0x00000001, 0x00000001},
    {"DDRCTRL_RST"                          , 0x00000001, 0x00000001, 0x00000001},
    {"DDRC_INTR_RAW_STAT"                   , 0x00000002, 0x00000001, 0x00000001},
    {"DDRC_INTR_MASK"                       , 0x00000003, 0x00000001, 0x00000001},
    {"DDRC_INTR_MASKED_STAT"                , 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CPU_SFR_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CLK_GATING"                           , 0x00000000, 0x00000001, 0x00000001},
    {"AHBLITE2AXI"                          , 0x00000001, 0x00000001, 0x00000001},
    {"TZAESB"                               , 0x00000002, 0x00000001, 0x00000001},
    {"MCAN"                                 , 0x00000003, 0x00000001, 0x00000001},
    {"HICM"                                 , 0x00000004, 0x00000001, 0x00000001},
    {"UDPHS"                                , 0x00000005, 0x00000001, 0x00000001},
    {"UDDR"                                 , 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CPU_PCIE_PHY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PHY_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
    {"PHY_TUNE"                             , 0x00000001, 0x00000001, 0x00000001},
    {"PCS_CFG"                              , 0x00000002, 0x00000001, 0x00000001},
    {"PHY_CR_CTRL"                          , 0x00000003, 0x00000001, 0x00000001},
    {"PHY_CR_DATA"                          , 0x00000004, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_CPU[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"CPU_REGS"                             , 0x00000000, 0x00000001, 0x0000002c, regs_within_CPU_CPU_REGS},
    {"GCK_REGS"                             , 0x0000002c, 0x00000001, 0x0000000e, regs_within_CPU_GCK_REGS},
    {"USB_REGS"                             , 0x0000003a, 0x00000001, 0x0000000c, regs_within_CPU_USB_REGS},
    {"MIIM_TARGET"                          , 0x00000046, 0x00000001, 0x00000001, regs_within_CPU_MIIM_TARGET},
    {"VCORE_ACC"                            , 0x00000047, 0x00000001, 0x00000001, regs_within_CPU_VCORE_ACC},
#ifndef VTSS_RELEASE
    {"MSIX_ACC"                             , 0x00000048, 0x00000001, 0x00000001, regs_within_CPU_MSIX_ACC},
#endif
#ifndef VTSS_RELEASE
    {"EXT_IF_ACC_STAT"                      , 0x00000049, 0x00000001, 0x00000001, regs_within_CPU_EXT_IF_ACC_STAT},
#endif
    {"INTR"                                 , 0x0000004a, 0x00000001, 0x00000064, regs_within_CPU_INTR},
    {"DDRCTRL"                              , 0x000000ae, 0x00000001, 0x00000005, regs_within_CPU_DDRCTRL},
    {"SFR_REGS"                             , 0x000000b3, 0x00000001, 0x00000007, regs_within_CPU_SFR_REGS},
    {"PCIE_PHY"                             , 0x000000ba, 0x00000001, 0x00000005, regs_within_CPU_PCIE_PHY},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DDR_PHY_DDR3_2_PHY_PUB[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"RIDR"                                 , 0x00000000, 0x00000001, 0x00000001},
    {"PIR"                                  , 0x00000001, 0x00000001, 0x00000001},
    {"PGCR0"                                , 0x00000002, 0x00000001, 0x00000001},
    {"PGCR1"                                , 0x00000003, 0x00000001, 0x00000001},
    {"PGSR0"                                , 0x00000004, 0x00000001, 0x00000001},
    {"PGSR1"                                , 0x00000005, 0x00000001, 0x00000001},
    {"PLLCR"                                , 0x00000006, 0x00000001, 0x00000001},
    {"PTR0"                                 , 0x00000007, 0x00000001, 0x00000001},
    {"PTR1"                                 , 0x00000008, 0x00000001, 0x00000001},
    {"PTR2"                                 , 0x00000009, 0x00000001, 0x00000001},
    {"PTR3"                                 , 0x0000000a, 0x00000001, 0x00000001},
    {"PTR4"                                 , 0x0000000b, 0x00000001, 0x00000001},
    {"ACMDLR"                               , 0x0000000c, 0x00000001, 0x00000001},
    {"ACBDLR"                               , 0x0000000d, 0x00000001, 0x00000001},
    {"ACIOCR"                               , 0x0000000e, 0x00000001, 0x00000001},
    {"DXCCR"                                , 0x0000000f, 0x00000001, 0x00000001},
    {"DSGCR"                                , 0x00000010, 0x00000001, 0x00000001},
    {"DCR"                                  , 0x00000011, 0x00000001, 0x00000001},
    {"DTPR0"                                , 0x00000012, 0x00000001, 0x00000001},
    {"DTPR1"                                , 0x00000013, 0x00000001, 0x00000001},
    {"DTPR2"                                , 0x00000014, 0x00000001, 0x00000001},
    {"MR0"                                  , 0x00000015, 0x00000001, 0x00000001},
    {"MR1"                                  , 0x00000016, 0x00000001, 0x00000001},
    {"MR2"                                  , 0x00000017, 0x00000001, 0x00000001},
    {"MR3"                                  , 0x00000018, 0x00000001, 0x00000001},
    {"ODTCR"                                , 0x00000019, 0x00000001, 0x00000001},
    {"DTCR"                                 , 0x0000001a, 0x00000001, 0x00000001},
    {"DTAR0"                                , 0x0000001b, 0x00000001, 0x00000001},
    {"DTAR1"                                , 0x0000001c, 0x00000001, 0x00000001},
    {"DTAR2"                                , 0x0000001d, 0x00000001, 0x00000001},
    {"DTAR3"                                , 0x0000001e, 0x00000001, 0x00000001},
    {"DTDR0"                                , 0x0000001f, 0x00000001, 0x00000001},
    {"DTDR1"                                , 0x00000020, 0x00000001, 0x00000001},
    {"DTEDR0"                               , 0x00000021, 0x00000001, 0x00000001},
    {"DTEDR1"                               , 0x00000022, 0x00000001, 0x00000001},
    {"PGCR2"                                , 0x00000023, 0x00000001, 0x00000001},
    {"RDIMMGCR0"                            , 0x0000002c, 0x00000001, 0x00000001},
    {"RDIMMGCR1"                            , 0x0000002d, 0x00000001, 0x00000001},
    {"RDIMMCR0"                             , 0x0000002e, 0x00000001, 0x00000001},
    {"RDIMMCR1"                             , 0x0000002f, 0x00000001, 0x00000001},
    {"DCUAR"                                , 0x00000030, 0x00000001, 0x00000001},
    {"DCUDR"                                , 0x00000031, 0x00000001, 0x00000001},
    {"DCURR"                                , 0x00000032, 0x00000001, 0x00000001},
    {"DCULR"                                , 0x00000033, 0x00000001, 0x00000001},
    {"DCUGCR"                               , 0x00000034, 0x00000001, 0x00000001},
    {"DCUTPR"                               , 0x00000035, 0x00000001, 0x00000001},
    {"DCUSR0"                               , 0x00000036, 0x00000001, 0x00000001},
    {"DCUSR1"                               , 0x00000037, 0x00000001, 0x00000001},
    {"BISTRR"                               , 0x00000040, 0x00000001, 0x00000001},
    {"BISTWCR"                              , 0x00000041, 0x00000001, 0x00000001},
    {"BISTMSKR0"                            , 0x00000042, 0x00000001, 0x00000001},
    {"BISTMSKR1"                            , 0x00000043, 0x00000001, 0x00000001},
    {"BISTMSKR2"                            , 0x00000044, 0x00000001, 0x00000001},
    {"BISTLSR"                              , 0x00000045, 0x00000001, 0x00000001},
    {"BISTAR0"                              , 0x00000046, 0x00000001, 0x00000001},
    {"BISTAR1"                              , 0x00000047, 0x00000001, 0x00000001},
    {"BISTAR2"                              , 0x00000048, 0x00000001, 0x00000001},
    {"BISTUDPR"                             , 0x00000049, 0x00000001, 0x00000001},
    {"BISTGSR"                              , 0x0000004a, 0x00000001, 0x00000001},
    {"BISTWER"                              , 0x0000004b, 0x00000001, 0x00000001},
    {"BISTBER0"                             , 0x0000004c, 0x00000001, 0x00000001},
    {"BISTBER1"                             , 0x0000004d, 0x00000001, 0x00000001},
    {"BISTBER2"                             , 0x0000004e, 0x00000001, 0x00000001},
    {"BISTBER3"                             , 0x0000004f, 0x00000001, 0x00000001},
    {"BISTWCSR"                             , 0x00000050, 0x00000001, 0x00000001},
    {"BISTFWR0"                             , 0x00000051, 0x00000001, 0x00000001},
    {"BISTFWR1"                             , 0x00000052, 0x00000001, 0x00000001},
    {"BISTFWR2"                             , 0x00000053, 0x00000001, 0x00000001},
    {"AACR"                                 , 0x0000005d, 0x00000001, 0x00000001},
    {"ZQ0CR0"                               , 0x00000060, 0x00000001, 0x00000001},
    {"ZQ0CR1"                               , 0x00000061, 0x00000001, 0x00000001},
    {"ZQ0SR0"                               , 0x00000062, 0x00000001, 0x00000001},
    {"ZQ0SR1"                               , 0x00000063, 0x00000001, 0x00000001},
    {"ZQ1CR0"                               , 0x00000064, 0x00000001, 0x00000001},
    {"ZQ1CR1"                               , 0x00000065, 0x00000001, 0x00000001},
    {"ZQ1SR0"                               , 0x00000066, 0x00000001, 0x00000001},
    {"ZQ1SR1"                               , 0x00000067, 0x00000001, 0x00000001},
    {"DX0GCR"                               , 0x00000070, 0x00000001, 0x00000001},
    {"DX0GSR0"                              , 0x00000071, 0x00000001, 0x00000001},
    {"DX0GSR1"                              , 0x00000072, 0x00000001, 0x00000001},
    {"DX0BDLR0"                             , 0x00000073, 0x00000001, 0x00000001},
    {"DX0BDLR1"                             , 0x00000074, 0x00000001, 0x00000001},
    {"DX0BDLR2"                             , 0x00000075, 0x00000001, 0x00000001},
    {"DX0BDLR3"                             , 0x00000076, 0x00000001, 0x00000001},
    {"DX0BDLR4"                             , 0x00000077, 0x00000001, 0x00000001},
    {"DX0LCDLR0"                            , 0x00000078, 0x00000001, 0x00000001},
    {"DX0LCDLR1"                            , 0x00000079, 0x00000001, 0x00000001},
    {"DX0LCDLR2"                            , 0x0000007a, 0x00000001, 0x00000001},
    {"DX0MDLR"                              , 0x0000007b, 0x00000001, 0x00000001},
    {"DX0GTR"                               , 0x0000007c, 0x00000001, 0x00000001},
    {"DX0GSR2"                              , 0x0000007d, 0x00000001, 0x00000001},
    {"DX1GCR"                               , 0x00000080, 0x00000001, 0x00000001},
    {"DX1GSR0"                              , 0x00000081, 0x00000001, 0x00000001},
    {"DX1GSR1"                              , 0x00000082, 0x00000001, 0x00000001},
    {"DX1BDLR0"                             , 0x00000083, 0x00000001, 0x00000001},
    {"DX1BDLR1"                             , 0x00000084, 0x00000001, 0x00000001},
    {"DX1BDLR2"                             , 0x00000085, 0x00000001, 0x00000001},
    {"DX1BDLR3"                             , 0x00000086, 0x00000001, 0x00000001},
    {"DX1BDLR4"                             , 0x00000087, 0x00000001, 0x00000001},
    {"DX1LCDLR0"                            , 0x00000088, 0x00000001, 0x00000001},
    {"DX1LCDLR1"                            , 0x00000089, 0x00000001, 0x00000001},
    {"DX1LCDLR2"                            , 0x0000008a, 0x00000001, 0x00000001},
    {"DX1MDLR"                              , 0x0000008b, 0x00000001, 0x00000001},
    {"DX1GTR"                               , 0x0000008c, 0x00000001, 0x00000001},
    {"DX1GSR2"                              , 0x0000008d, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DDR_PHY[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DDR3_2_PHY_PUB"                       , 0x00000000, 0x00000001, 0x00000400, regs_within_DDR_PHY_DDR3_2_PHY_PUB},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DDR_UMCTL2_UMCTL2_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MSTR"                                 , 0x00000000, 0x00000001, 0x00000001},
    {"STAT"                                 , 0x00000001, 0x00000001, 0x00000001},
    {"MRCTRL0"                              , 0x00000004, 0x00000001, 0x00000001},
    {"MRCTRL1"                              , 0x00000005, 0x00000001, 0x00000001},
    {"MRSTAT"                               , 0x00000006, 0x00000001, 0x00000001},
    {"PWRCTL"                               , 0x0000000c, 0x00000001, 0x00000001},
    {"PWRTMG"                               , 0x0000000d, 0x00000001, 0x00000001},
    {"HWLPCTL"                              , 0x0000000e, 0x00000001, 0x00000001},
    {"RFSHCTL0"                             , 0x00000014, 0x00000001, 0x00000001},
    {"RFSHCTL1"                             , 0x00000015, 0x00000001, 0x00000001},
    {"RFSHCTL3"                             , 0x00000018, 0x00000001, 0x00000001},
    {"RFSHTMG"                              , 0x00000019, 0x00000001, 0x00000001},
    {"ECCCFG0"                              , 0x0000001c, 0x00000001, 0x00000001},
    {"ECCCFG1"                              , 0x0000001d, 0x00000001, 0x00000001},
    {"ECCSTAT"                              , 0x0000001e, 0x00000001, 0x00000001},
    {"ECCCTL"                               , 0x0000001f, 0x00000001, 0x00000001},
    {"ECCERRCNT"                            , 0x00000020, 0x00000001, 0x00000001},
    {"ECCCADDR0"                            , 0x00000021, 0x00000001, 0x00000001},
    {"ECCCADDR1"                            , 0x00000022, 0x00000001, 0x00000001},
    {"ECCCSYN0"                             , 0x00000023, 0x00000001, 0x00000001},
    {"ECCCSYN1"                             , 0x00000024, 0x00000001, 0x00000001},
    {"ECCCSYN2"                             , 0x00000025, 0x00000001, 0x00000001},
    {"ECCBITMASK0"                          , 0x00000026, 0x00000001, 0x00000001},
    {"ECCBITMASK1"                          , 0x00000027, 0x00000001, 0x00000001},
    {"ECCBITMASK2"                          , 0x00000028, 0x00000001, 0x00000001},
    {"ECCUADDR0"                            , 0x00000029, 0x00000001, 0x00000001},
    {"ECCUADDR1"                            , 0x0000002a, 0x00000001, 0x00000001},
    {"ECCUSYN0"                             , 0x0000002b, 0x00000001, 0x00000001},
    {"ECCUSYN1"                             , 0x0000002c, 0x00000001, 0x00000001},
    {"ECCUSYN2"                             , 0x0000002d, 0x00000001, 0x00000001},
    {"ECCPOISONADDR0"                       , 0x0000002e, 0x00000001, 0x00000001},
    {"ECCPOISONADDR1"                       , 0x0000002f, 0x00000001, 0x00000001},
    {"CRCPARCTL0"                           , 0x00000030, 0x00000001, 0x00000001},
    {"CRCPARSTAT"                           , 0x00000033, 0x00000001, 0x00000001},
    {"INIT0"                                , 0x00000034, 0x00000001, 0x00000001},
    {"INIT1"                                , 0x00000035, 0x00000001, 0x00000001},
    {"INIT3"                                , 0x00000037, 0x00000001, 0x00000001},
    {"INIT4"                                , 0x00000038, 0x00000001, 0x00000001},
    {"INIT5"                                , 0x00000039, 0x00000001, 0x00000001},
    {"DIMMCTL"                              , 0x0000003c, 0x00000001, 0x00000001},
    {"RANKCTL"                              , 0x0000003d, 0x00000001, 0x00000001},
    {"DRAMTMG0"                             , 0x00000040, 0x00000001, 0x00000001},
    {"DRAMTMG1"                             , 0x00000041, 0x00000001, 0x00000001},
    {"DRAMTMG2"                             , 0x00000042, 0x00000001, 0x00000001},
    {"DRAMTMG3"                             , 0x00000043, 0x00000001, 0x00000001},
    {"DRAMTMG4"                             , 0x00000044, 0x00000001, 0x00000001},
    {"DRAMTMG5"                             , 0x00000045, 0x00000001, 0x00000001},
    {"DRAMTMG8"                             , 0x00000048, 0x00000001, 0x00000001},
    {"DRAMTMG15"                            , 0x0000004f, 0x00000001, 0x00000001},
    {"ZQCTL0"                               , 0x00000060, 0x00000001, 0x00000001},
    {"ZQCTL1"                               , 0x00000061, 0x00000001, 0x00000001},
    {"DFITMG0"                              , 0x00000064, 0x00000001, 0x00000001},
    {"DFITMG1"                              , 0x00000065, 0x00000001, 0x00000001},
    {"DFILPCFG0"                            , 0x00000066, 0x00000001, 0x00000001},
    {"DFIUPD0"                              , 0x00000068, 0x00000001, 0x00000001},
    {"DFIUPD1"                              , 0x00000069, 0x00000001, 0x00000001},
    {"DFIUPD2"                              , 0x0000006a, 0x00000001, 0x00000001},
    {"DFIMISC"                              , 0x0000006c, 0x00000001, 0x00000001},
    {"DFISTAT"                              , 0x0000006f, 0x00000001, 0x00000001},
    {"DFIPHYMSTR"                           , 0x00000071, 0x00000001, 0x00000001},
    {"ADDRMAP0"                             , 0x00000080, 0x00000001, 0x00000001},
    {"ADDRMAP1"                             , 0x00000081, 0x00000001, 0x00000001},
    {"ADDRMAP2"                             , 0x00000082, 0x00000001, 0x00000001},
    {"ADDRMAP3"                             , 0x00000083, 0x00000001, 0x00000001},
    {"ADDRMAP4"                             , 0x00000084, 0x00000001, 0x00000001},
    {"ADDRMAP5"                             , 0x00000085, 0x00000001, 0x00000001},
    {"ADDRMAP6"                             , 0x00000086, 0x00000001, 0x00000001},
    {"ADDRMAP9"                             , 0x00000089, 0x00000001, 0x00000001},
    {"ADDRMAP10"                            , 0x0000008a, 0x00000001, 0x00000001},
    {"ADDRMAP11"                            , 0x0000008b, 0x00000001, 0x00000001},
    {"ODTCFG"                               , 0x00000090, 0x00000001, 0x00000001},
    {"ODTMAP"                               , 0x00000091, 0x00000001, 0x00000001},
    {"SCHED"                                , 0x00000094, 0x00000001, 0x00000001},
    {"SCHED1"                               , 0x00000095, 0x00000001, 0x00000001},
    {"PERFHPR1"                             , 0x00000097, 0x00000001, 0x00000001},
    {"PERFLPR1"                             , 0x00000099, 0x00000001, 0x00000001},
    {"PERFWR1"                              , 0x0000009b, 0x00000001, 0x00000001},
    {"DBG0"                                 , 0x000000c0, 0x00000001, 0x00000001},
    {"DBG1"                                 , 0x000000c1, 0x00000001, 0x00000001},
    {"DBGCAM"                               , 0x000000c2, 0x00000001, 0x00000001},
    {"DBGCMD"                               , 0x000000c3, 0x00000001, 0x00000001},
    {"DBGSTAT"                              , 0x000000c4, 0x00000001, 0x00000001},
    {"DBGCAM1"                              , 0x000000c6, 0x00000001, 0x00000001},
    {"SWCTL"                                , 0x000000c8, 0x00000001, 0x00000001},
    {"SWSTAT"                               , 0x000000c9, 0x00000001, 0x00000001},
    {"SWCTLSTATIC"                          , 0x000000ca, 0x00000001, 0x00000001},
    {"POISONCFG"                            , 0x000000db, 0x00000001, 0x00000001},
    {"POISONSTAT"                           , 0x000000dc, 0x00000001, 0x00000001},
    {"ADVECCINDEX"                          , 0x000000dd, 0x00000001, 0x00000001},
    {"ECCPOISONPAT0"                        , 0x000000df, 0x00000001, 0x00000001},
    {"ECCPOISONPAT2"                        , 0x000000e1, 0x00000001, 0x00000001},
    {"ECCAPSTAT"                            , 0x000000e2, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DDR_UMCTL2_UMCTL2_MP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PSTAT"                                , 0x00000001, 0x00000001, 0x00000001},
    {"PCCFG"                                , 0x00000002, 0x00000001, 0x00000001},
    {"PCFGR_0"                              , 0x00000003, 0x00000001, 0x00000001},
    {"PCFGW_0"                              , 0x00000004, 0x00000001, 0x00000001},
    {"PCTRL_0"                              , 0x00000026, 0x00000001, 0x00000001},
    {"PCFGQOS0_0"                           , 0x00000027, 0x00000001, 0x00000001},
    {"PCFGQOS1_0"                           , 0x00000028, 0x00000001, 0x00000001},
    {"PCFGWQOS0_0"                          , 0x00000029, 0x00000001, 0x00000001},
    {"PCFGWQOS1_0"                          , 0x0000002a, 0x00000001, 0x00000001},
    {"PCFGR_1"                              , 0x0000002f, 0x00000001, 0x00000001},
    {"PCFGW_1"                              , 0x00000030, 0x00000001, 0x00000001},
    {"PCTRL_1"                              , 0x00000052, 0x00000001, 0x00000001},
    {"PCFGQOS0_1"                           , 0x00000053, 0x00000001, 0x00000001},
    {"PCFGQOS1_1"                           , 0x00000054, 0x00000001, 0x00000001},
    {"PCFGWQOS0_1"                          , 0x00000055, 0x00000001, 0x00000001},
    {"PCFGWQOS1_1"                          , 0x00000056, 0x00000001, 0x00000001},
    {"PCFGR_2"                              , 0x0000005b, 0x00000001, 0x00000001},
    {"PCFGW_2"                              , 0x0000005c, 0x00000001, 0x00000001},
    {"PCTRL_2"                              , 0x0000007e, 0x00000001, 0x00000001},
    {"PCFGQOS0_2"                           , 0x0000007f, 0x00000001, 0x00000001},
    {"PCFGQOS1_2"                           , 0x00000080, 0x00000001, 0x00000001},
    {"PCFGWQOS0_2"                          , 0x00000081, 0x00000001, 0x00000001},
    {"PCFGWQOS1_2"                          , 0x00000082, 0x00000001, 0x00000001},
    {"SARBASE0"                             , 0x000002c3, 0x00000001, 0x00000001},
    {"SARSIZE0"                             , 0x000002c4, 0x00000001, 0x00000001},
    {"SBRCTL"                               , 0x000002cb, 0x00000001, 0x00000001},
    {"SBRSTAT"                              , 0x000002cc, 0x00000001, 0x00000001},
    {"SBRWDATA0"                            , 0x000002cd, 0x00000001, 0x00000001},
    {"SBRSTART0"                            , 0x000002d0, 0x00000001, 0x00000001},
    {"SBRSTART1"                            , 0x000002d1, 0x00000001, 0x00000001},
    {"SBRRANGE0"                            , 0x000002d2, 0x00000001, 0x00000001},
    {"SBRRANGE1"                            , 0x000002d3, 0x00000001, 0x00000001},
    {"UMCTL2_VER_NUMBER"                    , 0x000002fe, 0x00000001, 0x00000001},
    {"UMCTL2_VER_TYPE"                      , 0x000002ff, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DDR_UMCTL2[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"UMCTL2_REGS"                          , 0x00000000, 0x00000001, 0x000000fe, regs_within_DDR_UMCTL2_UMCTL2_REGS},
    {"UMCTL2_MP"                            , 0x000000fe, 0x00000001, 0x000005c2, regs_within_DDR_UMCTL2_UMCTL2_MP},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_FDMA_FDMA[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FDMA_CH_ACTIVATE"                     , 0x00000000, 0x00000001, 0x00000001},
    {"FDMA_CH_RELOAD"                       , 0x00000001, 0x00000001, 0x00000001},
    {"FDMA_CH_DISABLE"                      , 0x00000002, 0x00000001, 0x00000001},
    {"FDMA_CH_FORCEDIS"                     , 0x00000003, 0x00000001, 0x00000001},
    {"FDMA_CH_DB_DISCARD"                   , 0x00000004, 0x00000001, 0x00000001},
    {"FDMA_CH_CNT"                          , 0x00000005, 0x00000008, 0x00000001},
    {"FDMA_DCB_LLP"                         , 0x0000000d, 0x00000008, 0x00000001},
    {"FDMA_DCB_LLP1"                        , 0x00000015, 0x00000008, 0x00000001},
    {"FDMA_DCB_LLP_PREV"                    , 0x0000001d, 0x00000008, 0x00000001},
    {"FDMA_DCB_LLP_PREV1"                   , 0x00000025, 0x00000008, 0x00000001},
    {"FDMA_CH_ACTIVE"                       , 0x0000002d, 0x00000001, 0x00000001},
    {"FDMA_CH_PENDING"                      , 0x0000002e, 0x00000001, 0x00000001},
    {"FDMA_CH_IDLE"                         , 0x0000002f, 0x00000001, 0x00000001},
    {"FDMA_CH_STATUS"                       , 0x00000030, 0x00000008, 0x00000001},
    {"FDMA_CH_CFG"                          , 0x00000038, 0x00000008, 0x00000001},
    {"FDMA_CH_TRANSLATE"                    , 0x00000040, 0x00000008, 0x00000001},
    {"FDMA_CH_INJ_TOKEN_CNT"                , 0x00000048, 0x00000006, 0x00000001},
    {"FDMA_CH_INJ_TOKEN_TICK_RLD"           , 0x0000004e, 0x00000006, 0x00000001},
    {"FDMA_CH_INJ_TOKEN_TICK_CNT"           , 0x00000054, 0x00000006, 0x00000001},
    {"FDMA_INJ_CFG"                         , 0x0000005a, 0x00000001, 0x00000001},
    {"FDMA_XTR_CFG"                         , 0x0000005b, 0x00000001, 0x00000001},
    {"FDMA_PORT_CFG"                        , 0x0000005c, 0x00000002, 0x00000001},
    {"FDMA_PORT_CTRL"                       , 0x0000005e, 0x00000002, 0x00000001},
    {"FDMA_INTR_DCB"                        , 0x00000060, 0x00000001, 0x00000001},
    {"FDMA_INTR_DCB_ENA"                    , 0x00000061, 0x00000001, 0x00000001},
    {"FDMA_INTR_DB"                         , 0x00000062, 0x00000001, 0x00000001},
    {"FDMA_INTR_DB_ENA"                     , 0x00000063, 0x00000001, 0x00000001},
    {"FDMA_INTR_ERR"                        , 0x00000064, 0x00000001, 0x00000001},
    {"FDMA_INTR_ENA"                        , 0x00000065, 0x00000001, 0x00000001},
    {"FDMA_INTR_IDENT"                      , 0x00000066, 0x00000001, 0x00000001},
    {"FDMA_ERRORS"                          , 0x00000067, 0x00000001, 0x00000001},
    {"FDMA_ERRORS_2"                        , 0x00000068, 0x00000001, 0x00000001},
    {"FDMA_IDLECNT"                         , 0x00000069, 0x00000001, 0x00000001},
    {"FDMA_CTRL"                            , 0x0000006a, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_FDMA_FDMA_HA[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FDMA_PORT_STAT"                       , 0x00000000, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_FDMA[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"FDMA"                                 , 0x00000002, 0x00000001, 0x0000006b, regs_within_FDMA_FDMA},
    {"FDMA_HA"                              , 0x00000000, 0x00000001, 0x00000002, regs_within_FDMA_FDMA_HA},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_FLEXCOM_FLEXCOM_REG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FLEX_MR"                              , 0x00000000, 0x00000001, 0x00000001},
    {"FLEX_RHR"                             , 0x00000004, 0x00000001, 0x00000001},
    {"FLEX_THR"                             , 0x00000008, 0x00000001, 0x00000001},
    {"FLEX_VERSION"                         , 0x0000003f, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_FLEXCOM_FLEXCOM_USART_REG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FLEX_US_CR"                           , 0x00000000, 0x00000001, 0x00000001},
    {"FLEX_US_MR"                           , 0x00000001, 0x00000001, 0x00000001},
    {"FLEX_US_IER"                          , 0x00000002, 0x00000001, 0x00000001},
    {"FLEX_US_IDR"                          , 0x00000003, 0x00000001, 0x00000001},
    {"FLEX_US_IMR"                          , 0x00000004, 0x00000001, 0x00000001},
    {"FLEX_US_CSR"                          , 0x00000005, 0x00000001, 0x00000001},
    {"FLEX_US_RHR"                          , 0x00000006, 0x00000001, 0x00000001},
    {"FLEX_US_FMT_RHR"                      , 0x00000006, 0x00000001, 0x00000001},
    {"FLEX_US_THR"                          , 0x00000007, 0x00000001, 0x00000001},
    {"FLEX_US_FMT_THR"                      , 0x00000007, 0x00000001, 0x00000001},
    {"FLEX_US_BRGR"                         , 0x00000008, 0x00000001, 0x00000001},
    {"FLEX_US_RTOR"                         , 0x00000009, 0x00000001, 0x00000001},
    {"FLEX_US_TTGR"                         , 0x0000000a, 0x00000001, 0x00000001},
    {"FLEX_US_MAN"                          , 0x00000014, 0x00000001, 0x00000001},
    {"FLEX_US_CMPR"                         , 0x00000024, 0x00000001, 0x00000001},
    {"FLEX_US_FMR"                          , 0x00000028, 0x00000001, 0x00000001},
    {"FLEX_US_FLR"                          , 0x00000029, 0x00000001, 0x00000001},
    {"FLEX_US_FIER"                         , 0x0000002a, 0x00000001, 0x00000001},
    {"FLEX_US_FIDR"                         , 0x0000002b, 0x00000001, 0x00000001},
    {"FLEX_US_FIMR"                         , 0x0000002c, 0x00000001, 0x00000001},
    {"FLEX_US_FESR"                         , 0x0000002d, 0x00000001, 0x00000001},
    {"FLEX_US_WPMR"                         , 0x00000039, 0x00000001, 0x00000001},
    {"FLEX_US_WPSR"                         , 0x0000003a, 0x00000001, 0x00000001},
    {"FLEX_US_VERSION"                      , 0x0000003f, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_FLEXCOM_FLEXCOM_SPI_REG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FLEX_SPI_CR"                          , 0x00000000, 0x00000001, 0x00000001},
    {"FLEX_SPI_MR"                          , 0x00000001, 0x00000001, 0x00000001},
    {"FLEX_SPI_RDR"                         , 0x00000002, 0x00000001, 0x00000001},
    {"FLEX_SPI_FMT_RDR_8"                   , 0x00000002, 0x00000001, 0x00000001},
    {"FLEX_SPI_FMT_RDR_16"                  , 0x00000002, 0x00000001, 0x00000001},
    {"FLEX_SPI_TDR"                         , 0x00000003, 0x00000001, 0x00000001},
    {"FLEX_SPI_FMT_TDR"                     , 0x00000003, 0x00000001, 0x00000001},
    {"FLEX_SPI_SR"                          , 0x00000004, 0x00000001, 0x00000001},
    {"FLEX_SPI_IER"                         , 0x00000005, 0x00000001, 0x00000001},
    {"FLEX_SPI_IDR"                         , 0x00000006, 0x00000001, 0x00000001},
    {"FLEX_SPI_IMR"                         , 0x00000007, 0x00000001, 0x00000001},
    {"FLEX_SPI_CSR0"                        , 0x0000000c, 0x00000001, 0x00000001},
    {"FLEX_SPI_CSR1"                        , 0x0000000d, 0x00000001, 0x00000001},
    {"FLEX_SPI_FMR"                         , 0x00000010, 0x00000001, 0x00000001},
    {"FLEX_SPI_FLR"                         , 0x00000011, 0x00000001, 0x00000001},
    {"FLEX_SPI_CMPR"                        , 0x00000012, 0x00000001, 0x00000001},
    {"FLEX_SPI_WPMR"                        , 0x00000039, 0x00000001, 0x00000001},
    {"FLEX_SPI_WPSR"                        , 0x0000003a, 0x00000001, 0x00000001},
    {"FLEX_SPI_VERSION"                     , 0x0000003f, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_FLEXCOM_FLEXCOM_TWI_REG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FLEX_TWI_CR"                          , 0x00000000, 0x00000001, 0x00000001},
    {"FLEX_TWI_MMR"                         , 0x00000001, 0x00000001, 0x00000001},
    {"FLEX_TWI_SMR"                         , 0x00000002, 0x00000001, 0x00000001},
    {"FLEX_TWI_IADR"                        , 0x00000003, 0x00000001, 0x00000001},
    {"FLEX_TWI_CWGR"                        , 0x00000004, 0x00000001, 0x00000001},
    {"FLEX_TWI_SR"                          , 0x00000008, 0x00000001, 0x00000001},
    {"FLEX_TWI_IER"                         , 0x00000009, 0x00000001, 0x00000001},
    {"FLEX_TWI_IDR"                         , 0x0000000a, 0x00000001, 0x00000001},
    {"FLEX_TWI_IMR"                         , 0x0000000b, 0x00000001, 0x00000001},
    {"FLEX_TWI_RHR"                         , 0x0000000c, 0x00000001, 0x00000001},
    {"FLEX_TWI_FMT_RHR"                     , 0x0000000c, 0x00000001, 0x00000001},
    {"FLEX_TWI_THR"                         , 0x0000000d, 0x00000001, 0x00000001},
    {"FLEX_TWI_FMT_THR"                     , 0x0000000d, 0x00000001, 0x00000001},
    {"FLEX_TWI_SMBTR"                       , 0x0000000e, 0x00000001, 0x00000001},
    {"FLEX_TWI_HSR"                         , 0x0000000f, 0x00000001, 0x00000001},
    {"FLEX_TWI_ACR"                         , 0x00000010, 0x00000001, 0x00000001},
    {"FLEX_TWI_FILTR"                       , 0x00000011, 0x00000001, 0x00000001},
    {"FLEX_TWI_HSCWGR"                      , 0x00000012, 0x00000001, 0x00000001},
    {"FLEX_TWI_SWMR"                        , 0x00000013, 0x00000001, 0x00000001},
    {"FLEX_TWI_FMR"                         , 0x00000014, 0x00000001, 0x00000001},
    {"FLEX_TWI_FLR"                         , 0x00000015, 0x00000001, 0x00000001},
    {"FLEX_TWI_FSR"                         , 0x00000018, 0x00000001, 0x00000001},
    {"FLEX_TWI_FIER"                        , 0x00000019, 0x00000001, 0x00000001},
    {"FLEX_TWI_FIDR"                        , 0x0000001a, 0x00000001, 0x00000001},
    {"FLEX_TWI_FIMR"                        , 0x0000001b, 0x00000001, 0x00000001},
    {"FLEX_TWI_DR"                          , 0x00000034, 0x00000001, 0x00000001},
    {"FLEX_TWI_WPMR"                        , 0x00000039, 0x00000001, 0x00000001},
    {"FLEX_TWI_WPSR"                        , 0x0000003a, 0x00000001, 0x00000001},
    {"FLEX_TWI_VER"                         , 0x0000003f, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_FLEXCOM[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"FLEXCOM_REG"                          , 0x00000000, 0x00000001, 0x00000040, regs_within_FLEXCOM_FLEXCOM_REG},
    {"FLEXCOM_USART_REG"                    , 0x00000080, 0x00000001, 0x00000042, regs_within_FLEXCOM_FLEXCOM_USART_REG},
    {"FLEXCOM_SPI_REG"                      , 0x00000100, 0x00000001, 0x00000043, regs_within_FLEXCOM_FLEXCOM_SPI_REG},
    {"FLEXCOM_TWI_REG"                      , 0x00000180, 0x00000001, 0x00000042, regs_within_FLEXCOM_FLEXCOM_TWI_REG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_CPU_SYSCNT_CXTSGEN_REGISTERS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CNTCR"                                , 0x00000000, 0x00000001, 0x00000001},
    {"CNTSR"                                , 0x00000001, 0x00000001, 0x00000001},
    {"CNTCVL"                               , 0x00000002, 0x00000001, 0x00000001},
    {"CNTCVU"                               , 0x00000003, 0x00000001, 0x00000001},
    {"CNTFID0"                              , 0x00000008, 0x00000001, 0x00000001},
    {"PIDR0"                                , 0x000003f8, 0x00000001, 0x00000001},
    {"PIDR1"                                , 0x000003f9, 0x00000001, 0x00000001},
    {"PIDR2"                                , 0x000003fa, 0x00000001, 0x00000001},
    {"PIDR3"                                , 0x000003fb, 0x00000001, 0x00000001},
    {"PIDR4"                                , 0x000003f4, 0x00000001, 0x00000001},
    {"CIDR0"                                , 0x000003fc, 0x00000001, 0x00000001},
    {"CIDR1"                                , 0x000003fd, 0x00000001, 0x00000001},
    {"CIDR2"                                , 0x000003fe, 0x00000001, 0x00000001},
    {"CIDR3"                                , 0x000003ff, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_CPU_SYSCNT[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"CXTSGEN_REGISTERS"                    , 0x00000000, 0x00000001, 0x00000400, regs_within_CPU_SYSCNT_CXTSGEN_REGISTERS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_CPU_SYSCNT_RO_CXTSGEN_READ_REGISTERS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CNTCVL"                               , 0x00000000, 0x00000001, 0x00000001},
    {"CNTCVU"                               , 0x00000001, 0x00000001, 0x00000001},
    {"PIDR0"                                , 0x000003f8, 0x00000001, 0x00000001},
    {"PIDR1"                                , 0x000003f9, 0x00000001, 0x00000001},
    {"PIDR2"                                , 0x000003fa, 0x00000001, 0x00000001},
    {"PIDR3"                                , 0x000003fb, 0x00000001, 0x00000001},
    {"PIDR4"                                , 0x000003f4, 0x00000001, 0x00000001},
    {"CIDR0"                                , 0x000003fc, 0x00000001, 0x00000001},
    {"CIDR1"                                , 0x000003fd, 0x00000001, 0x00000001},
    {"CIDR2"                                , 0x000003fe, 0x00000001, 0x00000001},
    {"CIDR3"                                , 0x000003ff, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_CPU_SYSCNT_RO[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"CXTSGEN_READ_REGISTERS"               , 0x00000400, 0x00000001, 0x00000400, regs_within_CPU_SYSCNT_RO_CXTSGEN_READ_REGISTERS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_GIC500_DISTRIBUTOR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DISTRIBUTOR__1_GICD_CTLR"             , 0x00000000, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__3_GICD_TYPER"            , 0x00000001, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__4_GICD_IIDR"             , 0x00000002, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__5_GICD_SETSPI_NSR"       , 0x00000010, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__6_GICD_CLRSPI_NSR"       , 0x00000012, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__7_GICD_SETSPI_SR"        , 0x00000014, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__8_GICD_CLRSPI_SR"        , 0x00000016, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__9_GICD_IGROUPR0"         , 0x00000020, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__10_GICD_IGROUPR1"        , 0x00000021, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__10_GICD_IGROUPR2"        , 0x00000022, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__10_GICD_IGROUPR3"        , 0x00000023, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__10_GICD_IGROUPR4"        , 0x00000024, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__10_GICD_IGROUPR5"        , 0x00000025, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__12_GICD_ISENABLER1"      , 0x00000041, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__12_GICD_ISENABLER2"      , 0x00000042, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__12_GICD_ISENABLER3"      , 0x00000043, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__12_GICD_ISENABLER4"      , 0x00000044, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__12_GICD_ISENABLER5"      , 0x00000045, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__14_GICD_ICENABLER1"      , 0x00000061, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__14_GICD_ICENABLER2"      , 0x00000062, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__14_GICD_ICENABLER3"      , 0x00000063, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__14_GICD_ICENABLER4"      , 0x00000064, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__14_GICD_ICENABLER5"      , 0x00000065, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__16_GICD_ISPENDR1"        , 0x00000081, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__16_GICD_ISPENDR2"        , 0x00000082, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__16_GICD_ISPENDR3"        , 0x00000083, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__16_GICD_ISPENDR4"        , 0x00000084, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__16_GICD_ISPENDR5"        , 0x00000085, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__18_GICD_ICPENDR1"        , 0x000000a1, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__18_GICD_ICPENDR2"        , 0x000000a2, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__18_GICD_ICPENDR3"        , 0x000000a3, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__18_GICD_ICPENDR4"        , 0x000000a4, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__18_GICD_ICPENDR5"        , 0x000000a5, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__20_GICD_ISACTIVER1"      , 0x000000c1, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__20_GICD_ISACTIVER2"      , 0x000000c2, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__20_GICD_ISACTIVER3"      , 0x000000c3, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__20_GICD_ISACTIVER4"      , 0x000000c4, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__20_GICD_ISACTIVER5"      , 0x000000c5, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__22_GICD_ICACTIVER1"      , 0x000000e1, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__22_GICD_ICACTIVER2"      , 0x000000e2, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__22_GICD_ICACTIVER3"      , 0x000000e3, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__22_GICD_ICACTIVER4"      , 0x000000e4, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__22_GICD_ICACTIVER5"      , 0x000000e5, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR8"     , 0x00000108, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR9"     , 0x00000109, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR10"    , 0x0000010a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR11"    , 0x0000010b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR12"    , 0x0000010c, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR13"    , 0x0000010d, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR14"    , 0x0000010e, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR15"    , 0x0000010f, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR16"    , 0x00000110, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR17"    , 0x00000111, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR18"    , 0x00000112, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR19"    , 0x00000113, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR20"    , 0x00000114, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR21"    , 0x00000115, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR22"    , 0x00000116, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR23"    , 0x00000117, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR24"    , 0x00000118, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR25"    , 0x00000119, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR26"    , 0x0000011a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR27"    , 0x0000011b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR28"    , 0x0000011c, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR29"    , 0x0000011d, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR30"    , 0x0000011e, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR31"    , 0x0000011f, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR32"    , 0x00000120, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR33"    , 0x00000121, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR34"    , 0x00000122, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR35"    , 0x00000123, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR36"    , 0x00000124, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR37"    , 0x00000125, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR38"    , 0x00000126, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR39"    , 0x00000127, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR40"    , 0x00000128, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR41"    , 0x00000129, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR42"    , 0x0000012a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR43"    , 0x0000012b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR44"    , 0x0000012c, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR45"    , 0x0000012d, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR46"    , 0x0000012e, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__24_GICD_IPRIORITYR47"    , 0x0000012f, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR8"      , 0x00000208, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR9"      , 0x00000209, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR10"     , 0x0000020a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR11"     , 0x0000020b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR12"     , 0x0000020c, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR13"     , 0x0000020d, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR14"     , 0x0000020e, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR15"     , 0x0000020f, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR16"     , 0x00000210, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR17"     , 0x00000211, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR18"     , 0x00000212, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR19"     , 0x00000213, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR20"     , 0x00000214, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR21"     , 0x00000215, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR22"     , 0x00000216, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR23"     , 0x00000217, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR24"     , 0x00000218, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR25"     , 0x00000219, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR26"     , 0x0000021a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR27"     , 0x0000021b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR28"     , 0x0000021c, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR29"     , 0x0000021d, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR30"     , 0x0000021e, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR31"     , 0x0000021f, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR32"     , 0x00000220, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR33"     , 0x00000221, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR34"     , 0x00000222, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR35"     , 0x00000223, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR36"     , 0x00000224, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR37"     , 0x00000225, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR38"     , 0x00000226, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR39"     , 0x00000227, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR40"     , 0x00000228, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR41"     , 0x00000229, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR42"     , 0x0000022a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR43"     , 0x0000022b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR44"     , 0x0000022c, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR45"     , 0x0000022d, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR46"     , 0x0000022e, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__26_GICD_ITARGETSR47"     , 0x0000022f, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__29_GICD_ICFGR2"          , 0x00000302, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__29_GICD_ICFGR3"          , 0x00000303, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__29_GICD_ICFGR4"          , 0x00000304, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__29_GICD_ICFGR5"          , 0x00000305, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__29_GICD_ICFGR6"          , 0x00000306, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__29_GICD_ICFGR7"          , 0x00000307, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__29_GICD_ICFGR8"          , 0x00000308, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__29_GICD_ICFGR9"          , 0x00000309, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__29_GICD_ICFGR10"         , 0x0000030a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__29_GICD_ICFGR11"         , 0x0000030b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__30_GICD_IGRPMODR0"       , 0x00000340, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__31_GICD_IGRPMODR1"       , 0x00000341, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__31_GICD_IGRPMODR2"       , 0x00000342, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__31_GICD_IGRPMODR3"       , 0x00000343, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__31_GICD_IGRPMODR4"       , 0x00000344, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__31_GICD_IGRPMODR5"       , 0x00000345, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__32_GICD_NSACR0"          , 0x00000380, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__32_GICD_NSACR1"          , 0x00000381, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__33_GICD_NSACR2"          , 0x00000382, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__33_GICD_NSACR3"          , 0x00000383, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__33_GICD_NSACR4"          , 0x00000384, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__33_GICD_NSACR5"          , 0x00000385, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__33_GICD_NSACR6"          , 0x00000386, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__33_GICD_NSACR7"          , 0x00000387, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__33_GICD_NSACR8"          , 0x00000388, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__33_GICD_NSACR9"          , 0x00000389, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__33_GICD_NSACR10"         , 0x0000038a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__33_GICD_NSACR11"         , 0x0000038b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER32_LOWER" , 0x00001840, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER32_UPPER" , 0x00001841, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER33_LOWER" , 0x00001842, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER33_UPPER" , 0x00001843, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER34_LOWER" , 0x00001844, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER34_UPPER" , 0x00001845, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER35_LOWER" , 0x00001846, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER35_UPPER" , 0x00001847, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER36_LOWER" , 0x00001848, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER36_UPPER" , 0x00001849, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER37_LOWER" , 0x0000184a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER37_UPPER" , 0x0000184b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER38_LOWER" , 0x0000184c, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER38_UPPER" , 0x0000184d, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER39_LOWER" , 0x0000184e, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER39_UPPER" , 0x0000184f, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER40_LOWER" , 0x00001850, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER40_UPPER" , 0x00001851, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER41_LOWER" , 0x00001852, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER41_UPPER" , 0x00001853, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER42_LOWER" , 0x00001854, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER42_UPPER" , 0x00001855, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER43_LOWER" , 0x00001856, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER43_UPPER" , 0x00001857, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER44_LOWER" , 0x00001858, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER44_UPPER" , 0x00001859, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER45_LOWER" , 0x0000185a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER45_UPPER" , 0x0000185b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER46_LOWER" , 0x0000185c, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER46_UPPER" , 0x0000185d, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER47_LOWER" , 0x0000185e, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER47_UPPER" , 0x0000185f, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER48_LOWER" , 0x00001860, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER48_UPPER" , 0x00001861, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER49_LOWER" , 0x00001862, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER49_UPPER" , 0x00001863, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER50_LOWER" , 0x00001864, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER50_UPPER" , 0x00001865, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER51_LOWER" , 0x00001866, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER51_UPPER" , 0x00001867, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER52_LOWER" , 0x00001868, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER52_UPPER" , 0x00001869, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER53_LOWER" , 0x0000186a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER53_UPPER" , 0x0000186b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER54_LOWER" , 0x0000186c, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER54_UPPER" , 0x0000186d, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER55_LOWER" , 0x0000186e, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER55_UPPER" , 0x0000186f, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER56_LOWER" , 0x00001870, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER56_UPPER" , 0x00001871, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER57_LOWER" , 0x00001872, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER57_UPPER" , 0x00001873, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER58_LOWER" , 0x00001874, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER58_UPPER" , 0x00001875, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER59_LOWER" , 0x00001876, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER59_UPPER" , 0x00001877, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER60_LOWER" , 0x00001878, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER60_UPPER" , 0x00001879, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER61_LOWER" , 0x0000187a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER61_UPPER" , 0x0000187b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER62_LOWER" , 0x0000187c, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER62_UPPER" , 0x0000187d, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER63_LOWER" , 0x0000187e, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER63_UPPER" , 0x0000187f, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER64_LOWER" , 0x00001880, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER64_UPPER" , 0x00001881, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER65_LOWER" , 0x00001882, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER65_UPPER" , 0x00001883, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER66_LOWER" , 0x00001884, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER66_UPPER" , 0x00001885, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER67_LOWER" , 0x00001886, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER67_UPPER" , 0x00001887, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER68_LOWER" , 0x00001888, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER68_UPPER" , 0x00001889, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER69_LOWER" , 0x0000188a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER69_UPPER" , 0x0000188b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER70_LOWER" , 0x0000188c, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER70_UPPER" , 0x0000188d, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER71_LOWER" , 0x0000188e, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER71_UPPER" , 0x0000188f, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER72_LOWER" , 0x00001890, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER72_UPPER" , 0x00001891, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER73_LOWER" , 0x00001892, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER73_UPPER" , 0x00001893, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER74_LOWER" , 0x00001894, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER74_UPPER" , 0x00001895, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER75_LOWER" , 0x00001896, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER75_UPPER" , 0x00001897, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER76_LOWER" , 0x00001898, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER76_UPPER" , 0x00001899, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER77_LOWER" , 0x0000189a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER77_UPPER" , 0x0000189b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER78_LOWER" , 0x0000189c, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER78_UPPER" , 0x0000189d, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER79_LOWER" , 0x0000189e, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER79_UPPER" , 0x0000189f, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER80_LOWER" , 0x000018a0, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER80_UPPER" , 0x000018a1, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER81_LOWER" , 0x000018a2, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER81_UPPER" , 0x000018a3, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER82_LOWER" , 0x000018a4, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER82_UPPER" , 0x000018a5, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER83_LOWER" , 0x000018a6, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER83_UPPER" , 0x000018a7, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER84_LOWER" , 0x000018a8, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER84_UPPER" , 0x000018a9, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER85_LOWER" , 0x000018aa, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER85_UPPER" , 0x000018ab, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER86_LOWER" , 0x000018ac, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER86_UPPER" , 0x000018ad, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER87_LOWER" , 0x000018ae, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER87_UPPER" , 0x000018af, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER88_LOWER" , 0x000018b0, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER88_UPPER" , 0x000018b1, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER89_LOWER" , 0x000018b2, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER89_UPPER" , 0x000018b3, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER90_LOWER" , 0x000018b4, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER90_UPPER" , 0x000018b5, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER91_LOWER" , 0x000018b6, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER91_UPPER" , 0x000018b7, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER92_LOWER" , 0x000018b8, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER92_UPPER" , 0x000018b9, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER93_LOWER" , 0x000018ba, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER93_UPPER" , 0x000018bb, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER94_LOWER" , 0x000018bc, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER94_UPPER" , 0x000018bd, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER95_LOWER" , 0x000018be, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER95_UPPER" , 0x000018bf, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER96_LOWER" , 0x000018c0, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER96_UPPER" , 0x000018c1, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER97_LOWER" , 0x000018c2, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER97_UPPER" , 0x000018c3, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER98_LOWER" , 0x000018c4, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER98_UPPER" , 0x000018c5, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER99_LOWER" , 0x000018c6, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER99_UPPER" , 0x000018c7, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER100_LOWER", 0x000018c8, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER100_UPPER", 0x000018c9, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER101_LOWER", 0x000018ca, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER101_UPPER", 0x000018cb, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER102_LOWER", 0x000018cc, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER102_UPPER", 0x000018cd, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER103_LOWER", 0x000018ce, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER103_UPPER", 0x000018cf, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER104_LOWER", 0x000018d0, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER104_UPPER", 0x000018d1, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER105_LOWER", 0x000018d2, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER105_UPPER", 0x000018d3, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER106_LOWER", 0x000018d4, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER106_UPPER", 0x000018d5, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER107_LOWER", 0x000018d6, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER107_UPPER", 0x000018d7, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER108_LOWER", 0x000018d8, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER108_UPPER", 0x000018d9, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER109_LOWER", 0x000018da, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER109_UPPER", 0x000018db, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER110_LOWER", 0x000018dc, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER110_UPPER", 0x000018dd, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER111_LOWER", 0x000018de, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER111_UPPER", 0x000018df, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER112_LOWER", 0x000018e0, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER112_UPPER", 0x000018e1, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER113_LOWER", 0x000018e2, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER113_UPPER", 0x000018e3, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER114_LOWER", 0x000018e4, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER114_UPPER", 0x000018e5, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER115_LOWER", 0x000018e6, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER115_UPPER", 0x000018e7, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER116_LOWER", 0x000018e8, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER116_UPPER", 0x000018e9, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER117_LOWER", 0x000018ea, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER117_UPPER", 0x000018eb, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER118_LOWER", 0x000018ec, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER118_UPPER", 0x000018ed, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER119_LOWER", 0x000018ee, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER119_UPPER", 0x000018ef, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER120_LOWER", 0x000018f0, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER120_UPPER", 0x000018f1, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER121_LOWER", 0x000018f2, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER121_UPPER", 0x000018f3, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER122_LOWER", 0x000018f4, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER122_UPPER", 0x000018f5, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER123_LOWER", 0x000018f6, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER123_UPPER", 0x000018f7, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER124_LOWER", 0x000018f8, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER124_UPPER", 0x000018f9, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER125_LOWER", 0x000018fa, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER125_UPPER", 0x000018fb, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER126_LOWER", 0x000018fc, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER126_UPPER", 0x000018fd, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER127_LOWER", 0x000018fe, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER127_UPPER", 0x000018ff, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER128_LOWER", 0x00001900, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER128_UPPER", 0x00001901, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER129_LOWER", 0x00001902, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER129_UPPER", 0x00001903, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER130_LOWER", 0x00001904, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER130_UPPER", 0x00001905, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER131_LOWER", 0x00001906, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER131_UPPER", 0x00001907, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER132_LOWER", 0x00001908, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER132_UPPER", 0x00001909, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER133_LOWER", 0x0000190a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER133_UPPER", 0x0000190b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER134_LOWER", 0x0000190c, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER134_UPPER", 0x0000190d, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER135_LOWER", 0x0000190e, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER135_UPPER", 0x0000190f, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER136_LOWER", 0x00001910, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER136_UPPER", 0x00001911, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER137_LOWER", 0x00001912, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER137_UPPER", 0x00001913, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER138_LOWER", 0x00001914, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER138_UPPER", 0x00001915, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER139_LOWER", 0x00001916, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER139_UPPER", 0x00001917, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER140_LOWER", 0x00001918, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER140_UPPER", 0x00001919, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER141_LOWER", 0x0000191a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER141_UPPER", 0x0000191b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER142_LOWER", 0x0000191c, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER142_UPPER", 0x0000191d, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER143_LOWER", 0x0000191e, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER143_UPPER", 0x0000191f, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER144_LOWER", 0x00001920, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER144_UPPER", 0x00001921, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER145_LOWER", 0x00001922, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER145_UPPER", 0x00001923, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER146_LOWER", 0x00001924, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER146_UPPER", 0x00001925, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER147_LOWER", 0x00001926, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER147_UPPER", 0x00001927, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER148_LOWER", 0x00001928, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER148_UPPER", 0x00001929, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER149_LOWER", 0x0000192a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER149_UPPER", 0x0000192b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER150_LOWER", 0x0000192c, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER150_UPPER", 0x0000192d, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER151_LOWER", 0x0000192e, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER151_UPPER", 0x0000192f, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER152_LOWER", 0x00001930, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER152_UPPER", 0x00001931, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER153_LOWER", 0x00001932, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER153_UPPER", 0x00001933, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER154_LOWER", 0x00001934, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER154_UPPER", 0x00001935, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER155_LOWER", 0x00001936, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER155_UPPER", 0x00001937, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER156_LOWER", 0x00001938, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER156_UPPER", 0x00001939, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER157_LOWER", 0x0000193a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER157_UPPER", 0x0000193b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER158_LOWER", 0x0000193c, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER158_UPPER", 0x0000193d, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER159_LOWER", 0x0000193e, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER159_UPPER", 0x0000193f, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER160_LOWER", 0x00001940, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER160_UPPER", 0x00001941, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER161_LOWER", 0x00001942, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER161_UPPER", 0x00001943, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER162_LOWER", 0x00001944, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER162_UPPER", 0x00001945, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER163_LOWER", 0x00001946, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER163_UPPER", 0x00001947, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER164_LOWER", 0x00001948, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER164_UPPER", 0x00001949, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER165_LOWER", 0x0000194a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER165_UPPER", 0x0000194b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER166_LOWER", 0x0000194c, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER166_UPPER", 0x0000194d, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER167_LOWER", 0x0000194e, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER167_UPPER", 0x0000194f, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER168_LOWER", 0x00001950, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER168_UPPER", 0x00001951, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER169_LOWER", 0x00001952, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER169_UPPER", 0x00001953, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER170_LOWER", 0x00001954, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER170_UPPER", 0x00001955, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER171_LOWER", 0x00001956, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER171_UPPER", 0x00001957, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER172_LOWER", 0x00001958, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER172_UPPER", 0x00001959, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER173_LOWER", 0x0000195a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER173_UPPER", 0x0000195b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER174_LOWER", 0x0000195c, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER174_UPPER", 0x0000195d, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER175_LOWER", 0x0000195e, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER175_UPPER", 0x0000195f, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER176_LOWER", 0x00001960, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER176_UPPER", 0x00001961, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER177_LOWER", 0x00001962, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER177_UPPER", 0x00001963, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER178_LOWER", 0x00001964, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER178_UPPER", 0x00001965, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER179_LOWER", 0x00001966, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER179_UPPER", 0x00001967, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER180_LOWER", 0x00001968, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER180_UPPER", 0x00001969, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER181_LOWER", 0x0000196a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER181_UPPER", 0x0000196b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER182_LOWER", 0x0000196c, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER182_UPPER", 0x0000196d, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER183_LOWER", 0x0000196e, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER183_UPPER", 0x0000196f, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER184_LOWER", 0x00001970, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER184_UPPER", 0x00001971, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER185_LOWER", 0x00001972, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER185_UPPER", 0x00001973, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER186_LOWER", 0x00001974, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER186_UPPER", 0x00001975, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER187_LOWER", 0x00001976, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER187_UPPER", 0x00001977, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER188_LOWER", 0x00001978, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER188_UPPER", 0x00001979, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER189_LOWER", 0x0000197a, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER189_UPPER", 0x0000197b, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER190_LOWER", 0x0000197c, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER190_UPPER", 0x0000197d, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER191_LOWER", 0x0000197e, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__37_GICD_IROUTER191_UPPER", 0x0000197f, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__38_GICD_ESTATUSR"        , 0x00003000, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__39_GICD_ERRTESTR"        , 0x00003001, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__40_GICD_SPISR0"          , 0x00003021, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__40_GICD_SPISR1"          , 0x00003022, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__40_GICD_SPISR2"          , 0x00003023, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__40_GICD_SPISR3"          , 0x00003024, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__40_GICD_SPISR4"          , 0x00003025, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__41_GICD_PIDR4"           , 0x00003ff4, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__42_GICD_PIDR5"           , 0x00003ff5, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__43_GICD_PIDR6"           , 0x00003ff6, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__44_GICD_PIDR7"           , 0x00003ff7, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__45_GICD_PIDR0"           , 0x00003ff8, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__46_GICD_PIDR1"           , 0x00003ff9, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__47_GICD_PIDR2"           , 0x00003ffa, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__48_GICD_PIDR3"           , 0x00003ffb, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__49_GICD_CIDR0"           , 0x00003ffc, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__50_GICD_CIDR1"           , 0x00003ffd, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__51_GICD_CIDR2"           , 0x00003ffe, 0x00000001, 0x00000001},
    {"DISTRIBUTOR__52_GICD_CIDR3"           , 0x00003fff, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_GIC500_MESSAGE_BASED_SPIS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MESSAGE_BASED_SPIS__1_GICD_SETSPI_NSR", 0x00000010, 0x00000001, 0x00000001},
    {"MESSAGE_BASED_SPIS__2_GICD_CLRSPI_NSR", 0x00000012, 0x00000001, 0x00000001},
    {"MESSAGE_BASED_SPIS__3_GICD_SETSPI_SR" , 0x00000014, 0x00000001, 0x00000001},
    {"MESSAGE_BASED_SPIS__4_GICD_CLRSPI_SR" , 0x00000016, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_GIC500_REDISTRIBUTOR_CONTROL_LPI_0[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"REDISTRIBUTOR_CONTROL_LPI_0__1_GICR_CTLR", 0x00000000, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_CONTROL_LPI_0__3_GICR_IIDR", 0x00000001, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_CONTROL_LPI_0__4_GICR_TYPER_LOWER", 0x00000002, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_CONTROL_LPI_0__5_GICR_TYPER_UPPER", 0x00000003, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_CONTROL_LPI_0__6_GICR_WAKER", 0x00000005, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_CONTROL_LPI_0__11_GICR_PIDR4", 0x00003ff4, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_CONTROL_LPI_0__12_GICR_PIDR5", 0x00003ff5, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_CONTROL_LPI_0__13_GICR_PIDR6", 0x00003ff6, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_CONTROL_LPI_0__14_GICR_PIDR7", 0x00003ff7, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_CONTROL_LPI_0__15_GICR_PIDR0", 0x00003ff8, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_CONTROL_LPI_0__16_GICR_PIDR1", 0x00003ff9, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_CONTROL_LPI_0__17_GICR_PIDR2", 0x00003ffa, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_CONTROL_LPI_0__18_GICR_PIDR3", 0x00003ffb, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_CONTROL_LPI_0__19_GICR_CIDR0", 0x00003ffc, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_CONTROL_LPI_0__20_GICR_CIDR1", 0x00003ffd, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_CONTROL_LPI_0__21_GICR_CIDR2", 0x00003ffe, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_CONTROL_LPI_0__22_GICR_CIDR3", 0x00003fff, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_GIC500_REDISTRIBUTOR_SGI_PPI_0[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"REDISTRIBUTOR_SGI_PPI_0__1_GICR_IGROUPR0", 0x00000020, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_SGI_PPI_0__2_GICR_ISENABLER0", 0x00000040, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_SGI_PPI_0__3_GICR_ICENABLER0", 0x00000060, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_SGI_PPI_0__4_GICR_ISPENDR0", 0x00000080, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_SGI_PPI_0__5_GICR_ICPENDR0", 0x000000a0, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_SGI_PPI_0__6_GICR_ISACTIVER0", 0x000000c0, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_SGI_PPI_0__7_GICR_ICACTIVER0", 0x000000e0, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_SGI_PPI_0__8_GICR_IPRIORITYR0", 0x00000100, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_SGI_PPI_0__8_GICR_IPRIORITYR1", 0x00000101, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_SGI_PPI_0__8_GICR_IPRIORITYR2", 0x00000102, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_SGI_PPI_0__8_GICR_IPRIORITYR3", 0x00000103, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_SGI_PPI_0__8_GICR_IPRIORITYR4", 0x00000104, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_SGI_PPI_0__8_GICR_IPRIORITYR5", 0x00000105, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_SGI_PPI_0__8_GICR_IPRIORITYR6", 0x00000106, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_SGI_PPI_0__8_GICR_IPRIORITYR7", 0x00000107, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_SGI_PPI_0__9_GICR_ICFGR0", 0x00000300, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_SGI_PPI_0__10_GICR_ICFGR1", 0x00000301, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_SGI_PPI_0__11_GICR_IGRPMODR0", 0x00000340, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_SGI_PPI_0__12_GICR_NSACR", 0x00000380, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_SGI_PPI_0__13_GICR_MISCSTATUSR", 0x00003000, 0x00000001, 0x00000001},
    {"REDISTRIBUTOR_SGI_PPI_0__14_GICR_PPISR", 0x00003020, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_GIC500[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DISTRIBUTOR"                          , 0x00000000, 0x00000001, 0x00000010, regs_within_GIC500_DISTRIBUTOR},
    {"MESSAGE_BASED_SPIS"                   , 0x00004000, 0x00000001, 0x00000010, regs_within_GIC500_MESSAGE_BASED_SPIS},
    {"REDISTRIBUTOR_CONTROL_LPI_0"          , 0x00010000, 0x00000001, 0x00000010, regs_within_GIC500_REDISTRIBUTOR_CONTROL_LPI_0},
    {"REDISTRIBUTOR_SGI_PPI_0"              , 0x00014000, 0x00000001, 0x00000010, regs_within_GIC500_REDISTRIBUTOR_SGI_PPI_0},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_GPV_ADDRESSBLOCK_DEFAULT_0XE8B00000_CA7[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PERIPH_ID_4"                          , 0x000007f4, 0x00000001, 0x00000001},
    {"PERIPH_ID_5"                          , 0x000007f5, 0x00000001, 0x00000001},
    {"PERIPH_ID_6"                          , 0x000007f6, 0x00000001, 0x00000001},
    {"PERIPH_ID_7"                          , 0x000007f7, 0x00000001, 0x00000001},
    {"PERIPH_ID_0"                          , 0x000007f8, 0x00000001, 0x00000001},
    {"PERIPH_ID_1"                          , 0x000007f9, 0x00000001, 0x00000001},
    {"PERIPH_ID_2"                          , 0x000007fa, 0x00000001, 0x00000001},
    {"PERIPH_ID_3"                          , 0x000007fb, 0x00000001, 0x00000001},
    {"COMP_ID_0"                            , 0x000007fc, 0x00000001, 0x00000001},
    {"COMP_ID_1"                            , 0x000007fd, 0x00000001, 0x00000001},
    {"COMP_ID_2"                            , 0x000007fe, 0x00000001, 0x00000001},
    {"COMP_ID_3"                            , 0x000007ff, 0x00000001, 0x00000001},
    {"SECURITY_BOOT_RAM"                    , 0x00000003, 0x00000001, 0x00000001},
    {"SECURITY_DDR_CSS"                     , 0x00000005, 0x00000001, 0x00000001},
    {"SECURITY_CSR_REGS"                    , 0x00000007, 0x00000001, 0x00000001},
    {"SECURITY_CPU_REGS"                    , 0x00000008, 0x00000001, 0x00000001},
    {"SECURITY_PI"                          , 0x0000000c, 0x00000001, 0x00000001},
    {"SECURITY_PCIE_DBI"                    , 0x0000000e, 0x00000001, 0x00000001},
    {"SECURITY_PCIE_OB"                     , 0x0000000f, 0x00000001, 0x00000001},
    {"SECURITY_QSPI1"                       , 0x00000010, 0x00000001, 0x00000001},
    {"SECURITY_PCIE_CFG"                    , 0x00000011, 0x00000001, 0x00000001},
    {"SECURITY_CUPHY"                       , 0x00000012, 0x00000001, 0x00000001},
    {"SECURITY_APB_MAIN3"                   , 0x00000014, 0x00000001, 0x00000001},
    {"SECURITY_APB_CSS2"                    , 0x00000015, 0x00000001, 0x00000001},
    {"CA7_FN_MOD"                           , 0x00010842, 0x00000001, 0x00000001},
    {"SECURITY_DDR_MAIN"                    , 0x0000000b, 0x00000001, 0x00000001},
    {"CA7_DAP_IB_FN_MOD2"                   , 0x00010c09, 0x00000001, 0x00000001},
    {"CA7_DAP_IB_FN_MOD"                    , 0x00010c42, 0x00000001, 0x00000001},
    {"EXT_INITIATOR_IB_FN_MOD2"             , 0x00011009, 0x00000001, 0x00000001},
    {"EXT_INITIATOR_IB_FN_MOD"              , 0x00011042, 0x00000001, 0x00000001},
    {"FDMA_FN_MOD"                          , 0x00011442, 0x00000001, 0x00000001},
    {"PCIE_IB_FN_MOD"                       , 0x00011842, 0x00000001, 0x00000001},
    {"XDMAC_FN_MOD"                         , 0x00011c42, 0x00000001, 0x00000001},
    {"RTE_IB_FN_MOD2"                       , 0x00012009, 0x00000001, 0x00000001},
    {"RTE_IB_FN_MOD"                        , 0x00012042, 0x00000001, 0x00000001},
    {"APB_CSS_AHB_CNTL"                     , 0x00000811, 0x00000001, 0x00000001},
    {"APB_CSS_IB_FN_MOD2"                   , 0x00000809, 0x00000001, 0x00000001},
    {"APB_CSS_IB_FN_MOD_ISS_BM"             , 0x00000802, 0x00000001, 0x00000001},
    {"BOOT_RAM_FN_MOD_ISS_BM"               , 0x00000c02, 0x00000001, 0x00000001},
    {"BOOT_RAM_AHB_CNTL"                    , 0x00000c11, 0x00000001, 0x00000001},
    {"CPKCC_AHB_CNTL"                       , 0x00001011, 0x00000001, 0x00000001},
    {"CPKCC_IB_FN_MOD2"                     , 0x00001009, 0x00000001, 0x00000001},
    {"CPKCC_IB_FN_MOD_ISS_BM"               , 0x00001002, 0x00000001, 0x00000001},
    {"DDR_CSS_FN_MOD_ISS_BM"                , 0x00001402, 0x00000001, 0x00000001},
    {"CSS2HSS_IB_FN_MOD2"                   , 0x00001809, 0x00000001, 0x00000001},
    {"CSS2HSS_IB_FN_MOD_LB"                 , 0x0000180b, 0x00000001, 0x00000001},
    {"CSS2HSS_IB_FN_MOD_ISS_BM"             , 0x00001802, 0x00000001, 0x00000001},
    {"CSR_REGS_AHB_CNTL"                    , 0x00001c11, 0x00000001, 0x00000001},
    {"CSR_REGS_IB_FN_MOD2"                  , 0x00001c09, 0x00000001, 0x00000001},
    {"CSR_REGS_IB_FN_MOD_ISS_BM"            , 0x00001c02, 0x00000001, 0x00000001},
    {"CPU_REGS_AHB_CNTL"                    , 0x00002011, 0x00000001, 0x00000001},
    {"CPU_REGS_IB_FN_MOD2"                  , 0x00002009, 0x00000001, 0x00000001},
    {"CPU_REGS_IB_FN_MOD_ISS_BM"            , 0x00002002, 0x00000001, 0x00000001},
    {"APB_MAIN1_FN_MOD_ISS_BM"              , 0x00002402, 0x00000001, 0x00000001},
    {"APB_MAIN1_AHB_CNTL"                   , 0x00002411, 0x00000001, 0x00000001},
    {"APB_MAIN2_FN_MOD_ISS_BM"              , 0x00002802, 0x00000001, 0x00000001},
    {"APB_MAIN2_AHB_CNTL"                   , 0x00002811, 0x00000001, 0x00000001},
    {"DDR_MAIN_FN_MOD_ISS_BM"               , 0x00002c02, 0x00000001, 0x00000001},
    {"PI_AHB_CNTL"                          , 0x00003011, 0x00000001, 0x00000001},
    {"PI_IB_FN_MOD2"                        , 0x00003009, 0x00000001, 0x00000001},
    {"PI_IB_FN_MOD_ISS_BM"                  , 0x00003002, 0x00000001, 0x00000001},
    {"MAIN2HSS_FN_MOD_ISS_BM"               , 0x00003402, 0x00000001, 0x00000001},
    {"PCIE_DBI_IB_FN_MOD2"                  , 0x00003809, 0x00000001, 0x00000001},
    {"PCIE_DBI_IB_FN_MOD_ISS_BM"            , 0x00003802, 0x00000001, 0x00000001},
    {"PCIE_OB_FN_MOD_ISS_BM"                , 0x00003c02, 0x00000001, 0x00000001},
    {"QSPI1_FN_MOD_ISS_BM"                  , 0x00004002, 0x00000001, 0x00000001},
    {"QSPI1_AHB_CNTL"                       , 0x00004011, 0x00000001, 0x00000001},
    {"PCIE_CFG_AHB_CNTL"                    , 0x00004411, 0x00000001, 0x00000001},
    {"PCIE_CFG_IB_FN_MOD2"                  , 0x00004409, 0x00000001, 0x00000001},
    {"PCIE_CFG_IB_FN_MOD_ISS_BM"            , 0x00004402, 0x00000001, 0x00000001},
    {"CUPHY_AHB_CNTL"                       , 0x00004811, 0x00000001, 0x00000001},
    {"CUPHY_IB_FN_MOD2"                     , 0x00004809, 0x00000001, 0x00000001},
    {"CUPHY_IB_FN_MOD_ISS_BM"               , 0x00004802, 0x00000001, 0x00000001},
    {"FDMA_SLV_M_IB_FN_MOD2"                , 0x00004c09, 0x00000001, 0x00000001},
    {"APB_MAIN3_IB_FN_MOD2"                 , 0x00005009, 0x00000001, 0x00000001},
    {"APB_MAIN3_IB_FN_MOD_ISS_BM"           , 0x00005002, 0x00000001, 0x00000001},
    {"APB_CSS2_IB_FN_MOD2"                  , 0x00005409, 0x00000001, 0x00000001},
    {"APB_CSS2_IB_FN_MOD_ISS_BM"            , 0x00005402, 0x00000001, 0x00000001},
    {"CSS2HSS_IB_FN_MOD"                    , 0x00001842, 0x00000001, 0x00000001},
    {"PCIE_DBI_IB_FN_MOD"                   , 0x00003842, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_GPV[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"ADDRESSBLOCK_DEFAULT_0XE8B00000_CA7"  , 0x00000000, 0x00000001, 0x00009c40, regs_within_GPV_ADDRESSBLOCK_DEFAULT_0XE8B00000_CA7},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_HICM_HICM_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"ICM_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
    {"ICM_CTRL"                             , 0x00000001, 0x00000001, 0x00000001},
    {"ICM_SR"                               , 0x00000002, 0x00000001, 0x00000001},
    {"ICM_IER"                              , 0x00000004, 0x00000001, 0x00000001},
    {"ICM_IDR"                              , 0x00000005, 0x00000001, 0x00000001},
    {"ICM_IMR"                              , 0x00000006, 0x00000001, 0x00000001},
    {"ICM_ISR"                              , 0x00000007, 0x00000001, 0x00000001},
    {"ICM_UASR"                             , 0x00000008, 0x00000001, 0x00000001},
    {"ICM_DSCR"                             , 0x0000000c, 0x00000001, 0x00000001},
    {"ICM_HASH"                             , 0x0000000d, 0x00000001, 0x00000001},
    {"ICM_UIHVAL0"                          , 0x0000000e, 0x00000001, 0x00000001},
    {"ICM_UIHVAL1"                          , 0x0000000f, 0x00000001, 0x00000001},
    {"ICM_UIHVAL2"                          , 0x00000010, 0x00000001, 0x00000001},
    {"ICM_UIHVAL3"                          , 0x00000011, 0x00000001, 0x00000001},
    {"ICM_UIHVAL4"                          , 0x00000012, 0x00000001, 0x00000001},
    {"ICM_UIHVAL5"                          , 0x00000013, 0x00000001, 0x00000001},
    {"ICM_UIHVAL6"                          , 0x00000014, 0x00000001, 0x00000001},
    {"ICM_UIHVAL7"                          , 0x00000015, 0x00000001, 0x00000001},
    {"ICM_ADDRSIZE"                         , 0x0000003b, 0x00000001, 0x00000001},
    {"ICM_IPNAME1"                          , 0x0000003c, 0x00000001, 0x00000001},
    {"ICM_IPNAME2"                          , 0x0000003d, 0x00000001, 0x00000001},
    {"ICM_FEATURES"                         , 0x0000003e, 0x00000001, 0x00000001},
    {"ICM_VERSION"                          , 0x0000003f, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_HICM[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"HICM_REGS"                            , 0x00000000, 0x00000001, 0x00000040, regs_within_HICM_HICM_REGS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_HMATRIX2_HMATRIX2_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MATRIX_MCFG0"                         , 0x00000000, 0x00000001, 0x00000001},
    {"MATRIX_MCFG1"                         , 0x00000001, 0x00000001, 0x00000001},
    {"MATRIX_MCFG2"                         , 0x00000002, 0x00000001, 0x00000001},
    {"MATRIX_MCFG3"                         , 0x00000003, 0x00000001, 0x00000001},
    {"MATRIX_MCFG4"                         , 0x00000004, 0x00000001, 0x00000001},
    {"MATRIX_MCFG5"                         , 0x00000005, 0x00000001, 0x00000001},
    {"MATRIX_MCFG6"                         , 0x00000006, 0x00000001, 0x00000001},
    {"MATRIX_MCFG7"                         , 0x00000007, 0x00000001, 0x00000001},
    {"MATRIX_MCFG8"                         , 0x00000008, 0x00000001, 0x00000001},
    {"MATRIX_SCFG0"                         , 0x00000010, 0x00000001, 0x00000001},
    {"MATRIX_SCFG1"                         , 0x00000011, 0x00000001, 0x00000001},
    {"MATRIX_SCFG2"                         , 0x00000012, 0x00000001, 0x00000001},
    {"MATRIX_SCFG3"                         , 0x00000013, 0x00000001, 0x00000001},
    {"MATRIX_SCFG4"                         , 0x00000014, 0x00000001, 0x00000001},
    {"MATRIX_SCFG5"                         , 0x00000015, 0x00000001, 0x00000001},
    {"MATRIX_SCFG6"                         , 0x00000016, 0x00000001, 0x00000001},
    {"MATRIX_SCFG7"                         , 0x00000009, 0x00000001, 0x00000001},
    {"MATRIX_PRAS0"                         , 0x00000020, 0x00000001, 0x00000001},
    {"MATRIX_PRBS0"                         , 0x00000021, 0x00000001, 0x00000001},
    {"MATRIX_PRAS1"                         , 0x00000022, 0x00000001, 0x00000001},
    {"MATRIX_PRBS1"                         , 0x00000023, 0x00000001, 0x00000001},
    {"MATRIX_PRAS2"                         , 0x00000024, 0x00000001, 0x00000001},
    {"MATRIX_PRBS2"                         , 0x00000025, 0x00000001, 0x00000001},
    {"MATRIX_PRAS3"                         , 0x00000026, 0x00000001, 0x00000001},
    {"MATRIX_PRBS3"                         , 0x00000027, 0x00000001, 0x00000001},
    {"MATRIX_PRAS4"                         , 0x00000028, 0x00000001, 0x00000001},
    {"MATRIX_PRBS4"                         , 0x00000029, 0x00000001, 0x00000001},
    {"MATRIX_PRAS5"                         , 0x0000002a, 0x00000001, 0x00000001},
    {"MATRIX_PRBS5"                         , 0x0000002b, 0x00000001, 0x00000001},
    {"MATRIX_PRAS6"                         , 0x0000000a, 0x00000001, 0x00000001},
    {"MATRIX_PRBS6"                         , 0x0000000b, 0x00000001, 0x00000001},
    {"MATRIX_PRAS7"                         , 0x0000000c, 0x00000001, 0x00000001},
    {"MATRIX_PRBS7"                         , 0x0000000d, 0x00000001, 0x00000001},
    {"MATRIX_MRCR"                          , 0x00000040, 0x00000001, 0x00000001},
    {"MATRIX_SFR0"                          , 0x00000044, 0x00000001, 0x00000001},
    {"MATRIX_SFR1"                          , 0x00000045, 0x00000001, 0x00000001},
    {"MATRIX_SFR2"                          , 0x00000046, 0x00000001, 0x00000001},
    {"MATRIX_SFR3"                          , 0x00000047, 0x00000001, 0x00000001},
    {"MATRIX_SFR4"                          , 0x00000048, 0x00000001, 0x00000001},
    {"MATRIX_SFR5"                          , 0x00000049, 0x00000001, 0x00000001},
    {"MATRIX_SFR6"                          , 0x0000004a, 0x00000001, 0x00000001},
    {"MATRIX_SFR7"                          , 0x0000000e, 0x00000001, 0x00000001},
    {"MATRIX_MEIER"                         , 0x00000054, 0x00000001, 0x00000001},
    {"MATRIX_MEIDR"                         , 0x00000055, 0x00000001, 0x00000001},
    {"MATRIX_MEIMR"                         , 0x00000056, 0x00000001, 0x00000001},
    {"MATRIX_MESR"                          , 0x00000057, 0x00000001, 0x00000001},
    {"MATRIX_MEAR0"                         , 0x00000058, 0x00000001, 0x00000001},
    {"MATRIX_MEAR1"                         , 0x00000059, 0x00000001, 0x00000001},
    {"MATRIX_MEAR2"                         , 0x0000005a, 0x00000001, 0x00000001},
    {"MATRIX_MEAR3"                         , 0x0000005b, 0x00000001, 0x00000001},
    {"MATRIX_MEAR4"                         , 0x0000005c, 0x00000001, 0x00000001},
    {"MATRIX_MEAR5"                         , 0x0000005d, 0x00000001, 0x00000001},
    {"MATRIX_MEAR6"                         , 0x0000000f, 0x00000001, 0x00000001},
    {"MATRIX_MEAR7"                         , 0x00000017, 0x00000001, 0x00000001},
    {"MATRIX_MEAR8"                         , 0x00000018, 0x00000001, 0x00000001},
    {"MATRIX_WPMR"                          , 0x00000079, 0x00000001, 0x00000001},
    {"MATRIX_WPSR"                          , 0x0000007a, 0x00000001, 0x00000001},
    {"MATRIX_VERSION"                       , 0x0000007f, 0x00000001, 0x00000001},
    {"MATRIX_SSR0"                          , 0x00000080, 0x00000001, 0x00000001},
    {"MATRIX_SSR1"                          , 0x00000081, 0x00000001, 0x00000001},
    {"MATRIX_SSR2"                          , 0x00000082, 0x00000001, 0x00000001},
    {"MATRIX_SSR3"                          , 0x00000083, 0x00000001, 0x00000001},
    {"MATRIX_SSR4"                          , 0x00000084, 0x00000001, 0x00000001},
    {"MATRIX_SSR5"                          , 0x00000085, 0x00000001, 0x00000001},
    {"MATRIX_SSR6"                          , 0x00000019, 0x00000001, 0x00000001},
    {"MATRIX_SSR7"                          , 0x0000001a, 0x00000001, 0x00000001},
    {"MATRIX_SASSR0"                        , 0x00000090, 0x00000001, 0x00000001},
    {"MATRIX_SASSR1"                        , 0x00000091, 0x00000001, 0x00000001},
    {"MATRIX_SASSR2"                        , 0x00000092, 0x00000001, 0x00000001},
    {"MATRIX_SASSR3"                        , 0x00000093, 0x00000001, 0x00000001},
    {"MATRIX_SASSR4"                        , 0x00000094, 0x00000001, 0x00000001},
    {"MATRIX_SASSR5"                        , 0x00000095, 0x00000001, 0x00000001},
    {"MATRIX_SASSR6"                        , 0x0000001b, 0x00000001, 0x00000001},
    {"MATRIX_SASSR7"                        , 0x0000001c, 0x00000001, 0x00000001},
    {"MATRIX_SRTSR0"                        , 0x000000a0, 0x00000001, 0x00000001},
    {"MATRIX_SRTSR1"                        , 0x000000a1, 0x00000001, 0x00000001},
    {"MATRIX_SRTSR2"                        , 0x000000a2, 0x00000001, 0x00000001},
    {"MATRIX_SRTSR3"                        , 0x000000a3, 0x00000001, 0x00000001},
    {"MATRIX_SRTSR4"                        , 0x000000a4, 0x00000001, 0x00000001},
    {"MATRIX_SRTSR5"                        , 0x000000a5, 0x00000001, 0x00000001},
    {"MATRIX_SRTSR6"                        , 0x0000001d, 0x00000001, 0x00000001},
    {"MATRIX_SRTSR7"                        , 0x0000001e, 0x00000001, 0x00000001},
    {"MATRIX_SPSELR1"                       , 0x000000b0, 0x00000001, 0x00000001},
    {"MATRIX_SPSELR2"                       , 0x000000b1, 0x00000001, 0x00000001},
    {"MATRIX_SPSELR3"                       , 0x000000b2, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_HMATRIX2[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"HMATRIX2_REGS"                        , 0x00000000, 0x00000001, 0x000000b3, regs_within_HMATRIX2_HMATRIX2_REGS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_MCAN_MCAN_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CREL"                                 , 0x00000000, 0x00000001, 0x00000001},
    {"ENDN"                                 , 0x00000001, 0x00000001, 0x00000001},
    {"CUST"                                 , 0x00000002, 0x00000001, 0x00000001},
    {"DBTP"                                 , 0x00000003, 0x00000001, 0x00000001},
    {"TEST"                                 , 0x00000004, 0x00000001, 0x00000001},
    {"RWD"                                  , 0x00000005, 0x00000001, 0x00000001},
    {"CCCR"                                 , 0x00000006, 0x00000001, 0x00000001},
    {"NBTP"                                 , 0x00000007, 0x00000001, 0x00000001},
    {"TSCC"                                 , 0x00000008, 0x00000001, 0x00000001},
    {"TSCV"                                 , 0x00000009, 0x00000001, 0x00000001},
    {"TOCC"                                 , 0x0000000a, 0x00000001, 0x00000001},
    {"TOCV"                                 , 0x0000000b, 0x00000001, 0x00000001},
    {"ECR"                                  , 0x00000010, 0x00000001, 0x00000001},
    {"PSR"                                  , 0x00000011, 0x00000001, 0x00000001},
    {"TDCR"                                 , 0x00000012, 0x00000001, 0x00000001},
    {"IR"                                   , 0x00000014, 0x00000001, 0x00000001},
    {"IE"                                   , 0x00000015, 0x00000001, 0x00000001},
    {"ILS"                                  , 0x00000016, 0x00000001, 0x00000001},
    {"ILE"                                  , 0x00000017, 0x00000001, 0x00000001},
    {"GFC"                                  , 0x00000020, 0x00000001, 0x00000001},
    {"SIDFC"                                , 0x00000021, 0x00000001, 0x00000001},
    {"XIDFC"                                , 0x00000022, 0x00000001, 0x00000001},
    {"XIDAM"                                , 0x00000024, 0x00000001, 0x00000001},
    {"HPMS"                                 , 0x00000025, 0x00000001, 0x00000001},
    {"NDAT1"                                , 0x00000026, 0x00000001, 0x00000001},
    {"NDAT2"                                , 0x00000027, 0x00000001, 0x00000001},
    {"RXF0C"                                , 0x00000028, 0x00000001, 0x00000001},
    {"RXF0S"                                , 0x00000029, 0x00000001, 0x00000001},
    {"RXF0A"                                , 0x0000002a, 0x00000001, 0x00000001},
    {"RXBC"                                 , 0x0000002b, 0x00000001, 0x00000001},
    {"RXF1C"                                , 0x0000002c, 0x00000001, 0x00000001},
    {"RXF1S"                                , 0x0000002d, 0x00000001, 0x00000001},
    {"RXF1A"                                , 0x0000002e, 0x00000001, 0x00000001},
    {"RXESC"                                , 0x0000002f, 0x00000001, 0x00000001},
    {"TXBC"                                 , 0x00000030, 0x00000001, 0x00000001},
    {"TXFQS"                                , 0x00000031, 0x00000001, 0x00000001},
    {"TXESC"                                , 0x00000032, 0x00000001, 0x00000001},
    {"TXBRP"                                , 0x00000033, 0x00000001, 0x00000001},
    {"TXBAR"                                , 0x00000034, 0x00000001, 0x00000001},
    {"TXBCR"                                , 0x00000035, 0x00000001, 0x00000001},
    {"TXBTO"                                , 0x00000036, 0x00000001, 0x00000001},
    {"TXBCF"                                , 0x00000037, 0x00000001, 0x00000001},
    {"TXBTIE"                               , 0x00000038, 0x00000001, 0x00000001},
    {"TXBCIE"                               , 0x00000039, 0x00000001, 0x00000001},
    {"TXEFC"                                , 0x0000003c, 0x00000001, 0x00000001},
    {"TXEFS"                                , 0x0000003d, 0x00000001, 0x00000001},
    {"TXEFA"                                , 0x0000003e, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_MCAN[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"MCAN_REGS"                            , 0x00000000, 0x00000001, 0x0000003f, regs_within_MCAN_MCAN_REGS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_MCAN_TIMER_TIMER_REG_CHANNEL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TC_CCR"                               , 0x00000000, 0x00000001, 0x00000001},
    {"TC_CMR_CAPTURE"                       , 0x00000001, 0x00000001, 0x00000001},
    {"TC_CMR_WAVE"                          , 0x00000001, 0x00000001, 0x00000001},
    {"TC_SMMR"                              , 0x00000002, 0x00000001, 0x00000001},
    {"TC_RAB"                               , 0x00000003, 0x00000001, 0x00000001},
    {"TC_CV"                                , 0x00000004, 0x00000001, 0x00000001},
    {"TC_RA"                                , 0x00000005, 0x00000001, 0x00000001},
    {"TC_RB"                                , 0x00000006, 0x00000001, 0x00000001},
    {"TC_RC"                                , 0x00000007, 0x00000001, 0x00000001},
    {"TC_SR"                                , 0x00000008, 0x00000001, 0x00000001},
    {"TC_IER"                               , 0x00000009, 0x00000001, 0x00000001},
    {"TC_IDR"                               , 0x0000000a, 0x00000001, 0x00000001},
    {"TC_IMR"                               , 0x0000000b, 0x00000001, 0x00000001},
    {"TC_EMR"                               , 0x0000000c, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_MCAN_TIMER_TIMER_REG_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TC_BCR"                               , 0x00000000, 0x00000001, 0x00000001},
    {"TC_BMR"                               , 0x00000001, 0x00000001, 0x00000001},
    {"TC_QIER"                              , 0x00000002, 0x00000001, 0x00000001},
    {"TC_QIDR"                              , 0x00000003, 0x00000001, 0x00000001},
    {"TC_QIMR"                              , 0x00000004, 0x00000001, 0x00000001},
    {"TC_QISR"                              , 0x00000005, 0x00000001, 0x00000001},
    {"TC_FMR"                               , 0x00000006, 0x00000001, 0x00000001},
    {"TC_WPMR"                              , 0x00000007, 0x00000001, 0x00000001},
    {"TC_VER"                               , 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_MCAN_TIMER[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"TIMER_REG_CHANNEL"                    , 0x00000000, 0x00000003, 0x00000010, regs_within_MCAN_TIMER_TIMER_REG_CHANNEL},
    {"TIMER_REG_CFG"                        , 0x00000030, 0x00000001, 0x00000009, regs_within_MCAN_TIMER_TIMER_REG_CFG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_OTP_OTP_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"OTP_PWR_DN"                           , 0x00000000, 0x00000001, 0x00000001},
    {"OTP_ADDR_HI"                          , 0x00000001, 0x00000001, 0x00000001},
    {"OTP_ADDR_LO"                          , 0x00000002, 0x00000001, 0x00000001},
    {"OTP_ADDR_BITS"                        , 0x00000003, 0x00000001, 0x00000001},
    {"OTP_PRGM_DATA"                        , 0x00000004, 0x00000001, 0x00000001},
    {"OTP_PRGM_MODE"                        , 0x00000005, 0x00000001, 0x00000001},
    {"OTP_RD_DATA"                          , 0x00000006, 0x00000001, 0x00000001},
    {"OTP_FUNC_CMD"                         , 0x00000008, 0x00000001, 0x00000001},
    {"OTP_TEST_CMD"                         , 0x00000009, 0x00000001, 0x00000001},
    {"OTP_CMD_GO"                           , 0x0000000a, 0x00000001, 0x00000001},
    {"OTP_PASS_FAIL"                        , 0x0000000b, 0x00000001, 0x00000001},
    {"OTP_STATUS"                           , 0x0000000c, 0x00000001, 0x00000001},
    {"OTP_MAX_PRG"                          , 0x0000000d, 0x00000001, 0x00000001},
    {"OTP_INTR_STATUS"                      , 0x00000010, 0x00000001, 0x00000001},
    {"OTP_INTR_MASK"                        , 0x00000011, 0x00000001, 0x00000001},
    {"OTP_RSTB_PW_HI"                       , 0x00000014, 0x00000001, 0x00000001},
    {"OTP_RSTB_PW_LO"                       , 0x00000015, 0x00000001, 0x00000001},
    {"OTP_PGM_PW_HI"                        , 0x00000018, 0x00000001, 0x00000001},
    {"OTP_PGM_PW_LO"                        , 0x00000019, 0x00000001, 0x00000001},
    {"OTP_READ_PW_HI"                       , 0x0000001c, 0x00000001, 0x00000001},
    {"OTP_READ_PW_LO"                       , 0x0000001d, 0x00000001, 0x00000001},
    {"OTP_TCRST_VAL"                        , 0x00000020, 0x00000001, 0x00000001},
    {"OTP_TRSRD_VAL"                        , 0x00000021, 0x00000001, 0x00000001},
    {"OTP_TREADEN_VAL"                      , 0x00000022, 0x00000001, 0x00000001},
    {"OTP_TDLES_VAL"                        , 0x00000023, 0x00000001, 0x00000001},
    {"OTP_TWWL_VAL"                         , 0x00000024, 0x00000001, 0x00000001},
    {"OTP_TDLEH_VAL"                        , 0x00000025, 0x00000001, 0x00000001},
    {"OTP_TWPED_VAL"                        , 0x00000026, 0x00000001, 0x00000001},
    {"OTP_TPES_VAL"                         , 0x00000027, 0x00000001, 0x00000001},
    {"OTP_TCPS_VAL"                         , 0x00000028, 0x00000001, 0x00000001},
    {"OTP_TCPH_VAL"                         , 0x00000029, 0x00000001, 0x00000001},
    {"OTP_TPGMVFY_VAL"                      , 0x0000002a, 0x00000001, 0x00000001},
    {"OTP_TPEH_VAL"                         , 0x0000002b, 0x00000001, 0x00000001},
    {"OTP_TPGRST_VAL"                       , 0x0000002c, 0x00000001, 0x00000001},
    {"OTP_TCLES_VAL"                        , 0x0000002d, 0x00000001, 0x00000001},
    {"OTP_TCLEH_VAL"                        , 0x0000002e, 0x00000001, 0x00000001},
    {"OTP_TRDES_VAL"                        , 0x0000002f, 0x00000001, 0x00000001},
    {"OTP_TBCAAC_VAL"                       , 0x00000030, 0x00000001, 0x00000001},
    {"OTP_TAAC_VAL"                         , 0x00000031, 0x00000001, 0x00000001},
    {"OTP_TACCT_VAL"                        , 0x00000032, 0x00000001, 0x00000001},
    {"OTP_TPWAD_VAL"                        , 0x00000033, 0x00000001, 0x00000001},
    {"OTP_TWCAD_VAL_HI"                     , 0x00000034, 0x00000001, 0x00000001},
    {"OTP_TWCAD_VAL_LO"                     , 0x00000035, 0x00000001, 0x00000001},
    {"OTP_TAS_VAL"                          , 0x00000036, 0x00000001, 0x00000001},
    {"OTP_TDS_VAL"                          , 0x00000037, 0x00000001, 0x00000001},
    {"OTP_TPVSR_VAL"                        , 0x0000003a, 0x00000001, 0x00000001},
    {"OTP_TVHR_VAL"                         , 0x0000003b, 0x00000001, 0x00000001},
    {"OTP_TPGMAS_VAL"                       , 0x0000003c, 0x00000001, 0x00000001},
    {"OTP_TCWDD_VAL"                        , 0x0000003d, 0x00000001, 0x00000001},
    {"OTP_TCPRD_VAL"                        , 0x00000040, 0x00000001, 0x00000001},
    {"OTP_TRDCP_VAL"                        , 0x00000041, 0x00000001, 0x00000001},
    {"OTP_NP1_VAL"                          , 0x00000045, 0x00000001, 0x00000001},
    {"OTP_NP2_VAL"                          , 0x00000046, 0x00000001, 0x00000001},
    {"OTP_READ_PROTECT"                     , 0x00000080, 0x00000001, 0x00000001},
    {"OTP_FPGA_PROM_CTL"                    , 0x000000c0, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_OTP[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"OTP_REGS"                             , 0x00000000, 0x00000001, 0x000000c1, regs_within_OTP_OTP_REGS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_QSPI_QSPI_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"QSPI_CR"                              , 0x00000000, 0x00000001, 0x00000001},
    {"QSPI_MR"                              , 0x00000001, 0x00000001, 0x00000001},
    {"QSPI_RDR"                             , 0x00000002, 0x00000001, 0x00000001},
    {"QSPI_TDR"                             , 0x00000003, 0x00000001, 0x00000001},
    {"QSPI_ISR"                             , 0x00000004, 0x00000001, 0x00000001},
    {"QSPI_IER"                             , 0x00000005, 0x00000001, 0x00000001},
    {"QSPI_IDR"                             , 0x00000006, 0x00000001, 0x00000001},
    {"QSPI_IMR"                             , 0x00000007, 0x00000001, 0x00000001},
    {"QSPI_SCR"                             , 0x00000008, 0x00000001, 0x00000001},
    {"QSPI_SR"                              , 0x00000009, 0x00000001, 0x00000001},
    {"QSPI_IAR"                             , 0x0000000c, 0x00000001, 0x00000001},
    {"QSPI_WICR"                            , 0x0000000d, 0x00000001, 0x00000001},
    {"QSPI_IFR"                             , 0x0000000e, 0x00000001, 0x00000001},
    {"QSPI_RICR"                            , 0x0000000f, 0x00000001, 0x00000001},
    {"QSPI_SMR"                             , 0x00000010, 0x00000001, 0x00000001},
    {"QSPI_SKR"                             , 0x00000011, 0x00000001, 0x00000001},
    {"QSPI_REFRESH"                         , 0x00000014, 0x00000001, 0x00000001},
    {"QSPI_WRACNT"                          , 0x00000015, 0x00000001, 0x00000001},
    {"QSPI_DLLCFG"                          , 0x00000016, 0x00000001, 0x00000001},
    {"QSPI_PCALCFG"                         , 0x00000017, 0x00000001, 0x00000001},
    {"QSPI_PCALBP"                          , 0x00000018, 0x00000001, 0x00000001},
    {"QSPI_TOUT"                            , 0x00000019, 0x00000001, 0x00000001},
    {"QSPI_DEBUG"                           , 0x00000034, 0x00000001, 0x00000001},
    {"QSPI_WPMR"                            , 0x00000039, 0x00000001, 0x00000001},
    {"QSPI_WPSR"                            , 0x0000003a, 0x00000001, 0x00000001},
    {"QSPI_VERSION"                         , 0x0000003f, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_QSPI[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"QSPI_REGS"                            , 0x00000000, 0x00000001, 0x00000040, regs_within_QSPI_QSPI_REGS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_SDMMC_SDMMC_REG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SDMMC_SSAR"                           , 0x00000000, 0x00000001, 0x00000001},
    {"SDMMC_BSBCR"                          , 0x00000001, 0x00000001, 0x00000001},
    {"SDMMC_ARG1R"                          , 0x00000002, 0x00000001, 0x00000001},
    {"SDMMC_TMCR"                           , 0x00000003, 0x00000001, 0x00000001},
    {"SDMMC_RR0"                            , 0x00000004, 0x00000001, 0x00000001},
    {"SDMMC_RR1"                            , 0x00000005, 0x00000001, 0x00000001},
    {"SDMMC_RR2"                            , 0x00000006, 0x00000001, 0x00000001},
    {"SDMMC_RR3"                            , 0x00000007, 0x00000001, 0x00000001},
    {"SDMMC_BDPR"                           , 0x00000008, 0x00000001, 0x00000001},
    {"SDMMC_PSR"                            , 0x00000009, 0x00000001, 0x00000001},
    {"SDMMC_HC1R"                           , 0x0000000a, 0x00000001, 0x00000001},
    {"SDMMC_CTSR"                           , 0x0000000b, 0x00000001, 0x00000001},
    {"SDMMC_NIEI_STR"                       , 0x0000000c, 0x00000001, 0x00000001},
    {"SDMMC_NIEI_STER"                      , 0x0000000d, 0x00000001, 0x00000001},
    {"SDMMC_NIEI_SIGER"                     , 0x0000000e, 0x00000001, 0x00000001},
    {"SDMMC_ACESR_HC2R"                     , 0x0000000f, 0x00000001, 0x00000001},
    {"SDMMC_CA0R"                           , 0x00000010, 0x00000001, 0x00000001},
    {"SDMMC_CA1R"                           , 0x00000011, 0x00000001, 0x00000001},
    {"SDMMC_MCCAR"                          , 0x00000012, 0x00000001, 0x00000001},
    {"SDMMC_FCES_FEIS"                      , 0x00000014, 0x00000001, 0x00000001},
    {"SDMMC_AESR"                           , 0x00000015, 0x00000001, 0x00000001},
    {"SDMMC_ASAR0"                          , 0x00000016, 0x00000001, 0x00000001},
    {"SDMMC_ASAR1"                          , 0x00000017, 0x00000001, 0x00000001},
    {"SDMMC_PVR01"                          , 0x00000018, 0x00000001, 0x00000001},
    {"SDMMC_PVR23"                          , 0x00000019, 0x00000001, 0x00000001},
    {"SDMMC_PVR45"                          , 0x0000001a, 0x00000001, 0x00000001},
    {"SDMMC_PVR67"                          , 0x0000001b, 0x00000001, 0x00000001},
    {"SDMMC_SBCR"                           , 0x00000038, 0x00000001, 0x00000001},
    {"SDMMC_SISR"                           , 0x0000003f, 0x00000001, 0x00000001},
    {"SDMMC_APSR"                           , 0x00000080, 0x00000001, 0x00000001},
    {"SDMMC_MCR_DEBR"                       , 0x00000081, 0x00000001, 0x00000001},
    {"SDMMC_ACR"                            , 0x00000082, 0x00000001, 0x00000001},
    {"SDMMC_CC2R"                           , 0x00000083, 0x00000001, 0x00000001},
    {"SDMMC_RTC_1R2R"                       , 0x00000084, 0x00000001, 0x00000001},
    {"SDMMC_RTCVR"                          , 0x00000085, 0x00000001, 0x00000001},
    {"SDMMC_RTI_STSIER"                     , 0x00000086, 0x00000001, 0x00000001},
    {"SDMMC_RTISTR_RTSSR"                   , 0x00000087, 0x00000001, 0x00000001},
    {"SDMMC_TUNCR"                          , 0x00000088, 0x00000001, 0x00000001},
    {"SDMMC_TUNSR"                          , 0x00000089, 0x00000001, 0x00000001},
    {"SDMMC_FSMTR"                          , 0x0000008a, 0x00000001, 0x00000001},
    {"SDMMC_CACR"                           , 0x0000008c, 0x00000001, 0x00000001},
    {"SDMMC_DBGR"                           , 0x0000008d, 0x00000001, 0x00000001},
    {"SDMMC_EDBGR"                          , 0x0000008e, 0x00000001, 0x00000001},
    {"SDMMC_CALCR"                          , 0x00000090, 0x00000001, 0x00000001},
    {"SDMMC_EPVR8"                          , 0x00000091, 0x00000001, 0x00000001},
    {"SDMMC_TXPHTR"                         , 0x0000009c, 0x00000001, 0x00000001},
    {"SDMMC_VERSION1"                       , 0x000000ba, 0x00000001, 0x00000001},
    {"SDMMC_VERSION2"                       , 0x000000bb, 0x00000001, 0x00000001},
    {"SDMMC_VERSION3"                       , 0x000000bf, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_SDMMC[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"SDMMC_REG"                            , 0x00000000, 0x00000001, 0x000000c0, regs_within_SDMMC_SDMMC_REG},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_SHA_SHA_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SHA_CR"                               , 0x00000000, 0x00000001, 0x00000001},
    {"SHA_MR"                               , 0x00000001, 0x00000001, 0x00000001},
    {"SHA_IER"                              , 0x00000004, 0x00000001, 0x00000001},
    {"SHA_IDR"                              , 0x00000005, 0x00000001, 0x00000001},
    {"SHA_IMR"                              , 0x00000006, 0x00000001, 0x00000001},
    {"SHA_ISR"                              , 0x00000007, 0x00000001, 0x00000001},
    {"SHA_MSR"                              , 0x00000008, 0x00000001, 0x00000001},
    {"SHA_BCR"                              , 0x0000000c, 0x00000001, 0x00000001},
    {"SHA_IDATAR0"                          , 0x00000010, 0x00000001, 0x00000001},
    {"SHA_IDATAR1"                          , 0x00000011, 0x00000001, 0x00000001},
    {"SHA_IDATAR2"                          , 0x00000012, 0x00000001, 0x00000001},
    {"SHA_IDATAR3"                          , 0x00000013, 0x00000001, 0x00000001},
    {"SHA_IDATAR4"                          , 0x00000014, 0x00000001, 0x00000001},
    {"SHA_IDATAR5"                          , 0x00000015, 0x00000001, 0x00000001},
    {"SHA_IDATAR6"                          , 0x00000016, 0x00000001, 0x00000001},
    {"SHA_IDATAR7"                          , 0x00000017, 0x00000001, 0x00000001},
    {"SHA_IDATAR8"                          , 0x00000018, 0x00000001, 0x00000001},
    {"SHA_IDATAR9"                          , 0x00000019, 0x00000001, 0x00000001},
    {"SHA_IDATAR10"                         , 0x0000001a, 0x00000001, 0x00000001},
    {"SHA_IDATAR11"                         , 0x0000001b, 0x00000001, 0x00000001},
    {"SHA_IDATAR12"                         , 0x0000001c, 0x00000001, 0x00000001},
    {"SHA_IDATAR13"                         , 0x0000001d, 0x00000001, 0x00000001},
    {"SHA_IDATAR14"                         , 0x0000001e, 0x00000001, 0x00000001},
    {"SHA_IDATAR15"                         , 0x0000001f, 0x00000001, 0x00000001},
    {"SHA_IODATAR0"                         , 0x00000020, 0x00000001, 0x00000001},
    {"SHA_IODATAR1"                         , 0x00000021, 0x00000001, 0x00000001},
    {"SHA_IODATAR2"                         , 0x00000022, 0x00000001, 0x00000001},
    {"SHA_IODATAR3"                         , 0x00000023, 0x00000001, 0x00000001},
    {"SHA_IODATAR4"                         , 0x00000024, 0x00000001, 0x00000001},
    {"SHA_IODATAR5"                         , 0x00000025, 0x00000001, 0x00000001},
    {"SHA_IODATAR6"                         , 0x00000026, 0x00000001, 0x00000001},
    {"SHA_IODATAR7"                         , 0x00000027, 0x00000001, 0x00000001},
    {"SHA_IODATAR8"                         , 0x00000028, 0x00000001, 0x00000001},
    {"SHA_IODATAR9"                         , 0x00000029, 0x00000001, 0x00000001},
    {"SHA_IODATAR10"                        , 0x0000002a, 0x00000001, 0x00000001},
    {"SHA_IODATAR11"                        , 0x0000002b, 0x00000001, 0x00000001},
    {"SHA_IODATAR12"                        , 0x0000002c, 0x00000001, 0x00000001},
    {"SHA_IODATAR13"                        , 0x0000002d, 0x00000001, 0x00000001},
    {"SHA_IODATAR14"                        , 0x0000002e, 0x00000001, 0x00000001},
    {"SHA_IODATAR15"                        , 0x0000002f, 0x00000001, 0x00000001},
    {"SHA_WPMR"                             , 0x00000039, 0x00000001, 0x00000001},
    {"SHA_WPSR"                             , 0x0000003a, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_SHA[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"SHA_REGS"                             , 0x00000000, 0x00000001, 0x0000003b, regs_within_SHA_SHA_REGS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_SJTAG_SJTAG_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CTL"                                  , 0x00000000, 0x00000001, 0x00000001},
    {"INT_STATUS"                           , 0x00000001, 0x00000001, 0x00000001},
    {"INT_MASK"                             , 0x00000002, 0x00000001, 0x00000001},
    {"NONCE"                                , 0x00000004, 0x00000008, 0x00000001},
    {"HOST_DIGEST"                          , 0x0000000c, 0x00000008, 0x00000001},
    {"DEVICE_DIGEST"                        , 0x00000014, 0x00000008, 0x00000001},
    {"UUID"                                 , 0x0000001c, 0x00000003, 0x00000001},
    {"HC_TO"                                , 0x00000020, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_SJTAG[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"SJTAG_REGS"                           , 0x00000000, 0x00000001, 0x0000001f, regs_within_SJTAG_SJTAG_REGS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_TIMERS_TIMERS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TIMER1LOADCOUNT"                      , 0x00000000, 0x00000001, 0x00000001},
    {"TIMER1CURRENTVAL"                     , 0x00000001, 0x00000001, 0x00000001},
    {"TIMER1CONTROLREG"                     , 0x00000002, 0x00000001, 0x00000001},
    {"TIMER1EOI"                            , 0x00000003, 0x00000001, 0x00000001},
    {"TIMER1INTSTAT"                        , 0x00000004, 0x00000001, 0x00000001},
    {"TIMER2LOADCOUNT"                      , 0x00000005, 0x00000001, 0x00000001},
    {"TIMER2CURRENTVAL"                     , 0x00000006, 0x00000001, 0x00000001},
    {"TIMER2CONTROLREG"                     , 0x00000007, 0x00000001, 0x00000001},
    {"TIMER2EOI"                            , 0x00000008, 0x00000001, 0x00000001},
    {"TIMER2INTSTAT"                        , 0x00000009, 0x00000001, 0x00000001},
    {"TIMER3LOADCOUNT"                      , 0x0000000a, 0x00000001, 0x00000001},
    {"TIMER3CURRENTVAL"                     , 0x0000000b, 0x00000001, 0x00000001},
    {"TIMER3CONTROLREG"                     , 0x0000000c, 0x00000001, 0x00000001},
    {"TIMER3EOI"                            , 0x0000000d, 0x00000001, 0x00000001},
    {"TIMER3INTSTAT"                        , 0x0000000e, 0x00000001, 0x00000001},
    {"TIMERSINTSTATUS"                      , 0x00000028, 0x00000001, 0x00000001},
    {"TIMERSEOI"                            , 0x00000029, 0x00000001, 0x00000001},
    {"TIMERSRAWINTSTATUS"                   , 0x0000002a, 0x00000001, 0x00000001},
    {"TIMERS_COMP_VERSION"                  , 0x0000002b, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_TIMERS[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"TIMERS"                               , 0x00000000, 0x00000001, 0x00000100, regs_within_TIMERS_TIMERS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_TRNG_TRNG_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TRNG_CR"                              , 0x00000000, 0x00000001, 0x00000001},
    {"TRNG_MR"                              , 0x00000001, 0x00000001, 0x00000001},
    {"TRNG_PKBCR"                           , 0x00000002, 0x00000001, 0x00000001},
    {"TRNG_IER"                             , 0x00000004, 0x00000001, 0x00000001},
    {"TRNG_IDR"                             , 0x00000005, 0x00000001, 0x00000001},
    {"TRNG_IMR"                             , 0x00000006, 0x00000001, 0x00000001},
    {"TRNG_ISR"                             , 0x00000007, 0x00000001, 0x00000001},
    {"TRNG_ODATA"                           , 0x00000014, 0x00000001, 0x00000001},
    {"TRNG_WPMR"                            , 0x00000039, 0x00000001, 0x00000001},
    {"TRNG_WPSR"                            , 0x0000003a, 0x00000001, 0x00000001},
    {"TRNG_VERSION"                         , 0x0000003f, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_TRNG[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"TRNG_REGS"                            , 0x00000000, 0x00000001, 0x00000040, regs_within_TRNG_TRNG_REGS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_TZAESB_TZAESB_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TZAESB_CR"                            , 0x00000000, 0x00000001, 0x00000001},
    {"TZAESB_MR"                            , 0x00000001, 0x00000001, 0x00000001},
    {"TZAESB_IER"                           , 0x00000004, 0x00000001, 0x00000001},
    {"TZAESB_IDR"                           , 0x00000005, 0x00000001, 0x00000001},
    {"TZAESB_IMR"                           , 0x00000006, 0x00000001, 0x00000001},
    {"TZAESB_ISR"                           , 0x00000007, 0x00000001, 0x00000001},
    {"TZAESB_KEYWR0"                        , 0x00000008, 0x00000001, 0x00000001},
    {"TZAESB_KEYWR1"                        , 0x00000009, 0x00000001, 0x00000001},
    {"TZAESB_KEYWR2"                        , 0x0000000a, 0x00000001, 0x00000001},
    {"TZAESB_KEYWR3"                        , 0x0000000b, 0x00000001, 0x00000001},
    {"TZAESB_IVR0"                          , 0x00000018, 0x00000001, 0x00000001},
    {"TZAESB_IVR1"                          , 0x00000019, 0x00000001, 0x00000001},
    {"TZAESB_IVR2"                          , 0x0000001a, 0x00000001, 0x00000001},
    {"TZAESB_IVR3"                          , 0x0000001b, 0x00000001, 0x00000001},
    {"TZAESB_EMR"                           , 0x0000002c, 0x00000001, 0x00000001},
    {"TZAESB_WPMR"                          , 0x00000039, 0x00000001, 0x00000001},
    {"TZAESB_WPSR"                          , 0x0000003a, 0x00000001, 0x00000001},
    {"TZAESB_VERSION"                       , 0x0000003f, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_TZAESB[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"TZAESB_REGS"                          , 0x00000000, 0x00000001, 0x00000040, regs_within_TZAESB_TZAESB_REGS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_TZPM_TZPM_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TZPM_EN"                              , 0x00000000, 0x00000001, 0x00000001},
    {"TZPM_KEY"                             , 0x00000001, 0x00000001, 0x00000001},
    {"TZPCTL0"                              , 0x00000002, 0x00000001, 0x00000001},
    {"TZPCTL1"                              , 0x00000003, 0x00000001, 0x00000001},
    {"TZPCTL2"                              , 0x00000004, 0x00000001, 0x00000001},
    {"TZPCTL3"                              , 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_TZPM[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"TZPM_REGS"                            , 0x00000000, 0x00000001, 0x00000006, regs_within_TZPM_TZPM_REGS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_WDT_WDT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"WDT_CR"                               , 0x00000000, 0x00000001, 0x00000001},
    {"WDT_TORR"                             , 0x00000001, 0x00000001, 0x00000001},
    {"WDT_CCVR"                             , 0x00000002, 0x00000001, 0x00000001},
    {"WDT_CRR"                              , 0x00000003, 0x00000001, 0x00000001},
    {"WDT_STAT"                             , 0x00000004, 0x00000001, 0x00000001},
    {"WDT_EOI"                              , 0x00000005, 0x00000001, 0x00000001},
    {"WDT_COMP_PARAM_5"                     , 0x00000039, 0x00000001, 0x00000001},
    {"WDT_COMP_PARAM_4"                     , 0x0000003a, 0x00000001, 0x00000001},
    {"WDT_COMP_PARAM_3"                     , 0x0000003b, 0x00000001, 0x00000001},
    {"WDT_COMP_PARAM_2"                     , 0x0000003c, 0x00000001, 0x00000001},
    {"WDT_COMP_PARAM_1"                     , 0x0000003d, 0x00000001, 0x00000001},
    {"WDT_COMP_VERSION"                     , 0x0000003e, 0x00000001, 0x00000001},
    {"WDT_COMP_TYPE"                        , 0x0000003f, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_WDT[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"WDT"                                  , 0x00000000, 0x00000001, 0x00000400, regs_within_WDT_WDT},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_XDMAC_XDMAC_REG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"XDMAC_GTYPE"                          , 0x00000000, 0x00000001, 0x00000001},
    {"XDMAC_GCFG"                           , 0x00000001, 0x00000001, 0x00000001},
    {"XDMAC_GWAC"                           , 0x00000002, 0x00000001, 0x00000001},
    {"XDMAC_GIE"                            , 0x00000003, 0x00000001, 0x00000001},
    {"XDMAC_GID"                            , 0x00000004, 0x00000001, 0x00000001},
    {"XDMAC_GIM"                            , 0x00000005, 0x00000001, 0x00000001},
    {"XDMAC_GIS"                            , 0x00000006, 0x00000001, 0x00000001},
    {"XDMAC_GE"                             , 0x00000007, 0x00000001, 0x00000001},
    {"XDMAC_GD"                             , 0x00000008, 0x00000001, 0x00000001},
    {"XDMAC_GS"                             , 0x00000009, 0x00000001, 0x00000001},
    {"XDMAC_GRSS"                           , 0x0000000a, 0x00000001, 0x00000001},
    {"XDMAC_GWSS"                           , 0x0000000b, 0x00000001, 0x00000001},
    {"XDMAC_GRS"                            , 0x0000000c, 0x00000001, 0x00000001},
    {"XDMAC_GRR"                            , 0x0000000d, 0x00000001, 0x00000001},
    {"XDMAC_GWS"                            , 0x0000000e, 0x00000001, 0x00000001},
    {"XDMAC_GWR"                            , 0x0000000f, 0x00000001, 0x00000001},
    {"XDMAC_GRWS"                           , 0x00000010, 0x00000001, 0x00000001},
    {"XDMAC_GRWR"                           , 0x00000011, 0x00000001, 0x00000001},
    {"XDMAC_GSWR"                           , 0x00000012, 0x00000001, 0x00000001},
    {"XDMAC_GSWS"                           , 0x00000013, 0x00000001, 0x00000001},
    {"XDMAC_GSWF"                           , 0x00000014, 0x00000001, 0x00000001},
    {"XDMAC_CIE_CH0"                        , 0x00000018, 0x00000001, 0x00000001},
    {"XDMAC_CID_CH0"                        , 0x00000019, 0x00000001, 0x00000001},
    {"XDMAC_CIM_CH0"                        , 0x0000001a, 0x00000001, 0x00000001},
    {"XDMAC_CIS_CH0"                        , 0x0000001b, 0x00000001, 0x00000001},
    {"XDMAC_CSA_CH0"                        , 0x0000001c, 0x00000001, 0x00000001},
    {"XDMAC_CDA_CH0"                        , 0x0000001d, 0x00000001, 0x00000001},
    {"XDMAC_CNDA_CH0"                       , 0x0000001e, 0x00000001, 0x00000001},
    {"XDMAC_CNDC_CH0"                       , 0x0000001f, 0x00000001, 0x00000001},
    {"XDMAC_CUBC_CH0"                       , 0x00000020, 0x00000001, 0x00000001},
    {"XDMAC_CBC_CH0"                        , 0x00000021, 0x00000001, 0x00000001},
    {"XDMAC_CC_CH0"                         , 0x00000022, 0x00000001, 0x00000001},
    {"XDMAC_CDS_MSP_CH0"                    , 0x00000023, 0x00000001, 0x00000001},
    {"XDMAC_CSUS_CH0"                       , 0x00000024, 0x00000001, 0x00000001},
    {"XDMAC_CDUS_CH0"                       , 0x00000025, 0x00000001, 0x00000001},
    {"XDMAC_CTCS_CH0"                       , 0x00000026, 0x00000001, 0x00000001},
    {"XDMAC_CIE_CH1"                        , 0x00000028, 0x00000001, 0x00000001},
    {"XDMAC_CID_CH1"                        , 0x00000029, 0x00000001, 0x00000001},
    {"XDMAC_CIM_CH1"                        , 0x0000002a, 0x00000001, 0x00000001},
    {"XDMAC_CIS_CH1"                        , 0x0000002b, 0x00000001, 0x00000001},
    {"XDMAC_CSA_CH1"                        , 0x0000002c, 0x00000001, 0x00000001},
    {"XDMAC_CDA_CH1"                        , 0x0000002d, 0x00000001, 0x00000001},
    {"XDMAC_CNDA_CH1"                       , 0x0000002e, 0x00000001, 0x00000001},
    {"XDMAC_CNDC_CH1"                       , 0x0000002f, 0x00000001, 0x00000001},
    {"XDMAC_CUBC_CH1"                       , 0x00000030, 0x00000001, 0x00000001},
    {"XDMAC_CBC_CH1"                        , 0x00000031, 0x00000001, 0x00000001},
    {"XDMAC_CC_CH1"                         , 0x00000032, 0x00000001, 0x00000001},
    {"XDMAC_CDS_MSP_CH1"                    , 0x00000033, 0x00000001, 0x00000001},
    {"XDMAC_CSUS_CH1"                       , 0x00000034, 0x00000001, 0x00000001},
    {"XDMAC_CDUS_CH1"                       , 0x00000035, 0x00000001, 0x00000001},
    {"XDMAC_CTCS_CH1"                       , 0x00000036, 0x00000001, 0x00000001},
    {"XDMAC_CIE_CH2"                        , 0x00000038, 0x00000001, 0x00000001},
    {"XDMAC_CID_CH2"                        , 0x00000039, 0x00000001, 0x00000001},
    {"XDMAC_CIM_CH2"                        , 0x0000003a, 0x00000001, 0x00000001},
    {"XDMAC_CIS_CH2"                        , 0x0000003b, 0x00000001, 0x00000001},
    {"XDMAC_CSA_CH2"                        , 0x0000003c, 0x00000001, 0x00000001},
    {"XDMAC_CDA_CH2"                        , 0x0000003d, 0x00000001, 0x00000001},
    {"XDMAC_CNDA_CH2"                       , 0x0000003e, 0x00000001, 0x00000001},
    {"XDMAC_CNDC_CH2"                       , 0x0000003f, 0x00000001, 0x00000001},
    {"XDMAC_CUBC_CH2"                       , 0x00000040, 0x00000001, 0x00000001},
    {"XDMAC_CBC_CH2"                        , 0x00000041, 0x00000001, 0x00000001},
    {"XDMAC_CC_CH2"                         , 0x00000042, 0x00000001, 0x00000001},
    {"XDMAC_CDS_MSP_CH2"                    , 0x00000043, 0x00000001, 0x00000001},
    {"XDMAC_CSUS_CH2"                       , 0x00000044, 0x00000001, 0x00000001},
    {"XDMAC_CDUS_CH2"                       , 0x00000045, 0x00000001, 0x00000001},
    {"XDMAC_CTCS_CH2"                       , 0x00000046, 0x00000001, 0x00000001},
    {"XDMAC_CIE_CH3"                        , 0x00000048, 0x00000001, 0x00000001},
    {"XDMAC_CID_CH3"                        , 0x00000049, 0x00000001, 0x00000001},
    {"XDMAC_CIM_CH3"                        , 0x0000004a, 0x00000001, 0x00000001},
    {"XDMAC_CIS_CH3"                        , 0x0000004b, 0x00000001, 0x00000001},
    {"XDMAC_CSA_CH3"                        , 0x0000004c, 0x00000001, 0x00000001},
    {"XDMAC_CDA_CH3"                        , 0x0000004d, 0x00000001, 0x00000001},
    {"XDMAC_CNDA_CH3"                       , 0x0000004e, 0x00000001, 0x00000001},
    {"XDMAC_CNDC_CH3"                       , 0x0000004f, 0x00000001, 0x00000001},
    {"XDMAC_CUBC_CH3"                       , 0x00000050, 0x00000001, 0x00000001},
    {"XDMAC_CBC_CH3"                        , 0x00000051, 0x00000001, 0x00000001},
    {"XDMAC_CC_CH3"                         , 0x00000052, 0x00000001, 0x00000001},
    {"XDMAC_CDS_MSP_CH3"                    , 0x00000053, 0x00000001, 0x00000001},
    {"XDMAC_CSUS_CH3"                       , 0x00000054, 0x00000001, 0x00000001},
    {"XDMAC_CDUS_CH3"                       , 0x00000055, 0x00000001, 0x00000001},
    {"XDMAC_CTCS_CH3"                       , 0x00000056, 0x00000001, 0x00000001},
    {"XDMAC_CIE_CH4"                        , 0x00000058, 0x00000001, 0x00000001},
    {"XDMAC_CID_CH4"                        , 0x00000059, 0x00000001, 0x00000001},
    {"XDMAC_CIM_CH4"                        , 0x0000005a, 0x00000001, 0x00000001},
    {"XDMAC_CIS_CH4"                        , 0x0000005b, 0x00000001, 0x00000001},
    {"XDMAC_CSA_CH4"                        , 0x0000005c, 0x00000001, 0x00000001},
    {"XDMAC_CDA_CH4"                        , 0x0000005d, 0x00000001, 0x00000001},
    {"XDMAC_CNDA_CH4"                       , 0x0000005e, 0x00000001, 0x00000001},
    {"XDMAC_CNDC_CH4"                       , 0x0000005f, 0x00000001, 0x00000001},
    {"XDMAC_CUBC_CH4"                       , 0x00000060, 0x00000001, 0x00000001},
    {"XDMAC_CBC_CH4"                        , 0x00000061, 0x00000001, 0x00000001},
    {"XDMAC_CC_CH4"                         , 0x00000062, 0x00000001, 0x00000001},
    {"XDMAC_CDS_MSP_CH4"                    , 0x00000063, 0x00000001, 0x00000001},
    {"XDMAC_CSUS_CH4"                       , 0x00000064, 0x00000001, 0x00000001},
    {"XDMAC_CDUS_CH4"                       , 0x00000065, 0x00000001, 0x00000001},
    {"XDMAC_CTCS_CH4"                       , 0x00000066, 0x00000001, 0x00000001},
    {"XDMAC_CIE_CH5"                        , 0x00000068, 0x00000001, 0x00000001},
    {"XDMAC_CID_CH5"                        , 0x00000069, 0x00000001, 0x00000001},
    {"XDMAC_CIM_CH5"                        , 0x0000006a, 0x00000001, 0x00000001},
    {"XDMAC_CIS_CH5"                        , 0x0000006b, 0x00000001, 0x00000001},
    {"XDMAC_CSA_CH5"                        , 0x0000006c, 0x00000001, 0x00000001},
    {"XDMAC_CDA_CH5"                        , 0x0000006d, 0x00000001, 0x00000001},
    {"XDMAC_CNDA_CH5"                       , 0x0000006e, 0x00000001, 0x00000001},
    {"XDMAC_CNDC_CH5"                       , 0x0000006f, 0x00000001, 0x00000001},
    {"XDMAC_CUBC_CH5"                       , 0x00000070, 0x00000001, 0x00000001},
    {"XDMAC_CBC_CH5"                        , 0x00000071, 0x00000001, 0x00000001},
    {"XDMAC_CC_CH5"                         , 0x00000072, 0x00000001, 0x00000001},
    {"XDMAC_CDS_MSP_CH5"                    , 0x00000073, 0x00000001, 0x00000001},
    {"XDMAC_CSUS_CH5"                       , 0x00000074, 0x00000001, 0x00000001},
    {"XDMAC_CDUS_CH5"                       , 0x00000075, 0x00000001, 0x00000001},
    {"XDMAC_CTCS_CH5"                       , 0x00000076, 0x00000001, 0x00000001},
    {"XDMAC_CIE_CH6"                        , 0x00000078, 0x00000001, 0x00000001},
    {"XDMAC_CID_CH6"                        , 0x00000079, 0x00000001, 0x00000001},
    {"XDMAC_CIM_CH6"                        , 0x0000007a, 0x00000001, 0x00000001},
    {"XDMAC_CIS_CH6"                        , 0x0000007b, 0x00000001, 0x00000001},
    {"XDMAC_CSA_CH6"                        , 0x0000007c, 0x00000001, 0x00000001},
    {"XDMAC_CDA_CH6"                        , 0x0000007d, 0x00000001, 0x00000001},
    {"XDMAC_CNDA_CH6"                       , 0x0000007e, 0x00000001, 0x00000001},
    {"XDMAC_CNDC_CH6"                       , 0x0000007f, 0x00000001, 0x00000001},
    {"XDMAC_CUBC_CH6"                       , 0x00000080, 0x00000001, 0x00000001},
    {"XDMAC_CBC_CH6"                        , 0x00000081, 0x00000001, 0x00000001},
    {"XDMAC_CC_CH6"                         , 0x00000082, 0x00000001, 0x00000001},
    {"XDMAC_CDS_MSP_CH6"                    , 0x00000083, 0x00000001, 0x00000001},
    {"XDMAC_CSUS_CH6"                       , 0x00000084, 0x00000001, 0x00000001},
    {"XDMAC_CDUS_CH6"                       , 0x00000085, 0x00000001, 0x00000001},
    {"XDMAC_CTCS_CH6"                       , 0x00000086, 0x00000001, 0x00000001},
    {"XDMAC_CIE_CH7"                        , 0x00000088, 0x00000001, 0x00000001},
    {"XDMAC_CID_CH7"                        , 0x00000089, 0x00000001, 0x00000001},
    {"XDMAC_CIM_CH7"                        , 0x0000008a, 0x00000001, 0x00000001},
    {"XDMAC_CIS_CH7"                        , 0x0000008b, 0x00000001, 0x00000001},
    {"XDMAC_CSA_CH7"                        , 0x0000008c, 0x00000001, 0x00000001},
    {"XDMAC_CDA_CH7"                        , 0x0000008d, 0x00000001, 0x00000001},
    {"XDMAC_CNDA_CH7"                       , 0x0000008e, 0x00000001, 0x00000001},
    {"XDMAC_CNDC_CH7"                       , 0x0000008f, 0x00000001, 0x00000001},
    {"XDMAC_CUBC_CH7"                       , 0x00000090, 0x00000001, 0x00000001},
    {"XDMAC_CBC_CH7"                        , 0x00000091, 0x00000001, 0x00000001},
    {"XDMAC_CC_CH7"                         , 0x00000092, 0x00000001, 0x00000001},
    {"XDMAC_CDS_MSP_CH7"                    , 0x00000093, 0x00000001, 0x00000001},
    {"XDMAC_CSUS_CH7"                       , 0x00000094, 0x00000001, 0x00000001},
    {"XDMAC_CDUS_CH7"                       , 0x00000095, 0x00000001, 0x00000001},
    {"XDMAC_CTCS_CH7"                       , 0x00000096, 0x00000001, 0x00000001},
    {"XDMAC_CIE_CH8"                        , 0x00000098, 0x00000001, 0x00000001},
    {"XDMAC_CID_CH8"                        , 0x00000099, 0x00000001, 0x00000001},
    {"XDMAC_CIM_CH8"                        , 0x0000009a, 0x00000001, 0x00000001},
    {"XDMAC_CIS_CH8"                        , 0x0000009b, 0x00000001, 0x00000001},
    {"XDMAC_CSA_CH8"                        , 0x0000009c, 0x00000001, 0x00000001},
    {"XDMAC_CDA_CH8"                        , 0x0000009d, 0x00000001, 0x00000001},
    {"XDMAC_CNDA_CH8"                       , 0x0000009e, 0x00000001, 0x00000001},
    {"XDMAC_CNDC_CH8"                       , 0x0000009f, 0x00000001, 0x00000001},
    {"XDMAC_CUBC_CH8"                       , 0x000000a0, 0x00000001, 0x00000001},
    {"XDMAC_CBC_CH8"                        , 0x000000a1, 0x00000001, 0x00000001},
    {"XDMAC_CC_CH8"                         , 0x000000a2, 0x00000001, 0x00000001},
    {"XDMAC_CDS_MSP_CH8"                    , 0x000000a3, 0x00000001, 0x00000001},
    {"XDMAC_CSUS_CH8"                       , 0x000000a4, 0x00000001, 0x00000001},
    {"XDMAC_CDUS_CH8"                       , 0x000000a5, 0x00000001, 0x00000001},
    {"XDMAC_CTCS_CH8"                       , 0x000000a6, 0x00000001, 0x00000001},
    {"XDMAC_CIE_CH9"                        , 0x000000a8, 0x00000001, 0x00000001},
    {"XDMAC_CID_CH9"                        , 0x000000a9, 0x00000001, 0x00000001},
    {"XDMAC_CIM_CH9"                        , 0x000000aa, 0x00000001, 0x00000001},
    {"XDMAC_CIS_CH9"                        , 0x000000ab, 0x00000001, 0x00000001},
    {"XDMAC_CSA_CH9"                        , 0x000000ac, 0x00000001, 0x00000001},
    {"XDMAC_CDA_CH9"                        , 0x000000ad, 0x00000001, 0x00000001},
    {"XDMAC_CNDA_CH9"                       , 0x000000ae, 0x00000001, 0x00000001},
    {"XDMAC_CNDC_CH9"                       , 0x000000af, 0x00000001, 0x00000001},
    {"XDMAC_CUBC_CH9"                       , 0x000000b0, 0x00000001, 0x00000001},
    {"XDMAC_CBC_CH9"                        , 0x000000b1, 0x00000001, 0x00000001},
    {"XDMAC_CC_CH9"                         , 0x000000b2, 0x00000001, 0x00000001},
    {"XDMAC_CDS_MSP_CH9"                    , 0x000000b3, 0x00000001, 0x00000001},
    {"XDMAC_CSUS_CH9"                       , 0x000000b4, 0x00000001, 0x00000001},
    {"XDMAC_CDUS_CH9"                       , 0x000000b5, 0x00000001, 0x00000001},
    {"XDMAC_CTCS_CH9"                       , 0x000000b6, 0x00000001, 0x00000001},
    {"XDMAC_CIE_CH10"                       , 0x000000b8, 0x00000001, 0x00000001},
    {"XDMAC_CID_CH10"                       , 0x000000b9, 0x00000001, 0x00000001},
    {"XDMAC_CIM_CH10"                       , 0x000000ba, 0x00000001, 0x00000001},
    {"XDMAC_CIS_CH10"                       , 0x000000bb, 0x00000001, 0x00000001},
    {"XDMAC_CSA_CH10"                       , 0x000000bc, 0x00000001, 0x00000001},
    {"XDMAC_CDA_CH10"                       , 0x000000bd, 0x00000001, 0x00000001},
    {"XDMAC_CNDA_CH10"                      , 0x000000be, 0x00000001, 0x00000001},
    {"XDMAC_CNDC_CH10"                      , 0x000000bf, 0x00000001, 0x00000001},
    {"XDMAC_CUBC_CH10"                      , 0x000000c0, 0x00000001, 0x00000001},
    {"XDMAC_CBC_CH10"                       , 0x000000c1, 0x00000001, 0x00000001},
    {"XDMAC_CC_CH10"                        , 0x000000c2, 0x00000001, 0x00000001},
    {"XDMAC_CDS_MSP_CH10"                   , 0x000000c3, 0x00000001, 0x00000001},
    {"XDMAC_CSUS_CH10"                      , 0x000000c4, 0x00000001, 0x00000001},
    {"XDMAC_CDUS_CH10"                      , 0x000000c5, 0x00000001, 0x00000001},
    {"XDMAC_CTCS_CH10"                      , 0x000000c6, 0x00000001, 0x00000001},
    {"XDMAC_CIE_CH11"                       , 0x000000c8, 0x00000001, 0x00000001},
    {"XDMAC_CID_CH11"                       , 0x000000c9, 0x00000001, 0x00000001},
    {"XDMAC_CIM_CH11"                       , 0x000000ca, 0x00000001, 0x00000001},
    {"XDMAC_CIS_CH11"                       , 0x000000cb, 0x00000001, 0x00000001},
    {"XDMAC_CSA_CH11"                       , 0x000000cc, 0x00000001, 0x00000001},
    {"XDMAC_CDA_CH11"                       , 0x000000cd, 0x00000001, 0x00000001},
    {"XDMAC_CNDA_CH11"                      , 0x000000ce, 0x00000001, 0x00000001},
    {"XDMAC_CNDC_CH11"                      , 0x000000cf, 0x00000001, 0x00000001},
    {"XDMAC_CUBC_CH11"                      , 0x000000d0, 0x00000001, 0x00000001},
    {"XDMAC_CBC_CH11"                       , 0x000000d1, 0x00000001, 0x00000001},
    {"XDMAC_CC_CH11"                        , 0x000000d2, 0x00000001, 0x00000001},
    {"XDMAC_CDS_MSP_CH11"                   , 0x000000d3, 0x00000001, 0x00000001},
    {"XDMAC_CSUS_CH11"                      , 0x000000d4, 0x00000001, 0x00000001},
    {"XDMAC_CDUS_CH11"                      , 0x000000d5, 0x00000001, 0x00000001},
    {"XDMAC_CTCS_CH11"                      , 0x000000d6, 0x00000001, 0x00000001},
    {"XDMAC_CIE_CH12"                       , 0x000000d8, 0x00000001, 0x00000001},
    {"XDMAC_CID_CH12"                       , 0x000000d9, 0x00000001, 0x00000001},
    {"XDMAC_CIM_CH12"                       , 0x000000da, 0x00000001, 0x00000001},
    {"XDMAC_CIS_CH12"                       , 0x000000db, 0x00000001, 0x00000001},
    {"XDMAC_CSA_CH12"                       , 0x000000dc, 0x00000001, 0x00000001},
    {"XDMAC_CDA_CH12"                       , 0x000000dd, 0x00000001, 0x00000001},
    {"XDMAC_CNDA_CH12"                      , 0x000000de, 0x00000001, 0x00000001},
    {"XDMAC_CNDC_CH12"                      , 0x000000df, 0x00000001, 0x00000001},
    {"XDMAC_CUBC_CH12"                      , 0x000000e0, 0x00000001, 0x00000001},
    {"XDMAC_CBC_CH12"                       , 0x000000e1, 0x00000001, 0x00000001},
    {"XDMAC_CC_CH12"                        , 0x000000e2, 0x00000001, 0x00000001},
    {"XDMAC_CDS_MSP_CH12"                   , 0x000000e3, 0x00000001, 0x00000001},
    {"XDMAC_CSUS_CH12"                      , 0x000000e4, 0x00000001, 0x00000001},
    {"XDMAC_CDUS_CH12"                      , 0x000000e5, 0x00000001, 0x00000001},
    {"XDMAC_CTCS_CH12"                      , 0x000000e6, 0x00000001, 0x00000001},
    {"XDMAC_CIE_CH13"                       , 0x000000e8, 0x00000001, 0x00000001},
    {"XDMAC_CID_CH13"                       , 0x000000e9, 0x00000001, 0x00000001},
    {"XDMAC_CIM_CH13"                       , 0x000000ea, 0x00000001, 0x00000001},
    {"XDMAC_CIS_CH13"                       , 0x000000eb, 0x00000001, 0x00000001},
    {"XDMAC_CSA_CH13"                       , 0x000000ec, 0x00000001, 0x00000001},
    {"XDMAC_CDA_CH13"                       , 0x000000ed, 0x00000001, 0x00000001},
    {"XDMAC_CNDA_CH13"                      , 0x000000ee, 0x00000001, 0x00000001},
    {"XDMAC_CNDC_CH13"                      , 0x000000ef, 0x00000001, 0x00000001},
    {"XDMAC_CUBC_CH13"                      , 0x000000f0, 0x00000001, 0x00000001},
    {"XDMAC_CBC_CH13"                       , 0x000000f1, 0x00000001, 0x00000001},
    {"XDMAC_CC_CH13"                        , 0x000000f2, 0x00000001, 0x00000001},
    {"XDMAC_CDS_MSP_CH13"                   , 0x000000f3, 0x00000001, 0x00000001},
    {"XDMAC_CSUS_CH13"                      , 0x000000f4, 0x00000001, 0x00000001},
    {"XDMAC_CDUS_CH13"                      , 0x000000f5, 0x00000001, 0x00000001},
    {"XDMAC_CTCS_CH13"                      , 0x000000f6, 0x00000001, 0x00000001},
    {"XDMAC_CIE_CH14"                       , 0x000000f8, 0x00000001, 0x00000001},
    {"XDMAC_CID_CH14"                       , 0x000000f9, 0x00000001, 0x00000001},
    {"XDMAC_CIM_CH14"                       , 0x000000fa, 0x00000001, 0x00000001},
    {"XDMAC_CIS_CH14"                       , 0x000000fb, 0x00000001, 0x00000001},
    {"XDMAC_CSA_CH14"                       , 0x000000fc, 0x00000001, 0x00000001},
    {"XDMAC_CDA_CH14"                       , 0x000000fd, 0x00000001, 0x00000001},
    {"XDMAC_CNDA_CH14"                      , 0x000000fe, 0x00000001, 0x00000001},
    {"XDMAC_CNDC_CH14"                      , 0x000000ff, 0x00000001, 0x00000001},
    {"XDMAC_CUBC_CH14"                      , 0x00000100, 0x00000001, 0x00000001},
    {"XDMAC_CBC_CH14"                       , 0x00000101, 0x00000001, 0x00000001},
    {"XDMAC_CC_CH14"                        , 0x00000102, 0x00000001, 0x00000001},
    {"XDMAC_CDS_MSP_CH14"                   , 0x00000103, 0x00000001, 0x00000001},
    {"XDMAC_CSUS_CH14"                      , 0x00000104, 0x00000001, 0x00000001},
    {"XDMAC_CDUS_CH14"                      , 0x00000105, 0x00000001, 0x00000001},
    {"XDMAC_CTCS_CH14"                      , 0x00000106, 0x00000001, 0x00000001},
    {"XDMAC_CIE_CH15"                       , 0x00000108, 0x00000001, 0x00000001},
    {"XDMAC_CID_CH15"                       , 0x00000109, 0x00000001, 0x00000001},
    {"XDMAC_CIM_CH15"                       , 0x0000010a, 0x00000001, 0x00000001},
    {"XDMAC_CIS_CH15"                       , 0x0000010b, 0x00000001, 0x00000001},
    {"XDMAC_CSA_CH15"                       , 0x0000010c, 0x00000001, 0x00000001},
    {"XDMAC_CDA_CH15"                       , 0x0000010d, 0x00000001, 0x00000001},
    {"XDMAC_CNDA_CH15"                      , 0x0000010e, 0x00000001, 0x00000001},
    {"XDMAC_CNDC_CH15"                      , 0x0000010f, 0x00000001, 0x00000001},
    {"XDMAC_CUBC_CH15"                      , 0x00000110, 0x00000001, 0x00000001},
    {"XDMAC_CBC_CH15"                       , 0x00000111, 0x00000001, 0x00000001},
    {"XDMAC_CC_CH15"                        , 0x00000112, 0x00000001, 0x00000001},
    {"XDMAC_CDS_MSP_CH15"                   , 0x00000113, 0x00000001, 0x00000001},
    {"XDMAC_CSUS_CH15"                      , 0x00000114, 0x00000001, 0x00000001},
    {"XDMAC_CDUS_CH15"                      , 0x00000115, 0x00000001, 0x00000001},
    {"XDMAC_CTCS_CH15"                      , 0x00000116, 0x00000001, 0x00000001},
    {"XDMAC_VERSION"                        , 0x000003ff, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_XDMAC[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"XDMAC_REG"                            , 0x00000000, 0x00000001, 0x00000400, regs_within_XDMAC_XDMAC_REG},
    {NULL, 0, 0, 0, NULL}
};
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
    {"TTI_TUPE_CTRL"                        , 0x00000005, 0x00000001, 0x00000001},
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
    {"TTI_CTRL2"                            , 0x0000000d, 0x00000001, 0x00000001},
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
static const vtss_symreg_reg_t regs_within_AFI_TUPE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TUPE_MISC"                            , 0x00000000, 0x00000001, 0x00000001},
    {"TUPE_ADDR"                            , 0x00000001, 0x00000001, 0x00000001},
    {"TUPE_CRIT1"                           , 0x00000002, 0x00000001, 0x00000001},
    {"TUPE_CRIT2"                           , 0x00000003, 0x00000001, 0x00000001},
    {"TUPE_CRIT3"                           , 0x00000004, 0x00000002, 0x00000001},
    {"TUPE_CMD1"                            , 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_AFI[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"MISC"                                 , 0x0000c146, 0x00000001, 0x00000008, regs_within_AFI_MISC},
    {"FRM_TBL"                              , 0x00008000, 0x00001000, 0x00000004, regs_within_AFI_FRM_TBL},
    {"DTI_TBL"                              , 0x0000c000, 0x00000020, 0x00000008, regs_within_AFI_DTI_TBL},
    {"DTI_MISC"                             , 0x0000c14e, 0x00000020, 0x00000003, regs_within_AFI_DTI_MISC},
    {"TTI_TBL"                              , 0x00000000, 0x00001000, 0x00000008, regs_within_AFI_TTI_TBL},
    {"TTI_TICKS"                            , 0x0000c1ae, 0x00000001, 0x0000000b, regs_within_AFI_TTI_TICKS},
    {"TTI_MISC"                             , 0x0000c1b9, 0x00000001, 0x00000011, regs_within_AFI_TTI_MISC},
    {"PORT_TBL"                             , 0x0000c100, 0x00000023, 0x00000002, regs_within_AFI_PORT_TBL},
    {"TUPE"                                 , 0x0000c1ca, 0x00000001, 0x00000007, regs_within_AFI_TUPE},
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
    {"VSTAX_CTRL"                           , 0x00000012, 0x0000001e, 0x00000001},
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
    {"GLOBAL_CNT_FRM_TYPE_CFG"              , 0x00000000, 0x00000006, 0x00000001},
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
    {"RAM_CTRL"                             , 0x000091c4, 0x00000001, 0x00000001, regs_within_ANA_AC_RAM_CTRL},
#ifndef VTSS_RELEASE
    {"COREMEM"                              , 0x000091c5, 0x00000001, 0x00000004, regs_within_ANA_AC_COREMEM},
#endif
    {"PS_COMMON"                            , 0x0000c520, 0x00000001, 0x00000058, regs_within_ANA_AC_PS_COMMON},
    {"MIRROR_PROBE"                         , 0x0000c578, 0x00000003, 0x00000008, regs_within_ANA_AC_MIRROR_PROBE},
    {"AGGR"                                 , 0x0000c480, 0x00000010, 0x00000004, regs_within_ANA_AC_AGGR},
    {"SRC"                                  , 0x00009180, 0x00000043, 0x00000001, regs_within_ANA_AC_SRC},
    {"SFLOW"                                , 0x0000c4c0, 0x0000001e, 0x00000002, regs_within_ANA_AC_SFLOW},
    {"UPSID"                                , 0x00009080, 0x00000020, 0x00000004, regs_within_ANA_AC_UPSID},
    {"GLAG"                                 , 0x000091e0, 0x00000020, 0x00000001, regs_within_ANA_AC_GLAG},
    {"PGID"                                 , 0x00008000, 0x0000041e, 0x00000004, regs_within_ANA_AC_PGID},
    {"CSD"                                  , 0x00000000, 0x00001000, 0x00000004, regs_within_ANA_AC_CSD},
    {"LAG_RST"                              , 0x0000c460, 0x00000008, 0x00000004, regs_within_ANA_AC_LAG_RST},
    {"PS_STICKY"                            , 0x000091c9, 0x00000001, 0x00000001, regs_within_ANA_AC_PS_STICKY},
    {"PS_STICKY_MASK"                       , 0x0000c590, 0x00000004, 0x00000010, regs_within_ANA_AC_PS_STICKY_MASK},
    {"FRER_GEN"                             , 0x00009400, 0x00000400, 0x00000001, regs_within_ANA_AC_FRER_GEN},
#ifndef VTSS_RELEASE
    {"FRER_GEN_STATE_ACC"                   , 0x000091ca, 0x00000001, 0x00000001, regs_within_ANA_AC_FRER_GEN_STATE_ACC},
#endif
#ifndef VTSS_RELEASE
    {"FRER_GEN_STATE"                       , 0x000091c3, 0x00000001, 0x00000001, regs_within_ANA_AC_FRER_GEN_STATE},
#endif
    {"TSN_SF"                               , 0x000091cb, 0x00000001, 0x00000001, regs_within_ANA_AC_TSN_SF},
    {"TSN_SF_CFG"                           , 0x0000c800, 0x00000400, 0x00000001, regs_within_ANA_AC_TSN_SF_CFG},
#ifndef VTSS_RELEASE
    {"TSN_SF_STATUS"                        , 0x00009078, 0x00000001, 0x00000004, regs_within_ANA_AC_TSN_SF_STATUS},
#endif
    {"SG_ACCESS"                            , 0x000091cc, 0x00000001, 0x00000003, regs_within_ANA_AC_SG_ACCESS},
    {"SG_CONFIG"                            , 0x0000c500, 0x00000001, 0x00000020, regs_within_ANA_AC_SG_CONFIG},
    {"SG_STATUS"                            , 0x0000907c, 0x00000001, 0x00000004, regs_within_ANA_AC_SG_STATUS},
    {"SG_STATUS_STICKY"                     , 0x000091cf, 0x00000001, 0x00000001, regs_within_ANA_AC_SG_STATUS_STICKY},
    {"STAT_GLOBAL_CFG_PORT"                 , 0x000091d0, 0x00000001, 0x00000005, regs_within_ANA_AC_STAT_GLOBAL_CFG_PORT},
    {"STAT_CNT_CFG_PORT"                    , 0x0000cc00, 0x00000023, 0x00000010, regs_within_ANA_AC_STAT_CNT_CFG_PORT},
    {"STAT_GLOBAL_CFG_ACL"                  , 0x000091d5, 0x00000001, 0x00000006, regs_within_ANA_AC_STAT_GLOBAL_CFG_ACL},
    {"STAT_CNT_CFG_ACL"                     , 0x00009100, 0x00000020, 0x00000004, regs_within_ANA_AC_STAT_CNT_CFG_ACL},
    {"STAT_GLOBAL_CFG_QUEUE"                , 0x0000c5d0, 0x00000001, 0x00000006, regs_within_ANA_AC_STAT_GLOBAL_CFG_QUEUE},
    {"STAT_CNT_CFG_QUEUE"                   , 0x0000c000, 0x00000118, 0x00000004, regs_within_ANA_AC_STAT_CNT_CFG_QUEUE},
    {"STAT_GLOBAL_CFG_ISDX"                 , 0x0000c5d6, 0x00000001, 0x00000012, regs_within_ANA_AC_STAT_GLOBAL_CFG_ISDX},
    {"STAT_CNT_CFG_ISDX"                    , 0x00004000, 0x00000400, 0x00000010, regs_within_ANA_AC_STAT_CNT_CFG_ISDX},
    {"STAT_GLOBAL_CFG_BDLB"                 , 0x0000c5e8, 0x00000001, 0x00000006, regs_within_ANA_AC_STAT_GLOBAL_CFG_BDLB},
    {"STAT_CNT_CFG_BDLB"                    , 0x00009200, 0x00000080, 0x00000004, regs_within_ANA_AC_STAT_CNT_CFG_BDLB},
    {"STAT_GLOBAL_CFG_BUM"                  , 0x0000c5ee, 0x00000001, 0x00000012, regs_within_ANA_AC_STAT_GLOBAL_CFG_BUM},
    {"STAT_CNT_CFG_BUM"                     , 0x00009800, 0x00000080, 0x00000010, regs_within_ANA_AC_STAT_CNT_CFG_BUM},
    {"STAT_GLOBAL_CFG_IRLEG"                , 0x0000c600, 0x00000001, 0x00000018, regs_within_ANA_AC_STAT_GLOBAL_CFG_IRLEG},
    {"STAT_CNT_CFG_IRLEG"                   , 0x0000a000, 0x00000100, 0x00000010, regs_within_ANA_AC_STAT_CNT_CFG_IRLEG},
    {"STAT_GLOBAL_CFG_ERLEG"                , 0x0000c618, 0x00000001, 0x00000018, regs_within_ANA_AC_STAT_GLOBAL_CFG_ERLEG},
    {"STAT_CNT_CFG_ERLEG"                   , 0x0000b000, 0x00000100, 0x00000010, regs_within_ANA_AC_STAT_CNT_CFG_ERLEG},
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
    {"DM_PTP_DOMAIN_CFG"                    , 0x00000000, 0x0000001e, 0x00000001},
    {"PTP_NTP_OFFSET_CFG"                   , 0x00000041, 0x00000003, 0x00000001},
    {"RD_LAST_PORT_LM_CNT_LSB"              , 0x00000044, 0x00000001, 0x00000001},
    {"RD_LAST_PORT_FRM_CNT_LSB"             , 0x00000045, 0x00000001, 0x00000001},
    {"RD_LAST_PORT_BYTE_CNT_MSB"            , 0x00000046, 0x00000001, 0x00000001},
    {"RD_LAST_PORT_BYTE_CNT_LSB"            , 0x00000047, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_ANA_AC_OAM_MOD[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"VOE_SRV_LM_CNT"                       , 0x00000800, 0x00000100, 0x00000001, regs_within_ANA_AC_OAM_MOD_VOE_SRV_LM_CNT},
    {"VOE_PORT_LM_CNT"                      , 0x00000400, 0x000000f0, 0x00000004, regs_within_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT},
#ifndef VTSS_RELEASE
    {"OAM_PDU_MOD_CONT"                     , 0x00000000, 0x0000007d, 0x00000008, regs_within_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT},
#endif
    {"PDU_MOD_CFG"                          , 0x00000900, 0x00000001, 0x00000048, regs_within_ANA_AC_OAM_MOD_PDU_MOD_CFG},
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
    {"POL_PORT_FC_CFG"                      , 0x000000d8, 0x00000023, 0x00000001},
    {"POL_ALL_CFG"                          , 0x0000011e, 0x00000001, 0x00000001},
    {"POL_UPD_INT_CFG"                      , 0x0000011f, 0x00000001, 0x00000001},
    {"POL_STICKY"                           , 0x00000120, 0x00000001, 0x00000001},
    {"POL_STICKY1"                          , 0x00000121, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ANA_AC_POL_POL_PORT_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"POL_PORT_THRES_CFG_0"                 , 0x00000000, 0x0000008c, 0x00000001},
    {"POL_PORT_THRES_CFG_1"                 , 0x00000200, 0x0000008c, 0x00000001},
    {"POL_PORT_RATE_CFG"                    , 0x00000400, 0x0000008c, 0x00000001},
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
    {"POL_ALL_CFG"                          , 0x00001118, 0x00000001, 0x00000122, regs_within_ANA_AC_POL_POL_ALL_CFG},
    {"POL_PORT_CFG"                         , 0x00000000, 0x00000001, 0x00000800, regs_within_ANA_AC_POL_POL_PORT_CFG},
    {"POL_PORT_CTRL"                        , 0x00001000, 0x00000023, 0x00000008, regs_within_ANA_AC_POL_POL_PORT_CTRL},
    {"PORT_PT_CTRL"                         , 0x0000123a, 0x00000028, 0x00000005, regs_within_ANA_AC_POL_PORT_PT_CTRL},
    {"COMMON_BDLB"                          , 0x00001302, 0x00000001, 0x00000002, regs_within_ANA_AC_POL_COMMON_BDLB},
    {"BDLB"                                 , 0x00000800, 0x00000080, 0x00000008, regs_within_ANA_AC_POL_BDLB},
    {"COMMON_BUM_SLB"                       , 0x00001304, 0x00000001, 0x00000005, regs_within_ANA_AC_POL_COMMON_BUM_SLB},
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
    {"MISC"                                 , 0x00004f00, 0x00000001, 0x0000000b, regs_within_ANA_AC_SDLB_MISC},
    {"LBGRP_TBL"                            , 0x00004f0b, 0x00000008, 0x00000006, regs_within_ANA_AC_SDLB_LBGRP_TBL},
    {"LBSET_TBL"                            , 0x00000000, 0x000004f0, 0x00000010, regs_within_ANA_AC_SDLB_LBSET_TBL},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_ANA_ACL_COMMON[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VCAP_S2_CFG"                          , 0x00000000, 0x00000023, 0x00000001},
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
    {"PORT"                                 , 0x00000894, 0x00000023, 0x00000003, regs_within_ANA_ACL_PORT},
    {"KEY_SEL"                              , 0x000008fd, 0x00000063, 0x00000004, regs_within_ANA_ACL_KEY_SEL},
    {"CNT_A"                                , 0x00000000, 0x00000400, 0x00000001, regs_within_ANA_ACL_CNT_A},
    {"CNT_B"                                , 0x00000400, 0x00000400, 0x00000001, regs_within_ANA_ACL_CNT_B},
    {"PTP_MASTER_CFG"                       , 0x00000a89, 0x00000004, 0x00000004, regs_within_ANA_ACL_PTP_MASTER_CFG},
    {"STICKY"                               , 0x00000a99, 0x00000001, 0x00000004, regs_within_ANA_ACL_STICKY},
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
    {"PORT"                                 , 0x00004000, 0x00000023, 0x00000080, regs_within_ANA_CL_PORT},
    {"COMMON"                               , 0x00005500, 0x00000001, 0x000000bd, regs_within_ANA_CL_COMMON},
    {"MPLS_PROFILE"                         , 0x00005180, 0x00000012, 0x00000001, regs_within_ANA_CL_MPLS_PROFILE},
    {"MIP_TBL"                              , 0x00005400, 0x00000020, 0x00000008, regs_within_ANA_CL_MIP_TBL},
    {"L2CP_TBL"                             , 0x00007000, 0x000005c0, 0x00000001, regs_within_ANA_CL_L2CP_TBL},
    {"MAP_TBL"                              , 0x00005800, 0x00000080, 0x00000010, regs_within_ANA_CL_MAP_TBL},
    {"IPT"                                  , 0x00006000, 0x00000400, 0x00000004, regs_within_ANA_CL_IPT},
    {"PPT"                                  , 0x00005192, 0x00000001, 0x00000010, regs_within_ANA_CL_PPT},
    {"VMID"                                 , 0x00005200, 0x0000007f, 0x00000004, regs_within_ANA_CL_VMID},
    {"CSC"                                  , 0x00000000, 0x00001000, 0x00000004, regs_within_ANA_CL_CSC},
    {"STICKY"                               , 0x000051a2, 0x00000001, 0x0000000c, regs_within_ANA_CL_STICKY},
    {"STICKY_MASK"                          , 0x000051ae, 0x00000004, 0x0000000a, regs_within_ANA_CL_STICKY_MASK},
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
    {"PORT_DLB_CFG"                         , 0x00000012, 0x0000001e, 0x00000001},
    {"PORT_ISDX_LIMIT_CFG"                  , 0x00000053, 0x0000001e, 0x00000001},
    {"SCAN_FID_CTRL"                        , 0x00000094, 0x00000001, 0x00000001},
    {"SCAN_FID_CFG"                         , 0x00000095, 0x00000010, 0x00000001},
    {"MOVELOG_STICKY"                       , 0x000000a5, 0x00000001, 0x00000001},
    {"OWN_UPSID"                            , 0x000000a8, 0x00000001, 0x00000001},
    {"VSTAX_CTRL"                           , 0x000000ab, 0x00000001, 0x00000001},
    {"INTR"                                 , 0x000000ac, 0x00000001, 0x00000001},
    {"INTR_ENA"                             , 0x000000ad, 0x00000001, 0x00000001},
    {"INTR_IDENT"                           , 0x000000ae, 0x00000001, 0x00000001},
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
    {"COMMON"                               , 0x000228c2, 0x00000001, 0x000000af, regs_within_ANA_L2_COMMON},
    {"LRN_LIMIT"                            , 0x00020000, 0x00001400, 0x00000002, regs_within_ANA_L2_LRN_LIMIT},
    {"ISDX_LIMIT"                           , 0x00023000, 0x00000100, 0x00000002, regs_within_ANA_L2_ISDX_LIMIT},
    {"PORT_LIMIT"                           , 0x00022800, 0x0000003e, 0x00000002, regs_within_ANA_L2_PORT_LIMIT},
    {"ISDX"                                 , 0x00000000, 0x00000400, 0x00000020, regs_within_ANA_L2_ISDX},
    {"STICKY"                               , 0x00022971, 0x00000001, 0x00000001, regs_within_ANA_L2_STICKY},
    {"STICKY_MASK"                          , 0x00022972, 0x00000004, 0x00000001, regs_within_ANA_L2_STICKY_MASK},
    {"PMAC"                                 , 0x00022976, 0x00000001, 0x00000009, regs_within_ANA_L2_PMAC},
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
    {"COMMON"                               , 0x0001aa10, 0x00000001, 0x0000002e, regs_within_ANA_L3_COMMON},
    {"VLAN"                                 , 0x00000000, 0x00001400, 0x00000010, regs_within_ANA_L3_VLAN},
    {"MSTP"                                 , 0x0001a800, 0x00000042, 0x00000008, regs_within_ANA_L3_MSTP},
    {"VMID"                                 , 0x0001a000, 0x0000007f, 0x00000010, regs_within_ANA_L3_VMID},
    {"ARP_PTR_REMAP"                        , 0x0001aa40, 0x00000040, 0x00000001, regs_within_ANA_L3_ARP_PTR_REMAP},
    {"ARP"                                  , 0x00014000, 0x00000800, 0x00000008, regs_within_ANA_L3_ARP},
    {"L3MC"                                 , 0x00018000, 0x00000400, 0x00000008, regs_within_ANA_L3_L3MC},
    {"LPM_REMAP_STICKY"                     , 0x0001a7f0, 0x00000001, 0x00000001, regs_within_ANA_L3_LPM_REMAP_STICKY},
    {"VLAN_ARP_L3MC_STICKY"                 , 0x0001a7f1, 0x00000001, 0x00000002, regs_within_ANA_L3_VLAN_ARP_L3MC_STICKY},
    {"L3_STICKY_MASK"                       , 0x0001aa80, 0x00000004, 0x00000004, regs_within_ANA_L3_L3_STICKY_MASK},
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
    {"MAC_ADDR_HIGH_CFG"                    , 0x00000001, 0x00000020, 0x00000001},
    {"MAC_ADDR_LOW_CFG"                     , 0x00000021, 0x00000020, 0x00000001},
    {"PORT_CFG"                             , 0x00000041, 0x00000020, 0x00000001},
    {"CPU_FC_CFG"                           , 0x00000061, 0x00000001, 0x00000001},
    {"PAUSE_CFG"                            , 0x00000062, 0x00000020, 0x00000001},
    {"INJ_VLAN_CFG"                         , 0x00000082, 0x00000001, 0x00000001},
    {"TIME_TICK_CFG"                        , 0x00000083, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ASM_DBG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DBG_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
    {"ERR_STICKY"                           , 0x00000001, 0x00000006, 0x00000001},
    {"PRE_CNT_OFLW_STICKY"                  , 0x00000007, 0x00000001, 0x00000001},
    {"CELLBUF_STAT"                         , 0x00000008, 0x00000006, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ASM_PORT_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PORT_STICKY"                          , 0x00000000, 0x00000020, 0x00000001},
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
    {"LBK_FIFO_CFG"                         , 0x00000003, 0x00000004, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_ASM_LBK_STAT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LBK_OVFLW_STICKY"                     , 0x00000000, 0x00000003, 0x00000001},
    {"LBK_AGING_STICKY"                     , 0x00000003, 0x00000003, 0x00000001},
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
    {"DEV_STATISTICS"                       , 0x00000000, 0x0000001e, 0x00000080, regs_within_ASM_DEV_STATISTICS},
    {"CFG"                                  , 0x00000f00, 0x00000001, 0x00000084, regs_within_ASM_CFG},
#ifndef VTSS_RELEASE
    {"DBG"                                  , 0x00000f84, 0x00000001, 0x0000000e, regs_within_ASM_DBG},
#endif
    {"PORT_STATUS"                          , 0x00000f92, 0x00000001, 0x00000020, regs_within_ASM_PORT_STATUS},
    {"PFC"                                  , 0x00001000, 0x0000001e, 0x00000010, regs_within_ASM_PFC},
    {"PFC_TIMER_CFG"                        , 0x00000fb2, 0x00000001, 0x00000007, regs_within_ASM_PFC_TIMER_CFG},
    {"LBK_WM_CFG"                           , 0x00000fb9, 0x00000001, 0x00000003, regs_within_ASM_LBK_WM_CFG},
    {"LBK_MISC_CFG"                         , 0x00000fbc, 0x00000001, 0x00000007, regs_within_ASM_LBK_MISC_CFG},
    {"LBK_STAT"                             , 0x00000fc3, 0x00000001, 0x00000006, regs_within_ASM_LBK_STAT},
    {"RAM_CTRL"                             , 0x00000fc9, 0x00000001, 0x00000001, regs_within_ASM_RAM_CTRL},
#ifndef VTSS_RELEASE
    {"COREMEM"                              , 0x00000fca, 0x00000001, 0x00000004, regs_within_ASM_COREMEM},
#endif
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_CHIP_TOP_OTP_MEM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"OTP_CFG"                              , 0x00000000, 0x00000001, 0x00000001},
    {"OTP_RCR"                              , 0x00000001, 0x00000003, 0x00000001},
    {"OTP_MSC"                              , 0x00000004, 0x00000004, 0x00000001},
    {"OTP_ID"                               , 0x00000008, 0x00000001, 0x00000001},
    {"OTP_RND"                              , 0x00000009, 0x00000008, 0x00000001},
    {"OTP_PRD"                              , 0x00000011, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_CHIP_TOP[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"OTP_MEM"                              , 0x00000000, 0x00000001, 0x00000019, regs_within_CHIP_TOP_OTP_MEM},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_CLKGEN_AOUT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AOUT_CFG"                             , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CLKGEN_HSIO_CLKTREE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"HSIO_CLKTREE_CFG"                     , 0x00000000, 0x00000001, 0x00000001},
    {"HSIO_CLKTREE_STATUS"                  , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_CLKGEN_LCPLL1[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LCPLL1_CORE_CLK_CFG"                  , 0x00000000, 0x00000001, 0x00000001},
    {"LCPLL1_DDR_CLK_CFG"                   , 0x00000001, 0x00000001, 0x00000001},
    {"LCPLL1_CPU2_CLK_CFG"                  , 0x00000002, 0x00000001, 0x00000001},
    {"LCPLL1_ARM2_CLK_CFG"                  , 0x00000003, 0x00000001, 0x00000001},
    {"LCPLL1_AUX1_CLK_CFG"                  , 0x00000004, 0x00000001, 0x00000001},
    {"LCPLL1_AUX2_CLK_CFG"                  , 0x00000005, 0x00000001, 0x00000001},
    {"LCPLL1_AUX3_CLK_CFG"                  , 0x00000006, 0x00000001, 0x00000001},
    {"LCPLL1_AUX4_CLK_CFG"                  , 0x00000007, 0x00000001, 0x00000001},
    {"LCPLL1_SYNCE_CFG"                     , 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_CLKGEN[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"AOUT"                                 , 0x00000000, 0x00000001, 0x00000001, regs_within_CLKGEN_AOUT},
    {"HSIO_CLKTREE"                         , 0x00000001, 0x00000001, 0x00000002, regs_within_CLKGEN_HSIO_CLKTREE},
    {"LCPLL1"                               , 0x00000003, 0x00000001, 0x00000009, regs_within_CLKGEN_LCPLL1},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEV1G_DEV_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"DEV_RST_CTRL"                         , 0x00000000, 0x00000001, 0x00000001},
    {"DEV_STICKY"                           , 0x00000001, 0x00000001, 0x00000001},
    {"DEV_DBG_CFG"                          , 0x00000002, 0x00000001, 0x00000001},
    {"DEV_PORT_PROTECT"                     , 0x00000003, 0x00000001, 0x00000001},
    {"DEV_LB_CFG"                           , 0x00000004, 0x00000001, 0x00000001},
    {"USXGMII_TX_RADAPT_CFG"                , 0x00000005, 0x00000001, 0x00000001},
    {"USXGMII_GMII_XGMII_MAP_CFG"           , 0x00000006, 0x00000001, 0x00000001},
    {"USXGMII_RX_RADAPT_CFG"                , 0x00000007, 0x00000001, 0x00000001},
    {"EEE_CFG"                              , 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEV1G_USXGMII_ANEG_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"USXGMII_ANEG_CFG"                     , 0x00000000, 0x00000001, 0x00000001},
    {"USXGMII_ANEG_STATUS"                  , 0x00000001, 0x00000001, 0x00000001},
    {"USXGMII_PCS_SD_CFG"                   , 0x00000002, 0x00000001, 0x00000001},
    {"USXGMII_PCS_STATUS"                   , 0x00000003, 0x00000001, 0x00000001},
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
    {"PTP_PREDICT_CFG"                      , 0x00000003, 0x00000001, 0x00000001},
    {"PTP_EVENTS"                           , 0x00000004, 0x00000001, 0x00000001},
    {"DEV_TX_CFG"                           , 0x00000005, 0x00000001, 0x00000001},
    {"DEV_PFRAME_CFG"                       , 0x00000006, 0x00000001, 0x00000001},
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
static const vtss_symreg_reg_t regs_within_DEV1G_DEV2G5U_INTR_CFG_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INTR"                                 , 0x00000000, 0x00000001, 0x00000001},
    {"INTR_ENA"                             , 0x00000001, 0x00000001, 0x00000001},
    {"INTR_IDENT"                           , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEV1G[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEV_CFG_STATUS"                       , 0x00000000, 0x00000001, 0x00000009, regs_within_DEV1G_DEV_CFG_STATUS},
    {"USXGMII_ANEG_CFG_STATUS"              , 0x00000009, 0x00000001, 0x00000004, regs_within_DEV1G_USXGMII_ANEG_CFG_STATUS},
    {"MAC_CFG_STATUS"                       , 0x0000000d, 0x00000001, 0x00000009, regs_within_DEV1G_MAC_CFG_STATUS},
    {"PCS1G_CFG_STATUS"                     , 0x00000016, 0x00000001, 0x00000011, regs_within_DEV1G_PCS1G_CFG_STATUS},
    {"PCS1G_TSTPAT_CFG_STATUS"              , 0x00000027, 0x00000001, 0x00000002, regs_within_DEV1G_PCS1G_TSTPAT_CFG_STATUS},
    {"PCS_FX100_CONFIGURATION"              , 0x00000029, 0x00000001, 0x00000001, regs_within_DEV1G_PCS_FX100_CONFIGURATION},
    {"PCS_FX100_STATUS"                     , 0x0000002a, 0x00000001, 0x00000001, regs_within_DEV1G_PCS_FX100_STATUS},
    {"PTP_CFG_STATUS"                       , 0x0000002b, 0x00000001, 0x00000007, regs_within_DEV1G_PTP_CFG_STATUS},
    {"PHASE_DETECTOR_CTRL"                  , 0x00000032, 0x00000002, 0x00000003, regs_within_DEV1G_PHASE_DETECTOR_CTRL},
    {"MM_CONFIG"                            , 0x00000038, 0x00000001, 0x00000002, regs_within_DEV1G_MM_CONFIG},
    {"MM_STATISTICS"                        , 0x0000003a, 0x00000001, 0x00000001, regs_within_DEV1G_MM_STATISTICS},
    {"DEV2G5_INTR_CFG_STATUS"               , 0x0000003b, 0x00000001, 0x00000003, regs_within_DEV1G_DEV2G5_INTR_CFG_STATUS},
    {"DEV2G5U_INTR_CFG_STATUS"              , 0x0000003e, 0x00000001, 0x00000003, regs_within_DEV1G_DEV2G5U_INTR_CFG_STATUS},
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
    {"PTP_PREDICT_CFG"                      , 0x00000003, 0x00000001, 0x00000001},
    {"PTP_EVENTS"                           , 0x00000004, 0x00000001, 0x00000001},
    {"DEV_TX_CFG"                           , 0x00000005, 0x00000001, 0x00000001},
    {"DEV_PFRAME_CFG"                       , 0x00000006, 0x00000001, 0x00000001},
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
    {"PTP_CFG_STATUS"                       , 0x00000089, 0x00000001, 0x00000007, regs_within_DEV10G_PTP_CFG_STATUS},
    {"PHASE_DETECTOR_CTRL"                  , 0x00000090, 0x00000002, 0x00000003, regs_within_DEV10G_PHASE_DETECTOR_CTRL},
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
    {"CHIP_ID"                              , 0x00000000, 0x00000001, 0x00000001},
    {"REVID_RAW"                            , 0x00000001, 0x00000001, 0x00000001},
    {"GPR"                                  , 0x00000002, 0x00000001, 0x00000001},
    {"SOFT_RST"                             , 0x00000003, 0x00000001, 0x00000001},
    {"HW_STAT"                              , 0x00000004, 0x00000001, 0x00000001},
    {"HW_SGPIO_TO_SD_MAP_CFG"               , 0x00000005, 0x0000001e, 0x00000001},
    {"HW_SGPIO_TO_SERDES_SD_MAP_CFG"        , 0x00000023, 0x0000000a, 0x00000001},
    {"BUILDID"                              , 0x0000002d, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_SI_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IF_CTRL"                              , 0x00000000, 0x00000001, 0x00000001},
    {"IF_CFGSTAT"                           , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_SW_REGS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SW_INTR"                              , 0x00000000, 0x00000001, 0x00000001},
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
    {"GPIO_OUT_SET1"                        , 0x00000001, 0x00000001, 0x00000001},
    {"GPIO_OUT_SET2"                        , 0x00000002, 0x00000001, 0x00000001},
    {"GPIO_OUT_CLR"                         , 0x00000003, 0x00000001, 0x00000001},
    {"GPIO_OUT_CLR1"                        , 0x00000004, 0x00000001, 0x00000001},
    {"GPIO_OUT_CLR2"                        , 0x00000005, 0x00000001, 0x00000001},
    {"GPIO_OUT"                             , 0x00000006, 0x00000001, 0x00000001},
    {"GPIO_OUT1"                            , 0x00000007, 0x00000001, 0x00000001},
    {"GPIO_OUT2"                            , 0x00000008, 0x00000001, 0x00000001},
    {"GPIO_IN"                              , 0x00000009, 0x00000001, 0x00000001},
    {"GPIO_IN1"                             , 0x0000000a, 0x00000001, 0x00000001},
    {"GPIO_IN2"                             , 0x0000000b, 0x00000001, 0x00000001},
    {"GPIO_OE"                              , 0x0000000c, 0x00000001, 0x00000001},
    {"GPIO_OE1"                             , 0x0000000d, 0x00000001, 0x00000001},
    {"GPIO_OE2"                             , 0x0000000e, 0x00000001, 0x00000001},
    {"GPIO_INTR"                            , 0x0000000f, 0x00000001, 0x00000001},
    {"GPIO_INTR1"                           , 0x00000010, 0x00000001, 0x00000001},
    {"GPIO_INTR2"                           , 0x00000011, 0x00000001, 0x00000001},
    {"GPIO_INTR_ENA"                        , 0x00000012, 0x00000001, 0x00000001},
    {"GPIO_INTR_ENA1"                       , 0x00000013, 0x00000001, 0x00000001},
    {"GPIO_INTR_ENA2"                       , 0x00000014, 0x00000001, 0x00000001},
    {"GPIO_INTR_IDENT"                      , 0x00000015, 0x00000001, 0x00000001},
    {"GPIO_INTR_IDENT1"                     , 0x00000016, 0x00000001, 0x00000001},
    {"GPIO_INTR_IDENT2"                     , 0x00000017, 0x00000001, 0x00000001},
    {"GPIO_ALT"                             , 0x00000018, 0x00000003, 0x00000001},
    {"GPIO_ALT1"                            , 0x0000001b, 0x00000003, 0x00000001},
    {"GPIO_ALT2"                            , 0x0000001e, 0x00000003, 0x00000001},
    {"GPIO_SD_DEV_MAP"                      , 0x00000021, 0x00000006, 0x00000001},
    {"GPIO_SD_SERDES_MAP"                   , 0x00000027, 0x00000006, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_MIIM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MII_STATUS"                           , 0x00000000, 0x00000001, 0x00000001},
    {"MII_CFG_7226"                         , 0x00000001, 0x00000001, 0x00000001},
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
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_FLEXCOM_SHARED[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SS_MASK"                              , 0x00000000, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_ROSC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"ROSC_CFG"                             , 0x00000000, 0x00000005, 0x00000001},
    {"ROSC_MEASURE_CFG"                     , 0x00000005, 0x00000001, 0x00000001},
    {"ROSC_FREQ_CNT"                        , 0x00000006, 0x00000001, 0x00000001},
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
    {"SIO_INTR_ENA"                         , 0x0000003e, 0x00000004, 0x00000001},
    {"SIO_INTR_IDENT"                       , 0x00000042, 0x00000004, 0x00000001},
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
    {"MEMITGR_DBG"                          , 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_GCB_VRAP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"VRAP_ACCESS_STAT"                     , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEVCPU_GCB[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"CHIP_REGS"                            , 0x00000000, 0x00000001, 0x0000002e, regs_within_DEVCPU_GCB_CHIP_REGS},
    {"SI_REGS"                              , 0x0000002e, 0x00000001, 0x00000002, regs_within_DEVCPU_GCB_SI_REGS},
#ifndef VTSS_RELEASE
    {"SW_REGS"                              , 0x00000030, 0x00000001, 0x00000001, regs_within_DEVCPU_GCB_SW_REGS},
#endif
    {"VCORE_ACCESS"                         , 0x00000031, 0x00000001, 0x00000005, regs_within_DEVCPU_GCB_VCORE_ACCESS},
    {"GPIO"                                 , 0x00000036, 0x00000001, 0x0000002d, regs_within_DEVCPU_GCB_GPIO},
    {"MIIM"                                 , 0x00000063, 0x00000002, 0x00000009, regs_within_DEVCPU_GCB_MIIM},
    {"MIIM_READ_SCAN"                       , 0x00000075, 0x00000001, 0x00000002, regs_within_DEVCPU_GCB_MIIM_READ_SCAN},
    {"FLEXCOM_SHARED"                       , 0x00000077, 0x00000005, 0x00000002, regs_within_DEVCPU_GCB_FLEXCOM_SHARED},
#ifndef VTSS_RELEASE
    {"ROSC"                                 , 0x00000081, 0x00000001, 0x00000007, regs_within_DEVCPU_GCB_ROSC},
#endif
    {"SIO_CTRL"                             , 0x00000088, 0x00000001, 0x00000046, regs_within_DEVCPU_GCB_SIO_CTRL},
    {"FAN_CTRL"                             , 0x000000ce, 0x00000001, 0x00000003, regs_within_DEVCPU_GCB_FAN_CTRL},
    {"MEMITGR"                              , 0x000000d1, 0x00000001, 0x00000006, regs_within_DEVCPU_GCB_MEMITGR},
    {"VRAP"                                 , 0x000000d7, 0x00000001, 0x00000001, regs_within_DEVCPU_GCB_VRAP},
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
    {"SEMA"                                 , 0x0000000a, 0x00000008, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DEVCPU_ORG[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"DEVCPU_ORG"                           , 0x00000000, 0x00000001, 0x00000012, regs_within_DEVCPU_ORG_DEVCPU_ORG},
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
    {"PTP_CFG"                              , 0x00000050, 0x00000001, 0x00000004, regs_within_PTP_PTP_CFG},
    {"PTP_TOD_DOMAINS"                      , 0x00000054, 0x00000003, 0x00000007, regs_within_PTP_PTP_TOD_DOMAINS},
    {"PTP_PINS"                             , 0x00000000, 0x00000005, 0x00000010, regs_within_PTP_PTP_PINS},
    {"PTP_TS_FIFO"                          , 0x00000069, 0x00000001, 0x00000004, regs_within_PTP_PTP_TS_FIFO},
    {"PHASE_DETECTOR_CTRL"                  , 0x0000006d, 0x00000005, 0x00000003, regs_within_PTP_PHASE_DETECTOR_CTRL},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_QS_XTR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"XTR_GRP_CFG"                          , 0x00000000, 0x00000002, 0x00000001},
    {"XTR_RD"                               , 0x00000002, 0x00000002, 0x00000001},
    {"XTR_FRM_PRUNING"                      , 0x00000004, 0x00000002, 0x00000001},
    {"XTR_FLUSH"                            , 0x00000006, 0x00000001, 0x00000001},
    {"XTR_DATA_PRESENT"                     , 0x00000007, 0x00000001, 0x00000001},
    {"XTR_CFG"                              , 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DEVCPU_QS_INJ[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"INJ_GRP_CFG"                          , 0x00000000, 0x00000002, 0x00000001},
    {"INJ_WR"                               , 0x00000002, 0x00000002, 0x00000001},
    {"INJ_CTRL"                             , 0x00000004, 0x00000002, 0x00000001},
    {"INJ_STATUS"                           , 0x00000006, 0x00000001, 0x00000001},
    {"INJ_ERR"                              , 0x00000007, 0x00000002, 0x00000001},
    {"VTSS_DBG"                             , 0x00000009, 0x00000001, 0x00000001},
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
    {"BUF_CFG"                              , 0x00000000, 0x00000020, 0x00000001},
    {"RATE_CTRL"                            , 0x00000020, 0x00000020, 0x00000001},
    {"IPG_SHRINK_CFG"                       , 0x00000040, 0x00000020, 0x00000001},
    {"CLR_BUF"                              , 0x00000060, 0x00000003, 0x00000001},
    {"SCH_STOP_WM_CFG"                      , 0x00000063, 0x00000020, 0x00000001},
    {"TX_START_WM_CFG"                      , 0x00000083, 0x00000020, 0x00000001},
    {"DEV_TX_STOP_WM_CFG"                   , 0x000000a3, 0x00000020, 0x00000001},
    {"RX_PAUSE_CFG"                         , 0x000000c3, 0x00000020, 0x00000001},
    {"ETH_FC_CFG"                           , 0x000000e3, 0x00000020, 0x00000001},
    {"ETH_PFC_CFG"                          , 0x00000103, 0x00000020, 0x00000001},
    {"MAC_CFG"                              , 0x00000123, 0x00000020, 0x00000001},
    {"MAC_ADDR_BASE_HIGH_CFG"               , 0x00000143, 0x0000001e, 0x00000001},
    {"MAC_ADDR_BASE_LOW_CFG"                , 0x00000161, 0x0000001e, 0x00000001},
    {"DBG_CTRL"                             , 0x0000017f, 0x00000001, 0x00000001},
    {"TAXI_CAL_CFG"                         , 0x00000180, 0x00000006, 0x00000001},
    {"PREEMPT_CFG"                          , 0x00000186, 0x00000020, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DSM_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AGED_FRMS"                            , 0x00000000, 0x00000041, 0x00000001},
    {"CELL_BUS_STICKY"                      , 0x00000041, 0x00000001, 0x00000001},
    {"BUF_OFLW_STICKY"                      , 0x00000042, 0x00000003, 0x00000001},
    {"BUF_UFLW_STICKY"                      , 0x00000045, 0x00000003, 0x00000001},
    {"PRE_CNT_OFLW_STICKY"                  , 0x00000048, 0x00000001, 0x00000001},
    {"BUF_MAX_FILL"                         , 0x00000049, 0x00000041, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DSM_RATE_LIMIT_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TX_RATE_LIMIT_MODE"                   , 0x00000000, 0x00000020, 0x00000001},
    {"TX_IPG_STRETCH_RATIO_CFG"             , 0x00000020, 0x00000020, 0x00000001},
    {"TX_FRAME_RATE_START_CFG"              , 0x00000040, 0x00000020, 0x00000001},
    {"TX_RATE_LIMIT_HDR_CFG"                , 0x00000060, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_DSM_RATE_LIMIT_STATUS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TX_RATE_LIMIT_STICKY"                 , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_DSM[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"RAM_CTRL"                             , 0x00000000, 0x00000001, 0x00000001, regs_within_DSM_RAM_CTRL},
#ifndef VTSS_RELEASE
    {"COREMEM"                              , 0x00000001, 0x00000001, 0x00000004, regs_within_DSM_COREMEM},
#endif
    {"CFG"                                  , 0x00000005, 0x00000001, 0x000001a6, regs_within_DSM_CFG},
    {"STATUS"                               , 0x000001ab, 0x00000001, 0x0000008a, regs_within_DSM_STATUS},
    {"RATE_LIMIT_CFG"                       , 0x00000235, 0x00000001, 0x00000061, regs_within_DSM_RATE_LIMIT_CFG},
    {"RATE_LIMIT_STATUS"                    , 0x00000296, 0x00000001, 0x00000001, regs_within_DSM_RATE_LIMIT_STATUS},
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
    {"COMMON"                               , 0x00001f88, 0x00000001, 0x00000036, regs_within_EACL_COMMON},
    {"INTERFACE_MAP"                        , 0x00001800, 0x00000578, 0x00000001, regs_within_EACL_INTERFACE_MAP},
    {"ES2_KEY_SELECT_PROFILE"               , 0x00001f00, 0x00000044, 0x00000002, regs_within_EACL_ES2_KEY_SELECT_PROFILE},
    {"CNT_TBL"                              , 0x00002000, 0x00000400, 0x00000001, regs_within_EACL_CNT_TBL},
    {"POL_CFG"                              , 0x00002880, 0x00000001, 0x000000c3, regs_within_EACL_POL_CFG},
    {"ES2_STICKY"                           , 0x00001d7c, 0x00000001, 0x00000002, regs_within_EACL_ES2_STICKY},
#ifndef VTSS_RELEASE
    {"DBG_STICKY"                           , 0x00001d7e, 0x00000001, 0x00000001, regs_within_EACL_DBG_STICKY},
#endif
    {"FRER_MAP"                             , 0x00000000, 0x00000400, 0x00000004, regs_within_EACL_FRER_MAP},
    {"FRER_CFG"                             , 0x00001d7f, 0x00000001, 0x00000001, regs_within_EACL_FRER_CFG},
    {"FRER_CFG_COMPOUND"                    , 0x00001d80, 0x00000080, 0x00000001, regs_within_EACL_FRER_CFG_COMPOUND},
    {"FRER_CFG_MEMBER"                      , 0x00001e00, 0x00000100, 0x00000001, regs_within_EACL_FRER_CFG_MEMBER},
#ifndef VTSS_RELEASE
    {"FRER_STA_COMPOUND"                    , 0x00001d78, 0x00000001, 0x00000002, regs_within_EACL_FRER_STA_COMPOUND},
#endif
#ifndef VTSS_RELEASE
    {"FRER_STA_MEMBER"                      , 0x00001d7a, 0x00000001, 0x00000002, regs_within_EACL_FRER_STA_MEMBER},
#endif
    {"FRER_CNT_COMPOUND"                    , 0x00002400, 0x00000080, 0x00000008, regs_within_EACL_FRER_CNT_COMPOUND},
    {"FRER_CNT_MEMBER"                      , 0x00001000, 0x00000100, 0x00000008, regs_within_EACL_FRER_CNT_MEMBER},
    {"STAT_GLOBAL_CFG_EACL"                 , 0x00001fbe, 0x00000001, 0x00000006, regs_within_EACL_STAT_GLOBAL_CFG_EACL},
    {"STAT_CNT_CFG_EACL"                    , 0x00002800, 0x00000020, 0x00000004, regs_within_EACL_STAT_CNT_CFG_EACL},
    {"RAM_CTRL"                             , 0x00001fc4, 0x00000001, 0x00000001, regs_within_EACL_RAM_CTRL},
#ifndef VTSS_RELEASE
    {"COREMEM"                              , 0x00001fc5, 0x00000001, 0x00000004, regs_within_EACL_COREMEM},
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
    {"HSCH_MISC_PORT_CFG"                   , 0x00000001, 0x00000023, 0x00000001},
    {"HSCH_CFG_CFG"                         , 0x00000024, 0x00000001, 0x00000001},
    {"PFC_CFG"                              , 0x00000025, 0x0000001e, 0x00000001},
    {"HSCH_LARGE_ENA"                       , 0x00000043, 0x0000000b, 0x00000001},
    {"EVENTS_CORE"                          , 0x0000004e, 0x00000001, 0x00000001},
    {"DEBUG_CTRL"                           , 0x0000004f, 0x00000001, 0x00000001},
    {"HSCH_UPDATE_STAT"                     , 0x00000050, 0x00000001, 0x00000001},
    {"SYS_CLK_PER"                          , 0x00000051, 0x00000001, 0x00000001},
    {"HSCH_FORCE_CTRL"                      , 0x00000052, 0x00000001, 0x00000001},
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
    {"PORT_MODE"                            , 0x00000002, 0x00000023, 0x00000001},
    {"OUTB_SHARE_ENA"                       , 0x00000025, 0x00000005, 0x00000001},
    {"OUTB_CPU_SHARE_ENA"                   , 0x0000002a, 0x00000001, 0x00000001},
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
    {"TAS_CFG_CTRL2"                        , 0x00000002, 0x00000001, 0x00000001},
    {"TAS_STATEMACHINE_CFG"                 , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_TAS_PROFILE_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TAS_QMAXSDU_CFG"                      , 0x00000000, 0x00000008, 0x00000001},
    {"TAS_PROFILE_CONFIG"                   , 0x00000008, 0x00000001, 0x00000001},
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
    {"TAS_LIST_PTR_STATE"                   , 0x0000000a, 0x00000001, 0x00000001},
    {"TAS_LIST_STATE_INT"                   , 0x0000000b, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_TAS_GCL_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TAS_GCL_CTRL_CFG"                     , 0x00000000, 0x00000001, 0x00000001},
    {"TAS_GCL_CTRL_CFG2"                    , 0x00000001, 0x00000001, 0x00000001},
    {"TAS_GCL_TIME_CFG"                     , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSCH_HSCH_TAS_STATE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TAS_GATE_STATE"                       , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_HSCH[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"HSCH_L0_CFG"                          , 0x00005800, 0x00000578, 0x00000001, regs_within_HSCH_HSCH_L0_CFG},
    {"HSCH_L1_CFG"                          , 0x00003b60, 0x00000020, 0x00000001, regs_within_HSCH_HSCH_L1_CFG},
    {"HSCH_CFG"                             , 0x00000000, 0x00000578, 0x00000008, regs_within_HSCH_HSCH_CFG},
    {"HSCH_STATUS"                          , 0x00004000, 0x00000578, 0x00000004, regs_within_HSCH_HSCH_STATUS},
    {"QSHP_CFG"                             , 0x00003b00, 0x00000028, 0x00000002, regs_within_HSCH_QSHP_CFG},
    {"QSHP_ALLOC_CFG"                       , 0x00003000, 0x00000578, 0x00000002, regs_within_HSCH_QSHP_ALLOC_CFG},
    {"QSHP_STATUS"                          , 0x00002bc0, 0x00000028, 0x00000001, regs_within_HSCH_QSHP_STATUS},
    {"HSCH_INP_STATE"                       , 0x00002bec, 0x00000002, 0x00000001, regs_within_HSCH_HSCH_INP_STATE},
    {"HSCH_DWRR"                            , 0x00002fc0, 0x00000028, 0x00000001, regs_within_HSCH_HSCH_DWRR},
    {"HSCH_MISC"                            , 0x00003b80, 0x00000001, 0x00000053, regs_within_HSCH_HSCH_MISC},
    {"HSCH_LEAK_LISTS"                      , 0x00003bd3, 0x00000004, 0x00000008, regs_within_HSCH_HSCH_LEAK_LISTS},
    {"SYSTEM"                               , 0x00003bf3, 0x00000001, 0x0000002b, regs_within_HSCH_SYSTEM},
    {"MMGT"                                 , 0x00002fe8, 0x00000001, 0x00000004, regs_within_HSCH_MMGT},
    {"TAS_CONFIG"                           , 0x00002fec, 0x00000001, 0x00000004, regs_within_HSCH_TAS_CONFIG},
    {"TAS_PROFILE_CFG"                      , 0x00002c00, 0x0000003c, 0x00000010, regs_within_HSCH_TAS_PROFILE_CFG},
    {"TAS_LIST_CFG"                         , 0x00002bf0, 0x00000001, 0x00000010, regs_within_HSCH_TAS_LIST_CFG},
    {"TAS_GCL_CFG"                          , 0x00002be8, 0x00000001, 0x00000004, regs_within_HSCH_TAS_GCL_CFG},
    {"HSCH_TAS_STATE"                       , 0x00002bee, 0x00000001, 0x00000001, regs_within_HSCH_HSCH_TAS_STATE},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_HSIOWRAP_SYNC_ETH_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SYNC_ETH_CFG"                         , 0x00000000, 0x00000004, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSIOWRAP_GPIO_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GPIO_CFG"                             , 0x00000000, 0x0000004e, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_HSIOWRAP_TEMP_SENSOR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TEMP_SENSOR_CTRL"                     , 0x00000000, 0x00000001, 0x00000001},
    {"TEMP_SENSOR_CFG"                      , 0x00000001, 0x00000001, 0x00000001},
    {"TEMP_SENSOR_STAT"                     , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_HSIOWRAP[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"SYNC_ETH_CFG"                         , 0x00000000, 0x00000001, 0x00000004, regs_within_HSIOWRAP_SYNC_ETH_CFG},
    {"GPIO_CFG"                             , 0x00000004, 0x00000001, 0x0000004e, regs_within_HSIOWRAP_GPIO_CFG},
    {"TEMP_SENSOR"                          , 0x00000052, 0x00000001, 0x00000003, regs_within_HSIOWRAP_TEMP_SENSOR},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_LCPLL28_LCPLL28[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LCPLL_CONFIG1"                        , 0x00000000, 0x00000001, 0x00000001},
    {"LCPLL_CONFIG2"                        , 0x00000001, 0x00000001, 0x00000001},
    {"LCPLL_CONFIG3"                        , 0x00000002, 0x00000001, 0x00000001},
    {"LCPLL_CONFIG4"                        , 0x00000003, 0x00000001, 0x00000001},
    {"LCPLL_CONFIG5"                        , 0x00000004, 0x00000001, 0x00000001},
    {"LCPLL_MISC_CONFIG"                    , 0x00000005, 0x00000001, 0x00000001},
    {"LCPLL_STATUS"                         , 0x00000006, 0x00000001, 0x00000001},
    {"LCPLL_MISC_STATUS"                    , 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_LCPLL28[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"LCPLL28"                              , 0x00000000, 0x00000001, 0x00000008, regs_within_LCPLL28_LCPLL28},
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
    {"DEV5G_MODES"                          , 0x00000000, 0x00000001, 0x00000001},
    {"DEV10G_MODES"                         , 0x00000001, 0x00000001, 0x00000001},
    {"QSGMII_ENA"                           , 0x00000002, 0x00000001, 0x00000001},
    {"USXGMII_ENA"                          , 0x00000003, 0x00000001, 0x00000001},
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
    {"HW_CFG"                               , 0x00000000, 0x00000001, 0x00000004, regs_within_PORT_CONF_HW_CFG},
    {"QSGMII_CFG_STAT"                      , 0x00000004, 0x00000006, 0x00000002, regs_within_PORT_CONF_QSGMII_CFG_STAT},
    {"USXGMII_CFG"                          , 0x00000010, 0x0000000a, 0x00000003, regs_within_PORT_CONF_USXGMII_CFG},
    {"USXGMII_STAT"                         , 0x0000002e, 0x0000000a, 0x00000002, regs_within_PORT_CONF_USXGMII_STAT},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_QFWD_SYSTEM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SWITCH_PORT_MODE"                     , 0x00000000, 0x00000023, 0x00000001},
    {"FWD_CTRL"                             , 0x00000023, 0x00000001, 0x00000001},
    {"FRAME_COPY_CFG"                       , 0x00000024, 0x0000000c, 0x00000001},
    {"FWD_PRESS_DROP_CNT"                   , 0x00000030, 0x00000001, 0x00000001},
    {"AFWD_PRESS_DROP_CNT"                  , 0x00000031, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_QFWD[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"SYSTEM"                               , 0x00000000, 0x00000001, 0x00000032, regs_within_QFWD_SYSTEM},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_QRES_RES_WRED[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"WRED_PROFILE"                         , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QRES_RES_QOS_ADV[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"WRED_GROUP"                           , 0x00000000, 0x00000023, 0x00000001},
    {"RES_QOS_MODE"                         , 0x00000023, 0x00000001, 0x00000001},
    {"RES_DLB_OFFSET"                       , 0x00000024, 0x00000001, 0x00000001},
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
    {"RES_QOS_ADV"                          , 0x00005048, 0x00000001, 0x00000025, regs_within_QRES_RES_QOS_ADV},
    {"RES_CTRL"                             , 0x00000000, 0x00001400, 0x00000004, regs_within_QRES_RES_CTRL},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_QSYS_SYSTEM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EEE_CFG"                              , 0x00000000, 0x0000001e, 0x00000001},
    {"EEE_THRES"                            , 0x0000001e, 0x00000001, 0x00000001},
    {"FRM_AGING"                            , 0x0000001f, 0x00000001, 0x00000001},
    {"DP_MAP"                               , 0x00000020, 0x00000001, 0x00000001},
    {"STAT_CFG"                             , 0x00000021, 0x00000001, 0x00000001},
    {"IQUEUE_CFG"                           , 0x00000022, 0x0000001e, 0x00000001},
    {"DBG_UTIL"                             , 0x00000040, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_MISC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"EVENTS_CORE"                          , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_PAUSE_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PAUSE_CFG"                            , 0x00000000, 0x00000023, 0x00000001},
    {"PAUSE_TOT_CFG"                        , 0x00000023, 0x00000001, 0x00000001},
    {"ATOP"                                 , 0x00000024, 0x00000023, 0x00000001},
    {"FWD_PRESSURE"                         , 0x00000047, 0x00000023, 0x00000001},
    {"ATOP_TOT_CFG"                         , 0x0000006a, 0x00000001, 0x00000001},
    {"PFC_CFG"                              , 0x0000006b, 0x00000023, 0x00000001},
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
    {"SOFDATA_STAT"                         , 0x00000001, 0x00000023, 0x00000001},
    {"SOFDATA_CFG"                          , 0x00000024, 0x00000023, 0x00000001},
    {"SOFDATA_WM_VAL"                       , 0x00000047, 0x00000005, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_QSYS_CALCFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CAL_AUTO"                             , 0x00000000, 0x00000004, 0x00000001},
    {"CAL_SEQ"                              , 0x00000004, 0x00000001, 0x00000001},
    {"CAL_SEQ_SEL_CFG"                      , 0x00000005, 0x00000001, 0x00000001},
    {"CAL_CTRL"                             , 0x00000006, 0x00000001, 0x00000001},
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
    {"SYSTEM"                               , 0x00000000, 0x00000001, 0x00000041, regs_within_QSYS_SYSTEM},
#ifndef VTSS_RELEASE
    {"MISC"                                 , 0x00000041, 0x00000001, 0x00000001, regs_within_QSYS_MISC},
#endif
    {"PAUSE_CFG"                            , 0x00000042, 0x00000001, 0x0000008e, regs_within_QSYS_PAUSE_CFG},
    {"MMGT_PORT"                            , 0x000000d0, 0x00000001, 0x0000000c, regs_within_QSYS_MMGT_PORT},
    {"SOFDATA_POOL"                         , 0x000000dc, 0x00000001, 0x0000004c, regs_within_QSYS_SOFDATA_POOL},
    {"CALCFG"                               , 0x00000128, 0x00000001, 0x00000007, regs_within_QSYS_CALCFG},
    {"RAM_CTRL"                             , 0x0000012f, 0x00000001, 0x00000001, regs_within_QSYS_RAM_CTRL},
#ifndef VTSS_RELEASE
    {"COREMEM"                              , 0x00000130, 0x00000001, 0x00000004, regs_within_QSYS_COREMEM},
#endif
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_REW_COMMON[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"OWN_UPSID"                            , 0x00000000, 0x00000001, 0x00000001},
    {"COMMON_CTRL"                          , 0x00000003, 0x00000001, 0x00000001},
    {"IFH_CTRL"                             , 0x00000004, 0x0000001e, 0x00000001},
    {"IFH_CTRL_CPUVD"                       , 0x00000045, 0x00000001, 0x00000001},
    {"PORT_CTRL"                            , 0x00000046, 0x00000023, 0x00000001},
    {"RTAG_ETAG_CTRL"                       , 0x0000008c, 0x00000023, 0x00000001},
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
static const vtss_symreg_reg_t regs_within_REW_PTP_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
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
    {"DM_PTP_DOMAIN_CFG"                    , 0x00000000, 0x0000001e, 0x00000001},
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
static const vtss_symreg_reggrp_t reggrps_within_REW[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"COMMON"                               , 0x00006000, 0x00000001, 0x00000134, regs_within_REW_COMMON},
    {"MAP_RES_A"                            , 0x00004000, 0x00000400, 0x00000002, regs_within_REW_MAP_RES_A},
    {"MAP_RES_B"                            , 0x00004800, 0x00000400, 0x00000002, regs_within_REW_MAP_RES_B},
    {"PORT"                                 , 0x00003000, 0x00000023, 0x00000040, regs_within_REW_PORT},
    {"MIP_TBL"                              , 0x00003900, 0x00000020, 0x00000008, regs_within_REW_MIP_TBL},
    {"MAC_TBL"                              , 0x00003a00, 0x00000080, 0x00000004, regs_within_REW_MAC_TBL},
    {"ISDX_TBL"                             , 0x00002000, 0x00000400, 0x00000004, regs_within_REW_ISDX_TBL},
    {"PTP_CTRL"                             , 0x000038c0, 0x00000001, 0x0000000a, regs_within_REW_PTP_CTRL},
    {"ENCAP"                                , 0x00000000, 0x00000100, 0x00000020, regs_within_REW_ENCAP},
    {"ENCAP_IP4"                            , 0x00005000, 0x00000100, 0x00000008, regs_within_REW_ENCAP_IP4},
    {"VMID"                                 , 0x00005e80, 0x0000007f, 0x00000001, regs_within_REW_VMID},
    {"PTP_SEQ_NO"                           , 0x00003c00, 0x00000001, 0x00000400, regs_within_REW_PTP_SEQ_NO},
    {"VOE_SRV_LM_CNT"                       , 0x00005f00, 0x00000100, 0x00000001, regs_within_REW_VOE_SRV_LM_CNT},
    {"VOE_PORT_LM_CNT"                      , 0x00005800, 0x000000f0, 0x00000004, regs_within_REW_VOE_PORT_LM_CNT},
#ifndef VTSS_RELEASE
    {"OAM_PDU_MOD_CONT"                     , 0x00005c00, 0x00000041, 0x00000008, regs_within_REW_OAM_PDU_MOD_CONT},
#endif
    {"PDU_MOD_CFG"                          , 0x00005e08, 0x00000001, 0x00000048, regs_within_REW_PDU_MOD_CFG},
    {"RAM_CTRL"                             , 0x000038ca, 0x00000001, 0x00000001, regs_within_REW_RAM_CTRL},
#ifndef VTSS_RELEASE
    {"COREMEM"                              , 0x000038cb, 0x00000001, 0x00000004, regs_within_REW_COREMEM},
#endif
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_SD10G_CMU_TARGET_CMU_GRP_0[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CMU_00"                               , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G_CMU_TARGET_CMU_GRP_1[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CMU_05"                               , 0x00000000, 0x00000001, 0x00000001},
    {"CMU_06"                               , 0x00000001, 0x00000001, 0x00000001},
    {"CMU_07"                               , 0x00000002, 0x00000001, 0x00000001},
    {"CMU_08"                               , 0x00000003, 0x00000001, 0x00000001},
    {"CMU_09"                               , 0x00000004, 0x00000001, 0x00000001},
    {"CMU_0A"                               , 0x00000005, 0x00000001, 0x00000001},
    {"CMU_0B"                               , 0x00000006, 0x00000001, 0x00000001},
    {"CMU_0C"                               , 0x00000007, 0x00000001, 0x00000001},
    {"CMU_0D"                               , 0x00000008, 0x00000001, 0x00000001},
    {"CMU_0E"                               , 0x00000009, 0x00000001, 0x00000001},
    {"CMU_0F"                               , 0x0000000a, 0x00000001, 0x00000001},
    {"CMU_10"                               , 0x0000000b, 0x00000001, 0x00000001},
    {"CMU_11"                               , 0x0000000c, 0x00000001, 0x00000001},
    {"CMU_12"                               , 0x0000000d, 0x00000001, 0x00000001},
    {"CMU_13"                               , 0x0000000e, 0x00000001, 0x00000001},
    {"CMU_14"                               , 0x0000000f, 0x00000001, 0x00000001},
    {"CMU_15"                               , 0x00000010, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G_CMU_TARGET_CMU_GRP_2[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CMU_17"                               , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G_CMU_TARGET_CMU_GRP_3[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CMU_1A"                               , 0x00000000, 0x00000001, 0x00000001},
    {"CMU_1B"                               , 0x00000001, 0x00000001, 0x00000001},
    {"CMU_1C"                               , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G_CMU_TARGET_CMU_GRP_4[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CMU_1F"                               , 0x00000000, 0x00000001, 0x00000001},
    {"CMU_20"                               , 0x00000001, 0x00000001, 0x00000001},
    {"CMU_21"                               , 0x00000002, 0x00000001, 0x00000001},
    {"CMU_22"                               , 0x00000003, 0x00000001, 0x00000001},
    {"CMU_23"                               , 0x00000004, 0x00000001, 0x00000001},
    {"CMU_24"                               , 0x00000005, 0x00000001, 0x00000001},
    {"CMU_25"                               , 0x00000006, 0x00000001, 0x00000001},
    {"CMU_26"                               , 0x00000007, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G_CMU_TARGET_CMU_GRP_5[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CMU_30"                               , 0x00000000, 0x00000001, 0x00000001},
    {"CMU_31"                               , 0x00000001, 0x00000001, 0x00000001},
    {"CMU_32"                               , 0x00000002, 0x00000001, 0x00000001},
    {"CMU_33"                               , 0x00000003, 0x00000001, 0x00000001},
    {"CMU_34"                               , 0x00000004, 0x00000001, 0x00000001},
    {"CMU_35"                               , 0x00000005, 0x00000001, 0x00000001},
    {"CMU_36"                               , 0x00000006, 0x00000001, 0x00000001},
    {"CMU_37"                               , 0x00000007, 0x00000001, 0x00000001},
    {"CMU_38"                               , 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G_CMU_TARGET_CMU_GRP_6[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CMU_42"                               , 0x00000000, 0x00000001, 0x00000001},
    {"CMU_43"                               , 0x00000001, 0x00000001, 0x00000001},
    {"CMU_44"                               , 0x00000002, 0x00000001, 0x00000001},
    {"CMU_45"                               , 0x00000003, 0x00000001, 0x00000001},
    {"CMU_46"                               , 0x00000004, 0x00000001, 0x00000001},
    {"CMU_47"                               , 0x00000005, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G_CMU_TARGET_CMU_GRP_7[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CMU_E0"                               , 0x00000000, 0x00000001, 0x00000001},
    {"CMU_E1"                               , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_SD10G_CMU_TARGET[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"CMU_GRP_0"                            , 0x00000000, 0x00000001, 0x00000005, regs_within_SD10G_CMU_TARGET_CMU_GRP_0},
    {"CMU_GRP_1"                            , 0x00000005, 0x00000001, 0x00000012, regs_within_SD10G_CMU_TARGET_CMU_GRP_1},
    {"CMU_GRP_2"                            , 0x00000017, 0x00000001, 0x00000003, regs_within_SD10G_CMU_TARGET_CMU_GRP_2},
    {"CMU_GRP_3"                            , 0x0000001a, 0x00000001, 0x00000005, regs_within_SD10G_CMU_TARGET_CMU_GRP_3},
    {"CMU_GRP_4"                            , 0x0000001f, 0x00000001, 0x00000011, regs_within_SD10G_CMU_TARGET_CMU_GRP_4},
    {"CMU_GRP_5"                            , 0x00000030, 0x00000001, 0x00000012, regs_within_SD10G_CMU_TARGET_CMU_GRP_5},
    {"CMU_GRP_6"                            , 0x00000042, 0x00000001, 0x0000009e, regs_within_SD10G_CMU_TARGET_CMU_GRP_6},
    {"CMU_GRP_7"                            , 0x000000e0, 0x00000001, 0x00000002, regs_within_SD10G_CMU_TARGET_CMU_GRP_7},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_SD_CMU_TERM_TARGET_SD_CMU_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_CMU_CFG"                           , 0x00000000, 0x00000001, 0x00000001},
    {"SD_CMU_STAT"                          , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD_CMU_TERM_TARGET_SD_EXTCFG_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_EXTCFG_CFG"                        , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD_CMU_TERM_TARGET_SD_LCPLL_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LCPLL_CFG"                            , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_SD_CMU_TERM_TARGET[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"SD_CMU_CFG"                           , 0x00000000, 0x00000001, 0x00000002, regs_within_SD_CMU_TERM_TARGET_SD_CMU_CFG},
    {"SD_EXTCFG_CFG"                        , 0x00000002, 0x00000001, 0x00000001, regs_within_SD_CMU_TERM_TARGET_SD_EXTCFG_CFG},
#ifndef VTSS_RELEASE
    {"SD_LCPLL_CFG"                         , 0x00000003, 0x00000001, 0x00000001, regs_within_SD_CMU_TERM_TARGET_SD_LCPLL_CFG},
#endif
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_SD_CMU_NONTERM_TARGET_SD_CMU_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_CMU_CFG"                           , 0x00000000, 0x00000001, 0x00000001},
    {"SD_CMU_STAT"                          , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_EXTCFG_CFG"                        , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD_CMU_NONTERM_TARGET_SD_LCPLL_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LCPLL_CFG"                            , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_SD_CMU_NONTERM_TARGET[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"SD_CMU_CFG"                           , 0x00000000, 0x00000001, 0x00000002, regs_within_SD_CMU_NONTERM_TARGET_SD_CMU_CFG},
    {"SD_EXTCFG_CFG"                        , 0x00000002, 0x00000001, 0x00000001, regs_within_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG},
#ifndef VTSS_RELEASE
    {"SD_LCPLL_CFG"                         , 0x00000003, 0x00000001, 0x00000001, regs_within_SD_CMU_NONTERM_TARGET_SD_LCPLL_CFG},
#endif
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_SD10G_LANE_TARGET_LANE_GRP_0[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LANE_00"                              , 0x00000000, 0x00000001, 0x00000001},
    {"LANE_01"                              , 0x00000001, 0x00000001, 0x00000001},
    {"LANE_02"                              , 0x00000002, 0x00000001, 0x00000001},
    {"LANE_03"                              , 0x00000003, 0x00000001, 0x00000001},
    {"LANE_04"                              , 0x00000004, 0x00000001, 0x00000001},
    {"LANE_05"                              , 0x00000005, 0x00000001, 0x00000001},
    {"LANE_06"                              , 0x00000006, 0x00000001, 0x00000001},
    {"LANE_07"                              , 0x00000007, 0x00000001, 0x00000001},
    {"LANE_08"                              , 0x00000008, 0x00000001, 0x00000001},
    {"LANE_09"                              , 0x00000009, 0x00000001, 0x00000001},
    {"LANE_0A"                              , 0x0000000a, 0x00000001, 0x00000001},
    {"LANE_0B"                              , 0x0000000b, 0x00000001, 0x00000001},
    {"LANE_0C"                              , 0x0000000c, 0x00000001, 0x00000001},
    {"LANE_0D"                              , 0x0000000d, 0x00000001, 0x00000001},
    {"LANE_0E"                              , 0x0000000e, 0x00000001, 0x00000001},
    {"LANE_0F"                              , 0x0000000f, 0x00000001, 0x00000001},
    {"LANE_10"                              , 0x00000010, 0x00000001, 0x00000001},
    {"LANE_11"                              , 0x00000011, 0x00000001, 0x00000001},
    {"LANE_12"                              , 0x00000012, 0x00000001, 0x00000001},
    {"LANE_13"                              , 0x00000013, 0x00000001, 0x00000001},
    {"LANE_14"                              , 0x00000014, 0x00000001, 0x00000001},
    {"LANE_15"                              , 0x00000015, 0x00000001, 0x00000001},
    {"LANE_16"                              , 0x00000016, 0x00000001, 0x00000001},
    {"LANE_17"                              , 0x00000017, 0x00000001, 0x00000001},
    {"LANE_18"                              , 0x00000018, 0x00000001, 0x00000001},
    {"LANE_19"                              , 0x00000019, 0x00000001, 0x00000001},
    {"LANE_1A"                              , 0x0000001a, 0x00000001, 0x00000001},
    {"LANE_1B"                              , 0x0000001b, 0x00000001, 0x00000001},
    {"LANE_1C"                              , 0x0000001c, 0x00000001, 0x00000001},
    {"LANE_1D"                              , 0x0000001d, 0x00000001, 0x00000001},
    {"LANE_1E"                              , 0x0000001e, 0x00000001, 0x00000001},
    {"LANE_1F"                              , 0x0000001f, 0x00000001, 0x00000001},
    {"LANE_20"                              , 0x00000020, 0x00000001, 0x00000001},
    {"LANE_21"                              , 0x00000021, 0x00000001, 0x00000001},
    {"LANE_22"                              , 0x00000022, 0x00000001, 0x00000001},
    {"LANE_23"                              , 0x00000023, 0x00000001, 0x00000001},
    {"LANE_24"                              , 0x00000024, 0x00000001, 0x00000001},
    {"LANE_25"                              , 0x00000025, 0x00000001, 0x00000001},
    {"LANE_26"                              , 0x00000026, 0x00000001, 0x00000001},
    {"LANE_27"                              , 0x00000027, 0x00000001, 0x00000001},
    {"LANE_28"                              , 0x00000028, 0x00000001, 0x00000001},
    {"LANE_29"                              , 0x00000029, 0x00000001, 0x00000001},
    {"LANE_2A"                              , 0x0000002a, 0x00000001, 0x00000001},
    {"LANE_2B"                              , 0x0000002b, 0x00000001, 0x00000001},
    {"LANE_2C"                              , 0x0000002c, 0x00000001, 0x00000001},
    {"LANE_2D"                              , 0x0000002d, 0x00000001, 0x00000001},
    {"LANE_2E"                              , 0x0000002e, 0x00000001, 0x00000001},
    {"LANE_2F"                              , 0x0000002f, 0x00000001, 0x00000001},
    {"LANE_30"                              , 0x00000030, 0x00000001, 0x00000001},
    {"LANE_31"                              , 0x00000031, 0x00000001, 0x00000001},
    {"LANE_32"                              , 0x00000032, 0x00000001, 0x00000001},
    {"LANE_33"                              , 0x00000033, 0x00000001, 0x00000001},
    {"LANE_34"                              , 0x00000034, 0x00000001, 0x00000001},
    {"LANE_35"                              , 0x00000035, 0x00000001, 0x00000001},
    {"LANE_36"                              , 0x00000036, 0x00000001, 0x00000001},
    {"LANE_37"                              , 0x00000037, 0x00000001, 0x00000001},
    {"LANE_38"                              , 0x00000038, 0x00000001, 0x00000001},
    {"LANE_39"                              , 0x00000039, 0x00000001, 0x00000001},
    {"LANE_3A"                              , 0x0000003a, 0x00000001, 0x00000001},
    {"LANE_3B"                              , 0x0000003b, 0x00000001, 0x00000001},
    {"LANE_3C"                              , 0x0000003c, 0x00000001, 0x00000001},
    {"LANE_3D"                              , 0x0000003d, 0x00000001, 0x00000001},
    {"LANE_3E"                              , 0x0000003e, 0x00000001, 0x00000001},
    {"LANE_3F"                              , 0x0000003f, 0x00000001, 0x00000001},
    {"LANE_40"                              , 0x00000040, 0x00000001, 0x00000001},
    {"LANE_41"                              , 0x00000041, 0x00000001, 0x00000001},
    {"LANE_42"                              , 0x00000042, 0x00000001, 0x00000001},
    {"LANE_43"                              , 0x00000043, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G_LANE_TARGET_LANE_GRP_1[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LANE_48"                              , 0x00000000, 0x00000001, 0x00000001},
    {"LANE_49"                              , 0x00000001, 0x00000001, 0x00000001},
    {"LANE_4A"                              , 0x00000002, 0x00000001, 0x00000001},
    {"LANE_4B"                              , 0x00000003, 0x00000001, 0x00000001},
    {"LANE_4C"                              , 0x00000004, 0x00000001, 0x00000001},
    {"LANE_4D"                              , 0x00000005, 0x00000001, 0x00000001},
    {"LANE_4E"                              , 0x00000006, 0x00000001, 0x00000001},
    {"LANE_4F"                              , 0x00000007, 0x00000001, 0x00000001},
    {"LANE_50"                              , 0x00000008, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G_LANE_TARGET_LANE_GRP_2[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LANE_52"                              , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G_LANE_TARGET_LANE_GRP_3[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LANE_58"                              , 0x00000000, 0x00000001, 0x00000001},
    {"LANE_59"                              , 0x00000001, 0x00000001, 0x00000001},
    {"LANE_5A"                              , 0x00000002, 0x00000001, 0x00000001},
    {"LANE_5B"                              , 0x00000003, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G_LANE_TARGET_LANE_GRP_4[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LANE_74"                              , 0x00000000, 0x00000001, 0x00000001},
    {"LANE_75"                              , 0x00000001, 0x00000001, 0x00000001},
    {"LANE_76"                              , 0x00000002, 0x00000001, 0x00000001},
    {"LANE_77"                              , 0x00000003, 0x00000001, 0x00000001},
    {"LANE_78"                              , 0x00000004, 0x00000001, 0x00000001},
    {"LANE_79"                              , 0x00000005, 0x00000001, 0x00000001},
    {"LANE_7A"                              , 0x00000006, 0x00000001, 0x00000001},
    {"LANE_7B"                              , 0x00000007, 0x00000001, 0x00000001},
    {"LANE_7C"                              , 0x00000008, 0x00000001, 0x00000001},
    {"LANE_7D"                              , 0x00000009, 0x00000001, 0x00000001},
    {"LANE_7E"                              , 0x0000000a, 0x00000001, 0x00000001},
    {"LANE_7F"                              , 0x0000000b, 0x00000001, 0x00000001},
    {"LANE_80"                              , 0x0000000c, 0x00000001, 0x00000001},
    {"LANE_81"                              , 0x0000000d, 0x00000001, 0x00000001},
    {"LANE_82"                              , 0x0000000e, 0x00000001, 0x00000001},
    {"LANE_83"                              , 0x0000000f, 0x00000001, 0x00000001},
    {"LANE_84"                              , 0x00000010, 0x00000001, 0x00000001},
    {"LANE_85"                              , 0x00000011, 0x00000001, 0x00000001},
    {"LANE_86"                              , 0x00000012, 0x00000001, 0x00000001},
    {"LANE_87"                              , 0x00000013, 0x00000001, 0x00000001},
    {"LANE_88"                              , 0x00000014, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G_LANE_TARGET_LANE_GRP_5[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LANE_90"                              , 0x00000000, 0x00000001, 0x00000001},
    {"LANE_91"                              , 0x00000001, 0x00000001, 0x00000001},
    {"LANE_92"                              , 0x00000002, 0x00000001, 0x00000001},
    {"LANE_93"                              , 0x00000003, 0x00000001, 0x00000001},
    {"LANE_94"                              , 0x00000004, 0x00000001, 0x00000001},
    {"LANE_95"                              , 0x00000005, 0x00000001, 0x00000001},
    {"LANE_96"                              , 0x00000006, 0x00000001, 0x00000001},
    {"LANE_97"                              , 0x00000007, 0x00000001, 0x00000001},
    {"LANE_98"                              , 0x00000008, 0x00000001, 0x00000001},
    {"LANE_99"                              , 0x00000009, 0x00000001, 0x00000001},
    {"LANE_9A"                              , 0x0000000a, 0x00000001, 0x00000001},
    {"LANE_9B"                              , 0x0000000b, 0x00000001, 0x00000001},
    {"LANE_9C"                              , 0x0000000c, 0x00000001, 0x00000001},
    {"LANE_9D"                              , 0x0000000d, 0x00000001, 0x00000001},
    {"LANE_9E"                              , 0x0000000e, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G_LANE_TARGET_LANE_GRP_6[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LANE_A0"                              , 0x00000000, 0x00000001, 0x00000001},
    {"LANE_A1"                              , 0x00000001, 0x00000001, 0x00000001},
    {"LANE_A2"                              , 0x00000002, 0x00000001, 0x00000001},
    {"LANE_A3"                              , 0x00000003, 0x00000001, 0x00000001},
    {"LANE_A4"                              , 0x00000004, 0x00000001, 0x00000001},
    {"LANE_A5"                              , 0x00000005, 0x00000001, 0x00000001},
    {"LANE_A6"                              , 0x00000006, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G_LANE_TARGET_LANE_GRP_7[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LANE_C0"                              , 0x00000000, 0x00000001, 0x00000001},
    {"LANE_C1"                              , 0x00000001, 0x00000001, 0x00000001},
    {"LANE_C2"                              , 0x00000002, 0x00000001, 0x00000001},
    {"LANE_C3"                              , 0x00000003, 0x00000001, 0x00000001},
    {"LANE_C4"                              , 0x00000004, 0x00000001, 0x00000001},
    {"LANE_C5"                              , 0x00000005, 0x00000001, 0x00000001},
    {"LANE_C6"                              , 0x00000006, 0x00000001, 0x00000001},
    {"LANE_C7"                              , 0x00000007, 0x00000001, 0x00000001},
    {"LANE_C8"                              , 0x00000008, 0x00000001, 0x00000001},
    {"LANE_C9"                              , 0x00000009, 0x00000001, 0x00000001},
    {"LANE_CA"                              , 0x0000000a, 0x00000001, 0x00000001},
    {"LANE_CB"                              , 0x0000000b, 0x00000001, 0x00000001},
    {"LANE_CC"                              , 0x0000000c, 0x00000001, 0x00000001},
    {"LANE_CD"                              , 0x0000000d, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD10G_LANE_TARGET_LANE_GRP_8[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LANE_D0"                              , 0x00000000, 0x00000001, 0x00000001},
    {"LANE_D1"                              , 0x00000001, 0x00000001, 0x00000001},
    {"LANE_D2"                              , 0x00000002, 0x00000001, 0x00000001},
    {"LANE_D3"                              , 0x00000003, 0x00000001, 0x00000001},
    {"LANE_D4"                              , 0x00000004, 0x00000001, 0x00000001},
    {"LANE_D5"                              , 0x00000005, 0x00000001, 0x00000001},
    {"LANE_D6"                              , 0x00000006, 0x00000001, 0x00000001},
    {"LANE_D7"                              , 0x00000007, 0x00000001, 0x00000001},
    {"LANE_D8"                              , 0x00000008, 0x00000001, 0x00000001},
    {"LANE_D9"                              , 0x00000009, 0x00000001, 0x00000001},
    {"LANE_DA"                              , 0x0000000a, 0x00000001, 0x00000001},
    {"LANE_DB"                              , 0x0000000b, 0x00000001, 0x00000001},
    {"LANE_DC"                              , 0x0000000c, 0x00000001, 0x00000001},
    {"LANE_DD"                              , 0x0000000d, 0x00000001, 0x00000001},
    {"LANE_DE"                              , 0x0000000e, 0x00000001, 0x00000001},
    {"LANE_DF"                              , 0x0000000f, 0x00000001, 0x00000001},
    {"LANE_E0"                              , 0x00000010, 0x00000001, 0x00000001},
    {"LANE_E1"                              , 0x00000011, 0x00000001, 0x00000001},
    {"LANE_E2"                              , 0x00000012, 0x00000001, 0x00000001},
    {"LANE_E3"                              , 0x00000013, 0x00000001, 0x00000001},
    {"LANE_E4"                              , 0x00000014, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_SD10G_LANE_TARGET[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"LANE_GRP_0"                           , 0x00000000, 0x00000001, 0x00000048, regs_within_SD10G_LANE_TARGET_LANE_GRP_0},
    {"LANE_GRP_1"                           , 0x00000048, 0x00000001, 0x0000000a, regs_within_SD10G_LANE_TARGET_LANE_GRP_1},
    {"LANE_GRP_2"                           , 0x00000052, 0x00000001, 0x00000006, regs_within_SD10G_LANE_TARGET_LANE_GRP_2},
    {"LANE_GRP_3"                           , 0x00000058, 0x00000001, 0x0000001c, regs_within_SD10G_LANE_TARGET_LANE_GRP_3},
    {"LANE_GRP_4"                           , 0x00000074, 0x00000001, 0x0000001c, regs_within_SD10G_LANE_TARGET_LANE_GRP_4},
    {"LANE_GRP_5"                           , 0x00000090, 0x00000001, 0x00000010, regs_within_SD10G_LANE_TARGET_LANE_GRP_5},
    {"LANE_GRP_6"                           , 0x000000a0, 0x00000001, 0x00000020, regs_within_SD10G_LANE_TARGET_LANE_GRP_6},
    {"LANE_GRP_7"                           , 0x000000c0, 0x00000001, 0x00000010, regs_within_SD10G_LANE_TARGET_LANE_GRP_7},
    {"LANE_GRP_8"                           , 0x000000d0, 0x00000001, 0x00000015, regs_within_SD10G_LANE_TARGET_LANE_GRP_8},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_KR_PMD_CTRL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"KR_PMD_CTRL"                          , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_KR_PMD_STS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"KR_PMD_STS"                           , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_LP_COEF_UPD[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LP_COEF_UPD"                          , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_LP_STS_RPT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LP_STS_RPT"                           , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_LD_COEF_UPD[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LD_COEF_UPD"                          , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_LD_STS_RPT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LD_STS_RPT"                           , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_CLK_EN[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"CLK_EN"                               , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_TMR_HOLD[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TMR_HOLD"                             , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_TR_CFG0[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TR_CFG0"                              , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_FRCNT_BER[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FRCNT_BER"                            , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_TR_FRSENT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TR_FRSENT"                            , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_TR_ERRCNT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TR_ERRCNT"                            , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_AN_CFG0[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AN_CFG0"                              , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_AN_STS0[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AN_STS0"                              , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_LD_ADV[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LD_ADV0"                              , 0x00000000, 0x00000001, 0x00000001},
    {"LD_ADV1"                              , 0x00000001, 0x00000001, 0x00000001},
    {"LD_ADV2"                              , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_LP_BP0[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LP_BP0"                               , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_LP_BP1[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LP_BP1"                               , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_LP_BP2[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LP_BP2"                               , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_LD_NP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LD_NP0"                               , 0x00000000, 0x00000001, 0x00000001},
    {"LD_NP1"                               , 0x00000001, 0x00000001, 0x00000001},
    {"LD_NP2"                               , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_LP_NP[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LP_NP0"                               , 0x00000000, 0x00000001, 0x00000001},
    {"LP_NP1"                               , 0x00000001, 0x00000001, 0x00000001},
    {"LP_NP2"                               , 0x00000002, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_BP_ETH_STS[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"BP_ETH_STS"                           , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_AN_CFG1[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AN_CFG1"                              , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_BL_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"BL_TMR"                               , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_AW_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AW_TMR"                               , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_LFLONG_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LFLONG_TMR"                           , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_LFSHORT_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LFSHORT_TMR"                          , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_LP_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"LP_TMR"                               , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_TR_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"TR_TMR"                               , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_PD_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"PD_TMR"                               , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_WT_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"WT_TMR"                               , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_MW_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MW_TMR"                               , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_GEN0_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GEN0_TMR"                             , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_GEN1_TMR[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"GEN1_TMR"                             , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_AN_HIST[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AN_HIST"                              , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_AN_SM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AN_SM"                                , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_AN_STS1[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"AN_STS1"                              , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_FW_MSG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FW_MSG"                               , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_FW_REQ[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"FW_REQ"                               , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_IRQ_VEC[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IRQ_VEC"                              , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_IP_KRANEG_IRQ_MASK[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"IRQ_MASK"                             , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_IP_KRANEG[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"KR_PMD_CTRL"                          , 0x00000196, 0x00000001, 0x00000001, regs_within_IP_KRANEG_KR_PMD_CTRL},
    {"KR_PMD_STS"                           , 0x00000197, 0x00000001, 0x00000001, regs_within_IP_KRANEG_KR_PMD_STS},
    {"LP_COEF_UPD"                          , 0x00000198, 0x00000001, 0x00000001, regs_within_IP_KRANEG_LP_COEF_UPD},
    {"LP_STS_RPT"                           , 0x00000199, 0x00000001, 0x00000001, regs_within_IP_KRANEG_LP_STS_RPT},
    {"LD_COEF_UPD"                          , 0x0000019a, 0x00000001, 0x00000001, regs_within_IP_KRANEG_LD_COEF_UPD},
    {"LD_STS_RPT"                           , 0x0000019b, 0x00000001, 0x00000001, regs_within_IP_KRANEG_LD_STS_RPT},
    {"CLK_EN"                               , 0x00001100, 0x00000001, 0x00000001, regs_within_IP_KRANEG_CLK_EN},
    {"TMR_HOLD"                             , 0x00001101, 0x00000001, 0x00000001, regs_within_IP_KRANEG_TMR_HOLD},
    {"TR_CFG0"                              , 0x00001102, 0x00000001, 0x00000001, regs_within_IP_KRANEG_TR_CFG0},
    {"FRCNT_BER"                            , 0x00001103, 0x00000001, 0x00000001, regs_within_IP_KRANEG_FRCNT_BER},
    {"TR_FRSENT"                            , 0x00001104, 0x00000001, 0x00000001, regs_within_IP_KRANEG_TR_FRSENT},
    {"TR_ERRCNT"                            , 0x00001105, 0x00000001, 0x00000001, regs_within_IP_KRANEG_TR_ERRCNT},
    {"AN_CFG0"                              , 0x00000000, 0x00000001, 0x00000001, regs_within_IP_KRANEG_AN_CFG0},
    {"AN_STS0"                              , 0x00000001, 0x00000001, 0x00000001, regs_within_IP_KRANEG_AN_STS0},
    {"LD_ADV"                               , 0x00000010, 0x00000001, 0x00000003, regs_within_IP_KRANEG_LD_ADV},
    {"LP_BP0"                               , 0x00000013, 0x00000001, 0x00000001, regs_within_IP_KRANEG_LP_BP0},
    {"LP_BP1"                               , 0x00000014, 0x00000001, 0x00000001, regs_within_IP_KRANEG_LP_BP1},
    {"LP_BP2"                               , 0x00000015, 0x00000001, 0x00000001, regs_within_IP_KRANEG_LP_BP2},
    {"LD_NP"                                , 0x00000016, 0x00000001, 0x00000003, regs_within_IP_KRANEG_LD_NP},
    {"LP_NP"                                , 0x00000019, 0x00000001, 0x00000004, regs_within_IP_KRANEG_LP_NP},
    {"BP_ETH_STS"                           , 0x00000030, 0x00000001, 0x00000001, regs_within_IP_KRANEG_BP_ETH_STS},
    {"AN_CFG1"                              , 0x00001000, 0x00000001, 0x00000001, regs_within_IP_KRANEG_AN_CFG1},
    {"BL_TMR"                               , 0x00001010, 0x00000001, 0x00000001, regs_within_IP_KRANEG_BL_TMR},
    {"AW_TMR"                               , 0x00001012, 0x00000001, 0x00000001, regs_within_IP_KRANEG_AW_TMR},
    {"LFLONG_TMR"                           , 0x00001014, 0x00000001, 0x00000001, regs_within_IP_KRANEG_LFLONG_TMR},
    {"LFSHORT_TMR"                          , 0x00001016, 0x00000001, 0x00000001, regs_within_IP_KRANEG_LFSHORT_TMR},
    {"LP_TMR"                               , 0x00001018, 0x00000001, 0x00000001, regs_within_IP_KRANEG_LP_TMR},
    {"TR_TMR"                               , 0x0000101a, 0x00000001, 0x00000001, regs_within_IP_KRANEG_TR_TMR},
    {"PD_TMR"                               , 0x0000101c, 0x00000001, 0x00000001, regs_within_IP_KRANEG_PD_TMR},
    {"WT_TMR"                               , 0x00001024, 0x00000001, 0x00000001, regs_within_IP_KRANEG_WT_TMR},
    {"MW_TMR"                               , 0x00001026, 0x00000001, 0x00000001, regs_within_IP_KRANEG_MW_TMR},
    {"GEN0_TMR"                             , 0x00001028, 0x00000001, 0x00000001, regs_within_IP_KRANEG_GEN0_TMR},
    {"GEN1_TMR"                             , 0x0000102a, 0x00000001, 0x00000001, regs_within_IP_KRANEG_GEN1_TMR},
#ifndef VTSS_RELEASE
    {"AN_HIST"                              , 0x00001030, 0x00000001, 0x00000001, regs_within_IP_KRANEG_AN_HIST},
#endif
    {"AN_SM"                                , 0x00001031, 0x00000001, 0x00000001, regs_within_IP_KRANEG_AN_SM},
    {"AN_STS1"                              , 0x00001032, 0x00000001, 0x00000001, regs_within_IP_KRANEG_AN_STS1},
    {"FW_MSG"                               , 0x00001040, 0x00000001, 0x00000001, regs_within_IP_KRANEG_FW_MSG},
    {"FW_REQ"                               , 0x00001041, 0x00000001, 0x00000001, regs_within_IP_KRANEG_FW_REQ},
    {"IRQ_VEC"                              , 0x00001042, 0x00000001, 0x00000001, regs_within_IP_KRANEG_IRQ_VEC},
    {"IRQ_MASK"                             , 0x00001043, 0x00000001, 0x00000001, regs_within_IP_KRANEG_IRQ_MASK},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_SD_LANE_TARGET_SD_RESET[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_SER_RST"                           , 0x00000000, 0x00000001, 0x00000001},
    {"SD_DES_RST"                           , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD_LANE_TARGET_SD_LANE_CFG_STAT[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_LANE_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
    {"SD_LANE_STAT"                         , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD_LANE_TARGET_SD_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_CFG"                               , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD_LANE_TARGET_SD_CLK_GATE[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_CLK_GATE"                          , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD_LANE_TARGET_SD_PWR_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"NORMAL_MODE"                          , 0x00000000, 0x00000001, 0x00000001},
    {"QUIET_MODE_6G"                        , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD_LANE_TARGET_SD_ANEG_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_KR_ANEG_MODE"                      , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD_LANE_TARGET_SD_EXTCFG_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_EXTCFG_CFG"                        , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD_LANE_TARGET_SD_FIFO_DELAY[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SD_DELAY_CFG"                         , 0x00000000, 0x00000001, 0x00000001},
    {"SD_DELAY_VAR"                         , 0x00000001, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD_LANE_TARGET_SYNC_ETH_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"SYNC_ETH_SD_CFG"                      , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD_LANE_TARGET_HW_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"KR_DATA_CFG"                          , 0x00000000, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_SD_LANE_TARGET_CFG_STAT_FX100[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"MISC"                                 , 0x00000000, 0x00000001, 0x00000001},
    {"STICKY_BITS"                          , 0x00000001, 0x00000001, 0x00000001},
    {"EDGE_CFG"                             , 0x00000002, 0x00000001, 0x00000001},
    {"LOCK_PERIOD"                          , 0x00000003, 0x00000001, 0x00000001},
    {"LOCK_PERIOD_PTR_ADJ_SUM_ABS_THRES"    , 0x00000004, 0x00000001, 0x00000001},
    {"LOCK_PERIOD_PTR_ADJ_CNT_THRES"        , 0x00000005, 0x00000001, 0x00000001},
    {"FILTER_CFG"                           , 0x00000006, 0x00000002, 0x00000001},
    {"M_CTRL"                               , 0x00000008, 0x00000001, 0x00000001},
    {"M_STAT_MISC"                          , 0x00000009, 0x00000001, 0x00000001},
    {"M_STAT_SD_ONE_CNT"                    , 0x0000000a, 0x00000001, 0x00000001},
    {"M_STAT_FX_ONE_CNT"                    , 0x0000000b, 0x00000001, 0x00000001},
    {"M_STAT_FILTER_MATCH_CNT"              , 0x0000000c, 0x00000002, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reggrp_t reggrps_within_SD_LANE_TARGET[] = {
    //reggrp name                           , base_addr , repl_cnt  , repl_width, reg list
    {"SD_RESET"                             , 0x00000000, 0x00000001, 0x00000002, regs_within_SD_LANE_TARGET_SD_RESET},
    {"SD_LANE_CFG_STAT"                     , 0x00000002, 0x00000001, 0x00000002, regs_within_SD_LANE_TARGET_SD_LANE_CFG_STAT},
    {"SD_CFG"                               , 0x00000004, 0x00000001, 0x00000001, regs_within_SD_LANE_TARGET_SD_CFG},
    {"SD_CLK_GATE"                          , 0x00000005, 0x00000001, 0x00000001, regs_within_SD_LANE_TARGET_SD_CLK_GATE},
    {"SD_PWR_CFG"                           , 0x00000006, 0x00000001, 0x00000002, regs_within_SD_LANE_TARGET_SD_PWR_CFG},
#ifndef VTSS_RELEASE
    {"SD_ANEG_CFG"                          , 0x00000008, 0x00000001, 0x00000001, regs_within_SD_LANE_TARGET_SD_ANEG_CFG},
#endif
    {"SD_EXTCFG_CFG"                        , 0x00000009, 0x00000001, 0x00000001, regs_within_SD_LANE_TARGET_SD_EXTCFG_CFG},
    {"SD_FIFO_DELAY"                        , 0x0000000a, 0x00000001, 0x00000002, regs_within_SD_LANE_TARGET_SD_FIFO_DELAY},
    {"SYNC_ETH_CFG"                         , 0x0000000c, 0x00000001, 0x00000001, regs_within_SD_LANE_TARGET_SYNC_ETH_CFG},
#ifndef VTSS_RELEASE
    {"HW_CFG"                               , 0x0000000d, 0x00000001, 0x00000001, regs_within_SD_LANE_TARGET_HW_CFG},
#endif
    {"CFG_STAT_FX100"                       , 0x0000000e, 0x00000001, 0x0000000e, regs_within_SD_LANE_TARGET_CFG_STAT_FX100},
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
    {"BIST_DIAG_BITMAPA_STAT"               , 0x00000017, 0x00000003, 0x00000001},
    {"BIST_DIAG_BITMAPB_STAT"               , 0x0000001a, 0x00000003, 0x00000001},
    {"RCR_CTRL"                             , 0x0000001d, 0x00000001, 0x00000001},
    {"RCR_STAT"                             , 0x0000001e, 0x00000001, 0x00000001},
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
    {"TCAM_BIST"                            , 0x000000f1, 0x00000001, 0x0000001f, regs_within_VCAP_ES0_TCAM_BIST},
    {"ECC_CHK"                              , 0x00000110, 0x00000001, 0x00000004, regs_within_VCAP_ES0_ECC_CHK},
    {"MEMITGR"                              , 0x00000114, 0x00000001, 0x00000006, regs_within_VCAP_ES0_MEMITGR},
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
    {"BIST_DIAG_BITMAPA_STAT"               , 0x00000017, 0x00000003, 0x00000001},
    {"BIST_DIAG_BITMAPB_STAT"               , 0x0000001a, 0x00000003, 0x00000001},
    {"RCR_CTRL"                             , 0x0000001d, 0x00000001, 0x00000001},
    {"RCR_STAT"                             , 0x0000001e, 0x00000001, 0x00000001},
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
    {"TCAM_BIST"                            , 0x000000f1, 0x00000001, 0x0000001f, regs_within_VCAP_ES2_TCAM_BIST},
    {"ECC_CHK"                              , 0x00000110, 0x00000001, 0x00000004, regs_within_VCAP_ES2_ECC_CHK},
    {"MEMITGR"                              , 0x00000114, 0x00000001, 0x00000006, regs_within_VCAP_ES2_MEMITGR},
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
    {"BIST_DIAG_BITMAPA_STAT"               , 0x00000017, 0x00000003, 0x00000001},
    {"BIST_DIAG_BITMAPB_STAT"               , 0x0000001a, 0x00000003, 0x00000001},
    {"RCR_CTRL"                             , 0x0000001d, 0x00000001, 0x00000001},
    {"RCR_STAT"                             , 0x0000001e, 0x00000001, 0x00000001},
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
    {"TCAM_BIST"                            , 0x000000f1, 0x00000001, 0x0000001f, regs_within_VCAP_IP6PFX_TCAM_BIST},
    {"ECC_CHK"                              , 0x00000110, 0x00000001, 0x00000004, regs_within_VCAP_IP6PFX_ECC_CHK},
    {"MEMITGR"                              , 0x00000114, 0x00000001, 0x00000006, regs_within_VCAP_IP6PFX_MEMITGR},
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
    {"BIST_DIAG_BITMAPA_STAT"               , 0x00000017, 0x00000003, 0x00000001},
    {"BIST_DIAG_BITMAPB_STAT"               , 0x0000001a, 0x00000003, 0x00000001},
    {"RCR_CTRL"                             , 0x0000001d, 0x00000001, 0x00000001},
    {"RCR_STAT"                             , 0x0000001e, 0x00000001, 0x00000001},
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
    {"TCAM_BIST"                            , 0x000000f1, 0x00000001, 0x0000001f, regs_within_VCAP_SUPER_TCAM_BIST},
    {"ECC_CHK"                              , 0x00000110, 0x00000001, 0x00000004, regs_within_VCAP_SUPER_ECC_CHK},
    {"MEMITGR"                              , 0x00000114, 0x00000001, 0x00000006, regs_within_VCAP_SUPER_MEMITGR},
    {"RAM_CTRL"                             , 0x0000011a, 0x00000001, 0x00000001, regs_within_VCAP_SUPER_RAM_CTRL},
#ifndef VTSS_RELEASE
    {"COREMEM"                              , 0x0000011b, 0x00000001, 0x00000004, regs_within_VCAP_SUPER_COREMEM},
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
    {"LOC_PERIOD_CFG"                       , 0x0000002d, 0x00000007, 0x00000001},
    {"HMO_PERIOD_CFG"                       , 0x00000034, 0x00000002, 0x00000001},
    {"HMO_FORCE_SLOT_CFG"                   , 0x00000036, 0x00000002, 0x00000001},
    {"HMO_TIMER_CFG"                        , 0x00000038, 0x00000001, 0x00000001},
    {"LOC_SCAN_STICKY"                      , 0x00000039, 0x00000001, 0x00000001},
    {"MASTER_INTR_CTRL"                     , 0x0000003a, 0x00000001, 0x00000001},
    {"VOE32_INTR"                           , 0x0000003b, 0x00000001, 0x00000001},
    {"INTR"                                 , 0x0000003d, 0x00000002, 0x00000001},
    {"COMMON_MEP_MC_MAC_LSB"                , 0x00000060, 0x00000001, 0x00000001},
    {"COMMON_MEP_MC_MAC_MSB"                , 0x00000061, 0x00000001, 0x00000001},
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
    {"COMMON"                               , 0x0000357e, 0x00000001, 0x00000062, regs_within_VOP_COMMON},
    {"VOE_CONF_REG"                         , 0x000034c0, 0x0000003e, 0x00000001, regs_within_VOP_VOE_CONF_REG},
    {"VOE_CONF"                             , 0x00000000, 0x0000003e, 0x00000040, regs_within_VOP_VOE_CONF},
    {"VOE_STAT"                             , 0x00001000, 0x0000003e, 0x00000040, regs_within_VOP_VOE_STAT},
    {"VOE_STAT_REG"                         , 0x00003500, 0x0000003e, 0x00000001, regs_within_VOP_VOE_STAT_REG},
    {"VOE_CCM_LM"                           , 0x00000f80, 0x0000003e, 0x00000002, regs_within_VOP_VOE_CCM_LM},
#ifndef VTSS_RELEASE
    {"VOE_CONTEXT_ANA"                      , 0x00002800, 0x0000007d, 0x00000010, regs_within_VOP_VOE_CONTEXT_ANA},
#endif
#ifndef VTSS_RELEASE
    {"VOE_CONTEXT_REW"                      , 0x00003000, 0x00000041, 0x00000010, regs_within_VOP_VOE_CONTEXT_REW},
#endif
    {"VOE_CRC_ERR"                          , 0x00003540, 0x0000003e, 0x00000001, regs_within_VOP_VOE_CRC_ERR},
    {"ANA_COSID_MAP_CONF"                   , 0x00003440, 0x00000020, 0x00000002, regs_within_VOP_ANA_COSID_MAP_CONF},
    {"REW_COSID_MAP_CONF"                   , 0x00003480, 0x00000020, 0x00000002, regs_within_VOP_REW_COSID_MAP_CONF},
    {"PORT_COSID_MAP_CONF"                  , 0x00001f80, 0x0000001e, 0x00000004, regs_within_VOP_PORT_COSID_MAP_CONF},
    {"SAM_COSID_SEQ_CNT"                    , 0x00002000, 0x00000020, 0x00000040, regs_within_VOP_SAM_COSID_SEQ_CNT},
    {"RAM_CTRL"                             , 0x00000ffc, 0x00000001, 0x00000001, regs_within_VOP_RAM_CTRL},
#ifndef VTSS_RELEASE
    {"COREMEM"                              , 0x00001ff8, 0x00000001, 0x00000004, regs_within_VOP_COREMEM},
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
    {"VOE_CONF_L3"                          , 0x00000000, 0x0000003e, 0x00000040, regs_within_VOP_L3_VOE_CONF_L3},
    {"VOE_STAT_L3"                          , 0x00001000, 0x0000003e, 0x00000020, regs_within_VOP_L3_VOE_STAT_L3},
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
    {"VOE_CONF_MPLS"                        , 0x00000800, 0x0000003e, 0x00000010, regs_within_VOP_MPLS_VOE_CONF_MPLS},
    {"VOE_STAT_MPLS"                        , 0x00000000, 0x0000003e, 0x00000020, regs_within_VOP_MPLS_VOE_STAT_MPLS},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_reg_t regs_within_XQS_SYSTEM[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"STAT_CNT_CFG"                         , 0x00000000, 0x00000001, 0x00000001},
    {"MAP_CFG_CFG"                          , 0x00000001, 0x00000001, 0x00000001},
    {"FWD_CTRL"                             , 0x00000002, 0x00000001, 0x00000001},
    {"FWD_DROP_EVENTS"                      , 0x00000003, 0x00000023, 0x00000001},
    {"FWD_STAT_CNT"                         , 0x00000026, 0x00000005, 0x00000001},
    {"FWD_CPU_DROP_CNT"                     , 0x0000002b, 0x00000001, 0x00000001},
    {"FWD_CT_CFG"                           , 0x0000002c, 0x0000001e, 0x00000001},
    {"QMAP_PORT_MODE"                       , 0x0000004a, 0x00000023, 0x00000001},
    {"QMAP_EACL"                            , 0x0000006d, 0x00000001, 0x00000001},
    {"STAT_CFG"                             , 0x0000006e, 0x00000001, 0x00000001},
    {"MIRROR_CFG"                           , 0x0000006f, 0x00000001, 0x00000001},
    {"CPUQ_DISCARD"                         , 0x00000070, 0x00000001, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_XQS_QMAP_VPORT_TBL[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"QMAP_VPORT_TBL"                       , 0x00000000, 0x00000023, 0x00000001},
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
    {"QLIMIT_CONG_CNT"                      , 0x00000006, 0x00000005, 0x00000001},
    {NULL, 0, 0, 0}
};
static const vtss_symreg_reg_t regs_within_XQS_QLIMIT_CFG[] = {
    //reg name                              , addr      , repl_cnt  , repl_width
    {"QLIMIT_PORT_CFG"                      , 0x00000000, 0x00000023, 0x00000001},
    {"QLIMIT_DP_CFG"                        , 0x00000023, 0x00000004, 0x00000001},
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
    {"SYSTEM"                               , 0x0000055c, 0x00000001, 0x00000071, regs_within_XQS_SYSTEM},
    {"QMAP_VPORT_TBL"                       , 0x00000400, 0x00000004, 0x00000040, regs_within_XQS_QMAP_VPORT_TBL},
    {"QMAP_SE_TBL"                          , 0x00000550, 0x00000004, 0x00000002, regs_within_XQS_QMAP_SE_TBL},
    {"QMAP_QOS_TBL"                         , 0x00000540, 0x00000004, 0x00000004, regs_within_XQS_QMAP_QOS_TBL},
    {"QLIMIT_QUEUE"                         , 0x00000558, 0x00000004, 0x00000001, regs_within_XQS_QLIMIT_QUEUE},
    {"QLIMIT_SE"                            , 0x00000500, 0x00000004, 0x00000010, regs_within_XQS_QLIMIT_SE},
    {"QLIMIT_CFG"                           , 0x000005cd, 0x00000001, 0x00000027, regs_within_XQS_QLIMIT_CFG},
    {"QLIMIT_SHR"                           , 0x000005f4, 0x00000004, 0x0000000c, regs_within_XQS_QLIMIT_SHR},
    {"QLIMIT_MON"                           , 0x00000624, 0x00000004, 0x00000003, regs_within_XQS_QLIMIT_MON},
    {"STAT"                                 , 0x00000000, 0x00000400, 0x00000001, regs_within_XQS_STAT},
    {NULL, 0, 0, 0, NULL}
};
static const vtss_symreg_target_t vtss_symreg_targets[] = {
    //target name         , repl, tgt_id    , base_addr                  , register group list
    {"AES"                ,   -1, 0x00000006, VTSS_IO_OFFSET2(0x0004c000), reggrps_within_AES},
    {"AESB_ASC"           ,   -1, 0x00000007, VTSS_IO_OFFSET2(0x00050000), reggrps_within_AESB_ASC},
    {"CPU"                ,   -1, 0x00000016, VTSS_IO_OFFSET2(0x000c0000), reggrps_within_CPU},
    {"DDR_PHY"            ,   -1, 0x00000012, VTSS_IO_OFFSET2(0x00084000), reggrps_within_DDR_PHY},
    {"DDR_UMCTL2"         ,   -1, 0x00000011, VTSS_IO_OFFSET2(0x00080000), reggrps_within_DDR_UMCTL2},
    {"FDMA"               ,   -1, 0x00000017, VTSS_IO_OFFSET2(0x000c0400), reggrps_within_FDMA},
    {"FLEXCOM"            ,    0, 0x00000002, VTSS_IO_OFFSET2(0x00040000), reggrps_within_FLEXCOM},
    {"FLEXCOM"            ,    1, 0x00000003, VTSS_IO_OFFSET2(0x00044000), reggrps_within_FLEXCOM},
    {"FLEXCOM"            ,    2, 0x00000009, VTSS_IO_OFFSET2(0x00060000), reggrps_within_FLEXCOM},
    {"FLEXCOM"            ,    3, 0x0000000a, VTSS_IO_OFFSET2(0x00064000), reggrps_within_FLEXCOM},
    {"FLEXCOM"            ,    4, 0x0000000b, VTSS_IO_OFFSET2(0x00070000), reggrps_within_FLEXCOM},
    {"CPU_SYSCNT"         ,   -1, 0x00000026, VTSS_IO_OFFSET2(0x08000000), reggrps_within_CPU_SYSCNT},
    {"CPU_SYSCNT_RO"      ,   -1, 0x00000027, VTSS_IO_OFFSET2(0x08000000), reggrps_within_CPU_SYSCNT_RO},
    {"GIC500"             ,   -1, 0x0000002b, VTSS_IO_OFFSET2(0x02304000), reggrps_within_GIC500},
    {"GPV"                ,   -1, 0x00000029, VTSS_IO_OFFSET2(0x08b00000), reggrps_within_GPV},
    {"HICM"               ,   -1, 0x0000001d, VTSS_IO_OFFSET2(0x00810000), reggrps_within_HICM},
    {"HMATRIX2"           ,   -1, 0x00000019, VTSS_IO_OFFSET2(0x00800000), reggrps_within_HMATRIX2},
    {"MCAN"               ,    0, 0x00000021, VTSS_IO_OFFSET2(0x0081c000), reggrps_within_MCAN},
    {"MCAN"               ,    1, 0x00000022, VTSS_IO_OFFSET2(0x00820000), reggrps_within_MCAN},
    {"MCAN_TIMER"         ,   -1, 0x00000023, VTSS_IO_OFFSET2(0x00824000), reggrps_within_MCAN_TIMER},
    {"OTP"                ,   -1, 0x00000025, VTSS_IO_OFFSET2(0x00021000), reggrps_within_OTP},
    {"QSPI"               ,    0, 0x0000001a, VTSS_IO_OFFSET2(0x00804000), reggrps_within_QSPI},
    {"QSPI"               ,    2, 0x0000001b, VTSS_IO_OFFSET2(0x00834000), reggrps_within_QSPI},
    {"SDMMC"              ,   -1, 0x0000000f, VTSS_IO_OFFSET2(0x00830000), reggrps_within_SDMMC},
    {"SHA"                ,   -1, 0x0000000e, VTSS_IO_OFFSET2(0x0006c000), reggrps_within_SHA},
    {"SJTAG"              ,   -1, 0x0000002a, VTSS_IO_OFFSET2(0x00020000), reggrps_within_SJTAG},
    {"TIMERS"             ,   -1, 0x00000013, VTSS_IO_OFFSET2(0x0008c000), reggrps_within_TIMERS},
    {"TRNG"               ,   -1, 0x00000005, VTSS_IO_OFFSET2(0x00048000), reggrps_within_TRNG},
    {"TZAESBNS"           ,   -1, 0x0000001e, VTSS_IO_OFFSET2(0x00814000), reggrps_within_TZAESB},
    {"TZAESBS"            ,   -1, 0x0000001f, VTSS_IO_OFFSET2(0x00818000), reggrps_within_TZAESB},
    {"TZPM"               ,   -1, 0x00000001, VTSS_IO_OFFSET2(0x00004000), reggrps_within_TZPM},
    {"WDT"                ,   -1, 0x00000015, VTSS_IO_OFFSET2(0x00090000), reggrps_within_WDT},
    {"XDMAC"              ,   -1, 0x0000000d, VTSS_IO_OFFSET2(0x00068000), reggrps_within_XDMAC},
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
    {"CHIP_TOP"           ,   -1, 0x00000008, VTSS_IO_OFFSET1(0x00020000), reggrps_within_CHIP_TOP},
    {"CLKGEN"             ,   -1, 0x00000040, VTSS_IO_OFFSET1(0x00100000), reggrps_within_CLKGEN},
    {"DEV2G5"             ,    1, 0x00000404, VTSS_IO_OFFSET1(0x01010000), reggrps_within_DEV1G},
    {"DEV2G5"             ,    2, 0x00000405, VTSS_IO_OFFSET1(0x01014000), reggrps_within_DEV1G},
    {"DEV2G5"             ,    3, 0x00000406, VTSS_IO_OFFSET1(0x01018000), reggrps_within_DEV1G},
    {"DEV2G5"             ,    5, 0x0000040a, VTSS_IO_OFFSET1(0x01028000), reggrps_within_DEV1G},
    {"DEV2G5"             ,    6, 0x0000040b, VTSS_IO_OFFSET1(0x0102c000), reggrps_within_DEV1G},
    {"DEV2G5"             ,    7, 0x0000040c, VTSS_IO_OFFSET1(0x01030000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   10, 0x00000413, VTSS_IO_OFFSET1(0x0104c000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   11, 0x00000414, VTSS_IO_OFFSET1(0x01050000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   14, 0x0000041b, VTSS_IO_OFFSET1(0x0106c000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   15, 0x0000041c, VTSS_IO_OFFSET1(0x01070000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   18, 0x00000423, VTSS_IO_OFFSET1(0x0108c000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   19, 0x00000424, VTSS_IO_OFFSET1(0x01090000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   22, 0x0000042b, VTSS_IO_OFFSET1(0x010ac000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   23, 0x0000042c, VTSS_IO_OFFSET1(0x010b0000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   28, 0x00000439, VTSS_IO_OFFSET1(0x010e4000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   29, 0x0000043a, VTSS_IO_OFFSET1(0x010e8000), reggrps_within_DEV1G},
    {"DEV2G5"             ,    0, 0x00000401, VTSS_IO_OFFSET1(0x01004000), reggrps_within_DEV1G},
    {"DEV2G5"             ,    4, 0x00000407, VTSS_IO_OFFSET1(0x0101c000), reggrps_within_DEV1G},
    {"DEV2G5"             ,    9, 0x00000410, VTSS_IO_OFFSET1(0x01040000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   13, 0x00000418, VTSS_IO_OFFSET1(0x01060000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   17, 0x00000420, VTSS_IO_OFFSET1(0x01080000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   21, 0x00000428, VTSS_IO_OFFSET1(0x010a0000), reggrps_within_DEV1G},
    {"DEV2G5"             ,    8, 0x0000040d, VTSS_IO_OFFSET1(0x01034000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   12, 0x00000415, VTSS_IO_OFFSET1(0x01054000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   16, 0x0000041d, VTSS_IO_OFFSET1(0x01074000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   20, 0x00000425, VTSS_IO_OFFSET1(0x01094000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   24, 0x0000042d, VTSS_IO_OFFSET1(0x010b4000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   25, 0x00000430, VTSS_IO_OFFSET1(0x010c0000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   26, 0x00000433, VTSS_IO_OFFSET1(0x010cc000), reggrps_within_DEV1G},
    {"DEV2G5"             ,   27, 0x00000436, VTSS_IO_OFFSET1(0x010d8000), reggrps_within_DEV1G},
    {"DEV5G"              ,    0, 0x00000402, VTSS_IO_OFFSET1(0x01008000), reggrps_within_DEV10G},
    {"DEV5G"              ,    1, 0x00000408, VTSS_IO_OFFSET1(0x01020000), reggrps_within_DEV10G},
    {"DEV5G"              ,    2, 0x00000411, VTSS_IO_OFFSET1(0x01044000), reggrps_within_DEV10G},
    {"DEV5G"              ,    3, 0x00000419, VTSS_IO_OFFSET1(0x01064000), reggrps_within_DEV10G},
    {"DEV5G"              ,    4, 0x00000421, VTSS_IO_OFFSET1(0x01084000), reggrps_within_DEV10G},
    {"DEV5G"              ,    5, 0x00000429, VTSS_IO_OFFSET1(0x010a4000), reggrps_within_DEV10G},
    {"PCS5G_BR"           ,    0, 0x00000403, VTSS_IO_OFFSET1(0x0100c000), reggrps_within_PCS_10GBASE_R},
    {"PCS5G_BR"           ,    1, 0x00000409, VTSS_IO_OFFSET1(0x01024000), reggrps_within_PCS_10GBASE_R},
    {"PCS5G_BR"           ,    2, 0x00000412, VTSS_IO_OFFSET1(0x01048000), reggrps_within_PCS_10GBASE_R},
    {"PCS5G_BR"           ,    3, 0x0000041a, VTSS_IO_OFFSET1(0x01068000), reggrps_within_PCS_10GBASE_R},
    {"PCS5G_BR"           ,    4, 0x00000422, VTSS_IO_OFFSET1(0x01088000), reggrps_within_PCS_10GBASE_R},
    {"PCS5G_BR"           ,    5, 0x0000042a, VTSS_IO_OFFSET1(0x010a8000), reggrps_within_PCS_10GBASE_R},
    {"DEV10G"             ,    0, 0x0000040e, VTSS_IO_OFFSET1(0x01038000), reggrps_within_DEV10G},
    {"DEV10G"             ,    1, 0x00000416, VTSS_IO_OFFSET1(0x01058000), reggrps_within_DEV10G},
    {"DEV10G"             ,    2, 0x0000041e, VTSS_IO_OFFSET1(0x01078000), reggrps_within_DEV10G},
    {"DEV10G"             ,    3, 0x00000426, VTSS_IO_OFFSET1(0x01098000), reggrps_within_DEV10G},
    {"DEV10G"             ,    4, 0x0000042e, VTSS_IO_OFFSET1(0x010b8000), reggrps_within_DEV10G},
    {"DEV10G"             ,    5, 0x00000431, VTSS_IO_OFFSET1(0x010c4000), reggrps_within_DEV10G},
    {"DEV10G"             ,    6, 0x00000434, VTSS_IO_OFFSET1(0x010d0000), reggrps_within_DEV10G},
    {"DEV10G"             ,    7, 0x00000437, VTSS_IO_OFFSET1(0x010dc000), reggrps_within_DEV10G},
    {"PCS10G_BR"          ,    0, 0x0000040f, VTSS_IO_OFFSET1(0x0103c000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,    1, 0x00000417, VTSS_IO_OFFSET1(0x0105c000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,    2, 0x0000041f, VTSS_IO_OFFSET1(0x0107c000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,    3, 0x00000427, VTSS_IO_OFFSET1(0x0109c000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,    4, 0x0000042f, VTSS_IO_OFFSET1(0x010bc000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,    5, 0x00000432, VTSS_IO_OFFSET1(0x010c8000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,    6, 0x00000435, VTSS_IO_OFFSET1(0x010d4000), reggrps_within_PCS_10GBASE_R},
    {"PCS10G_BR"          ,    7, 0x00000438, VTSS_IO_OFFSET1(0x010e0000), reggrps_within_PCS_10GBASE_R},
    {"DEVCPU_GCB"         ,   -1, 0x00000004, VTSS_IO_OFFSET1(0x00010000), reggrps_within_DEVCPU_GCB},
    {"DEVCPU_ORG0"        ,   -1, 0x00000000, VTSS_IO_OFFSET1(0x00000000), reggrps_within_DEVCPU_ORG},
    {"DEVCPU_ORG1"        ,   -1, 0x00000400, VTSS_IO_OFFSET1(0x01000000), reggrps_within_DEVCPU_ORG},
    {"DEVCPU_ORG2"        ,   -1, 0x00000500, VTSS_IO_OFFSET1(0x01400000), reggrps_within_DEVCPU_ORG},
    {"PTP"                ,   -1, 0x00000010, VTSS_IO_OFFSET1(0x00040000), reggrps_within_PTP},
    {"DEVCPU_QS"          ,   -1, 0x0000000c, VTSS_IO_OFFSET1(0x00030000), reggrps_within_DEVCPU_QS},
    {"DSM"                ,   -1, 0x0000043b, VTSS_IO_OFFSET1(0x010ec000), reggrps_within_DSM},
    {"EACL"               ,   -1, 0x000000b0, VTSS_IO_OFFSET1(0x002c0000), reggrps_within_EACL},
    {"HSCH"               ,   -1, 0x00000160, VTSS_IO_OFFSET1(0x00580000), reggrps_within_HSCH},
    {"HSIOWRAP"           ,   -1, 0x00000502, VTSS_IO_OFFSET1(0x01408000), reggrps_within_HSIOWRAP},
    {"LCPLL28"            ,    1, 0x0000003c, VTSS_IO_OFFSET1(0x000f0000), reggrps_within_LCPLL28},
    {"LRN"                ,   -1, 0x00000018, VTSS_IO_OFFSET1(0x00060000), reggrps_within_LRN},
    {"PORT_CONF"          ,   -1, 0x0000043c, VTSS_IO_OFFSET1(0x010f0000), reggrps_within_PORT_CONF},
    {"QFWD"               ,   -1, 0x0000002c, VTSS_IO_OFFSET1(0x000b0000), reggrps_within_QFWD},
    {"QRES"               ,   -1, 0x000000a0, VTSS_IO_OFFSET1(0x00280000), reggrps_within_QRES},
    {"QSYS"               ,   -1, 0x00000028, VTSS_IO_OFFSET1(0x000a0000), reggrps_within_QSYS},
    {"REW"                ,   -1, 0x00000180, VTSS_IO_OFFSET1(0x00600000), reggrps_within_REW},
    {"SD_CMU"             ,    0, 0x00000504, VTSS_IO_OFFSET1(0x01410000), reggrps_within_SD10G_CMU_TARGET},
    {"SD_CMU_CFG"         ,    0, 0x00000510, VTSS_IO_OFFSET1(0x01440000), reggrps_within_SD_CMU_TERM_TARGET},
    {"SD_CMU"             ,    1, 0x00000506, VTSS_IO_OFFSET1(0x01418000), reggrps_within_SD10G_CMU_TARGET},
    {"SD_CMU_CFG"         ,    1, 0x00000512, VTSS_IO_OFFSET1(0x01448000), reggrps_within_SD_CMU_NONTERM_TARGET},
    {"SD_CMU"             ,    2, 0x00000508, VTSS_IO_OFFSET1(0x01420000), reggrps_within_SD10G_CMU_TARGET},
    {"SD_CMU_CFG"         ,    2, 0x00000514, VTSS_IO_OFFSET1(0x01450000), reggrps_within_SD_CMU_NONTERM_TARGET},
    {"SD_CMU"             ,    3, 0x0000050a, VTSS_IO_OFFSET1(0x01428000), reggrps_within_SD10G_CMU_TARGET},
    {"SD_CMU_CFG"         ,    3, 0x00000516, VTSS_IO_OFFSET1(0x01458000), reggrps_within_SD_CMU_NONTERM_TARGET},
    {"SD_CMU"             ,    4, 0x0000050c, VTSS_IO_OFFSET1(0x01430000), reggrps_within_SD10G_CMU_TARGET},
    {"SD_CMU_CFG"         ,    4, 0x00000518, VTSS_IO_OFFSET1(0x01460000), reggrps_within_SD_CMU_NONTERM_TARGET},
    {"SD_CMU"             ,    5, 0x0000050e, VTSS_IO_OFFSET1(0x01438000), reggrps_within_SD10G_CMU_TARGET},
    {"SD_CMU_CFG"         ,    5, 0x0000051a, VTSS_IO_OFFSET1(0x01468000), reggrps_within_SD_CMU_NONTERM_TARGET},
    {"SD10G_LANE"         ,    0, 0x0000051c, VTSS_IO_OFFSET1(0x01470000), reggrps_within_SD10G_LANE_TARGET},
    {"SD10G_LANE"         ,    1, 0x0000051e, VTSS_IO_OFFSET1(0x01478000), reggrps_within_SD10G_LANE_TARGET},
    {"SD10G_LANE"         ,    2, 0x00000520, VTSS_IO_OFFSET1(0x01480000), reggrps_within_SD10G_LANE_TARGET},
    {"SD10G_LANE"         ,    3, 0x00000522, VTSS_IO_OFFSET1(0x01488000), reggrps_within_SD10G_LANE_TARGET},
    {"SD10G_LANE"         ,    4, 0x00000524, VTSS_IO_OFFSET1(0x01490000), reggrps_within_SD10G_LANE_TARGET},
    {"SD10G_LANE"         ,    5, 0x00000526, VTSS_IO_OFFSET1(0x01498000), reggrps_within_SD10G_LANE_TARGET},
    {"SD10G_LANE"         ,    6, 0x00000528, VTSS_IO_OFFSET1(0x014a0000), reggrps_within_SD10G_LANE_TARGET},
    {"SD10G_LANE"         ,    7, 0x0000052a, VTSS_IO_OFFSET1(0x014a8000), reggrps_within_SD10G_LANE_TARGET},
    {"SD10G_LANE"         ,    8, 0x0000052c, VTSS_IO_OFFSET1(0x014b0000), reggrps_within_SD10G_LANE_TARGET},
    {"SD10G_LANE"         ,    9, 0x0000052e, VTSS_IO_OFFSET1(0x014b8000), reggrps_within_SD10G_LANE_TARGET},
    {"SD10G_KR"           ,    0, 0x00000530, VTSS_IO_OFFSET1(0x014c0000), reggrps_within_IP_KRANEG},
    {"SD10G_KR"           ,    1, 0x00000532, VTSS_IO_OFFSET1(0x014c8000), reggrps_within_IP_KRANEG},
    {"SD10G_KR"           ,    2, 0x00000534, VTSS_IO_OFFSET1(0x014d0000), reggrps_within_IP_KRANEG},
    {"SD10G_KR"           ,    3, 0x00000536, VTSS_IO_OFFSET1(0x014d8000), reggrps_within_IP_KRANEG},
    {"SD10G_KR"           ,    4, 0x00000538, VTSS_IO_OFFSET1(0x014e0000), reggrps_within_IP_KRANEG},
    {"SD10G_KR"           ,    5, 0x0000053a, VTSS_IO_OFFSET1(0x014e8000), reggrps_within_IP_KRANEG},
    {"SD10G_KR"           ,    6, 0x0000053c, VTSS_IO_OFFSET1(0x014f0000), reggrps_within_IP_KRANEG},
    {"SD10G_KR"           ,    7, 0x0000053e, VTSS_IO_OFFSET1(0x014f8000), reggrps_within_IP_KRANEG},
    {"SD10G_KR"           ,    8, 0x00000540, VTSS_IO_OFFSET1(0x01500000), reggrps_within_IP_KRANEG},
    {"SD10G_KR"           ,    9, 0x00000542, VTSS_IO_OFFSET1(0x01508000), reggrps_within_IP_KRANEG},
    {"SD_LANE"            ,    0, 0x00000544, VTSS_IO_OFFSET1(0x01510000), reggrps_within_SD_LANE_TARGET},
    {"SD_LANE"            ,    1, 0x00000546, VTSS_IO_OFFSET1(0x01518000), reggrps_within_SD_LANE_TARGET},
    {"SD_LANE"            ,    2, 0x00000548, VTSS_IO_OFFSET1(0x01520000), reggrps_within_SD_LANE_TARGET},
    {"SD_LANE"            ,    3, 0x0000054a, VTSS_IO_OFFSET1(0x01528000), reggrps_within_SD_LANE_TARGET},
    {"SD_LANE"            ,    4, 0x0000054c, VTSS_IO_OFFSET1(0x01530000), reggrps_within_SD_LANE_TARGET},
    {"SD_LANE"            ,    5, 0x0000054e, VTSS_IO_OFFSET1(0x01538000), reggrps_within_SD_LANE_TARGET},
    {"SD_LANE"            ,    6, 0x00000550, VTSS_IO_OFFSET1(0x01540000), reggrps_within_SD_LANE_TARGET},
    {"SD_LANE"            ,    7, 0x00000552, VTSS_IO_OFFSET1(0x01548000), reggrps_within_SD_LANE_TARGET},
    {"SD_LANE"            ,    8, 0x00000554, VTSS_IO_OFFSET1(0x01550000), reggrps_within_SD_LANE_TARGET},
    {"SD_LANE"            ,    9, 0x00000556, VTSS_IO_OFFSET1(0x01558000), reggrps_within_SD_LANE_TARGET},
    {"VCAP_ES0"           ,   -1, 0x00000038, VTSS_IO_OFFSET1(0x000e0000), reggrps_within_VCAP_ES0},
    {"VCAP_ES2"           ,   -1, 0x00000034, VTSS_IO_OFFSET1(0x000d0000), reggrps_within_VCAP_ES2},
    {"VCAP_IP6PFX"        ,   -1, 0x00000024, VTSS_IO_OFFSET1(0x00090000), reggrps_within_VCAP_IP6PFX},
    {"VCAP_SUPER"         ,   -1, 0x00000020, VTSS_IO_OFFSET1(0x00080000), reggrps_within_VCAP_SUPER},
    {"VOP"                ,   -1, 0x00000280, VTSS_IO_OFFSET1(0x00a00000), reggrps_within_VOP},
    {"VOP_L3"             ,   -1, 0x000002c0, VTSS_IO_OFFSET1(0x00b00000), reggrps_within_VOP_L3},
    {"VOP_MPLS"           ,   -1, 0x000001a0, VTSS_IO_OFFSET1(0x00680000), reggrps_within_VOP_MPLS},
    {"XQS"                ,   -1, 0x00000030, VTSS_IO_OFFSET1(0x000c0000), reggrps_within_XQS},
};

#define SYMREG_REPL_CNT_MAX 5120
#define SYMREG_NAME_LEN_MAX 47
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
#endif /* VTSS_ARCH_LAGUNA */
