//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p34x/p34x_chip/v_emouchel.priv.p34x_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/slice_control/slice_ctrl_registers_def.xml
// Register File Name  : SLICE_CTRL_PDI_REGISTERS
// Register File Title : SLICE_CTRL Control Registers
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _SLICE_CTRL_PDI_REGISTERS_H
#define _SLICE_CTRL_PDI_REGISTERS_H

//! \defgroup SLICE_CTRL_PDI_REGISTERS Register File SLICE_CTRL_PDI_REGISTERS - SLICE_CTRL Control Registers
//! @{

//! Base Address of SLICE_CTRL_PDI_REGISTERS
#define SLICE_CTRL_PDI_REGISTERS_MODULE_BASE 0x00A4CF40u

//! \defgroup SLICE_CTRL_PDI_CTRL Register SLICE_CTRL_PDI_CTRL - SLICE_CTRL Interface Control Register
//! @{

//! Register Offset (relative)
#define SLICE_CTRL_PDI_CTRL 0x0
//! Register Offset (absolute) for 1st Instance SLICE_CTRL_PDI_REGISTERS
#define SLICE_CTRL_PDI_REGISTERS_SLICE_CTRL_PDI_CTRL 0x00A4CF40u

//! Register Reset Value
#define SLICE_CTRL_PDI_CTRL_RST 0x00000000u

//! Field SB0_SD - Shared Buffer 0 Shutdown
#define SLICE_CTRL_PDI_CTRL_SB0_SD_POS 4
//! Field SB0_SD - Shared Buffer 0 Shutdown
#define SLICE_CTRL_PDI_CTRL_SB0_SD_MASK 0x10u
//! Constant ON - Normal operation
#define CONST_SLICE_CTRL_PDI_CTRL_SB0_SD_ON 0x0
//! Constant OFF - Shutdown mode
#define CONST_SLICE_CTRL_PDI_CTRL_SB0_SD_OFF 0x1

//! Field SB1_SD - Shared Buffer 1 Shutdown
#define SLICE_CTRL_PDI_CTRL_SB1_SD_POS 5
//! Field SB1_SD - Shared Buffer 1 Shutdown
#define SLICE_CTRL_PDI_CTRL_SB1_SD_MASK 0x20u
//! Constant ON - Normal operation
#define CONST_SLICE_CTRL_PDI_CTRL_SB1_SD_ON 0x0
//! Constant OFF - Shutdown mode
#define CONST_SLICE_CTRL_PDI_CTRL_SB1_SD_OFF 0x1

//! @}

//! \defgroup SLICE_CTRL_PDI_ID Register SLICE_CTRL_PDI_ID
//! @{

//! Register Offset (relative)
#define SLICE_CTRL_PDI_ID 0x4
//! Register Offset (absolute) for 1st Instance SLICE_CTRL_PDI_REGISTERS
#define SLICE_CTRL_PDI_REGISTERS_SLICE_CTRL_PDI_ID 0x00A4CF44u

//! Register Reset Value
#define SLICE_CTRL_PDI_ID_RST 0x00000000u

//! Field HW_ID - Slice ID
#define SLICE_CTRL_PDI_ID_HW_ID_POS 0
//! Field HW_ID - Slice ID
#define SLICE_CTRL_PDI_ID_HW_ID_MASK 0x3u
//! Constant SLICE0 - Slice 0
#define CONST_SLICE_CTRL_PDI_ID_HW_ID_SLICE0 0x0
//! Constant SLICE1 - Slice 1
#define CONST_SLICE_CTRL_PDI_ID_HW_ID_SLICE1 0x1
//! Constant SLICE2 - Slice 2
#define CONST_SLICE_CTRL_PDI_ID_HW_ID_SLICE2 0x2
//! Constant SLICE3 - Slice 3
#define CONST_SLICE_CTRL_PDI_ID_HW_ID_SLICE3 0x3

//! Field IS_MASTER - Indicate that Slice is MASTER
#define SLICE_CTRL_PDI_ID_IS_MASTER_POS 2
//! Field IS_MASTER - Indicate that Slice is MASTER
#define SLICE_CTRL_PDI_ID_IS_MASTER_MASK 0x4u
//! Constant FALSE - Slice is not Master
#define CONST_SLICE_CTRL_PDI_ID_IS_MASTER_FALSE 0x0
//! Constant TRUE - Slice is Master
#define CONST_SLICE_CTRL_PDI_ID_IS_MASTER_TRUE 0x1

//! @}

//! \defgroup SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH0 Register SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH0 - Configuration common to all slices
//! @{

//! Register Offset (relative)
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH0 0x8
//! Register Offset (absolute) for 1st Instance SLICE_CTRL_PDI_REGISTERS
#define SLICE_CTRL_PDI_REGISTERS_SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH0 0x00A4CF48u

//! Register Reset Value
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH0_RST 0x00004000u

//! Field BFDEV - Base Frequency Deviation
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH0_BFDEV_POS 0
//! Field BFDEV - Base Frequency Deviation
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH0_BFDEV_MASK 0xFFFFu

//! @}

//! \defgroup SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1 Register SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1 - GPHY General Purpose Pin Strapping 1 Register
//! @{

//! Register Offset (relative)
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1 0xC
//! Register Offset (absolute) for 1st Instance SLICE_CTRL_PDI_REGISTERS
#define SLICE_CTRL_PDI_REGISTERS_SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1 0x00A4CF4Cu

//! Register Reset Value
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1_RST 0x00000000u

//! Field CHIP_ID - Chip ID
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1_CHIP_ID_POS 0
//! Field CHIP_ID - Chip ID
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1_CHIP_ID_MASK 0xFu

