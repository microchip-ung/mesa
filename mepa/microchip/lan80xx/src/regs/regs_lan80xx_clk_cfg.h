// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _LAN80XX_MALIBU25G_REGS_CLK_CFG_H_
#define _LAN80XX_MALIBU25G_REGS_CLK_CFG_H_

#include "regs_lan8042_common.h"

/***********************************************************************
 *
 * Target: \a CLK_CFG
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a CLK_CFG:SYSPLL
 *
 * SYSPLL Configuration Registers
 */


/**
 * \brief SYSPLL Command Register
 *
 * \details
 * SYSPLL Command Register
 *
 * Register: \a CLK_CFG:SYSPLL:SYSPLL_CMD_REG
 */
#define LAN80XX_CLK_CFG_SYSPLL_CMD_REG          LAN80XX_IOREG(MMD_ID_CLK_CFG, 0, 0x600)

/**
 * \brief
 * Set to cause the hardware clock controller to update the SYSPLL with new
 * settings and reset the pll. Self-clearing.
 *
 * \details
 * Field: ::LAN80XX_CLK_CFG_SYSPLL_CMD_REG . SYSPLL_UPDATE
 */
#define  LAN80XX_F_CLK_CFG_SYSPLL_CMD_REG_SYSPLL_UPDATE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_CLK_CFG_SYSPLL_CMD_REG_SYSPLL_UPDATE  LAN80XX_BIT(0)
#define  LAN80XX_X_CLK_CFG_SYSPLL_CMD_REG_SYSPLL_UPDATE(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SYSPLL Range Register
 *
 * \details
 * SYSPLL Range Register
 *
 * Register: \a CLK_CFG:SYSPLL:SYSPLL_RANGE_REG
 */
#define LAN80XX_CLK_CFG_SYSPLL_RANGE_REG        LAN80XX_IOREG(MMD_ID_CLK_CFG, 0, 0x601)

/**
 * \details
 * 000:      sets the PLL loop filter in Fractional mode to work with
 * post-reference divider frequency
 * 000~111: sets the PLL loop filter in Integer mode to work with the
 * post-reference divider frequency. Choose the highest valid range for
 * best jitter performance
 *
 * Field: ::LAN80XX_CLK_CFG_SYSPLL_RANGE_REG . SYSPLL_RANGE
 */
#define  LAN80XX_F_CLK_CFG_SYSPLL_RANGE_REG_SYSPLL_RANGE(x)  LAN80XX_ENCODE_BITFIELD(x,0,3)
#define  LAN80XX_M_CLK_CFG_SYSPLL_RANGE_REG_SYSPLL_RANGE     LAN80XX_ENCODE_BITMASK(0,3)
#define  LAN80XX_X_CLK_CFG_SYSPLL_RANGE_REG_SYSPLL_RANGE(x)  LAN80XX_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief SYSPLL Divider Value Register
 *
 * \details
 * SYSPLL Divider Value Register
 *
 * Register: \a CLK_CFG:SYSPLL:SYSPLL_DIVR_REG
 */
#define LAN80XX_CLK_CFG_SYSPLL_DIVR_REG         LAN80XX_IOREG(MMD_ID_CLK_CFG, 0, 0x602)

/**
 * \brief
 * The DIVR[5:0] setting to the PLL IPthe divisor of PLL is DIVR+1
 *
 * \details
 * Field: ::LAN80XX_CLK_CFG_SYSPLL_DIVR_REG . SYSPLL_DIVR
 */
#define  LAN80XX_F_CLK_CFG_SYSPLL_DIVR_REG_SYSPLL_DIVR(x)  LAN80XX_ENCODE_BITFIELD(x,0,6)
#define  LAN80XX_M_CLK_CFG_SYSPLL_DIVR_REG_SYSPLL_DIVR     LAN80XX_ENCODE_BITMASK(0,6)
#define  LAN80XX_X_CLK_CFG_SYSPLL_DIVR_REG_SYSPLL_DIVR(x)  LAN80XX_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief SYSPLL Divider Control Register
 *
 * \details
 * SYSPLL Divider Control Register
 *
 * Register: \a CLK_CFG:SYSPLL:SYSPLL_DIVQ_REG
 */
#define LAN80XX_CLK_CFG_SYSPLL_DIVQ_REG         LAN80XX_IOREG(MMD_ID_CLK_CFG, 0, 0x603)

