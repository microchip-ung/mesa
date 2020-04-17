// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_VENICE_REGS_HOST_MAC_H_
#define _VTSS_VENICE_REGS_HOST_MAC_H_


#include "vtss_venice_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a HOST_MAC
 *
 * Full duplex (half duplex is not supported) 10/100/1000/10000 MAC registers.
 *
 ***********************************************************************/

/**
 * Register Group: \a HOST_MAC:CONFIG
 *
 * 10G MAC configuration registers
 */


/** 
 * \brief MAC enable register
 *
 * \details
 * Register: \a HOST_MAC:CONFIG:MAC_ENA_CFG
 */
#define VTSS_HOST_MAC_CONFIG_MAC_ENA_CFG     VTSS_IOREG(0x03, 1, 0xf100)

/** 
 * \brief
 * MAC Rx clock enable
 *
 * \details 
 * 0: All clocks for this module with the exception of CSR clock are
 * disabled
 * 1: All clocks for this module are enabled
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_ENA_CFG . RX_CLK_ENA
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_ENA_CFG_RX_CLK_ENA  VTSS_BIT(0)

/** 
 * \brief
 * MAC Tx clock enable
 *
 * \details 
 * 0: All clocks for this module with the exception of CSR clock are
 * disabled
 * 1: All clocks for this module are enabled
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_ENA_CFG . TX_CLK_ENA
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_ENA_CFG_TX_CLK_ENA  VTSS_BIT(4)

/** 
 * \brief
 * MAC Rx software reset
 *
 * \details 
 * 0: Block operates normally
 * 1: All logic (other than CSR target) is held in reset, clocks are not
 * disabled
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_ENA_CFG . RX_SW_RST
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_ENA_CFG_RX_SW_RST  VTSS_BIT(8)

/** 
 * \brief
 * MAC Tx software reset
 *
 * \details 
 * 0: Block operates normally
 * 1: All logic (other than CSR target) is held in reset, clocks are not
 * disabled
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_ENA_CFG . TX_SW_RST
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_ENA_CFG_TX_SW_RST  VTSS_BIT(12)

/** 
 * \brief
 * Enable receiver
 *
 * \details 
 * 0: Disabled
 * 1: Enabled
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_ENA_CFG . RX_ENA
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_ENA_CFG_RX_ENA  VTSS_BIT(16)

/** 
 * \brief
 * Enable transmitter
 *
 * \details 
 * 0: Disabled
 * 1: Enabled
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_ENA_CFG . TX_ENA
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_ENA_CFG_TX_ENA  VTSS_BIT(20)


/** 
 * \brief Mode configuration register
 *
 * \details
 * Register: \a HOST_MAC:CONFIG:MAC_MODE_CFG
 */
#define VTSS_HOST_MAC_CONFIG_MAC_MODE_CFG    VTSS_IOREG(0x03, 1, 0xf101)

/** 
 * \brief
 * According to IEEE 802.3 clause 49, MAC drops frames whose length is less
 * than 64 bytes. So to allow these frames this bit needs to be set to '1'.
 * 
 * Note:
 * 1) MAC statistics will still reflect these frames as undersized frames.
 * 2) Undersized frames with valid FCS are only allowed when this bit is
 * set to '1'. Frames with FCS error are still dropped.
 *
 * \details 
 * 0: MAC drops undersized frames
 * 1: MAC passes through undersized frames
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_MODE_CFG . UNDERSIZED_FRAME_DROP_DIS
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_MODE_CFG_UNDERSIZED_FRAME_DROP_DIS  VTSS_BIT(1)

/** 
 * \brief
 * When this value is 0 MAC10G follows 0-3 DIC algorithm to insert IPG,
 * averaging to 12.
 * When this value is 1 MAC10G does not follow DIC alogrithm for IPG
 * insertion and, as a result, back pressure to host block from kernel is
 * not issued.
 *
 * \details 
 * 0: IPG insertion in MAC10G is enabled
 * 1: IPG insertion in MAC10G is disabled
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_MODE_CFG . DISABLE_DIC
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_MODE_CFG_DISABLE_DIC  VTSS_BIT(0)


/** 
 * \brief Maximum length configuration register
 *
 * \details
 * Register: \a HOST_MAC:CONFIG:MAC_MAXLEN_CFG
 */
#define VTSS_HOST_MAC_CONFIG_MAC_MAXLEN_CFG  VTSS_IOREG(0x03, 1, 0xf102)

/** 
 * \brief
 * Configures the maximum length check to consider the number of Q tags
 * when assessing if a frame is too long.
 *
 * \details 
 * 0: Check max frame length against MAX_LEN
 * 1: Add 4 bytes to MAX_LEN when checking a single tagged frame for max
 * frame length
 *     Add 8 bytes to MAX_LEN when checking a double tagged frame for max
 * frame length
 *     Add 12 bytes to MAX_LEN when checking a triple tagged frame for max
 * frame length
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_MAXLEN_CFG . MAX_LEN_TAG_CHK
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_MAXLEN_CFG_MAX_LEN_TAG_CHK  VTSS_BIT(16)

/** 
 * \brief
 * Maximum frame length accepted by the receive module. 
 * If the length is exceeded, it is indicated in the statistics engine
 * (LONG_FRAME). The maximum length is automatically adjusted to
 * accommodate maximum sized frames containing a VLAN tag, given that the
 * MAC is configured to be VLAN-aware by default.
 * The maximum size is 10056 Bytes. This includes all encapsulations and
 * TAGs. Does not include IFH.
 *
 * \details 
 * Field: VTSS_HOST_MAC_CONFIG_MAC_MAXLEN_CFG . MAX_LEN
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_MAXLEN_CFG_MAX_LEN(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_MAC_CONFIG_MAC_MAXLEN_CFG_MAX_LEN     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_MAC_CONFIG_MAC_MAXLEN_CFG_MAX_LEN(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Tag number configuration register
 *
 * \details
 * Register: \a HOST_MAC:CONFIG:MAC_NUM_TAGS_CFG
 */
#define VTSS_HOST_MAC_CONFIG_MAC_NUM_TAGS_CFG  VTSS_IOREG(0x03, 1, 0xf103)

