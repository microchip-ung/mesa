// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LUTON26_REGS_ICPU_CFG_H_
#define _VTSS_LUTON26_REGS_ICPU_CFG_H_


#include "vtss_luton26_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a ICPU_CFG
 *
 * VCore Configuration
 *
 ***********************************************************************/

/**
 * Register Group: \a ICPU_CFG:CPU_SYSTEM_CTRL
 *
 * Configurations for the CPU system.
 */


/** 
 * \brief General Purpose Register
 *
 * \details
 * Register: \a ICPU_CFG:CPU_SYSTEM_CTRL:GPR
 *
 * @param ri Register: GPR (??), 0-7
 */
#define VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GPR(ri)  VTSS_IOREG(VTSS_TO_CFG,0x0 + (ri))


/** 
 * \brief Reset Settings
 *
 * \details
 * Register: \a ICPU_CFG:CPU_SYSTEM_CTRL:RESET
 */
#define VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_RESET  VTSS_IOREG(VTSS_TO_CFG,0x8)

/** 
 * \brief
 * Set this field to enable the VCore CPU. This field is only valid when
 * automatic booting of the VCore CPU has been disabled via VCore_Cfg
 * inputs. This field has no effect when the VCore CPU is configured for
 * automatically boot.
 * Note: By using this field it is possible for an external CPU to manually
 * load a code image to memory, change into normal mode, and then release
 * the VCore CPU after which it will boot from memory rather than FLASH.
 *
 * \details 
 * 0: VCore CPU is forced in reset
 * 1: VCore CPU is allowed to boot
 *
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_RESET . CPU_RELEASE
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_RESET_CPU_RELEASE  VTSS_BIT(4)

/** 
 * \brief
 * Set this field to enable VCore System reset protection. It is possible
 * to protect the VCore System from soft-reset (issued via
 * RESET:CORE_RST_FORCE) and watchdog-timeout. When this field is set the
 * aforementioned resets only reset the VCore CPU, not the VCore System.
 *
 * \details 
 * 0: WDT event reset entire VCore
 * 1: WDT event only reset the VCore CPU
 *
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_RESET . CORE_RST_CPU_ONLY
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_RESET_CORE_RST_CPU_ONLY  VTSS_BIT(3)

/** 
 * \brief
 * Set this field to enable VCore reset protection. It is possible to
 * protect the entire VCore from chip-level soft-reset (issued via
 * DEVCPU_GCB::SOFT_CHIP_RST.SOFT_CHIP_RST). Setting this field does not
 * protect agains hard-reset of the chip (by asserting the reset pin).
 *
 * \details 
 * 0: No reset protection
 * 1: VCore is protected from chip-level-soft-reset
 *
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_RESET . CORE_RST_PROTECT
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_RESET_CORE_RST_PROTECT  VTSS_BIT(2)

/** 
 * \brief
 * Set this field to generate a soft reset for the VCore. This field will
 * be cleared when the reset has taken effect.
 * It is possible to protect the VCore system (everyhing else than the
 * VCore CPU) from reset via  RESET.CORE_RST_CPU_ONLY.
 *
 * \details 
 * 0: VCore is not reset
 * 1: Initiate soft reset of the VCore
 *
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_RESET . CORE_RST_FORCE
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_RESET_CORE_RST_FORCE  VTSS_BIT(1)

/** 
 * \brief
 * While this field is set, the memory controller is held in reset.
 *
 * \details 
 * 0: Memory controller is not reset
 * 1: Memory controller is forced in reset
 *
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_RESET . MEM_RST_FORCE
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_RESET_MEM_RST_FORCE  VTSS_BIT(0)


/** 
 * \brief General control
 *
 * \details
 * Register: \a ICPU_CFG:CPU_SYSTEM_CTRL:GENERAL_CTRL
 */
#define VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL  VTSS_IOREG(VTSS_TO_CFG,0x9)

/** 
 * \brief
 * Set this field to force PI interface into master mode. By default only
 * the boot interface of the VCore system is in master mode (controlled by
 * the VCore).
 * This field must be set if the VCore is started manually or requires the
 * non-boot interface for accessing logic outside the chip. Please note, if
 * this fiel is set, it is no longer possible for an external CPU to access
 * registers in the chip via PI.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL . IF_MASTER_PI_ENA
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_MASTER_PI_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Use this field to change from Boot mode to Normal mode. In Boot mode,
 * the reset vector of the VCore CPU maps to CS0 on the parallel interface.
 * When in Normal mode, this address maps instead to the DRAM Controller.
 * The DRAM Controller must be operational before disabling Boot mode.
 * After setting Boot mode, this register must be read back. The change in
 * Boot mode becomes effective during reading.
 *
 * \details 
 * 0: The VCore memory map is in Normal mode.
 * 1: The VCore memory map is in Boot mode.
 *
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL . BOOT_MODE_ENA
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_BOOT_MODE_ENA  VTSS_BIT(0)


/** 
 * \brief General status
 *
 * \details
 * Register: \a ICPU_CFG:CPU_SYSTEM_CTRL:GENERAL_STAT
 */
#define VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT  VTSS_IOREG(VTSS_TO_CFG,0xa)

/** 
 * \brief
 * This field is set if the VCore CPU has entered sleep mode.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT . CPU_SLEEP
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT_CPU_SLEEP  VTSS_BIT(3)

/** 
 * \brief
 * This field shows the endianess that has been configured for the VCore
 * CPU.
 *
 * \details 
 * 0: Little Endian
 * 1: Big Endian
 *
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT . ENDIAN_MODE
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT_ENDIAN_MODE  VTSS_BIT(2)

/** 
 * \brief
 * This field shows which boot strategy that has been configured for the
 * VCore CPU.
 *
 * \details 
 * 0: Automatic booting
 * 1: Manual booting
 *
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT . BOOT_MODE
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT_BOOT_MODE  VTSS_BIT(1)

/** 
 * \brief
 * This field shows which boot interface that has been configured for the
 * VCore CPU.
 *
 * \details 
 * 0: PI
 * 1: SPI
 *
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT . BOOT_IF
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT_BOOT_IF  VTSS_BIT(0)

/**
 * Register Group: \a ICPU_CFG:PI_MST
 *
 * Parallel Interface Master Configuration
 */


/** 
 * \brief PI Master Configuration
 *
 * \details
 * Register: \a ICPU_CFG:PI_MST:PI_MST_CFG
 */
#define VTSS_ICPU_CFG_PI_MST_PI_MST_CFG      VTSS_IOREG(VTSS_TO_CFG,0xb)

/** 
 * \brief
 * Controls the clock for the PI Controller.
 *
 * \details 
 * 0: Illegal
 * 1: Illegal
 * 2: Use CPU clock/2
 * ...
 * 31: Use CPU clock/31
 *
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_MST_CFG . CLK_DIV
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_CFG_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_MST_CFG_CLK_DIV     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_MST_CFG_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief PI Master Control Register
 *
 * \details
 * This is a replicated register, where each replication holds the
 * configurations for one chip select. Changes to a value in one of the
 * replicated instances apply only to that chip select.
 *
 * Register: \a ICPU_CFG:PI_MST:PI_MST_CTRL
 *
 * @param ri Replicator: x_PI_MST_CS_CNT (??), 0-3
 */
#define VTSS_ICPU_CFG_PI_MST_PI_MST_CTRL(ri)  VTSS_IOREG(VTSS_TO_CFG,0xc + (ri))

/** 
 * \brief
 * Data width. In 8-bit mode, the unused data-bits contain additional
 * address information.
 *
 * \details 
 * 0: 8 bits
 * 1: 16 bits
 *
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_MST_CTRL . DATA_WID
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_CTRL_DATA_WID  VTSS_BIT(23)

/** 
 * \brief
 * Device-paced transfer enable. When enabled, use PI_nDone to end a
 * transfer.
 *
 * \details 
 * 0: Disabled
 * 1: Enabled
 *
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_MST_CTRL . DEVICE_PACED_XFER_ENA
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_CTRL_DEVICE_PACED_XFER_ENA  VTSS_BIT(22)

/** 
 * \brief
 * Enable timeout on device-paced transfers. If enabled, a
 * device_paced_transfer transfer does not wait indefinitely for assertion
 * of PI_nDone. If a timeout occurs, the TIMEOUT_ERR_STICKY bit is set in
 * the status register and the current transfer is terminated (read-data
 * will be invalid).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_MST_CTRL . DEVICE_PACED_TIMEOUT_ENA
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_CTRL_DEVICE_PACED_TIMEOUT_ENA  VTSS_BIT(21)

/** 
 * \brief
 * Determines the number of PI_Clk cycles from the start of a transfer
 * until a timeout occurs. This field is only valid when timeout for
 * device-paced transfer is enabled.
 *
 * \details 
 * 000: 16 PI_Clk cycles
 * 001: 32 PI_Clk cycles
 * 010: 64 PI_Clk cycles
 * 011: 128 PI_Clk cycles
 * 100: 256 PI_Clk cycles
 * 101: 512 PI_Clk cycles
 * 110: 1024 PI_Clk cycles
 * 111: 2048 PI_Clk cycles
 *
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_MST_CTRL . DEVICE_PACED_TIMEOUT
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_CTRL_DEVICE_PACED_TIMEOUT(x)  VTSS_ENCODE_BITFIELD(x,18,3)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_MST_CTRL_DEVICE_PACED_TIMEOUT     VTSS_ENCODE_BITMASK(18,3)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_MST_CTRL_DEVICE_PACED_TIMEOUT(x)  VTSS_EXTRACT_BITFIELD(x,18,3)

/** 
 * \brief
 * Polarity of PI_nDone for device-paced transfers.
 *
 * \details 
 * 0: PI_nDone is active low
 * 1: PI_nDone is active high
 *
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_MST_CTRL . DONE_POL
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_CTRL_DONE_POL  VTSS_BIT(16)

/** 
 * \brief
 * Controls when data is sampled in relation to assertion of PI_nDone for
 * device-paced reads.
 *
 * \details 
 * 0: Data is sampled one PI_Clk cycle after PI_nDone goes active.
 * 1: Data is sampled on the same PI_Clk cycle where PI_nDone goes active.
 *
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_MST_CTRL . SMPL_ON_DONE
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_CTRL_SMPL_ON_DONE  VTSS_BIT(15)

/** 
 * \brief
 * Number of wait states measured in PI_Clk cycles on both read and write
 * transfers.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_MST_CTRL . WAITCC
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_CTRL_WAITCC(x)  VTSS_ENCODE_BITFIELD(x,7,8)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_MST_CTRL_WAITCC     VTSS_ENCODE_BITMASK(7,8)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_MST_CTRL_WAITCC(x)  VTSS_EXTRACT_BITFIELD(x,7,8)

/** 
 * \brief
 * Number of PI_Clk cycles from address driven to PI_nCS[x] low.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_MST_CTRL . CSCC
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_CTRL_CSCC(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_MST_CTRL_CSCC     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_MST_CTRL_CSCC(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/** 
 * \brief
 * Number of PI_Clk cycles from PI_nCS[x] low to PI_nOE low.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_MST_CTRL . OECC
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_CTRL_OECC(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_MST_CTRL_OECC     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_MST_CTRL_OECC(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * Number of PI_Clk cycles to insert at the end of a transfer.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_MST_CTRL . HLDCC
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_CTRL_HLDCC(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_MST_CTRL_HLDCC     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_MST_CTRL_HLDCC(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief PI Master Status Registers
 *
 * \details
 * This is a replicated register, where each replication holds the status
 * for one chip select.
 *
 * Register: \a ICPU_CFG:PI_MST:PI_MST_STATUS
 *
 * @param ri Replicator: x_PI_MST_CS_CNT (??), 0-3
 */
#define VTSS_ICPU_CFG_PI_MST_PI_MST_STATUS(ri)  VTSS_IOREG(VTSS_TO_CFG,0x10 + (ri))

/** 
 * \brief
 * If a timeout is enabled and timeout occurs during a device-paced
 * transfer, this bit is set.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_MST_STATUS . TIMEOUT_ERR_STICKY
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_STATUS_TIMEOUT_ERR_STICKY  VTSS_BIT(0)

/**
 * Register Group: \a ICPU_CFG:SPI_MST
 *
 * SPI Master Configuration
 */


/** 
 * \brief SPI Master Configuration
 *
 * \details
 * Register: \a ICPU_CFG:SPI_MST:SPI_MST_CFG
 */
#define VTSS_ICPU_CFG_SPI_MST_SPI_MST_CFG    VTSS_IOREG(VTSS_TO_CFG,0x14)

/** 
 * \brief
 * The type of read-instruction that the SPI Controller generates for
 * reads.
 *
 * \details 
 * 0: READ (slow read - Instruction code - 0x03)
 * 1: FAST READ (fast read - Instruction code - 0x0B)
 *
 * Field: ::VTSS_ICPU_CFG_SPI_MST_SPI_MST_CFG . FAST_READ_ENA
 */
#define  VTSS_F_ICPU_CFG_SPI_MST_SPI_MST_CFG_FAST_READ_ENA  VTSS_BIT(10)

/** 
 * \brief
 * The minimum number of SPI clock cycles for which the SPI chip select
 * (SI_nEn) must be deasserted in between transfers. Typical value of this
 * is 100 ns. Setting this field to 0 is illegal.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_SPI_MST_SPI_MST_CFG . CS_DESELECT_TIME
 */
#define  VTSS_F_ICPU_CFG_SPI_MST_SPI_MST_CFG_CS_DESELECT_TIME(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_ICPU_CFG_SPI_MST_SPI_MST_CFG_CS_DESELECT_TIME     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_ICPU_CFG_SPI_MST_SPI_MST_CFG_CS_DESELECT_TIME(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * Controls the clock frequency for the SPI interface (SI_Clk). The clock
 * frequency is VCore system clock divided by the value of this field.
 * Setting this field to 0 or 1 value is illegal.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_SPI_MST_SPI_MST_CFG . CLK_DIV
 */
#define  VTSS_F_ICPU_CFG_SPI_MST_SPI_MST_CFG_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_ICPU_CFG_SPI_MST_SPI_MST_CFG_CLK_DIV     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_ICPU_CFG_SPI_MST_SPI_MST_CFG_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief Manual control of the SPI interface
 *
 * \details
 * Note: There are 4 chip selects in total, but only chip select 0 is
 * mapped to IO-pin (SI_nEn). The rest of the SPI chip selects are
 * available as alternate functions on GPIOs, these must be enabled in the
 * GPIO controller before they can be controlled via this register.
 *
 * Register: \a ICPU_CFG:SPI_MST:SW_MODE
 */
#define VTSS_ICPU_CFG_SPI_MST_SW_MODE        VTSS_IOREG(VTSS_TO_CFG,0x19)

/** 
 * \brief
 * Set to enable software pin control mode (Bit banging), when set software
 * has direct control of the SPI interface.
 * This mode is used for writing into flash.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_SPI_MST_SW_MODE . SW_PIN_CTRL_MODE
 */
#define  VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_PIN_CTRL_MODE  VTSS_BIT(13)

/** 
 * \brief
 * Value to drive on SI_Clk output. This field is only used if
 * SW_MODE.SW_PIN_CTRL_MODE is set.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_SPI_MST_SW_MODE . SW_SPI_SCK
 */
#define  VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SCK  VTSS_BIT(12)

/** 
 * \brief
 * Set to enable drive of SI_Clk output. This field is only used if
 * SW_MODE.SW_PIN_CTRL_MODE is set.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_SPI_MST_SW_MODE . SW_SPI_SCK_OE
 */
#define  VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SCK_OE  VTSS_BIT(11)

/** 
 * \brief
 * Value to drive on SI_DO output. This field is only used if
 * SW_MODE.SW_PIN_CTRL_MODE is set.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_SPI_MST_SW_MODE . SW_SPI_SDO
 */
#define  VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDO  VTSS_BIT(10)

/** 
 * \brief
 * Set to enable drive of SI_DO output. This field is only used if
 * SW_MODE.SW_PIN_CTRL_MODE is set.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_SPI_MST_SW_MODE . SW_SPI_SDO_OE
 */
#define  VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDO_OE  VTSS_BIT(9)

/** 
 * \brief
 * Value to drive on SI_nEn outputs, each bit in this field maps to a
 * corresponding chip-select (0 though 3). This field is only used if
 * SW_MODE.SW_PIN_CTRL_MODE is set.
 * Note: Chip selects 1 though 3 are available as alternate GPIO functions.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_SPI_MST_SW_MODE . SW_SPI_CS
 */
#define  VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_CS(x)  VTSS_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_CS     VTSS_ENCODE_BITMASK(5,4)
#define  VTSS_X_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_CS(x)  VTSS_EXTRACT_BITFIELD(x,5,4)

/** 
 * \brief
 * Set to enable drive of SI_nEn outputs, each bit in this field maps to a
 * corresponding chip-select (0 though 3). This field is only used if
 * SW_MODE.SW_PIN_CTRL_MODE is set.
 * Note: Chip selects 1 though 3 are available as alternate GPIO functions.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_SPI_MST_SW_MODE . SW_SPI_CS_OE
 */
#define  VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_CS_OE(x)  VTSS_ENCODE_BITFIELD(x,1,4)
#define  VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_CS_OE     VTSS_ENCODE_BITMASK(1,4)
#define  VTSS_X_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_CS_OE(x)  VTSS_EXTRACT_BITFIELD(x,1,4)

/** 
 * \brief
 * Current value of the SI_DI input.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_SPI_MST_SW_MODE . SW_SPI_SDI
 */
