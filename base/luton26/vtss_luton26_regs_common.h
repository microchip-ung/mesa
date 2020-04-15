#ifndef _VTSS_LUTON26_REGS_COMMON_H_
#define _VTSS_LUTON26_REGS_COMMON_H_

/*
 Copyright (c) 2004-2017 Microsemi Corporation "Microsemi".

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

#ifndef VTSS_BITOPS_DEFINED
#ifdef __ASSEMBLER__
#define VTSS_BIT(x)                   (1 << (x))
#define VTSS_BITMASK(x)               ((1 << (x)) - 1)
#else
#define VTSS_BIT(x)                   (1U << (x))
#define VTSS_BITMASK(x)               ((1U << (x)) - 1)
#endif
#define VTSS_EXTRACT_BITFIELD(x,o,w)  (((x) >> (o)) & VTSS_BITMASK(w))
#define VTSS_ENCODE_BITFIELD(x,o,w)   (((x) & VTSS_BITMASK(w)) << (o))
#define VTSS_ENCODE_BITMASK(o,w)      (VTSS_BITMASK(w) << (o))
#define VTSS_BITOPS_DEFINED
#endif /* VTSS_BITOPS_DEFINED */


/*
 * Target offset base(s)
 */
#define VTSS_IO_ORIGIN1_OFFSET 0x60000000
#define VTSS_IO_ORIGIN1_SIZE   0x01000000
#define VTSS_IO_ORIGIN2_OFFSET 0x70000000
#define VTSS_IO_ORIGIN2_SIZE   0x00200000
#ifndef VTSS_IO_OFFSET1
#define VTSS_IO_OFFSET1(offset) (VTSS_IO_ORIGIN1_OFFSET + offset)
#endif
#ifndef VTSS_IO_OFFSET2
#define VTSS_IO_OFFSET2(offset) (VTSS_IO_ORIGIN2_OFFSET + offset)
#endif

