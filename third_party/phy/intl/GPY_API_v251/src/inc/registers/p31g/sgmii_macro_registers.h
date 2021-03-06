/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/sgmii_macro_registers_def.xml
// Register File Name  : SGMII_MACRO_REGISTERS
// Register File Title : SGMII_MACRO Registers
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _SGMII_MACRO_REGISTERS_H
#define _SGMII_MACRO_REGISTERS_H

//! \defgroup SGMII_MACRO_REGISTERS Register File SGMII_MACRO_REGISTERS - SGMII_MACRO Registers
//! @{

//! Base Address of SGMII_MACRO_REGISTERS
#define SGMII_MACRO_REGISTERS_MODULE_BASE 0x00D34800u

//! \defgroup SGMII_MACRO_RESETN Register SGMII_MACRO_RESETN - SGMII Macro reset control
//! @{

//! Register Offset (relative)
#define SGMII_MACRO_RESETN 0x0
//! Register Offset (absolute) for 1st Instance SGMII_MACRO_REGISTERS
#define SGMII_MACRO_REGISTERS_SGMII_MACRO_RESETN 0x00D34800u

//! Register Reset Value
#define SGMII_MACRO_RESETN_RST 0x00000003u

//! Field SGMII_PHY_RESETN - SGMII_PHY_RESETN
#define SGMII_MACRO_RESETN_SGMII_PHY_RESETN_POS 0
//! Field SGMII_PHY_RESETN - SGMII_PHY_RESETN
#define SGMII_MACRO_RESETN_SGMII_PHY_RESETN_MASK 0x1u
//! Constant RESET - RESET
#define CONST_SGMII_MACRO_RESETN_SGMII_PHY_RESETN_RESET 0x0
//! Constant NOT_RESET - NO_RESET
#define CONST_SGMII_MACRO_RESETN_SGMII_PHY_RESETN_NOT_RESET 0x1

//! Field SGMII_PCS_RESETN - SGMII_PCS_RESETN
#define SGMII_MACRO_RESETN_SGMII_PCS_RESETN_POS 1
//! Field SGMII_PCS_RESETN - SGMII_PCS_RESETN
#define SGMII_MACRO_RESETN_SGMII_PCS_RESETN_MASK 0x2u
//! Constant RESET - RESET
#define CONST_SGMII_MACRO_RESETN_SGMII_PCS_RESETN_RESET 0x0
//! Constant NOT_RESET - NO_RESET
#define CONST_SGMII_MACRO_RESETN_SGMII_PCS_RESETN_NOT_RESET 0x1

//! @}

//! \defgroup SGMII_MACRO_QSGMII_CTRL1 Register SGMII_MACRO_QSGMII_CTRL1 - SGMII Macro QSGMII CTRL1
//! @{

//! Register Offset (relative)
#define SGMII_MACRO_QSGMII_CTRL1 0x4
//! Register Offset (absolute) for 1st Instance SGMII_MACRO_REGISTERS
#define SGMII_MACRO_REGISTERS_SGMII_MACRO_QSGMII_CTRL1 0x00D34804u

//! Register Reset Value
#define SGMII_MACRO_QSGMII_CTRL1_RST 0x0000020Cu

//! Field QSGMII_SEL - qsgmii_sel
#define SGMII_MACRO_QSGMII_CTRL1_QSGMII_SEL_POS 0
//! Field QSGMII_SEL - qsgmii_sel
#define SGMII_MACRO_QSGMII_CTRL1_QSGMII_SEL_MASK 0x1u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_MACRO_QSGMII_CTRL1_QSGMII_SEL_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_MACRO_QSGMII_CTRL1_QSGMII_SEL_ENABLE 0x1

//! Field PSGMII_SEL - psgmii_sel
#define SGMII_MACRO_QSGMII_CTRL1_PSGMII_SEL_POS 1
//! Field PSGMII_SEL - psgmii_sel
#define SGMII_MACRO_QSGMII_CTRL1_PSGMII_SEL_MASK 0x2u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_MACRO_QSGMII_CTRL1_PSGMII_SEL_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_MACRO_QSGMII_CTRL1_PSGMII_SEL_ENABLE 0x1

//! Field TX_RD_INITN - tx_rd_initn
#define SGMII_MACRO_QSGMII_CTRL1_TX_RD_INITN_POS 2
//! Field TX_RD_INITN - tx_rd_initn
#define SGMII_MACRO_QSGMII_CTRL1_TX_RD_INITN_MASK 0x4u
//! Constant INIT0 - INIT0
#define CONST_SGMII_MACRO_QSGMII_CTRL1_TX_RD_INITN_INIT0 0x0
//! Constant INIT1 - INIT1
#define CONST_SGMII_MACRO_QSGMII_CTRL1_TX_RD_INITN_INIT1 0x1

