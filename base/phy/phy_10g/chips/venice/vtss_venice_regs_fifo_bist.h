// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_VENICE_REGS_FIFO_BIST_H_
#define _VTSS_VENICE_REGS_FIFO_BIST_H_


#include "vtss_venice_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a FIFO_BIST
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a FIFO_BIST:GEN_CFG
 *
 * Not documented
 */


/** 
 * \brief Generator configuration
 *
 * \details
 * Register: \a FIFO_BIST:GEN_CFG:GEN_CFG
 */
#define VTSS_FIFO_BIST_GEN_CFG_GEN_CFG       VTSS_IOREG(0x04, 0, 0xe900)

/** 
 * \brief
 * Decrease pktlen by lenofs
 *
 * \details 
 * Field: VTSS_FIFO_BIST_GEN_CFG_GEN_CFG . LENOFS
 */
#define  VTSS_F_FIFO_BIST_GEN_CFG_GEN_CFG_LENOFS(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_FIFO_BIST_GEN_CFG_GEN_CFG_LENOFS     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_FIFO_BIST_GEN_CFG_GEN_CFG_LENOFS(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/** 
 * \brief
 * Number of standard frames between PTP frames
 *
 * \details 
 * Field: VTSS_FIFO_BIST_GEN_CFG_GEN_CFG . SRATE
 */
#define  VTSS_F_FIFO_BIST_GEN_CFG_GEN_CFG_SRATE(x)  VTSS_ENCODE_BITFIELD(x,4,8)
#define  VTSS_M_FIFO_BIST_GEN_CFG_GEN_CFG_SRATE     VTSS_ENCODE_BITMASK(4,8)
#define  VTSS_X_FIFO_BIST_GEN_CFG_GEN_CFG_SRATE(x)  VTSS_EXTRACT_BITFIELD(x,4,8)

/** 
 * \brief
 * Generate all Idles 
 *
 * \details 
 * 0: Generate frames
 * 1: Generate idles only
 *
 * Field: VTSS_FIFO_BIST_GEN_CFG_GEN_CFG . IDLES
 */
#define  VTSS_F_FIFO_BIST_GEN_CFG_GEN_CFG_IDLES  VTSS_BIT(2)

/** 
 * \brief
 * Generate PTP frames 
 *
 * \details 
 * 0: Generate standard frames
 * 1: Generate PTP frames
 *
 * Field: VTSS_FIFO_BIST_GEN_CFG_GEN_CFG . PTP_ENABLE
 */
#define  VTSS_F_FIFO_BIST_GEN_CFG_GEN_CFG_PTP_ENABLE  VTSS_BIT(1)

/** 
 * \brief
 * Enable packet generator 
 *
 * \details 
 * 0: Generator is disabled
 * 1: Generator is enabled
 * Note:   Pattern generator data can not simultaneously be inserted in the
 * egress and ingress data paths.  Insertion of pattern generator data into
 * the paths is controlled by Datapath_Control.IGR_XGMII_PG_SEL and
 * Datapath_Control.EGR_XGMII_PG_SEL.
 *
 * Field: VTSS_FIFO_BIST_GEN_CFG_GEN_CFG . ENABLE
 */
#define  VTSS_F_FIFO_BIST_GEN_CFG_GEN_CFG_ENABLE  VTSS_BIT(0)

/**
 * Register Group: \a FIFO_BIST:UPDATE
 *
 * Not documented
 */


/** 
 * \brief Self-clearing pulse to latch all counters
 *
 * \details
 * Register: \a FIFO_BIST:UPDATE:UPDATE
 */
#define VTSS_FIFO_BIST_UPDATE_UPDATE         VTSS_IOREG(0x04, 0, 0xe901)

/** 
 * \brief
 * Freeze all generator and monitor counters for readback
 *
 * \details 
 * Field: VTSS_FIFO_BIST_UPDATE_UPDATE . UPDATE
 */
#define  VTSS_F_FIFO_BIST_UPDATE_UPDATE_UPDATE  VTSS_BIT(0)

/**
 * Register Group: \a FIFO_BIST:GEN_PKTLEN
 *
 * Not documented
 */


/** 
 * \brief Packet length
 *
 * \details
 * Register: \a FIFO_BIST:GEN_PKTLEN:GEN_PKTLEN
 */
#define VTSS_FIFO_BIST_GEN_PKTLEN_GEN_PKTLEN  VTSS_IOREG(0x04, 0, 0xe902)

