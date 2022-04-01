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
#define VTSS_CPU_INTR_RAW                    VTSS_IOREG(VTSS_TO_CPU,0x0)

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
#define VTSS_CPU_INTR_RAW1                   VTSS_IOREG(VTSS_TO_CPU,0x1)

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
#define VTSS_CPU_INTR_RAW2                   VTSS_IOREG(VTSS_TO_CPU,0x2)

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
 * \brief Interrupt raw status
 *
 * \details
 * Register: \a CPU:INTR:INTR_RAW3
 */
#define VTSS_CPU_INTR_RAW3                   VTSS_IOREG(VTSS_TO_CPU,0x3)

/**
 * \brief
 * Bit 96-127 of field INTR_RAW.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_RAW3 . INTR_RAW3
 */
#define  VTSS_F_CPU_INTR_RAW3_INTR_RAW3(x)    (x)
#define  VTSS_M_CPU_INTR_RAW3_INTR_RAW3       0xffffffff
#define  VTSS_X_CPU_INTR_RAW3_INTR_RAW3(x)    (x)


/**
 * \brief Interrupt trigger mode
 *
 * \details
 * Register: \a CPU:INTR:INTR_TRIGGER
 *
 * @param ri Register: INTR_TRIGGER (??), 0-1
 */
#define VTSS_CPU_INTR_TRIGGER(ri)            VTSS_IOREG(VTSS_TO_CPU,0x4 + (ri))

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
#define VTSS_CPU_INTR_TRIGGER1(ri)           VTSS_IOREG(VTSS_TO_CPU,0x6 + (ri))

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
#define VTSS_CPU_INTR_TRIGGER2(ri)           VTSS_IOREG(VTSS_TO_CPU,0x8 + (ri))

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
 * \brief Interrupt trigger mode
 *
 * \details
 * Register: \a CPU:INTR:INTR_TRIGGER3
 *
 * @param ri Register: INTR_TRIGGER3 (??), 0-1
 */
#define VTSS_CPU_INTR_TRIGGER3(ri)           VTSS_IOREG(VTSS_TO_CPU,0xa + (ri))

/**
 * \brief
 * Bit 96-127 of field INTR_TRIGGER.
 *
 * \details
 * 0: Interrupt is level-activated
 * 1: Interrupt is edge-triggered
 * 2: Interrupt is falling-edge-triggered
 * 3: Interrupt is rising-edge-triggered
 *
 * Field: ::VTSS_CPU_INTR_TRIGGER3 . INTR_TRIGGER3
 */
#define  VTSS_F_CPU_INTR_TRIGGER3_INTR_TRIGGER3(x)  (x)
#define  VTSS_M_CPU_INTR_TRIGGER3_INTR_TRIGGER3     0xffffffff
#define  VTSS_X_CPU_INTR_TRIGGER3_INTR_TRIGGER3(x)  (x)


/**
 * \brief Interrupt force sticky event
 *
 * \details
 * Register: \a CPU:INTR:INTR_FORCE
 */
#define VTSS_CPU_INTR_FORCE                  VTSS_IOREG(VTSS_TO_CPU,0xc)

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
#define VTSS_CPU_INTR_FORCE1                 VTSS_IOREG(VTSS_TO_CPU,0xd)

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
#define VTSS_CPU_INTR_FORCE2                 VTSS_IOREG(VTSS_TO_CPU,0xe)

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
 * \brief Interrupt force sticky event
 *
 * \details
 * Register: \a CPU:INTR:INTR_FORCE3
 */
#define VTSS_CPU_INTR_FORCE3                 VTSS_IOREG(VTSS_TO_CPU,0xf)

/**
 * \brief
 * Bit 96-127 of field INTR_FORCE.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_FORCE3 . INTR_FORCE3
 */
#define  VTSS_F_CPU_INTR_FORCE3_INTR_FORCE3(x)  (x)
#define  VTSS_M_CPU_INTR_FORCE3_INTR_FORCE3     0xffffffff
#define  VTSS_X_CPU_INTR_FORCE3_INTR_FORCE3(x)  (x)


