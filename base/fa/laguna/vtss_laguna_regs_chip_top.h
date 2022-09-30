// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_CHIP_TOP_H_
#define _VTSS_LAGUNA_REGS_CHIP_TOP_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a CHIP_TOP
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a CHIP_TOP:SJTAG_MUX_CFG
 *
 * Controls the mux of the SJTAG.
 */


/**
 * \brief Controls the mux of the SJTAG.
 *
 * \details
 * Register: \a CHIP_TOP:SJTAG_MUX_CFG:SJTAG_MUX_CTRL
 */
#define VTSS_CHIP_TOP_SJTAG_MUX_CTRL         VTSS_IOREG(VTSS_TO_CHIP_TOP,0x0)

/**
 * \brief
 * One-shot event. Write 1 to set HOLD on the SJTAG mux. This action has an
 * effect only if the SJTAG is already in OPEN mode.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_SJTAG_MUX_CTRL . HOLD_SET
 */
#define  VTSS_F_CHIP_TOP_SJTAG_MUX_CTRL_HOLD_SET(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CHIP_TOP_SJTAG_MUX_CTRL_HOLD_SET  VTSS_BIT(2)
#define  VTSS_X_CHIP_TOP_SJTAG_MUX_CTRL_HOLD_SET(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * One-shot event. Write 1 to clear the HOLD on the SJTAG mux.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_SJTAG_MUX_CTRL . HOLD_CLR
 */
#define  VTSS_F_CHIP_TOP_SJTAG_MUX_CTRL_HOLD_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CHIP_TOP_SJTAG_MUX_CTRL_HOLD_CLR  VTSS_BIT(1)
#define  VTSS_X_CHIP_TOP_SJTAG_MUX_CTRL_HOLD_CLR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Status of HOLD on SJTAG mux.
 *
 * \details
 * 1: The selection of the SJTAG mux is locked. Any change in the SJTAG IP
 * or the SJTAG strapping will not have any effect. Pin reset does not
 * change the mux selection. Only a power-cycle , or writing to HOLD_CLR
 * can release the SJTAG mux.
 * 0: The SJTAG mux selection is controlled by the SJTAG IP and the
 * strapping.
 *
 * Field: ::VTSS_CHIP_TOP_SJTAG_MUX_CTRL . HOLD_STAT
 */
#define  VTSS_F_CHIP_TOP_SJTAG_MUX_CTRL_HOLD_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_SJTAG_MUX_CTRL_HOLD_STAT  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_SJTAG_MUX_CTRL_HOLD_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a CHIP_TOP:RESET_CFG
 *
 * Not documented
 */


/**
 * \brief Configuration of chip reset
 *
 * \details
 * Register: \a CHIP_TOP:RESET_CFG:RESET_CFG
 */
#define VTSS_CHIP_TOP_RESET_CFG              VTSS_IOREG(VTSS_TO_CHIP_TOP,0x1)

/**
 * \brief
 * Power good signal from ovuv028_IPTOP pad cell.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_RESET_CFG . POWER_GOOD_STATUS
 */
#define  VTSS_F_CHIP_TOP_RESET_CFG_POWER_GOOD_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CHIP_TOP_RESET_CFG_POWER_GOOD_STATUS  VTSS_BIT(2)
#define  VTSS_X_CHIP_TOP_RESET_CFG_POWER_GOOD_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * When enabled the over voltage monitor is allowed to do a chip reset in
 * case an over voltage event is detected.
 *
 * \details
 * 0: Disable OV reset
 * 1: Allow OV reset
 *
 * Field: ::VTSS_CHIP_TOP_RESET_CFG . OV_RST_ENA
 */
#define  VTSS_F_CHIP_TOP_RESET_CFG_OV_RST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CHIP_TOP_RESET_CFG_OV_RST_ENA  VTSS_BIT(1)
#define  VTSS_X_CHIP_TOP_RESET_CFG_OV_RST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * When enabled the under voltage monitor is allowed to do a chip reset in
 * case an under voltage event is detected.
 *
 * \details
 * 0: Disable UV reset
 * 1: Allow UV reset
 *
 * Field: ::VTSS_CHIP_TOP_RESET_CFG . UV_RST_ENA
 */
#define  VTSS_F_CHIP_TOP_RESET_CFG_UV_RST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_RESET_CFG_UV_RST_ENA  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_RESET_CFG_UV_RST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a CHIP_TOP:MBIST_STAT
 *
 * Status of power on memory BIST
 */


/**
 * \brief Chip memory BIST status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:MBIST_STAT
 */
#define VTSS_CHIP_TOP_MBIST_STAT             VTSS_IOREG(VTSS_TO_CHIP_TOP,0x2)

/**
 * \brief
 * The power on MBIST testing of all memories has passed
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_MBIST_STAT . MBIST_PASS
 */
#define  VTSS_F_CHIP_TOP_MBIST_STAT_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CHIP_TOP_MBIST_STAT_MBIST_PASS  VTSS_BIT(2)
#define  VTSS_X_CHIP_TOP_MBIST_STAT_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * The power on MBIST testing has completed
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_MBIST_STAT . MBIST_DONE
 */
#define  VTSS_F_CHIP_TOP_MBIST_STAT_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CHIP_TOP_MBIST_STAT_MBIST_DONE  VTSS_BIT(1)
#define  VTSS_X_CHIP_TOP_MBIST_STAT_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * The MBIST did not complete within expected time
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_MBIST_STAT . MBIST_TIMED_OUT
 */
#define  VTSS_F_CHIP_TOP_MBIST_STAT_MBIST_TIMED_OUT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_MBIST_STAT_MBIST_TIMED_OUT  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_MBIST_STAT_MBIST_TIMED_OUT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief RB memory bist pass status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:RB_MBIST_PASS
 */
#define VTSS_CHIP_TOP_RB_MBIST_PASS          VTSS_IOREG(VTSS_TO_CHIP_TOP,0x3)

/**
 * \brief
 * The RB MBIST has passed
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_RB_MBIST_PASS . RB_MBIST_PASS
 */
#define  VTSS_F_CHIP_TOP_RB_MBIST_PASS_RB_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_CHIP_TOP_RB_MBIST_PASS_RB_MBIST_PASS     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_CHIP_TOP_RB_MBIST_PASS_RB_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief RB memory bist done status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:RB_MBIST_DONE
 */
#define VTSS_CHIP_TOP_RB_MBIST_DONE          VTSS_IOREG(VTSS_TO_CHIP_TOP,0x4)

/**
 * \brief
 * The RB MBIST is done
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_RB_MBIST_DONE . RB_MBIST_DONE
 */
#define  VTSS_F_CHIP_TOP_RB_MBIST_DONE_RB_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_CHIP_TOP_RB_MBIST_DONE_RB_MBIST_DONE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_CHIP_TOP_RB_MBIST_DONE_RB_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief ASM memory bist pass status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:ASM_MBIST_PASS
 */
#define VTSS_CHIP_TOP_ASM_MBIST_PASS         VTSS_IOREG(VTSS_TO_CHIP_TOP,0x5)

/**
 * \brief
 * The ASM MBIST has passed
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_ASM_MBIST_PASS . ASM_MBIST_PASS
 */
#define  VTSS_F_CHIP_TOP_ASM_MBIST_PASS_ASM_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_ASM_MBIST_PASS_ASM_MBIST_PASS  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_ASM_MBIST_PASS_ASM_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief ASM memory bist done status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:ASM_MBIST_DONE
 */
#define VTSS_CHIP_TOP_ASM_MBIST_DONE         VTSS_IOREG(VTSS_TO_CHIP_TOP,0x6)

/**
 * \brief
 * The ASM MBIST is done
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_ASM_MBIST_DONE . ASM_MBIST_DONE
 */
#define  VTSS_F_CHIP_TOP_ASM_MBIST_DONE_ASM_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_ASM_MBIST_DONE_ASM_MBIST_DONE  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_ASM_MBIST_DONE_ASM_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief QSYS memory bist pass status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:QSYS_MBIST_PASS
 */
#define VTSS_CHIP_TOP_QSYS_MBIST_PASS        VTSS_IOREG(VTSS_TO_CHIP_TOP,0x7)

/**
 * \brief
 * The QSYS MBIST has passed
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_QSYS_MBIST_PASS . QSYS_MBIST_PASS
 */
#define  VTSS_F_CHIP_TOP_QSYS_MBIST_PASS_QSYS_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_QSYS_MBIST_PASS_QSYS_MBIST_PASS  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_QSYS_MBIST_PASS_QSYS_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief QSYS memory bist done status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:QSYS_MBIST_DONE
 */
#define VTSS_CHIP_TOP_QSYS_MBIST_DONE        VTSS_IOREG(VTSS_TO_CHIP_TOP,0x8)

/**
 * \brief
 * The QSYS MBIST is done
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_QSYS_MBIST_DONE . QSYS_MBIST_DONE
 */
#define  VTSS_F_CHIP_TOP_QSYS_MBIST_DONE_QSYS_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_QSYS_MBIST_DONE_QSYS_MBIST_DONE  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_QSYS_MBIST_DONE_QSYS_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief PMEM memory bist pass status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:PMEM_MBIST_PASS
 */
#define VTSS_CHIP_TOP_PMEM_MBIST_PASS        VTSS_IOREG(VTSS_TO_CHIP_TOP,0x9)

/**
 * \brief
 * The PMEM MBIST has passed
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_PMEM_MBIST_PASS . PMEM_MBIST_PASS
 */
#define  VTSS_F_CHIP_TOP_PMEM_MBIST_PASS_PMEM_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_PMEM_MBIST_PASS_PMEM_MBIST_PASS  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_PMEM_MBIST_PASS_PMEM_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief PMEM memory bist done status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:PMEM_MBIST_DONE
 */
#define VTSS_CHIP_TOP_PMEM_MBIST_DONE        VTSS_IOREG(VTSS_TO_CHIP_TOP,0xa)

/**
 * \brief
 * The PMEM MBIST is done
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_PMEM_MBIST_DONE . PMEM_MBIST_DONE
 */
#define  VTSS_F_CHIP_TOP_PMEM_MBIST_DONE_PMEM_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_PMEM_MBIST_DONE_PMEM_MBIST_DONE  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_PMEM_MBIST_DONE_PMEM_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief VCAP memory bist pass status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:VCAP_MBIST_PASS
 */
#define VTSS_CHIP_TOP_VCAP_MBIST_PASS        VTSS_IOREG(VTSS_TO_CHIP_TOP,0xb)

/**
 * \brief
 * The VCAP MBIST has passed
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_VCAP_MBIST_PASS . VCAP_MBIST_PASS
 */
#define  VTSS_F_CHIP_TOP_VCAP_MBIST_PASS_VCAP_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_VCAP_MBIST_PASS_VCAP_MBIST_PASS  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_VCAP_MBIST_PASS_VCAP_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief VCAP memory bist done status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:VCAP_MBIST_DONE
 */
#define VTSS_CHIP_TOP_VCAP_MBIST_DONE        VTSS_IOREG(VTSS_TO_CHIP_TOP,0xc)

/**
 * \brief
 * The VCAP MBIST is done
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_VCAP_MBIST_DONE . VCAP_MBIST_DONE
 */
#define  VTSS_F_CHIP_TOP_VCAP_MBIST_DONE_VCAP_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_VCAP_MBIST_DONE_VCAP_MBIST_DONE  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_VCAP_MBIST_DONE_VCAP_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief ANA_CL32 memory bist pass status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:ANA_CL32_MBIST_PASS
 */
#define VTSS_CHIP_TOP_ANA_CL32_MBIST_PASS    VTSS_IOREG(VTSS_TO_CHIP_TOP,0xd)

/**
 * \brief
 * The ANA_CL32 MBIST has passed
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_ANA_CL32_MBIST_PASS . ANA_CL32_MBIST_PASS
 */
