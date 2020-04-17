// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU_REGS_FIFO_BIST_H_
#define _VTSS_MALIBU_REGS_FIFO_BIST_H_


#include "vtss_malibu_regs_common.h"

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
 * Field: VTSS_FIFO_BIST_GEN_CFG_GEN_CFG . lenofs
 */
#define  VTSS_F_FIFO_BIST_GEN_CFG_GEN_CFG_lenofs(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_FIFO_BIST_GEN_CFG_GEN_CFG_lenofs     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_FIFO_BIST_GEN_CFG_GEN_CFG_lenofs(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/** 
 * \brief
 * Number of standard frames between PTP frames
 *
 * \details 
 * Field: VTSS_FIFO_BIST_GEN_CFG_GEN_CFG . srate
 */
#define  VTSS_F_FIFO_BIST_GEN_CFG_GEN_CFG_srate(x)  VTSS_ENCODE_BITFIELD(x,4,8)
#define  VTSS_M_FIFO_BIST_GEN_CFG_GEN_CFG_srate     VTSS_ENCODE_BITMASK(4,8)
#define  VTSS_X_FIFO_BIST_GEN_CFG_GEN_CFG_srate(x)  VTSS_EXTRACT_BITFIELD(x,4,8)

/** 
 * \brief
 * Generate a single packet during pktgen_idles
 *
 * \details 
 * Field: VTSS_FIFO_BIST_GEN_CFG_GEN_CFG . single
 */
#define  VTSS_F_FIFO_BIST_GEN_CFG_GEN_CFG_single  VTSS_BIT(3)

/** 
 * \brief
 * Generate all Idles 
 *
 * \details 
 * 0: Generate frames
 * 1: Generate idles only
 *
 * Field: VTSS_FIFO_BIST_GEN_CFG_GEN_CFG . idles
 */
#define  VTSS_F_FIFO_BIST_GEN_CFG_GEN_CFG_idles  VTSS_BIT(2)

/** 
 * \brief
 * Generate PTP frames 
 *
 * \details 
 * 0: Generate standard frames
 * 1: Generate PTP frames
 *
 * Field: VTSS_FIFO_BIST_GEN_CFG_GEN_CFG . ptp_enable
 */
#define  VTSS_F_FIFO_BIST_GEN_CFG_GEN_CFG_ptp_enable  VTSS_BIT(1)

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
 * Field: VTSS_FIFO_BIST_GEN_CFG_GEN_CFG . enable
 */
#define  VTSS_F_FIFO_BIST_GEN_CFG_GEN_CFG_enable  VTSS_BIT(0)

/**
 * Register Group: \a FIFO_BIST:UPDATE
 *
 * Not documented
 */


/** 
 * \brief latch all counters and timestamps for readback
 *
 * \details
 * Register: \a FIFO_BIST:UPDATE:UPDATE
 */
#define VTSS_FIFO_BIST_UPDATE_UPDATE         VTSS_IOREG(0x04, 0, 0xe901)

/** 
 * \brief
 * Freeze most recent 10 timestamps for readback 
 *
 * \details 
 * 0 : timestamps are updating. Do not read.
 * 1 : timestamps are not updating. Ok to read.
 *
 * Field: VTSS_FIFO_BIST_UPDATE_UPDATE . ts_hold
 */
#define  VTSS_F_FIFO_BIST_UPDATE_UPDATE_ts_hold  VTSS_BIT(1)

/** 
 * \brief
 * Freeze all generator and monitor counters for readback
 *
 * \details 
 * Field: VTSS_FIFO_BIST_UPDATE_UPDATE . cntr_update
 */
#define  VTSS_F_FIFO_BIST_UPDATE_UPDATE_cntr_update  VTSS_BIT(0)

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
 * Packet length 
 *
 * \details 
 * 0: bytes = preamble + 64 + /T/
 * >0: bytes = 24 + pktlen*64 + (8-lenofs) 
 *
 * Field: VTSS_FIFO_BIST_GEN_PKTLEN_GEN_PKTLEN . pktlen
 */
#define  VTSS_F_FIFO_BIST_GEN_PKTLEN_GEN_PKTLEN_pktlen(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FIFO_BIST_GEN_PKTLEN_GEN_PKTLEN_pktlen     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FIFO_BIST_GEN_PKTLEN_GEN_PKTLEN_pktlen(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a FIFO_BIST:GEN_IPGLEN
 *
 * Not documented
 */


/** 
 * \brief Lower 16 bits of 32-bit IPG length
 *
 * \details
 * Register: \a FIFO_BIST:GEN_IPGLEN:GEN_IPGLEN_LSW
 */
#define VTSS_FIFO_BIST_GEN_IPGLEN_GEN_IPGLEN_LSW  VTSS_IOREG(0x04, 0, 0xe903)

/** 
 * \brief
 * IPG length: /I/ bytes = lenofs + ipglen*4
 *
 * \details 
 * Field: VTSS_FIFO_BIST_GEN_IPGLEN_GEN_IPGLEN_LSW . ipglen_lsw
 */
#define  VTSS_F_FIFO_BIST_GEN_IPGLEN_GEN_IPGLEN_LSW_ipglen_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_IPGLEN_GEN_IPGLEN_LSW_ipglen_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_IPGLEN_GEN_IPGLEN_LSW_ipglen_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Upper 16 bits of 32-bit IPG length
 *
 * \details
 * Register: \a FIFO_BIST:GEN_IPGLEN:GEN_IPGLEN_MSW
 */
#define VTSS_FIFO_BIST_GEN_IPGLEN_GEN_IPGLEN_MSW  VTSS_IOREG(0x04, 0, 0xe904)

/** 
 * \brief
 * IPG length: /I/ bytes = lenofs + ipglen*4
 *
 * \details 
 * Field: VTSS_FIFO_BIST_GEN_IPGLEN_GEN_IPGLEN_MSW . ipglen_msw
 */