#define  VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDI  VTSS_BIT(0)

/**
 * Register Group: \a ICPU_CFG:MPU8051
 *
 * Configuration/status for the 8051
 */


/** 
 * \brief Status from the 8051
 *
 * \details
 * These read only fields can be used for debugging 8051 programs.
 *
 * Register: \a ICPU_CFG:MPU8051:MPU8051_STAT
 */
#define VTSS_ICPU_CFG_MPU8051_MPU8051_STAT   VTSS_IOREG(VTSS_TO_CFG,0x1b)

/** 
 * \brief
 * Set when the 8051 has stopped itself by setting bit 2 in the PCON SFR
 * register.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MPU8051_STAT . MPU8051_STOP
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_STAT_MPU8051_STOP  VTSS_BIT(8)

/** 
 * \brief
 * A read-only copy of the 8051 GPR register at SFR address 0xF0.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MPU8051_STAT . MPU8051_GPR
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_STAT_MPU8051_GPR(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ICPU_CFG_MPU8051_MPU8051_STAT_MPU8051_GPR     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ICPU_CFG_MPU8051_MPU8051_STAT_MPU8051_GPR(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Configuration of the 8051 memory mapping mechanism
 *
 * \details
 * The MAP_* and MSADDR_* fields in this register is similar to the
 * corresponding 8051 SFR register for control mapping the on-chip memory
 * into the 8051 memory space. These fields must be used to configure 8051
 * memory mapping if the 8051 on-chip memory is loaded manually via an
 * external processor. If the 8051 program itself does loading of on-chip
 * memory then it must instead use the SFR equivalents.
 *
 * Register: \a ICPU_CFG:MPU8051:MPU8051_MMAP
 */
#define VTSS_ICPU_CFG_MPU8051_MPU8051_MMAP   VTSS_IOREG(VTSS_TO_CFG,0x1c)

/** 
 * \brief
 * Configure which half of the on-chip memory an 8051 data-accesses in the
 * low 32KByte memory range (when mapped to on-chip memory) actually use.
 * When set to 0, the low half of the on-chip 64KByte is accessed, when set
 * to 1 the high half is accessed. 
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MPU8051_MMAP . MSADDR_CODE_HIGH
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_MMAP_MSADDR_CODE_HIGH  VTSS_BIT(7)

/** 
 * \brief
 * Configure which half of the on-chip memory an 8051 code-accesses in the
 * low 32KByte memory range (when mapped to on-chip memory) actually use.
 * When set to 0, the low half of the on-chip 64KByte is accessed, when set
 * to 1 the high half is accessed. 
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MPU8051_MMAP . MSADDR_CODE_LOW
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_MMAP_MSADDR_CODE_LOW  VTSS_BIT(6)

/** 
 * \brief
 * Configure which half of the on-chip memory an 8051 data-accesses in the
 * high 32KByte memory range (when mapped to on-chip memory) actually use.
 * When set to 0, the low half of the on-chip 64KByte is accessed, when set
 * to 1 the high half is accessed. 
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MPU8051_MMAP . MSADDR_DATA_HIGH
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_MMAP_MSADDR_DATA_HIGH  VTSS_BIT(5)

/** 
 * \brief
 * Configure which half of the on-chip memory an 8051 data-accesses in the
 * low 32KByte memory range (when mapped to on-chip memory) actually use.
 * When set to 0, the low half of the on-chip 64KByte is accessed, when set
 * to 1 the high half is accessed. 
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MPU8051_MMAP . MSADDR_DATA_LOW
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_MMAP_MSADDR_DATA_LOW  VTSS_BIT(4)

/** 
 * \brief
 * Set to map 8051 code-accesses in the high 32KByte memory range to
 * on-chip memory instead of FLASH.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MPU8051_MMAP . MAP_CODE_HIGH
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_MMAP_MAP_CODE_HIGH  VTSS_BIT(3)

/** 
 * \brief
 * Set to map 8051 code-accesses in the low 32KByte memory range to on-chip
 * memory instead of FLASH.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MPU8051_MMAP . MAP_CODE_LOW
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_MMAP_MAP_CODE_LOW  VTSS_BIT(2)

/** 
 * \brief
 * Set to map 8051 data-accesses in the high 32KByte memory range to
 * on-chip memory instead of FLASH.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MPU8051_MMAP . MAP_DATA_HIGH
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_MMAP_MAP_DATA_HIGH  VTSS_BIT(1)

/** 
 * \brief
 * Set to map 8051 data-accesses in the low 32KByte memory range to on-chip
 * memory instead of FLASH.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MPU8051_MMAP . MAP_DATA_LOW
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_MMAP_MAP_DATA_LOW  VTSS_BIT(0)


/** 
 * \brief Configuration of and status for the load/examine of the onchip 8051 memory.
 *
 * \details
 * Register: \a ICPU_CFG:MPU8051:MEMACC_CTRL
 */
#define VTSS_ICPU_CFG_MPU8051_MEMACC_CTRL    VTSS_IOREG(VTSS_TO_CFG,0x1d)

/** 
 * \brief
 * This field controls if the onchip 8051 memory is either loaded (written)
 * or examined (read).
 *
 * \details 
 * 0: Load data from SBA to onchip memory.
 * 1: Examine data from onchip memory to SBA.
 *
 * Field: ::VTSS_ICPU_CFG_MPU8051_MEMACC_CTRL . MEMACC_EXAMINE
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MEMACC_CTRL_MEMACC_EXAMINE  VTSS_BIT(1)

/** 
 * \brief
 * Set this field to start an access with the parameters specified by
 * MEMACC_CTRL.MEMACC_EXAMINE, MEMACC.MEMACC_START, MEMACC.MEMACC_STOP, and
 * MEMACC_SBA.MEMACC_SBA_START. This field is cleared when the requested
 * number of 32-bit words has been transfered.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MEMACC_CTRL . MEMACC_DO
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MEMACC_CTRL_MEMACC_DO  VTSS_BIT(0)


/** 
 * \brief Configure where in the onchip 8051 memory to load/examine.
 *
 * \details
 * When loading (or examining) onchip 8051 memory, then it is only possible
 * to move 32-bit words. This is why bits [17:16] and [1:0] of this
 * register is not implemented. Setting START and STOP addresses determines
 * how many words that are loaded (or examined). For example, when loading
 * programs of less than 64KBytes, decreasing the stop address will speed
 * up the load time.
 * When manually loading or examining the onchip 8051 memory via an
 * external CPU the data has to be put somewhere in SBA memory space on its
 * way into or out-of the onchip 8051 memory, for this the 8 x 32-bit
 * general purpose registers starting at 0x70000000 is a good choice. By
 * using all (or some) of these registers it is possible to move up to 8
 * 32-bit words to/from the onchip memory per access.
 *
 * Register: \a ICPU_CFG:MPU8051:MEMACC
 */
#define VTSS_ICPU_CFG_MPU8051_MEMACC         VTSS_IOREG(VTSS_TO_CFG,0x1e)

/** 
 * \brief
 * Ending 32-bit word address when loading or examining the onchip 8051
 * memory, the value of this field must be equal to or higher than the
 * MEMACC.MEMACC_START field.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MEMACC . MEMACC_STOP
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MEMACC_MEMACC_STOP(x)  VTSS_ENCODE_BITFIELD(x,18,14)
#define  VTSS_M_ICPU_CFG_MPU8051_MEMACC_MEMACC_STOP     VTSS_ENCODE_BITMASK(18,14)
#define  VTSS_X_ICPU_CFG_MPU8051_MEMACC_MEMACC_STOP(x)  VTSS_EXTRACT_BITFIELD(x,18,14)

/** 
 * \brief
 * Starting 32-bit word address when loading or examining the onchip 8051
 * memory.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MEMACC . MEMACC_START
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MEMACC_MEMACC_START(x)  VTSS_ENCODE_BITFIELD(x,2,14)
#define  VTSS_M_ICPU_CFG_MPU8051_MEMACC_MEMACC_START     VTSS_ENCODE_BITMASK(2,14)
#define  VTSS_X_ICPU_CFG_MPU8051_MEMACC_MEMACC_START(x)  VTSS_EXTRACT_BITFIELD(x,2,14)


/** 
 * \details
 * There is no stop address in the SBA address space. The number of 32-bit
 * words which is moved per access is determined by the MEMACC.MEMACC_START
 * and MEMACC.MEMACC_STOP.
 *
 * Register: \a ICPU_CFG:MPU8051:MEMACC_SBA
 */
#define VTSS_ICPU_CFG_MPU8051_MEMACC_SBA     VTSS_IOREG(VTSS_TO_CFG,0x1f)

/** 
 * \brief
 * This field determines where in the SBA memory space (32-bit alligned)
 * the automatic load/examine mechanims reads/writes data to/from the
 * onchip 8051 memory.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MEMACC_SBA . MEMACC_SBA_START
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MEMACC_SBA_MEMACC_SBA_START(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_ICPU_CFG_MPU8051_MEMACC_SBA_MEMACC_SBA_START     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_ICPU_CFG_MPU8051_MEMACC_SBA_MEMACC_SBA_START(x)  VTSS_EXTRACT_BITFIELD(x,2,30)

/**
 * Register Group: \a ICPU_CFG:INTR
 *
 * Interrupt Registers
 */


/** 
 * \brief Interrupt sticky bits
 *
 * \details
 * Asserted for the active interrupt sources.
 *
 * Register: \a ICPU_CFG:INTR:INTR
 */
#define VTSS_ICPU_CFG_INTR_INTR              VTSS_IOREG(VTSS_TO_CFG,0x21)

/** 
 * \brief
 * This field is set when MIIM master1 interrupt is detected. Clearing of
 * this field is done by writing 1 to this field. This field can only be
 * cleared if the MIIM master1 interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . MIIM1_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_MIIM1_INTR  VTSS_BIT(28)

/** 
 * \brief
 * This field is set when MIIM master0 interrupt is detected. Clearing of
 * this field is done by writing 1 to this field. This field can only be
 * cleared if the MIIM master0 interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . MIIM0_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_MIIM0_INTR  VTSS_BIT(27)

/** 
 * \brief
 * This field is set when PTP-Sync interrupt is detected. Clearing of this
 * field is done by writing 1 to this field. This field can only be cleared
 * if the PTP-Sync interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . PTP_SYNC_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_PTP_SYNC_INTR  VTSS_BIT(26)

/** 
 * \brief
 * This field is set when integrity interrupt is detected. Clearing of this
 * field is done by writing 1 to this field. This field can only be cleared
 * if there are  no longer any pending integrity interrupt event.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . INTEGRITY_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_INTEGRITY_INTR  VTSS_BIT(25)

/** 
 * \brief
 * This field is set when inj-group-4 interrupt is detected. Clearing of
 * this field is done by writing 1 to this field. This field can only be
 * cleared if the inj-group-4 interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . INJ_RDY4_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_INJ_RDY4_INTR  VTSS_BIT(24)

/** 
 * \brief
 * This field is set when inj-group-3 interrupt is detected. Clearing of
 * this field is done by writing 1 to this field. This field can only be
 * cleared if the inj-group-3 interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . INJ_RDY3_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_INJ_RDY3_INTR  VTSS_BIT(23)

/** 
 * \brief
 * This field is set when inj-group-2 interrupt is detected. Clearing of
 * this field is done by writing 1 to this field. This field can only be
 * cleared if the inj-group-2 interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . INJ_RDY2_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_INJ_RDY2_INTR  VTSS_BIT(22)

/** 
 * \brief
 * This field is set when inj-group-1 interrupt is detected. Clearing of
 * this field is done by writing 1 to this field. This field can only be
 * cleared if the inj-group-1 interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . INJ_RDY1_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_INJ_RDY1_INTR  VTSS_BIT(21)

/** 
 * \brief
 * This field is set when inj-group-0 interrupt is detected. Clearing of
 * this field is done by writing 1 to this field. This field can only be
 * cleared if the inj-group-0 interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . INJ_RDY0_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_INJ_RDY0_INTR  VTSS_BIT(20)

/** 
 * \brief
 * This field is set when xtr-group-3 interrupt is detected. Clearing of
 * this field is done by writing 1 to this field. This field can only be
 * cleared if the xtr-group-3 interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . XTR_RDY3_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_XTR_RDY3_INTR  VTSS_BIT(19)

/** 
 * \brief
 * This field is set when xtr-group-2 interrupt is detected. Clearing of
 * this field is done by writing 1 to this field. This field can only be
 * cleared if the xtr-group-2 interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . XTR_RDY2_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_XTR_RDY2_INTR  VTSS_BIT(18)

/** 
 * \brief
 * This field is set when xtr-group-1 interrupt is detected. Clearing of
 * this field is done by writing 1 to this field. This field can only be
 * cleared if the xtr-group-1 interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . XTR_RDY1_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_XTR_RDY1_INTR  VTSS_BIT(17)

/** 
 * \brief
 * This field is set when xtr-group-0 interrupt is detected. Clearing of
 * this field is done by writing 1 to this field. This field can only be
 * cleared if the xtr-group-0 interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . XTR_RDY0_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_XTR_RDY0_INTR  VTSS_BIT(16)

/** 
 * \brief
 * This field is set when Analyzer interrupt is detected. Clearing of this
 * field is done by writing 1 to this field. This field can only be cleared
 * if the Analyzer interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . BLK_ANA_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_BLK_ANA_INTR  VTSS_BIT(15)

/** 
 * \brief
 * This field is set when interrupt from any device (port) is detected.
 * Clearing of this field is done by writing 1 to this field. This field
 * can only be cleared if there is still a pending interrupt from any
 * device.
 * This is a cascaded interrupt, read DEV_IDENT to see which device(s) that
 * is/are currently interrupting.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . DEV_ALL_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_DEV_ALL_INTR  VTSS_BIT(14)

/** 
 * \brief
 * This field is set when Serial-GPIO interrupt is detected. Clearing of
 * this field is done by writing 1 to this field. This field can only be
 * cleared if the Serial-GPIO interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . SGPIO_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_SGPIO_INTR  VTSS_BIT(13)

/** 
 * \brief
 * This field is set when Parallel-GPIO interrupt is detected. Clearing of
 * this field is done by writing 1 to this field. This field can only be
 * cleared if the Parallel-GPIO interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . GPIO_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_GPIO_INTR  VTSS_BIT(12)

/** 
 * \brief
 * This field is set when TWI interrupt is detected. Clearing of this field
 * is done by writing 1 to this field. This field can only be cleared if
 * the TWI interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . TWI_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_TWI_INTR   VTSS_BIT(11)

/** 
 * \brief
 * This field is set when FDMA interrupt is detected. Clearing of this
 * field is done by writing 1 to this field. This field can only be cleared
 * if the FDMA interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . FDMA_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_FDMA_INTR  VTSS_BIT(10)

/** 
 * \brief
 * This field is set when Timer-2 interrupt is detected. Clearing of this
 * field is done by writing 1 to this field. This field can only be cleared
 * if the Timer-2 interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . TIMER2_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_TIMER2_INTR  VTSS_BIT(9)

/** 
 * \brief
 * This field is set when Timer-1 interrupt is detected. Clearing of this
 * field is done by writing 1 to this field. This field can only be cleared
 * if the Timer-1 interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . TIMER1_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_TIMER1_INTR  VTSS_BIT(8)

/** 
 * \brief
 * This field is set when Timer-0 interrupt is detected. Clearing of this
 * field is done by writing 1 to this field. This field can only be cleared
 * if the Timer-0 interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . TIMER0_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_TIMER0_INTR  VTSS_BIT(7)

/** 
 * \brief
 * This field is set when UART interrupt is detected. Clearing of this
 * field is done by writing 1 to this field. This field can only be cleared
 * if the UART interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . UART_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_UART_INTR  VTSS_BIT(6)

/** 
 * \brief
 * This field is set when PI-Slow-Done-1 interrupt is detected. Clearing of
 * this field is done by writing 1 to this field. This field can only be
 * cleared if the PI-Slow-Done-1 interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . PI_SD1_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_PI_SD1_INTR  VTSS_BIT(5)

/** 
 * \brief
 * This field is set when PI-Slow-Done-0 interrupt is detected. Clearing of
 * this field is done by writing 1 to this field. This field can only be
 * cleared if the PI-Slow-Done-0 interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . PI_SD0_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_PI_SD0_INTR  VTSS_BIT(4)

/** 
 * \brief
 * This field is set when SW1 interrupt is detected. Clearing of this field
 * is done by writing 1 to this field. This field can only be cleared if
 * the SW1 interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . SW1_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_SW1_INTR   VTSS_BIT(3)

/** 
 * \brief
 * This field is set when SW0 interrupt is detected. Clearing of this field
 * is done by writing 1 to this field. This field can only be cleared if
 * the SW0 interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . SW0_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_SW0_INTR   VTSS_BIT(2)

/** 
 * \brief
 * This field is set when EXT_IRQ1 interrupt is detected. Clearing of this
 * field is done by writing 1 to this field. This field can only be cleared
 * if the EXT_IRQ1 interrupt event is no longer active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . EXT_IRQ1_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_EXT_IRQ1_INTR  VTSS_BIT(1)

/** 
 * \brief
 * This field is set when EXT_IRQ0 interrupt is detected. Clearing of this
 * field is done by writing 1 to this field. This field can only be cleared
 * if the EXT_IRQ0 interrupt event is no longer active.

 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR . EXT_IRQ0_INTR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_EXT_IRQ0_INTR  VTSS_BIT(0)


/** 
 * \brief Interrupt enable
 *
 * \details
 * Controls if active interrupt indications (from INTR) can propagate to
 * their destinations. In a multi-threaded environment, or with more than
 * one active processor the INTR_ENA_SET and INTR_ENA_CLR registers can be
 * used for atomic modifications of this register. Writing 1 to any bit(s)
 * in the INTR_ENA_SET register will set the corresponding bit(s) in this
 * register, Writing 1 to any bit in the INTR_ENA_CLR register will clear
 * the corresponding bit(s) in this register.
 *
 * Register: \a ICPU_CFG:INTR:INTR_ENA
 */
