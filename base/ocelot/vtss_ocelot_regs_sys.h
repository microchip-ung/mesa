// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_OCELOT_REGS_SYS_H_
#define _VTSS_OCELOT_REGS_SYS_H_


#include "vtss_ocelot_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a SYS
 *
 * Switching Engine Configuration
 *
 ***********************************************************************/

/**
 * Register Group: \a SYS:SYSTEM
 *
 * Switch configuration
 */


/** 
 * \brief Core reset control
 *
 * \details
 * Controls reset and initialization of the switching core. Proper startup
 * sequence is:
 * - Enable memories
 * - Initialize memories
 * - Enable core
 *
 * Register: \a SYS:SYSTEM:RESET_CFG
 */
#define VTSS_SYS_SYSTEM_RESET_CFG            VTSS_IOREG(VTSS_TO_SYS,0x142)

/** 
 * \brief
 * Switch core is enabled when this field is set.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_RESET_CFG . CORE_ENA
 */
#define  VTSS_F_SYS_SYSTEM_RESET_CFG_CORE_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Core memory controllers are enabled when this field is set.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_RESET_CFG . MEM_ENA
 */
#define  VTSS_F_SYS_SYSTEM_RESET_CFG_MEM_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Initialize core memories. Field is automatically cleared when operation
 * is complete ( approx. 40 us).
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_RESET_CFG . MEM_INIT
 */
#define  VTSS_F_SYS_SYSTEM_RESET_CFG_MEM_INIT  VTSS_BIT(0)


/** 
 * \brief Target for core memory inspection
 *
 * \details
 * Register: \a SYS:SYSTEM:CMID
 */
#define VTSS_SYS_SYSTEM_CMID                 VTSS_IOREG(VTSS_TO_SYS,0x143)

/** 
 * \brief
 * Refer to cmid.xls in the AS1000, misc_docs folder.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_CMID . CMID
 */
#define  VTSS_F_SYS_SYSTEM_CMID_CMID(x)       VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SYS_SYSTEM_CMID_CMID          VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SYS_SYSTEM_CMID_CMID(x)       VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief S-tag Ethernet Type
 *
 * \details
 * Register: \a SYS:SYSTEM:VLAN_ETYPE_CFG
 */
#define VTSS_SYS_SYSTEM_VLAN_ETYPE_CFG       VTSS_IOREG(VTSS_TO_SYS,0x144)

/** 
 * \brief
 * Custom Ethernet Type for S-tags. Tags with TPID = 0x88A8 are always
 * recognized as S-tags.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_VLAN_ETYPE_CFG . VLAN_S_TAG_ETYPE_VAL
 */
#define  VTSS_F_SYS_SYSTEM_VLAN_ETYPE_CFG_VLAN_S_TAG_ETYPE_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SYS_SYSTEM_VLAN_ETYPE_CFG_VLAN_S_TAG_ETYPE_VAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SYS_SYSTEM_VLAN_ETYPE_CFG_VLAN_S_TAG_ETYPE_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Per device port configuration
 *
 * \details
 * These configurations exists per front port and for each of the two CPU
 * ports (11+12).
 *
 * Register: \a SYS:SYSTEM:PORT_MODE
 *
 * @param ri Replicator: x_DPORT_CNT (??), 0-12
 */
#define VTSS_SYS_SYSTEM_PORT_MODE(ri)        VTSS_IOREG(VTSS_TO_SYS,0x145 + (ri))

/** 
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_PORT_MODE . DATA_WO_TS
 */
#define  VTSS_F_SYS_SYSTEM_PORT_MODE_DATA_WO_TS(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_SYS_SYSTEM_PORT_MODE_DATA_WO_TS     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_SYS_SYSTEM_PORT_MODE_DATA_WO_TS(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/** 
 * \brief
 * Set the mode for the formatting of incoming frames. If INCL_INJ_HDR>0,
 * incoming frames are expected to contain the selected prefix followed by
 * the 16-byte CPU injection header as the first part of the frame. Frames
 * are forwarded based on the contents in the CPU injection header instead
 * of normal forwarding.
 * 
 * Three different prefixes are supported:
 * - No prefix.
 * - Short prefix: 0x8880000A.
 * - Long prefix: any DMAC, any SMAC, EtherType=0x8880, payload=0x000A.
 * 
 * In modes 2 and 3, if the incoming frame's format does not comply with
 * the prefix, then sticky bit INJ_HDR_PREFIX_ERR is set. A non-complying
 * frame is discarded. 

 *
 * \details 
 * 0: No CPU injection header (normal frames)
 * 1: CPU injection header without prefix
 * 2: CPU injection header with short prefix
 * 3: CPU injection header with long prefix

 *
 * Field: ::VTSS_SYS_SYSTEM_PORT_MODE . INCL_INJ_HDR
 */