/** 
 * \brief
 * Packet length: packet bytes = header + pktlen*64 + (8-lenofs)
 *
 * \details 
 * Field: VTSS_FIFO_BIST_GEN_PKTLEN_GEN_PKTLEN . PKTLEN
 */
#define  VTSS_F_FIFO_BIST_GEN_PKTLEN_GEN_PKTLEN_PKTLEN(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FIFO_BIST_GEN_PKTLEN_GEN_PKTLEN_PKTLEN     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FIFO_BIST_GEN_PKTLEN_GEN_PKTLEN_PKTLEN(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a FIFO_BIST:GEN_IPGLEN
 *
 * Not documented
 */


/** 
 * \brief IPG length
 *
 * \details
 * Register: \a FIFO_BIST:GEN_IPGLEN:GEN_IPGLEN
 */
#define VTSS_FIFO_BIST_GEN_IPGLEN_GEN_IPGLEN  VTSS_IOREG(0x04, 0, 0xe903)

/** 
 * \brief
 * IPG length: /I/ bytes = lenofs + ipglen*4
 *
 * \details 
 * Field: VTSS_FIFO_BIST_GEN_IPGLEN_GEN_IPGLEN . IPGLEN
 */
#define  VTSS_F_FIFO_BIST_GEN_IPGLEN_GEN_IPGLEN_IPGLEN(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_IPGLEN_GEN_IPGLEN_IPGLEN     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_IPGLEN_GEN_IPGLEN_IPGLEN(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:GEN_TIME
 *
 * Not documented
 */


/** 
 * \brief PTP timestamp
 *
 * \details
 * Register: \a FIFO_BIST:GEN_TIME:GEN_TIME
 */
#define VTSS_FIFO_BIST_GEN_TIME_GEN_TIME     VTSS_IOREG(0x04, 0, 0xe904)

/** 
 * \brief
 * PTP timestamp to generate: [15:8] is seconds, [7:0] is ns
 *
 * \details 
 * Field: VTSS_FIFO_BIST_GEN_TIME_GEN_TIME . PTPTIME
 */
#define  VTSS_F_FIFO_BIST_GEN_TIME_GEN_TIME_PTPTIME(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_TIME_GEN_TIME_PTPTIME     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_TIME_GEN_TIME_PTPTIME(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:GEN_ETYPE
 *
 * Not documented
 */


/** 
 * \brief Ethernet type
 *
 * \details
 * Register: \a FIFO_BIST:GEN_ETYPE:GEN_ETYPE
 */
#define VTSS_FIFO_BIST_GEN_ETYPE_GEN_ETYPE   VTSS_IOREG(0x04, 0, 0xe905)

/** 
 * \brief
 * Etype field for standard frames
 *
 * \details 
 * Field: VTSS_FIFO_BIST_GEN_ETYPE_GEN_ETYPE . ETYPE
 */
#define  VTSS_F_FIFO_BIST_GEN_ETYPE_GEN_ETYPE_ETYPE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_ETYPE_GEN_ETYPE_ETYPE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_ETYPE_GEN_ETYPE_ETYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:GEN_SA
 *
 * Not documented
 */


/** 
 * \brief Lower 16 bits of 48-bit source address to generate
 *
 * \details
 * Register: \a FIFO_BIST:GEN_SA:GEN_SA0
 */
#define VTSS_FIFO_BIST_GEN_SA_GEN_SA0        VTSS_IOREG(0x04, 0, 0xe910)

/** 
 * \brief
 * Generated source address [15:0]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_GEN_SA_GEN_SA0 . SA0
 */
#define  VTSS_F_FIFO_BIST_GEN_SA_GEN_SA0_SA0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_SA_GEN_SA0_SA0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_SA_GEN_SA0_SA0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Middle 16 bits of 48-bit source address to generate
 *
 * \details
 * Register: \a FIFO_BIST:GEN_SA:GEN_SA1
 */
#define VTSS_FIFO_BIST_GEN_SA_GEN_SA1        VTSS_IOREG(0x04, 0, 0xe911)

/** 
 * \brief
 * Generated source address [31:16]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_GEN_SA_GEN_SA1 . SA1
 */
#define  VTSS_F_FIFO_BIST_GEN_SA_GEN_SA1_SA1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_SA_GEN_SA1_SA1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_SA_GEN_SA1_SA1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Upper 16 bits of 48-bit source address to generate
 *
 * \details
 * Register: \a FIFO_BIST:GEN_SA:GEN_SA2
 */
