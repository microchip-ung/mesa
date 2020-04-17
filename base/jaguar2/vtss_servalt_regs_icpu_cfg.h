// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_SERVALT_REGS_ICPU_CFG_H_
#define _VTSS_SERVALT_REGS_ICPU_CFG_H_


#include "vtss_servalt_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a ICPU_CFG
 *
 * AMBA Top Level Settings
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
 * \brief
 * General purpose 8 times 32-bit registers for software development and
 * debug.
 * Note: This register is only reset by the device's reset input, i.e. it
 * is not affected by soft reset!
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GPR . GPR
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GPR_GPR(x)  (x)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GPR_GPR     0xffffffff
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GPR_GPR(x)  (x)


/** 
 * \brief Reset Settings
 *
 * \details
 * Register: \a ICPU_CFG:CPU_SYSTEM_CTRL:RESET
 */
#define VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_RESET  VTSS_IOREG(VTSS_TO_CFG,0x8)

/** 
 * \brief
 * Set this field to enable VCore System reset protection. It is possible
 * to protect the VCore System from soft-reset (issued via
 * RESET.CORE_RST_FORCE) and watchdog-timeout. When this field is set the
 * aforementioned resets only reset the VCore CPU, not the VCore System.
 *
 * \details 
 * 0: Soft-reset and WDT-event and reset entire VCore
 * 1: Soft-reset and WDT-event only reset the VCore CPU
 *
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_RESET . CORE_RST_CPU_ONLY
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_RESET_CORE_RST_CPU_ONLY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_RESET_CORE_RST_CPU_ONLY  VTSS_BIT(3)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_RESET_CORE_RST_CPU_ONLY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set this field to enable VCore reset protection. It is possible to
 * protect the entire VCore from chip-level soft-reset (issued via
 * DEVCPU_GCB::SOFT_RST.SOFT_CHIP_RST). Setting this field does not protect
 * agains hard-reset of the chip (by asserting the reset pin).
 *
 * \details 
 * 0: No reset protection
 * 1: VCore is protected from chip-level-soft-reset
 *
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_RESET . CORE_RST_PROTECT
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_RESET_CORE_RST_PROTECT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_RESET_CORE_RST_PROTECT  VTSS_BIT(2)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_RESET_CORE_RST_PROTECT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

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
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_RESET_CORE_RST_FORCE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_RESET_CORE_RST_FORCE  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_RESET_CORE_RST_FORCE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Clear this field to release the DDR2/3 controller from reset.
 *
 * \details 
 * 0: Memory controller is not reset
 * 1: Memory controller is forced in reset
 *
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_RESET . MEM_RST_FORCE
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_RESET_MEM_RST_FORCE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_RESET_MEM_RST_FORCE  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_RESET_MEM_RST_FORCE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief General control
 *
 * \details
 * Register: \a ICPU_CFG:CPU_SYSTEM_CTRL:GENERAL_CTRL
 */
#define VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL  VTSS_IOREG(VTSS_TO_CFG,0x9)

/** 
 * \brief
 * Set this field to disable sleep of the VCore CPU bus interface.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL . CPU_BUSIF_SLEEP_DIS
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_CPU_BUSIF_SLEEP_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_CPU_BUSIF_SLEEP_DIS  VTSS_BIT(14)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_CPU_BUSIF_SLEEP_DIS(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Set this field to enable interrupt from the VCore CPU bus interface in
 * case of write errors on the internal bus. Clear this field to clear
 * pending write-error interrupts (then reenable field to receive new
 * interrupts).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL . CPU_BUSIF_WERR_ENA
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_CPU_BUSIF_WERR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_CPU_BUSIF_WERR_ENA  VTSS_BIT(13)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_CPU_BUSIF_WERR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * The default value of this field depends on strapping of the VCore.
 * Set this field to make the 8051 boot from internal ROM image, the
 * purpose of this boot-mode is implementing simple startup procedure for
 * chips w.o. internal CPU running.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL . CPU_8051_IROM_ENA
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_CPU_8051_IROM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_CPU_8051_IROM_ENA  VTSS_BIT(12)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_CPU_8051_IROM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Set this field to disable the MIPS core (and instead enable 8051).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL . CPU_MIPS_DIS
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_CPU_MIPS_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_CPU_MIPS_DIS  VTSS_BIT(11)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_CPU_MIPS_DIS(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * MIIM slave address when MIIM slave interface is enabled.
 *
 * \details 
 * 0: Address 0
 * 1: Address 31
 *
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL . IF_MIIM_SLV_ADDR_SEL
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_MIIM_SLV_ADDR_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_MIIM_SLV_ADDR_SEL  VTSS_BIT(10)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_MIIM_SLV_ADDR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * The default value of this field depends on strapping of the VCore.
 * Set this field to enable the MIIM slave-interface on the GPIOs.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL . IF_MIIM_SLV_ENA
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_MIIM_SLV_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_MIIM_SLV_ENA  VTSS_BIT(9)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_MIIM_SLV_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * The default value of this field depends on strapping of the VCore (the
 * PI_nDone signal).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL . IF_PI_SLV_DONEPOL
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_PI_SLV_DONEPOL(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_PI_SLV_DONEPOL  VTSS_BIT(8)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_PI_SLV_DONEPOL(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * The default value of this field depends on strapping of the VCore.
 * Set this field to force PI interfaces into master mode (and enable PI on
 * GPIOs).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL . IF_PI_MST_ENA
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_PI_MST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_PI_MST_ENA  VTSS_BIT(7)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_PI_MST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * The default value of this field depends on strapping of the VCore.
 * Set this field to force PI interfaces into slave mode (and enable PI on
 * GPIOs).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL . IF_PI_SLV_ENA
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_PI_SLV_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_PI_SLV_ENA  VTSS_BIT(6)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_PI_SLV_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * The default value of this field depends on strapping of the VCore.
 * Select the owner of the dedicated SI interface. Note, if the SI slave is
 * not owner of this interface, it is not possible for an external CPU to
 * access registers in the chip via the dedicated SI interface.
 * It is possible for VCore CPU to boot via SI and then change overship to
 * either SI Slave or SI Master Controller.
 *
 * \details 
 * 00 : SI Slave
 * 01 : SI Boot Master
 * 10 : SI Master Controller
 *
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL . IF_SI_OWNER
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_SI_OWNER(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_SI_OWNER     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_IF_SI_OWNER(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Hooked up to the master contention input (ss_in_n) of the SPI Master
 * block.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL . SIMC_SSP_ENA
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_SIMC_SSP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_SIMC_SSP_ENA  VTSS_BIT(3)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_SIMC_SSP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * The default value of this field depends on strapping of the VCore.
 * Set this field to force the MIPS VCore CPU into Big-Endian mode.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL . CPU_BE_ENA
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_CPU_BE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_CPU_BE_ENA  VTSS_BIT(2)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_CPU_BE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * The default value of this field depends on strapping of the VCore.
 * Clear this field to allow booting of the VCore CPU, while this field is
 * set the VCore CPU is held in reset.
 *
 * \details 
 * 0: VCore CPU is allowed to boot
 * 1: VCore CPU is forced in reset
 *
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL . CPU_DIS
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_CPU_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_CPU_DIS  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_CPU_DIS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Use this field to change from Boot mode to Normal mode. In Boot mode,
 * the reset vector of the VCore CPU maps to CS0 on the FLASH interface.
 * When in Normal mode, this address maps instead to the DRAM Controller.
 * The DRAM Controller must be operational before disabling Boot mode.
 * After setting Boot mode, this register must be read back. The change in
 * Boot mode takes effect during read.
 *
 * \details 
 * 0: The VCore memory map is in Normal mode.
 * 1: The VCore memory map is in Boot mode.
 *
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL . BOOT_MODE_ENA
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_BOOT_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_BOOT_MODE_ENA  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL_BOOT_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief General status
 *
 * \details
 * Register: \a ICPU_CFG:CPU_SYSTEM_CTRL:GENERAL_STAT
 */
#define VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT  VTSS_IOREG(VTSS_TO_CFG,0xa)

/** 
 * \brief
 * This field is set if the PI slave interface has received error
 * indication from the SBA fabric during a write access.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT . PI_SLV_WR_ERR
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT_PI_SLV_WR_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT_PI_SLV_WR_ERR  VTSS_BIT(9)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT_PI_SLV_WR_ERR(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * This field is set if the PI slave interface has received error
 * indication from the SBA fabric during a read access. The PI slave will
 * have returned 0x88888888 for the offending read.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT . PI_SLV_RD_ERR
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT_PI_SLV_RD_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT_PI_SLV_RD_ERR  VTSS_BIT(8)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT_PI_SLV_RD_ERR(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Shows the value of the VCore Cfg strapping inputs.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT . VCORE_CFG
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT_VCORE_CFG(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT_VCORE_CFG     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT_VCORE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Debug information for checking register read/write problems. This is a
 * read-only field which can only be cleared by reset of the VCore System.
 *
 * \details 
 * 0: No errors detected.
 * 1: Non-32bit access to VCore or SwC registers, access has been
 * discarded, read returns 0x8888 or 0x88.
 * 2: SwC registers not ready when accessed, access has been discarded,
 * read returns 0x88888888.
 * 3: SwC registers reported error, check DEVCPU_ORG::ERR_CNTS for error,
 * read returns 0x88888888.
 * 4: Unimplemented VCore register, access has been discarded, read returns
 * 0x88888888.
 *
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT . REG_IF_ERR
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT_REG_IF_ERR(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT_REG_IF_ERR     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT_REG_IF_ERR(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/** 
 * \brief
 * This field is set if the VCore CPU has entered sleep mode.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT . CPU_SLEEP
 */
