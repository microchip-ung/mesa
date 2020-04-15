#ifndef _VTSS_LUTON26_REGS_DEV_GMII_H_
#define _VTSS_LUTON26_REGS_DEV_GMII_H_

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
 * Target: \a DEV_GMII
 *
 * \see vtss_target_DEV_GMII_e
 *
 * Port configuration
 *
 ***********************************************************************/

/**
 * Register Group: \a DEV_GMII:PORT_MODE
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a DEV_GMII:PORT_MODE:CLOCK_CFG
 *
 * @param target A \a ::vtss_target_DEV_GMII_e target
 */
#define VTSS_DEV_GMII_PORT_MODE_CLOCK_CFG(target)  VTSS_IOREG(target,0x0)

/** 
 * \details 
 * Field: ::VTSS_DEV_GMII_PORT_MODE_CLOCK_CFG . MAC_TX_RST
 */
#define  VTSS_F_DEV_GMII_PORT_MODE_CLOCK_CFG_MAC_TX_RST  VTSS_BIT(3)

/** 
 * \details 
 * Field: ::VTSS_DEV_GMII_PORT_MODE_CLOCK_CFG . MAC_RX_RST
 */
#define  VTSS_F_DEV_GMII_PORT_MODE_CLOCK_CFG_MAC_RX_RST  VTSS_BIT(2)

/** 
 * \details 
 * Field: ::VTSS_DEV_GMII_PORT_MODE_CLOCK_CFG . PORT_RST
 */
#define  VTSS_F_DEV_GMII_PORT_MODE_CLOCK_CFG_PORT_RST  VTSS_BIT(1)

/** 
 * \details 
 * Field: ::VTSS_DEV_GMII_PORT_MODE_CLOCK_CFG . PHY_RST
 */
#define  VTSS_F_DEV_GMII_PORT_MODE_CLOCK_CFG_PHY_RST  VTSS_BIT(0)


/** 
 * \details
 * Register: \a DEV_GMII:PORT_MODE:PORT_MISC
 *
 * @param target A \a ::vtss_target_DEV_GMII_e target
 */
#define VTSS_DEV_GMII_PORT_MODE_PORT_MISC(target)  VTSS_IOREG(target,0x1)

/** 
 * \brief
 * Forward pause frames (EtherType = 0x8808, opcode = 0x0001). The reaction
 * to incoming pause frames is controlled independently of TBD.
 *
 * \details 
 * Field: ::VTSS_DEV_GMII_PORT_MODE_PORT_MISC . FWD_PAUSE_ENA
 */
#define  VTSS_F_DEV_GMII_PORT_MODE_PORT_MISC_FWD_PAUSE_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Forward MAC control frames excluding pause frames (EtherType = 0x8808,
 * opcode different from 0x0001).
 *
 * \details 
 * Field: ::VTSS_DEV_GMII_PORT_MODE_PORT_MISC . FWD_CTRL_ENA
 */
#define  VTSS_F_DEV_GMII_PORT_MODE_PORT_MISC_FWD_CTRL_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Loop GMII transmit data directly into receive path.
 *
 * \details 
 * Field: ::VTSS_DEV_GMII_PORT_MODE_PORT_MISC . GMII_LOOP_ENA
 */
#define  VTSS_F_DEV_GMII_PORT_MODE_PORT_MISC_GMII_LOOP_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Loop the device bus through this port. The MAC is potentially bypassed.
 *
 * \details 
 * Field: ::VTSS_DEV_GMII_PORT_MODE_PORT_MISC . DEV_LOOP_ENA
 */
#define  VTSS_F_DEV_GMII_PORT_MODE_PORT_MISC_DEV_LOOP_ENA  VTSS_BIT(0)

/**
 * Register Group: \a DEV_GMII:MAC_CFG_STATUS
 *
 * Not documented
 */


