// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_ES6514_CLOCK_CIL_H_
#define _VTSS_ES6514_CLOCK_CIL_H_

#if !defined(VTSS_CHIP_ES6514)
/* Use relative DWORD addresses for registers - must be first */
#define VTSS_IOADDR(t, o) ((((t) - VTSS_IO_ORIGIN1_OFFSET) >> 2) + (o))
#define VTSS_IOREG(t, o)  (VTSS_IOADDR(t, o))
#endif // VTSS_CHIP_ES6514

/* Use relative addresses for registers - must be first */
#define VTSS_ES6514_IOADDR(t, o) ((t) + (o))
#define VTSS_ES6514_IOREG(t, o)  (VTSS_ES6514_IOADDR(t, o))

#include "vtss_api.h"

#include "../ail/vtss_state.h"

/* ================================================================= *
 *  Register access
 * ================================================================= */
/* include header file generated from CML */
#if defined(VTSS_ARCH_SERVAL_T)
#include "../jaguar2/vtss_servalt_regs.h"
#endif
#if defined(VTSS_CHIP_ES6514)
#include "vtss_es6514_regs.h"
#endif
/*
Do not declare puplic
vtss_rc vtss_es6514_rd(const vtss_state_t *vtss_state, u32 addr, u32 *value);
vtss_rc vtss_es6514_wr(const vtss_state_t *vtss_state, u32 addr, u32 value);
vtss_rc vtss_es6514_wrm(const vtss_state_t *vtss_state, u32 addr, u32 value, u32
mask);
*/

#if defined(VTSS_ARCH_SERVAL_T)
#define VTSS_TO_SD10G65(channel) (VTSS_TO_XGANA_0 + (channel * (VTSS_TO_XGANA_1 - VTSS_TO_XGANA_0)))
#define VTSS_TO_SD10G65_DIG(channel)                                                               \
    (VTSS_TO_XGDIG_0 + (channel * (VTSS_TO_XGDIG_1 - VTSS_TO_XGDIG_0)))
#define VTSS_TO_PLL_XFI(channel) (VTSS_TO_XGXFI_0 + (channel * (VTSS_TO_XGXFI_1 - VTSS_TO_XGXFI_0)))

#else
#define VTSS_TO_SD10G65(channel)                                                                   \
    (VTSS_TO_SD10G65_0 + (channel * (VTSS_TO_SD10G65_1 - VTSS_TO_SD10G65_0)))
#define VTSS_TO_SD10G65_DIG(channel)                                                               \
    (VTSS_TO_SD10G65_DIG_0 + (channel * (VTSS_TO_SD10G65_DIG_1 - VTSS_TO_SD10G65_DIG_0)))
#endif

/* Concatenations */
#define ES6514_ADDR(tgt, addr)                VTSS_##tgt##_##addr
#define ES6514_ADDR_X(tgt, addr, x)           VTSS_##tgt##_##addr(x)
#define ES6514_GET_FLD(tgt, addr, fld, value) VTSS_X_##tgt##_##addr##_##fld(value)
#if defined(VTSS_ARCH_SERVAL_T)
#define ES6514_GET_BIT(tgt, addr, fld, value) (VTSS_X_##tgt##_##addr##_##fld(value))
#else
#define ES6514_GET_BIT(tgt, addr, fld, value) (VTSS_F_##tgt##_##addr##_##fld & (value) ? 1 : 0)
#endif
#define ES6514_PUT_FLD(tgt, addr, fld, value) VTSS_F_##tgt##_##addr##_##fld(value)
#if defined(VTSS_ARCH_SERVAL_T)
#define ES6514_PUT_BIT(tgt, addr, fld, value) (VTSS_F_##tgt##_##addr##_##fld(value))
#else
#define ES6514_PUT_BIT(tgt, addr, fld, value) ((value) ? VTSS_F_##tgt##_##addr##_##fld : 0)
#endif
#define ES6514_MSK(tgt, addr, fld) VTSS_M_##tgt##_##addr##_##fld
#if defined(VTSS_ARCH_SERVAL_T)
#define ES6514_MSK_BIT(tgt, addr, fld) VTSS_M_##tgt##_##addr##_##fld
#else
#define ES6514_MSK_BIT(tgt, addr, fld) VTSS_F_##tgt##_##addr##_##fld
#endif

/* ============================== */
/* Helper Macros                  */
/* ============================== */
/* Read register */
#define ES6514_RD_REG(reg, value) VTSS_RC(vtss_es6514_rd(vtss_state, reg, value));

/* Read and extract register field */
#define ES6514_RD_FLD(reg, tgt, addr, fld, value)                                                  \
    {                                                                                              \
        u32 __x__;                                                                                 \
        ES6514_RD_REG(reg, &__x__);                                                                \
        *(value) = ES6514_GET_FLD(tgt, addr, fld, __x__);                                          \
    }

