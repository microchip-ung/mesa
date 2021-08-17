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

#ifndef _VTSS_LAGUNA_REGS_HMATRIX2_H_
#define _VTSS_LAGUNA_REGS_HMATRIX2_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a HMATRIX2
 *
 * AHB Bus Matrix (MATRIX) User Interface
 *
 ***********************************************************************/

/**
 * Register Group: \a HMATRIX2:HMATRIX2_REGS
 *
 * Not documented
 */


/**
 * \brief Bus Matrix Initiator Configuration Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MCFG0
 */
#define VTSS_HMATRIX2_MATRIX_MCFG0           VTSS_IOREG(VTSS_TO_HMATRIX2,0x0)

/**
 * \brief
 * ULBT: Undefined Length Burst Type
 *
 * \details
 * 0 UNLIMITED
 * Unlimited Length Burst : No predicted end of burst is generated,
 * therefore INCR bursts coming from this
 * initiator can only be broken if the Target Slot Cycle Limit is reached.
 * If the Slot Cycle Limit is not reached, the
 * burst is normally completed by the initiator, at the latest, on the next
 * AHB 1 Kbyte address boundary, allowing
 * up to 256-beat word bursts or 128-beat double-word bursts.
 * This value should not be used in the very particular case of a initiator
 * capable of performing back-to-back
 * undefined length bursts on a single target, since this could
 * indefinitely freeze the target arbitration and thus
 * prevent another initiator from accessing this target.
 * 1 SINGLE
 * Single Access The undefined length burst is treated as a succession of
 * single accesses, allowing rearbitration
 * at each beat of the INCR burst or bursts sequence.
 * 2 4_BEAT
 * 4-beat Burst The undefined length burst or bursts sequence is split into
 * 4-beat bursts or less, allowing rearbitration
 * every 4 beats.
 * 3 8_BEAT
 * 8-beat Burst The undefined length burst or bursts sequence is split into
 * 8-beat bursts or less, allowing rearbitration
 * every 8 beats.
 * 4 16_BEAT
 * 16-beat Burst The undefined length burst or bursts sequence is split
 * into 16-beat bursts or less, allowing rearbitration
 * every 16 beats.
 * 5 32_BEAT
 * 32-beat Burst The undefined length burst or bursts sequence is split
 * into 32-beat bursts or less, allowing rearbitration
 * every 32 beats.
 * 6 64_BEAT
 * 64-beat Burst The undefined length burst or bursts sequence is split
 * into 64-beat bursts or less, allowing rearbitration
 * every 64 beats.
 * 7 128_BEAT
 * 128-beat Burst The undefined length burst or bursts sequence is split
 * into 128-beat bursts or less, allowing
 * re-arbitration every 128 beats.
 * Unless duly needed, the ULBT should be left at its default 0 value for
 * power saving.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_MCFG0 . ULBT0
 */
#define  VTSS_F_HMATRIX2_MATRIX_MCFG0_ULBT0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_HMATRIX2_MATRIX_MCFG0_ULBT0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_HMATRIX2_MATRIX_MCFG0_ULBT0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Bus Matrix Initiator Configuration Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MCFG1
 */
#define VTSS_HMATRIX2_MATRIX_MCFG1           VTSS_IOREG(VTSS_TO_HMATRIX2,0x1)

/**
 * \brief
 * ULBT: Undefined Length Burst Type
 *
 * \details
 * 0 UNLIMITED
 * Unlimited Length Burst—No predicted end of burst is generated, therefore
 * INCR bursts coming from this
 * initiator can only be broken if the Target Slot Cycle Limit is reached.
 * If the Slot Cycle Limit is not reached, the
 * burst is normally completed by the initiator, at the latest, on the next
 * AHB 1 Kbyte address boundary, allowing
 * up to 256-beat word bursts or 128-beat double-word bursts.
 * This value should not be used in the very particular case of a initiator
 * capable of performing back-to-back
 * undefined length bursts on a single target, since this could
 * indefinitely freeze the target arbitration and thus
 * prevent another initiator from accessing this target.
 * 1 SINGLE
 * Single Access The undefined length burst is treated as a succession of
 * single accesses, allowing rearbitration
 * at each beat of the INCR burst or bursts sequence.
 * 2 4_BEAT
 * 4-beat Burst The undefined length burst or bursts sequence is split into
 * 4-beat bursts or less, allowing rearbitration
 * every 4 beats.
 * 3 8_BEAT
 * 8-beat Burst The undefined length burst or bursts sequence is split into
 * 8-beat bursts or less, allowing rearbitration
 * every 8 beats.
 * 4 16_BEAT
 * 16-beat Burst The undefined length burst or bursts sequence is split
 * into 16-beat bursts or less, allowing rearbitration
 * every 16 beats.
 * 5 32_BEAT
 * 32-beat Burst The undefined length burst or bursts sequence is split
 * into 32-beat bursts or less, allowing rearbitration
 * every 32 beats.
 * 6 64_BEAT
 * 64-beat Burst The undefined length burst or bursts sequence is split
 * into 64-beat bursts or less, allowing rearbitration
 * every 64 beats.
 * 7 128_BEAT
 * 128-beat Burst The undefined length burst or bursts sequence is split
 * into 128-beat bursts or less, allowing
 * re-arbitration every 128 beats.
 * Unless duly needed, the ULBT should be left at its default 0 value for
 * power saving.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_MCFG1 . ULBT1
 */
#define  VTSS_F_HMATRIX2_MATRIX_MCFG1_ULBT1(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_HMATRIX2_MATRIX_MCFG1_ULBT1     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_HMATRIX2_MATRIX_MCFG1_ULBT1(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Bus Matrix Initiator Configuration Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MCFG2
 */
#define VTSS_HMATRIX2_MATRIX_MCFG2           VTSS_IOREG(VTSS_TO_HMATRIX2,0x2)

/**
 * \brief
 * ULBT: Undefined Length Burst Type
 *
 * \details
 * 0 UNLIMITED
 * Unlimited Length Burst—No predicted end of burst is generated, therefore
 * INCR bursts coming from this
 * initiator can only be broken if the Target Slot Cycle Limit is reached.
 * If the Slot Cycle Limit is not reached, the
 * burst is normally completed by the initiator, at the latest, on the next
 * AHB 1 Kbyte address boundary, allowing
 * up to 256-beat word bursts or 128-beat double-word bursts.
 * This value should not be used in the very particular case of a initiator
 * capable of performing back-to-back
 * undefined length bursts on a single target, since this could
 * indefinitely freeze the target arbitration and thus
 * prevent another initiator from accessing this target.
 * 1 SINGLE
 * Single Access The undefined length burst is treated as a succession of
 * single accesses, allowing rearbitration
 * at each beat of the INCR burst or bursts sequence.
 * 2 4_BEAT
 * 4-beat Burst The undefined length burst or bursts sequence is split into
 * 4-beat bursts or less, allowing rearbitration
 * every 4 beats.
 * 3 8_BEAT
 * 8-beat Burst The undefined length burst or bursts sequence is split into
 * 8-beat bursts or less, allowing rearbitration
 * every 8 beats.
 * 4 16_BEAT
 * 16-beat Burst The undefined length burst or bursts sequence is split
 * into 16-beat bursts or less, allowing rearbitration
 * every 16 beats.
 * 5 32_BEAT
 * 32-beat Burst The undefined length burst or bursts sequence is split
 * into 32-beat bursts or less, allowing rearbitration
 * every 32 beats.
 * 6 64_BEAT
 * 64-beat Burst The undefined length burst or bursts sequence is split
 * into 64-beat bursts or less, allowing rearbitration
 * every 64 beats.
 * 7 128_BEAT
 * 128-beat Burst The undefined length burst or bursts sequence is split
 * into 128-beat bursts or less, allowing
 * re-arbitration every 128 beats.
 * Unless duly needed, the ULBT should be left at its default 0 value for
 * power saving.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_MCFG2 . ULBT2
 */
#define  VTSS_F_HMATRIX2_MATRIX_MCFG2_ULBT2(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_HMATRIX2_MATRIX_MCFG2_ULBT2     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_HMATRIX2_MATRIX_MCFG2_ULBT2(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Bus Matrix Initiator Configuration Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MCFG3
 */
#define VTSS_HMATRIX2_MATRIX_MCFG3           VTSS_IOREG(VTSS_TO_HMATRIX2,0x3)

/**
 * \brief
 * ULBT: Undefined Length Burst Type
 *
 * \details
 * 0 UNLIMITED
 * Unlimited Length Burst—No predicted end of burst is generated, therefore
 * INCR bursts coming from this
 * initiator can only be broken if the Target Slot Cycle Limit is reached.
 * If the Slot Cycle Limit is not reached, the
 * burst is normally completed by the initiator, at the latest, on the next
 * AHB 1 Kbyte address boundary, allowing
 * up to 256-beat word bursts or 128-beat double-word bursts.
 * This value should not be used in the very particular case of a initiator
 * capable of performing back-to-back
 * undefined length bursts on a single target, since this could
 * indefinitely freeze the target arbitration and thus
 * prevent another initiator from accessing this target.
 * 1 SINGLE
 * Single Access The undefined length burst is treated as a succession of
 * single accesses, allowing rearbitration
 * at each beat of the INCR burst or bursts sequence.
 * 2 4_BEAT
 * 4-beat Burst The undefined length burst or bursts sequence is split into
 * 4-beat bursts or less, allowing rearbitration
 * every 4 beats.
 * 3 8_BEAT
 * 8-beat Burst The undefined length burst or bursts sequence is split into
 * 8-beat bursts or less, allowing rearbitration
 * every 8 beats.
 * 4 16_BEAT
 * 16-beat Burst The undefined length burst or bursts sequence is split
 * into 16-beat bursts or less, allowing rearbitration
 * every 16 beats.
 * 5 32_BEAT
 * 32-beat Burst The undefined length burst or bursts sequence is split
 * into 32-beat bursts or less, allowing rearbitration
 * every 32 beats.
 * 6 64_BEAT
 * 64-beat Burst The undefined length burst or bursts sequence is split
 * into 64-beat bursts or less, allowing rearbitration
 * every 64 beats.
 * 7 128_BEAT
 * 128-beat Burst The undefined length burst or bursts sequence is split
 * into 128-beat bursts or less, allowing
 * re-arbitration every 128 beats.
 * Unless duly needed, the ULBT should be left at its default 0 value for
 * power saving.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_MCFG3 . ULBT3
 */
#define  VTSS_F_HMATRIX2_MATRIX_MCFG3_ULBT3(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_HMATRIX2_MATRIX_MCFG3_ULBT3     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_HMATRIX2_MATRIX_MCFG3_ULBT3(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Bus Matrix Initiator Configuration Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MCFG4
 */
#define VTSS_HMATRIX2_MATRIX_MCFG4           VTSS_IOREG(VTSS_TO_HMATRIX2,0x4)

/**
 * \brief
 * ULBT: Undefined Length Burst Type
 *
 * \details
 * 0 UNLIMITED
 * Unlimited Length Burst—No predicted end of burst is generated, therefore
 * INCR bursts coming from this
 * initiator can only be broken if the Target Slot Cycle Limit is reached.
 * If the Slot Cycle Limit is not reached, the
 * burst is normally completed by the initiator, at the latest, on the next
 * AHB 1 Kbyte address boundary, allowing
 * up to 256-beat word bursts or 128-beat double-word bursts.
 * This value should not be used in the very particular case of a initiator
 * capable of performing back-to-back
 * undefined length bursts on a single target, since this could
 * indefinitely freeze the target arbitration and thus
 * prevent another initiator from accessing this target.
 * 1 SINGLE
 * Single Access The undefined length burst is treated as a succession of
 * single accesses, allowing rearbitration
 * at each beat of the INCR burst or bursts sequence.
 * 2 4_BEAT
 * 4-beat Burst The undefined length burst or bursts sequence is split into
 * 4-beat bursts or less, allowing rearbitration
 * every 4 beats.
 * 3 8_BEAT
 * 8-beat Burst The undefined length burst or bursts sequence is split into
 * 8-beat bursts or less, allowing rearbitration
 * every 8 beats.
 * 4 16_BEAT
 * 16-beat Burst The undefined length burst or bursts sequence is split
 * into 16-beat bursts or less, allowing rearbitration
 * every 16 beats.
 * 5 32_BEAT
 * 32-beat Burst The undefined length burst or bursts sequence is split
 * into 32-beat bursts or less, allowing rearbitration
 * every 32 beats.
 * 6 64_BEAT
 * 64-beat Burst The undefined length burst or bursts sequence is split
 * into 64-beat bursts or less, allowing rearbitration
 * every 64 beats.
 * 7 128_BEAT
 * 128-beat Burst The undefined length burst or bursts sequence is split
 * into 128-beat bursts or less, allowing
 * re-arbitration every 128 beats.
 * Unless duly needed, the ULBT should be left at its default 0 value for
 * power saving.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_MCFG4 . ULBT4
 */
#define  VTSS_F_HMATRIX2_MATRIX_MCFG4_ULBT4(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_HMATRIX2_MATRIX_MCFG4_ULBT4     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_HMATRIX2_MATRIX_MCFG4_ULBT4(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Bus Matrix Initiator Configuration Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MCFG5
 */
#define VTSS_HMATRIX2_MATRIX_MCFG5           VTSS_IOREG(VTSS_TO_HMATRIX2,0x5)

/**
 * \brief
 * ULBT: Undefined Length Burst Type
 *
 * \details
 * 0 UNLIMITED
 * Unlimited Length Burst—No predicted end of burst is generated, therefore
 * INCR bursts coming from this
 * initiator can only be broken if the Target Slot Cycle Limit is reached.
 * If the Slot Cycle Limit is not reached, the
 * burst is normally completed by the initiator, at the latest, on the next
 * AHB 1 Kbyte address boundary, allowing
 * up to 256-beat word bursts or 128-beat double-word bursts.
 * This value should not be used in the very particular case of a initiator
 * capable of performing back-to-back
 * undefined length bursts on a single target, since this could
 * indefinitely freeze the target arbitration and thus
 * prevent another initiator from accessing this target.
 * 1 SINGLE
 * Single Access The undefined length burst is treated as a succession of
 * single accesses, allowing rearbitration
 * at each beat of the INCR burst or bursts sequence.
 * 2 4_BEAT
 * 4-beat Burst The undefined length burst or bursts sequence is split into
 * 4-beat bursts or less, allowing rearbitration
 * every 4 beats.
 * 3 8_BEAT
 * 8-beat Burst The undefined length burst or bursts sequence is split into
 * 8-beat bursts or less, allowing rearbitration
 * every 8 beats.
 * 4 16_BEAT
 * 16-beat Burst The undefined length burst or bursts sequence is split
 * into 16-beat bursts or less, allowing rearbitration
 * every 16 beats.
 * 5 32_BEAT
 * 32-beat Burst The undefined length burst or bursts sequence is split
 * into 32-beat bursts or less, allowing rearbitration
 * every 32 beats.
 * 6 64_BEAT
 * 64-beat Burst The undefined length burst or bursts sequence is split
 * into 64-beat bursts or less, allowing rearbitration
 * every 64 beats.
 * 7 128_BEAT
 * 128-beat Burst The undefined length burst or bursts sequence is split
 * into 128-beat bursts or less, allowing
 * re-arbitration every 128 beats.
 * Unless duly needed, the ULBT should be left at its default 0 value for
 * power saving.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_MCFG5 . ULBT5
 */
#define  VTSS_F_HMATRIX2_MATRIX_MCFG5_ULBT5(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_HMATRIX2_MATRIX_MCFG5_ULBT5     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_HMATRIX2_MATRIX_MCFG5_ULBT5(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Bus Matrix Initiator Configuration Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MCFG6
 */
#define VTSS_HMATRIX2_MATRIX_MCFG6           VTSS_IOREG(VTSS_TO_HMATRIX2,0x6)

/**
 * \brief
 * ULBT: Undefined Length Burst Type
 *
 * \details
 * 0 UNLIMITED
 * Unlimited Length Burst—No predicted end of burst is generated, therefore
 * INCR bursts coming from this
 * initiator can only be broken if the Target Slot Cycle Limit is reached.
 * If the Slot Cycle Limit is not reached, the
 * burst is normally completed by the initiator, at the latest, on the next
 * AHB 1 Kbyte address boundary, allowing
 * up to 256-beat word bursts or 128-beat double-word bursts.
 * This value should not be used in the very particular case of a initiator
 * capable of performing back-to-back
 * undefined length bursts on a single target, since this could
 * indefinitely freeze the target arbitration and thus
 * prevent another initiator from accessing this target.
 * 1 SINGLE
 * Single Access The undefined length burst is treated as a succession of
 * single accesses, allowing rearbitration
 * at each beat of the INCR burst or bursts sequence.
 * 2 4_BEAT
 * 4-beat Burst The undefined length burst or bursts sequence is split into
 * 4-beat bursts or less, allowing rearbitration
 * every 4 beats.
 * 3 8_BEAT
 * 8-beat Burst The undefined length burst or bursts sequence is split into
 * 8-beat bursts or less, allowing rearbitration
 * every 8 beats.
 * 4 16_BEAT
 * 16-beat Burst The undefined length burst or bursts sequence is split
 * into 16-beat bursts or less, allowing rearbitration
 * every 16 beats.
 * 5 32_BEAT
 * 32-beat Burst The undefined length burst or bursts sequence is split
 * into 32-beat bursts or less, allowing rearbitration
 * every 32 beats.
 * 6 64_BEAT
 * 64-beat Burst The undefined length burst or bursts sequence is split
 * into 64-beat bursts or less, allowing rearbitration
 * every 64 beats.
 * 7 128_BEAT
 * 128-beat Burst The undefined length burst or bursts sequence is split
 * into 128-beat bursts or less, allowing
 * re-arbitration every 128 beats.
 * Unless duly needed, the ULBT should be left at its default 0 value for
 * power saving.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_MCFG6 . ULBT6
 */
#define  VTSS_F_HMATRIX2_MATRIX_MCFG6_ULBT6(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_HMATRIX2_MATRIX_MCFG6_ULBT6     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_HMATRIX2_MATRIX_MCFG6_ULBT6(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Bus Matrix Initiator Configuration Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MCFG7
 */
#define VTSS_HMATRIX2_MATRIX_MCFG7           VTSS_IOREG(VTSS_TO_HMATRIX2,0x7)

/**
 * \brief
 * ULBT: Undefined Length Burst Type
 *
 * \details
 * 0 UNLIMITED
 * Unlimited Length Burst—No predicted end of burst is generated, therefore
 * INCR bursts coming from this
 * initiator can only be broken if the Target Slot Cycle Limit is reached.
 * If the Slot Cycle Limit is not reached, the
 * burst is normally completed by the initiator, at the latest, on the next
 * AHB 1 Kbyte address boundary, allowing
 * up to 256-beat word bursts or 128-beat double-word bursts.
 * This value should not be used in the very particular case of a initiator
 * capable of performing back-to-back
 * undefined length bursts on a single target, since this could
 * indefinitely freeze the target arbitration and thus
 * prevent another initiator from accessing this target.
 * 1 SINGLE
 * Single Access The undefined length burst is treated as a succession of
 * single accesses, allowing rearbitration
 * at each beat of the INCR burst or bursts sequence.
 * 2 4_BEAT
 * 4-beat Burst The undefined length burst or bursts sequence is split into
 * 4-beat bursts or less, allowing rearbitration
 * every 4 beats.
 * 3 8_BEAT
 * 8-beat Burst The undefined length burst or bursts sequence is split into
 * 8-beat bursts or less, allowing rearbitration
 * every 8 beats.
 * 4 16_BEAT
 * 16-beat Burst The undefined length burst or bursts sequence is split
 * into 16-beat bursts or less, allowing rearbitration
 * every 16 beats.
 * 5 32_BEAT
 * 32-beat Burst The undefined length burst or bursts sequence is split
 * into 32-beat bursts or less, allowing rearbitration
 * every 32 beats.
 * 6 64_BEAT
 * 64-beat Burst The undefined length burst or bursts sequence is split
 * into 64-beat bursts or less, allowing rearbitration
 * every 64 beats.
 * 7 128_BEAT
 * 128-beat Burst The undefined length burst or bursts sequence is split
 * into 128-beat bursts or less, allowing
 * re-arbitration every 128 beats.
 * Unless duly needed, the ULBT should be left at its default 0 value for
 * power saving.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_MCFG7 . ULBT7
 */
#define  VTSS_F_HMATRIX2_MATRIX_MCFG7_ULBT7(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_HMATRIX2_MATRIX_MCFG7_ULBT7     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_HMATRIX2_MATRIX_MCFG7_ULBT7(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Bus Matrix Initiator Configuration Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MCFG8
 */
#define VTSS_HMATRIX2_MATRIX_MCFG8           VTSS_IOREG(VTSS_TO_HMATRIX2,0x8)

/**
 * \brief
 * ULBT: Undefined Length Burst Type
 *
 * \details
 * 0 UNLIMITED
 * Unlimited Length Burst—No predicted end of burst is generated, therefore
 * INCR bursts coming from this
 * initiator can only be broken if the Target Slot Cycle Limit is reached.
 * If the Slot Cycle Limit is not reached, the
 * burst is normally completed by the initiator, at the latest, on the next
 * AHB 1 Kbyte address boundary, allowing
 * up to 256-beat word bursts or 128-beat double-word bursts.
 * This value should not be used in the very particular case of a initiator
 * capable of performing back-to-back
 * undefined length bursts on a single target, since this could
 * indefinitely freeze the target arbitration and thus
 * prevent another initiator from accessing this target.
 * 1 SINGLE
 * Single Access The undefined length burst is treated as a succession of
 * single accesses, allowing rearbitration
 * at each beat of the INCR burst or bursts sequence.
 * 2 4_BEAT
 * 4-beat Burst The undefined length burst or bursts sequence is split into
 * 4-beat bursts or less, allowing rearbitration
 * every 4 beats.
 * 3 8_BEAT
 * 8-beat Burst The undefined length burst or bursts sequence is split into
 * 8-beat bursts or less, allowing rearbitration
 * every 8 beats.
 * 4 16_BEAT
 * 16-beat Burst The undefined length burst or bursts sequence is split
 * into 16-beat bursts or less, allowing rearbitration
 * every 16 beats.
 * 5 32_BEAT
 * 32-beat Burst The undefined length burst or bursts sequence is split
 * into 32-beat bursts or less, allowing rearbitration
 * every 32 beats.
 * 6 64_BEAT
 * 64-beat Burst The undefined length burst or bursts sequence is split
 * into 64-beat bursts or less, allowing rearbitration
 * every 64 beats.
 * 7 128_BEAT
 * 128-beat Burst The undefined length burst or bursts sequence is split
 * into 128-beat bursts or less, allowing
 * re-arbitration every 128 beats.
 * Unless duly needed, the ULBT should be left at its default 0 value for
 * power saving.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_MCFG8 . ULBT8
 */
