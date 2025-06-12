// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _LAN80XX_MALIBU25G_REGS_HOST_SLICE_H_
#define _LAN80XX_MALIBU25G_REGS_HOST_SLICE_H_

#include "regs_lan8042_common.h"

/***********************************************************************
 *
 * Target: \a HOST_SLICE
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a HOST_SLICE:HOST_SLICE_SOFTWARE_RESET
 *
 * Generate the Reset for the block in slice
 */


/**
 * \brief Host SD25G SerDes Resets
 *
 * \details
 * Host SD25G SerDes Resets
 *
 * Register: \a HOST_SLICE:HOST_SLICE_SOFTWARE_RESET:HOST_SD25G_RESET
 */
#define LAN80XX_HOST_SLICE_HOST_SD25G_RESET     LAN80XX_IOREG(MMD_ID_HOST_SLICE, 0,0x8100)

/**
 * \brief
 * Reset external SD25G interface logic, restore the SD25G register value
 * back to defaults
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_HOST_SLICE_HOST_SD25G_RESET . HOST_SD25G_BASECK_RST
 */
#define  LAN80XX_F_HOST_SLICE_HOST_SD25G_RESET_HOST_SD25G_BASECK_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_SLICE_HOST_SD25G_RESET_HOST_SD25G_BASECK_RST  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_SLICE_HOST_SD25G_RESET_HOST_SD25G_BASECK_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * SD25G fundamental global software reset
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_HOST_SLICE_HOST_SD25G_RESET . HOST_SD25G_MACRO_RST
 */
#define  LAN80XX_F_HOST_SLICE_HOST_SD25G_RESET_HOST_SD25G_MACRO_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_HOST_SLICE_HOST_SD25G_RESET_HOST_SD25G_MACRO_RST  LAN80XX_BIT(2)
#define  LAN80XX_X_HOST_SLICE_HOST_SD25G_RESET_HOST_SD25G_MACRO_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)


/**
 * \brief Host KR IP Resets
 *
 * \details
 * Host KR IP Resets
 *
 * Register: \a HOST_SLICE:HOST_SLICE_SOFTWARE_RESET:HOST_KR_RESET
 */
#define LAN80XX_HOST_SLICE_HOST_KR_RESET        LAN80XX_IOREG(MMD_ID_HOST_SLICE, 0,0x8101)

/**
 * \brief
 * Reset KR ingress logic
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_HOST_SLICE_HOST_KR_RESET . HOST_KR_INGR_RST
 */
#define  LAN80XX_F_HOST_SLICE_HOST_KR_RESET_HOST_KR_INGR_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_SLICE_HOST_KR_RESET_HOST_KR_INGR_RST  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_SLICE_HOST_KR_RESET_HOST_KR_INGR_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Reset KR egress logic
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_HOST_SLICE_HOST_KR_RESET . HOST_KR_EGR_RST
 */
#define  LAN80XX_F_HOST_SLICE_HOST_KR_RESET_HOST_KR_EGR_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_HOST_SLICE_HOST_KR_RESET_HOST_KR_EGR_RST  LAN80XX_BIT(1)
#define  LAN80XX_X_HOST_SLICE_HOST_KR_RESET_HOST_KR_EGR_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)


/**
 * \brief Host PCS1G Resets
 *
 * \details
 * Host PCS1G Resets
 *
 * Register: \a HOST_SLICE:HOST_SLICE_SOFTWARE_RESET:HOST_PCS1G_RESET
 */
#define LAN80XX_HOST_SLICE_HOST_PCS1G_RESET     LAN80XX_IOREG(MMD_ID_HOST_SLICE, 0,0x8102)

/**
 * \brief
 * Reset PCS1G ingress logic
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_HOST_SLICE_HOST_PCS1G_RESET . HOST_PCS1G_INGR_RST
 */