/**
 * \brief
 * the DIVQ[14:0] setting to the PLL IP0-1 (not valid)2-10 (all
 * values)12-508 (in steps of 4)512-1016 (in steps of 8)1024-2032 (in steps
 * of 16)2048-4064 (in steps of 32)4096-8128 (in steps of 64)8192-16256 (in
 * steps of 128)16384-32512 (in steps of 256)Divide values that are not in
 * exact step increments will round down to lower step value.
 *
 * \details
 * Field: ::LAN80XX_CLK_CFG_SYSPLL_DIVQ_REG . SYSPLL_DIVQ
 */
#define  LAN80XX_F_CLK_CFG_SYSPLL_DIVQ_REG_SYSPLL_DIVQ(x)  LAN80XX_ENCODE_BITFIELD(x,0,15)
#define  LAN80XX_M_CLK_CFG_SYSPLL_DIVQ_REG_SYSPLL_DIVQ     LAN80XX_ENCODE_BITMASK(0,15)
#define  LAN80XX_X_CLK_CFG_SYSPLL_DIVQ_REG_SYSPLL_DIVQ(x)  LAN80XX_EXTRACT_BITFIELD(x,0,15)


/**
 * \brief SYSPLL Divider Fractional High Register
 *
 * \details
 * SYSPLL Divider Fractional High Register
 *
 * Register: \a CLK_CFG:SYSPLL:SYSPLL_DIVFF_HI_REG
 */
#define LAN80XX_CLK_CFG_SYSPLL_DIVFF_HI_REG     LAN80XX_IOREG(MMD_ID_CLK_CFG, 0, 0x604)

/**
 * \brief
 * The DIVIFF[23:16] setting to the PLL IP
 *
 * \details
 * Field: ::LAN80XX_CLK_CFG_SYSPLL_DIVFF_HI_REG . SYSPLL_DIVFF_HI
 */
#define  LAN80XX_F_CLK_CFG_SYSPLL_DIVFF_HI_REG_SYSPLL_DIVFF_HI(x)  LAN80XX_ENCODE_BITFIELD(x,0,8)
#define  LAN80XX_M_CLK_CFG_SYSPLL_DIVFF_HI_REG_SYSPLL_DIVFF_HI     LAN80XX_ENCODE_BITMASK(0,8)
#define  LAN80XX_X_CLK_CFG_SYSPLL_DIVFF_HI_REG_SYSPLL_DIVFF_HI(x)  LAN80XX_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief SYSPLL Divider Fractional Low Register
 *
 * \details
 * SYSPLL Divider Fractional Low Register
 *
 * Register: \a CLK_CFG:SYSPLL:SYSPLL_DIVFF_LO_REG
 */
#define LAN80XX_CLK_CFG_SYSPLL_DIVFF_LO_REG     LAN80XX_IOREG(MMD_ID_CLK_CFG, 0, 0x605)

/**
 * \brief
 * The DIVIFF[15:0] setting to the PLL IP
 *
 * \details
 * Field: ::LAN80XX_CLK_CFG_SYSPLL_DIVFF_LO_REG . SYSPLL_DIVFF_LO
 */
#define  LAN80XX_F_CLK_CFG_SYSPLL_DIVFF_LO_REG_SYSPLL_DIVFF_LO(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_CLK_CFG_SYSPLL_DIVFF_LO_REG_SYSPLL_DIVFF_LO     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_CLK_CFG_SYSPLL_DIVFF_LO_REG_SYSPLL_DIVFF_LO(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief SYSPLL Divider Integer Register
 *
 * \details
 * SYSPLL Divider Integer Register
 *
 * Register: \a CLK_CFG:SYSPLL:SYSPLL_DIVFI_REG
 */
#define LAN80XX_CLK_CFG_SYSPLL_DIVFI_REG        LAN80XX_IOREG(MMD_ID_CLK_CFG, 0, 0x606)

/**
 * \brief
 * The DIVFI[6:0] setting to the PLL IPthe devisor of PLL is DIVFI+1
 *
 * \details
 * Field: ::LAN80XX_CLK_CFG_SYSPLL_DIVFI_REG . SYSPLL_DIVFI
 */
#define  LAN80XX_F_CLK_CFG_SYSPLL_DIVFI_REG_SYSPLL_DIVFI(x)  LAN80XX_ENCODE_BITFIELD(x,0,7)
#define  LAN80XX_M_CLK_CFG_SYSPLL_DIVFI_REG_SYSPLL_DIVFI     LAN80XX_ENCODE_BITMASK(0,7)
#define  LAN80XX_X_CLK_CFG_SYSPLL_DIVFI_REG_SYSPLL_DIVFI(x)  LAN80XX_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief SYSPLL Status Register
 *
 * \details
 * SYSPLL Status Register
 *
 * Register: \a CLK_CFG:SYSPLL:SYSPLL_STS_REG
 */
