#ifndef _VTSS_PHY_TS_REGS_COMMON_H_
#define _VTSS_PHY_TS_REGS_COMMON_H_

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


/* IO address mapping macro - may be changed for platform */
#if !defined(VTSS_IOADDR)
#define VTSS_IOADDR(o)        (o)
#endif

/* IO register access macro - may be changed for platform */
#if !defined(VTSS_IOREG)
/**
 * @param o - subtarget offset
 */
#define VTSS_IOREG(o)      (VTSS_IOADDR(o))
#endif

/* IO indexed register access macro - may be changed for platform */
#if !defined(VTSS_IOREG_IX)
/**
 * @param o  - subtarget offset
 * @param g  - group instance,
 * @param gw - group width
 * @param ro - register offset,
 * @param r  - register (instance) number
 */
#define VTSS_IOREG_IX(o, g, gw, r, ro)   VTSS_IOREG((o) + ((g) * (gw)) + (ro) + (r))
#endif


#endif /* _VTSS_PHY_TS_REGS_COMMON_H_ */