#define  LAN80XX_F_HOST_SLICE_HOST_PCS1G_RESET_HOST_PCS1G_INGR_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_SLICE_HOST_PCS1G_RESET_HOST_PCS1G_INGR_RST  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_SLICE_HOST_PCS1G_RESET_HOST_PCS1G_INGR_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Reset PCS1G egress logic
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_HOST_SLICE_HOST_PCS1G_RESET . HOST_PCS1G_EGR_RST
 */
#define  LAN80XX_F_HOST_SLICE_HOST_PCS1G_RESET_HOST_PCS1G_EGR_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_HOST_SLICE_HOST_PCS1G_RESET_HOST_PCS1G_EGR_RST  LAN80XX_BIT(1)
#define  LAN80XX_X_HOST_SLICE_HOST_PCS1G_RESET_HOST_PCS1G_EGR_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)


/**
 * \brief Host PCS25G Resets
 *
 * \details
 * Host PCS25G Resets
 *
 * Register: \a HOST_SLICE:HOST_SLICE_SOFTWARE_RESET:HOST_PCS25G_RESET
 */
#define LAN80XX_HOST_SLICE_HOST_PCS25G_RESET    LAN80XX_IOREG(MMD_ID_HOST_SLICE, 0,0x8103)

/**
 * \brief
 * Reset PCS25G ingress logic
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_HOST_SLICE_HOST_PCS25G_RESET . HOST_PCS25G_INGR_RST
 */
#define  LAN80XX_F_HOST_SLICE_HOST_PCS25G_RESET_HOST_PCS25G_INGR_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_SLICE_HOST_PCS25G_RESET_HOST_PCS25G_INGR_RST  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_SLICE_HOST_PCS25G_RESET_HOST_PCS25G_INGR_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Reset PCS25G egress logic
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_HOST_SLICE_HOST_PCS25G_RESET . HOST_PCS25G_EGR_RST
 */
#define  LAN80XX_F_HOST_SLICE_HOST_PCS25G_RESET_HOST_PCS25G_EGR_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_HOST_SLICE_HOST_PCS25G_RESET_HOST_PCS25G_EGR_RST  LAN80XX_BIT(1)
#define  LAN80XX_X_HOST_SLICE_HOST_PCS25G_RESET_HOST_PCS25G_EGR_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)


/**
 * \brief Host XC Port Reset
 *
 * \details
 * Host XC Port Reset
 *
 * Register: \a HOST_SLICE:HOST_SLICE_SOFTWARE_RESET:HOST_XC_RESET
 */
#define LAN80XX_HOST_SLICE_HOST_XC_RESET        LAN80XX_IOREG(MMD_ID_HOST_SLICE, 0,0x8104)

/**
 * \brief
 * Reset all four XC FIFO Read Ports toward the Host Port(L2H direction)
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_HOST_SLICE_HOST_XC_RESET . HOST_XC_INGR_RST
 */
#define  LAN80XX_F_HOST_SLICE_HOST_XC_RESET_HOST_XC_INGR_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_SLICE_HOST_XC_RESET_HOST_XC_INGR_RST  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_SLICE_HOST_XC_RESET_HOST_XC_INGR_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XGMII H2L RA_FIFO Egress Reset
 *
 * \details
 * XGMII H2L RA_FIFO Egress Reset
 *
 * Register: \a HOST_SLICE:HOST_SLICE_SOFTWARE_RESET:XGMII_H2L_RA_FIFO_EGR_RST
 */
#define LAN80XX_HOST_SLICE_XGMII_H2L_RA_FIFO_EGR_RST  LAN80XX_IOREG(MMD_ID_HOST_SLICE, 0,0x8105)

/**
 * \brief
 * Reset the Host XGMII H2L RA FIFO
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_HOST_SLICE_XGMII_H2L_RA_FIFO_EGR_RST . XGMII_H2L_RA_FIFO_EGR_RST
 */