#define  VTSS_F_HMATRIX2_MATRIX_MCFG8_ULBT8(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_HMATRIX2_MATRIX_MCFG8_ULBT8     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_HMATRIX2_MATRIX_MCFG8_ULBT8(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Bus Matrix Target Configuration Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SCFG0
 */
#define VTSS_HMATRIX2_MATRIX_SCFG0           VTSS_IOREG(VTSS_TO_HMATRIX2,0x10)

/**
 * \brief
 * FIXED_DEFMSTR: Fixed Default InitiatorThis is the number of the Default
 * Initiator for this target. Only used if DEFMSTR_TYPE is 2. Specifying
 * the number of a initiatorwhich is not connected to the selected target
 * is equivalent to setting DEFMSTR_TYPE to 0.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG0 . FIXED_DEFMSTR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG0_FIXED_DEFMSTR0(x)  VTSS_ENCODE_BITFIELD(x,18,4)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG0_FIXED_DEFMSTR0     VTSS_ENCODE_BITMASK(18,4)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG0_FIXED_DEFMSTR0(x)  VTSS_EXTRACT_BITFIELD(x,18,4)

/**
 * \brief
 * DEFMSTR_TYPE: Default Initiator Type
 *
 * \details
 * 0 NONE
 * No Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target is
 * disconnected from all initiators.
 * This results in a one clock cycle latency for the first access of a
 * burst transfer or for a single access.
 * 1 LAST
 * Last Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target
 * stays connected to the last initiator having accessed it.
 * This results in not having one clock cycle latency when the last
 * initiator tries to access the target again.
 * 2 FIXED
 * Fixed Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target
 * connects to the fixed initiator the number that has been written in the
 * FIXED_DEFMSTR field.
 * This results in not having one clock cycle latency when the fixed
 * initiator tries to access the target again.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG0 . DEFMSTR_TYPE0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG0_DEFMSTR_TYPE0(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG0_DEFMSTR_TYPE0     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG0_DEFMSTR_TYPE0(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * SLOT_CYCLE: Maximum Bus Grant Duration for InitiatorsWhen SLOT_CYCLE AHB
 * clock cycles have elapsed since the last arbitration, a new arbitration
 * takes place to let anotherinitiator access this target. If another
 * initiator is requesting the target bus, then the current initiator burst
 * is broken.If SLOT_CYCLE = 0, the Slot Cycle Limit feature is disabled
 * and bursts always complete unless broken according to theULBT.This limit
 * has been placed in order to enforce arbitration so as to meet potential
 * latency constraints of initiators waiting fortarget access.This limit
 * must not be too small. Unreasonably small values break every burst and
 * the Bus Matrix arbitrates without performingany data transfer. The
 * default maximum value is usually an optimal conservative choice.In most
 * cases, this feature is not needed and should be disabled for power
 * saving.See  Slot Cycle Limit Arbitration  on page 5 for details.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG0 . SLOT_CYCLE0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG0_SLOT_CYCLE0(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG0_SLOT_CYCLE0     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG0_SLOT_CYCLE0(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/**
 * \brief Bus Matrix Target Configuration Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SCFG1
 */
#define VTSS_HMATRIX2_MATRIX_SCFG1           VTSS_IOREG(VTSS_TO_HMATRIX2,0x11)

/**
 * \brief
 * FIXED_DEFMSTR: Fixed Default InitiatorThis is the number of the Default
 * Initiator for this target. Only used if DEFMSTR_TYPE is 2. Specifying
 * the number of a initiatorwhich is not connected to the selected target
 * is equivalent to setting DEFMSTR_TYPE to 0.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG1 . FIXED_DEFMSTR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG1_FIXED_DEFMSTR1(x)  VTSS_ENCODE_BITFIELD(x,18,4)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG1_FIXED_DEFMSTR1     VTSS_ENCODE_BITMASK(18,4)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG1_FIXED_DEFMSTR1(x)  VTSS_EXTRACT_BITFIELD(x,18,4)

/**
 * \brief
 * DEFMSTR_TYPE: Default Initiator Type
 *
 * \details
 * 0 NONE
 * No Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target is
 * disconnected from all initiators.
 * This results in a one clock cycle latency for the first access of a
 * burst transfer or for a single access.
 * 1 LAST
 * Last Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target
 * stays connected to the last initiator having accessed it.
 * This results in not having one clock cycle latency when the last
 * initiator tries to access the target again.
 * 2 FIXED
 * Fixed Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target
 * connects to the fixed initiator the number that has been written in the
 * FIXED_DEFMSTR field.
 * This results in not having one clock cycle latency when the fixed
 * initiator tries to access the target again.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG1 . DEFMSTR_TYPE1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG1_DEFMSTR_TYPE1(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG1_DEFMSTR_TYPE1     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG1_DEFMSTR_TYPE1(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * SLOT_CYCLE: Maximum Bus Grant Duration for InitiatorsWhen SLOT_CYCLE AHB
 * clock cycles have elapsed since the last arbitration, a new arbitration
 * takes place to let anotherinitiator access this target. If another
 * initiator is requesting the target bus, then the current initiator burst
 * is broken.If SLOT_CYCLE = 0, the Slot Cycle Limit feature is disabled
 * and bursts always complete unless broken according to theULBT.This limit
 * has been placed in order to enforce arbitration so as to meet potential
 * latency constraints of initiators waiting fortarget access.This limit
 * must not be too small. Unreasonably small values break every burst and
 * the Bus Matrix arbitrates without performingany data transfer. The
 * default maximum value is usually an optimal conservative choice.In most
 * cases, this feature is not needed and should be disabled for power
 * saving.See  Slot Cycle Limit Arbitration  on page 5 for details.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG1 . SLOT_CYCLE1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG1_SLOT_CYCLE1(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG1_SLOT_CYCLE1     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG1_SLOT_CYCLE1(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/**
 * \brief Bus Matrix Target Configuration Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SCFG2
 */
#define VTSS_HMATRIX2_MATRIX_SCFG2           VTSS_IOREG(VTSS_TO_HMATRIX2,0x12)

/**
 * \brief
 * FIXED_DEFMSTR: Fixed Default InitiatorThis is the number of the Default
 * Initiator for this target. Only used if DEFMSTR_TYPE is 2. Specifying
 * the number of a initiatorwhich is not connected to the selected target
 * is equivalent to setting DEFMSTR_TYPE to 0.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG2 . FIXED_DEFMSTR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG2_FIXED_DEFMSTR2(x)  VTSS_ENCODE_BITFIELD(x,18,4)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG2_FIXED_DEFMSTR2     VTSS_ENCODE_BITMASK(18,4)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG2_FIXED_DEFMSTR2(x)  VTSS_EXTRACT_BITFIELD(x,18,4)

/**
 * \brief
 * DEFMSTR_TYPE: Default Initiator Type
 *
 * \details
 * 0 NONE
 * No Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target is
 * disconnected from all initiators.
 * This results in a one clock cycle latency for the first access of a
 * burst transfer or for a single access.
 * 1 LAST
 * Last Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target
 * stays connected to the last initiator having accessed it.
 * This results in not having one clock cycle latency when the last
 * initiator tries to access the target again.
 * 2 FIXED
 * Fixed Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target
 * connects to the fixed initiator the number that has been written in the
 * FIXED_DEFMSTR field.
 * This results in not having one clock cycle latency when the fixed
 * initiator tries to access the target again.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG2 . DEFMSTR_TYPE2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG2_DEFMSTR_TYPE2(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG2_DEFMSTR_TYPE2     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG2_DEFMSTR_TYPE2(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * SLOT_CYCLE: Maximum Bus Grant Duration for InitiatorsWhen SLOT_CYCLE AHB
 * clock cycles have elapsed since the last arbitration, a new arbitration
 * takes place to let anotherinitiator access this target. If another
 * initiator is requesting the target bus, then the current initiator burst
 * is broken.If SLOT_CYCLE = 0, the Slot Cycle Limit feature is disabled
 * and bursts always complete unless broken according to theULBT.This limit
 * has been placed in order to enforce arbitration so as to meet potential
 * latency constraints of initiators waiting fortarget access.This limit
 * must not be too small. Unreasonably small values break every burst and
 * the Bus Matrix arbitrates without performingany data transfer. The
 * default maximum value is usually an optimal conservative choice.In most
 * cases, this feature is not needed and should be disabled for power
 * saving.See  Slot Cycle Limit Arbitration  on page 5 for details.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG2 . SLOT_CYCLE2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG2_SLOT_CYCLE2(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG2_SLOT_CYCLE2     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG2_SLOT_CYCLE2(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/**
 * \brief Bus Matrix Target Configuration Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SCFG3
 */
#define VTSS_HMATRIX2_MATRIX_SCFG3           VTSS_IOREG(VTSS_TO_HMATRIX2,0x13)

/**
 * \brief
 * FIXED_DEFMSTR: Fixed Default InitiatorThis is the number of the Default
 * Initiator for this target. Only used if DEFMSTR_TYPE is 2. Specifying
 * the number of a initiatorwhich is not connected to the selected target
 * is equivalent to setting DEFMSTR_TYPE to 0.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG3 . FIXED_DEFMSTR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG3_FIXED_DEFMSTR3(x)  VTSS_ENCODE_BITFIELD(x,18,4)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG3_FIXED_DEFMSTR3     VTSS_ENCODE_BITMASK(18,4)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG3_FIXED_DEFMSTR3(x)  VTSS_EXTRACT_BITFIELD(x,18,4)

/**
 * \brief
 * DEFMSTR_TYPE: Default Initiator Type
 *
 * \details
 * 0 NONE
 * No Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target is
 * disconnected from all initiators.
 * This results in a one clock cycle latency for the first access of a
 * burst transfer or for a single access.
 * 1 LAST
 * Last Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target
 * stays connected to the last initiator having accessed it.
 * This results in not having one clock cycle latency when the last
 * initiator tries to access the target again.
 * 2 FIXED
 * Fixed Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target
 * connects to the fixed initiator the number that has been written in the
 * FIXED_DEFMSTR field.
 * This results in not having one clock cycle latency when the fixed
 * initiator tries to access the target again.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG3 . DEFMSTR_TYPE3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG3_DEFMSTR_TYPE3(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG3_DEFMSTR_TYPE3     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG3_DEFMSTR_TYPE3(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * SLOT_CYCLE: Maximum Bus Grant Duration for InitiatorsWhen SLOT_CYCLE AHB
 * clock cycles have elapsed since the last arbitration, a new arbitration
 * takes place to let anotherinitiator access this target. If another
 * initiator is requesting the target bus, then the current initiator burst
 * is broken.If SLOT_CYCLE = 0, the Slot Cycle Limit feature is disabled
 * and bursts always complete unless broken according to theULBT.This limit
 * has been placed in order to enforce arbitration so as to meet potential
 * latency constraints of initiators waiting fortarget access.This limit
 * must not be too small. Unreasonably small values break every burst and
 * the Bus Matrix arbitrates without performingany data transfer. The
 * default maximum value is usually an optimal conservative choice.In most
 * cases, this feature is not needed and should be disabled for power
 * saving.See  Slot Cycle Limit Arbitration  on page 5 for details.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG3 . SLOT_CYCLE3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG3_SLOT_CYCLE3(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG3_SLOT_CYCLE3     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG3_SLOT_CYCLE3(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/**
 * \brief Bus Matrix Target Configuration Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SCFG4
 */
#define VTSS_HMATRIX2_MATRIX_SCFG4           VTSS_IOREG(VTSS_TO_HMATRIX2,0x14)

/**
 * \brief
 * FIXED_DEFMSTR: Fixed Default InitiatorThis is the number of the Default
 * Initiator for this target. Only used if DEFMSTR_TYPE is 2. Specifying
 * the number of a initiatorwhich is not connected to the selected target
 * is equivalent to setting DEFMSTR_TYPE to 0.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG4 . FIXED_DEFMSTR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG4_FIXED_DEFMSTR4(x)  VTSS_ENCODE_BITFIELD(x,18,4)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG4_FIXED_DEFMSTR4     VTSS_ENCODE_BITMASK(18,4)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG4_FIXED_DEFMSTR4(x)  VTSS_EXTRACT_BITFIELD(x,18,4)

/**
 * \brief
 * DEFMSTR_TYPE: Default Initiator Type
 *
 * \details
 * 0 NONE
 * No Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target is
 * disconnected from all initiators.
 * This results in a one clock cycle latency for the first access of a
 * burst transfer or for a single access.
 * 1 LAST
 * Last Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target
 * stays connected to the last initiator having accessed it.
 * This results in not having one clock cycle latency when the last
 * initiator tries to access the target again.
 * 2 FIXED
 * Fixed Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target
 * connects to the fixed initiator the number that has been written in the
 * FIXED_DEFMSTR field.
 * This results in not having one clock cycle latency when the fixed
 * initiator tries to access the target again.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG4 . DEFMSTR_TYPE4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG4_DEFMSTR_TYPE4(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG4_DEFMSTR_TYPE4     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG4_DEFMSTR_TYPE4(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * SLOT_CYCLE: Maximum Bus Grant Duration for InitiatorsWhen SLOT_CYCLE AHB
 * clock cycles have elapsed since the last arbitration, a new arbitration
 * takes place to let anotherinitiator access this target. If another
 * initiator is requesting the target bus, then the current initiator burst
 * is broken.If SLOT_CYCLE = 0, the Slot Cycle Limit feature is disabled
 * and bursts always complete unless broken according to theULBT.This limit
 * has been placed in order to enforce arbitration so as to meet potential
 * latency constraints of initiators waiting fortarget access.This limit
 * must not be too small. Unreasonably small values break every burst and
 * the Bus Matrix arbitrates without performingany data transfer. The
 * default maximum value is usually an optimal conservative choice.In most
 * cases, this feature is not needed and should be disabled for power
 * saving.See  Slot Cycle Limit Arbitration  on page 5 for details.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG4 . SLOT_CYCLE4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG4_SLOT_CYCLE4(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG4_SLOT_CYCLE4     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG4_SLOT_CYCLE4(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/**
 * \brief Bus Matrix Target Configuration Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SCFG5
 */
#define VTSS_HMATRIX2_MATRIX_SCFG5           VTSS_IOREG(VTSS_TO_HMATRIX2,0x15)

/**
 * \brief
 * FIXED_DEFMSTR: Fixed Default InitiatorThis is the number of the Default
 * Initiator for this target. Only used if DEFMSTR_TYPE is 2. Specifying
 * the number of a initiatorwhich is not connected to the selected target
 * is equivalent to setting DEFMSTR_TYPE to 0.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG5 . FIXED_DEFMSTR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG5_FIXED_DEFMSTR5(x)  VTSS_ENCODE_BITFIELD(x,18,4)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG5_FIXED_DEFMSTR5     VTSS_ENCODE_BITMASK(18,4)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG5_FIXED_DEFMSTR5(x)  VTSS_EXTRACT_BITFIELD(x,18,4)

/**
 * \brief
 * DEFMSTR_TYPE: Default Initiator Type
 *
 * \details
 * 0 NONE
 * No Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target is
 * disconnected from all initiators.
 * This results in a one clock cycle latency for the first access of a
 * burst transfer or for a single access.
 * 1 LAST
 * Last Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target
 * stays connected to the last initiator having accessed it.
 * This results in not having one clock cycle latency when the last
 * initiator tries to access the target again.
 * 2 FIXED
 * Fixed Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target
 * connects to the fixed initiator the number that has been written in the
 * FIXED_DEFMSTR field.
 * This results in not having one clock cycle latency when the fixed
 * initiator tries to access the target again.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG5 . DEFMSTR_TYPE5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG5_DEFMSTR_TYPE5(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG5_DEFMSTR_TYPE5     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG5_DEFMSTR_TYPE5(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * SLOT_CYCLE: Maximum Bus Grant Duration for InitiatorsWhen SLOT_CYCLE AHB
 * clock cycles have elapsed since the last arbitration, a new arbitration
 * takes place to let anotherinitiator access this target. If another
 * initiator is requesting the target bus, then the current initiator burst
 * is broken.If SLOT_CYCLE = 0, the Slot Cycle Limit feature is disabled
 * and bursts always complete unless broken according to theULBT.This limit
 * has been placed in order to enforce arbitration so as to meet potential
 * latency constraints of initiators waiting fortarget access.This limit
 * must not be too small. Unreasonably small values break every burst and
 * the Bus Matrix arbitrates without performingany data transfer. The
 * default maximum value is usually an optimal conservative choice.In most
 * cases, this feature is not needed and should be disabled for power
 * saving.See  Slot Cycle Limit Arbitration  on page 5 for details.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG5 . SLOT_CYCLE5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG5_SLOT_CYCLE5(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG5_SLOT_CYCLE5     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG5_SLOT_CYCLE5(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/**
 * \brief Bus Matrix Target Configuration Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SCFG6
 */
#define VTSS_HMATRIX2_MATRIX_SCFG6           VTSS_IOREG(VTSS_TO_HMATRIX2,0x16)

/**
 * \brief
 * FIXED_DEFMSTR: Fixed Default InitiatorThis is the number of the Default
 * Initiator for this target. Only used if DEFMSTR_TYPE is 2. Specifying
 * the number of a initiatorwhich is not connected to the selected target
 * is equivalent to setting DEFMSTR_TYPE to 0.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG6 . FIXED_DEFMSTR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG6_FIXED_DEFMSTR6(x)  VTSS_ENCODE_BITFIELD(x,18,4)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG6_FIXED_DEFMSTR6     VTSS_ENCODE_BITMASK(18,4)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG6_FIXED_DEFMSTR6(x)  VTSS_EXTRACT_BITFIELD(x,18,4)

/**
 * \brief
 * DEFMSTR_TYPE: Default Initiator Type
 *
 * \details
 * 0 NONE
 * No Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target is
 * disconnected from all initiators.
 * This results in a one clock cycle latency for the first access of a
 * burst transfer or for a single access.
 * 1 LAST
 * Last Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target
 * stays connected to the last initiator having accessed it.
 * This results in not having one clock cycle latency when the last
 * initiator tries to access the target again.
 * 2 FIXED
 * Fixed Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target
 * connects to the fixed initiator the number that has been written in the
 * FIXED_DEFMSTR field.
 * This results in not having one clock cycle latency when the fixed
 * initiator tries to access the target again.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG6 . DEFMSTR_TYPE6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG6_DEFMSTR_TYPE6(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG6_DEFMSTR_TYPE6     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG6_DEFMSTR_TYPE6(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * SLOT_CYCLE: Maximum Bus Grant Duration for InitiatorsWhen SLOT_CYCLE AHB
 * clock cycles have elapsed since the last arbitration, a new arbitration
 * takes place to let anotherinitiator access this target. If another
 * initiator is requesting the target bus, then the current initiator burst
 * is broken.If SLOT_CYCLE = 0, the Slot Cycle Limit feature is disabled
 * and bursts always complete unless broken according to theULBT.This limit
 * has been placed in order to enforce arbitration so as to meet potential
 * latency constraints of initiators waiting fortarget access.This limit
 * must not be too small. Unreasonably small values break every burst and
 * the Bus Matrix arbitrates without performingany data transfer. The
 * default maximum value is usually an optimal conservative choice.In most
 * cases, this feature is not needed and should be disabled for power
 * saving.See  Slot Cycle Limit Arbitration  on page 5 for details.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG6 . SLOT_CYCLE6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG6_SLOT_CYCLE6(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG6_SLOT_CYCLE6     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG6_SLOT_CYCLE6(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/**
 * \brief Bus Matrix Target Configuration Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SCFG7
 */
#define VTSS_HMATRIX2_MATRIX_SCFG7           VTSS_IOREG(VTSS_TO_HMATRIX2,0x9)

/**
 * \brief
 * FIXED_DEFMSTR: Fixed Default InitiatorThis is the number of the Default
 * Initiator for this target. Only used if DEFMSTR_TYPE is 2. Specifying
 * the number of a initiatorwhich is not connected to the selected target
 * is equivalent to setting DEFMSTR_TYPE to 0.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG7 . FIXED_DEFMSTR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG7_FIXED_DEFMSTR7(x)  VTSS_ENCODE_BITFIELD(x,18,4)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG7_FIXED_DEFMSTR7     VTSS_ENCODE_BITMASK(18,4)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG7_FIXED_DEFMSTR7(x)  VTSS_EXTRACT_BITFIELD(x,18,4)

/**
 * \brief
 * DEFMSTR_TYPE: Default Initiator Type
 *
 * \details
 * 0 NONE
 * No Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target is
 * disconnected from all initiators.
 * This results in a one clock cycle latency for the first access of a
 * burst transfer or for a single access.
 * 1 LAST
 * Last Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target
 * stays connected to the last initiator having accessed it.
 * This results in not having one clock cycle latency when the last
 * initiator tries to access the target again.
 * 2 FIXED
 * Fixed Default Initiator At the end of the current target access, if no
 * other initiator request is pending, the target
 * connects to the fixed initiator the number that has been written in the
 * FIXED_DEFMSTR field.
 * This results in not having one clock cycle latency when the fixed
 * initiator tries to access the target again.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG7 . DEFMSTR_TYPE7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG7_DEFMSTR_TYPE7(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG7_DEFMSTR_TYPE7     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG7_DEFMSTR_TYPE7(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * SLOT_CYCLE: Maximum Bus Grant Duration for InitiatorsWhen SLOT_CYCLE AHB
 * clock cycles have elapsed since the last arbitration, a new arbitration
 * takes place to let anotherinitiator access this target. If another
 * initiator is requesting the target bus, then the current initiator burst
 * is broken.If SLOT_CYCLE = 0, the Slot Cycle Limit feature is disabled
 * and bursts always complete unless broken according to theULBT.This limit
 * has been placed in order to enforce arbitration so as to meet potential
 * latency constraints of initiators waiting fortarget access.This limit
 * must not be too small. Unreasonably small values break every burst and
 * the Bus Matrix arbitrates without performingany data transfer. The
 * default maximum value is usually an optimal conservative choice.In most
 * cases, this feature is not needed and should be disabled for power
 * saving.See  Slot Cycle Limit Arbitration  on page 5 for details.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SCFG7 . SLOT_CYCLE7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SCFG7_SLOT_CYCLE7(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_HMATRIX2_MATRIX_SCFG7_SLOT_CYCLE7     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_HMATRIX2_MATRIX_SCFG7_SLOT_CYCLE7(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/**
 * \brief Bus Matrix Priority Registers A For Targets
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_PRAS0
 */
