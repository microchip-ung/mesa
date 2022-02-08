// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_PCIE_CFG_H_
#define _VTSS_LAGUNA_REGS_PCIE_CFG_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a PCIE_CFG
 *
 * This target contains registers for configuring and controlling the PCIe
 * controller logic.
 *
 ***********************************************************************/

/**
 * Register Group: \a PCIE_CFG:PCIE
 *
 * PCIe Dual mode Controller Configuration
 */


/**
 * \brief PCIe DM Controller control
 *
 * \details
 * Register: \a PCIE_CFG:PCIE:PCIE_CTRL
 */
#define VTSS_PCIE_CFG_PCIE_CTRL              VTSS_IOREG(VTSS_TO_PCIE_CFG,0x0)

/**
 * \brief
 * Set this field to send out PME from the controller, this is only
 * possible if PME is enabled in the PCIe core in Endpoint mode of
 * operation. This field is cleared automatically after controller has
 * received the request.In the D3 state the controller will transmit beacon
 * and/or assert #WAKE (see PCIE_CFG::PCIE_CFG.WAKE_DIS for more
 * information).In other states the link will be transitioned to L0 (when
 * applicable) and PME event will then be transmitted upsteam.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_CTRL . POWERUP
 */
#define  VTSS_F_PCIE_CFG_PCIE_CTRL_POWERUP(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCIE_CFG_PCIE_CTRL_POWERUP    VTSS_BIT(2)
#define  VTSS_X_PCIE_CFG_PCIE_CTRL_POWERUP(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Set to disable wake-up on interrupt. By default the PCIe endpoint will
 * attempt to wake up from powerdown when a change in interrupt state is
 * detected.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_CTRL . WAKEUP_ON_INTR_DIS
 */
#define  VTSS_F_PCIE_CFG_PCIE_CTRL_WAKEUP_ON_INTR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCIE_CFG_PCIE_CTRL_WAKEUP_ON_INTR_DIS  VTSS_BIT(1)
#define  VTSS_X_PCIE_CFG_PCIE_CTRL_WAKEUP_ON_INTR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Triggers warm reset to PCIe controller.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_CTRL . WARM_RESET
 */
#define  VTSS_F_PCIE_CFG_PCIE_CTRL_WARM_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_CFG_PCIE_CTRL_WARM_RESET  VTSS_BIT(0)
#define  VTSS_X_PCIE_CFG_PCIE_CTRL_WARM_RESET(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief PCIe DM Controller configuration
 *
 * \details
 * Register: \a PCIE_CFG:PCIE:PCIE_CFG
 */
#define VTSS_PCIE_CFG_PCIE_CFG               VTSS_IOREG(VTSS_TO_PCIE_CFG,0x1)

/**
 * \brief
 * Set to defer incoming configuration requests with a Configuration
 * Request Retry Status.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_CFG . REQ_RETRY_ENA
 */
#define  VTSS_F_PCIE_CFG_PCIE_CFG_REQ_RETRY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PCIE_CFG_PCIE_CFG_REQ_RETRY_ENA  VTSS_BIT(19)
#define  VTSS_X_PCIE_CFG_PCIE_CFG_REQ_RETRY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Separate Refclk with Independent Spread Spectrum Clocking (SRIS).
 *
 * \details
 * 0: non-SRIS mode
 * 1: SRIS mode
 *
 * Field: ::VTSS_PCIE_CFG_PCIE_CFG . SRIS_MODE
 */
#define  VTSS_F_PCIE_CFG_PCIE_CFG_SRIS_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_PCIE_CFG_PCIE_CFG_SRIS_MODE   VTSS_BIT(18)
#define  VTSS_X_PCIE_CFG_PCIE_CFG_SRIS_MODE(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Set this field to enable initialization of the PCIe link.By default the
 * PCIe core will start up and try to achieve link when the SERDES is
 * started, by setting this field before starting the SERDES it is possible
 * to make changes to the PCIe configruration/registers prior to linking
 * with the root complex.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_CFG . LTSSM_ENA
 */
#define  VTSS_F_PCIE_CFG_PCIE_CFG_LTSSM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_PCIE_CFG_PCIE_CFG_LTSSM_ENA   VTSS_BIT(17)
#define  VTSS_X_PCIE_CFG_PCIE_CFG_LTSSM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * DBI Read-only Write Disable
 *
 * \details
 * 0: PCIE_DBI::MISC_CONTROL_1_OFF.DBI_RO_WR_EN register field is
 * read-write.
 * 1: PCIE_DBI::MISC_CONTROL_1_OFF.DBI_RO_WR_EN register field is forced to
 * 0 and is read-only.
 *
 * Field: ::VTSS_PCIE_CFG_PCIE_CFG . DBI_RO_WR_DIS
 */
#define  VTSS_F_PCIE_CFG_PCIE_CFG_DBI_RO_WR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PCIE_CFG_PCIE_CFG_DBI_RO_WR_DIS  VTSS_BIT(16)
#define  VTSS_X_PCIE_CFG_PCIE_CFG_DBI_RO_WR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Set this signal to one before the deassertion of power on reset to hold
 * the PHY in reset. This can be used to configure the PHY.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_CFG . HOLD_PHY_RST
 */
