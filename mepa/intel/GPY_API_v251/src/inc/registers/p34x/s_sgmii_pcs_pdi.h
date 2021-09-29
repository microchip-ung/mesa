//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p34x/p34x_chip/v_emouchel.priv.p34x_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/slice_sgmii/s_sgmii_pcs_pdi_def.xml
// Register File Name  : S_SGMII_PCS_PDI
// Register File Title : SGMII PCS PDI Register File
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _S_SGMII_PCS_PDI_H
#define _S_SGMII_PCS_PDI_H

//! \defgroup S_SGMII_PCS_PDI Register File S_SGMII_PCS_PDI - SGMII PCS PDI Register File
//! @{

//! Base Address of S_SGMII_PCS_PDI
#define S_SGMII_PCS_PDI_MODULE_BASE 0x00A35000u

//! \defgroup S_SGMII_PCS_PDI_CFG Register S_SGMII_PCS_PDI_CFG - Configuration Register
//! @{

//! Register Offset (relative)
#define S_SGMII_PCS_PDI_CFG 0x0
//! Register Offset (absolute) for 1st Instance S_SGMII_PCS_PDI
#define S_SGMII_PCS_PDI_S_SGMII_PCS_PDI_CFG 0x00A35000u

//! Register Reset Value
#define S_SGMII_PCS_PDI_CFG_RST 0x00000000u

//! Field LPB - Loop Back RX to TX PATH
#define S_SGMII_PCS_PDI_CFG_LPB_POS 0
//! Field LPB - Loop Back RX to TX PATH
#define S_SGMII_PCS_PDI_CFG_LPB_MASK 0x1u
//! Constant NORMAL - Normal Operation TX
#define CONST_S_SGMII_PCS_PDI_CFG_LPB_NORMAL 0x0
//! Constant LOOP - Loop Back RX to TX Path
#define CONST_S_SGMII_PCS_PDI_CFG_LPB_LOOP 0x1

//! Field INITRX - INIT SGMII RX PATH
#define S_SGMII_PCS_PDI_CFG_INITRX_POS 1
//! Field INITRX - INIT SGMII RX PATH
#define S_SGMII_PCS_PDI_CFG_INITRX_MASK 0x2u
//! Constant NORMAL - Normal Operation TX
#define CONST_S_SGMII_PCS_PDI_CFG_INITRX_NORMAL 0x0
//! Constant INIT - Reset RX Path
#define CONST_S_SGMII_PCS_PDI_CFG_INITRX_INIT 0x1

//! Field INITTX - INIT SGMII TX PATH
#define S_SGMII_PCS_PDI_CFG_INITTX_POS 2
//! Field INITTX - INIT SGMII TX PATH
#define S_SGMII_PCS_PDI_CFG_INITTX_MASK 0x4u
//! Constant NORMAL - Normal Operation TX
#define CONST_S_SGMII_PCS_PDI_CFG_INITTX_NORMAL 0x0
//! Constant INIT - Reset TX Path
#define CONST_S_SGMII_PCS_PDI_CFG_INITTX_INIT 0x1

//! Field RTE_EN - RTE Enable
#define S_SGMII_PCS_PDI_CFG_RTE_EN_POS 3
//! Field RTE_EN - RTE Enable
#define S_SGMII_PCS_PDI_CFG_RTE_EN_MASK 0x8u
//! Constant DISABLE - Disable RTE
#define CONST_S_SGMII_PCS_PDI_CFG_RTE_EN_DISABLE 0x0
//! Constant ENABLE - Enable RTE
#define CONST_S_SGMII_PCS_PDI_CFG_RTE_EN_ENABLE 0x1

//! @}

//! \defgroup S_SGMII_PCS_PDI_RXB_CTL Register S_SGMII_PCS_PDI_RXB_CTL - Receive Buffer Control Register
//! @{

//! Register Offset (relative)
#define S_SGMII_PCS_PDI_RXB_CTL 0x4
//! Register Offset (absolute) for 1st Instance S_SGMII_PCS_PDI
#define S_SGMII_PCS_PDI_S_SGMII_PCS_PDI_RXB_CTL 0x00A35004u

//! Register Reset Value
#define S_SGMII_PCS_PDI_RXB_CTL_RST 0x00000001u

//! Field ENAB_RXB - Enable RX Buffer
#define S_SGMII_PCS_PDI_RXB_CTL_ENAB_RXB_POS 0
//! Field ENAB_RXB - Enable RX Buffer
#define S_SGMII_PCS_PDI_RXB_CTL_ENAB_RXB_MASK 0x1u
//! Constant DISABLE - RX Buffer is disabled
#define CONST_S_SGMII_PCS_PDI_RXB_CTL_ENAB_RXB_DISABLE 0x0
//! Constant ENABLE - RX Buffer is enabled
#define CONST_S_SGMII_PCS_PDI_RXB_CTL_ENAB_RXB_ENABLE 0x1

