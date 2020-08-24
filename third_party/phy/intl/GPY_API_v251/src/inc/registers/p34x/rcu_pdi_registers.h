//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p34x/p34x_chip/v_emouchel.priv.p34x_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/chip_control/rcu_pdi_registers_def.xml
// Register File Name  : RCU_PDI_REGISTERS
// Register File Title : Top Level RCU
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _RCU_PDI_REGISTERS_H
#define _RCU_PDI_REGISTERS_H

//! \defgroup RCU_PDI_REGISTERS Register File RCU_PDI_REGISTERS - Top Level RCU
//! @{

//! Base Address of RCU_PDI_REGISTERS
#define RCU_PDI_REGISTERS_MODULE_BASE 0x00D29404u

//! \defgroup RCU_PDI_REGISTERS_RST_REQ Register RCU_PDI_REGISTERS_RST_REQ - Reset Request
//! @{

//! Register Offset (relative)
#define RCU_PDI_REGISTERS_RST_REQ 0x0
//! Register Offset (absolute) for 1st Instance RCU_PDI_REGISTERS
#define RCU_PDI_REGISTERS_RCU_PDI_REGISTERS_RST_REQ 0x00D29404u

//! Register Reset Value
#define RCU_PDI_REGISTERS_RST_REQ_RST 0x00000070u

//! Field MGE1 - Reset MGE
#define RCU_PDI_REGISTERS_RST_REQ_MGE1_POS 0
//! Field MGE1 - Reset MGE
#define RCU_PDI_REGISTERS_RST_REQ_MGE1_MASK 0x1u
//! Constant DISABLED - Disabled
#define CONST_RCU_PDI_REGISTERS_RST_REQ_MGE1_DISABLED 0x0
//! Constant ENABLED - Enabled
#define CONST_RCU_PDI_REGISTERS_RST_REQ_MGE1_ENABLED 0x1

//! Field MGE2 - Reset MGE except registers
#define RCU_PDI_REGISTERS_RST_REQ_MGE2_POS 1
//! Field MGE2 - Reset MGE except registers
#define RCU_PDI_REGISTERS_RST_REQ_MGE2_MASK 0x2u
//! Constant DISABLED - Disabled
#define CONST_RCU_PDI_REGISTERS_RST_REQ_MGE2_DISABLED 0x0
//! Constant ENABLED - Enabled
#define CONST_RCU_PDI_REGISTERS_RST_REQ_MGE2_ENABLED 0x1

//! Field GPIO - Reset Request for GPIO
#define RCU_PDI_REGISTERS_RST_REQ_GPIO_POS 2
//! Field GPIO - Reset Request for GPIO
#define RCU_PDI_REGISTERS_RST_REQ_GPIO_MASK 0x4u
//! Constant DISABLED - Disabled
#define CONST_RCU_PDI_REGISTERS_RST_REQ_GPIO_DISABLED 0x0
//! Constant ENABLED - Enabled
#define CONST_RCU_PDI_REGISTERS_RST_REQ_GPIO_ENABLED 0x1

//! Field SLICE0 - Reset Request to SLICE0
#define RCU_PDI_REGISTERS_RST_REQ_SLICE0_POS 3
//! Field SLICE0 - Reset Request to SLICE0
#define RCU_PDI_REGISTERS_RST_REQ_SLICE0_MASK 0x8u
//! Constant NIL - Nil
#define CONST_RCU_PDI_REGISTERS_RST_REQ_SLICE0_NIL 0x0
//! Constant REQ - REQ
#define CONST_RCU_PDI_REGISTERS_RST_REQ_SLICE0_REQ 0x1

//! Field SLICE1 - Reset Request to SLICE1
#define RCU_PDI_REGISTERS_RST_REQ_SLICE1_POS 4
//! Field SLICE1 - Reset Request to SLICE1
#define RCU_PDI_REGISTERS_RST_REQ_SLICE1_MASK 0x10u
//! Constant NIL - Nil
#define CONST_RCU_PDI_REGISTERS_RST_REQ_SLICE1_NIL 0x0
//! Constant REQ - REQ
#define CONST_RCU_PDI_REGISTERS_RST_REQ_SLICE1_REQ 0x1

