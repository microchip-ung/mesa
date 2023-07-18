// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


// This file has been done by merging auto-generated files vtss_fa_vcap.h and laguna/vtss_laguna_vcap.h.

/* ================================================================= *
 *  VCAP CLM
 * ================================================================= */

/* CLM X12 key types */
#define CLM_X12_TYPE_NORMAL_7TUPLE                   0
#define CLM_X12_TYPE_CUSTOM_1                        1

/* CLM X12 common key fields */
#define CLM_KO_X12_TYPE                              0
#define CLM_KL_X12_TYPE                              1
#define CLM_KO_X12_FIRST                             (CLM_KO_X12_TYPE + CLM_KL_X12_TYPE)
#define CLM_KL_X12_FIRST                             1
#define CLM_KO_X12_G_IDX_SEL                         (CLM_KO_X12_FIRST + CLM_KL_X12_FIRST)
#define CLM_KL_X12_G_IDX_SEL                         2
#define CLM_KO_X12_G_IDX                             (CLM_KO_X12_G_IDX_SEL + CLM_KL_X12_G_IDX_SEL)
#define CLM_KL_X12_G_IDX                             (FA_TGT ? 12 : 10)

/* CLM X12 NORMAL_7TUPLE key fields */
#define CLM_KO_NORMAL_7TUPLE_IGR_PORT_MASK_SEL       (CLM_KO_X12_G_IDX + CLM_KL_X12_G_IDX)
#define CLM_KL_NORMAL_7TUPLE_IGR_PORT_MASK_SEL       2
#define CLM_KO_NORMAL_7TUPLE_IGR_PORT_MASK_0         (CLM_KO_NORMAL_7TUPLE_IGR_PORT_MASK_SEL + CLM_KL_NORMAL_7TUPLE_IGR_PORT_MASK_SEL)
#define CLM_KL_NORMAL_7TUPLE_IGR_PORT_MASK_0         32
#define CLM_KO_NORMAL_7TUPLE_IGR_PORT_MASK_1         (CLM_KO_NORMAL_7TUPLE_IGR_PORT_MASK_0 + CLM_KL_NORMAL_7TUPLE_IGR_PORT_MASK_0)
#define CLM_KL_NORMAL_7TUPLE_IGR_PORT_MASK_1         32
#define CLM_KO_NORMAL_7TUPLE_IGR_PORT_MASK_2         (CLM_KO_NORMAL_7TUPLE_IGR_PORT_MASK_1 + CLM_KL_NORMAL_7TUPLE_IGR_PORT_MASK_1)
#define CLM_KL_NORMAL_7TUPLE_IGR_PORT_MASK_2         1
#define CLM_KO_NORMAL_7TUPLE_L2_MC                   (CLM_KO_NORMAL_7TUPLE_IGR_PORT_MASK_2 + CLM_KL_NORMAL_7TUPLE_IGR_PORT_MASK_2)
#define CLM_KL_NORMAL_7TUPLE_L2_MC                   1
#define CLM_KO_NORMAL_7TUPLE_L2_BC                   (CLM_KO_NORMAL_7TUPLE_L2_MC + CLM_KL_NORMAL_7TUPLE_L2_MC)
#define CLM_KL_NORMAL_7TUPLE_L2_BC                   1
#define CLM_KO_NORMAL_7TUPLE_VLAN_TAGS               (CLM_KO_NORMAL_7TUPLE_L2_BC + CLM_KL_NORMAL_7TUPLE_L2_BC)
#define CLM_KL_NORMAL_7TUPLE_VLAN_TAGS               3
#define CLM_KO_NORMAL_7TUPLE_TPID0                   (CLM_KO_NORMAL_7TUPLE_VLAN_TAGS + CLM_KL_NORMAL_7TUPLE_VLAN_TAGS)
#define CLM_KL_NORMAL_7TUPLE_TPID0                   3
#define CLM_KO_NORMAL_7TUPLE_PCP0                    (CLM_KO_NORMAL_7TUPLE_TPID0 + CLM_KL_NORMAL_7TUPLE_TPID0)
#define CLM_KL_NORMAL_7TUPLE_PCP0                    3
#define CLM_KO_NORMAL_7TUPLE_DEI0                    (CLM_KO_NORMAL_7TUPLE_PCP0 + CLM_KL_NORMAL_7TUPLE_PCP0)
#define CLM_KL_NORMAL_7TUPLE_DEI0                    1
#define CLM_KO_NORMAL_7TUPLE_VID0                    (CLM_KO_NORMAL_7TUPLE_DEI0 + CLM_KL_NORMAL_7TUPLE_DEI0)
#define CLM_KL_NORMAL_7TUPLE_VID0                    12
#define CLM_KO_NORMAL_7TUPLE_TPID1                   (CLM_KO_NORMAL_7TUPLE_VID0 + CLM_KL_NORMAL_7TUPLE_VID0)
#define CLM_KL_NORMAL_7TUPLE_TPID1                   3
#define CLM_KO_NORMAL_7TUPLE_PCP1                    (CLM_KO_NORMAL_7TUPLE_TPID1 + CLM_KL_NORMAL_7TUPLE_TPID1)
#define CLM_KL_NORMAL_7TUPLE_PCP1                    3
#define CLM_KO_NORMAL_7TUPLE_DEI1                    (CLM_KO_NORMAL_7TUPLE_PCP1 + CLM_KL_NORMAL_7TUPLE_PCP1)
#define CLM_KL_NORMAL_7TUPLE_DEI1                    1
#define CLM_KO_NORMAL_7TUPLE_VID1                    (CLM_KO_NORMAL_7TUPLE_DEI1 + CLM_KL_NORMAL_7TUPLE_DEI1)
#define CLM_KL_NORMAL_7TUPLE_VID1                    12
#define CLM_KO_NORMAL_7TUPLE_TPID2                   (CLM_KO_NORMAL_7TUPLE_VID1 + CLM_KL_NORMAL_7TUPLE_VID1)
#define CLM_KL_NORMAL_7TUPLE_TPID2                   3
#define CLM_KO_NORMAL_7TUPLE_PCP2                    (CLM_KO_NORMAL_7TUPLE_TPID2 + CLM_KL_NORMAL_7TUPLE_TPID2)
#define CLM_KL_NORMAL_7TUPLE_PCP2                    3
#define CLM_KO_NORMAL_7TUPLE_DEI2                    (CLM_KO_NORMAL_7TUPLE_PCP2 + CLM_KL_NORMAL_7TUPLE_PCP2)
#define CLM_KL_NORMAL_7TUPLE_DEI2                    1
#define CLM_KO_NORMAL_7TUPLE_VID2                    (CLM_KO_NORMAL_7TUPLE_DEI2 + CLM_KL_NORMAL_7TUPLE_DEI2)
#define CLM_KL_NORMAL_7TUPLE_VID2                    12
#define CLM_KO_NORMAL_7TUPLE_L2_DMAC_0               (FA_TGT ? (CLM_KO_NORMAL_7TUPLE_VID2 + CLM_KL_NORMAL_7TUPLE_VID2) : (CLM_KO_NORMAL_7TUPLE_RED_TAGGED + CLM_KL_NORMAL_7TUPLE_RED_TAGGED))
#define CLM_KL_NORMAL_7TUPLE_L2_DMAC_0               32
#define CLM_KO_NORMAL_7TUPLE_L2_DMAC_1               (CLM_KO_NORMAL_7TUPLE_L2_DMAC_0 + CLM_KL_NORMAL_7TUPLE_L2_DMAC_0)
#define CLM_KL_NORMAL_7TUPLE_L2_DMAC_1               16
#define CLM_KO_NORMAL_7TUPLE_L2_SMAC_0               (CLM_KO_NORMAL_7TUPLE_L2_DMAC_1 + CLM_KL_NORMAL_7TUPLE_L2_DMAC_1)
#define CLM_KL_NORMAL_7TUPLE_L2_SMAC_0               32
#define CLM_KO_NORMAL_7TUPLE_L2_SMAC_1               (CLM_KO_NORMAL_7TUPLE_L2_SMAC_0 + CLM_KL_NORMAL_7TUPLE_L2_SMAC_0)
#define CLM_KL_NORMAL_7TUPLE_L2_SMAC_1               16
#define CLM_KO_NORMAL_7TUPLE_IP_MC                   (CLM_KO_NORMAL_7TUPLE_L2_SMAC_1 + CLM_KL_NORMAL_7TUPLE_L2_SMAC_1)
#define CLM_KL_NORMAL_7TUPLE_IP_MC                   1
#define CLM_KO_NORMAL_7TUPLE_ETYPE_LEN               (CLM_KO_NORMAL_7TUPLE_IP_MC + CLM_KL_NORMAL_7TUPLE_IP_MC)
#define CLM_KL_NORMAL_7TUPLE_ETYPE_LEN               1
#define CLM_KO_NORMAL_7TUPLE_ETYPE                   (CLM_KO_NORMAL_7TUPLE_ETYPE_LEN + CLM_KL_NORMAL_7TUPLE_ETYPE_LEN)
#define CLM_KL_NORMAL_7TUPLE_ETYPE                   16
#define CLM_KO_NORMAL_7TUPLE_IP_SNAP                 (CLM_KO_NORMAL_7TUPLE_ETYPE + CLM_KL_NORMAL_7TUPLE_ETYPE)
#define CLM_KL_NORMAL_7TUPLE_IP_SNAP                 1
#define CLM_KO_NORMAL_7TUPLE_IP4                     (CLM_KO_NORMAL_7TUPLE_IP_SNAP + CLM_KL_NORMAL_7TUPLE_IP_SNAP)
#define CLM_KL_NORMAL_7TUPLE_IP4                     1
#define CLM_KO_NORMAL_7TUPLE_L3_FRAGMENT_TYPE        (CLM_KO_NORMAL_7TUPLE_IP4 + CLM_KL_NORMAL_7TUPLE_IP4)
#define CLM_KL_NORMAL_7TUPLE_L3_FRAGMENT_TYPE        2
#define CLM_KO_NORMAL_7TUPLE_L3_FRAG_INVLD_L4_LEN    (CLM_KO_NORMAL_7TUPLE_L3_FRAGMENT_TYPE + CLM_KL_NORMAL_7TUPLE_L3_FRAGMENT_TYPE)
#define CLM_KL_NORMAL_7TUPLE_L3_FRAG_INVLD_L4_LEN    1
#define CLM_KO_NORMAL_7TUPLE_L3_OPTIONS              (CLM_KO_NORMAL_7TUPLE_L3_FRAG_INVLD_L4_LEN + CLM_KL_NORMAL_7TUPLE_L3_FRAG_INVLD_L4_LEN)
#define CLM_KL_NORMAL_7TUPLE_L3_OPTIONS              1
#define CLM_KO_NORMAL_7TUPLE_L3_DSCP                 (CLM_KO_NORMAL_7TUPLE_L3_OPTIONS + CLM_KL_NORMAL_7TUPLE_L3_OPTIONS)
#define CLM_KL_NORMAL_7TUPLE_L3_DSCP                 6
#define CLM_KO_NORMAL_7TUPLE_L3_IP6_DIP_0            (CLM_KO_NORMAL_7TUPLE_L3_DSCP + CLM_KL_NORMAL_7TUPLE_L3_DSCP)
#define CLM_KL_NORMAL_7TUPLE_L3_IP6_DIP_0            32
#define CLM_KO_NORMAL_7TUPLE_L3_IP6_DIP_1            (CLM_KO_NORMAL_7TUPLE_L3_IP6_DIP_0 + CLM_KL_NORMAL_7TUPLE_L3_IP6_DIP_0)
#define CLM_KL_NORMAL_7TUPLE_L3_IP6_DIP_1            32
#define CLM_KO_NORMAL_7TUPLE_L3_IP6_DIP_2            (CLM_KO_NORMAL_7TUPLE_L3_IP6_DIP_1 + CLM_KL_NORMAL_7TUPLE_L3_IP6_DIP_1)
#define CLM_KL_NORMAL_7TUPLE_L3_IP6_DIP_2            32
#define CLM_KO_NORMAL_7TUPLE_L3_IP6_DIP_3            (CLM_KO_NORMAL_7TUPLE_L3_IP6_DIP_2 + CLM_KL_NORMAL_7TUPLE_L3_IP6_DIP_2)
#define CLM_KL_NORMAL_7TUPLE_L3_IP6_DIP_3            32
#define CLM_KO_NORMAL_7TUPLE_L3_IP6_SIP_0            (CLM_KO_NORMAL_7TUPLE_L3_IP6_DIP_3 + CLM_KL_NORMAL_7TUPLE_L3_IP6_DIP_3)
#define CLM_KL_NORMAL_7TUPLE_L3_IP6_SIP_0            32
#define CLM_KO_NORMAL_7TUPLE_L3_IP6_SIP_1            (CLM_KO_NORMAL_7TUPLE_L3_IP6_SIP_0 + CLM_KL_NORMAL_7TUPLE_L3_IP6_SIP_0)
#define CLM_KL_NORMAL_7TUPLE_L3_IP6_SIP_1            32
#define CLM_KO_NORMAL_7TUPLE_L3_IP6_SIP_2            (CLM_KO_NORMAL_7TUPLE_L3_IP6_SIP_1 + CLM_KL_NORMAL_7TUPLE_L3_IP6_SIP_1)
#define CLM_KL_NORMAL_7TUPLE_L3_IP6_SIP_2            32
#define CLM_KO_NORMAL_7TUPLE_L3_IP6_SIP_3            (CLM_KO_NORMAL_7TUPLE_L3_IP6_SIP_2 + CLM_KL_NORMAL_7TUPLE_L3_IP6_SIP_2)
#define CLM_KL_NORMAL_7TUPLE_L3_IP6_SIP_3            32
#define CLM_KO_NORMAL_7TUPLE_TCP_UDP                 (CLM_KO_NORMAL_7TUPLE_L3_IP6_SIP_3 + CLM_KL_NORMAL_7TUPLE_L3_IP6_SIP_3)
#define CLM_KL_NORMAL_7TUPLE_TCP_UDP                 1
#define CLM_KO_NORMAL_7TUPLE_TCP                     (CLM_KO_NORMAL_7TUPLE_TCP_UDP + CLM_KL_NORMAL_7TUPLE_TCP_UDP)
#define CLM_KL_NORMAL_7TUPLE_TCP                     1
#define CLM_KO_NORMAL_7TUPLE_L4_SPORT                (CLM_KO_NORMAL_7TUPLE_TCP + CLM_KL_NORMAL_7TUPLE_TCP)
#define CLM_KL_NORMAL_7TUPLE_L4_SPORT                16
#define CLM_KO_NORMAL_7TUPLE_L4_RNG                  (CLM_KO_NORMAL_7TUPLE_L4_SPORT + CLM_KL_NORMAL_7TUPLE_L4_SPORT)
#define CLM_KL_NORMAL_7TUPLE_L4_RNG                  8

/* CLM X12 CUSTOM_1 key fields */
#define CLM_KO_CUSTOM_1_CUSTOM_15                    (CLM_KO_X12_G_IDX + CLM_KL_X12_G_IDX)
#define CLM_KL_CUSTOM_1_CUSTOM_15                    32
#define CLM_KO_CUSTOM_1_CUSTOM_14                    (CLM_KO_CUSTOM_1_CUSTOM_15 + CLM_KL_CUSTOM_1_CUSTOM_15)
#define CLM_KL_CUSTOM_1_CUSTOM_14                    32
#define CLM_KO_CUSTOM_1_CUSTOM_13                    (CLM_KO_CUSTOM_1_CUSTOM_14 + CLM_KL_CUSTOM_1_CUSTOM_14)
#define CLM_KL_CUSTOM_1_CUSTOM_13                    32
#define CLM_KO_CUSTOM_1_CUSTOM_12                    (CLM_KO_CUSTOM_1_CUSTOM_13 + CLM_KL_CUSTOM_1_CUSTOM_13)
#define CLM_KL_CUSTOM_1_CUSTOM_12                    32
#define CLM_KO_CUSTOM_1_CUSTOM_11                    (CLM_KO_CUSTOM_1_CUSTOM_12 + CLM_KL_CUSTOM_1_CUSTOM_12)
#define CLM_KL_CUSTOM_1_CUSTOM_11                    32
#define CLM_KO_CUSTOM_1_CUSTOM_10                    (CLM_KO_CUSTOM_1_CUSTOM_11 + CLM_KL_CUSTOM_1_CUSTOM_11)
#define CLM_KL_CUSTOM_1_CUSTOM_10                    32
#define CLM_KO_CUSTOM_1_CUSTOM_9                     (CLM_KO_CUSTOM_1_CUSTOM_10 + CLM_KL_CUSTOM_1_CUSTOM_10)
#define CLM_KL_CUSTOM_1_CUSTOM_9                     32
#define CLM_KO_CUSTOM_1_CUSTOM_8                     (CLM_KO_CUSTOM_1_CUSTOM_9 + CLM_KL_CUSTOM_1_CUSTOM_9)
#define CLM_KL_CUSTOM_1_CUSTOM_8                     32
#define CLM_KO_CUSTOM_1_CUSTOM_7                     (CLM_KO_CUSTOM_1_CUSTOM_8 + CLM_KL_CUSTOM_1_CUSTOM_8)
#define CLM_KL_CUSTOM_1_CUSTOM_7                     32
#define CLM_KO_CUSTOM_1_CUSTOM_6                     (CLM_KO_CUSTOM_1_CUSTOM_7 + CLM_KL_CUSTOM_1_CUSTOM_7)
#define CLM_KL_CUSTOM_1_CUSTOM_6                     32
#define CLM_KO_CUSTOM_1_CUSTOM_5                     (CLM_KO_CUSTOM_1_CUSTOM_6 + CLM_KL_CUSTOM_1_CUSTOM_6)
#define CLM_KL_CUSTOM_1_CUSTOM_5                     32
#define CLM_KO_CUSTOM_1_CUSTOM_4                     (CLM_KO_CUSTOM_1_CUSTOM_5 + CLM_KL_CUSTOM_1_CUSTOM_5)
#define CLM_KL_CUSTOM_1_CUSTOM_4                     32
#define CLM_KO_CUSTOM_1_CUSTOM_3                     (CLM_KO_CUSTOM_1_CUSTOM_4 + CLM_KL_CUSTOM_1_CUSTOM_4)
#define CLM_KL_CUSTOM_1_CUSTOM_3                     32
#define CLM_KO_CUSTOM_1_CUSTOM_2                     (CLM_KO_CUSTOM_1_CUSTOM_3 + CLM_KL_CUSTOM_1_CUSTOM_3)
#define CLM_KL_CUSTOM_1_CUSTOM_2                     32
#define CLM_KO_CUSTOM_1_CUSTOM_1                     (CLM_KO_CUSTOM_1_CUSTOM_2 + CLM_KL_CUSTOM_1_CUSTOM_2)
#define CLM_KL_CUSTOM_1_CUSTOM_1                     32
#define CLM_KO_CUSTOM_1_CUSTOM_0                     (CLM_KO_CUSTOM_1_CUSTOM_1 + CLM_KL_CUSTOM_1_CUSTOM_1)
#define CLM_KL_CUSTOM_1_CUSTOM_0                     32

/* CLM X6 key types */
#define CLM_X6_TYPE_LL_FULL                          0
#define CLM_X6_TYPE_NORMAL                           1
#define CLM_X6_TYPE_NORMAL_5TUPLE_IP4                2
#define CLM_X6_TYPE_CUSTOM_2                         3

/* CLM X6 common key fields */
#define CLM_KO_X6_TYPE                               0
#define CLM_KL_X6_TYPE                               2
#define CLM_KO_X6_FIRST                              (CLM_KO_X6_TYPE + CLM_KL_X6_TYPE)
#define CLM_KL_X6_FIRST                              1

#define CLM_KO_X6_G_IDX_SEL                          (CLM_KO_X6_FIRST + CLM_KL_X6_FIRST)
#define CLM_KL_X6_G_IDX_SEL                          2
#define CLM_KO_X6_G_IDX                              (CLM_KO_X6_G_IDX_SEL + CLM_KL_X6_G_IDX_SEL)
#define CLM_KL_X6_G_IDX                              (FA_TGT ? 12 : 10)
#define CLM_KO_X6_IGR_PORT_MASK_SEL                  (CLM_KO_X6_G_IDX + CLM_KL_X6_G_IDX)
#define CLM_KL_X6_IGR_PORT_MASK_SEL                  2
#define CLM_KO_X6_IGR_PORT_MASK_0                    (CLM_KO_X6_IGR_PORT_MASK_SEL + CLM_KL_X6_IGR_PORT_MASK_SEL)
#define CLM_KL_X6_IGR_PORT_MASK_0                    32
#define CLM_KO_X6_IGR_PORT_MASK_1                    (CLM_KO_X6_IGR_PORT_MASK_0 + CLM_KL_X6_IGR_PORT_MASK_0)
#define CLM_KL_X6_IGR_PORT_MASK_1                    32
#define CLM_KO_X6_IGR_PORT_MASK_2                    (CLM_KO_X6_IGR_PORT_MASK_1 + CLM_KL_X6_IGR_PORT_MASK_1)
#define CLM_KL_X6_IGR_PORT_MASK_2                    1
#define CLM_KO_X6_L2_MC                              (CLM_KO_X6_IGR_PORT_MASK_2 + CLM_KL_X6_IGR_PORT_MASK_2)
#define CLM_KL_X6_L2_MC                              1
#define CLM_KO_X6_L2_BC                              (CLM_KO_X6_L2_MC + CLM_KL_X6_L2_MC)
#define CLM_KL_X6_L2_BC                              1
#define CLM_KO_X6_VLAN_TAGS                          (CLM_KO_X6_L2_BC + CLM_KL_X6_L2_BC)
#define CLM_KL_X6_VLAN_TAGS                          3
#define CLM_KO_X6_TPID0                              (CLM_KO_X6_VLAN_TAGS + CLM_KL_X6_VLAN_TAGS)
#define CLM_KL_X6_TPID0                              3
#define CLM_KO_X6_PCP0                               (CLM_KO_X6_TPID0 + CLM_KL_X6_TPID0)
#define CLM_KL_X6_PCP0                               3
#define CLM_KO_X6_DEI0                               (CLM_KO_X6_PCP0 + CLM_KL_X6_PCP0)
#define CLM_KL_X6_DEI0                               1
#define CLM_KO_X6_VID0                               (CLM_KO_X6_DEI0 + CLM_KL_X6_DEI0)
#define CLM_KL_X6_VID0                               12
#define CLM_KO_X6_TPID1                              (CLM_KO_X6_VID0 + CLM_KL_X6_VID0)
#define CLM_KL_X6_TPID1                              3
#define CLM_KO_X6_PCP1                               (CLM_KO_X6_TPID1 + CLM_KL_X6_TPID1)
#define CLM_KL_X6_PCP1                               3
#define CLM_KO_X6_DEI1                               (CLM_KO_X6_PCP1 + CLM_KL_X6_PCP1)
#define CLM_KL_X6_DEI1                               1
#define CLM_KO_X6_VID1                               (CLM_KO_X6_DEI1 + CLM_KL_X6_DEI1)
#define CLM_KL_X6_VID1                               12
#define CLM_KO_X6_TPID2                              (CLM_KO_X6_VID1 + CLM_KL_X6_VID1)
#define CLM_KL_X6_TPID2                              3
#define CLM_KO_X6_PCP2                               (CLM_KO_X6_TPID2 + CLM_KL_X6_TPID2)
#define CLM_KL_X6_PCP2                               3
#define CLM_KO_X6_DEI2                               (CLM_KO_X6_PCP2 + CLM_KL_X6_PCP2)
#define CLM_KL_X6_DEI2                               1
#define CLM_KO_X6_VID2                               (CLM_KO_X6_DEI2 + CLM_KL_X6_DEI2)
#define CLM_KL_X6_VID2                               12

/* CLM X6 LL_FULL key fields */
#define CLM_KO_LL_FULL_IGR_PORT                      (CLM_KO_X6_FIRST + CLM_KL_X6_FIRST)
#define CLM_KL_LL_FULL_IGR_PORT                      (FA_TGT ? 7 : 6)
#define CLM_KO_LL_FULL_VLAN_TAGS                     (CLM_KO_LL_FULL_IGR_PORT + CLM_KL_LL_FULL_IGR_PORT)
#define CLM_KL_LL_FULL_VLAN_TAGS                     3
#define CLM_KO_LL_FULL_TPID0                         (CLM_KO_LL_FULL_VLAN_TAGS + CLM_KL_LL_FULL_VLAN_TAGS)
#define CLM_KL_LL_FULL_TPID0                         3
#define CLM_KO_LL_FULL_PCP0                          (CLM_KO_LL_FULL_TPID0 + CLM_KL_LL_FULL_TPID0)
#define CLM_KL_LL_FULL_PCP0                          3
#define CLM_KO_LL_FULL_DEI0                          (CLM_KO_LL_FULL_PCP0 + CLM_KL_LL_FULL_PCP0)
#define CLM_KL_LL_FULL_DEI0                          1
#define CLM_KO_LL_FULL_VID0                          (CLM_KO_LL_FULL_DEI0 + CLM_KL_LL_FULL_DEI0)
#define CLM_KL_LL_FULL_VID0                          12
#define CLM_KO_LL_FULL_TPID1                         (CLM_KO_LL_FULL_VID0 + CLM_KL_LL_FULL_VID0)
#define CLM_KL_LL_FULL_TPID1                         3
#define CLM_KO_LL_FULL_PCP1                          (CLM_KO_LL_FULL_TPID1 + CLM_KL_LL_FULL_TPID1)
#define CLM_KL_LL_FULL_PCP1                          3
#define CLM_KO_LL_FULL_DEI1                          (CLM_KO_LL_FULL_PCP1 + CLM_KL_LL_FULL_PCP1)
#define CLM_KL_LL_FULL_DEI1                          1
#define CLM_KO_LL_FULL_VID1                          (CLM_KO_LL_FULL_DEI1 + CLM_KL_LL_FULL_DEI1)
#define CLM_KL_LL_FULL_VID1                          12
#define CLM_KO_LL_FULL_TPID2                         (CLM_KO_LL_FULL_VID1 + CLM_KL_LL_FULL_VID1)
#define CLM_KL_LL_FULL_TPID2                         3
#define CLM_KO_LL_FULL_PCP2                          (CLM_KO_LL_FULL_TPID2 + CLM_KL_LL_FULL_TPID2)
#define CLM_KL_LL_FULL_PCP2                          3
#define CLM_KO_LL_FULL_DEI2                          (CLM_KO_LL_FULL_PCP2 + CLM_KL_LL_FULL_PCP2)
#define CLM_KL_LL_FULL_DEI2                          1
#define CLM_KO_LL_FULL_VID2                          (CLM_KO_LL_FULL_DEI2 + CLM_KL_LL_FULL_DEI2)
#define CLM_KL_LL_FULL_VID2                          12
#define CLM_KO_LL_FULL_L2_DMAC_0                     (FA_TGT ? (CLM_KO_LL_FULL_VID2 + CLM_KL_LL_FULL_VID2) : (CLM_KO_LL_FULL_RED_TAGGED + CLM_KL_LL_FULL_RED_TAGGED))
#define CLM_KL_LL_FULL_L2_DMAC_0                     32
#define CLM_KO_LL_FULL_L2_DMAC_1                     (CLM_KO_LL_FULL_L2_DMAC_0 + CLM_KL_LL_FULL_L2_DMAC_0)
#define CLM_KL_LL_FULL_L2_DMAC_1                     16
#define CLM_KO_LL_FULL_L2_SMAC_0                     (CLM_KO_LL_FULL_L2_DMAC_1 + CLM_KL_LL_FULL_L2_DMAC_1)
#define CLM_KL_LL_FULL_L2_SMAC_0                     32
#define CLM_KO_LL_FULL_L2_SMAC_1                     (CLM_KO_LL_FULL_L2_SMAC_0 + CLM_KL_LL_FULL_L2_SMAC_0)
#define CLM_KL_LL_FULL_L2_SMAC_1                     16
#define CLM_KO_LL_FULL_ETYPE_LEN                     (CLM_KO_LL_FULL_L2_SMAC_1 + CLM_KL_LL_FULL_L2_SMAC_1)
#define CLM_KL_LL_FULL_ETYPE_LEN                     1
#define CLM_KO_LL_FULL_ETYPE                         (CLM_KO_LL_FULL_ETYPE_LEN + CLM_KL_LL_FULL_ETYPE_LEN)
#define CLM_KL_LL_FULL_ETYPE                         16
#define CLM_KO_LL_FULL_IP_SNAP                       (CLM_KO_LL_FULL_ETYPE + CLM_KL_LL_FULL_ETYPE)
#define CLM_KL_LL_FULL_IP_SNAP                       1
#define CLM_KO_LL_FULL_IP4                           (CLM_KO_LL_FULL_IP_SNAP + CLM_KL_LL_FULL_IP_SNAP)
#define CLM_KL_LL_FULL_IP4                           1
#define CLM_KO_LL_FULL_L3_FRAGMENT_TYPE              (CLM_KO_LL_FULL_IP4 + CLM_KL_LL_FULL_IP4)
#define CLM_KL_LL_FULL_L3_FRAGMENT_TYPE              2
#define CLM_KO_LL_FULL_L3_FRAG_INVLD_L4_LEN          (CLM_KO_LL_FULL_L3_FRAGMENT_TYPE + CLM_KL_LL_FULL_L3_FRAGMENT_TYPE)
#define CLM_KL_LL_FULL_L3_FRAG_INVLD_L4_LEN          1
#define CLM_KO_LL_FULL_L3_OPTIONS                    (CLM_KO_LL_FULL_L3_FRAG_INVLD_L4_LEN + CLM_KL_LL_FULL_L3_FRAG_INVLD_L4_LEN)
#define CLM_KL_LL_FULL_L3_OPTIONS                    1
#define CLM_KO_LL_FULL_L3_DSCP                       (CLM_KO_LL_FULL_L3_OPTIONS + CLM_KL_LL_FULL_L3_OPTIONS)
#define CLM_KL_LL_FULL_L3_DSCP                       6
#define CLM_KO_LL_FULL_L3_IP4_DIP                    (CLM_KO_LL_FULL_L3_DSCP + CLM_KL_LL_FULL_L3_DSCP)
#define CLM_KL_LL_FULL_L3_IP4_DIP                    32
#define CLM_KO_LL_FULL_L3_IP4_SIP                    (CLM_KO_LL_FULL_L3_IP4_DIP + CLM_KL_LL_FULL_L3_IP4_DIP)
#define CLM_KL_LL_FULL_L3_IP4_SIP                    32
#define CLM_KO_LL_FULL_TCP_UDP                       (CLM_KO_LL_FULL_L3_IP4_SIP + CLM_KL_LL_FULL_L3_IP4_SIP)
#define CLM_KL_LL_FULL_TCP_UDP                       1
#define CLM_KO_LL_FULL_TCP                           (CLM_KO_LL_FULL_TCP_UDP + CLM_KL_LL_FULL_TCP_UDP)
#define CLM_KL_LL_FULL_TCP                           1
#define CLM_KO_LL_FULL_L4_SPORT                      (CLM_KO_LL_FULL_TCP + CLM_KL_LL_FULL_TCP)
#define CLM_KL_LL_FULL_L4_SPORT                      16
#define CLM_KO_LL_FULL_L4_RNG                        (CLM_KO_LL_FULL_L4_SPORT + CLM_KL_LL_FULL_L4_SPORT)
#define CLM_KL_LL_FULL_L4_RNG                        8

/* CLM X6 NORMAL key fields */
#define CLM_KO_NORMAL_DST_ENTRY                      (FA_TGT ? (CLM_KO_X6_VID2 + CLM_KL_X6_VID2) : (CLM_KO_X6_RED_TAGGED + CLM_KL_X6_RED_TAGGED))
#define CLM_KL_NORMAL_DST_ENTRY                      1
#define CLM_KO_NORMAL_L2_SMAC_0                      (CLM_KO_NORMAL_DST_ENTRY + CLM_KL_NORMAL_DST_ENTRY)
#define CLM_KL_NORMAL_L2_SMAC_0                      32
#define CLM_KO_NORMAL_L2_SMAC_1                      (CLM_KO_NORMAL_L2_SMAC_0 + CLM_KL_NORMAL_L2_SMAC_0)
#define CLM_KL_NORMAL_L2_SMAC_1                      16
#define CLM_KO_NORMAL_IP_MC                          (CLM_KO_NORMAL_L2_SMAC_1 + CLM_KL_NORMAL_L2_SMAC_1)
#define CLM_KL_NORMAL_IP_MC                          1
#define CLM_KO_NORMAL_ETYPE_LEN                      (CLM_KO_NORMAL_IP_MC + CLM_KL_NORMAL_IP_MC)
#define CLM_KL_NORMAL_ETYPE_LEN                      1
#define CLM_KO_NORMAL_ETYPE                          (CLM_KO_NORMAL_ETYPE_LEN + CLM_KL_NORMAL_ETYPE_LEN)
#define CLM_KL_NORMAL_ETYPE                          16
#define CLM_KO_NORMAL_IP_SNAP                        (CLM_KO_NORMAL_ETYPE + CLM_KL_NORMAL_ETYPE)
#define CLM_KL_NORMAL_IP_SNAP                        1
#define CLM_KO_NORMAL_IP4                            (CLM_KO_NORMAL_IP_SNAP + CLM_KL_NORMAL_IP_SNAP)
#define CLM_KL_NORMAL_IP4                            1
#define CLM_KO_NORMAL_L3_FRAGMENT_TYPE               (CLM_KO_NORMAL_IP4 + CLM_KL_NORMAL_IP4)
#define CLM_KL_NORMAL_L3_FRAGMENT_TYPE               2
#define CLM_KO_NORMAL_L3_FRAG_INVLD_L4_LEN           (CLM_KO_NORMAL_L3_FRAGMENT_TYPE + CLM_KL_NORMAL_L3_FRAGMENT_TYPE)
#define CLM_KL_NORMAL_L3_FRAG_INVLD_L4_LEN           1
#define CLM_KO_NORMAL_L3_OPTIONS                     (CLM_KO_NORMAL_L3_FRAG_INVLD_L4_LEN + CLM_KL_NORMAL_L3_FRAG_INVLD_L4_LEN)
#define CLM_KL_NORMAL_L3_OPTIONS                     1
#define CLM_KO_NORMAL_L3_DSCP                        (CLM_KO_NORMAL_L3_OPTIONS + CLM_KL_NORMAL_L3_OPTIONS)
#define CLM_KL_NORMAL_L3_DSCP                        6
#define CLM_KO_NORMAL_L3_IP4_SIP                     (CLM_KO_NORMAL_L3_DSCP + CLM_KL_NORMAL_L3_DSCP)
#define CLM_KL_NORMAL_L3_IP4_SIP                     32
#define CLM_KO_NORMAL_TCP_UDP                        (CLM_KO_NORMAL_L3_IP4_SIP + CLM_KL_NORMAL_L3_IP4_SIP)
#define CLM_KL_NORMAL_TCP_UDP                        1
#define CLM_KO_NORMAL_TCP                            (CLM_KO_NORMAL_TCP_UDP + CLM_KL_NORMAL_TCP_UDP)
#define CLM_KL_NORMAL_TCP                            1
#define CLM_KO_NORMAL_L4_SPORT                       (CLM_KO_NORMAL_TCP + CLM_KL_NORMAL_TCP)
#define CLM_KL_NORMAL_L4_SPORT                       16
#define CLM_KO_NORMAL_L4_RNG                         (CLM_KO_NORMAL_L4_SPORT + CLM_KL_NORMAL_L4_SPORT)
#define CLM_KL_NORMAL_L4_RNG                         8

