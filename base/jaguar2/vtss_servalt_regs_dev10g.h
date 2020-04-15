#ifndef _VTSS_SERVALT_REGS_DEV10G_H_
#define _VTSS_SERVALT_REGS_DEV10G_H_

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

#include "vtss_servalt_regs_common.h"

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
#define VTSS_DEV10G_MAC_CFG_STATUS_MAC_ENA_CFG(target)  VTSS_IOREG(target,0x0)

/** 
 * \brief
 * Enable Receiver.
 *
 * \details 
 * '0': Disabled
 * '1': Enabled.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_ENA_CFG . RX_ENA
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_ENA_CFG_RX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_ENA_CFG_RX_ENA  VTSS_BIT(4)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_ENA_CFG_RX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enable Transmitter.
 *
 * \details 
 * '0': Disabled
 * '1': Enabled.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_ENA_CFG . TX_ENA
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_ENA_CFG_TX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_ENA_CFG_TX_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_ENA_CFG_TX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Mode Configuration Register
 *
 * \details
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_MODE_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG(target)  VTSS_IOREG(target,0x1)

/** 
 * \brief
 * On a given link, Pause Frames can be either "Link Pause frames" or
 * "Tunnel Pause Frames".
 * 
 * "Link Pause Frames" will have standard preamble, while "Tunnel Pause
 * Frames" will have HIH in the preamble.
 * 
 * For "Link Pause Frames" MAC10G should not verify HIH CKSM, while for
 * "Tunnel Pause Frames" MAC10G should verify HIH CKSM.

 *
 * \details 
 * 0: Pause frames are expected to be Link Pause frames - No HIH CKSM
 * verification in MAC10G
 * 1: Pause frames are expected to be Tunnel Pause frames - HIH CKSM is
 * verified in MAC10G
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG . TUNNEL_PAUSE_FRAMES
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG_TUNNEL_PAUSE_FRAMES(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG_TUNNEL_PAUSE_FRAMES  VTSS_BIT(16)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG_TUNNEL_PAUSE_FRAMES(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * This register configures the format of the preamble.
 * This supports:
 * 1) Standard preamble = 0xFB555555555555D5
 * 2) Minimum preamble = 0xFB
 * 3) Host Interface Header (HIH) located before the SFD
 * 4) Host Interface Header (HIH) located after the SFD - default CRC
 * 5) Host Interface Header (HIH) located after the SFD - HIH included in
 * CRC
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
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG . MAC_PREAMBLE_CFG
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG_MAC_PREAMBLE_CFG(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG_MAC_PREAMBLE_CFG     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG_MAC_PREAMBLE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/** 
 * \brief
 * Register configures the format of the IPG.
 * 1) Normal IPG : Averaging IPG for average of 12 bytes
 * 2) Shrinked IPG : Minimum IPG of 4 - 7 bytes (Incl. Terminate Character
 * and IDLE BYTEs)
 *
 * \details 
 * '0': Normal IPG.
 * '1': Shrink IPG.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG . MAC_IPG_CFG
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG_MAC_IPG_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG_MAC_IPG_CFG  VTSS_BIT(8)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG_MAC_IPG_CFG(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

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
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG . XGMII_GEN_MODE_ENA
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG_XGMII_GEN_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG_XGMII_GEN_MODE_ENA  VTSS_BIT(4)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG_XGMII_GEN_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * When asserted (=1) MAC10G must check HIH checksum and discard frames if
 * HIH checksum is not valid.
 * When deasserted (=0) MAC10G must disregard the HIH checksum.
 *
 * \details 
 * = 0 ; MAC10G should disregard the HIH CKSM.
 * = 1 ; MAC10G should discard any frame with invalid CKSM
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG . HIH_CRC_CHECK
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG_HIH_CRC_CHECK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG_HIH_CRC_CHECK  VTSS_BIT(0)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_MODE_CFG_HIH_CRC_CHECK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Max Length Configuration Register
 *
 * \details
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_MAXLEN_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MAC_CFG_STATUS_MAC_MAXLEN_CFG(target)  VTSS_IOREG(target,0x2)

/** 
 * \brief
 * Configures whether the Max Length Check takes the number of Q tags into
 * consideration when assing if a frame is too long.
 * 
 * If asserted, 
 *  - 4 bytes will be added to MAX_LEN for single tagged frame.
 *  - 8 bytes will be added to MAX_LEN for double tagged frame.
 *  - 12 bytes will be added to MAX_LEN for tripple tagged frame.
 *
 * \details 
 * '0' : Only check max frame length against MAX_LEN
 * '1' : Add 4/8/12 bytes to MAX_LEN when checking for max frame length
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_MAXLEN_CFG . MAX_LEN_TAG_CHK
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_MAXLEN_CFG_MAX_LEN_TAG_CHK(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_MAXLEN_CFG_MAX_LEN_TAG_CHK  VTSS_BIT(16)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_MAXLEN_CFG_MAX_LEN_TAG_CHK(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * The maximum frame length accepted by the Receive Module. If the length
 * is exceeded, this is indicated in the Statistics Engine (LONG_FRAME).
 * The maximum length is automatically adjusted to accommodate maximum
 * sized frames containing a VLAN tag - given that the MAC is configured to
 * be VLAN aware (default):
 * 
 * MTU size = 10056 Bytes. This includes all encapsulations and TAGs. Not
 * including IFH.
 *  
 * Reason is: QS supports a max of 63 segments. A segment is 160 Bytes. The
 * IFH must be stored in the QS also, so room must be allocated.
 * Thereby:
 * 63 x 160B - 24B (IFH) = 10056 Bytes
 *
 * \details 
 * The maximum allowable size is 10056 Bytes.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_MAXLEN_CFG . MAX_LEN
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_MAXLEN_CFG_MAX_LEN(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_MAXLEN_CFG_MAX_LEN     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_MAXLEN_CFG_MAX_LEN(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Register to specify no.of tags supoorted
 *
 * \details
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_NUM_TAGS_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MAC_CFG_STATUS_MAC_NUM_TAGS_CFG(target)  VTSS_IOREG(target,0x3)

/** 
 * \brief
 * Configuration for number of consecutive VLAN Tags supported by the MAC.
 * Maximum value is 3.
 *
 * \details 
 * '0': No tags are detected by MAC.
 * 'n': Maximum of n consecutive VLAN Tags are detected by the MAC and
 * accordingly MAX LEN is modified for frame length calculations.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_NUM_TAGS_CFG . NUM_TAGS
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_NUM_TAGS_CFG_NUM_TAGS(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_NUM_TAGS_CFG_NUM_TAGS     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_NUM_TAGS_CFG_NUM_TAGS(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


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
#define VTSS_DEV10G_MAC_CFG_STATUS_MAC_TAGS_CFG(target,ri)  VTSS_IOREG(target,0x4 + (ri))

/** 
 * \brief
 * This field defines which value is regarded as a VLAN/Service tag -
 * besides 0x8100 and 0x88A8. The value is used for all ALL tag positions.
 * I.e. a double tagged frame can have the following tag values:
 * (INNER_TAG, OUTER_TAG):
 * ( 0x8100, 0x8100 )
 * ( 0x8100, TAG_ID ) or
 * ( TAG_ID, TAG_ID )
 *
 * \details 
 * "0x8100" - Standard Ethernet Bridge ethertype (C-tag)
 * "0x88A8" - Provider Bridge Ethertype  (S-tag)
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_TAGS_CFG . TAG_ID
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_TAGS_CFG_TAG_ID(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_TAGS_CFG_TAG_ID     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_TAGS_CFG_TAG_ID(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Enables TAG_ID apart from standard 0x8100 and 0x88A8 for Tag
 * comparision.
 *
 * \details 
 * '0': The MAC doesn't take TAG_ID for tag identification.
 * '1': The MAC looks for tag according to encoding of TAG_ID
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_TAGS_CFG . TAG_ENA
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_TAGS_CFG_TAG_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_TAGS_CFG_TAG_ENA  VTSS_BIT(4)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_TAGS_CFG_TAG_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief Advanced Check Feature Configuration Register
 *
 * \details
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_ADV_CHK_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG(target)  VTSS_IOREG(target,0x7)

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
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG . EXT_EOP_CHK_ENA
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_EXT_EOP_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_EXT_EOP_CHK_ENA  VTSS_BIT(24)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_EXT_EOP_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

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
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG . EXT_SOP_CHK_ENA
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_EXT_SOP_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_EXT_SOP_CHK_ENA  VTSS_BIT(20)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_EXT_SOP_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Start-of-Frame-Delimiter Check Enable: Specifies the requirement for a
 * successful frame reception.
 * When disabled (='0'), MAC10G will assume that preamble is 8 bytes (incl.
 * SOP & SFD) when SOP is received. No checking of SFD is carried out.
 * When enabled (='1'), MAC10G will search for SFD in lane 3/7 after
 * reception of SOP, before accepting frame data. MAC10G will search for
 * SFD until SFD is found or a control character is encountered.
 *
 * \details 
 * '0': Skip SFD check
 * '1': Strict SFD check enabled, i.e. the SFD must be "D5" for a
 * successful frame reception.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG . SFD_CHK_ENA
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_SFD_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_SFD_CHK_ENA  VTSS_BIT(16)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_SFD_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Preamble Shrink Check Disable:
 * The MAC can be setup to discard a frame, if a SFD is received in lane 3
 * of the column containing the SOP. If stacking tags must be supported,
 * the MAC must accept any data byte at this position.
 *
 * \details 
 * '0': Frames with a SFD in lane 3 of the column containing the SOP are
 * discarded.
 * '1': Frames with a SFD in lane 3 of the column containing the SOP are
 * NOT discarded.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG . PRM_SHK_CHK_DIS
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_PRM_SHK_CHK_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_PRM_SHK_CHK_DIS  VTSS_BIT(12)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_PRM_SHK_CHK_DIS(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

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
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG . PRM_CHK_ENA
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_PRM_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_PRM_CHK_ENA  VTSS_BIT(8)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_PRM_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

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
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG . OOR_ERR_ENA
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_OOR_ERR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_OOR_ERR_ENA  VTSS_BIT(4)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_OOR_ERR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

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
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG . INR_ERR_ENA
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_INR_ERR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_INR_ERR_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_ADV_CHK_CFG_INR_ERR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Link Fault Signaling Register
 *
 * \details
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_LFS_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MAC_CFG_STATUS_MAC_LFS_CFG(target)  VTSS_IOREG(target,0x8)

/** 
 * \brief
 * LFS Unidirectional mode enable. Implementation of 802.3 clause 66. When
 * asserted, this enables MAC to transmit data during reception of Local
 * Fault and Remote Fault ordered sets from the PHY. 
 * 
 * When in Unidirectional mode:
 * When receiving LF, frames are transmitted separated by RF ordered sets.
 * When receiving RF, frames are transmitted separated by IDLE symbols
 *
 * \details 
 * '0' : LFS unidirectional mode is disabled
 * '1' : LFS unidirectional mode is enabled
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_LFS_CFG . LFS_UNIDIR_ENA
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_LFS_CFG_LFS_UNIDIR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_LFS_CFG_LFS_UNIDIR_ENA  VTSS_BIT(3)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_LFS_CFG_LFS_UNIDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * GNATS #6146. Use the leading edge of the TX_ENA signal to control the
 * state machine in tx_datapath.
 * This bit is implemented to disable the fix incase it is causing
 * problems.
 *
 * \details 
 * 0 : Leading edge detect disabled
 * 1 : Leading edge detect enabled
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_LFS_CFG . USE_LEADING_EDGE_DETECT
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_LFS_CFG_USE_LEADING_EDGE_DETECT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_LFS_CFG_USE_LEADING_EDGE_DETECT  VTSS_BIT(2)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_LFS_CFG_USE_LEADING_EDGE_DETECT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * During normal 802.3 compliant operation, it is possible to send spurious
 * ||Q|| after the lfs condition was deasserted.
 * 
 * Asserting this bit will prevent these spurious ||Q|| by delaying TX
 * until the PCS reports that no ||Q|| are pending.
 * 
 * Applicable for XAUI speeds only.
 *
 * \details 
 * 0 - Allow ||Q|| transmission (ieee 802.3 compliant)
 * 1 - Suppress ||Q|| transmission
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_LFS_CFG . SPURIOUS_Q_DIS
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_LFS_CFG_SPURIOUS_Q_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_LFS_CFG_SPURIOUS_Q_DIS  VTSS_BIT(1)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_LFS_CFG_SPURIOUS_Q_DIS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

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
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_LFS_CFG . LFS_MODE_ENA
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_LFS_CFG_LFS_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_LFS_CFG_LFS_MODE_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_LFS_CFG_LFS_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Miscellaneous Configuration Register
 *
 * \details
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_LB_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MAC_CFG_STATUS_MAC_LB_CFG(target)  VTSS_IOREG(target,0x9)

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
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_LB_CFG . XGMII_HOST_LB_ENA
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_LB_CFG_XGMII_HOST_LB_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_LB_CFG_XGMII_HOST_LB_ENA  VTSS_BIT(4)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_LB_CFG_XGMII_HOST_LB_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enables loopback from ingress to egress data path at XGMII interface.
 *
 * \details 
 * '0': PHY Loopback Disabled at XGMII interface.
 * '1': PHY Loopback Enabled at XGMII interface.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_LB_CFG . XGMII_PHY_LB_ENA
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_LB_CFG_XGMII_PHY_LB_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_LB_CFG_XGMII_PHY_LB_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_LB_CFG_XGMII_PHY_LB_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief XGMII Lane Debug Sticky bit Register 0
 *
 * \details
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_RX_LANE_STICKY_0
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_0(target)  VTSS_IOREG(target,0xa)

/** 
 * \brief
 * Sticky bits for debugging Lane 3.
 *
 * \details 
 * See format of LANE0 sticky bit register.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_0 . LANE3_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_0_LANE3_STICKY(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_0_LANE3_STICKY     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_0_LANE3_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/** 
 * \brief
 * Sticky bits for debugging Lane 2.
 *
 * \details 
 * See format of LANE0 sticky bit register.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_0 . LANE2_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_0_LANE2_STICKY(x)  VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_0_LANE2_STICKY     VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_0_LANE2_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,7)

/** 
 * \brief
 * Sticky bits for debugging Lane 1.
 *
 * \details 
 * See format of LANE0 sticky bit register.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_0 . LANE1_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_0_LANE1_STICKY(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_0_LANE1_STICKY     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_0_LANE1_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

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
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_0 . LANE0_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_0_LANE0_STICKY(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_0_LANE0_STICKY     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_0_LANE0_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief XGMII Lane Debug Sticky bit Register 1
 *
 * \details
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_RX_LANE_STICKY_1
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_1(target)  VTSS_IOREG(target,0xb)

/** 
 * \brief
 * Sticky bits for debugging Lane 7.
 *
 * \details 
 * See format of LANE0 sticky bit register.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_1 . LANE7_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_1_LANE7_STICKY(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_1_LANE7_STICKY     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_1_LANE7_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/** 
 * \brief
 * Sticky bits for debugging Lane 6.
 *
 * \details 
 * See format of LANE0 sticky bit register.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_1 . LANE6_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_1_LANE6_STICKY(x)  VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_1_LANE6_STICKY     VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_1_LANE6_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,7)

/** 
 * \brief
 * Sticky bits for debugging Lane 5.
 *
 * \details 
 * See format of LANE0 sticky bit register.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_1 . LANE5_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_1_LANE5_STICKY(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_1_LANE5_STICKY     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_1_LANE5_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/** 
 * \brief
 * Sticky bits for debugging Lane 4.
 *
 * \details 
 * See format of LANE0 sticky bit register.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_1 . LANE4_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_1_LANE4_STICKY(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_1_LANE4_STICKY     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_RX_LANE_STICKY_1_LANE4_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief MAC10G Tx Monitor Sticky bit Register
 *
 * \details
 * Register: \a DEV10G:MAC_CFG_STATUS:MAC_TX_MONITOR_STICKY
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY(target)  VTSS_IOREG(target,0xc)

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
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY . LOCAL_ERR_STATE_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY_LOCAL_ERR_STATE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY_LOCAL_ERR_STATE_STICKY  VTSS_BIT(4)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY_LOCAL_ERR_STATE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

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
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY . REMOTE_ERR_STATE_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY_REMOTE_ERR_STATE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY_REMOTE_ERR_STATE_STICKY  VTSS_BIT(3)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY_REMOTE_ERR_STATE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

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
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY . IDLE_STATE_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY  VTSS_BIT(1)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

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
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY . DIS_STATE_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY_DIS_STATE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY_DIS_STATE_STICKY  VTSS_BIT(0)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_TX_MONITOR_STICKY_DIS_STATE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


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
#define VTSS_DEV10G_MAC_CFG_STATUS_MAC_STICKY(target)  VTSS_IOREG(target,0xd)

/** 
 * \brief
 * Indicates that an inter packet gap shrink was detected (IPG < 12 bytes).
 *
 * \details 
 * '0': no ipg shrink was detected
 * '1': one or more ipg shrink were detected
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_STICKY . RX_IPG_SHRINK_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_IPG_SHRINK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_IPG_SHRINK_STICKY  VTSS_BIT(9)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_IPG_SHRINK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Indicates that a preamble shrink was detected (preamble < 8 bytes).
 * This sticky bit can only be set when the port is setup in 10 Gbps mode,
 * where frames with e.g. a 4 bytes preamble will be discarded, and it
 * requires that PRM_SHK_CHK_DIS = 0 and SFD_CHK_ENA = 1.
 * In SGMII mode, all preamble sizes down to 3 bytes (including SFD) are
 * accepted and will not cause this sticky bit to be set.
 *
 * \details 
 * '0': no preamble shrink detected;
 * '1': one or more preamble shrinks detected;
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_STICKY . RX_PREAM_SHRINK_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_PREAM_SHRINK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_PREAM_SHRINK_STICKY  VTSS_BIT(8)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_PREAM_SHRINK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * If Preamble Check is enabled and a SOP is received, this bit is set if
 * the following bytes do not match a "5555555555..55D5" pattern.
 * A 12 bytes preamble of "55555555.55555555.555555D5" will not cause this
 * sticky bit to be set.
 * 
 * This sticky bit can only be set when the port is setup in 10 Gbps mode.
 *
 * \details 
 * '0': No Preamble check has failed;
 * '1': One or more preamble checks have failed;
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_STICKY . RX_PREAM_MISMATCH_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_PREAM_MISMATCH_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_PREAM_MISMATCH_STICKY  VTSS_BIT(7)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_PREAM_MISMATCH_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

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
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_STICKY . RX_PREAM_ERR_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_PREAM_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_PREAM_ERR_STICKY  VTSS_BIT(6)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_PREAM_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Indicates that a frame was received with a non-standard preamble.
 *
 * \details 
 * '0': No non-standard preamble detected;
 * '1': One or more frames with non-standard preamble detected;
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_STICKY . RX_NON_STD_PREAM_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_NON_STD_PREAM_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_NON_STD_PREAM_STICKY  VTSS_BIT(5)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_NON_STD_PREAM_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

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
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_STICKY . RX_MPLS_MC_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_MPLS_MC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_MPLS_MC_STICKY  VTSS_BIT(4)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_MPLS_MC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Indicates that a frame with MPLS unicast was received.
 *
 * \details 
 * '0': No frames with MPLS Unicast EtherType has been detected;
 * '1': One or more frames with MPLS Unicast EtherType have been detected;
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_STICKY . RX_MPLS_UC_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_MPLS_UC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_MPLS_UC_STICKY  VTSS_BIT(3)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_MPLS_UC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Indicates that a frame was received with a VLAN tag.
 *
 * \details 
 * '0': No Tagged frames have been detected;
 * '1': One or more Tagged frames have been detected;
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_STICKY . RX_TAG_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_TAG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_TAG_STICKY  VTSS_BIT(2)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_STICKY_RX_TAG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Sticky bit indicating that the MAC Transmit FIFO has dropped one or more
 * frames because of underrun.
 *
 * \details 
 * '0': No MAC Tx FIFO underrun has occured
 * '1': One or more MAC Tx FIFO underruns have occured
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_STICKY . TX_UFLW_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_STICKY_TX_UFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_STICKY_TX_UFLW_STICKY  VTSS_BIT(1)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_STICKY_TX_UFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Indicates that the transmit host initiated abort was executed.
 *
 * \details 
 * '0': no tx frame was aborted
 * '1': one or more tx frames were aborted
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEV10G_MAC_CFG_STATUS_MAC_STICKY . TX_ABORT_STICKY
 */