#define  LAN80XX_F_HOST_SLICE_XGMII_H2L_RA_FIFO_EGR_RST_XGMII_H2L_RA_FIFO_EGR_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_SLICE_XGMII_H2L_RA_FIFO_EGR_RST_XGMII_H2L_RA_FIFO_EGR_RST  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_SLICE_XGMII_H2L_RA_FIFO_EGR_RST_XGMII_H2L_RA_FIFO_EGR_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a HOST_SLICE:HOST_PMA_PCS_LPBK
 *
 * Loopback at PMA and PCS
 */


/**
 * \brief Loopback at interface of PCS with PMA
 *
 * \details
 * Register: \a HOST_SLICE:HOST_PMA_PCS_LPBK:L2_LPBK
 */
#define LAN80XX_HOST_SLICE_L2_LPBK              LAN80XX_IOREG(MMD_ID_HOST_SLICE, 0, 0x8106)

/**
 * \brief
 * Malibu-25G L2 Loopback.Loops Host PCS/FEC Tx data back toward Malibu-25G
 * core. This loopback works for all port speeds, both PCS and MAC Retimer
 * modes. Blocking/Forwarding behavior toward the Host SerDes is configured
 * using L2_LPBK_FW_SEL.
 *
 * \details
 * 0: Disable Loopback
 * 1: Enable Loopback
 *
 * Field: ::LAN80XX_HOST_SLICE_L2_LPBK . L2_LPBK
 */
#define  LAN80XX_F_HOST_SLICE_L2_LPBK_L2_LPBK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_SLICE_L2_LPBK_L2_LPBK     LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_SLICE_L2_LPBK_L2_LPBK(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Configures blocking/forwarding behavior for the L2 loopback.
 *
 * \details
 * 00: Forward looped data to the Host SerDes
 * 01: Send 0x0000 data to the Host SerDes
 * 10: Send 0x00FF data to the Host Serdes
 * 11: Reserved
 *
 * Field: ::LAN80XX_HOST_SLICE_L2_LPBK . L2_LPBK_FW_SEL
 */
#define  LAN80XX_F_HOST_SLICE_L2_LPBK_L2_LPBK_FW_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,4,2)
#define  LAN80XX_M_HOST_SLICE_L2_LPBK_L2_LPBK_FW_SEL     LAN80XX_ENCODE_BITMASK(4,2)
#define  LAN80XX_X_HOST_SLICE_L2_LPBK_L2_LPBK_FW_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,4,2)


/**
 * \brief Loopback at PCS XGMII interface
 *
 * \details
 * Register: \a HOST_SLICE:HOST_PMA_PCS_LPBK:L3P_LPBK
 */
#define LAN80XX_HOST_SLICE_L3P_LPBK             LAN80XX_IOREG(MMD_ID_HOST_SLICE, 0,0x8107)

/**
 * \brief
 * Malibu-25G L3P Loopback. Loops Host PCS Tx XGMII arrival data back
 * toward Malibu-25G core. This loopback works for all port speeds, both
 * PCS and MAC Retimer modes. Blocking/Forwarding behavior toward the Host
 * PCS is configured using L3P_LPBK_FW_SEL.
 *
 * \details
 * 0: Disable Loopback
 * 1: Enable Loopback
 *
 * Field: ::LAN80XX_HOST_SLICE_L3P_LPBK . L3P_LPBK
 */
#define  LAN80XX_F_HOST_SLICE_L3P_LPBK_L3P_LPBK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_SLICE_L3P_LPBK_L3P_LPBK  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_SLICE_L3P_LPBK_L3P_LPBK(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Configures blocking/forwarding behavior for the L3P loopback.
 *
 * \details
 * 0: Forward looped XGMII data to the Host PCS
 * 1: Send XGMII Idles to the Host PCS
 *
 * Field: ::LAN80XX_HOST_SLICE_L3P_LPBK . L3P_LPBK_FW_SEL
 */
#define  LAN80XX_F_HOST_SLICE_L3P_LPBK_L3P_LPBK_FW_SEL(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_SLICE_L3P_LPBK_L3P_LPBK_FW_SEL  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_SLICE_L3P_LPBK_L3P_LPBK_FW_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * Register Group: \a HOST_SLICE:SERDES_LOS
 *
 * SERDES_Los Indicator
 */