//! Field CHIP_VER - Chip Version
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1_CHIP_VER_POS 4
//! Field CHIP_VER - Chip Version
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1_CHIP_VER_MASK 0xF0u

//! Field MDIO_PHY_ADDR - MDIO PHY Address
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1_MDIO_PHY_ADDR_POS 8
//! Field MDIO_PHY_ADDR - MDIO PHY Address
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1_MDIO_PHY_ADDR_MASK 0x1F00u

//! Field MDIO_INT_POL - MDIO Interrupt Polarity
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1_MDIO_INT_POL_POS 13
//! Field MDIO_INT_POL - MDIO Interrupt Polarity
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1_MDIO_INT_POL_MASK 0x2000u
//! Constant HIGH - Interrupt is active high.
#define CONST_SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1_MDIO_INT_POL_HIGH 0x0
//! Constant LOW - Interrupt is active low.
#define CONST_SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1_MDIO_INT_POL_LOW 0x1

//! Field G2_5_DIS - Disable 2.5G mode support
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1_G2_5_DIS_POS 14
//! Field G2_5_DIS - Disable 2.5G mode support
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1_G2_5_DIS_MASK 0x4000u
//! Constant EN - Enable 2.5G mode
#define CONST_SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1_G2_5_DIS_EN 0x0
//! Constant DIS - Disable 2.5G mode
#define CONST_SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1_G2_5_DIS_DIS 0x1

//! Field LED_EN - Led startup enable
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1_LED_EN_POS 15
//! Field LED_EN - Led startup enable
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1_LED_EN_MASK 0x8000u
//! Constant DISABLE - LED is disabled at startup
#define CONST_SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1_LED_EN_DISABLE 0x0
//! Constant ENABLE - LED is enabled at startup
#define CONST_SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH1_LED_EN_ENABLE 0x1

//! @}

//! \defgroup SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH2 Register SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH2 - GPHY General Purpose Pin Strapping 2 Register
//! @{

//! Register Offset (relative)
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH2 0x10
//! Register Offset (absolute) for 1st Instance SLICE_CTRL_PDI_REGISTERS
#define SLICE_CTRL_PDI_REGISTERS_SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH2 0x00A4CF50u

//! Register Reset Value
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH2_RST 0x00000000u

//! Field RCAL - RCAL
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH2_RCAL_POS 0
//! Field RCAL - RCAL
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH2_RCAL_MASK 0xFu

//! Field RC_COUNT - RC Count
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH2_RC_COUNT_POS 4
//! Field RC_COUNT - RC Count
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH2_RC_COUNT_MASK 0x3FF0u

//! Field MDIO_I2C - MDIO/I2C Select
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH2_MDIO_I2C_POS 14
//! Field MDIO_I2C - MDIO/I2C Select
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH2_MDIO_I2C_MASK 0x4000u
//! Constant MDIO - MDIO
#define CONST_SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH2_MDIO_I2C_MDIO 0x0
//! Constant I2C - I2C
#define CONST_SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH2_MDIO_I2C_I2C 0x1

//! Field RJ45_TAP - RJ45 Tap Configuration
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH2_RJ45_TAP_POS 15
//! Field RJ45_TAP - RJ45 Tap Configuration
#define SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH2_RJ45_TAP_MASK 0x8000u
//! Constant DOWN - TAP-DOWN RJ45
#define CONST_SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH2_RJ45_TAP_DOWN 0x0
//! Constant UP - TAP-UP RJ45
#define CONST_SLICE_CTRL_PDI_IP_PINSTRAP_TO_LATCH2_RJ45_TAP_UP 0x1

//! @}

//! \defgroup SLICE_CTRL_PDI_IP_CFG0 Register SLICE_CTRL_PDI_IP_CFG0 - Slice configuration items which are in addition of the GPHY_IP pinstraps
//! @{

//! Register Offset (relative)
#define SLICE_CTRL_PDI_IP_CFG0 0x14
//! Register Offset (absolute) for 1st Instance SLICE_CTRL_PDI_REGISTERS
#define SLICE_CTRL_PDI_REGISTERS_SLICE_CTRL_PDI_IP_CFG0 0x00A4CF54u

//! Register Reset Value
#define SLICE_CTRL_PDI_IP_CFG0_RST 0x00000000u

//! Field CFG0 - CFG0
#define SLICE_CTRL_PDI_IP_CFG0_CFG0_POS 0
//! Field CFG0 - CFG0
#define SLICE_CTRL_PDI_IP_CFG0_CFG0_MASK 0xFFFFu

//! @}

//! \defgroup SLICE_CTRL_PDI_IP_CFG1 Register SLICE_CTRL_PDI_IP_CFG1 - Slice configuration items which are in addition of the GPHY_IP pinstraps
//! @{

//! Register Offset (relative)
#define SLICE_CTRL_PDI_IP_CFG1 0x18
//! Register Offset (absolute) for 1st Instance SLICE_CTRL_PDI_REGISTERS
#define SLICE_CTRL_PDI_REGISTERS_SLICE_CTRL_PDI_IP_CFG1 0x00A4CF58u

//! Register Reset Value
#define SLICE_CTRL_PDI_IP_CFG1_RST 0x00000000u

//! Field CFG1 - CFG1
#define SLICE_CTRL_PDI_IP_CFG1_CFG1_POS 0
//! Field CFG1 - CFG1
#define SLICE_CTRL_PDI_IP_CFG1_CFG1_MASK 0xFFFFu

//! @}

//! @}

#endif
