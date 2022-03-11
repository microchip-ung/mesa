//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p34x/p34x_chip/v_emouchel.priv.p34x_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/chip_top/top_pdi_def.xml
// Register File Name  : TOP_PDI_REGISTERS
// Register File Title : P34X Top Level Registers Description
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _TOP_PDI_REGISTERS_H
#define _TOP_PDI_REGISTERS_H

//! \defgroup TOP_PDI_REGISTERS Register File TOP_PDI_REGISTERS - P34X Top Level Registers Description
//! @{

//! Base Address of TOP_PDI_REGISTERS
#define TOP_PDI_REGISTERS_MODULE_BASE 0x00D28800u

//! \defgroup TOP_CHIP_CFG Register TOP_CHIP_CFG - Top level configuration register
//! @{

//! Register Offset (relative)
#define TOP_CHIP_CFG 0x0
//! Register Offset (absolute) for 1st Instance TOP_PDI_REGISTERS
#define TOP_PDI_REGISTERS_TOP_CHIP_CFG 0x00D28800u

//! Register Reset Value
#define TOP_CHIP_CFG_RST 0x00000000u

//! Field SPI_SECURE_EN - SPI Security Enable
#define TOP_CHIP_CFG_SPI_SECURE_EN_POS 0
//! Field SPI_SECURE_EN - SPI Security Enable
#define TOP_CHIP_CFG_SPI_SECURE_EN_MASK 0x1u
//! Constant DIS - Security Disable
#define CONST_TOP_CHIP_CFG_SPI_SECURE_EN_DIS 0x0
//! Constant EN - Security Enable
#define CONST_TOP_CHIP_CFG_SPI_SECURE_EN_EN 0x1

//! Field DATA_IF_MODE - Data Interface Mode
#define TOP_CHIP_CFG_DATA_IF_MODE_POS 1
//! Field DATA_IF_MODE - Data Interface Mode
#define TOP_CHIP_CFG_DATA_IF_MODE_MASK 0x6u
//! Constant QSGMII - QSGMII
#define CONST_TOP_CHIP_CFG_DATA_IF_MODE_QSGMII 0x0
//! Constant USXGMII - USXGMII
#define CONST_TOP_CHIP_CFG_DATA_IF_MODE_USXGMII 0x1
//! Constant TWO_SGMII - Two SGMII
#define CONST_TOP_CHIP_CFG_DATA_IF_MODE_TWO_SGMII 0x2
//! Constant FOUR_SGMII - Four SGMII
#define CONST_TOP_CHIP_CFG_DATA_IF_MODE_FOUR_SGMII 0x3

//! @}

//! \defgroup TOP_STATUS Register TOP_STATUS - Top level Status register
//! @{

//! Register Offset (relative)
#define TOP_STATUS 0x4
//! Register Offset (absolute) for 1st Instance TOP_PDI_REGISTERS
#define TOP_PDI_REGISTERS_TOP_STATUS 0x00D28804u

//! Register Reset Value
#define TOP_STATUS_RST 0x00000000u

//! Field MDINT_SLICE0 - Slice 0 has asserted an MDINT
#define TOP_STATUS_MDINT_SLICE0_POS 0
//! Field MDINT_SLICE0 - Slice 0 has asserted an MDINT
#define TOP_STATUS_MDINT_SLICE0_MASK 0x1u
//! Constant INACTIVE - MDINT is Not ACTIVE
#define CONST_TOP_STATUS_MDINT_SLICE0_INACTIVE 0x0
//! Constant ACTIVE - MDINT is ACTIVE
#define CONST_TOP_STATUS_MDINT_SLICE0_ACTIVE 0x1

//! Field MDINT_SLICE1 - Slice 1 has asserted an MDINT
#define TOP_STATUS_MDINT_SLICE1_POS 1
//! Field MDINT_SLICE1 - Slice 1 has asserted an MDINT
#define TOP_STATUS_MDINT_SLICE1_MASK 0x2u
//! Constant INACTIVE - MDINT is Not ACTIVE
#define CONST_TOP_STATUS_MDINT_SLICE1_INACTIVE 0x0
//! Constant ACTIVE - MDINT is ACTIVE
#define CONST_TOP_STATUS_MDINT_SLICE1_ACTIVE 0x1

//! Field MDINT_SLICE2 - Slice 2 has asserted an MDINT
#define TOP_STATUS_MDINT_SLICE2_POS 2
//! Field MDINT_SLICE2 - Slice 2 has asserted an MDINT
#define TOP_STATUS_MDINT_SLICE2_MASK 0x4u
//! Constant INACTIVE - MDINT is Not ACTIVE
#define CONST_TOP_STATUS_MDINT_SLICE2_INACTIVE 0x0
//! Constant ACTIVE - MDINT is ACTIVE
#define CONST_TOP_STATUS_MDINT_SLICE2_ACTIVE 0x1

