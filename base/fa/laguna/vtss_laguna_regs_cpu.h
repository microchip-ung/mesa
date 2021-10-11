// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_CPU_H_
#define _VTSS_LAGUNA_REGS_CPU_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a CPU
 *
 * CPU system registers.
 *
 ***********************************************************************/

/**
 * Register Group: \a CPU:CPU_REGS
 *
 * Not documented
 */


/**
 * \brief General Purpose Register
 *
 * \details
 * Register: \a CPU:CPU_REGS:GPR
 *
 * @param ri Register: GPR (??), 0-31
 */
#define VTSS_CPU_GPR(ri)                     VTSS_IOREG(VTSS_TO_CPU,0x0 + (ri))

/**
 * \brief
 * General purpose 32-bit registers for software development and
 * debug.Note: This register is only reset by the device's reset input,
 * i.e. it is not affected by soft reset!
 *
 * \details
 * Field: ::VTSS_CPU_GPR . GPR
 */
#define  VTSS_F_CPU_GPR_GPR(x)                (x)
#define  VTSS_M_CPU_GPR_GPR                   0xffffffff
#define  VTSS_X_CPU_GPR_GPR(x)                (x)


/**
 * \brief FPGA drop identifier
 *
 * \details
 * Register: \a CPU:CPU_REGS:BUILDID
 */
#define VTSS_CPU_BUILDID                     VTSS_IOREG(VTSS_TO_CPU,0x20)

/**
 * \details
 * Field: ::VTSS_CPU_BUILDID . BUILDID
 */
#define  VTSS_F_CPU_BUILDID_BUILDID(x)        (x)
#define  VTSS_M_CPU_BUILDID_BUILDID           0xffffffff
#define  VTSS_X_CPU_BUILDID_BUILDID(x)        (x)


/**
 * \brief Reset Settings
 *
 * \details
 * Register: \a CPU:CPU_REGS:RESET
 */
#define VTSS_CPU_RESET                       VTSS_IOREG(VTSS_TO_CPU,0x21)

/**
 * \brief
 * Set this field to generate a soft reset for the VCore. This field will
 * be cleared when the reset has taken effect.It is possible to protect the
 * blocks of vcore system with protection bits.
 *
 * \details
 * 0: VCore is not reset
 * 1: Initiate soft reset of the VCore and the reset will get cleared after
 * the reset process is done.
 *
 * Field: ::VTSS_CPU_RESET . VCORE_RST
 */
#define  VTSS_F_CPU_RESET_VCORE_RST(x)        VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_CPU_RESET_VCORE_RST           VTSS_BIT(7)
#define  VTSS_X_CPU_RESET_VCORE_RST(x)        VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * This register performs warm reset of Core 0 of ARM Processor inside
 * Vcore system.Self clearing field at the end of warm reset.
 *
 * \details
 * 0 - Normal operation
 * 1 - Perform warm reset of core 0 (Self clears at the end of reset).
 *
 * Field: ::VTSS_CPU_RESET . CPU_CORE_0_WARM_RST
 */
#define  VTSS_F_CPU_RESET_CPU_CORE_0_WARM_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_CPU_RESET_CPU_CORE_0_WARM_RST  VTSS_BIT(6)
#define  VTSS_X_CPU_RESET_CPU_CORE_0_WARM_RST(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * This single, cluster-wide field resets the integrated CoreSight
 * components that connect to the external PCLK domain, such as debug
 * logic.
 *
 * \details
 * 0 - No reset to debug interface due to this register.
 * 1 - Reset applied to debug interface due to this register.
 *
 * Field: ::VTSS_CPU_RESET . PROC_DBG_RST
 */
#define  VTSS_F_CPU_RESET_PROC_DBG_RST(x)     VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_CPU_RESET_PROC_DBG_RST        VTSS_BIT(5)
#define  VTSS_X_CPU_RESET_PROC_DBG_RST(x)     VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Force reset the TAP controller of the CPU.
 *
 * \details
 * 1: Reset asserted
 * 0: Reset de-asserted
 *
 * Field: ::VTSS_CPU_RESET . JTAG_RST
 */
#define  VTSS_F_CPU_RESET_JTAG_RST(x)         VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CPU_RESET_JTAG_RST            VTSS_BIT(4)
#define  VTSS_X_CPU_RESET_JTAG_RST(x)         VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * This field resets the L2 cache in CPU of VCORE to be in reset.This block
 * auto-clears when reset of L2 is complete.
 *
 * \details
 * 1 - Put the CPU L2 cache in reset.
 * 0 - CPU L2 cache is not in reset.
 *
 * Field: ::VTSS_CPU_RESET . CPU_L2_RST
 */
#define  VTSS_F_CPU_RESET_CPU_L2_RST(x)       VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_RESET_CPU_L2_RST          VTSS_BIT(3)
#define  VTSS_X_CPU_RESET_CPU_L2_RST(x)       VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * This field resets the DDR Memory in the Vcore Sub-system.
 *
 * \details
 * 1 - DDR Memory is in reset.
 * 0 - DDR Memory is not in reset.
 *
 * Field: ::VTSS_CPU_RESET . MEM_RST
 */
#define  VTSS_F_CPU_RESET_MEM_RST(x)          VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_RESET_MEM_RST             VTSS_BIT(2)
#define  VTSS_X_CPU_RESET_MEM_RST(x)          VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * This field forces the WDT block in APB into reset.
 *
 * \details
 * 1 - Force WDT into Reset.
 * 0 - Bring WDT out of reset.
 *
 * Field: ::VTSS_CPU_RESET . WDT_FORCE_RST
 */
#define  VTSS_F_CPU_RESET_WDT_FORCE_RST(x)    VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_RESET_WDT_FORCE_RST       VTSS_BIT(1)
#define  VTSS_X_CPU_RESET_WDT_FORCE_RST(x)    VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * This field performs a cold reset (includes debug logic of core 0) of CPU
 * Core 0.
 *
 * \details
 * 1 -	Core 0 of CPU is in cold reset
 * 0  - Core 0 of CPU is not in cold reset
 *
 * Field: ::VTSS_CPU_RESET . CPU_CORE_0_COLD_RST
 */
#define  VTSS_F_CPU_RESET_CPU_CORE_0_COLD_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_RESET_CPU_CORE_0_COLD_RST  VTSS_BIT(0)
#define  VTSS_X_CPU_RESET_CPU_CORE_0_COLD_RST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief This register contains fields that protect certain blocks from resets.
 *
 * \details
 * Register: \a CPU:CPU_REGS:RESET_PROT_STAT
 */
#define VTSS_CPU_RESET_PROT_STAT             VTSS_IOREG(VTSS_TO_CPU,0x22)

/**
 * \brief
 * This field protects the VCORE from System reset.
 *
 * \details
 * 0: System reset also causes VCore to go into reset.
 * 1: Vcore is protected from System Reset.
 *
 * Field: ::VTSS_CPU_RESET_PROT_STAT . SYS_RST_PROT_VCORE
 */
#define  VTSS_F_CPU_RESET_PROT_STAT_SYS_RST_PROT_VCORE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_CPU_RESET_PROT_STAT_SYS_RST_PROT_VCORE  VTSS_BIT(5)
#define  VTSS_X_CPU_RESET_PROT_STAT_SYS_RST_PROT_VCORE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * This field protects AMBA from Vcore Reset, WDT reset.This field also
 * protects AXI from VCORE_RST_FORCE (that comes from GCB target)
 *
 * \details
 * 0: No Protection is applied to AMBA
 * 1: AMBA is protected from Vcore Reset and Watch dog Timeout reset.
 *
 * Field: ::VTSS_CPU_RESET_PROT_STAT . VCORE_RST_PROT_AMBA
 */
#define  VTSS_F_CPU_RESET_PROT_STAT_VCORE_RST_PROT_AMBA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CPU_RESET_PROT_STAT_VCORE_RST_PROT_AMBA  VTSS_BIT(4)
#define  VTSS_X_CPU_RESET_PROT_STAT_VCORE_RST_PROT_AMBA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Set this field to protect Watch dog Timer from Watch dog Timeout reset
 * and Vcore Soft Reset (VCORE_RST Register).
 *
 * \details
 * 0: No reset protection to Watch Dog Timer block.
 * 1: WDT block is protected from VCORE Soft Reset and its own timeout.
 *
 * Field: ::VTSS_CPU_RESET_PROT_STAT . VCORE_RST_PROT_WDT
 */
#define  VTSS_F_CPU_RESET_PROT_STAT_VCORE_RST_PROT_WDT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_RESET_PROT_STAT_VCORE_RST_PROT_WDT  VTSS_BIT(3)
#define  VTSS_X_CPU_RESET_PROT_STAT_VCORE_RST_PROT_WDT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * This field protects the Watch-dog timer block in the vcore-system from
 * its own timeout.
 *
 * \details
 * 1 - Protect the Vcore's WDT from its own timeout.
 * 0 - resets the WDT block as well from VCORE's Watch-dog timer timeout.
 *
 * Field: ::VTSS_CPU_RESET_PROT_STAT . VCORE_WDT_RST_PROT_WDT
 */
#define  VTSS_F_CPU_RESET_PROT_STAT_VCORE_WDT_RST_PROT_WDT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_RESET_PROT_STAT_VCORE_WDT_RST_PROT_WDT  VTSS_BIT(2)
#define  VTSS_X_CPU_RESET_PROT_STAT_VCORE_WDT_RST_PROT_WDT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * This register contains the status indication to indicate that VCORE has
 * been reset because of WDT.
 *
 * \details
 * 0 : Watch dog timer timeout is not the cause for Vcore Reset.
 * 1 : Watch dog timer timeout is the cause for vcore reset.
 *
 * Field: ::VTSS_CPU_RESET_PROT_STAT . VCORE_WDT_RST_STAT
 */
#define  VTSS_F_CPU_RESET_PROT_STAT_VCORE_WDT_RST_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_RESET_PROT_STAT_VCORE_WDT_RST_STAT  VTSS_BIT(1)
#define  VTSS_X_CPU_RESET_PROT_STAT_VCORE_WDT_RST_STAT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * This field protects the PCIe controller from a Vcore reset.
 *
 * \details
 * 0: Not protected
 * 1: Protected
 *
 * Field: ::VTSS_CPU_RESET_PROT_STAT . VCORE_RST_PROT_PCIE
 */
#define  VTSS_F_CPU_RESET_PROT_STAT_VCORE_RST_PROT_PCIE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_RESET_PROT_STAT_VCORE_RST_PROT_PCIE  VTSS_BIT(0)
#define  VTSS_X_CPU_RESET_PROT_STAT_VCORE_RST_PROT_PCIE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief General control
 *
 * \details
 * Register: \a CPU:CPU_REGS:GENERAL_CTRL
 */
#define VTSS_CPU_GENERAL_CTRL                VTSS_IOREG(VTSS_TO_CPU,0x23)

/**
 * \brief
 * The default value of this field depends on strapping of the VCore.Set
 * this field to enable the MIIM target-interface on the GPIOs.
 *
 * \details
 * Field: ::VTSS_CPU_GENERAL_CTRL . IF_MIIM_SLV_ENA
 */
#define  VTSS_F_CPU_GENERAL_CTRL_IF_MIIM_SLV_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_GENERAL_CTRL_IF_MIIM_SLV_ENA  VTSS_BIT(2)
#define  VTSS_X_CPU_GENERAL_CTRL_IF_MIIM_SLV_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Set this field to disable the ARM processor in the Vcore-system.
 *
 * \details
 * 0 : ARM Processor in the vcore-system is enabled.
 * 1 : ARM Processor in the vcore-system is disabled.
 *
 * Field: ::VTSS_CPU_GENERAL_CTRL . VCORE_CPU_DIS
 */
#define  VTSS_F_CPU_GENERAL_CTRL_VCORE_CPU_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_GENERAL_CTRL_VCORE_CPU_DIS  VTSS_BIT(1)
#define  VTSS_X_CPU_GENERAL_CTRL_VCORE_CPU_DIS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * The default value of this field depends on strapping of the VCore.
 * Select the owner of the dedicated SI interface. Note, if the SI target
 * is not owner of this interface, it is not possible for an external CPU
 * to access registers in the chip via the dedicated SI interface.
 *
 * \details
 * 0: SI Target
 * 1: QSPI0
 *
 * Field: ::VTSS_CPU_GENERAL_CTRL . IF_SI_OWNER
 */
#define  VTSS_F_CPU_GENERAL_CTRL_IF_SI_OWNER(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_GENERAL_CTRL_IF_SI_OWNER  VTSS_BIT(0)
#define  VTSS_X_CPU_GENERAL_CTRL_IF_SI_OWNER(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief General Status
 *
 * \details
 * Register: \a CPU:CPU_REGS:GENERAL_STAT
 */
#define VTSS_CPU_GENERAL_STAT                VTSS_IOREG(VTSS_TO_CPU,0x24)

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
 * Field: ::VTSS_CPU_GENERAL_STAT . REG_IF_ERR
 */
#define  VTSS_F_CPU_GENERAL_STAT_REG_IF_ERR(x)  VTSS_ENCODE_BITFIELD(x,7,3)
#define  VTSS_M_CPU_GENERAL_STAT_REG_IF_ERR     VTSS_ENCODE_BITMASK(7,3)
#define  VTSS_X_CPU_GENERAL_STAT_REG_IF_ERR(x)  VTSS_EXTRACT_BITFIELD(x,7,3)

/**
 * \brief
 * Debug information for checking register read/write problems. This is a
 * read-only field which can only be cleared by reset of the SwC System.
 *
 * \details
 * 0: No errors detected.
 * 1: Non-32bit access, access has been discarded, read returns 0x8888 or
 * 0x88.
 * 2: Reserved.
 * 3: Registers reported error, check DEVCPU_ORG::ERR_CNTS for error, read
 * returns 0x88888888.
 *
 * Field: ::VTSS_CPU_GENERAL_STAT . CSR_REG_IF_ERR
 */
#define  VTSS_F_CPU_GENERAL_STAT_CSR_REG_IF_ERR(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_CPU_GENERAL_STAT_CSR_REG_IF_ERR     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_CPU_GENERAL_STAT_CSR_REG_IF_ERR(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \details
 * Field: ::VTSS_CPU_GENERAL_STAT . VCORE_CFG
 */
#define  VTSS_F_CPU_GENERAL_STAT_VCORE_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CPU_GENERAL_STAT_VCORE_CFG     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CPU_GENERAL_STAT_VCORE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief OTP memory status
 *
 * \details
 * Register: \a CPU:CPU_REGS:OTP_STAT
 */
#define VTSS_CPU_OTP_STAT                    VTSS_IOREG(VTSS_TO_CPU,0x25)

/**
 * \brief
 * OTP memory program status.
 *
 * \details
 * 1: Programmed
 * 0: Not programmed
 *
 * Field: ::VTSS_CPU_OTP_STAT . OTP_PROGRAMMED
 */
#define  VTSS_F_CPU_OTP_STAT_OTP_PROGRAMMED(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CPU_OTP_STAT_OTP_PROGRAMMED   VTSS_BIT(4)
#define  VTSS_X_CPU_OTP_STAT_OTP_PROGRAMMED(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * CPU disabled.
 *
 * \details
 * 0: CPU enabled
 * 1: CPU disabled
 *
 * Field: ::VTSS_CPU_OTP_STAT . OTP_CPU_DISABLED
 */
#define  VTSS_F_CPU_OTP_STAT_OTP_CPU_DISABLED(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_OTP_STAT_OTP_CPU_DISABLED  VTSS_BIT(3)
#define  VTSS_X_CPU_OTP_STAT_OTP_CPU_DISABLED(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * CPU debug access disabled.
 *
 * \details
 * 0: Enabled
 * 1: Disabled
 *
 * Field: ::VTSS_CPU_OTP_STAT . OTP_CPU_DBG_DISABLED
 */
#define  VTSS_F_CPU_OTP_STAT_OTP_CPU_DBG_DISABLED(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_OTP_STAT_OTP_CPU_DBG_DISABLED  VTSS_BIT(2)
#define  VTSS_X_CPU_OTP_STAT_OTP_CPU_DBG_DISABLED(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * CPU secure debug access disabled.
 *
 * \details
 * 0: Enabled
 * 1: Disabled
 *
 * Field: ::VTSS_CPU_OTP_STAT . OTP_CPU_SEC_DBG_DISABLED
 */
#define  VTSS_F_CPU_OTP_STAT_OTP_CPU_SEC_DBG_DISABLED(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_OTP_STAT_OTP_CPU_SEC_DBG_DISABLED  VTSS_BIT(1)
#define  VTSS_X_CPU_OTP_STAT_OTP_CPU_SEC_DBG_DISABLED(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * CAN disabled from OTP.
 *
 * \details
 * 0: Enabled
 * 1: Disabled
 *
 * Field: ::VTSS_CPU_OTP_STAT . OTP_CAN_DISABLED
 */
#define  VTSS_F_CPU_OTP_STAT_OTP_CAN_DISABLED(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_OTP_STAT_OTP_CAN_DISABLED  VTSS_BIT(0)
#define  VTSS_X_CPU_OTP_STAT_OTP_CAN_DISABLED(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Enable debug options for CPU
 *
 * \details
 * Register: \a CPU:CPU_REGS:CPU_DBG
 */
#define VTSS_CPU_CPU_DBG                     VTSS_IOREG(VTSS_TO_CPU,0x26)

/**
 * \brief
 * Enable Protection Debug bit.
 *
 * \details
 * Field: ::VTSS_CPU_CPU_DBG . ENABLE_PROT_DEBUG_BIT
 */
#define  VTSS_F_CPU_CPU_DBG_ENABLE_PROT_DEBUG_BIT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_CPU_CPU_DBG_ENABLE_PROT_DEBUG_BIT  VTSS_BIT(5)
#define  VTSS_X_CPU_CPU_DBG_ENABLE_PROT_DEBUG_BIT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Debug enable.
 *
 * \details
 * Field: ::VTSS_CPU_CPU_DBG . DBGEN
 */
#define  VTSS_F_CPU_CPU_DBG_DBGEN(x)          VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CPU_CPU_DBG_DBGEN             VTSS_BIT(4)
#define  VTSS_X_CPU_CPU_DBG_DBGEN(x)          VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Secure privileged invasive debug enable.
 *
 * \details
 * Field: ::VTSS_CPU_CPU_DBG . SPIDEN
 */
