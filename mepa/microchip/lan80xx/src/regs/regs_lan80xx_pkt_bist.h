// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LAN80XX_MALIBU25G_REGS_PKT_BIST_H_
#define LAN80XX_MALIBU25G_REGS_PKT_BIST_H_

#include "regs_lan80xx_common.h"

/***********************************************************************
 *
 * Target: \a PKT_BIST
 *
 * Packet BIST config/status
 *
 ***********************************************************************/

/**
 * Register Group: \a PKT_BIST:GEN_CFG
 *
 * Packet Generator Configuration
 */


/**
 * \brief Generator configuration
 *
 * \details
 * Register: \a PKT_BIST:GEN_CFG:GEN_CFG
 */
#define LAN80XX_PKT_BIST_GEN_CFG                                                                    (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe900))

/**
 * \brief
 * Decrease pktlen by lenofs
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_GEN_CFG . LENOFS
 */
#define  LAN80XX_F_PKT_BIST_GEN_CFG_LENOFS(x)                                                       (LAN80XX_ENCODE_BITFIELD(x,12,3))
#define  LAN80XX_M_PKT_BIST_GEN_CFG_LENOFS                                                          (LAN80XX_ENCODE_BITMASK(12,3))
#define  LAN80XX_X_PKT_BIST_GEN_CFG_LENOFS(x)                                                       (LAN80XX_EXTRACT_BITFIELD(x,12,3))

/**
 * \brief
 * Number of standard frames between PTP frames
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_GEN_CFG . SRATE
 */
#define  LAN80XX_F_PKT_BIST_GEN_CFG_SRATE(x)                                                        (LAN80XX_ENCODE_BITFIELD(x,4,8))
#define  LAN80XX_M_PKT_BIST_GEN_CFG_SRATE                                                           (LAN80XX_ENCODE_BITMASK(4,8))
#define  LAN80XX_X_PKT_BIST_GEN_CFG_SRATE(x)                                                        (LAN80XX_EXTRACT_BITFIELD(x,4,8))

/**
 * \brief
 * Generate a single packet during pktgen_idles
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_GEN_CFG . SINGLE
 */
#define  LAN80XX_F_PKT_BIST_GEN_CFG_SINGLE(x)                                                       (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_PKT_BIST_GEN_CFG_SINGLE                                                          (LAN80XX_BIT(3))
#define  LAN80XX_X_PKT_BIST_GEN_CFG_SINGLE(x)                                                       (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Generate all Idles
 *
 * \details
 * 0: Generate frames
 * 1: Generate idles only
 *
 * Field: ::LAN80XX_PKT_BIST_GEN_CFG . IDLES
 */
#define  LAN80XX_F_PKT_BIST_GEN_CFG_IDLES(x)                                                        (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_PKT_BIST_GEN_CFG_IDLES                                                           (LAN80XX_BIT(2))
#define  LAN80XX_X_PKT_BIST_GEN_CFG_IDLES(x)                                                        (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Generate PTP frames
 *
 * \details
 * 0: Generate standard frames
 * 1: Generate PTP frames
 *
 * Field: ::LAN80XX_PKT_BIST_GEN_CFG . PTP_ENABLE
 */
#define  LAN80XX_F_PKT_BIST_GEN_CFG_PTP_ENABLE(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_PKT_BIST_GEN_CFG_PTP_ENABLE                                                      (LAN80XX_BIT(1))
#define  LAN80XX_X_PKT_BIST_GEN_CFG_PTP_ENABLE(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Enable packet generator
 *
 * \details
 * 0: Generator is disabled
 * 1: Generator is enabled
 * Note:   Packet generator data can not simultaneously be inserted in the
 * egress and ingress data paths. Insertion of packet generator data into
 * the paths is controlled by Datapath_Control.IGR_XGMII_PG_SEL and
 * Datapath_Control.EGR_XGMII_PG_SEL. Note: Pattern Generator does not
 * support Frame Preemption, and can only generate e-frames(unfragmented).
 *
 * Field: ::LAN80XX_PKT_BIST_GEN_CFG . ENABLE
 */
#define  LAN80XX_F_PKT_BIST_GEN_CFG_ENABLE(x)                                                       (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_PKT_BIST_GEN_CFG_ENABLE                                                          (LAN80XX_BIT(0))
#define  LAN80XX_X_PKT_BIST_GEN_CFG_ENABLE(x)                                                       (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a PKT_BIST:UPDATE
 *
 * Packet Update
 */


/**
 * \brief latch all counters and timestamps for readback
 *
 * \details
 * Register: \a PKT_BIST:UPDATE:UPDATE
 */
#define LAN80XX_PKT_BIST_UPDATE                                                                     (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe901))

/**
 * \brief
 * Freeze most recent 10 timestamps for readback
 *
 * \details
 * 0 : timestamps are updating. Do not read.
 * 1 : timestamps are not updating. Ok to read.
 *
 * Field: ::LAN80XX_PKT_BIST_UPDATE . TS_HOLD
 */
#define  LAN80XX_F_PKT_BIST_UPDATE_TS_HOLD(x)                                                       (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_PKT_BIST_UPDATE_TS_HOLD                                                          (LAN80XX_BIT(1))
#define  LAN80XX_X_PKT_BIST_UPDATE_TS_HOLD(x)                                                       (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Freeze all generator and monitor counters for readback
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_UPDATE . CNTR_UPDATE
 */
#define  LAN80XX_F_PKT_BIST_UPDATE_CNTR_UPDATE(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_PKT_BIST_UPDATE_CNTR_UPDATE                                                      (LAN80XX_BIT(0))
#define  LAN80XX_X_PKT_BIST_UPDATE_CNTR_UPDATE(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a PKT_BIST:GEN_PKTLEN
 *
 * Packet Length
 */


/**
 * \brief Packet length
 *
 * \details
 * Register: \a PKT_BIST:GEN_PKTLEN:GEN_PKTLEN
 */
#define LAN80XX_PKT_BIST_GEN_PKTLEN                                                                 (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe902))

/**
 * \brief
 * Packet length
 *
 * \details
 * 0: bytes = preamble + 64 + /T/
 * >0: bytes = 24 + pktlen*64 + (8-lenofs)
 *
 * Field: ::LAN80XX_PKT_BIST_GEN_PKTLEN . PKTLEN
 */