#define VTSS_ICPU_CFG_INTR_INTR_ENA          VTSS_IOREG(VTSS_TO_CFG,0x22)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . MIIM1_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_MIIM1_INTR_ENA  VTSS_BIT(28)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . MIIM0_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_MIIM0_INTR_ENA  VTSS_BIT(27)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . PTP_SYNC_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_PTP_SYNC_INTR_ENA  VTSS_BIT(26)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . INTEGRITY_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_INTEGRITY_INTR_ENA  VTSS_BIT(25)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . INJ_RDY4_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_INJ_RDY4_INTR_ENA  VTSS_BIT(24)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . INJ_RDY3_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_INJ_RDY3_INTR_ENA  VTSS_BIT(23)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . INJ_RDY2_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_INJ_RDY2_INTR_ENA  VTSS_BIT(22)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . INJ_RDY1_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_INJ_RDY1_INTR_ENA  VTSS_BIT(21)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . INJ_RDY0_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_INJ_RDY0_INTR_ENA  VTSS_BIT(20)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . XTR_RDY3_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_XTR_RDY3_INTR_ENA  VTSS_BIT(19)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . XTR_RDY2_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_XTR_RDY2_INTR_ENA  VTSS_BIT(18)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . XTR_RDY1_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_XTR_RDY1_INTR_ENA  VTSS_BIT(17)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . XTR_RDY0_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_XTR_RDY0_INTR_ENA  VTSS_BIT(16)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . BLK_ANA_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_BLK_ANA_INTR_ENA  VTSS_BIT(15)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . DEV_ALL_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_DEV_ALL_INTR_ENA  VTSS_BIT(14)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . SGPIO_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SGPIO_INTR_ENA  VTSS_BIT(13)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . GPIO_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_GPIO_INTR_ENA  VTSS_BIT(12)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . TWI_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_TWI_INTR_ENA  VTSS_BIT(11)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . FDMA_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_FDMA_INTR_ENA  VTSS_BIT(10)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . TIMER2_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_TIMER2_INTR_ENA  VTSS_BIT(9)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . TIMER1_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_TIMER1_INTR_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . TIMER0_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_TIMER0_INTR_ENA  VTSS_BIT(7)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . UART_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_UART_INTR_ENA  VTSS_BIT(6)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . PI_SD1_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_PI_SD1_INTR_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . PI_SD0_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_PI_SD0_INTR_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . SW1_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SW1_INTR_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . SW0_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SW0_INTR_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . EXT_IRQ1_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_EXT_IRQ1_INTR_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Set this field to enable the interrupt to propagate to its destination.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . EXT_IRQ0_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_EXT_IRQ0_INTR_ENA  VTSS_BIT(0)


/** 
 * \brief Clear interrupt enable
 *
 * \details
 * Register: \a ICPU_CFG:INTR:INTR_ENA_CLR
 */
#define VTSS_ICPU_CFG_INTR_INTR_ENA_CLR      VTSS_IOREG(VTSS_TO_CFG,0x23)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . MIIM1_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_MIIM1_INTR_ENA_CLR  VTSS_BIT(28)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . MIIM0_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_MIIM0_INTR_ENA_CLR  VTSS_BIT(27)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . PTP_SYNC_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_PTP_SYNC_INTR_ENA_CLR  VTSS_BIT(26)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . INTEGRITY_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_INTEGRITY_INTR_ENA_CLR  VTSS_BIT(25)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . INJ_RDY4_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_INJ_RDY4_INTR_ENA_CLR  VTSS_BIT(24)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . INJ_RDY3_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_INJ_RDY3_INTR_ENA_CLR  VTSS_BIT(23)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . INJ_RDY2_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_INJ_RDY2_INTR_ENA_CLR  VTSS_BIT(22)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . INJ_RDY1_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_INJ_RDY1_INTR_ENA_CLR  VTSS_BIT(21)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . INJ_RDY0_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_INJ_RDY0_INTR_ENA_CLR  VTSS_BIT(20)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . XTR_RDY3_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_XTR_RDY3_INTR_ENA_CLR  VTSS_BIT(19)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . XTR_RDY2_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_XTR_RDY2_INTR_ENA_CLR  VTSS_BIT(18)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . XTR_RDY1_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_XTR_RDY1_INTR_ENA_CLR  VTSS_BIT(17)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . XTR_RDY0_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_XTR_RDY0_INTR_ENA_CLR  VTSS_BIT(16)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . BLK_ANA_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_BLK_ANA_INTR_ENA_CLR  VTSS_BIT(15)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . DEV_ALL_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_DEV_ALL_INTR_ENA_CLR  VTSS_BIT(14)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . SGPIO_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_SGPIO_INTR_ENA_CLR  VTSS_BIT(13)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . GPIO_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_GPIO_INTR_ENA_CLR  VTSS_BIT(12)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . TWI_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_TWI_INTR_ENA_CLR  VTSS_BIT(11)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . FDMA_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_FDMA_INTR_ENA_CLR  VTSS_BIT(10)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . TIMER2_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_TIMER2_INTR_ENA_CLR  VTSS_BIT(9)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . TIMER1_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_TIMER1_INTR_ENA_CLR  VTSS_BIT(8)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . TIMER0_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_TIMER0_INTR_ENA_CLR  VTSS_BIT(7)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . UART_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_UART_INTR_ENA_CLR  VTSS_BIT(6)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . PI_SD1_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_PI_SD1_INTR_ENA_CLR  VTSS_BIT(5)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . PI_SD0_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_PI_SD0_INTR_ENA_CLR  VTSS_BIT(4)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . SW1_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_SW1_INTR_ENA_CLR  VTSS_BIT(3)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . SW0_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_SW0_INTR_ENA_CLR  VTSS_BIT(2)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . EXT_IRQ1_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_EXT_IRQ1_INTR_ENA_CLR  VTSS_BIT(1)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . EXT_IRQ0_INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_EXT_IRQ0_INTR_ENA_CLR  VTSS_BIT(0)


/** 
 * \brief Set interrupt enable
 *
 * \details
 * Register: \a ICPU_CFG:INTR:INTR_ENA_SET
 */
#define VTSS_ICPU_CFG_INTR_INTR_ENA_SET      VTSS_IOREG(VTSS_TO_CFG,0x24)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . MIIM1_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_MIIM1_INTR_ENA_SET  VTSS_BIT(28)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . MIIM0_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_MIIM0_INTR_ENA_SET  VTSS_BIT(27)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . PTP_SYNC_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_PTP_SYNC_INTR_ENA_SET  VTSS_BIT(26)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . INTEGRITY_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_INTEGRITY_INTR_ENA_SET  VTSS_BIT(25)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . INJ_RDY4_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_INJ_RDY4_INTR_ENA_SET  VTSS_BIT(24)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . INJ_RDY3_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_INJ_RDY3_INTR_ENA_SET  VTSS_BIT(23)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . INJ_RDY2_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_INJ_RDY2_INTR_ENA_SET  VTSS_BIT(22)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . INJ_RDY1_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_INJ_RDY1_INTR_ENA_SET  VTSS_BIT(21)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . INJ_RDY0_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_INJ_RDY0_INTR_ENA_SET  VTSS_BIT(20)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . XTR_RDY3_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_XTR_RDY3_INTR_ENA_SET  VTSS_BIT(19)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . XTR_RDY2_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_XTR_RDY2_INTR_ENA_SET  VTSS_BIT(18)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . XTR_RDY1_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_XTR_RDY1_INTR_ENA_SET  VTSS_BIT(17)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . XTR_RDY0_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_XTR_RDY0_INTR_ENA_SET  VTSS_BIT(16)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . BLK_ANA_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_BLK_ANA_INTR_ENA_SET  VTSS_BIT(15)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . DEV_ALL_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_DEV_ALL_INTR_ENA_SET  VTSS_BIT(14)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . SGPIO_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_SGPIO_INTR_ENA_SET  VTSS_BIT(13)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . GPIO_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_GPIO_INTR_ENA_SET  VTSS_BIT(12)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . TWI_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_TWI_INTR_ENA_SET  VTSS_BIT(11)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . FDMA_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_FDMA_INTR_ENA_SET  VTSS_BIT(10)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . TIMER2_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_TIMER2_INTR_ENA_SET  VTSS_BIT(9)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . TIMER1_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_TIMER1_INTR_ENA_SET  VTSS_BIT(8)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . TIMER0_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_TIMER0_INTR_ENA_SET  VTSS_BIT(7)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . UART_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_UART_INTR_ENA_SET  VTSS_BIT(6)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . PI_SD1_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_PI_SD1_INTR_ENA_SET  VTSS_BIT(5)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . PI_SD0_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_PI_SD0_INTR_ENA_SET  VTSS_BIT(4)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . SW1_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_SW1_INTR_ENA_SET  VTSS_BIT(3)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . SW0_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_SW0_INTR_ENA_SET  VTSS_BIT(2)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . EXT_IRQ1_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_EXT_IRQ1_INTR_ENA_SET  VTSS_BIT(1)

/** 
 * \brief
 * Set this field to set corresponding interrupt enable in INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . EXT_IRQ0_INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_EXT_IRQ0_INTR_ENA_SET  VTSS_BIT(0)


/** 
 * \brief Raw of interrupt source
 *
 * \details
 * Shows the current value of the interrupt source to the interrupt
 * controller (interrupts are active high). External interrupt inputs are
 * corrected for polarity before being presented in this register.
 *
 * Register: \a ICPU_CFG:INTR:INTR_RAW
 */
#define VTSS_ICPU_CFG_INTR_INTR_RAW          VTSS_IOREG(VTSS_TO_CFG,0x25)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . MIIM1_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_MIIM1_RAW  VTSS_BIT(28)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . MIIM0_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_MIIM0_RAW  VTSS_BIT(27)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . PTP_SYNC_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_PTP_SYNC_RAW  VTSS_BIT(26)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . INTEGRITY_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_INTEGRITY_RAW  VTSS_BIT(25)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . INJ_RDY4_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_INJ_RDY4_RAW  VTSS_BIT(24)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . INJ_RDY3_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_INJ_RDY3_RAW  VTSS_BIT(23)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . INJ_RDY2_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_INJ_RDY2_RAW  VTSS_BIT(22)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . INJ_RDY1_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_INJ_RDY1_RAW  VTSS_BIT(21)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . INJ_RDY0_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_INJ_RDY0_RAW  VTSS_BIT(20)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . XTR_RDY3_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_XTR_RDY3_RAW  VTSS_BIT(19)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . XTR_RDY2_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_XTR_RDY2_RAW  VTSS_BIT(18)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . XTR_RDY1_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_XTR_RDY1_RAW  VTSS_BIT(17)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . XTR_RDY0_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_XTR_RDY0_RAW  VTSS_BIT(16)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . BLK_ANA_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_BLK_ANA_RAW  VTSS_BIT(15)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . DEV_ALL_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_DEV_ALL_RAW  VTSS_BIT(14)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . SGPIO_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_SGPIO_RAW  VTSS_BIT(13)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . GPIO_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_GPIO_RAW  VTSS_BIT(12)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . TWI_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_TWI_RAW  VTSS_BIT(11)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . FDMA_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_FDMA_RAW  VTSS_BIT(10)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . TIMER2_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_TIMER2_RAW  VTSS_BIT(9)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . TIMER1_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_TIMER1_RAW  VTSS_BIT(8)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . TIMER0_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_TIMER0_RAW  VTSS_BIT(7)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . UART_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_UART_RAW  VTSS_BIT(6)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . PI_SD1_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_PI_SD1_RAW  VTSS_BIT(5)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . PI_SD0_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_PI_SD0_RAW  VTSS_BIT(4)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . SW1_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_SW1_RAW  VTSS_BIT(3)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . SW0_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_SW0_RAW  VTSS_BIT(2)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller, is
 * already corrected for polarity as configured vua
 * EXT_IRQ1_INTR_CFG.EXT_IRQ1_INTR_POL.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . EXT_IRQ1_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_EXT_IRQ1_RAW  VTSS_BIT(1)

/** 
 * \brief
 * Current value of interrupt source input to the interrupt controller, is
 * already corrected for polarity as configured vua
 * EXT_IRQ0_INTR_CFG.EXT_IRQ0_INTR_POL.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . EXT_IRQ0_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_EXT_IRQ0_RAW  VTSS_BIT(0)


/** 
 * \brief Enable of ICPU_IRQ0 interrupt
 *
 * \details
 * Register: \a ICPU_CFG:INTR:ICPU_IRQ0_ENA
 */
#define VTSS_ICPU_CFG_INTR_ICPU_IRQ0_ENA     VTSS_IOREG(VTSS_TO_CFG,0x26)

/** 
 * \brief
 * Enables ICPU_IRQ0 interrupt
 *
 * \details 
 * 0: Interrupt is disabled
 * 1: Interrupt is enabled
 *
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_ENA . ICPU_IRQ0_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_ENA_ICPU_IRQ0_ENA  VTSS_BIT(0)


/** 
 * \brief Sources of ICPU_IRQ0 interrupt
 *
 * \details
 * Identifies the source(s) of an active interrupt on output interrupt:
 * ICPU_IRQ0. All asserted interrupts are shown as active high.
 *
 * Register: \a ICPU_CFG:INTR:ICPU_IRQ0_IDENT
 */
#define VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT   VTSS_IOREG(VTSS_TO_CFG,0x27)

/** 
 * \brief
 * Set when MIIM1 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_MIIM1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_MIIM1_IDENT  VTSS_BIT(28)

/** 
 * \brief
 * Set when MIIM0 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_MIIM0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_MIIM0_IDENT  VTSS_BIT(27)

/** 
 * \brief
 * Set when PTP_SYNC interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_PTP_SYNC_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_PTP_SYNC_IDENT  VTSS_BIT(26)

/** 
 * \brief
 * Set when INTEGRITY interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_INTEGRITY_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_INTEGRITY_IDENT  VTSS_BIT(25)

/** 
 * \brief
 * Set when INJ_RDY4 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_INJ_RDY4_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_INJ_RDY4_IDENT  VTSS_BIT(24)

/** 
 * \brief
 * Set when INJ_RDY3 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_INJ_RDY3_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_INJ_RDY3_IDENT  VTSS_BIT(23)

/** 
 * \brief
 * Set when INJ_RDY2 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_INJ_RDY2_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_INJ_RDY2_IDENT  VTSS_BIT(22)

/** 
 * \brief
 * Set when INJ_RDY1 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_INJ_RDY1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_INJ_RDY1_IDENT  VTSS_BIT(21)

/** 
 * \brief
 * Set when INJ_RDY0 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_INJ_RDY0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_INJ_RDY0_IDENT  VTSS_BIT(20)

/** 
 * \brief
 * Set when XTR_RDY3 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_XTR_RDY3_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_XTR_RDY3_IDENT  VTSS_BIT(19)

/** 
 * \brief
 * Set when XTR_RDY2 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_XTR_RDY2_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_XTR_RDY2_IDENT  VTSS_BIT(18)

/** 
 * \brief
 * Set when XTR_RDY1 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_XTR_RDY1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_XTR_RDY1_IDENT  VTSS_BIT(17)

/** 
 * \brief
 * Set when XTR_RDY0 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_XTR_RDY0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_XTR_RDY0_IDENT  VTSS_BIT(16)

/** 
 * \brief
 * Set when BLK_ANA interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_BLK_ANA_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_BLK_ANA_IDENT  VTSS_BIT(15)

/** 
 * \brief
 * Set when DEV_ALL interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_DEV_ALL_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_DEV_ALL_IDENT  VTSS_BIT(14)

/** 
 * \brief
 * Set when SGPIO interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_SGPIO_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_SGPIO_IDENT  VTSS_BIT(13)

/** 
 * \brief
 * Set when GPIO interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_GPIO_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_GPIO_IDENT  VTSS_BIT(12)

/** 
 * \brief
 * Set when TWI interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_TWI_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_TWI_IDENT  VTSS_BIT(11)

/** 
 * \brief
 * Set when FDMA interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_FDMA_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_FDMA_IDENT  VTSS_BIT(10)

/** 
 * \brief
 * Set when TIMER2 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_TIMER2_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_TIMER2_IDENT  VTSS_BIT(9)

/** 
 * \brief
 * Set when TIMER1 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_TIMER1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_TIMER1_IDENT  VTSS_BIT(8)

/** 
 * \brief
 * Set when TIMER0 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_TIMER0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_TIMER0_IDENT  VTSS_BIT(7)

/** 
 * \brief
 * Set when UART interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_UART_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_UART_IDENT  VTSS_BIT(6)

/** 
 * \brief
 * Set when PI_SD1 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_PI_SD1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_PI_SD1_IDENT  VTSS_BIT(5)

/** 
 * \brief
 * Set when PI_SD0 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_PI_SD0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_PI_SD0_IDENT  VTSS_BIT(4)

/** 
 * \brief
 * Set when SW1 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_SW1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_SW1_IDENT  VTSS_BIT(3)

/** 
 * \brief
 * Set when SW0 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_SW0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_SW0_IDENT  VTSS_BIT(2)

/** 
 * \brief
 * Set when EXT_IRQ1 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_EXT_IRQ1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_EXT_IRQ1_IDENT  VTSS_BIT(1)

/** 
 * \brief
 * Set when EXT_IRQ0 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ0_IDENT . ICPU_IRQ0_EXT_IRQ0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ0_IDENT_ICPU_IRQ0_EXT_IRQ0_IDENT  VTSS_BIT(0)


/** 
 * \brief Enable of ICPU_IRQ1 interrupt
 *
 * \details
 * Register: \a ICPU_CFG:INTR:ICPU_IRQ1_ENA
 */