#define  VTSS_F_SYS_SYSTEM_PORT_MODE_INCL_INJ_HDR(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_SYS_SYSTEM_PORT_MODE_INCL_INJ_HDR     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_SYS_SYSTEM_PORT_MODE_INCL_INJ_HDR(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * Set the mode for the formatting of outgoing frames. If INCL_XTR_HDR>0,
 * outgoing frames are prepended the selected prefix followed by the
 * 16-byte CPU extraction header as the first part of the frame. Inserting
 * the CPU extraction header prevents other rewriter operations on the same
 * frame.
 * 
 * Three different prefixes are supported:
 * - No prefix.
 * - Short prefix: 0x8880000A.
 * - Long prefix: DMAC=0xFFFFFFFFFFFF, SMAC=0xFEFFFFFFFFFF,
 * EtherType=0x8880, payload=0x000A.
 *
 * \details 
 * 0: No CPU extraction header (normal frames)
 * 1: CPU extraction header without prefix
 * 2: CPU extraction header with short prefix
 * 3: CPU extraction header with long prefix

 *
 * Field: ::VTSS_SYS_SYSTEM_PORT_MODE . INCL_XTR_HDR
 */
#define  VTSS_F_SYS_SYSTEM_PORT_MODE_INCL_XTR_HDR(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_SYS_SYSTEM_PORT_MODE_INCL_XTR_HDR     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_SYS_SYSTEM_PORT_MODE_INCL_XTR_HDR(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * If set, a frame has been received with prefix not complying with the
 * setting in INCL_INJ_HDR.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_PORT_MODE . INJ_HDR_ERR
 */
#define  VTSS_F_SYS_SYSTEM_PORT_MODE_INJ_HDR_ERR  VTSS_BIT(0)


/** 
 * \brief Various Ethernet port configurations per front port
 *
 * \details
 * Register: \a SYS:SYSTEM:FRONT_PORT_MODE
 *
 * @param ri Replicator: x_FPORT_CNT (??), 0-10
 */
#define VTSS_SYS_SYSTEM_FRONT_PORT_MODE(ri)  VTSS_IOREG(VTSS_TO_SYS,0x152 + (ri))

/** 
 * \brief
 * Enables the queue system to support the half-duplex mode. Must be set
 * for a port when enabled for half-duplex mode (MAC_MODE_ENA.FDX_ENA
 * cleared).
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_FRONT_PORT_MODE . HDX_MODE
 */
#define  VTSS_F_SYS_SYSTEM_FRONT_PORT_MODE_HDX_MODE  VTSS_BIT(0)


/** 
 * \brief Frame aging configuration
 *
 * \details
 * Register: \a SYS:SYSTEM:FRM_AGING
 */
#define VTSS_SYS_SYSTEM_FRM_AGING            VTSS_IOREG(VTSS_TO_SYS,0x15d)

/** 
 * \brief
 * If set, frames exceeding the frame aging time while waiting head-of-line
 * in a port due to a link partner signaling pause are allowed to be aged.
 * Note that frames aged in this case are not counted by the normal frame
 * aging counter C_TX_AGED.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_FRM_AGING . AGE_TX_ENA
 */
#define  VTSS_F_SYS_SYSTEM_FRM_AGING_AGE_TX_ENA  VTSS_BIT(20)

/** 
 * \brief
 * Frames are aged and removed from the queue system when the frame's age
 * timer becomes two. The frame age timer is increased for all frames
 * whenever the configured time, MAX_AGE,  has passed. The unit is 6.5us.
 * Effectively, this means that a frame is aged when the frame has waited
 * in the queue system between one or two times the period specified by
 * MAX_AGE.
 * 
 * A value of zero disables frame aging. 

 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_FRM_AGING . MAX_AGE
 */
#define  VTSS_F_SYS_SYSTEM_FRM_AGING_MAX_AGE(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_SYS_SYSTEM_FRM_AGING_MAX_AGE     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_SYS_SYSTEM_FRM_AGING_MAX_AGE(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/** 
 * \brief Statistics configuration
 *
 * \details
 * Register: \a SYS:SYSTEM:STAT_CFG
 */
#define VTSS_SYS_SYSTEM_STAT_CFG             VTSS_IOREG(VTSS_TO_SYS,0x15e)

/** 
 * \brief
 * Set STAT_CLEAR_SHOT to clear counters in the counter group for the port
 * or service index selected by STAT_VIEW. Auto-cleared when complete
 * (1us). Multiple counter groups can be cleared at the same time by
 * setting multiple bits in STAT_CLEAR_SHOT.
 *
 * \details 
 * Bit 0: Group 0 - Rx counters.
 * Bit 1: Group 1 - Tx counters.
 * Bit 2: Group 2 - Drop counters.
 * Bit 3: Group 3 - Ingress service counters.
 * Bit 4: Group 4 - Egress service counters.
 *
 * Field: ::VTSS_SYS_SYSTEM_STAT_CFG . STAT_CLEAR_SHOT
 */