#define  LAN80XX_F_PKT_BIST_GEN_PKTLEN_PKTLEN(x)                                                    (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_PKT_BIST_GEN_PKTLEN_PKTLEN                                                       (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_PKT_BIST_GEN_PKTLEN_PKTLEN(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,0,8))

/**
 * Register Group: \a PKT_BIST:GEN_IPGLEN
 *
 * Packet IPG Length
 */


/**
 * \brief Lower 16 bits of 32-bit IPG length
 *
 * \details
 * Register: \a PKT_BIST:GEN_IPGLEN:GEN_IPGLEN_LSW
 */
#define LAN80XX_PKT_BIST_GEN_IPGLEN_LSW                                                             (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe903))

/**
 * \brief
 * IPG length: /I/ bytes = lenofs + ipglen*4
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_GEN_IPGLEN_LSW . IPGLEN_LSW
 */
#define  LAN80XX_F_PKT_BIST_GEN_IPGLEN_LSW_IPGLEN_LSW(x)                                            (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_GEN_IPGLEN_LSW_IPGLEN_LSW                                               (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_GEN_IPGLEN_LSW_IPGLEN_LSW(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Upper 16 bits of 32-bit IPG length
 *
 * \details
 * Register: \a PKT_BIST:GEN_IPGLEN:GEN_IPGLEN_MSW
 */
#define LAN80XX_PKT_BIST_GEN_IPGLEN_MSW                                                             (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe904))

/**
 * \brief
 * IPG length: /I/ bytes = lenofs + ipglen*4
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_GEN_IPGLEN_MSW . IPGLEN_MSW
 */
#define  LAN80XX_F_PKT_BIST_GEN_IPGLEN_MSW_IPGLEN_MSW(x)                                            (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_GEN_IPGLEN_MSW_IPGLEN_MSW                                               (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_GEN_IPGLEN_MSW_IPGLEN_MSW(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:GEN_TIME
 *
 * Packet Time
 */


/**
 * \brief PTP timestamp
 *
 * \details
 * Register: \a PKT_BIST:GEN_TIME:GEN_TIME
 */
#define LAN80XX_PKT_BIST_GEN_TIME                                                                   (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe905))

/**
 * \brief
 * PTP timestamp to generate: [15:8] is seconds, [7:0] is ns
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_GEN_TIME . PTPTIME
 */
#define  LAN80XX_F_PKT_BIST_GEN_TIME_PTPTIME(x)                                                     (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_GEN_TIME_PTPTIME                                                        (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_GEN_TIME_PTPTIME(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:GEN_ETYPE
 *
 * Packet ETYPE
 */


/**
 * \brief Ethernet type
 *
 * \details
 * Register: \a PKT_BIST:GEN_ETYPE:GEN_ETYPE
 */
#define LAN80XX_PKT_BIST_GEN_ETYPE                                                                  (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe906))

/**
 * \brief
 * Etype field for standard frames
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_GEN_ETYPE . ETYPE
 */
#define  LAN80XX_F_PKT_BIST_GEN_ETYPE_ETYPE(x)                                                      (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_GEN_ETYPE_ETYPE                                                         (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_GEN_ETYPE_ETYPE(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:GEN_SA
 *
 * Packet SA
 */


/**
 * \brief Lower 16 bits of 48-bit MAC source address to generate
 *
 * \details
 * Register: \a PKT_BIST:GEN_SA:GEN_SA0
 */
#define LAN80XX_PKT_BIST_GEN_SA0                                                                    (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe907))

/**
 * \brief
 * Generated MAC source address [15:0]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_GEN_SA0 . SA0
 */
#define  LAN80XX_F_PKT_BIST_GEN_SA0_SA0(x)                                                          (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_GEN_SA0_SA0                                                             (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_GEN_SA0_SA0(x)                                                          (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Middle 16 bits of 48-bit MAC source address to generate
 *
 * \details
 * Register: \a PKT_BIST:GEN_SA:GEN_SA1
 */
#define LAN80XX_PKT_BIST_GEN_SA1                                                                    (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe908))

/**
 * \brief
 * Generated MAC source address [31:16]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_GEN_SA1 . SA1
 */
#define  LAN80XX_F_PKT_BIST_GEN_SA1_SA1(x)                                                          (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_GEN_SA1_SA1                                                             (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_GEN_SA1_SA1(x)                                                          (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Upper 16 bits of 48-bit MAC source address to generate
 *
 * \details
 * Register: \a PKT_BIST:GEN_SA:GEN_SA2
 */
#define LAN80XX_PKT_BIST_GEN_SA2                                                                    (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe909))

/**
 * \brief
 * Generated MAC source address [47:32]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_GEN_SA2 . SA2
 */
#define  LAN80XX_F_PKT_BIST_GEN_SA2_SA2(x)                                                          (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_GEN_SA2_SA2                                                             (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_GEN_SA2_SA2(x)                                                          (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:GEN_DA
 *
 * Packet DA
 */


/**
 * \brief Lower 16 bits of 48-bit MAC destination address to generate
 *
 * \details
 * Register: \a PKT_BIST:GEN_DA:GEN_DA0
 */
#define LAN80XX_PKT_BIST_GEN_DA0                                                                    (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe90a))

/**
 * \brief
 * Generated MAC destination address [15:0]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_GEN_DA0 . DA0
 */
#define  LAN80XX_F_PKT_BIST_GEN_DA0_DA0(x)                                                          (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_GEN_DA0_DA0                                                             (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_GEN_DA0_DA0(x)                                                          (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Middle 16 bits of 48-bit MAC destination address to generate
 *
 * \details
 * Register: \a PKT_BIST:GEN_DA:GEN_DA1
 */
#define LAN80XX_PKT_BIST_GEN_DA1                                                                    (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe90b))

/**
 * \brief
 * Generated MAC destination address [31:16]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_GEN_DA1 . DA1
 */
#define  LAN80XX_F_PKT_BIST_GEN_DA1_DA1(x)                                                          (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_GEN_DA1_DA1                                                             (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_GEN_DA1_DA1(x)                                                          (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Upper 16 bits of 48-bit MAC destination address to generate
 *
 * \details
 * Register: \a PKT_BIST:GEN_DA:GEN_DA2
 */