#define  VTSS_F_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT_CPU_SLEEP(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT_CPU_SLEEP  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_STAT_CPU_SLEEP(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ICPU_CFG:PI_MST
 *
 * Parallel Interface Configuration
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
 * Disable Automatic Tester Equipment mode for the parallel interface. This
 * mode is used during production testing for controlled loading of CPU.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_MST_CFG . ATE_MODE_DIS
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_CFG_ATE_MODE_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_MST_CFG_ATE_MODE_DIS  VTSS_BIT(7)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_MST_CFG_ATE_MODE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Controls the clock-polarity of the PI Master.
 *
 * \details 
 * 0: Rising edge of the clock sets and samples signals.
 * 1: Falling edge of the clock sets and samples signals.
 *
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_MST_CFG . CLK_POL
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_CFG_CLK_POL(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_MST_CFG_CLK_POL  VTSS_BIT(6)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_MST_CFG_CLK_POL(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Controls drive of address and control signals between transfers. See
 * also PI_MST_CTRL.CS_TRISTATE_CTRL.
 *
 * \details 
 * 0: Address and control signals are high-Z between transfers.
 * 1: Address and control signals are driven between transfers.
 *
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_MST_CFG . TRISTATE_CTRL
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_CFG_TRISTATE_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_MST_CFG_TRISTATE_CTRL  VTSS_BIT(5)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_MST_CFG_TRISTATE_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Controls the clock for the PI Controller. Setting this field to 0 or 1
 * value is illegal.
 *
 * \details 
 * The PI interface frequency is: 250MHz/CLK_DIV.
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
 */
#define VTSS_ICPU_CFG_PI_MST_PI_MST_CTRL     VTSS_IOREG(VTSS_TO_CFG,0xc)

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
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_CTRL_DEVICE_PACED_XFER_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_MST_CTRL_DEVICE_PACED_XFER_ENA  VTSS_BIT(22)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_MST_CTRL_DEVICE_PACED_XFER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

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
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_CTRL_DEVICE_PACED_TIMEOUT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_MST_CTRL_DEVICE_PACED_TIMEOUT_ENA  VTSS_BIT(21)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_MST_CTRL_DEVICE_PACED_TIMEOUT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

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
 * Controls drive of PI_nCS[x] between transfers.
 *
 * \details 
 * 0: PI_nCS[x] is high-Z between transfers.
 * 1: PI_nCS[x] is driven inactive between transfers.
 *
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_MST_CTRL . CS_TRISTATE_CTRL
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_CTRL_CS_TRISTATE_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_MST_CTRL_CS_TRISTATE_CTRL  VTSS_BIT(17)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_MST_CTRL_CS_TRISTATE_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

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
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_CTRL_DONE_POL(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_MST_CTRL_DONE_POL  VTSS_BIT(16)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_MST_CTRL_DONE_POL(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

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
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_CTRL_SMPL_ON_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_MST_CTRL_SMPL_ON_DONE  VTSS_BIT(15)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_MST_CTRL_SMPL_ON_DONE(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

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
 */
#define VTSS_ICPU_CFG_PI_MST_PI_MST_STATUS   VTSS_IOREG(VTSS_TO_CFG,0xd)

/** 
 * \brief
 * If a timeout is enabled and timeout occurs during a device-paced
 * transfer, this bit is set.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_MST_STATUS . TIMEOUT_ERR_STICKY
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_MST_STATUS_TIMEOUT_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_MST_STATUS_TIMEOUT_ERR_STICKY  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_MST_STATUS_TIMEOUT_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PI Slave Configuration
 *
 * \details
 * Register: \a ICPU_CFG:PI_MST:PI_SLV_CFG
 */
#define VTSS_ICPU_CFG_PI_MST_PI_SLV_CFG      VTSS_IOREG(VTSS_TO_CFG,0xe)

/** 
 * \brief
 * See ICPU_CFG::PI_SLV_CFG.DONEPOL_SET for more information.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_SLV_CFG . DONEPOL_VAL
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_SLV_CFG_DONEPOL_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_SLV_CFG_DONEPOL_VAL  VTSS_BIT(24)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_SLV_CFG_DONEPOL_VAL(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * Set this field to force the value in ICPU_CFG::PI_SLV_CFG.DONEPOL_VAL
 * into ICPU_CFG::GENERAL_CTRL.IF_PI_SLV_DONEPOL. This field is immediately
 * cleared.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_SLV_CFG . DONEPOL_SET
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_SLV_CFG_DONEPOL_SET(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_SLV_CFG_DONEPOL_SET  VTSS_BIT(23)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_SLV_CFG_DONEPOL_SET(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * Set to configure PI interface for big-endian mode.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_SLV_CFG . BIGENDIAN
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_SLV_CFG_BIGENDIAN(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_SLV_CFG_BIGENDIAN  VTSS_BIT(22)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_SLV_CFG_BIGENDIAN(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Configure a minimum number of cycles after release of NCS until ndone is
 * no longer driven by device. The device will deassert ndone value when
 * NCS is released, this setting allows parking of the ndone at inactive
 * level before releasing drive of output.
 *
 * \details 
 * 0: Immediate release of ndone (async path from CS input).
 * n: Wait at least n+1 clocks after CS release until ndone is released.
 *
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_SLV_CFG . DONEPARK
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_SLV_CFG_DONEPARK(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_SLV_CFG_DONEPARK     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_SLV_CFG_DONEPARK(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/** 
 * \brief
 * Configures number of clock cycles to delay nDone indication for read
 * operations after accerss is done.
 *
 * \details 
 * n: Wait n clocks after read data ready before asserting nDone
 * indication.
 *
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_SLV_CFG . DONEWAIT
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_SLV_CFG_DONEWAIT(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_SLV_CFG_DONEWAIT     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_SLV_CFG_DONEWAIT(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Configures number of clock cycles after detecting asserted CS to
 * control/data is sampled.
 *
 * \details 
 * n: Wait n clocks after detecting CS before sampling control/data.
 *
 * Field: ::VTSS_ICPU_CFG_PI_MST_PI_SLV_CFG . CSWAIT
 */
#define  VTSS_F_ICPU_CFG_PI_MST_PI_SLV_CFG_CSWAIT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ICPU_CFG_PI_MST_PI_SLV_CFG_CSWAIT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ICPU_CFG_PI_MST_PI_SLV_CFG_CSWAIT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a ICPU_CFG:SPI_MST
 *
 * SPI boot master
 */


/** 
 * \brief SPI boot master configuration
 *
 * \details
 * Register: \a ICPU_CFG:SPI_MST:SPI_MST_CFG
 */
#define VTSS_ICPU_CFG_SPI_MST_SPI_MST_CFG    VTSS_IOREG(VTSS_TO_CFG,0xf)

/** 
 * \brief
 * Set to enable 32bit address mode. In 32bit addressing mode only CS0 is
 * used, the SPI address region is limited to 256MByte reserved for the SI
 * interface.
 *
 * \details 
 * 0: Use 24bit addressing with 4 different CS.
 * 1: Use 32bit addressing on CS0, max 256MByte
 *
 * Field: ::VTSS_ICPU_CFG_SPI_MST_SPI_MST_CFG . A32B_ENA
 */
#define  VTSS_F_ICPU_CFG_SPI_MST_SPI_MST_CFG_A32B_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ICPU_CFG_SPI_MST_SPI_MST_CFG_A32B_ENA  VTSS_BIT(11)
#define  VTSS_X_ICPU_CFG_SPI_MST_SPI_MST_CFG_A32B_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

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
#define  VTSS_F_ICPU_CFG_SPI_MST_SPI_MST_CFG_FAST_READ_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_ICPU_CFG_SPI_MST_SPI_MST_CFG_FAST_READ_ENA  VTSS_BIT(10)
#define  VTSS_X_ICPU_CFG_SPI_MST_SPI_MST_CFG_FAST_READ_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

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
 * The SPI interface frequency is: 250MHz/CLK_DIV.
 *
 * Field: ::VTSS_ICPU_CFG_SPI_MST_SPI_MST_CFG . CLK_DIV
 */
#define  VTSS_F_ICPU_CFG_SPI_MST_SPI_MST_CFG_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_ICPU_CFG_SPI_MST_SPI_MST_CFG_CLK_DIV     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_ICPU_CFG_SPI_MST_SPI_MST_CFG_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief SPI boot master status
 *
 * \details
 * This is a replicated register, where each replication holds the status
 * for one chip select.
 *
 * Register: \a ICPU_CFG:SPI_MST:SPI_MST_STATUS
 *
 * @param ri Replicator: x_SPI_MST_CS_CNT (??), 0-3
 */
#define VTSS_ICPU_CFG_SPI_MST_SPI_MST_STATUS(ri)  VTSS_IOREG(VTSS_TO_CFG,0x10 + (ri))

/** 
 * \brief
 * Upsupported operation has been performed on the SPI master from AHB
 * slave.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_SPI_MST_SPI_MST_STATUS . UNSUP_ERR
 */
#define  VTSS_F_ICPU_CFG_SPI_MST_SPI_MST_STATUS_UNSUP_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_SPI_MST_SPI_MST_STATUS_UNSUP_ERR  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_SPI_MST_SPI_MST_STATUS_UNSUP_ERR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


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
#define VTSS_ICPU_CFG_SPI_MST_SW_MODE        VTSS_IOREG(VTSS_TO_CFG,0x14)

/** 
 * \brief
 * Set to enable software pin control mode (Bit banging), when set software
 * has direct control of the SPI interface.
 * This mode is used for writing into flash.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_SPI_MST_SW_MODE . SW_PIN_CTRL_MODE
 */
#define  VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_PIN_CTRL_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_PIN_CTRL_MODE  VTSS_BIT(13)
#define  VTSS_X_ICPU_CFG_SPI_MST_SW_MODE_SW_PIN_CTRL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Value to drive on SI_Clk output. This field is only used if
 * SW_MODE.SW_PIN_CTRL_MODE is set.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_SPI_MST_SW_MODE . SW_SPI_SCK
 */
#define  VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SCK(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SCK  VTSS_BIT(12)
#define  VTSS_X_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SCK(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Set to enable drive of SI_Clk output. This field is only used if
 * SW_MODE.SW_PIN_CTRL_MODE is set.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_SPI_MST_SW_MODE . SW_SPI_SCK_OE
 */
#define  VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SCK_OE(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SCK_OE  VTSS_BIT(11)
#define  VTSS_X_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SCK_OE(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Value to drive on SI_DO output. This field is only used if
 * SW_MODE.SW_PIN_CTRL_MODE is set.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_SPI_MST_SW_MODE . SW_SPI_SDO
 */
#define  VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDO(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDO  VTSS_BIT(10)
#define  VTSS_X_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDO(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Set to enable drive of SI_DO output. This field is only used if
 * SW_MODE.SW_PIN_CTRL_MODE is set.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_SPI_MST_SW_MODE . SW_SPI_SDO_OE
 */
#define  VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDO_OE(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDO_OE  VTSS_BIT(9)
#define  VTSS_X_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDO_OE(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

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
 * This field has not effect, chip selects are always driven.
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
#define  VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDI(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDI  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDI(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ICPU_CFG:MPU8051
 *
 * Configuration/status for the 8051
 */


/** 
 * \brief 8051 configuration
 *
 * \details
 * Register: \a ICPU_CFG:MPU8051:MPU8051_CFG
 */
#define VTSS_ICPU_CFG_MPU8051_MPU8051_CFG    VTSS_IOREG(VTSS_TO_CFG,0x15)

/** 
 * \brief
 * This field controls if the VCore UART or the 8051's internal UART is
 * conencted to the chip IOs. The default, when the UART is always used.
 * By clearing this field the 8051's internal UART will be connected to the
 * chip IOs, this field only applies to an 8051 enabled system - clearing
 * this field has no effect in a MIPS based VCore System.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MPU8051_CFG . UART_SYS_ENA
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_CFG_UART_SYS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_MPU8051_MPU8051_CFG_UART_SYS_ENA  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_MPU8051_MPU8051_CFG_UART_SYS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief 8051 status
 *
 * \details
 * These read only fields can be used for debugging 8051 programs.
 *
 * Register: \a ICPU_CFG:MPU8051:MPU8051_STAT
 */
#define VTSS_ICPU_CFG_MPU8051_MPU8051_STAT   VTSS_IOREG(VTSS_TO_CFG,0x16)

/** 
 * \brief
 * This field is set if the 8051 get a shared bus error while fetching code
 * or data from offchip memory, this field can only be cleared by a reset
 * of the 8051.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MPU8051_STAT . MPU8051_SBA_ERR
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_STAT_MPU8051_SBA_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ICPU_CFG_MPU8051_MPU8051_STAT_MPU8051_SBA_ERR  VTSS_BIT(9)
#define  VTSS_X_ICPU_CFG_MPU8051_MPU8051_STAT_MPU8051_SBA_ERR(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Set when the 8051 has stopped itself by setting bit 2 in the PCON SFR
 * register.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MPU8051_STAT . MPU8051_STOP
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_STAT_MPU8051_STOP(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ICPU_CFG_MPU8051_MPU8051_STAT_MPU8051_STOP  VTSS_BIT(8)
#define  VTSS_X_ICPU_CFG_MPU8051_MPU8051_STAT_MPU8051_STOP(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

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
 * \brief 8051 memory mapping mechanism
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
#define VTSS_ICPU_CFG_MPU8051_MPU8051_MMAP   VTSS_IOREG(VTSS_TO_CFG,0x17)

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
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_MMAP_MSADDR_CODE_HIGH(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ICPU_CFG_MPU8051_MPU8051_MMAP_MSADDR_CODE_HIGH  VTSS_BIT(7)
#define  VTSS_X_ICPU_CFG_MPU8051_MPU8051_MMAP_MSADDR_CODE_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

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
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_MMAP_MSADDR_CODE_LOW(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ICPU_CFG_MPU8051_MPU8051_MMAP_MSADDR_CODE_LOW  VTSS_BIT(6)
#define  VTSS_X_ICPU_CFG_MPU8051_MPU8051_MMAP_MSADDR_CODE_LOW(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

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
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_MMAP_MSADDR_DATA_HIGH(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ICPU_CFG_MPU8051_MPU8051_MMAP_MSADDR_DATA_HIGH  VTSS_BIT(5)
#define  VTSS_X_ICPU_CFG_MPU8051_MPU8051_MMAP_MSADDR_DATA_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

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
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_MMAP_MSADDR_DATA_LOW(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ICPU_CFG_MPU8051_MPU8051_MMAP_MSADDR_DATA_LOW  VTSS_BIT(4)
#define  VTSS_X_ICPU_CFG_MPU8051_MPU8051_MMAP_MSADDR_DATA_LOW(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set to map 8051 code-accesses in the high 32KByte memory range to
 * on-chip memory instead of FLASH.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MPU8051_MMAP . MAP_CODE_HIGH
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_MMAP_MAP_CODE_HIGH(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ICPU_CFG_MPU8051_MPU8051_MMAP_MAP_CODE_HIGH  VTSS_BIT(3)
#define  VTSS_X_ICPU_CFG_MPU8051_MPU8051_MMAP_MAP_CODE_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set to map 8051 code-accesses in the low 32KByte memory range to on-chip
 * memory instead of FLASH.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MPU8051_MMAP . MAP_CODE_LOW
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_MMAP_MAP_CODE_LOW(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ICPU_CFG_MPU8051_MPU8051_MMAP_MAP_CODE_LOW  VTSS_BIT(2)
#define  VTSS_X_ICPU_CFG_MPU8051_MPU8051_MMAP_MAP_CODE_LOW(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set to map 8051 data-accesses in the high 32KByte memory range to
 * on-chip memory instead of FLASH.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MPU8051_MMAP . MAP_DATA_HIGH
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_MMAP_MAP_DATA_HIGH(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_MPU8051_MPU8051_MMAP_MAP_DATA_HIGH  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_MPU8051_MPU8051_MMAP_MAP_DATA_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set to map 8051 data-accesses in the low 32KByte memory range to on-chip
 * memory instead of FLASH.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MPU8051_MMAP . MAP_DATA_LOW
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_MMAP_MAP_DATA_LOW(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_MPU8051_MPU8051_MMAP_MAP_DATA_LOW  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_MPU8051_MPU8051_MMAP_MAP_DATA_LOW(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief 8051 memory load/examine configuration/status
 *
 * \details
 * Register: \a ICPU_CFG:MPU8051:MEMACC_CTRL
 */
#define VTSS_ICPU_CFG_MPU8051_MEMACC_CTRL    VTSS_IOREG(VTSS_TO_CFG,0x18)

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
#define  VTSS_F_ICPU_CFG_MPU8051_MEMACC_CTRL_MEMACC_EXAMINE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_MPU8051_MEMACC_CTRL_MEMACC_EXAMINE  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_MPU8051_MEMACC_CTRL_MEMACC_EXAMINE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

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
#define  VTSS_F_ICPU_CFG_MPU8051_MEMACC_CTRL_MEMACC_DO(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_MPU8051_MEMACC_CTRL_MEMACC_DO  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_MPU8051_MEMACC_CTRL_MEMACC_DO(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief 8051 memory offset configuration
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
#define VTSS_ICPU_CFG_MPU8051_MEMACC         VTSS_IOREG(VTSS_TO_CFG,0x19)

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
 * \brief SBA memory offset configuration
 *
 * \details
 * There is no stop address in the SBA address space. The number of 32-bit
 * words which is moved per access is determined by the MEMACC.MEMACC_START
 * and MEMACC.MEMACC_STOP.
 *
 * Register: \a ICPU_CFG:MPU8051:MEMACC_SBA
 */
#define VTSS_ICPU_CFG_MPU8051_MEMACC_SBA     VTSS_IOREG(VTSS_TO_CFG,0x1a)

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
 * \brief 8051 ROM configuration
 *
 * \details
 * Register: \a ICPU_CFG:MPU8051:MPU8051_IROM
 */
#define VTSS_ICPU_CFG_MPU8051_MPU8051_IROM   VTSS_IOREG(VTSS_TO_CFG,0x1b)

/** 
 * \brief
 * This Field specifies the offset into AHB space from which the 8051 must
 * fetch its IROM code during firmware startup.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MPU8051_MPU8051_IROM . ROM_OFFSET
 */
#define  VTSS_F_ICPU_CFG_MPU8051_MPU8051_IROM_ROM_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_ICPU_CFG_MPU8051_MPU8051_IROM_ROM_OFFSET     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_ICPU_CFG_MPU8051_MPU8051_IROM_ROM_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * Register Group: \a ICPU_CFG:INTR
 *
 * Interrupt controller
 */


/** 
 * \brief Interrupt raw status
 *
 * \details
 * Register: \a ICPU_CFG:INTR:INTR_RAW
 */
#define VTSS_ICPU_CFG_INTR_INTR_RAW          VTSS_IOREG(VTSS_TO_CFG,0x1c)

/** 
 * \brief
 * Shows the current value of individual interrupt sources. All sources are
 * active high (the external interrupts has been corrected for polarity as
 * configured in ICPU_CFG::EXT_SRC_INTR_POL).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_RAW . INTR_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_RAW_INTR_RAW(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_ICPU_CFG_INTR_INTR_RAW_INTR_RAW     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_ICPU_CFG_INTR_INTR_RAW_INTR_RAW(x)  VTSS_EXTRACT_BITFIELD(x,0,27)


/** 
 * \brief Interrupt trigger mode
 *
 * \details
 * Register: \a ICPU_CFG:INTR:INTR_TRIGGER
 *
 * @param ri Register: INTR_TRIGGER (??), 0-1
 */
#define VTSS_ICPU_CFG_INTR_INTR_TRIGGER(ri)  VTSS_IOREG(VTSS_TO_CFG,0x1d + (ri))

/** 
 * \brief
 * Configure trigger mode of individual interrupt sources. The trigger mode
 * determines how the value of the ICPU_CFG::INTR_RAW register is
 * transfered to the ICPU_CFG::INTR_STICKY register. This register is
 * replicated, the first replication controls bit 0 in the encoding, the
 * second replication controls bit 1 in the encoding. I.e. to configure
 * falling-edge-triggered interrupt for interrupt source 5; set
 * ICPU_CFG::INTR_TRIGGER[0][5]='0' and ICPU_CFG::INTR_TRIGGER[1][5]='1'.
 * For level-triggered interrupts ICPU_CFG::INTR_STICKY is set for as long
 * as the corresponding bit in ICPU_CFG::INTR_RAW is high - i.e. is not
 * possible to clear a bit in ICPU_CFG::INTR_STICKY until the corresponding
 * ICPU_CFG::INTR_RAW is zero.
 * For edge-triggeded interrupts ICPU_CFG::INTR_STICKY is set when the
 * corresponding bit in ICPU_CFG::INTR_RAW changes value.
 * For falling-edge-triggeded interrupts ICPU_CFG::INTR_STICKY is set when
 * the corresponding bit in ICPU_CFG::INTR_RAW changes from '1' to '0'.
 * For rising-edge-triggeded interrupts ICPU_CFG::INTR_STICKY is set when
 * the corresponding bit in ICPU_CFG::INTR_RAW changes from '0' to '1'.
 *
 * \details 
 * 0: Interrupt is level-activated
 * 1: Interrupt is edge-triggered
 * 2: Interrupt is falling-edge-triggered
 * 3: Interrupt is rising-edge-triggered
 *
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_TRIGGER . INTR_TRIGGER
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_TRIGGER_INTR_TRIGGER(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_ICPU_CFG_INTR_INTR_TRIGGER_INTR_TRIGGER     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_ICPU_CFG_INTR_INTR_TRIGGER_INTR_TRIGGER(x)  VTSS_EXTRACT_BITFIELD(x,0,27)


/** 
 * \brief Interrupt force sticky event
 *
 * \details
 * Register: \a ICPU_CFG:INTR:INTR_FORCE
 */
#define VTSS_ICPU_CFG_INTR_INTR_FORCE        VTSS_IOREG(VTSS_TO_CFG,0x1f)

/** 
 * \brief
 * Set to force corresponding ICPU_CFG::INTR_STICKY bits.
 * This field may be useful during development of software interrupt
 * handler functions.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_FORCE . INTR_FORCE
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_FORCE_INTR_FORCE(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_ICPU_CFG_INTR_INTR_FORCE_INTR_FORCE     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_ICPU_CFG_INTR_INTR_FORCE_INTR_FORCE(x)  VTSS_EXTRACT_BITFIELD(x,0,27)


/** 
 * \brief Interrupt sticky status
 *
 * \details
 * Register: \a ICPU_CFG:INTR:INTR_STICKY
 */
#define VTSS_ICPU_CFG_INTR_INTR_STICKY       VTSS_IOREG(VTSS_TO_CFG,0x20)

/** 
 * \brief
 * This register is set based on source interrupt events or by debug-force.
 * See ICPU_CFG::INTR_TRIGGER and ICPU_CFG::INTR_FORCE for more
 * information. Bits in this register remains set until cleared by
 * software.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_STICKY . INTR_STICKY
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_STICKY_INTR_STICKY(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_ICPU_CFG_INTR_INTR_STICKY_INTR_STICKY     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_ICPU_CFG_INTR_INTR_STICKY_INTR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,27)


/** 
 * \brief Interrupt bypass enable
 *
 * \details
 * Register: \a ICPU_CFG:INTR:INTR_BYPASS
 */
#define VTSS_ICPU_CFG_INTR_INTR_BYPASS       VTSS_IOREG(VTSS_TO_CFG,0x21)

/** 
 * \brief
 * This register allows bypass of ICPU_CFG::INTR_STICKY for individual
 * interrupt sources. When an interrupt source is in bypass mode then
 * ICPU_CFG::INTR_RAW is used instead of ICPU_CFG::INTR_STICKY.
 * Note: Enabling bypass does not make sense for all interrupt sources. It
 * should only be used when the corresponding interrupt is sticky at the
 * soruce. For example manual extraction data available interrupts can be
 * configured to bypass, because the interrupt will remain asserted until
 * the available data has been extracted.
 * Note: The device interrupt is bypassed per default, "stickyness" is
 * already implemented by ICPU_CFG::DEV_INTR_STICKY.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_BYPASS . INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_BYPASS_INTR_BYPASS(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_ICPU_CFG_INTR_INTR_BYPASS_INTR_BYPASS     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_ICPU_CFG_INTR_INTR_BYPASS_INTR_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,0,27)


/** 
 * \brief Interrupt enable
 *
 * \details
 * Register: \a ICPU_CFG:INTR:INTR_ENA
 */
#define VTSS_ICPU_CFG_INTR_INTR_ENA          VTSS_IOREG(VTSS_TO_CFG,0x22)

/** 
 * \brief
 * Set to enable propagation of individual interrupt sources to
 * destinations.
 * Atomic access to this register (needed in a multithreaded system) can be
 * implemented by the ICPU_CFG::INTR_ENA_CLR and ICPU_CFG::INTR_ENA_SET
 * registers.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA . INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_ICPU_CFG_INTR_INTR_ENA_INTR_ENA     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_ICPU_CFG_INTR_INTR_ENA_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,27)


/** 
 * \brief Atomic clear of interrupt enable
 *
 * \details
 * Register: \a ICPU_CFG:INTR:INTR_ENA_CLR
 */
#define VTSS_ICPU_CFG_INTR_INTR_ENA_CLR      VTSS_IOREG(VTSS_TO_CFG,0x23)

/** 
 * \brief
 * Set bit(s) in this register to clear the corresponding bits in
 * ICPU_CFG::INTR_ENA. This register can be used for atomic access to
 * ICPU_CFG::INTR_ENA register.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_CLR . INTR_ENA_CLR
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_CLR_INTR_ENA_CLR(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_ICPU_CFG_INTR_INTR_ENA_CLR_INTR_ENA_CLR     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_ICPU_CFG_INTR_INTR_ENA_CLR_INTR_ENA_CLR(x)  VTSS_EXTRACT_BITFIELD(x,0,27)


/** 
 * \brief Atomic set of interrupt
 *
 * \details
 * Register: \a ICPU_CFG:INTR:INTR_ENA_SET
 */
#define VTSS_ICPU_CFG_INTR_INTR_ENA_SET      VTSS_IOREG(VTSS_TO_CFG,0x24)

/** 
 * \brief
 * Set bit(s) in this register to set the corresponding bits in
 * ICPU_CFG::INTR_ENA. This register can be used for atomic access to
 * ICPU_CFG::INTR_ENA register.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_ENA_SET . INTR_ENA_SET
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_ENA_SET_INTR_ENA_SET(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_ICPU_CFG_INTR_INTR_ENA_SET_INTR_ENA_SET     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_ICPU_CFG_INTR_INTR_ENA_SET_INTR_ENA_SET(x)  VTSS_EXTRACT_BITFIELD(x,0,27)


/** 
 * \brief Currently active interrupt sources
 *
 * \details
 * Register: \a ICPU_CFG:INTR:INTR_IDENT
 */
#define VTSS_ICPU_CFG_INTR_INTR_IDENT        VTSS_IOREG(VTSS_TO_CFG,0x25)

/** 
 * \brief
 * Shows the currently active interrupt sources. For interrupt sources that
 * are not bypassed this register is a result of AND'ing
 * ICPU_CFG::INTR_STICKY with ICPU_CFG::INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_INTR_IDENT . INTR_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_INTR_IDENT_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_ICPU_CFG_INTR_INTR_IDENT_INTR_IDENT     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_ICPU_CFG_INTR_INTR_IDENT_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,0,27)


/** 
 * \brief Mapping of source to destination interrupts
 *
 * \details
 * Replicated per destination interrupt.
 *
 * Register: \a ICPU_CFG:INTR:DST_INTR_MAP
 *
 * @param ri Replicator: x_INTR_DST_CNT (??), 0-3
 */
#define VTSS_ICPU_CFG_INTR_DST_INTR_MAP(ri)  VTSS_IOREG(VTSS_TO_CFG,0x26 + (ri))

/** 
 * \brief
 * Set to enable mapping of individual interrupt sources to interrupt
 * destinations. This register is replicated once for each destination
 * interrupt. 
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_DST_INTR_MAP . DST_INTR_MAP
 */
#define  VTSS_F_ICPU_CFG_INTR_DST_INTR_MAP_DST_INTR_MAP(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_ICPU_CFG_INTR_DST_INTR_MAP_DST_INTR_MAP     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_ICPU_CFG_INTR_DST_INTR_MAP_DST_INTR_MAP(x)  VTSS_EXTRACT_BITFIELD(x,0,27)


/** 
 * \brief Currently active interrupt sources per destination
 *
 * \details
 * Replicated per destination interrupt.
 *
 * Register: \a ICPU_CFG:INTR:DST_INTR_IDENT
 *
 * @param ri Replicator: x_INTR_DST_CNT (??), 0-3
 */
#define VTSS_ICPU_CFG_INTR_DST_INTR_IDENT(ri)  VTSS_IOREG(VTSS_TO_CFG,0x2a + (ri))

/** 
 * \brief
 * Shows the currently active interrupt sources per destination interrupt.
 * The contents of this register is equal to ICPU_CFG::INTR_IDENT AND'ed
 * with the corresponding ICPU_CFG::DST_INTR_MAP.
 * If any bit is set in this register the corresponding destination
 * interrupt is asserted.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_DST_INTR_IDENT . DST_INTR_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_DST_INTR_IDENT_DST_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_ICPU_CFG_INTR_DST_INTR_IDENT_DST_INTR_IDENT     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_ICPU_CFG_INTR_DST_INTR_IDENT_DST_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,0,27)


/** 
 * \brief External source interrupt polarity
 *
 * \details
 * Register: \a ICPU_CFG:INTR:EXT_SRC_INTR_POL
 */
#define VTSS_ICPU_CFG_INTR_EXT_SRC_INTR_POL  VTSS_IOREG(VTSS_TO_CFG,0x2e)

/** 
 * \brief
 * Set individual bits in this register to configure polarity of the
 * corresponding external source interrupt.
 *
 * \details 
 * 0: External interrupt input is active low
 * 1: External interrupt input is active high
 *
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_SRC_INTR_POL . EXT_SRC_INTR_POL
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_SRC_INTR_POL_EXT_SRC_INTR_POL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_EXT_SRC_INTR_POL_EXT_SRC_INTR_POL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_EXT_SRC_INTR_POL_EXT_SRC_INTR_POL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief External destination interrupt polarity
 *
 * \details
 * Register: \a ICPU_CFG:INTR:EXT_DST_INTR_POL
 */
#define VTSS_ICPU_CFG_INTR_EXT_DST_INTR_POL  VTSS_IOREG(VTSS_TO_CFG,0x2f)

/** 
 * \brief
 * Set individual bits in this register to configure polarity of the
 * corresponding external destination interrupt.
 *
 * \details 
 * 0: External interrupt output is active low
 * 1: External interrupt output is active high
 *
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_DST_INTR_POL . EXT_DST_INTR_POL
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_DST_INTR_POL_EXT_DST_INTR_POL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_EXT_DST_INTR_POL_EXT_DST_INTR_POL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_EXT_DST_INTR_POL_EXT_DST_INTR_POL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief External interrupt destination output drive mode
 *
 * \details
 * Register: \a ICPU_CFG:INTR:EXT_DST_INTR_DRV
 */
#define VTSS_ICPU_CFG_INTR_EXT_DST_INTR_DRV  VTSS_IOREG(VTSS_TO_CFG,0x30)

/** 
 * \brief
 * This register configures drive mode of the corresponding external
 * destination interrupt.
 *
 * \details 
 * 0: Only drive external interrupt output when asserted (tristate when
 * inactive)
 * 1: External interrupt output is always driven
 *
 * Field: ::VTSS_ICPU_CFG_INTR_EXT_DST_INTR_DRV . EXT_DST_INTR_DRV
 */
#define  VTSS_F_ICPU_CFG_INTR_EXT_DST_INTR_DRV_EXT_DST_INTR_DRV(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_INTR_EXT_DST_INTR_DRV_EXT_DST_INTR_DRV     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_INTR_EXT_DST_INTR_DRV_EXT_DST_INTR_DRV(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Device interrupt polarity
 *
 * \details
 * Register: \a ICPU_CFG:INTR:DEV_INTR_POL
 */
#define VTSS_ICPU_CFG_INTR_DEV_INTR_POL      VTSS_IOREG(VTSS_TO_CFG,0x31)

/** 
 * \brief
 * Set individual bits in this register to configure polarity of the
 * corresponding device interrupt.
 *
 * \details 
 * 0: Device interrupt is active low
 * 1: Device interrupt is active high
 *
 * Field: ::VTSS_ICPU_CFG_INTR_DEV_INTR_POL . DEV_INTR_POL
 */
#define  VTSS_F_ICPU_CFG_INTR_DEV_INTR_POL_DEV_INTR_POL(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_ICPU_CFG_INTR_DEV_INTR_POL_DEV_INTR_POL     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_ICPU_CFG_INTR_DEV_INTR_POL_DEV_INTR_POL(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Device interrupt raw status
 *
 * \details
 * Register: \a ICPU_CFG:INTR:DEV_INTR_RAW
 */
#define VTSS_ICPU_CFG_INTR_DEV_INTR_RAW      VTSS_IOREG(VTSS_TO_CFG,0x32)

/** 
 * \brief
 * Shows the current value of individual device interrupt sources. All
 * sources are active high (sources have been corrected for polarity as
 * configured in ICPU_CFG::DEV_INTR_POL).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_DEV_INTR_RAW . DEV_INTR_RAW
 */
#define  VTSS_F_ICPU_CFG_INTR_DEV_INTR_RAW_DEV_INTR_RAW(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_ICPU_CFG_INTR_DEV_INTR_RAW_DEV_INTR_RAW     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_ICPU_CFG_INTR_DEV_INTR_RAW_DEV_INTR_RAW(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Device interrupt trigger mode
 *
 * \details
 * Register: \a ICPU_CFG:INTR:DEV_INTR_TRIGGER
 *
 * @param ri Register: DEV_INTR_TRIGGER (??), 0-1
 */
#define VTSS_ICPU_CFG_INTR_DEV_INTR_TRIGGER(ri)  VTSS_IOREG(VTSS_TO_CFG,0x33 + (ri))

/** 
 * \brief
 * Configure trigger mode of individual device interrupt sources. The
 * trigger mode determines how the value of the ICPU_CFG::DEV_INTR_RAW
 * register is transfered to the ICPU_CFG::DEV_INTR_STICKY register. This
 * register is replicated, the first replication controls bit 0 in the
 * encoding, the second replication controls bit 1 in the encoding. I.e. to
 * configure edge-triggered interrupt for device 3; set
 * ICPU_CFG::DEV_INTR_TRIGGER[0][3]='1' and
 * ICPU_CFG::DEV_INTR_TRIGGER[1][3]='0'.
 * For level-triggered interrupts ICPU_CFG::DEV_INTR_STICKY is set for as
 * long as the corresponding bit in ICPU_CFG::DEV_INTR_RAW is high - i.e.
 * is not possible to clear a bit in ICPU_CFG::DEV_INTR_STICKY until the
 * corresponding ICPU_CFG::DEV_INTR_RAW is zero.
 * For edge-triggeded interrupts ICPU_CFG::DEV_INTR_STICKY is set when the
 * corresponding bit in ICPU_CFG::DEV_INTR_RAW changes value.
 * For falling-edge-triggeded interrupts ICPU_CFG::DEV_INTR_STICKY is set
 * when the corresponding bit in ICPU_CFG::DEV_INTR_RAW changes from '1' to
 * '0'.
 * For rising-edge-triggeded interrupts ICPU_CFG::DEV_INTR_STICKY is set
 * when the corresponding bit in ICPU_CFG::DEV_INTR_RAW changes from '0' to
 * '1'.
 *
 * \details 
 * 0: Interrupt is level-activated
 * 1: Interrupt is edge-triggered
 * 2: Interrupt is falling-edge-triggered
 * 3: Interrupt is rising-edge-triggered
 *
 * Field: ::VTSS_ICPU_CFG_INTR_DEV_INTR_TRIGGER . DEV_INTR_TRIGGER
 */
#define  VTSS_F_ICPU_CFG_INTR_DEV_INTR_TRIGGER_DEV_INTR_TRIGGER(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_ICPU_CFG_INTR_DEV_INTR_TRIGGER_DEV_INTR_TRIGGER     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_ICPU_CFG_INTR_DEV_INTR_TRIGGER_DEV_INTR_TRIGGER(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Device interrupt sticky status
 *
 * \details
 * Register: \a ICPU_CFG:INTR:DEV_INTR_STICKY
 */
#define VTSS_ICPU_CFG_INTR_DEV_INTR_STICKY   VTSS_IOREG(VTSS_TO_CFG,0x35)

/** 
 * \brief
 * This register is set based on device interrupt sourec events. See
 * ICPU_CFG::DEV_INTR_TRIGGER for more information. Bits in this register
 * remains set until cleared by software.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_DEV_INTR_STICKY . DEV_INTR_STICKY
 */
#define  VTSS_F_ICPU_CFG_INTR_DEV_INTR_STICKY_DEV_INTR_STICKY(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_ICPU_CFG_INTR_DEV_INTR_STICKY_DEV_INTR_STICKY     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_ICPU_CFG_INTR_DEV_INTR_STICKY_DEV_INTR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Device interrupt bypass enable
 *
 * \details
 * Register: \a ICPU_CFG:INTR:DEV_INTR_BYPASS
 */
#define VTSS_ICPU_CFG_INTR_DEV_INTR_BYPASS   VTSS_IOREG(VTSS_TO_CFG,0x36)

/** 
 * \brief
 * This register allows bypass of ICPU_CFG::DEV_INTR_STICKY for individual
 * device interrupt sources. When a device interrupt source is in bypass
 * mode then ICPU_CFG::DEV_INTR_RAW is used instead of
 * ICPU_CFG::DEV_INTR_STICKY.
 * See note on bypass in ICPU_CFG::INTR_BYPASS.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_DEV_INTR_BYPASS . DEV_INTR_BYPASS
 */
#define  VTSS_F_ICPU_CFG_INTR_DEV_INTR_BYPASS_DEV_INTR_BYPASS(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_ICPU_CFG_INTR_DEV_INTR_BYPASS_DEV_INTR_BYPASS     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_ICPU_CFG_INTR_DEV_INTR_BYPASS_DEV_INTR_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Device interrupt enable
 *
 * \details
 * Register: \a ICPU_CFG:INTR:DEV_INTR_ENA
 */
#define VTSS_ICPU_CFG_INTR_DEV_INTR_ENA      VTSS_IOREG(VTSS_TO_CFG,0x37)

/** 
 * \brief
 * Set to enable propagation of individual device interrupt sources to the
 * main interrupt controller.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_DEV_INTR_ENA . DEV_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_INTR_DEV_INTR_ENA_DEV_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_ICPU_CFG_INTR_DEV_INTR_ENA_DEV_INTR_ENA     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_ICPU_CFG_INTR_DEV_INTR_ENA_DEV_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Currently active device interrupts
 *
 * \details
 * Register: \a ICPU_CFG:INTR:DEV_INTR_IDENT
 */
#define VTSS_ICPU_CFG_INTR_DEV_INTR_IDENT    VTSS_IOREG(VTSS_TO_CFG,0x38)

/** 
 * \brief
 * Shows the currently active interrupt sources. For interrupt sources that
 * are not bypassed this register is a result of AND'ing
 * ICPU_CFG::DEV_INTR_STICKY with ICPU_CFG::DEV_INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_INTR_DEV_INTR_IDENT . DEV_INTR_IDENT
 */
#define  VTSS_F_ICPU_CFG_INTR_DEV_INTR_IDENT_DEV_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_ICPU_CFG_INTR_DEV_INTR_IDENT_DEV_INTR_IDENT     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_ICPU_CFG_INTR_DEV_INTR_IDENT_DEV_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,0,13)

/**
 * Register Group: \a ICPU_CFG:TIMERS
 *
 * Timers
 */


/** 
 * \brief Watchdog timer
 *
 * \details
 * Register: \a ICPU_CFG:TIMERS:WDT
 */
#define VTSS_ICPU_CFG_TIMERS_WDT             VTSS_IOREG(VTSS_TO_CFG,0x39)

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
#define  VTSS_F_ICPU_CFG_TIMERS_WDT_WDT_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ICPU_CFG_TIMERS_WDT_WDT_STATUS  VTSS_BIT(9)
#define  VTSS_X_ICPU_CFG_TIMERS_WDT_WDT_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Use this field to enable or disable the watchdog timer. When the WDT is
 * enabled, it causes a reset after 2 seconds if it is not periodically
 * reset. This field is only read by the WDT after a sucessful lock
 * sequence (see ICPU_CFG::WDT.WDT_LOCK).
 *
 * \details 
 * 0: WDT is disabled
 * 1: WDT is enabled
 *
 * Field: ::VTSS_ICPU_CFG_TIMERS_WDT . WDT_ENABLE
 */
#define  VTSS_F_ICPU_CFG_TIMERS_WDT_WDT_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ICPU_CFG_TIMERS_WDT_WDT_ENABLE  VTSS_BIT(8)
#define  VTSS_X_ICPU_CFG_TIMERS_WDT_WDT_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Use this field to configure and reset the WDT. When writing 0xBE to this
 * field immediately followed by writing 0xEF, the WDT resets and
 * configurations are read from this register (as provided when the 0xEF is
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
 * \brief Timer tick divider
 *
 * \details
 * Register: \a ICPU_CFG:TIMERS:TIMER_TICK_DIV
 */
#define VTSS_ICPU_CFG_TIMERS_TIMER_TICK_DIV  VTSS_IOREG(VTSS_TO_CFG,0x3a)

/** 
 * \brief
 * The timer tick generator runs from the VCore System frequency. By
 * default, the divider value generates a timer tick every 100 us (10KHz).
 * The timer tick is used for all of the timers (except the WDT). This
 * field must not be set to generate a timer tick of less than 0.1 us
 * (higher than 10MHz). If this field is changed, it may take up to 2ms
 * before the timers are running stable at the new frequency.
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
#define VTSS_ICPU_CFG_TIMERS_TIMER_VALUE(ri)  VTSS_IOREG(VTSS_TO_CFG,0x3b + (ri))

/** 
 * \brief
 * The current value of the timer. When enabled via TIMER_CTRL.TIMER_ENA
 * the timer decrements at every timer tick (see TIMER_TICK_DIV for more
 * info on timer tick frequency). When the timer has reached 0, and a
 * timer-tick is received, then an interrupt is generated. For example; If
 * a periodic interrupt is needed every 1ms, and the timer tick is
 * generated every 100us then the TIMER_VALUE (and TIMER_RELOAD_VALUE) must
 * be configured to 9.
 * By default the timer will reload from the TIMER_RELOAD_VALUE when
 * interrupt is generated, and then continue decrementing from the reloaded
 * value. It is possible to make the timer stop after generating interrupt
 * by setting TIMER_CTRL.ONE_SHOT_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_TIMERS_TIMER_VALUE . TIMER_VAL
 */
#define  VTSS_F_ICPU_CFG_TIMERS_TIMER_VALUE_TIMER_VAL(x)  (x)
#define  VTSS_M_ICPU_CFG_TIMERS_TIMER_VALUE_TIMER_VAL     0xffffffff
#define  VTSS_X_ICPU_CFG_TIMERS_TIMER_VALUE_TIMER_VAL(x)  (x)


/** 
 * \brief Timer reload value
 *
 * \details
 * Register: \a ICPU_CFG:TIMERS:TIMER_RELOAD_VALUE
 *
 * @param ri Replicator: x_TIMER_CNT (??), 0-2
 */
#define VTSS_ICPU_CFG_TIMERS_TIMER_RELOAD_VALUE(ri)  VTSS_IOREG(VTSS_TO_CFG,0x3e + (ri))

/** 
 * \brief
 * The contents of this field are loaded into the corresponding timer
 * (TIMER_VALUE) when it wraps (decrements a zero).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_TIMERS_TIMER_RELOAD_VALUE . RELOAD_VAL
 */
#define  VTSS_F_ICPU_CFG_TIMERS_TIMER_RELOAD_VALUE_RELOAD_VAL(x)  (x)
#define  VTSS_M_ICPU_CFG_TIMERS_TIMER_RELOAD_VALUE_RELOAD_VAL     0xffffffff
#define  VTSS_X_ICPU_CFG_TIMERS_TIMER_RELOAD_VALUE_RELOAD_VAL(x)  (x)


/** 
 * \brief Timer control
 *
 * \details
 * Register: \a ICPU_CFG:TIMERS:TIMER_CTRL
 *
 * @param ri Replicator: x_TIMER_CNT (??), 0-2
 */
#define VTSS_ICPU_CFG_TIMERS_TIMER_CTRL(ri)  VTSS_IOREG(VTSS_TO_CFG,0x41 + (ri))

/** 
 * \brief
 * When set the timer will count continously (increment in each clock
 * cycle) with out regard to the timer-tick generator. This feature is used
 * for timing validation of the VCore system.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_TIMERS_TIMER_CTRL . MAX_FREQ_ENA
 */
#define  VTSS_F_ICPU_CFG_TIMERS_TIMER_CTRL_MAX_FREQ_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ICPU_CFG_TIMERS_TIMER_CTRL_MAX_FREQ_ENA  VTSS_BIT(3)
#define  VTSS_X_ICPU_CFG_TIMERS_TIMER_CTRL_MAX_FREQ_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * When set the timer will automatically disable itself after it has
 * generated interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_TIMERS_TIMER_CTRL . ONE_SHOT_ENA
 */
#define  VTSS_F_ICPU_CFG_TIMERS_TIMER_CTRL_ONE_SHOT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ICPU_CFG_TIMERS_TIMER_CTRL_ONE_SHOT_ENA  VTSS_BIT(2)
#define  VTSS_X_ICPU_CFG_TIMERS_TIMER_CTRL_ONE_SHOT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * When enabled, the correponding timer decrements at each timer-tick. If
 * TIMER_CTRL.ONE_SHOT_ENA is set this field is cleared when the timer
 * reach 0 and interrupt is generated.
 *
 * \details 
 * 0: Timer is disabled
 * 1: Timer is enabled
 *
 * Field: ::VTSS_ICPU_CFG_TIMERS_TIMER_CTRL . TIMER_ENA
 */
#define  VTSS_F_ICPU_CFG_TIMERS_TIMER_CTRL_TIMER_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_TIMERS_TIMER_CTRL_TIMER_ENA  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_TIMERS_TIMER_CTRL_TIMER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set this field to force the reload of the timer, this will set the
 * TIMER_VALUE to TIMER_RELOAD_VALUE for the corresponding timer. This
 * field can be set at the same time as enabeling the counter, in that case
 * the counter will be reloaded and then enabled for counting.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_TIMERS_TIMER_CTRL . FORCE_RELOAD
 */
#define  VTSS_F_ICPU_CFG_TIMERS_TIMER_CTRL_FORCE_RELOAD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_TIMERS_TIMER_CTRL_FORCE_RELOAD  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_TIMERS_TIMER_CTRL_FORCE_RELOAD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ICPU_CFG:MEMCTRL
 *
 * DDR2/3 memory controller
 */


/** 
 * \brief DDR2/3 control
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_CTRL
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL   VTSS_IOREG(VTSS_TO_CFG,0x44)

/** 
 * \brief
 * Set this field to force the memory module into low power self refresh
 * mode. The ICPU_CFG::MEMCTRL_STAT.PWR_DOWN_ACK is set when the controller
 * has executed the command. Clear this field to bring the controller back
 * to normal operation.
 * Note: Before using power-down the ICPU_CFG::MEMCTRL_TIMING2.INIT_DLY
 * must be reconfigured, see field description for more information.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL . PWR_DOWN
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL_PWR_DOWN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL_PWR_DOWN  VTSS_BIT(3)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL_PWR_DOWN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set this field to do memory register write command. The register to
 * write is defined by ICPU_CFG::MEMCTRL_MR0_VAL[15:14], the data to write
 * is defined by ICPU_CFG::MEMCTRL_MR0_VAL[15:0].
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL . MDSET
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL_MDSET(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL_MDSET  VTSS_BIT(2)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL_MDSET(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set this field to temporarily give software unhindered access to memory;
 * two things changes in the controller:
 * a) Refreshes are postponed until
 * ICPU_CFG::MEMCTRL_REF_PERIOD.MAX_PEND_REF is exceeded.
 * b) Only a single refresh will be issued when exceeding
 * ICPU_CFG::MEMCTRL_REF_PERIOD.MAX_PEND_REF.
 * When this field is NOT set (the normal case) the memory controller try
 * to do refreshes during controller idle periods, also once refresh has
 * started - all pending refreshes will be performed.
 * Note: Interrupt routines and other high-priority tasks can use this
 * field to ensure uninterrupted access to the memory, such routines must
 * clear this field when memory access is no longer critical.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL . STALL_REF_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL_STALL_REF_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL_STALL_REF_ENA  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL_STALL_REF_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set this field to force the memory controller to initialize the SDRAM.
 * This field is automatically cleared after the controller has started
 * initialization of the SDRAM. Wait for ICPU_CFG::MEMCTRL_STAT.INIT_DONE
 * before performing read/write operations on the controller.
 * Note: The ICPU_CFG::MEMCTRL_CFG, ICPU_CFG::MEMCTRL_REF_PERIOD,
 * ICPU_CFG::MEMCTRL_TIMING*, and ICPU_CFG::MEMCTRL_MR* registers must be
 * configured appropriately before setting this field.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL . INITIALIZE
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL_INITIALIZE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL_INITIALIZE  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_CTRL_INITIALIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief DDR2/3 configuration
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_CFG
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CFG    VTSS_IOREG(VTSS_TO_CFG,0x45)

/** 
 * \brief
 * Set this field to enable support for more than 512MByte SDRAM.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CFG . DDR_512MBYTE_PLUS
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_DDR_512MBYTE_PLUS(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_DDR_512MBYTE_PLUS  VTSS_BIT(16)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_DDR_512MBYTE_PLUS(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Set this field to enable propagation of ECC errors to SBA by generating
 * bus-error event when ECC error is detected. This field may not be set
 * unless ICPU_CFG::MEMCTRL_CFG.DDR_ECC_ENA is also set.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CFG . DDR_ECC_ERR_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_DDR_ECC_ERR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_DDR_ECC_ERR_ENA  VTSS_BIT(15)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_DDR_ECC_ERR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Set this field to enable propagation of ECC corrections to SBA by
 * generating bus-error event when ECC correction is detected. This field
 * may not be set unless ICPU_CFG::MEMCTRL_CFG.DDR_ECC_ENA is also set.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CFG . DDR_ECC_COR_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_DDR_ECC_COR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_DDR_ECC_COR_ENA  VTSS_BIT(14)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_DDR_ECC_COR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * This field enables ECC mode of the SDRAM controller. This field may only
 * be set when ICPU_CFG::MEMCTRL_CFG.DDR_WIDTH is configured for 16bit. In
 * ECC mode byte lane 1 is used for ECC information and byte lane 0 is used
 * for data.
 * When using ECC mode, then the amount of random-access memory availble to
 * an application is half of the physically attatched memory.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CFG . DDR_ECC_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_DDR_ECC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_DDR_ECC_ENA  VTSS_BIT(13)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_DDR_ECC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * This field configures the interface width of the SDRAM controller. If
 * 8bit is selected then byte lane 0 must be populated by external SDRAM
 * memory.
 *
 * \details 
 * 0: 8bit
 * 1: 16bit
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CFG . DDR_WIDTH
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_DDR_WIDTH(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_DDR_WIDTH  VTSS_BIT(12)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_DDR_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * This field configures the operating mode of the SDRAM controller.
 *
 * \details 
 * 0: DDR2
 * 1: DDR3
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CFG . DDR_MODE
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_DDR_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_DDR_MODE  VTSS_BIT(11)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_DDR_MODE(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * The number of data-bytes that is transmitted during one burst (of the
 * defined burst length: ICPU_CFG::MEMCTRL_CFG.BURST_LEN).
 *
 * \details 
 * 0: 8 data-bytes per burst.
 * 1: 16 data-bytes per burst.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CFG . BURST_SIZE
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_BURST_SIZE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_BURST_SIZE  VTSS_BIT(10)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_BURST_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * The burst size that is used by the SDRAM controller. The SDRAM must be
 * configured with the corresponding burst size (through the
 * ICPU_CFG::MEMCTRL_MR0_VAL register.)
 * Note: The number of data-bytes that is transmitted during one burst must
 * be encoded in the ICPU_CFG::MEMCTRL_CFG.BURST_SIZE field.
 *
 * \details 
 * 0 : BURST4
 * 1 : BURST8
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CFG . BURST_LEN
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_BURST_LEN(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_BURST_LEN  VTSS_BIT(9)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_BURST_LEN(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

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
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_BANK_CNT(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_BANK_CNT  VTSS_BIT(8)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_BANK_CNT(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Set to 1 less than the number of row address bits for the SDRAM
 * configuration in use.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CFG . MSB_ROW_ADDR
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_MSB_ROW_ADDR(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_MSB_ROW_ADDR     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_MSB_ROW_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Set to 1 less than the number of column address bits for the SDRAM
 * configuration in use. For example; for a memory that is using column
 * addresses {A11, A9-A0} this field must be set to 10.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_CFG . MSB_COL_ADDR
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_MSB_COL_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_MSB_COL_ADDR     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_CFG_MSB_COL_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief DDR2/3 status
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_STAT
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_STAT   VTSS_IOREG(VTSS_TO_CFG,0x46)

/** 
 * \brief
 * Set if the controller has masked a data-set towards the SBA (too many
 * data words received from SDRAM). This field may be set during training.
 * If this event occurs during normal operation then the DQS window may be
 * wrongly configured.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_STAT . RDATA_MASKED
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_STAT_RDATA_MASKED(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_STAT_RDATA_MASKED  VTSS_BIT(5)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_STAT_RDATA_MASKED(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Set if the controller has inserted missing data-set towards the SBA 
 * (too few data words received from SDRAM). This field may be set during
 * training. If this event occurs during normal operation then the DQS
 * window may be wrongly configured.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_STAT . RDATA_DUMMY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_STAT_RDATA_DUMMY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_STAT_RDATA_DUMMY  VTSS_BIT(4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_STAT_RDATA_DUMMY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set if the controller is enabled for ECC and an uncorrectable error has
 * been detected.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_STAT . RDATA_ECC_ERR
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_STAT_RDATA_ECC_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_STAT_RDATA_ECC_ERR  VTSS_BIT(3)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_STAT_RDATA_ECC_ERR(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set if the controller is enabled for ECC and a dataset has been
 * corrected (a correctable error has been corrected).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_STAT . RDATA_ECC_COR
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_STAT_RDATA_ECC_COR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_STAT_RDATA_ECC_COR  VTSS_BIT(2)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_STAT_RDATA_ECC_COR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Is set once the memory controller has put the SDRAM in low power self
 * refresh mode (result of setting ICPU_CFG::MEMCTRL_CTRL.PWR_DOWN).
 * When this field is set SDRAM interface signal may turned off (all
 * signals except the CKE and ODT) may be left floating.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_STAT . PWR_DOWN_ACK
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_STAT_PWR_DOWN_ACK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_STAT_PWR_DOWN_ACK  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_STAT_PWR_DOWN_ACK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * This field is set after initialization of the SDRAM is done. When this
 * field is set then read/write operations can be performed.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_STAT . INIT_DONE
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_STAT_INIT_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_STAT_INIT_DONE  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_STAT_INIT_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Refresh configuration
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_REF_PERIOD
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_REF_PERIOD  VTSS_IOREG(VTSS_TO_CFG,0x47)

/** 
 * \brief
 * Maximum number of refreshes that are allowed to be outstanding at any
 * time. If the number of outstanding refreshes exceeds this value, the
 * memory controller will stop data accesses, and issue refreshes. If no
 * outstanding refreshes is allowed then set this field to 0.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_REF_PERIOD . MAX_PEND_REF
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_REF_PERIOD_MAX_PEND_REF(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_REF_PERIOD_MAX_PEND_REF     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_REF_PERIOD_MAX_PEND_REF(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Refresh interval of the SDRAM expressed in number of clock cycles. This
 * value is calculated by dividing the average periodic refresh interval
 * (tREFI) by the clock period.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_REF_PERIOD . REF_PERIOD
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_REF_PERIOD_REF_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_REF_PERIOD_REF_PERIOD     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_REF_PERIOD_REF_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief DDR3 ZQ-calibration
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_ZQCAL
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_ZQCAL  VTSS_IOREG(VTSS_TO_CFG,0x48)

/** 
 * \brief
 * Set this field to issue long ZQ calibration command. This field is
 * cleared when calibration has been performed.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_ZQCAL . ZQCAL_LONG
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_ZQCAL_ZQCAL_LONG(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_ZQCAL_ZQCAL_LONG  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_ZQCAL_ZQCAL_LONG(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set this field to issue short ZQ calibration command. This field is
 * cleared when calibration has been performed.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_ZQCAL . ZQCAL_SHORT
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_ZQCAL_ZQCAL_SHORT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_ZQCAL_ZQCAL_SHORT  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_ZQCAL_ZQCAL_SHORT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Timing configuration
 *
 * \details
 * The Following parameters are needed for configuration of the
 * ICPU_CFG::MEMCTRL_TIMING* registers. All asynchronous delays should be
 * converted (round up) to the corresponding number of DDR controller clock
 * cycles. Note that DDR modules may specify a minimum number of clock
 * cycles for some parameters:
 * RL=CL
 * BL=2 for burst4, 4 for burst8
 * 
 * Additional for DDR2 memories:
 * WL=RL-1
 * MD=tMRD
 * ID=400ns
 * SD=tXSRD
 * OW=WL-2
 * OR=RL-3
 * RP=tRP for 4-bank modules, tRPA for 8-bank modules
 * FAW=1 for 4-bank modules, tFAW for 8-bank modules
 * 
 * Additional for DDR3 memories:
 * WL=CWL
 * MD=tMOD
 * ID=tXPR
 * SD=tDLLK
 * OW=2
 * OR=2
 * RP=tRP
 * FAW=tFAW
 *
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_TIMING0
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0  VTSS_IOREG(VTSS_TO_CFG,0x49)

/** 
 * \brief
 * Delay from read to write on same chip select.
 *
 * \details 
 * RL+BL+1-WL
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0 . RD_TO_WR_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_TO_WR_DLY(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_TO_WR_DLY     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_TO_WR_DLY(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/** 
 * \brief
 * Delay from write to write on different chip selects.
 * If ICPU_CFG::MEMCTRL_TERMRES_CTRL.ODT_WR_ENA==9 then increase this field
 * by 2 (to allow ODT handover between destination devices).
 *
 * \details 
 * BL-1
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0 . WR_CS_CHANGE_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_WR_CS_CHANGE_DLY(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_WR_CS_CHANGE_DLY     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_WR_CS_CHANGE_DLY(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/** 
 * \brief
 * Delay from read to read on different chip selects.
 *
 * \details 
 * BL
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0 . RD_CS_CHANGE_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_CS_CHANGE_DLY(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_CS_CHANGE_DLY     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_CS_CHANGE_DLY(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/** 
 * \brief
 * Delay from RAS to precharge.
 *
 * \details 
 * tRAS_min-1
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0 . RAS_TO_PRECH_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RAS_TO_PRECH_DLY(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RAS_TO_PRECH_DLY     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RAS_TO_PRECH_DLY(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Delay from write to precharge.
 *
 * \details 
 * WL+BL+tWR-1
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0 . WR_TO_PRECH_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_WR_TO_PRECH_DLY(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_WR_TO_PRECH_DLY     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_WR_TO_PRECH_DLY(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Delay from read to precharge.
 *
 * \details 
 * BL-1
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0 . RD_TO_PRECH_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_TO_PRECH_DLY(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_TO_PRECH_DLY     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_TO_PRECH_DLY(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Delay from write command to data.
 *
 * \details 
 * WL-1
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0 . WR_DATA_XFR_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_WR_DATA_XFR_DLY(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_WR_DATA_XFR_DLY     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_WR_DATA_XFR_DLY(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Delay from read command to data. Important; this delay is further
 * increased by the DQS delay logic - see ICPU_CFG::MEMCTRL_DQS_DLY for
 * more information.
 *
 * \details 
 * RL-3
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0 . RD_DATA_XFR_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_DATA_XFR_DLY(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_DATA_XFR_DLY     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING0_RD_DATA_XFR_DLY(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Timing configuration
 *
 * \details
 * See ICPU_CFG::MEMCTRL_TIMING0 for description of important parameters.
 *
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_TIMING1
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1  VTSS_IOREG(VTSS_TO_CFG,0x4a)

/** 
 * \brief
 * Delay from RAS to RAS within same bank.
 *
 * \details 
 * tRC-1
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1 . RAS_TO_RAS_SAME_BANK_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_RAS_TO_RAS_SAME_BANK_DLY(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_RAS_TO_RAS_SAME_BANK_DLY     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_RAS_TO_RAS_SAME_BANK_DLY(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * Four bank activate period.
 *
 * \details 
 * FAW-1
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1 . BANK8_FAW_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_BANK8_FAW_DLY(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_BANK8_FAW_DLY     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_BANK8_FAW_DLY(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Delay from precharge to RAS.
 *
 * \details 
 * tRP-1
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1 . PRECH_TO_RAS_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_PRECH_TO_RAS_DLY(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_PRECH_TO_RAS_DLY     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_PRECH_TO_RAS_DLY(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Delay from RAS to RAS.
 *
 * \details 
 * tRRD-1
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1 . RAS_TO_RAS_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_RAS_TO_RAS_DLY(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_RAS_TO_RAS_DLY     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_RAS_TO_RAS_DLY(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Delay from RAS to CAS.
 *
 * \details 
 * tRCD-1
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1 . RAS_TO_CAS_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_RAS_TO_CAS_DLY(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_RAS_TO_CAS_DLY     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_RAS_TO_CAS_DLY(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Delay from write to read.
 *
 * \details 
 * WL+BL+tWTR-1
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1 . WR_TO_RD_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_WR_TO_RD_DLY(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_WR_TO_RD_DLY     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING1_WR_TO_RD_DLY(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Timing configuration
 *
 * \details
 * See ICPU_CFG::MEMCTRL_TIMING0 for description of important parameters.
 *
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_TIMING2
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2  VTSS_IOREG(VTSS_TO_CFG,0x4b)

/** 
 * \brief
 * Delay after precharge all.
 *
 * \details 
 * RP-1
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2 . PRECH_ALL_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_PRECH_ALL_DLY(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_PRECH_ALL_DLY     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_PRECH_ALL_DLY(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/** 
 * \brief
 * Delay after register-write.
 *
 * \details 
 * MD-1
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2 . MDSET_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_MDSET_DLY(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_MDSET_DLY     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_MDSET_DLY(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/** 
 * \brief
 * Delay after refresh.
 *
 * \details 
 * tRFC-1
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2 . REF_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_REF_DLY(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_REF_DLY     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_REF_DLY(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Delay for initialization (see ICPU_CFG::MEMCTRL_CTRL.INITIALIZE).
 *
 * \details 
 * Before initialization: ID-1
 * After initialization: SD-1
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2 . INIT_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_INIT_DLY(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_INIT_DLY     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING2_INIT_DLY(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Timing configuration
 *
 * \details
 * See ICPU_CFG::MEMCTRL_TIMING0 for description of important parameters.
 *
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_TIMING3
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3  VTSS_IOREG(VTSS_TO_CFG,0x4c)

/** 
 * \brief
 * Read-modify-write is not used by this device.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3 . RMW_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_RMW_DLY(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_RMW_DLY     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_RMW_DLY(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Delay from read to ODT assert.
 * External ODT assert for read commands is enabled by
 * ICPU_CFG::MEMCTRL_TERMRES_CTRL.ODT_RD_ENA.
 *
 * \details 
 * OR-1
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3 . ODT_RD_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_ODT_RD_DLY(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_ODT_RD_DLY     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_ODT_RD_DLY(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Delay from write to ODT assert.
 * External ODT assert for write commands is enabled by
 * ICPU_CFG::MEMCTRL_TERMRES_CTRL.ODT_WR_ENA.
 *
 * \details 
 * OW-1
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3 . ODT_WR_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_ODT_WR_DLY(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_ODT_WR_DLY     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_ODT_WR_DLY(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Delay from read to local read-termination activate. Important; this
 * delay is further increased by the DQS delay logic - see
 * ICPU_CFG::MEMCTRL_DQS_DLY for more information.
 * Local read-termination is enabled by
 * ICPU_CFG::MEMCTRL_TERMRES_CTRL.LOCAL_ODT_RD_ENA.
 *
 * \details 
 * RL-3
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3 . LOCAL_ODT_RD_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_LOCAL_ODT_RD_DLY(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_LOCAL_ODT_RD_DLY     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_LOCAL_ODT_RD_DLY(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Delay from write to write on different chip selects.
 *
 * \details 
 * WL+tWTR-1
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3 . WR_TO_RD_CS_CHANGE_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_WR_TO_RD_CS_CHANGE_DLY(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_WR_TO_RD_CS_CHANGE_DLY     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING3_WR_TO_RD_CS_CHANGE_DLY(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Timing configuration
 *
 * \details
 * See ICPU_CFG::MEMCTRL_TIMING0 for description of important parameters.
 *
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_TIMING4
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING4  VTSS_IOREG(VTSS_TO_CFG,0x4d)

/** 
 * \brief
 * Delay for initial ZQ calibration.
 *
 * \details 
 * max(tZQinit, tDLLK)-3
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING4 . ZQCAL_INIT_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING4_ZQCAL_INIT_DLY(x)  VTSS_ENCODE_BITFIELD(x,20,12)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING4_ZQCAL_INIT_DLY     VTSS_ENCODE_BITMASK(20,12)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING4_ZQCAL_INIT_DLY(x)  VTSS_EXTRACT_BITFIELD(x,20,12)

/** 
 * \brief
 * Delay for long ZQ calibration.
 *
 * \details 
 * tZQoper-3
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING4 . ZQCAL_LONG_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING4_ZQCAL_LONG_DLY(x)  VTSS_ENCODE_BITFIELD(x,8,12)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING4_ZQCAL_LONG_DLY     VTSS_ENCODE_BITMASK(8,12)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING4_ZQCAL_LONG_DLY(x)  VTSS_EXTRACT_BITFIELD(x,8,12)

/** 
 * \brief
 * Delay for short ZQ calibration.
 *
 * \details 
 * tZQCS-3
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING4 . ZQCAL_SHORT_DLY
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING4_ZQCAL_SHORT_DLY(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING4_ZQCAL_SHORT_DLY     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TIMING4_ZQCAL_SHORT_DLY(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Mode register 0 value
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_MR0_VAL
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_MR0_VAL  VTSS_IOREG(VTSS_TO_CFG,0x4e)

/** 
 * \brief
 * Value to be programmed into the mode register (0) during SDRAM
 * initialization. During initialization bit 8 (DLL Reset) of this register
 * must be set to 0, the memory controller automatically sets this bit when
 * required during the initialization procedure.
 * After initialization this field is used for sending custom MDSET
 * commands. If ICPU_CFG::MEMCTRL_CTRL.MDSET is set then the value of this
 * field is writtten to the register defined by bit [15:14].
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_MR0_VAL . MR0_VAL
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_MR0_VAL_MR0_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_MR0_VAL_MR0_VAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_MR0_VAL_MR0_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Mode register 1 value
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_MR1_VAL
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_MR1_VAL  VTSS_IOREG(VTSS_TO_CFG,0x4f)

/** 
 * \brief
 * Value to be programmed into mode register 1 / extended mode register
 * during SDRAM initialization.
 * Bits 7 thorugh 9 (OCD Calibration Program) of this register must be set
 * to 0x7, the memory controller sets this field when required during the
 * initialization procedure.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_MR1_VAL . MR1_VAL
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_MR1_VAL_MR1_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_MR1_VAL_MR1_VAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_MR1_VAL_MR1_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Mode register 2 value
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_MR2_VAL
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_MR2_VAL  VTSS_IOREG(VTSS_TO_CFG,0x50)

/** 
 * \brief
 * Value to be programmed into mode register 2 / extended mode register 2
 * during SDRAM initialization.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_MR2_VAL . MR2_VAL
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_MR2_VAL_MR2_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_MR2_VAL_MR2_VAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_MR2_VAL_MR2_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Mode register 3 value
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_MR3_VAL
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_MR3_VAL  VTSS_IOREG(VTSS_TO_CFG,0x51)

/** 
 * \brief
 * Value to be programmed into mode register 3 / extended mode register 3
 * during SDRAM initialization.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_MR3_VAL . MR3_VAL
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_MR3_VAL_MR3_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_MR3_VAL_MR3_VAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_MR3_VAL_MR3_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief On-die-termination configuration
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_TERMRES_CTRL
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL  VTSS_IOREG(VTSS_TO_CFG,0x52)

/** 
 * \brief
 * Set this field to extend the ODT termination output by one clock during
 * read operations.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL . ODT_RD_EXT
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_ODT_RD_EXT(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_ODT_RD_EXT  VTSS_BIT(11)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_ODT_RD_EXT(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Set to enable ODT output during read operations.
 *
 * \details 
 * 0: Reading will not assert ODT
 * 1: Assert ODT for CS0 read
 * 2: Assert ODT for CS1 read
 * 3: Assert ODT for any read
 * Other values are reserved
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL . ODT_RD_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_ODT_RD_ENA(x)  VTSS_ENCODE_BITFIELD(x,7,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_ODT_RD_ENA     VTSS_ENCODE_BITMASK(7,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_ODT_RD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,4)

/** 
 * \brief
 * Set this field to extend the ODT termination output by one clock during
 * write operations.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL . ODT_WR_EXT
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_ODT_WR_EXT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_ODT_WR_EXT  VTSS_BIT(6)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_ODT_WR_EXT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Set to assert ODT output(s) during write operations.
 *
 * \details 
 * 0: Writing will not assert ODT
 * 1: Assert ODT for CS1 write
 * 2: Assert ODT for CS0 write
 * 3: Assert ODT for any write
 * Others values are reserved
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL . ODT_WR_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_ODT_WR_ENA(x)  VTSS_ENCODE_BITFIELD(x,2,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_ODT_WR_ENA     VTSS_ENCODE_BITMASK(2,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_ODT_WR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,4)

/** 
 * \brief
 * Set this field to extend the local termination by one clock during read
 * operations.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL . LOCAL_ODT_RD_EXT
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_LOCAL_ODT_RD_EXT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_LOCAL_ODT_RD_EXT  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_LOCAL_ODT_RD_EXT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set to enable local termination during a read operation.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL . LOCAL_ODT_RD_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_LOCAL_ODT_RD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_LOCAL_ODT_RD_ENA  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_TERMRES_CTRL_LOCAL_ODT_RD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Design for test features
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_DFT
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DFT    VTSS_IOREG(VTSS_TO_CFG,0x53)

/** 
 * \brief
 * Set this field to disable check for data in every clock cycle during the
 * DDR read test. Setting this field makes it possible to send in data with
 * a slower rate than the internal clock frequency and thus allowing for
 * input voltage to stabilize prior to toggeling DQS when checking for
 * voltages.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DFT . DDRDFT_LBW
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_LBW(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_LBW  VTSS_BIT(7)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_LBW(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Set to force the DQS gate open (and no flushing).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DFT . DDRDFT_GATE_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_GATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_GATE_ENA  VTSS_BIT(6)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_GATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Set to force enable of the local-term.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DFT . DDRDFT_TERM_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_TERM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_TERM_ENA  VTSS_BIT(5)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_TERM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DFT . DDRDFT_A10
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_A10(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_A10  VTSS_BIT(4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_A10(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Status for ReadTest.
 *
 * \details 
 * 0: Err
 * 1: Pass
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DFT . DDRDFT_STAT
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_STAT  VTSS_BIT(3)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_STAT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set this field to configure a specific testmode. For the SSO output
 * pattern address output A10 will be forced to the value that is set in
 * ICPU_CFG::MEMCTRL_DFT.DDRDFT_A10 (to be used for measuring swing).
 *
 * \details 
 * 0: Sample (expect signiture pattern)
 * 1: Drive all-zeros (where possible)
 * 2: Drive all-ones (where possible)
 * 3: Drive SSO pattern (A10 value is determined by DDRDFT_A10)
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DFT . DDRDFT_MODE
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_MODE(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_MODE     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Set this field to enable testmode.
 *
 * \details 
 * 0: Disabled
 * 1: Enabled
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DFT . DDRDFT_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_ENA  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_DFT_DDRDFT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief DQS window configuration
 *
 * \details
 * This register is replicated two times, once for each Byte Lane (first
 * replication corresponds to Byte Lane 0).
 *
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_DQS_DLY
 *
 * @param ri Replicator: x_DATA_BYTE_WID (??), 0-1
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_DLY(ri)  VTSS_IOREG(VTSS_TO_CFG,0x54 + (ri))

/** 
 * \brief
 * Set this field if training of individual data bit is required. When this
 * field is set, data will not automatically be realligned during read from
 * SDRAM. This enables training of the read-timing for individual data-bits
 * inside the byte-lanes. The actual procedure for training is TBA
 * (targeted for future high-speed implementations).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_DLY . TRAIN_DQ_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_DLY_TRAIN_DQ_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_DLY_TRAIN_DQ_ENA  VTSS_BIT(11)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_DLY_TRAIN_DQ_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * The functionality of this field is the same as DQS_DLY_TRM, just for the
 * nDQS signal (2'nd DDR data-set). See DQS_DLY_TRM for description and
 * encoding.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_DLY . DQS_DLY_TRM1
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_DLY_DQS_DLY_TRM1(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_DLY_DQS_DLY_TRM1     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_DLY_DQS_DLY_TRM1(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/** 
 * \brief
 * This field allows fine tuning of the DQS signal (1'st DDR data-set)
 * read-window delay (configured by DQS_DLY) by adding/removing an offset
 * in steps of 25ps (typical).
 *
 * \details 
 * 0: -3 steps.
 * 1: -2 steps.
 * 2: -1 steps.
 * 3: Norminal delay.
 * 4: +1 steps.
 * 5: +2 steps.
 * 6: +3 steps.
 * 7: +4 steps.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_DLY . DQS_DLY_TRM0
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_DLY_DQS_DLY_TRM0(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_DLY_DQS_DLY_TRM0     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_DLY_DQS_DLY_TRM0(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * This field configures read-window delay as an offset in 1/4 clock cycles
 * from the fixed read-delay configured in MEMCTRL_TIMING0.RD_DATA_XFR_DLY.
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
 * This register has the same replication scheme as
 * ICPU_CFG::MEMCTRL_DQS_DLY.
 *
 * Register: \a ICPU_CFG:MEMCTRL:MEMCTRL_DQS_AUTO
 *
 * @param ri Replicator: x_DATA_BYTE_WID (??), 0-1
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO(ri)  VTSS_IOREG(VTSS_TO_CFG,0x56 + (ri))

/** 
 * \brief
 * Resynced DQS (or nDQS) drift indication.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO . DQS_DRIFT
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_DRIFT(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_DRIFT     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_DRIFT(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * This field is set if the automatic read-window drift detection causes an
 * overflow in the MEMCTRL_DQS_DLY.DQS_DLY field. If this occurs during
 * runtime, the memory controller must be configured to provide the
 * read-indication later.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO . DQS_OVERFLOW
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_OVERFLOW(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_OVERFLOW  VTSS_BIT(5)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_OVERFLOW(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * This field is set if the automatic read-window drift detection causes an
 * underflow in the MEMCTRL_DQS_DLY.DQS_DLY field. If this occurs during
 * runtime, the memory controller must be configured to provide the
 * read-indication earlier.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO . DQS_UNDERFLOW
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_UNDERFLOW(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_UNDERFLOW  VTSS_BIT(4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_UNDERFLOW(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Selects either DQS or nDQS to be monitored for automatic drift
 * detection.
 *
 * \details 
 * 0: DQS is monitored
 * 1: nDQS is monitored
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO . DQS_AUTO_SRC
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_AUTO_SRC(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_AUTO_SRC  VTSS_BIT(3)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_AUTO_SRC(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * This field is set when an up-ajusting happens. If this field is set and
 * DQS_AUTO_ENA is also set, then the MEMCTRL_DQS_DLY.DQS_DLY has been
 * increased.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO . DQS_AUTO_UP
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_AUTO_UP(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_AUTO_UP  VTSS_BIT(2)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_AUTO_UP(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * This field is set when an down-ajusting happens. If this field is set
 * and DQS_AUTO_ENA is also set, then the MEMCTRL_DQS_DLY.DQS_DLY has been
 * decremented.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO . DQS_AUTO_DOWN
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_AUTO_DOWN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_AUTO_DOWN  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_AUTO_DOWN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

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
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_AUTO_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_AUTO_ENA  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMCTRL_DQS_AUTO_DQS_AUTO_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SSTL configuration
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMPHY_CFG
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMPHY_CFG     VTSS_IOREG(VTSS_TO_CFG,0x58)

/** 
 * \brief
 * Set to disable flushing of write- and read-data during controller idle
 * time.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_CFG . PHY_FLUSH_DIS
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_FLUSH_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_FLUSH_DIS  VTSS_BIT(10)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_FLUSH_DIS(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Set this field to disable masking or dummy insert of receive data words.
 * During normal operation this is not needed, but during DQS/DQ training
 * this feature makes sure the SBA get the number of datasets that has been
 * requested.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_CFG . PHY_RD_ADJ_DIS
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_RD_ADJ_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_RD_ADJ_DIS  VTSS_BIT(9)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_RD_ADJ_DIS(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Set this field to extend the read-data-window by one clock-cycle (two
 * DDR data slots).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_CFG . PHY_DQS_EXT
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_DQS_EXT(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_DQS_EXT  VTSS_BIT(8)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_DQS_EXT(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Soft-reset to the FIFO blocks in the memory controller physical
 * interface. Leave at default value.
 *
 * \details 
 * 0: PHY FIFOs is in working mode.
 * 1: PHY FIFOs is forced in reset.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_CFG . PHY_FIFO_RST
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_FIFO_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_FIFO_RST  VTSS_BIT(7)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_FIFO_RST(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Soft-reset to the byte lane DLLs in the memory controller physical
 * interface.
 *
 * \details 
 * 0: PHY DLLs is in working mode.
 * 1: PHY DLLs is forced in reset.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_CFG . PHY_DLL_BL_RST
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_DLL_BL_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_DLL_BL_RST  VTSS_BIT(6)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_DLL_BL_RST(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Soft-reset to the Command lane DLL in the memory controller physical
 * interface.
 *
 * \details 
 * 0: PHY DLL is in working mode.
 * 1: PHY DLL is forced in reset.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_CFG . PHY_DLL_CL_RST
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_DLL_CL_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_DLL_CL_RST  VTSS_BIT(5)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_DLL_CL_RST(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Set to enable output drive of the ODT output.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_CFG . PHY_ODT_OE
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_ODT_OE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_ODT_OE  VTSS_BIT(4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_ODT_OE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set to enable output drive of the CK/nCK and CKE outputs.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_CFG . PHY_CK_OE
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_CK_OE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_CK_OE  VTSS_BIT(3)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_CK_OE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set to enable output drive of the Command Lane outputs.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_CFG . PHY_CL_OE
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_CL_OE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_CL_OE  VTSS_BIT(2)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_CL_OE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set this field to enable the SSTL mode for the memory controllers
 * physical interfaces.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_CFG . PHY_SSTL_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_SSTL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_SSTL_ENA  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_SSTL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

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
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_RST  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_CFG_PHY_RST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Design for test features
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMPHY_DFT
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DFT     VTSS_IOREG(VTSS_TO_CFG,0x59)

/** 
 * \brief
 * Set to force the DLLs into bypass mode.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DFT . PHY_DLL_BYPASS
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DFT_PHY_DLL_BYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DFT_PHY_DLL_BYPASS  VTSS_BIT(2)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DFT_PHY_DLL_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set to enable the ATO (Analog Test Output) driver.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DFT . PHY_AT_OE
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DFT_PHY_AT_OE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DFT_PHY_AT_OE  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DFT_PHY_AT_OE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set to enable SSTL drivers/receivers in the DTO (Digital Test Outputs)
 * drivers.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DFT . PHY_DT_SSTL_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DFT_PHY_DT_SSTL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DFT_PHY_DT_SSTL_ENA  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DFT_PHY_DT_SSTL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief DLL configuration
 *
 * \details
 * This register is replicated three times, replication-0 controls the
 * Command Lane DLL, replication-1 controls the Lower Byte Lane DLL, and
 * replication-2 controls the Upper Byte Lane DLL.
 *
 * Register: \a ICPU_CFG:MEMCTRL:MEMPHY_DLLCFG0
 *
 * @param ri Replicator: x_DATA_BYTE_WID_PLUS1 (??), 0-2
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0(ri)  VTSS_IOREG(VTSS_TO_CFG,0x5a + (ri))

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0 . DLLCFG_RES6
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES6(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES6     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES6(x)  VTSS_EXTRACT_BITFIELD(x,30,2)

/** 
 * \brief
 * Lock detector enable.
 *
 * \details 
 * 0: Disable lock detector.
 * 1: Enable lock detector.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0 . DLLCFG_LOCK_DET_EN
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_LOCK_DET_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_LOCK_DET_EN  VTSS_BIT(29)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_LOCK_DET_EN(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0 . DLLCFG_RES5
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES5(x)  VTSS_ENCODE_BITFIELD(x,27,2)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES5     VTSS_ENCODE_BITMASK(27,2)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES5(x)  VTSS_EXTRACT_BITFIELD(x,27,2)

/** 
 * \brief
 * Slave bias generator control voltage trim.
 *
 * \details 
 * 0: Vc level trim: minimum adjust.
 * 7: Vc level trim: maximum adjust.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0 . DLLCFG_BIAS_TRM3
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_BIAS_TRM3(x)  VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_BIAS_TRM3     VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_BIAS_TRM3(x)  VTSS_EXTRACT_BITFIELD(x,24,3)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0 . DLLCFG_RES4
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES4(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES4  VTSS_BIT(23)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES4(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * Slave bias generator frequency trim.
 *
 * \details 
 * 0: Fmax trim: minimum adjust.
 * 7: Fmax trim: maximum adjust.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0 . DLLCFG_BIAS_TRM2
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_BIAS_TRM2(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_BIAS_TRM2     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_BIAS_TRM2(x)  VTSS_EXTRACT_BITFIELD(x,20,3)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0 . DLLCFG_RES3
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES3(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES3  VTSS_BIT(19)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES3(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * Master bias generator control voltage trim.
 *
 * \details 
 * 0: Vc level trim: minimum adjust.
 * 7: Vc level trim: maximum adjust.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0 . DLLCFG_BIAS_TRM1
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_BIAS_TRM1(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_BIAS_TRM1     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_BIAS_TRM1(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0 . DLLCFG_RES2
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES2(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES2  VTSS_BIT(15)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES2(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Master bias generator frequency trim.
 *
 * \details 
 * 0: Fmax trim: minimum adjust.
 * 7: Fmax trim: maximum adjust.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0 . DLLCFG_BIAS_TRM0
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_BIAS_TRM0(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_BIAS_TRM0     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_BIAS_TRM0(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0 . DLLCFG_RES1
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES1(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES1  VTSS_BIT(11)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES1(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Analog test control. Selects the analog signal to be viewed at ATO
 * (Analog Test Output) when enabled by DLLCFG_TEST_CTRL_EN and
 * MEMPHY_DLLCFG1.DLLCFG_TEST_HIZB_A.
 *
 * \details 
 * 0: Filter output (Vc).
 * 1: Replica bias output for NMOS (Vbn).
 * 2: Replica bias output for PMOS (Vbp).
 * 3: VDD.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0 . DLLCFG_TEST_CTRL_A
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_TEST_CTRL_A(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_TEST_CTRL_A     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_TEST_CTRL_A(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/** 
 * \brief
 * Digital test control. Selects the digital signal to be viewed at DTO[1]
 * (Digital Test Output), DTO[0] always output clk_0 when enabled by
 * DLLCFG_TEST_CTRL_EN.
 *
 * \details 
 * 0: 0deg output clock (clk_0).
 * 1: 90deg output clock (clk_90).
 * 2: 180deg output clock (clk_180).
 * 3: 270deg output clock (clk_270).
 * 4: 360deg internal clock (clk_360_int).
 * 5: Speed-up pulse (spdup).
 * 6: Slow-down pulse (slwdn).
 * 7: Output clock (cclk_0).
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0 . DLLCFG_TEST_CTRL_D
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_TEST_CTRL_D(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_TEST_CTRL_D     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_TEST_CTRL_D(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * Test control enable for ATO and DTO (Analog and Digital Test Outputs).
 *
 * \details 
 * 0: Digital and Analog test outputs are disabled and drive 0/VSS.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0 . DLLCFG_TEST_CTRL_EN
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_TEST_CTRL_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_TEST_CTRL_EN  VTSS_BIT(5)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_TEST_CTRL_EN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Charge pump current trim.
 *
 * \details 
 * 0: Maximum current.
 * 7: Minimum current.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0 . DLLCFG_IPUMP_TRM
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_IPUMP_TRM(x)  VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_IPUMP_TRM     VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_IPUMP_TRM(x)  VTSS_EXTRACT_BITFIELD(x,2,3)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0 . DLLCFG_RES0
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG0_DLLCFG_RES0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief DLL configuration
 *
 * \details
 * This register has the same replication scheme as
 * ICPU_CFG::MEMPHY_DLLCFG0.
 *
 * Register: \a ICPU_CFG:MEMCTRL:MEMPHY_DLLCFG1
 *
 * @param ri Replicator: x_DATA_BYTE_WID_PLUS1 (??), 0-2
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1(ri)  VTSS_IOREG(VTSS_TO_CFG,0x5d + (ri))

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1 . DLLCFG_RES9
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1_DLLCFG_RES9(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1_DLLCFG_RES9  VTSS_BIT(19)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1_DLLCFG_RES9(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * Analog test output tri-stated control. Observe, all the DLLs are
 * connected to the same analog test output. Only one DLL must have ATO
 * enabled at any point in time.
 *
 * \details 
 * 0: ATO is tri-stated (High-Z).
 * 1: ATO is driven.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1 . DLLCFG_TEST_HIZB_A
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1_DLLCFG_TEST_HIZB_A(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1_DLLCFG_TEST_HIZB_A  VTSS_BIT(18)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1_DLLCFG_TEST_HIZB_A(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1 . DLLCFG_RES8
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1_DLLCFG_RES8(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1_DLLCFG_RES8     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1_DLLCFG_RES8(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/** 
 * \brief
 * Feed-forward delay adjust.
 *
 * \details 
 * 0:Minimum additional delay
 * 7:Maximum additional delay
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1 . DLLCFG_FF_TRM
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1_DLLCFG_FF_TRM(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1_DLLCFG_FF_TRM     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1_DLLCFG_FF_TRM(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/** 
 * \brief
 * Feed-back delay adjust.
 *
 * \details 
 * 0:Minimum additional delay
 * 7:Maximum additional delay
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1 . DLLCFG_FB_TRM
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1_DLLCFG_FB_TRM(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1_DLLCFG_FB_TRM     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1_DLLCFG_FB_TRM(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1 . DLLCFG_RES7
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1_DLLCFG_RES7(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1_DLLCFG_RES7     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DLLCFG1_DLLCFG_RES7(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief DQ window configuration
 *
 * \details
 * This register has the same replication scheme as
 * ICPU_CFG::MEMCTRL_DQS_DLY.
 *
 * Register: \a ICPU_CFG:MEMCTRL:MEMPHY_DQ_DLY_TRM
 *
 * @param ri Replicator: x_DATA_BYTE_WID (??), 0-1
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DQ_DLY_TRM(ri)  VTSS_IOREG(VTSS_TO_CFG,0x60 + (ri))

/** 
 * \brief
 * Data input window placement trim for data latched on DQS and nDQS.
 * Each DQ has 4 bit of associated trim-settings, these are replicated for
 * each of the DQ pins. Bits 3:0 controls DQ0, bits 7:4 controls DQ1 and so
 * on.
 * Inside the 4 bits of trim configurations; [1:0] configrues strobe
 * placement trim for data latched by DQS and [3:2] controls strobe
 * placement trim for data latched by nDQS.
 *
 * \details 
 * 0: nominal delay.
 * 1: nominal delay + 1 step.
 * 2: nominal delay + 2 steps.
 * 3: nominal delay + 3 steps.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_DQ_DLY_TRM . PHY_DQ_DLY_TRM
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_DQ_DLY_TRM_PHY_DQ_DLY_TRM(x)  (x)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_DQ_DLY_TRM_PHY_DQ_DLY_TRM     0xffffffff
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_DQ_DLY_TRM_PHY_DQ_DLY_TRM(x)  (x)


/** 
 * \brief SSTL drive-strength calibration
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMPHY_ZCAL
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL    VTSS_IOREG(VTSS_TO_CFG,0x62)

/** 
 * \brief
 * Controls speed of the automatic impedance calibration.
 *
 * \details 
 * 0: Fast
 * 1: Slow
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL . ZCAL_CLK_SEL
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_ZCAL_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_ZCAL_CLK_SEL  VTSS_BIT(9)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_ZCAL_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Together with the external reference resistor this field configures the
 * SSTL On-Die-Termination (ODT) impedance.
 * This field must be configured prior to, or at the same time as, setting
 * the ICPU_CFG::MEMPHY_ZCAL.ZCAL_ENA field.
 *
 * \details 
 * 2: 150ohms
 * 3: 120ohms
 * 5: 75ohms
 * 7: 60ohms
 * 8: 50ohms
 * 11: 40ohms
 * 13: 34ohms
 * Other values are reserved.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL . ZCAL_PROG_ODT
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_ZCAL_PROG_ODT(x)  VTSS_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_ZCAL_PROG_ODT     VTSS_ENCODE_BITMASK(5,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_ZCAL_PROG_ODT(x)  VTSS_EXTRACT_BITFIELD(x,5,4)

/** 
 * \brief
 * Together with the external reference resistor this field configures the
 * SSTL output drive-strength.
 * This field must be configured prior to, or at the same time as, setting
 * the ICPU_CFG::MEMPHY_ZCAL.ZCAL_ENA field.
 *
 * \details 
 * 2: 150ohms
 * 3: 120ohms
 * 5: 75ohms
 * 7: 60ohms
 * 8: 50ohms
 * 11: 40ohms
 * 13: 34ohms
 * Other values are reserved.
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL . ZCAL_PROG
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_ZCAL_PROG(x)  VTSS_ENCODE_BITFIELD(x,1,4)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_ZCAL_PROG     VTSS_ENCODE_BITMASK(1,4)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_ZCAL_PROG(x)  VTSS_EXTRACT_BITFIELD(x,1,4)

/** 
 * \brief
 * Set this field to start automatic SSTL output and ODT drive-strength
 * calibration. This field is cleared when the automatic calibration has
 * completed.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL . ZCAL_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_ZCAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_ZCAL_ENA  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_ZCAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SSTL drive-strength status
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMPHY_ZCAL_STAT
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT  VTSS_IOREG(VTSS_TO_CFG,0x63)

/** 
 * \brief
 * Current value of impedance control.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT . ZCAL_ZCTRL
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_ZCTRL(x)  VTSS_ENCODE_BITFIELD(x,12,20)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_ZCTRL     VTSS_ENCODE_BITMASK(12,20)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_ZCTRL(x)  VTSS_EXTRACT_BITFIELD(x,12,20)

/** 
 * \brief
 * Status of On-Die-termination pull-up calibration.
 *
 * \details 
 * 0: Completed with no errors
 * 1: Overflow error
 * 2: Underflow errror
 * 3: Calibration in progress
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT . ZCAL_STAT_ODTPU
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_STAT_ODTPU(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_STAT_ODTPU     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_STAT_ODTPU(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Status of On-Die-termination pull-down calibration.
 *
 * \details 
 * 0: Completed with no errors
 * 1: Overflow error
 * 2: Underflow errror
 * 3: Calibration in progress
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT . ZCAL_STAT_ODTPD
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_STAT_ODTPD(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_STAT_ODTPD     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_STAT_ODTPD(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * Status of pull-up calibration.
 *
 * \details 
 * 0: Completed with no errors
 * 1: Overflow error
 * 2: Underflow errror
 * 3: Calibration in progress
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT . ZCAL_STAT_PU
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_STAT_PU(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_STAT_PU     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_STAT_PU(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Status of pull-down calibration.
 *
 * \details 
 * 0: Completed with no errors
 * 1: Overflow error
 * 2: Underflow errror
 * 3: Calibration in progress
 *
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT . ZCAL_STAT_PD
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_STAT_PD(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_STAT_PD     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_STAT_PD(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Set if an error occurs during automatic impedance calibration.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT . ZCAL_ERR
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_ERR  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_ERR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set when the automatic impedance calibration indicates done.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT . ZCAL_DONE
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_DONE  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_STAT_ZCAL_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SSTL drive-strength override
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMPHY_ZCAL_OVR
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_OVR  VTSS_IOREG(VTSS_TO_CFG,0x64)

/** 
 * \brief
 * Value for manual override of impedance control.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_OVR . ZCAL_OVR_DATA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_OVR_ZCAL_OVR_DATA(x)  VTSS_ENCODE_BITFIELD(x,12,20)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_OVR_ZCAL_OVR_DATA     VTSS_ENCODE_BITMASK(12,20)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_OVR_ZCAL_OVR_DATA(x)  VTSS_EXTRACT_BITFIELD(x,12,20)

/** 
 * \brief
 * Debug field that allows the feedback from done indication to clearing of
 * MEMPHY_ZCAL.ZCAL_ENA to be broken. That is; when this field is set
 * ZCAL_ENA will never be cleared.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_OVR . ZCAL_ENACLR_DIS
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_OVR_ZCAL_ENACLR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_OVR_ZCAL_ENACLR_DIS  VTSS_BIT(2)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_OVR_ZCAL_ENACLR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * The zcomp input from the IO ring. Is read directly from other clock
 * domain, keep reading until same value returned twice in a row.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_OVR . ZCAL_ZCOMP
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_OVR_ZCAL_ZCOMP(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_OVR_ZCAL_ZCOMP  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_OVR_ZCAL_ZCOMP(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set to force override value MEMCTRl_ZCAL_OVR.ZCAL_OVR_DATA instead of
 * automatic calibration result.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_OVR . ZCAL_OVR_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_OVR_ZCAL_OVR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_OVR_ZCAL_OVR_ENA  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_OVR_ZCAL_OVR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SSTL drive-strength force
 *
 * \details
 * Register: \a ICPU_CFG:MEMCTRL:MEMPHY_ZCAL_FORCE
 */
#define VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_FORCE  VTSS_IOREG(VTSS_TO_CFG,0x65)

/** 
 * \brief
 * ZCAL value when forcing calibration signals.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_FORCE . ZCAL_FORCE_ZCAL
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_FORCE_ZCAL_FORCE_ZCAL(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_FORCE_ZCAL_FORCE_ZCAL     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_FORCE_ZCAL_FORCE_ZCAL(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * ZQ_OFF value when forcing calibration signals.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_FORCE . ZCAL_FORCE_ZQ_OFF
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_FORCE_ZCAL_FORCE_ZQ_OFF(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_FORCE_ZCAL_FORCE_ZQ_OFF  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_FORCE_ZCAL_FORCE_ZQ_OFF(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set to force override of calibration signals.

 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_FORCE . ZCAL_FORCE_ENA
 */
#define  VTSS_F_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_FORCE_ZCAL_FORCE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_FORCE_ZCAL_FORCE_ENA  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_MEMCTRL_MEMPHY_ZCAL_FORCE_ZCAL_FORCE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ICPU_CFG:TWI_DELAY
 *
 * TWI hold time configuration
 */


/** 
 * \brief TWI hold time configuration
 *
 * \details
 * Register: \a ICPU_CFG:TWI_DELAY:TWI_CONFIG
 */
#define VTSS_ICPU_CFG_TWI_DELAY_TWI_CONFIG   VTSS_IOREG(VTSS_TO_CFG,0x66)

/** 
 * \brief
 * Configure the hold time delay to apply to SDA after SCK when
 * transmitting from the device. This delay is expressed in a number of
 * VCore System clock cycles. The delay value should be as close to 300ns
 * as possible without going below 300ns.
 *
 * \details 
 * Set to (300ns/4.8ns + 2) = 65
 *
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
#define  VTSS_F_ICPU_CFG_TWI_DELAY_TWI_CONFIG_TWI_DELAY_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_TWI_DELAY_TWI_CONFIG_TWI_DELAY_ENABLE  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_TWI_DELAY_TWI_CONFIG_TWI_DELAY_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ICPU_CFG:TWI_SPIKE_FILTER
 *
 * TWI spike filter configuration
 */


/** 
 * \brief TWI spike filter configuration
 *
 * \details
 * Register: \a ICPU_CFG:TWI_SPIKE_FILTER:TWI_SPIKE_FILTER_CFG
 */
#define VTSS_ICPU_CFG_TWI_SPIKE_FILTER_TWI_SPIKE_FILTER_CFG  VTSS_IOREG(VTSS_TO_CFG,0x67)

/** 
 * \brief
 * Configuration of the spike filter width on the SCL and SDA inputs.
 * Filters spikes with a width of (SPIKE_FILTER_CFG+1)*SYSTEM_CLK or less.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_TWI_SPIKE_FILTER_TWI_SPIKE_FILTER_CFG . SPIKE_FILTER_CFG
 */
#define  VTSS_F_ICPU_CFG_TWI_SPIKE_FILTER_TWI_SPIKE_FILTER_CFG_SPIKE_FILTER_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_ICPU_CFG_TWI_SPIKE_FILTER_TWI_SPIKE_FILTER_CFG_SPIKE_FILTER_CFG     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_ICPU_CFG_TWI_SPIKE_FILTER_TWI_SPIKE_FILTER_CFG_SPIKE_FILTER_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * Register Group: \a ICPU_CFG:FDMA
 *
 * Frame DMA
 */


/** 
 * \brief Pointer to next DCB
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_DCB_LLP
 *
 * @param ri Replicator: x_FDMA_CH_CNT (??), 0-9
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_DCB_LLP(ri)  VTSS_IOREG(VTSS_TO_CFG,0x68 + (ri))

/** 
 * \brief
 * This field is used by the FDMA for tracking lists of DCBs. This field is
 * updated automatically when the FDMA load DCBs from memory. This field
 * can only be modified when the channel is in safe mode, see
 * ICPU_CFG::FDMA_CH_SAFE.CH_SAFE for more information.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_DCB_LLP . LLP
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_DCB_LLP_LLP(x)  (x)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_DCB_LLP_LLP     0xffffffff
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_DCB_LLP_LLP(x)  (x)


/** 
 * \brief Pointer to data block
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_DCB_DATAP
 *
 * @param ri Replicator: x_FDMA_CH_CNT (??), 0-9
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_DCB_DATAP(ri)  VTSS_IOREG(VTSS_TO_CFG,0x72 + (ri))

/** 
 * \brief
 * For debug, current data-pointer.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_DCB_DATAP . DATAP
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_DCB_DATAP_DATAP(x)  (x)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_DCB_DATAP_DATAP     0xffffffff
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_DCB_DATAP_DATAP(x)  (x)


/** 
 * \brief Length of data block
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_DCB_DATAL
 *
 * @param ri Replicator: x_FDMA_CH_CNT (??), 0-9
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_DCB_DATAL(ri)  VTSS_IOREG(VTSS_TO_CFG,0x7c + (ri))

/** 
 * \brief
 * For debug, current token-indication.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_DCB_DATAL . TOKEN
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_DCB_DATAL_TOKEN(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_DCB_DATAL_TOKEN  VTSS_BIT(17)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_DCB_DATAL_TOKEN(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * For debug, current data-length.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_DCB_DATAL . DATAL
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_DCB_DATAL_DATAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_DCB_DATAL_DATAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_DCB_DATAL_DATAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Status word
 *
 * \details
 * This register is updated by the FDMA during extraction or injection.
 * Software cannot rely on the value of this register.
 *
 * Register: \a ICPU_CFG:FDMA:FDMA_DCB_STAT
 *
 * @param ri Replicator: x_FDMA_CH_CNT (??), 0-9
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_DCB_STAT(ri)  VTSS_IOREG(VTSS_TO_CFG,0x86 + (ri))

/** 
 * \brief
 * Block offset in bytes, the value of this field is loaded from the DCB.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_DCB_STAT . BLOCKO
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_DCB_STAT_BLOCKO(x)  VTSS_ENCODE_BITFIELD(x,20,12)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_DCB_STAT_BLOCKO     VTSS_ENCODE_BITMASK(20,12)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_DCB_STAT_BLOCKO(x)  VTSS_EXTRACT_BITFIELD(x,20,12)

/** 
 * \brief
 * Pruned/Done indication.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_DCB_STAT . PD
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_DCB_STAT_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_DCB_STAT_PD  VTSS_BIT(19)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_DCB_STAT_PD(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * Abort indication.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_DCB_STAT . ABORT
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_DCB_STAT_ABORT(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_DCB_STAT_ABORT  VTSS_BIT(18)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_DCB_STAT_ABORT(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Set when the current DCB contains end-of-frame.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_DCB_STAT . EOF
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_DCB_STAT_EOF(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_DCB_STAT_EOF  VTSS_BIT(17)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_DCB_STAT_EOF(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Set when the current DCB contains start-of-frame.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_DCB_STAT . SOF
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_DCB_STAT_SOF(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_DCB_STAT_SOF  VTSS_BIT(16)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_DCB_STAT_SOF(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Block size in bytes, excluding offset (as specified in
 * ICPU_CFG::FDMA_DCB_STAT.BLOCKO). For frames that span multiple DCBs,
 * this field only shows the amount of data in the current DCB.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_DCB_STAT . BLOCKL
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_DCB_STAT_BLOCKL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_DCB_STAT_BLOCKL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_DCB_STAT_BLOCKL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Pointer to current DCB
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_DCB_LLP_PREV
 *
 * @param ri Replicator: x_FDMA_CH_CNT (??), 0-9
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_DCB_LLP_PREV(ri)  VTSS_IOREG(VTSS_TO_CFG,0x90 + (ri))

/** 
 * \brief
 * This field holds the pointer to current DCB (the previous
 * ICPU_CFG::FDMA_DCB_LLP.LLP).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_DCB_LLP_PREV . LLP_PREV
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_DCB_LLP_PREV_LLP_PREV(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_DCB_LLP_PREV_LLP_PREV     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_DCB_LLP_PREV_LLP_PREV(x)  VTSS_EXTRACT_BITFIELD(x,2,30)


/** 
 * \brief Current channel status
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_CH_STAT
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_CH_STAT      VTSS_IOREG(VTSS_TO_CFG,0x9a)

/** 
 * \brief
 * Shows status for all FDMA channels, there is one bit per channel.
 *
 * \details 
 * 0:Disabled
 * 1:Updating, or Active
 *
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_CH_STAT . CH_STAT
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_CH_STAT_CH_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_CH_STAT_CH_STAT     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_CH_STAT_CH_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Current channel safe-status
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_CH_SAFE
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_CH_SAFE      VTSS_IOREG(VTSS_TO_CFG,0x9b)

/** 
 * \brief
 * When set it is safe for software to read/modify/write
 * ICPU_CFG::FDMA_DCB_LLP.LLP, ICPU_CFG::FDMA_CH_CNT.CH_CNT_SIG,
 * ICPU_CFG::FDMA_CH_CNT.CH_CNT_DCB, and
 * ICPU_CFG::FDMA_CH_INJ_TOKEN_CNT.CH_INJ_TOKEN_CNT. There is one bit per
 * channel.
 * This field is set when a channel is a) disabled or b) active and
 * scheduled for disabling.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_CH_SAFE . CH_SAFE
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_CH_SAFE_CH_SAFE(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_CH_SAFE_CH_SAFE     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_CH_SAFE_CH_SAFE(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Activate specific channels
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_CH_ACTIVATE
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_CH_ACTIVATE  VTSS_IOREG(VTSS_TO_CFG,0x9c)

/** 
 * \brief
 * Enables specific FDMA channels, there is one bit per channel. Setting a
 * bit in this field will clear a corresponding pending
 * ICPU_CFG::FDMA_CH_DISABLE.CH_DISABLE request. Bits in this field are
 * cleared immediately when set.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_CH_ACTIVATE . CH_ACTIVATE
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_CH_ACTIVATE_CH_ACTIVATE(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_CH_ACTIVATE_CH_ACTIVATE     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_CH_ACTIVATE_CH_ACTIVATE(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Disable specific channels
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_CH_DISABLE
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_CH_DISABLE   VTSS_IOREG(VTSS_TO_CFG,0x9d)

/** 
 * \brief
 * Schedules specific FDMA channels to be disabled, there is one bit per
 * channel. The channel will finish the current DCB and then disable (after
 * writing the DCB status word). Bits in this field is cleared either when
 * the channel disables or by writing
 * ICPU_CFG::FDMA_CH_ACTIVATE.CH_ACTIVATE).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_CH_DISABLE . CH_DISABLE
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_CH_DISABLE_CH_DISABLE(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_CH_DISABLE_CH_DISABLE     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_CH_DISABLE_CH_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Ungraceful disable of specific channels
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_CH_FORCEDIS
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_CH_FORCEDIS  VTSS_IOREG(VTSS_TO_CFG,0x9e)

/** 
 * \brief
 * Immediately disable specific FDMA channels, there is one bit per
 * channel. Unlike ICPU_CFG::FDMA_CH_DISABLE using CH_FORCEDIS will not
 * take the state of the channel into account, if the channel is actively
 * extracting or injecting from/to QS there is no guarantee that it will be
 * functional after disabling the channel.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_CH_FORCEDIS . CH_FORCEDIS
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_CH_FORCEDIS_CH_FORCEDIS(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_CH_FORCEDIS_CH_FORCEDIS     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_CH_FORCEDIS_CH_FORCEDIS(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Channel counters
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_CH_CNT
 *
 * @param ri Replicator: x_FDMA_CH_CNT (??), 0-9
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_CH_CNT(ri)   VTSS_IOREG(VTSS_TO_CFG,0x9f + (ri))

/** 
 * \brief
 * This field is incremented every time the channel saves status for a DCB
 * that has EOF.
 * This counter can only be modified safely when the corresponding channel
 * is disabled (see ICPU_CFG::FDMA_CH_STAT.CH_STAT for more information).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_CH_CNT . CH_CNT_FRM
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_CH_CNT_CH_CNT_FRM(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_CH_CNT_CH_CNT_FRM     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_CH_CNT_CH_CNT_FRM(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * This field is incremented every time the channel loads a DCB.
 * This counter can be modified safely while the corresponding channel is
 * safe (see ICPU_CFG::FDMA_CH_SAFE.CH_SAFE for more information).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_CH_CNT . CH_CNT_DCB
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_CH_CNT_CH_CNT_DCB(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_CH_CNT_CH_CNT_DCB     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_CH_CNT_CH_CNT_DCB(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * This field is incremented every time the channel loads a DCB that has
 * the SIG field set. The FDMA can generate interrupt whenever this counter
 * is incremented (see ICPU_CFG::FDMA_INTR_SIG.INTR_SIG for more
 * information).
 * This counter can be modified safely while the corresponding channel is
 * safe (see ICPU_CFG::FDMA_CH_SAFE.CH_SAFE for more information).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_CH_CNT . CH_CNT_SIG
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_CH_CNT_CH_CNT_SIG(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_CH_CNT_CH_CNT_SIG     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_CH_CNT_CH_CNT_SIG(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Injection channel token counter
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_CH_INJ_TOKEN_CNT
 *
 * @param ri Replicator: x_FDMA_CH_INJ_CNT (??), 0-7
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_CH_INJ_TOKEN_CNT(ri)  VTSS_IOREG(VTSS_TO_CFG,0xa9 + (ri))

/** 
 * \brief
 * Every time a channel activates with a DCB that has the TOKEN field set
 * this counter is decremented by one. Channels that loads a DCB with the
 * TOKEN field set cannot activate unless this counter is different from
 * zero.
 * This counter can be writen by software, or incremented automatically by
 * using the token tick counter (see ICPU_CFG::FDMA_CH_INJ_TOKEN_TICK_CNT
 * for more information). This counter can be modified safely when
 * automatic incrementing is not enabled and the corresponding injection
 * channel is in safe mode (see ICPU_CFG::FDMA_CH_INJ_TOKEN_CNT and
 * ICPU_CFG::FDMA_CH_SAFE.CH_SAFE for more information).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_CH_INJ_TOKEN_CNT . CH_INJ_TOKEN_CNT
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_CH_INJ_TOKEN_CNT_CH_INJ_TOKEN_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_CH_INJ_TOKEN_CNT_CH_INJ_TOKEN_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_CH_INJ_TOKEN_CNT_CH_INJ_TOKEN_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Injection channel token tick counter reload value
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_CH_INJ_TOKEN_TICK_RLD
 *
 * @param ri Replicator: x_FDMA_CH_INJ_CNT (??), 0-7
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_CH_INJ_TOKEN_TICK_RLD(ri)  VTSS_IOREG(VTSS_TO_CFG,0xb1 + (ri))

/** 
 * \brief
 * Automatic incrementing of the token counter is enabled by setting this
 * field different from 0. This field holds the reload value for the
 * ICPU_CFG::FDMA_CH_INJ_TOKEN_TICK_CNT.
 * Note: When changing the value of this field the same value should also
 * be written to the ICPU_CH_INJ_TOKEN_TICK_CNT field, this is needed for
 * speeding up token counter increments when changing from a high reload
 * value to a low reload value.
 *
 * \details 
 * 0: Token tick counter is disabled
 * n: Add one token every n * 200ns clock cycles
 *
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_CH_INJ_TOKEN_TICK_RLD . CH_INJ_TOKEN_TICK_RLD
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_CH_INJ_TOKEN_TICK_RLD_CH_INJ_TOKEN_TICK_RLD(x)  (x)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_CH_INJ_TOKEN_TICK_RLD_CH_INJ_TOKEN_TICK_RLD     0xffffffff
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_CH_INJ_TOKEN_TICK_RLD_CH_INJ_TOKEN_TICK_RLD(x)  (x)


/** 
 * \brief Injection channel token tick counter
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_CH_INJ_TOKEN_TICK_CNT
 *
 * @param ri Replicator: x_FDMA_CH_INJ_CNT (??), 0-7
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_CH_INJ_TOKEN_TICK_CNT(ri)  VTSS_IOREG(VTSS_TO_CFG,0xb9 + (ri))

/** 
 * \brief
 * Down-counter, when enabled by ICPU_CFG::FDMA_CH_INJ_TOKEN_TICK_RLD this
 * field is decremented by one every 200ns. When zero is reached one token
 * will be added to ICPU_CFG::FDMA_CH_INJ_TOKEN_CNT and this counted will
 * load the value from ICPU_CFG::FDMA_CH_INJ_TOKEN_TICK_RLD (subtract one
 * and continue decrementing from that value).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_CH_INJ_TOKEN_TICK_CNT . CH_INJ_TOKEN_TICK_CNT
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_CH_INJ_TOKEN_TICK_CNT_CH_INJ_TOKEN_TICK_CNT(x)  (x)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_CH_INJ_TOKEN_TICK_CNT_CH_INJ_TOKEN_TICK_CNT     0xffffffff
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_CH_INJ_TOKEN_TICK_CNT_CH_INJ_TOKEN_TICK_CNT(x)  (x)


/** 
 * \brief Error event
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_EVT_ERR
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_EVT_ERR      VTSS_IOREG(VTSS_TO_CFG,0xc1)

/** 
 * \brief
 * Shows if an Error-event has occurred, there is one bit per channel. See
 * ICPU_CFG::FDMA_EVT_ERR_CODE.EVT_ERR_CODE for description of errors for
 * which the FDMA implements run-time checks.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_EVT_ERR . EVT_ERR
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_EVT_ERR_EVT_ERR(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_EVT_ERR_EVT_ERR     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_EVT_ERR_EVT_ERR(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Additional error information
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_EVT_ERR_CODE
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_EVT_ERR_CODE  VTSS_IOREG(VTSS_TO_CFG,0xc2)

/** 
 * \brief
 * This field shows information about Error-events that has been recorded
 * by the FDMA, this can be used for software development and debugging. If
 * multiple errors happen in succession, only the newest of the err-codes
 * is shown.
 *
 * \details 
 * 0:Default (no error has occurred)
 * 1:CH_ACTIVATE set for channel w. DCB_LLP==NULL
 * 2:Got DCB w. DATAP==NULL
 * 3:Got extraction DCB w. DATAL==0
 * 4:Got extraction DCB w. DATAL<=BLOCKO
 * 5:Got injection DCB w. BLOCKL==0
 * 6:Got injection DCB w. SOF for already active channel
 * 7:Activate attempted for channel w. error indication.
 * 8:Activate attempted for channel enabled for manual mode.
 * 9:Manual mode enabled for channel in active FDMA mode.
 *
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_EVT_ERR_CODE . EVT_ERR_CODE
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_EVT_ERR_CODE_EVT_ERR_CODE(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_EVT_ERR_CODE_EVT_ERR_CODE     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_EVT_ERR_CODE_EVT_ERR_CODE(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief LLP-event
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_INTR_LLP
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_INTR_LLP     VTSS_IOREG(VTSS_TO_CFG,0xc3)

/** 
 * \brief
 * Shows if an LLP-event has occurred, there is one bit per channel. See
 * the data sheet for information on when this event can occur. 
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_INTR_LLP . INTR_LLP
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_INTR_LLP_INTR_LLP(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_INTR_LLP_INTR_LLP     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_INTR_LLP_INTR_LLP(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief LLP-event interrupt enable
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_INTR_LLP_ENA
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_INTR_LLP_ENA  VTSS_IOREG(VTSS_TO_CFG,0xc4)

/** 
 * \brief
 * Enables LLP-event to be propagated as interrupt, there is one bit per
 * channel. See ICPU_CFG::FDMA_INTR_LLP.INTR_LLP for additional
 * information.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_INTR_LLP_ENA . INTR_LLP_ENA
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_INTR_LLP_ENA_INTR_LLP_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_INTR_LLP_ENA_INTR_LLP_ENA     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_INTR_LLP_ENA_INTR_LLP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief FRM-event
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_INTR_FRM
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_INTR_FRM     VTSS_IOREG(VTSS_TO_CFG,0xc5)

/** 
 * \brief
 * Shows if a FRM-event has occurred, there is one bit per channel. See the
 * data sheet for information on when this event can occur.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_INTR_FRM . INTR_FRM
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_INTR_FRM_INTR_FRM(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_INTR_FRM_INTR_FRM     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_INTR_FRM_INTR_FRM(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief FRM-event interrupt enable
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_INTR_FRM_ENA
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_INTR_FRM_ENA  VTSS_IOREG(VTSS_TO_CFG,0xc6)

/** 
 * \brief
 * Enables FRM-event to be propagated as interrupt, there is one bit per
 * channel. See ICPU_CFG::FDMA_INTR_FRM.INTR_FRM for additional
 * information.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_INTR_FRM_ENA . INTR_FRM_ENA
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_INTR_FRM_ENA_INTR_FRM_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_INTR_FRM_ENA_INTR_FRM_ENA     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_INTR_FRM_ENA_INTR_FRM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief SIG-event
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_INTR_SIG
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_INTR_SIG     VTSS_IOREG(VTSS_TO_CFG,0xc7)

/** 
 * \brief
 * Shows if a SIG-event has occurred, there is one bit per channel. See the
 * data sheet for information on when this event can occur.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_INTR_SIG . INTR_SIG
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_INTR_SIG_INTR_SIG(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_INTR_SIG_INTR_SIG     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_INTR_SIG_INTR_SIG(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief SIG-event interrupt enable
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_INTR_SIG_ENA
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_INTR_SIG_ENA  VTSS_IOREG(VTSS_TO_CFG,0xc8)

/** 
 * \brief
 * Enables SIG-event to be propagated as interrupt, there is one bit per
 * channel. See ICPU_CFG::FDMA_INTR_SIG.INTR_SIG for additional
 * information.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_INTR_SIG_ENA . INTR_SIG_ENA
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_INTR_SIG_ENA_INTR_SIG_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_INTR_SIG_ENA_INTR_SIG_ENA     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_INTR_SIG_ENA_INTR_SIG_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Channel interrupt enable
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_INTR_ENA
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_INTR_ENA     VTSS_IOREG(VTSS_TO_CFG,0xc9)

/** 
 * \brief
 * Enables propagation of enabled channel LLP-event, FRM-event and
 * SIG-event as interrupt, there is one bit per channel. ERR-events are
 * always propagated when interrupt is enabled for a channel.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_INTR_ENA . INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_INTR_ENA_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_INTR_ENA_INTR_ENA     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_INTR_ENA_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Currently interrupting channels
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_INTR_IDENT
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_INTR_IDENT   VTSS_IOREG(VTSS_TO_CFG,0xca)

/** 
 * \brief
 * Shows currently interrupting channels, there is one bit per channel.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_INTR_IDENT . INTR_IDENT
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_INTR_IDENT_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_INTR_IDENT_INTR_IDENT     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_INTR_IDENT_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Channel specific configurations
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_CH_CFG
 *
 * @param ri Replicator: x_FDMA_CH_CNT (??), 0-9
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_CH_CFG(ri)   VTSS_IOREG(VTSS_TO_CFG,0xcb + (ri))

/** 
 * \brief
 * When this field is set the FDMA will save the STAT-word to the
 * DATAP-address instead of the DCB's STAT-word position. The DCB's DATAP
 * field will be incremented by 4 (bytes) when the DCB is loaded (the FDMA
 * will continue as if the DATAP field was DATAP+4).
 * This feature is meant to be used for channels that extract or inject
 * from PCIe mapped memory. The ICPU_CFG::FDMA_DCB_LLP_PREV field is
 * repurposed as DATAP pointer and can no longer be used when this field is
 * set.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_CH_CFG . STAT_IN_DATA_ENA
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_CH_CFG_STAT_IN_DATA_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_CH_CFG_STAT_IN_DATA_ENA  VTSS_BIT(7)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_CH_CFG_STAT_IN_DATA_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * This field is only applicable to injection channels. Use this field to
 * map the injection channel to an injection group.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_CH_CFG . CH_INJ_GRP
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_CH_CFG_CH_INJ_GRP(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_CH_CFG_CH_INJ_GRP  VTSS_BIT(6)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_CH_CFG_CH_INJ_GRP(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * The FDMA implements a strict priority scheme between all channels - both
 * injection and extraction.
 * Observe: The FDMA does not directly control the order in which ports are
 * serviced in the Queuing System. In order to adjust for this (and to
 * avoid head of line blocking) all extraction channels are automatically
 * assigned the highest priority of the extraction channels with available
 * data.
 * If multiple channels are configured with equal priorities then the
 * following strict scheme is in place: Higher channel number takes
 * priority over lower channel number. This implies that injection takes
 * priority over extraction.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_CH_CFG . CH_PRIO
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_CH_CFG_CH_PRIO(x)  VTSS_ENCODE_BITFIELD(x,2,4)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_CH_CFG_CH_PRIO     VTSS_ENCODE_BITMASK(2,4)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_CH_CFG_CH_PRIO(x)  VTSS_EXTRACT_BITFIELD(x,2,4)

/** 
 * \brief
 * Set this field to automatically disable the channel after completing any
 * DCB. The channel will disable after saving DCB status. An LLP-event will
 * be generated at the same time as the channel is disabled.
 * Be careful when using this feature, extraction channels may head-of-line
 * block other extraction channels if not immediately re-activated.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_CH_CFG . DONE_STOP_ENA
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_CH_CFG_DONE_STOP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_CH_CFG_DONE_STOP_ENA  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_CH_CFG_DONE_STOP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set this field to automatically disable the channel after completing any
 * DCB with EOF indication. The channel will disable after saving DCB
 * status. An LLP-event will be generated at the same time as the channel
 * is disabled.
 * Be careful when using this feature, extraction channels may head-of-line
 * block other extraction channels if not immediately re-activated.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_CH_CFG . DONEEOF_STOP_ENA
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_CH_CFG_DONEEOF_STOP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_CH_CFG_DONEEOF_STOP_ENA  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_CH_CFG_DONEEOF_STOP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief General FDMA configurations
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_GCFG
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_GCFG         VTSS_IOREG(VTSS_TO_CFG,0xd5)

/** 
 * \brief
 * Injection resync FIFO fill-level watermark, when exceeded backpressure
 * will be asserted towards SBA.
 * The maximum fill-level for the FIFO is reported via
 * ICPU_CFG::FDMA_GSTAT.INJ_RF_HIGH.
 *
 * \details 
 * n: backpressure when n+1 or more words in buffer.
 *
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_GCFG . INJ_RF_WM
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_GCFG_INJ_RF_WM(x)  VTSS_ENCODE_BITFIELD(x,7,5)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_GCFG_INJ_RF_WM     VTSS_ENCODE_BITMASK(7,5)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_GCFG_INJ_RF_WM(x)  VTSS_EXTRACT_BITFIELD(x,7,5)

/** 
 * \brief
 * Extraction resync fifo fill-level watermark, when exceeded backpressure
 * will be asserted towards towards QS.
 * The maximum fill-level for the fifo is reported via
 * ICPU_CFG::FDMA_GSTAT.XTR_RF_HIGH.
 * This field must not be modified at the same time as frames are extracted
 * through the FDMA.
 *
 * \details 
 * n: backpressure when n+1 or more words in buffer.
 *
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_GCFG . XTR_RF_WM
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_GCFG_XTR_RF_WM(x)  VTSS_ENCODE_BITFIELD(x,3,4)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_GCFG_XTR_RF_WM     VTSS_ENCODE_BITMASK(3,4)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_GCFG_XTR_RF_WM(x)  VTSS_EXTRACT_BITFIELD(x,3,4)

/** 
 * \brief
 * Set this field to disable extending of data available indications in the
 * extraction direction of the FDMA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_GCFG . XTR_AVAIL_EXT_DIS
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_GCFG_XTR_AVAIL_EXT_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_GCFG_XTR_AVAIL_EXT_DIS  VTSS_BIT(2)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_GCFG_XTR_AVAIL_EXT_DIS(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set this field to disable extraction group backpressure based on
 * priorities of groups that has data available.
 * By default the FDMA will assert backpressure on low priority extraction
 * channels when a higher priority channel has data available.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_GCFG . XTR_PRIO_BP_DIS
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_GCFG_XTR_PRIO_BP_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_GCFG_XTR_PRIO_BP_DIS  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_GCFG_XTR_PRIO_BP_DIS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set this field to make the FDMA ignore the value of the DCB's PD field
 * when injecting frames. By default the FDMA will treat the PD field in
 * the same way as ABORT.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_GCFG . PD_IGNORE
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_GCFG_PD_IGNORE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_GCFG_PD_IGNORE  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_GCFG_PD_IGNORE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief General FDMA status
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_GSTAT
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_GSTAT        VTSS_IOREG(VTSS_TO_CFG,0xd6)

/** 
 * \brief
 * This field shows the highest fill level that the injection resync FIFO
 * has experienced since reset of the injection logic. The depth of the
 * FIFO is 32 words, reaching a fill-level of 33 (or more) means that
 * overflow has occurred.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_GSTAT . INJ_RF_HIGH
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_GSTAT_INJ_RF_HIGH(x)  VTSS_ENCODE_BITFIELD(x,5,6)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_GSTAT_INJ_RF_HIGH     VTSS_ENCODE_BITMASK(5,6)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_GSTAT_INJ_RF_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,5,6)

/** 
 * \brief
 * This field shows the highest fill level that the extraction resync FIFO
 * has experienced since reset of the extraction logic. The depth of the
 * FIFO is 16 words, reaching a fill-level of 17 (or more) means that
 * overflow has occurred.
 * This field is read directly from other clock-domain; software must keep
 * reading this field until same value has been returned by two consecutive
 * read accesses.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_GSTAT . XTR_RF_HIGH
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_GSTAT_XTR_RF_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_GSTAT_XTR_RF_HIGH     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_GSTAT_XTR_RF_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief FDMA idle Counter
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_IDLECNT
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_IDLECNT      VTSS_IOREG(VTSS_TO_CFG,0xd7)

/** 
 * \brief
 * The counter is reset whenever a channel is enabled and when FDMA moves
 * frame data to or from the queuing system. When the FDMA is idle this
 * counter is incremented once every 200ns. The counter saturates at
 * maximum value (approx 3.3 seconds of idle time).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_IDLECNT . IDLECNT
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_IDLECNT_IDLECNT(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_IDLECNT_IDLECNT     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_IDLECNT_IDLECNT(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/** 
 * \brief Constants for this FDMA implementation.
 *
 * \details
 * Register: \a ICPU_CFG:FDMA:FDMA_CONST
 */
#define VTSS_ICPU_CFG_FDMA_FDMA_CONST        VTSS_IOREG(VTSS_TO_CFG,0xd8)

/** 
 * \brief
 * The number of injection channels.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_CONST . CH_INJ_CNT
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_CONST_CH_INJ_CNT(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_CONST_CH_INJ_CNT     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_CONST_CH_INJ_CNT(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * The number of extraction channels.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_FDMA_FDMA_CONST . CH_XTR_CNT
 */
#define  VTSS_F_ICPU_CFG_FDMA_FDMA_CONST_CH_XTR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ICPU_CFG_FDMA_FDMA_CONST_CH_XTR_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ICPU_CFG_FDMA_FDMA_CONST_CH_XTR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a ICPU_CFG:PCIE
 *
 * PCIe endpoint
 */


/** 
 * \brief PCIe endpoint control
 *
 * \details
 * Register: \a ICPU_CFG:PCIE:PCIE_CTRL
 */
#define VTSS_ICPU_CFG_PCIE_PCIE_CTRL         VTSS_IOREG(VTSS_TO_CFG,0xd9)

/** 
 * \brief
 * Set this field to send out PME from the controller, this is only
 * possible if PME is enabled in the PCIe EP core. This field is cleared
 * automatically after controller has received the request.
 * In the D3 state the controller will transmit beacon and/or assert #WAKE
 * (see ICPU_CFG::PCIEPCS_CFG.BEACON_DIS for more information).
 * In other states the link will be transitioned to L0 (when applicable)
 * and PME event will then be transmitted upsteam.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_CTRL . POWERUP
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_CTRL_POWERUP(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_CTRL_POWERUP  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_CTRL_POWERUP(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCIe endpoint configuration
 *
 * \details
 * Register: \a ICPU_CFG:PCIE:PCIE_CFG
 */
#define VTSS_ICPU_CFG_PCIE_PCIE_CFG          VTSS_IOREG(VTSS_TO_CFG,0xda)

/** 
 * \brief
 * Set to disable clock gating requests from PCIe core.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_CFG . CG_DIS
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_CFG_CG_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_CFG_CG_DIS  VTSS_BIT(5)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_CFG_CG_DIS(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Set to disable clock gating in PCIe core memories.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_CFG . MEM_CG_DIS
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_CFG_MEM_CG_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_CFG_MEM_CG_DIS  VTSS_BIT(4)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_CFG_MEM_CG_DIS(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set to defer incomming configuration requests with a Configuration
 * Request Retry Status.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_CFG . CONF_REQ_RETRY_ENA
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_CFG_CONF_REQ_RETRY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_CFG_CONF_REQ_RETRY_ENA  VTSS_BIT(3)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_CFG_CONF_REQ_RETRY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set this field to enable write of PCIe BAR masks via PCIE register
 * target. Only registers PCIE::BAR0, PCIE::BAR1, and PCIE::BAR2 may be
 * written while this field is set.
 * The minimum size for Memory and IO BARs are 64K (mask 0xFFFF). Note: The
 * low 4 bits of all BARs can be written via the PCIe target when this
 * field is not set.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_CFG . PCIE_BAR_WR_ENA
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_CFG_PCIE_BAR_WR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_CFG_PCIE_BAR_WR_ENA  VTSS_BIT(2)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_CFG_PCIE_BAR_WR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set this field to disable initliazation of the PCIe link.
 * By default the PCIe core will start up and try to acchieve link when the
 * SERDES is started, by setting this field before starting the SERDES it
 * is possible to make changes to the PCIe configruration/registers prior
 * to linking with the root complex.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_CFG . LTSSM_DIS
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_CFG_LTSSM_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_CFG_LTSSM_DIS  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_CFG_LTSSM_DIS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set to add the PCIe core memories to the RAM integrity ring.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_CFG . MEM_RING_CORE_ENA
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_CFG_MEM_RING_CORE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_CFG_MEM_RING_CORE_ENA  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_CFG_MEM_RING_CORE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCIe endpoint status
 *
 * \details
 * Register: \a ICPU_CFG:PCIE:PCIE_STAT
 */
#define VTSS_ICPU_CFG_PCIE_PCIE_STAT         VTSS_IOREG(VTSS_TO_CFG,0xdb)

/** 
 * \brief
 * Set when the PCIe outbound request interface returns a non-ok SBA reply,
 * ie. ERROR.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_STAT . SLV_ERROR_REPLY
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_STAT_SLV_ERROR_REPLY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_STAT_SLV_ERROR_REPLY  VTSS_BIT(12)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_STAT_SLV_ERROR_REPLY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * The current LTSSM state of the PCIe core.
 *
 * \details 
 * 0x00: DETECT_QUIET
 * 0x01: DETECT_ACT
 * 0x02: POLL_ACTIVE
 * 0x03: POLL_COMPLIANCE
 * 0x04: POLL_CONFIG
 * 0x05: PRE_DETECT_QUIET
 * 0x06: DETECT_WAIT
 * 0x07: CFG_LINKWD_START
 * 0x08: CFG_LINKWD_ACEPT
 * 0x09: CFG_LANENUM_WAIT
 * 0x0A: CFG_LANENUM_ACEPT
 * 0x0B: CFG_COMPLETE
 * 0x0C: CFG_IDLE
 * 0x0D: RCVRY_LOCK
 * 0x0E: RCVRY_SPEED
 * 0x0F: RCVRY_RCVRCFG
 * 0x10: RCVRY_IDLE
 * 0x20: RCVRY_EQ0
 * 0x21: RCVRY_EQ1
 * 0x22: RCVRY_EQ2
 * 0x23: RCVRY_EQ3
 * 0x11: L0
 * 0x12: L0S
 * 0x13: L123_SEND_EIDLE
 * 0x14: L1_IDLE
 * 0x15: L2_IDLE
 * 0x16: L2_WAKE
 * 0x17: DISABLED_ENTRY
 * 0x18: DISABLED_IDLE
 * 0x19: DISABLED
 * 0x1A: LPBK_ENTRY
 * 0x1B: LPBK_ACTIVE
 * 0x1C: LPBK_EXIT
 * 0x1D: LPBK_EXIT_TIMEOUT
 * 0x1E: HOT_RESET_ENTRY
 * 0x1F: HOT_RESET
 *
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_STAT . LTSSM_STATE
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_STAT_LTSSM_STATE(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_STAT_LTSSM_STATE     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_STAT_LTSSM_STATE(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Current Link State of the PCIe core.
 *
 * \details 
 * 0: L0 (or not working, check LTSSM)
 * 1: L0s
 * 2: L1
 * 3: L2
 * 4: L3
 *
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_STAT . LINK_STATE
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_STAT_LINK_STATE(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_STAT_LINK_STATE     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_STAT_LINK_STATE(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/** 
 * \brief
 * The current power managment state of the PCIe core.
 *
 * \details 
 * 0: D0
 * 1: D1
 * 2: D2
 * 3: D3
 * 4: D0-Uninitialized

 *
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_STAT . PM_STATE
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_STAT_PM_STATE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_STAT_PM_STATE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_STAT_PM_STATE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Auxiliary power configuration
 *
 * \details
 * Register: \a ICPU_CFG:PCIE:PCIE_AUX_CFG
 */
#define VTSS_ICPU_CFG_PCIE_PCIE_AUX_CFG      VTSS_IOREG(VTSS_TO_CFG,0xdc)

/** 
 * \brief
 * Set to force "detection" of PCIe auxiliary power.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_AUX_CFG . AUX_POWER_VAL
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_AUX_CFG_AUX_POWER_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_AUX_CFG_AUX_POWER_VAL  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_AUX_CFG_AUX_POWER_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCIe endpoint debug status
 *
 * \details
 * Register: \a ICPU_CFG:PCIE:PCIE_DBG_STAT
 */
#define VTSS_ICPU_CFG_PCIE_PCIE_DBG_STAT     VTSS_IOREG(VTSS_TO_CFG,0xdd)

/** 
 * \brief
 * This field is set when the PCIe receive path detects 8b10b decoder
 * errors.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_DBG_STAT . TBI_RX_CE
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_DBG_STAT_TBI_RX_CE(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_DBG_STAT_TBI_RX_CE  VTSS_BIT(14)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_DBG_STAT_TBI_RX_CE(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * This field is a sticky loss of signal indication that is set whenever
 * ICPU_CFG::PCIE_DBG_STAT.TBI_RX_SDET is low.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_DBG_STAT . TBI_RX_LOS
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_DBG_STAT_TBI_RX_LOS(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_DBG_STAT_TBI_RX_LOS  VTSS_BIT(13)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_DBG_STAT_TBI_RX_LOS(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * This field returns the TBI SDET value returned from the Serdes macro.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_DBG_STAT . TBI_RX_SDET
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_DBG_STAT_TBI_RX_SDET(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_DBG_STAT_TBI_RX_SDET  VTSS_BIT(12)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_DBG_STAT_TBI_RX_SDET(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * This field just returns the TBI DATA value returned from the Serdes
 * macro. This field is read directly from another clock domain, during
 * normal operation the value presented in this field will be garbage.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_DBG_STAT . TBI_RX_DATA
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_DBG_STAT_TBI_RX_DATA(x)  VTSS_ENCODE_BITFIELD(x,2,10)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_DBG_STAT_TBI_RX_DATA     VTSS_ENCODE_BITMASK(2,10)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_DBG_STAT_TBI_RX_DATA(x)  VTSS_EXTRACT_BITFIELD(x,2,10)

/** 
 * \brief
 * Set when the Power Management is exiting L2 state. This value is read
 * directly from other clock domain, keep reading until same value was read
 * twice in a row - then read was sucessful.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_DBG_STAT . PM_L2_EXIT
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_DBG_STAT_PM_L2_EXIT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_DBG_STAT_PM_L2_EXIT  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_DBG_STAT_PM_L2_EXIT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set when the PCIe Data Link Layer is up and ready to receive/transmit
 * packages. This value is read directly from other clock domain, keep
 * reading until same value was read twice in a row - then read was
 * sucessful.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_DBG_STAT . DATA_LINK_LAYER_UP
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_DBG_STAT_DATA_LINK_LAYER_UP(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_DBG_STAT_DATA_LINK_LAYER_UP  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_DBG_STAT_DATA_LINK_LAYER_UP(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Additional inbound reply information
 *
 * \details
 * Register: \a ICPU_CFG:PCIE:PCIEMST_REPLY_INFO
 */
#define VTSS_ICPU_CFG_PCIE_PCIEMST_REPLY_INFO  VTSS_IOREG(VTSS_TO_CFG,0xde)

/** 
 * \brief
 * This field allows additional PCIe-transaction settings in addition to
 * those provided via SBA. The settings in this register is applied to all
 * PCIe inbound accesses.
 *
 * \details 
 * [0] SBA Response with bad EOT. Cause drop of inbound response.
 * [1] EP-field.
 * [2] TD-field.
 * [4:3] Reserved, must be "01".
 *
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEMST_REPLY_INFO . MST_REPLY_INFO
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEMST_REPLY_INFO_MST_REPLY_INFO(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEMST_REPLY_INFO_MST_REPLY_INFO     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEMST_REPLY_INFO_MST_REPLY_INFO(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief BAR1 offset into SBA address space
 *
 * \details
 * Register: \a ICPU_CFG:PCIE:PCIEMST_BAR1_OFFSET
 */
#define VTSS_ICPU_CFG_PCIE_PCIEMST_BAR1_OFFSET  VTSS_IOREG(VTSS_TO_CFG,0xdf)

/** 
 * \brief
 * PCIe BAR1 is a 16MByte region that, by default maps to FLASH memory
 * space.
 * It can be reconfigured to point at an other region in SBA by using this
 * field. The upper 24 bit of the address can be overwritten by setting
 * this field. The corresponding mask-field determines which bits to
 * actually overwrite (see ICPU_CFG::PCIEMST_BAR1_MASK.BAR1_MASK), the
 * default-value of the mask field "enables" the upper 8 bit of this field.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEMST_BAR1_OFFSET . BAR1_OFFSET
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEMST_BAR1_OFFSET_BAR1_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEMST_BAR1_OFFSET_BAR1_OFFSET     VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEMST_BAR1_OFFSET_BAR1_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,8,24)


/** 
 * \brief BAR1 offset mask into SBA address space
 *
 * \details
 * Register: \a ICPU_CFG:PCIE:PCIEMST_BAR1_MASK
 */
#define VTSS_ICPU_CFG_PCIE_PCIEMST_BAR1_MASK  VTSS_IOREG(VTSS_TO_CFG,0xe0)

/** 
 * \brief
 * See ICPU_CFG::PCIEMST_BAR1_OFFSET.BAR1_OFFSET for more information.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEMST_BAR1_MASK . BAR1_MASK
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEMST_BAR1_MASK_BAR1_MASK(x)  VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEMST_BAR1_MASK_BAR1_MASK     VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEMST_BAR1_MASK_BAR1_MASK(x)  VTSS_EXTRACT_BITFIELD(x,8,24)


/** 
 * \brief BAR2 offset into SBA address space
 *
 * \details
 * Register: \a ICPU_CFG:PCIE:PCIEMST_BAR2_OFFSET
 */
#define VTSS_ICPU_CFG_PCIE_PCIEMST_BAR2_OFFSET  VTSS_IOREG(VTSS_TO_CFG,0xe1)

/** 
 * \brief
 * PCIe BAR2 is a 128MByte region that, by default maps to DDR interface.
 * It can be reconfigured to point at an other region in SBA by using this
 * field. The upper 8 bit of the address can be overwritten by setting this
 * field. The corresponding mask-field determines which bits to actually
 * overwrite (see ICPU_CFG::PCIEMST_BAR2_MASK.BAR2_MASK), the default-value
 * of the mask field "enables" the upper 5 bit of this field.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEMST_BAR2_OFFSET . BAR2_OFFSET
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEMST_BAR2_OFFSET_BAR2_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEMST_BAR2_OFFSET_BAR2_OFFSET     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEMST_BAR2_OFFSET_BAR2_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/** 
 * \brief BAR2 offset mask into SBA address space
 *
 * \details
 * Register: \a ICPU_CFG:PCIE:PCIEMST_BAR2_MASK
 */
#define VTSS_ICPU_CFG_PCIE_PCIEMST_BAR2_MASK  VTSS_IOREG(VTSS_TO_CFG,0xe2)

/** 
 * \brief
 * See ICPU_CFG::PCIEMST_BAR2_OFFSET.BAR2_OFFSET for more information.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEMST_BAR2_MASK . BAR2_MASK
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEMST_BAR2_MASK_BAR2_MASK(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEMST_BAR2_MASK_BAR2_MASK     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEMST_BAR2_MASK_BAR2_MASK(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/** 
 * \brief FDMA access into PCIe address space
 *
 * \details
 * Register: \a ICPU_CFG:PCIE:PCIESLV_FDMA
 */
#define VTSS_ICPU_CFG_PCIE_PCIESLV_FDMA      VTSS_IOREG(VTSS_TO_CFG,0xe3)

/** 
 * \brief
 * This field allows configuration of outbound PCIe-transaction TC field.
 * This is applied to all FDMA initiated outbound PCIe accesses.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIESLV_FDMA . FDMA_TC
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIESLV_FDMA_FDMA_TC(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_ICPU_CFG_PCIE_PCIESLV_FDMA_FDMA_TC     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_ICPU_CFG_PCIE_PCIESLV_FDMA_FDMA_TC(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/** 
 * \brief
 * This field allows configuration of outbound PCIe-transaction ATTR field.
 * This is applied to all FDMA initiated outbound PCIe accesses.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIESLV_FDMA . FDMA_ATTR
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIESLV_FDMA_FDMA_ATTR(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_ICPU_CFG_PCIE_PCIESLV_FDMA_FDMA_ATTR     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_ICPU_CFG_PCIE_PCIESLV_FDMA_FDMA_ATTR(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * The FDMA has access to one 1GByte region (0xC0000000 though 0xFFFFFFFF)
 * that maps accesses to PCIe interface. The value of this field is used
 * for address-bits [31:30] towards the PCIe endpoint.
 *
 * \details 
 * Set this field to 1.
 *
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIESLV_FDMA . FDMA_OFFSET
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIESLV_FDMA_FDMA_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_PCIE_PCIESLV_FDMA_FDMA_OFFSET     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_PCIE_PCIESLV_FDMA_FDMA_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief SBA access into PCIe address space
 *
 * \details
 * Register: \a ICPU_CFG:PCIE:PCIESLV_SBA
 */
#define VTSS_ICPU_CFG_PCIE_PCIESLV_SBA       VTSS_IOREG(VTSS_TO_CFG,0xe4)

/** 
 * \brief
 * This field allows configuration of outbound PCIe-transaction Byte-Enable
 * field. This is applied to all SBA (non-FDMA) initiated outbound PCIe
 * accesses.
 * This field is not used for TYPE=MRr/MWr/MRdLk accesses. Byte-enables are
 * needed in order to support Zero-byte and non-contiguous byte IO and CFG
 * transfers and Zero-byte Messages.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIESLV_SBA . SBA_BE
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_BE(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_BE     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_BE(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/** 
 * \brief
 * Reserved, must be 0.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIESLV_SBA . SBA_RESERVED1
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_RESERVED1(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_RESERVED1  VTSS_BIT(23)
#define  VTSS_X_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_RESERVED1(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * This field allows configuration of outbound PCIe-transaction MSG field.
 * This is applied to all SBA (non-FDMA) initiated outbound PCIe accesses.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIESLV_SBA . SBA_MSG_CODE
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_MSG_CODE(x)  VTSS_ENCODE_BITFIELD(x,15,8)
#define  VTSS_M_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_MSG_CODE     VTSS_ENCODE_BITMASK(15,8)
#define  VTSS_X_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_MSG_CODE(x)  VTSS_EXTRACT_BITFIELD(x,15,8)

/** 
 * \brief
 * This field allows configuration of outbound PCIe-transaction TC field.
 * This is applied to all SBA (non-FDMA) initiated outbound PCIe accesses.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIESLV_SBA . SBA_TC
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_TC(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_TC     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_TC(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/** 
 * \brief
 * This field allows configuration of outbound PCIe-transaction ATTR field.
 * This is applied to all SBA (non-FDMA) initiated outbound PCIe accesses.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIESLV_SBA . SBA_ATTR
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_ATTR(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_ATTR     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_ATTR(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * This field allows configuration of outbound PCIe-transaction TD field.
 * This is applied to all SBA (non-FDMA) initiated outbound PCIe accesses.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIESLV_SBA . SBA_TD
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_TD(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_TD  VTSS_BIT(9)
#define  VTSS_X_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_TD(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * This field allows configuration of outbound PCIe-transaction EP field.
 * This is applied to all SBA (non-FDMA) initiated outbound PCIe accesses.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIESLV_SBA . SBA_EP
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_EP(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_EP  VTSS_BIT(8)
#define  VTSS_X_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_EP(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Reserved, must be 0.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIESLV_SBA . SBA_RESERVED0
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_RESERVED0(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_RESERVED0  VTSS_BIT(7)
#define  VTSS_X_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_RESERVED0(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * This field allows configuration of outbound PCIe-transaction TYPE field.
 * This is applied to all SBA (non-FDMA) initiated outbound PCIe accesses.
 *
 * \details 
 * Encoding as defined by PCIe standard.
 *
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIESLV_SBA . SBA_TYPE
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_TYPE(x)  VTSS_ENCODE_BITFIELD(x,2,5)
#define  VTSS_M_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_TYPE     VTSS_ENCODE_BITMASK(2,5)
#define  VTSS_X_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,2,5)

/** 
 * \brief
 * SBA masters (non-FDMA) has access to one 1GByte region (0xC0000000
 * though 0xFFFFFFFF) that maps accesses to PCIe interface. The value of
 * this field is used for address-bits [31:30] towards the PCIe endpoint.
 *
 * \details 
 * Set this field to 0.
 *
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIESLV_SBA . SBA_OFFSET
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_OFFSET     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ICPU_CFG_PCIE_PCIESLV_SBA_SBA_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief PCIe PCS configuration
 *
 * \details
 * Register: \a ICPU_CFG:PCIE:PCIEPCS_CFG
 */
#define VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG       VTSS_IOREG(VTSS_TO_CFG,0xe5)

/** 
 * \brief
 * Configure receiver detection result (when requested by PCIe MAC on
 * pipe-if)
 *
 * \details 
 * 0: Receiver detected
 * 1: Receiver not detected
 *
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . TXRX_DETECT
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_TXRX_DETECT(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_TXRX_DETECT  VTSS_BIT(21)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_TXRX_DETECT(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * Set to enable contineous reset of comma-detection logic during loss of
 * rx signal. SDETCOM_DIS must be cleared for this to work.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . SDETCOM_PERM
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_SDETCOM_PERM(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_SDETCOM_PERM  VTSS_BIT(20)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_SDETCOM_PERM(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Set to disable reset of comma-detection logic when loss of rx signal is
 * "detected".
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . SDETCOM_DIS
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_SDETCOM_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_SDETCOM_DIS  VTSS_BIT(19)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_SDETCOM_DIS(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * Set this field to force beacon signal to be transmitted on serdes
 * output.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . BEACON_FORCE
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_BEACON_FORCE(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_BEACON_FORCE  VTSS_BIT(18)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_BEACON_FORCE(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Set this field to force the value of the receive reset from serdes to
 * PCS to the value of ICPU_CFG::PCIEPCS_CFG.RXRST_VAL.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . RXRST_FORCE
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_RXRST_FORCE(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_RXRST_FORCE  VTSS_BIT(17)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_RXRST_FORCE(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * See ICPU_CFG::PCIEPCS_CFG.RXRST_FORCE for more information.
 *
 * \details 
 * 0: Reset is asserted
 * 1: Reset is not asserted
 *
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . RXRST_VAL
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_RXRST_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_RXRST_VAL  VTSS_BIT(16)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_RXRST_VAL(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Set this field to force the value of the transmit reset from serdes to
 * PCS to the value of ICPU_CFG::PCIEPCS_CFG.TXRST_VAL.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . TXRST_FORCE
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_TXRST_FORCE(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_TXRST_FORCE  VTSS_BIT(15)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_TXRST_FORCE(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * See ICPU_CFG::PCIEPCS_CFG.TXRST_FORCE for more information.
 *
 * \details 
 * 0: Reset is asserted
 * 1: Reset is not asserted
 *
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . TXRST_VAL
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_TXRST_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_TXRST_VAL  VTSS_BIT(14)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_TXRST_VAL(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Set this field to invert the value of the signal-detect from serdes to
 * PCS.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . RXSDET_XOR
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_RXSDET_XOR(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_RXSDET_XOR  VTSS_BIT(13)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_RXSDET_XOR(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Set this field to force the value of the signal-detect from serdes to
 * PCS to the value of ICPU_CFG::PCIEPCS_CFG.RXSDET_XOR.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . RXSDET_FORCE
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_RXSDET_FORCE(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_RXSDET_FORCE  VTSS_BIT(12)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_RXSDET_FORCE(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Set to enable RX inversion from serdes to PCS block. This is for test
 * only, the PCS handles inversion internally when ever this is requested
 * by the PCIe MAC.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . RXINV_ENA
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_RXINV_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_RXINV_ENA  VTSS_BIT(11)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_RXINV_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Set this field to swap TBI from serdes to PCS block (crossover bit 0 to
 * 9, 1 to 8, etc.)
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . RXSWAP_ENA
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_RXSWAP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_RXSWAP_ENA  VTSS_BIT(10)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_RXSWAP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Set this field to swap TBI from PCS to serdes block (crossover bit 0 to
 * 9, 1 to 8, etc.)
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . TXSWAP_ENA
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_TXSWAP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_TXSWAP_ENA  VTSS_BIT(9)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_TXSWAP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Set this field to disable drive of constant TBI data (zeros) during IDLE
 * indication.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . IDLE_DATA_DIS
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_IDLE_DATA_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_IDLE_DATA_DIS  VTSS_BIT(8)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_IDLE_DATA_DIS(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Set this field to disable support for outband idle signalling.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . IDLE_DIS
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_IDLE_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_IDLE_DIS  VTSS_BIT(7)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_IDLE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Set this field allows skewing TBI DATA vs. IDLE signals.
 * When configured to -1 then IDLE_DATA_DIS will also need to be set, else
 * first symbol transmitted will just be 0s'.
 *
 * \details 
 * 0: No delay of IDLE.
 * 1: Delay IDLE by 1 symbol.
 * 2: Delay IDLE by 2 symbols.
 * 3: Delay IDLE by -1 symbol (is delaying data by 1 symbol).
 *
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . IDLE_DLY
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_IDLE_DLY(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_IDLE_DLY     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_IDLE_DLY(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/** 
 * \brief
 * Set this field to (always) signal receive lowpower towards the serdes.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . RXLP_FORCE
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_RXLP_FORCE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_RXLP_FORCE  VTSS_BIT(4)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_RXLP_FORCE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set this field to (always) signal transmit lowpower towards the serdes.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . TXLP_FORCE
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_TXLP_FORCE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_TXLP_FORCE  VTSS_BIT(3)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_TXLP_FORCE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Polarity of the PCIe WAKE output, WAKE is typically an active low output
 * - but if an amplifier is needed for driving a large WAKE net then
 * polarity may need to be changed.
 *
 * \details 
 * 0: Active low
 * 1: Active high
 *
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . WAKE_POL
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_WAKE_POL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_WAKE_POL  VTSS_BIT(2)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_WAKE_POL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set to permanently drive PCIe WAKE output, by default the WAKE output is
 * only driven when active and thusly allowing pull-resistor network.
 *
 * \details 
 * 0: Only drive output when active.
 * 1: Always drive output.
 *
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . WAKE_OE
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_WAKE_OE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_WAKE_OE  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_WAKE_OE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set this field to disable outband PCIe beacon signalling when attempting
 * to wake from D3. When beacon is disabled the WAKE# signal (available as
 * alternate GPIO function) must be used instead.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_CFG . BEACON_DIS
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_CFG_BEACON_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_CFG_BEACON_DIS  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_CFG_BEACON_DIS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCIe beacon parameters
 *
 * \details
 * Register: \a ICPU_CFG:PCIE:PCIEPCS_BEACON
 */
#define VTSS_ICPU_CFG_PCIE_PCIEPCS_BEACON    VTSS_IOREG(VTSS_TO_CFG,0xe6)

/** 
 * \brief
 * 10bit value to transmit during PCIe-beacon signaling, if 0x3E becaon
 * will be 250Mhz alternating signal. Special, if all-zeros PCS will
 * generate a 125MHz alternating signal.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_BEACON . BEACON_VAL
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_BEACON_BEACON_VAL(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_BEACON_BEACON_VAL     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_BEACON_BEACON_VAL(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/** 
 * \brief
 * Set to disable the BEACON_MAX_DLY feature, when set beacon will be
 * generated until reply from upsteam port is received.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_BEACON . BEACON_MAX_DIS
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_BEACON_BEACON_MAX_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_BEACON_BEACON_MAX_DIS  VTSS_BIT(15)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_BEACON_BEACON_MAX_DIS(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Set this field to the maximum number of PCIe (transmit) clock cycles for
 * which beacon may be asserted. The standard says beacon must not be
 * asserted for longer than 32 us.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIEPCS_BEACON . BEACON_MAX_DLY
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIEPCS_BEACON_BEACON_MAX_DLY(x)  VTSS_ENCODE_BITFIELD(x,0,15)
#define  VTSS_M_ICPU_CFG_PCIE_PCIEPCS_BEACON_BEACON_MAX_DLY     VTSS_ENCODE_BITMASK(0,15)
#define  VTSS_X_ICPU_CFG_PCIE_PCIEPCS_BEACON_BEACON_MAX_DLY(x)  VTSS_EXTRACT_BITFIELD(x,0,15)


/** 
 * \brief PCIe events
 *
 * \details
 * Register: \a ICPU_CFG:PCIE:PCIE_INTR
 */
#define VTSS_ICPU_CFG_PCIE_PCIE_INTR         VTSS_IOREG(VTSS_TO_CFG,0xe7)

/** 
 * \brief
 * This event is set whenever the ICPU_CFG::PCIE_STAT.LTSSM_STATE field is
 * changed.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR . INTR_LTSSM_STATE
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_INTR_LTSSM_STATE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_INTR_LTSSM_STATE  VTSS_BIT(4)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_INTR_LTSSM_STATE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * This event is set whenever the ICPU_CFG::PCIE_STAT.LINK_STATE field is
 * changed.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR . INTR_LINK_STATE
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_INTR_LINK_STATE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_INTR_LINK_STATE  VTSS_BIT(3)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_INTR_LINK_STATE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * This event is set whenever an external CPU writes to BAR1 region.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR . INTR_BAR1_WR
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_INTR_BAR1_WR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_INTR_BAR1_WR  VTSS_BIT(2)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_INTR_BAR1_WR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * This event is set whenever an external CPU reads from BAR1 region.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR . INTR_BAR1_RD
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_INTR_BAR1_RD(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_INTR_BAR1_RD  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_INTR_BAR1_RD(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * This event is set whenever the ICPU_CFG::PCIE_STAT.PM_STATE field is
 * changed.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR . INTR_PM_STATE
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_INTR_PM_STATE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_INTR_PM_STATE  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_INTR_PM_STATE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCIe interrupt enable
 *
 * \details
 * Register: \a ICPU_CFG:PCIE:PCIE_INTR_ENA
 */
#define VTSS_ICPU_CFG_PCIE_PCIE_INTR_ENA     VTSS_IOREG(VTSS_TO_CFG,0xe8)

/** 
 * \brief
 * Set to enable propagation of the LTSSM_STATE interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_ENA . INTR_LTSSM_STATE_ENA
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_ENA_INTR_LTSSM_STATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_ENA_INTR_LTSSM_STATE_ENA  VTSS_BIT(4)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_ENA_INTR_LTSSM_STATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set to enable propagation of the LINK_STATE interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_ENA . INTR_LINK_STATE_ENA
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_ENA_INTR_LINK_STATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_ENA_INTR_LINK_STATE_ENA  VTSS_BIT(3)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_ENA_INTR_LINK_STATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set to enable propagation of the BAR1_WR interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_ENA . INTR_BAR1_WR_ENA
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_ENA_INTR_BAR1_WR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_ENA_INTR_BAR1_WR_ENA  VTSS_BIT(2)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_ENA_INTR_BAR1_WR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set to enable propagation of the BAR1_RD interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_ENA . INTR_BAR1_RD_ENA
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_ENA_INTR_BAR1_RD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_ENA_INTR_BAR1_RD_ENA  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_ENA_INTR_BAR1_RD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set to enable propagation of the PM_STATE interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_ENA . INTR_PM_STATE_ENA
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_ENA_INTR_PM_STATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_ENA_INTR_PM_STATE_ENA  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_ENA_INTR_PM_STATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Currently active PCIe interrupts
 *
 * \details
 * Register: \a ICPU_CFG:PCIE:PCIE_INTR_IDENT
 */
#define VTSS_ICPU_CFG_PCIE_PCIE_INTR_IDENT   VTSS_IOREG(VTSS_TO_CFG,0xe9)

/** 
 * \brief
 * Set if the LTSSM_STATE interrupt is currently active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_IDENT . INTR_LTSSM_STATE_IDENT
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_IDENT_INTR_LTSSM_STATE_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_IDENT_INTR_LTSSM_STATE_IDENT  VTSS_BIT(4)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_IDENT_INTR_LTSSM_STATE_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set if the LINK_STATE interrupt is currently active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_IDENT . INTR_LINK_STATE_IDENT
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_IDENT_INTR_LINK_STATE_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_IDENT_INTR_LINK_STATE_IDENT  VTSS_BIT(3)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_IDENT_INTR_LINK_STATE_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set if the BAR1_WR interrupt is currently active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_IDENT . INTR_BAR1_WR_IDENT
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_IDENT_INTR_BAR1_WR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_IDENT_INTR_BAR1_WR_IDENT  VTSS_BIT(2)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_IDENT_INTR_BAR1_WR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set if the BAR1_RD interrupt is currently active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_IDENT . INTR_BAR1_RD_IDENT
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_IDENT_INTR_BAR1_RD_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_IDENT_INTR_BAR1_RD_IDENT  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_IDENT_INTR_BAR1_RD_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set if the PM_STATE interrupt is currently active.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_IDENT . INTR_PM_STATE_IDENT
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_IDENT_INTR_PM_STATE_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_IDENT_INTR_PM_STATE_IDENT  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_IDENT_INTR_PM_STATE_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCIe outbound interrupt configuration
 *
 * \details
 * Register: \a ICPU_CFG:PCIE:PCIE_INTR_COMMON_CFG
 */
#define VTSS_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG  VTSS_IOREG(VTSS_TO_CFG,0xea)

/** 
 * \brief
 * Set to disable wake-up on interrupt. By default the PCIe endpoint will
 * attempt to wake up from powerdown when a change in interrupt state is
 * detected.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG . WAKEUP_ON_INTR_DIS
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG_WAKEUP_ON_INTR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG_WAKEUP_ON_INTR_DIS  VTSS_BIT(2)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG_WAKEUP_ON_INTR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Select the external interrupt from the VCore interrupt controller that
 * must be used to generate PCIe legacy interrupt.
 *
 * \details 
 * 0: Use EXT_DST0
 * 1: Use EXT_DST1
 *
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG . LEGACY_MODE_INTR_SEL
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG_LEGACY_MODE_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG_LEGACY_MODE_INTR_SEL  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG_LEGACY_MODE_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set to enable PCIe interrupts. The PCIe endpoint's MSI Capability
 * Register Set must have been configured before enabling interrupts.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG . PCIE_INTR_ENA
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG_PCIE_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG_PCIE_INTR_ENA  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_COMMON_CFG_PCIE_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCIe outbound MSI interrupt configuration
 *
 * \details
 * Replicated per EXT_DST interrupt.
 *
 * Register: \a ICPU_CFG:PCIE:PCIE_INTR_CFG
 *
 * @param ri Register: PCIE_INTR_CFG (??), 0-1
 */
#define VTSS_ICPU_CFG_PCIE_PCIE_INTR_CFG(ri)  VTSS_IOREG(VTSS_TO_CFG,0xeb + (ri))

/** 
 * \brief
 * Reserved, must be 0.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_CFG . FUNCTION_NUMBER
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_CFG_FUNCTION_NUMBER(x)  VTSS_ENCODE_BITFIELD(x,15,3)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_CFG_FUNCTION_NUMBER     VTSS_ENCODE_BITMASK(15,3)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_CFG_FUNCTION_NUMBER(x)  VTSS_EXTRACT_BITFIELD(x,15,3)

/** 
 * \brief
 * Configure MSI interrupt traffic class for corresponding EXT_DST
 * interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_CFG . TRAFFIC_CLASS
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_CFG_TRAFFIC_CLASS(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_CFG_TRAFFIC_CLASS     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_CFG_TRAFFIC_CLASS(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/** 
 * \brief
 * Configure MSI interrupt vector for falling edge of corresponding EXT_DST
 * interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_CFG . FALLING_VECTOR_VAL
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_CFG_FALLING_VECTOR_VAL(x)  VTSS_ENCODE_BITFIELD(x,7,5)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_CFG_FALLING_VECTOR_VAL     VTSS_ENCODE_BITMASK(7,5)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_CFG_FALLING_VECTOR_VAL(x)  VTSS_EXTRACT_BITFIELD(x,7,5)

/** 
 * \brief
 * Configure MSI interrupt vector for rising edge of corresponding EXT_DST
 * interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_CFG . RISING_VECTOR_VAL
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_CFG_RISING_VECTOR_VAL(x)  VTSS_ENCODE_BITFIELD(x,2,5)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_CFG_RISING_VECTOR_VAL     VTSS_ENCODE_BITMASK(2,5)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_CFG_RISING_VECTOR_VAL(x)  VTSS_EXTRACT_BITFIELD(x,2,5)

/** 
 * \brief
 * Set to enable MSI interrupt on falling edge of corresponding EXT_DST
 * interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_CFG . INTR_FALLING_ENA
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_CFG_INTR_FALLING_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_CFG_INTR_FALLING_ENA  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_CFG_INTR_FALLING_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set to enable MSI interrupt on rising edge of corresponding EXT_DST
 * interrupt.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_CFG . INTR_RISING_ENA
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_CFG_INTR_RISING_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_CFG_INTR_RISING_ENA  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_CFG_INTR_RISING_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCIe outbound MSI interrupt status
 *
 * \details
 * Replicated per EXT_DST interrupt.
 *
 * Register: \a ICPU_CFG:PCIE:PCIE_INTR_STAT
 *
 * @param ri Register: PCIE_INTR_STAT (??), 0-1
 */
#define VTSS_ICPU_CFG_PCIE_PCIE_INTR_STAT(ri)  VTSS_IOREG(VTSS_TO_CFG,0xed + (ri))

/** 
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_STAT . INTR_PENDING_FALLING
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_STAT_INTR_PENDING_FALLING(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_STAT_INTR_PENDING_FALLING  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_STAT_INTR_PENDING_FALLING(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \details 
 * Field: ::VTSS_ICPU_CFG_PCIE_PCIE_INTR_STAT . INTR_PENDING_RISING
 */
#define  VTSS_F_ICPU_CFG_PCIE_PCIE_INTR_STAT_INTR_PENDING_RISING(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_PCIE_PCIE_INTR_STAT_INTR_PENDING_RISING  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_PCIE_PCIE_INTR_STAT_INTR_PENDING_RISING(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ICPU_CFG:MANUAL_XTRINJ
 *
 * Manual extraction and injection via FDMA
 */


/** 
 * \brief Manual extraction replicated register-array
 *
 * \details
 * Register: \a ICPU_CFG:MANUAL_XTRINJ:MANUAL_XTR
 *
 * @param ri Register: MANUAL_XTR (??), 0-4095
 */
#define VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_XTR(ri)  VTSS_IOREG(VTSS_TO_CFG,0x1000 + (ri))

/** 
 * \brief
 * Manual extraction is done by reading from this block of registers. The
 * manual extraction status word is accessed by reading the last
 * word-address in this block. Manual extraction has to be enabled via
 * ICPU_CFG::MANUAL_CFG.XTR_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_XTR . XTR
 */
#define  VTSS_F_ICPU_CFG_MANUAL_XTRINJ_MANUAL_XTR_XTR(x)  (x)
#define  VTSS_M_ICPU_CFG_MANUAL_XTRINJ_MANUAL_XTR_XTR     0xffffffff
#define  VTSS_X_ICPU_CFG_MANUAL_XTRINJ_MANUAL_XTR_XTR(x)  (x)


/** 
 * \brief Manual injection replicated register-array
 *
 * \details
 * Register: \a ICPU_CFG:MANUAL_XTRINJ:MANUAL_INJ
 *
 * @param ri Register: MANUAL_INJ (??), 0-4095
 */
#define VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INJ(ri)  VTSS_IOREG(VTSS_TO_CFG,0x2000 + (ri))

/** 
 * \brief
 * Manual injection is done by writing to this block of registers. The
 * manual injection status word is located at the first word-address in
 * this block. Manual injection has to be enabled via
 * ICPU_CFG::MANUAL_CFG.INJ_ENA.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INJ . INJ
 */
#define  VTSS_F_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INJ_INJ(x)  (x)
#define  VTSS_M_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INJ_INJ     0xffffffff
#define  VTSS_X_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INJ_INJ(x)  (x)


/** 
 * \brief Manual extraction and injection configuration
 *
 * \details
 * Register: \a ICPU_CFG:MANUAL_XTRINJ:MANUAL_CFG
 */
#define VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG  VTSS_IOREG(VTSS_TO_CFG,0x3000)

/** 
 * \brief
 * Set to disable flushing/abort mechanism when manual extraction is
 * enabled via ICPU_CFG::MANUAL_CFG.XTR_ENA. When manually extracting via
 * 8051 SFR registers this field must be set.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG . XTR_FLUSH_DIS
 */
#define  VTSS_F_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG_XTR_FLUSH_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG_XTR_FLUSH_DIS  VTSS_BIT(4)
#define  VTSS_X_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG_XTR_FLUSH_DIS(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set to swap endianess of data injected to the MANUAL_INJ region. The
 * manual injection status word is never swapped.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG . INJ_SWAP_ENA
 */
#define  VTSS_F_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG_INJ_SWAP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG_INJ_SWAP_ENA  VTSS_BIT(3)
#define  VTSS_X_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG_INJ_SWAP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set to byte-swap endianess of data extracted from the MANUAL_XTR region.
 * The manual extraction status word is never swapped.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG . XTR_SWAP_ENA
 */
#define  VTSS_F_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG_XTR_SWAP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG_XTR_SWAP_ENA  VTSS_BIT(2)
#define  VTSS_X_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG_XTR_SWAP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set to enable manual injection by using FDMA channel number 9. When
 * manual injection is enabled; the FDMA cannot be used for regular FDMA
 * injection operations (on any injection channel).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG . INJ_ENA
 */
#define  VTSS_F_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG_INJ_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG_INJ_ENA  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG_INJ_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set to enable manual extraction by using FDMA channel number 1. When
 * manual extraction is enabled; the FDMA cannot be used for regular FDMA
 * extraction operations (on any extraction channel).
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG . XTR_ENA
 */
#define  VTSS_F_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG_XTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG_XTR_ENA  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_MANUAL_XTRINJ_MANUAL_CFG_XTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Manual extraction and injection interrupt indications
 *
 * \details
 * Register: \a ICPU_CFG:MANUAL_XTRINJ:MANUAL_INTR
 */
#define VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR  VTSS_IOREG(VTSS_TO_CFG,0x3001)

/** 
 * \brief
 * Set when there is room for more injection data-words in injection fifo.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR . INTR_INJ_RDY
 */
#define  VTSS_F_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_INTR_INJ_RDY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_INTR_INJ_RDY  VTSS_BIT(2)
#define  VTSS_X_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_INTR_INJ_RDY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set when any extraction word is ready for extraction.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR . INTR_XTR_ANY_RDY
 */
#define  VTSS_F_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_INTR_XTR_ANY_RDY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_INTR_XTR_ANY_RDY  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_INTR_XTR_ANY_RDY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set when there is an extraction word containing SOF ready for
 * extraction.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR . INTR_XTR_SOF_RDY
 */
#define  VTSS_F_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_INTR_XTR_SOF_RDY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_INTR_XTR_SOF_RDY  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_INTR_XTR_SOF_RDY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Manual extraction and injection interrupt enables
 *
 * \details
 * Register: \a ICPU_CFG:MANUAL_XTRINJ:MANUAL_INTR_ENA
 */
#define VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_ENA  VTSS_IOREG(VTSS_TO_CFG,0x3002)

/** 
 * \brief
 * Set to enable FDMA interrupt while there is room for more injection
 * data. This interrupt is asserted for as long as there is free space in
 * the injection buffers.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_ENA . INTR_INJ_RDY_ENA
 */
#define  VTSS_F_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_ENA_INTR_INJ_RDY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_ENA_INTR_INJ_RDY_ENA  VTSS_BIT(2)
#define  VTSS_X_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_ENA_INTR_INJ_RDY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set to enable FDMA interrupt while any data is ready for manual
 * extraction. This interrupt is asserted for as long as there is data
 * ready in the extraction buffer.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_ENA . INTR_XTR_ANY_RDY_ENA
 */
#define  VTSS_F_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_ENA_INTR_XTR_ANY_RDY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_ENA_INTR_XTR_ANY_RDY_ENA  VTSS_BIT(1)
#define  VTSS_X_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_ENA_INTR_XTR_ANY_RDY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set to enable FDMA interrupt when a new frame is waiting to be
 * extracted. This event is asserted when a frame-word with sof set is
 * waiting to be extracted. If a previous frame is only partially extracted
 * then no interrupt will be generated until the previous frame is
 * completely extracted.
 *
 * \details 
 * Field: ::VTSS_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_ENA . INTR_XTR_SOF_RDY_ENA
 */
#define  VTSS_F_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_ENA_INTR_XTR_SOF_RDY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_ENA_INTR_XTR_SOF_RDY_ENA  VTSS_BIT(0)
#define  VTSS_X_ICPU_CFG_MANUAL_XTRINJ_MANUAL_INTR_ENA_INTR_XTR_SOF_RDY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_SERVALT_REGS_ICPU_CFG_H_ */
