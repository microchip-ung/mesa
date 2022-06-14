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
 * \brief HSIO_SWC memory bist pass status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:HSIO_SWC_MBIST_PASS
 */
#define VTSS_CHIP_TOP_HSIO_SWC_MBIST_PASS    VTSS_IOREG(VTSS_TO_CHIP_TOP,0x3)

/**
 * \brief
 * The HSIO_SWC MBIST has passed
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_HSIO_SWC_MBIST_PASS . HSIO_SWC_MBIST_PASS
 */
#define  VTSS_F_CHIP_TOP_HSIO_SWC_MBIST_PASS_HSIO_SWC_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CHIP_TOP_HSIO_SWC_MBIST_PASS_HSIO_SWC_MBIST_PASS     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CHIP_TOP_HSIO_SWC_MBIST_PASS_HSIO_SWC_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief HSIO_SWC memory bist done status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:HSIO_SWC_MBIST_DONE
 */
#define VTSS_CHIP_TOP_HSIO_SWC_MBIST_DONE    VTSS_IOREG(VTSS_TO_CHIP_TOP,0x4)

/**
 * \brief
 * The HSIO_SWC MBIST is done
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_HSIO_SWC_MBIST_DONE . HSIO_SWC_MBIST_DONE
 */
#define  VTSS_F_CHIP_TOP_HSIO_SWC_MBIST_DONE_HSIO_SWC_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CHIP_TOP_HSIO_SWC_MBIST_DONE_HSIO_SWC_MBIST_DONE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CHIP_TOP_HSIO_SWC_MBIST_DONE_HSIO_SWC_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief REW memory bist pass status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:REW_MBIST_PASS
 */
#define VTSS_CHIP_TOP_REW_MBIST_PASS         VTSS_IOREG(VTSS_TO_CHIP_TOP,0x5)

/**
 * \brief
 * The REW MBIST has passed
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_REW_MBIST_PASS . REW_MBIST_PASS
 */
#define  VTSS_F_CHIP_TOP_REW_MBIST_PASS_REW_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CHIP_TOP_REW_MBIST_PASS_REW_MBIST_PASS     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CHIP_TOP_REW_MBIST_PASS_REW_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief REW memory bist done status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:REW_MBIST_DONE
 */
#define VTSS_CHIP_TOP_REW_MBIST_DONE         VTSS_IOREG(VTSS_TO_CHIP_TOP,0x6)

/**
 * \brief
 * The REW MBIST is done
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_REW_MBIST_DONE . REW_MBIST_DONE
 */
#define  VTSS_F_CHIP_TOP_REW_MBIST_DONE_REW_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CHIP_TOP_REW_MBIST_DONE_REW_MBIST_DONE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CHIP_TOP_REW_MBIST_DONE_REW_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


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
#define  VTSS_F_CHIP_TOP_QSYS_MBIST_PASS_QSYS_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CHIP_TOP_QSYS_MBIST_PASS_QSYS_MBIST_PASS     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CHIP_TOP_QSYS_MBIST_PASS_QSYS_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


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
#define  VTSS_F_CHIP_TOP_QSYS_MBIST_DONE_QSYS_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CHIP_TOP_QSYS_MBIST_DONE_QSYS_MBIST_DONE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CHIP_TOP_QSYS_MBIST_DONE_QSYS_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


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
#define  VTSS_F_CHIP_TOP_PMEM_MBIST_PASS_PMEM_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CHIP_TOP_PMEM_MBIST_PASS_PMEM_MBIST_PASS     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CHIP_TOP_PMEM_MBIST_PASS_PMEM_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


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
#define  VTSS_F_CHIP_TOP_PMEM_MBIST_DONE_PMEM_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CHIP_TOP_PMEM_MBIST_DONE_PMEM_MBIST_DONE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CHIP_TOP_PMEM_MBIST_DONE_PMEM_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


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
#define  VTSS_F_CHIP_TOP_VCAP_MBIST_PASS_VCAP_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CHIP_TOP_VCAP_MBIST_PASS_VCAP_MBIST_PASS     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CHIP_TOP_VCAP_MBIST_PASS_VCAP_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


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
#define  VTSS_F_CHIP_TOP_VCAP_MBIST_DONE_VCAP_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CHIP_TOP_VCAP_MBIST_DONE_VCAP_MBIST_DONE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CHIP_TOP_VCAP_MBIST_DONE_VCAP_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


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
#define  VTSS_F_CHIP_TOP_ANA_CL32_MBIST_PASS_ANA_CL32_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CHIP_TOP_ANA_CL32_MBIST_PASS_ANA_CL32_MBIST_PASS     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CHIP_TOP_ANA_CL32_MBIST_PASS_ANA_CL32_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


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
#define  VTSS_F_CHIP_TOP_ANA_CL32_MBIST_DONE_ANA_CL32_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CHIP_TOP_ANA_CL32_MBIST_DONE_ANA_CL32_MBIST_DONE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CHIP_TOP_ANA_CL32_MBIST_DONE_ANA_CL32_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


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
#define  VTSS_F_CHIP_TOP_ANA_AC_MBIST_PASS_ANA_AC_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CHIP_TOP_ANA_AC_MBIST_PASS_ANA_AC_MBIST_PASS     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CHIP_TOP_ANA_AC_MBIST_PASS_ANA_AC_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


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
#define  VTSS_F_CHIP_TOP_ANA_AC_MBIST_DONE_ANA_AC_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CHIP_TOP_ANA_AC_MBIST_DONE_ANA_AC_MBIST_DONE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CHIP_TOP_ANA_AC_MBIST_DONE_ANA_AC_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief DEVCPU0 memory bist pass status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:DEVCPU0_MBIST_PASS
 */
#define VTSS_CHIP_TOP_DEVCPU0_MBIST_PASS     VTSS_IOREG(VTSS_TO_CHIP_TOP,0x11)

