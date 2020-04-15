/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

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

#ifndef _VTSS_FA_REGS_DEV10G_H_
#define _VTSS_FA_REGS_DEV10G_H_

#include "vtss_fa_regs_common.h"

/***********************************************************************
 *
 * Target: \a DEV10G
 *
 * \see vtss_target_DEV10G_e
 *
 * VAUI @ 12Gbps 2 lanes, XAUI @ 10 Gbps, XAUI @ 12 Gbps, VAUI @ 10Gbps 2
 * lanes and SGMII @ 10/100/1000/2500 Mbps
 *
 ***********************************************************************/

/**
 * Register Group: \a DEV10G:MAC_CFG_STATUS
 *
 * MAC10G Configuration and Status Registers
 */


/** 
 * \brief Mode Configuration Register
 *
 * \details
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_ENA_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MAC_ENA_CFG(target)      VTSS_IOREG(target,0x0)

/** 
 * \brief
 * Enable Receiver.
 *
 * \details 
 * '0': Disabled
 * '1': Enabled.
 *
 * Field: ::VTSS_DEV10G_MAC_ENA_CFG . RX_ENA
 */
#define  VTSS_F_DEV10G_MAC_ENA_CFG_RX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_MAC_ENA_CFG_RX_ENA     VTSS_BIT(4)
#define  VTSS_X_DEV10G_MAC_ENA_CFG_RX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enable Transmitter.
 *
 * \details 
 * '0': Disabled
 * '1': Enabled.
 *
 * Field: ::VTSS_DEV10G_MAC_ENA_CFG . TX_ENA
 */
#define  VTSS_F_DEV10G_MAC_ENA_CFG_TX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_MAC_ENA_CFG_TX_ENA     VTSS_BIT(0)
#define  VTSS_X_DEV10G_MAC_ENA_CFG_TX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Mode Configuration Register
 *
 * \details
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_MODE_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MAC_MODE_CFG(target)     VTSS_IOREG(target,0x1)

/** 
 * \brief
 * On a given link, Pause Frames can be either "Link Pause frames" or
 * "Tunnel Pause Frames"."Link Pause Frames" will have standard preamble,
 * while "Tunnel Pause Frames" will have HIH in the preamble.For "Link
 * Pause Frames" MAC10G should not verify HIH CKSM, while for "Tunnel Pause
 * Frames" MAC10G should verify HIH CKSM.
 *
 * \details 
 * 0: Pause frames are expected to be Link Pause frames - No HIH CKSM
 * verification in MAC10G
 * 1: Pause frames are expected to be Tunnel Pause frames - HIH CKSM is
 * verified in MAC10G
 *
 * Field: ::VTSS_DEV10G_MAC_MODE_CFG . TUNNEL_PAUSE_FRAMES
 */
#define  VTSS_F_DEV10G_MAC_MODE_CFG_TUNNEL_PAUSE_FRAMES(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DEV10G_MAC_MODE_CFG_TUNNEL_PAUSE_FRAMES  VTSS_BIT(16)
#define  VTSS_X_DEV10G_MAC_MODE_CFG_TUNNEL_PAUSE_FRAMES(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * This register configures the format of the preamble.This supports:1)
 * Standard preamble = 0xFB555555555555D52) Minimum preamble = 0xFB3) Host
 * Interface Header (HIH) located before the SFD4) Host Interface Header
 * (HIH) located after the SFD - default CRC5) Host Interface Header (HIH)
 * located after the SFD - HIH included in CRC
 *
 * \details 
 * 0: Standard Preamble
 * 1: Minimum Preamble = 0xFB
 * 2: HIH before SFD -	default CRC = 0xFB H0 H1 H2 H3 0x55 0x55 0xD5
 * 3: HIH after SFD - default CRC = 0xFB 0x55 0x55 0xD5 H0 H1 H2 H3
 * 4: HIH after SFD - HIH in CRC = 0xFB 0x55 0x55 0xD5 H0 H1 H2 H3
 * 5 - 7: reserved
 * 
 * HIH is 4 bytes: H0 H1 H2 H3
 *
 * Field: ::VTSS_DEV10G_MAC_MODE_CFG . MAC_PREAMBLE_CFG
 */
#define  VTSS_F_DEV10G_MAC_MODE_CFG_MAC_PREAMBLE_CFG(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_DEV10G_MAC_MODE_CFG_MAC_PREAMBLE_CFG     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_DEV10G_MAC_MODE_CFG_MAC_PREAMBLE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/** 
 * \brief
 * Register configures the format of the IPG.1) Normal IPG : Averaging IPG
 * for average of 12 bytes2) Shrinked IPG : Minimum IPG of 4 - 7 bytes
 * (Incl. Terminate Character and IDLE BYTEs)
 *
 * \details 
 * '0': Normal IPG.
 * '1': Shrink IPG.
 *
 * Field: ::VTSS_DEV10G_MAC_MODE_CFG . MAC_IPG_CFG
 */
#define  VTSS_F_DEV10G_MAC_MODE_CFG_MAC_IPG_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV10G_MAC_MODE_CFG_MAC_IPG_CFG  VTSS_BIT(8)
#define  VTSS_X_DEV10G_MAC_MODE_CFG_MAC_IPG_CFG(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * XGMII Generator Mode Enable: In this mode, the transmitter will not
 * insert the preamble and the end-of-packet control characters. Data that
 * matches one of the XGMII control characters will be translated from a
 * data character to a control character. This mode enables the MAC 10G to
 * transmit e.g. special XGMII messages and/or malformed frames (in terms
 * of the XGMII protocol).
 *
 * \details 
 * '0': XGMII Generator Mode Disabled
 * '1': XGMII Generator Mode Enabled.
 *
 * Field: ::VTSS_DEV10G_MAC_MODE_CFG . XGMII_GEN_MODE_ENA
 */
#define  VTSS_F_DEV10G_MAC_MODE_CFG_XGMII_GEN_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_MAC_MODE_CFG_XGMII_GEN_MODE_ENA  VTSS_BIT(4)
#define  VTSS_X_DEV10G_MAC_MODE_CFG_XGMII_GEN_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * When asserted (=1) MAC10G must check HIH checksum and discard frames if
 * HIH checksum is not valid.When deasserted (=0) MAC10G must disregard the
 * HIH checksum.
 *
 * \details 
 * = 0 ; MAC10G should disregard the HIH CKSM.
 * = 1 ; MAC10G should discard any frame with invalid CKSM
 *
 * Field: ::VTSS_DEV10G_MAC_MODE_CFG . HIH_CRC_CHECK
 */
#define  VTSS_F_DEV10G_MAC_MODE_CFG_HIH_CRC_CHECK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_MAC_MODE_CFG_HIH_CRC_CHECK  VTSS_BIT(0)
#define  VTSS_X_DEV10G_MAC_MODE_CFG_HIH_CRC_CHECK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Max Length Configuration Register
 *
 * \details
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_MAXLEN_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MAC_MAXLEN_CFG(target)   VTSS_IOREG(target,0x2)

/** 
 * \brief
 * Configures whether the Max Length Check takes the number of Q tags into
 * consideration when assessing if a frame is too long.If asserted,  - 4
 * bytes will be added to MAX_LEN for single tagged frame. - 8 bytes will
 * be added to MAX_LEN for double tagged frame. - 12 bytes will be added to
 * MAX_LEN for triple tagged frame.
 *
 * \details 
 * '0' : Only check max frame length against MAX_LEN
 * '1' : Add 4/8/12 bytes to MAX_LEN when checking for max frame length
 *
 * Field: ::VTSS_DEV10G_MAC_MAXLEN_CFG . MAX_LEN_TAG_CHK
 */
#define  VTSS_F_DEV10G_MAC_MAXLEN_CFG_MAX_LEN_TAG_CHK(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DEV10G_MAC_MAXLEN_CFG_MAX_LEN_TAG_CHK  VTSS_BIT(16)
#define  VTSS_X_DEV10G_MAC_MAXLEN_CFG_MAX_LEN_TAG_CHK(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * The maximum frame length accepted by the Receive Module. If the length
 * is exceeded, this is indicated in the Statistics Engine (LONG_FRAME).
 * The maximum length is automatically adjusted to accommodate maximum
 * sized frames containing a VLAN tag - given that the MAC is configured to
 * be VLAN aware (default):The default value of 2000 is as per 802.3 for
 * Envelope frames.
 *
 * \details 
 * Field: ::VTSS_DEV10G_MAC_MAXLEN_CFG . MAX_LEN
 */
#define  VTSS_F_DEV10G_MAC_MAXLEN_CFG_MAX_LEN(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DEV10G_MAC_MAXLEN_CFG_MAX_LEN     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DEV10G_MAC_MAXLEN_CFG_MAX_LEN(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Register to specify no.of tags supported
 *
 * \details
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_NUM_TAGS_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MAC_NUM_TAGS_CFG(target)  VTSS_IOREG(target,0x3)

/** 
 * \brief
 * Configuration for number of consecutive VLAN Tags supported by the
 * MAC.Maximum value is 3.
 *
 * \details 
 * '0': No tags are detected by MAC.
 * 'n': Maximum of n consecutive VLAN Tags are detected by the MAC and
 * accordingly MAX LEN is modified for frame length calculations.
 *
 * Field: ::VTSS_DEV10G_MAC_NUM_TAGS_CFG . NUM_TAGS
 */
#define  VTSS_F_DEV10G_MAC_NUM_TAGS_CFG_NUM_TAGS(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DEV10G_MAC_NUM_TAGS_CFG_NUM_TAGS     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DEV10G_MAC_NUM_TAGS_CFG_NUM_TAGS(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief VLAN / Service tag configuration register
 *
 * \details
 * The MAC can be configured to accept 0, 1, 2 and 3 tags and the TAG value
 * can be user-defined.
 *
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_TAGS_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 * @param ri Register: MAC_TAGS_CFG (??), 0-2
 */
#define VTSS_DEV10G_MAC_TAGS_CFG(target,ri)  VTSS_IOREG(target,0x4 + (ri))

/** 
 * \brief
 * This field defines which value is regarded as a VLAN/Service tag -
 * besides 0x8100 and 0x88A8. The value is used for all ALL tag positions.
 * I.e. a double tagged frame can have the following tag values:(INNER_TAG,
 * OUTER_TAG):( 0x8100, 0x8100 )( 0x8100, TAG_ID ) or( TAG_ID, TAG_ID )
 *
 * \details 
 * "0x8100" - Standard Ethernet Bridge ethertype (C-tag)
 * "0x88A8" - Provider Bridge Ethertype  (S-tag)
 *
 * Field: ::VTSS_DEV10G_MAC_TAGS_CFG . TAG_ID
 */
#define  VTSS_F_DEV10G_MAC_TAGS_CFG_TAG_ID(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DEV10G_MAC_TAGS_CFG_TAG_ID     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DEV10G_MAC_TAGS_CFG_TAG_ID(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Enables TAG_ID apart from standard 0x8100 and 0x88A8 for Tag
 * comparision.
 *
 * \details 
 * '0': The MAC does not take TAG_ID for tag identification.
 * '1': The MAC looks for tag according to encoding of TAG_ID
 *
 * Field: ::VTSS_DEV10G_MAC_TAGS_CFG . TAG_ENA
 */
#define  VTSS_F_DEV10G_MAC_TAGS_CFG_TAG_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_MAC_TAGS_CFG_TAG_ENA   VTSS_BIT(4)
#define  VTSS_X_DEV10G_MAC_TAGS_CFG_TAG_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief Advanced Check Feature Configuration Register
 *
 * \details
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_ADV_CHK_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MAC_ADV_CHK_CFG(target)  VTSS_IOREG(target,0x7)

/** 
 * \brief
 * Extended End Of Packet Check: Specifies the requirement for the Rx
 * column when holding an EOP character.
 *
 * \details 
 * '0': The values of the remaining Rx lanes of a column holding an EOP are
 * ignored. E.g. if lane 1 holds an EOP, the value of lanes 2 and 3 are
 * ignored
 * '1': A received frame is error-marked if an Error character is received
 * in any lane of the column holding the EOP character. E.g. if lane 1
 * holds an EOP, the frame is error-marked if lanes 0, 2, or 3 holds an
 * Error character.
 *
 * Field: ::VTSS_DEV10G_MAC_ADV_CHK_CFG . EXT_EOP_CHK_ENA
 */
#define  VTSS_F_DEV10G_MAC_ADV_CHK_CFG_EXT_EOP_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_DEV10G_MAC_ADV_CHK_CFG_EXT_EOP_CHK_ENA  VTSS_BIT(24)
#define  VTSS_X_DEV10G_MAC_ADV_CHK_CFG_EXT_EOP_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * Extended Start Of Packet Check Enable: Specifies the requirement for the
 * Rx column prior to SOP character.
 *
 * \details 
 * '0': Value of Rx column at the XGMII interface prior to a SOP character
 * is ignored
 * '1': An IDLE column at the XGMII interface must be received prior to a
 * SOP character for the MAC to detect a start of frame.
 *
 * Field: ::VTSS_DEV10G_MAC_ADV_CHK_CFG . EXT_SOP_CHK_ENA
 */
#define  VTSS_F_DEV10G_MAC_ADV_CHK_CFG_EXT_SOP_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_DEV10G_MAC_ADV_CHK_CFG_EXT_SOP_CHK_ENA  VTSS_BIT(20)
#define  VTSS_X_DEV10G_MAC_ADV_CHK_CFG_EXT_SOP_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Start-of-Frame-Delimiter Check Enable: Specifies the requirement for a
 * successful frame reception.When disabled (='0'), MAC10G will assume that
 * preamble is 8 bytes (incl. SOP & SFD) when SOP is received. No checking
 * of SFD is carried out.When enabled (='1'), MAC10G will search for SFD in
 * lane 3/7 after reception of SOP, before accepting frame data. MAC10G
 * will search for SFD until SFD is found or a control character is
 * encountered.
 *
 * \details 
 * '0': Skip SFD check
 * '1': Strict SFD check enabled, i.e. the SFD must be "D5" for a
 * successful frame reception.
 *
 * Field: ::VTSS_DEV10G_MAC_ADV_CHK_CFG . SFD_CHK_ENA
 */
#define  VTSS_F_DEV10G_MAC_ADV_CHK_CFG_SFD_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DEV10G_MAC_ADV_CHK_CFG_SFD_CHK_ENA  VTSS_BIT(16)
#define  VTSS_X_DEV10G_MAC_ADV_CHK_CFG_SFD_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Preamble Shrink Check Disable:The MAC can be setup to discard a frame,
 * if a SFD is received in lane 3 of the column containing the SOP. If
 * stacking tags must be supported, the MAC must accept any data byte at
 * this position.
 *
 * \details 
 * '0': Frames with a SFD in lane 3 of the column containing the SOP are
 * discarded.
 * '1': Frames with a SFD in lane 3 of the column containing the SOP are
 * NOT discarded.
 *
 * Field: ::VTSS_DEV10G_MAC_ADV_CHK_CFG . PRM_SHK_CHK_DIS
 */
#define  VTSS_F_DEV10G_MAC_ADV_CHK_CFG_PRM_SHK_CHK_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DEV10G_MAC_ADV_CHK_CFG_PRM_SHK_CHK_DIS  VTSS_BIT(12)
#define  VTSS_X_DEV10G_MAC_ADV_CHK_CFG_PRM_SHK_CHK_DIS(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Preamble Check Enable: Specifies the preamble requirement for a
 * successful frame reception.
 *
 * \details 
 * '0': Skip preamble check. A SOP control character is sufficient for a
 * successful frame reception. The minimum allowed preamble size is still 8
 * bytes (incl. SOP and SFD) but the preamble bytes between the SOP and SFD
 * can have any data value.
 * '1': Strict preamble check enabled, i.e. the last 6 bytes of a preamble
 * - prior to the SFD - must all be equal to 0x55 for a successful frame
 * reception. For preambles larger than 8 bytes, only the last 6 preamble
 * bytes prior to the SFD are checked when this bit is set to 1.
 *
 * Field: ::VTSS_DEV10G_MAC_ADV_CHK_CFG . PRM_CHK_ENA
 */
#define  VTSS_F_DEV10G_MAC_ADV_CHK_CFG_PRM_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV10G_MAC_ADV_CHK_CFG_PRM_CHK_ENA  VTSS_BIT(8)
#define  VTSS_X_DEV10G_MAC_ADV_CHK_CFG_PRM_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Out-Of-Range Error Check Enable: Determines whether or not a received
 * frame should be discarded if the frame length field is out of range.
 *
 * \details 
 * '0': Out-of-range errors are ignored
 * '1': A frame is discarded if the frame length field value is out of
 * range
 *
 * Field: ::VTSS_DEV10G_MAC_ADV_CHK_CFG . OOR_ERR_ENA
 */
#define  VTSS_F_DEV10G_MAC_ADV_CHK_CFG_OOR_ERR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_MAC_ADV_CHK_CFG_OOR_ERR_ENA  VTSS_BIT(4)
#define  VTSS_X_DEV10G_MAC_ADV_CHK_CFG_OOR_ERR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * In-Range Error Check Enable: Determines whether or not a received frame
 * should be discarded if the frame length does not match the frame PDU
 * size:
 *
 * \details 
 * '0':
 * Frames which have a frame length field inconsistent with the actual
 * frame length are not error-marked
 * '1': Frames with inconsistent frame length fields are error marked and
 * will be discarded by the Rx Queue System.
 *
 * Field: ::VTSS_DEV10G_MAC_ADV_CHK_CFG . INR_ERR_ENA
 */
#define  VTSS_F_DEV10G_MAC_ADV_CHK_CFG_INR_ERR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_MAC_ADV_CHK_CFG_INR_ERR_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV10G_MAC_ADV_CHK_CFG_INR_ERR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Link Fault Signaling Register
 *
 * \details
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_LFS_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MAC_LFS_CFG(target)      VTSS_IOREG(target,0x8)

/** 
 * \brief
 * Compare IEEE802.3 figure 46-11 Link Fault Signaling State Diagram.
 * Configures the number of columns received not containing a
 * fault_sequence required to get back into the INIT state. Should be set
 * to 127 for standard operation mode. Might be reduced in USXGMII mode in
 * network port speeds that require a replication size the replicator will
 * remove some of the idle samples.
 *
 * \details 
 * Number of non-fault ordered sets required to get back to INIT state.
 *
 * Field: ::VTSS_DEV10G_MAC_LFS_CFG . LFS_MAX_NON_FAULT_SEQ
 */
#define  VTSS_F_DEV10G_MAC_LFS_CFG_LFS_MAX_NON_FAULT_SEQ(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_DEV10G_MAC_LFS_CFG_LFS_MAX_NON_FAULT_SEQ     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_DEV10G_MAC_LFS_CFG_LFS_MAX_NON_FAULT_SEQ(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/** 
 * \brief
 * Compare IEEE802.3 figure 46-11 Link Fault Signaling State Diagram.
 * Configures the number of columns received containing a fault_sequence
 * required to get into FAULT state. Should be set to 3 for standard
 * operation mode. Might be reduced in USXGMII mode for network port speeds
 * that require a replication since the replicator will remove some of the
 * fault_sequence samples.
 *
 * \details 
 * Number of fault ordered sets required to get to FAULT state.
 *
 * Field: ::VTSS_DEV10G_MAC_LFS_CFG . LFS_MAX_FAULT_SEQ
 */
#define  VTSS_F_DEV10G_MAC_LFS_CFG_LFS_MAX_FAULT_SEQ(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_DEV10G_MAC_LFS_CFG_LFS_MAX_FAULT_SEQ     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_DEV10G_MAC_LFS_CFG_LFS_MAX_FAULT_SEQ(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/** 
 * \brief
 * LFS Unidirectional mode enable. Implementation of 802.3 clause 66. When
 * asserted, this enables MAC to transmit data during reception of Local
 * Fault and Remote Fault ordered sets from the PHY. When in Unidirectional
 * mode:When receiving LF, frames are transmitted separated by RF ordered
 * sets.When receiving RF, frames are transmitted separated by IDLE symbols
 *
 * \details 
 * '0' : LFS unidirectional mode is disabled
 * '1' : LFS unidirectional mode is enabled
 *
 * Field: ::VTSS_DEV10G_MAC_LFS_CFG . LFS_UNIDIR_ENA
 */
#define  VTSS_F_DEV10G_MAC_LFS_CFG_LFS_UNIDIR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV10G_MAC_LFS_CFG_LFS_UNIDIR_ENA  VTSS_BIT(3)
#define  VTSS_X_DEV10G_MAC_LFS_CFG_LFS_UNIDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * GNATS #6146. Use the leading edge of the TX_ENA signal to control the
 * state machine in tx_datapath.This bit is implemented to disable the fix
 * incase it is causing problems.
 *
 * \details 
 * 0 : Leading edge detect disabled
 * 1 : Leading edge detect enabled
 *
 * Field: ::VTSS_DEV10G_MAC_LFS_CFG . USE_LEADING_EDGE_DETECT
 */
#define  VTSS_F_DEV10G_MAC_LFS_CFG_USE_LEADING_EDGE_DETECT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV10G_MAC_LFS_CFG_USE_LEADING_EDGE_DETECT  VTSS_BIT(2)
#define  VTSS_X_DEV10G_MAC_LFS_CFG_USE_LEADING_EDGE_DETECT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * During normal 802.3 compliant operation, it is possible to send spurious
 * ||Q|| after the lfs condition was deasserted.Asserting this bit will
 * prevent these spurious ||Q|| by delaying TX until the PCS reports that
 * no ||Q|| are pending.Applicable for XAUI speeds only.
 *
 * \details 
 * 0 - Allow ||Q|| transmission (ieee 802.3 compliant)
 * 1 - Suppress ||Q|| transmission
 *
 * Field: ::VTSS_DEV10G_MAC_LFS_CFG . SPURIOUS_Q_DIS
 */
#define  VTSS_F_DEV10G_MAC_LFS_CFG_SPURIOUS_Q_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV10G_MAC_LFS_CFG_SPURIOUS_Q_DIS  VTSS_BIT(1)
#define  VTSS_X_DEV10G_MAC_LFS_CFG_SPURIOUS_Q_DIS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Link Fault Signaling Mode Enable: If enabled, the transmitter reacts on
 * received Link Fault indications.
 *
 * \details 
 * 
 * '0': Ignore Link Faults detected by the MAC receiver module
 * '1': React on detected Link Faults and transmit the appropriate Sequence
 * Ordered Set.
 *
 * Field: ::VTSS_DEV10G_MAC_LFS_CFG . LFS_MODE_ENA
 */
#define  VTSS_F_DEV10G_MAC_LFS_CFG_LFS_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_MAC_LFS_CFG_LFS_MODE_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV10G_MAC_LFS_CFG_LFS_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Miscellaneous Configuration Register
 *
 * \details
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_LB_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MAC_LB_CFG(target)       VTSS_IOREG(target,0x9)

/** 
 * \brief
 * Enables loopback from egress to ingress in the device. The MAC Rx clock
 * is automatically set equal to the MAC Tx clock when the loop back is
 * enabled.
 *
 * \details 
 * '0': Host loopback disabled at XGMII interface.
 * '1': Host loopback enabled at XGMII interface.
 *
 * Field: ::VTSS_DEV10G_MAC_LB_CFG . XGMII_HOST_LB_ENA
 */
#define  VTSS_F_DEV10G_MAC_LB_CFG_XGMII_HOST_LB_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_MAC_LB_CFG_XGMII_HOST_LB_ENA  VTSS_BIT(4)
#define  VTSS_X_DEV10G_MAC_LB_CFG_XGMII_HOST_LB_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enables loopback from ingress to egress data path at XGMII interface.
 *
 * \details 
 * '0': PHY Loopback Disabled at XGMII interface.
 * '1': PHY Loopback Enabled at XGMII interface.
 *
 * Field: ::VTSS_DEV10G_MAC_LB_CFG . XGMII_PHY_LB_ENA
 */
#define  VTSS_F_DEV10G_MAC_LB_CFG_XGMII_PHY_LB_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_MAC_LB_CFG_XGMII_PHY_LB_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV10G_MAC_LB_CFG_XGMII_PHY_LB_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief XGMII Lane Debug Sticky bit Register 0
 *
 * \details
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_RX_LANE_STICKY_0
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MAC_RX_LANE_STICKY_0(target)  VTSS_IOREG(target,0xa)

/** 
 * \brief
 * Sticky bits for debugging Lane 3.
 *
 * \details 
 * See format of LANE0 sticky bit register.
 *
 * Field: ::VTSS_DEV10G_MAC_RX_LANE_STICKY_0 . LANE3_STICKY
 */
#define  VTSS_F_DEV10G_MAC_RX_LANE_STICKY_0_LANE3_STICKY(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_DEV10G_MAC_RX_LANE_STICKY_0_LANE3_STICKY     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_DEV10G_MAC_RX_LANE_STICKY_0_LANE3_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/** 
 * \brief
 * Sticky bits for debugging Lane 2.
 *
 * \details 
 * See format of LANE0 sticky bit register.
 *
 * Field: ::VTSS_DEV10G_MAC_RX_LANE_STICKY_0 . LANE2_STICKY
 */