//! Field INIT_RX_RXB - Initialize RX Buffer
#define S_SGMII_PCS_PDI_RXB_CTL_INIT_RX_RXB_POS 1
//! Field INIT_RX_RXB - Initialize RX Buffer
#define S_SGMII_PCS_PDI_RXB_CTL_INIT_RX_RXB_MASK 0x2u
//! Constant NORMAL - RX Buffer and pointers are normally operating
#define CONST_S_SGMII_PCS_PDI_RXB_CTL_INIT_RX_RXB_NORMAL 0x0
//! Constant ACTIVE - RX Buffer and pointers are initialized
#define CONST_S_SGMII_PCS_PDI_RXB_CTL_INIT_RX_RXB_ACTIVE 0x1

//! Field SIPG_FILT - Elongate short IPGs
#define S_SGMII_PCS_PDI_RXB_CTL_SIPG_FILT_POS 2
//! Field SIPG_FILT - Elongate short IPGs
#define S_SGMII_PCS_PDI_RXB_CTL_SIPG_FILT_MASK 0x4u
//! Constant FILT_ON - IPGs from bridge are lengthened to at least 3 cycles
#define CONST_S_SGMII_PCS_PDI_RXB_CTL_SIPG_FILT_FILT_ON 0x0
//! Constant FILT_OFF - IPGs from bridge passed to buffer without change
#define CONST_S_SGMII_PCS_PDI_RXB_CTL_SIPG_FILT_FILT_OFF 0x1

//! @}

//! \defgroup S_SGMII_PCS_PDI_RXB_CFG Register S_SGMII_PCS_PDI_RXB_CFG - Receive Buffer Configuration Register
//! @{

//! Register Offset (relative)
#define S_SGMII_PCS_PDI_RXB_CFG 0x8
//! Register Offset (absolute) for 1st Instance S_SGMII_PCS_PDI
#define S_SGMII_PCS_PDI_S_SGMII_PCS_PDI_RXB_CFG 0x00A35008u

//! Register Reset Value
#define S_SGMII_PCS_PDI_RXB_CFG_RST 0x00000040u

//! Field DLY_WP_RXB - Delay
#define S_SGMII_PCS_PDI_RXB_CFG_DLY_WP_RXB_POS 0
//! Field DLY_WP_RXB - Delay
#define S_SGMII_PCS_PDI_RXB_CFG_DLY_WP_RXB_MASK 0xFu

//! Field DLY_RP_RXB - Delay
#define S_SGMII_PCS_PDI_RXB_CFG_DLY_RP_RXB_POS 4
//! Field DLY_RP_RXB - Delay
#define S_SGMII_PCS_PDI_RXB_CFG_DLY_RP_RXB_MASK 0xF0u

//! @}

//! \defgroup S_SGMII_PCS_PDI_RXB_STAT Register S_SGMII_PCS_PDI_RXB_STAT - Receive Buffer Status Register
//! @{

//! Register Offset (relative)
#define S_SGMII_PCS_PDI_RXB_STAT 0xC
//! Register Offset (absolute) for 1st Instance S_SGMII_PCS_PDI
#define S_SGMII_PCS_PDI_S_SGMII_PCS_PDI_RXB_STAT 0x00A3500Cu

//! Register Reset Value
#define S_SGMII_PCS_PDI_RXB_STAT_RST 0x00000000u

//! Field OVFL_RXB - Overflow Indicator
#define S_SGMII_PCS_PDI_RXB_STAT_OVFL_RXB_POS 0
//! Field OVFL_RXB - Overflow Indicator
#define S_SGMII_PCS_PDI_RXB_STAT_OVFL_RXB_MASK 0x1u
//! Constant NONE - Overflow never detected
#define CONST_S_SGMII_PCS_PDI_RXB_STAT_OVFL_RXB_NONE 0x0
//! Constant ONCE - Overflow occurred at least once
#define CONST_S_SGMII_PCS_PDI_RXB_STAT_OVFL_RXB_ONCE 0x1

//! Field UNFL_RXB - Underflow Indicator
#define S_SGMII_PCS_PDI_RXB_STAT_UNFL_RXB_POS 1
//! Field UNFL_RXB - Underflow Indicator
#define S_SGMII_PCS_PDI_RXB_STAT_UNFL_RXB_MASK 0x2u
//! Constant NONE - Underflow never detected
#define CONST_S_SGMII_PCS_PDI_RXB_STAT_UNFL_RXB_NONE 0x0
//! Constant ONCE - Underflow occurred at least once
#define CONST_S_SGMII_PCS_PDI_RXB_STAT_UNFL_RXB_ONCE 0x1

//! @}

//! \defgroup S_SGMII_PCS_PDI_TXB_CTL Register S_SGMII_PCS_PDI_TXB_CTL - Transmit Buffer Control Register
//! @{