#define  VTSS_F_SYS_SYSTEM_STAT_CFG_STAT_CLEAR_SHOT(x)  VTSS_ENCODE_BITFIELD(x,10,5)
#define  VTSS_M_SYS_SYSTEM_STAT_CFG_STAT_CLEAR_SHOT     VTSS_ENCODE_BITMASK(10,5)
#define  VTSS_X_SYS_SYSTEM_STAT_CFG_STAT_CLEAR_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,10,5)

/** 
 * \brief
 * Selects the subset of counters accessible through the SYS:STAT:CNT
 * register.
 * For groups 0-2, STAT_VIEW defines the port to read counters for.
 * For groups 3-4, STAT_VIEW defines the service index to read counters
 * for.

 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_STAT_CFG . STAT_VIEW
 */
#define  VTSS_F_SYS_SYSTEM_STAT_CFG_STAT_VIEW(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_SYS_SYSTEM_STAT_CFG_STAT_VIEW     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_SYS_SYSTEM_STAT_CFG_STAT_VIEW(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Various status info per switch port
 *
 * \details
 * Register: \a SYS:SYSTEM:SW_STATUS
 *
 * @param ri Replicator: x_SPORT_CNT (??), 0-11
 */
#define VTSS_SYS_SYSTEM_SW_STATUS(ri)        VTSS_IOREG(VTSS_TO_SYS,0x15f + (ri))

/** 
 * \brief
 * Status bit indicating whether the switch core is instructing the MAC to
 * pause the ingress port.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_SW_STATUS . PORT_RX_PAUSED
 */
#define  VTSS_F_SYS_SYSTEM_SW_STATUS_PORT_RX_PAUSED  VTSS_BIT(0)


/** 
 * \brief Miscellaneous configuration
 *
 * \details
 * Register: \a SYS:SYSTEM:MISC_CFG
 */
#define VTSS_SYS_SYSTEM_MISC_CFG             VTSS_IOREG(VTSS_TO_SYS,0x16b)

/** 
 * \brief
 * Always clear reserved bytes field in PTP PDUs when leaving switch after
 * two-step meassurement>
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_MISC_CFG . PTP_RSRV_CLR
 */
#define  VTSS_F_SYS_SYSTEM_MISC_CFG_PTP_RSRV_CLR  VTSS_BIT(1)

/** 
 * \brief
 * Dont fix negative rollover conditions in ingress unit doing ADDSUB
 * transfers.>
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_MISC_CFG . PTP_DIS_NEG_RO
 */
#define  VTSS_F_SYS_SYSTEM_MISC_CFG_PTP_DIS_NEG_RO  VTSS_BIT(0)


/** 
 * \brief Mac address to patch into frames transmitted
 *
 * \details
 * Register: \a SYS:SYSTEM:REW_MAC_HIGH_CFG
 *
 * @param ri Replicator: x_FPORT_CNT (??), 0-10
 */
#define VTSS_SYS_SYSTEM_REW_MAC_HIGH_CFG(ri)  VTSS_IOREG(VTSS_TO_SYS,0x16c + (ri))

/** 
 * \brief
 * Upper part of MAC address used when replacing source MAC address.
 * VCAP_IS2 action SMAC_REPLACE_ENA enables replacement of the source MAC
 * address
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_REW_MAC_HIGH_CFG . REW_MAC_HIGH
 */
#define  VTSS_F_SYS_SYSTEM_REW_MAC_HIGH_CFG_REW_MAC_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SYS_SYSTEM_REW_MAC_HIGH_CFG_REW_MAC_HIGH     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SYS_SYSTEM_REW_MAC_HIGH_CFG_REW_MAC_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Mac address to patch into frames transmitted
 *
 * \details
 * Register: \a SYS:SYSTEM:REW_MAC_LOW_CFG
 *
 * @param ri Replicator: x_FPORT_CNT (??), 0-10
 */
#define VTSS_SYS_SYSTEM_REW_MAC_LOW_CFG(ri)  VTSS_IOREG(VTSS_TO_SYS,0x177 + (ri))

/** 
 * \brief
 * Lower part of MAC address used when replacing source MAC address.
 * VCAP_IS2 action SMAC_REPLACE_ENA enables replacement of the source MAC
 * address
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_REW_MAC_LOW_CFG . REW_MAC_LOW
 */
#define  VTSS_F_SYS_SYSTEM_REW_MAC_LOW_CFG_REW_MAC_LOW(x)  (x)
#define  VTSS_M_SYS_SYSTEM_REW_MAC_LOW_CFG_REW_MAC_LOW     0xffffffff
#define  VTSS_X_SYS_SYSTEM_REW_MAC_LOW_CFG_REW_MAC_LOW(x)  (x)

/**
 * Register Group: \a SYS:COREMEM
 *
 * Access core memory
 */


/** 
 * \brief Address selection
 *
 * \details
 * Register: \a SYS:COREMEM:CM_ADDR
 */