#define  VTSS_F_PCIE_CFG_PCIE_CFG_HOLD_PHY_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_PCIE_CFG_PCIE_CFG_HOLD_PHY_RST  VTSS_BIT(15)
#define  VTSS_X_PCIE_CFG_PCIE_CFG_HOLD_PHY_RST(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Set to add the PCIe core memories to the RAM integrity ring.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_CFG . MEM_RING_CORE_ENA
 */
#define  VTSS_F_PCIE_CFG_PCIE_CFG_MEM_RING_CORE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_PCIE_CFG_PCIE_CFG_MEM_RING_CORE_ENA  VTSS_BIT(14)
#define  VTSS_X_PCIE_CFG_PCIE_CFG_MEM_RING_CORE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * This field can be used by the masters driving the PCIE link to prevent
 * the controller from entering the L1 state if there is some data still
 * left for transmission. When the data is transmitted, master should clear
 * this field in order for normal PCIE power management to happen.
 *
 * \details
 * 0: Normal operation. When idle, controller assumes no traffic pending
 * and enters L1
 * 1: Prevents the controller from entering the L1 state or exits L1 state
 * if already in L1 state.
 *
 * Field: ::VTSS_PCIE_CFG_PCIE_CFG . MSTR_XFER_PENDING
 */
#define  VTSS_F_PCIE_CFG_PCIE_CFG_MSTR_XFER_PENDING(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PCIE_CFG_PCIE_CFG_MSTR_XFER_PENDING  VTSS_BIT(13)
#define  VTSS_X_PCIE_CFG_PCIE_CFG_MSTR_XFER_PENDING(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Controls generation of WAKE signal generation during wake-up from low
 * power modes.
 *
 * \details
 * 0:Wake signal generation enabled
 * 1:Wake signal generation disabled.
 *
 * Field: ::VTSS_PCIE_CFG_PCIE_CFG . WAKE_DIS
 */
#define  VTSS_F_PCIE_CFG_PCIE_CFG_WAKE_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PCIE_CFG_PCIE_CFG_WAKE_DIS    VTSS_BIT(12)
#define  VTSS_X_PCIE_CFG_PCIE_CFG_WAKE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Polarity of the PCIe WAKE output, WAKE is typically an active low output
 * - but if an amplifier is needed for driving a large WAKE net then
 * polarity may need to be changed.
 *
 * \details
 * 0: Active low
 * 1: Active high
 *
 * Field: ::VTSS_PCIE_CFG_PCIE_CFG . WAKE_POL
 */
#define  VTSS_F_PCIE_CFG_PCIE_CFG_WAKE_POL(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PCIE_CFG_PCIE_CFG_WAKE_POL    VTSS_BIT(11)
#define  VTSS_X_PCIE_CFG_PCIE_CFG_WAKE_POL(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Set to permanently drive PCIe WAKE output, by default the WAKE output is
 * only driven when active and thus allowing pull-resistor network.
 *
 * \details
 * 0: Only drive output when active.
 * 1: Always drive output.
 *
 * Field: ::VTSS_PCIE_CFG_PCIE_CFG . WAKE_OE
 */
#define  VTSS_F_PCIE_CFG_PCIE_CFG_WAKE_OE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PCIE_CFG_PCIE_CFG_WAKE_OE     VTSS_BIT(10)
#define  VTSS_X_PCIE_CFG_PCIE_CFG_WAKE_OE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Allows debug access as per section 3.5.4.5.2 in PCIe controller's
 * databook.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_CFG . DBI_ADDR_31_22
 */
#define  VTSS_F_PCIE_CFG_PCIE_CFG_DBI_ADDR_31_22(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_PCIE_CFG_PCIE_CFG_DBI_ADDR_31_22     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_PCIE_CFG_PCIE_CFG_DBI_ADDR_31_22(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/**
 * \brief PCIe DM Controller status
 *
 * \details
 * Register: \a PCIE_CFG:PCIE:PCIE_STAT
 */
#define VTSS_PCIE_CFG_PCIE_STAT              VTSS_IOREG(VTSS_TO_PCIE_CFG,0x2)

