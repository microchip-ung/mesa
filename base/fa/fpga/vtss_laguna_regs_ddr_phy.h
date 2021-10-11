/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#ifndef _VTSS_LAGUNA_REGS_DDR_PHY_H_
#define _VTSS_LAGUNA_REGS_DDR_PHY_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a DDR_PHY
 *
 * DesignWare Cores DDR3/2 PHY Memory Map
 *
 ***********************************************************************/

/**
 * Register Group: \a DDR_PHY:DDR3_2_PHY_PUB
 *
 * DesignWare Cores DDR3/2 PHY PUB
 */


/**
 * \brief Revision Identification Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:RIDR
 */
#define VTSS_DDR_PHY_RIDR                    VTSS_IOREG(VTSS_TO_DDR_PHY,0x0)

/**
 * \brief
 * PUB Revision.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RIDR . PUBID
 */
#define  VTSS_F_DDR_PHY_RIDR_PUBID(x)         VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_PHY_RIDR_PUBID            VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_PHY_RIDR_PUBID(x)         VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * PHY Revision.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RIDR . PHYID
 */
#define  VTSS_F_DDR_PHY_RIDR_PHYID(x)         VTSS_ENCODE_BITFIELD(x,12,12)
#define  VTSS_M_DDR_PHY_RIDR_PHYID            VTSS_ENCODE_BITMASK(12,12)
#define  VTSS_X_DDR_PHY_RIDR_PHYID(x)         VTSS_EXTRACT_BITFIELD(x,12,12)

/**
 * \brief
 * User-Defined Revision ID.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RIDR . UDRID
 */
#define  VTSS_F_DDR_PHY_RIDR_UDRID(x)         VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DDR_PHY_RIDR_UDRID            VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DDR_PHY_RIDR_UDRID(x)         VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief PHY Initialization Register
 *
 * \details
 * PHY Initialization Register is used to configure and control the
 * initialization of the PHY. This includes the
 * triggering of certain initialization routines, as well as the reset of
 * the PHY and/or the PLLs used in the PHY.
 *
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:PIR
 */
#define VTSS_DDR_PHY_PIR                     VTSS_IOREG(VTSS_TO_DDR_PHY,0x1)

/**
 * \brief
 * Initialization Trigger: A write of '1' to this bit triggers the DDR
 * system initialization,including PHY initialization, DRAM initialization,
 * and PHY training. The exactinitialization steps to be executed are
 * specified in bits 1 to 15 of this register. A bitsetting of 1 means the
 * step will be executed as part of the initialization sequence,while a
 * setting of '0' means the step will be bypassed. The initialization
 * trigger bitis self-clearing.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . INIT
 */
#define  VTSS_F_DDR_PHY_PIR_INIT(x)           VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_PIR_INIT              VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_PIR_INIT(x)           VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Impedance Calibration: Performs PHY impedance calibration. When set
 * theimpedance calibration will be performed in parallel with PHY
 * initialization (PLLinitialization + DDL calibration + PHY reset).
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . ZCAL
 */
#define  VTSS_F_DDR_PHY_PIR_ZCAL(x)           VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_PHY_PIR_ZCAL              VTSS_BIT(1)
#define  VTSS_X_DDR_PHY_PIR_ZCAL(x)           VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * PLL Initialization: Executes the PLL initialization sequence which
 * includes correctdriving of PLL power-down, reset and gear shift pins,
 * and then waiting for thePHY PLLs to lock.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . PLLINIT
 */
#define  VTSS_F_DDR_PHY_PIR_PLLINIT(x)        VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_PHY_PIR_PLLINIT           VTSS_BIT(4)
#define  VTSS_X_DDR_PHY_PIR_PLLINIT(x)        VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Digital Delay Line (DDL) Calibration: Performs PHY delay line
 * calibration.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . DCAL
 */
#define  VTSS_F_DDR_PHY_PIR_DCAL(x)           VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_PHY_PIR_DCAL              VTSS_BIT(5)
#define  VTSS_X_DDR_PHY_PIR_DCAL(x)           VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * PHY Reset: Resets the AC and DATX8 modules by asserting the AC/DATX8
 * resetpin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . PHYRST
 */
#define  VTSS_F_DDR_PHY_PIR_PHYRST(x)         VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DDR_PHY_PIR_PHYRST            VTSS_BIT(6)
#define  VTSS_X_DDR_PHY_PIR_PHYRST(x)         VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * DRAM Reset (DDR3 Only): Issues a reset to the DRAM (by driving the
 * DRAMreset pin low) and wait 200us. This can be triggered in isolation or
 * with the fullDRAM initialization (DRAMINIT). For the later case, the
 * reset is issued and 200usis waited before starting the full
 * initialization sequence.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . DRAMRST
 */
#define  VTSS_F_DDR_PHY_PIR_DRAMRST(x)        VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DDR_PHY_PIR_DRAMRST           VTSS_BIT(7)
#define  VTSS_X_DDR_PHY_PIR_DRAMRST(x)        VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * DRAM Initialization: Executes the DRAM initialization sequence.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . DRAMINIT
 */
#define  VTSS_F_DDR_PHY_PIR_DRAMINIT(x)       VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DDR_PHY_PIR_DRAMINIT          VTSS_BIT(8)
#define  VTSS_X_DDR_PHY_PIR_DRAMINIT(x)       VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Write Leveling (DDR3 Only): Executes a PUB write leveling routine.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . WL
 */
#define  VTSS_F_DDR_PHY_PIR_WL(x)             VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_DDR_PHY_PIR_WL                VTSS_BIT(9)
#define  VTSS_X_DDR_PHY_PIR_WL(x)             VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Read DQS Gate Training: Executes a PUB training routine to determine
 * theoptimum position of the read data DQS strobe for maximum system
 * timingmargins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . QSGATE
 */
#define  VTSS_F_DDR_PHY_PIR_QSGATE(x)         VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_DDR_PHY_PIR_QSGATE            VTSS_BIT(10)
#define  VTSS_X_DDR_PHY_PIR_QSGATE(x)         VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Write Leveling Adjust (DDR3 Only): Executes a PUB training routine that
 * readjuststhe write latency used during write in case the write leveling
 * routinechanged the expected latency.Note: Ensure that the DCU command
 * cache is cleared prior to running WLADJ.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . WLADJ
 */
#define  VTSS_F_DDR_PHY_PIR_WLADJ(x)          VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_DDR_PHY_PIR_WLADJ             VTSS_BIT(11)
#define  VTSS_X_DDR_PHY_PIR_WLADJ(x)          VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Read Data Bit Deskew: Executes a PUB training routine to deskew the DQ
 * bitsduring read.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . RDDSKW
 */
#define  VTSS_F_DDR_PHY_PIR_RDDSKW(x)         VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DDR_PHY_PIR_RDDSKW            VTSS_BIT(12)
#define  VTSS_X_DDR_PHY_PIR_RDDSKW(x)         VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Write Data Bit Deskew: Executes a PUB training routine to deskew the DQ
 * bitsduring write.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . WRDSKW
 */
#define  VTSS_F_DDR_PHY_PIR_WRDSKW(x)         VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DDR_PHY_PIR_WRDSKW            VTSS_BIT(13)
#define  VTSS_X_DDR_PHY_PIR_WRDSKW(x)         VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Read Data Eye Training: Executes a PUB training routine to maximize the
 * readdata eye.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . RDEYE
 */
#define  VTSS_F_DDR_PHY_PIR_RDEYE(x)          VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_DDR_PHY_PIR_RDEYE             VTSS_BIT(14)
#define  VTSS_X_DDR_PHY_PIR_RDEYE(x)          VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Write Data Eye Training: Executes a PUB training routine to maximize the
 * writedata eye.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . WREYE
 */
#define  VTSS_F_DDR_PHY_PIR_WREYE(x)          VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_DDR_PHY_PIR_WREYE             VTSS_BIT(15)
#define  VTSS_X_DDR_PHY_PIR_WREYE(x)          VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Initialization Complete Pin Configuration: Specifies how the DFI
 * initializationcomplete output pin (dfi_init_complete) should be used to
 * indicate the status ofinitialization. Valid value are:0 = Asserted after
 * PHY initialization (DLL locking and impedance calibration) iscomplete.1
 * = Asserted after PHY initialization is complete and the triggered the
 * PUBinitialization (DRAM initialization, data training, or initialization
 * trigger with noselected initialization) is complete.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . ICPC
 */
#define  VTSS_F_DDR_PHY_PIR_ICPC(x)           VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DDR_PHY_PIR_ICPC              VTSS_BIT(16)
#define  VTSS_X_DDR_PHY_PIR_ICPC(x)           VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * PLL Bypass: A setting of 1 on this bit will put all PHY PLLs in bypass
 * mode.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . PIR_PLLBYP
 */
#define  VTSS_F_DDR_PHY_PIR_PIR_PLLBYP(x)     VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_DDR_PHY_PIR_PIR_PLLBYP        VTSS_BIT(17)
#define  VTSS_X_DDR_PHY_PIR_PIR_PLLBYP(x)     VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Controller DRAM Initialization: Indicates, if set, that DRAM
 * initialization will beperformed by the controller. Otherwise if not set
 * it indicates that DRAMinitialization will be performed using the
 * built-in initialization sequence or usingsoftware through the
 * configuration port.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . CTLDINIT
 */
#define  VTSS_F_DDR_PHY_PIR_CTLDINIT(x)       VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_DDR_PHY_PIR_CTLDINIT          VTSS_BIT(18)
#define  VTSS_X_DDR_PHY_PIR_CTLDINIT(x)       VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * RDIMM Initialization: Executes the RDIMM buffer chip initialization
 * beforeexecuting DRAM initialization. The RDIMM buffer chip
 * initialization is run after theDRAM is reset and CKE have been driven
 * high by the DRAM initializationsequence.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . RDIMMINIT
 */
#define  VTSS_F_DDR_PHY_PIR_RDIMMINIT(x)      VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_DDR_PHY_PIR_RDIMMINIT         VTSS_BIT(19)
#define  VTSS_X_DDR_PHY_PIR_RDIMMINIT(x)      VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Clear Status Registers: Writing 1 to this bit clears (reset to 0) select
 * status bits inregister PGSR0.This bit is primarily for debug purposes
 * and is typically not needed during normalfunctional operation. It can be
 * used when PGSR0.IDONE=1, to manually clear aselection of the PGSR0
 * status bits, although starting a new initialization process(PIR[0].INIT
 * = 1'b1) automatically clears the PGSR0 status bits associated with
 * theinitialization steps enabled.The following list describes which bits
 * within the PGSR0 register are clearedwhen CLRSR is set to 1'b1 and which
 * bits are not cleared:> The following bits are not cleared by PIR[27]
 * (CLRSR):- PGSR0[31] (APLOCK)- PGSR0[29:28] (PLDONE_CHN)- PGSR0[23]
 * (WLAERR)- PGSR0[21] (WLERR)- PGSR0[4] (DIDONE)- PGSR0[2] (DCDONE)-
 * PGSR0[1] (PLDONE)- PGSR0[0] (IDONE)> The following bits are always
 * zero:- PGSR0[30] (reserved)- PGSR0[19:12] (reserved)> The following bits
 * are cleared unconditionally by PIR[27] (CLRSR):- PGSR0[27] (WEERR)-
 * PGSR0[26] (REERR)- PGSR0[25] (WDERR)- PGSR0[24] (RDERR)- - PGSR0[22]
 * (QSGERR)- - PGSR0[20] (ZCERR)- - PGSR0[11] (WEDONE)- - PGSR0[10]
 * (REDONE)- - PGSR0[9] (WDDONE)- - PGSR0[8] (RDDONE)- - PGSR0[7]
 * (WLADONE)- - PGSR0[6] (QSGDONE)- - PGSR0[5] (WLDONE)
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . CLRSR
 */
#define  VTSS_F_DDR_PHY_PIR_CLRSR(x)          VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_DDR_PHY_PIR_CLRSR             VTSS_BIT(27)
#define  VTSS_X_DDR_PHY_PIR_CLRSR(x)          VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * PLL Lock Bypass: Bypasses or stops, if set, the waiting of PLLs to lock.
 * PLL lockwait is automatically triggered after reset. PLL lock wait may
 * be triggeredmanually using INIT and PLLINIT bits of the PIR register.
 * This bit is self-clearing.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . LOCKBYP
 */
#define  VTSS_F_DDR_PHY_PIR_LOCKBYP(x)        VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_DDR_PHY_PIR_LOCKBYP           VTSS_BIT(28)
#define  VTSS_X_DDR_PHY_PIR_LOCKBYP(x)        VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Digital Delay Line (DDL) Calibration Bypass: Bypasses or stops, if set,
 * DDLcalibration that automatically triggers after reset. DDL calibration
 * may betriggered manually using INIT and DCAL bits of the PIR register.
 * This bit is selfclearing.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . DCALBYP
 */
#define  VTSS_F_DDR_PHY_PIR_DCALBYP(x)        VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_DDR_PHY_PIR_DCALBYP           VTSS_BIT(29)
#define  VTSS_X_DDR_PHY_PIR_DCALBYP(x)        VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Impedance Calibration Bypass: Bypasses or stops, if set, impedance
 * calibrationof all ZQ control blocks that automatically triggers after
 * reset. Impedancecalibration may be triggered manually using INIT and
 * ZCAL bits of the PIRregister. This bit is self-clearing.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . ZCALBYP
 */
#define  VTSS_F_DDR_PHY_PIR_ZCALBYP(x)        VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_PHY_PIR_ZCALBYP           VTSS_BIT(30)
#define  VTSS_X_DDR_PHY_PIR_ZCALBYP(x)        VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Initialization Bypass: Bypasses or stops, if set, all initialization
 * routines currentlyrunning, including PHY initialization, DRAM
 * initialization, and PHY training.Initialization may be triggered
 * manually using INIT and the other relevant bits ofthe PIR register. This
 * bit is self-clearing.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PIR . INITBYP
 */
#define  VTSS_F_DDR_PHY_PIR_INITBYP(x)        VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_PHY_PIR_INITBYP           VTSS_BIT(31)
#define  VTSS_X_DDR_PHY_PIR_INITBYP(x)        VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief PHY General Configuration Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:PGCR0
 */
#define VTSS_DDR_PHY_PGCR0                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x2)

/**
 * \brief
 * Write Leveling LCDL Delay VT Compensation: Enables, if set, the VT
 * driftcompensation of the write leveling LCDL.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR0 . WLLVT
 */
#define  VTSS_F_DDR_PHY_PGCR0_WLLVT(x)        VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_PGCR0_WLLVT           VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_PGCR0_WLLVT(x)        VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Write DQ LCDL Delay VT Compensation: Enables, if set, the VT drift
 * compensationof the write DQ LCDL.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR0 . WDLVT
 */
#define  VTSS_F_DDR_PHY_PGCR0_WDLVT(x)        VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_PHY_PGCR0_WDLVT           VTSS_BIT(1)
#define  VTSS_X_DDR_PHY_PGCR0_WDLVT(x)        VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Read DQS LCDL Delay VT Compensation: Enables, if set, the VT
 * driftcompensation of the read DQS LCDL.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR0 . RDLVT
 */
#define  VTSS_F_DDR_PHY_PGCR0_RDLVT(x)        VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_PHY_PGCR0_RDLVT           VTSS_BIT(2)
#define  VTSS_X_DDR_PHY_PGCR0_RDLVT(x)        VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Read DQS Gating LCDL Delay VT Compensation: Enables, if set, the VT
 * driftcompensation of the read DQS gating LCDL.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR0 . RGLVT
 */
#define  VTSS_F_DDR_PHY_PGCR0_RGLVT(x)        VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_PHY_PGCR0_RGLVT           VTSS_BIT(3)
#define  VTSS_X_DDR_PHY_PGCR0_RGLVT(x)        VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Write Data BDL VT Compensation: Enables, if set, the VT drift
 * compensation of thewrite data bit delay lines.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR0 . WDBVT
 */
#define  VTSS_F_DDR_PHY_PGCR0_WDBVT(x)        VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_PHY_PGCR0_WDBVT           VTSS_BIT(4)
#define  VTSS_X_DDR_PHY_PGCR0_WDBVT(x)        VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Read Data BDL VT Compensation: Enables, if set, the VT drift
 * compensation of theread data bit delay lines.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR0 . RDBVT
 */
#define  VTSS_F_DDR_PHY_PGCR0_RDBVT(x)        VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_PHY_PGCR0_RDBVT           VTSS_BIT(5)
#define  VTSS_X_DDR_PHY_PGCR0_RDBVT(x)        VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Delay Line Test Mode: Selects, if set, the delay line oscillator test
 * mode.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR0 . DLTMODE
 */
#define  VTSS_F_DDR_PHY_PGCR0_DLTMODE(x)      VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DDR_PHY_PGCR0_DLTMODE         VTSS_BIT(6)
#define  VTSS_X_DDR_PHY_PGCR0_DLTMODE(x)      VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Oscillator Enable: Enables, if set, the delay line oscillation.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR0 . DLTST
 */
#define  VTSS_F_DDR_PHY_PGCR0_DLTST(x)        VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DDR_PHY_PGCR0_DLTST           VTSS_BIT(7)
#define  VTSS_X_DDR_PHY_PGCR0_DLTST(x)        VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Oscillator Enable: Enables, if set, the delay line oscillation.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR0 . OSCEN
 */
#define  VTSS_F_DDR_PHY_PGCR0_OSCEN(x)        VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DDR_PHY_PGCR0_OSCEN           VTSS_BIT(8)
#define  VTSS_X_DDR_PHY_PGCR0_OSCEN(x)        VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Oscillator Mode Division: Specifies the factor by which the delay line
 * oscillator modeoutput is divided down before it is output on the delay
 * line digital test output pindl_dto. Valid values are:000 = Divide by
 * 1001 = Divide by 256010 = Divide by 512011 = Divide by 1024100 = Divide
 * by 2048101 = Divide by 4096110 = Divide by 8192111 = Divide by 65536
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR0 . OSCDIV
 */
#define  VTSS_F_DDR_PHY_PGCR0_OSCDIV(x)       VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_DDR_PHY_PGCR0_OSCDIV          VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_DDR_PHY_PGCR0_OSCDIV(x)       VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * Oscillator Mode Write-Leveling Delay Line Select: Selects which of the
 * two writeleveling LCDLs is active. The delay select value of the
 * inactive LCDL is set to zerowhile the delay select value of the active
 * LCDL can be varied by the input writeleveling delay select pin. Valid
 * values are:00 = No WL LCDL is active01 = DDR WL LCDL is active10 = SDR
 * WL LCDL is active11 = Both LCDLs are active
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR0 . OSCWDL
 */
#define  VTSS_F_DDR_PHY_PGCR0_OSCWDL(x)       VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_DDR_PHY_PGCR0_OSCWDL          VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_DDR_PHY_PGCR0_OSCWDL(x)       VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * Digital Test Output Select: Selects the PHY digital test output that is
 * driven ontoPHY digital test output (phy_dto) pin: Valid values are:00000
 * = DATX8 0 PLL digital test output00001 = DATX8 1 PLL digital test
 * output00010 = DATX8 2 PLL digital test output00011 = DATX8 3 PLL digital
 * test output00100 = DATX8 4 PLL digital test output00101 = DATX8 5 PLL
 * digital test output00110 = DATX8 6 PLL digital test output00111 = DATX8
 * 7 PLL digital test output01000 = DATX8 8 PLL digital test output01001 =
 * AC PLL digital test output01010 - 01111 = Reserved10000 = DATX8 0 delay
 * line digital test output10001 = DATX8 1 delay line digital test
 * output10010 = DATX8 2 delay line digital test output10011 = DATX8 3
 * delay line digital test output10100 = DATX8 4 delay line digital test
 * output10101 = DATX8 5 delay line digital test output10110 = DATX8 6
 * delay line digital test output10111 = DATX8 7 delay line digital test
 * output11000 = DATX8 8 delay line digital test output11001 = AC delay
 * line digital test output11010 - 11111 = Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR0 . DTOSEL
 */
#define  VTSS_F_DDR_PHY_PGCR0_DTOSEL(x)       VTSS_ENCODE_BITFIELD(x,14,5)
#define  VTSS_M_DDR_PHY_PGCR0_DTOSEL          VTSS_ENCODE_BITMASK(14,5)
#define  VTSS_X_DDR_PHY_PGCR0_DTOSEL(x)       VTSS_EXTRACT_BITFIELD(x,14,5)

/**
 * \brief
 * Enables, if set, the PUB to control the interface to the PHY and SDRAM.
 * In thismode the DFI commands from the controller are ignored. The bit
 * must be set to 0after the system determines it is convenient to pass
 * control of the DFI bus to thecontroller. When set to 0 the DFI interface
 * has control of the PHY and SDRAMinterface except when triggering pub
 * operations such as BIST, DCU or data training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR0 . PUBMODE
 */
#define  VTSS_F_DDR_PHY_PGCR0_PUBMODE(x)      VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_DDR_PHY_PGCR0_PUBMODE         VTSS_BIT(25)
#define  VTSS_X_DDR_PHY_PGCR0_PUBMODE(x)      VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * CK Enable: Controls whether the CK going to the SDRAM is enabled
 * (toggling) ordisabled (static value) and whether the CK is inverted. Two
 * bits for each of the up tothree CK pairs. Valid values for the two bits
 * are:00 = CK disabled (Driven to constant 0)01 = CK toggling with
 * inverted polarity10 = CK toggling with normal polarity (This should be
 * the default setting)11 = CK disabled (Driven to constant 1).
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR0 . CKEN
 */
#define  VTSS_F_DDR_PHY_PGCR0_CKEN(x)         VTSS_ENCODE_BITFIELD(x,26,6)
#define  VTSS_M_DDR_PHY_PGCR0_CKEN            VTSS_ENCODE_BITMASK(26,6)
#define  VTSS_X_DDR_PHY_PGCR0_CKEN(x)         VTSS_EXTRACT_BITFIELD(x,26,6)


/**
 * \brief PHY General Configuration Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:PGCR1
 */
#define VTSS_DDR_PHY_PGCR1                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x3)

/**
 * \brief
 * PDDISDX Power Down Disabled Byte: Indicates, if set, that the PLL and
 * I/Os of a disabledbyte should be powered down.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR1 . PDDISDX
 */
#define  VTSS_F_DDR_PHY_PGCR1_PDDISDX(x)      VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_PGCR1_PDDISDX         VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_PGCR1_PDDISDX(x)      VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Write Leveling (Software) Mode: Indicates, if set, that the PUB is in
 * software writeleveling mode in which software executes single steps of
 * DQS pulsing by writing '1'to PIR.WL. The write leveling DQ status from
 * the DRAM is captured inDXnGSR0.WLDQ.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR1 . WLMODE
 */
#define  VTSS_F_DDR_PHY_PGCR1_WLMODE(x)       VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_PHY_PGCR1_WLMODE          VTSS_BIT(1)
#define  VTSS_X_DDR_PHY_PGCR1_WLMODE(x)       VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Write Leveling Step: Specifies the number of delay step-size increments
 * duringeach step of write leveling. Valid values are:0 = computed to be
 * 1/2 of the associated lane's DXnGSR0.WLPRD value1 = 1 step size
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR1 . WLSTEP
 */
#define  VTSS_F_DDR_PHY_PGCR1_WLSTEP(x)       VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_PHY_PGCR1_WLSTEP          VTSS_BIT(2)
#define  VTSS_X_DDR_PHY_PGCR1_WLSTEP(x)       VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Write System Latency Optimization: controls the insertion of a pipeline
 * stage on theAC signals from the DFI interface to the PHY to cater for a
 * negative write systemlatency (WSL) value (only -1 possible).0x0 = A
 * pipeline stage is inserted only if WL2 training results in a WSL of -1
 * for anyrank0x1 = Inserts a pipeline stage.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR1 . WSLOPT
 */
#define  VTSS_F_DDR_PHY_PGCR1_WSLOPT(x)       VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_PHY_PGCR1_WSLOPT          VTSS_BIT(4)
#define  VTSS_X_DDR_PHY_PGCR1_WSLOPT(x)       VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * AC PHY High-Speed Reset: a Write of '0' to this bit resets the AC macro
 * withoutresetting the PUB RTL logic. This bit is not self-clearing and a
 * '1' must be written todeassert the reset.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR1 . ACHRST
 */
#define  VTSS_F_DDR_PHY_PGCR1_ACHRST(x)       VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_PHY_PGCR1_ACHRST          VTSS_BIT(5)
#define  VTSS_X_DDR_PHY_PGCR1_ACHRST(x)       VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Write Leveling Select Type: Selects the encoding type for the write
 * leveling selectsignal depending on the desired setup/hold margins for
 * the internal pipelines. Referto the DDR PHY Databook for details of how
 * the select type is used. Valid valuesare:0 = Type 1: Setup margin of 90
 * degrees and hold margin of 90 degrees1 = Type 2: Setup margin of 135
 * degrees and hold margin of 45 degrees
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR1 . WLSELT
 */
#define  VTSS_F_DDR_PHY_PGCR1_WLSELT(x)       VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DDR_PHY_PGCR1_WLSELT          VTSS_BIT(6)
#define  VTSS_X_DDR_PHY_PGCR1_WLSELT(x)       VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Master Delay Line Enable: Enables, if set, the AC master delay line
 * calibration toperform subsequent period measurements following the
 * initial periodmeasurements that are performed after reset or on when
 * calibration is manuallytriggered. These additional measurements are
 * accumulated and filtered as long asthis bit remains high.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR1 . PGCR1_MDLEN
 */
#define  VTSS_F_DDR_PHY_PGCR1_PGCR1_MDLEN(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_DDR_PHY_PGCR1_PGCR1_MDLEN     VTSS_BIT(9)
#define  VTSS_X_DDR_PHY_PGCR1_PGCR1_MDLEN(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Low-Pass Filter Enable: Enables, if set, the low pass filtering of MDL
 * periodmeasurements.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR1 . LPFEN
 */
#define  VTSS_F_DDR_PHY_PGCR1_LPFEN(x)        VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_DDR_PHY_PGCR1_LPFEN           VTSS_BIT(10)
#define  VTSS_X_DDR_PHY_PGCR1_LPFEN(x)        VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Low-Pass Filter Depth: Specifies the number of measurements over which
 * MDLperiod measurements are filtered. This determines the time constant
 * of the lowpass filter. Valid values are:00 = 201 = 410 = 811 = 16
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR1 . LPFDEPTH
 */
#define  VTSS_F_DDR_PHY_PGCR1_LPFDEPTH(x)     VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_DDR_PHY_PGCR1_LPFDEPTH        VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_DDR_PHY_PGCR1_LPFDEPTH(x)     VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * Filter Depth: Specifies the number of measurements over which all AC and
 * DATX8initial period measurements, that happen after reset or when
 * calibration is manuallytriggered, are averaged. Valid values are:00 =
 * 201 = 410 = 811 = 16
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR1 . FDEPTH
 */
#define  VTSS_F_DDR_PHY_PGCR1_FDEPTH(x)       VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_DDR_PHY_PGCR1_FDEPTH          VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_DDR_PHY_PGCR1_FDEPTH(x)       VTSS_EXTRACT_BITFIELD(x,13,2)

/**
 * \brief
 * Delay Line VT Drift Limit: Specifies the minimum change in the delay
 * line VT drift inone direction which should result in the assertion of
 * the delay line VT drift statussignal (vt_drift). The limit is specified
 * in terms of delay select values. A value of 0disables the assertion of
 * delay line VT drift status signal.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR1 . DLDLMT
 */
#define  VTSS_F_DDR_PHY_PGCR1_DLDLMT(x)       VTSS_ENCODE_BITFIELD(x,15,8)
#define  VTSS_M_DDR_PHY_PGCR1_DLDLMT          VTSS_ENCODE_BITMASK(15,8)
#define  VTSS_X_DDR_PHY_PGCR1_DLDLMT(x)       VTSS_EXTRACT_BITFIELD(x,15,8)

/**
 * \brief
 * Impedance Clock Divider Select: Selects the divide ratio for the clock
 * used by theimpedance control logic relative to the clock used by the
 * memory controller andSDRAM.Valid values are:00 = Divide by 201 = Divide
 * by 810 = Divide by 3211 = Divide by 64
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR1 . ZCKSEL
 */
#define  VTSS_F_DDR_PHY_PGCR1_ZCKSEL(x)       VTSS_ENCODE_BITFIELD(x,23,2)
#define  VTSS_M_DDR_PHY_PGCR1_ZCKSEL          VTSS_ENCODE_BITMASK(23,2)
#define  VTSS_X_DDR_PHY_PGCR1_ZCKSEL(x)       VTSS_EXTRACT_BITFIELD(x,23,2)

/**
 * \brief
 * DX PHY High-Speed Reset: a Write of '0' to this bit resets the DX macro
 * withoutresetting the PUB RTL logic. This bit is not self-clearing and a
 * '1' must be written todeassert the reset.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR1 . DXHRST
 */
#define  VTSS_F_DDR_PHY_PGCR1_DXHRST(x)       VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_DDR_PHY_PGCR1_DXHRST          VTSS_BIT(25)
#define  VTSS_X_DDR_PHY_PGCR1_DXHRST(x)       VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * VT Calculation Inhibit: Inhibits calculation of the next VT compensated
 * delay linevalues. A value of 1 will inhibit the VT calculation. This bit
 * should be set to 1 duringwrites to the delay line registers.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR1 . INHVT
 */
#define  VTSS_F_DDR_PHY_PGCR1_INHVT(x)        VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_DDR_PHY_PGCR1_INHVT           VTSS_BIT(26)
#define  VTSS_X_DDR_PHY_PGCR1_INHVT(x)        VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * I/O Loopback Select: Selects where inside the I/O the loopback of
 * signalshappens. Valid values are:0 = Loopback is after output buffer;
 * output enable must be asserted1 = Loopback is before output buffer;
 * output enable is don't care
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR1 . IOLB
 */
#define  VTSS_F_DDR_PHY_PGCR1_IOLB(x)         VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_DDR_PHY_PGCR1_IOLB            VTSS_BIT(27)
#define  VTSS_X_DDR_PHY_PGCR1_IOLB(x)         VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Loopback DQS Shift: Selects how the read DQS is shifted during loopback
 * toensure that the read DQS is centered into the read data eye. Valid
 * values are:1b0 = PUB sets the read DQS LCDL to 0 (internally). DQS is
 * already shifted 90degrees by write path1b1 = The read DQS shift is set
 * manually through software
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR1 . LBDQSS
 */
#define  VTSS_F_DDR_PHY_PGCR1_LBDQSS(x)       VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_DDR_PHY_PGCR1_LBDQSS          VTSS_BIT(28)
#define  VTSS_X_DDR_PHY_PGCR1_LBDQSS(x)       VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Loopback DQS Gating: Selects the DQS gating mode that should be used
 * when thePHY is in loopback mode, including BIST loopback mode. Valid
 * values are:00 = DQS gate is always on01 = DQS gate training will be
 * triggered on the PUB10 = DQS gate is set manually using software11 =
 * Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR1 . LBGDQS
 */
#define  VTSS_F_DDR_PHY_PGCR1_LBGDQS(x)       VTSS_ENCODE_BITFIELD(x,29,2)
#define  VTSS_M_DDR_PHY_PGCR1_LBGDQS          VTSS_ENCODE_BITMASK(29,2)
#define  VTSS_X_DDR_PHY_PGCR1_LBGDQS(x)       VTSS_EXTRACT_BITFIELD(x,29,2)

/**
 * \brief
 * Loopback Mode: Indicates, if set, that the PHY/PUB is in loopback mode.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR1 . LBMODE
 */
#define  VTSS_F_DDR_PHY_PGCR1_LBMODE(x)       VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_PHY_PGCR1_LBMODE          VTSS_BIT(31)
#define  VTSS_X_DDR_PHY_PGCR1_LBMODE(x)       VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief PHY General Status Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:PGSR0
 */
#define VTSS_DDR_PHY_PGSR0                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x4)

/**
 * \brief
 * Initialization Done.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . IDONE
 */
#define  VTSS_F_DDR_PHY_PGSR0_IDONE(x)        VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_PGSR0_IDONE           VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_PGSR0_IDONE(x)        VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * PLL Lock Done.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . PLDONE
 */
#define  VTSS_F_DDR_PHY_PGSR0_PLDONE(x)       VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_PHY_PGSR0_PLDONE          VTSS_BIT(1)
#define  VTSS_X_DDR_PHY_PGSR0_PLDONE(x)       VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Digital Delay Line (DDL) Calibration Done.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . DCDONE
 */
#define  VTSS_F_DDR_PHY_PGSR0_DCDONE(x)       VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_PHY_PGSR0_DCDONE          VTSS_BIT(2)
#define  VTSS_X_DDR_PHY_PGSR0_DCDONE(x)       VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Impedance Calibration Done.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . ZCDONE
 */
#define  VTSS_F_DDR_PHY_PGSR0_ZCDONE(x)       VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_PHY_PGSR0_ZCDONE          VTSS_BIT(3)
#define  VTSS_X_DDR_PHY_PGSR0_ZCDONE(x)       VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DRAM Initialization Done.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . DIDONE
 */
#define  VTSS_F_DDR_PHY_PGSR0_DIDONE(x)       VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_PHY_PGSR0_DIDONE          VTSS_BIT(4)
#define  VTSS_X_DDR_PHY_PGSR0_DIDONE(x)       VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Write Leveling Done.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . WLDONE
 */
#define  VTSS_F_DDR_PHY_PGSR0_WLDONE(x)       VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_PHY_PGSR0_WLDONE          VTSS_BIT(5)
#define  VTSS_X_DDR_PHY_PGSR0_WLDONE(x)       VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DQS Gate Training Done.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . QSGDONE
 */
#define  VTSS_F_DDR_PHY_PGSR0_QSGDONE(x)      VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DDR_PHY_PGSR0_QSGDONE         VTSS_BIT(6)
#define  VTSS_X_DDR_PHY_PGSR0_QSGDONE(x)      VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Write Leveling Adjustment Done.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . WLADONE
 */
#define  VTSS_F_DDR_PHY_PGSR0_WLADONE(x)      VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DDR_PHY_PGSR0_WLADONE         VTSS_BIT(7)
#define  VTSS_X_DDR_PHY_PGSR0_WLADONE(x)      VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Read Bit Deskew Done.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . RDDONE
 */
#define  VTSS_F_DDR_PHY_PGSR0_RDDONE(x)       VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DDR_PHY_PGSR0_RDDONE          VTSS_BIT(8)
#define  VTSS_X_DDR_PHY_PGSR0_RDDONE(x)       VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Write Bit Deskew Done.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . WDDONE
 */
#define  VTSS_F_DDR_PHY_PGSR0_WDDONE(x)       VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_DDR_PHY_PGSR0_WDDONE          VTSS_BIT(9)
#define  VTSS_X_DDR_PHY_PGSR0_WDDONE(x)       VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Read Eye Training Done.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . REDONE
 */
#define  VTSS_F_DDR_PHY_PGSR0_REDONE(x)       VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_DDR_PHY_PGSR0_REDONE          VTSS_BIT(10)
#define  VTSS_X_DDR_PHY_PGSR0_REDONE(x)       VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Write Eye Training Done.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . WEDONE
 */
#define  VTSS_F_DDR_PHY_PGSR0_WEDONE(x)       VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_DDR_PHY_PGSR0_WEDONE          VTSS_BIT(11)
#define  VTSS_X_DDR_PHY_PGSR0_WEDONE(x)       VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Impedance Calibration Error.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . ZCERR
 */
#define  VTSS_F_DDR_PHY_PGSR0_ZCERR(x)        VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_DDR_PHY_PGSR0_ZCERR           VTSS_BIT(20)
#define  VTSS_X_DDR_PHY_PGSR0_ZCERR(x)        VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Write Leveling Error.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . WLERR
 */
#define  VTSS_F_DDR_PHY_PGSR0_WLERR(x)        VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_DDR_PHY_PGSR0_WLERR           VTSS_BIT(21)
#define  VTSS_X_DDR_PHY_PGSR0_WLERR(x)        VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * DQS Gate Training Error.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . QSGERR
 */
#define  VTSS_F_DDR_PHY_PGSR0_QSGERR(x)       VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_DDR_PHY_PGSR0_QSGERR          VTSS_BIT(22)
#define  VTSS_X_DDR_PHY_PGSR0_QSGERR(x)       VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Write Leveling Adjustment Error.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . WLAERR
 */
#define  VTSS_F_DDR_PHY_PGSR0_WLAERR(x)       VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_DDR_PHY_PGSR0_WLAERR          VTSS_BIT(23)
#define  VTSS_X_DDR_PHY_PGSR0_WLAERR(x)       VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Read Bit Deskew Error.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . RDERR
 */
#define  VTSS_F_DDR_PHY_PGSR0_RDERR(x)        VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_DDR_PHY_PGSR0_RDERR           VTSS_BIT(24)
#define  VTSS_X_DDR_PHY_PGSR0_RDERR(x)        VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Write Bit Deskew Error.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . WDERR
 */
#define  VTSS_F_DDR_PHY_PGSR0_WDERR(x)        VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_DDR_PHY_PGSR0_WDERR           VTSS_BIT(25)
#define  VTSS_X_DDR_PHY_PGSR0_WDERR(x)        VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Read Eye Training Error.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . REERR
 */
#define  VTSS_F_DDR_PHY_PGSR0_REERR(x)        VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_DDR_PHY_PGSR0_REERR           VTSS_BIT(26)
#define  VTSS_X_DDR_PHY_PGSR0_REERR(x)        VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * Write Eye Training Error.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . WEERR
 */
#define  VTSS_F_DDR_PHY_PGSR0_WEERR(x)        VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_DDR_PHY_PGSR0_WEERR           VTSS_BIT(27)
#define  VTSS_X_DDR_PHY_PGSR0_WEERR(x)        VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * PLL Lock Done per Channel: Indicates PLL locking has completed for
 * eachunderlying channel. Bit 28 represents channel 0 while bit 29
 * representschannel 1.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . PLDONE_CHN
 */
#define  VTSS_F_DDR_PHY_PGSR0_PLDONE_CHN(x)   VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_DDR_PHY_PGSR0_PLDONE_CHN      VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_DDR_PHY_PGSR0_PLDONE_CHN(x)   VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * AC PLL Lock.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR0 . APLOCK
 */
#define  VTSS_F_DDR_PHY_PGSR0_APLOCK(x)       VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_PHY_PGSR0_APLOCK          VTSS_BIT(31)
#define  VTSS_X_DDR_PHY_PGSR0_APLOCK(x)       VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief PHY General Status Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:PGSR1
 */
#define VTSS_DDR_PHY_PGSR1                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x5)

/**
 * \brief
 * Delay Line Test Done: Indicates, if set, that the PHY control block has
 * finished doingperiod measurement of the AC delay line digital test
 * output.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR1 . DLTDONE
 */
#define  VTSS_F_DDR_PHY_PGSR1_DLTDONE(x)      VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_PGSR1_DLTDONE         VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_PGSR1_DLTDONE(x)      VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Delay Line Test Code: Returns the code measured by the PHY control block
 * thatcorresponds to the period of the AC delay line digital test output.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR1 . DLTCODE
 */
#define  VTSS_F_DDR_PHY_PGSR1_DLTCODE(x)      VTSS_ENCODE_BITFIELD(x,1,24)
#define  VTSS_M_DDR_PHY_PGSR1_DLTCODE         VTSS_ENCODE_BITMASK(1,24)
#define  VTSS_X_DDR_PHY_PGSR1_DLTCODE(x)      VTSS_EXTRACT_BITFIELD(x,1,24)

/**
 * \brief
 * VT Stop: Indicates, if set, that the VT calculation logic has stopped
 * computing thenext values for the VT compensated delay line values. After
 * assertion of thePGCR1.INHVT, the VTSTOP bit should be read to ensure all
 * VT compensation logichas stopped computations before writing to the
 * delay line registers.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR1 . VTSTOP
 */
#define  VTSS_F_DDR_PHY_PGSR1_VTSTOP(x)       VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_PHY_PGSR1_VTSTOP          VTSS_BIT(30)
#define  VTSS_X_DDR_PHY_PGSR1_VTSTOP(x)       VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * RDIMM Parity Error: Indicates, if set, that there was a parity error
 * (i.e. err_out_n wassampled low) during one of the transactions to the
 * RDIMM buffer chip. This bitremains asserted until cleared by the
 * PIR.CLRSR.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGSR1 . PARERR
 */
#define  VTSS_F_DDR_PHY_PGSR1_PARERR(x)       VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_PHY_PGSR1_PARERR          VTSS_BIT(31)
#define  VTSS_X_DDR_PHY_PGSR1_PARERR(x)       VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief PLL Control Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:PLLCR
 */
#define VTSS_DDR_PHY_PLLCR                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x6)

/**
 * \brief
 * Digital Test Control: Selects various PLL digital test signals and other
 * test modesignals to be brought out via bit [1] of the PLL digital test
 * output (pll_dto[1]). Validvalues are:00 = '0' (Test output is
 * disabled)01 = PLL x1 clock (X1)10 = PLL reference (input) clock
 * (REF_CLK)11 = PLL feedback clock (FB_X1)
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PLLCR . DTC
 */
#define  VTSS_F_DDR_PHY_PLLCR_DTC(x)          VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DDR_PHY_PLLCR_DTC             VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DDR_PHY_PLLCR_DTC(x)          VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * Analog Test Control: Selects various PLL analog test signals to be
 * brought out viaPLL analog test output pin (pll_ato). Valid values
 * are:0000 = Reserved0001 = vdd_ckin0010 = vrfbf0011 = vdd_cko0100 =
 * vp_cp0101 = vpfil(vp)0110 = Reserved0111 = gd1000 = vcntrl_atb1001 =
 * vref_atb1010 = vpsf_atb1011 - 1111 = Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PLLCR . ATC
 */
#define  VTSS_F_DDR_PHY_PLLCR_ATC(x)          VTSS_ENCODE_BITFIELD(x,2,4)
#define  VTSS_M_DDR_PHY_PLLCR_ATC             VTSS_ENCODE_BITMASK(2,4)
#define  VTSS_X_DDR_PHY_PLLCR_ATC(x)          VTSS_EXTRACT_BITFIELD(x,2,4)

/**
 * \brief
 * Analog Test Enable (ATOEN): Selects the analog test signal that is
 * driven on theanalog test output pin. Otherwise the analog test output is
 * tri-stated. This allowsanalog test output pins from multiple PLLs to be
 * connected together. Valid valuesare:0000 = All PLL analog test signals
 * are tri-stated0001 = AC PLL analog test signal is driven out0010 = DATX8
 * 0 PLL analog test signal is driven out0011 = DATX8 1 PLL analog test
 * signal is driven out0100 = DATX8 2 PLL analog test signal is driven
 * out0101 = DATX8 3 PLL analog test signal is driven out0110 = DATX8 4 PLL
 * analog test signal is driven out0111 = DATX8 5 PLL analog test signal is
 * driven out1000 = DATX8 6 PLL analog test signal is driven out1001 =
 * DATX8 7 PLL analog test signal is driven out1010 = DATX8 8 PLL analog
 * test signal is driven out1011 - 1111 = Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PLLCR . ATOEN
 */
#define  VTSS_F_DDR_PHY_PLLCR_ATOEN(x)        VTSS_ENCODE_BITFIELD(x,6,4)
#define  VTSS_M_DDR_PHY_PLLCR_ATOEN           VTSS_ENCODE_BITMASK(6,4)
#define  VTSS_X_DDR_PHY_PLLCR_ATOEN(x)        VTSS_EXTRACT_BITFIELD(x,6,4)

/**
 * \brief
 * Gear Shift: Enables, if set, rapid locking mode.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PLLCR . GSHIFT
 */
#define  VTSS_F_DDR_PHY_PLLCR_GSHIFT(x)       VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_DDR_PHY_PLLCR_GSHIFT          VTSS_BIT(10)
#define  VTSS_X_DDR_PHY_PLLCR_GSHIFT(x)       VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Charge Pump Integrating Current Control.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PLLCR . CPIC
 */
#define  VTSS_F_DDR_PHY_PLLCR_CPIC(x)         VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_DDR_PHY_PLLCR_CPIC            VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_DDR_PHY_PLLCR_CPIC(x)         VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * Charge Pump Proportional Current Control.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PLLCR . CPPC
 */
#define  VTSS_F_DDR_PHY_PLLCR_CPPC(x)         VTSS_ENCODE_BITFIELD(x,13,4)
#define  VTSS_M_DDR_PHY_PLLCR_CPPC            VTSS_ENCODE_BITMASK(13,4)
#define  VTSS_X_DDR_PHY_PLLCR_CPPC(x)         VTSS_EXTRACT_BITFIELD(x,13,4)

/**
 * \brief
 * PLL Quadrature Phase Mode: Enables, if set, the quadrature phase clock
 * outputs.This mode is not used in this version of the PHY.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PLLCR . QPMODE
 */
#define  VTSS_F_DDR_PHY_PLLCR_QPMODE(x)       VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_DDR_PHY_PLLCR_QPMODE          VTSS_BIT(17)
#define  VTSS_X_DDR_PHY_PLLCR_QPMODE(x)       VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * PLL Frequency Select: Selects the operating range of the PLL.Valid
 * values for PHYs that go up to 2133 Mbps are:00 = PLL reference clock
 * (ctl_clk/REF_CLK) ranges from 335MHz to 533MHz01 = PLL reference clock
 * (ctl_clk/REF_CLK) ranges from 225MHz to 385MHz10 = Reserved11 = PLL
 * reference clock (ctl_clk/REF_CLK) ranges from 166MHz to 275MHzValid
 * values for PHYs that don't go up to 2133 Mbps are:00 = PLL reference
 * clock (ctl_clk/REF_CLK) ranges from 250MHz to 400MHz01 = PLL reference
 * clock (ctl_clk/REF_CLK) ranges from 166MHz to 300MHz10 = Reserved11 =
 * Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PLLCR . FRQSEL
 */
#define  VTSS_F_DDR_PHY_PLLCR_FRQSEL(x)       VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_DDR_PHY_PLLCR_FRQSEL          VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_DDR_PHY_PLLCR_FRQSEL(x)       VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * PLL Power Down: Puts the PLLs in power down mode by driving the PLL
 * powerdown pin. This bit is not self-clearing and a '0' must be written
 * to deassert thepower-down.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PLLCR . PLLCR_PLLPD
 */
#define  VTSS_F_DDR_PHY_PLLCR_PLLCR_PLLPD(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_DDR_PHY_PLLCR_PLLCR_PLLPD     VTSS_BIT(29)
#define  VTSS_X_DDR_PHY_PLLCR_PLLCR_PLLPD(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * PLL Rest: Resets the PLLs by driving the PLL reset pin. This bit is not
 * self-clearingand a '0' must be written to deassert the reset.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PLLCR . PLLCR_PLLRST
 */
#define  VTSS_F_DDR_PHY_PLLCR_PLLCR_PLLRST(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_PHY_PLLCR_PLLCR_PLLRST    VTSS_BIT(30)
#define  VTSS_X_DDR_PHY_PLLCR_PLLCR_PLLRST(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * PLL Bypass: Bypasses the PLL, if set, to 1.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PLLCR . PLLCR_PLLBYP
 */
#define  VTSS_F_DDR_PHY_PLLCR_PLLCR_PLLBYP(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_PHY_PLLCR_PLLCR_PLLBYP    VTSS_BIT(31)
#define  VTSS_X_DDR_PHY_PLLCR_PLLCR_PLLBYP(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief PHY Timing Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:PTR0
 */
#define VTSS_DDR_PHY_PTR0                    VTSS_IOREG(VTSS_TO_DDR_PHY,0x7)

/**
 * \brief
 * PHY Reset Time: Number of configuration or APB clock cycles that the PHY
 * resetmust remain asserted after PHY calibration is done before the reset
 * to the PHY isdeasserted. This is used to extend the reset to the PHY so
 * that the reset isasserted for some clock cycles after the clocks are
 * stable. Valid values are from 1 to63 (the value must be non-zero).
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PTR0 . TPHYRST
 */
#define  VTSS_F_DDR_PHY_PTR0_TPHYRST(x)       VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_PHY_PTR0_TPHYRST          VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_PHY_PTR0_TPHYRST(x)       VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * PLL Gear Shift Time: Number of configuration or APB clock cycles from
 * when thePLL reset pin is deasserted to when the PLL gear shift pin is
 * deasserted. Thismust correspond to a value that is equal to or more than
 * 4us. Default valuecorresponds to 4us.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PTR0 . TPLLGS
 */
#define  VTSS_F_DDR_PHY_PTR0_TPLLGS(x)        VTSS_ENCODE_BITFIELD(x,6,15)
#define  VTSS_M_DDR_PHY_PTR0_TPLLGS           VTSS_ENCODE_BITMASK(6,15)
#define  VTSS_X_DDR_PHY_PTR0_TPLLGS(x)        VTSS_EXTRACT_BITFIELD(x,6,15)

/**
 * \brief
 * PLL Power-Down Time: Number of configuration or APB clock cycles that
 * the PLLmust remain in power-down mode, i.e. number of clock cycles from
 * when PLLpower-down pin is asserted to when PLL power-down pin is
 * deasserted. This mustcorrespond to a value that is equal to or more than
 * 1us. Default value correspondsto 1us.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PTR0 . TPLLPD
 */
#define  VTSS_F_DDR_PHY_PTR0_TPLLPD(x)        VTSS_ENCODE_BITFIELD(x,21,11)
#define  VTSS_M_DDR_PHY_PTR0_TPLLPD           VTSS_ENCODE_BITMASK(21,11)
#define  VTSS_X_DDR_PHY_PTR0_TPLLPD(x)        VTSS_EXTRACT_BITFIELD(x,21,11)


/**
 * \brief PHY Timing Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:PTR1
 */
#define VTSS_DDR_PHY_PTR1                    VTSS_IOREG(VTSS_TO_DDR_PHY,0x8)

/**
 * \brief
 * PLL Reset Time: Number of configuration or APB clock cycles that the PLL
 * mustremain in reset mode, i.e. number of clock cycles from when PLL
 * power-down pin isdeasserted and PLL reset pin is asserted to when PLL
 * reset pin is deasserted.The setting must correspond to a value that is
 * equal to, or greater than, 3us.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PTR1 . TPLLRST
 */
#define  VTSS_F_DDR_PHY_PTR1_TPLLRST(x)       VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_DDR_PHY_PTR1_TPLLRST          VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_DDR_PHY_PTR1_TPLLRST(x)       VTSS_EXTRACT_BITFIELD(x,0,13)

/**
 * \brief
 * PLL Lock Time: Number of configuration or APB clock cycles for the PLL
 * to stabilizeand lock, i.e. number of clock cycles from when the PLL
 * reset pin is deasserted towhen the PLL has lock and is ready for use.
 * This must correspond to a value that isequal to or more than 100us.
 * Default value corresponds to 100us.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PTR1 . TPLLLOCK
 */
#define  VTSS_F_DDR_PHY_PTR1_TPLLLOCK(x)      VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DDR_PHY_PTR1_TPLLLOCK         VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DDR_PHY_PTR1_TPLLLOCK(x)      VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief PHY Timing Register 2
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:PTR2
 */
#define VTSS_DDR_PHY_PTR2                    VTSS_IOREG(VTSS_TO_DDR_PHY,0x9)

/**
 * \brief
 * Calibration On Time: Number of clock cycles that the calibration clock
 * is enabled(cal_clk_en asserted).
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PTR2 . TCALON
 */
#define  VTSS_F_DDR_PHY_PTR2_TCALON(x)        VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_PHY_PTR2_TCALON           VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_PHY_PTR2_TCALON(x)        VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * Calibration Setup Time: Number of controller clock cycles from when
 * calibration isenabled (cal_en asserted) to when the calibration clock is
 * asserted again(cal_clk_en asserted).
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PTR2 . TCALS
 */
#define  VTSS_F_DDR_PHY_PTR2_TCALS(x)         VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_DDR_PHY_PTR2_TCALS            VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_DDR_PHY_PTR2_TCALS(x)         VTSS_EXTRACT_BITFIELD(x,5,5)

/**
 * \brief
 * Calibration Hold Time: Number of controller clock cycles from when the
 * clock wasdisabled (cal_clk_en deasserted) to when calibration is enable
 * (cal_en asserted).
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PTR2 . TCALH
 */
#define  VTSS_F_DDR_PHY_PTR2_TCALH(x)         VTSS_ENCODE_BITFIELD(x,10,5)
#define  VTSS_M_DDR_PHY_PTR2_TCALH            VTSS_ENCODE_BITMASK(10,5)
#define  VTSS_X_DDR_PHY_PTR2_TCALH(x)         VTSS_EXTRACT_BITFIELD(x,10,5)

/**
 * \brief
 * Write Leveling Delay Settling Time: Number of controller clock cycles
 * from when anew value of the write leveling delay is applies to the LCDL
 * to when to DQS high isdriven high. This allows the delay to settle.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PTR2 . TWLDLYS
 */
#define  VTSS_F_DDR_PHY_PTR2_TWLDLYS(x)       VTSS_ENCODE_BITFIELD(x,15,5)
#define  VTSS_M_DDR_PHY_PTR2_TWLDLYS          VTSS_ENCODE_BITMASK(15,5)
#define  VTSS_X_DDR_PHY_PTR2_TWLDLYS(x)       VTSS_EXTRACT_BITFIELD(x,15,5)


/**
 * \brief PHY Timing Register 3
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:PTR3
 */
#define VTSS_DDR_PHY_PTR3                    VTSS_IOREG(VTSS_TO_DDR_PHY,0xa)

/**
 * \brief
 * DRAM Initialization Time 0: DRAM initialization time in DRAM clock
 * cyclescorresponding to the following:DDR3 = CKE low time with power and
 * clock stable (500 us)DDR2 = CKE low time with power and clock stable
 * (200 us)Default value corresponds to DDR3 500 us at 1066 MHz.During
 * Verilog simulations, it is recommended that this value is changed to a
 * muchsmaller value in order to avoid long simulation times. However, this
 * may cause amemory model error, due to a violation of the CKE setup
 * sequence. This violation isexpected if this value is not programmed to
 * the required SDRAM CKE low time, butmemory models should be able to
 * tolerate this violation without malfunction of themodel.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PTR3 . TDINIT0
 */
#define  VTSS_F_DDR_PHY_PTR3_TDINIT0(x)       VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_DDR_PHY_PTR3_TDINIT0          VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_DDR_PHY_PTR3_TDINIT0(x)       VTSS_EXTRACT_BITFIELD(x,0,20)

/**
 * \brief
 * DRAM Initialization Time 1: DRAM initialization time in DRAM clock
 * cyclescorresponding to the following:DDR3 = CKE high time to first
 * command (tRFC + 10 ns or 5 tCK, whichever is bigger)DDR2 = CKE high time
 * to first command (400 ns)Default value corresponds to DDR3 tRFC of 360ns
 * at 1066 MHz.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PTR3 . TDINIT1
 */
#define  VTSS_F_DDR_PHY_PTR3_TDINIT1(x)       VTSS_ENCODE_BITFIELD(x,20,10)
#define  VTSS_M_DDR_PHY_PTR3_TDINIT1          VTSS_ENCODE_BITMASK(20,10)
#define  VTSS_X_DDR_PHY_PTR3_TDINIT1(x)       VTSS_EXTRACT_BITFIELD(x,20,10)


/**
 * \brief PHY Timing Register 4
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:PTR4
 */
#define VTSS_DDR_PHY_PTR4                    VTSS_IOREG(VTSS_TO_DDR_PHY,0xb)

/**
 * \brief
 * DRAM Initialization Time 2: DRAM initialization time in DRAM clock
 * cyclescorresponding to the following:DDR3 = Reset low time (200 us on
 * power-up or 100 ns after power-up)Default value corresponds to DDR3 200
 * us at 1066 MHz.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PTR4 . TDINIT2
 */
#define  VTSS_F_DDR_PHY_PTR4_TDINIT2(x)       VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_DDR_PHY_PTR4_TDINIT2          VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_DDR_PHY_PTR4_TDINIT2(x)       VTSS_EXTRACT_BITFIELD(x,0,18)

/**
 * \brief
 * DRAM Initialization Time 3: DRAM initialization time in DRAM clock
 * cyclescorresponding to the following:DDR3 = Time from ZQ initialization
 * command to first command (1 us)Default value corresponds to the DDR3
 * 640ns at 1066 MHz.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PTR4 . TDINIT3
 */
#define  VTSS_F_DDR_PHY_PTR4_TDINIT3(x)       VTSS_ENCODE_BITFIELD(x,18,10)
#define  VTSS_M_DDR_PHY_PTR4_TDINIT3          VTSS_ENCODE_BITMASK(18,10)
#define  VTSS_X_DDR_PHY_PTR4_TDINIT3(x)       VTSS_EXTRACT_BITFIELD(x,18,10)


/**
 * \brief AC Master Delay Line Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:ACMDLR
 */
#define VTSS_DDR_PHY_ACMDLR                  VTSS_IOREG(VTSS_TO_DDR_PHY,0xc)

/**
 * \brief
 * Initial Period: Initial period measured by the master delay line
 * calibration for VT driftcompensation. This value is used as the
 * denominator when calculating the ratios ofupdates during VT
 * compensation.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACMDLR . IPRD
 */
#define  VTSS_F_DDR_PHY_ACMDLR_IPRD(x)        VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_PHY_ACMDLR_IPRD           VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_PHY_ACMDLR_IPRD(x)        VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Target Period: Target period measured by the master delay line
 * calibration for VTdrift compensation. This is the current measured value
 * of the period and iscontinuously updated if the MDL is enabled to do so.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACMDLR . TPRD
 */
#define  VTSS_F_DDR_PHY_ACMDLR_TPRD(x)        VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DDR_PHY_ACMDLR_TPRD           VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DDR_PHY_ACMDLR_TPRD(x)        VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * MDL Delay: Delay select for the LCDL for the Master Delay Line.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACMDLR . MDLD
 */
#define  VTSS_F_DDR_PHY_ACMDLR_MDLD(x)        VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_PHY_ACMDLR_MDLD           VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_PHY_ACMDLR_MDLD(x)        VTSS_EXTRACT_BITFIELD(x,16,8)


/**
 * \brief AC Bit Delay Line Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:ACBDLR
 */
#define VTSS_DDR_PHY_ACBDLR                  VTSS_IOREG(VTSS_TO_DDR_PHY,0xd)

/**
 * \brief
 * CK0 Bit Delay: Delay select for the BDL on CK0.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACBDLR . CK0BD
 */
#define  VTSS_F_DDR_PHY_ACBDLR_CK0BD(x)       VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_PHY_ACBDLR_CK0BD          VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_PHY_ACBDLR_CK0BD(x)       VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * CK1 Bit Delay: Delay select for the BDL on CK1.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACBDLR . CK1BD
 */
#define  VTSS_F_DDR_PHY_ACBDLR_CK1BD(x)       VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_DDR_PHY_ACBDLR_CK1BD          VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_DDR_PHY_ACBDLR_CK1BD(x)       VTSS_EXTRACT_BITFIELD(x,6,6)

/**
 * \brief
 * CK2 Bit Delay: Delay select for the BDL on CK2.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACBDLR . CK2BD
 */
#define  VTSS_F_DDR_PHY_ACBDLR_CK2BD(x)       VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_DDR_PHY_ACBDLR_CK2BD          VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_DDR_PHY_ACBDLR_CK2BD(x)       VTSS_EXTRACT_BITFIELD(x,12,6)

/**
 * \brief
 * Address/Command Bit Delay: Delay select for the BDLs on address and
 * commandsignals.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACBDLR . ACBD
 */
#define  VTSS_F_DDR_PHY_ACBDLR_ACBD(x)        VTSS_ENCODE_BITFIELD(x,18,6)
#define  VTSS_M_DDR_PHY_ACBDLR_ACBD           VTSS_ENCODE_BITMASK(18,6)
#define  VTSS_X_DDR_PHY_ACBDLR_ACBD(x)        VTSS_EXTRACT_BITFIELD(x,18,6)


/**
 * \brief AC I/O Configuration Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:ACIOCR
 */
#define VTSS_DDR_PHY_ACIOCR                  VTSS_IOREG(VTSS_TO_DDR_PHY,0xe)

/**
 * \brief
 * Address/Command I/O Mode: Selects SSTL mode (when set to 0) or CMOS
 * mode(when set to 1) of the I/O for all address and command pins. This
 * bit connects to bit[0] of the IOM pin on the D3F I/Os, and for other I/O
 * libraries, it connects to the IOMpin of the I/O.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACIOCR . ACIOM
 */
#define  VTSS_F_DDR_PHY_ACIOCR_ACIOM(x)       VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_ACIOCR_ACIOM          VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_ACIOCR_ACIOM(x)       VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Address/Command Output Enable: Enables, when set, the output driver on
 * the I/Ofor all address and command pins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACIOCR . AC0E
 */
#define  VTSS_F_DDR_PHY_ACIOCR_AC0E(x)        VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_PHY_ACIOCR_AC0E           VTSS_BIT(1)
#define  VTSS_X_DDR_PHY_ACIOCR_AC0E(x)        VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Address/Command On-Die Termination: Enables, when set, the on-die
 * terminationon the I/O for RAS#, CAS#, WE#, BA[2:0], and A[15:0] pins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACIOCR . ACODT
 */
#define  VTSS_F_DDR_PHY_ACIOCR_ACODT(x)       VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_PHY_ACIOCR_ACODT          VTSS_BIT(2)
#define  VTSS_X_DDR_PHY_ACIOCR_ACODT(x)       VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * AC Power Down Driver: Powers down, when set, the output driver on the
 * I/O forRAS#, CAS#, WE#, BA[2:0], and A[15:0] pins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACIOCR . ACPDD
 */
#define  VTSS_F_DDR_PHY_ACIOCR_ACPDD(x)       VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_PHY_ACIOCR_ACPDD          VTSS_BIT(3)
#define  VTSS_X_DDR_PHY_ACIOCR_ACPDD(x)       VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * AC Power Down Receiver: Powers down, when set, the input receiver on the
 * I/O forRAS#, CAS#, WE#, BA[2:0], and A[15:0] pins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACIOCR . ACPDR
 */
#define  VTSS_F_DDR_PHY_ACIOCR_ACPDR(x)       VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_PHY_ACIOCR_ACPDR          VTSS_BIT(4)
#define  VTSS_X_DDR_PHY_ACIOCR_ACPDR(x)       VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * CK On-Die Termination: Enables, when set, the on-die termination on the
 * I/O forCK[0], CK[1], and CK[2] pins, respectively.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACIOCR . CKODT
 */
#define  VTSS_F_DDR_PHY_ACIOCR_CKODT(x)       VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_DDR_PHY_ACIOCR_CKODT          VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_DDR_PHY_ACIOCR_CKODT(x)       VTSS_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * CK Power Down Driver: Powers down, when set, the output driver on the
 * I/O forCK[0], CK[1], and CK[2] pins, respectively.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACIOCR . CKPDD
 */
#define  VTSS_F_DDR_PHY_ACIOCR_CKPDD(x)       VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_DDR_PHY_ACIOCR_CKPDD          VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_DDR_PHY_ACIOCR_CKPDD(x)       VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * CK Power Down Receiver: Powers down, when set, the input receiver on the
 * I/O forCK[0], CK[1], and CK[2] pins, respectively.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACIOCR . CKPDR
 */
#define  VTSS_F_DDR_PHY_ACIOCR_CKPDR(x)       VTSS_ENCODE_BITFIELD(x,11,3)
#define  VTSS_M_DDR_PHY_ACIOCR_CKPDR          VTSS_ENCODE_BITMASK(11,3)
#define  VTSS_X_DDR_PHY_ACIOCR_CKPDR(x)       VTSS_EXTRACT_BITFIELD(x,11,3)

/**
 * \brief
 * Rank On-Die Termination: Enables, when set, the on-die termination on
 * the I/O forCKE[3:0], ODT[3:0], and CS#[3:0] pins. RANKODT[0] controls
 * the on-dietermination for CKE[0], ODT[0], and CS#[0], RANKODT[1]
 * controls the on-dietermination for CKE[1], ODT[1], and CS#[1], and so
 * on.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACIOCR . RANKODT
 */
#define  VTSS_F_DDR_PHY_ACIOCR_RANKODT(x)     VTSS_ENCODE_BITFIELD(x,14,4)
#define  VTSS_M_DDR_PHY_ACIOCR_RANKODT        VTSS_ENCODE_BITMASK(14,4)
#define  VTSS_X_DDR_PHY_ACIOCR_RANKODT(x)     VTSS_EXTRACT_BITFIELD(x,14,4)

/**
 * \brief
 * CS# Power Down Driver: Powers down, when set, the output driver on the
 * I/O forCS#[3:0] pins. CSPDD[0] controls the power down for CS#[0],
 * CSPDD[1] controlsthe power down for CS#[1], and so on. CKE and ODT
 * driver power down iscontrolled by DSGCR register.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACIOCR . CSPDD
 */
#define  VTSS_F_DDR_PHY_ACIOCR_CSPDD(x)       VTSS_ENCODE_BITFIELD(x,18,4)
#define  VTSS_M_DDR_PHY_ACIOCR_CSPDD          VTSS_ENCODE_BITMASK(18,4)
#define  VTSS_X_DDR_PHY_ACIOCR_CSPDD(x)       VTSS_EXTRACT_BITFIELD(x,18,4)

/**
 * \brief
 * Rank Power Down Receiver: Powers down, when set, the input receiver on
 * the I/OCKE[3:0], ODT[3:0], and CS#[3:0] pins. RANKPDR[0] controls the
 * power down forCKE[0], ODT[0], and CS#[0], RANKPDR[1] controls the power
 * down for CKE[1],ODT[1], and CS#[1], and so on.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACIOCR . RANKPDR
 */
#define  VTSS_F_DDR_PHY_ACIOCR_RANKPDR(x)     VTSS_ENCODE_BITFIELD(x,22,4)
#define  VTSS_M_DDR_PHY_ACIOCR_RANKPDR        VTSS_ENCODE_BITMASK(22,4)
#define  VTSS_X_DDR_PHY_ACIOCR_RANKPDR(x)     VTSS_EXTRACT_BITFIELD(x,22,4)

/**
 * \brief
 * SDRAM Reset On-Die Termination: Enables, when set, the on-die
 * termination onthe I/O for SDRAM RST# pin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACIOCR . RSTODT
 */
#define  VTSS_F_DDR_PHY_ACIOCR_RSTODT(x)      VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_DDR_PHY_ACIOCR_RSTODT         VTSS_BIT(26)
#define  VTSS_X_DDR_PHY_ACIOCR_RSTODT(x)      VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * SDRAM Reset Power Down Driver: Powers down, when set, the output driver
 * on theI/O for SDRAM RST# pin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACIOCR . RSTPDD
 */
#define  VTSS_F_DDR_PHY_ACIOCR_RSTPDD(x)      VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_DDR_PHY_ACIOCR_RSTPDD         VTSS_BIT(27)
#define  VTSS_X_DDR_PHY_ACIOCR_RSTPDD(x)      VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * SDRAM Reset Power Down Receiver: Powers down, when set, the input
 * receiveron the I/O for SDRAM RST# pin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACIOCR . RSTPDR
 */
#define  VTSS_F_DDR_PHY_ACIOCR_RSTPDR(x)      VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_DDR_PHY_ACIOCR_RSTPDR         VTSS_BIT(28)
#define  VTSS_X_DDR_PHY_ACIOCR_RSTPDR(x)      VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * SDRAM Reset I/O Mode: Selects SSTL mode (when set to 0) or CMOS
 * mode(when set to 1) of the I/O for SDRAM Reset.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ACIOCR . RSTIOM
 */
#define  VTSS_F_DDR_PHY_ACIOCR_RSTIOM(x)      VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_DDR_PHY_ACIOCR_RSTIOM         VTSS_BIT(29)
#define  VTSS_X_DDR_PHY_ACIOCR_RSTIOM(x)      VTSS_EXTRACT_BITFIELD(x,29,1)


/**
 * \brief DATX8 Common Configuration Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DXCCR
 */
#define VTSS_DDR_PHY_DXCCR                   VTSS_IOREG(VTSS_TO_DDR_PHY,0xf)

/**
 * \brief
 * Data On-Die Termination: Enables, when set, the on-die termination on
 * the I/O forDQ, DM, and DQS/DQS# pins of all DATX8 macros. This bit is
 * ORed with the ODTconfiguration bit of the individual DATX8 ("DATX8
 * General Configuration Register(DXnGCR)"
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DXCCR . DXODT
 */
#define  VTSS_F_DDR_PHY_DXCCR_DXODT(x)        VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_DXCCR_DXODT           VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_DXCCR_DXODT(x)        VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Data I/O Mode: Selects SSTL mode (when set to 0) or CMOS mode (when set
 * to1) of the I/O for DQ, DM, and DQS/DQS# pins of all DATX8 macros. This
 * bit isORed with the IOM configuration bit of the individual DATX8.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DXCCR . DXIOM
 */
