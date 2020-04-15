#ifndef _VTSS_JAGUAR2C_REGS_LRN_H_
#define _VTSS_JAGUAR2C_REGS_LRN_H_

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

#include "vtss_jaguar2c_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a LRN
 *
 * Learn block
 *
 ***********************************************************************/

/**
 * Register Group: \a LRN:COMMON
 *
 * Common configurations and status for all ports
 */


/** 
 * \brief MAC Table Control
 *
 * \details
 * Configures command and access parameters when accessing the MAC table.
 *
 * Register: \a LRN:COMMON:COMMON_ACCESS_CTRL
 */
#define VTSS_LRN_COMMON_COMMON_ACCESS_CTRL   VTSS_IOREG(VTSS_TO_LRN,0x0)

/** 
 * \brief
 * Configures the MAC table bucket or column index that holds the MAC_ENTRY
 * that is accessed when CPU_ACCESS_CMD command is READ or WRITE.

 *
 * \details 
 * 0: Column (bucket) 0
 * 1: Column (bucket) 1
 * ...
 * n: Column (bucket) n.
 *
 * Field: ::VTSS_LRN_COMMON_COMMON_ACCESS_CTRL . CPU_ACCESS_DIRECT_COL
 */
#define  VTSS_F_LRN_COMMON_COMMON_ACCESS_CTRL_CPU_ACCESS_DIRECT_COL(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_LRN_COMMON_COMMON_ACCESS_CTRL_CPU_ACCESS_DIRECT_COL     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_LRN_COMMON_COMMON_ACCESS_CTRL_CPU_ACCESS_DIRECT_COL(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/** 
 * \brief
 * Configures the MAC table type that holds the MAC_ENTRY that is accessed
 * when CPU_ACCESS_CMD command is READ or WRITE.
 * 
 * Configures the MAC table starting type when CPU_ACCESS_CMD command is
 * FIND NEXT. If the Command succeeds in finding a matching entry this
 * field is updated with the type for the (last) matching entry. 
 *
 * \details 
 * 0: MAC table
 * 1: MAC CAM (CPU_ACCESS_DIRECT_ROW is not used)
 *
 * Field: ::VTSS_LRN_COMMON_COMMON_ACCESS_CTRL . CPU_ACCESS_DIRECT_TYPE
 */
#define  VTSS_F_LRN_COMMON_COMMON_ACCESS_CTRL_CPU_ACCESS_DIRECT_TYPE(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_LRN_COMMON_COMMON_ACCESS_CTRL_CPU_ACCESS_DIRECT_TYPE  VTSS_BIT(19)
#define  VTSS_X_LRN_COMMON_COMMON_ACCESS_CTRL_CPU_ACCESS_DIRECT_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * Configures the MAC table row index that holds the MAC_ENTRY that is
 * accessed when CPU_ACCESS_CMD command is READ or WRITE.
 * 
 * Configures the MAC table starting row index when CPU_ACCESS_CMD command
 * is FIND NEXT. If the Command succeeds in finding a matching entry this
 * field is updated with the row index for the (last) matching entry. 
 *
 * \details 
 * 0: Row 0
 * 1: Row 1
 * ...
 * n: Row n.
 *
 * Field: ::VTSS_LRN_COMMON_COMMON_ACCESS_CTRL . CPU_ACCESS_DIRECT_ROW
 */
#define  VTSS_F_LRN_COMMON_COMMON_ACCESS_CTRL_CPU_ACCESS_DIRECT_ROW(x)  VTSS_ENCODE_BITFIELD(x,5,14)
#define  VTSS_M_LRN_COMMON_COMMON_ACCESS_CTRL_CPU_ACCESS_DIRECT_ROW     VTSS_ENCODE_BITMASK(5,14)
#define  VTSS_X_LRN_COMMON_COMMON_ACCESS_CTRL_CPU_ACCESS_DIRECT_ROW(x)  VTSS_EXTRACT_BITFIELD(x,5,14)

/** 
 * \brief
 * Configures the MAC table access command:
 * 
 * LEARN, UNLEARN, and LOOKUP Command accesses a MAC_ENTRY at the
 * HASH(VID/FID,MAC) index. MAC and FID/VID must to be written to the
 * respective bitgroups in registers MAC_ACCESS_CFG_[0|1|2].
 * 
 * READ and WRITE Command accesses a MAC_ENTRY at the index specified by
 * means of CPU_ACCESS_DIRECT_ROW,  CPU_ACCESS_DIRECT_COL and
 * CPU_ACCESS_DIRECT_TYPE fields.
 * 
 * SCAN Command access traverses the entire MAC table and handle all found
 * entries depending on configuration and filter settings. If any set of
 * filters is enabled then only entries matching the enabled filters are
 * affected / found. Refer to description of bitgroups found in
 * LRN::SCAN_NEXT_CFG-	Note that it is possible to configure the scan to
 * FIND ALL or FIND first using
 * LRN::SCAN_NEXT_CFG.SCAN_NEXT_UNTIL_FOUND_ENA.
 * 
 * FIND SMALLEST Command traverses the entire table and returns the
 * MAC_ENTRY with the smallest FID/VID,MAC which is larger than a
 * configured starting FID/VID,MAC value (configured in
 * MAC_ACCESS_CFG_[0|1|2].). FID/VID take precedence over MAC.
 * 
 * CLEAR ALL Command traverses the entire table and resets all entries.
 *
 * \details 
 * 0: LEARN
 * 1: UNLEARN
 * 2: LOOKUP
 * 3: READ
 * 4: WRITE
 * 5: SCAN (AGE or FIND NEXT)
 * 6: FIND SMALLEST
 * 7: CLEAR ALL
 *
 * Field: ::VTSS_LRN_COMMON_COMMON_ACCESS_CTRL . CPU_ACCESS_CMD
 */
#define  VTSS_F_LRN_COMMON_COMMON_ACCESS_CTRL_CPU_ACCESS_CMD(x)  VTSS_ENCODE_BITFIELD(x,1,4)
#define  VTSS_M_LRN_COMMON_COMMON_ACCESS_CTRL_CPU_ACCESS_CMD     VTSS_ENCODE_BITMASK(1,4)
#define  VTSS_X_LRN_COMMON_COMMON_ACCESS_CTRL_CPU_ACCESS_CMD(x)  VTSS_EXTRACT_BITFIELD(x,1,4)

/** 
 * \brief
 * Perform the access command specified by CPU_ACCESS_CMD. Cleared when the
 * access completes.
 * 
 * Interrupt upon access completion can be configured using: 
 * ANA_L2::INTR_ENA.LRN_ACCESS_COMPLETE_INTR_ENA

 *
 * \details 
 * 0: Idle
 * 1: Initiate CPU ACCESS
 * 
 * The bit is cleared upon completion
 *
 * Field: ::VTSS_LRN_COMMON_COMMON_ACCESS_CTRL . MAC_TABLE_ACCESS_SHOT
 */
#define  VTSS_F_LRN_COMMON_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_LRN_COMMON_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT  VTSS_BIT(0)
#define  VTSS_X_LRN_COMMON_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief MAC entry Data 0
 *
 * \details
 * Configures MAC address and FID/VID when accessing the MAC table.
 *
 * Register: \a LRN:COMMON:MAC_ACCESS_CFG_0
 */
#define VTSS_LRN_COMMON_MAC_ACCESS_CFG_0     VTSS_IOREG(VTSS_TO_LRN,0x1)

/** 
 * \brief
 * Configures FID/VID for the MAC_ENTRY. This values is a FID for unicast
 * entries and CL-VID for multicast entries.  
 * 
 * Can also be used as FID/VID filter value during SCAN or FIND SMALLEST
 * Command.
 *
 * \details 
 * Field: ::VTSS_LRN_COMMON_MAC_ACCESS_CFG_0 . MAC_ENTRY_FID
 */
#define  VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_0_MAC_ENTRY_FID(x)  VTSS_ENCODE_BITFIELD(x,16,13)
#define  VTSS_M_LRN_COMMON_MAC_ACCESS_CFG_0_MAC_ENTRY_FID     VTSS_ENCODE_BITMASK(16,13)
#define  VTSS_X_LRN_COMMON_MAC_ACCESS_CFG_0_MAC_ENTRY_FID(x)  VTSS_EXTRACT_BITFIELD(x,16,13)