/* CLM X6 NORMAL_5TUPLE_IP4 key fields */
#define CLM_KO_NORMAL_5TUPLE_IP4_IP_MC               (FA_TGT ? (CLM_KO_X6_VID2 + CLM_KL_X6_VID2) : (CLM_KO_X6_RED_TAGGED + CLM_KL_X6_RED_TAGGED))
#define CLM_KL_NORMAL_5TUPLE_IP4_IP_MC               1
#define CLM_KO_NORMAL_5TUPLE_IP4_IP4                 (CLM_KO_NORMAL_5TUPLE_IP4_IP_MC + CLM_KL_NORMAL_5TUPLE_IP4_IP_MC)
#define CLM_KL_NORMAL_5TUPLE_IP4_IP4                 1
#define CLM_KO_NORMAL_5TUPLE_IP4_L3_FRAGMENT_TYPE    (CLM_KO_NORMAL_5TUPLE_IP4_IP4 + CLM_KL_NORMAL_5TUPLE_IP4_IP4)
#define CLM_KL_NORMAL_5TUPLE_IP4_L3_FRAGMENT_TYPE    2
#define CLM_KO_NORMAL_5TUPLE_IP4_L3_FRAG_INVLD_L4_LEN (CLM_KO_NORMAL_5TUPLE_IP4_L3_FRAGMENT_TYPE + CLM_KL_NORMAL_5TUPLE_IP4_L3_FRAGMENT_TYPE)
#define CLM_KL_NORMAL_5TUPLE_IP4_L3_FRAG_INVLD_L4_LEN 1
#define CLM_KO_NORMAL_5TUPLE_IP4_L3_OPTIONS          (CLM_KO_NORMAL_5TUPLE_IP4_L3_FRAG_INVLD_L4_LEN + CLM_KL_NORMAL_5TUPLE_IP4_L3_FRAG_INVLD_L4_LEN)
#define CLM_KL_NORMAL_5TUPLE_IP4_L3_OPTIONS          1
#define CLM_KO_NORMAL_5TUPLE_IP4_L3_DSCP             (CLM_KO_NORMAL_5TUPLE_IP4_L3_OPTIONS + CLM_KL_NORMAL_5TUPLE_IP4_L3_OPTIONS)
#define CLM_KL_NORMAL_5TUPLE_IP4_L3_DSCP             6
#define CLM_KO_NORMAL_5TUPLE_IP4_L3_IP4_DIP          (CLM_KO_NORMAL_5TUPLE_IP4_L3_DSCP + CLM_KL_NORMAL_5TUPLE_IP4_L3_DSCP)
#define CLM_KL_NORMAL_5TUPLE_IP4_L3_IP4_DIP          32
#define CLM_KO_NORMAL_5TUPLE_IP4_L3_IP4_SIP          (CLM_KO_NORMAL_5TUPLE_IP4_L3_IP4_DIP + CLM_KL_NORMAL_5TUPLE_IP4_L3_IP4_DIP)
#define CLM_KL_NORMAL_5TUPLE_IP4_L3_IP4_SIP          32
#define CLM_KO_NORMAL_5TUPLE_IP4_L3_IP_PROTO         (CLM_KO_NORMAL_5TUPLE_IP4_L3_IP4_SIP + CLM_KL_NORMAL_5TUPLE_IP4_L3_IP4_SIP)
#define CLM_KL_NORMAL_5TUPLE_IP4_L3_IP_PROTO         8
#define CLM_KO_NORMAL_5TUPLE_IP4_TCP_UDP             (CLM_KO_NORMAL_5TUPLE_IP4_L3_IP_PROTO + CLM_KL_NORMAL_5TUPLE_IP4_L3_IP_PROTO)
#define CLM_KL_NORMAL_5TUPLE_IP4_TCP_UDP             1
#define CLM_KO_NORMAL_5TUPLE_IP4_TCP                 (CLM_KO_NORMAL_5TUPLE_IP4_TCP_UDP + CLM_KL_NORMAL_5TUPLE_IP4_TCP_UDP)
#define CLM_KL_NORMAL_5TUPLE_IP4_TCP                 1
#define CLM_KO_NORMAL_5TUPLE_IP4_L4_RNG              (CLM_KO_NORMAL_5TUPLE_IP4_TCP + CLM_KL_NORMAL_5TUPLE_IP4_TCP)
#define CLM_KL_NORMAL_5TUPLE_IP4_L4_RNG              8
#define CLM_KO_NORMAL_5TUPLE_IP4_IP_PAYLOAD_5TUPLE   (CLM_KO_NORMAL_5TUPLE_IP4_L4_RNG + CLM_KL_NORMAL_5TUPLE_IP4_L4_RNG)
#define CLM_KL_NORMAL_5TUPLE_IP4_IP_PAYLOAD_5TUPLE   32

/* CLM X6 CUSTOM_2 key fields */
#define CLM_KO_CUSTOM_2_CUSTOM_7                     (CLM_KO_X6_G_IDX + CLM_KL_X6_G_IDX)
#define CLM_KL_CUSTOM_2_CUSTOM_7                     32
#define CLM_KO_CUSTOM_2_CUSTOM_6                     (CLM_KO_CUSTOM_2_CUSTOM_7 + CLM_KL_CUSTOM_2_CUSTOM_7)
#define CLM_KL_CUSTOM_2_CUSTOM_6                     32
#define CLM_KO_CUSTOM_2_CUSTOM_5                     (CLM_KO_CUSTOM_2_CUSTOM_6 + CLM_KL_CUSTOM_2_CUSTOM_6)
#define CLM_KL_CUSTOM_2_CUSTOM_5                     32
#define CLM_KO_CUSTOM_2_CUSTOM_4                     (CLM_KO_CUSTOM_2_CUSTOM_5 + CLM_KL_CUSTOM_2_CUSTOM_5)
#define CLM_KL_CUSTOM_2_CUSTOM_4                     32
#define CLM_KO_CUSTOM_2_CUSTOM_3                     (CLM_KO_CUSTOM_2_CUSTOM_4 + CLM_KL_CUSTOM_2_CUSTOM_4)
#define CLM_KL_CUSTOM_2_CUSTOM_3                     32
#define CLM_KO_CUSTOM_2_CUSTOM_2                     (CLM_KO_CUSTOM_2_CUSTOM_3 + CLM_KL_CUSTOM_2_CUSTOM_3)
#define CLM_KL_CUSTOM_2_CUSTOM_2                     32
#define CLM_KO_CUSTOM_2_CUSTOM_1                     (CLM_KO_CUSTOM_2_CUSTOM_2 + CLM_KL_CUSTOM_2_CUSTOM_2)
#define CLM_KL_CUSTOM_2_CUSTOM_1                     32
#define CLM_KO_CUSTOM_2_CUSTOM_0                     (CLM_KO_CUSTOM_2_CUSTOM_1 + CLM_KL_CUSTOM_2_CUSTOM_1)
#define CLM_KL_CUSTOM_2_CUSTOM_0                     32

/* CLM X3 key types */
#define CLM_X3_TYPE_MLL                              0
#define CLM_X3_TYPE_TRI_MLBS                         1
#define CLM_X3_TYPE_PURE_5TUPLE_IP4                  2
#define CLM_X3_TYPE_CUSTOM_4                         3

/* CLM X3 common key fields */
#define CLM_KO_X3_TYPE                               0
#define CLM_KL_X3_TYPE                               2
#define CLM_KO_X3_FIRST                              (CLM_KO_X3_TYPE + CLM_KL_X3_TYPE)
#define CLM_KL_X3_FIRST                              1

#define CLM_KO_X3_G_IDX_SEL                          (CLM_KO_X3_FIRST + CLM_KL_X3_FIRST)
#define CLM_KL_X3_G_IDX_SEL                          2
#define CLM_KO_X3_G_IDX                              (CLM_KO_X3_G_IDX_SEL + CLM_KL_X3_G_IDX_SEL)
#define CLM_KL_X3_G_IDX                              (FA_TGT ? 12 : 10)

/* CLM X3 MLL key fields */
#define CLM_KO_MLL_IGR_PORT                          (CLM_KO_X3_FIRST + CLM_KL_X3_FIRST)
#define CLM_KL_MLL_IGR_PORT                          (FA_TGT ? 7 : 6)
#define CLM_KO_MLL_VLAN_TAGS                         (CLM_KO_MLL_IGR_PORT + CLM_KL_MLL_IGR_PORT)
#define CLM_KL_MLL_VLAN_TAGS                         3
#define CLM_KO_MLL_TPID0                             (CLM_KO_MLL_VLAN_TAGS + CLM_KL_MLL_VLAN_TAGS)
#define CLM_KL_MLL_TPID0                             3
#define CLM_KO_MLL_VID0                              (CLM_KO_MLL_TPID0 + CLM_KL_MLL_TPID0)
#define CLM_KL_MLL_VID0                              12
#define CLM_KO_MLL_TPID1                             (CLM_KO_MLL_VID0 + CLM_KL_MLL_VID0)
#define CLM_KL_MLL_TPID1                             3
#define CLM_KO_MLL_VID1                              (CLM_KO_MLL_TPID1 + CLM_KL_MLL_TPID1)
#define CLM_KL_MLL_VID1                              12
#define CLM_KO_MLL_L2_DMAC_0                         (FA_TGT ? (CLM_KO_MLL_VID1 + CLM_KL_MLL_VID1) : (CLM_KO_MLL_RED_TAGGED + CLM_KL_MLL_RED_TAGGED))
#define CLM_KL_MLL_L2_DMAC_0                         32
#define CLM_KO_MLL_L2_DMAC_1                         (CLM_KO_MLL_L2_DMAC_0 + CLM_KL_MLL_L2_DMAC_0)
#define CLM_KL_MLL_L2_DMAC_1                         16
#define CLM_KO_MLL_L2_SMAC_0                         (CLM_KO_MLL_L2_DMAC_1 + CLM_KL_MLL_L2_DMAC_1)
#define CLM_KL_MLL_L2_SMAC_0                         32
#define CLM_KO_MLL_L2_SMAC_1                         (CLM_KO_MLL_L2_SMAC_0 + CLM_KL_MLL_L2_SMAC_0)
#define CLM_KL_MLL_L2_SMAC_1                         16
#define CLM_KO_MLL_ETYPE_MPLS                        (CLM_KO_MLL_L2_SMAC_1 + CLM_KL_MLL_L2_SMAC_1)
#define CLM_KL_MLL_ETYPE_MPLS                        2
#define CLM_KO_MLL_L4_RNG                            (CLM_KO_MLL_ETYPE_MPLS + CLM_KL_MLL_ETYPE_MPLS)
#define CLM_KL_MLL_L4_RNG                            8

/* CLM X3 TRI_MLBS key fields */
#define CLM_KO_TRI_MLBS_LBL0                         (CLM_KO_X3_G_IDX + CLM_KL_X3_G_IDX)
#define CLM_KL_TRI_MLBS_LBL0                         20
#define CLM_KO_TRI_MLBS_TC0                          (CLM_KO_TRI_MLBS_LBL0 + CLM_KL_TRI_MLBS_LBL0)
#define CLM_KL_TRI_MLBS_TC0                          3
#define CLM_KO_TRI_MLBS_SBIT0                        (CLM_KO_TRI_MLBS_TC0 + CLM_KL_TRI_MLBS_TC0)
#define CLM_KL_TRI_MLBS_SBIT0                        1
#define CLM_KO_TRI_MLBS_TTL0_EXPIRY                  (CLM_KO_TRI_MLBS_SBIT0 + CLM_KL_TRI_MLBS_SBIT0)
#define CLM_KL_TRI_MLBS_TTL0_EXPIRY                  1
#define CLM_KO_TRI_MLBS_LBL1                         (CLM_KO_TRI_MLBS_TTL0_EXPIRY + CLM_KL_TRI_MLBS_TTL0_EXPIRY)
#define CLM_KL_TRI_MLBS_LBL1                         20
#define CLM_KO_TRI_MLBS_TC1                          (CLM_KO_TRI_MLBS_LBL1 + CLM_KL_TRI_MLBS_LBL1)
#define CLM_KL_TRI_MLBS_TC1                          3
#define CLM_KO_TRI_MLBS_SBIT1                        (CLM_KO_TRI_MLBS_TC1 + CLM_KL_TRI_MLBS_TC1)
#define CLM_KL_TRI_MLBS_SBIT1                        1
#define CLM_KO_TRI_MLBS_TTL1_EXPIRY                  (CLM_KO_TRI_MLBS_SBIT1 + CLM_KL_TRI_MLBS_SBIT1)
#define CLM_KL_TRI_MLBS_TTL1_EXPIRY                  1
#define CLM_KO_TRI_MLBS_LBL2                         (CLM_KO_TRI_MLBS_TTL1_EXPIRY + CLM_KL_TRI_MLBS_TTL1_EXPIRY)
#define CLM_KL_TRI_MLBS_LBL2                         20
#define CLM_KO_TRI_MLBS_TC2                          (CLM_KO_TRI_MLBS_LBL2 + CLM_KL_TRI_MLBS_LBL2)
#define CLM_KL_TRI_MLBS_TC2                          3
#define CLM_KO_TRI_MLBS_SBIT2                        (CLM_KO_TRI_MLBS_TC2 + CLM_KL_TRI_MLBS_TC2)
#define CLM_KL_TRI_MLBS_SBIT2                        1
#define CLM_KO_TRI_MLBS_TTL2_EXPIRY                  (CLM_KO_TRI_MLBS_SBIT2 + CLM_KL_TRI_MLBS_SBIT2)
#define CLM_KL_TRI_MLBS_TTL2_EXPIRY                  1
#define CLM_KO_TRI_MLBS_RSV_LBL_VAL                  (CLM_KO_TRI_MLBS_TTL2_EXPIRY + CLM_KL_TRI_MLBS_TTL2_EXPIRY)
#define CLM_KL_TRI_MLBS_RSV_LBL_VAL                  4
#define CLM_KO_TRI_MLBS_CW_ACH                       (CLM_KO_TRI_MLBS_RSV_LBL_VAL + CLM_KL_TRI_MLBS_RSV_LBL_VAL)
#define CLM_KL_TRI_MLBS_CW_ACH                       32
#define CLM_KO_TRI_MLBS_RSV_LBL_POS                  (CLM_KO_TRI_MLBS_CW_ACH + CLM_KL_TRI_MLBS_CW_ACH)
#define CLM_KL_TRI_MLBS_RSV_LBL_POS                  3

/* CLM X3 PURE_5TUPLE_IP4 key fields */
#define CLM_KO_PURE_5TUPLE_IP4_L3_FRAGMENT_TYPE      (CLM_KO_X3_G_IDX + CLM_KL_X3_G_IDX)
#define CLM_KL_PURE_5TUPLE_IP4_L3_FRAGMENT_TYPE      2
#define CLM_KO_PURE_5TUPLE_IP4_L3_FRAG_INVLD_L4_LEN  (CLM_KO_PURE_5TUPLE_IP4_L3_FRAGMENT_TYPE + CLM_KL_PURE_5TUPLE_IP4_L3_FRAGMENT_TYPE)
#define CLM_KL_PURE_5TUPLE_IP4_L3_FRAG_INVLD_L4_LEN  1
#define CLM_KO_PURE_5TUPLE_IP4_L3_OPTIONS            (CLM_KO_PURE_5TUPLE_IP4_L3_FRAG_INVLD_L4_LEN + CLM_KL_PURE_5TUPLE_IP4_L3_FRAG_INVLD_L4_LEN)
#define CLM_KL_PURE_5TUPLE_IP4_L3_OPTIONS            1
#define CLM_KO_PURE_5TUPLE_IP4_L3_DSCP               (CLM_KO_PURE_5TUPLE_IP4_L3_OPTIONS + CLM_KL_PURE_5TUPLE_IP4_L3_OPTIONS)
#define CLM_KL_PURE_5TUPLE_IP4_L3_DSCP               6
#define CLM_KO_PURE_5TUPLE_IP4_L3_IP4_DIP            (CLM_KO_PURE_5TUPLE_IP4_L3_DSCP + CLM_KL_PURE_5TUPLE_IP4_L3_DSCP)
#define CLM_KL_PURE_5TUPLE_IP4_L3_IP4_DIP            32
#define CLM_KO_PURE_5TUPLE_IP4_L3_IP4_SIP            (CLM_KO_PURE_5TUPLE_IP4_L3_IP4_DIP + CLM_KL_PURE_5TUPLE_IP4_L3_IP4_DIP)
#define CLM_KL_PURE_5TUPLE_IP4_L3_IP4_SIP            32
#define CLM_KO_PURE_5TUPLE_IP4_L3_IP_PROTO           (CLM_KO_PURE_5TUPLE_IP4_L3_IP4_SIP + CLM_KL_PURE_5TUPLE_IP4_L3_IP4_SIP)
#define CLM_KL_PURE_5TUPLE_IP4_L3_IP_PROTO           8
#define CLM_KO_PURE_5TUPLE_IP4_L4_RNG                (CLM_KO_PURE_5TUPLE_IP4_L3_IP_PROTO + CLM_KL_PURE_5TUPLE_IP4_L3_IP_PROTO)
#define CLM_KL_PURE_5TUPLE_IP4_L4_RNG                8
#define CLM_KO_PURE_5TUPLE_IP4_IP_PAYLOAD_5TUPLE     (CLM_KO_PURE_5TUPLE_IP4_L4_RNG + CLM_KL_PURE_5TUPLE_IP4_L4_RNG)
#define CLM_KL_PURE_5TUPLE_IP4_IP_PAYLOAD_5TUPLE     32

/* CLM X3 CUSTOM_4 key fields */
#define CLM_KO_CUSTOM_4_CUSTOM_3                     (CLM_KO_X3_G_IDX + CLM_KL_X3_G_IDX)
#define CLM_KL_CUSTOM_4_CUSTOM_3                     32
#define CLM_KO_CUSTOM_4_CUSTOM_2                     (CLM_KO_CUSTOM_4_CUSTOM_3 + CLM_KL_CUSTOM_4_CUSTOM_3)
#define CLM_KL_CUSTOM_4_CUSTOM_2                     32
#define CLM_KO_CUSTOM_4_CUSTOM_1                     (CLM_KO_CUSTOM_4_CUSTOM_2 + CLM_KL_CUSTOM_4_CUSTOM_2)
#define CLM_KL_CUSTOM_4_CUSTOM_1                     32
#define CLM_KO_CUSTOM_4_CUSTOM_0                     (CLM_KO_CUSTOM_4_CUSTOM_1 + CLM_KL_CUSTOM_4_CUSTOM_1)
#define CLM_KL_CUSTOM_4_CUSTOM_0                     32

/* CLM X2 key types */
#define CLM_X2_TYPE_TRI_VID                          0
#define CLM_X2_TYPE_DBL_MLBS                         1
#define CLM_X2_TYPE_TRI_VID_IDX                      2
#define CLM_X2_TYPE_ETAG                             3

/* CLM X2 common key fields */
#define CLM_KO_X2_TYPE                               0
#define CLM_KL_X2_TYPE                               2
#define CLM_KO_X2_FIRST                              (CLM_KO_X2_TYPE + CLM_KL_X2_TYPE)
#define CLM_KL_X2_FIRST                              1
#define CLM_KO_X2_IGR_PORT                           (CLM_KO_X2_FIRST + CLM_KL_X2_FIRST)
#define CLM_KL_X2_IGR_PORT                           (FA_TGT ? 7 : 6)

#define CLM_KO_X2_G_IDX_SEL                          (CLM_KO_X2_FIRST + CLM_KL_X2_FIRST)
#define CLM_KL_X2_G_IDX_SEL                          2
#define CLM_KO_X2_G_IDX                              (CLM_KO_X2_G_IDX_SEL + CLM_KL_X2_G_IDX_SEL)
#define CLM_KL_X2_G_IDX                              (FA_TGT ? 12 : 10)

/* CLM X2 TRI_VID key fields */
#define CLM_KO_TRI_VID_G_IDX_SEL                     (CLM_KO_X2_IGR_PORT + CLM_KL_X2_IGR_PORT)
#define CLM_KL_TRI_VID_G_IDX_SEL                     2
#define CLM_KO_TRI_VID_G_IDX                         (CLM_KO_TRI_VID_G_IDX_SEL + CLM_KL_TRI_VID_G_IDX_SEL)
#define CLM_KL_TRI_VID_G_IDX                         (FA_TGT ? 12 : 10)
#define CLM_KO_TRI_VID_VLAN_TAGS                     (CLM_KO_TRI_VID_G_IDX + CLM_KL_TRI_VID_G_IDX)
#define CLM_KL_TRI_VID_VLAN_TAGS                     3
#define CLM_KO_TRI_VID_TPID0                         (CLM_KO_TRI_VID_VLAN_TAGS + CLM_KL_TRI_VID_VLAN_TAGS)
#define CLM_KL_TRI_VID_TPID0                         3
#define CLM_KO_TRI_VID_PCP0                          (CLM_KO_TRI_VID_TPID0 + CLM_KL_TRI_VID_TPID0)
#define CLM_KL_TRI_VID_PCP0                          3
#define CLM_KO_TRI_VID_DEI0                          (CLM_KO_TRI_VID_PCP0 + CLM_KL_TRI_VID_PCP0)
#define CLM_KL_TRI_VID_DEI0                          1
#define CLM_KO_TRI_VID_VID0                          (CLM_KO_TRI_VID_DEI0 + CLM_KL_TRI_VID_DEI0)
#define CLM_KL_TRI_VID_VID0                          12
#define CLM_KO_TRI_VID_TPID1                         (CLM_KO_TRI_VID_VID0 + CLM_KL_TRI_VID_VID0)
#define CLM_KL_TRI_VID_TPID1                         3
#define CLM_KO_TRI_VID_PCP1                          (CLM_KO_TRI_VID_TPID1 + CLM_KL_TRI_VID_TPID1)
#define CLM_KL_TRI_VID_PCP1                          3
#define CLM_KO_TRI_VID_DEI1                          (CLM_KO_TRI_VID_PCP1 + CLM_KL_TRI_VID_PCP1)
#define CLM_KL_TRI_VID_DEI1                          1
#define CLM_KO_TRI_VID_VID1                          (CLM_KO_TRI_VID_DEI1 + CLM_KL_TRI_VID_DEI1)
#define CLM_KL_TRI_VID_VID1                          12
#define CLM_KO_TRI_VID_TPID2                         (CLM_KO_TRI_VID_VID1 + CLM_KL_TRI_VID_VID1)
#define CLM_KL_TRI_VID_TPID2                         3
#define CLM_KO_TRI_VID_PCP2                          (CLM_KO_TRI_VID_TPID2 + CLM_KL_TRI_VID_TPID2)
#define CLM_KL_TRI_VID_PCP2                          3
#define CLM_KO_TRI_VID_DEI2                          (CLM_KO_TRI_VID_PCP2 + CLM_KL_TRI_VID_PCP2)
#define CLM_KL_TRI_VID_DEI2                          1
#define CLM_KO_TRI_VID_VID2                          (CLM_KO_TRI_VID_DEI2 + CLM_KL_TRI_VID_DEI2)
#define CLM_KL_TRI_VID_VID2                          12
#define CLM_KO_TRI_VID_L4_RNG                        (FA_TGT ? (CLM_KO_TRI_VID_VID2 + CLM_KL_TRI_VID_VID2) : (CLM_KO_TRI_VID_RED_TAGGED + CLM_KL_TRI_VID_RED_TAGGED))
#define CLM_KL_TRI_VID_L4_RNG                        8
#define CLM_KO_TRI_VID_OAM_Y1731                     (CLM_KO_TRI_VID_L4_RNG + CLM_KL_TRI_VID_L4_RNG)
#define CLM_KL_TRI_VID_OAM_Y1731                     1
#define CLM_KO_TRI_VID_OAM_MEL_FLAGS                 (CLM_KO_TRI_VID_OAM_Y1731 + CLM_KL_TRI_VID_OAM_Y1731)
#define CLM_KL_TRI_VID_OAM_MEL_FLAGS                 7

/* CLM X2 DBL_MLBS key fields */
#define CLM_KO_DBL_MLBS_LBL0                         (CLM_KO_X2_G_IDX + CLM_KL_X2_G_IDX)
#define CLM_KL_DBL_MLBS_LBL0                         20
#define CLM_KO_DBL_MLBS_TC0                          (CLM_KO_DBL_MLBS_LBL0 + CLM_KL_DBL_MLBS_LBL0)
#define CLM_KL_DBL_MLBS_TC0                          3
#define CLM_KO_DBL_MLBS_SBIT0                        (CLM_KO_DBL_MLBS_TC0 + CLM_KL_DBL_MLBS_TC0)
#define CLM_KL_DBL_MLBS_SBIT0                        1
#define CLM_KO_DBL_MLBS_TTL0_EXPIRY                  (CLM_KO_DBL_MLBS_SBIT0 + CLM_KL_DBL_MLBS_SBIT0)
#define CLM_KL_DBL_MLBS_TTL0_EXPIRY                  1
#define CLM_KO_DBL_MLBS_LBL1                         (CLM_KO_DBL_MLBS_TTL0_EXPIRY + CLM_KL_DBL_MLBS_TTL0_EXPIRY)
#define CLM_KL_DBL_MLBS_LBL1                         20
#define CLM_KO_DBL_MLBS_TC1                          (CLM_KO_DBL_MLBS_LBL1 + CLM_KL_DBL_MLBS_LBL1)
#define CLM_KL_DBL_MLBS_TC1                          3
#define CLM_KO_DBL_MLBS_SBIT1                        (CLM_KO_DBL_MLBS_TC1 + CLM_KL_DBL_MLBS_TC1)
#define CLM_KL_DBL_MLBS_SBIT1                        1
#define CLM_KO_DBL_MLBS_TTL1_EXPIRY                  (CLM_KO_DBL_MLBS_SBIT1 + CLM_KL_DBL_MLBS_SBIT1)
#define CLM_KL_DBL_MLBS_TTL1_EXPIRY                  1
#define CLM_KO_DBL_MLBS_RSV_LBL_VAL                  (CLM_KO_DBL_MLBS_TTL1_EXPIRY + CLM_KL_DBL_MLBS_TTL1_EXPIRY)
#define CLM_KL_DBL_MLBS_RSV_LBL_VAL                  4
#define CLM_KO_DBL_MLBS_RSV_LBL_POS                  (CLM_KO_DBL_MLBS_RSV_LBL_VAL + CLM_KL_DBL_MLBS_RSV_LBL_VAL)
#define CLM_KL_DBL_MLBS_RSV_LBL_POS                  3

/* CLM X2 TRI_VID_IDX key fields */
#define CLM_KO_TRI_VID_IDX_VLAN_TAGS                 (CLM_KO_X2_G_IDX + CLM_KL_X2_G_IDX)
#define CLM_KL_TRI_VID_IDX_VLAN_TAGS                 3
#define CLM_KO_TRI_VID_IDX_TPID0                     (CLM_KO_TRI_VID_IDX_VLAN_TAGS + CLM_KL_TRI_VID_IDX_VLAN_TAGS)
#define CLM_KL_TRI_VID_IDX_TPID0                     3
#define CLM_KO_TRI_VID_IDX_VID0                      (CLM_KO_TRI_VID_IDX_TPID0 + CLM_KL_TRI_VID_IDX_TPID0)
#define CLM_KL_TRI_VID_IDX_VID0                      12
#define CLM_KO_TRI_VID_IDX_TPID1                     (CLM_KO_TRI_VID_IDX_VID0 + CLM_KL_TRI_VID_IDX_VID0)
#define CLM_KL_TRI_VID_IDX_TPID1                     3
#define CLM_KO_TRI_VID_IDX_VID1                      (CLM_KO_TRI_VID_IDX_TPID1 + CLM_KL_TRI_VID_IDX_TPID1)
#define CLM_KL_TRI_VID_IDX_VID1                      12
#define CLM_KO_TRI_VID_IDX_TPID2                     (CLM_KO_TRI_VID_IDX_VID1 + CLM_KL_TRI_VID_IDX_VID1)
#define CLM_KL_TRI_VID_IDX_TPID2                     3
#define CLM_KO_TRI_VID_IDX_VID2                      (CLM_KO_TRI_VID_IDX_TPID2 + CLM_KL_TRI_VID_IDX_TPID2)
#define CLM_KL_TRI_VID_IDX_VID2                      12
#define CLM_KO_TRI_VID_IDX_L4_RNG                    (FA_TGT ? (CLM_KO_TRI_VID_IDX_VID2 + CLM_KL_TRI_VID_IDX_VID2) : (CLM_KO_TRI_VID_IDX_RED_TAGGED + CLM_KL_TRI_VID_IDX_RED_TAGGED))
#define CLM_KL_TRI_VID_IDX_L4_RNG                    8
#define CLM_KO_TRI_VID_IDX_OAM_Y1731                 (CLM_KO_TRI_VID_IDX_L4_RNG + CLM_KL_TRI_VID_IDX_L4_RNG)
#define CLM_KL_TRI_VID_IDX_OAM_Y1731                 1
#define CLM_KO_TRI_VID_IDX_OAM_MEL_FLAGS             (CLM_KO_TRI_VID_IDX_OAM_Y1731 + CLM_KL_TRI_VID_IDX_OAM_Y1731)
#define CLM_KL_TRI_VID_IDX_OAM_MEL_FLAGS             7

/* CLM X2 ETAG key fields */
#define CLM_KO_ETAG_ETAGGED                          (CLM_KO_X2_IGR_PORT + CLM_KL_X2_IGR_PORT)
#define CLM_KL_ETAG_ETAGGED                          1
#define CLM_KO_ETAG_GRP                              (CLM_KO_ETAG_ETAGGED + CLM_KL_ETAG_ETAGGED)
#define CLM_KL_ETAG_GRP                              2
#define CLM_KO_ETAG_ECID_EXT                         (CLM_KO_ETAG_GRP + CLM_KL_ETAG_GRP)
#define CLM_KL_ETAG_ECID_EXT                         8
#define CLM_KO_ETAG_ECID_BASE                        (CLM_KO_ETAG_ECID_EXT + CLM_KL_ETAG_ECID_EXT)
#define CLM_KL_ETAG_ECID_BASE                        12
#define CLM_KO_ETAG_IGR_ECID_EXT                     (CLM_KO_ETAG_ECID_BASE + CLM_KL_ETAG_ECID_BASE)
#define CLM_KL_ETAG_IGR_ECID_EXT                     8
#define CLM_KO_ETAG_IGR_ECID_BASE                    (CLM_KO_ETAG_IGR_ECID_EXT + CLM_KL_ETAG_IGR_ECID_EXT)
#define CLM_KL_ETAG_IGR_ECID_BASE                    12

/* CLM X1 key types */
#define CLM_X1_TYPE_SGL_MLBS                         0
#define CLM_X1_TYPE_DBL_VID_IDX                      1

/* CLM X1 common key fields */
#define CLM_KO_X1_TYPE                               0
#define CLM_KL_X1_TYPE                               1
#define CLM_KO_X1_FIRST                              (CLM_KO_X1_TYPE + CLM_KL_X1_TYPE)
#define CLM_KL_X1_FIRST                              1
#define CLM_KO_X1_G_IDX_SEL                          (CLM_KO_X1_FIRST + CLM_KL_X1_FIRST)
#define CLM_KL_X1_G_IDX_SEL                          2
#define CLM_KO_X1_G_IDX                              (CLM_KO_X1_G_IDX_SEL + CLM_KL_X1_G_IDX_SEL)
#define CLM_KL_X1_G_IDX                              (FA_TGT ? 12 : 10)

/* CLM X1 SGL_MLBS key fields */
#define CLM_KO_SGL_MLBS_LBL0                         (CLM_KO_X1_G_IDX + CLM_KL_X1_G_IDX)
#define CLM_KL_SGL_MLBS_LBL0                         20
#define CLM_KO_SGL_MLBS_TC0                          (CLM_KO_SGL_MLBS_LBL0 + CLM_KL_SGL_MLBS_LBL0)
#define CLM_KL_SGL_MLBS_TC0                          3
#define CLM_KO_SGL_MLBS_SBIT0                        (CLM_KO_SGL_MLBS_TC0 + CLM_KL_SGL_MLBS_TC0)
#define CLM_KL_SGL_MLBS_SBIT0                        1
#define CLM_KO_SGL_MLBS_TTL0_EXPIRY                  (CLM_KO_SGL_MLBS_SBIT0 + CLM_KL_SGL_MLBS_SBIT0)
#define CLM_KL_SGL_MLBS_TTL0_EXPIRY                  1
#define CLM_KO_SGL_MLBS_RSV_LBL_VAL                  (CLM_KO_SGL_MLBS_TTL0_EXPIRY + CLM_KL_SGL_MLBS_TTL0_EXPIRY)
#define CLM_KL_SGL_MLBS_RSV_LBL_VAL                  4
#define CLM_KO_SGL_MLBS_RSV_LBL_POS                  (CLM_KO_SGL_MLBS_RSV_LBL_VAL + CLM_KL_SGL_MLBS_RSV_LBL_VAL)
#define CLM_KL_SGL_MLBS_RSV_LBL_POS                  3

/* CLM X1 DBL_VID_IDX key fields */
#define CLM_KO_DBL_VID_IDX_VLAN_TAG_TPID             (CLM_KO_X1_G_IDX + CLM_KL_X1_G_IDX)
#define CLM_KL_DBL_VID_IDX_VLAN_TAG_TPID             3
#define CLM_KO_DBL_VID_IDX_VID0                      (CLM_KO_DBL_VID_IDX_VLAN_TAG_TPID + CLM_KL_DBL_VID_IDX_VLAN_TAG_TPID)
#define CLM_KL_DBL_VID_IDX_VID0                      12
#define CLM_KO_DBL_VID_IDX_VID1                      (CLM_KO_DBL_VID_IDX_VID0 + CLM_KL_DBL_VID_IDX_VID0)
#define CLM_KL_DBL_VID_IDX_VID1                      12
#define CLM_KO_DBL_VID_IDX_OAM_Y1731                 (FA_TGT ? (CLM_KO_DBL_VID_IDX_VID1 + CLM_KL_DBL_VID_IDX_VID1) : (CLM_KO_DBL_VID_IDX_RED_TAGGED + CLM_KL_DBL_VID_IDX_RED_TAGGED))
#define CLM_KL_DBL_VID_IDX_OAM_Y1731                 1
#define CLM_KO_DBL_VID_IDX_OAM_MEL_FLAGS             (CLM_KO_DBL_VID_IDX_OAM_Y1731 + CLM_KL_DBL_VID_IDX_OAM_Y1731)
#define CLM_KL_DBL_VID_IDX_OAM_MEL_FLAGS             7