/**
 * \brief Interrupt sticky status
 *
 * \details
 * Register: \a CPU:INTR:INTR_STICKY
 */
#define VTSS_CPU_INTR_STICKY                 VTSS_IOREG(VTSS_TO_CPU,0x10)

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
#define VTSS_CPU_INTR_STICKY1                VTSS_IOREG(VTSS_TO_CPU,0x11)

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
#define VTSS_CPU_INTR_STICKY2                VTSS_IOREG(VTSS_TO_CPU,0x12)

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
 * \brief Interrupt sticky status
 *
 * \details
 * Register: \a CPU:INTR:INTR_STICKY3
 */
#define VTSS_CPU_INTR_STICKY3                VTSS_IOREG(VTSS_TO_CPU,0x13)

/**
 * \brief
 * Bit 96-127 of field INTR_STICKY.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_STICKY3 . INTR_STICKY3
 */
#define  VTSS_F_CPU_INTR_STICKY3_INTR_STICKY3(x)  (x)
#define  VTSS_M_CPU_INTR_STICKY3_INTR_STICKY3     0xffffffff
#define  VTSS_X_CPU_INTR_STICKY3_INTR_STICKY3(x)  (x)


/**
 * \brief Interrupt bypass enable
 *
 * \details
 * Register: \a CPU:INTR:INTR_BYPASS
 */
#define VTSS_CPU_INTR_BYPASS                 VTSS_IOREG(VTSS_TO_CPU,0x14)

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
#define VTSS_CPU_INTR_BYPASS1                VTSS_IOREG(VTSS_TO_CPU,0x15)

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
#define VTSS_CPU_INTR_BYPASS2                VTSS_IOREG(VTSS_TO_CPU,0x16)

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
 * \brief Interrupt bypass enable
 *
 * \details
 * Register: \a CPU:INTR:INTR_BYPASS3
 */
#define VTSS_CPU_INTR_BYPASS3                VTSS_IOREG(VTSS_TO_CPU,0x17)

/**
 * \brief
 * Bit 96-127 of field INTR_BYPASS.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_BYPASS3 . INTR_BYPASS3
 */
#define  VTSS_F_CPU_INTR_BYPASS3_INTR_BYPASS3(x)  (x)
#define  VTSS_M_CPU_INTR_BYPASS3_INTR_BYPASS3     0xffffffff
#define  VTSS_X_CPU_INTR_BYPASS3_INTR_BYPASS3(x)  (x)


/**
 * \brief Interrupt enable
 *
 * \details
 * Register: \a CPU:INTR:INTR_ENA
 */
#define VTSS_CPU_INTR_ENA                    VTSS_IOREG(VTSS_TO_CPU,0x18)

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
#define VTSS_CPU_INTR_ENA1                   VTSS_IOREG(VTSS_TO_CPU,0x19)

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
#define VTSS_CPU_INTR_ENA2                   VTSS_IOREG(VTSS_TO_CPU,0x1a)

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
 * \brief Interrupt enable
 *
 * \details
 * Register: \a CPU:INTR:INTR_ENA3
 */
#define VTSS_CPU_INTR_ENA3                   VTSS_IOREG(VTSS_TO_CPU,0x1b)

/**
 * \brief
 * Bit 96-127 of field INTR_ENA.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_ENA3 . INTR_ENA3
 */
#define  VTSS_F_CPU_INTR_ENA3_INTR_ENA3(x)    (x)
#define  VTSS_M_CPU_INTR_ENA3_INTR_ENA3       0xffffffff
#define  VTSS_X_CPU_INTR_ENA3_INTR_ENA3(x)    (x)


/**
 * \brief Atomic clear of interrupt enable
 *
 * \details
 * Register: \a CPU:INTR:INTR_ENA_CLR
 */