#define  VTSS_F_CPU_CPU_DBG_SPIDEN(x)         VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_CPU_DBG_SPIDEN            VTSS_BIT(3)
#define  VTSS_X_CPU_CPU_DBG_SPIDEN(x)         VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Non-invasive debug enable.
 *
 * \details
 * Field: ::VTSS_CPU_CPU_DBG . NIDEN
 */
#define  VTSS_F_CPU_CPU_DBG_NIDEN(x)          VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_CPU_DBG_NIDEN             VTSS_BIT(2)
#define  VTSS_X_CPU_CPU_DBG_NIDEN(x)          VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Secure privileged non-invasive debug enable.
 *
 * \details
 * Field: ::VTSS_CPU_CPU_DBG . SPNIDEN
 */
#define  VTSS_F_CPU_CPU_DBG_SPNIDEN(x)        VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_CPU_DBG_SPNIDEN           VTSS_BIT(1)
#define  VTSS_X_CPU_CPU_DBG_SPNIDEN(x)        VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * This field indicates that the CPU is in debug mode.
 *
 * \details
 * 0: CPU not in debug mode
 * 1: CPU in debug mode
 *
 * Field: ::VTSS_CPU_CPU_DBG . CORE_IN_DBG
 */
#define  VTSS_F_CPU_CPU_DBG_CORE_IN_DBG(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_CPU_DBG_CORE_IN_DBG       VTSS_BIT(0)
#define  VTSS_X_CPU_CPU_DBG_CORE_IN_DBG(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configures endianness towards CPU system and CSR registers.
 *
 * \details
 * Register: \a CPU:CPU_REGS:ENDIANNESS
 */
#define VTSS_CPU_ENDIANNESS                  VTSS_IOREG(VTSS_TO_CPU,0x27)

/**
 * \brief
 * This register is constructed so that it can always be written correctly
 * no matter the current state of the interface. When initializing this
 * interface, then this is the first register that must be written if the
 * desired endianness is different than the default. When writing a 1-bit
 * value to this field construct a 32-bit data-word as follows: a) copy the
 * 1-bit value into bits 0, 7, 8, 15, 16, 23, 24 and 31.Example: To write
 * the value 1 to this field, the 32-bit data-word to write is
 * "0x81818181".To write 0 just write "0x00000000".
 *
 * \details
 * Field: ::VTSS_CPU_ENDIANNESS . REG_IF_BIGENDIAN
 */
#define  VTSS_F_CPU_ENDIANNESS_REG_IF_BIGENDIAN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_ENDIANNESS_REG_IF_BIGENDIAN  VTSS_BIT(0)
#define  VTSS_X_CPU_ENDIANNESS_REG_IF_BIGENDIAN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Register containing control configuration of Processor
 *
 * \details
 * Register: \a CPU:CPU_REGS:PROC_CTRL
 */
#define VTSS_CPU_PROC_CTRL                   VTSS_IOREG(VTSS_TO_CPU,0x28)

/**
 * \brief
 * This configuration controls whether the processor runs in 64-Bit mode of
 * Architecture or 32-bit mode of architecture.By default, the processor
 * runs in 64-bit architectural mode.Note that this field is to be changed
 * only when the processor is in cold reset.
 *
 * \details
 * 0 - 32-bit arch mode is enabled.
 * 1 - 64-bit arch mode is enabled.
 *
 * Field: ::VTSS_CPU_PROC_CTRL . AARCH64_MODE_ENA
 */
#define  VTSS_F_CPU_PROC_CTRL_AARCH64_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_CPU_PROC_CTRL_AARCH64_MODE_ENA  VTSS_BIT(8)
#define  VTSS_X_CPU_PROC_CTRL_AARCH64_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Disable Automatic L2 cache invalidate on reset.Only change this register
 * when the processor is in reset state.
 *
 * \details
 * '1' - Disable automatic invalidation of L2 cache on reset.
 * '0' - Enable automatic invalidation of L2 cache on reset.
 *
 * Field: ::VTSS_CPU_PROC_CTRL . L2_RST_INVALIDATE_DIS
 */
#define  VTSS_F_CPU_PROC_CTRL_L2_RST_INVALIDATE_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_CPU_PROC_CTRL_L2_RST_INVALIDATE_DIS  VTSS_BIT(7)
#define  VTSS_X_CPU_PROC_CTRL_L2_RST_INVALIDATE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Disable L1 data cache automatic invalidate on reset functionality.This
 * register is sampled only during reset of the processor.
 *
 * \details
 * 0 - Enable automatic invalidation of L1 data cache on reset.
 * 1 - Disable automatic invalidation of L1 data cache on reset.
 *
 * Field: ::VTSS_CPU_PROC_CTRL . L1_RST_INVALIDATE_DIS
 */
#define  VTSS_F_CPU_PROC_CTRL_L1_RST_INVALIDATE_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_CPU_PROC_CTRL_L1_RST_INVALIDATE_DIS  VTSS_BIT(6)
#define  VTSS_X_CPU_PROC_CTRL_L1_RST_INVALIDATE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Endianness configuration for exception handling.This register is sampled
 * only out of processor's reset.
 *
 * \details
 * 0 - Little Endian data during exception handling.
 * 1 - Big Endian data during exception handling

 *
 * Field: ::VTSS_CPU_PROC_CTRL . BE_EXCEP_MODE
 */
#define  VTSS_F_CPU_PROC_CTRL_BE_EXCEP_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_CPU_PROC_CTRL_BE_EXCEP_MODE   VTSS_BIT(5)
#define  VTSS_X_CPU_PROC_CTRL_BE_EXCEP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Location of the exception vectors at reset. It sets the initial value of
 * the V bit in the SCTLR and HSCTLR registers.This register is sampled
 * only during reset of both the cores.
 *
 * \details
 * 0 - Exception vectors start at address 0x00000000
 * 1 - Exception vectors start at address 0xFFFF0000
 *
 * Field: ::VTSS_CPU_PROC_CTRL . VINITHI
 */
#define  VTSS_F_CPU_PROC_CTRL_VINITHI(x)      VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CPU_PROC_CTRL_VINITHI         VTSS_BIT(4)
#define  VTSS_X_CPU_PROC_CTRL_VINITHI(x)      VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable T32 exceptions. It sets the initial value of the TE bit in the
 * SCTLR and HSCTLR registers.This register is sampled only out of
 * processors reset.
 *
 * \details
 * 0 - Enables ARM Instruction set for exception handling
 * 1 - Enable Thumb instruction set for exception handling.
 *
 * Field: ::VTSS_CPU_PROC_CTRL . CFGTE
 */
#define  VTSS_F_CPU_PROC_CTRL_CFGTE(x)        VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_PROC_CTRL_CFGTE           VTSS_BIT(3)
#define  VTSS_X_CPU_PROC_CTRL_CFGTE(x)        VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Disable write access to some secure CP15 registers.
 *
 * \details
 * 0 - Enable access to all CP15 registers.
 * 1 - Disable access to some secure CP15 registers.
 *
 * Field: ::VTSS_CPU_PROC_CTRL . CP15S_DISABLE
 */
#define  VTSS_F_CPU_PROC_CTRL_CP15S_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_PROC_CTRL_CP15S_DISABLE   VTSS_BIT(2)
#define  VTSS_X_CPU_PROC_CTRL_CP15S_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * This register disables the cryptography extensions of individual core of
 * the processor.This register is sampled only during the reset of the
 * processor. Hence change this register only when processor is in reset.
 *
 * \details
 * 0 - Crypto logic in both the cores is enabled.
 * 1 - Crypto logic in both the cores is disabled.
 *
 * Field: ::VTSS_CPU_PROC_CTRL . PROC_CRYPTO_DISABLE
 */
#define  VTSS_F_CPU_PROC_CTRL_PROC_CRYPTO_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_PROC_CTRL_PROC_CRYPTO_DISABLE  VTSS_BIT(1)
#define  VTSS_X_CPU_PROC_CTRL_PROC_CRYPTO_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Flush L2 to memory.
 *
 * \details
 * Field: ::VTSS_CPU_PROC_CTRL . L2_FLUSH_REQ
 */
#define  VTSS_F_CPU_PROC_CTRL_L2_FLUSH_REQ(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PROC_CTRL_L2_FLUSH_REQ    VTSS_BIT(0)
#define  VTSS_X_CPU_PROC_CTRL_L2_FLUSH_REQ(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Status indications from various blocks in processor
 *
 * \details
 * Register: \a CPU:CPU_REGS:PROC_STAT
 */
#define VTSS_CPU_PROC_STAT                   VTSS_IOREG(VTSS_TO_CPU,0x29)

/**
 * \brief
 * Indicates whether the SWJ-DP in DAP-Lite module is in JTAG Mode or in
 * SWD Mode.
 *
 * \details
 * '1' - SWJ-DP is in JTAG Mode
 * '0' - SWJ-DP is in SWD Mode
 *
 * Field: ::VTSS_CPU_PROC_STAT . DAP_JTAG_SW_MODE
 */
#define  VTSS_F_CPU_PROC_STAT_DAP_JTAG_SW_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_PROC_STAT_DAP_JTAG_SW_MODE  VTSS_BIT(3)
#define  VTSS_X_CPU_PROC_STAT_DAP_JTAG_SW_MODE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Wait-for-interrupt status.
 *
 * \details
 * Field: ::VTSS_CPU_PROC_STAT . WFI
 */
#define  VTSS_F_CPU_PROC_STAT_WFI(x)          VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_PROC_STAT_WFI             VTSS_BIT(2)
#define  VTSS_X_CPU_PROC_STAT_WFI(x)          VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Wait-for-interrupt status of L2 system.
 *
 * \details
 * Field: ::VTSS_CPU_PROC_STAT . WFIL2
 */
#define  VTSS_F_CPU_PROC_STAT_WFIL2(x)        VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_PROC_STAT_WFIL2           VTSS_BIT(1)
#define  VTSS_X_CPU_PROC_STAT_WFIL2(x)        VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Wait-for-event status.
 *
 * \details
 * Field: ::VTSS_CPU_PROC_STAT . WFE
 */
#define  VTSS_F_CPU_PROC_STAT_WFE(x)          VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PROC_STAT_WFE             VTSS_BIT(0)
#define  VTSS_X_CPU_PROC_STAT_WFE(x)          VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Reset Vector Base Address Register of Core 0
 *
 * \details
 * Register: \a CPU:CPU_REGS:CPU0_RVBAR_LSB
 */
#define VTSS_CPU_CPU0_RVBAR_LSB              VTSS_IOREG(VTSS_TO_CPU,0x2a)

/**
 * \brief
 * Reset Vector Base Address for Core 0 of processor in 64-bit state.This
 * register is sampled on reset of the core 0 of the processor.See also
 * CPU::CPU0_RVBAR_MSB.
 *
 * \details
 * Reset vector base address[33:2] for the 64-bit state.
 *
 * Field: ::VTSS_CPU_CPU0_RVBAR_LSB . CPU0_RVBAR_LSB
 */
#define  VTSS_F_CPU_CPU0_RVBAR_LSB_CPU0_RVBAR_LSB(x)  (x)
#define  VTSS_M_CPU_CPU0_RVBAR_LSB_CPU0_RVBAR_LSB     0xffffffff
#define  VTSS_X_CPU_CPU0_RVBAR_LSB_CPU0_RVBAR_LSB(x)  (x)


/**
 * \brief Reset Vector Base Address Register of Core 0
 *
 * \details
 * Register: \a CPU:CPU_REGS:CPU0_RVBAR_MSB
 */
#define VTSS_CPU_CPU0_RVBAR_MSB              VTSS_IOREG(VTSS_TO_CPU,0x2b)

/**
 * \brief
 * Reset Vector Base Address for Core 0 of processor in 64-bit state.This
 * register is sampled on reset of the core 0 of the processor.See also
 * CPU::CPU0_RVBAR_LSB.
 *
 * \details
 * Reset vector base address[39:34] for the 64-bit state
 *
 * Field: ::VTSS_CPU_CPU0_RVBAR_MSB . CPU0_RVBAR_MSB
 */
#define  VTSS_F_CPU_CPU0_RVBAR_MSB_CPU0_RVBAR_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CPU_CPU0_RVBAR_MSB_CPU0_RVBAR_MSB     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CPU_CPU0_RVBAR_MSB_CPU0_RVBAR_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a CPU:GCK_REGS
 *
 * Generic Clock controller
 */


/**
 * \brief Generic Clock Configuration register
 *
 * \details
 * This register controls configuration for generation of Generic clock
 * (GCK) for each of the peripherals which require GCK. This register is
 * replicated 12 times. The below index specifies the peripheral position
 * in the replicated register.
 *
 * GCK_ID_QSPI0 = 0,
 * GCK_ID_QSPI1 = 1,
 * GCK_ID_QSPI2 = 2,
 * GCK_ID_SDMMC0 = 3,
 * GCK_ID_PI = 4,
 * GCK_ID_MCAN0 = 5,
 * GCK_ID_MCAN1 = 6,
 * GCK_ID_FLEXCOM0 = 7,
 * GCK_ID_FLEXCOM1 = 8,
 * GCK_ID_FLEXCOM2 = 9,
 * GCK_ID_FLEXCOM3 = 10,
 * GCK_ID_FLEXCOM4 = 11,
 * GCK_ID_TIMER    = 12,
 * GCK_ID_USB_REFCLK = 13,
 *
 *
 * i.e GCK_CFG[0] controls QSPI0, GCK_CFG[7] controls FLEXCOM0
 *
 * Register: \a CPU:GCK_REGS:GCK_CFG
 *
 * @param ri Register: GCK_CFG (??), 0-13
 */
#define VTSS_CPU_GCK_CFG(ri)                 VTSS_IOREG(VTSS_TO_CPU,0x2c + (ri))

/**
 * \brief
 * Prescaler divider value. The selected source clock is divided by
 * prescaler + 1.
 *
 * \details
 * 0 - Divide by 1
 * 1 - Divide by 2
 * 2 - Divide by 3
 * ...
 * 255 - Divide by 256
 *
 * Field: ::VTSS_CPU_GCK_CFG . GCK_PRESCALER
 */
#define  VTSS_F_CPU_GCK_CFG_GCK_PRESCALER(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_CPU_GCK_CFG_GCK_PRESCALER     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_CPU_GCK_CFG_GCK_PRESCALER(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Selects which source clock is used for GCK generation. There are 3
 * source clocks available for GCK generation.0  - CPU_CLK which is 600
 * MHz1  - DDR_CLK which is 300 MHz (or 266 MHz TBD).2	- SYS_CLK  which is
 * 162.5 MHz
 *
 * \details
 * 0 - CPU_CLK is used for Source clock.
 * 1 - DDR_CLK is used for Source clock.
 * 2 - SYS_CLK is used for Source  clock.
 * 3 - Reserved. Do not use
 *
 * Field: ::VTSS_CPU_GCK_CFG . GCK_SRC_SEL
 */
#define  VTSS_F_CPU_GCK_CFG_GCK_SRC_SEL(x)    VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_CPU_GCK_CFG_GCK_SRC_SEL       VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_CPU_GCK_CFG_GCK_SRC_SEL(x)    VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * Enable Generic clock generation for this peripheral
 *
 * \details
 * 0 - GCK is clock gated.
 * 1 - GCK is enabled.
 *
 * Field: ::VTSS_CPU_GCK_CFG . GCK_ENA
 */
#define  VTSS_F_CPU_GCK_CFG_GCK_ENA(x)        VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_GCK_CFG_GCK_ENA           VTSS_BIT(0)
#define  VTSS_X_CPU_GCK_CFG_GCK_ENA(x)        VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a CPU:USB_REGS
 *
 * USB registers
 */


/**
 * \brief Configuration register
 *
 * \details
 * Register: \a CPU:USB_REGS:USB_CFG
 */
#define VTSS_CPU_USB_CFG                     VTSS_IOREG(VTSS_TO_CPU,0x3a)

/**
 * \brief
 * Wait value for debouncer. The input is qualified once it has remained
 * stable for DEB_CYCLES_CNT clock cycles, otherwise it is rejected.
 *
 * \details
 * Field: ::VTSS_CPU_USB_CFG . DEB_CYCLES_CNT
 */
#define  VTSS_F_CPU_USB_CFG_DEB_CYCLES_CNT(x)  VTSS_ENCODE_BITFIELD(x,2,24)
#define  VTSS_M_CPU_USB_CFG_DEB_CYCLES_CNT     VTSS_ENCODE_BITMASK(2,24)
#define  VTSS_X_CPU_USB_CFG_DEB_CYCLES_CNT(x)  VTSS_EXTRACT_BITFIELD(x,2,24)

/**
 * \brief
 * Polarity for VBUS_DET.
 *
 * \details
 * 0: Active high
 * 1: Active low
 *
 * Field: ::VTSS_CPU_USB_CFG . VBUS_DET_POL
 */
#define  VTSS_F_CPU_USB_CFG_VBUS_DET_POL(x)   VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_USB_CFG_VBUS_DET_POL      VTSS_BIT(1)
#define  VTSS_X_CPU_USB_CFG_VBUS_DET_POL(x)   VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Polarity for OCS_N.
 *
 * \details
 * 0: Active high
 * 1: Active low
 *
 * Field: ::VTSS_CPU_USB_CFG . OCS_N_POL
 */
#define  VTSS_F_CPU_USB_CFG_OCS_N_POL(x)      VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_USB_CFG_OCS_N_POL         VTSS_BIT(0)
#define  VTSS_X_CPU_USB_CFG_OCS_N_POL(x)      VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Control signals for USB
 *
 * \details
 * Register: \a CPU:USB_REGS:USB_CTRL
 */
#define VTSS_CPU_USB_CTRL                    VTSS_IOREG(VTSS_TO_CPU,0x3b)

/**
 * \brief
 * FLADJ_30MHZ_REG: HS Jitter AdjustmentIndicates the correction required
 * to accommodate mac3 clock and utmi clock jitter to measure 125 's
 * duration.With fladj_30mhz_reg tied to zero, the high speed 125us
 * micro-frame is counted for 123933ns. You must program the value in terms
 * of high speed bit times in a 30 MHz cycle. The default value that must
 * be driven is 32 (assuming 30 MHz perfect clock).Each count is equal to
 * 16 high speed bit times. Now, based the clock accuracy you can decrement
 * the count orincrement the count to get the 125 us uSOF window.
 *
 * \details
 * Field: ::VTSS_CPU_USB_CTRL . FLADJ_30MHZ_REG
 */