#define VTSS_ICPU_CFG_INTR_ICPU_IRQ1_ENA     VTSS_IOREG(VTSS_TO_CFG,0x28)

/** 
 * \brief
 * Enables ICPU_IRQ1 interrupt
 *
 * \details 
 * 0: Interrupt is disabled
 * 1: Interrupt is enabled
 *
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_ENA . ICPU_IRQ1_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_ENA_ICPU_IRQ1_ENA  VTSS_BIT(0)


/** 
 * \brief Sources of ICPU_IRQ1 interrupt
 *
 * \details
 * Identifies the source(s) of an active interrupt on output interrupt:
 * ICPU_IRQ1. All asserted interrupts are shown as active high.
 *
 * Register: \a ICPU_CFG:INTR:ICPU_IRQ1_IDENT
 */
#define VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT   VTSS_IOREG(VTSS_TO_CFG,0x29)

/** 
 * \brief
 * Set when MIIM1 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_MIIM1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_MIIM1_IDENT  VTSS_BIT(28)

/** 
 * \brief
 * Set when MIIM0 interrupt is a source of the ICPU_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_MIIM0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_MIIM0_IDENT  VTSS_BIT(27)

/** 
 * \brief
 * Set when PTP_SYNC interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_PTP_SYNC_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_PTP_SYNC_IDENT  VTSS_BIT(26)

/** 
 * \brief
 * Set when INTEGRITY interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_INTEGRITY_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_INTEGRITY_IDENT  VTSS_BIT(25)

/** 
 * \brief
 * Set when INJ_RDY4 interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_INJ_RDY4_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_INJ_RDY4_IDENT  VTSS_BIT(24)

/** 
 * \brief
 * Set when INJ_RDY3 interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_INJ_RDY3_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_INJ_RDY3_IDENT  VTSS_BIT(23)

/** 
 * \brief
 * Set when INJ_RDY2 interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_INJ_RDY2_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_INJ_RDY2_IDENT  VTSS_BIT(22)

/** 
 * \brief
 * Set when INJ_RDY1 interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_INJ_RDY1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_INJ_RDY1_IDENT  VTSS_BIT(21)

/** 
 * \brief
 * Set when INJ_RDY0 interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_INJ_RDY0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_INJ_RDY0_IDENT  VTSS_BIT(20)

/** 
 * \brief
 * Set when XTR_RDY3 interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_XTR_RDY3_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_XTR_RDY3_IDENT  VTSS_BIT(19)

/** 
 * \brief
 * Set when XTR_RDY2 interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_XTR_RDY2_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_XTR_RDY2_IDENT  VTSS_BIT(18)

/** 
 * \brief
 * Set when XTR_RDY1 interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_XTR_RDY1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_XTR_RDY1_IDENT  VTSS_BIT(17)

/** 
 * \brief
 * Set when XTR_RDY0 interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_XTR_RDY0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_XTR_RDY0_IDENT  VTSS_BIT(16)

/** 
 * \brief
 * Set when BLK_ANA interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_BLK_ANA_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_BLK_ANA_IDENT  VTSS_BIT(15)

/** 
 * \brief
 * Set when DEV_ALL interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_DEV_ALL_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_DEV_ALL_IDENT  VTSS_BIT(14)

/** 
 * \brief
 * Set when SGPIO interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_SGPIO_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_SGPIO_IDENT  VTSS_BIT(13)

/** 
 * \brief
 * Set when GPIO interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_GPIO_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_GPIO_IDENT  VTSS_BIT(12)

/** 
 * \brief
 * Set when TWI interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_TWI_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_TWI_IDENT  VTSS_BIT(11)

/** 
 * \brief
 * Set when FDMA interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_FDMA_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_FDMA_IDENT  VTSS_BIT(10)

/** 
 * \brief
 * Set when TIMER2 interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_TIMER2_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_TIMER2_IDENT  VTSS_BIT(9)

/** 
 * \brief
 * Set when TIMER1 interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_TIMER1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_TIMER1_IDENT  VTSS_BIT(8)

/** 
 * \brief
 * Set when TIMER0 interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_TIMER0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_TIMER0_IDENT  VTSS_BIT(7)

/** 
 * \brief
 * Set when UART interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_UART_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_UART_IDENT  VTSS_BIT(6)

/** 
 * \brief
 * Set when PI_SD1 interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_PI_SD1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_PI_SD1_IDENT  VTSS_BIT(5)

/** 
 * \brief
 * Set when PI_SD0 interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_PI_SD0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_PI_SD0_IDENT  VTSS_BIT(4)

/** 
 * \brief
 * Set when SW1 interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_SW1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_SW1_IDENT  VTSS_BIT(3)

/** 
 * \brief
 * Set when SW0 interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_SW0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_SW0_IDENT  VTSS_BIT(2)

/** 
 * \brief
 * Set when EXT_IRQ1 interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_EXT_IRQ1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_EXT_IRQ1_IDENT  VTSS_BIT(1)

/** 
 * \brief
 * Set when EXT_IRQ0 interrupt is a source of the ICPU_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_ICPU_IRQ1_IDENT . ICPU_IRQ1_EXT_IRQ0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_ICPU_IRQ1_IDENT_ICPU_IRQ1_EXT_IRQ0_IDENT  VTSS_BIT(0)


/** 
 * \brief Enable of EXT_IRQ0 interrupt
 *
 * \details
 * Register: \a ICPU_CFG:INTR:EXT_IRQ0_ENA
 */
#define VTSS_ICPU_CFG_INTR_EXT_IRQ0_ENA      VTSS_IOREG(VTSS_TO_CFG,0x2a)

/** 
 * \brief
 * Enables EXT_IRQ0 interrupt
 *
 * \details 
 * 0: Interrupt is disabled
 * 1: Interrupt is enabled
 *
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_ENA . EXT_IRQ0_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_ENA_EXT_IRQ0_ENA  VTSS_BIT(0)


/** 
 * \brief Sources of EXT_IRQ0 interrupt
 *
 * \details
 * Identifies the source(s) of an active interrupt on output interrupt:
 * EXT_IRQ0. All asserted interrupts are shown as active high.
 *
 * Register: \a ICPU_CFG:INTR:EXT_IRQ0_IDENT
 */
#define VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT    VTSS_IOREG(VTSS_TO_CFG,0x2b)

/** 
 * \brief
 * Set when MIIM1 interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_MIIM1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_MIIM1_IDENT  VTSS_BIT(28)

/** 
 * \brief
 * Set when MIIM0 interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_MIIM0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_MIIM0_IDENT  VTSS_BIT(27)

/** 
 * \brief
 * Set when PTP_SYNC interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_PTP_SYNC_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_PTP_SYNC_IDENT  VTSS_BIT(26)

/** 
 * \brief
 * Set when INTEGRITY interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_INTEGRITY_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_INTEGRITY_IDENT  VTSS_BIT(25)

/** 
 * \brief
 * Set when INJ_RDY4 interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_INJ_RDY4_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_INJ_RDY4_IDENT  VTSS_BIT(24)

/** 
 * \brief
 * Set when INJ_RDY3 interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_INJ_RDY3_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_INJ_RDY3_IDENT  VTSS_BIT(23)

/** 
 * \brief
 * Set when INJ_RDY2 interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_INJ_RDY2_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_INJ_RDY2_IDENT  VTSS_BIT(22)

/** 
 * \brief
 * Set when INJ_RDY1 interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_INJ_RDY1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_INJ_RDY1_IDENT  VTSS_BIT(21)

/** 
 * \brief
 * Set when INJ_RDY0 interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_INJ_RDY0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_INJ_RDY0_IDENT  VTSS_BIT(20)

/** 
 * \brief
 * Set when XTR_RDY3 interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_XTR_RDY3_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_XTR_RDY3_IDENT  VTSS_BIT(19)

/** 
 * \brief
 * Set when XTR_RDY2 interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_XTR_RDY2_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_XTR_RDY2_IDENT  VTSS_BIT(18)

/** 
 * \brief
 * Set when XTR_RDY1 interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_XTR_RDY1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_XTR_RDY1_IDENT  VTSS_BIT(17)

/** 
 * \brief
 * Set when XTR_RDY0 interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_XTR_RDY0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_XTR_RDY0_IDENT  VTSS_BIT(16)

/** 
 * \brief
 * Set when BLK_ANA interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_BLK_ANA_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_BLK_ANA_IDENT  VTSS_BIT(15)

/** 
 * \brief
 * Set when DEV_ALL interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_DEV_ALL_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_DEV_ALL_IDENT  VTSS_BIT(14)

/** 
 * \brief
 * Set when SGPIO interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_SGPIO_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_SGPIO_IDENT  VTSS_BIT(13)

/** 
 * \brief
 * Set when GPIO interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_GPIO_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_GPIO_IDENT  VTSS_BIT(12)

/** 
 * \brief
 * Set when TWI interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_TWI_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_TWI_IDENT  VTSS_BIT(11)

/** 
 * \brief
 * Set when FDMA interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_FDMA_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_FDMA_IDENT  VTSS_BIT(10)

/** 
 * \brief
 * Set when TIMER2 interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_TIMER2_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_TIMER2_IDENT  VTSS_BIT(9)

/** 
 * \brief
 * Set when TIMER1 interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_TIMER1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_TIMER1_IDENT  VTSS_BIT(8)

/** 
 * \brief
 * Set when TIMER0 interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_TIMER0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_TIMER0_IDENT  VTSS_BIT(7)

/** 
 * \brief
 * Set when UART interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_UART_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_UART_IDENT  VTSS_BIT(6)

/** 
 * \brief
 * Set when PI_SD1 interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_PI_SD1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_PI_SD1_IDENT  VTSS_BIT(5)

/** 
 * \brief
 * Set when PI_SD0 interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_PI_SD0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_PI_SD0_IDENT  VTSS_BIT(4)

/** 
 * \brief
 * Set when SW1 interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_SW1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_SW1_IDENT  VTSS_BIT(3)

/** 
 * \brief
 * Set when SW0 interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_SW0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_SW0_IDENT  VTSS_BIT(2)

/** 
 * \brief
 * Set when EXT_IRQ1 interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_EXT_IRQ1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_EXT_IRQ1_IDENT  VTSS_BIT(1)

/** 
 * \brief
 * Set when EXT_IRQ0 interrupt is a source of the EXT_IRQ0 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_IDENT . EXT_IRQ0_EXT_IRQ0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_IDENT_EXT_IRQ0_EXT_IRQ0_IDENT  VTSS_BIT(0)


/** 
 * \brief Enable of EXT_IRQ1 interrupt
 *
 * \details
 * Register: \a ICPU_CFG:INTR:EXT_IRQ1_ENA
 */
#define VTSS_ICPU_CFG_INTR_EXT_IRQ1_ENA      VTSS_IOREG(VTSS_TO_CFG,0x2c)

/** 
 * \brief
 * Enables EXT_IRQ1 interrupt
 *
 * \details 
 * 0: Interrupt is disabled
 * 1: Interrupt is enabled
 *
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_ENA . EXT_IRQ1_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_ENA_EXT_IRQ1_ENA  VTSS_BIT(0)


/** 
 * \brief Sources of EXT_IRQ1 interrupt
 *
 * \details
 * Identifies the source(s) of an active interrupt on output interrupt:
 * EXT_IRQ1. All asserted interrupts are shown as active high.
 *
 * Register: \a ICPU_CFG:INTR:EXT_IRQ1_IDENT
 */
#define VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT    VTSS_IOREG(VTSS_TO_CFG,0x2d)

/** 
 * \brief
 * Set when MIIM1 interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_MIIM1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_MIIM1_IDENT  VTSS_BIT(28)

/** 
 * \brief
 * Set when MIIM0 interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_MIIM0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_MIIM0_IDENT  VTSS_BIT(27)

/** 
 * \brief
 * Set when PTP_SYNC interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_PTP_SYNC_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_PTP_SYNC_IDENT  VTSS_BIT(26)

/** 
 * \brief
 * Set when INTEGRITY interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_INTEGRITY_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_INTEGRITY_IDENT  VTSS_BIT(25)

/** 
 * \brief
 * Set when INJ_RDY4 interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_INJ_RDY4_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_INJ_RDY4_IDENT  VTSS_BIT(24)

/** 
 * \brief
 * Set when INJ_RDY3 interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_INJ_RDY3_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_INJ_RDY3_IDENT  VTSS_BIT(23)

/** 
 * \brief
 * Set when INJ_RDY2 interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_INJ_RDY2_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_INJ_RDY2_IDENT  VTSS_BIT(22)

/** 
 * \brief
 * Set when INJ_RDY1 interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_INJ_RDY1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_INJ_RDY1_IDENT  VTSS_BIT(21)

/** 
 * \brief
 * Set when INJ_RDY0 interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_INJ_RDY0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_INJ_RDY0_IDENT  VTSS_BIT(20)

/** 
 * \brief
 * Set when XTR_RDY3 interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_XTR_RDY3_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_XTR_RDY3_IDENT  VTSS_BIT(19)

/** 
 * \brief
 * Set when XTR_RDY2 interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_XTR_RDY2_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_XTR_RDY2_IDENT  VTSS_BIT(18)

/** 
 * \brief
 * Set when XTR_RDY1 interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_XTR_RDY1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_XTR_RDY1_IDENT  VTSS_BIT(17)

/** 
 * \brief
 * Set when XTR_RDY0 interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_XTR_RDY0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_XTR_RDY0_IDENT  VTSS_BIT(16)

/** 
 * \brief
 * Set when BLK_ANA interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_BLK_ANA_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_BLK_ANA_IDENT  VTSS_BIT(15)

/** 
 * \brief
 * Set when DEV_ALL interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_DEV_ALL_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_DEV_ALL_IDENT  VTSS_BIT(14)

/** 
 * \brief
 * Set when SGPIO interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_SGPIO_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_SGPIO_IDENT  VTSS_BIT(13)

/** 
 * \brief
 * Set when GPIO interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_GPIO_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_GPIO_IDENT  VTSS_BIT(12)

/** 
 * \brief
 * Set when TWI interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_TWI_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_TWI_IDENT  VTSS_BIT(11)

/** 
 * \brief
 * Set when FDMA interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_FDMA_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_FDMA_IDENT  VTSS_BIT(10)

/** 
 * \brief
 * Set when TIMER2 interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_TIMER2_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_TIMER2_IDENT  VTSS_BIT(9)

/** 
 * \brief
 * Set when TIMER1 interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_TIMER1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_TIMER1_IDENT  VTSS_BIT(8)

/** 
 * \brief
 * Set when TIMER0 interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_TIMER0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_TIMER0_IDENT  VTSS_BIT(7)

/** 
 * \brief
 * Set when UART interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_UART_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_UART_IDENT  VTSS_BIT(6)

/** 
 * \brief
 * Set when PI_SD1 interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_PI_SD1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_PI_SD1_IDENT  VTSS_BIT(5)

/** 
 * \brief
 * Set when PI_SD0 interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_PI_SD0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_PI_SD0_IDENT  VTSS_BIT(4)

/** 
 * \brief
 * Set when SW1 interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_SW1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_SW1_IDENT  VTSS_BIT(3)

/** 
 * \brief
 * Set when SW0 interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_SW0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_SW0_IDENT  VTSS_BIT(2)

/** 
 * \brief
 * Set when EXT_IRQ1 interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_EXT_IRQ1_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_EXT_IRQ1_IDENT  VTSS_BIT(1)

/** 
 * \brief
 * Set when EXT_IRQ0 interrupt is a source of the EXT_IRQ1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_IDENT . EXT_IRQ1_EXT_IRQ0_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_IDENT_EXT_IRQ1_EXT_IRQ0_IDENT  VTSS_BIT(0)


/** 
 * \brief Device interrupts
 *
 * \details
 * Shows the sources of the DEV_ALL interrupt.
 *
 * Register: \a ICPU_CFG:INTR:DEV_IDENT
 */
#define VTSS_ICPU_CFG_INTR_DEV_IDENT         VTSS_IOREG(VTSS_TO_CFG,0x2e)