#define VTSS_FIFO_BIST_GEN_SA_GEN_SA2        VTSS_IOREG(0x04, 0, 0xe912)

/** 
 * \brief
 * Generated source address [47:32]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_GEN_SA_GEN_SA2 . SA2
 */
#define  VTSS_F_FIFO_BIST_GEN_SA_GEN_SA2_SA2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_SA_GEN_SA2_SA2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_SA_GEN_SA2_SA2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:GEN_DA
 *
 * Not documented
 */


/** 
 * \brief Lower 16 bits of 48-bit destination address to generate
 *
 * \details
 * Register: \a FIFO_BIST:GEN_DA:GEN_DA0
 */
#define VTSS_FIFO_BIST_GEN_DA_GEN_DA0        VTSS_IOREG(0x04, 0, 0xe920)

/** 
 * \brief
 * Generated destination address [15:0]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_GEN_DA_GEN_DA0 . DA0
 */
#define  VTSS_F_FIFO_BIST_GEN_DA_GEN_DA0_DA0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_DA_GEN_DA0_DA0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_DA_GEN_DA0_DA0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Middle 16 bits of 48-bit destination address to generate
 *
 * \details
 * Register: \a FIFO_BIST:GEN_DA:GEN_DA1
 */
#define VTSS_FIFO_BIST_GEN_DA_GEN_DA1        VTSS_IOREG(0x04, 0, 0xe921)

/** 
 * \brief
 * Generated destination address [31:16]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_GEN_DA_GEN_DA1 . DA1
 */
#define  VTSS_F_FIFO_BIST_GEN_DA_GEN_DA1_DA1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_DA_GEN_DA1_DA1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_DA_GEN_DA1_DA1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Upper 16 bits of 48-bit destination address to generate
 *
 * \details
 * Register: \a FIFO_BIST:GEN_DA:GEN_DA2
 */
#define VTSS_FIFO_BIST_GEN_DA_GEN_DA2        VTSS_IOREG(0x04, 0, 0xe922)

/** 
 * \brief
 * Generated destination address [47:32]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_GEN_DA_GEN_DA2 . DA2
 */
#define  VTSS_F_FIFO_BIST_GEN_DA_GEN_DA2_DA2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_DA_GEN_DA2_DA2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_DA_GEN_DA2_DA2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:GEN_SENT
 *
 * Not documented
 */


/** 
 * \brief Lower 16 bits of 32-bit packets_sent counter
 *
 * \details
 * Register: \a FIFO_BIST:GEN_SENT:GEN_SENT_LSW
 */
#define VTSS_FIFO_BIST_GEN_SENT_GEN_SENT_LSW  VTSS_IOREG(0x04, 0, 0xe930)

/** 
 * \brief
 * LSW of number of packets generated
 *
 * \details 
 * Field: VTSS_FIFO_BIST_GEN_SENT_GEN_SENT_LSW . SENT_LSW
 */
#define  VTSS_F_FIFO_BIST_GEN_SENT_GEN_SENT_LSW_SENT_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_SENT_GEN_SENT_LSW_SENT_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_SENT_GEN_SENT_LSW_SENT_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Upper 16 bits of 32-bit packets_sent counter
 *
 * \details
 * Register: \a FIFO_BIST:GEN_SENT:GEN_SENT_MSW
 */
#define VTSS_FIFO_BIST_GEN_SENT_GEN_SENT_MSW  VTSS_IOREG(0x04, 0, 0xe931)

/** 
 * \brief
 * MSW of number of packets generated
 *
 * \details 
 * Field: VTSS_FIFO_BIST_GEN_SENT_GEN_SENT_MSW . SENT_MSW
 */
#define  VTSS_F_FIFO_BIST_GEN_SENT_GEN_SENT_MSW_SENT_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_SENT_GEN_SENT_MSW_SENT_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_SENT_GEN_SENT_MSW_SENT_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:MON_CFG
 *
 * Not documented
 */


/** 
 * \brief monitor configuration
 *
 * \details
 * Register: \a FIFO_BIST:MON_CFG:MON_CFG
 */
#define VTSS_FIFO_BIST_MON_CFG_MON_CFG       VTSS_IOREG(0x04, 0, 0xe940)

