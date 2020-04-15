#ifndef _VTSS_LUTON26_REGS_ANA_H_
#define _VTSS_LUTON26_REGS_ANA_H_

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

#include "vtss_luton26_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a ANA
 *
 * Analyzer Configuration
 *
 ***********************************************************************/

/**
 * Register Group: \a ANA:ANA
 *
 * Not documented
 */


/** 
 * \brief Advanced Learning Setup
 *
 * \details
 * Register: \a ANA:ANA:ADVLEARN
 */
#define VTSS_ANA_ANA_ADVLEARN                VTSS_IOREG(VTSS_TO_ANA,0x360)

/** 
 * \brief
 * If this bit is set, a frame discarded because of VLAN ingress filtering
 * is not subject to learning. VLAN ingress filtering is controlled by the
 * VLAN_SRC_CHK flag in the VLAN table (see VLANACCESS register) or the
 * VLANMASK register.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ADVLEARN . VLAN_CHK
 */
#define  VTSS_F_ANA_ANA_ADVLEARN_VLAN_CHK     VTSS_BIT(26)

/** 
 * \brief
 * Learn frames are also forwarded to ports marked in this mask.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ADVLEARN . LEARN_MIRROR
 */
#define  VTSS_F_ANA_ANA_ADVLEARN_LEARN_MIRROR(x)  VTSS_ENCODE_BITFIELD(x,0,26)
#define  VTSS_M_ANA_ANA_ADVLEARN_LEARN_MIRROR     VTSS_ENCODE_BITMASK(0,26)
#define  VTSS_X_ANA_ANA_ADVLEARN_LEARN_MIRROR(x)  VTSS_EXTRACT_BITFIELD(x,0,26)


/** 
 * \brief VLAN Source Port Mask
 *
 * \details
 * Register: \a ANA:ANA:VLANMASK
 */
#define VTSS_ANA_ANA_VLANMASK                VTSS_IOREG(VTSS_TO_ANA,0x361)

/** 
 * \brief
 * Mask for requiring VLAN ingress filtering. If the bit for the frame's
 * physical ingress port is set in this mask,  then the port must be member
 * of ingress frame's VLAN (VLANACCESS.VLAN_PORT_MASK), otherwise the frame
 *  is discarded.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_VLANMASK . VLANMASK
 */
#define  VTSS_F_ANA_ANA_VLANMASK_VLANMASK(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_ANA_ANA_VLANMASK_VLANMASK     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_ANA_ANA_VLANMASK_VLANMASK(x)  VTSS_EXTRACT_BITFIELD(x,0,27)


/** 
 * \brief Aging Filter
 *
 * \details
 * This register sets up which entries are touched by an aging operation
 * (manual as well as automatic aging). 
 * In this way, it is possible to have different aging periods in each VLAN
 * and to have quick removal of entries on specific ports.
 * 
 * The register also affects the GET_NEXT MAC table command. When using the
 * register to control the behavior of GET_NEXT, it is recommended to
 * disable automatic aging while executing the GET_NEXT command.
 *
 * Register: \a ANA:ANA:ANAGEFIL
 */
#define VTSS_ANA_ANA_ANAGEFIL                VTSS_IOREG(VTSS_TO_ANA,0x362)

/** 
 * \brief
 * Select entries to age. If cleared, unlocked entries will be aged and
 * potentially removed. If set, locked entries will be aged but not
 * removed.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANAGEFIL . AGE_LOCKED
 */
#define  VTSS_F_ANA_ANA_ANAGEFIL_AGE_LOCKED   VTSS_BIT(19)

/** 
 * \brief
 * If set, only MAC table entries with a destination index matching PID_VAL
 * are aged.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANAGEFIL . PID_EN
 */
#define  VTSS_F_ANA_ANA_ANAGEFIL_PID_EN       VTSS_BIT(18)

/** 
 * \brief
 * Destination index used in selective aging.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANAGEFIL . PID_VAL
 */
#define  VTSS_F_ANA_ANA_ANAGEFIL_PID_VAL(x)   VTSS_ENCODE_BITFIELD(x,13,5)
#define  VTSS_M_ANA_ANA_ANAGEFIL_PID_VAL      VTSS_ENCODE_BITMASK(13,5)
#define  VTSS_X_ANA_ANA_ANAGEFIL_PID_VAL(x)   VTSS_EXTRACT_BITFIELD(x,13,5)

/** 
 * \brief
 * If set, only MAC table entries with a VID matching VID_VAL are aged.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANAGEFIL . VID_EN
 */
#define  VTSS_F_ANA_ANA_ANAGEFIL_VID_EN       VTSS_BIT(12)

/** 
 * \brief
 * VID used in selective aging.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANAGEFIL . VID_VAL
 */
#define  VTSS_F_ANA_ANA_ANAGEFIL_VID_VAL(x)   VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_ANA_ANA_ANAGEFIL_VID_VAL      VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_ANA_ANA_ANAGEFIL_VID_VAL(x)   VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Event Sticky Bits
 *
 * \details
 * Register: \a ANA:ANA:ANEVENTS
 */
#define VTSS_ANA_ANA_ANEVENTS                VTSS_IOREG(VTSS_TO_ANA,0x363)

/** 
 * \brief
 * An AUTOAGE run was performed.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . AUTOAGE
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_AUTOAGE      VTSS_BIT(24)

/** 
 * \brief
 * A frame was discarded, because it exceeded the flooding storm
 * limitations configured in STORMLIMIT.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . STORM_DROP
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_STORM_DROP   VTSS_BIT(22)

/** 
 * \brief
 * A frame was discarded, because it was subject to learning, and the
 * DropMode flag was set in ADVLEARN.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . LEARN_DROP
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_LEARN_DROP   VTSS_BIT(21)

/** 
 * \brief
 * An entry was removed at CPU Learn, or CPU requested an aging process.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . AGED_ENTRY
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_AGED_ENTRY   VTSS_BIT(20)

/** 
 * \brief
 * A learn operation failed due to hash table depletion. CPU-based learning
 * only.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . CPU_LEARN_FAILED
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_CPU_LEARN_FAILED  VTSS_BIT(19)

/** 
 * \brief
 * A learn operation of incoming source MAC address failed due to hash
 * table depletion. Hardware-based learning only.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . AUTO_LEARN_FAILED
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_AUTO_LEARN_FAILED  VTSS_BIT(18)

/** 
 * \brief
 * An entry was removed when learning a new source MAC address.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . LEARN_REMOVE
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_LEARN_REMOVE  VTSS_BIT(17)

/** 
 * \brief
 * An entry was learned from an incoming frame. Hardware-based learning
 * only.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . AUTO_LEARNED
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_AUTO_LEARNED  VTSS_BIT(16)

/** 
 * \brief
 * A station was moved to another port.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . AUTO_MOVED
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_AUTO_MOVED   VTSS_BIT(15)

/** 
 * \brief
 * A frame was not forwarded due to classification (such as BPDUs).
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . CLASSIFIED_DROP
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_CLASSIFIED_DROP  VTSS_BIT(13)

/** 
 * \brief
 * A frame was copied to the CPU due to classification.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . CLASSIFIED_COPY
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_CLASSIFIED_COPY  VTSS_BIT(12)

/** 
 * \brief
 * A frame was discarded due to lack of VLAN membership on source port.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . VLAN_DISCARD
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_VLAN_DISCARD  VTSS_BIT(11)

/** 
 * \brief
 * A frame was discarded due to missing forwarding state on source port.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . FWD_DISCARD
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_FWD_DISCARD  VTSS_BIT(10)

/** 
 * \brief
 * A frame was flooded with multicast flooding mask.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . MULTICAST_FLOOD
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_MULTICAST_FLOOD  VTSS_BIT(9)

/** 
 * \brief
 * A frame was flooded with unicast flooding mask.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . UNICAST_FLOOD
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_UNICAST_FLOOD  VTSS_BIT(8)

/** 
 * \brief
 * A frame was forwarded with known destination MAC address.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . DEST_KNOWN
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_DEST_KNOWN   VTSS_BIT(7)

/** 
 * \brief
 * A destination was found in hash table bucket 3.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . BUCKET3_MATCH
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_BUCKET3_MATCH  VTSS_BIT(6)

/** 
 * \brief
 * A destination was found in hash table bucket 2.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . BUCKET2_MATCH
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_BUCKET2_MATCH  VTSS_BIT(5)

/** 
 * \brief
 * A destination was found in hash table bucket 1.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . BUCKET1_MATCH
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_BUCKET1_MATCH  VTSS_BIT(4)

/** 
 * \brief
 * A destination was found in hash table bucket 0.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . BUCKET0_MATCH
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_BUCKET0_MATCH  VTSS_BIT(3)

/** 
 * \brief
 * A CPU-initiated operation on the MAC or VLAN table was processed.
 * Default is 1 due to auto-initialization of the MAC and VLAN table.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . CPU_OPERATION
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_CPU_OPERATION  VTSS_BIT(2)

/** 
 * \brief
 * A destination address was looked up in the MAC table.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . DMAC_LOOKUP
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_DMAC_LOOKUP  VTSS_BIT(1)

/** 
 * \brief
 * A source address was looked up in the MAC table.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ANEVENTS . SMAC_LOOKUP
 */
#define  VTSS_F_ANA_ANA_ANEVENTS_SMAC_LOOKUP  VTSS_BIT(0)


/** 
 * \brief Storm policer burst
 *
 * \details
 * Register: \a ANA:ANA:STORMLIMIT_BURST
 */
#define VTSS_ANA_ANA_STORMLIMIT_BURST        VTSS_IOREG(VTSS_TO_ANA,0x364)

/** 
 * \brief
 * Allowed number of frames in a burst is 2**STORM_BURST. The STORM_BURST
 * is common for all storm policers.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_STORMLIMIT_BURST . STORM_BURST
 */
#define  VTSS_F_ANA_ANA_STORMLIMIT_BURST_STORM_BURST(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ANA_ANA_STORMLIMIT_BURST_STORM_BURST     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ANA_ANA_STORMLIMIT_BURST_STORM_BURST(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Storm Policer configuration
 *
 * \details
 * 0: UC storm policer
 * 1: BC storm policer
 * 2: MC policer
 * 3: Learn policer
 *
 * Register: \a ANA:ANA:STORMLIMIT_CFG
 *
 * @param ri Register: STORMLIMIT_CFG (??), 0-3
 */
#define VTSS_ANA_ANA_STORMLIMIT_CFG(ri)      VTSS_IOREG(VTSS_TO_ANA,0x365 + (ri))

/** 
 * \brief
 * Allowed rate of storm policer
 *
 * \details 
 * 0 : 1 frames/sec or kiloframes/sec (see STORM_UNIT).
 * 1 : 2 frames/sec or kiloframes/sec (see STORM_UNIT).
 * 2 : 4 frames/sec or kiloframes/sec (see STORM_UNIT).
 * 3 : 8 frames/sec or kiloframes/sec (see STORM_UNIT).
 * ...
 * 15 : 32768 frames/sec or kiloframes/sec (see STORM_UNIT).
 *
 * Field: ::VTSS_ANA_ANA_STORMLIMIT_CFG . STORM_RATE
 */
#define  VTSS_F_ANA_ANA_STORMLIMIT_CFG_STORM_RATE(x)  VTSS_ENCODE_BITFIELD(x,3,4)
#define  VTSS_M_ANA_ANA_STORMLIMIT_CFG_STORM_RATE     VTSS_ENCODE_BITMASK(3,4)
#define  VTSS_X_ANA_ANA_STORMLIMIT_CFG_STORM_RATE(x)  VTSS_EXTRACT_BITFIELD(x,3,4)

/** 
 * \brief
 * If set, the base unit for the storm policer is 1 frame per second. If
 * cleared, the base unit is 1 kiloframes per second.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_STORMLIMIT_CFG . STORM_UNIT
 */
#define  VTSS_F_ANA_ANA_STORMLIMIT_CFG_STORM_UNIT  VTSS_BIT(2)