/* Read and extract register bit field */
#define ES6514_RD_BIT(reg, tgt, addr, fld, value)                                                  \
    {                                                                                              \
        u32 __x__;                                                                                 \
        ES6514_RD_REG(reg, &__x__);                                                                \
        *(value) = ES6514_GET_BIT(tgt, addr, fld, __x__);                                          \
    }

/* Write register */
#define ES6514_WR_REG(reg, value) VTSS_RC(vtss_es6514_wr(vtss_state, reg, value));

/* Write register masked */
#define ES6514_WR_MSK(reg, value, mask) VTSS_RC(vtss_es6514_wrm(vtss_state, reg, value, mask));

/* Write non-replicated register field */
#define ES6514_WR_FLD(reg, tgt, addr, fld, value)                                                  \
    ES6514_WR_MSK(reg, ES6514_PUT_FLD(tgt, addr, fld, value), ES6514_MSK(tgt, addr, fld))

/* Write register bit field */
#define ES6514_WR_BIT(reg, tgt, addr, fld, value)                                                  \
    ES6514_WR_MSK(reg, ES6514_PUT_BIT(tgt, addr, fld, value), ES6514_PUT_BIT(tgt, addr, fld, 1))

/* ============================== */
/* User Macros                    */
/* ============================== */

/* - No replication ------------------------------------------------ */
/* Read register */
#define ES6514_RD(tgt, addr, value) ES6514_RD_REG(ES6514_ADDR(tgt, addr), value)

/* Read register field */
#define ES6514_RDF(tgt, addr, fld, value)                                                          \
    ES6514_RD_FLD(ES6514_ADDR(tgt, addr), tgt, addr, fld, value)

/* Read register bit field */
#define ES6514_RDB(tgt, addr, fld, value)                                                          \
    ES6514_RD_BIT(ES6514_ADDR(tgt, addr), tgt, addr, fld, value)

/* Write register */
#define ES6514_WR(tgt, addr, value) ES6514_WR_REG(ES6514_ADDR(tgt, addr), value);

/* Write register field */
#define ES6514_WRF(tgt, addr, fld, value)                                                          \
    ES6514_WR_FLD(ES6514_ADDR(tgt, addr), tgt, addr, fld, value)

/* Write register bit field */
#define ES6514_WRB(tgt, addr, fld, value)                                                          \
    ES6514_WR_BIT(ES6514_ADDR(tgt, addr), tgt, addr, fld, value)

/* Write register masked and set/clear */
#define ES6514_WRM(tgt, addr, value, mask) ES6514_WR_MSK(ES6514_ADDR(tgt, addr), value, mask)
#define ES6514_WRM_SET(tgt, addr, mask)    ES6514_WRM(tgt, addr, mask, mask)
#define ES6514_WRM_CLR(tgt, addr, mask)    ES6514_WRM(tgt, addr, 0, mask)

/* - Single replication (X) ---------------------------------------- */

/* Read replicated register */
#define ES6514_RDX(tgt, addr, x, value) ES6514_RD_REG(ES6514_ADDR_X(tgt, addr, x), value)

/* Read replicated register field */
#define ES6514_RDXF(tgt, addr, x, fld, value)                                                      \
    ES6514_RD_FLD(ES6514_ADDR_X(tgt, addr, x), tgt, addr, fld, value)

/* Read register bit field */
#define ES6514_RDXB(tgt, addr, x, fld, value)                                                      \
    ES6514_RD_BIT(ES6514_ADDR_X(tgt, addr, x), tgt, addr, fld, value)

/* Write replicated register */
#define ES6514_WRX(tgt, addr, x, value) ES6514_WR_REG(ES6514_ADDR_X(tgt, addr, x), value)

/* Write replicated register field */
#define ES6514_WRXF(tgt, addr, x, fld, value)                                                      \
    ES6514_WR_FLD(ES6514_ADDR_X(tgt, addr, x), tgt, addr, fld, value)

/* Write register bit field */
#define ES6514_WRXB(tgt, addr, x, fld, value)                                                      \
    ES6514_WR_BIT(ES6514_ADDR_X(tgt, addr, x), tgt, addr, fld, value)

/* Write register masked and set/clear */
#define ES6514_WRXM(tgt, addr, x, value, mask)                                                     \
    ES6514_WR_MSK(ES6514_ADDR_X(tgt, addr, x), value, mask)
#define ES6514_WRXM_SET(tgt, addr, x, mask) ES6514_WRXM(tgt, addr, x, mask, mask)
#define ES6514_WRXM_CLR(tgt, addr, x, mask) ES6514_WRXM(tgt, addr, x, 0, mask)

vtss_rc vtss_omega_clock_output_filter_bw_refresh(vtss_state_t *vtss_state, const u8 clock_output);

vtss_rc vtss_es6514_clock_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

#endif /* _VTSS_ES6514_CLOCK_CIL_H_ */