/** 
 * \brief
 * Enable packet monitor 
 *
 * \details 
 * 0: Monitor is disabled
 * 1: Monitor is enabled
 *
 * Field: VTSS_FIFO_BIST_MON_CFG_MON_CFG . ENABLE
 */
#define  VTSS_F_FIFO_BIST_MON_CFG_MON_CFG_ENABLE  VTSS_BIT(0)

/**
 * Register Group: \a FIFO_BIST:MON_RST
 *
 * Not documented
 */


/** 
 * \brief Self-clearing monitor counters reset
 *
 * \details
 * Register: \a FIFO_BIST:MON_RST:MON_RST
 */
#define VTSS_FIFO_BIST_MON_RST_MON_RST       VTSS_IOREG(0x04, 0, 0xe950)

/** 
 * \brief
 * reset BER counter
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_FIFO_BIST_MON_RST_MON_RST . BER_RST
 */
#define  VTSS_F_FIFO_BIST_MON_RST_MON_RST_BER_RST  VTSS_BIT(4)

/** 
 * \brief
 * reset Local_Fault counter
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_FIFO_BIST_MON_RST_MON_RST . LFAULT_RST
 */
#define  VTSS_F_FIFO_BIST_MON_RST_MON_RST_LFAULT_RST  VTSS_BIT(3)

/** 
 * \brief
 * reset Packet_Fragment counter
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_FIFO_BIST_MON_RST_MON_RST . FRAG_RST
 */
#define  VTSS_F_FIFO_BIST_MON_RST_MON_RST_FRAG_RST  VTSS_BIT(2)

/** 
 * \brief
 * reset Bad_CRC counter
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_FIFO_BIST_MON_RST_MON_RST . BAD_RST
 */
#define  VTSS_F_FIFO_BIST_MON_RST_MON_RST_BAD_RST  VTSS_BIT(1)

/** 
 * \brief
 * reset Good_CRC counter
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_FIFO_BIST_MON_RST_MON_RST . GOOD_RST
 */
#define  VTSS_F_FIFO_BIST_MON_RST_MON_RST_GOOD_RST  VTSS_BIT(0)

/**
 * Register Group: \a FIFO_BIST:MON_STAT
 *
 * Not documented
 */


/** 
 * \brief monitor status
 *
 * \details
 * Register: \a FIFO_BIST:MON_STAT:MON_STAT
 */
#define VTSS_FIFO_BIST_MON_STAT_MON_STAT     VTSS_IOREG(0x04, 0, 0xe951)

/** 
 * \brief
 * Asserts when Good_CRCs >= crc_thr
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_STAT_MON_STAT . crc_pass
 */
#define  VTSS_F_FIFO_BIST_MON_STAT_MON_STAT_crc_pass  VTSS_BIT(0)

/**
 * Register Group: \a FIFO_BIST:MON_CRC_THR
 *
 * Not documented
 */


/** 
 * \brief Good_CRC count threshold
 *
 * \details
 * Register: \a FIFO_BIST:MON_CRC_THR:MON_CRC_THR
 */
#define VTSS_FIFO_BIST_MON_CRC_THR_MON_CRC_THR  VTSS_IOREG(0x04, 0, 0xe952)

/** 
 * \brief
 * Value of Good_CRCs before crc_pass asserts
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_CRC_THR_MON_CRC_THR . crc_thr
 */
#define  VTSS_F_FIFO_BIST_MON_CRC_THR_MON_CRC_THR_crc_thr(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_CRC_THR_MON_CRC_THR_crc_thr     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_CRC_THR_MON_CRC_THR_crc_thr(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:MON_GOODCRC
 *
 * Not documented
 */


/** 
 * \brief Lower 16 bits of 32-bit Good_CRC counter
 *
 * \details
 * Register: \a FIFO_BIST:MON_GOODCRC:MON_GOOD_LSW
 */
#define VTSS_FIFO_BIST_MON_GOODCRC_MON_GOOD_LSW  VTSS_IOREG(0x04, 0, 0xe960)

/** 
 * \brief
 * LSW of Good_CRC counter
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_GOODCRC_MON_GOOD_LSW . GOOD_LSW
 */
#define  VTSS_F_FIFO_BIST_MON_GOODCRC_MON_GOOD_LSW_GOOD_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_GOODCRC_MON_GOOD_LSW_GOOD_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_GOODCRC_MON_GOOD_LSW_GOOD_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Upper 16 bits of 32-bit Good_CRC counter
 *
 * \details
 * Register: \a FIFO_BIST:MON_GOODCRC:MON_GOOD_MSW
 */