/** 
 * \brief
 * Number of consecutive VLAN tags supported by the MAC. The maximum value
 * is 3
 *
 * \details 
 * 0: No tags are detected by MAC
 * n: Maximum of n consecutive VLAN Tags are detected by the MAC and
 * accordingly MAX LEN is modified for frame length calculations
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_NUM_TAGS_CFG . NUM_TAGS
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_NUM_TAGS_CFG_NUM_TAGS(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HOST_MAC_CONFIG_MAC_NUM_TAGS_CFG_NUM_TAGS     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HOST_MAC_CONFIG_MAC_NUM_TAGS_CFG_NUM_TAGS(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief VLAN/Service tag configuration register
 *
 * \details
 * The MAC can be configured to accept 0, 1, 2, and 3 tags and the TAG
 * value can be user-defined.
 *
 * Register: \a HOST_MAC:CONFIG:MAC_TAGS_CFG
 *
 * @param ri Register: MAC_TAGS_CFG, 0-2
 */
#define VTSS_HOST_MAC_CONFIG_MAC_TAGS_CFG(ri)  VTSS_IOREG(0x03, 1, 0xf104 | (ri))

/** 
 * \brief
 * Value (other than 0x8100 or 0x88A8) that is regarded as a VLAN/Service
 * tag. 
 * This value is used for all all tag positions. A double tagged frame can
 * have the following INNER_TAG and OUTER_TAG values:
 * 0x8100 and 0x8100
 * 0x8100 and TAG_ID
 * TAG_ID and TAG_ID

 *
 * \details 
 * 0x8100: Standard Ethernet bridge Ethertype (C-tag)
 * 0x88A8: Provider Bridge Ethertype (S-tag)
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_TAGS_CFG . TAG_ID
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_TAGS_CFG_TAG_ID(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_HOST_MAC_CONFIG_MAC_TAGS_CFG_TAG_ID     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_HOST_MAC_CONFIG_MAC_TAGS_CFG_TAG_ID(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Enables TAG_ID other than 0x8100 and 0x88A8 for tag comparison.
 *
 * \details 
 * 0: The MAC does not take TAG_ID for tag identification
 * 1: The MAC looks for tag according to encoding of TAG_ID
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_TAGS_CFG . TAG_ENA
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_TAGS_CFG_TAG_ENA  VTSS_BIT(4)


/** 
 * \brief Advanced check configuration register
 *
 * \details
 * Register: \a HOST_MAC:CONFIG:MAC_ADV_CHK_CFG
 */
#define VTSS_HOST_MAC_CONFIG_MAC_ADV_CHK_CFG  VTSS_IOREG(0x03, 1, 0xf107)

/** 
 * \brief
 * Extended end of packet check.
 * Specifies the requirement for the Rx column when holding an EOP
 * character.
 *
 * \details 
 * 0: Ignore the values of the remaining Rx lanes of a column holding an
 * EOP. For example, if lane 1 holds an EOP, the value of lanes 2 and 3 are
 * ignored.
 * 1: A received frame is error-marked if an Error character is received in
 * any lane of the column holding the EOP character. For example, if lane 1
 * holds an EOP, the frame is error-marked if lanes 0, 2, or 3 hold an
 * Error character.
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_ADV_CHK_CFG . EXT_EOP_CHK_ENA
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_ADV_CHK_CFG_EXT_EOP_CHK_ENA  VTSS_BIT(24)

/** 
 * \brief
 * Enable extended start of packet check.
 * Specifies the requirement for the Rx column prior to the start of packet
 * character.
 *
 * \details 
 * 0: Ignore the value of Rx column at the XGMII interface before a start
 * of packet character.
 * 1: An IDLE column at the XGMII interface must be received before a start
 * of packet character for the MAC to detect a start of frame.
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_ADV_CHK_CFG . EXT_SOP_CHK_ENA
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_ADV_CHK_CFG_EXT_SOP_CHK_ENA  VTSS_BIT(20)

/** 
 * \brief
 * Enable start of frame delimiter check.
 * Specifies the requirements for a successful frame reception.
 *
 * \details 
 * 0: Skip SFD check
 * MAC10G assumes that preamble is 8 bytes (including SOP & SFD) when SOP
 * is received. No checking of SFD is carried out.
 * 1: Enforce strict SFD check
 * The SFD must be D5 for a successful frame reception. MAC10G searches for
 * SFD in lane 3/7 after reception of SOP, before accepting frame data.
 * MAC10G searches for SFD until SFD is found or a control character is
 * encountered.
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_ADV_CHK_CFG . SFD_CHK_ENA
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_ADV_CHK_CFG_SFD_CHK_ENA  VTSS_BIT(16)

/** 
 * \brief
 * Enable preamble check.
 * Specifies the preamble requirements for a successful frame reception.
 *
 * \details 
 * 0: Skip preamble check. 
 * A SOP control character is sufficient for a successful frame reception.
 * The minimum allowed preamble size is still 8 bytes (including SOP and
 * SFD) but the preamble bytes between the SOP and the SFD can have any
 * data value.
 * 1: Enable strict preamble check
 * The last 6 bytes of a preamble prior to the SFD must all be equal to
 * 0x55 for a successful frame reception. For preambles larger than 8
 * bytes, only the last 6 preamble bytes prior to the SFD are checked when
 * this bit is set to 1.
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_ADV_CHK_CFG . PRM_CHK_ENA
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_ADV_CHK_CFG_PRM_CHK_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Enable out of range error check.
 * Determines whether a received frame should be discarded if the frame
 * length field is out of range.
 *
 * \details 
 * 0: Ignore out of range errors
 * 1: Discard frame if the frame length field value is out of range
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_ADV_CHK_CFG . OOR_ERR_ENA
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_ADV_CHK_CFG_OOR_ERR_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Enable in-range error check.
 * Determines whether a received frame should be discarded if the frame
 * length does not match the frame PDU size.
 *
 * \details 
 * 0: Do not error-mark frames with a frame length field that is
 * inconsistent with the actual frame length.
 * 1: Error-mark frames with inconsistent frame length fields and discard
 * them using the Rx queue system.
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_ADV_CHK_CFG . INR_ERR_ENA
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_ADV_CHK_CFG_INR_ERR_ENA  VTSS_BIT(0)


/** 
 * \brief Link fault signaling register
 *
 * \details
 * Register: \a HOST_MAC:CONFIG:MAC_LFS_CFG
 */
#define VTSS_HOST_MAC_CONFIG_MAC_LFS_CFG     VTSS_IOREG(0x03, 1, 0xf108)