//! Field MDINT_SLICE3 - Slice 3 has asserted an MDINT
#define TOP_STATUS_MDINT_SLICE3_POS 3
//! Field MDINT_SLICE3 - Slice 3 has asserted an MDINT
#define TOP_STATUS_MDINT_SLICE3_MASK 0x8u
//! Constant INACTIVE - MDINT is Not ACTIVE
#define CONST_TOP_STATUS_MDINT_SLICE3_INACTIVE 0x0
//! Constant ACTIVE - MDINT is ACTIVE
#define CONST_TOP_STATUS_MDINT_SLICE3_ACTIVE 0x1

//! Field LP_SLICE0 - LP status Slice 0
#define TOP_STATUS_LP_SLICE0_POS 4
//! Field LP_SLICE0 - LP status Slice 0
#define TOP_STATUS_LP_SLICE0_MASK 0x10u
//! Constant NORMAL - Slice is not in LP mode
#define CONST_TOP_STATUS_LP_SLICE0_NORMAL 0x0
//! Constant LP - Slice is in LP mode
#define CONST_TOP_STATUS_LP_SLICE0_LP 0x1

//! Field LP_SLICE1 - LP status Slice 1
#define TOP_STATUS_LP_SLICE1_POS 5
//! Field LP_SLICE1 - LP status Slice 1
#define TOP_STATUS_LP_SLICE1_MASK 0x20u
//! Constant NORMAL - Slice is not in LP mode
#define CONST_TOP_STATUS_LP_SLICE1_NORMAL 0x0
//! Constant LP - Slice is in LP mode
#define CONST_TOP_STATUS_LP_SLICE1_LP 0x1

//! Field LP_SLICE2 - LP status Slice 2
#define TOP_STATUS_LP_SLICE2_POS 6
//! Field LP_SLICE2 - LP status Slice 2
#define TOP_STATUS_LP_SLICE2_MASK 0x40u
//! Constant NORMAL - Slice is not in LP mode
#define CONST_TOP_STATUS_LP_SLICE2_NORMAL 0x0
//! Constant LP - Slice is in LP mode
#define CONST_TOP_STATUS_LP_SLICE2_LP 0x1

//! Field LP_SLICE3 - LP status Slice 3
#define TOP_STATUS_LP_SLICE3_POS 7
//! Field LP_SLICE3 - LP status Slice 3
#define TOP_STATUS_LP_SLICE3_MASK 0x80u
//! Constant NORMAL - Slice is not in LP mode
#define CONST_TOP_STATUS_LP_SLICE3_NORMAL 0x0
//! Constant LP - Slice is in LP mode
#define CONST_TOP_STATUS_LP_SLICE3_LP 0x1

//! @}

//! \defgroup TOP_SLICE_IF Register TOP_SLICE_IF - Slice Interface Selector
//! @{

//! Register Offset (relative)
#define TOP_SLICE_IF 0x8
//! Register Offset (absolute) for 1st Instance TOP_PDI_REGISTERS
#define TOP_PDI_REGISTERS_TOP_SLICE_IF 0x00D28808u

//! Register Reset Value
#define TOP_SLICE_IF_RST 0x00000000u

//! Field IF_SLICE - Select Slice redirection from top to slice
#define TOP_SLICE_IF_IF_SLICE_POS 0
//! Field IF_SLICE - Select Slice redirection from top to slice
#define TOP_SLICE_IF_IF_SLICE_MASK 0x3u
//! Constant SLICE0 - Slice 0
#define CONST_TOP_SLICE_IF_IF_SLICE_SLICE0 0x0
//! Constant SLICE1 - Slice 1
#define CONST_TOP_SLICE_IF_IF_SLICE_SLICE1 0x1
//! Constant SLICE2 - Slice 2
#define CONST_TOP_SLICE_IF_IF_SLICE_SLICE2 0x2
//! Constant SLICE3 - Slice 3
#define CONST_TOP_SLICE_IF_IF_SLICE_SLICE3 0x3

//! Field LP_WAKE0 - Wake-up Slice 0 from LP
#define TOP_SLICE_IF_LP_WAKE0_POS 2
//! Field LP_WAKE0 - Wake-up Slice 0 from LP
#define TOP_SLICE_IF_LP_WAKE0_MASK 0x4u
//! Constant NOWAKE - Wake-up event is not asserted
#define CONST_TOP_SLICE_IF_LP_WAKE0_NOWAKE 0x0
//! Constant WAKE - Wake-up event is asserted
#define CONST_TOP_SLICE_IF_LP_WAKE0_WAKE 0x1