/** 
 * \brief
 * Configures 16 MSB bits of the MAC address for the MAC_ENTRY.
 * 
 * Used as starting MAC value during FIND SMALLEST Command.
 *
 * \details 
 * Upper 16 bits of MAC address.
 *
 * Field: ::VTSS_LRN_COMMON_MAC_ACCESS_CFG_0 . MAC_ENTRY_MAC_MSB
 */
#define  VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_0_MAC_ENTRY_MAC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LRN_COMMON_MAC_ACCESS_CFG_0_MAC_ENTRY_MAC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LRN_COMMON_MAC_ACCESS_CFG_0_MAC_ENTRY_MAC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief MAC entry Data 1
 *
 * \details
 * Configures MAC address when accessing the MAC table.
 *
 * Register: \a LRN:COMMON:MAC_ACCESS_CFG_1
 */
#define VTSS_LRN_COMMON_MAC_ACCESS_CFG_1     VTSS_IOREG(VTSS_TO_LRN,0x2)

/** 
 * \brief
 * Configures 32 LSB bits of the MAC address for the MAC_ENTRY.
 * 
 * Used as starting MAC value during FIND SMALLEST Command.
 *
 * \details 
 * 0xXXXXXXXX: Lower 32 bits of MAC address.
 *
 * Field: ::VTSS_LRN_COMMON_MAC_ACCESS_CFG_1 . MAC_ENTRY_MAC_LSB
 */
#define  VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_1_MAC_ENTRY_MAC_LSB(x)  (x)
#define  VTSS_M_LRN_COMMON_MAC_ACCESS_CFG_1_MAC_ENTRY_MAC_LSB     0xffffffff
#define  VTSS_X_LRN_COMMON_MAC_ACCESS_CFG_1_MAC_ENTRY_MAC_LSB(x)  (x)


/** 
 * \brief MAC entry Data 2
 *
 * \details
 * Configures warious MAC_ENTRY parameters when accessing the MAC table
 *
 * Register: \a LRN:COMMON:MAC_ACCESS_CFG_2
 */
#define VTSS_LRN_COMMON_MAC_ACCESS_CFG_2     VTSS_IOREG(VTSS_TO_LRN,0x3)

/** 
 * \brief
 * Configures MAC_ENTRY SRC_KILL_FWD flag. Used to discard forwarding of
 * frames from this source.
 *
 * \details 
 * 0: Disable
 * 1: Enable (Frames with this entry MAC address as SMAC are killed)
 *
 * Field: ::VTSS_LRN_COMMON_MAC_ACCESS_CFG_2 . MAC_ENTRY_SRC_KILL_FWD
 */
#define  VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_SRC_KILL_FWD(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_SRC_KILL_FWD  VTSS_BIT(28)
#define  VTSS_X_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_SRC_KILL_FWD(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/** 
 * \brief
 * Configures MAC_ENTRY NXT_LRN_ALL flag. This is used to ensure MAC
 * entries are learned consistend in a multi device configuration.
 * 
 * Cleared by HW when a frame is received for a (IFID, SMAC) matching this
 * entry.
 *
 * \details 
 * 0:  Disabled
 * 1:  Next learn all.
 *
 * Field: ::VTSS_LRN_COMMON_MAC_ACCESS_CFG_2 . MAC_ENTRY_NXT_LRN_ALL
 */
#define  VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_NXT_LRN_ALL(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_NXT_LRN_ALL  VTSS_BIT(27)
#define  VTSS_X_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_NXT_LRN_ALL(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/** 
 * \brief
 * Configures MAC_ENTRY CPU Queue number if MAC_ENTRY_CPU_COPY is set.
 *
 * \details 
 * Field: ::VTSS_LRN_COMMON_MAC_ACCESS_CFG_2 . MAC_ENTRY_CPU_QU
 */
#define  VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_CPU_QU     VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,24,3)

/** 
 * \brief
 * Configures MAC_ENTRY CPU copy flag. 
 * 
 * Used together with ANA_L2::FWD_CFG.CPU_DMAC_COPY_ENA to determine if a
 * CPU copy should be send when the entry found as forwarding entry.
 * 
 * Used together with ANA_L2::LRN_CFG.CPU_SMAC_COPY_ENA to determine if a
 * CPU copy should be send when the entry found as source entry.
 *
 * \details 
 * Field: ::VTSS_LRN_COMMON_MAC_ACCESS_CFG_2 . MAC_ENTRY_CPU_COPY
 */
#define  VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_CPU_COPY(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_CPU_COPY  VTSS_BIT(23)
#define  VTSS_X_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_CPU_COPY(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * Configures MAC_ENTRY VLAN ignore flag.  
 * 
 * Can be used to ignore VLAN mask or Source mask during forwarding based
 * on ANA_L2::FWD_CFG.FILTER_MODE_SEL. 
 *
 * \details 
 * 0: no effect
 *  
 * 1: VLAN mask or source mask is ignored.
 *
 * Field: ::VTSS_LRN_COMMON_MAC_ACCESS_CFG_2 . MAC_ENTRY_VLAN_IGNORE
 */
#define  VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_VLAN_IGNORE(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_VLAN_IGNORE  VTSS_BIT(22)
#define  VTSS_X_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_VLAN_IGNORE(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Configures the MAC_ENTRY mirror flag. 
 * 
 * Used to configure MAC entries that are candidates for mirroring. See:
 * ANA_AC:MIRROR_PROBE:PROBE_CFG.PROBE_MAC_MODE.
 *
 * \details 
 * Field: ::VTSS_LRN_COMMON_MAC_ACCESS_CFG_2 . MAC_ENTRY_MIRROR
 */
#define  VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_MIRROR(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_MIRROR  VTSS_BIT(21)
#define  VTSS_X_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_MIRROR(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * MAC_ENTRY AGE flag used to identify if a MAC_ENTRY is active of not.
 * 
 * Cleared by HW when a entry is used as source entry. Used to ensure that
 * entries associated with inactive stations can be located and discarded. 
 * 
 * The MAC table can be aged by HW either a CPU Scan command or through
 * Automatic ageing (LRN::AUTOAGE_CFG). 
 *
 * \details 
 * 0:  Not aged 
 * n:  Aged n times.
 *
 * Field: ::VTSS_LRN_COMMON_MAC_ACCESS_CFG_2 . MAC_ENTRY_AGE_FLAG
 */
#define  VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_AGE_FLAG(x)  VTSS_ENCODE_BITFIELD(x,19,2)
#define  VTSS_M_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_AGE_FLAG     VTSS_ENCODE_BITMASK(19,2)
#define  VTSS_X_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_AGE_FLAG(x)  VTSS_EXTRACT_BITFIELD(x,19,2)

/** 
 * \brief
 * MAC_ENTRY AGE Interval is used to select which age timer is associated
 * with the entry. 
 * 
 * The MAC table can be aged by HW either a CPU Scan command or through
 * Automatic ageing (LRN::AUTOAGE_CFG). 
 *
 * \details 
 * Field: ::VTSS_LRN_COMMON_MAC_ACCESS_CFG_2 . MAC_ENTRY_AGE_INTERVAL
 */
#define  VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_AGE_INTERVAL(x)  VTSS_ENCODE_BITFIELD(x,17,2)
#define  VTSS_M_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_AGE_INTERVAL     VTSS_ENCODE_BITMASK(17,2)
#define  VTSS_X_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_AGE_INTERVAL(x)  VTSS_EXTRACT_BITFIELD(x,17,2)

/** 
 * \brief
 * Configures the MAC_ENTRY locked flag. Used to install static MAC table
 * entries that can not be removed by learning and ageing.
 *
 * \details 
 * 0: Not locked
 * 1: Locked.
 *
 * Field: ::VTSS_LRN_COMMON_MAC_ACCESS_CFG_2 . MAC_ENTRY_LOCKED
 */
#define  VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_LOCKED(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_LOCKED  VTSS_BIT(16)
#define  VTSS_X_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_LOCKED(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Configures the MAC_ENTRY valid flag. Used to indicate that this entry is
 * active. This bit can be cleared for non locked entries by auto learning
 * or through the CPU_ACCESS_CMD UNLEARN command.
 *
 * \details 
 * 0: Invalid
 * 1: Valid.
 *
 * Field: ::VTSS_LRN_COMMON_MAC_ACCESS_CFG_2 . MAC_ENTRY_VLD
 */