#define  VTSS_F_CHIP_TOP_ANA_CL32_MBIST_PASS_ANA_CL32_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_ANA_CL32_MBIST_PASS_ANA_CL32_MBIST_PASS  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_ANA_CL32_MBIST_PASS_ANA_CL32_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief ANA_CL32 memory bist done status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:ANA_CL32_MBIST_DONE
 */
#define VTSS_CHIP_TOP_ANA_CL32_MBIST_DONE    VTSS_IOREG(VTSS_TO_CHIP_TOP,0xe)

/**
 * \brief
 * The ANA_CL32 MBIST is done
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_ANA_CL32_MBIST_DONE . ANA_CL32_MBIST_DONE
 */
#define  VTSS_F_CHIP_TOP_ANA_CL32_MBIST_DONE_ANA_CL32_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_ANA_CL32_MBIST_DONE_ANA_CL32_MBIST_DONE  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_ANA_CL32_MBIST_DONE_ANA_CL32_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief ANA_AC memory bist pass status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:ANA_AC_MBIST_PASS
 */
#define VTSS_CHIP_TOP_ANA_AC_MBIST_PASS      VTSS_IOREG(VTSS_TO_CHIP_TOP,0xf)

/**
 * \brief
 * The ANA_AC MBIST has passed
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_ANA_AC_MBIST_PASS . ANA_AC_MBIST_PASS
 */
#define  VTSS_F_CHIP_TOP_ANA_AC_MBIST_PASS_ANA_AC_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_ANA_AC_MBIST_PASS_ANA_AC_MBIST_PASS  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_ANA_AC_MBIST_PASS_ANA_AC_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief ANA_AC memory bist done status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:ANA_AC_MBIST_DONE
 */
#define VTSS_CHIP_TOP_ANA_AC_MBIST_DONE      VTSS_IOREG(VTSS_TO_CHIP_TOP,0x10)

/**
 * \brief
 * The ANA_AC MBIST is done
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_ANA_AC_MBIST_DONE . ANA_AC_MBIST_DONE
 */
#define  VTSS_F_CHIP_TOP_ANA_AC_MBIST_DONE_ANA_AC_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_ANA_AC_MBIST_DONE_ANA_AC_MBIST_DONE  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_ANA_AC_MBIST_DONE_ANA_AC_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief DEVCPU memory bist pass status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:DEVCPU_MBIST_PASS
 */
#define VTSS_CHIP_TOP_DEVCPU_MBIST_PASS      VTSS_IOREG(VTSS_TO_CHIP_TOP,0x11)

/**
 * \brief
 * The DEVCPU MBIST has passed
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_DEVCPU_MBIST_PASS . DEVCPU_MBIST_PASS
 */
#define  VTSS_F_CHIP_TOP_DEVCPU_MBIST_PASS_DEVCPU_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_CHIP_TOP_DEVCPU_MBIST_PASS_DEVCPU_MBIST_PASS     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_CHIP_TOP_DEVCPU_MBIST_PASS_DEVCPU_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief DEVCPU memory bist done status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:DEVCPU_MBIST_DONE
 */
#define VTSS_CHIP_TOP_DEVCPU_MBIST_DONE      VTSS_IOREG(VTSS_TO_CHIP_TOP,0x12)

/**
 * \brief
 * The DEVCPU MBIST is done
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_DEVCPU_MBIST_DONE . DEVCPU_MBIST_DONE
 */
#define  VTSS_F_CHIP_TOP_DEVCPU_MBIST_DONE_DEVCPU_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_CHIP_TOP_DEVCPU_MBIST_DONE_DEVCPU_MBIST_DONE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_CHIP_TOP_DEVCPU_MBIST_DONE_DEVCPU_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief DDR memory bist pass status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:DDR_MBIST_PASS
 */
#define VTSS_CHIP_TOP_DDR_MBIST_PASS         VTSS_IOREG(VTSS_TO_CHIP_TOP,0x13)

/**
 * \brief
 * The DDR MBIST has passed
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_DDR_MBIST_PASS . DDR_MBIST_PASS
 */
#define  VTSS_F_CHIP_TOP_DDR_MBIST_PASS_DDR_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_DDR_MBIST_PASS_DDR_MBIST_PASS  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_DDR_MBIST_PASS_DDR_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief DDR memory bist done status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:DDR_MBIST_DONE
 */
#define VTSS_CHIP_TOP_DDR_MBIST_DONE         VTSS_IOREG(VTSS_TO_CHIP_TOP,0x14)

/**
 * \brief
 * The DDR MBIST is done
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_DDR_MBIST_DONE . DDR_MBIST_DONE
 */
#define  VTSS_F_CHIP_TOP_DDR_MBIST_DONE_DDR_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_DDR_MBIST_DONE_DDR_MBIST_DONE  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_DDR_MBIST_DONE_DDR_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief PROC memory bist pass status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:PROC_MBIST_PASS
 */
#define VTSS_CHIP_TOP_PROC_MBIST_PASS        VTSS_IOREG(VTSS_TO_CHIP_TOP,0x15)

/**
 * \brief
 * The PROC MBIST has passed
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_PROC_MBIST_PASS . PROC_MBIST_PASS
 */
#define  VTSS_F_CHIP_TOP_PROC_MBIST_PASS_PROC_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_PROC_MBIST_PASS_PROC_MBIST_PASS  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_PROC_MBIST_PASS_PROC_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief PROC memory bist done status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:PROC_MBIST_DONE
 */
#define VTSS_CHIP_TOP_PROC_MBIST_DONE        VTSS_IOREG(VTSS_TO_CHIP_TOP,0x16)

/**
 * \brief
 * The PROC MBIST is done
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_PROC_MBIST_DONE . PROC_MBIST_DONE
 */
#define  VTSS_F_CHIP_TOP_PROC_MBIST_DONE_PROC_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_PROC_MBIST_DONE_PROC_MBIST_DONE  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_PROC_MBIST_DONE_PROC_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a CHIP_TOP:HW_STAT
 *
 * Not documented
 */


/**
 * \brief Status of strapped PADs.
 *
 * \details
 * Register: \a CHIP_TOP:HW_STAT:HW_STAT
 */
#define VTSS_CHIP_TOP_HW_STAT                VTSS_IOREG(VTSS_TO_CHIP_TOP,0x17)

/**
 * \brief
 * Value on PAD JTAG_SEL.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_HW_STAT . JTAG_SEL
 */
#define  VTSS_F_CHIP_TOP_HW_STAT_JTAG_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CHIP_TOP_HW_STAT_JTAG_SEL     VTSS_BIT(2)
#define  VTSS_X_CHIP_TOP_HW_STAT_JTAG_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Latched value on PAD REFCLK_SEL.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_HW_STAT . REFCLK_SEL
 */
#define  VTSS_F_CHIP_TOP_HW_STAT_REFCLK_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CHIP_TOP_HW_STAT_REFCLK_SEL   VTSS_BIT(1)
#define  VTSS_X_CHIP_TOP_HW_STAT_REFCLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Latched value on PAD PLL_NBYPASS.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_HW_STAT . PLL_NBYPASS
 */
#define  VTSS_F_CHIP_TOP_HW_STAT_PLL_NBYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_HW_STAT_PLL_NBYPASS  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_HW_STAT_PLL_NBYPASS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a CHIP_TOP:OTP_MEM
 *
 * OTP memory
 */


/**
 * \brief Configuration of OTP memory
 *
 * \details
 * Register: \a CHIP_TOP:OTP_MEM:OTP_CFG
 */
#define VTSS_CHIP_TOP_OTP_CFG                VTSS_IOREG(VTSS_TO_CHIP_TOP,0x18)

/**
 * \brief
 * The core frequency divided by OTP_DIV must be 164MHz +/- 8%
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_OTP_CFG . OTP_DIV
 */
#define  VTSS_F_CHIP_TOP_OTP_CFG_OTP_DIV(x)   VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_CHIP_TOP_OTP_CFG_OTP_DIV      VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_CHIP_TOP_OTP_CFG_OTP_DIV(x)   VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief TCAM recovery information
 *
 * \details
 * Register: \a CHIP_TOP:OTP_MEM:OTP_RCR
 *
 * @param ri Register: OTP_RCR (??), 0-2
 */
#define VTSS_CHIP_TOP_OTP_RCR(ri)            VTSS_IOREG(VTSS_TO_CHIP_TOP,0x19 + (ri))

/**
 * \details
 *
 *	     TCAM repair information is divided in groups of 16-bits (2
 * groups per 32-bit register)
 *		 0..5: column
 *		    6: 0:core_a 1:core_b
 *		7..12: tcam index
 *	       13..14: 0:super 1:es0 2:es2 3:ip6pfx
 *		   15: 0:invalid group 1:valid group

 *
 * Field: ::VTSS_CHIP_TOP_OTP_RCR . OTP_RCR
 */
#define  VTSS_F_CHIP_TOP_OTP_RCR_OTP_RCR(x)   (x)
#define  VTSS_M_CHIP_TOP_OTP_RCR_OTP_RCR      0xffffffff
#define  VTSS_X_CHIP_TOP_OTP_RCR_OTP_RCR(x)   (x)


/**
 * \brief miscellaneous memory
 *
 * \details
 * Register: \a CHIP_TOP:OTP_MEM:OTP_MSC
 *
 * @param ri Register: OTP_MSC (??), 0-3
 */
#define VTSS_CHIP_TOP_OTP_MSC(ri)            VTSS_IOREG(VTSS_TO_CHIP_TOP,0x1c + (ri))

/**
 * \details
 * Field: ::VTSS_CHIP_TOP_OTP_MSC . OTP_MSC
 */
#define  VTSS_F_CHIP_TOP_OTP_MSC_OTP_MSC(x)   (x)
#define  VTSS_M_CHIP_TOP_OTP_MSC_OTP_MSC      0xffffffff
#define  VTSS_X_CHIP_TOP_OTP_MSC_OTP_MSC(x)   (x)


/**
 * \brief Chip Identification
 *
 * \details
 * Register: \a CHIP_TOP:OTP_MEM:OTP_ID
 */
#define VTSS_CHIP_TOP_OTP_ID                 VTSS_IOREG(VTSS_TO_CHIP_TOP,0x20)

/**
 * \details
 * Field: ::VTSS_CHIP_TOP_OTP_ID . OTP_ID
 */
#define  VTSS_F_CHIP_TOP_OTP_ID_OTP_ID(x)     (x)
#define  VTSS_M_CHIP_TOP_OTP_ID_OTP_ID        0xffffffff
#define  VTSS_X_CHIP_TOP_OTP_ID_OTP_ID(x)     (x)


/**
 * \brief OTP product information
 *
 * \details
 * Register: \a CHIP_TOP:OTP_MEM:OTP_PRD
 *
 * @param ri Register: OTP_PRD (??), 0-7
 */
#define VTSS_CHIP_TOP_OTP_PRD(ri)            VTSS_IOREG(VTSS_TO_CHIP_TOP,0x29 + (ri))

/**
 * \details
 * Field: ::VTSS_CHIP_TOP_OTP_PRD . OTP_PRD
 */
#define  VTSS_F_CHIP_TOP_OTP_PRD_OTP_PRD(x)   (x)
#define  VTSS_M_CHIP_TOP_OTP_PRD_OTP_PRD      0xffffffff
#define  VTSS_X_CHIP_TOP_OTP_PRD_OTP_PRD(x)   (x)

/**
 * Register Group: \a CHIP_TOP:CPU_PLL_CFG
 *
 * CPU PLL configuration
 */


/**
 * \brief CPU PLL configuration
 *
 * \details
 * Register: \a CHIP_TOP:CPU_PLL_CFG:CPU_PLL_CFG
 */
#define VTSS_CHIP_TOP_CPU_PLL_CFG            VTSS_IOREG(VTSS_TO_CHIP_TOP,0x31)