#define  VTSS_F_DEV10G_MAC_RX_LANE_STICKY_0_LANE2_STICKY(x)  VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_DEV10G_MAC_RX_LANE_STICKY_0_LANE2_STICKY     VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_DEV10G_MAC_RX_LANE_STICKY_0_LANE2_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,7)

/** 
 * \brief
 * Sticky bits for debugging Lane 1.
 *
 * \details 
 * See format of LANE0 sticky bit register.
 *
 * Field: ::VTSS_DEV10G_MAC_RX_LANE_STICKY_0 . LANE1_STICKY
 */
#define  VTSS_F_DEV10G_MAC_RX_LANE_STICKY_0_LANE1_STICKY(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_DEV10G_MAC_RX_LANE_STICKY_0_LANE1_STICKY     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_DEV10G_MAC_RX_LANE_STICKY_0_LANE1_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/** 
 * \brief
 * Sticky bits for debugging Lane 0.
 *
 * \details 
 * Bit 0: Sticky bit indicating that a Data character has been received on
 * Lane 0. Writing a '1' clears the sticky bit.
 * 
 * Bit 1: Sticky bit indicating that a Control character has been received
 * on Lane 0. Writing a '1' clears the sticky bit.
 * 
 * Bit 2: Sticky bit indicating that an Idle character has been received on
 * Lane 0. Writing a '1' clears the sticky bit.
 * 
 * Bit 3: Sticky bit indicating that a Sequence character (0x9C) has been
 * received on Lane 0. Writing a '1' clears the sticky bit.
 * 
 * Bit 4: Sticky bit indicating that a SOP character has been received on
 * Lane 0. Writing a '1' clears the sticky bit.
 * 
 * Bit 5: Sticky bit indicating that an EOP character has been received on
 * Lane 0. Writing a '1' clears the sticky bit.
 * 
 * Bit 6: Sticky bit indicating that an Error character has been received
 * on Lane 0. Writing a '1' clears the sticky bit.
 *
 * Field: ::VTSS_DEV10G_MAC_RX_LANE_STICKY_0 . LANE0_STICKY
 */
#define  VTSS_F_DEV10G_MAC_RX_LANE_STICKY_0_LANE0_STICKY(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_DEV10G_MAC_RX_LANE_STICKY_0_LANE0_STICKY     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_DEV10G_MAC_RX_LANE_STICKY_0_LANE0_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief XGMII Lane Debug Sticky bit Register 1
 *
 * \details
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_RX_LANE_STICKY_1
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MAC_RX_LANE_STICKY_1(target)  VTSS_IOREG(target,0xb)

/** 
 * \brief
 * Sticky bits for debugging Lane 7.
 *
 * \details 
 * See format of LANE0 sticky bit register.
 *
 * Field: ::VTSS_DEV10G_MAC_RX_LANE_STICKY_1 . LANE7_STICKY
 */
#define  VTSS_F_DEV10G_MAC_RX_LANE_STICKY_1_LANE7_STICKY(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_DEV10G_MAC_RX_LANE_STICKY_1_LANE7_STICKY     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_DEV10G_MAC_RX_LANE_STICKY_1_LANE7_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/** 
 * \brief
 * Sticky bits for debugging Lane 6.
 *
 * \details 
 * See format of LANE0 sticky bit register.
 *
 * Field: ::VTSS_DEV10G_MAC_RX_LANE_STICKY_1 . LANE6_STICKY
 */
#define  VTSS_F_DEV10G_MAC_RX_LANE_STICKY_1_LANE6_STICKY(x)  VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_DEV10G_MAC_RX_LANE_STICKY_1_LANE6_STICKY     VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_DEV10G_MAC_RX_LANE_STICKY_1_LANE6_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,7)

/** 
 * \brief
 * Sticky bits for debugging Lane 5.
 *
 * \details 
 * See format of LANE0 sticky bit register.
 *
 * Field: ::VTSS_DEV10G_MAC_RX_LANE_STICKY_1 . LANE5_STICKY
 */
#define  VTSS_F_DEV10G_MAC_RX_LANE_STICKY_1_LANE5_STICKY(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_DEV10G_MAC_RX_LANE_STICKY_1_LANE5_STICKY     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_DEV10G_MAC_RX_LANE_STICKY_1_LANE5_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/** 
 * \brief
 * Sticky bits for debugging Lane 4.
 *
 * \details 
 * See format of LANE0 sticky bit register.
 *
 * Field: ::VTSS_DEV10G_MAC_RX_LANE_STICKY_1 . LANE4_STICKY
 */
#define  VTSS_F_DEV10G_MAC_RX_LANE_STICKY_1_LANE4_STICKY(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_DEV10G_MAC_RX_LANE_STICKY_1_LANE4_STICKY     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_DEV10G_MAC_RX_LANE_STICKY_1_LANE4_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief MAC10G Tx Monitor Sticky bit Register
 *
 * \details
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_TX_MONITOR_STICKY
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MAC_TX_MONITOR_STICKY(target)  VTSS_IOREG(target,0xc)

/** 
 * \brief
 * LFS: LOCAL FAULT state reached in Tx module of 10G MAC. Writing a '1'
 * clears the sticky bit.
 *
 * \details 
 * '0': The LOCAL_FAULT state has never been reached.
 * '1': The LOCAL_FAULT state has been reached.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_TX_MONITOR_STICKY . LOCAL_ERR_STATE_STICKY
 */
#define  VTSS_F_DEV10G_MAC_TX_MONITOR_STICKY_LOCAL_ERR_STATE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_MAC_TX_MONITOR_STICKY_LOCAL_ERR_STATE_STICKY  VTSS_BIT(4)
#define  VTSS_X_DEV10G_MAC_TX_MONITOR_STICKY_LOCAL_ERR_STATE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * LFS REMOTE FAULT state reached in Tx module of 10G MAC. Writing a '1'
 * clears the sticky bit.
 *
 * \details 
 * '0': The REMOTE_FAULT state has never been reached.
 * '1': The REMOTE_FAULT state has been reached.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_TX_MONITOR_STICKY . REMOTE_ERR_STATE_STICKY
 */
#define  VTSS_F_DEV10G_MAC_TX_MONITOR_STICKY_REMOTE_ERR_STATE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV10G_MAC_TX_MONITOR_STICKY_REMOTE_ERR_STATE_STICKY  VTSS_BIT(3)
#define  VTSS_X_DEV10G_MAC_TX_MONITOR_STICKY_REMOTE_ERR_STATE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * LFS LINK_INTERRUPTION state reached in Tx module of 10G MAC. Writing a
 * '1' clears the sticky bit.
 *
 * \details 
 * '0': The LINK_INTERRUPTION state has never been reached.
 * '1': The LINK_INTERRUPTION state has been reached.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_TX_MONITOR_STICKY . LINK_INTERRUPTION_STATE_STICKY
 */
#define  VTSS_F_DEV10G_MAC_TX_MONITOR_STICKY_LINK_INTERRUPTION_STATE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV10G_MAC_TX_MONITOR_STICKY_LINK_INTERRUPTION_STATE_STICKY  VTSS_BIT(2)
#define  VTSS_X_DEV10G_MAC_TX_MONITOR_STICKY_LINK_INTERRUPTION_STATE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * IDLE state reached in Tx module of 10G MAC. Writing a '1' clears the
 * sticky bit.
 *
 * \details 
 * '0': The IDLE state has never been reached.
 * '1': The  IDLE state has been reached.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_TX_MONITOR_STICKY . IDLE_STATE_STICKY
 */
#define  VTSS_F_DEV10G_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV10G_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY  VTSS_BIT(1)
#define  VTSS_X_DEV10G_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * DISABLE state reached in Tx module of 10G MAC. Writing a '1' clears the
 * sticky bit.
 *
 * \details 
 * '0': The DISABLE state has never been reached.
 * '1': The DISABLE state has been reached.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_TX_MONITOR_STICKY . DIS_STATE_STICKY
 */
#define  VTSS_F_DEV10G_MAC_TX_MONITOR_STICKY_DIS_STATE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_MAC_TX_MONITOR_STICKY_DIS_STATE_STICKY  VTSS_BIT(0)
#define  VTSS_X_DEV10G_MAC_TX_MONITOR_STICKY_DIS_STATE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Sticky Bit Register
 *
 * \details
 * Clear the sticky bits by writing a '0' in the relevant bitgroups
 * (writing a '1' sets the bit)!.
 *
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_STICKY
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MAC_STICKY(target)       VTSS_IOREG(target,0xd)

/** 
 * \brief
 * Indicates that an inter packet gap shrink was detected (IPG < 12 bytes).
 *
 * \details 
 * '0': no ipg shrink was detected
 * '1': one or more ipg shrink were detected
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_STICKY . RX_IPG_SHRINK_STICKY
 */
#define  VTSS_F_DEV10G_MAC_STICKY_RX_IPG_SHRINK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_DEV10G_MAC_STICKY_RX_IPG_SHRINK_STICKY  VTSS_BIT(9)
#define  VTSS_X_DEV10G_MAC_STICKY_RX_IPG_SHRINK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Indicates that a preamble shrink was detected (preamble < 8 bytes).This
 * sticky bit can only be set when the port is setup in 10 Gbps mode, where
 * frames with e.g. a 4 bytes preamble will be discarded, and it requires
 * that PRM_SHK_CHK_DIS = 0 and SFD_CHK_ENA = 1.In SGMII mode, all preamble
 * sizes down to 3 bytes (including SFD) are accepted and will not cause
 * this sticky bit to be set.
 *
 * \details 
 * '0': no preamble shrink detected;
 * '1': one or more preamble shrinks detected;
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_STICKY . RX_PREAM_SHRINK_STICKY
 */
#define  VTSS_F_DEV10G_MAC_STICKY_RX_PREAM_SHRINK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV10G_MAC_STICKY_RX_PREAM_SHRINK_STICKY  VTSS_BIT(8)
#define  VTSS_X_DEV10G_MAC_STICKY_RX_PREAM_SHRINK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * If Preamble Check is enabled and a SOP is received, this bit is set if
 * the following bytes do not match a "5555555555..55D5" pattern.A 12 bytes
 * preamble of "55555555.55555555.555555D5" will not cause this sticky bit
 * to be set.This sticky bit can only be set when the port is setup in 10
 * Gbps mode.
 *
 * \details 
 * '0': No Preamble check has failed;
 * '1': One or more preamble checks have failed;
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_STICKY . RX_PREAM_MISMATCH_STICKY
 */
#define  VTSS_F_DEV10G_MAC_STICKY_RX_PREAM_MISMATCH_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DEV10G_MAC_STICKY_RX_PREAM_MISMATCH_STICKY  VTSS_BIT(7)
#define  VTSS_X_DEV10G_MAC_STICKY_RX_PREAM_MISMATCH_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * If a SOP is received and a following control character is received
 * within the preamble, this bit is set. (No data is passed to the host
 * interface of the MAC).
 *
 * \details 
 * '0': No Preamble error detected;
 * '1': One or more preamble errors detected;
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_STICKY . RX_PREAM_ERR_STICKY
 */
#define  VTSS_F_DEV10G_MAC_STICKY_RX_PREAM_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DEV10G_MAC_STICKY_RX_PREAM_ERR_STICKY  VTSS_BIT(6)
#define  VTSS_X_DEV10G_MAC_STICKY_RX_PREAM_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Indicates that a frame was received with a non-standard preamble.
 *
 * \details 
 * '0': No non-standard preamble detected;
 * '1': One or more frames with non-standard preamble detected;
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_STICKY . RX_NON_STD_PREAM_STICKY
 */
#define  VTSS_F_DEV10G_MAC_STICKY_RX_NON_STD_PREAM_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DEV10G_MAC_STICKY_RX_NON_STD_PREAM_STICKY  VTSS_BIT(5)
#define  VTSS_X_DEV10G_MAC_STICKY_RX_NON_STD_PREAM_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Indicates that a frame with MPLS multicast was received.
 *
 * \details 
 * '0': No frames with MPLS multicast EtherType has been detected;
 * '1': One or more frames with MPLS multicast EtherType have been
 * detected;
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_STICKY . RX_MPLS_MC_STICKY
 */
#define  VTSS_F_DEV10G_MAC_STICKY_RX_MPLS_MC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_MAC_STICKY_RX_MPLS_MC_STICKY  VTSS_BIT(4)
#define  VTSS_X_DEV10G_MAC_STICKY_RX_MPLS_MC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Indicates that a frame with MPLS unicast was received.
 *
 * \details 
 * '0': No frames with MPLS Unicast EtherType has been detected;
 * '1': One or more frames with MPLS Unicast EtherType have been detected;
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_STICKY . RX_MPLS_UC_STICKY
 */
#define  VTSS_F_DEV10G_MAC_STICKY_RX_MPLS_UC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV10G_MAC_STICKY_RX_MPLS_UC_STICKY  VTSS_BIT(3)
#define  VTSS_X_DEV10G_MAC_STICKY_RX_MPLS_UC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Indicates that a frame was received with a VLAN tag.
 *
 * \details 
 * '0': No Tagged frames have been detected;
 * '1': One or more Tagged frames have been detected;
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_STICKY . RX_TAG_STICKY
 */
#define  VTSS_F_DEV10G_MAC_STICKY_RX_TAG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV10G_MAC_STICKY_RX_TAG_STICKY  VTSS_BIT(2)
#define  VTSS_X_DEV10G_MAC_STICKY_RX_TAG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Sticky bit indicating that the MAC Transmit FIFO has dropped one or more
 * frames because of underrun.
 *
 * \details 
 * '0': No MAC Tx FIFO underrun has occurred
 * '1': One or more MAC Tx FIFO underruns have occurred
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_STICKY . TX_UFLW_STICKY
 */
#define  VTSS_F_DEV10G_MAC_STICKY_TX_UFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV10G_MAC_STICKY_TX_UFLW_STICKY  VTSS_BIT(1)
#define  VTSS_X_DEV10G_MAC_STICKY_TX_UFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Indicates that the transmit host initiated abort was executed.
 *
 * \details 
 * '0': no tx frame was aborted
 * '1': one or more tx frames were aborted
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_STICKY . TX_ABORT_STICKY
 */
#define  VTSS_F_DEV10G_MAC_STICKY_TX_ABORT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_MAC_STICKY_TX_ABORT_STICKY  VTSS_BIT(0)
#define  VTSS_X_DEV10G_MAC_STICKY_TX_ABORT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Sticky Bit Register
 *
 * \details
 * Clear the sticky bits by writing a '0' in the relevant bitgroups
 * (writing a '1' sets the bit)!.
 *
 * Register: \a DEV10G:MAC_CFG_STATUS:PMAC_STICKY
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_STICKY(target)      VTSS_IOREG(target,0xe)

/** 
 * \brief
 * Indicates that a preamble shrink was detected (preamble < 8 bytes).This
 * sticky bit can only be set when the port is setup in 10 Gbps mode, where
 * frames with e.g. a 4 bytes preamble will be discarded, and it requires
 * that PRM_SHK_CHK_DIS = 0 and SFD_CHK_ENA = 1.In SGMII mode, all preamble
 * sizes down to 3 bytes (including SFD) are accepted and will not cause
 * this sticky bit to be set.
 *
 * \details 
 * '0': no preamble shrink detected;
 * '1': one or more preamble shrinks detected;
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_PMAC_STICKY . PMAC_RX_PREAM_SHRINK_STICKY
 */
#define  VTSS_F_DEV10G_PMAC_STICKY_PMAC_RX_PREAM_SHRINK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV10G_PMAC_STICKY_PMAC_RX_PREAM_SHRINK_STICKY  VTSS_BIT(8)
#define  VTSS_X_DEV10G_PMAC_STICKY_PMAC_RX_PREAM_SHRINK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * If Preamble Check is enabled and a SOP is received, this bit is set if
 * the following bytes do not match a "5555555555..55D5" pattern.A 12 bytes
 * preamble of "55555555.55555555.555555D5" will not cause this sticky bit
 * to be set.This sticky bit can only be set when the port is setup in 10
 * Gbps mode.
 *
 * \details 
 * '0': No Preamble check has failed;
 * '1': One or more preamble checks have failed;
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_PMAC_STICKY . PMAC_RX_PREAM_MISMATCH_STICKY
 */
#define  VTSS_F_DEV10G_PMAC_STICKY_PMAC_RX_PREAM_MISMATCH_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DEV10G_PMAC_STICKY_PMAC_RX_PREAM_MISMATCH_STICKY  VTSS_BIT(7)
#define  VTSS_X_DEV10G_PMAC_STICKY_PMAC_RX_PREAM_MISMATCH_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * If a SOP is received and a following control character is received
 * within the preamble, this bit is set. (No data is passed to the host
 * interface of the MAC).
 *
 * \details 
 * '0': No Preamble error detected;
 * '1': One or more preamble errors detected;
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_PMAC_STICKY . PMAC_RX_PREAM_ERR_STICKY
 */
#define  VTSS_F_DEV10G_PMAC_STICKY_PMAC_RX_PREAM_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DEV10G_PMAC_STICKY_PMAC_RX_PREAM_ERR_STICKY  VTSS_BIT(6)
#define  VTSS_X_DEV10G_PMAC_STICKY_PMAC_RX_PREAM_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Indicates that a frame was received with a non-standard preamble.
 *
 * \details 
 * '0': No non-standard preamble detected;
 * '1': One or more frames with non-standard preamble detected;
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_PMAC_STICKY . PMAC_RX_NON_STD_PREAM_STICKY
 */
#define  VTSS_F_DEV10G_PMAC_STICKY_PMAC_RX_NON_STD_PREAM_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DEV10G_PMAC_STICKY_PMAC_RX_NON_STD_PREAM_STICKY  VTSS_BIT(5)
#define  VTSS_X_DEV10G_PMAC_STICKY_PMAC_RX_NON_STD_PREAM_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Indicates that a frame with MPLS multicast was received.
 *
 * \details 
 * '0': No frames with MPLS multicast EtherType has been detected;
 * '1': One or more frames with MPLS multicast EtherType have been
 * detected;
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_PMAC_STICKY . PMAC_RX_MPLS_MC_STICKY
 */
#define  VTSS_F_DEV10G_PMAC_STICKY_PMAC_RX_MPLS_MC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_PMAC_STICKY_PMAC_RX_MPLS_MC_STICKY  VTSS_BIT(4)
#define  VTSS_X_DEV10G_PMAC_STICKY_PMAC_RX_MPLS_MC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Indicates that a frame with MPLS unicast was received.
 *
 * \details 
 * '0': No frames with MPLS Unicast EtherType has been detected;
 * '1': One or more frames with MPLS Unicast EtherType have been detected;
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_PMAC_STICKY . PMAC_RX_MPLS_UC_STICKY
 */
#define  VTSS_F_DEV10G_PMAC_STICKY_PMAC_RX_MPLS_UC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV10G_PMAC_STICKY_PMAC_RX_MPLS_UC_STICKY  VTSS_BIT(3)
#define  VTSS_X_DEV10G_PMAC_STICKY_PMAC_RX_MPLS_UC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Sticky bit indicating that the MAC Transmit FIFO has dropped one or more
 * frames because of underrun.
 *
 * \details 
 * '0': No MAC Tx FIFO underrun has occurred
 * '1': One or more MAC Tx FIFO underruns have occurred
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_PMAC_STICKY . PMAC_TX_UFLW_STICKY
 */
#define  VTSS_F_DEV10G_PMAC_STICKY_PMAC_TX_UFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV10G_PMAC_STICKY_PMAC_TX_UFLW_STICKY  VTSS_BIT(1)
#define  VTSS_X_DEV10G_PMAC_STICKY_PMAC_TX_UFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Indicates that the transmit host initiated abort was executed.
 *
 * \details 
 * '0': no tx frame was aborted
 * '1': one or more tx frames were aborted
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_PMAC_STICKY . PMAC_TX_ABORT_STICKY
 */
#define  VTSS_F_DEV10G_PMAC_STICKY_PMAC_TX_ABORT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_PMAC_STICKY_PMAC_TX_ABORT_STICKY  VTSS_BIT(0)
#define  VTSS_X_DEV10G_PMAC_STICKY_PMAC_TX_ABORT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a DEV10G:DEV_STATISTICS_32BIT
 *
 * Device Statistics Registers
 */


/** 
 * \brief Rx Symbol Carrier Error Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_SYMBOL_ERR_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_SYMBOL_ERR_CNT(target)  VTSS_IOREG(target,0xf)

/** 
 * \brief
 * The number of frames received with one or more symbol errors.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_SYMBOL_ERR_CNT . RX_SYMBOL_ERR_CNT
 */
#define  VTSS_F_DEV10G_RX_SYMBOL_ERR_CNT_RX_SYMBOL_ERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_SYMBOL_ERR_CNT_RX_SYMBOL_ERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_SYMBOL_ERR_CNT_RX_SYMBOL_ERR_CNT(x)  (x)


/** 
 * \brief Rx Pause Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_PAUSE_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_PAUSE_CNT(target)     VTSS_IOREG(target,0x10)

/** 
 * \brief
 * Number of pause control frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_PAUSE_CNT . RX_PAUSE_CNT
 */
#define  VTSS_F_DEV10G_RX_PAUSE_CNT_RX_PAUSE_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_PAUSE_CNT_RX_PAUSE_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_PAUSE_CNT_RX_PAUSE_CNT(x)  (x)


/** 
 * \brief Rx Control Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_UNSUP_OPCODE_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_UNSUP_OPCODE_CNT(target)  VTSS_IOREG(target,0x11)

/** 
 * \brief
 * Number of control frames with unsupported opcode received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_UNSUP_OPCODE_CNT . RX_UNSUP_OPCODE_CNT
 */
#define  VTSS_F_DEV10G_RX_UNSUP_OPCODE_CNT_RX_UNSUP_OPCODE_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_UNSUP_OPCODE_CNT_RX_UNSUP_OPCODE_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_UNSUP_OPCODE_CNT_RX_UNSUP_OPCODE_CNT(x)  (x)


/** 
 * \brief Rx Unicast Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_UC_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_UC_CNT(target)        VTSS_IOREG(target,0x12)

/** 
 * \brief
 * The number of good unicast frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_UC_CNT . RX_UC_CNT
 */
#define  VTSS_F_DEV10G_RX_UC_CNT_RX_UC_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_UC_CNT_RX_UC_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_UC_CNT_RX_UC_CNT(x)  (x)


/** 
 * \brief Rx Multicast Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_MC_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_MC_CNT(target)        VTSS_IOREG(target,0x13)

/** 
 * \brief
 * The number of good multicast frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_MC_CNT . RX_MC_CNT
 */
#define  VTSS_F_DEV10G_RX_MC_CNT_RX_MC_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_MC_CNT_RX_MC_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_MC_CNT_RX_MC_CNT(x)  (x)


/** 
 * \brief Rx Broadcast Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_BC_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_BC_CNT(target)        VTSS_IOREG(target,0x14)

/** 
 * \brief
 * The number of good broadcast frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_BC_CNT . RX_BC_CNT
 */
#define  VTSS_F_DEV10G_RX_BC_CNT_RX_BC_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_BC_CNT_RX_BC_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_BC_CNT_RX_BC_CNT(x)  (x)


/** 
 * \brief Rx CRC Error Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_CRC_ERR_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_CRC_ERR_CNT(target)   VTSS_IOREG(target,0x15)

/** 
 * \brief
 * The number of frames received with CRC error only.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_CRC_ERR_CNT . RX_CRC_ERR_CNT
 */
#define  VTSS_F_DEV10G_RX_CRC_ERR_CNT_RX_CRC_ERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_CRC_ERR_CNT_RX_CRC_ERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_CRC_ERR_CNT_RX_CRC_ERR_CNT(x)  (x)


/** 
 * \brief Rx Undersize Counter (valid frame format)
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_UNDERSIZE_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_UNDERSIZE_CNT(target)  VTSS_IOREG(target,0x16)

/** 
 * \brief
 * The number of undersize well-formed frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_UNDERSIZE_CNT . RX_UNDERSIZE_CNT
 */
#define  VTSS_F_DEV10G_RX_UNDERSIZE_CNT_RX_UNDERSIZE_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_UNDERSIZE_CNT_RX_UNDERSIZE_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_UNDERSIZE_CNT_RX_UNDERSIZE_CNT(x)  (x)


/** 
 * \brief Rx Undersize Counter (CRC error)
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_FRAGMENTS_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_FRAGMENTS_CNT(target)  VTSS_IOREG(target,0x17)

/** 
 * \brief
 * The number of undersize frames with CRC error received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_FRAGMENTS_CNT . RX_FRAGMENTS_CNT
 */
#define  VTSS_F_DEV10G_RX_FRAGMENTS_CNT_RX_FRAGMENTS_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_FRAGMENTS_CNT_RX_FRAGMENTS_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_FRAGMENTS_CNT_RX_FRAGMENTS_CNT(x)  (x)


