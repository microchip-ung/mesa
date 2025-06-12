// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _LAN80XX_MALIBU25G_REGS_HOST_MAC_H_
#define _LAN80XX_MALIBU25G_REGS_HOST_MAC_H_

#include "regs_lan8042_common.h"

/***********************************************************************
 *
 * Target: \a HOST_MAC
 *
 * Full duplex (half duplex is not supported) 10/100/1000/10000 MAC registers.
 *
 ***********************************************************************/

/**
 * Register Group: \a HOST_MAC:HOST_MAC_CONFIG
 *
 * 10G MAC configuration registers
 */


/**
 * \brief MAC enable register
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_CONFIG:HOST_MAC_MAC_ENA_CFG
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MAC_ENA_CFG   LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf100)

/**
 * \brief
 * MAC Rx clock enable
 *
 * \details
 * 0: All clocks for this module with the exception of CSR clock are
 * disabled
 * 1: All clocks for this module are enabled
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_ENA_CFG . RX_CLK_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_CLK_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_CLK_ENA  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_CLK_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * MAC Tx clock enable
 *
 * \details
 * 0: All clocks for this module with the exception of CSR clock are
 * disabled
 * 1: All clocks for this module are enabled
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_ENA_CFG . TX_CLK_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_CLK_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_CLK_ENA  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_CLK_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * MAC Rx software reset
 *
 * \details
 * 0: Block operates normally
 * 1: All logic (other than CSR target) is held in reset, clocks are not
 * disabled
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_ENA_CFG . RX_SW_RST
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_SW_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_SW_RST  LAN80XX_BIT(8)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_SW_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * MAC Tx software reset
 *
 * \details
 * 0: Block operates normally
 * 1: All logic (other than CSR target) is held in reset, clocks are not
 * disabled
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_ENA_CFG . TX_SW_RST
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_SW_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),12,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_SW_RST  LAN80XX_BIT(12)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_SW_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Enable receiver
 *
 * \details
 * 0: Disabled
 * 1: Enabled
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_ENA_CFG . RX_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),16,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_ENA  LAN80XX_BIT(16)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Enable transmitter
 *
 * \details
 * 0: Disabled
 * 1: Enabled
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_ENA_CFG . TX_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),20,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_ENA  LAN80XX_BIT(20)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,20,1)


/**
 * \brief Mode configuration register
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_CONFIG:HOST_MAC_MAC_MODE_CFG
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MAC_MODE_CFG  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf101)

/**
 * \brief
 * The value used to schedule the next special control word when
 * FORCE_CW_UPDATE=1. The recomended value is 10.
 *
 * \details
 * n: Wait of n clocks before scheduling next control word
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_MODE_CFG . FORCE_CW_UPDATE_INTERVAL
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_MODE_CFG_FORCE_CW_UPDATE_INTERVAL(x)  LAN80XX_ENCODE_BITFIELD(x,20,10)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_MODE_CFG_FORCE_CW_UPDATE_INTERVAL     LAN80XX_ENCODE_BITMASK(20,10)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_MODE_CFG_FORCE_CW_UPDATE_INTERVAL(x)  LAN80XX_EXTRACT_BITFIELD(x,20,10)

/**
 * \brief
 * Configuration bit for enabling generation of special control words (CW)
 * regularly with minimum gap of FORCE_CW_UPDATE_INTERVAL clocks
 *
 * \details
 * '0': Generation of CW regulary is disabled.
 * '1': Generation of CW regulary is enabled.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_MODE_CFG . FORCE_CW_UPDATE
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_MODE_CFG_FORCE_CW_UPDATE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),16,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_MODE_CFG_FORCE_CW_UPDATE  LAN80XX_BIT(16)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_MODE_CFG_FORCE_CW_UPDATE(x)  LAN80XX_EXTRACT_BITFIELD(x,16,1)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_MODE_CFG . TUNNEL_PAUSE_FRAMES
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_MODE_CFG_TUNNEL_PAUSE_FRAMES(x)  LAN80XX_ENCODE_BITFIELD(!!(x),14,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_MODE_CFG_TUNNEL_PAUSE_FRAMES  LAN80XX_BIT(14)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_MODE_CFG_TUNNEL_PAUSE_FRAMES(x)  LAN80XX_EXTRACT_BITFIELD(x,14,1)

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
 * 2: HIH before SFD -  default CRC = 0xFB H0 H1 H2 H3 0x55 0x55 0xD5
 * 3: HIH after SFD - default CRC = 0xFB 0x55 0x55 0xD5 H0 H1 H2 H3
 * 4: HIH after SFD - HIH in CRC = 0xFB 0x55 0x55 0xD5 H0 H1 H2 H3
 * 5 - 7: reserved
 *
 * HIH is 4 bytes: H0 H1 H2 H3
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_MODE_CFG . MAC_PREAMBLE_CFG
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_MODE_CFG_MAC_PREAMBLE_CFG(x)  LAN80XX_ENCODE_BITFIELD(x,10,3)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_MODE_CFG_MAC_PREAMBLE_CFG     LAN80XX_ENCODE_BITMASK(10,3)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_MODE_CFG_MAC_PREAMBLE_CFG(x)  LAN80XX_EXTRACT_BITFIELD(x,10,3)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_MODE_CFG . MAC_IPG_CFG
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_MODE_CFG_MAC_IPG_CFG(x)  LAN80XX_ENCODE_BITFIELD(!!(x),6,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_MODE_CFG_MAC_IPG_CFG  LAN80XX_BIT(6)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_MODE_CFG_MAC_IPG_CFG(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_MODE_CFG . XGMII_GEN_MODE_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_MODE_CFG_XGMII_GEN_MODE_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_MODE_CFG_XGMII_GEN_MODE_ENA  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_MODE_CFG_XGMII_GEN_MODE_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * When asserted (=1) MAC10G must check HIH checksum and discard frames if
 * HIH checksum is not valid.When de-asserted (=0) MAC10G must disregard
 * the HIH checksum.
 *
 * \details
 * '0': MAC10G should disregard the HIH CKSM.
 * '1': MAC10G should discard any frame with invalid CKSM
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_MODE_CFG . HIH_CRC_CHECK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_MODE_CFG_HIH_CRC_CHECK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_MODE_CFG_HIH_CRC_CHECK  LAN80XX_BIT(2)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_MODE_CFG_HIH_CRC_CHECK(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * According to IEEE 802.3 clause 49, MAC drops frames whose length is less
 * than 64 bytes. So to allow these frames this bit needs to be set to
 * '1'.Note:1) MAC statistics will still reflect these frames as undersized
 * frames.2) Undersized frames with valid FCS are only allowed when this
 * bit is set to '1'. Frames with FCS error are still dropped.
 *
 * \details
 * 0: MAC drops undersized frames
 * 1: MAC passes through undersized frames
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_MODE_CFG . UNDERSIZED_FRAME_DROP_DIS
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_MODE_CFG_UNDERSIZED_FRAME_DROP_DIS(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_MODE_CFG_UNDERSIZED_FRAME_DROP_DIS  LAN80XX_BIT(1)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_MODE_CFG_UNDERSIZED_FRAME_DROP_DIS(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * When this value is 0 MAC10G follows 0-3 DIC algorithm to insert IPG,
 * averaging to 12.When this value is 1 MAC10G does not follow DIC
 * alogrithm for IPG insertion and, as a result, back pressure to host
 * block from kernel is not issued.
 *
 * \details
 * 0: IPG insertion in MAC10G is enabled
 * 1: IPG insertion in MAC10G is disabled
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_MODE_CFG . DISABLE_DIC
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_MODE_CFG_DISABLE_DIC(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_MODE_CFG_DISABLE_DIC  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_MODE_CFG_DISABLE_DIC(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Maximum length configuration register
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_CONFIG:HOST_MAC_MAC_MAXLEN_CFG
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MAC_MAXLEN_CFG  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf102)

/**
 * \brief
 * Configures the maximum length check to consider the number of VLAN tags
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
 *     Add 16 bytes to MAX_LEN when checking a quadruple tagged frame for
 * max frame length
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_MAXLEN_CFG . MAX_LEN_TAG_CHK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_MAXLEN_CFG_MAX_LEN_TAG_CHK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),16,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_MAXLEN_CFG_MAX_LEN_TAG_CHK  LAN80XX_BIT(16)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_MAXLEN_CFG_MAX_LEN_TAG_CHK(x)  LAN80XX_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Maximum frame length accepted by the receive module. If the length is
 * exceeded, it is indicated in the statistics engine (LONG_FRAME). The
 * maximum length is automatically adjusted to accommodate maximum sized
 * frames containing up to four VLAN tags, given that the MAC is configured
 * to be VLAN-aware by default. The maximum size is 10056 Bytes not
 * including VLAN tags.
 *
 * \details
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_MAXLEN_CFG . MAX_LEN
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_MAXLEN_CFG_MAX_LEN(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_MAXLEN_CFG_MAX_LEN     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_MAXLEN_CFG_MAX_LEN(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Tag number configuration register
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_CONFIG:HOST_MAC_MAC_NUM_TAGS_CFG
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MAC_NUM_TAGS_CFG  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf103)

/**
 * \brief
 * Number of consecutive VLAN tags supported by the MAC. The maximum value
 * is 4
 *
 * \details
 * 0: No tags are detected by MAC
 * n: Maximum of n consecutive VLAN Tags are detected by the MAC and
 * accordingly MAX LEN is modified for frame length calculations
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_NUM_TAGS_CFG . NUM_TAGS
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_NUM_TAGS_CFG_NUM_TAGS(x)  LAN80XX_ENCODE_BITFIELD(x,0,3)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_NUM_TAGS_CFG_NUM_TAGS     LAN80XX_ENCODE_BITMASK(0,3)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_NUM_TAGS_CFG_NUM_TAGS(x)  LAN80XX_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief VLAN/Service tag configuration register
 *
 * \details
 * The MAC can be configured to accept 0, 1, 2, 3 and 4 tags and the TAG
 * value can be user-defined.
 *
 * Register: \a HOST_MAC:HOST_MAC_CONFIG:HOST_MAC_MAC_TAGS_CFG
 *
 * @param ri Register: HOST_MAC_MAC_TAGS_CFG (??), 0-2
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MAC_TAGS_CFG(ri)  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf104 + (ri))

/**
 * \brief
 * Value (other than 0x8100 or 0x88A8) that is regarded as a VLAN/Service
 * tag. This value is used for all all tag positions.
 *
 * \details
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_TAGS_CFG . TAG_ID
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_TAGS_CFG_TAG_ID(x)  LAN80XX_ENCODE_BITFIELD(x,16,16)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_TAGS_CFG_TAG_ID     LAN80XX_ENCODE_BITMASK(16,16)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_TAGS_CFG_TAG_ID(x)  LAN80XX_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * Enables TAG_ID other than 0x8100 and 0x88A8 for tag comparison.
 *
 * \details
 * 0: The MAC does not take TAG_ID for tag identification
 * 1: The MAC looks for tag according to encoding of TAG_ID
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_TAGS_CFG . TAG_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_TAGS_CFG_TAG_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_TAGS_CFG_TAG_ENA  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_TAGS_CFG_TAG_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)


/**
 * \brief Advanced check configuration register
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_CONFIG:HOST_MAC_MAC_ADV_CHK_CFG
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf107)

/**
 * \brief
 * Extended end of packet check.Specifies the requirement for the Rx column
 * when holding an EOP character.
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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG . EXT_EOP_CHK_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_EXT_EOP_CHK_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),24,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_EXT_EOP_CHK_ENA  LAN80XX_BIT(24)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_EXT_EOP_CHK_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Enable extended start of packet check.Specifies the requirement for the
 * Rx column prior to the start of packet character.
 *
 * \details
 * 0: Ignore the value of Rx column at the XGMII interface before a start
 * of packet character.
 * 1: An IDLE column at the XGMII interface must be received before a start
 * of packet character for the MAC to detect a start of frame.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG . EXT_SOP_CHK_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_EXT_SOP_CHK_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),20,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_EXT_SOP_CHK_ENA  LAN80XX_BIT(20)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_EXT_SOP_CHK_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Enable start of frame delimiter check.Specifies the requirements for a
 * successful frame reception.
 *
 * \details
 * 0: Skip SFD check
 * MAC10G assumes that preamble is 8 bytes (including SOP & SFD) when SOP
 * is received. No checking of SFD is carried out.
 * 1: Enforce strict SFD/SMD check
 * The SFD must be D5 (express packet) or legal SMD (for preempted packet)
 * for a successful frame reception. MAC10G searches for SFD/SMD-S in lane
 * 3/7 or SMD_C in lane 2/6 after reception of SOP, before accepting frame
 * data. MAC10G searches for SFD/SMD-S/SMD-C+FRAG_NUM until
 * SFD/SMD-S/SMD-C+Frag_NUM is found or a control character is encountered.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG . SFD_CHK_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_SFD_CHK_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),16,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_SFD_CHK_ENA  LAN80XX_BIT(16)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_SFD_CHK_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,16,1)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG . PRM_SHK_CHK_DIS
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_PRM_SHK_CHK_DIS(x)  LAN80XX_ENCODE_BITFIELD(!!(x),12,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_PRM_SHK_CHK_DIS  LAN80XX_BIT(12)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_PRM_SHK_CHK_DIS(x)  LAN80XX_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Enable preamble check.Specifies the preamble requirements for a
 * successful frame reception.
 *
 * \details
 * 0: Skip preamble check.
 * A SOP control character is sufficient for a successful frame reception.
 * The minimum allowed preamble size is still 8 bytes (including SOP and
 * SFD/SMD-S/"SMD-C+FRAG_NUM") but the preamble bytes between the SOP and
 * the SFD can have any data value.
 * 1: Enable strict preamble check
 * The last 6 bytes of a preamble prior to the SFD or SMD-S must all be
 * equal to 0x55 or the last 5 bytes of preamble prior to the
 * "SMD-C+FRAG_NUM" must all be equal to 0x55 for a successful frame
 * reception.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG . PRM_CHK_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_PRM_CHK_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_PRM_CHK_ENA  LAN80XX_BIT(8)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_PRM_CHK_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Enable out of range error check.Determines whether a received frame
 * should be discarded if the frame length field is out of range.
 *
 * \details
 * 0: Ignore out of range errors
 * 1: Discard frame if the frame length field value is out of range
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG . OOR_ERR_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_OOR_ERR_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_OOR_ERR_ENA  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_OOR_ERR_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable in-range error check.Determines whether a received frame should
 * be discarded if the frame length does not match the frame PDU size.
 *
 * \details
 * 0: Do not error-mark frames with a frame length field that is
 * inconsistent with the actual frame length.
 * 1: Error-mark frames with inconsistent frame length fields and discard
 * them using the Rx queue system.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG . INR_ERR_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_INR_ERR_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_INR_ERR_ENA  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_INR_ERR_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Link fault signaling register
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_CONFIG:HOST_MAC_MAC_LFS_CFG
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MAC_LFS_CFG   LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf108)

/**
 * \brief
 * Inhibit Tx link fault signaling.Determine Tx behavior when a remote or
 * local link fault has been detected and LFS_MODE is set.Frames received
 * after a link fault signal are not transmitted on the XGMII interface
 * because link fault signaling requires special sequence ordered sets to
 * be transmitted during a link fault.When the receiver has cleared the
 * link fault state, the transmitter automatically starts to request and
 * successfully transmit frames if LFS_DIS_TX is not set.
 *
 * \details
 * 0: Continue to request frames from the FIFO after a link fault has been
 * detected.
 * 1: Cease to request frames from the FIFO after a link fault has been
 * detected.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_LFS_CFG . LFS_INH_TX
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_LFS_CFG_LFS_INH_TX(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_LFS_CFG_LFS_INH_TX  LAN80XX_BIT(8)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_LFS_CFG_LFS_INH_TX(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Disable Tx link fault signaling.Determine Tx behavior when a remote or
 * local link fault has been detected and both LFS_MODE and LFS_INH_TX are
 * asserted.
 *
 * \details
 * 0: Keep transmitter enabled during and after a link fault.
 * 1: Disable transmitte when a link fault is detected.
 * Software must actively enable the transmitter again by de-asserting
 * TX_ENA followed by an assertion of TX_ENA.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_LFS_CFG . LFS_DIS_TX
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_LFS_CFG_LFS_DIS_TX(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_LFS_CFG_LFS_DIS_TX  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_LFS_CFG_LFS_DIS_TX(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable unidirectional mode for link fault signaling.Enables the MAC to
 * transmit data during reception of local fault and remote fault ordered
 * sets from the PHY. In the unidirectional mode, frames are transmitted
 * separated by remote fault ordered sets when receiving local fault. They
 * are transmitted separated by IDLE symbols when receiving remote fault.
 *
 * \details
 * 0: Disable unidirectional mode link fault signaling.
 * 1: Enable unidirectional mode link fault signaling.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_LFS_CFG . LFS_UNIDIR_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_LFS_CFG_LFS_UNIDIR_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_LFS_CFG_LFS_UNIDIR_ENA  LAN80XX_BIT(3)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_LFS_CFG_LFS_UNIDIR_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_LFS_CFG . USE_LEADING_EDGE_DETECT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_LFS_CFG_USE_LEADING_EDGE_DETECT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_LFS_CFG_USE_LEADING_EDGE_DETECT  LAN80XX_BIT(2)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_LFS_CFG_USE_LEADING_EDGE_DETECT(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_LFS_CFG . SPURIOUS_Q_DIS
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_LFS_CFG_SPURIOUS_Q_DIS(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_LFS_CFG_SPURIOUS_Q_DIS  LAN80XX_BIT(1)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_LFS_CFG_SPURIOUS_Q_DIS(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable link fault signaling mode.Configure how the transmitter reacts on
 * received link fault indications.
 *
 * \details
 * 0: Ignore link faults detected by the MAC receiver module.
 * 1: React on detected link faults and transmit the appropriate sequence
 * ordered set.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_LFS_CFG . LFS_MODE_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_LFS_CFG_LFS_MODE_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_LFS_CFG_LFS_MODE_ENA  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_LFS_CFG_LFS_MODE_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Miscellaneous configuration register
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_CONFIG:HOST_MAC_MAC_LB_CFG
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MAC_LB_CFG    LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf109)

/**
 * \brief
 * Malibu-25G H3M loopbackEnables loopback from egress to ingress in the
 * device. The MAC Rx clock is automatically set equal to the MAC Tx clock
 * when the loopback is enabled.
 *
 * \details
 * 0: Host loopback disabled at XGMII interface.
 * 1: Host loopback enabled at XGMII interface.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_LB_CFG . XGMII_HOST_LB_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_LB_CFG_XGMII_HOST_LB_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_LB_CFG_XGMII_HOST_LB_ENA     LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_LB_CFG_XGMII_HOST_LB_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enables loopback from ingress to egres data path at XGMII interface.
 *
 * \details
 * '0': PHY Loopback Disabled at XGMII interface.
 * '1': PHY Loopback Enabled at XGMII interface.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_LB_CFG . XGMII_PHY_LB_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_LB_CFG_XGMII_PHY_LB_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_LB_CFG_XGMII_PHY_LB_ENA  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_LB_CFG_XGMII_PHY_LB_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Packet interface configuration register
 *
 * \details
 * Packet interface module configuration register
 *
 * Register: \a HOST_MAC:HOST_MAC_CONFIG:HOST_MAC_MAC_PKTINF_CFG
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf10a)

/**
 * \brief
 * Enables stripping of FCS in ingress traffic.
 *
 * \details
 * 0: FCS is not stripped.
 * 1: FCS is stripped in ingress.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG . STRIP_FCS_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_STRIP_FCS_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_STRIP_FCS_ENA  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_STRIP_FCS_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Enables FCS insertion in egress traffic.
 *
 * \details
 * 0: FCS is not added.
 * 1: FCS is added in egress direction.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG . INSERT_FCS_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_INSERT_FCS_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_INSERT_FCS_ENA  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_INSERT_FCS_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enables stripping of preamble from MAC frame in the ingress direction.
 *
 * \details
 * 0: Preamble is unaltered.
 * 1: Preamble is stripped in ingress direction.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG . STRIP_PREAMBLE_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_STRIP_PREAMBLE_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_STRIP_PREAMBLE_ENA  LAN80XX_BIT(8)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_STRIP_PREAMBLE_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Enables addition of standard preamble in egress direction.
 *
 * \details
 * 0: Standard preamble is not inserted.
 * 1: Standard preamble is added in egress direction.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG . INSERT_PREAMBLE_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_INSERT_PREAMBLE_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),12,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_INSERT_PREAMBLE_ENA  LAN80XX_BIT(12)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_INSERT_PREAMBLE_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Enables signaling of LPI received.
 *
 * \details
 * 0: Disable LPI received status.
 * 1: Enable LPI received status signaling.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG . LPI_RELAY_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_LPI_RELAY_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),16,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_LPI_RELAY_ENA  LAN80XX_BIT(16)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_LPI_RELAY_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Enables signaling of local fault state.
 *
 * \details
 * 0: Disable signaling of local fault state.
 * 1: Enable local fault state signaling.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG . LF_RELAY_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_LF_RELAY_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),20,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_LF_RELAY_ENA  LAN80XX_BIT(20)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_LF_RELAY_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Enables signaling of remote fault state.
 *
 * \details
 * 0: Disable signaling of remote fault state.
 * 1: Enable remote fault state signaling.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG . RF_RELAY_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_RF_RELAY_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),24,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_RF_RELAY_ENA  LAN80XX_BIT(24)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_RF_RELAY_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Enables padding frames during transmission. Frames with length less than
 * 64 are padded with zeros.
 *
 * \details
 * 0: Disable padding.
 * 1: Enable padding.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG . ENABLE_TX_PADDING
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_ENABLE_TX_PADDING(x)  LAN80XX_ENCODE_BITFIELD(!!(x),25,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_ENABLE_TX_PADDING  LAN80XX_BIT(25)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_ENABLE_TX_PADDING(x)  LAN80XX_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Enables padding received frames. Frames wtih length less than 64 are
 * padded with zeros.
 *
 * \details
 * 0: Disable padding.
 * 1: Enable padding.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG . ENABLE_RX_PADDING
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_ENABLE_RX_PADDING(x)  LAN80XX_ENCODE_BITFIELD(!!(x),26,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_ENABLE_RX_PADDING  LAN80XX_BIT(26)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_ENABLE_RX_PADDING(x)  LAN80XX_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * Enables insertion of 4 byte preamble if INSERT_PREAMBLE_ENA is set.
 * Followed by 4 byte preamble is DMAC.Preamble will be 4 bytes only if per
 * frame signal host_tx_4byte_preamble_i (at MAC10G packet interface) is
 * also asserted along with this configuration.
 *
 * \details
 * 0: Disable 4 byte preamble.
 * 1: Enable insertion of 4 byte preamble.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG . ENABLE_4BYTE_PREAMBLE
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_ENABLE_4BYTE_PREAMBLE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),27,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_ENABLE_4BYTE_PREAMBLE  LAN80XX_BIT(27)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_ENABLE_4BYTE_PREAMBLE(x)  LAN80XX_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Enable stalling for 1588 timestamped frame to ensure timestamped frames
 * undergo fixed latency through the MAC block.This configuration specifies
 * the number of enabled clock cycles to stall to achieve fixed latency in
 * MACsec bypass mode. The recommended value is 2.
 *
 * \details
 * 0: Stalling is disabled.
 * 1: 1 clock stall is generated.
 * ...
 * n: n clocks stall is generated.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG . MACSEC_BYPASS_NUM_PTP_STALL_CLKS
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_MACSEC_BYPASS_NUM_PTP_STALL_CLKS(x)  LAN80XX_ENCODE_BITFIELD(x,28,3)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_MACSEC_BYPASS_NUM_PTP_STALL_CLKS     LAN80XX_ENCODE_BITMASK(28,3)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_MACSEC_BYPASS_NUM_PTP_STALL_CLKS(x)  LAN80XX_EXTRACT_BITFIELD(x,28,3)

/**
 * \brief
 * Allow MCH encrypt_en bit to control MACsec bypass.
 *
 * \details
 * 0: MCH encrypt_en bit cannot control MACsec bypass.
 * 1: Allow MCH encrypt_en bit to control MACsec bypass.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG . MCH_MACSEC_BYPASS_EN
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_MCH_MACSEC_BYPASS_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),31,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_MCH_MACSEC_BYPASS_EN  LAN80XX_BIT(31)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_MCH_MACSEC_BYPASS_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,31,1)

/**
 * Register Group: \a HOST_MAC:HOST_MAC_PAUSE_CFG
 *
 * 10G MAC pause configuration registers
 */