/** 
 * \brief
 * Enable unidirectional mode for link fault signaling.
 * Enables the MAC to transmit data during reception of local fault and
 * remote fault ordered sets from the PHY. 
 * In the unidirectional mode, frames are transmitted separated by remote
 * fault ordered sets when receiving local fault. They are transmitted
 * separated by IDLE symbols when receiving remote fault.
 *
 * \details 
 * 0: Disable unidirectional mode link fault signaling.
 * 1: Enable unidirectional mode link fault signaling.
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_LFS_CFG . LFS_UNIDIR_ENA
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_LFS_CFG_LFS_UNIDIR_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Enable link fault signaling mode.
 * Configure how the transmitter reacts on received link fault indications.
 *
 * \details 
 * 0: Ignore link faults detected by the MAC receiver module.
 * 1: React on detected link faults and transmit the appropriate sequence
 * ordered set.
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_LFS_CFG . LFS_MODE_ENA
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_LFS_CFG_LFS_MODE_ENA  VTSS_BIT(0)


/** 
 * \brief Packet interface configuration register
 *
 * \details
 * Packet interface module configuration register
 *
 * Register: \a HOST_MAC:CONFIG:MAC_PKTINF_CFG
 */
#define VTSS_HOST_MAC_CONFIG_MAC_PKTINF_CFG  VTSS_IOREG(0x03, 1, 0xf10a)

/** 
 * \brief
 * Enables stripping of FCS in ingress traffic.
 *
 * \details 
 * 0: FCS is not stripped.
 * 1: FCS is stripped in ingress.
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_PKTINF_CFG . STRIP_FCS_ENA
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_PKTINF_CFG_STRIP_FCS_ENA  VTSS_BIT(0)

/** 
 * \brief
 * Enables FCS insertion in egress traffic.
 *
 * \details 
 * 0: FCS is not added.
 * 1: FCS is added in egress direction.
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_PKTINF_CFG . INSERT_FCS_ENA
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_PKTINF_CFG_INSERT_FCS_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Enables stripping of preamble from MAC frame in the ingress direction.
 *
 * \details 
 * 0: Preamble is unaltered.
 * 1: Preamble is stripped in ingress direction.
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_PKTINF_CFG . STRIP_PREAMBLE_ENA
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_PKTINF_CFG_STRIP_PREAMBLE_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Enables addition of standard preamble in egress direction.
 *
 * \details 
 * 0: Standard preamble is not inserted.
 * 1: Standard preamble is added in egress direction.
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_PKTINF_CFG . INSERT_PREAMBLE_ENA
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_PKTINF_CFG_INSERT_PREAMBLE_ENA  VTSS_BIT(12)

/** 
 * \brief
 * Enables signaling of LPI received.
 *
 * \details 
 * 0: Disable LPI received status.
 * 1: Enable LPI received status signaling.
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_PKTINF_CFG . LPI_RELAY_ENA
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_PKTINF_CFG_LPI_RELAY_ENA  VTSS_BIT(16)

/** 
 * \brief
 * Enables signaling of local fault state.
 *
 * \details 
 * 0: Disable signaling of local fault state.
 * 1: Enable local fault state signaling.
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_PKTINF_CFG . LF_RELAY_ENA
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_PKTINF_CFG_LF_RELAY_ENA  VTSS_BIT(20)

/** 
 * \brief
 * Enables signaling of remote fault state.
 *
 * \details 
 * 0: Disable signaling of remote fault state.
 * 1: Enable remote fault state signaling.
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_PKTINF_CFG . RF_RELAY_ENA
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_PKTINF_CFG_RF_RELAY_ENA  VTSS_BIT(24)

/** 
 * \brief
 * Enables padding frames during transmission. Frames with length less than
 * 64 are padded with zeros.
 *
 * \details 
 * 0: Disable padding.
 * 1: Enable padding.
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_PKTINF_CFG . ENABLE_TX_PADDING
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_PKTINF_CFG_ENABLE_TX_PADDING  VTSS_BIT(25)

/** 
 * \brief
 * Enables insertion of 4 byte preamble if INSERT_PREAMBLE_ENA is set.
 * Followed by 4 byte preamble is DMAC.
 * Preamble will be 4 bytes only if per frame signal
 * host_tx_4byte_preamble_i (at MAC10G packet interface) is also asserted
 * along with this configuration.
 *
 * \details 
 * 0: Disable 4 byte preamble.
 * 1: Enable insertion of 4 byte preamble.
 *
 * Field: VTSS_HOST_MAC_CONFIG_MAC_PKTINF_CFG . ENABLE_4BYTE_PREAMBLE
 */
#define  VTSS_F_HOST_MAC_CONFIG_MAC_PKTINF_CFG_ENABLE_4BYTE_PREAMBLE  VTSS_BIT(27)

/**
 * Register Group: \a HOST_MAC:PAUSE_CFG
 *
 * 10G MAC pause configuration registers
 */


/** 
 * \brief Transmit pause frame control register
 *
 * \details
 * Register: \a HOST_MAC:PAUSE_CFG:PAUSE_TX_FRAME_CONTROL
 */
#define VTSS_HOST_MAC_PAUSE_CFG_PAUSE_TX_FRAME_CONTROL  VTSS_IOREG(0x03, 1, 0xf10b)

/** 
 * \brief
 * Pause value used when generating pause frames (except XON frames in mode
 * 2).
 *
 * \details 
 * Field: VTSS_HOST_MAC_PAUSE_CFG_PAUSE_TX_FRAME_CONTROL . MAC_TX_PAUSE_VALUE
 */
#define  VTSS_F_HOST_MAC_PAUSE_CFG_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_VALUE(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_HOST_MAC_PAUSE_CFG_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_VALUE     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_HOST_MAC_PAUSE_CFG_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Enables pause-generate module to wait for 10 clocks (for idle insertion)
 * before generating XOFF pause frame if MAC 10G is transmitting LPI idles.
 * This bit should be set only if LPI generation is forced in Kernel 10G
 * and a pause frame needs to be transmitted.
 *
 * \details 
 * 0: No idles are inserted before pause frame.
 * 1: Idles are inserted before pause frame.
 *
 * Field: VTSS_HOST_MAC_PAUSE_CFG_PAUSE_TX_FRAME_CONTROL . MAC_TX_WAIT_FOR_LPI_LOW
 */
#define  VTSS_F_HOST_MAC_PAUSE_CFG_PAUSE_TX_FRAME_CONTROL_MAC_TX_WAIT_FOR_LPI_LOW  VTSS_BIT(12)

/** 
 * \brief
 * Enables generation of stall signal when inserting XOFF/XON pause frame
 * into transmission stream or MAC Tx is in pause state. This can be used
 * to upper blocks as clock enables so that their pipeline is paused.
 *
 * \details 
 * 0: Disable stall generation.
 * 1: Enable stall generation.
 *
 * Field: VTSS_HOST_MAC_PAUSE_CFG_PAUSE_TX_FRAME_CONTROL . MAC_TX_USE_PAUSE_STALL_ENA
 */