/**
 * \brief
 * Acknowledge frequncy change. Wlll toggle high after NEWDIV is set to '1'
 * and toggle low when NEWDIV is set to '0'
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CPU_PLL_CFG . DIVACK
 */
#define  VTSS_F_CHIP_TOP_CPU_PLL_CFG_DIVACK(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_CHIP_TOP_CPU_PLL_CFG_DIVACK   VTSS_BIT(27)
#define  VTSS_X_CHIP_TOP_CPU_PLL_CFG_DIVACK(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Set this bit to allow glitch free change of the PLL output frequency by
 * changing DIVFI and DIVFF. Note that DIVFI and DIVFF must be configured
 * before setting this bit to '1'
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CPU_PLL_CFG . NEWDIV
 */
#define  VTSS_F_CHIP_TOP_CPU_PLL_CFG_NEWDIV(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_CHIP_TOP_CPU_PLL_CFG_NEWDIV   VTSS_BIT(26)
#define  VTSS_X_CHIP_TOP_CPU_PLL_CFG_NEWDIV(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * PLL filter range. Must be 0 to operate the PLL is fractional mode
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CPU_PLL_CFG . FILTER_RANGE
 */
#define  VTSS_F_CHIP_TOP_CPU_PLL_CFG_FILTER_RANGE(x)  VTSS_ENCODE_BITFIELD(x,23,3)
#define  VTSS_M_CHIP_TOP_CPU_PLL_CFG_FILTER_RANGE     VTSS_ENCODE_BITMASK(23,3)
#define  VTSS_X_CHIP_TOP_CPU_PLL_CFG_FILTER_RANGE(x)  VTSS_EXTRACT_BITFIELD(x,23,3)

/**
 * \brief
 * This setting is ignored while CPU_PLL_CFG.ENA_CFG is 0. Output divider
 * value. See ENA_CFG and CPU_PLL_FREQ_CFG for details
 *
 * \details
 * 15-bit output divider control value.
 * The DIVQ_VAL calculated from DIVQ like this:
 * 0-1: Not valid
 * 2-10: All values. DIVQ_VAL = DIVQ
 * 11: Use 10. DIVQ_VAL = 10
 * 12-508: Steps of 4: DIVQ_VAL = 12,16..508
 * 512-1016: Steps of 8: DIVQ_VAL = 512,520..1016
 * 1024-2032: Steps of 16: DIVQ_VAL = 1024,1040..2032
 * 2048-4064: Steps of 32: DIVQ_VAL = 2048,2080..4064
 * 4096-8128: Steps of 64
 * 8192-16256: Steps of 128
 * 16384-32512: Steps of 256
 *
 * Field: ::VTSS_CHIP_TOP_CPU_PLL_CFG . DIVQ
 */
#define  VTSS_F_CHIP_TOP_CPU_PLL_CFG_DIVQ(x)  VTSS_ENCODE_BITFIELD(x,8,15)
#define  VTSS_M_CHIP_TOP_CPU_PLL_CFG_DIVQ     VTSS_ENCODE_BITMASK(8,15)
#define  VTSS_X_CHIP_TOP_CPU_PLL_CFG_DIVQ(x)  VTSS_EXTRACT_BITFIELD(x,8,15)

/**
 * \brief
 * This setting is ignored while CPU_PLL_CFG.ENA_CFG is 0. Reference
 * divider value. See ENA_CFG and CPU_PLL_FREQ_CFG for detailsBefore
 * ENA_CFG is set to '1' this must be set to:6 when the reference clock is
 * 39.0625Mhz 3 when the reference clock is 25.00Mhz
 *
 * \details
 * N: Divide Fin by N+1
 *
 * Field: ::VTSS_CHIP_TOP_CPU_PLL_CFG . DIVR
 */
#define  VTSS_F_CHIP_TOP_CPU_PLL_CFG_DIVR(x)  VTSS_ENCODE_BITFIELD(x,2,6)
#define  VTSS_M_CHIP_TOP_CPU_PLL_CFG_DIVR     VTSS_ENCODE_BITMASK(2,6)
#define  VTSS_X_CHIP_TOP_CPU_PLL_CFG_DIVR(x)  VTSS_EXTRACT_BITFIELD(x,2,6)

/**
 * \brief
 * Allow modification of PLL configuration. All register based PLL settings
 * including default values are ignored while this bit is 0Frequency change
 * procedure.DIVFI and DIVFF can be changed glitch free:Set DIVR to 6 or 3
 * depending on reference clockKeep DIVQ default valueSet DIVFI and DIVFF
 * to desired values, Set ENA_CFG = 1, Set NEWDIV = '1', Read DIVACK.
 * Expect 1, Set NEWDIV = '0'Fvco must be between 2000MHz and
 * 4000MHzAlternatively the CPU_PLL can be fully reconfigured using the
 * SPARE_PLL:Configure the SPARE_PLL to generate the current CPU_PLL
 * frequencySwitch CPU clock to SPARE_PLL. See SPARE_PLL_CFG.ASSIGN_TO_CPU.
 * Set BYPASS_ENA = 1Configre DIVQ, DIVR, DIVFI and DIVFF to desired
 * valuesSet ENA_CFG = 1Set BYPASS_ENA = 0Switch CPU clock back to the
 * reconfigured CPU_PLL. See SPARE_PLL_CFG.ASSIGN_TO_CPU.
 *
 * \details
 * 0: Use fixed configuration
 * 1: Allow modification of PLL settings
 *
 * Field: ::VTSS_CHIP_TOP_CPU_PLL_CFG . ENA_CFG
 */
#define  VTSS_F_CHIP_TOP_CPU_PLL_CFG_ENA_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CHIP_TOP_CPU_PLL_CFG_ENA_CFG  VTSS_BIT(1)
#define  VTSS_X_CHIP_TOP_CPU_PLL_CFG_ENA_CFG(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Read lock status signal from PLL
 *
 * \details
 * 0: PLL is not locked to reference clock
 * 1: PLL is locked
 *
 * Field: ::VTSS_CHIP_TOP_CPU_PLL_CFG . LOCK_STAT
 */
#define  VTSS_F_CHIP_TOP_CPU_PLL_CFG_LOCK_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_CPU_PLL_CFG_LOCK_STAT  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_CPU_PLL_CFG_LOCK_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief CPU PLL configuration
 *
 * \details
 * Settings in this register are ignored while CPU_PLL_CFG.ENA_CFG is 0.
 *
 * Fin: Reference clock frequency 25MHz or 39.0625MHz
 *
 * The PLL VCO frequency is calculated as
 * Fvco = Fin / DIVR_VAL * 8 * DIVF_VAL, where:
 * DIVR_VAL = DIVR+1
 * DIVF_VAL = 1 + DIVFI + (DIVFF / 2^24)
 * Fvco must be between 2000MHz and 4000MHz
 * Fin / DIVR_VAL must be between 5.0MHz and 7.5MHz
 *
 * The PLL output frequency is calculated as:
 * Fout = Fvco / DIVQ_VAL, where
 * DIVQ_VAL = Encoding of DIVQ. See DIVQ description
 *
 * Complete equation:
 * Fout = (Fin / (DIVR+1)) * 8 * (1+DIVFI + (DIVFF / 2^24)) / DIVQ_VAL

 *
 * Register: \a CHIP_TOP:CPU_PLL_CFG:CPU_PLL_FREQ_CFG
 */
#define VTSS_CHIP_TOP_CPU_PLL_FREQ_CFG       VTSS_IOREG(VTSS_TO_CHIP_TOP,0x32)

/**
 * \brief
 * This setting is ignored while CPU_PLL_CFG.ENA_CFG is 0. Bypass PLL and
 * output the reference clock directly. Setting this bit to '1' will also
 * cause the PLL to reconfigure. The DIVFI, DIVFF, DIVQ and DIVR values can
 * be changed while the PLL is bypassed.Setting BYPASS_ENA is not glitch
 * free and the PLL output clock should not be used while BYPASS_ENA = 1.
 *
 * \details
 * 0: Normal oeration. Track reference clock
 * 1: Bypass PLL. Output reference clock directly

 *
 * Field: ::VTSS_CHIP_TOP_CPU_PLL_FREQ_CFG . BYPASS_ENA
 */
#define  VTSS_F_CHIP_TOP_CPU_PLL_FREQ_CFG_BYPASS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_CHIP_TOP_CPU_PLL_FREQ_CFG_BYPASS_ENA  VTSS_BIT(31)
#define  VTSS_X_CHIP_TOP_CPU_PLL_FREQ_CFG_BYPASS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * This setting is ignored while CPU_PLL_CFG.ENA_CFG is 0. Feedback divider
 * integer value. The NEWDIV bit must be '0' when changing this register
 *
 * \details
 * N: Divide by N+1
 *
 * Field: ::VTSS_CHIP_TOP_CPU_PLL_FREQ_CFG . DIVFI
 */
#define  VTSS_F_CHIP_TOP_CPU_PLL_FREQ_CFG_DIVFI(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_CHIP_TOP_CPU_PLL_FREQ_CFG_DIVFI     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_CHIP_TOP_CPU_PLL_FREQ_CFG_DIVFI(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * This setting is ignored while CPU_PLL_CFG.ENA_CFG is 0. Feedback divider
 * fractional value. The NEWDIV bit must be '0' when changing this register
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CPU_PLL_FREQ_CFG . DIVFF
 */
#define  VTSS_F_CHIP_TOP_CPU_PLL_FREQ_CFG_DIVFF(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_CHIP_TOP_CPU_PLL_FREQ_CFG_DIVFF     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_CHIP_TOP_CPU_PLL_FREQ_CFG_DIVFF(x)  VTSS_EXTRACT_BITFIELD(x,0,24)

/**
 * Register Group: \a CHIP_TOP:DDR_PLL_CFG
 *
 * DDR PLL configuration
 */


/**
 * \brief DDR PLL configuration
 *
 * \details
 * Register: \a CHIP_TOP:DDR_PLL_CFG:DDR_PLL_CFG
 */
#define VTSS_CHIP_TOP_DDR_PLL_CFG            VTSS_IOREG(VTSS_TO_CHIP_TOP,0x33)

/**
 * \brief
 * Acknowledge frequncy change. Wlll toggle high after NEWDIV is set to '1'
 * and toggle low when NEWDIV is set to '0'
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_DDR_PLL_CFG . DIVACK
 */
#define  VTSS_F_CHIP_TOP_DDR_PLL_CFG_DIVACK(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_CHIP_TOP_DDR_PLL_CFG_DIVACK   VTSS_BIT(27)
#define  VTSS_X_CHIP_TOP_DDR_PLL_CFG_DIVACK(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Set this bit to allow glitch free change of the PLL output frequency by
 * changing DIVFI and DIVFF. Note that DIVFI and DIVFF must be configured
 * before setting this bit to '1'
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_DDR_PLL_CFG . NEWDIV
 */
#define  VTSS_F_CHIP_TOP_DDR_PLL_CFG_NEWDIV(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_CHIP_TOP_DDR_PLL_CFG_NEWDIV   VTSS_BIT(26)
#define  VTSS_X_CHIP_TOP_DDR_PLL_CFG_NEWDIV(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * PLL filter range. Must be 0 to operate the PLL is fractional mode
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_DDR_PLL_CFG . FILTER_RANGE
 */
#define  VTSS_F_CHIP_TOP_DDR_PLL_CFG_FILTER_RANGE(x)  VTSS_ENCODE_BITFIELD(x,23,3)
#define  VTSS_M_CHIP_TOP_DDR_PLL_CFG_FILTER_RANGE     VTSS_ENCODE_BITMASK(23,3)
#define  VTSS_X_CHIP_TOP_DDR_PLL_CFG_FILTER_RANGE(x)  VTSS_EXTRACT_BITFIELD(x,23,3)