/**
 * \brief
 * The DEVCPU0 MBIST has passed
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_DEVCPU0_MBIST_PASS . DEVCPU0_MBIST_PASS
 */
#define  VTSS_F_CHIP_TOP_DEVCPU0_MBIST_PASS_DEVCPU0_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CHIP_TOP_DEVCPU0_MBIST_PASS_DEVCPU0_MBIST_PASS     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CHIP_TOP_DEVCPU0_MBIST_PASS_DEVCPU0_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief DEVCPU0 memory bist done status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:DEVCPU0_MBIST_DONE
 */
#define VTSS_CHIP_TOP_DEVCPU0_MBIST_DONE     VTSS_IOREG(VTSS_TO_CHIP_TOP,0x12)

/**
 * \brief
 * The DEVCPU0 MBIST is done
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_DEVCPU0_MBIST_DONE . DEVCPU0_MBIST_DONE
 */
#define  VTSS_F_CHIP_TOP_DEVCPU0_MBIST_DONE_DEVCPU0_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CHIP_TOP_DEVCPU0_MBIST_DONE_DEVCPU0_MBIST_DONE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CHIP_TOP_DEVCPU0_MBIST_DONE_DEVCPU0_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief DEVCPU1 memory bist pass status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:DEVCPU1_MBIST_PASS
 */
#define VTSS_CHIP_TOP_DEVCPU1_MBIST_PASS     VTSS_IOREG(VTSS_TO_CHIP_TOP,0x13)

/**
 * \brief
 * The DEVCPU1 MBIST has passed
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_DEVCPU1_MBIST_PASS . DEVCPU1_MBIST_PASS
 */
#define  VTSS_F_CHIP_TOP_DEVCPU1_MBIST_PASS_DEVCPU1_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CHIP_TOP_DEVCPU1_MBIST_PASS_DEVCPU1_MBIST_PASS     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CHIP_TOP_DEVCPU1_MBIST_PASS_DEVCPU1_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief DEVCPU1 memory bist done status
 *
 * \details
 * Register: \a CHIP_TOP:MBIST_STAT:DEVCPU1_MBIST_DONE
 */
#define VTSS_CHIP_TOP_DEVCPU1_MBIST_DONE     VTSS_IOREG(VTSS_TO_CHIP_TOP,0x14)

/**
 * \brief
 * The DEVCPU1 MBIST is done
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_DEVCPU1_MBIST_DONE . DEVCPU1_MBIST_DONE
 */
#define  VTSS_F_CHIP_TOP_DEVCPU1_MBIST_DONE_DEVCPU1_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CHIP_TOP_DEVCPU1_MBIST_DONE_DEVCPU1_MBIST_DONE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CHIP_TOP_DEVCPU1_MBIST_DONE_DEVCPU1_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


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
#define  VTSS_F_CHIP_TOP_PROC_MBIST_PASS_PROC_MBIST_PASS(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CHIP_TOP_PROC_MBIST_PASS_PROC_MBIST_PASS     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CHIP_TOP_PROC_MBIST_PASS_PROC_MBIST_PASS(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


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
#define  VTSS_F_CHIP_TOP_PROC_MBIST_DONE_PROC_MBIST_DONE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_CHIP_TOP_PROC_MBIST_DONE_PROC_MBIST_DONE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_CHIP_TOP_PROC_MBIST_DONE_PROC_MBIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

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
#define VTSS_CHIP_TOP_OTP_CFG                VTSS_IOREG(VTSS_TO_CHIP_TOP,0x17)

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
#define VTSS_CHIP_TOP_OTP_RCR(ri)            VTSS_IOREG(VTSS_TO_CHIP_TOP,0x18 + (ri))

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
#define VTSS_CHIP_TOP_OTP_MSC(ri)            VTSS_IOREG(VTSS_TO_CHIP_TOP,0x1b + (ri))

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
#define VTSS_CHIP_TOP_OTP_ID                 VTSS_IOREG(VTSS_TO_CHIP_TOP,0x1f)

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
#define VTSS_CHIP_TOP_OTP_PRD(ri)            VTSS_IOREG(VTSS_TO_CHIP_TOP,0x28 + (ri))

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
#define VTSS_CHIP_TOP_CPU_PLL_CFG            VTSS_IOREG(VTSS_TO_CHIP_TOP,0x30)

/**
 * \brief
 * Update acknowledge from PLL. Will be low when UPDATE_CFG is low and then
 * toggle high when UPDAT_CFG toggles high.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CPU_PLL_CFG . UPDATE_ACK
 */
#define  VTSS_F_CHIP_TOP_CPU_PLL_CFG_UPDATE_ACK(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_CHIP_TOP_CPU_PLL_CFG_UPDATE_ACK  VTSS_BIT(7)
#define  VTSS_X_CHIP_TOP_CPU_PLL_CFG_UPDATE_ACK(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Enable test mode
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CPU_PLL_CFG . TEST_ENA
 */
#define  VTSS_F_CHIP_TOP_CPU_PLL_CFG_TEST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_CHIP_TOP_CPU_PLL_CFG_TEST_ENA  VTSS_BIT(6)
#define  VTSS_X_CHIP_TOP_CPU_PLL_CFG_TEST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * This settings is ignored while CPU_PLL_CFG.ENA_CFG is 0. Bypass PLL and
 * output the reference clock directly. Should not be set in normal
 * operation
 *
 * \details
 * 0: Track reference clock
 * 1: Bypass PLL. Output reference clock directly

 *
 * Field: ::VTSS_CHIP_TOP_CPU_PLL_CFG . BYPASS_ENA
 */
#define  VTSS_F_CHIP_TOP_CPU_PLL_CFG_BYPASS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_CHIP_TOP_CPU_PLL_CFG_BYPASS_ENA  VTSS_BIT(5)
#define  VTSS_X_CHIP_TOP_CPU_PLL_CFG_BYPASS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Enable PLL clock output
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CPU_PLL_CFG . ENABLE_CLOCK
 */