/**
 * \brief
 * The current LTSSM state of the PCIe core.
 *
 * \details
 * 0x00: DETECT_QUIET
 * 0x01: DETECT_ACT
 * 0x02: POLL_ACTIVE
 * 0x03: POLL_COMPLIANCE
 * 0x04: POLL_CONFIG
 * 0x05: PRE_DETECT_QUIET
 * 0x06: DETECT_WAIT
 * 0x07: CFG_LINKWD_START
 * 0x08: CFG_LINKWD_ACEPT
 * 0x09: CFG_LANENUM_WAIT
 * 0x0A: CFG_LANENUM_ACEPT
 * 0x0B: CFG_COMPLETE
 * 0x0C: CFG_IDLE
 * 0x0D: RCVRY_LOCK
 * 0x0E: RCVRY_SPEED
 * 0x0F: RCVRY_RCVRCFG
 * 0x10: RCVRY_IDLE
 * 0x20: RCVRY_EQ0
 * 0x21: RCVRY_EQ1
 * 0x22: RCVRY_EQ2
 * 0x23: RCVRY_EQ3
 * 0x11: L0
 * 0x12: L0S
 * 0x13: L123_SEND_EIDLE
 * 0x14: L1_IDLE
 * 0x15: L2_IDLE
 * 0x16: L2_WAKE
 * 0x17: DISABLED_ENTRY
 * 0x18: DISABLED_IDLE
 * 0x19: DISABLED
 * 0x1A: LPBK_ENTRY
 * 0x1B: LPBK_ACTIVE
 * 0x1C: LPBK_EXIT
 * 0x1D: LPBK_EXIT_TIMEOUT
 * 0x1E: HOT_RESET_ENTRY
 * 0x1F: HOT_RESET
 *
 * Field: ::VTSS_PCIE_CFG_PCIE_STAT . LTSSM_STATE
 */
#define  VTSS_F_PCIE_CFG_PCIE_STAT_LTSSM_STATE(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_PCIE_CFG_PCIE_STAT_LTSSM_STATE     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_PCIE_CFG_PCIE_STAT_LTSSM_STATE(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/**
 * \brief
 * Current Link State of the PCIe core.
 *
 * \details
 * 0: L0 (or not working, check LTSSM)
 * 1: L0s
 * 2: L1
 * 3: L2
 * 4: L3
 *
 * Field: ::VTSS_PCIE_CFG_PCIE_STAT . LINK_STATE
 */
#define  VTSS_F_PCIE_CFG_PCIE_STAT_LINK_STATE(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_PCIE_CFG_PCIE_STAT_LINK_STATE     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_PCIE_CFG_PCIE_STAT_LINK_STATE(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * The current power management state of the PCIe core.
 *
 * \details
 * 0: D0
 * 1: D1
 * 2: D2
 * 3: D3
 * 4: D0-Uninitialized

 *
 * Field: ::VTSS_PCIE_CFG_PCIE_STAT . PM_STATE
 */
#define  VTSS_F_PCIE_CFG_PCIE_STAT_PM_STATE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PCIE_CFG_PCIE_STAT_PM_STATE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PCIE_CFG_PCIE_STAT_PM_STATE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief PCIe endpoint debug status
 *
 * \details
 * Register: \a PCIE_CFG:PCIE:PCIE_DBG_STAT
 */
#define VTSS_PCIE_CFG_PCIE_DBG_STAT          VTSS_IOREG(VTSS_TO_PCIE_CFG,0x3)

/**
 * \brief
 * Set when the Power Management is exiting L2 state. This value is read
 * directly from other clock domain, keep reading until same value was read
 * twice in a row - then read was sucessful.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_DBG_STAT . PM_L2_EXIT
 */
#define  VTSS_F_PCIE_CFG_PCIE_DBG_STAT_PM_L2_EXIT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCIE_CFG_PCIE_DBG_STAT_PM_L2_EXIT  VTSS_BIT(2)
#define  VTSS_X_PCIE_CFG_PCIE_DBG_STAT_PM_L2_EXIT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Set when the PCIe Data Link Layer is up and ready to receive/transmit
 * packages. This value is read directly from other clock domain, keep
 * reading until same value was read twice in a row - then read was
 * sucessful.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_DBG_STAT . DATA_LINK_LAYER_UP
 */
#define  VTSS_F_PCIE_CFG_PCIE_DBG_STAT_DATA_LINK_LAYER_UP(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCIE_CFG_PCIE_DBG_STAT_DATA_LINK_LAYER_UP  VTSS_BIT(1)
#define  VTSS_X_PCIE_CFG_PCIE_DBG_STAT_DATA_LINK_LAYER_UP(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Set when the physical layer of the Controller is up.  This value is read
 * directly from other clock domain, keep reading until same value was read
 * twice in a row - then read was sucessful.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_DBG_STAT . PHY_LAYER_UP
 */
#define  VTSS_F_PCIE_CFG_PCIE_DBG_STAT_PHY_LAYER_UP(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_CFG_PCIE_DBG_STAT_PHY_LAYER_UP  VTSS_BIT(0)
#define  VTSS_X_PCIE_CFG_PCIE_DBG_STAT_PHY_LAYER_UP(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Additional inbound reply information
 *
 * \details
 * Register: \a PCIE_CFG:PCIE:PCIEMST_REPLY_INFO
 */
#define VTSS_PCIE_CFG_PCIEMST_REPLY_INFO     VTSS_IOREG(VTSS_TO_PCIE_CFG,0x4)

/**
 * \brief
 * This field allows additional PCIe-transaction settings in PCIe Master
 * Reply. The settings in this register is applied to all PCIe inbound
 * accesses.
 *
 * \details
 * [0] EP-field.
 * [3:1] This field indicates response to be sent out on PCIe link in case
 * of successful Write Request on PCIe Master, default to "00"
 * [6:4] This field indicates response to be sent out on PCIe link in case
 * of successful Read Request on PCIe Master, default to "000"
 * 000-SC(Successful Completion)
 * 001-UR(Unsupported Request)
 * 010-RRS(Request Retry Status)
 * 100-CA(Completer Abort)

 *
 * Field: ::VTSS_PCIE_CFG_PCIEMST_REPLY_INFO . MST_REPLY_INFO
 */