#define LAN80XX_CLK_CFG_SYSPLL_STS_REG          LAN80XX_IOREG(MMD_ID_CLK_CFG, 0, 0x607)

/**
 * \brief
 * hardware clock controller indicates PLL is locked
 *
 * \details
 * Field: ::LAN80XX_CLK_CFG_SYSPLL_STS_REG . SYSPLL_STS
 */
#define  LAN80XX_F_CLK_CFG_SYSPLL_STS_REG_SYSPLL_STS(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_CLK_CFG_SYSPLL_STS_REG_SYSPLL_STS  LAN80XX_BIT(0)
#define  LAN80XX_X_CLK_CFG_SYSPLL_STS_REG_SYSPLL_STS(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a CLK_CFG:LTCPLL
 *
 * LTCPLL Configuration Registers
 */


/**
 * \brief LTCPLL Command Register
 *
 * \details
 * LTCPLL Command Register
 *
 * Register: \a CLK_CFG:LTCPLL:LTCPLL_CMD_REG
 */
#define LAN80XX_CLK_CFG_LTCPLL_CMD_REG          LAN80XX_IOREG(MMD_ID_CLK_CFG, 0, 0x608)

/**
 * \brief
 * Set to cause the hardware clock controller to hold the ltcclk pll in
 * reset (lowest power state)
 *
 * \details
 * Field: ::LAN80XX_CLK_CFG_LTCPLL_CMD_REG . LTCPLL_POWERDOWN
 */
#define  LAN80XX_F_CLK_CFG_LTCPLL_CMD_REG_LTCPLL_POWERDOWN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_CLK_CFG_LTCPLL_CMD_REG_LTCPLL_POWERDOWN  LAN80XX_BIT(1)
#define  LAN80XX_X_CLK_CFG_LTCPLL_CMD_REG_LTCPLL_POWERDOWN(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Set to cause the hardware clock controller to update the LTCPLL with new
 * settings and reset the pll. Self-clearing
 *
 * \details
 * Field: ::LAN80XX_CLK_CFG_LTCPLL_CMD_REG . LTCPLL_UPDATE
 */
#define  LAN80XX_F_CLK_CFG_LTCPLL_CMD_REG_LTCPLL_UPDATE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_CLK_CFG_LTCPLL_CMD_REG_LTCPLL_UPDATE  LAN80XX_BIT(0)
#define  LAN80XX_X_CLK_CFG_LTCPLL_CMD_REG_LTCPLL_UPDATE(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief LTCPLL Range Register
 *
 * \details
 * LTCPLL Range Register
 *
 * Register: \a CLK_CFG:LTCPLL:LTCPLL_RANGE_REG
 */
#define LAN80XX_CLK_CFG_LTCPLL_RANGE_REG        LAN80XX_IOREG(MMD_ID_CLK_CFG, 0, 0x609)

/**
 * \details
 * 000:      sets the PLL loop filter in Fractional mode to work with
 * post-reference divider frequency
 * 000~111: sets the PLL loop filter in Integer mode to work with the
 * post-reference divider frequency. Choose the highest valid range for
 * best jitter performance
 *
 * Field: ::LAN80XX_CLK_CFG_LTCPLL_RANGE_REG . LTCPLL_RANGE
 */
#define  LAN80XX_F_CLK_CFG_LTCPLL_RANGE_REG_LTCPLL_RANGE(x)  LAN80XX_ENCODE_BITFIELD(x,0,3)
#define  LAN80XX_M_CLK_CFG_LTCPLL_RANGE_REG_LTCPLL_RANGE     LAN80XX_ENCODE_BITMASK(0,3)
#define  LAN80XX_X_CLK_CFG_LTCPLL_RANGE_REG_LTCPLL_RANGE(x)  LAN80XX_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief LTCPLL Divider Value Register
 *
 * \details
 * LTCPLL Divider Value Register
 *
 * Register: \a CLK_CFG:LTCPLL:LTCPLL_DIVR_REG
 */
#define LAN80XX_CLK_CFG_LTCPLL_DIVR_REG         LAN80XX_IOREG(MMD_ID_CLK_CFG, 0, 0x60a)