#define  VTSS_F_CHIP_TOP_CPU_PLL_CFG_ENABLE_CLOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CHIP_TOP_CPU_PLL_CFG_ENABLE_CLOCK  VTSS_BIT(4)
#define  VTSS_X_CHIP_TOP_CPU_PLL_CFG_ENABLE_CLOCK(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable PLL
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CPU_PLL_CFG . ENABLE_PLL
 */
#define  VTSS_F_CHIP_TOP_CPU_PLL_CFG_ENABLE_PLL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CHIP_TOP_CPU_PLL_CFG_ENABLE_PLL  VTSS_BIT(3)
#define  VTSS_X_CHIP_TOP_CPU_PLL_CFG_ENABLE_PLL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * This bit allows user control. Must toggle from 0 to 1 to update the
 * generated PLL frequency. See ENA_CFG
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CPU_PLL_CFG . UPDATE_CFG
 */
#define  VTSS_F_CHIP_TOP_CPU_PLL_CFG_UPDATE_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CHIP_TOP_CPU_PLL_CFG_UPDATE_CFG  VTSS_BIT(2)
#define  VTSS_X_CHIP_TOP_CPU_PLL_CFG_UPDATE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Allow modification of PLL configuration. All register based PLL setting
 * are ignored while this bit is 0Frequency change procedure:Switch CPU
 * clock to spare PLL. See SPARE_PLL_CFG.ASSIGN_TO_CPU. Make sure that the
 * SPARE_PLL is generating a valid frequency before the switch
 * over.Reconfigure CPU_PLL_FREQ_CFGSet ENA_CFG = 1, UPDATE_CFG = 0,
 * ENABLE_PLL = 0 and ENABLE_CLOCK = 0Set ENA_CFG = 1, UPDATE_CFG = 1,
 * ENABLE_PLL = 1 and ENABLE_CLOCK = 1Switch CPU clock back to the
 * reconfigured CPU_PLL. See SPARE_PLL_CFG.ASSIGN_TO_CPU.
 *
 * \details
 * 0: Use fixed configuration
 * 1: Allow modification of ND, QD and FRACR parameters

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
 * This register configures the out frequency of the PLL:
 *
 * Reference clock frequency: Fin
 *
 * Fvco = Fin * (ND + FRACR*2^(-12)). Fvco must be between 750MHz and
 * 1500MHz
 *
 * The PLL output frequency is calculated as:
 * Fout = Fvco / (QD+1)

 *
 * Register: \a CHIP_TOP:CPU_PLL_CFG:CPU_PLL_FREQ_CFG
 */
#define VTSS_CHIP_TOP_CPU_PLL_FREQ_CFG       VTSS_IOREG(VTSS_TO_CHIP_TOP,0x31)

/**
 * \brief
 * This sets the PLL loop filter to work with the post divider reference
 * frequency
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CPU_PLL_FREQ_CFG . FILTER_CTRL
 */
#define  VTSS_F_CHIP_TOP_CPU_PLL_FREQ_CFG_FILTER_CTRL(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_CHIP_TOP_CPU_PLL_FREQ_CFG_FILTER_CTRL     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_CHIP_TOP_CPU_PLL_FREQ_CFG_FILTER_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \brief
 * Fractional loop divider value. See register description
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CPU_PLL_FREQ_CFG . FRACR
 */
#define  VTSS_F_CHIP_TOP_CPU_PLL_FREQ_CFG_FRACR(x)  VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_CHIP_TOP_CPU_PLL_FREQ_CFG_FRACR     VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_CHIP_TOP_CPU_PLL_FREQ_CFG_FRACR(x)  VTSS_EXTRACT_BITFIELD(x,16,12)

/**
 * \brief
 * Post scalar divider for output clock. Divide Fvco frequency by QD
 *
 * \details
 * 0: Reserved
 * N: Divide by N
 *
 * Field: ::VTSS_CHIP_TOP_CPU_PLL_FREQ_CFG . QD
 */
#define  VTSS_F_CHIP_TOP_CPU_PLL_FREQ_CFG_QD(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_CHIP_TOP_CPU_PLL_FREQ_CFG_QD     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_CHIP_TOP_CPU_PLL_FREQ_CFG_QD(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Integer loop multiplier value. Controls Fvco frequency
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CPU_PLL_FREQ_CFG . ND
 */
#define  VTSS_F_CHIP_TOP_CPU_PLL_FREQ_CFG_ND(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CHIP_TOP_CPU_PLL_FREQ_CFG_ND     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CHIP_TOP_CPU_PLL_FREQ_CFG_ND(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a CHIP_TOP:DDR_PLL_CFG
 *
 * CPU PLL configuration
 */


/**
 * \brief CPU PLL configuration
 *
 * \details
 * Register: \a CHIP_TOP:DDR_PLL_CFG:DDR_PLL_CFG
 */
#define VTSS_CHIP_TOP_DDR_PLL_CFG            VTSS_IOREG(VTSS_TO_CHIP_TOP,0x32)

/**
 * \brief
 * Update acknowledge from PLL. Will be low when UPDATE_CFG is low and then
 * toggle high when UPDAT_CFG toggles high.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_DDR_PLL_CFG . UPDATE_ACK
 */
#define  VTSS_F_CHIP_TOP_DDR_PLL_CFG_UPDATE_ACK(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_CHIP_TOP_DDR_PLL_CFG_UPDATE_ACK  VTSS_BIT(7)
#define  VTSS_X_CHIP_TOP_DDR_PLL_CFG_UPDATE_ACK(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Enable test mode
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_DDR_PLL_CFG . TEST_ENA
 */
