// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_FA_KERNEL_REGS_CPU_H_
#define _VTSS_FA_KERNEL_REGS_CPU_H_

#include "vtss_fa_kernel_regs_common.h"

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
 * General purpose 8 times 32-bit registers for software development and
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
 * \brief Reset Settings
 *
 * \details
 * Register: \a CPU:CPU_REGS:RESET
 */
#define VTSS_CPU_RESET                       VTSS_IOREG(VTSS_TO_CPU,0x20)

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
#define  VTSS_F_CPU_RESET_VCORE_RST(x)        VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_CPU_RESET_VCORE_RST           VTSS_BIT(9)
#define  VTSS_X_CPU_RESET_VCORE_RST(x)        VTSS_EXTRACT_BITFIELD(x,9,1)

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
#define  VTSS_F_CPU_RESET_CPU_CORE_0_WARM_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_CPU_RESET_CPU_CORE_0_WARM_RST  VTSS_BIT(8)
#define  VTSS_X_CPU_RESET_CPU_CORE_0_WARM_RST(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * This register performs warm reset of Core 1 of ARM Processor inside
 * Vcore system.Self clearing field at the end of warm reset.
 *
 * \details 
 * 0 - Normal operation
 * 1 - Perform warm reset of core 1 (Self clears at the end of reset).
 *
 * Field: ::VTSS_CPU_RESET . CPU_CORE_1_WARM_RST
 */
#define  VTSS_F_CPU_RESET_CPU_CORE_1_WARM_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_CPU_RESET_CPU_CORE_1_WARM_RST  VTSS_BIT(7)
#define  VTSS_X_CPU_RESET_CPU_CORE_1_WARM_RST(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

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
#define  VTSS_F_CPU_RESET_PROC_DBG_RST(x)     VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_CPU_RESET_PROC_DBG_RST        VTSS_BIT(6)
#define  VTSS_X_CPU_RESET_PROC_DBG_RST(x)     VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * This field resets the L2 cache in CPU of VCORE to be in reset.This block
 * auto-clears when reset of L2 is complete.
 *
 * \details 
 * 1 - Put the CPU L2 cache in reset (auto-clear at the end of reset).
 * 0 - CPU L2 cache is not in reset.
 *
 * Field: ::VTSS_CPU_RESET . CPU_L2_RST
 */
#define  VTSS_F_CPU_RESET_CPU_L2_RST(x)       VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_CPU_RESET_CPU_L2_RST          VTSS_BIT(5)
#define  VTSS_X_CPU_RESET_CPU_L2_RST(x)       VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * This field resets the DDR Memory in the Vcore Sub-system.
 *
 * \details 
 * 1 - DDR Memory is in reset (self - clears when DDR reset is done).
 * 0 - DDR Memory is not in reset.
 *
 * Field: ::VTSS_CPU_RESET . MEM_RST
 */
#define  VTSS_F_CPU_RESET_MEM_RST(x)          VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CPU_RESET_MEM_RST             VTSS_BIT(4)
#define  VTSS_X_CPU_RESET_MEM_RST(x)          VTSS_EXTRACT_BITFIELD(x,4,1)

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
#define  VTSS_F_CPU_RESET_WDT_FORCE_RST(x)    VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_RESET_WDT_FORCE_RST       VTSS_BIT(3)
#define  VTSS_X_CPU_RESET_WDT_FORCE_RST(x)    VTSS_EXTRACT_BITFIELD(x,3,1)

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
#define  VTSS_F_CPU_RESET_CPU_CORE_0_COLD_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_RESET_CPU_CORE_0_COLD_RST  VTSS_BIT(2)
#define  VTSS_X_CPU_RESET_CPU_CORE_0_COLD_RST(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * This field performs a cold reset (includes debug logic of core 1) of CPU
 * Core 1.
 *
 * \details 
 * 1 -	Core 1 of CPU is in cold reset
 * 0  - Core 1 of CPU is not in cold reset
 *
 * Field: ::VTSS_CPU_RESET . CPU_CORE_1_COLD_RST
 */
#define  VTSS_F_CPU_RESET_CPU_CORE_1_COLD_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_RESET_CPU_CORE_1_COLD_RST  VTSS_BIT(1)
#define  VTSS_X_CPU_RESET_CPU_CORE_1_COLD_RST(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * This field resets the GIC Block.
 *
 * \details 
 * 0 - Do not reset GIC block.
 * 1 - Put GIC Block in reset.

 *
 * Field: ::VTSS_CPU_RESET . GIC_RST
 */
#define  VTSS_F_CPU_RESET_GIC_RST(x)          VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_RESET_GIC_RST             VTSS_BIT(0)
#define  VTSS_X_CPU_RESET_GIC_RST(x)          VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief This register contains fields that protect certain blocks from resets.
 *
 * \details
 * Register: \a CPU:CPU_REGS:RESET_PROT_STAT
 */
#define VTSS_CPU_RESET_PROT_STAT             VTSS_IOREG(VTSS_TO_CPU,0x21)

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
#define  VTSS_F_CPU_RESET_PROT_STAT_SYS_RST_PROT_VCORE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_CPU_RESET_PROT_STAT_SYS_RST_PROT_VCORE  VTSS_BIT(10)
#define  VTSS_X_CPU_RESET_PROT_STAT_SYS_RST_PROT_VCORE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

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
#define  VTSS_F_CPU_RESET_PROT_STAT_VCORE_RST_PROT_AMBA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_CPU_RESET_PROT_STAT_VCORE_RST_PROT_AMBA  VTSS_BIT(9)
#define  VTSS_X_CPU_RESET_PROT_STAT_VCORE_RST_PROT_AMBA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

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
#define  VTSS_F_CPU_RESET_PROT_STAT_VCORE_RST_PROT_WDT(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_CPU_RESET_PROT_STAT_VCORE_RST_PROT_WDT  VTSS_BIT(8)
#define  VTSS_X_CPU_RESET_PROT_STAT_VCORE_RST_PROT_WDT(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * This field protects the integrated coresight components from: Watchdog
 * timer reset, Vcore Soft Reset (VCORE_RST Register Field), Vcore Cold
 * Reset (CPU_CORE_x_COLD_RST). 
 *
 * \details 
 * 0 : No protection to processor's debug logic.
 * 1 : Protection applied to processor debug logic from Watch dog timeout,
 * Vcore soft reset, Vcore Cold Reset.
 *
 * Field: ::VTSS_CPU_RESET_PROT_STAT . VCORE_RST_PROT_PDBG
 */
#define  VTSS_F_CPU_RESET_PROT_STAT_VCORE_RST_PROT_PDBG(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_CPU_RESET_PROT_STAT_VCORE_RST_PROT_PDBG  VTSS_BIT(7)
#define  VTSS_X_CPU_RESET_PROT_STAT_VCORE_RST_PROT_PDBG(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * By default, GIC is reset when both the cores of CPU are cold reset.
 * However, this field protects GIC from getting reset in such cases.
 *
 * \details 
 * 0 : No protection to GIC when both the cores of CPU are cold reset.
 * 1 : GIC is protected from reset when both the cores of CPU are cold
 * reset.
 *
 * Field: ::VTSS_CPU_RESET_PROT_STAT . VCORE_RST_PROT_GIC
 */
#define  VTSS_F_CPU_RESET_PROT_STAT_VCORE_RST_PROT_GIC(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_CPU_RESET_PROT_STAT_VCORE_RST_PROT_GIC  VTSS_BIT(6)
#define  VTSS_X_CPU_RESET_PROT_STAT_VCORE_RST_PROT_GIC(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

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
#define  VTSS_F_CPU_RESET_PROT_STAT_VCORE_WDT_RST_PROT_WDT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_CPU_RESET_PROT_STAT_VCORE_WDT_RST_PROT_WDT  VTSS_BIT(5)
#define  VTSS_X_CPU_RESET_PROT_STAT_VCORE_WDT_RST_PROT_WDT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

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
#define  VTSS_F_CPU_RESET_PROT_STAT_VCORE_WDT_RST_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CPU_RESET_PROT_STAT_VCORE_WDT_RST_STAT  VTSS_BIT(4)
#define  VTSS_X_CPU_RESET_PROT_STAT_VCORE_WDT_RST_STAT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * GIC has been reset due to either ecc_fatal (Unrecoverable fatal error)
 * indication from SRAMS inside it ordue to fatal errors (SLVERR/DECERR)
 * received from accessing DDR Memory.
 *
 * \details 
 * 0 : GIC has not been reset due to the mentioned causes.
 * 1 : GIC has been reset due to ecc_fatal error from SRAMS.
 * 2 : GIC has been reset due to SLVERR/DECERR received from accessing DDR
 * Memory.
 * 3 : GIC has been reset due to ecc_fatal error from SRAMS and there was
 * also error on accessing DDR.
 *
 * Field: ::VTSS_CPU_RESET_PROT_STAT . GIC_RST_STAT
 */
#define  VTSS_F_CPU_RESET_PROT_STAT_GIC_RST_STAT(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_CPU_RESET_PROT_STAT_GIC_RST_STAT     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_CPU_RESET_PROT_STAT_GIC_RST_STAT(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * By default L2 is reset when both cores of processor are cold reset. This
 * register protects from such auto resetting of L2
 *
 * \details 
 * 0 - No protection from auto reset of L2.
 * 1 - Protect L2 when both cores of processor are cold reset.
 *
 * Field: ::VTSS_CPU_RESET_PROT_STAT . CPU_RST_PROT_L2
 */
#define  VTSS_F_CPU_RESET_PROT_STAT_CPU_RST_PROT_L2(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_RESET_PROT_STAT_CPU_RST_PROT_L2  VTSS_BIT(1)
#define  VTSS_X_CPU_RESET_PROT_STAT_CPU_RST_PROT_L2(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * This protection bits protects GIC from resetting itself.This occurs when
 * there is any error on transaction towards the AXI Master port of the
 * GIC.
 *
 * \details 
 * '0' : GIC is not protected from a reset by itself.
 * '1': GIC is protected from a reset by itself.
 *
 * Field: ::VTSS_CPU_RESET_PROT_STAT . SELF_RST_PROT_GIC
 */
#define  VTSS_F_CPU_RESET_PROT_STAT_SELF_RST_PROT_GIC(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_RESET_PROT_STAT_SELF_RST_PROT_GIC  VTSS_BIT(0)
#define  VTSS_X_CPU_RESET_PROT_STAT_SELF_RST_PROT_GIC(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief General control
 *
 * \details
 * Register: \a CPU:CPU_REGS:GENERAL_CTRL
 */
#define VTSS_CPU_GENERAL_CTRL                VTSS_IOREG(VTSS_TO_CPU,0x22)

/** 
 * \brief
 * Delay clock to card to meet setup time requirements.
 *
 * \details 
 * N : Delay (N+1)*1.25 ns, N>0.
 * Value 0 is reserved.
 *
 * Field: ::VTSS_CPU_GENERAL_CTRL . MSHC_CLK2CARD_DLY_CC
 */
#define  VTSS_F_CPU_GENERAL_CTRL_MSHC_CLK2CARD_DLY_CC(x)  VTSS_ENCODE_BITFIELD(x,13,4)
#define  VTSS_M_CPU_GENERAL_CTRL_MSHC_CLK2CARD_DLY_CC     VTSS_ENCODE_BITMASK(13,4)
#define  VTSS_X_CPU_GENERAL_CTRL_MSHC_CLK2CARD_DLY_CC(x)  VTSS_EXTRACT_BITFIELD(x,13,4)

/** 
 * \brief
 * Hooked up to the master contention input (ss_in_n) of the SPI Master
 * block.
 *
 * \details 
 * Field: ::VTSS_CPU_GENERAL_CTRL . SIMC_SSP_ENA
 */
#define  VTSS_F_CPU_GENERAL_CTRL_SIMC_SSP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_CPU_GENERAL_CTRL_SIMC_SSP_ENA  VTSS_BIT(12)
#define  VTSS_X_CPU_GENERAL_CTRL_SIMC_SSP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * The default value of this field depends on strapping of the VCore.Set
 * this field to enable the MIIM slave-interface on the GPIOs.
 *
 * \details 
 * Field: ::VTSS_CPU_GENERAL_CTRL . IF_MIIM_SLV_ENA
 */
#define  VTSS_F_CPU_GENERAL_CTRL_IF_MIIM_SLV_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_CPU_GENERAL_CTRL_IF_MIIM_SLV_ENA  VTSS_BIT(11)
#define  VTSS_X_CPU_GENERAL_CTRL_IF_MIIM_SLV_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * The default value of this field depends on strapping of the VCore (the
 * PI_nDone signal).
 *
 * \details 
 * Field: ::VTSS_CPU_GENERAL_CTRL . IF_PI_SLV_DONEPOL
 */
#define  VTSS_F_CPU_GENERAL_CTRL_IF_PI_SLV_DONEPOL(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_CPU_GENERAL_CTRL_IF_PI_SLV_DONEPOL  VTSS_BIT(10)
#define  VTSS_X_CPU_GENERAL_CTRL_IF_PI_SLV_DONEPOL(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * The default value of this field depends on strapping of the VCore.Set
 * this field to force PI interfaces into slave mode (and enable PI on
 * GPIOs).
 *
 * \details 
 * Field: ::VTSS_CPU_GENERAL_CTRL . IF_PI_SLV_ENA
 */
#define  VTSS_F_CPU_GENERAL_CTRL_IF_PI_SLV_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_CPU_GENERAL_CTRL_IF_PI_SLV_ENA  VTSS_BIT(9)
#define  VTSS_X_CPU_GENERAL_CTRL_IF_PI_SLV_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * The default value of this field depends on strapping of the VCore.Set
 * this field to enable PI master interface (and enable PI on GPIOs).
 *
 * \details 
 * Field: ::VTSS_CPU_GENERAL_CTRL . IF_PI_MST_ENA
 */
#define  VTSS_F_CPU_GENERAL_CTRL_IF_PI_MST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_CPU_GENERAL_CTRL_IF_PI_MST_ENA  VTSS_BIT(8)
#define  VTSS_X_CPU_GENERAL_CTRL_IF_PI_MST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * The default value of this field depends on strapping of the VCore.Select
 * the owner of the SPI interface.
 *
 * \details 
 * 0: SI Slave
 * 1: SI Boot Master
 * 2: SI Master Controller
 *
 * Field: ::VTSS_CPU_GENERAL_CTRL . IF_SI_OWNER
 */
#define  VTSS_F_CPU_GENERAL_CTRL_IF_SI_OWNER(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_CPU_GENERAL_CTRL_IF_SI_OWNER     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_CPU_GENERAL_CTRL_IF_SI_OWNER(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * Select the owner of the SPI2 interface that is mapped on GPIOs.
 *
 * \details 
 * 0: SI Slave
 * 1: SI Boot Master
 * 2: SI Master Controller
 *
 * Field: ::VTSS_CPU_GENERAL_CTRL . IF_SI2_OWNER
 */
#define  VTSS_F_CPU_GENERAL_CTRL_IF_SI2_OWNER(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_CPU_GENERAL_CTRL_IF_SI2_OWNER     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_CPU_GENERAL_CTRL_IF_SI2_OWNER(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Enable interface mode for SPI GPIOs.
 *
 * \details 
 * Field: ::VTSS_CPU_GENERAL_CTRL . IF_SI_ENA
 */
#define  VTSS_F_CPU_GENERAL_CTRL_IF_SI_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_GENERAL_CTRL_IF_SI_ENA    VTSS_BIT(3)
#define  VTSS_X_CPU_GENERAL_CTRL_IF_SI_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Enable interface mode for SPI2 GPIOs.
 *
 * \details 
 * Field: ::VTSS_CPU_GENERAL_CTRL . IF_SI2_ENA
 */
#define  VTSS_F_CPU_GENERAL_CTRL_IF_SI2_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_GENERAL_CTRL_IF_SI2_ENA   VTSS_BIT(2)
#define  VTSS_X_CPU_GENERAL_CTRL_IF_SI2_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Use this field to change from Boot mode to Normal mode. In Boot mode,
 * the reset vector of the VCore CPU maps to CS0 on the FLASH interface.
 * When in Normal mode, this address maps instead to the DRAM Controller.
 * The DRAM Controller must be operational before disabling Boot
 * mode.&#13;After setting Boot mode, this register must be read back. The
 * change in Boot mode takes effect during read.
 *
 * \details 
 * 0: The VCore memory map is in Normal mode.
 * 1: The VCore memory map is in Boot mode.
 *
 * Field: ::VTSS_CPU_GENERAL_CTRL . BOOT_MODE_ENA
 */
#define  VTSS_F_CPU_GENERAL_CTRL_BOOT_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_GENERAL_CTRL_BOOT_MODE_ENA  VTSS_BIT(1)
#define  VTSS_X_CPU_GENERAL_CTRL_BOOT_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

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
#define  VTSS_F_CPU_GENERAL_CTRL_VCORE_CPU_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_GENERAL_CTRL_VCORE_CPU_DIS  VTSS_BIT(0)
#define  VTSS_X_CPU_GENERAL_CTRL_VCORE_CPU_DIS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief General Status 
 *
 * \details
 * Register: \a CPU:CPU_REGS:GENERAL_STAT
 */
#define VTSS_CPU_GENERAL_STAT                VTSS_IOREG(VTSS_TO_CPU,0x23)

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
#define  VTSS_F_CPU_GENERAL_STAT_REG_IF_ERR(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_CPU_GENERAL_STAT_REG_IF_ERR     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_CPU_GENERAL_STAT_REG_IF_ERR(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * This bit indicates that there is a write access request to AXI bus with
 * invalid address.
 *
 * \details 
 * 1 - An invalid write address has been accessed on AXI.
 * 0 - No invalid write address request has come to AXI from the last time
 * this bit was cleared.
 *
 * Field: ::VTSS_CPU_GENERAL_STAT . AXI_INVLD_WR_STICKY
 */
#define  VTSS_F_CPU_GENERAL_STAT_AXI_INVLD_WR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_CPU_GENERAL_STAT_AXI_INVLD_WR_STICKY  VTSS_BIT(5)
#define  VTSS_X_CPU_GENERAL_STAT_AXI_INVLD_WR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * This bit indicates that there is a read access request to AXI bus with
 * invalid address.
 *
 * \details 
 * 1 - An invalid read address has been accessed on AXI.
 * 0 - No invalid read address request has come to AXI from the last time
 * this bit was cleared.
 *
 * Field: ::VTSS_CPU_GENERAL_STAT . AXI_INVLD_RD_STICKY
 */
#define  VTSS_F_CPU_GENERAL_STAT_AXI_INVLD_RD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CPU_GENERAL_STAT_AXI_INVLD_RD_STICKY  VTSS_BIT(4)
#define  VTSS_X_CPU_GENERAL_STAT_AXI_INVLD_RD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \details 
 * Field: ::VTSS_CPU_GENERAL_STAT . VCORE_CFG
 */
#define  VTSS_F_CPU_GENERAL_STAT_VCORE_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CPU_GENERAL_STAT_VCORE_CFG     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CPU_GENERAL_STAT_VCORE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Configures endianness towards CPU system and CSR registers.
 *
 * \details
 * Register: \a CPU:CPU_REGS:ENDIANNESS
 */
#define VTSS_CPU_ENDIANNESS                  VTSS_IOREG(VTSS_TO_CPU,0x24)

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
 * \brief This register contains configuration fields related to POE System in Vcore CPU Sub-system
 *
 * \details
 * Register: \a CPU:CPU_REGS:SUBCPU_SYS_CFG
 */
#define VTSS_CPU_SUBCPU_SYS_CFG              VTSS_IOREG(VTSS_TO_CPU,0x25)

/** 
 * \brief
 * This register enables or disables the POE System.The default value of
 * this field is defined through the strapping.
 *
 * \details 
 * 0 - Normal operation of PoE sub-system.
 * 1 - Entire POE system is gated. In such case, all the read attempts
 * through the fabric return 0xFFFFFFFF
 *
 * Field: ::VTSS_CPU_SUBCPU_SYS_CFG . SUBCPU_SYS_DIS
 */
#define  VTSS_F_CPU_SUBCPU_SYS_CFG_SUBCPU_SYS_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_SUBCPU_SYS_CFG_SUBCPU_SYS_DIS  VTSS_BIT(2)
#define  VTSS_X_CPU_SUBCPU_SYS_CFG_SUBCPU_SYS_DIS(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * This field controls whether PoE system is in reset or not.The default
 * value of this field is defined through the strapping.
 *
 * \details 
 * 0 - PoE system is not in reset.
 * 1 - PoE system is forced to reset.
 * Note that the PoE system must be enabled (via POE_SYS_DIS) before this
 * reset is deasserted.
 *
 * Field: ::VTSS_CPU_SUBCPU_SYS_CFG . SUBCPU_SYS_RST_FORCE
 */
#define  VTSS_F_CPU_SUBCPU_SYS_CFG_SUBCPU_SYS_RST_FORCE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_SUBCPU_SYS_CFG_SUBCPU_SYS_RST_FORCE  VTSS_BIT(1)
#define  VTSS_X_CPU_SUBCPU_SYS_CFG_SUBCPU_SYS_RST_FORCE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * This register limits the forced reset (POE_RST_FORCE) only to the CPU of
 * the PoE system.This can be used to allow the fabric to exit from reset,
 * while still keeping the PoE's CPU under reset.
 *
 * \details 
 * 0 - Entire PoE system will be under reset when POE_RST_FORCE is
 * asserted.
 * 1 - Only the CPU of PoE will be under reset when POE_RST_FORCE is
 * asserted.
 *
 * Field: ::VTSS_CPU_SUBCPU_SYS_CFG . SUBCPU_SYS_RST_FORCE_PROT_AMBA
 */
#define  VTSS_F_CPU_SUBCPU_SYS_CFG_SUBCPU_SYS_RST_FORCE_PROT_AMBA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_SUBCPU_SYS_CFG_SUBCPU_SYS_RST_FORCE_PROT_AMBA  VTSS_BIT(0)
#define  VTSS_X_CPU_SUBCPU_SYS_CFG_SUBCPU_SYS_RST_FORCE_PROT_AMBA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Shared interrupts accessible from all CPUs.
 *
 * \details
 * Register: \a CPU:CPU_REGS:SHARED_INTR
 */
#define VTSS_CPU_SHARED_INTR                 VTSS_IOREG(VTSS_TO_CPU,0x26)

/** 
 * \brief
 * 
 *	     Set to generate interrupt, one interrupt per bit.	       
 * Atomic access to this register can be implemented by the
 * CPU::SHARED_INTR_CLR and CPU::SHARED_INTR_SET registers.

 *
 * \details 
 * Field: ::VTSS_CPU_SHARED_INTR . SHARED_INTR
 */
#define  VTSS_F_CPU_SHARED_INTR_SHARED_INTR(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_CPU_SHARED_INTR_SHARED_INTR     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_CPU_SHARED_INTR_SHARED_INTR(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief This register interrupts accessible from all CPUs.
 *
 * \details
 * Register: \a CPU:CPU_REGS:SHARED_INTR_CLR
 */
#define VTSS_CPU_SHARED_INTR_CLR             VTSS_IOREG(VTSS_TO_CPU,0x27)

/** 
 * \brief
 * 
 *	     Set bit(s) in this register to clear the corresponding bits in
 * CPU::SHARED_INTR. This register can be used for atomic access to
 * CPU::SHARED_INTR register.	     
 *
 * \details 
 * Field: ::VTSS_CPU_SHARED_INTR_CLR . SHARED_INTR_CLR
 */
#define  VTSS_F_CPU_SHARED_INTR_CLR_SHARED_INTR_CLR(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_CPU_SHARED_INTR_CLR_SHARED_INTR_CLR     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_CPU_SHARED_INTR_CLR_SHARED_INTR_CLR(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief This register interrupts accessible from all CPUs.
 *
 * \details
 * Register: \a CPU:CPU_REGS:SHARED_INTR_SET
 */
#define VTSS_CPU_SHARED_INTR_SET             VTSS_IOREG(VTSS_TO_CPU,0x28)

/** 
 * \brief
 * 
 *	     Set bit(s) in this register to set the corresponding bits in
 * CPU::SHARED_INTR. This register can be used for atomic access to
 * CPU::SHARED_INTR register.	     
 *
 * \details 
 * Field: ::VTSS_CPU_SHARED_INTR_SET . SHARED_INTR_SET
 */