/** 
 * \brief Rx In-range Length Error Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_IN_RANGE_LEN_ERR_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_IN_RANGE_LEN_ERR_CNT(target)  VTSS_IOREG(target,0x18)

/** 
 * \brief
 * The number of frames with legal length field that does not match length
 * of MAC client data.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_IN_RANGE_LEN_ERR_CNT . RX_IN_RANGE_LEN_ERR_CNT
 */
#define  VTSS_F_DEV10G_RX_IN_RANGE_LEN_ERR_CNT_RX_IN_RANGE_LEN_ERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_IN_RANGE_LEN_ERR_CNT_RX_IN_RANGE_LEN_ERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_IN_RANGE_LEN_ERR_CNT_RX_IN_RANGE_LEN_ERR_CNT(x)  (x)


/** 
 * \brief Rx Out-Of-Range Length Error Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_OUT_OF_RANGE_LEN_ERR_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_OUT_OF_RANGE_LEN_ERR_CNT(target)  VTSS_IOREG(target,0x19)

/** 
 * \brief
 * The number of frames with illegal length field (frames using type field
 * are not counted here).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_OUT_OF_RANGE_LEN_ERR_CNT . RX_OUT_OF_RANGE_LEN_ERR_CNT
 */
#define  VTSS_F_DEV10G_RX_OUT_OF_RANGE_LEN_ERR_CNT_RX_OUT_OF_RANGE_LEN_ERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_OUT_OF_RANGE_LEN_ERR_CNT_RX_OUT_OF_RANGE_LEN_ERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_OUT_OF_RANGE_LEN_ERR_CNT_RX_OUT_OF_RANGE_LEN_ERR_CNT(x)  (x)


/** 
 * \brief Rx Oversize Counter (valid frame format)
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_OVERSIZE_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_OVERSIZE_CNT(target)  VTSS_IOREG(target,0x1a)

/** 
 * \brief
 * The number of oversize well-formed frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_OVERSIZE_CNT . RX_OVERSIZE_CNT
 */
#define  VTSS_F_DEV10G_RX_OVERSIZE_CNT_RX_OVERSIZE_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_OVERSIZE_CNT_RX_OVERSIZE_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_OVERSIZE_CNT_RX_OVERSIZE_CNT(x)  (x)


/** 
 * \brief Rx Jabbers Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_JABBERS_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_JABBERS_CNT(target)   VTSS_IOREG(target,0x1b)

/** 
 * \brief
 * The number of oversize frames with CRC error received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_JABBERS_CNT . RX_JABBERS_CNT
 */
#define  VTSS_F_DEV10G_RX_JABBERS_CNT_RX_JABBERS_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_JABBERS_CNT_RX_JABBERS_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_JABBERS_CNT_RX_JABBERS_CNT(x)  (x)


/** 
 * \brief Rx 64 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_SIZE64_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_SIZE64_CNT(target)    VTSS_IOREG(target,0x1c)

/** 
 * \brief
 * The number of 64 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_SIZE64_CNT . RX_SIZE64_CNT
 */
#define  VTSS_F_DEV10G_RX_SIZE64_CNT_RX_SIZE64_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_SIZE64_CNT_RX_SIZE64_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_SIZE64_CNT_RX_SIZE64_CNT(x)  (x)


/** 
 * \brief Rx 65-127 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_SIZE65TO127_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_SIZE65TO127_CNT(target)  VTSS_IOREG(target,0x1d)

/** 
 * \brief
 * The number of 65 to 127 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_SIZE65TO127_CNT . RX_SIZE65TO127_CNT
 */
#define  VTSS_F_DEV10G_RX_SIZE65TO127_CNT_RX_SIZE65TO127_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_SIZE65TO127_CNT_RX_SIZE65TO127_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_SIZE65TO127_CNT_RX_SIZE65TO127_CNT(x)  (x)


/** 
 * \brief Rx 128-255 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_SIZE128TO255_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_SIZE128TO255_CNT(target)  VTSS_IOREG(target,0x1e)

/** 
 * \brief
 * The number of 128 to 255 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_SIZE128TO255_CNT . RX_SIZE128TO255_CNT
 */
#define  VTSS_F_DEV10G_RX_SIZE128TO255_CNT_RX_SIZE128TO255_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_SIZE128TO255_CNT_RX_SIZE128TO255_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_SIZE128TO255_CNT_RX_SIZE128TO255_CNT(x)  (x)


/** 
 * \brief Rx 256-511 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_SIZE256TO511_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_SIZE256TO511_CNT(target)  VTSS_IOREG(target,0x1f)

/** 
 * \brief
 * The number of 256 to 511 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_SIZE256TO511_CNT . RX_SIZE256TO511_CNT
 */
#define  VTSS_F_DEV10G_RX_SIZE256TO511_CNT_RX_SIZE256TO511_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_SIZE256TO511_CNT_RX_SIZE256TO511_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_SIZE256TO511_CNT_RX_SIZE256TO511_CNT(x)  (x)


/** 
 * \brief Rx 512-1023 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_SIZE512TO1023_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_SIZE512TO1023_CNT(target)  VTSS_IOREG(target,0x20)

/** 
 * \brief
 * The number of 512 to 1023 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_SIZE512TO1023_CNT . RX_SIZE512TO1023_CNT
 */
#define  VTSS_F_DEV10G_RX_SIZE512TO1023_CNT_RX_SIZE512TO1023_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_SIZE512TO1023_CNT_RX_SIZE512TO1023_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_SIZE512TO1023_CNT_RX_SIZE512TO1023_CNT(x)  (x)


/** 
 * \brief Rx 1024-1518 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_SIZE1024TO1518_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_SIZE1024TO1518_CNT(target)  VTSS_IOREG(target,0x21)

/** 
 * \brief
 * The number of 1024 to 1518 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_SIZE1024TO1518_CNT . RX_SIZE1024TO1518_CNT
 */
#define  VTSS_F_DEV10G_RX_SIZE1024TO1518_CNT_RX_SIZE1024TO1518_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_SIZE1024TO1518_CNT_RX_SIZE1024TO1518_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_SIZE1024TO1518_CNT_RX_SIZE1024TO1518_CNT(x)  (x)


/** 
 * \brief Rx 1519 To Max. Length Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_SIZE1519TOMAX_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_SIZE1519TOMAX_CNT(target)  VTSS_IOREG(target,0x22)

/** 
 * \brief
 * The number of frames received longer than 1518 bytes and not longer than
 * Maximum Length Register (Maximum Length Register + 4 if the frame is
 * VLAN tagged).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_SIZE1519TOMAX_CNT . RX_SIZE1519TOMAX_CNT
 */
#define  VTSS_F_DEV10G_RX_SIZE1519TOMAX_CNT_RX_SIZE1519TOMAX_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_SIZE1519TOMAX_CNT_RX_SIZE1519TOMAX_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_SIZE1519TOMAX_CNT_RX_SIZE1519TOMAX_CNT(x)  (x)


/** 
 * \brief Rx Inter Packet Gap Shrink Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_IPG_SHRINK_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_IPG_SHRINK_CNT(target)  VTSS_IOREG(target,0x23)

/** 
 * \brief
 * Number of inter packet gap shrinks detected (IPG < 12 bytes).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_IPG_SHRINK_CNT . RX_IPG_SHRINK_CNT
 */
#define  VTSS_F_DEV10G_RX_IPG_SHRINK_CNT_RX_IPG_SHRINK_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_IPG_SHRINK_CNT_RX_IPG_SHRINK_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_IPG_SHRINK_CNT_RX_IPG_SHRINK_CNT(x)  (x)


/** 
 * \brief Tx Pause Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_PAUSE_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_TX_PAUSE_CNT(target)     VTSS_IOREG(target,0x24)

/** 
 * \brief
 * The number of pause control frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_TX_PAUSE_CNT . TX_PAUSE_CNT
 */
#define  VTSS_F_DEV10G_TX_PAUSE_CNT_TX_PAUSE_CNT(x)  (x)
#define  VTSS_M_DEV10G_TX_PAUSE_CNT_TX_PAUSE_CNT     0xffffffff
#define  VTSS_X_DEV10G_TX_PAUSE_CNT_TX_PAUSE_CNT(x)  (x)


/** 
 * \brief Tx Unicast Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_UC_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_TX_UC_CNT(target)        VTSS_IOREG(target,0x25)

/** 
 * \brief
 * The number of unicast frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_TX_UC_CNT . TX_UC_CNT
 */
#define  VTSS_F_DEV10G_TX_UC_CNT_TX_UC_CNT(x)  (x)
#define  VTSS_M_DEV10G_TX_UC_CNT_TX_UC_CNT     0xffffffff
#define  VTSS_X_DEV10G_TX_UC_CNT_TX_UC_CNT(x)  (x)


/** 
 * \brief Tx Multicast Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_MC_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_TX_MC_CNT(target)        VTSS_IOREG(target,0x26)

/** 
 * \brief
 * The number of multicast frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_TX_MC_CNT . TX_MC_CNT
 */
#define  VTSS_F_DEV10G_TX_MC_CNT_TX_MC_CNT(x)  (x)
#define  VTSS_M_DEV10G_TX_MC_CNT_TX_MC_CNT     0xffffffff
#define  VTSS_X_DEV10G_TX_MC_CNT_TX_MC_CNT(x)  (x)


/** 
 * \brief Tx Broadcast Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_BC_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_TX_BC_CNT(target)        VTSS_IOREG(target,0x27)

/** 
 * \brief
 * The number of broadcast frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_TX_BC_CNT . TX_BC_CNT
 */
#define  VTSS_F_DEV10G_TX_BC_CNT_TX_BC_CNT(x)  (x)
#define  VTSS_M_DEV10G_TX_BC_CNT_TX_BC_CNT     0xffffffff
#define  VTSS_X_DEV10G_TX_BC_CNT_TX_BC_CNT(x)  (x)


/** 
 * \brief Tx 64 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_SIZE64_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_TX_SIZE64_CNT(target)    VTSS_IOREG(target,0x28)

/** 
 * \brief
 * The number of 64 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_TX_SIZE64_CNT . TX_SIZE64_CNT
 */
#define  VTSS_F_DEV10G_TX_SIZE64_CNT_TX_SIZE64_CNT(x)  (x)
#define  VTSS_M_DEV10G_TX_SIZE64_CNT_TX_SIZE64_CNT     0xffffffff
#define  VTSS_X_DEV10G_TX_SIZE64_CNT_TX_SIZE64_CNT(x)  (x)


/** 
 * \brief Tx 65-127 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_SIZE65TO127_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_TX_SIZE65TO127_CNT(target)  VTSS_IOREG(target,0x29)

/** 
 * \brief
 * The number of 65 to 127 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_TX_SIZE65TO127_CNT . TX_SIZE65TO127_CNT
 */
#define  VTSS_F_DEV10G_TX_SIZE65TO127_CNT_TX_SIZE65TO127_CNT(x)  (x)
#define  VTSS_M_DEV10G_TX_SIZE65TO127_CNT_TX_SIZE65TO127_CNT     0xffffffff
#define  VTSS_X_DEV10G_TX_SIZE65TO127_CNT_TX_SIZE65TO127_CNT(x)  (x)


/** 
 * \brief Tx 128-255 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_SIZE128TO255_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_TX_SIZE128TO255_CNT(target)  VTSS_IOREG(target,0x2a)

/** 
 * \brief
 * The number of 128 to 255 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_TX_SIZE128TO255_CNT . TX_SIZE128TO255_CNT
 */
#define  VTSS_F_DEV10G_TX_SIZE128TO255_CNT_TX_SIZE128TO255_CNT(x)  (x)
#define  VTSS_M_DEV10G_TX_SIZE128TO255_CNT_TX_SIZE128TO255_CNT     0xffffffff
#define  VTSS_X_DEV10G_TX_SIZE128TO255_CNT_TX_SIZE128TO255_CNT(x)  (x)


/** 
 * \brief Tx 256-511 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_SIZE256TO511_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_TX_SIZE256TO511_CNT(target)  VTSS_IOREG(target,0x2b)

/** 
 * \brief
 * The number of 256 to 511 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_TX_SIZE256TO511_CNT . TX_SIZE256TO511_CNT
 */
#define  VTSS_F_DEV10G_TX_SIZE256TO511_CNT_TX_SIZE256TO511_CNT(x)  (x)
#define  VTSS_M_DEV10G_TX_SIZE256TO511_CNT_TX_SIZE256TO511_CNT     0xffffffff
#define  VTSS_X_DEV10G_TX_SIZE256TO511_CNT_TX_SIZE256TO511_CNT(x)  (x)


/** 
 * \brief Tx 512-1023 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_SIZE512TO1023_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_TX_SIZE512TO1023_CNT(target)  VTSS_IOREG(target,0x2c)

/** 
 * \brief
 * The number of 512 to 1023 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_TX_SIZE512TO1023_CNT . TX_SIZE512TO1023_CNT
 */
#define  VTSS_F_DEV10G_TX_SIZE512TO1023_CNT_TX_SIZE512TO1023_CNT(x)  (x)
#define  VTSS_M_DEV10G_TX_SIZE512TO1023_CNT_TX_SIZE512TO1023_CNT     0xffffffff
#define  VTSS_X_DEV10G_TX_SIZE512TO1023_CNT_TX_SIZE512TO1023_CNT(x)  (x)


/** 
 * \brief Tx 1024-1518 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_SIZE1024TO1518_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_TX_SIZE1024TO1518_CNT(target)  VTSS_IOREG(target,0x2d)

/** 
 * \brief
 * The number of 1024 to 1518 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_TX_SIZE1024TO1518_CNT . TX_SIZE1024TO1518_CNT
 */
#define  VTSS_F_DEV10G_TX_SIZE1024TO1518_CNT_TX_SIZE1024TO1518_CNT(x)  (x)
#define  VTSS_M_DEV10G_TX_SIZE1024TO1518_CNT_TX_SIZE1024TO1518_CNT     0xffffffff
#define  VTSS_X_DEV10G_TX_SIZE1024TO1518_CNT_TX_SIZE1024TO1518_CNT(x)  (x)


/** 
 * \brief Tx 1519 To Max. Length Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_SIZE1519TOMAX_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_TX_SIZE1519TOMAX_CNT(target)  VTSS_IOREG(target,0x2e)

/** 
 * \brief
 * The number of frames transmitted longer than 1518 bytes and not longer
 * than Maximum Length Register (Maximum Length Register + 4 if the frame
 * is VLAN tagged).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_TX_SIZE1519TOMAX_CNT . TX_SIZE1519TOMAX_CNT
 */
#define  VTSS_F_DEV10G_TX_SIZE1519TOMAX_CNT_TX_SIZE1519TOMAX_CNT(x)  (x)
#define  VTSS_M_DEV10G_TX_SIZE1519TOMAX_CNT_TX_SIZE1519TOMAX_CNT     0xffffffff
#define  VTSS_X_DEV10G_TX_SIZE1519TOMAX_CNT_TX_SIZE1519TOMAX_CNT(x)  (x)


/** 
 * \brief Counter to track the dribble-nibble (extra nibble) errors in frames.
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_ALIGNMENT_LOST_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_ALIGNMENT_LOST_CNT(target)  VTSS_IOREG(target,0x2f)

/** 
 * \brief
 * The number of frames received with Alignment (dribble-nibble) error.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_ALIGNMENT_LOST_CNT . RX_ALIGNMENT_LOST_CNT
 */
#define  VTSS_F_DEV10G_RX_ALIGNMENT_LOST_CNT_RX_ALIGNMENT_LOST_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_ALIGNMENT_LOST_CNT_RX_ALIGNMENT_LOST_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_ALIGNMENT_LOST_CNT_RX_ALIGNMENT_LOST_CNT(x)  (x)


/** 
 * \brief Counts frames that are tagged (C-Tagged or S-Tagged).
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_TAGGED_FRMS_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_TAGGED_FRMS_CNT(target)  VTSS_IOREG(target,0x30)

/** 
 * \brief
 * The number of frames received with C-Tag or S-Tag information
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_TAGGED_FRMS_CNT . RX_TAGGED_FRMS_CNT
 */
#define  VTSS_F_DEV10G_RX_TAGGED_FRMS_CNT_RX_TAGGED_FRMS_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_TAGGED_FRMS_CNT_RX_TAGGED_FRMS_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_TAGGED_FRMS_CNT_RX_TAGGED_FRMS_CNT(x)  (x)


/** 
 * \brief Counts frames that are Not tagged  (neither C-Tagged nor S-Tagged).
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_UNTAGGED_FRMS_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_UNTAGGED_FRMS_CNT(target)  VTSS_IOREG(target,0x31)

/** 
 * \brief
 * The number of frames received without C-Tag and S-Tag information.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_UNTAGGED_FRMS_CNT . RX_UNTAGGED_FRMS_CNT
 */
#define  VTSS_F_DEV10G_RX_UNTAGGED_FRMS_CNT_RX_UNTAGGED_FRMS_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_UNTAGGED_FRMS_CNT_RX_UNTAGGED_FRMS_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_UNTAGGED_FRMS_CNT_RX_UNTAGGED_FRMS_CNT(x)  (x)


/** 
 * \brief Counts frames that are tagged (C-Tagged or S-Tagged).
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_TAGGED_FRMS_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_TX_TAGGED_FRMS_CNT(target)  VTSS_IOREG(target,0x32)

/** 
 * \brief
 * The number of frames transmitted with C-Tag or S-Tag information
 *
 * \details 
 * Field: ::VTSS_DEV10G_TX_TAGGED_FRMS_CNT . TX_TAGGED_FRMS_CNT
 */
#define  VTSS_F_DEV10G_TX_TAGGED_FRMS_CNT_TX_TAGGED_FRMS_CNT(x)  (x)
#define  VTSS_M_DEV10G_TX_TAGGED_FRMS_CNT_TX_TAGGED_FRMS_CNT     0xffffffff
#define  VTSS_X_DEV10G_TX_TAGGED_FRMS_CNT_TX_TAGGED_FRMS_CNT(x)  (x)


/** 
 * \brief Counts frames that are Not tagged  (neither C-Tagged nor S-Tagged).
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_UNTAGGED_FRMS_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_TX_UNTAGGED_FRMS_CNT(target)  VTSS_IOREG(target,0x33)

/** 
 * \brief
 * The number of frames transmitted without C-Tag and S-Tag information.
 *
 * \details 
 * Field: ::VTSS_DEV10G_TX_UNTAGGED_FRMS_CNT . TX_UNTAGGED_FRMS_CNT
 */
#define  VTSS_F_DEV10G_TX_UNTAGGED_FRMS_CNT_TX_UNTAGGED_FRMS_CNT(x)  (x)
#define  VTSS_M_DEV10G_TX_UNTAGGED_FRMS_CNT_TX_UNTAGGED_FRMS_CNT     0xffffffff
#define  VTSS_X_DEV10G_TX_UNTAGGED_FRMS_CNT_TX_UNTAGGED_FRMS_CNT(x)  (x)


/** 
 * \brief Rx Symbol Carrier Error Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_SYMBOL_ERR_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_SYMBOL_ERR_CNT(target)  VTSS_IOREG(target,0x34)

/** 
 * \brief
 * PMAC - The number of frames received with one or more symbol errors.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_SYMBOL_ERR_CNT . PMAC_RX_SYMBOL_ERR_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_SYMBOL_ERR_CNT_PMAC_RX_SYMBOL_ERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_SYMBOL_ERR_CNT_PMAC_RX_SYMBOL_ERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_SYMBOL_ERR_CNT_PMAC_RX_SYMBOL_ERR_CNT(x)  (x)


/** 
 * \brief Rx Pause Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_PAUSE_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_PAUSE_CNT(target)  VTSS_IOREG(target,0x35)

/** 
 * \brief
 * PMAC - Number of pause control frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_PAUSE_CNT . PMAC_RX_PAUSE_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_PAUSE_CNT_PMAC_RX_PAUSE_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_PAUSE_CNT_PMAC_RX_PAUSE_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_PAUSE_CNT_PMAC_RX_PAUSE_CNT(x)  (x)


/** 
 * \brief Rx Control Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_UNSUP_OPCODE_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_UNSUP_OPCODE_CNT(target)  VTSS_IOREG(target,0x36)

/** 
 * \brief
 * PMAC - Number of control frames with unsupported opcode received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_UNSUP_OPCODE_CNT . PMAC_RX_UNSUP_OPCODE_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_UNSUP_OPCODE_CNT_PMAC_RX_UNSUP_OPCODE_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_UNSUP_OPCODE_CNT_PMAC_RX_UNSUP_OPCODE_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_UNSUP_OPCODE_CNT_PMAC_RX_UNSUP_OPCODE_CNT(x)  (x)


/** 
 * \brief Rx Unicast Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_UC_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_UC_CNT(target)   VTSS_IOREG(target,0x37)

/** 
 * \brief
 * PMAC - The number of good unicast frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_UC_CNT . PMAC_RX_UC_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_UC_CNT_PMAC_RX_UC_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_UC_CNT_PMAC_RX_UC_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_UC_CNT_PMAC_RX_UC_CNT(x)  (x)


/** 
 * \brief Rx Multicast Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_MC_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_MC_CNT(target)   VTSS_IOREG(target,0x38)

/** 
 * \brief
 * PMAC - The number of good multicast frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_MC_CNT . PMAC_RX_MC_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_MC_CNT_PMAC_RX_MC_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_MC_CNT_PMAC_RX_MC_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_MC_CNT_PMAC_RX_MC_CNT(x)  (x)


/** 
 * \brief Rx Broadcast Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_BC_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_BC_CNT(target)   VTSS_IOREG(target,0x39)

/** 
 * \brief
 * PMAC - The number of good broadcast frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_BC_CNT . PMAC_RX_BC_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_BC_CNT_PMAC_RX_BC_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_BC_CNT_PMAC_RX_BC_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_BC_CNT_PMAC_RX_BC_CNT(x)  (x)


/** 
 * \brief Rx CRC Error Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_CRC_ERR_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_CRC_ERR_CNT(target)  VTSS_IOREG(target,0x3a)

/** 
 * \brief
 * PMAC - The number of frames received with CRC error only.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_CRC_ERR_CNT . PMAC_RX_CRC_ERR_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_CRC_ERR_CNT_PMAC_RX_CRC_ERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_CRC_ERR_CNT_PMAC_RX_CRC_ERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_CRC_ERR_CNT_PMAC_RX_CRC_ERR_CNT(x)  (x)


/** 
 * \brief Rx Undersize Counter (valid frame format)
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_UNDERSIZE_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_UNDERSIZE_CNT(target)  VTSS_IOREG(target,0x3b)

/** 
 * \brief
 * PMAC - The number of undersize well-formed frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_UNDERSIZE_CNT . PMAC_RX_UNDERSIZE_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_UNDERSIZE_CNT_PMAC_RX_UNDERSIZE_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_UNDERSIZE_CNT_PMAC_RX_UNDERSIZE_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_UNDERSIZE_CNT_PMAC_RX_UNDERSIZE_CNT(x)  (x)


/** 
 * \brief Rx Undersize Counter (CRC error)
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_FRAGMENTS_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_FRAGMENTS_CNT(target)  VTSS_IOREG(target,0x3c)

/** 
 * \brief
 * PMAC - The number of undersize frames with CRC error received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_FRAGMENTS_CNT . PMAC_RX_FRAGMENTS_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_FRAGMENTS_CNT_PMAC_RX_FRAGMENTS_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_FRAGMENTS_CNT_PMAC_RX_FRAGMENTS_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_FRAGMENTS_CNT_PMAC_RX_FRAGMENTS_CNT(x)  (x)


/** 
 * \brief Rx In-range Length Error Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_IN_RANGE_LEN_ERR_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_IN_RANGE_LEN_ERR_CNT(target)  VTSS_IOREG(target,0x3d)

/** 
 * \brief
 * PMAC - The number of frames with legal length field that does not match
 * length of MAC client data.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_IN_RANGE_LEN_ERR_CNT . PMAC_RX_IN_RANGE_LEN_ERR_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_IN_RANGE_LEN_ERR_CNT_PMAC_RX_IN_RANGE_LEN_ERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_IN_RANGE_LEN_ERR_CNT_PMAC_RX_IN_RANGE_LEN_ERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_IN_RANGE_LEN_ERR_CNT_PMAC_RX_IN_RANGE_LEN_ERR_CNT(x)  (x)


/** 
 * \brief Rx Out-Of-Range Length Error Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT(target)  VTSS_IOREG(target,0x3e)

/** 
 * \brief
 * PMAC - The number of frames with illegal length field (frames using type
 * field are not counted here).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT . PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT(x)  (x)


/** 
 * \brief Rx Oversize Counter (valid frame format)
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_OVERSIZE_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_OVERSIZE_CNT(target)  VTSS_IOREG(target,0x3f)

/** 
 * \brief
 * PMAC - The number of oversize well-formed frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_OVERSIZE_CNT . PMAC_RX_OVERSIZE_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_OVERSIZE_CNT_PMAC_RX_OVERSIZE_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_OVERSIZE_CNT_PMAC_RX_OVERSIZE_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_OVERSIZE_CNT_PMAC_RX_OVERSIZE_CNT(x)  (x)


/** 
 * \brief Rx Jabbers Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_JABBERS_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_JABBERS_CNT(target)  VTSS_IOREG(target,0x40)

/** 
 * \brief
 * PMAC - The number of oversize frames with CRC error received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_JABBERS_CNT . PMAC_RX_JABBERS_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_JABBERS_CNT_PMAC_RX_JABBERS_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_JABBERS_CNT_PMAC_RX_JABBERS_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_JABBERS_CNT_PMAC_RX_JABBERS_CNT(x)  (x)


/** 
 * \brief Rx 64 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_SIZE64_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_SIZE64_CNT(target)  VTSS_IOREG(target,0x41)

/** 
 * \brief
 * PMAC - The number of 64 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_SIZE64_CNT . PMAC_RX_SIZE64_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_SIZE64_CNT_PMAC_RX_SIZE64_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_SIZE64_CNT_PMAC_RX_SIZE64_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_SIZE64_CNT_PMAC_RX_SIZE64_CNT(x)  (x)


/** 
 * \brief Rx 65-127 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_SIZE65TO127_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_SIZE65TO127_CNT(target)  VTSS_IOREG(target,0x42)

/** 
 * \brief
 * PMAC - The number of 65 to 127 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_SIZE65TO127_CNT . PMAC_RX_SIZE65TO127_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_SIZE65TO127_CNT_PMAC_RX_SIZE65TO127_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_SIZE65TO127_CNT_PMAC_RX_SIZE65TO127_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_SIZE65TO127_CNT_PMAC_RX_SIZE65TO127_CNT(x)  (x)


/** 
 * \brief Rx 128-255 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_SIZE128TO255_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_SIZE128TO255_CNT(target)  VTSS_IOREG(target,0x43)

/** 
 * \brief
 * PMAC - The number of 128 to 255 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_SIZE128TO255_CNT . PMAC_RX_SIZE128TO255_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_SIZE128TO255_CNT_PMAC_RX_SIZE128TO255_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_SIZE128TO255_CNT_PMAC_RX_SIZE128TO255_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_SIZE128TO255_CNT_PMAC_RX_SIZE128TO255_CNT(x)  (x)


/** 
 * \brief Rx 256-511 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_SIZE256TO511_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_SIZE256TO511_CNT(target)  VTSS_IOREG(target,0x44)

/** 
 * \brief
 * PMAC - The number of 256 to 511 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_SIZE256TO511_CNT . PMAC_RX_SIZE256TO511_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_SIZE256TO511_CNT_PMAC_RX_SIZE256TO511_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_SIZE256TO511_CNT_PMAC_RX_SIZE256TO511_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_SIZE256TO511_CNT_PMAC_RX_SIZE256TO511_CNT(x)  (x)


/** 
 * \brief Rx 512-1023 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_SIZE512TO1023_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_SIZE512TO1023_CNT(target)  VTSS_IOREG(target,0x45)

/** 
 * \brief
 * PMAC - The number of 512 to 1023 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_SIZE512TO1023_CNT . PMAC_RX_SIZE512TO1023_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_SIZE512TO1023_CNT_PMAC_RX_SIZE512TO1023_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_SIZE512TO1023_CNT_PMAC_RX_SIZE512TO1023_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_SIZE512TO1023_CNT_PMAC_RX_SIZE512TO1023_CNT(x)  (x)


/** 
 * \brief Rx 1024-1518 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_SIZE1024TO1518_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_SIZE1024TO1518_CNT(target)  VTSS_IOREG(target,0x46)

/** 
 * \brief
 * PMAC - The number of 1024 to 1518 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_SIZE1024TO1518_CNT . PMAC_RX_SIZE1024TO1518_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_SIZE1024TO1518_CNT_PMAC_RX_SIZE1024TO1518_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_SIZE1024TO1518_CNT_PMAC_RX_SIZE1024TO1518_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_SIZE1024TO1518_CNT_PMAC_RX_SIZE1024TO1518_CNT(x)  (x)


/** 
 * \brief Rx 1519 To Max. Length Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_SIZE1519TOMAX_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_SIZE1519TOMAX_CNT(target)  VTSS_IOREG(target,0x47)

/** 
 * \brief
 * PMAC - The number of frames received longer than 1518 bytes and not
 * longer than Maximum Length Register (Maximum Length Register + 4 if the
 * frame is VLAN tagged).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_SIZE1519TOMAX_CNT . PMAC_RX_SIZE1519TOMAX_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_SIZE1519TOMAX_CNT_PMAC_RX_SIZE1519TOMAX_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_SIZE1519TOMAX_CNT_PMAC_RX_SIZE1519TOMAX_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_SIZE1519TOMAX_CNT_PMAC_RX_SIZE1519TOMAX_CNT(x)  (x)


/** 
 * \brief Tx Pause Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_TX_PAUSE_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_TX_PAUSE_CNT(target)  VTSS_IOREG(target,0x48)

/** 
 * \brief
 * PMAC - The number of pause control frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_TX_PAUSE_CNT . PMAC_TX_PAUSE_CNT
 */