/** 
 * \brief EXT_IRQ0 interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:EXT_IRQ0_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_EXT_IRQ0_INTR_CFG  VTSS_IOREG(VTSS_TO_CFG,0x2f)

/** 
 * \brief
 * Configures when to drive the external interrupt EXT_IRQ0 output, this
 * setting applies only when EXT_IRQ0 is configured for output mode.
 *
 * \details 
 * 0: Only drive when interrupt is active
 * 1: Always driven
 *
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_INTR_CFG . EXT_IRQ0_INTR_DRV
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_INTR_CFG_EXT_IRQ0_INTR_DRV  VTSS_BIT(6)

/** 
 * \brief
 * Controls the direction of external interrupt: EXT_IRQ0.
 * In input mode the interrupt can used as source in the interrupt
 * controller, in this mode any configurations related to the output mode
 * of the interrupt has no effect. In output mode sources can be assigned
 * to the interrupt, in this mode the EXT_IRQ0 must not be enabled as
 * interrupt source (INTR_ENA.EXT_IRQ0_INTR_ENA must remain 0).
 *
 * \details 
 * 0: Input
 * 1: Output
 *
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_INTR_CFG . EXT_IRQ0_INTR_DIR
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_INTR_CFG_EXT_IRQ0_INTR_DIR  VTSS_BIT(5)

/** 
 * \brief
 * Controls the interrupt polarity of external interrupt: EXT_IRQ0. This
 * setting is applies to both to input and output mode. The polarity is
 * corrected at the edge of the chip, internally interrupts are always
 * active-high.
 *
 * \details 
 * 0: Active low
 * 1: Active high
 *
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_INTR_CFG . EXT_IRQ0_INTR_POL
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_INTR_CFG_EXT_IRQ0_INTR_POL  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of EXT_IRQ0 interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_INTR_CFG . EXT_IRQ0_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_INTR_CFG_EXT_IRQ0_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Controls whether interrupts from the EXT_IRQ0 interrupt are edge
 * (low-to-high-transition) or level (interrupt while high value is seen)
 * sensitive.
 *
 * \details 
 * 0: LEVEL sensitive
 * 1: EDGE sensitive
 *
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_INTR_CFG . EXT_IRQ0_INTR_TRIGGER
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_INTR_CFG_EXT_IRQ0_INTR_TRIGGER  VTSS_BIT(2)

/** 
 * \brief
 * Selects the destination of the EXT_IRQ0 interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ0_INTR_CFG . EXT_IRQ0_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ0_INTR_CFG_EXT_IRQ0_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_EXT_IRQ0_INTR_CFG_EXT_IRQ0_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_EXT_IRQ0_INTR_CFG_EXT_IRQ0_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief EXT_IRQ1 interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:EXT_IRQ1_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_EXT_IRQ1_INTR_CFG  VTSS_IOREG(VTSS_TO_CFG,0x30)

/** 
 * \brief
 * Configures when to drive the external interrupt EXT_IRQ1 output, this
 * setting applies only when EXT_IRQ1 is configured for output mode.
 *
 * \details 
 * 0: Only drive when interrupt is active
 * 1: Always driven
 *
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_INTR_CFG . EXT_IRQ1_INTR_DRV
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_INTR_CFG_EXT_IRQ1_INTR_DRV  VTSS_BIT(6)

/** 
 * \brief
 * Controls the direction of external interrupt: EXT_IRQ1.
 * In input mode the interrupt can used as source in the interrupt
 * controller, in this mode any configurations related to the output mode
 * of the interrupt has no effect. In output mode sources can be assigned
 * to the interrupt, in this mode the EXT_IRQ1 must not be enabled as
 * interrupt source (INTR_ENA.EXT_IRQ1_INTR_ENA must remain 0).
 *
 * \details 
 * 0: Input
 * 1: Output
 *
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_INTR_CFG . EXT_IRQ1_INTR_DIR
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_INTR_CFG_EXT_IRQ1_INTR_DIR  VTSS_BIT(5)

/** 
 * \brief
 * Controls the interrupt polarity of external interrupt: EXT_IRQ1. This
 * setting is applies to both to input and output mode. The polarity is
 * corrected at the edge of the chip, internally interrupts are always
 * active-high.
 *
 * \details 
 * 0: Active low
 * 1: Active high
 *
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_INTR_CFG . EXT_IRQ1_INTR_POL
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_INTR_CFG_EXT_IRQ1_INTR_POL  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of EXT_IRQ1 interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_INTR_CFG . EXT_IRQ1_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_INTR_CFG_EXT_IRQ1_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Controls whether interrupts from the EXT_IRQ1 interrupt are edge
 * (low-to-high-transition) or level (interrupt while high value is seen)
 * sensitive.
 *
 * \details 
 * 0: LEVEL sensitive
 * 1: EDGE sensitive
 *
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_INTR_CFG . EXT_IRQ1_INTR_TRIGGER
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_INTR_CFG_EXT_IRQ1_INTR_TRIGGER  VTSS_BIT(2)

/** 
 * \brief
 * Selects the destination of the EXT_IRQ1 interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_IRQ1_INTR_CFG . EXT_IRQ1_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_IRQ1_INTR_CFG_EXT_IRQ1_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_EXT_IRQ1_INTR_CFG_EXT_IRQ1_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_EXT_IRQ1_INTR_CFG_EXT_IRQ1_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief SW0 interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:SW0_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_SW0_INTR_CFG      VTSS_IOREG(VTSS_TO_CFG,0x31)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_SW0_INTR_CFG . SW0_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_SW0_INTR_CFG_SW0_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of SW0 interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_SW0_INTR_CFG . SW0_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_SW0_INTR_CFG_SW0_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the SW0 interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_SW0_INTR_CFG . SW0_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_SW0_INTR_CFG_SW0_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_SW0_INTR_CFG_SW0_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_SW0_INTR_CFG_SW0_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief SW1 interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:SW1_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_SW1_INTR_CFG      VTSS_IOREG(VTSS_TO_CFG,0x32)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_SW1_INTR_CFG . SW1_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_SW1_INTR_CFG_SW1_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of SW1 interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_SW1_INTR_CFG . SW1_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_SW1_INTR_CFG_SW1_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the SW1 interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_SW1_INTR_CFG . SW1_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_SW1_INTR_CFG_SW1_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_SW1_INTR_CFG_SW1_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_SW1_INTR_CFG_SW1_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief MIIM1 interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:MIIM1_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_MIIM1_INTR_CFG    VTSS_IOREG(VTSS_TO_CFG,0x33)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_MIIM1_INTR_CFG . MIIM1_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_MIIM1_INTR_CFG_MIIM1_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of MIIM1 interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_MIIM1_INTR_CFG . MIIM1_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_MIIM1_INTR_CFG_MIIM1_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the MIIM1 interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_MIIM1_INTR_CFG . MIIM1_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_MIIM1_INTR_CFG_MIIM1_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_MIIM1_INTR_CFG_MIIM1_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_MIIM1_INTR_CFG_MIIM1_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief MIIM0 interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:MIIM0_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_MIIM0_INTR_CFG    VTSS_IOREG(VTSS_TO_CFG,0x34)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_MIIM0_INTR_CFG . MIIM0_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_MIIM0_INTR_CFG_MIIM0_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of MIIM0 interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_MIIM0_INTR_CFG . MIIM0_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_MIIM0_INTR_CFG_MIIM0_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the MIIM0 interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_MIIM0_INTR_CFG . MIIM0_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_MIIM0_INTR_CFG_MIIM0_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_MIIM0_INTR_CFG_MIIM0_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_MIIM0_INTR_CFG_MIIM0_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief PI_SD0 interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:PI_SD0_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_PI_SD0_INTR_CFG   VTSS_IOREG(VTSS_TO_CFG,0x35)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_PI_SD0_INTR_CFG . PI_SD0_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_PI_SD0_INTR_CFG_PI_SD0_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of PI_SD0 interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_PI_SD0_INTR_CFG . PI_SD0_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_PI_SD0_INTR_CFG_PI_SD0_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the PI_SD0 interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_PI_SD0_INTR_CFG . PI_SD0_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_PI_SD0_INTR_CFG_PI_SD0_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_PI_SD0_INTR_CFG_PI_SD0_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_PI_SD0_INTR_CFG_PI_SD0_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief PI_SD1 interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:PI_SD1_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_PI_SD1_INTR_CFG   VTSS_IOREG(VTSS_TO_CFG,0x36)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_PI_SD1_INTR_CFG . PI_SD1_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_PI_SD1_INTR_CFG_PI_SD1_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of PI_SD1 interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_PI_SD1_INTR_CFG . PI_SD1_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_PI_SD1_INTR_CFG_PI_SD1_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the PI_SD1 interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_PI_SD1_INTR_CFG . PI_SD1_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_PI_SD1_INTR_CFG_PI_SD1_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_PI_SD1_INTR_CFG_PI_SD1_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_PI_SD1_INTR_CFG_PI_SD1_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief UART interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:UART_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_UART_INTR_CFG     VTSS_IOREG(VTSS_TO_CFG,0x37)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_UART_INTR_CFG . UART_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_UART_INTR_CFG_UART_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of UART interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_UART_INTR_CFG . UART_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_UART_INTR_CFG_UART_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the UART interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_UART_INTR_CFG . UART_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_UART_INTR_CFG_UART_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_UART_INTR_CFG_UART_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_UART_INTR_CFG_UART_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief TIMER0 interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:TIMER0_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_TIMER0_INTR_CFG   VTSS_IOREG(VTSS_TO_CFG,0x38)

/** 
 * \brief
 * Set to force assertion of TIMER0 interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_TIMER0_INTR_CFG . TIMER0_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_TIMER0_INTR_CFG_TIMER0_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the TIMER0 interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_TIMER0_INTR_CFG . TIMER0_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_TIMER0_INTR_CFG_TIMER0_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_TIMER0_INTR_CFG_TIMER0_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_TIMER0_INTR_CFG_TIMER0_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief TIMER1 interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:TIMER1_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_TIMER1_INTR_CFG   VTSS_IOREG(VTSS_TO_CFG,0x39)

/** 
 * \brief
 * Set to force assertion of TIMER1 interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_TIMER1_INTR_CFG . TIMER1_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_TIMER1_INTR_CFG_TIMER1_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the TIMER1 interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_TIMER1_INTR_CFG . TIMER1_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_TIMER1_INTR_CFG_TIMER1_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_TIMER1_INTR_CFG_TIMER1_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_TIMER1_INTR_CFG_TIMER1_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief TIMER2 interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:TIMER2_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_TIMER2_INTR_CFG   VTSS_IOREG(VTSS_TO_CFG,0x3a)

/** 
 * \brief
 * Set to force assertion of TIMER2 interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_TIMER2_INTR_CFG . TIMER2_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_TIMER2_INTR_CFG_TIMER2_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the TIMER2 interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_TIMER2_INTR_CFG . TIMER2_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_TIMER2_INTR_CFG_TIMER2_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_TIMER2_INTR_CFG_TIMER2_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_TIMER2_INTR_CFG_TIMER2_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief FDMA interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:FDMA_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_FDMA_INTR_CFG     VTSS_IOREG(VTSS_TO_CFG,0x3b)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_FDMA_INTR_CFG . FDMA_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_FDMA_INTR_CFG_FDMA_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of FDMA interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_FDMA_INTR_CFG . FDMA_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_FDMA_INTR_CFG_FDMA_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the FDMA interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_FDMA_INTR_CFG . FDMA_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_FDMA_INTR_CFG_FDMA_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_FDMA_INTR_CFG_FDMA_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_FDMA_INTR_CFG_FDMA_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief TWI interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:TWI_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_TWI_INTR_CFG      VTSS_IOREG(VTSS_TO_CFG,0x3c)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_TWI_INTR_CFG . TWI_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_TWI_INTR_CFG_TWI_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of TWI interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_TWI_INTR_CFG . TWI_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_TWI_INTR_CFG_TWI_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the TWI interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_TWI_INTR_CFG . TWI_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_TWI_INTR_CFG_TWI_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_TWI_INTR_CFG_TWI_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_TWI_INTR_CFG_TWI_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief GPIO interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:GPIO_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_GPIO_INTR_CFG     VTSS_IOREG(VTSS_TO_CFG,0x3d)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_GPIO_INTR_CFG . GPIO_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_GPIO_INTR_CFG_GPIO_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of GPIO interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_GPIO_INTR_CFG . GPIO_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_GPIO_INTR_CFG_GPIO_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the GPIO interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_GPIO_INTR_CFG . GPIO_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_GPIO_INTR_CFG_GPIO_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_GPIO_INTR_CFG_GPIO_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_GPIO_INTR_CFG_GPIO_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief SGPIO interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:SGPIO_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_SGPIO_INTR_CFG    VTSS_IOREG(VTSS_TO_CFG,0x3e)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_SGPIO_INTR_CFG . SGPIO_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_SGPIO_INTR_CFG_SGPIO_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of SGPIO interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_SGPIO_INTR_CFG . SGPIO_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_SGPIO_INTR_CFG_SGPIO_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the SGPIO interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_SGPIO_INTR_CFG . SGPIO_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_SGPIO_INTR_CFG_SGPIO_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_SGPIO_INTR_CFG_SGPIO_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_SGPIO_INTR_CFG_SGPIO_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief DEV_ALL interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:DEV_ALL_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_DEV_ALL_INTR_CFG  VTSS_IOREG(VTSS_TO_CFG,0x3f)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_DEV_ALL_INTR_CFG . DEV_ALL_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_DEV_ALL_INTR_CFG_DEV_ALL_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of DEV_ALL interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_DEV_ALL_INTR_CFG . DEV_ALL_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_DEV_ALL_INTR_CFG_DEV_ALL_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the DEV_ALL interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_DEV_ALL_INTR_CFG . DEV_ALL_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_DEV_ALL_INTR_CFG_DEV_ALL_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_DEV_ALL_INTR_CFG_DEV_ALL_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_DEV_ALL_INTR_CFG_DEV_ALL_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief BLK_ANA interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:BLK_ANA_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_BLK_ANA_INTR_CFG  VTSS_IOREG(VTSS_TO_CFG,0x40)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_BLK_ANA_INTR_CFG . BLK_ANA_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_BLK_ANA_INTR_CFG_BLK_ANA_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of BLK_ANA interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_BLK_ANA_INTR_CFG . BLK_ANA_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_BLK_ANA_INTR_CFG_BLK_ANA_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the BLK_ANA interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_BLK_ANA_INTR_CFG . BLK_ANA_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_BLK_ANA_INTR_CFG_BLK_ANA_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_BLK_ANA_INTR_CFG_BLK_ANA_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_BLK_ANA_INTR_CFG_BLK_ANA_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief XTR_RDY0 interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:XTR_RDY0_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_XTR_RDY0_INTR_CFG  VTSS_IOREG(VTSS_TO_CFG,0x41)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_XTR_RDY0_INTR_CFG . XTR_RDY0_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_XTR_RDY0_INTR_CFG_XTR_RDY0_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of XTR_RDY0 interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_XTR_RDY0_INTR_CFG . XTR_RDY0_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_XTR_RDY0_INTR_CFG_XTR_RDY0_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the XTR_RDY0 interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_XTR_RDY0_INTR_CFG . XTR_RDY0_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_XTR_RDY0_INTR_CFG_XTR_RDY0_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_XTR_RDY0_INTR_CFG_XTR_RDY0_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_XTR_RDY0_INTR_CFG_XTR_RDY0_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief XTR_RDY1 interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:XTR_RDY1_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_XTR_RDY1_INTR_CFG  VTSS_IOREG(VTSS_TO_CFG,0x42)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_XTR_RDY1_INTR_CFG . XTR_RDY1_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_XTR_RDY1_INTR_CFG_XTR_RDY1_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of XTR_RDY1 interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_XTR_RDY1_INTR_CFG . XTR_RDY1_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_XTR_RDY1_INTR_CFG_XTR_RDY1_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the XTR_RDY1 interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_XTR_RDY1_INTR_CFG . XTR_RDY1_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_XTR_RDY1_INTR_CFG_XTR_RDY1_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_XTR_RDY1_INTR_CFG_XTR_RDY1_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_XTR_RDY1_INTR_CFG_XTR_RDY1_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief XTR_RDY2 interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:XTR_RDY2_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_XTR_RDY2_INTR_CFG  VTSS_IOREG(VTSS_TO_CFG,0x43)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_XTR_RDY2_INTR_CFG . XTR_RDY2_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_XTR_RDY2_INTR_CFG_XTR_RDY2_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of XTR_RDY2 interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_XTR_RDY2_INTR_CFG . XTR_RDY2_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_XTR_RDY2_INTR_CFG_XTR_RDY2_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the XTR_RDY2 interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_XTR_RDY2_INTR_CFG . XTR_RDY2_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_XTR_RDY2_INTR_CFG_XTR_RDY2_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_XTR_RDY2_INTR_CFG_XTR_RDY2_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_XTR_RDY2_INTR_CFG_XTR_RDY2_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief XTR_RDY3 interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:XTR_RDY3_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_XTR_RDY3_INTR_CFG  VTSS_IOREG(VTSS_TO_CFG,0x44)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_XTR_RDY3_INTR_CFG . XTR_RDY3_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_XTR_RDY3_INTR_CFG_XTR_RDY3_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of XTR_RDY3 interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_XTR_RDY3_INTR_CFG . XTR_RDY3_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_XTR_RDY3_INTR_CFG_XTR_RDY3_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the XTR_RDY3 interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_XTR_RDY3_INTR_CFG . XTR_RDY3_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_XTR_RDY3_INTR_CFG_XTR_RDY3_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_XTR_RDY3_INTR_CFG_XTR_RDY3_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_XTR_RDY3_INTR_CFG_XTR_RDY3_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief INJ_RDY0 interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:INJ_RDY0_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_INJ_RDY0_INTR_CFG  VTSS_IOREG(VTSS_TO_CFG,0x45)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INJ_RDY0_INTR_CFG . INJ_RDY0_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_INJ_RDY0_INTR_CFG_INJ_RDY0_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of INJ_RDY0 interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INJ_RDY0_INTR_CFG . INJ_RDY0_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_INJ_RDY0_INTR_CFG_INJ_RDY0_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the INJ_RDY0 interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_INJ_RDY0_INTR_CFG . INJ_RDY0_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_INJ_RDY0_INTR_CFG_INJ_RDY0_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_INJ_RDY0_INTR_CFG_INJ_RDY0_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_INJ_RDY0_INTR_CFG_INJ_RDY0_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief INJ_RDY1 interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:INJ_RDY1_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_INJ_RDY1_INTR_CFG  VTSS_IOREG(VTSS_TO_CFG,0x46)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INJ_RDY1_INTR_CFG . INJ_RDY1_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_INJ_RDY1_INTR_CFG_INJ_RDY1_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of INJ_RDY1 interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INJ_RDY1_INTR_CFG . INJ_RDY1_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_INJ_RDY1_INTR_CFG_INJ_RDY1_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the INJ_RDY1 interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_INJ_RDY1_INTR_CFG . INJ_RDY1_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_INJ_RDY1_INTR_CFG_INJ_RDY1_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_INJ_RDY1_INTR_CFG_INJ_RDY1_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_INJ_RDY1_INTR_CFG_INJ_RDY1_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief INJ_RDY2 interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:INJ_RDY2_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_INJ_RDY2_INTR_CFG  VTSS_IOREG(VTSS_TO_CFG,0x47)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INJ_RDY2_INTR_CFG . INJ_RDY2_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_INJ_RDY2_INTR_CFG_INJ_RDY2_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of INJ_RDY2 interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INJ_RDY2_INTR_CFG . INJ_RDY2_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_INJ_RDY2_INTR_CFG_INJ_RDY2_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the INJ_RDY2 interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_INJ_RDY2_INTR_CFG . INJ_RDY2_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_INJ_RDY2_INTR_CFG_INJ_RDY2_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_INJ_RDY2_INTR_CFG_INJ_RDY2_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_INJ_RDY2_INTR_CFG_INJ_RDY2_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief INJ_RDY3 interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:INJ_RDY3_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_INJ_RDY3_INTR_CFG  VTSS_IOREG(VTSS_TO_CFG,0x48)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INJ_RDY3_INTR_CFG . INJ_RDY3_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_INJ_RDY3_INTR_CFG_INJ_RDY3_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of INJ_RDY3 interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INJ_RDY3_INTR_CFG . INJ_RDY3_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_INJ_RDY3_INTR_CFG_INJ_RDY3_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the INJ_RDY3 interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_INJ_RDY3_INTR_CFG . INJ_RDY3_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_INJ_RDY3_INTR_CFG_INJ_RDY3_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_INJ_RDY3_INTR_CFG_INJ_RDY3_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_INJ_RDY3_INTR_CFG_INJ_RDY3_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief INJ_RDY4 interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:INJ_RDY4_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_INJ_RDY4_INTR_CFG  VTSS_IOREG(VTSS_TO_CFG,0x49)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INJ_RDY4_INTR_CFG . INJ_RDY4_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_INJ_RDY4_INTR_CFG_INJ_RDY4_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of INJ_RDY4 interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INJ_RDY4_INTR_CFG . INJ_RDY4_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_INJ_RDY4_INTR_CFG_INJ_RDY4_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the INJ_RDY4 interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_INJ_RDY4_INTR_CFG . INJ_RDY4_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_INJ_RDY4_INTR_CFG_INJ_RDY4_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_INJ_RDY4_INTR_CFG_INJ_RDY4_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_INJ_RDY4_INTR_CFG_INJ_RDY4_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief INTEGRITY interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:INTEGRITY_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_INTEGRITY_INTR_CFG  VTSS_IOREG(VTSS_TO_CFG,0x4a)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTEGRITY_INTR_CFG . INTEGRITY_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_INTEGRITY_INTR_CFG_INTEGRITY_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of INTEGRITY interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTEGRITY_INTR_CFG . INTEGRITY_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_INTEGRITY_INTR_CFG_INTEGRITY_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the INTEGRITY interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_INTEGRITY_INTR_CFG . INTEGRITY_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_INTEGRITY_INTR_CFG_INTEGRITY_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_INTEGRITY_INTR_CFG_INTEGRITY_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_INTEGRITY_INTR_CFG_INTEGRITY_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief PTP_SYNC interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:INTR:PTP_SYNC_INTR_CFG
 */