#define  VTSS_F_CHIP_TOP_DDR_PLL_CFG_TEST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_CHIP_TOP_DDR_PLL_CFG_TEST_ENA  VTSS_BIT(6)
#define  VTSS_X_CHIP_TOP_DDR_PLL_CFG_TEST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * This settings is ignored while DDR_PLL_CFG.ENA_CFG is 0. Bypass PLL and
 * output the reference clock directly. Should not be set in normal
 * operation
 *
 * \details
 * 0: Track reference clock
 * 1: Bypass PLL. Output reference clock directly

 *
 * Field: ::VTSS_CHIP_TOP_DDR_PLL_CFG . BYPASS_ENA
 */
#define  VTSS_F_CHIP_TOP_DDR_PLL_CFG_BYPASS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_CHIP_TOP_DDR_PLL_CFG_BYPASS_ENA  VTSS_BIT(5)
#define  VTSS_X_CHIP_TOP_DDR_PLL_CFG_BYPASS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Enable PLL clock output
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_DDR_PLL_CFG . ENABLE_CLOCK
 */
#define  VTSS_F_CHIP_TOP_DDR_PLL_CFG_ENABLE_CLOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CHIP_TOP_DDR_PLL_CFG_ENABLE_CLOCK  VTSS_BIT(4)
#define  VTSS_X_CHIP_TOP_DDR_PLL_CFG_ENABLE_CLOCK(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable PLL
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_DDR_PLL_CFG . ENABLE_PLL
 */
#define  VTSS_F_CHIP_TOP_DDR_PLL_CFG_ENABLE_PLL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CHIP_TOP_DDR_PLL_CFG_ENABLE_PLL  VTSS_BIT(3)
#define  VTSS_X_CHIP_TOP_DDR_PLL_CFG_ENABLE_PLL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Update signal divider ratio
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_DDR_PLL_CFG . UPDATE_CFG
 */
#define  VTSS_F_CHIP_TOP_DDR_PLL_CFG_UPDATE_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CHIP_TOP_DDR_PLL_CFG_UPDATE_CFG  VTSS_BIT(2)
#define  VTSS_X_CHIP_TOP_DDR_PLL_CFG_UPDATE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Allow modification of PLL configuration. All register based PLL setting
 * are ignored while this bit is 0Changing of the DDR frequency is not
 * glitch free and must be done as part of the DDR initialization
 * procedure.Configuration procedure:Reconfigure DDR_PLL_FREQ_CFG to
 * desired frequency.Set ENA_CFG = 1, UPDATE_CFG = 0, ENABLE_PLL = 0 and
 * ENABLE_CLOCK = 0Set ENA_CFG = 1, UPDATE_CFG = 1, ENABLE_PLL = 1 and
 * ENABLE_CLOCK = 1
 *
 * \details
 * 0: Use fixed configuration
 * 1: Allow modification of ND, QD and FRACR parameters

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
 * This register configures the out frequency of the PLL:
 *
 * Reference clock frequency: Fin
 *
 * Fvco = Fin * (ND + FRACR*2^(-12)). Fvco must be between 750MHz and
 * 1500MHz
 *
 * The PLL output frequency is calculated as:
 * Fout = Fvco / (QD+1)

 *
 * Register: \a CHIP_TOP:DDR_PLL_CFG:DDR_PLL_FREQ_CFG
 */
#define VTSS_CHIP_TOP_DDR_PLL_FREQ_CFG       VTSS_IOREG(VTSS_TO_CHIP_TOP,0x33)

/**
 * \brief
 * This sets the PLL loop filter to work with the post divider reference
 * frequency
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_DDR_PLL_FREQ_CFG . FILTER_CTRL
 */
#define  VTSS_F_CHIP_TOP_DDR_PLL_FREQ_CFG_FILTER_CTRL(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_CHIP_TOP_DDR_PLL_FREQ_CFG_FILTER_CTRL     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_CHIP_TOP_DDR_PLL_FREQ_CFG_FILTER_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \brief
 * Fractional loop divider value. See register description
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_DDR_PLL_FREQ_CFG . FRACR
 */
#define  VTSS_F_CHIP_TOP_DDR_PLL_FREQ_CFG_FRACR(x)  VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_CHIP_TOP_DDR_PLL_FREQ_CFG_FRACR     VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_CHIP_TOP_DDR_PLL_FREQ_CFG_FRACR(x)  VTSS_EXTRACT_BITFIELD(x,16,12)

/**
 * \brief
 * Post scalar divider for output clock. Divide Fvco frequency by QD
 *
 * \details
 * 0: Reserved
 * N: Divide by N
 *
 * Field: ::VTSS_CHIP_TOP_DDR_PLL_FREQ_CFG . QD
 */
#define  VTSS_F_CHIP_TOP_DDR_PLL_FREQ_CFG_QD(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_CHIP_TOP_DDR_PLL_FREQ_CFG_QD     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_CHIP_TOP_DDR_PLL_FREQ_CFG_QD(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Integer loop multiplier value. Controls Fvco frequency
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_DDR_PLL_FREQ_CFG . ND
 */
#define  VTSS_F_CHIP_TOP_DDR_PLL_FREQ_CFG_ND(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CHIP_TOP_DDR_PLL_FREQ_CFG_ND     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CHIP_TOP_DDR_PLL_FREQ_CFG_ND(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a CHIP_TOP:CORE_PLL_CFG
 *
 * CPU PLL configuration
 */


/**
 * \brief CPU PLL configuration
 *
 * \details
 * Register: \a CHIP_TOP:CORE_PLL_CFG:CORE_PLL_CFG
 */
#define VTSS_CHIP_TOP_CORE_PLL_CFG           VTSS_IOREG(VTSS_TO_CHIP_TOP,0x34)