#define  VTSS_F_DDR_PHY_DXCCR_DXIOM(x)        VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_PHY_DXCCR_DXIOM           VTSS_BIT(1)
#define  VTSS_X_DDR_PHY_DXCCR_DXIOM(x)        VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Master Delay Line Enable: Enables, if set, all DATX8 master delay line
 * calibrationto perform subsequent period measurements following the
 * initial periodmeasurements that are performed after reset or on when
 * calibration is manuallytriggered. These additional measurements are
 * accumulated and filtered as long asthis bit remains high. This bit is
 * ANDed with the MDLEN bit in the individual DATX8.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DXCCR . DXCCR_MDLEN
 */
#define  VTSS_F_DDR_PHY_DXCCR_DXCCR_MDLEN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_PHY_DXCCR_DXCCR_MDLEN     VTSS_BIT(2)
#define  VTSS_X_DDR_PHY_DXCCR_DXCCR_MDLEN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Data Power Down Driver: Powers down, when set, the output driver on I/O
 * for DQ,DM, and DQS/DQS# pins of all DATX8 macros. This bit is ORed with
 * the PDDconfiguration bit of the individual DATX8.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DXCCR . DXPDD
 */
#define  VTSS_F_DDR_PHY_DXCCR_DXPDD(x)        VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_PHY_DXCCR_DXPDD           VTSS_BIT(3)
#define  VTSS_X_DDR_PHY_DXCCR_DXPDD(x)        VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Data Power Down Receiver: Powers down, when set, the input receiver on
 * I/O forDQ, DM, and DQS/DQS# pins of all DATX8 macros. This bit is ORed
 * with the PDRconfiguration bit of the individual DATX8.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DXCCR . DXPDR
 */
#define  VTSS_F_DDR_PHY_DXCCR_DXPDR(x)        VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_PHY_DXCCR_DXPDR           VTSS_BIT(4)
#define  VTSS_X_DDR_PHY_DXCCR_DXPDR(x)        VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * DQS Resistor: Selects the on-die pull-down/pull-up resistor for DQS
 * pins.DQSRES[3] selects pull-down (when set to 0) or pull-up (when set to
 * 1).DQSRES[2:0] selects the resistor value.Refer PHY databook for
 * pull-down/pull-up resistor values (RA_SEL/RB_SEL) forDQS/DQS_b.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DXCCR . DQSRES
 */
#define  VTSS_F_DDR_PHY_DXCCR_DQSRES(x)       VTSS_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_DDR_PHY_DXCCR_DQSRES          VTSS_ENCODE_BITMASK(5,4)
#define  VTSS_X_DDR_PHY_DXCCR_DQSRES(x)       VTSS_EXTRACT_BITFIELD(x,5,4)

/**
 * \brief
 * DQS Resistor: Selects the on-die pull-down/pull-up resistor for DQS
 * pins.DQSRES[3] selects pull-down (when set to 0) or pull-up (when set to
 * 1).DQSRES[2:0] selects the resistor value.Refer PHY databook for
 * pull-down/pull-up resistor values (RA_SEL/RB_SEL) forDQS/DQS_b.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DXCCR . DQSNRES
 */
#define  VTSS_F_DDR_PHY_DXCCR_DQSNRES(x)      VTSS_ENCODE_BITFIELD(x,9,4)
#define  VTSS_M_DDR_PHY_DXCCR_DQSNRES         VTSS_ENCODE_BITMASK(9,4)
#define  VTSS_X_DDR_PHY_DXCCR_DQSNRES(x)      VTSS_EXTRACT_BITFIELD(x,9,4)

/**
 * \brief
 * Most Significant Byte Unused DQs: Specifies the number of DQ bits that
 * are notused in the most significant byte. The used (valid) bits for this
 * byte are [8-MSBDQ-1:0]. To disable the whole byte, use the DXnGCR.DXEN
 * register.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DXCCR . MSBUDQ
 */
#define  VTSS_F_DDR_PHY_DXCCR_MSBUDQ(x)       VTSS_ENCODE_BITFIELD(x,15,3)
#define  VTSS_M_DDR_PHY_DXCCR_MSBUDQ          VTSS_ENCODE_BITMASK(15,3)
#define  VTSS_X_DDR_PHY_DXCCR_MSBUDQ(x)       VTSS_EXTRACT_BITFIELD(x,15,3)

/**
 * \brief
 * Unused DQ On-Die Termination: Enables, when set, the on-die termination
 * on theI/O for unused DQ pins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DXCCR . UDQODT
 */
#define  VTSS_F_DDR_PHY_DXCCR_UDQODT(x)       VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_DDR_PHY_DXCCR_UDQODT          VTSS_BIT(18)
#define  VTSS_X_DDR_PHY_DXCCR_UDQODT(x)       VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Unused DQ Power Down Driver: Powers down, when set, the output driver on
 * theI/O for unused DQ pins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DXCCR . UDQPDD
 */
#define  VTSS_F_DDR_PHY_DXCCR_UDQPDD(x)       VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_DDR_PHY_DXCCR_UDQPDD          VTSS_BIT(19)
#define  VTSS_X_DDR_PHY_DXCCR_UDQPDD(x)       VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Unused DQ Power Down Receiver: Powers down, when set, the input receiver
 * onthe I/O for unused DQ pins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DXCCR . UDQPDR
 */
#define  VTSS_F_DDR_PHY_DXCCR_UDQPDR(x)       VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_DDR_PHY_DXCCR_UDQPDR          VTSS_BIT(20)
#define  VTSS_X_DDR_PHY_DXCCR_UDQPDR(x)       VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Unused DQ I/O Mode: Selects SSTL mode (when set to 0) or CMOS mode
 * (whenset to 1) of the I/O for unused DQ pins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DXCCR . UDQIOM
 */
#define  VTSS_F_DDR_PHY_DXCCR_UDQIOM(x)       VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_DDR_PHY_DXCCR_UDQIOM          VTSS_BIT(21)
#define  VTSS_X_DDR_PHY_DXCCR_UDQIOM(x)       VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Dynamic Data Power Down Driver: Dynamically powers down, when set, the
 * outputdriver on I/O for the DQ pins of the active DATX8 macros. Applies
 * only whenDXPDD and DXnGCR.DXPDD are not set to 1. Driver is powered-up
 * on a DFIWRITE command and powered-down (twrlat + WL/2 + n) HDR cycles
 * after the lastDFI WRITE command. Note that n is defined by the register
 * bit fieldDXCCR[27:24] (DDPDDCDO).
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DXCCR . DYNDXPDD
 */
#define  VTSS_F_DDR_PHY_DXCCR_DYNDXPDD(x)     VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_DDR_PHY_DXCCR_DYNDXPDD        VTSS_BIT(22)
#define  VTSS_X_DDR_PHY_DXCCR_DYNDXPDD(x)     VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Data Power Down Receiver: Dynamically powers down, when set, the
 * inputreceiver on I/O for the DQ pins of the active DATX8 macros. Applies
 * only whenDXPDR and DXnGCR.DXPDR are not set to 1. Receiver is powered-up
 * on a DFIREAD command and powered-down (trddata_en + fixed_read_latency +
 * n) HDRcycles after the last DFI READ command. Note that n is defined by
 * the register bitfield DXCCR[31:28] (DDPDRCDO).
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DXCCR . DYNDXPDR
 */
#define  VTSS_F_DDR_PHY_DXCCR_DYNDXPDR(x)     VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_DDR_PHY_DXCCR_DYNDXPDR        VTSS_BIT(23)
#define  VTSS_X_DDR_PHY_DXCCR_DYNDXPDR(x)     VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Dynamic Data Power Down Driver Count Down Offset: Offset applied in
 * calculatingwindow of time where driver is powered up
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DXCCR . DDPDDCDO
 */
#define  VTSS_F_DDR_PHY_DXCCR_DDPDDCDO(x)     VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_PHY_DXCCR_DDPDDCDO        VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_PHY_DXCCR_DDPDDCDO(x)     VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * Dynamic Data Power Down Receiver Count Down Offset: Offset applied
 * incalculating window of time where receiver is powered up
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DXCCR . DDPDRCDO
 */
#define  VTSS_F_DDR_PHY_DXCCR_DDPDRCDO(x)     VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_DDR_PHY_DXCCR_DDPDRCDO        VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_DDR_PHY_DXCCR_DDPDRCDO(x)     VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief DDR System General Configuration Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DSGCR
 */
#define VTSS_DDR_PHY_DSGCR                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x10)

/**
 * \brief
 * PHY Update Request Enable: Specifies if set, that the PHY should issue
 * PHYinitiatedupdate request when there is DDL VT drift.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . PUREN
 */
#define  VTSS_F_DDR_PHY_DSGCR_PUREN(x)        VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_DSGCR_PUREN           VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_DSGCR_PUREN(x)        VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Byte Disable Enable: Specifies, if set, that the PHY should respond to
 * DFI bytedisable request. Otherwise the byte disable from the DFI is
 * ignored in which casebytes can only be disabled using the DXnGCR
 * register.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . BDISEN
 */
#define  VTSS_F_DDR_PHY_DSGCR_BDISEN(x)       VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_PHY_DSGCR_BDISEN          VTSS_BIT(1)
#define  VTSS_X_DDR_PHY_DSGCR_BDISEN(x)       VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Impedance Update Enable: Specifies, if set, that in addition to DDL VT
 * update, thePHY could also perform impedance calibration (update).Refer
 * to the "Impedance Control Register 0-1 (ZQnCR0-1)"  bit fields DFICU0,
 * DFICU1 and DFICCU bits to control if an impedance calibration is
 * performed (update) with a DFI controller update request.Refer to the
 * "Impedance Control Register 0-1 (ZQnCR0-1)" bit fields DFIPU0 and DFIPU1
 * bits to control if an impedance calibration is performed (update) with a
 * DFI PHY update request.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . ZUEN
 */
#define  VTSS_F_DDR_PHY_DSGCR_ZUEN(x)         VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_PHY_DSGCR_ZUEN            VTSS_BIT(2)
#define  VTSS_X_DDR_PHY_DSGCR_ZUEN(x)         VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Low Power I/O Power Down: Specifies, if set, that the PHY should respond
 * to theDFI low power opportunity request and power down the I/Os of the
 * byte.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . LPIOPD
 */