#define  VTSS_F_FIFO_BIST_GEN_IPGLEN_GEN_IPGLEN_MSW_ipglen_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_IPGLEN_GEN_IPGLEN_MSW_ipglen_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_IPGLEN_GEN_IPGLEN_MSW_ipglen_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

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
#define VTSS_FIFO_BIST_GEN_TIME_GEN_TIME     VTSS_IOREG(0x04, 0, 0xe905)

/** 
 * \brief
 * PTP timestamp to generate: [15:8] is seconds, [7:0] is ns
 *
 * \details 
 * Field: VTSS_FIFO_BIST_GEN_TIME_GEN_TIME . ptptime
 */
#define  VTSS_F_FIFO_BIST_GEN_TIME_GEN_TIME_ptptime(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_TIME_GEN_TIME_ptptime     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_TIME_GEN_TIME_ptptime(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

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
#define VTSS_FIFO_BIST_GEN_ETYPE_GEN_ETYPE   VTSS_IOREG(0x04, 0, 0xe906)

/** 
 * \brief
 * Etype field for standard frames
 *
 * \details 
 * Field: VTSS_FIFO_BIST_GEN_ETYPE_GEN_ETYPE . etype
 */
#define  VTSS_F_FIFO_BIST_GEN_ETYPE_GEN_ETYPE_etype(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_ETYPE_GEN_ETYPE_etype     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_ETYPE_GEN_ETYPE_etype(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

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
 * Field: VTSS_FIFO_BIST_GEN_SA_GEN_SA0 . sa0
 */
#define  VTSS_F_FIFO_BIST_GEN_SA_GEN_SA0_sa0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_SA_GEN_SA0_sa0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_SA_GEN_SA0_sa0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


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
 * Field: VTSS_FIFO_BIST_GEN_SA_GEN_SA1 . sa1
 */
#define  VTSS_F_FIFO_BIST_GEN_SA_GEN_SA1_sa1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_SA_GEN_SA1_sa1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_SA_GEN_SA1_sa1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


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
 * Field: VTSS_FIFO_BIST_GEN_SA_GEN_SA2 . sa2
 */
#define  VTSS_F_FIFO_BIST_GEN_SA_GEN_SA2_sa2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_SA_GEN_SA2_sa2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_SA_GEN_SA2_sa2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

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
 * Field: VTSS_FIFO_BIST_GEN_DA_GEN_DA0 . da0
 */
#define  VTSS_F_FIFO_BIST_GEN_DA_GEN_DA0_da0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_DA_GEN_DA0_da0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_DA_GEN_DA0_da0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


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
 * Field: VTSS_FIFO_BIST_GEN_DA_GEN_DA1 . da1
 */
#define  VTSS_F_FIFO_BIST_GEN_DA_GEN_DA1_da1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_DA_GEN_DA1_da1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_DA_GEN_DA1_da1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


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
 * Field: VTSS_FIFO_BIST_GEN_DA_GEN_DA2 . da2
 */
#define  VTSS_F_FIFO_BIST_GEN_DA_GEN_DA2_da2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_DA_GEN_DA2_da2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_DA_GEN_DA2_da2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

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
 * Field: VTSS_FIFO_BIST_GEN_SENT_GEN_SENT_LSW . sent_lsw
 */
#define  VTSS_F_FIFO_BIST_GEN_SENT_GEN_SENT_LSW_sent_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_SENT_GEN_SENT_LSW_sent_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_SENT_GEN_SENT_LSW_sent_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


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
 * Field: VTSS_FIFO_BIST_GEN_SENT_GEN_SENT_MSW . sent_msw
 */
#define  VTSS_F_FIFO_BIST_GEN_SENT_GEN_SENT_MSW_sent_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_GEN_SENT_GEN_SENT_MSW_sent_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_GEN_SENT_GEN_SENT_MSW_sent_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

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
 * Field: VTSS_FIFO_BIST_MON_CFG_MON_CFG . enable
 */
#define  VTSS_F_FIFO_BIST_MON_CFG_MON_CFG_enable  VTSS_BIT(0)

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
 * Field: VTSS_FIFO_BIST_MON_RST_MON_RST . ber_rst
 */
#define  VTSS_F_FIFO_BIST_MON_RST_MON_RST_ber_rst  VTSS_BIT(5)

/** 
 * \brief
 * reset Local_Fault counter
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_RST_MON_RST . lfault_rst
 */
#define  VTSS_F_FIFO_BIST_MON_RST_MON_RST_lfault_rst  VTSS_BIT(4)

/** 
 * \brief
 * reset Packet_Fragment counter
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_RST_MON_RST . frag_rst
 */
#define  VTSS_F_FIFO_BIST_MON_RST_MON_RST_frag_rst  VTSS_BIT(3)

/** 
 * \brief
 * reset Bad_CRC counter
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_RST_MON_RST . bad_rst
 */
#define  VTSS_F_FIFO_BIST_MON_RST_MON_RST_bad_rst  VTSS_BIT(2)

/** 
 * \brief
 * reset Good_CRC counter
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_RST_MON_RST . good_rst
 */
#define  VTSS_F_FIFO_BIST_MON_RST_MON_RST_good_rst  VTSS_BIT(1)

/** 
 * \brief
 * reset all counters
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_RST_MON_RST . all_rst
 */
#define  VTSS_F_FIFO_BIST_MON_RST_MON_RST_all_rst  VTSS_BIT(0)

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
 * Field: VTSS_FIFO_BIST_MON_GOODCRC_MON_GOOD_LSW . good_lsw
 */
#define  VTSS_F_FIFO_BIST_MON_GOODCRC_MON_GOOD_LSW_good_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_GOODCRC_MON_GOOD_LSW_good_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_GOODCRC_MON_GOOD_LSW_good_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


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
 * Field: VTSS_FIFO_BIST_MON_GOODCRC_MON_GOOD_MSW . good_msw
 */