#define LAN80XX_PKT_BIST_GEN_DA2                                                                    (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe90c))

/**
 * \brief
 * Generated MAC destination address [47:32]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_GEN_DA2 . DA2
 */
#define  LAN80XX_F_PKT_BIST_GEN_DA2_DA2(x)                                                          (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_GEN_DA2_DA2                                                             (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_GEN_DA2_DA2(x)                                                          (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:GEN_SENT
 *
 * Packet Sent
 */


/**
 * \brief Lower 16 bits of 32-bit packets_sent counter
 *
 * \details
 * Register: \a PKT_BIST:GEN_SENT:GEN_SENT_LSW
 */
#define LAN80XX_PKT_BIST_GEN_SENT_LSW                                                               (LAN80XX_IOREG(LAN80XX_TO_PKT_BIST,0xe90d))

/**
 * \brief
 * LSW of number of packets generated. Use reg CNTR_UPDATE to load the
 * counter data. Non-rollover
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_GEN_SENT_LSW . SENT_LSW
 */
#define  LAN80XX_F_PKT_BIST_GEN_SENT_LSW_SENT_LSW(x)                                                (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_GEN_SENT_LSW_SENT_LSW                                                   (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_GEN_SENT_LSW_SENT_LSW(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Upper 16 bits of 32-bit packets_sent counter
 *
 * \details
 * Register: \a PKT_BIST:GEN_SENT:GEN_SENT_MSW
 */
#define LAN80XX_PKT_BIST_GEN_SENT_MSW                                                               (LAN80XX_IOREG(LAN80XX_TO_PKT_BIST,0xe90e))

/**
 * \brief
 * MSW of number of packets generated. Use reg CNTR_UPDATE to load the
 * counter data. Non-rollover
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_GEN_SENT_MSW . SENT_MSW
 */
#define  LAN80XX_F_PKT_BIST_GEN_SENT_MSW_SENT_MSW(x)                                                (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_GEN_SENT_MSW_SENT_MSW                                                   (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_GEN_SENT_MSW_SENT_MSW(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:TRANSPORT_SPECIFIC_MAJOR_SDOID
 *
 * Transport specific in PTP v2 or Major SDO ID in PTP v2.1
 */


/**
 * \brief The transport specific in PTP v2 or the Major SDO ID in PTP v2.1
 *
 * \details
 * Register: \a PKT_BIST:TRANSPORT_SPECIFIC_MAJOR_SDOID:TRANSPORT_SPECIFIC_MAJOR_SDOID
 */
#define LAN80XX_PKT_BIST_TRANSPORT_SPECIFIC_MAJOR_SDOID                                             (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe90f))

/**
 * \brief
 * The subtype of the Announce and Signaling message of transport in PTP v2
 * or the Major SDO(Standards Development Organization) ID in PTP v2.1. If
 * SdoId appears in the common header of all PTP messages, PTP nodes can
 * then ignore all messages which do not have the SdoID they want
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_TRANSPORT_SPECIFIC_MAJOR_SDOID . TRANSPORT_SPECIFIC_MAJOR_SDOID
 */
#define  LAN80XX_F_PKT_BIST_TRANSPORT_SPECIFIC_MAJOR_SDOID_TRANSPORT_SPECIFIC_MAJOR_SDOID(x)        (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_PKT_BIST_TRANSPORT_SPECIFIC_MAJOR_SDOID_TRANSPORT_SPECIFIC_MAJOR_SDOID           (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_PKT_BIST_TRANSPORT_SPECIFIC_MAJOR_SDOID_TRANSPORT_SPECIFIC_MAJOR_SDOID(x)        (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * Register Group: \a PKT_BIST:MINOR_VERSION_PTP
 *
 * Minor Version of PTP
 */


/**
 * \brief Minor Version of PTP
 *
 * \details
 * Register: \a PKT_BIST:MINOR_VERSION_PTP:MINOR_VERSION
 */
#define LAN80XX_PKT_BIST_MINOR_VERSION                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe910))

/**
 * \brief
 * This reg is reserved in PTP v2. In the PTP v2.1, it is minor version of
 * PTP. That will allow PTP nodes to distinguish PTPv2 and PTPv2.1
 * messages.  If a PTPv2 node which does not know about PTPv2.1 receives a
 * PTPv2.1 message, it will ignore the minor version number, since that was
 * previously a reserved field
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MINOR_VERSION . MINOR_VERSION
 */
#define  LAN80XX_F_PKT_BIST_MINOR_VERSION_MINOR_VERSION(x)                                          (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_PKT_BIST_MINOR_VERSION_MINOR_VERSION                                             (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_PKT_BIST_MINOR_VERSION_MINOR_VERSION(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * Register Group: \a PKT_BIST:MINOR_SDOID
 *
 * Minor SDO ID in PTP v2.1
 */


/**
 * \brief Minor SDO ID in PTP v2.1
 *
 * \details
 * Register: \a PKT_BIST:MINOR_SDOID:MINOR_SDOID
 */
#define LAN80XX_PKT_BIST_MINOR_SDOID                                                                (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe911))

/**
 * \brief
 * This reg is ignored in PTP v2. In PTP v2.1, this is the minor SDO ID. If
 * SdoId appears in the common header of all PTP messages, PTP nodes can
 * then ignore all messages which do not have the SdoID they want
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MINOR_SDOID . MINOR_SDOID
 */
#define  LAN80XX_F_PKT_BIST_MINOR_SDOID_MINOR_SDOID(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_PKT_BIST_MINOR_SDOID_MINOR_SDOID                                                 (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_PKT_BIST_MINOR_SDOID_MINOR_SDOID(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,8))

/**
 * Register Group: \a PKT_BIST:MESSAGE_TYPE_SPECIFIC
 *
 * Message Type Specific in PTP v2.1
 */


/**
 * \brief Message Type Specific MSB in PTP v2.1
 *
 * \details
 * Register: \a PKT_BIST:MESSAGE_TYPE_SPECIFIC:MESSAGE_TYPE_SPECIFIC_HI
 */
#define LAN80XX_PKT_BIST_MESSAGE_TYPE_SPECIFIC_HI                                                   (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe912))

/**
 * \brief
 * This reg is ignored in PTP v2. In PTP v2.1, this is the message type
 * specific, bit 31 to bit 16
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MESSAGE_TYPE_SPECIFIC_HI . MESSAGE_TYPE_SPECIFIC_HI
 */