/**
 * \brief Transmit pause frame control register
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_PAUSE_CFG:HOST_MAC_PAUSE_TX_FRAME_CONTROL
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf10b)

/**
 * \brief
 * Pause value used when generating pause frames (except XON frames in mode
 * 2).
 *
 * \details
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL . MAC_TX_PAUSE_VALUE
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_VALUE(x)  LAN80XX_ENCODE_BITFIELD(x,16,16)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_VALUE     LAN80XX_ENCODE_BITMASK(16,16)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_VALUE(x)  LAN80XX_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * Enables pause-generate module to wait for 10 clocks (for idle insertion)
 * before generating XOFF pause frame if MAC 10G is transmitting LPI
 * idles.This bit should be set only if LPI generation is forced in Kernel
 * 10G and a pause frame needs to be transmitted.
 *
 * \details
 * 0: No idles are inserted before pause frame.
 * 1: Idles are inserted before pause frame.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL . MAC_TX_WAIT_FOR_LPI_LOW
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_WAIT_FOR_LPI_LOW(x)  LAN80XX_ENCODE_BITFIELD(!!(x),12,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_WAIT_FOR_LPI_LOW  LAN80XX_BIT(12)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_WAIT_FOR_LPI_LOW(x)  LAN80XX_EXTRACT_BITFIELD(x,12,1)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL . MAC_TX_USE_PAUSE_STALL_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_USE_PAUSE_STALL_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_USE_PAUSE_STALL_ENA  LAN80XX_BIT(8)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_USE_PAUSE_STALL_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Used to force the pause frame generator to send duplicate pause frames
 * instead of one when enabled.  This mode is used to overcome a problem
 * with Smartbits inability to detect every pause frame.
 *
 * \details
 * 0 = Normal mode
 * 1 = Send duplicate pause frames
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL . MAC_TX_PAUSE_REPL_MODE
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_REPL_MODE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_REPL_MODE  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_REPL_MODE(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Force a pause frame with MAC_PAUSE_VALUE to be sent
 *
 * \details
 * 0 = Normal operation
 * 1 = Force a single pause frame to be sent, self clearing
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL . MAC_TX_PAUSE_FRC_FRAME
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_FRC_FRAME(x)  LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_FRC_FRAME  LAN80XX_BIT(2)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_FRC_FRAME(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL . MAC_TX_PAUSE_MODE
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_MODE(x)  LAN80XX_ENCODE_BITFIELD(x,0,2)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_MODE     LAN80XX_ENCODE_BITMASK(0,2)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_MODE(x)  LAN80XX_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Transmit pause frame control part 2 register
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_PAUSE_CFG:HOST_MAC_PAUSE_TX_FRAME_CONTROL_2
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_2  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf10c)

/**
 * \brief
 * Pause frame interval.Each count in the pause frame interval value
 * corresponds to one cycle of the MAC clock (PCS clock divided by 2),
 * typically 156.25 MHz (6.4 ns period). The interval is counted from the
 * end of one pause frame to the beginning of the next (assuming no other
 * Tx traffic). The internal pause interval timer is cleared when an XON
 * pause frame is sent in Tx pause mode 2.The pause interval value of
 * 0xffff gives the same pause frame interval as the pause interval value
 * of 0xfffe. Do not use a value of 0.
 *
 * \details
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_2 . MAC_TX_PAUSE_INTERVAL
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_2_MAC_TX_PAUSE_INTERVAL(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_2_MAC_TX_PAUSE_INTERVAL     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_2_MAC_TX_PAUSE_INTERVAL(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Receive pause frame control register
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_PAUSE_CFG:HOST_MAC_PAUSE_RX_FRAME_CONTROL
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf10d)

/**
 * \brief
 * Enable pause frame detection at XGMII interface
 *
 * \details
 * 0: Disable pause frame detection at XGMII interface
 * 1: Enable pause frame detection at XGMII interface
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL . MAC_RX_EARLY_PAUSE_DETECT_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_EARLY_PAUSE_DETECT_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),16,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_EARLY_PAUSE_DETECT_ENA  LAN80XX_BIT(16)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_EARLY_PAUSE_DETECT_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Configuration for XOFF indication before CRC check to meet pause
 * reaction time.XOFF detection is done at XGMII interface depending on
 * MAC_RX_EARLY_PAUSE_DETECT_ENA. Information of CRC check failed for the
 * XOFF pause frame is also passed with a separate side band signal and so
 * that the pause timer is reloaded with previous pause value. This bit is
 * unused if XOFF detection is done after the MAC.
 *
 * \details
 * 0: XOFF indication at XGMII is done after CRC check.
 * 1: XOFF indication ar XGMII is done before CRC check.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL . MAC_RX_PRE_CRC_MODE
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PRE_CRC_MODE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),20,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PRE_CRC_MODE  LAN80XX_BIT(20)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PRE_CRC_MODE(x)  LAN80XX_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Enables pause timer implementation in MAC Rx clock domain for the
 * received pause frame.
 *
 * \details
 * 0: Disable pause timer implementation
 * 1: Enables pause timer implementation
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL . MAC_RX_PAUSE_TIMER_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_TIMER_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),12,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_TIMER_ENA  LAN80XX_BIT(12)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_TIMER_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Enables pausing of transmission when a pause frame is received.
 *
 * \details
 * 0: Disable pause reaction
 * 1: Enables pause reaction
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL . MAC_TX_PAUSE_REACT_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_TX_PAUSE_REACT_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_TX_PAUSE_REACT_ENA  LAN80XX_BIT(8)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_TX_PAUSE_REACT_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Enables dropping of pause frames in the pause frame detector.
 *
 * \details
 * 0: Pause frames are not dropped
 * 1: Pause frames are dropped
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL . MAC_RX_PAUSE_FRAME_DROP_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_FRAME_DROP_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_FRAME_DROP_ENA  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_FRAME_DROP_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Controls pause frame detection in receive path.
 *
 * \details
 * 0: Pause frame detection is disabled
 * 1: Pause frame detection is enabled
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL . MAC_RX_PAUSE_MODE
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_MODE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_MODE  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_MODE(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Pause detector state register
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_PAUSE_CFG:HOST_MAC_PAUSE_STATE
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PAUSE_STATE   LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf10e)

/**
 * \brief
 * Pause state indicator. Interface is paused when the pause timer is a
 * non-zero value.
 *
 * \details
 * 0: Not paused
 * 1: Paused
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PAUSE_STATE . PAUSE_STATE
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PAUSE_STATE_PAUSE_STATE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_STATE_PAUSE_STATE  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PAUSE_STATE_PAUSE_STATE(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Indicates the current value of the mac_pause_frm_gen_i signal
 *
 * \details
 * 0 = Below the threshold, do not generate pause frames
 * 1 = Above the threshold, generate pause frames if enabled
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PAUSE_STATE . MAC_TX_PAUSE_GEN
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PAUSE_STATE_MAC_TX_PAUSE_GEN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_STATE_MAC_TX_PAUSE_GEN  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PAUSE_STATE_MAC_TX_PAUSE_GEN(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)


/**
 * \brief MAC address LSB register
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_PAUSE_CFG:HOST_MAC_MAC_ADDRESS_LSB
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MAC_ADDRESS_LSB  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf10f)

/**
 * \brief
 * Lower 32 bits of the MAC address
 *
 * \details
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_ADDRESS_LSB . MAC_ADDRESS_LSB
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_ADDRESS_LSB_MAC_ADDRESS_LSB(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ADDRESS_LSB_MAC_ADDRESS_LSB     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_ADDRESS_LSB_MAC_ADDRESS_LSB(x)  (x)


/**
 * \brief MAC address MSB register
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_PAUSE_CFG:HOST_MAC_MAC_ADDRESS_MSB
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MAC_ADDRESS_MSB  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf110)

/**
 * \brief
 * Upper 16 bits of the MAC address
 *
 * \details
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_ADDRESS_MSB . MAC_ADDRESS_MSB
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_ADDRESS_MSB_MAC_ADDRESS_MSB(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ADDRESS_MSB_MAC_ADDRESS_MSB     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_ADDRESS_MSB_MAC_ADDRESS_MSB(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_MAC:HOST_MAC_STATUS
 *
 * 10G MAC configuration registers
 */