#define VTSS_SYS_COREMEM_CM_ADDR             VTSS_IOREG(VTSS_TO_SYS,0x140)

/** 
 * \brief
 * Address selection within selected core memory (CMID register). Address
 * is automatically advanced at every data access.
 *
 * \details 
 * Field: ::VTSS_SYS_COREMEM_CM_ADDR . CM_ADDR
 */
#define  VTSS_F_SYS_COREMEM_CM_ADDR_CM_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,22)
#define  VTSS_M_SYS_COREMEM_CM_ADDR_CM_ADDR     VTSS_ENCODE_BITMASK(0,22)
#define  VTSS_X_SYS_COREMEM_CM_ADDR_CM_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,22)


/** 
 * \brief Data register for core memory access.
 *
 * \details
 * Register: \a SYS:COREMEM:CM_DATA
 */
#define VTSS_SYS_COREMEM_CM_DATA             VTSS_IOREG(VTSS_TO_SYS,0x141)

/** 
 * \brief
 * Data register for core memory access. Wider memories are big endian
 * mapped into the 32 inspection space.
 *
 * \details 
 * Field: ::VTSS_SYS_COREMEM_CM_DATA . CM_DATA
 */
#define  VTSS_F_SYS_COREMEM_CM_DATA_CM_DATA(x)  (x)
#define  VTSS_M_SYS_COREMEM_CM_DATA_CM_DATA     0xffffffff
#define  VTSS_X_SYS_COREMEM_CM_DATA_CM_DATA(x)  (x)

/**
 * Register Group: \a SYS:PAUSE_CFG
 *
 * Watermarks for egress queue system
 */


/** 
 * \brief Watermarks for flow control condition per switch port.
 *
 * \details
 * Register: \a SYS:PAUSE_CFG:PAUSE_CFG
 *
 * @param ri Replicator: x_SPORT_CNT (??), 0-11
 */
#define VTSS_SYS_PAUSE_CFG_PAUSE_CFG(ri)     VTSS_IOREG(VTSS_TO_SYS,0x182 + (ri))

/** 
 * \brief
 * Start pausing ingress stream when the amount of memory consumed by the
 * port exceeds this watermark. The TOTPAUSE condition must also be met.
 *
 * \details 
 * See RES_CFG
 *
 * Field: ::VTSS_SYS_PAUSE_CFG_PAUSE_CFG . PAUSE_START
 */
#define  VTSS_F_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_START(x)  VTSS_ENCODE_BITFIELD(x,10,9)
#define  VTSS_M_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_START     VTSS_ENCODE_BITMASK(10,9)
#define  VTSS_X_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_START(x)  VTSS_EXTRACT_BITFIELD(x,10,9)

/** 
 * \brief
 * Stop pausing ingress stream when the amount of memory consumed by the
 * port is below  this watermark.
 *
 * \details 
 * See RES_CFG.
 *
 * Field: ::VTSS_SYS_PAUSE_CFG_PAUSE_CFG . PAUSE_STOP
 */
#define  VTSS_F_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_STOP(x)  VTSS_ENCODE_BITFIELD(x,1,9)
#define  VTSS_M_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_STOP     VTSS_ENCODE_BITMASK(1,9)
#define  VTSS_X_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_STOP(x)  VTSS_EXTRACT_BITFIELD(x,1,9)

/** 
 * \brief
 * Enable pause feedback to the MAC, allowing transmission of pause frames
 * or HDX collisions to limit ingress data rate.
 *
 * \details 
 * Field: ::VTSS_SYS_PAUSE_CFG_PAUSE_CFG . PAUSE_ENA
 */
#define  VTSS_F_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_ENA  VTSS_BIT(0)


/** 
 * \brief Configure total memory pause condition
 *
 * \details
 * Register: \a SYS:PAUSE_CFG:PAUSE_TOT_CFG
 */
#define VTSS_SYS_PAUSE_CFG_PAUSE_TOT_CFG     VTSS_IOREG(VTSS_TO_SYS,0x18e)

/** 
 * \brief
 * Assert TOTPAUSE condition when total memory allocation is above this
 * watermark.
 *
 * \details 
 * See RES_CFG
 *
 * Field: ::VTSS_SYS_PAUSE_CFG_PAUSE_TOT_CFG . PAUSE_TOT_START
 */
#define  VTSS_F_SYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_START(x)  VTSS_ENCODE_BITFIELD(x,9,9)
#define  VTSS_M_SYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_START     VTSS_ENCODE_BITMASK(9,9)
#define  VTSS_X_SYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_START(x)  VTSS_EXTRACT_BITFIELD(x,9,9)

/** 
 * \brief
 * Deassert TOTPAUSE condition when total memory allocation is below this
 * watermark.
 *
 * \details 
 * See RES_CFG
 *
 * Field: ::VTSS_SYS_PAUSE_CFG_PAUSE_TOT_CFG . PAUSE_TOT_STOP
 */