/**
 * \brief
 * This setting is ignored while DDR_PLL_CFG.ENA_CFG is 0. Output divider
 * value. See DDR_PLL_FREQ_CFG for details
 *
 * \details
 * See CHIP_TOP:CPU_PLL_CFG:CPU_PLL_CFG.DIVQ
 *
 * Field: ::VTSS_CHIP_TOP_DDR_PLL_CFG . DIVQ
 */
#define  VTSS_F_CHIP_TOP_DDR_PLL_CFG_DIVQ(x)  VTSS_ENCODE_BITFIELD(x,8,15)
#define  VTSS_M_CHIP_TOP_DDR_PLL_CFG_DIVQ     VTSS_ENCODE_BITMASK(8,15)
#define  VTSS_X_CHIP_TOP_DDR_PLL_CFG_DIVQ(x)  VTSS_EXTRACT_BITFIELD(x,8,15)

/**
 * \brief
 * This setting is ignored while DDR_PLL_CFG.ENA_CFG is 0. Reference
 * divider value. See DDR_PLL_FREQ_CFG for detailsBefore ENA_CFG is set to
 * '1' this must be set to:6 when the reference clock is 39.0625Mhz 3 when
 * the reference clock is 25.00Mhz
 *
 * \details
 * N: Divide Fin by N+1
 *
 * Field: ::VTSS_CHIP_TOP_DDR_PLL_CFG . DIVR
 */
#define  VTSS_F_CHIP_TOP_DDR_PLL_CFG_DIVR(x)  VTSS_ENCODE_BITFIELD(x,2,6)
#define  VTSS_M_CHIP_TOP_DDR_PLL_CFG_DIVR     VTSS_ENCODE_BITMASK(2,6)
#define  VTSS_X_CHIP_TOP_DDR_PLL_CFG_DIVR(x)  VTSS_EXTRACT_BITFIELD(x,2,6)

/**
 * \brief
 * Allow modification of PLL configuration. All register based PLL settings
 * are ignored while this bit is 0Frequency change procedure.DIVFI and
 * DIVFF can be changed glitch free:Set DIVR to 6 or 3 depending on
 * reference clockKeep DIVQ default valueSet DIVFI and DIVFF to desired
 * values, Set ENA_CFG = 1, Set NEWDIV = '1', Read DIVACK. Expect 1, Set
 * NEWDIV = '0'Fvco must be between 2000MHz and 4000MHzIt is also possible
 * to do a full reconfiguration of the PLL using the BYPASS_ENA setting,
 * but this will not be glitch free
 *
 * \details
 * 0: Use fixed configuration
 * 1: Allow modification of PLL settings
 *
 * Field: ::VTSS_CHIP_TOP_DDR_PLL_CFG . ENA_CFG
 */
#define  VTSS_F_CHIP_TOP_DDR_PLL_CFG_ENA_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CHIP_TOP_DDR_PLL_CFG_ENA_CFG  VTSS_BIT(1)
#define  VTSS_X_CHIP_TOP_DDR_PLL_CFG_ENA_CFG(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Read lock status signal from PLL
 *
 * \details
 * 0: PLL is not locked to reference clock
 * 1: PLL is locked
 *
 * Field: ::VTSS_CHIP_TOP_DDR_PLL_CFG . LOCK_STAT
 */
#define  VTSS_F_CHIP_TOP_DDR_PLL_CFG_LOCK_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_DDR_PLL_CFG_LOCK_STAT  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_DDR_PLL_CFG_LOCK_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief CPU PLL configuration
 *
 * \details
 * Settings in this register are ignored while DDR_PLL_CFG.ENA_CFG is 0.
 *
 * Fin: Reference clock frequency 25MHz or 39.0625MHz
 *
 * The PLL VCO frequency is calculated as
 * Fvco = Fin / DIVR_VAL * 8 * DIVF_VAL, where:
 * DIVR_VAL = DIVR+1
 * DIVF_VAL = 1 + DIVFI + (DIVFF / 2^24)
 * Fvco must be between 2000MHz and 4000MHz
 * Fin / DIVR_VAL must be between 5.0MHz and 7.5MHz
 *
 * The PLL output frequency is calculated as:
 * Fout = Fvco / DIVQ_VAL, where
 * DIVQ_VAL = Encoding of DIVQ. See DIVQ description
 *
 * Complete equation:
 * Fout = (Fin / (DIVR+1)) * 8 * (1+DIVFI + (DIVFF / 2^24)) / DIVQ_VAL

 *
 * Register: \a CHIP_TOP:DDR_PLL_CFG:DDR_PLL_FREQ_CFG
 */
#define VTSS_CHIP_TOP_DDR_PLL_FREQ_CFG       VTSS_IOREG(VTSS_TO_CHIP_TOP,0x34)

/**
 * \brief
 * This setting is ignored while DDR_PLL_CFG.ENA_CFG is 0. Bypass PLL and
 * output the reference clock directly.  Setting this bit to '1' will also
 * cause the PLL to reconfigure. The DIVFI, DIVFF, DIVQ and DIVR values can
 * be changed while the PLL is bypassed.Setting BYPASS_ENA is not glitch
 * free and the PLL output clock should not be used while BYPASS_ENA = 1.
 *
 * \details
 * 0: Normal oeration. Track reference clock
 * 1: Bypass PLL. Output reference clock directly

 *
 * Field: ::VTSS_CHIP_TOP_DDR_PLL_FREQ_CFG . BYPASS_ENA
 */
#define  VTSS_F_CHIP_TOP_DDR_PLL_FREQ_CFG_BYPASS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_CHIP_TOP_DDR_PLL_FREQ_CFG_BYPASS_ENA  VTSS_BIT(31)
#define  VTSS_X_CHIP_TOP_DDR_PLL_FREQ_CFG_BYPASS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * This setting is ignored while DDR_PLL_CFG.ENA_CFG is 0. Feedback divider
 * integer value. The NEWDIV bit must be '0' when changing this register
 *
 * \details
 * N: Divide by N+1
 *
 * Field: ::VTSS_CHIP_TOP_DDR_PLL_FREQ_CFG . DIVFI
 */
#define  VTSS_F_CHIP_TOP_DDR_PLL_FREQ_CFG_DIVFI(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_CHIP_TOP_DDR_PLL_FREQ_CFG_DIVFI     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_CHIP_TOP_DDR_PLL_FREQ_CFG_DIVFI(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * This setting is ignored while DDR_PLL_CFG.ENA_CFG is 0. Feedback divider
 * fractional value. The NEWDIV bit must be '0' when changing this register
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_DDR_PLL_FREQ_CFG . DIVFF
 */
#define  VTSS_F_CHIP_TOP_DDR_PLL_FREQ_CFG_DIVFF(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_CHIP_TOP_DDR_PLL_FREQ_CFG_DIVFF     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_CHIP_TOP_DDR_PLL_FREQ_CFG_DIVFF(x)  VTSS_EXTRACT_BITFIELD(x,0,24)

/**
 * Register Group: \a CHIP_TOP:CORE_PLL_CFG
 *
 * CORE PLL configuration
 */


/**
 * \brief CORE PLL configuration
 *
 * \details
 * Register: \a CHIP_TOP:CORE_PLL_CFG:CORE_PLL_CFG
 */
#define VTSS_CHIP_TOP_CORE_PLL_CFG           VTSS_IOREG(VTSS_TO_CHIP_TOP,0x35)

/**
 * \brief
 * Allow configuration based selection of the reference clock. This setting
 * is ignored while ENA_CFG is 0.The CORE_PLL must be fully reconfigured if
 * the refrence clock is changed. See ENA_CFG
 *
 * \details
 * 0: Use strapping pin
 * 1: Force 39.0625MHz reference clock
 * 2: Force 25Mhz reference clock
 * 3: Reserved
 *
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_CFG . REF_CLK_SEL
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_CFG_REF_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_CHIP_TOP_CORE_PLL_CFG_REF_CLK_SEL     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_CHIP_TOP_CORE_PLL_CFG_REF_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * Acknowledge frequncy change. Wlll toggle high after NEWDIV is set to '1'
 * and toggle low when NEWDIV is set to '0'
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_CFG . DIVACK
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_CFG_DIVACK(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_CHIP_TOP_CORE_PLL_CFG_DIVACK  VTSS_BIT(27)
#define  VTSS_X_CHIP_TOP_CORE_PLL_CFG_DIVACK(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Set this bit to allow glitch free change of the PLL output frequency by
 * changing DIVFI and DIVFF. Note that DIVFI and DIVFF must be configured
 * before setting this bit to '1'
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_CFG . NEWDIV
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_CFG_NEWDIV(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_CHIP_TOP_CORE_PLL_CFG_NEWDIV  VTSS_BIT(26)
#define  VTSS_X_CHIP_TOP_CORE_PLL_CFG_NEWDIV(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * PLL filter range. Must be 0 to operate the PLL is fractional mode
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_CFG . FILTER_RANGE
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_CFG_FILTER_RANGE(x)  VTSS_ENCODE_BITFIELD(x,23,3)
#define  VTSS_M_CHIP_TOP_CORE_PLL_CFG_FILTER_RANGE     VTSS_ENCODE_BITMASK(23,3)
#define  VTSS_X_CHIP_TOP_CORE_PLL_CFG_FILTER_RANGE(x)  VTSS_EXTRACT_BITFIELD(x,23,3)

/**
 * \brief
 * This setting is ignored while CORE_PLL_CFG.ENA_CFG is 0. Output divider
 * value. See CORE_PLL_FREQ_CFG for details
 *
 * \details
 * See CHIP_TOP:CPU_PLL_CFG:CPU_PLL_CFG.DIVQ
 *
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_CFG . DIVQ
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_CFG_DIVQ(x)  VTSS_ENCODE_BITFIELD(x,8,15)
#define  VTSS_M_CHIP_TOP_CORE_PLL_CFG_DIVQ     VTSS_ENCODE_BITMASK(8,15)
#define  VTSS_X_CHIP_TOP_CORE_PLL_CFG_DIVQ(x)  VTSS_EXTRACT_BITFIELD(x,8,15)

/**
 * \brief
 * This setting is ignored while CORE_PLL_CFG.ENA_CFG is 0. Reference
 * divider value. See CORE_PLL_FREQ_CFG for detailsBefore ENA_CFG is set to
 * '1' this must be set to:6 when the reference clock is 39.0625Mhz 3 when
 * the reference clock is 25.00Mhz
 *
 * \details
 * N: Divide Fin by N+1
 *
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_CFG . DIVR
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_CFG_DIVR(x)  VTSS_ENCODE_BITFIELD(x,2,6)
#define  VTSS_M_CHIP_TOP_CORE_PLL_CFG_DIVR     VTSS_ENCODE_BITMASK(2,6)
#define  VTSS_X_CHIP_TOP_CORE_PLL_CFG_DIVR(x)  VTSS_EXTRACT_BITFIELD(x,2,6)

/**
 * \brief
 * Allow modification of PLL configuration. All register based PLL settings
 * are ignored while this bit is 0Frequency change procedure.DIVFI and
 * DIVFF can be changed glitch free:Set DIVR to 6 or 3 depending on
 * reference clockKeep DIVQ default valueSet DIVFI and DIVFF to desired
 * values, Set ENA_CFG = 1, Set NEWDIV = '1', Read DIVACK. Expect 1, Set
 * NEWDIV = '0'Fvco must be between 2000MHz and 4000MHzAlternatively the
 * CORE_PLL can be fully reconfigured using the SPARE_PLL:Configure the
 * SPARE_PLL to generate the current CORE_PLL frequencySwitch CORE clock to
 * SPARE_PLL. See SPARE_PLL_CFG.ASSIGN_TO_CORE. Set BYPASS_ENA = 1Configre
 * DIVQ, DIVR, DIVFI and DIVFF to desired valuesSet ENA_CFG = 1Set
 * BYPASS_ENA = 0Switch CORE clock back to the reconfigured CORE_PLL. See
 * SPARE_PLL_CFG.ASSIGN_TO_CORE.
 *
 * \details
 * 0: Use fixed configuration
 * 1: Allow modification of PLL settings

 *
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_CFG . ENA_CFG
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_CFG_ENA_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CHIP_TOP_CORE_PLL_CFG_ENA_CFG  VTSS_BIT(1)
#define  VTSS_X_CHIP_TOP_CORE_PLL_CFG_ENA_CFG(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Read lock status signal from PLL
 *
 * \details
 * 0: PLL is not locked to reference clock
 * 1: PLL is locked
 *
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_CFG . LOCK_STAT
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_CFG_LOCK_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_CORE_PLL_CFG_LOCK_STAT  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_CORE_PLL_CFG_LOCK_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief CPU PLL configuration
 *
 * \details
 * Settings in this register are ignored while CORE_PLL_CFG.ENA_CFG is 0.
 *
 * Fin: Reference clock frequency 25MHz or 39.0625MHz
 *
 * The PLL VCO frequency is calculated as
 * Fvco = Fin / DIVR_VAL * 8 * DIVF_VAL, where:
 * DIVR_VAL = DIVR+1
 * DIVF_VAL = 1 + DIVFI + (DIVFF / 2^24)
 * Fvco must be between 2000MHz and 4000MHz
 * Fin / DIVR_VAL must be between 5.0MHz and 7.5MHz
 *
 * The PLL output frequency is calculated as:
 * Fout = Fvco / DIVQ_VAL, where
 * DIVQ_VAL = Encoding of DIVQ. See DIVQ description
 *
 * Complete equation:
 * Fout = (Fin / (DIVR+1)) * 8 * (1+DIVFI + (DIVFF / 2^24)) / DIVQ_VAL

 *
 * Register: \a CHIP_TOP:CORE_PLL_CFG:CORE_PLL_FREQ_CFG
 */