/* CLM X3 FULL action fields */
#define CLM_AO_FULL_DSCP_ENA                         0
#define CLM_AL_FULL_DSCP_ENA                         1
#define CLM_AO_FULL_DSCP_VAL                         (CLM_AO_FULL_DSCP_ENA + CLM_AL_FULL_DSCP_ENA)
#define CLM_AL_FULL_DSCP_VAL                         6
#define CLM_AO_FULL_COSID_ENA                        (CLM_AO_FULL_DSCP_VAL + CLM_AL_FULL_DSCP_VAL)
#define CLM_AL_FULL_COSID_ENA                        1
#define CLM_AO_FULL_COSID_VAL                        (CLM_AO_FULL_COSID_ENA + CLM_AL_FULL_COSID_ENA)
#define CLM_AL_FULL_COSID_VAL                        3
#define CLM_AO_FULL_QOS_ENA                          (CLM_AO_FULL_COSID_VAL + CLM_AL_FULL_COSID_VAL)
#define CLM_AL_FULL_QOS_ENA                          1
#define CLM_AO_FULL_QOS_VAL                          (CLM_AO_FULL_QOS_ENA + CLM_AL_FULL_QOS_ENA)
#define CLM_AL_FULL_QOS_VAL                          3
#define CLM_AO_FULL_DP_ENA                           (CLM_AO_FULL_QOS_VAL + CLM_AL_FULL_QOS_VAL)
#define CLM_AL_FULL_DP_ENA                           1
#define CLM_AO_FULL_DP_VAL                           (CLM_AO_FULL_DP_ENA + CLM_AL_FULL_DP_ENA)
#define CLM_AL_FULL_DP_VAL                           2
#define CLM_AO_FULL_DEI_ENA                          (CLM_AO_FULL_DP_VAL + CLM_AL_FULL_DP_VAL)
#define CLM_AL_FULL_DEI_ENA                          1
#define CLM_AO_FULL_DEI_VAL                          (CLM_AO_FULL_DEI_ENA + CLM_AL_FULL_DEI_ENA)
#define CLM_AL_FULL_DEI_VAL                          1
#define CLM_AO_FULL_PCP_ENA                          (CLM_AO_FULL_DEI_VAL + CLM_AL_FULL_DEI_VAL)
#define CLM_AL_FULL_PCP_ENA                          1
#define CLM_AO_FULL_PCP_VAL                          (CLM_AO_FULL_PCP_ENA + CLM_AL_FULL_PCP_ENA)
#define CLM_AL_FULL_PCP_VAL                          3
#define CLM_AO_FULL_MAP_LOOKUP_SEL                   (CLM_AO_FULL_PCP_VAL + CLM_AL_FULL_PCP_VAL)
#define CLM_AL_FULL_MAP_LOOKUP_SEL                   2
#define CLM_AO_FULL_MAP_KEY                          (CLM_AO_FULL_MAP_LOOKUP_SEL + CLM_AL_FULL_MAP_LOOKUP_SEL)
#define CLM_AL_FULL_MAP_KEY                          3
#define CLM_AO_FULL_MAP_IDX                          (CLM_AO_FULL_MAP_KEY + CLM_AL_FULL_MAP_KEY)
#define CLM_AL_FULL_MAP_IDX                          (FA_TGT ? 9 : 7)
#define CLM_AO_FULL_XVID_ADD_REPLACE_SEL             (CLM_AO_FULL_MAP_IDX + CLM_AL_FULL_MAP_IDX)
#define CLM_AL_FULL_XVID_ADD_REPLACE_SEL             3
#define CLM_AO_FULL_GVID_ADD_REPLACE_SEL             (CLM_AO_FULL_XVID_ADD_REPLACE_SEL + CLM_AL_FULL_XVID_ADD_REPLACE_SEL)
#define CLM_AL_FULL_GVID_ADD_REPLACE_SEL             3
#define CLM_AO_FULL_VID_VAL                          (CLM_AO_FULL_GVID_ADD_REPLACE_SEL + CLM_AL_FULL_GVID_ADD_REPLACE_SEL)
#define CLM_AL_FULL_VID_VAL                          13
#define CLM_AO_FULL_VLAN_POP_CNT_ENA                 (CLM_AO_FULL_VID_VAL + CLM_AL_FULL_VID_VAL)
#define CLM_AL_FULL_VLAN_POP_CNT_ENA                 1
#define CLM_AO_FULL_VLAN_POP_CNT                     (CLM_AO_FULL_VLAN_POP_CNT_ENA + CLM_AL_FULL_VLAN_POP_CNT_ENA)
#define CLM_AL_FULL_VLAN_POP_CNT                     2
#define CLM_AO_FULL_VLAN_PUSH_CNT_ENA                (CLM_AO_FULL_VLAN_POP_CNT + CLM_AL_FULL_VLAN_POP_CNT)
#define CLM_AL_FULL_VLAN_PUSH_CNT_ENA                1
#define CLM_AO_FULL_VLAN_PUSH_CNT                    (CLM_AO_FULL_VLAN_PUSH_CNT_ENA + CLM_AL_FULL_VLAN_PUSH_CNT_ENA)
#define CLM_AL_FULL_VLAN_PUSH_CNT                    2
#define CLM_AO_FULL_TPID_SEL                         (CLM_AO_FULL_VLAN_PUSH_CNT + CLM_AL_FULL_VLAN_PUSH_CNT)
#define CLM_AL_FULL_TPID_SEL                         2
#define CLM_AO_FULL_VLAN_WAS_TAGGED                  (CLM_AO_FULL_TPID_SEL + CLM_AL_FULL_TPID_SEL)
#define CLM_AL_FULL_VLAN_WAS_TAGGED                  2
#define CLM_AO_FULL_ISDX_ADD_REPLACE_SEL             (CLM_AO_FULL_VLAN_WAS_TAGGED + CLM_AL_FULL_VLAN_WAS_TAGGED)
#define CLM_AL_FULL_ISDX_ADD_REPLACE_SEL             1
#define CLM_AO_FULL_ISDX_VAL                         (CLM_AO_FULL_ISDX_ADD_REPLACE_SEL + CLM_AL_FULL_ISDX_ADD_REPLACE_SEL)
#define CLM_AL_FULL_ISDX_VAL                         (FA_TGT ? 12 : 10)
#define CLM_AO_FULL_MASK_MODE                        (CLM_AO_FULL_ISDX_VAL + CLM_AL_FULL_ISDX_VAL)
#define CLM_AL_FULL_MASK_MODE                        3
#define CLM_AO_FULL_PORT_MASK_0                      (CLM_AO_FULL_MASK_MODE + CLM_AL_FULL_MASK_MODE)
#define CLM_AL_FULL_PORT_MASK_0                      32
#define CLM_AO_FULL_PORT_MASK_1                      (CLM_AO_FULL_PORT_MASK_0 + CLM_AL_FULL_PORT_MASK_0)
#define CLM_AL_FULL_PORT_MASK_1                      (FA_TGT ? 32 : 5)
#define CLM_AO_FULL_PORT_MASK_2                      (CLM_AO_FULL_PORT_MASK_1 + CLM_AL_FULL_PORT_MASK_1)
#define CLM_AL_FULL_PORT_MASK_2                      1
#define CLM_AO_FULL_RT_SEL                           (FA_TGT ? (CLM_AO_FULL_PORT_MASK_2 + CLM_AL_FULL_PORT_MASK_2) : (CLM_AO_FULL_PORT_MASK_1 + CLM_AL_FULL_PORT_MASK_1))
#define CLM_AL_FULL_RT_SEL                           2
#define CLM_AO_FULL_LPM_AFFIX_ENA                    (CLM_AO_FULL_RT_SEL + CLM_AL_FULL_RT_SEL)
#define CLM_AL_FULL_LPM_AFFIX_ENA                    1
#define CLM_AO_FULL_LPM_AFFIX_VAL                    (CLM_AO_FULL_LPM_AFFIX_ENA + CLM_AL_FULL_LPM_AFFIX_ENA)
#define CLM_AL_FULL_LPM_AFFIX_VAL                    10
#define CLM_AO_FULL_RLEG_DMAC_CHK_DIS                (CLM_AO_FULL_LPM_AFFIX_VAL + CLM_AL_FULL_LPM_AFFIX_VAL)
#define CLM_AL_FULL_RLEG_DMAC_CHK_DIS                1
#define CLM_AO_FULL_TTL_DECR_DIS                     (CLM_AO_FULL_RLEG_DMAC_CHK_DIS + CLM_AL_FULL_RLEG_DMAC_CHK_DIS)
#define CLM_AL_FULL_TTL_DECR_DIS                     1
#define CLM_AO_FULL_L3_MAC_UPDATE_DIS                (CLM_AO_FULL_TTL_DECR_DIS + CLM_AL_FULL_TTL_DECR_DIS)
#define CLM_AL_FULL_L3_MAC_UPDATE_DIS                1
#define CLM_AO_FULL_CPU_ENA                          (CLM_AO_FULL_L3_MAC_UPDATE_DIS + CLM_AL_FULL_L3_MAC_UPDATE_DIS)
#define CLM_AL_FULL_CPU_ENA                          1
#define CLM_AO_FULL_CPU_Q                            (CLM_AO_FULL_CPU_ENA + CLM_AL_FULL_CPU_ENA)
#define CLM_AL_FULL_CPU_Q                            3
#define CLM_AO_FULL_MIP_SEL                          (CLM_AO_FULL_CPU_Q + CLM_AL_FULL_CPU_Q)
#define CLM_AL_FULL_MIP_SEL                          2
#define CLM_AO_FULL_OAM_Y1731_SEL                    (CLM_AO_FULL_MIP_SEL + CLM_AL_FULL_MIP_SEL)
#define CLM_AL_FULL_OAM_Y1731_SEL                    3
#define CLM_AO_FULL_OAM_TWAMP_ENA                    (CLM_AO_FULL_OAM_Y1731_SEL + CLM_AL_FULL_OAM_Y1731_SEL)
#define CLM_AL_FULL_OAM_TWAMP_ENA                    1
#define CLM_AO_FULL_OAM_IP_BFD_ENA                   (CLM_AO_FULL_OAM_TWAMP_ENA + CLM_AL_FULL_OAM_TWAMP_ENA)
#define CLM_AL_FULL_OAM_IP_BFD_ENA                   1
#define CLM_AO_FULL_RSVD_LBL_VAL                     (FA_TGT ? (CLM_AO_FULL_OAM_IP_BFD_ENA + CLM_AL_FULL_OAM_IP_BFD_ENA) : (CLM_AO_FULL_OAM_DLR_ENA + CLM_AL_FULL_OAM_DLR_ENA))
#define CLM_AL_FULL_RSVD_LBL_VAL                     4
#define CLM_AO_FULL_TC_LABEL                         (CLM_AO_FULL_RSVD_LBL_VAL + CLM_AL_FULL_RSVD_LBL_VAL)
#define CLM_AL_FULL_TC_LABEL                         3
#define CLM_AO_FULL_TTL_LABEL                        (CLM_AO_FULL_TC_LABEL + CLM_AL_FULL_TC_LABEL)
#define CLM_AL_FULL_TTL_LABEL                        3
#define CLM_AO_FULL_NUM_VLD_LABELS                   (CLM_AO_FULL_TTL_LABEL + CLM_AL_FULL_TTL_LABEL)
#define CLM_AL_FULL_NUM_VLD_LABELS                   2
#define CLM_AO_FULL_FWD_TYPE                         (CLM_AO_FULL_NUM_VLD_LABELS + CLM_AL_FULL_NUM_VLD_LABELS)
#define CLM_AL_FULL_FWD_TYPE                         3
#define CLM_AO_FULL_MPLS_OAM_TYPE                    (CLM_AO_FULL_FWD_TYPE + CLM_AL_FULL_FWD_TYPE)
#define CLM_AL_FULL_MPLS_OAM_TYPE                    3
#define CLM_AO_FULL_MPLS_MEP_ENA                     (CLM_AO_FULL_MPLS_OAM_TYPE + CLM_AL_FULL_MPLS_OAM_TYPE)
#define CLM_AL_FULL_MPLS_MEP_ENA                     1
#define CLM_AO_FULL_MPLS_MIP_ENA                     (CLM_AO_FULL_MPLS_MEP_ENA + CLM_AL_FULL_MPLS_MEP_ENA)
#define CLM_AL_FULL_MPLS_MIP_ENA                     1
#define CLM_AO_FULL_MPLS_OAM_FLAVOR                  (CLM_AO_FULL_MPLS_MIP_ENA + CLM_AL_FULL_MPLS_MIP_ENA)
#define CLM_AL_FULL_MPLS_OAM_FLAVOR                  1
#define CLM_AO_FULL_MPLS_IP_CTRL_ENA                 (CLM_AO_FULL_MPLS_OAM_FLAVOR + CLM_AL_FULL_MPLS_OAM_FLAVOR)
#define CLM_AL_FULL_MPLS_IP_CTRL_ENA                 1
#define CLM_AO_FULL_CUSTOM_ACE_ENA                   (CLM_AO_FULL_MPLS_IP_CTRL_ENA + CLM_AL_FULL_MPLS_IP_CTRL_ENA)
#define CLM_AL_FULL_CUSTOM_ACE_ENA                   5
#define CLM_AO_FULL_CUSTOM_ACE_OFFSET                (CLM_AO_FULL_CUSTOM_ACE_ENA + CLM_AL_FULL_CUSTOM_ACE_ENA)
#define CLM_AL_FULL_CUSTOM_ACE_OFFSET                2
#define CLM_AO_FULL_PAG_OVERRIDE_MASK                (CLM_AO_FULL_CUSTOM_ACE_OFFSET + CLM_AL_FULL_CUSTOM_ACE_OFFSET)
#define CLM_AL_FULL_PAG_OVERRIDE_MASK                8
#define CLM_AO_FULL_PAG_VAL                          (CLM_AO_FULL_PAG_OVERRIDE_MASK + CLM_AL_FULL_PAG_OVERRIDE_MASK)
#define CLM_AL_FULL_PAG_VAL                          8
#define CLM_AO_FULL_S2_KEY_SEL_ENA                   (CLM_AO_FULL_PAG_VAL + CLM_AL_FULL_PAG_VAL)
#define CLM_AL_FULL_S2_KEY_SEL_ENA                   1
#define CLM_AO_FULL_S2_KEY_SEL_IDX                   (CLM_AO_FULL_S2_KEY_SEL_ENA + CLM_AL_FULL_S2_KEY_SEL_ENA)
#define CLM_AL_FULL_S2_KEY_SEL_IDX                   6
#define CLM_AO_FULL_INJ_MASQ_ENA                     (CLM_AO_FULL_S2_KEY_SEL_IDX + CLM_AL_FULL_S2_KEY_SEL_IDX)
#define CLM_AL_FULL_INJ_MASQ_ENA                     1
#define CLM_AO_FULL_INJ_MASQ_PORT                    (CLM_AO_FULL_INJ_MASQ_ENA + CLM_AL_FULL_INJ_MASQ_ENA)
#define CLM_AL_FULL_INJ_MASQ_PORT                    (FA_TGT ? 7 : 6)
#define CLM_AO_FULL_LPORT_ENA                        (CLM_AO_FULL_INJ_MASQ_PORT + CLM_AL_FULL_INJ_MASQ_PORT)
#define CLM_AL_FULL_LPORT_ENA                        1
#define CLM_AO_FULL_INJ_MASQ_LPORT                   (CLM_AO_FULL_LPORT_ENA + CLM_AL_FULL_LPORT_ENA)
#define CLM_AL_FULL_INJ_MASQ_LPORT                   (FA_TGT ? 7 : 6)
#define CLM_AO_FULL_MATCH_ID                         (CLM_AO_FULL_INJ_MASQ_LPORT + CLM_AL_FULL_INJ_MASQ_LPORT)
#define CLM_AL_FULL_MATCH_ID                         16
#define CLM_AO_FULL_MATCH_ID_MASK                    (CLM_AO_FULL_MATCH_ID + CLM_AL_FULL_MATCH_ID)
#define CLM_AL_FULL_MATCH_ID_MASK                    16
#define CLM_AO_FULL_PIPELINE_FORCE_ENA               (CLM_AO_FULL_MATCH_ID_MASK + CLM_AL_FULL_MATCH_ID_MASK)
#define CLM_AL_FULL_PIPELINE_FORCE_ENA               2
#define CLM_AO_FULL_PIPELINE_ACT_SEL                 (CLM_AO_FULL_PIPELINE_FORCE_ENA + CLM_AL_FULL_PIPELINE_FORCE_ENA)
#define CLM_AL_FULL_PIPELINE_ACT_SEL                 1
#define CLM_AO_FULL_PIPELINE_PT                      (CLM_AO_FULL_PIPELINE_ACT_SEL + CLM_AL_FULL_PIPELINE_ACT_SEL)
#define CLM_AL_FULL_PIPELINE_PT                      5
#define CLM_AO_FULL_NXT_KEY_TYPE                     (CLM_AO_FULL_PIPELINE_PT + CLM_AL_FULL_PIPELINE_PT)
#define CLM_AL_FULL_NXT_KEY_TYPE                     5
#define CLM_AO_FULL_NXT_NORM_W16_OFFSET              (CLM_AO_FULL_NXT_KEY_TYPE + CLM_AL_FULL_NXT_KEY_TYPE)
#define CLM_AL_FULL_NXT_NORM_W16_OFFSET              5
#define CLM_AO_FULL_NXT_OFFSET_FROM_TYPE             (CLM_AO_FULL_NXT_NORM_W16_OFFSET + CLM_AL_FULL_NXT_NORM_W16_OFFSET)
#define CLM_AL_FULL_NXT_OFFSET_FROM_TYPE             2
#define CLM_AO_FULL_NXT_TYPE_AFTER_OFFSET            (CLM_AO_FULL_NXT_OFFSET_FROM_TYPE + CLM_AL_FULL_NXT_OFFSET_FROM_TYPE)
#define CLM_AL_FULL_NXT_TYPE_AFTER_OFFSET            2
#define CLM_AO_FULL_NXT_NORMALIZE                    (CLM_AO_FULL_NXT_TYPE_AFTER_OFFSET + CLM_AL_FULL_NXT_TYPE_AFTER_OFFSET)
#define CLM_AL_FULL_NXT_NORMALIZE                    1
#define CLM_AO_FULL_NXT_IDX_CTRL                     (CLM_AO_FULL_NXT_NORMALIZE + CLM_AL_FULL_NXT_NORMALIZE)
#define CLM_AL_FULL_NXT_IDX_CTRL                     3
#define CLM_AO_FULL_NXT_IDX                          (CLM_AO_FULL_NXT_IDX_CTRL + CLM_AL_FULL_NXT_IDX_CTRL)
#define CLM_AL_FULL_NXT_IDX                          (FA_TGT ? 12 : 10)

/* CLM X2 action types */
#define CLM_X2_TYPE_MLBS                             0
#define CLM_X2_TYPE_CLASSIFICATION                   1

/* CLM X2 common action fields */
#define CLM_AO_X2_TYPE                               0
#define CLM_AL_X2_TYPE                               1
/* CLM X2 MLBS action fields */
#define CLM_AO_MLBS_COSID_ENA                        (CLM_AO_X2_TYPE + CLM_AL_X2_TYPE)
#define CLM_AL_MLBS_COSID_ENA                        1
#define CLM_AO_MLBS_COSID_VAL                        (CLM_AO_MLBS_COSID_ENA + CLM_AL_MLBS_COSID_ENA)
#define CLM_AL_MLBS_COSID_VAL                        3
#define CLM_AO_MLBS_QOS_ENA                          (CLM_AO_MLBS_COSID_VAL + CLM_AL_MLBS_COSID_VAL)
#define CLM_AL_MLBS_QOS_ENA                          1
#define CLM_AO_MLBS_QOS_VAL                          (CLM_AO_MLBS_QOS_ENA + CLM_AL_MLBS_QOS_ENA)
#define CLM_AL_MLBS_QOS_VAL                          3
#define CLM_AO_MLBS_DP_ENA                           (CLM_AO_MLBS_QOS_VAL + CLM_AL_MLBS_QOS_VAL)
#define CLM_AL_MLBS_DP_ENA                           1
#define CLM_AO_MLBS_DP_VAL                           (CLM_AO_MLBS_DP_ENA + CLM_AL_MLBS_DP_ENA)
#define CLM_AL_MLBS_DP_VAL                           2
#define CLM_AO_MLBS_MAP_LOOKUP_SEL                   (CLM_AO_MLBS_DP_VAL + CLM_AL_MLBS_DP_VAL)
#define CLM_AL_MLBS_MAP_LOOKUP_SEL                   2
#define CLM_AO_MLBS_MAP_KEY                          (CLM_AO_MLBS_MAP_LOOKUP_SEL + CLM_AL_MLBS_MAP_LOOKUP_SEL)
#define CLM_AL_MLBS_MAP_KEY                          3
#define CLM_AO_MLBS_MAP_IDX                          (CLM_AO_MLBS_MAP_KEY + CLM_AL_MLBS_MAP_KEY)
#define CLM_AL_MLBS_MAP_IDX                          (FA_TGT ? 9 : 7)
#define CLM_AO_MLBS_XVID_ADD_REPLACE_SEL             (CLM_AO_MLBS_MAP_IDX + CLM_AL_MLBS_MAP_IDX)
#define CLM_AL_MLBS_XVID_ADD_REPLACE_SEL             3
#define CLM_AO_MLBS_GVID_ADD_REPLACE_SEL             (CLM_AO_MLBS_XVID_ADD_REPLACE_SEL + CLM_AL_MLBS_XVID_ADD_REPLACE_SEL)
#define CLM_AL_MLBS_GVID_ADD_REPLACE_SEL             3
#define CLM_AO_MLBS_VID_VAL                          (CLM_AO_MLBS_GVID_ADD_REPLACE_SEL + CLM_AL_MLBS_GVID_ADD_REPLACE_SEL)
#define CLM_AL_MLBS_VID_VAL                          13
#define CLM_AO_MLBS_ISDX_ADD_REPLACE_SEL             (CLM_AO_MLBS_VID_VAL + CLM_AL_MLBS_VID_VAL)
#define CLM_AL_MLBS_ISDX_ADD_REPLACE_SEL             1
#define CLM_AO_MLBS_ISDX_VAL                         (CLM_AO_MLBS_ISDX_ADD_REPLACE_SEL + CLM_AL_MLBS_ISDX_ADD_REPLACE_SEL)
#define CLM_AL_MLBS_ISDX_VAL                         (FA_TGT ? 12 : 10)
#define CLM_AO_MLBS_FWD_DIS                          (CLM_AO_MLBS_ISDX_VAL + CLM_AL_MLBS_ISDX_VAL)
#define CLM_AL_MLBS_FWD_DIS                          1
#define CLM_AO_MLBS_CPU_ENA                          (CLM_AO_MLBS_FWD_DIS + CLM_AL_MLBS_FWD_DIS)
#define CLM_AL_MLBS_CPU_ENA                          1
#define CLM_AO_MLBS_CPU_Q                            (CLM_AO_MLBS_CPU_ENA + CLM_AL_MLBS_CPU_ENA)
#define CLM_AL_MLBS_CPU_Q                            3
#define CLM_AO_MLBS_OAM_Y1731_SEL                    (CLM_AO_MLBS_CPU_Q + CLM_AL_MLBS_CPU_Q)
#define CLM_AL_MLBS_OAM_Y1731_SEL                    3
#define CLM_AO_MLBS_OAM_TWAMP_ENA                    (CLM_AO_MLBS_OAM_Y1731_SEL + CLM_AL_MLBS_OAM_Y1731_SEL)
#define CLM_AL_MLBS_OAM_TWAMP_ENA                    1
#define CLM_AO_MLBS_OAM_IP_BFD_ENA                   (CLM_AO_MLBS_OAM_TWAMP_ENA + CLM_AL_MLBS_OAM_TWAMP_ENA)
#define CLM_AL_MLBS_OAM_IP_BFD_ENA                   1
#define CLM_AO_MLBS_TC_LABEL                         (FA_TGT ? (CLM_AO_MLBS_OAM_IP_BFD_ENA + CLM_AL_MLBS_OAM_IP_BFD_ENA) : (CLM_AO_MLBS_OAM_DLR_ENA + CLM_AL_MLBS_OAM_DLR_ENA))
#define CLM_AL_MLBS_TC_LABEL                         3
#define CLM_AO_MLBS_TTL_LABEL                        (CLM_AO_MLBS_TC_LABEL + CLM_AL_MLBS_TC_LABEL)
#define CLM_AL_MLBS_TTL_LABEL                        3
#define CLM_AO_MLBS_NUM_VLD_LABELS                   (CLM_AO_MLBS_TTL_LABEL + CLM_AL_MLBS_TTL_LABEL)
#define CLM_AL_MLBS_NUM_VLD_LABELS                   2
#define CLM_AO_MLBS_FWD_TYPE                         (CLM_AO_MLBS_NUM_VLD_LABELS + CLM_AL_MLBS_NUM_VLD_LABELS)
#define CLM_AL_MLBS_FWD_TYPE                         3
#define CLM_AO_MLBS_MPLS_OAM_TYPE                    (CLM_AO_MLBS_FWD_TYPE + CLM_AL_MLBS_FWD_TYPE)
#define CLM_AL_MLBS_MPLS_OAM_TYPE                    3
#define CLM_AO_MLBS_MPLS_MEP_ENA                     (CLM_AO_MLBS_MPLS_OAM_TYPE + CLM_AL_MLBS_MPLS_OAM_TYPE)
#define CLM_AL_MLBS_MPLS_MEP_ENA                     1
#define CLM_AO_MLBS_MPLS_MIP_ENA                     (CLM_AO_MLBS_MPLS_MEP_ENA + CLM_AL_MLBS_MPLS_MEP_ENA)
#define CLM_AL_MLBS_MPLS_MIP_ENA                     1
#define CLM_AO_MLBS_MPLS_OAM_FLAVOR                  (CLM_AO_MLBS_MPLS_MIP_ENA + CLM_AL_MLBS_MPLS_MIP_ENA)
#define CLM_AL_MLBS_MPLS_OAM_FLAVOR                  1
#define CLM_AO_MLBS_MPLS_IP_CTRL_ENA                 (CLM_AO_MLBS_MPLS_OAM_FLAVOR + CLM_AL_MLBS_MPLS_OAM_FLAVOR)
#define CLM_AL_MLBS_MPLS_IP_CTRL_ENA                 1
#define CLM_AO_MLBS_PAG_OVERRIDE_MASK                (CLM_AO_MLBS_MPLS_IP_CTRL_ENA + CLM_AL_MLBS_MPLS_IP_CTRL_ENA)
#define CLM_AL_MLBS_PAG_OVERRIDE_MASK                8
#define CLM_AO_MLBS_PAG_VAL                          (CLM_AO_MLBS_PAG_OVERRIDE_MASK + CLM_AL_MLBS_PAG_OVERRIDE_MASK)
#define CLM_AL_MLBS_PAG_VAL                          8
#define CLM_AO_MLBS_S2_KEY_SEL_ENA                   (CLM_AO_MLBS_PAG_VAL + CLM_AL_MLBS_PAG_VAL)
#define CLM_AL_MLBS_S2_KEY_SEL_ENA                   1
#define CLM_AO_MLBS_S2_KEY_SEL_IDX                   (CLM_AO_MLBS_S2_KEY_SEL_ENA + CLM_AL_MLBS_S2_KEY_SEL_ENA)
#define CLM_AL_MLBS_S2_KEY_SEL_IDX                   6
#define CLM_AO_MLBS_PIPELINE_FORCE_ENA               (CLM_AO_MLBS_S2_KEY_SEL_IDX + CLM_AL_MLBS_S2_KEY_SEL_IDX)
#define CLM_AL_MLBS_PIPELINE_FORCE_ENA               2
#define CLM_AO_MLBS_PIPELINE_ACT_SEL                 (CLM_AO_MLBS_PIPELINE_FORCE_ENA + CLM_AL_MLBS_PIPELINE_FORCE_ENA)
#define CLM_AL_MLBS_PIPELINE_ACT_SEL                 1
#define CLM_AO_MLBS_PIPELINE_PT                      (CLM_AO_MLBS_PIPELINE_ACT_SEL + CLM_AL_MLBS_PIPELINE_ACT_SEL)
#define CLM_AL_MLBS_PIPELINE_PT                      5
#define CLM_AO_MLBS_NXT_KEY_TYPE                     (CLM_AO_MLBS_PIPELINE_PT + CLM_AL_MLBS_PIPELINE_PT)
#define CLM_AL_MLBS_NXT_KEY_TYPE                     5
#define CLM_AO_MLBS_NXT_NORM_W16_OFFSET              (CLM_AO_MLBS_NXT_KEY_TYPE + CLM_AL_MLBS_NXT_KEY_TYPE)
#define CLM_AL_MLBS_NXT_NORM_W16_OFFSET              5
#define CLM_AO_MLBS_NXT_OFFSET_FROM_TYPE             (CLM_AO_MLBS_NXT_NORM_W16_OFFSET + CLM_AL_MLBS_NXT_NORM_W16_OFFSET)
#define CLM_AL_MLBS_NXT_OFFSET_FROM_TYPE             2
#define CLM_AO_MLBS_NXT_TYPE_AFTER_OFFSET            (CLM_AO_MLBS_NXT_OFFSET_FROM_TYPE + CLM_AL_MLBS_NXT_OFFSET_FROM_TYPE)
#define CLM_AL_MLBS_NXT_TYPE_AFTER_OFFSET            2
#define CLM_AO_MLBS_NXT_NORMALIZE                    (CLM_AO_MLBS_NXT_TYPE_AFTER_OFFSET + CLM_AL_MLBS_NXT_TYPE_AFTER_OFFSET)
#define CLM_AL_MLBS_NXT_NORMALIZE                    1
#define CLM_AO_MLBS_NXT_IDX_CTRL                     (CLM_AO_MLBS_NXT_NORMALIZE + CLM_AL_MLBS_NXT_NORMALIZE)
#define CLM_AL_MLBS_NXT_IDX_CTRL                     3
#define CLM_AO_MLBS_NXT_IDX                          (CLM_AO_MLBS_NXT_IDX_CTRL + CLM_AL_MLBS_NXT_IDX_CTRL)
#define CLM_AL_MLBS_NXT_IDX                          (FA_TGT ? 12 : 10)

/* CLM X2 CLASSIFICATION action fields */
#define CLM_AO_CLASSIFICATION_DSCP_ENA               (CLM_AO_X2_TYPE + CLM_AL_X2_TYPE)
#define CLM_AL_CLASSIFICATION_DSCP_ENA               1
#define CLM_AO_CLASSIFICATION_DSCP_VAL               (CLM_AO_CLASSIFICATION_DSCP_ENA + CLM_AL_CLASSIFICATION_DSCP_ENA)
#define CLM_AL_CLASSIFICATION_DSCP_VAL               6
#define CLM_AO_CLASSIFICATION_COSID_ENA              (CLM_AO_CLASSIFICATION_DSCP_VAL + CLM_AL_CLASSIFICATION_DSCP_VAL)
#define CLM_AL_CLASSIFICATION_COSID_ENA              1
#define CLM_AO_CLASSIFICATION_COSID_VAL              (CLM_AO_CLASSIFICATION_COSID_ENA + CLM_AL_CLASSIFICATION_COSID_ENA)
#define CLM_AL_CLASSIFICATION_COSID_VAL              3
#define CLM_AO_CLASSIFICATION_QOS_ENA                (CLM_AO_CLASSIFICATION_COSID_VAL + CLM_AL_CLASSIFICATION_COSID_VAL)
#define CLM_AL_CLASSIFICATION_QOS_ENA                1
#define CLM_AO_CLASSIFICATION_QOS_VAL                (CLM_AO_CLASSIFICATION_QOS_ENA + CLM_AL_CLASSIFICATION_QOS_ENA)
#define CLM_AL_CLASSIFICATION_QOS_VAL                3
#define CLM_AO_CLASSIFICATION_DP_ENA                 (CLM_AO_CLASSIFICATION_QOS_VAL + CLM_AL_CLASSIFICATION_QOS_VAL)
#define CLM_AL_CLASSIFICATION_DP_ENA                 1
#define CLM_AO_CLASSIFICATION_DP_VAL                 (CLM_AO_CLASSIFICATION_DP_ENA + CLM_AL_CLASSIFICATION_DP_ENA)
#define CLM_AL_CLASSIFICATION_DP_VAL                 2
#define CLM_AO_CLASSIFICATION_DEI_ENA                (CLM_AO_CLASSIFICATION_DP_VAL + CLM_AL_CLASSIFICATION_DP_VAL)
#define CLM_AL_CLASSIFICATION_DEI_ENA                1
#define CLM_AO_CLASSIFICATION_DEI_VAL                (CLM_AO_CLASSIFICATION_DEI_ENA + CLM_AL_CLASSIFICATION_DEI_ENA)
#define CLM_AL_CLASSIFICATION_DEI_VAL                1
#define CLM_AO_CLASSIFICATION_PCP_ENA                (CLM_AO_CLASSIFICATION_DEI_VAL + CLM_AL_CLASSIFICATION_DEI_VAL)
#define CLM_AL_CLASSIFICATION_PCP_ENA                1
#define CLM_AO_CLASSIFICATION_PCP_VAL                (CLM_AO_CLASSIFICATION_PCP_ENA + CLM_AL_CLASSIFICATION_PCP_ENA)
#define CLM_AL_CLASSIFICATION_PCP_VAL                3
#define CLM_AO_CLASSIFICATION_MAP_LOOKUP_SEL         (CLM_AO_CLASSIFICATION_PCP_VAL + CLM_AL_CLASSIFICATION_PCP_VAL)
#define CLM_AL_CLASSIFICATION_MAP_LOOKUP_SEL         2
#define CLM_AO_CLASSIFICATION_MAP_KEY                (CLM_AO_CLASSIFICATION_MAP_LOOKUP_SEL + CLM_AL_CLASSIFICATION_MAP_LOOKUP_SEL)
#define CLM_AL_CLASSIFICATION_MAP_KEY                3
#define CLM_AO_CLASSIFICATION_MAP_IDX                (CLM_AO_CLASSIFICATION_MAP_KEY + CLM_AL_CLASSIFICATION_MAP_KEY)
#define CLM_AL_CLASSIFICATION_MAP_IDX                (FA_TGT ? 9 : 7)
#define CLM_AO_CLASSIFICATION_XVID_ADD_REPLACE_SEL   (CLM_AO_CLASSIFICATION_MAP_IDX + CLM_AL_CLASSIFICATION_MAP_IDX)
#define CLM_AL_CLASSIFICATION_XVID_ADD_REPLACE_SEL   3
#define CLM_AO_CLASSIFICATION_GVID_ADD_REPLACE_SEL   (CLM_AO_CLASSIFICATION_XVID_ADD_REPLACE_SEL + CLM_AL_CLASSIFICATION_XVID_ADD_REPLACE_SEL)
#define CLM_AL_CLASSIFICATION_GVID_ADD_REPLACE_SEL   3
#define CLM_AO_CLASSIFICATION_VID_VAL                (CLM_AO_CLASSIFICATION_GVID_ADD_REPLACE_SEL + CLM_AL_CLASSIFICATION_GVID_ADD_REPLACE_SEL)
#define CLM_AL_CLASSIFICATION_VID_VAL                13
#define CLM_AO_CLASSIFICATION_VLAN_POP_CNT_ENA       (CLM_AO_CLASSIFICATION_VID_VAL + CLM_AL_CLASSIFICATION_VID_VAL)
#define CLM_AL_CLASSIFICATION_VLAN_POP_CNT_ENA       1
#define CLM_AO_CLASSIFICATION_VLAN_POP_CNT           (CLM_AO_CLASSIFICATION_VLAN_POP_CNT_ENA + CLM_AL_CLASSIFICATION_VLAN_POP_CNT_ENA)
#define CLM_AL_CLASSIFICATION_VLAN_POP_CNT           2
#define CLM_AO_CLASSIFICATION_VLAN_PUSH_CNT_ENA      (CLM_AO_CLASSIFICATION_VLAN_POP_CNT + CLM_AL_CLASSIFICATION_VLAN_POP_CNT)
#define CLM_AL_CLASSIFICATION_VLAN_PUSH_CNT_ENA      1
#define CLM_AO_CLASSIFICATION_VLAN_PUSH_CNT          (CLM_AO_CLASSIFICATION_VLAN_PUSH_CNT_ENA + CLM_AL_CLASSIFICATION_VLAN_PUSH_CNT_ENA)
#define CLM_AL_CLASSIFICATION_VLAN_PUSH_CNT          2
#define CLM_AO_CLASSIFICATION_TPID_SEL               (CLM_AO_CLASSIFICATION_VLAN_PUSH_CNT + CLM_AL_CLASSIFICATION_VLAN_PUSH_CNT)
#define CLM_AL_CLASSIFICATION_TPID_SEL               2
#define CLM_AO_CLASSIFICATION_VLAN_WAS_TAGGED        (CLM_AO_CLASSIFICATION_TPID_SEL + CLM_AL_CLASSIFICATION_TPID_SEL)
#define CLM_AL_CLASSIFICATION_VLAN_WAS_TAGGED        2
#define CLM_AO_CLASSIFICATION_ISDX_ADD_REPLACE_SEL   (CLM_AO_CLASSIFICATION_VLAN_WAS_TAGGED + CLM_AL_CLASSIFICATION_VLAN_WAS_TAGGED)
#define CLM_AL_CLASSIFICATION_ISDX_ADD_REPLACE_SEL   1
#define CLM_AO_CLASSIFICATION_ISDX_VAL               (CLM_AO_CLASSIFICATION_ISDX_ADD_REPLACE_SEL + CLM_AL_CLASSIFICATION_ISDX_ADD_REPLACE_SEL)
#define CLM_AL_CLASSIFICATION_ISDX_VAL               (FA_TGT ? 12 : 10)
#define CLM_AO_CLASSIFICATION_RT_SEL                 (CLM_AO_CLASSIFICATION_ISDX_VAL + CLM_AL_CLASSIFICATION_ISDX_VAL)
#define CLM_AL_CLASSIFICATION_RT_SEL                 2
#define CLM_AO_CLASSIFICATION_LPM_AFFIX_ENA          (CLM_AO_CLASSIFICATION_RT_SEL + CLM_AL_CLASSIFICATION_RT_SEL)
#define CLM_AL_CLASSIFICATION_LPM_AFFIX_ENA          1
#define CLM_AO_CLASSIFICATION_LPM_AFFIX_VAL          (CLM_AO_CLASSIFICATION_LPM_AFFIX_ENA + CLM_AL_CLASSIFICATION_LPM_AFFIX_ENA)
#define CLM_AL_CLASSIFICATION_LPM_AFFIX_VAL          10
#define CLM_AO_CLASSIFICATION_RLEG_DMAC_CHK_DIS      (CLM_AO_CLASSIFICATION_LPM_AFFIX_VAL + CLM_AL_CLASSIFICATION_LPM_AFFIX_VAL)
#define CLM_AL_CLASSIFICATION_RLEG_DMAC_CHK_DIS      1
#define CLM_AO_CLASSIFICATION_TTL_DECR_DIS           (CLM_AO_CLASSIFICATION_RLEG_DMAC_CHK_DIS + CLM_AL_CLASSIFICATION_RLEG_DMAC_CHK_DIS)
#define CLM_AL_CLASSIFICATION_TTL_DECR_DIS           1
#define CLM_AO_CLASSIFICATION_L3_MAC_UPDATE_DIS      (CLM_AO_CLASSIFICATION_TTL_DECR_DIS + CLM_AL_CLASSIFICATION_TTL_DECR_DIS)
#define CLM_AL_CLASSIFICATION_L3_MAC_UPDATE_DIS      1
#define CLM_AO_CLASSIFICATION_FWD_DIS                (CLM_AO_CLASSIFICATION_L3_MAC_UPDATE_DIS + CLM_AL_CLASSIFICATION_L3_MAC_UPDATE_DIS)
#define CLM_AL_CLASSIFICATION_FWD_DIS                1
#define CLM_AO_CLASSIFICATION_CPU_ENA                (CLM_AO_CLASSIFICATION_FWD_DIS + CLM_AL_CLASSIFICATION_FWD_DIS)
#define CLM_AL_CLASSIFICATION_CPU_ENA                1
#define CLM_AO_CLASSIFICATION_CPU_Q                  (CLM_AO_CLASSIFICATION_CPU_ENA + CLM_AL_CLASSIFICATION_CPU_ENA)
#define CLM_AL_CLASSIFICATION_CPU_Q                  3
#define CLM_AO_CLASSIFICATION_MIP_SEL                (CLM_AO_CLASSIFICATION_CPU_Q + CLM_AL_CLASSIFICATION_CPU_Q)
#define CLM_AL_CLASSIFICATION_MIP_SEL                2
#define CLM_AO_CLASSIFICATION_OAM_Y1731_SEL          (CLM_AO_CLASSIFICATION_MIP_SEL + CLM_AL_CLASSIFICATION_MIP_SEL)
#define CLM_AL_CLASSIFICATION_OAM_Y1731_SEL          3
#define CLM_AO_CLASSIFICATION_OAM_TWAMP_ENA          (CLM_AO_CLASSIFICATION_OAM_Y1731_SEL + CLM_AL_CLASSIFICATION_OAM_Y1731_SEL)
#define CLM_AL_CLASSIFICATION_OAM_TWAMP_ENA          1
#define CLM_AO_CLASSIFICATION_OAM_IP_BFD_ENA         (CLM_AO_CLASSIFICATION_OAM_TWAMP_ENA + CLM_AL_CLASSIFICATION_OAM_TWAMP_ENA)
#define CLM_AL_CLASSIFICATION_OAM_IP_BFD_ENA         1
#define CLM_AO_CLASSIFICATION_PAG_OVERRIDE_MASK      (FA_TGT ? (CLM_AO_CLASSIFICATION_OAM_IP_BFD_ENA + CLM_AL_CLASSIFICATION_OAM_IP_BFD_ENA) : (CLM_AO_CLASSIFICATION_OAM_DLR_ENA + CLM_AL_CLASSIFICATION_OAM_DLR_ENA))
#define CLM_AL_CLASSIFICATION_PAG_OVERRIDE_MASK      8
#define CLM_AO_CLASSIFICATION_PAG_VAL                (CLM_AO_CLASSIFICATION_PAG_OVERRIDE_MASK + CLM_AL_CLASSIFICATION_PAG_OVERRIDE_MASK)
#define CLM_AL_CLASSIFICATION_PAG_VAL                8
#define CLM_AO_CLASSIFICATION_S2_KEY_SEL_ENA         (CLM_AO_CLASSIFICATION_PAG_VAL + CLM_AL_CLASSIFICATION_PAG_VAL)
#define CLM_AL_CLASSIFICATION_S2_KEY_SEL_ENA         1
#define CLM_AO_CLASSIFICATION_S2_KEY_SEL_IDX         (CLM_AO_CLASSIFICATION_S2_KEY_SEL_ENA + CLM_AL_CLASSIFICATION_S2_KEY_SEL_ENA)
#define CLM_AL_CLASSIFICATION_S2_KEY_SEL_IDX         6
#define CLM_AO_CLASSIFICATION_INJ_MASQ_ENA           (CLM_AO_CLASSIFICATION_S2_KEY_SEL_IDX + CLM_AL_CLASSIFICATION_S2_KEY_SEL_IDX)
#define CLM_AL_CLASSIFICATION_INJ_MASQ_ENA           1
#define CLM_AO_CLASSIFICATION_INJ_MASQ_PORT          (CLM_AO_CLASSIFICATION_INJ_MASQ_ENA + CLM_AL_CLASSIFICATION_INJ_MASQ_ENA)
#define CLM_AL_CLASSIFICATION_INJ_MASQ_PORT          (FA_TGT ? 7 : 6)
#define CLM_AO_CLASSIFICATION_LPORT_ENA              (CLM_AO_CLASSIFICATION_INJ_MASQ_PORT + CLM_AL_CLASSIFICATION_INJ_MASQ_PORT)
#define CLM_AL_CLASSIFICATION_LPORT_ENA              1
#define CLM_AO_CLASSIFICATION_INJ_MASQ_LPORT         (CLM_AO_CLASSIFICATION_LPORT_ENA + CLM_AL_CLASSIFICATION_LPORT_ENA)
#define CLM_AL_CLASSIFICATION_INJ_MASQ_LPORT         (FA_TGT ? 7 : 6)
#define CLM_AO_CLASSIFICATION_PIPELINE_FORCE_ENA     (CLM_AO_CLASSIFICATION_INJ_MASQ_LPORT + CLM_AL_CLASSIFICATION_INJ_MASQ_LPORT)
#define CLM_AL_CLASSIFICATION_PIPELINE_FORCE_ENA     2
#define CLM_AO_CLASSIFICATION_PIPELINE_ACT_SEL       (CLM_AO_CLASSIFICATION_PIPELINE_FORCE_ENA + CLM_AL_CLASSIFICATION_PIPELINE_FORCE_ENA)
#define CLM_AL_CLASSIFICATION_PIPELINE_ACT_SEL       1
#define CLM_AO_CLASSIFICATION_PIPELINE_PT            (CLM_AO_CLASSIFICATION_PIPELINE_ACT_SEL + CLM_AL_CLASSIFICATION_PIPELINE_ACT_SEL)
#define CLM_AL_CLASSIFICATION_PIPELINE_PT            5
#define CLM_AO_CLASSIFICATION_NXT_KEY_TYPE           (CLM_AO_CLASSIFICATION_PIPELINE_PT + CLM_AL_CLASSIFICATION_PIPELINE_PT)
#define CLM_AL_CLASSIFICATION_NXT_KEY_TYPE           5
#define CLM_AO_CLASSIFICATION_NXT_NORM_W16_OFFSET    (CLM_AO_CLASSIFICATION_NXT_KEY_TYPE + CLM_AL_CLASSIFICATION_NXT_KEY_TYPE)
#define CLM_AL_CLASSIFICATION_NXT_NORM_W16_OFFSET    5
#define CLM_AO_CLASSIFICATION_NXT_OFFSET_FROM_TYPE   (CLM_AO_CLASSIFICATION_NXT_NORM_W16_OFFSET + CLM_AL_CLASSIFICATION_NXT_NORM_W16_OFFSET)
#define CLM_AL_CLASSIFICATION_NXT_OFFSET_FROM_TYPE   2
#define CLM_AO_CLASSIFICATION_NXT_TYPE_AFTER_OFFSET  (CLM_AO_CLASSIFICATION_NXT_OFFSET_FROM_TYPE + CLM_AL_CLASSIFICATION_NXT_OFFSET_FROM_TYPE)
#define CLM_AL_CLASSIFICATION_NXT_TYPE_AFTER_OFFSET  2
#define CLM_AO_CLASSIFICATION_NXT_NORMALIZE          (CLM_AO_CLASSIFICATION_NXT_TYPE_AFTER_OFFSET + CLM_AL_CLASSIFICATION_NXT_TYPE_AFTER_OFFSET)
#define CLM_AL_CLASSIFICATION_NXT_NORMALIZE          1
#define CLM_AO_CLASSIFICATION_NXT_IDX_CTRL           (CLM_AO_CLASSIFICATION_NXT_NORMALIZE + CLM_AL_CLASSIFICATION_NXT_NORMALIZE)
#define CLM_AL_CLASSIFICATION_NXT_IDX_CTRL           3
#define CLM_AO_CLASSIFICATION_NXT_IDX                (CLM_AO_CLASSIFICATION_NXT_IDX_CTRL + CLM_AL_CLASSIFICATION_NXT_IDX_CTRL)
#define CLM_AL_CLASSIFICATION_NXT_IDX                (FA_TGT ? 12 : 10)