#define  VTSS_F_SYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_STOP(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_SYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_STOP     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_SYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_STOP(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/** 
 * \brief Tail dropping level
 *
 * \details
 * Register: \a SYS:PAUSE_CFG:ATOP
 *
 * @param ri Replicator: x_SPORT_CNT (??), 0-11
 */
#define VTSS_SYS_PAUSE_CFG_ATOP(ri)          VTSS_IOREG(VTSS_TO_SYS,0x18f + (ri))

/** 
 * \brief
 * When a source port consumes more than this level in the packet memory,
 * frames are tail dropped, unconditionally of destination. 
 *
 * \details 
 * See RES_CFG
 *
 * Field: ::VTSS_SYS_PAUSE_CFG_ATOP . ATOP
 */
#define  VTSS_F_SYS_PAUSE_CFG_ATOP_ATOP(x)    VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_SYS_PAUSE_CFG_ATOP_ATOP       VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_SYS_PAUSE_CFG_ATOP_ATOP(x)    VTSS_EXTRACT_BITFIELD(x,0,9)


/** 
 * \brief Total raw memory use before tail dropping is activated
 *
 * \details
 * Register: \a SYS:PAUSE_CFG:ATOP_TOT_CFG
 */
#define VTSS_SYS_PAUSE_CFG_ATOP_TOT_CFG      VTSS_IOREG(VTSS_TO_SYS,0x19b)

/** 
 * \brief
 * Tail dropping is activate on a port when the port use has exceeded the
 * ATOP watermark for the port, and the total memory use has exceeded this
 * watermark.
 *
 * \details 
 * See RES_CFG
 *
 * Field: ::VTSS_SYS_PAUSE_CFG_ATOP_TOT_CFG . ATOP_TOT
 */
#define  VTSS_F_SYS_PAUSE_CFG_ATOP_TOT_CFG_ATOP_TOT(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_SYS_PAUSE_CFG_ATOP_TOT_CFG_ATOP_TOT     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_SYS_PAUSE_CFG_ATOP_TOT_CFG_ATOP_TOT(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/** 
 * \brief MAC Flow Control Configuration Register
 *
 * \details
 * Register: \a SYS:PAUSE_CFG:MAC_FC_CFG
 *
 * @param ri Replicator: x_FPORT_CNT (??), 0-10
 */
#define VTSS_SYS_PAUSE_CFG_MAC_FC_CFG(ri)    VTSS_IOREG(VTSS_TO_SYS,0x19c + (ri))

/** 
 * \brief
 * Configures the link speed. This is used to evaluate the time
 * specification in incoming pause frames.
 *
 * \details 
 * 0: 2500 Mbps
 * 1: 1000 Mbps
 * 2: 100 Mbps
 * 3: 10 Mbps
 *
 * Field: ::VTSS_SYS_PAUSE_CFG_MAC_FC_CFG . FC_LINK_SPEED
 */
#define  VTSS_F_SYS_PAUSE_CFG_MAC_FC_CFG_FC_LINK_SPEED(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_SYS_PAUSE_CFG_MAC_FC_CFG_FC_LINK_SPEED     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_SYS_PAUSE_CFG_MAC_FC_CFG_FC_LINK_SPEED(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/** 
 * \brief
 * Accepted reaction time for link partner after the port has transmitted a
 * pause frame. Frames starting after this latency are aborted. Unit is 64
 * byte times.
 *
 * \details 
 * Field: ::VTSS_SYS_PAUSE_CFG_MAC_FC_CFG . FC_LATENCY_CFG
 */
#define  VTSS_F_SYS_PAUSE_CFG_MAC_FC_CFG_FC_LATENCY_CFG(x)  VTSS_ENCODE_BITFIELD(x,20,6)
#define  VTSS_M_SYS_PAUSE_CFG_MAC_FC_CFG_FC_LATENCY_CFG     VTSS_ENCODE_BITMASK(20,6)
#define  VTSS_X_SYS_PAUSE_CFG_MAC_FC_CFG_FC_LATENCY_CFG(x)  VTSS_EXTRACT_BITFIELD(x,20,6)

/** 
 * \brief
 * If set, a zero-delay pause frame is transmitted when flow control is
 * deasserted.
 *
 * \details 
 * '0': Don't send zero pause frame.
 * '1': Send zero pause frame.
 *
 * Field: ::VTSS_SYS_PAUSE_CFG_MAC_FC_CFG . ZERO_PAUSE_ENA
 */
#define  VTSS_F_SYS_PAUSE_CFG_MAC_FC_CFG_ZERO_PAUSE_ENA  VTSS_BIT(18)

/** 
 * \brief
 * When set the MAC will send pause control frames in the Tx direction.
 *
 * \details 
 * '0': Don't send pause control frames
 * '1': Send pause control frames
 *
 * Field: ::VTSS_SYS_PAUSE_CFG_MAC_FC_CFG . TX_FC_ENA
 */