//! Field LP_WAKE1 - Wake-up Slice 1 from LP.
#define TOP_SLICE_IF_LP_WAKE1_POS 3
//! Field LP_WAKE1 - Wake-up Slice 1 from LP.
#define TOP_SLICE_IF_LP_WAKE1_MASK 0x8u
//! Constant NOWAKE - Wake-up event is not asserted
#define CONST_TOP_SLICE_IF_LP_WAKE1_NOWAKE 0x0
//! Constant WAKE - Wake-up event is asserted
#define CONST_TOP_SLICE_IF_LP_WAKE1_WAKE 0x1

//! Field LP_WAKE2 - Wake-up Slice 2 from LP
#define TOP_SLICE_IF_LP_WAKE2_POS 4
//! Field LP_WAKE2 - Wake-up Slice 2 from LP
#define TOP_SLICE_IF_LP_WAKE2_MASK 0x10u
//! Constant NOWAKE - Wake-up event is not asserted
#define CONST_TOP_SLICE_IF_LP_WAKE2_NOWAKE 0x0
//! Constant WAKE - Wake-up event is asserted
#define CONST_TOP_SLICE_IF_LP_WAKE2_WAKE 0x1

//! Field LP_WAKE3 - Wake-up Slice 3 from LP
#define TOP_SLICE_IF_LP_WAKE3_POS 5
//! Field LP_WAKE3 - Wake-up Slice 3 from LP
#define TOP_SLICE_IF_LP_WAKE3_MASK 0x20u
//! Constant NOWAKE - Wake-up event is not asserted
#define CONST_TOP_SLICE_IF_LP_WAKE3_NOWAKE 0x0
//! Constant WAKE - Wake-up event is asserted
#define CONST_TOP_SLICE_IF_LP_WAKE3_WAKE 0x1

//! @}

//! \defgroup TOP_FCR Register TOP_FCR - Firmware address offset register
//! @{

//! Register Offset (relative)
#define TOP_FCR 0xC
//! Register Offset (absolute) for 1st Instance TOP_PDI_REGISTERS
#define TOP_PDI_REGISTERS_TOP_FCR 0x00D2880Cu

//! Register Reset Value
#define TOP_FCR_RST 0x00000000u

//! Field FCR - Firmware address offset MSB
#define TOP_FCR_FCR_POS 0
//! Field FCR - Firmware address offset MSB
#define TOP_FCR_FCR_MASK 0x3FFFu

//! Field BOOTSEL - Boot Select
#define TOP_FCR_BOOTSEL_POS 14
//! Field BOOTSEL - Boot Select
#define TOP_FCR_BOOTSEL_MASK 0xC000u
//! Constant ROM - GPHY Macro loads firmware memory from internal ROM
#define CONST_TOP_FCR_BOOTSEL_ROM 0x0
//! Constant RAM - GPHY Macro loads firmware memory from internal RAM.
#define CONST_TOP_FCR_BOOTSEL_RAM 0x1
//! Constant FLASH - GPHY Macro loads firmware memory by external E2PROM.
#define CONST_TOP_FCR_BOOTSEL_FLASH 0x2
//! Constant OTP - GPHY Macro loads firmware memory from OTP
#define CONST_TOP_FCR_BOOTSEL_OTP 0x3

//! @}

//! \defgroup TOP_CFG Register TOP_CFG - GPHY Code Configuration Register
//! @{

//! Register Offset (relative)
#define TOP_CFG 0x10
//! Register Offset (absolute) for 1st Instance TOP_PDI_REGISTERS
#define TOP_PDI_REGISTERS_TOP_CFG 0x00D28810u

//! Register Reset Value
#define TOP_CFG_RST 0x00000002u

//! Field NOWAIT - No Wait
#define TOP_CFG_NOWAIT_POS 1
//! Field NOWAIT - No Wait
#define TOP_CFG_NOWAIT_MASK 0x2u
//! Constant HALT - Halt mode enable
#define CONST_TOP_CFG_NOWAIT_HALT 0x0
//! Constant NOWAIT - Halt mode disable
#define CONST_TOP_CFG_NOWAIT_NOWAIT 0x1

//! @}

//! \defgroup TOP_INDICATOR Register TOP_INDICATOR - Error codes for debug
//! @{

//! Register Offset (relative)
#define TOP_INDICATOR 0x14
//! Register Offset (absolute) for 1st Instance TOP_PDI_REGISTERS
#define TOP_PDI_REGISTERS_TOP_INDICATOR 0x00D28814u