#define VTSS_CHIP_TOP_CORE_PLL_FREQ_CFG      VTSS_IOREG(VTSS_TO_CHIP_TOP,0x36)

/**
 * \brief
 * This setting is ignored while CORE_PLL_CFG.ENA_CFG is 0. Bypass PLL and
 * output the reference clock directly.  Setting this bit to '1' will also
 * cause the PLL to reconfigure. The DIVFI, DIVFF, DIVQ and DIVR values can
 * be changed while the PLL is bypassed.Setting BYPASS_ENA is not glitch
 * free and the PLL output clock should not be used while BYPASS_ENA = 1.
 *
 * \details
 * 0: Normal oeration. Track reference clock
 * 1: Bypass PLL. Output reference clock directly

 *
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_FREQ_CFG . BYPASS_ENA
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_FREQ_CFG_BYPASS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_CHIP_TOP_CORE_PLL_FREQ_CFG_BYPASS_ENA  VTSS_BIT(31)
#define  VTSS_X_CHIP_TOP_CORE_PLL_FREQ_CFG_BYPASS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * This setting is ignored while CORE_PLL_CFG.ENA_CFG is 0. Feedback
 * divider integer value. The NEWDIV bit must be '0' when changing this
 * register
 *
 * \details
 * N: Divide by N+1
 *
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_FREQ_CFG . DIVFI
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_FREQ_CFG_DIVFI(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_CHIP_TOP_CORE_PLL_FREQ_CFG_DIVFI     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_CHIP_TOP_CORE_PLL_FREQ_CFG_DIVFI(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * This setting is ignored while CORE_PLL_CFG.ENA_CFG is 0. Feedback
 * divider fractional value. The NEWDIV bit must be '0' when changing this
 * register
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_FREQ_CFG . DIVFF
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_FREQ_CFG_DIVFF(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_CHIP_TOP_CORE_PLL_FREQ_CFG_DIVFF     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_CHIP_TOP_CORE_PLL_FREQ_CFG_DIVFF(x)  VTSS_EXTRACT_BITFIELD(x,0,24)

/**
 * Register Group: \a CHIP_TOP:RGMII_PLL_CFG
 *
 * RGMII PLL configuration
 */


/**
 * \brief RGMII PLL configuration
 *
 * \details
 * Register: \a CHIP_TOP:RGMII_PLL_CFG:RGMII_PLL_CFG
 */
#define VTSS_CHIP_TOP_RGMII_PLL_CFG          VTSS_IOREG(VTSS_TO_CHIP_TOP,0x37)

/**
 * \brief
 * Acknowledge frequncy change. Wlll toggle high after NEWDIV is set to '1'
 * and toggle low when NEWDIV is set to '0'
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_RGMII_PLL_CFG . DIVACK
 */
#define  VTSS_F_CHIP_TOP_RGMII_PLL_CFG_DIVACK(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_CHIP_TOP_RGMII_PLL_CFG_DIVACK  VTSS_BIT(27)
#define  VTSS_X_CHIP_TOP_RGMII_PLL_CFG_DIVACK(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Set this bit to allow glitch free change of the PLL output frequency by
 * changing DIVFI and DIVFF. Note that DIVFI and DIVFF must be configured
 * before setting this bit to '1'
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_RGMII_PLL_CFG . NEWDIV
 */
#define  VTSS_F_CHIP_TOP_RGMII_PLL_CFG_NEWDIV(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_CHIP_TOP_RGMII_PLL_CFG_NEWDIV  VTSS_BIT(26)
#define  VTSS_X_CHIP_TOP_RGMII_PLL_CFG_NEWDIV(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * PLL filter range. Must be 0 to operate the PLL is fractional mode
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_RGMII_PLL_CFG . FILTER_RANGE
 */
#define  VTSS_F_CHIP_TOP_RGMII_PLL_CFG_FILTER_RANGE(x)  VTSS_ENCODE_BITFIELD(x,23,3)
#define  VTSS_M_CHIP_TOP_RGMII_PLL_CFG_FILTER_RANGE     VTSS_ENCODE_BITMASK(23,3)
#define  VTSS_X_CHIP_TOP_RGMII_PLL_CFG_FILTER_RANGE(x)  VTSS_EXTRACT_BITFIELD(x,23,3)

/**
 * \brief
 * This setting is ignored while RGMII_PLL_CFG.ENA_CFG is 0. Output divider
 * value. See RGMII_PLL_FREQ_CFG for details
 *
 * \details
 * See CHIP_TOP:CPU_PLL_CFG:CPU_PLL_CFG.DIVQ
 *
 * Field: ::VTSS_CHIP_TOP_RGMII_PLL_CFG . DIVQ
 */
#define  VTSS_F_CHIP_TOP_RGMII_PLL_CFG_DIVQ(x)  VTSS_ENCODE_BITFIELD(x,8,15)
#define  VTSS_M_CHIP_TOP_RGMII_PLL_CFG_DIVQ     VTSS_ENCODE_BITMASK(8,15)
#define  VTSS_X_CHIP_TOP_RGMII_PLL_CFG_DIVQ(x)  VTSS_EXTRACT_BITFIELD(x,8,15)

/**
 * \brief
 * This setting is ignored while RGMII_PLL_CFG.ENA_CFG is 0. Reference
 * divider value. See RGMII_PLL_FREQ_CFG for detailsBefore ENA_CFG is '1'
 * this must be set to:6 when the reference clock is 39.0625Mhz 3 when the
 * reference clock is 25.00Mhz
 *
 * \details
 * N: Divide Fin by N+1
 *
 * Field: ::VTSS_CHIP_TOP_RGMII_PLL_CFG . DIVR
 */
#define  VTSS_F_CHIP_TOP_RGMII_PLL_CFG_DIVR(x)  VTSS_ENCODE_BITFIELD(x,2,6)
#define  VTSS_M_CHIP_TOP_RGMII_PLL_CFG_DIVR     VTSS_ENCODE_BITMASK(2,6)
#define  VTSS_X_CHIP_TOP_RGMII_PLL_CFG_DIVR(x)  VTSS_EXTRACT_BITFIELD(x,2,6)

/**
 * \brief
 * Allow modification of PLL configuration. All register based PLL settings
 * are ignored while this bit is 0Frequency change procedure.DIVFI and
 * DIVFF can be changed glitch free:Set DIVR to 6 or 3 depending on
 * reference clockKeep DIVQ default valueSet DIVFI and DIVFF to desired
 * values, Set ENA_CFG = 1, Set NEWDIV = '1', Read DIVACK. Expect 1, Set
 * NEWDIV = '0'Fvco must be between 2000MHz and 4000MHzIt is also possible
 * to do a full reconfiguration of the PLL using the BYPASS_ENA setting,
 * but this will not be glitch free
 *
 * \details
 * 0: Use fixed configuration
 * 1: Allow modification of PLL settings

 *
 * Field: ::VTSS_CHIP_TOP_RGMII_PLL_CFG . ENA_CFG
 */
#define  VTSS_F_CHIP_TOP_RGMII_PLL_CFG_ENA_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CHIP_TOP_RGMII_PLL_CFG_ENA_CFG  VTSS_BIT(1)
#define  VTSS_X_CHIP_TOP_RGMII_PLL_CFG_ENA_CFG(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Read lock status signal from PLL
 *
 * \details
 * 0: PLL is not locked to reference clock
 * 1: PLL is locked
 *
 * Field: ::VTSS_CHIP_TOP_RGMII_PLL_CFG . LOCK_STAT
 */
#define  VTSS_F_CHIP_TOP_RGMII_PLL_CFG_LOCK_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_RGMII_PLL_CFG_LOCK_STAT  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_RGMII_PLL_CFG_LOCK_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief CPU PLL configuration
 *
 * \details
 * Settings in this register are ignored while RGMII_PLL_CFG.ENA_CFG is 0.
 *
 * Fin: Reference clock frequency 25MHz or 39.0625MHz
 *
 * The PLL VCO frequency is calculated as
 * Fvco = Fin / DIVR_VAL * 8 * DIVF_VAL, where:
 * DIVR_VAL = DIVR+1
 * DIVF_VAL = 1 + DIVFI + (DIVFF / 2^24)
 * Fvco must be between 2000MHz and 4000MHz
 * Fin / DIVR_VAL must be between 5.0MHz and 7.5MHz
 *
 * The PLL output frequency is calculated as:
 * Fout = Fvco / DIVQ_VAL, where
 * DIVQ_VAL = Encoding of DIVQ. See DIVQ description
 *
 * Complete equation:
 * Fout = (Fin / (DIVR+1)) * 8 * (1+DIVFI + (DIVFF / 2^24)) / DIVQ_VAL

 *
 * Register: \a CHIP_TOP:RGMII_PLL_CFG:RGMII_PLL_FREQ_CFG
 */
#define VTSS_CHIP_TOP_RGMII_PLL_FREQ_CFG     VTSS_IOREG(VTSS_TO_CHIP_TOP,0x38)

/**
 * \brief
 * This setting is ignored while RGMII_PLL_CFG.ENA_CFG is 0. Bypass PLL and
 * output the reference clock directly. Setting this bit to '1' will also
 * cause the PLL to reconfigure. The DIVFI, DIVFF, DIVQ and DIVR values can
 * be changed while the PLL is bypassed.Setting BYPASS_ENA is not glitch
 * free and the PLL output clock should not be used while BYPASS_ENA = 1.
 *
 * \details
 * 0: Normal oeration. Track reference clock
 * 1: Bypass PLL. Output reference clock directly

 *
 * Field: ::VTSS_CHIP_TOP_RGMII_PLL_FREQ_CFG . BYPASS_ENA
 */
#define  VTSS_F_CHIP_TOP_RGMII_PLL_FREQ_CFG_BYPASS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_CHIP_TOP_RGMII_PLL_FREQ_CFG_BYPASS_ENA  VTSS_BIT(31)
#define  VTSS_X_CHIP_TOP_RGMII_PLL_FREQ_CFG_BYPASS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * This setting is ignored while RGMII_PLL_CFG.ENA_CFG is 0. Feedback
 * divider integer value. The NEWDIV bit must be '0' when changing this
 * register
 *
 * \details
 * N: Divide by N+1
 *
 * Field: ::VTSS_CHIP_TOP_RGMII_PLL_FREQ_CFG . DIVFI
 */