#define  VTSS_F_FIFO_BIST_MON_GOODCRC_MON_GOOD_MSW_good_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_GOODCRC_MON_GOOD_MSW_good_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_GOODCRC_MON_GOOD_MSW_good_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

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
 * Field: VTSS_FIFO_BIST_MON_BADCRC_MON_BAD_LSW . bad_lsw
 */
#define  VTSS_F_FIFO_BIST_MON_BADCRC_MON_BAD_LSW_bad_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_BADCRC_MON_BAD_LSW_bad_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_BADCRC_MON_BAD_LSW_bad_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


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
 * Field: VTSS_FIFO_BIST_MON_BADCRC_MON_BAD_MSW . bad_msw
 */
#define  VTSS_F_FIFO_BIST_MON_BADCRC_MON_BAD_MSW_bad_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_BADCRC_MON_BAD_MSW_bad_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_BADCRC_MON_BAD_MSW_bad_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

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
 * Field: VTSS_FIFO_BIST_MON_FRAG_MON_FRAG_LSW . frag_lsw
 */
#define  VTSS_F_FIFO_BIST_MON_FRAG_MON_FRAG_LSW_frag_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_FRAG_MON_FRAG_LSW_frag_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_FRAG_MON_FRAG_LSW_frag_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


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
 * Field: VTSS_FIFO_BIST_MON_FRAG_MON_FRAG_MSW . frag_msw
 */
#define  VTSS_F_FIFO_BIST_MON_FRAG_MON_FRAG_MSW_frag_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_FRAG_MON_FRAG_MSW_frag_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_FRAG_MON_FRAG_MSW_frag_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

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
 * Field: VTSS_FIFO_BIST_MON_LFAULT_MON_LFAULT_LSW . lfault_lsw
 */
#define  VTSS_F_FIFO_BIST_MON_LFAULT_MON_LFAULT_LSW_lfault_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_LFAULT_MON_LFAULT_LSW_lfault_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_LFAULT_MON_LFAULT_LSW_lfault_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


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
 * Field: VTSS_FIFO_BIST_MON_LFAULT_MON_LFAULT_MSW . lfault_msw
 */
#define  VTSS_F_FIFO_BIST_MON_LFAULT_MON_LFAULT_MSW_lfault_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_LFAULT_MON_LFAULT_MSW_lfault_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_LFAULT_MON_LFAULT_MSW_lfault_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

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
 * Field: VTSS_FIFO_BIST_MON_BER_MON_BER_LSW . ber_lsw
 */
#define  VTSS_F_FIFO_BIST_MON_BER_MON_BER_LSW_ber_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_BER_MON_BER_LSW_ber_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_BER_MON_BER_LSW_ber_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


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
 * Field: VTSS_FIFO_BIST_MON_BER_MON_BER_MSW . ber_msw
 */
#define  VTSS_F_FIFO_BIST_MON_BER_MON_BER_MSW_ber_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_BER_MON_BER_MSW_ber_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_BER_MON_BER_MSW_ber_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:MON_TSTAMP0
 *
 * Not documented
 */


/** 
 * \brief PTP timestamp0 (oldest) bits 15-0
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP0:MON_TSTAMP0_0
 */
#define VTSS_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_0  VTSS_IOREG(0x04, 0, 0xe9b0)

/** 
 * \brief
 * PTP timestamp 0, bits [15:0]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_0 . tstamp0_0
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_0_tstamp0_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_0_tstamp0_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_0_tstamp0_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp0 (oldest) bits 31-16
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP0:MON_TSTAMP0_1
 */
#define VTSS_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_1  VTSS_IOREG(0x04, 0, 0xe9b1)

/** 
 * \brief
 * PTP timestamp 0, bits [31:16]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_1 . tstamp0_1
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_1_tstamp0_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_1_tstamp0_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_1_tstamp0_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp0 (oldest) bits 47-32
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP0:MON_TSTAMP0_2
 */
#define VTSS_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_2  VTSS_IOREG(0x04, 0, 0xe9b2)

/** 
 * \brief
 * PTP timestamp 0, bits [47:32]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_2 . tstamp0_2
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_2_tstamp0_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_2_tstamp0_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_2_tstamp0_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp0 (oldest) bits 63-48
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP0:MON_TSTAMP0_3
 */
#define VTSS_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_3  VTSS_IOREG(0x04, 0, 0xe9b3)

/** 
 * \brief
 * PTP timestamp 0, bits [63:48]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_3 . tstamp0_3
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_3_tstamp0_3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_3_tstamp0_3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_3_tstamp0_3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp0 (oldest) bits 79-64
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP0:MON_TSTAMP0_4
 */
#define VTSS_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_4  VTSS_IOREG(0x04, 0, 0xe9b4)

/** 
 * \brief
 * PTP timestamp 0, bits [79:64]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_4 . tstamp0_4
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_4_tstamp0_4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_4_tstamp0_4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP0_MON_TSTAMP0_4_tstamp0_4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:MON_TSTAMP1
 *
 * Not documented
 */


/** 
 * \brief PTP timestamp1 bits 15-0
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP1:MON_TSTAMP1_0
 */
#define VTSS_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_0  VTSS_IOREG(0x04, 0, 0xe9c0)

/** 
 * \brief
 * PTP timestamp 1, bits [15:0]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_0 . tstamp1_0
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_0_tstamp1_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_0_tstamp1_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_0_tstamp1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp1 bits 31-16
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP1:MON_TSTAMP1_1
 */
#define VTSS_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_1  VTSS_IOREG(0x04, 0, 0xe9c1)

/** 
 * \brief
 * PTP timestamp 1, bits [31:16]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_1 . tstamp1_1
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_1_tstamp1_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_1_tstamp1_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_1_tstamp1_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp1 bits 47-32
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP1:MON_TSTAMP1_2
 */
#define VTSS_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_2  VTSS_IOREG(0x04, 0, 0xe9c2)