#define  VTSS_F_DDR_PHY_DSGCR_LPIOPD(x)       VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_PHY_DSGCR_LPIOPD          VTSS_BIT(3)
#define  VTSS_X_DDR_PHY_DSGCR_LPIOPD(x)       VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Low Power PLL Power Down: Specifies, if set, that the PHY should respond
 * to theDFI low power opportunity request and power down the PLL of the
 * byte if thewakeup time request satisfies the PLL lock time.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . LPPLLPD
 */
#define  VTSS_F_DDR_PHY_DSGCR_LPPLLPD(x)      VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_PHY_DSGCR_LPPLLPD         VTSS_BIT(4)
#define  VTSS_X_DDR_PHY_DSGCR_LPPLLPD(x)      VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Controller Update Acknowledge Enable: Specifies, if set, that the PHY
 * should issuecontroller update acknowledge when the DFI controller update
 * request is asserted.By default the PHY does not acknowledge controller
 * initiated update requests butsimply does an update whenever there is a
 * controller update request. This speedsup the update.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . CUAEN
 */
#define  VTSS_F_DDR_PHY_DSGCR_CUAEN(x)        VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_PHY_DSGCR_CUAEN           VTSS_BIT(5)
#define  VTSS_X_DDR_PHY_DSGCR_CUAEN(x)        VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DQS Gate Extension: Specifies, if set, that the DQS gating must be
 * extended by twoDRAM clock cycles and then re-centered, i.e. one clock
 * cycle extension on eitherside.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . DQSGX
 */
#define  VTSS_F_DDR_PHY_DSGCR_DQSGX(x)        VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DDR_PHY_DSGCR_DQSGX           VTSS_BIT(6)
#define  VTSS_X_DDR_PHY_DSGCR_DQSGX(x)        VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Bypass Rise-to-Rise Mode: Indicates, if set, that the PHY bypass mode
 * isconfigured to run in rise-to-rise mode. Otherwise if not set the PHY
 * bypass mode isrunning in rise-to-fall mode.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . BRRMODE
 */
#define  VTSS_F_DDR_PHY_DSGCR_BRRMODE(x)      VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DDR_PHY_DSGCR_BRRMODE         VTSS_BIT(7)
#define  VTSS_X_DDR_PHY_DSGCR_BRRMODE(x)      VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * PHY Update Acknowledge Delay: Specifies the number of clock cycles that
 * theindication for the completion of PHY update from the PHY to the
 * controller shouldbe delayed. This essentially delays, by this many clock
 * cycles, the deassertion ofdfi_ctrlup_ack and dfi_phyupd_req signals
 * relative to the time when the delay linesor I/Os are updated.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . PUAD
 */
#define  VTSS_F_DDR_PHY_DSGCR_PUAD(x)         VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_PHY_DSGCR_PUAD            VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_PHY_DSGCR_PUAD(x)         VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * DTO On-Die Termination: Enables, when set, the on-die termination on the
 * I/O forDTO pins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . DTOODT
 */
#define  VTSS_F_DDR_PHY_DSGCR_DTOODT(x)       VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DDR_PHY_DSGCR_DTOODT          VTSS_BIT(12)
#define  VTSS_X_DDR_PHY_DSGCR_DTOODT(x)       VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * DTO Power Down Driver: Powers down, when set, the output driver on the
 * I/O forDTO pins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . DTOPDD
 */
#define  VTSS_F_DDR_PHY_DSGCR_DTOPDD(x)       VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DDR_PHY_DSGCR_DTOPDD          VTSS_BIT(13)
#define  VTSS_X_DDR_PHY_DSGCR_DTOPDD(x)       VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * DTO Power Down Receiver: Powers down, when set, the input receiver on
 * the I/Ofor DTO pins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . DTOPDR
 */
#define  VTSS_F_DDR_PHY_DSGCR_DTOPDR(x)       VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_DDR_PHY_DSGCR_DTOPDR          VTSS_BIT(14)
#define  VTSS_X_DDR_PHY_DSGCR_DTOPDR(x)       VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * DTO I/O Mode: Selects SSTL mode (when set to 0) or CMOS mode (when set
 * to 1)of the I/O for DTO pins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . DTOIOM
 */
#define  VTSS_F_DDR_PHY_DSGCR_DTOIOM(x)       VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_DDR_PHY_DSGCR_DTOIOM          VTSS_BIT(15)
#define  VTSS_X_DDR_PHY_DSGCR_DTOIOM(x)       VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * DTO Output Enable: Enables, when set, the output driver on the I/O for
 * DTO pins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . DTOOE
 */
#define  VTSS_F_DDR_PHY_DSGCR_DTOOE(x)        VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DDR_PHY_DSGCR_DTOOE           VTSS_BIT(16)
#define  VTSS_X_DDR_PHY_DSGCR_DTOOE(x)        VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * ATO Analog Test Enable.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . ATOAE
 */
#define  VTSS_F_DDR_PHY_DSGCR_ATOAE(x)        VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_DDR_PHY_DSGCR_ATOAE           VTSS_BIT(17)
#define  VTSS_X_DDR_PHY_DSGCR_ATOAE(x)        VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Rise-to-Rise Mode: Indicates, if set, that the PHY mission mode is
 * configured to runin rise-to-rise mode. Otherwise if not set the PHY
 * mission mode is running in rise-to-fallmode.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . RRMODE
 */
#define  VTSS_F_DDR_PHY_DSGCR_RRMODE(x)       VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_DDR_PHY_DSGCR_RRMODE          VTSS_BIT(18)
#define  VTSS_X_DDR_PHY_DSGCR_RRMODE(x)       VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Single Data Rate Mode: Indicates, if set, that the external controller
 * is configured torun in single data rate (SDR) mode. Otherwise if not set
 * the controller is running inhalf data rate (HDR) mode. This bit not
 * supported in the current version of the PUB.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . SDRMODE
 */
#define  VTSS_F_DDR_PHY_DSGCR_SDRMODE(x)      VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_DDR_PHY_DSGCR_SDRMODE         VTSS_BIT(19)
#define  VTSS_X_DDR_PHY_DSGCR_SDRMODE(x)      VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * CKE Power Down Driver: Powers down, when set, the output driver on the
 * I/O forCKE[3:0] pins. CKEPDD[0] controls the power down for CKE[0],
 * CKEPDD[1]controls the power down for CKE[1], and so on.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . CKEPDD
 */
#define  VTSS_F_DDR_PHY_DSGCR_CKEPDD(x)       VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_DDR_PHY_DSGCR_CKEPDD          VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_DDR_PHY_DSGCR_CKEPDD(x)       VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * ODT Power Down Driver: Powers down, when set, the output driver on the
 * I/O forODT[3:0] pins. ODTPDD[0] controls the power down for ODT[0],
 * ODTPDD[1]controls the power down for ODT[1], and so on.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . ODTPDD
 */
#define  VTSS_F_DDR_PHY_DSGCR_ODTPDD(x)       VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_PHY_DSGCR_ODTPDD          VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_PHY_DSGCR_ODTPDD(x)       VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * SDRAM CK Output Enable: Enables, when set, the output driver on the I/O
 * forSDRAM CK/CK# pins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . CKOE
 */
#define  VTSS_F_DDR_PHY_DSGCR_CKOE(x)         VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_DDR_PHY_DSGCR_CKOE            VTSS_BIT(28)
#define  VTSS_X_DDR_PHY_DSGCR_CKOE(x)         VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * SDRAM ODT Output Enable: Enables, when set, the output driver on the I/O
 * forSDRAM ODT pins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . ODTOE
 */
#define  VTSS_F_DDR_PHY_DSGCR_ODTOE(x)        VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_DDR_PHY_DSGCR_ODTOE           VTSS_BIT(29)
#define  VTSS_X_DDR_PHY_DSGCR_ODTOE(x)        VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * SDRAM Reset Output Enable: Enables, when set, the output driver on the
 * I/O forSDRAM RST# pin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . RSTOE
 */
#define  VTSS_F_DDR_PHY_DSGCR_RSTOE(x)        VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_PHY_DSGCR_RSTOE           VTSS_BIT(30)
#define  VTSS_X_DDR_PHY_DSGCR_RSTOE(x)        VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * SDRAM CKE Output Enable: Enables, when set, the output driver on the I/O
 * forSDRAM CKE pins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DSGCR . CKEOE
 */
#define  VTSS_F_DDR_PHY_DSGCR_CKEOE(x)        VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_PHY_DSGCR_CKEOE           VTSS_BIT(31)
#define  VTSS_X_DDR_PHY_DSGCR_CKEOE(x)        VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief DRAM Configuration Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DCR
 */
#define VTSS_DDR_PHY_DCR                     VTSS_IOREG(VTSS_TO_DDR_PHY,0x11)

/**
 * \brief
 * DDR Mode: SDRAM DDR mode. Valid values are:000 = Reserved001 =
 * Reserved010 = DDR2011 = DDR3100 - 111 = Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCR . DDRMD
 */
#define  VTSS_F_DDR_PHY_DCR_DDRMD(x)          VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_DDR_PHY_DCR_DDRMD             VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_DDR_PHY_DCR_DDRMD(x)          VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * DDR 8-Bank: Indicates, if set, that the SDRAM used has 8 banks. tRPA =
 * tRP+1 andtFAW are used for 8-bank DRAMs, otherwise tRPA = tRP and no
 * tFAW is used.Note that a setting of 1 for DRAMs that have fewer than 8
 * banks results in correctfunctionality, but less tight DRAM command
 * spacing for the parameters.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCR . DDR8BNK
 */
#define  VTSS_F_DDR_PHY_DCR_DDR8BNK(x)        VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_PHY_DCR_DDR8BNK           VTSS_BIT(3)
#define  VTSS_X_DDR_PHY_DCR_DDR8BNK(x)        VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Primary DQ (DDR3 Only): Specifies the DQ pin in a byte that is
 * designated as aprimary pin for Multi-Purpose Register (MPR) reads. Valid
 * values are 0 to 7 forDQ[0] to DQ[7], respectively.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCR . PDQ
 */
#define  VTSS_F_DDR_PHY_DCR_PDQ(x)            VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_DDR_PHY_DCR_PDQ               VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_DDR_PHY_DCR_PDQ(x)            VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \brief
 * Multi-Purpose Register (MPR) DQ (DDR3 Only): Specifies the value that is
 * drivenon non-primary DQ pins during MPR reads. Valid values are:0 =
 * Primary DQ drives out the data from MPR (0-1-0-1); non-primary DQs drive
 * '0'1 = Primary DQ and non-primary DQs all drive the same data from MPR
 * (0-1-0-1)
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCR . MPRDQ
 */
#define  VTSS_F_DDR_PHY_DCR_MPRDQ(x)          VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DDR_PHY_DCR_MPRDQ             VTSS_BIT(7)
#define  VTSS_X_DDR_PHY_DCR_MPRDQ(x)          VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Byte Mask: Mask applied to all beats of read data on all bytes lanes
 * during readDQS gate training. This allows training to be conducted based
 * on selected bit(s)from the byte lanes.Valid values for each bit are:0 =
 * Disable compare for that bit1 = Enable compare for that bitNote that
 * this mask applies in DDR3 MPR operation mode as well and must be
 * inkeeping with the PDQ field setting.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCR . BYTEMASK
 */
#define  VTSS_F_DDR_PHY_DCR_BYTEMASK(x)       VTSS_ENCODE_BITFIELD(x,10,8)
#define  VTSS_M_DDR_PHY_DCR_BYTEMASK          VTSS_ENCODE_BITMASK(10,8)
#define  VTSS_X_DDR_PHY_DCR_BYTEMASK(x)       VTSS_EXTRACT_BITFIELD(x,10,8)

/**
 * \brief
 * No Simultaneous Rank Access: Specifies, if set, that simultaneous rank
 * access onthe same clock cycle is not allowed. This means that multiple
 * chip select signalsshould not be asserted at the same time. This may be
 * required on some DIMMsystems.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCR . NOSRA
 */
#define  VTSS_F_DDR_PHY_DCR_NOSRA(x)          VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_DDR_PHY_DCR_NOSRA             VTSS_BIT(27)
#define  VTSS_X_DDR_PHY_DCR_NOSRA(x)          VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * DDR 2T Timing: Indicates, if set, that 2T timing should be used by PUB
 * internallygenerated SDRAM transactions.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCR . DDR2T
 */