/* CLM X1 action types */
#define CLM_X1_TYPE_MLBS_REDUCED                     0
#define CLM_X1_TYPE_CLASS_REDUCED                    1

/* CLM X1 common action fields */
#define CLM_AO_X1_TYPE                               0
#define CLM_AL_X1_TYPE                               1
#define CLM_AO_X1_COSID_ENA                          (CLM_AO_X1_TYPE + CLM_AL_X1_TYPE)
#define CLM_AL_X1_COSID_ENA                          1
#define CLM_AO_X1_COSID_VAL                          (CLM_AO_X1_COSID_ENA + CLM_AL_X1_COSID_ENA)
#define CLM_AL_X1_COSID_VAL                          3
#define CLM_AO_X1_QOS_ENA                            (CLM_AO_X1_COSID_VAL + CLM_AL_X1_COSID_VAL)
#define CLM_AL_X1_QOS_ENA                            1
#define CLM_AO_X1_QOS_VAL                            (CLM_AO_X1_QOS_ENA + CLM_AL_X1_QOS_ENA)
#define CLM_AL_X1_QOS_VAL                            3
#define CLM_AO_X1_DP_ENA                             (CLM_AO_X1_QOS_VAL + CLM_AL_X1_QOS_VAL)
#define CLM_AL_X1_DP_ENA                             1
#define CLM_AO_X1_DP_VAL                             (CLM_AO_X1_DP_ENA + CLM_AL_X1_DP_ENA)
#define CLM_AL_X1_DP_VAL                             2
#define CLM_AO_X1_MAP_LOOKUP_SEL                     (CLM_AO_X1_DP_VAL + CLM_AL_X1_DP_VAL)
#define CLM_AL_X1_MAP_LOOKUP_SEL                     2

/* CLM X1 MLBS_REDUCED action fields */
#define CLM_AO_MLBS_REDUCED_ISDX_ADD_REPLACE_SEL     (CLM_AO_X1_MAP_LOOKUP_SEL + CLM_AL_X1_MAP_LOOKUP_SEL)
#define CLM_AL_MLBS_REDUCED_ISDX_ADD_REPLACE_SEL     1
#define CLM_AO_MLBS_REDUCED_ISDX_VAL                 (CLM_AO_MLBS_REDUCED_ISDX_ADD_REPLACE_SEL + CLM_AL_MLBS_REDUCED_ISDX_ADD_REPLACE_SEL)
#define CLM_AL_MLBS_REDUCED_ISDX_VAL                 (FA_TGT ? 12 : 10)
#define CLM_AO_MLBS_REDUCED_FWD_DIS                  (CLM_AO_MLBS_REDUCED_ISDX_VAL + CLM_AL_MLBS_REDUCED_ISDX_VAL)
#define CLM_AL_MLBS_REDUCED_FWD_DIS                  1
#define CLM_AO_MLBS_REDUCED_CPU_ENA                  (CLM_AO_MLBS_REDUCED_FWD_DIS + CLM_AL_MLBS_REDUCED_FWD_DIS)
#define CLM_AL_MLBS_REDUCED_CPU_ENA                  1
#define CLM_AO_MLBS_REDUCED_CPU_Q                    (CLM_AO_MLBS_REDUCED_CPU_ENA + CLM_AL_MLBS_REDUCED_CPU_ENA)
#define CLM_AL_MLBS_REDUCED_CPU_Q                    3
#define CLM_AO_MLBS_REDUCED_TC_ENA                   (CLM_AO_MLBS_REDUCED_CPU_Q + CLM_AL_MLBS_REDUCED_CPU_Q)
#define CLM_AL_MLBS_REDUCED_TC_ENA                   1
#define CLM_AO_MLBS_REDUCED_TTL_ENA                  (CLM_AO_MLBS_REDUCED_TC_ENA + CLM_AL_MLBS_REDUCED_TC_ENA)
#define CLM_AL_MLBS_REDUCED_TTL_ENA                  1
#define CLM_AO_MLBS_REDUCED_FWD_TYPE                 (CLM_AO_MLBS_REDUCED_TTL_ENA + CLM_AL_MLBS_REDUCED_TTL_ENA)
#define CLM_AL_MLBS_REDUCED_FWD_TYPE                 3
#define CLM_AO_MLBS_REDUCED_MPLS_OAM_TYPE            (CLM_AO_MLBS_REDUCED_FWD_TYPE + CLM_AL_MLBS_REDUCED_FWD_TYPE)
#define CLM_AL_MLBS_REDUCED_MPLS_OAM_TYPE            3
#define CLM_AO_MLBS_REDUCED_MPLS_MEP_ENA             (CLM_AO_MLBS_REDUCED_MPLS_OAM_TYPE + CLM_AL_MLBS_REDUCED_MPLS_OAM_TYPE)
#define CLM_AL_MLBS_REDUCED_MPLS_MEP_ENA             1
#define CLM_AO_MLBS_REDUCED_MPLS_MIP_ENA             (CLM_AO_MLBS_REDUCED_MPLS_MEP_ENA + CLM_AL_MLBS_REDUCED_MPLS_MEP_ENA)
#define CLM_AL_MLBS_REDUCED_MPLS_MIP_ENA             1
#define CLM_AO_MLBS_REDUCED_MPLS_OAM_FLAVOR          (CLM_AO_MLBS_REDUCED_MPLS_MIP_ENA + CLM_AL_MLBS_REDUCED_MPLS_MIP_ENA)
#define CLM_AL_MLBS_REDUCED_MPLS_OAM_FLAVOR          1
#define CLM_AO_MLBS_REDUCED_MPLS_IP_CTRL_ENA         (CLM_AO_MLBS_REDUCED_MPLS_OAM_FLAVOR + CLM_AL_MLBS_REDUCED_MPLS_OAM_FLAVOR)
#define CLM_AL_MLBS_REDUCED_MPLS_IP_CTRL_ENA         1
#define CLM_AO_MLBS_REDUCED_PIPELINE_FORCE_ENA       (CLM_AO_MLBS_REDUCED_MPLS_IP_CTRL_ENA + CLM_AL_MLBS_REDUCED_MPLS_IP_CTRL_ENA)
#define CLM_AL_MLBS_REDUCED_PIPELINE_FORCE_ENA       2
#define CLM_AO_MLBS_REDUCED_PIPELINE_ACT_SEL         (CLM_AO_MLBS_REDUCED_PIPELINE_FORCE_ENA + CLM_AL_MLBS_REDUCED_PIPELINE_FORCE_ENA)
#define CLM_AL_MLBS_REDUCED_PIPELINE_ACT_SEL         1
#define CLM_AO_MLBS_REDUCED_PIPELINE_PT_REDUCED      (CLM_AO_MLBS_REDUCED_PIPELINE_ACT_SEL + CLM_AL_MLBS_REDUCED_PIPELINE_ACT_SEL)
#define CLM_AL_MLBS_REDUCED_PIPELINE_PT_REDUCED      3
#define CLM_AO_MLBS_REDUCED_NXT_KEY_TYPE             (CLM_AO_MLBS_REDUCED_PIPELINE_PT_REDUCED + CLM_AL_MLBS_REDUCED_PIPELINE_PT_REDUCED)
#define CLM_AL_MLBS_REDUCED_NXT_KEY_TYPE             5
#define CLM_AO_MLBS_REDUCED_NXT_NORM_W32_OFFSET      (CLM_AO_MLBS_REDUCED_NXT_KEY_TYPE + CLM_AL_MLBS_REDUCED_NXT_KEY_TYPE)
#define CLM_AL_MLBS_REDUCED_NXT_NORM_W32_OFFSET      2
#define CLM_AO_MLBS_REDUCED_NXT_TYPE_AFTER_OFFSET    (CLM_AO_MLBS_REDUCED_NXT_NORM_W32_OFFSET + CLM_AL_MLBS_REDUCED_NXT_NORM_W32_OFFSET)
#define CLM_AL_MLBS_REDUCED_NXT_TYPE_AFTER_OFFSET    2
#define CLM_AO_MLBS_REDUCED_NXT_NORMALIZE            (CLM_AO_MLBS_REDUCED_NXT_TYPE_AFTER_OFFSET + CLM_AL_MLBS_REDUCED_NXT_TYPE_AFTER_OFFSET)
#define CLM_AL_MLBS_REDUCED_NXT_NORMALIZE            1
#define CLM_AO_MLBS_REDUCED_NXT_IDX_CTRL             (CLM_AO_MLBS_REDUCED_NXT_NORMALIZE + CLM_AL_MLBS_REDUCED_NXT_NORMALIZE)
#define CLM_AL_MLBS_REDUCED_NXT_IDX_CTRL             3
#define CLM_AO_MLBS_REDUCED_NXT_IDX                  (CLM_AO_MLBS_REDUCED_NXT_IDX_CTRL + CLM_AL_MLBS_REDUCED_NXT_IDX_CTRL)
#define CLM_AL_MLBS_REDUCED_NXT_IDX                  (FA_TGT ? 12 : 10)

/* CLM X1 CLASS_REDUCED action fields */
#define CLM_AO_CLASS_REDUCED_MAP_KEY                 (CLM_AO_X1_MAP_LOOKUP_SEL + CLM_AL_X1_MAP_LOOKUP_SEL)
#define CLM_AL_CLASS_REDUCED_MAP_KEY                 3
#define CLM_AO_CLASS_REDUCED_XVID_ADD_REPLACE_SEL    (CLM_AO_CLASS_REDUCED_MAP_KEY + CLM_AL_CLASS_REDUCED_MAP_KEY)
#define CLM_AL_CLASS_REDUCED_XVID_ADD_REPLACE_SEL    3
#define CLM_AO_CLASS_REDUCED_GVID_ADD_REPLACE_SEL    (CLM_AO_CLASS_REDUCED_XVID_ADD_REPLACE_SEL + CLM_AL_CLASS_REDUCED_XVID_ADD_REPLACE_SEL)
#define CLM_AL_CLASS_REDUCED_GVID_ADD_REPLACE_SEL    3
#define CLM_AO_CLASS_REDUCED_VID_VAL                 (CLM_AO_CLASS_REDUCED_GVID_ADD_REPLACE_SEL + CLM_AL_CLASS_REDUCED_GVID_ADD_REPLACE_SEL)
#define CLM_AL_CLASS_REDUCED_VID_VAL                 13
#define CLM_AO_CLASS_REDUCED_VLAN_POP_CNT_ENA        (CLM_AO_CLASS_REDUCED_VID_VAL + CLM_AL_CLASS_REDUCED_VID_VAL)
#define CLM_AL_CLASS_REDUCED_VLAN_POP_CNT_ENA        1
#define CLM_AO_CLASS_REDUCED_VLAN_POP_CNT            (CLM_AO_CLASS_REDUCED_VLAN_POP_CNT_ENA + CLM_AL_CLASS_REDUCED_VLAN_POP_CNT_ENA)
#define CLM_AL_CLASS_REDUCED_VLAN_POP_CNT            2
#define CLM_AO_CLASS_REDUCED_VLAN_PUSH_CNT_ENA       (CLM_AO_CLASS_REDUCED_VLAN_POP_CNT + CLM_AL_CLASS_REDUCED_VLAN_POP_CNT)
#define CLM_AL_CLASS_REDUCED_VLAN_PUSH_CNT_ENA       1
#define CLM_AO_CLASS_REDUCED_VLAN_PUSH_CNT           (CLM_AO_CLASS_REDUCED_VLAN_PUSH_CNT_ENA + CLM_AL_CLASS_REDUCED_VLAN_PUSH_CNT_ENA)
#define CLM_AL_CLASS_REDUCED_VLAN_PUSH_CNT           2
#define CLM_AO_CLASS_REDUCED_TPID_SEL                (CLM_AO_CLASS_REDUCED_VLAN_PUSH_CNT + CLM_AL_CLASS_REDUCED_VLAN_PUSH_CNT)
#define CLM_AL_CLASS_REDUCED_TPID_SEL                2
#define CLM_AO_CLASS_REDUCED_VLAN_WAS_TAGGED         (CLM_AO_CLASS_REDUCED_TPID_SEL + CLM_AL_CLASS_REDUCED_TPID_SEL)
#define CLM_AL_CLASS_REDUCED_VLAN_WAS_TAGGED         2
#define CLM_AO_CLASS_REDUCED_ISDX_ADD_REPLACE_SEL    (CLM_AO_CLASS_REDUCED_VLAN_WAS_TAGGED + CLM_AL_CLASS_REDUCED_VLAN_WAS_TAGGED)
#define CLM_AL_CLASS_REDUCED_ISDX_ADD_REPLACE_SEL    1
#define CLM_AO_CLASS_REDUCED_ISDX_VAL                (CLM_AO_CLASS_REDUCED_ISDX_ADD_REPLACE_SEL + CLM_AL_CLASS_REDUCED_ISDX_ADD_REPLACE_SEL)
#define CLM_AL_CLASS_REDUCED_ISDX_VAL                (FA_TGT ? 12 : 10)
#define CLM_AO_CLASS_REDUCED_FWD_DIS                 (CLM_AO_CLASS_REDUCED_ISDX_VAL + CLM_AL_CLASS_REDUCED_ISDX_VAL)
#define CLM_AL_CLASS_REDUCED_FWD_DIS                 1
#define CLM_AO_CLASS_REDUCED_CPU_ENA                 (CLM_AO_CLASS_REDUCED_FWD_DIS + CLM_AL_CLASS_REDUCED_FWD_DIS)
#define CLM_AL_CLASS_REDUCED_CPU_ENA                 1
#define CLM_AO_CLASS_REDUCED_CPU_Q                   (CLM_AO_CLASS_REDUCED_CPU_ENA + CLM_AL_CLASS_REDUCED_CPU_ENA)
#define CLM_AL_CLASS_REDUCED_CPU_Q                   3
#define CLM_AO_CLASS_REDUCED_MIP_SEL                 (CLM_AO_CLASS_REDUCED_CPU_Q + CLM_AL_CLASS_REDUCED_CPU_Q)
#define CLM_AL_CLASS_REDUCED_MIP_SEL                 2
#define CLM_AO_CLASS_REDUCED_OAM_Y1731_SEL           (CLM_AO_CLASS_REDUCED_MIP_SEL + CLM_AL_CLASS_REDUCED_MIP_SEL)
#define CLM_AL_CLASS_REDUCED_OAM_Y1731_SEL           3
#define CLM_AO_CLASS_REDUCED_LPORT_ENA               (FA_TGT ? (CLM_AO_CLASS_REDUCED_OAM_Y1731_SEL + CLM_AL_CLASS_REDUCED_OAM_Y1731_SEL) : (CLM_AO_CLASS_REDUCED_OAM_DLR_ENA + CLM_AL_CLASS_REDUCED_OAM_DLR_ENA))
#define CLM_AL_CLASS_REDUCED_LPORT_ENA               1
#define CLM_AO_CLASS_REDUCED_INJ_MASQ_LPORT          (CLM_AO_CLASS_REDUCED_LPORT_ENA + CLM_AL_CLASS_REDUCED_LPORT_ENA)
#define CLM_AL_CLASS_REDUCED_INJ_MASQ_LPORT          (FA_TGT ? 7 : 6)
#define CLM_AO_CLASS_REDUCED_PIPELINE_FORCE_ENA      (CLM_AO_CLASS_REDUCED_INJ_MASQ_LPORT + CLM_AL_CLASS_REDUCED_INJ_MASQ_LPORT)
#define CLM_AL_CLASS_REDUCED_PIPELINE_FORCE_ENA      2
#define CLM_AO_CLASS_REDUCED_PIPELINE_ACT_SEL        (CLM_AO_CLASS_REDUCED_PIPELINE_FORCE_ENA + CLM_AL_CLASS_REDUCED_PIPELINE_FORCE_ENA)
#define CLM_AL_CLASS_REDUCED_PIPELINE_ACT_SEL        1
#define CLM_AO_CLASS_REDUCED_PIPELINE_PT             (CLM_AO_CLASS_REDUCED_PIPELINE_ACT_SEL + CLM_AL_CLASS_REDUCED_PIPELINE_ACT_SEL)
#define CLM_AL_CLASS_REDUCED_PIPELINE_PT             5
#define CLM_AO_CLASS_REDUCED_NXT_KEY_TYPE            (CLM_AO_CLASS_REDUCED_PIPELINE_PT + CLM_AL_CLASS_REDUCED_PIPELINE_PT)
#define CLM_AL_CLASS_REDUCED_NXT_KEY_TYPE            5
#define CLM_AO_CLASS_REDUCED_NXT_IDX_CTRL            (CLM_AO_CLASS_REDUCED_NXT_KEY_TYPE + CLM_AL_CLASS_REDUCED_NXT_KEY_TYPE)
#define CLM_AL_CLASS_REDUCED_NXT_IDX_CTRL            3
#define CLM_AO_CLASS_REDUCED_NXT_IDX                 (CLM_AO_CLASS_REDUCED_NXT_IDX_CTRL + CLM_AL_CLASS_REDUCED_NXT_IDX_CTRL)
#define CLM_AL_CLASS_REDUCED_NXT_IDX                 (FA_TGT ? 12 : 10)

/* ================================================================= *
 *  VCAP IS2
 * ================================================================= */

/* IS2 X12 key types */
#define IS2_X12_TYPE_IP6_TCP_UDP                     0
#define IS2_X12_TYPE_IP_7TUPLE                       1
#define IS2_X12_TYPE_CUSTOM_1                        2

/* IS2 X12 common key fields */
#define IS2_KO_X12_TYPE                              0
#define IS2_KL_X12_TYPE                              2
#define IS2_KO_X12_FIRST                             (IS2_KO_X12_TYPE + IS2_KL_X12_TYPE)
#define IS2_KL_X12_FIRST                             1
#define IS2_KO_X12_PAG                               (IS2_KO_X12_FIRST + IS2_KL_X12_FIRST)
#define IS2_KL_X12_PAG                               8
#define IS2_KO_X12_IGR_PORT_MASK_L3                  (IS2_KO_X12_PAG + IS2_KL_X12_PAG)
#define IS2_KL_X12_IGR_PORT_MASK_L3                  1
#define IS2_KO_X12_IGR_PORT_MASK_RNG                 (IS2_KO_X12_IGR_PORT_MASK_L3 + IS2_KL_X12_IGR_PORT_MASK_L3)
#define IS2_KL_X12_IGR_PORT_MASK_RNG                 4
#define IS2_KO_X12_IGR_PORT_MASK_SEL                 (IS2_KO_X12_IGR_PORT_MASK_RNG + IS2_KL_X12_IGR_PORT_MASK_RNG)
#define IS2_KL_X12_IGR_PORT_MASK_SEL                 2
#define IS2_KO_X12_IGR_PORT_MASK_0                   (IS2_KO_X12_IGR_PORT_MASK_SEL + IS2_KL_X12_IGR_PORT_MASK_SEL)
#define IS2_KL_X12_IGR_PORT_MASK_0                   32
#define IS2_KO_X12_IGR_PORT_MASK_1                   (IS2_KO_X12_IGR_PORT_MASK_0 + IS2_KL_X12_IGR_PORT_MASK_0)
#define IS2_KL_X12_IGR_PORT_MASK_1                   32
#define IS2_KO_X12_IGR_PORT_MASK_2                   (IS2_KO_X12_IGR_PORT_MASK_1 + IS2_KL_X12_IGR_PORT_MASK_1)
#define IS2_KL_X12_IGR_PORT_MASK_2                   1
#define IS2_KO_X12_L2_MC                             (IS2_KO_X12_IGR_PORT_MASK_2 + IS2_KL_X12_IGR_PORT_MASK_2)
#define IS2_KL_X12_L2_MC                             1
#define IS2_KO_X12_L2_BC                             (IS2_KO_X12_L2_MC + IS2_KL_X12_L2_MC)
#define IS2_KL_X12_L2_BC                             1
#define IS2_KO_X12_VLAN_TAGGED                       (IS2_KO_X12_L2_BC + IS2_KL_X12_L2_BC)
#define IS2_KL_X12_VLAN_TAGGED                       1
#define IS2_KO_X12_SERVICE_FRM                       (FA_TGT ? (IS2_KO_X12_VLAN_TAGGED + IS2_KL_X12_VLAN_TAGGED) : (IS2_KO_X12_RED_TAGGED + IS2_KL_X12_RED_TAGGED))
#define IS2_KL_X12_SERVICE_FRM                       1
#define IS2_KO_X12_ISDX                              (IS2_KO_X12_SERVICE_FRM + IS2_KL_X12_SERVICE_FRM)
#define IS2_KL_X12_ISDX                              (FA_TGT ? 12 : 10)
#define IS2_KO_X12_XVID                              (IS2_KO_X12_ISDX + IS2_KL_X12_ISDX)
#define IS2_KL_X12_XVID                              13
#define IS2_KO_X12_DEI                               (IS2_KO_X12_XVID + IS2_KL_X12_XVID)
#define IS2_KL_X12_DEI                               1
#define IS2_KO_X12_PCP                               (IS2_KO_X12_DEI + IS2_KL_X12_DEI)
#define IS2_KL_X12_PCP                               3
#define IS2_KO_X12_L2_FWD                            (IS2_KO_X12_PCP + IS2_KL_X12_PCP)
#define IS2_KL_X12_L2_FWD                            1
#define IS2_KO_X12_L3_SMAC_SIP_MATCH                 (IS2_KO_X12_L2_FWD + IS2_KL_X12_L2_FWD)
#define IS2_KL_X12_L3_SMAC_SIP_MATCH                 1
#define IS2_KO_X12_L3_DMAC_DIP_MATCH                 (IS2_KO_X12_L3_SMAC_SIP_MATCH + IS2_KL_X12_L3_SMAC_SIP_MATCH)
#define IS2_KL_X12_L3_DMAC_DIP_MATCH                 1
#define IS2_KO_X12_L3_RT                             (IS2_KO_X12_L3_DMAC_DIP_MATCH + IS2_KL_X12_L3_DMAC_DIP_MATCH)
#define IS2_KL_X12_L3_RT                             1
#define IS2_KO_X12_L3_DST                            (IS2_KO_X12_L3_RT + IS2_KL_X12_L3_RT)
#define IS2_KL_X12_L3_DST                            1
#define IS2_KO_X12_L2_DMAC_0                         (IS2_KO_X12_L3_DST + IS2_KL_X12_L3_DST)
#define IS2_KL_X12_L2_DMAC_0                         32
#define IS2_KO_X12_L2_DMAC_1                         (IS2_KO_X12_L2_DMAC_0 + IS2_KL_X12_L2_DMAC_0)
#define IS2_KL_X12_L2_DMAC_1                         16
#define IS2_KO_X12_L2_SMAC_0                         (IS2_KO_X12_L2_DMAC_1 + IS2_KL_X12_L2_DMAC_1)
#define IS2_KL_X12_L2_SMAC_0                         32
#define IS2_KO_X12_L2_SMAC_1                         (IS2_KO_X12_L2_SMAC_0 + IS2_KL_X12_L2_SMAC_0)
#define IS2_KL_X12_L2_SMAC_1                         16

/* IS2 X12 IP6_TCP_UDP key fields */
#define IS2_KO_IP6_TCP_UDP_L3_TTL_GT0                (IS2_KO_X12_L2_SMAC_1 + IS2_KL_X12_L2_SMAC_1)
#define IS2_KL_IP6_TCP_UDP_L3_TTL_GT0                1
#define IS2_KO_IP6_TCP_UDP_L3_TOS                    (IS2_KO_IP6_TCP_UDP_L3_TTL_GT0 + IS2_KL_IP6_TCP_UDP_L3_TTL_GT0)
#define IS2_KL_IP6_TCP_UDP_L3_TOS                    8
#define IS2_KO_IP6_TCP_UDP_L3_IP6_DIP_0              (IS2_KO_IP6_TCP_UDP_L3_TOS + IS2_KL_IP6_TCP_UDP_L3_TOS)
#define IS2_KL_IP6_TCP_UDP_L3_IP6_DIP_0              32
#define IS2_KO_IP6_TCP_UDP_L3_IP6_DIP_1              (IS2_KO_IP6_TCP_UDP_L3_IP6_DIP_0 + IS2_KL_IP6_TCP_UDP_L3_IP6_DIP_0)
#define IS2_KL_IP6_TCP_UDP_L3_IP6_DIP_1              32
#define IS2_KO_IP6_TCP_UDP_L3_IP6_DIP_2              (IS2_KO_IP6_TCP_UDP_L3_IP6_DIP_1 + IS2_KL_IP6_TCP_UDP_L3_IP6_DIP_1)
#define IS2_KL_IP6_TCP_UDP_L3_IP6_DIP_2              32
#define IS2_KO_IP6_TCP_UDP_L3_IP6_DIP_3              (IS2_KO_IP6_TCP_UDP_L3_IP6_DIP_2 + IS2_KL_IP6_TCP_UDP_L3_IP6_DIP_2)
#define IS2_KL_IP6_TCP_UDP_L3_IP6_DIP_3              32
#define IS2_KO_IP6_TCP_UDP_L3_IP6_SIP_0              (IS2_KO_IP6_TCP_UDP_L3_IP6_DIP_3 + IS2_KL_IP6_TCP_UDP_L3_IP6_DIP_3)
#define IS2_KL_IP6_TCP_UDP_L3_IP6_SIP_0              32
#define IS2_KO_IP6_TCP_UDP_L3_IP6_SIP_1              (IS2_KO_IP6_TCP_UDP_L3_IP6_SIP_0 + IS2_KL_IP6_TCP_UDP_L3_IP6_SIP_0)
#define IS2_KL_IP6_TCP_UDP_L3_IP6_SIP_1              32
#define IS2_KO_IP6_TCP_UDP_L3_IP6_SIP_2              (IS2_KO_IP6_TCP_UDP_L3_IP6_SIP_1 + IS2_KL_IP6_TCP_UDP_L3_IP6_SIP_1)
#define IS2_KL_IP6_TCP_UDP_L3_IP6_SIP_2              32
#define IS2_KO_IP6_TCP_UDP_L3_IP6_SIP_3              (IS2_KO_IP6_TCP_UDP_L3_IP6_SIP_2 + IS2_KL_IP6_TCP_UDP_L3_IP6_SIP_2)
#define IS2_KL_IP6_TCP_UDP_L3_IP6_SIP_3              32
#define IS2_KO_IP6_TCP_UDP_DIP_EQ_SIP                (IS2_KO_IP6_TCP_UDP_L3_IP6_SIP_3 + IS2_KL_IP6_TCP_UDP_L3_IP6_SIP_3)
#define IS2_KL_IP6_TCP_UDP_DIP_EQ_SIP                1
#define IS2_KO_IP6_TCP_UDP_TCP                       (IS2_KO_IP6_TCP_UDP_DIP_EQ_SIP + IS2_KL_IP6_TCP_UDP_DIP_EQ_SIP)
#define IS2_KL_IP6_TCP_UDP_TCP                       1
#define IS2_KO_IP6_TCP_UDP_L4_DPORT                  (IS2_KO_IP6_TCP_UDP_TCP + IS2_KL_IP6_TCP_UDP_TCP)
#define IS2_KL_IP6_TCP_UDP_L4_DPORT                  16
#define IS2_KO_IP6_TCP_UDP_L4_SPORT                  (IS2_KO_IP6_TCP_UDP_L4_DPORT + IS2_KL_IP6_TCP_UDP_L4_DPORT)
#define IS2_KL_IP6_TCP_UDP_L4_SPORT                  16
#define IS2_KO_IP6_TCP_UDP_L4_RNG                    (IS2_KO_IP6_TCP_UDP_L4_SPORT + IS2_KL_IP6_TCP_UDP_L4_SPORT)
#define IS2_KL_IP6_TCP_UDP_L4_RNG                    16
#define IS2_KO_IP6_TCP_UDP_SPORT_EQ_DPORT            (IS2_KO_IP6_TCP_UDP_L4_RNG + IS2_KL_IP6_TCP_UDP_L4_RNG)
#define IS2_KL_IP6_TCP_UDP_SPORT_EQ_DPORT            1
#define IS2_KO_IP6_TCP_UDP_SEQUENCE_EQ0              (IS2_KO_IP6_TCP_UDP_SPORT_EQ_DPORT + IS2_KL_IP6_TCP_UDP_SPORT_EQ_DPORT)
#define IS2_KL_IP6_TCP_UDP_SEQUENCE_EQ0              1
#define IS2_KO_IP6_TCP_UDP_L4_FIN                    (IS2_KO_IP6_TCP_UDP_SEQUENCE_EQ0 + IS2_KL_IP6_TCP_UDP_SEQUENCE_EQ0)
#define IS2_KL_IP6_TCP_UDP_L4_FIN                    1
#define IS2_KO_IP6_TCP_UDP_L4_SYN                    (IS2_KO_IP6_TCP_UDP_L4_FIN + IS2_KL_IP6_TCP_UDP_L4_FIN)
#define IS2_KL_IP6_TCP_UDP_L4_SYN                    1
#define IS2_KO_IP6_TCP_UDP_L4_RST                    (IS2_KO_IP6_TCP_UDP_L4_SYN + IS2_KL_IP6_TCP_UDP_L4_SYN)
#define IS2_KL_IP6_TCP_UDP_L4_RST                    1
#define IS2_KO_IP6_TCP_UDP_L4_PSH                    (IS2_KO_IP6_TCP_UDP_L4_RST + IS2_KL_IP6_TCP_UDP_L4_RST)
#define IS2_KL_IP6_TCP_UDP_L4_PSH                    1
#define IS2_KO_IP6_TCP_UDP_L4_ACK                    (IS2_KO_IP6_TCP_UDP_L4_PSH + IS2_KL_IP6_TCP_UDP_L4_PSH)
#define IS2_KL_IP6_TCP_UDP_L4_ACK                    1
#define IS2_KO_IP6_TCP_UDP_L4_URG                    (IS2_KO_IP6_TCP_UDP_L4_ACK + IS2_KL_IP6_TCP_UDP_L4_ACK)
#define IS2_KL_IP6_TCP_UDP_L4_URG                    1
#define IS2_KO_IP6_TCP_UDP_L4_PAYLOAD_0              (IS2_KO_IP6_TCP_UDP_L4_URG + IS2_KL_IP6_TCP_UDP_L4_URG)
#define IS2_KL_IP6_TCP_UDP_L4_PAYLOAD_0              32
#define IS2_KO_IP6_TCP_UDP_L4_PAYLOAD_1              (IS2_KO_IP6_TCP_UDP_L4_PAYLOAD_0 + IS2_KL_IP6_TCP_UDP_L4_PAYLOAD_0)
#define IS2_KL_IP6_TCP_UDP_L4_PAYLOAD_1              32