#define  VTSS_F_CHIP_TOP_RGMII_PLL_FREQ_CFG_DIVFI(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_CHIP_TOP_RGMII_PLL_FREQ_CFG_DIVFI     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_CHIP_TOP_RGMII_PLL_FREQ_CFG_DIVFI(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * This setting is ignored while RGMII_PLL_CFG.ENA_CFG is 0. Feedback
 * divider fractional value. The NEWDIV bit must be '0' when changing this
 * register
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_RGMII_PLL_FREQ_CFG . DIVFF
 */
#define  VTSS_F_CHIP_TOP_RGMII_PLL_FREQ_CFG_DIVFF(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_CHIP_TOP_RGMII_PLL_FREQ_CFG_DIVFF     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_CHIP_TOP_RGMII_PLL_FREQ_CFG_DIVFF(x)  VTSS_EXTRACT_BITFIELD(x,0,24)

/**
 * Register Group: \a CHIP_TOP:FX100_PLL_CFG
 *
 * FX100 PLL configuration
 */


/**
 * \brief FX100 PLL configuration
 *
 * \details
 * Register: \a CHIP_TOP:FX100_PLL_CFG:FX100_PLL_CFG
 */
#define VTSS_CHIP_TOP_FX100_PLL_CFG          VTSS_IOREG(VTSS_TO_CHIP_TOP,0x39)

/**
 * \brief
 * Acknowledge frequncy change. Wlll toggle high after NEWDIV is set to '1'
 * and toggle low when NEWDIV is set to '0'
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_FX100_PLL_CFG . DIVACK
 */
#define  VTSS_F_CHIP_TOP_FX100_PLL_CFG_DIVACK(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_CHIP_TOP_FX100_PLL_CFG_DIVACK  VTSS_BIT(27)
#define  VTSS_X_CHIP_TOP_FX100_PLL_CFG_DIVACK(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Set this bit to allow glitch free change of the PLL output frequency by
 * changing DIVFI and DIVFF. Note that DIVFI and DIVFF must be configured
 * before setting this bit to '1'
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_FX100_PLL_CFG . NEWDIV
 */
#define  VTSS_F_CHIP_TOP_FX100_PLL_CFG_NEWDIV(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_CHIP_TOP_FX100_PLL_CFG_NEWDIV  VTSS_BIT(26)
#define  VTSS_X_CHIP_TOP_FX100_PLL_CFG_NEWDIV(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * PLL filter range. Must be 0 to operate the PLL is fractional mode
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_FX100_PLL_CFG . FILTER_RANGE
 */
#define  VTSS_F_CHIP_TOP_FX100_PLL_CFG_FILTER_RANGE(x)  VTSS_ENCODE_BITFIELD(x,23,3)
#define  VTSS_M_CHIP_TOP_FX100_PLL_CFG_FILTER_RANGE     VTSS_ENCODE_BITMASK(23,3)
#define  VTSS_X_CHIP_TOP_FX100_PLL_CFG_FILTER_RANGE(x)  VTSS_EXTRACT_BITFIELD(x,23,3)

/**
 * \brief
 * This setting is ignored while FX100_PLL_CFG.ENA_CFG is 0. Output divider
 * value. See FX100_PLL_FREQ_CFG for details
 *
 * \details
 * See CHIP_TOP:CPU_PLL_CFG:CPU_PLL_CFG.DIVQ
 *
 * Field: ::VTSS_CHIP_TOP_FX100_PLL_CFG . DIVQ
 */
#define  VTSS_F_CHIP_TOP_FX100_PLL_CFG_DIVQ(x)  VTSS_ENCODE_BITFIELD(x,8,15)
#define  VTSS_M_CHIP_TOP_FX100_PLL_CFG_DIVQ     VTSS_ENCODE_BITMASK(8,15)
#define  VTSS_X_CHIP_TOP_FX100_PLL_CFG_DIVQ(x)  VTSS_EXTRACT_BITFIELD(x,8,15)

/**
 * \brief
 * This setting is ignored while FX100_PLL_CFG.ENA_CFG is 0. Reference
 * divider value. See FX100_PLL_FREQ_CFG for detailsBefore ENA_CFG is set
 * to '1' this must be set to:6 when the reference clock is 39.0625Mhz 3
 * when the reference clock is 25.00Mhz
 *
 * \details
 * N: Divide Fin by N+1
 *
 * Field: ::VTSS_CHIP_TOP_FX100_PLL_CFG . DIVR
 */
#define  VTSS_F_CHIP_TOP_FX100_PLL_CFG_DIVR(x)  VTSS_ENCODE_BITFIELD(x,2,6)
#define  VTSS_M_CHIP_TOP_FX100_PLL_CFG_DIVR     VTSS_ENCODE_BITMASK(2,6)
#define  VTSS_X_CHIP_TOP_FX100_PLL_CFG_DIVR(x)  VTSS_EXTRACT_BITFIELD(x,2,6)

/**
 * \brief
 * Allow modification of PLL configuration. All register based PLL settings
 * are ignored while this bit is 0Frequency change procedure.DIVFI and
 * DIVFF can be changed glitch free:Set DIVR to 6 or 3 depending on
 * reference clockKeep DIVQ default valueSet DIVFI and DIVFF to desired
 * values, Set ENA_CFG = 1, Set NEWDIV = '1', Read DIVACK. Expect 1, Set
 * NEWDIV = '0'Fvco must be between 2000MHz and 4000MHzIt is also possible
 * to do a full reconfiguration of the PLL using the BYPASS_ENA setting,
 * but this will not be glitch free
 *
 * \details
 * 0: Use fixed configuration
 * 1: Allow modification of PLL settings

 *
 * Field: ::VTSS_CHIP_TOP_FX100_PLL_CFG . ENA_CFG
 */
#define  VTSS_F_CHIP_TOP_FX100_PLL_CFG_ENA_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CHIP_TOP_FX100_PLL_CFG_ENA_CFG  VTSS_BIT(1)
#define  VTSS_X_CHIP_TOP_FX100_PLL_CFG_ENA_CFG(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Read lock status signal from PLL
 *
 * \details
 * 0: PLL is not locked to reference clock
 * 1: PLL is locked
 *
 * Field: ::VTSS_CHIP_TOP_FX100_PLL_CFG . LOCK_STAT
 */
#define  VTSS_F_CHIP_TOP_FX100_PLL_CFG_LOCK_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_FX100_PLL_CFG_LOCK_STAT  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_FX100_PLL_CFG_LOCK_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief CPU PLL configuration
 *
 * \details
 * Settings in this register are ignored while FX100_PLL_CFG.ENA_CFG is 0.
 *
 * Fin: Reference clock frequency 25MHz or 39.0625MHz
 *
 * The PLL VCO frequency is calculated as
 * Fvco = Fin / DIVR_VAL * 8 * DIVF_VAL, where:
 * DIVR_VAL = DIVR+1
 * DIVF_VAL = 1 + DIVFI + (DIVFF / 2^24)
 * Fvco must be between 2000MHz and 4000MHz
 * Fin / DIVR_VAL must be between 5.0MHz and 7.5MHz
 *
 * The PLL output frequency is calculated as:
 * Fout = Fvco / DIVQ_VAL, where
 * DIVQ_VAL = Encoding of DIVQ. See DIVQ description
 *
 * Complete equation:
 * Fout = (Fin / (DIVR+1)) * 8 * (1+DIVFI + (DIVFF / 2^24)) / DIVQ_VAL

 *
 * Register: \a CHIP_TOP:FX100_PLL_CFG:FX100_PLL_FREQ_CFG
 */
#define VTSS_CHIP_TOP_FX100_PLL_FREQ_CFG     VTSS_IOREG(VTSS_TO_CHIP_TOP,0x3a)

/**
 * \brief
 * This setting is ignored while FX100_PLL_CFG.ENA_CFG is 0. Bypass PLL and
 * output the reference clock directly. Setting this bit to '1' will also
 * cause the PLL to reconfigure. The DIVFI, DIVFF, DIVQ and DIVR values can
 * be changed while the PLL is bypassed.Setting BYPASS_ENA is not glitch
 * free and the PLL output clock should not be used while BYPASS_ENA = 1.
 *
 * \details
 * 0: Normal oeration. Track reference clock
 * 1: Bypass PLL. Output reference clock directly

 *
 * Field: ::VTSS_CHIP_TOP_FX100_PLL_FREQ_CFG . BYPASS_ENA
 */
#define  VTSS_F_CHIP_TOP_FX100_PLL_FREQ_CFG_BYPASS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_CHIP_TOP_FX100_PLL_FREQ_CFG_BYPASS_ENA  VTSS_BIT(31)
#define  VTSS_X_CHIP_TOP_FX100_PLL_FREQ_CFG_BYPASS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * This setting is ignored while FX100_PLL_CFG.ENA_CFG is 0. Feedback
 * divider integer value. The NEWDIV bit must be '0' when changing this
 * register
 *
 * \details
 * N: Divide by N+1
 *
 * Field: ::VTSS_CHIP_TOP_FX100_PLL_FREQ_CFG . DIVFI
 */
#define  VTSS_F_CHIP_TOP_FX100_PLL_FREQ_CFG_DIVFI(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_CHIP_TOP_FX100_PLL_FREQ_CFG_DIVFI     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_CHIP_TOP_FX100_PLL_FREQ_CFG_DIVFI(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * This setting is ignored while FX100_PLL_CFG.ENA_CFG is 0. Feedback
 * divider fractional value. The NEWDIV bit must be '0' when changing this
 * register
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_FX100_PLL_FREQ_CFG . DIVFF
 */
#define  VTSS_F_CHIP_TOP_FX100_PLL_FREQ_CFG_DIVFF(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_CHIP_TOP_FX100_PLL_FREQ_CFG_DIVFF     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_CHIP_TOP_FX100_PLL_FREQ_CFG_DIVFF(x)  VTSS_EXTRACT_BITFIELD(x,0,24)

/**
 * Register Group: \a CHIP_TOP:SPARE_PLL_CFG
 *
 * SPARE PLL configuration
 */


/**
 * \brief SPARE PLL configuration
 *
 * \details
 * Register: \a CHIP_TOP:SPARE_PLL_CFG:SPARE_PLL_CFG
 */
#define VTSS_CHIP_TOP_SPARE_PLL_CFG          VTSS_IOREG(VTSS_TO_CHIP_TOP,0x3b)