#define  VTSS_F_DEV10G_PMAC_TX_PAUSE_CNT_PMAC_TX_PAUSE_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_TX_PAUSE_CNT_PMAC_TX_PAUSE_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_TX_PAUSE_CNT_PMAC_TX_PAUSE_CNT(x)  (x)


/** 
 * \brief Tx Unicast Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_TX_UC_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_TX_UC_CNT(target)   VTSS_IOREG(target,0x49)

/** 
 * \brief
 * PMAC - The number of unicast frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_TX_UC_CNT . PMAC_TX_UC_CNT
 */
#define  VTSS_F_DEV10G_PMAC_TX_UC_CNT_PMAC_TX_UC_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_TX_UC_CNT_PMAC_TX_UC_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_TX_UC_CNT_PMAC_TX_UC_CNT(x)  (x)


/** 
 * \brief Tx Multicast Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_TX_MC_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_TX_MC_CNT(target)   VTSS_IOREG(target,0x4a)

/** 
 * \brief
 * PMAC - The number of multicast frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_TX_MC_CNT . PMAC_TX_MC_CNT
 */
#define  VTSS_F_DEV10G_PMAC_TX_MC_CNT_PMAC_TX_MC_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_TX_MC_CNT_PMAC_TX_MC_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_TX_MC_CNT_PMAC_TX_MC_CNT(x)  (x)


/** 
 * \brief Tx Broadcast Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_TX_BC_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_TX_BC_CNT(target)   VTSS_IOREG(target,0x4b)

/** 
 * \brief
 * PMAC - The number of broadcast frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_TX_BC_CNT . PMAC_TX_BC_CNT
 */
#define  VTSS_F_DEV10G_PMAC_TX_BC_CNT_PMAC_TX_BC_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_TX_BC_CNT_PMAC_TX_BC_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_TX_BC_CNT_PMAC_TX_BC_CNT(x)  (x)


/** 
 * \brief Tx 64 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_TX_SIZE64_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_TX_SIZE64_CNT(target)  VTSS_IOREG(target,0x4c)

/** 
 * \brief
 * PMAC - The number of 64 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_TX_SIZE64_CNT . PMAC_TX_SIZE64_CNT
 */
#define  VTSS_F_DEV10G_PMAC_TX_SIZE64_CNT_PMAC_TX_SIZE64_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_TX_SIZE64_CNT_PMAC_TX_SIZE64_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_TX_SIZE64_CNT_PMAC_TX_SIZE64_CNT(x)  (x)


/** 
 * \brief Tx 65-127 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_TX_SIZE65TO127_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_TX_SIZE65TO127_CNT(target)  VTSS_IOREG(target,0x4d)

/** 
 * \brief
 * PMAC - The number of 65 to 127 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_TX_SIZE65TO127_CNT . PMAC_TX_SIZE65TO127_CNT
 */
#define  VTSS_F_DEV10G_PMAC_TX_SIZE65TO127_CNT_PMAC_TX_SIZE65TO127_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_TX_SIZE65TO127_CNT_PMAC_TX_SIZE65TO127_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_TX_SIZE65TO127_CNT_PMAC_TX_SIZE65TO127_CNT(x)  (x)


/** 
 * \brief Tx 128-255 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_TX_SIZE128TO255_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_TX_SIZE128TO255_CNT(target)  VTSS_IOREG(target,0x4e)

/** 
 * \brief
 * PMAC - The number of 128 to 255 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_TX_SIZE128TO255_CNT . PMAC_TX_SIZE128TO255_CNT
 */
#define  VTSS_F_DEV10G_PMAC_TX_SIZE128TO255_CNT_PMAC_TX_SIZE128TO255_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_TX_SIZE128TO255_CNT_PMAC_TX_SIZE128TO255_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_TX_SIZE128TO255_CNT_PMAC_TX_SIZE128TO255_CNT(x)  (x)


/** 
 * \brief Tx 256-511 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_TX_SIZE256TO511_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_TX_SIZE256TO511_CNT(target)  VTSS_IOREG(target,0x4f)

/** 
 * \brief
 * PMAC - The number of 256 to 511 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_TX_SIZE256TO511_CNT . PMAC_TX_SIZE256TO511_CNT
 */
#define  VTSS_F_DEV10G_PMAC_TX_SIZE256TO511_CNT_PMAC_TX_SIZE256TO511_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_TX_SIZE256TO511_CNT_PMAC_TX_SIZE256TO511_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_TX_SIZE256TO511_CNT_PMAC_TX_SIZE256TO511_CNT(x)  (x)


/** 
 * \brief Tx 512-1023 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_TX_SIZE512TO1023_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_TX_SIZE512TO1023_CNT(target)  VTSS_IOREG(target,0x50)

/** 
 * \brief
 * PMAC - The number of 512 to 1023 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_TX_SIZE512TO1023_CNT . PMAC_TX_SIZE512TO1023_CNT
 */
#define  VTSS_F_DEV10G_PMAC_TX_SIZE512TO1023_CNT_PMAC_TX_SIZE512TO1023_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_TX_SIZE512TO1023_CNT_PMAC_TX_SIZE512TO1023_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_TX_SIZE512TO1023_CNT_PMAC_TX_SIZE512TO1023_CNT(x)  (x)


/** 
 * \brief Tx 1024-1518 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_TX_SIZE1024TO1518_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_TX_SIZE1024TO1518_CNT(target)  VTSS_IOREG(target,0x51)

/** 
 * \brief
 * PMAC - The number of 1024 to 1518 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_TX_SIZE1024TO1518_CNT . PMAC_TX_SIZE1024TO1518_CNT
 */
#define  VTSS_F_DEV10G_PMAC_TX_SIZE1024TO1518_CNT_PMAC_TX_SIZE1024TO1518_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_TX_SIZE1024TO1518_CNT_PMAC_TX_SIZE1024TO1518_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_TX_SIZE1024TO1518_CNT_PMAC_TX_SIZE1024TO1518_CNT(x)  (x)


/** 
 * \brief Tx 1519 To Max. Length Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_TX_SIZE1519TOMAX_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_TX_SIZE1519TOMAX_CNT(target)  VTSS_IOREG(target,0x52)

/** 
 * \brief
 * PMAC - The number of frames transmitted longer than 1518 bytes and not
 * longer than Maximum Length Register (Maximum Length Register + 4 if the
 * frame is VLAN tagged).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_TX_SIZE1519TOMAX_CNT . PMAC_TX_SIZE1519TOMAX_CNT
 */
#define  VTSS_F_DEV10G_PMAC_TX_SIZE1519TOMAX_CNT_PMAC_TX_SIZE1519TOMAX_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_TX_SIZE1519TOMAX_CNT_PMAC_TX_SIZE1519TOMAX_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_TX_SIZE1519TOMAX_CNT_PMAC_TX_SIZE1519TOMAX_CNT(x)  (x)


/** 
 * \brief Counter to track the dribble-nibble (extra nibble) errors in frames.
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_ALIGNMENT_LOST_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_ALIGNMENT_LOST_CNT(target)  VTSS_IOREG(target,0x53)

/** 
 * \brief
 * PMAC - The number of frames received with Alignment (dribble-nibble)
 * error.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_ALIGNMENT_LOST_CNT . PMAC_RX_ALIGNMENT_LOST_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_ALIGNMENT_LOST_CNT_PMAC_RX_ALIGNMENT_LOST_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_ALIGNMENT_LOST_CNT_PMAC_RX_ALIGNMENT_LOST_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_ALIGNMENT_LOST_CNT_PMAC_RX_ALIGNMENT_LOST_CNT(x)  (x)


/** 
 * \brief Counts Pframes that are with assembly error .
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:MM_RX_ASSEMBLY_ERR_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MM_RX_ASSEMBLY_ERR_CNT(target)  VTSS_IOREG(target,0x54)

/** 
 * \brief
 * MAC MERGE - The number of Pframes received with aseembly error.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_MM_RX_ASSEMBLY_ERR_CNT . MM_RX_ASSEMBLY_ERR_CNT
 */
#define  VTSS_F_DEV10G_MM_RX_ASSEMBLY_ERR_CNT_MM_RX_ASSEMBLY_ERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_MM_RX_ASSEMBLY_ERR_CNT_MM_RX_ASSEMBLY_ERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_MM_RX_ASSEMBLY_ERR_CNT_MM_RX_ASSEMBLY_ERR_CNT(x)  (x)


/** 
 * \brief Counts Pframes that are with SMD error .
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:MM_RX_SMD_ERR_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MM_RX_SMD_ERR_CNT(target)  VTSS_IOREG(target,0x55)

/** 
 * \brief
 * MAC MERGE - The number of Pframe fragaments rejected die to unknown SMD
 * values or arrving with SMD-C when no pframe in progress  .
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_MM_RX_SMD_ERR_CNT . MM_RX_SMD_ERR_CNT
 */
#define  VTSS_F_DEV10G_MM_RX_SMD_ERR_CNT_MM_RX_SMD_ERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_MM_RX_SMD_ERR_CNT_MM_RX_SMD_ERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_MM_RX_SMD_ERR_CNT_MM_RX_SMD_ERR_CNT(x)  (x)


/** 
 * \brief Counts Pframes that are successfully  re-assembled and sent to PMAC .
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:MM_RX_ASSEMBLY_OK_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MM_RX_ASSEMBLY_OK_CNT(target)  VTSS_IOREG(target,0x56)

/** 
 * \brief
 * MAC MERGE - The number of Pframes received whitch are successfully
 * reassembled .
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_MM_RX_ASSEMBLY_OK_CNT . MM_RX_ASSEMBLY_OK_CNT
 */
#define  VTSS_F_DEV10G_MM_RX_ASSEMBLY_OK_CNT_MM_RX_ASSEMBLY_OK_CNT(x)  (x)
#define  VTSS_M_DEV10G_MM_RX_ASSEMBLY_OK_CNT_MM_RX_ASSEMBLY_OK_CNT     0xffffffff
#define  VTSS_X_DEV10G_MM_RX_ASSEMBLY_OK_CNT_MM_RX_ASSEMBLY_OK_CNT(x)  (x)


/** 
 * \brief Counts Pframes which are mPackets (fragments) due to preemption.
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:MM_RX_MERGE_FRAG_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MM_RX_MERGE_FRAG_CNT(target)  VTSS_IOREG(target,0x57)

/** 
 * \brief
 * MAC MERGE - The number of Pframes received whitch are mPackets
 * (Fragments) due to preemption .
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_MM_RX_MERGE_FRAG_CNT . MM_RX_MERGE_FRAG_CNT
 */
#define  VTSS_F_DEV10G_MM_RX_MERGE_FRAG_CNT_MM_RX_MERGE_FRAG_CNT(x)  (x)
#define  VTSS_M_DEV10G_MM_RX_MERGE_FRAG_CNT_MM_RX_MERGE_FRAG_CNT     0xffffffff
#define  VTSS_X_DEV10G_MM_RX_MERGE_FRAG_CNT_MM_RX_MERGE_FRAG_CNT(x)  (x)


/** 
 * \brief Counts pframe fragment sent when preemption enabled .
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:MM_TX_PFRAGMENT_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MM_TX_PFRAGMENT_CNT(target)  VTSS_IOREG(target,0x58)

/** 
 * \brief
 * MAC MERGE - The number of Pframe fragments sent when preemption enabled
 * .
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_MM_TX_PFRAGMENT_CNT . MM_TX_PFRAGMENT_CNT
 */
#define  VTSS_F_DEV10G_MM_TX_PFRAGMENT_CNT_MM_TX_PFRAGMENT_CNT(x)  (x)
#define  VTSS_M_DEV10G_MM_TX_PFRAGMENT_CNT_MM_TX_PFRAGMENT_CNT     0xffffffff
#define  VTSS_X_DEV10G_MM_TX_PFRAGMENT_CNT_MM_TX_PFRAGMENT_CNT(x)  (x)


/** 
 * \brief Rx HiH Checksum Error Counter
 *
 * \details
 * If HIH CRC checking is enabled, this counter will count the number of
 * frames discarded due to HIH CRC errors.
 *
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_HIH_CKSM_ERR_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_HIH_CKSM_ERR_CNT(target)  VTSS_IOREG(target,0x59)

/** 
 * \brief
 * Number of frames discarded due to errors in HIH checksum.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_HIH_CKSM_ERR_CNT . RX_HIH_CKSM_ERR_CNT
 */
#define  VTSS_F_DEV10G_RX_HIH_CKSM_ERR_CNT_RX_HIH_CKSM_ERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_HIH_CKSM_ERR_CNT_RX_HIH_CKSM_ERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_HIH_CKSM_ERR_CNT_RX_HIH_CKSM_ERR_CNT(x)  (x)


/** 
 * \brief Rx XGMII Protocol Error Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_XGMII_PROT_ERR_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_XGMII_PROT_ERR_CNT(target)  VTSS_IOREG(target,0x5a)

/** 
 * \brief
 * Number of XGMII protocol errors detected.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_XGMII_PROT_ERR_CNT . RX_XGMII_PROT_ERR_CNT
 */
#define  VTSS_F_DEV10G_RX_XGMII_PROT_ERR_CNT_RX_XGMII_PROT_ERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_XGMII_PROT_ERR_CNT_RX_XGMII_PROT_ERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_XGMII_PROT_ERR_CNT_RX_XGMII_PROT_ERR_CNT(x)  (x)


/** 
 * \brief Rx HiH Checksum Error Counter
 *
 * \details
 * PMAC - If HIH CRC checking is enabled, this counter will count the
 * number of frames discarded due to HIH CRC errors.
 *
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_HIH_CKSM_ERR_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_HIH_CKSM_ERR_CNT(target)  VTSS_IOREG(target,0x5b)

/** 
 * \brief
 * PMAC - Number of frames discarded due to errors in HIH checksum.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_HIH_CKSM_ERR_CNT . PMAC_RX_HIH_CKSM_ERR_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_HIH_CKSM_ERR_CNT_PMAC_RX_HIH_CKSM_ERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_HIH_CKSM_ERR_CNT_PMAC_RX_HIH_CKSM_ERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_HIH_CKSM_ERR_CNT_PMAC_RX_HIH_CKSM_ERR_CNT(x)  (x)


/** 
 * \brief Rx XGMII Protocol Error Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:PMAC_RX_XGMII_PROT_ERR_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_XGMII_PROT_ERR_CNT(target)  VTSS_IOREG(target,0x5c)

/** 
 * \brief
 * PMAC - Number of XGMII protocol errors detected.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_XGMII_PROT_ERR_CNT . PMAC_RX_XGMII_PROT_ERR_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_XGMII_PROT_ERR_CNT_PMAC_RX_XGMII_PROT_ERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_XGMII_PROT_ERR_CNT_PMAC_RX_XGMII_PROT_ERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_XGMII_PROT_ERR_CNT_PMAC_RX_XGMII_PROT_ERR_CNT(x)  (x)

/**
 * Register Group: \a DEV10G:DEV_STATISTICS_40BIT
 *
 * Device Statistics Registers
 */


/** 
 * \brief Rx Byte Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_40BIT:RX_IN_BYTES_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_IN_BYTES_CNT(target)  VTSS_IOREG(target,0x5d)

/** 
 * \brief
 * The number of bytes received (good, bad, and framing).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_IN_BYTES_CNT . RX_IN_BYTES_CNT
 */
#define  VTSS_F_DEV10G_RX_IN_BYTES_CNT_RX_IN_BYTES_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_IN_BYTES_CNT_RX_IN_BYTES_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_IN_BYTES_CNT_RX_IN_BYTES_CNT(x)  (x)


/** 
 * \brief Rx In Bytes Counter - MSB part
 *
 * \details
 * The number of bytes received (good, bad. Framing). 
 * MSB s only)
 *
 * Register: \a DEV10G:DEV_STATISTICS_40BIT:RX_IN_BYTES_MSB_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_IN_BYTES_MSB_CNT(target)  VTSS_IOREG(target,0x5e)

/** 
 * \brief
 * The number of bytes received (good, bad, and framing) - MSBs only
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_IN_BYTES_MSB_CNT . RX_IN_BYTES_MSB_CNT
 */
#define  VTSS_F_DEV10G_RX_IN_BYTES_MSB_CNT_RX_IN_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEV10G_RX_IN_BYTES_MSB_CNT_RX_IN_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEV10G_RX_IN_BYTES_MSB_CNT_RX_IN_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Rx OK Byte Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_40BIT:RX_OK_BYTES_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_OK_BYTES_CNT(target)  VTSS_IOREG(target,0x5f)

/** 
 * \brief
 * The number of received bytes in good frames.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_OK_BYTES_CNT . RX_OK_BYTES_CNT
 */
#define  VTSS_F_DEV10G_RX_OK_BYTES_CNT_RX_OK_BYTES_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_OK_BYTES_CNT_RX_OK_BYTES_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_OK_BYTES_CNT_RX_OK_BYTES_CNT(x)  (x)


/** 
 * \brief Rx Ok Bytes Counter - MSB part
 *
 * \details
 * The number of received bytes in good frames - MSBs only
 *
 * Register: \a DEV10G:DEV_STATISTICS_40BIT:RX_OK_BYTES_MSB_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_OK_BYTES_MSB_CNT(target)  VTSS_IOREG(target,0x60)

/** 
 * \brief
 * The number of received bytes in good frames - MSBs only.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_OK_BYTES_MSB_CNT . RX_OK_BYTES_MSB_CNT
 */
#define  VTSS_F_DEV10G_RX_OK_BYTES_MSB_CNT_RX_OK_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEV10G_RX_OK_BYTES_MSB_CNT_RX_OK_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEV10G_RX_OK_BYTES_MSB_CNT_RX_OK_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Rx Bad Byte Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_40BIT:RX_BAD_BYTES_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_BAD_BYTES_CNT(target)  VTSS_IOREG(target,0x61)

/** 
 * \brief
 * The number of received bytes in bad frames.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_BAD_BYTES_CNT . RX_BAD_BYTES_CNT
 */
#define  VTSS_F_DEV10G_RX_BAD_BYTES_CNT_RX_BAD_BYTES_CNT(x)  (x)
#define  VTSS_M_DEV10G_RX_BAD_BYTES_CNT_RX_BAD_BYTES_CNT     0xffffffff
#define  VTSS_X_DEV10G_RX_BAD_BYTES_CNT_RX_BAD_BYTES_CNT(x)  (x)


/** 
 * \brief Rx Bad Bytes Counter - MSB part
 *
 * \details
 * The number of received bytes in bad frames -  MSBs only.
 *
 * Register: \a DEV10G:DEV_STATISTICS_40BIT:RX_BAD_BYTES_MSB_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_RX_BAD_BYTES_MSB_CNT(target)  VTSS_IOREG(target,0x62)

/** 
 * \brief
 * The number of received bytes in bad frames - MSBs only.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_RX_BAD_BYTES_MSB_CNT . RX_BAD_BYTES_MSB_CNT
 */
#define  VTSS_F_DEV10G_RX_BAD_BYTES_MSB_CNT_RX_BAD_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEV10G_RX_BAD_BYTES_MSB_CNT_RX_BAD_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEV10G_RX_BAD_BYTES_MSB_CNT_RX_BAD_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Tx Byte Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_40BIT:TX_OUT_BYTES_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_TX_OUT_BYTES_CNT(target)  VTSS_IOREG(target,0x63)

/** 
 * \brief
 * The number of bytes transmitted (good, bad and framing).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_TX_OUT_BYTES_CNT . TX_OUT_BYTES_CNT
 */
#define  VTSS_F_DEV10G_TX_OUT_BYTES_CNT_TX_OUT_BYTES_CNT(x)  (x)
#define  VTSS_M_DEV10G_TX_OUT_BYTES_CNT_TX_OUT_BYTES_CNT     0xffffffff
#define  VTSS_X_DEV10G_TX_OUT_BYTES_CNT_TX_OUT_BYTES_CNT(x)  (x)