#define  VTSS_F_HOST_MAC_PAUSE_CFG_PAUSE_TX_FRAME_CONTROL_MAC_TX_USE_PAUSE_STALL_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Determines the mode that the pause frame generator operates in
 *
 * \details 
 * 0: Pause frame generation is disabled
 * 1: Pause frames are generated only with the pause-value specified in the
 * MAC_PAUSE_VALUE register
 * 2: XON mode, pause frames with a pause value of 0 are generated when
 * traffic is to be restarted, in addition to generating pause frames as in
 * mode 1
 * 3: Reserved
 *
 * Field: VTSS_HOST_MAC_PAUSE_CFG_PAUSE_TX_FRAME_CONTROL . MAC_TX_PAUSE_MODE
 */
#define  VTSS_F_HOST_MAC_PAUSE_CFG_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HOST_MAC_PAUSE_CFG_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HOST_MAC_PAUSE_CFG_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Transmit pause frame control part 2 register
 *
 * \details
 * Register: \a HOST_MAC:PAUSE_CFG:PAUSE_TX_FRAME_CONTROL_2
 */
#define VTSS_HOST_MAC_PAUSE_CFG_PAUSE_TX_FRAME_CONTROL_2  VTSS_IOREG(0x03, 1, 0xf10c)

/** 
 * \brief
 * Pause frame interval.
 * Each count in the pause frame interval value corresponds to one cycle of
 * the MAC clock (PCS clock divided by 2), typically 156.25 MHz (6.4 ns
 * period). The interval is counted from the end of one pause frame to the
 * beginning of the next (assuming no other Tx traffic). The internal pause
 * interval timer is cleared when an XON pause frame is sent in Tx pause
 * mode 2.
 * The pause interval value of 0xffff gives the same pause frame interval
 * as the pause interval value of 0xfffe. Do not use a value of 0.
 *
 * \details 
 * Field: VTSS_HOST_MAC_PAUSE_CFG_PAUSE_TX_FRAME_CONTROL_2 . MAC_TX_PAUSE_INTERVAL
 */
#define  VTSS_F_HOST_MAC_PAUSE_CFG_PAUSE_TX_FRAME_CONTROL_2_MAC_TX_PAUSE_INTERVAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_MAC_PAUSE_CFG_PAUSE_TX_FRAME_CONTROL_2_MAC_TX_PAUSE_INTERVAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_MAC_PAUSE_CFG_PAUSE_TX_FRAME_CONTROL_2_MAC_TX_PAUSE_INTERVAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Receive pause frame control register
 *
 * \details
 * Register: \a HOST_MAC:PAUSE_CFG:PAUSE_RX_FRAME_CONTROL
 */
#define VTSS_HOST_MAC_PAUSE_CFG_PAUSE_RX_FRAME_CONTROL  VTSS_IOREG(0x03, 1, 0xf10d)

/** 
 * \brief
 * Enable pause frame detection at XGMII interface
 *
 * \details 
 * 0: Disable pause frame detection at XGMII interface
 * 1: Enable pause frame detection at XGMII interface
 *
 * Field: VTSS_HOST_MAC_PAUSE_CFG_PAUSE_RX_FRAME_CONTROL . MAC_RX_EARLY_PAUSE_DETECT_ENA
 */
#define  VTSS_F_HOST_MAC_PAUSE_CFG_PAUSE_RX_FRAME_CONTROL_MAC_RX_EARLY_PAUSE_DETECT_ENA  VTSS_BIT(16)

/** 
 * \brief
 * Configuration for XOFF indication before CRC check to meet pause
 * reaction time.
 * XOFF detection is done at XGMII interface depending on
 * MAC_RX_EARLY_PAUSE_DETECT_ENA. Information of CRC check failed for the
 * XOFF pause frame is also passed with a separate side band signal and so
 * that the pause timer is reloaded with previous pause value. 
 * This bit is unused if XOFF detection is done after the MAC.
 *
 * \details 
 * 0: XOFF indication at XGMII is done after CRC check.
 * 1: XOFF indication ar XGMII is done before CRC check.
 *
 * Field: VTSS_HOST_MAC_PAUSE_CFG_PAUSE_RX_FRAME_CONTROL . MAC_RX_PRE_CRC_MODE
 */
#define  VTSS_F_HOST_MAC_PAUSE_CFG_PAUSE_RX_FRAME_CONTROL_MAC_RX_PRE_CRC_MODE  VTSS_BIT(20)

/** 
 * \brief
 * Enables pause timer implementation in MAC Rx clock domain for the
 * received pause frame.
 *
 * \details 
 * 0: Disable pause timer implementation
 * 1: Enables pause timer implementation
 *
 * Field: VTSS_HOST_MAC_PAUSE_CFG_PAUSE_RX_FRAME_CONTROL . MAC_RX_PAUSE_TIMER_ENA
 */
#define  VTSS_F_HOST_MAC_PAUSE_CFG_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_TIMER_ENA  VTSS_BIT(12)

/** 
 * \brief
 * Enables pausing of transmission when a pause frame is received.
 *
 * \details 
 * 0: Disable pause reaction
 * 1: Enables pause reaction
 *
 * Field: VTSS_HOST_MAC_PAUSE_CFG_PAUSE_RX_FRAME_CONTROL . MAC_TX_PAUSE_REACT_ENA
 */
#define  VTSS_F_HOST_MAC_PAUSE_CFG_PAUSE_RX_FRAME_CONTROL_MAC_TX_PAUSE_REACT_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Enables dropping of pause frames in the pause frame detector.
 *
 * \details 
 * 0: Pause frames are not dropped
 * 1: Pause frames are dropped
 *
 * Field: VTSS_HOST_MAC_PAUSE_CFG_PAUSE_RX_FRAME_CONTROL . MAC_RX_PAUSE_FRAME_DROP_ENA
 */
#define  VTSS_F_HOST_MAC_PAUSE_CFG_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_FRAME_DROP_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Controls pause frame detection in receive path.
 *
 * \details 
 * 0: Pause frame detection is disabled
 * 1: Pause frame detection is enabled
 *
 * Field: VTSS_HOST_MAC_PAUSE_CFG_PAUSE_RX_FRAME_CONTROL . MAC_RX_PAUSE_MODE
 */
#define  VTSS_F_HOST_MAC_PAUSE_CFG_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_MODE  VTSS_BIT(0)