#define  VTSS_F_DDR_PHY_DCR_DDR2T(x)          VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_DDR_PHY_DCR_DDR2T             VTSS_BIT(28)
#define  VTSS_X_DDR_PHY_DCR_DDR2T(x)          VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Un-buffered DIMM Address Mirroring: Indicates, if set, that there is
 * addressmirroring on the second rank of an un-buffered DIMM (the rank
 * connected toCS#[1]). In this case, the PUB re-scrambles the bank and
 * address when sendingmode register commands to the second rank. This only
 * applies to PUB internalSDRAM transactions. Transactions generated by the
 * controller must make its ownadjustments when using an un-buffered DIMM.
 * DCR[NOSRA] must be set ifaddress mirroring is enabled.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCR . UDIMM
 */
#define  VTSS_F_DDR_PHY_DCR_UDIMM(x)          VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_DDR_PHY_DCR_UDIMM             VTSS_BIT(29)
#define  VTSS_X_DDR_PHY_DCR_UDIMM(x)          VTSS_EXTRACT_BITFIELD(x,29,1)


/**
 * \brief DRAM Timing Parameters Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DTPR0
 */
#define VTSS_DDR_PHY_DTPR0                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x12)

/**
 * \brief
 * Internal read to precharge command delay. Valid values are 2 to 15.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR0 . TRTP
 */
#define  VTSS_F_DDR_PHY_DTPR0_TRTP(x)         VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_PHY_DTPR0_TRTP            VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_PHY_DTPR0_TRTP(x)         VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Internal write to read command delay. Valid values are 1 to 15.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR0 . TWTR
 */
#define  VTSS_F_DDR_PHY_DTPR0_TWTR(x)         VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_DDR_PHY_DTPR0_TWTR            VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_DDR_PHY_DTPR0_TWTR(x)         VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * Precharge command period: The minimum time between a precharge
 * commandand any other command. Note that the Controller automatically
 * derives tRPA for 8-bank DDR2 devices by adding 1 to tRP. Valid values
 * are 2 to 15.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR0 . TRP
 */
#define  VTSS_F_DDR_PHY_DTPR0_TRP(x)          VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_PHY_DTPR0_TRP             VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_PHY_DTPR0_TRP(x)          VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * Activate to read or write delay. Minimum time from when an activate
 * command isissued to when a read or write to the activated row can be
 * issued. Valid values are 2to 15.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR0 . TRCD
 */
#define  VTSS_F_DDR_PHY_DTPR0_TRCD(x)         VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_DDR_PHY_DTPR0_TRCD            VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_DDR_PHY_DTPR0_TRCD(x)         VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * Activate to precharge command delay. Valid values are 2 to 63.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR0 . TRAS
 */
#define  VTSS_F_DDR_PHY_DTPR0_TRAS(x)         VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_DDR_PHY_DTPR0_TRAS            VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_DDR_PHY_DTPR0_TRAS(x)         VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * Activate to activate command delay (different banks). Valid values are 1
 * to 15.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR0 . TRRD
 */
#define  VTSS_F_DDR_PHY_DTPR0_TRRD(x)         VTSS_ENCODE_BITFIELD(x,22,4)
#define  VTSS_M_DDR_PHY_DTPR0_TRRD            VTSS_ENCODE_BITMASK(22,4)
#define  VTSS_X_DDR_PHY_DTPR0_TRRD(x)         VTSS_EXTRACT_BITFIELD(x,22,4)

/**
 * \brief
 * Activate to activate command delay (same bank). Valid values are 2 to
 * 63.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR0 . TRC
 */
#define  VTSS_F_DDR_PHY_DTPR0_TRC(x)          VTSS_ENCODE_BITFIELD(x,26,6)
#define  VTSS_M_DDR_PHY_DTPR0_TRC             VTSS_ENCODE_BITMASK(26,6)
#define  VTSS_X_DDR_PHY_DTPR0_TRC(x)          VTSS_EXTRACT_BITFIELD(x,26,6)


/**
 * \brief DRAM Timing Parameters Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DTPR1
 */
#define VTSS_DDR_PHY_DTPR1                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x13)

/**
 * \brief
 * Load mode cycle time: The minimum time between a load mode register
 * commandand any other command. For DDR3 this is the minimum time between
 * two loadmode register commands. Valid values for DDR2 are 2 to 3. For
 * DDR3, the valueused for tMRD is 4 plus the value programmed in these
 * bits, i.e. tMRD value for DDR3ranges from 4 to 7.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR1 . TMRD
 */
#define  VTSS_F_DDR_PHY_DTPR1_TMRD(x)         VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DDR_PHY_DTPR1_TMRD            VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DDR_PHY_DTPR1_TMRD(x)         VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * Load mode update delay (DDR3 only). The minimum time between a load
 * moderegister command and a non-load mode register command. Valid values
 * are:000 = 12001 = 13010 = 14011 = 15100 = 16101 = 17110 - 111 =
 * Reserved.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR1 . TMOD
 */
#define  VTSS_F_DDR_PHY_DTPR1_TMOD(x)         VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_DDR_PHY_DTPR1_TMOD            VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_DDR_PHY_DTPR1_TMOD(x)         VTSS_EXTRACT_BITFIELD(x,2,3)

/**
 * \brief
 * 4-bank activate period. No more than 4-bank activate commands may be
 * issued in agiven tFAW period. Only applies to 8-bank devices. Valid
 * values are 2 to 63.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR1 . TFAW
 */
#define  VTSS_F_DDR_PHY_DTPR1_TFAW(x)         VTSS_ENCODE_BITFIELD(x,5,6)
#define  VTSS_M_DDR_PHY_DTPR1_TFAW            VTSS_ENCODE_BITMASK(5,6)
#define  VTSS_X_DDR_PHY_DTPR1_TFAW(x)         VTSS_EXTRACT_BITFIELD(x,5,6)

/**
 * \brief
 * Refresh-to-Refresh: Indicates the minimum time, in clock cycles, between
 * tworefresh commands or between a refresh and an active command. This is
 * derivedfrom the minimum refresh interval from the datasheet, tRFC(min),
 * divided by the clockcycle time. The default number of clock cycles is
 * for the largest JEDEC tRFC(minparameter value supported.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR1 . TRFC
 */
#define  VTSS_F_DDR_PHY_DTPR1_TRFC(x)         VTSS_ENCODE_BITFIELD(x,11,9)
#define  VTSS_M_DDR_PHY_DTPR1_TRFC            VTSS_ENCODE_BITMASK(11,9)
#define  VTSS_X_DDR_PHY_DTPR1_TRFC(x)         VTSS_EXTRACT_BITFIELD(x,11,9)

/**
 * \brief
 * Minimum delay from when write leveling mode is programmed to the
 * firstDQS/DQS# rising edge.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR1 . TWLMRD
 */
#define  VTSS_F_DDR_PHY_DTPR1_TWLMRD(x)       VTSS_ENCODE_BITFIELD(x,20,6)
#define  VTSS_M_DDR_PHY_DTPR1_TWLMRD          VTSS_ENCODE_BITMASK(20,6)
#define  VTSS_X_DDR_PHY_DTPR1_TWLMRD(x)       VTSS_EXTRACT_BITFIELD(x,20,6)

/**
 * \brief
 * Write leveling output delay: Number of clock cycles from when write
 * leveling DQS isdriven high by the control block to when the results from
 * the SDRAM on DQ issampled by the control block. This must include the
 * SDRAM tWLO timing parameterplus the round trip delay from control block
 * to SDRAM back to control block.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR1 . TWLO
 */
#define  VTSS_F_DDR_PHY_DTPR1_TWLO(x)         VTSS_ENCODE_BITFIELD(x,26,4)
#define  VTSS_M_DDR_PHY_DTPR1_TWLO            VTSS_ENCODE_BITMASK(26,4)
#define  VTSS_X_DDR_PHY_DTPR1_TWLO(x)         VTSS_EXTRACT_BITFIELD(x,26,4)

/**
 * \brief
 * ODT turn-on/turn-off delays (DDR2 only). The delays are in clock cycles.
 * Validvalues are:00 = 2/2.501 = 3/3.510 = 4/4.511 = 5/5.5Most DDR2
 * devices utilize a fixed value of 2/2.5. For non-standard SDRAMs, theuser
 * must ensure that the operational Write Latency is always greater than or
 * equalto the ODT turn-on delay. For example, a DDR2 SDRAM with CAS
 * latency set to 3and CAS additive latency set to 0 has a Write Latency of
 * 2. Thus 2/2.5 can be used,but not 3/3.5 or higher.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR1 . TAON_OFF_D
 */
#define  VTSS_F_DDR_PHY_DTPR1_TAON_OFF_D(x)   VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_DDR_PHY_DTPR1_TAON_OFF_D      VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_DDR_PHY_DTPR1_TAON_OFF_D(x)   VTSS_EXTRACT_BITFIELD(x,30,2)


/**
 * \brief DRAM Timing Parameters Register 2
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DTPR2
 */
#define VTSS_DDR_PHY_DTPR2                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x14)

/**
 * \brief
 * Self refresh exit delay. The minimum time between a self refresh exit
 * command andany other command. This parameter must be set to the maximum
 * of the variousminimum self refresh exit delay parameters specified in
 * the SDRAM datasheet, i.e.max(tXSNR, tXSRD) for DDR2 and max(tXS, tXSDLL)
 * for DDR3. Valid values are 2 to1023.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR2 . TXS
 */
#define  VTSS_F_DDR_PHY_DTPR2_TXS(x)          VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_DDR_PHY_DTPR2_TXS             VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_DDR_PHY_DTPR2_TXS(x)          VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * \brief
 * Power down exit delay. The minimum time between a power down exit
 * commandand any other command. This parameter must be set to the maximum
 * of the variousminimum power down exit delay parameters specified in the
 * SDRAM datasheet, i.e.max(tXP, tXARD, tXARDS) for DDR2 and max(tXP,
 * tXPDLL) for DDR3. Valid values are 2to 31.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR2 . TXP
 */
#define  VTSS_F_DDR_PHY_DTPR2_TXP(x)          VTSS_ENCODE_BITFIELD(x,10,5)
#define  VTSS_M_DDR_PHY_DTPR2_TXP             VTSS_ENCODE_BITMASK(10,5)
#define  VTSS_X_DDR_PHY_DTPR2_TXP(x)          VTSS_EXTRACT_BITFIELD(x,10,5)

/**
 * \brief
 * CKE minimum pulse width. Also specifies the minimum time that the SDRAM
 * mustremain in power down or self refresh mode. For DDR3 this parameter
 * must be set tothe value of tCKESR which is usually bigger than the value
 * of tCKE. Valid values are 2to 15.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR2 . TCKE
 */
#define  VTSS_F_DDR_PHY_DTPR2_TCKE(x)         VTSS_ENCODE_BITFIELD(x,15,4)
#define  VTSS_M_DDR_PHY_DTPR2_TCKE            VTSS_ENCODE_BITMASK(15,4)
#define  VTSS_X_DDR_PHY_DTPR2_TCKE(x)         VTSS_EXTRACT_BITFIELD(x,15,4)

/**
 * \brief
 * DLL locking time. Valid values are 2 to 1023.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR2 . TDLLK
 */
#define  VTSS_F_DDR_PHY_DTPR2_TDLLK(x)        VTSS_ENCODE_BITFIELD(x,19,10)
#define  VTSS_M_DDR_PHY_DTPR2_TDLLK           VTSS_ENCODE_BITMASK(19,10)
#define  VTSS_X_DDR_PHY_DTPR2_TDLLK(x)        VTSS_EXTRACT_BITFIELD(x,19,10)

/**
 * \brief
 * Read to ODT delay (DDR3 only). Specifies whether ODT can be
 * enabledimmediately after the read post-amble or one clock delay has to
 * be added. Validvalues are:0 = ODT may be turned on immediately after
 * read post-amble1 = ODT may not be turned on until one clock after the
 * read post-ambleIf tRTODT is set to 1, then the read-to-write latency is
 * increased by 1 if ODT isenabled.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR2 . TRTODT
 */
#define  VTSS_F_DDR_PHY_DTPR2_TRTODT(x)       VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_DDR_PHY_DTPR2_TRTODT          VTSS_BIT(29)
#define  VTSS_X_DDR_PHY_DTPR2_TRTODT(x)       VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Read to Write command delay. Valid values are:0 = standard bus turn
 * around delay1 = add 1 clock to standard bus turn around delayThis
 * parameter allows the user to increase the delay between issuing
 * Writecommands to the SDRAM when preceded by Read commands. This provides
 * anoption to increase bus turn-around margin for high frequency systems.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR2 . TRTW
 */
#define  VTSS_F_DDR_PHY_DTPR2_TRTW(x)         VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_PHY_DTPR2_TRTW            VTSS_BIT(30)
#define  VTSS_X_DDR_PHY_DTPR2_TRTW(x)         VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Read to read and write to write command delay. Valid values are:0 = BL/2
 * for DDR2 and 4 for DDR31 = BL/2 + 1 for DDR2 and 5 for DDR3
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTPR2 . TCCD
 */
#define  VTSS_F_DDR_PHY_DTPR2_TCCD(x)         VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_PHY_DTPR2_TCCD            VTSS_BIT(31)
#define  VTSS_X_DDR_PHY_DTPR2_TCCD(x)         VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief DDR3 Mode Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:MR0
 */
#define VTSS_DDR_PHY_MR0                     VTSS_IOREG(VTSS_TO_DDR_PHY,0x15)

/**
 * \brief
 * Burst Length: Determines the maximum number of column locations that can
 * beaccessed during a given read or write command. Valid values are:Valid
 * values for DDR3 are:00 = 8 (Fixed)01 = 4 or 8 (On the fly)10 = 4
 * (Fixed)11 = Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR0 . BL
 */
#define  VTSS_F_DDR_PHY_MR0_BL(x)             VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DDR_PHY_MR0_BL                VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DDR_PHY_MR0_BL(x)             VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * CAS Latency: The delay, in clock cycles, between when the SDRAM
 * registers aread command to when data is available. Valid values are:0010
 * = 50100 = 60110 = 71000 = 81010 = 91100 = 101110 = 110001 = 120011 =
 * 130101 = 14All other settings are reserved and should not be used.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR0 . CL_2
 */
#define  VTSS_F_DDR_PHY_MR0_CL_2(x)           VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_PHY_MR0_CL_2              VTSS_BIT(2)
#define  VTSS_X_DDR_PHY_MR0_CL_2(x)           VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Burst Type: Indicates whether a burst is sequential (0) or interleaved
 * (1).
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR0 . BT
 */
#define  VTSS_F_DDR_PHY_MR0_BT(x)             VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_PHY_MR0_BT                VTSS_BIT(3)
#define  VTSS_X_DDR_PHY_MR0_BT(x)             VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * CAS Latency: The delay, in clock cycles, between when the SDRAM
 * registers aread command to when data is available. Valid values are:0010
 * = 50100 = 60110 = 71000 = 81010 = 91100 = 101110 = 110001 = 120011 =
 * 130101 = 14All other settings are reserved and should not be used.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR0 . CL_6_4
 */
#define  VTSS_F_DDR_PHY_MR0_CL_6_4(x)         VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_DDR_PHY_MR0_CL_6_4            VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_DDR_PHY_MR0_CL_6_4(x)         VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \brief
 * Operating Mode: Selects either normal operating mode (0) or test mode
 * (1). Testmode is reserved for the manufacturer and should not be used.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR0 . TM
 */
#define  VTSS_F_DDR_PHY_MR0_TM(x)             VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DDR_PHY_MR0_TM                VTSS_BIT(7)
#define  VTSS_X_DDR_PHY_MR0_TM(x)             VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * DLL Reset: Writing a '1' to this bit will reset the SDRAM DLL. This bit
 * is selfclearing,i.e. it returns back to '0' after the DLL reset has been
 * issued.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR0 . DR
 */
#define  VTSS_F_DDR_PHY_MR0_DR(x)             VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DDR_PHY_MR0_DR                VTSS_BIT(8)
#define  VTSS_X_DDR_PHY_MR0_DR(x)             VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Write Recovery: This is the value of the write recovery in clock cycles.
 * It iscalculated by dividing the datasheet write recovery time, tWR (ns)
 * by the datasheetclock cycle time, tCK (ns) and rounding up a non-integer
 * value to the next integer.Valid values are:000 = 16001 = 5010 = 6011 =
 * 7100 = 8101 = 10110 = 12111 = 14All other settings are reserved and
 * should not be used.NOTE: tWR (ns) is the time from the first SDRAM
 * positive clock edge after the lastdata-in pair of a write command, to
 * when a precharge of the same bank can beissued.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR0 . WR
 */
#define  VTSS_F_DDR_PHY_MR0_WR(x)             VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_DDR_PHY_MR0_WR                VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_DDR_PHY_MR0_WR(x)             VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * Power-Down Control: Controls the exit time for power-down modes. Refer
 * to theSDRAM datasheet for details on power-down modes. Valid values
 * are:0 = Slow exit (DLL off)1 = Fast exit (DLL on)
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR0 . PD
 */
#define  VTSS_F_DDR_PHY_MR0_PD(x)             VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DDR_PHY_MR0_PD                VTSS_BIT(12)
#define  VTSS_X_DDR_PHY_MR0_PD(x)             VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * JEDEC Reserved.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR0 . MR0_RSVD_15_13
 */
#define  VTSS_F_DDR_PHY_MR0_MR0_RSVD_15_13(x)  VTSS_ENCODE_BITFIELD(x,13,3)
#define  VTSS_M_DDR_PHY_MR0_MR0_RSVD_15_13     VTSS_ENCODE_BITMASK(13,3)
#define  VTSS_X_DDR_PHY_MR0_MR0_RSVD_15_13(x)  VTSS_EXTRACT_BITFIELD(x,13,3)


/**
 * \brief DDR3 Mode Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:MR1
 */
#define VTSS_DDR_PHY_MR1                     VTSS_IOREG(VTSS_TO_DDR_PHY,0x16)

/**
 * \brief
 * DLL Enable/Disable: Enable (0) or disable (1) the DLL. DLL must be
 * enabled fornormal operation.Note: SDRAM DLL off mode is not supported
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR1 . DE
 */
#define  VTSS_F_DDR_PHY_MR1_DE(x)             VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_MR1_DE                VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_MR1_DE(x)             VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Output Driver Impedance Control: Controls the output drive strength.
 * Valid valuesare:00 = RZQ/601 = RZQ710 = Reserved11 = Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR1 . DIC_1
 */
#define  VTSS_F_DDR_PHY_MR1_DIC_1(x)          VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_PHY_MR1_DIC_1             VTSS_BIT(1)
#define  VTSS_X_DDR_PHY_MR1_DIC_1(x)          VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * On Die Termination: Selects the effective resistance for SDRAM on die
 * termination.Valid values are:000 = ODT disabled001 = RZQ/4010 = RZQ/2011
 * = RZQ/6100 = RZQ/12101 = RZQ/8All other settings are reserved and should
 * not be used.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR1 . RTT_2
 */
#define  VTSS_F_DDR_PHY_MR1_RTT_2(x)          VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_PHY_MR1_RTT_2             VTSS_BIT(2)
#define  VTSS_X_DDR_PHY_MR1_RTT_2(x)          VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Posted CAS Additive Latency: Setting additive latency that allows read
 * and writecommands to be issued to the SDRAM earlier than normal (refer
 * to the SDRAMdatasheet for details). Valid values are:00 = 0 (AL
 * disabled)01 = CL - 110 = CL - 211 = Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR1 . AL
 */
#define  VTSS_F_DDR_PHY_MR1_AL(x)             VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_DDR_PHY_MR1_AL                VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_DDR_PHY_MR1_AL(x)             VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * Output Driver Impedance Control: Controls the output drive strength.
 * Valid valuesare:00 = RZQ/601 = RZQ710 = Reserved11 = Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR1 . DIC_5
 */
#define  VTSS_F_DDR_PHY_MR1_DIC_5(x)          VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_PHY_MR1_DIC_5             VTSS_BIT(5)
#define  VTSS_X_DDR_PHY_MR1_DIC_5(x)          VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * On Die Termination: Selects the effective resistance for SDRAM on die
 * termination.Valid values are:000 = ODT disabled001 = RZQ/4010 = RZQ/2011
 * = RZQ/6100 = RZQ/12101 = RZQ/8All other settings are reserved and should
 * not be used.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR1 . RTT_6
 */
#define  VTSS_F_DDR_PHY_MR1_RTT_6(x)          VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DDR_PHY_MR1_RTT_6             VTSS_BIT(6)
#define  VTSS_X_DDR_PHY_MR1_RTT_6(x)          VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Write Leveling Enable: Enables write-leveling when set.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR1 . LEVEL
 */
#define  VTSS_F_DDR_PHY_MR1_LEVEL(x)          VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DDR_PHY_MR1_LEVEL             VTSS_BIT(7)
#define  VTSS_X_DDR_PHY_MR1_LEVEL(x)          VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * JEDEC Reserved.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR1 . DE_RSVD_8
 */
#define  VTSS_F_DDR_PHY_MR1_DE_RSVD_8(x)      VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DDR_PHY_MR1_DE_RSVD_8         VTSS_BIT(8)
#define  VTSS_X_DDR_PHY_MR1_DE_RSVD_8(x)      VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * On Die Termination: Selects the effective resistance for SDRAM on die
 * termination.Valid values are:000 = ODT disabled001 = RZQ/4010 = RZQ/2011
 * = RZQ/6100 = RZQ/12101 = RZQ/8All other settings are reserved and should
 * not be used.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR1 . RTT_9
 */
#define  VTSS_F_DDR_PHY_MR1_RTT_9(x)          VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_DDR_PHY_MR1_RTT_9             VTSS_BIT(9)
#define  VTSS_X_DDR_PHY_MR1_RTT_9(x)          VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * JEDEC Reserved.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR1 . RSVD_10
 */
#define  VTSS_F_DDR_PHY_MR1_RSVD_10(x)        VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_DDR_PHY_MR1_RSVD_10           VTSS_BIT(10)
#define  VTSS_X_DDR_PHY_MR1_RSVD_10(x)        VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Termination Data Strobe: When enabled ('1') TDQS provides additional
 * terminationresistance outputs that may be useful in some system
 * configurations. Refer to theSDRAM datasheet for details.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR1 . TDQS
 */
#define  VTSS_F_DDR_PHY_MR1_TDQS(x)           VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_DDR_PHY_MR1_TDQS              VTSS_BIT(11)
#define  VTSS_X_DDR_PHY_MR1_TDQS(x)           VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Output Enable/Disable: When '0', all outputs function normal; when '1'
 * all SDRAMoutputs are disabled removing output buffer current. This
 * feature is intended to beused for IDD characterization of read current
 * and should not be used in normaloperation.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR1 . QOFF
 */
#define  VTSS_F_DDR_PHY_MR1_QOFF(x)           VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DDR_PHY_MR1_QOFF              VTSS_BIT(12)
#define  VTSS_X_DDR_PHY_MR1_QOFF(x)           VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * JEDEC Reserved.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR1 . MR1_RSVD_15_13
 */
#define  VTSS_F_DDR_PHY_MR1_MR1_RSVD_15_13(x)  VTSS_ENCODE_BITFIELD(x,13,3)
#define  VTSS_M_DDR_PHY_MR1_MR1_RSVD_15_13     VTSS_ENCODE_BITMASK(13,3)
#define  VTSS_X_DDR_PHY_MR1_MR1_RSVD_15_13(x)  VTSS_EXTRACT_BITFIELD(x,13,3)


/**
 * \brief DDR3 Mode Register 2
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:MR2
 */
#define VTSS_DDR_PHY_MR2                     VTSS_IOREG(VTSS_TO_DDR_PHY,0x17)

/**
 * \brief
 * Partial Array Self Refresh: Specifies that data located in areas of the
 * array beyondthe specified location will be lost if self refresh is
 * entered.Valid settings for 4 banks are:000 = Full Array001 = Half Array
 * (BA[1:0] = 00 & 01)010 = Quarter Array (BA[1:0] = 00)011 = Not
 * defined100 = 3/4 Array (BA[1:0] = 01, 10, & 11)101 = Half Array (BA[1:0]
 * = 10 & 11)110 = Quarter Array (BA[1:0] = 11)111 = Not definedValid
 * settings for 8 banks are:000 = Full Array001 = Half Array (BA[2:0] =
 * 000, 001, 010 & 011)010 = Quarter Array (BA[2:0] = 000, 001)011 = 1/8
 * Array (BA[2:0] = 000)100 = 3/4 Array (BA[2:0] = 010, 011, 100, 101, 110
 * & 111)101 = Half Array (BA[2:0] = 100, 101, 110 & 111)110 = Quarter
 * Array (BA[2:0] = 110 & 111)111 = 1/8 Array (BA[2:0] 111)
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR2 . PASR
 */
#define  VTSS_F_DDR_PHY_MR2_PASR(x)           VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_DDR_PHY_MR2_PASR              VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_DDR_PHY_MR2_PASR(x)           VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * CAS Write Latency: The delay, in clock cycles, between when the SDRAM
 * registersa write command to when write data is available. Valid values
 * are:000 = 5 (tCK > 2.5ns)001 = 6 (2.5ns > tCK > 1.875ns)010 = 7 (1.875ns
 * > tCK> 1.5ns)011 = 8 (1.5ns > tCK > 1.25ns)100 = 9 (1.25ns > tCK >
 * 1.07ns)101 = 10 (1.07ns > tCK > 0.935ns)110 = 11 (0.935ns > tCK >
 * 0.833ns)111 = 12 (0.833ns > tCK > 0.75ns)All other settings are reserved
 * and should not be used.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR2 . CWL
 */
#define  VTSS_F_DDR_PHY_MR2_CWL(x)            VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_DDR_PHY_MR2_CWL               VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_DDR_PHY_MR2_CWL(x)            VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * Auto Self-Refresh: When enabled ('1'), SDRAM automatically provides
 * self-refreshpower management functions for all supported operating
 * temperature values.Otherwise the SRT bit must be programmed to indicate
 * the temperature range.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR2 . ASR
 */
#define  VTSS_F_DDR_PHY_MR2_ASR(x)            VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DDR_PHY_MR2_ASR               VTSS_BIT(6)
#define  VTSS_X_DDR_PHY_MR2_ASR(x)            VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Self-Refresh Temperature Range: Selects either normal ('0') or extended
 * ('1')operating temperature range during self-refresh.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR2 . SRT
 */
#define  VTSS_F_DDR_PHY_MR2_SRT(x)            VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DDR_PHY_MR2_SRT               VTSS_BIT(7)
#define  VTSS_X_DDR_PHY_MR2_SRT(x)            VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * JEDEC Reserved.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR2 . MR2_RSVD_8
 */
#define  VTSS_F_DDR_PHY_MR2_MR2_RSVD_8(x)     VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DDR_PHY_MR2_MR2_RSVD_8        VTSS_BIT(8)
#define  VTSS_X_DDR_PHY_MR2_MR2_RSVD_8(x)     VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Dynamic ODT: Selects RTT for dynamic ODT. Valid values are:00 = Dynamic
 * ODT off01 = RZQ/410 = RZQ/211 = Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR2 . RTT_WR
 */
#define  VTSS_F_DDR_PHY_MR2_RTT_WR(x)         VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_DDR_PHY_MR2_RTT_WR            VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_DDR_PHY_MR2_RTT_WR(x)         VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * JEDEC Reserved.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR2 . RSVD_15_11
 */
#define  VTSS_F_DDR_PHY_MR2_RSVD_15_11(x)     VTSS_ENCODE_BITFIELD(x,11,5)
#define  VTSS_M_DDR_PHY_MR2_RSVD_15_11        VTSS_ENCODE_BITMASK(11,5)
#define  VTSS_X_DDR_PHY_MR2_RSVD_15_11(x)     VTSS_EXTRACT_BITFIELD(x,11,5)


/**
 * \brief DDR3 Mode Register 3
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:MR3
 */
#define VTSS_DDR_PHY_MR3                     VTSS_IOREG(VTSS_TO_DDR_PHY,0x18)

/**
 * \brief
 * Multi-Purpose Register (MPR) Location: Selects MPR data location: Valid
 * value are:00 = Predefined pattern for system calibrationAll other
 * settings are reserved and should not be used.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR3 . MPRLOC
 */
#define  VTSS_F_DDR_PHY_MR3_MPRLOC(x)         VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DDR_PHY_MR3_MPRLOC            VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DDR_PHY_MR3_MPRLOC(x)         VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * Multi-Purpose Register Enable: Enables, if set, that read data should
 * come from theMulti-Purpose Register. Otherwise read data come from the
 * DRAM array.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR3 . MPR
 */
#define  VTSS_F_DDR_PHY_MR3_MPR(x)            VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_PHY_MR3_MPR               VTSS_BIT(2)
#define  VTSS_X_DDR_PHY_MR3_MPR(x)            VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * JEDEC Reserved.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_MR3 . RSVD_15_3
 */
#define  VTSS_F_DDR_PHY_MR3_RSVD_15_3(x)      VTSS_ENCODE_BITFIELD(x,3,13)
#define  VTSS_M_DDR_PHY_MR3_RSVD_15_3         VTSS_ENCODE_BITMASK(3,13)
#define  VTSS_X_DDR_PHY_MR3_RSVD_15_3(x)      VTSS_EXTRACT_BITFIELD(x,3,13)


/**
 * \brief ODT Configuration Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:ODTCR
 */
#define VTSS_DDR_PHY_ODTCR                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x19)

/**
 * \brief
 * Read ODT: Specifies whether ODT should be enabled ('1') or disabled
 * ('0') on eachof the up to four ranks when a read command is sent to rank
 * n. RDODT0, RDODT1,RDODT2, and RDODT3 specify ODT settings when a read is
 * to rank 0, rank 1, rank2, and rank 3, respectively. The four bits of
 * each field each represent a rank, theLSB being rank 0 and the MSB being
 * rank 3. Default is to disable ODT during reads.bits [3  : 0] =
 * RDODT0bits [7  : 4] = RDODT1bits [11: 8] = RDODT2bits [15:12] =
 * RDODT3For example, assume the system is a 2-rank configuration and
 * during Read commands the user wishes toalways enable the ODT on the
 * SDRAM which is not providing the Read data. In this case, the user
 * wouldwrite "0010" to RDODT0 and "0001" to RDODT1.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ODTCR . RDODT
 */
#define  VTSS_F_DDR_PHY_ODTCR_RDODT(x)        VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_PHY_ODTCR_RDODT           VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_PHY_ODTCR_RDODT(x)        VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Write ODT: Specifies whether ODT should be enabled ('1') or disabled
 * ('0') on eachof the up to four ranks when a write command is sent to
 * rank n. WRODT0,WRODT1, WRODT2, and WRODT3 specify ODT settings when a
 * write is to rank 0,rank 1, rank 2, and rank 3, respectively. The four
 * bits of each field each represent arank, the LSB being rank 0 and the
 * MSB being rank 3. Default is to enable ODT onlyon rank being written to.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ODTCR . WRODT
 */
#define  VTSS_F_DDR_PHY_ODTCR_WRODT(x)        VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DDR_PHY_ODTCR_WRODT           VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DDR_PHY_ODTCR_WRODT(x)        VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Data Training Configuration Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DTCR
 */
#define VTSS_DDR_PHY_DTCR                    VTSS_IOREG(VTSS_TO_DDR_PHY,0x1a)

/**
 * \brief
 * Data Training Repeat Number: Repeat number used to confirm stability of
 * DDRwrite or read.Note: The minimum value should be 0x4
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTCR . DTRPTN
 */
#define  VTSS_F_DDR_PHY_DTCR_DTRPTN(x)        VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_PHY_DTCR_DTRPTN           VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_PHY_DTCR_DTRPTN(x)        VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Data Training Rank: Select the SDRAM rank to be used during Read DQS
 * gatetraining, Read/Write Data Bit Deskew, Read/Write Eye Training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTCR . DTRANK
 */
#define  VTSS_F_DDR_PHY_DTCR_DTRANK(x)        VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_DDR_PHY_DTCR_DTRANK           VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_DDR_PHY_DTCR_DTRANK(x)        VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * Read Data Training Using MPR (DDR3 Only): Specifies, if set, that DQS
 * gatetraining should use the SDRAM Multi-Purpose Register (MPR) register.
 * Otherwisedata-training is performed by first writing to some locations
 * in the SDRAM and thenreading them back.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTCR . DTMPR
 */
#define  VTSS_F_DDR_PHY_DTCR_DTMPR(x)         VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DDR_PHY_DTCR_DTMPR            VTSS_BIT(6)
#define  VTSS_X_DDR_PHY_DTCR_DTMPR(x)         VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Read Data Training Compare Data: Specifies, if set, that DQS gate
 * training shouldalso check if the returning read data is correct.
 * Otherwise data-training only checksif the correct number of DQS edges
 * were returned.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTCR . DTCMPD
 */
#define  VTSS_F_DDR_PHY_DTCR_DTCMPD(x)        VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DDR_PHY_DTCR_DTCMPD           VTSS_BIT(7)
#define  VTSS_X_DDR_PHY_DTCR_DTCMPD(x)        VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Training WDQ Margin: Defines how close to 0 or how close to
 * 2*(wdqcalibration_value) the WDQ LCDL can be moved during training.
 * Basically defineshow much timing margin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTCR . DTWDQM
 */
#define  VTSS_F_DDR_PHY_DTCR_DTWDQM(x)        VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_PHY_DTCR_DTWDQM           VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_PHY_DTCR_DTWDQM(x)        VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * Data Training Write Bit Deskew Data Mask, if set, it enables write bit
 * deskew of thedata mask.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTCR . DTWBDDM
 */
#define  VTSS_F_DDR_PHY_DTCR_DTWBDDM(x)       VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DDR_PHY_DTCR_DTWBDDM          VTSS_BIT(12)
#define  VTSS_X_DDR_PHY_DTCR_DTWBDDM(x)       VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Data Training Bit Deskew Centering: Enables, if set, eye centering
 * capability duringwrite and read bit deskew training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTCR . DTBDC
 */
#define  VTSS_F_DDR_PHY_DTCR_DTBDC(x)         VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DDR_PHY_DTCR_DTBDC            VTSS_BIT(13)
#define  VTSS_X_DDR_PHY_DTCR_DTBDC(x)         VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Data Training WDQ Margin Override: If set, the Training WDQ Margin
 * valuespecified in DTCR[11:8] (DTWDQM) is used during data training.
 * Otherwise thevalue is computed as ¼ of the ddr_clk period measurement
 * found during calibrationof the WDQ LCDL.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTCR . DTWDQMO
 */
#define  VTSS_F_DDR_PHY_DTCR_DTWDQMO(x)       VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_DDR_PHY_DTCR_DTWDQMO          VTSS_BIT(14)
#define  VTSS_X_DDR_PHY_DTCR_DTWDQMO(x)       VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Data Training Debug Byte Select: Selects the byte during data training
 * single stepdebug mode.Note: DTDEN is not used to enable this feature.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTCR . DTDBS
 */
#define  VTSS_F_DDR_PHY_DTCR_DTDBS(x)         VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DDR_PHY_DTCR_DTDBS            VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DDR_PHY_DTCR_DTDBS(x)         VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Data Training Debug Enable: Enables, if set, the data training single
 * step debugmode.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTCR . DTDEN
 */
#define  VTSS_F_DDR_PHY_DTCR_DTDEN(x)         VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_DDR_PHY_DTCR_DTDEN            VTSS_BIT(20)
#define  VTSS_X_DDR_PHY_DTCR_DTDEN(x)         VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Data Training Debug Step: A write of 1 to this bit steps the data
 * training algorithmthrough a single step. This bit is used to initiate
 * one step of the data trainingalgorithm in question.This bit is
 * self-clearing. To trigger the next step, this bit must be written to
 * again.Note: The training steps must be repeated in order to get new data
 * in the "DataTraining Eye Data Register 0-1 (DTEDR0-1)" For example, to
 * see thetraining results for a different lane, select that lane and
 * repeat the training steps topopulate DTEDR0 and DTEDR1 with the correct
 * data.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTCR . DTDSTP
 */
#define  VTSS_F_DDR_PHY_DTCR_DTDSTP(x)        VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_DDR_PHY_DTCR_DTDSTP           VTSS_BIT(21)
#define  VTSS_X_DDR_PHY_DTCR_DTDSTP(x)        VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Data Training Extended Write DQS: Enables, if set, an extended write DQS
 * wherebytwo additional pulses of DQS are added as post-amble to a burst
 * of writes.Generally this should only be enabled when running read bit
 * deskew with theintention of performing read eye deskew prior to running
 * write leveling adjustment.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTCR . DTEXD
 */
#define  VTSS_F_DDR_PHY_DTCR_DTEXD(x)         VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_DDR_PHY_DTCR_DTEXD            VTSS_BIT(22)
#define  VTSS_X_DDR_PHY_DTCR_DTEXD(x)         VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Rank Enable: Specifies the ranks that are enabled for data-training. Bit
 * 0 controlsrank 0, bit 1 controls rank 1, bit 2 controls rank 2, and bit
 * 3 controls rank 3. Settingthe bit to '1' enables the rank, and setting
 * it to '0' disables the rank.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTCR . RANKEN
 */
#define  VTSS_F_DDR_PHY_DTCR_RANKEN(x)        VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_PHY_DTCR_RANKEN           VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_PHY_DTCR_RANKEN(x)        VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * Refresh During Training: A non-zero value specifies that a burst of
 * refreshes equalto the number specified in this field should be sent to
 * the SDRAM after training eachrank except the last rank.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTCR . RFSHDT
 */
#define  VTSS_F_DDR_PHY_DTCR_RFSHDT(x)        VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_DDR_PHY_DTCR_RFSHDT           VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_DDR_PHY_DTCR_RFSHDT(x)        VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief Data Training Address Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DTAR0
 */
#define VTSS_DDR_PHY_DTAR0                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x1b)

/**
 * \brief
 * Data Training Column Address: Selects the SDRAM column address to be
 * usedduring data training. The lower four bits of this address must
 * always be "000".
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTAR0 . DTAR0_DTCOL
 */
#define  VTSS_F_DDR_PHY_DTAR0_DTAR0_DTCOL(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_PHY_DTAR0_DTAR0_DTCOL     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_PHY_DTAR0_DTAR0_DTCOL(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Data Training Row Address: Selects the SDRAM row address to be used
 * duringdata training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTAR0 . DTAR0_DTROW
 */
#define  VTSS_F_DDR_PHY_DTAR0_DTAR0_DTROW(x)  VTSS_ENCODE_BITFIELD(x,12,16)
#define  VTSS_M_DDR_PHY_DTAR0_DTAR0_DTROW     VTSS_ENCODE_BITMASK(12,16)
#define  VTSS_X_DDR_PHY_DTAR0_DTAR0_DTROW(x)  VTSS_EXTRACT_BITFIELD(x,12,16)

/**
 * \brief
 * Data Training Bank Address: Selects the SDRAM bank address to be used
 * duringdata training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTAR0 . DTAR0_DTBANK
 */
#define  VTSS_F_DDR_PHY_DTAR0_DTAR0_DTBANK(x)  VTSS_ENCODE_BITFIELD(x,28,3)
#define  VTSS_M_DDR_PHY_DTAR0_DTAR0_DTBANK     VTSS_ENCODE_BITMASK(28,3)
#define  VTSS_X_DDR_PHY_DTAR0_DTAR0_DTBANK(x)  VTSS_EXTRACT_BITFIELD(x,28,3)


/**
 * \brief Data Training Address Register 1
 *
 * \details
 * Data Training Column Address: Selects the SDRAM column address to be
 * used
 * during data training. The lower four bits of this address must always be
 * "000".
 *
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DTAR1
 */
#define VTSS_DDR_PHY_DTAR1                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x1c)

/**
 * \brief
 * Data Training Column Address.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTAR1 . DTAR1_DTCOL
 */
#define  VTSS_F_DDR_PHY_DTAR1_DTAR1_DTCOL(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_PHY_DTAR1_DTAR1_DTCOL     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_PHY_DTAR1_DTAR1_DTCOL(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Data Training Row Address: Selects the SDRAM row address to be used
 * duringdata training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTAR1 . DTAR1_DTROW
 */
#define  VTSS_F_DDR_PHY_DTAR1_DTAR1_DTROW(x)  VTSS_ENCODE_BITFIELD(x,12,16)
#define  VTSS_M_DDR_PHY_DTAR1_DTAR1_DTROW     VTSS_ENCODE_BITMASK(12,16)
#define  VTSS_X_DDR_PHY_DTAR1_DTAR1_DTROW(x)  VTSS_EXTRACT_BITFIELD(x,12,16)

/**
 * \brief
 * Data Training Bank Address: Selects the SDRAM bank address to be used
 * duringdata training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTAR1 . DTAR1_DTBANK
 */
#define  VTSS_F_DDR_PHY_DTAR1_DTAR1_DTBANK(x)  VTSS_ENCODE_BITFIELD(x,28,3)
#define  VTSS_M_DDR_PHY_DTAR1_DTAR1_DTBANK     VTSS_ENCODE_BITMASK(28,3)
#define  VTSS_X_DDR_PHY_DTAR1_DTAR1_DTBANK(x)  VTSS_EXTRACT_BITFIELD(x,28,3)


/**
 * \brief Data Training Address Register 2
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DTAR2
 */
#define VTSS_DDR_PHY_DTAR2                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x1d)

/**
 * \brief
 * Data Training Column Address: Selects the SDRAM column address to be
 * usedduring data training. The lower four bits of this address must
 * always be "000".
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTAR2 . DTAR2_DTCOL
 */
#define  VTSS_F_DDR_PHY_DTAR2_DTAR2_DTCOL(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_PHY_DTAR2_DTAR2_DTCOL     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_PHY_DTAR2_DTAR2_DTCOL(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Data Training Row Address: Selects the SDRAM row address to be used
 * duringdata training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTAR2 . DTAR2_DTROW
 */
#define  VTSS_F_DDR_PHY_DTAR2_DTAR2_DTROW(x)  VTSS_ENCODE_BITFIELD(x,12,16)
#define  VTSS_M_DDR_PHY_DTAR2_DTAR2_DTROW     VTSS_ENCODE_BITMASK(12,16)
#define  VTSS_X_DDR_PHY_DTAR2_DTAR2_DTROW(x)  VTSS_EXTRACT_BITFIELD(x,12,16)

/**
 * \brief
 * Data Training Bank Address: Selects the SDRAM bank address to be used
 * duringdata training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTAR2 . DTAR2_DTBANK
 */
#define  VTSS_F_DDR_PHY_DTAR2_DTAR2_DTBANK(x)  VTSS_ENCODE_BITFIELD(x,28,3)
#define  VTSS_M_DDR_PHY_DTAR2_DTAR2_DTBANK     VTSS_ENCODE_BITMASK(28,3)
#define  VTSS_X_DDR_PHY_DTAR2_DTAR2_DTBANK(x)  VTSS_EXTRACT_BITFIELD(x,28,3)


/**
 * \brief Data Training Address Register 3
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DTAR3
 */
#define VTSS_DDR_PHY_DTAR3                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x1e)

/**
 * \brief
 * Data Training Column Address: Selects the SDRAM column address to be
 * usedduring data training. The lower four bits of this address must
 * always be "000".
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTAR3 . DTAR3_DTCOL
 */
#define  VTSS_F_DDR_PHY_DTAR3_DTAR3_DTCOL(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_PHY_DTAR3_DTAR3_DTCOL     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_PHY_DTAR3_DTAR3_DTCOL(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Data Training Row Address: Selects the SDRAM row address to be used
 * duringdata training
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTAR3 . DTAR3_DTROW
 */
#define  VTSS_F_DDR_PHY_DTAR3_DTAR3_DTROW(x)  VTSS_ENCODE_BITFIELD(x,12,16)
#define  VTSS_M_DDR_PHY_DTAR3_DTAR3_DTROW     VTSS_ENCODE_BITMASK(12,16)
#define  VTSS_X_DDR_PHY_DTAR3_DTAR3_DTROW(x)  VTSS_EXTRACT_BITFIELD(x,12,16)

/**
 * \brief
 * Data Training Bank Address: Selects the SDRAM bank address to be used
 * duringdata training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTAR3 . DTAR3_DTBANK
 */
#define  VTSS_F_DDR_PHY_DTAR3_DTAR3_DTBANK(x)  VTSS_ENCODE_BITFIELD(x,28,3)
#define  VTSS_M_DDR_PHY_DTAR3_DTAR3_DTBANK     VTSS_ENCODE_BITMASK(28,3)
#define  VTSS_X_DDR_PHY_DTAR3_DTAR3_DTBANK(x)  VTSS_EXTRACT_BITFIELD(x,28,3)


/**
 * \brief Data Training Data Register 0
 *
 * \details
 * Data Training Data: The first 4 bytes of data used during data training.
 * This same
 * data byte is used for each Byte Lane. Default sequence is a walking 1
 * while toggling
 * data every data cycle.
 *
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DTDR0
 */
#define VTSS_DDR_PHY_DTDR0                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x1f)

/**
 * \brief
 * Data Training Data.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTDR0 . DTBYTE0
 */
#define  VTSS_F_DDR_PHY_DTDR0_DTBYTE0(x)      VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_PHY_DTDR0_DTBYTE0         VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_PHY_DTDR0_DTBYTE0(x)      VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Data Training Data.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTDR0 . DTBYTE1
 */
#define  VTSS_F_DDR_PHY_DTDR0_DTBYTE1(x)      VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DDR_PHY_DTDR0_DTBYTE1         VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DDR_PHY_DTDR0_DTBYTE1(x)      VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Data Training Data.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTDR0 . DTBYTE2
 */
#define  VTSS_F_DDR_PHY_DTDR0_DTBYTE2(x)      VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_PHY_DTDR0_DTBYTE2         VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_PHY_DTDR0_DTBYTE2(x)      VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Data Training Data.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTDR0 . DTBYTE3
 */
#define  VTSS_F_DDR_PHY_DTDR0_DTBYTE3(x)      VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DDR_PHY_DTDR0_DTBYTE3         VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DDR_PHY_DTDR0_DTBYTE3(x)      VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief Data Training Data Register 1
 *
 * \details
 * Data Training Data: The second 4 bytes of data used during data
 * training. This same
 * data byte is used for each Byte Lane. Default sequence is a walking 1
 * while toggling
 * data every data cycle.
 *
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DTDR1
 */
#define VTSS_DDR_PHY_DTDR1                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x20)

/**
 * \brief
 * Data Training Data.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTDR1 . DTBYTE4
 */
#define  VTSS_F_DDR_PHY_DTDR1_DTBYTE4(x)      VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_PHY_DTDR1_DTBYTE4         VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_PHY_DTDR1_DTBYTE4(x)      VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Data Training Data.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTDR1 . DTBYTE5
 */
#define  VTSS_F_DDR_PHY_DTDR1_DTBYTE5(x)      VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DDR_PHY_DTDR1_DTBYTE5         VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DDR_PHY_DTDR1_DTBYTE5(x)      VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Data Training Data.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTDR1 . DTBYTE6
 */
#define  VTSS_F_DDR_PHY_DTDR1_DTBYTE6(x)      VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_PHY_DTDR1_DTBYTE6         VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_PHY_DTDR1_DTBYTE6(x)      VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Data Training Data.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTDR1 . DTBYTE7
 */
#define  VTSS_F_DDR_PHY_DTDR1_DTBYTE7(x)      VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DDR_PHY_DTDR1_DTBYTE7         VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DDR_PHY_DTDR1_DTBYTE7(x)      VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief Data Training Eye Data Register 0
 *
 * \details
 * The register is updated after successfully running write data eye
 * training and read data eye training
 * respectively. The write data eye center is determined by the formula
 * (DTWBMX + DTWLMX + DTWLMN -
 * DTWBMN) / 2, and the read data eye center is determined by the formula
 * (DTRBMX + DTRLMX +
 * DTRLMN - DTRBMN) / 2.
 *
 * The training steps must be repeated in order to get new data in the
 * DTEDR0-1 registers. For
 * example, to see the training results for a different lane, select that
 * lane and repeat the training
 * steps to populate DTEDR0 and DTEDR1 with the correct data.
 *
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DTEDR0
 */
#define VTSS_DDR_PHY_DTEDR0                  VTSS_IOREG(VTSS_TO_DDR_PHY,0x21)

/**
 * \brief
 * Data Training Write LCDL Minimum.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTEDR0 . DTWLMN
 */
#define  VTSS_F_DDR_PHY_DTEDR0_DTWLMN(x)      VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_PHY_DTEDR0_DTWLMN         VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_PHY_DTEDR0_DTWLMN(x)      VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Data Training Write LCDL Maximum.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTEDR0 . DTWLMX
 */
#define  VTSS_F_DDR_PHY_DTEDR0_DTWLMX(x)      VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DDR_PHY_DTEDR0_DTWLMX         VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DDR_PHY_DTEDR0_DTWLMX(x)      VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Data Training Write BDL Minimum.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTEDR0 . DTWBMN
 */
#define  VTSS_F_DDR_PHY_DTEDR0_DTWBMN(x)      VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_PHY_DTEDR0_DTWBMN         VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_PHY_DTEDR0_DTWBMN(x)      VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Data Training Write BDL Maximum.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTEDR0 . DTWBMX
 */
#define  VTSS_F_DDR_PHY_DTEDR0_DTWBMX(x)      VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DDR_PHY_DTEDR0_DTWBMX         VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DDR_PHY_DTEDR0_DTWBMX(x)      VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief Data Training Eye Data Register 1
 *
 * \details
 * The register is updated after successfully running write data eye
 * training and read data eye training
 * respectively. The write data eye center is determined by the formula
 * (DTWBMX + DTWLMX + DTWLMN -
 * DTWBMN) / 2, and the read data eye center is determined by the formula
 * (DTRBMX + DTRLMX +
 * DTRLMN - DTRBMN) / 2.
 *
 * The training steps must be repeated in order to get new data in the
 * DTEDR0-1 registers. For
 * example, to see the training results for a different lane, select that
 * lane and repeat the training
 * steps to populate DTEDR0 and DTEDR1 with the correct data.
 *
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DTEDR1
 */
#define VTSS_DDR_PHY_DTEDR1                  VTSS_IOREG(VTSS_TO_DDR_PHY,0x22)

/**
 * \brief
 * Data Training Read DQS LCDL Minimum.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTEDR1 . DTRLMN
 */
#define  VTSS_F_DDR_PHY_DTEDR1_DTRLMN(x)      VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_PHY_DTEDR1_DTRLMN         VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_PHY_DTEDR1_DTRLMN(x)      VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Data Training Read DQS LCDL Maximum.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTEDR1 . DTRLMX
 */
#define  VTSS_F_DDR_PHY_DTEDR1_DTRLMX(x)      VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DDR_PHY_DTEDR1_DTRLMX         VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DDR_PHY_DTEDR1_DTRLMX(x)      VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Data Training Read BDL Shift Minimum.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTEDR1 . DTRBMN
 */
#define  VTSS_F_DDR_PHY_DTEDR1_DTRBMN(x)      VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_PHY_DTEDR1_DTRBMN         VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_PHY_DTEDR1_DTRBMN(x)      VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Data Training Read BDL Shift Maximum.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DTEDR1 . DTRBMX
 */
#define  VTSS_F_DDR_PHY_DTEDR1_DTRBMX(x)      VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DDR_PHY_DTEDR1_DTRBMX         VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DDR_PHY_DTEDR1_DTRBMX(x)      VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief PHY General Configuration Register 2
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:PGCR2
 */
#define VTSS_DDR_PHY_PGCR2                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x23)

/**
 * \brief
 * Refresh Period: Indicates the period in clock cycles after which the PUB
 * has toissue a refresh command to the SDRAM. This is derived from the
 * maximum refreshinterval from the datasheet, tRFC(max) or REFI, divided
 * by the clock cycle time. Afurther 400 clocks must be subtracted from the
 * derived number to account forcommand flow and missed slots of refreshes
 * in the internal PUB blocks. The defaultcorresponds to DDR3 9*7.8us at
 * 1066MHz when a burst of 9 refreshes are issuedat every refresh interval.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR2 . TREFPRD
 */
#define  VTSS_F_DDR_PHY_PGCR2_TREFPRD(x)      VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_DDR_PHY_PGCR2_TREFPRD         VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_DDR_PHY_PGCR2_TREFPRD(x)      VTSS_EXTRACT_BITFIELD(x,0,18)

/**
 * \brief
 * No Bubbles: Specified whether reads should be returned to the controller
 * with nobubbles. Enabling no-bubble reads increases the read latency.
 * Valid values are:0 = Bubbles are allowed during reads1 = Bubbles are not
 * allowed during reads
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR2 . NOBUB
 */
#define  VTSS_F_DDR_PHY_PGCR2_NOBUB(x)        VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_DDR_PHY_PGCR2_NOBUB           VTSS_BIT(18)
#define  VTSS_X_DDR_PHY_PGCR2_NOBUB(x)        VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Fixed Latency: Specified whether all reads should be returned to the
 * controller witha fixed read latency. Enabling fixed read latency
 * increases the read latency. Validvalues are:0 = Disable fixed read
 * latency1 = Enable fixed read latencyFixed read latency is calculated as
 * (12 + (maximum DXnGTR.RxDGSL)/2) HDRclock cycles
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR2 . FXDLAT
 */
#define  VTSS_F_DDR_PHY_PGCR2_FXDLAT(x)       VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_DDR_PHY_PGCR2_FXDLAT          VTSS_BIT(19)
#define  VTSS_X_DDR_PHY_PGCR2_FXDLAT(x)       VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Data Training PUB Mode Timer Exit: Specifies the number of controller
 * clocks towait when entering and exiting pub mode data training. The
 * default value ensurescontroller refreshes do not cause memory model
 * errors when entering and exitingdata training. The value should be
 * increased if controller initiated SDRAM ZQ shortor long operation may
 * occur just before or just after the execution of data training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR2 . DTPMXTMR
 */
#define  VTSS_F_DDR_PHY_PGCR2_DTPMXTMR(x)     VTSS_ENCODE_BITFIELD(x,20,8)
#define  VTSS_M_DDR_PHY_PGCR2_DTPMXTMR        VTSS_ENCODE_BITMASK(20,8)
#define  VTSS_X_DDR_PHY_PGCR2_DTPMXTMR(x)     VTSS_EXTRACT_BITFIELD(x,20,8)

/**
 * \brief
 * Shared-AC mode: set to 1 to enable shared address/command mode with
 * twoindependent data channels - available only if shared address/command
 * modesupport is compiled in.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR2 . SHRAC
 */
#define  VTSS_F_DDR_PHY_PGCR2_SHRAC(x)        VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_DDR_PHY_PGCR2_SHRAC           VTSS_BIT(28)
#define  VTSS_X_DDR_PHY_PGCR2_SHRAC(x)        VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * AC Power-Down with Dual Channels : Set to 1 to power-down
 * address/commandlane when both data channels are powered-down. Only valid
 * in shared-AC mode.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR2 . ACPDDC
 */
#define  VTSS_F_DDR_PHY_PGCR2_ACPDDC(x)       VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_DDR_PHY_PGCR2_ACPDDC          VTSS_BIT(29)
#define  VTSS_X_DDR_PHY_PGCR2_ACPDDC(x)       VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Low-Power Master Channel 0: set to 1 to have channel 0 act as master to
 * drivechannel 1 low-power functions simultaneously. Only valid in
 * shared-AC mode.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR2 . LPMSTRC0
 */
#define  VTSS_F_DDR_PHY_PGCR2_LPMSTRC0(x)     VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_PHY_PGCR2_LPMSTRC0        VTSS_BIT(30)
#define  VTSS_X_DDR_PHY_PGCR2_LPMSTRC0(x)     VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Dynamic AC Power Down Driver: Powers down, when set, the output driver
 * on I/Ofor ADDR and BA. This bit is ORed with bit ACIOCR[3] (ACPDD).
 *
 * \details
 * Field: ::VTSS_DDR_PHY_PGCR2 . DYNACPDD
 */
#define  VTSS_F_DDR_PHY_PGCR2_DYNACPDD(x)     VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_PHY_PGCR2_DYNACPDD        VTSS_BIT(31)
#define  VTSS_X_DDR_PHY_PGCR2_DYNACPDD(x)     VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief RDIMM General Configuration Register 0
 *
 * \details
 * RDIMM General Configuration Registers are used to configure and control
 * the PUB and the PHY for
 * RDIMM support.
 *
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:RDIMMGCR0
 */
#define VTSS_DDR_PHY_RDIMMGCR0               VTSS_IOREG(VTSS_TO_DDR_PHY,0x2c)

/**
 * \brief
 * Registered DIMM: Indicates, if set, that a registered DIMM is used. In
 * this case,the PUB increases the SDRAM write and read latencies (WL/RL)
 * by 1 and alsoenforces that accesses adhere to RDIMM buffer chip. This
 * only applies to PUBinternal SDRAM transactions. Transactions generated
 * by the controller mustmake its own adjustments to WL/RL when using a
 * registered DIMM. TheDCR.NOSRA register bit must be set to '1' if using
 * the standard RDIMM bufferchip so that normal DRAM accesses do not assert
 * multiple chip select bits atthe same time.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . RDIMM
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_RDIMM(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_RDIMM       VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_RDIMM(x)    VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Parity Error No Registering: Indicates, if set, that parity error signal
 * from theRDIMM should be passed to the DFI controller without any
 * synchronization orregistering.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . ERRNOREG
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_ERRNOREG(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_ERRNOREG    VTSS_BIT(1)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_ERRNOREG(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Stop On Parity Error: Indicates, if set, that the PUB is to stop driving
 * commandsto the DRAM upon encountering a parity error. Transactions can
 * resume onlyafter status is cleared via PIR.CLRSR
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . SOPERR
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_SOPERR(x)   VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_SOPERR      VTSS_BIT(2)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_SOPERR(x)   VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * PAR_IN On-Die Termination: Enables, when set, the on-die termination on
 * theI/O for PAR_IN pin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . PARINODT
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_PARINODT(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_PARINODT    VTSS_BIT(14)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_PARINODT(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * PAR_IN Power Down Driver: Powers down, when set, the output driver on
 * theI/O for PAR_IN pin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . PARINPDD
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_PARINPDD(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_PARINPDD    VTSS_BIT(15)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_PARINPDD(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * PAR_IN Power Down Receiver: Powers down, when set, the input receiver
 * onthe I/O for PAR_IN pin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . PARINPDR
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_PARINPDR(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_PARINPDR    VTSS_BIT(16)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_PARINPDR(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * PAR_IN I/O Mode: Selects SSTL mode (when set to 0) or CMOS mode (whenset
 * to 1) of the I/O for PAR_IN pin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . PARINIOM
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_PARINIOM(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_PARINIOM    VTSS_BIT(17)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_PARINIOM(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * PAR_IN Output Enable: Enables, when set, the output driver on the I/O
 * forPAR_IN pin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . PARINOE
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_PARINOE(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_PARINOE     VTSS_BIT(18)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_PARINOE(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * ERROUT# On-Die Termination: Enables, when set, the on-die termination
 * onthe I/O for ERROUT# pin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . ERROUTODT
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_ERROUTODT(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_ERROUTODT   VTSS_BIT(19)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_ERROUTODT(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * ERROUT# Power Down Driver: Powers down, when set, the output driver on
 * theI/O for ERROUT# pin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . ERROUTPDD
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_ERROUTPDD(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_ERROUTPDD   VTSS_BIT(20)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_ERROUTPDD(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * ERROUT# Power Down Receiver: Powers down, when set, the input receiver
 * onthe I/O for ERROUT# pin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . ERROUTPDR
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_ERROUTPDR(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_ERROUTPDR   VTSS_BIT(21)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_ERROUTPDR(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * ERROUT# I/O Mode: Selects SSTL mode (when set to 0) or CMOS mode(when
 * set to 1) of the I/O for ERROUT# pin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . ERROUTIOM
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_ERROUTIOM(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_ERROUTIOM   VTSS_BIT(22)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_ERROUTIOM(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * ERROUT# Output Enable: Enables, when set, the output driver on the I/O
 * forERROUT# pin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . ERROUTOE
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_ERROUTOE(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_ERROUTOE    VTSS_BIT(23)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_ERROUTOE(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * RDIMM Outputs On-Die Termination: Enables, when set, the on-die
 * terminationon the I/O for QCSEN# and MIRROR pins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . RDIMMODT
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_RDIMMODT(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_RDIMMODT    VTSS_BIT(24)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_RDIMMODT(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * RDIMM Outputs Power Down Driver: Powers down, when set, the output
 * driveron the I/O for QCSEN# and MIRROR pins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . RDIMMPDD
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_RDIMMPDD(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_RDIMMPDD    VTSS_BIT(25)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_RDIMMPDD(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * RDIMM Outputs Power Down Receiver: Powers down, when set, the
 * inputreceiver on the I/O for QCSEN# and MIRROR pins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . RDIMMPDR
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_RDIMMPDR(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_RDIMMPDR    VTSS_BIT(26)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_RDIMMPDR(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * RDIMM Outputs I/O Mode: Selects SSTL mode (when set to 0) or CMOS
 * mode(when set to 1) of the I/O for QCSEN# and MIRROR pins.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . RDIMMIOM
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_RDIMMIOM(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_RDIMMIOM    VTSS_BIT(27)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_RDIMMIOM(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * QCSEN# Output Enable: Enables, when set, the output driver on the I/O
 * forQCSEN# pin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . QCSENOE
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_QCSENOE(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_QCSENOE     VTSS_BIT(28)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_QCSENOE(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * MIRROR Output Enable: Enables, when set, the output driver on the I/O
 * forMIRROR pin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . MIRROROE
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_MIRROROE(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_MIRROROE    VTSS_BIT(29)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_MIRROROE(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * RDMIMM Quad CS Enable: Enables, if set, the Quad CS mode for the
 * RDIMMregistering buffer chip. This register bit controls the buffer chip
 * QCSEN# signal.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . QCSEN
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_QCSEN(x)    VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_QCSEN       VTSS_BIT(30)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_QCSEN(x)    VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * RDIMM Mirror: Selects between two different ballouts of the RDIMM buffer
 * chipfor front or back operation. This register bit controls the buffer
 * chip MIRRORsignal.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR0 . MIRROR
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR0_MIRROR(x)   VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_PHY_RDIMMGCR0_MIRROR      VTSS_BIT(31)
#define  VTSS_X_DDR_PHY_RDIMMGCR0_MIRROR(x)   VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief RDIMM General Configuration Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:RDIMMGCR1
 */
#define VTSS_DDR_PHY_RDIMMGCR1               VTSS_IOREG(VTSS_TO_DDR_PHY,0x2d)

/**
 * \brief
 * Stabilization time: Number of DRAM clock cycles for the RDIMM buffer
 * chip tostabilize. This parameter corresponds to the buffer chip tSTAB
 * parameter. Defaultvalue is in decimal format and corresponds to 6us at
 * 533MHz.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR1 . TBCSTAB
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR1_TBCSTAB(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_PHY_RDIMMGCR1_TBCSTAB     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_PHY_RDIMMGCR1_TBCSTAB(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Command word to command word programming delay: Number of DRAM
 * clockcycles between two RDIMM buffer chip command programming accesses.
 * Thevalue used for tBCMRD is 8 plus the value programmed in these bits,
 * i.e. tBCMRDvalue ranges from 8 to 15. This parameter corresponds to the
 * buffer chip tMRDparameter.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR1 . TBCMRD
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR1_TBCMRD(x)   VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_DDR_PHY_RDIMMGCR1_TBCMRD      VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_DDR_PHY_RDIMMGCR1_TBCMRD(x)   VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * Control Registers Initialization Enable: Indicates which RDIMM buffer
 * chip controlregisters (RC0 to RC15) should be initialized (written) when
 * the PUB is triggered toinitialize the buffer chip. A setting of '1' on
 * CRINIT[n] bit means that CRn should bewritten during initialization.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMGCR1 . CRINIT
 */
#define  VTSS_F_DDR_PHY_RDIMMGCR1_CRINIT(x)   VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DDR_PHY_RDIMMGCR1_CRINIT      VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DDR_PHY_RDIMMGCR1_CRINIT(x)   VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief RDIMM Control Register 0 (DDR3)
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:RDIMMCR0
 */
#define VTSS_DDR_PHY_RDIMMCR0                VTSS_IOREG(VTSS_TO_DDR_PHY,0x2e)

/**
 * \brief
 * Control Word 0 (Global Features Control Word): Bit definitions
 * are:RC0[0]: 0 = Output inversion enabled, 1 = Output inversion
 * disabled.RC0[1]: 0 = Floating outputs disabled, 1 = Floating outputs
 * enabled.RC0[2]: 0 = A outputs enabled, 1 = A outputs disabled.RC0[3]: 0
 * = B outputs enabled, 1 = B outputs disabled.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMCR0 . RC0
 */
#define  VTSS_F_DDR_PHY_RDIMMCR0_RC0(x)       VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_PHY_RDIMMCR0_RC0          VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_PHY_RDIMMCR0_RC0(x)       VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Control Word 1 (Clock Driver Enable Control Word): Bit definitions
 * are:RC1[0]: 0 = Y0/Y0# clock enabled, 1 = Y0/Y0# clock disabled.RC1[1]:
 * 0 = Y1/Y1# clock enabled, 1 = Y1/Y1# clock disabled.RC1[2]: 0 = Y2/Y2#
 * clock enabled, 1 = Y2/Y2# clock disabled.RC1[3]: 0 = Y3/Y3# clock
 * enabled, 1 = Y3/Y3# clock disabled.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMCR0 . RC1
 */
#define  VTSS_F_DDR_PHY_RDIMMCR0_RC1(x)       VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_DDR_PHY_RDIMMCR0_RC1          VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_DDR_PHY_RDIMMCR0_RC1(x)       VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * Control Word 2 (Timing Control Word): Bit definitions are:RC2[0]: 0 =
 * Standard (1/2 clock) pre-launch, 1 = Prelaunch controlled by
 * RC12.RC2[1]: 0 = Reserved.RC2[2]: 0 = 100 Ohm input bus termination, 1 =
 * 150 Ohm input bus termination.RC2[3]: 0 = Operation frequency band 1, 1
 * = Test mode frequency band 2.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMCR0 . RC2
 */
#define  VTSS_F_DDR_PHY_RDIMMCR0_RC2(x)       VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_PHY_RDIMMCR0_RC2          VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_PHY_RDIMMCR0_RC2(x)       VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * Control Word 3 (Command/Address Signals Driver Characteristics Control
 * Word):RC3[1:0] is driver settings for command/address A outputs, and
 * RC3[3:2] is driversettings for command/address B outputs. Bit
 * definitions are:00 = Light drive (4 or 5 DRAM loads)01 = Moderate drive
 * (8 or 10 DRAM loads)10 = Strong drive (16 or 20 DRAM loads)11 = Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMCR0 . RC3
 */