/** 
 * \brief Mode Configuration Register
 *
 * \details
 * Register: \a DEV_GMII:MAC_CFG_STATUS:MAC_ENA_CFG
 *
 * @param target A \a ::vtss_target_DEV_GMII_e target
 */
#define VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_ENA_CFG(target)  VTSS_IOREG(target,0x3)

/** 
 * \brief
 * Receiver Module Enable.
 *
 * \details 
 * '0': Receiver Module Disabled
 * '1': Receiver Module Enabled
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_ENA_CFG . RX_ENA
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_ENA_CFG_RX_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Transmitter Module Enable.
 *
 * \details 
 * '0': Transmitter Module Disabled
 * '1': Transmitter Module Enabled
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_ENA_CFG . TX_ENA
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_ENA_CFG_TX_ENA  VTSS_BIT(0)


/** 
 * \brief Mode Configuration Register
 *
 * \details
 * Register: \a DEV_GMII:MAC_CFG_STATUS:MAC_MODE_CFG
 *
 * @param target A \a ::vtss_target_DEV_GMII_e target
 */
#define VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_MODE_CFG(target)  VTSS_IOREG(target,0x4)

/** 
 * \brief
 * Enables 1 Gbps mode.
 *
 * \details 
 * '0': 10/100 Mbps mode
 * '1': 1 Gbps mode. Note: FDX_ENA must also be set.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_MODE_CFG . GIGA_MODE_ENA
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_MODE_CFG_GIGA_MODE_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Enables Full Duplex:
 *
 * \details 
 * '0': Half Duplex
 * '1': Full duplex.
 * 
 * Note: Full duplex MUST be selected if GIGA_MODE is enabled.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_MODE_CFG . FDX_ENA
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_MODE_CFG_FDX_ENA  VTSS_BIT(0)


/** 
 * \brief Max Length Configuration Register
 *
 * \details
 * Register: \a DEV_GMII:MAC_CFG_STATUS:MAC_MAXLEN_CFG
 *
 * @param target A \a ::vtss_target_DEV_GMII_e target
 */
#define VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_MAXLEN_CFG(target)  VTSS_IOREG(target,0x5)

/** 
 * \brief
 * When set, single tagged frames are allowed to be 4 bytes longer than the
 * MAC_MAXLEN_CFG configuration and double tagged frames are allowed to be
 * 8 bytes longer. Single tagged frames are adjusted if VLAN_AWR_ENA is
 * also set. Double tagged frames are adjusted if both VLAN_AWR_ENA and
 * VLAN_DBL_AWR_ENA are set.
 *
 * \details 
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_MAXLEN_CFG . MAX_LEN
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_MAXLEN_CFG_MAX_LEN(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DEV_GMII_MAC_CFG_STATUS_MAC_MAXLEN_CFG_MAX_LEN     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DEV_GMII_MAC_CFG_STATUS_MAC_MAXLEN_CFG_MAX_LEN(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VLAN / Service tag configuration register
 *
 * \details
 * The MAC can be configured to accept 0, 1 and 2 tags and the TAG value
 * can be user-defined.
 *
 * Register: \a DEV_GMII:MAC_CFG_STATUS:MAC_TAGS_CFG
 *
 * @param target A \a ::vtss_target_DEV_GMII_e target
 */
#define VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_TAGS_CFG(target)  VTSS_IOREG(target,0x6)