#define  VTSS_F_CPU_USB_CTRL_FLADJ_30MHZ_REG(x)  VTSS_ENCODE_BITFIELD(x,5,6)
#define  VTSS_M_CPU_USB_CTRL_FLADJ_30MHZ_REG     VTSS_ENCODE_BITMASK(5,6)
#define  VTSS_X_CPU_USB_CTRL_FLADJ_30MHZ_REG(x)  VTSS_EXTRACT_BITFIELD(x,5,6)

/**
 * \brief
 * Power enable (USB host mode).
 *
 * \details
 * Field: ::VTSS_CPU_USB_CTRL . POWER_EN
 */
#define  VTSS_F_CPU_USB_CTRL_POWER_EN(x)      VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_USB_CTRL_POWER_EN         VTSS_BIT(0)
#define  VTSS_X_CPU_USB_CTRL_POWER_EN(x)      VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Forwarding an external OCS input status to DWC_usb3 IP core.
 *
 * \details
 * 0: Not forwarding OCS status to DWC_usb3
 * 1: Forwarding OCS status to DWC_usb3
 *
 * Field: ::VTSS_CPU_USB_CTRL . OCS_TO_DWC_USB3
 */
#define  VTSS_F_CPU_USB_CTRL_OCS_TO_DWC_USB3(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_USB_CTRL_OCS_TO_DWC_USB3  VTSS_BIT(2)
#define  VTSS_X_CPU_USB_CTRL_OCS_TO_DWC_USB3(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Controlling an external VBUS output either through CSR register
 * (CPU:USB_REGS:USB_CTRL.POWER_EN) OR xHCI register field Port Power in
 * PORTSC register).
 *
 * \details
 * 0: CSR register
 * 1: xHCI register
 *
 * Field: ::VTSS_CPU_USB_CTRL . POWER_EN_CONTROL
 */
#define  VTSS_F_CPU_USB_CTRL_POWER_EN_CONTROL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_USB_CTRL_POWER_EN_CONTROL  VTSS_BIT(3)
#define  VTSS_X_CPU_USB_CTRL_POWER_EN_CONTROL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * This register bit controls the "host_port_power_control_present" input
 * port of DWC_usb3 IP core. This port defines the bit[3] of Capability
 * Parameters (HCCPARAMS).
 *
 * \details
 * 0: Indicates that the port does not have port power switches.
 * 1: Indicates that the port has port power switches.
 *
 * Field: ::VTSS_CPU_USB_CTRL . PORT_POWER_CONTROL_PRESENT
 */
#define  VTSS_F_CPU_USB_CTRL_PORT_POWER_CONTROL_PRESENT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CPU_USB_CTRL_PORT_POWER_CONTROL_PRESENT  VTSS_BIT(4)
#define  VTSS_X_CPU_USB_CTRL_PORT_POWER_CONTROL_PRESENT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/**
 * \brief Status register
 *
 * \details
 * Register: \a CPU:USB_REGS:USB_STAT
 */
#define VTSS_CPU_USB_STAT                    VTSS_IOREG(VTSS_TO_CPU,0x3c)

/**
 * \brief
 * Clock gating controlThis signal indicates the clock gating controls used
 * for gating RAM and bus clocks.Bit[0] is gating control for bus_clk,
 * bit[1] and bit[2] is for ram_clk_in.
 *
 * \details
 * Field: ::VTSS_CPU_USB_STAT . CLK_GATE_CTRL
 */
#define  VTSS_F_CPU_USB_STAT_CLK_GATE_CTRL(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_CPU_USB_STAT_CLK_GATE_CTRL     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_CPU_USB_STAT_CLK_GATE_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * HOST_SYS_ERR: Host System ErrorThis status bit indicates that a Host
 * System Error has occurred as reflected in the HSE register field of
 * USBSTS register of Synopsys USB Host Controller. This signal is asserted
 * only if the HSEE register field of USBCMD register is set to '1'. It can
 * occur when the host controller encounters an 'Error' response in the
 * AHB, the AXI, or the Native Master Bus. When the HSE register field of
 * USBSTS register is cleared by software, this signal is deasserted unless
 * the master continues to assert its bus error output. The typical
 * software response to an HSE is to reset the controller. For more
 * details, refer to section 4.10.2.6 of the xHCI 1.0 specification.
 *
 * \details
 * Field: ::VTSS_CPU_USB_STAT . HOST_SYS_ERR
 */
#define  VTSS_F_CPU_USB_STAT_HOST_SYS_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_USB_STAT_HOST_SYS_ERR     VTSS_BIT(2)
#define  VTSS_X_CPU_USB_STAT_HOST_SYS_ERR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Over-current-detected (USB host mode).
 *
 * \details
 * Field: ::VTSS_CPU_USB_STAT . OCS_N
 */
#define  VTSS_F_CPU_USB_STAT_OCS_N(x)         VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_USB_STAT_OCS_N            VTSS_BIT(1)
#define  VTSS_X_CPU_USB_STAT_OCS_N(x)         VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Indicates that there is power applied to the USB target interface.
 *
 * \details
 * Field: ::VTSS_CPU_USB_STAT . VBUS_DET
 */
#define  VTSS_F_CPU_USB_STAT_VBUS_DET(x)      VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_USB_STAT_VBUS_DET         VTSS_BIT(0)
#define  VTSS_X_CPU_USB_STAT_VBUS_DET(x)      VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Interrupt Status Register
 *
 * \details
 * Register: \a CPU:USB_REGS:USB_INTR
 */
#define VTSS_CPU_USB_INTR                    VTSS_IOREG(VTSS_TO_CPU,0x3d)

/**
 * \brief
 * Sticky bit for OCS_N.
 *
 * \details
 * Field: ::VTSS_CPU_USB_INTR . INTR_OCS_N_STICKY
 */
#define  VTSS_F_CPU_USB_INTR_INTR_OCS_N_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_USB_INTR_INTR_OCS_N_STICKY  VTSS_BIT(1)
#define  VTSS_X_CPU_USB_INTR_INTR_OCS_N_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Sticky bit for VBUS_DET.
 *
 * \details
 * Field: ::VTSS_CPU_USB_INTR . INTR_VBUS_DET_STICKY
 */
#define  VTSS_F_CPU_USB_INTR_INTR_VBUS_DET_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_USB_INTR_INTR_VBUS_DET_STICKY  VTSS_BIT(0)
#define  VTSS_X_CPU_USB_INTR_INTR_VBUS_DET_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Interrupt Enable Register
 *
 * \details
 * Register: \a CPU:USB_REGS:USB_INTR_ENA
 */
#define VTSS_CPU_USB_INTR_ENA                VTSS_IOREG(VTSS_TO_CPU,0x3e)

/**
 * \brief
 * Interrupt enable.
 *
 * \details
 * Field: ::VTSS_CPU_USB_INTR_ENA . INTR_ENA_OCS_N
 */
#define  VTSS_F_CPU_USB_INTR_ENA_INTR_ENA_OCS_N(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_USB_INTR_ENA_INTR_ENA_OCS_N  VTSS_BIT(1)
#define  VTSS_X_CPU_USB_INTR_ENA_INTR_ENA_OCS_N(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Interrupt enable.
 *
 * \details
 * Field: ::VTSS_CPU_USB_INTR_ENA . INTR_ENA_VBUS_DET
 */
#define  VTSS_F_CPU_USB_INTR_ENA_INTR_ENA_VBUS_DET(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_USB_INTR_ENA_INTR_ENA_VBUS_DET  VTSS_BIT(0)
#define  VTSS_X_CPU_USB_INTR_ENA_INTR_ENA_VBUS_DET(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Currently active interrupt sources.
 *
 * \details
 * Register: \a CPU:USB_REGS:USB_INTR_IDENT
 */
#define VTSS_CPU_USB_INTR_IDENT              VTSS_IOREG(VTSS_TO_CPU,0x3f)

/**
 * \details
 * 1: Interrupt active
 * 0: Interrupt inactive
 *
 * Field: ::VTSS_CPU_USB_INTR_IDENT . INTR_IDENT_OCS_N
 */
#define  VTSS_F_CPU_USB_INTR_IDENT_INTR_IDENT_OCS_N(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_USB_INTR_IDENT_INTR_IDENT_OCS_N  VTSS_BIT(1)
#define  VTSS_X_CPU_USB_INTR_IDENT_INTR_IDENT_OCS_N(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * 1: Interrupt active
 * 0: Interrupt inactive
 *
 * Field: ::VTSS_CPU_USB_INTR_IDENT . INTR_IDENT_VBUS_DET
 */
#define  VTSS_F_CPU_USB_INTR_IDENT_INTR_IDENT_VBUS_DET(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_USB_INTR_IDENT_INTR_IDENT_VBUS_DET  VTSS_BIT(0)
#define  VTSS_X_CPU_USB_INTR_IDENT_INTR_IDENT_VBUS_DET(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief USB DEBUG1 Register
 *
 * \details
 * Register: \a CPU:USB_REGS:USB_DEBUG1
 */
#define VTSS_CPU_USB_DEBUG1                  VTSS_IOREG(VTSS_TO_CPU,0x40)

/**
 * \brief
 * DEBUG1: For debugging purposeTo log the values of debug[31:0] out of
 * debug[66:0] output port.
 *
 * \details
 * Field: ::VTSS_CPU_USB_DEBUG1 . DEBUG1
 */
#define  VTSS_F_CPU_USB_DEBUG1_DEBUG1(x)      (x)
#define  VTSS_M_CPU_USB_DEBUG1_DEBUG1         0xffffffff
#define  VTSS_X_CPU_USB_DEBUG1_DEBUG1(x)      (x)


/**
 * \brief USB Debug2 Register
 *
 * \details
 * Register: \a CPU:USB_REGS:USB_DEBUG2
 */
#define VTSS_CPU_USB_DEBUG2                  VTSS_IOREG(VTSS_TO_CPU,0x41)

/**
 * \brief
 * DEBUG2: For debugging purposeTo log the values of debug[63:32] out of
 * debug[66:0] output port.
 *
 * \details
 * Field: ::VTSS_CPU_USB_DEBUG2 . DEBUG2
 */
#define  VTSS_F_CPU_USB_DEBUG2_DEBUG2(x)      (x)
#define  VTSS_M_CPU_USB_DEBUG2_DEBUG2         0xffffffff
#define  VTSS_X_CPU_USB_DEBUG2_DEBUG2(x)      (x)


/**
 * \brief USB Debug3 register
 *
 * \details
 * Register: \a CPU:USB_REGS:USB_DEBUG3
 */
#define VTSS_CPU_USB_DEBUG3                  VTSS_IOREG(VTSS_TO_CPU,0x42)

/**
 * \brief
 * DEBUG3: For debugging purposeTo log the values of debug[66:64] out of
 * debug[66:0] output port.
 *
 * \details
 * Field: ::VTSS_CPU_USB_DEBUG3 . DEBUG3
 */
#define  VTSS_F_CPU_USB_DEBUG3_DEBUG3(x)      VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_CPU_USB_DEBUG3_DEBUG3         VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_CPU_USB_DEBUG3_DEBUG3(x)      VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief USB Logic Analyzer trace 1 register
 *
 * \details
 * Register: \a CPU:USB_REGS:USB_LA_TRACE1
 */
#define VTSS_CPU_USB_LA_TRACE1               VTSS_IOREG(VTSS_TO_CPU,0x43)

/**
 * \brief
 * LA_TRACE1:  Logic Analyzer Trace output LSB 32 bitsThese are internal
 * design signals of DWC_usb3 IP core that can be used for debug
 * purposes.To log the values of logic_analyzer_trace[31:0] out of
 * logic_analyzer_trace[63:0] output port.
 *
 * \details
 * Field: ::VTSS_CPU_USB_LA_TRACE1 . LA_TRACE1
 */
#define  VTSS_F_CPU_USB_LA_TRACE1_LA_TRACE1(x)  (x)
#define  VTSS_M_CPU_USB_LA_TRACE1_LA_TRACE1     0xffffffff
#define  VTSS_X_CPU_USB_LA_TRACE1_LA_TRACE1(x)  (x)


/**
 * \brief USB Logic Analyzer trace 2 register
 *
 * \details
 * Register: \a CPU:USB_REGS:USB_LA_TRACE2
 */
#define VTSS_CPU_USB_LA_TRACE2               VTSS_IOREG(VTSS_TO_CPU,0x44)

/**
 * \brief
 * LA_TRACE2: Logic Analyzer Trace output MSB 32 bitsThese are internal
 * design signals of DWC_usb3 IP core that can be used for debug
 * purposes.To log the values of logic_analyzer_trace[63:32] out of
 * logic_analyzer_trace[63:0] output port.
 *
 * \details
 * Field: ::VTSS_CPU_USB_LA_TRACE2 . LA_TRACE2
 */
#define  VTSS_F_CPU_USB_LA_TRACE2_LA_TRACE2(x)  (x)
#define  VTSS_M_CPU_USB_LA_TRACE2_LA_TRACE2     0xffffffff
#define  VTSS_X_CPU_USB_LA_TRACE2_LA_TRACE2(x)  (x)


/**
 * \brief USB Global General Purpose Input/Output Register
 *
 * \details
 * The application can use this register for general purpose input and
 * output ports or for debugging.
 *
 * Register: \a CPU:USB_REGS:USB_GGPIO
 */
#define VTSS_CPU_USB_GGPIO                   VTSS_IOREG(VTSS_TO_CPU,0x45)

/**
 * \brief
 * General Purpose OutputThe value of this field is driven out on the
 * gp_out[15:0] output port.
 *
 * \details
 * Field: ::VTSS_CPU_USB_GGPIO . GPO
 */
#define  VTSS_F_CPU_USB_GGPIO_GPO(x)          VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_CPU_USB_GGPIO_GPO             VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_CPU_USB_GGPIO_GPO(x)          VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * GPI: General Purpose InputThe read value of this field reflects the
 * gp_in[15:0] input signal value.Note: Register bit-bash test should not
 * check for reset value of this field since its not predictable; depends
 * on the gp_in port.
 *
 * \details
 * Field: ::VTSS_CPU_USB_GGPIO . GPI
 */
#define  VTSS_F_CPU_USB_GGPIO_GPI(x)          VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_CPU_USB_GGPIO_GPI             VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_CPU_USB_GGPIO_GPI(x)          VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a CPU:MIIM_TARGET
 *
 * Register group controlling MIIM slave attached to external interface AXI Master
 */


/**
 * \brief MIIM Slave Spike Filter
 *
 * \details
 * Register: \a CPU:MIIM_TARGET:MIIM_TARGET_CFG
 */
#define VTSS_CPU_MIIM_TARGET_CFG             VTSS_IOREG(VTSS_TO_CPU,0x46)

/**
 * \brief
 * Configuration of the spike filter width on the MDC and MDIO
 * inputs.Filters spikes with a width of (SPIKE_FILTER_CFG+1)*SYSTEM_CLK or
 * less.
 *
 * \details
 * Field: ::VTSS_CPU_MIIM_TARGET_CFG . SPIKE_FILTER_CFG
 */
#define  VTSS_F_CPU_MIIM_TARGET_CFG_SPIKE_FILTER_CFG(x)  VTSS_ENCODE_BITFIELD(x,1,5)
#define  VTSS_M_CPU_MIIM_TARGET_CFG_SPIKE_FILTER_CFG     VTSS_ENCODE_BITMASK(1,5)
#define  VTSS_X_CPU_MIIM_TARGET_CFG_SPIKE_FILTER_CFG(x)  VTSS_EXTRACT_BITFIELD(x,1,5)

/**
 * \brief
 * Set this field to enable the spike filter on the MDC and MDIO inputs.
 * When enabled the MIIM_TARGET_CFG.SPIKE_FILTER_CFG field determines the
 * width of the spike filter.
 *
 * \details
 * Field: ::VTSS_CPU_MIIM_TARGET_CFG . SPIKE_FILTER_ENA
 */
#define  VTSS_F_CPU_MIIM_TARGET_CFG_SPIKE_FILTER_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_MIIM_TARGET_CFG_SPIKE_FILTER_ENA  VTSS_BIT(0)
#define  VTSS_X_CPU_MIIM_TARGET_CFG_SPIKE_FILTER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a CPU:VCORE_ACC
 *
 * This register group contains configurations to control VCore Access via registers in GCB.
 */


/**
 * \brief This configuration controls Vcore Accesses
 *
 * \details
 * Register: \a CPU:VCORE_ACC:VCORE_ACC_CFG
 */
#define VTSS_CPU_VCORE_ACC_CFG               VTSS_IOREG(VTSS_TO_CPU,0x47)

/**
 * \brief
 * Disable Vcore Access's Read error propagation from AXI bus.
 *
 * \details
 * 0 : Propagate VA_RD_ERR from AXI
 * 1 : Do not propagate VA_RD_ERR from AXI.
 *
 * Field: ::VTSS_CPU_VCORE_ACC_CFG . DIS_VA_RD_ERR
 */
#define  VTSS_F_CPU_VCORE_ACC_CFG_DIS_VA_RD_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_VCORE_ACC_CFG_DIS_VA_RD_ERR  VTSS_BIT(0)
#define  VTSS_X_CPU_VCORE_ACC_CFG_DIS_VA_RD_ERR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a CPU:MSIX_ACC
 *
 * Register which controls MSIX access through External master
 */


/**
 * \brief This configuration controls Interrupt accesses that go throuhg extenral master.
 *
 * \details
 * Register: \a CPU:MSIX_ACC:MSIX_ACC_CFG
 */
#define VTSS_CPU_MSIX_ACC_CFG                VTSS_IOREG(VTSS_TO_CPU,0x48)

/**
 * \brief
 * Disable PCI-e MSIX Read error propagation from AXI bus.
 *
 * \details
 * 0 : Propagate MSIX RD_ERR from AXI
 * 1 : Do not propagate MSIX_RD_ERR from AXI.
 *
 * Field: ::VTSS_CPU_MSIX_ACC_CFG . DIS_MSIX_RD_ERR
 */