#define  VTSS_F_DDR_PHY_RDIMMCR0_RC3(x)       VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_DDR_PHY_RDIMMCR0_RC3          VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_DDR_PHY_RDIMMCR0_RC3(x)       VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * Control Word 4 (Control Signals Driver Characteristics Control Word):
 * RC4[1:0] isdriver settings for control A outputs, and RC4[3:2] is driver
 * settings for control Boutputs. Bit definitions are:00 = Light drive (4
 * or 5 DRAM loads)01 = Moderate drive (8 or 10 DRAM loads)10 = Reserved11
 * = Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMCR0 . RC4
 */
#define  VTSS_F_DDR_PHY_RDIMMCR0_RC4(x)       VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DDR_PHY_RDIMMCR0_RC4          VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DDR_PHY_RDIMMCR0_RC4(x)       VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Control Word 5 (CK Driver Characteristics Control Word): RC5[1:0] is
 * driver settingsfor clock Y1, Y1#, Y3, and Y3# outputs, and RC5[3:2] is
 * driver settings for clock Y0,Y0#, Y2, and Y2# outputs. Bit definitions
 * are:00 = Light drive (4 or 5 DRAM loads)01 = Moderate drive (8 or 10
 * DRAM loads)10 = Strong drive (16 or 20 DRAM loads)11 = Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMCR0 . RC5
 */
#define  VTSS_F_DDR_PHY_RDIMMCR0_RC5(x)       VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_DDR_PHY_RDIMMCR0_RC5          VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_DDR_PHY_RDIMMCR0_RC5(x)       VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * Control Word 6: Reserved, free to use by vendor.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMCR0 . RC6
 */
#define  VTSS_F_DDR_PHY_RDIMMCR0_RC6(x)       VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_PHY_RDIMMCR0_RC6          VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_PHY_RDIMMCR0_RC6(x)       VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * Control Word 7: Reserved, free to use by vendor.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMCR0 . RC7
 */
#define  VTSS_F_DDR_PHY_RDIMMCR0_RC7(x)       VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_DDR_PHY_RDIMMCR0_RC7          VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_DDR_PHY_RDIMMCR0_RC7(x)       VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief RDIMM Control Register 1 (DDR3)
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:RDIMMCR1
 */
#define VTSS_DDR_PHY_RDIMMCR1                VTSS_IOREG(VTSS_TO_DDR_PHY,0x2f)

/**
 * \brief
 * Control Word 8 (Additional Input Bus Termination Setting Control
 * Word):RC8[2:0] is Input Bus Termination (IBT) setting as follows:000 =
 * IBT as defined in RC2.001 = Reserved010 = 200 Ohm011 = Reserved100 = 300
 * Ohm101 = Reserved110 = Reserved111 = OffRC8[3]: 0 = IBT off when MIRROR
 * is HIGH, 1 = IBT on when MIRROR is high
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMCR1 . RC8
 */
#define  VTSS_F_DDR_PHY_RDIMMCR1_RC8(x)       VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_PHY_RDIMMCR1_RC8          VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_PHY_RDIMMCR1_RC8(x)       VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Control Word 9 (Power Saving Settings Control Word): Bit definitions
 * are:RC9[0]: 0 = Floating outputs as defined in RC0, 1 = Weak drive
 * enabled.RC9[1]: 0 = Reserved.RC9[2]: 0 = CKE power down with IBT ON,
 * QxODT is a function of DxODT, 1 =CKE power down with IBT off, QxODT held
 * LOW. RC9[2] is valid only when RC9[3]is 1.RC9[3]: 0 = CKE power down
 * mode disabled, 1 = CKE power down mode enabled
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMCR1 . RC9
 */
#define  VTSS_F_DDR_PHY_RDIMMCR1_RC9(x)       VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_DDR_PHY_RDIMMCR1_RC9          VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_DDR_PHY_RDIMMCR1_RC9(x)       VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * Control Word 10 (RDIMM Operating Speed Control Word):RC10[2:0] is RDIMM
 * operating speed setting as follows:000 = DDR3/DDR3L-800001 =
 * DDR3/DDR3L-1066010 = DDR3/DDR3L-1333011 = DDR3/DDR3L-1600100 =
 * Reserved101 = Reserved110 = Reserved111 = ReservedRC10[3]: Don't care.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMCR1 . RC10
 */
#define  VTSS_F_DDR_PHY_RDIMMCR1_RC10(x)      VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_PHY_RDIMMCR1_RC10         VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_PHY_RDIMMCR1_RC10(x)      VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * Control Word 11 (Operating Voltage VDD Control Word):RC10[1:0] is VDD
 * operating voltage setting as follows:00 = DDR3 1.5V mode01 = DDR3L 1.35V
 * mode10 = Reserved11 = ReservedRC10[3:2]: Reserved.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMCR1 . RC11
 */
#define  VTSS_F_DDR_PHY_RDIMMCR1_RC11(x)      VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_DDR_PHY_RDIMMCR1_RC11         VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_DDR_PHY_RDIMMCR1_RC11(x)      VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * Control Word 12: Reserved for future use.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMCR1 . RC12
 */
#define  VTSS_F_DDR_PHY_RDIMMCR1_RC12(x)      VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DDR_PHY_RDIMMCR1_RC12         VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DDR_PHY_RDIMMCR1_RC12(x)      VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Control Word 13: Reserved for future use.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMCR1 . RC13
 */
#define  VTSS_F_DDR_PHY_RDIMMCR1_RC13(x)      VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_DDR_PHY_RDIMMCR1_RC13         VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_DDR_PHY_RDIMMCR1_RC13(x)      VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * Control Word 14: Reserved for future use.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMCR1 . RC14
 */
#define  VTSS_F_DDR_PHY_RDIMMCR1_RC14(x)      VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_PHY_RDIMMCR1_RC14         VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_PHY_RDIMMCR1_RC14(x)      VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * Control Word 15: Reserved for future use.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_RDIMMCR1 . RC15
 */
#define  VTSS_F_DDR_PHY_RDIMMCR1_RC15(x)      VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_DDR_PHY_RDIMMCR1_RC15         VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_DDR_PHY_RDIMMCR1_RC15(x)      VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief DCU Address Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DCUAR
 */
#define VTSS_DDR_PHY_DCUAR                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x30)

/**
 * \brief
 * Cache Word Address: Address of the cache word to be accessed.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCUAR . CWADDR
 */
#define  VTSS_F_DDR_PHY_DCUAR_CWADDR(x)       VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_PHY_DCUAR_CWADDR          VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_PHY_DCUAR_CWADDR(x)       VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Cache Slice Address: Address of the cache slice to be accessed.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCUAR . CSADDR
 */
#define  VTSS_F_DDR_PHY_DCUAR_CSADDR(x)       VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_DDR_PHY_DCUAR_CSADDR          VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_DDR_PHY_DCUAR_CSADDR(x)       VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * Cache Select: Selects the cache to be accessed. Valid values are:00 =
 * Command cache01 = Expected data cache10 = Read data cache11 = Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCUAR . CSEL
 */
#define  VTSS_F_DDR_PHY_DCUAR_CSEL(x)         VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_DDR_PHY_DCUAR_CSEL            VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_DDR_PHY_DCUAR_CSEL(x)         VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * Increment Address: Specifies, if set, that the cache address specified
 * in WADDRand SADDR should be automatically incremented after each access
 * of the cache.The increment happens in such a way that all the slices of
 * a selected word are firstaccessed before going to the next word.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCUAR . INCA
 */
#define  VTSS_F_DDR_PHY_DCUAR_INCA(x)         VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_DDR_PHY_DCUAR_INCA            VTSS_BIT(10)
#define  VTSS_X_DDR_PHY_DCUAR_INCA(x)         VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Access Type: Specifies the type of access to be performed using this
 * address. Validvalues are:0 = Write access1 = Read access
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCUAR . ATYPE
 */
#define  VTSS_F_DDR_PHY_DCUAR_ATYPE(x)        VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_DDR_PHY_DCUAR_ATYPE           VTSS_BIT(11)
#define  VTSS_X_DDR_PHY_DCUAR_ATYPE(x)        VTSS_EXTRACT_BITFIELD(x,11,1)


/**
 * \brief DCU Data Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DCUDR
 */
#define VTSS_DDR_PHY_DCUDR                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x31)

/**
 * \brief
 * Cache Data: Data to be written to or read from a cache. This data
 * corresponds tothe cache word slice specified by the DCU Address
 * Register.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCUDR . CDATA
 */
#define  VTSS_F_DDR_PHY_DCUDR_CDATA(x)        (x)
#define  VTSS_M_DDR_PHY_DCUDR_CDATA           0xffffffff
#define  VTSS_X_DDR_PHY_DCUDR_CDATA(x)        (x)


/**
 * \brief DCU Run Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DCURR
 */
#define VTSS_DDR_PHY_DCURR                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x32)

/**
 * \brief
 * DCU Instruction: Selects the DCU command to be executed: Valid values
 * are:0000 = NOP: No operation0001 = Run: Triggers the execution of
 * commands in the command cache.0010 = Stop: Stops the execution of
 * commands in the command cache.0011 = Stop Loop: Stops the execution of
 * an infinite loop in the command cache.0100 = Reset: Resets all DCU run
 * time registers. 0101 - 1111 Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCURR . DINST
 */
#define  VTSS_F_DDR_PHY_DCURR_DINST(x)        VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_PHY_DCURR_DINST           VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_PHY_DCURR_DINST(x)        VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Start Address: Cache word address where the execution of commands
 * shouldbegin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCURR . SADDR
 */
#define  VTSS_F_DDR_PHY_DCURR_SADDR(x)        VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_DDR_PHY_DCURR_SADDR           VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_DDR_PHY_DCURR_SADDR(x)        VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * End Address: Cache word address where the execution of command should
 * end.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCURR . EADDR
 */
#define  VTSS_F_DDR_PHY_DCURR_EADDR(x)        VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_PHY_DCURR_EADDR           VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_PHY_DCURR_EADDR(x)        VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * Number of Failures: Specifies the number of failures after which the
 * execution ofcommands and the capture of read data should stop if SONF
 * bit of this register isset. Execution of commands and the capture of
 * read data will stop after (NFAIL+1)failures if SONF is set.Valid values
 * are from 0 to 254.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCURR . DCURR_NFAIL
 */
#define  VTSS_F_DDR_PHY_DCURR_DCURR_NFAIL(x)  VTSS_ENCODE_BITFIELD(x,12,8)
#define  VTSS_M_DDR_PHY_DCURR_DCURR_NFAIL     VTSS_ENCODE_BITMASK(12,8)
#define  VTSS_X_DDR_PHY_DCURR_DCURR_NFAIL(x)  VTSS_EXTRACT_BITFIELD(x,12,8)

/**
 * \brief
 * Stop On Nth Fail: Specifies, if set, that the execution of commands and
 * the captureof read data should stop when there are N read data failures.
 * The number of failuresis specified by NFAIL. Otherwise commands execute
 * until the end of the program oruntil manually stopped using a STOP
 * command.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCURR . SONF
 */
#define  VTSS_F_DDR_PHY_DCURR_SONF(x)         VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_DDR_PHY_DCURR_SONF            VTSS_BIT(20)
#define  VTSS_X_DDR_PHY_DCURR_SONF(x)         VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Stop Capture On Full: Specifies, if set, that the capture of read data
 * should stopwhen the capture cache is full.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCURR . SCOF
 */
#define  VTSS_F_DDR_PHY_DCURR_SCOF(x)         VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_DDR_PHY_DCURR_SCOF            VTSS_BIT(21)
#define  VTSS_X_DDR_PHY_DCURR_SCOF(x)         VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Read Capture Enable: Indicates, if set, that read data coming back from
 * theSDRAM should be captured into the read data cache.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCURR . RCEN
 */
#define  VTSS_F_DDR_PHY_DCURR_RCEN(x)         VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_DDR_PHY_DCURR_RCEN            VTSS_BIT(22)
#define  VTSS_X_DDR_PHY_DCURR_RCEN(x)         VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Expected Compare Enable: Indicates, if set, that read data coming back
 * from theSDRAM should be should be compared with the expected data.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCURR . XCEN
 */
#define  VTSS_F_DDR_PHY_DCURR_XCEN(x)         VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_DDR_PHY_DCURR_XCEN            VTSS_BIT(23)
#define  VTSS_X_DDR_PHY_DCURR_XCEN(x)         VTSS_EXTRACT_BITFIELD(x,23,1)


/**
 * \brief DCU Loop Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DCULR
 */
#define VTSS_DDR_PHY_DCULR                   VTSS_IOREG(VTSS_TO_DDR_PHY,0x33)

/**
 * \brief
 * Loop Start Address: Command cache word address where the loop should
 * start.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCULR . LSADDR
 */
#define  VTSS_F_DDR_PHY_DCULR_LSADDR(x)       VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_PHY_DCULR_LSADDR          VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_PHY_DCULR_LSADDR(x)       VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Loop End Address: Command cache word address where the loop should end.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCULR . LEADDR
 */
#define  VTSS_F_DDR_PHY_DCULR_LEADDR(x)       VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_DDR_PHY_DCULR_LEADDR          VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_DDR_PHY_DCULR_LEADDR(x)       VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * Loop Count: The number of times that the loop should be executed if LINF
 * is notset.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCULR . LCNT
 */
#define  VTSS_F_DDR_PHY_DCULR_LCNT(x)         VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DDR_PHY_DCULR_LCNT            VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DDR_PHY_DCULR_LCNT(x)         VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Loop Infinite: Indicates, if set, that the loop should be executed
 * indefinitely untilstopped by the STOP command. Otherwise the loop is
 * execute LCNT times.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCULR . LINF
 */
#define  VTSS_F_DDR_PHY_DCULR_LINF(x)         VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DDR_PHY_DCULR_LINF            VTSS_BIT(16)
#define  VTSS_X_DDR_PHY_DCULR_LINF(x)         VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Increment DRAM Address: Indicates, if set, that DRAM addresses should
 * beincremented every time a DRAM read/write command inside the loop is
 * executed.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCULR . IDA
 */
#define  VTSS_F_DDR_PHY_DCULR_IDA(x)          VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_DDR_PHY_DCULR_IDA             VTSS_BIT(17)
#define  VTSS_X_DDR_PHY_DCULR_IDA(x)          VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Expected Data Loop End Address: The last expected data cache word
 * address thatcontains valid expected data. Expected data should looped
 * between 0 and thisaddress.XLEADDR field uses only the following bits
 * based on the cache depth:> DCU expected data cache = 4, XLEADDR[1:0]>
 * DCU expected data cache = 8, XLEADDR[2:0]> DCU expected data cache = 16,
 * XLEADDR[3:0]
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCULR . XLEADDR
 */
#define  VTSS_F_DDR_PHY_DCULR_XLEADDR(x)      VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_DDR_PHY_DCULR_XLEADDR         VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_DDR_PHY_DCULR_XLEADDR(x)      VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief DCU Generation Configuration Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DCUGCR
 */
#define VTSS_DDR_PHY_DCUGCR                  VTSS_IOREG(VTSS_TO_DDR_PHY,0x34)

/**
 * \brief
 * Read Capture Start Word: The capture and compare of read data should
 * start afterNth word. For example setting this value to 12 will skip the
 * first 12 read data.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCUGCR . RCSW
 */
#define  VTSS_F_DDR_PHY_DCUGCR_RCSW(x)        VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_PHY_DCUGCR_RCSW           VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_PHY_DCUGCR_RCSW(x)        VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief DCU Timing Parameter Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DCUTPR
 */
#define VTSS_DDR_PHY_DCUTPR                  VTSS_IOREG(VTSS_TO_DDR_PHY,0x35)

/**
 * \brief
 * DCU Generic Timing Parameter 0.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCUTPR . TDCUT0
 */
#define  VTSS_F_DDR_PHY_DCUTPR_TDCUT0(x)      VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_PHY_DCUTPR_TDCUT0         VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_PHY_DCUTPR_TDCUT0(x)      VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * DCU Generic Timing Parameter 1.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCUTPR . TDCUT1
 */
#define  VTSS_F_DDR_PHY_DCUTPR_TDCUT1(x)      VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DDR_PHY_DCUTPR_TDCUT1         VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DDR_PHY_DCUTPR_TDCUT1(x)      VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * DCU Generic Timing Parameter 2.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCUTPR . TDCUT2
 */
#define  VTSS_F_DDR_PHY_DCUTPR_TDCUT2(x)      VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_PHY_DCUTPR_TDCUT2         VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_PHY_DCUTPR_TDCUT2(x)      VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * DCU Generic Timing Parameter 3.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCUTPR . TDCUT3
 */
#define  VTSS_F_DDR_PHY_DCUTPR_TDCUT3(x)      VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DDR_PHY_DCUTPR_TDCUT3         VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DDR_PHY_DCUTPR_TDCUT3(x)      VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief DCU Status Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DCUSR0
 */
#define VTSS_DDR_PHY_DCUSR0                  VTSS_IOREG(VTSS_TO_DDR_PHY,0x36)

/**
 * \brief
 * Run Done: Indicates, if set, that the DCU has finished executing the
 * commands inthe command cache. This bit is also set to indicate that a
 * STOP command hassuccessfully been executed and command execution has
 * stopped.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCUSR0 . RDONE
 */
#define  VTSS_F_DDR_PHY_DCUSR0_RDONE(x)       VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_DCUSR0_RDONE          VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_DCUSR0_RDONE(x)       VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Capture Fail: Indicates, if set, that at least one read data word has
 * failed.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCUSR0 . CFAIL
 */
#define  VTSS_F_DDR_PHY_DCUSR0_CFAIL(x)       VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_PHY_DCUSR0_CFAIL          VTSS_BIT(1)
#define  VTSS_X_DDR_PHY_DCUSR0_CFAIL(x)       VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Capture Full: Indicates, if set, that the capture cache is full.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCUSR0 . CFULL
 */
#define  VTSS_F_DDR_PHY_DCUSR0_CFULL(x)       VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_PHY_DCUSR0_CFULL          VTSS_BIT(2)
#define  VTSS_X_DDR_PHY_DCUSR0_CFULL(x)       VTSS_EXTRACT_BITFIELD(x,2,1)


/**
 * \brief DCU Status Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DCUSR1
 */
#define VTSS_DDR_PHY_DCUSR1                  VTSS_IOREG(VTSS_TO_DDR_PHY,0x37)

/**
 * \brief
 * Read Count: Number of read words returned from the SDRAM.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCUSR1 . RDCNT
 */
#define  VTSS_F_DDR_PHY_DCUSR1_RDCNT(x)       VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_PHY_DCUSR1_RDCNT          VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_PHY_DCUSR1_RDCNT(x)       VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Fail Count: Number of read words that have failed.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCUSR1 . FLCNT
 */
#define  VTSS_F_DDR_PHY_DCUSR1_FLCNT(x)       VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_PHY_DCUSR1_FLCNT          VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_PHY_DCUSR1_FLCNT(x)       VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Loop Count: Indicates the value of the loop count. This is useful when
 * the programhas stopped because of failures to assess how many reads were
 * executed beforefirst fail.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DCUSR1 . LPCNT
 */
#define  VTSS_F_DDR_PHY_DCUSR1_LPCNT(x)       VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DDR_PHY_DCUSR1_LPCNT          VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DDR_PHY_DCUSR1_LPCNT(x)       VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief BIST Run Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:BISTRR
 */
#define VTSS_DDR_PHY_BISTRR                  VTSS_IOREG(VTSS_TO_DDR_PHY,0x40)

/**
 * \brief
 * BIST Instruction: Selects the BIST instruction to be executed: Valid
 * values are:000 = NOP: No operation001 = Run: Triggers the running of the
 * BIST.010 = Stop: Stops the running of the BIST.011 = Reset: Resets all
 * BIST run-time registers, such as error counters.100 - 111 Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTRR . BINST
 */
#define  VTSS_F_DDR_PHY_BISTRR_BINST(x)       VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_DDR_PHY_BISTRR_BINST          VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_DDR_PHY_BISTRR_BINST(x)       VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * BIST Mode: Selects the mode in which BIST is run. Valid values are:0 =
 * Loopback mode: Address, commands and data loop back at the PHY I/Os.1 =
 * DRAM mode: Address, commands and data go to DRAM for normal
 * memoryaccesses.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTRR . BMODE
 */
#define  VTSS_F_DDR_PHY_BISTRR_BMODE(x)       VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_PHY_BISTRR_BMODE          VTSS_BIT(3)
#define  VTSS_X_DDR_PHY_BISTRR_BMODE(x)       VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * BIST Infinite Run: Specifies, if set, that the BIST should be run
 * indefinitely untilwhen it is either stopped or a failure has been
 * encountered. Otherwise BIST is rununtil number of BIST words specified
 * in the BISTWCR register has been generated.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTRR . BINF
 */
#define  VTSS_F_DDR_PHY_BISTRR_BINF(x)        VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_PHY_BISTRR_BINF           VTSS_BIT(4)
#define  VTSS_X_DDR_PHY_BISTRR_BINF(x)        VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Number of Failures: Specifies the number of failures after which the
 * execution ofcommands and the capture of read data should stop if BSONF
 * bit of this register isset. Execution of commands and the capture of
 * read data will stop after (NFAIL+1)failures if BSONF is set.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTRR . BISTRR_NFAIL
 */
#define  VTSS_F_DDR_PHY_BISTRR_BISTRR_NFAIL(x)  VTSS_ENCODE_BITFIELD(x,5,8)
#define  VTSS_M_DDR_PHY_BISTRR_BISTRR_NFAIL     VTSS_ENCODE_BITMASK(5,8)
#define  VTSS_X_DDR_PHY_BISTRR_BISTRR_NFAIL(x)  VTSS_EXTRACT_BITFIELD(x,5,8)

/**
 * \brief
 * BIST Stop On Nth Fail: Specifies, if set, that the BIST should stop when
 * an nth dataword or address/command comparison error has been
 * encountered.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTRR . BSONF
 */
#define  VTSS_F_DDR_PHY_BISTRR_BSONF(x)       VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DDR_PHY_BISTRR_BSONF          VTSS_BIT(13)
#define  VTSS_X_DDR_PHY_BISTRR_BSONF(x)       VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * BIST DATX8 Enable: Enables the running of BIST on the data byte lane
 * PHYs. Thisbit is exclusive with BACEN, i.e. both cannot be set to '1' at
 * the same time.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTRR . BDXEN
 */
#define  VTSS_F_DDR_PHY_BISTRR_BDXEN(x)       VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_DDR_PHY_BISTRR_BDXEN          VTSS_BIT(14)
#define  VTSS_X_DDR_PHY_BISTRR_BDXEN(x)       VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * BIST AC Enable: Enables the running of BIST on the address/command lane
 * PHY.This bit is exclusive with BDXEN, i.e. both cannot be set to '1' at
 * the same time.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTRR . BACEN
 */
#define  VTSS_F_DDR_PHY_BISTRR_BACEN(x)       VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_DDR_PHY_BISTRR_BACEN          VTSS_BIT(15)
#define  VTSS_X_DDR_PHY_BISTRR_BACEN(x)       VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * BIST Data Mask Enable: Enables, if set, that the data mask BIST should
 * beincluded in the BIST run, i.e. data pattern generated and loopback
 * data compared.This is valid only for loopback mode.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTRR . BDMEN
 */
#define  VTSS_F_DDR_PHY_BISTRR_BDMEN(x)       VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DDR_PHY_BISTRR_BDMEN          VTSS_BIT(16)
#define  VTSS_X_DDR_PHY_BISTRR_BDMEN(x)       VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * BIST Data Pattern: Selects the data pattern used during BIST. Valid
 * values are:00 = Walking 001 = Walking 110 = LFSR-based pseudo-random11 =
 * User programmable (Not valid for AC loopback).
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTRR . BDPAT
 */
#define  VTSS_F_DDR_PHY_BISTRR_BDPAT(x)       VTSS_ENCODE_BITFIELD(x,17,2)
#define  VTSS_M_DDR_PHY_BISTRR_BDPAT          VTSS_ENCODE_BITMASK(17,2)
#define  VTSS_X_DDR_PHY_BISTRR_BDPAT(x)       VTSS_EXTRACT_BITFIELD(x,17,2)

/**
 * \brief
 * BIST DATX8 Select: Select the byte lane for comparison of loopback/read
 * data.Valid values are 0 to 8.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTRR . BDXSEL
 */
#define  VTSS_F_DDR_PHY_BISTRR_BDXSEL(x)      VTSS_ENCODE_BITFIELD(x,19,4)
#define  VTSS_M_DDR_PHY_BISTRR_BDXSEL         VTSS_ENCODE_BITMASK(19,4)
#define  VTSS_X_DDR_PHY_BISTRR_BDXSEL(x)      VTSS_EXTRACT_BITFIELD(x,19,4)

/**
 * \brief
 * BIST CK Select: Selects the CK that should be used to register the AC
 * loopbacksignals from the I/Os. Valid values are:00 = CK[0]01 = CK[1]10 =
 * CK[2]11 = Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTRR . BCKSEL
 */
#define  VTSS_F_DDR_PHY_BISTRR_BCKSEL(x)      VTSS_ENCODE_BITFIELD(x,23,2)
#define  VTSS_M_DDR_PHY_BISTRR_BCKSEL         VTSS_ENCODE_BITMASK(23,2)
#define  VTSS_X_DDR_PHY_BISTRR_BCKSEL(x)      VTSS_EXTRACT_BITFIELD(x,23,2)

/**
 * \brief
 * BIST Clock Cycle Select: Selects the clock numbers on which the AC
 * loopback datais written into the FIFO. Data is written into the loopback
 * FIFO once every four clockcycles. Valid values are:00 = Clock cycle 0,
 * 4, 8, 12, etc.01 = Clock cycle 1, 5, 9, 13, etc.10 = Clock cycle 2, 6,
 * 10, 14, etc.11 = Clock cycle 3, 7, 11, 15, etc.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTRR . BCCSEL
 */
#define  VTSS_F_DDR_PHY_BISTRR_BCCSEL(x)      VTSS_ENCODE_BITFIELD(x,25,2)
#define  VTSS_M_DDR_PHY_BISTRR_BCCSEL         VTSS_ENCODE_BITMASK(25,2)
#define  VTSS_X_DDR_PHY_BISTRR_BCCSEL(x)      VTSS_EXTRACT_BITFIELD(x,25,2)


/**
 * \brief BIST Word Count Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:BISTWCR
 */
#define VTSS_DDR_PHY_BISTWCR                 VTSS_IOREG(VTSS_TO_DDR_PHY,0x41)

/**
 * \brief
 * BIST Word Count: Indicates the number of words to generate during BIST.
 * Thismust be a multiple of DRAM burst length (BL) divided by 2, e.g. for
 * BL=8, validvalues are 4, 8, 12, 16, and so on.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTWCR . BWCNT
 */
#define  VTSS_F_DDR_PHY_BISTWCR_BWCNT(x)      VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_PHY_BISTWCR_BWCNT         VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_PHY_BISTWCR_BWCNT(x)      VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief BIST Mask Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:BISTMSKR0
 */
#define VTSS_DDR_PHY_BISTMSKR0               VTSS_IOREG(VTSS_TO_DDR_PHY,0x42)

/**
 * \brief
 * Mask bit for each of the up to 16 address bits.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTMSKR0 . AMSK
 */
#define  VTSS_F_DDR_PHY_BISTMSKR0_AMSK(x)     VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_PHY_BISTMSKR0_AMSK        VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_PHY_BISTMSKR0_AMSK(x)     VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Mask bit for each of the up to 3 bank address bits
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTMSKR0 . BAMSK
 */
#define  VTSS_F_DDR_PHY_BISTMSKR0_BAMSK(x)    VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_DDR_PHY_BISTMSKR0_BAMSK       VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_DDR_PHY_BISTMSKR0_BAMSK(x)    VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * Mask bit for the WE#.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTMSKR0 . WEMSK
 */
#define  VTSS_F_DDR_PHY_BISTMSKR0_WEMSK(x)    VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_DDR_PHY_BISTMSKR0_WEMSK       VTSS_BIT(19)
#define  VTSS_X_DDR_PHY_BISTMSKR0_WEMSK(x)    VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Mask bit for each of the up to 4 CKE bits.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTMSKR0 . CKEMSK
 */
#define  VTSS_F_DDR_PHY_BISTMSKR0_CKEMSK(x)   VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_DDR_PHY_BISTMSKR0_CKEMSK      VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_DDR_PHY_BISTMSKR0_CKEMSK(x)   VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * Mask bit for each of the up to 4 CS# bits.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTMSKR0 . CSMSK
 */
#define  VTSS_F_DDR_PHY_BISTMSKR0_CSMSK(x)    VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_PHY_BISTMSKR0_CSMSK       VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_PHY_BISTMSKR0_CSMSK(x)    VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * Mask bit for each of the up to 4 ODT bits.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTMSKR0 . ODTMSK
 */
#define  VTSS_F_DDR_PHY_BISTMSKR0_ODTMSK(x)   VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_DDR_PHY_BISTMSKR0_ODTMSK      VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_DDR_PHY_BISTMSKR0_ODTMSK(x)   VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief BIST Mask Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:BISTMSKR1
 */
#define VTSS_DDR_PHY_BISTMSKR1               VTSS_IOREG(VTSS_TO_DDR_PHY,0x43)

/**
 * \brief
 * Mask bit for the RAS
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTMSKR1 . RASMSK
 */
#define  VTSS_F_DDR_PHY_BISTMSKR1_RASMSK(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_BISTMSKR1_RASMSK      VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_BISTMSKR1_RASMSK(x)   VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Mask bit for the CAS
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTMSKR1 . CASMSK
 */
#define  VTSS_F_DDR_PHY_BISTMSKR1_CASMSK(x)   VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_PHY_BISTMSKR1_CASMSK      VTSS_BIT(1)
#define  VTSS_X_DDR_PHY_BISTMSKR1_CASMSK(x)   VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Mask bit for the PAR_IN. Only for DIMM parity support and only if the
 * design iscompiled for less than 3 ranks
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTMSKR1 . PARMSK
 */
#define  VTSS_F_DDR_PHY_BISTMSKR1_PARMSK(x)   VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_DDR_PHY_BISTMSKR1_PARMSK      VTSS_BIT(27)
#define  VTSS_X_DDR_PHY_BISTMSKR1_PARMSK(x)   VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Mask bit for the data mask (DM) bit.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTMSKR1 . DMMSK
 */
#define  VTSS_F_DDR_PHY_BISTMSKR1_DMMSK(x)    VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_DDR_PHY_BISTMSKR1_DMMSK       VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_DDR_PHY_BISTMSKR1_DMMSK(x)    VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief BIST Mask Register 2
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:BISTMSKR2
 */
#define VTSS_DDR_PHY_BISTMSKR2               VTSS_IOREG(VTSS_TO_DDR_PHY,0x44)

/**
 * \brief
 * Mask bit for each of the 8 data (DQ) bits.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTMSKR2 . DQMSK
 */
#define  VTSS_F_DDR_PHY_BISTMSKR2_DQMSK(x)    (x)
#define  VTSS_M_DDR_PHY_BISTMSKR2_DQMSK       0xffffffff
#define  VTSS_X_DDR_PHY_BISTMSKR2_DQMSK(x)    (x)


/**
 * \brief BIST LFSR Seed Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:BISTLSR
 */
#define VTSS_DDR_PHY_BISTLSR                 VTSS_IOREG(VTSS_TO_DDR_PHY,0x45)

/**
 * \brief
 * LFSR seed for pseudo-random BIST patterns
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTLSR . SEED
 */
#define  VTSS_F_DDR_PHY_BISTLSR_SEED(x)       (x)
#define  VTSS_M_DDR_PHY_BISTLSR_SEED          0xffffffff
#define  VTSS_X_DDR_PHY_BISTLSR_SEED(x)       (x)


/**
 * \brief BIST Address Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:BISTAR0
 */
#define VTSS_DDR_PHY_BISTAR0                 VTSS_IOREG(VTSS_TO_DDR_PHY,0x46)

/**
 * \brief
 * BIST Column Address: Selects the SDRAM column address to be used
 * duringBIST. The lower bits of this address must be "0000" for BL16,
 * "000" for BL8, "00" forBL4 and "0" for BL2.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTAR0 . BCOL
 */
#define  VTSS_F_DDR_PHY_BISTAR0_BCOL(x)       VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_PHY_BISTAR0_BCOL          VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_PHY_BISTAR0_BCOL(x)       VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * BIST Row Address: Selects the SDRAM row address to be used during BIST.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTAR0 . BROW
 */
#define  VTSS_F_DDR_PHY_BISTAR0_BROW(x)       VTSS_ENCODE_BITFIELD(x,12,16)
#define  VTSS_M_DDR_PHY_BISTAR0_BROW          VTSS_ENCODE_BITMASK(12,16)
#define  VTSS_X_DDR_PHY_BISTAR0_BROW(x)       VTSS_EXTRACT_BITFIELD(x,12,16)

/**
 * \brief
 * BIST Bank Address: Selects the SDRAM bank address to be used during BIST
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTAR0 . BBANK
 */
#define  VTSS_F_DDR_PHY_BISTAR0_BBANK(x)      VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_DDR_PHY_BISTAR0_BBANK         VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_DDR_PHY_BISTAR0_BBANK(x)      VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief BIST Address Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:BISTAR1
 */
#define VTSS_DDR_PHY_BISTAR1                 VTSS_IOREG(VTSS_TO_DDR_PHY,0x47)

/**
 * \brief
 * BIST Rank: Selects the SDRAM rank to be used during BIST. Valid values
 * rangefrom 0 to maximum ranks minus 1
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTAR1 . BRANK
 */
#define  VTSS_F_DDR_PHY_BISTAR1_BRANK(x)      VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DDR_PHY_BISTAR1_BRANK         VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DDR_PHY_BISTAR1_BRANK(x)      VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * BIST Maximum Rank: Specifies the maximum SDRAM rank to be used during
 * BIST.The default value is set to maximum ranks minus 1. Example default
 * shown here isfor a 4-rank system
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTAR1 . BMRANK
 */
#define  VTSS_F_DDR_PHY_BISTAR1_BMRANK(x)     VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_DDR_PHY_BISTAR1_BMRANK        VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_DDR_PHY_BISTAR1_BMRANK(x)     VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * BIST Address Increment: Selects the value by which the SDRAM address
 * isincremented for each write/read access. This value must be at the
 * beginning of aburst boundary, i.e. the lower bits must be "0000" for
 * BL16, "000" for BL8, "00" forBL4 and "0" for BL2.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTAR1 . BAINC
 */
#define  VTSS_F_DDR_PHY_BISTAR1_BAINC(x)      VTSS_ENCODE_BITFIELD(x,4,12)
#define  VTSS_M_DDR_PHY_BISTAR1_BAINC         VTSS_ENCODE_BITMASK(4,12)
#define  VTSS_X_DDR_PHY_BISTAR1_BAINC(x)      VTSS_EXTRACT_BITFIELD(x,4,12)


/**
 * \brief BIST Address Register 2
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:BISTAR2
 */
#define VTSS_DDR_PHY_BISTAR2                 VTSS_IOREG(VTSS_TO_DDR_PHY,0x48)

/**
 * \brief
 * BIST Maximum Column Address: Specifies the maximum SDRAM column
 * addressto be used during BIST before the address increments to the next
 * row.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTAR2 . BMCOL
 */
#define  VTSS_F_DDR_PHY_BISTAR2_BMCOL(x)      VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_PHY_BISTAR2_BMCOL         VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_PHY_BISTAR2_BMCOL(x)      VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * BIST Maximum Row Address: Specifies the maximum SDRAM row address to
 * beused during BIST before the address increments to the next bank.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTAR2 . BMROW
 */
#define  VTSS_F_DDR_PHY_BISTAR2_BMROW(x)      VTSS_ENCODE_BITFIELD(x,12,16)
#define  VTSS_M_DDR_PHY_BISTAR2_BMROW         VTSS_ENCODE_BITMASK(12,16)
#define  VTSS_X_DDR_PHY_BISTAR2_BMROW(x)      VTSS_EXTRACT_BITFIELD(x,12,16)

/**
 * \brief
 * BIST Maximum Bank Address: Specifies the maximum SDRAM bank address to
 * beused during BIST before the address increments to the next rank.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTAR2 . BMBANK
 */
#define  VTSS_F_DDR_PHY_BISTAR2_BMBANK(x)     VTSS_ENCODE_BITFIELD(x,28,3)
#define  VTSS_M_DDR_PHY_BISTAR2_BMBANK        VTSS_ENCODE_BITMASK(28,3)
#define  VTSS_X_DDR_PHY_BISTAR2_BMBANK(x)     VTSS_EXTRACT_BITFIELD(x,28,3)


/**
 * \brief BIST User Data Pattern Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:BISTUDPR
 */
#define VTSS_DDR_PHY_BISTUDPR                VTSS_IOREG(VTSS_TO_DDR_PHY,0x49)

/**
 * \brief
 * BIST User Data Pattern 0: Data to be applied on even DQ pins during
 * BIST.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTUDPR . BUDP0
 */
#define  VTSS_F_DDR_PHY_BISTUDPR_BUDP0(x)     VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_PHY_BISTUDPR_BUDP0        VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_PHY_BISTUDPR_BUDP0(x)     VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * BIST User Data Pattern 1: Data to be applied on odd DQ pins during BIST.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTUDPR . BUDP1
 */
#define  VTSS_F_DDR_PHY_BISTUDPR_BUDP1(x)     VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DDR_PHY_BISTUDPR_BUDP1        VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DDR_PHY_BISTUDPR_BUDP1(x)     VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief BIST General Status Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:BISTGSR
 */
#define VTSS_DDR_PHY_BISTGSR                 VTSS_IOREG(VTSS_TO_DDR_PHY,0x4a)

/**
 * \brief
 * BIST Done: Indicates, if set, that the BIST has finished executing. This
 * bit is reset tozero when BIST is triggered.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTGSR . BDONE
 */
#define  VTSS_F_DDR_PHY_BISTGSR_BDONE(x)      VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_BISTGSR_BDONE         VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_BISTGSR_BDONE(x)      VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * BIST Address/Command Error: indicates, if set, that there is a data
 * comparisonerror in the address/command lane.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTGSR . BACERR
 */
#define  VTSS_F_DDR_PHY_BISTGSR_BACERR(x)     VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_PHY_BISTGSR_BACERR        VTSS_BIT(1)
#define  VTSS_X_DDR_PHY_BISTGSR_BACERR(x)     VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIST Data Error: indicates, if set, that there is a data comparison
 * error in the bytelane.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTGSR . BDXERR
 */
#define  VTSS_F_DDR_PHY_BISTGSR_BDXERR(x)     VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_PHY_BISTGSR_BDXERR        VTSS_BIT(2)
#define  VTSS_X_DDR_PHY_BISTGSR_BDXERR(x)     VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * PAR_IN Bit Error (DIMM Only): Indicates the number of bit errors on
 * PAR_IN
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTGSR . PARBER
 */
#define  VTSS_F_DDR_PHY_BISTGSR_PARBER(x)     VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_DDR_PHY_BISTGSR_PARBER        VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_DDR_PHY_BISTGSR_PARBER(x)     VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * DM Bit Error: Indicates the number of bit errors on data mask (DM) bit.
 * DMBER[1:0]are for even DQS cycles first DM beat, and DMBER[3:2] are for
 * even DQS cyclessecond DM beat. Similarly, DMBER[5:4] are for odd DQS
 * cycles first DM beat, andDMBER[7:6] are for odd DQS cycles second DM
 * beat.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTGSR . DMBER
 */
