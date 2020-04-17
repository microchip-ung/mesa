// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _LUTON26_REG_H_
#define _LUTON26_REG_H_

#include "vtss_luton26_regs.h"

/* Port -> DEV_RGMII, DEV Target Offset */
#define VTSS_TO_DEV(port)   (VTSS_TO_DEV_0 + (port * (VTSS_TO_DEV_1 - VTSS_TO_DEV_0)))

/* Commands for Mac Table Command register */
#define MAC_CMD_IDLE        0  /* Idle */
#define MAC_CMD_LEARN       1  /* Insert (Learn) 1 entry */
#define MAC_CMD_FORGET      2  /* Delete (Forget) 1 entry */
#define MAC_CMD_TABLE_AGE   3  /* Age entire table */
#define MAC_CMD_GET_NEXT    4  /* Get next entry */
#define MAC_CMD_TABLE_CLEAR 5  /* Delete all entries in table */
#define MAC_CMD_READ        6  /* Read entry at Mac Table Index */
#define MAC_CMD_WRITE       7  /* Write entry at Mac Table Index */

#define MAC_TYPE_NORMAL  0 /* Normal entry */
#define MAC_TYPE_LOCKED  1 /* Locked entry */
#define MAC_TYPE_IPV4_MC 2 /* IPv4 MC entry */
#define MAC_TYPE_IPV6_MC 3 /* IPv6 MC entry */

/* Commands for VLAN Table Command register */
#define VLAN_CMD_IDLE        0  /* Idle */
#define VLAN_CMD_READ        1  /* Read entry at VLAN Table Index */
#define VLAN_CMD_WRITE       2  /* Write entry at VLAN Table Index */
#define VLAN_CMD_TABLE_CLEAR 3  /* Reset all entries in table */

/* Types for REW_PORT::TAG_CFG */
#define TAG_CFG_DISABLE       0 /* Port tagging disabled */
#define TAG_CFG_ALL_NPV_NNUL  1 /* Tag all frames, except when VID=PORT_VLAN_CFG.PORT_VID or VID=0 */
#define TAG_CFG_ALL_NNUL      2 /* Tag all frames, except when VID=0 */
#define TAG_CFG_ALL           3 /* Tag all frames */

/* Types for REW_PORT::TAG_TPID_CFG */
#define TAG_TPID_CFG_0x8100   0  /* Use 0x8100 */
#define TAG_TPID_CFG_0x88A8   1  /* Use 0x88A8 */
#define TAG_TPID_CFG_PTPID    2  /* Use custom from PORT_VLAN_CFG.PORT_TPID */
#define TAG_TPID_CFG_PTPID_NC 3  /* As above, but unless ingress tag was a C-tag */

/* Types for SYS_POL::POL_MODE_CFG */
#define POL_MODE_LINERATE       0 /* Line rate. Police bytes including IPG_SIZE */
#define POL_MODE_DATARATE       1 /* Data rate. Police bytes excluding IPG. */
#define POL_MODE_FRMRATE_100FPS 2 /* Frame rate. Rate unit = 100 fps */
#define POL_MODE_FRMRATE_1FPS   3 /* Frame rate. Rate unit = 1 fps */

/* ACL Mask bits (inverse of chip polarity) */
#define ACL_MASK_ONES           0xFFFFFFFF
#define ACL_MASK_ZERO           0

/* IS2 ACL types */
#define ACL_TYPE_ETYPE            0
#define ACL_TYPE_LLC              1
#define ACL_TYPE_SNAP             2
#define ACL_TYPE_ARP              3
#define ACL_TYPE_UDP_TCP          4
#define ACL_TYPE_IPV4             5
#define ACL_TYPE_IPV6             6
#define ACL_TYPE_ANY              100 /* Pseudo type */

/* VCAP Type-Group values */
#define VCAP_TG_VAL_IS1_IS1     5 /* Value 1 in both subwords: 0101 */
#define VCAP_TG_VAL_IS1_IP4     2
#define VCAP_TG_VAL_IS1_IP6     1
#define VCAP_TG_VAL_IS2         1
#define VCAP_TG_VAL_ES0         1

/* IS1 action types */
#define IS1_ACTION_TYPE_NORMAL    0
#define IS1_ACTION_TYPE_SMAC_SIP4 1
#define IS1_ACTION_TYPE_SMAC_SIP6 2

#endif /* _LUTON26_REG_H */