#define VTSS_HMATRIX2_MATRIX_PRAS0           VTSS_IOREG(VTSS_TO_HMATRIX2,0x20)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS0 . LQOSEN7_PRAS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS0_LQOSEN7_PRAS0(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS0_LQOSEN7_PRAS0  VTSS_BIT(30)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS0_LQOSEN7_PRAS0(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS0 . M7PR_PRAS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS0_M7PR_PRAS0(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS0_M7PR_PRAS0     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS0_M7PR_PRAS0(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS0 . LQOSEN6_PRAS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS0_LQOSEN6_PRAS0(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS0_LQOSEN6_PRAS0  VTSS_BIT(26)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS0_LQOSEN6_PRAS0(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS0 . M6PR_PRAS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS0_M6PR_PRAS0(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS0_M6PR_PRAS0     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS0_M6PR_PRAS0(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS0 . LQOSEN5_PRAS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS0_LQOSEN5_PRAS0(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS0_LQOSEN5_PRAS0  VTSS_BIT(22)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS0_LQOSEN5_PRAS0(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS0 . M5PR_PRAS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS0_M5PR_PRAS0(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS0_M5PR_PRAS0     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS0_M5PR_PRAS0(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS0 . LQOSEN4_PRAS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS0_LQOSEN4_PRAS0(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS0_LQOSEN4_PRAS0  VTSS_BIT(18)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS0_LQOSEN4_PRAS0(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS0 . M4PR_PRAS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS0_M4PR_PRAS0(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS0_M4PR_PRAS0     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS0_M4PR_PRAS0(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS0 . LQOSEN3_PRAS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS0_LQOSEN3_PRAS0(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS0_LQOSEN3_PRAS0  VTSS_BIT(14)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS0_LQOSEN3_PRAS0(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS0 . M3PR_PRAS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS0_M3PR_PRAS0(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS0_M3PR_PRAS0     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS0_M3PR_PRAS0(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS0 . LQOSEN2_PRAS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS0_LQOSEN2_PRAS0(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS0_LQOSEN2_PRAS0  VTSS_BIT(10)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS0_LQOSEN2_PRAS0(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS0 . M2PR_PRAS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS0_M2PR_PRAS0(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS0_M2PR_PRAS0     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS0_M2PR_PRAS0(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS0 . LQOSEN1_PRAS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS0_LQOSEN1_PRAS0(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS0_LQOSEN1_PRAS0  VTSS_BIT(6)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS0_LQOSEN1_PRAS0(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS0 . M1PR_PRAS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS0_M1PR_PRAS0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS0_M1PR_PRAS0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS0_M1PR_PRAS0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS0 . LQOSEN0_PRAS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS0_LQOSEN0_PRAS0(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS0_LQOSEN0_PRAS0  VTSS_BIT(2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS0_LQOSEN0_PRAS0(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS0 . M0PR_PRAS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS0_M0PR_PRAS0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS0_M0PR_PRAS0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS0_M0PR_PRAS0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Priority Register B for Target 0
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_PRBS0
 */
#define VTSS_HMATRIX2_MATRIX_PRBS0           VTSS_IOREG(VTSS_TO_HMATRIX2,0x21)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS0 . LQOSEN15_PRBS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS0_LQOSEN15_PRBS0(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS0_LQOSEN15_PRBS0  VTSS_BIT(30)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS0_LQOSEN15_PRBS0(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS0 . M15PR_PRBS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS0_M15PR_PRBS0(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS0_M15PR_PRBS0     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS0_M15PR_PRBS0(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS0 . LQOSEN14_PRBS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS0_LQOSEN14_PRBS0(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS0_LQOSEN14_PRBS0  VTSS_BIT(26)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS0_LQOSEN14_PRBS0(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS0 . M14PR_PRBS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS0_M14PR_PRBS0(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS0_M14PR_PRBS0     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS0_M14PR_PRBS0(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS0 . LQOSEN13_PRBS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS0_LQOSEN13_PRBS0(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS0_LQOSEN13_PRBS0  VTSS_BIT(22)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS0_LQOSEN13_PRBS0(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS0 . M13PR_PRBS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS0_M13PR_PRBS0(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS0_M13PR_PRBS0     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS0_M13PR_PRBS0(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS0 . LQOSEN12_PRBS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS0_LQOSEN12_PRBS0(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS0_LQOSEN12_PRBS0  VTSS_BIT(18)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS0_LQOSEN12_PRBS0(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS0 . M12PR_PRBS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS0_M12PR_PRBS0(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS0_M12PR_PRBS0     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS0_M12PR_PRBS0(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS0 . LQOSEN11_PRBS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS0_LQOSEN11_PRBS0(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS0_LQOSEN11_PRBS0  VTSS_BIT(14)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS0_LQOSEN11_PRBS0(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS0 . M11PR_PRBS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS0_M11PR_PRBS0(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS0_M11PR_PRBS0     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS0_M11PR_PRBS0(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS0 . LQOSEN10_PRBS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS0_LQOSEN10_PRBS0(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS0_LQOSEN10_PRBS0  VTSS_BIT(10)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS0_LQOSEN10_PRBS0(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS0 . M10PR_PRBS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS0_M10PR_PRBS0(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS0_M10PR_PRBS0     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS0_M10PR_PRBS0(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS0 . LQOSEN9_PRBS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS0_LQOSEN9_PRBS0(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS0_LQOSEN9_PRBS0  VTSS_BIT(6)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS0_LQOSEN9_PRBS0(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS0 . M9PR_PRBS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS0_M9PR_PRBS0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS0_M9PR_PRBS0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS0_M9PR_PRBS0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS0 . LQOSEN8_PRBS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS0_LQOSEN8_PRBS0(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS0_LQOSEN8_PRBS0  VTSS_BIT(2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS0_LQOSEN8_PRBS0(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS0 . M8PR_PRBS0
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS0_M8PR_PRBS0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS0_M8PR_PRBS0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS0_M8PR_PRBS0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Bus Matrix Priority Registers A For Targets
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_PRAS1
 */
#define VTSS_HMATRIX2_MATRIX_PRAS1           VTSS_IOREG(VTSS_TO_HMATRIX2,0x22)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS1 . LQOSEN7_PRAS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS1_LQOSEN7_PRAS1(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS1_LQOSEN7_PRAS1  VTSS_BIT(30)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS1_LQOSEN7_PRAS1(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS1 . M7PR_PRAS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS1_M7PR_PRAS1(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS1_M7PR_PRAS1     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS1_M7PR_PRAS1(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS1 . LQOSEN6_PRAS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS1_LQOSEN6_PRAS1(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS1_LQOSEN6_PRAS1  VTSS_BIT(26)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS1_LQOSEN6_PRAS1(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS1 . M6PR_PRAS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS1_M6PR_PRAS1(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS1_M6PR_PRAS1     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS1_M6PR_PRAS1(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS1 . LQOSEN5_PRAS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS1_LQOSEN5_PRAS1(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS1_LQOSEN5_PRAS1  VTSS_BIT(22)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS1_LQOSEN5_PRAS1(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS1 . M5PR_PRAS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS1_M5PR_PRAS1(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS1_M5PR_PRAS1     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS1_M5PR_PRAS1(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS1 . LQOSEN4_PRAS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS1_LQOSEN4_PRAS1(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS1_LQOSEN4_PRAS1  VTSS_BIT(18)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS1_LQOSEN4_PRAS1(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS1 . M4PR_PRAS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS1_M4PR_PRAS1(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS1_M4PR_PRAS1     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS1_M4PR_PRAS1(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS1 . LQOSEN3_PRAS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS1_LQOSEN3_PRAS1(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS1_LQOSEN3_PRAS1  VTSS_BIT(14)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS1_LQOSEN3_PRAS1(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS1 . M3PR_PRAS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS1_M3PR_PRAS1(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS1_M3PR_PRAS1     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS1_M3PR_PRAS1(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS1 . LQOSEN2_PRAS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS1_LQOSEN2_PRAS1(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS1_LQOSEN2_PRAS1  VTSS_BIT(10)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS1_LQOSEN2_PRAS1(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS1 . M2PR_PRAS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS1_M2PR_PRAS1(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS1_M2PR_PRAS1     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS1_M2PR_PRAS1(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS1 . LQOSEN1_PRAS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS1_LQOSEN1_PRAS1(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS1_LQOSEN1_PRAS1  VTSS_BIT(6)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS1_LQOSEN1_PRAS1(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS1 . M1PR_PRAS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS1_M1PR_PRAS1(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS1_M1PR_PRAS1     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS1_M1PR_PRAS1(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS1 . LQOSEN0_PRAS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS1_LQOSEN0_PRAS1(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS1_LQOSEN0_PRAS1  VTSS_BIT(2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS1_LQOSEN0_PRAS1(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS1 . M0PR_PRAS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS1_M0PR_PRAS1(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS1_M0PR_PRAS1     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS1_M0PR_PRAS1(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Priority Register B for Target 0
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_PRBS1
 */