/* IS2 X12 IP_7TUPLE key fields */
#define IS2_KO_IP_7TUPLE_IP4                         (FA_TGT ? (IS2_KO_X12_L2_SMAC_1 + IS2_KL_X12_L2_SMAC_1) : (IS2_KO_IP_7TUPLE_IP_SNAP + IS2_KL_IP_7TUPLE_IP_SNAP))
#define IS2_KL_IP_7TUPLE_IP4                         1
#define IS2_KO_IP_7TUPLE_L3_TTL_GT0                  (IS2_KO_IP_7TUPLE_IP4 + IS2_KL_IP_7TUPLE_IP4)
#define IS2_KL_IP_7TUPLE_L3_TTL_GT0                  1
#define IS2_KO_IP_7TUPLE_L3_TOS                      (IS2_KO_IP_7TUPLE_L3_TTL_GT0 + IS2_KL_IP_7TUPLE_L3_TTL_GT0)
#define IS2_KL_IP_7TUPLE_L3_TOS                      8
#define IS2_KO_IP_7TUPLE_L3_IP6_DIP_0                (IS2_KO_IP_7TUPLE_L3_TOS + IS2_KL_IP_7TUPLE_L3_TOS)
#define IS2_KL_IP_7TUPLE_L3_IP6_DIP_0                32
#define IS2_KO_IP_7TUPLE_L3_IP6_DIP_1                (IS2_KO_IP_7TUPLE_L3_IP6_DIP_0 + IS2_KL_IP_7TUPLE_L3_IP6_DIP_0)
#define IS2_KL_IP_7TUPLE_L3_IP6_DIP_1                32
#define IS2_KO_IP_7TUPLE_L3_IP6_DIP_2                (IS2_KO_IP_7TUPLE_L3_IP6_DIP_1 + IS2_KL_IP_7TUPLE_L3_IP6_DIP_1)
#define IS2_KL_IP_7TUPLE_L3_IP6_DIP_2                32
#define IS2_KO_IP_7TUPLE_L3_IP6_DIP_3                (IS2_KO_IP_7TUPLE_L3_IP6_DIP_2 + IS2_KL_IP_7TUPLE_L3_IP6_DIP_2)
#define IS2_KL_IP_7TUPLE_L3_IP6_DIP_3                32
#define IS2_KO_IP_7TUPLE_L3_IP6_SIP_0                (IS2_KO_IP_7TUPLE_L3_IP6_DIP_3 + IS2_KL_IP_7TUPLE_L3_IP6_DIP_3)
#define IS2_KL_IP_7TUPLE_L3_IP6_SIP_0                32
#define IS2_KO_IP_7TUPLE_L3_IP6_SIP_1                (IS2_KO_IP_7TUPLE_L3_IP6_SIP_0 + IS2_KL_IP_7TUPLE_L3_IP6_SIP_0)
#define IS2_KL_IP_7TUPLE_L3_IP6_SIP_1                32
#define IS2_KO_IP_7TUPLE_L3_IP6_SIP_2                (IS2_KO_IP_7TUPLE_L3_IP6_SIP_1 + IS2_KL_IP_7TUPLE_L3_IP6_SIP_1)
#define IS2_KL_IP_7TUPLE_L3_IP6_SIP_2                32
#define IS2_KO_IP_7TUPLE_L3_IP6_SIP_3                (IS2_KO_IP_7TUPLE_L3_IP6_SIP_2 + IS2_KL_IP_7TUPLE_L3_IP6_SIP_2)
#define IS2_KL_IP_7TUPLE_L3_IP6_SIP_3                32
#define IS2_KO_IP_7TUPLE_DIP_EQ_SIP                  (IS2_KO_IP_7TUPLE_L3_IP6_SIP_3 + IS2_KL_IP_7TUPLE_L3_IP6_SIP_3)
#define IS2_KL_IP_7TUPLE_DIP_EQ_SIP                  1
#define IS2_KO_IP_7TUPLE_TCP_UDP                     (IS2_KO_IP_7TUPLE_DIP_EQ_SIP + IS2_KL_IP_7TUPLE_DIP_EQ_SIP)
#define IS2_KL_IP_7TUPLE_TCP_UDP                     1
#define IS2_KO_IP_7TUPLE_TCP                         (IS2_KO_IP_7TUPLE_TCP_UDP + IS2_KL_IP_7TUPLE_TCP_UDP)
#define IS2_KL_IP_7TUPLE_TCP                         1
#define IS2_KO_IP_7TUPLE_L4_DPORT                    (IS2_KO_IP_7TUPLE_TCP + IS2_KL_IP_7TUPLE_TCP)
#define IS2_KL_IP_7TUPLE_L4_DPORT                    16
#define IS2_KO_IP_7TUPLE_L4_SPORT                    (IS2_KO_IP_7TUPLE_L4_DPORT + IS2_KL_IP_7TUPLE_L4_DPORT)
#define IS2_KL_IP_7TUPLE_L4_SPORT                    16
#define IS2_KO_IP_7TUPLE_L4_RNG                      (IS2_KO_IP_7TUPLE_L4_SPORT + IS2_KL_IP_7TUPLE_L4_SPORT)
#define IS2_KL_IP_7TUPLE_L4_RNG                      16
#define IS2_KO_IP_7TUPLE_SPORT_EQ_DPORT              (IS2_KO_IP_7TUPLE_L4_RNG + IS2_KL_IP_7TUPLE_L4_RNG)
#define IS2_KL_IP_7TUPLE_SPORT_EQ_DPORT              1
#define IS2_KO_IP_7TUPLE_SEQUENCE_EQ0                (IS2_KO_IP_7TUPLE_SPORT_EQ_DPORT + IS2_KL_IP_7TUPLE_SPORT_EQ_DPORT)
#define IS2_KL_IP_7TUPLE_SEQUENCE_EQ0                1
#define IS2_KO_IP_7TUPLE_L4_FIN                      (IS2_KO_IP_7TUPLE_SEQUENCE_EQ0 + IS2_KL_IP_7TUPLE_SEQUENCE_EQ0)
#define IS2_KL_IP_7TUPLE_L4_FIN                      1
#define IS2_KO_IP_7TUPLE_L4_SYN                      (IS2_KO_IP_7TUPLE_L4_FIN + IS2_KL_IP_7TUPLE_L4_FIN)
#define IS2_KL_IP_7TUPLE_L4_SYN                      1
#define IS2_KO_IP_7TUPLE_L4_RST                      (IS2_KO_IP_7TUPLE_L4_SYN + IS2_KL_IP_7TUPLE_L4_SYN)
#define IS2_KL_IP_7TUPLE_L4_RST                      1
#define IS2_KO_IP_7TUPLE_L4_PSH                      (IS2_KO_IP_7TUPLE_L4_RST + IS2_KL_IP_7TUPLE_L4_RST)
#define IS2_KL_IP_7TUPLE_L4_PSH                      1
#define IS2_KO_IP_7TUPLE_L4_ACK                      (IS2_KO_IP_7TUPLE_L4_PSH + IS2_KL_IP_7TUPLE_L4_PSH)
#define IS2_KL_IP_7TUPLE_L4_ACK                      1
#define IS2_KO_IP_7TUPLE_L4_URG                      (IS2_KO_IP_7TUPLE_L4_ACK + IS2_KL_IP_7TUPLE_L4_ACK)
#define IS2_KL_IP_7TUPLE_L4_URG                      1
#define IS2_KO_IP_7TUPLE_L4_PAYLOAD_0                (IS2_KO_IP_7TUPLE_L4_URG + IS2_KL_IP_7TUPLE_L4_URG)
#define IS2_KL_IP_7TUPLE_L4_PAYLOAD_0                32
#define IS2_KO_IP_7TUPLE_L4_PAYLOAD_1                (IS2_KO_IP_7TUPLE_L4_PAYLOAD_0 + IS2_KL_IP_7TUPLE_L4_PAYLOAD_0)
#define IS2_KL_IP_7TUPLE_L4_PAYLOAD_1                32

/* IS2 X12 CUSTOM_1 key fields */
#define IS2_KO_CUSTOM_1_CUSTOM_14                    (IS2_KO_X12_L3_DST + IS2_KL_X12_L3_DST)
#define IS2_KL_CUSTOM_1_CUSTOM_14                    32
#define IS2_KO_CUSTOM_1_CUSTOM_13                    (IS2_KO_CUSTOM_1_CUSTOM_14 + IS2_KL_CUSTOM_1_CUSTOM_14)
#define IS2_KL_CUSTOM_1_CUSTOM_13                    32
#define IS2_KO_CUSTOM_1_CUSTOM_12                    (IS2_KO_CUSTOM_1_CUSTOM_13 + IS2_KL_CUSTOM_1_CUSTOM_13)
#define IS2_KL_CUSTOM_1_CUSTOM_12                    32
#define IS2_KO_CUSTOM_1_CUSTOM_11                    (IS2_KO_CUSTOM_1_CUSTOM_12 + IS2_KL_CUSTOM_1_CUSTOM_12)
#define IS2_KL_CUSTOM_1_CUSTOM_11                    32
#define IS2_KO_CUSTOM_1_CUSTOM_10                    (IS2_KO_CUSTOM_1_CUSTOM_11 + IS2_KL_CUSTOM_1_CUSTOM_11)
#define IS2_KL_CUSTOM_1_CUSTOM_10                    32
#define IS2_KO_CUSTOM_1_CUSTOM_9                     (IS2_KO_CUSTOM_1_CUSTOM_10 + IS2_KL_CUSTOM_1_CUSTOM_10)
#define IS2_KL_CUSTOM_1_CUSTOM_9                     32
#define IS2_KO_CUSTOM_1_CUSTOM_8                     (IS2_KO_CUSTOM_1_CUSTOM_9 + IS2_KL_CUSTOM_1_CUSTOM_9)
#define IS2_KL_CUSTOM_1_CUSTOM_8                     32
#define IS2_KO_CUSTOM_1_CUSTOM_7                     (IS2_KO_CUSTOM_1_CUSTOM_8 + IS2_KL_CUSTOM_1_CUSTOM_8)
#define IS2_KL_CUSTOM_1_CUSTOM_7                     32
#define IS2_KO_CUSTOM_1_CUSTOM_6                     (IS2_KO_CUSTOM_1_CUSTOM_7 + IS2_KL_CUSTOM_1_CUSTOM_7)
#define IS2_KL_CUSTOM_1_CUSTOM_6                     32
#define IS2_KO_CUSTOM_1_CUSTOM_5                     (IS2_KO_CUSTOM_1_CUSTOM_6 + IS2_KL_CUSTOM_1_CUSTOM_6)
#define IS2_KL_CUSTOM_1_CUSTOM_5                     32
#define IS2_KO_CUSTOM_1_CUSTOM_4                     (IS2_KO_CUSTOM_1_CUSTOM_5 + IS2_KL_CUSTOM_1_CUSTOM_5)
#define IS2_KL_CUSTOM_1_CUSTOM_4                     32
#define IS2_KO_CUSTOM_1_CUSTOM_3                     (IS2_KO_CUSTOM_1_CUSTOM_4 + IS2_KL_CUSTOM_1_CUSTOM_4)
#define IS2_KL_CUSTOM_1_CUSTOM_3                     32
#define IS2_KO_CUSTOM_1_CUSTOM_2                     (IS2_KO_CUSTOM_1_CUSTOM_3 + IS2_KL_CUSTOM_1_CUSTOM_3)
#define IS2_KL_CUSTOM_1_CUSTOM_2                     32
#define IS2_KO_CUSTOM_1_CUSTOM_1                     (IS2_KO_CUSTOM_1_CUSTOM_2 + IS2_KL_CUSTOM_1_CUSTOM_2)
#define IS2_KL_CUSTOM_1_CUSTOM_1                     32
#define IS2_KO_CUSTOM_1_CUSTOM_0                     (IS2_KO_CUSTOM_1_CUSTOM_1 + IS2_KL_CUSTOM_1_CUSTOM_1)
#define IS2_KL_CUSTOM_1_CUSTOM_0                     32

/* IS2 X6 key types */
#define IS2_X6_TYPE_MAC_ETYPE                        0
#define IS2_X6_TYPE_MAC_LLC                          1
#define IS2_X6_TYPE_MAC_SNAP                         2
#define IS2_X6_TYPE_ARP                              3
#define IS2_X6_TYPE_IP4_TCP_UDP                      4
#define IS2_X6_TYPE_IP4_OTHER                        5
#define IS2_X6_TYPE_IP6_STD                          6
#define IS2_X6_TYPE_OAM                              7
#define IS2_X6_TYPE_CUSTOM_2                         8
#define IS2_X6_TYPE_IP6_VID                          9

/* IS2 X6 common key fields */
#define IS2_KO_X6_TYPE                               0
#define IS2_KL_X6_TYPE                               4
#define IS2_KO_X6_FIRST                              (IS2_KO_X6_TYPE + IS2_KL_X6_TYPE)
#define IS2_KL_X6_FIRST                              1
#define IS2_KO_X6_PAG                                (IS2_KO_X6_FIRST + IS2_KL_X6_FIRST)
#define IS2_KL_X6_PAG                                8
#define IS2_KO_X6_IGR_PORT_MASK_L3                   (IS2_KO_X6_PAG + IS2_KL_X6_PAG)
#define IS2_KL_X6_IGR_PORT_MASK_L3                   1
#define IS2_KO_X6_IGR_PORT_MASK_RNG                  (IS2_KO_X6_IGR_PORT_MASK_L3 + IS2_KL_X6_IGR_PORT_MASK_L3)
#define IS2_KL_X6_IGR_PORT_MASK_RNG                  4
#define IS2_KO_X6_IGR_PORT_MASK_SEL                  (IS2_KO_X6_IGR_PORT_MASK_RNG + IS2_KL_X6_IGR_PORT_MASK_RNG)
#define IS2_KL_X6_IGR_PORT_MASK_SEL                  2
#define IS2_KO_X6_IGR_PORT_MASK_0                    (IS2_KO_X6_IGR_PORT_MASK_SEL + IS2_KL_X6_IGR_PORT_MASK_SEL)
#define IS2_KL_X6_IGR_PORT_MASK_0                    32
#define IS2_KO_X6_L2_MC                              (IS2_KO_X6_IGR_PORT_MASK_0 + IS2_KL_X6_IGR_PORT_MASK_0)
#define IS2_KL_X6_L2_MC                              1
#define IS2_KO_X6_L2_BC                              (IS2_KO_X6_L2_MC + IS2_KL_X6_L2_MC)
#define IS2_KL_X6_L2_BC                              1
#define IS2_KO_X6_VLAN_TAGGED                        (IS2_KO_X6_L2_BC + IS2_KL_X6_L2_BC)
#define IS2_KL_X6_VLAN_TAGGED                        1
#define IS2_KO_X6_SERVICE_FRM                        (FA_TGT ? (IS2_KO_X6_VLAN_TAGGED + IS2_KL_X6_VLAN_TAGGED) : (IS2_KO_X6_RED_TAGGED + IS2_KL_X6_RED_TAGGED))
#define IS2_KL_X6_SERVICE_FRM                        1
#define IS2_KO_X6_ISDX                               (IS2_KO_X6_SERVICE_FRM + IS2_KL_X6_SERVICE_FRM)
#define IS2_KL_X6_ISDX                               (FA_TGT ? 12 : 10)
#define IS2_KO_X6_XVID                               (IS2_KO_X6_ISDX + IS2_KL_X6_ISDX)
#define IS2_KL_X6_XVID                               13
#define IS2_KO_X6_DEI                                (IS2_KO_X6_XVID + IS2_KL_X6_XVID)
#define IS2_KL_X6_DEI                                1
#define IS2_KO_X6_PCP                                (IS2_KO_X6_DEI + IS2_KL_X6_DEI)
#define IS2_KL_X6_PCP                                3
#define IS2_KO_X6_L2_FWD                             (IS2_KO_X6_PCP + IS2_KL_X6_PCP)
#define IS2_KL_X6_L2_FWD                             1
#define IS2_KO_X6_L3_SMAC_SIP_MATCH                  (IS2_KO_X6_L2_FWD + IS2_KL_X6_L2_FWD)
#define IS2_KL_X6_L3_SMAC_SIP_MATCH                  1
#define IS2_KO_X6_L3_DMAC_DIP_MATCH                  (IS2_KO_X6_L3_SMAC_SIP_MATCH + IS2_KL_X6_L3_SMAC_SIP_MATCH)
#define IS2_KL_X6_L3_DMAC_DIP_MATCH                  1
#define IS2_KO_X6_L3_RT                              (IS2_KO_X6_L3_DMAC_DIP_MATCH + IS2_KL_X6_L3_DMAC_DIP_MATCH)
#define IS2_KL_X6_L3_RT                              1
#define IS2_KO_X6_L3_DST                             (IS2_KO_X6_L3_RT + IS2_KL_X6_L3_RT)
#define IS2_KL_X6_L3_DST                             1

#define IS2_KO_X6_L2_DMAC_0                          (IS2_KO_X6_L2_FWD + IS2_KL_X6_L2_FWD)
#define IS2_KL_X6_L2_DMAC_0                          32
#define IS2_KO_X6_L2_DMAC_1                          (IS2_KO_X6_L2_DMAC_0 + IS2_KL_X6_L2_DMAC_0)
#define IS2_KL_X6_L2_DMAC_1                          16
#define IS2_KO_X6_L2_SMAC_0                          (IS2_KO_X6_L2_DMAC_1 + IS2_KL_X6_L2_DMAC_1)
#define IS2_KL_X6_L2_SMAC_0                          32
#define IS2_KO_X6_L2_SMAC_1                          (IS2_KO_X6_L2_SMAC_0 + IS2_KL_X6_L2_SMAC_0)
#define IS2_KL_X6_L2_SMAC_1                          16

#define IS2_KO_X6_IP4                                (IS2_KO_X6_L3_DST + IS2_KL_X6_L3_DST)
#define IS2_KL_X6_IP4                                1
#define IS2_KO_X6_L3_FRAGMENT_TYPE                   (IS2_KO_X6_IP4 + IS2_KL_X6_IP4)
#define IS2_KL_X6_L3_FRAGMENT_TYPE                   2
#define IS2_KO_X6_L3_FRAG_INVLD_L4_LEN               (IS2_KO_X6_L3_FRAGMENT_TYPE + IS2_KL_X6_L3_FRAGMENT_TYPE)
#define IS2_KL_X6_L3_FRAG_INVLD_L4_LEN               1
#define IS2_KO_X6_L3_OPTIONS                         (IS2_KO_X6_L3_FRAG_INVLD_L4_LEN + IS2_KL_X6_L3_FRAG_INVLD_L4_LEN)
#define IS2_KL_X6_L3_OPTIONS                         1
#define IS2_KO_X6_L3_TTL_GT0                         (IS2_KO_X6_L3_OPTIONS + IS2_KL_X6_L3_OPTIONS)
#define IS2_KL_X6_L3_TTL_GT0                         1
#define IS2_KO_X6_L3_TOS                             (IS2_KO_X6_L3_TTL_GT0 + IS2_KL_X6_L3_TTL_GT0)
#define IS2_KL_X6_L3_TOS                             8
#define IS2_KO_X6_L3_IP4_DIP                         (IS2_KO_X6_L3_TOS + IS2_KL_X6_L3_TOS)
#define IS2_KL_X6_L3_IP4_DIP                         32
#define IS2_KO_X6_L3_IP4_SIP                         (IS2_KO_X6_L3_IP4_DIP + IS2_KL_X6_L3_IP4_DIP)
#define IS2_KL_X6_L3_IP4_SIP                         32
#define IS2_KO_X6_DIP_EQ_SIP                         (IS2_KO_X6_L3_IP4_SIP + IS2_KL_X6_L3_IP4_SIP)
#define IS2_KL_X6_DIP_EQ_SIP                         1

/* IS2 X6 MAC_ETYPE key fields */
#define IS2_KO_MAC_ETYPE_L2_DMAC_0                   (IS2_KO_X6_L3_DST + IS2_KL_X6_L3_DST)
#define IS2_KL_MAC_ETYPE_L2_DMAC_0                   32
#define IS2_KO_MAC_ETYPE_L2_DMAC_1                   (IS2_KO_MAC_ETYPE_L2_DMAC_0 + IS2_KL_MAC_ETYPE_L2_DMAC_0)
#define IS2_KL_MAC_ETYPE_L2_DMAC_1                   16
#define IS2_KO_MAC_ETYPE_L2_SMAC_0                   (IS2_KO_MAC_ETYPE_L2_DMAC_1 + IS2_KL_MAC_ETYPE_L2_DMAC_1)
#define IS2_KL_MAC_ETYPE_L2_SMAC_0                   32
#define IS2_KO_MAC_ETYPE_L2_SMAC_1                   (IS2_KO_MAC_ETYPE_L2_SMAC_0 + IS2_KL_MAC_ETYPE_L2_SMAC_0)
#define IS2_KL_MAC_ETYPE_L2_SMAC_1                   16
#define IS2_KO_MAC_ETYPE_ETYPE_LEN                   (IS2_KO_MAC_ETYPE_L2_SMAC_1 + IS2_KL_MAC_ETYPE_L2_SMAC_1)
#define IS2_KL_MAC_ETYPE_ETYPE_LEN                   1
#define IS2_KO_MAC_ETYPE_ETYPE                       (IS2_KO_MAC_ETYPE_ETYPE_LEN + IS2_KL_MAC_ETYPE_ETYPE_LEN)
#define IS2_KL_MAC_ETYPE_ETYPE                       16
#define IS2_KO_MAC_ETYPE_L2_PAYLOAD_ETYPE_0          (IS2_KO_MAC_ETYPE_ETYPE + IS2_KL_MAC_ETYPE_ETYPE)
#define IS2_KL_MAC_ETYPE_L2_PAYLOAD_ETYPE_0          32
#define IS2_KO_MAC_ETYPE_L2_PAYLOAD_ETYPE_1          (IS2_KO_MAC_ETYPE_L2_PAYLOAD_ETYPE_0 + IS2_KL_MAC_ETYPE_L2_PAYLOAD_ETYPE_0)
#define IS2_KL_MAC_ETYPE_L2_PAYLOAD_ETYPE_1          32
#define IS2_KO_MAC_ETYPE_L4_RNG                      (IS2_KO_MAC_ETYPE_L2_PAYLOAD_ETYPE_1 + IS2_KL_MAC_ETYPE_L2_PAYLOAD_ETYPE_1)
#define IS2_KL_MAC_ETYPE_L4_RNG                      16
#define IS2_KO_MAC_ETYPE_OAM_CCM_CNTS_EQ0            (IS2_KO_MAC_ETYPE_L4_RNG + IS2_KL_MAC_ETYPE_L4_RNG)
#define IS2_KL_MAC_ETYPE_OAM_CCM_CNTS_EQ0            1
#define IS2_KO_MAC_ETYPE_OAM_Y1731                   (IS2_KO_MAC_ETYPE_OAM_CCM_CNTS_EQ0 + IS2_KL_MAC_ETYPE_OAM_CCM_CNTS_EQ0)
#define IS2_KL_MAC_ETYPE_OAM_Y1731                   1

/* IS2 X6 MAC_LLC key fields */
#define IS2_KO_MAC_LLC_L2_LLC_0                      (IS2_KO_X6_L2_SMAC_1 + IS2_KL_X6_L2_SMAC_1)
#define IS2_KL_MAC_LLC_L2_LLC_0                      32
#define IS2_KO_MAC_LLC_L2_LLC_1                      (IS2_KO_MAC_LLC_L2_LLC_0 + IS2_KL_MAC_LLC_L2_LLC_0)
#define IS2_KL_MAC_LLC_L2_LLC_1                      8
#define IS2_KO_MAC_LLC_L4_RNG                        (IS2_KO_MAC_LLC_L2_LLC_1 + IS2_KL_MAC_LLC_L2_LLC_1)
#define IS2_KL_MAC_LLC_L4_RNG                        16

/* IS2 X6 MAC_SNAP key fields */
#define IS2_KO_MAC_SNAP_L2_SNAP_0                    (IS2_KO_X6_L2_SMAC_1 + IS2_KL_X6_L2_SMAC_1)
#define IS2_KL_MAC_SNAP_L2_SNAP_0                    32
#define IS2_KO_MAC_SNAP_L2_SNAP_1                    (IS2_KO_MAC_SNAP_L2_SNAP_0 + IS2_KL_MAC_SNAP_L2_SNAP_0)
#define IS2_KL_MAC_SNAP_L2_SNAP_1                    8
#define IS2_KO_MAC_SNAP_L4_RNG                       (IS2_KO_MAC_SNAP_L2_SNAP_1 + IS2_KL_MAC_SNAP_L2_SNAP_1)
#define IS2_KL_MAC_SNAP_L4_RNG                       16

/* IS2 X6 ARP key fields */
#define IS2_KO_ARP_L2_SMAC_0                         (IS2_KO_X6_L2_FWD + IS2_KL_X6_L2_FWD)
#define IS2_KL_ARP_L2_SMAC_0                         32
#define IS2_KO_ARP_L2_SMAC_1                         (IS2_KO_ARP_L2_SMAC_0 + IS2_KL_ARP_L2_SMAC_0)
#define IS2_KL_ARP_L2_SMAC_1                         16
#define IS2_KO_ARP_ARP_ADDR_SPACE_OK                 (IS2_KO_ARP_L2_SMAC_1 + IS2_KL_ARP_L2_SMAC_1)
#define IS2_KL_ARP_ARP_ADDR_SPACE_OK                 1
#define IS2_KO_ARP_ARP_PROTO_SPACE_OK                (IS2_KO_ARP_ARP_ADDR_SPACE_OK + IS2_KL_ARP_ARP_ADDR_SPACE_OK)
#define IS2_KL_ARP_ARP_PROTO_SPACE_OK                1
#define IS2_KO_ARP_ARP_LEN_OK                        (IS2_KO_ARP_ARP_PROTO_SPACE_OK + IS2_KL_ARP_ARP_PROTO_SPACE_OK)
#define IS2_KL_ARP_ARP_LEN_OK                        1
#define IS2_KO_ARP_ARP_TGT_MATCH                     (IS2_KO_ARP_ARP_LEN_OK + IS2_KL_ARP_ARP_LEN_OK)
#define IS2_KL_ARP_ARP_TGT_MATCH                     1
#define IS2_KO_ARP_ARP_SENDER_MATCH                  (IS2_KO_ARP_ARP_TGT_MATCH + IS2_KL_ARP_ARP_TGT_MATCH)
#define IS2_KL_ARP_ARP_SENDER_MATCH                  1
#define IS2_KO_ARP_ARP_OPCODE_UNKNOWN                (IS2_KO_ARP_ARP_SENDER_MATCH + IS2_KL_ARP_ARP_SENDER_MATCH)
#define IS2_KL_ARP_ARP_OPCODE_UNKNOWN                1
#define IS2_KO_ARP_ARP_OPCODE                        (IS2_KO_ARP_ARP_OPCODE_UNKNOWN + IS2_KL_ARP_ARP_OPCODE_UNKNOWN)
#define IS2_KL_ARP_ARP_OPCODE                        2
#define IS2_KO_ARP_L3_IP4_DIP                        (IS2_KO_ARP_ARP_OPCODE + IS2_KL_ARP_ARP_OPCODE)
#define IS2_KL_ARP_L3_IP4_DIP                        32
#define IS2_KO_ARP_L3_IP4_SIP                        (IS2_KO_ARP_L3_IP4_DIP + IS2_KL_ARP_L3_IP4_DIP)
#define IS2_KL_ARP_L3_IP4_SIP                        32
#define IS2_KO_ARP_DIP_EQ_SIP                        (IS2_KO_ARP_L3_IP4_SIP + IS2_KL_ARP_L3_IP4_SIP)
#define IS2_KL_ARP_DIP_EQ_SIP                        1
#define IS2_KO_ARP_L4_RNG                            (IS2_KO_ARP_DIP_EQ_SIP + IS2_KL_ARP_DIP_EQ_SIP)
#define IS2_KL_ARP_L4_RNG                            16

/* IS2 X6 IP4_TCP_UDP key fields */
#define IS2_KO_IP4_TCP_UDP_TCP                       (IS2_KO_X6_DIP_EQ_SIP + IS2_KL_X6_DIP_EQ_SIP)
#define IS2_KL_IP4_TCP_UDP_TCP                       1
#define IS2_KO_IP4_TCP_UDP_L4_DPORT                  (IS2_KO_IP4_TCP_UDP_TCP + IS2_KL_IP4_TCP_UDP_TCP)
#define IS2_KL_IP4_TCP_UDP_L4_DPORT                  16
#define IS2_KO_IP4_TCP_UDP_L4_SPORT                  (IS2_KO_IP4_TCP_UDP_L4_DPORT + IS2_KL_IP4_TCP_UDP_L4_DPORT)
#define IS2_KL_IP4_TCP_UDP_L4_SPORT                  16
#define IS2_KO_IP4_TCP_UDP_L4_RNG                    (IS2_KO_IP4_TCP_UDP_L4_SPORT + IS2_KL_IP4_TCP_UDP_L4_SPORT)
#define IS2_KL_IP4_TCP_UDP_L4_RNG                    16
#define IS2_KO_IP4_TCP_UDP_SPORT_EQ_DPORT            (IS2_KO_IP4_TCP_UDP_L4_RNG + IS2_KL_IP4_TCP_UDP_L4_RNG)
#define IS2_KL_IP4_TCP_UDP_SPORT_EQ_DPORT            1
#define IS2_KO_IP4_TCP_UDP_SEQUENCE_EQ0              (IS2_KO_IP4_TCP_UDP_SPORT_EQ_DPORT + IS2_KL_IP4_TCP_UDP_SPORT_EQ_DPORT)
#define IS2_KL_IP4_TCP_UDP_SEQUENCE_EQ0              1
#define IS2_KO_IP4_TCP_UDP_L4_FIN                    (IS2_KO_IP4_TCP_UDP_SEQUENCE_EQ0 + IS2_KL_IP4_TCP_UDP_SEQUENCE_EQ0)
#define IS2_KL_IP4_TCP_UDP_L4_FIN                    1
#define IS2_KO_IP4_TCP_UDP_L4_SYN                    (IS2_KO_IP4_TCP_UDP_L4_FIN + IS2_KL_IP4_TCP_UDP_L4_FIN)
#define IS2_KL_IP4_TCP_UDP_L4_SYN                    1
#define IS2_KO_IP4_TCP_UDP_L4_RST                    (IS2_KO_IP4_TCP_UDP_L4_SYN + IS2_KL_IP4_TCP_UDP_L4_SYN)
#define IS2_KL_IP4_TCP_UDP_L4_RST                    1
#define IS2_KO_IP4_TCP_UDP_L4_PSH                    (IS2_KO_IP4_TCP_UDP_L4_RST + IS2_KL_IP4_TCP_UDP_L4_RST)
#define IS2_KL_IP4_TCP_UDP_L4_PSH                    1
#define IS2_KO_IP4_TCP_UDP_L4_ACK                    (IS2_KO_IP4_TCP_UDP_L4_PSH + IS2_KL_IP4_TCP_UDP_L4_PSH)
#define IS2_KL_IP4_TCP_UDP_L4_ACK                    1
#define IS2_KO_IP4_TCP_UDP_L4_URG                    (IS2_KO_IP4_TCP_UDP_L4_ACK + IS2_KL_IP4_TCP_UDP_L4_ACK)
#define IS2_KL_IP4_TCP_UDP_L4_URG                    1
#define IS2_KO_IP4_TCP_UDP_L4_PAYLOAD_0              (IS2_KO_IP4_TCP_UDP_L4_URG + IS2_KL_IP4_TCP_UDP_L4_URG)
#define IS2_KL_IP4_TCP_UDP_L4_PAYLOAD_0              32
#define IS2_KO_IP4_TCP_UDP_L4_PAYLOAD_1              (IS2_KO_IP4_TCP_UDP_L4_PAYLOAD_0 + IS2_KL_IP4_TCP_UDP_L4_PAYLOAD_0)
#define IS2_KL_IP4_TCP_UDP_L4_PAYLOAD_1              32

/* IS2 X6 IP4_OTHER key fields */
#define IS2_KO_IP4_OTHER_L3_PROTO                    (IS2_KO_X6_DIP_EQ_SIP + IS2_KL_X6_DIP_EQ_SIP)
#define IS2_KL_IP4_OTHER_L3_PROTO                    8
#define IS2_KO_IP4_OTHER_L4_RNG                      (IS2_KO_IP4_OTHER_L3_PROTO + IS2_KL_IP4_OTHER_L3_PROTO)
#define IS2_KL_IP4_OTHER_L4_RNG                      16
#define IS2_KO_IP4_OTHER_L3_PAYLOAD_0                (IS2_KO_IP4_OTHER_L4_RNG + IS2_KL_IP4_OTHER_L4_RNG)
#define IS2_KL_IP4_OTHER_L3_PAYLOAD_0                32
#define IS2_KO_IP4_OTHER_L3_PAYLOAD_1                (IS2_KO_IP4_OTHER_L3_PAYLOAD_0 + IS2_KL_IP4_OTHER_L3_PAYLOAD_0)
#define IS2_KL_IP4_OTHER_L3_PAYLOAD_1                32
#define IS2_KO_IP4_OTHER_L3_PAYLOAD_2                (IS2_KO_IP4_OTHER_L3_PAYLOAD_1 + IS2_KL_IP4_OTHER_L3_PAYLOAD_1)
#define IS2_KL_IP4_OTHER_L3_PAYLOAD_2                32

/* IS2 X6 IP6_STD key fields */
#define IS2_KO_IP6_STD_L3_TTL_GT0                    (IS2_KO_X6_L3_DST + IS2_KL_X6_L3_DST)
#define IS2_KL_IP6_STD_L3_TTL_GT0                    1
#define IS2_KO_IP6_STD_L3_IP6_SIP_0                  (IS2_KO_IP6_STD_L3_TTL_GT0 + IS2_KL_IP6_STD_L3_TTL_GT0)
#define IS2_KL_IP6_STD_L3_IP6_SIP_0                  32
#define IS2_KO_IP6_STD_L3_IP6_SIP_1                  (IS2_KO_IP6_STD_L3_IP6_SIP_0 + IS2_KL_IP6_STD_L3_IP6_SIP_0)
#define IS2_KL_IP6_STD_L3_IP6_SIP_1                  32
#define IS2_KO_IP6_STD_L3_IP6_SIP_2                  (IS2_KO_IP6_STD_L3_IP6_SIP_1 + IS2_KL_IP6_STD_L3_IP6_SIP_1)
#define IS2_KL_IP6_STD_L3_IP6_SIP_2                  32
#define IS2_KO_IP6_STD_L3_IP6_SIP_3                  (IS2_KO_IP6_STD_L3_IP6_SIP_2 + IS2_KL_IP6_STD_L3_IP6_SIP_2)
#define IS2_KL_IP6_STD_L3_IP6_SIP_3                  32
#define IS2_KO_IP6_STD_DIP_EQ_SIP                    (IS2_KO_IP6_STD_L3_IP6_SIP_3 + IS2_KL_IP6_STD_L3_IP6_SIP_3)
#define IS2_KL_IP6_STD_DIP_EQ_SIP                    1
#define IS2_KO_IP6_STD_L3_PROTO                      (IS2_KO_IP6_STD_DIP_EQ_SIP + IS2_KL_IP6_STD_DIP_EQ_SIP)
#define IS2_KL_IP6_STD_L3_PROTO                      8
#define IS2_KO_IP6_STD_L4_RNG                        (IS2_KO_IP6_STD_L3_PROTO + IS2_KL_IP6_STD_L3_PROTO)
#define IS2_KL_IP6_STD_L4_RNG                        16
#define IS2_KO_IP6_STD_L3_PAYLOAD_0                  (IS2_KO_IP6_STD_L4_RNG + IS2_KL_IP6_STD_L4_RNG)
#define IS2_KL_IP6_STD_L3_PAYLOAD_0                  32
#define IS2_KO_IP6_STD_L3_PAYLOAD_1                  (IS2_KO_IP6_STD_L3_PAYLOAD_0 + IS2_KL_IP6_STD_L3_PAYLOAD_0)
#define IS2_KL_IP6_STD_L3_PAYLOAD_1                  8

/* IS2 X6 OAM key fields */
#define IS2_KO_OAM_L4_RNG                            (IS2_KO_X6_L2_SMAC_1 + IS2_KL_X6_L2_SMAC_1)
#define IS2_KL_OAM_L4_RNG                            16
#define IS2_KO_OAM_OAM_MEL_FLAGS                     (IS2_KO_OAM_L4_RNG + IS2_KL_OAM_L4_RNG)
#define IS2_KL_OAM_OAM_MEL_FLAGS                     7
#define IS2_KO_OAM_OAM_VER                           (IS2_KO_OAM_OAM_MEL_FLAGS + IS2_KL_OAM_OAM_MEL_FLAGS)
#define IS2_KL_OAM_OAM_VER                           5
#define IS2_KO_OAM_OAM_OPCODE                        (IS2_KO_OAM_OAM_VER + IS2_KL_OAM_OAM_VER)
#define IS2_KL_OAM_OAM_OPCODE                        8
#define IS2_KO_OAM_OAM_FLAGS                         (IS2_KO_OAM_OAM_OPCODE + IS2_KL_OAM_OAM_OPCODE)
#define IS2_KL_OAM_OAM_FLAGS                         8
#define IS2_KO_OAM_OAM_MEPID                         (IS2_KO_OAM_OAM_FLAGS + IS2_KL_OAM_OAM_FLAGS)
#define IS2_KL_OAM_OAM_MEPID                         16
#define IS2_KO_OAM_OAM_CCM_CNTS_EQ0                  (IS2_KO_OAM_OAM_MEPID + IS2_KL_OAM_OAM_MEPID)
#define IS2_KL_OAM_OAM_CCM_CNTS_EQ0                  1
#define IS2_KO_OAM_OAM_TYPE                          (IS2_KO_OAM_OAM_CCM_CNTS_EQ0 + IS2_KL_OAM_OAM_CCM_CNTS_EQ0)
#define IS2_KL_OAM_OAM_TYPE                          2

/* IS2 X6 CUSTOM_2 key fields */
#define IS2_KO_CUSTOM_2_CUSTOM_5                     (IS2_KO_X6_L3_DST + IS2_KL_X6_L3_DST)
#define IS2_KL_CUSTOM_2_CUSTOM_5                     32
#define IS2_KO_CUSTOM_2_CUSTOM_4                     (IS2_KO_CUSTOM_2_CUSTOM_5 + IS2_KL_CUSTOM_2_CUSTOM_5)
#define IS2_KL_CUSTOM_2_CUSTOM_4                     32
#define IS2_KO_CUSTOM_2_CUSTOM_3                     (IS2_KO_CUSTOM_2_CUSTOM_4 + IS2_KL_CUSTOM_2_CUSTOM_4)
#define IS2_KL_CUSTOM_2_CUSTOM_3                     32
#define IS2_KO_CUSTOM_2_CUSTOM_2                     (IS2_KO_CUSTOM_2_CUSTOM_3 + IS2_KL_CUSTOM_2_CUSTOM_3)
#define IS2_KL_CUSTOM_2_CUSTOM_2                     32
#define IS2_KO_CUSTOM_2_CUSTOM_1                     (IS2_KO_CUSTOM_2_CUSTOM_2 + IS2_KL_CUSTOM_2_CUSTOM_2)
#define IS2_KL_CUSTOM_2_CUSTOM_1                     32
#define IS2_KO_CUSTOM_2_CUSTOM_0                     (IS2_KO_CUSTOM_2_CUSTOM_1 + IS2_KL_CUSTOM_2_CUSTOM_1)
#define IS2_KL_CUSTOM_2_CUSTOM_0                     32

