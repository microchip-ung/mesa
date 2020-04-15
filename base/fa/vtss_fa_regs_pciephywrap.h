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

#ifndef _VTSS_FA_REGS_PCIEPHYWRAP_H_
#define _VTSS_FA_REGS_PCIEPHYWRAP_H_

#include "vtss_fa_regs_common.h"

/***********************************************************************
 *
 * Target: \a PCIEPHYWRAP
 *
 * Register for Wrapper of PCIE PHY (CMU, Lane and PCS)
 *
 ***********************************************************************/

/**
 * Register Group: \a PCIEPHYWRAP:PCIE_PHY_CFG
 *
 * Not documented
 */


/** 
 * \brief PCIE PHY Configuration 
 *
 * \details
 * Register: \a PCIEPHYWRAP:PCIE_PHY_CFG:PCIE_PHY_CFG
 */
#define VTSS_PCIEPHYWRAP_PCIE_PHY_CFG        VTSS_IOREG(VTSS_TO_PCIE_PHY_WRAP,0x0)

/** 
 * \brief
 * Software Reset for PCIE PHY 
 *
 * \details 
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::VTSS_PCIEPHYWRAP_PCIE_PHY_CFG . PIPE_RST
 */
#define  VTSS_F_PCIEPHYWRAP_PCIE_PHY_CFG_PIPE_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIEPHYWRAP_PCIE_PHY_CFG_PIPE_RST  VTSS_BIT(0)
#define  VTSS_X_PCIEPHYWRAP_PCIE_PHY_CFG_PIPE_RST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Software Reset for PCIE PHY SD configuration interface.
 *
 * \details 
 * 1: Reset active
 * 0: Reset incactive
 *
 * Field: ::VTSS_PCIEPHYWRAP_PCIE_PHY_CFG . EXT_CFG_RST
 */
#define  VTSS_F_PCIEPHYWRAP_PCIE_PHY_CFG_EXT_CFG_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCIEPHYWRAP_PCIE_PHY_CFG_EXT_CFG_RST  VTSS_BIT(1)
#define  VTSS_X_PCIEPHYWRAP_PCIE_PHY_CFG_EXT_CFG_RST(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Software Reset for PCIE PHY PCS APB Configuration Interface.
 *
 * \details 
 * 1: Reset active
 * 0: Reset incactive
 *
 * Field: ::VTSS_PCIEPHYWRAP_PCIE_PHY_CFG . APB_IF_RST
 */
#define  VTSS_F_PCIEPHYWRAP_PCIE_PHY_CFG_APB_IF_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCIEPHYWRAP_PCIE_PHY_CFG_APB_IF_RST  VTSS_BIT(2)
#define  VTSS_X_PCIEPHYWRAP_PCIE_PHY_CFG_APB_IF_RST(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * When set, this restricts the propagation of 'phy_rst_n' from PCIE
 * controller clk rst module to PCIE PHY. Only, software reset
 * PCIE_PHY_CFG.PIPE_RST would reset the PHY in such cases. Note: This is
 * just introduced as a fail safe mechanism if at all 'phy_rst_n' creates
 * any issues. Not to be used during normal operation.
 *
 * \details 
 * Field: ::VTSS_PCIEPHYWRAP_PCIE_PHY_CFG . PCIE_CNTLR_PHY_RST_DIS
 */
#define  VTSS_F_PCIEPHYWRAP_PCIE_PHY_CFG_PCIE_CNTLR_PHY_RST_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCIEPHYWRAP_PCIE_PHY_CFG_PCIE_CNTLR_PHY_RST_DIS  VTSS_BIT(3)
#define  VTSS_X_PCIEPHYWRAP_PCIE_PHY_CFG_PCIE_CNTLR_PHY_RST_DIS(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * When set, this restrics propagation of 'apb_rst_n' from AMBA to not
 * propagate to PCIE PHY. Only, software reset, PCIE_PHY_CFG.APB_IF_RST
 * would have an effect in such case.Note:This is just introduced as a fail
 * safe mechanism and not to be used in normal cases.
 *
 * \details 
 * Field: ::VTSS_PCIEPHYWRAP_PCIE_PHY_CFG . AMBA_APB_RST_DIS
 */
