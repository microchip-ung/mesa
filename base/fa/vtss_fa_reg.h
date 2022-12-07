// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _FA_REG_H_
#define _FA_REG_H_

#if defined(VTSS_ARCH_FA)

/* Commands for Mac Table Command register */
#define MAC_CMD_LEARN         0 /* Insert (Learn) 1 entry */
#define MAC_CMD_UNLEARN       1 /* Unlearn (Forget) 1 entry */
#define MAC_CMD_LOOKUP        2 /* Look up 1 entry */
#define MAC_CMD_READ          3 /* Read entry at Mac Table Index */
#define MAC_CMD_WRITE         4 /* Write entry at Mac Table Index */
#define MAC_CMD_SCAN          5 /* Scan (Age or find next) */
#define MAC_CMD_FIND_SMALLEST 6 /* Get next entry */
#define MAC_CMD_CLEAR_ALL     7 /* Delete all entries in table */

/* Commands for MAC_ENTRY_ADDR_TYPE */
#define  MAC_ENTRY_ADDR_TYPE_UPSID_PN         0
#define  MAC_ENTRY_ADDR_TYPE_UPSID_CPU_OR_INT 1
#define  MAC_ENTRY_ADDR_TYPE_GLAG             2
#define  MAC_ENTRY_ADDR_TYPE_MC_IDX           3

/* CLM TPID values */
#define CLM_TPID_UNTAG    0
#define CLM_TPID_C_TAG    1
#define CLM_TPID_S_TAG    4
#define CLM_TPID_CUSTOM_1 5
#define CLM_TPID_CUSTOM_2 6
#define CLM_TPID_CUSTOM_3 7

/* CLM pipeline enable/mode */
#define CLM_PL_ENA_NONE 0
#define CLM_PL_ENA_XTR  1
#define CLM_PL_ENA_INJ  2
#define CLM_PL_ENA_LBK  3

/* CLM pipeline action selection */
#define CLM_PL_SEL_INJ_NORMAL 0
#define CLM_PL_SEL_INJ_MASQ   1
#define CLM_PL_SEL_LBK_QS     0
#define CLM_PL_SEL_LBK_ASM    1

/* IS2/CLM pipeline points */
#define CLM_PL_PT_NONE         0
#define CLM_PL_PT_ANA_VRAP     1
#define CLM_PL_PT_ANA_PORT_VOE 2
#define CLM_PL_PT_ANA_CL       3
#define CLM_PL_PT_ANA_CLM      4
#define CLM_PL_PT_ANA_IPT_PROT 5
#define CLM_PL_PT_ANA_OU_MIP   6
#define CLM_PL_PT_ANA_OU_SW    7
#define CLM_PL_PT_ANA_OU_PROT  8
#define CLM_PL_PT_ANA_OU_VOE   9
#define CLM_PL_PT_ANA_MID_PROT 10
#define CLM_PL_PT_ANA_IN_VOE   11
#define CLM_PL_PT_ANA_IN_PROT  12
#define CLM_PL_PT_ANA_IN_SW    13
#define CLM_PL_PT_ANA_IN_MIP   14
#define CLM_PL_PT_ANA_VLAN     15
#define CLM_PL_PT_ANA_DONE     16

/* ES0 PUSH_OUTER_TAG values */
#define ES0_ACT_PUSH_OT_PORT_ENA 0
#define ES0_ACT_PUSH_OT_ES0      1
#define ES0_ACT_PUSH_OT_PORT     2
#define ES0_ACT_PUSH_OT_NONE     3

/* ES0 TPID_SEL values */
#define ES0_ACT_TPID_SEL_C        0
#define ES0_ACT_TPID_SEL_S        1
#define ES0_ACT_TPID_SEL_CUSTOM_1 2
#define ES0_ACT_TPID_SEL_CUSTOM_2 3
#define ES0_ACT_TPID_SEL_CUSTOM_3 4
#define ES0_ACT_TPID_SEL_INGRESS  5

/* ES0 VID_SEL values */
#define ES0_ACT_VID_SEL_CL_VID   0
#define ES0_ACT_VID_SEL_VID_ES0  1
#define ES0_ACT_VID_SEL_GVID     2

/* ES0 PCP_SEL values */
#define ES0_ACT_PCP_SEL_CL_PCP  0
#define ES0_ACT_PCP_SEL_PCP_ES0 1
#define ES0_ACT_PCP_SEL_POPPED  3
#define ES0_ACT_PCP_SEL_MAP_0   4
#define ES0_ACT_PCP_SEL_MAP_1   5
#define ES0_ACT_PCP_SEL_MAP_2   6
#define ES0_ACT_PCP_SEL_MAP_3   7

/* ES0 DEI_SEL values */
#define ES0_ACT_DEI_SEL_CL_DEI  0
#define ES0_ACT_DEI_SEL_DEI_ES0 1
#define ES0_ACT_DEI_SEL_MAPPED  2
#define ES0_ACT_DEI_SEL_POPPED  3
#define ES0_ACT_DEI_SEL_MAP_0   4
#define ES0_ACT_DEI_SEL_MAP_1   5
#define ES0_ACT_DEI_SEL_MAP_2   6
#define ES0_ACT_DEI_SEL_MAP_3   7

/* ES0 DSCP_SEL values */
#define ES0_ACT_DSCP_SEL_PORT  0
#define ES0_ACT_DSCP_SEL_CL    1
#define ES0_ACT_DSCP_SEL_ES0   2
#define ES0_ACT_DSCP_SEL_RESV  3
#define ES0_ACT_DSCP_SEL_MAP_0 4
#define ES0_ACT_DSCP_SEL_MAP_1 5
#define ES0_ACT_DSCP_SEL_MAP_2 6
#define ES0_ACT_DSCP_SEL_MAP_3 7

/* ES0 TC_SEL values */
#define ES0_ACT_TC_SEL_CL    0
#define ES0_ACT_TC_SEL_ES0   1
#define ES0_ACT_TC_SEL_COSID 2
#define ES0_ACT_TC_SEL_RESV  3
#define ES0_ACT_TC_SEL_MAP_0 4
#define ES0_ACT_TC_SEL_MAP_1 5
#define ES0_ACT_TC_SEL_MAP_2 6
#define ES0_ACT_TC_SEL_MAP_3 7

#endif /* VTSS_ARCH_FA */
#endif /* _FA_REG_H */