#define  VTSS_F_CPU_MSIX_ACC_CFG_DIS_MSIX_RD_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_MSIX_ACC_CFG_DIS_MSIX_RD_ERR  VTSS_BIT(0)
#define  VTSS_X_CPU_MSIX_ACC_CFG_DIS_MSIX_RD_ERR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a CPU:EXT_IF_ACC_STAT
 *
 * This register group contains statistics indications for external Interface accesses
 */


/**
 * \brief Access status indication for ETHFRM_ACC, SI_SLAVE_ACC
 *
 * \details
 * Register: \a CPU:EXT_IF_ACC_STAT:EXT_IF_ACC_STAT
 */
#define VTSS_CPU_EXT_IF_ACC_STAT             VTSS_IOREG(VTSS_TO_CPU,0x49)

/**
 * \brief
 * Status indication for last access performed via VRAP access.
 *
 * \details
 * 3'h0: OK_R; Read transaction finished successfully
 * 3'h1 OK_W; Write transaction finished successfully
 * 3'h2 Reserved
 * 3'h3 Reserved
 * 3'h4 SLVERR_R; Addressed slave generated error for read access
 * 3'h5 SLVERR_W; Addressed slave generated an error for write access
 * 3'h6 DECERR_R; Decode error from interconnect on read access
 * 3'h7 DECERR_W; Decode error from interconnect on write access
 *
 * Field: ::VTSS_CPU_EXT_IF_ACC_STAT . VRAP_ACC_STAT
 */
#define  VTSS_F_CPU_EXT_IF_ACC_STAT_VRAP_ACC_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_CPU_EXT_IF_ACC_STAT_VRAP_ACC_STAT     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_CPU_EXT_IF_ACC_STAT_VRAP_ACC_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Status indication for last access performed via SI access.
 *
 * \details
 * 3'h0: OK_R; Read transaction finished successfully
 * 3'h1  OK_W; Write transaction finished successfully
 * 3'h2  Reserved
 * 3'h3  Reserved
 * 3'h4  SLVERR_R; Addressed slave generated error for read access
 * 3'h5  SLVERR_W; Addressed slave generated an error for write access
 * 3'h6  DECERR_R; Decode error from interconnect on read access
 * 3'h7  DECERR_W; Decode error from interconnect on write access
 *
 * Field: ::VTSS_CPU_EXT_IF_ACC_STAT . SI_ACC_STAT
 */
#define  VTSS_F_CPU_EXT_IF_ACC_STAT_SI_ACC_STAT(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_CPU_EXT_IF_ACC_STAT_SI_ACC_STAT     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_CPU_EXT_IF_ACC_STAT_SI_ACC_STAT(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \brief
 * Status indication for last access performed via Parallel Interface.
 *
 * \details
 * 3'h0: OK_R; Read transaction finished successfully
 * 3'h1  OK_W; Write transaction finished successfully
 * 3'h2  Reserved
 * 3'h3  Reserved
 * 3'h4  SLVERR_R; Addressed slave generated error for read access
 * 3'h5  SLVERR_W; Addressed slave generated an error for write access
 * 3'h6  DECERR_R; Decode error from interconnect on read access
 * 3'h7  DECERR_W; Decode error from interconnect on write access
 *
 * Field: ::VTSS_CPU_EXT_IF_ACC_STAT . MIIM_ACC_STAT
 */
#define  VTSS_F_CPU_EXT_IF_ACC_STAT_MIIM_ACC_STAT(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_CPU_EXT_IF_ACC_STAT_MIIM_ACC_STAT     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_CPU_EXT_IF_ACC_STAT_MIIM_ACC_STAT(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * Status indication for last access performed via VCORE Access
 *
 * \details
 * 3'h0: OK_R; Read transaction finished successfully
 * 3'h1  OK_W; Write transaction finished successfully
 * 3'h2  Reserved
 * 3'h3  Reserved
 * 3'h4  SLVERR_R; Addressed slave generated error for read access
 * 3'h5  SLVERR_W; Addressed slave generated an error for write access
 * 3'h6  DECERR_R; Decode error from interconnect on read access
 * 3'h7  DECERR_W; Decode error from interconnect on write access
 *
 * Field: ::VTSS_CPU_EXT_IF_ACC_STAT . VA_ACC_STAT
 */
#define  VTSS_F_CPU_EXT_IF_ACC_STAT_VA_ACC_STAT(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_CPU_EXT_IF_ACC_STAT_VA_ACC_STAT     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_CPU_EXT_IF_ACC_STAT_VA_ACC_STAT(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * Status indication for last access performed via MSIX Access
 *
 * \details
 * 3'h0: OK_R; Read transaction finished successfully
 * 3'h1  OK_W; Write transaction finished successfully
 * 3'h2  Reserved
 * 3'h3  Reserved
 * 3'h4  SLVERR_R; Addressed slave generated error for read access
 * 3'h5  SLVERR_W; Addressed slave generated an error for write access
 * 3'h6  DECERR_R; Decode error from interconnect on read access
 * 3'h7  DECERR_W; Decode error from interconnect on write access
 *
 * Field: ::VTSS_CPU_EXT_IF_ACC_STAT . MSIX_ACC_STAT
 */
#define  VTSS_F_CPU_EXT_IF_ACC_STAT_MSIX_ACC_STAT(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_CPU_EXT_IF_ACC_STAT_MSIX_ACC_STAT     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_CPU_EXT_IF_ACC_STAT_MSIX_ACC_STAT(x)  VTSS_EXTRACT_BITFIELD(x,20,3)

/**
 * Register Group: \a CPU:INTR
 *
 * Interrupt controller
 */


/**
 * \brief Interrupt raw status
 *
 * \details
 * Register: \a CPU:INTR:INTR_RAW
 */
#define VTSS_CPU_INTR_RAW                    VTSS_IOREG(VTSS_TO_CPU,0x4a)

/**
 * \brief
 * Shows the current value of individual interrupt sources. All sources are
 * active high (the external interrupts has been corrected for polarity as
 * configured in EXT_SRC_INTR_POL).
 *
 * \details
 * Field: ::VTSS_CPU_INTR_RAW . INTR_RAW
 */
#define  VTSS_F_CPU_INTR_RAW_INTR_RAW(x)      (x)
#define  VTSS_M_CPU_INTR_RAW_INTR_RAW         0xffffffff
#define  VTSS_X_CPU_INTR_RAW_INTR_RAW(x)      (x)


/**
 * \brief Interrupt raw status
 *
 * \details
 * Register: \a CPU:INTR:INTR_RAW1
 */
#define VTSS_CPU_INTR_RAW1                   VTSS_IOREG(VTSS_TO_CPU,0x4b)

/**
 * \brief
 * Bit 32-63 of field INTR_RAW.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_RAW1 . INTR_RAW1
 */
#define  VTSS_F_CPU_INTR_RAW1_INTR_RAW1(x)    (x)
#define  VTSS_M_CPU_INTR_RAW1_INTR_RAW1       0xffffffff
#define  VTSS_X_CPU_INTR_RAW1_INTR_RAW1(x)    (x)


/**
 * \brief Interrupt raw status
 *
 * \details
 * Register: \a CPU:INTR:INTR_RAW2
 */
#define VTSS_CPU_INTR_RAW2                   VTSS_IOREG(VTSS_TO_CPU,0x4c)

/**
 * \brief
 * Bit 64-95 of field INTR_RAW.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_RAW2 . INTR_RAW2
 */
#define  VTSS_F_CPU_INTR_RAW2_INTR_RAW2(x)    (x)
#define  VTSS_M_CPU_INTR_RAW2_INTR_RAW2       0xffffffff
#define  VTSS_X_CPU_INTR_RAW2_INTR_RAW2(x)    (x)


/**
 * \brief Interrupt trigger mode
 *
 * \details
 * Register: \a CPU:INTR:INTR_TRIGGER
 *
 * @param ri Register: INTR_TRIGGER (??), 0-1
 */
#define VTSS_CPU_INTR_TRIGGER(ri)            VTSS_IOREG(VTSS_TO_CPU,0x4d + (ri))

/**
 * \brief
 * Configure trigger mode of individual interrupt sources. The trigger mode
 * determines how the value of the INTR_RAW register is transferred to the
 * INTR_STICKY register. This register is replicated, the first replication
 * controls bit 0 in the encoding, the second replication controls bit 1 in
 * the encoding. I.e. to configure falling-edge-triggered interrupt for
 * interrupt source 5; set INTR_TRIGGER[0][5]='0' and
 * INTR_TRIGGER[1][5]='1'.For level-triggered interrupts INTR_STICKY is set
 * for as long as the corresponding bit in INTR_RAW is high - i.e. is not
 * possible to clear a bit in INTR_STICKY until the corresponding INTR_RAW
 * is zero.For edge-triggeded interrupts INTR_STICKY is set when the
 * corresponding bit in INTR_RAW changes value.For falling-edge-triggeded
 * interrupts INTR_STICKY is set when the corresponding bit in INTR_RAW
 * changes from '1' to '0'.For rising-edge-triggeded interrupts INTR_STICKY
 * is set when the corresponding bit in INTR_RAW changes from '0' to '1'.
 *
 * \details
 * 0: Interrupt is level-activated
 * 1: Interrupt is edge-triggered
 * 2: Interrupt is falling-edge-triggered
 * 3: Interrupt is rising-edge-triggered
 *
 * Field: ::VTSS_CPU_INTR_TRIGGER . INTR_TRIGGER
 */
#define  VTSS_F_CPU_INTR_TRIGGER_INTR_TRIGGER(x)  (x)
#define  VTSS_M_CPU_INTR_TRIGGER_INTR_TRIGGER     0xffffffff
#define  VTSS_X_CPU_INTR_TRIGGER_INTR_TRIGGER(x)  (x)


/**
 * \brief Interrupt trigger mode
 *
 * \details
 * Register: \a CPU:INTR:INTR_TRIGGER1
 *
 * @param ri Register: INTR_TRIGGER1 (??), 0-1
 */
#define VTSS_CPU_INTR_TRIGGER1(ri)           VTSS_IOREG(VTSS_TO_CPU,0x4f + (ri))

/**
 * \brief
 * Bit 32-63 of field INTR_TRIGGER.
 *
 * \details
 * 0: Interrupt is level-activated
 * 1: Interrupt is edge-triggered
 * 2: Interrupt is falling-edge-triggered
 * 3: Interrupt is rising-edge-triggered
 *
 * Field: ::VTSS_CPU_INTR_TRIGGER1 . INTR_TRIGGER1
 */
#define  VTSS_F_CPU_INTR_TRIGGER1_INTR_TRIGGER1(x)  (x)
#define  VTSS_M_CPU_INTR_TRIGGER1_INTR_TRIGGER1     0xffffffff
#define  VTSS_X_CPU_INTR_TRIGGER1_INTR_TRIGGER1(x)  (x)


/**
 * \brief Interrupt trigger mode
 *
 * \details
 * Register: \a CPU:INTR:INTR_TRIGGER2
 *
 * @param ri Register: INTR_TRIGGER2 (??), 0-1
 */
#define VTSS_CPU_INTR_TRIGGER2(ri)           VTSS_IOREG(VTSS_TO_CPU,0x51 + (ri))

/**
 * \brief
 * Bit 64-95 of field INTR_TRIGGER.
 *
 * \details
 * 0: Interrupt is level-activated
 * 1: Interrupt is edge-triggered
 * 2: Interrupt is falling-edge-triggered
 * 3: Interrupt is rising-edge-triggered
 *
 * Field: ::VTSS_CPU_INTR_TRIGGER2 . INTR_TRIGGER2
 */
#define  VTSS_F_CPU_INTR_TRIGGER2_INTR_TRIGGER2(x)  (x)
#define  VTSS_M_CPU_INTR_TRIGGER2_INTR_TRIGGER2     0xffffffff
#define  VTSS_X_CPU_INTR_TRIGGER2_INTR_TRIGGER2(x)  (x)


/**
 * \brief Interrupt force sticky event
 *
 * \details
 * Register: \a CPU:INTR:INTR_FORCE
 */
#define VTSS_CPU_INTR_FORCE                  VTSS_IOREG(VTSS_TO_CPU,0x53)

/**
 * \brief
 * Set to force corresponding INTR_STICKY bits.This field may be useful
 * during development of software interrupt handler functions.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_FORCE . INTR_FORCE
 */
#define  VTSS_F_CPU_INTR_FORCE_INTR_FORCE(x)  (x)
#define  VTSS_M_CPU_INTR_FORCE_INTR_FORCE     0xffffffff
#define  VTSS_X_CPU_INTR_FORCE_INTR_FORCE(x)  (x)


/**
 * \brief Interrupt force sticky event
 *
 * \details
 * Register: \a CPU:INTR:INTR_FORCE1
 */
#define VTSS_CPU_INTR_FORCE1                 VTSS_IOREG(VTSS_TO_CPU,0x54)

/**
 * \brief
 * Bit 32-63 of field INTR_FORCE.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_FORCE1 . INTR_FORCE1
 */
#define  VTSS_F_CPU_INTR_FORCE1_INTR_FORCE1(x)  (x)
#define  VTSS_M_CPU_INTR_FORCE1_INTR_FORCE1     0xffffffff
#define  VTSS_X_CPU_INTR_FORCE1_INTR_FORCE1(x)  (x)


/**
 * \brief Interrupt force sticky event
 *
 * \details
 * Register: \a CPU:INTR:INTR_FORCE2
 */
#define VTSS_CPU_INTR_FORCE2                 VTSS_IOREG(VTSS_TO_CPU,0x55)

/**
 * \brief
 * Bit 64-95 of field INTR_FORCE.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_FORCE2 . INTR_FORCE2
 */
#define  VTSS_F_CPU_INTR_FORCE2_INTR_FORCE2(x)  (x)
#define  VTSS_M_CPU_INTR_FORCE2_INTR_FORCE2     0xffffffff
#define  VTSS_X_CPU_INTR_FORCE2_INTR_FORCE2(x)  (x)


/**
 * \brief Interrupt sticky status
 *
 * \details
 * Register: \a CPU:INTR:INTR_STICKY
 */
#define VTSS_CPU_INTR_STICKY                 VTSS_IOREG(VTSS_TO_CPU,0x56)

/**
 * \brief
 * This register is set based on source interrupt events or by debug-force.
 * See INTR_TRIGGER and INTR_FORCE for more information. Bits in this
 * register remains set until cleared by software.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_STICKY . INTR_STICKY
 */
#define  VTSS_F_CPU_INTR_STICKY_INTR_STICKY(x)  (x)
#define  VTSS_M_CPU_INTR_STICKY_INTR_STICKY     0xffffffff
#define  VTSS_X_CPU_INTR_STICKY_INTR_STICKY(x)  (x)


/**
 * \brief Interrupt sticky status
 *
 * \details
 * Register: \a CPU:INTR:INTR_STICKY1
 */
#define VTSS_CPU_INTR_STICKY1                VTSS_IOREG(VTSS_TO_CPU,0x57)

/**
 * \brief
 * Bit 32-63 of field INTR_STICKY.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_STICKY1 . INTR_STICKY1
 */
#define  VTSS_F_CPU_INTR_STICKY1_INTR_STICKY1(x)  (x)
#define  VTSS_M_CPU_INTR_STICKY1_INTR_STICKY1     0xffffffff
#define  VTSS_X_CPU_INTR_STICKY1_INTR_STICKY1(x)  (x)


/**
 * \brief Interrupt sticky status
 *
 * \details
 * Register: \a CPU:INTR:INTR_STICKY2
 */
#define VTSS_CPU_INTR_STICKY2                VTSS_IOREG(VTSS_TO_CPU,0x58)

/**
 * \brief
 * Bit 64-95 of field INTR_STICKY.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_STICKY2 . INTR_STICKY2
 */
#define  VTSS_F_CPU_INTR_STICKY2_INTR_STICKY2(x)  (x)
#define  VTSS_M_CPU_INTR_STICKY2_INTR_STICKY2     0xffffffff
#define  VTSS_X_CPU_INTR_STICKY2_INTR_STICKY2(x)  (x)


/**
 * \brief Interrupt bypass enable
 *
 * \details
 * Register: \a CPU:INTR:INTR_BYPASS
 */
#define VTSS_CPU_INTR_BYPASS                 VTSS_IOREG(VTSS_TO_CPU,0x59)

/**
 * \brief
 * This register allows bypass of INTR_STICKY for individual interrupt
 * sources. When an interrupt source is in bypass mode then INTR_RAW is
 * used instead of INTR_STICKY.Note: Enabling bypass does not make sense
 * for all interrupt sources. It should only be used when the corresponding
 * interrupt is sticky at the source. For example manual extraction data
 * available interrupts can be configured to bypass, because the interrupt
 * will remain asserted until the available data has been extracted.Note:
 * The device interrupt is bypassed per default, "stickyness" is already
 * implemented by DEV_INTR_STICKY.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_BYPASS . INTR_BYPASS
 */
#define  VTSS_F_CPU_INTR_BYPASS_INTR_BYPASS(x)  (x)
#define  VTSS_M_CPU_INTR_BYPASS_INTR_BYPASS     0xffffffff
#define  VTSS_X_CPU_INTR_BYPASS_INTR_BYPASS(x)  (x)


/**
 * \brief Interrupt bypass enable
 *
 * \details
 * Register: \a CPU:INTR:INTR_BYPASS1
 */
#define VTSS_CPU_INTR_BYPASS1                VTSS_IOREG(VTSS_TO_CPU,0x5a)

/**
 * \brief
 * Bit 32-63 of field INTR_BYPASS.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_BYPASS1 . INTR_BYPASS1
 */
#define  VTSS_F_CPU_INTR_BYPASS1_INTR_BYPASS1(x)  (x)
#define  VTSS_M_CPU_INTR_BYPASS1_INTR_BYPASS1     0xffffffff
#define  VTSS_X_CPU_INTR_BYPASS1_INTR_BYPASS1(x)  (x)


/**
 * \brief Interrupt bypass enable
 *
 * \details
 * Register: \a CPU:INTR:INTR_BYPASS2
 */
#define VTSS_CPU_INTR_BYPASS2                VTSS_IOREG(VTSS_TO_CPU,0x5b)

/**
 * \brief
 * Bit 64-95 of field INTR_BYPASS.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_BYPASS2 . INTR_BYPASS2
 */