/** 
 * \brief
 * This field defines which EtherTypes are recognized as a VLAN TPID -
 * besides 0x8100. The value is used for all tag positions. I.e. a double
 * tagged frame can have the following tag values:
 * (TAG1,TAG2):
 * ( 0x8100, 0x8100 )
 * ( 0x8100, TAG_ID )
 * ( TAG_ID, 0x8100 ) or
 * ( TAG_ID, TAG_ID )
 * 
 * Single tagged frame can have the following TPID values: 0x8100 or
 * TAG_ID.
 *
 * \details 
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_TAGS_CFG . TAG_ID
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_TAGS_CFG_TAG_ID(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DEV_GMII_MAC_CFG_STATUS_MAC_TAGS_CFG_TAG_ID     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DEV_GMII_MAC_CFG_STATUS_MAC_TAGS_CFG_TAG_ID(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * If set, double tagged frames are subject to length adjustments
 * (VLAN_LEN_AWR_ENA). VLAN_AWR_ENA must be set when VLAN_DBL_AWR_ENA is
 * set.
 *
 * \details 
 * '0': The MAC does not look for inner tags.
 * '1': The MAC accepts inner tags with TPID=0x8100 or TAG_ID.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_TAGS_CFG . VLAN_DBL_AWR_ENA
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_TAGS_CFG_VLAN_DBL_AWR_ENA  VTSS_BIT(1)

/** 
 * \brief
 * If set, single tagged frames are subject to length adjustments
 * (VLAN_LEN_AWR_ENA).
 *
 * \details 
 * '0': The MAC does not look for any tags.
 * '1': The MAC accepts outer tags with TPID=0x8100 or TAG_ID.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_TAGS_CFG . VLAN_AWR_ENA
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_TAGS_CFG_VLAN_AWR_ENA  VTSS_BIT(0)

/** 
 * \brief
 * When set, single tagged frames are allowed to be 4 bytes longer than the
 * MAC_MAXLEN_CFG configuration and double tagged frames are allowed to be
 * 8 bytes longer. Single tagged frames are adjusted if VLAN_AWR_ENA is
 * also set. Double tagged frames are adjusted if both VLAN_AWR_ENA and
 * VLAN_DBL_AWR_ENA are set.
 *
 * \details 
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_TAGS_CFG . VLAN_LEN_AWR_ENA
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_TAGS_CFG_VLAN_LEN_AWR_ENA  VTSS_BIT(2)


/** 
 * \brief Advanced Check Feature Configuration Register
 *
 * \details
 * Register: \a DEV_GMII:MAC_CFG_STATUS:MAC_ADV_CHK_CFG
 *
 * @param target A \a ::vtss_target_DEV_GMII_e target
 */
#define VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_ADV_CHK_CFG(target)  VTSS_IOREG(target,0x7)

/** 
 * \brief
 * Length Drop Enable:\nConfigures the Receive Module to drop frames in
 * reference to in-range and out-of-range errors:
 *
 * \details 
 * '0': Length Drop Disabled
 * '1': Length Drop Enabled.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_ADV_CHK_CFG . LEN_DROP_ENA
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_LEN_DROP_ENA  VTSS_BIT(0)


/** 
 * \brief Inter Frame Gap Configuration Register
 *
 * \details
 * Register: \a DEV_GMII:MAC_CFG_STATUS:MAC_IFG_CFG
 *
 * @param target A \a ::vtss_target_DEV_GMII_e target
 */
#define VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_IFG_CFG(target)  VTSS_IOREG(target,0x8)

/** 
 * \brief
 * Used to adjust the duration of the inter-frame gap in the Tx direction
 * and must be set according to the speed and duplex settings.
 *
 * \details 
 * 10/100 Mbps, HDX, FDX 0x19, 0x13
 * 1000 Mbps: 0x07.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_IFG_CFG . TX_IFG
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_IFG_CFG_TX_IFG(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_DEV_GMII_MAC_CFG_STATUS_MAC_IFG_CFG_TX_IFG     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_DEV_GMII_MAC_CFG_STATUS_MAC_IFG_CFG_TX_IFG(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * Used to adjust the duration of the second part of the inter-frame gap in
 * the Rx direction and must be set according to the speed and duplex
 * settings.
 *
 * \details 
 * 10/100 Mbps, HDX, FDX: 0x8, 0xB
 * 1000 Mbps: 0x1.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_IFG_CFG . RX_IFG2
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_IFG_CFG_RX_IFG2(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_DEV_GMII_MAC_CFG_STATUS_MAC_IFG_CFG_RX_IFG2     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_DEV_GMII_MAC_CFG_STATUS_MAC_IFG_CFG_RX_IFG2(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Used to adjust the duration of the first part of the inter-frame gap in
 * the Rx direction and must be set according to the speed settings.
 *
 * \details 
 * 10/100 Mbps: 0x7
 * 1000 Mbps: 0x5.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_IFG_CFG . RX_IFG1
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_IFG_CFG_RX_IFG1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DEV_GMII_MAC_CFG_STATUS_MAC_IFG_CFG_RX_IFG1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DEV_GMII_MAC_CFG_STATUS_MAC_IFG_CFG_RX_IFG1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Half Duplex Configuration Register
 *
 * \details
 * Register: \a DEV_GMII:MAC_CFG_STATUS:MAC_HDX_CFG
 *
 * @param target A \a ::vtss_target_DEV_GMII_e target
 */