/**
 * \brief Serdes Loss of Signal
 *
 * \details
 * Register: \a HOST_SLICE:SERDES_LOS:SERDES_LOS
 */
#define LAN80XX_HOST_SLICE_SERDES_LOS           LAN80XX_IOREG(MMD_ID_HOST_SLICE, 0,0x8108)

/**
 * \brief
 * Indication that Serdes has loss of signal fault from
 * pma2pcs_rei_filtered
 *
 * \details
 * Field: ::LAN80XX_HOST_SLICE_SERDES_LOS . LOS
 */
#define  LAN80XX_F_HOST_SLICE_SERDES_LOS_LOS(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_SLICE_SERDES_LOS_LOS     LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_SLICE_SERDES_LOS_LOS(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 *  Enable sent SD25G Serdes LOS to PCS
 *
 * \details
 * 0: Serdes LOS is disabled
 * 1: Serdes LOS is enabled
 *
 * Field: ::LAN80XX_HOST_SLICE_SERDES_LOS . SD25G_LOS_EN
 */
#define  LAN80XX_F_HOST_SLICE_SERDES_LOS_SD25G_LOS_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_SLICE_SERDES_LOS_SD25G_LOS_EN  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_SLICE_SERDES_LOS_SD25G_LOS_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 *  Invert SD25G Serdes LOS to PCS
 *
 * \details
 * 0: Serdes LOS is normal
 * 1: Serdes LOS is inverted
 *
 * Field: ::LAN80XX_HOST_SLICE_SERDES_LOS . SD25G_LOS_INV
 */
#define  LAN80XX_F_HOST_SLICE_SERDES_LOS_SD25G_LOS_INV(x)  LAN80XX_ENCODE_BITFIELD(!!(x),5,1)
#define  LAN80XX_M_HOST_SLICE_SERDES_LOS_SD25G_LOS_INV  LAN80XX_BIT(5)
#define  LAN80XX_X_HOST_SLICE_SERDES_LOS_SD25G_LOS_INV(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 *  Enable sent MOD Module LOS to PCS
 *
 * \details
 * 0: Module LOS is disabled
 * 1: Module LOS is enabled
 *
 * Field: ::LAN80XX_HOST_SLICE_SERDES_LOS . MOD_LOS_EN
 */
#define  LAN80XX_F_HOST_SLICE_SERDES_LOS_MOD_LOS_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),6,1)
#define  LAN80XX_M_HOST_SLICE_SERDES_LOS_MOD_LOS_EN  LAN80XX_BIT(6)
#define  LAN80XX_X_HOST_SLICE_SERDES_LOS_MOD_LOS_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 *  Invert Module  LOS to PCS
 *
 * \details
 * 0: Module LOS is normal
 * 1: Serdes LOS is Module
 *
 * Field: ::LAN80XX_HOST_SLICE_SERDES_LOS . MOD_LOS_INV
 */
#define  LAN80XX_F_HOST_SLICE_SERDES_LOS_MOD_LOS_INV(x)  LAN80XX_ENCODE_BITFIELD(!!(x),7,1)
#define  LAN80XX_M_HOST_SLICE_SERDES_LOS_MOD_LOS_INV  LAN80XX_BIT(7)
#define  LAN80XX_X_HOST_SLICE_SERDES_LOS_MOD_LOS_INV(x)  LAN80XX_EXTRACT_BITFIELD(x,7,1)

/**
 * Register Group: \a HOST_SLICE:PKTBIST_DATAPATH_CONTROL
 *
 * PKTBIST_DATAPATH_CONTROL
 */


/**
 * \brief Datapath Control
 *
 * \details
 * Register: \a HOST_SLICE:PKTBIST_DATAPATH_CONTROL:DATAPATH_CONTROL
 */
#define LAN80XX_HOST_SLICE_DATAPATH_CONTROL     LAN80XX_IOREG(MMD_ID_HOST_SLICE, 0, 0x8109)