#define  VTSS_F_CPU_INTR_BYPASS2_INTR_BYPASS2(x)  (x)
#define  VTSS_M_CPU_INTR_BYPASS2_INTR_BYPASS2     0xffffffff
#define  VTSS_X_CPU_INTR_BYPASS2_INTR_BYPASS2(x)  (x)


/**
 * \brief Interrupt enable
 *
 * \details
 * Register: \a CPU:INTR:INTR_ENA
 */
#define VTSS_CPU_INTR_ENA                    VTSS_IOREG(VTSS_TO_CPU,0x5c)

/**
 * \brief
 * Set to enable propagation of individual interrupt sources to
 * destinations.Atomic access to this register (needed in a multithreaded
 * system) can be implemented by the INTR_ENA_CLR and INTR_ENA_SET
 * registers.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_ENA . INTR_ENA
 */
#define  VTSS_F_CPU_INTR_ENA_INTR_ENA(x)      (x)
#define  VTSS_M_CPU_INTR_ENA_INTR_ENA         0xffffffff
#define  VTSS_X_CPU_INTR_ENA_INTR_ENA(x)      (x)


/**
 * \brief Interrupt enable
 *
 * \details
 * Register: \a CPU:INTR:INTR_ENA1
 */
#define VTSS_CPU_INTR_ENA1                   VTSS_IOREG(VTSS_TO_CPU,0x5d)

/**
 * \brief
 * Bit 32-63 of field INTR_ENA.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_ENA1 . INTR_ENA1
 */
#define  VTSS_F_CPU_INTR_ENA1_INTR_ENA1(x)    (x)
#define  VTSS_M_CPU_INTR_ENA1_INTR_ENA1       0xffffffff
#define  VTSS_X_CPU_INTR_ENA1_INTR_ENA1(x)    (x)


/**
 * \brief Interrupt enable
 *
 * \details
 * Register: \a CPU:INTR:INTR_ENA2
 */
#define VTSS_CPU_INTR_ENA2                   VTSS_IOREG(VTSS_TO_CPU,0x5e)

/**
 * \brief
 * Bit 64-95 of field INTR_ENA.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_ENA2 . INTR_ENA2
 */
#define  VTSS_F_CPU_INTR_ENA2_INTR_ENA2(x)    (x)
#define  VTSS_M_CPU_INTR_ENA2_INTR_ENA2       0xffffffff
#define  VTSS_X_CPU_INTR_ENA2_INTR_ENA2(x)    (x)


/**
 * \brief Atomic clear of interrupt enable
 *
 * \details
 * Register: \a CPU:INTR:INTR_ENA_CLR
 */
#define VTSS_CPU_INTR_ENA_CLR                VTSS_IOREG(VTSS_TO_CPU,0x5f)

/**
 * \brief
 * Set bit(s) in this register to clear the corresponding bits in INTR_ENA.
 * This register can be used for atomic access to INTR_ENA register.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_ENA_CLR . INTR_ENA_CLR
 */
#define  VTSS_F_CPU_INTR_ENA_CLR_INTR_ENA_CLR(x)  (x)
#define  VTSS_M_CPU_INTR_ENA_CLR_INTR_ENA_CLR     0xffffffff
#define  VTSS_X_CPU_INTR_ENA_CLR_INTR_ENA_CLR(x)  (x)


/**
 * \brief Atomic clear of interrupt enable
 *
 * \details
 * Register: \a CPU:INTR:INTR_ENA_CLR1
 */
#define VTSS_CPU_INTR_ENA_CLR1               VTSS_IOREG(VTSS_TO_CPU,0x60)

/**
 * \brief
 * Bit 32-63 of field INTR_ENA_CLR.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_ENA_CLR1 . INTR_ENA_CLR1
 */
#define  VTSS_F_CPU_INTR_ENA_CLR1_INTR_ENA_CLR1(x)  (x)
#define  VTSS_M_CPU_INTR_ENA_CLR1_INTR_ENA_CLR1     0xffffffff
#define  VTSS_X_CPU_INTR_ENA_CLR1_INTR_ENA_CLR1(x)  (x)


/**
 * \brief Atomic clear of interrupt enable
 *
 * \details
 * Register: \a CPU:INTR:INTR_ENA_CLR2
 */
#define VTSS_CPU_INTR_ENA_CLR2               VTSS_IOREG(VTSS_TO_CPU,0x61)

/**
 * \brief
 * Bit 64-95 of field INTR_ENA_CLR.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_ENA_CLR2 . INTR_ENA_CLR2
 */
#define  VTSS_F_CPU_INTR_ENA_CLR2_INTR_ENA_CLR2(x)  (x)
#define  VTSS_M_CPU_INTR_ENA_CLR2_INTR_ENA_CLR2     0xffffffff
#define  VTSS_X_CPU_INTR_ENA_CLR2_INTR_ENA_CLR2(x)  (x)


/**
 * \brief Atomic set of interrupt
 *
 * \details
 * Register: \a CPU:INTR:INTR_ENA_SET
 */
#define VTSS_CPU_INTR_ENA_SET                VTSS_IOREG(VTSS_TO_CPU,0x62)

/**
 * \brief
 * Set bit(s) in this register to set the corresponding bits in INTR_ENA.
 * This register can be used for atomic access to INTR_ENA register.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_ENA_SET . INTR_ENA_SET
 */
#define  VTSS_F_CPU_INTR_ENA_SET_INTR_ENA_SET(x)  (x)
#define  VTSS_M_CPU_INTR_ENA_SET_INTR_ENA_SET     0xffffffff
#define  VTSS_X_CPU_INTR_ENA_SET_INTR_ENA_SET(x)  (x)


/**
 * \brief Atomic set of interrupt
 *
 * \details
 * Register: \a CPU:INTR:INTR_ENA_SET1
 */
#define VTSS_CPU_INTR_ENA_SET1               VTSS_IOREG(VTSS_TO_CPU,0x63)

/**
 * \brief
 * Bit 32-63 of field INTR_ENA_SET.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_ENA_SET1 . INTR_ENA_SET1
 */
#define  VTSS_F_CPU_INTR_ENA_SET1_INTR_ENA_SET1(x)  (x)
#define  VTSS_M_CPU_INTR_ENA_SET1_INTR_ENA_SET1     0xffffffff
#define  VTSS_X_CPU_INTR_ENA_SET1_INTR_ENA_SET1(x)  (x)


/**
 * \brief Atomic set of interrupt
 *
 * \details
 * Register: \a CPU:INTR:INTR_ENA_SET2
 */
#define VTSS_CPU_INTR_ENA_SET2               VTSS_IOREG(VTSS_TO_CPU,0x64)

/**
 * \brief
 * Bit 64-95 of field INTR_ENA_SET.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_ENA_SET2 . INTR_ENA_SET2
 */
#define  VTSS_F_CPU_INTR_ENA_SET2_INTR_ENA_SET2(x)  (x)
#define  VTSS_M_CPU_INTR_ENA_SET2_INTR_ENA_SET2     0xffffffff
#define  VTSS_X_CPU_INTR_ENA_SET2_INTR_ENA_SET2(x)  (x)


/**
 * \brief Currently active interrupt sources
 *
 * \details
 * Register: \a CPU:INTR:INTR_IDENT
 */
#define VTSS_CPU_INTR_IDENT                  VTSS_IOREG(VTSS_TO_CPU,0x65)

/**
 * \brief
 * Shows the currently active interrupt sources. For interrupt sources that
 * are not bypassed this register is a result of AND'ing INTR_STICKY with
 * INTR_ENA.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_IDENT . INTR_IDENT
 */
#define  VTSS_F_CPU_INTR_IDENT_INTR_IDENT(x)  (x)
#define  VTSS_M_CPU_INTR_IDENT_INTR_IDENT     0xffffffff
#define  VTSS_X_CPU_INTR_IDENT_INTR_IDENT(x)  (x)


/**
 * \brief Currently active interrupt sources
 *
 * \details
 * Register: \a CPU:INTR:INTR_IDENT1
 */
#define VTSS_CPU_INTR_IDENT1                 VTSS_IOREG(VTSS_TO_CPU,0x66)

/**
 * \brief
 * Bit 32-63 of field INTR_IDENT.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_IDENT1 . INTR_IDENT1
 */
#define  VTSS_F_CPU_INTR_IDENT1_INTR_IDENT1(x)  (x)
#define  VTSS_M_CPU_INTR_IDENT1_INTR_IDENT1     0xffffffff
#define  VTSS_X_CPU_INTR_IDENT1_INTR_IDENT1(x)  (x)


/**
 * \brief Currently active interrupt sources
 *
 * \details
 * Register: \a CPU:INTR:INTR_IDENT2
 */
#define VTSS_CPU_INTR_IDENT2                 VTSS_IOREG(VTSS_TO_CPU,0x67)

/**
 * \brief
 * Bit 64-95 of field INTR_IDENT.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_IDENT2 . INTR_IDENT2
 */
#define  VTSS_F_CPU_INTR_IDENT2_INTR_IDENT2(x)  (x)
#define  VTSS_M_CPU_INTR_IDENT2_INTR_IDENT2     0xffffffff
#define  VTSS_X_CPU_INTR_IDENT2_INTR_IDENT2(x)  (x)


/**
 * \brief Mapping of source to destination interrupts
 *
 * \details
 * Replicated per destination interrupt.
 *
 * Register: \a CPU:INTR:DST_INTR_MAP
 *
 * @param ri Replicator: x_VCORE5_INTR_DST_CNT (??), 0-8
 */
#define VTSS_CPU_DST_INTR_MAP(ri)            VTSS_IOREG(VTSS_TO_CPU,0x68 + (ri))

/**
 * \brief
 * Set to enable mapping of individual interrupt sources to interrupt
 * destinations. This register is replicated once for each destination
 * interrupt.
 *
 * \details
 * Field: ::VTSS_CPU_DST_INTR_MAP . DST_INTR_MAP
 */
#define  VTSS_F_CPU_DST_INTR_MAP_DST_INTR_MAP(x)  (x)
#define  VTSS_M_CPU_DST_INTR_MAP_DST_INTR_MAP     0xffffffff
#define  VTSS_X_CPU_DST_INTR_MAP_DST_INTR_MAP(x)  (x)


/**
 * \brief Mapping of source to destination interrupts
 *
 * \details
 * Replicated per destination interrupt.
 *
 * Register: \a CPU:INTR:DST_INTR_MAP1
 *
 * @param ri Replicator: x_VCORE5_INTR_DST_CNT (??), 0-8
 */
#define VTSS_CPU_DST_INTR_MAP1(ri)           VTSS_IOREG(VTSS_TO_CPU,0x71 + (ri))

/**
 * \brief
 * Bit 32-63 of field DST_INTR_MAP.
 *
 * \details
 * Field: ::VTSS_CPU_DST_INTR_MAP1 . DST_INTR_MAP1
 */
#define  VTSS_F_CPU_DST_INTR_MAP1_DST_INTR_MAP1(x)  (x)
#define  VTSS_M_CPU_DST_INTR_MAP1_DST_INTR_MAP1     0xffffffff
#define  VTSS_X_CPU_DST_INTR_MAP1_DST_INTR_MAP1(x)  (x)


/**
 * \brief Mapping of source to destination interrupts
 *
 * \details
 * Replicated per destination interrupt.
 *
 * Register: \a CPU:INTR:DST_INTR_MAP2
 *
 * @param ri Replicator: x_VCORE5_INTR_DST_CNT (??), 0-8
 */
#define VTSS_CPU_DST_INTR_MAP2(ri)           VTSS_IOREG(VTSS_TO_CPU,0x7a + (ri))

/**
 * \brief
 * Bit 64-95 of field DST_INTR_MAP.
 *
 * \details
 * Field: ::VTSS_CPU_DST_INTR_MAP2 . DST_INTR_MAP2
 */
#define  VTSS_F_CPU_DST_INTR_MAP2_DST_INTR_MAP2(x)  (x)
#define  VTSS_M_CPU_DST_INTR_MAP2_DST_INTR_MAP2     0xffffffff
#define  VTSS_X_CPU_DST_INTR_MAP2_DST_INTR_MAP2(x)  (x)


/**
 * \brief Currently active interrupt sources per destination
 *
 * \details
 * Replicated per destination interrupt.
 *
 * Register: \a CPU:INTR:DST_INTR_IDENT
 *
 * @param ri Replicator: x_VCORE5_INTR_DST_CNT (??), 0-8
 */
#define VTSS_CPU_DST_INTR_IDENT(ri)          VTSS_IOREG(VTSS_TO_CPU,0x83 + (ri))

/**
 * \brief
 * Shows the currently active interrupt sources per destination interrupt.
 * The contents of this register is equal to INTR_IDENT AND'ed with the
 * corresponding DST_INTR_MAP.If any bit is set in this register the
 * corresponding destination interrupt is asserted.
 *
 * \details
 * Field: ::VTSS_CPU_DST_INTR_IDENT . DST_INTR_IDENT
 */
#define  VTSS_F_CPU_DST_INTR_IDENT_DST_INTR_IDENT(x)  (x)
#define  VTSS_M_CPU_DST_INTR_IDENT_DST_INTR_IDENT     0xffffffff
#define  VTSS_X_CPU_DST_INTR_IDENT_DST_INTR_IDENT(x)  (x)


/**
 * \brief Currently active interrupt sources per destination
 *
 * \details
 * Replicated per destination interrupt.
 *
 * Register: \a CPU:INTR:DST_INTR_IDENT1
 *
 * @param ri Replicator: x_VCORE5_INTR_DST_CNT (??), 0-8
 */
#define VTSS_CPU_DST_INTR_IDENT1(ri)         VTSS_IOREG(VTSS_TO_CPU,0x8c + (ri))

/**
 * \brief
 * Bit 32-63 of field DST_INTR_IDENT.
 *
 * \details
 * Field: ::VTSS_CPU_DST_INTR_IDENT1 . DST_INTR_IDENT1
 */
#define  VTSS_F_CPU_DST_INTR_IDENT1_DST_INTR_IDENT1(x)  (x)
#define  VTSS_M_CPU_DST_INTR_IDENT1_DST_INTR_IDENT1     0xffffffff
#define  VTSS_X_CPU_DST_INTR_IDENT1_DST_INTR_IDENT1(x)  (x)


/**
 * \brief Currently active interrupt sources per destination
 *
 * \details
 * Replicated per destination interrupt.
 *
 * Register: \a CPU:INTR:DST_INTR_IDENT2
 *
 * @param ri Replicator: x_VCORE5_INTR_DST_CNT (??), 0-8
 */
#define VTSS_CPU_DST_INTR_IDENT2(ri)         VTSS_IOREG(VTSS_TO_CPU,0x95 + (ri))

/**
 * \brief
 * Bit 64-95 of field DST_INTR_IDENT.
 *
 * \details
 * Field: ::VTSS_CPU_DST_INTR_IDENT2 . DST_INTR_IDENT2
 */
#define  VTSS_F_CPU_DST_INTR_IDENT2_DST_INTR_IDENT2(x)  (x)
#define  VTSS_M_CPU_DST_INTR_IDENT2_DST_INTR_IDENT2     0xffffffff
#define  VTSS_X_CPU_DST_INTR_IDENT2_DST_INTR_IDENT2(x)  (x)


/**
 * \brief External source interrupt polarity
 *
 * \details
 * Register: \a CPU:INTR:EXT_SRC_INTR_POL
 */
#define VTSS_CPU_EXT_SRC_INTR_POL            VTSS_IOREG(VTSS_TO_CPU,0x9e)

/**
 * \brief
 * Set individual bits in this register to configure polarity of the
 * corresponding external source interrupt.
 *
 * \details
 * 0: External interrupt input is active low
 * 1: External interrupt input is active high
 *
 * Field: ::VTSS_CPU_EXT_SRC_INTR_POL . EXT_SRC_INTR_POL
 */
#define  VTSS_F_CPU_EXT_SRC_INTR_POL_EXT_SRC_INTR_POL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CPU_EXT_SRC_INTR_POL_EXT_SRC_INTR_POL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CPU_EXT_SRC_INTR_POL_EXT_SRC_INTR_POL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief External destination interrupt polarity
 *
 * \details
 * Register: \a CPU:INTR:EXT_DST_INTR_POL
 */
#define VTSS_CPU_EXT_DST_INTR_POL            VTSS_IOREG(VTSS_TO_CPU,0x9f)

/**
 * \brief
 * Set individual bits in this register to configure polarity of the
 * corresponding external destination interrupt.
 *
 * \details
 * 0: External interrupt output is active low
 * 1: External interrupt output is active high
 *
 * Field: ::VTSS_CPU_EXT_DST_INTR_POL . EXT_DST_INTR_POL
 */
#define  VTSS_F_CPU_EXT_DST_INTR_POL_EXT_DST_INTR_POL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CPU_EXT_DST_INTR_POL_EXT_DST_INTR_POL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CPU_EXT_DST_INTR_POL_EXT_DST_INTR_POL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief External interrupt destination output drive mode
 *
 * \details
 * Register: \a CPU:INTR:EXT_DST_INTR_DRV
 */
#define VTSS_CPU_EXT_DST_INTR_DRV            VTSS_IOREG(VTSS_TO_CPU,0xa0)

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
 * Field: ::VTSS_CPU_EXT_DST_INTR_DRV . EXT_DST_INTR_DRV
 */
#define  VTSS_F_CPU_EXT_DST_INTR_DRV_EXT_DST_INTR_DRV(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CPU_EXT_DST_INTR_DRV_EXT_DST_INTR_DRV     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CPU_EXT_DST_INTR_DRV_EXT_DST_INTR_DRV(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Device interrupt polarity
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_POL
 */
#define VTSS_CPU_DEV_INTR_POL                VTSS_IOREG(VTSS_TO_CPU,0xa1)

/**
 * \brief
 * Set individual bits in this register to configure polarity of the
 * corresponding device interrupt.
 *
 * \details
 * 0: Device interrupt is active low
 * 1: Device interrupt is active high
 *
 * Field: ::VTSS_CPU_DEV_INTR_POL . DEV_INTR_POL
 */
#define  VTSS_F_CPU_DEV_INTR_POL_DEV_INTR_POL(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_CPU_DEV_INTR_POL_DEV_INTR_POL     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_CPU_DEV_INTR_POL_DEV_INTR_POL(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Device interrupt raw status
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_RAW
 */