#define  LAN80XX_F_PKT_BIST_MESSAGE_TYPE_SPECIFIC_HI_MESSAGE_TYPE_SPECIFIC_HI(x)                    (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MESSAGE_TYPE_SPECIFIC_HI_MESSAGE_TYPE_SPECIFIC_HI                       (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MESSAGE_TYPE_SPECIFIC_HI_MESSAGE_TYPE_SPECIFIC_HI(x)                    (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Message Type Specific LSB in PTP v2.1
 *
 * \details
 * Register: \a PKT_BIST:MESSAGE_TYPE_SPECIFIC:MESSAGE_TYPE_SPECIFIC_LO
 */
#define LAN80XX_PKT_BIST_MESSAGE_TYPE_SPECIFIC_LO                                                   (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe913))

/**
 * \brief
 * This reg is ignored in PTP v2. In PTP v2.1, this is the message type
 * specific, bit 15 to bit 0
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MESSAGE_TYPE_SPECIFIC_LO . MESSAGE_TYPE_SPECIFIC_LO
 */
#define  LAN80XX_F_PKT_BIST_MESSAGE_TYPE_SPECIFIC_LO_MESSAGE_TYPE_SPECIFIC_LO(x)                    (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MESSAGE_TYPE_SPECIFIC_LO_MESSAGE_TYPE_SPECIFIC_LO                       (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MESSAGE_TYPE_SPECIFIC_LO_MESSAGE_TYPE_SPECIFIC_LO(x)                    (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:MON_CFG
 *
 * Packet Monitor CFG
 */


/**
 * \brief monitor configuration
 *
 * \details
 * Register: \a PKT_BIST:MON_CFG:MON_CFG
 */
#define LAN80XX_PKT_BIST_MON_CFG                                                                    (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe914))

/**
 * \brief
 * Enable packet monitor. Packet monitor does not support Frame Preemption,
 * any p-frames or p-frame fragments will result in incorrect packet counts
 *
 * \details
 * 0: Monitor is disabled
 * 1: Monitor is enabled
 *
 * Field: ::LAN80XX_PKT_BIST_MON_CFG . ENABLE
 */
#define  LAN80XX_F_PKT_BIST_MON_CFG_ENABLE(x)                                                       (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_PKT_BIST_MON_CFG_ENABLE                                                          (LAN80XX_BIT(0))
#define  LAN80XX_X_PKT_BIST_MON_CFG_ENABLE(x)                                                       (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a PKT_BIST:MON_RST
 *
 * Packet Monitor RST
 */


/**
 * \brief Self-clearing monitor counters reset
 *
 * \details
 * Register: \a PKT_BIST:MON_RST:MON_RST
 */
#define LAN80XX_PKT_BIST_MON_RST                                                                    (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe915))

/**
 * \brief
 * Write 1 to reset BER counter, self-clear
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_RST . BER_RST
 */
#define  LAN80XX_F_PKT_BIST_MON_RST_BER_RST(x)                                                      (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_PKT_BIST_MON_RST_BER_RST                                                         (LAN80XX_BIT(5))
#define  LAN80XX_X_PKT_BIST_MON_RST_BER_RST(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Write 1 to reset Local_Fault counter, self-clear
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_RST . LFAULT_RST
 */
#define  LAN80XX_F_PKT_BIST_MON_RST_LFAULT_RST(x)                                                   (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_PKT_BIST_MON_RST_LFAULT_RST                                                      (LAN80XX_BIT(4))
#define  LAN80XX_X_PKT_BIST_MON_RST_LFAULT_RST(x)                                                   (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Write 1 to reset Packet_Fragment counter, self-clear
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_RST . FRAG_RST
 */
#define  LAN80XX_F_PKT_BIST_MON_RST_FRAG_RST(x)                                                     (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_PKT_BIST_MON_RST_FRAG_RST                                                        (LAN80XX_BIT(3))
#define  LAN80XX_X_PKT_BIST_MON_RST_FRAG_RST(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Write 1 to reset Bad_CRC counter, self-clear
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_RST . BAD_RST
 */
#define  LAN80XX_F_PKT_BIST_MON_RST_BAD_RST(x)                                                      (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_PKT_BIST_MON_RST_BAD_RST                                                         (LAN80XX_BIT(2))
#define  LAN80XX_X_PKT_BIST_MON_RST_BAD_RST(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Write 1 to reset Good_CRC counter, self-clear
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_RST . GOOD_RST
 */
#define  LAN80XX_F_PKT_BIST_MON_RST_GOOD_RST(x)                                                     (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_PKT_BIST_MON_RST_GOOD_RST                                                        (LAN80XX_BIT(1))
#define  LAN80XX_X_PKT_BIST_MON_RST_GOOD_RST(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Write 1 to reset all counters, self-clear
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_RST . ALL_RST
 */
#define  LAN80XX_F_PKT_BIST_MON_RST_ALL_RST(x)                                                      (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_PKT_BIST_MON_RST_ALL_RST                                                         (LAN80XX_BIT(0))
#define  LAN80XX_X_PKT_BIST_MON_RST_ALL_RST(x)                                                      (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a PKT_BIST:MON_GOODCRC
 *
 * Packet Monitor Good CRC
 */


/**
 * \brief Lower 16 bits of 32-bit Good_CRC counter
 *
 * \details
 * Register: \a PKT_BIST:MON_GOODCRC:MON_GOOD_LSW
 */
#define LAN80XX_PKT_BIST_MON_GOOD_LSW                                                               (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe916))

/**
 * \brief
 * LSW of Good_CRC counter. Use reg CNTR_UPDATE to load the counter data.
 * Non-rollover
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_GOOD_LSW . GOOD_LSW
 */
#define  LAN80XX_F_PKT_BIST_MON_GOOD_LSW_GOOD_LSW(x)                                                (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_GOOD_LSW_GOOD_LSW                                                   (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_GOOD_LSW_GOOD_LSW(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Upper 16 bits of 32-bit Good_CRC counter
 *
 * \details
 * Register: \a PKT_BIST:MON_GOODCRC:MON_GOOD_MSW
 */
#define LAN80XX_PKT_BIST_MON_GOOD_MSW                                                               (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe917))