#define  VTSS_F_CPU_SHARED_INTR_SET_SHARED_INTR_SET(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_CPU_SHARED_INTR_SET_SHARED_INTR_SET     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_CPU_SHARED_INTR_SET_SHARED_INTR_SET(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Enable slave-select forcing
 *
 * \details
 * Register: \a CPU:CPU_REGS:SS_FORCE_ENA
 */
#define VTSS_CPU_SS_FORCE_ENA                VTSS_IOREG(VTSS_TO_CPU,0x29)

/** 
 * \brief
 * Use to enable forcing of the slave select of the SPI master controller
 * in Main CPU system. When set, the slave select is driven by SS_FORCE.
 * When 0, the slave select is driven by the SPI master, and SS_FORCE must
 * be kept at 1.
 *
 * \details 
 * Field: ::VTSS_CPU_SS_FORCE_ENA . SS_FORCE_ENA
 */
#define  VTSS_F_CPU_SS_FORCE_ENA_SS_FORCE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_SS_FORCE_ENA_SS_FORCE_ENA  VTSS_BIT(0)
#define  VTSS_X_CPU_SS_FORCE_ENA_SS_FORCE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Slave select value to force
 *
 * \details
 * Register: \a CPU:CPU_REGS:SS_FORCE
 */
#define VTSS_CPU_SS_FORCE                    VTSS_IOREG(VTSS_TO_CPU,0x2a)

/** 
 * \brief
 * Value to drive on the slave select output. This field is used when
 * SS_FORCE_ENA is set to 1. Otherwise it must be kept to 1.
 *
 * \details 
 * Field: ::VTSS_CPU_SS_FORCE . SS_FORCE
 */
#define  VTSS_F_CPU_SS_FORCE_SS_FORCE(x)      VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_CPU_SS_FORCE_SS_FORCE         VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_CPU_SS_FORCE_SS_FORCE(x)      VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCIE Configuration Selection
 *
 * \details
 * Register: \a CPU:CPU_REGS:PCIE_SYS_CFG
 */
#define VTSS_CPU_PCIE_SYS_CFG                VTSS_IOREG(VTSS_TO_CPU,0x2b)

/** 
 * \brief
 * The default value of this field depends on strapping of the VCore.Set
 * this field to enable the Root Complex mode of PCIE Controller
 *
 * \details 
 * 1: Root Complex mode of operation is enabled in PCIE Controller
 * 0: End point mode of operation is enabled in PCIE Controller.
 *
 * Field: ::VTSS_CPU_PCIE_SYS_CFG . PCIE_RC_EP_MODE
 */
#define  VTSS_F_CPU_PCIE_SYS_CFG_PCIE_RC_EP_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PCIE_SYS_CFG_PCIE_RC_EP_MODE  VTSS_BIT(0)
#define  VTSS_X_CPU_PCIE_SYS_CFG_PCIE_RC_EP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Register containing control configuration of Processor
 *
 * \details
 * Register: \a CPU:CPU_REGS:PROC_CTRL
 */
#define VTSS_CPU_PROC_CTRL                   VTSS_IOREG(VTSS_TO_CPU,0x2c)

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
#define  VTSS_F_CPU_PROC_CTRL_AARCH64_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_CPU_PROC_CTRL_AARCH64_MODE_ENA  VTSS_BIT(12)
#define  VTSS_X_CPU_PROC_CTRL_AARCH64_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

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
#define  VTSS_F_CPU_PROC_CTRL_L2_RST_INVALIDATE_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_CPU_PROC_CTRL_L2_RST_INVALIDATE_DIS  VTSS_BIT(11)
#define  VTSS_X_CPU_PROC_CTRL_L2_RST_INVALIDATE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

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
#define  VTSS_F_CPU_PROC_CTRL_L1_RST_INVALIDATE_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_CPU_PROC_CTRL_L1_RST_INVALIDATE_DIS  VTSS_BIT(10)
#define  VTSS_X_CPU_PROC_CTRL_L1_RST_INVALIDATE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

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
#define  VTSS_F_CPU_PROC_CTRL_BE_EXCEP_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_CPU_PROC_CTRL_BE_EXCEP_MODE   VTSS_BIT(9)
#define  VTSS_X_CPU_PROC_CTRL_BE_EXCEP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

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
#define  VTSS_F_CPU_PROC_CTRL_VINITHI(x)      VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_CPU_PROC_CTRL_VINITHI         VTSS_BIT(8)
#define  VTSS_X_CPU_PROC_CTRL_VINITHI(x)      VTSS_EXTRACT_BITFIELD(x,8,1)

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
#define  VTSS_F_CPU_PROC_CTRL_CFGTE(x)        VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_CPU_PROC_CTRL_CFGTE           VTSS_BIT(7)
#define  VTSS_X_CPU_PROC_CTRL_CFGTE(x)        VTSS_EXTRACT_BITFIELD(x,7,1)

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
#define  VTSS_F_CPU_PROC_CTRL_CP15S_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_CPU_PROC_CTRL_CP15S_DISABLE   VTSS_BIT(6)
#define  VTSS_X_CPU_PROC_CTRL_CP15S_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

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
#define  VTSS_F_CPU_PROC_CTRL_PROC_CRYPTO_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_CPU_PROC_CTRL_PROC_CRYPTO_DISABLE  VTSS_BIT(5)
#define  VTSS_X_CPU_PROC_CTRL_PROC_CRYPTO_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Enable forcing of memory type attributes on CPU slave IF.
 *
 * \details 
 * 1: Forcing enabled
 * 0: Forcing disabled
 *
 * Field: ::VTSS_CPU_PROC_CTRL . ACP_CACHE_FORCE_ENA
 */
#define  VTSS_F_CPU_PROC_CTRL_ACP_CACHE_FORCE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CPU_PROC_CTRL_ACP_CACHE_FORCE_ENA  VTSS_BIT(4)
#define  VTSS_X_CPU_PROC_CTRL_ACP_CACHE_FORCE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Selects between Write-Back Write-allocate and No-allocate for write
 * transactions when ACP_CACHE_FORCE_ENA is set.
 *
 * \details 
 * 0: No-allocate
 * 1: Write-allocate
 *
 * Field: ::VTSS_CPU_PROC_CTRL . ACP_AWCACHE
 */
#define  VTSS_F_CPU_PROC_CTRL_ACP_AWCACHE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_PROC_CTRL_ACP_AWCACHE     VTSS_BIT(3)
#define  VTSS_X_CPU_PROC_CTRL_ACP_AWCACHE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Selects between Write-Back Read-allocate and No-allocate for read
 * transactions when ACP_CACHE_FORCE_ENA is set.
 *
 * \details 
 * 0: No-allocate
 * 1: Write-allocate
 *
 * Field: ::VTSS_CPU_PROC_CTRL . ACP_ARCACHE
 */
#define  VTSS_F_CPU_PROC_CTRL_ACP_ARCACHE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_PROC_CTRL_ACP_ARCACHE     VTSS_BIT(2)
#define  VTSS_X_CPU_PROC_CTRL_ACP_ARCACHE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Flush L2 to memory.
 *
 * \details 
 * Field: ::VTSS_CPU_PROC_CTRL . L2_FLUSH_REQ
 */
#define  VTSS_F_CPU_PROC_CTRL_L2_FLUSH_REQ(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_PROC_CTRL_L2_FLUSH_REQ    VTSS_BIT(1)
#define  VTSS_X_CPU_PROC_CTRL_L2_FLUSH_REQ(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Disables ACP port. It must be asserted before flushing L2 memory.
 *
 * \details 
 * 0: ACP enabled
 * 1: ACP disabled
 *
 * Field: ::VTSS_CPU_PROC_CTRL . ACP_DISABLE
 */
#define  VTSS_F_CPU_PROC_CTRL_ACP_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PROC_CTRL_ACP_DISABLE     VTSS_BIT(0)
#define  VTSS_X_CPU_PROC_CTRL_ACP_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Base address for GIC registers
 *
 * \details
 * Register: \a CPU:CPU_REGS:PROC_PERIPH_BASE
 */
#define VTSS_CPU_PROC_PERIPH_BASE            VTSS_IOREG(VTSS_TO_CPU,0x2d)

/** 
 * \brief
 * Specifies the base address for the GIC registers. This is sampled on
 * reset by the processor into CBAR.
 *
 * \details 
 * PERIPHBASE(39 down to 18) = 0x18008
 *
 * Field: ::VTSS_CPU_PROC_PERIPH_BASE . PERIPHBASE
 */
#define  VTSS_F_CPU_PROC_PERIPH_BASE_PERIPHBASE(x)  VTSS_ENCODE_BITFIELD(x,0,22)
#define  VTSS_M_CPU_PROC_PERIPH_BASE_PERIPHBASE     VTSS_ENCODE_BITMASK(0,22)
#define  VTSS_X_CPU_PROC_PERIPH_BASE_PERIPHBASE(x)  VTSS_EXTRACT_BITFIELD(x,0,22)


/** 
 * \brief Core 0 of the Processor Reset Vector Base Address Register least significant 32 bits
 *
 * \details
 * Register: \a CPU:CPU_REGS:CPU0_RVBAR_LSB
 */
#define VTSS_CPU_CPU0_RVBAR_LSB              VTSS_IOREG(VTSS_TO_CPU,0x2e)

/** 
 * \brief
 * Least significant 32-bits of the reset Vector Base Address for executing
 * Core 0 of processor in 64-bit state.This register is sampled along with
 * its LSB register only on reset of the core 0 of the processor
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
 * \brief Core 0 of the Processor Reset Vector Base Address Register most significant 6 bits
 *
 * \details
 * Register: \a CPU:CPU_REGS:CPU0_RVBAR_MSB
 */
#define VTSS_CPU_CPU0_RVBAR_MSB              VTSS_IOREG(VTSS_TO_CPU,0x2f)

/** 
 * \brief
 * Most significant 6-bits of the reset Vector Base Address for executing
 * core 0 of processor in 64-bit state.This register is sampled along with
 * its LSB register only on reset of the core 0 of the processor.
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
 * \brief Core 1 of the Processor Reset Vector Base Address Register least significant 32 bits
 *
 * \details
 * Register: \a CPU:CPU_REGS:CPU1_RVBAR_LSB
 */
#define VTSS_CPU_CPU1_RVBAR_LSB              VTSS_IOREG(VTSS_TO_CPU,0x30)

/** 
 * \brief
 * Least significant 32-bits of the reset Vector Base Address for executing
 * Core 1 of processor in 64-bit state.This register is sampled along with
 * its LSB register only on reset of the core 1 of the processor
 *
 * \details 
 * Reset vector base address[33:2] for the 64-bit state.
 *
 * Field: ::VTSS_CPU_CPU1_RVBAR_LSB . CPU1_RVBAR_LSB
 */
#define  VTSS_F_CPU_CPU1_RVBAR_LSB_CPU1_RVBAR_LSB(x)  (x)
#define  VTSS_M_CPU_CPU1_RVBAR_LSB_CPU1_RVBAR_LSB     0xffffffff
#define  VTSS_X_CPU_CPU1_RVBAR_LSB_CPU1_RVBAR_LSB(x)  (x)


/** 
 * \brief Core 1 of the Processor Reset Vector Base Address Register most significant 6 bits
 *
 * \details
 * Register: \a CPU:CPU_REGS:CPU1_RVBAR_MSB
 */
#define VTSS_CPU_CPU1_RVBAR_MSB              VTSS_IOREG(VTSS_TO_CPU,0x31)

/** 
 * \brief
 * Most significant 6-bits of the reset Vector Base Address for executing
 * core 1 of processor in 64-bit state.This register is sampled along with
 * its LSB register only on reset of the core 1 of the processor.
 *
 * \details 
 * Reset vector base address[39:34] for the 64-bit state
 *
 * Field: ::VTSS_CPU_CPU1_RVBAR_MSB . CPU1_RVBAR_MSB
 */
#define  VTSS_F_CPU_CPU1_RVBAR_MSB_CPU1_RVBAR_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CPU_CPU1_RVBAR_MSB_CPU1_RVBAR_MSB     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CPU_CPU1_RVBAR_MSB_CPU1_RVBAR_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Status indications from various blocks in processor
 *
 * \details
 * Register: \a CPU:CPU_REGS:PROC_STAT
 */
#define VTSS_CPU_PROC_STAT                   VTSS_IOREG(VTSS_TO_CPU,0x32)

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
#define  VTSS_F_CPU_PROC_STAT_DAP_JTAG_SW_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_PROC_STAT_DAP_JTAG_SW_MODE  VTSS_BIT(2)
#define  VTSS_X_CPU_PROC_STAT_DAP_JTAG_SW_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Wait-for-interrupt status of core 0.
 *
 * \details 
 * Field: ::VTSS_CPU_PROC_STAT . WFI_CORE_0
 */
#define  VTSS_F_CPU_PROC_STAT_WFI_CORE_0(x)   VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_PROC_STAT_WFI_CORE_0      VTSS_BIT(1)
#define  VTSS_X_CPU_PROC_STAT_WFI_CORE_0(x)   VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Wait-for-interrupt status of core 1.
 *
 * \details 
 * Field: ::VTSS_CPU_PROC_STAT . WFI_CORE_1
 */
#define  VTSS_F_CPU_PROC_STAT_WFI_CORE_1(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PROC_STAT_WFI_CORE_1      VTSS_BIT(0)
#define  VTSS_X_CPU_PROC_STAT_WFI_CORE_1(x)   VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a CPU:TWI_DELAY
 *
 * TWI hold time configuration
 */


/** 
 * \brief TWI hold time configuration
 *
 * \details
 * Register: \a CPU:TWI_DELAY:TWI_CONFIG
 */
#define VTSS_CPU_TWI_CONFIG                  VTSS_IOREG(VTSS_TO_CPU,0x33)

/** 
 * \brief
 * Configure the hold time delay to apply to SDA after SCK when
 * transmitting from the device. This delay is expressed in a number of
 * clock cycles. The delay value should be as close to 300ns as possible
 * without going below 300ns.
 *
 * \details 
 * ceil(300 (ns) / T (ns)) where T is the clock period
 *
 * Field: ::VTSS_CPU_TWI_CONFIG . TWI_CNT_RELOAD
 */
#define  VTSS_F_CPU_TWI_CONFIG_TWI_CNT_RELOAD(x)  VTSS_ENCODE_BITFIELD(x,1,8)
#define  VTSS_M_CPU_TWI_CONFIG_TWI_CNT_RELOAD     VTSS_ENCODE_BITMASK(1,8)
#define  VTSS_X_CPU_TWI_CONFIG_TWI_CNT_RELOAD(x)  VTSS_EXTRACT_BITFIELD(x,1,8)

/** 
 * \brief
 * Set this field to enable hold time on the TWI SDA output. When enabled
 * the TWI_CONFIG.TWI_CNT_RELOAD field determines the amount of hold time
 * to apply to SDA.
 *
 * \details 
 * Field: ::VTSS_CPU_TWI_CONFIG . TWI_DELAY_ENABLE
 */
#define  VTSS_F_CPU_TWI_CONFIG_TWI_DELAY_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_TWI_CONFIG_TWI_DELAY_ENABLE  VTSS_BIT(0)
#define  VTSS_X_CPU_TWI_CONFIG_TWI_DELAY_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a CPU:TWI_SPIKE_FILTER
 *
 * TWI spike filter configuration
 */


/** 
 * \brief TWI spike filter configuration
 *
 * \details
 * Register: \a CPU:TWI_SPIKE_FILTER:TWI_SPIKE_FILTER_CFG
 */
#define VTSS_CPU_TWI_SPIKE_FILTER_CFG        VTSS_IOREG(VTSS_TO_CPU,0x34)

/** 
 * \brief
 * Configuration of the spike filter width on the SCL and SDA
 * inputs.Filters spikes with a width of (SPIKE_FILTER_CFG+1)*SYSTEM_CLK or
 * less.
 *
 * \details 
 * Field: ::VTSS_CPU_TWI_SPIKE_FILTER_CFG . SPIKE_FILTER_CFG
 */
#define  VTSS_F_CPU_TWI_SPIKE_FILTER_CFG_SPIKE_FILTER_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_CPU_TWI_SPIKE_FILTER_CFG_SPIKE_FILTER_CFG     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_CPU_TWI_SPIKE_FILTER_CFG_SPIKE_FILTER_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * Register Group: \a CPU:SPI_MST
 *
 * SPI boot master
 */


/** 
 * \brief SPI boot master configuration
 *
 * \details
 * Register: \a CPU:SPI_MST:SPI_MST_CFG
 */
#define VTSS_CPU_SPI_MST_CFG                 VTSS_IOREG(VTSS_TO_CPU,0x35)

/** 
 * \brief
 * The number of dummy cycles in case of of FAST READ commands. Typically
 * the value is 8, sometimes need to be set to 10 for QUAD SPI protocol
 * mode.It is also possible to write to any other value provided that the
 * Flash is also configured to use this value. The max frequency of
 * operation in  case of Fast read depends on the number of dummy cycles
 * configured.Minimum is 1 amd maximum is 15.
 *
 * \details 
 * 0 - Do not configure to 0.
 * 1-15 -- Number of dummy cycles used in Fast read commands.
 *
 * Field: ::VTSS_CPU_SPI_MST_CFG . NUM_DUMMY_CLK_CYCLES
 */
#define  VTSS_F_CPU_SPI_MST_CFG_NUM_DUMMY_CLK_CYCLES(x)  VTSS_ENCODE_BITFIELD(x,15,4)
#define  VTSS_M_CPU_SPI_MST_CFG_NUM_DUMMY_CLK_CYCLES     VTSS_ENCODE_BITMASK(15,4)
#define  VTSS_X_CPU_SPI_MST_CFG_NUM_DUMMY_CLK_CYCLES(x)  VTSS_EXTRACT_BITFIELD(x,15,4)

/** 
 * \brief
 * Set to enable 32bit address mode. If set 4 bytes of address is sent in
 * address phase, otherwise 3 bytes. In 24bit addressing mode CS0 to CS3 is
 * used, the SPI address region is limited to 64MB of the 1GB reserved SI
 * interface.In 32bit addressing mode CS0 to CS3 is used, the SPI address
 * region is limited to 1GByte reserved for the SI interface.
 *
 * \details 
 * 0: Use 24bit addressing with 4 different CS, max 64MByte
 * 1: Use 32bit addressing with 4 different CS, max 1GByte
 *
 * Field: ::VTSS_CPU_SPI_MST_CFG . A32B_ENA
 */
#define  VTSS_F_CPU_SPI_MST_CFG_A32B_ENA(x)   VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_CPU_SPI_MST_CFG_A32B_ENA      VTSS_BIT(14)
#define  VTSS_X_CPU_SPI_MST_CFG_A32B_ENA(x)   VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * If set, the SPI master will use 4 Byte READ / 4 Byte FAST READ commands
 * instead of READ/FAST_READ. It implies that flash supports 32-bit
 * addressing and SPI master sends 4 byte of address and use command codes
 * 13h and 0Ch.
 *
 * \details 
 * Field: ::VTSS_CPU_SPI_MST_CFG . USE_4BYTE_READ_CMD
 */
#define  VTSS_F_CPU_SPI_MST_CFG_USE_4BYTE_READ_CMD(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_CPU_SPI_MST_CFG_USE_4BYTE_READ_CMD  VTSS_BIT(13)
#define  VTSS_X_CPU_SPI_MST_CFG_USE_4BYTE_READ_CMD(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * The type of read-instruction that the SPI Controller generates for
 * reads. Also see USE_4BYTE_READ_CMD.
 *
 * \details 
 * 0: READ (slow read - Instruction code - 0x03)
 * 1: FAST READ (fast read - Instruction code - 0x0B)
 *
 * Field: ::VTSS_CPU_SPI_MST_CFG . FAST_READ_ENA
 */
#define  VTSS_F_CPU_SPI_MST_CFG_FAST_READ_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_CPU_SPI_MST_CFG_FAST_READ_ENA  VTSS_BIT(12)
#define  VTSS_X_CPU_SPI_MST_CFG_FAST_READ_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * This field is used to configure SPI protocol mode.The SPI master
 * supports Single Transfer Rate (STR). Supported protocols in STR mode is
 * as below.Extended I/O protocol - DQ0 is used for CMD/ADDR. DQ1 is used
 * for Data.Dual I/O protocol - DQ[1:0] is used for the complete
 * transfer.Quad I/O protocol - DQ [3:0] is used for the complete transfer.
 *
 * \details 
 * 0 - Extended I/O protocol
 * 1 - Dual I/O protocol
 * 2,3 - Quad I/O protocol
 *
 * Field: ::VTSS_CPU_SPI_MST_CFG . SPI_PROTOCOL_MODE
 */
#define  VTSS_F_CPU_SPI_MST_CFG_SPI_PROTOCOL_MODE(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_CPU_SPI_MST_CFG_SPI_PROTOCOL_MODE     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_CPU_SPI_MST_CFG_SPI_PROTOCOL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * The minimum number of SPI clock cycles for which the SPI chip select
 * (SI_nEn) must be deasserted in between transfers. Typical value of this
 * is 100 ns. Setting this field to 0 is illegal.
 *
 * \details 
 * Field: ::VTSS_CPU_SPI_MST_CFG . CS_DESELECT_TIME
 */
#define  VTSS_F_CPU_SPI_MST_CFG_CS_DESELECT_TIME(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_CPU_SPI_MST_CFG_CS_DESELECT_TIME     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_CPU_SPI_MST_CFG_CS_DESELECT_TIME(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * Controls the clock frequency for the SPI interface (SI_Clk). The clock
 * frequency is VCore system clock divided by the value of this field.
 * Setting this field to 0 or 1 value is illegal.
 *
 * \details 
 * The SPI interface frequency is: 250MHz/CLK_DIV.
 *
 * Field: ::VTSS_CPU_SPI_MST_CFG . CLK_DIV
 */
#define  VTSS_F_CPU_SPI_MST_CFG_CLK_DIV(x)    VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_CPU_SPI_MST_CFG_CLK_DIV       VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_CPU_SPI_MST_CFG_CLK_DIV(x)    VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief SPI boot master status
 *
 * \details
 * This is a replicated register, where each replication holds the status
 * for one chip select.
 *
 * Register: \a CPU:SPI_MST:SPI_MST_STATUS
 *
 * @param ri Replicator: x_VCORE_SPI_CS_CNT (??), 0-3
 */
#define VTSS_CPU_SPI_MST_STATUS(ri)          VTSS_IOREG(VTSS_TO_CPU,0x36 + (ri))

/** 
 * \brief
 * Upsupported operation has been performed on the SPI master from AHB
 * slave.
 *
 * \details 
 * Field: ::VTSS_CPU_SPI_MST_STATUS . UNSUP_ERR
 */
#define  VTSS_F_CPU_SPI_MST_STATUS_UNSUP_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_SPI_MST_STATUS_UNSUP_ERR  VTSS_BIT(0)
#define  VTSS_X_CPU_SPI_MST_STATUS_UNSUP_ERR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Manual control of the SPI interface
 *
 * \details
 * Note: There are 4 chip selects in total, but only chip select 0 is
 * mapped to IO-pin (SI_nEn). The rest of the SPI chip selects are
 * available as alternate functions on GPIOs, these must be enabled in the
 * GPIO controller before they can be controlled via this register.
 *
 * Register: \a CPU:SPI_MST:SW_MODE
 */
#define VTSS_CPU_SW_MODE                     VTSS_IOREG(VTSS_TO_CPU,0x3a)

/** 
 * \brief
 * Set to enable software pin control mode (Bit banging), when set software
 * has direct control of the SPI interface.This mode is used for writing
 * into flash.
 *
 * \details 
 * Field: ::VTSS_CPU_SW_MODE . SW_PIN_CTRL_MODE
 */
#define  VTSS_F_CPU_SW_MODE_SW_PIN_CTRL_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_CPU_SW_MODE_SW_PIN_CTRL_MODE  VTSS_BIT(22)
#define  VTSS_X_CPU_SW_MODE_SW_PIN_CTRL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Value to drive on SI_Clk output. This field is only used if
 * SW_MODE.SW_PIN_CTRL_MODE is set.
 *
 * \details 
 * Field: ::VTSS_CPU_SW_MODE . SW_SPI_SCK
 */