/* IS2 X6 IP6_VID key fields */
#define IS2_KO_IP6_VID_SERVICE_FRM                   (IS2_KO_X6_PAG + IS2_KL_X6_PAG)
#define IS2_KL_IP6_VID_SERVICE_FRM                   1
#define IS2_KO_IP6_VID_ISDX                          (IS2_KO_IP6_VID_SERVICE_FRM + IS2_KL_IP6_VID_SERVICE_FRM)
#define IS2_KL_IP6_VID_ISDX                          (FA_TGT ? 12 : 10)
#define IS2_KO_IP6_VID_XVID                          (IS2_KO_IP6_VID_ISDX + IS2_KL_IP6_VID_ISDX)
#define IS2_KL_IP6_VID_XVID                          13
#define IS2_KO_IP6_VID_L3_SMAC_SIP_MATCH             (IS2_KO_IP6_VID_XVID + IS2_KL_IP6_VID_XVID)
#define IS2_KL_IP6_VID_L3_SMAC_SIP_MATCH             1
#define IS2_KO_IP6_VID_L3_DMAC_DIP_MATCH             (IS2_KO_IP6_VID_L3_SMAC_SIP_MATCH + IS2_KL_IP6_VID_L3_SMAC_SIP_MATCH)
#define IS2_KL_IP6_VID_L3_DMAC_DIP_MATCH             1
#define IS2_KO_IP6_VID_L3_RT                         (IS2_KO_IP6_VID_L3_DMAC_DIP_MATCH + IS2_KL_IP6_VID_L3_DMAC_DIP_MATCH)
#define IS2_KL_IP6_VID_L3_RT                         1
#define IS2_KO_IP6_VID_L3_DST                        (IS2_KO_IP6_VID_L3_RT + IS2_KL_IP6_VID_L3_RT)
#define IS2_KL_IP6_VID_L3_DST                        1
#define IS2_KO_IP6_VID_L3_IP6_DIP_0                  (IS2_KO_IP6_VID_L3_DST + IS2_KL_IP6_VID_L3_DST)
#define IS2_KL_IP6_VID_L3_IP6_DIP_0                  32
#define IS2_KO_IP6_VID_L3_IP6_DIP_1                  (IS2_KO_IP6_VID_L3_IP6_DIP_0 + IS2_KL_IP6_VID_L3_IP6_DIP_0)
#define IS2_KL_IP6_VID_L3_IP6_DIP_1                  32
#define IS2_KO_IP6_VID_L3_IP6_DIP_2                  (IS2_KO_IP6_VID_L3_IP6_DIP_1 + IS2_KL_IP6_VID_L3_IP6_DIP_1)
#define IS2_KL_IP6_VID_L3_IP6_DIP_2                  32
#define IS2_KO_IP6_VID_L3_IP6_DIP_3                  (IS2_KO_IP6_VID_L3_IP6_DIP_2 + IS2_KL_IP6_VID_L3_IP6_DIP_2)
#define IS2_KL_IP6_VID_L3_IP6_DIP_3                  32
#define IS2_KO_IP6_VID_L3_IP6_SIP_0                  (IS2_KO_IP6_VID_L3_IP6_DIP_3 + IS2_KL_IP6_VID_L3_IP6_DIP_3)
#define IS2_KL_IP6_VID_L3_IP6_SIP_0                  32
#define IS2_KO_IP6_VID_L3_IP6_SIP_1                  (IS2_KO_IP6_VID_L3_IP6_SIP_0 + IS2_KL_IP6_VID_L3_IP6_SIP_0)
#define IS2_KL_IP6_VID_L3_IP6_SIP_1                  32
#define IS2_KO_IP6_VID_L3_IP6_SIP_2                  (IS2_KO_IP6_VID_L3_IP6_SIP_1 + IS2_KL_IP6_VID_L3_IP6_SIP_1)
#define IS2_KL_IP6_VID_L3_IP6_SIP_2                  32
#define IS2_KO_IP6_VID_L3_IP6_SIP_3                  (IS2_KO_IP6_VID_L3_IP6_SIP_2 + IS2_KL_IP6_VID_L3_IP6_SIP_2)
#define IS2_KL_IP6_VID_L3_IP6_SIP_3                  32

/* IS2 X3 IP4_VID key fields */
#define IS2_KO_IP4_VID_FIRST                         0
#define IS2_KL_IP4_VID_FIRST                         1
#define IS2_KO_IP4_VID_PAG                           (IS2_KO_IP4_VID_FIRST + IS2_KL_IP4_VID_FIRST)
#define IS2_KL_IP4_VID_PAG                           8
#define IS2_KO_IP4_VID_SERVICE_FRM                   (IS2_KO_IP4_VID_PAG + IS2_KL_IP4_VID_PAG)
#define IS2_KL_IP4_VID_SERVICE_FRM                   1
#define IS2_KO_IP4_VID_ISDX                          (IS2_KO_IP4_VID_SERVICE_FRM + IS2_KL_IP4_VID_SERVICE_FRM)
#define IS2_KL_IP4_VID_ISDX                          (FA_TGT ? 12 : 10)
#define IS2_KO_IP4_VID_XVID                          (IS2_KO_IP4_VID_ISDX + IS2_KL_IP4_VID_ISDX)
#define IS2_KL_IP4_VID_XVID                          13
#define IS2_KO_IP4_VID_L3_SMAC_SIP_MATCH             (IS2_KO_IP4_VID_XVID + IS2_KL_IP4_VID_XVID)
#define IS2_KL_IP4_VID_L3_SMAC_SIP_MATCH             1
#define IS2_KO_IP4_VID_L3_DMAC_DIP_MATCH             (IS2_KO_IP4_VID_L3_SMAC_SIP_MATCH + IS2_KL_IP4_VID_L3_SMAC_SIP_MATCH)
#define IS2_KL_IP4_VID_L3_DMAC_DIP_MATCH             1
#define IS2_KO_IP4_VID_L3_RT                         (IS2_KO_IP4_VID_L3_DMAC_DIP_MATCH + IS2_KL_IP4_VID_L3_DMAC_DIP_MATCH)
#define IS2_KL_IP4_VID_L3_RT                         1
#define IS2_KO_IP4_VID_L3_DST                        (IS2_KO_IP4_VID_L3_RT + IS2_KL_IP4_VID_L3_RT)
#define IS2_KL_IP4_VID_L3_DST                        1
#define IS2_KO_IP4_VID_L3_IP4_DIP                    (IS2_KO_IP4_VID_L3_DST + IS2_KL_IP4_VID_L3_DST)
#define IS2_KL_IP4_VID_L3_IP4_DIP                    32
#define IS2_KO_IP4_VID_L3_IP4_SIP                    (IS2_KO_IP4_VID_L3_IP4_DIP + IS2_KL_IP4_VID_L3_IP4_DIP)
#define IS2_KL_IP4_VID_L3_IP4_SIP                    32

/* IS2 X3 BASE_TYPE action fields */
#define IS2_AO_BASE_TYPE_IS_INNER_ACL                0
#define IS2_AL_BASE_TYPE_IS_INNER_ACL                1
#define IS2_AO_BASE_TYPE_PIPELINE_FORCE_ENA          (IS2_AO_BASE_TYPE_IS_INNER_ACL + IS2_AL_BASE_TYPE_IS_INNER_ACL)
#define IS2_AL_BASE_TYPE_PIPELINE_FORCE_ENA          1
#define IS2_AO_BASE_TYPE_PIPELINE_PT                 (IS2_AO_BASE_TYPE_PIPELINE_FORCE_ENA + IS2_AL_BASE_TYPE_PIPELINE_FORCE_ENA)
#define IS2_AL_BASE_TYPE_PIPELINE_PT                 5
#define IS2_AO_BASE_TYPE_HIT_ME_ONCE                 (IS2_AO_BASE_TYPE_PIPELINE_PT + IS2_AL_BASE_TYPE_PIPELINE_PT)
#define IS2_AL_BASE_TYPE_HIT_ME_ONCE                 1
#define IS2_AO_BASE_TYPE_INTR_ENA                    (IS2_AO_BASE_TYPE_HIT_ME_ONCE + IS2_AL_BASE_TYPE_HIT_ME_ONCE)
#define IS2_AL_BASE_TYPE_INTR_ENA                    1
#define IS2_AO_BASE_TYPE_CPU_COPY_ENA                (IS2_AO_BASE_TYPE_INTR_ENA + IS2_AL_BASE_TYPE_INTR_ENA)
#define IS2_AL_BASE_TYPE_CPU_COPY_ENA                1
#define IS2_AO_BASE_TYPE_CPU_QU_NUM                  (IS2_AO_BASE_TYPE_CPU_COPY_ENA + IS2_AL_BASE_TYPE_CPU_COPY_ENA)
#define IS2_AL_BASE_TYPE_CPU_QU_NUM                  3
#define IS2_AO_BASE_TYPE_CPU_DIS                     (FA_TGT ? (IS2_AO_BASE_TYPE_CPU_QU_NUM + IS2_AL_BASE_TYPE_CPU_QU_NUM) : (IS2_AO_BASE_TYPE_CPU_DIS_MODE + IS2_AL_BASE_TYPE_CPU_DIS_MODE))
#define IS2_AL_BASE_TYPE_CPU_DIS                     1
#define IS2_AO_BASE_TYPE_LRN_DIS                     (IS2_AO_BASE_TYPE_CPU_DIS + IS2_AL_BASE_TYPE_CPU_DIS)
#define IS2_AL_BASE_TYPE_LRN_DIS                     1
#define IS2_AO_BASE_TYPE_RT_DIS                      (IS2_AO_BASE_TYPE_LRN_DIS + IS2_AL_BASE_TYPE_LRN_DIS)
#define IS2_AL_BASE_TYPE_RT_DIS                      1
#define IS2_AO_BASE_TYPE_POLICE_ENA                  (IS2_AO_BASE_TYPE_RT_DIS + IS2_AL_BASE_TYPE_RT_DIS)
#define IS2_AL_BASE_TYPE_POLICE_ENA                  1
#define IS2_AO_BASE_TYPE_POLICE_IDX                  (IS2_AO_BASE_TYPE_POLICE_ENA + IS2_AL_BASE_TYPE_POLICE_ENA)
#define IS2_AL_BASE_TYPE_POLICE_IDX                  (FA_TGT ? 6 : 5)
#define IS2_AO_BASE_TYPE_IGNORE_PIPELINE_CTRL        (IS2_AO_BASE_TYPE_POLICE_IDX + IS2_AL_BASE_TYPE_POLICE_IDX)
#define IS2_AL_BASE_TYPE_IGNORE_PIPELINE_CTRL        1
#define IS2_AO_BASE_TYPE_DLB_OFFSET                  (IS2_AO_BASE_TYPE_IGNORE_PIPELINE_CTRL + IS2_AL_BASE_TYPE_IGNORE_PIPELINE_CTRL)
#define IS2_AL_BASE_TYPE_DLB_OFFSET                  3
#define IS2_AO_BASE_TYPE_MASK_MODE                   (IS2_AO_BASE_TYPE_DLB_OFFSET + IS2_AL_BASE_TYPE_DLB_OFFSET)
#define IS2_AL_BASE_TYPE_MASK_MODE                   3
#define IS2_AO_BASE_TYPE_PORT_MASK_0                 (IS2_AO_BASE_TYPE_MASK_MODE + IS2_AL_BASE_TYPE_MASK_MODE)
#define IS2_AL_BASE_TYPE_PORT_MASK_0                 32
#define IS2_AO_BASE_TYPE_PORT_MASK_1                 (IS2_AO_BASE_TYPE_PORT_MASK_0 + IS2_AL_BASE_TYPE_PORT_MASK_0)
#define IS2_AL_BASE_TYPE_PORT_MASK_1                 (FA_TGT ? 32 : 5)
#define IS2_AO_BASE_TYPE_PORT_MASK_2                 (IS2_AO_BASE_TYPE_PORT_MASK_1 + IS2_AL_BASE_TYPE_PORT_MASK_1)
#define IS2_AL_BASE_TYPE_PORT_MASK_2                 4
#define IS2_AO_BASE_TYPE_RSDX_ENA                    (FA_TGT ? (IS2_AO_BASE_TYPE_PORT_MASK_2 + IS2_AL_BASE_TYPE_PORT_MASK_2) : (IS2_AO_BASE_TYPE_PORT_MASK_1 + IS2_AL_BASE_TYPE_PORT_MASK_1))
#define IS2_AL_BASE_TYPE_RSDX_ENA                    1
#define IS2_AO_BASE_TYPE_RSDX_VAL                    (IS2_AO_BASE_TYPE_RSDX_ENA + IS2_AL_BASE_TYPE_RSDX_ENA)
#define IS2_AL_BASE_TYPE_RSDX_VAL                    (FA_TGT ? 12 : 10)
#define IS2_AO_BASE_TYPE_MIRROR_PROBE                (IS2_AO_BASE_TYPE_RSDX_VAL + IS2_AL_BASE_TYPE_RSDX_VAL)
#define IS2_AL_BASE_TYPE_MIRROR_PROBE                2
#define IS2_AO_BASE_TYPE_REW_CMD                     (IS2_AO_BASE_TYPE_MIRROR_PROBE + IS2_AL_BASE_TYPE_MIRROR_PROBE)
#define IS2_AL_BASE_TYPE_REW_CMD                     (FA_TGT ? 11 : 16)
#define IS2_AO_BASE_TYPE_TTL_UPDATE_ENA              (IS2_AO_BASE_TYPE_REW_CMD + IS2_AL_BASE_TYPE_REW_CMD)
#define IS2_AL_BASE_TYPE_TTL_UPDATE_ENA              1
#define IS2_AO_BASE_TYPE_SAM_SEQ_ENA                 (IS2_AO_BASE_TYPE_TTL_UPDATE_ENA + IS2_AL_BASE_TYPE_TTL_UPDATE_ENA)
#define IS2_AL_BASE_TYPE_SAM_SEQ_ENA                 1
#define IS2_AO_BASE_TYPE_TCP_UDP_ENA                 (IS2_AO_BASE_TYPE_SAM_SEQ_ENA + IS2_AL_BASE_TYPE_SAM_SEQ_ENA)
#define IS2_AL_BASE_TYPE_TCP_UDP_ENA                 1
#define IS2_AO_BASE_TYPE_TCP_UDP_DPORT               (IS2_AO_BASE_TYPE_TCP_UDP_ENA + IS2_AL_BASE_TYPE_TCP_UDP_ENA)
#define IS2_AL_BASE_TYPE_TCP_UDP_DPORT               16
#define IS2_AO_BASE_TYPE_TCP_UDP_SPORT               (IS2_AO_BASE_TYPE_TCP_UDP_DPORT + IS2_AL_BASE_TYPE_TCP_UDP_DPORT)
#define IS2_AL_BASE_TYPE_TCP_UDP_SPORT               16
#define IS2_AO_BASE_TYPE_MATCH_ID                    (IS2_AO_BASE_TYPE_TCP_UDP_SPORT + IS2_AL_BASE_TYPE_TCP_UDP_SPORT)
#define IS2_AL_BASE_TYPE_MATCH_ID                    16
#define IS2_AO_BASE_TYPE_MATCH_ID_MASK               (IS2_AO_BASE_TYPE_MATCH_ID + IS2_AL_BASE_TYPE_MATCH_ID)
#define IS2_AL_BASE_TYPE_MATCH_ID_MASK               16
#define IS2_AO_BASE_TYPE_CNT_ID                      (IS2_AO_BASE_TYPE_MATCH_ID_MASK + IS2_AL_BASE_TYPE_MATCH_ID_MASK)
#define IS2_AL_BASE_TYPE_CNT_ID                      (FA_TGT ? 12 : 10)
#define IS2_AO_BASE_TYPE_SWAP_MAC_ENA                (IS2_AO_BASE_TYPE_CNT_ID + IS2_AL_BASE_TYPE_CNT_ID)
#define IS2_AL_BASE_TYPE_SWAP_MAC_ENA                1
#define IS2_AO_BASE_TYPE_ACL_RT_MODE                 (FA_TGT ? (IS2_AO_BASE_TYPE_SWAP_MAC_ENA + IS2_AL_BASE_TYPE_SWAP_MAC_ENA) : (IS2_AO_BASE_TYPE_MAC_REW_SEL + IS2_AL_BASE_TYPE_MAC_REW_SEL))
#define IS2_AL_BASE_TYPE_ACL_RT_MODE                 4
#define IS2_AO_BASE_TYPE_ACL_MAC_0                   (IS2_AO_BASE_TYPE_ACL_RT_MODE + IS2_AL_BASE_TYPE_ACL_RT_MODE)
#define IS2_AL_BASE_TYPE_ACL_MAC_0                   32
#define IS2_AO_BASE_TYPE_ACL_MAC_1                   (IS2_AO_BASE_TYPE_ACL_MAC_0 + IS2_AL_BASE_TYPE_ACL_MAC_0)
#define IS2_AL_BASE_TYPE_ACL_MAC_1                   16
#define IS2_AO_BASE_TYPE_DMAC_OFFSET_ENA             (IS2_AO_BASE_TYPE_ACL_MAC_1 + IS2_AL_BASE_TYPE_ACL_MAC_1)
#define IS2_AL_BASE_TYPE_DMAC_OFFSET_ENA             1
#define IS2_AO_BASE_TYPE_PTP_MASTER_SEL              (IS2_AO_BASE_TYPE_DMAC_OFFSET_ENA + IS2_AL_BASE_TYPE_DMAC_OFFSET_ENA)
#define IS2_AL_BASE_TYPE_PTP_MASTER_SEL              2
#define IS2_AO_BASE_TYPE_LOG_MSG_INTERVAL            (IS2_AO_BASE_TYPE_PTP_MASTER_SEL + IS2_AL_BASE_TYPE_PTP_MASTER_SEL)
#define IS2_AL_BASE_TYPE_LOG_MSG_INTERVAL            4
#define IS2_AO_BASE_TYPE_SIP_IDX                     (IS2_AO_BASE_TYPE_LOG_MSG_INTERVAL + IS2_AL_BASE_TYPE_LOG_MSG_INTERVAL)
#define IS2_AL_BASE_TYPE_SIP_IDX                     5
#define IS2_AO_BASE_TYPE_RLEG_STAT_IDX               (IS2_AO_BASE_TYPE_SIP_IDX + IS2_AL_BASE_TYPE_SIP_IDX)
#define IS2_AL_BASE_TYPE_RLEG_STAT_IDX               3
#define IS2_AO_BASE_TYPE_IGR_ACL_ENA                 (IS2_AO_BASE_TYPE_RLEG_STAT_IDX + IS2_AL_BASE_TYPE_RLEG_STAT_IDX)
#define IS2_AL_BASE_TYPE_IGR_ACL_ENA                 1
#define IS2_AO_BASE_TYPE_EGR_ACL_ENA                 (IS2_AO_BASE_TYPE_IGR_ACL_ENA + IS2_AL_BASE_TYPE_IGR_ACL_ENA)
#define IS2_AL_BASE_TYPE_EGR_ACL_ENA                 1

/* ================================================================= *
 *  VCAP LPM
 * ================================================================= */

/* LPM X6 DBL_IP6 key fields */
#define LPM_KO_DBL_IP6_AFFIX                         0
#define LPM_KL_DBL_IP6_AFFIX                         10
#define LPM_KO_DBL_IP6_IP6_SIP_0                     (LPM_KO_DBL_IP6_AFFIX + LPM_KL_DBL_IP6_AFFIX)
#define LPM_KL_DBL_IP6_IP6_SIP_0                     32
#define LPM_KO_DBL_IP6_IP6_SIP_1                     (LPM_KO_DBL_IP6_IP6_SIP_0 + LPM_KL_DBL_IP6_IP6_SIP_0)
#define LPM_KL_DBL_IP6_IP6_SIP_1                     32
#define LPM_KO_DBL_IP6_IP6_SIP_2                     (LPM_KO_DBL_IP6_IP6_SIP_1 + LPM_KL_DBL_IP6_IP6_SIP_1)
#define LPM_KL_DBL_IP6_IP6_SIP_2                     32
#define LPM_KO_DBL_IP6_IP6_SIP_3                     (LPM_KO_DBL_IP6_IP6_SIP_2 + LPM_KL_DBL_IP6_IP6_SIP_2)
#define LPM_KL_DBL_IP6_IP6_SIP_3                     32
#define LPM_KO_DBL_IP6_IP6_DIP_0                     (LPM_KO_DBL_IP6_IP6_SIP_3 + LPM_KL_DBL_IP6_IP6_SIP_3)
#define LPM_KL_DBL_IP6_IP6_DIP_0                     32
#define LPM_KO_DBL_IP6_IP6_DIP_1                     (LPM_KO_DBL_IP6_IP6_DIP_0 + LPM_KL_DBL_IP6_IP6_DIP_0)
#define LPM_KL_DBL_IP6_IP6_DIP_1                     32
#define LPM_KO_DBL_IP6_IP6_DIP_2                     (LPM_KO_DBL_IP6_IP6_DIP_1 + LPM_KL_DBL_IP6_IP6_DIP_1)
#define LPM_KL_DBL_IP6_IP6_DIP_2                     32
#define LPM_KO_DBL_IP6_IP6_DIP_3                     (LPM_KO_DBL_IP6_IP6_DIP_2 + LPM_KL_DBL_IP6_IP6_DIP_2)
#define LPM_KL_DBL_IP6_IP6_DIP_3                     32

/* LPM X3 SGL_IP6 key fields */
#define LPM_KO_SGL_IP6_DST_FLAG                      0
#define LPM_KL_SGL_IP6_DST_FLAG                      1
#define LPM_KO_SGL_IP6_AFFIX                         (LPM_KO_SGL_IP6_DST_FLAG + LPM_KL_SGL_IP6_DST_FLAG)
#define LPM_KL_SGL_IP6_AFFIX                         10
#define LPM_KO_SGL_IP6_IP6_XIP_0                     (LPM_KO_SGL_IP6_AFFIX + LPM_KL_SGL_IP6_AFFIX)
#define LPM_KL_SGL_IP6_IP6_XIP_0                     32
#define LPM_KO_SGL_IP6_IP6_XIP_1                     (LPM_KO_SGL_IP6_IP6_XIP_0 + LPM_KL_SGL_IP6_IP6_XIP_0)
#define LPM_KL_SGL_IP6_IP6_XIP_1                     32
#define LPM_KO_SGL_IP6_IP6_XIP_2                     (LPM_KO_SGL_IP6_IP6_XIP_1 + LPM_KL_SGL_IP6_IP6_XIP_1)
#define LPM_KL_SGL_IP6_IP6_XIP_2                     32
#define LPM_KO_SGL_IP6_IP6_XIP_3                     (LPM_KO_SGL_IP6_IP6_XIP_2 + LPM_KL_SGL_IP6_IP6_XIP_2)
#define LPM_KL_SGL_IP6_IP6_XIP_3                     32

/* LPM X2 key types */
#define LPM_X2_TYPE_DBL_IP4                          0
#define LPM_X2_TYPE_IP6PFX_ID                        1

/* LPM X2 common key fields */
#define LPM_KO_X2_TYPE                               0
#define LPM_KL_X2_TYPE                               1
/* LPM X2 DBL_IP4 key fields */
#define LPM_KO_DBL_IP4_AFFIX                         (LPM_KO_X2_TYPE + LPM_KL_X2_TYPE)
#define LPM_KL_DBL_IP4_AFFIX                         10
#define LPM_KO_DBL_IP4_IP4_SIP                       (LPM_KO_DBL_IP4_AFFIX + LPM_KL_DBL_IP4_AFFIX)
#define LPM_KL_DBL_IP4_IP4_SIP                       32
#define LPM_KO_DBL_IP4_IP4_DIP                       (LPM_KO_DBL_IP4_IP4_SIP + LPM_KL_DBL_IP4_IP4_SIP)
#define LPM_KL_DBL_IP4_IP4_DIP                       32

/* LPM X2 IP6PFX_ID key fields */
#define LPM_KO_IP6PFX_ID_DST_FLAG                    (LPM_KO_X2_TYPE + LPM_KL_X2_TYPE)
#define LPM_KL_IP6PFX_ID_DST_FLAG                    1
#define LPM_KO_IP6PFX_ID_AFFIX                       (LPM_KO_IP6PFX_ID_DST_FLAG + LPM_KL_IP6PFX_ID_DST_FLAG)
#define LPM_KL_IP6PFX_ID_AFFIX                       10
#define LPM_KO_IP6PFX_ID_IP6PFX_ID                   (LPM_KO_IP6PFX_ID_AFFIX + LPM_KL_IP6PFX_ID_AFFIX)
#define LPM_KL_IP6PFX_ID_IP6PFX_ID                   (FA_TGT ? 9 : 2)
#define LPM_KO_IP6PFX_ID_IP6_XIP_0_2                 (LPM_KO_IP6PFX_ID_IP6PFX_ID + LPM_KL_IP6PFX_ID_IP6PFX_ID)
#define LPM_KL_IP6PFX_ID_IP6_XIP_0_2                 32
#define LPM_KO_IP6PFX_ID_IP6_XIP_1_3                 (LPM_KO_IP6PFX_ID_IP6_XIP_0_2 + LPM_KL_IP6PFX_ID_IP6_XIP_0_2)
#define LPM_KL_IP6PFX_ID_IP6_XIP_1_3                 32

/* LPM X1 SGL_IP4 key fields */
#define LPM_KO_SGL_IP4_DST_FLAG                      0
#define LPM_KL_SGL_IP4_DST_FLAG                      1
#define LPM_KO_SGL_IP4_AFFIX                         (LPM_KO_SGL_IP4_DST_FLAG + LPM_KL_SGL_IP4_DST_FLAG)
#define LPM_KL_SGL_IP4_AFFIX                         10
#define LPM_KO_SGL_IP4_IP4_XIP                       (LPM_KO_SGL_IP4_AFFIX + LPM_KL_SGL_IP4_AFFIX)
#define LPM_KL_SGL_IP4_IP4_XIP                       32

/* LPM X1 action types */
#define LPM_X1_TYPE_ARP_PTR                          0
#define LPM_X1_TYPE_L3MC_PTR                         1
#define LPM_X1_TYPE_ARP_ENTRY                        2

/* LPM X1 common action fields */
#define LPM_AO_X1_TYPE                               0
#define LPM_AL_X1_TYPE                               2
/* LPM X1 ARP_PTR action fields */
#define LPM_AO_ARP_PTR_ARP_PTR                       (LPM_AO_X1_TYPE + LPM_AL_X1_TYPE)
#define LPM_AL_ARP_PTR_ARP_PTR                       (FA_TGT ? 11 : 10)
#define LPM_AO_ARP_PTR_ARP_PTR_REMAP_ENA             (LPM_AO_ARP_PTR_ARP_PTR + LPM_AL_ARP_PTR_ARP_PTR)
#define LPM_AL_ARP_PTR_ARP_PTR_REMAP_ENA             1
#define LPM_AO_ARP_PTR_ECMP_CNT                      (LPM_AO_ARP_PTR_ARP_PTR_REMAP_ENA + LPM_AL_ARP_PTR_ARP_PTR_REMAP_ENA)
#define LPM_AL_ARP_PTR_ECMP_CNT                      4
#define LPM_AO_ARP_PTR_RGID                          (LPM_AO_ARP_PTR_ECMP_CNT + LPM_AL_ARP_PTR_ECMP_CNT)
#define LPM_AL_ARP_PTR_RGID                          3

/* LPM X1 L3MC_PTR action fields */
#define LPM_AO_L3MC_PTR_L3MC_PTR                     (LPM_AO_X1_TYPE + LPM_AL_X1_TYPE)
#define LPM_AL_L3MC_PTR_L3MC_PTR                     (FA_TGT ? 11 : 10)

/* LPM X1 ARP_ENTRY action fields */
#define LPM_AO_ARP_ENTRY_MAC_MSB                     (LPM_AO_X1_TYPE + LPM_AL_X1_TYPE)
#define LPM_AL_ARP_ENTRY_MAC_MSB                     16
#define LPM_AO_ARP_ENTRY_MAC_LSB                     (LPM_AO_ARP_ENTRY_MAC_MSB + LPM_AL_ARP_ENTRY_MAC_MSB)
#define LPM_AL_ARP_ENTRY_MAC_LSB                     32
#define LPM_AO_ARP_ENTRY_ARP_VMID                    (LPM_AO_ARP_ENTRY_MAC_LSB + LPM_AL_ARP_ENTRY_MAC_LSB)
#define LPM_AL_ARP_ENTRY_ARP_VMID                    (FA_TGT ? 9 : 7)
#define LPM_AO_ARP_ENTRY_ZERO_DMAC_CPU_QU            (LPM_AO_ARP_ENTRY_ARP_VMID + LPM_AL_ARP_ENTRY_ARP_VMID)
#define LPM_AL_ARP_ENTRY_ZERO_DMAC_CPU_QU            3
#define LPM_AO_ARP_ENTRY_SIP_RPF_ENA                 (LPM_AO_ARP_ENTRY_ZERO_DMAC_CPU_QU + LPM_AL_ARP_ENTRY_ZERO_DMAC_CPU_QU)
#define LPM_AL_ARP_ENTRY_SIP_RPF_ENA                 1
#define LPM_AO_ARP_ENTRY_SECUR_MATCH_VMID_ENA        (LPM_AO_ARP_ENTRY_SIP_RPF_ENA + LPM_AL_ARP_ENTRY_SIP_RPF_ENA)
#define LPM_AL_ARP_ENTRY_SECUR_MATCH_VMID_ENA        1
#define LPM_AO_ARP_ENTRY_SECUR_MATCH_MAC_ENA         (LPM_AO_ARP_ENTRY_SECUR_MATCH_VMID_ENA + LPM_AL_ARP_ENTRY_SECUR_MATCH_VMID_ENA)
#define LPM_AL_ARP_ENTRY_SECUR_MATCH_MAC_ENA         1
#define LPM_AO_ARP_ENTRY_ARP_ENA                     (LPM_AO_ARP_ENTRY_SECUR_MATCH_MAC_ENA + LPM_AL_ARP_ENTRY_SECUR_MATCH_MAC_ENA)
#define LPM_AL_ARP_ENTRY_ARP_ENA                     1
#define LPM_AO_ARP_ENTRY_ENCAP_ID                    (LPM_AO_ARP_ENTRY_ARP_ENA + LPM_AL_ARP_ENTRY_ARP_ENA)
#define LPM_AL_ARP_ENTRY_ENCAP_ID                    (FA_TGT ? 10 : 8)
#define LPM_AO_ARP_ENTRY_RSDX                        (LPM_AO_ARP_ENTRY_ENCAP_ID + LPM_AL_ARP_ENTRY_ENCAP_ID)
#define LPM_AL_ARP_ENTRY_RSDX                        (FA_TGT ? 12 : 10)

/* ================================================================= *
 *  VCAP ES0
 * ================================================================= */

/* ES0 X1 key types */
#define ES0_X1_TYPE_ISDX                             0
#define ES0_X1_TYPE_VID                              1

/* ES0 X1 common key fields */
#define ES0_KO_X1_TYPE                               0
#define ES0_KL_X1_TYPE                               1
#define ES0_KO_X1_EGR_PORT                           (ES0_KO_X1_TYPE + ES0_KL_X1_TYPE)
#define ES0_KL_X1_EGR_PORT                           (FA_TGT ? 7 : 6)
#define ES0_KO_X1_XVID                               (ES0_KO_X1_EGR_PORT + ES0_KL_X1_EGR_PORT)
#define ES0_KL_X1_XVID                               13
#define ES0_KO_X1_COSID                              (ES0_KO_X1_XVID + ES0_KL_X1_XVID)
#define ES0_KL_X1_COSID                              3
#define ES0_KO_X1_TPID                               (ES0_KO_X1_COSID + ES0_KL_X1_COSID)
#define ES0_KL_X1_TPID                               3
#define ES0_KO_X1_COLOR                              (ES0_KO_X1_TPID + ES0_KL_X1_TPID)
#define ES0_KL_X1_COLOR                              1
#define ES0_KO_X1_SERVICE_FRM                        (ES0_KO_X1_COLOR + ES0_KL_X1_COLOR)
#define ES0_KL_X1_SERVICE_FRM                        1
#define ES0_KO_X1_PROT_ACTIVE                        (ES0_KO_X1_SERVICE_FRM + ES0_KL_X1_SERVICE_FRM)
#define ES0_KL_X1_PROT_ACTIVE                        1
#define ES0_KO_X1_ENCAP_ID_ENA                       (ES0_KO_X1_PROT_ACTIVE + ES0_KL_X1_PROT_ACTIVE)
#define ES0_KL_X1_ENCAP_ID_ENA                       1
#define ES0_KO_X1_OAM_Y1731                          (ES0_KO_X1_ENCAP_ID_ENA + ES0_KL_X1_ENCAP_ID_ENA)
#define ES0_KL_X1_OAM_Y1731                          1
#define ES0_KO_X1_OAM_MEL_FLAGS                      (ES0_KO_X1_OAM_Y1731 + ES0_KL_X1_OAM_Y1731)
#define ES0_KL_X1_OAM_MEL_FLAGS                      7

/* ES0 X1 ISDX key fields */
#define ES0_KO_ISDX_ISDX                             (ES0_KO_X1_OAM_MEL_FLAGS + ES0_KL_X1_OAM_MEL_FLAGS)
#define ES0_KL_ISDX_ISDX                             (FA_TGT ? 12 : 10)

/* ES0 X1 VID key fields */
#define ES0_KO_VID_GVID                              (ES0_KO_X1_OAM_MEL_FLAGS + ES0_KL_X1_OAM_MEL_FLAGS)
#define ES0_KL_VID_GVID                              12