/**
 * \brief
 * MSW of Good_CRC counter. Use reg CNTR_UPDATE to load the counter data.
 * Non-rollover
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_GOOD_MSW . GOOD_MSW
 */
#define  LAN80XX_F_PKT_BIST_MON_GOOD_MSW_GOOD_MSW(x)                                                (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_GOOD_MSW_GOOD_MSW                                                   (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_GOOD_MSW_GOOD_MSW(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:MON_BADCRC
 *
 * Packet Monitor Bad CRC
 */


/**
 * \brief Lower 16 bits of 32-bit Bad_CRC counter
 *
 * \details
 * Register: \a PKT_BIST:MON_BADCRC:MON_BAD_LSW
 */
#define LAN80XX_PKT_BIST_MON_BAD_LSW                                                                (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe918))

/**
 * \brief
 * LSW of Bad_CRC counter. Use reg CNTR_UPDATE to load the counter data.
 * Non-rollover
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_BAD_LSW . BAD_LSW
 */
#define  LAN80XX_F_PKT_BIST_MON_BAD_LSW_BAD_LSW(x)                                                  (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_BAD_LSW_BAD_LSW                                                     (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_BAD_LSW_BAD_LSW(x)                                                  (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Upper 16 bits of 32-bit Bad_CRC counter
 *
 * \details
 * Register: \a PKT_BIST:MON_BADCRC:MON_BAD_MSW
 */
#define LAN80XX_PKT_BIST_MON_BAD_MSW                                                                (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe919))

/**
 * \brief
 * MSW of Bad_CRC counter. Use reg CNTR_UPDATE to load the counter data.
 * Non-rollover
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_BAD_MSW . BAD_MSW
 */
#define  LAN80XX_F_PKT_BIST_MON_BAD_MSW_BAD_MSW(x)                                                  (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_BAD_MSW_BAD_MSW                                                     (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_BAD_MSW_BAD_MSW(x)                                                  (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:MON_FRAG
 *
 * Packet Monitor Fragment
 */


/**
 * \brief Lower 16 bits of 32-bit Packet_Fragment counter
 *
 * \details
 * Register: \a PKT_BIST:MON_FRAG:MON_FRAG_LSW
 */
#define LAN80XX_PKT_BIST_MON_FRAG_LSW                                                               (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe91a))

/**
 * \brief
 * LSW of Packet_Fragment counter. Packet monitor does not support Frame
 * Preemption, packet fragments are counted as errors. Use reg CNTR_UPDATE
 * to load the counter data. Non-rollover
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_FRAG_LSW . FRAG_LSW
 */
#define  LAN80XX_F_PKT_BIST_MON_FRAG_LSW_FRAG_LSW(x)                                                (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_FRAG_LSW_FRAG_LSW                                                   (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_FRAG_LSW_FRAG_LSW(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Upper 16 bits of 32-bit Packet_Fragment counter
 *
 * \details
 * Register: \a PKT_BIST:MON_FRAG:MON_FRAG_MSW
 */
#define LAN80XX_PKT_BIST_MON_FRAG_MSW                                                               (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe91b))

/**
 * \brief
 * MSW of Packet_Fragment counter. Packet monitor does not support Frame
 * Preemption, packet fragments are counted as errors. Use reg CNTR_UPDATE
 * to load the counter data. Non-rollover
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_FRAG_MSW . FRAG_MSW
 */
#define  LAN80XX_F_PKT_BIST_MON_FRAG_MSW_FRAG_MSW(x)                                                (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_FRAG_MSW_FRAG_MSW                                                   (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_FRAG_MSW_FRAG_MSW(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:MON_LFAULT
 *
 * Packet Monitor Local Fault
 */


/**
 * \brief Lower 16 bits of 32-bit Local_Fault counter
 *
 * \details
 * Register: \a PKT_BIST:MON_LFAULT:MON_LFAULT_LSW
 */
#define LAN80XX_PKT_BIST_MON_LFAULT_LSW                                                             (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe91c))

/**
 * \brief
 * LSW of Local_Fault counter. Use reg CNTR_UPDATE to load the counter
 * data. Non-rollover
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_LFAULT_LSW . LFAULT_LSW
 */
#define  LAN80XX_F_PKT_BIST_MON_LFAULT_LSW_LFAULT_LSW(x)                                            (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_LFAULT_LSW_LFAULT_LSW                                               (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_LFAULT_LSW_LFAULT_LSW(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Upper 16 bits of 32-bit Local_Fault counter
 *
 * \details
 * Register: \a PKT_BIST:MON_LFAULT:MON_LFAULT_MSW
 */
#define LAN80XX_PKT_BIST_MON_LFAULT_MSW                                                             (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe91d))

/**
 * \brief
 * MSW of Local_Fault counter. Use reg CNTR_UPDATE to load the counter
 * data. Non-rollover
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_LFAULT_MSW . LFAULT_MSW
 */
#define  LAN80XX_F_PKT_BIST_MON_LFAULT_MSW_LFAULT_MSW(x)                                            (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_LFAULT_MSW_LFAULT_MSW                                               (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_LFAULT_MSW_LFAULT_MSW(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:MON_BER
 *
 * Packet Monitor Bit Error Rate
 */


/**
 * \brief Lower 16 bits of 32-bit BER counter
 *
 * \details
 * Register: \a PKT_BIST:MON_BER:MON_BER_LSW
 */
#define LAN80XX_PKT_BIST_MON_BER_LSW                                                                (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe91e))

/**
 * \brief
 * LSW of BER counter. Use reg CNTR_UPDATE to load the counter data.
 * Non-rollover
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_BER_LSW . BER_LSW
 */
#define  LAN80XX_F_PKT_BIST_MON_BER_LSW_BER_LSW(x)                                                  (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_BER_LSW_BER_LSW                                                     (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_BER_LSW_BER_LSW(x)                                                  (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Upper 16 bits of 32-bit BER counter
 *
 * \details
 * Register: \a PKT_BIST:MON_BER:MON_BER_MSW
 */
#define LAN80XX_PKT_BIST_MON_BER_MSW                                                                (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe91f))

/**
 * \brief
 * MSW of BER counter. Use reg CNTR_UPDATE to load the counter data.
 * Non-rollover
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_BER_MSW . BER_MSW
 */