#define  VTSS_F_CPU_SW_MODE_SW_SPI_SCK(x)     VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_CPU_SW_MODE_SW_SPI_SCK        VTSS_BIT(21)
#define  VTSS_X_CPU_SW_MODE_SW_SPI_SCK(x)     VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * Set to enable drive of SI_Clk output. This field is only used if
 * SW_MODE.SW_PIN_CTRL_MODE is set.
 *
 * \details 
 * Field: ::VTSS_CPU_SW_MODE . SW_SPI_SCK_OE
 */
#define  VTSS_F_CPU_SW_MODE_SW_SPI_SCK_OE(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_CPU_SW_MODE_SW_SPI_SCK_OE     VTSS_BIT(20)
#define  VTSS_X_CPU_SW_MODE_SW_SPI_SCK_OE(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Value to drive on SI_DQ output. This field is only used if
 * SW_MODE.SW_PIN_CTRL_MODE is set.
 *
 * \details 
 * Field: ::VTSS_CPU_SW_MODE . SW_SPI_SDQ
 */
#define  VTSS_F_CPU_SW_MODE_SW_SPI_SDQ(x)     VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_CPU_SW_MODE_SW_SPI_SDQ        VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_CPU_SW_MODE_SW_SPI_SDQ(x)     VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Set to enable drive of SI_DQ output. This field is only used if
 * SW_MODE.SW_PIN_CTRL_MODE is set.
 *
 * \details 
 * Field: ::VTSS_CPU_SW_MODE . SW_SPI_SDQ_OE
 */
#define  VTSS_F_CPU_SW_MODE_SW_SPI_SDQ_OE(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_CPU_SW_MODE_SW_SPI_SDQ_OE     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_CPU_SW_MODE_SW_SPI_SDQ_OE(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Set bit to activate SI_nEn output, each bit in this field maps to a
 * corresponding chip-select (0 though 3). A value of 1 in this register
 * cause SI_nEn output to drive 0. This field is only used if
 * SW_MODE.SW_PIN_CTRL_MODE is set.Note: Chip selects 1 though 3 are
 * available as alternate GPIO functions.
 *
 * \details 
 * Field: ::VTSS_CPU_SW_MODE . SW_SPI_CS
 */
#define  VTSS_F_CPU_SW_MODE_SW_SPI_CS(x)      VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_CPU_SW_MODE_SW_SPI_CS         VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_CPU_SW_MODE_SW_SPI_CS(x)      VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Set to enable drive of SI_nEn outputs, each bit in this field maps to a
 * corresponding chip-select (0 though 3). This field is only used if
 * SW_MODE.SW_PIN_CTRL_MODE is set.Note: Chip selects 1 though 3 are
 * available as alternate GPIO functions.
 *
 * \details 
 * Field: ::VTSS_CPU_SW_MODE . SW_SPI_CS_OE
 */
#define  VTSS_F_CPU_SW_MODE_SW_SPI_CS_OE(x)   VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_CPU_SW_MODE_SW_SPI_CS_OE      VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_CPU_SW_MODE_SW_SPI_CS_OE(x)   VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Current value of the SI_DI input.
 *
 * \details 
 * Field: ::VTSS_CPU_SW_MODE . SW_SPI_SDQ_IN
 */
#define  VTSS_F_CPU_SW_MODE_SW_SPI_SDQ_IN(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CPU_SW_MODE_SW_SPI_SDQ_IN     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CPU_SW_MODE_SW_SPI_SDQ_IN(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a CPU:PI_MST
 *
 * Parallel Interface Configuration
 */


/** 
 * \brief PI Master Configuration
 *
 * \details
 * Register: \a CPU:PI_MST:PI_MST_CFG
 */
#define VTSS_CPU_PI_MST_CFG                  VTSS_IOREG(VTSS_TO_CPU,0x3b)

/** 
 * \brief
 * Disable Automatic Tester Equipment mode for the parallel interface. This
 * mode is used during production testing for controlled loading of CPU.
 *
 * \details 
 * Field: ::VTSS_CPU_PI_MST_CFG . ATE_MODE_DIS
 */
#define  VTSS_F_CPU_PI_MST_CFG_ATE_MODE_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_CPU_PI_MST_CFG_ATE_MODE_DIS   VTSS_BIT(7)
#define  VTSS_X_CPU_PI_MST_CFG_ATE_MODE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Controls the clock-polarity of the PI Master.
 *
 * \details 
 * 0: Rising edge of the clock sets and samples signals.
 * 1: Falling edge of the clock sets and samples signals.
 *
 * Field: ::VTSS_CPU_PI_MST_CFG . CLK_POL
 */
#define  VTSS_F_CPU_PI_MST_CFG_CLK_POL(x)     VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_CPU_PI_MST_CFG_CLK_POL        VTSS_BIT(6)
#define  VTSS_X_CPU_PI_MST_CFG_CLK_POL(x)     VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Controls drive of address and control signals between transfers. See
 * also PI_MST_CTRL.CS_TRISTATE_CTRL.
 *
 * \details 
 * 0: Address and control signals are high-Z between transfers.
 * 1: Address and control signals are driven between transfers.
 *
 * Field: ::VTSS_CPU_PI_MST_CFG . TRISTATE_CTRL
 */
#define  VTSS_F_CPU_PI_MST_CFG_TRISTATE_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_CPU_PI_MST_CFG_TRISTATE_CTRL  VTSS_BIT(5)
#define  VTSS_X_CPU_PI_MST_CFG_TRISTATE_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Controls the clock for the PI Controller. Setting this field to 0 or 1
 * value is illegal.
 *
 * \details 
 * The PI interface frequency is: 250MHz/CLK_DIV.
 *
 * Field: ::VTSS_CPU_PI_MST_CFG . CLK_DIV
 */
#define  VTSS_F_CPU_PI_MST_CFG_CLK_DIV(x)     VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_CPU_PI_MST_CFG_CLK_DIV        VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_CPU_PI_MST_CFG_CLK_DIV(x)     VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief PI Master Control Register
 *
 * \details
 * This is a replicated register, where each replication holds the
 * configurations for one chip select. Changes to a value in one of the
 * replicated instances apply only to that chip select.
 *
 * Register: \a CPU:PI_MST:PI_MST_CTRL
 */
#define VTSS_CPU_PI_MST_CTRL                 VTSS_IOREG(VTSS_TO_CPU,0x3c)

/** 
 * \brief
 * Data width. In 8-bit mode, the unused data-bits contain additional
 * address information.
 *
 * \details 
 * 0: 8 bits
 * 1: 16 bits
 *
 * Field: ::VTSS_CPU_PI_MST_CTRL . DATA_WID
 */
#define  VTSS_F_CPU_PI_MST_CTRL_DATA_WID(x)   VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_CPU_PI_MST_CTRL_DATA_WID      VTSS_BIT(23)
#define  VTSS_X_CPU_PI_MST_CTRL_DATA_WID(x)   VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * Device-paced transfer enable. When enabled, use PI_nDone to end a
 * transfer.
 *
 * \details 
 * 0: Disabled
 * 1: Enabled
 *
 * Field: ::VTSS_CPU_PI_MST_CTRL . DEVICE_PACED_XFER_ENA
 */
#define  VTSS_F_CPU_PI_MST_CTRL_DEVICE_PACED_XFER_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_CPU_PI_MST_CTRL_DEVICE_PACED_XFER_ENA  VTSS_BIT(22)
#define  VTSS_X_CPU_PI_MST_CTRL_DEVICE_PACED_XFER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Enable timeout on device-paced transfers. If enabled, a
 * device_paced_transfer transfer does not wait indefinitely for assertion
 * of PI_nDone. If a timeout occurs, the TIMEOUT_ERR_STICKY bit is set in
 * the status register and the current transfer is terminated (read-data
 * will be invalid).
 *
 * \details 
 * Field: ::VTSS_CPU_PI_MST_CTRL . DEVICE_PACED_TIMEOUT_ENA
 */
#define  VTSS_F_CPU_PI_MST_CTRL_DEVICE_PACED_TIMEOUT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_CPU_PI_MST_CTRL_DEVICE_PACED_TIMEOUT_ENA  VTSS_BIT(21)
#define  VTSS_X_CPU_PI_MST_CTRL_DEVICE_PACED_TIMEOUT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

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
 * Field: ::VTSS_CPU_PI_MST_CTRL . DEVICE_PACED_TIMEOUT
 */
#define  VTSS_F_CPU_PI_MST_CTRL_DEVICE_PACED_TIMEOUT(x)  VTSS_ENCODE_BITFIELD(x,18,3)
#define  VTSS_M_CPU_PI_MST_CTRL_DEVICE_PACED_TIMEOUT     VTSS_ENCODE_BITMASK(18,3)
#define  VTSS_X_CPU_PI_MST_CTRL_DEVICE_PACED_TIMEOUT(x)  VTSS_EXTRACT_BITFIELD(x,18,3)

/** 
 * \brief
 * Controls drive of PI_nCS[x] between transfers.
 *
 * \details 
 * 0: PI_nCS[x] is high-Z between transfers.
 * 1: PI_nCS[x] is driven inactive between transfers.
 *
 * Field: ::VTSS_CPU_PI_MST_CTRL . CS_TRISTATE_CTRL
 */
#define  VTSS_F_CPU_PI_MST_CTRL_CS_TRISTATE_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_CPU_PI_MST_CTRL_CS_TRISTATE_CTRL  VTSS_BIT(17)
#define  VTSS_X_CPU_PI_MST_CTRL_CS_TRISTATE_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Polarity of PI_nDone for device-paced transfers.
 *
 * \details 
 * 0: PI_nDone is active low
 * 1: PI_nDone is active high
 *
 * Field: ::VTSS_CPU_PI_MST_CTRL . DONE_POL
 */
#define  VTSS_F_CPU_PI_MST_CTRL_DONE_POL(x)   VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_CPU_PI_MST_CTRL_DONE_POL      VTSS_BIT(16)
#define  VTSS_X_CPU_PI_MST_CTRL_DONE_POL(x)   VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Controls when data is sampled in relation to assertion of PI_nDone for
 * device-paced reads.
 *
 * \details 
 * 0: Data is sampled one PI_Clk cycle after PI_nDone goes active.
 * 1: Data is sampled on the same PI_Clk cycle where PI_nDone goes active.
 *
 * Field: ::VTSS_CPU_PI_MST_CTRL . SMPL_ON_DONE
 */
#define  VTSS_F_CPU_PI_MST_CTRL_SMPL_ON_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_CPU_PI_MST_CTRL_SMPL_ON_DONE  VTSS_BIT(15)
#define  VTSS_X_CPU_PI_MST_CTRL_SMPL_ON_DONE(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Number of wait states measured in PI_Clk cycles on both read and write
 * transfers.
 *
 * \details 
 * Field: ::VTSS_CPU_PI_MST_CTRL . WAITCC
 */
#define  VTSS_F_CPU_PI_MST_CTRL_WAITCC(x)     VTSS_ENCODE_BITFIELD(x,7,8)
#define  VTSS_M_CPU_PI_MST_CTRL_WAITCC        VTSS_ENCODE_BITMASK(7,8)
#define  VTSS_X_CPU_PI_MST_CTRL_WAITCC(x)     VTSS_EXTRACT_BITFIELD(x,7,8)

/** 
 * \brief
 * Number of PI_Clk cycles from address driven to PI_nCS[x] low.
 *
 * \details 
 * Field: ::VTSS_CPU_PI_MST_CTRL . CSCC
 */
#define  VTSS_F_CPU_PI_MST_CTRL_CSCC(x)       VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_CPU_PI_MST_CTRL_CSCC          VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_CPU_PI_MST_CTRL_CSCC(x)       VTSS_EXTRACT_BITFIELD(x,5,2)

/** 
 * \brief
 * Number of PI_Clk cycles from PI_nCS[x] low to PI_nOE low.
 *
 * \details 
 * Field: ::VTSS_CPU_PI_MST_CTRL . OECC
 */
#define  VTSS_F_CPU_PI_MST_CTRL_OECC(x)       VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_CPU_PI_MST_CTRL_OECC          VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_CPU_PI_MST_CTRL_OECC(x)       VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * Number of PI_Clk cycles to insert at the end of a transfer.
 *
 * \details 
 * Field: ::VTSS_CPU_PI_MST_CTRL . HLDCC
 */
#define  VTSS_F_CPU_PI_MST_CTRL_HLDCC(x)      VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_CPU_PI_MST_CTRL_HLDCC         VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_CPU_PI_MST_CTRL_HLDCC(x)      VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief PI Master Status Registers
 *
 * \details
 * This is a replicated register, where each replication holds the status
 * for one chip select.
 *
 * Register: \a CPU:PI_MST:PI_MST_STATUS
 */
#define VTSS_CPU_PI_MST_STATUS               VTSS_IOREG(VTSS_TO_CPU,0x3d)

/** 
 * \brief
 * If a timeout is enabled and timeout occurs during a device-paced
 * transfer, this bit is set.
 *
 * \details 
 * Field: ::VTSS_CPU_PI_MST_STATUS . TIMEOUT_ERR_STICKY
 */
#define  VTSS_F_CPU_PI_MST_STATUS_TIMEOUT_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PI_MST_STATUS_TIMEOUT_ERR_STICKY  VTSS_BIT(0)
#define  VTSS_X_CPU_PI_MST_STATUS_TIMEOUT_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PI Slave Configuration
 *
 * \details
 * Register: \a CPU:PI_MST:PI_SLV_CFG
 */
#define VTSS_CPU_PI_SLV_CFG                  VTSS_IOREG(VTSS_TO_CPU,0x3e)

/** 
 * \brief
 * See CPU:PI_MST:PI_SLV_CFG.DONEPOL_SET for more information.
 *
 * \details 
 * Field: ::VTSS_CPU_PI_SLV_CFG . DONEPOL_VAL
 */
#define  VTSS_F_CPU_PI_SLV_CFG_DONEPOL_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_CPU_PI_SLV_CFG_DONEPOL_VAL    VTSS_BIT(24)
#define  VTSS_X_CPU_PI_SLV_CFG_DONEPOL_VAL(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * Set this field to force the value in CPU:PI_MST:PI_SLV_CFG.DONEPOL_VAL
 * into CPU:CPU_REGS:GENERAL_CTRL.IF_PI_SLV_DONEPOL. This field is
 * immediately cleared.
 *
 * \details 
 * Field: ::VTSS_CPU_PI_SLV_CFG . DONEPOL_SET
 */
#define  VTSS_F_CPU_PI_SLV_CFG_DONEPOL_SET(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_CPU_PI_SLV_CFG_DONEPOL_SET    VTSS_BIT(23)
#define  VTSS_X_CPU_PI_SLV_CFG_DONEPOL_SET(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * Set to configure PI interface for big-endian mode.
 *
 * \details 
 * Field: ::VTSS_CPU_PI_SLV_CFG . BIGENDIAN
 */
#define  VTSS_F_CPU_PI_SLV_CFG_BIGENDIAN(x)   VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_CPU_PI_SLV_CFG_BIGENDIAN      VTSS_BIT(22)
#define  VTSS_X_CPU_PI_SLV_CFG_BIGENDIAN(x)   VTSS_EXTRACT_BITFIELD(x,22,1)

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
 * Field: ::VTSS_CPU_PI_SLV_CFG . DONEPARK
 */
#define  VTSS_F_CPU_PI_SLV_CFG_DONEPARK(x)    VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_CPU_PI_SLV_CFG_DONEPARK       VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_CPU_PI_SLV_CFG_DONEPARK(x)    VTSS_EXTRACT_BITFIELD(x,16,6)

/** 
 * \brief
 * Configures number of clock cycles to delay nDone indication for read
 * operations after accerss is done.
 *
 * \details 
 * n: Wait n clocks after read data ready before asserting nDone
 * indication.
 *
 * Field: ::VTSS_CPU_PI_SLV_CFG . DONEWAIT
 */
#define  VTSS_F_CPU_PI_SLV_CFG_DONEWAIT(x)    VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_CPU_PI_SLV_CFG_DONEWAIT       VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_CPU_PI_SLV_CFG_DONEWAIT(x)    VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Configures number of clock cycles after detecting asserted CS to
 * control/data is sampled.
 *
 * \details 
 * n: Wait n clocks after detecting CS before sampling control/data.
 *
 * Field: ::VTSS_CPU_PI_SLV_CFG . CSWAIT
 */
#define  VTSS_F_CPU_PI_SLV_CFG_CSWAIT(x)      VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CPU_PI_SLV_CFG_CSWAIT         VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CPU_PI_SLV_CFG_CSWAIT(x)      VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a CPU:MIIM_SLAVE
 *
 * Register group controlling MIIM slave attached to external interface AXI Master
 */


/** 
 * \brief MIIM Slave Spike Filter
 *
 * \details
 * Register: \a CPU:MIIM_SLAVE:MIIM_SLAVE_CFG
 */
#define VTSS_CPU_MIIM_SLAVE_CFG              VTSS_IOREG(VTSS_TO_CPU,0x3f)

/** 
 * \brief
 * Configuration of the spike filter width on the MDC and MDIO
 * inputs.Filters spikes with a width of (SPIKE_FILTER_CFG+1)*SYSTEM_CLK or
 * less.
 *
 * \details 
 * Field: ::VTSS_CPU_MIIM_SLAVE_CFG . SPIKE_FILTER_CFG
 */
#define  VTSS_F_CPU_MIIM_SLAVE_CFG_SPIKE_FILTER_CFG(x)  VTSS_ENCODE_BITFIELD(x,1,5)
#define  VTSS_M_CPU_MIIM_SLAVE_CFG_SPIKE_FILTER_CFG     VTSS_ENCODE_BITMASK(1,5)
#define  VTSS_X_CPU_MIIM_SLAVE_CFG_SPIKE_FILTER_CFG(x)  VTSS_EXTRACT_BITFIELD(x,1,5)

/** 
 * \brief
 * Set this field to enable the spike filter on the MDC and MDIO inputs.
 * When enabled the MIIM_SLAVE_CFG.SPIKE_FILTER_CFG field determines the
 * width of the spike filter.
 *
 * \details 
 * Field: ::VTSS_CPU_MIIM_SLAVE_CFG . SPIKE_FILTER_ENA
 */
#define  VTSS_F_CPU_MIIM_SLAVE_CFG_SPIKE_FILTER_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_MIIM_SLAVE_CFG_SPIKE_FILTER_ENA  VTSS_BIT(0)
#define  VTSS_X_CPU_MIIM_SLAVE_CFG_SPIKE_FILTER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

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
#define VTSS_CPU_VCORE_ACC_CFG               VTSS_IOREG(VTSS_TO_CPU,0x40)

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
#define VTSS_CPU_MSIX_ACC_CFG                VTSS_IOREG(VTSS_TO_CPU,0x41)

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
#define VTSS_CPU_EXT_IF_ACC_STAT             VTSS_IOREG(VTSS_TO_CPU,0x42)

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
 * Field: ::VTSS_CPU_EXT_IF_ACC_STAT . PI_ACC_STAT
 */
#define  VTSS_F_CPU_EXT_IF_ACC_STAT_PI_ACC_STAT(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_CPU_EXT_IF_ACC_STAT_PI_ACC_STAT     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_CPU_EXT_IF_ACC_STAT_PI_ACC_STAT(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

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
 * Register Group: \a CPU:PCIE
 *
 * PCIe Dual mode Controller Configuration
 */


/** 
 * \brief PCIe DM Controller control
 *
 * \details
 * Register: \a CPU:PCIE:PCIE_CTRL
 */
#define VTSS_CPU_PCIE_CTRL                   VTSS_IOREG(VTSS_TO_CPU,0x43)

/** 
 * \brief
 * This field is per function. Bit '0' indicates Func0(Switch Core
 * Function) powerup, Bit '1' indicates Func1(PoE function) powerup.Set
 * this field to send out PME from the controller, this is only possible if
 * PME is enabled in the PCIe core in Endpoint mode of operation. This
 * field is cleared automatically after controller has received the
 * request.In the D3 state the controller will transmit beacon and/or
 * assert #WAKE (see CPU::PCIE_CFG.WAKE_DIS for more information).In other
 * states the link will be transitioned to L0 (when applicable) and PME
 * event will then be transmitted upsteam.Note: This field is only valid in
 * End point mode of operation of controller.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_CTRL . POWERUP
 */
#define  VTSS_F_CPU_PCIE_CTRL_POWERUP(x)      VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_CPU_PCIE_CTRL_POWERUP         VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_CPU_PCIE_CTRL_POWERUP(x)      VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Set this field to generate PME_Turn_Off Messages to power down the link
 * to L2/L3. This would broadcast the messages to all the USPs.Note: This
 * is the functionality of Root Complex device to trigger the entry of link
 * to L2/L3. So, this configuration is only valid in RC mode of operation
 * of controller.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_CTRL . POWERDOWN
 */
#define  VTSS_F_CPU_PCIE_CTRL_POWERDOWN(x)    VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_PCIE_CTRL_POWERDOWN       VTSS_BIT(3)
#define  VTSS_X_CPU_PCIE_CTRL_POWERDOWN(x)    VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set this field to instruct PCIe Controller to send out an Unlock Message
 * in a Locked Transaction. Note: This functionality is only valid in RC
 * mode of operation of controller.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_CTRL . UNLOCK_MSG_TX
 */
#define  VTSS_F_CPU_PCIE_CTRL_UNLOCK_MSG_TX(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_PCIE_CTRL_UNLOCK_MSG_TX   VTSS_BIT(2)
#define  VTSS_X_CPU_PCIE_CTRL_UNLOCK_MSG_TX(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set this field to instruct the controller to flush of pending
 * requests/responses before stalling outbound traffic. Note: Enabling this
 * bit, only triggers the flushing process on controller. This bit is
 * immediately cleared and does not wait for actual time taken by the
 * controller to complete the flushing process.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_CTRL . FLUSH_ENA
 */
#define  VTSS_F_CPU_PCIE_CTRL_FLUSH_ENA(x)    VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_PCIE_CTRL_FLUSH_ENA       VTSS_BIT(1)
#define  VTSS_X_CPU_PCIE_CTRL_FLUSH_ENA(x)    VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set this field to instruct the controller to send a hot reset to the
 * upstream port.Note: This feature is only valid in Root Complex mode of
 * operation of controller and shouldn't be used when controller is
 * configured in End Point mode of operation.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_CTRL . INIT_RST_ENA
 */
#define  VTSS_F_CPU_PCIE_CTRL_INIT_RST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PCIE_CTRL_INIT_RST_ENA    VTSS_BIT(0)
#define  VTSS_X_CPU_PCIE_CTRL_INIT_RST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCIe DM Controller configuration
 *
 * \details
 * Register: \a CPU:PCIE:PCIE_CFG
 */
#define VTSS_CPU_PCIE_CFG                    VTSS_IOREG(VTSS_TO_CPU,0x44)

/** 
 * \brief
 * Set to disable clock gating requests from PCIe core.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_CFG . CG_DIS
 */
#define  VTSS_F_CPU_PCIE_CFG_CG_DIS(x)        VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_CPU_PCIE_CFG_CG_DIS           VTSS_BIT(11)
#define  VTSS_X_CPU_PCIE_CFG_CG_DIS(x)        VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Set to disable clock gating in PCIe core memories.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_CFG . MEM_CG_DIS
 */
#define  VTSS_F_CPU_PCIE_CFG_MEM_CG_DIS(x)    VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_CPU_PCIE_CFG_MEM_CG_DIS       VTSS_BIT(10)
#define  VTSS_X_CPU_PCIE_CFG_MEM_CG_DIS(x)    VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Set to defer incoming configuration requests with a Configuration
 * Request Retry Status.Note: Feature valid only in Endpoint mode of
 * operation of controller.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_CFG . CONF_REQ_RETRY_ENA
 */