/** 
 * \brief
 * PTP timestamp 1, bits [47:32]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_2 . tstamp1_2
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_2_tstamp1_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_2_tstamp1_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_2_tstamp1_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp1 bits 63-48
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP1:MON_TSTAMP1_3
 */
#define VTSS_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_3  VTSS_IOREG(0x04, 0, 0xe9c3)

/** 
 * \brief
 * PTP timestamp 1, bits [63:48]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_3 . tstamp1_3
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_3_tstamp1_3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_3_tstamp1_3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_3_tstamp1_3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp1 bits 79-64
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP1:MON_TSTAMP1_4
 */
#define VTSS_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_4  VTSS_IOREG(0x04, 0, 0xe9c4)

/** 
 * \brief
 * PTP timestamp 1, bits [79:64]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_4 . tstamp1_4
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_4_tstamp1_4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_4_tstamp1_4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP1_MON_TSTAMP1_4_tstamp1_4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:MON_TSTAMP2
 *
 * Not documented
 */


/** 
 * \brief PTP timestamp2 bits 15-0
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP2:MON_TSTAMP2_0
 */
#define VTSS_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_0  VTSS_IOREG(0x04, 0, 0xe9d0)

/** 
 * \brief
 * PTP timestamp 2, bits [15:0]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_0 . tstamp2_0
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_0_tstamp2_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_0_tstamp2_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_0_tstamp2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp2 bits 31-16
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP2:MON_TSTAMP2_1
 */
#define VTSS_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_1  VTSS_IOREG(0x04, 0, 0xe9d1)

/** 
 * \brief
 * PTP timestamp 2, bits [31:16]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_1 . tstamp2_1
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_1_tstamp2_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_1_tstamp2_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_1_tstamp2_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp2 bits 47-32
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP2:MON_TSTAMP2_2
 */
#define VTSS_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_2  VTSS_IOREG(0x04, 0, 0xe9d2)

/** 
 * \brief
 * PTP timestamp 2, bits [47:32]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_2 . tstamp2_2
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_2_tstamp2_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_2_tstamp2_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_2_tstamp2_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp2 bits 63-48
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP2:MON_TSTAMP2_3
 */
#define VTSS_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_3  VTSS_IOREG(0x04, 0, 0xe9d3)

/** 
 * \brief
 * PTP timestamp 2, bits [63:48]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_3 . tstamp2_3
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_3_tstamp2_3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_3_tstamp2_3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_3_tstamp2_3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp2 bits 79-64
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP2:MON_TSTAMP2_4
 */
#define VTSS_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_4  VTSS_IOREG(0x04, 0, 0xe9d4)

/** 
 * \brief
 * PTP timestamp 2, bits [79:64]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_4 . tstamp2_4
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_4_tstamp2_4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_4_tstamp2_4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP2_MON_TSTAMP2_4_tstamp2_4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:MON_TSTAMP3
 *
 * Not documented
 */


/** 
 * \brief PTP timestamp3 bits 15-0
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP3:MON_TSTAMP3_0
 */
#define VTSS_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_0  VTSS_IOREG(0x04, 0, 0xe9e0)

/** 
 * \brief
 * PTP timestamp 3, bits [15:0]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_0 . tstamp3_0
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_0_tstamp3_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_0_tstamp3_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_0_tstamp3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp3 bits 31-16
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP3:MON_TSTAMP3_1
 */
#define VTSS_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_1  VTSS_IOREG(0x04, 0, 0xe9e1)

/** 
 * \brief
 * PTP timestamp 3, bits [31:16]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_1 . tstamp3_1
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_1_tstamp3_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_1_tstamp3_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_1_tstamp3_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp3 bits 47-32
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP3:MON_TSTAMP3_2
 */
#define VTSS_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_2  VTSS_IOREG(0x04, 0, 0xe9e2)

/** 
 * \brief
 * PTP timestamp 3, bits [47:32]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_2 . tstamp3_2
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_2_tstamp3_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_2_tstamp3_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_2_tstamp3_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp3 bits 63-48
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP3:MON_TSTAMP3_3
 */
#define VTSS_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_3  VTSS_IOREG(0x04, 0, 0xe9e3)

/** 
 * \brief
 * PTP timestamp 3, bits [63:48]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_3 . tstamp3_3
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_3_tstamp3_3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_3_tstamp3_3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_3_tstamp3_3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp3 bits 79-64
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP3:MON_TSTAMP3_4
 */
#define VTSS_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_4  VTSS_IOREG(0x04, 0, 0xe9e4)

/** 
 * \brief
 * PTP timestamp 3, bits [79:64]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_4 . tstamp3_4
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_4_tstamp3_4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_4_tstamp3_4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP3_MON_TSTAMP3_4_tstamp3_4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:MON_TSTAMP4
 *
 * Not documented
 */


/** 
 * \brief PTP timestamp4 bits 15-0
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP4:MON_TSTAMP4_0
 */
#define VTSS_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_0  VTSS_IOREG(0x04, 0, 0xe9f0)

/** 
 * \brief
 * PTP timestamp 4, bits [15:0]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_0 . tstamp4_0
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_0_tstamp4_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_0_tstamp4_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_0_tstamp4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp4 bits 31-16
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP4:MON_TSTAMP4_1
 */
#define VTSS_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_1  VTSS_IOREG(0x04, 0, 0xe9f1)

/** 
 * \brief
 * PTP timestamp 4, bits [31:16]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_1 . tstamp4_1
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_1_tstamp4_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_1_tstamp4_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_1_tstamp4_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp4 bits 47-32
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP4:MON_TSTAMP4_2
 */
#define VTSS_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_2  VTSS_IOREG(0x04, 0, 0xe9f2)

/** 
 * \brief
 * PTP timestamp 4, bits [47:32]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_2 . tstamp4_2
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_2_tstamp4_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_2_tstamp4_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_2_tstamp4_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp4 bits 63-48
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP4:MON_TSTAMP4_3
 */