#define  LAN80XX_F_PKT_BIST_MON_BER_MSW_BER_MSW(x)                                                  (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_BER_MSW_BER_MSW                                                     (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_BER_MSW_BER_MSW(x)                                                  (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:MON_TSTAMP0
 *
 * Packet Monitor PTP Timestamp0
 */


/**
 * \brief PTP timestamp0 (oldest) bits 15-0
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP0:MON_TSTAMP0_0
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP0_0                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe920))

/**
 * \brief
 * PTP timestamp 0, bits [15:0]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP0_0 . TSTAMP0_0
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP0_0_TSTAMP0_0(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP0_0_TSTAMP0_0                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP0_0_TSTAMP0_0(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp0 (oldest) bits 31-16
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP0:MON_TSTAMP0_1
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP0_1                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe921))

/**
 * \brief
 * PTP timestamp 0, bits [31:16]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP0_1 . TSTAMP0_1
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP0_1_TSTAMP0_1(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP0_1_TSTAMP0_1                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP0_1_TSTAMP0_1(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp0 (oldest) bits 47-32
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP0:MON_TSTAMP0_2
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP0_2                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe922))

/**
 * \brief
 * PTP timestamp 0, bits [47:32]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP0_2 . TSTAMP0_2
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP0_2_TSTAMP0_2(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP0_2_TSTAMP0_2                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP0_2_TSTAMP0_2(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp0 (oldest) bits 63-48
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP0:MON_TSTAMP0_3
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP0_3                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe923))

/**
 * \brief
 * PTP timestamp 0, bits [63:48]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP0_3 . TSTAMP0_3
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP0_3_TSTAMP0_3(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP0_3_TSTAMP0_3                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP0_3_TSTAMP0_3(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp0 (oldest) bits 79-64
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP0:MON_TSTAMP0_4
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP0_4                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe924))

/**
 * \brief
 * PTP timestamp 0, bits [79:64]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP0_4 . TSTAMP0_4
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP0_4_TSTAMP0_4(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP0_4_TSTAMP0_4                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP0_4_TSTAMP0_4(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:MON_TSTAMP1
 *
 * Packet Monitor PTP Timestamp1
 */


/**
 * \brief PTP timestamp1 bits 15-0
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP1:MON_TSTAMP1_0
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP1_0                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe925))

/**
 * \brief
 * PTP timestamp 1, bits [15:0]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP1_0 . TSTAMP1_0
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP1_0_TSTAMP1_0(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP1_0_TSTAMP1_0                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP1_0_TSTAMP1_0(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp1 bits 31-16
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP1:MON_TSTAMP1_1
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP1_1                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0, 0xe926))

/**
 * \brief
 * PTP timestamp 1, bits [31:16]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP1_1 . TSTAMP1_1
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP1_1_TSTAMP1_1(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP1_1_TSTAMP1_1                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP1_1_TSTAMP1_1(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp1 bits 47-32
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP1:MON_TSTAMP1_2
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP1_2                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe927))

/**
 * \brief
 * PTP timestamp 1, bits [47:32]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP1_2 . TSTAMP1_2
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP1_2_TSTAMP1_2(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP1_2_TSTAMP1_2                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP1_2_TSTAMP1_2(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp1 bits 63-48
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP1:MON_TSTAMP1_3
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP1_3                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe928))

/**
 * \brief
 * PTP timestamp 1, bits [63:48]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP1_3 . TSTAMP1_3
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP1_3_TSTAMP1_3(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP1_3_TSTAMP1_3                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP1_3_TSTAMP1_3(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp1 bits 79-64
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP1:MON_TSTAMP1_4
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP1_4                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe929))

/**
 * \brief
 * PTP timestamp 1, bits [79:64]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP1_4 . TSTAMP1_4
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP1_4_TSTAMP1_4(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP1_4_TSTAMP1_4                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP1_4_TSTAMP1_4(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:MON_TSTAMP2
 *
 * Packet Monitor PTP Timestamp2
 */


/**
 * \brief PTP timestamp2 bits 15-0
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP2:MON_TSTAMP2_0
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP2_0                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe92a))

/**
 * \brief
 * PTP timestamp 2, bits [15:0]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP2_0 . TSTAMP2_0
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP2_0_TSTAMP2_0(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP2_0_TSTAMP2_0                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP2_0_TSTAMP2_0(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp2 bits 31-16
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP2:MON_TSTAMP2_1
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP2_1                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe92b))

/**
 * \brief
 * PTP timestamp 2, bits [31:16]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP2_1 . TSTAMP2_1
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP2_1_TSTAMP2_1(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP2_1_TSTAMP2_1                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP2_1_TSTAMP2_1(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp2 bits 47-32
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP2:MON_TSTAMP2_2
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP2_2                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe92c))

/**
 * \brief
 * PTP timestamp 2, bits [47:32]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP2_2 . TSTAMP2_2
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP2_2_TSTAMP2_2(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP2_2_TSTAMP2_2                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP2_2_TSTAMP2_2(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp2 bits 63-48
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP2:MON_TSTAMP2_3
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP2_3                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe92d))

/**
 * \brief
 * PTP timestamp 2, bits [63:48]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP2_3 . TSTAMP2_3
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP2_3_TSTAMP2_3(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP2_3_TSTAMP2_3                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP2_3_TSTAMP2_3(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp2 bits 79-64
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP2:MON_TSTAMP2_4
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP2_4                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe92e))

/**
 * \brief
 * PTP timestamp 2, bits [79:64]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP2_4 . TSTAMP2_4
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP2_4_TSTAMP2_4(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP2_4_TSTAMP2_4                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP2_4_TSTAMP2_4(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:MON_TSTAMP3
 *
 * Packet Monitor PTP Timestamp3
 */