#define  VTSS_F_CPU_PCIE_CFG_CONF_REQ_RETRY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_CPU_PCIE_CFG_CONF_REQ_RETRY_ENA  VTSS_BIT(9)
#define  VTSS_X_CPU_PCIE_CFG_CONF_REQ_RETRY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * This field is used to set the bits [21:20] of DBI Address bus during the
 * accesses to CDM/ELBI or iATU register Space of PCIE DM Controller.00--
 * Access to CDM register spaceDuring this access DBI address bus layout is
 * [31:22]- unused, [21:20]- 00, [19:16]- function number, [15:12]-
 * Reserved, [11:2]- DWORD Register Address, [1:0]- 0001-- Access to CDM
 * register space through shadow registers. Only Masks can be configured in
 * this mode. "DBI_CS2" is set in this access.Enable write of PCIe BAR
 * masks via PCIE register target. Registers
 * PCIE_DM_EP::PF0_TYPE0_HDR_BAR0_MASK_REGPCIE_DM_EP::PF0_TYPE0_HDR_BAR1_MA
 * SK_REGPCIE_DM_EP::BAR2_MASK_REGPCIE_DM_EP::BAR3_MASK_REGPCIE_DM_EP::PF0_
 * TYPE0_HDR_BAR4_MASK_REGPCIE_DM_EP::PF0_TYPE0_HDR_BAR5_MASK_REGPCIE_DM_EP
 * ::PF1_TYPE0_HDR_BAR0_MASK_REGPCIE_DM_EP::PF1_TYPE0_HDR_BAR1_MASK_REGPCIE
 * _DM_EP::PF1_TYPE0_HDR_BAR4_MASK_REGPCIE_DM_EP::PF1_TYPE0_HDR_BAR5_MASK_R
 * EGmay be written while this field is set.The minimum size for Memory and
 * IO BARs are 64K (mask 0xFFFF). Note: The low 4 bits of all BARs can be
 * written via the PCIe target when this field is not set.During this
 * access DBI address bus layout is [31:22]- unused, [21:20]- 01, [19:16]-
 * function number, [15:12]- Reserved, [11:2]- DWORD Register Address,
 * [1:0]- 0010-- Access to ELBI register spaceDuring this access DBI
 * address bus layout is [31:22]- unused, [21:20]- 10, [19:16]- function
 * number, [15:12]- BAR number, [11:2]- DWORD Register Address, [1:0]-
 * 0011-- Access to iATU register spaceDuring this access DBI address bus
 * layout is [31:22]- unused, [21:20]- 11,[19] - 0, [18:0]-- iATU
 * AddressiATU Address consists of [18:17]- Reserved, [16:9]- Region
 * number, [8:0] - Register Address as indicated in Controller Databook for
 * accessing different Configuration Registers within a Region.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_CFG . PCIE_DBI_ACCESS_ENA
 */
#define  VTSS_F_CPU_PCIE_CFG_PCIE_DBI_ACCESS_ENA(x)  VTSS_ENCODE_BITFIELD(x,7,2)
#define  VTSS_M_CPU_PCIE_CFG_PCIE_DBI_ACCESS_ENA     VTSS_ENCODE_BITMASK(7,2)
#define  VTSS_X_CPU_PCIE_CFG_PCIE_DBI_ACCESS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,2)

/** 
 * \brief
 * Set this field to disable initialization of the PCIe link.By default the
 * PCIe core will start up and try to acchieve link when the SERDES is
 * started, by setting this field before starting the SERDES it is possible
 * to make changes to the PCIe configruration/registers prior to linking
 * with the root complex.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_CFG . LTSSM_DIS
 */
#define  VTSS_F_CPU_PCIE_CFG_LTSSM_DIS(x)     VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_CPU_PCIE_CFG_LTSSM_DIS        VTSS_BIT(6)
#define  VTSS_X_CPU_PCIE_CFG_LTSSM_DIS(x)     VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Set to add the PCIe core memories to the RAM integrity ring.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_CFG . MEM_RING_CORE_ENA
 */
#define  VTSS_F_CPU_PCIE_CFG_MEM_RING_CORE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_CPU_PCIE_CFG_MEM_RING_CORE_ENA  VTSS_BIT(5)
#define  VTSS_X_CPU_PCIE_CFG_MEM_RING_CORE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * This field can be used by the masters driving the PCIE link to prevent
 * the controller from entering the L1 state if there is some data still
 * left for transmission. When the data is transmitted, master should clear
 * this field inorder for normal PCIE power management to happen.
 *
 * \details 
 * 0: Normal operation. When idle, controller assumes no traffic pending 
 * and enters L1
 * 1: Prevents the controller from entering the L1 state or exits L1 state
 * if already in L1 state.
 *
 * Field: ::VTSS_CPU_PCIE_CFG . MSTR_XFER_PENDING
 */
#define  VTSS_F_CPU_PCIE_CFG_MSTR_XFER_PENDING(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CPU_PCIE_CFG_MSTR_XFER_PENDING  VTSS_BIT(4)
#define  VTSS_X_CPU_PCIE_CFG_MSTR_XFER_PENDING(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Controls generation of WAKE signal generation during wake-up from low
 * power modes.Note: Unused in RC mode of operation of controller
 *
 * \details 
 * 0:Wake signal generation enabled
 * 1:Wake signal generation disabled.
 *
 * Field: ::VTSS_CPU_PCIE_CFG . WAKE_DIS
 */
#define  VTSS_F_CPU_PCIE_CFG_WAKE_DIS(x)      VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_PCIE_CFG_WAKE_DIS         VTSS_BIT(3)
#define  VTSS_X_CPU_PCIE_CFG_WAKE_DIS(x)      VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Polarity of Wake signal as used in EP & RC modes:In EP Mode of
 * Controller:Polarity of the PCIe WAKE output, WAKE is typically an active
 * low output - but if an amplifier is needed for driving a large WAKE net
 * then polarity may need to be changed.In RC Mode of Controller:Polarity
 * of the PCIe WAKE input as received on WAKE PAD. Default is an active low
 * signal. This can be reconfigured by changing the value in this register.
 *
 * \details 
 * 0: Active low
 * 1: Active high
 *
 * Field: ::VTSS_CPU_PCIE_CFG . WAKE_POL
 */
#define  VTSS_F_CPU_PCIE_CFG_WAKE_POL(x)      VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_PCIE_CFG_WAKE_POL         VTSS_BIT(2)
#define  VTSS_X_CPU_PCIE_CFG_WAKE_POL(x)      VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set to permanently drive PCIe WAKE output, by default the WAKE output is
 * only driven when active and thus allowing pull-resistor network.Note:
 * Unused in RC mode of operation.
 *
 * \details 
 * 0: Only drive output when active.
 * 1: Always drive output.
 *
 * Field: ::VTSS_CPU_PCIE_CFG . WAKE_OE
 */
#define  VTSS_F_CPU_PCIE_CFG_WAKE_OE(x)       VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_PCIE_CFG_WAKE_OE          VTSS_BIT(1)
#define  VTSS_X_CPU_PCIE_CFG_WAKE_OE(x)       VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * By default, when controller is in EP mode of operation, inbound address
 * translation is done in hardware for TLP matching BAR0, 2 for either of
 * PF0/1 and the iATU of controller need not be configured. This
 * functionality can be bypassed by setting this field, in which case the
 * in bound address translation should happen by configuring the iATU of
 * controller.Note: This field is relevant only in EP mode of operation of
 * controller.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_CFG . BYPASS_INBOUND_AT
 */
#define  VTSS_F_CPU_PCIE_CFG_BYPASS_INBOUND_AT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PCIE_CFG_BYPASS_INBOUND_AT  VTSS_BIT(0)
#define  VTSS_X_CPU_PCIE_CFG_BYPASS_INBOUND_AT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCIe DM Controller status
 *
 * \details
 * Register: \a CPU:PCIE:PCIE_STAT
 */
#define VTSS_CPU_PCIE_STAT                   VTSS_IOREG(VTSS_TO_CPU,0x45)

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
 * Field: ::VTSS_CPU_PCIE_STAT . LTSSM_STATE
 */
#define  VTSS_F_CPU_PCIE_STAT_LTSSM_STATE(x)  VTSS_ENCODE_BITFIELD(x,9,6)
#define  VTSS_M_CPU_PCIE_STAT_LTSSM_STATE     VTSS_ENCODE_BITMASK(9,6)
#define  VTSS_X_CPU_PCIE_STAT_LTSSM_STATE(x)  VTSS_EXTRACT_BITFIELD(x,9,6)

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
 * Field: ::VTSS_CPU_PCIE_STAT . LINK_STATE
 */
#define  VTSS_F_CPU_PCIE_STAT_LINK_STATE(x)   VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_CPU_PCIE_STAT_LINK_STATE      VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_CPU_PCIE_STAT_LINK_STATE(x)   VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * The current power management state of the PCIe core per Function. Lower
 * 3 bits [2:0] indicate PM State of Func 0 (SwC Function), Upper 3 bits
 * [5:3] indicate PM State of Func1(PoE Function).
 *
 * \details 
 * 0: D0
 * 1: D1
 * 2: D2
 * 3: D3
 * 4: D0-Uninitialized

 *
 * Field: ::VTSS_CPU_PCIE_STAT . PM_STATE
 */
#define  VTSS_F_CPU_PCIE_STAT_PM_STATE(x)     VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CPU_PCIE_STAT_PM_STATE        VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CPU_PCIE_STAT_PM_STATE(x)     VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Auxiliary power configuration
 *
 * \details
 * Register: \a CPU:PCIE:PCIE_AUX_CFG
 */
#define VTSS_CPU_PCIE_AUX_CFG                VTSS_IOREG(VTSS_TO_CPU,0x46)

/** 
 * \brief
 * Set to force "detection" of PCIe auxiliary power.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_AUX_CFG . AUX_POWER_VAL
 */
#define  VTSS_F_CPU_PCIE_AUX_CFG_AUX_POWER_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PCIE_AUX_CFG_AUX_POWER_VAL  VTSS_BIT(0)
#define  VTSS_X_CPU_PCIE_AUX_CFG_AUX_POWER_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCIe endpoint debug status
 *
 * \details
 * Register: \a CPU:PCIE:PCIE_DBG_STAT
 */
#define VTSS_CPU_PCIE_DBG_STAT               VTSS_IOREG(VTSS_TO_CPU,0x47)

/** 
 * \brief
 * Set when the Power Management is exiting L2 state. This value is read
 * directly from other clock domain, keep reading until same value was read
 * twice in a row - then read was sucessful.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_DBG_STAT . PM_L2_EXIT
 */
#define  VTSS_F_CPU_PCIE_DBG_STAT_PM_L2_EXIT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_PCIE_DBG_STAT_PM_L2_EXIT  VTSS_BIT(2)
#define  VTSS_X_CPU_PCIE_DBG_STAT_PM_L2_EXIT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set when the PCIe Data Link Layer is up and ready to receive/transmit
 * packages. This value is read directly from other clock domain, keep
 * reading until same value was read twice in a row - then read was
 * sucessful.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_DBG_STAT . DATA_LINK_LAYER_UP
 */
#define  VTSS_F_CPU_PCIE_DBG_STAT_DATA_LINK_LAYER_UP(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_PCIE_DBG_STAT_DATA_LINK_LAYER_UP  VTSS_BIT(1)
#define  VTSS_X_CPU_PCIE_DBG_STAT_DATA_LINK_LAYER_UP(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set when the physical layer of the Controller is up.  This value is read
 * directly from other clock domain, keep reading until same value was read
 * twice in a row - then read was sucessful.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_DBG_STAT . PHY_LAYER_UP
 */
#define  VTSS_F_CPU_PCIE_DBG_STAT_PHY_LAYER_UP(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PCIE_DBG_STAT_PHY_LAYER_UP  VTSS_BIT(0)
#define  VTSS_X_CPU_PCIE_DBG_STAT_PHY_LAYER_UP(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Additional inbound reply information
 *
 * \details
 * Register: \a CPU:PCIE:PCIEMST_REPLY_INFO
 */
#define VTSS_CPU_PCIEMST_REPLY_INFO          VTSS_IOREG(VTSS_TO_CPU,0x48)

/** 
 * \brief
 * This field allows additional PCIe-transaction settings in PCIe Master
 * Reply. The settings in this register is applied to all PCIe inbound
 * accesses.
 *
 * \details 
 * [0] EP-field.
 * [2:1] This field indicates response to be sent out on PCIe link in case
 * of successful Write Request on PCIe Master, default to "00"
 * [4:3] This field indicates response to be sent out on PCIe link in case
 * of successful Read Request on PCIe Master, default to "00"
 * 00-SC(Successful Completion)
 * 01-CA(Completer Abort)
 * 10-UR(Unsupported Request)
 * 11-SC(Successful Completion)
 *
 * Field: ::VTSS_CPU_PCIEMST_REPLY_INFO . MST_REPLY_INFO
 */
#define  VTSS_F_CPU_PCIEMST_REPLY_INFO_MST_REPLY_INFO(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_CPU_PCIEMST_REPLY_INFO_MST_REPLY_INFO     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_CPU_PCIEMST_REPLY_INFO_MST_REPLY_INFO(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief 64-bit BAR0&1 lower offset of Physical Function1(PoE Func)  into Vcore Memory Space
 *
 * \details
 * Register: \a CPU:PCIE:PCIEMST_PF1_BAR0_OFFSET_LOW
 */
#define VTSS_CPU_PCIEMST_PF1_BAR0_OFFSET_LOW  VTSS_IOREG(VTSS_TO_CPU,0x49)

/** 
 * \brief
 * BAR0&BAR1 is combined 64-bit BAR which by default, assigned to 32MB of
 * CSR Chip Registers Address space starting at offset 0x610000000. It can
 * be reconfigured to support any other address region in Address space by
 * configuring this register. Lower 24 bits can be programmed into this
 * register while upper 4bits can be programmed into PF1_BAR0_OFFSET_HIGH
 * register. The corresponding mask need to be programmed in the
 * PCIEMST_PF1_BAR0_MASK_LOW, PCIEMST_PF1_BAR0_MASK_HIGH registers.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIEMST_PF1_BAR0_OFFSET_LOW . PF1_BAR0_OFFSET_LOW
 */
#define  VTSS_F_CPU_PCIEMST_PF1_BAR0_OFFSET_LOW_PF1_BAR0_OFFSET_LOW(x)  VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_CPU_PCIEMST_PF1_BAR0_OFFSET_LOW_PF1_BAR0_OFFSET_LOW     VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_CPU_PCIEMST_PF1_BAR0_OFFSET_LOW_PF1_BAR0_OFFSET_LOW(x)  VTSS_EXTRACT_BITFIELD(x,8,24)


/** 
 * \brief MSB 4 bits of PF1_BAR0_OFFSET
 *
 * \details
 * Register: \a CPU:PCIE:PCIEMST_PF1_BAR0_OFFSET_HIGH
 */
#define VTSS_CPU_PCIEMST_PF1_BAR0_OFFSET_HIGH  VTSS_IOREG(VTSS_TO_CPU,0x4a)

/** 
 * \brief
 * See PCIEMST_PF1_BAR0_OFFSET_LOW.PF1_BAR0_OFFSET_LOW for more details.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIEMST_PF1_BAR0_OFFSET_HIGH . PF1_BAR0_OFFSET_HIGH
 */
#define  VTSS_F_CPU_PCIEMST_PF1_BAR0_OFFSET_HIGH_PF1_BAR0_OFFSET_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CPU_PCIEMST_PF1_BAR0_OFFSET_HIGH_PF1_BAR0_OFFSET_HIGH     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CPU_PCIEMST_PF1_BAR0_OFFSET_HIGH_PF1_BAR0_OFFSET_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief BAR0 mask for space configured in PCIEMST_PF1_BAR0_OFFSET_LOW
 *
 * \details
 * Register: \a CPU:PCIE:PCIEMST_PF1_BAR0_MASK_LOW
 */
#define VTSS_CPU_PCIEMST_PF1_BAR0_MASK_LOW   VTSS_IOREG(VTSS_TO_CPU,0x4b)

/** 
 * \brief
 * See PCIEMST_PF1_BAR0_OFFSET_LOW.PF1_BAR0_OFFSET_LOW for more details.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIEMST_PF1_BAR0_MASK_LOW . PF1_BAR0_MASK_LOW
 */
#define  VTSS_F_CPU_PCIEMST_PF1_BAR0_MASK_LOW_PF1_BAR0_MASK_LOW(x)  VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_CPU_PCIEMST_PF1_BAR0_MASK_LOW_PF1_BAR0_MASK_LOW     VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_CPU_PCIEMST_PF1_BAR0_MASK_LOW_PF1_BAR0_MASK_LOW(x)  VTSS_EXTRACT_BITFIELD(x,8,24)


/** 
 * \brief MSB Mask bits of PCIEMST_PF1_BAR0_MASK_LOW
 *
 * \details
 * Register: \a CPU:PCIE:PCIEMST_PF1_BAR0_MASK_HIGH
 */
#define VTSS_CPU_PCIEMST_PF1_BAR0_MASK_HIGH  VTSS_IOREG(VTSS_TO_CPU,0x4c)

/** 
 * \brief
 * See PCIEMST_PF1_BAR0_OFFSET_LOW.PF1_BAR0_OFFSET_LOW for more details.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIEMST_PF1_BAR0_MASK_HIGH . PF1_BAR0_MASK_HIGH
 */
#define  VTSS_F_CPU_PCIEMST_PF1_BAR0_MASK_HIGH_PF1_BAR0_MASK_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CPU_PCIEMST_PF1_BAR0_MASK_HIGH_PF1_BAR0_MASK_HIGH     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CPU_PCIEMST_PF1_BAR0_MASK_HIGH_PF1_BAR0_MASK_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief 64-bit BAR2&3 lower offset of Physical Function0(SwC Func)  into Vcore Memory Space
 *
 * \details
 * Register: \a CPU:PCIE:PCIEMST_PF0_BAR2_OFFSET_LOW
 */
#define VTSS_CPU_PCIEMST_PF0_BAR2_OFFSET_LOW  VTSS_IOREG(VTSS_TO_CPU,0x4d)

/** 
 * \brief
 * BAR2&BAR3 is combined 64-bit BAR which by default, assigned to 1MB of
 * Vcore Chip Registers Address space starting at offset 0x600000000. It
 * can be reconfigured to support any other address region in Vcore Address
 * space by configuring this register. Lower 24 bits can be programmed into
 * this register while upper 4bits can be programmed into
 * PF0_BAR2_OFFSET_HIGH register. The corresponding mask need to be
 * programmed in the PCIEMST_PF0_BAR2_MASK_LOW, PCIEMST_PF0_BAR2_MASK_HIGH
 * registers.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIEMST_PF0_BAR2_OFFSET_LOW . PF0_BAR2_OFFSET_LOW
 */
#define  VTSS_F_CPU_PCIEMST_PF0_BAR2_OFFSET_LOW_PF0_BAR2_OFFSET_LOW(x)  VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_CPU_PCIEMST_PF0_BAR2_OFFSET_LOW_PF0_BAR2_OFFSET_LOW     VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_CPU_PCIEMST_PF0_BAR2_OFFSET_LOW_PF0_BAR2_OFFSET_LOW(x)  VTSS_EXTRACT_BITFIELD(x,8,24)


/** 
 * \brief MSB 4 bits of PF0_BAR2_OFFSET
 *
 * \details
 * Register: \a CPU:PCIE:PCIEMST_PF0_BAR2_OFFSET_HIGH
 */
#define VTSS_CPU_PCIEMST_PF0_BAR2_OFFSET_HIGH  VTSS_IOREG(VTSS_TO_CPU,0x4e)

/** 
 * \brief
 * See PCIEMST_PF0_BAR2_OFFSET_LOW.PF0_BAR2_OFFSET_LOW for more details.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIEMST_PF0_BAR2_OFFSET_HIGH . PF0_BAR2_OFFSET_HIGH
 */
#define  VTSS_F_CPU_PCIEMST_PF0_BAR2_OFFSET_HIGH_PF0_BAR2_OFFSET_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CPU_PCIEMST_PF0_BAR2_OFFSET_HIGH_PF0_BAR2_OFFSET_HIGH     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CPU_PCIEMST_PF0_BAR2_OFFSET_HIGH_PF0_BAR2_OFFSET_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief BAR2 mask for space configured in PCIEMST_PF0_BAR2_OFFSET_LOW
 *
 * \details
 * Register: \a CPU:PCIE:PCIEMST_PF0_BAR2_MASK_LOW
 */
#define VTSS_CPU_PCIEMST_PF0_BAR2_MASK_LOW   VTSS_IOREG(VTSS_TO_CPU,0x4f)

/** 
 * \brief
 * See PCIEMST_PF0_BAR2_OFFSET_LOW.PF0_BAR2_OFFSET_LOW for more details.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIEMST_PF0_BAR2_MASK_LOW . PF0_BAR2_MASK_LOW
 */
#define  VTSS_F_CPU_PCIEMST_PF0_BAR2_MASK_LOW_PF0_BAR2_MASK_LOW(x)  VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_CPU_PCIEMST_PF0_BAR2_MASK_LOW_PF0_BAR2_MASK_LOW     VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_CPU_PCIEMST_PF0_BAR2_MASK_LOW_PF0_BAR2_MASK_LOW(x)  VTSS_EXTRACT_BITFIELD(x,8,24)


/** 
 * \brief MSB Mask bits of PCIEMST_PF0_BAR2_MASK_LOW
 *
 * \details
 * Register: \a CPU:PCIE:PCIEMST_PF0_BAR2_MASK_HIGH
 */
#define VTSS_CPU_PCIEMST_PF0_BAR2_MASK_HIGH  VTSS_IOREG(VTSS_TO_CPU,0x50)

/** 
 * \brief
 * See PCIEMST_PF0_BAR2_OFFSET_LOW.PF0_BAR2_OFFSET_LOW for more details.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIEMST_PF0_BAR2_MASK_HIGH . PF0_BAR2_MASK_HIGH
 */
#define  VTSS_F_CPU_PCIEMST_PF0_BAR2_MASK_HIGH_PF0_BAR2_MASK_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CPU_PCIEMST_PF0_BAR2_MASK_HIGH_PF0_BAR2_MASK_HIGH     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CPU_PCIEMST_PF0_BAR2_MASK_HIGH_PF0_BAR2_MASK_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Configuration to bypass iATU(Internal Address Translation Unit) of Controller
 *
 * \details
 * Register: \a CPU:PCIE:PCIESLV_IATU_BYPASS
 */
#define VTSS_CPU_PCIESLV_IATU_BYPASS         VTSS_IOREG(VTSS_TO_CPU,0x51)

/** 
 * \brief
 * When set, bypass all the issued AXI Write Requests onto PCIe AXI Slave
 * in undergoing address translation through iATU of Controller.
 *
 * \details 
 * 0: Don't Bypass iATU
 * 1: Bypass iATU
 *
 * Field: ::VTSS_CPU_PCIESLV_IATU_BYPASS . WR_REQ_BYPASS_ENA
 */
#define  VTSS_F_CPU_PCIESLV_IATU_BYPASS_WR_REQ_BYPASS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_PCIESLV_IATU_BYPASS_WR_REQ_BYPASS_ENA  VTSS_BIT(1)
#define  VTSS_X_CPU_PCIESLV_IATU_BYPASS_WR_REQ_BYPASS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * When set, bypass all the issued AXI Read Requests onto PCIe AXI Slave in
 * undergoing address translation through iATU of Controller.
 *
 * \details 
 * 0: Don't Bypass iATU
 * 1: Bypass iATU
 *
 * Field: ::VTSS_CPU_PCIESLV_IATU_BYPASS . RD_REQ_BYPASS_ENA
 */
#define  VTSS_F_CPU_PCIESLV_IATU_BYPASS_RD_REQ_BYPASS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PCIESLV_IATU_BYPASS_RD_REQ_BYPASS_ENA  VTSS_BIT(0)
#define  VTSS_X_CPU_PCIESLV_IATU_BYPASS_RD_REQ_BYPASS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief FDMA access into PCIe address space
 *
 * \details
 * Register: \a CPU:PCIE:PCIESLV_FDMA
 */
#define VTSS_CPU_PCIESLV_FDMA                VTSS_IOREG(VTSS_TO_CPU,0x52)

/** 
 * \brief
 * This field allows configuration of outbound PCIe-transaction TC field.
 * This is applied to all FDMA initiated outbound PCIe accesses.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIESLV_FDMA . FDMA_TC
 */
#define  VTSS_F_CPU_PCIESLV_FDMA_FDMA_TC(x)   VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_CPU_PCIESLV_FDMA_FDMA_TC      VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_CPU_PCIESLV_FDMA_FDMA_TC(x)   VTSS_EXTRACT_BITFIELD(x,2,3)

/** 
 * \brief
 * This field allows configuration of outbound PCIe-transaction ATTR field.
 * This is applied to all FDMA initiated outbound PCIe accesses.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIESLV_FDMA . FDMA_ATTR
 */