#define VTSS_FIFO_BIST_MON_GOODCRC_MON_GOOD_MSW  VTSS_IOREG(0x04, 0, 0xe961)

/** 
 * \brief
 * MSW of Good_CRC counter
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_GOODCRC_MON_GOOD_MSW . GOOD_MSW
 */
#define  VTSS_F_FIFO_BIST_MON_GOODCRC_MON_GOOD_MSW_GOOD_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_GOODCRC_MON_GOOD_MSW_GOOD_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_GOODCRC_MON_GOOD_MSW_GOOD_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:MON_BADCRC
 *
 * Not documented
 */


/** 
 * \brief Lower 16 bits of 32-bit Bad_CRC counter
 *
 * \details
 * Register: \a FIFO_BIST:MON_BADCRC:MON_BAD_LSW
 */
#define VTSS_FIFO_BIST_MON_BADCRC_MON_BAD_LSW  VTSS_IOREG(0x04, 0, 0xe970)

/** 
 * \brief
 * LSW of Bad_CRC counter
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_BADCRC_MON_BAD_LSW . BAD_LSW
 */
#define  VTSS_F_FIFO_BIST_MON_BADCRC_MON_BAD_LSW_BAD_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_BADCRC_MON_BAD_LSW_BAD_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_BADCRC_MON_BAD_LSW_BAD_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Upper 16 bits of 32-bit Bad_CRC counter
 *
 * \details
 * Register: \a FIFO_BIST:MON_BADCRC:MON_BAD_MSW
 */
#define VTSS_FIFO_BIST_MON_BADCRC_MON_BAD_MSW  VTSS_IOREG(0x04, 0, 0xe971)

/** 
 * \brief
 * MSW of Bad_CRC counter
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_BADCRC_MON_BAD_MSW . BAD_MSW
 */
#define  VTSS_F_FIFO_BIST_MON_BADCRC_MON_BAD_MSW_BAD_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_BADCRC_MON_BAD_MSW_BAD_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_BADCRC_MON_BAD_MSW_BAD_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:MON_FRAG
 *
 * Not documented
 */


/** 
 * \brief Lower 16 bits of 32-bit Packet_Fragment counter
 *
 * \details
 * Register: \a FIFO_BIST:MON_FRAG:MON_FRAG_LSW
 */
#define VTSS_FIFO_BIST_MON_FRAG_MON_FRAG_LSW  VTSS_IOREG(0x04, 0, 0xe980)

/** 
 * \brief
 * LSW of Packet_Fragment counter
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_FRAG_MON_FRAG_LSW . FRAG_LSW
 */
#define  VTSS_F_FIFO_BIST_MON_FRAG_MON_FRAG_LSW_FRAG_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_FRAG_MON_FRAG_LSW_FRAG_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_FRAG_MON_FRAG_LSW_FRAG_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Upper 16 bits of 32-bit Packet_Fragment counter
 *
 * \details
 * Register: \a FIFO_BIST:MON_FRAG:MON_FRAG_MSW
 */
#define VTSS_FIFO_BIST_MON_FRAG_MON_FRAG_MSW  VTSS_IOREG(0x04, 0, 0xe981)

/** 
 * \brief
 * MSW of Packet_Fragment counter
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_FRAG_MON_FRAG_MSW . FRAG_MSW
 */
#define  VTSS_F_FIFO_BIST_MON_FRAG_MON_FRAG_MSW_FRAG_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_FRAG_MON_FRAG_MSW_FRAG_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_FRAG_MON_FRAG_MSW_FRAG_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:MON_LFAULT
 *
 * Not documented
 */


/** 
 * \brief Lower 16 bits of 32-bit Local_Fault counter
 *
 * \details
 * Register: \a FIFO_BIST:MON_LFAULT:MON_LFAULT_LSW
 */
#define VTSS_FIFO_BIST_MON_LFAULT_MON_LFAULT_LSW  VTSS_IOREG(0x04, 0, 0xe990)

/** 
 * \brief
 * LSW of Local_Fault counter
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_LFAULT_MON_LFAULT_LSW . LFAULT_LSW
 */
#define  VTSS_F_FIFO_BIST_MON_LFAULT_MON_LFAULT_LSW_LFAULT_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_LFAULT_MON_LFAULT_LSW_LFAULT_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_LFAULT_MON_LFAULT_LSW_LFAULT_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Upper 16 bits of 32-bit Local_Fault counter
 *
 * \details
 * Register: \a FIFO_BIST:MON_LFAULT:MON_LFAULT_MSW
 */