#define  VTSS_F_PCIE_CFG_PCIEMST_REPLY_INFO_MST_REPLY_INFO(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_PCIE_CFG_PCIEMST_REPLY_INFO_MST_REPLY_INFO     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_PCIE_CFG_PCIEMST_REPLY_INFO_MST_REPLY_INFO(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief Configuration to bypass iATU(Internal Address Translation Unit) of Controller
 *
 * \details
 * Register: \a PCIE_CFG:PCIE:PCIESLV_IATU_BYPASS
 */
#define VTSS_PCIE_CFG_PCIESLV_IATU_BYPASS    VTSS_IOREG(VTSS_TO_PCIE_CFG,0x5)

/**
 * \brief
 * When set, bypass all the issued AXI Write Requests onto PCIe AXI Slave
 * in undergoing address translation through iATU of Controller.
 *
 * \details
 * 0: Don't Bypass iATU
 * 1: Bypass iATU
 *
 * Field: ::VTSS_PCIE_CFG_PCIESLV_IATU_BYPASS . WR_REQ_BYPASS_ENA
 */
#define  VTSS_F_PCIE_CFG_PCIESLV_IATU_BYPASS_WR_REQ_BYPASS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCIE_CFG_PCIESLV_IATU_BYPASS_WR_REQ_BYPASS_ENA  VTSS_BIT(1)
#define  VTSS_X_PCIE_CFG_PCIESLV_IATU_BYPASS_WR_REQ_BYPASS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * When set, bypass all the issued AXI Read Requests onto PCIe AXI Slave in
 * undergoing address translation through iATU of Controller.
 *
 * \details
 * 0: Don't Bypass iATU
 * 1: Bypass iATU
 *
 * Field: ::VTSS_PCIE_CFG_PCIESLV_IATU_BYPASS . RD_REQ_BYPASS_ENA
 */
#define  VTSS_F_PCIE_CFG_PCIESLV_IATU_BYPASS_RD_REQ_BYPASS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_CFG_PCIESLV_IATU_BYPASS_RD_REQ_BYPASS_ENA  VTSS_BIT(0)
#define  VTSS_X_PCIE_CFG_PCIESLV_IATU_BYPASS_RD_REQ_BYPASS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief CPU access into PCIe address space
 *
 * \details
 * Register: \a PCIE_CFG:PCIE:PCIESLV_ATTR
 */
#define VTSS_PCIE_CFG_PCIESLV_ATTR           VTSS_IOREG(VTSS_TO_PCIE_CFG,0x6)

/**
 * \brief
 * Reserved, must be 0.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIESLV_ATTR . RESERVED2
 */
#define  VTSS_F_PCIE_CFG_PCIESLV_ATTR_RESERVED2(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PCIE_CFG_PCIESLV_ATTR_RESERVED2  VTSS_BIT(21)
#define  VTSS_X_PCIE_CFG_PCIESLV_ATTR_RESERVED2(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * This field allows configuration of outbound PCIe-transaction MSG field.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIESLV_ATTR . TLP_MSG_CODE
 */
#define  VTSS_F_PCIE_CFG_PCIESLV_ATTR_TLP_MSG_CODE(x)  VTSS_ENCODE_BITFIELD(x,13,8)
#define  VTSS_M_PCIE_CFG_PCIESLV_ATTR_TLP_MSG_CODE     VTSS_ENCODE_BITMASK(13,8)
#define  VTSS_X_PCIE_CFG_PCIESLV_ATTR_TLP_MSG_CODE(x)  VTSS_EXTRACT_BITFIELD(x,13,8)

/**
 * \brief
 * This field allows configuration of outbound PCIe-transaction TC field.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIESLV_ATTR . TLP_TC
 */
#define  VTSS_F_PCIE_CFG_PCIESLV_ATTR_TLP_TC(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_PCIE_CFG_PCIESLV_ATTR_TLP_TC     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_PCIE_CFG_PCIESLV_ATTR_TLP_TC(x)  VTSS_EXTRACT_BITFIELD(x,10,3)

/**
 * \brief
 * This field allows configuration of outbound PCIe-transaction ATTR field.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIESLV_ATTR . TLP_ATTR
 */
#define  VTSS_F_PCIE_CFG_PCIESLV_ATTR_TLP_ATTR(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_PCIE_CFG_PCIESLV_ATTR_TLP_ATTR     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_PCIE_CFG_PCIESLV_ATTR_TLP_ATTR(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * Reserved, must be 0.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIESLV_ATTR . RESERVED1
 */
#define  VTSS_F_PCIE_CFG_PCIESLV_ATTR_RESERVED1(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PCIE_CFG_PCIESLV_ATTR_RESERVED1  VTSS_BIT(7)
#define  VTSS_X_PCIE_CFG_PCIESLV_ATTR_RESERVED1(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * This field allows configuration of outbound PCIe-transaction EP field.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIESLV_ATTR . TLP_EP
 */