#define  VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_VLD(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_VLD  VTSS_BIT(15)
#define  VTSS_X_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_VLD(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Configures MAC_ENTRY address type. 
 * 
 * Can be used as filter value during SCAN or FIND SMALLEST Command.
 *
 * \details 
 * 0: UPSID_PN 
 * 1: UPSID_CPU_OR_INT
 * 2: GLAG
 * 3: MC_IDX

 *
 * Field: ::VTSS_LRN_COMMON_MAC_ACCESS_CFG_2 . MAC_ENTRY_ADDR_TYPE
 */
#define  VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR_TYPE(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR_TYPE     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/** 
 * \brief
 * Configures the ADDRESS for the MAC_ENTRY. Encoding of this field is
 * determined by MAC_ENTRY_ADDR_TYPE.
 * 
 * Can be used as filter value during SCAN or FIND SMALLEST Command.
 *
 * \details 
 * MAC_ENTRY_ADDR_TYPE= UPSID_PN:
 *   MAC_ENTRY_ADDR(9:5) = UPSID
 *   MAC_ENTRY_ADDR(4:0) = UPSPN
 *   Specifies unicast forwarding to port: UPSPN in device: UPSID.
 * 
 * MAC_ENTRY_ADDR_TYPE = UPSID_CPU_OR_INT:
 *   MAC_ENTRY_ADDR(9:5) = UPSID
 *   MAC_ENTRY_ADDR(3:0) = CPU queue number when MAC_ENTRY_ADDR(11) = 0
 *   MAC_ENTRY_ADDR(3:0) = Internal port number when MAC_ENTRY_ADDR(11) = 1
 *	  0xe: Internal port number (intpn_router)
 *	  0xf: Local lookup at destination upsid (ntpn_dlookup)
 * 
 * MAC_ENTRY_ADDR_TYPE = GLAG
 *   MAC_ENTRY_ADDR = GLAGID 
 *   Specifies unicast forwarding to the global aggregated port group:
 * GLAGID.
 * 
 * MAC_ENTRY_ADDR_TYPE = MC_IDX:
 *   MAC_ENTRY_ADDR = MC_IDX
 *   Specifies forwarding according to ANA_AC:PGID[32 + MC_IDX)
 *
 * Field: ::VTSS_LRN_COMMON_MAC_ACCESS_CFG_2 . MAC_ENTRY_ADDR
 */
#define  VTSS_F_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_LRN_COMMON_MAC_ACCESS_CFG_2_MAC_ENTRY_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Scan parameters
 *
 * \details
 * Configures various filters and associated actions when scanning the MAC
 * table through CPU Scan Command. 
 *
 * Register: \a LRN:COMMON:SCAN_NEXT_CFG
 */
#define VTSS_LRN_COMMON_SCAN_NEXT_CFG        VTSS_IOREG(VTSS_TO_LRN,0x4)

/** 
 * \brief
 * Controls update of MAC_ENTRY_AGE_FLAG for found entries.
 * 
 * Field is ignored if SCAN_NEXT_INC_AGE_BITS_ENA is set
 *
 * \details 
 * 0: No change to MAC_ENTRY_AGE_FLAG
 * 1: Clear MAC_ENTRY_AGE_FLAG
 * 2: Set MAC_ENTRY_AGE_FLAG
 * 3: MAC_ENTRY_AGE_FLAG
 * 4: MAC_ENTRY_AGE_FLAG
 *
 * Field: ::VTSS_LRN_COMMON_SCAN_NEXT_CFG . SCAN_AGE_FLAG_UPDATE_SEL
 */
#define  VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_SCAN_AGE_FLAG_UPDATE_SEL(x)  VTSS_ENCODE_BITFIELD(x,18,3)
#define  VTSS_M_LRN_COMMON_SCAN_NEXT_CFG_SCAN_AGE_FLAG_UPDATE_SEL     VTSS_ENCODE_BITMASK(18,3)
#define  VTSS_X_LRN_COMMON_SCAN_NEXT_CFG_SCAN_AGE_FLAG_UPDATE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,18,3)

/** 
 * \brief
 * Controls update of MAC_ENTRY_NXT_LRN_ALL for found entries.
 *
 * \details 
 * 0: No change to MAC_ENTRY_NXT_LRN_ALL
 * 1: Clear MAC_ENTRY_NXT_LRN_ALL
 * 2: Set MAC_ENTRY_NXT_LRN_ALL. 
 *
 * Field: ::VTSS_LRN_COMMON_SCAN_NEXT_CFG . SCAN_NXT_LRN_ALL_UPDATE_SEL
 */
#define  VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NXT_LRN_ALL_UPDATE_SEL(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NXT_LRN_ALL_UPDATE_SEL     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NXT_LRN_ALL_UPDATE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * Specify how MAC_ENTRY_AGE is matched during scan commands.
 *
 * \details 
 * 0: Ignore 
 * 1: Find entries with MAC_ENTRY_AGE equal to
 * MAC_ACCESS_CFG_2.MAC_ENTRY_AGE_FLAG or larger
 * 2: Find entries with MAC_ENTRY_AGE equal to
 * MAC_ACCESS_CFG_2.MAC_ENTRY_AGE_FLAG or smaller
 * 3: Find entries with MAC_ENTRY_AGE equal to
 * MAC_ACCESS_CFG_2.MAC_ENTRY_AGE_FLAG.
 *
 * Field: ::VTSS_LRN_COMMON_SCAN_NEXT_CFG . SCAN_AGE_FILTER_SEL
 */
#define  VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_SCAN_AGE_FILTER_SEL(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_LRN_COMMON_SCAN_NEXT_CFG_SCAN_AGE_FILTER_SEL     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_LRN_COMMON_SCAN_NEXT_CFG_SCAN_AGE_FILTER_SEL(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Controls update of MAC_ENTRY_ADDR_TYPE and MAC_ENTRY_ADDR for entries
 * matched during a SCAN command. 
 * (Will only have effect if SCAN_NEXT_UNTIL_FOUND_ENA is disabled).
 * 
 * Allows all MAC addresses learned on a specific port to be moved to
 * another port. Refer also to PORT_MOVE_NEW_ADDR and SCAN_ENTRY_ADDR_MASK
 *
 * \details 
 * 0: MAC_ENTRY_ADDR and MAC_ENTRY_ADDR_TYPE will be kept unaffected.  
 * 1: Entries matching the condition will have MAC_ENTRY_ADDR and
 * MAC_ENTRY_ADDR_TYPE updated.
 *
 * Field: ::VTSS_LRN_COMMON_SCAN_NEXT_CFG . SCAN_NEXT_MOVE_FOUND_ENA
 */
#define  VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_MOVE_FOUND_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_MOVE_FOUND_ENA  VTSS_BIT(13)
#define  VTSS_X_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_MOVE_FOUND_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Configures whether NXT_LRN_ALL values is don't care or entries with a
 * specific NXT_LRN_ALL/CCM_CHG value are found during FIND SMALLEST or
 * SCAN commands.
 *
 * \details 
 * 0: SCAN and FIND_SMALLEST commands don't care about
 * MAC_ENTRY_NXT_LRN_ALL.
 * 1: Enable filter. SCAN and FIND_SMALLEST commands will only search for
 * entries with NXT_LRN_ALL set according to MAC_ENTRY_NXT_LRN_ALL.

 *
 * Field: ::VTSS_LRN_COMMON_SCAN_NEXT_CFG . NXT_LRN_ALL_FILTER_ENA
 */
#define  VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_NXT_LRN_ALL_FILTER_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_LRN_COMMON_SCAN_NEXT_CFG_NXT_LRN_ALL_FILTER_ENA  VTSS_BIT(12)
#define  VTSS_X_LRN_COMMON_SCAN_NEXT_CFG_NXT_LRN_ALL_FILTER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Configures scanning of all port or only port not disabled in
 * ANA_L2::FILTER_OTHER_CTRL and ANA_L2::FILTER_LOCAL_CTRL.
 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_LRN_COMMON_SCAN_NEXT_CFG . SCAN_USE_PORT_FILTER_ENA
 */