/** 
 * \brief Pause detector state register
 *
 * \details
 * Register: \a HOST_MAC:PAUSE_CFG:PAUSE_STATE
 */
#define VTSS_HOST_MAC_PAUSE_CFG_PAUSE_STATE  VTSS_IOREG(0x03, 1, 0xf10e)

/** 
 * \brief
 * Pause state indicator. 
 * Interface is paused when the pause timer is a non-zero value.
 *
 * \details 
 * 0: Not paused
 * 1: Paused
 *
 * Field: VTSS_HOST_MAC_PAUSE_CFG_PAUSE_STATE . PAUSE_STATE
 */
#define  VTSS_F_HOST_MAC_PAUSE_CFG_PAUSE_STATE_PAUSE_STATE  VTSS_BIT(0)


/** 
 * \brief MAC address LSB register
 *
 * \details
 * Register: \a HOST_MAC:PAUSE_CFG:MAC_ADDRESS_LSB
 */
#define VTSS_HOST_MAC_PAUSE_CFG_MAC_ADDRESS_LSB  VTSS_IOREG(0x03, 1, 0xf10f)


/** 
 * \brief MAC address MSB register
 *
 * \details
 * Register: \a HOST_MAC:PAUSE_CFG:MAC_ADDRESS_MSB
 */
#define VTSS_HOST_MAC_PAUSE_CFG_MAC_ADDRESS_MSB  VTSS_IOREG(0x03, 1, 0xf110)

/** 
 * \brief
 * Upper 16 bits of the MAC address
 *
 * \details 
 * Field: VTSS_HOST_MAC_PAUSE_CFG_MAC_ADDRESS_MSB . MAC_ADDRESS_MSB
 */
#define  VTSS_F_HOST_MAC_PAUSE_CFG_MAC_ADDRESS_MSB_MAC_ADDRESS_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_MAC_PAUSE_CFG_MAC_ADDRESS_MSB_MAC_ADDRESS_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_MAC_PAUSE_CFG_MAC_ADDRESS_MSB_MAC_ADDRESS_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_MAC:STATUS
 *
 * 10G MAC configuration registers
 */


/** 
 * \brief Sticky bit register
 *
 * \details
 * Clear the sticky bits by writing a 0 in the relevant bitgroups (writing
 * a 1 sets the bit)
 *
 * Register: \a HOST_MAC:STATUS:MAC_STICKY
 */
#define VTSS_HOST_MAC_STATUS_MAC_STICKY      VTSS_IOREG(0x03, 1, 0xf115)

/** 
 * \brief
 * Indicates an inter packet gap shrink was detected (IPG < 12 bytes).
 * Write 1 to clear the bit.
 *
 * \details 
 * 0: No IPG shrink was detected
 * 1: one or more IPG shrinks were detected
 *
 * Field: VTSS_HOST_MAC_STATUS_MAC_STICKY . RX_IPG_SHRINK_STICKY
 */
#define  VTSS_F_HOST_MAC_STATUS_MAC_STICKY_RX_IPG_SHRINK_STICKY  VTSS_BIT(9)

/** 
 * \brief
 * Indicates that a preamble shrink was detected (preamble < 8 bytes).
 * This sticky bit can only be set when the port is setup in 10 Gbps mode,
 * where frames with, for example, a 4 bytes preamble are discarded. In
 * addition, it requires that PRM_SHK_CHK_DIS = 0 and SFD_CHK_ENA = 1.
 * In SGMII mode, all preamble sizes down to 3 bytes (including SFD) are
 * accepted and do not cause this sticky bit to be set. Write 1 to clear
 * the bit.
 *
 * \details 
 * 0: No preamble shrink was detected
 * 1: one or more preamble shrinks were detected
 *
 * Field: VTSS_HOST_MAC_STATUS_MAC_STICKY . RX_PREAM_SHRINK_STICKY
 */
#define  VTSS_F_HOST_MAC_STATUS_MAC_STICKY_RX_PREAM_SHRINK_STICKY  VTSS_BIT(8)

/** 
 * \brief
 * This bit is set if a preamble check is enabled, an SOP is received, and
 * the following bytes do not match a 5555555555..55D5 pattern.
 * A 12 byte preamble of 55555555.55555555.555555D5 will not cause this
 * sticky bit to be set. This sticky bit can only be set when the port is
 * set up in 10 Gbps mode. Write 1 to clear the bit.
 *
 * \details 
 * 0: No preamble mismatch was detected
 * 1: one or more preamble matches were detected
 *
 * Field: VTSS_HOST_MAC_STATUS_MAC_STICKY . RX_PREAM_MISMATCH_STICKY
 */
#define  VTSS_F_HOST_MAC_STATUS_MAC_STICKY_RX_PREAM_MISMATCH_STICKY  VTSS_BIT(7)

/** 
 * \brief
 * This bit is set if an SOP is received and a following control character
 * is received within the preamble. (No data is passed to the host
 * interface of the MAC). Write 1 to clear the bit.
 *
 * \details 
 * 0: No preamble error was detected.
 * 1: One or more preamble errors were detected.
 *
 * Field: VTSS_HOST_MAC_STATUS_MAC_STICKY . RX_PREAM_ERR_STICKY
 */
#define  VTSS_F_HOST_MAC_STATUS_MAC_STICKY_RX_PREAM_ERR_STICKY  VTSS_BIT(6)

/** 
 * \brief
 * Indicates that a frame was received with a non-standard preamble. Write
 * 1 to clear the bit.
 *
 * \details 
 * 0: No MAC frame with non-standard preamble is received.
 * 1: One or more MAC frames are received with non-standard preamble.
 *
 * Field: VTSS_HOST_MAC_STATUS_MAC_STICKY . RX_NON_STD_PREAM_STICKY
 */
#define  VTSS_F_HOST_MAC_STATUS_MAC_STICKY_RX_NON_STD_PREAM_STICKY  VTSS_BIT(5)

/** 
 * \brief
 * Indicates that a frame with MPLS multicast was received. Write 1 to
 * clear the bit.
 *
 * \details 
 * 0: No MPLS multicast frame is received.
 * 1: One or more MPLS multicast frames are received.
 *
 * Field: VTSS_HOST_MAC_STATUS_MAC_STICKY . RX_MPLS_MC_STICKY
 */
#define  VTSS_F_HOST_MAC_STATUS_MAC_STICKY_RX_MPLS_MC_STICKY  VTSS_BIT(4)