/** 
 * \brief
 * Mode of operation for storm policer.
 *
 * \details 
 * 0: Disabled
 * 1: Police CPU destination only.
 * 2: Police front port destinations only.
 * 3: Police both CPU and front port destinations.
 *
 * Field: ::VTSS_ANA_ANA_STORMLIMIT_CFG . STORM_MODE
 */
#define  VTSS_F_ANA_ANA_STORMLIMIT_CFG_STORM_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ANA_ANA_STORMLIMIT_CFG_STORM_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ANA_ANA_STORMLIMIT_CFG_STORM_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Private VLAN Mask for isolated ports
 *
 * \details
 * Register: \a ANA:ANA:ISOLATED_PORTS
 */
#define VTSS_ANA_ANA_ISOLATED_PORTS          VTSS_IOREG(VTSS_TO_ANA,0x369)

/** 
 * \brief
 * This mask is used in private VLANs applications. Promiscuous and
 * community ports must be set and isolated ports must be cleared. 
 * 
 * For frames classified to a private VLAN (see the VLAN_PRIV_VLAN field in
 * VLAN table), the resulting VLAN mask is calculated as follows:
 * - Frames received on a promiscuous port use the VLAN mask directly.
 * - Frames received on a community port use the VLAN mask AND'ed with the
 * ISOL_PORTS.
 * - Frames received on a isolated port use the VLAN mask AND'ed with the
 * COMM_PORTS AND'ed with the ISOL_PORTS.
 * 
 * For frames classified to a non-private VLAN, this mask is not used.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_ISOLATED_PORTS . ISOL_PORTS
 */
#define  VTSS_F_ANA_ANA_ISOLATED_PORTS_ISOL_PORTS(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_ANA_ANA_ISOLATED_PORTS_ISOL_PORTS     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_ANA_ANA_ISOLATED_PORTS_ISOL_PORTS(x)  VTSS_EXTRACT_BITFIELD(x,0,27)


/** 
 * \brief Private VLAN Mask for community ports
 *
 * \details
 * Register: \a ANA:ANA:COMMUNITY_PORTS
 */
#define VTSS_ANA_ANA_COMMUNITY_PORTS         VTSS_IOREG(VTSS_TO_ANA,0x36a)

/** 
 * \brief
 * This mask is used in private VLANs applications. Promiscuous and
 * isolated ports must be set and community ports must be cleared. 
 * 
 * See ISOLATED_PORTS.ISOL_PORTS for details.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_COMMUNITY_PORTS . COMM_PORTS
 */
#define  VTSS_F_ANA_ANA_COMMUNITY_PORTS_COMM_PORTS(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_ANA_ANA_COMMUNITY_PORTS_COMM_PORTS     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_ANA_ANA_COMMUNITY_PORTS_COMM_PORTS(x)  VTSS_EXTRACT_BITFIELD(x,0,27)


/** 
 * \brief Auto Age Timer
 *
 * \details
 * Register: \a ANA:ANA:AUTOAGE
 */
#define VTSS_ANA_ANA_AUTOAGE                 VTSS_IOREG(VTSS_TO_ANA,0x36b)

/** 
 * \brief
 * Sets the unit of PERIOD to 8.2 us. PERIOD must be a minimum of 3 when
 * using the FAST option.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_AUTOAGE . AGE_FAST
 */
#define  VTSS_F_ANA_ANA_AUTOAGE_AGE_FAST      VTSS_BIT(21)

/** 
 * \brief
 * Time in seconds between automatic aging of a MAC table entry. Setting
 * AGE_PERIOD to zero effectively disables automatic aging. An inactive
 * unlocked MAC table entry is aged after 2*AGE_PERIOD.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_AUTOAGE . AGE_PERIOD
 */
#define  VTSS_F_ANA_ANA_AUTOAGE_AGE_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,1,20)
#define  VTSS_M_ANA_ANA_AUTOAGE_AGE_PERIOD     VTSS_ENCODE_BITMASK(1,20)
#define  VTSS_X_ANA_ANA_AUTOAGE_AGE_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,1,20)

/** 
 * \brief
 * Also set the AGED_FLAG bit on locked entries. They will not be removed.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_AUTOAGE . AUTOAGE_LOCKED
 */
#define  VTSS_F_ANA_ANA_AUTOAGE_AUTOAGE_LOCKED  VTSS_BIT(0)


/** 
 * \brief MAC Table Options
 *
 * \details
 * Register: \a ANA:ANA:MACTOPTIONS
 */
#define VTSS_ANA_ANA_MACTOPTIONS             VTSS_IOREG(VTSS_TO_ANA,0x36c)

/** 
 * \brief
 * When set, the MAC table will be reduced 256 entries (64 hash-chains of
 * 4) 
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_MACTOPTIONS . REDUCED_TABLE
 */
#define  VTSS_F_ANA_ANA_MACTOPTIONS_REDUCED_TABLE  VTSS_BIT(1)

/** 
 * \brief
 * Enable MAC table shadow registers. The SHADOW bit affects the behavior
 * of the READ command in MACACCESS.MAC_TABLE_CMD: With the shadow bit set,
 * reading bucket 0 causes the remaining 3 buckets in the row to be stored
 * in "shadow registers". Following read accesses to bucket 1-3 return the
 * content of the shadow registers. This is useful when reading a MAC
 * table, which can change while being read.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_MACTOPTIONS . SHADOW
 */
#define  VTSS_F_ANA_ANA_MACTOPTIONS_SHADOW    VTSS_BIT(0)


/** 
 * \brief Learn Discard Counter
 *
 * \details
 * The total number of MAC table entries that have been or would have been
 * learned, but have been discarded due to a lack of storage space.
 *
 * Register: \a ANA:ANA:LEARNDISC
 */
#define VTSS_ANA_ANA_LEARNDISC               VTSS_IOREG(VTSS_TO_ANA,0x36d)


/** 
 * \brief Analyzer Configuration
 *
 * \details
 * Register: \a ANA:ANA:AGENCTRL
 */
#define VTSS_ANA_ANA_AGENCTRL                VTSS_IOREG(VTSS_TO_ANA,0x36e)

/** 
 * \brief
 * Mask used to enable shared learning among multiple VLANs. The FID value
 * used in learning and MAC table lookup is calculated as: FID = VID and
 * (not FID_MASK) By default, FID_MASK is set to all-zeros, corresponding
 * to independent VLAN learning. In this case FID becomes identical to VID.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_AGENCTRL . FID_MASK
 */
#define  VTSS_F_ANA_ANA_AGENCTRL_FID_MASK(x)  VTSS_ENCODE_BITFIELD(x,12,12)
#define  VTSS_M_ANA_ANA_AGENCTRL_FID_MASK     VTSS_ENCODE_BITMASK(12,12)
#define  VTSS_X_ANA_ANA_AGENCTRL_FID_MASK(x)  VTSS_EXTRACT_BITFIELD(x,12,12)

/** 
 * \brief
 * Do not react to flags found in the DMAC entry or the corresponding flags
 * for flooded frames (FLOOD_IGNORE_VLAN).
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_AGENCTRL . IGNORE_DMAC_FLAGS
 */
#define  VTSS_F_ANA_ANA_AGENCTRL_IGNORE_DMAC_FLAGS  VTSS_BIT(11)

/** 
 * \brief
 * Do not react to flags found in the SMAC entry. Note, the IGNORE_VLAN
 * flag is not checked for SMAC entries.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_AGENCTRL . IGNORE_SMAC_FLAGS
 */
#define  VTSS_F_ANA_ANA_AGENCTRL_IGNORE_SMAC_FLAGS  VTSS_BIT(10)

/** 
 * \brief
 * Flood frames using the lowest 27 bits of DMAC as destination port mask.
 * This is only added for testing purposes.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_AGENCTRL . FLOOD_SPECIAL
 */
#define  VTSS_F_ANA_ANA_AGENCTRL_FLOOD_SPECIAL  VTSS_BIT(9)

/** 
 * \brief
 * VLAN mask is not applied to flooded frames.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_AGENCTRL . FLOOD_IGNORE_VLAN
 */
#define  VTSS_F_ANA_ANA_AGENCTRL_FLOOD_IGNORE_VLAN  VTSS_BIT(8)

/** 
 * \brief
 * Frames destined for the CPU extraction queues are also forwarded to the
 * port set configured in MIRRORPORTS.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_AGENCTRL . MIRROR_CPU
 */
#define  VTSS_F_ANA_ANA_AGENCTRL_MIRROR_CPU   VTSS_BIT(7)

/** 
 * \brief
 * If set, auto-learned stations get the CPU_COPY flag set in the MAC table
 * entry.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_AGENCTRL . LEARN_CPU_COPY
 */
#define  VTSS_F_ANA_ANA_AGENCTRL_LEARN_CPU_COPY  VTSS_BIT(6)

/** 
 * \brief
 * If set, auto-learned stations get the SRC_KILL flag set in the MAC table
 * entry.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_AGENCTRL . LEARN_SRC_KILL
 */
#define  VTSS_F_ANA_ANA_AGENCTRL_LEARN_SRC_KILL  VTSS_BIT(5)

/** 
 * \brief
 * If set, auto-learned stations get the IGNORE_VLAN flag set in the MAC
 * table entry.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_AGENCTRL . LEARN_IGNORE_VLAN
 */
#define  VTSS_F_ANA_ANA_AGENCTRL_LEARN_IGNORE_VLAN  VTSS_BIT(4)

/** 
 * \brief
 * If set, CPU injected frames are never sent back to the CPU.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_AGENCTRL . CPU_CPU_KILL_ENA
 */
#define  VTSS_F_ANA_ANA_AGENCTRL_CPU_CPU_KILL_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Counter mode for the Rx priority counters for green frames
 * (CNT_RX_GREEN_PRIO_x)
 *
 * \details 
 * 0: Count octets
 * 1: Count frames
 *
 * Field: ::VTSS_ANA_ANA_AGENCTRL . GREEN_COUNT_MODE
 */
#define  VTSS_F_ANA_ANA_AGENCTRL_GREEN_COUNT_MODE  VTSS_BIT(2)

/** 
 * \brief
 * Counter mode for the Rx priority counters for yellow frames
 * (CNT_RX_YELLOW_PRIO_x)
 *
 * \details 
 * 0: Count octets
 * 1: Count frames
 *
 * Field: ::VTSS_ANA_ANA_AGENCTRL . YELLOW_COUNT_MODE
 */
#define  VTSS_F_ANA_ANA_AGENCTRL_YELLOW_COUNT_MODE  VTSS_BIT(1)

/** 
 * \brief
 * Counter mode for the Rx priority counters for red frames
 * (CNT_RX_RED_PRIO_x)
 *
 * \details 
 * 0: Count octets
 * 1: Count frames
 *
 * Field: ::VTSS_ANA_ANA_AGENCTRL . RED_COUNT_MODE
 */
#define  VTSS_F_ANA_ANA_AGENCTRL_RED_COUNT_MODE  VTSS_BIT(0)


/** 
 * \brief Mirror Target Ports
 *
 * \details
 * Register: \a ANA:ANA:MIRRORPORTS
 */
#define VTSS_ANA_ANA_MIRRORPORTS             VTSS_IOREG(VTSS_TO_ANA,0x36f)

/** 
 * \brief
 * Ports set in this mask receive a mirror copy. If CPU is included in mask
 * (bit 26 set), then the frame is copied to CPU extraction queue
 * CPUQ_CFG.CPUQ_MIRROR.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_MIRRORPORTS . MIRRORPORTS
 */
#define  VTSS_F_ANA_ANA_MIRRORPORTS_MIRRORPORTS(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_ANA_ANA_MIRRORPORTS_MIRRORPORTS     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_ANA_ANA_MIRRORPORTS_MIRRORPORTS(x)  VTSS_EXTRACT_BITFIELD(x,0,27)


/** 
 * \brief Egress Mirror Mask
 *
 * \details
 * Register: \a ANA:ANA:EMIRRORPORTS
 */
#define VTSS_ANA_ANA_EMIRRORPORTS            VTSS_IOREG(VTSS_TO_ANA,0x370)