#define  VTSS_F_CPU_PCIESLV_FDMA_FDMA_ATTR(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CPU_PCIESLV_FDMA_FDMA_ATTR     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CPU_PCIESLV_FDMA_FDMA_ATTR(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CPU access into PCIe address space
 *
 * \details
 * Register: \a CPU:PCIE:PCIESLV_CPU
 */
#define VTSS_CPU_PCIESLV_CPU                 VTSS_IOREG(VTSS_TO_CPU,0x53)

/** 
 * \brief
 * Reserved, must be 0.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIESLV_CPU . CPU_RESERVED2
 */
#define  VTSS_F_CPU_PCIESLV_CPU_CPU_RESERVED2(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_CPU_PCIESLV_CPU_CPU_RESERVED2  VTSS_BIT(21)
#define  VTSS_X_CPU_PCIESLV_CPU_CPU_RESERVED2(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * This field allows configuration of outbound PCIe-transaction MSG field.
 * This is applied to all non-FDMA initiated outbound PCIe accesses.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIESLV_CPU . CPU_MSG_CODE
 */
#define  VTSS_F_CPU_PCIESLV_CPU_CPU_MSG_CODE(x)  VTSS_ENCODE_BITFIELD(x,13,8)
#define  VTSS_M_CPU_PCIESLV_CPU_CPU_MSG_CODE     VTSS_ENCODE_BITMASK(13,8)
#define  VTSS_X_CPU_PCIESLV_CPU_CPU_MSG_CODE(x)  VTSS_EXTRACT_BITFIELD(x,13,8)

/** 
 * \brief
 * This field allows configuration of outbound PCIe-transaction TC field.
 * This is applied to all non-FDMA initiated outbound PCIe accesses.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIESLV_CPU . CPU_TC
 */
#define  VTSS_F_CPU_PCIESLV_CPU_CPU_TC(x)     VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_CPU_PCIESLV_CPU_CPU_TC        VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_CPU_PCIESLV_CPU_CPU_TC(x)     VTSS_EXTRACT_BITFIELD(x,10,3)

/** 
 * \brief
 * This field allows configuration of outbound PCIe-transaction ATTR field.
 * This is applied to all non-FDMA initiated outbound PCIe accesses.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIESLV_CPU . CPU_ATTR
 */
#define  VTSS_F_CPU_PCIESLV_CPU_CPU_ATTR(x)   VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_CPU_PCIESLV_CPU_CPU_ATTR      VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_CPU_PCIESLV_CPU_CPU_ATTR(x)   VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Reserved, must be 0.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIESLV_CPU . CPU_RESERVED1
 */
#define  VTSS_F_CPU_PCIESLV_CPU_CPU_RESERVED1(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_CPU_PCIESLV_CPU_CPU_RESERVED1  VTSS_BIT(7)
#define  VTSS_X_CPU_PCIESLV_CPU_CPU_RESERVED1(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * This field allows configuration of outbound PCIe-transaction EP field.
 * This is applied to all non-FDMA initiated outbound PCIe accesses.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIESLV_CPU . CPU_EP
 */
#define  VTSS_F_CPU_PCIESLV_CPU_CPU_EP(x)     VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_CPU_PCIESLV_CPU_CPU_EP        VTSS_BIT(6)
#define  VTSS_X_CPU_PCIESLV_CPU_CPU_EP(x)     VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Reserved, must be 0.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIESLV_CPU . CPU_RESERVED0
 */
#define  VTSS_F_CPU_PCIESLV_CPU_CPU_RESERVED0(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_CPU_PCIESLV_CPU_CPU_RESERVED0  VTSS_BIT(5)
#define  VTSS_X_CPU_PCIESLV_CPU_CPU_RESERVED0(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * This field allows configuration of outbound PCIe-transaction TYPE field.
 * This is applied to all non-FDMA initiated outbound PCIe accesses.
 *
 * \details 
 * Encoding as defined by PCIe standard.
 *
 * Field: ::VTSS_CPU_PCIESLV_CPU . CPU_TYPE
 */
#define  VTSS_F_CPU_PCIESLV_CPU_CPU_TYPE(x)   VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_CPU_PCIESLV_CPU_CPU_TYPE      VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_CPU_PCIESLV_CPU_CPU_TYPE(x)   VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief 3rd Header DW that is to be sent in a PCIE Msg/MsgD
 *
 * \details
 * Register: \a CPU:PCIE:PCIESLV_MSG_3DW
 */
#define VTSS_CPU_PCIESLV_MSG_3DW             VTSS_IOREG(VTSS_TO_CPU,0x54)

/** 
 * \brief
 * 32-bit value of 3rd DW that is to be sent in outbound PCIE Msg/MsgD Type 
 *
 * \details 
 * Field: ::VTSS_CPU_PCIESLV_MSG_3DW . PCIESLV_MSG_3DW
 */
#define  VTSS_F_CPU_PCIESLV_MSG_3DW_PCIESLV_MSG_3DW(x)  (x)
#define  VTSS_M_CPU_PCIESLV_MSG_3DW_PCIESLV_MSG_3DW     0xffffffff
#define  VTSS_X_CPU_PCIESLV_MSG_3DW_PCIESLV_MSG_3DW(x)  (x)


/** 
 * \brief 4th Header DW that is to be sent in a PCIE Msg/MsgD
 *
 * \details
 * Register: \a CPU:PCIE:PCIESLV_MSG_4DW
 */
#define VTSS_CPU_PCIESLV_MSG_4DW             VTSS_IOREG(VTSS_TO_CPU,0x55)

/** 
 * \brief
 * 32-bit value of 4th DW that is to be sent in outbound PCIE Msg/MsgD Type 
 *
 * \details 
 * Field: ::VTSS_CPU_PCIESLV_MSG_4DW . PCIESLV_MSG_4DW
 */
#define  VTSS_F_CPU_PCIESLV_MSG_4DW_PCIESLV_MSG_4DW(x)  (x)
#define  VTSS_M_CPU_PCIESLV_MSG_4DW_PCIESLV_MSG_4DW     0xffffffff
#define  VTSS_X_CPU_PCIESLV_MSG_4DW_PCIESLV_MSG_4DW(x)  (x)


/** 
 * \brief PCIe RST configuration
 *
 * \details
 * Register: \a CPU:PCIE:PCIERST_CFG
 */
#define VTSS_CPU_PCIERST_CFG                 VTSS_IOREG(VTSS_TO_CPU,0x56)

/** 
 * \brief
 * Set this field to force power on reset(Cold reset) to value in
 * PCIERST_CFG.POWERONRST_VAL.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIERST_CFG . POWERONRST_FORCE
 */
#define  VTSS_F_CPU_PCIERST_CFG_POWERONRST_FORCE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_PCIERST_CFG_POWERONRST_FORCE  VTSS_BIT(2)
#define  VTSS_X_CPU_PCIERST_CFG_POWERONRST_FORCE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * See PCIERST_CFG.POWERONRST_FORCE for more information.
 *
 * \details 
 * 0: Reset is asserted
 * 1: Reset is not asserted
 *
 * Field: ::VTSS_CPU_PCIERST_CFG . POWERONRST_VAL
 */
#define  VTSS_F_CPU_PCIERST_CFG_POWERONRST_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_PCIERST_CFG_POWERONRST_VAL  VTSS_BIT(1)
#define  VTSS_X_CPU_PCIERST_CFG_POWERONRST_VAL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * By default, AMBA resets like VCORE SOFT RESET, WDT RESET, VCORE CPU
 * FORCE RESET will be propagated as hot reset towards controller(core,
 * non-sticky registers of controller, phy will be reset).Setting this
 * field disables the propagation of above resets as hot reset towards
 * controller. 
 *
 * \details 
 * 0 : Propagate reset towards controller
 * 1 : Disable propagation of reset towards controller.
 *
 * Field: ::VTSS_CPU_PCIERST_CFG . AMBA_RST_DIS
 */
#define  VTSS_F_CPU_PCIERST_CFG_AMBA_RST_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PCIERST_CFG_AMBA_RST_DIS  VTSS_BIT(0)
#define  VTSS_X_CPU_PCIERST_CFG_AMBA_RST_DIS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CORR, FATAL, NONFATAL error, Unlock, PM MSG stickies
 *
 * \details
 * Register: \a CPU:PCIE:PCIE_MSG_STICKY
 */
#define VTSS_CPU_PCIE_MSG_STICKY             VTSS_IOREG(VTSS_TO_CPU,0x57)

/** 
 * \brief
 * Sticky indicates that Controller received a Correctable error message.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_MSG_STICKY . CORR_ERR_STICKY
 */
#define  VTSS_F_CPU_PCIE_MSG_STICKY_CORR_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_CPU_PCIE_MSG_STICKY_CORR_ERR_STICKY  VTSS_BIT(7)
#define  VTSS_X_CPU_PCIE_MSG_STICKY_CORR_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Sticky indicates that Controller received a Fatal error message.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_MSG_STICKY . FATAL_ERR_STICKY
 */
#define  VTSS_F_CPU_PCIE_MSG_STICKY_FATAL_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_CPU_PCIE_MSG_STICKY_FATAL_ERR_STICKY  VTSS_BIT(6)
#define  VTSS_X_CPU_PCIE_MSG_STICKY_FATAL_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Sticky indicates that Controller received a non fatal error message.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_MSG_STICKY . NONFATAL_ERR_STICKY
 */
#define  VTSS_F_CPU_PCIE_MSG_STICKY_NONFATAL_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_CPU_PCIE_MSG_STICKY_NONFATAL_ERR_STICKY  VTSS_BIT(5)
#define  VTSS_X_CPU_PCIE_MSG_STICKY_NONFATAL_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Sticky indicates that Controller received an Unlock message.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_MSG_STICKY . UNLOCK_MSG_STICKY
 */
#define  VTSS_F_CPU_PCIE_MSG_STICKY_UNLOCK_MSG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CPU_PCIE_MSG_STICKY_UNLOCK_MSG_STICKY  VTSS_BIT(4)
#define  VTSS_X_CPU_PCIE_MSG_STICKY_UNLOCK_MSG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Sticky indicates that controller received a PM_PME message.Note: This is
 * valid only in Root Complex mode of operation.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_MSG_STICKY . PM_PME_MSG_STICKY
 */
#define  VTSS_F_CPU_PCIE_MSG_STICKY_PM_PME_MSG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_PCIE_MSG_STICKY_PM_PME_MSG_STICKY  VTSS_BIT(3)
#define  VTSS_X_CPU_PCIE_MSG_STICKY_PM_PME_MSG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Sticky indicates that Controller received a PM_TO_ACK MSG.Note: This is
 * valid only in Root Complex mode of operation.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_MSG_STICKY . PM_TO_ACK_MSG_STICKY
 */
#define  VTSS_F_CPU_PCIE_MSG_STICKY_PM_TO_ACK_MSG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_PCIE_MSG_STICKY_PM_TO_ACK_MSG_STICKY  VTSS_BIT(2)
#define  VTSS_X_CPU_PCIE_MSG_STICKY_PM_TO_ACK_MSG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Sticky indicates that Controller received a PME_Turnoff MSG.Note: This
 * is only valid in End point mode of operation.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_MSG_STICKY . PM_TURNOFF_MSG_STICKY
 */
#define  VTSS_F_CPU_PCIE_MSG_STICKY_PM_TURNOFF_MSG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_PCIE_MSG_STICKY_PM_TURNOFF_MSG_STICKY  VTSS_BIT(1)
#define  VTSS_X_CPU_PCIE_MSG_STICKY_PM_TURNOFF_MSG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Sticky indicates that Controller received a vendor-defined message.
 * Message information is present in MSG_PAYLOAD.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_MSG_STICKY . VENDOR_MSG_STICKY
 */
#define  VTSS_F_CPU_PCIE_MSG_STICKY_VENDOR_MSG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PCIE_MSG_STICKY_VENDOR_MSG_STICKY  VTSS_BIT(0)
#define  VTSS_X_CPU_PCIE_MSG_STICKY_VENDOR_MSG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief MSG Payload(LSB 32 bits) of the received Vendor Message by Controller.
 *
 * \details
 * Register: \a CPU:PCIE:PCIE_MSG_PAYLOAD_LOW
 */
#define VTSS_CPU_PCIE_MSG_PAYLOAD_LOW        VTSS_IOREG(VTSS_TO_CPU,0x58)

/** 
 * \brief
 * This registers captures the LSB 32 bits of Vendor MSG PAYLOAD received
 * and provided by Controller signal 'radm_msg_payload[31:0]'. Description
 * of the signal can be found in PCIE DM Controller Databook.Note: PCIe
 * Controller outputs payload information for other messages like error, pm
 * etc but since the payload is reserved for them, our interest would only
 * be in Vendor messages.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_MSG_PAYLOAD_LOW . VDM_MSG_PAYLOAD_LOW
 */
#define  VTSS_F_CPU_PCIE_MSG_PAYLOAD_LOW_VDM_MSG_PAYLOAD_LOW(x)  (x)
#define  VTSS_M_CPU_PCIE_MSG_PAYLOAD_LOW_VDM_MSG_PAYLOAD_LOW     0xffffffff
#define  VTSS_X_CPU_PCIE_MSG_PAYLOAD_LOW_VDM_MSG_PAYLOAD_LOW(x)  (x)


/** 
 * \brief MSG Payload(MSB 32 bits) of the received Vendor Message by Controller.
 *
 * \details
 * Register: \a CPU:PCIE:PCIE_MSG_PAYLOAD_HIGH
 */
#define VTSS_CPU_PCIE_MSG_PAYLOAD_HIGH       VTSS_IOREG(VTSS_TO_CPU,0x59)

/** 
 * \brief
 * This registers captures the MSB 32 bits of MSG PAYLOAD received and
 * provided by Controller signal 'radm_msg_payload[63:32]'. Description of
 * the signal can be found in PCIE DM Controller Databook.Note: PCIe
 * Controller outputs payload information for other messages like error, pm
 * etc but since the payload is reserved for them, our interest would only
 * be in Vendor messages
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_MSG_PAYLOAD_HIGH . VDM_MSG_PAYLOAD_HIGH
 */
#define  VTSS_F_CPU_PCIE_MSG_PAYLOAD_HIGH_VDM_MSG_PAYLOAD_HIGH(x)  (x)
#define  VTSS_M_CPU_PCIE_MSG_PAYLOAD_HIGH_VDM_MSG_PAYLOAD_HIGH     0xffffffff
#define  VTSS_X_CPU_PCIE_MSG_PAYLOAD_HIGH_VDM_MSG_PAYLOAD_HIGH(x)  (x)


/** 
 * \brief Contains Req. id of the received Message as provided by Controller.
 *
 * \details
 * Register: \a CPU:PCIE:PCIE_MSG_HDR_INFO_0
 */
#define VTSS_CPU_PCIE_MSG_HDR_INFO_0         VTSS_IOREG(VTSS_TO_CPU,0x5a)

/** 
 * \brief
 * Contains the Requester ID(BDF) of the last received CORR Error Message
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_MSG_HDR_INFO_0 . CORR_MSG_REQ_ID
 */
#define  VTSS_F_CPU_PCIE_MSG_HDR_INFO_0_CORR_MSG_REQ_ID(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_CPU_PCIE_MSG_HDR_INFO_0_CORR_MSG_REQ_ID     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_CPU_PCIE_MSG_HDR_INFO_0_CORR_MSG_REQ_ID(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Contains the Requester ID(BDF) of the last received Non-FATAL Error
 * Message
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_MSG_HDR_INFO_0 . NF_MSG_REQ_ID
 */
#define  VTSS_F_CPU_PCIE_MSG_HDR_INFO_0_NF_MSG_REQ_ID(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_CPU_PCIE_MSG_HDR_INFO_0_NF_MSG_REQ_ID     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_CPU_PCIE_MSG_HDR_INFO_0_NF_MSG_REQ_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Contains Req. id of the received Message as provided by Controller.
 *
 * \details
 * Register: \a CPU:PCIE:PCIE_MSG_HDR_INFO_1
 */
#define VTSS_CPU_PCIE_MSG_HDR_INFO_1         VTSS_IOREG(VTSS_TO_CPU,0x5b)

/** 
 * \brief
 * Contains the Requester ID(BDF) of the last received FATAL Error Message
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_MSG_HDR_INFO_1 . F_MSG_REQ_ID
 */
#define  VTSS_F_CPU_PCIE_MSG_HDR_INFO_1_F_MSG_REQ_ID(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_CPU_PCIE_MSG_HDR_INFO_1_F_MSG_REQ_ID     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_CPU_PCIE_MSG_HDR_INFO_1_F_MSG_REQ_ID(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Contains the Requester ID(BDF) of the last received	PM PME Message
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_MSG_HDR_INFO_1 . PME_MSG_REQ_ID
 */
#define  VTSS_F_CPU_PCIE_MSG_HDR_INFO_1_PME_MSG_REQ_ID(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_CPU_PCIE_MSG_HDR_INFO_1_PME_MSG_REQ_ID     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_CPU_PCIE_MSG_HDR_INFO_1_PME_MSG_REQ_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Contains Req. id of the received Message as provided by Controller.
 *
 * \details
 * Register: \a CPU:PCIE:PCIE_MSG_HDR_INFO_2
 */
#define VTSS_CPU_PCIE_MSG_HDR_INFO_2         VTSS_IOREG(VTSS_TO_CPU,0x5c)

/** 
 * \brief
 * Contains the Requester ID(BDF) of the last received	PME_TO_ACK Message
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_MSG_HDR_INFO_2 . ACK_MSG_REQ_ID
 */
#define  VTSS_F_CPU_PCIE_MSG_HDR_INFO_2_ACK_MSG_REQ_ID(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_CPU_PCIE_MSG_HDR_INFO_2_ACK_MSG_REQ_ID     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_CPU_PCIE_MSG_HDR_INFO_2_ACK_MSG_REQ_ID(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Contains the Requester ID(BDF) of the last received	PME_TURNOFF Message
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_MSG_HDR_INFO_2 . TURNOFF_MSG_REQ_ID
 */
#define  VTSS_F_CPU_PCIE_MSG_HDR_INFO_2_TURNOFF_MSG_REQ_ID(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_CPU_PCIE_MSG_HDR_INFO_2_TURNOFF_MSG_REQ_ID     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_CPU_PCIE_MSG_HDR_INFO_2_TURNOFF_MSG_REQ_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Contains Req. id of the received Message as provided by Controller.
 *
 * \details
 * Register: \a CPU:PCIE:PCIE_MSG_HDR_INFO_3
 */
#define VTSS_CPU_PCIE_MSG_HDR_INFO_3         VTSS_IOREG(VTSS_TO_CPU,0x5d)

/** 
 * \brief
 * Contains the Requester ID(BDF) of the last received	UNLOCK Message
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_MSG_HDR_INFO_3 . UNLOCK_MSG_REQ_ID
 */
#define  VTSS_F_CPU_PCIE_MSG_HDR_INFO_3_UNLOCK_MSG_REQ_ID(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_CPU_PCIE_MSG_HDR_INFO_3_UNLOCK_MSG_REQ_ID     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_CPU_PCIE_MSG_HDR_INFO_3_UNLOCK_MSG_REQ_ID(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Contains the Requester ID(BDF) of the last received	Vendor Defined
 * Message(VDM).
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_MSG_HDR_INFO_3 . VDM_MSG_REQ_ID
 */
#define  VTSS_F_CPU_PCIE_MSG_HDR_INFO_3_VDM_MSG_REQ_ID(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_CPU_PCIE_MSG_HDR_INFO_3_VDM_MSG_REQ_ID     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_CPU_PCIE_MSG_HDR_INFO_3_VDM_MSG_REQ_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCIe events
 *
 * \details
 * Register: \a CPU:PCIE:PCIE_INTR
 */
#define VTSS_CPU_PCIE_INTR                   VTSS_IOREG(VTSS_TO_CPU,0x5e)

/** 
 * \brief
 * This event is set when controller detects a system error either due to
 * ERR_COR, ERR_FATAL, ERR_NONFATAL reported by a device in the hierarchy
 * or if any internal error is detected.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR . INTR_SYS_ERR_RC
 */
#define  VTSS_F_CPU_PCIE_INTR_INTR_SYS_ERR_RC(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_CPU_PCIE_INTR_INTR_SYS_ERR_RC  VTSS_BIT(9)
#define  VTSS_X_CPU_PCIE_INTR_INTR_SYS_ERR_RC(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * This event is set whenever a link down on PCIE is about to occur. This
 * is an early version of hot reset received by controller sampled on
 * falling edge.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR . INTR_EARLY_LINK_DOWN
 */
#define  VTSS_F_CPU_PCIE_INTR_INTR_EARLY_LINK_DOWN(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_CPU_PCIE_INTR_INTR_EARLY_LINK_DOWN  VTSS_BIT(8)
#define  VTSS_X_CPU_PCIE_INTR_INTR_EARLY_LINK_DOWN(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * This event is set whenever the CPU::PCIE_STAT.LTSSM_STATE field is
 * changed.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR . INTR_LTSSM_STATE
 */
#define  VTSS_F_CPU_PCIE_INTR_INTR_LTSSM_STATE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_CPU_PCIE_INTR_INTR_LTSSM_STATE  VTSS_BIT(7)
#define  VTSS_X_CPU_PCIE_INTR_INTR_LTSSM_STATE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * This event is set whenever the CPU::PCIE_STAT.LINK_STATE field is
 * changed.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR . INTR_LINK_STATE
 */
#define  VTSS_F_CPU_PCIE_INTR_INTR_LINK_STATE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_CPU_PCIE_INTR_INTR_LINK_STATE  VTSS_BIT(6)
#define  VTSS_X_CPU_PCIE_INTR_INTR_LINK_STATE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * This event is set whenever the CPU::PCIE_STAT.PM_STATE field is
 * changed.Bit 0 pertains to Func0(SwC function)Bit 1 pertains to Func1(PoE
 * function)
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR . INTR_PM_STATE
 */
#define  VTSS_F_CPU_PCIE_INTR_INTR_PM_STATE(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_CPU_PCIE_INTR_INTR_PM_STATE     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_CPU_PCIE_INTR_INTR_PM_STATE(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * This event is set when a notification 'cfg_link_auto_bw_int' is asserted
 * by controller indicating that Link Autonomous Bandwidth Status register
 * (Link Status register bit 15) is updated and the Link Autonomous
 * Bandwidth Interrupt Enable (Link Control register bit 11) is set.Note:
 * This interrupt is only valid in Root Complex mode of operation of
 * controller.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR . INTR_LINK_AUTO_BW_STATUS
 */
#define  VTSS_F_CPU_PCIE_INTR_INTR_LINK_AUTO_BW_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_PCIE_INTR_INTR_LINK_AUTO_BW_STATUS  VTSS_BIT(3)
#define  VTSS_X_CPU_PCIE_INTR_INTR_LINK_AUTO_BW_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * This event is set when a notification 'cfg_bw_mgt_int' is asserted by
 * controller to indicate the Link Bandwidth Management Status register
 * (Link Status register bit 14) is updated and the Link Bandwidth
 * Management Interrupt Enable (Link Control register bit 10) is set.Note:
 * This interrupt is only valid in Root Complex mode of operation of
 * controller.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR . INTR_LINK_BW_MGT_STATUS
 */
#define  VTSS_F_CPU_PCIE_INTR_INTR_LINK_BW_MGT_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_PCIE_INTR_INTR_LINK_BW_MGT_STATUS  VTSS_BIT(2)
#define  VTSS_X_CPU_PCIE_INTR_INTR_LINK_BW_MGT_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * This event is set when MSI or MSI-X is enabled and a reported error
 * condition causes a bit to be set in the Root Error Status register and
 * the associated error message reporting enable bit is set in the Root
 * Error Command register.Note: This information is valid only in Root
 * Complex mode of operation of controller and MSI(-X) is enabled. 
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR . INTR_AER_RC_ERR_MSI
 */
#define  VTSS_F_CPU_PCIE_INTR_INTR_AER_RC_ERR_MSI(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_PCIE_INTR_INTR_AER_RC_ERR_MSI  VTSS_BIT(1)
#define  VTSS_X_CPU_PCIE_INTR_INTR_AER_RC_ERR_MSI(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * This event is set when MSI or MSI-X is enabled and when the PME
 * Interrupt Enable bit in the Root Control register is set to 1 and the
 * PME Status bit in the Root Status register is set to 1.Note: This
 * information is valid only in Root Complex mode of operation of
 * controller and MSI(-X) is enabled. 
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR . INTR_PME_MSI
 */