#define VTSS_CPU_INTR_ENA_CLR                VTSS_IOREG(VTSS_TO_CPU,0x1c)

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
#define VTSS_CPU_INTR_ENA_CLR1               VTSS_IOREG(VTSS_TO_CPU,0x1d)

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
#define VTSS_CPU_INTR_ENA_CLR2               VTSS_IOREG(VTSS_TO_CPU,0x1e)

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
 * \brief Atomic clear of interrupt enable
 *
 * \details
 * Register: \a CPU:INTR:INTR_ENA_CLR3
 */
#define VTSS_CPU_INTR_ENA_CLR3               VTSS_IOREG(VTSS_TO_CPU,0x1f)

/**
 * \brief
 * Bit 96-127 of field INTR_ENA_CLR.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_ENA_CLR3 . INTR_ENA_CLR3
 */
#define  VTSS_F_CPU_INTR_ENA_CLR3_INTR_ENA_CLR3(x)  (x)
#define  VTSS_M_CPU_INTR_ENA_CLR3_INTR_ENA_CLR3     0xffffffff
#define  VTSS_X_CPU_INTR_ENA_CLR3_INTR_ENA_CLR3(x)  (x)


/**
 * \brief Atomic set of interrupt
 *
 * \details
 * Register: \a CPU:INTR:INTR_ENA_SET
 */
#define VTSS_CPU_INTR_ENA_SET                VTSS_IOREG(VTSS_TO_CPU,0x20)

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
#define VTSS_CPU_INTR_ENA_SET1               VTSS_IOREG(VTSS_TO_CPU,0x21)

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
#define VTSS_CPU_INTR_ENA_SET2               VTSS_IOREG(VTSS_TO_CPU,0x22)

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
 * \brief Atomic set of interrupt
 *
 * \details
 * Register: \a CPU:INTR:INTR_ENA_SET3
 */
#define VTSS_CPU_INTR_ENA_SET3               VTSS_IOREG(VTSS_TO_CPU,0x23)

/**
 * \brief
 * Bit 96-127 of field INTR_ENA_SET.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_ENA_SET3 . INTR_ENA_SET3
 */
#define  VTSS_F_CPU_INTR_ENA_SET3_INTR_ENA_SET3(x)  (x)
#define  VTSS_M_CPU_INTR_ENA_SET3_INTR_ENA_SET3     0xffffffff
#define  VTSS_X_CPU_INTR_ENA_SET3_INTR_ENA_SET3(x)  (x)


/**
 * \brief Currently active interrupt sources
 *
 * \details
 * Register: \a CPU:INTR:INTR_IDENT
 */
#define VTSS_CPU_INTR_IDENT                  VTSS_IOREG(VTSS_TO_CPU,0x24)

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
#define VTSS_CPU_INTR_IDENT1                 VTSS_IOREG(VTSS_TO_CPU,0x25)

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
#define VTSS_CPU_INTR_IDENT2                 VTSS_IOREG(VTSS_TO_CPU,0x26)

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
 * \brief Currently active interrupt sources
 *
 * \details
 * Register: \a CPU:INTR:INTR_IDENT3
 */
#define VTSS_CPU_INTR_IDENT3                 VTSS_IOREG(VTSS_TO_CPU,0x27)

/**
 * \brief
 * Bit 96-127 of field INTR_IDENT.
 *
 * \details
 * Field: ::VTSS_CPU_INTR_IDENT3 . INTR_IDENT3
 */
#define  VTSS_F_CPU_INTR_IDENT3_INTR_IDENT3(x)  (x)
#define  VTSS_M_CPU_INTR_IDENT3_INTR_IDENT3     0xffffffff
#define  VTSS_X_CPU_INTR_IDENT3_INTR_IDENT3(x)  (x)


/**
 * \brief Mapping of source to destination interrupts
 *
 * \details
 * Replicated per destination interrupt.
 *
 * Register: \a CPU:INTR:DST_INTR_MAP
 *
 * @param ri Replicator: x_VCORE5_INTR_DST_CNT (??), 0-6
 */