/** 
 * \brief
 * Frames forwarded to ports in this mask are mirrored to the port set
 * configured in MIRRORPORTS (i.e. egress port mirroring).
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_EMIRRORPORTS . EMIRRORPORTS
 */
#define  VTSS_F_ANA_ANA_EMIRRORPORTS_EMIRRORPORTS(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_ANA_ANA_EMIRRORPORTS_EMIRRORPORTS     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_ANA_ANA_EMIRRORPORTS_EMIRRORPORTS(x)  VTSS_EXTRACT_BITFIELD(x,0,27)


/** 
 * \brief Standard flooding configuration
 *
 * \details
 * Register: \a ANA:ANA:FLOODING
 */
#define VTSS_ANA_ANA_FLOODING                VTSS_IOREG(VTSS_TO_ANA,0x371)

/** 
 * \brief
 * Set the PGID mask to use when flooding unknown unicast frames.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_FLOODING . FLD_UNICAST
 */
#define  VTSS_F_ANA_ANA_FLOODING_FLD_UNICAST(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_ANA_ANA_FLOODING_FLD_UNICAST     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_ANA_ANA_FLOODING_FLD_UNICAST(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/** 
 * \brief
 * Set the PGID mask to use when flooding unknown broadcast frames.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_FLOODING . FLD_BROADCAST
 */
#define  VTSS_F_ANA_ANA_FLOODING_FLD_BROADCAST(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_ANA_ANA_FLOODING_FLD_BROADCAST     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_ANA_ANA_FLOODING_FLD_BROADCAST(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Set the PGID mask to use when flooding unknown multicast frames (except
 * IP multicasts).
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_FLOODING . FLD_MULTICAST
 */
#define  VTSS_F_ANA_ANA_FLOODING_FLD_MULTICAST(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_ANA_ANA_FLOODING_FLD_MULTICAST     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_ANA_ANA_FLOODING_FLD_MULTICAST(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Flooding configuration for IP multicasts
 *
 * \details
 * Register: \a ANA:ANA:FLOODING_IPMC
 */
#define VTSS_ANA_ANA_FLOODING_IPMC           VTSS_IOREG(VTSS_TO_ANA,0x372)

/** 
 * \brief
 * Set the PGID mask to use when flooding unknown IPv4 Multicast Control
 * frames.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_FLOODING_IPMC . FLD_MC4_CTRL
 */
#define  VTSS_F_ANA_ANA_FLOODING_IPMC_FLD_MC4_CTRL(x)  VTSS_ENCODE_BITFIELD(x,18,6)
#define  VTSS_M_ANA_ANA_FLOODING_IPMC_FLD_MC4_CTRL     VTSS_ENCODE_BITMASK(18,6)
#define  VTSS_X_ANA_ANA_FLOODING_IPMC_FLD_MC4_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,18,6)

/** 
 * \brief
 * Set the PGID mask to use when flooding unknown IPv4 Multicast Data
 * frames.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_FLOODING_IPMC . FLD_MC4_DATA
 */
#define  VTSS_F_ANA_ANA_FLOODING_IPMC_FLD_MC4_DATA(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_ANA_ANA_FLOODING_IPMC_FLD_MC4_DATA     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_ANA_ANA_FLOODING_IPMC_FLD_MC4_DATA(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/** 
 * \brief
 * Set the PGID mask to use when flooding unknown IPv6 Multicast Control
 * frames.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_FLOODING_IPMC . FLD_MC6_CTRL
 */
#define  VTSS_F_ANA_ANA_FLOODING_IPMC_FLD_MC6_CTRL(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_ANA_ANA_FLOODING_IPMC_FLD_MC6_CTRL     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_ANA_ANA_FLOODING_IPMC_FLD_MC6_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Set the PGID mask to use when flooding unknown IPv6 Multicast Data
 * frames.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_FLOODING_IPMC . FLD_MC6_DATA
 */
#define  VTSS_F_ANA_ANA_FLOODING_IPMC_FLD_MC6_DATA(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_ANA_ANA_FLOODING_IPMC_FLD_MC6_DATA     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_ANA_ANA_FLOODING_IPMC_FLD_MC6_DATA(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SFlow sampling configuration per port
 *
 * \details
 * Register: \a ANA:ANA:SFLOW_CFG
 *
 * @param ri Replicator: x_SPORT_CNT (??), 0-26
 */
#define VTSS_ANA_ANA_SFLOW_CFG(ri)           VTSS_IOREG(VTSS_TO_ANA,0x373 + (ri))

/** 
 * \brief
 * Probability of a frame being SFLOW sampled. Unit is 1/4096. A value of 0
 * makes 1/4096 of the candidates being forwarded to the SFLOW CPU
 * extraction queue. A values of 4095 makes all candidates being forwarded. 
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_SFLOW_CFG . SF_RATE
 */
#define  VTSS_F_ANA_ANA_SFLOW_CFG_SF_RATE(x)  VTSS_ENCODE_BITFIELD(x,2,12)
#define  VTSS_M_ANA_ANA_SFLOW_CFG_SF_RATE     VTSS_ENCODE_BITMASK(2,12)
#define  VTSS_X_ANA_ANA_SFLOW_CFG_SF_RATE(x)  VTSS_EXTRACT_BITFIELD(x,2,12)

/** 
 * \brief
 * Enable SFLOW sampling of frames received on this port. 
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_SFLOW_CFG . SF_SAMPLE_RX
 */
#define  VTSS_F_ANA_ANA_SFLOW_CFG_SF_SAMPLE_RX  VTSS_BIT(1)

/** 
 * \brief
 * Enable SFLOW sampling of frames transmitted on this port. 
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_SFLOW_CFG . SF_SAMPLE_TX
 */
#define  VTSS_F_ANA_ANA_SFLOW_CFG_SF_SAMPLE_TX  VTSS_BIT(0)

/**
 * Register Group: \a ANA:ANA_TABLES
 *
 * Not documented
 */


/** 
 * \brief Station Move Logger
 *
 * \details
 * Register: \a ANA:ANA_TABLES:ANMOVED
 */
#define VTSS_ANA_ANA_TABLES_ANMOVED          VTSS_IOREG(VTSS_TO_ANA,0x46b)

/** 
 * \brief
 * Sticky bit set when a station has been learned on a port while already
 * learned on another port (i.e. port move). The register is cleared by
 * writing 1 to the bits to be cleared. This mask can be used to detect
 * topology problems in the network, where stations are learned on multiple
 * ports repeatedly. If some bits in this register get asserted repeatedly,
 * the ports can be shut down, or management warnings can be issued.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_ANMOVED . ANMOVED
 */
#define  VTSS_F_ANA_ANA_TABLES_ANMOVED_ANMOVED(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_ANA_ANA_TABLES_ANMOVED_ANMOVED     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_ANA_ANA_TABLES_ANMOVED_ANMOVED(x)  VTSS_EXTRACT_BITFIELD(x,0,27)


/** 
 * \brief MAC Address High
 *
 * \details
 * Register: \a ANA:ANA_TABLES:MACHDATA
 */
#define VTSS_ANA_ANA_TABLES_MACHDATA         VTSS_IOREG(VTSS_TO_ANA,0x46c)

/** 
 * \brief
 * VID used in MAC table operations through MACACCESS. For read operations,
 * the VID value is returned in this field.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_MACHDATA . VID
 */
#define  VTSS_F_ANA_ANA_TABLES_MACHDATA_VID(x)  VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_ANA_ANA_TABLES_MACHDATA_VID     VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_ANA_ANA_TABLES_MACHDATA_VID(x)  VTSS_EXTRACT_BITFIELD(x,16,12)

/** 
 * \brief
 * Most significant 16 MAC address bits used in MAC table operations
 * through MACACCESS.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_MACHDATA . MACHDATA
 */
#define  VTSS_F_ANA_ANA_TABLES_MACHDATA_MACHDATA(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ANA_ANA_TABLES_MACHDATA_MACHDATA     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ANA_ANA_TABLES_MACHDATA_MACHDATA(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief MAC Address Low
 *
 * \details
 * Register: \a ANA:ANA_TABLES:MACLDATA
 */
#define VTSS_ANA_ANA_TABLES_MACLDATA         VTSS_IOREG(VTSS_TO_ANA,0x46d)


/** 
 * \brief MAC Table Command
 *
 * \details
 * This register is used for updating or reading the MAC table from the
 * CPU.
 * The command (MAC_TABLE_CMD) selects between different operations and
 * uses the following encoding:
 *     000 - IDLE:
 *     The previous operation has completed.
 *     
 *     001 - LEARN:
 *     Insert/learn new entry in MAC table. Position given by (MAC, VID) in
 * MACHDATA and MACLDATA.
 *     
 *     010 - FORGET:
 *     Delete/unlearn entry given by (MAC, VID) in MACHDATA and MACLDATA. 
 *     Both locked and unlocked entries are deleted.
 *     
 *     011 - AGE:
 *     Start an age scan on the MAC table.
 *     
 *     100 - GET_NEXT:
 *     Get the smallest entry in the MAC table numerically larger than the
 * (MAC, VID) specified in MACHDATA and MACLDATA. The VID and MAC are
 * evaluated as a 60-bit number with the VID being most significant.
 *     
 *     101 - INIT:
 *     Table is initialized (completely cleared).
 *     
 *     110 - READ:
 *     The READ command is divided into two modes: Direct mode and indirect
 * mode.
 *     Direct mode (read):
 *     With MACACCESS.VALID cleared, the entry pointed to by MACTINDX.INDEX
 * (row) and MACTINDX.BUCKET (column) is read.
 *     Indirect mode (lookup):
 *     With MACACCESS.VALID set, the entry pointed to by (MAC, VID) in the
 * MACHDATA and MACLDATA is read.
 *     
 *     111 - WRITE
 *     Write entry. Address of the entry is specified in MACTINDX.INDEX
 * (row) and MACTINDX.BUCKET (column).
 *     An existing entry (locked or unlocked) is overwritten.
 *     
 * The MAC_TABLE_CMD must be IDLE before a new command can be issued.
 * The AGE and CLEAR commands run for approximately 50 us. The other
 * commands execute immediately.
 *     
 * The flags IGNORE_VLAN and MAC_CPU_COPY are ignored for DMAC lookup if
 * AGENCTRL.IGNORE_DMAC_FLAGS is set. 
 * The flags SRC_KILL and MAC_CPU_COPY are ignored for SMAC lookup if
 * AGENCTRL.IGNORE_SMAC_FLAGS is set.
 *
 * Register: \a ANA:ANA_TABLES:MACACCESS
 */
#define VTSS_ANA_ANA_TABLES_MACACCESS        VTSS_IOREG(VTSS_TO_ANA,0x46e)

/** 
 * \brief
 * Bits 24:22 in the destination port mask for IPv6 entries.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_MACACCESS . IP6_MASK
 */
#define  VTSS_F_ANA_ANA_TABLES_MACACCESS_IP6_MASK(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_ANA_ANA_TABLES_MACACCESS_IP6_MASK     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_ANA_ANA_TABLES_MACACCESS_IP6_MASK(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/** 
 * \brief
 * Frames matching this entry are copied  to the CPU extraction queue
 * CPUQ_CFG.CPUQ_MAC. Applies to both SMAC and DMAC lookup.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_MACACCESS . MAC_CPU_COPY
 */
#define  VTSS_F_ANA_ANA_TABLES_MACACCESS_MAC_CPU_COPY  VTSS_BIT(15)

/** 
 * \brief
 * Frames matching this entry are discarded. Applies only to the SMAC
 * lookup. For discarding frames based on the DMAC lookup a NULL PGID mask
 * can be used.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_MACACCESS . SRC_KILL
 */
#define  VTSS_F_ANA_ANA_TABLES_MACACCESS_SRC_KILL  VTSS_BIT(14)

/** 
 * \brief
 * The VLAN mask is ignored for this destination. Applies only to DMAC
 * lookup.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_MACACCESS . IGNORE_VLAN
 */
#define  VTSS_F_ANA_ANA_TABLES_MACACCESS_IGNORE_VLAN  VTSS_BIT(13)