#define  VTSS_F_CPU_PCIE_INTR_INTR_PME_MSI(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PCIE_INTR_INTR_PME_MSI    VTSS_BIT(0)
#define  VTSS_X_CPU_PCIE_INTR_INTR_PME_MSI(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCIe interrupt enable
 *
 * \details
 * Register: \a CPU:PCIE:PCIE_INTR_ENA
 */
#define VTSS_CPU_PCIE_INTR_ENA               VTSS_IOREG(VTSS_TO_CPU,0x5f)

/** 
 * \brief
 * Enable propagation of SYS ERR interrupt
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_ENA . INTR_SYS_ERR_ENA
 */
#define  VTSS_F_CPU_PCIE_INTR_ENA_INTR_SYS_ERR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_CPU_PCIE_INTR_ENA_INTR_SYS_ERR_ENA  VTSS_BIT(10)
#define  VTSS_X_CPU_PCIE_INTR_ENA_INTR_SYS_ERR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Set to enable propagation of EARLY_LINK_DOWN interrupt
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_ENA . INTR_EARLY_LINK_DOWN_ENA
 */
#define  VTSS_F_CPU_PCIE_INTR_ENA_INTR_EARLY_LINK_DOWN_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_CPU_PCIE_INTR_ENA_INTR_EARLY_LINK_DOWN_ENA  VTSS_BIT(9)
#define  VTSS_X_CPU_PCIE_INTR_ENA_INTR_EARLY_LINK_DOWN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Set to enable propagation of the LTSSM_STATE interrupt.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_ENA . INTR_LTSSM_STATE_ENA
 */
#define  VTSS_F_CPU_PCIE_INTR_ENA_INTR_LTSSM_STATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_CPU_PCIE_INTR_ENA_INTR_LTSSM_STATE_ENA  VTSS_BIT(8)
#define  VTSS_X_CPU_PCIE_INTR_ENA_INTR_LTSSM_STATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Set to enable propagation of the LINK_STATE interrupt.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_ENA . INTR_LINK_STATE_ENA
 */
#define  VTSS_F_CPU_PCIE_INTR_ENA_INTR_LINK_STATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_CPU_PCIE_INTR_ENA_INTR_LINK_STATE_ENA  VTSS_BIT(7)
#define  VTSS_X_CPU_PCIE_INTR_ENA_INTR_LINK_STATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Set to enable propagation of the PM_STATE interrupt.Bit 0 pertains to
 * Func0(SwC function)Bit 1 pertains to Func1(PoE function)
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_ENA . INTR_PM_STATE_ENA
 */
#define  VTSS_F_CPU_PCIE_INTR_ENA_INTR_PM_STATE_ENA(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_CPU_PCIE_INTR_ENA_INTR_PM_STATE_ENA     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_CPU_PCIE_INTR_ENA_INTR_PM_STATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/** 
 * \brief
 * When set will propagate the 'cfg_link_auto_bw_int' interrupt from
 * controller to GIC-500Note: This interrupt is only valid in Root Complex
 * mode of operation of controller.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_ENA . INTR_LINK_AUTO_BW_ENA
 */
#define  VTSS_F_CPU_PCIE_INTR_ENA_INTR_LINK_AUTO_BW_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CPU_PCIE_INTR_ENA_INTR_LINK_AUTO_BW_ENA  VTSS_BIT(4)
#define  VTSS_X_CPU_PCIE_INTR_ENA_INTR_LINK_AUTO_BW_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * When set will propagate the 'cfg_bw_mgt_int' interrupt from controller
 * to GIC-500Note: This interrupt is only valid in Root Complex mode of
 * operation of controller.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_ENA . INTR_LINK_BW_MGT_ENA
 */
#define  VTSS_F_CPU_PCIE_INTR_ENA_INTR_LINK_BW_MGT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_PCIE_INTR_ENA_INTR_LINK_BW_MGT_ENA  VTSS_BIT(3)
#define  VTSS_X_CPU_PCIE_INTR_ENA_INTR_LINK_BW_MGT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * When set will propagate the 'cfg_link_eq_req_int' interrupt from
 * controller to GIC-500. Interrupt indicates that the Link Equalization
 * Request bit in the Link Status 2 Register has been set and the Link
 * Equalization Request Interrupt Enable (Link Control 3 Register bit 1) is
 * set.Note: This interrupt is only valid in Root Complex mode of operation
 * of controller. Also, the interrupt is already the level signal from
 * controller so there is no sticky bit allocated.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_ENA . INTR_LINK_EQ_REQ_ENA
 */
#define  VTSS_F_CPU_PCIE_INTR_ENA_INTR_LINK_EQ_REQ_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_PCIE_INTR_ENA_INTR_LINK_EQ_REQ_ENA  VTSS_BIT(2)
#define  VTSS_X_CPU_PCIE_INTR_ENA_INTR_LINK_EQ_REQ_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * When set will propagate 'cfg_aer_rc_err_int' or 'cfg_aer_rc_err_msi'
 * interrupts from controller to GIC-500. This interrupts are asserted by
 * controller when a reported error condition causes a bit to be set in the
 * Root Error Status register and the associated error message reporting
 * enable bit is set in the Root Error Command register.Note: This
 * interrupt is only valid in Root Complex mode of operation of controller.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_ENA . INTR_AER_RC_ERR_ENA
 */
#define  VTSS_F_CPU_PCIE_INTR_ENA_INTR_AER_RC_ERR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_PCIE_INTR_ENA_INTR_AER_RC_ERR_ENA  VTSS_BIT(1)
#define  VTSS_X_CPU_PCIE_INTR_ENA_INTR_AER_RC_ERR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * When set will propagate 'cfg_pme_int' or 'cfg_pme_msi' interrupts from
 * controller to GIC-500. This interrupt is asserted by controller when the
 * PME Interrupt Enable bit in the Root Control register is set to 1 and
 * the PME Status bit in the Root Status register is set to 1.Note: This
 * interrupt is only valid in Root Complex mode of operation of controller.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_ENA . INTR_PME_ENA
 */
#define  VTSS_F_CPU_PCIE_INTR_ENA_INTR_PME_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PCIE_INTR_ENA_INTR_PME_ENA  VTSS_BIT(0)
#define  VTSS_X_CPU_PCIE_INTR_ENA_INTR_PME_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Currently active PCIe interrupts
 *
 * \details
 * Register: \a CPU:PCIE:PCIE_INTR_IDENT
 */
#define VTSS_CPU_PCIE_INTR_IDENT             VTSS_IOREG(VTSS_TO_CPU,0x60)

/** 
 * \brief
 * Set if SYS ERR interrupt is currently active.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_IDENT . INTR_SYS_ERR_IDENT
 */
#define  VTSS_F_CPU_PCIE_INTR_IDENT_INTR_SYS_ERR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_CPU_PCIE_INTR_IDENT_INTR_SYS_ERR_IDENT  VTSS_BIT(20)
#define  VTSS_X_CPU_PCIE_INTR_IDENT_INTR_SYS_ERR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Set if the EARLY LINK DOWN interrupt is currently active.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_IDENT . INTR_EARLY_LINK_DOWN_IDENT
 */
#define  VTSS_F_CPU_PCIE_INTR_IDENT_INTR_EARLY_LINK_DOWN_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_CPU_PCIE_INTR_IDENT_INTR_EARLY_LINK_DOWN_IDENT  VTSS_BIT(19)
#define  VTSS_X_CPU_PCIE_INTR_IDENT_INTR_EARLY_LINK_DOWN_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * Set if the LTSSM_STATE interrupt is currently active.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_IDENT . INTR_LTSSM_STATE_IDENT
 */
#define  VTSS_F_CPU_PCIE_INTR_IDENT_INTR_LTSSM_STATE_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_CPU_PCIE_INTR_IDENT_INTR_LTSSM_STATE_IDENT  VTSS_BIT(18)
#define  VTSS_X_CPU_PCIE_INTR_IDENT_INTR_LTSSM_STATE_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Set if the LINK_STATE interrupt is currently active.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_IDENT . INTR_LINK_STATE_IDENT
 */
#define  VTSS_F_CPU_PCIE_INTR_IDENT_INTR_LINK_STATE_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_CPU_PCIE_INTR_IDENT_INTR_LINK_STATE_IDENT  VTSS_BIT(17)
#define  VTSS_X_CPU_PCIE_INTR_IDENT_INTR_LINK_STATE_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Set if the PM_STATE interrupt is currently active.Bit 0 pertains to
 * Func0(SwC function)Bit 1 pertains to Func1(PoE function)
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_IDENT . INTR_PM_STATE_IDENT
 */
#define  VTSS_F_CPU_PCIE_INTR_IDENT_INTR_PM_STATE_IDENT(x)  VTSS_ENCODE_BITFIELD(x,15,2)
#define  VTSS_M_CPU_PCIE_INTR_IDENT_INTR_PM_STATE_IDENT     VTSS_ENCODE_BITMASK(15,2)
#define  VTSS_X_CPU_PCIE_INTR_IDENT_INTR_PM_STATE_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,15,2)

/** 
 * \brief
 * Set if LINK_AUTO_BW interrupt is currently active.Note: This interrupt
 * is only valid in Root Complex mode of operation of controller.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_IDENT . INTR_LINK_AUTO_BW_IDENT
 */
#define  VTSS_F_CPU_PCIE_INTR_IDENT_INTR_LINK_AUTO_BW_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_CPU_PCIE_INTR_IDENT_INTR_LINK_AUTO_BW_IDENT  VTSS_BIT(14)
#define  VTSS_X_CPU_PCIE_INTR_IDENT_INTR_LINK_AUTO_BW_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Set if LINK_BW_MGT interrupt is currently active.Note: This interrupt is
 * only valid in Root Complex mode of operation of controller.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_IDENT . INTR_LINK_BW_MGT_IDENT
 */
#define  VTSS_F_CPU_PCIE_INTR_IDENT_INTR_LINK_BW_MGT_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_CPU_PCIE_INTR_IDENT_INTR_LINK_BW_MGT_IDENT  VTSS_BIT(13)
#define  VTSS_X_CPU_PCIE_INTR_IDENT_INTR_LINK_BW_MGT_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Set if LINK_EQ_REQ interrupt is currently active.Note: This interrupt is
 * only valid in Root Complex mode of operation of controller.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_IDENT . INTR_LINK_EQ_REQ_IDENT
 */
#define  VTSS_F_CPU_PCIE_INTR_IDENT_INTR_LINK_EQ_REQ_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_CPU_PCIE_INTR_IDENT_INTR_LINK_EQ_REQ_IDENT  VTSS_BIT(12)
#define  VTSS_X_CPU_PCIE_INTR_IDENT_INTR_LINK_EQ_REQ_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Set if AER_RC_ERR interrupt is active due to either 'cfg_aer_err_int' or
 * 'cfg_aer_err_msi' assertion.Note: This interrupt is only valid in Root
 * Complex mode of operation of controller.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_IDENT . INTR_AER_RC_ERR_IDENT
 */
#define  VTSS_F_CPU_PCIE_INTR_IDENT_INTR_AER_RC_ERR_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_CPU_PCIE_INTR_IDENT_INTR_AER_RC_ERR_IDENT  VTSS_BIT(11)
#define  VTSS_X_CPU_PCIE_INTR_IDENT_INTR_AER_RC_ERR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * The value in this field is only valid if 'cfg_aer_rc_err_msi' is cause
 * of assertion of AER_RC_ERR interrupt which happens when MSI(-X) is
 * enabled. This field indicates bits [31:27] of the Root Error Status
 * register.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_IDENT . INTR_AER_MSG_NUM
 */
#define  VTSS_F_CPU_PCIE_INTR_IDENT_INTR_AER_MSG_NUM(x)  VTSS_ENCODE_BITFIELD(x,6,5)
#define  VTSS_M_CPU_PCIE_INTR_IDENT_INTR_AER_MSG_NUM     VTSS_ENCODE_BITMASK(6,5)
#define  VTSS_X_CPU_PCIE_INTR_IDENT_INTR_AER_MSG_NUM(x)  VTSS_EXTRACT_BITFIELD(x,6,5)

/** 
 * \brief
 * Set if PME interrupt is active due to either 'cfg_pme_int' or
 * 'cfg_pme_msi' assertionNote: This interrupt is only valid in Root
 * Complex mode of operation of controller.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_IDENT . INTR_PME_IDENT
 */
#define  VTSS_F_CPU_PCIE_INTR_IDENT_INTR_PME_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_CPU_PCIE_INTR_IDENT_INTR_PME_IDENT  VTSS_BIT(5)
#define  VTSS_X_CPU_PCIE_INTR_IDENT_INTR_PME_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * The value in this field is only valid if 'cfg_pme_msi' is cause of
 * assertion of PME interrupt which happens when MSI(-X) is enabled. This
 * field indicates bits [13:9] of the PCI Express Capabilities register
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_IDENT . INTR_PCIE_CAP_MSG_NUM
 */
#define  VTSS_F_CPU_PCIE_INTR_IDENT_INTR_PCIE_CAP_MSG_NUM(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_CPU_PCIE_INTR_IDENT_INTR_PCIE_CAP_MSG_NUM     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_CPU_PCIE_INTR_IDENT_INTR_PCIE_CAP_MSG_NUM(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief PCIE MSIX DOOR BELL Address to be used while generating MSIX requests towards PCIE DM Controller
 *
 * \details
 * Register: \a CPU:PCIE:PCIE_MSIX_DBELL_LOW
 */
#define VTSS_CPU_PCIE_MSIX_DBELL_LOW         VTSS_IOREG(VTSS_TO_CPU,0x61)

/** 
 * \brief
 * This register value along with MSIX_DBELL_ADDR_HIGH is used in end point
 * mode of PCIe DM Controller to generate the AXI WR requests with this
 * special address which are detected inside PCIe DM Controller as an MSIX
 * request and correspoding Mem Wr TLP will be generated. Value programmed
 * in this register also needs to be programmed in the Controller
 * MSIX_ADDRESS_MATCH_LOW_OFF register for controller to detect the MSIX
 * requests.Note: This is a special reserved address and shouldn't be used
 * by any other master generating any kind of requests towards AXI PCIe
 * Slave for other purposes.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_MSIX_DBELL_LOW . MSIX_DBELL_ADDR_LOW
 */
#define  VTSS_F_CPU_PCIE_MSIX_DBELL_LOW_MSIX_DBELL_ADDR_LOW(x)  (x)
#define  VTSS_M_CPU_PCIE_MSIX_DBELL_LOW_MSIX_DBELL_ADDR_LOW     0xffffffff
#define  VTSS_X_CPU_PCIE_MSIX_DBELL_LOW_MSIX_DBELL_ADDR_LOW(x)  (x)


/** 
 * \brief PCIE MSIX DOOR BELL MSB Address to be used while generating MSIX requests towards PCIE DM Controller
 *
 * \details
 * Register: \a CPU:PCIE:PCIE_MSIX_DBELL_HIGH
 */
#define VTSS_CPU_PCIE_MSIX_DBELL_HIGH        VTSS_IOREG(VTSS_TO_CPU,0x62)

/** 
 * \brief
 * See PCIE_MSIX_DBELL_LOW.MSIX_DBELL_ADDR_LOW register for description.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_MSIX_DBELL_HIGH . MSIX_DBELL_ADDR_HIGH
 */
#define  VTSS_F_CPU_PCIE_MSIX_DBELL_HIGH_MSIX_DBELL_ADDR_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CPU_PCIE_MSIX_DBELL_HIGH_MSIX_DBELL_ADDR_HIGH     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CPU_PCIE_MSIX_DBELL_HIGH_MSIX_DBELL_ADDR_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief PCIe outbound interrupt configuration
 *
 * \details
 * Replicated per function. FireAnt supports two functions.
 *
 * Register: \a CPU:PCIE:PCIE_INTR_COMMON_CFG
 *
 * @param ri Register: PCIE_INTR_COMMON_CFG (??), 0-1
 */
#define VTSS_CPU_PCIE_INTR_COMMON_CFG(ri)    VTSS_IOREG(VTSS_TO_CPU,0x63 + (ri))

/** 
 * \brief
 * Set to disable wake-up on interrupt. By default the PCIe endpoint will
 * attempt to wake up from powerdown when a change in interrupt state is
 * detected.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_COMMON_CFG . WAKEUP_ON_INTR_DIS
 */
#define  VTSS_F_CPU_PCIE_INTR_COMMON_CFG_WAKEUP_ON_INTR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_PCIE_INTR_COMMON_CFG_WAKEUP_ON_INTR_DIS  VTSS_BIT(3)
#define  VTSS_X_CPU_PCIE_INTR_COMMON_CFG_WAKEUP_ON_INTR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Select the external interrupt from the VCore interrupt controller that
 * must be used to generate PCIe legacy interrupt.
 *
 * \details 
 * 0: Use EXT_DST0
 * 1: Use EXT_DST1
 *
 * Field: ::VTSS_CPU_PCIE_INTR_COMMON_CFG . LEGACY_MODE_INTR_SEL
 */
#define  VTSS_F_CPU_PCIE_INTR_COMMON_CFG_LEGACY_MODE_INTR_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_PCIE_INTR_COMMON_CFG_LEGACY_MODE_INTR_SEL  VTSS_BIT(2)
#define  VTSS_X_CPU_PCIE_INTR_COMMON_CFG_LEGACY_MODE_INTR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set to enable PCIe interrupts. The PCIe DM Controller(EP Mode) MSI or
 * MSI-X Capability Register Set must have been configured before enabling
 * interrupts.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_COMMON_CFG . PCIE_INTR_ENA
 */
#define  VTSS_F_CPU_PCIE_INTR_COMMON_CFG_PCIE_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_PCIE_INTR_COMMON_CFG_PCIE_INTR_ENA  VTSS_BIT(1)
#define  VTSS_X_CPU_PCIE_INTR_COMMON_CFG_PCIE_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enables MSI-X mode of interrupt generation. This field is only used by
 * the interrupt control block surrounding the controller. Actual enabling
 * of MSI-X mode of operation should be done in controller
 * configuration(within MSIX capability registers in Configuration space)
 * also for this to have an effect.Also, PCIE_INTR_ENA should be enabled
 * for this to have an effect.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_COMMON_CFG . MSIX_INTR_ENA
 */
#define  VTSS_F_CPU_PCIE_INTR_COMMON_CFG_MSIX_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PCIE_INTR_COMMON_CFG_MSIX_INTR_ENA  VTSS_BIT(0)
#define  VTSS_X_CPU_PCIE_INTR_COMMON_CFG_MSIX_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCIe outbound MSI interrupt configuration
 *
 * \details
 * Replicated per EXT_DST interrupt.
 *
 * Register: \a CPU:PCIE:PCIE_INTR_CFG
 *
 * @param ri Register: PCIE_INTR_CFG (??), 0-1
 */
#define VTSS_CPU_PCIE_INTR_CFG(ri)           VTSS_IOREG(VTSS_TO_CPU,0x65 + (ri))

/** 
 * \brief
 * We support two functions, SwC func(Func0), PoE func(Func1). Values to be
 * programmed here are 0 or 1.Note: This information is only used with MSI
 * or MSI-X Interrupt requests
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_CFG . FUNCTION_NUMBER
 */
#define  VTSS_F_CPU_PCIE_INTR_CFG_FUNCTION_NUMBER(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_CPU_PCIE_INTR_CFG_FUNCTION_NUMBER     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_CPU_PCIE_INTR_CFG_FUNCTION_NUMBER(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Configure MSI or MSI-X interrupt traffic class for corresponding EXT_DST
 * interrupt.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_CFG . TRAFFIC_CLASS
 */
#define  VTSS_F_CPU_PCIE_INTR_CFG_TRAFFIC_CLASS(x)  VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_CPU_PCIE_INTR_CFG_TRAFFIC_CLASS     VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_CPU_PCIE_INTR_CFG_TRAFFIC_CLASS(x)  VTSS_EXTRACT_BITFIELD(x,24,3)

/** 
 * \brief
 * Configure MSI or MSI-X interrupt vector for falling edge of
 * corresponding EXT_DST interrupt.Note: Only LSB 5 bits will be used when
 * configured to generate MSI interrupts as MSI supports a maximum vector
 * value of 31.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_CFG . FALLING_VECTOR_VAL
 */
#define  VTSS_F_CPU_PCIE_INTR_CFG_FALLING_VECTOR_VAL(x)  VTSS_ENCODE_BITFIELD(x,13,11)
#define  VTSS_M_CPU_PCIE_INTR_CFG_FALLING_VECTOR_VAL     VTSS_ENCODE_BITMASK(13,11)
#define  VTSS_X_CPU_PCIE_INTR_CFG_FALLING_VECTOR_VAL(x)  VTSS_EXTRACT_BITFIELD(x,13,11)

/** 
 * \brief
 * Configure MSI or MSI-X interrupt vector for rising edge of corresponding
 * EXT_DST interrupt.Note: Only LSB 5 bits will be used when configured to
 * generate MSI interrupts as MSI supports a maximum vector value of 31.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_CFG . RISING_VECTOR_VAL
 */
#define  VTSS_F_CPU_PCIE_INTR_CFG_RISING_VECTOR_VAL(x)  VTSS_ENCODE_BITFIELD(x,2,11)
#define  VTSS_M_CPU_PCIE_INTR_CFG_RISING_VECTOR_VAL     VTSS_ENCODE_BITMASK(2,11)
#define  VTSS_X_CPU_PCIE_INTR_CFG_RISING_VECTOR_VAL(x)  VTSS_EXTRACT_BITFIELD(x,2,11)

/** 
 * \brief
 * Set to enable MSI or MSI-X interrupt on falling edge of corresponding
 * EXT_DST interrupt.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_CFG . INTR_FALLING_ENA
 */
#define  VTSS_F_CPU_PCIE_INTR_CFG_INTR_FALLING_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_PCIE_INTR_CFG_INTR_FALLING_ENA  VTSS_BIT(1)
#define  VTSS_X_CPU_PCIE_INTR_CFG_INTR_FALLING_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set to enable MSI or MSI-X interrupt on rising edge of corresponding
 * EXT_DST interrupt.
 *
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_CFG . INTR_RISING_ENA
 */
#define  VTSS_F_CPU_PCIE_INTR_CFG_INTR_RISING_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PCIE_INTR_CFG_INTR_RISING_ENA  VTSS_BIT(0)
#define  VTSS_X_CPU_PCIE_INTR_CFG_INTR_RISING_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PCIe outbound MSI interrupt status
 *
 * \details
 * Replicated per EXT_DST interrupt.
 *
 * Register: \a CPU:PCIE:PCIE_INTR_STAT
 *
 * @param ri Register: PCIE_INTR_STAT (??), 0-1
 */
#define VTSS_CPU_PCIE_INTR_STAT(ri)          VTSS_IOREG(VTSS_TO_CPU,0x67 + (ri))

/** 
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_STAT . INTR_PENDING_FALLING
 */
#define  VTSS_F_CPU_PCIE_INTR_STAT_INTR_PENDING_FALLING(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_PCIE_INTR_STAT_INTR_PENDING_FALLING  VTSS_BIT(1)
#define  VTSS_X_CPU_PCIE_INTR_STAT_INTR_PENDING_FALLING(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \details 
 * Field: ::VTSS_CPU_PCIE_INTR_STAT . INTR_PENDING_RISING
 */
#define  VTSS_F_CPU_PCIE_INTR_STAT_INTR_PENDING_RISING(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_PCIE_INTR_STAT_INTR_PENDING_RISING  VTSS_BIT(0)
#define  VTSS_X_CPU_PCIE_INTR_STAT_INTR_PENDING_RISING(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

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
#define VTSS_CPU_INTR_RAW                    VTSS_IOREG(VTSS_TO_CPU,0x69)

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
#define VTSS_CPU_INTR_RAW1                   VTSS_IOREG(VTSS_TO_CPU,0x6a)

/** 
 * \brief
 * Bit 32-49 of field INTR_RAW.
 *
 * \details 
 * Field: ::VTSS_CPU_INTR_RAW1 . INTR_RAW1
 */
#define  VTSS_F_CPU_INTR_RAW1_INTR_RAW1(x)    VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_CPU_INTR_RAW1_INTR_RAW1       VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_CPU_INTR_RAW1_INTR_RAW1(x)    VTSS_EXTRACT_BITFIELD(x,0,18)