/**
 * \brief
 * Update acknowledge from PLL. Will be low when UPDATE_CFG is low and then
 * toggle high when UPDAT_CFG toggles high.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_CFG . UPDATE_ACK
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_CFG_UPDATE_ACK(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_CHIP_TOP_CORE_PLL_CFG_UPDATE_ACK  VTSS_BIT(9)
#define  VTSS_X_CHIP_TOP_CORE_PLL_CFG_UPDATE_ACK(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Enable test mode
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_CFG . TEST_ENA
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_CFG_TEST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_CHIP_TOP_CORE_PLL_CFG_TEST_ENA  VTSS_BIT(8)
#define  VTSS_X_CHIP_TOP_CORE_PLL_CFG_TEST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * This settings is ignored while CORE_PLL_CFG.ENA_CFG is 0. Bypass PLL and
 * output the reference clock directly. Should not be set in normal
 * operation
 *
 * \details
 * 0: Track reference clock
 * 1: Bypass PLL. Output reference clock directly

 *
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_CFG . BYPASS_ENA
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_CFG_BYPASS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_CHIP_TOP_CORE_PLL_CFG_BYPASS_ENA  VTSS_BIT(7)
#define  VTSS_X_CHIP_TOP_CORE_PLL_CFG_BYPASS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Enable PLL clock output
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_CFG . ENABLE_CLOCK
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_CFG_ENABLE_CLOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_CHIP_TOP_CORE_PLL_CFG_ENABLE_CLOCK  VTSS_BIT(6)
#define  VTSS_X_CHIP_TOP_CORE_PLL_CFG_ENABLE_CLOCK(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Enable PLL
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_CFG . ENABLE_PLL
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_CFG_ENABLE_PLL(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_CHIP_TOP_CORE_PLL_CFG_ENABLE_PLL  VTSS_BIT(5)
#define  VTSS_X_CHIP_TOP_CORE_PLL_CFG_ENABLE_PLL(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Update signal divider ratio
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_CFG . UPDATE_CFG
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_CFG_UPDATE_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CHIP_TOP_CORE_PLL_CFG_UPDATE_CFG  VTSS_BIT(4)
#define  VTSS_X_CHIP_TOP_CORE_PLL_CFG_UPDATE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

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
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_CFG . REF_CLK_SEL
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_CFG_REF_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_CHIP_TOP_CORE_PLL_CFG_REF_CLK_SEL     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_CHIP_TOP_CORE_PLL_CFG_REF_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * Allow modification of PLL configuration. All register based PLL setting
 * are ignored while this bit is 0Frequency change procedure:Switch core
 * clock to spare PLL. See SPARE_PLL_CFG.ASSIGN_TO_CORE. Make sure that the
 * SPARE_PLL is generating a valid frequency before the switch
 * over.Reconfigure CORE_PLL_FREQ_CFG to desired valuesSet ENA_CFG = 1,
 * UPDATE_CFG = 0, ENABLE_PLL = 0 and ENABLE_CLOCK = 0Set ENA_CFG = 1,
 * UPDATE_CFG = 1, ENABLE_PLL = 1 and ENABLE_CLOCK = 1Switch CORE clock
 * back to the reconfigured CORE_PLL. See SPARE_PLL_CFG.ASSIGN_TO_CORE.
 *
 * \details
 * 0: Use fixed configuration
 * 1: Allow modification of ND, QD and FRACR parameters

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
 * This register configures the out frequency of the PLL:
 *
 * Reference clock frequency: Fin
 *
 * Fvco = Fin * (ND + FRACR*2^(-12)). Fvco must be between 750MHz and
 * 1500MHz
 *
 * The PLL output frequency is calculated as:
 * Fout = Fvco / (QD+1)

 *
 * Register: \a CHIP_TOP:CORE_PLL_CFG:CORE_PLL_FREQ_CFG
 */
#define VTSS_CHIP_TOP_CORE_PLL_FREQ_CFG      VTSS_IOREG(VTSS_TO_CHIP_TOP,0x35)

/**
 * \brief
 * This sets the PLL loop filter to work with the post divider reference
 * frequency
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_FREQ_CFG . FILTER_CTRL
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_FREQ_CFG_FILTER_CTRL(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_CHIP_TOP_CORE_PLL_FREQ_CFG_FILTER_CTRL     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_CHIP_TOP_CORE_PLL_FREQ_CFG_FILTER_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \brief
 * Fractional loop divider value. See register description
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_FREQ_CFG . FRACR
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_FREQ_CFG_FRACR(x)  VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_CHIP_TOP_CORE_PLL_FREQ_CFG_FRACR     VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_CHIP_TOP_CORE_PLL_FREQ_CFG_FRACR(x)  VTSS_EXTRACT_BITFIELD(x,16,12)

/**
 * \brief
 * Post scalar divider for output clock. Divide Fvco frequency by QD
 *
 * \details
 * 0: Reserved
 * N: Divide by N
 *
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_FREQ_CFG . QD
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_FREQ_CFG_QD(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_CHIP_TOP_CORE_PLL_FREQ_CFG_QD     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_CHIP_TOP_CORE_PLL_FREQ_CFG_QD(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Integer loop multiplier value. Controls Fvco frequency
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_CORE_PLL_FREQ_CFG . ND
 */
#define  VTSS_F_CHIP_TOP_CORE_PLL_FREQ_CFG_ND(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CHIP_TOP_CORE_PLL_FREQ_CFG_ND     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CHIP_TOP_CORE_PLL_FREQ_CFG_ND(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a CHIP_TOP:RGMII_PLL_CFG
 *
 * CPU PLL configuration
 */


/**
 * \brief CPU PLL configuration
 *
 * \details
 * Register: \a CHIP_TOP:RGMII_PLL_CFG:RGMII_PLL_CFG
 */
#define VTSS_CHIP_TOP_RGMII_PLL_CFG          VTSS_IOREG(VTSS_TO_CHIP_TOP,0x36)

/**
 * \brief
 * Update acknowledge from PLL. Will be low when UPDATE_CFG is low and then
 * toggle high when UPDATE_CFG toggles high.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_RGMII_PLL_CFG . UPDATE_ACK
 */