/**
 * \brief
 * The DIVR[5:0] setting to the PLL IPthe divisor of PLL is DIVR+1
 *
 * \details
 * Field: ::LAN80XX_CLK_CFG_LTCPLL_DIVR_REG . LTCPLL_DIVR
 */
#define  LAN80XX_F_CLK_CFG_LTCPLL_DIVR_REG_LTCPLL_DIVR(x)  LAN80XX_ENCODE_BITFIELD(x,0,6)
#define  LAN80XX_M_CLK_CFG_LTCPLL_DIVR_REG_LTCPLL_DIVR     LAN80XX_ENCODE_BITMASK(0,6)
#define  LAN80XX_X_CLK_CFG_LTCPLL_DIVR_REG_LTCPLL_DIVR(x)  LAN80XX_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief LTCPLL Divider Control Register
 *
 * \details
 * LTCPLL Divider Control Register
 *
 * Register: \a CLK_CFG:LTCPLL:LTCPLL_DIVQ_REG
 */
#define LAN80XX_CLK_CFG_LTCPLL_DIVQ_REG         LAN80XX_IOREG(MMD_ID_CLK_CFG, 0, 0x60b)

/**
 * \brief
 * the DIVQ[14:0] setting to the PLL IP0-1 (not valid)2-10 (all
 * values)12-508 (in steps of 4)512-1016 (in steps of 8)1024-2032 (in steps
 * of 16)2048-4064 (in steps of 32)4096-8128 (in steps of 64)8192-16256 (in
 * steps of 128)16384-32512 (in steps of 256)Divide values that are not in
 * exact step increments will round down to lower step value.
 *
 * \details
 * Field: ::LAN80XX_CLK_CFG_LTCPLL_DIVQ_REG . LTCPLL_DIVQ
 */
#define  LAN80XX_F_CLK_CFG_LTCPLL_DIVQ_REG_LTCPLL_DIVQ(x)  LAN80XX_ENCODE_BITFIELD(x,0,15)
#define  LAN80XX_M_CLK_CFG_LTCPLL_DIVQ_REG_LTCPLL_DIVQ     LAN80XX_ENCODE_BITMASK(0,15)
#define  LAN80XX_X_CLK_CFG_LTCPLL_DIVQ_REG_LTCPLL_DIVQ(x)  LAN80XX_EXTRACT_BITFIELD(x,0,15)


/**
 * \brief LTCPLL Divider Fractional High Register
 *
 * \details
 * LTCPLL Divider Fractional High Register
 *
 * Register: \a CLK_CFG:LTCPLL:LTCPLL_DIVFF_HI_REG
 */
#define LAN80XX_CLK_CFG_LTCPLL_DIVFF_HI_REG     LAN80XX_IOREG(MMD_ID_CLK_CFG, 0, 0x60c)

/**
 * \brief
 * The DIVIFF[23:16] setting to the PLL IP
 *
 * \details
 * Field: ::LAN80XX_CLK_CFG_LTCPLL_DIVFF_HI_REG . LTCPLL_DIVFF_HI
 */
#define  LAN80XX_F_CLK_CFG_LTCPLL_DIVFF_HI_REG_LTCPLL_DIVFF_HI(x)  LAN80XX_ENCODE_BITFIELD(x,0,8)
#define  LAN80XX_M_CLK_CFG_LTCPLL_DIVFF_HI_REG_LTCPLL_DIVFF_HI     LAN80XX_ENCODE_BITMASK(0,8)
#define  LAN80XX_X_CLK_CFG_LTCPLL_DIVFF_HI_REG_LTCPLL_DIVFF_HI(x)  LAN80XX_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief LTCPLL Divider Fractional Low Register
 *
 * \details
 * LTCPLL Divider Fractional Low Register
 *
 * Register: \a CLK_CFG:LTCPLL:LTCPLL_DIVFF_LO_REG
 */
#define LAN80XX_CLK_CFG_LTCPLL_DIVFF_LO_REG     LAN80XX_IOREG(MMD_ID_CLK_CFG, 0, 0x60d)

/**
 * \brief
 * The DIVIFF[15:0] setting to the PLL IP
 *
 * \details
 * Field: ::LAN80XX_CLK_CFG_LTCPLL_DIVFF_LO_REG . LTCPLL_DIVFF_LO
 */