#define  VTSS_F_PCIE_CFG_PCIESLV_ATTR_TLP_EP(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCIE_CFG_PCIESLV_ATTR_TLP_EP  VTSS_BIT(6)
#define  VTSS_X_PCIE_CFG_PCIESLV_ATTR_TLP_EP(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Reserved, must be 0.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIESLV_ATTR . RESERVED0
 */
#define  VTSS_F_PCIE_CFG_PCIESLV_ATTR_RESERVED0(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PCIE_CFG_PCIESLV_ATTR_RESERVED0  VTSS_BIT(5)
#define  VTSS_X_PCIE_CFG_PCIESLV_ATTR_RESERVED0(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * This field allows configuration of outbound PCIe-transaction TYPE field.
 *
 * \details
 * Encoding as defined by PCIe standard.
 *
 * Field: ::VTSS_PCIE_CFG_PCIESLV_ATTR . TLP_TYPE
 */
#define  VTSS_F_PCIE_CFG_PCIESLV_ATTR_TLP_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_PCIE_CFG_PCIESLV_ATTR_TLP_TYPE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_PCIE_CFG_PCIESLV_ATTR_TLP_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief 3rd Header DW that is to be sent in a PCIE Msg/MsgD
 *
 * \details
 * Register: \a PCIE_CFG:PCIE:PCIESLV_MSG_3DW
 */
#define VTSS_PCIE_CFG_PCIESLV_MSG_3DW        VTSS_IOREG(VTSS_TO_PCIE_CFG,0x7)

/**
 * \brief
 * 32-bit value of 3rd DW that is to be sent in outbound PCIE Msg/MsgD Type
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIESLV_MSG_3DW . PCIESLV_MSG_3DW
 */
#define  VTSS_F_PCIE_CFG_PCIESLV_MSG_3DW_PCIESLV_MSG_3DW(x)  (x)
#define  VTSS_M_PCIE_CFG_PCIESLV_MSG_3DW_PCIESLV_MSG_3DW     0xffffffff
#define  VTSS_X_PCIE_CFG_PCIESLV_MSG_3DW_PCIESLV_MSG_3DW(x)  (x)


/**
 * \brief 4th Header DW that is to be sent in a PCIE Msg/MsgD
 *
 * \details
 * Register: \a PCIE_CFG:PCIE:PCIESLV_MSG_4DW
 */
#define VTSS_PCIE_CFG_PCIESLV_MSG_4DW        VTSS_IOREG(VTSS_TO_PCIE_CFG,0x8)

/**
 * \brief
 * 32-bit value of 4th DW that is to be sent in outbound PCIE Msg/MsgD Type
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIESLV_MSG_4DW . PCIESLV_MSG_4DW
 */
#define  VTSS_F_PCIE_CFG_PCIESLV_MSG_4DW_PCIESLV_MSG_4DW(x)  (x)
#define  VTSS_M_PCIE_CFG_PCIESLV_MSG_4DW_PCIESLV_MSG_4DW     0xffffffff
#define  VTSS_X_PCIE_CFG_PCIESLV_MSG_4DW_PCIESLV_MSG_4DW(x)  (x)

/**
 * Register Group: \a PCIE_CFG:MESSAGES
 *
 * Not documented
 */


/**
 * \brief CORR, FATAL, NONFATAL error, Unlock, PM MSG stickies
 *
 * \details
 * Register: \a PCIE_CFG:MESSAGES:PCIE_MSG_STICKY
 */
#define VTSS_PCIE_CFG_PCIE_MSG_STICKY        VTSS_IOREG(VTSS_TO_PCIE_CFG,0x9)

/**
 * \brief
 * Sticky indicates that Controller received an Unlock message.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_MSG_STICKY . UNLOCK_MSG_STICKY
 */
#define  VTSS_F_PCIE_CFG_PCIE_MSG_STICKY_UNLOCK_MSG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_PCIE_CFG_PCIE_MSG_STICKY_UNLOCK_MSG_STICKY  VTSS_BIT(8)
#define  VTSS_X_PCIE_CFG_PCIE_MSG_STICKY_UNLOCK_MSG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Sticky indicates that Controller received a PME_Turnoff MSG.Note: This
 * is only valid in End point mode of operation.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_MSG_STICKY . PM_TURNOFF_MSG_STICKY
 */
#define  VTSS_F_PCIE_CFG_PCIE_MSG_STICKY_PM_TURNOFF_MSG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PCIE_CFG_PCIE_MSG_STICKY_PM_TURNOFF_MSG_STICKY  VTSS_BIT(7)
#define  VTSS_X_PCIE_CFG_PCIE_MSG_STICKY_PM_TURNOFF_MSG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Sticky indicates that Controller received a vendor-defined message.
 * Message information is present in MSG_PAYLOAD.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_MSG_STICKY . VENDOR_MSG_STICKY
 */