//! Field SLICE2 - Reset Request to SLICE2
#define RCU_PDI_REGISTERS_RST_REQ_SLICE2_POS 5
//! Field SLICE2 - Reset Request to SLICE2
#define RCU_PDI_REGISTERS_RST_REQ_SLICE2_MASK 0x20u
//! Constant NIL - Nil
#define CONST_RCU_PDI_REGISTERS_RST_REQ_SLICE2_NIL 0x0
//! Constant REQ - REQ
#define CONST_RCU_PDI_REGISTERS_RST_REQ_SLICE2_REQ 0x1

//! Field SLICE3 - Reset Request to SLICE3
#define RCU_PDI_REGISTERS_RST_REQ_SLICE3_POS 6
//! Field SLICE3 - Reset Request to SLICE3
#define RCU_PDI_REGISTERS_RST_REQ_SLICE3_MASK 0x40u
//! Constant NIL - Nil
#define CONST_RCU_PDI_REGISTERS_RST_REQ_SLICE3_NIL 0x0
//! Constant REQ - REQ
#define CONST_RCU_PDI_REGISTERS_RST_REQ_SLICE3_REQ 0x1

//! Field SRST - Top Level Software Reset
#define RCU_PDI_REGISTERS_RST_REQ_SRST_POS 7
//! Field SRST - Top Level Software Reset
#define RCU_PDI_REGISTERS_RST_REQ_SRST_MASK 0x80u
//! Constant NIL - There is no pending command
#define CONST_RCU_PDI_REGISTERS_RST_REQ_SRST_NIL 0x0
//! Constant REQ - Request
#define CONST_RCU_PDI_REGISTERS_RST_REQ_SRST_REQ 0x1

//! Field USXGMII_XPCS - USXGMII XPCS Reset
#define RCU_PDI_REGISTERS_RST_REQ_USXGMII_XPCS_POS 8
//! Field USXGMII_XPCS - USXGMII XPCS Reset
#define RCU_PDI_REGISTERS_RST_REQ_USXGMII_XPCS_MASK 0x100u
//! Constant NIL - No reset to USXGMII XPCS
#define CONST_RCU_PDI_REGISTERS_RST_REQ_USXGMII_XPCS_NIL 0x0
//! Constant REQ - Reset USXGMII XPCS
#define CONST_RCU_PDI_REGISTERS_RST_REQ_USXGMII_XPCS_REQ 0x1

//! Field USXGMII_PHY - USXGMII PHY only reset
#define RCU_PDI_REGISTERS_RST_REQ_USXGMII_PHY_POS 9
//! Field USXGMII_PHY - USXGMII PHY only reset
#define RCU_PDI_REGISTERS_RST_REQ_USXGMII_PHY_MASK 0x200u
//! Constant NIL - No reset to USXGMII PHY0
#define CONST_RCU_PDI_REGISTERS_RST_REQ_USXGMII_PHY_NIL 0x0
//! Constant REQ - Reset USXGMII PHY0
#define CONST_RCU_PDI_REGISTERS_RST_REQ_USXGMII_PHY_REQ 0x1

//! Field USXGMII_IDDQ - USXGMII IDDQ state
#define RCU_PDI_REGISTERS_RST_REQ_USXGMII_IDDQ_POS 10
//! Field USXGMII_IDDQ - USXGMII IDDQ state
#define RCU_PDI_REGISTERS_RST_REQ_USXGMII_IDDQ_MASK 0x400u
//! Constant NIL - No reset to USXGMII IDDQ
#define CONST_RCU_PDI_REGISTERS_RST_REQ_USXGMII_IDDQ_NIL 0x0
//! Constant REQ - Requests USXGMII to go to IDDQ state
#define CONST_RCU_PDI_REGISTERS_RST_REQ_USXGMII_IDDQ_REQ 0x1

//! Field OTP - OTP reset
#define RCU_PDI_REGISTERS_RST_REQ_OTP_POS 11
//! Field OTP - OTP reset
#define RCU_PDI_REGISTERS_RST_REQ_OTP_MASK 0x800u
//! Constant NIL - No reset to OTP
#define CONST_RCU_PDI_REGISTERS_RST_REQ_OTP_NIL 0x0
//! Constant REQ - Reset OTP
#define CONST_RCU_PDI_REGISTERS_RST_REQ_OTP_REQ 0x1