/** 
 * \brief
 * This flag is set on every aging run. Entry is removed if flag is already
 * set. The flag is cleared when the entry is target for a SMAC lookup.
 * Locked entries will not be removed. Bit is for IPv6 Multicast used for
 * port 25.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_MACACCESS . AGED_FLAG
 */
#define  VTSS_F_ANA_ANA_TABLES_MACACCESS_AGED_FLAG  VTSS_BIT(12)

/** 
 * \brief
 * Entry is valid.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_MACACCESS . VALID
 */
#define  VTSS_F_ANA_ANA_TABLES_MACACCESS_VALID  VTSS_BIT(11)

/** 
 * \brief
 * Type of entry:
 *
 * \details 
 * 0: Normal entry eligible for aging
 * 1: Locked entry. Entry will not be removed by aging
 * 2: IPv4 Multicast entry. Full portset in mac record
 * 3: IPv6 Multicast entry. Full portset in mac record
 *
 * Field: ::VTSS_ANA_ANA_TABLES_MACACCESS . ENTRY_TYPE
 */
#define  VTSS_F_ANA_ANA_TABLES_MACACCESS_ENTRY_TYPE(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_ANA_ANA_TABLES_MACACCESS_ENTRY_TYPE     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_ANA_ANA_TABLES_MACACCESS_ENTRY_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/** 
 * \brief
 * Index for the destination masks table (PGID). For unicasts, this is a
 * number from 0-EXB_PORT_CNT_MINUS_ONE.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_MACACCESS . DEST_IDX
 */
#define  VTSS_F_ANA_ANA_TABLES_MACACCESS_DEST_IDX(x)  VTSS_ENCODE_BITFIELD(x,3,6)
#define  VTSS_M_ANA_ANA_TABLES_MACACCESS_DEST_IDX     VTSS_ENCODE_BITMASK(3,6)
#define  VTSS_X_ANA_ANA_TABLES_MACACCESS_DEST_IDX(x)  VTSS_EXTRACT_BITFIELD(x,3,6)

/** 
 * \brief
 * MAC Table Command. See below.

 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_MACACCESS . MAC_TABLE_CMD
 */
#define  VTSS_F_ANA_ANA_TABLES_MACACCESS_MAC_TABLE_CMD(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_ANA_TABLES_MACACCESS_MAC_TABLE_CMD     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_ANA_TABLES_MACACCESS_MAC_TABLE_CMD(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief MAC Table Index
 *
 * \details
 * Register: \a ANA:ANA_TABLES:MACTINDX
 */
#define VTSS_ANA_ANA_TABLES_MACTINDX         VTSS_IOREG(VTSS_TO_ANA,0x46f)

/** 
 * \brief
 * Selects one of the four MAC table entries in a row. The row is addressed
 * with the INDEX field. 
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_MACTINDX . BUCKET
 */
#define  VTSS_F_ANA_ANA_TABLES_MACTINDX_BUCKET(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_ANA_ANA_TABLES_MACTINDX_BUCKET     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_ANA_ANA_TABLES_MACTINDX_BUCKET(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/** 
 * \brief
 * The index selects one of the 2048 MAC table rows. Within a row the entry
 * is addressed by the BUCKET field
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_MACTINDX . M_INDEX
 */
#define  VTSS_F_ANA_ANA_TABLES_MACTINDX_M_INDEX(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_ANA_ANA_TABLES_MACTINDX_M_INDEX     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_ANA_ANA_TABLES_MACTINDX_M_INDEX(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/** 
 * \brief VLAN Table Command
 *
 * \details
 * The VLAN_TBL_CMD field of this register is used for updating and reading
 * the VLAN table. The command (VLAN_TBL_CMD) selects between different
 * operations and uses the following encoding:
 *   00 - IDLE:
 *   The previous operation has completed.
 * 
 *   01 - READ:
 *   The VLAN table entry set in VLANTIDX.INDEX is returned in
 * VLANACCESS.VLAN_PORT_MASK and the VLAN flags in VLANTIDX.
 * 
 *   10 - WRITE:
 *   The VLAN table entry pointed to by VLANTIDX.INDEX is updated with
 * VLANACCESS.VLAN_PORT_MASK and the VLAN flags in VLANTIDX.
 * 
 *   11 - INIT:
 *   The VLAN table is initialized to default values (all ports are members
 * of all VLANs).
 * 
 * The VLAN_TBL_CMD must be IDLE before a new command can be issued. The
 * INIT command run for approximately 50 us whereas the other commands
 * execute immediately. When an operation has completed, VLAN_TBL_CMD
 * changes to IDLE.
 *
 * Register: \a ANA:ANA_TABLES:VLANACCESS
 */
#define VTSS_ANA_ANA_TABLES_VLANACCESS       VTSS_IOREG(VTSS_TO_ANA,0x470)

/** 
 * \brief
 * Frames classified to this VLAN can only be sent to ports in this mask.
 * Note that the CPU port module is always member of all VLANs and its VLAN
 * membership can therefore not be configured through this mask.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_VLANACCESS . VLAN_PORT_MASK
 */
#define  VTSS_F_ANA_ANA_TABLES_VLANACCESS_VLAN_PORT_MASK(x)  VTSS_ENCODE_BITFIELD(x,2,27)
#define  VTSS_M_ANA_ANA_TABLES_VLANACCESS_VLAN_PORT_MASK     VTSS_ENCODE_BITMASK(2,27)
#define  VTSS_X_ANA_ANA_TABLES_VLANACCESS_VLAN_PORT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,2,27)

/** 
 * \brief
 * VLAN Table Command.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_VLANACCESS . VLAN_TBL_CMD
 */
#define  VTSS_F_ANA_ANA_TABLES_VLANACCESS_VLAN_TBL_CMD(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ANA_ANA_TABLES_VLANACCESS_VLAN_TBL_CMD     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ANA_ANA_TABLES_VLANACCESS_VLAN_TBL_CMD(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief VLAN Table Index
 *
 * \details
 * Register: \a ANA:ANA_TABLES:VLANTIDX
 */
#define VTSS_ANA_ANA_TABLES_VLANTIDX         VTSS_IOREG(VTSS_TO_ANA,0x471)

/** 
 * \brief
 * If set, a VLAN is a private VLAN. See PRIV_VLAN_MASK for details.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_VLANTIDX . VLAN_PRIV_VLAN
 */
#define  VTSS_F_ANA_ANA_TABLES_VLANTIDX_VLAN_PRIV_VLAN  VTSS_BIT(15)

/** 
 * \brief
 * Disable learning for this VLAN.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_VLANTIDX . VLAN_LEARN_DISABLED
 */
#define  VTSS_F_ANA_ANA_TABLES_VLANTIDX_VLAN_LEARN_DISABLED  VTSS_BIT(14)

/** 
 * \brief
 * If set, all frames classified to this VLAN are mirrored to the port set
 * configured in MIRRORPORTS.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_VLANTIDX . VLAN_MIRROR
 */
#define  VTSS_F_ANA_ANA_TABLES_VLANTIDX_VLAN_MIRROR  VTSS_BIT(13)

/** 
 * \brief
 * If set, VLAN ingress filtering is enabled for this VLAN. If set, a
 * frame's ingress port must be member of the frame's VLAN, otherwise the
 * frame is discarded.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_VLANTIDX . VLAN_SRC_CHK
 */
#define  VTSS_F_ANA_ANA_TABLES_VLANTIDX_VLAN_SRC_CHK  VTSS_BIT(12)

/** 
 * \brief
 * Index used to select VLAN table entry for read/write operations (see
 * VLANACCESS). This value equals the VID.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_VLANTIDX . V_INDEX
 */
#define  VTSS_F_ANA_ANA_TABLES_VLANTIDX_V_INDEX(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_ANA_ANA_TABLES_VLANTIDX_V_INDEX     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_ANA_ANA_TABLES_VLANTIDX_V_INDEX(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Port Group Identifiers
 *
 * \details
 * Three port masks are applied to all frames, allowing transmission to a
 * port if the corresponding bit is set in all masks.
 * 0-63:     A mask is applied based on destination analysis
 * 64-79:   A mask is applied based on aggregation analysis
 * 80-106: A mask is applied based on source port analysis
 * 
 * Destination analysis:
 * There are 64 destination masks in total. By default, the first 26 port
 * masks only have the bit corresponding to their port number set. These
 * masks should not be changed, except for aggregation.
 * 
 * The remaining destination masks are set to 0 by default and are
 * available for use for Layer-2 multicasts and flooding (See FLOODING and
 * FLOODING_IPMC).
 * 
 * Aggregation analysis:
 * The aggregation port masks are used to select only one port within each
 * aggregation group. These 16 masks must be setup to select only one port
 * in each aggregated port group. 
 * For ports, which are not part of any aggregation group, the
 * corresponding bits in all 16 masks must be set. 
 * I.e. if no aggregation is configured, all masks must be set to all-ones.
 * 
 * The aggregation mask used for the forwarding of a given frame is
 * selected by the frame's aggregation code (see AGGRCTRL).
 * 
 * Source port analysis:
 * The source port masks are used to prevent frames from being looped back
 * to the ports on which they were received, and must be updated according
 * to the
 * aggregation configuration. A frame that is received on port n, uses mask
 * 80+n as a mask to filter out destination ports to avoid loopback, or to
 * facilitate port grouping (port-based VLANs). The default values are that
 * all bits are set except for the index number.
 *
 * Register: \a ANA:ANA_TABLES:PGID
 *
 * @param ri Register: PGID (??), 0-106
 */
#define VTSS_ANA_ANA_TABLES_PGID(ri)         VTSS_IOREG(VTSS_TO_ANA,0x400 + (ri))

/** 
 * \brief
 * When a mask is chosen, bit N must be set for the frame to be transmitted
 * on port N.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_PGID . PGID
 */
#define  VTSS_F_ANA_ANA_TABLES_PGID_PGID(x)   VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_ANA_ANA_TABLES_PGID_PGID      VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_ANA_ANA_TABLES_PGID_PGID(x)   VTSS_EXTRACT_BITFIELD(x,0,27)

/** 
 * \brief
 * CPU extraction queue used when CPU port is enabled in PGID. Only
 * applicable for the destination analysis.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_PGID . CPUQ_DST_PGID
 */
#define  VTSS_F_ANA_ANA_TABLES_PGID_CPUQ_DST_PGID(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_ANA_ANA_TABLES_PGID_CPUQ_DST_PGID     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_ANA_ANA_TABLES_PGID_CPUQ_DST_PGID(x)  VTSS_EXTRACT_BITFIELD(x,27,3)


/** 
 * \brief MAC Table Entry Limits
 *
 * \details
 * Register: \a ANA:ANA_TABLES:ENTRYLIM
 *
 * @param ri Replicator: x_SPORT_CNT (??), 0-26
 */
#define VTSS_ANA_ANA_TABLES_ENTRYLIM(ri)     VTSS_IOREG(VTSS_TO_ANA,0x480 + (ri))

/** 
 * \brief
 * Maximum number of unlocked entries in the MAC table learned on this
 * port.
 * Locked entries and IPMC entries do not obey this limit.
 * Both auto-learned and unlocked CPU-learned entries obey this limit.
 *
 * \details 
 * 0: 1 entry
 * 1: 2 entries
 * n: 2**n entries
 * >12: 8192 entries
 *
 * Field: ::VTSS_ANA_ANA_TABLES_ENTRYLIM . ENTRYLIM
 */
#define  VTSS_F_ANA_ANA_TABLES_ENTRYLIM_ENTRYLIM(x)  VTSS_ENCODE_BITFIELD(x,14,4)
#define  VTSS_M_ANA_ANA_TABLES_ENTRYLIM_ENTRYLIM     VTSS_ENCODE_BITMASK(14,4)
#define  VTSS_X_ANA_ANA_TABLES_ENTRYLIM_ENTRYLIM(x)  VTSS_EXTRACT_BITFIELD(x,14,4)

/** 
 * \brief
 * Current number of unlocked MAC table entries learned on this port.
 *
 * \details 
 * Field: ::VTSS_ANA_ANA_TABLES_ENTRYLIM . ENTRYSTAT
 */