#define VTSS_CPU_DEV_INTR_RAW                VTSS_IOREG(VTSS_TO_CPU,0xa2)

/**
 * \brief
 * Shows the current value of individual device interrupt sources. All
 * sources are active high (sources have been corrected for polarity as
 * configured in DEV_INTR_POL).
 *
 * \details
 * Field: ::VTSS_CPU_DEV_INTR_RAW . DEV_INTR_RAW
 */
#define  VTSS_F_CPU_DEV_INTR_RAW_DEV_INTR_RAW(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_CPU_DEV_INTR_RAW_DEV_INTR_RAW     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_CPU_DEV_INTR_RAW_DEV_INTR_RAW(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Device interrupt trigger mode
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_TRIGGER
 *
 * @param ri Register: DEV_INTR_TRIGGER (??), 0-1
 */
#define VTSS_CPU_DEV_INTR_TRIGGER(ri)        VTSS_IOREG(VTSS_TO_CPU,0xa3 + (ri))

/**
 * \brief
 * Configure trigger mode of individual device interrupt sources. The
 * trigger mode determines how the value of the DEV_INTR_RAW register is
 * transferred to the DEV_INTR_STICKY register. This register is
 * replicated, the first replication controls bit 0 in the encoding, the
 * second replication controls bit 1 in the encoding. I.e. to configure
 * edge-triggered interrupt for device 3; set DEV_INTR_TRIGGER[0][3]='1'
 * and DEV_INTR_TRIGGER[1][3]='0'.For level-triggered interrupts
 * DEV_INTR_STICKY is set for as long as the corresponding bit in
 * DEV_INTR_RAW is high - i.e. is not possible to clear a bit in
 * DEV_INTR_STICKY until the corresponding DEV_INTR_RAW is zero.For
 * edge-triggeded interrupts DEV_INTR_STICKY is set when the corresponding
 * bit in DEV_INTR_RAW changes value.For falling-edge-triggeded interrupts
 * DEV_INTR_STICKY is set when the corresponding bit in DEV_INTR_RAW
 * changes from '1' to '0'.For rising-edge-triggeded interrupts
 * DEV_INTR_STICKY is set when the corresponding bit in DEV_INTR_RAW
 * changes from '0' to '1'.
 *
 * \details
 * 0: Interrupt is level-activated
 * 1: Interrupt is edge-triggered
 * 2: Interrupt is falling-edge-triggered
 * 3: Interrupt is rising-edge-triggered
 *
 * Field: ::VTSS_CPU_DEV_INTR_TRIGGER . DEV_INTR_TRIGGER
 */
#define  VTSS_F_CPU_DEV_INTR_TRIGGER_DEV_INTR_TRIGGER(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_CPU_DEV_INTR_TRIGGER_DEV_INTR_TRIGGER     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_CPU_DEV_INTR_TRIGGER_DEV_INTR_TRIGGER(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Device interrupt sticky status
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_STICKY
 */
#define VTSS_CPU_DEV_INTR_STICKY             VTSS_IOREG(VTSS_TO_CPU,0xa5)

/**
 * \brief
 * This register is set based on device interrupt sourec events. See
 * DEV_INTR_TRIGGER for more information. Bits in this register remains set
 * until cleared by software.
 *
 * \details
 * Field: ::VTSS_CPU_DEV_INTR_STICKY . DEV_INTR_STICKY
 */
#define  VTSS_F_CPU_DEV_INTR_STICKY_DEV_INTR_STICKY(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_CPU_DEV_INTR_STICKY_DEV_INTR_STICKY     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_CPU_DEV_INTR_STICKY_DEV_INTR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Device interrupt bypass enable
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_BYPASS
 */
#define VTSS_CPU_DEV_INTR_BYPASS             VTSS_IOREG(VTSS_TO_CPU,0xa6)

/**
 * \brief
 * This register allows bypass of DEV_INTR_STICKY for individual device
 * interrupt sources. When a device interrupt source is in bypass mode then
 * DEV_INTR_RAW is used instead of DEV_INTR_STICKY.See note on bypass in
 * INTR_BYPASS.
 *
 * \details
 * Field: ::VTSS_CPU_DEV_INTR_BYPASS . DEV_INTR_BYPASS
 */
#define  VTSS_F_CPU_DEV_INTR_BYPASS_DEV_INTR_BYPASS(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_CPU_DEV_INTR_BYPASS_DEV_INTR_BYPASS     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_CPU_DEV_INTR_BYPASS_DEV_INTR_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Device interrupt enable
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_ENA
 */
#define VTSS_CPU_DEV_INTR_ENA                VTSS_IOREG(VTSS_TO_CPU,0xa7)

/**
 * \brief
 * Set to enable propagation of individual device interrupt sources to the
 * main interrupt controller.
 *
 * \details
 * Field: ::VTSS_CPU_DEV_INTR_ENA . DEV_INTR_ENA
 */
#define  VTSS_F_CPU_DEV_INTR_ENA_DEV_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_CPU_DEV_INTR_ENA_DEV_INTR_ENA     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_CPU_DEV_INTR_ENA_DEV_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Currently active device interrupts
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_IDENT
 */
#define VTSS_CPU_DEV_INTR_IDENT              VTSS_IOREG(VTSS_TO_CPU,0xa8)

/**
 * \brief
 * Shows the currently active interrupt sources. For interrupt sources that
 * are not bypassed this register is a result of AND'ing DEV_INTR_STICKY
 * with DEV_INTR_ENA.
 *
 * \details
 * Field: ::VTSS_CPU_DEV_INTR_IDENT . DEV_INTR_IDENT
 */
#define  VTSS_F_CPU_DEV_INTR_IDENT_DEV_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_CPU_DEV_INTR_IDENT_DEV_INTR_IDENT     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_CPU_DEV_INTR_IDENT_DEV_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Configuration of memory mapped PCIe MSI-X message generation
 *
 * \details
 * Register: \a CPU:INTR:MSIX_CFG
 */
#define VTSS_CPU_MSIX_CFG                    VTSS_IOREG(VTSS_TO_CPU,0xa9)

/**
 * \brief
 * Enable generation of memory mapped MSI-X messages.
 *
 * \details
 * Field: ::VTSS_CPU_MSIX_CFG . MSIX_ENA
 */
#define  VTSS_F_CPU_MSIX_CFG_MSIX_ENA(x)      VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_CPU_MSIX_CFG_MSIX_ENA         VTSS_BIT(17)
#define  VTSS_X_CPU_MSIX_CFG_MSIX_ENA(x)      VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * MSIX Doorbell Traffic Class. This register determines which traffic
 * class to generate the MSI-X transaction with.
 *
 * \details
 * Field: ::VTSS_CPU_MSIX_CFG . MSIX_DOORBELL_TC
 */
#define  VTSS_F_CPU_MSIX_CFG_MSIX_DOORBELL_TC(x)  VTSS_ENCODE_BITFIELD(x,14,3)
#define  VTSS_M_CPU_MSIX_CFG_MSIX_DOORBELL_TC     VTSS_ENCODE_BITMASK(14,3)
#define  VTSS_X_CPU_MSIX_CFG_MSIX_DOORBELL_TC(x)  VTSS_EXTRACT_BITFIELD(x,14,3)

/**
 * \brief
 * MSIX Doorbell Virtual Function Active. This register determines whether
 * a Virtual Function is used to generate the MSI-X transaction.
 *
 * \details
 * Field: ::VTSS_CPU_MSIX_CFG . MSIX_DOORBELL_VF_ACTIVE
 */
#define  VTSS_F_CPU_MSIX_CFG_MSIX_DOORBELL_VF_ACTIVE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_CPU_MSIX_CFG_MSIX_DOORBELL_VF_ACTIVE  VTSS_BIT(13)
#define  VTSS_X_CPU_MSIX_CFG_MSIX_DOORBELL_VF_ACTIVE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * MSIX Doorbell Virtual Function. This register determines the Virtual
 * Function for the MSI-X transaction.
 *
 * \details
 * Field: ::VTSS_CPU_MSIX_CFG . MSIX_DOORBELL_VF
 */
#define  VTSS_F_CPU_MSIX_CFG_MSIX_DOORBELL_VF(x)  VTSS_ENCODE_BITFIELD(x,5,8)
#define  VTSS_M_CPU_MSIX_CFG_MSIX_DOORBELL_VF     VTSS_ENCODE_BITMASK(5,8)
#define  VTSS_X_CPU_MSIX_CFG_MSIX_DOORBELL_VF(x)  VTSS_EXTRACT_BITFIELD(x,5,8)

/**
 * \brief
 * MSIX Doorbell Physical Function. This register determines the Physical
 * Function for the MSI-X transaction.
 *
 * \details
 * Field: ::VTSS_CPU_MSIX_CFG . MSIX_DOORBELL_PF
 */
#define  VTSS_F_CPU_MSIX_CFG_MSIX_DOORBELL_PF(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_CPU_MSIX_CFG_MSIX_DOORBELL_PF     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_CPU_MSIX_CFG_MSIX_DOORBELL_PF(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief Address for MSI-X messages.
 *
 * \details
 * Register: \a CPU:INTR:MSIX_DOORBELL_ADDR
 */
#define VTSS_CPU_MSIX_DOORBELL_ADDR          VTSS_IOREG(VTSS_TO_CPU,0xaa)

/**
 * \brief
 * Address for MSI-X messages.Relevant
 * fields:PCIE_DBI:PF0_PORT_LOGIC:MSIX_ADDRESS_MATCH_LOW_OFFPCIE_DBI:PF0_PO
 * RT_LOGIC:MSIX_ADDRESS_MATCH_HIGH_OFF.MSIX_ADDRESS_MATCH_HIGH
 *
 * \details
 * Field: ::VTSS_CPU_MSIX_DOORBELL_ADDR . MSIX_ADDRESS
 */
#define  VTSS_F_CPU_MSIX_DOORBELL_ADDR_MSIX_ADDRESS(x)  (x)
#define  VTSS_M_CPU_MSIX_DOORBELL_ADDR_MSIX_ADDRESS     0xffffffff
#define  VTSS_X_CPU_MSIX_DOORBELL_ADDR_MSIX_ADDRESS(x)  (x)


/**
 * \brief MSI-X interrupt pending
 *
 * \details
 * Register: \a CPU:INTR:MSIX_INTR_PENDING
 */
#define VTSS_CPU_MSIX_INTR_PENDING           VTSS_IOREG(VTSS_TO_CPU,0xab)

/**
 * \brief
 * Per interrupt indication of MSI-X message pending to be sent.
 *
 * \details
 * Field: ::VTSS_CPU_MSIX_INTR_PENDING . MSIX_INTR_PENDING
 */
#define  VTSS_F_CPU_MSIX_INTR_PENDING_MSIX_INTR_PENDING(x)  (x)
#define  VTSS_M_CPU_MSIX_INTR_PENDING_MSIX_INTR_PENDING     0xffffffff
#define  VTSS_X_CPU_MSIX_INTR_PENDING_MSIX_INTR_PENDING(x)  (x)


/**
 * \brief MSI-X interrupt pending
 *
 * \details
 * Register: \a CPU:INTR:MSIX_INTR_PENDING1
 */
#define VTSS_CPU_MSIX_INTR_PENDING1          VTSS_IOREG(VTSS_TO_CPU,0xac)

/**
 * \brief
 * Bit 32-63 of field MSIX_INTR_PENDING.
 *
 * \details
 * Field: ::VTSS_CPU_MSIX_INTR_PENDING1 . MSIX_INTR_PENDING1
 */
#define  VTSS_F_CPU_MSIX_INTR_PENDING1_MSIX_INTR_PENDING1(x)  (x)
#define  VTSS_M_CPU_MSIX_INTR_PENDING1_MSIX_INTR_PENDING1     0xffffffff
#define  VTSS_X_CPU_MSIX_INTR_PENDING1_MSIX_INTR_PENDING1(x)  (x)


/**
 * \brief MSI-X interrupt pending
 *
 * \details
 * Register: \a CPU:INTR:MSIX_INTR_PENDING2
 */
#define VTSS_CPU_MSIX_INTR_PENDING2          VTSS_IOREG(VTSS_TO_CPU,0xad)

/**
 * \brief
 * Bit 64-95 of field MSIX_INTR_PENDING.
 *
 * \details
 * Field: ::VTSS_CPU_MSIX_INTR_PENDING2 . MSIX_INTR_PENDING2
 */
#define  VTSS_F_CPU_MSIX_INTR_PENDING2_MSIX_INTR_PENDING2(x)  (x)
#define  VTSS_M_CPU_MSIX_INTR_PENDING2_MSIX_INTR_PENDING2     0xffffffff
#define  VTSS_X_CPU_MSIX_INTR_PENDING2_MSIX_INTR_PENDING2(x)  (x)

/**
 * Register Group: \a CPU:DDRCTRL
 *
 * DDR3/4 memory controller + PHY config status
 */


/**
 * \brief DDR Controller/Phy clock configuration
 *
 * \details
 * Register: \a CPU:DDRCTRL:DDRCTRL_CLK
 */
#define VTSS_CPU_DDRCTRL_CLK                 VTSS_IOREG(VTSS_TO_CPU,0xae)

/**
 * \brief
 * Enable ddrc_core_clk.
 *
 * \details
 * 0 : clock disable
 * 1 : clock enable
 *
 * Field: ::VTSS_CPU_DDRCTRL_CLK . DDR_CLK_ENA
 */
#define  VTSS_F_CPU_DDRCTRL_CLK_DDR_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_DDRCTRL_CLK_DDR_CLK_ENA   VTSS_BIT(0)
#define  VTSS_X_CPU_DDRCTRL_CLK_DDR_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Enable AXI_0 clock of DDR controller.
 *
 * \details
 * 0 : clock disable
 * 1 : clock enable
 *
 * Field: ::VTSS_CPU_DDRCTRL_CLK . DDR_AXI0_CLK_ENA
 */
#define  VTSS_F_CPU_DDRCTRL_CLK_DDR_AXI0_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_DDRCTRL_CLK_DDR_AXI0_CLK_ENA  VTSS_BIT(1)
#define  VTSS_X_CPU_DDRCTRL_CLK_DDR_AXI0_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable AXI_1 clock of DDR controller.
 *
 * \details
 * 0 : clock disable
 * 1 : clock enable
 *
 * Field: ::VTSS_CPU_DDRCTRL_CLK . DDR_AXI1_CLK_ENA
 */
#define  VTSS_F_CPU_DDRCTRL_CLK_DDR_AXI1_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_DDRCTRL_CLK_DDR_AXI1_CLK_ENA  VTSS_BIT(2)
#define  VTSS_X_CPU_DDRCTRL_CLK_DDR_AXI1_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable AXI_2 clock of DDR controller.
 *
 * \details
 * 0 : clock disable
 * 1 : clock enable
 *
 * Field: ::VTSS_CPU_DDRCTRL_CLK . DDR_AXI2_CLK_ENA
 */
#define  VTSS_F_CPU_DDRCTRL_CLK_DDR_AXI2_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_DDRCTRL_CLK_DDR_AXI2_CLK_ENA  VTSS_BIT(3)
#define  VTSS_X_CPU_DDRCTRL_CLK_DDR_AXI2_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable APB clock of DDR controller.
 *
 * \details
 * 0 : clock disable
 * 1 : clock enable
 *
 * Field: ::VTSS_CPU_DDRCTRL_CLK . DDR_APB_CLK_ENA
 */
#define  VTSS_F_CPU_DDRCTRL_CLK_DDR_APB_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CPU_DDRCTRL_CLK_DDR_APB_CLK_ENA  VTSS_BIT(4)
#define  VTSS_X_CPU_DDRCTRL_CLK_DDR_APB_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable PUB/PHY controller clock.
 *
 * \details
 * 0 : clock disable
 * 1 : clock enable
 *
 * Field: ::VTSS_CPU_DDRCTRL_CLK . DDRPHY_CTL_CLK_ENA
 */
#define  VTSS_F_CPU_DDRCTRL_CLK_DDRPHY_CTL_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_CPU_DDRCTRL_CLK_DDRPHY_CTL_CLK_ENA  VTSS_BIT(5)
#define  VTSS_X_CPU_DDRCTRL_CLK_DDRPHY_CTL_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Enable APB clock of DDR PHY.
 *
 * \details
 * 0 : clock disable
 * 1 : clock enable
 *
 * Field: ::VTSS_CPU_DDRCTRL_CLK . DDRPHY_APB_CLK_ENA
 */
#define  VTSS_F_CPU_DDRCTRL_CLK_DDRPHY_APB_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_CPU_DDRCTRL_CLK_DDRPHY_APB_CLK_ENA  VTSS_BIT(6)
#define  VTSS_X_CPU_DDRCTRL_CLK_DDRPHY_APB_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * When enabled, it connects the memories of the DDR controller to the ram
 * ring.
 *
 * \details
 * 1: Enabled
 * 0: Disabled
 *
 * Field: ::VTSS_CPU_DDRCTRL_CLK . RAM_RING_ENA
 */
#define  VTSS_F_CPU_DDRCTRL_CLK_RAM_RING_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_CPU_DDRCTRL_CLK_RAM_RING_ENA  VTSS_BIT(7)
#define  VTSS_X_CPU_DDRCTRL_CLK_RAM_RING_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/**
 * \brief DDR Controller/Phy reset configuration
 *
 * \details
 * Register: \a CPU:DDRCTRL:DDRCTRL_RST
 */
#define VTSS_CPU_DDRCTRL_RST                 VTSS_IOREG(VTSS_TO_CPU,0xaf)

/**
 * \brief
 * Assert ddrc_core_rst. The controller registers must be configured when
 * DDR controller is in reset.
 *
 * \details
 * 0 : No Reset
 * 1 : Reset.
 *
 * Field: ::VTSS_CPU_DDRCTRL_RST . DDRC_RST
 */
#define  VTSS_F_CPU_DDRCTRL_RST_DDRC_RST(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_DDRCTRL_RST_DDRC_RST      VTSS_BIT(0)
#define  VTSS_X_CPU_DDRCTRL_RST_DDRC_RST(x)   VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Assert AXI_0 reset of DDR controller. The controller registers must be
 * configured when AXI channel of DDR controller is in reset.
 *
 * \details
 * 0 : No Reset
 * 1 : Reset.
 *
 * Field: ::VTSS_CPU_DDRCTRL_RST . DDR_AXI0_RST
 */