//! Field RX_RD_INITN - rx_rd_initn
#define SGMII_MACRO_QSGMII_CTRL1_RX_RD_INITN_POS 3
//! Field RX_RD_INITN - rx_rd_initn
#define SGMII_MACRO_QSGMII_CTRL1_RX_RD_INITN_MASK 0x8u
//! Constant INIT0 - INIT0
#define CONST_SGMII_MACRO_QSGMII_CTRL1_RX_RD_INITN_INIT0 0x0
//! Constant INIT1 - INIT1
#define CONST_SGMII_MACRO_QSGMII_CTRL1_RX_RD_INITN_INIT1 0x1

//! Field DISPAR_EN - dispar_en
#define SGMII_MACRO_QSGMII_CTRL1_DISPAR_EN_POS 4
//! Field DISPAR_EN - dispar_en
#define SGMII_MACRO_QSGMII_CTRL1_DISPAR_EN_MASK 0x10u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_MACRO_QSGMII_CTRL1_DISPAR_EN_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_MACRO_QSGMII_CTRL1_DISPAR_EN_ENABLE 0x1

//! Field Q_JITE - q_jite
#define SGMII_MACRO_QSGMII_CTRL1_Q_JITE_POS 5
//! Field Q_JITE - q_jite
#define SGMII_MACRO_QSGMII_CTRL1_Q_JITE_MASK 0x60u
//! Constant NO - Normal Function
#define CONST_SGMII_MACRO_QSGMII_CTRL1_Q_JITE_NO 0x0
//! Constant HIGH - Transmit High Frequency test pattern 36A.1
#define CONST_SGMII_MACRO_QSGMII_CTRL1_Q_JITE_HIGH 0x1
//! Constant LOW - Transmit Low Frequency test pattern 36A.2
#define CONST_SGMII_MACRO_QSGMII_CTRL1_Q_JITE_LOW 0x2
//! Constant MIXED - Transmit Mixed Frequency test pattern 36A.3
#define CONST_SGMII_MACRO_QSGMII_CTRL1_Q_JITE_MIXED 0x3

//! Field Q_RVBI - q_rvbi
#define SGMII_MACRO_QSGMII_CTRL1_Q_RVBI_POS 7
//! Field Q_RVBI - q_rvbi
#define SGMII_MACRO_QSGMII_CTRL1_Q_RVBI_MASK 0x80u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_MACRO_QSGMII_CTRL1_Q_RVBI_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_MACRO_QSGMII_CTRL1_Q_RVBI_ENABLE 0x1

//! Field Q_RVBO - q_rvbo
#define SGMII_MACRO_QSGMII_CTRL1_Q_RVBO_POS 8
//! Field Q_RVBO - q_rvbo
#define SGMII_MACRO_QSGMII_CTRL1_Q_RVBO_MASK 0x100u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_MACRO_QSGMII_CTRL1_Q_RVBO_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_MACRO_QSGMII_CTRL1_Q_RVBO_ENABLE 0x1

//! Field QSGMII_HW_OVERD - psgmii_hw_ovrd
#define SGMII_MACRO_QSGMII_CTRL1_QSGMII_HW_OVERD_POS 9
//! Field QSGMII_HW_OVERD - psgmii_hw_ovrd
#define SGMII_MACRO_QSGMII_CTRL1_QSGMII_HW_OVERD_MASK 0x200u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_MACRO_QSGMII_CTRL1_QSGMII_HW_OVERD_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_MACRO_QSGMII_CTRL1_QSGMII_HW_OVERD_ENABLE 0x1

//! Field LPI_MODE_ACTIVE - lpi_mode_active
#define SGMII_MACRO_QSGMII_CTRL1_LPI_MODE_ACTIVE_POS 10
//! Field LPI_MODE_ACTIVE - lpi_mode_active
#define SGMII_MACRO_QSGMII_CTRL1_LPI_MODE_ACTIVE_MASK 0x400u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_MACRO_QSGMII_CTRL1_LPI_MODE_ACTIVE_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_MACRO_QSGMII_CTRL1_LPI_MODE_ACTIVE_ENABLE 0x1