#define VTSS_CPU_DST_INTR_MAP(ri)            VTSS_IOREG(VTSS_TO_CPU,0x28 + (ri))

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
 * @param ri Replicator: x_VCORE5_INTR_DST_CNT (??), 0-6
 */
#define VTSS_CPU_DST_INTR_MAP1(ri)           VTSS_IOREG(VTSS_TO_CPU,0x2f + (ri))

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
 * @param ri Replicator: x_VCORE5_INTR_DST_CNT (??), 0-6
 */
#define VTSS_CPU_DST_INTR_MAP2(ri)           VTSS_IOREG(VTSS_TO_CPU,0x36 + (ri))

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
 * \brief Mapping of source to destination interrupts
 *
 * \details
 * Replicated per destination interrupt.
 *
 * Register: \a CPU:INTR:DST_INTR_MAP3
 *
 * @param ri Replicator: x_VCORE5_INTR_DST_CNT (??), 0-6
 */
#define VTSS_CPU_DST_INTR_MAP3(ri)           VTSS_IOREG(VTSS_TO_CPU,0x3d + (ri))

/**
 * \brief
 * Bit 96-127 of field DST_INTR_MAP.
 *
 * \details
 * Field: ::VTSS_CPU_DST_INTR_MAP3 . DST_INTR_MAP3
 */
#define  VTSS_F_CPU_DST_INTR_MAP3_DST_INTR_MAP3(x)  (x)
#define  VTSS_M_CPU_DST_INTR_MAP3_DST_INTR_MAP3     0xffffffff
#define  VTSS_X_CPU_DST_INTR_MAP3_DST_INTR_MAP3(x)  (x)


/**
 * \brief Currently active interrupt sources per destination
 *
 * \details
 * Replicated per destination interrupt.
 *
 * Register: \a CPU:INTR:DST_INTR_IDENT
 *
 * @param ri Replicator: x_VCORE5_INTR_DST_CNT (??), 0-6
 */
#define VTSS_CPU_DST_INTR_IDENT(ri)          VTSS_IOREG(VTSS_TO_CPU,0x44 + (ri))

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
 * @param ri Replicator: x_VCORE5_INTR_DST_CNT (??), 0-6
 */
#define VTSS_CPU_DST_INTR_IDENT1(ri)         VTSS_IOREG(VTSS_TO_CPU,0x4b + (ri))

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
 * @param ri Replicator: x_VCORE5_INTR_DST_CNT (??), 0-6
 */
#define VTSS_CPU_DST_INTR_IDENT2(ri)         VTSS_IOREG(VTSS_TO_CPU,0x52 + (ri))

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
 * \brief Currently active interrupt sources per destination
 *
 * \details
 * Replicated per destination interrupt.
 *
 * Register: \a CPU:INTR:DST_INTR_IDENT3
 *
 * @param ri Replicator: x_VCORE5_INTR_DST_CNT (??), 0-6
 */
#define VTSS_CPU_DST_INTR_IDENT3(ri)         VTSS_IOREG(VTSS_TO_CPU,0x59 + (ri))

/**
 * \brief
 * Bit 96-127 of field DST_INTR_IDENT.
 *
 * \details
 * Field: ::VTSS_CPU_DST_INTR_IDENT3 . DST_INTR_IDENT3
 */
#define  VTSS_F_CPU_DST_INTR_IDENT3_DST_INTR_IDENT3(x)  (x)
#define  VTSS_M_CPU_DST_INTR_IDENT3_DST_INTR_IDENT3     0xffffffff
#define  VTSS_X_CPU_DST_INTR_IDENT3_DST_INTR_IDENT3(x)  (x)


/**
 * \brief External source interrupt polarity
 *
 * \details
 * Register: \a CPU:INTR:EXT_SRC_INTR_POL
 */
#define VTSS_CPU_EXT_SRC_INTR_POL            VTSS_IOREG(VTSS_TO_CPU,0x60)

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
#define  VTSS_F_CPU_EXT_SRC_INTR_POL_EXT_SRC_INTR_POL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CPU_EXT_SRC_INTR_POL_EXT_SRC_INTR_POL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CPU_EXT_SRC_INTR_POL_EXT_SRC_INTR_POL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief External destination interrupt polarity
 *
 * \details
 * Register: \a CPU:INTR:EXT_DST_INTR_POL
 */