/** 
 * \brief
 * Indicates that a frame with MPLS unicast was received. Write 1 to clear
 * the bit.
 *
 * \details 
 * 0: No MPLS unicast frame is received.
 * 1: One or more MPLS unicast frames are received.
 *
 * Field: VTSS_HOST_MAC_STATUS_MAC_STICKY . RX_MPLS_UC_STICKY
 */
#define  VTSS_F_HOST_MAC_STATUS_MAC_STICKY_RX_MPLS_UC_STICKY  VTSS_BIT(3)

/** 
 * \brief
 * Indicates that a frame was received with a VLAN tag. Write 1 to clear
 * the bit.
 *
 * \details 
 * 0: No VLAN tagged frame is received.
 * 1: One or more VLAN tagged frames are received.
 *
 * Field: VTSS_HOST_MAC_STATUS_MAC_STICKY . RX_TAG_STICKY
 */
#define  VTSS_F_HOST_MAC_STATUS_MAC_STICKY_RX_TAG_STICKY  VTSS_BIT(2)

/** 
 * \brief
 * Sticky bit indicating that the MAC transmit FIFO has dropped one or more
 * frames because of underrun. Write 1 to clear the bit.
 *
 * \details 
 * 0: No MAC Tx FIFO underrun has occured.
 * 1: One or more MAC Tx FIFO underruns have occurred.
 *
 * Field: VTSS_HOST_MAC_STATUS_MAC_STICKY . TX_UFLW_STICKY
 */
#define  VTSS_F_HOST_MAC_STATUS_MAC_STICKY_TX_UFLW_STICKY  VTSS_BIT(1)

/** 
 * \brief
 * Indicates that the transmit host initiated abort was executed. Write 1
 * to clear the bit.
 *
 * \details 
 * 0: No Tx frames aborted.
 * 1: Tx frames aborted.
 *
 * Field: VTSS_HOST_MAC_STATUS_MAC_STICKY . TX_ABORT_STICKY
 */
#define  VTSS_F_HOST_MAC_STATUS_MAC_STICKY_TX_ABORT_STICKY  VTSS_BIT(0)


/** 
 * \brief MAC sticky bits interrupt mask register
 *
 * \details
 * Register: \a HOST_MAC:STATUS:MAC_STICKY_MASK
 */
#define VTSS_HOST_MAC_STATUS_MAC_STICKY_MASK  VTSS_IOREG(0x03, 1, 0xf116)

/** 
 * \brief
 * Interrupt mask for RX_IPG_SHRINK_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_HOST_MAC_STATUS_MAC_STICKY_MASK . RX_IPG_SHRINK_STICKY_MASK
 */
#define  VTSS_F_HOST_MAC_STATUS_MAC_STICKY_MASK_RX_IPG_SHRINK_STICKY_MASK  VTSS_BIT(9)

/** 
 * \brief
 * Interrupt mask for RX_PREAM_SHRINK_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_HOST_MAC_STATUS_MAC_STICKY_MASK . RX_PREAM_SHRINK_STICKY_MASK
 */
#define  VTSS_F_HOST_MAC_STATUS_MAC_STICKY_MASK_RX_PREAM_SHRINK_STICKY_MASK  VTSS_BIT(8)

/** 
 * \brief
 * Interrupt mask for RX_PREAM_MISMATCH_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_HOST_MAC_STATUS_MAC_STICKY_MASK . RX_PREAM_MISMATCH_STICKY_MASK
 */
#define  VTSS_F_HOST_MAC_STATUS_MAC_STICKY_MASK_RX_PREAM_MISMATCH_STICKY_MASK  VTSS_BIT(7)

/** 
 * \brief
 * Interrupt mask for RX_PREAM_ERR_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_HOST_MAC_STATUS_MAC_STICKY_MASK . RX_PREAM_ERR_STICKY_MASK
 */
#define  VTSS_F_HOST_MAC_STATUS_MAC_STICKY_MASK_RX_PREAM_ERR_STICKY_MASK  VTSS_BIT(6)

/** 
 * \brief
 * Interrupt mask for RX_NON_STD_PREAM_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_HOST_MAC_STATUS_MAC_STICKY_MASK . RX_NON_STD_PREAM_STICKY_MASK
 */
#define  VTSS_F_HOST_MAC_STATUS_MAC_STICKY_MASK_RX_NON_STD_PREAM_STICKY_MASK  VTSS_BIT(5)

/** 
 * \brief
 * Interrupt mask for RX_MPLS_MC_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_HOST_MAC_STATUS_MAC_STICKY_MASK . RX_MPLS_MC_STICKY_MASK
 */
#define  VTSS_F_HOST_MAC_STATUS_MAC_STICKY_MASK_RX_MPLS_MC_STICKY_MASK  VTSS_BIT(4)

/** 
 * \brief
 * Interrupt mask for RX_MPLS_UC_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_HOST_MAC_STATUS_MAC_STICKY_MASK . RX_MPLS_UC_STICKY_MASK
 */
#define  VTSS_F_HOST_MAC_STATUS_MAC_STICKY_MASK_RX_MPLS_UC_STICKY_MASK  VTSS_BIT(3)

/** 
 * \brief
 * Interrupt mask for RX_TAG_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_HOST_MAC_STATUS_MAC_STICKY_MASK . RX_TAG_STICKY_MASK
 */
#define  VTSS_F_HOST_MAC_STATUS_MAC_STICKY_MASK_RX_TAG_STICKY_MASK  VTSS_BIT(2)

/** 
 * \brief
 * Interrupt mask for TX_UFLW_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_HOST_MAC_STATUS_MAC_STICKY_MASK . TX_UFLW_STICKY_MASK
 */
#define  VTSS_F_HOST_MAC_STATUS_MAC_STICKY_MASK_TX_UFLW_STICKY_MASK  VTSS_BIT(1)

/** 
 * \brief
 * Interrupt mask for TX_ABORT_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_HOST_MAC_STATUS_MAC_STICKY_MASK . TX_ABORT_STICKY_MASK
 */
#define  VTSS_F_HOST_MAC_STATUS_MAC_STICKY_MASK_TX_ABORT_STICKY_MASK  VTSS_BIT(0)

/**
 * Register Group: \a HOST_MAC:STATISTICS_32BIT
 *
 * Not documented
 */