//! Field LJPLL - LJPLL reset
#define RCU_PDI_REGISTERS_RST_REQ_LJPLL_POS 12
//! Field LJPLL - LJPLL reset
#define RCU_PDI_REGISTERS_RST_REQ_LJPLL_MASK 0x1000u
//! Constant NIL - No reset to LJPLL
#define CONST_RCU_PDI_REGISTERS_RST_REQ_LJPLL_NIL 0x0
//! Constant REQ - Reset LJPLL
#define CONST_RCU_PDI_REGISTERS_RST_REQ_LJPLL_REQ 0x1

//! @}

//! \defgroup RCU_PDI_REGISTERS_RST_REQ2 Register RCU_PDI_REGISTERS_RST_REQ2 - Second reset request Chip RCU register
//! @{

//! Register Offset (relative)
#define RCU_PDI_REGISTERS_RST_REQ2 0x4
//! Register Offset (absolute) for 1st Instance RCU_PDI_REGISTERS
#define RCU_PDI_REGISTERS_RCU_PDI_REGISTERS_RST_REQ2 0x00D29408u

//! Register Reset Value
#define RCU_PDI_REGISTERS_RST_REQ2_RST 0x00000000u

//! Field S0LP - Slice 0 Low Power Reset
#define RCU_PDI_REGISTERS_RST_REQ2_S0LP_POS 0
//! Field S0LP - Slice 0 Low Power Reset
#define RCU_PDI_REGISTERS_RST_REQ2_S0LP_MASK 0x1u
//! Constant NIL - Reset is not active
#define CONST_RCU_PDI_REGISTERS_RST_REQ2_S0LP_NIL 0x0
//! Constant RST - Reset is requested
#define CONST_RCU_PDI_REGISTERS_RST_REQ2_S0LP_RST 0x1

//! Field S0SC - Slice 0 Self-Clearing reset
#define RCU_PDI_REGISTERS_RST_REQ2_S0SC_POS 1
//! Field S0SC - Slice 0 Self-Clearing reset
#define RCU_PDI_REGISTERS_RST_REQ2_S0SC_MASK 0x2u
//! Constant NIL - Reset is not active
#define CONST_RCU_PDI_REGISTERS_RST_REQ2_S0SC_NIL 0x0
//! Constant RST - Reset is requested
#define CONST_RCU_PDI_REGISTERS_RST_REQ2_S0SC_RST 0x1

//! Field S1LP - Slice 1 Low Power reset
#define RCU_PDI_REGISTERS_RST_REQ2_S1LP_POS 2
//! Field S1LP - Slice 1 Low Power reset
#define RCU_PDI_REGISTERS_RST_REQ2_S1LP_MASK 0x4u
//! Constant NIL - Reset is not active
#define CONST_RCU_PDI_REGISTERS_RST_REQ2_S1LP_NIL 0x0
//! Constant RST - Reset is requested
#define CONST_RCU_PDI_REGISTERS_RST_REQ2_S1LP_RST 0x1

//! Field S1SC - Slice 1 GPHY_IP Self-Clearing reset
#define RCU_PDI_REGISTERS_RST_REQ2_S1SC_POS 3
//! Field S1SC - Slice 1 GPHY_IP Self-Clearing reset
#define RCU_PDI_REGISTERS_RST_REQ2_S1SC_MASK 0x8u
//! Constant NIL - Reset is not active
#define CONST_RCU_PDI_REGISTERS_RST_REQ2_S1SC_NIL 0x0
//! Constant RST - Reset is requested
#define CONST_RCU_PDI_REGISTERS_RST_REQ2_S1SC_RST 0x1

//! Field S2LP - Slice 2 Low Power reset
#define RCU_PDI_REGISTERS_RST_REQ2_S2LP_POS 4
//! Field S2LP - Slice 2 Low Power reset
#define RCU_PDI_REGISTERS_RST_REQ2_S2LP_MASK 0x10u
//! Constant NIL - Reset is not active
#define CONST_RCU_PDI_REGISTERS_RST_REQ2_S2LP_NIL 0x0
//! Constant RST - Reset is requested
#define CONST_RCU_PDI_REGISTERS_RST_REQ2_S2LP_RST 0x1