/** 
 * \brief Interrupt trigger mode
 *
 * \details
 * Register: \a CPU:INTR:INTR_TRIGGER
 *
 * @param ri Register: INTR_TRIGGER (??), 0-1
 */
#define VTSS_CPU_INTR_TRIGGER(ri)            VTSS_IOREG(VTSS_TO_CPU,0x6b + (ri))

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
#define VTSS_CPU_INTR_TRIGGER1(ri)           VTSS_IOREG(VTSS_TO_CPU,0x6d + (ri))

/** 
 * \brief
 * Bit 32-49 of field INTR_TRIGGER.
 *
 * \details 
 * 0: Interrupt is level-activated
 * 1: Interrupt is edge-triggered
 * 2: Interrupt is falling-edge-triggered
 * 3: Interrupt is rising-edge-triggered
 *
 * Field: ::VTSS_CPU_INTR_TRIGGER1 . INTR_TRIGGER1
 */
#define  VTSS_F_CPU_INTR_TRIGGER1_INTR_TRIGGER1(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_CPU_INTR_TRIGGER1_INTR_TRIGGER1     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_CPU_INTR_TRIGGER1_INTR_TRIGGER1(x)  VTSS_EXTRACT_BITFIELD(x,0,18)


/** 
 * \brief Interrupt force sticky event
 *
 * \details
 * Register: \a CPU:INTR:INTR_FORCE
 */
#define VTSS_CPU_INTR_FORCE                  VTSS_IOREG(VTSS_TO_CPU,0x6f)

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
#define VTSS_CPU_INTR_FORCE1                 VTSS_IOREG(VTSS_TO_CPU,0x70)

/** 
 * \brief
 * Bit 32-49 of field INTR_FORCE.
 *
 * \details 
 * Field: ::VTSS_CPU_INTR_FORCE1 . INTR_FORCE1
 */
#define  VTSS_F_CPU_INTR_FORCE1_INTR_FORCE1(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_CPU_INTR_FORCE1_INTR_FORCE1     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_CPU_INTR_FORCE1_INTR_FORCE1(x)  VTSS_EXTRACT_BITFIELD(x,0,18)


/** 
 * \brief Interrupt sticky status
 *
 * \details
 * Register: \a CPU:INTR:INTR_STICKY
 */
#define VTSS_CPU_INTR_STICKY                 VTSS_IOREG(VTSS_TO_CPU,0x71)

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
#define VTSS_CPU_INTR_STICKY1                VTSS_IOREG(VTSS_TO_CPU,0x72)

/** 
 * \brief
 * Bit 32-49 of field INTR_STICKY.
 *
 * \details 
 * Field: ::VTSS_CPU_INTR_STICKY1 . INTR_STICKY1
 */
#define  VTSS_F_CPU_INTR_STICKY1_INTR_STICKY1(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_CPU_INTR_STICKY1_INTR_STICKY1     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_CPU_INTR_STICKY1_INTR_STICKY1(x)  VTSS_EXTRACT_BITFIELD(x,0,18)


/** 
 * \brief Interrupt bypass enable
 *
 * \details
 * Register: \a CPU:INTR:INTR_BYPASS
 */
#define VTSS_CPU_INTR_BYPASS                 VTSS_IOREG(VTSS_TO_CPU,0x73)

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
#define VTSS_CPU_INTR_BYPASS1                VTSS_IOREG(VTSS_TO_CPU,0x74)

/** 
 * \brief
 * Bit 32-49 of field INTR_BYPASS.
 *
 * \details 
 * Field: ::VTSS_CPU_INTR_BYPASS1 . INTR_BYPASS1
 */
#define  VTSS_F_CPU_INTR_BYPASS1_INTR_BYPASS1(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_CPU_INTR_BYPASS1_INTR_BYPASS1     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_CPU_INTR_BYPASS1_INTR_BYPASS1(x)  VTSS_EXTRACT_BITFIELD(x,0,18)


/** 
 * \brief Interrupt enable
 *
 * \details
 * Register: \a CPU:INTR:INTR_ENA
 */
#define VTSS_CPU_INTR_ENA                    VTSS_IOREG(VTSS_TO_CPU,0x75)

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
#define VTSS_CPU_INTR_ENA1                   VTSS_IOREG(VTSS_TO_CPU,0x76)

/** 
 * \brief
 * Bit 32-49 of field INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_CPU_INTR_ENA1 . INTR_ENA1
 */
#define  VTSS_F_CPU_INTR_ENA1_INTR_ENA1(x)    VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_CPU_INTR_ENA1_INTR_ENA1       VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_CPU_INTR_ENA1_INTR_ENA1(x)    VTSS_EXTRACT_BITFIELD(x,0,18)


/** 
 * \brief Atomic clear of interrupt enable
 *
 * \details
 * Register: \a CPU:INTR:INTR_ENA_CLR
 */
#define VTSS_CPU_INTR_ENA_CLR                VTSS_IOREG(VTSS_TO_CPU,0x77)

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
#define VTSS_CPU_INTR_ENA_CLR1               VTSS_IOREG(VTSS_TO_CPU,0x78)

/** 
 * \brief
 * Bit 32-49 of field INTR_ENA_CLR.
 *
 * \details 
 * Field: ::VTSS_CPU_INTR_ENA_CLR1 . INTR_ENA_CLR1
 */
#define  VTSS_F_CPU_INTR_ENA_CLR1_INTR_ENA_CLR1(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_CPU_INTR_ENA_CLR1_INTR_ENA_CLR1     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_CPU_INTR_ENA_CLR1_INTR_ENA_CLR1(x)  VTSS_EXTRACT_BITFIELD(x,0,18)


/** 
 * \brief Atomic set of interrupt
 *
 * \details
 * Register: \a CPU:INTR:INTR_ENA_SET
 */
#define VTSS_CPU_INTR_ENA_SET                VTSS_IOREG(VTSS_TO_CPU,0x79)

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
#define VTSS_CPU_INTR_ENA_SET1               VTSS_IOREG(VTSS_TO_CPU,0x7a)

/** 
 * \brief
 * Bit 32-49 of field INTR_ENA_SET.
 *
 * \details 
 * Field: ::VTSS_CPU_INTR_ENA_SET1 . INTR_ENA_SET1
 */
#define  VTSS_F_CPU_INTR_ENA_SET1_INTR_ENA_SET1(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_CPU_INTR_ENA_SET1_INTR_ENA_SET1     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_CPU_INTR_ENA_SET1_INTR_ENA_SET1(x)  VTSS_EXTRACT_BITFIELD(x,0,18)


/** 
 * \brief Currently active interrupt sources
 *
 * \details
 * Register: \a CPU:INTR:INTR_IDENT
 */
#define VTSS_CPU_INTR_IDENT                  VTSS_IOREG(VTSS_TO_CPU,0x7b)

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
#define VTSS_CPU_INTR_IDENT1                 VTSS_IOREG(VTSS_TO_CPU,0x7c)

/** 
 * \brief
 * Bit 32-49 of field INTR_IDENT.
 *
 * \details 
 * Field: ::VTSS_CPU_INTR_IDENT1 . INTR_IDENT1
 */
#define  VTSS_F_CPU_INTR_IDENT1_INTR_IDENT1(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_CPU_INTR_IDENT1_INTR_IDENT1     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_CPU_INTR_IDENT1_INTR_IDENT1(x)  VTSS_EXTRACT_BITFIELD(x,0,18)


/** 
 * \brief Mapping of source to destination interrupts
 *
 * \details
 * Replicated per destination interrupt.
 *
 * Register: \a CPU:INTR:DST_INTR_MAP
 *
 * @param ri Replicator: x_VCORE_INTR_DST_CNT (??), 0-1
 */
#define VTSS_CPU_DST_INTR_MAP(ri)            VTSS_IOREG(VTSS_TO_CPU,0x7d + (ri))

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
 * @param ri Replicator: x_VCORE_INTR_DST_CNT (??), 0-1
 */
#define VTSS_CPU_DST_INTR_MAP1(ri)           VTSS_IOREG(VTSS_TO_CPU,0x7f + (ri))

/** 
 * \brief
 * Bit 32-49 of field DST_INTR_MAP.
 *
 * \details 
 * Field: ::VTSS_CPU_DST_INTR_MAP1 . DST_INTR_MAP1
 */
#define  VTSS_F_CPU_DST_INTR_MAP1_DST_INTR_MAP1(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_CPU_DST_INTR_MAP1_DST_INTR_MAP1     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_CPU_DST_INTR_MAP1_DST_INTR_MAP1(x)  VTSS_EXTRACT_BITFIELD(x,0,18)


/** 
 * \brief Currently active interrupt sources per destination
 *
 * \details
 * Replicated per destination interrupt.
 *
 * Register: \a CPU:INTR:DST_INTR_IDENT
 *
 * @param ri Replicator: x_VCORE_INTR_DST_CNT (??), 0-1
 */
#define VTSS_CPU_DST_INTR_IDENT(ri)          VTSS_IOREG(VTSS_TO_CPU,0x81 + (ri))

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
 * @param ri Replicator: x_VCORE_INTR_DST_CNT (??), 0-1
 */
#define VTSS_CPU_DST_INTR_IDENT1(ri)         VTSS_IOREG(VTSS_TO_CPU,0x83 + (ri))

/** 
 * \brief
 * Bit 32-49 of field DST_INTR_IDENT.
 *
 * \details 
 * Field: ::VTSS_CPU_DST_INTR_IDENT1 . DST_INTR_IDENT1
 */
#define  VTSS_F_CPU_DST_INTR_IDENT1_DST_INTR_IDENT1(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_CPU_DST_INTR_IDENT1_DST_INTR_IDENT1     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_CPU_DST_INTR_IDENT1_DST_INTR_IDENT1(x)  VTSS_EXTRACT_BITFIELD(x,0,18)


/** 
 * \brief External source interrupt polarity
 *
 * \details
 * Register: \a CPU:INTR:EXT_SRC_INTR_POL
 */
#define VTSS_CPU_EXT_SRC_INTR_POL            VTSS_IOREG(VTSS_TO_CPU,0x85)

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
#define  VTSS_F_CPU_EXT_SRC_INTR_POL_EXT_SRC_INTR_POL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CPU_EXT_SRC_INTR_POL_EXT_SRC_INTR_POL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CPU_EXT_SRC_INTR_POL_EXT_SRC_INTR_POL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief External destination interrupt polarity
 *
 * \details
 * Register: \a CPU:INTR:EXT_DST_INTR_POL
 */
#define VTSS_CPU_EXT_DST_INTR_POL            VTSS_IOREG(VTSS_TO_CPU,0x86)

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
#define  VTSS_F_CPU_EXT_DST_INTR_POL_EXT_DST_INTR_POL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CPU_EXT_DST_INTR_POL_EXT_DST_INTR_POL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CPU_EXT_DST_INTR_POL_EXT_DST_INTR_POL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief External interrupt destination output drive mode
 *
 * \details
 * Register: \a CPU:INTR:EXT_DST_INTR_DRV
 */
#define VTSS_CPU_EXT_DST_INTR_DRV            VTSS_IOREG(VTSS_TO_CPU,0x87)

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
#define  VTSS_F_CPU_EXT_DST_INTR_DRV_EXT_DST_INTR_DRV(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CPU_EXT_DST_INTR_DRV_EXT_DST_INTR_DRV     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CPU_EXT_DST_INTR_DRV_EXT_DST_INTR_DRV(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Device interrupt polarity
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_POL
 */
#define VTSS_CPU_DEV_INTR_POL                VTSS_IOREG(VTSS_TO_CPU,0x88)

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
#define  VTSS_F_CPU_DEV_INTR_POL_DEV_INTR_POL(x)  (x)
#define  VTSS_M_CPU_DEV_INTR_POL_DEV_INTR_POL     0xffffffff
#define  VTSS_X_CPU_DEV_INTR_POL_DEV_INTR_POL(x)  (x)


/** 
 * \brief Device interrupt polarity
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_POL1
 */
#define VTSS_CPU_DEV_INTR_POL1               VTSS_IOREG(VTSS_TO_CPU,0x89)

/** 
 * \brief
 * Bit 32-63 of field DEV_INTR_POL.
 *
 * \details 
 * 0: Device interrupt is active low
 * 1: Device interrupt is active high
 *
 * Field: ::VTSS_CPU_DEV_INTR_POL1 . DEV_INTR_POL1
 */
#define  VTSS_F_CPU_DEV_INTR_POL1_DEV_INTR_POL1(x)  (x)
#define  VTSS_M_CPU_DEV_INTR_POL1_DEV_INTR_POL1     0xffffffff
#define  VTSS_X_CPU_DEV_INTR_POL1_DEV_INTR_POL1(x)  (x)


/** 
 * \brief Device interrupt polarity
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_POL2
 */
#define VTSS_CPU_DEV_INTR_POL2               VTSS_IOREG(VTSS_TO_CPU,0x8a)

/** 
 * \brief
 * Bit 64-64 of field DEV_INTR_POL.
 *
 * \details 
 * 0: Device interrupt is active low
 * 1: Device interrupt is active high
 *
 * Field: ::VTSS_CPU_DEV_INTR_POL2 . DEV_INTR_POL2
 */
#define  VTSS_F_CPU_DEV_INTR_POL2_DEV_INTR_POL2(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_DEV_INTR_POL2_DEV_INTR_POL2  VTSS_BIT(0)
#define  VTSS_X_CPU_DEV_INTR_POL2_DEV_INTR_POL2(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Device interrupt raw status
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_RAW
 */
#define VTSS_CPU_DEV_INTR_RAW                VTSS_IOREG(VTSS_TO_CPU,0x8b)

/** 
 * \brief
 * Shows the current value of individual device interrupt sources. All
 * sources are active high (sources have been corrected for polarity as
 * configured in DEV_INTR_POL).
 *
 * \details 
 * Field: ::VTSS_CPU_DEV_INTR_RAW . DEV_INTR_RAW
 */
#define  VTSS_F_CPU_DEV_INTR_RAW_DEV_INTR_RAW(x)  (x)
#define  VTSS_M_CPU_DEV_INTR_RAW_DEV_INTR_RAW     0xffffffff
#define  VTSS_X_CPU_DEV_INTR_RAW_DEV_INTR_RAW(x)  (x)


/** 
 * \brief Device interrupt raw status
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_RAW1
 */
#define VTSS_CPU_DEV_INTR_RAW1               VTSS_IOREG(VTSS_TO_CPU,0x8c)

/** 
 * \brief
 * Bit 32-63 of field DEV_INTR_RAW.
 *
 * \details 
 * Field: ::VTSS_CPU_DEV_INTR_RAW1 . DEV_INTR_RAW1
 */
#define  VTSS_F_CPU_DEV_INTR_RAW1_DEV_INTR_RAW1(x)  (x)
#define  VTSS_M_CPU_DEV_INTR_RAW1_DEV_INTR_RAW1     0xffffffff
#define  VTSS_X_CPU_DEV_INTR_RAW1_DEV_INTR_RAW1(x)  (x)


/** 
 * \brief Device interrupt raw status
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_RAW2
 */
#define VTSS_CPU_DEV_INTR_RAW2               VTSS_IOREG(VTSS_TO_CPU,0x8d)

/** 
 * \brief
 * Bit 64-64 of field DEV_INTR_RAW.
 *
 * \details 
 * Field: ::VTSS_CPU_DEV_INTR_RAW2 . DEV_INTR_RAW2
 */
#define  VTSS_F_CPU_DEV_INTR_RAW2_DEV_INTR_RAW2(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_DEV_INTR_RAW2_DEV_INTR_RAW2  VTSS_BIT(0)
#define  VTSS_X_CPU_DEV_INTR_RAW2_DEV_INTR_RAW2(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Device interrupt trigger mode
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_TRIGGER
 *
 * @param ri Register: DEV_INTR_TRIGGER (??), 0-1
 */
#define VTSS_CPU_DEV_INTR_TRIGGER(ri)        VTSS_IOREG(VTSS_TO_CPU,0x8e + (ri))

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
#define  VTSS_F_CPU_DEV_INTR_TRIGGER_DEV_INTR_TRIGGER(x)  (x)
#define  VTSS_M_CPU_DEV_INTR_TRIGGER_DEV_INTR_TRIGGER     0xffffffff
#define  VTSS_X_CPU_DEV_INTR_TRIGGER_DEV_INTR_TRIGGER(x)  (x)


/** 
 * \brief Device interrupt trigger mode
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_TRIGGER1
 *
 * @param ri Register: DEV_INTR_TRIGGER1 (??), 0-1
 */
#define VTSS_CPU_DEV_INTR_TRIGGER1(ri)       VTSS_IOREG(VTSS_TO_CPU,0x90 + (ri))

/** 
 * \brief
 * Bit 32-63 of field DEV_INTR_TRIGGER.
 *
 * \details 
 * 0: Interrupt is level-activated
 * 1: Interrupt is edge-triggered
 * 2: Interrupt is falling-edge-triggered
 * 3: Interrupt is rising-edge-triggered
 *
 * Field: ::VTSS_CPU_DEV_INTR_TRIGGER1 . DEV_INTR_TRIGGER1
 */
#define  VTSS_F_CPU_DEV_INTR_TRIGGER1_DEV_INTR_TRIGGER1(x)  (x)
#define  VTSS_M_CPU_DEV_INTR_TRIGGER1_DEV_INTR_TRIGGER1     0xffffffff
#define  VTSS_X_CPU_DEV_INTR_TRIGGER1_DEV_INTR_TRIGGER1(x)  (x)


/** 
 * \brief Device interrupt trigger mode
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_TRIGGER2
 *
 * @param ri Register: DEV_INTR_TRIGGER2 (??), 0-1
 */
#define VTSS_CPU_DEV_INTR_TRIGGER2(ri)       VTSS_IOREG(VTSS_TO_CPU,0x92 + (ri))

/** 
 * \brief
 * Bit 64-64 of field DEV_INTR_TRIGGER.
 *
 * \details 
 * 0: Interrupt is level-activated
 * 1: Interrupt is edge-triggered
 * 2: Interrupt is falling-edge-triggered
 * 3: Interrupt is rising-edge-triggered
 *
 * Field: ::VTSS_CPU_DEV_INTR_TRIGGER2 . DEV_INTR_TRIGGER2
 */
#define  VTSS_F_CPU_DEV_INTR_TRIGGER2_DEV_INTR_TRIGGER2(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_DEV_INTR_TRIGGER2_DEV_INTR_TRIGGER2  VTSS_BIT(0)
#define  VTSS_X_CPU_DEV_INTR_TRIGGER2_DEV_INTR_TRIGGER2(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Device interrupt sticky status
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_STICKY
 */
#define VTSS_CPU_DEV_INTR_STICKY             VTSS_IOREG(VTSS_TO_CPU,0x94)

/** 
 * \brief
 * This register is set based on device interrupt sourec events. See
 * DEV_INTR_TRIGGER for more information. Bits in this register remains set
 * until cleared by software.
 *
 * \details 
 * Field: ::VTSS_CPU_DEV_INTR_STICKY . DEV_INTR_STICKY
 */
#define  VTSS_F_CPU_DEV_INTR_STICKY_DEV_INTR_STICKY(x)  (x)
#define  VTSS_M_CPU_DEV_INTR_STICKY_DEV_INTR_STICKY     0xffffffff
#define  VTSS_X_CPU_DEV_INTR_STICKY_DEV_INTR_STICKY(x)  (x)


/** 
 * \brief Device interrupt sticky status
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_STICKY1
 */
#define VTSS_CPU_DEV_INTR_STICKY1            VTSS_IOREG(VTSS_TO_CPU,0x95)

/** 
 * \brief
 * Bit 32-63 of field DEV_INTR_STICKY.
 *
 * \details 
 * Field: ::VTSS_CPU_DEV_INTR_STICKY1 . DEV_INTR_STICKY1
 */
#define  VTSS_F_CPU_DEV_INTR_STICKY1_DEV_INTR_STICKY1(x)  (x)
#define  VTSS_M_CPU_DEV_INTR_STICKY1_DEV_INTR_STICKY1     0xffffffff
#define  VTSS_X_CPU_DEV_INTR_STICKY1_DEV_INTR_STICKY1(x)  (x)


/** 
 * \brief Device interrupt sticky status
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_STICKY2
 */
#define VTSS_CPU_DEV_INTR_STICKY2            VTSS_IOREG(VTSS_TO_CPU,0x96)

/** 
 * \brief
 * Bit 64-64 of field DEV_INTR_STICKY.
 *
 * \details 
 * Field: ::VTSS_CPU_DEV_INTR_STICKY2 . DEV_INTR_STICKY2
 */
#define  VTSS_F_CPU_DEV_INTR_STICKY2_DEV_INTR_STICKY2(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_DEV_INTR_STICKY2_DEV_INTR_STICKY2  VTSS_BIT(0)
#define  VTSS_X_CPU_DEV_INTR_STICKY2_DEV_INTR_STICKY2(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Device interrupt bypass enable
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_BYPASS
 */
#define VTSS_CPU_DEV_INTR_BYPASS             VTSS_IOREG(VTSS_TO_CPU,0x97)

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
#define  VTSS_F_CPU_DEV_INTR_BYPASS_DEV_INTR_BYPASS(x)  (x)
#define  VTSS_M_CPU_DEV_INTR_BYPASS_DEV_INTR_BYPASS     0xffffffff
#define  VTSS_X_CPU_DEV_INTR_BYPASS_DEV_INTR_BYPASS(x)  (x)


/** 
 * \brief Device interrupt bypass enable
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_BYPASS1
 */
#define VTSS_CPU_DEV_INTR_BYPASS1            VTSS_IOREG(VTSS_TO_CPU,0x98)

/** 
 * \brief
 * Bit 32-63 of field DEV_INTR_BYPASS.
 *
 * \details 
 * Field: ::VTSS_CPU_DEV_INTR_BYPASS1 . DEV_INTR_BYPASS1
 */
#define  VTSS_F_CPU_DEV_INTR_BYPASS1_DEV_INTR_BYPASS1(x)  (x)
#define  VTSS_M_CPU_DEV_INTR_BYPASS1_DEV_INTR_BYPASS1     0xffffffff
#define  VTSS_X_CPU_DEV_INTR_BYPASS1_DEV_INTR_BYPASS1(x)  (x)


/** 
 * \brief Device interrupt bypass enable
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_BYPASS2
 */
#define VTSS_CPU_DEV_INTR_BYPASS2            VTSS_IOREG(VTSS_TO_CPU,0x99)

/** 
 * \brief
 * Bit 64-64 of field DEV_INTR_BYPASS.
 *
 * \details 
 * Field: ::VTSS_CPU_DEV_INTR_BYPASS2 . DEV_INTR_BYPASS2
 */
#define  VTSS_F_CPU_DEV_INTR_BYPASS2_DEV_INTR_BYPASS2(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_DEV_INTR_BYPASS2_DEV_INTR_BYPASS2  VTSS_BIT(0)
#define  VTSS_X_CPU_DEV_INTR_BYPASS2_DEV_INTR_BYPASS2(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Device interrupt enable
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_ENA
 */
#define VTSS_CPU_DEV_INTR_ENA                VTSS_IOREG(VTSS_TO_CPU,0x9a)

/** 
 * \brief
 * Set to enable propagation of individual device interrupt sources to the
 * main interrupt controller.
 *
 * \details 
 * Field: ::VTSS_CPU_DEV_INTR_ENA . DEV_INTR_ENA
 */
#define  VTSS_F_CPU_DEV_INTR_ENA_DEV_INTR_ENA(x)  (x)
#define  VTSS_M_CPU_DEV_INTR_ENA_DEV_INTR_ENA     0xffffffff
#define  VTSS_X_CPU_DEV_INTR_ENA_DEV_INTR_ENA(x)  (x)


/** 
 * \brief Device interrupt enable
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_ENA1
 */
#define VTSS_CPU_DEV_INTR_ENA1               VTSS_IOREG(VTSS_TO_CPU,0x9b)

/** 
 * \brief
 * Bit 32-63 of field DEV_INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_CPU_DEV_INTR_ENA1 . DEV_INTR_ENA1
 */
#define  VTSS_F_CPU_DEV_INTR_ENA1_DEV_INTR_ENA1(x)  (x)
#define  VTSS_M_CPU_DEV_INTR_ENA1_DEV_INTR_ENA1     0xffffffff
#define  VTSS_X_CPU_DEV_INTR_ENA1_DEV_INTR_ENA1(x)  (x)