/** 
 * \brief RX_HIH checksum error counter
 *
 * \details
 * If HIH CRC checking is enabled, this counter counts the number of frames
 * discarded because of HIH CRC errors.
 *
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_HIH_CKSM_ERR_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_HIH_CKSM_ERR_CNT  VTSS_IOREG(0x03, 1, 0xf117)


/** 
 * \brief Rx XGMII protocol error counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_XGMII_PROT_ERR_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_XGMII_PROT_ERR_CNT  VTSS_IOREG(0x03, 1, 0xf118)


/** 
 * \brief Rx symbol carrier error counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_SYMBOL_ERR_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_SYMBOL_ERR_CNT  VTSS_IOREG(0x03, 1, 0xf119)


/** 
 * \brief Rx pause frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_PAUSE_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_PAUSE_CNT  VTSS_IOREG(0x03, 1, 0xf11a)


/** 
 * \brief Rx control frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_UNSUP_OPCODE_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_UNSUP_OPCODE_CNT  VTSS_IOREG(0x03, 1, 0xf11b)


/** 
 * \brief Rx unicast frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_UC_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_UC_CNT  VTSS_IOREG(0x03, 1, 0xf11c)


/** 
 * \brief Rx multicast frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_MC_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_MC_CNT  VTSS_IOREG(0x03, 1, 0xf11d)


/** 
 * \brief Rx broadcast frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_BC_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_BC_CNT  VTSS_IOREG(0x03, 1, 0xf11e)


/** 
 * \brief Rx CRC error counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_CRC_ERR_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_CRC_ERR_CNT  VTSS_IOREG(0x03, 1, 0xf11f)


/** 
 * \brief Rx undersize counter (valid frame format)
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_UNDERSIZE_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_UNDERSIZE_CNT  VTSS_IOREG(0x03, 1, 0xf120)


/** 
 * \brief Rx undersize counter (CRC error)
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_FRAGMENTS_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_FRAGMENTS_CNT  VTSS_IOREG(0x03, 1, 0xf121)


/** 
 * \brief Rx in-range length error counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_IN_RANGE_LEN_ERR_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_IN_RANGE_LEN_ERR_CNT  VTSS_IOREG(0x03, 1, 0xf122)


/** 
 * \brief Rx out-of-range length error counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_OUT_OF_RANGE_LEN_ERR_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_OUT_OF_RANGE_LEN_ERR_CNT  VTSS_IOREG(0x03, 1, 0xf123)


/** 
 * \brief Rx oversize counter (valid frame format)
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_OVERSIZE_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_OVERSIZE_CNT  VTSS_IOREG(0x03, 1, 0xf124)


/** 
 * \brief Rx jabbers counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_JABBERS_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_JABBERS_CNT  VTSS_IOREG(0x03, 1, 0xf125)


/** 
 * \brief Rx 64 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_SIZE64_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE64_CNT  VTSS_IOREG(0x03, 1, 0xf126)


/** 
 * \brief Rx 65-127 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_SIZE65TO127_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE65TO127_CNT  VTSS_IOREG(0x03, 1, 0xf127)


/** 
 * \brief Rx 128-255 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_SIZE128TO255_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE128TO255_CNT  VTSS_IOREG(0x03, 1, 0xf128)


/** 
 * \brief Rx 256-511 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_SIZE256TO511_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE256TO511_CNT  VTSS_IOREG(0x03, 1, 0xf129)


/** 
 * \brief Rx 512-1023 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_SIZE512TO1023_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE512TO1023_CNT  VTSS_IOREG(0x03, 1, 0xf12a)


/** 
 * \brief Rx 1024-1518 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_SIZE1024TO1518_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE1024TO1518_CNT  VTSS_IOREG(0x03, 1, 0xf12b)


/** 
 * \brief Rx 1519 to max. length byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_SIZE1519TOMAX_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_SIZE1519TOMAX_CNT  VTSS_IOREG(0x03, 1, 0xf12c)


/** 
 * \brief Rx inter packet gap shrink counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:RX_IPG_SHRINK_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_RX_IPG_SHRINK_CNT  VTSS_IOREG(0x03, 1, 0xf12d)


/** 
 * \brief Tx pause frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:TX_PAUSE_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_TX_PAUSE_CNT  VTSS_IOREG(0x03, 1, 0xf12e)


/** 
 * \brief Tx unicast frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:TX_UC_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_TX_UC_CNT  VTSS_IOREG(0x03, 1, 0xf12f)


/** 
 * \brief Tx multicast frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:TX_MC_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_TX_MC_CNT  VTSS_IOREG(0x03, 1, 0xf130)


/** 
 * \brief Tx broadcast frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:TX_BC_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_TX_BC_CNT  VTSS_IOREG(0x03, 1, 0xf131)


/** 
 * \brief Tx 64 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:TX_SIZE64_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE64_CNT  VTSS_IOREG(0x03, 1, 0xf132)


/** 
 * \brief Tx 65-127 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:TX_SIZE65TO127_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE65TO127_CNT  VTSS_IOREG(0x03, 1, 0xf133)


/** 
 * \brief Tx 128-255 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:TX_SIZE128TO255_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE128TO255_CNT  VTSS_IOREG(0x03, 1, 0xf134)


/** 
 * \brief Tx 256-511 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:TX_SIZE256TO511_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE256TO511_CNT  VTSS_IOREG(0x03, 1, 0xf135)


/** 
 * \brief Tx 512-1023 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:TX_SIZE512TO1023_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE512TO1023_CNT  VTSS_IOREG(0x03, 1, 0xf136)


/** 
 * \brief Tx 1024-1518 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:TX_SIZE1024TO1518_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE1024TO1518_CNT  VTSS_IOREG(0x03, 1, 0xf137)


/** 
 * \brief Tx 1519 to max. length byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:STATISTICS_32BIT:TX_SIZE1519TOMAX_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_32BIT_TX_SIZE1519TOMAX_CNT  VTSS_IOREG(0x03, 1, 0xf138)

/**
 * Register Group: \a HOST_MAC:STATISTICS_40BIT
 *
 * Not documented
 */


/** 
 * \brief Rx bad bytes counter (LSB)
 *
 * \details
 * The number of received bytes in bad frames (LSBs only).
 *
 * Register: \a HOST_MAC:STATISTICS_40BIT:RX_BAD_BYTES_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_40BIT_RX_BAD_BYTES_CNT  VTSS_IOREG(0x03, 1, 0xf139)


/** 
 * \brief Rx bad bytes counter (MSB)
 *
 * \details
 * The number of received bytes in bad frames (MSBs only).
 *
 * Register: \a HOST_MAC:STATISTICS_40BIT:RX_BAD_BYTES_MSB_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_40BIT_RX_BAD_BYTES_MSB_CNT  VTSS_IOREG(0x03, 1, 0xf13a)

/** 
 * \brief
 * The number of received bytes in bad frames (MSBs only).
 *
 * \details 
 * Counter can be written by software.
 *
 * Field: VTSS_HOST_MAC_STATISTICS_40BIT_RX_BAD_BYTES_MSB_CNT . RX_BAD_BYTES_MSB_CNT
 */