#define VTSS_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_3  VTSS_IOREG(0x04, 0, 0xe9f3)

/** 
 * \brief
 * PTP timestamp 4, bits [63:48]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_3 . tstamp4_3
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_3_tstamp4_3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_3_tstamp4_3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_3_tstamp4_3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp4 bits 79-64
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP4:MON_TSTAMP4_4
 */
#define VTSS_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_4  VTSS_IOREG(0x04, 0, 0xe9f4)

/** 
 * \brief
 * PTP timestamp 4, bits [79:64]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_4 . tstamp4_4
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_4_tstamp4_4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_4_tstamp4_4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP4_MON_TSTAMP4_4_tstamp4_4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:MON_TSTAMP5
 *
 * Not documented
 */


/** 
 * \brief PTP timestamp5 bits 15-0
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP5:MON_TSTAMP5_0
 */
#define VTSS_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_0  VTSS_IOREG(0x04, 0, 0xea00)

/** 
 * \brief
 * PTP timestamp 5, bits [15:0]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_0 . tstamp5_0
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_0_tstamp5_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_0_tstamp5_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_0_tstamp5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp5 bits 31-16
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP5:MON_TSTAMP5_1
 */
#define VTSS_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_1  VTSS_IOREG(0x04, 0, 0xea01)

/** 
 * \brief
 * PTP timestamp 5, bits [31:16]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_1 . tstamp5_1
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_1_tstamp5_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_1_tstamp5_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_1_tstamp5_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp5 bits 47-32
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP5:MON_TSTAMP5_2
 */
#define VTSS_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_2  VTSS_IOREG(0x04, 0, 0xea02)

/** 
 * \brief
 * PTP timestamp 5, bits [47:32]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_2 . tstamp5_2
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_2_tstamp5_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_2_tstamp5_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_2_tstamp5_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp5 bits 63-48
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP5:MON_TSTAMP5_3
 */
#define VTSS_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_3  VTSS_IOREG(0x04, 0, 0xea03)

/** 
 * \brief
 * PTP timestamp 5, bits [63:48]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_3 . tstamp5_3
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_3_tstamp5_3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_3_tstamp5_3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_3_tstamp5_3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp5 bits 79-64
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP5:MON_TSTAMP5_4
 */
#define VTSS_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_4  VTSS_IOREG(0x04, 0, 0xea04)

/** 
 * \brief
 * PTP timestamp 5, bits [79:64]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_4 . tstamp5_4
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_4_tstamp5_4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_4_tstamp5_4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP5_MON_TSTAMP5_4_tstamp5_4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:MON_TSTAMP6
 *
 * Not documented
 */


/** 
 * \brief PTP timestamp6 bits 15-0
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP6:MON_TSTAMP6_0
 */
#define VTSS_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_0  VTSS_IOREG(0x04, 0, 0xea10)

/** 
 * \brief
 * PTP timestamp 6, bits [15:0]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_0 . tstamp6_0
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_0_tstamp6_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_0_tstamp6_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_0_tstamp6_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp6 bits 31-16
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP6:MON_TSTAMP6_1
 */
#define VTSS_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_1  VTSS_IOREG(0x04, 0, 0xea11)

/** 
 * \brief
 * PTP timestamp 6, bits [31:16]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_1 . tstamp6_1
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_1_tstamp6_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_1_tstamp6_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_1_tstamp6_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp6 bits 47-32
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP6:MON_TSTAMP6_2
 */
#define VTSS_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_2  VTSS_IOREG(0x04, 0, 0xea12)

/** 
 * \brief
 * PTP timestamp 6, bits [47:32]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_2 . tstamp6_2
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_2_tstamp6_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_2_tstamp6_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_2_tstamp6_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp6 bits 63-48
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP6:MON_TSTAMP6_3
 */
#define VTSS_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_3  VTSS_IOREG(0x04, 0, 0xea13)

/** 
 * \brief
 * PTP timestamp 6, bits [63:48]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_3 . tstamp6_3
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_3_tstamp6_3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_3_tstamp6_3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_3_tstamp6_3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp6 bits 79-64
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP6:MON_TSTAMP6_4
 */
#define VTSS_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_4  VTSS_IOREG(0x04, 0, 0xea14)

/** 
 * \brief
 * PTP timestamp 6, bits [79:64]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_4 . tstamp6_4
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_4_tstamp6_4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_4_tstamp6_4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP6_MON_TSTAMP6_4_tstamp6_4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:MON_TSTAMP7
 *
 * Not documented
 */


/** 
 * \brief PTP timestamp7 bits 15-0
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP7:MON_TSTAMP7_0
 */
#define VTSS_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_0  VTSS_IOREG(0x04, 0, 0xea20)

/** 
 * \brief
 * PTP timestamp 7, bits [15:0]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_0 . tstamp7_0
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_0_tstamp7_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_0_tstamp7_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_0_tstamp7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp7 bits 31-16
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP7:MON_TSTAMP7_1
 */
#define VTSS_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_1  VTSS_IOREG(0x04, 0, 0xea21)

/** 
 * \brief
 * PTP timestamp 7, bits [31:16]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_1 . tstamp7_1
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_1_tstamp7_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_1_tstamp7_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_1_tstamp7_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp7 bits 47-32
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP7:MON_TSTAMP7_2
 */
#define VTSS_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_2  VTSS_IOREG(0x04, 0, 0xea22)

/** 
 * \brief
 * PTP timestamp 7, bits [47:32]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_2 . tstamp7_2
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_2_tstamp7_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_2_tstamp7_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_2_tstamp7_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp7 bits 63-48
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP7:MON_TSTAMP7_3
 */
#define VTSS_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_3  VTSS_IOREG(0x04, 0, 0xea23)

/** 
 * \brief
 * PTP timestamp 7, bits [63:48]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_3 . tstamp7_3
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_3_tstamp7_3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_3_tstamp7_3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_3_tstamp7_3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp7 bits 79-64
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP7:MON_TSTAMP7_4
 */