#define VTSS_CPU_EXT_DST_INTR_POL            VTSS_IOREG(VTSS_TO_CPU,0x61)

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
#define  VTSS_F_CPU_EXT_DST_INTR_POL_EXT_DST_INTR_POL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CPU_EXT_DST_INTR_POL_EXT_DST_INTR_POL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CPU_EXT_DST_INTR_POL_EXT_DST_INTR_POL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief External interrupt destination output drive mode
 *
 * \details
 * Register: \a CPU:INTR:EXT_DST_INTR_DRV
 */
#define VTSS_CPU_EXT_DST_INTR_DRV            VTSS_IOREG(VTSS_TO_CPU,0x62)

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
#define  VTSS_F_CPU_EXT_DST_INTR_DRV_EXT_DST_INTR_DRV(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CPU_EXT_DST_INTR_DRV_EXT_DST_INTR_DRV     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CPU_EXT_DST_INTR_DRV_EXT_DST_INTR_DRV(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief Device interrupt polarity
 *
 * \details
 * Register: \a CPU:INTR:DEV_INTR_POL
 */
#define VTSS_CPU_DEV_INTR_POL                VTSS_IOREG(VTSS_TO_CPU,0x63)

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
#define VTSS_CPU_DEV_INTR_RAW                VTSS_IOREG(VTSS_TO_CPU,0x64)

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
#define VTSS_CPU_DEV_INTR_TRIGGER(ri)        VTSS_IOREG(VTSS_TO_CPU,0x65 + (ri))

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
#define VTSS_CPU_DEV_INTR_STICKY             VTSS_IOREG(VTSS_TO_CPU,0x67)

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
#define VTSS_CPU_DEV_INTR_BYPASS             VTSS_IOREG(VTSS_TO_CPU,0x68)

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
#define VTSS_CPU_DEV_INTR_ENA                VTSS_IOREG(VTSS_TO_CPU,0x69)

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
#define VTSS_CPU_DEV_INTR_IDENT              VTSS_IOREG(VTSS_TO_CPU,0x6a)

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
#define VTSS_CPU_MSIX_CFG                    VTSS_IOREG(VTSS_TO_CPU,0x6b)

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
#define VTSS_CPU_MSIX_DOORBELL_ADDR          VTSS_IOREG(VTSS_TO_CPU,0x6c)

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
#define VTSS_CPU_MSIX_INTR_PENDING           VTSS_IOREG(VTSS_TO_CPU,0x6d)

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
#define VTSS_CPU_MSIX_INTR_PENDING1          VTSS_IOREG(VTSS_TO_CPU,0x6e)

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
#define VTSS_CPU_MSIX_INTR_PENDING2          VTSS_IOREG(VTSS_TO_CPU,0x6f)

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
 * \brief MSI-X interrupt pending
 *
 * \details
 * Register: \a CPU:INTR:MSIX_INTR_PENDING3
 */
#define VTSS_CPU_MSIX_INTR_PENDING3          VTSS_IOREG(VTSS_TO_CPU,0x70)

/**
 * \brief
 * Bit 96-127 of field MSIX_INTR_PENDING.
 *
 * \details
 * Field: ::VTSS_CPU_MSIX_INTR_PENDING3 . MSIX_INTR_PENDING3
 */
#define  VTSS_F_CPU_MSIX_INTR_PENDING3_MSIX_INTR_PENDING3(x)  (x)
#define  VTSS_M_CPU_MSIX_INTR_PENDING3_MSIX_INTR_PENDING3     0xffffffff
#define  VTSS_X_CPU_MSIX_INTR_PENDING3_MSIX_INTR_PENDING3(x)  (x)


#endif /* _VTSS_LAGUNA_REGS_CPU_H_ */