#define  VTSS_F_ANA_ANA_TABLES_ENTRYLIM_ENTRYSTAT(x)  VTSS_ENCODE_BITFIELD(x,0,14)
#define  VTSS_M_ANA_ANA_TABLES_ENTRYLIM_ENTRYSTAT     VTSS_ENCODE_BITMASK(0,14)
#define  VTSS_X_ANA_ANA_TABLES_ENTRYLIM_ENTRYSTAT(x)  VTSS_EXTRACT_BITFIELD(x,0,14)


/** 
 * \brief PTP Identifiers 63-32
 *
 * \details
 * Register: \a ANA:ANA_TABLES:PTP_ID_HIGH
 */
#define VTSS_ANA_ANA_TABLES_PTP_ID_HIGH      VTSS_IOREG(VTSS_TO_ANA,0x472)


/** 
 * \brief PTP Identifiers 31-0
 *
 * \details
 * Register: \a ANA:ANA_TABLES:PTP_ID_LOW
 */
#define VTSS_ANA_ANA_TABLES_PTP_ID_LOW       VTSS_IOREG(VTSS_TO_ANA,0x473)

/**
 * Register Group: \a ANA:PORT
 *
 * Per port configurations for Classifier
 */


/** 
 * \brief Port VLAN configuration
 *
 * \details
 * Register: \a ANA:PORT:VLAN_CFG
 *
 * @param gi Register: PORT (??), 0-26
 */
#define VTSS_ANA_PORT_VLAN_CFG(gi)           VTSS_IOREG_IX(VTSS_TO_ANA,0x0,gi,32,0,0)

/** 
 * \brief
 * Enable VLAN awareness. If set, Q-tag headers are processed during the
 * basic VLAN classification. If cleared, Q-tag headers are ignored during
 * the basic VLAN classification.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_VLAN_CFG . VLAN_AWARE_ENA
 */
#define  VTSS_F_ANA_PORT_VLAN_CFG_VLAN_AWARE_ENA  VTSS_BIT(20)

/** 
 * \brief
 * Number of tag headers to remove from ingress frame.
 *
 * \details 
 * 0: Keep all tags.
 * 1: Pop up to 1 tag (outer tag if available).
 * 2: Pop up to 2 tags (outer and inner tag if available).
 * 3: Reserved.

 *
 * Field: ::VTSS_ANA_PORT_VLAN_CFG . VLAN_POP_CNT
 */
#define  VTSS_F_ANA_PORT_VLAN_CFG_VLAN_POP_CNT(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_ANA_PORT_VLAN_CFG_VLAN_POP_CNT     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_ANA_PORT_VLAN_CFG_VLAN_POP_CNT(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/** 
 * \brief
 * Set if the inner Q-tag must be used instead of the outer Q-tag. If the
 * received frame is single tagged, the outer tag is used. This bit
 * influences the VLAN acceptance filter (DROP_CFG), the basic VLAN
 * classification (VLAN_CFG), and the basic QoS classification (QOS_CFG).
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_VLAN_CFG . VLAN_INNER_TAG_ENA
 */
#define  VTSS_F_ANA_PORT_VLAN_CFG_VLAN_INNER_TAG_ENA  VTSS_BIT(17)

/** 
 * \brief
 * Tag Protocol Identifier type for port-based VLAN.
 *
 * \details 
 * 0: C-tag (EtherType = 0x8100)
 * 1: S-tag (EtherType = 0x88A8 or configurable value (VLAN_ETYPE_CFG))
 *
 * Field: ::VTSS_ANA_PORT_VLAN_CFG . VLAN_TAG_TYPE
 */
#define  VTSS_F_ANA_PORT_VLAN_CFG_VLAN_TAG_TYPE  VTSS_BIT(16)

/** 
 * \brief
 * DEI value for port-based VLAN.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_VLAN_CFG . VLAN_DEI
 */
#define  VTSS_F_ANA_PORT_VLAN_CFG_VLAN_DEI    VTSS_BIT(15)

/** 
 * \brief
 * PCP value for port-based VLAN.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_VLAN_CFG . VLAN_PCP
 */
#define  VTSS_F_ANA_PORT_VLAN_CFG_VLAN_PCP(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_ANA_PORT_VLAN_CFG_VLAN_PCP     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_ANA_PORT_VLAN_CFG_VLAN_PCP(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/** 
 * \brief
 * VID value for port-based VLAN.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_VLAN_CFG . VLAN_VID
 */
#define  VTSS_F_ANA_PORT_VLAN_CFG_VLAN_VID(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_ANA_PORT_VLAN_CFG_VLAN_VID     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_ANA_PORT_VLAN_CFG_VLAN_VID(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief VLAN acceptance filtering
 *
 * \details
 * Register: \a ANA:PORT:DROP_CFG
 *
 * @param gi Register: PORT (??), 0-26
 */
#define VTSS_ANA_PORT_DROP_CFG(gi)           VTSS_IOREG_IX(VTSS_TO_ANA,0x0,gi,32,0,1)

/** 
 * \brief
 * Drop untagged frames.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_DROP_CFG . DROP_UNTAGGED_ENA
 */
#define  VTSS_F_ANA_PORT_DROP_CFG_DROP_UNTAGGED_ENA  VTSS_BIT(6)

/** 
 * \brief
 * Drop S-tagged frames (VID different from 0 and EtherType = 0x88A8 or
 * configurable value (VLAN_ETYPE_CFG)).
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_DROP_CFG . DROP_S_TAGGED_ENA
 */
#define  VTSS_F_ANA_PORT_DROP_CFG_DROP_S_TAGGED_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Drop C-tagged frames (VID different from 0 and EtherType = 0x8100).
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_DROP_CFG . DROP_C_TAGGED_ENA
 */
#define  VTSS_F_ANA_PORT_DROP_CFG_DROP_C_TAGGED_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Drop S-tagged frames (VID=0 and EtherType = 0x88A8 or configurable value
 * (VLAN_ETYPE_CFG)).
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_DROP_CFG . DROP_PRIO_S_TAGGED_ENA
 */
#define  VTSS_F_ANA_PORT_DROP_CFG_DROP_PRIO_S_TAGGED_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Drop priority C-tagged frames (VID=0 and EtherType = 0x8100).
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_DROP_CFG . DROP_PRIO_C_TAGGED_ENA
 */
#define  VTSS_F_ANA_PORT_DROP_CFG_DROP_PRIO_C_TAGGED_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Drop frames with source or destination MAC address equal to
 * 0x000000000000.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_DROP_CFG . DROP_NULL_MAC_ENA
 */
#define  VTSS_F_ANA_PORT_DROP_CFG_DROP_NULL_MAC_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Drop frames with multicast source MAC address.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_DROP_CFG . DROP_MC_SMAC_ENA
 */
#define  VTSS_F_ANA_PORT_DROP_CFG_DROP_MC_SMAC_ENA  VTSS_BIT(0)


/** 
 * \brief QoS and DSCP configuration
 *
 * \details
 * Register: \a ANA:PORT:QOS_CFG
 *
 * @param gi Register: PORT (??), 0-26
 */
#define VTSS_ANA_PORT_QOS_CFG(gi)            VTSS_IOREG_IX(VTSS_TO_ANA,0x0,gi,32,0,2)

/** 
 * \brief
 * Default drop precendence level.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_QOS_CFG . DP_DEFAULT_VAL
 */
#define  VTSS_F_ANA_PORT_QOS_CFG_DP_DEFAULT_VAL  VTSS_BIT(8)

/** 
 * \brief
 * Default QoS class.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_QOS_CFG . QOS_DEFAULT_VAL
 */
#define  VTSS_F_ANA_PORT_QOS_CFG_QOS_DEFAULT_VAL(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_ANA_PORT_QOS_CFG_QOS_DEFAULT_VAL     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_ANA_PORT_QOS_CFG_QOS_DEFAULT_VAL(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * If set, the DP level and QoS class can be based on DSCP values.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_QOS_CFG . QOS_DSCP_ENA
 */
#define  VTSS_F_ANA_PORT_QOS_CFG_QOS_DSCP_ENA  VTSS_BIT(4)

/** 
 * \brief
 * If set, DP level and QoS class can be based on the PCP and DEI bits for
 * tagged frames.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_QOS_CFG . QOS_PCP_ENA
 */
#define  VTSS_F_ANA_PORT_QOS_CFG_QOS_PCP_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Set if the DSCP value must be translated before using the DSCP value. If
 * set, the translated DSCP value is given from
 * DSCP_CFG[DSCP].DSCP_TRANSLATE_VAL.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_QOS_CFG . DSCP_TRANSLATE_ENA
 */
#define  VTSS_F_ANA_PORT_QOS_CFG_DSCP_TRANSLATE_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Configure which DSCP values to rewrite based on DP level and QoS class.
 * If the DSCP value is to be rewritten, then the new DSCP =
 * DSCP_REWR_CFG[8*DP level + QoS class].DSCP_QOS_REWR_VAL.
 *
 * \details 
 * 0: Rewrite none.
 * 1: Rewrite if DSCP=0
 * 2: Rewrite for selected values configured in
 * DSCP_CFG[DSCP].DSCP_REWR_ENA.
 * 3: Rewrite all.
 *
 * Field: ::VTSS_ANA_PORT_QOS_CFG . DSCP_REWR_CFG
 */
#define  VTSS_F_ANA_PORT_QOS_CFG_DSCP_REWR_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ANA_PORT_QOS_CFG_DSCP_REWR_CFG     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ANA_PORT_QOS_CFG_DSCP_REWR_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief VCAP configuration
 *
 * \details
 * Register: \a ANA:PORT:VCAP_CFG
 *
 * @param gi Register: PORT (??), 0-26
 */
#define VTSS_ANA_PORT_VCAP_CFG(gi)           VTSS_IOREG_IX(VTSS_TO_ANA,0x0,gi,32,0,3)

/** 
 * \brief
 * If S1 is enabled, each frame received on this port is processed and
 * matched against the entries in the S1 TCAM. Each frame results in three
 * lookups (two lookups to determine classification actions such as VLAN
 * and QoS class, and one lookup to check host identity).
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_VCAP_CFG . S1_ENA
 */
#define  VTSS_F_ANA_PORT_VCAP_CFG_S1_ENA      VTSS_BIT(29)

/** 
 * \brief
 * Set if the destination MAC address and the destination IP address must
 * be passed on to the S1 TCAM instead of the source MAC address and the
 * source IP address. Bit 0 controls destination address information for
 * first lookup in S1. Bit 1 controls destination address information for
 * second lookup in S1. Note that the host identity lookup in S1 always
 * uses soource information.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_VCAP_CFG . S1_DMAC_DIP_ENA
 */
#define  VTSS_F_ANA_PORT_VCAP_CFG_S1_DMAC_DIP_ENA(x)  VTSS_ENCODE_BITFIELD(x,27,2)
#define  VTSS_M_ANA_PORT_VCAP_CFG_S1_DMAC_DIP_ENA     VTSS_ENCODE_BITMASK(27,2)
#define  VTSS_X_ANA_PORT_VCAP_CFG_S1_DMAC_DIP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,27,2)

/** 
 * \brief
 * Set if the inner Q-tag must be passed on to the S1 TCAM instead of the
 * outer Q-tag. For single tagged frames, the outer tag is used. For
 * untagged frames, the port VLAN is used. This bit influences the TPID,
 * VID, PCP, and DEI input to the S1 key generation.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_VCAP_CFG . S1_VLAN_INNER_TAG_ENA
 */
#define  VTSS_F_ANA_PORT_VCAP_CFG_S1_VLAN_INNER_TAG_ENA(x)  VTSS_ENCODE_BITFIELD(x,25,2)
#define  VTSS_M_ANA_PORT_VCAP_CFG_S1_VLAN_INNER_TAG_ENA     VTSS_ENCODE_BITMASK(25,2)
#define  VTSS_X_ANA_PORT_VCAP_CFG_S1_VLAN_INNER_TAG_ENA(x)  VTSS_EXTRACT_BITFIELD(x,25,2)