#define VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_HDX_CFG(target)  VTSS_IOREG(target,0x9)

/** 
 * \brief
 * Determines whether the MAC backs off after an excessive collision has
 * occurred. If set, back off is disabled after excessive collisions.
 *
 * \details 
 * '0': Back off after excessive collisions
 * '1': Don't back off after excessive collisions
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_HDX_CFG . WEXC_DIS
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_HDX_CFG_WEXC_DIS  VTSS_BIT(24)

/** 
 * \brief
 * Seed value loaded into the PRBS of the MAC.
 *
 * \details 
 * Used to prevent excessive collision events.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_HDX_CFG . SEED
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_HDX_CFG_SEED(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DEV_GMII_MAC_CFG_STATUS_MAC_HDX_CFG_SEED     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DEV_GMII_MAC_CFG_STATUS_MAC_HDX_CFG_SEED(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Load SEED value into PRNG register. A SEED value is loaded into the PRNG
 * register of the MAC, when SEED_LOAD is asserted. After a load, the
 * SEED_LOAD must be deasserted.
 *
 * \details 
 * '0': Do not load SEED value
 * '1': Load SEED value.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_HDX_CFG . SEED_LOAD
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_HDX_CFG_SEED_LOAD  VTSS_BIT(12)

/** 
 * \brief
 * This bit is used to setup the MAC to retransmit a frame after an early
 * collision even though 16 (or more) early collisions have occurred. This
 * feature violates the IEEE 802.3 standard and should only be used when
 * running in HDX flow control, which is not defined in the IEEE standard
 * anyway.
 *
 * \details 
 * '0': A frame is discarded and counted as an excessive collision if 16
 * collisions occur for this frame.
 * '1': The MAC retransmits a frame after an early collision, regardless of
 * the number of previous early collisions. The backoff sequence is reset
 * after every 16 collisions.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_HDX_CFG . RETRY_AFTER_EXC_COL_ENA
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_HDX_CFG_RETRY_AFTER_EXC_COL_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Adjustment of early/late collision boundary:\nThis bitgroup is used to
 * adjust the MAC so that a collision on a shared transmission medium
 * before bit 512 is handled as an early collision, whereas a collision
 * after bit 512 is handled as a late collision, i.e. no retransmission is
 * performed.
 *
 * \details 
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_HDX_CFG . LATE_COL_POS
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_HDX_CFG_LATE_COL_POS(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_DEV_GMII_MAC_CFG_STATUS_MAC_HDX_CFG_LATE_COL_POS     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_DEV_GMII_MAC_CFG_STATUS_MAC_HDX_CFG_LATE_COL_POS(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief MAC Flow Control Configuration Register
 *
 * \details
 * Register: \a DEV_GMII:MAC_CFG_STATUS:MAC_FC_CFG
 *
 * @param target A \a ::vtss_target_DEV_GMII_e target
 */
#define VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_FC_CFG(target)  VTSS_IOREG(target,0xb)