/** 
 * \brief Tx Out Bytes Counter - MSB part
 *
 * \details
 * The number of bytes transmitted (good, bad, and framing) - MSBs only
 *
 * Register: \a DEV10G:DEV_STATISTICS_40BIT:TX_OUT_BYTES_MSB_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_TX_OUT_BYTES_MSB_CNT(target)  VTSS_IOREG(target,0x64)

/** 
 * \brief
 * The number of bytes transmitted (good, bad, framing) - MSBs only.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_TX_OUT_BYTES_MSB_CNT . TX_OUT_BYTES_MSB_CNT
 */
#define  VTSS_F_DEV10G_TX_OUT_BYTES_MSB_CNT_TX_OUT_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEV10G_TX_OUT_BYTES_MSB_CNT_TX_OUT_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEV10G_TX_OUT_BYTES_MSB_CNT_TX_OUT_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Tx OK Byte Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_40BIT:TX_OK_BYTES_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_TX_OK_BYTES_CNT(target)  VTSS_IOREG(target,0x65)

/** 
 * \brief
 * The number of bytes transmitted successfully.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_TX_OK_BYTES_CNT . TX_OK_BYTES_CNT
 */
#define  VTSS_F_DEV10G_TX_OK_BYTES_CNT_TX_OK_BYTES_CNT(x)  (x)
#define  VTSS_M_DEV10G_TX_OK_BYTES_CNT_TX_OK_BYTES_CNT     0xffffffff
#define  VTSS_X_DEV10G_TX_OK_BYTES_CNT_TX_OK_BYTES_CNT(x)  (x)


/** 
 * \brief Tx OK Bytes Counter - MSB part
Tx OK Bytes Counter - MSB
 *
 * \details
 * The number of bytes transmitted - MSBs only.
 *
 * Register: \a DEV10G:DEV_STATISTICS_40BIT:TX_OK_BYTES_MSB_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_TX_OK_BYTES_MSB_CNT(target)  VTSS_IOREG(target,0x66)

/** 
 * \brief
 * The number of transmitted bytes transmitted successfully - MSBs only.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_TX_OK_BYTES_MSB_CNT . TX_OK_BYTES_MSB_CNT
 */
#define  VTSS_F_DEV10G_TX_OK_BYTES_MSB_CNT_TX_OK_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEV10G_TX_OK_BYTES_MSB_CNT_TX_OK_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEV10G_TX_OK_BYTES_MSB_CNT_TX_OK_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Rx OK Byte Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_40BIT:PMAC_RX_OK_BYTES_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_OK_BYTES_CNT(target)  VTSS_IOREG(target,0x67)

/** 
 * \brief
 * PMAC - The number of received bytes in good frames.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_OK_BYTES_CNT . PMAC_RX_OK_BYTES_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_OK_BYTES_CNT_PMAC_RX_OK_BYTES_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_OK_BYTES_CNT_PMAC_RX_OK_BYTES_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_OK_BYTES_CNT_PMAC_RX_OK_BYTES_CNT(x)  (x)


/** 
 * \brief Rx Ok Bytes Counter - MSB part
 *
 * \details
 * PMAC - The number of received bytes in good frames - MSBs only
 *
 * Register: \a DEV10G:DEV_STATISTICS_40BIT:PMAC_RX_OK_BYTES_MSB_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_OK_BYTES_MSB_CNT(target)  VTSS_IOREG(target,0x68)

/** 
 * \brief
 * PMAC - The number of received bytes in good frames - MSBs only.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_OK_BYTES_MSB_CNT . PMAC_RX_OK_BYTES_MSB_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_OK_BYTES_MSB_CNT_PMAC_RX_OK_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEV10G_PMAC_RX_OK_BYTES_MSB_CNT_PMAC_RX_OK_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEV10G_PMAC_RX_OK_BYTES_MSB_CNT_PMAC_RX_OK_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Rx Bad Byte Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_40BIT:PMAC_RX_BAD_BYTES_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_BAD_BYTES_CNT(target)  VTSS_IOREG(target,0x69)

/** 
 * \brief
 * PMAC - The number of received bytes in bad frames.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_BAD_BYTES_CNT . PMAC_RX_BAD_BYTES_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_BAD_BYTES_CNT_PMAC_RX_BAD_BYTES_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_RX_BAD_BYTES_CNT_PMAC_RX_BAD_BYTES_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_RX_BAD_BYTES_CNT_PMAC_RX_BAD_BYTES_CNT(x)  (x)


/** 
 * \brief Rx Bad Bytes Counter - MSB part
 *
 * \details
 * PMAC - The number of received bytes in bad frames -	MSBs only.
 *
 * Register: \a DEV10G:DEV_STATISTICS_40BIT:PMAC_RX_BAD_BYTES_MSB_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_RX_BAD_BYTES_MSB_CNT(target)  VTSS_IOREG(target,0x6a)

/** 
 * \brief
 * PMAC - The number of received bytes in bad frames - MSBs only.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_RX_BAD_BYTES_MSB_CNT . PMAC_RX_BAD_BYTES_MSB_CNT
 */
#define  VTSS_F_DEV10G_PMAC_RX_BAD_BYTES_MSB_CNT_PMAC_RX_BAD_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEV10G_PMAC_RX_BAD_BYTES_MSB_CNT_PMAC_RX_BAD_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEV10G_PMAC_RX_BAD_BYTES_MSB_CNT_PMAC_RX_BAD_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Tx OK Byte Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_40BIT:PMAC_TX_OK_BYTES_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_TX_OK_BYTES_CNT(target)  VTSS_IOREG(target,0x6b)

/** 
 * \brief
 * PMAC - The number of bytes transmitted successfully.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_TX_OK_BYTES_CNT . PMAC_TX_OK_BYTES_CNT
 */
#define  VTSS_F_DEV10G_PMAC_TX_OK_BYTES_CNT_PMAC_TX_OK_BYTES_CNT(x)  (x)
#define  VTSS_M_DEV10G_PMAC_TX_OK_BYTES_CNT_PMAC_TX_OK_BYTES_CNT     0xffffffff
#define  VTSS_X_DEV10G_PMAC_TX_OK_BYTES_CNT_PMAC_TX_OK_BYTES_CNT(x)  (x)


/** 
 * \brief Tx OK Bytes Counter - MSB part
Tx OK Bytes Counter - MSB
 *
 * \details
 * PMAC - The number of bytes transmitted - MSBs only.
 *
 * Register: \a DEV10G:DEV_STATISTICS_40BIT:PMAC_TX_OK_BYTES_MSB_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PMAC_TX_OK_BYTES_MSB_CNT(target)  VTSS_IOREG(target,0x6c)

/** 
 * \brief
 * PMAC - The number of transmitted bytes transmitted successfully - MSBs
 * only.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_PMAC_TX_OK_BYTES_MSB_CNT . PMAC_TX_OK_BYTES_MSB_CNT
 */
#define  VTSS_F_DEV10G_PMAC_TX_OK_BYTES_MSB_CNT_PMAC_TX_OK_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEV10G_PMAC_TX_OK_BYTES_MSB_CNT_PMAC_TX_OK_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEV10G_PMAC_TX_OK_BYTES_MSB_CNT_PMAC_TX_OK_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a DEV10G:DEV_CFG_STATUS
 *
 * Device 10G Configuration and Status Registers
 */


/** 
 * \brief Clock/Reset Control Register
 *
 * \details
 * Register: \a DEV10G:DEV_CFG_STATUS:DEV_RST_CTRL
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_RST_CTRL(target)     VTSS_IOREG(target,0x6d)

/** 
 * \brief
 * Backplane Ethernet: Enable parallel detection mode for autonegotiation
 *
 * \details 
 * '0':  Parallel detection mode disabled
 * '1': Parallel detection mode enabled
 *
 * Field: ::VTSS_DEV10G_DEV_RST_CTRL . PARDET_MODE_ENA
 */
#define  VTSS_F_DEV10G_DEV_RST_CTRL_PARDET_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_DEV10G_DEV_RST_CTRL_PARDET_MODE_ENA  VTSS_BIT(28)
#define  VTSS_X_DEV10G_DEV_RST_CTRL_PARDET_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/** 
 * \brief
 * The USXGMII replicator block samples only the first XGMII word. The
 * other replications are ignored. Only if they contain a Local Fault or
 * remote Fault ordered set the next data will be overwritten. This bit
 * will disable overwrite wit ordered sets.
 *
 * \details 
 * '0': Non-Sampleld ordered sets will overwrite the following XGMII words
 * '1': Overwrite of XGMII words with ordered sets is disabled.
 *
 * Field: ::VTSS_DEV10G_DEV_RST_CTRL . USXGMII_OSET_FILTER_DIS
 */
#define  VTSS_F_DEV10G_DEV_RST_CTRL_USXGMII_OSET_FILTER_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_DEV10G_DEV_RST_CTRL_USXGMII_OSET_FILTER_DIS  VTSS_BIT(27)
#define  VTSS_X_DEV10G_DEV_RST_CTRL_USXGMII_OSET_FILTER_DIS(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/** 
 * \brief
 * Number of USXGMII network port transported over the connected PHY.
 *
 * \details 
 * '00': Single Network Port
 * '01': Dual Network Port
 * '1-': Quad Network Port
 *
 * Field: ::VTSS_DEV10G_DEV_RST_CTRL . MUXED_USXGMII_NETWORK_PORTS
 */
#define  VTSS_F_DEV10G_DEV_RST_CTRL_MUXED_USXGMII_NETWORK_PORTS(x)  VTSS_ENCODE_BITFIELD(x,25,2)
#define  VTSS_M_DEV10G_DEV_RST_CTRL_MUXED_USXGMII_NETWORK_PORTS     VTSS_ENCODE_BITMASK(25,2)
#define  VTSS_X_DEV10G_DEV_RST_CTRL_MUXED_USXGMII_NETWORK_PORTS(x)  VTSS_EXTRACT_BITFIELD(x,25,2)

/** 
 * \brief
 * This field is used to configure the SERDES clock frequency.
 *
 * \details 
 * '00': 10G SerDes Speed
 * '01': 5G SerDes Speed
 * '1-': Reserved
 *
 * Field: ::VTSS_DEV10G_DEV_RST_CTRL . SERDES_SPEED_SEL
 */
#define  VTSS_F_DEV10G_DEV_RST_CTRL_SERDES_SPEED_SEL(x)  VTSS_ENCODE_BITFIELD(x,23,2)
#define  VTSS_M_DEV10G_DEV_RST_CTRL_SERDES_SPEED_SEL     VTSS_ENCODE_BITMASK(23,2)
#define  VTSS_X_DEV10G_DEV_RST_CTRL_SERDES_SPEED_SEL(x)  VTSS_EXTRACT_BITFIELD(x,23,2)

/** 
 * \brief
 * This field is used to configure the MAC and PCS Rx/Tx clock frequencies.
 *
 * \details 
 * '000': MAC works at 10000 Mbps
 * '001': MAC works at 5000 Mbps
 * '010': MAC works at 2500 Mbps
 * '011': MAC works at 1000 Mbps
 * '100': MAC works at 100 Mbps
 * '101': MAC works at 10 Mbps
 * Unused values are reserved.
 *
 * Field: ::VTSS_DEV10G_DEV_RST_CTRL . SPEED_SEL
 */
#define  VTSS_F_DEV10G_DEV_RST_CTRL_SPEED_SEL(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_DEV10G_DEV_RST_CTRL_SPEED_SEL     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_DEV10G_DEV_RST_CTRL_SPEED_SEL(x)  VTSS_EXTRACT_BITFIELD(x,20,3)

/** 
 * \brief
 * Reset PCS Tx clock domains of the device.
 *
 * \details 
 * '0': The PCS Tx clock domain is NOT reset
 * '1': The PCS Tx clock domain is reset 
 * Note: PCS_TX_RST is NOT a one-shot operation. The PCS Tx clock domain
 * remains reset until a '0' is written to PCS_TX_RST.
 *
 * Field: ::VTSS_DEV10G_DEV_RST_CTRL . PCS_TX_RST
 */
#define  VTSS_F_DEV10G_DEV_RST_CTRL_PCS_TX_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DEV10G_DEV_RST_CTRL_PCS_TX_RST  VTSS_BIT(12)
#define  VTSS_X_DEV10G_DEV_RST_CTRL_PCS_TX_RST(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Reset PCS Rx clock domains of the device.
 *
 * \details 
 * '0': The PCS Rx clock domain is NOT reset
 * '1': The PCS Rx clock domain is reset 
 * Note: PCS_RX_RST is NOT a one-shot operation. The PCS Rx clock domain
 * remains reset until a '0' is written to PCS_RX_RST.
 *
 * Field: ::VTSS_DEV10G_DEV_RST_CTRL . PCS_RX_RST
 */
#define  VTSS_F_DEV10G_DEV_RST_CTRL_PCS_RX_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV10G_DEV_RST_CTRL_PCS_RX_RST  VTSS_BIT(8)
#define  VTSS_X_DEV10G_DEV_RST_CTRL_PCS_RX_RST(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Reset MAC Tx clock domain of device.
 *
 * \details 
 * '0': The MAC Tx clock domain is not reset.
 * '1': The MAC Tx clock domain is reset.
 * 
 * Note: The MAC Tx clock domain remains reset until 0 is written to this
 * register field.
 *
 * Field: ::VTSS_DEV10G_DEV_RST_CTRL . MAC_TX_RST
 */
#define  VTSS_F_DEV10G_DEV_RST_CTRL_MAC_TX_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_DEV_RST_CTRL_MAC_TX_RST  VTSS_BIT(4)
#define  VTSS_X_DEV10G_DEV_RST_CTRL_MAC_TX_RST(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Reset MAC Rx clock domains of the device.
 *
 * \details 
 * '0': The MAC Rx clock domain is NOT reset
 * '1': The MAC Rx clock domain is reset 
 * Note: MAC_RX_RST is NOT a one-shot operation. The MAC Rx clock domain
 * remains reset until a '0' is written to MAC_RX_RST.
 *
 * Field: ::VTSS_DEV10G_DEV_RST_CTRL . MAC_RX_RST
 */
#define  VTSS_F_DEV10G_DEV_RST_CTRL_MAC_RX_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_DEV_RST_CTRL_MAC_RX_RST  VTSS_BIT(0)
#define  VTSS_X_DEV10G_DEV_RST_CTRL_MAC_RX_RST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Port Protection Configuration Register
 *
 * \details
 * When port protection is enabled the device will snoop and transmit data
 * destined for another device 10G identified by port_protect_id.
 *
 * Register: \a DEV10G:DEV_CFG_STATUS:DEV_PORT_PROTECT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_PORT_PROTECT(target)  VTSS_IOREG(target,0x6e)

/** 
 * \brief
 * Indicates from which port egress data must be copied and transmitted at
 * this Ethernet port.The port from which egress data is copied must always
 * be a port that is closer to the ASM. I.e. DEV(X) may be configured to
 * snoop egress data destined for DEV(X+n), where DEV(X+n) is closer to the
 * ASM - but NOT vice versa.
 *
 * \details 
 * 0: Reserved
 * 1: Egress data destined for DEV(1) is also transmitted by this device.
 * 2: Egress data destined for DEV(2) is also transmitted by this device.
 * ..
 *
 * Field: ::VTSS_DEV10G_DEV_PORT_PROTECT . PORT_PROTECT_ID
 */
#define  VTSS_F_DEV10G_DEV_PORT_PROTECT_PORT_PROTECT_ID(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_DEV10G_DEV_PORT_PROTECT_PORT_PROTECT_ID     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_DEV10G_DEV_PORT_PROTECT_PORT_PROTECT_ID(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Enables snooping of egress data from another port. The port from which
 * egress data is copied and transmitted at the Ethernet port is determined
 * by the PORT_PROTECT_ID configuration.
 *
 * \details 
 * '0': Port protection is disabled.
 * '1': Port protection is enabled.
 *
 * Field: ::VTSS_DEV10G_DEV_PORT_PROTECT . PORT_PROTECT_ENA
 */
#define  VTSS_F_DEV10G_DEV_PORT_PROTECT_PORT_PROTECT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_DEV_PORT_PROTECT_PORT_PROTECT_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV10G_DEV_PORT_PROTECT_PORT_PROTECT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Loopback Configuration Register
 *
 * \details
 * A number of internal loopback can be enabled in each device by the
 * configuration bits in this register.
 *
 * Register: \a DEV10G:DEV_CFG_STATUS:DEV_LB_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_LB_CFG(target)       VTSS_IOREG(target,0x6f)

/** 
 * \brief
 * An internal loopback from the igress Taxi bus to the egress Taxi bus can
 * be enabled.
 *
 * \details 
 * '0': Loopback from Taxi ingress bus to Taxi egress bus disabled
 * '1': Loopback from Taxi ingress bus to Taxi egress bus enabled
 *
 * Field: ::VTSS_DEV10G_DEV_LB_CFG . TAXI_PHY_LB_ENA
 */
#define  VTSS_F_DEV10G_DEV_LB_CFG_TAXI_PHY_LB_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_DEV_LB_CFG_TAXI_PHY_LB_ENA  VTSS_BIT(4)
#define  VTSS_X_DEV10G_DEV_LB_CFG_TAXI_PHY_LB_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * An internal loopback from the egress Taxi bus to the ingress Taxi bus
 * can be enabled.
 *
 * \details 
 * '0': Loopback from Taxi egress to Taxi ingress is disabled
 * '1': Loopback from Taxi egress to Taxi ingress is enabled
 *
 * Field: ::VTSS_DEV10G_DEV_LB_CFG . TAXI_HOST_LB_ENA
 */
#define  VTSS_F_DEV10G_DEV_LB_CFG_TAXI_HOST_LB_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_DEV_LB_CFG_TAXI_HOST_LB_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV10G_DEV_LB_CFG_TAXI_HOST_LB_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief USXGMII Tx rate adaptation FIFO threshold control
 *
 * \details
 * Set the add and drop thresholds for the Tx rate adaptation (radapt) FIFO
 *
 * Register: \a DEV10G:DEV_CFG_STATUS:USXGMII_TX_RADAPT_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_USXGMII_TX_RADAPT_CFG(target)  VTSS_IOREG(target,0x70)

/** 
 * \brief
 * Disable TX local fault generation when no alignment has been reached
 *
 * \details 
 * 0: Output local fault symbol at XGMII when not aligned
 * 1: Output IDLE symbols at XGMII when not aligned
 *
 * Field: ::VTSS_DEV10G_USXGMII_TX_RADAPT_CFG . TX_LF_GEN_DIS
 */
#define  VTSS_F_DEV10G_USXGMII_TX_RADAPT_CFG_TX_LF_GEN_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DEV10G_USXGMII_TX_RADAPT_CFG_TX_LF_GEN_DIS  VTSS_BIT(31)
#define  VTSS_X_DEV10G_USXGMII_TX_RADAPT_CFG_TX_LF_GEN_DIS(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * One-shot that causes the Tx rate adaptation FIFO to be cleared and
 * reset. Bit is reset by hardware.
 *
 * \details 
 * 0: No action
 * 1: Clear FIFO
 *
 * Field: ::VTSS_DEV10G_USXGMII_TX_RADAPT_CFG . TX_RADAPT_FIFO_FLUSH
 */
#define  VTSS_F_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_FIFO_FLUSH(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_FIFO_FLUSH  VTSS_BIT(28)
#define  VTSS_X_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_FIFO_FLUSH(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/** 
 * \brief
 * Set the minimum inter-frame gap to maintain during rate adaptation when
 * dropping transactions. Setting the value to 1 means that 1 idle or
 * ordered set is kept after a terminate. When set to 2 or 3, that many
 * idle or ordered set transactions are kept. Each transaction is 4 bytes.
 *
 * \details 
 * 0: INVALID
 * 1: 1 Idle/O set column maintained
 * 2: 2 Idle/O set column maintained
 * 3: 3 Idle/O set column maintained
 *
 * Field: ::VTSS_DEV10G_USXGMII_TX_RADAPT_CFG . TX_RADAPT_MIN_IFG
 */
#define  VTSS_F_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_MIN_IFG(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_MIN_IFG     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_MIN_IFG(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Set the add threshold in the FIFO. Level is in 72-bit words.
 *
 * \details 
 * Field: ::VTSS_DEV10G_USXGMII_TX_RADAPT_CFG . TX_RADAPT_ADD_LVL
 */
#define  VTSS_F_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_ADD_LVL(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_ADD_LVL     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_ADD_LVL(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Set the drop threshold in the FIFO. Level is in 72-bit words.
 *
 * \details 
 * Field: ::VTSS_DEV10G_USXGMII_TX_RADAPT_CFG . TX_RADAPT_DROP_LVL
 */
#define  VTSS_F_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_DROP_LVL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_DROP_LVL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DEV10G_USXGMII_TX_RADAPT_CFG_TX_RADAPT_DROP_LVL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Debug Configuration Register
 *
 * \details
 * Register: \a DEV10G:DEV_CFG_STATUS:DEV_MISC_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_MISC_CFG(target)     VTSS_IOREG(target,0x71)

/** 
 * \brief
 * The device can be configured to disregard the fcs_update indication from
 * the DSM and not update the FCS of any transmitted frames.
 *
 * \details 
 * 0: The FCS of transmitted frames is updated according to the fcs_update
 * indication from the DSM.
 * 1: The FCS of transmitted frames is never updated.
 * 2: The FCS of transmitted frames is always updated.
 *
 * Field: ::VTSS_DEV10G_DEV_MISC_CFG . TX_FCS_UPDATE_SEL
 */
#define  VTSS_F_DEV10G_DEV_MISC_CFG_TX_FCS_UPDATE_SEL(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_DEV10G_DEV_MISC_CFG_TX_FCS_UPDATE_SEL     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_DEV10G_DEV_MISC_CFG_TX_FCS_UPDATE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * Clears RX_RESYNC_MAX_FILL_LVL that holds the max. fill level of RX
 * RESYNC FIFO. This is a on shot bit automatically cleared by HW.
 *
 * \details 
 * '0': No action
 * '1': clears RX_RESYNC_MAX_FILL_LVL (Bit is automatically cleared)
 *
 * Field: ::VTSS_DEV10G_DEV_MISC_CFG . RX_RESYNC_MAX_FILL_LVL_CLR
 */
#define  VTSS_F_DEV10G_DEV_MISC_CFG_RX_RESYNC_MAX_FILL_LVL_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DEV10G_DEV_MISC_CFG_RX_RESYNC_MAX_FILL_LVL_CLR  VTSS_BIT(13)
#define  VTSS_X_DEV10G_DEV_MISC_CFG_RX_RESYNC_MAX_FILL_LVL_CLR(x)  VTSS_EXTRACT_BITFIELD(x,13,1)


/** 
 * \brief Configures PTP timestamping logic
 *
 * \details
 * Register: \a DEV10G:DEV_CFG_STATUS:PTP_STAMPER_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PTP_STAMPER_CFG(target)  VTSS_IOREG(target,0x72)

/** 
 * \brief
 * Specifies the amount of line bit times to subtract from delay in egress
 * direction when the swap signal is asserted. 
 *
 * \details 
 * 00: Subtract 0 BT
 * 01: Subtract 32 BT
 * 10: Subtract 33 BT
 * 11: Subtract 34 BT

 *
 * Field: ::VTSS_DEV10G_PTP_STAMPER_CFG . PTP_TX_SFT_VAL
 */
#define  VTSS_F_DEV10G_PTP_STAMPER_CFG_PTP_TX_SFT_VAL(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_DEV10G_PTP_STAMPER_CFG_PTP_TX_SFT_VAL     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_DEV10G_PTP_STAMPER_CFG_PTP_TX_SFT_VAL(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Specifies the amount of line bit times to subtract from delay in ingress
 * direction when the swap signal is asserted. 
 *
 * \details 
 * 00: Subtract 0 BT
 * 01: Subtract 32 BT
 * 10: Subtract 33 BT
 * 11: Subtract 34 BT

 *
 * Field: ::VTSS_DEV10G_PTP_STAMPER_CFG . PTP_RX_SFT_VAL
 */
#define  VTSS_F_DEV10G_PTP_STAMPER_CFG_PTP_RX_SFT_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DEV10G_PTP_STAMPER_CFG_PTP_RX_SFT_VAL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DEV10G_PTP_STAMPER_CFG_PTP_RX_SFT_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Miscellaneous Sticky Bit Register
 *
 * \details
 * Clear the sticky bits by writing a '1' in the relevant bitgroups.
 *
 * Register: \a DEV10G:DEV_CFG_STATUS:DEV_STICKY
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STICKY(target)       VTSS_IOREG(target,0x73)

/** 
 * \brief
 * Indicates if an overflow has occurred in the ingress resynchronization
 * FIFO.Writing a '1' clears the sticky bit.
 *
 * \details 
 * '0': No overflow has occurred in the ingress resynchronization FIFO.
 * '1': An overflow has occurred in the ingress resynchronization FIFO.
 *
 * Field: ::VTSS_DEV10G_DEV_STICKY . RX_RESYNC_FIFO_OFLW_STICKY
 */