//! Field LOS_PCS_DIS - los_pcs_dis
#define SGMII_MACRO_QSGMII_CTRL1_LOS_PCS_DIS_POS 11
//! Field LOS_PCS_DIS - los_pcs_dis
#define SGMII_MACRO_QSGMII_CTRL1_LOS_PCS_DIS_MASK 0x800u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_MACRO_QSGMII_CTRL1_LOS_PCS_DIS_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_MACRO_QSGMII_CTRL1_LOS_PCS_DIS_ENABLE 0x1

//! @}

//! \defgroup SGMII_MACRO_CLK_CTRL Register SGMII_MACRO_CLK_CTRL - SGMII macro clock control
//! @{

//! Register Offset (relative)
#define SGMII_MACRO_CLK_CTRL 0x3C
//! Register Offset (absolute) for 1st Instance SGMII_MACRO_REGISTERS
#define SGMII_MACRO_REGISTERS_SGMII_MACRO_CLK_CTRL 0x00D3483Cu

//! Register Reset Value
#define SGMII_MACRO_CLK_CTRL_RST 0x00001111u

//! Field XAUI_PHY_TX_CLK_EN - PMD/PMA Core's txclk enable
#define SGMII_MACRO_CLK_CTRL_XAUI_PHY_TX_CLK_EN_POS 0
//! Field XAUI_PHY_TX_CLK_EN - PMD/PMA Core's txclk enable
#define SGMII_MACRO_CLK_CTRL_XAUI_PHY_TX_CLK_EN_MASK 0x1u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_MACRO_CLK_CTRL_XAUI_PHY_TX_CLK_EN_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_MACRO_CLK_CTRL_XAUI_PHY_TX_CLK_EN_ENABLE 0x1

//! Field XAUI_PHY_RX_CLK_EN - PMD/PMA Core's Rxclk enable
#define SGMII_MACRO_CLK_CTRL_XAUI_PHY_RX_CLK_EN_POS 4
//! Field XAUI_PHY_RX_CLK_EN - PMD/PMA Core's Rxclk enable
#define SGMII_MACRO_CLK_CTRL_XAUI_PHY_RX_CLK_EN_MASK 0x10u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_MACRO_CLK_CTRL_XAUI_PHY_RX_CLK_EN_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_MACRO_CLK_CTRL_XAUI_PHY_RX_CLK_EN_ENABLE 0x1

//! Field GMII_TXCLK_EN - GMII Txclk enable
#define SGMII_MACRO_CLK_CTRL_GMII_TXCLK_EN_POS 8
//! Field GMII_TXCLK_EN - GMII Txclk enable
#define SGMII_MACRO_CLK_CTRL_GMII_TXCLK_EN_MASK 0x100u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_MACRO_CLK_CTRL_GMII_TXCLK_EN_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_MACRO_CLK_CTRL_GMII_TXCLK_EN_ENABLE 0x1

//! Field GMII_RXCLK_EN - GMII Rxclk enable
#define SGMII_MACRO_CLK_CTRL_GMII_RXCLK_EN_POS 12
//! Field GMII_RXCLK_EN - GMII Rxclk enable
#define SGMII_MACRO_CLK_CTRL_GMII_RXCLK_EN_MASK 0x1000u
//! Constant DISABLE - DISABLE
#define CONST_SGMII_MACRO_CLK_CTRL_GMII_RXCLK_EN_DISABLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_SGMII_MACRO_CLK_CTRL_GMII_RXCLK_EN_ENABLE 0x1

//! @}

//! \defgroup SGMII_MACRO_DBG Register SGMII_MACRO_DBG - SGMII macro clock control
//! @{

//! Register Offset (relative)
#define SGMII_MACRO_DBG 0x40
//! Register Offset (absolute) for 1st Instance SGMII_MACRO_REGISTERS
#define SGMII_MACRO_REGISTERS_SGMII_MACRO_DBG 0x00D34840u

//! Register Reset Value
#define SGMII_MACRO_DBG_RST 0x00000000u

//! Field K_DET_DONE - k_det_done
#define SGMII_MACRO_DBG_K_DET_DONE_POS 0
//! Field K_DET_DONE - k_det_done
#define SGMII_MACRO_DBG_K_DET_DONE_MASK 0x1u

//! Field K28_1_REALIGN - k28_1_realign
#define SGMII_MACRO_DBG_K28_1_REALIGN_POS 1
//! Field K28_1_REALIGN - k28_1_realign
#define SGMII_MACRO_DBG_K28_1_REALIGN_MASK 0x2u

//! @}

//! @}

#endif