#define  VTSS_F_PCIE_CFG_PCIE_MSG_STICKY_VENDOR_MSG_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PCIE_CFG_PCIE_MSG_STICKY_VENDOR_MSG_STICKY  VTSS_BIT(6)
#define  VTSS_X_PCIE_CFG_PCIE_MSG_STICKY_VENDOR_MSG_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * ATU Error indication per ATU region.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_MSG_STICKY . ATU_CBUF_ERR_STICKY
 */
#define  VTSS_F_PCIE_CFG_PCIE_MSG_STICKY_ATU_CBUF_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_PCIE_CFG_PCIE_MSG_STICKY_ATU_CBUF_ERR_STICKY     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_PCIE_CFG_PCIE_MSG_STICKY_ATU_CBUF_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief MSG Payload(LSB 32 bits) of the received Vendor Message by Controller.
 *
 * \details
 * Register: \a PCIE_CFG:MESSAGES:PCIE_MSG_PAYLOAD_LOW
 */
#define VTSS_PCIE_CFG_PCIE_MSG_PAYLOAD_LOW   VTSS_IOREG(VTSS_TO_PCIE_CFG,0xa)

/**
 * \brief
 * This registers captures the LSB 32 bits of Vendor MSG PAYLOAD received
 * and provided by Controller signal 'radm_msg_payload[31:0]'. Description
 * of the signal can be found in PCIE DM Controller Databook.Note: PCIe
 * Controller outputs payload information for other messages like error, pm
 * etc but since the payload is reserved for them, our interest would only
 * be in Vendor messages.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_MSG_PAYLOAD_LOW . VDM_MSG_PAYLOAD_LOW
 */
#define  VTSS_F_PCIE_CFG_PCIE_MSG_PAYLOAD_LOW_VDM_MSG_PAYLOAD_LOW(x)  (x)
#define  VTSS_M_PCIE_CFG_PCIE_MSG_PAYLOAD_LOW_VDM_MSG_PAYLOAD_LOW     0xffffffff
#define  VTSS_X_PCIE_CFG_PCIE_MSG_PAYLOAD_LOW_VDM_MSG_PAYLOAD_LOW(x)  (x)


/**
 * \brief MSG Payload(MSB 32 bits) of the received Vendor Message by Controller.
 *
 * \details
 * Register: \a PCIE_CFG:MESSAGES:PCIE_MSG_PAYLOAD_HIGH
 */
#define VTSS_PCIE_CFG_PCIE_MSG_PAYLOAD_HIGH  VTSS_IOREG(VTSS_TO_PCIE_CFG,0xb)

/**
 * \brief
 * This registers captures the MSB 32 bits of MSG PAYLOAD received and
 * provided by Controller signal 'radm_msg_payload[63:32]'. Description of
 * the signal can be found in PCIE DM Controller Databook.Note: PCIe
 * Controller outputs payload information for other messages like error, pm
 * etc but since the payload is reserved for them, our interest would only
 * be in Vendor messages
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_MSG_PAYLOAD_HIGH . VDM_MSG_PAYLOAD_HIGH
 */
#define  VTSS_F_PCIE_CFG_PCIE_MSG_PAYLOAD_HIGH_VDM_MSG_PAYLOAD_HIGH(x)  (x)
#define  VTSS_M_PCIE_CFG_PCIE_MSG_PAYLOAD_HIGH_VDM_MSG_PAYLOAD_HIGH     0xffffffff
#define  VTSS_X_PCIE_CFG_PCIE_MSG_PAYLOAD_HIGH_VDM_MSG_PAYLOAD_HIGH(x)  (x)


/**
 * \brief Contains Req. id of the received Message as provided by Controller.
 *
 * \details
 * Register: \a PCIE_CFG:MESSAGES:PCIE_MSG_HDR_INFO_0
 */
#define VTSS_PCIE_CFG_PCIE_MSG_HDR_INFO_0    VTSS_IOREG(VTSS_TO_PCIE_CFG,0xc)

/**
 * \brief
 * Contains the Requester ID(BDF) of the last received	UNLOCK Message
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_MSG_HDR_INFO_0 . UNLOCK_MSG_REQ_ID
 */
#define  VTSS_F_PCIE_CFG_PCIE_MSG_HDR_INFO_0_UNLOCK_MSG_REQ_ID(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_CFG_PCIE_MSG_HDR_INFO_0_UNLOCK_MSG_REQ_ID     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_CFG_PCIE_MSG_HDR_INFO_0_UNLOCK_MSG_REQ_ID(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * Contains the Requester ID(BDF) of the last received	Vendor Defined
 * Message(VDM).
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_MSG_HDR_INFO_0 . VDM_MSG_REQ_ID
 */
#define  VTSS_F_PCIE_CFG_PCIE_MSG_HDR_INFO_0_VDM_MSG_REQ_ID(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_CFG_PCIE_MSG_HDR_INFO_0_VDM_MSG_REQ_ID     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_CFG_PCIE_MSG_HDR_INFO_0_VDM_MSG_REQ_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Contains Req. id of the received Message as provided by Controller.
 *
 * \details
 * Register: \a PCIE_CFG:MESSAGES:PCIE_MSG_HDR_INFO_1
 */