#define VTSS_ICPU_CFG_INTR_PTP_SYNC_INTR_CFG  VTSS_IOREG(VTSS_TO_CFG,0x4b)

/** 
 * \brief
 * Set to bypass sticky interrupt functionality. When set the value from
 * the interrupting source is passed directly to the destination interrupt.
 * This feature can be useful when mapping a small number of interrupts via
 * external interrupt output to an external CPU.
 * When this field is set, the TRIGGER and FORCE fields no longer has any
 * effect.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_PTP_SYNC_INTR_CFG . PTP_SYNC_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_PTP_SYNC_INTR_CFG_PTP_SYNC_INTR_BYPASS  VTSS_BIT(4)

/** 
 * \brief
 * Set to force assertion of PTP_SYNC interrupt. This field is cleared
 * immediately after generating interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_PTP_SYNC_INTR_CFG . PTP_SYNC_INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_PTP_SYNC_INTR_CFG_PTP_SYNC_INTR_FORCE  VTSS_BIT(3)

/** 
 * \brief
 * Selects the destination of the PTP_SYNC interrupt.
 *
 * \details 
 * 0: ICPU_IRQ0
 * 1: ICPU_IRQ1
 * 2: EXT_IRQ0
 * 3: EXT_IRQ1
 *
 * Field: ::VTSS_ICPU_CFG_INTR_PTP_SYNC_INTR_CFG . PTP_SYNC_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_INTR_PTP_SYNC_INTR_CFG_PTP_SYNC_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_PTP_SYNC_INTR_CFG_PTP_SYNC_INTR_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_PTP_SYNC_INTR_CFG_PTP_SYNC_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Device Interrupt enable
 *
 * \details
 * Register: \a ICPU_CFG:INTR:DEV_ENA
 */
#define VTSS_ICPU_CFG_INTR_DEV_ENA           VTSS_IOREG(VTSS_TO_CFG,0x4c)


/** 
 * \brief Device Interrupt polarity
 *
 * \details
 * Register: \a ICPU_CFG:INTR:DEV_POL
 */
#define VTSS_ICPU_CFG_INTR_DEV_POL           VTSS_IOREG(VTSS_TO_CFG,0x4d)


/** 
 * \brief Device Interrupt sticky indications
 *
 * \details
 * Register: \a ICPU_CFG:INTR:DEV_IDENT_STICKY
 */
#define VTSS_ICPU_CFG_INTR_DEV_IDENT_STICKY  VTSS_IOREG(VTSS_TO_CFG,0x4e)

/**
 * Register Group: \a ICPU_CFG:GPDMA
 *
 * Frame DMA
 */


/** 
 * \brief Common Injection or Extraction Configuration
 *
 * \details
 * Register: \a ICPU_CFG:GPDMA:FDMA_CFG
 */
#define VTSS_ICPU_CFG_GPDMA_FDMA_CFG         VTSS_IOREG(VTSS_TO_CFG,0x4f)

/** 
 * \brief
 * Specifies an injection group ID to abort frames on when setting
 * INJ_GRP_ABRT. This field may only be changed when INJ_GRP_ABRT is
 * cleared.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_GPDMA_FDMA_CFG . INJ_GRP_ABRT_ID
 */
#define  VTSS_F_ICPU_CFG_GPDMA_FDMA_CFG_INJ_GRP_ABRT_ID  VTSS_BIT(2)

/** 
 * \brief
 * Set to abort the frame currently being transmitted on the injection
 * group indicated by INJ_GRP_ABRT_ID. This field is cleared once the abort
 * has been accepted. If no frame is currently being transmitted (on the
 * injection group) then no aborting will occur.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_GPDMA_FDMA_CFG . INJ_GRP_ABRT
 */
#define  VTSS_F_ICPU_CFG_GPDMA_FDMA_CFG_INJ_GRP_ABRT  VTSS_BIT(1)

/** 
 * \brief
 * Enable FDMA access to the queuing system.When this field is set, manual
 * injection and extraction must not be done through the DEVCPU registers.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_GPDMA_FDMA_CFG . FDMA_ENA
 */
#define  VTSS_F_ICPU_CFG_GPDMA_FDMA_CFG_FDMA_ENA  VTSS_BIT(0)


/** 
 * \brief FDMA Channel Usage and Flow Control
 *
 * \details
 * Configurations for each of the DMA channels.
 *
 * Register: \a ICPU_CFG:GPDMA:FDMA_CH_CFG
 *
 * @param ri Replicator: x_GPDMA_CH_CNT (??), 0-7
 */
#define VTSS_ICPU_CFG_GPDMA_FDMA_CH_CFG(ri)  VTSS_IOREG(VTSS_TO_CFG,0x51 + (ri))

/** 
 * \brief
 * Controls the usage of the channel. The channel can be configured for
 * either frame extraction (XTR) or frame injection (INJ)
 *
 * \details 
 * 0: The channel is an extraction channel (XTR)
 * 1: The channel is an injection channel (INJ)
 *
 * Field: ::VTSS_ICPU_CFG_GPDMA_FDMA_CH_CFG . USAGE
 */
#define  VTSS_F_ICPU_CFG_GPDMA_FDMA_CH_CFG_USAGE  VTSS_BIT(1)

/** 
 * \brief
 * Enable channel for the specified function.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_GPDMA_FDMA_CH_CFG . CH_ENA
 */
#define  VTSS_F_ICPU_CFG_GPDMA_FDMA_CH_CFG_CH_ENA  VTSS_BIT(0)


/** 
 * \brief FDMA Injection Parameters
 *
 * \details
 * Configurations for each of the injection groups.
 *
 * Register: \a ICPU_CFG:GPDMA:FDMA_INJ_CFG
 *
 * @param ri Replicator: x_DEVCPU_QS_INJ_GRP_CNT (??), 0-1
 */
#define VTSS_ICPU_CFG_GPDMA_FDMA_INJ_CFG(ri)  VTSS_IOREG(VTSS_TO_CFG,0x59 + (ri))

/** 
 * \brief
 * Set this field to enable back pressure timeout interrupt for this
 * injection group, see FDMA_BP_TIMEOUT_INT:INJ_BP_TIMEOUT_INT for more
 * information.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_GPDMA_FDMA_INJ_CFG . INJ_GRP_BP_TO_INT_ENA
 */
#define  VTSS_F_ICPU_CFG_GPDMA_FDMA_INJ_CFG_INJ_GRP_BP_TO_INT_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Enable back pressure from the corresponding injection cannel. If an
 * injection channel is used this field (and INJ_GRP_BP_MAP) must be set.
 *
 * \details 
 * 0: back-pressure is disabled.
 * 1: Back-pressure is enabled.

 *
 * Field: ::VTSS_ICPU_CFG_GPDMA_FDMA_INJ_CFG . INJ_GRP_BP_ENA
 */
#define  VTSS_F_ICPU_CFG_GPDMA_FDMA_INJ_CFG_INJ_GRP_BP_ENA  VTSS_BIT(3)

/** 
 * \brief
 * To correctly generate backpressure to the DMA from individual injection
 * groups, configure the DMA channel ID which may send frames to the
 * corresponding injection group. If the injetion group is not used then
 * this field is dont-care. 
 * Please note that an injection group may only receive frames from a
 * single DMA channel - while DMA channels can inject to multiple injection
 * groups. When a DMA channel injects to multiple injection groups -
 * backpressure must be enabled from all of the injection groups.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_GPDMA_FDMA_INJ_CFG . INJ_GRP_BP_MAP
 */
#define  VTSS_F_ICPU_CFG_GPDMA_FDMA_INJ_CFG_INJ_GRP_BP_MAP(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ICPU_CFG_GPDMA_FDMA_INJ_CFG_INJ_GRP_BP_MAP     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ICPU_CFG_GPDMA_FDMA_INJ_CFG_INJ_GRP_BP_MAP(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief FDMA Extraction Parameters
 *
 * \details
 * Configurations for each of the extraction groups.
 *
 * Register: \a ICPU_CFG:GPDMA:FDMA_XTR_CFG
 *
 * @param ri Replicator: x_DEVCPU_QS_XTR_GRP_CNT (??), 0-1
 */
#define VTSS_ICPU_CFG_GPDMA_FDMA_XTR_CFG(ri)  VTSS_IOREG(VTSS_TO_CFG,0x5b + (ri))

/** 
 * \brief
 * Must be configured to the same value as CTL0:SRC_MSIZE for the
 * corresponding DMA channel.
 *
 * \details 
 * 0 : 1
 * 1 : 4
 * 2 : 8
 * 3 : 16
 * 4 : 32
 * 5 : 64
 * 6-7 : reserved, do not use
 *
 * Field: ::VTSS_ICPU_CFG_GPDMA_FDMA_XTR_CFG . XTR_BURST_SIZE
 */
#define  VTSS_F_ICPU_CFG_GPDMA_FDMA_XTR_CFG_XTR_BURST_SIZE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ICPU_CFG_GPDMA_FDMA_XTR_CFG_XTR_BURST_SIZE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ICPU_CFG_GPDMA_FDMA_XTR_CFG_XTR_BURST_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Extraction Status for FDMA Engine
 *
 * \details
 * Ths register provides the extraction status to be used by this FDMA
 * engine.
 *
 * Register: \a ICPU_CFG:GPDMA:FDMA_XTR_STAT_LAST_DCB
 *
 * @param ri Replicator: x_DEVCPU_QS_XTR_GRP_CNT (??), 0-1
 */
#define VTSS_ICPU_CFG_GPDMA_FDMA_XTR_STAT_LAST_DCB(ri)  VTSS_IOREG(VTSS_TO_CFG,0x5d + (ri))

/** 
 * \brief
 * Length of frame (in bytes).
 * If frames are spread accross multiple DCBs this field is incremental; it
 * shows the number of bytes written to the current and all previous DCBs,
 * at the last DCB (EOF when is set), then value then represents the total
 * frame-length.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_GPDMA_FDMA_XTR_STAT_LAST_DCB . XTR_STAT_FRM_LEN
 */
#define  VTSS_F_ICPU_CFG_GPDMA_FDMA_XTR_STAT_LAST_DCB_XTR_STAT_FRM_LEN(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_ICPU_CFG_GPDMA_FDMA_XTR_STAT_LAST_DCB_XTR_STAT_FRM_LEN     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_ICPU_CFG_GPDMA_FDMA_XTR_STAT_LAST_DCB_XTR_STAT_FRM_LEN(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Frame has been aborted, this will happen if frame is longer than maximum
 * allowed size.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_GPDMA_FDMA_XTR_STAT_LAST_DCB . XTR_STAT_ABORT
 */
#define  VTSS_F_ICPU_CFG_GPDMA_FDMA_XTR_STAT_LAST_DCB_XTR_STAT_ABORT  VTSS_BIT(4)

/** 
 * \brief
 * Frame has been pruned (see extraction queue registers for more details).
 *
 * \details 
 * 0: Not pruned
 * 1: Pruned
 *
 * Field: ::VTSS_ICPU_CFG_GPDMA_FDMA_XTR_STAT_LAST_DCB . XTR_STAT_PRUNED
 */
#define  VTSS_F_ICPU_CFG_GPDMA_FDMA_XTR_STAT_LAST_DCB_XTR_STAT_PRUNED  VTSS_BIT(3)

/** 
 * \brief
 * End of frame
 *
 * \details 
 * 0:  Not EOF
 * 1:  EOF
 *
 * Field: ::VTSS_ICPU_CFG_GPDMA_FDMA_XTR_STAT_LAST_DCB . XTR_STAT_EOF
 */
#define  VTSS_F_ICPU_CFG_GPDMA_FDMA_XTR_STAT_LAST_DCB_XTR_STAT_EOF  VTSS_BIT(2)

/** 
 * \brief
 * Start of frame
 *
 * \details 
 * 0:  Not SOF
 * 1:  SOF
 *
 * Field: ::VTSS_ICPU_CFG_GPDMA_FDMA_XTR_STAT_LAST_DCB . XTR_STAT_SOF
 */
#define  VTSS_F_ICPU_CFG_GPDMA_FDMA_XTR_STAT_LAST_DCB_XTR_STAT_SOF  VTSS_BIT(1)

/** 
 * \brief
 * Always reads as '1'.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_GPDMA_FDMA_XTR_STAT_LAST_DCB . XTR_STAT_VLD
 */
#define  VTSS_F_ICPU_CFG_GPDMA_FDMA_XTR_STAT_LAST_DCB_XTR_STAT_VLD  VTSS_BIT(0)


/** 
 * \brief Frame Counter and Flow Control Status
 *
 * \details
 * Register: \a ICPU_CFG:GPDMA:FDMA_FRM_CNT
 */
#define VTSS_ICPU_CFG_GPDMA_FDMA_FRM_CNT     VTSS_IOREG(VTSS_TO_CFG,0x5f)

/** 
 * \brief
 * This counter is incremented by 1 for every frame that is moved through
 * the FDMA (both XTR or INJ). The counter increments when end-of-frame is
 * processed by the FDMA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_GPDMA_FDMA_FRM_CNT . FDMA_FRM_CNT
 */