/* ES0 X1 ES0 action fields */
#define ES0_AO_ES0_PUSH_OUTER_TAG                    0
#define ES0_AL_ES0_PUSH_OUTER_TAG                    2
#define ES0_AO_ES0_PUSH_INNER_TAG                    (ES0_AO_ES0_PUSH_OUTER_TAG + ES0_AL_ES0_PUSH_OUTER_TAG)
#define ES0_AL_ES0_PUSH_INNER_TAG                    1
#define ES0_AO_ES0_TAG_A_TPID_SEL                    (ES0_AO_ES0_PUSH_INNER_TAG + ES0_AL_ES0_PUSH_INNER_TAG)
#define ES0_AL_ES0_TAG_A_TPID_SEL                    3
#define ES0_AO_ES0_TAG_A_VID_SEL                     (ES0_AO_ES0_TAG_A_TPID_SEL + ES0_AL_ES0_TAG_A_TPID_SEL)
#define ES0_AL_ES0_TAG_A_VID_SEL                     2
#define ES0_AO_ES0_TAG_A_PCP_SEL                     (ES0_AO_ES0_TAG_A_VID_SEL + ES0_AL_ES0_TAG_A_VID_SEL)
#define ES0_AL_ES0_TAG_A_PCP_SEL                     3
#define ES0_AO_ES0_TAG_A_DEI_SEL                     (ES0_AO_ES0_TAG_A_PCP_SEL + ES0_AL_ES0_TAG_A_PCP_SEL)
#define ES0_AL_ES0_TAG_A_DEI_SEL                     3
#define ES0_AO_ES0_TAG_B_TPID_SEL                    (ES0_AO_ES0_TAG_A_DEI_SEL + ES0_AL_ES0_TAG_A_DEI_SEL)
#define ES0_AL_ES0_TAG_B_TPID_SEL                    3
#define ES0_AO_ES0_TAG_B_VID_SEL                     (ES0_AO_ES0_TAG_B_TPID_SEL + ES0_AL_ES0_TAG_B_TPID_SEL)
#define ES0_AL_ES0_TAG_B_VID_SEL                     2
#define ES0_AO_ES0_TAG_B_PCP_SEL                     (ES0_AO_ES0_TAG_B_VID_SEL + ES0_AL_ES0_TAG_B_VID_SEL)
#define ES0_AL_ES0_TAG_B_PCP_SEL                     3
#define ES0_AO_ES0_TAG_B_DEI_SEL                     (ES0_AO_ES0_TAG_B_PCP_SEL + ES0_AL_ES0_TAG_B_PCP_SEL)
#define ES0_AL_ES0_TAG_B_DEI_SEL                     3
#define ES0_AO_ES0_TAG_C_TPID_SEL                    (ES0_AO_ES0_TAG_B_DEI_SEL + ES0_AL_ES0_TAG_B_DEI_SEL)
#define ES0_AL_ES0_TAG_C_TPID_SEL                    3
#define ES0_AO_ES0_TAG_C_PCP_SEL                     (ES0_AO_ES0_TAG_C_TPID_SEL + ES0_AL_ES0_TAG_C_TPID_SEL)
#define ES0_AL_ES0_TAG_C_PCP_SEL                     3
#define ES0_AO_ES0_TAG_C_DEI_SEL                     (ES0_AO_ES0_TAG_C_PCP_SEL + ES0_AL_ES0_TAG_C_PCP_SEL)
#define ES0_AL_ES0_TAG_C_DEI_SEL                     3
#define ES0_AO_ES0_VID_A_VAL                         (ES0_AO_ES0_TAG_C_DEI_SEL + ES0_AL_ES0_TAG_C_DEI_SEL)
#define ES0_AL_ES0_VID_A_VAL                         12
#define ES0_AO_ES0_PCP_A_VAL                         (ES0_AO_ES0_VID_A_VAL + ES0_AL_ES0_VID_A_VAL)
#define ES0_AL_ES0_PCP_A_VAL                         3
#define ES0_AO_ES0_DEI_A_VAL                         (ES0_AO_ES0_PCP_A_VAL + ES0_AL_ES0_PCP_A_VAL)
#define ES0_AL_ES0_DEI_A_VAL                         1
#define ES0_AO_ES0_VID_B_VAL                         (ES0_AO_ES0_DEI_A_VAL + ES0_AL_ES0_DEI_A_VAL)
#define ES0_AL_ES0_VID_B_VAL                         12
#define ES0_AO_ES0_PCP_B_VAL                         (ES0_AO_ES0_VID_B_VAL + ES0_AL_ES0_VID_B_VAL)
#define ES0_AL_ES0_PCP_B_VAL                         3
#define ES0_AO_ES0_DEI_B_VAL                         (ES0_AO_ES0_PCP_B_VAL + ES0_AL_ES0_PCP_B_VAL)
#define ES0_AL_ES0_DEI_B_VAL                         1
#define ES0_AO_ES0_VID_C_VAL                         (ES0_AO_ES0_DEI_B_VAL + ES0_AL_ES0_DEI_B_VAL)
#define ES0_AL_ES0_VID_C_VAL                         12
#define ES0_AO_ES0_PCP_C_VAL                         (ES0_AO_ES0_VID_C_VAL + ES0_AL_ES0_VID_C_VAL)
#define ES0_AL_ES0_PCP_C_VAL                         3
#define ES0_AO_ES0_DEI_C_VAL                         (ES0_AO_ES0_PCP_C_VAL + ES0_AL_ES0_PCP_C_VAL)
#define ES0_AL_ES0_DEI_C_VAL                         1
#define ES0_AO_ES0_POP_VAL                           (ES0_AO_ES0_DEI_C_VAL + ES0_AL_ES0_DEI_C_VAL)
#define ES0_AL_ES0_POP_VAL                           2
#define ES0_AO_ES0_UNTAG_VID_ENA                     (ES0_AO_ES0_POP_VAL + ES0_AL_ES0_POP_VAL)
#define ES0_AL_ES0_UNTAG_VID_ENA                     1
#define ES0_AO_ES0_PUSH_CUSTOMER_TAG                 (ES0_AO_ES0_UNTAG_VID_ENA + ES0_AL_ES0_UNTAG_VID_ENA)
#define ES0_AL_ES0_PUSH_CUSTOMER_TAG                 2
#define ES0_AO_ES0_TAG_C_VID_SEL                     (ES0_AO_ES0_PUSH_CUSTOMER_TAG + ES0_AL_ES0_PUSH_CUSTOMER_TAG)
#define ES0_AL_ES0_TAG_C_VID_SEL                     2
#define ES0_AO_ES0_PUSH_ETAG                         (ES0_AO_ES0_TAG_C_VID_SEL + ES0_AL_ES0_TAG_C_VID_SEL)
#define ES0_AL_ES0_PUSH_ETAG                         1
#define ES0_AO_ES0_ECID_BASE_SEL                     (ES0_AO_ES0_PUSH_ETAG + ES0_AL_ES0_PUSH_ETAG)
#define ES0_AL_ES0_ECID_BASE_SEL                     1
#define ES0_AO_ES0_ECID_EXT_SEL                      (ES0_AO_ES0_ECID_BASE_SEL + ES0_AL_ES0_ECID_BASE_SEL)
#define ES0_AL_ES0_ECID_EXT_SEL                      1
#define ES0_AO_ES0_GRP_SEL                           (ES0_AO_ES0_ECID_EXT_SEL + ES0_AL_ES0_ECID_EXT_SEL)
#define ES0_AL_ES0_GRP_SEL                           1
#define ES0_AO_ES0_IGR_ECID_SEL                      (ES0_AO_ES0_GRP_SEL + ES0_AL_ES0_GRP_SEL)
#define ES0_AL_ES0_IGR_ECID_SEL                      2
#define ES0_AO_ES0_ECID_BASE_VAL                     (ES0_AO_ES0_IGR_ECID_SEL + ES0_AL_ES0_IGR_ECID_SEL)
#define ES0_AL_ES0_ECID_BASE_VAL                     12
#define ES0_AO_ES0_ECID_EXT_VAL                      (ES0_AO_ES0_ECID_BASE_VAL + ES0_AL_ES0_ECID_BASE_VAL)
#define ES0_AL_ES0_ECID_EXT_VAL                      8
#define ES0_AO_ES0_GRP_VAL                           (ES0_AO_ES0_ECID_EXT_VAL + ES0_AL_ES0_ECID_EXT_VAL)
#define ES0_AL_ES0_GRP_VAL                           2
#define ES0_AO_ES0_EPCP_EDEI_SEL                     (ES0_AO_ES0_GRP_VAL + ES0_AL_ES0_GRP_VAL)
#define ES0_AL_ES0_EPCP_EDEI_SEL                     3
#define ES0_AO_ES0_EPCP_VAL                          (ES0_AO_ES0_EPCP_EDEI_SEL + ES0_AL_ES0_EPCP_EDEI_SEL)
#define ES0_AL_ES0_EPCP_VAL                          3
#define ES0_AO_ES0_EDEI_VAL                          (ES0_AO_ES0_EPCP_VAL + ES0_AL_ES0_EPCP_VAL)
#define ES0_AL_ES0_EDEI_VAL                          1
#define ES0_AO_ES0_RTAG_POP_ENA                      (ES0_AO_ES0_EDEI_VAL + ES0_AL_ES0_EDEI_VAL)
#define ES0_AL_ES0_RTAG_POP_ENA                      1
#define ES0_AO_ES0_RTAG_PUSH_SEL                     (ES0_AO_ES0_RTAG_POP_ENA + ES0_AL_ES0_RTAG_POP_ENA)
#define ES0_AL_ES0_RTAG_PUSH_SEL                     2
#define ES0_AO_ES0_DSCP_SEL                          (ES0_AO_ES0_RTAG_PUSH_SEL + ES0_AL_ES0_RTAG_PUSH_SEL)
#define ES0_AL_ES0_DSCP_SEL                          3
#define ES0_AO_ES0_DSCP_VAL                          (ES0_AO_ES0_DSCP_SEL + ES0_AL_ES0_DSCP_SEL)
#define ES0_AL_ES0_DSCP_VAL                          6
#define ES0_AO_ES0_PROTECTION_SEL                    (ES0_AO_ES0_DSCP_VAL + ES0_AL_ES0_DSCP_VAL)
#define ES0_AL_ES0_PROTECTION_SEL                    2
#define ES0_AO_ES0_LBL1_SEL                          (ES0_AO_ES0_PROTECTION_SEL + ES0_AL_ES0_PROTECTION_SEL)
#define ES0_AL_ES0_LBL1_SEL                          3
#define ES0_AO_ES0_TC1_SEL                           (ES0_AO_ES0_LBL1_SEL + ES0_AL_ES0_LBL1_SEL)
#define ES0_AL_ES0_TC1_SEL                           3
#define ES0_AO_ES0_SBIT1_SEL                         (ES0_AO_ES0_TC1_SEL + ES0_AL_ES0_TC1_SEL)
#define ES0_AL_ES0_SBIT1_SEL                         2
#define ES0_AO_ES0_TTL1_SEL                          (ES0_AO_ES0_SBIT1_SEL + ES0_AL_ES0_SBIT1_SEL)
#define ES0_AL_ES0_TTL1_SEL                          2
#define ES0_AO_ES0_LBL1_VAL                          (ES0_AO_ES0_TTL1_SEL + ES0_AL_ES0_TTL1_SEL)
#define ES0_AL_ES0_LBL1_VAL                          20
#define ES0_AO_ES0_TC1_VAL                           (ES0_AO_ES0_LBL1_VAL + ES0_AL_ES0_LBL1_VAL)
#define ES0_AL_ES0_TC1_VAL                           3
#define ES0_AO_ES0_SBIT1_VAL                         (ES0_AO_ES0_TC1_VAL + ES0_AL_ES0_TC1_VAL)
#define ES0_AL_ES0_SBIT1_VAL                         1
#define ES0_AO_ES0_TTL1_VAL                          (ES0_AO_ES0_SBIT1_VAL + ES0_AL_ES0_SBIT1_VAL)
#define ES0_AL_ES0_TTL1_VAL                          8
#define ES0_AO_ES0_LBL2_SEL                          (ES0_AO_ES0_TTL1_VAL + ES0_AL_ES0_TTL1_VAL)
#define ES0_AL_ES0_LBL2_SEL                          3
#define ES0_AO_ES0_TC2_SEL                           (ES0_AO_ES0_LBL2_SEL + ES0_AL_ES0_LBL2_SEL)
#define ES0_AL_ES0_TC2_SEL                           3
#define ES0_AO_ES0_SBIT2_SEL                         (ES0_AO_ES0_TC2_SEL + ES0_AL_ES0_TC2_SEL)
#define ES0_AL_ES0_SBIT2_SEL                         2
#define ES0_AO_ES0_TTL2_SEL                          (ES0_AO_ES0_SBIT2_SEL + ES0_AL_ES0_SBIT2_SEL)
#define ES0_AL_ES0_TTL2_SEL                          2
#define ES0_AO_ES0_LBL2_VAL                          (ES0_AO_ES0_TTL2_SEL + ES0_AL_ES0_TTL2_SEL)
#define ES0_AL_ES0_LBL2_VAL                          20
#define ES0_AO_ES0_TC2_VAL                           (ES0_AO_ES0_LBL2_VAL + ES0_AL_ES0_LBL2_VAL)
#define ES0_AL_ES0_TC2_VAL                           3
#define ES0_AO_ES0_SBIT2_VAL                         (ES0_AO_ES0_TC2_VAL + ES0_AL_ES0_TC2_VAL)
#define ES0_AL_ES0_SBIT2_VAL                         1
#define ES0_AO_ES0_TTL2_VAL                          (ES0_AO_ES0_SBIT2_VAL + ES0_AL_ES0_SBIT2_VAL)
#define ES0_AL_ES0_TTL2_VAL                          8
#define ES0_AO_ES0_LBL3_SEL                          (ES0_AO_ES0_TTL2_VAL + ES0_AL_ES0_TTL2_VAL)
#define ES0_AL_ES0_LBL3_SEL                          3
#define ES0_AO_ES0_TC3_SEL                           (ES0_AO_ES0_LBL3_SEL + ES0_AL_ES0_LBL3_SEL)
#define ES0_AL_ES0_TC3_SEL                           3
#define ES0_AO_ES0_SBIT3_SEL                         (ES0_AO_ES0_TC3_SEL + ES0_AL_ES0_TC3_SEL)
#define ES0_AL_ES0_SBIT3_SEL                         2
#define ES0_AO_ES0_TTL3_SEL                          (ES0_AO_ES0_SBIT3_SEL + ES0_AL_ES0_SBIT3_SEL)
#define ES0_AL_ES0_TTL3_SEL                          2
#define ES0_AO_ES0_LBL3_VAL                          (ES0_AO_ES0_TTL3_SEL + ES0_AL_ES0_TTL3_SEL)
#define ES0_AL_ES0_LBL3_VAL                          20
#define ES0_AO_ES0_TC3_VAL                           (ES0_AO_ES0_LBL3_VAL + ES0_AL_ES0_LBL3_VAL)
#define ES0_AL_ES0_TC3_VAL                           3
#define ES0_AO_ES0_SBIT3_VAL                         (ES0_AO_ES0_TC3_VAL + ES0_AL_ES0_TC3_VAL)
#define ES0_AL_ES0_SBIT3_VAL                         1
#define ES0_AO_ES0_TTL3_VAL                          (ES0_AO_ES0_SBIT3_VAL + ES0_AL_ES0_SBIT3_VAL)
#define ES0_AL_ES0_TTL3_VAL                          8
#define ES0_AO_ES0_CW_CFG                            (ES0_AO_ES0_TTL3_VAL + ES0_AL_ES0_TTL3_VAL)
#define ES0_AL_ES0_CW_CFG                            2
#define ES0_AO_ES0_CW_VAL                            (ES0_AO_ES0_CW_CFG + ES0_AL_ES0_CW_CFG)
#define ES0_AL_ES0_CW_VAL                            32
#define ES0_AO_ES0_ENCAP_ID                          (ES0_AO_ES0_CW_VAL + ES0_AL_ES0_CW_VAL)
#define ES0_AL_ES0_ENCAP_ID                          (FA_TGT ? 10 : 8)
#define ES0_AO_ES0_ENCAP_ID_P                        (ES0_AO_ES0_ENCAP_ID + ES0_AL_ES0_ENCAP_ID)
#define ES0_AL_ES0_ENCAP_ID_P                        (FA_TGT ? 10 : 8)
#define ES0_AO_ES0_POP_CNT                           (ES0_AO_ES0_ENCAP_ID_P + ES0_AL_ES0_ENCAP_ID_P)
#define ES0_AL_ES0_POP_CNT                           5
#define ES0_AO_ES0_ESDX_BASE                         (ES0_AO_ES0_POP_CNT + ES0_AL_ES0_POP_CNT)
#define ES0_AL_ES0_ESDX_BASE                         (FA_TGT ? 13 : 10)
#define ES0_AO_ES0_ESDX_BASE_P                       (ES0_AO_ES0_ESDX_BASE + ES0_AL_ES0_ESDX_BASE)
#define ES0_AL_ES0_ESDX_BASE_P                       (FA_TGT ? 13 : 10)
#define ES0_AO_ES0_ESDX_COSID_OFFSET                 (ES0_AO_ES0_ESDX_BASE_P + ES0_AL_ES0_ESDX_BASE_P)
#define ES0_AL_ES0_ESDX_COSID_OFFSET                 24
#define ES0_AO_ES0_MAP_0_IDX                         (ES0_AO_ES0_ESDX_COSID_OFFSET + ES0_AL_ES0_ESDX_COSID_OFFSET)
#define ES0_AL_ES0_MAP_0_IDX                         (FA_TGT ? 9 : 10)
#define ES0_AO_ES0_MAP_1_IDX                         (ES0_AO_ES0_MAP_0_IDX + ES0_AL_ES0_MAP_0_IDX)
#define ES0_AL_ES0_MAP_1_IDX                         (FA_TGT ? 9 : 10)
#define ES0_AO_ES0_MAP_2_IDX                         (ES0_AO_ES0_MAP_1_IDX + ES0_AL_ES0_MAP_1_IDX)
#define ES0_AL_ES0_MAP_2_IDX                         (FA_TGT ? 9 : 10)
#define ES0_AO_ES0_MAP_3_IDX                         (ES0_AO_ES0_MAP_2_IDX + ES0_AL_ES0_MAP_2_IDX)
#define ES0_AL_ES0_MAP_3_IDX                         (FA_TGT ? 9 : 10)
#define ES0_AO_ES0_MAP_0_KEY                         (ES0_AO_ES0_MAP_3_IDX + ES0_AL_ES0_MAP_3_IDX)
#define ES0_AL_ES0_MAP_0_KEY                         4
#define ES0_AO_ES0_MAP_1_KEY                         (ES0_AO_ES0_MAP_0_KEY + ES0_AL_ES0_MAP_0_KEY)
#define ES0_AL_ES0_MAP_1_KEY                         4
#define ES0_AO_ES0_MAP_2_KEY                         (ES0_AO_ES0_MAP_1_KEY + ES0_AL_ES0_MAP_1_KEY)
#define ES0_AL_ES0_MAP_2_KEY                         4
#define ES0_AO_ES0_MAP_3_KEY                         (ES0_AO_ES0_MAP_2_KEY + ES0_AL_ES0_MAP_2_KEY)
#define ES0_AL_ES0_MAP_3_KEY                         4
#define ES0_AO_ES0_OAM_MEP_IDX_VLD                   (ES0_AO_ES0_MAP_3_KEY + ES0_AL_ES0_MAP_3_KEY)
#define ES0_AL_ES0_OAM_MEP_IDX_VLD                   1
#define ES0_AO_ES0_OAM_MEP_IDX                       (ES0_AO_ES0_OAM_MEP_IDX_VLD + ES0_AL_ES0_OAM_MEP_IDX_VLD)
#define ES0_AL_ES0_OAM_MEP_IDX                       (FA_TGT ? 10 : 5)
#define ES0_AO_ES0_OAM_MEP_IDX_P                     (ES0_AO_ES0_OAM_MEP_IDX + ES0_AL_ES0_OAM_MEP_IDX)
#define ES0_AL_ES0_OAM_MEP_IDX_P                     (FA_TGT ? 10 : 5)
#define ES0_AO_ES0_OAM_LM_COSID_COLOR_SEL            (ES0_AO_ES0_OAM_MEP_IDX_P + ES0_AL_ES0_OAM_MEP_IDX_P)
#define ES0_AL_ES0_OAM_LM_COSID_COLOR_SEL            2
#define ES0_AO_ES0_INDEPENDENT_MEL_ENA               (ES0_AO_ES0_OAM_LM_COSID_COLOR_SEL + ES0_AL_ES0_OAM_LM_COSID_COLOR_SEL)
#define ES0_AL_ES0_INDEPENDENT_MEL_ENA               1
#define ES0_AO_ES0_MIP_IDX                           (ES0_AO_ES0_INDEPENDENT_MEL_ENA + ES0_AL_ES0_INDEPENDENT_MEL_ENA)
#define ES0_AL_ES0_MIP_IDX                           (FA_TGT ? 10 : 5)
#define ES0_AO_ES0_FWD_SEL                           (ES0_AO_ES0_MIP_IDX + ES0_AL_ES0_MIP_IDX)
#define ES0_AL_ES0_FWD_SEL                           2
#define ES0_AO_ES0_CPU_QU                            (ES0_AO_ES0_FWD_SEL + ES0_AL_ES0_FWD_SEL)
#define ES0_AL_ES0_CPU_QU                            3
#define ES0_AO_ES0_PIPELINE_PT                       (ES0_AO_ES0_CPU_QU + ES0_AL_ES0_CPU_QU)
#define ES0_AL_ES0_PIPELINE_PT                       2
#define ES0_AO_ES0_PIPELINE_ACT                      (ES0_AO_ES0_PIPELINE_PT + ES0_AL_ES0_PIPELINE_PT)
#define ES0_AL_ES0_PIPELINE_ACT                      1
#define ES0_AO_ES0_MAC_IDX                           (ES0_AO_ES0_PIPELINE_ACT + ES0_AL_ES0_PIPELINE_ACT)
#define ES0_AL_ES0_MAC_IDX                           7
#define ES0_AO_ES0_REPLACE_DMAC_ENA                  (ES0_AO_ES0_MAC_IDX + ES0_AL_ES0_MAC_IDX)
#define ES0_AL_ES0_REPLACE_DMAC_ENA                  1
#define ES0_AO_ES0_SWAP_MACS_ENA                     (ES0_AO_ES0_REPLACE_DMAC_ENA + ES0_AL_ES0_REPLACE_DMAC_ENA)
#define ES0_AL_ES0_SWAP_MACS_ENA                     1
#define ES0_AO_ES0_LOOP_ENA                          (ES0_AO_ES0_SWAP_MACS_ENA + ES0_AL_ES0_SWAP_MACS_ENA)
#define ES0_AL_ES0_LOOP_ENA                          1
#define ES0_AO_ES0_QS_INFO                           (ES0_AO_ES0_LOOP_ENA + ES0_AL_ES0_LOOP_ENA)
#define ES0_AL_ES0_QS_INFO                           12

/* ================================================================= *
 *  VCAP ES2
 * ================================================================= */

/* ES2 X12 IP_7TUPLE key fields */
#define ES2_KO_IP_7TUPLE_FIRST                       0
#define ES2_KL_IP_7TUPLE_FIRST                       1
#define ES2_KO_IP_7TUPLE_ACL_GRP_ID                  (ES2_KO_IP_7TUPLE_FIRST + ES2_KL_IP_7TUPLE_FIRST)
#define ES2_KL_IP_7TUPLE_ACL_GRP_ID                  8
#define ES2_KO_IP_7TUPLE_PROT_ACTIVE                 (ES2_KO_IP_7TUPLE_ACL_GRP_ID + ES2_KL_IP_7TUPLE_ACL_GRP_ID)
#define ES2_KL_IP_7TUPLE_PROT_ACTIVE                 1
#define ES2_KO_IP_7TUPLE_L2_MC                       (ES2_KO_IP_7TUPLE_PROT_ACTIVE + ES2_KL_IP_7TUPLE_PROT_ACTIVE)
#define ES2_KL_IP_7TUPLE_L2_MC                       1
#define ES2_KO_IP_7TUPLE_L2_BC                       (ES2_KO_IP_7TUPLE_L2_MC + ES2_KL_IP_7TUPLE_L2_MC)
#define ES2_KL_IP_7TUPLE_L2_BC                       1
#define ES2_KO_IP_7TUPLE_SERVICE_FRM                 (ES2_KO_IP_7TUPLE_L2_BC + ES2_KL_IP_7TUPLE_L2_BC)
#define ES2_KL_IP_7TUPLE_SERVICE_FRM                 1
#define ES2_KO_IP_7TUPLE_ISDX                        (ES2_KO_IP_7TUPLE_SERVICE_FRM + ES2_KL_IP_7TUPLE_SERVICE_FRM)
#define ES2_KL_IP_7TUPLE_ISDX                        (FA_TGT ? 12 : 10)
#define ES2_KO_IP_7TUPLE_VLAN_TAGGED                 (ES2_KO_IP_7TUPLE_ISDX + ES2_KL_IP_7TUPLE_ISDX)
#define ES2_KL_IP_7TUPLE_VLAN_TAGGED                 1
#define ES2_KO_IP_7TUPLE_XVID                        (FA_TGT ? (ES2_KO_IP_7TUPLE_VLAN_TAGGED + ES2_KL_IP_7TUPLE_VLAN_TAGGED) : (ES2_KO_IP_7TUPLE_RED_TAGGED + ES2_KL_IP_7TUPLE_RED_TAGGED))
#define ES2_KL_IP_7TUPLE_XVID                        13
#define ES2_KO_IP_7TUPLE_EGR_PORT_MASK_RNG           (ES2_KO_IP_7TUPLE_XVID + ES2_KL_IP_7TUPLE_XVID)
#define ES2_KL_IP_7TUPLE_EGR_PORT_MASK_RNG           3
#define ES2_KO_IP_7TUPLE_EGR_PORT_MASK               (ES2_KO_IP_7TUPLE_EGR_PORT_MASK_RNG + ES2_KL_IP_7TUPLE_EGR_PORT_MASK_RNG)
#define ES2_KL_IP_7TUPLE_EGR_PORT_MASK               32
#define ES2_KO_IP_7TUPLE_IGR_PORT_SEL                (ES2_KO_IP_7TUPLE_EGR_PORT_MASK + ES2_KL_IP_7TUPLE_EGR_PORT_MASK)
#define ES2_KL_IP_7TUPLE_IGR_PORT_SEL                1
#define ES2_KO_IP_7TUPLE_IGR_PORT                    (ES2_KO_IP_7TUPLE_IGR_PORT_SEL + ES2_KL_IP_7TUPLE_IGR_PORT_SEL)
#define ES2_KL_IP_7TUPLE_IGR_PORT                    (FA_TGT ? 9 : 7)
#define ES2_KO_IP_7TUPLE_PCP                         (ES2_KO_IP_7TUPLE_IGR_PORT + ES2_KL_IP_7TUPLE_IGR_PORT)
#define ES2_KL_IP_7TUPLE_PCP                         3
#define ES2_KO_IP_7TUPLE_DEI                         (ES2_KO_IP_7TUPLE_PCP + ES2_KL_IP_7TUPLE_PCP)
#define ES2_KL_IP_7TUPLE_DEI                         1
#define ES2_KO_IP_7TUPLE_COSID                       (ES2_KO_IP_7TUPLE_DEI + ES2_KL_IP_7TUPLE_DEI)
#define ES2_KL_IP_7TUPLE_COSID                       3
#define ES2_KO_IP_7TUPLE_COLOR                       (ES2_KO_IP_7TUPLE_COSID + ES2_KL_IP_7TUPLE_COSID)
#define ES2_KL_IP_7TUPLE_COLOR                       1
#define ES2_KO_IP_7TUPLE_L3_RT                       (ES2_KO_IP_7TUPLE_COLOR + ES2_KL_IP_7TUPLE_COLOR)
#define ES2_KL_IP_7TUPLE_L3_RT                       1
#define ES2_KO_IP_7TUPLE_ES0_ISDX_KEY_ENA            (ES2_KO_IP_7TUPLE_L3_RT + ES2_KL_IP_7TUPLE_L3_RT)
#define ES2_KL_IP_7TUPLE_ES0_ISDX_KEY_ENA            1
#define ES2_KO_IP_7TUPLE_MIRROR_PROBE                (ES2_KO_IP_7TUPLE_ES0_ISDX_KEY_ENA + ES2_KL_IP_7TUPLE_ES0_ISDX_KEY_ENA)
#define ES2_KL_IP_7TUPLE_MIRROR_PROBE                2
#define ES2_KO_IP_7TUPLE_L2_DMAC_0                   (ES2_KO_IP_7TUPLE_MIRROR_PROBE + ES2_KL_IP_7TUPLE_MIRROR_PROBE)
#define ES2_KL_IP_7TUPLE_L2_DMAC_0                   32
#define ES2_KO_IP_7TUPLE_L2_DMAC_1                   (ES2_KO_IP_7TUPLE_L2_DMAC_0 + ES2_KL_IP_7TUPLE_L2_DMAC_0)
#define ES2_KL_IP_7TUPLE_L2_DMAC_1                   16
#define ES2_KO_IP_7TUPLE_L2_SMAC_0                   (ES2_KO_IP_7TUPLE_L2_DMAC_1 + ES2_KL_IP_7TUPLE_L2_DMAC_1)
#define ES2_KL_IP_7TUPLE_L2_SMAC_0                   32
#define ES2_KO_IP_7TUPLE_L2_SMAC_1                   (ES2_KO_IP_7TUPLE_L2_SMAC_0 + ES2_KL_IP_7TUPLE_L2_SMAC_0)
#define ES2_KL_IP_7TUPLE_L2_SMAC_1                   16
#define ES2_KO_IP_7TUPLE_IP4                         (FA_TGT ? (ES2_KO_IP_7TUPLE_L2_SMAC_1 + ES2_KL_IP_7TUPLE_L2_SMAC_1) : (ES2_KO_IP_7TUPLE_IP_SNAP + ES2_KL_IP_7TUPLE_IP_SNAP))
#define ES2_KL_IP_7TUPLE_IP4                         1
#define ES2_KO_IP_7TUPLE_L3_TTL_GT0                  (ES2_KO_IP_7TUPLE_IP4 + ES2_KL_IP_7TUPLE_IP4)
#define ES2_KL_IP_7TUPLE_L3_TTL_GT0                  1
#define ES2_KO_IP_7TUPLE_L3_TOS                      (ES2_KO_IP_7TUPLE_L3_TTL_GT0 + ES2_KL_IP_7TUPLE_L3_TTL_GT0)
#define ES2_KL_IP_7TUPLE_L3_TOS                      8
#define ES2_KO_IP_7TUPLE_L3_IP6_DIP_0                (ES2_KO_IP_7TUPLE_L3_TOS + ES2_KL_IP_7TUPLE_L3_TOS)
#define ES2_KL_IP_7TUPLE_L3_IP6_DIP_0                32
#define ES2_KO_IP_7TUPLE_L3_IP6_DIP_1                (ES2_KO_IP_7TUPLE_L3_IP6_DIP_0 + ES2_KL_IP_7TUPLE_L3_IP6_DIP_0)
#define ES2_KL_IP_7TUPLE_L3_IP6_DIP_1                32
#define ES2_KO_IP_7TUPLE_L3_IP6_DIP_2                (ES2_KO_IP_7TUPLE_L3_IP6_DIP_1 + ES2_KL_IP_7TUPLE_L3_IP6_DIP_1)
#define ES2_KL_IP_7TUPLE_L3_IP6_DIP_2                32
#define ES2_KO_IP_7TUPLE_L3_IP6_DIP_3                (ES2_KO_IP_7TUPLE_L3_IP6_DIP_2 + ES2_KL_IP_7TUPLE_L3_IP6_DIP_2)
#define ES2_KL_IP_7TUPLE_L3_IP6_DIP_3                32
#define ES2_KO_IP_7TUPLE_L3_IP6_SIP_0                (ES2_KO_IP_7TUPLE_L3_IP6_DIP_3 + ES2_KL_IP_7TUPLE_L3_IP6_DIP_3)
#define ES2_KL_IP_7TUPLE_L3_IP6_SIP_0                32
#define ES2_KO_IP_7TUPLE_L3_IP6_SIP_1                (ES2_KO_IP_7TUPLE_L3_IP6_SIP_0 + ES2_KL_IP_7TUPLE_L3_IP6_SIP_0)
#define ES2_KL_IP_7TUPLE_L3_IP6_SIP_1                32
#define ES2_KO_IP_7TUPLE_L3_IP6_SIP_2                (ES2_KO_IP_7TUPLE_L3_IP6_SIP_1 + ES2_KL_IP_7TUPLE_L3_IP6_SIP_1)
#define ES2_KL_IP_7TUPLE_L3_IP6_SIP_2                32
#define ES2_KO_IP_7TUPLE_L3_IP6_SIP_3                (ES2_KO_IP_7TUPLE_L3_IP6_SIP_2 + ES2_KL_IP_7TUPLE_L3_IP6_SIP_2)
#define ES2_KL_IP_7TUPLE_L3_IP6_SIP_3                32
#define ES2_KO_IP_7TUPLE_DIP_EQ_SIP                  (ES2_KO_IP_7TUPLE_L3_IP6_SIP_3 + ES2_KL_IP_7TUPLE_L3_IP6_SIP_3)
#define ES2_KL_IP_7TUPLE_DIP_EQ_SIP                  1
#define ES2_KO_IP_7TUPLE_TCP_UDP                     (ES2_KO_IP_7TUPLE_DIP_EQ_SIP + ES2_KL_IP_7TUPLE_DIP_EQ_SIP)
#define ES2_KL_IP_7TUPLE_TCP_UDP                     1
#define ES2_KO_IP_7TUPLE_TCP                         (ES2_KO_IP_7TUPLE_TCP_UDP + ES2_KL_IP_7TUPLE_TCP_UDP)
#define ES2_KL_IP_7TUPLE_TCP                         1
#define ES2_KO_IP_7TUPLE_L4_DPORT                    (ES2_KO_IP_7TUPLE_TCP + ES2_KL_IP_7TUPLE_TCP)
#define ES2_KL_IP_7TUPLE_L4_DPORT                    16
#define ES2_KO_IP_7TUPLE_L4_SPORT                    (ES2_KO_IP_7TUPLE_L4_DPORT + ES2_KL_IP_7TUPLE_L4_DPORT)
#define ES2_KL_IP_7TUPLE_L4_SPORT                    16
#define ES2_KO_IP_7TUPLE_L4_RNG                      (ES2_KO_IP_7TUPLE_L4_SPORT + ES2_KL_IP_7TUPLE_L4_SPORT)
#define ES2_KL_IP_7TUPLE_L4_RNG                      16
#define ES2_KO_IP_7TUPLE_SPORT_EQ_DPORT              (ES2_KO_IP_7TUPLE_L4_RNG + ES2_KL_IP_7TUPLE_L4_RNG)
#define ES2_KL_IP_7TUPLE_SPORT_EQ_DPORT              1
#define ES2_KO_IP_7TUPLE_SEQUENCE_EQ0                (ES2_KO_IP_7TUPLE_SPORT_EQ_DPORT + ES2_KL_IP_7TUPLE_SPORT_EQ_DPORT)
#define ES2_KL_IP_7TUPLE_SEQUENCE_EQ0                1
#define ES2_KO_IP_7TUPLE_L4_FIN                      (ES2_KO_IP_7TUPLE_SEQUENCE_EQ0 + ES2_KL_IP_7TUPLE_SEQUENCE_EQ0)
#define ES2_KL_IP_7TUPLE_L4_FIN                      1
#define ES2_KO_IP_7TUPLE_L4_SYN                      (ES2_KO_IP_7TUPLE_L4_FIN + ES2_KL_IP_7TUPLE_L4_FIN)
#define ES2_KL_IP_7TUPLE_L4_SYN                      1
#define ES2_KO_IP_7TUPLE_L4_RST                      (ES2_KO_IP_7TUPLE_L4_SYN + ES2_KL_IP_7TUPLE_L4_SYN)
#define ES2_KL_IP_7TUPLE_L4_RST                      1
#define ES2_KO_IP_7TUPLE_L4_PSH                      (ES2_KO_IP_7TUPLE_L4_RST + ES2_KL_IP_7TUPLE_L4_RST)
#define ES2_KL_IP_7TUPLE_L4_PSH                      1
#define ES2_KO_IP_7TUPLE_L4_ACK                      (ES2_KO_IP_7TUPLE_L4_PSH + ES2_KL_IP_7TUPLE_L4_PSH)
#define ES2_KL_IP_7TUPLE_L4_ACK                      1
#define ES2_KO_IP_7TUPLE_L4_URG                      (ES2_KO_IP_7TUPLE_L4_ACK + ES2_KL_IP_7TUPLE_L4_ACK)
#define ES2_KL_IP_7TUPLE_L4_URG                      1
#define ES2_KO_IP_7TUPLE_L4_PAYLOAD_0                (ES2_KO_IP_7TUPLE_L4_URG + ES2_KL_IP_7TUPLE_L4_URG)
#define ES2_KL_IP_7TUPLE_L4_PAYLOAD_0                32
#define ES2_KO_IP_7TUPLE_L4_PAYLOAD_1                (ES2_KO_IP_7TUPLE_L4_PAYLOAD_0 + ES2_KL_IP_7TUPLE_L4_PAYLOAD_0)
#define ES2_KL_IP_7TUPLE_L4_PAYLOAD_1                32

/* ES2 X6 key types */
#define ES2_X6_TYPE_MAC_ETYPE                        0
#define ES2_X6_TYPE_ARP                              1
#define ES2_X6_TYPE_IP4_TCP_UDP                      2
#define ES2_X6_TYPE_IP4_OTHER                        3
#define ES2_X6_TYPE_IP6_STD                          4
#define ES2_X6_TYPE_IP6_VID                          5

/* ES2 X6 common key fields */
#define ES2_KO_X6_TYPE                               0
#define ES2_KL_X6_TYPE                               3
#define ES2_KO_X6_FIRST                              (ES2_KO_X6_TYPE + ES2_KL_X6_TYPE)
#define ES2_KL_X6_FIRST                              1
#define ES2_KO_X6_ACL_GRP_ID                         (ES2_KO_X6_FIRST + ES2_KL_X6_FIRST)
#define ES2_KL_X6_ACL_GRP_ID                         8
#define ES2_KO_X6_PROT_ACTIVE                        (ES2_KO_X6_ACL_GRP_ID + ES2_KL_X6_ACL_GRP_ID)
#define ES2_KL_X6_PROT_ACTIVE                        1
#define ES2_KO_X6_L2_MC                              (ES2_KO_X6_PROT_ACTIVE + ES2_KL_X6_PROT_ACTIVE)
#define ES2_KL_X6_L2_MC                              1
#define ES2_KO_X6_L2_BC                              (ES2_KO_X6_L2_MC + ES2_KL_X6_L2_MC)
#define ES2_KL_X6_L2_BC                              1
#define ES2_KO_X6_SERVICE_FRM                        (ES2_KO_X6_L2_BC + ES2_KL_X6_L2_BC)
#define ES2_KL_X6_SERVICE_FRM                        1
#define ES2_KO_X6_ISDX                               (ES2_KO_X6_SERVICE_FRM + ES2_KL_X6_SERVICE_FRM)
#define ES2_KL_X6_ISDX                               (FA_TGT ? 12 : 10)
#define ES2_KO_X6_VLAN_TAGGED                        (ES2_KO_X6_ISDX + ES2_KL_X6_ISDX)
#define ES2_KL_X6_VLAN_TAGGED                        1
#define ES2_KO_X6_XVID                               (FA_TGT ? (ES2_KO_X6_VLAN_TAGGED + ES2_KL_X6_VLAN_TAGGED) : (ES2_KO_X6_RED_TAGGED + ES2_KL_X6_RED_TAGGED))
#define ES2_KL_X6_XVID                               13
#define ES2_KO_X6_EGR_PORT_MASK_RNG                  (ES2_KO_X6_XVID + ES2_KL_X6_XVID)
#define ES2_KL_X6_EGR_PORT_MASK_RNG                  3
#define ES2_KO_X6_EGR_PORT_MASK                      (ES2_KO_X6_EGR_PORT_MASK_RNG + ES2_KL_X6_EGR_PORT_MASK_RNG)
#define ES2_KL_X6_EGR_PORT_MASK                      32
#define ES2_KO_X6_IGR_PORT_SEL                       (ES2_KO_X6_EGR_PORT_MASK + ES2_KL_X6_EGR_PORT_MASK)
#define ES2_KL_X6_IGR_PORT_SEL                       1
#define ES2_KO_X6_IGR_PORT                           (ES2_KO_X6_IGR_PORT_SEL + ES2_KL_X6_IGR_PORT_SEL)
#define ES2_KL_X6_IGR_PORT                           (FA_TGT ? 9 : 7)
#define ES2_KO_X6_PCP                                (ES2_KO_X6_IGR_PORT + ES2_KL_X6_IGR_PORT)
#define ES2_KL_X6_PCP                                3
#define ES2_KO_X6_DEI                                (ES2_KO_X6_PCP + ES2_KL_X6_PCP)
#define ES2_KL_X6_DEI                                1
#define ES2_KO_X6_COSID                              (ES2_KO_X6_DEI + ES2_KL_X6_DEI)
#define ES2_KL_X6_COSID                              3
#define ES2_KO_X6_COLOR                              (ES2_KO_X6_COSID + ES2_KL_X6_COSID)
#define ES2_KL_X6_COLOR                              1
#define ES2_KO_X6_L3_RT                              (ES2_KO_X6_COLOR + ES2_KL_X6_COLOR)
#define ES2_KL_X6_L3_RT                              1
#define ES2_KO_X6_ES0_ISDX_KEY_ENA                   (ES2_KO_X6_L3_RT + ES2_KL_X6_L3_RT)
#define ES2_KL_X6_ES0_ISDX_KEY_ENA                   1
#define ES2_KO_X6_MIRROR_PROBE                       (ES2_KO_X6_ES0_ISDX_KEY_ENA + ES2_KL_X6_ES0_ISDX_KEY_ENA)
#define ES2_KL_X6_MIRROR_PROBE                       2