#define  VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_SCAN_USE_PORT_FILTER_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_LRN_COMMON_SCAN_NEXT_CFG_SCAN_USE_PORT_FILTER_ENA  VTSS_BIT(11)
#define  VTSS_X_LRN_COMMON_SCAN_NEXT_CFG_SCAN_USE_PORT_FILTER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Controls whether scan removes entries matching the condition or not.
 * 
 * CPU Age scan:
 * if SCAN_NEXT_REMOVE_FOUND_ENA==1 and SCAN_NEXT_INC_AGE_BITS_ENA == 1 and
 * SCAN_NEXT_AGED_ONLY_ENA==0 then non aged entries (MAC_ENTRY_AGE_FLAG
 * less than max configured through ANA_L2::LRN_CFG.AGE_SIZE) will be aged
 * (MAC_ENTRY_AGE_FLAG incremented) and aged entries  (MAC_ENTRY_AGE_FLAG
 * set to MAX) will be removed.
 * 
 * CPU cleanup scan:
 * if SCAN_NEXT_REMOVE_FOUND_ENA==1 and SCAN_NEXT_INC_AGE_BITS_ENA ==0 then
 * all entries matching the enabled filtering conditions will be removed.
 * 
 * (Will only have effect if SCAN_NEXT_UNTIL_FOUND_ENA is disabled).

 *
 * \details 
 * 0: No entries will be removed.
 * 1: Entries matching the condition will be removed (or MAC_ENTRY_AGE_FLAG
 * will be incremented based on SCAN_NEXT_INC_AGE_BITS_ENA)
 *
 * Field: ::VTSS_LRN_COMMON_SCAN_NEXT_CFG . SCAN_NEXT_REMOVE_FOUND_ENA
 */
#define  VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_REMOVE_FOUND_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_REMOVE_FOUND_ENA  VTSS_BIT(10)
#define  VTSS_X_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_REMOVE_FOUND_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Specify whether the scan stops at the next row which matches the
 * condition during scan commands.
 *
 * \details 
 * 0: SCAN command scans through the complete table. 
 * 1: Scan stops at the first row with one or more entries matching the
 * filter conditions.
 *
 * Field: ::VTSS_LRN_COMMON_SCAN_NEXT_CFG . SCAN_NEXT_UNTIL_FOUND_ENA
 */
#define  VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_UNTIL_FOUND_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_UNTIL_FOUND_ENA  VTSS_BIT(9)
#define  VTSS_X_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_UNTIL_FOUND_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Configures whether the MAC_ENTRY_AGE_FLAG will be incremented during
 * scan commands or not.
 *
 * \details 
 * 0: Find next will keep entries intact. 
 * 1: Find next will increment MAC_ENTRY_AGE_FLAG for entries matching the
 * filter conditions. Refer also to bitgroup SCAN_NEXT_REMOVE_FOUND_ENA
 *
 * Field: ::VTSS_LRN_COMMON_SCAN_NEXT_CFG . SCAN_NEXT_INC_AGE_BITS_ENA
 */
#define  VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_INC_AGE_BITS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_INC_AGE_BITS_ENA  VTSS_BIT(8)
#define  VTSS_X_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_INC_AGE_BITS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Specify whether AGE flags are ignored during scan commands.
 *
 * \details 
 * 0: Ignore the MAC_ENTRY_AGE_FLAG duting scan.
 * 1: Find only entries with MAC_ENTRY_AGE_FLAG set.
 *
 * Field: ::VTSS_LRN_COMMON_SCAN_NEXT_CFG . SCAN_NEXT_AGED_ONLY_ENA
 */
#define  VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_AGED_ONLY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_AGED_ONLY_ENA  VTSS_BIT(7)
#define  VTSS_X_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_AGED_ONLY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Configures whether locked entries are ignored during a FIND SMALLEST or
 * SCAN commands or not.
 *
 * \details 
 * 0: Consider only unlocked (entries with MAC_ENTRY_LOCKED cleared)
 * entries during FIND SMALLEST or SCAN commands.
 * 1: Ignore MAC_ENTRY_LOCKED flag during FIND SMALLEST or SCAN commands.
 *
 * Field: ::VTSS_LRN_COMMON_SCAN_NEXT_CFG . SCAN_NEXT_IGNORE_LOCKED_ENA
 */
#define  VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_IGNORE_LOCKED_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_IGNORE_LOCKED_ENA  VTSS_BIT(6)
#define  VTSS_X_LRN_COMMON_SCAN_NEXT_CFG_SCAN_NEXT_IGNORE_LOCKED_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Specifies age intervals are taken into account during FIND SMALLEST or
 * SCAN commands .
 *
 * \details 
 * x0: Don't find entries in the corresponding age interval.
 * 0x: Entries with the corresponding interval are taken into account.
 *
 * Field: ::VTSS_LRN_COMMON_SCAN_NEXT_CFG . SCAN_AGE_INTERVAL_MASK
 */
#define  VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_SCAN_AGE_INTERVAL_MASK(x)  VTSS_ENCODE_BITFIELD(x,2,4)
#define  VTSS_M_LRN_COMMON_SCAN_NEXT_CFG_SCAN_AGE_INTERVAL_MASK     VTSS_ENCODE_BITMASK(2,4)
#define  VTSS_X_LRN_COMMON_SCAN_NEXT_CFG_SCAN_AGE_INTERVAL_MASK(x)  VTSS_EXTRACT_BITFIELD(x,2,4)

/** 
 * \brief
 * Configures if FIND SMALLEST command or SCAN command cares about FID
 * values or not.
 * 
 * It is possible to configure additional FID filters through:
 * ANA_L2:COMMON:SCAN_FID_CTRL.SCAN_FID_ENA and 
 * ANA_L2:COMMON:SCAN_FID_CFG.SCAN_FID_VAL
 *
 * \details 
 * 0: Disable FID/VID filters (and ignore FID/VID) during SCAN and
 * FIND_SMALLEST commands.
 * 1: Enable FID/VID filter(s) during SCAN and FIND_SMALLEST. Only entries
 * with FID/VID value equal to LRN::MAC_ACCESS_CFG_0.MAC_ENTRY_FID or
 * optionally also values configured in
 * ANA_L2:COMMON:SCAN_FID_CFG.SCAN_FID_VAL will be found.
 *
 * Field: ::VTSS_LRN_COMMON_SCAN_NEXT_CFG . FID_FILTER_ENA
 */
#define  VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_FID_FILTER_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_LRN_COMMON_SCAN_NEXT_CFG_FID_FILTER_ENA  VTSS_BIT(1)
#define  VTSS_X_LRN_COMMON_SCAN_NEXT_CFG_FID_FILTER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Specifies whether ADDR values is dont care or will only affect entries
 * with a specific ADDR value during FIND SMALLEST or SCAN commands (refer
 * also to MAC_ENTRY_ADDR, MAC_ENTRY_ADDR_TYPE and FID_FILTER_ENA /
 * MAC_ENTRY_ADDR).
 *
 * \details 
 * 0: Disable. SCAN and FIND_SMALLEST commands will treat MAC_ENTRY_ADDR
 * and MAC_ENTRY_ADDR_TYPE values as don't care..
 * 1: Enable MAC_ENTRY_ADDR and MAC_ENTRY_ADDR_TYPE filter. SCAN and
 * FIND_SMALLEST commands will only search for entries with Address value
 * corresponding to MAC_ENTRY_ADDR and MAC_ENTRY_ADDR_TYPE taking
 * LRN::SCAN_NEXT_CFG_1.SCAN_ENTRY_ADDR_MASK into account).
 *
 * Field: ::VTSS_LRN_COMMON_SCAN_NEXT_CFG . ADDR_FILTER_ENA
 */
#define  VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_ADDR_FILTER_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_LRN_COMMON_SCAN_NEXT_CFG_ADDR_FILTER_ENA  VTSS_BIT(0)
#define  VTSS_X_LRN_COMMON_SCAN_NEXT_CFG_ADDR_FILTER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Age Filter
 *
 * \details
 * Register: \a LRN:COMMON:SCAN_NEXT_CFG_1
 */
#define VTSS_LRN_COMMON_SCAN_NEXT_CFG_1      VTSS_IOREG(VTSS_TO_LRN,0x5)

/** 
 * \brief
 * NEW ADDRESS when doing port move scan. This specifies the MAC_ENTRY_ADDR
 * with don't care positions (i.e. only care positions are replaced).
 *
 * \details 
 * Field: ::VTSS_LRN_COMMON_SCAN_NEXT_CFG_1 . PORT_MOVE_NEW_ADDR
 */
#define  VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_1_PORT_MOVE_NEW_ADDR(x)  VTSS_ENCODE_BITFIELD(x,16,15)
#define  VTSS_M_LRN_COMMON_SCAN_NEXT_CFG_1_PORT_MOVE_NEW_ADDR     VTSS_ENCODE_BITMASK(16,15)
#define  VTSS_X_LRN_COMMON_SCAN_NEXT_CFG_1_PORT_MOVE_NEW_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,16,15)