/** 
 * \brief
 * If set, payload bytes 0, 1, 4, and 6 following the UDP header replaces
 * the source IP address in the S2 IP4_TCP_UDP key for UDP frames. Bit 0
 * controls first lookup in S2 and bit 1 controls second lookup in S2.

 *
 * \details 
 * Field: ::VTSS_ANA_PORT_VCAP_CFG . S2_UDP_PAYLOAD_ENA
 */
#define  VTSS_F_ANA_PORT_VCAP_CFG_S2_UDP_PAYLOAD_ENA(x)  VTSS_ENCODE_BITFIELD(x,23,2)
#define  VTSS_M_ANA_PORT_VCAP_CFG_S2_UDP_PAYLOAD_ENA     VTSS_ENCODE_BITMASK(23,2)
#define  VTSS_X_ANA_PORT_VCAP_CFG_S2_UDP_PAYLOAD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,23,2)

/** 
 * \brief
 * If set, payload bytes 2-7 following the EtherType replaces the source
 * MAC address in the S2 MAC ETYPE key. Payload bytes 0-1 immediately after
 * the EtherType are already available in the key. Bit 0 controls first
 * lookup in S2 and bit 1 controls second lookup in S2.

 *
 * \details 
 * Field: ::VTSS_ANA_PORT_VCAP_CFG . S2_ETYPE_PAYLOAD_ENA
 */
#define  VTSS_F_ANA_PORT_VCAP_CFG_S2_ETYPE_PAYLOAD_ENA(x)  VTSS_ENCODE_BITFIELD(x,21,2)
#define  VTSS_M_ANA_PORT_VCAP_CFG_S2_ETYPE_PAYLOAD_ENA     VTSS_ENCODE_BITMASK(21,2)
#define  VTSS_X_ANA_PORT_VCAP_CFG_S2_ETYPE_PAYLOAD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,21,2)

/** 
 * \brief
 * If S2 is enabled, each frame received on this port is processed and
 * matched against the entries in the S2 TCAM. Each frame results in two
 * lookups to determine both an ingress and an egress action.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_VCAP_CFG . S2_ENA
 */
#define  VTSS_F_ANA_PORT_VCAP_CFG_S2_ENA      VTSS_BIT(20)

/** 
 * \brief
 * If set, MAC_SNAP frames received on this port are treated as MAC_LLC
 * frames when matching in S2.
 * Bit 0 controls the ingress lookup and bit 1 controls the egress lookup.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_VCAP_CFG . S2_SNAP_DIS
 */
#define  VTSS_F_ANA_PORT_VCAP_CFG_S2_SNAP_DIS(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_ANA_PORT_VCAP_CFG_S2_SNAP_DIS     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_ANA_PORT_VCAP_CFG_S2_SNAP_DIS(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/** 
 * \brief
 * If set, MAC_ARP frames received on this port are treated as MAC_ETYPE
 * frames when matching in S2.
 * Bit 0 controls the ingress lookup and bit 1 controls the egress lookup.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_VCAP_CFG . S2_ARP_DIS
 */
#define  VTSS_F_ANA_PORT_VCAP_CFG_S2_ARP_DIS(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_ANA_PORT_VCAP_CFG_S2_ARP_DIS     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_ANA_PORT_VCAP_CFG_S2_ARP_DIS(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * If set, IP_TCPUDP frames received on this port are treated as MAC_ETYPE
 * frames when matching in S2.
 * Bit 0 controls the ingress lookup and bit 1 controls the egress lookup.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_VCAP_CFG . S2_IP_TCPUDP_DIS
 */
#define  VTSS_F_ANA_PORT_VCAP_CFG_S2_IP_TCPUDP_DIS(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_ANA_PORT_VCAP_CFG_S2_IP_TCPUDP_DIS     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_ANA_PORT_VCAP_CFG_S2_IP_TCPUDP_DIS(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * If set, IP_OTHER frames received on this port are treated as MAC_ETYPE
 * frames when matching in S2.
 * Bit 0 controls the ingress lookup and bit 1 controls the egress lookup.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_VCAP_CFG . S2_IP_OTHER_DIS
 */
#define  VTSS_F_ANA_PORT_VCAP_CFG_S2_IP_OTHER_DIS(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_ANA_PORT_VCAP_CFG_S2_IP_OTHER_DIS     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_ANA_PORT_VCAP_CFG_S2_IP_OTHER_DIS(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * If set, IP6_STD frames received on this port are not matched against
 * IP6_STD entries. If S2_IP6_TCPUDP_OTHER_DIS is set, IP6_STD frames are
 * matched against MAC_ETYPE entries. If S2_IP6_TCPUDP_OTHER_DIS is
 * cleared, TCP/UDP IP6_STD frames are matched against IP4_TCPUDP entries,
 * otherwise against IP4_OTHER entries. Bit 0 controls the ingress lookup
 * and bit 1 controls the egress lookup.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_VCAP_CFG . S2_IP6_STD_DIS
 */
#define  VTSS_F_ANA_PORT_VCAP_CFG_S2_IP6_STD_DIS(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_ANA_PORT_VCAP_CFG_S2_IP6_STD_DIS     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_ANA_PORT_VCAP_CFG_S2_IP6_STD_DIS(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * See S2_IP6_STD_DIS for details. 
 * Bit 0 controls the ingress lookup and bit 1 controls the egress lookup.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_VCAP_CFG . S2_IP6_TCPUDP_OTHER_DIS
 */
#define  VTSS_F_ANA_PORT_VCAP_CFG_S2_IP6_TCPUDP_OTHER_DIS(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_ANA_PORT_VCAP_CFG_S2_IP6_TCPUDP_OTHER_DIS     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_ANA_PORT_VCAP_CFG_S2_IP6_TCPUDP_OTHER_DIS(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Default PAG value used as input to S2. The PAG value can be changed by
 * S1 actions.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_VCAP_CFG . PAG_VAL
 */
#define  VTSS_F_ANA_PORT_VCAP_CFG_PAG_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ANA_PORT_VCAP_CFG_PAG_VAL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ANA_PORT_VCAP_CFG_PAG_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Mapping of DEI and PCP to QoS class and drop precedence level
 *
 * \details
 * Register: \a ANA:PORT:QOS_PCP_DEI_MAP_CFG
 *
 * @param gi Register: PORT (??), 0-26
 * @param ri Register: QOS_PCP_DEI_MAP_CFG (??), 0-15
 */
#define VTSS_ANA_PORT_QOS_PCP_DEI_MAP_CFG(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA,0x0,gi,32,ri,4)

/** 
 * \brief
 * Map the frame's PCP and DEI values to a drop precedence level. DP level
 * = QOS_PCP_DEI_MAP_CFG[index].DP_PCP_DEI_VAL, where index = 8*DEI + PCP.
 * Only applicable to tagged frames. The use of Inner or outer tag can be
 * selected using VLAN_CFG.VLAN_INNER_TAG_ENA.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_QOS_PCP_DEI_MAP_CFG . DP_PCP_DEI_VAL
 */
#define  VTSS_F_ANA_PORT_QOS_PCP_DEI_MAP_CFG_DP_PCP_DEI_VAL  VTSS_BIT(3)

/** 
 * \brief
 * Map the frame's PCP and DEI values to a QoS class. QoS class =
 * QOS_PCP_DEI_MAP_CFG[index].QOS_PCP_DEI_VAL, where index = 8*DEI + PCP.
 * Only applicable to tagged frames. The use of Inner or outer tag can be
 * selected using VLAN_CFG.VLAN_INNER_TAG_ENA.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_QOS_PCP_DEI_MAP_CFG . QOS_PCP_DEI_VAL
 */
#define  VTSS_F_ANA_PORT_QOS_PCP_DEI_MAP_CFG_QOS_PCP_DEI_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_PORT_QOS_PCP_DEI_MAP_CFG_QOS_PCP_DEI_VAL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_PORT_QOS_PCP_DEI_MAP_CFG_QOS_PCP_DEI_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief CPU forwarding of special protocols
 *
 * \details
 * Register: \a ANA:PORT:CPU_FWD_CFG
 *
 * @param gi Register: PORT (??), 0-26
 */
#define VTSS_ANA_PORT_CPU_FWD_CFG(gi)        VTSS_IOREG_IX(VTSS_TO_ANA,0x0,gi,32,0,20)

/** 
 * \brief
 * If set, MLD frames are redirected to the CPU.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_CPU_FWD_CFG . CPU_MLD_REDIR_ENA
 */
#define  VTSS_F_ANA_PORT_CPU_FWD_CFG_CPU_MLD_REDIR_ENA  VTSS_BIT(4)

/** 
 * \brief
 * If set, IGMP frames are redirected to the CPU.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_CPU_FWD_CFG . CPU_IGMP_REDIR_ENA
 */
#define  VTSS_F_ANA_PORT_CPU_FWD_CFG_CPU_IGMP_REDIR_ENA  VTSS_BIT(3)

/** 
 * \brief
 * If set, IPv4 multicast control frames (destination IP address in the
 * range 224.0.0.x) are copied to the CPU.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_CPU_FWD_CFG . CPU_IPMC_CTRL_COPY_ENA
 */
#define  VTSS_F_ANA_PORT_CPU_FWD_CFG_CPU_IPMC_CTRL_COPY_ENA  VTSS_BIT(2)

/** 
 * \brief
 * If set, all frames received on this port are copied to the CPU
 * extraction queue given by CPUQ_CFG.CPUQ_SRC_COPY.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_CPU_FWD_CFG . CPU_SRC_COPY_ENA
 */
#define  VTSS_F_ANA_PORT_CPU_FWD_CFG_CPU_SRC_COPY_ENA  VTSS_BIT(1)

/** 
 * \brief
 * If set, All LANs bridge management group frames (DMAC =
 * 01-80-C2-00-00-10) are redirected to the CPU.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_CPU_FWD_CFG . CPU_ALLBRIDGE_REDIR_ENA
 */
#define  VTSS_F_ANA_PORT_CPU_FWD_CFG_CPU_ALLBRIDGE_REDIR_ENA  VTSS_BIT(0)


/** 
 * \brief CPU forwarding of BPDU frames
 *
 * \details
 * Register: \a ANA:PORT:CPU_FWD_BPDU_CFG
 *
 * @param gi Register: PORT (??), 0-26
 */
#define VTSS_ANA_PORT_CPU_FWD_BPDU_CFG(gi)   VTSS_IOREG_IX(VTSS_TO_ANA,0x0,gi,32,0,21)

/** 
 * \brief
 * If bit x is set, BPDU frame (DMAC = 01-80-C2-00-00-0x) is redirected to
 * the CPU.

 *
 * \details 
 * Field: ::VTSS_ANA_PORT_CPU_FWD_BPDU_CFG . BPDU_REDIR_ENA
 */
#define  VTSS_F_ANA_PORT_CPU_FWD_BPDU_CFG_BPDU_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ANA_PORT_CPU_FWD_BPDU_CFG_BPDU_REDIR_ENA     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ANA_PORT_CPU_FWD_BPDU_CFG_BPDU_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief CPU forwarding of GARP frames
 *
 * \details
 * Register: \a ANA:PORT:CPU_FWD_GARP_CFG
 *
 * @param gi Register: PORT (??), 0-26
 */
#define VTSS_ANA_PORT_CPU_FWD_GARP_CFG(gi)   VTSS_IOREG_IX(VTSS_TO_ANA,0x0,gi,32,0,22)

/** 
 * \brief
 * If bit x is set, GARP frame (DMAC = 01-80-C2-00-00-2x) is redirected to
 * the CPU.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_CPU_FWD_GARP_CFG . GARP_REDIR_ENA
 */
#define  VTSS_F_ANA_PORT_CPU_FWD_GARP_CFG_GARP_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ANA_PORT_CPU_FWD_GARP_CFG_GARP_REDIR_ENA     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ANA_PORT_CPU_FWD_GARP_CFG_GARP_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief CPU forwarding of CCM/Link trace frames
 *
 * \details
 * Register: \a ANA:PORT:CPU_FWD_CCM_CFG
 *
 * @param gi Register: PORT (??), 0-26
 */