#define VTSS_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_4  VTSS_IOREG(0x04, 0, 0xea24)

/** 
 * \brief
 * PTP timestamp 7, bits [79:64]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_4 . tstamp7_4
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_4_tstamp7_4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_4_tstamp7_4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP7_MON_TSTAMP7_4_tstamp7_4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:MON_TSTAMP8
 *
 * Not documented
 */


/** 
 * \brief PTP timestamp8 bits 15-0
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP8:MON_TSTAMP8_0
 */
#define VTSS_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_0  VTSS_IOREG(0x04, 0, 0xea30)

/** 
 * \brief
 * PTP timestamp 8, bits [15:0]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_0 . tstamp8_0
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_0_tstamp8_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_0_tstamp8_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_0_tstamp8_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp8 bits 31-16
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP8:MON_TSTAMP8_1
 */
#define VTSS_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_1  VTSS_IOREG(0x04, 0, 0xea31)

/** 
 * \brief
 * PTP timestamp 8, bits [31:16]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_1 . tstamp8_1
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_1_tstamp8_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_1_tstamp8_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_1_tstamp8_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp8 bits 47-32
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP8:MON_TSTAMP8_2
 */
#define VTSS_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_2  VTSS_IOREG(0x04, 0, 0xea32)

/** 
 * \brief
 * PTP timestamp 8, bits [47:32]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_2 . tstamp8_2
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_2_tstamp8_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_2_tstamp8_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_2_tstamp8_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp8 bits 63-48
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP8:MON_TSTAMP8_3
 */
#define VTSS_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_3  VTSS_IOREG(0x04, 0, 0xea33)

/** 
 * \brief
 * PTP timestamp 8, bits [63:48]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_3 . tstamp8_3
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_3_tstamp8_3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_3_tstamp8_3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_3_tstamp8_3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp8 bits 79-64
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP8:MON_TSTAMP8_4
 */
#define VTSS_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_4  VTSS_IOREG(0x04, 0, 0xea34)

/** 
 * \brief
 * PTP timestamp 8, bits [79:64]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_4 . tstamp8_4
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_4_tstamp8_4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_4_tstamp8_4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP8_MON_TSTAMP8_4_tstamp8_4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:MON_TSTAMP9
 *
 * Not documented
 */


/** 
 * \brief PTP timestamp9 (most recent) bits 15-0
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP9:MON_TSTAMP9_0
 */
#define VTSS_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_0  VTSS_IOREG(0x04, 0, 0xea40)

/** 
 * \brief
 * PTP timestamp 9, bits [15:0]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_0 . tstamp9_0
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_0_tstamp9_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_0_tstamp9_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_0_tstamp9_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp9 (most recent) bits 31-16
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP9:MON_TSTAMP9_1
 */
#define VTSS_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_1  VTSS_IOREG(0x04, 0, 0xea41)

/** 
 * \brief
 * PTP timestamp 9, bits [31:16]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_1 . tstamp9_1
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_1_tstamp9_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_1_tstamp9_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_1_tstamp9_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp9 (most recent) bits 47-32
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP9:MON_TSTAMP9_2
 */
#define VTSS_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_2  VTSS_IOREG(0x04, 0, 0xea42)

/** 
 * \brief
 * PTP timestamp 9, bits [47:32]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_2 . tstamp9_2
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_2_tstamp9_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_2_tstamp9_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_2_tstamp9_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp9 (most recent) bits 63-48
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP9:MON_TSTAMP9_3
 */
#define VTSS_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_3  VTSS_IOREG(0x04, 0, 0xea43)

/** 
 * \brief
 * PTP timestamp 9, bits [63:48]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_3 . tstamp9_3
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_3_tstamp9_3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_3_tstamp9_3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_3_tstamp9_3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PTP timestamp9 (most recent) bits 79-64
 *
 * \details
 * Register: \a FIFO_BIST:MON_TSTAMP9:MON_TSTAMP9_4
 */
#define VTSS_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_4  VTSS_IOREG(0x04, 0, 0xea44)

/** 
 * \brief
 * PTP timestamp 9, bits [79:64]
 *
 * \details 
 * Field: VTSS_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_4 . tstamp9_4
 */
#define  VTSS_F_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_4_tstamp9_4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_4_tstamp9_4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_MON_TSTAMP9_MON_TSTAMP9_4_tstamp9_4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FIFO_BIST:RATE_COMP_FIFO_STAT
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a FIFO_BIST:RATE_COMP_FIFO_STAT:RATE_COMP_FIFO_MASK
 */
#define VTSS_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_MASK  VTSS_IOREG(0x04, 0, 0xea50)