/**
 * \brief
 * Selects source of data transmitted from PCS to MAC core in the H2L
 * direction
 *
 * \details
 * 0: Data is from Host PCS
 * 1: Data is from Pattern Generator
 *
 * Field: ::LAN80XX_HOST_SLICE_DATAPATH_CONTROL . EGR_XGMII_PG_SEL
 */
#define  LAN80XX_F_HOST_SLICE_DATAPATH_CONTROL_EGR_XGMII_PG_SEL(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_HOST_SLICE_DATAPATH_CONTROL_EGR_XGMII_PG_SEL  LAN80XX_BIT(8)
#define  LAN80XX_X_HOST_SLICE_DATAPATH_CONTROL_EGR_XGMII_PG_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Selects source of data transmitted from MAC core to PCS in the L2H
 * direction
 *
 * \details
 * 0: Data is from MAC core in the ingress data path
 * 1: Data is from Pattern Generator
 *
 * Field: ::LAN80XX_HOST_SLICE_DATAPATH_CONTROL . IGR_XGMII_PG_SEL
 */
#define  LAN80XX_F_HOST_SLICE_DATAPATH_CONTROL_IGR_XGMII_PG_SEL(x)  LAN80XX_ENCODE_BITFIELD(!!(x),7,1)
#define  LAN80XX_M_HOST_SLICE_DATAPATH_CONTROL_IGR_XGMII_PG_SEL  LAN80XX_BIT(7)
#define  LAN80XX_X_HOST_SLICE_DATAPATH_CONTROL_IGR_XGMII_PG_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Malibu-25G H7 Loopback. Selects source of data transmitted from MAC core
 * or Egress PCS receive data
 *
 * \details
 * 0: Data is from ingress MAC core
 * 1: Data is looped from Egress PCS receive data in the egress data path
 *
 * Field: ::LAN80XX_HOST_SLICE_DATAPATH_CONTROL . IGR_XGMII_PG_SEL2
 */
#define  LAN80XX_F_HOST_SLICE_DATAPATH_CONTROL_IGR_XGMII_PG_SEL2(x)  LAN80XX_ENCODE_BITFIELD(!!(x),6,1)
#define  LAN80XX_M_HOST_SLICE_DATAPATH_CONTROL_IGR_XGMII_PG_SEL2  LAN80XX_BIT(6)
#define  LAN80XX_X_HOST_SLICE_DATAPATH_CONTROL_IGR_XGMII_PG_SEL2(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)

/**
 * Register Group: \a HOST_SLICE:SPARE
 *
 * Spare Registers
 */


/**
 * \brief Spare Read writeable register 0
 *
 * \details
 * Register: \a HOST_SLICE:SPARE:SPARE_RW_0
 */
#define LAN80XX_HOST_SLICE_SPARE_RW_0           LAN80XX_IOREG(MMD_ID_HOST_SLICE, 0,0x8110)

/**
 * \brief
 * Spare read writeable register CHANNEL ID
 * This Register will be configured through OTP
 *
 * \details
 * Field: ::LAN80XX_HOST_SLICE_SPARE_RW_0 . SPARE_RW_0_CHN_ID
 */
#define  LAN80XX_F_HOST_SLICE_SPARE_RW_0_SPARE_RW_0_CHN_ID(x)  LAN80XX_ENCODE_BITFIELD(x,2,2)
#define  LAN80XX_M_HOST_SLICE_SPARE_RW_0_SPARE_RW_0_CHN_ID     LAN80XX_ENCODE_BITMASK(2,2)
#define  LAN80XX_X_HOST_SLICE_SPARE_RW_0_SPARE_RW_0_CHN_ID(x)  LAN80XX_EXTRACT_BITFIELD(x,2,2)


/**
 * \brief
 * Spare read writeable register 0
 *
 * \details
 * Field: ::LAN80XX_HOST_SLICE_SPARE_RW_0 . SPARE_RW_0
 */