/**
 * \brief PTP timestamp3 bits 15-0
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP3:MON_TSTAMP3_0
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP3_0                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe92f))

/**
 * \brief
 * PTP timestamp 3, bits [15:0]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP3_0 . TSTAMP3_0
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP3_0_TSTAMP3_0(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP3_0_TSTAMP3_0                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP3_0_TSTAMP3_0(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp3 bits 31-16
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP3:MON_TSTAMP3_1
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP3_1                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe930))

/**
 * \brief
 * PTP timestamp 3, bits [31:16]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP3_1 . TSTAMP3_1
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP3_1_TSTAMP3_1(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP3_1_TSTAMP3_1                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP3_1_TSTAMP3_1(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp3 bits 47-32
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP3:MON_TSTAMP3_2
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP3_2                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe931))

/**
 * \brief
 * PTP timestamp 3, bits [47:32]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP3_2 . TSTAMP3_2
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP3_2_TSTAMP3_2(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP3_2_TSTAMP3_2                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP3_2_TSTAMP3_2(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp3 bits 63-48
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP3:MON_TSTAMP3_3
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP3_3                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe932))

/**
 * \brief
 * PTP timestamp 3, bits [63:48]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP3_3 . TSTAMP3_3
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP3_3_TSTAMP3_3(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP3_3_TSTAMP3_3                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP3_3_TSTAMP3_3(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp3 bits 79-64
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP3:MON_TSTAMP3_4
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP3_4                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe933))

/**
 * \brief
 * PTP timestamp 3, bits [79:64]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP3_4 . TSTAMP3_4
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP3_4_TSTAMP3_4(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP3_4_TSTAMP3_4                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP3_4_TSTAMP3_4(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:MON_TSTAMP4
 *
 * Packet Monitor PTP Timestamp4
 */


/**
 * \brief PTP timestamp4 bits 15-0
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP4:MON_TSTAMP4_0
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP4_0                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe934))

/**
 * \brief
 * PTP timestamp 4, bits [15:0]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP4_0 . TSTAMP4_0
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP4_0_TSTAMP4_0(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP4_0_TSTAMP4_0                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP4_0_TSTAMP4_0(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp4 bits 31-16
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP4:MON_TSTAMP4_1
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP4_1                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe935))

/**
 * \brief
 * PTP timestamp 4, bits [31:16]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP4_1 . TSTAMP4_1
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP4_1_TSTAMP4_1(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP4_1_TSTAMP4_1                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP4_1_TSTAMP4_1(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp4 bits 47-32
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP4:MON_TSTAMP4_2
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP4_2                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe936))

/**
 * \brief
 * PTP timestamp 4, bits [47:32]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP4_2 . TSTAMP4_2
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP4_2_TSTAMP4_2(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP4_2_TSTAMP4_2                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP4_2_TSTAMP4_2(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp4 bits 63-48
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP4:MON_TSTAMP4_3
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP4_3                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe937))

/**
 * \brief
 * PTP timestamp 4, bits [63:48]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP4_3 . TSTAMP4_3
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP4_3_TSTAMP4_3(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP4_3_TSTAMP4_3                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP4_3_TSTAMP4_3(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp4 bits 79-64
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP4:MON_TSTAMP4_4
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP4_4                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe938))

/**
 * \brief
 * PTP timestamp 4, bits [79:64]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP4_4 . TSTAMP4_4
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP4_4_TSTAMP4_4(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP4_4_TSTAMP4_4                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP4_4_TSTAMP4_4(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:MON_TSTAMP5
 *
 * Packet Monitor PTP Timestamp5
 */


/**
 * \brief PTP timestamp5 bits 15-0
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP5:MON_TSTAMP5_0
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP5_0                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe939))

/**
 * \brief
 * PTP timestamp 5, bits [15:0]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP5_0 . TSTAMP5_0
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP5_0_TSTAMP5_0(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP5_0_TSTAMP5_0                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP5_0_TSTAMP5_0(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp5 bits 31-16
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP5:MON_TSTAMP5_1
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP5_1                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe93a))

/**
 * \brief
 * PTP timestamp 5, bits [31:16]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP5_1 . TSTAMP5_1
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP5_1_TSTAMP5_1(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP5_1_TSTAMP5_1                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP5_1_TSTAMP5_1(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp5 bits 47-32
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP5:MON_TSTAMP5_2
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP5_2                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe93b))

/**
 * \brief
 * PTP timestamp 5, bits [47:32]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP5_2 . TSTAMP5_2
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP5_2_TSTAMP5_2(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP5_2_TSTAMP5_2                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP5_2_TSTAMP5_2(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp5 bits 63-48
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP5:MON_TSTAMP5_3
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP5_3                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe93c))

/**
 * \brief
 * PTP timestamp 5, bits [63:48]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP5_3 . TSTAMP5_3
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP5_3_TSTAMP5_3(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP5_3_TSTAMP5_3                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP5_3_TSTAMP5_3(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp5 bits 79-64
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP5:MON_TSTAMP5_4
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP5_4                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe93d))

/**
 * \brief
 * PTP timestamp 5, bits [79:64]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP5_4 . TSTAMP5_4
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP5_4_TSTAMP5_4(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP5_4_TSTAMP5_4                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP5_4_TSTAMP5_4(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:MON_TSTAMP6
 *
 * Packet Monitor PTP Timestamp6
 */


/**
 * \brief PTP timestamp6 bits 15-0
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP6:MON_TSTAMP6_0
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP6_0                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe93e))

/**
 * \brief
 * PTP timestamp 6, bits [15:0]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP6_0 . TSTAMP6_0
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP6_0_TSTAMP6_0(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP6_0_TSTAMP6_0                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP6_0_TSTAMP6_0(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp6 bits 31-16
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP6:MON_TSTAMP6_1
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP6_1                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe93f))

/**
 * \brief
 * PTP timestamp 6, bits [31:16]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP6_1 . TSTAMP6_1
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP6_1_TSTAMP6_1(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP6_1_TSTAMP6_1                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP6_1_TSTAMP6_1(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp6 bits 47-32
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP6:MON_TSTAMP6_2
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP6_2                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe940))

/**
 * \brief
 * PTP timestamp 6, bits [47:32]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP6_2 . TSTAMP6_2
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP6_2_TSTAMP6_2(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP6_2_TSTAMP6_2                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP6_2_TSTAMP6_2(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp6 bits 63-48
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP6:MON_TSTAMP6_3
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP6_3                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe941))

/**
 * \brief
 * PTP timestamp 6, bits [63:48]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP6_3 . TSTAMP6_3
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP6_3_TSTAMP6_3(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP6_3_TSTAMP6_3                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP6_3_TSTAMP6_3(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp6 bits 79-64
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP6:MON_TSTAMP6_4
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP6_4                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe942))

/**
 * \brief
 * PTP timestamp 6, bits [79:64]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP6_4 . TSTAMP6_4
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP6_4_TSTAMP6_4(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP6_4_TSTAMP6_4                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP6_4_TSTAMP6_4(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:MON_TSTAMP7
 *
 * Packet Monitor PTP Timestamp7
 */