/** 
 * \brief
 * Interrupt enable for Tx_FIFO2_overflow
 *
 * \details 
 * 0 = Tx_FIFO2_overflow will not propogate to interrupt
 * 1 = Tx_FIFO2_overflow will propogate to interrupt
 *
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_MASK . TX_FIFO2_OVERFLOW_INTR_EN
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_MASK_TX_FIFO2_OVERFLOW_INTR_EN  VTSS_BIT(5)

/** 
 * \brief
 * Interrupt enable for Tx_FIFO2_underflow
 *
 * \details 
 * 0 = Tx_FIFO2_underflow will not propogate to interrupt
 * 1 = Tx_FIFO2_underflow will propogate to interrupt
 *
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_MASK . TX_FIFO2_UNDERFLOW_INTR_EN
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_MASK_TX_FIFO2_UNDERFLOW_INTR_EN  VTSS_BIT(4)

/** 
 * \brief
 * Interrupt enable for Rx_FIFO_overflow
 *
 * \details 
 * 0 = Rx_FIFO_overflow will not propogate to interrupt
 * 1 = Rx_FIFO_overflow will propogate to interrupt
 *
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_MASK . RX_FIFO_OVERFLOW_INTR_EN
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_MASK_RX_FIFO_OVERFLOW_INTR_EN  VTSS_BIT(3)

/** 
 * \brief
 * Interrupt enable for Rx_FIFO_underflow
 *
 * \details 
 * 0 = Rx_FIFO_underflow will not propogate to interrupt
 * 1 = Rx_FIFO_underflow will propogate to interrupt
 *
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_MASK . RX_FIFO_UNDERFLOW_INTR_EN
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_MASK_RX_FIFO_UNDERFLOW_INTR_EN  VTSS_BIT(2)

/** 
 * \brief
 * Interrupt enable for Tx_FIFO_overflow
 *
 * \details 
 * 0 = Tx_FIFO_overflow will not propogate to interrupt
 * 1 = Tx_FIFO_overflow will propogate to interrupt
 *
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_MASK . TX_FIFO_OVERFLOW_INTR_EN
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_MASK_TX_FIFO_OVERFLOW_INTR_EN  VTSS_BIT(1)

/** 
 * \brief
 * Interrupt enable for Tx_FIFO_underflow
 *
 * \details 
 * 0 = Tx_FIFO_underflow will not propogate to interrupt
 * 1 = Tx_FIFO_underflow will propogate to interrupt
 *
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_MASK . TX_FIFO_UNDERFLOW_INTR_EN
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_MASK_TX_FIFO_UNDERFLOW_INTR_EN  VTSS_BIT(0)


/** 
 * \brief  Rate Compensation FIFO Status
 *
 * \details
 * Register: \a FIFO_BIST:RATE_COMP_FIFO_STAT:RATE_COMP_FIFO_STAT
 */
#define VTSS_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT  VTSS_IOREG(0x04, 0, 0xea51)

/** 
 * \brief
 * Overflow status bit for the 10G host clock rate compensating FIFO in the
 * chip's egress data path.
 *
 * \details 
 * Status:
 * 0: No overflow
 * 1: Overflow
 *
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT . Tx_FIFO2_overflow
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT_Tx_FIFO2_overflow  VTSS_BIT(5)

/** 
 * \brief
 * Underflow status bit for the 10G host clock rate compensating FIFO in
 * the chip's egress data path.
 *
 * \details 
 * Status:
 * 0: No underflow
 * 1: Underflow
 *
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT . Tx_FIFO2_underflow
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT_Tx_FIFO2_underflow  VTSS_BIT(4)

/** 
 * \brief
 * Overflow status bit for the rate compensating FIFO in the chip's ingress
 * data path.  The ingress FIFO is enabled when the MACs are disabled.
 *
 * \details 
 * Status:
 * 0: No overflow
 * 1: Overflow
 *
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT . Rx_FIFO_overflow
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT_Rx_FIFO_overflow  VTSS_BIT(3)

/** 
 * \brief
 * Underflow status bit for the rate compensating FIFO in the chip's
 * ingress data path.  The ingress FIFO is enabled when the MACs are
 * disabled.
 *
 * \details 
 * Status:
 * 0: No underflow
 * 1: Underflow
 *
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT . Rx_FIFO_underflow
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT_Rx_FIFO_underflow  VTSS_BIT(2)

/** 
 * \brief
 * Overflow status bit for the second rate compensating FIFO in the chip's
 * egress data path.  The egress FIFO is enabled when the MACs are
 * disabled.
 *
 * \details 
 * Status:
 * 0: No overflow
 * 1: Overflow
 *
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT . Tx_FIFO_overflow
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT_Tx_FIFO_overflow  VTSS_BIT(1)

/** 
 * \brief
 * Underflow status bit for the second rate compensating FIFO in the chip's
 * egress data path.  The egress FIFO is enabled when the MACs are
 * disabled.
 *
 * \details 
 * Status:
 * 0: No underflow
 * 1: Underflow
 *
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT . Tx_FIFO_underflow
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_STAT_RATE_COMP_FIFO_STAT_Tx_FIFO_underflow  VTSS_BIT(0)

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
#define VTSS_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO_Idle_Add_Count  VTSS_IOREG(0x04, 0, 0xea60)

/** 
 * \brief
 * Idle group count added in Tx FIFO1 for line/host clock rate compensating
 * in the chip's egress data path.  The counter saturates when the maximum
 * value is exceeded.  The counter is cleared when the register is read.
 *
 * \details 
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO_Idle_Add_Count . Tx_FIFO_idle_group_add_count
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO_Idle_Add_Count_Tx_FIFO_idle_group_add_count(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO_Idle_Add_Count_Tx_FIFO_idle_group_add_count     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO_Idle_Add_Count_Tx_FIFO_idle_group_add_count(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Tx FIFO Idle Drop Count
 *
 * \details
 * Register: \a FIFO_BIST:RATE_COMP_FIFO_Idle_Counts:Tx_FIFO_Idle_Drop_Count
 */
#define VTSS_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO_Idle_Drop_Count  VTSS_IOREG(0x04, 0, 0xea61)

/** 
 * \brief
 * Idle group count dropped in Tx FIFO1 for line/host clock rate
 * compensating in the chip's egress data path.  The counter saturates when
 * the maximum value is exceeded.  The counter is cleared when the register
 * is read.
 *
 * \details 
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO_Idle_Drop_Count . Tx_FIFO_idle_group_drop_count
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO_Idle_Drop_Count_Tx_FIFO_idle_group_drop_count(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO_Idle_Drop_Count_Tx_FIFO_idle_group_drop_count     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO_Idle_Drop_Count_Tx_FIFO_idle_group_drop_count(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Rx FIFO Idle Add Count
 *
 * \details
 * Register: \a FIFO_BIST:RATE_COMP_FIFO_Idle_Counts:Rx_FIFO_Idle_Add_Count
 */
#define VTSS_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Rx_FIFO_Idle_Add_Count  VTSS_IOREG(0x04, 0, 0xea62)