#define  VTSS_F_CHIP_TOP_RGMII_PLL_CFG_UPDATE_ACK(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_CHIP_TOP_RGMII_PLL_CFG_UPDATE_ACK  VTSS_BIT(7)
#define  VTSS_X_CHIP_TOP_RGMII_PLL_CFG_UPDATE_ACK(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Enable test mode
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_RGMII_PLL_CFG . TEST_ENA
 */
#define  VTSS_F_CHIP_TOP_RGMII_PLL_CFG_TEST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_CHIP_TOP_RGMII_PLL_CFG_TEST_ENA  VTSS_BIT(6)
#define  VTSS_X_CHIP_TOP_RGMII_PLL_CFG_TEST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * This settings is ignored while RGMII_PLL_CFG.ENA_CFG is 0. Bypass PLL
 * and output the reference clock directly. Should not be set in normal
 * operation
 *
 * \details
 * 0: Track reference clock
 * 1: Bypass PLL. Output reference clock directly

 *
 * Field: ::VTSS_CHIP_TOP_RGMII_PLL_CFG . BYPASS_ENA
 */
#define  VTSS_F_CHIP_TOP_RGMII_PLL_CFG_BYPASS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_CHIP_TOP_RGMII_PLL_CFG_BYPASS_ENA  VTSS_BIT(5)
#define  VTSS_X_CHIP_TOP_RGMII_PLL_CFG_BYPASS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Enable PLL clock output
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_RGMII_PLL_CFG . ENABLE_CLOCK
 */
#define  VTSS_F_CHIP_TOP_RGMII_PLL_CFG_ENABLE_CLOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CHIP_TOP_RGMII_PLL_CFG_ENABLE_CLOCK  VTSS_BIT(4)
#define  VTSS_X_CHIP_TOP_RGMII_PLL_CFG_ENABLE_CLOCK(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable PLL
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_RGMII_PLL_CFG . ENABLE_PLL
 */
#define  VTSS_F_CHIP_TOP_RGMII_PLL_CFG_ENABLE_PLL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CHIP_TOP_RGMII_PLL_CFG_ENABLE_PLL  VTSS_BIT(3)
#define  VTSS_X_CHIP_TOP_RGMII_PLL_CFG_ENABLE_PLL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Update signal divider ratio
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_RGMII_PLL_CFG . UPDATE_CFG
 */
#define  VTSS_F_CHIP_TOP_RGMII_PLL_CFG_UPDATE_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CHIP_TOP_RGMII_PLL_CFG_UPDATE_CFG  VTSS_BIT(2)
#define  VTSS_X_CHIP_TOP_RGMII_PLL_CFG_UPDATE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Allow modification of PLL configuration.
 *
 * \details
 * 0: Use fixed configuration
 * 1: Allow modification of ND, QD and FRACR parameters

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
 * This register configures the out frequency of the PLL:
 *
 * Reference clock frequency: Fin
 *
 * Fvco = Fin * (ND + FRACR*2^(-12)). Fvco must be between 750MHz and
 * 1500MHz
 *
 * The PLL output frequency is calculated as:
 * Fout = Fvco / (QD+1)

 *
 * Register: \a CHIP_TOP:RGMII_PLL_CFG:RGMII_PLL_FREQ_CFG
 */
#define VTSS_CHIP_TOP_RGMII_PLL_FREQ_CFG     VTSS_IOREG(VTSS_TO_CHIP_TOP,0x37)

/**
 * \brief
 * This sets the PLL loop filter to work with the post divider reference
 * frequency
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_RGMII_PLL_FREQ_CFG . FILTER_CTRL
 */
#define  VTSS_F_CHIP_TOP_RGMII_PLL_FREQ_CFG_FILTER_CTRL(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_CHIP_TOP_RGMII_PLL_FREQ_CFG_FILTER_CTRL     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_CHIP_TOP_RGMII_PLL_FREQ_CFG_FILTER_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \brief
 * Fractional loop divider value. See register description
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_RGMII_PLL_FREQ_CFG . FRACR
 */
#define  VTSS_F_CHIP_TOP_RGMII_PLL_FREQ_CFG_FRACR(x)  VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_CHIP_TOP_RGMII_PLL_FREQ_CFG_FRACR     VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_CHIP_TOP_RGMII_PLL_FREQ_CFG_FRACR(x)  VTSS_EXTRACT_BITFIELD(x,16,12)

/**
 * \brief
 * Post scalar divider for output clock. Divide Fvco frequency by QD
 *
 * \details
 * 0: Reserved
 * N: Divide by N
 *
 * Field: ::VTSS_CHIP_TOP_RGMII_PLL_FREQ_CFG . QD
 */
#define  VTSS_F_CHIP_TOP_RGMII_PLL_FREQ_CFG_QD(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_CHIP_TOP_RGMII_PLL_FREQ_CFG_QD     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_CHIP_TOP_RGMII_PLL_FREQ_CFG_QD(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Integer loop multiplier value. Controls Fvco frequency
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_RGMII_PLL_FREQ_CFG . ND
 */
#define  VTSS_F_CHIP_TOP_RGMII_PLL_FREQ_CFG_ND(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CHIP_TOP_RGMII_PLL_FREQ_CFG_ND     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CHIP_TOP_RGMII_PLL_FREQ_CFG_ND(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a CHIP_TOP:FX100_PLL_CFG
 *
 * CPU PLL configuration
 */


/**
 * \brief CPU PLL configuration
 *
 * \details
 * Register: \a CHIP_TOP:FX100_PLL_CFG:FX100_PLL_CFG
 */
#define VTSS_CHIP_TOP_FX100_PLL_CFG          VTSS_IOREG(VTSS_TO_CHIP_TOP,0x38)

/**
 * \brief
 * Update acknowledge from PLL. Will be low when UPDATE_CFG is low and then
 * toggle high when UPDATE_CFG toggles high.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_FX100_PLL_CFG . UPDATE_ACK
 */