#define  VTSS_F_SYS_PAUSE_CFG_MAC_FC_CFG_TX_FC_ENA  VTSS_BIT(17)

/** 
 * \brief
 * When set the MAC obeys received pause control frames
 *
 * \details 
 * '0': Don't obey received pause control frames
 * '1': Obey received pause control frames.
 *
 * Field: ::VTSS_SYS_PAUSE_CFG_MAC_FC_CFG . RX_FC_ENA
 */
#define  VTSS_F_SYS_PAUSE_CFG_MAC_FC_CFG_RX_FC_ENA  VTSS_BIT(16)

/** 
 * \brief
 * Pause timer value inserted in generated pause frames.
 *
 * \details 
 * 0: Insert timer value 0 in TX pause frame.
 * ...
 * N: Insert timer value N in TX pause frame.
 *
 * Field: ::VTSS_SYS_PAUSE_CFG_MAC_FC_CFG . PAUSE_VAL_CFG
 */
#define  VTSS_F_SYS_PAUSE_CFG_MAC_FC_CFG_PAUSE_VAL_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SYS_PAUSE_CFG_MAC_FC_CFG_PAUSE_VAL_CFG     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SYS_PAUSE_CFG_MAC_FC_CFG_PAUSE_VAL_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a SYS:MMGT
 *
 * Memory manager status
 */


/** 
 * \brief Packet memory status
 *
 * \details
 * Register: \a SYS:MMGT:MMGT
 */
#define VTSS_SYS_MMGT_MMGT                   VTSS_IOREG(VTSS_TO_SYS,0x1a7)

/** 
 * \brief
 * Number of quad frames awaiting releasing.
 *
 * \details 
 * Field: ::VTSS_SYS_MMGT_MMGT . RELCNT
 */
#define  VTSS_F_SYS_MMGT_MMGT_RELCNT(x)       VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SYS_MMGT_MMGT_RELCNT          VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SYS_MMGT_MMGT_RELCNT(x)       VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Number of 192-byte free memory words.
 *
 * \details 
 * Field: ::VTSS_SYS_MMGT_MMGT . FREECNT
 */
#define  VTSS_F_SYS_MMGT_MMGT_FREECNT(x)      VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SYS_MMGT_MMGT_FREECNT         VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SYS_MMGT_MMGT_FREECNT(x)      VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Packet Memory Status
 *
 * \details
 * Register: \a SYS:MMGT:MMGT_FAST
 */
#define VTSS_SYS_MMGT_MMGT_FAST              VTSS_IOREG(VTSS_TO_SYS,0x1a8)

/** 
 * \brief
 * Number of words in the fast pool

 *
 * \details 
 * Field: ::VTSS_SYS_MMGT_MMGT_FAST . FREEVLD
 */
#define  VTSS_F_SYS_MMGT_MMGT_FAST_FREEVLD(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SYS_MMGT_MMGT_FAST_FREEVLD     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SYS_MMGT_MMGT_FAST_FREEVLD(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Number of frames awaiting release in the fast pool
 *
 * \details 
 * Field: ::VTSS_SYS_MMGT_MMGT_FAST . RELVLD
 */
#define  VTSS_F_SYS_MMGT_MMGT_FAST_RELVLD(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SYS_MMGT_MMGT_FAST_RELVLD     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SYS_MMGT_MMGT_FAST_RELVLD(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a SYS:MISC
 *
 * Miscellaneous
 */


/** 
 * \brief Device I/O events
 *
 * \details
 * Register: \a SYS:MISC:EVENTS_DIF
 *
 * @param ri Replicator: x_TAXI_CNT (??), 0-3
 */
#define VTSS_SYS_MISC_EVENTS_DIF(ri)         VTSS_IOREG(VTSS_TO_SYS,0x1a9 + (ri))

/** 
 * \brief
 * 0: Injection error (prefix)
 * 1: Very short frame received after very short IFG
 * 2: Too short MPLS frames seen
 *
 * \details 
 * Field: ::VTSS_SYS_MISC_EVENTS_DIF . EV_DRX
 */
#define  VTSS_F_SYS_MISC_EVENTS_DIF_EV_DRX(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_SYS_MISC_EVENTS_DIF_EV_DRX     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_SYS_MISC_EVENTS_DIF_EV_DRX(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * Look in the RTL!
 *
 * \details 
 * Field: ::VTSS_SYS_MISC_EVENTS_DIF . EV_DTX
 */
#define  VTSS_F_SYS_MISC_EVENTS_DIF_EV_DTX(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SYS_MISC_EVENTS_DIF_EV_DTX     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SYS_MISC_EVENTS_DIF_EV_DTX(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Core events
 *
 * \details
 * Core events.
 *
 * Register: \a SYS:MISC:EVENTS_CORE
 */