/** 
 * \brief
 * ADDRESS mask when doing port scan. This correspond to specify
 * MAC_ENTRY_ADDR with dont care positions (MSB-1 controls two additional
 * type bits).
 * 
 * To scan for all upsid_pn entries set MAC_ENTRY_ADDR_TYPE= UPSID_PN and
 * SCAN_ENTRY_ADDR_MASK(14:12)="111" and remaining SCAN_ENTRY_ADDR_MASK
 * bits to ALL_ZEROS

 *
 * \details 
 * 0: The corresponding bit is treated as dont care (ignore bit value)
 * 1: The corresponding bit is treated as care
 *
 * Field: ::VTSS_LRN_COMMON_SCAN_NEXT_CFG_1 . SCAN_ENTRY_ADDR_MASK
 */
#define  VTSS_F_LRN_COMMON_SCAN_NEXT_CFG_1_SCAN_ENTRY_ADDR_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,15)
#define  VTSS_M_LRN_COMMON_SCAN_NEXT_CFG_1_SCAN_ENTRY_ADDR_MASK     VTSS_ENCODE_BITMASK(0,15)
#define  VTSS_X_LRN_COMMON_SCAN_NEXT_CFG_1_SCAN_ENTRY_ADDR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,15)


/** 
 * \brief Configures last scan row
 *
 * \details
 * Configures an ending row for scan access. 
 *
 * Register: \a LRN:COMMON:SCAN_LAST_ROW_CFG
 */
#define VTSS_LRN_COMMON_SCAN_LAST_ROW_CFG    VTSS_IOREG(VTSS_TO_LRN,0x6)

/** 
 * \brief
 * Configures the last row to be part of scan. ignored if set to all ones.
 *
 * \details 
 * 0: Scan completes at row 0
 * ...
 * n: Scan completes at row n
 *
 * Field: ::VTSS_LRN_COMMON_SCAN_LAST_ROW_CFG . SCAN_LAST_ROW
 */
#define  VTSS_F_LRN_COMMON_SCAN_LAST_ROW_CFG_SCAN_LAST_ROW(x)  VTSS_ENCODE_BITFIELD(x,0,14)
#define  VTSS_M_LRN_COMMON_SCAN_LAST_ROW_CFG_SCAN_LAST_ROW     VTSS_ENCODE_BITMASK(0,14)
#define  VTSS_X_LRN_COMMON_SCAN_LAST_ROW_CFG_SCAN_LAST_ROW(x)  VTSS_EXTRACT_BITFIELD(x,0,14)


/** 
 * \brief Age Filter
 *
 * \details
 * Register: \a LRN:COMMON:SCAN_NEXT_CNT
 */
#define VTSS_LRN_COMMON_SCAN_NEXT_CNT        VTSS_IOREG(VTSS_TO_LRN,0x7)

/** 
 * \brief
 * Counter with number of found scan entries.
 *
 * \details 
 * Field: ::VTSS_LRN_COMMON_SCAN_NEXT_CNT . SCAN_NEXT_CNT
 */
#define  VTSS_F_LRN_COMMON_SCAN_NEXT_CNT_SCAN_NEXT_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LRN_COMMON_SCAN_NEXT_CNT_SCAN_NEXT_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LRN_COMMON_SCAN_NEXT_CNT_SCAN_NEXT_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Automated age scan configuration
 *
 * \details
 * Configures automated age scan of MAC table. 
 * 
 * This register is replicated for the four age intervals supported. 
 * 
 * Age interval are configured for auto leared entries through:
 * LRN:COMMON:AUTO_LRN_CFG.AUTO_AGE_INTERVAL
 * 
 * Age intervals are configured for CPU learned entries through:
 * LRN:COMMON:MAC_ACCESS_CFG_2.MAC_ENTRY_AGE_INTERVAL
 *
 * Register: \a LRN:COMMON:AUTOAGE_CFG
 *
 * @param ri Register: AUTOAGE_CFG (??), 0-3
 */
#define VTSS_LRN_COMMON_AUTOAGE_CFG(ri)      VTSS_IOREG(VTSS_TO_LRN,0x8 + (ri))

/** 
 * \brief
 * Sets the unit time. Setting UNIT_SIZE to zero effectively disables
 * ageing.
 *
 * \details 
 * 0: Disable age scan 
 * 1: 100 us (fastest possible scan is bestcase 150 us so increase
 * AUTOAGE_PERIOD_VAL to 2)
 * 2: 10 ms
 * 3: 1 s
 *
 * Field: ::VTSS_LRN_COMMON_AUTOAGE_CFG . UNIT_SIZE
 */
#define  VTSS_F_LRN_COMMON_AUTOAGE_CFG_UNIT_SIZE(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_LRN_COMMON_AUTOAGE_CFG_UNIT_SIZE     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_LRN_COMMON_AUTOAGE_CFG_UNIT_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/** 
 * \brief
 * Time in units between automatic ageing of an entry.
 * If otherwise subject to ageing, an inactive entry is removed after
 * between 3*AGE_PERIOD_VAL and 4*AGE_PERIOD_VAL.
 *
 * \details 
 * 0: Disabled
 * n: Age period = n * UNIT_SIZE
 *
 * Field: ::VTSS_LRN_COMMON_AUTOAGE_CFG . PERIOD_VAL
 */
#define  VTSS_F_LRN_COMMON_AUTOAGE_CFG_PERIOD_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,28)
#define  VTSS_M_LRN_COMMON_AUTOAGE_CFG_PERIOD_VAL     VTSS_ENCODE_BITMASK(0,28)
#define  VTSS_X_LRN_COMMON_AUTOAGE_CFG_PERIOD_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,28)


/** 
 * \brief Automated age scan configuration and status
 *
 * \details
 * Configures automated age scan of MAC table
 *
 * Register: \a LRN:COMMON:AUTOAGE_CFG_1
 */
#define VTSS_LRN_COMMON_AUTOAGE_CFG_1        VTSS_IOREG(VTSS_TO_LRN,0xc)

/** 
 * \brief
 * Pause current autoage scan.
 *
 * \details 
 * Field: ::VTSS_LRN_COMMON_AUTOAGE_CFG_1 . PAUSE_AUTO_AGE_ENA
 */
#define  VTSS_F_LRN_COMMON_AUTOAGE_CFG_1_PAUSE_AUTO_AGE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_LRN_COMMON_AUTOAGE_CFG_1_PAUSE_AUTO_AGE_ENA  VTSS_BIT(25)
#define  VTSS_X_LRN_COMMON_AUTOAGE_CFG_1_PAUSE_AUTO_AGE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/** 
 * \brief
 * Specifies the number of clk cycle before another autoage access can be
 * attempted.
 *
 * \details 
 * Field: ::VTSS_LRN_COMMON_AUTOAGE_CFG_1 . CELLS_BETWEEN_ENTRY_SCAN
 */
#define  VTSS_F_LRN_COMMON_AUTOAGE_CFG_1_CELLS_BETWEEN_ENTRY_SCAN(x)  VTSS_ENCODE_BITFIELD(x,15,10)
#define  VTSS_M_LRN_COMMON_AUTOAGE_CFG_1_CELLS_BETWEEN_ENTRY_SCAN     VTSS_ENCODE_BITMASK(15,10)
#define  VTSS_X_LRN_COMMON_AUTOAGE_CFG_1_CELLS_BETWEEN_ENTRY_SCAN(x)  VTSS_EXTRACT_BITFIELD(x,15,10)

/** 
 * \brief
 * Specifies the clock period in NS x 10.
 *
 * \details 
 * 64: 6,4ns
 * 192: 19,2 ns
 *
 * Field: ::VTSS_LRN_COMMON_AUTOAGE_CFG_1 . CLK_PERIOD_01NS
 */
#define  VTSS_F_LRN_COMMON_AUTOAGE_CFG_1_CLK_PERIOD_01NS(x)  VTSS_ENCODE_BITFIELD(x,7,8)
#define  VTSS_M_LRN_COMMON_AUTOAGE_CFG_1_CLK_PERIOD_01NS     VTSS_ENCODE_BITMASK(7,8)
#define  VTSS_X_LRN_COMMON_AUTOAGE_CFG_1_CLK_PERIOD_01NS(x)  VTSS_EXTRACT_BITFIELD(x,7,8)