#define  LAN80XX_F_HOST_SLICE_SPARE_RW_0_SPARE_RW_0(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_SLICE_SPARE_RW_0_SPARE_RW_0     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_SLICE_SPARE_RW_0_SPARE_RW_0(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Spare Read writeable register 1
 *
 * \details
 * Register: \a HOST_SLICE:SPARE:SPARE_RW_1
 */
#define LAN80XX_HOST_SLICE_SPARE_RW_1           LAN80XX_IOREG(MMD_ID_HOST_SLICE, 0,0x8111)

/**
 * \brief
 * Spare read writeable register 1
 *
 * \details
 * Field: ::LAN80XX_HOST_SLICE_SPARE_RW_1 . SPARE_RW_1
 */
#define  LAN80XX_F_HOST_SLICE_SPARE_RW_1_SPARE_RW_1(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_SLICE_SPARE_RW_1_SPARE_RW_1     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_SLICE_SPARE_RW_1_SPARE_RW_1(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Spare Read writeable register 2
 *
 * \details
 * Register: \a HOST_SLICE:SPARE:SPARE_RW_2
 */
#define LAN80XX_HOST_SLICE_SPARE_RW_2           LAN80XX_IOREG(MMD_ID_HOST_SLICE, 0,0x8112)

/**
 * \brief
 * Spare read writeable register 2
 *
 * \details
 * Field: ::LAN80XX_HOST_SLICE_SPARE_RW_2 . SPARE_RW_2
 */
#define  LAN80XX_F_HOST_SLICE_SPARE_RW_2_SPARE_RW_2(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_SLICE_SPARE_RW_2_SPARE_RW_2     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_SLICE_SPARE_RW_2_SPARE_RW_2(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Spare Read writeable register 3
 *
 * \details
 * Register: \a HOST_SLICE:SPARE:SPARE_RW_3
 */
#define LAN80XX_HOST_SLICE_SPARE_RW_3           LAN80XX_IOREG(MMD_ID_HOST_SLICE, 0,0x8113)

/**
 * \brief
 * Spare read writeable register 3
 *
 * \details
 * Field: ::LAN80XX_HOST_SLICE_SPARE_RW_3 . SPARE_RW_3
 */
#define  LAN80XX_F_HOST_SLICE_SPARE_RW_3_SPARE_RW_3(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_SLICE_SPARE_RW_3_SPARE_RW_3     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_SLICE_SPARE_RW_3_SPARE_RW_3(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Spare Read only register 0
 *
 * \details
 * Register: \a HOST_SLICE:SPARE:SPARE_RO_0
 */
#define LAN80XX_HOST_SLICE_SPARE_RO_0           LAN80XX_IOREG(MMD_ID_HOST_SLICE, 0,0x8114)

/**
 * \brief
 * Spare read only register 0
 *
 * \details
 * Field: ::LAN80XX_HOST_SLICE_SPARE_RO_0 . SPARE_RO_0
 */
#define  LAN80XX_F_HOST_SLICE_SPARE_RO_0_SPARE_RO_0(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_SLICE_SPARE_RO_0_SPARE_RO_0     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_SLICE_SPARE_RO_0_SPARE_RO_0(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Spare Read only register 1
 *
 * \details
 * Register: \a HOST_SLICE:SPARE:SPARE_RO_1
 */
#define LAN80XX_HOST_SLICE_SPARE_RO_1           LAN80XX_IOREG(MMD_ID_HOST_SLICE, 0,0x8115)

/**
 * \brief
 * Spare read only register 1
 *
 * \details
 * Field: ::LAN80XX_HOST_SLICE_SPARE_RO_1 . SPARE_RO_1
 */
#define  LAN80XX_F_HOST_SLICE_SPARE_RO_1_SPARE_RO_1(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_SLICE_SPARE_RO_1_SPARE_RO_1     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_SLICE_SPARE_RO_1_SPARE_RO_1(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


#endif /* _LAN80XX_MALIBU25G_REGS_HOST_SLICE_H_ */