//! Register Offset (relative)
#define S_SGMII_PCS_PDI_TXB_CTL 0x10
//! Register Offset (absolute) for 1st Instance S_SGMII_PCS_PDI
#define S_SGMII_PCS_PDI_S_SGMII_PCS_PDI_TXB_CTL 0x00A35010u

//! Register Reset Value
#define S_SGMII_PCS_PDI_TXB_CTL_RST 0x00000001u

//! Field ENAB_TXB - Enable TX Buffer
#define S_SGMII_PCS_PDI_TXB_CTL_ENAB_TXB_POS 0
//! Field ENAB_TXB - Enable TX Buffer
#define S_SGMII_PCS_PDI_TXB_CTL_ENAB_TXB_MASK 0x1u
//! Constant DISABLE - TX Buffer is disabled
#define CONST_S_SGMII_PCS_PDI_TXB_CTL_ENAB_TXB_DISABLE 0x0
//! Constant ENABLE - TX Buffer is enabled
#define CONST_S_SGMII_PCS_PDI_TXB_CTL_ENAB_TXB_ENABLE 0x1

//! Field INIT_TX_TXB - Initialize TX Buffer
#define S_SGMII_PCS_PDI_TXB_CTL_INIT_TX_TXB_POS 1
//! Field INIT_TX_TXB - Initialize TX Buffer
#define S_SGMII_PCS_PDI_TXB_CTL_INIT_TX_TXB_MASK 0x2u
//! Constant NORMAL - TXB is normally operating
#define CONST_S_SGMII_PCS_PDI_TXB_CTL_INIT_TX_TXB_NORMAL 0x0
//! Constant ACTIVE - TXB is initialized
#define CONST_S_SGMII_PCS_PDI_TXB_CTL_INIT_TX_TXB_ACTIVE 0x1

//! @}

//! \defgroup S_SGMII_PCS_PDI_TXB_CFG Register S_SGMII_PCS_PDI_TXB_CFG - Transmit Buffer Configuration Register
//! @{

//! Register Offset (relative)
#define S_SGMII_PCS_PDI_TXB_CFG 0x14
//! Register Offset (absolute) for 1st Instance S_SGMII_PCS_PDI
#define S_SGMII_PCS_PDI_S_SGMII_PCS_PDI_TXB_CFG 0x00A35014u

//! Register Reset Value
#define S_SGMII_PCS_PDI_TXB_CFG_RST 0x00000040u

//! Field DLY_WP_TX - Delay
#define S_SGMII_PCS_PDI_TXB_CFG_DLY_WP_TX_POS 0
//! Field DLY_WP_TX - Delay
#define S_SGMII_PCS_PDI_TXB_CFG_DLY_WP_TX_MASK 0xFu

//! Field DLY_RP_TXB - Delay
#define S_SGMII_PCS_PDI_TXB_CFG_DLY_RP_TXB_POS 4
//! Field DLY_RP_TXB - Delay
#define S_SGMII_PCS_PDI_TXB_CFG_DLY_RP_TXB_MASK 0xF0u

//! @}

//! \defgroup S_SGMII_PCS_PDI_TXB_STAT Register S_SGMII_PCS_PDI_TXB_STAT - Transmit Buffer Status Register
//! @{

//! Register Offset (relative)
#define S_SGMII_PCS_PDI_TXB_STAT 0x18
//! Register Offset (absolute) for 1st Instance S_SGMII_PCS_PDI
#define S_SGMII_PCS_PDI_S_SGMII_PCS_PDI_TXB_STAT 0x00A35018u

//! Register Reset Value
#define S_SGMII_PCS_PDI_TXB_STAT_RST 0x00000000u

//! Field OVFL_TX - Overflow Indicator
#define S_SGMII_PCS_PDI_TXB_STAT_OVFL_TX_POS 0
//! Field OVFL_TX - Overflow Indicator
#define S_SGMII_PCS_PDI_TXB_STAT_OVFL_TX_MASK 0x1u
//! Constant NONE - Overflow never detected
#define CONST_S_SGMII_PCS_PDI_TXB_STAT_OVFL_TX_NONE 0x0
//! Constant ONCE - Overflow occurred at least once
#define CONST_S_SGMII_PCS_PDI_TXB_STAT_OVFL_TX_ONCE 0x1

//! Field UNFL_TX - Underflow Indicator
#define S_SGMII_PCS_PDI_TXB_STAT_UNFL_TX_POS 1
//! Field UNFL_TX - Underflow Indicator
#define S_SGMII_PCS_PDI_TXB_STAT_UNFL_TX_MASK 0x2u
//! Constant NONE - Underflow never detected
#define CONST_S_SGMII_PCS_PDI_TXB_STAT_UNFL_TX_NONE 0x0
//! Constant ONCE - Underflow occurred at least once
#define CONST_S_SGMII_PCS_PDI_TXB_STAT_UNFL_TX_ONCE 0x1

//! @}

//! @}

#endif