#define  VTSS_F_DEV10G_DEV_STICKY_RX_RESYNC_FIFO_OFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DEV10G_DEV_STICKY_RX_RESYNC_FIFO_OFLW_STICKY  VTSS_BIT(12)
#define  VTSS_X_DEV10G_DEV_STICKY_RX_RESYNC_FIFO_OFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Indicates that a missing SOF has been detected in the Rx path of the
 * DEV10G.Writing a '1' clears the sticky bit.
 *
 * \details 
 * '0': No missing SOF detected
 * '1': Missing SOF indication detected in Rx path of DEV10G.
 *
 * Field: ::VTSS_DEV10G_DEV_STICKY . RX_SOF_STICKY
 */
#define  VTSS_F_DEV10G_DEV_STICKY_RX_SOF_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_DEV10G_DEV_STICKY_RX_SOF_STICKY  VTSS_BIT(10)
#define  VTSS_X_DEV10G_DEV_STICKY_RX_SOF_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Indicates that a missing EOF has been detected.Writing a '1' clears the
 * sticky bit.
 *
 * \details 
 * '0': No EOF error detected
 * '1': Missing EOF indication detected in Rx path of DEV10G.
 *
 * Field: ::VTSS_DEV10G_DEV_STICKY . RX_EOF_STICKY
 */
#define  VTSS_F_DEV10G_DEV_STICKY_RX_EOF_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV10G_DEV_STICKY_RX_EOF_STICKY  VTSS_BIT(8)
#define  VTSS_X_DEV10G_DEV_STICKY_RX_EOF_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Indicates that a missing EOF has been detected.Writing a '1' clears the
 * sticky bit.
 *
 * \details 
 * '0': No EOF error detected
 * '1': Missing EOF indication detected in Tx path of DEV10G.
 *
 * Field: ::VTSS_DEV10G_DEV_STICKY . TX_EOF_STICKY
 */
#define  VTSS_F_DEV10G_DEV_STICKY_TX_EOF_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DEV10G_DEV_STICKY_TX_EOF_STICKY  VTSS_BIT(5)
#define  VTSS_X_DEV10G_DEV_STICKY_TX_EOF_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Indicates that a missing SOF has been detected in the Tx path of the
 * DEV10G.Writing a '1' clears the sticky bit.
 *
 * \details 
 * '0': No missing SOF detected
 * '1': Missing SOF indication detected in Tx path of DEV10G.
 *
 * Field: ::VTSS_DEV10G_DEV_STICKY . TX_SOF_STICKY
 */
#define  VTSS_F_DEV10G_DEV_STICKY_TX_SOF_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_DEV_STICKY_TX_SOF_STICKY  VTSS_BIT(4)
#define  VTSS_X_DEV10G_DEV_STICKY_TX_SOF_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * FIFO underflow interrupt
 *
 * \details 
 * 0: No underflow
 * 1: FIFO underflow
 *
 * Field: ::VTSS_DEV10G_DEV_STICKY . TX_RADAPT_FIFO_UFLOW_STICKY
 */
#define  VTSS_F_DEV10G_DEV_STICKY_TX_RADAPT_FIFO_UFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV10G_DEV_STICKY_TX_RADAPT_FIFO_UFLOW_STICKY  VTSS_BIT(3)
#define  VTSS_X_DEV10G_DEV_STICKY_TX_RADAPT_FIFO_UFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * FIFO overflow interrupt
 *
 * \details 
 * 0: No overflow
 * 1: FIFO overflow
 *
 * Field: ::VTSS_DEV10G_DEV_STICKY . TX_RADAPT_FIFO_OFLOW_STICKY
 */
#define  VTSS_F_DEV10G_DEV_STICKY_TX_RADAPT_FIFO_OFLOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV10G_DEV_STICKY_TX_RADAPT_FIFO_OFLOW_STICKY  VTSS_BIT(2)
#define  VTSS_X_DEV10G_DEV_STICKY_TX_RADAPT_FIFO_OFLOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


/** 
 * \brief Interrupt Source Register
 *
 * \details
 * Interrupt Source Register
 *
 * Register: \a DEV10G:DEV_CFG_STATUS:INTR
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_INTR(target)             VTSS_IOREG(target,0x74)

/** 
 * \brief
 * USXGMII ANEG next page receive interrupt.
 *
 * \details 
 * 0: No interrupt
 * 1: Interrupt occurred
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV10G_INTR . AN_PAGE_RX_INTR
 */
#define  VTSS_F_DEV10G_INTR_AN_PAGE_RX_INTR(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_DEV10G_INTR_AN_PAGE_RX_INTR   VTSS_BIT(11)
#define  VTSS_X_DEV10G_INTR_AN_PAGE_RX_INTR(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * USXGMII ANEG Link UP interrupt.
 *
 * \details 
 * 0: No interrupt
 * 1: Interrupt occurred
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV10G_INTR . AN_LINK_UP_INTR
 */
#define  VTSS_F_DEV10G_INTR_AN_LINK_UP_INTR(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_DEV10G_INTR_AN_LINK_UP_INTR   VTSS_BIT(10)
#define  VTSS_X_DEV10G_INTR_AN_LINK_UP_INTR(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * USXGMII ANEG Link down interrupt.
 *
 * \details 
 * 0: No interrupt
 * 1: Interrupt occurred
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV10G_INTR . AN_LINK_DWN_INTR
 */
#define  VTSS_F_DEV10G_INTR_AN_LINK_DWN_INTR(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_DEV10G_INTR_AN_LINK_DWN_INTR  VTSS_BIT(9)
#define  VTSS_X_DEV10G_INTR_AN_LINK_DWN_INTR(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * USXGMII rate adaptation FIFO interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR . USXGMII_RADAPT_INTR
 */
#define  VTSS_F_DEV10G_INTR_USXGMII_RADAPT_INTR(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV10G_INTR_USXGMII_RADAPT_INTR  VTSS_BIT(8)
#define  VTSS_X_DEV10G_INTR_USXGMII_RADAPT_INTR(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * SerDes 10G, Base-R interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR . SD10G_BR_INTR
 */
#define  VTSS_F_DEV10G_INTR_SD10G_BR_INTR(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DEV10G_INTR_SD10G_BR_INTR     VTSS_BIT(7)
#define  VTSS_X_DEV10G_INTR_SD10G_BR_INTR(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * SerDes 10G, server signal failure interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR . SD10G_SSF_INTR
 */
#define  VTSS_F_DEV10G_INTR_SD10G_SSF_INTR(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DEV10G_INTR_SD10G_SSF_INTR    VTSS_BIT(6)
#define  VTSS_X_DEV10G_INTR_SD10G_SSF_INTR(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * SerDes 10G, KR interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR . SD10G_KR_INTR
 */
#define  VTSS_F_DEV10G_INTR_SD10G_KR_INTR(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DEV10G_INTR_SD10G_KR_INTR     VTSS_BIT(5)
#define  VTSS_X_DEV10G_INTR_SD10G_KR_INTR(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Aggregate of BaseR PCS indications, see PCS_10GBASE_R::PCS_INTR_STAT and
 * PCS_10GBASE_R::PCS_INTR_MASK for more information. This field is set
 * when any BaseR PCS interrupt indication is active and enabled.
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR . PCS_BR_INTR
 */
#define  VTSS_F_DEV10G_INTR_PCS_BR_INTR(x)    VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_INTR_PCS_BR_INTR       VTSS_BIT(4)
#define  VTSS_X_DEV10G_INTR_PCS_BR_INTR(x)    VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * PCS10G, PCS1G: TX Low Power Idle mode has changed
 *
 * \details 
 * 0 = no indication
 * 1 = active indication
 *
 * Field: ::VTSS_DEV10G_INTR . TX_LPI_INTR
 */
#define  VTSS_F_DEV10G_INTR_TX_LPI_INTR(x)    VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV10G_INTR_TX_LPI_INTR       VTSS_BIT(3)
#define  VTSS_X_DEV10G_INTR_TX_LPI_INTR(x)    VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * PCS10G, PCS1G: RX Low Power Idle mode has changed
 *
 * \details 
 * 0 = no indication
 * 1 = active indication
 *
 * Field: ::VTSS_DEV10G_INTR . RX_LPI_INTR
 */
#define  VTSS_F_DEV10G_INTR_RX_LPI_INTR(x)    VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV10G_INTR_RX_LPI_INTR       VTSS_BIT(2)
#define  VTSS_X_DEV10G_INTR_RX_LPI_INTR(x)    VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Link status is up (source: PCS1G, PCS10G or PCS2x6G depending on current
 * DEV10G mode)
 *
 * \details 
 * 0 = no indication
 * 1 = active indication
 *
 * Field: ::VTSS_DEV10G_INTR . LINK_UP_INTR
 */
#define  VTSS_F_DEV10G_INTR_LINK_UP_INTR(x)   VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV10G_INTR_LINK_UP_INTR      VTSS_BIT(1)
#define  VTSS_X_DEV10G_INTR_LINK_UP_INTR(x)   VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Link status is down (source: PCS1G, PCS10G or PCS2x6G depending on
 * current DEV10G mode)
 *
 * \details 
 * 0 = no indication
 * 1 = active indication
 *
 * Field: ::VTSS_DEV10G_INTR . LINK_DWN_INTR
 */
#define  VTSS_F_DEV10G_INTR_LINK_DWN_INTR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_INTR_LINK_DWN_INTR     VTSS_BIT(0)
#define  VTSS_X_DEV10G_INTR_LINK_DWN_INTR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Interrupt Enable Register
 *
 * \details
 * Interrupt Enable Register
 *
 * Register: \a DEV10G:DEV_CFG_STATUS:INTR_ENA
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_INTR_ENA(target)         VTSS_IOREG(target,0x75)

/** 
 * \brief
 * Set to enable propagation of USXGMII ANEG Page RX interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_ENA . AN_PAGE_RX_INTR_ENA
 */
#define  VTSS_F_DEV10G_INTR_ENA_AN_PAGE_RX_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_DEV10G_INTR_ENA_AN_PAGE_RX_INTR_ENA  VTSS_BIT(11)
#define  VTSS_X_DEV10G_INTR_ENA_AN_PAGE_RX_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Set to enable propagation of USXGMII ANEG Link up interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_ENA . AN_LINK_UP_INTR_ENA
 */
#define  VTSS_F_DEV10G_INTR_ENA_AN_LINK_UP_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_DEV10G_INTR_ENA_AN_LINK_UP_INTR_ENA  VTSS_BIT(10)
#define  VTSS_X_DEV10G_INTR_ENA_AN_LINK_UP_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Set to enable propagation of USXGMII ANEG Link down interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_ENA . AN_LINK_DWN_INTR_ENA
 */
#define  VTSS_F_DEV10G_INTR_ENA_AN_LINK_DWN_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_DEV10G_INTR_ENA_AN_LINK_DWN_INTR_ENA  VTSS_BIT(9)
#define  VTSS_X_DEV10G_INTR_ENA_AN_LINK_DWN_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Set to enable propagation of USXGMII rate adaptation FIFO interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_ENA . USXGMII_RADAPT_INTR_ENA
 */
#define  VTSS_F_DEV10G_INTR_ENA_USXGMII_RADAPT_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV10G_INTR_ENA_USXGMII_RADAPT_INTR_ENA  VTSS_BIT(8)
#define  VTSS_X_DEV10G_INTR_ENA_USXGMII_RADAPT_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Set to enable propagation of SerDes 10G, Base-R interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_ENA . SD10G_BR_INTR_ENA
 */
#define  VTSS_F_DEV10G_INTR_ENA_SD10G_BR_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DEV10G_INTR_ENA_SD10G_BR_INTR_ENA  VTSS_BIT(7)
#define  VTSS_X_DEV10G_INTR_ENA_SD10G_BR_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Set to enable propagation of SerDes 10G, server signal failure
 * interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_ENA . SD10G_SSF_INTR_ENA
 */
#define  VTSS_F_DEV10G_INTR_ENA_SD10G_SSF_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DEV10G_INTR_ENA_SD10G_SSF_INTR_ENA  VTSS_BIT(6)
#define  VTSS_X_DEV10G_INTR_ENA_SD10G_SSF_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Set to enable propagation of SerDes 10G, KR interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_ENA . SD10G_KR_INTR_ENA
 */
#define  VTSS_F_DEV10G_INTR_ENA_SD10G_KR_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DEV10G_INTR_ENA_SD10G_KR_INTR_ENA  VTSS_BIT(5)
#define  VTSS_X_DEV10G_INTR_ENA_SD10G_KR_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Set to enable propagation of PCS_BR interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_ENA . PCS_BR_INTR_ENA
 */
#define  VTSS_F_DEV10G_INTR_ENA_PCS_BR_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_INTR_ENA_PCS_BR_INTR_ENA  VTSS_BIT(4)
#define  VTSS_X_DEV10G_INTR_ENA_PCS_BR_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set to enable propagation of TX_LPI interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_ENA . TX_LPI_INTR_ENA
 */
#define  VTSS_F_DEV10G_INTR_ENA_TX_LPI_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV10G_INTR_ENA_TX_LPI_INTR_ENA  VTSS_BIT(3)
#define  VTSS_X_DEV10G_INTR_ENA_TX_LPI_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set to enable propagation of RX_LPI interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_ENA . RX_LPI_INTR_ENA
 */
#define  VTSS_F_DEV10G_INTR_ENA_RX_LPI_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV10G_INTR_ENA_RX_LPI_INTR_ENA  VTSS_BIT(2)
#define  VTSS_X_DEV10G_INTR_ENA_RX_LPI_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set to enable propagation of LINK_UP interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_ENA . LINK_UP_INTR_ENA
 */
#define  VTSS_F_DEV10G_INTR_ENA_LINK_UP_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV10G_INTR_ENA_LINK_UP_INTR_ENA  VTSS_BIT(1)
#define  VTSS_X_DEV10G_INTR_ENA_LINK_UP_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set to enable propagation of LINK_DWN interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_ENA . LINK_DWN_INTR_ENA
 */
#define  VTSS_F_DEV10G_INTR_ENA_LINK_DWN_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_INTR_ENA_LINK_DWN_INTR_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV10G_INTR_ENA_LINK_DWN_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Interrupt Status Register
 *
 * \details
 * Interrupt Status Register
 *
 * Register: \a DEV10G:DEV_CFG_STATUS:INTR_IDENT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_INTR_IDENT(target)       VTSS_IOREG(target,0x76)

/** 
 * \brief
 * Set if USXGMII aneg Page RX interrupt is currently active (indicating
 * interrupt towards higher level interrupt controller).
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_IDENT . AN_PAGE_RX_INTR_IDENT
 */
#define  VTSS_F_DEV10G_INTR_IDENT_AN_PAGE_RX_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_DEV10G_INTR_IDENT_AN_PAGE_RX_INTR_IDENT  VTSS_BIT(11)
#define  VTSS_X_DEV10G_INTR_IDENT_AN_PAGE_RX_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Set if USXGMII aneg link up interrupt is currently active (indicating
 * interrupt towards higher level interrupt controller).
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_IDENT . AN_LINK_UP_INTR_IDENT
 */
#define  VTSS_F_DEV10G_INTR_IDENT_AN_LINK_UP_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_DEV10G_INTR_IDENT_AN_LINK_UP_INTR_IDENT  VTSS_BIT(10)
#define  VTSS_X_DEV10G_INTR_IDENT_AN_LINK_UP_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Set if USXGMII aneg link down interrupt is currently active (indicating
 * interrupt towards higher level interrupt controller).
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_IDENT . AN_LINK_DWN_INTR_IDENT
 */
#define  VTSS_F_DEV10G_INTR_IDENT_AN_LINK_DWN_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_DEV10G_INTR_IDENT_AN_LINK_DWN_INTR_IDENT  VTSS_BIT(9)
#define  VTSS_X_DEV10G_INTR_IDENT_AN_LINK_DWN_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Set if USXGMII rate adaptation FIFO interrupt is currently active
 * (indicating interrupt towards higher level interrupt controller).
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_IDENT . USXGMII_RADAPT_INTR_IDENT
 */
#define  VTSS_F_DEV10G_INTR_IDENT_USXGMII_RADAPT_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV10G_INTR_IDENT_USXGMII_RADAPT_INTR_IDENT  VTSS_BIT(8)
#define  VTSS_X_DEV10G_INTR_IDENT_USXGMII_RADAPT_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Set if SD10G_BR interrupt is currently active (indicating interrupt
 * towards higher level interrupt controller).
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_IDENT . SD10G_BR_INTR_IDENT
 */
#define  VTSS_F_DEV10G_INTR_IDENT_SD10G_BR_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DEV10G_INTR_IDENT_SD10G_BR_INTR_IDENT  VTSS_BIT(7)
#define  VTSS_X_DEV10G_INTR_IDENT_SD10G_BR_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Set if SD10G_SSF interrupt is currently active (indicating interrupt
 * towards higher level interrupt controller).
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_IDENT . SD10G_SSF_INTR_IDENT
 */
#define  VTSS_F_DEV10G_INTR_IDENT_SD10G_SSF_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DEV10G_INTR_IDENT_SD10G_SSF_INTR_IDENT  VTSS_BIT(6)
#define  VTSS_X_DEV10G_INTR_IDENT_SD10G_SSF_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Set if SD10G_KR interrupt is currently active (indicating interrupt
 * towards higher level interrupt controller).
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_IDENT . SD10G_KR_INTR_IDENT
 */
#define  VTSS_F_DEV10G_INTR_IDENT_SD10G_KR_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DEV10G_INTR_IDENT_SD10G_KR_INTR_IDENT  VTSS_BIT(5)
#define  VTSS_X_DEV10G_INTR_IDENT_SD10G_KR_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Set if PCS_BR interrupt is currently active (indicating interrupt
 * towards higher level interrupt controller).
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_IDENT . PCS_BR_INTR_IDENT
 */
#define  VTSS_F_DEV10G_INTR_IDENT_PCS_BR_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_INTR_IDENT_PCS_BR_INTR_IDENT  VTSS_BIT(4)
#define  VTSS_X_DEV10G_INTR_IDENT_PCS_BR_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set if TX_LPI interrupt is currently active (indicating interrupt
 * towards higher level interrupt controller).
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_IDENT . TX_LPI_INTR_IDENT
 */
#define  VTSS_F_DEV10G_INTR_IDENT_TX_LPI_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV10G_INTR_IDENT_TX_LPI_INTR_IDENT  VTSS_BIT(3)
#define  VTSS_X_DEV10G_INTR_IDENT_TX_LPI_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set if RX_LPI interrupt is currently active (indicating interrupt
 * towards higher level interrupt controller).
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_IDENT . RX_LPI_INTR_IDENT
 */
#define  VTSS_F_DEV10G_INTR_IDENT_RX_LPI_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV10G_INTR_IDENT_RX_LPI_INTR_IDENT  VTSS_BIT(2)
#define  VTSS_X_DEV10G_INTR_IDENT_RX_LPI_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set if LINK_UP interrupt is currently active (indicating interrupt
 * towards higher level interrupt controller).
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_IDENT . LINK_UP_INTR_IDENT
 */
#define  VTSS_F_DEV10G_INTR_IDENT_LINK_UP_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV10G_INTR_IDENT_LINK_UP_INTR_IDENT  VTSS_BIT(1)
#define  VTSS_X_DEV10G_INTR_IDENT_LINK_UP_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set if LINK_DWN interrupt is currently active (indicating interrupt
 * towards higher level interrupt controller).
 *
 * \details 
 * Field: ::VTSS_DEV10G_INTR_IDENT . LINK_DWN_INTR_IDENT
 */
#define  VTSS_F_DEV10G_INTR_IDENT_LINK_DWN_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_INTR_IDENT_LINK_DWN_INTR_IDENT  VTSS_BIT(0)
#define  VTSS_X_DEV10G_INTR_IDENT_LINK_DWN_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Ingress (receive) Path Status Register
 *
 * \details
 * Register: \a DEV10G:DEV_CFG_STATUS:DEV_RX_STATUS
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_RX_STATUS(target)    VTSS_IOREG(target,0x77)

/** 
 * \brief
 * Maximum fill level of Rx resync FIFO. Fill level can be cleared by
 * writing to RX_RESYNC_MAX_FILL_LVL_CLR bit.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_RX_STATUS . RX_RESYNC_MAX_FILL_LVL
 */
#define  VTSS_F_DEV10G_DEV_RX_STATUS_RX_RESYNC_MAX_FILL_LVL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DEV10G_DEV_RX_STATUS_RX_RESYNC_MAX_FILL_LVL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DEV10G_DEV_RX_STATUS_RX_RESYNC_MAX_FILL_LVL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Control Energy Efficient Ethernet operation.
 *
 * \details
 * Register: \a DEV10G:DEV_CFG_STATUS:EEE_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_EEE_CFG(target)          VTSS_IOREG(target,0x78)

/** 
 * \brief
 * Enable EEE operation on the port.A port enters the low power mode when
 * no egress queues have data ready.The port is activated when one of the
 * following conditions is true:- A queue has been non-empty for
 * EEE_TIMER_AGE.- A queue has more than EEE_HIGH_FRAMES frames pending.- A
 * queue has more than EEE_HIGH_BYTES bytes pending.- A queue is marked as
 * a fast queue, and has data pending.
 *
 * \details 
 * Field: ::VTSS_DEV10G_EEE_CFG . EEE_ENA
 */
#define  VTSS_F_DEV10G_EEE_CFG_EEE_ENA(x)     VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_DEV10G_EEE_CFG_EEE_ENA        VTSS_BIT(22)
#define  VTSS_X_DEV10G_EEE_CFG_EEE_ENA(x)     VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Maximum time frames in any queue must wait before the port is activated.
 * The default value corresponds to 48 us.
 *
 * \details 
 * Time = 4**(EEE_TIMER_AGE/16) * (EEE_TIMER_AGE mod 16) microseconds
 *
 * Field: ::VTSS_DEV10G_EEE_CFG . EEE_TIMER_AGE
 */
#define  VTSS_F_DEV10G_EEE_CFG_EEE_TIMER_AGE(x)  VTSS_ENCODE_BITFIELD(x,15,7)
#define  VTSS_M_DEV10G_EEE_CFG_EEE_TIMER_AGE     VTSS_ENCODE_BITMASK(15,7)
#define  VTSS_X_DEV10G_EEE_CFG_EEE_TIMER_AGE(x)  VTSS_EXTRACT_BITFIELD(x,15,7)

/** 
 * \brief
 * Time from the egress port is activated until frame transmission is
 * restarted. Default value corresponds to 16 us.
 *
 * \details 
 * Time = 4**(EEE_TIMER_WAKEUP/16) * (EEE_TIMER_WAKEUP mod 16) microseconds
 *
 * Field: ::VTSS_DEV10G_EEE_CFG . EEE_TIMER_WAKEUP
 */
#define  VTSS_F_DEV10G_EEE_CFG_EEE_TIMER_WAKEUP(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_DEV10G_EEE_CFG_EEE_TIMER_WAKEUP     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_DEV10G_EEE_CFG_EEE_TIMER_WAKEUP(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/** 
 * \brief
 * When all queues are empty, the port is kept active until this time has
 * passed. Default value corresponds to 5 us.
 *
 * \details 
 * Time = 4**(EEE_TIMER_HOLDOFF/16) * (EEE_TIMER_HOLDOFF mod 16)
 * microseconds
 *
 * Field: ::VTSS_DEV10G_EEE_CFG . EEE_TIMER_HOLDOFF
 */
#define  VTSS_F_DEV10G_EEE_CFG_EEE_TIMER_HOLDOFF(x)  VTSS_ENCODE_BITFIELD(x,1,7)
#define  VTSS_M_DEV10G_EEE_CFG_EEE_TIMER_HOLDOFF     VTSS_ENCODE_BITMASK(1,7)
#define  VTSS_X_DEV10G_EEE_CFG_EEE_TIMER_HOLDOFF(x)  VTSS_EXTRACT_BITFIELD(x,1,7)

/** 
 * \brief
 * Status bit indicating whether port is in low-power-idle due to the LPI
 * algorithm (EEE_CFG). If set, transmissions are held back.
 *
 * \details 
 * Field: ::VTSS_DEV10G_EEE_CFG . PORT_LPI
 */
#define  VTSS_F_DEV10G_EEE_CFG_PORT_LPI(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_EEE_CFG_PORT_LPI       VTSS_BIT(0)
#define  VTSS_X_DEV10G_EEE_CFG_PORT_LPI(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Selects mode for which status counter will count the corresponding frames on RX and TX
 *
 * \details
 * Register: \a DEV10G:DEV_CFG_STATUS:PFC_PAUSE_MODE_CTRL
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PFC_PAUSE_MODE_CTRL(target)  VTSS_IOREG(target,0x79)