/**
 * \brief PTP timestamp7 bits 15-0
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP7:MON_TSTAMP7_0
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP7_0                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe943))

/**
 * \brief
 * PTP timestamp 7, bits [15:0]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP7_0 . TSTAMP7_0
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP7_0_TSTAMP7_0(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP7_0_TSTAMP7_0                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP7_0_TSTAMP7_0(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp7 bits 31-16
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP7:MON_TSTAMP7_1
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP7_1                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe944))

/**
 * \brief
 * PTP timestamp 7, bits [31:16]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP7_1 . TSTAMP7_1
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP7_1_TSTAMP7_1(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP7_1_TSTAMP7_1                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP7_1_TSTAMP7_1(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp7 bits 47-32
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP7:MON_TSTAMP7_2
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP7_2                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe945))

/**
 * \brief
 * PTP timestamp 7, bits [47:32]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP7_2 . TSTAMP7_2
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP7_2_TSTAMP7_2(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP7_2_TSTAMP7_2                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP7_2_TSTAMP7_2(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp7 bits 63-48
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP7:MON_TSTAMP7_3
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP7_3                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe946))

/**
 * \brief
 * PTP timestamp 7, bits [63:48]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP7_3 . TSTAMP7_3
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP7_3_TSTAMP7_3(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP7_3_TSTAMP7_3                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP7_3_TSTAMP7_3(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp7 bits 79-64
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP7:MON_TSTAMP7_4
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP7_4                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe947))

/**
 * \brief
 * PTP timestamp 7, bits [79:64]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP7_4 . TSTAMP7_4
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP7_4_TSTAMP7_4(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP7_4_TSTAMP7_4                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP7_4_TSTAMP7_4(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:MON_TSTAMP8
 *
 * Packet Monitor PTP Timestamp8
 */


/**
 * \brief PTP timestamp8 bits 15-0
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP8:MON_TSTAMP8_0
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP8_0                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe948))

/**
 * \brief
 * PTP timestamp 8, bits [15:0]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP8_0 . TSTAMP8_0
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP8_0_TSTAMP8_0(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP8_0_TSTAMP8_0                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP8_0_TSTAMP8_0(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp8 bits 31-16
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP8:MON_TSTAMP8_1
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP8_1                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe949))

/**
 * \brief
 * PTP timestamp 8, bits [31:16]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP8_1 . TSTAMP8_1
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP8_1_TSTAMP8_1(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP8_1_TSTAMP8_1                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP8_1_TSTAMP8_1(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp8 bits 47-32
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP8:MON_TSTAMP8_2
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP8_2                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe94a))

/**
 * \brief
 * PTP timestamp 8, bits [47:32]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP8_2 . TSTAMP8_2
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP8_2_TSTAMP8_2(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP8_2_TSTAMP8_2                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP8_2_TSTAMP8_2(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp8 bits 63-48
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP8:MON_TSTAMP8_3
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP8_3                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe94b))

/**
 * \brief
 * PTP timestamp 8, bits [63:48]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP8_3 . TSTAMP8_3
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP8_3_TSTAMP8_3(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP8_3_TSTAMP8_3                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP8_3_TSTAMP8_3(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp8 bits 79-64
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP8:MON_TSTAMP8_4
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP8_4                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe94c))

/**
 * \brief
 * PTP timestamp 8, bits [79:64]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP8_4 . TSTAMP8_4
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP8_4_TSTAMP8_4(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP8_4_TSTAMP8_4                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP8_4_TSTAMP8_4(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a PKT_BIST:MON_TSTAMP9
 *
 * Packet Monitor PTP Timestamp9
 */


/**
 * \brief PTP timestamp9 (most recent) bits 15-0
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP9:MON_TSTAMP9_0
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP9_0                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe94d))

/**
 * \brief
 * PTP timestamp 9, bits [15:0]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP9_0 . TSTAMP9_0
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP9_0_TSTAMP9_0(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP9_0_TSTAMP9_0                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP9_0_TSTAMP9_0(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp9 (most recent) bits 31-16
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP9:MON_TSTAMP9_1
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP9_1                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe94e))

/**
 * \brief
 * PTP timestamp 9, bits [31:16]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP9_1 . TSTAMP9_1
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP9_1_TSTAMP9_1(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP9_1_TSTAMP9_1                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP9_1_TSTAMP9_1(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp9 (most recent) bits 47-32
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP9:MON_TSTAMP9_2
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP9_2                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe94f))

/**
 * \brief
 * PTP timestamp 9, bits [47:32]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP9_2 . TSTAMP9_2
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP9_2_TSTAMP9_2(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP9_2_TSTAMP9_2                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP9_2_TSTAMP9_2(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp9 (most recent) bits 63-48
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP9:MON_TSTAMP9_3
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP9_3                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe950))

/**
 * \brief
 * PTP timestamp 9, bits [63:48]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP9_3 . TSTAMP9_3
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP9_3_TSTAMP9_3(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP9_3_TSTAMP9_3                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP9_3_TSTAMP9_3(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief PTP timestamp9 (most recent) bits 79-64
 *
 * \details
 * Register: \a PKT_BIST:MON_TSTAMP9:MON_TSTAMP9_4
 */
#define LAN80XX_PKT_BIST_MON_TSTAMP9_4                                                              (LAN80XX_IOREG(MMD_ID_PKT_BIST, 0,0xe951))

/**
 * \brief
 * PTP timestamp 9, bits [79:64]
 *
 * \details
 * Field: ::LAN80XX_PKT_BIST_MON_TSTAMP9_4 . TSTAMP9_4
 */
#define  LAN80XX_F_PKT_BIST_MON_TSTAMP9_4_TSTAMP9_4(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PKT_BIST_MON_TSTAMP9_4_TSTAMP9_4                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PKT_BIST_MON_TSTAMP9_4_TSTAMP9_4(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


#endif /* _LAN80XX_MALIBU25G_REGS_PKT_BIST_H_ */