/** 
 * \brief
 * If set, a zero-delay pause frame is transmitted when flow control is
 * deasserted.
 *
 * \details 
 * '0': Don't send zero pause frame.
 * '1': Send zero pause frame.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_FC_CFG . ZERO_PAUSE_ENA
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_FC_CFG_ZERO_PAUSE_ENA  VTSS_BIT(18)

/** 
 * \brief
 * When set the MAC will send pause control frames in the Tx direction.
 *
 * \details 
 * '0': Don't send pause control frames
 * '1': Send pause control frames
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_FC_CFG . TX_FC_ENA
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_FC_CFG_TX_FC_ENA  VTSS_BIT(17)

/** 
 * \brief
 * When set the MAC obeys received pause control frames
 *
 * \details 
 * '0': Don't obey received pause control frames
 * '1': Obey received pause control frames.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_FC_CFG . RX_FC_ENA
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_FC_CFG_RX_FC_ENA  VTSS_BIT(16)

/** 
 * \brief
 * Pause timer value inserted in generated pause frames.
 *
 * \details 
 * 0: Insert timer value 0 in TX pause frame.
 * ...
 * N: Insert timer value N in TX pause frame.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_FC_CFG . PAUSE_VAL_CFG
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_FC_CFG_PAUSE_VAL_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DEV_GMII_MAC_CFG_STATUS_MAC_FC_CFG_PAUSE_VAL_CFG     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DEV_GMII_MAC_CFG_STATUS_MAC_FC_CFG_PAUSE_VAL_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * Accepted reaction time for link partner after the port has transmitted a
 * pause frame. Frames starting after this latency are aborted. Unit is 64
 * byte times. A value of 63 disables the feature.
 *
 * \details 
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_FC_CFG . FC_LATENCY_CFG
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_FC_CFG_FC_LATENCY_CFG(x)  VTSS_ENCODE_BITFIELD(x,19,6)
#define  VTSS_M_DEV_GMII_MAC_CFG_STATUS_MAC_FC_CFG_FC_LATENCY_CFG     VTSS_ENCODE_BITMASK(19,6)
#define  VTSS_X_DEV_GMII_MAC_CFG_STATUS_MAC_FC_CFG_FC_LATENCY_CFG(x)  VTSS_EXTRACT_BITFIELD(x,19,6)


/** 
 * \brief MAC Flow Control Configuration Register
 *
 * \details
 * Register: \a DEV_GMII:MAC_CFG_STATUS:MAC_FC_MAC_LOW_CFG
 *
 * @param target A \a ::vtss_target_DEV_GMII_e target
 */
#define VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_FC_MAC_LOW_CFG(target)  VTSS_IOREG(target,0xc)

/** 
 * \brief
 * Lower three bytes in the SMAC in generated flow control frames.

 *
 * \details 
 * 0xNNN: Lower three DMAC bytes

 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_FC_MAC_LOW_CFG . MAC_LOW
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_FC_MAC_LOW_CFG_MAC_LOW(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_DEV_GMII_MAC_CFG_STATUS_MAC_FC_MAC_LOW_CFG_MAC_LOW     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_DEV_GMII_MAC_CFG_STATUS_MAC_FC_MAC_LOW_CFG_MAC_LOW(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/** 
 * \brief MAC Flow Control Configuration Register
 *
 * \details
 * Register: \a DEV_GMII:MAC_CFG_STATUS:MAC_FC_MAC_HIGH_CFG
 *
 * @param target A \a ::vtss_target_DEV_GMII_e target
 */
#define VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_FC_MAC_HIGH_CFG(target)  VTSS_IOREG(target,0xd)

/** 
 * \brief
 * Higher three bytes in the SMAC in generated flow control frames.
 *
 * \details 
 * 0xNNN: Higher three DMAC bytes
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_FC_MAC_HIGH_CFG . MAC_HIGH
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_FC_MAC_HIGH_CFG_MAC_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_DEV_GMII_MAC_CFG_STATUS_MAC_FC_MAC_HIGH_CFG_MAC_HIGH     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_DEV_GMII_MAC_CFG_STATUS_MAC_FC_MAC_HIGH_CFG_MAC_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/** 
 * \brief Sticky Bit Register
 *
 * \details
 * Clear the sticky bits by writing a '0' in the relevant bitgroups
 * (writing a '1' sets the bit)!.
 *
 * Register: \a DEV_GMII:MAC_CFG_STATUS:MAC_STICKY
 *
 * @param target A \a ::vtss_target_DEV_GMII_e target
 */