#define VTSS_HMATRIX2_MATRIX_PRBS1           VTSS_IOREG(VTSS_TO_HMATRIX2,0x23)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS1 . LQOSEN15_PRBS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS1_LQOSEN15_PRBS1(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS1_LQOSEN15_PRBS1  VTSS_BIT(30)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS1_LQOSEN15_PRBS1(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS1 . M15PR_PRBS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS1_M15PR_PRBS1(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS1_M15PR_PRBS1     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS1_M15PR_PRBS1(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS1 . LQOSEN14_PRBS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS1_LQOSEN14_PRBS1(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS1_LQOSEN14_PRBS1  VTSS_BIT(26)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS1_LQOSEN14_PRBS1(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS1 . M14PR_PRBS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS1_M14PR_PRBS1(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS1_M14PR_PRBS1     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS1_M14PR_PRBS1(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS1 . LQOSEN13_PRBS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS1_LQOSEN13_PRBS1(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS1_LQOSEN13_PRBS1  VTSS_BIT(22)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS1_LQOSEN13_PRBS1(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS1 . M13PR_PRBS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS1_M13PR_PRBS1(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS1_M13PR_PRBS1     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS1_M13PR_PRBS1(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS1 . LQOSEN12_PRBS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS1_LQOSEN12_PRBS1(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS1_LQOSEN12_PRBS1  VTSS_BIT(18)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS1_LQOSEN12_PRBS1(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS1 . M12PR_PRBS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS1_M12PR_PRBS1(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS1_M12PR_PRBS1     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS1_M12PR_PRBS1(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS1 . LQOSEN11_PRBS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS1_LQOSEN11_PRBS1(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS1_LQOSEN11_PRBS1  VTSS_BIT(14)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS1_LQOSEN11_PRBS1(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS1 . M11PR_PRBS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS1_M11PR_PRBS1(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS1_M11PR_PRBS1     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS1_M11PR_PRBS1(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS1 . LQOSEN10_PRBS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS1_LQOSEN10_PRBS1(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS1_LQOSEN10_PRBS1  VTSS_BIT(10)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS1_LQOSEN10_PRBS1(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS1 . M10PR_PRBS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS1_M10PR_PRBS1(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS1_M10PR_PRBS1     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS1_M10PR_PRBS1(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS1 . LQOSEN9_PRBS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS1_LQOSEN9_PRBS1(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS1_LQOSEN9_PRBS1  VTSS_BIT(6)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS1_LQOSEN9_PRBS1(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS1 . M9PR_PRBS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS1_M9PR_PRBS1(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS1_M9PR_PRBS1     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS1_M9PR_PRBS1(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS1 . LQOSEN8_PRBS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS1_LQOSEN8_PRBS1(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS1_LQOSEN8_PRBS1  VTSS_BIT(2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS1_LQOSEN8_PRBS1(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS1 . M8PR_PRBS1
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS1_M8PR_PRBS1(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS1_M8PR_PRBS1     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS1_M8PR_PRBS1(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Bus Matrix Priority Registers A For Targets
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_PRAS2
 */
#define VTSS_HMATRIX2_MATRIX_PRAS2           VTSS_IOREG(VTSS_TO_HMATRIX2,0x24)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS2 . LQOSEN7_PRAS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS2_LQOSEN7_PRAS2(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS2_LQOSEN7_PRAS2  VTSS_BIT(30)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS2_LQOSEN7_PRAS2(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS2 . M7PR_PRAS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS2_M7PR_PRAS2(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS2_M7PR_PRAS2     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS2_M7PR_PRAS2(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS2 . LQOSEN6_PRAS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS2_LQOSEN6_PRAS2(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS2_LQOSEN6_PRAS2  VTSS_BIT(26)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS2_LQOSEN6_PRAS2(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS2 . M6PR_PRAS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS2_M6PR_PRAS2(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS2_M6PR_PRAS2     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS2_M6PR_PRAS2(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS2 . LQOSEN5_PRAS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS2_LQOSEN5_PRAS2(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS2_LQOSEN5_PRAS2  VTSS_BIT(22)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS2_LQOSEN5_PRAS2(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS2 . M5PR_PRAS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS2_M5PR_PRAS2(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS2_M5PR_PRAS2     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS2_M5PR_PRAS2(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS2 . LQOSEN4_PRAS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS2_LQOSEN4_PRAS2(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS2_LQOSEN4_PRAS2  VTSS_BIT(18)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS2_LQOSEN4_PRAS2(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS2 . M4PR_PRAS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS2_M4PR_PRAS2(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS2_M4PR_PRAS2     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS2_M4PR_PRAS2(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS2 . LQOSEN3_PRAS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS2_LQOSEN3_PRAS2(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS2_LQOSEN3_PRAS2  VTSS_BIT(14)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS2_LQOSEN3_PRAS2(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS2 . M3PR_PRAS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS2_M3PR_PRAS2(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS2_M3PR_PRAS2     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS2_M3PR_PRAS2(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS2 . LQOSEN2_PRAS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS2_LQOSEN2_PRAS2(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS2_LQOSEN2_PRAS2  VTSS_BIT(10)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS2_LQOSEN2_PRAS2(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS2 . M2PR_PRAS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS2_M2PR_PRAS2(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS2_M2PR_PRAS2     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS2_M2PR_PRAS2(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS2 . LQOSEN1_PRAS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS2_LQOSEN1_PRAS2(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS2_LQOSEN1_PRAS2  VTSS_BIT(6)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS2_LQOSEN1_PRAS2(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS2 . M1PR_PRAS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS2_M1PR_PRAS2(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS2_M1PR_PRAS2     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS2_M1PR_PRAS2(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS2 . LQOSEN0_PRAS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS2_LQOSEN0_PRAS2(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS2_LQOSEN0_PRAS2  VTSS_BIT(2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS2_LQOSEN0_PRAS2(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS2 . M0PR_PRAS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS2_M0PR_PRAS2(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS2_M0PR_PRAS2     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS2_M0PR_PRAS2(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Priority Register B for Target 0
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_PRBS2
 */
#define VTSS_HMATRIX2_MATRIX_PRBS2           VTSS_IOREG(VTSS_TO_HMATRIX2,0x25)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS2 . LQOSEN15_PRBS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS2_LQOSEN15_PRBS2(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS2_LQOSEN15_PRBS2  VTSS_BIT(30)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS2_LQOSEN15_PRBS2(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS2 . M15PR_PRBS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS2_M15PR_PRBS2(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS2_M15PR_PRBS2     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS2_M15PR_PRBS2(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS2 . LQOSEN14_PRBS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS2_LQOSEN14_PRBS2(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS2_LQOSEN14_PRBS2  VTSS_BIT(26)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS2_LQOSEN14_PRBS2(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS2 . M14PR_PRBS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS2_M14PR_PRBS2(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS2_M14PR_PRBS2     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS2_M14PR_PRBS2(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS2 . LQOSEN13_PRBS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS2_LQOSEN13_PRBS2(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS2_LQOSEN13_PRBS2  VTSS_BIT(22)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS2_LQOSEN13_PRBS2(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS2 . M13PR_PRBS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS2_M13PR_PRBS2(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS2_M13PR_PRBS2     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS2_M13PR_PRBS2(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS2 . LQOSEN12_PRBS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS2_LQOSEN12_PRBS2(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS2_LQOSEN12_PRBS2  VTSS_BIT(18)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS2_LQOSEN12_PRBS2(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS2 . M12PR_PRBS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS2_M12PR_PRBS2(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS2_M12PR_PRBS2     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS2_M12PR_PRBS2(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS2 . LQOSEN11_PRBS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS2_LQOSEN11_PRBS2(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS2_LQOSEN11_PRBS2  VTSS_BIT(14)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS2_LQOSEN11_PRBS2(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS2 . M11PR_PRBS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS2_M11PR_PRBS2(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS2_M11PR_PRBS2     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS2_M11PR_PRBS2(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS2 . LQOSEN10_PRBS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS2_LQOSEN10_PRBS2(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS2_LQOSEN10_PRBS2  VTSS_BIT(10)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS2_LQOSEN10_PRBS2(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS2 . M10PR_PRBS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS2_M10PR_PRBS2(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS2_M10PR_PRBS2     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS2_M10PR_PRBS2(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS2 . LQOSEN9_PRBS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS2_LQOSEN9_PRBS2(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS2_LQOSEN9_PRBS2  VTSS_BIT(6)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS2_LQOSEN9_PRBS2(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS2 . M9PR_PRBS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS2_M9PR_PRBS2(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS2_M9PR_PRBS2     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS2_M9PR_PRBS2(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS2 . LQOSEN8_PRBS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS2_LQOSEN8_PRBS2(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS2_LQOSEN8_PRBS2  VTSS_BIT(2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS2_LQOSEN8_PRBS2(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS2 . M8PR_PRBS2
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS2_M8PR_PRBS2(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS2_M8PR_PRBS2     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS2_M8PR_PRBS2(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Bus Matrix Priority Registers A For Targets
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_PRAS3
 */
#define VTSS_HMATRIX2_MATRIX_PRAS3           VTSS_IOREG(VTSS_TO_HMATRIX2,0x26)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS3 . LQOSEN7_PRAS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS3_LQOSEN7_PRAS3(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS3_LQOSEN7_PRAS3  VTSS_BIT(30)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS3_LQOSEN7_PRAS3(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS3 . M7PR_PRAS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS3_M7PR_PRAS3(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS3_M7PR_PRAS3     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS3_M7PR_PRAS3(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS3 . LQOSEN6_PRAS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS3_LQOSEN6_PRAS3(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS3_LQOSEN6_PRAS3  VTSS_BIT(26)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS3_LQOSEN6_PRAS3(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS3 . M6PR_PRAS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS3_M6PR_PRAS3(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS3_M6PR_PRAS3     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS3_M6PR_PRAS3(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS3 . LQOSEN5_PRAS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS3_LQOSEN5_PRAS3(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS3_LQOSEN5_PRAS3  VTSS_BIT(22)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS3_LQOSEN5_PRAS3(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS3 . M5PR_PRAS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS3_M5PR_PRAS3(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS3_M5PR_PRAS3     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS3_M5PR_PRAS3(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS3 . LQOSEN4_PRAS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS3_LQOSEN4_PRAS3(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS3_LQOSEN4_PRAS3  VTSS_BIT(18)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS3_LQOSEN4_PRAS3(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS3 . M4PR_PRAS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS3_M4PR_PRAS3(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS3_M4PR_PRAS3     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS3_M4PR_PRAS3(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS3 . LQOSEN3_PRAS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS3_LQOSEN3_PRAS3(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS3_LQOSEN3_PRAS3  VTSS_BIT(14)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS3_LQOSEN3_PRAS3(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS3 . M3PR_PRAS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS3_M3PR_PRAS3(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS3_M3PR_PRAS3     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS3_M3PR_PRAS3(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS3 . LQOSEN2_PRAS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS3_LQOSEN2_PRAS3(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS3_LQOSEN2_PRAS3  VTSS_BIT(10)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS3_LQOSEN2_PRAS3(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS3 . M2PR_PRAS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS3_M2PR_PRAS3(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS3_M2PR_PRAS3     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS3_M2PR_PRAS3(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS3 . LQOSEN1_PRAS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS3_LQOSEN1_PRAS3(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS3_LQOSEN1_PRAS3  VTSS_BIT(6)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS3_LQOSEN1_PRAS3(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS3 . M1PR_PRAS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS3_M1PR_PRAS3(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS3_M1PR_PRAS3     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS3_M1PR_PRAS3(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS3 . LQOSEN0_PRAS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS3_LQOSEN0_PRAS3(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS3_LQOSEN0_PRAS3  VTSS_BIT(2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS3_LQOSEN0_PRAS3(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS3 . M0PR_PRAS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS3_M0PR_PRAS3(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS3_M0PR_PRAS3     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS3_M0PR_PRAS3(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Priority Register B for Target 0
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_PRBS3
 */
#define VTSS_HMATRIX2_MATRIX_PRBS3           VTSS_IOREG(VTSS_TO_HMATRIX2,0x27)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS3 . LQOSEN15_PRBS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS3_LQOSEN15_PRBS3(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS3_LQOSEN15_PRBS3  VTSS_BIT(30)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS3_LQOSEN15_PRBS3(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS3 . M15PR_PRBS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS3_M15PR_PRBS3(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS3_M15PR_PRBS3     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS3_M15PR_PRBS3(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS3 . LQOSEN14_PRBS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS3_LQOSEN14_PRBS3(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS3_LQOSEN14_PRBS3  VTSS_BIT(26)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS3_LQOSEN14_PRBS3(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS3 . M14PR_PRBS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS3_M14PR_PRBS3(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS3_M14PR_PRBS3     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS3_M14PR_PRBS3(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS3 . LQOSEN13_PRBS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS3_LQOSEN13_PRBS3(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS3_LQOSEN13_PRBS3  VTSS_BIT(22)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS3_LQOSEN13_PRBS3(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS3 . M13PR_PRBS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS3_M13PR_PRBS3(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS3_M13PR_PRBS3     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS3_M13PR_PRBS3(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS3 . LQOSEN12_PRBS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS3_LQOSEN12_PRBS3(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS3_LQOSEN12_PRBS3  VTSS_BIT(18)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS3_LQOSEN12_PRBS3(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS3 . M12PR_PRBS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS3_M12PR_PRBS3(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS3_M12PR_PRBS3     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS3_M12PR_PRBS3(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS3 . LQOSEN11_PRBS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS3_LQOSEN11_PRBS3(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS3_LQOSEN11_PRBS3  VTSS_BIT(14)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS3_LQOSEN11_PRBS3(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS3 . M11PR_PRBS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS3_M11PR_PRBS3(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS3_M11PR_PRBS3     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS3_M11PR_PRBS3(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS3 . LQOSEN10_PRBS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS3_LQOSEN10_PRBS3(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS3_LQOSEN10_PRBS3  VTSS_BIT(10)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS3_LQOSEN10_PRBS3(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS3 . M10PR_PRBS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS3_M10PR_PRBS3(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS3_M10PR_PRBS3     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS3_M10PR_PRBS3(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS3 . LQOSEN9_PRBS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS3_LQOSEN9_PRBS3(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS3_LQOSEN9_PRBS3  VTSS_BIT(6)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS3_LQOSEN9_PRBS3(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS3 . M9PR_PRBS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS3_M9PR_PRBS3(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS3_M9PR_PRBS3     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS3_M9PR_PRBS3(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS3 . LQOSEN8_PRBS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS3_LQOSEN8_PRBS3(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS3_LQOSEN8_PRBS3  VTSS_BIT(2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS3_LQOSEN8_PRBS3(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS3 . M8PR_PRBS3
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS3_M8PR_PRBS3(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS3_M8PR_PRBS3     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS3_M8PR_PRBS3(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Bus Matrix Priority Registers A For Targets
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_PRAS4
 */
#define VTSS_HMATRIX2_MATRIX_PRAS4           VTSS_IOREG(VTSS_TO_HMATRIX2,0x28)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS4 . LQOSEN7_PRAS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS4_LQOSEN7_PRAS4(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS4_LQOSEN7_PRAS4  VTSS_BIT(30)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS4_LQOSEN7_PRAS4(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS4 . M7PR_PRAS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS4_M7PR_PRAS4(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS4_M7PR_PRAS4     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS4_M7PR_PRAS4(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS4 . LQOSEN6_PRAS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS4_LQOSEN6_PRAS4(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS4_LQOSEN6_PRAS4  VTSS_BIT(26)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS4_LQOSEN6_PRAS4(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS4 . M6PR_PRAS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS4_M6PR_PRAS4(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS4_M6PR_PRAS4     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS4_M6PR_PRAS4(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS4 . LQOSEN5_PRAS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS4_LQOSEN5_PRAS4(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS4_LQOSEN5_PRAS4  VTSS_BIT(22)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS4_LQOSEN5_PRAS4(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS4 . M5PR_PRAS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS4_M5PR_PRAS4(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS4_M5PR_PRAS4     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS4_M5PR_PRAS4(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS4 . LQOSEN4_PRAS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS4_LQOSEN4_PRAS4(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS4_LQOSEN4_PRAS4  VTSS_BIT(18)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS4_LQOSEN4_PRAS4(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS4 . M4PR_PRAS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS4_M4PR_PRAS4(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS4_M4PR_PRAS4     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS4_M4PR_PRAS4(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS4 . LQOSEN3_PRAS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS4_LQOSEN3_PRAS4(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS4_LQOSEN3_PRAS4  VTSS_BIT(14)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS4_LQOSEN3_PRAS4(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS4 . M3PR_PRAS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS4_M3PR_PRAS4(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS4_M3PR_PRAS4     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS4_M3PR_PRAS4(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS4 . LQOSEN2_PRAS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS4_LQOSEN2_PRAS4(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS4_LQOSEN2_PRAS4  VTSS_BIT(10)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS4_LQOSEN2_PRAS4(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS4 . M2PR_PRAS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS4_M2PR_PRAS4(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS4_M2PR_PRAS4     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS4_M2PR_PRAS4(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS4 . LQOSEN1_PRAS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS4_LQOSEN1_PRAS4(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS4_LQOSEN1_PRAS4  VTSS_BIT(6)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS4_LQOSEN1_PRAS4(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS4 . M1PR_PRAS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS4_M1PR_PRAS4(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS4_M1PR_PRAS4     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS4_M1PR_PRAS4(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS4 . LQOSEN0_PRAS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS4_LQOSEN0_PRAS4(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS4_LQOSEN0_PRAS4  VTSS_BIT(2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS4_LQOSEN0_PRAS4(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS4 . M0PR_PRAS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS4_M0PR_PRAS4(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS4_M0PR_PRAS4     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS4_M0PR_PRAS4(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Priority Register B for Target 0
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_PRBS4
 */
#define VTSS_HMATRIX2_MATRIX_PRBS4           VTSS_IOREG(VTSS_TO_HMATRIX2,0x29)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS4 . LQOSEN15_PRBS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS4_LQOSEN15_PRBS4(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS4_LQOSEN15_PRBS4  VTSS_BIT(30)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS4_LQOSEN15_PRBS4(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS4 . M15PR_PRBS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS4_M15PR_PRBS4(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS4_M15PR_PRBS4     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS4_M15PR_PRBS4(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS4 . LQOSEN14_PRBS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS4_LQOSEN14_PRBS4(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS4_LQOSEN14_PRBS4  VTSS_BIT(26)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS4_LQOSEN14_PRBS4(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS4 . M14PR_PRBS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS4_M14PR_PRBS4(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS4_M14PR_PRBS4     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS4_M14PR_PRBS4(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS4 . LQOSEN13_PRBS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS4_LQOSEN13_PRBS4(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS4_LQOSEN13_PRBS4  VTSS_BIT(22)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS4_LQOSEN13_PRBS4(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS4 . M13PR_PRBS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS4_M13PR_PRBS4(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS4_M13PR_PRBS4     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS4_M13PR_PRBS4(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS4 . LQOSEN12_PRBS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS4_LQOSEN12_PRBS4(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS4_LQOSEN12_PRBS4  VTSS_BIT(18)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS4_LQOSEN12_PRBS4(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS4 . M12PR_PRBS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS4_M12PR_PRBS4(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS4_M12PR_PRBS4     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS4_M12PR_PRBS4(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS4 . LQOSEN11_PRBS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS4_LQOSEN11_PRBS4(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS4_LQOSEN11_PRBS4  VTSS_BIT(14)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS4_LQOSEN11_PRBS4(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS4 . M11PR_PRBS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS4_M11PR_PRBS4(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS4_M11PR_PRBS4     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS4_M11PR_PRBS4(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS4 . LQOSEN10_PRBS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS4_LQOSEN10_PRBS4(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS4_LQOSEN10_PRBS4  VTSS_BIT(10)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS4_LQOSEN10_PRBS4(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS4 . M10PR_PRBS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS4_M10PR_PRBS4(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS4_M10PR_PRBS4     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS4_M10PR_PRBS4(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS4 . LQOSEN9_PRBS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS4_LQOSEN9_PRBS4(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS4_LQOSEN9_PRBS4  VTSS_BIT(6)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS4_LQOSEN9_PRBS4(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS4 . M9PR_PRBS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS4_M9PR_PRBS4(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS4_M9PR_PRBS4     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS4_M9PR_PRBS4(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS4 . LQOSEN8_PRBS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS4_LQOSEN8_PRBS4(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS4_LQOSEN8_PRBS4  VTSS_BIT(2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS4_LQOSEN8_PRBS4(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS4 . M8PR_PRBS4
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS4_M8PR_PRBS4(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS4_M8PR_PRBS4     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS4_M8PR_PRBS4(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Bus Matrix Priority Registers A For Targets
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_PRAS5
 */
#define VTSS_HMATRIX2_MATRIX_PRAS5           VTSS_IOREG(VTSS_TO_HMATRIX2,0x2a)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS5 . LQOSEN7_PRAS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS5_LQOSEN7_PRAS5(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS5_LQOSEN7_PRAS5  VTSS_BIT(30)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS5_LQOSEN7_PRAS5(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS5 . M7PR_PRAS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS5_M7PR_PRAS5(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS5_M7PR_PRAS5     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS5_M7PR_PRAS5(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS5 . LQOSEN6_PRAS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS5_LQOSEN6_PRAS5(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS5_LQOSEN6_PRAS5  VTSS_BIT(26)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS5_LQOSEN6_PRAS5(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS5 . M6PR_PRAS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS5_M6PR_PRAS5(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS5_M6PR_PRAS5     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS5_M6PR_PRAS5(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS5 . LQOSEN5_PRAS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS5_LQOSEN5_PRAS5(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS5_LQOSEN5_PRAS5  VTSS_BIT(22)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS5_LQOSEN5_PRAS5(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS5 . M5PR_PRAS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS5_M5PR_PRAS5(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS5_M5PR_PRAS5     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS5_M5PR_PRAS5(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS5 . LQOSEN4_PRAS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS5_LQOSEN4_PRAS5(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS5_LQOSEN4_PRAS5  VTSS_BIT(18)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS5_LQOSEN4_PRAS5(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS5 . M4PR_PRAS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS5_M4PR_PRAS5(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS5_M4PR_PRAS5     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS5_M4PR_PRAS5(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS5 . LQOSEN3_PRAS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS5_LQOSEN3_PRAS5(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS5_LQOSEN3_PRAS5  VTSS_BIT(14)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS5_LQOSEN3_PRAS5(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS5 . M3PR_PRAS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS5_M3PR_PRAS5(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS5_M3PR_PRAS5     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS5_M3PR_PRAS5(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS5 . LQOSEN2_PRAS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS5_LQOSEN2_PRAS5(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS5_LQOSEN2_PRAS5  VTSS_BIT(10)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS5_LQOSEN2_PRAS5(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS5 . M2PR_PRAS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS5_M2PR_PRAS5(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS5_M2PR_PRAS5     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS5_M2PR_PRAS5(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS5 . LQOSEN1_PRAS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS5_LQOSEN1_PRAS5(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS5_LQOSEN1_PRAS5  VTSS_BIT(6)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS5_LQOSEN1_PRAS5(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS5 . M1PR_PRAS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS5_M1PR_PRAS5(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS5_M1PR_PRAS5     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS5_M1PR_PRAS5(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS5 . LQOSEN0_PRAS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS5_LQOSEN0_PRAS5(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS5_LQOSEN0_PRAS5  VTSS_BIT(2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS5_LQOSEN0_PRAS5(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS5 . M0PR_PRAS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS5_M0PR_PRAS5(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS5_M0PR_PRAS5     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS5_M0PR_PRAS5(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Priority Register B for Target 0
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_PRBS5
 */
#define VTSS_HMATRIX2_MATRIX_PRBS5           VTSS_IOREG(VTSS_TO_HMATRIX2,0x2b)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS5 . LQOSEN15_PRBS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS5_LQOSEN15_PRBS5(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS5_LQOSEN15_PRBS5  VTSS_BIT(30)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS5_LQOSEN15_PRBS5(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS5 . M15PR_PRBS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS5_M15PR_PRBS5(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS5_M15PR_PRBS5     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS5_M15PR_PRBS5(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS5 . LQOSEN14_PRBS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS5_LQOSEN14_PRBS5(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS5_LQOSEN14_PRBS5  VTSS_BIT(26)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS5_LQOSEN14_PRBS5(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS5 . M14PR_PRBS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS5_M14PR_PRBS5(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS5_M14PR_PRBS5     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS5_M14PR_PRBS5(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS5 . LQOSEN13_PRBS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS5_LQOSEN13_PRBS5(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS5_LQOSEN13_PRBS5  VTSS_BIT(22)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS5_LQOSEN13_PRBS5(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS5 . M13PR_PRBS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS5_M13PR_PRBS5(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS5_M13PR_PRBS5     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS5_M13PR_PRBS5(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS5 . LQOSEN12_PRBS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS5_LQOSEN12_PRBS5(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS5_LQOSEN12_PRBS5  VTSS_BIT(18)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS5_LQOSEN12_PRBS5(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS5 . M12PR_PRBS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS5_M12PR_PRBS5(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS5_M12PR_PRBS5     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS5_M12PR_PRBS5(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS5 . LQOSEN11_PRBS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS5_LQOSEN11_PRBS5(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS5_LQOSEN11_PRBS5  VTSS_BIT(14)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS5_LQOSEN11_PRBS5(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS5 . M11PR_PRBS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS5_M11PR_PRBS5(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS5_M11PR_PRBS5     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS5_M11PR_PRBS5(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS5 . LQOSEN10_PRBS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS5_LQOSEN10_PRBS5(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS5_LQOSEN10_PRBS5  VTSS_BIT(10)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS5_LQOSEN10_PRBS5(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS5 . M10PR_PRBS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS5_M10PR_PRBS5(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS5_M10PR_PRBS5     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS5_M10PR_PRBS5(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS5 . LQOSEN9_PRBS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS5_LQOSEN9_PRBS5(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS5_LQOSEN9_PRBS5  VTSS_BIT(6)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS5_LQOSEN9_PRBS5(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS5 . M9PR_PRBS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS5_M9PR_PRBS5(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS5_M9PR_PRBS5     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS5_M9PR_PRBS5(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS5 . LQOSEN8_PRBS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS5_LQOSEN8_PRBS5(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS5_LQOSEN8_PRBS5  VTSS_BIT(2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS5_LQOSEN8_PRBS5(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS5 . M8PR_PRBS5
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS5_M8PR_PRBS5(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS5_M8PR_PRBS5     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS5_M8PR_PRBS5(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Bus Matrix Priority Registers A For Targets
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_PRAS6
 */
#define VTSS_HMATRIX2_MATRIX_PRAS6           VTSS_IOREG(VTSS_TO_HMATRIX2,0xa)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS6 . LQOSEN7_PRAS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS6_LQOSEN7_PRAS6(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS6_LQOSEN7_PRAS6  VTSS_BIT(30)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS6_LQOSEN7_PRAS6(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS6 . M7PR_PRAS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS6_M7PR_PRAS6(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS6_M7PR_PRAS6     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS6_M7PR_PRAS6(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS6 . LQOSEN6_PRAS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS6_LQOSEN6_PRAS6(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS6_LQOSEN6_PRAS6  VTSS_BIT(26)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS6_LQOSEN6_PRAS6(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS6 . M6PR_PRAS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS6_M6PR_PRAS6(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS6_M6PR_PRAS6     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS6_M6PR_PRAS6(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS6 . LQOSEN5_PRAS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS6_LQOSEN5_PRAS6(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS6_LQOSEN5_PRAS6  VTSS_BIT(22)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS6_LQOSEN5_PRAS6(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS6 . M5PR_PRAS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS6_M5PR_PRAS6(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS6_M5PR_PRAS6     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS6_M5PR_PRAS6(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS6 . LQOSEN4_PRAS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS6_LQOSEN4_PRAS6(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS6_LQOSEN4_PRAS6  VTSS_BIT(18)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS6_LQOSEN4_PRAS6(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS6 . M4PR_PRAS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS6_M4PR_PRAS6(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS6_M4PR_PRAS6     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS6_M4PR_PRAS6(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS6 . LQOSEN3_PRAS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS6_LQOSEN3_PRAS6(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS6_LQOSEN3_PRAS6  VTSS_BIT(14)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS6_LQOSEN3_PRAS6(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS6 . M3PR_PRAS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS6_M3PR_PRAS6(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS6_M3PR_PRAS6     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS6_M3PR_PRAS6(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS6 . LQOSEN2_PRAS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS6_LQOSEN2_PRAS6(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS6_LQOSEN2_PRAS6  VTSS_BIT(10)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS6_LQOSEN2_PRAS6(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS6 . M2PR_PRAS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS6_M2PR_PRAS6(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS6_M2PR_PRAS6     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS6_M2PR_PRAS6(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS6 . LQOSEN1_PRAS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS6_LQOSEN1_PRAS6(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS6_LQOSEN1_PRAS6  VTSS_BIT(6)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS6_LQOSEN1_PRAS6(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS6 . M1PR_PRAS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS6_M1PR_PRAS6(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS6_M1PR_PRAS6     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS6_M1PR_PRAS6(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS6 . LQOSEN0_PRAS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS6_LQOSEN0_PRAS6(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS6_LQOSEN0_PRAS6  VTSS_BIT(2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS6_LQOSEN0_PRAS6(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS6 . M0PR_PRAS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS6_M0PR_PRAS6(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS6_M0PR_PRAS6     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS6_M0PR_PRAS6(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Priority Register B for Target 0
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_PRBS6
 */
#define VTSS_HMATRIX2_MATRIX_PRBS6           VTSS_IOREG(VTSS_TO_HMATRIX2,0xb)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS6 . LQOSEN15_PRBS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS6_LQOSEN15_PRBS6(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS6_LQOSEN15_PRBS6  VTSS_BIT(30)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS6_LQOSEN15_PRBS6(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS6 . M15PR_PRBS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS6_M15PR_PRBS6(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS6_M15PR_PRBS6     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS6_M15PR_PRBS6(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS6 . LQOSEN14_PRBS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS6_LQOSEN14_PRBS6(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS6_LQOSEN14_PRBS6  VTSS_BIT(26)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS6_LQOSEN14_PRBS6(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS6 . M14PR_PRBS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS6_M14PR_PRBS6(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS6_M14PR_PRBS6     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS6_M14PR_PRBS6(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS6 . LQOSEN13_PRBS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS6_LQOSEN13_PRBS6(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS6_LQOSEN13_PRBS6  VTSS_BIT(22)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS6_LQOSEN13_PRBS6(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS6 . M13PR_PRBS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS6_M13PR_PRBS6(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS6_M13PR_PRBS6     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS6_M13PR_PRBS6(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS6 . LQOSEN12_PRBS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS6_LQOSEN12_PRBS6(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS6_LQOSEN12_PRBS6  VTSS_BIT(18)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS6_LQOSEN12_PRBS6(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS6 . M12PR_PRBS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS6_M12PR_PRBS6(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS6_M12PR_PRBS6     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS6_M12PR_PRBS6(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS6 . LQOSEN11_PRBS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS6_LQOSEN11_PRBS6(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS6_LQOSEN11_PRBS6  VTSS_BIT(14)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS6_LQOSEN11_PRBS6(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS6 . M11PR_PRBS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS6_M11PR_PRBS6(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS6_M11PR_PRBS6     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS6_M11PR_PRBS6(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS6 . LQOSEN10_PRBS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS6_LQOSEN10_PRBS6(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS6_LQOSEN10_PRBS6  VTSS_BIT(10)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS6_LQOSEN10_PRBS6(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS6 . M10PR_PRBS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS6_M10PR_PRBS6(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS6_M10PR_PRBS6     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS6_M10PR_PRBS6(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS6 . LQOSEN9_PRBS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS6_LQOSEN9_PRBS6(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS6_LQOSEN9_PRBS6  VTSS_BIT(6)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS6_LQOSEN9_PRBS6(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS6 . M9PR_PRBS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS6_M9PR_PRBS6(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS6_M9PR_PRBS6     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS6_M9PR_PRBS6(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS6 . LQOSEN8_PRBS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS6_LQOSEN8_PRBS6(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS6_LQOSEN8_PRBS6  VTSS_BIT(2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS6_LQOSEN8_PRBS6(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS6 . M8PR_PRBS6
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS6_M8PR_PRBS6(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS6_M8PR_PRBS6     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS6_M8PR_PRBS6(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Bus Matrix Priority Registers A For Targets
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_PRAS7
 */
#define VTSS_HMATRIX2_MATRIX_PRAS7           VTSS_IOREG(VTSS_TO_HMATRIX2,0xc)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS7 . LQOSEN7_PRAS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS7_LQOSEN7_PRAS7(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS7_LQOSEN7_PRAS7  VTSS_BIT(30)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS7_LQOSEN7_PRAS7(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS7 . M7PR_PRAS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS7_M7PR_PRAS7(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS7_M7PR_PRAS7     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS7_M7PR_PRAS7(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS7 . LQOSEN6_PRAS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS7_LQOSEN6_PRAS7(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS7_LQOSEN6_PRAS7  VTSS_BIT(26)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS7_LQOSEN6_PRAS7(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS7 . M6PR_PRAS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS7_M6PR_PRAS7(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS7_M6PR_PRAS7     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS7_M6PR_PRAS7(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS7 . LQOSEN5_PRAS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS7_LQOSEN5_PRAS7(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS7_LQOSEN5_PRAS7  VTSS_BIT(22)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS7_LQOSEN5_PRAS7(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS7 . M5PR_PRAS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS7_M5PR_PRAS7(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS7_M5PR_PRAS7     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS7_M5PR_PRAS7(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS7 . LQOSEN4_PRAS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS7_LQOSEN4_PRAS7(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS7_LQOSEN4_PRAS7  VTSS_BIT(18)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS7_LQOSEN4_PRAS7(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS7 . M4PR_PRAS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS7_M4PR_PRAS7(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS7_M4PR_PRAS7     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS7_M4PR_PRAS7(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS7 . LQOSEN3_PRAS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS7_LQOSEN3_PRAS7(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS7_LQOSEN3_PRAS7  VTSS_BIT(14)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS7_LQOSEN3_PRAS7(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS7 . M3PR_PRAS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS7_M3PR_PRAS7(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS7_M3PR_PRAS7     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS7_M3PR_PRAS7(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x0: Disable
 * propagation of Latency Quality of Service from the Initiator x to the
 * Target and apply MxPR priority for all accessfrom Initiator x to the
 * Target.1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS7 . LQOSEN2_PRAS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS7_LQOSEN2_PRAS7(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS7_LQOSEN2_PRAS7  VTSS_BIT(10)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS7_LQOSEN2_PRAS7(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS7 . M2PR_PRAS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS7_M2PR_PRAS7(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS7_M2PR_PRAS7     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS7_M2PR_PRAS7(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS7 . LQOSEN1_PRAS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS7_LQOSEN1_PRAS7(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS7_LQOSEN1_PRAS7  VTSS_BIT(6)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS7_LQOSEN1_PRAS7(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS7 . M1PR_PRAS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS7_M1PR_PRAS7(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS7_M1PR_PRAS7     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS7_M1PR_PRAS7(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS7 . LQOSEN0_PRAS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS7_LQOSEN0_PRAS7(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS7_LQOSEN0_PRAS7  VTSS_BIT(2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS7_LQOSEN0_PRAS7(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).See Arbitration
 * Priority Scheme on page 6 for details.This priority is used by default
 * any time that the Latency Quality of Service propagation from the
 * Initiator x is not used or notavailable. Set this field to 0x0 when the
 * LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRAS7 . M0PR_PRAS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRAS7_M0PR_PRAS7(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRAS7_M0PR_PRAS7     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRAS7_M0PR_PRAS7(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Priority Register B for Target 0
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_PRBS7
 */
#define VTSS_HMATRIX2_MATRIX_PRBS7           VTSS_IOREG(VTSS_TO_HMATRIX2,0xd)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS7 . LQOSEN15_PRBS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS7_LQOSEN15_PRBS7(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS7_LQOSEN15_PRBS7  VTSS_BIT(30)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS7_LQOSEN15_PRBS7(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS7 . M15PR_PRBS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS7_M15PR_PRBS7(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS7_M15PR_PRBS7     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS7_M15PR_PRBS7(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS7 . LQOSEN14_PRBS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS7_LQOSEN14_PRBS7(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS7_LQOSEN14_PRBS7  VTSS_BIT(26)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS7_LQOSEN14_PRBS7(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS7 . M14PR_PRBS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS7_M14PR_PRBS7(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS7_M14PR_PRBS7     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS7_M14PR_PRBS7(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS7 . LQOSEN13_PRBS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS7_LQOSEN13_PRBS7(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS7_LQOSEN13_PRBS7  VTSS_BIT(22)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS7_LQOSEN13_PRBS7(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS7 . M13PR_PRBS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS7_M13PR_PRBS7(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS7_M13PR_PRBS7     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS7_M13PR_PRBS7(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS7 . LQOSEN12_PRBS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS7_LQOSEN12_PRBS7(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS7_LQOSEN12_PRBS7  VTSS_BIT(18)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS7_LQOSEN12_PRBS7(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS7 . M12PR_PRBS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS7_M12PR_PRBS7(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS7_M12PR_PRBS7     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS7_M12PR_PRBS7(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS7 . LQOSEN11_PRBS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS7_LQOSEN11_PRBS7(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS7_LQOSEN11_PRBS7  VTSS_BIT(14)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS7_LQOSEN11_PRBS7(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS7 . M11PR_PRBS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS7_M11PR_PRBS7(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS7_M11PR_PRBS7     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS7_M11PR_PRBS7(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS7 . LQOSEN10_PRBS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS7_LQOSEN10_PRBS7(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS7_LQOSEN10_PRBS7  VTSS_BIT(10)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS7_LQOSEN10_PRBS7(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS7 . M10PR_PRBS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS7_M10PR_PRBS7(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS7_M10PR_PRBS7     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS7_M10PR_PRBS7(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS7 . LQOSEN9_PRBS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS7_LQOSEN9_PRBS7(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS7_LQOSEN9_PRBS7  VTSS_BIT(6)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS7_LQOSEN9_PRBS7(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS7 . M9PR_PRBS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS7_M9PR_PRBS7(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS7_M9PR_PRBS7     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS7_M9PR_PRBS7(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * LQOSENx: Latency Quality of Service Enable for Initiator x
 *
 * \details
 * 0: Disable propagation of Latency Quality of Service from the Initiator
 * x to the Target and apply MxPR priority for all access
 * from Initiator x to the Target.
 * 1: Enable the propagation of Latency Quality of Service from the
 * Initiator x to the Target if supported by the Initiator x.
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS7 . LQOSEN8_PRBS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS7_LQOSEN8_PRBS7(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS7_LQOSEN8_PRBS7  VTSS_BIT(2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS7_LQOSEN8_PRBS7(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * MxPR: Initiator x PriorityFixed priority of Initiator x for accessing
 * the selected target. The higher the number, the higher the priority.All
 * the initiators programmed with the same MxPR value for the target make
 * up a priority pool.Round-robin arbitration is used in the lowest (MxPR =
 * 0) and highest (MxPR = 3) priority pools.Fixed priority is used in
 * intermediate priority pools (MxPR = 1) and (MxPR = 2).This priority is
 * used by default any time that the Latency Quality of Service propagation
 * from the Initiator x is not used or notavailable. Set this field to 0x0
 * when the LQOSENx bit is set to 1.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_PRBS7 . M8PR_PRBS7
 */
#define  VTSS_F_HMATRIX2_MATRIX_PRBS7_M8PR_PRBS7(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HMATRIX2_MATRIX_PRBS7_M8PR_PRBS7     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HMATRIX2_MATRIX_PRBS7_M8PR_PRBS7(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Initiator Remap Control Register
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MRCR
 */
#define VTSS_HMATRIX2_MATRIX_MRCR            VTSS_IOREG(VTSS_TO_HMATRIX2,0x40)

/**
 * \brief
 * RCBx: Remap Command Bit for Initiator x
 *
 * \details
 * 0: Disable remapped address decoding for the selected Initiator
 * 1: Enable remapped address decoding for the selected Initiator
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_MRCR . RCB0
 */
#define  VTSS_F_HMATRIX2_MATRIX_MRCR_RCB0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HMATRIX2_MATRIX_MRCR_RCB0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HMATRIX2_MATRIX_MRCR_RCB0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Special Function Register 0
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SFR0
 */
#define VTSS_HMATRIX2_MATRIX_SFR0            VTSS_IOREG(VTSS_TO_HMATRIX2,0x44)

/**
 * \brief
 * SFR: Special Function Register FieldsThe SFR fields are a set of D-type
 * Flip-flops which are only connected to outputs of the Bus Matrix.They
 * are readable/writable from the User Interface and may be used to
 * implement Configuration Registers which cannotbe implemented in any of
 * the other embedded peripherals of the product. Each bit of the SFR may
 * be removed by hardwarecustomizing at synthesis if not used.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SFR0 . SFR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SFR0_SFR0(x)  (x)
#define  VTSS_M_HMATRIX2_MATRIX_SFR0_SFR0     0xffffffff
#define  VTSS_X_HMATRIX2_MATRIX_SFR0_SFR0(x)  (x)


/**
 * \brief Special Function Register 0
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SFR1
 */
#define VTSS_HMATRIX2_MATRIX_SFR1            VTSS_IOREG(VTSS_TO_HMATRIX2,0x45)

/**
 * \brief
 * SFR: Special Function Register FieldsThe SFR fields are a set of D-type
 * Flip-flops which are only connected to outputs of the Bus Matrix.They
 * are readable/writable from the User Interface and may be used to
 * implement Configuration Registers which cannotbe implemented in any of
 * the other embedded peripherals of the product. Each bit of the SFR may
 * be removed by hardwarecustomizing at synthesis if not used.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SFR1 . SFR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SFR1_SFR1(x)  (x)
#define  VTSS_M_HMATRIX2_MATRIX_SFR1_SFR1     0xffffffff
#define  VTSS_X_HMATRIX2_MATRIX_SFR1_SFR1(x)  (x)


/**
 * \brief Special Function Register 0
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SFR2
 */
#define VTSS_HMATRIX2_MATRIX_SFR2            VTSS_IOREG(VTSS_TO_HMATRIX2,0x46)

/**
 * \brief
 * SFR: Special Function Register FieldsThe SFR fields are a set of D-type
 * Flip-flops which are only connected to outputs of the Bus Matrix.They
 * are readable/writable from the User Interface and may be used to
 * implement Configuration Registers which cannotbe implemented in any of
 * the other embedded peripherals of the product. Each bit of the SFR may
 * be removed by hardwarecustomizing at synthesis if not used.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SFR2 . SFR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SFR2_SFR2(x)  (x)
#define  VTSS_M_HMATRIX2_MATRIX_SFR2_SFR2     0xffffffff
#define  VTSS_X_HMATRIX2_MATRIX_SFR2_SFR2(x)  (x)


/**
 * \brief Special Function Register 0
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SFR3
 */
#define VTSS_HMATRIX2_MATRIX_SFR3            VTSS_IOREG(VTSS_TO_HMATRIX2,0x47)

/**
 * \brief
 * SFR: Special Function Register FieldsThe SFR fields are a set of D-type
 * Flip-flops which are only connected to outputs of the Bus Matrix.They
 * are readable/writable from the User Interface and may be used to
 * implement Configuration Registers which cannotbe implemented in any of
 * the other embedded peripherals of the product. Each bit of the SFR may
 * be removed by hardwarecustomizing at synthesis if not used.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SFR3 . SFR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SFR3_SFR3(x)  (x)
#define  VTSS_M_HMATRIX2_MATRIX_SFR3_SFR3     0xffffffff
#define  VTSS_X_HMATRIX2_MATRIX_SFR3_SFR3(x)  (x)


/**
 * \brief Special Function Register 0
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SFR4
 */
#define VTSS_HMATRIX2_MATRIX_SFR4            VTSS_IOREG(VTSS_TO_HMATRIX2,0x48)

/**
 * \brief
 * SFR: Special Function Register FieldsThe SFR fields are a set of D-type
 * Flip-flops which are only connected to outputs of the Bus Matrix.They
 * are readable/writable from the User Interface and may be used to
 * implement Configuration Registers which cannotbe implemented in any of
 * the other embedded peripherals of the product. Each bit of the SFR may
 * be removed by hardwarecustomizing at synthesis if not used.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SFR4 . SFR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SFR4_SFR4(x)  (x)
#define  VTSS_M_HMATRIX2_MATRIX_SFR4_SFR4     0xffffffff
#define  VTSS_X_HMATRIX2_MATRIX_SFR4_SFR4(x)  (x)


/**
 * \brief Special Function Register 0
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SFR5
 */
#define VTSS_HMATRIX2_MATRIX_SFR5            VTSS_IOREG(VTSS_TO_HMATRIX2,0x49)

/**
 * \brief
 * SFR: Special Function Register FieldsThe SFR fields are a set of D-type
 * Flip-flops which are only connected to outputs of the Bus Matrix.They
 * are readable/writable from the User Interface and may be used to
 * implement Configuration Registers which cannotbe implemented in any of
 * the other embedded peripherals of the product. Each bit of the SFR may
 * be removed by hardwarecustomizing at synthesis if not used.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SFR5 . SFR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SFR5_SFR5(x)  (x)
#define  VTSS_M_HMATRIX2_MATRIX_SFR5_SFR5     0xffffffff
#define  VTSS_X_HMATRIX2_MATRIX_SFR5_SFR5(x)  (x)


/**
 * \brief Special Function Register 0
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SFR6
 */
#define VTSS_HMATRIX2_MATRIX_SFR6            VTSS_IOREG(VTSS_TO_HMATRIX2,0x4a)

/**
 * \brief
 * SFR: Special Function Register FieldsThe SFR fields are a set of D-type
 * Flip-flops which are only connected to outputs of the Bus Matrix.They
 * are readable/writable from the User Interface and may be used to
 * implement Configuration Registers which cannotbe implemented in any of
 * the other embedded peripherals of the product. Each bit of the SFR may
 * be removed by hardwarecustomizing at synthesis if not used.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SFR6 . SFR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SFR6_SFR6(x)  (x)
#define  VTSS_M_HMATRIX2_MATRIX_SFR6_SFR6     0xffffffff
#define  VTSS_X_HMATRIX2_MATRIX_SFR6_SFR6(x)  (x)


/**
 * \brief Special Function Register 0
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SFR7
 */
#define VTSS_HMATRIX2_MATRIX_SFR7            VTSS_IOREG(VTSS_TO_HMATRIX2,0xe)

/**
 * \brief
 * SFR: Special Function Register FieldsThe SFR fields are a set of D-type
 * Flip-flops which are only connected to outputs of the Bus Matrix.They
 * are readable/writable from the User Interface and may be used to
 * implement Configuration Registers which cannotbe implemented in any of
 * the other embedded peripherals of the product. Each bit of the SFR may
 * be removed by hardwarecustomizing at synthesis if not used.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SFR7 . SFR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SFR7_SFR7(x)  (x)
#define  VTSS_M_HMATRIX2_MATRIX_SFR7_SFR7     0xffffffff
#define  VTSS_X_HMATRIX2_MATRIX_SFR7_SFR7(x)  (x)


/**
 * \brief Initiator Error Interrupt Enable Register
 *
 * \details
 * Write-only
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.

 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MEIER
 */
#define VTSS_HMATRIX2_MATRIX_MEIER           VTSS_IOREG(VTSS_TO_HMATRIX2,0x54)

/**
 * \brief
 * MERRx: Initiator x Access Error0: No effect.1: Enable Initiator x Access
 * Error interrupt source.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_MEIER . MERR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_MEIER_MERR0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HMATRIX2_MATRIX_MEIER_MERR0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HMATRIX2_MATRIX_MEIER_MERR0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Initiator Error Interrupt Disable Register
 *
 * \details
 * Write-only.
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MEIDR
 */
#define VTSS_HMATRIX2_MATRIX_MEIDR           VTSS_IOREG(VTSS_TO_HMATRIX2,0x55)

/**
 * \brief
 * MERRx: Initiator x Access Error0: No effect.1: Disable Initiator x
 * Access Error interrupt source.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_MEIDR . MERR0_MEIDR
 */
#define  VTSS_F_HMATRIX2_MATRIX_MEIDR_MERR0_MEIDR(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HMATRIX2_MATRIX_MEIDR_MERR0_MEIDR     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HMATRIX2_MATRIX_MEIDR_MERR0_MEIDR(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Initiator Error Interrupt Mask Register
 *
 * \details
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MEIMR
 */
#define VTSS_HMATRIX2_MATRIX_MEIMR           VTSS_IOREG(VTSS_TO_HMATRIX2,0x56)

/**
 * \brief
 * MERRx: Initiator x Access Error0: Initiator x Access Error does not
 * trigger any interrupt.1: Initiator x Access Error triggers the Bus
 * Matrix interrupt line.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_MEIMR . MERR0_MEIMR
 */
#define  VTSS_F_HMATRIX2_MATRIX_MEIMR_MERR0_MEIMR(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HMATRIX2_MATRIX_MEIMR_MERR0_MEIMR     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HMATRIX2_MATRIX_MEIMR_MERR0_MEIMR(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Initiator Error Status Register
 *
 * \details
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MESR
 */
#define VTSS_HMATRIX2_MATRIX_MESR            VTSS_IOREG(VTSS_TO_HMATRIX2,0x57)

/**
 * \brief
 * MERRx: Initiator x Access Error0: No Initiator Access Error has occurred
 * since the last read of the MATRIX_MESR.1: At least one Initiator Access
 * Error has occurred since the last read of the MATRIX_MESR.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_MESR . MERR0_MESR
 */
#define  VTSS_F_HMATRIX2_MATRIX_MESR_MERR0_MESR(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HMATRIX2_MATRIX_MESR_MERR0_MESR     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HMATRIX2_MATRIX_MESR_MERR0_MESR(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Initiator Error Address Registers
 *
 * \details
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MEAR0
 */
#define VTSS_HMATRIX2_MATRIX_MEAR0           VTSS_IOREG(VTSS_TO_HMATRIX2,0x58)

/**
 * \brief
 * ERRADD: Initiator Error AddressInitiator Last Access Error Address
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_MEAR0 . ERRADD0
 */
#define  VTSS_F_HMATRIX2_MATRIX_MEAR0_ERRADD0(x)  (x)
#define  VTSS_M_HMATRIX2_MATRIX_MEAR0_ERRADD0     0xffffffff
#define  VTSS_X_HMATRIX2_MATRIX_MEAR0_ERRADD0(x)  (x)


/**
 * \brief Initiator Error Address Registers
 *
 * \details
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MEAR1
 */
#define VTSS_HMATRIX2_MATRIX_MEAR1           VTSS_IOREG(VTSS_TO_HMATRIX2,0x59)

/**
 * \brief
 * ERRADD: Initiator Error AddressInitiator Last Access Error Address
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_MEAR1 . ERRADD1
 */
#define  VTSS_F_HMATRIX2_MATRIX_MEAR1_ERRADD1(x)  (x)
#define  VTSS_M_HMATRIX2_MATRIX_MEAR1_ERRADD1     0xffffffff
#define  VTSS_X_HMATRIX2_MATRIX_MEAR1_ERRADD1(x)  (x)


/**
 * \brief Initiator Error Address Registers
 *
 * \details
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MEAR2
 */
#define VTSS_HMATRIX2_MATRIX_MEAR2           VTSS_IOREG(VTSS_TO_HMATRIX2,0x5a)

/**
 * \brief
 * ERRADD: Initiator Error AddressInitiator Last Access Error Address
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_MEAR2 . ERRADD2
 */
#define  VTSS_F_HMATRIX2_MATRIX_MEAR2_ERRADD2(x)  (x)
#define  VTSS_M_HMATRIX2_MATRIX_MEAR2_ERRADD2     0xffffffff
#define  VTSS_X_HMATRIX2_MATRIX_MEAR2_ERRADD2(x)  (x)


/**
 * \brief Initiator Error Address Registers
 *
 * \details
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MEAR3
 */
#define VTSS_HMATRIX2_MATRIX_MEAR3           VTSS_IOREG(VTSS_TO_HMATRIX2,0x5b)

/**
 * \brief
 * ERRADD: Initiator Error AddressInitiator Last Access Error Address
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_MEAR3 . ERRADD3
 */
#define  VTSS_F_HMATRIX2_MATRIX_MEAR3_ERRADD3(x)  (x)
#define  VTSS_M_HMATRIX2_MATRIX_MEAR3_ERRADD3     0xffffffff
#define  VTSS_X_HMATRIX2_MATRIX_MEAR3_ERRADD3(x)  (x)


/**
 * \brief Initiator Error Address Registers
 *
 * \details
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MEAR4
 */
#define VTSS_HMATRIX2_MATRIX_MEAR4           VTSS_IOREG(VTSS_TO_HMATRIX2,0x5c)

/**
 * \brief
 * ERRADD: Initiator Error AddressInitiator Last Access Error Address
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_MEAR4 . ERRADD4
 */
#define  VTSS_F_HMATRIX2_MATRIX_MEAR4_ERRADD4(x)  (x)
#define  VTSS_M_HMATRIX2_MATRIX_MEAR4_ERRADD4     0xffffffff
#define  VTSS_X_HMATRIX2_MATRIX_MEAR4_ERRADD4(x)  (x)


/**
 * \brief Initiator Error Address Registers
 *
 * \details
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MEAR5
 */
#define VTSS_HMATRIX2_MATRIX_MEAR5           VTSS_IOREG(VTSS_TO_HMATRIX2,0x5d)

/**
 * \brief
 * ERRADD: Initiator Error AddressInitiator Last Access Error Address
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_MEAR5 . ERRADD5
 */
#define  VTSS_F_HMATRIX2_MATRIX_MEAR5_ERRADD5(x)  (x)
#define  VTSS_M_HMATRIX2_MATRIX_MEAR5_ERRADD5     0xffffffff
#define  VTSS_X_HMATRIX2_MATRIX_MEAR5_ERRADD5(x)  (x)


/**
 * \brief Initiator Error Address Registers
 *
 * \details
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MEAR6
 */
#define VTSS_HMATRIX2_MATRIX_MEAR6           VTSS_IOREG(VTSS_TO_HMATRIX2,0xf)

/**
 * \brief
 * ERRADD: Initiator Error AddressInitiator Last Access Error Address
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_MEAR6 . ERRADD6
 */
#define  VTSS_F_HMATRIX2_MATRIX_MEAR6_ERRADD6(x)  (x)
#define  VTSS_M_HMATRIX2_MATRIX_MEAR6_ERRADD6     0xffffffff
#define  VTSS_X_HMATRIX2_MATRIX_MEAR6_ERRADD6(x)  (x)


/**
 * \brief Initiator Error Address Registers
 *
 * \details
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MEAR7
 */
#define VTSS_HMATRIX2_MATRIX_MEAR7           VTSS_IOREG(VTSS_TO_HMATRIX2,0x17)

/**
 * \brief
 * ERRADD: Initiator Error AddressInitiator Last Access Error Address
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_MEAR7 . ERRADD7
 */
#define  VTSS_F_HMATRIX2_MATRIX_MEAR7_ERRADD7(x)  (x)
#define  VTSS_M_HMATRIX2_MATRIX_MEAR7_ERRADD7     0xffffffff
#define  VTSS_X_HMATRIX2_MATRIX_MEAR7_ERRADD7(x)  (x)


/**
 * \brief Initiator Error Address Registers
 *
 * \details
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_MEAR8
 */
#define VTSS_HMATRIX2_MATRIX_MEAR8           VTSS_IOREG(VTSS_TO_HMATRIX2,0x18)

/**
 * \brief
 * ERRADD: Initiator Error AddressInitiator Last Access Error Address
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_MEAR8 . ERRADD8
 */
#define  VTSS_F_HMATRIX2_MATRIX_MEAR8_ERRADD8(x)  (x)
#define  VTSS_M_HMATRIX2_MATRIX_MEAR8_ERRADD8     0xffffffff
#define  VTSS_X_HMATRIX2_MATRIX_MEAR8_ERRADD8(x)  (x)


/**
 * \brief Write Protection Mode Register
 *
 * \details
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_WPMR
 */
#define VTSS_HMATRIX2_MATRIX_WPMR            VTSS_IOREG(VTSS_TO_HMATRIX2,0x79)

/**
 * \brief
 * WPKEY: Write Protection Key0x4D4154 PASSWDWriting any other value in
 * this field aborts the write operation of the WPEN bit.Always reads as 0.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_WPMR . WPKEY
 */
#define  VTSS_F_HMATRIX2_MATRIX_WPMR_WPKEY(x)  VTSS_ENCODE_BITFIELD(x,8,16)
#define  VTSS_M_HMATRIX2_MATRIX_WPMR_WPKEY     VTSS_ENCODE_BITMASK(8,16)
#define  VTSS_X_HMATRIX2_MATRIX_WPMR_WPKEY(x)  VTSS_EXTRACT_BITFIELD(x,8,16)

/**
 * \brief
 * WPEN: Write Protection Enable0: Disables the write protection if WPKEY
 * corresponds to 0x4D4154 (MAT in ASCII).1: Enables the write protection
 * if WPKEY corresponds to 0x4D4154 (MAT in ASCII).
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_WPMR . WPEN
 */
#define  VTSS_F_HMATRIX2_MATRIX_WPMR_WPEN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HMATRIX2_MATRIX_WPMR_WPEN     VTSS_BIT(0)
#define  VTSS_X_HMATRIX2_MATRIX_WPMR_WPEN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Write Protection Status Register
 *
 * \details
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_WPSR
 */
#define VTSS_HMATRIX2_MATRIX_WPSR            VTSS_IOREG(VTSS_TO_HMATRIX2,0x7a)

/**
 * \brief
 * WPVSRC: Write Protection Violation SourceWhen WPVS = 1, WPVSRC indicates
 * the register address offset at which a write access has been attempted.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_WPSR . WPVSRC
 */
#define  VTSS_F_HMATRIX2_MATRIX_WPSR_WPVSRC(x)  VTSS_ENCODE_BITFIELD(x,8,16)
#define  VTSS_M_HMATRIX2_MATRIX_WPSR_WPVSRC     VTSS_ENCODE_BITMASK(8,16)
#define  VTSS_X_HMATRIX2_MATRIX_WPSR_WPVSRC(x)  VTSS_EXTRACT_BITFIELD(x,8,16)

/**
 * \brief
 * WPVS: Write Protection Violation Status0: No write protection violation
 * has occurred since the last write of the MATRIX_WPMR.1: A write
 * protection violation has occurred since the last write of the
 * MATRIX_WPMR. If this violation is an unauthorizedattempt to write a
 * protected register, the associated violation is reported into field
 * WPVSRC.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_WPSR . WPVS
 */
#define  VTSS_F_HMATRIX2_MATRIX_WPSR_WPVS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HMATRIX2_MATRIX_WPSR_WPVS     VTSS_BIT(0)
#define  VTSS_X_HMATRIX2_MATRIX_WPSR_WPVS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Bus Matrix Version Register
 *
 * \details
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_VERSION
 */
#define VTSS_HMATRIX2_MATRIX_VERSION         VTSS_IOREG(VTSS_TO_HMATRIX2,0x7f)

/**
 * \brief
 * MFN: Metal Fix NumberReserved Value subject to change. No functionality
 * associated.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_VERSION . MFN
 */
#define  VTSS_F_HMATRIX2_MATRIX_VERSION_MFN(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_HMATRIX2_MATRIX_VERSION_MFN     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_HMATRIX2_MATRIX_VERSION_MFN(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * VERSION: Matrix VersionReserved Value subject to change. No
 * functionality associated. This is the Atmel internal version of the
 * macrocell.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_VERSION . VERSION
 */
#define  VTSS_F_HMATRIX2_MATRIX_VERSION_VERSION(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_HMATRIX2_MATRIX_VERSION_VERSION     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_HMATRIX2_MATRIX_VERSION_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief Security Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * WRNSECHx / RDNSECHx Non-Secure Access Secure Access
 * 00 Denied Write - Read
 * 01 Read Write - Read
 * 10 Write Write - Read
 * 11 Write - Read Write - Read
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SSR0
 */
#define VTSS_HMATRIX2_MATRIX_SSR0            VTSS_IOREG(VTSS_TO_HMATRIX2,0x80)

/**
 * \brief
 * WRNSECHx: Write Not Secured for HSELx Security Region0: The HSELx AHB
 * target security region is split into one Write Secured and one Write Not
 * Secured area, according toLANSECHx and MATRIX_SASSR / SASPLITx. That is,
 * the so defined securable high or low area is Secured for Writeaccess.1:
 * The HSELx AHB target security region is Not Secured for Write access.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR0 . WRNSECH0_SSR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR0_WRNSECH0_SSR0(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR0_WRNSECH0_SSR0     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR0_WRNSECH0_SSR0(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * RDNSECHx: Read Not Secured for HSELx Security Region0: The HSELx AHB
 * target security region is split into one Read Secured and one Read Not
 * Secured area, according toLANSECHx and MATRIX_SASSR / SASPLITx. That is,
 * the so defined securable high or low area is Secured for Readaccess.1:
 * The HSELx AHB target security region is Not Secured for Read access.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR0 . RDNSECH0_SSR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR0_RDNSECH0_SSR0(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR0_RDNSECH0_SSR0     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR0_RDNSECH0_SSR0(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * LANSECHx: Low Area Not Secured in HSELx Security Region0: The security
 * of the HSELx AHB target area laying below the corresponding MATRIX_SASSR
 * / SASPLITx boundary isconfigured according to RDNSECHx and WRNSECHx. The
 * whole remaining HSELx upper address space is configured asNot Secured
 * access.1: The HSELx AHB target address area laying below the
 * corresponding MATRIX_SASSR / SASPLITx boundary is configuredas Not
 * Secured access, and the whole remaining upper address space according to
 * RDNSECHx and WRNSECHx.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR0 . LANSECH0_SSR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR0_LANSECH0_SSR0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR0_LANSECH0_SSR0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR0_LANSECH0_SSR0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Security Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * WRNSECHx / RDNSECHx Non-Secure Access Secure Access
 * 00 Denied Write - Read
 * 01 Read Write - Read
 * 10 Write Write - Read
 * 11 Write - Read Write - Read
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SSR1
 */
#define VTSS_HMATRIX2_MATRIX_SSR1            VTSS_IOREG(VTSS_TO_HMATRIX2,0x81)

/**
 * \brief
 * WRNSECHx: Write Not Secured for HSELx Security Region0: The HSELx AHB
 * target security region is split into one Write Secured and one Write Not
 * Secured area, according toLANSECHx and MATRIX_SASSR / SASPLITx. That is,
 * the so defined securable high or low area is Secured for Writeaccess.1:
 * The HSELx AHB target security region is Not Secured for Write access.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR1 . WRNSECH0_SSR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR1_WRNSECH0_SSR1(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR1_WRNSECH0_SSR1     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR1_WRNSECH0_SSR1(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * RDNSECHx: Read Not Secured for HSELx Security Region0: The HSELx AHB
 * target security region is split into one Read Secured and one Read Not
 * Secured area, according toLANSECHx and MATRIX_SASSR / SASPLITx. That is,
 * the so defined securable high or low area is Secured for Readaccess.1:
 * The HSELx AHB target security region is Not Secured for Read access.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR1 . RDNSECH0_SSR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR1_RDNSECH0_SSR1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR1_RDNSECH0_SSR1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR1_RDNSECH0_SSR1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * LANSECHx: Low Area Not Secured in HSELx Security Region0: The security
 * of the HSELx AHB target area laying below the corresponding MATRIX_SASSR
 * / SASPLITx boundary isconfigured according to RDNSECHx and WRNSECHx. The
 * whole remaining HSELx upper address space is configured asNot Secured
 * access.1: The HSELx AHB target address area laying below the
 * corresponding MATRIX_SASSR / SASPLITx boundary is configuredas Not
 * Secured access, and the whole remaining upper address space according to
 * RDNSECHx and WRNSECHx.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR1 . LANSECH0_SSR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR1_LANSECH0_SSR1(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR1_LANSECH0_SSR1     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR1_LANSECH0_SSR1(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Security Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * WRNSECHx / RDNSECHx Non-Secure Access Secure Access
 * 00 Denied Write - Read
 * 01 Read Write - Read
 * 10 Write Write - Read
 * 11 Write - Read Write - Read
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SSR2
 */
#define VTSS_HMATRIX2_MATRIX_SSR2            VTSS_IOREG(VTSS_TO_HMATRIX2,0x82)

/**
 * \brief
 * WRNSECHx: Write Not Secured for HSELx Security Region0: The HSELx AHB
 * target security region is split into one Write Secured and one Write Not
 * Secured area, according toLANSECHx and MATRIX_SASSR / SASPLITx. That is,
 * the so defined securable high or low area is Secured for Writeaccess.1:
 * The HSELx AHB target security region is Not Secured for Write access.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR2 . WRNSECH0_SSR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR2_WRNSECH0_SSR2(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR2_WRNSECH0_SSR2     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR2_WRNSECH0_SSR2(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * RDNSECHx: Read Not Secured for HSELx Security Region0: The HSELx AHB
 * target security region is split into one Read Secured and one Read Not
 * Secured area, according toLANSECHx and MATRIX_SASSR / SASPLITx. That is,
 * the so defined securable high or low area is Secured for Readaccess.1:
 * The HSELx AHB target security region is Not Secured for Read access.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR2 . RDNSECH0_SSR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR2_RDNSECH0_SSR2(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR2_RDNSECH0_SSR2     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR2_RDNSECH0_SSR2(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * LANSECHx: Low Area Not Secured in HSELx Security Region0: The security
 * of the HSELx AHB target area laying below the corresponding MATRIX_SASSR
 * / SASPLITx boundary isconfigured according to RDNSECHx and WRNSECHx. The
 * whole remaining HSELx upper address space is configured asNot Secured
 * access.1: The HSELx AHB target address area laying below the
 * corresponding MATRIX_SASSR / SASPLITx boundary is configuredas Not
 * Secured access, and the whole remaining upper address space according to
 * RDNSECHx and WRNSECHx.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR2 . LANSECH0_SSR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR2_LANSECH0_SSR2(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR2_LANSECH0_SSR2     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR2_LANSECH0_SSR2(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Security Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * WRNSECHx / RDNSECHx Non-Secure Access Secure Access
 * 00 Denied Write - Read
 * 01 Read Write - Read
 * 10 Write Write - Read
 * 11 Write - Read Write - Read
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SSR3
 */
#define VTSS_HMATRIX2_MATRIX_SSR3            VTSS_IOREG(VTSS_TO_HMATRIX2,0x83)

/**
 * \brief
 * WRNSECHx: Write Not Secured for HSELx Security Region0: The HSELx AHB
 * target security region is split into one Write Secured and one Write Not
 * Secured area, according toLANSECHx and MATRIX_SASSR / SASPLITx. That is,
 * the so defined securable high or low area is Secured for Writeaccess.1:
 * The HSELx AHB target security region is Not Secured for Write access.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR3 . WRNSECH0_SSR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR3_WRNSECH0_SSR3(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR3_WRNSECH0_SSR3     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR3_WRNSECH0_SSR3(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * RDNSECHx: Read Not Secured for HSELx Security Region0: The HSELx AHB
 * target security region is split into one Read Secured and one Read Not
 * Secured area, according toLANSECHx and MATRIX_SASSR / SASPLITx. That is,
 * the so defined securable high or low area is Secured for Readaccess.1:
 * The HSELx AHB target security region is Not Secured for Read access.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR3 . RDNSECH0_SSR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR3_RDNSECH0_SSR3(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR3_RDNSECH0_SSR3     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR3_RDNSECH0_SSR3(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * LANSECHx: Low Area Not Secured in HSELx Security Region0: The security
 * of the HSELx AHB target area laying below the corresponding MATRIX_SASSR
 * / SASPLITx boundary isconfigured according to RDNSECHx and WRNSECHx. The
 * whole remaining HSELx upper address space is configured asNot Secured
 * access.1: The HSELx AHB target address area laying below the
 * corresponding MATRIX_SASSR / SASPLITx boundary is configuredas Not
 * Secured access, and the whole remaining upper address space according to
 * RDNSECHx and WRNSECHx.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR3 . LANSECH0_SSR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR3_LANSECH0_SSR3(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR3_LANSECH0_SSR3     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR3_LANSECH0_SSR3(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Security Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * WRNSECHx / RDNSECHx Non-Secure Access Secure Access
 * 00 Denied Write - Read
 * 01 Read Write - Read
 * 10 Write Write - Read
 * 11 Write - Read Write - Read
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SSR4
 */
#define VTSS_HMATRIX2_MATRIX_SSR4            VTSS_IOREG(VTSS_TO_HMATRIX2,0x84)

/**
 * \brief
 * WRNSECHx: Write Not Secured for HSELx Security Region0: The HSELx AHB
 * target security region is split into one Write Secured and one Write Not
 * Secured area, according toLANSECHx and MATRIX_SASSR / SASPLITx. That is,
 * the so defined securable high or low area is Secured for Writeaccess.1:
 * The HSELx AHB target security region is Not Secured for Write access.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR4 . WRNSECH0_SSR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR4_WRNSECH0_SSR4(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR4_WRNSECH0_SSR4     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR4_WRNSECH0_SSR4(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * RDNSECHx: Read Not Secured for HSELx Security Region0: The HSELx AHB
 * target security region is split into one Read Secured and one Read Not
 * Secured area, according toLANSECHx and MATRIX_SASSR / SASPLITx. That is,
 * the so defined securable high or low area is Secured for Readaccess.1:
 * The HSELx AHB target security region is Not Secured for Read access.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR4 . RDNSECH0_SSR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR4_RDNSECH0_SSR4(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR4_RDNSECH0_SSR4     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR4_RDNSECH0_SSR4(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * LANSECHx: Low Area Not Secured in HSELx Security Region0: The security
 * of the HSELx AHB target area laying below the corresponding MATRIX_SASSR
 * / SASPLITx boundary isconfigured according to RDNSECHx and WRNSECHx. The
 * whole remaining HSELx upper address space is configured asNot Secured
 * access.1: The HSELx AHB target address area laying below the
 * corresponding MATRIX_SASSR / SASPLITx boundary is configuredas Not
 * Secured access, and the whole remaining upper address space according to
 * RDNSECHx and WRNSECHx.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR4 . LANSECH0_SSR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR4_LANSECH0_SSR4(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR4_LANSECH0_SSR4     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR4_LANSECH0_SSR4(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Security Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * WRNSECHx / RDNSECHx Non-Secure Access Secure Access
 * 00 Denied Write - Read
 * 01 Read Write - Read
 * 10 Write Write - Read
 * 11 Write - Read Write - Read
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SSR5
 */
#define VTSS_HMATRIX2_MATRIX_SSR5            VTSS_IOREG(VTSS_TO_HMATRIX2,0x85)

/**
 * \brief
 * WRNSECHx: Write Not Secured for HSELx Security Region0: The HSELx AHB
 * target security region is split into one Write Secured and one Write Not
 * Secured area, according toLANSECHx and MATRIX_SASSR / SASPLITx. That is,
 * the so defined securable high or low area is Secured for Writeaccess.1:
 * The HSELx AHB target security region is Not Secured for Write access.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR5 . WRNSECH0_SSR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR5_WRNSECH0_SSR5(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR5_WRNSECH0_SSR5     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR5_WRNSECH0_SSR5(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * RDNSECHx: Read Not Secured for HSELx Security Region0: The HSELx AHB
 * target security region is split into one Read Secured and one Read Not
 * Secured area, according toLANSECHx and MATRIX_SASSR / SASPLITx. That is,
 * the so defined securable high or low area is Secured for Readaccess.1:
 * The HSELx AHB target security region is Not Secured for Read access.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR5 . RDNSECH0_SSR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR5_RDNSECH0_SSR5(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR5_RDNSECH0_SSR5     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR5_RDNSECH0_SSR5(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * LANSECHx: Low Area Not Secured in HSELx Security Region0: The security
 * of the HSELx AHB target area laying below the corresponding MATRIX_SASSR
 * / SASPLITx boundary isconfigured according to RDNSECHx and WRNSECHx. The
 * whole remaining HSELx upper address space is configured asNot Secured
 * access.1: The HSELx AHB target address area laying below the
 * corresponding MATRIX_SASSR / SASPLITx boundary is configuredas Not
 * Secured access, and the whole remaining upper address space according to
 * RDNSECHx and WRNSECHx.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR5 . LANSECH0_SSR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR5_LANSECH0_SSR5(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR5_LANSECH0_SSR5     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR5_LANSECH0_SSR5(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Security Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * WRNSECHx / RDNSECHx Non-Secure Access Secure Access
 * 00 Denied Write - Read
 * 01 Read Write - Read
 * 10 Write Write - Read
 * 11 Write - Read Write - Read
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SSR6
 */
#define VTSS_HMATRIX2_MATRIX_SSR6            VTSS_IOREG(VTSS_TO_HMATRIX2,0x19)

/**
 * \brief
 * WRNSECHx: Write Not Secured for HSELx Security Region0: The HSELx AHB
 * target security region is split into one Write Secured and one Write Not
 * Secured area, according toLANSECHx and MATRIX_SASSR / SASPLITx. That is,
 * the so defined securable high or low area is Secured for Writeaccess.1:
 * The HSELx AHB target security region is Not Secured for Write access.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR6 . WRNSECH0_SSR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR6_WRNSECH0_SSR6(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR6_WRNSECH0_SSR6     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR6_WRNSECH0_SSR6(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * RDNSECHx: Read Not Secured for HSELx Security Region0: The HSELx AHB
 * target security region is split into one Read Secured and one Read Not
 * Secured area, according toLANSECHx and MATRIX_SASSR / SASPLITx. That is,
 * the so defined securable high or low area is Secured for Readaccess.1:
 * The HSELx AHB target security region is Not Secured for Read access.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR6 . RDNSECH0_SSR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR6_RDNSECH0_SSR6(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR6_RDNSECH0_SSR6     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR6_RDNSECH0_SSR6(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * LANSECHx: Low Area Not Secured in HSELx Security Region0: The security
 * of the HSELx AHB target area laying below the corresponding MATRIX_SASSR
 * / SASPLITx boundary isconfigured according to RDNSECHx and WRNSECHx. The
 * whole remaining HSELx upper address space is configured asNot Secured
 * access.1: The HSELx AHB target address area laying below the
 * corresponding MATRIX_SASSR / SASPLITx boundary is configuredas Not
 * Secured access, and the whole remaining upper address space according to
 * RDNSECHx and WRNSECHx.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR6 . LANSECH0_SSR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR6_LANSECH0_SSR6(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR6_LANSECH0_SSR6     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR6_LANSECH0_SSR6(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Security Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * WRNSECHx / RDNSECHx Non-Secure Access Secure Access
 * 00 Denied Write - Read
 * 01 Read Write - Read
 * 10 Write Write - Read
 * 11 Write - Read Write - Read
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SSR7
 */
#define VTSS_HMATRIX2_MATRIX_SSR7            VTSS_IOREG(VTSS_TO_HMATRIX2,0x1a)

/**
 * \brief
 * WRNSECHx: Write Not Secured for HSELx Security Region0: The HSELx AHB
 * target security region is split into one Write Secured and one Write Not
 * Secured area, according toLANSECHx and MATRIX_SASSR / SASPLITx. That is,
 * the so defined securable high or low area is Secured for Writeaccess.1:
 * The HSELx AHB target security region is Not Secured for Write access.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR7 . WRNSECH0_SSR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR7_WRNSECH0_SSR7(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR7_WRNSECH0_SSR7     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR7_WRNSECH0_SSR7(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * RDNSECHx: Read Not Secured for HSELx Security Region0: The HSELx AHB
 * target security region is split into one Read Secured and one Read Not
 * Secured area, according toLANSECHx and MATRIX_SASSR / SASPLITx. That is,
 * the so defined securable high or low area is Secured for Readaccess.1:
 * The HSELx AHB target security region is Not Secured for Read access.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR7 . RDNSECH0_SSR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR7_RDNSECH0_SSR7(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR7_RDNSECH0_SSR7     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR7_RDNSECH0_SSR7(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * LANSECHx: Low Area Not Secured in HSELx Security Region0: The security
 * of the HSELx AHB target area laying below the corresponding MATRIX_SASSR
 * / SASPLITx boundary isconfigured according to RDNSECHx and WRNSECHx. The
 * whole remaining HSELx upper address space is configured asNot Secured
 * access.1: The HSELx AHB target address area laying below the
 * corresponding MATRIX_SASSR / SASPLITx boundary is configuredas Not
 * Secured access, and the whole remaining upper address space according to
 * RDNSECHx and WRNSECHx.
 *
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SSR7 . LANSECH0_SSR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SSR7_LANSECH0_SSR7(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HMATRIX2_MATRIX_SSR7_LANSECH0_SSR7     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HMATRIX2_MATRIX_SSR7_LANSECH0_SSR7(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Security Areas Split Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * SASPLITx: Security Areas Split for HSELx Security Region
 * This field defines the boundary address offset where the HSELx AHB
 * target security region splits into two Security Areas
 * whose access is controlled according to the corresponding MATRIX_SSR. So
 * it also defines the Security Low Area size
 * inside the HSELx region.
 * If this Low Area size is set at or above the HSELx Region Size, then
 * there is no more Security High Area and the
 * MATRIX_SSR settings for the Low area apply to the whole HSELx Security
 * Region.
 *
 * SASPLITx Split Offset Security Low Area Size
 * 0000 0x00001000 4 Kbytes
 * 0001 0x00002000 8 Kbytes
 * 0010 0x00004000 16 Kbytes
 * 0011 0x00008000 32 Kbytes
 * 0100 0x00010000 64 Kbytes
 * 0101 0x00020000 128 Kbytes
 * 0110 0x00040000 256 Kbytes
 * 0111 0x00080000 512 Kbytes
 * 1000 0x00100000 1 Mbyte
 * 1001 0x00200000 2 Mbytes
 * 1010 0x00400000 4 Mbytes
 * 1011 0x00800000 8 Mbytes
 * 1100 0x01000000 16 Mbytes
 * 1101 0x02000000 32 Mbytes
 * 1110 0x04000000 64 Mbytes
 * 1111 0x08000000 128 Mbytes
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SASSR0
 */
#define VTSS_HMATRIX2_MATRIX_SASSR0          VTSS_IOREG(VTSS_TO_HMATRIX2,0x90)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR0 . SASPLIT7_SASSR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR0_SASPLIT7_SASSR0(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR0_SASPLIT7_SASSR0     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR0_SASPLIT7_SASSR0(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR0 . SASPLIT6_SASSR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR0_SASPLIT6_SASSR0(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR0_SASPLIT6_SASSR0     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR0_SASPLIT6_SASSR0(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR0 . SASPLIT5_SASSR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR0_SASPLIT5_SASSR0(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR0_SASPLIT5_SASSR0     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR0_SASPLIT5_SASSR0(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR0 . SASPLIT4_SASSR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR0_SASPLIT4_SASSR0(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR0_SASPLIT4_SASSR0     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR0_SASPLIT4_SASSR0(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR0 . SASPLIT3_SASSR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR0_SASPLIT3_SASSR0(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR0_SASPLIT3_SASSR0     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR0_SASPLIT3_SASSR0(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR0 . SASPLIT2_SASSR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR0_SASPLIT2_SASSR0(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR0_SASPLIT2_SASSR0     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR0_SASPLIT2_SASSR0(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR0 . SASPLIT1_SASSR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR0_SASPLIT1_SASSR0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR0_SASPLIT1_SASSR0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR0_SASPLIT1_SASSR0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR0 . SASPLIT0_SASSR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR0_SASPLIT0_SASSR0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR0_SASPLIT0_SASSR0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR0_SASPLIT0_SASSR0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Security Areas Split Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * SASPLITx: Security Areas Split for HSELx Security Region
 * This field defines the boundary address offset where the HSELx AHB
 * target security region splits into two Security Areas
 * whose access is controlled according to the corresponding MATRIX_SSR. So
 * it also defines the Security Low Area size
 * inside the HSELx region.
 * If this Low Area size is set at or above the HSELx Region Size, then
 * there is no more Security High Area and the
 * MATRIX_SSR settings for the Low area apply to the whole HSELx Security
 * Region.
 *
 * SASPLITx Split Offset Security Low Area Size
 * 0000 0x00001000 4 Kbytes
 * 0001 0x00002000 8 Kbytes
 * 0010 0x00004000 16 Kbytes
 * 0011 0x00008000 32 Kbytes
 * 0100 0x00010000 64 Kbytes
 * 0101 0x00020000 128 Kbytes
 * 0110 0x00040000 256 Kbytes
 * 0111 0x00080000 512 Kbytes
 * 1000 0x00100000 1 Mbyte
 * 1001 0x00200000 2 Mbytes
 * 1010 0x00400000 4 Mbytes
 * 1011 0x00800000 8 Mbytes
 * 1100 0x01000000 16 Mbytes
 * 1101 0x02000000 32 Mbytes
 * 1110 0x04000000 64 Mbytes
 * 1111 0x08000000 128 Mbytes
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SASSR1
 */
#define VTSS_HMATRIX2_MATRIX_SASSR1          VTSS_IOREG(VTSS_TO_HMATRIX2,0x91)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR1 . SASPLIT7_SASSR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR1_SASPLIT7_SASSR1(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR1_SASPLIT7_SASSR1     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR1_SASPLIT7_SASSR1(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR1 . SASPLIT6_SASSR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR1_SASPLIT6_SASSR1(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR1_SASPLIT6_SASSR1     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR1_SASPLIT6_SASSR1(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR1 . SASPLIT5_SASSR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR1_SASPLIT5_SASSR1(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR1_SASPLIT5_SASSR1     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR1_SASPLIT5_SASSR1(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR1 . SASPLIT4_SASSR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR1_SASPLIT4_SASSR1(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR1_SASPLIT4_SASSR1     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR1_SASPLIT4_SASSR1(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR1 . SASPLIT3_SASSR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR1_SASPLIT3_SASSR1(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR1_SASPLIT3_SASSR1     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR1_SASPLIT3_SASSR1(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR1 . SASPLIT2_SASSR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR1_SASPLIT2_SASSR1(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR1_SASPLIT2_SASSR1     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR1_SASPLIT2_SASSR1(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR1 . SASPLIT1_SASSR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR1_SASPLIT1_SASSR1(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR1_SASPLIT1_SASSR1     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR1_SASPLIT1_SASSR1(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR1 . SASPLIT0_SASSR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR1_SASPLIT0_SASSR1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR1_SASPLIT0_SASSR1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR1_SASPLIT0_SASSR1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Security Areas Split Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * SASPLITx: Security Areas Split for HSELx Security Region
 * This field defines the boundary address offset where the HSELx AHB
 * target security region splits into two Security Areas
 * whose access is controlled according to the corresponding MATRIX_SSR. So
 * it also defines the Security Low Area size
 * inside the HSELx region.
 * If this Low Area size is set at or above the HSELx Region Size, then
 * there is no more Security High Area and the
 * MATRIX_SSR settings for the Low area apply to the whole HSELx Security
 * Region.
 *
 * SASPLITx Split Offset Security Low Area Size
 * 0000 0x00001000 4 Kbytes
 * 0001 0x00002000 8 Kbytes
 * 0010 0x00004000 16 Kbytes
 * 0011 0x00008000 32 Kbytes
 * 0100 0x00010000 64 Kbytes
 * 0101 0x00020000 128 Kbytes
 * 0110 0x00040000 256 Kbytes
 * 0111 0x00080000 512 Kbytes
 * 1000 0x00100000 1 Mbyte
 * 1001 0x00200000 2 Mbytes
 * 1010 0x00400000 4 Mbytes
 * 1011 0x00800000 8 Mbytes
 * 1100 0x01000000 16 Mbytes
 * 1101 0x02000000 32 Mbytes
 * 1110 0x04000000 64 Mbytes
 * 1111 0x08000000 128 Mbytes
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SASSR2
 */
#define VTSS_HMATRIX2_MATRIX_SASSR2          VTSS_IOREG(VTSS_TO_HMATRIX2,0x92)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR2 . SASPLIT7_SASSR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR2_SASPLIT7_SASSR2(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR2_SASPLIT7_SASSR2     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR2_SASPLIT7_SASSR2(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR2 . SASPLIT6_SASSR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR2_SASPLIT6_SASSR2(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR2_SASPLIT6_SASSR2     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR2_SASPLIT6_SASSR2(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR2 . SASPLIT5_SASSR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR2_SASPLIT5_SASSR2(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR2_SASPLIT5_SASSR2     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR2_SASPLIT5_SASSR2(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR2 . SASPLIT4_SASSR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR2_SASPLIT4_SASSR2(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR2_SASPLIT4_SASSR2     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR2_SASPLIT4_SASSR2(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR2 . SASPLIT3_SASSR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR2_SASPLIT3_SASSR2(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR2_SASPLIT3_SASSR2     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR2_SASPLIT3_SASSR2(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR2 . SASPLIT2_SASSR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR2_SASPLIT2_SASSR2(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR2_SASPLIT2_SASSR2     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR2_SASPLIT2_SASSR2(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR2 . SASPLIT1_SASSR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR2_SASPLIT1_SASSR2(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR2_SASPLIT1_SASSR2     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR2_SASPLIT1_SASSR2(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR2 . SASPLIT0_SASSR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR2_SASPLIT0_SASSR2(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR2_SASPLIT0_SASSR2     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR2_SASPLIT0_SASSR2(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Security Areas Split Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * SASPLITx: Security Areas Split for HSELx Security Region
 * This field defines the boundary address offset where the HSELx AHB
 * target security region splits into two Security Areas
 * whose access is controlled according to the corresponding MATRIX_SSR. So
 * it also defines the Security Low Area size
 * inside the HSELx region.
 * If this Low Area size is set at or above the HSELx Region Size, then
 * there is no more Security High Area and the
 * MATRIX_SSR settings for the Low area apply to the whole HSELx Security
 * Region.
 *
 * SASPLITx Split Offset Security Low Area Size
 * 0000 0x00001000 4 Kbytes
 * 0001 0x00002000 8 Kbytes
 * 0010 0x00004000 16 Kbytes
 * 0011 0x00008000 32 Kbytes
 * 0100 0x00010000 64 Kbytes
 * 0101 0x00020000 128 Kbytes
 * 0110 0x00040000 256 Kbytes
 * 0111 0x00080000 512 Kbytes
 * 1000 0x00100000 1 Mbyte
 * 1001 0x00200000 2 Mbytes
 * 1010 0x00400000 4 Mbytes
 * 1011 0x00800000 8 Mbytes
 * 1100 0x01000000 16 Mbytes
 * 1101 0x02000000 32 Mbytes
 * 1110 0x04000000 64 Mbytes
 * 1111 0x08000000 128 Mbytes
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SASSR3
 */
#define VTSS_HMATRIX2_MATRIX_SASSR3          VTSS_IOREG(VTSS_TO_HMATRIX2,0x93)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR3 . SASPLIT7_SASSR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR3_SASPLIT7_SASSR3(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR3_SASPLIT7_SASSR3     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR3_SASPLIT7_SASSR3(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR3 . SASPLIT6_SASSR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR3_SASPLIT6_SASSR3(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR3_SASPLIT6_SASSR3     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR3_SASPLIT6_SASSR3(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR3 . SASPLIT5_SASSR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR3_SASPLIT5_SASSR3(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR3_SASPLIT5_SASSR3     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR3_SASPLIT5_SASSR3(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR3 . SASPLIT4_SASSR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR3_SASPLIT4_SASSR3(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR3_SASPLIT4_SASSR3     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR3_SASPLIT4_SASSR3(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR3 . SASPLIT3_SASSR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR3_SASPLIT3_SASSR3(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR3_SASPLIT3_SASSR3     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR3_SASPLIT3_SASSR3(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR3 . SASPLIT2_SASSR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR3_SASPLIT2_SASSR3(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR3_SASPLIT2_SASSR3     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR3_SASPLIT2_SASSR3(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR3 . SASPLIT1_SASSR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR3_SASPLIT1_SASSR3(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR3_SASPLIT1_SASSR3     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR3_SASPLIT1_SASSR3(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR3 . SASPLIT0_SASSR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR3_SASPLIT0_SASSR3(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR3_SASPLIT0_SASSR3     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR3_SASPLIT0_SASSR3(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Security Areas Split Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * SASPLITx: Security Areas Split for HSELx Security Region
 * This field defines the boundary address offset where the HSELx AHB
 * target security region splits into two Security Areas
 * whose access is controlled according to the corresponding MATRIX_SSR. So
 * it also defines the Security Low Area size
 * inside the HSELx region.
 * If this Low Area size is set at or above the HSELx Region Size, then
 * there is no more Security High Area and the
 * MATRIX_SSR settings for the Low area apply to the whole HSELx Security
 * Region.
 *
 * SASPLITx Split Offset Security Low Area Size
 * 0000 0x00001000 4 Kbytes
 * 0001 0x00002000 8 Kbytes
 * 0010 0x00004000 16 Kbytes
 * 0011 0x00008000 32 Kbytes
 * 0100 0x00010000 64 Kbytes
 * 0101 0x00020000 128 Kbytes
 * 0110 0x00040000 256 Kbytes
 * 0111 0x00080000 512 Kbytes
 * 1000 0x00100000 1 Mbyte
 * 1001 0x00200000 2 Mbytes
 * 1010 0x00400000 4 Mbytes
 * 1011 0x00800000 8 Mbytes
 * 1100 0x01000000 16 Mbytes
 * 1101 0x02000000 32 Mbytes
 * 1110 0x04000000 64 Mbytes
 * 1111 0x08000000 128 Mbytes
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SASSR4
 */
#define VTSS_HMATRIX2_MATRIX_SASSR4          VTSS_IOREG(VTSS_TO_HMATRIX2,0x94)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR4 . SASPLIT7_SASSR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR4_SASPLIT7_SASSR4(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR4_SASPLIT7_SASSR4     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR4_SASPLIT7_SASSR4(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR4 . SASPLIT6_SASSR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR4_SASPLIT6_SASSR4(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR4_SASPLIT6_SASSR4     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR4_SASPLIT6_SASSR4(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR4 . SASPLIT5_SASSR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR4_SASPLIT5_SASSR4(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR4_SASPLIT5_SASSR4     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR4_SASPLIT5_SASSR4(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR4 . SASPLIT4_SASSR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR4_SASPLIT4_SASSR4(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR4_SASPLIT4_SASSR4     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR4_SASPLIT4_SASSR4(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR4 . SASPLIT3_SASSR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR4_SASPLIT3_SASSR4(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR4_SASPLIT3_SASSR4     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR4_SASPLIT3_SASSR4(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR4 . SASPLIT2_SASSR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR4_SASPLIT2_SASSR4(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR4_SASPLIT2_SASSR4     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR4_SASPLIT2_SASSR4(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR4 . SASPLIT1_SASSR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR4_SASPLIT1_SASSR4(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR4_SASPLIT1_SASSR4     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR4_SASPLIT1_SASSR4(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR4 . SASPLIT0_SASSR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR4_SASPLIT0_SASSR4(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR4_SASPLIT0_SASSR4     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR4_SASPLIT0_SASSR4(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Security Areas Split Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * SASPLITx: Security Areas Split for HSELx Security Region
 * This field defines the boundary address offset where the HSELx AHB
 * target security region splits into two Security Areas
 * whose access is controlled according to the corresponding MATRIX_SSR. So
 * it also defines the Security Low Area size
 * inside the HSELx region.
 * If this Low Area size is set at or above the HSELx Region Size, then
 * there is no more Security High Area and the
 * MATRIX_SSR settings for the Low area apply to the whole HSELx Security
 * Region.
 *
 * SASPLITx Split Offset Security Low Area Size
 * 0000 0x00001000 4 Kbytes
 * 0001 0x00002000 8 Kbytes
 * 0010 0x00004000 16 Kbytes
 * 0011 0x00008000 32 Kbytes
 * 0100 0x00010000 64 Kbytes
 * 0101 0x00020000 128 Kbytes
 * 0110 0x00040000 256 Kbytes
 * 0111 0x00080000 512 Kbytes
 * 1000 0x00100000 1 Mbyte
 * 1001 0x00200000 2 Mbytes
 * 1010 0x00400000 4 Mbytes
 * 1011 0x00800000 8 Mbytes
 * 1100 0x01000000 16 Mbytes
 * 1101 0x02000000 32 Mbytes
 * 1110 0x04000000 64 Mbytes
 * 1111 0x08000000 128 Mbytes
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SASSR5
 */
#define VTSS_HMATRIX2_MATRIX_SASSR5          VTSS_IOREG(VTSS_TO_HMATRIX2,0x95)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR5 . SASPLIT7_SASSR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR5_SASPLIT7_SASSR5(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR5_SASPLIT7_SASSR5     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR5_SASPLIT7_SASSR5(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR5 . SASPLIT6_SASSR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR5_SASPLIT6_SASSR5(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR5_SASPLIT6_SASSR5     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR5_SASPLIT6_SASSR5(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR5 . SASPLIT5_SASSR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR5_SASPLIT5_SASSR5(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR5_SASPLIT5_SASSR5     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR5_SASPLIT5_SASSR5(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR5 . SASPLIT4_SASSR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR5_SASPLIT4_SASSR5(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR5_SASPLIT4_SASSR5     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR5_SASPLIT4_SASSR5(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR5 . SASPLIT3_SASSR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR5_SASPLIT3_SASSR5(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR5_SASPLIT3_SASSR5     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR5_SASPLIT3_SASSR5(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR5 . SASPLIT2_SASSR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR5_SASPLIT2_SASSR5(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR5_SASPLIT2_SASSR5     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR5_SASPLIT2_SASSR5(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR5 . SASPLIT1_SASSR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR5_SASPLIT1_SASSR5(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR5_SASPLIT1_SASSR5     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR5_SASPLIT1_SASSR5(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR5 . SASPLIT0_SASSR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR5_SASPLIT0_SASSR5(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR5_SASPLIT0_SASSR5     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR5_SASPLIT0_SASSR5(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Security Areas Split Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * SASPLITx: Security Areas Split for HSELx Security Region
 * This field defines the boundary address offset where the HSELx AHB
 * target security region splits into two Security Areas
 * whose access is controlled according to the corresponding MATRIX_SSR. So
 * it also defines the Security Low Area size
 * inside the HSELx region.
 * If this Low Area size is set at or above the HSELx Region Size, then
 * there is no more Security High Area and the
 * MATRIX_SSR settings for the Low area apply to the whole HSELx Security
 * Region.
 *
 * SASPLITx Split Offset Security Low Area Size
 * 0000 0x00001000 4 Kbytes
 * 0001 0x00002000 8 Kbytes
 * 0010 0x00004000 16 Kbytes
 * 0011 0x00008000 32 Kbytes
 * 0100 0x00010000 64 Kbytes
 * 0101 0x00020000 128 Kbytes
 * 0110 0x00040000 256 Kbytes
 * 0111 0x00080000 512 Kbytes
 * 1000 0x00100000 1 Mbyte
 * 1001 0x00200000 2 Mbytes
 * 1010 0x00400000 4 Mbytes
 * 1011 0x00800000 8 Mbytes
 * 1100 0x01000000 16 Mbytes
 * 1101 0x02000000 32 Mbytes
 * 1110 0x04000000 64 Mbytes
 * 1111 0x08000000 128 Mbytes
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SASSR6
 */
#define VTSS_HMATRIX2_MATRIX_SASSR6          VTSS_IOREG(VTSS_TO_HMATRIX2,0x1b)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR6 . SASPLIT7_SASSR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR6_SASPLIT7_SASSR6(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR6_SASPLIT7_SASSR6     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR6_SASPLIT7_SASSR6(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR6 . SASPLIT6_SASSR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR6_SASPLIT6_SASSR6(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR6_SASPLIT6_SASSR6     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR6_SASPLIT6_SASSR6(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR6 . SASPLIT5_SASSR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR6_SASPLIT5_SASSR6(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR6_SASPLIT5_SASSR6     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR6_SASPLIT5_SASSR6(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR6 . SASPLIT4_SASSR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR6_SASPLIT4_SASSR6(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR6_SASPLIT4_SASSR6     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR6_SASPLIT4_SASSR6(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR6 . SASPLIT3_SASSR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR6_SASPLIT3_SASSR6(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR6_SASPLIT3_SASSR6     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR6_SASPLIT3_SASSR6(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR6 . SASPLIT2_SASSR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR6_SASPLIT2_SASSR6(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR6_SASPLIT2_SASSR6     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR6_SASPLIT2_SASSR6(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR6 . SASPLIT1_SASSR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR6_SASPLIT1_SASSR6(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR6_SASPLIT1_SASSR6     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR6_SASPLIT1_SASSR6(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR6 . SASPLIT0_SASSR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR6_SASPLIT0_SASSR6(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR6_SASPLIT0_SASSR6     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR6_SASPLIT0_SASSR6(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Security Areas Split Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * SASPLITx: Security Areas Split for HSELx Security Region
 * This field defines the boundary address offset where the HSELx AHB
 * target security region splits into two Security Areas
 * whose access is controlled according to the corresponding MATRIX_SSR. So
 * it also defines the Security Low Area size
 * inside the HSELx region.
 * If this Low Area size is set at or above the HSELx Region Size, then
 * there is no more Security High Area and the
 * MATRIX_SSR settings for the Low area apply to the whole HSELx Security
 * Region.
 *
 * SASPLITx Split Offset Security Low Area Size
 * 0000 0x00001000 4 Kbytes
 * 0001 0x00002000 8 Kbytes
 * 0010 0x00004000 16 Kbytes
 * 0011 0x00008000 32 Kbytes
 * 0100 0x00010000 64 Kbytes
 * 0101 0x00020000 128 Kbytes
 * 0110 0x00040000 256 Kbytes
 * 0111 0x00080000 512 Kbytes
 * 1000 0x00100000 1 Mbyte
 * 1001 0x00200000 2 Mbytes
 * 1010 0x00400000 4 Mbytes
 * 1011 0x00800000 8 Mbytes
 * 1100 0x01000000 16 Mbytes
 * 1101 0x02000000 32 Mbytes
 * 1110 0x04000000 64 Mbytes
 * 1111 0x08000000 128 Mbytes
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SASSR7
 */
#define VTSS_HMATRIX2_MATRIX_SASSR7          VTSS_IOREG(VTSS_TO_HMATRIX2,0x1c)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR7 . SASPLIT7_SASSR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR7_SASPLIT7_SASSR7(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR7_SASPLIT7_SASSR7     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR7_SASPLIT7_SASSR7(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR7 . SASPLIT6_SASSR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR7_SASPLIT6_SASSR7(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR7_SASPLIT6_SASSR7     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR7_SASPLIT6_SASSR7(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR7 . SASPLIT5_SASSR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR7_SASPLIT5_SASSR7(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR7_SASPLIT5_SASSR7     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR7_SASPLIT5_SASSR7(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR7 . SASPLIT4_SASSR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR7_SASPLIT4_SASSR7(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR7_SASPLIT4_SASSR7     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR7_SASPLIT4_SASSR7(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR7 . SASPLIT3_SASSR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR7_SASPLIT3_SASSR7(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR7_SASPLIT3_SASSR7     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR7_SASPLIT3_SASSR7(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR7 . SASPLIT2_SASSR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR7_SASPLIT2_SASSR7(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR7_SASPLIT2_SASSR7     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR7_SASPLIT2_SASSR7(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR7 . SASPLIT1_SASSR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR7_SASPLIT1_SASSR7(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR7_SASPLIT1_SASSR7     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR7_SASPLIT1_SASSR7(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SASSR7 . SASPLIT0_SASSR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SASSR7_SASPLIT0_SASSR7(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HMATRIX2_MATRIX_SASSR7_SASPLIT0_SASSR7     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HMATRIX2_MATRIX_SASSR7_SASPLIT0_SASSR7(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Security Region Top Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *  SRTOPx: HSELx Security Region Top
 * This field defines the size of the HSELx security region address space.
 * Invalid sizes for the target region must never be programmed.
 * Valid sizes and number of security regions are product, target and
 * target configuration dependent.
 * Note: The Targets featuring multiple scalable contiguous security
 * regions have a single SRTOP0 field for all the security regions.
 * If this HSELx security region size is set at or below the HSELx low area
 * size, then there is no more security high area and
 * the MATRIX_SSR settings for the low area apply to the whole HSELx
 * security region.
 *
 *
 * SRTOPx Top Offset Security Region Size
 * 0000 0x00001000 4 Kbytes
 * 0001 0x00002000 8 Kbytes
 * 0010 0x00004000 16 Kbytes
 * 0011 0x00008000 32 Kbytes
 * 0100 0x00010000 64 Kbytes
 * 0101 0x00020000 128 Kbytes
 * 0110 0x00040000 256 Kbytes
 * 0111 0x00080000 512 Kbytes
 * 1000 0x00100000 1 Mbyte
 * 1001 0x00200000 2 Mbytes
 * 1010 0x00400000 4 Mbytes
 * 1011 0x00800000 8 Mbytes
 * 1100 0x01000000 16 Mbytes
 * 1101 0x02000000 32 Mbytes
 * 1110 0x04000000 64 Mbytes
 * 1111 0x08000000 128 Mbytes
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SRTSR0
 */
#define VTSS_HMATRIX2_MATRIX_SRTSR0          VTSS_IOREG(VTSS_TO_HMATRIX2,0xa0)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR0 . SRTOP7_SRTSR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR0_SRTOP7_SRTSR0(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR0_SRTOP7_SRTSR0     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR0_SRTOP7_SRTSR0(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR0 . SRTOP6_SRTSR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR0_SRTOP6_SRTSR0(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR0_SRTOP6_SRTSR0     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR0_SRTOP6_SRTSR0(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR0 . SRTOP5_SRTSR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR0_SRTOP5_SRTSR0(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR0_SRTOP5_SRTSR0     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR0_SRTOP5_SRTSR0(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR0 . SRTOP4_SRTSR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR0_SRTOP4_SRTSR0(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR0_SRTOP4_SRTSR0     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR0_SRTOP4_SRTSR0(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR0 . SRTOP3_SRTSR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR0_SRTOP3_SRTSR0(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR0_SRTOP3_SRTSR0     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR0_SRTOP3_SRTSR0(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR0 . SRTOP2_SRTSR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR0_SRTOP2_SRTSR0(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR0_SRTOP2_SRTSR0     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR0_SRTOP2_SRTSR0(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR0 . SRTOP1_SRTSR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR0_SRTOP1_SRTSR0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR0_SRTOP1_SRTSR0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR0_SRTOP1_SRTSR0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR0 . SRTOP0_SRTSR0
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR0_SRTOP0_SRTSR0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR0_SRTOP0_SRTSR0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR0_SRTOP0_SRTSR0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Security Region Top Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *  SRTOPx: HSELx Security Region Top
 * This field defines the size of the HSELx security region address space.
 * Invalid sizes for the target region must never be programmed.
 * Valid sizes and number of security regions are product, target and
 * target configuration dependent.
 * Note: The Targets featuring multiple scalable contiguous security
 * regions have a single SRTOP0 field for all the security regions.
 * If this HSELx security region size is set at or below the HSELx low area
 * size, then there is no more security high area and
 * the MATRIX_SSR settings for the low area apply to the whole HSELx
 * security region.
 *
 *
 * SRTOPx Top Offset Security Region Size
 * 0000 0x00001000 4 Kbytes
 * 0001 0x00002000 8 Kbytes
 * 0010 0x00004000 16 Kbytes
 * 0011 0x00008000 32 Kbytes
 * 0100 0x00010000 64 Kbytes
 * 0101 0x00020000 128 Kbytes
 * 0110 0x00040000 256 Kbytes
 * 0111 0x00080000 512 Kbytes
 * 1000 0x00100000 1 Mbyte
 * 1001 0x00200000 2 Mbytes
 * 1010 0x00400000 4 Mbytes
 * 1011 0x00800000 8 Mbytes
 * 1100 0x01000000 16 Mbytes
 * 1101 0x02000000 32 Mbytes
 * 1110 0x04000000 64 Mbytes
 * 1111 0x08000000 128 Mbytes
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SRTSR1
 */
#define VTSS_HMATRIX2_MATRIX_SRTSR1          VTSS_IOREG(VTSS_TO_HMATRIX2,0xa1)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR1 . SRTOP7_SRTSR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR1_SRTOP7_SRTSR1(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR1_SRTOP7_SRTSR1     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR1_SRTOP7_SRTSR1(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR1 . SRTOP6_SRTSR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR1_SRTOP6_SRTSR1(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR1_SRTOP6_SRTSR1     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR1_SRTOP6_SRTSR1(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR1 . SRTOP5_SRTSR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR1_SRTOP5_SRTSR1(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR1_SRTOP5_SRTSR1     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR1_SRTOP5_SRTSR1(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR1 . SRTOP4_SRTSR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR1_SRTOP4_SRTSR1(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR1_SRTOP4_SRTSR1     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR1_SRTOP4_SRTSR1(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR1 . SRTOP3_SRTSR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR1_SRTOP3_SRTSR1(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR1_SRTOP3_SRTSR1     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR1_SRTOP3_SRTSR1(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR1 . SRTOP2_SRTSR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR1_SRTOP2_SRTSR1(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR1_SRTOP2_SRTSR1     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR1_SRTOP2_SRTSR1(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR1 . SRTOP1_SRTSR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR1_SRTOP1_SRTSR1(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR1_SRTOP1_SRTSR1     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR1_SRTOP1_SRTSR1(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR1 . SRTOP0_SRTSR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR1_SRTOP0_SRTSR1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR1_SRTOP0_SRTSR1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR1_SRTOP0_SRTSR1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Security Region Top Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *  SRTOPx: HSELx Security Region Top
 * This field defines the size of the HSELx security region address space.
 * Invalid sizes for the target region must never be programmed.
 * Valid sizes and number of security regions are product, target and
 * target configuration dependent.
 * Note: The Targets featuring multiple scalable contiguous security
 * regions have a single SRTOP0 field for all the security regions.
 * If this HSELx security region size is set at or below the HSELx low area
 * size, then there is no more security high area and
 * the MATRIX_SSR settings for the low area apply to the whole HSELx
 * security region.
 *
 *
 * SRTOPx Top Offset Security Region Size
 * 0000 0x00001000 4 Kbytes
 * 0001 0x00002000 8 Kbytes
 * 0010 0x00004000 16 Kbytes
 * 0011 0x00008000 32 Kbytes
 * 0100 0x00010000 64 Kbytes
 * 0101 0x00020000 128 Kbytes
 * 0110 0x00040000 256 Kbytes
 * 0111 0x00080000 512 Kbytes
 * 1000 0x00100000 1 Mbyte
 * 1001 0x00200000 2 Mbytes
 * 1010 0x00400000 4 Mbytes
 * 1011 0x00800000 8 Mbytes
 * 1100 0x01000000 16 Mbytes
 * 1101 0x02000000 32 Mbytes
 * 1110 0x04000000 64 Mbytes
 * 1111 0x08000000 128 Mbytes
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SRTSR2
 */
#define VTSS_HMATRIX2_MATRIX_SRTSR2          VTSS_IOREG(VTSS_TO_HMATRIX2,0xa2)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR2 . SRTOP7_SRTSR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR2_SRTOP7_SRTSR2(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR2_SRTOP7_SRTSR2     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR2_SRTOP7_SRTSR2(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR2 . SRTOP6_SRTSR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR2_SRTOP6_SRTSR2(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR2_SRTOP6_SRTSR2     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR2_SRTOP6_SRTSR2(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR2 . SRTOP5_SRTSR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR2_SRTOP5_SRTSR2(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR2_SRTOP5_SRTSR2     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR2_SRTOP5_SRTSR2(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR2 . SRTOP4_SRTSR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR2_SRTOP4_SRTSR2(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR2_SRTOP4_SRTSR2     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR2_SRTOP4_SRTSR2(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR2 . SRTOP3_SRTSR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR2_SRTOP3_SRTSR2(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR2_SRTOP3_SRTSR2     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR2_SRTOP3_SRTSR2(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR2 . SRTOP2_SRTSR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR2_SRTOP2_SRTSR2(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR2_SRTOP2_SRTSR2     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR2_SRTOP2_SRTSR2(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR2 . SRTOP1_SRTSR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR2_SRTOP1_SRTSR2(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR2_SRTOP1_SRTSR2     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR2_SRTOP1_SRTSR2(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR2 . SRTOP0_SRTSR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR2_SRTOP0_SRTSR2(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR2_SRTOP0_SRTSR2     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR2_SRTOP0_SRTSR2(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Security Region Top Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *  SRTOPx: HSELx Security Region Top
 * This field defines the size of the HSELx security region address space.
 * Invalid sizes for the target region must never be programmed.
 * Valid sizes and number of security regions are product, target and
 * target configuration dependent.
 * Note: The Targets featuring multiple scalable contiguous security
 * regions have a single SRTOP0 field for all the security regions.
 * If this HSELx security region size is set at or below the HSELx low area
 * size, then there is no more security high area and
 * the MATRIX_SSR settings for the low area apply to the whole HSELx
 * security region.
 *
 *
 * SRTOPx Top Offset Security Region Size
 * 0000 0x00001000 4 Kbytes
 * 0001 0x00002000 8 Kbytes
 * 0010 0x00004000 16 Kbytes
 * 0011 0x00008000 32 Kbytes
 * 0100 0x00010000 64 Kbytes
 * 0101 0x00020000 128 Kbytes
 * 0110 0x00040000 256 Kbytes
 * 0111 0x00080000 512 Kbytes
 * 1000 0x00100000 1 Mbyte
 * 1001 0x00200000 2 Mbytes
 * 1010 0x00400000 4 Mbytes
 * 1011 0x00800000 8 Mbytes
 * 1100 0x01000000 16 Mbytes
 * 1101 0x02000000 32 Mbytes
 * 1110 0x04000000 64 Mbytes
 * 1111 0x08000000 128 Mbytes
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SRTSR3
 */
#define VTSS_HMATRIX2_MATRIX_SRTSR3          VTSS_IOREG(VTSS_TO_HMATRIX2,0xa3)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR3 . SRTOP7_SRTSR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR3_SRTOP7_SRTSR3(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR3_SRTOP7_SRTSR3     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR3_SRTOP7_SRTSR3(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR3 . SRTOP6_SRTSR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR3_SRTOP6_SRTSR3(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR3_SRTOP6_SRTSR3     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR3_SRTOP6_SRTSR3(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR3 . SRTOP5_SRTSR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR3_SRTOP5_SRTSR3(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR3_SRTOP5_SRTSR3     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR3_SRTOP5_SRTSR3(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR3 . SRTOP4_SRTSR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR3_SRTOP4_SRTSR3(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR3_SRTOP4_SRTSR3     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR3_SRTOP4_SRTSR3(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR3 . SRTOP3_SRTSR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR3_SRTOP3_SRTSR3(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR3_SRTOP3_SRTSR3     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR3_SRTOP3_SRTSR3(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR3 . SRTOP2_SRTSR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR3_SRTOP2_SRTSR3(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR3_SRTOP2_SRTSR3     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR3_SRTOP2_SRTSR3(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR3 . SRTOP1_SRTSR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR3_SRTOP1_SRTSR3(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR3_SRTOP1_SRTSR3     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR3_SRTOP1_SRTSR3(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR3 . SRTOP0_SRTSR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR3_SRTOP0_SRTSR3(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR3_SRTOP0_SRTSR3     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR3_SRTOP0_SRTSR3(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Security Region Top Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *  SRTOPx: HSELx Security Region Top
 * This field defines the size of the HSELx security region address space.
 * Invalid sizes for the target region must never be programmed.
 * Valid sizes and number of security regions are product, target and
 * target configuration dependent.
 * Note: The Targets featuring multiple scalable contiguous security
 * regions have a single SRTOP0 field for all the security regions.
 * If this HSELx security region size is set at or below the HSELx low area
 * size, then there is no more security high area and
 * the MATRIX_SSR settings for the low area apply to the whole HSELx
 * security region.
 *
 *
 * SRTOPx Top Offset Security Region Size
 * 0000 0x00001000 4 Kbytes
 * 0001 0x00002000 8 Kbytes
 * 0010 0x00004000 16 Kbytes
 * 0011 0x00008000 32 Kbytes
 * 0100 0x00010000 64 Kbytes
 * 0101 0x00020000 128 Kbytes
 * 0110 0x00040000 256 Kbytes
 * 0111 0x00080000 512 Kbytes
 * 1000 0x00100000 1 Mbyte
 * 1001 0x00200000 2 Mbytes
 * 1010 0x00400000 4 Mbytes
 * 1011 0x00800000 8 Mbytes
 * 1100 0x01000000 16 Mbytes
 * 1101 0x02000000 32 Mbytes
 * 1110 0x04000000 64 Mbytes
 * 1111 0x08000000 128 Mbytes
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SRTSR4
 */
#define VTSS_HMATRIX2_MATRIX_SRTSR4          VTSS_IOREG(VTSS_TO_HMATRIX2,0xa4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR4 . SRTOP7_SRTSR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR4_SRTOP7_SRTSR4(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR4_SRTOP7_SRTSR4     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR4_SRTOP7_SRTSR4(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR4 . SRTOP6_SRTSR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR4_SRTOP6_SRTSR4(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR4_SRTOP6_SRTSR4     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR4_SRTOP6_SRTSR4(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR4 . SRTOP5_SRTSR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR4_SRTOP5_SRTSR4(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR4_SRTOP5_SRTSR4     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR4_SRTOP5_SRTSR4(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR4 . SRTOP4_SRTSR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR4_SRTOP4_SRTSR4(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR4_SRTOP4_SRTSR4     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR4_SRTOP4_SRTSR4(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR4 . SRTOP3_SRTSR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR4_SRTOP3_SRTSR4(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR4_SRTOP3_SRTSR4     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR4_SRTOP3_SRTSR4(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR4 . SRTOP2_SRTSR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR4_SRTOP2_SRTSR4(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR4_SRTOP2_SRTSR4     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR4_SRTOP2_SRTSR4(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR4 . SRTOP1_SRTSR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR4_SRTOP1_SRTSR4(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR4_SRTOP1_SRTSR4     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR4_SRTOP1_SRTSR4(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR4 . SRTOP0_SRTSR4
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR4_SRTOP0_SRTSR4(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR4_SRTOP0_SRTSR4     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR4_SRTOP0_SRTSR4(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Security Region Top Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *  SRTOPx: HSELx Security Region Top
 * This field defines the size of the HSELx security region address space.
 * Invalid sizes for the target region must never be programmed.
 * Valid sizes and number of security regions are product, target and
 * target configuration dependent.
 * Note: The Targets featuring multiple scalable contiguous security
 * regions have a single SRTOP0 field for all the security regions.
 * If this HSELx security region size is set at or below the HSELx low area
 * size, then there is no more security high area and
 * the MATRIX_SSR settings for the low area apply to the whole HSELx
 * security region.
 *
 *
 * SRTOPx Top Offset Security Region Size
 * 0000 0x00001000 4 Kbytes
 * 0001 0x00002000 8 Kbytes
 * 0010 0x00004000 16 Kbytes
 * 0011 0x00008000 32 Kbytes
 * 0100 0x00010000 64 Kbytes
 * 0101 0x00020000 128 Kbytes
 * 0110 0x00040000 256 Kbytes
 * 0111 0x00080000 512 Kbytes
 * 1000 0x00100000 1 Mbyte
 * 1001 0x00200000 2 Mbytes
 * 1010 0x00400000 4 Mbytes
 * 1011 0x00800000 8 Mbytes
 * 1100 0x01000000 16 Mbytes
 * 1101 0x02000000 32 Mbytes
 * 1110 0x04000000 64 Mbytes
 * 1111 0x08000000 128 Mbytes
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SRTSR5
 */
#define VTSS_HMATRIX2_MATRIX_SRTSR5          VTSS_IOREG(VTSS_TO_HMATRIX2,0xa5)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR5 . SRTOP7_SRTSR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR5_SRTOP7_SRTSR5(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR5_SRTOP7_SRTSR5     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR5_SRTOP7_SRTSR5(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR5 . SRTOP6_SRTSR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR5_SRTOP6_SRTSR5(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR5_SRTOP6_SRTSR5     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR5_SRTOP6_SRTSR5(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR5 . SRTOP5_SRTSR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR5_SRTOP5_SRTSR5(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR5_SRTOP5_SRTSR5     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR5_SRTOP5_SRTSR5(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR5 . SRTOP4_SRTSR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR5_SRTOP4_SRTSR5(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR5_SRTOP4_SRTSR5     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR5_SRTOP4_SRTSR5(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR5 . SRTOP3_SRTSR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR5_SRTOP3_SRTSR5(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR5_SRTOP3_SRTSR5     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR5_SRTOP3_SRTSR5(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR5 . SRTOP2_SRTSR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR5_SRTOP2_SRTSR5(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR5_SRTOP2_SRTSR5     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR5_SRTOP2_SRTSR5(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR5 . SRTOP1_SRTSR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR5_SRTOP1_SRTSR5(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR5_SRTOP1_SRTSR5     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR5_SRTOP1_SRTSR5(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR5 . SRTOP0_SRTSR5
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR5_SRTOP0_SRTSR5(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR5_SRTOP0_SRTSR5     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR5_SRTOP0_SRTSR5(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Security Region Top Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *  SRTOPx: HSELx Security Region Top
 * This field defines the size of the HSELx security region address space.
 * Invalid sizes for the target region must never be programmed.
 * Valid sizes and number of security regions are product, target and
 * target configuration dependent.
 * Note: The Targets featuring multiple scalable contiguous security
 * regions have a single SRTOP0 field for all the security regions.
 * If this HSELx security region size is set at or below the HSELx low area
 * size, then there is no more security high area and
 * the MATRIX_SSR settings for the low area apply to the whole HSELx
 * security region.
 *
 *
 * SRTOPx Top Offset Security Region Size
 * 0000 0x00001000 4 Kbytes
 * 0001 0x00002000 8 Kbytes
 * 0010 0x00004000 16 Kbytes
 * 0011 0x00008000 32 Kbytes
 * 0100 0x00010000 64 Kbytes
 * 0101 0x00020000 128 Kbytes
 * 0110 0x00040000 256 Kbytes
 * 0111 0x00080000 512 Kbytes
 * 1000 0x00100000 1 Mbyte
 * 1001 0x00200000 2 Mbytes
 * 1010 0x00400000 4 Mbytes
 * 1011 0x00800000 8 Mbytes
 * 1100 0x01000000 16 Mbytes
 * 1101 0x02000000 32 Mbytes
 * 1110 0x04000000 64 Mbytes
 * 1111 0x08000000 128 Mbytes
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SRTSR6
 */
#define VTSS_HMATRIX2_MATRIX_SRTSR6          VTSS_IOREG(VTSS_TO_HMATRIX2,0x1d)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR6 . SRTOP7_SRTSR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR6_SRTOP7_SRTSR6(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR6_SRTOP7_SRTSR6     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR6_SRTOP7_SRTSR6(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR6 . SRTOP6_SRTSR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR6_SRTOP6_SRTSR6(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR6_SRTOP6_SRTSR6     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR6_SRTOP6_SRTSR6(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR6 . SRTOP5_SRTSR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR6_SRTOP5_SRTSR6(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR6_SRTOP5_SRTSR6     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR6_SRTOP5_SRTSR6(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR6 . SRTOP4_SRTSR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR6_SRTOP4_SRTSR6(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR6_SRTOP4_SRTSR6     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR6_SRTOP4_SRTSR6(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR6 . SRTOP3_SRTSR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR6_SRTOP3_SRTSR6(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR6_SRTOP3_SRTSR6     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR6_SRTOP3_SRTSR6(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR6 . SRTOP2_SRTSR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR6_SRTOP2_SRTSR6(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR6_SRTOP2_SRTSR6     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR6_SRTOP2_SRTSR6(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR6 . SRTOP1_SRTSR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR6_SRTOP1_SRTSR6(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR6_SRTOP1_SRTSR6     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR6_SRTOP1_SRTSR6(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR6 . SRTOP0_SRTSR6
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR6_SRTOP0_SRTSR6(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR6_SRTOP0_SRTSR6     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR6_SRTOP0_SRTSR6(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Security Region Top Target Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *  SRTOPx: HSELx Security Region Top
 * This field defines the size of the HSELx security region address space.
 * Invalid sizes for the target region must never be programmed.
 * Valid sizes and number of security regions are product, target and
 * target configuration dependent.
 * Note: The Targets featuring multiple scalable contiguous security
 * regions have a single SRTOP0 field for all the security regions.
 * If this HSELx security region size is set at or below the HSELx low area
 * size, then there is no more security high area and
 * the MATRIX_SSR settings for the low area apply to the whole HSELx
 * security region.
 *
 *
 * SRTOPx Top Offset Security Region Size
 * 0000 0x00001000 4 Kbytes
 * 0001 0x00002000 8 Kbytes
 * 0010 0x00004000 16 Kbytes
 * 0011 0x00008000 32 Kbytes
 * 0100 0x00010000 64 Kbytes
 * 0101 0x00020000 128 Kbytes
 * 0110 0x00040000 256 Kbytes
 * 0111 0x00080000 512 Kbytes
 * 1000 0x00100000 1 Mbyte
 * 1001 0x00200000 2 Mbytes
 * 1010 0x00400000 4 Mbytes
 * 1011 0x00800000 8 Mbytes
 * 1100 0x01000000 16 Mbytes
 * 1101 0x02000000 32 Mbytes
 * 1110 0x04000000 64 Mbytes
 * 1111 0x08000000 128 Mbytes
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SRTSR7
 */
#define VTSS_HMATRIX2_MATRIX_SRTSR7          VTSS_IOREG(VTSS_TO_HMATRIX2,0x1e)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR7 . SRTOP7_SRTSR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR7_SRTOP7_SRTSR7(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR7_SRTOP7_SRTSR7     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR7_SRTOP7_SRTSR7(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR7 . SRTOP6_SRTSR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR7_SRTOP6_SRTSR7(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR7_SRTOP6_SRTSR7     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR7_SRTOP6_SRTSR7(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR7 . SRTOP5_SRTSR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR7_SRTOP5_SRTSR7(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR7_SRTOP5_SRTSR7     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR7_SRTOP5_SRTSR7(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR7 . SRTOP4_SRTSR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR7_SRTOP4_SRTSR7(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR7_SRTOP4_SRTSR7     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR7_SRTOP4_SRTSR7(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR7 . SRTOP3_SRTSR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR7_SRTOP3_SRTSR7(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR7_SRTOP3_SRTSR7     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR7_SRTOP3_SRTSR7(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR7 . SRTOP2_SRTSR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR7_SRTOP2_SRTSR7(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR7_SRTOP2_SRTSR7     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR7_SRTOP2_SRTSR7(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR7 . SRTOP1_SRTSR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR7_SRTOP1_SRTSR7(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR7_SRTOP1_SRTSR7     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR7_SRTOP1_SRTSR7(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \details
 * Field: ::VTSS_HMATRIX2_MATRIX_SRTSR7 . SRTOP0_SRTSR7
 */
#define  VTSS_F_HMATRIX2_MATRIX_SRTSR7_SRTOP0_SRTSR7(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HMATRIX2_MATRIX_SRTSR7_SRTOP0_SRTSR7     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HMATRIX2_MATRIX_SRTSR7_SRTOP0_SRTSR7(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Security Peripheral Select x Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Each MATRIX_SPSELR can configure the access security type for up to 32
 * peripherals:
 *
 *
 * MATRIX_SPSELR1 configures the access security type for peripheral
 * identifiers 0-31 (bits NSECP0-NSECP31)
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SPSELR1
 */
#define VTSS_HMATRIX2_MATRIX_SPSELR1         VTSS_IOREG(VTSS_TO_HMATRIX2,0xb0)

/**
 * \brief
 * NSECPy: Not Secured Peripheral
 *
 * \details
 * 0: The selected peripheral address space is configured as Secured access
 * (value of 0 has no effect if the peripheral
 * security type is Not Secured)
 * 1: The selected peripheral address space is configured as Not Secured
 * access (value of 1 has no effect if the peripheral
 * security type is Always Secured).
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_SPSELR1 . NSECP0_SPSELR1
 */
#define  VTSS_F_HMATRIX2_MATRIX_SPSELR1_NSECP0_SPSELR1(x)  (x)
#define  VTSS_M_HMATRIX2_MATRIX_SPSELR1_NSECP0_SPSELR1     0xffffffff
#define  VTSS_X_HMATRIX2_MATRIX_SPSELR1_NSECP0_SPSELR1(x)  (x)


/**
 * \brief Security Peripheral Select x Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Each MATRIX_SPSELR can configure the access security type for up to 32
 * peripherals:
 *
 *
 * MATRIX_SPSELR1 configures the access security type for peripheral
 * identifiers 32-63 (bits NSECP32-NSECP63)
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SPSELR2
 */
#define VTSS_HMATRIX2_MATRIX_SPSELR2         VTSS_IOREG(VTSS_TO_HMATRIX2,0xb1)

/**
 * \brief
 * NSECPy: Not Secured Peripheral
 *
 * \details
 * 0: The selected peripheral address space is configured as Secured access
 * (value of 0 has no effect if the peripheral
 * security type is Not Secured)
 * 1: The selected peripheral address space is configured as Not Secured
 * access (value of 1 has no effect if the peripheral
 * security type is Always Secured).
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_SPSELR2 . NSECP0_SPSELR2
 */
#define  VTSS_F_HMATRIX2_MATRIX_SPSELR2_NSECP0_SPSELR2(x)  (x)
#define  VTSS_M_HMATRIX2_MATRIX_SPSELR2_NSECP0_SPSELR2     0xffffffff
#define  VTSS_X_HMATRIX2_MATRIX_SPSELR2_NSECP0_SPSELR2(x)  (x)


/**
 * \brief Security Peripheral Select x Registers
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the
 * Write Protection Mode Register.
 *
 * Each MATRIX_SPSELR can configure the access security type for up to 32
 * peripherals:
 *
 *
 * MATRIX_SPSELR1 configures the access security type for peripheral
 * identifiers 64-95 (bits NSECP64-NSECP95)
 *
 * Register: \a HMATRIX2:HMATRIX2_REGS:MATRIX_SPSELR3
 */
#define VTSS_HMATRIX2_MATRIX_SPSELR3         VTSS_IOREG(VTSS_TO_HMATRIX2,0xb2)

/**
 * \brief
 * NSECPy: Not Secured Peripheral
 *
 * \details
 * 0: The selected peripheral address space is configured as Secured access
 * (value of 0 has no effect if the peripheral
 * security type is Not Secured)
 * 1: The selected peripheral address space is configured as Not Secured
 * access (value of 1 has no effect if the peripheral
 * security type is Always Secured).
 *
 * Field: ::VTSS_HMATRIX2_MATRIX_SPSELR3 . NSECP0_SPSELR3
 */
#define  VTSS_F_HMATRIX2_MATRIX_SPSELR3_NSECP0_SPSELR3(x)  (x)
#define  VTSS_M_HMATRIX2_MATRIX_SPSELR3_NSECP0_SPSELR3     0xffffffff
#define  VTSS_X_HMATRIX2_MATRIX_SPSELR3_NSECP0_SPSELR3(x)  (x)


#endif /* _VTSS_LAGUNA_REGS_HMATRIX2_H_ */