//! Field S2SC - Slice 2 GPHY_IP Self-Clearing reset
#define RCU_PDI_REGISTERS_RST_REQ2_S2SC_POS 5
//! Field S2SC - Slice 2 GPHY_IP Self-Clearing reset
#define RCU_PDI_REGISTERS_RST_REQ2_S2SC_MASK 0x20u
//! Constant NIL - Reset is not active
#define CONST_RCU_PDI_REGISTERS_RST_REQ2_S2SC_NIL 0x0
//! Constant RST - Reset is requested
#define CONST_RCU_PDI_REGISTERS_RST_REQ2_S2SC_RST 0x1

//! Field S3LP - Slice 3 Low Power reset
#define RCU_PDI_REGISTERS_RST_REQ2_S3LP_POS 6
//! Field S3LP - Slice 3 Low Power reset
#define RCU_PDI_REGISTERS_RST_REQ2_S3LP_MASK 0x40u
//! Constant NIL - Reset is not active
#define CONST_RCU_PDI_REGISTERS_RST_REQ2_S3LP_NIL 0x0
//! Constant RST - Reset is requested
#define CONST_RCU_PDI_REGISTERS_RST_REQ2_S3LP_RST 0x1

//! Field S3SC - Slice 3 GPHY_IP Self-Clearing reset
#define RCU_PDI_REGISTERS_RST_REQ2_S3SC_POS 7
//! Field S3SC - Slice 3 GPHY_IP Self-Clearing reset
#define RCU_PDI_REGISTERS_RST_REQ2_S3SC_MASK 0x80u
//! Constant NIL - Reset is not active
#define CONST_RCU_PDI_REGISTERS_RST_REQ2_S3SC_NIL 0x0
//! Constant RST - Reset is requested
#define CONST_RCU_PDI_REGISTERS_RST_REQ2_S3SC_RST 0x1

//! @}

//! \defgroup RCU_PDI_REGISTERS_SPARE1 Register RCU_PDI_REGISTERS_SPARE1 - spare config
//! @{

//! Register Offset (relative)
#define RCU_PDI_REGISTERS_SPARE1 0x8
//! Register Offset (absolute) for 1st Instance RCU_PDI_REGISTERS
#define RCU_PDI_REGISTERS_RCU_PDI_REGISTERS_SPARE1 0x00D2940Cu

//! Register Reset Value
#define RCU_PDI_REGISTERS_SPARE1_RST 0x00000000u

//! Field SPARE - spare config register
#define RCU_PDI_REGISTERS_SPARE1_SPARE_POS 0
//! Field SPARE - spare config register
#define RCU_PDI_REGISTERS_SPARE1_SPARE_MASK 0xFFFFu

//! @}

//! \defgroup RCU_PDI_REGISTERS_DBG0 Register RCU_PDI_REGISTERS_DBG0 - Debug Register
//! @{

//! Register Offset (relative)
#define RCU_PDI_REGISTERS_DBG0 0xC
//! Register Offset (absolute) for 1st Instance RCU_PDI_REGISTERS
#define RCU_PDI_REGISTERS_RCU_PDI_REGISTERS_DBG0 0x00D29410u

//! Register Reset Value
#define RCU_PDI_REGISTERS_DBG0_RST 0x00000000u

//! Field DBG - spare config register
#define RCU_PDI_REGISTERS_DBG0_DBG_POS 0
//! Field DBG - spare config register
#define RCU_PDI_REGISTERS_DBG0_DBG_MASK 0xFFFFu

//! @}

//! \defgroup RCU_PDI_REGISTERS_DBG1 Register RCU_PDI_REGISTERS_DBG1 - Debug Register
//! @{

//! Register Offset (relative)
#define RCU_PDI_REGISTERS_DBG1 0x10
//! Register Offset (absolute) for 1st Instance RCU_PDI_REGISTERS
#define RCU_PDI_REGISTERS_RCU_PDI_REGISTERS_DBG1 0x00D29414u

//! Register Reset Value
#define RCU_PDI_REGISTERS_DBG1_RST 0x00000000u

//! Field DBG - spare config register
#define RCU_PDI_REGISTERS_DBG1_DBG_POS 0
//! Field DBG - spare config register
#define RCU_PDI_REGISTERS_DBG1_DBG_MASK 0xFFFFu

//! @}

//! @}

#endif