#define  VTSS_F_CPU_DDRCTRL_RST_DDR_AXI0_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_DDRCTRL_RST_DDR_AXI0_RST  VTSS_BIT(1)
#define  VTSS_X_CPU_DDRCTRL_RST_DDR_AXI0_RST(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Assert AXI_1 reset of DDR controller. The controller registers must be
 * configured when AXI channel of DDR controller is in reset.
 *
 * \details
 * 0 : No Reset
 * 1 : Reset.
 *
 * Field: ::VTSS_CPU_DDRCTRL_RST . DDR_AXI1_RST
 */
#define  VTSS_F_CPU_DDRCTRL_RST_DDR_AXI1_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_DDRCTRL_RST_DDR_AXI1_RST  VTSS_BIT(2)
#define  VTSS_X_CPU_DDRCTRL_RST_DDR_AXI1_RST(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Assert AXI_2 reset of DDR controller. The controller registers must be
 * configured when AXI channel of DDR controller is in reset.
 *
 * \details
 * 0 : No Reset
 * 1 : Reset.
 *
 * Field: ::VTSS_CPU_DDRCTRL_RST . DDR_AXI2_RST
 */
#define  VTSS_F_CPU_DDRCTRL_RST_DDR_AXI2_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_DDRCTRL_RST_DDR_AXI2_RST  VTSS_BIT(3)
#define  VTSS_X_CPU_DDRCTRL_RST_DDR_AXI2_RST(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Assert APB reset of DDR controller.
 *
 * \details
 * 0 : No Reset
 * 1 : Reset.
 *
 * Field: ::VTSS_CPU_DDRCTRL_RST . DDR_APB_RST
 */
#define  VTSS_F_CPU_DDRCTRL_RST_DDR_APB_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CPU_DDRCTRL_RST_DDR_APB_RST   VTSS_BIT(4)
#define  VTSS_X_CPU_DDRCTRL_RST_DDR_APB_RST(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Assert DDR PHY PUB/PHY reset
 *
 * \details
 * 0 : No Reset
 * 1 : Reset.
 *
 * Field: ::VTSS_CPU_DDRCTRL_RST . DDRPHY_CTL_RST
 */
#define  VTSS_F_CPU_DDRCTRL_RST_DDRPHY_CTL_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_CPU_DDRCTRL_RST_DDRPHY_CTL_RST  VTSS_BIT(5)
#define  VTSS_X_CPU_DDRCTRL_RST_DDRPHY_CTL_RST(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Assert FPGA DDR PHY soft reset. This reset is used by the FPGA DDR PHY
 * to reset all flops on the DFICLK and FCLK clock domains with the
 * exception of the control/status registers. This allows the user to
 * essentially re-start the PHY without the need to refresh the registers.
 *
 * \details
 * 0 : No Reset
 * 1 : Reset.
 *
 * Field: ::VTSS_CPU_DDRCTRL_RST . FPGA_DDRPHY_SOFT_RST
 */
#define  VTSS_F_CPU_DDRCTRL_RST_FPGA_DDRPHY_SOFT_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_CPU_DDRCTRL_RST_FPGA_DDRPHY_SOFT_RST  VTSS_BIT(6)
#define  VTSS_X_CPU_DDRCTRL_RST_FPGA_DDRPHY_SOFT_RST(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Assert APB reset of DDR PHY.
 *
 * \details
 * 0 : No Reset
 * 1 : Reset.
 *
 * Field: ::VTSS_CPU_DDRCTRL_RST . DDRPHY_APB_RST
 */
#define  VTSS_F_CPU_DDRCTRL_RST_DDRPHY_APB_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_CPU_DDRCTRL_RST_DDRPHY_APB_RST  VTSS_BIT(7)
#define  VTSS_X_CPU_DDRCTRL_RST_DDRPHY_APB_RST(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/**
 * \brief DDR controller interrupt raw status
 *
 * \details
 * Register: \a CPU:DDRCTRL:DDRC_INTR_RAW_STAT
 */
#define VTSS_CPU_DDRC_INTR_RAW_STAT          VTSS_IOREG(VTSS_TO_CPU,0xb0)

/**
 * \brief
 * Scrubber interrupt indicating one full address range sweep; only
 * asserted in certain conditions. Behaves identical to SBRSTAT.scrub_done
 * register.
 *
 * \details
 * 0 : Interrupt deasserted.
 * 1 : Interrupt asserted.
 *
 * Field: ::VTSS_CPU_DDRC_INTR_RAW_STAT . SBR_DONE_INTR_RAW_STAT
 */
#define  VTSS_F_CPU_DDRC_INTR_RAW_STAT_SBR_DONE_INTR_RAW_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_DDRC_INTR_RAW_STAT_SBR_DONE_INTR_RAW_STAT  VTSS_BIT(0)
#define  VTSS_X_CPU_DDRC_INTR_RAW_STAT_SBR_DONE_INTR_RAW_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * This interrupt is asserted when a correctable ECC error is detected.
 * This interrupt status is generated by doing a logical OR operation of
 * both the interrupt output ports ecc_corrected_err_intr (enabled by
 * setting DDR_UMCTL2::ECCCTL.ecc_corrected_err_intr_en = 1) and
 * ecc_corrected_err_intr_fault (asserted irrespective of the setting of
 * the enable bit) of the DWC DDR uMCTL2 IP core.
 *
 * \details
 * 0 : Interrupt deasserted.
 * 1 : Interrupt asserted.
 *
 * Field: ::VTSS_CPU_DDRC_INTR_RAW_STAT . ECC_CORRECTED_ERR_INTR_RAW_STAT
 */
#define  VTSS_F_CPU_DDRC_INTR_RAW_STAT_ECC_CORRECTED_ERR_INTR_RAW_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_DDRC_INTR_RAW_STAT_ECC_CORRECTED_ERR_INTR_RAW_STAT  VTSS_BIT(1)
#define  VTSS_X_CPU_DDRC_INTR_RAW_STAT_ECC_CORRECTED_ERR_INTR_RAW_STAT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * This interrupt is asserted when a uncorrectable ECC error is detected.
 * This interrupt status is generated by doing a logical OR operation of
 * both the interrupt output ports ecc_uncorrected_err_intr (enabled by
 * setting DDR_UMCTL2::ECCCTL.ecc_uncorrected_err_intr_en = 1) and
 * ecc_uncorrected_err_intr_fault (asserted irrespective of the setting of
 * the enable bit) of the DWC DDR uMCTL2 IP core.
 *
 * \details
 * 0 : Interrupt deasserted.
 * 1 : Interrupt asserted.
 *
 * Field: ::VTSS_CPU_DDRC_INTR_RAW_STAT . ECC_UNCORRECTED_ERR_INTR_RAW_STAT
 */
#define  VTSS_F_CPU_DDRC_INTR_RAW_STAT_ECC_UNCORRECTED_ERR_INTR_RAW_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_DDRC_INTR_RAW_STAT_ECC_UNCORRECTED_ERR_INTR_RAW_STAT  VTSS_BIT(2)
#define  VTSS_X_CPU_DDRC_INTR_RAW_STAT_ECC_UNCORRECTED_ERR_INTR_RAW_STAT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * This interrupt is asserted when number of ECC error within a burst
 * exceeds the value set in ECCCFG1.ecc_ap_err_threshold. This interrupt
 * status is generated by doing a logical OR operation of both the
 * interrupt output ports ecc_ap_err_intr (enabled by setting
 * DDR_UMCTL2::ECCCTL.ecc_ap_err_intr_en = 1) and ecc_ap_err_intr_fault
 * (asserted irrespective of the setting of the enable bit) of the DWC DDR
 * uMCTL2 IP core.
 *
 * \details
 * 0 : Interrupt deasserted.
 * 1 : Interrupt asserted.
 *
 * Field: ::VTSS_CPU_DDRC_INTR_RAW_STAT . ECC_AP_ERR_INTR_RAW_STAT
 */
#define  VTSS_F_CPU_DDRC_INTR_RAW_STAT_ECC_AP_ERR_INTR_RAW_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_DDRC_INTR_RAW_STAT_ECC_AP_ERR_INTR_RAW_STAT  VTSS_BIT(3)
#define  VTSS_X_CPU_DDRC_INTR_RAW_STAT_ECC_AP_ERR_INTR_RAW_STAT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/**
 * \brief DDR controller interrupt mask register
 *
 * \details
 * Register: \a CPU:DDRCTRL:DDRC_INTR_MASK
 */
#define VTSS_CPU_DDRC_INTR_MASK              VTSS_IOREG(VTSS_TO_CPU,0xb1)

/**
 * \brief
 * Mask for Scrubber done interrupt.
 *
 * \details
 * 0 : Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_CPU_DDRC_INTR_MASK . SBR_DONE_INTR_MASK
 */
#define  VTSS_F_CPU_DDRC_INTR_MASK_SBR_DONE_INTR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_DDRC_INTR_MASK_SBR_DONE_INTR_MASK  VTSS_BIT(0)
#define  VTSS_X_CPU_DDRC_INTR_MASK_SBR_DONE_INTR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Mask for a correctable ECC error interrupt
 *
 * \details
 * 0 : Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_CPU_DDRC_INTR_MASK . ECC_CORRECTED_ERR_INTR_MASK
 */
#define  VTSS_F_CPU_DDRC_INTR_MASK_ECC_CORRECTED_ERR_INTR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_DDRC_INTR_MASK_ECC_CORRECTED_ERR_INTR_MASK  VTSS_BIT(1)
#define  VTSS_X_CPU_DDRC_INTR_MASK_ECC_CORRECTED_ERR_INTR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Mask for an uncorrectable ECC error interrupt
 *
 * \details
 * 0 : Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_CPU_DDRC_INTR_MASK . ECC_UNCORRECTED_ERR_INTR_MASK
 */
#define  VTSS_F_CPU_DDRC_INTR_MASK_ECC_UNCORRECTED_ERR_INTR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_DDRC_INTR_MASK_ECC_UNCORRECTED_ERR_INTR_MASK  VTSS_BIT(2)
#define  VTSS_X_CPU_DDRC_INTR_MASK_ECC_UNCORRECTED_ERR_INTR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Mask for an ECC Address Parity error interrupt
 *
 * \details
 * 0 : Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_CPU_DDRC_INTR_MASK . ECC_AP_ERR_INTR_MASK
 */
#define  VTSS_F_CPU_DDRC_INTR_MASK_ECC_AP_ERR_INTR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_DDRC_INTR_MASK_ECC_AP_ERR_INTR_MASK  VTSS_BIT(3)
#define  VTSS_X_CPU_DDRC_INTR_MASK_ECC_AP_ERR_INTR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/**
 * \brief DDR controller interrupt masked status
 *
 * \details
 * Register: \a CPU:DDRCTRL:DDRC_INTR_MASKED_STAT
 */
#define VTSS_CPU_DDRC_INTR_MASKED_STAT       VTSS_IOREG(VTSS_TO_CPU,0xb2)

/**
 * \brief
 * Status for Scrubber done interrupt after taking interrupt mask into
 * account.
 *
 * \details
 * 0 : Interrupt deasserted.
 * 1 : Interrupt asserted.
 *
 * Field: ::VTSS_CPU_DDRC_INTR_MASKED_STAT . SBR_DONE_INTR_STAT
 */
#define  VTSS_F_CPU_DDRC_INTR_MASKED_STAT_SBR_DONE_INTR_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_DDRC_INTR_MASKED_STAT_SBR_DONE_INTR_STAT  VTSS_BIT(0)
#define  VTSS_X_CPU_DDRC_INTR_MASKED_STAT_SBR_DONE_INTR_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Status for a correctable ECC error interrupt after taking interrupt mask
 * into account.This interrupt status is generated by doing a logical OR
 * operation of both the interrupt output ports ecc_corrected_err_intr
 * (enabled by setting DDR_UMCTL2::ECCCTL.ecc_corrected_err_intr_en = 1)
 * and ecc_corrected_err_intr_fault (asserted irrespective of the setting
 * of the enable bit) of the DWC DDR uMCTL2 IP core.
 *
 * \details
 * 0 : Interrupt deasserted.
 * 1 : Interrupt asserted.
 *
 * Field: ::VTSS_CPU_DDRC_INTR_MASKED_STAT . ECC_CORRECTED_ERR_INTR_STAT
 */
#define  VTSS_F_CPU_DDRC_INTR_MASKED_STAT_ECC_CORRECTED_ERR_INTR_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_DDRC_INTR_MASKED_STAT_ECC_CORRECTED_ERR_INTR_STAT  VTSS_BIT(1)
#define  VTSS_X_CPU_DDRC_INTR_MASKED_STAT_ECC_CORRECTED_ERR_INTR_STAT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Status for an Uncorrectable ECC error interrupt after taking interrupt
 * mask into account.This interrupt status is generated by doing a logical
 * OR operation of both the interrupt output ports ecc_uncorrected_err_intr
 * (enabled by setting DDR_UMCTL2::ECCCTL.ecc_uncorrected_err_intr_en = 1)
 * and ecc_uncorrected_err_intr_fault (asserted irrespective of the setting
 * of the enable bit) of the DWC DDR uMCTL2 IP core.
 *
 * \details
 * 0 : Interrupt deasserted.
 * 1 : Interrupt asserted.
 *
 * Field: ::VTSS_CPU_DDRC_INTR_MASKED_STAT . ECC_UNCORRECTED_ERR_INTR_STAT
 */
#define  VTSS_F_CPU_DDRC_INTR_MASKED_STAT_ECC_UNCORRECTED_ERR_INTR_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_DDRC_INTR_MASKED_STAT_ECC_UNCORRECTED_ERR_INTR_STAT  VTSS_BIT(2)
#define  VTSS_X_CPU_DDRC_INTR_MASKED_STAT_ECC_UNCORRECTED_ERR_INTR_STAT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Status for an ECC Address Parity error interrupt after taking interrupt
 * mask into account.This interrupt status is generated by doing a logical
 * OR operation of both the interrupt output ports ecc_ap_err_intr (enabled
 * by setting DDR_UMCTL2::ECCCTL.ecc_ap_err_intr_en = 1) and
 * ecc_ap_err_intr_fault (asserted irrespective of the setting of the
 * enable bit) of the DWC DDR uMCTL2 IP core.
 *
 * \details
 * 0 : Interrupt deasserted.
 * 1 : Interrupt asserted.
 *
 * Field: ::VTSS_CPU_DDRC_INTR_MASKED_STAT . ECC_AP_ERR_INTR_STAT
 */
#define  VTSS_F_CPU_DDRC_INTR_MASKED_STAT_ECC_AP_ERR_INTR_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_DDRC_INTR_MASKED_STAT_ECC_AP_ERR_INTR_STAT  VTSS_BIT(3)
#define  VTSS_X_CPU_DDRC_INTR_MASKED_STAT_ECC_AP_ERR_INTR_STAT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * Register Group: \a CPU:SFR_REGS
 *
 * HSS block configuration
 */


/**
 * \brief clock gating disable configuration
 *
 * \details
 * Register: \a CPU:SFR_REGS:CLK_GATING
 */
#define VTSS_CPU_CLK_GATING                  VTSS_IOREG(VTSS_TO_CPU,0xb3)

/**
 * \brief
 *
 * Clock gating for UHPHS0: Clock Disbaled1: Clock Enabled
 *
 * \details
 * Field: ::VTSS_CPU_CLK_GATING . UHPHS_CLK_GATING
 */
#define  VTSS_F_CPU_CLK_GATING_UHPHS_CLK_GATING(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_CPU_CLK_GATING_UHPHS_CLK_GATING  VTSS_BIT(11)
#define  VTSS_X_CPU_CLK_GATING_UHPHS_CLK_GATING(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 *
 * Clock gating for UDPHS0: Clock Disbaled1: Clock Enabled
 *
 * \details
 * Field: ::VTSS_CPU_CLK_GATING . UDPHS_CLK_GATING
 */
#define  VTSS_F_CPU_CLK_GATING_UDPHS_CLK_GATING(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_CPU_CLK_GATING_UDPHS_CLK_GATING  VTSS_BIT(10)
#define  VTSS_X_CPU_CLK_GATING_UDPHS_CLK_GATING(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 *
 * Clock gating for MCRAMC0: Clock Disbaled1: Clock Enabled
 *
 * \details
 * Field: ::VTSS_CPU_CLK_GATING . MCRAMC_CLK_GATING
 */
#define  VTSS_F_CPU_CLK_GATING_MCRAMC_CLK_GATING(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_CPU_CLK_GATING_MCRAMC_CLK_GATING  VTSS_BIT(9)
#define  VTSS_X_CPU_CLK_GATING_MCRAMC_CLK_GATING(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 *
 * Clock gating for HMATRIX0: Clock Disbaled1: Clock Enabled
 *
 * \details
 * Field: ::VTSS_CPU_CLK_GATING . HMATRIX_CLK_GATING
 */
#define  VTSS_F_CPU_CLK_GATING_HMATRIX_CLK_GATING(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_CPU_CLK_GATING_HMATRIX_CLK_GATING  VTSS_BIT(8)
#define  VTSS_X_CPU_CLK_GATING_HMATRIX_CLK_GATING(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 *
 * Clock gating for HBRIDGE0: Clock Disbaled1: Clock EnabledClock gating
 * disable for HBRIDGE. There are 3 HBRIDGE instances and hence 3-bits for
 * configuration0th bit : HSS HBRIDGE1st bit : APB_MAIN1 HBRIDGE2nd bit :
 * APB_MAIN2 HBRIDGE3rd bit : CSS HBRIDGE
 *
 * \details
 * Field: ::VTSS_CPU_CLK_GATING . HBRIDGE_CLK_GATING
 */
#define  VTSS_F_CPU_CLK_GATING_HBRIDGE_CLK_GATING(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CPU_CLK_GATING_HBRIDGE_CLK_GATING     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CPU_CLK_GATING_HBRIDGE_CLK_GATING(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief AHBLIT2rAXI block connfiguration
 *
 * \details
 * Register: \a CPU:SFR_REGS:AHBLITE2AXI
 */
#define VTSS_CPU_AHBLITE2AXI                 VTSS_IOREG(VTSS_TO_CPU,0xb4)