#define  VTSS_F_DDR_PHY_BISTGSR_DMBER(x)      VTSS_ENCODE_BITFIELD(x,20,8)
#define  VTSS_M_DDR_PHY_BISTGSR_DMBER         VTSS_ENCODE_BITMASK(20,8)
#define  VTSS_X_DDR_PHY_BISTGSR_DMBER(x)      VTSS_EXTRACT_BITFIELD(x,20,8)

/**
 * \brief
 * RAS Bit Error: Indicates the number of bit errors on RAS.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTGSR . RASBER
 */
#define  VTSS_F_DDR_PHY_BISTGSR_RASBER(x)     VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_DDR_PHY_BISTGSR_RASBER        VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_DDR_PHY_BISTGSR_RASBER(x)     VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * CAS Bit Error: Indicates the number of bit errors on CAS.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTGSR . CASBER
 */
#define  VTSS_F_DDR_PHY_BISTGSR_CASBER(x)     VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_DDR_PHY_BISTGSR_CASBER        VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_DDR_PHY_BISTGSR_CASBER(x)     VTSS_EXTRACT_BITFIELD(x,30,2)


/**
 * \brief BIST Word Error Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:BISTWER
 */
#define VTSS_DDR_PHY_BISTWER                 VTSS_IOREG(VTSS_TO_DDR_PHY,0x4b)

/**
 * \brief
 * Address/Command Word Error: Indicates the number of word errors on
 * theaddress/command lane. An error on any bit of the address/command
 * busincrements the error count
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTWER . ACWER
 */
#define  VTSS_F_DDR_PHY_BISTWER_ACWER(x)      VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_PHY_BISTWER_ACWER         VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_PHY_BISTWER_ACWER(x)      VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Byte Word Error: Indicates the number of word errors on the byte lane.
 * An error onany bit of the data bus including the data mask bit
 * increments the error count
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTWER . DXWER
 */
#define  VTSS_F_DDR_PHY_BISTWER_DXWER(x)      VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DDR_PHY_BISTWER_DXWER         VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DDR_PHY_BISTWER_DXWER(x)      VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief BIST Bit Error Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:BISTBER0
 */
#define VTSS_DDR_PHY_BISTBER0                VTSS_IOREG(VTSS_TO_DDR_PHY,0x4c)

/**
 * \brief
 * Address Bit Error: Each group of two bits indicate the bit error count
 * on each of theup to 16 address bits. [1:0] is the error count for A[0],
 * [3:2] for A[1], and so on.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTBER0 . ABER
 */
#define  VTSS_F_DDR_PHY_BISTBER0_ABER(x)      (x)
#define  VTSS_M_DDR_PHY_BISTBER0_ABER         0xffffffff
#define  VTSS_X_DDR_PHY_BISTBER0_ABER(x)      (x)


/**
 * \brief BIST Bit Error Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:BISTBER1
 */
#define VTSS_DDR_PHY_BISTBER1                VTSS_IOREG(VTSS_TO_DDR_PHY,0x4d)

/**
 * \brief
 * Bank Address Bit Error: Each group of two bits indicate the bit error
 * count on eachof the up to 3 bank address bits. [1:0] is the error count
 * for BA[0], [3:2] for BA[1],and so on.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTBER1 . BABER
 */
#define  VTSS_F_DDR_PHY_BISTBER1_BABER(x)     VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_PHY_BISTBER1_BABER        VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_PHY_BISTBER1_BABER(x)     VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * WE# Bit Error: Indicates the number of bit errors on WE#.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTBER1 . WEBER
 */
#define  VTSS_F_DDR_PHY_BISTBER1_WEBER(x)     VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_DDR_PHY_BISTBER1_WEBER        VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_DDR_PHY_BISTBER1_WEBER(x)     VTSS_EXTRACT_BITFIELD(x,6,2)

/**
 * \brief
 * CKE Bit Error: Each group of two bits indicate the bit error count on
 * each of the upto 4 CKE bits. [1:0] is the error count for CKE[0], [3:2]
 * for CKE[1], and so on.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTBER1 . CKEBER
 */
#define  VTSS_F_DDR_PHY_BISTBER1_CKEBER(x)    VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DDR_PHY_BISTBER1_CKEBER       VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DDR_PHY_BISTBER1_CKEBER(x)    VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * CS# Bit Error: Each group of two bits indicate the bit error count on
 * each of the upto 4 CS# bits. [1:0] is the error count for CS#[0], [3:2]
 * for CS#[1], and so on.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTBER1 . CSBER
 */
#define  VTSS_F_DDR_PHY_BISTBER1_CSBER(x)     VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_PHY_BISTBER1_CSBER        VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_PHY_BISTBER1_CSBER(x)     VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * ODT Bit Error: Each group of two bits indicates the bit error count on
 * each of theup to 4 ODT bits. [1:0] is the error count for ODT[0], [3:2]
 * for ODT[1], and so on
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTBER1 . ODTBER
 */
#define  VTSS_F_DDR_PHY_BISTBER1_ODTBER(x)    VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DDR_PHY_BISTBER1_ODTBER       VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DDR_PHY_BISTBER1_ODTBER(x)    VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief BIST Bit Error Register 2
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:BISTBER2
 */
#define VTSS_DDR_PHY_BISTBER2                VTSS_IOREG(VTSS_TO_DDR_PHY,0x4e)

/**
 * \brief
 * Data Bit Error: The error count for even DQS cycles. The first 16 bits
 * indicate theerror count for the first data beat (i.e. the data driven
 * out on DQ[7:0] on the risingedge of DQS). The second 16 bits indicate
 * the error on the second data beat(i.e. the error count of the data
 * driven out on DQ[7:0] on the falling edge of DQS).For each of the 16-bit
 * group, the first 2 bits are for DQ[0], the second for DQ[1],and so on.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTBER2 . DQBER0
 */
#define  VTSS_F_DDR_PHY_BISTBER2_DQBER0(x)    (x)
#define  VTSS_M_DDR_PHY_BISTBER2_DQBER0       0xffffffff
#define  VTSS_X_DDR_PHY_BISTBER2_DQBER0(x)    (x)


/**
 * \brief BIST Bit Error Register 3
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:BISTBER3
 */
#define VTSS_DDR_PHY_BISTBER3                VTSS_IOREG(VTSS_TO_DDR_PHY,0x4f)

/**
 * \brief
 * Data Bit Error: The error count for odd DQS cycles. The first 16 bits
 * indicate theerror count for the first data beat (i.e. the data driven
 * out on DQ[7:0] on the risingedge of DQS). The second 16 bits indicate
 * the error on the second data beat (i.e.the error count of the data
 * driven out on DQ[7:0] on the falling edge of DQS). Foreach of the 16-bit
 * group, the first 2 bits are for DQ[0], the second for DQ[1], andso on.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTBER3 . DQBER1
 */
#define  VTSS_F_DDR_PHY_BISTBER3_DQBER1(x)    (x)
#define  VTSS_M_DDR_PHY_BISTBER3_DQBER1       0xffffffff
#define  VTSS_X_DDR_PHY_BISTBER3_DQBER1(x)    (x)


/**
 * \brief BIST Word Count Status Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:BISTWCSR
 */
#define VTSS_DDR_PHY_BISTWCSR                VTSS_IOREG(VTSS_TO_DDR_PHY,0x50)

/**
 * \brief
 * Address/Command Word Count: Indicates the number of words received from
 * theaddress/command lane.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTWCSR . ACWCNT
 */
#define  VTSS_F_DDR_PHY_BISTWCSR_ACWCNT(x)    VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_PHY_BISTWCSR_ACWCNT       VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_PHY_BISTWCSR_ACWCNT(x)    VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Byte Word Count: Indicates the number of words received from the byte
 * lane.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTWCSR . DXWCNT
 */
#define  VTSS_F_DDR_PHY_BISTWCSR_DXWCNT(x)    VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DDR_PHY_BISTWCSR_DXWCNT       VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DDR_PHY_BISTWCSR_DXWCNT(x)    VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief BIST Fail Word Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:BISTFWR0
 */
#define VTSS_DDR_PHY_BISTFWR0                VTSS_IOREG(VTSS_TO_DDR_PHY,0x51)

/**
 * \brief
 * Bit status during a word error for each of the up to 16 address bits.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTFWR0 . AWEBS
 */
#define  VTSS_F_DDR_PHY_BISTFWR0_AWEBS(x)     VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_PHY_BISTFWR0_AWEBS        VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_PHY_BISTFWR0_AWEBS(x)     VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Bit status during a word error for each of the up to 3 bank address
 * bits.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTFWR0 . BAWEBS
 */
#define  VTSS_F_DDR_PHY_BISTFWR0_BAWEBS(x)    VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_DDR_PHY_BISTFWR0_BAWEBS       VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_DDR_PHY_BISTFWR0_BAWEBS(x)    VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * Bit status during a word error for the WE#.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTFWR0 . WEWEBS
 */
#define  VTSS_F_DDR_PHY_BISTFWR0_WEWEBS(x)    VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_DDR_PHY_BISTFWR0_WEWEBS       VTSS_BIT(19)
#define  VTSS_X_DDR_PHY_BISTFWR0_WEWEBS(x)    VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Bit status during a word error for each of the up to 4 CKE bits.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTFWR0 . CKEWEBS
 */
#define  VTSS_F_DDR_PHY_BISTFWR0_CKEWEBS(x)   VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_DDR_PHY_BISTFWR0_CKEWEBS      VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_DDR_PHY_BISTFWR0_CKEWEBS(x)   VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * Bit status during a word error for each of the up to 4 CS# bits
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTFWR0 . CSWEBS
 */
#define  VTSS_F_DDR_PHY_BISTFWR0_CSWEBS(x)    VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_PHY_BISTFWR0_CSWEBS       VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_PHY_BISTFWR0_CSWEBS(x)    VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * Bit status during a word error for each of the up to 4 ODT bits.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTFWR0 . ODTWEBS
 */
#define  VTSS_F_DDR_PHY_BISTFWR0_ODTWEBS(x)   VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_DDR_PHY_BISTFWR0_ODTWEBS      VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_DDR_PHY_BISTFWR0_ODTWEBS(x)   VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief BIST Fail Word Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:BISTFWR1
 */
#define VTSS_DDR_PHY_BISTFWR1                VTSS_IOREG(VTSS_TO_DDR_PHY,0x52)

/**
 * \brief
 * Bit status during a word error for the RAS.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTFWR1 . RASWEBS
 */
#define  VTSS_F_DDR_PHY_BISTFWR1_RASWEBS(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_BISTFWR1_RASWEBS      VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_BISTFWR1_RASWEBS(x)   VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Bit status during a word error for the CAS
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTFWR1 . CASWEBS
 */
#define  VTSS_F_DDR_PHY_BISTFWR1_CASWEBS(x)   VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_PHY_BISTFWR1_CASWEBS      VTSS_BIT(1)
#define  VTSS_X_DDR_PHY_BISTFWR1_CASWEBS(x)   VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Bit status during a word error for the PAR_IN. Only for DIMM parity
 * support
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTFWR1 . PARWEBS
 */
#define  VTSS_F_DDR_PHY_BISTFWR1_PARWEBS(x)   VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_DDR_PHY_BISTFWR1_PARWEBS      VTSS_BIT(26)
#define  VTSS_X_DDR_PHY_BISTFWR1_PARWEBS(x)   VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * Bit status during a word error for the data mask (DM) bit. DMWEBS [0] is
 * for thefirst DM beat, DMWEBS [1] is for the second DM beat, and so on.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTFWR1 . DMWEBS
 */
#define  VTSS_F_DDR_PHY_BISTFWR1_DMWEBS(x)    VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_DDR_PHY_BISTFWR1_DMWEBS       VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_DDR_PHY_BISTFWR1_DMWEBS(x)    VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief BIST Fail Word Register 2
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:BISTFWR2
 */
#define VTSS_DDR_PHY_BISTFWR2                VTSS_IOREG(VTSS_TO_DDR_PHY,0x53)

/**
 * \brief
 * Bit status during a word error for each of the 8 data (DQ) bits. The
 * first 8 bitsindicate the status of the first data beat (i.e. the status
 * of the data driven out onDQ[7:0] on the rising edge of DQS). The second
 * 8 bits indicate the status of thesecond data beat (i.e. the status of
 * the data driven out on DQ[7:0] on the fallingedge of DQS), and so on.
 * For each of the 8-bit group, the first bit is for DQ[0], thesecond bit
 * is for DQ[1], and so on.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_BISTFWR2 . DQWEBS
 */
#define  VTSS_F_DDR_PHY_BISTFWR2_DQWEBS(x)    (x)
#define  VTSS_M_DDR_PHY_BISTFWR2_DQWEBS       0xffffffff
#define  VTSS_X_DDR_PHY_BISTFWR2_DQWEBS(x)    (x)


/**
 * \brief Anti-Aging Control Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:AACR
 */
#define VTSS_DDR_PHY_AACR                    VTSS_IOREG(VTSS_TO_DDR_PHY,0x5d)

/**
 * \brief
 * Anti-Aging Toggle Rate: Defines the number of controller clock (ctl_clk)
 * cyclesafter which the PUB will toggle the data going to DATX8 if the
 * data channelbetween the controller/PUB and DATX8 has been idle for this
 * long.The default value correspond to a toggling count of 4096 ctl_clk
 * cycles. For actl_clk running at 533MHz the toggle rate will be
 * approximately 7.68us.The default value may also be overridden by the
 * macroDWC_AACR_AATR_DFLT.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_AACR . AATR
 */
#define  VTSS_F_DDR_PHY_AACR_AATR(x)          VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_DDR_PHY_AACR_AATR             VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_DDR_PHY_AACR_AATR(x)          VTSS_EXTRACT_BITFIELD(x,0,30)

/**
 * \brief
 * Anti-Aging Enable Control: Enables, if set, the automatic toggling of
 * the datagoing to the DATX8 when the data channel from the controller/PUB
 * to DATX8 isidle for programmable number of clock cycles.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_AACR . AAENC
 */
#define  VTSS_F_DDR_PHY_AACR_AAENC(x)         VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_PHY_AACR_AAENC            VTSS_BIT(30)
#define  VTSS_X_DDR_PHY_AACR_AAENC(x)         VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Anti-Aging PAD Output Enable Control: Enables, if set, anti-aging
 * toggling onthe pad output enable signal "ctl_oe_n" going into the
 * DATX8s. This willincrease power consumption for the anti-aging feature.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_AACR . AAOENC
 */
#define  VTSS_F_DDR_PHY_AACR_AAOENC(x)        VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_PHY_AACR_AAOENC           VTSS_BIT(31)
#define  VTSS_X_DDR_PHY_AACR_AAOENC(x)        VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief ZQ n Impedance Control Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:ZQ0CR0
 */
#define VTSS_DDR_PHY_ZQ0CR0                  VTSS_IOREG(VTSS_TO_DDR_PHY,0x60)

/**
 * \brief
 * Impedance Over-Ride Data: Data used to directly drive the impedance
 * control.ZDATA field mapping for D3F I/Os is as follows:ZDATA[27:21] is
 * used to select the pull-up on-die termination impedanceZDATA[20:14] is
 * used to select the pull-down on-die termination impedanceZDATA[13:7] is
 * used to select the pull-up output impedanceZDATA[6:0] is used to select
 * the pull-down output impedanceZDATA field mapping for D3A/B/R I/Os is as
 * follows:ZDATA[27:20] is reserved and returns zeros on readsZDATA[19:15]
 * is used to select the pull-up on-die termination impedanceZDATA[14:10]
 * is used to select the pull-down on-die termination impedanceZDATA[9:5]
 * is used to select the pull-up output impedanceZDATA[4:0] is used to
 * select the pull-down output impedanceThe default value is 0x000014A for
 * I/O type D3C/R and 0x0001830 for I/O typeD3F.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ0CR0 . ZQ0_ZDATA
 */
#define  VTSS_F_DDR_PHY_ZQ0CR0_ZQ0_ZDATA(x)   VTSS_ENCODE_BITFIELD(x,0,28)
#define  VTSS_M_DDR_PHY_ZQ0CR0_ZQ0_ZDATA      VTSS_ENCODE_BITMASK(0,28)
#define  VTSS_X_DDR_PHY_ZQ0CR0_ZQ0_ZDATA(x)   VTSS_EXTRACT_BITFIELD(x,0,28)

/**
 * \brief
 * Impedance Over-ride Enable: When this bit is set, it allows users to
 * directly drivethe impedance control using the data programmed in the
 * ZDATA field. Otherwise,the control is generated automatically by the
 * impedance control logic.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ0CR0 . ZQ0_ZDEN
 */
#define  VTSS_F_DDR_PHY_ZQ0CR0_ZQ0_ZDEN(x)    VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_DDR_PHY_ZQ0CR0_ZQ0_ZDEN       VTSS_BIT(28)
#define  VTSS_X_DDR_PHY_ZQ0CR0_ZQ0_ZDEN(x)    VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Impedance Calibration Bypass: Bypasses, if set, impedance calibration of
 * this ZQcontrol block when impedance calibration is already in progress.
 * Impedancecalibration can be disabled prior to trigger by using the
 * ZCALEN bit.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ0CR0 . ZQ0_ZCALBYP
 */
#define  VTSS_F_DDR_PHY_ZQ0CR0_ZQ0_ZCALBYP(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_DDR_PHY_ZQ0CR0_ZQ0_ZCALBYP    VTSS_BIT(29)
#define  VTSS_X_DDR_PHY_ZQ0CR0_ZQ0_ZCALBYP(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Impedance Calibration Enable: Enables, if set, the impedance calibration
 * of thisZQ control block when impedance calibration is triggered using
 * either the ZCAL bitof PIR register or the DFI update interface.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ0CR0 . ZQ0_ZCALEN
 */
#define  VTSS_F_DDR_PHY_ZQ0CR0_ZQ0_ZCALEN(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_PHY_ZQ0CR0_ZQ0_ZCALEN     VTSS_BIT(30)
#define  VTSS_X_DDR_PHY_ZQ0CR0_ZQ0_ZCALEN(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * ZQ Power Down: Powers down, if set, the PZQ cell.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ0CR0 . ZQ0_ZQPD
 */
#define  VTSS_F_DDR_PHY_ZQ0CR0_ZQ0_ZQPD(x)    VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_PHY_ZQ0CR0_ZQ0_ZQPD       VTSS_BIT(31)
#define  VTSS_X_DDR_PHY_ZQ0CR0_ZQ0_ZQPD(x)    VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief ZQ n Impedance Control Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:ZQ0CR1
 */
#define VTSS_DDR_PHY_ZQ0CR1                  VTSS_IOREG(VTSS_TO_DDR_PHY,0x61)

/**
 * \brief
 * Impedance Divide Ratio: Selects the external resistor divide ratio to be
 * used to setthe output impedance and the on-die termination as
 * follows:ZPROG[7:4] = On-die termination divide selectZPROG[3:0] = Output
 * impedance divide select
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ0CR1 . ZQ0_ZPROG
 */
#define  VTSS_F_DDR_PHY_ZQ0CR1_ZQ0_ZPROG(x)   VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_PHY_ZQ0CR1_ZQ0_ZPROG      VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_PHY_ZQ0CR1_ZQ0_ZPROG(x)   VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * DFI Controller Update Interface 0: Sets this impedance controller to be
 * enabled forcalibration when the DFI controller update interface 0
 * (channel 0) requests anupdate.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ0CR1 . ZQ0_DFICU0
 */
#define  VTSS_F_DDR_PHY_ZQ0CR1_ZQ0_DFICU0(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DDR_PHY_ZQ0CR1_ZQ0_DFICU0     VTSS_BIT(12)
#define  VTSS_X_DDR_PHY_ZQ0CR1_ZQ0_DFICU0(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * DFI Controller Update Interface 1: Sets this impedance controller to be
 * enabled forcalibration when the DFI controller update interface 1
 * (channel 1) requests anupdate.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ0CR1 . ZQ0_DFICU1
 */
#define  VTSS_F_DDR_PHY_ZQ0CR1_ZQ0_DFICU1(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DDR_PHY_ZQ0CR1_ZQ0_DFICU1     VTSS_BIT(13)
#define  VTSS_X_DDR_PHY_ZQ0CR1_ZQ0_DFICU1(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * DFI Concurrent Controller Update Interface: Sets this impedance
 * controller to beenabled for calibration when both of the DFI controller
 * update interfaces request anupdate on the same clock. This provides the
 * ability to enable impedance calibrationupdates for the Address/Command
 * lane. Only valid in shared-AC mode.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ0CR1 . ZQ0_DFICCU
 */
#define  VTSS_F_DDR_PHY_ZQ0CR1_ZQ0_DFICCU(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_DDR_PHY_ZQ0CR1_ZQ0_DFICCU     VTSS_BIT(14)
#define  VTSS_X_DDR_PHY_ZQ0CR1_ZQ0_DFICCU(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * DFI Update Interface 0: Sets this impedance controller to be enabled for
 * calibrationwhen the DFI PHY update interface 0 (channel 0) requests an
 * update.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ0CR1 . ZQ0_DFIPU0
 */
#define  VTSS_F_DDR_PHY_ZQ0CR1_ZQ0_DFIPU0(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DDR_PHY_ZQ0CR1_ZQ0_DFIPU0     VTSS_BIT(16)
#define  VTSS_X_DDR_PHY_ZQ0CR1_ZQ0_DFIPU0(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * DFI Update Interface 1: Sets this impedance controller to be enabled for
 * calibrationwhen the DFI PHY update interface 1 (channel 1) requests an
 * update. Only valid inshared-AC mode.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ0CR1 . ZQ0_DFIPU1
 */
#define  VTSS_F_DDR_PHY_ZQ0CR1_ZQ0_DFIPU1(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_DDR_PHY_ZQ0CR1_ZQ0_DFIPU1     VTSS_BIT(17)
#define  VTSS_X_DDR_PHY_ZQ0CR1_ZQ0_DFIPU1(x)  VTSS_EXTRACT_BITFIELD(x,17,1)


/**
 * \brief ZQ n Impedance Control Status Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:ZQ0SR0
 */
#define VTSS_DDR_PHY_ZQ0SR0                  VTSS_IOREG(VTSS_TO_DDR_PHY,0x62)

/**
 * \brief
 * Impedance Control: Current value of impedance control.ZCTRL field
 * mapping for D3F I/Os is as follows:ZCTRL[27:21] is used to select the
 * pull-up on-die termination impedanceZCTRL[20:14] is used to select the
 * pull-down on-die termination impedanceZCTRL[13:7] is used to select the
 * pull-up output impedanceZCTRL[6:0] is used to select the pull-down
 * output impedanceZCTRL field mapping for D3A/B/R I/Os is as
 * follows:ZCTRL[27:20] is reserved and returns zeros on readsZCTRL[19:15]
 * is used to select the pull-up on-die termination impedanceZCTRL[14:10]
 * is used to select the pull-down on-die termination impedanceZCTRL[9:5]
 * is used to select the pull-up output impedanceZCTRL[4:0] is used to
 * select the pull-down output impedanceNote: The default value is
 * 0x000014A for I/O type D3C/D3R and 0x0001839 forI/O type D3F.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ0SR0 . ZQ0_ZCTRL
 */
#define  VTSS_F_DDR_PHY_ZQ0SR0_ZQ0_ZCTRL(x)   VTSS_ENCODE_BITFIELD(x,0,28)
#define  VTSS_M_DDR_PHY_ZQ0SR0_ZQ0_ZCTRL      VTSS_ENCODE_BITMASK(0,28)
#define  VTSS_X_DDR_PHY_ZQ0SR0_ZQ0_ZCTRL(x)   VTSS_EXTRACT_BITFIELD(x,0,28)

/**
 * \brief
 * Impedance Calibration Error: If set, indicates that there was an error
 * duringimpedance calibration.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ0SR0 . ZQ0_ZERR
 */
#define  VTSS_F_DDR_PHY_ZQ0SR0_ZQ0_ZERR(x)    VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_PHY_ZQ0SR0_ZQ0_ZERR       VTSS_BIT(30)
#define  VTSS_X_DDR_PHY_ZQ0SR0_ZQ0_ZERR(x)    VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Impedance Calibration Done: Indicates that impedance calibration
 * hascompleted.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ0SR0 . ZQ0_ZDONE
 */
#define  VTSS_F_DDR_PHY_ZQ0SR0_ZQ0_ZDONE(x)   VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_PHY_ZQ0SR0_ZQ0_ZDONE      VTSS_BIT(31)
#define  VTSS_X_DDR_PHY_ZQ0SR0_ZQ0_ZDONE(x)   VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief ZQ n Impedance Control Status Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:ZQ0SR1
 */
#define VTSS_DDR_PHY_ZQ0SR1                  VTSS_IOREG(VTSS_TO_DDR_PHY,0x63)

/**
 * \brief
 * Output impedance pull-down calibration status. Valid status encodings
 * are:00 = Completed with no errors01 = Overflow error10 = Underflow
 * error11 = Calibration in progress
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ0SR1 . ZQ0_ZPD
 */
#define  VTSS_F_DDR_PHY_ZQ0SR1_ZQ0_ZPD(x)     VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DDR_PHY_ZQ0SR1_ZQ0_ZPD        VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DDR_PHY_ZQ0SR1_ZQ0_ZPD(x)     VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * Output impedance pull-up calibration status. Similar status encodings as
 * ZPD.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ0SR1 . ZQ0_ZPU
 */
#define  VTSS_F_DDR_PHY_ZQ0SR1_ZQ0_ZPU(x)     VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_DDR_PHY_ZQ0SR1_ZQ0_ZPU        VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_DDR_PHY_ZQ0SR1_ZQ0_ZPU(x)     VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * On-die termination (ODT) pull-down calibration status. Similar status
 * encodings asZPD
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ0SR1 . ZQ0_OPD
 */
#define  VTSS_F_DDR_PHY_ZQ0SR1_ZQ0_OPD(x)     VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_DDR_PHY_ZQ0SR1_ZQ0_OPD        VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_DDR_PHY_ZQ0SR1_ZQ0_OPD(x)     VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * On-die termination (ODT) pull-up calibration status. Similar status
 * encodings asZPD.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ0SR1 . ZQ0_OPU
 */
#define  VTSS_F_DDR_PHY_ZQ0SR1_ZQ0_OPU(x)     VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_DDR_PHY_ZQ0SR1_ZQ0_OPU        VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_DDR_PHY_ZQ0SR1_ZQ0_OPU(x)     VTSS_EXTRACT_BITFIELD(x,6,2)


/**
 * \brief ZQ n Impedance Control Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:ZQ1CR0
 */
#define VTSS_DDR_PHY_ZQ1CR0                  VTSS_IOREG(VTSS_TO_DDR_PHY,0x64)

/**
 * \brief
 * Impedance Over-Ride Data: Data used to directly drive the impedance
 * control.ZDATA field mapping for D3F I/Os is as follows:ZDATA[27:21] is
 * used to select the pull-up on-die termination impedanceZDATA[20:14] is
 * used to select the pull-down on-die termination impedanceZDATA[13:7] is
 * used to select the pull-up output impedanceZDATA[6:0] is used to select
 * the pull-down output impedanceZDATA field mapping for D3A/B/R I/Os is as
 * follows:ZDATA[27:20] is reserved and returns zeros on readsZDATA[19:15]
 * is used to select the pull-up on-die termination impedanceZDATA[14:10]
 * is used to select the pull-down on-die termination impedanceZDATA[9:5]
 * is used to select the pull-up output impedanceZDATA[4:0] is used to
 * select the pull-down output impedanceThe default value is 0x000014A for
 * I/O type D3C/R and 0x0001830 for I/O typeD3F.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ1CR0 . ZQ1_ZDATA
 */
#define  VTSS_F_DDR_PHY_ZQ1CR0_ZQ1_ZDATA(x)   VTSS_ENCODE_BITFIELD(x,0,28)
#define  VTSS_M_DDR_PHY_ZQ1CR0_ZQ1_ZDATA      VTSS_ENCODE_BITMASK(0,28)
#define  VTSS_X_DDR_PHY_ZQ1CR0_ZQ1_ZDATA(x)   VTSS_EXTRACT_BITFIELD(x,0,28)

/**
 * \brief
 * Impedance Over-ride Enable: When this bit is set, it allows users to
 * directly drivethe impedance control using the data programmed in the
 * ZDATA field. Otherwise,the control is generated automatically by the
 * impedance control logic.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ1CR0 . ZQ1_ZDEN
 */
#define  VTSS_F_DDR_PHY_ZQ1CR0_ZQ1_ZDEN(x)    VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_DDR_PHY_ZQ1CR0_ZQ1_ZDEN       VTSS_BIT(28)
#define  VTSS_X_DDR_PHY_ZQ1CR0_ZQ1_ZDEN(x)    VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Impedance Calibration Bypass: Bypasses, if set, impedance calibration of
 * this ZQcontrol block when impedance calibration is already in progress.
 * Impedancecalibration can be disabled prior to trigger by using the
 * ZCALEN bit.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ1CR0 . ZQ1_ZCALBYP
 */
#define  VTSS_F_DDR_PHY_ZQ1CR0_ZQ1_ZCALBYP(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_DDR_PHY_ZQ1CR0_ZQ1_ZCALBYP    VTSS_BIT(29)
#define  VTSS_X_DDR_PHY_ZQ1CR0_ZQ1_ZCALBYP(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Impedance Calibration Enable: Enables, if set, the impedance calibration
 * of thisZQ control block when impedance calibration is triggered using
 * either the ZCAL bitof PIR register or the DFI update interface.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ1CR0 . ZQ1_ZCALEN
 */
#define  VTSS_F_DDR_PHY_ZQ1CR0_ZQ1_ZCALEN(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_PHY_ZQ1CR0_ZQ1_ZCALEN     VTSS_BIT(30)
#define  VTSS_X_DDR_PHY_ZQ1CR0_ZQ1_ZCALEN(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * ZQ Power Down: Powers down, if set, the PZQ cell.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ1CR0 . ZQ1_ZQPD
 */
#define  VTSS_F_DDR_PHY_ZQ1CR0_ZQ1_ZQPD(x)    VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_PHY_ZQ1CR0_ZQ1_ZQPD       VTSS_BIT(31)
#define  VTSS_X_DDR_PHY_ZQ1CR0_ZQ1_ZQPD(x)    VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief ZQ n Impedance Control Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:ZQ1CR1
 */
#define VTSS_DDR_PHY_ZQ1CR1                  VTSS_IOREG(VTSS_TO_DDR_PHY,0x65)

/**
 * \brief
 * Impedance Divide Ratio: Selects the external resistor divide ratio to be
 * used to setthe output impedance and the on-die termination as
 * follows:ZPROG[7:4] = On-die termination divide selectZPROG[3:0] = Output
 * impedance divide select
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ1CR1 . ZQ1_ZPROG
 */
#define  VTSS_F_DDR_PHY_ZQ1CR1_ZQ1_ZPROG(x)   VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_PHY_ZQ1CR1_ZQ1_ZPROG      VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_PHY_ZQ1CR1_ZQ1_ZPROG(x)   VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * DFI Controller Update Interface 0: Sets this impedance controller to be
 * enabled forcalibration when the DFI controller update interface 0
 * (channel 0) requests anupdate.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ1CR1 . ZQ1_DFICU0
 */
#define  VTSS_F_DDR_PHY_ZQ1CR1_ZQ1_DFICU0(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DDR_PHY_ZQ1CR1_ZQ1_DFICU0     VTSS_BIT(12)
#define  VTSS_X_DDR_PHY_ZQ1CR1_ZQ1_DFICU0(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * DFI Controller Update Interface 1: Sets this impedance controller to be
 * enabled forcalibration when the DFI controller update interface 1
 * (channel 1) requests anupdate.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ1CR1 . ZQ1_DFICU1
 */
#define  VTSS_F_DDR_PHY_ZQ1CR1_ZQ1_DFICU1(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DDR_PHY_ZQ1CR1_ZQ1_DFICU1     VTSS_BIT(13)
#define  VTSS_X_DDR_PHY_ZQ1CR1_ZQ1_DFICU1(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * DFI Concurrent Controller Update Interface: Sets this impedance
 * controller to beenabled for calibration when both of the DFI controller
 * update interfaces request anupdate on the same clock. This provides the
 * ability to enable impedance calibrationupdates for the Address/Command
 * lane. Only valid in shared-AC mode.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ1CR1 . ZQ1_DFICCU
 */
#define  VTSS_F_DDR_PHY_ZQ1CR1_ZQ1_DFICCU(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_DDR_PHY_ZQ1CR1_ZQ1_DFICCU     VTSS_BIT(14)
#define  VTSS_X_DDR_PHY_ZQ1CR1_ZQ1_DFICCU(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * DFI Update Interface 0: Sets this impedance controller to be enabled for
 * calibrationwhen the DFI PHY update interface 0 (channel 0) requests an
 * update.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ1CR1 . ZQ1_DFIPU0
 */
#define  VTSS_F_DDR_PHY_ZQ1CR1_ZQ1_DFIPU0(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DDR_PHY_ZQ1CR1_ZQ1_DFIPU0     VTSS_BIT(16)
#define  VTSS_X_DDR_PHY_ZQ1CR1_ZQ1_DFIPU0(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * DFI Update Interface 1: Sets this impedance controller to be enabled for
 * calibrationwhen the DFI PHY update interface 1 (channel 1) requests an
 * update. Only valid inshared-AC mode.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ1CR1 . ZQ1_DFIPU1
 */
#define  VTSS_F_DDR_PHY_ZQ1CR1_ZQ1_DFIPU1(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_DDR_PHY_ZQ1CR1_ZQ1_DFIPU1     VTSS_BIT(17)
#define  VTSS_X_DDR_PHY_ZQ1CR1_ZQ1_DFIPU1(x)  VTSS_EXTRACT_BITFIELD(x,17,1)


/**
 * \brief ZQ n Impedance Control Status Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:ZQ1SR0
 */
#define VTSS_DDR_PHY_ZQ1SR0                  VTSS_IOREG(VTSS_TO_DDR_PHY,0x66)

/**
 * \brief
 * Impedance Control: Current value of impedance control.ZCTRL field
 * mapping for D3F I/Os is as follows:ZCTRL[27:21] is used to select the
 * pull-up on-die termination impedanceZCTRL[20:14] is used to select the
 * pull-down on-die termination impedanceZCTRL[13:7] is used to select the
 * pull-up output impedanceZCTRL[6:0] is used to select the pull-down
 * output impedanceZCTRL field mapping for D3A/B/R I/Os is as
 * follows:ZCTRL[27:20] is reserved and returns zeros on readsZCTRL[19:15]
 * is used to select the pull-up on-die termination impedanceZCTRL[14:10]
 * is used to select the pull-down on-die termination impedanceZCTRL[9:5]
 * is used to select the pull-up output impedanceZCTRL[4:0] is used to
 * select the pull-down output impedanceNote: The default value is
 * 0x000014A for I/O type D3C/D3R and 0x0001839 forI/O type D3F.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ1SR0 . ZQ1_ZCTRL
 */
#define  VTSS_F_DDR_PHY_ZQ1SR0_ZQ1_ZCTRL(x)   VTSS_ENCODE_BITFIELD(x,0,28)
#define  VTSS_M_DDR_PHY_ZQ1SR0_ZQ1_ZCTRL      VTSS_ENCODE_BITMASK(0,28)
#define  VTSS_X_DDR_PHY_ZQ1SR0_ZQ1_ZCTRL(x)   VTSS_EXTRACT_BITFIELD(x,0,28)

/**
 * \brief
 * Impedance Calibration Error: If set, indicates that there was an error
 * duringimpedance calibration.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ1SR0 . ZQ1_ZERR
 */
#define  VTSS_F_DDR_PHY_ZQ1SR0_ZQ1_ZERR(x)    VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_PHY_ZQ1SR0_ZQ1_ZERR       VTSS_BIT(30)
#define  VTSS_X_DDR_PHY_ZQ1SR0_ZQ1_ZERR(x)    VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Impedance Calibration Done: Indicates that impedance calibration
 * hascompleted.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ1SR0 . ZQ1_ZDONE
 */
#define  VTSS_F_DDR_PHY_ZQ1SR0_ZQ1_ZDONE(x)   VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_PHY_ZQ1SR0_ZQ1_ZDONE      VTSS_BIT(31)
#define  VTSS_X_DDR_PHY_ZQ1SR0_ZQ1_ZDONE(x)   VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief ZQ n Impedance Control Status Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:ZQ1SR1
 */
#define VTSS_DDR_PHY_ZQ1SR1                  VTSS_IOREG(VTSS_TO_DDR_PHY,0x67)

/**
 * \brief
 * Output impedance pull-down calibration status. Valid status encodings
 * are:00 = Completed with no errors01 = Overflow error10 = Underflow
 * error11 = Calibration in progress
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ1SR1 . ZQ1_ZPD
 */
#define  VTSS_F_DDR_PHY_ZQ1SR1_ZQ1_ZPD(x)     VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DDR_PHY_ZQ1SR1_ZQ1_ZPD        VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DDR_PHY_ZQ1SR1_ZQ1_ZPD(x)     VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * Output impedance pull-up calibration status. Similar status encodings as
 * ZPD.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ1SR1 . ZQ1_ZPU
 */
#define  VTSS_F_DDR_PHY_ZQ1SR1_ZQ1_ZPU(x)     VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_DDR_PHY_ZQ1SR1_ZQ1_ZPU        VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_DDR_PHY_ZQ1SR1_ZQ1_ZPU(x)     VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * On-die termination (ODT) pull-down calibration status. Similar status
 * encodings asZPD.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ1SR1 . ZQ1_OPD
 */
#define  VTSS_F_DDR_PHY_ZQ1SR1_ZQ1_OPD(x)     VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_DDR_PHY_ZQ1SR1_ZQ1_OPD        VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_DDR_PHY_ZQ1SR1_ZQ1_OPD(x)     VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * On-die termination (ODT) pull-up calibration status. Similar status
 * encodings asZPD.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_ZQ1SR1 . ZQ1_OPU
 */
#define  VTSS_F_DDR_PHY_ZQ1SR1_ZQ1_OPU(x)     VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_DDR_PHY_ZQ1SR1_ZQ1_OPU        VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_DDR_PHY_ZQ1SR1_ZQ1_OPU(x)     VTSS_EXTRACT_BITFIELD(x,6,2)


/**
 * \brief DX n General Configuration Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX0GCR
 */
#define VTSS_DDR_PHY_DX0GCR                  VTSS_IOREG(VTSS_TO_DDR_PHY,0x70)

/**
 * \brief
 * Data Byte Enable: Enables, if set, the data byte. Setting this bit to
 * '0' disables thebyte, i.e. the byte is not used in PHY initialization or
 * training and is ignored duringSDRAM read/write operations
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GCR . DX0_DXEN
 */
#define  VTSS_F_DDR_PHY_DX0GCR_DX0_DXEN(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_DX0GCR_DX0_DXEN       VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_DX0GCR_DX0_DXEN(x)    VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * DQS On-Die Termination: Enables, when set, the on-die termination on the
 * I/O forDQS/DQS# pin of the byte. This bit is ORed with the common DATX8
 * ODTconfiguration bit
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GCR . DX0_DQSODT
 */
#define  VTSS_F_DDR_PHY_DX0GCR_DX0_DQSODT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_PHY_DX0GCR_DX0_DQSODT     VTSS_BIT(1)
#define  VTSS_X_DDR_PHY_DX0GCR_DX0_DQSODT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Data On-Die Termination: Enables, when set, the on-die termination on
 * the I/O forDQ and DM pins of the byte. This bit is ORed with the common
 * DATX8 ODTconfiguration bit
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GCR . DX0_DQODT
 */