/**
 * \brief XGMII Lane Debug Sticky bit Register 0
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATUS:HOST_MAC_MAC_RX_LANE_STICKY_0
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_0  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf111)

/**
 * \brief
 * Sticky bits for debugging Lane 3.
 *
 * \details
 * See format of LANE0 sticky bit register.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_0 . LANE3_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_0_LANE3_STICKY(x)  LAN80XX_ENCODE_BITFIELD(x,24,7)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_0_LANE3_STICKY     LAN80XX_ENCODE_BITMASK(24,7)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_0_LANE3_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * Sticky bits for debugging Lane 2.
 *
 * \details
 * See format of LANE0 sticky bit register.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_0 . LANE2_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_0_LANE2_STICKY(x)  LAN80XX_ENCODE_BITFIELD(x,16,7)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_0_LANE2_STICKY     LAN80XX_ENCODE_BITMASK(16,7)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_0_LANE2_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,16,7)

/**
 * \brief
 * Sticky bits for debugging Lane 1.
 *
 * \details
 * See format of LANE0 sticky bit register.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_0 . LANE1_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_0_LANE1_STICKY(x)  LAN80XX_ENCODE_BITFIELD(x,8,7)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_0_LANE1_STICKY     LAN80XX_ENCODE_BITMASK(8,7)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_0_LANE1_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,8,7)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_0 . LANE0_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_0_LANE0_STICKY(x)  LAN80XX_ENCODE_BITFIELD(x,0,7)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_0_LANE0_STICKY     LAN80XX_ENCODE_BITMASK(0,7)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_0_LANE0_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief XGMII Lane Debug Sticky bit Register 1
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATUS:HOST_MAC_MAC_RX_LANE_STICKY_1
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_1  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf112)

/**
 * \brief
 * Sticky bits for debugging Lane 7.
 *
 * \details
 * See format of LANE0 sticky bit register.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_1 . LANE7_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_1_LANE7_STICKY(x)  LAN80XX_ENCODE_BITFIELD(x,24,7)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_1_LANE7_STICKY     LAN80XX_ENCODE_BITMASK(24,7)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_1_LANE7_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * Sticky bits for debugging Lane 6.
 *
 * \details
 * See format of LANE0 sticky bit register.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_1 . LANE6_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_1_LANE6_STICKY(x)  LAN80XX_ENCODE_BITFIELD(x,16,7)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_1_LANE6_STICKY     LAN80XX_ENCODE_BITMASK(16,7)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_1_LANE6_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,16,7)

/**
 * \brief
 * Sticky bits for debugging Lane 5.
 *
 * \details
 * See format of LANE0 sticky bit register.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_1 . LANE5_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_1_LANE5_STICKY(x)  LAN80XX_ENCODE_BITFIELD(x,8,7)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_1_LANE5_STICKY     LAN80XX_ENCODE_BITMASK(8,7)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_1_LANE5_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,8,7)

/**
 * \brief
 * Sticky bits for debugging Lane 4.
 *
 * \details
 * See format of LANE0 sticky bit register.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_1 . LANE4_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_1_LANE4_STICKY(x)  LAN80XX_ENCODE_BITFIELD(x,0,7)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_1_LANE4_STICKY     LAN80XX_ENCODE_BITMASK(0,7)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_RX_LANE_STICKY_1_LANE4_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief 25G Line MAC Tx Monitor Sticky bit Register
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATUS:HOST_MAC_MAC_TX_MONITOR_STICKY
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf113)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY . LOCAL_ERR_STATE_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_LOCAL_ERR_STATE_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_LOCAL_ERR_STATE_STICKY  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_LOCAL_ERR_STATE_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY . REMOTE_ERR_STATE_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_REMOTE_ERR_STATE_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_REMOTE_ERR_STATE_STICKY  LAN80XX_BIT(3)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_REMOTE_ERR_STATE_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY . IDLE_STATE_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY  LAN80XX_BIT(1)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY . DIS_STATE_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_DIS_STATE_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_DIS_STATE_STICKY  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_DIS_STATE_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief 25G Line MAC Tx Monitor interrupt mask register
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATUS:HOST_MAC_MAC_TX_MONITOR_STICKY_MASK
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf114)

/**
 * \brief
 * LFS: LOCAL FAULT state reached in Tx module of 10G MAC. Writing a '1'
 * clears the sticky bit.
 *
 * \details
 * '0': Disable interrupt
 * '1': Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK . LOCAL_ERR_STATE_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK_LOCAL_ERR_STATE_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK_LOCAL_ERR_STATE_STICKY_MASK  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK_LOCAL_ERR_STATE_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * LFS REMOTE FAULT state reached in Tx module of 10G MAC. Writing a '1'
 * clears the sticky bit.
 *
 * \details
 * '0': Disable interrupt
 * '1': Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK . REMOTE_ERR_STATE_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK_REMOTE_ERR_STATE_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK_REMOTE_ERR_STATE_STICKY_MASK  LAN80XX_BIT(3)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK_REMOTE_ERR_STATE_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * IDLE state reached in Tx module of 10G MAC. Writing a '1' clears the
 * sticky bit.
 *
 * \details
 * '0': Disable interrupt
 * '1': Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK . IDLE_STATE_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK_IDLE_STATE_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK_IDLE_STATE_STICKY_MASK  LAN80XX_BIT(1)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK_IDLE_STATE_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * DISABLE state reached in Tx module of 10G MAC. Writing a '1' clears the
 * sticky bit.
 *
 * \details
 * '0': Disable interrupt
 * '1': Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK . DIS_STATE_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK_DIS_STATE_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK_DIS_STATE_STICKY_MASK  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK_DIS_STATE_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Sticky bit register
 *
 * \details
 * Clear the sticky bits by writing a 0 in the relevant bitgroups (writing
 * a 1 sets the bit)
 *
 * Register: \a HOST_MAC:HOST_MAC_STATUS:HOST_MAC_MAC_STICKY
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY    LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf115)

/**
 * \brief
 * Indicates an inter packet gap shrink was detected (IPG < 12 bytes).Write
 * 1 to clear the bit.
 *
 * \details
 * 0: No IPG shrink was detected
 * 1: one or more IPG shrinks were detected
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY . RX_IPG_SHRINK_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_RX_IPG_SHRINK_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),9,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_RX_IPG_SHRINK_STICKY  LAN80XX_BIT(9)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_STICKY_RX_IPG_SHRINK_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Indicates that a preamble shrink was detected (preamble < 8 bytes).This
 * sticky bit can only be set when the port is setup in 10 Gbps mode, where
 * frames with, for example, a 4 bytes preamble are discarded. In addition,
 * it requires that PRM_SHK_CHK_DIS = 0 and SFD_CHK_ENA = 1.Write 1 to
 * clear the bit.
 *
 * \details
 * 0: No preamble shrink was detected
 * 1: one or more preamble shrinks were detected
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY . RX_PREAM_SHRINK_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_RX_PREAM_SHRINK_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_RX_PREAM_SHRINK_STICKY  LAN80XX_BIT(8)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_STICKY_RX_PREAM_SHRINK_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * This bit is set if a preamble check is enabled, an SOP is received, and
 * the following bytes do not match a 5555555555..55D5 pattern.A 12 byte
 * preamble of 55555555.55555555.555555D5 will not cause this sticky bit to
 * be set. This sticky bit can only be set when the port is set up in 10
 * Gbps mode. Write 1 to clear the bit.
 *
 * \details
 * 0: No preamble mismatch was detected
 * 1: one or more preamble matches were detected
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY . RX_PREAM_MISMATCH_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_RX_PREAM_MISMATCH_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),7,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_RX_PREAM_MISMATCH_STICKY  LAN80XX_BIT(7)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_STICKY_RX_PREAM_MISMATCH_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,7,1)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY . RX_PREAM_ERR_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_RX_PREAM_ERR_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),6,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_RX_PREAM_ERR_STICKY  LAN80XX_BIT(6)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_STICKY_RX_PREAM_ERR_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Indicates that a frame was received with a non-standard preamble. Write
 * 1 to clear the bit.
 *
 * \details
 * 0: No MAC frame with non-standard preamble is received.
 * 1: One or more MAC frames are received with non-standard preamble.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY . RX_NON_STD_PREAM_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_RX_NON_STD_PREAM_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),5,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_RX_NON_STD_PREAM_STICKY  LAN80XX_BIT(5)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_STICKY_RX_NON_STD_PREAM_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Indicates that a frame with MPLS multicast was received. Write 1 to
 * clear the bit.
 *
 * \details
 * 0: No MPLS multicast frame is received.
 * 1: One or more MPLS multicast frames are received.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY . RX_MPLS_MC_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_RX_MPLS_MC_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_RX_MPLS_MC_STICKY  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_STICKY_RX_MPLS_MC_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Indicates that a frame with MPLS unicast was received. Write 1 to clear
 * the bit.
 *
 * \details
 * 0: No MPLS unicast frame is received.
 * 1: One or more MPLS unicast frames are received.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY . RX_MPLS_UC_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_RX_MPLS_UC_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_RX_MPLS_UC_STICKY  LAN80XX_BIT(3)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_STICKY_RX_MPLS_UC_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Indicates that a frame was received with a VLAN tag. Write 1 to clear
 * the bit.
 *
 * \details
 * 0: No VLAN tagged frame is received.
 * 1: One or more VLAN tagged frames are received.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY . RX_TAG_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_RX_TAG_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_RX_TAG_STICKY  LAN80XX_BIT(2)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_STICKY_RX_TAG_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Sticky bit indicating that the MAC transmit FIFO has dropped one or more
 * frames because of underrun. Write 1 to clear the bit.
 *
 * \details
 * 0: No MAC Tx FIFO underrun has occured.
 * 1: One or more MAC Tx FIFO underruns have occurred.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY . TX_UFLW_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_TX_UFLW_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_TX_UFLW_STICKY  LAN80XX_BIT(1)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_STICKY_TX_UFLW_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Indicates that the transmit host initiated abort was executed. Write 1
 * to clear the bit.
 *
 * \details
 * 0: No Tx frames aborted.
 * 1: Tx frames aborted.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY . TX_ABORT_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_TX_ABORT_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_TX_ABORT_STICKY  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_STICKY_TX_ABORT_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief MAC sticky bits interrupt mask register
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATUS:HOST_MAC_MAC_STICKY_MASK
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY_MASK  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf116)

/**
 * \brief
 * Interrupt mask for RX_IPG_SHRINK_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY_MASK . RX_IPG_SHRINK_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_IPG_SHRINK_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),9,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_IPG_SHRINK_STICKY_MASK  LAN80XX_BIT(9)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_IPG_SHRINK_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Interrupt mask for RX_PREAM_SHRINK_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY_MASK . RX_PREAM_SHRINK_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_PREAM_SHRINK_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_PREAM_SHRINK_STICKY_MASK  LAN80XX_BIT(8)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_PREAM_SHRINK_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Interrupt mask for RX_PREAM_MISMATCH_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY_MASK . RX_PREAM_MISMATCH_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_PREAM_MISMATCH_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),7,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_PREAM_MISMATCH_STICKY_MASK  LAN80XX_BIT(7)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_PREAM_MISMATCH_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Interrupt mask for RX_PREAM_ERR_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY_MASK . RX_PREAM_ERR_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_PREAM_ERR_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),6,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_PREAM_ERR_STICKY_MASK  LAN80XX_BIT(6)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_PREAM_ERR_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Interrupt mask for RX_NON_STD_PREAM_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY_MASK . RX_NON_STD_PREAM_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_NON_STD_PREAM_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),5,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_NON_STD_PREAM_STICKY_MASK  LAN80XX_BIT(5)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_NON_STD_PREAM_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Interrupt mask for RX_MPLS_MC_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY_MASK . RX_MPLS_MC_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_MPLS_MC_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_MPLS_MC_STICKY_MASK  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_MPLS_MC_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Interrupt mask for RX_MPLS_UC_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY_MASK . RX_MPLS_UC_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_MPLS_UC_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_MPLS_UC_STICKY_MASK  LAN80XX_BIT(3)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_MPLS_UC_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Interrupt mask for RX_TAG_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY_MASK . RX_TAG_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_TAG_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_TAG_STICKY_MASK  LAN80XX_BIT(2)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_TAG_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Interrupt mask for TX_UFLW_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY_MASK . TX_UFLW_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_TX_UFLW_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_TX_UFLW_STICKY_MASK  LAN80XX_BIT(1)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_TX_UFLW_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Interrupt mask for TX_ABORT_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY_MASK . TX_ABORT_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_TX_ABORT_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_TX_ABORT_STICKY_MASK  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_TX_ABORT_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Sticky bit register
 *
 * \details
 * Clear the sticky bits by writing a 0 in the relevant bitgroups (writing
 * a 1 sets the bit)
 *
 * Register: \a HOST_MAC:HOST_MAC_STATUS:HOST_MAC_PMAC_STICKY
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_STICKY   LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf117)

/**
 * \brief
 * Indicates that a preamble shrink was detected (preamble < 8 bytes).This
 * sticky bit can only be set when the port is setup in 10 Gbps mode, where
 * frames with, for example, a 4 bytes preamble are discarded. In addition,
 * it requires that PRM_SHK_CHK_DIS = 0 and SFD_CHK_ENA = 1.Write 1 to
 * clear the bit.
 *
 * \details
 * 0: No preamble shrink was detected
 * 1: one or more preamble shrinks were detected
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_STICKY . PMAC_RX_PREAM_SHRINK_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_PREAM_SHRINK_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_PREAM_SHRINK_STICKY  LAN80XX_BIT(8)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_PREAM_SHRINK_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * This bit is set if a preamble check is enabled, an SOP is received, and
 * the following bytes do not match a 5555555555..55D5 pattern.A 12 byte
 * preamble of 55555555.55555555.555555D5 will not cause this sticky bit to
 * be set. This sticky bit can only be set when the port is set up in 10
 * Gbps mode. Write 1 to clear the bit.
 *
 * \details
 * 0: No preamble mismatch was detected
 * 1: one or more preamble matches were detected
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_STICKY . PMAC_RX_PREAM_MISMATCH_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_PREAM_MISMATCH_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),7,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_PREAM_MISMATCH_STICKY  LAN80XX_BIT(7)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_PREAM_MISMATCH_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,7,1)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_STICKY . PMAC_RX_PREAM_ERR_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_PREAM_ERR_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),6,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_PREAM_ERR_STICKY  LAN80XX_BIT(6)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_PREAM_ERR_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Indicates that a frame was received with a non-standard preamble. Write
 * 1 to clear the bit.
 *
 * \details
 * 0: No MAC frame with non-standard preamble is received.
 * 1: One or more MAC frames are received with non-standard preamble.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_STICKY . PMAC_RX_NON_STD_PREAM_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_NON_STD_PREAM_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),5,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_NON_STD_PREAM_STICKY  LAN80XX_BIT(5)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_NON_STD_PREAM_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Indicates that a frame with MPLS multicast was received. Write 1 to
 * clear the bit.
 *
 * \details
 * 0: No MPLS multicast frame is received.
 * 1: One or more MPLS multicast frames are received.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_STICKY . PMAC_RX_MPLS_MC_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_MPLS_MC_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_MPLS_MC_STICKY  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_MPLS_MC_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Indicates that a frame with MPLS unicast was received. Write 1 to clear
 * the bit.
 *
 * \details
 * 0: No MPLS unicast frame is received.
 * 1: One or more MPLS unicast frames are received.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_STICKY . PMAC_RX_MPLS_UC_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_MPLS_UC_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_MPLS_UC_STICKY  LAN80XX_BIT(3)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_MPLS_UC_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Sticky bit indicating that the MAC transmit FIFO has dropped one or more
 * frames because of underrun. Write 1 to clear the bit.
 *
 * \details
 * 0: No MAC Tx FIFO underrun has occured.
 * 1: One or more MAC Tx FIFO underruns have occurred.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_STICKY . PMAC_TX_UFLW_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_TX_UFLW_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_TX_UFLW_STICKY  LAN80XX_BIT(1)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_TX_UFLW_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Indicates that the transmit host initiated abort was executed. Write 1
 * to clear the bit.
 *
 * \details
 * 0: No Tx frames aborted.
 * 1: Tx frames aborted.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_STICKY . PMAC_TX_ABORT_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_TX_ABORT_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_TX_ABORT_STICKY  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_TX_ABORT_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief MAC sticky bits interrupt mask register
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATUS:HOST_MAC_PMAC_MAC_STICKY_MASK
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf118)

/**
 * \brief
 * Interrupt mask for RX_PREAM_SHRINK_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK . PMAC_RX_PREAM_SHRINK_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_PREAM_SHRINK_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_PREAM_SHRINK_STICKY_MASK  LAN80XX_BIT(8)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_PREAM_SHRINK_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Interrupt mask for RX_PREAM_MISMATCH_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK . PMAC_RX_PREAM_MISMATCH_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_PREAM_MISMATCH_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),7,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_PREAM_MISMATCH_STICKY_MASK  LAN80XX_BIT(7)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_PREAM_MISMATCH_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Interrupt mask for RX_PREAM_ERR_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK . PMAC_RX_PREAM_ERR_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_PREAM_ERR_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),6,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_PREAM_ERR_STICKY_MASK  LAN80XX_BIT(6)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_PREAM_ERR_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Interrupt mask for RX_NON_STD_PREAM_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK . PMAC_RX_NON_STD_PREAM_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_NON_STD_PREAM_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),5,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_NON_STD_PREAM_STICKY_MASK  LAN80XX_BIT(5)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_NON_STD_PREAM_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Interrupt mask for RX_MPLS_MC_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK . PMAC_RX_MPLS_MC_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_MPLS_MC_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_MPLS_MC_STICKY_MASK  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_MPLS_MC_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Interrupt mask for RX_MPLS_UC_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK . PMAC_RX_MPLS_UC_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_MPLS_UC_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_MPLS_UC_STICKY_MASK  LAN80XX_BIT(3)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_MPLS_UC_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Interrupt mask for TX_UFLW_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK . PMAC_TX_UFLW_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_TX_UFLW_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_TX_UFLW_STICKY_MASK  LAN80XX_BIT(1)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_TX_UFLW_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Interrupt mask for TX_ABORT_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK . PMAC_TX_ABORT_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_TX_ABORT_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_TX_ABORT_STICKY_MASK  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_TX_ABORT_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT
 *
 * Not documented
 */