#define ES2_KO_X6_IP4                                (ES2_KO_X6_MIRROR_PROBE + ES2_KL_X6_MIRROR_PROBE)
#define ES2_KL_X6_IP4                                1
#define ES2_KO_X6_L3_FRAGMENT_TYPE                   (ES2_KO_X6_IP4 + ES2_KL_X6_IP4)
#define ES2_KL_X6_L3_FRAGMENT_TYPE                   2
#define ES2_KO_X6_L3_OPTIONS                         (ES2_KO_X6_L3_FRAGMENT_TYPE + ES2_KL_X6_L3_FRAGMENT_TYPE)
#define ES2_KL_X6_L3_OPTIONS                         1
#define ES2_KO_X6_L3_TTL_GT0                         (ES2_KO_X6_L3_OPTIONS + ES2_KL_X6_L3_OPTIONS)
#define ES2_KL_X6_L3_TTL_GT0                         1
#define ES2_KO_X6_L3_TOS                             (ES2_KO_X6_L3_TTL_GT0 + ES2_KL_X6_L3_TTL_GT0)
#define ES2_KL_X6_L3_TOS                             8
#define ES2_KO_X6_L3_IP4_DIP                         (ES2_KO_X6_L3_TOS + ES2_KL_X6_L3_TOS)
#define ES2_KL_X6_L3_IP4_DIP                         32
#define ES2_KO_X6_L3_IP4_SIP                         (ES2_KO_X6_L3_IP4_DIP + ES2_KL_X6_L3_IP4_DIP)
#define ES2_KL_X6_L3_IP4_SIP                         32
#define ES2_KO_X6_DIP_EQ_SIP                         (ES2_KO_X6_L3_IP4_SIP + ES2_KL_X6_L3_IP4_SIP)
#define ES2_KL_X6_DIP_EQ_SIP                         1

/* ES2 X6 MAC_ETYPE key fields */
#define ES2_KO_MAC_ETYPE_L2_DMAC_0                   (ES2_KO_X6_MIRROR_PROBE + ES2_KL_X6_MIRROR_PROBE)
#define ES2_KL_MAC_ETYPE_L2_DMAC_0                   32
#define ES2_KO_MAC_ETYPE_L2_DMAC_1                   (ES2_KO_MAC_ETYPE_L2_DMAC_0 + ES2_KL_MAC_ETYPE_L2_DMAC_0)
#define ES2_KL_MAC_ETYPE_L2_DMAC_1                   16
#define ES2_KO_MAC_ETYPE_L2_SMAC_0                   (ES2_KO_MAC_ETYPE_L2_DMAC_1 + ES2_KL_MAC_ETYPE_L2_DMAC_1)
#define ES2_KL_MAC_ETYPE_L2_SMAC_0                   32
#define ES2_KO_MAC_ETYPE_L2_SMAC_1                   (ES2_KO_MAC_ETYPE_L2_SMAC_0 + ES2_KL_MAC_ETYPE_L2_SMAC_0)
#define ES2_KL_MAC_ETYPE_L2_SMAC_1                   16
#define ES2_KO_MAC_ETYPE_ETYPE_LEN                   (ES2_KO_MAC_ETYPE_L2_SMAC_1 + ES2_KL_MAC_ETYPE_L2_SMAC_1)
#define ES2_KL_MAC_ETYPE_ETYPE_LEN                   1
#define ES2_KO_MAC_ETYPE_ETYPE                       (ES2_KO_MAC_ETYPE_ETYPE_LEN + ES2_KL_MAC_ETYPE_ETYPE_LEN)
#define ES2_KL_MAC_ETYPE_ETYPE                       16
#define ES2_KO_MAC_ETYPE_L2_PAYLOAD_ETYPE_0          (ES2_KO_MAC_ETYPE_ETYPE + ES2_KL_MAC_ETYPE_ETYPE)
#define ES2_KL_MAC_ETYPE_L2_PAYLOAD_ETYPE_0          32
#define ES2_KO_MAC_ETYPE_L2_PAYLOAD_ETYPE_1          (ES2_KO_MAC_ETYPE_L2_PAYLOAD_ETYPE_0 + ES2_KL_MAC_ETYPE_L2_PAYLOAD_ETYPE_0)
#define ES2_KL_MAC_ETYPE_L2_PAYLOAD_ETYPE_1          32
#define ES2_KO_MAC_ETYPE_OAM_CCM_CNTS_EQ0            (ES2_KO_MAC_ETYPE_L2_PAYLOAD_ETYPE_1 + ES2_KL_MAC_ETYPE_L2_PAYLOAD_ETYPE_1)
#define ES2_KL_MAC_ETYPE_OAM_CCM_CNTS_EQ0            1
#define ES2_KO_MAC_ETYPE_OAM_Y1731                   (ES2_KO_MAC_ETYPE_OAM_CCM_CNTS_EQ0 + ES2_KL_MAC_ETYPE_OAM_CCM_CNTS_EQ0)
#define ES2_KL_MAC_ETYPE_OAM_Y1731                   1

/* ES2 X6 ARP key fields */
#define ES2_KO_ARP_ES0_ISDX_KEY_ENA                  (ES2_KO_X6_COLOR + ES2_KL_X6_COLOR)
#define ES2_KL_ARP_ES0_ISDX_KEY_ENA                  1
#define ES2_KO_ARP_MIRROR_PROBE                      (ES2_KO_ARP_ES0_ISDX_KEY_ENA + ES2_KL_ARP_ES0_ISDX_KEY_ENA)
#define ES2_KL_ARP_MIRROR_PROBE                      2
#define ES2_KO_ARP_L2_SMAC_0                         (ES2_KO_ARP_MIRROR_PROBE + ES2_KL_ARP_MIRROR_PROBE)
#define ES2_KL_ARP_L2_SMAC_0                         32
#define ES2_KO_ARP_L2_SMAC_1                         (ES2_KO_ARP_L2_SMAC_0 + ES2_KL_ARP_L2_SMAC_0)
#define ES2_KL_ARP_L2_SMAC_1                         16
#define ES2_KO_ARP_ARP_ADDR_SPACE_OK                 (ES2_KO_ARP_L2_SMAC_1 + ES2_KL_ARP_L2_SMAC_1)
#define ES2_KL_ARP_ARP_ADDR_SPACE_OK                 1
#define ES2_KO_ARP_ARP_PROTO_SPACE_OK                (ES2_KO_ARP_ARP_ADDR_SPACE_OK + ES2_KL_ARP_ARP_ADDR_SPACE_OK)
#define ES2_KL_ARP_ARP_PROTO_SPACE_OK                1
#define ES2_KO_ARP_ARP_LEN_OK                        (ES2_KO_ARP_ARP_PROTO_SPACE_OK + ES2_KL_ARP_ARP_PROTO_SPACE_OK)
#define ES2_KL_ARP_ARP_LEN_OK                        1
#define ES2_KO_ARP_ARP_TGT_MATCH                     (ES2_KO_ARP_ARP_LEN_OK + ES2_KL_ARP_ARP_LEN_OK)
#define ES2_KL_ARP_ARP_TGT_MATCH                     1
#define ES2_KO_ARP_ARP_SENDER_MATCH                  (ES2_KO_ARP_ARP_TGT_MATCH + ES2_KL_ARP_ARP_TGT_MATCH)
#define ES2_KL_ARP_ARP_SENDER_MATCH                  1
#define ES2_KO_ARP_ARP_OPCODE_UNKNOWN                (ES2_KO_ARP_ARP_SENDER_MATCH + ES2_KL_ARP_ARP_SENDER_MATCH)
#define ES2_KL_ARP_ARP_OPCODE_UNKNOWN                1
#define ES2_KO_ARP_ARP_OPCODE                        (ES2_KO_ARP_ARP_OPCODE_UNKNOWN + ES2_KL_ARP_ARP_OPCODE_UNKNOWN)
#define ES2_KL_ARP_ARP_OPCODE                        2
#define ES2_KO_ARP_L3_IP4_DIP                        (ES2_KO_ARP_ARP_OPCODE + ES2_KL_ARP_ARP_OPCODE)
#define ES2_KL_ARP_L3_IP4_DIP                        32
#define ES2_KO_ARP_L3_IP4_SIP                        (ES2_KO_ARP_L3_IP4_DIP + ES2_KL_ARP_L3_IP4_DIP)
#define ES2_KL_ARP_L3_IP4_SIP                        32
#define ES2_KO_ARP_DIP_EQ_SIP                        (ES2_KO_ARP_L3_IP4_SIP + ES2_KL_ARP_L3_IP4_SIP)
#define ES2_KL_ARP_DIP_EQ_SIP                        1

/* ES2 X6 IP4_TCP_UDP key fields */
#define ES2_KO_IP4_TCP_UDP_TCP                       (ES2_KO_X6_DIP_EQ_SIP + ES2_KL_X6_DIP_EQ_SIP)
#define ES2_KL_IP4_TCP_UDP_TCP                       1
#define ES2_KO_IP4_TCP_UDP_L4_DPORT                  (ES2_KO_IP4_TCP_UDP_TCP + ES2_KL_IP4_TCP_UDP_TCP)
#define ES2_KL_IP4_TCP_UDP_L4_DPORT                  16
#define ES2_KO_IP4_TCP_UDP_L4_SPORT                  (ES2_KO_IP4_TCP_UDP_L4_DPORT + ES2_KL_IP4_TCP_UDP_L4_DPORT)
#define ES2_KL_IP4_TCP_UDP_L4_SPORT                  16
#define ES2_KO_IP4_TCP_UDP_L4_RNG                    (ES2_KO_IP4_TCP_UDP_L4_SPORT + ES2_KL_IP4_TCP_UDP_L4_SPORT)
#define ES2_KL_IP4_TCP_UDP_L4_RNG                    16
#define ES2_KO_IP4_TCP_UDP_SPORT_EQ_DPORT            (ES2_KO_IP4_TCP_UDP_L4_RNG + ES2_KL_IP4_TCP_UDP_L4_RNG)
#define ES2_KL_IP4_TCP_UDP_SPORT_EQ_DPORT            1
#define ES2_KO_IP4_TCP_UDP_SEQUENCE_EQ0              (ES2_KO_IP4_TCP_UDP_SPORT_EQ_DPORT + ES2_KL_IP4_TCP_UDP_SPORT_EQ_DPORT)
#define ES2_KL_IP4_TCP_UDP_SEQUENCE_EQ0              1
#define ES2_KO_IP4_TCP_UDP_L4_FIN                    (ES2_KO_IP4_TCP_UDP_SEQUENCE_EQ0 + ES2_KL_IP4_TCP_UDP_SEQUENCE_EQ0)
#define ES2_KL_IP4_TCP_UDP_L4_FIN                    1
#define ES2_KO_IP4_TCP_UDP_L4_SYN                    (ES2_KO_IP4_TCP_UDP_L4_FIN + ES2_KL_IP4_TCP_UDP_L4_FIN)
#define ES2_KL_IP4_TCP_UDP_L4_SYN                    1
#define ES2_KO_IP4_TCP_UDP_L4_RST                    (ES2_KO_IP4_TCP_UDP_L4_SYN + ES2_KL_IP4_TCP_UDP_L4_SYN)
#define ES2_KL_IP4_TCP_UDP_L4_RST                    1
#define ES2_KO_IP4_TCP_UDP_L4_PSH                    (ES2_KO_IP4_TCP_UDP_L4_RST + ES2_KL_IP4_TCP_UDP_L4_RST)
#define ES2_KL_IP4_TCP_UDP_L4_PSH                    1
#define ES2_KO_IP4_TCP_UDP_L4_ACK                    (ES2_KO_IP4_TCP_UDP_L4_PSH + ES2_KL_IP4_TCP_UDP_L4_PSH)
#define ES2_KL_IP4_TCP_UDP_L4_ACK                    1
#define ES2_KO_IP4_TCP_UDP_L4_URG                    (ES2_KO_IP4_TCP_UDP_L4_ACK + ES2_KL_IP4_TCP_UDP_L4_ACK)
#define ES2_KL_IP4_TCP_UDP_L4_URG                    1
#define ES2_KO_IP4_TCP_UDP_L4_PAYLOAD_0              (ES2_KO_IP4_TCP_UDP_L4_URG + ES2_KL_IP4_TCP_UDP_L4_URG)
#define ES2_KL_IP4_TCP_UDP_L4_PAYLOAD_0              32
#define ES2_KO_IP4_TCP_UDP_L4_PAYLOAD_1              (ES2_KO_IP4_TCP_UDP_L4_PAYLOAD_0 + ES2_KL_IP4_TCP_UDP_L4_PAYLOAD_0)
#define ES2_KL_IP4_TCP_UDP_L4_PAYLOAD_1              32

/* ES2 X6 IP4_OTHER key fields */
#define ES2_KO_IP4_OTHER_L3_IP_PROTO                 (ES2_KO_X6_DIP_EQ_SIP + ES2_KL_X6_DIP_EQ_SIP)
#define ES2_KL_IP4_OTHER_L3_IP_PROTO                 8
#define ES2_KO_IP4_OTHER_L3_PAYLOAD_0                (ES2_KO_IP4_OTHER_L3_IP_PROTO + ES2_KL_IP4_OTHER_L3_IP_PROTO)
#define ES2_KL_IP4_OTHER_L3_PAYLOAD_0                32
#define ES2_KO_IP4_OTHER_L3_PAYLOAD_1                (ES2_KO_IP4_OTHER_L3_PAYLOAD_0 + ES2_KL_IP4_OTHER_L3_PAYLOAD_0)
#define ES2_KL_IP4_OTHER_L3_PAYLOAD_1                32
#define ES2_KO_IP4_OTHER_L3_PAYLOAD_2                (ES2_KO_IP4_OTHER_L3_PAYLOAD_1 + ES2_KL_IP4_OTHER_L3_PAYLOAD_1)
#define ES2_KL_IP4_OTHER_L3_PAYLOAD_2                32

/* ES2 X6 IP6_STD key fields */
#define ES2_KO_IP6_STD_L3_TTL_GT0                    (ES2_KO_X6_MIRROR_PROBE + ES2_KL_X6_MIRROR_PROBE)
#define ES2_KL_IP6_STD_L3_TTL_GT0                    1
#define ES2_KO_IP6_STD_L3_IP6_SIP_0                  (ES2_KO_IP6_STD_L3_TTL_GT0 + ES2_KL_IP6_STD_L3_TTL_GT0)
#define ES2_KL_IP6_STD_L3_IP6_SIP_0                  32
#define ES2_KO_IP6_STD_L3_IP6_SIP_1                  (ES2_KO_IP6_STD_L3_IP6_SIP_0 + ES2_KL_IP6_STD_L3_IP6_SIP_0)
#define ES2_KL_IP6_STD_L3_IP6_SIP_1                  32
#define ES2_KO_IP6_STD_L3_IP6_SIP_2                  (ES2_KO_IP6_STD_L3_IP6_SIP_1 + ES2_KL_IP6_STD_L3_IP6_SIP_1)
#define ES2_KL_IP6_STD_L3_IP6_SIP_2                  32
#define ES2_KO_IP6_STD_L3_IP6_SIP_3                  (ES2_KO_IP6_STD_L3_IP6_SIP_2 + ES2_KL_IP6_STD_L3_IP6_SIP_2)
#define ES2_KL_IP6_STD_L3_IP6_SIP_3                  32
#define ES2_KO_IP6_STD_DIP_EQ_SIP                    (ES2_KO_IP6_STD_L3_IP6_SIP_3 + ES2_KL_IP6_STD_L3_IP6_SIP_3)
#define ES2_KL_IP6_STD_DIP_EQ_SIP                    1
#define ES2_KO_IP6_STD_L3_IP_PROTO                   (ES2_KO_IP6_STD_DIP_EQ_SIP + ES2_KL_IP6_STD_DIP_EQ_SIP)
#define ES2_KL_IP6_STD_L3_IP_PROTO                   8
#define ES2_KO_IP6_STD_L4_RNG                        (ES2_KO_IP6_STD_L3_IP_PROTO + ES2_KL_IP6_STD_L3_IP_PROTO)
#define ES2_KL_IP6_STD_L4_RNG                        16
#define ES2_KO_IP6_STD_L3_PAYLOAD_0                  (ES2_KO_IP6_STD_L4_RNG + ES2_KL_IP6_STD_L4_RNG)
#define ES2_KL_IP6_STD_L3_PAYLOAD_0                  32
#define ES2_KO_IP6_STD_L3_PAYLOAD_1                  (ES2_KO_IP6_STD_L3_PAYLOAD_0 + ES2_KL_IP6_STD_L3_PAYLOAD_0)
#define ES2_KL_IP6_STD_L3_PAYLOAD_1                  8

/* ES2 X6 IP6_VID key fields */
#define ES2_KO_IP6_VID_L3_RT                         (ES2_KO_X6_XVID + ES2_KL_X6_XVID)
#define ES2_KL_IP6_VID_L3_RT                         1
#define ES2_KO_IP6_VID_L3_IP6_DIP_0                  (ES2_KO_IP6_VID_L3_RT + ES2_KL_IP6_VID_L3_RT)
#define ES2_KL_IP6_VID_L3_IP6_DIP_0                  32
#define ES2_KO_IP6_VID_L3_IP6_DIP_1                  (ES2_KO_IP6_VID_L3_IP6_DIP_0 + ES2_KL_IP6_VID_L3_IP6_DIP_0)
#define ES2_KL_IP6_VID_L3_IP6_DIP_1                  32
#define ES2_KO_IP6_VID_L3_IP6_DIP_2                  (ES2_KO_IP6_VID_L3_IP6_DIP_1 + ES2_KL_IP6_VID_L3_IP6_DIP_1)
#define ES2_KL_IP6_VID_L3_IP6_DIP_2                  32
#define ES2_KO_IP6_VID_L3_IP6_DIP_3                  (ES2_KO_IP6_VID_L3_IP6_DIP_2 + ES2_KL_IP6_VID_L3_IP6_DIP_2)
#define ES2_KL_IP6_VID_L3_IP6_DIP_3                  32
#define ES2_KO_IP6_VID_L3_IP6_SIP_0                  (ES2_KO_IP6_VID_L3_IP6_DIP_3 + ES2_KL_IP6_VID_L3_IP6_DIP_3)
#define ES2_KL_IP6_VID_L3_IP6_SIP_0                  32
#define ES2_KO_IP6_VID_L3_IP6_SIP_1                  (ES2_KO_IP6_VID_L3_IP6_SIP_0 + ES2_KL_IP6_VID_L3_IP6_SIP_0)
#define ES2_KL_IP6_VID_L3_IP6_SIP_1                  32
#define ES2_KO_IP6_VID_L3_IP6_SIP_2                  (ES2_KO_IP6_VID_L3_IP6_SIP_1 + ES2_KL_IP6_VID_L3_IP6_SIP_1)
#define ES2_KL_IP6_VID_L3_IP6_SIP_2                  32
#define ES2_KO_IP6_VID_L3_IP6_SIP_3                  (ES2_KO_IP6_VID_L3_IP6_SIP_2 + ES2_KL_IP6_VID_L3_IP6_SIP_2)
#define ES2_KL_IP6_VID_L3_IP6_SIP_3                  32

/* ES2 X3 IP4_VID key fields */
#define ES2_KO_IP4_VID_FIRST                         0
#define ES2_KL_IP4_VID_FIRST                         1
#define ES2_KO_IP4_VID_ACL_GRP_ID                    (ES2_KO_IP4_VID_FIRST + ES2_KL_IP4_VID_FIRST)
#define ES2_KL_IP4_VID_ACL_GRP_ID                    8
#define ES2_KO_IP4_VID_PROT_ACTIVE                   (ES2_KO_IP4_VID_ACL_GRP_ID + ES2_KL_IP4_VID_ACL_GRP_ID)
#define ES2_KL_IP4_VID_PROT_ACTIVE                   1
#define ES2_KO_IP4_VID_L2_MC                         (ES2_KO_IP4_VID_PROT_ACTIVE + ES2_KL_IP4_VID_PROT_ACTIVE)
#define ES2_KL_IP4_VID_L2_MC                         1
#define ES2_KO_IP4_VID_L2_BC                         (ES2_KO_IP4_VID_L2_MC + ES2_KL_IP4_VID_L2_MC)
#define ES2_KL_IP4_VID_L2_BC                         1
#define ES2_KO_IP4_VID_SERVICE_FRM                   (ES2_KO_IP4_VID_L2_BC + ES2_KL_IP4_VID_L2_BC)
#define ES2_KL_IP4_VID_SERVICE_FRM                   1
#define ES2_KO_IP4_VID_ISDX                          (ES2_KO_IP4_VID_SERVICE_FRM + ES2_KL_IP4_VID_SERVICE_FRM)
#define ES2_KL_IP4_VID_ISDX                          (FA_TGT ? 12 : 10)
#define ES2_KO_IP4_VID_VLAN_TAGGED                   (ES2_KO_IP4_VID_ISDX + ES2_KL_IP4_VID_ISDX)
#define ES2_KL_IP4_VID_VLAN_TAGGED                   1
#define ES2_KO_IP4_VID_XVID                          (FA_TGT ? (ES2_KO_IP4_VID_VLAN_TAGGED + ES2_KL_IP4_VID_VLAN_TAGGED) : (ES2_KO_IP4_VID_RED_TAGGED + ES2_KL_IP4_VID_RED_TAGGED))
#define ES2_KL_IP4_VID_XVID                          13
#define ES2_KO_IP4_VID_PCP                           (ES2_KO_IP4_VID_XVID + ES2_KL_IP4_VID_XVID)
#define ES2_KL_IP4_VID_PCP                           3
#define ES2_KO_IP4_VID_DEI                           (ES2_KO_IP4_VID_PCP + ES2_KL_IP4_VID_PCP)
#define ES2_KL_IP4_VID_DEI                           1
#define ES2_KO_IP4_VID_COSID                         (ES2_KO_IP4_VID_DEI + ES2_KL_IP4_VID_DEI)
#define ES2_KL_IP4_VID_COSID                         3
#define ES2_KO_IP4_VID_COLOR                         (ES2_KO_IP4_VID_COSID + ES2_KL_IP4_VID_COSID)
#define ES2_KL_IP4_VID_COLOR                         1
#define ES2_KO_IP4_VID_L3_RT                         (ES2_KO_IP4_VID_COLOR + ES2_KL_IP4_VID_COLOR)
#define ES2_KL_IP4_VID_L3_RT                         1
#define ES2_KO_IP4_VID_ES0_ISDX_KEY_ENA              (ES2_KO_IP4_VID_L3_RT + ES2_KL_IP4_VID_L3_RT)
#define ES2_KL_IP4_VID_ES0_ISDX_KEY_ENA              1
#define ES2_KO_IP4_VID_MIRROR_PROBE                  (ES2_KO_IP4_VID_ES0_ISDX_KEY_ENA + ES2_KL_IP4_VID_ES0_ISDX_KEY_ENA)
#define ES2_KL_IP4_VID_MIRROR_PROBE                  2
#define ES2_KO_IP4_VID_IP4                           (ES2_KO_IP4_VID_MIRROR_PROBE + ES2_KL_IP4_VID_MIRROR_PROBE)
#define ES2_KL_IP4_VID_IP4                           1
#define ES2_KO_IP4_VID_L3_IP4_DIP                    (ES2_KO_IP4_VID_IP4 + ES2_KL_IP4_VID_IP4)
#define ES2_KL_IP4_VID_L3_IP4_DIP                    32
#define ES2_KO_IP4_VID_L3_IP4_SIP                    (ES2_KO_IP4_VID_L3_IP4_DIP + ES2_KL_IP4_VID_L3_IP4_DIP)
#define ES2_KL_IP4_VID_L3_IP4_SIP                    32
#define ES2_KO_IP4_VID_L4_RNG                        (ES2_KO_IP4_VID_L3_IP4_SIP + ES2_KL_IP4_VID_L3_IP4_SIP)
#define ES2_KL_IP4_VID_L4_RNG                        16

/* ES2 X3 BASE_TYPE action fields */
#define ES2_AO_BASE_TYPE_HIT_ME_ONCE                 0
#define ES2_AL_BASE_TYPE_HIT_ME_ONCE                 1
#define ES2_AO_BASE_TYPE_INTR_ENA                    (ES2_AO_BASE_TYPE_HIT_ME_ONCE + ES2_AL_BASE_TYPE_HIT_ME_ONCE)
#define ES2_AL_BASE_TYPE_INTR_ENA                    1
#define ES2_AO_BASE_TYPE_FWD_MODE                    (ES2_AO_BASE_TYPE_INTR_ENA + ES2_AL_BASE_TYPE_INTR_ENA)
#define ES2_AL_BASE_TYPE_FWD_MODE                    2
#define ES2_AO_BASE_TYPE_COPY_QUEUE_NUM              (ES2_AO_BASE_TYPE_FWD_MODE + ES2_AL_BASE_TYPE_FWD_MODE)
#define ES2_AL_BASE_TYPE_COPY_QUEUE_NUM              (FA_TGT ? 16 : 14)
#define ES2_AO_BASE_TYPE_COPY_PORT_NUM               (ES2_AO_BASE_TYPE_COPY_QUEUE_NUM + ES2_AL_BASE_TYPE_COPY_QUEUE_NUM)
#define ES2_AL_BASE_TYPE_COPY_PORT_NUM               (FA_TGT ? 7 : 6)
#define ES2_AO_BASE_TYPE_MIRROR_PROBE_ID             (ES2_AO_BASE_TYPE_COPY_PORT_NUM + ES2_AL_BASE_TYPE_COPY_PORT_NUM)
#define ES2_AL_BASE_TYPE_MIRROR_PROBE_ID             2
#define ES2_AO_BASE_TYPE_CPU_COPY                    (ES2_AO_BASE_TYPE_MIRROR_PROBE_ID + ES2_AL_BASE_TYPE_MIRROR_PROBE_ID)
#define ES2_AL_BASE_TYPE_CPU_COPY                    1
#define ES2_AO_BASE_TYPE_CPU_QUEUE_NUM               (ES2_AO_BASE_TYPE_CPU_COPY + ES2_AL_BASE_TYPE_CPU_COPY)
#define ES2_AL_BASE_TYPE_CPU_QUEUE_NUM               3
#define ES2_AO_BASE_TYPE_POLICE_ENA                  (ES2_AO_BASE_TYPE_CPU_QUEUE_NUM + ES2_AL_BASE_TYPE_CPU_QUEUE_NUM)
#define ES2_AL_BASE_TYPE_POLICE_ENA                  1
#define ES2_AO_BASE_TYPE_POLICE_REMARK               (ES2_AO_BASE_TYPE_POLICE_ENA + ES2_AL_BASE_TYPE_POLICE_ENA)
#define ES2_AL_BASE_TYPE_POLICE_REMARK               1
#define ES2_AO_BASE_TYPE_POLICE_IDX                  (ES2_AO_BASE_TYPE_POLICE_REMARK + ES2_AL_BASE_TYPE_POLICE_REMARK)
#define ES2_AL_BASE_TYPE_POLICE_IDX                  (FA_TGT ? 6 : 5)
#define ES2_AO_BASE_TYPE_ES2_REW_CMD                 (ES2_AO_BASE_TYPE_POLICE_IDX + ES2_AL_BASE_TYPE_POLICE_IDX)
#define ES2_AL_BASE_TYPE_ES2_REW_CMD                 3
#define ES2_AO_BASE_TYPE_CNT_ID                      (ES2_AO_BASE_TYPE_ES2_REW_CMD + ES2_AL_BASE_TYPE_ES2_REW_CMD)
#define ES2_AL_BASE_TYPE_CNT_ID                      (FA_TGT ? 11 : 9)
#define ES2_AO_BASE_TYPE_IGNORE_PIPELINE_CTRL        (ES2_AO_BASE_TYPE_CNT_ID + ES2_AL_BASE_TYPE_CNT_ID)
#define ES2_AL_BASE_TYPE_IGNORE_PIPELINE_CTRL        1

/* ================================================================= *
 *  VCAP IP6PFX
 * ================================================================= */

/* IP6PFX X2 IP6PFX key fields */
#define IP6PFX_KO_IP6PFX_DST_FLAG                    0
#define IP6PFX_KL_IP6PFX_DST_FLAG                    1
#define IP6PFX_KO_IP6PFX_AFFIX                       (IP6PFX_KO_IP6PFX_DST_FLAG + IP6PFX_KL_IP6PFX_DST_FLAG)
#define IP6PFX_KL_IP6PFX_AFFIX                       10
#define IP6PFX_KO_IP6PFX_IP6_XIP_2                   (IP6PFX_KO_IP6PFX_AFFIX + IP6PFX_KL_IP6PFX_AFFIX)
#define IP6PFX_KL_IP6PFX_IP6_XIP_2                   32
#define IP6PFX_KO_IP6PFX_IP6_XIP_3                   (IP6PFX_KO_IP6PFX_IP6_XIP_2 + IP6PFX_KL_IP6PFX_IP6_XIP_2)
#define IP6PFX_KL_IP6PFX_IP6_XIP_3                   32

/* IP6PFX X1 IP6PFX_ID action fields */
#define IP6PFX_AO_IP6PFX_ID_IP6PFX_ID                0
#define IP6PFX_AL_IP6PFX_ID_IP6PFX_ID                (FA_TGT ? 9 : 8)

/* ======================================= */
/* Laguna only defines */
/* ======================================= */
#define CLM_KO_NORMAL_7TUPLE_RED_TAGGED              (CLM_KO_NORMAL_7TUPLE_VID2 + CLM_KL_NORMAL_7TUPLE_VID2)
#define CLM_KL_NORMAL_7TUPLE_RED_TAGGED              1
#define CLM_KO_X6_RED_TAGGED                         (CLM_KO_X6_VID2 + CLM_KL_X6_VID2)
#define CLM_KL_X6_RED_TAGGED                         1
#define CLM_KO_LL_FULL_RED_TAGGED                    (CLM_KO_LL_FULL_VID2 + CLM_KL_LL_FULL_VID2)
#define CLM_KL_LL_FULL_RED_TAGGED                    1
#define CLM_KO_MLL_RED_TAGGED                        (CLM_KO_MLL_VID1 + CLM_KL_MLL_VID1)
#define CLM_KL_MLL_RED_TAGGED                        1
#define CLM_KO_TRI_VID_RED_TAGGED                    (CLM_KO_TRI_VID_VID2 + CLM_KL_TRI_VID_VID2)
#define CLM_KL_TRI_VID_RED_TAGGED                    1
#define CLM_KO_TRI_VID_IDX_RED_TAGGED                (CLM_KO_TRI_VID_IDX_VID2 + CLM_KL_TRI_VID_IDX_VID2)
#define CLM_KL_TRI_VID_IDX_RED_TAGGED                1
#define CLM_KO_DBL_VID_IDX_RED_TAGGED                (CLM_KO_DBL_VID_IDX_VID1 + CLM_KL_DBL_VID_IDX_VID1)
#define CLM_KL_DBL_VID_IDX_RED_TAGGED                1
#define CLM_AO_FULL_OAM_MRP_ENA                      (CLM_AO_FULL_OAM_IP_BFD_ENA + CLM_AL_FULL_OAM_IP_BFD_ENA)
#define CLM_AL_FULL_OAM_MRP_ENA                      1
#define CLM_AO_FULL_OAM_DLR_ENA                      (CLM_AO_FULL_OAM_MRP_ENA + CLM_AL_FULL_OAM_MRP_ENA)
#define CLM_AL_FULL_OAM_DLR_ENA                      1
#define CLM_AO_MLBS_OAM_MRP_ENA                      (CLM_AO_MLBS_OAM_IP_BFD_ENA + CLM_AL_MLBS_OAM_IP_BFD_ENA)
#define CLM_AL_MLBS_OAM_MRP_ENA                      1
#define CLM_AO_MLBS_OAM_DLR_ENA                      (CLM_AO_MLBS_OAM_MRP_ENA + CLM_AL_MLBS_OAM_MRP_ENA)
#define CLM_AL_MLBS_OAM_DLR_ENA                      1
#define CLM_AO_CLASSIFICATION_OAM_MRP_ENA            (CLM_AO_CLASSIFICATION_OAM_IP_BFD_ENA + CLM_AL_CLASSIFICATION_OAM_IP_BFD_ENA)
#define CLM_AL_CLASSIFICATION_OAM_MRP_ENA            1
#define CLM_AO_CLASSIFICATION_OAM_DLR_ENA            (CLM_AO_CLASSIFICATION_OAM_MRP_ENA + CLM_AL_CLASSIFICATION_OAM_MRP_ENA)
#define CLM_AL_CLASSIFICATION_OAM_DLR_ENA            1
#define CLM_AO_CLASS_REDUCED_OAM_MRP_ENA             (CLM_AO_CLASS_REDUCED_OAM_Y1731_SEL + CLM_AL_CLASS_REDUCED_OAM_Y1731_SEL)
#define CLM_AL_CLASS_REDUCED_OAM_MRP_ENA             1
#define CLM_AO_CLASS_REDUCED_OAM_DLR_ENA             (CLM_AO_CLASS_REDUCED_OAM_MRP_ENA + CLM_AL_CLASS_REDUCED_OAM_MRP_ENA)
#define CLM_AL_CLASS_REDUCED_OAM_DLR_ENA             1
#define IS2_KO_X12_RED_TAGGED                        (IS2_KO_X12_VLAN_TAGGED + IS2_KL_X12_VLAN_TAGGED)
#define IS2_KL_X12_RED_TAGGED                        1
#define IS2_KO_IP_7TUPLE_ETYPE_LEN                   (IS2_KO_X12_L2_SMAC_1 + IS2_KL_X12_L2_SMAC_1)
#define IS2_KL_IP_7TUPLE_ETYPE_LEN                   1
#define IS2_KO_IP_7TUPLE_IP_SNAP                     (IS2_KO_IP_7TUPLE_ETYPE_LEN + IS2_KL_IP_7TUPLE_ETYPE_LEN)
#define IS2_KL_IP_7TUPLE_IP_SNAP                     1
#define IS2_KO_IP_7TUPLE_OAM_Y1731                   (IS2_KO_IP_7TUPLE_L4_PAYLOAD_1 + IS2_KL_IP_7TUPLE_L4_PAYLOAD_1)
#define IS2_KL_IP_7TUPLE_OAM_Y1731                   1
#define IS2_KO_X6_RED_TAGGED                         (IS2_KO_X6_VLAN_TAGGED + IS2_KL_X6_VLAN_TAGGED)
#define IS2_KL_X6_RED_TAGGED                         1
#define IS2_AO_BASE_TYPE_CPU_DIS_MODE                (IS2_AO_BASE_TYPE_CPU_QU_NUM + IS2_AL_BASE_TYPE_CPU_QU_NUM)
#define IS2_AL_BASE_TYPE_CPU_DIS_MODE                1
#define IS2_AO_BASE_TYPE_MAC_REW_SEL                 (IS2_AO_BASE_TYPE_SWAP_MAC_ENA + IS2_AL_BASE_TYPE_SWAP_MAC_ENA)
#define IS2_AL_BASE_TYPE_MAC_REW_SEL                 2
#define IS2_AO_BASE_TYPE_RB_FWD_SEL                  (IS2_AO_BASE_TYPE_EGR_ACL_ENA + IS2_AL_BASE_TYPE_EGR_ACL_ENA)
#define IS2_AL_BASE_TYPE_RB_FWD_SEL                  2
#define IS2_AO_BASE_TYPE_RB_TC0_ENA                  (IS2_AO_BASE_TYPE_RB_FWD_SEL + IS2_AL_BASE_TYPE_RB_FWD_SEL)
#define IS2_AL_BASE_TYPE_RB_TC0_ENA                  1
#define IS2_AO_BASE_TYPE_RB_PTP_ENA                  (IS2_AO_BASE_TYPE_RB_TC0_ENA + IS2_AL_BASE_TYPE_RB_TC0_ENA)
#define IS2_AL_BASE_TYPE_RB_PTP_ENA                  1
#define ES0_AO_ES0_RB_RTAG_ENA                       (ES0_AO_ES0_QS_INFO + ES0_AL_ES0_QS_INFO)
#define ES0_AL_ES0_RB_RTAG_ENA                       1
#define ES2_KO_IP_7TUPLE_RED_TAGGED                  (ES2_KO_IP_7TUPLE_VLAN_TAGGED + ES2_KL_IP_7TUPLE_VLAN_TAGGED)
#define ES2_KL_IP_7TUPLE_RED_TAGGED                  1
#define ES2_KO_IP_7TUPLE_ETYPE_LEN                   (ES2_KO_IP_7TUPLE_L2_SMAC_1 + ES2_KL_IP_7TUPLE_L2_SMAC_1)
#define ES2_KL_IP_7TUPLE_ETYPE_LEN                   1
#define ES2_KO_IP_7TUPLE_IP_SNAP                     (ES2_KO_IP_7TUPLE_ETYPE_LEN + ES2_KL_IP_7TUPLE_ETYPE_LEN)
#define ES2_KL_IP_7TUPLE_IP_SNAP                     1
#define ES2_KO_IP_7TUPLE_OAM_Y1731                   (ES2_KO_IP_7TUPLE_L4_PAYLOAD_1 + ES2_KL_IP_7TUPLE_L4_PAYLOAD_1)
#define ES2_KL_IP_7TUPLE_OAM_Y1731                   1
#define ES2_KO_X6_RED_TAGGED                         (ES2_KO_X6_VLAN_TAGGED + ES2_KL_X6_VLAN_TAGGED)
#define ES2_KL_X6_RED_TAGGED                         1
#define ES2_KO_IP4_VID_RED_TAGGED                    (ES2_KO_IP4_VID_VLAN_TAGGED + ES2_KL_IP4_VID_VLAN_TAGGED)
#define ES2_KL_IP4_VID_RED_TAGGED                    1