#define  VTSS_F_CHIP_TOP_FX100_PLL_CFG_UPDATE_ACK(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_CHIP_TOP_FX100_PLL_CFG_UPDATE_ACK  VTSS_BIT(7)
#define  VTSS_X_CHIP_TOP_FX100_PLL_CFG_UPDATE_ACK(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Enable test mode
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_FX100_PLL_CFG . TEST_ENA
 */
#define  VTSS_F_CHIP_TOP_FX100_PLL_CFG_TEST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_CHIP_TOP_FX100_PLL_CFG_TEST_ENA  VTSS_BIT(6)
#define  VTSS_X_CHIP_TOP_FX100_PLL_CFG_TEST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * This settings is ignored while FX100_PLL_CFG.ENA_CFG is 0. Bypass PLL
 * and output the reference clock directly. Should not be set in normal
 * operation
 *
 * \details
 * 0: Track reference clock
 * 1: Bypass PLL. Output reference clock directly

 *
 * Field: ::VTSS_CHIP_TOP_FX100_PLL_CFG . BYPASS_ENA
 */
#define  VTSS_F_CHIP_TOP_FX100_PLL_CFG_BYPASS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_CHIP_TOP_FX100_PLL_CFG_BYPASS_ENA  VTSS_BIT(5)
#define  VTSS_X_CHIP_TOP_FX100_PLL_CFG_BYPASS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Enable PLL clock output
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_FX100_PLL_CFG . ENABLE_CLOCK
 */
#define  VTSS_F_CHIP_TOP_FX100_PLL_CFG_ENABLE_CLOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_CHIP_TOP_FX100_PLL_CFG_ENABLE_CLOCK  VTSS_BIT(4)
#define  VTSS_X_CHIP_TOP_FX100_PLL_CFG_ENABLE_CLOCK(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable PLL
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_FX100_PLL_CFG . ENABLE_PLL
 */
#define  VTSS_F_CHIP_TOP_FX100_PLL_CFG_ENABLE_PLL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CHIP_TOP_FX100_PLL_CFG_ENABLE_PLL  VTSS_BIT(3)
#define  VTSS_X_CHIP_TOP_FX100_PLL_CFG_ENABLE_PLL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Update signal divider ratio
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_FX100_PLL_CFG . UPDATE_CFG
 */
#define  VTSS_F_CHIP_TOP_FX100_PLL_CFG_UPDATE_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CHIP_TOP_FX100_PLL_CFG_UPDATE_CFG  VTSS_BIT(2)
#define  VTSS_X_CHIP_TOP_FX100_PLL_CFG_UPDATE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Allow modification of PLL configuration. All register based PLL setting
 * are ignored while this bit is 0
 *
 * \details
 * 0: Use fixed configuration
 * 1: Allow modification of ND, QD and FRACR parameters

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
 * This register configures the out frequency of the PLL:
 *
 * Reference clock frequency: Fin
 *
 * Fvco = Fin * (ND + FRACR*2^(-12)). Fvco must be between 750MHz and
 * 1500MHz
 *
 * The PLL output frequency is calculated as:
 * Fout = Fvco / (QD+1)

 *
 * Register: \a CHIP_TOP:FX100_PLL_CFG:FX100_PLL_FREQ_CFG
 */
#define VTSS_CHIP_TOP_FX100_PLL_FREQ_CFG     VTSS_IOREG(VTSS_TO_CHIP_TOP,0x39)

/**
 * \brief
 * This sets the PLL loop filter to work with the post divider reference
 * frequency
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_FX100_PLL_FREQ_CFG . FILTER_CTRL
 */
#define  VTSS_F_CHIP_TOP_FX100_PLL_FREQ_CFG_FILTER_CTRL(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_CHIP_TOP_FX100_PLL_FREQ_CFG_FILTER_CTRL     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_CHIP_TOP_FX100_PLL_FREQ_CFG_FILTER_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \brief
 * Fractional loop divider value. See register description
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_FX100_PLL_FREQ_CFG . FRACR
 */
#define  VTSS_F_CHIP_TOP_FX100_PLL_FREQ_CFG_FRACR(x)  VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_CHIP_TOP_FX100_PLL_FREQ_CFG_FRACR     VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_CHIP_TOP_FX100_PLL_FREQ_CFG_FRACR(x)  VTSS_EXTRACT_BITFIELD(x,16,12)

/**
 * \brief
 * Post scalar divider for output clock. Divide Fvco frequency by QD
 *
 * \details
 * 0: Reserved
 * N: Divide by N
 *
 * Field: ::VTSS_CHIP_TOP_FX100_PLL_FREQ_CFG . QD
 */
#define  VTSS_F_CHIP_TOP_FX100_PLL_FREQ_CFG_QD(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_CHIP_TOP_FX100_PLL_FREQ_CFG_QD     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_CHIP_TOP_FX100_PLL_FREQ_CFG_QD(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Integer loop multiplier value. Controls Fvco frequency
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_FX100_PLL_FREQ_CFG . ND
 */
#define  VTSS_F_CHIP_TOP_FX100_PLL_FREQ_CFG_ND(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CHIP_TOP_FX100_PLL_FREQ_CFG_ND     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CHIP_TOP_FX100_PLL_FREQ_CFG_ND(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a CHIP_TOP:SPARE_PLL_CFG
 *
 * Spare PLL configuration
 */


/**
 * \brief CPU PLL configuration
 *
 * \details
 * Register: \a CHIP_TOP:SPARE_PLL_CFG:SPARE_PLL_CFG
 */
#define VTSS_CHIP_TOP_SPARE_PLL_CFG          VTSS_IOREG(VTSS_TO_CHIP_TOP,0x3a)