#define VTSS_FIFO_BIST_MON_LFAULT_MON_LFAULT_MSW  VTSS_IOREG(0x04, 0, 0xe991)

/** 
 * \brief
 * MSW of Local_Fault counter
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_LFAULT_MON_LFAULT_MSW . LFAULT_MSW
 */
#define  VTSS_F_FIFO_BIST_MON_LFAULT_MON_LFAULT_MSW_LFAULT_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_LFAULT_MON_LFAULT_MSW_LFAULT_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_LFAULT_MON_LFAULT_MSW_LFAULT_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:MON_BER
 *
 * Not documented
 */


/** 
 * \brief Lower 16 bits of 32-bit BER counter
 *
 * \details
 * Register: \a FIFO_BIST:MON_BER:MON_BER_LSW
 */
#define VTSS_FIFO_BIST_MON_BER_MON_BER_LSW   VTSS_IOREG(0x04, 0, 0xe9a0)

/** 
 * \brief
 * LSW of BER counter
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_BER_MON_BER_LSW . BER_LSW
 */
#define  VTSS_F_FIFO_BIST_MON_BER_MON_BER_LSW_BER_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_BER_MON_BER_LSW_BER_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_BER_MON_BER_LSW_BER_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Upper 16 bits of 32-bit BER counter
 *
 * \details
 * Register: \a FIFO_BIST:MON_BER:MON_BER_MSW
 */
#define VTSS_FIFO_BIST_MON_BER_MON_BER_MSW   VTSS_IOREG(0x04, 0, 0xe9a1)

/** 
 * \brief
 * MSW of BER counter
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_BER_MON_BER_MSW . BER_MSW
 */
#define  VTSS_F_FIFO_BIST_MON_BER_MON_BER_MSW_BER_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_BER_MON_BER_MSW_BER_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_BER_MON_BER_MSW_BER_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:MON_TSTAMP
 *
 * Not documented
 */


/** 
 * \brief PTP timestamp bits 15-0
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP:MON_TSTAMP0
 */
#define VTSS_FIFO_BIST_MON_TSTAMP_MON_TSTAMP0  VTSS_IOREG(0x04, 0, 0xe9b0)

/** 
 * \brief
 * Most recent PTP timestamp bits [15:0]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP_MON_TSTAMP0 . TSTAMP0
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP_MON_TSTAMP0_TSTAMP0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP_MON_TSTAMP0_TSTAMP0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP_MON_TSTAMP0_TSTAMP0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp bits 31-16
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP:MON_TSTAMP1
 */
#define VTSS_FIFO_BIST_MON_TSTAMP_MON_TSTAMP1  VTSS_IOREG(0x04, 0, 0xe9b1)

/** 
 * \brief
 * Most recent PTP timestamp bits [31:16]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP_MON_TSTAMP1 . TSTAMP1
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP_MON_TSTAMP1_TSTAMP1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP_MON_TSTAMP1_TSTAMP1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP_MON_TSTAMP1_TSTAMP1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp bits 47-32
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP:MON_TSTAMP2
 */
#define VTSS_FIFO_BIST_MON_TSTAMP_MON_TSTAMP2  VTSS_IOREG(0x04, 0, 0xe9b2)

/** 
 * \brief
 * Most recent PTP timestamp bits [47:32]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP_MON_TSTAMP2 . TSTAMP2
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP_MON_TSTAMP2_TSTAMP2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP_MON_TSTAMP2_TSTAMP2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP_MON_TSTAMP2_TSTAMP2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp bits 63-48
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP:MON_TSTAMP3
 */
#define VTSS_FIFO_BIST_MON_TSTAMP_MON_TSTAMP3  VTSS_IOREG(0x04, 0, 0xe9b3)

/** 
 * \brief
 * Most recent PTP timestamp bits [63:48]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP_MON_TSTAMP3 . TSTAMP3
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP_MON_TSTAMP3_TSTAMP3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP_MON_TSTAMP3_TSTAMP3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP_MON_TSTAMP3_TSTAMP3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp bits 79-64
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP:MON_TSTAMP4
 */
#define VTSS_FIFO_BIST_MON_TSTAMP_MON_TSTAMP4  VTSS_IOREG(0x04, 0, 0xe9b4)