#define VTSS_PCIE_CFG_PCIE_MSG_HDR_INFO_1    VTSS_IOREG(VTSS_TO_PCIE_CFG,0xd)

/**
 * \brief
 * Contains the Requester ID(BDF) of the last received	PME_TURNOFF Message
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_MSG_HDR_INFO_1 . TURNOFF_MSG_REQ_ID
 */
#define  VTSS_F_PCIE_CFG_PCIE_MSG_HDR_INFO_1_TURNOFF_MSG_REQ_ID(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_PCIE_CFG_PCIE_MSG_HDR_INFO_1_TURNOFF_MSG_REQ_ID     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_PCIE_CFG_PCIE_MSG_HDR_INFO_1_TURNOFF_MSG_REQ_ID(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * Contains the Requester ID(BDF) of the last received	ATU_CBUF_ERR
 * Message
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_MSG_HDR_INFO_1 . ATU_CBUF_ERR_REQ_ID
 */
#define  VTSS_F_PCIE_CFG_PCIE_MSG_HDR_INFO_1_ATU_CBUF_ERR_REQ_ID(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCIE_CFG_PCIE_MSG_HDR_INFO_1_ATU_CBUF_ERR_REQ_ID     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCIE_CFG_PCIE_MSG_HDR_INFO_1_ATU_CBUF_ERR_REQ_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a PCIE_CFG:INTR
 *
 * Not documented
 */


/**
 * \brief PCIe events
 *
 * \details
 * Register: \a PCIE_CFG:INTR:PCIE_INTR
 */
#define VTSS_PCIE_CFG_PCIE_INTR              VTSS_IOREG(VTSS_TO_PCIE_CFG,0xe)

/**
 * \brief
 * This event is set whenever a link down on PCIE is about to occur. This
 * is an early version of hot reset received by controller sampled on
 * falling edge.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_INTR . INTR_EARLY_LINK_DOWN
 */
#define  VTSS_F_PCIE_CFG_PCIE_INTR_INTR_EARLY_LINK_DOWN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCIE_CFG_PCIE_INTR_INTR_EARLY_LINK_DOWN  VTSS_BIT(4)
#define  VTSS_X_PCIE_CFG_PCIE_INTR_INTR_EARLY_LINK_DOWN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * This event is set whenever the PCIE_CFG::PCIE_STAT.LTSSM_STATE field is
 * changed.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_INTR . INTR_LTSSM_STATE
 */
#define  VTSS_F_PCIE_CFG_PCIE_INTR_INTR_LTSSM_STATE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCIE_CFG_PCIE_INTR_INTR_LTSSM_STATE  VTSS_BIT(3)
#define  VTSS_X_PCIE_CFG_PCIE_INTR_INTR_LTSSM_STATE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * This event is set whenever the PCIE_CFG::PCIE_STAT.LINK_STATE field is
 * changed.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_INTR . INTR_LINK_STATE
 */
#define  VTSS_F_PCIE_CFG_PCIE_INTR_INTR_LINK_STATE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCIE_CFG_PCIE_INTR_INTR_LINK_STATE  VTSS_BIT(2)
#define  VTSS_X_PCIE_CFG_PCIE_INTR_INTR_LINK_STATE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * This event is set whenever the PCIE_CFG::PCIE_STAT.PM_STATE field is
 * changed.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_INTR . INTR_PM_STATE
 */
#define  VTSS_F_PCIE_CFG_PCIE_INTR_INTR_PM_STATE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCIE_CFG_PCIE_INTR_INTR_PM_STATE  VTSS_BIT(1)
#define  VTSS_X_PCIE_CFG_PCIE_INTR_INTR_PM_STATE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Reset request because the link has gone down or the controller received
 * a hot-reset request. It indicates that the controller is requesting
 * external logic to reset the controller because the PHY link is down.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_INTR . INTR_LINK_REQ_RST_NOT
 */
#define  VTSS_F_PCIE_CFG_PCIE_INTR_INTR_LINK_REQ_RST_NOT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_CFG_PCIE_INTR_INTR_LINK_REQ_RST_NOT  VTSS_BIT(0)
#define  VTSS_X_PCIE_CFG_PCIE_INTR_INTR_LINK_REQ_RST_NOT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief PCIe interrupt enable
 *
 * \details
 * Register: \a PCIE_CFG:INTR:PCIE_INTR_ENA
 */
#define VTSS_PCIE_CFG_PCIE_INTR_ENA          VTSS_IOREG(VTSS_TO_PCIE_CFG,0xf)

/**
 * \brief
 * Set to enable propagation of EARLY_LINK_DOWN interrupt.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_INTR_ENA . INTR_EARLY_LINK_DOWN_ENA
 */
#define  VTSS_F_PCIE_CFG_PCIE_INTR_ENA_INTR_EARLY_LINK_DOWN_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCIE_CFG_PCIE_INTR_ENA_INTR_EARLY_LINK_DOWN_ENA  VTSS_BIT(4)
#define  VTSS_X_PCIE_CFG_PCIE_INTR_ENA_INTR_EARLY_LINK_DOWN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Set to enable propagation of the LTSSM_STATE interrupt.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_INTR_ENA . INTR_LTSSM_STATE_ENA
 */