#define  VTSS_F_HOST_MAC_STATISTICS_40BIT_RX_BAD_BYTES_MSB_CNT_RX_BAD_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_MAC_STATISTICS_40BIT_RX_BAD_BYTES_MSB_CNT_RX_BAD_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_MAC_STATISTICS_40BIT_RX_BAD_BYTES_MSB_CNT_RX_BAD_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Rx OK bytes counter (LSB)
 *
 * \details
 * The number of received bytes in good frames (LSBs only).
 *
 * Register: \a HOST_MAC:STATISTICS_40BIT:RX_OK_BYTES_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_40BIT_RX_OK_BYTES_CNT  VTSS_IOREG(0x03, 1, 0xf13b)


/** 
 * \brief Rx OK bytes counter (MSB)
 *
 * \details
 * The number of received bytes in good frames (MSBs only).
 *
 * Register: \a HOST_MAC:STATISTICS_40BIT:RX_OK_BYTES_MSB_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_40BIT_RX_OK_BYTES_MSB_CNT  VTSS_IOREG(0x03, 1, 0xf13c)

/** 
 * \brief
 * The number of received bytes in good frames (MSBs only).
 *
 * \details 
 * Counter can be written by software.
 *
 * Field: VTSS_HOST_MAC_STATISTICS_40BIT_RX_OK_BYTES_MSB_CNT . RX_OK_BYTES_MSB_CNT
 */
#define  VTSS_F_HOST_MAC_STATISTICS_40BIT_RX_OK_BYTES_MSB_CNT_RX_OK_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_MAC_STATISTICS_40BIT_RX_OK_BYTES_MSB_CNT_RX_OK_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_MAC_STATISTICS_40BIT_RX_OK_BYTES_MSB_CNT_RX_OK_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Rx bytes received counter (LSB)
 *
 * \details
 * The number of good, bad, and framing bytes received (LSBs only).
 *
 * Register: \a HOST_MAC:STATISTICS_40BIT:RX_IN_BYTES_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_40BIT_RX_IN_BYTES_CNT  VTSS_IOREG(0x03, 1, 0xf13d)


/** 
 * \brief Rx bytes received counter (MSB)
 *
 * \details
 * The number of good, bad, and framing bytes received (MSBs only).
 *
 * Register: \a HOST_MAC:STATISTICS_40BIT:RX_IN_BYTES_MSB_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_40BIT_RX_IN_BYTES_MSB_CNT  VTSS_IOREG(0x03, 1, 0xf13e)

/** 
 * \brief
 * The number of good, bad, and framing bytes received (MSBs only).
 *
 * \details 
 * Counter can be written by software.
 *
 * Field: VTSS_HOST_MAC_STATISTICS_40BIT_RX_IN_BYTES_MSB_CNT . RX_IN_BYTES_MSB_CNT
 */
#define  VTSS_F_HOST_MAC_STATISTICS_40BIT_RX_IN_BYTES_MSB_CNT_RX_IN_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_MAC_STATISTICS_40BIT_RX_IN_BYTES_MSB_CNT_RX_IN_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_MAC_STATISTICS_40BIT_RX_IN_BYTES_MSB_CNT_RX_IN_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Tx OK bytes counter (LSB)
 *
 * \details
 * The number of bytes transmitted successfully (LSBs only).
 *
 * Register: \a HOST_MAC:STATISTICS_40BIT:TX_OK_BYTES_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_40BIT_TX_OK_BYTES_CNT  VTSS_IOREG(0x03, 1, 0xf13f)


/** 
 * \brief Tx OK bytes counter (MSB)
 *
 * \details
 * The number of bytes transmitted successfully (MSBs only).
 *
 * Register: \a HOST_MAC:STATISTICS_40BIT:TX_OK_BYTES_MSB_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_40BIT_TX_OK_BYTES_MSB_CNT  VTSS_IOREG(0x03, 1, 0xf140)

/** 
 * \brief
 * The number of bytes transmitted successfully (MSBs only).
 *
 * \details 
 * Counter can be written by software.
 *
 * Field: VTSS_HOST_MAC_STATISTICS_40BIT_TX_OK_BYTES_MSB_CNT . TX_OK_BYTES_MSB_CNT
 */
#define  VTSS_F_HOST_MAC_STATISTICS_40BIT_TX_OK_BYTES_MSB_CNT_TX_OK_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_MAC_STATISTICS_40BIT_TX_OK_BYTES_MSB_CNT_TX_OK_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_MAC_STATISTICS_40BIT_TX_OK_BYTES_MSB_CNT_TX_OK_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Tx bytes transmitted counter (LSB)
 *
 * \details
 * The number of good, bad, and framing bytes transmitted (LSBs only).
 *
 * Register: \a HOST_MAC:STATISTICS_40BIT:TX_OUT_BYTES_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_40BIT_TX_OUT_BYTES_CNT  VTSS_IOREG(0x03, 1, 0xf141)


/** 
 * \brief Tx bytes transmitted counter (MSB)
 *
 * \details
 * The number of good, bad, and framing bytes transmitted (MSBs only).
 *
 * Register: \a HOST_MAC:STATISTICS_40BIT:TX_OUT_BYTES_MSB_CNT
 */
#define VTSS_HOST_MAC_STATISTICS_40BIT_TX_OUT_BYTES_MSB_CNT  VTSS_IOREG(0x03, 1, 0xf142)

/** 
 * \brief
 * The number of good, bad, and framing bytes transmitted (MSBs only).
 *
 * \details 
 * Counter can be written by software.
 *
 * Field: VTSS_HOST_MAC_STATISTICS_40BIT_TX_OUT_BYTES_MSB_CNT . TX_OUT_BYTES_MSB_CNT
 */
#define  VTSS_F_HOST_MAC_STATISTICS_40BIT_TX_OUT_BYTES_MSB_CNT_TX_OUT_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_MAC_STATISTICS_40BIT_TX_OUT_BYTES_MSB_CNT_TX_OUT_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_MAC_STATISTICS_40BIT_TX_OUT_BYTES_MSB_CNT_TX_OUT_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


#endif /* _VTSS_VENICE_REGS_HOST_MAC_H_ */