/**
 * \brief Rx XGMII protocol error counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_XGMII_PROT_ERR_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_XGMII_PROT_ERR_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf119)

/**
 * \brief
 * Number of XGMII protocol errors detected.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_XGMII_PROT_ERR_CNT . RX_XGMII_PROT_ERR_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_XGMII_PROT_ERR_CNT_RX_XGMII_PROT_ERR_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_XGMII_PROT_ERR_CNT_RX_XGMII_PROT_ERR_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_XGMII_PROT_ERR_CNT_RX_XGMII_PROT_ERR_CNT(x)  (x)


/**
 * \brief Rx symbol carrier error counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_SYMBOL_ERR_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_SYMBOL_ERR_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf11a)

/**
 * \brief
 * The number of frames received with one or more symbol errors.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_SYMBOL_ERR_CNT . RX_SYMBOL_ERR_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_SYMBOL_ERR_CNT_RX_SYMBOL_ERR_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_SYMBOL_ERR_CNT_RX_SYMBOL_ERR_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_SYMBOL_ERR_CNT_RX_SYMBOL_ERR_CNT(x)  (x)


/**
 * \brief Rx pause frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_PAUSE_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_PAUSE_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf11b)

/**
 * \brief
 * Number of pause control frames received.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_PAUSE_CNT . RX_PAUSE_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_PAUSE_CNT_RX_PAUSE_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_PAUSE_CNT_RX_PAUSE_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_PAUSE_CNT_RX_PAUSE_CNT(x)  (x)


/**
 * \brief Rx control frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_UNSUP_OPCODE_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_UNSUP_OPCODE_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf11c)

/**
 * \brief
 * Number of control frames with unsupported opcode received.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_UNSUP_OPCODE_CNT . RX_UNSUP_OPCODE_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_UNSUP_OPCODE_CNT_RX_UNSUP_OPCODE_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_UNSUP_OPCODE_CNT_RX_UNSUP_OPCODE_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_UNSUP_OPCODE_CNT_RX_UNSUP_OPCODE_CNT(x)  (x)


/**
 * \brief Rx unicast frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_UC_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_UC_CNT     LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf11d)

/**
 * \brief
 * The number of good unicast frames received.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_UC_CNT . RX_UC_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_UC_CNT_RX_UC_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_UC_CNT_RX_UC_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_UC_CNT_RX_UC_CNT(x)  (x)


/**
 * \brief Rx multicast frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_MC_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_MC_CNT     LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf11e)

/**
 * \brief
 * The number of good multicast frames received.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_MC_CNT . RX_MC_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_MC_CNT_RX_MC_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_MC_CNT_RX_MC_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_MC_CNT_RX_MC_CNT(x)  (x)


/**
 * \brief Rx broadcast frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_BC_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_BC_CNT     LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf11f)

/**
 * \brief
 * The number of good broadcast frames received.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_BC_CNT . RX_BC_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_BC_CNT_RX_BC_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_BC_CNT_RX_BC_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_BC_CNT_RX_BC_CNT(x)  (x)


/**
 * \brief Rx CRC error counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_CRC_ERR_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_CRC_ERR_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf120)

/**
 * \brief
 * The number of frames received with CRC error only.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_CRC_ERR_CNT . RX_CRC_ERR_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_CRC_ERR_CNT_RX_CRC_ERR_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_CRC_ERR_CNT_RX_CRC_ERR_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_CRC_ERR_CNT_RX_CRC_ERR_CNT(x)  (x)


/**
 * \brief Rx undersize counter (valid frame format)
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_UNDERSIZE_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_UNDERSIZE_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf121)

/**
 * \brief
 * The number of undersize but well-formed frames received.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_UNDERSIZE_CNT . RX_UNDERSIZE_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_UNDERSIZE_CNT_RX_UNDERSIZE_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_UNDERSIZE_CNT_RX_UNDERSIZE_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_UNDERSIZE_CNT_RX_UNDERSIZE_CNT(x)  (x)


/**
 * \brief Rx undersize counter (CRC error)
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_FRAGMENTS_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_FRAGMENTS_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf122)

/**
 * \brief
 * The number of undersize frames with CRC error received.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_FRAGMENTS_CNT . RX_FRAGMENTS_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_FRAGMENTS_CNT_RX_FRAGMENTS_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_FRAGMENTS_CNT_RX_FRAGMENTS_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_FRAGMENTS_CNT_RX_FRAGMENTS_CNT(x)  (x)


/**
 * \brief Rx in-range length error counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_IN_RANGE_LEN_ERR_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_IN_RANGE_LEN_ERR_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf123)

/**
 * \brief
 * The number of frames with legal length field that don't match length of
 * MAC client data.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_IN_RANGE_LEN_ERR_CNT . RX_IN_RANGE_LEN_ERR_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_IN_RANGE_LEN_ERR_CNT_RX_IN_RANGE_LEN_ERR_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_IN_RANGE_LEN_ERR_CNT_RX_IN_RANGE_LEN_ERR_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_IN_RANGE_LEN_ERR_CNT_RX_IN_RANGE_LEN_ERR_CNT(x)  (x)


/**
 * \brief Rx out-of-range length error counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_OUT_OF_RANGE_LEN_ERR_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_OUT_OF_RANGE_LEN_ERR_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf124)

/**
 * \brief
 * The number of frames with illegal length field (frames using type field
 * are not counted here).
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_OUT_OF_RANGE_LEN_ERR_CNT . RX_OUT_OF_RANGE_LEN_ERR_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_OUT_OF_RANGE_LEN_ERR_CNT_RX_OUT_OF_RANGE_LEN_ERR_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_OUT_OF_RANGE_LEN_ERR_CNT_RX_OUT_OF_RANGE_LEN_ERR_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_OUT_OF_RANGE_LEN_ERR_CNT_RX_OUT_OF_RANGE_LEN_ERR_CNT(x)  (x)


/**
 * \brief Rx oversize counter (valid frame format)
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_OVERSIZE_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_OVERSIZE_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf125)

/**
 * \brief
 * The number of oversize well-formed frames received.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_OVERSIZE_CNT . RX_OVERSIZE_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_OVERSIZE_CNT_RX_OVERSIZE_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_OVERSIZE_CNT_RX_OVERSIZE_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_OVERSIZE_CNT_RX_OVERSIZE_CNT(x)  (x)


/**
 * \brief Rx jabbers counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_JABBERS_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_JABBERS_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf126)

/**
 * \brief
 * The number of oversize frames with CRC error received.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_JABBERS_CNT . RX_JABBERS_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_JABBERS_CNT_RX_JABBERS_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_JABBERS_CNT_RX_JABBERS_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_JABBERS_CNT_RX_JABBERS_CNT(x)  (x)


/**
 * \brief Rx 64 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_SIZE64_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE64_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf127)

/**
 * \brief
 * The number of 64 bytes frames received.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE64_CNT . RX_SIZE64_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_SIZE64_CNT_RX_SIZE64_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_SIZE64_CNT_RX_SIZE64_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_SIZE64_CNT_RX_SIZE64_CNT(x)  (x)


/**
 * \brief Rx 65-127 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_SIZE65TO127_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE65TO127_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf128)

/**
 * \brief
 * The number of 65 to 127 bytes frames received.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE65TO127_CNT . RX_SIZE65TO127_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_SIZE65TO127_CNT_RX_SIZE65TO127_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_SIZE65TO127_CNT_RX_SIZE65TO127_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_SIZE65TO127_CNT_RX_SIZE65TO127_CNT(x)  (x)


/**
 * \brief Rx 128-255 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_SIZE128TO255_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE128TO255_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf129)

/**
 * \brief
 * The number of 128 to 255 bytes frames received.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE128TO255_CNT . RX_SIZE128TO255_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_SIZE128TO255_CNT_RX_SIZE128TO255_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_SIZE128TO255_CNT_RX_SIZE128TO255_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_SIZE128TO255_CNT_RX_SIZE128TO255_CNT(x)  (x)


/**
 * \brief Rx 256-511 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_SIZE256TO511_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE256TO511_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf12a)

/**
 * \brief
 * The number of 256 to 511 bytes frames received.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE256TO511_CNT . RX_SIZE256TO511_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_SIZE256TO511_CNT_RX_SIZE256TO511_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_SIZE256TO511_CNT_RX_SIZE256TO511_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_SIZE256TO511_CNT_RX_SIZE256TO511_CNT(x)  (x)


/**
 * \brief Rx 512-1023 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_SIZE512TO1023_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE512TO1023_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf12b)

/**
 * \brief
 * The number of 512 to 1023 bytes frames received.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE512TO1023_CNT . RX_SIZE512TO1023_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_SIZE512TO1023_CNT_RX_SIZE512TO1023_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_SIZE512TO1023_CNT_RX_SIZE512TO1023_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_SIZE512TO1023_CNT_RX_SIZE512TO1023_CNT(x)  (x)


/**
 * \brief Rx 1024-1518 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_SIZE1024TO1518_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE1024TO1518_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf12c)

/**
 * \brief
 * The number of 1024 to 1518 bytes frames received.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE1024TO1518_CNT . RX_SIZE1024TO1518_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_SIZE1024TO1518_CNT_RX_SIZE1024TO1518_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_SIZE1024TO1518_CNT_RX_SIZE1024TO1518_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_SIZE1024TO1518_CNT_RX_SIZE1024TO1518_CNT(x)  (x)


/**
 * \brief Rx 1519 to max. length byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_SIZE1519TOMAX_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE1519TOMAX_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf12d)

/**
 * \brief
 * The number of frames received that are longer than 1518 bytes but not
 * longer than the maximum length register (maximum length register + 4 if
 * the frame is VLAN tagged).
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE1519TOMAX_CNT . RX_SIZE1519TOMAX_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_SIZE1519TOMAX_CNT_RX_SIZE1519TOMAX_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_SIZE1519TOMAX_CNT_RX_SIZE1519TOMAX_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_SIZE1519TOMAX_CNT_RX_SIZE1519TOMAX_CNT(x)  (x)


/**
 * \brief Rx inter packet gap shrink counter
 *
 * \details
 * This counter will increment for both E-Frame and P-Frame.
 *
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_IPG_SHRINK_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_IPG_SHRINK_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf12e)

/**
 * \brief
 * Number of inter packet gap shrinks detected (IPG < 12 bytes).
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_IPG_SHRINK_CNT . RX_IPG_SHRINK_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_IPG_SHRINK_CNT_RX_IPG_SHRINK_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_IPG_SHRINK_CNT_RX_IPG_SHRINK_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_IPG_SHRINK_CNT_RX_IPG_SHRINK_CNT(x)  (x)


/**
 * \brief Tx pause frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_TX_PAUSE_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_TX_PAUSE_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf12f)

/**
 * \brief
 * The number of pause control frames transmitted.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_TX_PAUSE_CNT . TX_PAUSE_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_TX_PAUSE_CNT_TX_PAUSE_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_TX_PAUSE_CNT_TX_PAUSE_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_TX_PAUSE_CNT_TX_PAUSE_CNT(x)  (x)


/**
 * \brief Tx unicast frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_TX_UC_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_TX_UC_CNT     LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf130)

/**
 * \brief
 * The number of unicast frames transmitted.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_TX_UC_CNT . TX_UC_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_TX_UC_CNT_TX_UC_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_TX_UC_CNT_TX_UC_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_TX_UC_CNT_TX_UC_CNT(x)  (x)


/**
 * \brief Tx multicast frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_TX_MC_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_TX_MC_CNT     LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf131)

/**
 * \brief
 * The number of multicast frames transmitted.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_TX_MC_CNT . TX_MC_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_TX_MC_CNT_TX_MC_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_TX_MC_CNT_TX_MC_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_TX_MC_CNT_TX_MC_CNT(x)  (x)


/**
 * \brief Tx broadcast frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_TX_BC_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_TX_BC_CNT     LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf132)

/**
 * \brief
 * The number of broadcast frames transmitted.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_TX_BC_CNT . TX_BC_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_TX_BC_CNT_TX_BC_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_TX_BC_CNT_TX_BC_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_TX_BC_CNT_TX_BC_CNT(x)  (x)


/**
 * \brief Tx 64 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_TX_SIZE64_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE64_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf133)

/**
 * \brief
 * The number of 64 bytes frames transmitted.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE64_CNT . TX_SIZE64_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_TX_SIZE64_CNT_TX_SIZE64_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_TX_SIZE64_CNT_TX_SIZE64_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_TX_SIZE64_CNT_TX_SIZE64_CNT(x)  (x)


/**
 * \brief Tx 65-127 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_TX_SIZE65TO127_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE65TO127_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf134)

/**
 * \brief
 * The number of 65 to 127 bytes frames transmitted.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE65TO127_CNT . TX_SIZE65TO127_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_TX_SIZE65TO127_CNT_TX_SIZE65TO127_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_TX_SIZE65TO127_CNT_TX_SIZE65TO127_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_TX_SIZE65TO127_CNT_TX_SIZE65TO127_CNT(x)  (x)


/**
 * \brief Tx 128-255 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_TX_SIZE128TO255_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE128TO255_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf135)

/**
 * \brief
 * The number of 128 to 255 bytes frames transmitted.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE128TO255_CNT . TX_SIZE128TO255_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_TX_SIZE128TO255_CNT_TX_SIZE128TO255_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_TX_SIZE128TO255_CNT_TX_SIZE128TO255_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_TX_SIZE128TO255_CNT_TX_SIZE128TO255_CNT(x)  (x)


/**
 * \brief Tx 256-511 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_TX_SIZE256TO511_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE256TO511_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf136)

/**
 * \brief
 * The number of 256 to 511 bytes frames transmitted.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE256TO511_CNT . TX_SIZE256TO511_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_TX_SIZE256TO511_CNT_TX_SIZE256TO511_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_TX_SIZE256TO511_CNT_TX_SIZE256TO511_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_TX_SIZE256TO511_CNT_TX_SIZE256TO511_CNT(x)  (x)


/**
 * \brief Tx 512-1023 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_TX_SIZE512TO1023_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE512TO1023_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf137)

/**
 * \brief
 * The number of 512 to 1023 bytes frames transmitted.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE512TO1023_CNT . TX_SIZE512TO1023_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_TX_SIZE512TO1023_CNT_TX_SIZE512TO1023_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_TX_SIZE512TO1023_CNT_TX_SIZE512TO1023_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_TX_SIZE512TO1023_CNT_TX_SIZE512TO1023_CNT(x)  (x)


/**
 * \brief Tx 1024-1518 byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_TX_SIZE1024TO1518_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE1024TO1518_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf138)

/**
 * \brief
 * The number of 1024 to 1518 bytes frames transmitted.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE1024TO1518_CNT . TX_SIZE1024TO1518_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_TX_SIZE1024TO1518_CNT_TX_SIZE1024TO1518_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_TX_SIZE1024TO1518_CNT_TX_SIZE1024TO1518_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_TX_SIZE1024TO1518_CNT_TX_SIZE1024TO1518_CNT(x)  (x)


/**
 * \brief Tx 1519 to max. length byte frame counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_TX_SIZE1519TOMAX_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE1519TOMAX_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf139)

/**
 * \brief
 * The number of frames transmitted that are longer than 1518 bytes but not
 * longer than the maximum length register (maximum length register + 4 if
 * the frame is VLAN tagged).
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE1519TOMAX_CNT . TX_SIZE1519TOMAX_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_TX_SIZE1519TOMAX_CNT_TX_SIZE1519TOMAX_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_TX_SIZE1519TOMAX_CNT_TX_SIZE1519TOMAX_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_TX_SIZE1519TOMAX_CNT_TX_SIZE1519TOMAX_CNT(x)  (x)


/**
 * \brief Counter to track the dribble-nibble (extra nibble) errors in frames.
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_ALIGNMENT_LOST_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_ALIGNMENT_LOST_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf13a)

/**
 * \brief
 * The number of frames received with Alignment (dribble-nibble) error.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_ALIGNMENT_LOST_CNT . RX_ALIGNMENT_LOST_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_ALIGNMENT_LOST_CNT_RX_ALIGNMENT_LOST_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_ALIGNMENT_LOST_CNT_RX_ALIGNMENT_LOST_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_ALIGNMENT_LOST_CNT_RX_ALIGNMENT_LOST_CNT(x)  (x)


/**
 * \brief Counts frames that are tagged (C-Tagged or S-Tagged).
 *
 * \details
 * This counter will increment for both E-Frame and P-Frame with VLAN tag.
 *
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_TAGGED_FRMS_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_TAGGED_FRMS_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf13b)

/**
 * \brief
 * The number of frames received with C-Tag or S-Tag information
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_TAGGED_FRMS_CNT . RX_TAGGED_FRMS_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_TAGGED_FRMS_CNT_RX_TAGGED_FRMS_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_TAGGED_FRMS_CNT_RX_TAGGED_FRMS_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_TAGGED_FRMS_CNT_RX_TAGGED_FRMS_CNT(x)  (x)


/**
 * \brief Counts frames that are Not tagged  (neither C-Tagged nor S-Tagged).
 *
 * \details
 * This counter will increment for both E-Frame and P-Frame with VLAN tag.
 *
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_RX_UNTAGGED_FRMS_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_UNTAGGED_FRMS_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf13c)

/**
 * \brief
 * The number of frames received without C-Tag and S-Tag information.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_UNTAGGED_FRMS_CNT . RX_UNTAGGED_FRMS_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_UNTAGGED_FRMS_CNT_RX_UNTAGGED_FRMS_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_UNTAGGED_FRMS_CNT_RX_UNTAGGED_FRMS_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_UNTAGGED_FRMS_CNT_RX_UNTAGGED_FRMS_CNT(x)  (x)


/**
 * \brief Counts frames that are tagged (C-Tagged or S-Tagged).
 *
 * \details
 * This counter will increment for both E-Frame and P-Frame with VLAN tag.
 *
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_TX_TAGGED_FRMS_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_TX_TAGGED_FRMS_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf13d)

/**
 * \brief
 * The number of frames transmitted with C-Tag or S-Tag information
 *
 * \details
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_TX_TAGGED_FRMS_CNT . TX_TAGGED_FRMS_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_TX_TAGGED_FRMS_CNT_TX_TAGGED_FRMS_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_TX_TAGGED_FRMS_CNT_TX_TAGGED_FRMS_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_TX_TAGGED_FRMS_CNT_TX_TAGGED_FRMS_CNT(x)  (x)


/**
 * \brief Counts frames that are Not tagged  (neither C-Tagged nor S-Tagged).
 *
 * \details
 * This counter will increment for both E-Frame and P-Frame with VLAN tag.
 *
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_TX_UNTAGGED_FRMS_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_TX_UNTAGGED_FRMS_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf13e)

/**
 * \brief
 * The number of frames transmitted without C-Tag and S-Tag information.
 *
 * \details
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_TX_UNTAGGED_FRMS_CNT . TX_UNTAGGED_FRMS_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_TX_UNTAGGED_FRMS_CNT_TX_UNTAGGED_FRMS_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_TX_UNTAGGED_FRMS_CNT_TX_UNTAGGED_FRMS_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_TX_UNTAGGED_FRMS_CNT_TX_UNTAGGED_FRMS_CNT(x)  (x)


/**
 * \brief Rx XGMII protocol error counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_XGMII_PROT_ERR_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_XGMII_PROT_ERR_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf13f)

/**
 * \brief
 * PMAC - Number of XGMII protocol errors detected.
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_XGMII_PROT_ERR_CNT . PMAC_RX_XGMII_PROT_ERR_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_XGMII_PROT_ERR_CNT_PMAC_RX_XGMII_PROT_ERR_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_XGMII_PROT_ERR_CNT_PMAC_RX_XGMII_PROT_ERR_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_XGMII_PROT_ERR_CNT_PMAC_RX_XGMII_PROT_ERR_CNT(x)  (x)


/**
 * \brief Rx Symbol Carrier Error Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_SYMBOL_ERR_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_SYMBOL_ERR_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf140)

/**
 * \brief
 * PMAC - The number of frames received with one or more symbol errors.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_SYMBOL_ERR_CNT . PMAC_RX_SYMBOL_ERR_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_SYMBOL_ERR_CNT_PMAC_RX_SYMBOL_ERR_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_SYMBOL_ERR_CNT_PMAC_RX_SYMBOL_ERR_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_SYMBOL_ERR_CNT_PMAC_RX_SYMBOL_ERR_CNT(x)  (x)


/**
 * \brief Rx Pause Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_PAUSE_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_PAUSE_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf141)

/**
 * \brief
 * PMAC - Number of pause control frames received.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_PAUSE_CNT . PMAC_RX_PAUSE_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_PAUSE_CNT_PMAC_RX_PAUSE_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_PAUSE_CNT_PMAC_RX_PAUSE_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_PAUSE_CNT_PMAC_RX_PAUSE_CNT(x)  (x)


/**
 * \brief Rx Control Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_UNSUP_OPCODE_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_UNSUP_OPCODE_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf142)

/**
 * \brief
 * PMAC - Number of control frames with unsupported opcode received.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_UNSUP_OPCODE_CNT . PMAC_RX_UNSUP_OPCODE_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_UNSUP_OPCODE_CNT_PMAC_RX_UNSUP_OPCODE_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_UNSUP_OPCODE_CNT_PMAC_RX_UNSUP_OPCODE_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_UNSUP_OPCODE_CNT_PMAC_RX_UNSUP_OPCODE_CNT(x)  (x)


/**
 * \brief Rx Unicast Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_UC_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_UC_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf143)

/**
 * \brief
 * PMAC - The number of good unicast frames received.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_UC_CNT . PMAC_RX_UC_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_UC_CNT_PMAC_RX_UC_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_UC_CNT_PMAC_RX_UC_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_UC_CNT_PMAC_RX_UC_CNT(x)  (x)


/**
 * \brief Rx Multicast Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_MC_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_MC_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf144)

/**
 * \brief
 * PMAC - The number of good multicast frames received.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_MC_CNT . PMAC_RX_MC_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_MC_CNT_PMAC_RX_MC_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_MC_CNT_PMAC_RX_MC_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_MC_CNT_PMAC_RX_MC_CNT(x)  (x)


/**
 * \brief Rx Broadcast Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_BC_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_BC_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf145)

/**
 * \brief
 * PMAC - The number of good broadcast frames received.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_BC_CNT . PMAC_RX_BC_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_BC_CNT_PMAC_RX_BC_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_BC_CNT_PMAC_RX_BC_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_BC_CNT_PMAC_RX_BC_CNT(x)  (x)


/**
 * \brief Rx CRC Error Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_CRC_ERR_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_CRC_ERR_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf146)

/**
 * \brief
 * PMAC - The number of frames received with CRC error only.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_CRC_ERR_CNT . PMAC_RX_CRC_ERR_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_CRC_ERR_CNT_PMAC_RX_CRC_ERR_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_CRC_ERR_CNT_PMAC_RX_CRC_ERR_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_CRC_ERR_CNT_PMAC_RX_CRC_ERR_CNT(x)  (x)


/**
 * \brief Rx Undersize Counter (valid frame format)
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_UNDERSIZE_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_UNDERSIZE_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf147)

/**
 * \brief
 * PMAC - The number of undersize well-formed frames received.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_UNDERSIZE_CNT . PMAC_RX_UNDERSIZE_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_UNDERSIZE_CNT_PMAC_RX_UNDERSIZE_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_UNDERSIZE_CNT_PMAC_RX_UNDERSIZE_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_UNDERSIZE_CNT_PMAC_RX_UNDERSIZE_CNT(x)  (x)


/**
 * \brief Rx Undersize Counter (CRC error)
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_FRAGMENTS_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_FRAGMENTS_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf148)

/**
 * \brief
 * PMAC - The number of undersize frames with CRC error received.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_FRAGMENTS_CNT . PMAC_RX_FRAGMENTS_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_FRAGMENTS_CNT_PMAC_RX_FRAGMENTS_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_FRAGMENTS_CNT_PMAC_RX_FRAGMENTS_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_FRAGMENTS_CNT_PMAC_RX_FRAGMENTS_CNT(x)  (x)


/**
 * \brief Rx In-range Length Error Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_IN_RANGE_LEN_ERR_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_IN_RANGE_LEN_ERR_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf149)

/**
 * \brief
 * PMAC - The number of frames with legal length field that does not match
 * length of MAC client data.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_IN_RANGE_LEN_ERR_CNT . PMAC_RX_IN_RANGE_LEN_ERR_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_IN_RANGE_LEN_ERR_CNT_PMAC_RX_IN_RANGE_LEN_ERR_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_IN_RANGE_LEN_ERR_CNT_PMAC_RX_IN_RANGE_LEN_ERR_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_IN_RANGE_LEN_ERR_CNT_PMAC_RX_IN_RANGE_LEN_ERR_CNT(x)  (x)


/**
 * \brief Rx Out-Of-Range Length Error Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf14a)

/**
 * \brief
 * PMAC - The number of frames with illegal length field (frames using type
 * field are not counted here).
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT . PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT_PMAC_RX_OUT_OF_RANGE_LEN_ERR_CNT(x)  (x)


/**
 * \brief Rx Oversize Counter (valid frame format)
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_OVERSIZE_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_OVERSIZE_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf14b)

/**
 * \brief
 * PMAC - The number of oversize well-formed frames received.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_OVERSIZE_CNT . PMAC_RX_OVERSIZE_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_OVERSIZE_CNT_PMAC_RX_OVERSIZE_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_OVERSIZE_CNT_PMAC_RX_OVERSIZE_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_OVERSIZE_CNT_PMAC_RX_OVERSIZE_CNT(x)  (x)


/**
 * \brief Rx Jabbers Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_JABBERS_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_JABBERS_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf14c)

/**
 * \brief
 * PMAC - The number of oversize frames with CRC error received.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_JABBERS_CNT . PMAC_RX_JABBERS_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_JABBERS_CNT_PMAC_RX_JABBERS_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_JABBERS_CNT_PMAC_RX_JABBERS_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_JABBERS_CNT_PMAC_RX_JABBERS_CNT(x)  (x)


/**
 * \brief Rx 64 Byte Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_SIZE64_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_SIZE64_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf14d)

/**
 * \brief
 * PMAC - The number of 64 bytes frames received.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_SIZE64_CNT . PMAC_RX_SIZE64_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_SIZE64_CNT_PMAC_RX_SIZE64_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_SIZE64_CNT_PMAC_RX_SIZE64_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_SIZE64_CNT_PMAC_RX_SIZE64_CNT(x)  (x)


/**
 * \brief Rx 65-127 Byte Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_SIZE65TO127_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_SIZE65TO127_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf14e)

/**
 * \brief
 * PMAC - The number of 65 to 127 bytes frames received.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_SIZE65TO127_CNT . PMAC_RX_SIZE65TO127_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_SIZE65TO127_CNT_PMAC_RX_SIZE65TO127_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_SIZE65TO127_CNT_PMAC_RX_SIZE65TO127_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_SIZE65TO127_CNT_PMAC_RX_SIZE65TO127_CNT(x)  (x)


/**
 * \brief Rx 128-255 Byte Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_SIZE128TO255_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_SIZE128TO255_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf14f)

/**
 * \brief
 * PMAC - The number of 128 to 255 bytes frames received.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_SIZE128TO255_CNT . PMAC_RX_SIZE128TO255_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_SIZE128TO255_CNT_PMAC_RX_SIZE128TO255_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_SIZE128TO255_CNT_PMAC_RX_SIZE128TO255_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_SIZE128TO255_CNT_PMAC_RX_SIZE128TO255_CNT(x)  (x)


/**
 * \brief Rx 256-511 Byte Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_SIZE256TO511_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_SIZE256TO511_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf150)

/**
 * \brief
 * PMAC - The number of 256 to 511 bytes frames received.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_SIZE256TO511_CNT . PMAC_RX_SIZE256TO511_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_SIZE256TO511_CNT_PMAC_RX_SIZE256TO511_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_SIZE256TO511_CNT_PMAC_RX_SIZE256TO511_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_SIZE256TO511_CNT_PMAC_RX_SIZE256TO511_CNT(x)  (x)


/**
 * \brief Rx 512-1023 Byte Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_SIZE512TO1023_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_SIZE512TO1023_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf151)

/**
 * \brief
 * PMAC - The number of 512 to 1023 bytes frames received.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_SIZE512TO1023_CNT . PMAC_RX_SIZE512TO1023_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_SIZE512TO1023_CNT_PMAC_RX_SIZE512TO1023_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_SIZE512TO1023_CNT_PMAC_RX_SIZE512TO1023_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_SIZE512TO1023_CNT_PMAC_RX_SIZE512TO1023_CNT(x)  (x)


/**
 * \brief Rx 1024-1518 Byte Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_SIZE1024TO1518_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_SIZE1024TO1518_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf152)

/**
 * \brief
 * PMAC - The number of 1024 to 1518 bytes frames received.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_SIZE1024TO1518_CNT . PMAC_RX_SIZE1024TO1518_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_SIZE1024TO1518_CNT_PMAC_RX_SIZE1024TO1518_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_SIZE1024TO1518_CNT_PMAC_RX_SIZE1024TO1518_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_SIZE1024TO1518_CNT_PMAC_RX_SIZE1024TO1518_CNT(x)  (x)


/**
 * \brief Rx 1519 To Max. Length Byte Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_SIZE1519TOMAX_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_SIZE1519TOMAX_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf153)

/**
 * \brief
 * PMAC - The number of frames received longer than 1518 bytes and not
 * longer than Maximum Length Register (Maximum Length Register + 4 if the
 * frame is VLAN tagged).
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_SIZE1519TOMAX_CNT . PMAC_RX_SIZE1519TOMAX_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_SIZE1519TOMAX_CNT_PMAC_RX_SIZE1519TOMAX_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_SIZE1519TOMAX_CNT_PMAC_RX_SIZE1519TOMAX_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_SIZE1519TOMAX_CNT_PMAC_RX_SIZE1519TOMAX_CNT(x)  (x)


/**
 * \brief Tx Pause Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_TX_PAUSE_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_PAUSE_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf154)

/**
 * \brief
 * PMAC - The number of pause control frames transmitted.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_PAUSE_CNT . PMAC_TX_PAUSE_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_TX_PAUSE_CNT_PMAC_TX_PAUSE_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_TX_PAUSE_CNT_PMAC_TX_PAUSE_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_TX_PAUSE_CNT_PMAC_TX_PAUSE_CNT(x)  (x)


/**
 * \brief Tx Unicast Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_TX_UC_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_UC_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf155)

/**
 * \brief
 * PMAC - The number of unicast frames transmitted.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_UC_CNT . PMAC_TX_UC_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_TX_UC_CNT_PMAC_TX_UC_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_TX_UC_CNT_PMAC_TX_UC_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_TX_UC_CNT_PMAC_TX_UC_CNT(x)  (x)


/**
 * \brief Tx Multicast Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_TX_MC_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_MC_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf156)

/**
 * \brief
 * PMAC - The number of multicast frames transmitted.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_MC_CNT . PMAC_TX_MC_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_TX_MC_CNT_PMAC_TX_MC_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_TX_MC_CNT_PMAC_TX_MC_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_TX_MC_CNT_PMAC_TX_MC_CNT(x)  (x)


/**
 * \brief Tx Broadcast Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_TX_BC_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_BC_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf157)

/**
 * \brief
 * PMAC - The number of broadcast frames transmitted.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_BC_CNT . PMAC_TX_BC_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_TX_BC_CNT_PMAC_TX_BC_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_TX_BC_CNT_PMAC_TX_BC_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_TX_BC_CNT_PMAC_TX_BC_CNT(x)  (x)


/**
 * \brief Tx 64 Byte Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_TX_SIZE64_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_SIZE64_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf158)

/**
 * \brief
 * PMAC - The number of 64 bytes frames transmitted.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_SIZE64_CNT . PMAC_TX_SIZE64_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_TX_SIZE64_CNT_PMAC_TX_SIZE64_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_TX_SIZE64_CNT_PMAC_TX_SIZE64_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_TX_SIZE64_CNT_PMAC_TX_SIZE64_CNT(x)  (x)


/**
 * \brief Tx 65-127 Byte Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_TX_SIZE65TO127_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_SIZE65TO127_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf159)

/**
 * \brief
 * PMAC - The number of 65 to 127 bytes frames transmitted.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_SIZE65TO127_CNT . PMAC_TX_SIZE65TO127_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_TX_SIZE65TO127_CNT_PMAC_TX_SIZE65TO127_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_TX_SIZE65TO127_CNT_PMAC_TX_SIZE65TO127_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_TX_SIZE65TO127_CNT_PMAC_TX_SIZE65TO127_CNT(x)  (x)


/**
 * \brief Tx 128-255 Byte Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_TX_SIZE128TO255_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_SIZE128TO255_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf15a)

/**
 * \brief
 * PMAC - The number of 128 to 255 bytes frames transmitted.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_SIZE128TO255_CNT . PMAC_TX_SIZE128TO255_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_TX_SIZE128TO255_CNT_PMAC_TX_SIZE128TO255_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_TX_SIZE128TO255_CNT_PMAC_TX_SIZE128TO255_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_TX_SIZE128TO255_CNT_PMAC_TX_SIZE128TO255_CNT(x)  (x)


/**
 * \brief Tx 256-511 Byte Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_TX_SIZE256TO511_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_SIZE256TO511_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf15b)

/**
 * \brief
 * PMAC - The number of 256 to 511 bytes frames transmitted.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_SIZE256TO511_CNT . PMAC_TX_SIZE256TO511_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_TX_SIZE256TO511_CNT_PMAC_TX_SIZE256TO511_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_TX_SIZE256TO511_CNT_PMAC_TX_SIZE256TO511_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_TX_SIZE256TO511_CNT_PMAC_TX_SIZE256TO511_CNT(x)  (x)


/**
 * \brief Tx 512-1023 Byte Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_TX_SIZE512TO1023_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_SIZE512TO1023_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf15c)

/**
 * \brief
 * PMAC - The number of 512 to 1023 bytes frames transmitted.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_SIZE512TO1023_CNT . PMAC_TX_SIZE512TO1023_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_TX_SIZE512TO1023_CNT_PMAC_TX_SIZE512TO1023_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_TX_SIZE512TO1023_CNT_PMAC_TX_SIZE512TO1023_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_TX_SIZE512TO1023_CNT_PMAC_TX_SIZE512TO1023_CNT(x)  (x)


/**
 * \brief Tx 1024-1518 Byte Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_TX_SIZE1024TO1518_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_SIZE1024TO1518_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf15d)

/**
 * \brief
 * PMAC - The number of 1024 to 1518 bytes frames transmitted.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_SIZE1024TO1518_CNT . PMAC_TX_SIZE1024TO1518_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_TX_SIZE1024TO1518_CNT_PMAC_TX_SIZE1024TO1518_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_TX_SIZE1024TO1518_CNT_PMAC_TX_SIZE1024TO1518_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_TX_SIZE1024TO1518_CNT_PMAC_TX_SIZE1024TO1518_CNT(x)  (x)


/**
 * \brief Tx 1519 To Max. Length Byte Frame Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_TX_SIZE1519TOMAX_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_SIZE1519TOMAX_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf15e)

/**
 * \brief
 * PMAC - The number of frames transmitted longer than 1518 bytes and not
 * longer than Maximum Length Register (Maximum Length Register + 4 if the
 * frame is VLAN tagged).
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_SIZE1519TOMAX_CNT . PMAC_TX_SIZE1519TOMAX_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_TX_SIZE1519TOMAX_CNT_PMAC_TX_SIZE1519TOMAX_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_TX_SIZE1519TOMAX_CNT_PMAC_TX_SIZE1519TOMAX_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_TX_SIZE1519TOMAX_CNT_PMAC_TX_SIZE1519TOMAX_CNT(x)  (x)


/**
 * \brief Counter to track the dribble-nibble (extra nibble) errors in frames.
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_PMAC_RX_ALIGNMENT_LOST_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_ALIGNMENT_LOST_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf15f)

/**
 * \brief
 * PMAC - The number of frames received with Alignment (dribble-nibble)
 * error.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_ALIGNMENT_LOST_CNT . PMAC_RX_ALIGNMENT_LOST_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_ALIGNMENT_LOST_CNT_PMAC_RX_ALIGNMENT_LOST_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_ALIGNMENT_LOST_CNT_PMAC_RX_ALIGNMENT_LOST_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_ALIGNMENT_LOST_CNT_PMAC_RX_ALIGNMENT_LOST_CNT(x)  (x)


/**
 * \brief Counts Pframes that are with assembly error .
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_MM_RX_ASSEMBLY_ERR_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MM_RX_ASSEMBLY_ERR_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf160)

/**
 * \brief
 * MAC MERGE - The number of Pframes received with aseembly error.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MM_RX_ASSEMBLY_ERR_CNT . MM_RX_ASSEMBLY_ERR_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MM_RX_ASSEMBLY_ERR_CNT_MM_RX_ASSEMBLY_ERR_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MM_RX_ASSEMBLY_ERR_CNT_MM_RX_ASSEMBLY_ERR_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MM_RX_ASSEMBLY_ERR_CNT_MM_RX_ASSEMBLY_ERR_CNT(x)  (x)


/**
 * \brief Counts Pframes that are with SMD error .
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_MM_RX_SMD_ERR_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MM_RX_SMD_ERR_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf161)

/**
 * \brief
 * MAC MERGE - The number of Pframe fragaments rejected die to unknown SMD
 * values or arrving with SMD-C when no pframe in progress  .
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MM_RX_SMD_ERR_CNT . MM_RX_SMD_ERR_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MM_RX_SMD_ERR_CNT_MM_RX_SMD_ERR_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MM_RX_SMD_ERR_CNT_MM_RX_SMD_ERR_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MM_RX_SMD_ERR_CNT_MM_RX_SMD_ERR_CNT(x)  (x)


/**
 * \brief Counts Pframes that are successfully  re-assembled and sent to PMAC .
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_MM_RX_ASSEMBLY_OK_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MM_RX_ASSEMBLY_OK_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf162)

/**
 * \brief
 * MAC MERGE - The number of Pframes received whitch are successfully
 * reassembled .
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MM_RX_ASSEMBLY_OK_CNT . MM_RX_ASSEMBLY_OK_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MM_RX_ASSEMBLY_OK_CNT_MM_RX_ASSEMBLY_OK_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MM_RX_ASSEMBLY_OK_CNT_MM_RX_ASSEMBLY_OK_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MM_RX_ASSEMBLY_OK_CNT_MM_RX_ASSEMBLY_OK_CNT(x)  (x)


/**
 * \brief Counts Pframes which are mPackets (fragments) due to preemption.
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_MM_RX_MERGE_FRAG_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MM_RX_MERGE_FRAG_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf163)

/**
 * \brief
 * MAC MERGE - The number of Pframes received whitch are mPackets
 * (Fragments) due to preemption .
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MM_RX_MERGE_FRAG_CNT . MM_RX_MERGE_FRAG_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MM_RX_MERGE_FRAG_CNT_MM_RX_MERGE_FRAG_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MM_RX_MERGE_FRAG_CNT_MM_RX_MERGE_FRAG_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MM_RX_MERGE_FRAG_CNT_MM_RX_MERGE_FRAG_CNT(x)  (x)


/**
 * \brief Counts pframe fragment sent when preemption enabled .
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_32BIT:HOST_MAC_MM_TX_PFRAGMENT_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MM_TX_PFRAGMENT_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf164)

/**
 * \brief
 * MAC MERGE - The number of Pframe fragments sent when preemption enabled
 * .
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MM_TX_PFRAGMENT_CNT . MM_TX_PFRAGMENT_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MM_TX_PFRAGMENT_CNT_MM_TX_PFRAGMENT_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MM_TX_PFRAGMENT_CNT_MM_TX_PFRAGMENT_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MM_TX_PFRAGMENT_CNT_MM_TX_PFRAGMENT_CNT(x)  (x)

/**
 * Register Group: \a HOST_MAC:HOST_MAC_STATISTICS_64BIT
 *
 * Not documented
 */