#define  LAN80XX_F_CLK_CFG_LTCPLL_DIVFF_LO_REG_LTCPLL_DIVFF_LO(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_CLK_CFG_LTCPLL_DIVFF_LO_REG_LTCPLL_DIVFF_LO     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_CLK_CFG_LTCPLL_DIVFF_LO_REG_LTCPLL_DIVFF_LO(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief LTCPLL Divider Integer Register
 *
 * \details
 * LTCPLL Divider Integer Register
 *
 * Register: \a CLK_CFG:LTCPLL:LTCPLL_DIVFI_REG
 */
#define LAN80XX_CLK_CFG_LTCPLL_DIVFI_REG        LAN80XX_IOREG(MMD_ID_CLK_CFG, 0, 0x60e)

/**
 * \brief
 * The DIVFI[6:0] setting to the PLL IPthe devisor of PLL is DIVFI+1
 *
 * \details
 * Field: ::LAN80XX_CLK_CFG_LTCPLL_DIVFI_REG . LTCPLL_DIVFI
 */
#define  LAN80XX_F_CLK_CFG_LTCPLL_DIVFI_REG_LTCPLL_DIVFI(x)  LAN80XX_ENCODE_BITFIELD(x,0,7)
#define  LAN80XX_M_CLK_CFG_LTCPLL_DIVFI_REG_LTCPLL_DIVFI     LAN80XX_ENCODE_BITMASK(0,7)
#define  LAN80XX_X_CLK_CFG_LTCPLL_DIVFI_REG_LTCPLL_DIVFI(x)  LAN80XX_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief LTCPLL Status Register
 *
 * \details
 * LTCPLL Status Register
 *
 * Register: \a CLK_CFG:LTCPLL:LTCPLL_STS_REG
 */
#define LAN80XX_CLK_CFG_LTCPLL_STS_REG          LAN80XX_IOREG(MMD_ID_CLK_CFG, 0, 0x60f)

/**
 * \brief
 * hardware clock controller indicates PLL is locked
 *
 * \details
 * Field: ::LAN80XX_CLK_CFG_LTCPLL_STS_REG . LTCPLL_STS
 */
#define  LAN80XX_F_CLK_CFG_LTCPLL_STS_REG_LTCPLL_STS(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_CLK_CFG_LTCPLL_STS_REG_LTCPLL_STS  LAN80XX_BIT(0)
#define  LAN80XX_X_CLK_CFG_LTCPLL_STS_REG_LTCPLL_STS(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a CLK_CFG:RCVRD_CLK_CFG
 *
 * Recovered Clock Configuration Registers
 */


/**
 * \brief Recovered Clock A Configuration
 *
 * \details
 * Register: \a CLK_CFG:RCVRD_CLK_CFG:RCVRD_CLKA_CFG
 */
#define LAN80XX_CLK_CFG_RCVRD_CLKA_CFG          LAN80XX_IOREG(MMD_ID_CLK_CFG, 0, 0x610)

/**
 * \brief
 * The user should clear this bit before making any clock source
 * configuration changes of this recovered clock
 *
 * \details
 * 1:  enable RCKOUT_A
 * 0:  disable RCKOUT_A
 *
 * Field: ::LAN80XX_CLK_CFG_RCVRD_CLKA_CFG . CLKA_ENABLE
 */
#define  LAN80XX_F_CLK_CFG_RCVRD_CLKA_CFG_CLKA_ENABLE(x)  LAN80XX_ENCODE_BITFIELD(x,9,1)
#define  LAN80XX_M_CLK_CFG_RCVRD_CLKA_CFG_CLKA_ENABLE  LAN80XX_BIT(9)
#define  LAN80XX_X_CLK_CFG_RCVRD_CLKA_CFG_CLKA_ENABLE(x)  LAN80XX_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Source selector for this recovered clock output
 *
 * \details
 * 0000: Line 0 recovered clock
 * 0001: Line 1 recovered clock
 * 0010: Line 2 recovered clock
 * 0011: Line 3 recovered clock
 * 0100: Host 0 recovered clock
 * 0101: Host 1 recovered clock
 * 0110: Host 2 recovered clock
 * 0111: Host 3 recovered clock
 * 1000: PTP LTC clock
 * 1001: System clock
 * 1010-1110: Reserved
 * 1111: None
 *
 * Field: ::LAN80XX_CLK_CFG_RCVRD_CLKA_CFG . CLKA_RCVRD_CLK_SEL
 */