#define  VTSS_F_DEV10G_MAC_CFG_STATUS_MAC_STICKY_TX_ABORT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_MAC_CFG_STATUS_MAC_STICKY_TX_ABORT_STICKY  VTSS_BIT(0)
#define  VTSS_X_DEV10G_MAC_CFG_STATUS_MAC_STICKY_TX_ABORT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

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
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_SYMBOL_ERR_CNT(target)  VTSS_IOREG(target,0xe)

/** 
 * \brief
 * The number of frames received with one or more symbol errors.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_SYMBOL_ERR_CNT . RX_SYMBOL_ERR_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_SYMBOL_ERR_CNT_RX_SYMBOL_ERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_SYMBOL_ERR_CNT_RX_SYMBOL_ERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_SYMBOL_ERR_CNT_RX_SYMBOL_ERR_CNT(x)  (x)


/** 
 * \brief Rx Pause Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_PAUSE_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_PAUSE_CNT(target)  VTSS_IOREG(target,0xf)

/** 
 * \brief
 * Number of pause control frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_PAUSE_CNT . RX_PAUSE_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_PAUSE_CNT_RX_PAUSE_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_PAUSE_CNT_RX_PAUSE_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_PAUSE_CNT_RX_PAUSE_CNT(x)  (x)


/** 
 * \brief Rx Control Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_UNSUP_OPCODE_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_UNSUP_OPCODE_CNT(target)  VTSS_IOREG(target,0x10)

/** 
 * \brief
 * Number of control frames with unsupported opcode received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_UNSUP_OPCODE_CNT . RX_UNSUP_OPCODE_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_UNSUP_OPCODE_CNT_RX_UNSUP_OPCODE_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_UNSUP_OPCODE_CNT_RX_UNSUP_OPCODE_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_UNSUP_OPCODE_CNT_RX_UNSUP_OPCODE_CNT(x)  (x)


/** 
 * \brief Rx Unicast Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_UC_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_UC_CNT(target)  VTSS_IOREG(target,0x11)

/** 
 * \brief
 * The number of good unicast frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_UC_CNT . RX_UC_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_UC_CNT_RX_UC_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_UC_CNT_RX_UC_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_UC_CNT_RX_UC_CNT(x)  (x)


/** 
 * \brief Rx Multicast Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_MC_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_MC_CNT(target)  VTSS_IOREG(target,0x12)

/** 
 * \brief
 * The number of good multicast frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_MC_CNT . RX_MC_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_MC_CNT_RX_MC_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_MC_CNT_RX_MC_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_MC_CNT_RX_MC_CNT(x)  (x)


/** 
 * \brief Rx Broadcast Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_BC_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_BC_CNT(target)  VTSS_IOREG(target,0x13)

/** 
 * \brief
 * The number of good broadcast frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_BC_CNT . RX_BC_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_BC_CNT_RX_BC_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_BC_CNT_RX_BC_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_BC_CNT_RX_BC_CNT(x)  (x)


/** 
 * \brief Rx CRC Error Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_CRC_ERR_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_CRC_ERR_CNT(target)  VTSS_IOREG(target,0x14)

/** 
 * \brief
 * The number of frames received with CRC error only.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_CRC_ERR_CNT . RX_CRC_ERR_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_CRC_ERR_CNT_RX_CRC_ERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_CRC_ERR_CNT_RX_CRC_ERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_CRC_ERR_CNT_RX_CRC_ERR_CNT(x)  (x)


/** 
 * \brief Rx Undersize Counter (valid frame format)
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_UNDERSIZE_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_UNDERSIZE_CNT(target)  VTSS_IOREG(target,0x15)

/** 
 * \brief
 * The number of undersize well-formed frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_UNDERSIZE_CNT . RX_UNDERSIZE_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_UNDERSIZE_CNT_RX_UNDERSIZE_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_UNDERSIZE_CNT_RX_UNDERSIZE_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_UNDERSIZE_CNT_RX_UNDERSIZE_CNT(x)  (x)


/** 
 * \brief Rx Undersize Counter (CRC error)
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_FRAGMENTS_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_FRAGMENTS_CNT(target)  VTSS_IOREG(target,0x16)

/** 
 * \brief
 * The number of undersize frames with CRC error received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_FRAGMENTS_CNT . RX_FRAGMENTS_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_FRAGMENTS_CNT_RX_FRAGMENTS_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_FRAGMENTS_CNT_RX_FRAGMENTS_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_FRAGMENTS_CNT_RX_FRAGMENTS_CNT(x)  (x)


/** 
 * \brief Rx In-range Length Error Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_IN_RANGE_LEN_ERR_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_IN_RANGE_LEN_ERR_CNT(target)  VTSS_IOREG(target,0x17)

/** 
 * \brief
 * The number of frames with legal length field that doesn't match length
 * of MAC client data.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_IN_RANGE_LEN_ERR_CNT . RX_IN_RANGE_LEN_ERR_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_IN_RANGE_LEN_ERR_CNT_RX_IN_RANGE_LEN_ERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_IN_RANGE_LEN_ERR_CNT_RX_IN_RANGE_LEN_ERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_IN_RANGE_LEN_ERR_CNT_RX_IN_RANGE_LEN_ERR_CNT(x)  (x)


/** 
 * \brief Rx Out-Of-Range Length Error Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_OUT_OF_RANGE_LEN_ERR_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_OUT_OF_RANGE_LEN_ERR_CNT(target)  VTSS_IOREG(target,0x18)

/** 
 * \brief
 * The number of frames with illegal length field (frames using type field
 * are not counted here).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_OUT_OF_RANGE_LEN_ERR_CNT . RX_OUT_OF_RANGE_LEN_ERR_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_OUT_OF_RANGE_LEN_ERR_CNT_RX_OUT_OF_RANGE_LEN_ERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_OUT_OF_RANGE_LEN_ERR_CNT_RX_OUT_OF_RANGE_LEN_ERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_OUT_OF_RANGE_LEN_ERR_CNT_RX_OUT_OF_RANGE_LEN_ERR_CNT(x)  (x)


/** 
 * \brief Rx Oversize Counter (valid frame format)
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_OVERSIZE_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_OVERSIZE_CNT(target)  VTSS_IOREG(target,0x19)

/** 
 * \brief
 * The number of oversize well-formed frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_OVERSIZE_CNT . RX_OVERSIZE_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_OVERSIZE_CNT_RX_OVERSIZE_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_OVERSIZE_CNT_RX_OVERSIZE_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_OVERSIZE_CNT_RX_OVERSIZE_CNT(x)  (x)


/** 
 * \brief Rx Jabbers Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_JABBERS_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_JABBERS_CNT(target)  VTSS_IOREG(target,0x1a)

/** 
 * \brief
 * The number of oversize frames with CRC error received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_JABBERS_CNT . RX_JABBERS_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_JABBERS_CNT_RX_JABBERS_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_JABBERS_CNT_RX_JABBERS_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_JABBERS_CNT_RX_JABBERS_CNT(x)  (x)


/** 
 * \brief Rx 64 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_SIZE64_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE64_CNT(target)  VTSS_IOREG(target,0x1b)

/** 
 * \brief
 * The number of 64 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE64_CNT . RX_SIZE64_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE64_CNT_RX_SIZE64_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE64_CNT_RX_SIZE64_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE64_CNT_RX_SIZE64_CNT(x)  (x)


/** 
 * \brief Rx 65-127 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_SIZE65TO127_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE65TO127_CNT(target)  VTSS_IOREG(target,0x1c)

/** 
 * \brief
 * The number of 65 to 127 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE65TO127_CNT . RX_SIZE65TO127_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE65TO127_CNT_RX_SIZE65TO127_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE65TO127_CNT_RX_SIZE65TO127_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE65TO127_CNT_RX_SIZE65TO127_CNT(x)  (x)


/** 
 * \brief Rx 128-255 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_SIZE128TO255_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE128TO255_CNT(target)  VTSS_IOREG(target,0x1d)

/** 
 * \brief
 * The number of 128 to 255 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE128TO255_CNT . RX_SIZE128TO255_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE128TO255_CNT_RX_SIZE128TO255_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE128TO255_CNT_RX_SIZE128TO255_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE128TO255_CNT_RX_SIZE128TO255_CNT(x)  (x)


/** 
 * \brief Rx 256-511 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_SIZE256TO511_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE256TO511_CNT(target)  VTSS_IOREG(target,0x1e)

/** 
 * \brief
 * The number of 256 to 511 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE256TO511_CNT . RX_SIZE256TO511_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE256TO511_CNT_RX_SIZE256TO511_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE256TO511_CNT_RX_SIZE256TO511_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE256TO511_CNT_RX_SIZE256TO511_CNT(x)  (x)


/** 
 * \brief Rx 512-1023 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_SIZE512TO1023_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE512TO1023_CNT(target)  VTSS_IOREG(target,0x1f)

/** 
 * \brief
 * The number of 512 to 1023 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE512TO1023_CNT . RX_SIZE512TO1023_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE512TO1023_CNT_RX_SIZE512TO1023_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE512TO1023_CNT_RX_SIZE512TO1023_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE512TO1023_CNT_RX_SIZE512TO1023_CNT(x)  (x)


/** 
 * \brief Rx 1024-1518 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_SIZE1024TO1518_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE1024TO1518_CNT(target)  VTSS_IOREG(target,0x20)

/** 
 * \brief
 * The number of 1024 to 1518 bytes frames received.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE1024TO1518_CNT . RX_SIZE1024TO1518_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE1024TO1518_CNT_RX_SIZE1024TO1518_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE1024TO1518_CNT_RX_SIZE1024TO1518_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE1024TO1518_CNT_RX_SIZE1024TO1518_CNT(x)  (x)


/** 
 * \brief Rx 1519 To Max. Length Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_SIZE1519TOMAX_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE1519TOMAX_CNT(target)  VTSS_IOREG(target,0x21)

/** 
 * \brief
 * The number of frames received longer than 1518 bytes and not longer than
 * Maximum Length Register (Maximum Length Register + 4 if the frame is
 * VLAN tagged).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE1519TOMAX_CNT . RX_SIZE1519TOMAX_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE1519TOMAX_CNT_RX_SIZE1519TOMAX_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE1519TOMAX_CNT_RX_SIZE1519TOMAX_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_SIZE1519TOMAX_CNT_RX_SIZE1519TOMAX_CNT(x)  (x)


/** 
 * \brief Rx Inter Packet Gap Shrink Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_IPG_SHRINK_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_IPG_SHRINK_CNT(target)  VTSS_IOREG(target,0x22)

/** 
 * \brief
 * Number of inter packet gap shrinks detected (IPG < 12 bytes).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_IPG_SHRINK_CNT . RX_IPG_SHRINK_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_IPG_SHRINK_CNT_RX_IPG_SHRINK_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_IPG_SHRINK_CNT_RX_IPG_SHRINK_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_IPG_SHRINK_CNT_RX_IPG_SHRINK_CNT(x)  (x)


/** 
 * \brief Tx Pause Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_PAUSE_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_PAUSE_CNT(target)  VTSS_IOREG(target,0x23)

/** 
 * \brief
 * The number of pause control frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_PAUSE_CNT . TX_PAUSE_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_TX_PAUSE_CNT_TX_PAUSE_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_TX_PAUSE_CNT_TX_PAUSE_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_TX_PAUSE_CNT_TX_PAUSE_CNT(x)  (x)


/** 
 * \brief Tx Unicast Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_UC_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_UC_CNT(target)  VTSS_IOREG(target,0x24)

/** 
 * \brief
 * The number of unicast frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_UC_CNT . TX_UC_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_TX_UC_CNT_TX_UC_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_TX_UC_CNT_TX_UC_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_TX_UC_CNT_TX_UC_CNT(x)  (x)


/** 
 * \brief Tx Multicast Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_MC_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_MC_CNT(target)  VTSS_IOREG(target,0x25)

/** 
 * \brief
 * The number of multicast frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_MC_CNT . TX_MC_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_TX_MC_CNT_TX_MC_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_TX_MC_CNT_TX_MC_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_TX_MC_CNT_TX_MC_CNT(x)  (x)


/** 
 * \brief Tx Broadcast Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_BC_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_BC_CNT(target)  VTSS_IOREG(target,0x26)

/** 
 * \brief
 * The number of broadcast frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_BC_CNT . TX_BC_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_TX_BC_CNT_TX_BC_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_TX_BC_CNT_TX_BC_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_TX_BC_CNT_TX_BC_CNT(x)  (x)


/** 
 * \brief Tx 64 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_SIZE64_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE64_CNT(target)  VTSS_IOREG(target,0x27)

/** 
 * \brief
 * The number of 64 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE64_CNT . TX_SIZE64_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE64_CNT_TX_SIZE64_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE64_CNT_TX_SIZE64_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE64_CNT_TX_SIZE64_CNT(x)  (x)


/** 
 * \brief Tx 65-127 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_SIZE65TO127_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE65TO127_CNT(target)  VTSS_IOREG(target,0x28)

/** 
 * \brief
 * The number of 65 to 127 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE65TO127_CNT . TX_SIZE65TO127_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE65TO127_CNT_TX_SIZE65TO127_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE65TO127_CNT_TX_SIZE65TO127_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE65TO127_CNT_TX_SIZE65TO127_CNT(x)  (x)


/** 
 * \brief Tx 128-255 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_SIZE128TO255_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE128TO255_CNT(target)  VTSS_IOREG(target,0x29)

/** 
 * \brief
 * The number of 128 to 255 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE128TO255_CNT . TX_SIZE128TO255_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE128TO255_CNT_TX_SIZE128TO255_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE128TO255_CNT_TX_SIZE128TO255_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE128TO255_CNT_TX_SIZE128TO255_CNT(x)  (x)


/** 
 * \brief Tx 256-511 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_SIZE256TO511_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE256TO511_CNT(target)  VTSS_IOREG(target,0x2a)

/** 
 * \brief
 * The number of 256 to 511 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE256TO511_CNT . TX_SIZE256TO511_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE256TO511_CNT_TX_SIZE256TO511_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE256TO511_CNT_TX_SIZE256TO511_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE256TO511_CNT_TX_SIZE256TO511_CNT(x)  (x)


/** 
 * \brief Tx 512-1023 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_SIZE512TO1023_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE512TO1023_CNT(target)  VTSS_IOREG(target,0x2b)

/** 
 * \brief
 * The number of 512 to 1023 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE512TO1023_CNT . TX_SIZE512TO1023_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE512TO1023_CNT_TX_SIZE512TO1023_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE512TO1023_CNT_TX_SIZE512TO1023_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE512TO1023_CNT_TX_SIZE512TO1023_CNT(x)  (x)


/** 
 * \brief Tx 1024-1518 Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_SIZE1024TO1518_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE1024TO1518_CNT(target)  VTSS_IOREG(target,0x2c)

/** 
 * \brief
 * The number of 1024 to 1518 bytes frames transmitted.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE1024TO1518_CNT . TX_SIZE1024TO1518_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE1024TO1518_CNT_TX_SIZE1024TO1518_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE1024TO1518_CNT_TX_SIZE1024TO1518_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE1024TO1518_CNT_TX_SIZE1024TO1518_CNT(x)  (x)


/** 
 * \brief Tx 1519 To Max. Length Byte Frame Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_SIZE1519TOMAX_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE1519TOMAX_CNT(target)  VTSS_IOREG(target,0x2d)

/** 
 * \brief
 * The number of frames transmitted longer than 1518 bytes and not longer
 * than Maximum Length Register (Maximum Length Register + 4 if the frame
 * is VLAN tagged).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE1519TOMAX_CNT . TX_SIZE1519TOMAX_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE1519TOMAX_CNT_TX_SIZE1519TOMAX_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE1519TOMAX_CNT_TX_SIZE1519TOMAX_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_TX_SIZE1519TOMAX_CNT_TX_SIZE1519TOMAX_CNT(x)  (x)


/** 
 * \brief Counter to track the dribble-nibble (extra nibble) errors in frames.
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_ALIGNMENT_LOST_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_ALIGNMENT_LOST_CNT(target)  VTSS_IOREG(target,0x2e)

/** 
 * \brief
 * The number of frames received with Alignment (dribble-nibble) error.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_ALIGNMENT_LOST_CNT . RX_ALIGNMENT_LOST_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_ALIGNMENT_LOST_CNT_RX_ALIGNMENT_LOST_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_ALIGNMENT_LOST_CNT_RX_ALIGNMENT_LOST_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_ALIGNMENT_LOST_CNT_RX_ALIGNMENT_LOST_CNT(x)  (x)


/** 
 * \brief Counts frames that are tagged (C-Tagged or S-Tagged).
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_TAGGED_FRMS_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_TAGGED_FRMS_CNT(target)  VTSS_IOREG(target,0x2f)

/** 
 * \brief
 * The number of frames received with C-Tag or S-Tag information
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_TAGGED_FRMS_CNT . RX_TAGGED_FRMS_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_TAGGED_FRMS_CNT_RX_TAGGED_FRMS_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_TAGGED_FRMS_CNT_RX_TAGGED_FRMS_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_TAGGED_FRMS_CNT_RX_TAGGED_FRMS_CNT(x)  (x)


/** 
 * \brief Counts frames that are Not tagged  (neither C-Tagged nor S-Tagged).
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_UNTAGGED_FRMS_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_UNTAGGED_FRMS_CNT(target)  VTSS_IOREG(target,0x30)

/** 
 * \brief
 * The number of frames received without C-Tag and S-Tag information.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_UNTAGGED_FRMS_CNT . RX_UNTAGGED_FRMS_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_UNTAGGED_FRMS_CNT_RX_UNTAGGED_FRMS_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_UNTAGGED_FRMS_CNT_RX_UNTAGGED_FRMS_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_UNTAGGED_FRMS_CNT_RX_UNTAGGED_FRMS_CNT(x)  (x)


/** 
 * \brief Counts frames that are tagged (C-Tagged or S-Tagged).
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_TAGGED_FRMS_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_TAGGED_FRMS_CNT(target)  VTSS_IOREG(target,0x31)

/** 
 * \brief
 * The number of frames transmitted with C-Tag or S-Tag information
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_TAGGED_FRMS_CNT . TX_TAGGED_FRMS_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_TX_TAGGED_FRMS_CNT_TX_TAGGED_FRMS_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_TX_TAGGED_FRMS_CNT_TX_TAGGED_FRMS_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_TX_TAGGED_FRMS_CNT_TX_TAGGED_FRMS_CNT(x)  (x)


/** 
 * \brief Counts frames that are Not tagged  (neither C-Tagged nor S-Tagged).
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:TX_UNTAGGED_FRMS_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_UNTAGGED_FRMS_CNT(target)  VTSS_IOREG(target,0x32)

/** 
 * \brief
 * The number of frames transmitted without C-Tag and S-Tag information.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_TX_UNTAGGED_FRMS_CNT . TX_UNTAGGED_FRMS_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_TX_UNTAGGED_FRMS_CNT_TX_UNTAGGED_FRMS_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_TX_UNTAGGED_FRMS_CNT_TX_UNTAGGED_FRMS_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_TX_UNTAGGED_FRMS_CNT_TX_UNTAGGED_FRMS_CNT(x)  (x)


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
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_HIH_CKSM_ERR_CNT(target)  VTSS_IOREG(target,0x33)

/** 
 * \brief
 * Number of frames discarded due to errors in HIH checksum.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_HIH_CKSM_ERR_CNT . RX_HIH_CKSM_ERR_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_HIH_CKSM_ERR_CNT_RX_HIH_CKSM_ERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_HIH_CKSM_ERR_CNT_RX_HIH_CKSM_ERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_HIH_CKSM_ERR_CNT_RX_HIH_CKSM_ERR_CNT(x)  (x)


/** 
 * \brief Rx XGMII Protocol Error Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_32BIT:RX_XGMII_PROT_ERR_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_XGMII_PROT_ERR_CNT(target)  VTSS_IOREG(target,0x34)

/** 
 * \brief
 * Number of XGMII protocol errors detected.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_32BIT_RX_XGMII_PROT_ERR_CNT . RX_XGMII_PROT_ERR_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_32BIT_RX_XGMII_PROT_ERR_CNT_RX_XGMII_PROT_ERR_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_32BIT_RX_XGMII_PROT_ERR_CNT_RX_XGMII_PROT_ERR_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_32BIT_RX_XGMII_PROT_ERR_CNT_RX_XGMII_PROT_ERR_CNT(x)  (x)

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
#define VTSS_DEV10G_DEV_STATISTICS_40BIT_RX_IN_BYTES_CNT(target)  VTSS_IOREG(target,0x35)

/** 
 * \brief
 * The number of bytes received (good, bad, and framing).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_40BIT_RX_IN_BYTES_CNT . RX_IN_BYTES_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_40BIT_RX_IN_BYTES_CNT_RX_IN_BYTES_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_40BIT_RX_IN_BYTES_CNT_RX_IN_BYTES_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_40BIT_RX_IN_BYTES_CNT_RX_IN_BYTES_CNT(x)  (x)


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
#define VTSS_DEV10G_DEV_STATISTICS_40BIT_RX_IN_BYTES_MSB_CNT(target)  VTSS_IOREG(target,0x36)

/** 
 * \brief
 * The number of bytes received (good, bad, and framing) - MSBs only
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_40BIT_RX_IN_BYTES_MSB_CNT . RX_IN_BYTES_MSB_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_40BIT_RX_IN_BYTES_MSB_CNT_RX_IN_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEV10G_DEV_STATISTICS_40BIT_RX_IN_BYTES_MSB_CNT_RX_IN_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEV10G_DEV_STATISTICS_40BIT_RX_IN_BYTES_MSB_CNT_RX_IN_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Rx OK Byte Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_40BIT:RX_OK_BYTES_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_40BIT_RX_OK_BYTES_CNT(target)  VTSS_IOREG(target,0x37)

/** 
 * \brief
 * The number of received bytes in good frames.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_40BIT_RX_OK_BYTES_CNT . RX_OK_BYTES_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_40BIT_RX_OK_BYTES_CNT_RX_OK_BYTES_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_40BIT_RX_OK_BYTES_CNT_RX_OK_BYTES_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_40BIT_RX_OK_BYTES_CNT_RX_OK_BYTES_CNT(x)  (x)


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
#define VTSS_DEV10G_DEV_STATISTICS_40BIT_RX_OK_BYTES_MSB_CNT(target)  VTSS_IOREG(target,0x38)

/** 
 * \brief
 * The numberof received bytes in good frames - MSBs only.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_40BIT_RX_OK_BYTES_MSB_CNT . RX_OK_BYTES_MSB_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_40BIT_RX_OK_BYTES_MSB_CNT_RX_OK_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEV10G_DEV_STATISTICS_40BIT_RX_OK_BYTES_MSB_CNT_RX_OK_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEV10G_DEV_STATISTICS_40BIT_RX_OK_BYTES_MSB_CNT_RX_OK_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Rx Bad Byte Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_40BIT:RX_BAD_BYTES_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_40BIT_RX_BAD_BYTES_CNT(target)  VTSS_IOREG(target,0x39)

/** 
 * \brief
 * The number of received bytes in bad frames.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_40BIT_RX_BAD_BYTES_CNT . RX_BAD_BYTES_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_40BIT_RX_BAD_BYTES_CNT_RX_BAD_BYTES_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_40BIT_RX_BAD_BYTES_CNT_RX_BAD_BYTES_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_40BIT_RX_BAD_BYTES_CNT_RX_BAD_BYTES_CNT(x)  (x)


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
#define VTSS_DEV10G_DEV_STATISTICS_40BIT_RX_BAD_BYTES_MSB_CNT(target)  VTSS_IOREG(target,0x3a)

/** 
 * \brief
 * The number of received bytes in bad frames - MSBs only.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_40BIT_RX_BAD_BYTES_MSB_CNT . RX_BAD_BYTES_MSB_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_40BIT_RX_BAD_BYTES_MSB_CNT_RX_BAD_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEV10G_DEV_STATISTICS_40BIT_RX_BAD_BYTES_MSB_CNT_RX_BAD_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEV10G_DEV_STATISTICS_40BIT_RX_BAD_BYTES_MSB_CNT_RX_BAD_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Tx Byte Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_40BIT:TX_OUT_BYTES_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_40BIT_TX_OUT_BYTES_CNT(target)  VTSS_IOREG(target,0x3b)

/** 
 * \brief
 * The number of bytes transmitted (good, bad and framing).
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_40BIT_TX_OUT_BYTES_CNT . TX_OUT_BYTES_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_40BIT_TX_OUT_BYTES_CNT_TX_OUT_BYTES_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_40BIT_TX_OUT_BYTES_CNT_TX_OUT_BYTES_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_40BIT_TX_OUT_BYTES_CNT_TX_OUT_BYTES_CNT(x)  (x)


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
#define VTSS_DEV10G_DEV_STATISTICS_40BIT_TX_OUT_BYTES_MSB_CNT(target)  VTSS_IOREG(target,0x3c)

/** 
 * \brief
 * The number of bytes transmitted (good, bad, framing) - MSBs only.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_40BIT_TX_OUT_BYTES_MSB_CNT . TX_OUT_BYTES_MSB_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_40BIT_TX_OUT_BYTES_MSB_CNT_TX_OUT_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEV10G_DEV_STATISTICS_40BIT_TX_OUT_BYTES_MSB_CNT_TX_OUT_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEV10G_DEV_STATISTICS_40BIT_TX_OUT_BYTES_MSB_CNT_TX_OUT_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Tx OK Byte Counter
 *
 * \details
 * Register: \a DEV10G:DEV_STATISTICS_40BIT:TX_OK_BYTES_CNT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_STATISTICS_40BIT_TX_OK_BYTES_CNT(target)  VTSS_IOREG(target,0x3d)

/** 
 * \brief
 * The number of bytes transmitted successfully.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_40BIT_TX_OK_BYTES_CNT . TX_OK_BYTES_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_40BIT_TX_OK_BYTES_CNT_TX_OK_BYTES_CNT(x)  (x)
#define  VTSS_M_DEV10G_DEV_STATISTICS_40BIT_TX_OK_BYTES_CNT_TX_OK_BYTES_CNT     0xffffffff
#define  VTSS_X_DEV10G_DEV_STATISTICS_40BIT_TX_OK_BYTES_CNT_TX_OK_BYTES_CNT(x)  (x)


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
#define VTSS_DEV10G_DEV_STATISTICS_40BIT_TX_OK_BYTES_MSB_CNT(target)  VTSS_IOREG(target,0x3e)

/** 
 * \brief
 * The numbe rof transmitted bytes transmitted successfully - MSBs only.
 *
 * \details 
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DEV10G_DEV_STATISTICS_40BIT_TX_OK_BYTES_MSB_CNT . TX_OK_BYTES_MSB_CNT
 */