/**
 * \brief Rx bad bytes counter (LSB)
 *
 * \details
 * The number of received bytes in bad frames (LSBs only).
 *
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_64BIT:HOST_MAC_RX_BAD_BYTES_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_BAD_BYTES_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf165)

/**
 * \brief
 * The number of received bytes in bad frames (LSBs only).
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_BAD_BYTES_CNT . RX_BAD_BYTES_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_BAD_BYTES_CNT_RX_BAD_BYTES_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_BAD_BYTES_CNT_RX_BAD_BYTES_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_BAD_BYTES_CNT_RX_BAD_BYTES_CNT(x)  (x)


/**
 * \brief Rx bad bytes counter (MSB)
 *
 * \details
 * The number of received bytes in bad frames (MSBs only).
 *
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_64BIT:HOST_MAC_RX_BAD_BYTES_MSB_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_BAD_BYTES_MSB_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf166)

/**
 * \brief
 * The number of received bytes in bad frames (MSBs only).
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_BAD_BYTES_MSB_CNT . RX_BAD_BYTES_MSB_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_BAD_BYTES_MSB_CNT_RX_BAD_BYTES_MSB_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_BAD_BYTES_MSB_CNT_RX_BAD_BYTES_MSB_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_BAD_BYTES_MSB_CNT_RX_BAD_BYTES_MSB_CNT(x)  (x)


/**
 * \brief Rx OK bytes counter (LSB)
 *
 * \details
 * The number of received bytes in good frames (LSBs only).
 *
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_64BIT:HOST_MAC_RX_OK_BYTES_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_OK_BYTES_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf167)

/**
 * \brief
 * The number of received bytes in good frames (LSBs only).
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_OK_BYTES_CNT . RX_OK_BYTES_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_OK_BYTES_CNT_RX_OK_BYTES_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_OK_BYTES_CNT_RX_OK_BYTES_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_OK_BYTES_CNT_RX_OK_BYTES_CNT(x)  (x)


/**
 * \brief Rx OK bytes counter (MSB)
 *
 * \details
 * The number of received bytes in good frames (MSBs only).
 *
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_64BIT:HOST_MAC_RX_OK_BYTES_MSB_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_OK_BYTES_MSB_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf168)

/**
 * \brief
 * The number of received bytes in good frames (MSBs only).
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_OK_BYTES_MSB_CNT . RX_OK_BYTES_MSB_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_OK_BYTES_MSB_CNT_RX_OK_BYTES_MSB_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_OK_BYTES_MSB_CNT_RX_OK_BYTES_MSB_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_OK_BYTES_MSB_CNT_RX_OK_BYTES_MSB_CNT(x)  (x)


/**
 * \brief Rx bytes received counter (LSB)
 *
 * \details
 * The number of good, bad, and framing bytes received (LSBs only).
 *
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_64BIT:HOST_MAC_RX_IN_BYTES_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_IN_BYTES_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf169)

/**
 * \brief
 * The number of good, bad, and framing bytes received (LSBs only).
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_IN_BYTES_CNT . RX_IN_BYTES_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_IN_BYTES_CNT_RX_IN_BYTES_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_IN_BYTES_CNT_RX_IN_BYTES_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_IN_BYTES_CNT_RX_IN_BYTES_CNT(x)  (x)


/**
 * \brief Rx bytes received counter (MSB)
 *
 * \details
 * The number of good, bad, and framing bytes received (MSBs only).
 *
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_64BIT:HOST_MAC_RX_IN_BYTES_MSB_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_RX_IN_BYTES_MSB_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf16a)

/**
 * \brief
 * The number of good, bad, and framing bytes received (MSBs only).
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_RX_IN_BYTES_MSB_CNT . RX_IN_BYTES_MSB_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_RX_IN_BYTES_MSB_CNT_RX_IN_BYTES_MSB_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_RX_IN_BYTES_MSB_CNT_RX_IN_BYTES_MSB_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_RX_IN_BYTES_MSB_CNT_RX_IN_BYTES_MSB_CNT(x)  (x)


/**
 * \brief Tx OK bytes counter (LSB)
 *
 * \details
 * The number of bytes transmitted successfully (LSBs only).
 *
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_64BIT:HOST_MAC_TX_OK_BYTES_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_TX_OK_BYTES_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf16b)

/**
 * \brief
 * The number of bytes transmitted successfully (LSBs only).
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_TX_OK_BYTES_CNT . TX_OK_BYTES_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_TX_OK_BYTES_CNT_TX_OK_BYTES_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_TX_OK_BYTES_CNT_TX_OK_BYTES_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_TX_OK_BYTES_CNT_TX_OK_BYTES_CNT(x)  (x)


/**
 * \brief Tx OK bytes counter (MSB)
 *
 * \details
 * The number of bytes transmitted successfully (MSBs only).
 *
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_64BIT:HOST_MAC_TX_OK_BYTES_MSB_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_TX_OK_BYTES_MSB_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf16c)

/**
 * \brief
 * The number of bytes transmitted successfully (MSBs only).
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_TX_OK_BYTES_MSB_CNT . TX_OK_BYTES_MSB_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_TX_OK_BYTES_MSB_CNT_TX_OK_BYTES_MSB_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_TX_OK_BYTES_MSB_CNT_TX_OK_BYTES_MSB_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_TX_OK_BYTES_MSB_CNT_TX_OK_BYTES_MSB_CNT(x)  (x)


/**
 * \brief Tx bytes transmitted counter (LSB)
 *
 * \details
 * The number of good, bad, and framing bytes transmitted (LSBs only).
 *
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_64BIT:HOST_MAC_TX_OUT_BYTES_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_TX_OUT_BYTES_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf16d)

/**
 * \brief
 * The number of good, bad, and framing bytes transmitted (LSBs only).
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_TX_OUT_BYTES_CNT . TX_OUT_BYTES_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_TX_OUT_BYTES_CNT_TX_OUT_BYTES_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_TX_OUT_BYTES_CNT_TX_OUT_BYTES_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_TX_OUT_BYTES_CNT_TX_OUT_BYTES_CNT(x)  (x)


/**
 * \brief Tx bytes transmitted counter (MSB)
 *
 * \details
 * The number of good, bad, and framing bytes transmitted (MSBs only).
 *
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_64BIT:HOST_MAC_TX_OUT_BYTES_MSB_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_TX_OUT_BYTES_MSB_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf16e)

/**
 * \brief
 * The number of good, bad, and framing bytes transmitted (MSBs only).
 *
 * \details
 * Counter can be written by software.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_TX_OUT_BYTES_MSB_CNT . TX_OUT_BYTES_MSB_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_TX_OUT_BYTES_MSB_CNT_TX_OUT_BYTES_MSB_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_TX_OUT_BYTES_MSB_CNT_TX_OUT_BYTES_MSB_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_TX_OUT_BYTES_MSB_CNT_TX_OUT_BYTES_MSB_CNT(x)  (x)


/**
 * \brief Rx OK Byte Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_64BIT:HOST_MAC_PMAC_RX_OK_BYTES_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_OK_BYTES_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf16f)

/**
 * \brief
 * PMAC - The number of received bytes in good frames.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_OK_BYTES_CNT . PMAC_RX_OK_BYTES_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_OK_BYTES_CNT_PMAC_RX_OK_BYTES_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_OK_BYTES_CNT_PMAC_RX_OK_BYTES_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_OK_BYTES_CNT_PMAC_RX_OK_BYTES_CNT(x)  (x)


/**
 * \brief Rx Ok Bytes Counter - MSB part
 *
 * \details
 * PMAC - The number of received bytes in good frames - MSBs only
 *
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_64BIT:HOST_MAC_PMAC_RX_OK_BYTES_MSB_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_OK_BYTES_MSB_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf170)

/**
 * \brief
 * PMAC - The number of received bytes in good frames - MSBs only.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_OK_BYTES_MSB_CNT . PMAC_RX_OK_BYTES_MSB_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_OK_BYTES_MSB_CNT_PMAC_RX_OK_BYTES_MSB_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_OK_BYTES_MSB_CNT_PMAC_RX_OK_BYTES_MSB_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_OK_BYTES_MSB_CNT_PMAC_RX_OK_BYTES_MSB_CNT(x)  (x)


/**
 * \brief Rx Bad Byte Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_64BIT:HOST_MAC_PMAC_RX_BAD_BYTES_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_BAD_BYTES_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf171)

/**
 * \brief
 * PMAC - The number of received bytes in bad frames.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_BAD_BYTES_CNT . PMAC_RX_BAD_BYTES_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_BAD_BYTES_CNT_PMAC_RX_BAD_BYTES_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_BAD_BYTES_CNT_PMAC_RX_BAD_BYTES_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_BAD_BYTES_CNT_PMAC_RX_BAD_BYTES_CNT(x)  (x)


/**
 * \brief Rx Bad Bytes Counter - MSB part
 *
 * \details
 * PMAC - The number of received bytes in bad frames -  MSBs only.
 *
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_64BIT:HOST_MAC_PMAC_RX_BAD_BYTES_MSB_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_BAD_BYTES_MSB_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf172)

/**
 * \brief
 * PMAC - The number of received bytes in bad frames - MSBs only.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_RX_BAD_BYTES_MSB_CNT . PMAC_RX_BAD_BYTES_MSB_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_RX_BAD_BYTES_MSB_CNT_PMAC_RX_BAD_BYTES_MSB_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_RX_BAD_BYTES_MSB_CNT_PMAC_RX_BAD_BYTES_MSB_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_RX_BAD_BYTES_MSB_CNT_PMAC_RX_BAD_BYTES_MSB_CNT(x)  (x)


/**
 * \brief Tx OK Byte Counter
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_64BIT:HOST_MAC_PMAC_TX_OK_BYTES_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_OK_BYTES_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf173)

/**
 * \brief
 * PMAC - The number of bytes transmitted successfully.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_OK_BYTES_CNT . PMAC_TX_OK_BYTES_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_TX_OK_BYTES_CNT_PMAC_TX_OK_BYTES_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_TX_OK_BYTES_CNT_PMAC_TX_OK_BYTES_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_TX_OK_BYTES_CNT_PMAC_TX_OK_BYTES_CNT(x)  (x)


/**
 * \brief Tx OK Bytes Counter - MSB part
Tx OK Bytes Counter - MSB
 *
 * \details
 * PMAC - The number of bytes transmitted - MSBs only.
 *
 * Register: \a HOST_MAC:HOST_MAC_STATISTICS_64BIT:HOST_MAC_PMAC_TX_OK_BYTES_MSB_CNT
 */