/** 
 * \brief
 * Configures automated ageing of all port or only port not disabled in
 * ANA_L2::FILTER_OTHER_CTRL and ANA_L2::FILTER_LOCAL_CTRL.
 *
 * \details 
 * 0: Disable use additional port filter
 * 1: Enable use of additional port filter
 *
 * Field: ::VTSS_LRN_COMMON_AUTOAGE_CFG_1 . USE_PORT_FILTER_ENA
 */
#define  VTSS_F_LRN_COMMON_AUTOAGE_CFG_1_USE_PORT_FILTER_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_LRN_COMMON_AUTOAGE_CFG_1_USE_PORT_FILTER_ENA  VTSS_BIT(6)
#define  VTSS_X_LRN_COMMON_AUTOAGE_CFG_1_USE_PORT_FILTER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Triggers an instant hardware autoage scan (once current scan completes
 * -which can be ensured using FORCE_HW_SCAN_STOP_ENA).
 * 
 * The bit is cleared by HW when a new automated scan begins.
 *
 * \details 
 * 0: No force
 * 1: Force start of autoage scan
 *
 * Field: ::VTSS_LRN_COMMON_AUTOAGE_CFG_1 . FORCE_HW_SCAN_SHOT
 */
#define  VTSS_F_LRN_COMMON_AUTOAGE_CFG_1_FORCE_HW_SCAN_SHOT(x)  VTSS_ENCODE_BITFIELD(x,2,4)
#define  VTSS_M_LRN_COMMON_AUTOAGE_CFG_1_FORCE_HW_SCAN_SHOT     VTSS_ENCODE_BITMASK(2,4)
#define  VTSS_X_LRN_COMMON_AUTOAGE_CFG_1_FORCE_HW_SCAN_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,2,4)

/** 
 * \brief
 * Triggers forced stop of current autoage scan
 * 
 * The bit is cleared by HW when scan stop is obtained
 *
 * \details 
 * 0: No force
 * 1: Force autoage SCAN stop
 *
 * Field: ::VTSS_LRN_COMMON_AUTOAGE_CFG_1 . FORCE_HW_SCAN_STOP_SHOT
 */
#define  VTSS_F_LRN_COMMON_AUTOAGE_CFG_1_FORCE_HW_SCAN_STOP_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_LRN_COMMON_AUTOAGE_CFG_1_FORCE_HW_SCAN_STOP_SHOT  VTSS_BIT(1)
#define  VTSS_X_LRN_COMMON_AUTOAGE_CFG_1_FORCE_HW_SCAN_STOP_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Configures automated age scan stop after current automated scan
 * completes.

 *
 * \details 
 * 0: No force
 * 1: SCAN stop after current scan completes and stays stopped.
 *
 * Field: ::VTSS_LRN_COMMON_AUTOAGE_CFG_1 . FORCE_IDLE_ENA
 */
#define  VTSS_F_LRN_COMMON_AUTOAGE_CFG_1_FORCE_IDLE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_LRN_COMMON_AUTOAGE_CFG_1_FORCE_IDLE_ENA  VTSS_BIT(0)
#define  VTSS_X_LRN_COMMON_AUTOAGE_CFG_1_FORCE_IDLE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Automated age scan configuration and status
 *
 * \details
 * Configures automated age scan of MAC table
 *
 * Register: \a LRN:COMMON:AUTOAGE_CFG_2
 */
#define VTSS_LRN_COMMON_AUTOAGE_CFG_2        VTSS_IOREG(VTSS_TO_LRN,0xd)

/** 
 * \brief
 * Current autoage row. Changed on every autoage command. Indicate the MAC
 * table row to be autoaged aged next.
 * 
 * Incremented by hardware during auto ageing.
 *
 * \details 
 * 0: Row 0
 * 1: Row 1
 * ...
 * n: Row n.
 *
 * Field: ::VTSS_LRN_COMMON_AUTOAGE_CFG_2 . NEXT_ROW
 */
#define  VTSS_F_LRN_COMMON_AUTOAGE_CFG_2_NEXT_ROW(x)  VTSS_ENCODE_BITFIELD(x,4,14)
#define  VTSS_M_LRN_COMMON_AUTOAGE_CFG_2_NEXT_ROW     VTSS_ENCODE_BITMASK(4,14)
#define  VTSS_X_LRN_COMMON_AUTOAGE_CFG_2_NEXT_ROW(x)  VTSS_EXTRACT_BITFIELD(x,4,14)

/** 
 * \brief
 * High when AUTOAGE is ongoing for the given AGE interval.
 *
 * \details 
 * 0: No event has occured
 * 1: AUTOAGE scan ongoing.
 *
 * Field: ::VTSS_LRN_COMMON_AUTOAGE_CFG_2 . SCAN_ONGOING_STATUS
 */
#define  VTSS_F_LRN_COMMON_AUTOAGE_CFG_2_SCAN_ONGOING_STATUS(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_LRN_COMMON_AUTOAGE_CFG_2_SCAN_ONGOING_STATUS     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_LRN_COMMON_AUTOAGE_CFG_2_SCAN_ONGOING_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Auto Learn Options
 *
 * \details
 * Register: \a LRN:COMMON:AUTO_LRN_CFG
 */
#define VTSS_LRN_COMMON_AUTO_LRN_CFG         VTSS_IOREG(VTSS_TO_LRN,0xe)

/** 
 * \brief
 * The SRC_KILL_FWD flag for auto-learned entries will be set to the value
 * configured in this field.
 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_LRN_COMMON_AUTO_LRN_CFG . AUTO_LRN_SRC_KILL_FWD
 */
#define  VTSS_F_LRN_COMMON_AUTO_LRN_CFG_AUTO_LRN_SRC_KILL_FWD(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_LRN_COMMON_AUTO_LRN_CFG_AUTO_LRN_SRC_KILL_FWD  VTSS_BIT(9)
#define  VTSS_X_LRN_COMMON_AUTO_LRN_CFG_AUTO_LRN_SRC_KILL_FWD(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * The VLAN_IGNORE flag for auto-learned entries will be set to the value
 * configured in this field.
 *
 * \details 
 * 0: VLAN mask is used
 * 1: VLAN mask is ignored.
 *
 * Field: ::VTSS_LRN_COMMON_AUTO_LRN_CFG . AUTO_LRN_IGNORE_VLAN
 */
#define  VTSS_F_LRN_COMMON_AUTO_LRN_CFG_AUTO_LRN_IGNORE_VLAN(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_LRN_COMMON_AUTO_LRN_CFG_AUTO_LRN_IGNORE_VLAN  VTSS_BIT(8)
#define  VTSS_X_LRN_COMMON_AUTO_LRN_CFG_AUTO_LRN_IGNORE_VLAN(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * The CPU_QU for auto-learned entries will be set to the value configured
 * in this field.
 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_LRN_COMMON_AUTO_LRN_CFG . AUTO_LRN_CPU_QU
 */
#define  VTSS_F_LRN_COMMON_AUTO_LRN_CFG_AUTO_LRN_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_LRN_COMMON_AUTO_LRN_CFG_AUTO_LRN_CPU_QU     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_LRN_COMMON_AUTO_LRN_CFG_AUTO_LRN_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * The CPU_COPY flag for auto-learned entries will be set to the value
 * configured in this field.
 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_LRN_COMMON_AUTO_LRN_CFG . AUTO_LRN_CPU_COPY
 */
#define  VTSS_F_LRN_COMMON_AUTO_LRN_CFG_AUTO_LRN_CPU_COPY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_LRN_COMMON_AUTO_LRN_CFG_AUTO_LRN_CPU_COPY  VTSS_BIT(4)
#define  VTSS_X_LRN_COMMON_AUTO_LRN_CFG_AUTO_LRN_CPU_COPY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * The MIRROR flag for auto-learned entries will be set to the value
 * configured in this field.
 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_LRN_COMMON_AUTO_LRN_CFG . AUTO_LRN_MIRROR
 */
#define  VTSS_F_LRN_COMMON_AUTO_LRN_CFG_AUTO_LRN_MIRROR(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_LRN_COMMON_AUTO_LRN_CFG_AUTO_LRN_MIRROR  VTSS_BIT(3)
#define  VTSS_X_LRN_COMMON_AUTO_LRN_CFG_AUTO_LRN_MIRROR(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * The AGE interval for auto-learned entries will be set to the value
 * configured in this field.
 *
 * \details 
 * Field: ::VTSS_LRN_COMMON_AUTO_LRN_CFG . AUTO_AGE_INTERVAL
 */