#define VTSS_SYS_MISC_EVENTS_CORE            VTSS_IOREG(VTSS_TO_SYS,0x1ad)

/** 
 * \brief
 * Look in the RTL!
 *
 * \details 
 * Field: ::VTSS_SYS_MISC_EVENTS_CORE . EV_FWR
 */
#define  VTSS_F_SYS_MISC_EVENTS_CORE_EV_FWR   VTSS_BIT(2)

/** 
 * \brief
 * Look in the RTL!
 *
 * \details 
 * Field: ::VTSS_SYS_MISC_EVENTS_CORE . EV_ANA
 */
#define  VTSS_F_SYS_MISC_EVENTS_CORE_EV_ANA(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SYS_MISC_EVENTS_CORE_EV_ANA     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SYS_MISC_EVENTS_CORE_EV_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a SYS:STAT
 *
 * Frame statistics
 */


/** 
 * \brief Counter values
 *
 * \details
 * Register: \a SYS:STAT:CNT
 *
 * @param gi Replicator: x_STAT_CNT (??), 0-319
 */
#define VTSS_SYS_STAT_CNT(gi)                VTSS_IOREG_IX(VTSS_TO_SYS,0x0,gi,1,0,0)

/** 
 * \brief
 * Counter values.
 * 
 * The counters are layed in five counter groups:
 * Group 0: 0-63: Receive counters for port specified in
 * STAT_CFG.STAT_VIEW.
 * Group 1: 64-127: Transmit counters for port specified in
 * STAT_CFG.STAT_VIEW.
 * Group 2: 128-191: Drop counters for port specified in
 * STAT_CFG.STAT_VIEW.
 * Group 3: 192-255: Ingress Service counters for ingress service point
 * specified in STAT_CFG.STAT_VIEW.
 * Group 4: 256-319: Egress Service counters for egress service point
 * specified in STAT_CFG.STAT_VIEW.
 * 
 * QSYS::STAT_CNT_CFG and ANA::AGENCTRL control whether bytes or frames are
 * counted for specific counters. Counters are cleared through
 * STAT_CFG.STAT_CLEAR_SHOT.
 *
 * \details 
 * Field: ::VTSS_SYS_STAT_CNT . CNT
 */
#define  VTSS_F_SYS_STAT_CNT_CNT(x)           (x)
#define  VTSS_M_SYS_STAT_CNT_CNT              0xffffffff
#define  VTSS_X_SYS_STAT_CNT_CNT(x)           (x)

/**
 * Register Group: \a SYS:PTP
 *
 * Precision Time Protocol configuration
 */


/** 
 * \brief Stored timestamp and timestamp queue status
 *
 * \details
 * Register: \a SYS:PTP:PTP_STATUS
 */
#define VTSS_SYS_PTP_PTP_STATUS              VTSS_IOREG(VTSS_TO_SYS,0x1ae)

/** 
 * \brief
 * If set, the timestamp is generated on request by the Microsemi OAM
 * engine.
 *
 * \details 
 * Field: ::VTSS_SYS_PTP_PTP_STATUS . PTP_TXSTAMP_OAM
 */
#define  VTSS_F_SYS_PTP_PTP_STATUS_PTP_TXSTAMP_OAM  VTSS_BIT(29)

/** 
 * \brief
 * If set, the timestamp queue has overflown implying a timestamp entry
 * could not be enqueued. The PTP_OVFL bit is not cleared until the
 * timestamp queue is completely empty.
 *
 * \details 
 * Field: ::VTSS_SYS_PTP_PTP_STATUS . PTP_OVFL
 */
#define  VTSS_F_SYS_PTP_PTP_STATUS_PTP_OVFL   VTSS_BIT(28)

/** 
 * \brief
 * A timestamp entry is ready for reading. PTP_MESS_ID, PTP_MESS_TXPORT,
 * and PTP_DELAY contain the data of the timestamp entry.
 *
 * \details 
 * Field: ::VTSS_SYS_PTP_PTP_STATUS . PTP_MESS_VLD
 */
#define  VTSS_F_SYS_PTP_PTP_STATUS_PTP_MESS_VLD  VTSS_BIT(27)

/** 
 * \brief
 * Timestamp identifier for head-of-line timestamp entry.
 *
 * \details 
 * Field: ::VTSS_SYS_PTP_PTP_STATUS . PTP_MESS_ID
 */
#define  VTSS_F_SYS_PTP_PTP_STATUS_PTP_MESS_ID(x)  VTSS_ENCODE_BITFIELD(x,21,6)
#define  VTSS_M_SYS_PTP_PTP_STATUS_PTP_MESS_ID     VTSS_ENCODE_BITMASK(21,6)
#define  VTSS_X_SYS_PTP_PTP_STATUS_PTP_MESS_ID(x)  VTSS_EXTRACT_BITFIELD(x,21,6)