/** 
 * \brief
 * Most recent PTP timestamp bits [79:64]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP_MON_TSTAMP4 . TSTAMP4
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP_MON_TSTAMP4_TSTAMP4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP_MON_TSTAMP4_TSTAMP4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP_MON_TSTAMP4_TSTAMP4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:RATE_COMP_FIFO_STAT
 *
 * Not documented
 */


/** 
 * \brief  Rate Compensation FIFO Status
 *
 * \details
 * Register: \a FIFO_BIST:RATE_COMP_FIFO_STAT:RATE_COMP_FIFO_STAT
 */
#define VTSS_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT  VTSS_IOREG(0x04, 0, 0xea00)

/** 
 * \brief
 * This is a sticky bit that latches the high state.  The latch-high bit is
 * cleared when the register is read.
 *
 * \details 
 * Status:
 * 0: No overflow
 * 1: Overflow
 *
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT . FIFO_Rx_overflow
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT_FIFO_Rx_overflow  VTSS_BIT(3)

/** 
 * \brief
 * This is a sticky bit that latches the high state.  The latch-high bit is
 * cleared when the register is read.
 *
 * \details 
 * Status:
 * 0: No underflow
 * 1: Underflow
 *
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT . FIFO_Rx_underflow
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT_FIFO_Rx_underflow  VTSS_BIT(2)

/** 
 * \brief
 * This is a sticky bit that latches the high state.  The latch-high bit is
 * cleared when the register is read.
 *
 * \details 
 * Status:
 * 0: No overflow
 * 1: Overflow
 *
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT . FIFO_Tx_overflow
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT_FIFO_Tx_overflow  VTSS_BIT(1)

/** 
 * \brief
 * This is a sticky bit that latches the high state.  The latch-high bit is
 * cleared when the register is read.
 *
 * \details 
 * Status:
 * 0: No underflow
 * 1: Underflow
 *
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT . FIFO_Tx_underflow
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT_FIFO_Tx_underflow  VTSS_BIT(0)

/**
 * Register Group: \a FIFO_BIST:RATE_COMP_FIFO_Idle_Counts
 *
 * Reports the number of Idles added and dropped from the data streams.
 */


/** 
 * \brief Tx FIFO Idle Add Count
 *
 * \details
 * Register: \a FIFO_BIST:RATE_COMP_FIFO_Idle_Counts:Tx_FIFO_Idle_Add_Count
 */
#define VTSS_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO_Idle_Add_Count  VTSS_IOREG(0x04, 0, 0xea10)

/** 
 * \brief
 * FIFO Tx idle group add count.  The counter saturates when the maximum
 * value is exceeded.  The counter is cleared when the register is read.
 *
 * \details 
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO_Idle_Add_Count . FIFO_Tx_idle_group_add_count
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO_Idle_Add_Count_FIFO_Tx_idle_group_add_count(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO_Idle_Add_Count_FIFO_Tx_idle_group_add_count     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO_Idle_Add_Count_FIFO_Tx_idle_group_add_count(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Tx FIFO Idle Drop Count
 *
 * \details
 * Register: \a FIFO_BIST:RATE_COMP_FIFO_Idle_Counts:Tx_FIFO_Idle_Drop_Count
 */
#define VTSS_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO_Idle_Drop_Count  VTSS_IOREG(0x04, 0, 0xea11)

/** 
 * \brief
 * FIFO Tx idle group drop count.  The counter saturates when the maximum
 * value is exceeded.  The counter is cleared when the register is read.
 *
 * \details 
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO_Idle_Drop_Count . FIFO_Tx_idle_group_drop_count
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO_Idle_Drop_Count_FIFO_Tx_idle_group_drop_count(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO_Idle_Drop_Count_FIFO_Tx_idle_group_drop_count     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO_Idle_Drop_Count_FIFO_Tx_idle_group_drop_count(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Rx FIFO Idle Add Count
 *
 * \details
 * Register: \a FIFO_BIST:RATE_COMP_FIFO_Idle_Counts:Rx_FIFO_Idle_Add_Count
 */
#define VTSS_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Rx_FIFO_Idle_Add_Count  VTSS_IOREG(0x04, 0, 0xea12)