#define  VTSS_F_LRN_COMMON_AUTO_LRN_CFG_AUTO_AGE_INTERVAL(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_LRN_COMMON_AUTO_LRN_CFG_AUTO_AGE_INTERVAL     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_LRN_COMMON_AUTO_LRN_CFG_AUTO_AGE_INTERVAL(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Additional control for autonomous Learning.
 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_LRN_COMMON_AUTO_LRN_CFG . AUTO_LRN_ENA
 */
#define  VTSS_F_LRN_COMMON_AUTO_LRN_CFG_AUTO_LRN_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_LRN_COMMON_AUTO_LRN_CFG_AUTO_LRN_ENA  VTSS_BIT(0)
#define  VTSS_X_LRN_COMMON_AUTO_LRN_CFG_AUTO_LRN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Sticky diagnostic status
 *
 * \details
 * Register: \a LRN:COMMON:EVENT_STICKY
 */
#define VTSS_LRN_COMMON_EVENT_STICKY         VTSS_IOREG(VTSS_TO_LRN,0xf)

/** 
 * \brief
 * Set when AUTOAGE scan completes.
 *
 * \details 
 * 0: No event has occured
 * 1: AUTOAGE scan completes
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . AUTOAGE_SCAN_COMPLETED_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_AUTOAGE_SCAN_COMPLETED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_AUTOAGE_SCAN_COMPLETED_STICKY  VTSS_BIT(28)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_AUTOAGE_SCAN_COMPLETED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/** 
 * \brief
 * Set when Autoage scan starts.
 *
 * \details 
 * 0: No event has occured
 * 1: AUTOAGE scan started
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . AUTOAGE_SCAN_STARTED_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_AUTOAGE_SCAN_STARTED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_AUTOAGE_SCAN_STARTED_STICKY  VTSS_BIT(27)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_AUTOAGE_SCAN_STARTED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/** 
 * \brief
 * Set when Autoage scan should be started before the last scan completed.
 *
 * \details 
 * 0: No event has occured
 * 1: AUTOAGE could not start before the current scan completed
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . AUTOAGE_START_DELAYED_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_AUTOAGE_START_DELAYED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_AUTOAGE_START_DELAYED_STICKY  VTSS_BIT(26)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_AUTOAGE_START_DELAYED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * A sticky bit must be set when a learn request arrives to an already full
 * queue.
 *
 * \details 
 * 0: No overflow
 * 1:  Overflow
 * Write '1' to clear bit.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . LRN_QUEUE_OVERFLOW_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_LRN_QUEUE_OVERFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_LRN_QUEUE_OVERFLOW_STICKY  VTSS_BIT(25)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_LRN_QUEUE_OVERFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/** 
 * \brief
 * A non empty learn queue must be signalled.
 *
 * \details 
 * 0:  Empty
 * 1:  Non empty
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . LRN_QUEUE_DATA_AVAIL_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_LRN_QUEUE_DATA_AVAIL_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_LRN_QUEUE_DATA_AVAIL_STICKY  VTSS_BIT(24)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_LRN_QUEUE_DATA_AVAIL_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * Set if CPU learn failed due to FID learn limit exceeded. Write '1' to
 * clear this field.
 *
 * \details 
 * 0: No change.
 * 1: Fid Learn limit has caused CPU based learning to fail.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . CPU_LRN_FID_LIMIT_EXCEEDED_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_CPU_LRN_FID_LIMIT_EXCEEDED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_CPU_LRN_FID_LIMIT_EXCEEDED_STICKY  VTSS_BIT(23)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_CPU_LRN_FID_LIMIT_EXCEEDED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * Set if a MAC address entry has been aged due to an autoage operation.
 *
 * \details 
 * 0: No entries have been aged due to autoage.
 * 1: At least 1 entry has been aged due to autoage.
 * Write '1' to clear this field.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . AUTOAGE_AGED_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_AUTOAGE_AGED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_AUTOAGE_AGED_STICKY  VTSS_BIT(22)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_AUTOAGE_AGED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Set if a MAC address entry has been removed due to an autoage operation.
 *
 * \details 
 * 0: No entries have been removed due to autoage.
 * 1: At least 1 entry has been removed due to autoage.
 * Write '1' to clear this field.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . AUTOAGE_REMOVE_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_AUTOAGE_REMOVE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_AUTOAGE_REMOVE_STICKY  VTSS_BIT(21)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_AUTOAGE_REMOVE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * Set if a row matching the scan condition has been found. (Check after
 * MAC_TABLE_ACCESS_SHOT went to 0).
 *
 * \details 
 * 0: No entry has been found.
 * 1: An entry has been found.
 * Write '1' to clear this field.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . ROW_WITH_SCAN_ENTRY_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_ROW_WITH_SCAN_ENTRY_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_ROW_WITH_SCAN_ENTRY_STICKY  VTSS_BIT(20)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_ROW_WITH_SCAN_ENTRY_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Set if a MAC address entry has been removed due to a scan operation.
 *
 * \details 
 * 0: No entries have been removed due to scan.
 * 1: At least 1 entry has been removed due to scan.
 * Write '1' to clear this field.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . SCAN_REMOVED_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_SCAN_REMOVED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_SCAN_REMOVED_STICKY  VTSS_BIT(19)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_SCAN_REMOVED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * Set if AUTO learn failed due to FID learn limit exceeded. Write '1' to
 * clear this field.
 *
 * \details 
 * 0: No change.
 * 1: Fid Learn limit has caused CPU based learning to fail.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . AUTO_LRN_FID_LIMIT_EXCEEDED_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_AUTO_LRN_FID_LIMIT_EXCEEDED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_AUTO_LRN_FID_LIMIT_EXCEEDED_STICKY  VTSS_BIT(18)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_AUTO_LRN_FID_LIMIT_EXCEEDED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Set if an autonomous learning operation has failed due to hash table
 * depletion (i.e. all entries in a row were locked). Write '1' to clear
 * this field.
 *
 * \details 
 * 0: No autonomous learning operations have failed.
 * 1: An autonomous learning operation has failed.
 * Write '1' to clear this field.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . AUTO_LRN_FAILED_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_AUTO_LRN_FAILED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_AUTO_LRN_FAILED_STICKY  VTSS_BIT(17)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_AUTO_LRN_FAILED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Set if a MAC address entry has been inserted into the MAC CAM. Write '1'
 * to clear this field.
 *
 * \details 
 * 0: No entries have been inserted into empty buckets
 * 1: An entry has been inserted into an empty bucket.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . AUTO_LRN_INSERT_CAM_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_AUTO_LRN_INSERT_CAM_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_AUTO_LRN_INSERT_CAM_STICKY  VTSS_BIT(16)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_AUTO_LRN_INSERT_CAM_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Set if a MAC address entry has been inserted into a MAC address table
 * column (bucket). Write '1' to clear this field.
 *
 * \details 
 * 0: No entries have been inserted into empty buckets
 * 1: An entry has been inserted into an empty bucket.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . AUTO_LRN_INSERT_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_AUTO_LRN_INSERT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_AUTO_LRN_INSERT_STICKY  VTSS_BIT(15)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_AUTO_LRN_INSERT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Set if MAC entry has been updated. Write '1' to clear this field.
 *
 * \details 
 * 0: No entries have been refreshed.
 * 1: An entry has been refreshed.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . AUTO_LRN_REFRESH_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_AUTO_LRN_REFRESH_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_AUTO_LRN_REFRESH_STICKY  VTSS_BIT(14)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_AUTO_LRN_REFRESH_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Set if a randomly selected non-locked and valid MAC address entry can
 * not be overwritten by a new (VID, SMAC). Write '1' to clear this field.
 *
 * \details 
 * 0: No entries have been replaced.
 * 1: An entry has not been replaced due to configuration.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . AUTO_LRN_REPLACE_FAILED_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_AUTO_LRN_REPLACE_FAILED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_AUTO_LRN_REPLACE_FAILED_STICKY  VTSS_BIT(13)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_AUTO_LRN_REPLACE_FAILED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Set if a randomly selected non-locked and valid MAC address entry has
 * been overwritten by a new (VID, SMAC). Write '1' to clear this field.
 *
 * \details 
 * 0: No entries have been replaced.
 * 1: An entry has been replaced.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . AUTO_LRN_REPLACE_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_AUTO_LRN_REPLACE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_AUTO_LRN_REPLACE_STICKY  VTSS_BIT(12)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_AUTO_LRN_REPLACE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Set when a learn move has occured (move from CAM row to MAC table).
 * Write '1' to clear this field.
 *
 * \details 
 * 0:  No update
 * 1: Learn move operation has occured.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . LRN_MOVE_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_LRN_MOVE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_LRN_MOVE_STICKY  VTSS_BIT(11)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_LRN_MOVE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Set when a direct CPU MAC READ operation has occured. Write '1' to clear
 * this field.
 *
 * \details 
 * 0:  No update
 * 1: CPU read direct operation has occured.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . CPU_READ_DIRECT_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_CPU_READ_DIRECT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_CPU_READ_DIRECT_STICKY  VTSS_BIT(10)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_CPU_READ_DIRECT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Set when a direct CPU MAC WRITE operation has occured. Write '1' to
 * clear this field.
 *
 * \details 
 * 0:  No update
 * 1: CPU write direct operation has occured.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . CPU_WRITE_DIRECT_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_CPU_WRITE_DIRECT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_CPU_WRITE_DIRECT_STICKY  VTSS_BIT(9)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_CPU_WRITE_DIRECT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Set if a CPU MAC LOOKUP operation has failed due to not found an entry.
 * Write '1' to clear this field.
 *
 * \details 
 * 0:  No fail
 * 1: CPU lookup operation failed.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . CPU_LOOKUP_FAILED_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_CPU_LOOKUP_FAILED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_CPU_LOOKUP_FAILED_STICKY  VTSS_BIT(8)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_CPU_LOOKUP_FAILED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Set if a CPU MAC LOOKUP operation has succeeded. Write '1' to clear this
 * field.
 *
 * \details 
 * 0:  No successful lookup
 * 1: Successful lookup.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . CPU_LOOKUP_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_CPU_LOOKUP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_CPU_LOOKUP_STICKY  VTSS_BIT(7)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_CPU_LOOKUP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Set if a CPU MAC UNLEARN operation has failed because the respective
 * (valid) entry was not found. Write '1' to clear this field.
 *
 * \details 
 * 0:  No UNLEARN operation failed
 * 1: CPU UNLEARN operation failed.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . CPU_UNLEARN_FAILED_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_CPU_UNLEARN_FAILED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_CPU_UNLEARN_FAILED_STICKY  VTSS_BIT(6)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_CPU_UNLEARN_FAILED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Set if a CPU MAC UNLEARN operation has succeeded. Write '1' to clear
 * this field.
 *
 * \details 
 * 0:  No CPU MAC UNLEARN operation took place
 * 1:  CPU UNLEARN operations has succeeded.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . CPU_UNLEARN_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_CPU_UNLEARN_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_CPU_UNLEARN_STICKY  VTSS_BIT(5)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_CPU_UNLEARN_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Set if CPU learn replace can not be performed due to configuration.
 * Write '1' to clear this field.
 *
 * \details 
 * 0: No learn based replacement failed.
 * 1: The replacement of 1 or more entries failed.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . CPU_LRN_REPLACE_FAILED_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_CPU_LRN_REPLACE_FAILED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_CPU_LRN_REPLACE_FAILED_STICKY  VTSS_BIT(4)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_CPU_LRN_REPLACE_FAILED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set if a valid MAC entry has been updated (refreshed), i.e. a write
 * access to the same bucket with the same MAC and VID has occured. Write
 * '1' to clear this field.
 *
 * \details 
 * 0: No entries have been refreshed.
 * 1: An entry has been refreshed.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . CPU_LRN_REFRESH_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_CPU_LRN_REFRESH_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_CPU_LRN_REFRESH_STICKY  VTSS_BIT(3)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_CPU_LRN_REFRESH_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set if a valid MAC entry has been overwritten, i.e. a write access to
 * the same bucket with a changed MAC and/or VID has occured. Write '1' to
 * clear this field.
 *
 * \details 
 * 0: No entries have been replaced.
 * 1: An entry has been replaced.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . CPU_LRN_REPLACE_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_CPU_LRN_REPLACE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_CPU_LRN_REPLACE_STICKY  VTSS_BIT(2)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_CPU_LRN_REPLACE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set if a MAC entry has been inserted into an empty MAC table row,column
 * (=bucket). Write '1' to clear this field.
 *
 * \details 
 * 0: No entries have been inserted into an empty bucket
 * 1: An entry has been inserted into an empty bucket.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . CPU_LRN_INSERT_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_CPU_LRN_INSERT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_CPU_LRN_INSERT_STICKY  VTSS_BIT(1)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_CPU_LRN_INSERT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set if an CPU learning operation has failed due to hash table depletion
 * (i.e. all entries in a row were locked). Write '1' to clear this field.
 *
 * \details 
 * 0: No CPU LEARN operations has failed.
 * 1: A CPU LEARN operation has failed.
 *
 * Field: ::VTSS_LRN_COMMON_EVENT_STICKY . CPU_LRN_FAILED_STICKY
 */