#define  LAN80XX_F_CLK_CFG_RCVRD_CLKA_CFG_CLKA_RCVRD_CLK_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,5,4)
#define  LAN80XX_M_CLK_CFG_RCVRD_CLKA_CFG_CLKA_RCVRD_CLK_SEL     LAN80XX_ENCODE_BITMASK(5,4)
#define  LAN80XX_X_CLK_CFG_RCVRD_CLKA_CFG_CLKA_RCVRD_CLK_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,5,4)

/**
 * \brief
 * Divider setting for this recovered clock output.
 *
 * \details
 * 00 = Divide recovered clock by 1
 * 01 = Divide recovered clock by 2
 * 10 = Divide recovered clock by 4
 * 11 = Divide recovered clock by 8
 * Note: the recovered clock frequency for 1G/10G/25G port speed is
 * 125.00/257.8125/644.53125 MHz accordingly,
 * This output must not exceed 130 MHz,

 *
 * Field: ::LAN80XX_CLK_CFG_RCVRD_CLKA_CFG . CLKA_RCVRD_CLK_DIV
 */
#define  LAN80XX_F_CLK_CFG_RCVRD_CLKA_CFG_CLKA_RCVRD_CLK_DIV(x)  LAN80XX_ENCODE_BITFIELD(x,3,2)
#define  LAN80XX_M_CLK_CFG_RCVRD_CLKA_CFG_CLKA_RCVRD_CLK_DIV     LAN80XX_ENCODE_BITMASK(3,2)
#define  LAN80XX_X_CLK_CFG_RCVRD_CLKA_CFG_CLKA_RCVRD_CLK_DIV(x)  LAN80XX_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * Use SD25G LOS to squelch the recovered clock output. may be combined
 * with CLKA_PCS_LINK_STS_SQUELCH_EN.
 *
 * \details
 * 1: Use LOS for squelching
 * 0: Don't use LOS for squelching
 *
 * Field: ::LAN80XX_CLK_CFG_RCVRD_CLKA_CFG . CLKA_SD_LOS_SQUELCH_ENA
 */
#define  LAN80XX_F_CLK_CFG_RCVRD_CLKA_CFG_CLKA_SD_LOS_SQUELCH_ENA(x)  LAN80XX_ENCODE_BITFIELD(x,2,1)
#define  LAN80XX_M_CLK_CFG_RCVRD_CLKA_CFG_CLKA_SD_LOS_SQUELCH_ENA  LAN80XX_BIT(2)
#define  LAN80XX_X_CLK_CFG_RCVRD_CLKA_CFG_CLKA_SD_LOS_SQUELCH_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Use PCS Link Status to squelch the recovered clock output. May be
 * combined with CLKA_SD_LOS_SQUELCH_ENA.
 *
 * \details
 * 1: Use link status for squelching
 * 0: Don't use link status for squelching
 *
 * Field: ::LAN80XX_CLK_CFG_RCVRD_CLKA_CFG . CLKA_PCS_LINK_STS_SQUELCH_ENA
 */
#define  LAN80XX_F_CLK_CFG_RCVRD_CLKA_CFG_CLKA_PCS_LINK_STS_SQUELCH_ENA(x)  LAN80XX_ENCODE_BITFIELD(x,1,1)
#define  LAN80XX_M_CLK_CFG_RCVRD_CLKA_CFG_CLKA_PCS_LINK_STS_SQUELCH_ENA  LAN80XX_BIT(1)
#define  LAN80XX_X_CLK_CFG_RCVRD_CLKA_CFG_CLKA_PCS_LINK_STS_SQUELCH_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enables auto-squelching for this recovered clock output, where the clock
 * will stop toggling (keep its last value constantly) based on SerDes LOS,
 * PCS Link state and/or Link Training state.
 *
 * \details
 * 1: Auto-squelch enabled
 * 0: Auto-squelch disabled
 *
 * Field: ::LAN80XX_CLK_CFG_RCVRD_CLKA_CFG . CLKA_AUTO_SQUELCH_ENA
 */
#define  LAN80XX_F_CLK_CFG_RCVRD_CLKA_CFG_CLKA_AUTO_SQUELCH_ENA(x)  LAN80XX_ENCODE_BITFIELD(x,0,1)
#define  LAN80XX_M_CLK_CFG_RCVRD_CLKA_CFG_CLKA_AUTO_SQUELCH_ENA  LAN80XX_BIT(0)
#define  LAN80XX_X_CLK_CFG_RCVRD_CLKA_CFG_CLKA_AUTO_SQUELCH_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Recovered Clock B Configuration
 *
 * \details
 * Register: \a CLK_CFG:RCVRD_CLK_CFG:RCVRD_CLKB_CFG
 */