/** 
 * \brief
 * The transmit port for the head-of-line timestamp entry.
 *
 * \details 
 * Field: ::VTSS_SYS_PTP_PTP_STATUS . PTP_MESS_TXPORT
 */
#define  VTSS_F_SYS_PTP_PTP_STATUS_PTP_MESS_TXPORT(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_SYS_PTP_PTP_STATUS_PTP_MESS_TXPORT     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_SYS_PTP_PTP_STATUS_PTP_MESS_TXPORT(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * Timestamp sequence identifier for head-of-line timestamp entry.
 *
 * \details 
 * Field: ::VTSS_SYS_PTP_PTP_STATUS . PTP_MESS_SEQ_ID
 */
#define  VTSS_F_SYS_PTP_PTP_STATUS_PTP_MESS_SEQ_ID(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SYS_PTP_PTP_STATUS_PTP_MESS_SEQ_ID     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SYS_PTP_PTP_STATUS_PTP_MESS_SEQ_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Timestamp value
 *
 * \details
 * Register: \a SYS:PTP:PTP_TXSTAMP
 */
#define VTSS_SYS_PTP_PTP_TXSTAMP             VTSS_IOREG(VTSS_TO_SYS,0x1af)

/** 
 * \brief
 * The timestamp value for the head-of-line timestamp entry. The timestamp
 * value is the frame's departure time plus
 * DEV:PORT_MODE:TX_PATH_DELAY.TX_PATH_DELAY. This is the LSB of the
 * TOD_SEC value at time of event.
 *
 * \details 
 * Field: ::VTSS_SYS_PTP_PTP_TXSTAMP . PTP_TXSTAMP_SEC
 */
#define  VTSS_F_SYS_PTP_PTP_TXSTAMP_PTP_TXSTAMP_SEC  VTSS_BIT(31)

/** 
 * \brief
 * The timestamp value for the head-of-line timestamp entry. The timestamp
 * value is the frame's departure time plus
 * DEV:PORT_MODE:TX_PATH_DELAY.TX_PATH_DELAY. Unit is ns.
 *
 * \details 
 * Field: ::VTSS_SYS_PTP_PTP_TXSTAMP . PTP_TXSTAMP
 */
#define  VTSS_F_SYS_PTP_PTP_TXSTAMP_PTP_TXSTAMP(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_SYS_PTP_PTP_TXSTAMP_PTP_TXSTAMP     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_SYS_PTP_PTP_TXSTAMP_PTP_TXSTAMP(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/** 
 * \brief Advancing the timestamp queue
 *
 * \details
 * Register: \a SYS:PTP:PTP_NXT
 */
#define VTSS_SYS_PTP_PTP_NXT                 VTSS_IOREG(VTSS_TO_SYS,0x1b0)

/** 
 * \brief
 * Advance to the next timestamp entry. Registers PTP_STATUS and PTP_DELAY
 * points to the next entry. 
 *
 * \details 
 * Field: ::VTSS_SYS_PTP_PTP_NXT . PTP_NXT
 */
#define  VTSS_F_SYS_PTP_PTP_NXT_PTP_NXT       VTSS_BIT(0)


/** 
 * \brief System configuration of PTP
 *
 * \details
 * Register: \a SYS:PTP:PTP_CFG
 */
#define VTSS_SYS_PTP_PTP_CFG                 VTSS_IOREG(VTSS_TO_SYS,0x1b1)

/** 
 * \brief
 * Determines how many LSbits from the timestamp value are used by the
 * timestamp transfer function.
 *
 * \details 
 * Field: ::VTSS_SYS_PTP_PTP_CFG . PTP_STAMP_WID
 */
#define  VTSS_F_SYS_PTP_PTP_CFG_PTP_STAMP_WID(x)  VTSS_ENCODE_BITFIELD(x,2,6)
#define  VTSS_M_SYS_PTP_PTP_CFG_PTP_STAMP_WID     VTSS_ENCODE_BITMASK(2,6)
#define  VTSS_X_SYS_PTP_PTP_CFG_PTP_STAMP_WID(x)  VTSS_EXTRACT_BITFIELD(x,2,6)

/** 
 * \brief
 * Configures how rollover protection is done when doing add/subtract
 * transfer.
 *
 * \details 
 * 0: The four LSbits of CF sub-nano is filled out with the MSbits of the
 * timestamp.
 * 1: The LSbit of the CF sub-nano field is set to the MSbit of the
 * timestamp.
 * 2: The CF bit 62 is set to the MSbit of the timestamp.
 * 3: Reserved.
 *
 * Field: ::VTSS_SYS_PTP_PTP_CFG . PTP_CF_ROLL_MODE
 */
#define  VTSS_F_SYS_PTP_PTP_CFG_PTP_CF_ROLL_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SYS_PTP_PTP_CFG_PTP_CF_ROLL_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SYS_PTP_PTP_CFG_PTP_CF_ROLL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


#endif /* _VTSS_OCELOT_REGS_SYS_H_ */