/** 
 * \brief
 * '0' : counters will be having number of pause frame
 * received/transmitted'1' : counters will be having number of PFC frame
 * received/transmitted
 *
 * \details 
 * Field: ::VTSS_DEV10G_PFC_PAUSE_MODE_CTRL . PFC_PAUSE_MODE_SELECT
 */
#define  VTSS_F_DEV10G_PFC_PAUSE_MODE_CTRL_PFC_PAUSE_MODE_SELECT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_PFC_PAUSE_MODE_CTRL_PFC_PAUSE_MODE_SELECT  VTSS_BIT(0)
#define  VTSS_X_DEV10G_PFC_PAUSE_MODE_CTRL_PFC_PAUSE_MODE_SELECT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a DEV10G:PCS25G_CFG_STATUS
 *
 * PCS25G Wrapper Config and Status registers
 */


/** 
 * \brief PCS25G enable Configuration
 *
 * \details
 * Register: \a DEV10G:PCS25G_CFG_STATUS:PCS25G_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PCS25G_CFG(target)       VTSS_IOREG(target,0x7a)

/** 
 * \brief
 * Global PCS Enable/Disable configuration bit.
 *
 * \details 
 * 0 = Disable PCS
 * 1 = Enable PCS
 *
 * Field: ::VTSS_DEV10G_PCS25G_CFG . PCS25G_ENA
 */
#define  VTSS_F_DEV10G_PCS25G_CFG_PCS25G_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_PCS25G_CFG_PCS25G_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV10G_PCS25G_CFG_PCS25G_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCS SignalDetect Configuration
 *
 * \details
 * PCS signal_detect configuration
 *
 * Register: \a DEV10G:PCS25G_CFG_STATUS:PCS25G_SD_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PCS25G_SD_CFG(target)    VTSS_IOREG(target,0x7b)

/** 
 * \brief
 * Signal detect selection (select input for internal signal_detect line)
 *
 * \details 
 * 0: Select signal_detect line from hardmacro
 * 1: Select external signal_detect line
 *
 * Field: ::VTSS_DEV10G_PCS25G_SD_CFG . SD_SEL
 */
#define  VTSS_F_DEV10G_PCS25G_SD_CFG_SD_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV10G_PCS25G_SD_CFG_SD_SEL   VTSS_BIT(8)
#define  VTSS_X_DEV10G_PCS25G_SD_CFG_SD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Signal detect polarity: The signal level on signal_detect input pin must
 * be equal to SD_POL to indicate signal detection (SD_ENA must be set)
 *
 * \details 
 * 0: Signal Detect input pin must be '0' to indicate a signal detection
 * 1: Signal Detect input pin must be '1' to indicate a signal detection
 *
 * Field: ::VTSS_DEV10G_PCS25G_SD_CFG . SD_POL
 */
#define  VTSS_F_DEV10G_PCS25G_SD_CFG_SD_POL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_PCS25G_SD_CFG_SD_POL   VTSS_BIT(4)
#define  VTSS_X_DEV10G_PCS25G_SD_CFG_SD_POL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Signal Detect Enable
 *
 * \details 
 * 0: The Signal Detect input pin is ignored. The PCS assumes an active
 * Signal Detect at all times
 * 1: The Signal Detect input pin is used to determine if a signal is
 * detected
 *
 * Field: ::VTSS_DEV10G_PCS25G_SD_CFG . SD_ENA
 */
#define  VTSS_F_DEV10G_PCS25G_SD_CFG_SD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_PCS25G_SD_CFG_SD_ENA   VTSS_BIT(0)
#define  VTSS_X_DEV10G_PCS25G_SD_CFG_SD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Receive PCS Status
 *
 * \details
 * Register: \a DEV10G:PCS25G_CFG_STATUS:PCS25G_STATUS
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PCS25G_STATUS(target)    VTSS_IOREG(target,0x7c)

/** 
 * \brief
 * Alignment Marker Lock indication. When asserted (1) the alignment marker
 * lock state machines could successfully lock onto detection of alignment
 * markers on all virtual lanes. The signal stays asserted as long as
 * alignment marker lock is maintained.Relevant only when MLD mode of
 * operation is active (i.e. using RS-FEC).
 *
 * \details 
 * 0 - Alignment lock is achieved
 * 1 - Alignment lock is not achieved
 *
 * Field: ::VTSS_DEV10G_PCS25G_STATUS . ALIGN_DONE
 */
#define  VTSS_F_DEV10G_PCS25G_STATUS_ALIGN_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_PCS25G_STATUS_ALIGN_DONE  VTSS_BIT(0)
#define  VTSS_X_DEV10G_PCS25G_STATUS_ALIGN_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * 66b Block synchronization indication. When asserted (1) the block
 * synchronization state machines could successfully lock onto 66-bit block
 * boundaries. The signal stays asserted as long as block lock is
 * maintained.Relevant only when MLD is not used (i.e. not using RS-FEC).
 *
 * \details 
 * 0 - Block lock is achieved
 * 1 - Block lock is not achieved
 *
 * Field: ::VTSS_DEV10G_PCS25G_STATUS . BLOCK_LOCK
 */
#define  VTSS_F_DEV10G_PCS25G_STATUS_BLOCK_LOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV10G_PCS25G_STATUS_BLOCK_LOCK  VTSS_BIT(1)
#define  VTSS_X_DEV10G_PCS25G_STATUS_BLOCK_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * High Bit Error Rate indication for all lanes. If asserted sync header
 * errors exceeding the allowed maximum during the measurement time
 * (125 1.25ms) have occurred indicating a high bit error rate from the
 * line.As long as hi_ber stays asserted, local fault is signaled on
 * XGMII.hi_ber deasserts again when the bit error rate falls below the
 * limit again.
 *
 * \details 
 * 0 - HI BER is not asserted.
 * 1 - HI BER is asserted.
 *
 * Field: ::VTSS_DEV10G_PCS25G_STATUS . HI_BER
 */
#define  VTSS_F_DEV10G_PCS25G_STATUS_HI_BER(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV10G_PCS25G_STATUS_HI_BER   VTSS_BIT(2)
#define  VTSS_X_DEV10G_PCS25G_STATUS_HI_BER(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


/** 
 * \brief Forward Error correction (FEC clause 74) configuration
 *
 * \details
 * Register: \a DEV10G:PCS25G_CFG_STATUS:PCS25G_FEC74_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PCS25G_FEC74_CFG(target)  VTSS_IOREG(target,0x7d)

/** 
 * \brief
 * If set to 1, FEC encapsulation is enabled on the receive lane.
 *
 * \details 
 * Field: ::VTSS_DEV10G_PCS25G_FEC74_CFG . FEC74_ENA_RX
 */
#define  VTSS_F_DEV10G_PCS25G_FEC74_CFG_FEC74_ENA_RX(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_PCS25G_FEC74_CFG_FEC74_ENA_RX  VTSS_BIT(0)
#define  VTSS_X_DEV10G_PCS25G_FEC74_CFG_FEC74_ENA_RX(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * If set to 1, FEC encapsulation is enabled on the transmit lane.
 *
 * \details 
 * Field: ::VTSS_DEV10G_PCS25G_FEC74_CFG . FEC74_ENA_TX
 */
#define  VTSS_F_DEV10G_PCS25G_FEC74_CFG_FEC74_ENA_TX(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV10G_PCS25G_FEC74_CFG_FEC74_ENA_TX  VTSS_BIT(1)
#define  VTSS_X_DEV10G_PCS25G_FEC74_CFG_FEC74_ENA_TX(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * FEC module optional function to forward indication of uncorrectable
 * errors to the PCS layer by corrupting sync headers.
 *
 * \details 
 * Field: ::VTSS_DEV10G_PCS25G_FEC74_CFG . FEC74_ERR_ENA
 */
#define  VTSS_F_DEV10G_PCS25G_FEC74_CFG_FEC74_ERR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV10G_PCS25G_FEC74_CFG_FEC74_ERR_ENA  VTSS_BIT(2)
#define  VTSS_X_DEV10G_PCS25G_FEC74_CFG_FEC74_ERR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


/** 
 * \brief Forward Error correction (FEC clause 74) Status
 *
 * \details
 * Register: \a DEV10G:PCS25G_CFG_STATUS:PCS25G_FEC74_STATUS
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PCS25G_FEC74_STATUS(target)  VTSS_IOREG(target,0x7e)

/** 
 * \brief
 * Indication that FEC has achieved lock on the FEC block boundaries and
 * valid data is being decoded.
 *
 * \details 
 * Field: ::VTSS_DEV10G_PCS25G_FEC74_STATUS . FEC74_LOCKED
 */
#define  VTSS_F_DEV10G_PCS25G_FEC74_STATUS_FEC74_LOCKED(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_PCS25G_FEC74_STATUS_FEC74_LOCKED  VTSS_BIT(0)
#define  VTSS_X_DEV10G_PCS25G_FEC74_STATUS_FEC74_LOCKED(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief FEC74 correctable error counter
 *
 * \details
 * Register: \a DEV10G:PCS25G_CFG_STATUS:PCS25G_FEC74_CERR_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PCS25G_FEC74_CERR_CNT(target)  VTSS_IOREG(target,0x7f)

/** 
 * \brief
 * FEC corrected error counter. The FEC could detect and correct receive
 * errors in a block. The correctable error is counted max once per FEC
 * block (32 66-bit blocks). 
 *
 * \details 
 * Field: ::VTSS_DEV10G_PCS25G_FEC74_CERR_CNT . FEC74_CERR_CNT
 */
#define  VTSS_F_DEV10G_PCS25G_FEC74_CERR_CNT_FEC74_CERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_PCS25G_FEC74_CERR_CNT_FEC74_CERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_PCS25G_FEC74_CERR_CNT_FEC74_CERR_CNT(x)  (x)


/** 
 * \brief FEC74 uncorrectable error counter
 *
 * \details
 * Register: \a DEV10G:PCS25G_CFG_STATUS:PCS25G_FEC74_NCERR_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PCS25G_FEC74_NCERR_CNT(target)  VTSS_IOREG(target,0x80)

/** 
 * \brief
 * FEC uncorrected error counter. The FEC could detect but could not
 * correct receive errors in a block. The uncorrectable error is counted
 * max once per FEC block (32 66-bit blocks).
 *
 * \details 
 * Field: ::VTSS_DEV10G_PCS25G_FEC74_NCERR_CNT . FEC74_NCERR_CNT
 */
#define  VTSS_F_DEV10G_PCS25G_FEC74_NCERR_CNT_FEC74_NCERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_PCS25G_FEC74_NCERR_CNT_FEC74_NCERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_PCS25G_FEC74_NCERR_CNT_FEC74_NCERR_CNT(x)  (x)


/** 
 * \brief RSFEC datapath Config
 *
 * \details
 * Register: \a DEV10G:PCS25G_CFG_STATUS:PCS25G_RSFEC_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PCS25G_RSFEC_CFG(target)  VTSS_IOREG(target,0x81)

/** 
 * \brief
 * Enable RS-FEC datapath. The input is OR'ed with the RS FEC VENDOR
 * CONTROL register bit 2.
 *
 * \details 
 * Field: ::VTSS_DEV10G_PCS25G_RSFEC_CFG . FEC91_ENA
 */
#define  VTSS_F_DEV10G_PCS25G_RSFEC_CFG_FEC91_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_PCS25G_RSFEC_CFG_FEC91_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV10G_PCS25G_RSFEC_CFG_FEC91_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * The 25G PCS implementation does not perform compensation for the
 * inserted alignment markers. Enabling this bit would perform rate
 * compensation. This should be enabled when FEC91 is enabled.Note:
 * Codeword Marker Insertion is identical to Alignment Marker Insertion in
 * Multi-Lane Distribution(MLD) using four marker patterns and internally
 * assuming calculations for the marker interval as if usingfour virtual
 * lanes, as used in 40G Clause 82.
 *
 * \details 
 * Field: ::VTSS_DEV10G_PCS25G_RSFEC_CFG . FEC91_RADAPT_ENA
 */
#define  VTSS_F_DEV10G_PCS25G_RSFEC_CFG_FEC91_RADAPT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV10G_PCS25G_RSFEC_CFG_FEC91_RADAPT_ENA  VTSS_BIT(1)
#define  VTSS_X_DEV10G_PCS25G_RSFEC_CFG_FEC91_RADAPT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * Register Group: \a DEV10G:MM_CONFIG
 *
 * Configuration of Mac Merge block for this port
 */


/** 
 * \brief Enables the MAC Merge layer for this port
 *
 * \details
 * Register: \a DEV10G:MM_CONFIG:ENABLE_CONFIG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_ENABLE_CONFIG(target)    VTSS_IOREG(target,0x82)

/** 
 * \brief
 * Enable the MAC-MERGE Layer Receive block.
 *
 * \details 
 * 0: MAC Merge Receive block is not enabled. The input of MAC Merge RX is
 * directly given to its output.
 * 1: MAC Merge receive block is enabled, and the incoming frame is
 * processed as per 802.3br

 *
 * Field: ::VTSS_DEV10G_ENABLE_CONFIG . MM_RX_ENA
 */
#define  VTSS_F_DEV10G_ENABLE_CONFIG_MM_RX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_ENABLE_CONFIG_MM_RX_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV10G_ENABLE_CONFIG_MM_RX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Enable the MAC-MERGE Layer Transmit block.
 *
 * \details 
 * 0: MAC Merge Transmit block is not enabled. The input of MAC Merge TX is
 * directly given to its output.
 * 1: MAC Merge Transmit block is enabled, and the incoming frame is
 * processed as per 802.3br

 *
 * Field: ::VTSS_DEV10G_ENABLE_CONFIG . MM_TX_ENA
 */
#define  VTSS_F_DEV10G_ENABLE_CONFIG_MM_TX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_ENABLE_CONFIG_MM_TX_ENA  VTSS_BIT(4)
#define  VTSS_X_DEV10G_ENABLE_CONFIG_MM_TX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Process the start of a new Packet while discarding previously received
 * MAC_Merge layer error packet.Note: In any case, the first frame for
 * which SMD-C was missing, is discarded.
 *
 * \details 
 * '1': The second frame with SMD-S that was received while MM receiver was
 * waiting for SMD-C will be processed.
 * '0': The second frame with SMD-S that was received while MM receiver was
 * waiting for SMD-C will be discarded.

 *
 * Field: ::VTSS_DEV10G_ENABLE_CONFIG . KEEP_S_AFTER_D
 */
#define  VTSS_F_DEV10G_ENABLE_CONFIG_KEEP_S_AFTER_D(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV10G_ENABLE_CONFIG_KEEP_S_AFTER_D  VTSS_BIT(8)
#define  VTSS_X_DEV10G_ENABLE_CONFIG_KEEP_S_AFTER_D(x)  VTSS_EXTRACT_BITFIELD(x,8,1)


/** 
 * \brief Configuration to control the Preemption Verification-Response behavior of port.
 *
 * \details
 * Register: \a DEV10G:MM_CONFIG:VERIF_CONFIG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_VERIF_CONFIG(target)     VTSS_IOREG(target,0x83)

/** 
 * \brief
 * Disables the verification of preemption capabilities of link partner.
 *
 * \details 
 * '0' - Verification process has to be finished before a port can support
 * preemption.
 * '1' - Disable verification process (i.e., that preemption verification
 * process need not be peformed).

 *
 * Field: ::VTSS_DEV10G_VERIF_CONFIG . PRM_VERIFY_DIS
 */
#define  VTSS_F_DEV10G_VERIF_CONFIG_PRM_VERIFY_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_VERIF_CONFIG_PRM_VERIFY_DIS  VTSS_BIT(0)
#define  VTSS_X_DEV10G_VERIF_CONFIG_PRM_VERIFY_DIS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * This field configures the wait time between verification attempts to be
 * initiated by this port in milli seconds.Valid range of values is from 1
 * to 128.
 *
 * \details 
 * Valid values are from 1 to 128.
 * 1 = Wait for 1 ms before initiating verification frame transmission.
 * 2 = Wait for 2 ms before initiating verification frame transmission and
 * so on.
 *
 * Field: ::VTSS_DEV10G_VERIF_CONFIG . PRM_VERIFY_TIME
 */
#define  VTSS_F_DEV10G_VERIF_CONFIG_PRM_VERIFY_TIME(x)  VTSS_ENCODE_BITFIELD(x,4,8)
#define  VTSS_M_DEV10G_VERIF_CONFIG_PRM_VERIFY_TIME     VTSS_ENCODE_BITMASK(4,8)
#define  VTSS_X_DEV10G_VERIF_CONFIG_PRM_VERIFY_TIME(x)  VTSS_EXTRACT_BITFIELD(x,4,8)

/** 
 * \brief
 * Sets the unit of PRM_VERIFY_TIME register to one of below:0 :
 * denomination of 1 ms (Default) at 1G/100M/10M speeds1 : denomination of
 * 1040 ns = 1.04 us at 1G/100M/10M speeds2 : denomination of 1 ms time at
 * 2.5G speeds3 : denomination of 1001.6ns = 1.0016 us time at 2.5G
 * speedsThe actual timer value is PRM_VERIFY_TIME * (decoded FAST_TIMER
 * denomination).Denomination of 1.04 is used so as to be multiplied by 80
 * ns(80 * 13 = 1040).The denominations of 2, 3 are supposed to be used for
 * 2.5G speeds. And here, 1.0016us is used because 3.2*313 = 1001.6us
 *
 * \details 
 * 0 : denomination of 1 ms (Default) at 1G/100M/10M speeds
 * 1 : denomination of 1040 ns = 1.04 us at 1G/100M/10M speeds
 * 2 : denomination of 1 ms time at 2.5G speeds
 * 3 : denomination of 1001.6ns = 1.0016 us time at 2.5G speeds
 *
 * Field: ::VTSS_DEV10G_VERIF_CONFIG . VERIF_TIMER_UNITS
 */
#define  VTSS_F_DEV10G_VERIF_CONFIG_VERIF_TIMER_UNITS(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_DEV10G_VERIF_CONFIG_VERIF_TIMER_UNITS     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_DEV10G_VERIF_CONFIG_VERIF_TIMER_UNITS(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * Register Group: \a DEV10G:MM_STATISTICS
 *
 * Statistics for MAC Merge Layer
 */


/** 
 * \brief Status of MAC Merge layer of this port.
 *
 * \details
 * Register: \a DEV10G:MM_STATISTICS:MM_STATUS
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MM_STATUS(target)        VTSS_IOREG(target,0x84)

/** 
 * \brief
 * Status bit indicating that preemption is currently active on this
 * port.Note: Preemption is active if:a) preemption is enabled on that port
 * ANDb) (preemption capabilities have been verified OR preemption
 * verification has been disabled on that port).
 *
 * \details 
 * '1' - Preemption is currently active on this port.
 * '0' - Preemption is not currently active.

 *
 * Field: ::VTSS_DEV10G_MM_STATUS . PRMPT_ACTIVE_STATUS
 */
#define  VTSS_F_DEV10G_MM_STATUS_PRMPT_ACTIVE_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_MM_STATUS_PRMPT_ACTIVE_STATUS  VTSS_BIT(0)
#define  VTSS_X_DEV10G_MM_STATUS_PRMPT_ACTIVE_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * A sticky bit indicating there was a change in prmption state of this
 * port.Application layer should use this interrupt bit to identify the
 * change in prmpt_active_status and appropriately program prempt_queues in
 * qsys block.
 *
 * \details 
 * Field: ::VTSS_DEV10G_MM_STATUS . PRMPT_ACTIVE_STICKY
 */
#define  VTSS_F_DEV10G_MM_STATUS_PRMPT_ACTIVE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_MM_STATUS_PRMPT_ACTIVE_STICKY  VTSS_BIT(4)
#define  VTSS_X_DEV10G_MM_STATUS_PRMPT_ACTIVE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Status of MAC Merge sub-layer verification on the given port.
 *
 * \details 
 * 0 : Initial- the verify state diagram is in the INIT_VERIFICATION state.
 * 1 : Verifying (indicates that verify state diagram is in state
 * VERIFICATION_IDLE, SEND_VERIFY or WAIT_FOR_RESPONSE).
 * 2 : Verification successful (indicates that the verify state diagram is
 * in state VERIFIED)
 * 3 : Verification failed (indicates that the verify state diagram is in
 * state VERIFY_FAIL).
 * 4 : Verification process is Disabled.

 *
 * Field: ::VTSS_DEV10G_MM_STATUS . PRMPT_VERIFY_STATE
 */
#define  VTSS_F_DEV10G_MM_STATUS_PRMPT_VERIFY_STATE(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_DEV10G_MM_STATUS_PRMPT_VERIFY_STATE     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_DEV10G_MM_STATUS_PRMPT_VERIFY_STATE(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/** 
 * \brief
 * Sticky bit indicating that an unexpected P-Frame has been received by
 * the port when the preemption verification is unsuccessful or not yet
 * verified.
 *
 * \details 
 * 1 - Received a P-Frame when the preemption capabilities of the port are
 * yet to be verified or not yet verified.
 * 0 - No invalid p-frm received.
 * Write '1' to clear.
 *
 * Field: ::VTSS_DEV10G_MM_STATUS . UNEXP_RX_PFRM_STICKY
 */
#define  VTSS_F_DEV10G_MM_STATUS_UNEXP_RX_PFRM_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DEV10G_MM_STATUS_UNEXP_RX_PFRM_STICKY  VTSS_BIT(12)
#define  VTSS_X_DEV10G_MM_STATUS_UNEXP_RX_PFRM_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Sticky bit indicating that a P-Fragment was requested to be transmitted
 * when the preemption verification is unsuccessful or not yet verified or
 * when MM_TX_ENA = 0. Request is ignored and data will be processed using
 * PREEMPTABLE_TX state and never getting preempted.
 *
 * \details 
 * 1 - Request to transmit a P-Frame when preemption capabilities are yet
 * to be verified or when MM_TX_ENA = 0.
 * 0 - No invalid p-frm received.
 * Write '1' to clear.
 *
 * Field: ::VTSS_DEV10G_MM_STATUS . UNEXP_TX_PFRM_STICKY
 */
#define  VTSS_F_DEV10G_MM_STATUS_UNEXP_TX_PFRM_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DEV10G_MM_STATUS_UNEXP_TX_PFRM_STICKY  VTSS_BIT(16)
#define  VTSS_X_DEV10G_MM_STATUS_UNEXP_TX_PFRM_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Status bit indicating if the last received frame by MM was delivered to
 * P-MAC.'1' - Last received complete frame (not fragment) by MM was
 * delivered to P-MAC.'0' - Last received frame by MM was delivered to
 * E-MAC.Note: When MM is not enabled, then frames are delivered to E-MAC.
 *
 * \details 
 * '1' - Last received complete frame (not fragment) by MM was delivered to
 * P-MAC.
 * '0' - Last received frame by MM was delivered to E-MAC.
 *
 * Field: ::VTSS_DEV10G_MM_STATUS . MM_RX_FRAME_STATUS
 */
#define  VTSS_F_DEV10G_MM_STATUS_MM_RX_FRAME_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_DEV10G_MM_STATUS_MM_RX_FRAME_STATUS  VTSS_BIT(20)
#define  VTSS_X_DEV10G_MM_STATUS_MM_RX_FRAME_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Status bit indicating if the last transmitted frame by MM was from a
 * P-MAC.'1' - Last transmitted complete frame (not fragment) by MM was
 * from P-MAC.'0' - Last transmitted frame by MM was from E-MAC.Note: If
 * preemption is not enabled in switch, frames would be processed as
 * E-Frames.
 *
 * \details 
 * '1' - Last transmitted complete frame (not fragment) by MM was from
 * P-MAC.
 * '0' - Last transmitted frame by MM was from E-MAC.

 *
 * Field: ::VTSS_DEV10G_MM_STATUS . MM_TX_FRAME_STATUS
 */
#define  VTSS_F_DEV10G_MM_STATUS_MM_TX_FRAME_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_DEV10G_MM_STATUS_MM_TX_FRAME_STATUS  VTSS_BIT(24)
#define  VTSS_X_DEV10G_MM_STATUS_MM_TX_FRAME_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * Status bit indicating when a preemptable packet is to be preempted. '1'
 * : A P-frame is being preempted from this MM TX MAC.'0' : No P-frames are
 * preempted because of no requests from E-MAC and because of min_frag_size
 * check and because of no hold requests.
 *
 * \details 
 * Field: ::VTSS_DEV10G_MM_STATUS . MM_TX_PRMPT_STATUS
 */
#define  VTSS_F_DEV10G_MM_STATUS_MM_TX_PRMPT_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_DEV10G_MM_STATUS_MM_TX_PRMPT_STATUS  VTSS_BIT(28)
#define  VTSS_X_DEV10G_MM_STATUS_MM_TX_PRMPT_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * Register Group: \a DEV10G:USXGMII_ANEG_CFG_STATUS
 *
 * USXGMII ANEG Configuration Status Registers
 */