#define LAN80XX_CLK_CFG_RCVRD_CLKB_CFG          LAN80XX_IOREG(MMD_ID_CLK_CFG, 0, 0x611)

/**
 * \brief
 * The user should clear this bit before making any clock source
 * configuration changes of this recovered clock
 *
 * \details
 * 1:  enable RCKOUT_B
 * 0:  disable RCKOUT_B
 *
 * Field: ::LAN80XX_CLK_CFG_RCVRD_CLKB_CFG . CLKB_ENABLE
 */
#define  LAN80XX_F_CLK_CFG_RCVRD_CLKB_CFG_CLKB_ENABLE(x)  LAN80XX_ENCODE_BITFIELD(x,9,1)
#define  LAN80XX_M_CLK_CFG_RCVRD_CLKB_CFG_CLKB_ENABLE  LAN80XX_BIT(9)
#define  LAN80XX_X_CLK_CFG_RCVRD_CLKB_CFG_CLKB_ENABLE(x)  LAN80XX_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Source selector for this recovered clock output
 *
 * \details
 * 0000: Line 0 recovered clock
 * 0001: Line 1 recovered clock
 * 0010: Line 2 recovered clock
 * 0011: Line 3 recovered clock
 * 0100: Host 0 recovered clock
 * 0101: Host 1 recovered clock
 * 0110: Host 2 recovered clock
 * 0111: Host 3 recovered clock
 * 1000: PTP LTC clock
 * 1001: System clock
 * 1010-1110: Reserved
 * 1111: None
 *
 * Field: ::LAN80XX_CLK_CFG_RCVRD_CLKB_CFG . CLKB_RCVRD_CLK_SEL
 */
#define  LAN80XX_F_CLK_CFG_RCVRD_CLKB_CFG_CLKB_RCVRD_CLK_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,5,4)
#define  LAN80XX_M_CLK_CFG_RCVRD_CLKB_CFG_CLKB_RCVRD_CLK_SEL     LAN80XX_ENCODE_BITMASK(5,4)
#define  LAN80XX_X_CLK_CFG_RCVRD_CLKB_CFG_CLKB_RCVRD_CLK_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,5,4)

/**
 * \brief
 * Divider setting for this recovered clock output.
 *
 * \details
 * 00 = Divide recovered clock by 1
 * 01 = Divide recovered clock by 2
 * 10 = Divide recovered clock by 4
 * 11 = Divide recovered clock by 8
 * Note: the recovered clock frequency for 1G/10G/25G port speed is
 * 125.00/257.8125/644.53125 MHz accordingly,
 * This output must not exceed 130 MHz,

 *
 * Field: ::LAN80XX_CLK_CFG_RCVRD_CLKB_CFG . CLKB_RCVRD_CLK_DIV
 */
#define  LAN80XX_F_CLK_CFG_RCVRD_CLKB_CFG_CLKB_RCVRD_CLK_DIV(x)  LAN80XX_ENCODE_BITFIELD(x,3,2)
#define  LAN80XX_M_CLK_CFG_RCVRD_CLKB_CFG_CLKB_RCVRD_CLK_DIV     LAN80XX_ENCODE_BITMASK(3,2)
#define  LAN80XX_X_CLK_CFG_RCVRD_CLKB_CFG_CLKB_RCVRD_CLK_DIV(x)  LAN80XX_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * Use SD25G LOS to squelch the recovered clock output. may be combined
 * with CLKB_PCS_LINK_STS_SQUELCH_EN.
 *
 * \details
 * 1: Use LOS for squelching
 * 0: Don't use LOS for squelching
 *
 * Field: ::LAN80XX_CLK_CFG_RCVRD_CLKB_CFG . CLKB_SD_LOS_SQUELCH_ENA
 */
#define  LAN80XX_F_CLK_CFG_RCVRD_CLKB_CFG_CLKB_SD_LOS_SQUELCH_ENA(x)  LAN80XX_ENCODE_BITFIELD(x,2,1)
#define  LAN80XX_M_CLK_CFG_RCVRD_CLKB_CFG_CLKB_SD_LOS_SQUELCH_ENA  LAN80XX_BIT(2)
#define  LAN80XX_X_CLK_CFG_RCVRD_CLKB_CFG_CLKB_SD_LOS_SQUELCH_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Use PCS Link Status to squelch the recovered clock output. May be
 * combined with CLKB_SD_LOS_SQUELCH_ENA.
 *
 * \details
 * 1: Use link status for squelching
 * 0: Don't use link status for squelching
 *
 * Field: ::LAN80XX_CLK_CFG_RCVRD_CLKB_CFG . CLKB_PCS_LINK_STS_SQUELCH_ENA
 */