/** 
 * \brief Device interrupt enable
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_ENA2
 */
#define VTSS_CPU_DEV_INTR_ENA2               VTSS_IOREG(VTSS_TO_CPU,0x9c)

/** 
 * \brief
 * Bit 64-64 of field DEV_INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_CPU_DEV_INTR_ENA2 . DEV_INTR_ENA2
 */
#define  VTSS_F_CPU_DEV_INTR_ENA2_DEV_INTR_ENA2(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_DEV_INTR_ENA2_DEV_INTR_ENA2  VTSS_BIT(0)
#define  VTSS_X_CPU_DEV_INTR_ENA2_DEV_INTR_ENA2(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Currently active device interrupts
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_IDENT
 */
#define VTSS_CPU_DEV_INTR_IDENT              VTSS_IOREG(VTSS_TO_CPU,0x9d)

/** 
 * \brief
 * Shows the currently active interrupt sources. For interrupt sources that
 * are not bypassed this register is a result of AND'ing DEV_INTR_STICKY
 * with DEV_INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_CPU_DEV_INTR_IDENT . DEV_INTR_IDENT
 */
#define  VTSS_F_CPU_DEV_INTR_IDENT_DEV_INTR_IDENT(x)  (x)
#define  VTSS_M_CPU_DEV_INTR_IDENT_DEV_INTR_IDENT     0xffffffff
#define  VTSS_X_CPU_DEV_INTR_IDENT_DEV_INTR_IDENT(x)  (x)


/** 
 * \brief Currently active device interrupts
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_IDENT1
 */
#define VTSS_CPU_DEV_INTR_IDENT1             VTSS_IOREG(VTSS_TO_CPU,0x9e)

/** 
 * \brief
 * Bit 32-63 of field DEV_INTR_IDENT.
 *
 * \details 
 * Field: ::VTSS_CPU_DEV_INTR_IDENT1 . DEV_INTR_IDENT1
 */
#define  VTSS_F_CPU_DEV_INTR_IDENT1_DEV_INTR_IDENT1(x)  (x)
#define  VTSS_M_CPU_DEV_INTR_IDENT1_DEV_INTR_IDENT1     0xffffffff
#define  VTSS_X_CPU_DEV_INTR_IDENT1_DEV_INTR_IDENT1(x)  (x)


/** 
 * \brief Currently active device interrupts
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_IDENT2
 */
#define VTSS_CPU_DEV_INTR_IDENT2             VTSS_IOREG(VTSS_TO_CPU,0x9f)

/** 
 * \brief
 * Bit 64-64 of field DEV_INTR_IDENT.
 *
 * \details 
 * Field: ::VTSS_CPU_DEV_INTR_IDENT2 . DEV_INTR_IDENT2
 */
#define  VTSS_F_CPU_DEV_INTR_IDENT2_DEV_INTR_IDENT2(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_DEV_INTR_IDENT2_DEV_INTR_IDENT2  VTSS_BIT(0)
#define  VTSS_X_CPU_DEV_INTR_IDENT2_DEV_INTR_IDENT2(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Device interrupt polarity
 *
 * \details
 * Register: \a CPU:INTR:KR6G_INTR_POL
 */
#define VTSS_CPU_KR6G_INTR_POL               VTSS_IOREG(VTSS_TO_CPU,0xa0)

/** 
 * \brief
 * Set individual bits in this register to configure polarity of the
 * corresponding device interrupt.
 *
 * \details 
 * 0: Device interrupt is active low
 * 1: Device interrupt is active high
 *
 * Field: ::VTSS_CPU_KR6G_INTR_POL . KR6G_INTR_POL
 */
#define  VTSS_F_CPU_KR6G_INTR_POL_KR6G_INTR_POL(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_CPU_KR6G_INTR_POL_KR6G_INTR_POL     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_CPU_KR6G_INTR_POL_KR6G_INTR_POL(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Device interrupt raw status
 *
 * \details
 * Register: \a CPU:INTR:KR6G_INTR_RAW
 */
#define VTSS_CPU_KR6G_INTR_RAW               VTSS_IOREG(VTSS_TO_CPU,0xa1)

/** 
 * \brief
 * Shows the current value of individual device interrupt sources. All
 * sources are active high (sources have been corrected for polarity as
 * configured in KR6G_INTR_POL).
 *
 * \details 
 * Field: ::VTSS_CPU_KR6G_INTR_RAW . KR6G_INTR_RAW
 */
#define  VTSS_F_CPU_KR6G_INTR_RAW_KR6G_INTR_RAW(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_CPU_KR6G_INTR_RAW_KR6G_INTR_RAW     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_CPU_KR6G_INTR_RAW_KR6G_INTR_RAW(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Device interrupt trigger mode
 *
 * \details
 * Register: \a CPU:INTR:KR6G_INTR_TRIGGER
 *
 * @param ri Register: KR6G_INTR_TRIGGER (??), 0-1
 */
#define VTSS_CPU_KR6G_INTR_TRIGGER(ri)       VTSS_IOREG(VTSS_TO_CPU,0xa2 + (ri))

/** 
 * \brief
 * Configure trigger mode of individual device interrupt sources. The
 * trigger mode determines how the value of the KR6G_INTR_RAW register is
 * transferred to the KR6G_INTR_STICKY register. This register is
 * replicated, the first replication controls bit 0 in the encoding, the
 * second replication controls bit 1 in the encoding. I.e. to configure
 * edge-triggered interrupt for device 3; set KR6G_INTR_TRIGGER[0][3]='1'
 * and KR6G_INTR_TRIGGER[1][3]='0'.For level-triggered interrupts
 * KR6G_INTR_STICKY is set for as long as the corresponding bit in
 * KR6G_INTR_RAW is high - i.e. is not possible to clear a bit in
 * KR6G_INTR_STICKY until the corresponding KR6G_INTR_RAW is zero.For
 * edge-triggeded interrupts KR6G_INTR_STICKY is set when the corresponding
 * bit in KR6G_INTR_RAW changes value.For falling-edge-triggeded interrupts
 * KR6G_INTR_STICKY is set when the corresponding bit in KR6G_INTR_RAW
 * changes from '1' to '0'.For rising-edge-triggeded interrupts
 * KR6G_INTR_STICKY is set when the corresponding bit in KR6G_INTR_RAW
 * changes from '0' to '1'.
 *
 * \details 
 * 0: Interrupt is level-activated
 * 1: Interrupt is edge-triggered
 * 2: Interrupt is falling-edge-triggered
 * 3: Interrupt is rising-edge-triggered
 *
 * Field: ::VTSS_CPU_KR6G_INTR_TRIGGER . KR6G_INTR_TRIGGER
 */
#define  VTSS_F_CPU_KR6G_INTR_TRIGGER_KR6G_INTR_TRIGGER(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_CPU_KR6G_INTR_TRIGGER_KR6G_INTR_TRIGGER     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_CPU_KR6G_INTR_TRIGGER_KR6G_INTR_TRIGGER(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Device interrupt sticky status
 *
 * \details
 * Register: \a CPU:INTR:KR6G_INTR_STICKY
 */
#define VTSS_CPU_KR6G_INTR_STICKY            VTSS_IOREG(VTSS_TO_CPU,0xa4)

/** 
 * \brief
 * This register is set based on device interrupt sourec events. See
 * KR6G_INTR_TRIGGER for more information. Bits in this register remains
 * set until cleared by software.
 *
 * \details 
 * Field: ::VTSS_CPU_KR6G_INTR_STICKY . KR6G_INTR_STICKY
 */
#define  VTSS_F_CPU_KR6G_INTR_STICKY_KR6G_INTR_STICKY(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_CPU_KR6G_INTR_STICKY_KR6G_INTR_STICKY     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_CPU_KR6G_INTR_STICKY_KR6G_INTR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Device interrupt bypass enable
 *
 * \details
 * Register: \a CPU:INTR:KR6G_INTR_BYPASS
 */
#define VTSS_CPU_KR6G_INTR_BYPASS            VTSS_IOREG(VTSS_TO_CPU,0xa5)

/** 
 * \brief
 * This register allows bypass of KR6G_INTR_STICKY for individual device
 * interrupt sources. When a device interrupt source is in bypass mode then
 * KR6G_INTR_RAW is used instead of KR6G_INTR_STICKY.See note on bypass in
 * INTR_BYPASS.
 *
 * \details 
 * Field: ::VTSS_CPU_KR6G_INTR_BYPASS . KR6G_INTR_BYPASS
 */
#define  VTSS_F_CPU_KR6G_INTR_BYPASS_KR6G_INTR_BYPASS(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_CPU_KR6G_INTR_BYPASS_KR6G_INTR_BYPASS     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_CPU_KR6G_INTR_BYPASS_KR6G_INTR_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Device interrupt enable
 *
 * \details
 * Register: \a CPU:INTR:KR6G_INTR_ENA
 */
#define VTSS_CPU_KR6G_INTR_ENA               VTSS_IOREG(VTSS_TO_CPU,0xa6)

/** 
 * \brief
 * Set to enable propagation of individual device interrupt sources to the
 * main interrupt controller.
 *
 * \details 
 * Field: ::VTSS_CPU_KR6G_INTR_ENA . KR6G_INTR_ENA
 */
#define  VTSS_F_CPU_KR6G_INTR_ENA_KR6G_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_CPU_KR6G_INTR_ENA_KR6G_INTR_ENA     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_CPU_KR6G_INTR_ENA_KR6G_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Currently active device interrupts
 *
 * \details
 * Register: \a CPU:INTR:KR6G_INTR_IDENT
 */
#define VTSS_CPU_KR6G_INTR_IDENT             VTSS_IOREG(VTSS_TO_CPU,0xa7)

/** 
 * \brief
 * Shows the currently active interrupt sources. For interrupt sources that
 * are not bypassed this register is a result of AND'ing KR6G_INTR_STICKY
 * with KR6G_INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_CPU_KR6G_INTR_IDENT . KR6G_INTR_IDENT
 */
#define  VTSS_F_CPU_KR6G_INTR_IDENT_KR6G_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_CPU_KR6G_INTR_IDENT_KR6G_INTR_IDENT     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_CPU_KR6G_INTR_IDENT_KR6G_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Device interrupt polarity
 *
 * \details
 * Register: \a CPU:INTR:KR10G_INTR_POL
 */
#define VTSS_CPU_KR10G_INTR_POL              VTSS_IOREG(VTSS_TO_CPU,0xa8)

/** 
 * \brief
 * Set individual bits in this register to configure polarity of the
 * corresponding device interrupt.
 *
 * \details 
 * 0: Device interrupt is active low
 * 1: Device interrupt is active high
 *
 * Field: ::VTSS_CPU_KR10G_INTR_POL . KR10G_INTR_POL
 */
#define  VTSS_F_CPU_KR10G_INTR_POL_KR10G_INTR_POL(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_CPU_KR10G_INTR_POL_KR10G_INTR_POL     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_CPU_KR10G_INTR_POL_KR10G_INTR_POL(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/** 
 * \brief Device interrupt raw status
 *
 * \details
 * Register: \a CPU:INTR:KR10G_INTR_RAW
 */
#define VTSS_CPU_KR10G_INTR_RAW              VTSS_IOREG(VTSS_TO_CPU,0xa9)

/** 
 * \brief
 * Shows the current value of individual device interrupt sources. All
 * sources are active high (sources have been corrected for polarity as
 * configured in KR10G_INTR_POL).
 *
 * \details 
 * Field: ::VTSS_CPU_KR10G_INTR_RAW . KR10G_INTR_RAW
 */
#define  VTSS_F_CPU_KR10G_INTR_RAW_KR10G_INTR_RAW(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_CPU_KR10G_INTR_RAW_KR10G_INTR_RAW     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_CPU_KR10G_INTR_RAW_KR10G_INTR_RAW(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/** 
 * \brief Device interrupt trigger mode
 *
 * \details
 * Register: \a CPU:INTR:KR10G_INTR_TRIGGER
 *
 * @param ri Register: KR10G_INTR_TRIGGER (??), 0-1
 */
#define VTSS_CPU_KR10G_INTR_TRIGGER(ri)      VTSS_IOREG(VTSS_TO_CPU,0xaa + (ri))

/** 
 * \brief
 * Configure trigger mode of individual device interrupt sources. The
 * trigger mode determines how the value of the KR10G_INTR_RAW register is
 * transferred to the KR10G_INTR_STICKY register. This register is
 * replicated, the first replication controls bit 0 in the encoding, the
 * second replication controls bit 1 in the encoding. I.e. to configure
 * edge-triggered interrupt for device 3; set KR10G_INTR_TRIGGER[0][3]='1'
 * and KR10G_INTR_TRIGGER[1][3]='0'.For level-triggered interrupts
 * KR10G_INTR_STICKY is set for as long as the corresponding bit in
 * KR10G_INTR_RAW is high - i.e. is not possible to clear a bit in
 * KR10G_INTR_STICKY until the corresponding KR10G_INTR_RAW is zero.For
 * edge-triggeded interrupts KR10G_INTR_STICKY is set when the
 * corresponding bit in KR10G_INTR_RAW changes value.For
 * falling-edge-triggeded interrupts KR10G_INTR_STICKY is set when the
 * corresponding bit in KR10G_INTR_RAW changes from '1' to '0'.For
 * rising-edge-triggeded interrupts KR10G_INTR_STICKY is set when the
 * corresponding bit in KR10G_INTR_RAW changes from '0' to '1'.
 *
 * \details 
 * 0: Interrupt is level-activated
 * 1: Interrupt is edge-triggered
 * 2: Interrupt is falling-edge-triggered
 * 3: Interrupt is rising-edge-triggered
 *
 * Field: ::VTSS_CPU_KR10G_INTR_TRIGGER . KR10G_INTR_TRIGGER
 */
#define  VTSS_F_CPU_KR10G_INTR_TRIGGER_KR10G_INTR_TRIGGER(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_CPU_KR10G_INTR_TRIGGER_KR10G_INTR_TRIGGER     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_CPU_KR10G_INTR_TRIGGER_KR10G_INTR_TRIGGER(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/** 
 * \brief Device interrupt sticky status
 *
 * \details
 * Register: \a CPU:INTR:KR10G_INTR_STICKY
 */
#define VTSS_CPU_KR10G_INTR_STICKY           VTSS_IOREG(VTSS_TO_CPU,0xac)

/** 
 * \brief
 * This register is set based on device interrupt sourec events. See
 * KR10G_INTR_TRIGGER for more information. Bits in this register remains
 * set until cleared by software.
 *
 * \details 
 * Field: ::VTSS_CPU_KR10G_INTR_STICKY . KR10G_INTR_STICKY
 */
#define  VTSS_F_CPU_KR10G_INTR_STICKY_KR10G_INTR_STICKY(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_CPU_KR10G_INTR_STICKY_KR10G_INTR_STICKY     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_CPU_KR10G_INTR_STICKY_KR10G_INTR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/** 
 * \brief Device interrupt bypass enable
 *
 * \details
 * Register: \a CPU:INTR:KR10G_INTR_BYPASS
 */
#define VTSS_CPU_KR10G_INTR_BYPASS           VTSS_IOREG(VTSS_TO_CPU,0xad)

/** 
 * \brief
 * This register allows bypass of KR10G_INTR_STICKY for individual device
 * interrupt sources. When a device interrupt source is in bypass mode then
 * KR10G_INTR_RAW is used instead of KR10G_INTR_STICKY.See note on bypass
 * in INTR_BYPASS.
 *
 * \details 
 * Field: ::VTSS_CPU_KR10G_INTR_BYPASS . KR10G_INTR_BYPASS
 */
#define  VTSS_F_CPU_KR10G_INTR_BYPASS_KR10G_INTR_BYPASS(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_CPU_KR10G_INTR_BYPASS_KR10G_INTR_BYPASS     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_CPU_KR10G_INTR_BYPASS_KR10G_INTR_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/** 
 * \brief Device interrupt enable
 *
 * \details
 * Register: \a CPU:INTR:KR10G_INTR_ENA
 */
#define VTSS_CPU_KR10G_INTR_ENA              VTSS_IOREG(VTSS_TO_CPU,0xae)

/** 
 * \brief
 * Set to enable propagation of individual device interrupt sources to the
 * main interrupt controller.
 *
 * \details 
 * Field: ::VTSS_CPU_KR10G_INTR_ENA . KR10G_INTR_ENA
 */
#define  VTSS_F_CPU_KR10G_INTR_ENA_KR10G_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_CPU_KR10G_INTR_ENA_KR10G_INTR_ENA     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_CPU_KR10G_INTR_ENA_KR10G_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/** 
 * \brief Currently active device interrupts
 *
 * \details
 * Register: \a CPU:INTR:KR10G_INTR_IDENT
 */
#define VTSS_CPU_KR10G_INTR_IDENT            VTSS_IOREG(VTSS_TO_CPU,0xaf)

/** 
 * \brief
 * Shows the currently active interrupt sources. For interrupt sources that
 * are not bypassed this register is a result of AND'ing KR10G_INTR_STICKY
 * with KR10G_INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_CPU_KR10G_INTR_IDENT . KR10G_INTR_IDENT
 */
#define  VTSS_F_CPU_KR10G_INTR_IDENT_KR10G_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_CPU_KR10G_INTR_IDENT_KR10G_INTR_IDENT     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_CPU_KR10G_INTR_IDENT_KR10G_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,0,20)

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
#define VTSS_CPU_DDRCTRL_CLK                 VTSS_IOREG(VTSS_TO_CPU,0xb0)

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
 * Enable AXI clock of DDR controller.
 *
 * \details 
 * 0 : clock disable
 * 1 : clock enable
 *
 * Field: ::VTSS_CPU_DDRCTRL_CLK . DDR_AXI_CLK_ENA
 */
#define  VTSS_F_CPU_DDRCTRL_CLK_DDR_AXI_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_DDRCTRL_CLK_DDR_AXI_CLK_ENA  VTSS_BIT(1)
#define  VTSS_X_CPU_DDRCTRL_CLK_DDR_AXI_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

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
#define  VTSS_F_CPU_DDRCTRL_CLK_DDR_APB_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_DDRCTRL_CLK_DDR_APB_CLK_ENA  VTSS_BIT(2)
#define  VTSS_X_CPU_DDRCTRL_CLK_DDR_APB_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

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
#define  VTSS_F_CPU_DDRCTRL_CLK_DDRPHY_CTL_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_DDRCTRL_CLK_DDRPHY_CTL_CLK_ENA  VTSS_BIT(3)
#define  VTSS_X_CPU_DDRCTRL_CLK_DDRPHY_CTL_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

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
#define  VTSS_F_CPU_DDRCTRL_CLK_DDRPHY_APB_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CPU_DDRCTRL_CLK_DDRPHY_APB_CLK_ENA  VTSS_BIT(4)
#define  VTSS_X_CPU_DDRCTRL_CLK_DDRPHY_APB_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief DDR Controller/Phy reset configuration
 *
 * \details
 * Register: \a CPU:DDRCTRL:DDRCTRL_RST
 */
#define VTSS_CPU_DDRCTRL_RST                 VTSS_IOREG(VTSS_TO_CPU,0xb1)

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
 * Assert AXI reset of DDR controller. The controller registers must be
 * configured when AXI channel of DDR controller is in reset.
 *
 * \details 
 * 0 : No Reset
 * 1 : Reset.
 *
 * Field: ::VTSS_CPU_DDRCTRL_RST . DDR_AXI_RST
 */
#define  VTSS_F_CPU_DDRCTRL_RST_DDR_AXI_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_DDRCTRL_RST_DDR_AXI_RST   VTSS_BIT(1)
#define  VTSS_X_CPU_DDRCTRL_RST_DDR_AXI_RST(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

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
#define  VTSS_F_CPU_DDRCTRL_RST_DDR_APB_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CPU_DDRCTRL_RST_DDR_APB_RST   VTSS_BIT(2)
#define  VTSS_X_CPU_DDRCTRL_RST_DDR_APB_RST(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Assert DDR PHY PUB/PHY controller reset
 *
 * \details 
 * 0 : No Reset
 * 1 : Reset.
 *
 * Field: ::VTSS_CPU_DDRCTRL_RST . DDRPHY_CTL_RST
 */
#define  VTSS_F_CPU_DDRCTRL_RST_DDRPHY_CTL_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_DDRCTRL_RST_DDRPHY_CTL_RST  VTSS_BIT(3)
#define  VTSS_X_CPU_DDRCTRL_RST_DDRPHY_CTL_RST(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

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
#define  VTSS_F_CPU_DDRCTRL_RST_DDRPHY_APB_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CPU_DDRCTRL_RST_DDRPHY_APB_RST  VTSS_BIT(4)
#define  VTSS_X_CPU_DDRCTRL_RST_DDRPHY_APB_RST(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief DDR controller interrupt raw status
 *
 * \details
 * Register: \a CPU:DDRCTRL:DDRC_INTR_RAW_STAT
 */
#define VTSS_CPU_DDRC_INTR_RAW_STAT          VTSS_IOREG(VTSS_TO_CPU,0xb2)

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
 * This interrupt is asserted when a correctable ECC error is detected. It
 * may be cleared by writing to ECCCLR.ecc_clr_corr_err.
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
 * It may be cleared by writing to ECCCLR.ecc_clr_uncorr_err.
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
 * This interrupt is asserted when a parity or CRC error is detected on the
 * DFI interface. It may be cleared by writing to
 * CRCPARCTL0.dfi_alert_err_int_clr
 *
 * \details 
 * 0 : Interrupt deasserted.
 * 1 : Interrupt asserted.
 *
 * Field: ::VTSS_CPU_DDRC_INTR_RAW_STAT . DFI_ALERT_ERR_INTR_RAW_STAT
 */
#define  VTSS_F_CPU_DDRC_INTR_RAW_STAT_DFI_ALERT_ERR_INTR_RAW_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_DDRC_INTR_RAW_STAT_DFI_ALERT_ERR_INTR_RAW_STAT  VTSS_BIT(3)
#define  VTSS_X_CPU_DDRC_INTR_RAW_STAT_DFI_ALERT_ERR_INTR_RAW_STAT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/** 
 * \brief DDR controller interrupt mask register
 *
 * \details
 * Register: \a CPU:DDRCTRL:DDRC_INTR_MASK
 */
#define VTSS_CPU_DDRC_INTR_MASK              VTSS_IOREG(VTSS_TO_CPU,0xb3)

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
 * Mask for correctable ECC error interrupt
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
 * Mask for uncorrectable ECC error interrupt
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
 * Mask for DFI ALERT error interrupt
 *
 * \details 
 * 0 : Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: ::VTSS_CPU_DDRC_INTR_MASK . DFI_ALERT_ERR_INTR_MASK
 */
#define  VTSS_F_CPU_DDRC_INTR_MASK_DFI_ALERT_ERR_INTR_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_DDRC_INTR_MASK_DFI_ALERT_ERR_INTR_MASK  VTSS_BIT(3)
#define  VTSS_X_CPU_DDRC_INTR_MASK_DFI_ALERT_ERR_INTR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/** 
 * \brief DDR controller interrupt masked status
 *
 * \details
 * Register: \a CPU:DDRCTRL:DDRC_INTR_MASKED_STAT
 */
#define VTSS_CPU_DDRC_INTR_MASKED_STAT       VTSS_IOREG(VTSS_TO_CPU,0xb4)

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
 * Status for correctable ECC error interrupt after taking interrupt mask
 * into account.
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
 * Status for Uncorrectable ECC error interrupt after taking interrupt mask
 * into account.
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
 * Status for DFI ALERT error interrupt after taking interrupt mask into
 * account.
 *
 * \details 
 * 0 : Interrupt deasserted.
 * 1 : Interrupt asserted.
 *
 * Field: ::VTSS_CPU_DDRC_INTR_MASKED_STAT . DFI_ALERT_ERR_INTR_STAT
 */
#define  VTSS_F_CPU_DDRC_INTR_MASKED_STAT_DFI_ALERT_ERR_INTR_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_DDRC_INTR_MASKED_STAT_DFI_ALERT_ERR_INTR_STAT  VTSS_BIT(3)
#define  VTSS_X_CPU_DDRC_INTR_MASKED_STAT_DFI_ALERT_ERR_INTR_STAT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


#endif /* _VTSS_FA_KERNEL_REGS_CPU_H_ */