#define  VTSS_F_DDR_PHY_DX0GCR_DX0_DQODT(x)   VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_PHY_DX0GCR_DX0_DQODT      VTSS_BIT(2)
#define  VTSS_X_DDR_PHY_DX0GCR_DX0_DQODT(x)   VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Data I/O Mode: Selects SSTL mode (when set to 0) or CMOS mode (when set
 * to 1)of the I/O for DQ, DM, and DQS/DQS# pins of the byte. This bit is
 * ORed with theIOM configuration bit of the individual DATX8
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GCR . DX0_DXIOM
 */
#define  VTSS_F_DDR_PHY_DX0GCR_DX0_DXIOM(x)   VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_PHY_DX0GCR_DX0_DXIOM      VTSS_BIT(3)
#define  VTSS_X_DDR_PHY_DX0GCR_DX0_DXIOM(x)   VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Data Power Down Driver: Powers down, when set, the output driver on I/O
 * for DQ,DM, and DQS/DQS# pins of the byte. This bit is ORed with the
 * common PDDconfiguration bit
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GCR . DX0_DXPDD
 */
#define  VTSS_F_DDR_PHY_DX0GCR_DX0_DXPDD(x)   VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_PHY_DX0GCR_DX0_DXPDD      VTSS_BIT(4)
#define  VTSS_X_DDR_PHY_DX0GCR_DX0_DXPDD(x)   VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Data Power Down Receiver: Powers down, when set, the input receiver on
 * I/O forDQ, DM, and DQS/DQS# pins of the byte. This bit is ORed with the
 * common PDRconfiguration bit
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GCR . DX0_DXPDR
 */
#define  VTSS_F_DDR_PHY_DX0GCR_DX0_DXPDR(x)   VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_PHY_DX0GCR_DX0_DXPDR      VTSS_BIT(5)
#define  VTSS_X_DDR_PHY_DX0GCR_DX0_DXPDR(x)   VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DQSR Power Down: Powers down, if set, the PDQSR cell. This bit is ORed
 * with thecommon PDR configuration bit
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GCR . DX0_DQSRPD
 */
#define  VTSS_F_DDR_PHY_DX0GCR_DX0_DQSRPD(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DDR_PHY_DX0GCR_DX0_DQSRPD     VTSS_BIT(6)
#define  VTSS_X_DDR_PHY_DX0GCR_DX0_DQSRPD(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Write DQS Enable: Controls whether the write DQS going to the SDRAM is
 * enabled(toggling) or disabled (static value) and whether the DQS is
 * inverted. DQS# isalways the inversion of DQS. These values are valid
 * only when DQS/DQS# outputenable is on, otherwise the DQS/DQS# is
 * tri-stated. Valid settings are:00 = Reserved01 = DQS toggling with
 * normal polarity (This should be the default setting)10 = Reserved11 =
 * Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GCR . DX0_DSEN
 */
#define  VTSS_F_DDR_PHY_DX0GCR_DX0_DSEN(x)    VTSS_ENCODE_BITFIELD(x,7,2)
#define  VTSS_M_DDR_PHY_DX0GCR_DX0_DSEN       VTSS_ENCODE_BITMASK(7,2)
#define  VTSS_X_DDR_PHY_DX0GCR_DX0_DSEN(x)    VTSS_EXTRACT_BITFIELD(x,7,2)

/**
 * \brief
 * DQS Dynamic RTT Control: If set, the on die termination (ODT) control of
 * theDQS/DQS# SSTL I/O is dynamically generated to enable the ODT during
 * readoperation and disabled otherwise. By setting this bit to '0' the
 * dynamic ODT featureis disabled. To control ODT statically this bit must
 * be set to '0' and DXnGCR0[1](DQSODT) is used to enable ODT (when set to
 * '1') or disable ODT(when set to '0').
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GCR . DX0_DQSRTT
 */
#define  VTSS_F_DDR_PHY_DX0GCR_DX0_DQSRTT(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_DDR_PHY_DX0GCR_DX0_DQSRTT     VTSS_BIT(9)
#define  VTSS_X_DDR_PHY_DX0GCR_DX0_DQSRTT(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * DQ Dynamic RTT Control: If set, the on die termination (ODT) control of
 * the DQ/DMSSTL I/O is dynamically generated to enable the ODT during read
 * operation anddisabled otherwise. By setting this bit to '0' the dynamic
 * ODT feature is disabled. Tocontrol ODT statically this bit must be set
 * to '0' and DXnGCR0[2] (DQODT) is usedto enable ODT (when set to '1') or
 * disable ODT(when set to '0').
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GCR . DX0_DQRTT
 */
#define  VTSS_F_DDR_PHY_DX0GCR_DX0_DQRTT(x)   VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_DDR_PHY_DX0GCR_DX0_DQRTT      VTSS_BIT(10)
#define  VTSS_X_DDR_PHY_DX0GCR_DX0_DQRTT(x)   VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * RTT Output Hold: Indicates the number of clock cycles (from 0 to 3)
 * after the readdata postamble for which ODT control should remain set to
 * DQSODT for DQS orDQODT for DQ/DM before disabling it (setting it to '0')
 * when using dynamic ODTcontrol. ODT is disabled almost RTTOH clock cycles
 * after the read postamble
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GCR . DX0_RTTOH
 */
#define  VTSS_F_DDR_PHY_DX0GCR_DX0_RTTOH(x)   VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_DDR_PHY_DX0GCR_DX0_RTTOH      VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_DDR_PHY_DX0GCR_DX0_RTTOH(x)   VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * RTT On Additive Latency: Indicates when the ODT control of DQ/DQS SSTL
 * I/Os isset to the value in DQODT/DQSODT during read cycles. Valid values
 * are:0 = ODT control is set to DQSODT/DQODT almost two cycles before read
 * datapreamble1 = ODT control is set to DQSODT/DQODT almost one cycle
 * before read datapreamble
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GCR . DX0_RTTOAL
 */
#define  VTSS_F_DDR_PHY_DX0GCR_DX0_RTTOAL(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DDR_PHY_DX0GCR_DX0_RTTOAL     VTSS_BIT(13)
#define  VTSS_X_DDR_PHY_DX0GCR_DX0_RTTOAL(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Data Byte Output Enable Override: Specifies whether the output I/O
 * output enablefor the byte lane should be set to a fixed value. Valid
 * values are:00 = No override. Output enable is controlled by DFI
 * transactions01 = Ouput enable is asserted (I/O is forced to output
 * mode).10 = Output enable is deasserted (I/O is forced to input mode)11 =
 * Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GCR . DX0_DXOEO
 */
#define  VTSS_F_DDR_PHY_DX0GCR_DX0_DXOEO(x)   VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_DDR_PHY_DX0GCR_DX0_DXOEO      VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_DDR_PHY_DX0GCR_DX0_DXOEO(x)   VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * PLL Rest: Resets the byte PLL by driving the PLL reset pin. This bit is
 * not selfclearingand a '0' must be written to deassert the reset. This
 * bit is ORed with theglobal PLLRST configuration bit
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GCR . DX0_PLLRST
 */
#define  VTSS_F_DDR_PHY_DX0GCR_DX0_PLLRST(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DDR_PHY_DX0GCR_DX0_PLLRST     VTSS_BIT(16)
#define  VTSS_X_DDR_PHY_DX0GCR_DX0_PLLRST(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * PLL Power Down: Puts the byte PLL in power down mode by driving the PLL
 * powerdown pin. This bit is not self-clearing and a '0' must be written
 * to deassert thepower-down. This bit is ORed with the global PLLPD
 * configuration bit
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GCR . DX0_PLLPD
 */
#define  VTSS_F_DDR_PHY_DX0GCR_DX0_PLLPD(x)   VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_DDR_PHY_DX0GCR_DX0_PLLPD      VTSS_BIT(17)
#define  VTSS_X_DDR_PHY_DX0GCR_DX0_PLLPD(x)   VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Gear Shift: Enables, if set, rapid locking mode on the byte PLL. This
 * bit is ORed withthe global GSHIFT configuration bit.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GCR . DX0_GSHIFT
 */
#define  VTSS_F_DDR_PHY_DX0GCR_DX0_GSHIFT(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_DDR_PHY_DX0GCR_DX0_GSHIFT     VTSS_BIT(18)
#define  VTSS_X_DDR_PHY_DX0GCR_DX0_GSHIFT(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * PLL Bypass: Puts the byte PLL in bypass mode by driving the PLL bypass
 * pin. Thisbit is not self-clearing and a '0' must be written to deassert
 * the bypass. This bit isORed with the global BYP configuration bit.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GCR . DX0_PLLBYP
 */
#define  VTSS_F_DDR_PHY_DX0GCR_DX0_PLLBYP(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_DDR_PHY_DX0GCR_DX0_PLLBYP     VTSS_BIT(19)
#define  VTSS_X_DDR_PHY_DX0GCR_DX0_PLLBYP(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Write Level Rank Enable: Specifies the ranks that should be write
 * leveled for thisbyte. Write leveling responses from ranks that are not
 * enabled for write leveling for aparticular byte are ignored and write
 * leveling is flagged as done for these ranks.WLRKEN[0] enables rank 0,
 * [1] enables rank 1, [2] enables rank 2, and [3] enablesrank 3.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GCR . DX0_WLRKEN
 */
#define  VTSS_F_DDR_PHY_DX0GCR_DX0_WLRKEN(x)  VTSS_ENCODE_BITFIELD(x,26,4)
#define  VTSS_M_DDR_PHY_DX0GCR_DX0_WLRKEN     VTSS_ENCODE_BITMASK(26,4)
#define  VTSS_X_DDR_PHY_DX0GCR_DX0_WLRKEN(x)  VTSS_EXTRACT_BITFIELD(x,26,4)

/**
 * \brief
 * Master Delay Line Enable: Enables, if set, the DATX8 master delay line
 * calibrationto perform subsequent period measurements following the
 * initial periodmeasurements that are performed after reset or when
 * calibration is manuallytriggered. These additional measurements are
 * accumulated and filtered as long asthis bit remains high. This bit is
 * ANDed with the common DATX8 MDL enable bit.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GCR . DX0_MDLEN
 */
#define  VTSS_F_DDR_PHY_DX0GCR_DX0_MDLEN(x)   VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_PHY_DX0GCR_DX0_MDLEN      VTSS_BIT(30)
#define  VTSS_X_DDR_PHY_DX0GCR_DX0_MDLEN(x)   VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Calibration Bypass: Prevents, if set, period measurement calibration
 * fromautomatically triggering after PHY initialization.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GCR . DX0_CALBYP
 */
#define  VTSS_F_DDR_PHY_DX0GCR_DX0_CALBYP(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_PHY_DX0GCR_DX0_CALBYP     VTSS_BIT(31)
#define  VTSS_X_DDR_PHY_DX0GCR_DX0_CALBYP(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief DX n General Status Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX0GSR0
 */
#define VTSS_DDR_PHY_DX0GSR0                 VTSS_IOREG(VTSS_TO_DDR_PHY,0x71)

/**
 * \brief
 * Write DQ Calibration: Indicates, if set, that the DATX8 has finished
 * doing periodmeasurement calibration for the write DQ LCDL.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR0 . DX0_WDQCAL
 */
#define  VTSS_F_DDR_PHY_DX0GSR0_DX0_WDQCAL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_DX0GSR0_DX0_WDQCAL    VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_DX0GSR0_DX0_WDQCAL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Read DQS Calibration: Indicates, if set, that the DATX8 has finished
 * doing periodmeasurement calibration for the read DQS LCDL.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR0 . DX0_RDQSCAL
 */
#define  VTSS_F_DDR_PHY_DX0GSR0_DX0_RDQSCAL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_PHY_DX0GSR0_DX0_RDQSCAL   VTSS_BIT(1)
#define  VTSS_X_DDR_PHY_DX0GSR0_DX0_RDQSCAL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Read DQS gating Calibration: Indicates, if set, that the DATX8 has
 * finished doingperiod measurement calibration for the read DQS gating
 * LCDL.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR0 . DX0_GDQSCAL
 */
#define  VTSS_F_DDR_PHY_DX0GSR0_DX0_GDQSCAL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_PHY_DX0GSR0_DX0_GDQSCAL   VTSS_BIT(3)
#define  VTSS_X_DDR_PHY_DX0GSR0_DX0_GDQSCAL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Write Leveling Calibration: Indicates, if set, that the DATX8 has
 * finished doingperiod measurement calibration for the write leveling
 * target delay line.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR0 . DX0_WLCAL
 */
#define  VTSS_F_DDR_PHY_DX0GSR0_DX0_WLCAL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_PHY_DX0GSR0_DX0_WLCAL     VTSS_BIT(4)
#define  VTSS_X_DDR_PHY_DX0GSR0_DX0_WLCAL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Write Leveling Done: Indicates, if set, that the DATX8 has completed
 * writeleveling.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR0 . DX0_WLDONE
 */
#define  VTSS_F_DDR_PHY_DX0GSR0_DX0_WLDONE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_PHY_DX0GSR0_DX0_WLDONE    VTSS_BIT(5)
#define  VTSS_X_DDR_PHY_DX0GSR0_DX0_WLDONE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Write Leveling Error: Indicates, if set, that there is a write leveling
 * error in theDATX8
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR0 . DX0_WLERR
 */
#define  VTSS_F_DDR_PHY_DX0GSR0_DX0_WLERR(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DDR_PHY_DX0GSR0_DX0_WLERR     VTSS_BIT(6)
#define  VTSS_X_DDR_PHY_DX0GSR0_DX0_WLERR(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Write Leveling Period: Returns the DDR clock period measured by the
 * writeleveling LCDL during calibration. The measured period is used to
 * generate thecontrol of the write leveling pipeline which is a function
 * of the write-leveling delayand the clock period. This value is PVT
 * compensated
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR0 . DX0_WLPRD
 */
#define  VTSS_F_DDR_PHY_DX0GSR0_DX0_WLPRD(x)  VTSS_ENCODE_BITFIELD(x,7,8)
#define  VTSS_M_DDR_PHY_DX0GSR0_DX0_WLPRD     VTSS_ENCODE_BITMASK(7,8)
#define  VTSS_X_DDR_PHY_DX0GSR0_DX0_WLPRD(x)  VTSS_EXTRACT_BITFIELD(x,7,8)

/**
 * \brief
 * DATX8 PLL Lock: Indicates, if set, that the DATX8 PLL has locked. This
 * is a directstatus of the DATX8 PLL lock pin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR0 . DX0_DPLOCK
 */
#define  VTSS_F_DDR_PHY_DX0GSR0_DX0_DPLOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_DDR_PHY_DX0GSR0_DX0_DPLOCK    VTSS_BIT(15)
#define  VTSS_X_DDR_PHY_DX0GSR0_DX0_DPLOCK(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Read DQS gating Period: Returns the DDR clock period measured by the
 * readDQS gating LCDL during calibration. This value is PVT compensated
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR0 . DX0_GDQSPRD
 */
#define  VTSS_F_DDR_PHY_DX0GSR0_DX0_GDQSPRD(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_PHY_DX0GSR0_DX0_GDQSPRD     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_PHY_DX0GSR0_DX0_GDQSPRD(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * DQS Gate Training Error: Indicates, if set, that there is an error in
 * DQS gatetraining. One bit for each of the up to 4 ranks.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR0 . DX0_QSGERR
 */
#define  VTSS_F_DDR_PHY_DX0GSR0_DX0_QSGERR(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_PHY_DX0GSR0_DX0_QSGERR     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_PHY_DX0GSR0_DX0_QSGERR(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * Write Leveling DQ Status: Captures the write leveling DQ status from the
 * DRAMduring software write leveling.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR0 . DX0_WLDQ
 */
#define  VTSS_F_DDR_PHY_DX0GSR0_DX0_WLDQ(x)   VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_DDR_PHY_DX0GSR0_DX0_WLDQ      VTSS_BIT(28)
#define  VTSS_X_DDR_PHY_DX0GSR0_DX0_WLDQ(x)   VTSS_EXTRACT_BITFIELD(x,28,1)


/**
 * \brief DX n General Status Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX0GSR1
 */
#define VTSS_DDR_PHY_DX0GSR1                 VTSS_IOREG(VTSS_TO_DDR_PHY,0x72)

/**
 * \brief
 * Delay Line Test Done: Indicates, if set, that the PHY control block has
 * finisheddoing period measurement of the DATX8 delay line digital test
 * output.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR1 . DX0_DLTDONE
 */
#define  VTSS_F_DDR_PHY_DX0GSR1_DX0_DLTDONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_DX0GSR1_DX0_DLTDONE   VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_DX0GSR1_DX0_DLTDONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Delay Line Test Code: Returns the code measured by the PHY control block
 * thatcorresponds to the period of the DATX8 delay line digital test
 * output.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR1 . DX0_DLTCODE
 */
#define  VTSS_F_DDR_PHY_DX0GSR1_DX0_DLTCODE(x)  VTSS_ENCODE_BITFIELD(x,1,24)
#define  VTSS_M_DDR_PHY_DX0GSR1_DX0_DLTCODE     VTSS_ENCODE_BITMASK(1,24)
#define  VTSS_X_DDR_PHY_DX0GSR1_DX0_DLTCODE(x)  VTSS_EXTRACT_BITFIELD(x,1,24)


/**
 * \brief DX n Bit Delay Line Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX0BDLR0
 */
#define VTSS_DDR_PHY_DX0BDLR0                VTSS_IOREG(VTSS_TO_DDR_PHY,0x73)

/**
 * \brief
 * DQ0 Write Bit Delay. Delay select for the BDL on DQ0 write path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR0 . DX0_DQ0WBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR0_DX0_DQ0WBD(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_PHY_DX0BDLR0_DX0_DQ0WBD     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_PHY_DX0BDLR0_DX0_DQ0WBD(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * DQ1 Write Bit Delay. Delay select for the BDL on DQ1 write path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR0 . DX0_DQ1WBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR0_DX0_DQ1WBD(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_DDR_PHY_DX0BDLR0_DX0_DQ1WBD     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_DDR_PHY_DX0BDLR0_DX0_DQ1WBD(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/**
 * \brief
 * DQ2 Write Bit Delay. Delay select for the BDL on DQ2 write path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR0 . DX0_DQ2WBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR0_DX0_DQ2WBD(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_DDR_PHY_DX0BDLR0_DX0_DQ2WBD     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_DDR_PHY_DX0BDLR0_DX0_DQ2WBD(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/**
 * \brief
 * DQ3 Write Bit Delay. Delay select for the BDL on DQ3 write path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR0 . DX0_DQ3WBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR0_DX0_DQ3WBD(x)  VTSS_ENCODE_BITFIELD(x,18,6)
#define  VTSS_M_DDR_PHY_DX0BDLR0_DX0_DQ3WBD     VTSS_ENCODE_BITMASK(18,6)
#define  VTSS_X_DDR_PHY_DX0BDLR0_DX0_DQ3WBD(x)  VTSS_EXTRACT_BITFIELD(x,18,6)

/**
 * \brief
 * DQ4 Write Bit Delay. Delay select for the BDL on DQ4 write path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR0 . DX0_DQ4WBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR0_DX0_DQ4WBD(x)  VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_DDR_PHY_DX0BDLR0_DX0_DQ4WBD     VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_DDR_PHY_DX0BDLR0_DX0_DQ4WBD(x)  VTSS_EXTRACT_BITFIELD(x,24,6)


/**
 * \brief DX n Bit Delay Line Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX0BDLR1
 */
#define VTSS_DDR_PHY_DX0BDLR1                VTSS_IOREG(VTSS_TO_DDR_PHY,0x74)

/**
 * \brief
 * DQ5 Write Bit Delay. Delay select for the BDL on DQ5 write path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR1 . DX0_DQ5WBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR1_DX0_DQ5WBD(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_PHY_DX0BDLR1_DX0_DQ5WBD     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_PHY_DX0BDLR1_DX0_DQ5WBD(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * DQ6 Write Bit Delay. Delay select for the BDL on DQ6 write path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR1 . DX0_DQ6WBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR1_DX0_DQ6WBD(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_DDR_PHY_DX0BDLR1_DX0_DQ6WBD     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_DDR_PHY_DX0BDLR1_DX0_DQ6WBD(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/**
 * \brief
 * DQ7 Write Bit Delay. Delay select for the BDL on DQ7 write path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR1 . DX0_DQ7WBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR1_DX0_DQ7WBD(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_DDR_PHY_DX0BDLR1_DX0_DQ7WBD     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_DDR_PHY_DX0BDLR1_DX0_DQ7WBD(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/**
 * \brief
 * DM Write Bit Delay: Delay select for the BDL on DM write path.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR1 . DX0_DMWBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR1_DX0_DMWBD(x)  VTSS_ENCODE_BITFIELD(x,18,6)
#define  VTSS_M_DDR_PHY_DX0BDLR1_DX0_DMWBD     VTSS_ENCODE_BITMASK(18,6)
#define  VTSS_X_DDR_PHY_DX0BDLR1_DX0_DMWBD(x)  VTSS_EXTRACT_BITFIELD(x,18,6)

/**
 * \brief
 * DQS Write Bit Delay: Delay select for the BDL on DQS write path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR1 . DX0_DSWBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR1_DX0_DSWBD(x)  VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_DDR_PHY_DX0BDLR1_DX0_DSWBD     VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_DDR_PHY_DX0BDLR1_DX0_DSWBD(x)  VTSS_EXTRACT_BITFIELD(x,24,6)


/**
 * \brief DX n Bit Delay Line Register 2
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX0BDLR2
 */
#define VTSS_DDR_PHY_DX0BDLR2                VTSS_IOREG(VTSS_TO_DDR_PHY,0x75)

/**
 * \brief
 * DQS Output Enable Bit Delay: Delay select for the BDL on DQS output
 * enable path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR2 . DX0_DSOEBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR2_DX0_DSOEBD(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_PHY_DX0BDLR2_DX0_DSOEBD     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_PHY_DX0BDLR2_DX0_DSOEBD(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * DQ Output Enable Bit Delay: Delay select for the BDL on DQ/DM output
 * enablepath.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR2 . DX0_DQOEBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR2_DX0_DQOEBD(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_DDR_PHY_DX0BDLR2_DX0_DQOEBD     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_DDR_PHY_DX0BDLR2_DX0_DQOEBD(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/**
 * \brief
 * DQS Read Bit Delay: Delay select for the BDL on DQS read path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR2 . DX0_DSRBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR2_DX0_DSRBD(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_DDR_PHY_DX0BDLR2_DX0_DSRBD     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_DDR_PHY_DX0BDLR2_DX0_DSRBD(x)  VTSS_EXTRACT_BITFIELD(x,12,6)


/**
 * \brief DX n Bit Delay Line Register 3
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX0BDLR3
 */
#define VTSS_DDR_PHY_DX0BDLR3                VTSS_IOREG(VTSS_TO_DDR_PHY,0x76)

/**
 * \brief
 * DQ0 Read Bit Delay: Delay select for the BDL on DQ0 read path.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR3 . DX0_DQ0RBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR3_DX0_DQ0RBD(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_PHY_DX0BDLR3_DX0_DQ0RBD     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_PHY_DX0BDLR3_DX0_DQ0RBD(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * DQ1 Read Bit Delay: Delay select for the BDL on DQ1 read path.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR3 . DX0_DQ1RBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR3_DX0_DQ1RBD(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_DDR_PHY_DX0BDLR3_DX0_DQ1RBD     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_DDR_PHY_DX0BDLR3_DX0_DQ1RBD(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/**
 * \brief
 * DQ2 Read Bit Delay: Delay select for the BDL on DQ2 read path.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR3 . DX0_DQ2RBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR3_DX0_DQ2RBD(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_DDR_PHY_DX0BDLR3_DX0_DQ2RBD     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_DDR_PHY_DX0BDLR3_DX0_DQ2RBD(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/**
 * \brief
 * DQ3 Read Bit Delay: Delay select for the BDL on DQ3 read path.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR3 . DX0_DQ3RBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR3_DX0_DQ3RBD(x)  VTSS_ENCODE_BITFIELD(x,18,6)
#define  VTSS_M_DDR_PHY_DX0BDLR3_DX0_DQ3RBD     VTSS_ENCODE_BITMASK(18,6)
#define  VTSS_X_DDR_PHY_DX0BDLR3_DX0_DQ3RBD(x)  VTSS_EXTRACT_BITFIELD(x,18,6)

/**
 * \brief
 * DQ4 Read Bit Delay: Delay select for the BDL on DQ4 read path.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR3 . DX0_DQ4RBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR3_DX0_DQ4RBD(x)  VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_DDR_PHY_DX0BDLR3_DX0_DQ4RBD     VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_DDR_PHY_DX0BDLR3_DX0_DQ4RBD(x)  VTSS_EXTRACT_BITFIELD(x,24,6)


/**
 * \brief DX n Bit Delay Line Register 4
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX0BDLR4
 */
#define VTSS_DDR_PHY_DX0BDLR4                VTSS_IOREG(VTSS_TO_DDR_PHY,0x77)

/**
 * \brief
 * DQ5 Read Bit Delay: Delay select for the BDL on DQ5 read path.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR4 . DX0_DQ5RBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR4_DX0_DQ5RBD(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_PHY_DX0BDLR4_DX0_DQ5RBD     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_PHY_DX0BDLR4_DX0_DQ5RBD(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * DQ6 Read Bit Delay: Delay select for the BDL on DQ6 read path.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR4 . DX0_DQ6RBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR4_DX0_DQ6RBD(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_DDR_PHY_DX0BDLR4_DX0_DQ6RBD     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_DDR_PHY_DX0BDLR4_DX0_DQ6RBD(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/**
 * \brief
 * DQ7 Read Bit Delay: Delay select for the BDL on DQ7 read path.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR4 . DX0_DQ7RBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR4_DX0_DQ7RBD(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_DDR_PHY_DX0BDLR4_DX0_DQ7RBD     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_DDR_PHY_DX0BDLR4_DX0_DQ7RBD(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/**
 * \brief
 * DM Read Bit Delay: Delay select for the BDL on DM read path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0BDLR4 . DX0_DMRBD
 */
#define  VTSS_F_DDR_PHY_DX0BDLR4_DX0_DMRBD(x)  VTSS_ENCODE_BITFIELD(x,18,6)
#define  VTSS_M_DDR_PHY_DX0BDLR4_DX0_DMRBD     VTSS_ENCODE_BITMASK(18,6)
#define  VTSS_X_DDR_PHY_DX0BDLR4_DX0_DMRBD(x)  VTSS_EXTRACT_BITFIELD(x,18,6)


/**
 * \brief DX n Local Calibrated Delay Line Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX0LCDLR0
 */
#define VTSS_DDR_PHY_DX0LCDLR0               VTSS_IOREG(VTSS_TO_DDR_PHY,0x78)

/**
 * \brief
 * Rank 0 Write Leveling Delay: Rank 0 delay select for the write leveling
 * (WL) LCDL
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0LCDLR0 . DX0_R0WLD
 */
#define  VTSS_F_DDR_PHY_DX0LCDLR0_DX0_R0WLD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_PHY_DX0LCDLR0_DX0_R0WLD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_PHY_DX0LCDLR0_DX0_R0WLD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Rank 1 Write Leveling Delay: Rank 1 delay select for the write leveling
 * (WL) LCDL
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0LCDLR0 . DX0_R1WLD
 */
#define  VTSS_F_DDR_PHY_DX0LCDLR0_DX0_R1WLD(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DDR_PHY_DX0LCDLR0_DX0_R1WLD     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DDR_PHY_DX0LCDLR0_DX0_R1WLD(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Rank 2 Write Leveling Delay: Rank 2 delay select for the write leveling
 * (WL) LCDL
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0LCDLR0 . DX0_R2WLD
 */
#define  VTSS_F_DDR_PHY_DX0LCDLR0_DX0_R2WLD(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_PHY_DX0LCDLR0_DX0_R2WLD     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_PHY_DX0LCDLR0_DX0_R2WLD(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Rank 3 Write Leveling Delay: Rank 3 delay select for the write leveling
 * (WL) LCDL
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0LCDLR0 . DX0_R3WLD
 */
#define  VTSS_F_DDR_PHY_DX0LCDLR0_DX0_R3WLD(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DDR_PHY_DX0LCDLR0_DX0_R3WLD     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DDR_PHY_DX0LCDLR0_DX0_R3WLD(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief DX n Local Calibrated Delay Line Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX0LCDLR1
 */
#define VTSS_DDR_PHY_DX0LCDLR1               VTSS_IOREG(VTSS_TO_DDR_PHY,0x79)

/**
 * \brief
 * Write Data Delay: Delay select for the write data (WDQ) LCDL
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0LCDLR1 . DX0_WDQD
 */
#define  VTSS_F_DDR_PHY_DX0LCDLR1_DX0_WDQD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_PHY_DX0LCDLR1_DX0_WDQD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_PHY_DX0LCDLR1_DX0_WDQD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Read DQS Delay: Delay select for the read DQS (RDQS) LCDL
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0LCDLR1 . DX0_RDQSD
 */
#define  VTSS_F_DDR_PHY_DX0LCDLR1_DX0_RDQSD(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DDR_PHY_DX0LCDLR1_DX0_RDQSD     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DDR_PHY_DX0LCDLR1_DX0_RDQSD(x)  VTSS_EXTRACT_BITFIELD(x,8,8)


/**
 * \brief DX n Local Calibrated Delay Line Register 2
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX0LCDLR2
 */
#define VTSS_DDR_PHY_DX0LCDLR2               VTSS_IOREG(VTSS_TO_DDR_PHY,0x7a)

/**
 * \brief
 * Rank 0 Read DQS Gating Delay: Rank 0 delay select for the read DQS
 * gating(DQSG) LCDL
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0LCDLR2 . DX0_R0DQSGD
 */
#define  VTSS_F_DDR_PHY_DX0LCDLR2_DX0_R0DQSGD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_PHY_DX0LCDLR2_DX0_R0DQSGD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_PHY_DX0LCDLR2_DX0_R0DQSGD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Rank 1 Read DQS Gating Delay: Rank 1 delay select for the read DQS
 * gating(DQSG) LCDL
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0LCDLR2 . DX0_R1DQSGD
 */
#define  VTSS_F_DDR_PHY_DX0LCDLR2_DX0_R1DQSGD(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DDR_PHY_DX0LCDLR2_DX0_R1DQSGD     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DDR_PHY_DX0LCDLR2_DX0_R1DQSGD(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Rank 2 Read DQS Gating Delay: Rank 2 delay select for the read DQS
 * gating(DQSG) LCDL
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0LCDLR2 . DX0_R2DQSGD
 */
#define  VTSS_F_DDR_PHY_DX0LCDLR2_DX0_R2DQSGD(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_PHY_DX0LCDLR2_DX0_R2DQSGD     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_PHY_DX0LCDLR2_DX0_R2DQSGD(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Rank 3 Read DQS Gating Delay: Rank 3 delay select for the read DQS
 * gating(DQSG) LCDL
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0LCDLR2 . DX0_R3DQSGD
 */
#define  VTSS_F_DDR_PHY_DX0LCDLR2_DX0_R3DQSGD(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DDR_PHY_DX0LCDLR2_DX0_R3DQSGD     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DDR_PHY_DX0LCDLR2_DX0_R3DQSGD(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief DX n Master Delay Line Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX0MDLR
 */
#define VTSS_DDR_PHY_DX0MDLR                 VTSS_IOREG(VTSS_TO_DDR_PHY,0x7b)

/**
 * \brief
 * Initial Period: Initial period measured by the master delay line
 * calibration for VT driftcompensation. This value is used as the
 * denominator when calculating the ratios ofupdates during VT
 * compensation.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0MDLR . DX0_IPRD
 */
#define  VTSS_F_DDR_PHY_DX0MDLR_DX0_IPRD(x)   VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_PHY_DX0MDLR_DX0_IPRD      VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_PHY_DX0MDLR_DX0_IPRD(x)   VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Target Period: Target period measured by the master delay line
 * calibration for VTdrift compensation. This is the current measured value
 * of the period and iscontinuously updated if the MDL is enabled to do so
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0MDLR . DX0_TPRD
 */
#define  VTSS_F_DDR_PHY_DX0MDLR_DX0_TPRD(x)   VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DDR_PHY_DX0MDLR_DX0_TPRD      VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DDR_PHY_DX0MDLR_DX0_TPRD(x)   VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * MDL Delay: Delay select for the LCDL for the Master Delay Line.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0MDLR . DX0_MDLD
 */
#define  VTSS_F_DDR_PHY_DX0MDLR_DX0_MDLD(x)   VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_PHY_DX0MDLR_DX0_MDLD      VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_PHY_DX0MDLR_DX0_MDLD(x)   VTSS_EXTRACT_BITFIELD(x,16,8)


/**
 * \brief DX n General Timing Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX0GTR
 */
#define VTSS_DDR_PHY_DX0GTR                  VTSS_IOREG(VTSS_TO_DDR_PHY,0x7c)

/**
 * \brief
 * Rank n DQS Gating System Latency: This is used to increase the number of
 * clockcycles needed to expect valid DDR read data by up to seven extra
 * clock cycles.This is used to compensate for board delays and other
 * system delays. Power-updefault is 000 (i.e. no extra clock cycles
 * required). The SL fields are initially set bythe PUB during automatic
 * DQS data training but these values can be overwrittenby a direct write
 * to this register. Every three bits of this register control the
 * latencyof each of the (up to) four ranks. R0DGSL controls the latency of
 * rank 0, R1DGSLcontrols rank 1, and so on. Valid values are 0 to 7:
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GTR . DX0_DGSL
 */
#define  VTSS_F_DDR_PHY_DX0GTR_DX0_DGSL(x)    VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_PHY_DX0GTR_DX0_DGSL       VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_PHY_DX0GTR_DX0_DGSL(x)    VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Rank n Write Leveling System Latency: This is used to adjust the write
 * latencyafter write leveling. Power-up default is 01 (i.e. no extra clock
 * cycles required). TheSL fields are initially set by the PUB during
 * automatic write leveling but thesevalues can be overwritten by a direct
 * write to this register. Every two bits of thisregister control the
 * latency of each of the (up to) four ranks. R0WLSL controls thelatency of
 * rank 0, R1WLSL controls rank 1, and so on. Valid values:00 = Write
 * latency = WL - 101 = Write latency = WL10 = Write latency = WL + 111 =
 * Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GTR . DX0_WLSL
 */
#define  VTSS_F_DDR_PHY_DX0GTR_DX0_WLSL(x)    VTSS_ENCODE_BITFIELD(x,12,8)
#define  VTSS_M_DDR_PHY_DX0GTR_DX0_WLSL       VTSS_ENCODE_BITMASK(12,8)
#define  VTSS_X_DDR_PHY_DX0GTR_DX0_WLSL(x)    VTSS_EXTRACT_BITFIELD(x,12,8)


/**
 * \brief DATX8 General Status Register 2
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX0GSR2
 */
#define VTSS_DDR_PHY_DX0GSR2                 VTSS_IOREG(VTSS_TO_DDR_PHY,0x7d)

/**
 * \brief
 * Read Bit Deskew Error: Indicates, if set, that the DATX8 has encountered
 * an errorduring execution of the read bit deskew training
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR2 . DX0_RDERR
 */
#define  VTSS_F_DDR_PHY_DX0GSR2_DX0_RDERR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_DX0GSR2_DX0_RDERR     VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_DX0GSR2_DX0_RDERR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Read Bit Deskew Warning: Indicates, if set, that the DATX8 has
 * encountered awarning during execution of the read bit deskew training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR2 . DX0_RDWN
 */
#define  VTSS_F_DDR_PHY_DX0GSR2_DX0_RDWN(x)   VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_PHY_DX0GSR2_DX0_RDWN      VTSS_BIT(1)
#define  VTSS_X_DDR_PHY_DX0GSR2_DX0_RDWN(x)   VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Write Bit Deskew Error: Indicates, if set, that the DATX8 has
 * encountered an errorduring execution of the write bit deskew training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR2 . DX0_WDERR
 */
#define  VTSS_F_DDR_PHY_DX0GSR2_DX0_WDERR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_PHY_DX0GSR2_DX0_WDERR     VTSS_BIT(2)
#define  VTSS_X_DDR_PHY_DX0GSR2_DX0_WDERR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Write Bit Deskew Warning: Indicates, if set, that the DATX8 has
 * encountered awarning during execution of the write bit deskew training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR2 . DX0_WDWN
 */
#define  VTSS_F_DDR_PHY_DX0GSR2_DX0_WDWN(x)   VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_PHY_DX0GSR2_DX0_WDWN      VTSS_BIT(3)
#define  VTSS_X_DDR_PHY_DX0GSR2_DX0_WDWN(x)   VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Read Eye Centering Error: Indicates, if set, that the DATX8 has
 * encountered anerror during execution of the read eye centering training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR2 . DX0_REERR
 */
#define  VTSS_F_DDR_PHY_DX0GSR2_DX0_REERR(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_PHY_DX0GSR2_DX0_REERR     VTSS_BIT(4)
#define  VTSS_X_DDR_PHY_DX0GSR2_DX0_REERR(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Read Eye Centering Warning: Indicates, if set, that the DATX8 has
 * encountered awarning during execution of the read eye centering
 * training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR2 . DX0_REWN
 */
#define  VTSS_F_DDR_PHY_DX0GSR2_DX0_REWN(x)   VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_PHY_DX0GSR2_DX0_REWN      VTSS_BIT(5)
#define  VTSS_X_DDR_PHY_DX0GSR2_DX0_REWN(x)   VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Write Eye Centering Error: Indicates, if set, that the DATX8 has
 * encountered anerror during execution of the write eye centering
 * training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR2 . DX0_WEERR
 */
#define  VTSS_F_DDR_PHY_DX0GSR2_DX0_WEERR(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DDR_PHY_DX0GSR2_DX0_WEERR     VTSS_BIT(6)
#define  VTSS_X_DDR_PHY_DX0GSR2_DX0_WEERR(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Write Eye Centering Warning: Indicates, if set, that the DATX8 has
 * encountered awarning during execution of the write eye centering
 * training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR2 . DX0_WEWN
 */
#define  VTSS_F_DDR_PHY_DX0GSR2_DX0_WEWN(x)   VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DDR_PHY_DX0GSR2_DX0_WEWN      VTSS_BIT(7)
#define  VTSS_X_DDR_PHY_DX0GSR2_DX0_WEWN(x)   VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Error Status: If an error occurred for this lane as indicated by RDERR,
 * WDERR,REERR or WEERR the error status code can provide additional
 * information regardwhen the error occurred during the algorithm
 * execution.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX0GSR2 . DX0_ESTAT
 */
#define  VTSS_F_DDR_PHY_DX0GSR2_DX0_ESTAT(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_PHY_DX0GSR2_DX0_ESTAT     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_PHY_DX0GSR2_DX0_ESTAT(x)  VTSS_EXTRACT_BITFIELD(x,8,4)


/**
 * \brief DX n General Configuration Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX1GCR
 */
#define VTSS_DDR_PHY_DX1GCR                  VTSS_IOREG(VTSS_TO_DDR_PHY,0x80)

/**
 * \brief
 * Data Byte Enable: Enables, if set, the data byte. Setting this bit to
 * '0' disables thebyte, i.e. the byte is not used in PHY initialization or
 * training and is ignored duringSDRAM read/write operations
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GCR . DX1_DXEN
 */
#define  VTSS_F_DDR_PHY_DX1GCR_DX1_DXEN(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_DX1GCR_DX1_DXEN       VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_DX1GCR_DX1_DXEN(x)    VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * DQS On-Die Termination: Enables, when set, the on-die termination on the
 * I/O forDQS/DQS# pin of the byte. This bit is ORed with the common DATX8
 * ODTconfiguration bit
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GCR . DX1_DQSODT
 */