#define  VTSS_F_ICPU_CFG_GPDMA_FDMA_FRM_CNT_FDMA_FRM_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ICPU_CFG_GPDMA_FDMA_FRM_CNT_FDMA_FRM_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ICPU_CFG_GPDMA_FDMA_FRM_CNT_FDMA_FRM_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief FDMA Backpressure Timeout Interrupt
 *
 * \details
 * As long as a field in this register is set, the FDMA will indicate
 * interrupt towards the interrupt controller.
 *
 * Register: \a ICPU_CFG:GPDMA:FDMA_BP_TO_INT
 */
#define VTSS_ICPU_CFG_GPDMA_FDMA_BP_TO_INT   VTSS_IOREG(VTSS_TO_CFG,0x60)

/** 
 * \brief
 * This is an indication of backpressure timeout interrupt. If a bit in
 * this field is set the corresponding injection group has been in
 * back-pressure for more than the allowed time (as configured in
 * FDMA_BP_TO_DIV:INJ_BP_TO_DIV). Enable backpressure timeout interrupt in
 * FDMA_INJ_CFG:INJ_GRP_BP_TO_INT_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_GPDMA_FDMA_BP_TO_INT . INJ_BP_TO_INT
 */
#define  VTSS_F_ICPU_CFG_GPDMA_FDMA_BP_TO_INT_INJ_BP_TO_INT(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_GPDMA_FDMA_BP_TO_INT_INJ_BP_TO_INT     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_GPDMA_FDMA_BP_TO_INT_INJ_BP_TO_INT(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief FDMA Timeout Divider
 *
 * \details
 * Register: \a ICPU_CFG:GPDMA:FDMA_BP_TO_DIV
 */
#define VTSS_ICPU_CFG_GPDMA_FDMA_BP_TO_DIV   VTSS_IOREG(VTSS_TO_CFG,0x61)

/** 
 * \brief
 * Set this field to force reload of the backpressure timeout divider.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_GPDMA_FDMA_BP_TO_DIV . INJ_BP_TO_DIV_RLOAD
 */
#define  VTSS_F_ICPU_CFG_GPDMA_FDMA_BP_TO_DIV_INJ_BP_TO_DIV_RLOAD  VTSS_BIT(16)

/** 
 * \brief
 * Configures the timeout for injection group backpressure interrupt. The
 * timeout is calculated as follows:
 * timeout(s) = <div-value> / (sysfrequency(MHz) * 244)
 * E.g. configuring a timeout value of 1220 in a 200MHz system yields a
 * timeout of 25ms.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_GPDMA_FDMA_BP_TO_DIV . INJ_BP_TO_DIV
 */
#define  VTSS_F_ICPU_CFG_GPDMA_FDMA_BP_TO_DIV_INJ_BP_TO_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ICPU_CFG_GPDMA_FDMA_BP_TO_DIV_INJ_BP_TO_DIV     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ICPU_CFG_GPDMA_FDMA_BP_TO_DIV_INJ_BP_TO_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a ICPU_CFG:INJ_FRM_SPC
 *
 * Injection frame spacing
 */


/** 
 * \brief Injection frame spacing timer
 *
 * \details
 * Register: \a ICPU_CFG:INJ_FRM_SPC:INJ_FRM_SPC_TMR
 *
 * @param gi Replicator: x_GPDMA_CH_CNT (??), 0-7
 */
#define VTSS_ICPU_CFG_INJ_FRM_SPC_INJ_FRM_SPC_TMR(gi)  VTSS_IOREG_IX(VTSS_TO_CFG,0x62,gi,4,0,0)


/** 
 * \brief Reload value for injection frame spacing timer
 *
 * \details
 * Register: \a ICPU_CFG:INJ_FRM_SPC:INJ_FRM_SPC_TMR_CFG
 *
 * @param gi Replicator: x_GPDMA_CH_CNT (??), 0-7
 */
#define VTSS_ICPU_CFG_INJ_FRM_SPC_INJ_FRM_SPC_TMR_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_CFG,0x62,gi,4,0,1)


/** 
 * \brief Lack counter
 *
 * \details
 * Register: \a ICPU_CFG:INJ_FRM_SPC:INJ_FRM_SPC_LACK_CNTR
 *
 * @param gi Replicator: x_GPDMA_CH_CNT (??), 0-7
 */
#define VTSS_ICPU_CFG_INJ_FRM_SPC_INJ_FRM_SPC_LACK_CNTR(gi)  VTSS_IOREG_IX(VTSS_TO_CFG,0x62,gi,4,0,2)

/** 
 * \brief
 * When INJ_FRM_SPC_CFG.FRM_SPC_ENA is set, this counter counts the number
 * of ticks provided by the INJ_FRM_SPC_TMR and is decremented by hardware
 * for every transmitted frame. In other words, the value of lack counter
 * value is the number of frames which it is OK to transmit unspaced. Is
 * used in conjunction with the queue-system fill-level to signal to the
 * DMA that it is OK to transmit the next frame.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INJ_FRM_SPC_INJ_FRM_SPC_LACK_CNTR . LACK_CNTR
 */
#define  VTSS_F_ICPU_CFG_INJ_FRM_SPC_INJ_FRM_SPC_LACK_CNTR_LACK_CNTR(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ICPU_CFG_INJ_FRM_SPC_INJ_FRM_SPC_LACK_CNTR_LACK_CNTR     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ICPU_CFG_INJ_FRM_SPC_INJ_FRM_SPC_LACK_CNTR_LACK_CNTR(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Injection frame spacing configuration register
 *
 * \details
 * Register: \a ICPU_CFG:INJ_FRM_SPC:INJ_FRM_SPC_CFG
 *
 * @param gi Replicator: x_GPDMA_CH_CNT (??), 0-7
 */
#define VTSS_ICPU_CFG_INJ_FRM_SPC_INJ_FRM_SPC_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_CFG,0x62,gi,4,0,3)

/** 
 * \brief
 * This bit is used to generally enable/disable the frame spacing feature. 
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INJ_FRM_SPC_INJ_FRM_SPC_CFG . FRM_SPC_ENA
 */
#define  VTSS_F_ICPU_CFG_INJ_FRM_SPC_INJ_FRM_SPC_CFG_FRM_SPC_ENA  VTSS_BIT(0)

/** 
 * \brief
 * Controls whether the INJ_FRM_SPC_TMR is counting or not. When this field
 * is 0 the reload value is written to the frame space timer and the timer
 * is not running. When this field is 1 the timer is running and is
 * reloaded when it reaches zero.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INJ_FRM_SPC_INJ_FRM_SPC_CFG . TMR_ENA
 */
#define  VTSS_F_ICPU_CFG_INJ_FRM_SPC_INJ_FRM_SPC_CFG_TMR_ENA  VTSS_BIT(1)

/**
 * Register Group: \a ICPU_CFG:TIMERS
 *
 * Timer Registers
 */


/** 
 * \brief Watchdog Timer
 *
 * \details
 * Register: \a ICPU_CFG:TIMERS:WDT
 */
#define VTSS_ICPU_CFG_TIMERS_WDT             VTSS_IOREG(VTSS_TO_CFG,0x82)

/** 
 * \brief
 * Shows whether the last reset was caused by a watchdog timer reset. This
 * field is updated during reset, therefore it is always valid.
 *
 * \details 
 * 0: Reset was not caused by WDT
 * 1: Reset was caused by WDT timeout
 *
 * Field: ::VTSS_ICPU_CFG_TIMERS_WDT . WDT_STATUS
 */
#define  VTSS_F_ICPU_CFG_TIMERS_WDT_WDT_STATUS  VTSS_BIT(9)

/** 
 * \brief
 * Use this field to enable or disable the watchdog timer. When the WDT is
 * enabled, it causes a reset after 2 seconds if it is not periodically
 * reset. This field is only read by the WDT after a sucessful lock
 * sequence (WDT_LOCK).
 *
 * \details 
 * 0: WDT is disabled
 * 1: WDT is enabled
 *
 * Field: ::VTSS_ICPU_CFG_TIMERS_WDT . WDT_ENABLE
 */
#define  VTSS_F_ICPU_CFG_TIMERS_WDT_WDT_ENABLE  VTSS_BIT(8)

/** 
 * \brief
 * Use this field to configure and reset the WDT. When writing 0xBE to this
 * field immediately followed by writing 0xEF, the WDT resets and
 * configurations are read from this register (as set when the 0xEF is
 * written). When the WDT is enabled, writing any value other than 0xBE or
 * 0xEF after 0xBE is written, causes a WDT reset as if the timer had run
 * out.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_TIMERS_WDT . WDT_LOCK
 */
#define  VTSS_F_ICPU_CFG_TIMERS_WDT_WDT_LOCK(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ICPU_CFG_TIMERS_WDT_WDT_LOCK     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ICPU_CFG_TIMERS_WDT_WDT_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Timer Tick Divider
 *
 * \details
 * Register: \a ICPU_CFG:TIMERS:TIMER_TICK_DIV
 */
#define VTSS_ICPU_CFG_TIMERS_TIMER_TICK_DIV  VTSS_IOREG(VTSS_TO_CFG,0x83)

/** 
 * \brief
 * The timer tick generator runs from a 250MHz base clock. By default, the
 * divider value generates a timer tick every 100 us (10 KHz). The timer
 * tick is used for all of the timers (except the WDT). This field must not
 * be set to generate a timer tick of less than 0.1 us (higher than 10
 * MHz). If this field is changed, it may take up to 2 ms before the timers
 * are running stable at the new frequency.
 *
 * \details 
 * The timer tick frequency is: 250MHz/(TIMER_TICK_DIV+1).
 *
 * Field: ::VTSS_ICPU_CFG_TIMERS_TIMER_TICK_DIV . TIMER_TICK_DIV
 */
#define  VTSS_F_ICPU_CFG_TIMERS_TIMER_TICK_DIV_TIMER_TICK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_ICPU_CFG_TIMERS_TIMER_TICK_DIV_TIMER_TICK_DIV     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_ICPU_CFG_TIMERS_TIMER_TICK_DIV_TIMER_TICK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,18)


/** 
 * \brief Timer value
 *
 * \details
 * Register: \a ICPU_CFG:TIMERS:TIMER_VALUE
 *
 * @param ri Replicator: x_TIMER_CNT (??), 0-2
 */
#define VTSS_ICPU_CFG_TIMERS_TIMER_VALUE(ri)  VTSS_IOREG(VTSS_TO_CFG,0x84 + (ri))


/** 
 * \brief Timer Reload Value
 *
 * \details
 * Register: \a ICPU_CFG:TIMERS:TIMER_RELOAD_VALUE
 *
 * @param ri Replicator: x_TIMER_CNT (??), 0-2
 */
#define VTSS_ICPU_CFG_TIMERS_TIMER_RELOAD_VALUE(ri)  VTSS_IOREG(VTSS_TO_CFG,0x87 + (ri))


/** 
 * \brief Timer Control
 *
 * \details
 * Register: \a ICPU_CFG:TIMERS:TIMER_CTRL
 *
 * @param ri Replicator: x_TIMER_CNT (??), 0-2
 */
#define VTSS_ICPU_CFG_TIMERS_TIMER_CTRL(ri)  VTSS_IOREG(VTSS_TO_CFG,0x8a + (ri))

/** 
 * \brief
 * When set the timer will automatically disable itself after it has
 * generated interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_TIMERS_TIMER_CTRL . ONE_SHOT_ENA
 */
#define  VTSS_F_ICPU_CFG_TIMERS_TIMER_CTRL_ONE_SHOT_ENA  VTSS_BIT(2)

/** 
 * \brief
 * When enabled, the corresponding timer decrements at each timer-tick. If
 * TIMER_CTRL.ONE_SHOT_ENA is set this field is cleared when the timer
 * reach 0 and interrupt is generated.
 *
 * \details 
 * 0: Timer is disabled
 * 1: Timer is enabled
 *
 * Field: ::VTSS_ICPU_CFG_TIMERS_TIMER_CTRL . TIMER_ENA
 */
#define  VTSS_F_ICPU_CFG_TIMERS_TIMER_CTRL_TIMER_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Set this field to force the reload of the timer, this will set the
 * TIMER_VALUE to TIMER_RELOAD_VALUE for the corresponding timer. This
 * field can be set at the same time as enabling the counter, in that case
 * the counter will be reloaded and then enabled for counting.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_TIMERS_TIMER_CTRL . FORCE_RELOAD
 */
#define  VTSS_F_ICPU_CFG_TIMERS_TIMER_CTRL_FORCE_RELOAD  VTSS_BIT(0)

/**
 * Register Group: \a ICPU_CFG:MEMCTRL
 *
 * DDR2/3 Memory Controller Registers
 */