//! Register Reset Value
#define TOP_INDICATOR_RST 0x00000000u

//! Field FAILCODE - Boot Fail Code
#define TOP_INDICATOR_FAILCODE_POS 0
//! Field FAILCODE - Boot Fail Code
#define TOP_INDICATOR_FAILCODE_MASK 0x1Fu
//! Constant PASS - No Failure
#define CONST_TOP_INDICATOR_FAILCODE_PASS 0x0
//! Constant OTPBOOT - OTP Shell Boot Failed
#define CONST_TOP_INDICATOR_FAILCODE_OTPBOOT 0x1
//! Constant FWCRC - OTP FW CRC Check Failed
#define CONST_TOP_INDICATOR_FAILCODE_FWCRC 0x2
//! Constant CODE3 - Error 3
#define CONST_TOP_INDICATOR_FAILCODE_CODE3 0x3
//! Constant CODE4 - Error 4
#define CONST_TOP_INDICATOR_FAILCODE_CODE4 0x4
//! Constant CODE5 - Error 5
#define CONST_TOP_INDICATOR_FAILCODE_CODE5 0x5

//! Field BOOTROM_EXIT - BOOTROM Exit Path
#define TOP_INDICATOR_BOOTROM_EXIT_POS 5
//! Field BOOTROM_EXIT - BOOTROM Exit Path
#define TOP_INDICATOR_BOOTROM_EXIT_MASK 0xE0u
//! Constant NO - BootROM Exit Not completed Yet
#define CONST_TOP_INDICATOR_BOOTROM_EXIT_NO 0x0
//! Constant FLASH - BootROM Exit to FLASH
#define CONST_TOP_INDICATOR_BOOTROM_EXIT_FLASH 0x1
//! Constant ROM - BootROM Exit to ROM
#define CONST_TOP_INDICATOR_BOOTROM_EXIT_ROM 0x2
//! Constant OTP - BootROM exit to OTP
#define CONST_TOP_INDICATOR_BOOTROM_EXIT_OTP 0x3
//! Constant RAM - BootROM exit to RAM
#define CONST_TOP_INDICATOR_BOOTROM_EXIT_RAM 0x4

//! Field BOOTLOADER_EXIT - BOOT Loader Exit Path
#define TOP_INDICATOR_BOOTLOADER_EXIT_POS 8
//! Field BOOTLOADER_EXIT - BOOT Loader Exit Path
#define TOP_INDICATOR_BOOTLOADER_EXIT_MASK 0x700u
//! Constant NO - Boot Loader Exit Not completed Yet
#define CONST_TOP_INDICATOR_BOOTLOADER_EXIT_NO 0x0
//! Constant FLASH - Boot Loader Exit to FLASH
#define CONST_TOP_INDICATOR_BOOTLOADER_EXIT_FLASH 0x1
//! Constant ROM - Boot Loader Exit to ROM
#define CONST_TOP_INDICATOR_BOOTLOADER_EXIT_ROM 0x2
//! Constant OTP - Boot Loader Exit to OTP
#define CONST_TOP_INDICATOR_BOOTLOADER_EXIT_OTP 0x3
//! Constant RAM - Boot Loader Exit to RAM
#define CONST_TOP_INDICATOR_BOOTLOADER_EXIT_RAM 0x4

//! @}

//! \defgroup TOP_SLICE_MASTER Register TOP_SLICE_MASTER - Written by Master Slice FW
//! @{

//! Register Offset (relative)
#define TOP_SLICE_MASTER 0x18
//! Register Offset (absolute) for 1st Instance TOP_PDI_REGISTERS
#define TOP_PDI_REGISTERS_TOP_SLICE_MASTER 0x00D28818u

//! Register Reset Value
#define TOP_SLICE_MASTER_RST 0x00000000u

//! Field MASTER_SLICE - Master Slice Number
#define TOP_SLICE_MASTER_MASTER_SLICE_POS 0
//! Field MASTER_SLICE - Master Slice Number
#define TOP_SLICE_MASTER_MASTER_SLICE_MASK 0x3u
//! Constant SLICE0 - Slice 0
#define CONST_TOP_SLICE_MASTER_MASTER_SLICE_SLICE0 0x0
//! Constant SLICE1 - Slice 1
#define CONST_TOP_SLICE_MASTER_MASTER_SLICE_SLICE1 0x1
//! Constant SLICE2 - Slice 2
#define CONST_TOP_SLICE_MASTER_MASTER_SLICE_SLICE2 0x2
//! Constant SLICE3 - Slice 3
#define CONST_TOP_SLICE_MASTER_MASTER_SLICE_SLICE3 0x3

//! @}

#endif