/** 
 * \brief
 * FIFO Rx idle group add count.  The counter saturates when the maximum
 * value is exceeded.  The counter is cleared when the register is read.
 *
 * \details 
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Rx_FIFO_Idle_Add_Count . FIFO_Rx_idle_group_add_count
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Rx_FIFO_Idle_Add_Count_FIFO_Rx_idle_group_add_count(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Rx_FIFO_Idle_Add_Count_FIFO_Rx_idle_group_add_count     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Rx_FIFO_Idle_Add_Count_FIFO_Rx_idle_group_add_count(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Rx FIFO Idle Drop Count
 *
 * \details
 * Register: \a FIFO_BIST:RATE_COMP_FIFO_Idle_Counts:Rx_FIFO_Idle_Drop_Count
 */
#define VTSS_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Rx_FIFO_Idle_Drop_Count  VTSS_IOREG(0x04, 0, 0xea13)

/** 
 * \brief
 * FIFO Rx idle group drop count.  The counter saturates when the maximum
 * value is exceeded.  The counter is cleared when the register is read.
 *
 * \details 
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Rx_FIFO_Idle_Drop_Count . FIFO_Rx_idle_group_drop_count
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Rx_FIFO_Idle_Drop_Count_FIFO_Rx_idle_group_drop_count(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Rx_FIFO_Idle_Drop_Count_FIFO_Rx_idle_group_drop_count     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Rx_FIFO_Idle_Drop_Count_FIFO_Rx_idle_group_drop_count(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:Datapath_Control
 *
 * Not documented
 */


/** 
 * \brief Datapath_Control
 *
 * \details
 * Register: \a FIFO_BIST:Datapath_Control:Datapath_Control
 */
#define VTSS_FIFO_BIST_Datapath_Control_Datapath_Control  VTSS_IOREG(0x04, 0, 0xea20)

/** 
 * \brief
 * Selects source of data transmitted from PG_MUXA.  EGR_XGMII_PG_SEL and
 * IGR_XGMII_PG_SEL may not be set to 1 simultaneously.
 *
 * \details 
 * 0: Data from client-side PCS1G (1G mode) / XGXS (10G mode)
 * 1: Data from Pattern Generator
 *
 * Field: VTSS_FIFO_BIST_Datapath_Control_Datapath_Control . EGR_XGMII_PG_SEL
 */
#define  VTSS_F_FIFO_BIST_Datapath_Control_Datapath_Control_EGR_XGMII_PG_SEL  VTSS_BIT(8)

/** 
 * \brief
 * Selects source of data transmitted from PG_MUXB.  EGR_XGMII_PG_SEL and
 * IGR_XGMII_PG_SEL may not be set to 1 simultaneously.
 *
 * \details 
 * 0: Data from PG_MUXC in the ingress data path
 * 1: Data from Pattern Generator
 *
 * Field: VTSS_FIFO_BIST_Datapath_Control_Datapath_Control . IGR_XGMII_PG_SEL
 */
#define  VTSS_F_FIFO_BIST_Datapath_Control_Datapath_Control_IGR_XGMII_PG_SEL  VTSS_BIT(7)

/** 
 * \brief
 * Line-side/Network Loopback L2 Enable.
 *
 * \details 
 * Loopback L2 is:
 * 0: Disabled
 * 1: Enabled
 *
 * Field: VTSS_FIFO_BIST_Datapath_Control_Datapath_Control . LOOP_L2_ENA
 */
#define  VTSS_F_FIFO_BIST_Datapath_Control_Datapath_Control_LOOP_L2_ENA  VTSS_BIT(0)

/**
 * Register Group: \a FIFO_BIST:Datapath_Control2
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a FIFO_BIST:Datapath_Control2:Datapath_Control2
 */
#define VTSS_FIFO_BIST_Datapath_Control2_Datapath_Control2  VTSS_IOREG(0x04, 0, 0xea21)

/** 
 * \brief
 * Selects source of data transmitted from PG_MUXC.  This mux is intended
 * to be used to route data to the packet BIST monitor.  This mux may not
 * be used as a host-side loopback (i.e.  XAUI/RXAUI data input looped back
 * to XAUI/RXAUI data output).
 *
 * \details 
 * 0: Data from ingress data path
 * 1: Data from PG_MUXA in the egress data path
 *
 * Field: VTSS_FIFO_BIST_Datapath_Control2_Datapath_Control2 . IGR_XGMII_PG_SEL2
 */
#define  VTSS_F_FIFO_BIST_Datapath_Control2_Datapath_Control2_IGR_XGMII_PG_SEL2  VTSS_BIT(0)


#endif /* _VTSS_VENICE_REGS_FIFO_BIST_H_ */