/* Main target address offsets */
#define VTSS_TO_DEVCPU_ORG VTSS_IO_OFFSET1(0x00000000) /*!< Base offset for target DEVCPU_ORG */
#define VTSS_TO_SYS        VTSS_IO_OFFSET1(0x00010000) /*!< Base offset for target SYS */
#define VTSS_TO_ANA        VTSS_IO_OFFSET1(0x00020000) /*!< Base offset for target ANA */
#define VTSS_TO_REW        VTSS_IO_OFFSET1(0x00030000) /*!< Base offset for target REW */
#define VTSS_TO_ES0        VTSS_IO_OFFSET1(0x00040000) /*!< Base offset for target ES0 */
#define VTSS_TO_S1         VTSS_IO_OFFSET1(0x00050000) /*!< Base offset for target S1 */
#define VTSS_TO_S2         VTSS_IO_OFFSET1(0x00060000) /*!< Base offset for target S2 */
#define VTSS_TO_DEVCPU_GCB VTSS_IO_OFFSET1(0x00070000) /*!< Base offset for target DEVCPU_GCB */
#define VTSS_TO_DEVCPU_QS  VTSS_IO_OFFSET1(0x00080000) /*!< Base offset for target DEVCPU_QS */
#define VTSS_TO_DEVCPU_PI  VTSS_IO_OFFSET1(0x00090000) /*!< Base offset for target DEVCPU_PI */
#define VTSS_TO_MACRO_CTRL VTSS_IO_OFFSET1(0x000a0000) /*!< Base offset for target MACRO_CTRL */
#define VTSS_TO_DEV_0      VTSS_IO_OFFSET1(0x001e0000) /*!< Base offset for target DEV_0 */
#define VTSS_TO_DEV_1      VTSS_IO_OFFSET1(0x001f0000) /*!< Base offset for target DEV_1 */
#define VTSS_TO_DEV_2      VTSS_IO_OFFSET1(0x00200000) /*!< Base offset for target DEV_2 */
#define VTSS_TO_DEV_3      VTSS_IO_OFFSET1(0x00210000) /*!< Base offset for target DEV_3 */
#define VTSS_TO_DEV_4      VTSS_IO_OFFSET1(0x00220000) /*!< Base offset for target DEV_4 */
#define VTSS_TO_DEV_5      VTSS_IO_OFFSET1(0x00230000) /*!< Base offset for target DEV_5 */
#define VTSS_TO_DEV_6      VTSS_IO_OFFSET1(0x00240000) /*!< Base offset for target DEV_6 */
#define VTSS_TO_DEV_7      VTSS_IO_OFFSET1(0x00250000) /*!< Base offset for target DEV_7 */
#define VTSS_TO_DEV_8      VTSS_IO_OFFSET1(0x00260000) /*!< Base offset for target DEV_8 */
#define VTSS_TO_DEV_9      VTSS_IO_OFFSET1(0x00270000) /*!< Base offset for target DEV_9 */
#define VTSS_TO_DEV_10     VTSS_IO_OFFSET1(0x00280000) /*!< Base offset for target DEV_10 */
#define VTSS_TO_DEV_11     VTSS_IO_OFFSET1(0x00290000) /*!< Base offset for target DEV_11 */
#define VTSS_TO_DEV_12     VTSS_IO_OFFSET1(0x002a0000) /*!< Base offset for target DEV_12 */
#define VTSS_TO_DEV_13     VTSS_IO_OFFSET1(0x002b0000) /*!< Base offset for target DEV_13 */
#define VTSS_TO_DEV_14     VTSS_IO_OFFSET1(0x002c0000) /*!< Base offset for target DEV_14 */
#define VTSS_TO_DEV_15     VTSS_IO_OFFSET1(0x002d0000) /*!< Base offset for target DEV_15 */
#define VTSS_TO_DEV_16     VTSS_IO_OFFSET1(0x002e0000) /*!< Base offset for target DEV_16 */
#define VTSS_TO_DEV_17     VTSS_IO_OFFSET1(0x002f0000) /*!< Base offset for target DEV_17 */
#define VTSS_TO_DEV_18     VTSS_IO_OFFSET1(0x00300000) /*!< Base offset for target DEV_18 */
#define VTSS_TO_DEV_19     VTSS_IO_OFFSET1(0x00310000) /*!< Base offset for target DEV_19 */
#define VTSS_TO_DEV_20     VTSS_IO_OFFSET1(0x00320000) /*!< Base offset for target DEV_20 */
#define VTSS_TO_DEV_21     VTSS_IO_OFFSET1(0x00330000) /*!< Base offset for target DEV_21 */
#define VTSS_TO_DEV_22     VTSS_IO_OFFSET1(0x00340000) /*!< Base offset for target DEV_22 */
#define VTSS_TO_DEV_23     VTSS_IO_OFFSET1(0x00350000) /*!< Base offset for target DEV_23 */
#define VTSS_TO_DEV_24     VTSS_IO_OFFSET1(0x00360000) /*!< Base offset for target DEV_24 */
#define VTSS_TO_DEV_25     VTSS_IO_OFFSET1(0x00370000) /*!< Base offset for target DEV_25 */
#define VTSS_TO_CFG        VTSS_IO_OFFSET2(0x00000000) /*!< Base offset for target CFG */
#define VTSS_TO_UART       VTSS_IO_OFFSET2(0x00100000) /*!< Base offset for target UART */
#define VTSS_TO_TWI        VTSS_IO_OFFSET2(0x00100400) /*!< Base offset for target TWI */
#define VTSS_TO_SBA        VTSS_IO_OFFSET2(0x00110000) /*!< Base offset for target SBA */
#define VTSS_TO_DMAC       VTSS_IO_OFFSET2(0x00110800) /*!< Base offset for target DMAC */