#define  VTSS_F_PCIE_CFG_PCIE_INTR_ENA_INTR_LTSSM_STATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCIE_CFG_PCIE_INTR_ENA_INTR_LTSSM_STATE_ENA  VTSS_BIT(3)
#define  VTSS_X_PCIE_CFG_PCIE_INTR_ENA_INTR_LTSSM_STATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Set to enable propagation of the LINK_STATE interrupt.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_INTR_ENA . INTR_LINK_STATE_ENA
 */
#define  VTSS_F_PCIE_CFG_PCIE_INTR_ENA_INTR_LINK_STATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCIE_CFG_PCIE_INTR_ENA_INTR_LINK_STATE_ENA  VTSS_BIT(2)
#define  VTSS_X_PCIE_CFG_PCIE_INTR_ENA_INTR_LINK_STATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Set to enable propagation of the PM_STATE interrupt.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_INTR_ENA . INTR_PM_STATE_ENA
 */
#define  VTSS_F_PCIE_CFG_PCIE_INTR_ENA_INTR_PM_STATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCIE_CFG_PCIE_INTR_ENA_INTR_PM_STATE_ENA  VTSS_BIT(1)
#define  VTSS_X_PCIE_CFG_PCIE_INTR_ENA_INTR_PM_STATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enables INTR_LINK_REQ_RST_NOT interrupt.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_INTR_ENA . INTR_LINK_REQ_RST_NOT_ENA
 */
#define  VTSS_F_PCIE_CFG_PCIE_INTR_ENA_INTR_LINK_REQ_RST_NOT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_CFG_PCIE_INTR_ENA_INTR_LINK_REQ_RST_NOT_ENA  VTSS_BIT(0)
#define  VTSS_X_PCIE_CFG_PCIE_INTR_ENA_INTR_LINK_REQ_RST_NOT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Currently active PCIe interrupts
 *
 * \details
 * Register: \a PCIE_CFG:INTR:PCIE_INTR_IDENT
 */
#define VTSS_PCIE_CFG_PCIE_INTR_IDENT        VTSS_IOREG(VTSS_TO_PCIE_CFG,0x10)

/**
 * \brief
 * Set if the EARLY LINK DOWN interrupt is currently active.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_INTR_IDENT . INTR_EARLY_LINK_DOWN_IDENT
 */
#define  VTSS_F_PCIE_CFG_PCIE_INTR_IDENT_INTR_EARLY_LINK_DOWN_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PCIE_CFG_PCIE_INTR_IDENT_INTR_EARLY_LINK_DOWN_IDENT  VTSS_BIT(4)
#define  VTSS_X_PCIE_CFG_PCIE_INTR_IDENT_INTR_EARLY_LINK_DOWN_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Set if the LTSSM_STATE interrupt is currently active.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_INTR_IDENT . INTR_LTSSM_STATE_IDENT
 */
#define  VTSS_F_PCIE_CFG_PCIE_INTR_IDENT_INTR_LTSSM_STATE_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PCIE_CFG_PCIE_INTR_IDENT_INTR_LTSSM_STATE_IDENT  VTSS_BIT(3)
#define  VTSS_X_PCIE_CFG_PCIE_INTR_IDENT_INTR_LTSSM_STATE_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Set if the LINK_STATE interrupt is currently active.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_INTR_IDENT . INTR_LINK_STATE_IDENT
 */
#define  VTSS_F_PCIE_CFG_PCIE_INTR_IDENT_INTR_LINK_STATE_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PCIE_CFG_PCIE_INTR_IDENT_INTR_LINK_STATE_IDENT  VTSS_BIT(2)
#define  VTSS_X_PCIE_CFG_PCIE_INTR_IDENT_INTR_LINK_STATE_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Set if the PM_STATE interrupt is currently active.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_INTR_IDENT . INTR_PM_STATE_IDENT
 */
#define  VTSS_F_PCIE_CFG_PCIE_INTR_IDENT_INTR_PM_STATE_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PCIE_CFG_PCIE_INTR_IDENT_INTR_PM_STATE_IDENT  VTSS_BIT(1)
#define  VTSS_X_PCIE_CFG_PCIE_INTR_IDENT_INTR_PM_STATE_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Set if the LINK_REQ_RST_NOT interrupt is currently active.
 *
 * \details
 * Field: ::VTSS_PCIE_CFG_PCIE_INTR_IDENT . INTR_LINK_REQ_RST_NOT_IDENT
 */
#define  VTSS_F_PCIE_CFG_PCIE_INTR_IDENT_INTR_LINK_REQ_RST_NOT_IDENT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PCIE_CFG_PCIE_INTR_IDENT_INTR_LINK_REQ_RST_NOT_IDENT  VTSS_BIT(0)
#define  VTSS_X_PCIE_CFG_PCIE_INTR_IDENT_INTR_LINK_REQ_RST_NOT_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_LAGUNA_REGS_PCIE_CFG_H_ */