/** 
 * \brief Control register
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_CTRL
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL   VTSS_IOREG(VTSS_TO_CFG,0x8d)

/** 
 * \brief
 * Set this field to postpone refresh of the SDRAM for as long as possible.
 * Refresh will not be initiated until the number of pending refreshes
 * reaches MEMCTRL_REF_PERIOD.MAX_PEND_REF.
 * Interrupt rutines and other high-priority tasks can set this field to
 * ensure un-interrupted access to the memory.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL . STALL_REF_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL_STALL_REF_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Set this field to force the memory controller to initialize the SDRAM.
 * This field is automatically cleared once the initialization sequence is
 * complete.
 * Note: All other memory controller reigsters must have been configured
 * appropriatly before setting this field.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL . INITIALIZE
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL_INITIALIZE  VTSS_BIT(0)


/** 
 * \brief Configuration register
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_CFG
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CFG    VTSS_IOREG(VTSS_TO_CFG,0x8e)

/** 
 * \brief
 * The number of data-bytes that is transmitted during one burst (of the
 * defined burst length: BURST_LEN).
 *
 * \details 
 * 0: 8 data-bytes per burst.
 * 1: 16 data-bytes per burst.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CFG . BURST_SIZE
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_BURST_SIZE  VTSS_BIT(10)

/** 
 * \brief
 * The burst size that is used by the SDRAM controller. The SDRAM must be
 * configured with the corresponding burst size (through the
 * MEMCTRL_MDSET_VAL register.)
 * Note: The number of data-bytes that is transmitted during one burst must
 * be encoded in the BURST_SIZE field.
 *
 * \details 
 * 0 : BURST4
 * 1 : BURST8
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CFG . BURST_LEN
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_BURST_LEN  VTSS_BIT(9)

/** 
 * \brief
 * Number of banks in the SDRAM configuration being used.
 *
 * \details 
 * 0 : 4 banks
 * 1 : 8 banks
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CFG . BANK_CNT
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_BANK_CNT  VTSS_BIT(8)

/** 
 * \brief
 * This field should be programmed to 1 less than the number of row address
 * bits for the SDRAM configuration in use.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CFG . MSB_ROW_ADDR
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_MSB_ROW_ADDR(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_MSB_ROW_ADDR     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_MSB_ROW_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * This field should be programmed to 1 less than the number of column
 * address bits for the SDRAM configuration in use.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CFG . MSB_COL_ADDR
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_MSB_COL_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_MSB_COL_ADDR     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_MSB_COL_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Status register
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_STAT
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_STAT   VTSS_IOREG(VTSS_TO_CFG,0x8f)

/** 
 * \brief
 * This field is set once initalization of the SDRAM is done.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_STAT . INIT_DONE
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_STAT_INIT_DONE  VTSS_BIT(0)


/** 
 * \brief Refresh period configuration
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_REF_PERIOD
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_REF_PERIOD  VTSS_IOREG(VTSS_TO_CFG,0x90)

/** 
 * \brief
 * Maximum number of refreshes that are allowed to be outstanding at any
 * time. If the number of outstanding refreshes reaches this value, the
 * memory controller will stop the data transfer in progress, issue the
 * required number of refreshes and then continue.
 * This field must not be set to 0 (will disable the controller).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_REF_PERIOD . MAX_PEND_REF
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_REF_PERIOD_MAX_PEND_REF(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_REF_PERIOD_MAX_PEND_REF     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_REF_PERIOD_MAX_PEND_REF(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Refresh interval of the SDRAM expressed in terms of number of clock
 * cycles. This value is calculated by dividing the average periodic
 * refresh interval (tREFI) by the clock period.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_REF_PERIOD . REF_PERIOD
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_REF_PERIOD_REF_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_REF_PERIOD_REF_PERIOD     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_REF_PERIOD_REF_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Timing register 0
 *
 * \details
 * All asynchronous timing delays should be converted into the equivalent
 * number of core-clocks (round up). Note: The SDRAM datasheet may specify
 * parameters in a number of tCK cycles these are the same as clock cycles.
 *
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_TIMING0
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0  VTSS_IOREG(VTSS_TO_CFG,0x92)

/** 
 * \brief
 * Suggested value is 4. Value of 4 gives 2 cycles turn around time between
 * the last read from the SDRAM and the first write to the SDRAM.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0 . RD_TO_WR_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_TO_WR_DLY(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_TO_WR_DLY     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_TO_WR_DLY(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/** 
 * \brief
 * tRAS - 1 clock. Minimum delay between RAS and precharge commands.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0 . RAS_TO_PRECH_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RAS_TO_PRECH_DLY(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RAS_TO_PRECH_DLY     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RAS_TO_PRECH_DLY(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * This value depends on the burst length used by the configruation.
 * BURST4: CL + tWR.
 * BURST8: CL + 2 + tWR.
 * Minimum delay between write and precharge commands.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0 . WR_TO_PRECH_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_WR_TO_PRECH_DLY(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_WR_TO_PRECH_DLY     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_WR_TO_PRECH_DLY(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * This value depends on the burst length used by the configruation.
 * BURST4: 1.
 * BURST8: 3.
 * Minimum delay between read and precharge commands.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0 . RD_TO_PRECH_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_TO_PRECH_DLY(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_TO_PRECH_DLY     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_TO_PRECH_DLY(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * CL - 3. Delay between the issue of a write command and when the data is
 * transitted. CL must not be less than 3 (this register cannot be
 * configued to less than 0).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0 . WR_DATA_XFR_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_WR_DATA_XFR_DLY(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_WR_DATA_XFR_DLY     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_WR_DATA_XFR_DLY(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * This field should be programmed to 1, the receive window is also ajusted
 * by the DQS drift detection logic. Which adds an additional delay on top
 * of this value.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0 . RD_DATA_XFR_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_DATA_XFR_DLY(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_DATA_XFR_DLY     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_DATA_XFR_DLY(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Timing register 1
 *
 * \details
 * All asynchronous timing delays should be converted into the equivalent
 * number of core-clocks (round up). Note: The SDRAM datasheet may specify
 * parameters in a number of tCK cycles these are the same as clock cycles.
 *
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_TIMING1
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1  VTSS_IOREG(VTSS_TO_CFG,0x93)

/** 
 * \brief
 * tRC - 1. Minimum delay between successive open commands to the same
 * bank.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1 . RAS_TO_RAS_SAME_BANK_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_RAS_TO_RAS_SAME_BANK_DLY(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_RAS_TO_RAS_SAME_BANK_DLY     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_RAS_TO_RAS_SAME_BANK_DLY(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * tFAW - 1 for an 8-bank DDR2 SDRAM. 0 for a 4-bank DDR2 SDRAM. For 8 bank
 * DDR2 SDRAM configurations; this value specifies an additional row
 * opening restriction when a fifth bank is opened consecutively after 4
 * banks have been opened with minimum tRRD on the same chip select.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1 . BANK8_FAW_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_BANK8_FAW_DLY(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_BANK8_FAW_DLY     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_BANK8_FAW_DLY(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * tRP - 1. Minimum delay between issuing a precharge command and a RAS
 * command to the same bank.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1 . PRECH_TO_RAS_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_PRECH_TO_RAS_DLY(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_PRECH_TO_RAS_DLY     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_PRECH_TO_RAS_DLY(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * tRRD - 1. Minimum delay between two RAS commands issued to the same chip
 * select.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1 . RAS_TO_RAS_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_RAS_TO_RAS_DLY(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_RAS_TO_RAS_DLY     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_RAS_TO_RAS_DLY(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * tRCD - AL - 1. Mimimum delay between issuing of a RAS command and a CAS
 * command to the same bank.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1 . RAS_TO_CAS_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_RAS_TO_CAS_DLY(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_RAS_TO_CAS_DLY     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_RAS_TO_CAS_DLY(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * BURST4: CL + tWTR, where tWTR converted to clock cycles must be atleast
 * 2.
 * BURST8: CL + 2 + tWTR, where tWTR converted to clock cycles must be
 * atleast 2.
 * Minimum delay from a write to a read command.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1 . WR_TO_RD_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_WR_TO_RD_DLY(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_WR_TO_RD_DLY     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_WR_TO_RD_DLY(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Timing register 2
 *
 * \details
 * All asynchronous timing delays should be converted into the equivalent
 * number of core-clocks (round up). Note: The SDRAM datasheet may specify
 * parameters in a number of tCK cycles these are the same as clock cycles.
 *
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_TIMING2
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2  VTSS_IOREG(VTSS_TO_CFG,0x94)

/** 
 * \brief
 * tRP - 1 for 4 bank memory and tRPA - 1 for 8 bank memory. Minimum delay
 * between issuing a precharge all command and a LM/RAS command to any
 * bank.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2 . PRECH_ALL_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_PRECH_ALL_DLY(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_PRECH_ALL_DLY     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_PRECH_ALL_DLY(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/** 
 * \brief
 * tMRD - 1. Minimum delay required after a modeset command and before
 * issuing any other command.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2 . MDSET_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_MDSET_DLY(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_MDSET_DLY     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_MDSET_DLY(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/** 
 * \brief
 * tRFC - 1. Mimimum delay between issuing of a refresh command and a RAS
 * command. This value is assumed to be less than 67 clocks.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2 . REF_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_REF_DLY(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_REF_DLY     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_REF_DLY(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Four hundred nanoseconds expressed in clock periods (round up). This is
 * used during the initialization sequence.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2 . FOUR_HUNDRED_NS_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_FOUR_HUNDRED_NS_DLY(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_FOUR_HUNDRED_NS_DLY     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_FOUR_HUNDRED_NS_DLY(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Timing register 3
 *
 * \details
 * All asynchronous timing delays should be converted into the equivalent
 * number of core-clocks (round up). Note: The SDRAM datasheet may specify
 * parameters in a number of tCK cycles these are the same as clock cycles.
 *
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_TIMING3
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3  VTSS_IOREG(VTSS_TO_CFG,0x95)

/** 
 * \brief
 * Value to be used is AL + CL - 4. Number of clocks after the write
 * command that the ODT signal for the SDRAM should be turned on. This
 * implies that AL + CL should be greater than or equal to 4.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3 . ODT_WR_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_ODT_WR_DLY(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_ODT_WR_DLY     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_ODT_WR_DLY(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Value to be used is MEMCTRL_TIMING0.RD_DATA_XFR_DLY. Number of clocks
 * after the read command to enable of local on-die-termination (ODT), this
 * delay is also ajusted by the DQS drift detection logic. Which adds an
 * additional delay on top of this value.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3 . LOCAL_ODT_RD_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_LOCAL_ODT_RD_DLY(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_LOCAL_ODT_RD_DLY     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_LOCAL_ODT_RD_DLY(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * AL + CL - 1 but no less than 3. Minimum delay between a write command
 * issued to one chip select followed by a read command to the other chip
 * select. This value is less than the MEMCTRL_TIMING1:WR_TO_RD_DLY.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3 . WR_TO_RD_CS_CHANGE_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_WR_TO_RD_CS_CHANGE_DLY(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_WR_TO_RD_CS_CHANGE_DLY     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_WR_TO_RD_CS_CHANGE_DLY(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Mode Register 0 Value
 *
 * \details
 * Note: The memory controller will automatically generate the required
 * bank-addresses used for addressing the different mode registers. Do not
 * specify bank-addresses in this register.
 *
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_MR0_VAL
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_MR0_VAL  VTSS_IOREG(VTSS_TO_CFG,0x96)

/** 
 * \brief
 * Value to be programmed into the mode register (0) during SDRAM
 * intialization.
 * Bit 8 (DLL Reset) of this register must be set to 0, the memory
 * controller automatically sets this bit when required during the
 * initialization procedure.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_MR0_VAL . MR0_VAL
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_MR0_VAL_MR0_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_MR0_VAL_MR0_VAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_MR0_VAL_MR0_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Mode Register 1 / Extended Mode Register Value
 *
 * \details
 * Note: The memory controller will automatically generate the required
 * bank-addresses used for addressing the different mode registers. Do not
 * specify bank-addresses in this register.
 *
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_MR1_VAL
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_MR1_VAL  VTSS_IOREG(VTSS_TO_CFG,0x97)

/** 
 * \brief
 * Value to be programmed into mode register 1 / extended mode register
 * during SDRAM intialization.
 * Bits 7 thorugh 9 (OCD Calibration Program) of this register must be set
 * to 0x7, the memory controller set this field when required during the
 * initialization procedure.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_MR1_VAL . MR1_VAL
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_MR1_VAL_MR1_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_MR1_VAL_MR1_VAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_MR1_VAL_MR1_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Mode Register 2 / Extended Mode Register 2 Value
 *
 * \details
 * Note: The memory controller will automatically generate the required
 * bank-addresses used for addressing the different mode registers. Do not
 * specify bank-addresses in this register.
 *
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_MR2_VAL
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_MR2_VAL  VTSS_IOREG(VTSS_TO_CFG,0x98)

/** 
 * \brief
 * Value to be programmed into mode register 2 / extended mode register 2
 * during SDRAM intialization.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_MR2_VAL . MR2_VAL
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_MR2_VAL_MR2_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_MR2_VAL_MR2_VAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_MR2_VAL_MR2_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Mode Register 3 / Extended Mode Register 3 Value
 *
 * \details
 * Note: The memory controller will automatically generate the required
 * bank-addresses used for addressing the different mode registers. Do not
 * specify bank-addresses in this register.
 *
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_MR3_VAL
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_MR3_VAL  VTSS_IOREG(VTSS_TO_CFG,0x99)

/** 
 * \brief
 * Value to be programmed into mode register 3 / extended mode register 3
 * during SDRAM intialization.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_MR3_VAL . MR3_VAL
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_MR3_VAL_MR3_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_MR3_VAL_MR3_VAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_MR3_VAL_MR3_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief TBA
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_TERMRES_CTRL
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL  VTSS_IOREG(VTSS_TO_CFG,0x9a)

/** 
 * \brief
 * Set this fied to extend the ODT termination output by one clock during
 * write operations.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL . ODT_WR_EXT
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_ODT_WR_EXT  VTSS_BIT(3)

/** 
 * \brief
 * Enables external termination during write operations.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL . ODT_WR_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_ODT_WR_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Set this fied to extend the local termination by one clock during read
 * operations.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL . LOCAL_ODT_RD_EXT
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_LOCAL_ODT_RD_EXT  VTSS_BIT(1)

/** 
 * \brief
 * Enables local termination during a read operation.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL . LOCAL_ODT_RD_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_LOCAL_ODT_RD_ENA  VTSS_BIT(0)


/** 
 * \brief DQS window configuration
 *
 * \details
 * This register is replicated two times, once for each Byte Lane (first
 * replication corresponds to Byte Lane 0).
 * After initialization of the DRAM memory controller the read-data-path
 * must be trained. This is needed so that the controller knows exactly
 * when to sample read-data from the DRAM(s). During training a window of
 * DQS_DLY settings is determined during which correct read-data is
 * returned from the DRAM(s), after finding the window the mid-window-value
 * (round down) is programmed into DQS_DLY and then auto-adjusting is
 * enabled by setting MEMCTRL_DQS_AUTO:DQS_AUTO_ENA. Training is done per
 * Byte-Lane, two DRAM addresses are needed for training (a low and a high
 * address), the actual addresses depends on the number of byte-lanes in
 * the system, and which byte-lane that is trained: In a system with _one_
 * byte lane (x8), addresses 0x0 and 0xF is used. In a system with _two_
 * byte lanes (x16), DRAM addresses 0x0 and 0xE is used for training Byte
 * Lane 0, and addresses 0x1 and 0xF is used for training Byte Lane 1.
 * Training is done for in the following steps:
 * 1) Clear DRAM addresses 0x0 through 0xF by writing 0x00 to each address.
 * 2) Write 0xFF to both the low and the high DRAM address (the actual
 * addresses are defined in the above section) .
 * 3) Find the lower DQS_DLY limit by sweeping through delay settings
 * (DQS_DLY, starting from 0x0) while reading the high DRAM address.
 * Continue sweeping (incrementing DQS_DLY) until 0xFF is returned when
 * reading the high address.
 * 4) Find the upper DQS_DLY limit by continuing the sweep through delay
 * settings (starting at the lower limit determined during step 3) while
 * reading the low DRAM address. Continue sweeping (incrementing DQS_DLY)
 * until reading from the low address no longer returns 0xFF. The upper
 * limit is then the current DQS_DLY - 1.
 *
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_DQS_DLY
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_DLY  VTSS_IOREG(VTSS_TO_CFG,0x9c)

/** 
 * \brief
 * This field configures read-window delay as an offset in 1/4 clock cycles
 * from the fixed read-daly configured in MEMCTRL_TIMING0:RD_DATA_XFR_DLY.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_DLY . DQS_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_DLY_DQS_DLY(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_DLY_DQS_DLY     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_DLY_DQS_DLY(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief DQS window automatic drift detect/ajust
 *
 * \details
 * This register is subjected to the same replication scheme and encoding
 * as MEMCTRL_DQS_DLY.
 *
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_DQS_AUTO
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO  VTSS_IOREG(VTSS_TO_CFG,0x9d)

/** 
 * \brief
 * Set this field to enable automatic detection of drifting
 * read-data-window. Drifting of the DQS read window occurs as the chip is
 * heating/cooling. When this field is set MEMCTRL_DQS_DLY.DQS_DLY field
 * will automatically be ajusted when a drift is detected by the hardware.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO . DQS_AUTO_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_AUTO_ENA  VTSS_BIT(0)


/** 
 * \brief Control register
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMPHY_CFG
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMPHY_CFG     VTSS_IOREG(VTSS_TO_CFG,0x9e)

/** 
 * \brief
 * Soft-reset to the FIFO blocks in the memory controller physical
 * interface.
 *
 * \details 
 * 0: PHY FIFOs is in working mode.
 * 1: PHY FIFOs is forced in reset.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_CFG . PHY_FIFO_RST
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_FIFO_RST  VTSS_BIT(7)

/** 
 * \brief
 * Set to enable output drive of the ODT output.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_CFG . PHY_ODT_OE
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_ODT_OE  VTSS_BIT(4)

/** 
 * \brief
 * Set to enable output drive of the CK/nCK and CKE outputs.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_CFG . PHY_CK_OE
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_CK_OE  VTSS_BIT(3)

/** 
 * \brief
 * Set to enable output drive of the Command Lane outputs.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_CFG . PHY_CL_OE
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_CL_OE  VTSS_BIT(2)

/** 
 * \brief
 * Set this field to enable the SSTL drivers/receivers in the memory
 * controllers physical interface.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_CFG . PHY_SSTL_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_SSTL_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Master reset to the memory controller physical interface.
 *
 * \details 
 * 0: PHY is in working mode.
 * 1: PHY is forced in reset.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_CFG . PHY_RST
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_RST  VTSS_BIT(0)


/** 
 * \brief Impedance calibration
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMPHY_ZCAL
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL    VTSS_IOREG(VTSS_TO_CFG,0xa5)

/** 
 * \brief
 * Together with the external reference resistor this field configures the
 * SSTL On-Die-Termination (ODT) impedance.
 * This field must be configured prior to, or at the same time as, setting
 * the ZCAL_ENA field.
 *
 * \details 
 * 2: 150ohms
 * 5: 75ohms
 * 8: 50ohms
 * Ohter values are reserved.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL . ZCAL_PROG_ODT
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_ZCAL_PROG_ODT(x)  VTSS_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_ZCAL_PROG_ODT     VTSS_ENCODE_BITMASK(5,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_ZCAL_PROG_ODT(x)  VTSS_EXTRACT_BITFIELD(x,5,4)

/** 
 * \brief
 * Together with the external reference resistor this field configures the
 * SSTL output impedance.
 * This field must be configured prior to, or at the same time as, setting
 * the ZCAL_ENA field.
 *
 * \details 
 * 11: 40ohms
 * Other values are reserved.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL . ZCAL_PROG
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_ZCAL_PROG(x)  VTSS_ENCODE_BITFIELD(x,1,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_ZCAL_PROG     VTSS_ENCODE_BITMASK(1,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_ZCAL_PROG(x)  VTSS_EXTRACT_BITFIELD(x,1,4)

/** 
 * \brief
 * Set this field to start automatic SSTL output and ODT impedance
 * calibration. This field is cleared when the automatic calibration has
 * completed.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL . ZCAL_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_ZCAL_ENA  VTSS_BIT(0)

/**
 * Register Group: \a ICPU_CFG:TWI_DELAY
 *
 * Configuration registers
 */


/** 
 * \brief Configuration registers
 *
 * \details
 * Register: \a ICPU_CFG:TWI_DELAY:TWI_CONFIG
 */
#define VTSS_ICPU_CFG_TWI_DELAY_TWI_CONFIG   VTSS_IOREG(VTSS_TO_CFG,0xa9)

/** 
 * \brief
 * Configure the hold time delay to apply to SDA after SCK when
 * transmitting from the device. The delay depends on the VCore system
 * clock period. If for example the VCore system clock is 125MHz then the
 * period is 8ns, in turn the hold time will then be (TWI_CNT_RELOAD+2) *
 * 8ns. Replace the clock period for other VCore system frequencies.
 * The resulting value should be as close to 300ns as possible without
 * going below 300ns.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_TWI_DELAY_TWI_CONFIG . TWI_CNT_RELOAD
 */
#define  VTSS_F_ICPU_CFG_TWI_DELAY_TWI_CONFIG_TWI_CNT_RELOAD(x)  VTSS_ENCODE_BITFIELD(x,1,8)
#define  VTSS_M_ICPU_CFG_TWI_DELAY_TWI_CONFIG_TWI_CNT_RELOAD     VTSS_ENCODE_BITMASK(1,8)
#define  VTSS_X_ICPU_CFG_TWI_DELAY_TWI_CONFIG_TWI_CNT_RELOAD(x)  VTSS_EXTRACT_BITFIELD(x,1,8)

/** 
 * \brief
 * Set this field to enable hold time on the TWI SDA output. When enabled
 * the TWI_CONFIG.TWI_CNT_RELOAD field determines the amount of hold time
 * to apply to SDA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_TWI_DELAY_TWI_CONFIG . TWI_DELAY_ENABLE
 */
#define  VTSS_F_ICPU_CFG_TWI_DELAY_TWI_CONFIG_TWI_DELAY_ENABLE  VTSS_BIT(0)


#endif /* _VTSS_LUTON26_REGS_ICPU_CFG_H_ */