#define VTSS_ANA_PORT_CPU_FWD_CCM_CFG(gi)    VTSS_IOREG_IX(VTSS_TO_ANA,0x0,gi,32,0,23)

/** 
 * \brief
 * If bit x is set, CCM/Link trace frame (DMAC = 01-80-C2-00-00-3x) is
 * redirected to the CPU.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_CPU_FWD_CCM_CFG . CCM_REDIR_ENA
 */
#define  VTSS_F_ANA_PORT_CPU_FWD_CCM_CFG_CCM_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ANA_PORT_CPU_FWD_CCM_CFG_CCM_REDIR_ENA     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ANA_PORT_CPU_FWD_CCM_CFG_CCM_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Special port configuration
 *
 * \details
 * Register: \a ANA:PORT:PORT_CFG
 *
 * @param gi Register: PORT (??), 0-26
 */
#define VTSS_ANA_PORT_PORT_CFG(gi)           VTSS_IOREG_IX(VTSS_TO_ANA,0x0,gi,32,0,24)

/** 
 * \brief
 * If set, all frames received on this port are mirrored to the port set
 * configured in MIRRORPORTS (ie. ingress mirroring). For egress mirroring,
 * see EMIRRORMASK.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_PORT_CFG . SRC_MIRROR_ENA
 */
#define  VTSS_F_ANA_PORT_PORT_CFG_SRC_MIRROR_ENA  VTSS_BIT(14)

/** 
 * \brief
 * If set, learn frames on an ingress port, which has exceeded the maximum
 * number of MAC table entries are discarded. Forwarding to CPU is still
 * allowed. Note that if LEARN_ENA is cleared, then the LIMIT_DROP is
 * ignored.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_PORT_CFG . LIMIT_DROP
 */
#define  VTSS_F_ANA_PORT_PORT_CFG_LIMIT_DROP  VTSS_BIT(13)

/** 
 * \brief
 * If set, learn frames on an ingress port, which has exceeded the maximum
 * number of MAC table entries are copied to the CPU extraction queue
 * specified in CPUQ_CFG.CPUQ_LRN. Note that if LEARN_ENA is cleared, then
 * the LIMIT_CPU is ignored.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_PORT_CFG . LIMIT_CPU
 */
#define  VTSS_F_ANA_PORT_PORT_CFG_LIMIT_CPU   VTSS_BIT(12)

/** 
 * \brief
 * If set, incoming frames triggering a port move for a locked entry in the
 * MAC table received on this port are discarded. Forwarding to CPU is
 * still allowed. Note that if LEARN_ENA is cleared, then the
 * LOCKED_PORTMOVE_DROP is ignored.

 *
 * \details 
 * Field: ::VTSS_ANA_PORT_PORT_CFG . LOCKED_PORTMOVE_DROP
 */
#define  VTSS_F_ANA_PORT_PORT_CFG_LOCKED_PORTMOVE_DROP  VTSS_BIT(11)

/** 
 * \brief
 * If set, incoming frames triggering a port move for a locked MAC table
 * entry received on this port are copied to the CPU extraction queue
 * specified in CPUQ_CFG.CPUQ_LOCKED_PORTMOVE. Note that if LEARN_ENA is
 * cleared, then the LOCKED_PORTMOVE_CPU is ignored.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_PORT_CFG . LOCKED_PORTMOVE_CPU
 */
#define  VTSS_F_ANA_PORT_PORT_CFG_LOCKED_PORTMOVE_CPU  VTSS_BIT(10)

/** 
 * \brief
 * If set, incoming learn frames received on this port are discarded.
 * Forwarding to CPU is still allowed. Note that if LEARN_ENA is cleared,
 * then the LEARNDROP is ignored.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_PORT_CFG . LEARNDROP
 */
#define  VTSS_F_ANA_PORT_PORT_CFG_LEARNDROP   VTSS_BIT(9)

/** 
 * \brief
 * If set, incoming learn frames received on this port are copied to the
 * CPU extraction queue specified in AGENCTRL.CPUQ_LRN. Note that if
 * LEARN_ENA is cleared, then the LEARNCPU is ignored.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_PORT_CFG . LEARNCPU
 */
#define  VTSS_F_ANA_PORT_PORT_CFG_LEARNCPU    VTSS_BIT(8)

/** 
 * \brief
 * If set, incoming learn frames received on this port are auto learned.
 * Note that if LEARN_ENA is cleared, then the LEARNAUTO is ignored.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_PORT_CFG . LEARNAUTO
 */
#define  VTSS_F_ANA_PORT_PORT_CFG_LEARNAUTO   VTSS_BIT(7)

/** 
 * \brief
 * Enable learning for frames received on this port. If cleared, learning
 * is skipped and any configuration settings in LEARNAUTO, LEARNCPU,
 * LEARNDROP is ignored.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_PORT_CFG . LEARN_ENA
 */
#define  VTSS_F_ANA_PORT_PORT_CFG_LEARN_ENA   VTSS_BIT(6)

/** 
 * \brief
 * Enable reception of frames. If cleared, all incoming frames on this port
 * are discarded by the analyzer.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_PORT_CFG . RECV_ENA
 */
#define  VTSS_F_ANA_PORT_PORT_CFG_RECV_ENA    VTSS_BIT(5)

/** 
 * \brief
 * Logical port number for front port. 
 * If port is not a member of a LLAG, then PORTID must be set to the
 * physical port number.
 * If port is a member of a LLAG, then PORTID must be set to the common
 * PORTID_VAL used for all member ports of the LLAG.

 *
 * \details 
 * Field: ::VTSS_ANA_PORT_PORT_CFG . PORTID_VAL
 */
#define  VTSS_F_ANA_PORT_PORT_CFG_PORTID_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_ANA_PORT_PORT_CFG_PORTID_VAL     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_ANA_PORT_PORT_CFG_PORTID_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief Policer selection
 *
 * \details
 * Register: \a ANA:PORT:POL_CFG
 *
 * @param gi Register: PORT (??), 0-26
 */
#define VTSS_ANA_PORT_POL_CFG(gi)            VTSS_IOREG_IX(VTSS_TO_ANA,0x0,gi,32,0,25)

/** 
 * \brief
 * If set, frames with a DMAC = IEEE reserved addresses (BPDU, GARP, CCM,
 * ALLBRIGDE), which are redirected to the CPU are not policed by any
 * policers. The frames are still counted in the policer buckets.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_POL_CFG . POL_CPU_REDIR_8021
 */
#define  VTSS_F_ANA_PORT_POL_CFG_POL_CPU_REDIR_8021  VTSS_BIT(19)

/** 
 * \brief
 * If set, IGMP and MLD frames, which are redirected to the CPU are not
 * policed by any policers. The frames are still counted in the policers
 * buckets.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_POL_CFG . POL_CPU_REDIR_IP
 */
#define  VTSS_F_ANA_PORT_POL_CFG_POL_CPU_REDIR_IP  VTSS_BIT(18)

/** 
 * \brief
 * Enable port policing. Port policing on port P uses policer P.
 *
 * \details 
 * Field: ::VTSS_ANA_PORT_POL_CFG . PORT_POL_ENA
 */
#define  VTSS_F_ANA_PORT_POL_CFG_PORT_POL_ENA  VTSS_BIT(17)

/** 
 * \brief
 * Bitmask, where bit<n> enables policing of frames classified to QoS class
 * n on this port. Queue policing of QoS class Q on port P uses policer
 * 32+P*8+Q.

 *
 * \details 
 * Field: ::VTSS_ANA_PORT_POL_CFG . QUEUE_POL_ENA
 */
#define  VTSS_F_ANA_PORT_POL_CFG_QUEUE_POL_ENA(x)  VTSS_ENCODE_BITFIELD(x,9,8)
#define  VTSS_M_ANA_PORT_POL_CFG_QUEUE_POL_ENA     VTSS_ENCODE_BITMASK(9,8)
#define  VTSS_X_ANA_PORT_POL_CFG_QUEUE_POL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,8)

/** 
 * \brief
 * Each frame is checked against three policers: PORT(0), QOS/PORT(1) and
 * ACL(2). In this register, a bit set will make updating of a policer be
 * dependant on the result from another. 
 * 
 * Bit<n+3*m> set means: Policer state <n> is checked before policer <m> is
 * updated.
 * 
 * Bit0: Port policer must be open in order to update port policer with
 * frame
 * Bit1: QoS policer must be open in order to update port policer with
 * frame
 * Bit2: ACL policer must be open in order to update port policer with
 * frame
 * 
 * Bit3: Port policer must be open in order to update QoS policer with
 * frame
 * Bit4: QoS policer must be open in order to update QoS policer with frame
 * Bit5: ACL policer must be open in order to update QoS policer with frame
 * 
 * Bit6: Port policer must be open in order to update ACL policer with
 * frame
 * Bit7: QoS policer must be open in order to update ACL policer with frame
 * Bit8: ACL policer must be open in order to update ACL policer with frame

 *
 * \details 
 * Field: ::VTSS_ANA_PORT_POL_CFG . POL_ORDER
 */
#define  VTSS_F_ANA_PORT_POL_CFG_POL_ORDER(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_ANA_PORT_POL_CFG_POL_ORDER     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_ANA_PORT_POL_CFG_POL_ORDER(x)  VTSS_EXTRACT_BITFIELD(x,0,9)

/**
 * Register Group: \a ANA:COMMON
 *
 * Common configurations for Classifier
 */


/** 
 * \brief Aggregation code generation
 *
 * \details
 * Register: \a ANA:COMMON:AGGR_CFG
 */
#define VTSS_ANA_COMMON_AGGR_CFG             VTSS_IOREG(VTSS_TO_ANA,0x38e)

/** 
 * \brief
 * Use pseudo random number for aggregation code. Overrule other
 * contributions.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_AGGR_CFG . AC_RND_ENA
 */
#define  VTSS_F_ANA_COMMON_AGGR_CFG_AC_RND_ENA  VTSS_BIT(6)

/** 
 * \brief
 * Use the lower 12 bits of the destination MAC address for aggregation
 * code.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_AGGR_CFG . AC_DMAC_ENA
 */
#define  VTSS_F_ANA_COMMON_AGGR_CFG_AC_DMAC_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Use the lower 12 bits of the source MAC address for aggregation code.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_AGGR_CFG . AC_SMAC_ENA
 */
#define  VTSS_F_ANA_COMMON_AGGR_CFG_AC_SMAC_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Use the 20-bit IPv6 flow label for aggregation code.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_AGGR_CFG . AC_IP6_FLOW_LBL_ENA
 */
#define  VTSS_F_ANA_COMMON_AGGR_CFG_AC_IP6_FLOW_LBL_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Use least significant 8 bits of both source port and destination port of
 * IPv6 frames for aggregation code.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_AGGR_CFG . AC_IP6_TCPUDP_ENA
 */
#define  VTSS_F_ANA_COMMON_AGGR_CFG_AC_IP6_TCPUDP_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Use least significant 8 bits of both source IP address and destination
 * IP address of IPv4 frames for aggregation code.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_AGGR_CFG . AC_IP4_SIPDIP_ENA
 */
#define  VTSS_F_ANA_COMMON_AGGR_CFG_AC_IP4_SIPDIP_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Use least significant 8 bits of both source port and destination port of
 * IPv4 frames for aggregation code.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_AGGR_CFG . AC_IP4_TCPUDP_ENA
 */
#define  VTSS_F_ANA_COMMON_AGGR_CFG_AC_IP4_TCPUDP_ENA  VTSS_BIT(0)


/** 
 * \brief CPU extraction queue configuration
 *
 * \details
 * Register: \a ANA:COMMON:CPUQ_CFG
 */
#define VTSS_ANA_COMMON_CPUQ_CFG             VTSS_IOREG(VTSS_TO_ANA,0x38f)

/** 
 * \brief
 * CPU extraction queue used for MLD frames.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_CPUQ_CFG . CPUQ_MLD
 */
#define  VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_MLD(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_ANA_COMMON_CPUQ_CFG_CPUQ_MLD     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_ANA_COMMON_CPUQ_CFG_CPUQ_MLD(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * CPU extraction queue used for IGMP frames.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_CPUQ_CFG . CPUQ_IGMP
 */