/* IO address mapping macro - may be changed for platform */
#if !defined(VTSS_IOADDR)
#define VTSS_IOADDR(t,o)        ((t) + ((o) << 2))
#endif

/* IO register access macro - may be changed for platform */
#if !defined(VTSS_IOREG)
/** 
 * @param t - target base offset
 * @param o - subtarget offset
 */
#define VTSS_IOREG(t,o)      (*((volatile unsigned long*)(VTSS_IOADDR(t,o))))
#endif

/* IO indexed register access macro - may be changed for platform */
#if !defined(VTSS_IOREG_IX)
/** 
 * @param t  - target base offset
 * @param o  - subtarget offset
 * @param g  - group instance, 
 * @param gw - group width
 * @param ro - register offset, 
 * @param r  - register (instance) number
 */
#define VTSS_IOREG_IX(t,o,g,gw,r,ro)   VTSS_IOREG(t,(o) + ((g) * (gw)) + (ro) + (r))
#endif

#ifdef VTSS_HARDWARE_WANT_TARGET_ENUMS
/*
 * This section is primarily for documentation purposes.
 */

/**
  * \brief Target VCAP_CORE target offset(s)
  */
enum vtss_target_VCAP_CORE_e {
    VTSS_TOE_ES0             = VTSS_TO_ES0,
    VTSS_TOE_IS1             = VTSS_TO_IS1,
    VTSS_TOE_IS2             = VTSS_TO_IS2,
};

/**
  * \brief Target DEV_GMII target offset(s)
  */
enum vtss_target_DEV_GMII_e {
    VTSS_TOE_DEV_0           = VTSS_TO_DEV_0,
    VTSS_TOE_DEV_1           = VTSS_TO_DEV_1,
    VTSS_TOE_DEV_2           = VTSS_TO_DEV_2,
    VTSS_TOE_DEV_3           = VTSS_TO_DEV_3,
    VTSS_TOE_DEV_4           = VTSS_TO_DEV_4,
    VTSS_TOE_DEV_5           = VTSS_TO_DEV_5,
    VTSS_TOE_DEV_6           = VTSS_TO_DEV_6,
    VTSS_TOE_DEV_7           = VTSS_TO_DEV_7,
    VTSS_TOE_DEV_8           = VTSS_TO_DEV_8,
    VTSS_TOE_DEV_9           = VTSS_TO_DEV_9,
};

/**
  * \brief Target DEV target offset(s)
  */
enum vtss_target_DEV_e {
    VTSS_TOE_DEV_10          = VTSS_TO_DEV_10,
    VTSS_TOE_DEV_11          = VTSS_TO_DEV_11,
    VTSS_TOE_DEV_12          = VTSS_TO_DEV_12,
    VTSS_TOE_DEV_13          = VTSS_TO_DEV_13,
    VTSS_TOE_DEV_14          = VTSS_TO_DEV_14,
    VTSS_TOE_DEV_15          = VTSS_TO_DEV_15,
    VTSS_TOE_DEV_16          = VTSS_TO_DEV_16,
    VTSS_TOE_DEV_17          = VTSS_TO_DEV_17,
    VTSS_TOE_DEV_18          = VTSS_TO_DEV_18,
    VTSS_TOE_DEV_19          = VTSS_TO_DEV_19,
    VTSS_TOE_DEV_20          = VTSS_TO_DEV_20,
    VTSS_TOE_DEV_21          = VTSS_TO_DEV_21,
    VTSS_TOE_DEV_22          = VTSS_TO_DEV_22,
    VTSS_TOE_DEV_23          = VTSS_TO_DEV_23,
    VTSS_TOE_DEV_24          = VTSS_TO_DEV_24,
    VTSS_TOE_DEV_25          = VTSS_TO_DEV_25,
};

#endif /* VTSS_HARDWARE_WANT_TARGET_ENUMS */


#endif /* _VTSS_LUTON26_REGS_COMMON_H_ */