/** 
 * \brief USXGMII ANEG Configuration
 *
 * \details
 * USXGMII Auto-Negotiation configuration register
 *
 * Register: \a DEV10G:USXGMII_ANEG_CFG_STATUS:USXGMII_ANEG_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_USXGMII_ANEG_CFG(target)  VTSS_IOREG(target,0x85)

/** 
 * \brief
 * MAC UsxgmiiChannelInfo: Holds the 16-bit Usxgmii Channel Information
 * that needs to be advertised to PHY
 *
 * \details 
 * Field: ::VTSS_DEV10G_USXGMII_ANEG_CFG . ADV_ABILITY
 */
#define  VTSS_F_DEV10G_USXGMII_ANEG_CFG_ADV_ABILITY(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DEV10G_USXGMII_ANEG_CFG_ADV_ABILITY     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DEV10G_USXGMII_ANEG_CFG_ADV_ABILITY(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Specifies the Link Timer Value in duration corresponding to multiples of
 * 256 datapath clock cycles. A configuration value of 0 is invalid.  A
 * value of 1 indicates 256 Datapath clock cycles i.e.	      for a data
 * path clock frequency of 161MHz(6.2ns)   the Link timer value would be
 * 1x256x6.2ns	 = ~1.6us	for a data path clock frequency of  
 * 80MHz(12.4ns) the Link timer value would be 1x256x12.4ns = ~3.2usA value
 * of 0xFFF(4095) indicates 4095 x 256 Datapath clock cycles i.e.	
 * for a data path clock frequency of 161MHz(6.2ns)   the Link timer value
 * would be 4095x256x6.2ns   = ~6.5ms	    for a data path clock frequency
 * of	80MHz(12.4ns) the Link timer value would be 4095x256x12.4ns =
 * ~13msThe clock frequency used is unpaused clock frequency i.e. paused
 * clocks are also counted for the 256 clock count.This configuration is
 * supposed to set/changed before the ANEG is enabled or restarted.
 *
 * \details 
 * 0: Reserved
 * 1	   : 1 x 256 x Datapath clock cycle duration.
 * 2	   : 2 x 256 x Datapath clock cycle duration
 * 3	   : 3 x 256 x Datapath clock cycle duration
 * ...
 * 4094 : 4094 * 256 * Datapath clock cycle duration
 * 4095 : 4095 * 256 * Datapath clock cycle duration
 *
 * Field: ::VTSS_DEV10G_USXGMII_ANEG_CFG . LINK_TIMER
 */
#define  VTSS_F_DEV10G_USXGMII_ANEG_CFG_LINK_TIMER(x)  VTSS_ENCODE_BITFIELD(x,4,12)
#define  VTSS_M_DEV10G_USXGMII_ANEG_CFG_LINK_TIMER     VTSS_ENCODE_BITMASK(4,12)
#define  VTSS_X_DEV10G_USXGMII_ANEG_CFG_LINK_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,4,12)

/** 
 * \brief
 * Software Resolve Abilities
 *
 * \details 
 * 0: If Auto Negotiation fails (no matching HD or FD capabilities) the
 * link is disabled
 * 1: The result of an Auto Negotiation is ignored - the link can be setup
 * via software. This bit must be set in SGMII mode.
 *
 * Field: ::VTSS_DEV10G_USXGMII_ANEG_CFG . SW_RESOLVE_ENA
 */
#define  VTSS_F_DEV10G_USXGMII_ANEG_CFG_SW_RESOLVE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV10G_USXGMII_ANEG_CFG_SW_RESOLVE_ENA  VTSS_BIT(3)
#define  VTSS_X_DEV10G_USXGMII_ANEG_CFG_SW_RESOLVE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Block Lock Hysteresis Enable. This is a configuration to control the
 * an_sync_status of USXGMII ANEG w.r.t. block lock. Setting this bit will
 * set an_sync_status to fail link_timer duration after the block_lock is
 * set to false. If the bit is cleared, loss of block lock will set
 * an_sync_status to fail causing an autoneg restart as is mentioned in
 * USXGMII Specification.
 *
 * \details 
 * 1: an_sync_status is cleared after link timer duration of block_lock = 0
 * 0: an_sync_status is cleared immediately after block_lock = 0
 *
 * Field: ::VTSS_DEV10G_USXGMII_ANEG_CFG . BLK_LCK_HYS_ENA
 */
#define  VTSS_F_DEV10G_USXGMII_ANEG_CFG_BLK_LCK_HYS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV10G_USXGMII_ANEG_CFG_BLK_LCK_HYS_ENA  VTSS_BIT(2)
#define  VTSS_X_DEV10G_USXGMII_ANEG_CFG_BLK_LCK_HYS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Auto Negotiation Restart
 *
 * \details 
 * 0: No action
 * 1: Restart Auto Negotiation
 *
 * Field: ::VTSS_DEV10G_USXGMII_ANEG_CFG . ANEG_RESTART_ONE_SHOT
 */
#define  VTSS_F_DEV10G_USXGMII_ANEG_CFG_ANEG_RESTART_ONE_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV10G_USXGMII_ANEG_CFG_ANEG_RESTART_ONE_SHOT  VTSS_BIT(1)
#define  VTSS_X_DEV10G_USXGMII_ANEG_CFG_ANEG_RESTART_ONE_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Auto Negotiation Enable
 *
 * \details 
 * 0: Auto Negotiation Disabled
 * 1: Auto Negotiation Enabled
 *
 * Field: ::VTSS_DEV10G_USXGMII_ANEG_CFG . ANEG_ENA
 */
#define  VTSS_F_DEV10G_USXGMII_ANEG_CFG_ANEG_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_USXGMII_ANEG_CFG_ANEG_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV10G_USXGMII_ANEG_CFG_ANEG_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief USXGMII ANEG Status
 *
 * \details
 * USXGMII Auto-negotiation status register
 *
 * Register: \a DEV10G:USXGMII_ANEG_CFG_STATUS:USXGMII_ANEG_STATUS
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_USXGMII_ANEG_STATUS(target)  VTSS_IOREG(target,0x86)

/** 
 * \brief
 * PHY UsxgmiiChannelInfo: Holds the 16-bit Usxgmii Channel Information
 * received from PHY
 *
 * \details 
 * Field: ::VTSS_DEV10G_USXGMII_ANEG_STATUS . LP_ADV_ABILITY
 */
#define  VTSS_F_DEV10G_USXGMII_ANEG_STATUS_LP_ADV_ABILITY(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DEV10G_USXGMII_ANEG_STATUS_LP_ADV_ABILITY     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DEV10G_USXGMII_ANEG_STATUS_LP_ADV_ABILITY(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * USXGMII ANEG Link down status from Aneg State Machine.
 *
 * \details 
 * 0: Link is up
 * 1: Link is down

 *
 * Field: ::VTSS_DEV10G_USXGMII_ANEG_STATUS . LINK_DOWN_STATUS
 */
#define  VTSS_F_DEV10G_USXGMII_ANEG_STATUS_LINK_DOWN_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DEV10G_USXGMII_ANEG_STATUS_LINK_DOWN_STATUS  VTSS_BIT(5)
#define  VTSS_X_DEV10G_USXGMII_ANEG_STATUS_LINK_DOWN_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Sticky bit indicating whether a new page has been received.
 *
 * \details 
 * 0 : No new page received.
 * 1 : New page received.
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_DEV10G_USXGMII_ANEG_STATUS . PAGE_RX_STICKY
 */
#define  VTSS_F_DEV10G_USXGMII_ANEG_STATUS_PAGE_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_USXGMII_ANEG_STATUS_PAGE_RX_STICKY  VTSS_BIT(4)
#define  VTSS_X_DEV10G_USXGMII_ANEG_STATUS_PAGE_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Resolve priority
 *
 * \details 
 * 0: ANEG is in progress
 * 1: ANEG nearly finished - priority can be resolved (via software)
 *
 * Field: ::VTSS_DEV10G_USXGMII_ANEG_STATUS . PR
 */
#define  VTSS_F_DEV10G_USXGMII_ANEG_STATUS_PR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV10G_USXGMII_ANEG_STATUS_PR  VTSS_BIT(2)
#define  VTSS_X_DEV10G_USXGMII_ANEG_STATUS_PR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Auto Negotiation Complete
 *
 * \details 
 * 0: No Auto Negotiation has been completed
 * 1: Indicates that an Auto Negotiation has completed successfully
 *
 * Field: ::VTSS_DEV10G_USXGMII_ANEG_STATUS . ANEG_COMPLETE
 */
#define  VTSS_F_DEV10G_USXGMII_ANEG_STATUS_ANEG_COMPLETE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_USXGMII_ANEG_STATUS_ANEG_COMPLETE  VTSS_BIT(0)
#define  VTSS_X_DEV10G_USXGMII_ANEG_STATUS_ANEG_COMPLETE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief USXGMII PCS Signal Detect Configuration
 *
 * \details
 * USXGMII PCS Signal Detect Configuration
 *
 * Register: \a DEV10G:USXGMII_ANEG_CFG_STATUS:USXGMII_PCS_SD_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_USXGMII_PCS_SD_CFG(target)  VTSS_IOREG(target,0x87)

/** 
 * \brief
 * Signal detect polarity: The signal level on signal_detect input pin must
 * be equal to SD_POL to indicate signal detection (SD_ENA must be set)
 *
 * \details 
 * 0: Signal Detect input pin must be '0' to indicate a signal detection
 * 1: Signal Detect input pin must be '1' to indicate a signal detection
 *
 * Field: ::VTSS_DEV10G_USXGMII_PCS_SD_CFG . SD_POL
 */
#define  VTSS_F_DEV10G_USXGMII_PCS_SD_CFG_SD_POL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV10G_USXGMII_PCS_SD_CFG_SD_POL  VTSS_BIT(1)
#define  VTSS_X_DEV10G_USXGMII_PCS_SD_CFG_SD_POL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Signal Detect Enable
 *
 * \details 
 * 0: The Signal Detect input pin is ignored. The PCS assumes an active
 * Signal Detect at all times
 * 1: The Signal Detect input pin is used to determine if a signal is
 * detected
 *
 * Field: ::VTSS_DEV10G_USXGMII_PCS_SD_CFG . SD_ENA
 */
#define  VTSS_F_DEV10G_USXGMII_PCS_SD_CFG_SD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_USXGMII_PCS_SD_CFG_SD_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV10G_USXGMII_PCS_SD_CFG_SD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief USXGMII PCS status register
 *
 * \details
 * USXGMII PCS status register
 *
 * Register: \a DEV10G:USXGMII_ANEG_CFG_STATUS:USXGMII_PCS_STATUS
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_USXGMII_PCS_STATUS(target)  VTSS_IOREG(target,0x88)

/** 
 * \brief
 * Indicates if USXGMII PCS has reached block lock state
 *
 * \details 
 * 0: USXGMII PCS is not in block lock state,
 * 1: USXGMII PCS is in block lock state
 *
 * Field: ::VTSS_DEV10G_USXGMII_PCS_STATUS . USXGMII_BLOCK_LOCK
 */
#define  VTSS_F_DEV10G_USXGMII_PCS_STATUS_USXGMII_BLOCK_LOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_USXGMII_PCS_STATUS_USXGMII_BLOCK_LOCK  VTSS_BIT(0)
#define  VTSS_X_DEV10G_USXGMII_PCS_STATUS_USXGMII_BLOCK_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a DEV10G:PTP_CFG_STATUS
 *
 * Dev1g Configuration and Status Registers
 */


/** 
 * \brief PTP Configuration per port
 *
 * \details
 * Register: \a DEV10G:PTP_CFG_STATUS:PTP_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PTP_CFG(target)          VTSS_IOREG(target,0x89)

/** 
 * \brief
 * PCH Header Sub-portID. Inserted Tx direction. Checked in Rx direction.
 *
 * \details 
 * Field: ::VTSS_DEV10G_PTP_CFG . PCH_SUB_PORT_ID
 */
#define  VTSS_F_DEV10G_PTP_CFG_PCH_SUB_PORT_ID(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DEV10G_PTP_CFG_PCH_SUB_PORT_ID     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DEV10G_PTP_CFG_PCH_SUB_PORT_ID(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Enable PTP rewriting on the port.
 *
 * \details 
 * Field: ::VTSS_DEV10G_PTP_CFG . PTP_ENA
 */
#define  VTSS_F_DEV10G_PTP_CFG_PTP_ENA(x)     VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DEV10G_PTP_CFG_PTP_ENA        VTSS_BIT(7)
#define  VTSS_X_DEV10G_PTP_CFG_PTP_ENA(x)     VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Configures the time domain this port is assigned to. This domain
 * assignment must be made before the central counters in DEVCPU block is
 * enabled.
 *
 * \details 
 * Field: ::VTSS_DEV10G_PTP_CFG . PTP_DOM
 */
#define  VTSS_F_DEV10G_PTP_CFG_PTP_DOM(x)     VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_DEV10G_PTP_CFG_PTP_DOM        VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_DEV10G_PTP_CFG_PTP_DOM(x)     VTSS_EXTRACT_BITFIELD(x,5,2)

/** 
 * \brief
 * Enable insertion of PCH in preamble on the port
 *
 * \details 
 * 00: No PCH in transmitted frames
 * 01: PCH added on transmitted frames
 * 10: PCH added with encryption bit set
 * 11: PCH added with encryption bit set to inverted SMAC(40), which is
 * then cleared.#xD
 *
 * Field: ::VTSS_DEV10G_PTP_CFG . PTP_PCH_TX_ENA
 */
#define  VTSS_F_DEV10G_PTP_CFG_PTP_PCH_TX_ENA(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_DEV10G_PTP_CFG_PTP_PCH_TX_ENA     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_DEV10G_PTP_CFG_PTP_PCH_TX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * Set mode for ingress timestamps, in terms of nsec.subns bit widths.
 *
 * \details 
 * 000: No PCH expected
 * 001: 32.0 mode
 * 010: 28.4 mode
 * 011: 24.8 mode
 * 100: 16.16 mode
 * 101,110,111: Reserved
 *
 * Field: ::VTSS_DEV10G_PTP_CFG . PTP_PCH_RX_MODE
 */
#define  VTSS_F_DEV10G_PTP_CFG_PTP_PCH_RX_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_DEV10G_PTP_CFG_PTP_PCH_RX_MODE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_DEV10G_PTP_CFG_PTP_PCH_RX_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief PTP Configuration per port
 *
 * \details
 * Register: \a DEV10G:PTP_CFG_STATUS:PTP_RXDLY_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PTP_RXDLY_CFG(target)    VTSS_IOREG(target,0x8a)

/** 
 * \brief
 * Time in ns/256 to subtract from timestamper in the ingress direction to
 * compensate for static delay through the physical encoding layers.
 *
 * \details 
 * Field: ::VTSS_DEV10G_PTP_RXDLY_CFG . PTP_RX_IO_DLY
 */
#define  VTSS_F_DEV10G_PTP_RXDLY_CFG_PTP_RX_IO_DLY(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_DEV10G_PTP_RXDLY_CFG_PTP_RX_IO_DLY     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_DEV10G_PTP_RXDLY_CFG_PTP_RX_IO_DLY(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/** 
 * \brief PTP Configuration per port
 *
 * \details
 * Register: \a DEV10G:PTP_CFG_STATUS:PTP_TXDLY_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PTP_TXDLY_CFG(target)    VTSS_IOREG(target,0x8b)

/** 
 * \brief
 * Time in ns/256 to add to timestamper in the egress direction to
 * compensate for static delay through the physical encoding layers.
 *
 * \details 
 * Field: ::VTSS_DEV10G_PTP_TXDLY_CFG . PTP_TX_IO_DLY
 */
#define  VTSS_F_DEV10G_PTP_TXDLY_CFG_PTP_TX_IO_DLY(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_DEV10G_PTP_TXDLY_CFG_PTP_TX_IO_DLY     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_DEV10G_PTP_TXDLY_CFG_PTP_TX_IO_DLY(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/** 
 * \brief PTP Predictor Configuration per port
 *
 * \details
 * Register: \a DEV10G:PTP_CFG_STATUS:PTP_PREDICT_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PTP_PREDICT_CFG(target)  VTSS_IOREG(target,0x8c)

/** 
 * \brief
 * Enables increased accuracy in the time stamping logic, by finding the
 * dynamic phase between port and 1588 clocks.
 *
 * \details 
 * 0001: 125 MHz port clock
 * 0010:  25 MHz port clock
 * 0011:  2.5 MHz port clock
 * 0100:  161.13 MHz port clock
 * 0101:  156.25 MHz port clock
 * 0110:  312.5 MHz port clock
 * 0111:  80.566 port clock
 * others: Disabled
 *
 * Field: ::VTSS_DEV10G_PTP_PREDICT_CFG . PTP_PHASE_PREDICT_CFG
 */
#define  VTSS_F_DEV10G_PTP_PREDICT_CFG_PTP_PHASE_PREDICT_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DEV10G_PTP_PREDICT_CFG_PTP_PHASE_PREDICT_CFG     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DEV10G_PTP_PREDICT_CFG_PTP_PHASE_PREDICT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief PTP events per port
 *
 * \details
 * Register: \a DEV10G:PTP_CFG_STATUS:PTP_EVENTS
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_PTP_EVENTS(target)       VTSS_IOREG(target,0x8d)

/** 
 * \brief
 * An ingress PCH was received with a Sub-portID different than what is
 * configured in PTP_CFG.PCH_SUB_PORT_ID. Error also triggered if PktTy
 * isn't 0 or ExtTy isn't 1 
 *
 * \details 
 * Field: ::VTSS_DEV10G_PTP_EVENTS . PCH_SUB_PORT_ID_ERR_STICKY
 */
#define  VTSS_F_DEV10G_PTP_EVENTS_PCH_SUB_PORT_ID_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV10G_PTP_EVENTS_PCH_SUB_PORT_ID_ERR_STICKY  VTSS_BIT(2)
#define  VTSS_X_DEV10G_PTP_EVENTS_PCH_SUB_PORT_ID_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * The correction field update went out of range. Valid range is -2^47 to
 * 2^48-1. The frame CF will be changed to the maximum value. This range
 * check is bypassed if ADDS48 mode is in use on the ingress or egress
 * port.
 *
 * \details 
 * Field: ::VTSS_DEV10G_PTP_EVENTS . CF_TOO_BIG_STICKY
 */
#define  VTSS_F_DEV10G_PTP_EVENTS_CF_TOO_BIG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV10G_PTP_EVENTS_CF_TOO_BIG_STICKY  VTSS_BIT(1)
#define  VTSS_X_DEV10G_PTP_EVENTS_CF_TOO_BIG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * An ingress PCH was processed and failed the CRC8 checksum verification
 *
 * \details 
 * Field: ::VTSS_DEV10G_PTP_EVENTS . PCH_CRC_ERR_STICKY
 */
#define  VTSS_F_DEV10G_PTP_EVENTS_PCH_CRC_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_PTP_EVENTS_PCH_CRC_ERR_STICKY  VTSS_BIT(0)
#define  VTSS_X_DEV10G_PTP_EVENTS_PCH_CRC_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configures device transmission options
 *
 * \details
 * Register: \a DEV10G:PTP_CFG_STATUS:DEV_TX_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_TX_CFG(target)       VTSS_IOREG(target,0x8e)

/** 
 * \brief
 * Configures the minimum sof-sof delay for frames being transmitted on
 * this port. Unit is nano seconds. Cut through forwarded frames can be
 * transmitted with constant delay by proper configuration of this field.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_TX_CFG . DEV_TX_DLY
 */
#define  VTSS_F_DEV10G_DEV_TX_CFG_DEV_TX_DLY(x)  VTSS_ENCODE_BITFIELD(x,14,14)
#define  VTSS_M_DEV10G_DEV_TX_CFG_DEV_TX_DLY     VTSS_ENCODE_BITMASK(14,14)
#define  VTSS_X_DEV10G_DEV_TX_CFG_DEV_TX_DLY(x)  VTSS_EXTRACT_BITFIELD(x,14,14)

/** 
 * \brief
 * Field returns the maximum delay seen since tx domain was reset. This can
 * be used for calibrating constants latency function.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_TX_CFG . DEV_TX_DLY_MON
 */
#define  VTSS_F_DEV10G_DEV_TX_CFG_DEV_TX_DLY_MON(x)  VTSS_ENCODE_BITFIELD(x,0,14)
#define  VTSS_M_DEV10G_DEV_TX_CFG_DEV_TX_DLY_MON     VTSS_ENCODE_BITMASK(0,14)
#define  VTSS_X_DEV10G_DEV_TX_CFG_DEV_TX_DLY_MON(x)  VTSS_EXTRACT_BITFIELD(x,0,14)


/** 
 * \brief Configures preempting transmission options
 *
 * \details
 * Register: \a DEV10G:PTP_CFG_STATUS:DEV_PFRAME_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_PFRAME_CFG(target)   VTSS_IOREG(target,0x8f)

/** 
 * \brief
 * Configures the inter frame gap inserted after a p-frame fragment. The
 * MAC will for such fragments extend the frames, and the gap controller
 * must therefore wait longer than the standard 12, to get standard IFG on
 * the line.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_PFRAME_CFG . DEV_FRAGMENT_IFG
 */
#define  VTSS_F_DEV10G_DEV_PFRAME_CFG_DEV_FRAGMENT_IFG(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEV10G_DEV_PFRAME_CFG_DEV_FRAGMENT_IFG     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEV10G_DEV_PFRAME_CFG_DEV_FRAGMENT_IFG(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a DEV10G:PHASE_DETECTOR_CTRL
 *
 * High precission event detection Configuration and Status Registers
 */


/** 
 * \brief Phase detection control
 *
 * \details
 * Register: \a DEV10G:PHASE_DETECTOR_CTRL:PHAD_CTRL
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 * @param gi Replicator: x_PHASE_DETECTOR_INSTANCES (??), 0-1
 */
#define VTSS_DEV10G_PHAD_CTRL(gi)            VTSS_IOREG_IX(target,0x90,gi,2,0,0)

/** 
 * \brief
 * Enable phase detector
 *
 * \details 
 * Field: ::VTSS_DEV10G_PHAD_CTRL . PHAD_ENA
 */
#define  VTSS_F_DEV10G_PHAD_CTRL_PHAD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DEV10G_PHAD_CTRL_PHAD_ENA     VTSS_BIT(7)
#define  VTSS_X_DEV10G_PHAD_CTRL_PHAD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Phase detector has lost lock since the clearing of the bit. Can be
 * cleared writing one to this field.>
 *	     This field become unreliable for event clocks slower than 10
 * MHz, but phase detection can still be trusted. Slow event clocks are
 * only seen in synchronuous PPS detection.

 *
 * \details 
 * Field: ::VTSS_DEV10G_PHAD_CTRL . PHAD_FAILED
 */
#define  VTSS_F_DEV10G_PHAD_CTRL_PHAD_FAILED(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DEV10G_PHAD_CTRL_PHAD_FAILED  VTSS_BIT(6)
#define  VTSS_X_DEV10G_PHAD_CTRL_PHAD_FAILED(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Reduce the number of slaves cycles to measure period with by 2**value. 
 *
 * \details 
 * Field: ::VTSS_DEV10G_PHAD_CTRL . REDUCED_RES
 */
#define  VTSS_F_DEV10G_PHAD_CTRL_REDUCED_RES(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_DEV10G_PHAD_CTRL_REDUCED_RES     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_DEV10G_PHAD_CTRL_REDUCED_RES(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/** 
 * \brief
 * Accuracy of lock logic
 *
 * \details 
 * Field: ::VTSS_DEV10G_PHAD_CTRL . LOCK_ACC
 */
#define  VTSS_F_DEV10G_PHAD_CTRL_LOCK_ACC(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_DEV10G_PHAD_CTRL_LOCK_ACC     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_DEV10G_PHAD_CTRL_LOCK_ACC(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Phase detection status
 *
 * \details
 * Cycle time detected
 *
 * Register: \a DEV10G:PHASE_DETECTOR_CTRL:PHAD_CYC_STAT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 * @param gi Replicator: x_PHASE_DETECTOR_INSTANCES (??), 0-1
 */
#define VTSS_DEV10G_PHAD_CYC_STAT(gi)        VTSS_IOREG_IX(target,0x90,gi,2,0,1)

/** 
 * \brief
 * Detected event clock period in 4.28 fixedpoint format.
 *
 * \details 
 * Field: ::VTSS_DEV10G_PHAD_CYC_STAT . PHAD_CYCLETIME
 */
#define  VTSS_F_DEV10G_PHAD_CYC_STAT_PHAD_CYCLETIME(x)  (x)
#define  VTSS_M_DEV10G_PHAD_CYC_STAT_PHAD_CYCLETIME     0xffffffff
#define  VTSS_X_DEV10G_PHAD_CYC_STAT_PHAD_CYCLETIME(x)  (x)


#endif /* _VTSS_FA_REGS_DEV10G_H_ */