#define  VTSS_F_DEV10G_DEV_STATISTICS_40BIT_TX_OK_BYTES_MSB_CNT_TX_OK_BYTES_MSB_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEV10G_DEV_STATISTICS_40BIT_TX_OK_BYTES_MSB_CNT_TX_OK_BYTES_MSB_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEV10G_DEV_STATISTICS_40BIT_TX_OK_BYTES_MSB_CNT_TX_OK_BYTES_MSB_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

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
#define VTSS_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL(target)  VTSS_IOREG(target,0x3f)

/** 
 * \brief
 * Backplane Ethernet: Enable parallel detection mode for autonegotiation
 *
 * \details 
 * '0':  Parallel detection mode disabled
 * '1': Parallel detection mode enabled
 *
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL . PARDET_MODE_ENA
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_PARDET_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_PARDET_MODE_ENA  VTSS_BIT(23)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_PARDET_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * This field is used to configure the MAC and PCS Rx/Tx clock frequencies.
 *
 * \details 
 * '100':  XAUI/RXAUI 10 Gbps or 12Gbps OXAUI
 * '110':  Both MAC and PCS Rx/Tx clocks are disabled
 * '111':  XFI 10 Gbps
 * Unused values are reserved.
 *
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL . SPEED_SEL
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_SPEED_SEL(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_SPEED_SEL     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_SPEED_SEL(x)  VTSS_EXTRACT_BITFIELD(x,20,3)

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
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL . PCS_TX_RST
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_TX_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_TX_RST  VTSS_BIT(12)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_TX_RST(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

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
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL . PCS_RX_RST
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_RX_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_RX_RST  VTSS_BIT(8)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_PCS_RX_RST(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

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
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL . MAC_TX_RST
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_TX_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_TX_RST  VTSS_BIT(4)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_TX_RST(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

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
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL . MAC_RX_RST
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_RX_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_RX_RST  VTSS_BIT(0)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_DEV_RST_CTRL_MAC_RX_RST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Port Proetection Configuration Register
 *
 * \details
 * When port protedction is enabled the device will snoop and transmit data
 * destined for another device 10G identified by port_protect_id.
 *
 * Register: \a DEV10G:DEV_CFG_STATUS:DEV_PORT_PROTECT
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_CFG_STATUS_DEV_PORT_PROTECT(target)  VTSS_IOREG(target,0x40)

/** 
 * \brief
 * Indicates from which port egress data must be copied and transmitted at
 * this Ethernet port.
 * The port from which egress data is copied must always be a port that is
 * closer to the ASM. I.e. DEV(X) may be configured to snoop egress data
 * destined for DEV(X+n), where DEV(X+n) is closer to the ASM - but NOT
 * vice versa.
 *
 * \details 
 * 0: Reserved
 * 1: Egress data destined for DEV(1) is also transmitted by this device.
 * 2: Egress data destined for DEV(2) is also transmitted by this device.
 * ..
 *
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_DEV_PORT_PROTECT . PORT_PROTECT_ID
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_PORT_PROTECT_PORT_PROTECT_ID(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_PORT_PROTECT_PORT_PROTECT_ID     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_DEV_PORT_PROTECT_PORT_PROTECT_ID(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

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
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_DEV_PORT_PROTECT . PORT_PROTECT_ENA
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_PORT_PROTECT_PORT_PROTECT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_PORT_PROTECT_PORT_PROTECT_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_DEV_PORT_PROTECT_PORT_PROTECT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


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
#define VTSS_DEV10G_DEV_CFG_STATUS_DEV_LB_CFG(target)  VTSS_IOREG(target,0x41)

/** 
 * \brief
 * An internal loopback from the igress Taxi bus to the egress Taxi bus can
 * be enabled.
 *
 * \details 
 * '0': Loopback from Taxi ingress bus to Taxi egress bus disabled
 * '1': Loopback from Taxi ingress bus to Taxi egress bus enabled
 *
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_DEV_LB_CFG . TAXI_PHY_LB_ENA
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_LB_CFG_TAXI_PHY_LB_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_LB_CFG_TAXI_PHY_LB_ENA  VTSS_BIT(4)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_DEV_LB_CFG_TAXI_PHY_LB_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * An internal loopback from the egress Taxi bus to the ingress Taxi bus
 * can be enabled.
 *
 * \details 
 * '0': Loopback from Taxi egress to Taxi ingress is disabled
 * '1': Loopback from Taxi egress to Taxi ingress is enabled
 *
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_DEV_LB_CFG . TAXI_HOST_LB_ENA
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_LB_CFG_TAXI_HOST_LB_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_LB_CFG_TAXI_HOST_LB_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_DEV_LB_CFG_TAXI_HOST_LB_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Debug Configuration Register
 *
 * \details
 * Register: \a DEV10G:DEV_CFG_STATUS:DEV_MISC_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_CFG_STATUS_DEV_MISC_CFG(target)  VTSS_IOREG(target,0x42)

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
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_DEV_MISC_CFG . TX_FCS_UPDATE_SEL
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_MISC_CFG_TX_FCS_UPDATE_SEL(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_MISC_CFG_TX_FCS_UPDATE_SEL     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_DEV_MISC_CFG_TX_FCS_UPDATE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * Clears RX_RESYNC_MAX_FILL_LVL that holds the max. fill level of RX
 * RESYNC FIFO. This is a on shot bit automatically cleared by HW.
 *
 * \details 
 * '0': No action
 * '1': clears RX_RESYNC_MAX_FILL_LVL (Bit is automatically cleared)
 *
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_DEV_MISC_CFG . RX_RESYNC_MAX_FILL_LVL_CLR
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_MISC_CFG_RX_RESYNC_MAX_FILL_LVL_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_MISC_CFG_RX_RESYNC_MAX_FILL_LVL_CLR  VTSS_BIT(13)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_DEV_MISC_CFG_RX_RESYNC_MAX_FILL_LVL_CLR(x)  VTSS_EXTRACT_BITFIELD(x,13,1)


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
#define VTSS_DEV10G_DEV_CFG_STATUS_DEV_STICKY(target)  VTSS_IOREG(target,0x43)

/** 
 * \brief
 * Indicates if an overflow has occured in the ingress resynchronization
 * FIFO.
 * Writing a '1' clears the sticky bit.
 *
 * \details 
 * '0': No overflow has occurred in the ingress resynchronization FIFO.
 * '1': An overflow has occurred in the ingress resynchronization FIFO.
 *
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_DEV_STICKY . RX_RESYNC_FIFO_OFLW_STICKY
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_STICKY_RX_RESYNC_FIFO_OFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_STICKY_RX_RESYNC_FIFO_OFLW_STICKY  VTSS_BIT(12)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_DEV_STICKY_RX_RESYNC_FIFO_OFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Indicates that a missing SOF has been detected in the Rx path of the
 * DEV10G.
 * Writing a '1' clears the sticky bit.
 *
 * \details 
 * '0': No missing SOF detected
 * '1': Missing SOF indication detected in Rx path of DEV10G.
 *
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_DEV_STICKY . RX_SOF_STICKY
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_STICKY_RX_SOF_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_STICKY_RX_SOF_STICKY  VTSS_BIT(10)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_DEV_STICKY_RX_SOF_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Indicates that a missing EOF has been detected.
 * Writing a '1' clears the sticky bit.
 *
 * \details 
 * '0': No EOF error detected
 * '1': Missing EOF indication detected in Rx path of DEV10G.
 *
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_DEV_STICKY . RX_EOF_STICKY
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_STICKY_RX_EOF_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_STICKY_RX_EOF_STICKY  VTSS_BIT(8)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_DEV_STICKY_RX_EOF_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Indicates that a missing EOF has been detected.
 * Writing a '1' clears the sticky bit.
 *
 * \details 
 * '0': No EOF error detected
 * '1': Missing EOF indication detected in Tx path of DEV10G.
 *
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_DEV_STICKY . TX_EOF_STICKY
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_STICKY_TX_EOF_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_STICKY_TX_EOF_STICKY  VTSS_BIT(3)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_DEV_STICKY_TX_EOF_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Indicates that a missing SOF has been detected in the Tx path of the
 * DEV10G.
 * Writing a '1' clears the sticky bit.
 *
 * \details 
 * '0': No missing SOF detected
 * '1': Missing SOF indication detected in Tx path of DEV10G.
 *
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_DEV_STICKY . TX_SOF_STICKY
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_STICKY_TX_SOF_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_STICKY_TX_SOF_STICKY  VTSS_BIT(2)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_DEV_STICKY_TX_SOF_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


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
#define VTSS_DEV10G_DEV_CFG_STATUS_INTR(target)  VTSS_IOREG(target,0x44)

/** 
 * \brief
 * SerDes 10G, Base-R interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR . SD10G_BR_INTR
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_SD10G_BR_INTR(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_SD10G_BR_INTR  VTSS_BIT(7)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_SD10G_BR_INTR(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * SerDes 10G, server signal failure interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR . SD10G_SSF_INTR
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_SD10G_SSF_INTR(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_SD10G_SSF_INTR  VTSS_BIT(6)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_SD10G_SSF_INTR(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * SerDes 10G, KR interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR . SD10G_KR_INTR
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_SD10G_KR_INTR(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_SD10G_KR_INTR  VTSS_BIT(5)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_SD10G_KR_INTR(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Aggregate of BaseR PCS indications, see PCS_10GBASE_R::PCS_INTR_STAT and
 * PCS_10GBASE_R::PCS_INTR_MASK for more information. This field is set
 * when any BaseR PCS interrupt indication is active and enabled.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR . PCS_BR_INTR
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_PCS_BR_INTR(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_PCS_BR_INTR  VTSS_BIT(4)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_PCS_BR_INTR(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * PCS10G, PCS1G: TX Low Power Idle mode has changed
 *
 * \details 
 * 0 = no indication
 * 1 = active indication
 *
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR . TX_LPI_INTR
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_TX_LPI_INTR(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_TX_LPI_INTR  VTSS_BIT(3)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_TX_LPI_INTR(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * PCS10G, PCS1G: RX Low Power Idle mode has changed
 *
 * \details 
 * 0 = no indication
 * 1 = active indication
 *
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR . RX_LPI_INTR
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_RX_LPI_INTR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_RX_LPI_INTR  VTSS_BIT(2)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_RX_LPI_INTR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Link status is up (source: PCS1G, PCS10G or PCS2x6G depending on current
 * DEV10G mode)
 *
 * \details 
 * 0 = no indication
 * 1 = active indication
 *
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR . LINK_UP_INTR
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_LINK_UP_INTR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_LINK_UP_INTR  VTSS_BIT(1)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_LINK_UP_INTR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Link status is down (source: PCS1G, PCS10G or PCS2x6G depending on
 * current DEV10G mode)
 *
 * \details 
 * 0 = no indication
 * 1 = active indication
 *
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR . LINK_DWN_INTR
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_LINK_DWN_INTR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_LINK_DWN_INTR  VTSS_BIT(0)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_LINK_DWN_INTR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


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
#define VTSS_DEV10G_DEV_CFG_STATUS_INTR_ENA(target)  VTSS_IOREG(target,0x45)

/** 
 * \brief
 * Set to enable propagation of SerDes 10G, Base-R interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR_ENA . SD10G_BR_INTR_ENA
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_ENA_SD10G_BR_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_ENA_SD10G_BR_INTR_ENA  VTSS_BIT(7)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_ENA_SD10G_BR_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Set to enable propagation of SerDes 10G, server signal failure
 * interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR_ENA . SD10G_SSF_INTR_ENA
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_ENA_SD10G_SSF_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_ENA_SD10G_SSF_INTR_ENA  VTSS_BIT(6)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_ENA_SD10G_SSF_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Set to enable propagation of SerDes 10G, KR interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR_ENA . SD10G_KR_INTR_ENA
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_ENA_SD10G_KR_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_ENA_SD10G_KR_INTR_ENA  VTSS_BIT(5)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_ENA_SD10G_KR_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Set to enable propagation of PCS_BR interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR_ENA . PCS_BR_INTR_ENA
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_ENA_PCS_BR_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_ENA_PCS_BR_INTR_ENA  VTSS_BIT(4)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_ENA_PCS_BR_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set to enable propagation of TX_LPI interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR_ENA . TX_LPI_INTR_ENA
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_ENA_TX_LPI_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_ENA_TX_LPI_INTR_ENA  VTSS_BIT(3)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_ENA_TX_LPI_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set to enable propagation of RX_LPI interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR_ENA . RX_LPI_INTR_ENA
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_ENA_RX_LPI_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_ENA_RX_LPI_INTR_ENA  VTSS_BIT(2)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_ENA_RX_LPI_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set to enable propagation of LINK_UP interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR_ENA . LINK_UP_INTR_ENA
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_ENA_LINK_UP_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_ENA_LINK_UP_INTR_ENA  VTSS_BIT(1)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_ENA_LINK_UP_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set to enable propagation of LINK_DWN interrupt.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR_ENA . LINK_DWN_INTR_ENA
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_ENA_LINK_DWN_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_ENA_LINK_DWN_INTR_ENA  VTSS_BIT(0)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_ENA_LINK_DWN_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


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
#define VTSS_DEV10G_DEV_CFG_STATUS_INTR_IDENT(target)  VTSS_IOREG(target,0x46)

/** 
 * \brief
 * Set if SD10G_BR interrupt is currently active (indicating interrupt
 * towards higher level interrupt controller).
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR_IDENT . SD10G_BR_INTR_IDENT
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_IDENT_SD10G_BR_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_IDENT_SD10G_BR_INTR_IDENT  VTSS_BIT(7)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_IDENT_SD10G_BR_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Set if SD10G_SSF interrupt is currently active (indicating interrupt
 * towards higher level interrupt controller).
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR_IDENT . SD10G_SSF_INTR_IDENT
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_IDENT_SD10G_SSF_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_IDENT_SD10G_SSF_INTR_IDENT  VTSS_BIT(6)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_IDENT_SD10G_SSF_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Set if SD10G_KR interrupt is currently active (indicating interrupt
 * towards higher level interrupt controller).
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR_IDENT . SD10G_KR_INTR_IDENT
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_IDENT_SD10G_KR_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_IDENT_SD10G_KR_INTR_IDENT  VTSS_BIT(5)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_IDENT_SD10G_KR_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Set if PCS_BR interrupt is currently active (indicating interrupt
 * towards higher level interrupt controller).
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR_IDENT . PCS_BR_INTR_IDENT
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_IDENT_PCS_BR_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_IDENT_PCS_BR_INTR_IDENT  VTSS_BIT(4)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_IDENT_PCS_BR_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set if TX_LPI interrupt is currently active (indicating interrupt
 * towards higher level interrupt controller).
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR_IDENT . TX_LPI_INTR_IDENT
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_IDENT_TX_LPI_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_IDENT_TX_LPI_INTR_IDENT  VTSS_BIT(3)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_IDENT_TX_LPI_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set if RX_LPI interrupt is currently active (indicating interrupt
 * towards higher level interrupt controller).
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR_IDENT . RX_LPI_INTR_IDENT
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_IDENT_RX_LPI_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_IDENT_RX_LPI_INTR_IDENT  VTSS_BIT(2)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_IDENT_RX_LPI_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set if LINK_UP interrupt is currently active (indicating interrupt
 * towards higher level interrupt controller).
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR_IDENT . LINK_UP_INTR_IDENT
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_IDENT_LINK_UP_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_IDENT_LINK_UP_INTR_IDENT  VTSS_BIT(1)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_IDENT_LINK_UP_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set if LINK_DWN interrupt is currently active (indicating interrupt
 * towards higher level interrupt controller).
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_INTR_IDENT . LINK_DWN_INTR_IDENT
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_INTR_IDENT_LINK_DWN_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_INTR_IDENT_LINK_DWN_INTR_IDENT  VTSS_BIT(0)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_INTR_IDENT_LINK_DWN_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Ingress (receive) Path Status Register
 *
 * \details
 * Register: \a DEV10G:DEV_CFG_STATUS:DEV_RX_STATUS
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_CFG_STATUS_DEV_RX_STATUS(target)  VTSS_IOREG(target,0x47)

/** 
 * \brief
 * Maximum fill level of Rx resync FIFO. Fill level can be cleared by
 * writing to RX_RESYNC_MAX_FILL_LVL_CLR bit.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_DEV_RX_STATUS . RX_RESYNC_MAX_FILL_LVL
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_DEV_RX_STATUS_RX_RESYNC_MAX_FILL_LVL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_DEV_RX_STATUS_RX_RESYNC_MAX_FILL_LVL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_DEV_RX_STATUS_RX_RESYNC_MAX_FILL_LVL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Control Energy Efficient Ethernet operation.
 *
 * \details
 * Register: \a DEV10G:DEV_CFG_STATUS:EEE_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_CFG_STATUS_EEE_CFG(target)  VTSS_IOREG(target,0x48)

/** 
 * \brief
 * Enable EEE operation on the port.
 * 
 * A port enters the low power mode when no egress queues have data ready.
 * 
 * The port is activated when one of the following conditions is true:
 * - A queue has been non-empty for EEE_TIMER_AGE.
 * - A queue has more than EEE_HIGH_FRAMES frames pending.
 * - A queue has more than EEE_HIGH_BYTES bytes pending.
 * - A queue is marked as a fast queue, and has data pending.

 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_EEE_CFG . EEE_ENA
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_EEE_CFG_EEE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_EEE_CFG_EEE_ENA  VTSS_BIT(22)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_EEE_CFG_EEE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Maximum time frames in any queue must wait before the port is activated.
 * The default value corresponds to 48 us.

 *
 * \details 
 * Time = 4**(EEE_TIMER_AGE/16) * (EEE_TIMER_AGE mod 16) microseconds
 *
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_EEE_CFG . EEE_TIMER_AGE
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_AGE(x)  VTSS_ENCODE_BITFIELD(x,15,7)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_AGE     VTSS_ENCODE_BITMASK(15,7)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_AGE(x)  VTSS_EXTRACT_BITFIELD(x,15,7)

/** 
 * \brief
 * Time from the egress port is activated until frame transmission is
 * restarted. Default value corresponds to 16 us.
 *
 * \details 
 * Time = 4**(EEE_TIMER_WAKEUP/16) * (EEE_TIMER_WAKEUP mod 16) microseconds
 *
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_EEE_CFG . EEE_TIMER_WAKEUP
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_WAKEUP(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_WAKEUP     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_WAKEUP(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/** 
 * \brief
 * When all queues are empty, the port is kept active until this time has
 * passed. Default value corresponds to 5 us.
 *
 * \details 
 * Time = 4**(EEE_TIMER_HOLDOFF/16) * (EEE_TIMER_HOLDOFF mod 16)
 * microseconds
 *
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_EEE_CFG . EEE_TIMER_HOLDOFF
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_HOLDOFF(x)  VTSS_ENCODE_BITFIELD(x,1,7)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_HOLDOFF     VTSS_ENCODE_BITMASK(1,7)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_EEE_CFG_EEE_TIMER_HOLDOFF(x)  VTSS_EXTRACT_BITFIELD(x,1,7)

/** 
 * \brief
 * Status bit indicating whether port is in low-power-idle due to the LPI
 * algorithm (EEE_CFG). If set, transmissions are held back.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_EEE_CFG . PORT_LPI
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_EEE_CFG_PORT_LPI(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_EEE_CFG_PORT_LPI  VTSS_BIT(0)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_EEE_CFG_PORT_LPI(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief selects mode for which status counter will count the coresponding frames on RX and TX
 *
 * \details
 * Register: \a DEV10G:DEV_CFG_STATUS:PFC_PAUSE_MODE_CTRL
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_CFG_STATUS_PFC_PAUSE_MODE_CTRL(target)  VTSS_IOREG(target,0x49)

/** 
 * \brief
 * '0' : counters will be having number of pause frame received/transmitted
 * '1' : counters will be having number of PFC frame received/transmitted
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_PFC_PAUSE_MODE_CTRL . PFC_PAUSE_MODE_SELECT
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_PFC_PAUSE_MODE_CTRL_PFC_PAUSE_MODE_SELECT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_PFC_PAUSE_MODE_CTRL_PFC_PAUSE_MODE_SELECT  VTSS_BIT(0)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_PFC_PAUSE_MODE_CTRL_PFC_PAUSE_MODE_SELECT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PTP Configuration per port
 *
 * \details
 * Register: \a DEV10G:DEV_CFG_STATUS:PTP_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_CFG_STATUS_PTP_CFG(target)  VTSS_IOREG(target,0x4a)

/** 
 * \brief
 * Enable PTP on the port
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_PTP_CFG . PTP_ENA
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_PTP_CFG_PTP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_PTP_CFG_PTP_ENA  VTSS_BIT(20)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_PTP_CFG_PTP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Configures the time domain this port is assigned to. This domain
 * assignment must be made before the central counters in DEVCPU block is
 * enabled.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_PTP_CFG . PTP_DOM
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_PTP_CFG_PTP_DOM(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_PTP_CFG_PTP_DOM     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_PTP_CFG_PTP_DOM(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/** 
 * \brief
 * Time in ns to subtract from timestamper in the ingress direction to
 * compensate for static delay through the physical encoding layers.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_PTP_CFG . PTP_RX_IO_DLY
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_PTP_CFG_PTP_RX_IO_DLY(x)  VTSS_ENCODE_BITFIELD(x,9,9)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_PTP_CFG_PTP_RX_IO_DLY     VTSS_ENCODE_BITMASK(9,9)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_PTP_CFG_PTP_RX_IO_DLY(x)  VTSS_EXTRACT_BITFIELD(x,9,9)

/** 
 * \brief
 * Time in ns to add to timestamper in the egress direction to compensate
 * for static delay through the physical encoding layers.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_PTP_CFG . PTP_TX_IO_DLY
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_PTP_CFG_PTP_TX_IO_DLY(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_PTP_CFG_PTP_TX_IO_DLY     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_PTP_CFG_PTP_TX_IO_DLY(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/** 
 * \brief PTP Predictor Configuration per port
 *
 * \details
 * Register: \a DEV10G:DEV_CFG_STATUS:PTP_PREEDICT_CFG
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_CFG_STATUS_PTP_PREEDICT_CFG(target)  VTSS_IOREG(target,0x4b)

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
 * others: Disabled
 *
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_PTP_PREEDICT_CFG . PTP_PHASE_PREDICT_CFG
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_PTP_PREEDICT_CFG_PTP_PHASE_PREDICT_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_PTP_PREEDICT_CFG_PTP_PHASE_PREDICT_CFG     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_PTP_PREEDICT_CFG_PTP_PHASE_PREDICT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief PTP Bit time accuracy configuration
 *
 * \details
 * Register: \a DEV10G:DEV_CFG_STATUS:PTP_CFG_BTDLY
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_CFG_STATUS_PTP_CFG_BTDLY(target)  VTSS_IOREG(target,0x4c)

/** 
 * \brief
 * Time in 100ps to subtract from timestamper in the ingress direction to
 * compensate for static delay through the physical encoding layers.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_PTP_CFG_BTDLY . PTP_RX_BT_DLY
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_PTP_CFG_BTDLY_PTP_RX_BT_DLY(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_PTP_CFG_BTDLY_PTP_RX_BT_DLY     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_PTP_CFG_BTDLY_PTP_RX_BT_DLY(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Time in 100ps to subtract from timestamper in the egress direction to
 * compensate for static delay through the physical encoding layers.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_PTP_CFG_BTDLY . PTP_TX_BT_DLY
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_PTP_CFG_BTDLY_PTP_TX_BT_DLY(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_PTP_CFG_BTDLY_PTP_TX_BT_DLY     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_PTP_CFG_BTDLY_PTP_TX_BT_DLY(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Gearbox starting value when 6466b fifo is suspened in the ingress
 * direction.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_PTP_CFG_BTDLY . PTP_RX_GEARBOX_OFS
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_PTP_CFG_BTDLY_PTP_RX_GEARBOX_OFS(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_PTP_CFG_BTDLY_PTP_RX_GEARBOX_OFS     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_PTP_CFG_BTDLY_PTP_RX_GEARBOX_OFS(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Gearbox starting value when 6466b fifo is suspended in the egress
 * direction.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_PTP_CFG_BTDLY . PTP_TX_GEARBOX_OFS
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_PTP_CFG_BTDLY_PTP_TX_GEARBOX_OFS(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_PTP_CFG_BTDLY_PTP_TX_GEARBOX_OFS     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_PTP_CFG_BTDLY_PTP_TX_GEARBOX_OFS(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief PTP Events per port
 *
 * \details
 * Register: \a DEV10G:DEV_CFG_STATUS:PTP_EVENTS
 *
 * @param target A \a ::vtss_target_DEV10G_e target
 */
#define VTSS_DEV10G_DEV_CFG_STATUS_PTP_EVENTS(target)  VTSS_IOREG(target,0x4d)

/** 
 * \brief
 * The correction field update went out of range. Valid range is -2^47 to
 * 2^48-1. The frame CF will be changed to the maximum value. This range
 * check is bypassed if ADDS48 mode is in use on the ingress or egress
 * port.
 *
 * \details 
 * Field: ::VTSS_DEV10G_DEV_CFG_STATUS_PTP_EVENTS . CF_TOO_BIG_STICKY
 */
#define  VTSS_F_DEV10G_DEV_CFG_STATUS_PTP_EVENTS_CF_TOO_BIG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEV10G_DEV_CFG_STATUS_PTP_EVENTS_CF_TOO_BIG_STICKY  VTSS_BIT(0)
#define  VTSS_X_DEV10G_DEV_CFG_STATUS_PTP_EVENTS_CF_TOO_BIG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_SERVALT_REGS_DEV10G_H_ */