#define  VTSS_F_LRN_COMMON_EVENT_STICKY_CPU_LRN_FAILED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_LRN_COMMON_EVENT_STICKY_CPU_LRN_FAILED_STICKY  VTSS_BIT(0)
#define  VTSS_X_LRN_COMMON_EVENT_STICKY_CPU_LRN_FAILED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Learn Diagnostic
 *
 * \details
 * Register: \a LRN:COMMON:LATEST_POS_STATUS
 */
#define VTSS_LRN_COMMON_LATEST_POS_STATUS    VTSS_IOREG(VTSS_TO_LRN,0x10)

/** 
 * \brief
 * This field holds the current (i.e. latest accessed) type after a
 * CPU_ACCESS_CMD has been finished.
 *
 * \details 
 * 0: MAC table
 * 1: CAM MAC table
 *
 * Field: ::VTSS_LRN_COMMON_LATEST_POS_STATUS . LATEST_TYPE
 */
#define  VTSS_F_LRN_COMMON_LATEST_POS_STATUS_LATEST_TYPE(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_LRN_COMMON_LATEST_POS_STATUS_LATEST_TYPE  VTSS_BIT(24)
#define  VTSS_X_LRN_COMMON_LATEST_POS_STATUS_LATEST_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * Gives the scan result per bucket of the last row scanned (bitgroup
 * contains 1 bit per bucket of an entire row).
 *
 * \details 
 * Per bucket:
 * 0: Bucket does not match filter condition
 * 1: Bucket does match filter condition
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_LRN_COMMON_LATEST_POS_STATUS . SCAN_NEXT_STATUS
 */
#define  VTSS_F_LRN_COMMON_LATEST_POS_STATUS_SCAN_NEXT_STATUS(x)  VTSS_ENCODE_BITFIELD(x,18,4)
#define  VTSS_M_LRN_COMMON_LATEST_POS_STATUS_SCAN_NEXT_STATUS     VTSS_ENCODE_BITMASK(18,4)
#define  VTSS_X_LRN_COMMON_LATEST_POS_STATUS_SCAN_NEXT_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,18,4)

/** 
 * \brief
 * This field holds the current (i.e. latest accessed) MAC table row number
 * after a CPU_ACCESS_CMD has been finished.
 *
 * \details 
 * 0: Row 0
 * 1: Row 1
 * ...
 * n: Row n
 *
 * Field: ::VTSS_LRN_COMMON_LATEST_POS_STATUS . LATEST_ROW
 */
#define  VTSS_F_LRN_COMMON_LATEST_POS_STATUS_LATEST_ROW(x)  VTSS_ENCODE_BITFIELD(x,4,14)
#define  VTSS_M_LRN_COMMON_LATEST_POS_STATUS_LATEST_ROW     VTSS_ENCODE_BITMASK(4,14)
#define  VTSS_X_LRN_COMMON_LATEST_POS_STATUS_LATEST_ROW(x)  VTSS_EXTRACT_BITFIELD(x,4,14)

/** 
 * \brief
 * This field holds the current (i.e. latest accessed) column number after
 * a CPU_ACCESS_CMD has been finished.
 *
 * \details 
 * 0: Column (bucket) 0
 * 1: Column (bucket) 1
 * ...
 * n: Column (bucket) n
 *
 * Field: ::VTSS_LRN_COMMON_LATEST_POS_STATUS . LATEST_COL
 */
#define  VTSS_F_LRN_COMMON_LATEST_POS_STATUS_LATEST_COL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_LRN_COMMON_LATEST_POS_STATUS_LATEST_COL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_LRN_COMMON_LATEST_POS_STATUS_LATEST_COL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


#endif /* _VTSS_JAGUAR2C_REGS_LRN_H_ */