/**
 * \brief
 * When this bit is set the core clock is generated by the SPARE_PLL. The
 * switch over between the CPU- and spare PLLs is glitch free. The Spare
 * PLL is unused and can be reconfigured while this bit is '0'
 *
 * \details
 * 0: Use CPU_PLL to generate CPU clock
 * 1: Use SPARE_PLL to generate CPU clock
 *
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_CFG . ASSIGN_TO_CPU
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_CFG_ASSIGN_TO_CPU(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_CFG_ASSIGN_TO_CPU  VTSS_BIT(31)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_CFG_ASSIGN_TO_CPU(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * When this bit is set the core clock is generated by the SPARE_PLL. The
 * switch over between the core- and spare PLLs is glitch free. The Spare
 * PLL is unused and can be reconfigured while this bit is '0'
 *
 * \details
 * 0: Use CORE_PLL to generate core clock
 * 1: Use SPARE_PLL to generate core clock
 *
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_CFG . ASSIGN_TO_CORE
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_CFG_ASSIGN_TO_CORE(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_CFG_ASSIGN_TO_CORE  VTSS_BIT(30)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_CFG_ASSIGN_TO_CORE(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Allow configuration based selection of the reference clock. This setting
 * is ignored while ENA_CFG is 0.
 *
 * \details
 * 0: Use strapping pin
 * 1: Force 39.0625MHz reference clock
 * 2: Force 25Mhz reference clock
 * 3: Reserved
 *
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_CFG . REF_CLK_SEL
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_CFG_REF_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_CFG_REF_CLK_SEL     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_CFG_REF_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * Acknowledge frequncy change. Wlll toggle high after NEWDIV is set to '1'
 * and toggle low when NEWDIV is set to '0'
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_CFG . DIVACK
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_CFG_DIVACK(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_CFG_DIVACK  VTSS_BIT(27)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_CFG_DIVACK(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Set this bit to allow glitch free change of the PLL output frequency by
 * changing DIVFI and DIVFF. Note that DIVFI and DIVFF must be configured
 * before setting this bit to '1'
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_CFG . NEWDIV
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_CFG_NEWDIV(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_CFG_NEWDIV  VTSS_BIT(26)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_CFG_NEWDIV(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * PLL filter range. Must be 0 to operate the PLL is fractional mode
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_CFG . FILTER_RANGE
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_CFG_FILTER_RANGE(x)  VTSS_ENCODE_BITFIELD(x,23,3)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_CFG_FILTER_RANGE     VTSS_ENCODE_BITMASK(23,3)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_CFG_FILTER_RANGE(x)  VTSS_EXTRACT_BITFIELD(x,23,3)

/**
 * \brief
 * This setting is ignored while SPARE_PLL_CFG.ENA_CFG is 0.Output divider
 * value. See SPARE_PLL_FREQ_CFG for details
 *
 * \details
 * See CHIP_TOP:CPU_PLL_CFG:CPU_PLL_CFG.DIVQ
 *
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_CFG . DIVQ
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_CFG_DIVQ(x)  VTSS_ENCODE_BITFIELD(x,8,15)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_CFG_DIVQ     VTSS_ENCODE_BITMASK(8,15)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_CFG_DIVQ(x)  VTSS_EXTRACT_BITFIELD(x,8,15)

/**
 * \brief
 * This setting is ignored while SPARE_PLL_CFG.ENA_CFG is 0.Reference
 * divider value. See SPARE_PLL_FREQ_CFG for detailsBefore ENA_CFG is set
 * to '1' this must be set to:6 when the reference clock is 39.0625Mhz 3
 * when the reference clock is 25.00Mhz
 *
 * \details
 * N: Divide Fin by N+1
 *
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_CFG . DIVR
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_CFG_DIVR(x)  VTSS_ENCODE_BITFIELD(x,2,6)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_CFG_DIVR     VTSS_ENCODE_BITMASK(2,6)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_CFG_DIVR(x)  VTSS_EXTRACT_BITFIELD(x,2,6)

/**
 * \brief
 * Allow modification of PLL configuration. All register based PLL settings
 * are ignored while this bit is 0Frequency change procedure.Set BYPASS_ENA
 * = 1Configre DIVQ, DIVR, DIVFI and DIVFF to desired valuesSet ENA_CFG =
 * 1Set BYPASS_ENA = 0Switch CPU clock back to the reconfigured CPU_PLL.
 * See SPARE_PLL_CFG.ASSIGN_TO_CPU.
 *
 * \details
 * 0: Use fixed configuration
 * 1: Allow modification of PLL settings

 *
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_CFG . ENA_CFG
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_CFG_ENA_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_CFG_ENA_CFG  VTSS_BIT(1)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_CFG_ENA_CFG(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Read lock status signal from PLL
 *
 * \details
 * 0: PLL is not locked to reference clock
 * 1: PLL is locked
 *
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_CFG . LOCK_STAT
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_CFG_LOCK_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_CFG_LOCK_STAT  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_CFG_LOCK_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief CPU PLL configuration
 *
 * \details
 * Settings in this register are ignored while SPARE_PLL_CFG.ENA_CFG is 0.
 *
 * Fin: Reference clock frequency 25MHz or 39.0625MHz
 *
 * The PLL VCO frequency is calculated as
 * Fvco = Fin / DIVR_VAL * 8 * DIVF_VAL, where:
 * DIVR_VAL = DIVR+1
 * DIVF_VAL = 1 + DIVFI + (DIVFF / 2^24)
 * Fvco must be between 2000MHz and 4000MHz
 * Fin / DIVR_VAL must be between 5.0MHz and 7.5MHz
 *
 * The PLL output frequency is calculated as:
 * Fout = Fvco / DIVQ_VAL, where
 * DIVQ_VAL = Encoding of DIVQ. See DIVQ description
 *
 * Complete equation:
 * Fout = (Fin / (DIVR+1)) * 8 * (1+DIVFI + (DIVFF / 2^24)) / DIVQ_VAL

 *
 * Register: \a CHIP_TOP:SPARE_PLL_CFG:SPARE_PLL_FREQ_CFG
 */
#define VTSS_CHIP_TOP_SPARE_PLL_FREQ_CFG     VTSS_IOREG(VTSS_TO_CHIP_TOP,0x3c)

/**
 * \brief
 * This setting is ignored while SPARE_PLL_CFG.ENA_CFG is 0. Bypass PLL and
 * output the reference clock directly. Setting this bit to '1' will also
 * cause the PLL to reconfigure. The DIVFI, DIVFF, DIVQ and DIVR values can
 * be changed while the PLL is bypassed.Setting BYPASS_ENA is not glitch
 * free and the PLL output clock should not be used while BYPASS_ENA = 1.
 *
 * \details
 * 0: Normal oeration. Track reference clock
 * 1: Bypass PLL. Output reference clock directly

 *
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_FREQ_CFG . BYPASS_ENA
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_FREQ_CFG_BYPASS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_FREQ_CFG_BYPASS_ENA  VTSS_BIT(31)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_FREQ_CFG_BYPASS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * This setting is ignored while SPARE_PLL_CFG.ENA_CFG is 0.Feedback
 * divider integer value.The NEWDIV bit must be '0' when changing this
 * register
 *
 * \details
 * N: Divide by N+1
 *
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_FREQ_CFG . DIVFI
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_FREQ_CFG_DIVFI(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_FREQ_CFG_DIVFI     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_FREQ_CFG_DIVFI(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * This setting is ignored while SPARE_PLL_CFG.ENA_CFG is 0.Feedback
 * divider fractional value. The NEWDIV bit must be '0' when changing this
 * register
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_FREQ_CFG . DIVFF
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_FREQ_CFG_DIVFF(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_FREQ_CFG_DIVFF     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_FREQ_CFG_DIVFF(x)  VTSS_EXTRACT_BITFIELD(x,0,24)

/**
 * Register Group: \a CHIP_TOP:PLL_CHK
 *
 * PLL frequency check control
 */


/**
 * \brief Configuration of PLL frequency measurements
 *
 * \details
 * Register: \a CHIP_TOP:PLL_CHK:PLL_CHK_CFG
 */
#define VTSS_CHIP_TOP_PLL_CHK_CFG            VTSS_IOREG(VTSS_TO_CHIP_TOP,0x3d)

/**
 * \brief
 * Number of clock cycles per capture time unit. The default value of 3281
 * corresponds to a 10us base time unit.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_PLL_CHK_CFG . TIME_BASE
 */
#define  VTSS_F_CHIP_TOP_PLL_CHK_CFG_TIME_BASE(x)  VTSS_ENCODE_BITFIELD(x,13,12)
#define  VTSS_M_CHIP_TOP_PLL_CHK_CFG_TIME_BASE     VTSS_ENCODE_BITMASK(13,12)
#define  VTSS_X_CHIP_TOP_PLL_CHK_CFG_TIME_BASE(x)  VTSS_EXTRACT_BITFIELD(x,13,12)

/**
 * \brief
 * Configure the PLL frequency measuring time in base time units. The
 * default values correspond to a measuring time of 1msSee:
 * PLL_CHK_CFG.TIME_BASETime = MEASURE_TIME * TIME_BASE
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_PLL_CHK_CFG . MEASURE_TIME
 */
#define  VTSS_F_CHIP_TOP_PLL_CHK_CFG_MEASURE_TIME(x)  VTSS_ENCODE_BITFIELD(x,5,8)
#define  VTSS_M_CHIP_TOP_PLL_CHK_CFG_MEASURE_TIME     VTSS_ENCODE_BITMASK(5,8)
#define  VTSS_X_CHIP_TOP_PLL_CHK_CFG_MEASURE_TIME(x)  VTSS_EXTRACT_BITFIELD(x,5,8)

/**
 * \brief
 * Start sampling of the selected PLL frequency output. The HW will clear
 * this bit when the measuring time has passed.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_PLL_CHK_CFG . START
 */
#define  VTSS_F_CHIP_TOP_PLL_CHK_CFG_START(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CHIP_TOP_PLL_CHK_CFG_START    VTSS_BIT(4)
#define  VTSS_X_CHIP_TOP_PLL_CHK_CFG_START(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Select one of the six PLL frequencies to sample:0: CPU1: DDR2: CORE3:
 * RGMII4: FX1005: SPARE6-7: Reserved
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_PLL_CHK_CFG . PLL_CHK_SEL
 */
#define  VTSS_F_CHIP_TOP_PLL_CHK_CFG_PLL_CHK_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_CHIP_TOP_PLL_CHK_CFG_PLL_CHK_SEL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_CHIP_TOP_PLL_CHK_CFG_PLL_CHK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief PLL_CHK frequency counter
 *
 * \details
 * Register: \a CHIP_TOP:PLL_CHK:PLL_FREQ_CNT
 */
#define VTSS_CHIP_TOP_PLL_FREQ_CNT           VTSS_IOREG(VTSS_TO_CHIP_TOP,0x3e)

/**
 * \brief
 * The measured frequency of the selected PLL. This is expressed as the
 * number of counts that has occurred during the measuring time:PLL
 * frequency = 16*FREQ_CNT / (TIME_BASE * MEASURE_TIME)When the default
 * configuration is used a FREQ_CNT value of 1000 corresponds to a PLL
 * frequency frequency of 16 MHz.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_PLL_FREQ_CNT . FREQ_CNT
 */
#define  VTSS_F_CHIP_TOP_PLL_FREQ_CNT_FREQ_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,17)
#define  VTSS_M_CHIP_TOP_PLL_FREQ_CNT_FREQ_CNT     VTSS_ENCODE_BITMASK(0,17)
#define  VTSS_X_CHIP_TOP_PLL_FREQ_CNT_FREQ_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,17)


/**
 * \brief Monitor that the clock output of the PLLs are toggeling
 *
 * \details
 * Register: \a CHIP_TOP:PLL_CHK:PLL_MONITOR
 */
#define VTSS_CHIP_TOP_PLL_MONITOR            VTSS_IOREG(VTSS_TO_CHIP_TOP,0x3f)

/**
 * \brief
 * When this bit is set the CORE_PLL will be put into bypass mode if a PLL
 * monitor event has happened for the CORE_PLL. This allows the CPU to
 * access the switch core even if the CORE_PLL is not running.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_PLL_MONITOR . CORE_PLL_BYPASS
 */
#define  VTSS_F_CHIP_TOP_PLL_MONITOR_CORE_PLL_BYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_CHIP_TOP_PLL_MONITOR_CORE_PLL_BYPASS  VTSS_BIT(10)
#define  VTSS_X_CHIP_TOP_PLL_MONITOR_CORE_PLL_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * PLL monitor status. If a bit is set in this register, there has been an
 * event where a clock pulse was not seen within 32 CPU clocks
 *
 * \details
 * PLL that generated the event:
 * xxxx1: DDR
 * xxx1x: CORE
 * xx1xx: RGMII
 * x1xxx: FX100
 * 1xxxx: SPARE

 *
 * Field: ::VTSS_CHIP_TOP_PLL_MONITOR . STATUS
 */