#define  VTSS_F_PCIEPHYWRAP_PCIE_PHY_CFG_AMBA_APB_RST_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCIEPHYWRAP_PCIE_PHY_CFG_AMBA_APB_RST_DIS  VTSS_BIT(4)
#define  VTSS_X_PCIEPHYWRAP_PCIE_PHY_CFG_AMBA_APB_RST_DIS(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * Register Group: \a PCIEPHYWRAP:PCIE_EXTCFG_CFG
 *
 * Configuration of PCIE PHY local parallel configuration interface (EXT_CFG)
 */


/** 
 * \brief Configuration of PCIE PHY local parallel configuration interface (EXT_CFG)
 *
 * \details
 * Register: \a PCIEPHYWRAP:PCIE_EXTCFG_CFG:PCIE_EXTCFG_CFG
 */
#define VTSS_PCIEPHYWRAP_PCIE_EXTCFG_CFG     VTSS_IOREG(VTSS_TO_PCIE_PHY_WRAP,0x1)

/** 
 * \brief
 * Clock divider for EXTCFG Master. Divide the system clock by N + 2 to be
 * used as EXTCFG master clock for SerDes configuration.
 *
 * \details 
 * N: core clock (system clock) is divided by N+2.
 *
 * Field: ::VTSS_PCIEPHYWRAP_PCIE_EXTCFG_CFG . CLK_DIV
 */
#define  VTSS_F_PCIEPHYWRAP_PCIE_EXTCFG_CFG_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PCIEPHYWRAP_PCIE_EXTCFG_CFG_CLK_DIV     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PCIEPHYWRAP_PCIE_EXTCFG_CFG_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * EXTCFG Interface Timing configuration.Additional N wait states before
 * write enable is asserted after driving address and write data.
 *
 * \details 
 * Total Wait States are N+2 clock cycles of EXT_CFG clock signal. 
 *
 * Field: ::VTSS_PCIEPHYWRAP_PCIE_EXTCFG_CFG . WS_SETUP_WR
 */
#define  VTSS_F_PCIEPHYWRAP_PCIE_EXTCFG_CFG_WS_SETUP_WR(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_PCIEPHYWRAP_PCIE_EXTCFG_CFG_WS_SETUP_WR     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_PCIEPHYWRAP_PCIE_EXTCFG_CFG_WS_SETUP_WR(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * EXTCFG Interface Timing configuration.Additional N wait states before
 * write enable is deasserted again.
 *
 * \details 
 * Total Wait States (i.e. pulse width) are N+2 clock cycles of EXT_CFG
 * clock signal. 
 *
 * Field: ::VTSS_PCIEPHYWRAP_PCIE_EXTCFG_CFG . WS_EXEC_WR
 */
#define  VTSS_F_PCIEPHYWRAP_PCIE_EXTCFG_CFG_WS_EXEC_WR(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_PCIEPHYWRAP_PCIE_EXTCFG_CFG_WS_EXEC_WR     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_PCIEPHYWRAP_PCIE_EXTCFG_CFG_WS_EXEC_WR(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * EXTCFG Interface Timing configuration.Additional N wait states before
 * start of next write access.
 *
 * \details 
 * Total Wait States (i.e. pulse width) are N+2 clock cycles of EXT_CFG
 * clock signal. 
 *
 * Field: ::VTSS_PCIEPHYWRAP_PCIE_EXTCFG_CFG . WS_HOLD_WR
 */
#define  VTSS_F_PCIEPHYWRAP_PCIE_EXTCFG_CFG_WS_HOLD_WR(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_PCIEPHYWRAP_PCIE_EXTCFG_CFG_WS_HOLD_WR     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_PCIEPHYWRAP_PCIE_EXTCFG_CFG_WS_HOLD_WR(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * EXTCFG Interface Timing configuration.Additional N wait states before
 * read data is sampled.
 *
 * \details 
 * Total Wait States (i.e. pulse width) are N+2 clock cycles of EXT_CFG
 * clock signal. 
 *
 * Field: ::VTSS_PCIEPHYWRAP_PCIE_EXTCFG_CFG . WS_EXEC_RD
 */
#define  VTSS_F_PCIEPHYWRAP_PCIE_EXTCFG_CFG_WS_EXEC_RD(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_PCIEPHYWRAP_PCIE_EXTCFG_CFG_WS_EXEC_RD     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_PCIEPHYWRAP_PCIE_EXTCFG_CFG_WS_EXEC_RD(x)  VTSS_EXTRACT_BITFIELD(x,16,2)


#endif /* _VTSS_FA_REGS_PCIEPHYWRAP_H_ */