#define LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_OK_BYTES_MSB_CNT  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1,0xf174)

/**
 * \brief
 * PMAC - The number of transmitted bytes transmitted successfully - MSBs
 * only.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_PMAC_TX_OK_BYTES_MSB_CNT . PMAC_TX_OK_BYTES_MSB_CNT
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_PMAC_TX_OK_BYTES_MSB_CNT_PMAC_TX_OK_BYTES_MSB_CNT(x)  (x)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_TX_OK_BYTES_MSB_CNT_PMAC_TX_OK_BYTES_MSB_CNT     0xffffffff
#define  LAN80XX_X_HOST_MAC_HOST_MAC_PMAC_TX_OK_BYTES_MSB_CNT_PMAC_TX_OK_BYTES_MSB_CNT(x)  (x)

/**
 * Register Group: \a HOST_MAC:HOST_MAC_MM_CONFIG
 *
 * Configuration of Mac Merge block for this port
 */


/**
 * \brief Enables the MAC Merge layer for this port
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_MM_CONFIG:HOST_MAC_ENABLE_CONFIG
 */
#define LAN80XX_HOST_MAC_HOST_MAC_ENABLE_CONFIG  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf175)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_ENABLE_CONFIG . MM_RX_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_ENABLE_CONFIG_MM_RX_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_ENABLE_CONFIG_MM_RX_ENA  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_ENABLE_CONFIG_MM_RX_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_ENABLE_CONFIG . MM_TX_ENA
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_ENABLE_CONFIG_MM_TX_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_ENABLE_CONFIG_MM_TX_ENA  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_ENABLE_CONFIG_MM_TX_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_ENABLE_CONFIG . KEEP_S_AFTER_D
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_ENABLE_CONFIG_KEEP_S_AFTER_D(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_ENABLE_CONFIG_KEEP_S_AFTER_D  LAN80XX_BIT(8)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_ENABLE_CONFIG_KEEP_S_AFTER_D(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)


/**
 * \brief Configuration to control the Preemption Verification-Response behavior of port.
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_MM_CONFIG:HOST_MAC_VERIF_CONFIG
 */
#define LAN80XX_HOST_MAC_HOST_MAC_VERIF_CONFIG  LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf176)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_VERIF_CONFIG . PRM_VERIFY_DIS
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_VERIF_CONFIG_PRM_VERIFY_DIS(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_VERIF_CONFIG_PRM_VERIFY_DIS  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_VERIF_CONFIG_PRM_VERIFY_DIS(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_VERIF_CONFIG . PRM_VERIFY_TIME
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_VERIF_CONFIG_PRM_VERIFY_TIME(x)  LAN80XX_ENCODE_BITFIELD(x,4,8)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_VERIF_CONFIG_PRM_VERIFY_TIME     LAN80XX_ENCODE_BITMASK(4,8)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_VERIF_CONFIG_PRM_VERIFY_TIME(x)  LAN80XX_EXTRACT_BITFIELD(x,4,8)

/**
 * \brief
 * Sets the unit of PRM_VERIFY_TIME register to one of below:0 :
 * denomination of 1 ms (Default) at 5G speeds1 : denomination of 1011 ns =
 * 1.01 us at 5G speeds2 : denomination of 1 ms time at 10G speeds3 :
 * denomination of 1004.8ns = 1.0048 us time at 10G speedsThe actual timer
 * value is PRM_VERIFY_TIME * (decoded FAST_TIMER
 * denomination).Denomination of 1.01 is used so as to be multiplied by
 * 12.8 ns(12.8 * 79 = 1011).The denominations of 2, 3 are supposed to be
 * used for 10G speeds. And here, 1.0048us is used because 6.4*157 =
 * 1004.8us
 *
 * \details
 * 0 : denomination of 1 ms (Default) at 5G speeds
 * 1 : denomination of 1011 ns = 1.01 us at 5G speeds
 * 2 : denomination of 1 ms time at 10G speeds
 * 3 : denomination of 1004.8ns = 1.0048 us time at 10G speeds
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_VERIF_CONFIG . VERIF_TIMER_UNITS
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_VERIF_CONFIG_VERIF_TIMER_UNITS(x)  LAN80XX_ENCODE_BITFIELD(x,12,2)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_VERIF_CONFIG_VERIF_TIMER_UNITS     LAN80XX_ENCODE_BITMASK(12,2)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_VERIF_CONFIG_VERIF_TIMER_UNITS(x)  LAN80XX_EXTRACT_BITFIELD(x,12,2)

/**
 * Register Group: \a HOST_MAC:HOST_MAC_MM_STATISTICS
 *
 * Statistics for MAC Merge Layer
 */


/**
 * \brief Status of MAC Merge layer of this port.
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_MM_STATISTICS:HOST_MAC_MM_STATUS
 */
#define LAN80XX_HOST_MAC_HOST_MAC_MM_STATUS     LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf177)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MM_STATUS . PRMPT_ACTIVE_STATUS
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MM_STATUS_PRMPT_ACTIVE_STATUS(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MM_STATUS_PRMPT_ACTIVE_STATUS  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MM_STATUS_PRMPT_ACTIVE_STATUS(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * A sticky bit indicating there was a change in prmption state of this
 * port.
 *
 * \details
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MM_STATUS . PRMPT_ACTIVE_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MM_STATUS_PRMPT_ACTIVE_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MM_STATUS_PRMPT_ACTIVE_STICKY  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MM_STATUS_PRMPT_ACTIVE_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Interrupt mask for PRMPT_ACTIVE_STICKY
 *
 * \details
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MM_STATUS . PRMPT_ACTIVE_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MM_STATUS_PRMPT_ACTIVE_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),5,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MM_STATUS_PRMPT_ACTIVE_STICKY_MASK  LAN80XX_BIT(5)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MM_STATUS_PRMPT_ACTIVE_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MM_STATUS . PRMPT_VERIFY_STATE
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MM_STATUS_PRMPT_VERIFY_STATE(x)  LAN80XX_ENCODE_BITFIELD(x,8,3)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MM_STATUS_PRMPT_VERIFY_STATE     LAN80XX_ENCODE_BITMASK(8,3)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MM_STATUS_PRMPT_VERIFY_STATE(x)  LAN80XX_EXTRACT_BITFIELD(x,8,3)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MM_STATUS . UNEXP_RX_PFRM_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MM_STATUS_UNEXP_RX_PFRM_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),12,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MM_STATUS_UNEXP_RX_PFRM_STICKY  LAN80XX_BIT(12)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MM_STATUS_UNEXP_RX_PFRM_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Interrupt mask for UNEXP_RX_PFRM_STICKY
 *
 * \details
 * 1 - Enable Interrupt.
 * 0 - Disable Interrupt.

 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MM_STATUS . UNEXP_RX_PFRM_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MM_STATUS_UNEXP_RX_PFRM_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),13,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MM_STATUS_UNEXP_RX_PFRM_STICKY_MASK  LAN80XX_BIT(13)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MM_STATUS_UNEXP_RX_PFRM_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,13,1)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MM_STATUS . UNEXP_TX_PFRM_STICKY
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MM_STATUS_UNEXP_TX_PFRM_STICKY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),16,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MM_STATUS_UNEXP_TX_PFRM_STICKY  LAN80XX_BIT(16)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MM_STATUS_UNEXP_TX_PFRM_STICKY(x)  LAN80XX_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Interrupt mask for UNEXP_TX_PFRM_STICKY
 *
 * \details
 * 1 - Enable Interrupt.
 * 0 - Disable Interrupt.
 *
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MM_STATUS . UNEXP_TX_PFRM_STICKY_MASK
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MM_STATUS_UNEXP_TX_PFRM_STICKY_MASK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),17,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MM_STATUS_UNEXP_TX_PFRM_STICKY_MASK  LAN80XX_BIT(17)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MM_STATUS_UNEXP_TX_PFRM_STICKY_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,17,1)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MM_STATUS . MM_RX_FRAME_STATUS
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MM_STATUS_MM_RX_FRAME_STATUS(x)  LAN80XX_ENCODE_BITFIELD(!!(x),20,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MM_STATUS_MM_RX_FRAME_STATUS  LAN80XX_BIT(20)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MM_STATUS_MM_RX_FRAME_STATUS(x)  LAN80XX_EXTRACT_BITFIELD(x,20,1)

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
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MM_STATUS . MM_TX_FRAME_STATUS
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MM_STATUS_MM_TX_FRAME_STATUS(x)  LAN80XX_ENCODE_BITFIELD(!!(x),24,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MM_STATUS_MM_TX_FRAME_STATUS  LAN80XX_BIT(24)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MM_STATUS_MM_TX_FRAME_STATUS(x)  LAN80XX_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Status bit indicating when a preemptible packet is to be preempted. '1'
 * : A P-frame is being preempted from this MM TX MAC.'0' : No P-frames are
 * preempted because of no requests from E-MAC and because of min_frag_size
 * check and because of no hold requests.
 *
 * \details
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_MM_STATUS . MM_TX_PRMPT_STATUS
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_MM_STATUS_MM_TX_PRMPT_STATUS(x)  LAN80XX_ENCODE_BITFIELD(!!(x),28,1)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_MM_STATUS_MM_TX_PRMPT_STATUS  LAN80XX_BIT(28)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_MM_STATUS_MM_TX_PRMPT_STATUS(x)  LAN80XX_EXTRACT_BITFIELD(x,28,1)

/**
 * Register Group: \a HOST_MAC:HOST_MAC_DEBUG
 *
 * Debug Registers
 */


/**
 * \brief Debug read only register 0
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_DEBUG:HOST_MAC_DEBUG_RO_0
 */
#define LAN80XX_HOST_MAC_HOST_MAC_DEBUG_RO_0    LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf178)

/**
 * \brief
 * Debug read only register 0
 *
 * \details
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_DEBUG_RO_0 . DEBUG_RO_0
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_DEBUG_RO_0_DEBUG_RO_0(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_DEBUG_RO_0_DEBUG_RO_0     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_DEBUG_RO_0_DEBUG_RO_0(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug read only register 1
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_DEBUG:HOST_MAC_DEBUG_RO_1
 */
#define LAN80XX_HOST_MAC_HOST_MAC_DEBUG_RO_1    LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf179)

/**
 * \brief
 * Debug read only register 1
 *
 * \details
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_DEBUG_RO_1 . DEBUG_RO_1
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_DEBUG_RO_1_DEBUG_RO_1(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_DEBUG_RO_1_DEBUG_RO_1     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_DEBUG_RO_1_DEBUG_RO_1(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug read only register 2
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_DEBUG:HOST_MAC_DEBUG_RO_2
 */
#define LAN80XX_HOST_MAC_HOST_MAC_DEBUG_RO_2    LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf17a)

/**
 * \brief
 * Debug read only register 2
 *
 * \details
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_DEBUG_RO_2 . DEBUG_RO_2
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_DEBUG_RO_2_DEBUG_RO_2(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_DEBUG_RO_2_DEBUG_RO_2     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_DEBUG_RO_2_DEBUG_RO_2(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug read only register 3
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_DEBUG:HOST_MAC_DEBUG_RO_3
 */
#define LAN80XX_HOST_MAC_HOST_MAC_DEBUG_RO_3    LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf17b)

/**
 * \brief
 * Debug read only register 3
 *
 * \details
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_DEBUG_RO_3 . DEBUG_RO_3
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_DEBUG_RO_3_DEBUG_RO_3(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_DEBUG_RO_3_DEBUG_RO_3     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_DEBUG_RO_3_DEBUG_RO_3(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug read only register 4
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_DEBUG:HOST_MAC_DEBUG_RO_4
 */
#define LAN80XX_HOST_MAC_HOST_MAC_DEBUG_RO_4    LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf17c)

/**
 * \brief
 * Debug read only register 4
 *
 * \details
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_DEBUG_RO_4 . DEBUG_RO_4
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_DEBUG_RO_4_DEBUG_RO_4(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_DEBUG_RO_4_DEBUG_RO_4     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_DEBUG_RO_4_DEBUG_RO_4(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug read only register 5
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_DEBUG:HOST_MAC_DEBUG_RO_5
 */
#define LAN80XX_HOST_MAC_HOST_MAC_DEBUG_RO_5    LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf17d)

/**
 * \brief
 * Debug read only register 5
 *
 * \details
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_DEBUG_RO_5 . DEBUG_RO_5
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_DEBUG_RO_5_DEBUG_RO_5(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_DEBUG_RO_5_DEBUG_RO_5     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_DEBUG_RO_5_DEBUG_RO_5(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug read only register 6
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_DEBUG:HOST_MAC_DEBUG_RO_6
 */
#define LAN80XX_HOST_MAC_HOST_MAC_DEBUG_RO_6    LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf17e)

/**
 * \brief
 * Debug read only register 6
 *
 * \details
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_DEBUG_RO_6 . DEBUG_RO_6
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_DEBUG_RO_6_DEBUG_RO_6(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_DEBUG_RO_6_DEBUG_RO_6     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_DEBUG_RO_6_DEBUG_RO_6(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug read only register 6
 *
 * \details
 * Register: \a HOST_MAC:HOST_MAC_DEBUG:HOST_MAC_DEBUG_RW
 */
#define LAN80XX_HOST_MAC_HOST_MAC_DEBUG_RW      LAN80XX_IOREG(MMD_ID_HOST_MAC, 1, 0xf17f)

/**
 * \brief
 * Debug read only register 6
 *
 * \details
 * Field: ::LAN80XX_HOST_MAC_HOST_MAC_DEBUG_RW . DEBUG_RW
 */
#define  LAN80XX_F_HOST_MAC_HOST_MAC_DEBUG_RW_DEBUG_RW(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_MAC_HOST_MAC_DEBUG_RW_DEBUG_RW     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_MAC_HOST_MAC_DEBUG_RW_DEBUG_RW(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


#endif /* _LAN80XX_MALIBU25G_REGS_HOST_MAC_H_ */