#define  VTSS_F_CHIP_TOP_PLL_MONITOR_STATUS(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_CHIP_TOP_PLL_MONITOR_STATUS     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_CHIP_TOP_PLL_MONITOR_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/**
 * \brief
 * Enable monitoring of the PLL clocks. The CPU_CLK cannot be monitored.If
 * enabled an interrupt is generated if a clock pulse is not seen from a
 * PLL within a 32 CPU clock period. Note: This monitor will only detect
 * that a PLL clock is toggling. It will not detect that a PLL is running
 * with the expected frequency.The monitor must be disabled while a PLL is
 * being reconfigured.
 *
 * \details
 * xxxx1: DDR
 * xxx1x: CORE
 * xx1xx: RGMII
 * x1xxx: FX100
 * 1xxxx: SPARE

 *
 * Field: ::VTSS_CHIP_TOP_PLL_MONITOR . ENABLE
 */
#define  VTSS_F_CHIP_TOP_PLL_MONITOR_ENABLE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_CHIP_TOP_PLL_MONITOR_ENABLE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_CHIP_TOP_PLL_MONITOR_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * Register Group: \a CHIP_TOP:TEMP_SENSOR
 *
 * Temperature sensor control
 */


/**
 * \brief Temperature Sensor Control
 *
 * \details
 * Register: \a CHIP_TOP:TEMP_SENSOR:TEMP_SENSOR_CTRL
 */
#define VTSS_CHIP_TOP_TEMP_SENSOR_CTRL       VTSS_IOREG(VTSS_TO_CHIP_TOP,0x40)

/**
 * \brief
 * Set to force reading of temperature. This field only works when
 * SAMPLE_ENA is cleared. The read will either instantaneously or
 * synchronized to the RDY output of the temperature sensor if the sensor
 * is enabled.	The temperature sensor can be configured to run
 * continuously by using these settings:FORCE_POWER_UP = 1Wait 50
 * usFORCE_CLK = 1Wait 5 usFORCE_NO_RST = 1Wait 5 usFORCE_RUN =
 * 1FORCE_TEMP_RD= 1This will cause the temperature sensor to sample
 * continuously and provide the result in TEMP_SENSOR_STAT.TEMP.  The
 * status TEMP_SENSOR_STAT.TEMP_VALID will be 1 after the first sample.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_TEMP_SENSOR_CTRL . FORCE_TEMP_RD
 */
#define  VTSS_F_CHIP_TOP_TEMP_SENSOR_CTRL_FORCE_TEMP_RD(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CHIP_TOP_TEMP_SENSOR_CTRL_FORCE_TEMP_RD  VTSS_BIT(4)
#define  VTSS_X_CHIP_TOP_TEMP_SENSOR_CTRL_FORCE_TEMP_RD(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Set to force RUN signal towards temperature sensor. This field only
 * works when SAMPLE_ENA is cleared.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_TEMP_SENSOR_CTRL . FORCE_RUN
 */
#define  VTSS_F_CHIP_TOP_TEMP_SENSOR_CTRL_FORCE_RUN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CHIP_TOP_TEMP_SENSOR_CTRL_FORCE_RUN  VTSS_BIT(3)
#define  VTSS_X_CHIP_TOP_TEMP_SENSOR_CTRL_FORCE_RUN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Set to force the RSTN signal towards temperature sensor (release of
 * reset). This field only works when SAMPLE_ENA is cleared.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_TEMP_SENSOR_CTRL . FORCE_NO_RST
 */
#define  VTSS_F_CHIP_TOP_TEMP_SENSOR_CTRL_FORCE_NO_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CHIP_TOP_TEMP_SENSOR_CTRL_FORCE_NO_RST  VTSS_BIT(2)
#define  VTSS_X_CHIP_TOP_TEMP_SENSOR_CTRL_FORCE_NO_RST(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Set to force the PD signal towards temperature sensor. This field only
 * works when SAMPLE_ENA is cleared.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_TEMP_SENSOR_CTRL . FORCE_POWER_UP
 */
#define  VTSS_F_CHIP_TOP_TEMP_SENSOR_CTRL_FORCE_POWER_UP(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CHIP_TOP_TEMP_SENSOR_CTRL_FORCE_POWER_UP  VTSS_BIT(1)
#define  VTSS_X_CHIP_TOP_TEMP_SENSOR_CTRL_FORCE_POWER_UP(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Set to force a clock signal towards the temperature sensor. The clock
 * frequency will be controlled by the TEMP_SENSOR_CFG.CLK_CYCLES_1US
 * setting. This field only works when SAMPLE_ENA is cleared.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_TEMP_SENSOR_CTRL . FORCE_CLK
 */
#define  VTSS_F_CHIP_TOP_TEMP_SENSOR_CTRL_FORCE_CLK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_TEMP_SENSOR_CTRL_FORCE_CLK  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_TEMP_SENSOR_CTRL_FORCE_CLK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Temperature Sensor Configuration
 *
 * \details
 * Register: \a CHIP_TOP:TEMP_SENSOR:TEMP_SENSOR_CFG
 */
#define VTSS_CHIP_TOP_TEMP_SENSOR_CFG        VTSS_IOREG(VTSS_TO_CHIP_TOP,0x41)

/**
 * \brief
 * The number of system clock cycles in one 1us. This is used to generated
 * the temperature sensor clock signal (CLK.)  The frequency of CLK must be
 * higher than 0.75Mhz and lower than 2Mhz.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_TEMP_SENSOR_CFG . CLK_CYCLES_1US
 */
#define  VTSS_F_CHIP_TOP_TEMP_SENSOR_CFG_CLK_CYCLES_1US(x)  VTSS_ENCODE_BITFIELD(x,15,9)
#define  VTSS_M_CHIP_TOP_TEMP_SENSOR_CFG_CLK_CYCLES_1US     VTSS_ENCODE_BITMASK(15,9)
#define  VTSS_X_CHIP_TOP_TEMP_SENSOR_CFG_CLK_CYCLES_1US(x)  VTSS_EXTRACT_BITFIELD(x,15,9)

/**
 * \brief
 * Trim value. This value should only be modified as a result of a sensor
 * calibration
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_TEMP_SENSOR_CFG . TRIM_VAL
 */
#define  VTSS_F_CHIP_TOP_TEMP_SENSOR_CFG_TRIM_VAL(x)  VTSS_ENCODE_BITFIELD(x,11,4)
#define  VTSS_M_CHIP_TOP_TEMP_SENSOR_CFG_TRIM_VAL     VTSS_ENCODE_BITMASK(11,4)
#define  VTSS_X_CHIP_TOP_TEMP_SENSOR_CFG_TRIM_VAL(x)  VTSS_EXTRACT_BITFIELD(x,11,4)

/**
 * \brief
 * Set this field to enable calibration of the sensor. A 0.7V signal must
 * be applied to the calibration input.The calibration procedure is as
 * follows:Set SAMPLE_ENA to 0Apply 0.7V +/- 10% to the calibration input
 * pinMeasure actual voltage on calibration input with highest possible
 * precisionSet CAL_ENA to 1Set SAMPLE_ENA to 1Read TEMP_SENSOR_STAT.TEMP
 * and use this value and the calibration voltage to calculate the
 * calibration temperature.Find TRIM_VAL:Set SAMPLE_ENA to 0Set CAL_ENA to
 * 0Set SAMPLE_ENA to 1Change TRIM_VAL until TEMP_SENSOR_STAT.TEMP results
 * in a temperature as close as possible to the calibration
 * temperatureNormal mode:Set SAMPLE_ENA to 1Use TRIM_VAL obtained from
 * calibration
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_TEMP_SENSOR_CFG . CAL_ENA
 */
#define  VTSS_F_CHIP_TOP_TEMP_SENSOR_CFG_CAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_CHIP_TOP_TEMP_SENSOR_CFG_CAL_ENA  VTSS_BIT(10)
#define  VTSS_X_CHIP_TOP_TEMP_SENSOR_CFG_CAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Power up delay. The unit is number of sensor CLK cycles. See:
 * CLK_CYCLES_1USDefault value corresponds to a 50us delay, which is the
 * minimum required value.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_TEMP_SENSOR_CFG . PWR_UP_DELAY
 */
#define  VTSS_F_CHIP_TOP_TEMP_SENSOR_CFG_PWR_UP_DELAY(x)  VTSS_ENCODE_BITFIELD(x,3,7)
#define  VTSS_M_CHIP_TOP_TEMP_SENSOR_CFG_PWR_UP_DELAY     VTSS_ENCODE_BITMASK(3,7)
#define  VTSS_X_CHIP_TOP_TEMP_SENSOR_CFG_PWR_UP_DELAY(x)  VTSS_EXTRACT_BITFIELD(x,3,7)

/**
 * \brief
 * Set this bit to start a temperature sample cycle. This is only used if
 * continuous sampling is disabled.Procedure:Set START_CAPTURE to 1Wait
 * until hardware clears START_CAPTURE Read temperature from
 * TEMP_SENSOR_STAT.TEMP
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_TEMP_SENSOR_CFG . START_CAPTURE
 */
#define  VTSS_F_CHIP_TOP_TEMP_SENSOR_CFG_START_CAPTURE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CHIP_TOP_TEMP_SENSOR_CFG_START_CAPTURE  VTSS_BIT(2)
#define  VTSS_X_CHIP_TOP_TEMP_SENSOR_CFG_START_CAPTURE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Set this field to enable continuous sampling of temperature. The latest
 * sample value will be available in TEMP_SENSOR_STAT.TEMP
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_TEMP_SENSOR_CFG . CONTINUOUS_MODE
 */
#define  VTSS_F_CHIP_TOP_TEMP_SENSOR_CFG_CONTINUOUS_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CHIP_TOP_TEMP_SENSOR_CFG_CONTINUOUS_MODE  VTSS_BIT(1)
#define  VTSS_X_CHIP_TOP_TEMP_SENSOR_CFG_CONTINUOUS_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Set this field to enable sampling of temperature. The sensor will be
 * taken out of power down mode and the temperature sampling is stared when
 * SAMPLE_ENA is set to 1
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_TEMP_SENSOR_CFG . SAMPLE_ENA
 */
#define  VTSS_F_CHIP_TOP_TEMP_SENSOR_CFG_SAMPLE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CHIP_TOP_TEMP_SENSOR_CFG_SAMPLE_ENA  VTSS_BIT(0)
#define  VTSS_X_CHIP_TOP_TEMP_SENSOR_CFG_SAMPLE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Temperature Sensor Status
 *
 * \details
 * Register: \a CHIP_TOP:TEMP_SENSOR:TEMP_SENSOR_STAT
 */
#define VTSS_CHIP_TOP_TEMP_SENSOR_STAT       VTSS_IOREG(VTSS_TO_CHIP_TOP,0x42)

/**
 * \brief
 * This field is set when valid temperature data is available in
 * TEMP_SENSOR_STAT.TEMP
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_TEMP_SENSOR_STAT . TEMP_VALID
 */
#define  VTSS_F_CHIP_TOP_TEMP_SENSOR_STAT_TEMP_VALID(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_CHIP_TOP_TEMP_SENSOR_STAT_TEMP_VALID  VTSS_BIT(12)
#define  VTSS_X_CHIP_TOP_TEMP_SENSOR_STAT_TEMP_VALID(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Temperature data readout This field is valid when
 * TEMP_SENSOR_STAT.TEMP_VALID is set. This field is continually updated
 * while the temperature sensor is enabled. See TEMP_SENSOR_CFG.SAMPLE_ENA
 * for more information.
 *
 * \details
 * Temp(C) = TEMP_SENSOR_STAT.TEMP / 4096 * 352.2 - 109.4
 *
 * Field: ::VTSS_CHIP_TOP_TEMP_SENSOR_STAT . TEMP
 */
#define  VTSS_F_CHIP_TOP_TEMP_SENSOR_STAT_TEMP(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_CHIP_TOP_TEMP_SENSOR_STAT_TEMP     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_CHIP_TOP_TEMP_SENSOR_STAT_TEMP(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


#endif /* _VTSS_LAGUNA_REGS_CHIP_TOP_H_ */