/** 
 * \brief
 * Idle group count added in the Rx FIFO for line/host clock rate
 * compensating in the chip's ingress data path.  The counter saturates
 * when the maximum value is exceeded.	The counter is cleared when the
 * register is read.
 *
 * \details 
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Rx_FIFO_Idle_Add_Count . Rx_FIFO_idle_group_add_count
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Rx_FIFO_Idle_Add_Count_Rx_FIFO_idle_group_add_count(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Rx_FIFO_Idle_Add_Count_Rx_FIFO_idle_group_add_count     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Rx_FIFO_Idle_Add_Count_Rx_FIFO_idle_group_add_count(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Rx FIFO Idle Drop Count
 *
 * \details
 * Register: \a FIFO_BIST:RATE_COMP_FIFO_Idle_Counts:Rx_FIFO_Idle_Drop_Count
 */
#define VTSS_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Rx_FIFO_Idle_Drop_Count  VTSS_IOREG(0x04, 0, 0xea63)

/** 
 * \brief
 * Idle group count dropped in the Rx FIFO for line/host clock rate
 * compensating in the chip's ingress data path.  The counter saturates
 * when the maximum value is exceeded.	The counter is cleared when the
 * register is read.
 *
 * \details 
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Rx_FIFO_Idle_Drop_Count . Rx_FIFO_idle_group_drop_count
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Rx_FIFO_Idle_Drop_Count_Rx_FIFO_idle_group_drop_count(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Rx_FIFO_Idle_Drop_Count_Rx_FIFO_idle_group_drop_count     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Rx_FIFO_Idle_Drop_Count_Rx_FIFO_idle_group_drop_count(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Tx FIFO2 Idle Add Count
 *
 * \details
 * Register: \a FIFO_BIST:RATE_COMP_FIFO_Idle_Counts:Tx_FIFO2_Idle_Add_Count
 */
#define VTSS_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO2_Idle_Add_Count  VTSS_IOREG(0x04, 0, 0xea64)

/** 
 * \brief
 * Idle group count added in Tx FIFO2 for 10G host clock rate compensating
 * in the chip's egress data path.  The counter saturates when the maximum
 * value is exceeded.  The counter is cleared when the register is read.
 *
 * \details 
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO2_Idle_Add_Count . Tx_FIFO2_idle_group_add_count
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO2_Idle_Add_Count_Tx_FIFO2_idle_group_add_count(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO2_Idle_Add_Count_Tx_FIFO2_idle_group_add_count     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO2_Idle_Add_Count_Tx_FIFO2_idle_group_add_count(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Tx FIFO2 Idle Drop Count
 *
 * \details
 * Register: \a FIFO_BIST:RATE_COMP_FIFO_Idle_Counts:Tx_FIFO2_Idle_Drop_Count
 */
#define VTSS_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO2_Idle_Drop_Count  VTSS_IOREG(0x04, 0, 0xea65)

/** 
 * \brief
 * Idle group count dropped in Tx FIFO2 for 10G host clock rate
 * compensating in the chip's egress data path.  The counter saturates when
 * the maximum value is exceeded.  The counter is cleared when the register
 * is read.
 *
 * \details 
 * Field: VTSS_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO2_Idle_Drop_Count . Tx_FIFO2_idle_group_drop_count
 */
#define  VTSS_F_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO2_Idle_Drop_Count_Tx_FIFO2_idle_group_drop_count(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO2_Idle_Drop_Count_Tx_FIFO2_idle_group_drop_count     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FIFO_BIST_RATE_COMP_FIFO_Idle_Counts_Tx_FIFO2_Idle_Drop_Count_Tx_FIFO2_idle_group_drop_count(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

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
#define VTSS_FIFO_BIST_Datapath_Control_Datapath_Control  VTSS_IOREG(0x04, 0, 0xea70)

/** 
 * \brief
 * Selects source of data transmitted from PG_MUXA
 *
 * \details 
 * 0: Data is from client-side 1G/10G PCS
 * 1: Data is from Pattern Generator
 *
 * Field: VTSS_FIFO_BIST_Datapath_Control_Datapath_Control . EGR_XGMII_PG_SEL
 */
#define  VTSS_F_FIFO_BIST_Datapath_Control_Datapath_Control_EGR_XGMII_PG_SEL  VTSS_BIT(8)

/** 
 * \brief
 * Selects source of data transmitted from PG_MUXB
 *
 * \details 
 * 0: Data is from PG_MUXC in the ingress data path
 * 1: Data is from Pattern Generator
 *
 * Field: VTSS_FIFO_BIST_Datapath_Control_Datapath_Control . IGR_XGMII_PG_SEL
 */
#define  VTSS_F_FIFO_BIST_Datapath_Control_Datapath_Control_IGR_XGMII_PG_SEL  VTSS_BIT(7)

/** 
 * \brief
 * Selects source of data transmitted from PG_MUXC.  This mux is intended
 * to be used to route data to the packet BIST monitor.  This mux may not
 * be used as a host-side loopback (i.e.  Host-side data input looped back
 * to host-side data output).
 *
 * \details 
 * 0: Data is from ingress data path
 * 1: Data is from PG_MUXA in the egress data path
 *
 * Field: VTSS_FIFO_BIST_Datapath_Control_Datapath_Control . IGR_XGMII_PG_SEL2
 */
#define  VTSS_F_FIFO_BIST_Datapath_Control_Datapath_Control_IGR_XGMII_PG_SEL2  VTSS_BIT(6)

/** 
 * \brief
 * Line-side/Network Loopback L2C Enable.
 *
 * \details 
 * Loopback L2C is:
 * 0: Disabled
 * 1: Enabled
 *
 * Field: VTSS_FIFO_BIST_Datapath_Control_Datapath_Control . LOOP_L2C_ENA
 */
#define  VTSS_F_FIFO_BIST_Datapath_Control_Datapath_Control_LOOP_L2C_ENA  VTSS_BIT(1)

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


#endif /* _VTSS_MALIBU_REGS_FIFO_BIST_H_ */