#define  VTSS_F_DDR_PHY_DX1GCR_DX1_DQSODT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_PHY_DX1GCR_DX1_DQSODT     VTSS_BIT(1)
#define  VTSS_X_DDR_PHY_DX1GCR_DX1_DQSODT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Data On-Die Termination: Enables, when set, the on-die termination on
 * the I/O forDQ and DM pins of the byte. This bit is ORed with the common
 * DATX8 ODTconfiguration bit
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GCR . DX1_DQODT
 */
#define  VTSS_F_DDR_PHY_DX1GCR_DX1_DQODT(x)   VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_PHY_DX1GCR_DX1_DQODT      VTSS_BIT(2)
#define  VTSS_X_DDR_PHY_DX1GCR_DX1_DQODT(x)   VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Data I/O Mode: Selects SSTL mode (when set to 0) or CMOS mode (when set
 * to 1)of the I/O for DQ, DM, and DQS/DQS# pins of the byte. This bit is
 * ORed with theIOM configuration bit of the individual DATX8
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GCR . DX1_DXIOM
 */
#define  VTSS_F_DDR_PHY_DX1GCR_DX1_DXIOM(x)   VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_PHY_DX1GCR_DX1_DXIOM      VTSS_BIT(3)
#define  VTSS_X_DDR_PHY_DX1GCR_DX1_DXIOM(x)   VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Data Power Down Driver: Powers down, when set, the output driver on I/O
 * for DQ,DM, and DQS/DQS# pins of the byte. This bit is ORed with the
 * common PDDconfiguration bit
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GCR . DX1_DXPDD
 */
#define  VTSS_F_DDR_PHY_DX1GCR_DX1_DXPDD(x)   VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_PHY_DX1GCR_DX1_DXPDD      VTSS_BIT(4)
#define  VTSS_X_DDR_PHY_DX1GCR_DX1_DXPDD(x)   VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Data Power Down Receiver: Powers down, when set, the input receiver on
 * I/O forDQ, DM, and DQS/DQS# pins of the byte. This bit is ORed with the
 * common PDRconfiguration bit
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GCR . DX1_DXPDR
 */
#define  VTSS_F_DDR_PHY_DX1GCR_DX1_DXPDR(x)   VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_PHY_DX1GCR_DX1_DXPDR      VTSS_BIT(5)
#define  VTSS_X_DDR_PHY_DX1GCR_DX1_DXPDR(x)   VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DQSR Power Down: Powers down, if set, the PDQSR cell. This bit is ORed
 * with thecommon PDR configuration bit
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GCR . DX1_DQSRPD
 */
#define  VTSS_F_DDR_PHY_DX1GCR_DX1_DQSRPD(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DDR_PHY_DX1GCR_DX1_DQSRPD     VTSS_BIT(6)
#define  VTSS_X_DDR_PHY_DX1GCR_DX1_DQSRPD(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Write DQS Enable: Controls whether the write DQS going to the SDRAM is
 * enabled(toggling) or disabled (static value) and whether the DQS is
 * inverted. DQS# isalways the inversion of DQS. These values are valid
 * only when DQS/DQS# outputenable is on, otherwise the DQS/DQS# is
 * tri-stated. Valid settings are:00 = Reserved01 = DQS toggling with
 * normal polarity (This should be the default setting)10 = Reserved11 =
 * Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GCR . DX1_DSEN
 */
#define  VTSS_F_DDR_PHY_DX1GCR_DX1_DSEN(x)    VTSS_ENCODE_BITFIELD(x,7,2)
#define  VTSS_M_DDR_PHY_DX1GCR_DX1_DSEN       VTSS_ENCODE_BITMASK(7,2)
#define  VTSS_X_DDR_PHY_DX1GCR_DX1_DSEN(x)    VTSS_EXTRACT_BITFIELD(x,7,2)

/**
 * \brief
 * DQS Dynamic RTT Control: If set, the on die termination (ODT) control of
 * theDQS/DQS# SSTL I/O is dynamically generated to enable the ODT during
 * readoperation and disabled otherwise. By setting this bit to '0' the
 * dynamic ODT featureis disabled. To control ODT statically this bit must
 * be set to '0' and DXnGCR0[1](DQSODT) is used to enable ODT (when set to
 * '1') or disable ODT(when set to '0').
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GCR . DX1_DQSRTT
 */
#define  VTSS_F_DDR_PHY_DX1GCR_DX1_DQSRTT(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_DDR_PHY_DX1GCR_DX1_DQSRTT     VTSS_BIT(9)
#define  VTSS_X_DDR_PHY_DX1GCR_DX1_DQSRTT(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * DQ Dynamic RTT Control: If set, the on die termination (ODT) control of
 * the DQ/DMSSTL I/O is dynamically generated to enable the ODT during read
 * operation anddisabled otherwise. By setting this bit to '0' the dynamic
 * ODT feature is disabled. Tocontrol ODT statically this bit must be set
 * to '0' and DXnGCR0[2] (DQODT) is usedto enable ODT (when set to '1') or
 * disable ODT(when set to '0').
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GCR . DX1_DQRTT
 */
#define  VTSS_F_DDR_PHY_DX1GCR_DX1_DQRTT(x)   VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_DDR_PHY_DX1GCR_DX1_DQRTT      VTSS_BIT(10)
#define  VTSS_X_DDR_PHY_DX1GCR_DX1_DQRTT(x)   VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * RTT Output Hold: Indicates the number of clock cycles (from 0 to 3)
 * after the readdata postamble for which ODT control should remain set to
 * DQSODT for DQS orDQODT for DQ/DM before disabling it (setting it to '0')
 * when using dynamic ODTcontrol. ODT is disabled almost RTTOH clock cycles
 * after the read postamble
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GCR . DX1_RTTOH
 */
#define  VTSS_F_DDR_PHY_DX1GCR_DX1_RTTOH(x)   VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_DDR_PHY_DX1GCR_DX1_RTTOH      VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_DDR_PHY_DX1GCR_DX1_RTTOH(x)   VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * RTT On Additive Latency: Indicates when the ODT control of DQ/DQS SSTL
 * I/Os isset to the value in DQODT/DQSODT during read cycles. Valid values
 * are:0 = ODT control is set to DQSODT/DQODT almost two cycles before read
 * datapreamble1 = ODT control is set to DQSODT/DQODT almost one cycle
 * before read datapreamble
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GCR . DX1_RTTOAL
 */
#define  VTSS_F_DDR_PHY_DX1GCR_DX1_RTTOAL(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DDR_PHY_DX1GCR_DX1_RTTOAL     VTSS_BIT(13)
#define  VTSS_X_DDR_PHY_DX1GCR_DX1_RTTOAL(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Data Byte Output Enable Override: Specifies whether the output I/O
 * output enablefor the byte lane should be set to a fixed value. Valid
 * values are:00 = No override. Output enable is controlled by DFI
 * transactions01 = Ouput enable is asserted (I/O is forced to output
 * mode).10 = Output enable is deasserted (I/O is forced to input mode)11 =
 * Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GCR . DX1_DXOEO
 */
#define  VTSS_F_DDR_PHY_DX1GCR_DX1_DXOEO(x)   VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_DDR_PHY_DX1GCR_DX1_DXOEO      VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_DDR_PHY_DX1GCR_DX1_DXOEO(x)   VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * PLL Rest: Resets the byte PLL by driving the PLL reset pin. This bit is
 * not selfclearingand a '0' must be written to deassert the reset. This
 * bit is ORed with theglobal PLLRST configuration bit
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GCR . DX1_PLLRST
 */
#define  VTSS_F_DDR_PHY_DX1GCR_DX1_PLLRST(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DDR_PHY_DX1GCR_DX1_PLLRST     VTSS_BIT(16)
#define  VTSS_X_DDR_PHY_DX1GCR_DX1_PLLRST(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * PLL Power Down: Puts the byte PLL in power down mode by driving the PLL
 * powerdown pin. This bit is not self-clearing and a '0' must be written
 * to deassert thepower-down. This bit is ORed with the global PLLPD
 * configuration bit
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GCR . DX1_PLLPD
 */
#define  VTSS_F_DDR_PHY_DX1GCR_DX1_PLLPD(x)   VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_DDR_PHY_DX1GCR_DX1_PLLPD      VTSS_BIT(17)
#define  VTSS_X_DDR_PHY_DX1GCR_DX1_PLLPD(x)   VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Gear Shift: Enables, if set, rapid locking mode on the byte PLL. This
 * bit is ORed withthe global GSHIFT configuration bit.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GCR . DX1_GSHIFT
 */
#define  VTSS_F_DDR_PHY_DX1GCR_DX1_GSHIFT(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_DDR_PHY_DX1GCR_DX1_GSHIFT     VTSS_BIT(18)
#define  VTSS_X_DDR_PHY_DX1GCR_DX1_GSHIFT(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * PLL Bypass: Puts the byte PLL in bypass mode by driving the PLL bypass
 * pin. Thisbit is not self-clearing and a '0' must be written to deassert
 * the bypass. This bit isORed with the global BYP configuration bit.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GCR . DX1_PLLBYP
 */
#define  VTSS_F_DDR_PHY_DX1GCR_DX1_PLLBYP(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_DDR_PHY_DX1GCR_DX1_PLLBYP     VTSS_BIT(19)
#define  VTSS_X_DDR_PHY_DX1GCR_DX1_PLLBYP(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Write Level Rank Enable: Specifies the ranks that should be write
 * leveled for thisbyte. Write leveling responses from ranks that are not
 * enabled for write leveling for aparticular byte are ignored and write
 * leveling is flagged as done for these ranks.WLRKEN[0] enables rank 0,
 * [1] enables rank 1, [2] enables rank 2, and [3] enablesrank 3.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GCR . DX1_WLRKEN
 */
#define  VTSS_F_DDR_PHY_DX1GCR_DX1_WLRKEN(x)  VTSS_ENCODE_BITFIELD(x,26,4)
#define  VTSS_M_DDR_PHY_DX1GCR_DX1_WLRKEN     VTSS_ENCODE_BITMASK(26,4)
#define  VTSS_X_DDR_PHY_DX1GCR_DX1_WLRKEN(x)  VTSS_EXTRACT_BITFIELD(x,26,4)

/**
 * \brief
 * Master Delay Line Enable: Enables, if set, the DATX8 master delay line
 * calibrationto perform subsequent period measurements following the
 * initial periodmeasurements that are performed after reset or when
 * calibration is manuallytriggered. These additional measurements are
 * accumulated and filtered as long asthis bit remains high. This bit is
 * ANDed with the common DATX8 MDL enable bit.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GCR . DX1_MDLEN
 */
#define  VTSS_F_DDR_PHY_DX1GCR_DX1_MDLEN(x)   VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_PHY_DX1GCR_DX1_MDLEN      VTSS_BIT(30)
#define  VTSS_X_DDR_PHY_DX1GCR_DX1_MDLEN(x)   VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Calibration Bypass: Prevents, if set, period measurement calibration
 * fromautomatically triggering after PHY initialization.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GCR . DX1_CALBYP
 */
#define  VTSS_F_DDR_PHY_DX1GCR_DX1_CALBYP(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_PHY_DX1GCR_DX1_CALBYP     VTSS_BIT(31)
#define  VTSS_X_DDR_PHY_DX1GCR_DX1_CALBYP(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief DX n General Status Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX1GSR0
 */
#define VTSS_DDR_PHY_DX1GSR0                 VTSS_IOREG(VTSS_TO_DDR_PHY,0x81)

/**
 * \brief
 * Write DQ Calibration: Indicates, if set, that the DATX8 has finished
 * doing periodmeasurement calibration for the write DQ LCDL.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR0 . DX1_WDQCAL
 */
#define  VTSS_F_DDR_PHY_DX1GSR0_DX1_WDQCAL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_DX1GSR0_DX1_WDQCAL    VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_DX1GSR0_DX1_WDQCAL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Read DQS Calibration: Indicates, if set, that the DATX8 has finished
 * doing periodmeasurement calibration for the read DQS LCDL.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR0 . DX1_RDQSCAL
 */
#define  VTSS_F_DDR_PHY_DX1GSR0_DX1_RDQSCAL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_PHY_DX1GSR0_DX1_RDQSCAL   VTSS_BIT(1)
#define  VTSS_X_DDR_PHY_DX1GSR0_DX1_RDQSCAL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Read DQS gating Calibration: Indicates, if set, that the DATX8 has
 * finished doingperiod measurement calibration for the read DQS gating
 * LCDL.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR0 . DX1_GDQSCAL
 */
#define  VTSS_F_DDR_PHY_DX1GSR0_DX1_GDQSCAL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_PHY_DX1GSR0_DX1_GDQSCAL   VTSS_BIT(3)
#define  VTSS_X_DDR_PHY_DX1GSR0_DX1_GDQSCAL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Write Leveling Calibration: Indicates, if set, that the DATX8 has
 * finished doingperiod measurement calibration for the write leveling
 * target delay line.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR0 . DX1_WLCAL
 */
#define  VTSS_F_DDR_PHY_DX1GSR0_DX1_WLCAL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_PHY_DX1GSR0_DX1_WLCAL     VTSS_BIT(4)
#define  VTSS_X_DDR_PHY_DX1GSR0_DX1_WLCAL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Write Leveling Done: Indicates, if set, that the DATX8 has completed
 * writeleveling.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR0 . DX1_WLDONE
 */
#define  VTSS_F_DDR_PHY_DX1GSR0_DX1_WLDONE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_PHY_DX1GSR0_DX1_WLDONE    VTSS_BIT(5)
#define  VTSS_X_DDR_PHY_DX1GSR0_DX1_WLDONE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Write Leveling Error: Indicates, if set, that there is a write leveling
 * error in theDATX8
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR0 . DX1_WLERR
 */
#define  VTSS_F_DDR_PHY_DX1GSR0_DX1_WLERR(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DDR_PHY_DX1GSR0_DX1_WLERR     VTSS_BIT(6)
#define  VTSS_X_DDR_PHY_DX1GSR0_DX1_WLERR(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Write Leveling Period: Returns the DDR clock period measured by the
 * writeleveling LCDL during calibration. The measured period is used to
 * generate thecontrol of the write leveling pipeline which is a function
 * of the write-leveling delayand the clock period. This value is PVT
 * compensated
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR0 . DX1_WLPRD
 */
#define  VTSS_F_DDR_PHY_DX1GSR0_DX1_WLPRD(x)  VTSS_ENCODE_BITFIELD(x,7,8)
#define  VTSS_M_DDR_PHY_DX1GSR0_DX1_WLPRD     VTSS_ENCODE_BITMASK(7,8)
#define  VTSS_X_DDR_PHY_DX1GSR0_DX1_WLPRD(x)  VTSS_EXTRACT_BITFIELD(x,7,8)

/**
 * \brief
 * DATX8 PLL Lock: Indicates, if set, that the DATX8 PLL has locked. This
 * is a directstatus of the DATX8 PLL lock pin.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR0 . DX1_DPLOCK
 */
#define  VTSS_F_DDR_PHY_DX1GSR0_DX1_DPLOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_DDR_PHY_DX1GSR0_DX1_DPLOCK    VTSS_BIT(15)
#define  VTSS_X_DDR_PHY_DX1GSR0_DX1_DPLOCK(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Read DQS gating Period: Returns the DDR clock period measured by the
 * readDQS gating LCDL during calibration. This value is PVT compensated
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR0 . DX1_GDQSPRD
 */
#define  VTSS_F_DDR_PHY_DX1GSR0_DX1_GDQSPRD(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_PHY_DX1GSR0_DX1_GDQSPRD     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_PHY_DX1GSR0_DX1_GDQSPRD(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * DQS Gate Training Error: Indicates, if set, that there is an error in
 * DQS gatetraining. One bit for each of the up to 4 ranks.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR0 . DX1_QSGERR
 */
#define  VTSS_F_DDR_PHY_DX1GSR0_DX1_QSGERR(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_PHY_DX1GSR0_DX1_QSGERR     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_PHY_DX1GSR0_DX1_QSGERR(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * Write Leveling DQ Status: Captures the write leveling DQ status from the
 * DRAMduring software write leveling.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR0 . DX1_WLDQ
 */
#define  VTSS_F_DDR_PHY_DX1GSR0_DX1_WLDQ(x)   VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_DDR_PHY_DX1GSR0_DX1_WLDQ      VTSS_BIT(28)
#define  VTSS_X_DDR_PHY_DX1GSR0_DX1_WLDQ(x)   VTSS_EXTRACT_BITFIELD(x,28,1)


/**
 * \brief DX n General Status Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX1GSR1
 */
#define VTSS_DDR_PHY_DX1GSR1                 VTSS_IOREG(VTSS_TO_DDR_PHY,0x82)

/**
 * \brief
 * Delay Line Test Done: Indicates, if set, that the PHY control block has
 * finisheddoing period measurement of the DATX8 delay line digital test
 * output.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR1 . DX1_DLTDONE
 */
#define  VTSS_F_DDR_PHY_DX1GSR1_DX1_DLTDONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_DX1GSR1_DX1_DLTDONE   VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_DX1GSR1_DX1_DLTDONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Delay Line Test Code: Returns the code measured by the PHY control block
 * thatcorresponds to the period of the DATX8 delay line digital test
 * output.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR1 . DX1_DLTCODE
 */
#define  VTSS_F_DDR_PHY_DX1GSR1_DX1_DLTCODE(x)  VTSS_ENCODE_BITFIELD(x,1,24)
#define  VTSS_M_DDR_PHY_DX1GSR1_DX1_DLTCODE     VTSS_ENCODE_BITMASK(1,24)
#define  VTSS_X_DDR_PHY_DX1GSR1_DX1_DLTCODE(x)  VTSS_EXTRACT_BITFIELD(x,1,24)


/**
 * \brief DX n Bit Delay Line Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX1BDLR0
 */
#define VTSS_DDR_PHY_DX1BDLR0                VTSS_IOREG(VTSS_TO_DDR_PHY,0x83)

/**
 * \brief
 * DQ0 Write Bit Delay. Delay select for the BDL on DQ0 write path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR0 . DX1_DQ0WBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR0_DX1_DQ0WBD(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_PHY_DX1BDLR0_DX1_DQ0WBD     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_PHY_DX1BDLR0_DX1_DQ0WBD(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * DQ1 Write Bit Delay. Delay select for the BDL on DQ1 write path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR0 . DX1_DQ1WBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR0_DX1_DQ1WBD(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_DDR_PHY_DX1BDLR0_DX1_DQ1WBD     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_DDR_PHY_DX1BDLR0_DX1_DQ1WBD(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/**
 * \brief
 * DQ2 Write Bit Delay. Delay select for the BDL on DQ2 write path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR0 . DX1_DQ2WBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR0_DX1_DQ2WBD(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_DDR_PHY_DX1BDLR0_DX1_DQ2WBD     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_DDR_PHY_DX1BDLR0_DX1_DQ2WBD(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/**
 * \brief
 * DQ3 Write Bit Delay. Delay select for the BDL on DQ3 write path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR0 . DX1_DQ3WBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR0_DX1_DQ3WBD(x)  VTSS_ENCODE_BITFIELD(x,18,6)
#define  VTSS_M_DDR_PHY_DX1BDLR0_DX1_DQ3WBD     VTSS_ENCODE_BITMASK(18,6)
#define  VTSS_X_DDR_PHY_DX1BDLR0_DX1_DQ3WBD(x)  VTSS_EXTRACT_BITFIELD(x,18,6)

/**
 * \brief
 * DQ4 Write Bit Delay. Delay select for the BDL on DQ4 write path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR0 . DX1_DQ4WBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR0_DX1_DQ4WBD(x)  VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_DDR_PHY_DX1BDLR0_DX1_DQ4WBD     VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_DDR_PHY_DX1BDLR0_DX1_DQ4WBD(x)  VTSS_EXTRACT_BITFIELD(x,24,6)


/**
 * \brief DX n Bit Delay Line Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX1BDLR1
 */
#define VTSS_DDR_PHY_DX1BDLR1                VTSS_IOREG(VTSS_TO_DDR_PHY,0x84)

/**
 * \brief
 * DQ5 Write Bit Delay. Delay select for the BDL on DQ5 write path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR1 . DX1_DQ5WBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR1_DX1_DQ5WBD(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_PHY_DX1BDLR1_DX1_DQ5WBD     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_PHY_DX1BDLR1_DX1_DQ5WBD(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * DQ6 Write Bit Delay. Delay select for the BDL on DQ6 write path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR1 . DX1_DQ6WBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR1_DX1_DQ6WBD(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_DDR_PHY_DX1BDLR1_DX1_DQ6WBD     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_DDR_PHY_DX1BDLR1_DX1_DQ6WBD(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/**
 * \brief
 * DQ7 Write Bit Delay. Delay select for the BDL on DQ7 write path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR1 . DX1_DQ7WBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR1_DX1_DQ7WBD(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_DDR_PHY_DX1BDLR1_DX1_DQ7WBD     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_DDR_PHY_DX1BDLR1_DX1_DQ7WBD(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/**
 * \brief
 * DM Write Bit Delay: Delay select for the BDL on DM write path.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR1 . DX1_DMWBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR1_DX1_DMWBD(x)  VTSS_ENCODE_BITFIELD(x,18,6)
#define  VTSS_M_DDR_PHY_DX1BDLR1_DX1_DMWBD     VTSS_ENCODE_BITMASK(18,6)
#define  VTSS_X_DDR_PHY_DX1BDLR1_DX1_DMWBD(x)  VTSS_EXTRACT_BITFIELD(x,18,6)

/**
 * \brief
 * DQS Write Bit Delay: Delay select for the BDL on DQS write path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR1 . DX1_DSWBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR1_DX1_DSWBD(x)  VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_DDR_PHY_DX1BDLR1_DX1_DSWBD     VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_DDR_PHY_DX1BDLR1_DX1_DSWBD(x)  VTSS_EXTRACT_BITFIELD(x,24,6)


/**
 * \brief DX n Bit Delay Line Register 2
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX1BDLR2
 */
#define VTSS_DDR_PHY_DX1BDLR2                VTSS_IOREG(VTSS_TO_DDR_PHY,0x85)

/**
 * \brief
 * DQS Output Enable Bit Delay: Delay select for the BDL on DQS output
 * enable path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR2 . DX1_DSOEBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR2_DX1_DSOEBD(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_PHY_DX1BDLR2_DX1_DSOEBD     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_PHY_DX1BDLR2_DX1_DSOEBD(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * DQ Output Enable Bit Delay: Delay select for the BDL on DQ/DM output
 * enablepath.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR2 . DX1_DQOEBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR2_DX1_DQOEBD(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_DDR_PHY_DX1BDLR2_DX1_DQOEBD     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_DDR_PHY_DX1BDLR2_DX1_DQOEBD(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/**
 * \brief
 * DQS Read Bit Delay: Delay select for the BDL on DQS read path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR2 . DX1_DSRBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR2_DX1_DSRBD(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_DDR_PHY_DX1BDLR2_DX1_DSRBD     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_DDR_PHY_DX1BDLR2_DX1_DSRBD(x)  VTSS_EXTRACT_BITFIELD(x,12,6)


/**
 * \brief DX n Bit Delay Line Register 3
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX1BDLR3
 */
#define VTSS_DDR_PHY_DX1BDLR3                VTSS_IOREG(VTSS_TO_DDR_PHY,0x86)

/**
 * \brief
 * DQ0 Read Bit Delay: Delay select for the BDL on DQ0 read path.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR3 . DX1_DQ0RBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR3_DX1_DQ0RBD(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_PHY_DX1BDLR3_DX1_DQ0RBD     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_PHY_DX1BDLR3_DX1_DQ0RBD(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * DQ1 Read Bit Delay: Delay select for the BDL on DQ1 read path.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR3 . DX1_DQ1RBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR3_DX1_DQ1RBD(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_DDR_PHY_DX1BDLR3_DX1_DQ1RBD     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_DDR_PHY_DX1BDLR3_DX1_DQ1RBD(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/**
 * \brief
 * DQ2 Read Bit Delay: Delay select for the BDL on DQ2 read path.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR3 . DX1_DQ2RBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR3_DX1_DQ2RBD(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_DDR_PHY_DX1BDLR3_DX1_DQ2RBD     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_DDR_PHY_DX1BDLR3_DX1_DQ2RBD(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/**
 * \brief
 * DQ3 Read Bit Delay: Delay select for the BDL on DQ3 read path.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR3 . DX1_DQ3RBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR3_DX1_DQ3RBD(x)  VTSS_ENCODE_BITFIELD(x,18,6)
#define  VTSS_M_DDR_PHY_DX1BDLR3_DX1_DQ3RBD     VTSS_ENCODE_BITMASK(18,6)
#define  VTSS_X_DDR_PHY_DX1BDLR3_DX1_DQ3RBD(x)  VTSS_EXTRACT_BITFIELD(x,18,6)

/**
 * \brief
 * DQ4 Read Bit Delay: Delay select for the BDL on DQ4 read path.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR3 . DX1_DQ4RBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR3_DX1_DQ4RBD(x)  VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_DDR_PHY_DX1BDLR3_DX1_DQ4RBD     VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_DDR_PHY_DX1BDLR3_DX1_DQ4RBD(x)  VTSS_EXTRACT_BITFIELD(x,24,6)


/**
 * \brief DX n Bit Delay Line Register 4
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX1BDLR4
 */
#define VTSS_DDR_PHY_DX1BDLR4                VTSS_IOREG(VTSS_TO_DDR_PHY,0x87)

/**
 * \brief
 * DQ5 Read Bit Delay: Delay select for the BDL on DQ5 read path.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR4 . DX1_DQ5RBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR4_DX1_DQ5RBD(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_PHY_DX1BDLR4_DX1_DQ5RBD     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_PHY_DX1BDLR4_DX1_DQ5RBD(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * DQ6 Read Bit Delay: Delay select for the BDL on DQ6 read path.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR4 . DX1_DQ6RBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR4_DX1_DQ6RBD(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_DDR_PHY_DX1BDLR4_DX1_DQ6RBD     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_DDR_PHY_DX1BDLR4_DX1_DQ6RBD(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/**
 * \brief
 * DQ7 Read Bit Delay: Delay select for the BDL on DQ7 read path.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR4 . DX1_DQ7RBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR4_DX1_DQ7RBD(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_DDR_PHY_DX1BDLR4_DX1_DQ7RBD     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_DDR_PHY_DX1BDLR4_DX1_DQ7RBD(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/**
 * \brief
 * DM Read Bit Delay: Delay select for the BDL on DM read path
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1BDLR4 . DX1_DMRBD
 */
#define  VTSS_F_DDR_PHY_DX1BDLR4_DX1_DMRBD(x)  VTSS_ENCODE_BITFIELD(x,18,6)
#define  VTSS_M_DDR_PHY_DX1BDLR4_DX1_DMRBD     VTSS_ENCODE_BITMASK(18,6)
#define  VTSS_X_DDR_PHY_DX1BDLR4_DX1_DMRBD(x)  VTSS_EXTRACT_BITFIELD(x,18,6)


/**
 * \brief DX n Local Calibrated Delay Line Register 0
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX1LCDLR0
 */
#define VTSS_DDR_PHY_DX1LCDLR0               VTSS_IOREG(VTSS_TO_DDR_PHY,0x88)

/**
 * \brief
 * Rank 0 Write Leveling Delay: Rank 0 delay select for the write leveling
 * (WL) LCDL
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1LCDLR0 . DX1_R0WLD
 */
#define  VTSS_F_DDR_PHY_DX1LCDLR0_DX1_R0WLD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_PHY_DX1LCDLR0_DX1_R0WLD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_PHY_DX1LCDLR0_DX1_R0WLD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Rank 1 Write Leveling Delay: Rank 1 delay select for the write leveling
 * (WL) LCDL
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1LCDLR0 . DX1_R1WLD
 */
#define  VTSS_F_DDR_PHY_DX1LCDLR0_DX1_R1WLD(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DDR_PHY_DX1LCDLR0_DX1_R1WLD     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DDR_PHY_DX1LCDLR0_DX1_R1WLD(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Rank 2 Write Leveling Delay: Rank 2 delay select for the write leveling
 * (WL) LCDL
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1LCDLR0 . DX1_R2WLD
 */
#define  VTSS_F_DDR_PHY_DX1LCDLR0_DX1_R2WLD(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_PHY_DX1LCDLR0_DX1_R2WLD     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_PHY_DX1LCDLR0_DX1_R2WLD(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Rank 3 Write Leveling Delay: Rank 3 delay select for the write leveling
 * (WL) LCDL
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1LCDLR0 . DX1_R3WLD
 */
#define  VTSS_F_DDR_PHY_DX1LCDLR0_DX1_R3WLD(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DDR_PHY_DX1LCDLR0_DX1_R3WLD     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DDR_PHY_DX1LCDLR0_DX1_R3WLD(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief DX n Local Calibrated Delay Line Register 1
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX1LCDLR1
 */
#define VTSS_DDR_PHY_DX1LCDLR1               VTSS_IOREG(VTSS_TO_DDR_PHY,0x89)

/**
 * \brief
 * Write Data Delay: Delay select for the write data (WDQ) LCDL
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1LCDLR1 . DX1_WDQD
 */
#define  VTSS_F_DDR_PHY_DX1LCDLR1_DX1_WDQD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_PHY_DX1LCDLR1_DX1_WDQD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_PHY_DX1LCDLR1_DX1_WDQD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Read DQS Delay: Delay select for the read DQS (RDQS) LCDL
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1LCDLR1 . DX1_RDQSD
 */
#define  VTSS_F_DDR_PHY_DX1LCDLR1_DX1_RDQSD(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DDR_PHY_DX1LCDLR1_DX1_RDQSD     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DDR_PHY_DX1LCDLR1_DX1_RDQSD(x)  VTSS_EXTRACT_BITFIELD(x,8,8)


/**
 * \brief DX n Local Calibrated Delay Line Register 2
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX1LCDLR2
 */
#define VTSS_DDR_PHY_DX1LCDLR2               VTSS_IOREG(VTSS_TO_DDR_PHY,0x8a)

/**
 * \brief
 * Rank 0 Read DQS Gating Delay: Rank 0 delay select for the read DQS
 * gating(DQSG) LCDL
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1LCDLR2 . DX1_R0DQSGD
 */
#define  VTSS_F_DDR_PHY_DX1LCDLR2_DX1_R0DQSGD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_PHY_DX1LCDLR2_DX1_R0DQSGD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_PHY_DX1LCDLR2_DX1_R0DQSGD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Rank 1 Read DQS Gating Delay: Rank 1 delay select for the read DQS
 * gating(DQSG) LCDL
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1LCDLR2 . DX1_R1DQSGD
 */
#define  VTSS_F_DDR_PHY_DX1LCDLR2_DX1_R1DQSGD(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DDR_PHY_DX1LCDLR2_DX1_R1DQSGD     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DDR_PHY_DX1LCDLR2_DX1_R1DQSGD(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Rank 2 Read DQS Gating Delay: Rank 2 delay select for the read DQS
 * gating(DQSG) LCDL
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1LCDLR2 . DX1_R2DQSGD
 */
#define  VTSS_F_DDR_PHY_DX1LCDLR2_DX1_R2DQSGD(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_PHY_DX1LCDLR2_DX1_R2DQSGD     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_PHY_DX1LCDLR2_DX1_R2DQSGD(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Rank 3 Read DQS Gating Delay: Rank 3 delay select for the read DQS
 * gating(DQSG) LCDL
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1LCDLR2 . DX1_R3DQSGD
 */
#define  VTSS_F_DDR_PHY_DX1LCDLR2_DX1_R3DQSGD(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DDR_PHY_DX1LCDLR2_DX1_R3DQSGD     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DDR_PHY_DX1LCDLR2_DX1_R3DQSGD(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief DX n Master Delay Line Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX1MDLR
 */
#define VTSS_DDR_PHY_DX1MDLR                 VTSS_IOREG(VTSS_TO_DDR_PHY,0x8b)

/**
 * \brief
 * Initial Period: Initial period measured by the master delay line
 * calibration for VT driftcompensation. This value is used as the
 * denominator when calculating the ratios ofupdates during VT
 * compensation.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1MDLR . DX1_IPRD
 */
#define  VTSS_F_DDR_PHY_DX1MDLR_DX1_IPRD(x)   VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_PHY_DX1MDLR_DX1_IPRD      VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_PHY_DX1MDLR_DX1_IPRD(x)   VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Target Period: Target period measured by the master delay line
 * calibration for VTdrift compensation. This is the current measured value
 * of the period and iscontinuously updated if the MDL is enabled to do so
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1MDLR . DX1_TPRD
 */
#define  VTSS_F_DDR_PHY_DX1MDLR_DX1_TPRD(x)   VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DDR_PHY_DX1MDLR_DX1_TPRD      VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DDR_PHY_DX1MDLR_DX1_TPRD(x)   VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * MDL Delay: Delay select for the LCDL for the Master Delay Line.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1MDLR . DX1_MDLD
 */
#define  VTSS_F_DDR_PHY_DX1MDLR_DX1_MDLD(x)   VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_PHY_DX1MDLR_DX1_MDLD      VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_PHY_DX1MDLR_DX1_MDLD(x)   VTSS_EXTRACT_BITFIELD(x,16,8)


/**
 * \brief DX n General Timing Register
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX1GTR
 */
#define VTSS_DDR_PHY_DX1GTR                  VTSS_IOREG(VTSS_TO_DDR_PHY,0x8c)

/**
 * \brief
 * Rank n DQS Gating System Latency: This is used to increase the number of
 * clockcycles needed to expect valid DDR read data by up to seven extra
 * clock cycles.This is used to compensate for board delays and other
 * system delays. Power-updefault is 000 (i.e. no extra clock cycles
 * required). The SL fields are initially set bythe PUB during automatic
 * DQS data training but these values can be overwrittenby a direct write
 * to this register. Every three bits of this register control the
 * latencyof each of the (up to) four ranks. R0DGSL controls the latency of
 * rank 0, R1DGSLcontrols rank 1, and so on. Valid values are 0 to 7:
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GTR . DX1_DGSL
 */
#define  VTSS_F_DDR_PHY_DX1GTR_DX1_DGSL(x)    VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_PHY_DX1GTR_DX1_DGSL       VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_PHY_DX1GTR_DX1_DGSL(x)    VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Rank n Write Leveling System Latency: This is used to adjust the write
 * latencyafter write leveling. Power-up default is 01 (i.e. no extra clock
 * cycles required). TheSL fields are initially set by the PUB during
 * automatic write leveling but thesevalues can be overwritten by a direct
 * write to this register. Every two bits of thisregister control the
 * latency of each of the (up to) four ranks. R0WLSL controls thelatency of
 * rank 0, R1WLSL controls rank 1, and so on. Valid values:00 = Write
 * latency = WL - 101 = Write latency = WL10 = Write latency = WL + 111 =
 * Reserved
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GTR . DX1_WLSL
 */
#define  VTSS_F_DDR_PHY_DX1GTR_DX1_WLSL(x)    VTSS_ENCODE_BITFIELD(x,12,8)
#define  VTSS_M_DDR_PHY_DX1GTR_DX1_WLSL       VTSS_ENCODE_BITMASK(12,8)
#define  VTSS_X_DDR_PHY_DX1GTR_DX1_WLSL(x)    VTSS_EXTRACT_BITFIELD(x,12,8)


/**
 * \brief DATX8 General Status Register 2
 *
 * \details
 * Register: \a DDR_PHY:DDR3_2_PHY_PUB:DX1GSR2
 */
#define VTSS_DDR_PHY_DX1GSR2                 VTSS_IOREG(VTSS_TO_DDR_PHY,0x8d)

/**
 * \brief
 * Read Bit Deskew Error: Indicates, if set, that the DATX8 has encountered
 * an errorduring execution of the read bit deskew training
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR2 . DX1_RDERR
 */
#define  VTSS_F_DDR_PHY_DX1GSR2_DX1_RDERR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_PHY_DX1GSR2_DX1_RDERR     VTSS_BIT(0)
#define  VTSS_X_DDR_PHY_DX1GSR2_DX1_RDERR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Read Bit Deskew Warning: Indicates, if set, that the DATX8 has
 * encountered awarning during execution of the read bit deskew training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR2 . DX1_RDWN
 */
#define  VTSS_F_DDR_PHY_DX1GSR2_DX1_RDWN(x)   VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_PHY_DX1GSR2_DX1_RDWN      VTSS_BIT(1)
#define  VTSS_X_DDR_PHY_DX1GSR2_DX1_RDWN(x)   VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Write Bit Deskew Error: Indicates, if set, that the DATX8 has
 * encountered an errorduring execution of the write bit deskew training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR2 . DX1_WDERR
 */
#define  VTSS_F_DDR_PHY_DX1GSR2_DX1_WDERR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_PHY_DX1GSR2_DX1_WDERR     VTSS_BIT(2)
#define  VTSS_X_DDR_PHY_DX1GSR2_DX1_WDERR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Write Bit Deskew Warning: Indicates, if set, that the DATX8 has
 * encountered awarning during execution of the write bit deskew training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR2 . DX1_WDWN
 */
#define  VTSS_F_DDR_PHY_DX1GSR2_DX1_WDWN(x)   VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_PHY_DX1GSR2_DX1_WDWN      VTSS_BIT(3)
#define  VTSS_X_DDR_PHY_DX1GSR2_DX1_WDWN(x)   VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Read Eye Centering Error: Indicates, if set, that the DATX8 has
 * encountered anerror during execution of the read eye centering training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR2 . DX1_REERR
 */
#define  VTSS_F_DDR_PHY_DX1GSR2_DX1_REERR(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_PHY_DX1GSR2_DX1_REERR     VTSS_BIT(4)
#define  VTSS_X_DDR_PHY_DX1GSR2_DX1_REERR(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Read Eye Centering Warning: Indicates, if set, that the DATX8 has
 * encountered awarning during execution of the read eye centering
 * training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR2 . DX1_REWN
 */
#define  VTSS_F_DDR_PHY_DX1GSR2_DX1_REWN(x)   VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_PHY_DX1GSR2_DX1_REWN      VTSS_BIT(5)
#define  VTSS_X_DDR_PHY_DX1GSR2_DX1_REWN(x)   VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Write Eye Centering Error: Indicates, if set, that the DATX8 has
 * encountered anerror during execution of the write eye centering
 * training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR2 . DX1_WEERR
 */
#define  VTSS_F_DDR_PHY_DX1GSR2_DX1_WEERR(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DDR_PHY_DX1GSR2_DX1_WEERR     VTSS_BIT(6)
#define  VTSS_X_DDR_PHY_DX1GSR2_DX1_WEERR(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Write Eye Centering Warning: Indicates, if set, that the DATX8 has
 * encountered awarning during execution of the write eye centering
 * training.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR2 . DX1_WEWN
 */
#define  VTSS_F_DDR_PHY_DX1GSR2_DX1_WEWN(x)   VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DDR_PHY_DX1GSR2_DX1_WEWN      VTSS_BIT(7)
#define  VTSS_X_DDR_PHY_DX1GSR2_DX1_WEWN(x)   VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Error Status: If an error occurred for this lane as indicated by RDERR,
 * WDERR,REERR or WEERR the error status code can provide additional
 * information regardwhen the error occurred during the algorithm
 * execution.
 *
 * \details
 * Field: ::VTSS_DDR_PHY_DX1GSR2 . DX1_ESTAT
 */
#define  VTSS_F_DDR_PHY_DX1GSR2_DX1_ESTAT(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_PHY_DX1GSR2_DX1_ESTAT     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_PHY_DX1GSR2_DX1_ESTAT(x)  VTSS_EXTRACT_BITFIELD(x,8,4)


#endif /* _VTSS_LAGUNA_REGS_DDR_PHY_H_ */