/**
 * \brief
 * Update acknowledge from PLL. Will be low when UPDATE_CFG is low and then
 * toggle high when UPDAT_CFG toggles high.
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_CFG . UPDATE_ACK
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_CFG_UPDATE_ACK(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_CFG_UPDATE_ACK  VTSS_BIT(11)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_CFG_UPDATE_ACK(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Enable test mode
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_CFG . TEST_ENA
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_CFG_TEST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_CFG_TEST_ENA  VTSS_BIT(10)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_CFG_TEST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * This settings is ignored while SPARE_PLL_CFG.ENA_CFG is 0. Bypass PLL
 * and output the reference clock directly. Should not be set in normal
 * operation
 *
 * \details
 * 0: Track reference clock
 * 1: Bypass PLL. Output reference clock directly

 *
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_CFG . BYPASS_ENA
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_CFG_BYPASS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_CFG_BYPASS_ENA  VTSS_BIT(9)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_CFG_BYPASS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Enable PLL clock output
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_CFG . ENABLE_CLOCK
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_CFG_ENABLE_CLOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_CFG_ENABLE_CLOCK  VTSS_BIT(8)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_CFG_ENABLE_CLOCK(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Enable PLL
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_CFG . ENABLE_PLL
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_CFG_ENABLE_PLL(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_CFG_ENABLE_PLL  VTSS_BIT(7)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_CFG_ENABLE_PLL(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Update signal divider ratio
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_CFG . UPDATE_CFG
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_CFG_UPDATE_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_CFG_UPDATE_CFG  VTSS_BIT(6)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_CFG_UPDATE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

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
#define  VTSS_F_CHIP_TOP_SPARE_PLL_CFG_REF_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_CFG_REF_CLK_SEL     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_CFG_REF_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * Allow modification of PLL configuration. All register based PLL setting
 * are ignored while this bit is 0The spare PLL is unused while
 * ASSIGN_TO_CPU=0 and ASSIGN_TO_CORE=0 and can be reconfigured freely
 * while unused.Frequency change procedure:Reconfigure SPARE_PLL_FREQ_CFG
 * to desired frequencySet ENA_CFG = 1, UPDATE_CFG = 0, ENABLE_PLL = 0 and
 * ENABLE_CLOCK = 0Set ENA_CFG = 1, UPDATE_CFG = 1, ENABLE_PLL = 1 and
 * ENABLE_CLOCK = 1
 *
 * \details
 * 0: Use fixed configuration
 * 1: Allow modification of ND, QD and FRACR parameters

 *
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_CFG . ENA_CFG
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_CFG_ENA_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_CFG_ENA_CFG  VTSS_BIT(3)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_CFG_ENA_CFG(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * When this bit is set, the CPU clock is generated by the SPARE_PLL. The
 * switch over between the CPU- and spare PLLs is glitch free. The Spare
 * PLL is unused and can be reconfigured while this bit is '0'
 *
 * \details
 * 0: Use CPU_PLL to generate CPU clock
 * 1: Use SPARE_PLL to generate CPU clock
 *
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_CFG . ASSIGN_TO_CPU
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_CFG_ASSIGN_TO_CPU(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_CFG_ASSIGN_TO_CPU  VTSS_BIT(2)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_CFG_ASSIGN_TO_CPU(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

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
#define  VTSS_F_CHIP_TOP_SPARE_PLL_CFG_ASSIGN_TO_CORE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_CFG_ASSIGN_TO_CORE  VTSS_BIT(1)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_CFG_ASSIGN_TO_CORE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

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
 * This register configures the out frequency of the PLL:
 *
 * Reference clock frequency: Fin
 *
 * Fvco = Fin * (ND + FRACR*2^(-12)). Fvco must be between 750MHz and
 * 1500MHz
 *
 * The PLL output frequency is calculated as:
 * Fout = Fvco / (QD+1)

 *
 * Register: \a CHIP_TOP:SPARE_PLL_CFG:SPARE_PLL_FREQ_CFG
 */
#define VTSS_CHIP_TOP_SPARE_PLL_FREQ_CFG     VTSS_IOREG(VTSS_TO_CHIP_TOP,0x3b)

/**
 * \brief
 * This sets the PLL loop filter to work with the post divider reference
 * frequency
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_FREQ_CFG . FILTER_CTRL
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_FREQ_CFG_FILTER_CTRL(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_FREQ_CFG_FILTER_CTRL     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_FREQ_CFG_FILTER_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \brief
 * Fractional loop divider value. See register description
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_FREQ_CFG . FRACR
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_FREQ_CFG_FRACR(x)  VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_FREQ_CFG_FRACR     VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_FREQ_CFG_FRACR(x)  VTSS_EXTRACT_BITFIELD(x,16,12)

/**
 * \brief
 * Post scalar divider for output clock. Divide Fvco frequency by QD
 *
 * \details
 * 0: Reserved
 * N: Divide by N
 *
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_FREQ_CFG . QD
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_FREQ_CFG_QD(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_FREQ_CFG_QD     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_FREQ_CFG_QD(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Integer loop multiplier value. Controls Fvco frequency
 *
 * \details
 * Field: ::VTSS_CHIP_TOP_SPARE_PLL_FREQ_CFG . ND
 */
#define  VTSS_F_CHIP_TOP_SPARE_PLL_FREQ_CFG_ND(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CHIP_TOP_SPARE_PLL_FREQ_CFG_ND     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CHIP_TOP_SPARE_PLL_FREQ_CFG_ND(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

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
#define VTSS_CHIP_TOP_TEMP_SENSOR_CTRL       VTSS_IOREG(VTSS_TO_CHIP_TOP,0x3c)

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
#define VTSS_CHIP_TOP_TEMP_SENSOR_CFG        VTSS_IOREG(VTSS_TO_CHIP_TOP,0x3d)

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
#define VTSS_CHIP_TOP_TEMP_SENSOR_STAT       VTSS_IOREG(VTSS_TO_CHIP_TOP,0x3e)

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