#define  LAN80XX_F_CLK_CFG_RCVRD_CLKB_CFG_CLKB_PCS_LINK_STS_SQUELCH_ENA(x)  LAN80XX_ENCODE_BITFIELD(x,1,1)
#define  LAN80XX_M_CLK_CFG_RCVRD_CLKB_CFG_CLKB_PCS_LINK_STS_SQUELCH_ENA  LAN80XX_BIT(1)
#define  LAN80XX_X_CLK_CFG_RCVRD_CLKB_CFG_CLKB_PCS_LINK_STS_SQUELCH_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enables auto-squelching for this recovered clock output, where the clock
 * will stop toggling (keep its last value constantly) based on SerDes LOS,
 * PCS Link state and/or Link Training state.
 *
 * \details
 * 1: Auto-squelch enabled
 * 0: Auto-squelch disabled
 *
 * Field: ::LAN80XX_CLK_CFG_RCVRD_CLKB_CFG . CLKB_AUTO_SQUELCH_ENA
 */
#define  LAN80XX_F_CLK_CFG_RCVRD_CLKB_CFG_CLKB_AUTO_SQUELCH_ENA(x)  LAN80XX_ENCODE_BITFIELD(x,0,1)
#define  LAN80XX_M_CLK_CFG_RCVRD_CLKB_CFG_CLKB_AUTO_SQUELCH_ENA  LAN80XX_BIT(0)
#define  LAN80XX_X_CLK_CFG_RCVRD_CLKB_CFG_CLKB_AUTO_SQUELCH_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a CLK_CFG:LTC_CLK_CFG
 *
 * LTC clock configuration registers
 */


/**
 * \brief LTC clock configuration registers
 *
 * \details
 * Register: \a CLK_CFG:LTC_CLK_CFG:LTC_CLK_CFG_REG
 */
#define LAN80XX_CLK_CFG_LTC_CLK_CFG_REG         LAN80XX_IOREG(MMD_ID_CLK_CFG, 0, 0x612)

/**
 * \brief
 * The selection of the reference clock.
 *
 * \details
 * 0000: Line 0 recovered clock
 * 0001: Line 1 recovered clock
 * 0010: Line 2 recovered clock
 * 0011: Line 3 recovered clock
 * 0100: Host 0 recovered clock
 * 0101: Host 1 recovered clock
 * 0110: Host 2 recovered clock
 * 0111: Host 3 recovered clock
 * 1000: LSC clock
 * 1001: SYSREFCLK
 * 1010-1111: Reserved

 *
 * Field: ::LAN80XX_CLK_CFG_LTC_CLK_CFG_REG . LTC_CLK_SEL
 */
#define  LAN80XX_F_CLK_CFG_LTC_CLK_CFG_REG_LTC_CLK_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,4,4)
#define  LAN80XX_M_CLK_CFG_LTC_CLK_CFG_REG_LTC_CLK_SEL     LAN80XX_ENCODE_BITMASK(4,4)
#define  LAN80XX_X_CLK_CFG_LTC_CLK_CFG_REG_LTC_CLK_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * The input reference clock pre-divider value
 *
 * \details
 * 000: Divide by 1
 * 001: Divide by 2
 * 010: Divide by 3
 * 011: Divide by 4
 * 100: Divide by 5
 * 101: Divide by 6
 * 110: Divide by 7
 * 111: Divide by 8

 *
 * Field: ::LAN80XX_CLK_CFG_LTC_CLK_CFG_REG . LTC_CLK_DIV
 */
#define  LAN80XX_F_CLK_CFG_LTC_CLK_CFG_REG_LTC_CLK_DIV(x)  LAN80XX_ENCODE_BITFIELD(x,0,3)
#define  LAN80XX_M_CLK_CFG_LTC_CLK_CFG_REG_LTC_CLK_DIV     LAN80XX_ENCODE_BITMASK(0,3)
#define  LAN80XX_X_CLK_CFG_LTC_CLK_CFG_REG_LTC_CLK_DIV(x)  LAN80XX_EXTRACT_BITFIELD(x,0,3)


#endif /* _LAN80XX_MALIBU25G_REGS_CLK_CFG_H_ */