#define  VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_IGMP(x)  VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_ANA_COMMON_CPUQ_CFG_CPUQ_IGMP     VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_ANA_COMMON_CPUQ_CFG_CPUQ_IGMP(x)  VTSS_EXTRACT_BITFIELD(x,24,3)

/** 
 * \brief
 * CPU extraction queue used for IPv4 multicast control frames.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_CPUQ_CFG . CPUQ_IPMC_CTRL
 */
#define  VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_IPMC_CTRL(x)  VTSS_ENCODE_BITFIELD(x,21,3)
#define  VTSS_M_ANA_COMMON_CPUQ_CFG_CPUQ_IPMC_CTRL     VTSS_ENCODE_BITMASK(21,3)
#define  VTSS_X_ANA_COMMON_CPUQ_CFG_CPUQ_IPMC_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,21,3)

/** 
 * \brief
 * CPU extraction queue used for allbridge frames (DMAC =
 * 01-80-C2-00-00-10).
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_CPUQ_CFG . CPUQ_ALLBRIDGE
 */
#define  VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_ALLBRIDGE(x)  VTSS_ENCODE_BITFIELD(x,18,3)
#define  VTSS_M_ANA_COMMON_CPUQ_CFG_CPUQ_ALLBRIDGE     VTSS_ENCODE_BITMASK(18,3)
#define  VTSS_X_ANA_COMMON_CPUQ_CFG_CPUQ_ALLBRIDGE(x)  VTSS_EXTRACT_BITFIELD(x,18,3)

/** 
 * \brief
 * CPU extraction queue for frames triggering a port move for a locked MAC
 * table entry.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_CPUQ_CFG . CPUQ_LOCKED_PORTMOVE
 */
#define  VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_LOCKED_PORTMOVE(x)  VTSS_ENCODE_BITFIELD(x,15,3)
#define  VTSS_M_ANA_COMMON_CPUQ_CFG_CPUQ_LOCKED_PORTMOVE     VTSS_ENCODE_BITMASK(15,3)
#define  VTSS_X_ANA_COMMON_CPUQ_CFG_CPUQ_LOCKED_PORTMOVE(x)  VTSS_EXTRACT_BITFIELD(x,15,3)

/** 
 * \brief
 * CPU extraction queue for frames copied due to CPU_SRC_COPY_ENA
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_CPUQ_CFG . CPUQ_SRC_COPY
 */
#define  VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_SRC_COPY(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_ANA_COMMON_CPUQ_CFG_CPUQ_SRC_COPY     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_ANA_COMMON_CPUQ_CFG_CPUQ_SRC_COPY(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/** 
 * \brief
 * CPU extraction queue for frames copied due to CPU_COPY return by MAC
 * table lookup
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_CPUQ_CFG . CPUQ_MAC_COPY
 */
#define  VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_MAC_COPY(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_ANA_COMMON_CPUQ_CFG_CPUQ_MAC_COPY     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_ANA_COMMON_CPUQ_CFG_CPUQ_MAC_COPY(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/** 
 * \brief
 * CPU extraction queue for frames copied due to learned or moved stations.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_CPUQ_CFG . CPUQ_LRN
 */
#define  VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_LRN(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_ANA_COMMON_CPUQ_CFG_CPUQ_LRN     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_ANA_COMMON_CPUQ_CFG_CPUQ_LRN(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * CPU extraction queue for frames copied due to mirroring to the CPU.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_CPUQ_CFG . CPUQ_MIRROR
 */
#define  VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_MIRROR(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_ANA_COMMON_CPUQ_CFG_CPUQ_MIRROR     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_ANA_COMMON_CPUQ_CFG_CPUQ_MIRROR(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/** 
 * \brief
 * CPU extraction queue for frames copied due to SFLOW sampling.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_CPUQ_CFG . CPUQ_SFLOW
 */
#define  VTSS_F_ANA_COMMON_CPUQ_CFG_CPUQ_SFLOW(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_COMMON_CPUQ_CFG_CPUQ_SFLOW     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_COMMON_CPUQ_CFG_CPUQ_SFLOW(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief CPU extraction queue per address of BPDU, GARP, and CCM frames.
 *
 * \details
 * Register: \a ANA:COMMON:CPUQ_8021_CFG
 *
 * @param ri Register: CPUQ_8021_CFG (??), 0-15
 */
#define VTSS_ANA_COMMON_CPUQ_8021_CFG(ri)    VTSS_IOREG(VTSS_TO_ANA,0x390 + (ri))

/** 
 * \brief
 * CPU extraction queue used for BPDU frames.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_CPUQ_8021_CFG . CPUQ_BPDU_VAL
 */
#define  VTSS_F_ANA_COMMON_CPUQ_8021_CFG_CPUQ_BPDU_VAL(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_ANA_COMMON_CPUQ_8021_CFG_CPUQ_BPDU_VAL     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_ANA_COMMON_CPUQ_8021_CFG_CPUQ_BPDU_VAL(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * CPU extraction queue used for GARP frames.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_CPUQ_8021_CFG . CPUQ_GARP_VAL
 */
#define  VTSS_F_ANA_COMMON_CPUQ_8021_CFG_CPUQ_GARP_VAL(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_ANA_COMMON_CPUQ_8021_CFG_CPUQ_GARP_VAL     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_ANA_COMMON_CPUQ_8021_CFG_CPUQ_GARP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/** 
 * \brief
 * CPU extraction queue used for CCM/Link trace frames.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_CPUQ_8021_CFG . CPUQ_CCM_VAL
 */
#define  VTSS_F_ANA_COMMON_CPUQ_8021_CFG_CPUQ_CCM_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_COMMON_CPUQ_8021_CFG_CPUQ_CCM_VAL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_COMMON_CPUQ_8021_CFG_CPUQ_CCM_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief DSCP configuration per DSCP value.
 *
 * \details
 * Register: \a ANA:COMMON:DSCP_CFG
 *
 * @param ri Register: DSCP_CFG (??), 0-63
 */
#define VTSS_ANA_COMMON_DSCP_CFG(ri)         VTSS_IOREG(VTSS_TO_ANA,0x3a0 + (ri))

/** 
 * \brief
 * Maps the frame's DSCP value to a drop precedence level. This is enabled
 * in QOS_CFG.QOS_DSCP_ENA.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_DSCP_CFG . DP_DSCP_VAL
 */
#define  VTSS_F_ANA_COMMON_DSCP_CFG_DP_DSCP_VAL  VTSS_BIT(11)

/** 
 * \brief
 * Maps the frame's DSCP value to a QoS class. This is enabled in
 * QOS_CFG.QOS_DSCP_ENA.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_DSCP_CFG . QOS_DSCP_VAL
 */
#define  VTSS_F_ANA_COMMON_DSCP_CFG_QOS_DSCP_VAL(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_ANA_COMMON_DSCP_CFG_QOS_DSCP_VAL     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_ANA_COMMON_DSCP_CFG_QOS_DSCP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/** 
 * \brief
 * Translated DSCP value triggered if DSCP translation is set for port
 * (QOS_CFG[port].DSCP_TRANSLATE_ENA)
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_DSCP_CFG . DSCP_TRANSLATE_VAL
 */
#define  VTSS_F_ANA_COMMON_DSCP_CFG_DSCP_TRANSLATE_VAL(x)  VTSS_ENCODE_BITFIELD(x,2,6)
#define  VTSS_M_ANA_COMMON_DSCP_CFG_DSCP_TRANSLATE_VAL     VTSS_ENCODE_BITMASK(2,6)
#define  VTSS_X_ANA_COMMON_DSCP_CFG_DSCP_TRANSLATE_VAL(x)  VTSS_EXTRACT_BITFIELD(x,2,6)

/** 
 * \brief
 * Must be set for a DSCP value if the DSCP value is to be used for QoS
 * classification.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_DSCP_CFG . DSCP_TRUST_ENA
 */
#define  VTSS_F_ANA_COMMON_DSCP_CFG_DSCP_TRUST_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Set if the DSCP value is selected to be rewritten. This is controlled in
 * QOS_CFG.DSCP_REWR_CFG.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_DSCP_CFG . DSCP_REWR_ENA
 */
#define  VTSS_F_ANA_COMMON_DSCP_CFG_DSCP_REWR_ENA  VTSS_BIT(0)


/** 
 * \brief DSCP rewrite values per DP level and QoS class
 *
 * \details
 * Register: \a ANA:COMMON:DSCP_REWR_CFG
 *
 * @param ri Register: DSCP_REWR_CFG (??), 0-15
 */
#define VTSS_ANA_COMMON_DSCP_REWR_CFG(ri)    VTSS_IOREG(VTSS_TO_ANA,0x3e0 + (ri))

/** 
 * \brief
 * Map the frame's DP level and QoS class to a DSCP value. DSCP =
 * DSCP_REWR_CFG[8*DP level + QoS class].DSCP_QOS_REWR_VAL. This is
 * controlled in QOS_CFG.DSCP_REWR_CFG and DSCP_CFG.DSCP_REWR_ENA.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_DSCP_REWR_CFG . DSCP_QOS_REWR_VAL
 */
#define  VTSS_F_ANA_COMMON_DSCP_REWR_CFG_DSCP_QOS_REWR_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_ANA_COMMON_DSCP_REWR_CFG_DSCP_QOS_REWR_VAL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_ANA_COMMON_DSCP_REWR_CFG_DSCP_QOS_REWR_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief VCAP range checkers
 *
 * \details
 * Register: \a ANA:COMMON:VCAP_RNG_TYPE_CFG
 *
 * @param ri Register: VCAP_RNG_TYPE_CFG (??), 0-7
 */
#define VTSS_ANA_COMMON_VCAP_RNG_TYPE_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA,0x3f0 + (ri))

/** 
 * \details 
 * 0: Idle
 * 1: TCP/UDP destination port is matched against range
 * 2: TCP/UDP source port is matched against range
 * 3: TCP/UDP source and destination ports are matched against range. Match
 * if either source or destination port is within range.
 * 4: VID is matched against range (S1: VID in frame, S2: classified VID)
 * 5: DSCP value is matched against range
 * 6: Reserved
 * 7: Reserved
 *
 * Field: ::VTSS_ANA_COMMON_VCAP_RNG_TYPE_CFG . VCAP_RNG_CFG
 */
#define  VTSS_F_ANA_COMMON_VCAP_RNG_TYPE_CFG_VCAP_RNG_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_COMMON_VCAP_RNG_TYPE_CFG_VCAP_RNG_CFG     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_COMMON_VCAP_RNG_TYPE_CFG_VCAP_RNG_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Range configuration per range checker
 *
 * \details
 * Register: \a ANA:COMMON:VCAP_RNG_VAL_CFG
 *
 * @param ri Register: VCAP_RNG_VAL_CFG (??), 0-7
 */
#define VTSS_ANA_COMMON_VCAP_RNG_VAL_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA,0x3f8 + (ri))

/** 
 * \brief
 * Lower value. Value is included in range.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_VCAP_RNG_VAL_CFG . VCAP_RNG_MIN_VAL
 */
#define  VTSS_F_ANA_COMMON_VCAP_RNG_VAL_CFG_VCAP_RNG_MIN_VAL(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_ANA_COMMON_VCAP_RNG_VAL_CFG_VCAP_RNG_MIN_VAL     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_ANA_COMMON_VCAP_RNG_VAL_CFG_VCAP_RNG_MIN_VAL(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Upper value. Value is included in range.
 *
 * \details 
 * Field: ::VTSS_ANA_COMMON_VCAP_RNG_VAL_CFG . VCAP_RNG_MAX_VAL
 */
#define  VTSS_F_ANA_COMMON_VCAP_RNG_VAL_CFG_VCAP_RNG_MAX_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ANA_COMMON_VCAP_RNG_VAL_CFG_VCAP_RNG_MAX_VAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ANA_COMMON_VCAP_RNG_VAL_CFG_VCAP_RNG_MAX_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


#endif /* _VTSS_LUTON26_REGS_ANA_H_ */