/**
 * \brief
 *
 * AHBLITE2AXI IP configuration. HSS to DDR path where AHB to AXI bridge is
 * used. 0: False1:True
 *
 * \details
 * Field: ::VTSS_CPU_AHBLITE2AXI . AHBLITE2AXI_PFETCH8
 */
#define  VTSS_F_CPU_AHBLITE2AXI_AHBLITE2AXI_PFETCH8(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_AHBLITE2AXI_AHBLITE2AXI_PFETCH8  VTSS_BIT(0)
#define  VTSS_X_CPU_AHBLITE2AXI_AHBLITE2AXI_PFETCH8(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TZAESB block configuration
 *
 * \details
 * Register: \a CPU:SFR_REGS:TZAESB
 */
#define VTSS_CPU_TZAESB                      VTSS_IOREG(VTSS_TO_CPU,0xb5)

/**
 * \brief
 *
 * TZAESB lite enable configuration0: not enabled1: enabled
 *
 * \details
 * Field: ::VTSS_CPU_TZAESB . TZAESB_LITE_EN
 */
#define  VTSS_F_CPU_TZAESB_TZAESB_LITE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_TZAESB_TZAESB_LITE_EN     VTSS_BIT(0)
#define  VTSS_X_CPU_TZAESB_TZAESB_LITE_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief MACN configuration
 *
 * \details
 * Register: \a CPU:SFR_REGS:MCAN
 */
#define VTSS_CPU_MCAN                        VTSS_IOREG(VTSS_TO_CPU,0xb6)

/**
 * \brief
 *
 * MCAN ahb cachable configuration. There are 4 MCANs in HSS block0: not
 * cachable1: cachable
 *
 * \details
 * Field: ::VTSS_CPU_MCAN . MCAN_AHB_CACHABLE
 */
#define  VTSS_F_CPU_MCAN_MCAN_AHB_CACHABLE(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_CPU_MCAN_MCAN_AHB_CACHABLE     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_CPU_MCAN_MCAN_AHB_CACHABLE(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 *
 * MCAN ahb buffarable configuration. There are 4 MCANs in HSS block0: not
 * bufferable1:bufferable
 *
 * \details
 * Field: ::VTSS_CPU_MCAN . MCAN_AHB_BUFFERABLE
 */
#define  VTSS_F_CPU_MCAN_MCAN_AHB_BUFFERABLE(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CPU_MCAN_MCAN_AHB_BUFFERABLE     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CPU_MCAN_MCAN_AHB_BUFFERABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief HICM configirayion
 *
 * \details
 * Register: \a CPU:SFR_REGS:HICM
 */
#define VTSS_CPU_HICM                        VTSS_IOREG(VTSS_TO_CPU,0xb7)

/**
 * \brief
 *
 * HICM ahb cachable configuration. HICM instance in HSS block0: not
 * cachable1: cachable
 *
 * \details
 * Field: ::VTSS_CPU_HICM . HICM_AHB_CACHABLE
 */
#define  VTSS_F_CPU_HICM_HICM_AHB_CACHABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_CPU_HICM_HICM_AHB_CACHABLE    VTSS_BIT(8)
#define  VTSS_X_CPU_HICM_HICM_AHB_CACHABLE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 *
 * HICM ahb buffarable configuration. HICM instance in HSS block0: not
 * bufferable1:bufferable
 *
 * \details
 * Field: ::VTSS_CPU_HICM . HICM_AHB_BUFFERABLE
 */
#define  VTSS_F_CPU_HICM_HICM_AHB_BUFFERABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_HICM_HICM_AHB_BUFFERABLE  VTSS_BIT(0)
#define  VTSS_X_CPU_HICM_HICM_AHB_BUFFERABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief USB device configuration
 *
 * \details
 * Register: \a CPU:SFR_REGS:UDPHS
 */
#define VTSS_CPU_UDPHS                       VTSS_IOREG(VTSS_TO_CPU,0xb8)

/**
 * \brief
 *
 * USB Deivce (UDPHS) ahb cachable configuration. UDPHS instance in HSS
 * block0: not cachable1: cachable
 *
 * \details
 * Field: ::VTSS_CPU_UDPHS . UDPHS_AHB_CACHABLE
 */
#define  VTSS_F_CPU_UDPHS_UDPHS_AHB_CACHABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_CPU_UDPHS_UDPHS_AHB_CACHABLE  VTSS_BIT(8)
#define  VTSS_X_CPU_UDPHS_UDPHS_AHB_CACHABLE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 *
 * USB Deivce (UDPHS) ahb buffarable configuration. UDPHS instance in HSS
 * block0: not bufferable1:bufferable
 *
 * \details
 * Field: ::VTSS_CPU_UDPHS . UDPHS_AHB_BUFFERABLE
 */
#define  VTSS_F_CPU_UDPHS_UDPHS_AHB_BUFFERABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_UDPHS_UDPHS_AHB_BUFFERABLE  VTSS_BIT(0)
#define  VTSS_X_CPU_UDPHS_UDPHS_AHB_BUFFERABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief HSS DDR configuration
 *
 * \details
 * Register: \a CPU:SFR_REGS:UDDR
 */
#define VTSS_CPU_UDDR                        VTSS_IOREG(VTSS_TO_CPU,0xb9)

/**
 * \brief
 *
 * QOS signal configuration from HSS to DDR path0: qos disbaled1: qos
 * enabled
 *
 * \details
 * Field: ::VTSS_CPU_UDDR . AXI_READ_QOS
 */
#define  VTSS_F_CPU_UDDR_AXI_READ_QOS(x)      VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_CPU_UDDR_AXI_READ_QOS         VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_CPU_UDDR_AXI_READ_QOS(x)      VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 *
 * QOS signal configuration from HSS to DDR path0: qos disbaled1: qos
 * enabled
 *
 * \details
 * Field: ::VTSS_CPU_UDDR . AXI_WRITE_QOS
 */
#define  VTSS_F_CPU_UDDR_AXI_WRITE_QOS(x)     VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CPU_UDDR_AXI_WRITE_QOS        VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CPU_UDDR_AXI_WRITE_QOS(x)     VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a CPU:PCIE_PHY
 *
 * Not documented
 */


/**
 * \brief PCIe PHY configuration
 *
 * \details
 * Register: \a CPU:PCIE_PHY:PHY_CFG
 */
#define VTSS_CPU_PHY_CFG                     VTSS_IOREG(VTSS_TO_CPU,0xba)

/**
 * \brief
 * Loss-of-Signal Detector Threshold Level Control.Sets the LOS detection
 * threshold level. This signal is reserved and must be set to 3'b010.
 *
 * \details
 * Field: ::VTSS_CPU_PHY_CFG . LOS_BIAS
 */
#define  VTSS_F_CPU_PHY_CFG_LOS_BIAS(x)       VTSS_ENCODE_BITFIELD(x,17,3)
#define  VTSS_M_CPU_PHY_CFG_LOS_BIAS          VTSS_ENCODE_BITMASK(17,3)
#define  VTSS_X_CPU_PHY_CFG_LOS_BIAS(x)       VTSS_EXTRACT_BITFIELD(x,17,3)

/**
 * \brief
 * Loss-of-Signal Detector Sensitivity Level Control.Sets the sensitivity
 * level for the Loss-of-Signal detector. This bus must be set to 5'b01001.
 *
 * \details
 * Field: ::VTSS_CPU_PHY_CFG . LOS_LEVEL
 */
#define  VTSS_F_CPU_PHY_CFG_LOS_LEVEL(x)      VTSS_ENCODE_BITFIELD(x,12,5)
#define  VTSS_M_CPU_PHY_CFG_LOS_LEVEL         VTSS_ENCODE_BITMASK(12,5)
#define  VTSS_X_CPU_PHY_CFG_LOS_LEVEL(x)      VTSS_EXTRACT_BITFIELD(x,12,5)

/**
 * \brief
 * RX Equalizer SettingSets the fixed value of the RX equalizer. The
 * recommended setting is 2 (3'b010). The optimal EQ setting varies
 * depending on users' system environment.
 *
 * \details
 * Field: ::VTSS_CPU_PHY_CFG . RX_EQ
 */
#define  VTSS_F_CPU_PHY_CFG_RX_EQ(x)          VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_CPU_PHY_CFG_RX_EQ             VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_CPU_PHY_CFG_RX_EQ(x)          VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * Transmitter Termination Offset.Enables adjustment of the transmitter
 * termination value from the default value of 50 Ohm.
 *
 * \details
 * Field: ::VTSS_CPU_PHY_CFG . TX_TERM_OFFSET
 */
#define  VTSS_F_CPU_PHY_CFG_TX_TERM_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,4,5)
#define  VTSS_M_CPU_PHY_CFG_TX_TERM_OFFSET     VTSS_ENCODE_BITMASK(4,5)
#define  VTSS_X_CPU_PHY_CFG_TX_TERM_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,4,5)

/**
 * \brief
 * TX Voltage Boost Level.This bus is reserved and must be set to 3'b100.
 *
 * \details
 * Field: ::VTSS_CPU_PHY_CFG . TX_VBOOST_LVL
 */
#define  VTSS_F_CPU_PHY_CFG_TX_VBOOST_LVL(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_CPU_PHY_CFG_TX_VBOOST_LVL     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_CPU_PHY_CFG_TX_VBOOST_LVL(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/**
 * \brief
 * Built-in 3.3-V Regulator Bypass Mode Control.
 *
 * \details
 * 0: 3.3-V vph is applied, and the 3.3-2.5-V regulator is used.
 * 1: 2.5-V vph
 *
 * Field: ::VTSS_CPU_PHY_CFG . VREG_BYPASS
 */
#define  VTSS_F_CPU_PHY_CFG_VREG_BYPASS(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PHY_CFG_VREG_BYPASS       VTSS_BIT(0)
#define  VTSS_X_CPU_PHY_CFG_VREG_BYPASS(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief PCIe PHY tune
 *
 * \details
 * Register: \a CPU:PCIE_PHY:PHY_TUNE
 */
#define VTSS_CPU_PHY_TUNE                    VTSS_IOREG(VTSS_TO_CPU,0xbb)

/**
 * \brief
 * Resistor Tune Request.Assertion triggers a resistor tune request (if one
 * is not already in progress). When this signal is asserted, RTUNE_ACK
 * goes high until calibration of the termination impedances is complete.
 * Note that termination resistance tuning disrupts the normal flow of
 * data, so RTUNE_REQ must be asserted only when the PHY is inactive. The
 * PHY performs a tune automatically after coming out of phy_reset.
 *
 * \details
 * Field: ::VTSS_CPU_PHY_TUNE . RTUNE_REQ
 */
#define  VTSS_F_CPU_PHY_TUNE_RTUNE_REQ(x)     VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_PHY_TUNE_RTUNE_REQ        VTSS_BIT(1)
#define  VTSS_X_CPU_PHY_TUNE_RTUNE_REQ(x)     VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Resistor Tune Acknowledge.While asserted, indicates that a resistor tune
 * is still in progress.
 *
 * \details
 * Field: ::VTSS_CPU_PHY_TUNE . RTUNE_ACK
 */
#define  VTSS_F_CPU_PHY_TUNE_RTUNE_ACK(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PHY_TUNE_RTUNE_ACK        VTSS_BIT(0)
#define  VTSS_X_CPU_PHY_TUNE_RTUNE_ACK(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief PCIe PCS configuration
 *
 * \details
 * Register: \a CPU:PCIE_PHY:PCS_CFG
 */
#define VTSS_CPU_PCS_CFG                     VTSS_IOREG(VTSS_TO_CPU,0xbc)

/**
 * \brief
 * TX De-emphasis at 3.5 dB.This static value sets the TX driver
 * de-emphasis value in the case where pipeP_tx_deemph is set to 1'b1
 * (default setting) and the PHY is running at the Gen2 rate.
 *
 * \details
 * Field: ::VTSS_CPU_PCS_CFG . DEEMPH_GEN2_3P5DB
 */
#define  VTSS_F_CPU_PCS_CFG_DEEMPH_GEN2_3P5DB(x)  VTSS_ENCODE_BITFIELD(x,26,6)
#define  VTSS_M_CPU_PCS_CFG_DEEMPH_GEN2_3P5DB     VTSS_ENCODE_BITMASK(26,6)
#define  VTSS_X_CPU_PCS_CFG_DEEMPH_GEN2_3P5DB(x)  VTSS_EXTRACT_BITFIELD(x,26,6)

/**
 * \brief
 * TX De-emphasis at 6 dB.This static value sets the TX driver de-emphasis
 * value in the case where pipeP_tx_deemph is set to 1'b0 and the PHY is
 * running at the Gen2 rate.
 *
 * \details
 * Field: ::VTSS_CPU_PCS_CFG . DEEMPH_GEN2_6DB
 */
#define  VTSS_F_CPU_PCS_CFG_DEEMPH_GEN2_6DB(x)  VTSS_ENCODE_BITFIELD(x,20,6)
#define  VTSS_M_CPU_PCS_CFG_DEEMPH_GEN2_6DB     VTSS_ENCODE_BITMASK(20,6)
#define  VTSS_X_CPU_PCS_CFG_DEEMPH_GEN2_6DB(x)  VTSS_EXTRACT_BITFIELD(x,20,6)

/**
 * \brief
 * TX De-emphasis at 3.5 dB.This static value sets the TX driver
 * de-emphasis value in the case where pipeP_tx_deemph is set to 1'b1
 * (default setting) and the PHY is running at the Gen1 rate.
 *
 * \details
 * Field: ::VTSS_CPU_PCS_CFG . DEEMPH_GEN1
 */
#define  VTSS_F_CPU_PCS_CFG_DEEMPH_GEN1(x)    VTSS_ENCODE_BITFIELD(x,14,6)
#define  VTSS_M_CPU_PCS_CFG_DEEMPH_GEN1       VTSS_ENCODE_BITMASK(14,6)
#define  VTSS_X_CPU_PCS_CFG_DEEMPH_GEN1(x)    VTSS_EXTRACT_BITFIELD(x,14,6)

/**
 * \brief
 * TX Amplitude (Full Swing Mode).This static value sets the launch
 * amplitude of the transmitter when pipeP_tx_swing is set to 1'b0 (default
 * state).
 *
 * \details
 * Field: ::VTSS_CPU_PCS_CFG . SWING_FULL
 */
#define  VTSS_F_CPU_PCS_CFG_SWING_FULL(x)     VTSS_ENCODE_BITFIELD(x,7,7)
#define  VTSS_M_CPU_PCS_CFG_SWING_FULL        VTSS_ENCODE_BITMASK(7,7)
#define  VTSS_X_CPU_PCS_CFG_SWING_FULL(x)     VTSS_EXTRACT_BITFIELD(x,7,7)

/**
 * \brief
 * TX Amplitude (Low Swing Mode).This static value sets the launch
 * amplitude of the transmitter when pipeP_tx_swing is set to 1'b1 (low
 * swing mode). This bus can be set to an alternate launch amplitude if
 * required. This bus is provided for completeness and can be set to 7'b0.
 *
 * \details
 * Field: ::VTSS_CPU_PCS_CFG . SWING_LOW
 */
#define  VTSS_F_CPU_PCS_CFG_SWING_LOW(x)      VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_CPU_PCS_CFG_SWING_LOW         VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_CPU_PCS_CFG_SWING_LOW(x)      VTSS_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief Controls the PCIe PHY indirect register access
 *
 * \details
 * Register: \a CPU:PCIE_PHY:PHY_CR_CTRL
 */
#define VTSS_CPU_PHY_CR_CTRL                 VTSS_IOREG(VTSS_TO_CPU,0xbd)

/**
 * \details
 * Field: ::VTSS_CPU_PHY_CR_CTRL . CAP_ADDR
 */
#define  VTSS_F_CPU_PHY_CR_CTRL_CAP_ADDR(x)   VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CPU_PHY_CR_CTRL_CAP_ADDR      VTSS_BIT(4)
#define  VTSS_X_CPU_PHY_CR_CTRL_CAP_ADDR(x)   VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \details
 * Field: ::VTSS_CPU_PHY_CR_CTRL . CAP_DATA
 */
#define  VTSS_F_CPU_PHY_CR_CTRL_CAP_DATA(x)   VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_PHY_CR_CTRL_CAP_DATA      VTSS_BIT(3)
#define  VTSS_X_CPU_PHY_CR_CTRL_CAP_DATA(x)   VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \details
 * Field: ::VTSS_CPU_PHY_CR_CTRL . READ
 */
#define  VTSS_F_CPU_PHY_CR_CTRL_READ(x)       VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_PHY_CR_CTRL_READ          VTSS_BIT(2)
#define  VTSS_X_CPU_PHY_CR_CTRL_READ(x)       VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \details
 * Field: ::VTSS_CPU_PHY_CR_CTRL . WRITE
 */
#define  VTSS_F_CPU_PHY_CR_CTRL_WRITE(x)      VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_PHY_CR_CTRL_WRITE         VTSS_BIT(1)
#define  VTSS_X_CPU_PHY_CR_CTRL_WRITE(x)      VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * Field: ::VTSS_CPU_PHY_CR_CTRL . ACK
 */
#define  VTSS_F_CPU_PHY_CR_CTRL_ACK(x)        VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PHY_CR_CTRL_ACK           VTSS_BIT(0)
#define  VTSS_X_CPU_PHY_CR_CTRL_ACK(x)        VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Data the PCIe PHY indirect register access
 *
 * \details
 * Register: \a CPU:PCIE_PHY:PHY_CR_DATA
 */
#define VTSS_CPU_PHY_CR_DATA                 VTSS_IOREG(VTSS_TO_CPU,0xbe)

/**
 * \details
 * Field: ::VTSS_CPU_PHY_CR_DATA . DATA_IN
 */
#define  VTSS_F_CPU_PHY_CR_DATA_DATA_IN(x)    VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_CPU_PHY_CR_DATA_DATA_IN       VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_CPU_PHY_CR_DATA_DATA_IN(x)    VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \details
 * Field: ::VTSS_CPU_PHY_CR_DATA . DATA_OUT
 */
#define  VTSS_F_CPU_PHY_CR_DATA_DATA_OUT(x)   VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_CPU_PHY_CR_DATA_DATA_OUT      VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_CPU_PHY_CR_DATA_DATA_OUT(x)   VTSS_EXTRACT_BITFIELD(x,0,16)


#endif /* _VTSS_LAGUNA_REGS_CPU_H_ */