#define VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY(target)  VTSS_IOREG(target,0xe)

/** 
 * \brief
 * Sticky bit indicating that an inter packet gap shrink was detected (IPG
 * < 12 bytes).
 *
 * \details 
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY . RX_IPG_SHRINK_STICKY
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY_RX_IPG_SHRINK_STICKY  VTSS_BIT(9)

/** 
 * \brief
 * Sticky bit indicating that a preamble shrink was detected (preamble < 8
 * bytes).
 *
 * \details 
 * '0': no preamble shrink was detected
 * '1': a preamble shrink was detected one or more times
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY . RX_PREAM_SHRINK_STICKY
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY_RX_PREAM_SHRINK_STICKY  VTSS_BIT(8)

/** 
 * \brief
 * Sticky bit indicating that a carrier extend was detected.
 *
 * \details 
 * '0': no carrier extend was detected
 * '1': one or more carrier extends were detected
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY . RX_CARRIER_EXT_STICKY
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY_RX_CARRIER_EXT_STICKY  VTSS_BIT(7)

/** 
 * \brief
 * Sticky bit indicating that a carrier extend error was detected.
 *
 * \details 
 * '0': no carrier extend error was detected
 * '1': one or more carrier extend errors were detected
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY . RX_CARRIER_EXT_ERR_STICKY
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY_RX_CARRIER_EXT_ERR_STICKY  VTSS_BIT(6)

/** 
 * \brief
 * Sticky bit indicating that junk was received (bytes not recognized as a
 * frame).
 *
 * \details 
 * '0': no junk was received
 * '1': junk was received one or more times
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY . RX_JUNK_STICKY
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY_RX_JUNK_STICKY  VTSS_BIT(5)

/** 
 * \brief
 * Sticky bit indicating that the transmit MAC asked the host for a frame
 * retransmission.
 *
 * \details 
 * '0': no tx retransmission was initiated
 * '1': one or more tx retransmissions were initiated
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY . TX_RETRANSMIT_STICKY
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY_TX_RETRANSMIT_STICKY  VTSS_BIT(4)

/** 
 * \brief
 * Sticky bit indicating that the transmit host issued a jamming signal.
 *
 * \details 
 * '0': the transmit host issued no jamming signal
 * '1': the transmit host issued one or more jamming signals
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY . TX_JAM_STICKY
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY_TX_JAM_STICKY  VTSS_BIT(3)

/** 
 * \brief
 * Sticky bit indicating that the MAC transmit FIFO has overrun.
 *
 * \details 
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY . TX_FIFO_OFLW_STICKY
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY_TX_FIFO_OFLW_STICKY  VTSS_BIT(2)

/** 
 * \brief
 * Sticky bit indicating that the transmit frame length has overrun. I.e. a
 * frame longer than 64K occurred.
 *
 * \details 
 * '0': no tx frame length error occurred
 * '1': one or more tx frames length errors occurred
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY . TX_FRM_LEN_OVR_STICKY
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY_TX_FRM_LEN_OVR_STICKY  VTSS_BIT(1)

/** 
 * \brief
 * Sticky bit indicating that the transmit host initiated abort was
 * executed.
 *
 * \details 
 * Field: ::VTSS_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY . TX_ABORT_STICKY
 */
#define  VTSS_F_DEV_GMII_MAC_CFG_STATUS_MAC_STICKY_TX_ABORT_STICKY  VTSS_BIT(0)


#endif /* _VTSS_LUTON26_REGS_DEV_GMII_H_ */
