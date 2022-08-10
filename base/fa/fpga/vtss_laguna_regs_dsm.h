// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_DSM_H_
#define _VTSS_LAGUNA_REGS_DSM_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a DSM
 *
 * Disassembler
 *
 ***********************************************************************/

/**
 * Register Group: \a DSM:RAM_CTRL
 *
 * Access core memory
 */


/**
 * \brief Core reset control
 *
 * \details
 * Controls reset and initialization of the switching core. Proper startup
 * sequence is:
 * - Enable memories
 * - Initialize memories
 * - Enable core
 *
 * Register: \a DSM:RAM_CTRL:RAM_INIT
 */
#define VTSS_DSM_RAM_INIT                    VTSS_IOREG(VTSS_TO_DSM,0x0)

/**
 * \brief
 * Testing options for memories
 *
 * \details
 * xx1: Make parity errors on all memories
 * x1x: Make parity errors on local ring memories
 * 1xx: Make parity errors only at writes from software
 *
 * Field: ::VTSS_DSM_RAM_INIT . RAM_TEST_OPT
 */
#define  VTSS_F_DSM_RAM_INIT_RAM_TEST_OPT(x)  VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_DSM_RAM_INIT_RAM_TEST_OPT     VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_DSM_RAM_INIT_RAM_TEST_OPT(x)  VTSS_EXTRACT_BITFIELD(x,2,3)

/**
 * \brief
 * Initialize core memories. Field is automatically cleared when operation
 * is complete (approx. 40 us).
 *
 * \details
 * Field: ::VTSS_DSM_RAM_INIT . RAM_INIT
 */
#define  VTSS_F_DSM_RAM_INIT_RAM_INIT(x)      VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DSM_RAM_INIT_RAM_INIT         VTSS_BIT(1)
#define  VTSS_X_DSM_RAM_INIT_RAM_INIT(x)      VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * When this field is set, all memories HA_RESTART behavior will be
 * inverted. It is a backdoor for potentiel access issues.
 *
 * \details
 * Field: ::VTSS_DSM_RAM_INIT . RAM_CFG_HOOK
 */
#define  VTSS_F_DSM_RAM_INIT_RAM_CFG_HOOK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DSM_RAM_INIT_RAM_CFG_HOOK     VTSS_BIT(0)
#define  VTSS_X_DSM_RAM_INIT_RAM_CFG_HOOK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a DSM:COREMEM
 *
 * Access core memory
 */


/**
 * \brief Address selection
 *
 * \details
 * Register: \a DSM:COREMEM:CM_ADDR
 */
#define VTSS_DSM_CM_ADDR                     VTSS_IOREG(VTSS_TO_DSM,0x1)

/**
 * \brief
 * Address selection for the ram debug address space.
 *
 * \details
 * Field: ::VTSS_DSM_CM_ADDR . CM_ADDR
 */
#define  VTSS_F_DSM_CM_ADDR_CM_ADDR(x)        (x)
#define  VTSS_M_DSM_CM_ADDR_CM_ADDR           0xffffffff
#define  VTSS_X_DSM_CM_ADDR_CM_ADDR(x)        (x)


/**
 * \brief Data register for core memory access.
 *
 * \details
 * Register: \a DSM:COREMEM:CM_DATA_WR
 */
#define VTSS_DSM_CM_DATA_WR                  VTSS_IOREG(VTSS_TO_DSM,0x2)

/**
 * \brief
 * Data register for core memory access. Wider memories are big endian
 * mapped into the 32 bit inspection space. This register provides data to
 * be written when CM_OP is set.When CM_OP is set to 11 this register
 * encodes ram checking mode:-single /double parity errors induced on
 * writes-all chip memories or only the memories connected to this init
 * controller-errors at any write or only by software access
 *
 * \details
 * 000: No testing
 * 001: Single, local, any write
 * 010: Single, all, any write
 * 011: Single, local, s/w write
 * 100: Single, all, s/w write
 * 101: Double, local. s/w write
 * 110: Double, all, s/w write
 * 111: Solve climate crisis
 *
 * Field: ::VTSS_DSM_CM_DATA_WR . CM_DATA_WR
 */
#define  VTSS_F_DSM_CM_DATA_WR_CM_DATA_WR(x)  (x)
#define  VTSS_M_DSM_CM_DATA_WR_CM_DATA_WR     0xffffffff
#define  VTSS_X_DSM_CM_DATA_WR_CM_DATA_WR(x)  (x)


/**
 * \brief Core memory data register for read result
 *
 * \details
 * Register: \a DSM:COREMEM:CM_DATA_RD
 */
#define VTSS_DSM_CM_DATA_RD                  VTSS_IOREG(VTSS_TO_DSM,0x3)

/**
 * \brief
 * Read result
 *
 * \details
 * Field: ::VTSS_DSM_CM_DATA_RD . CM_DATA_RD
 */
#define  VTSS_F_DSM_CM_DATA_RD_CM_DATA_RD(x)  (x)
#define  VTSS_M_DSM_CM_DATA_RD_CM_DATA_RD     0xffffffff
#define  VTSS_X_DSM_CM_DATA_RD_CM_DATA_RD(x)  (x)


/**
 * \brief Operation to perform in core memory
 *
 * \details
 * Register: \a DSM:COREMEM:CM_OP
 */
#define VTSS_DSM_CM_OP                       VTSS_IOREG(VTSS_TO_DSM,0x4)

/**
 * \brief
 * Ask the memory debug system to read or write a specific location. If no
 * response is received from a memory, due to timeout, or selected address
 * out of range, the state machine can be reset by issuing the 11
 * command.Field will return to 00 upon completion.When the 11 command is
 * issued, cm_data_wr(2..0) enables ram test modes.000: No testing001:
 * Single error induced on local memories010: Single error induced on all
 * memories011: Single error induced on local memories accessed from
 * software only100: Single error induced on all memories accessed from
 * software only101: Double error induced on local memories from software
 * only110: Double error induced on all memories from software only111:
 * Solve climate crisis
 *
 * \details
 * 00: NOP
 * 01: Read from selected address into CM_DATA_RD
 * 10: Write CM_DATA_WR into selected address
 * 11: Reset debug access and configure test mode
 *
 * Field: ::VTSS_DSM_CM_OP . CM_OP
 */
#define  VTSS_F_DSM_CM_OP_CM_OP(x)            VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DSM_CM_OP_CM_OP               VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DSM_CM_OP_CM_OP(x)            VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a DSM:CFG
 *
 * Configuration registers
 */


/**
 * \brief Configuration per device buffer.
 *
 * \details
 * Miscellaneous configurations per device buffer.
 *
 * Register: \a DSM:CFG:BUF_CFG
 *
 * @param ri Replicator: x_DSM_EPORTS (??), 0-31
 */
#define VTSS_DSM_BUF_CFG(ri)                 VTSS_IOREG(VTSS_TO_DSM,0x5 + (ri))

/**
 * \brief
 * Status of TX_FORCE_STOP.
 *
 * \details
 * Field: ::VTSS_DSM_BUF_CFG . TX_FORCE_STOPPED
 */
#define  VTSS_F_DSM_BUF_CFG_TX_FORCE_STOPPED(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_DSM_BUF_CFG_TX_FORCE_STOPPED  VTSS_BIT(15)
#define  VTSS_X_DSM_BUF_CFG_TX_FORCE_STOPPED(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Stop tx on frame boundary (both express and preemptible traffic).
 *
 * \details
 * 1: Stop tx
 * 0: Release tx
 *
 * Field: ::VTSS_DSM_BUF_CFG . TX_FORCE_STOP
 */
#define  VTSS_F_DSM_BUF_CFG_TX_FORCE_STOP(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_DSM_BUF_CFG_TX_FORCE_STOP     VTSS_BIT(14)
#define  VTSS_X_DSM_BUF_CFG_TX_FORCE_STOP(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Disables updates of the DSM related counter for the common statistics
 * counter system that is used for DEV1G/DEV2G5 devices
 * (ASM:DEV_STATISTICS:TX_PAUSE_CNT).Set this when the port utilizes a
 * DEV10G device as it handles the statistics locally in the device
 * (Statistics counters in DEV10G:DEV_STATISTICS_*:*).
 *
 * \details
 * Field: ::VTSS_DSM_BUF_CFG . CSC_STAT_DIS
 */
#define  VTSS_F_DSM_BUF_CFG_CSC_STAT_DIS(x)   VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DSM_BUF_CFG_CSC_STAT_DIS      VTSS_BIT(13)
#define  VTSS_X_DSM_BUF_CFG_CSC_STAT_DIS(x)   VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Enable aging of frames stuck in the DSM buffer system for long
 * periods.Aging is done by comparing the age era stamped into the frame
 * with the current age era. This check is only performed at SOF. If the
 * current age era is more than one higher than the era stamped into the
 * frame, then the frame is discarded.Frame aging related
 * parameters:QSYS:SYSTEM:FRM_AGING.MAX_AGEHSCH:SYSTEM:PORT_MODE.AGE_DISDSM
 * :CFG:BUF_CFG.AGING_ENA
 *
 * \details
 * '0': Aging disabled.
 * '1': Aging enabled.
 *
 * Field: ::VTSS_DSM_BUF_CFG . AGING_ENA
 */
#define  VTSS_F_DSM_BUF_CFG_AGING_ENA(x)      VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DSM_BUF_CFG_AGING_ENA         VTSS_BIT(12)
#define  VTSS_X_DSM_BUF_CFG_AGING_ENA(x)      VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Disable dropping of frame when underflow occurs.
 *
 * \details
 * Field: ::VTSS_DSM_BUF_CFG . UNDERFLOW_WATCHDOG_DIS
 */
#define  VTSS_F_DSM_BUF_CFG_UNDERFLOW_WATCHDOG_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_DSM_BUF_CFG_UNDERFLOW_WATCHDOG_DIS  VTSS_BIT(11)
#define  VTSS_X_DSM_BUF_CFG_UNDERFLOW_WATCHDOG_DIS(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Number of taxi cycles that the cell buffer is allowed to be empty before
 * aborting frame due to underflow.
 *
 * \details
 * Field: ::VTSS_DSM_BUF_CFG . UNDERFLOW_WATCHDOG_TIMEOUT
 */
#define  VTSS_F_DSM_BUF_CFG_UNDERFLOW_WATCHDOG_TIMEOUT(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_DSM_BUF_CFG_UNDERFLOW_WATCHDOG_TIMEOUT     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_DSM_BUF_CFG_UNDERFLOW_WATCHDOG_TIMEOUT(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/**
 * \brief txAdditionalFrameOverhead configuration
 *
 * \details
 * Configuration of the txAdditionalFrameOverhead in RateLimit
 *
 * Register: \a DSM:CFG:RATE_CTRL
 *
 * @param ri Replicator: x_DSM_EPORTS (??), 0-31
 */
#define VTSS_DSM_RATE_CTRL(ri)               VTSS_IOREG(VTSS_TO_DSM,0x48 + (ri))

/**
 * \brief
 * If Rate Limit mode Frame Rate Overhead is enabled this bitgroup is used
 * for configuration of txAdditionalFrameOverhead.
 *
 * \details
 * Field: ::VTSS_DSM_RATE_CTRL . FRM_GAP_COMP
 */
#define  VTSS_F_DSM_RATE_CTRL_FRM_GAP_COMP(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DSM_RATE_CTRL_FRM_GAP_COMP     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DSM_RATE_CTRL_FRM_GAP_COMP(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief Configuration register for IPG shrink mode
 *
 * \details
 * Configuration register for IPG shrink mode
 *
 * Register: \a DSM:CFG:IPG_SHRINK_CFG
 *
 * @param ri Replicator: x_DSM_EPORTS (??), 0-31
 */
#define VTSS_DSM_IPG_SHRINK_CFG(ri)          VTSS_IOREG(VTSS_TO_DSM,0x8b + (ri))

/**
 * \brief
 * Enable for preamble shrink in IPG shrink mode of DEV10G, DEV24G.Preamble
 * shrink is only allowed when IPG shrink mode is enabled.
 *
 * \details
 * Field: ::VTSS_DSM_IPG_SHRINK_CFG . IPG_PREAM_SHRINK_ENA
 */
#define  VTSS_F_DSM_IPG_SHRINK_CFG_IPG_PREAM_SHRINK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DSM_IPG_SHRINK_CFG_IPG_PREAM_SHRINK_ENA  VTSS_BIT(1)
#define  VTSS_X_DSM_IPG_SHRINK_CFG_IPG_PREAM_SHRINK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable for IPG shrink mode of DEV10G, DEV24G.In shrink mode frame gap
 * compensation is depending on frame size.
 *
 * \details
 * Field: ::VTSS_DSM_IPG_SHRINK_CFG . IPG_SHRINK_ENA
 */
#define  VTSS_F_DSM_IPG_SHRINK_CFG_IPG_SHRINK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DSM_IPG_SHRINK_CFG_IPG_SHRINK_ENA  VTSS_BIT(0)
#define  VTSS_X_DSM_IPG_SHRINK_CFG_IPG_SHRINK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Clear a single buffer in the DSM.
 *
 * \details
 * This register controls clearing of buffers in the DSM.
 *
 * Register: \a DSM:CFG:CLR_BUF
 *
 * @param ri Replicator: x_DSM_CELL_BUFS_DIV32_CEIL (??), 0-2
 */
#define VTSS_DSM_CLR_BUF(ri)                 VTSS_IOREG(VTSS_TO_DSM,0xce + (ri))

/**
 * \brief
 * A write to this register clears the indicated buffer. No other buffers
 * will be influenced by clearing this buffer.Encoding:1: Clears buffer for
 * port 02: Clears buffer for port 12^N: Clears buffer for port NIf N > 31
 * Use respective next register.
 *
 * \details
 * '0': No action
 * '1': Buffer is cleared (Bit is automatically cleared)
 *
 * Field: ::VTSS_DSM_CLR_BUF . CLR_BUF
 */
#define  VTSS_F_DSM_CLR_BUF_CLR_BUF(x)        (x)
#define  VTSS_M_DSM_CLR_BUF_CLR_BUF           0xffffffff
#define  VTSS_X_DSM_CLR_BUF_CLR_BUF(x)        (x)


/**
 * \brief SCH stop fill level
 *
 * \details
 * SCH stop fill level
 *
 * Register: \a DSM:CFG:SCH_STOP_WM_CFG
 *
 * @param ri Replicator: x_DSM_EPORTS (??), 0-31
 */
#define VTSS_DSM_SCH_STOP_WM_CFG(ri)         VTSS_IOREG(VTSS_TO_DSM,0xd3 + (ri))

/**
 * \brief
 * DSM buffer fill level at which SCH is stopped to send to this device.
 *
 * \details
 * The SCH is stopped when the fill level is above the configured value.
 * When set to 0 the hardware will use a default watermark set to the mid
 * of the buffer.
 *
 * Field: ::VTSS_DSM_SCH_STOP_WM_CFG . SCH_STOP_WM
 */
#define  VTSS_F_DSM_SCH_STOP_WM_CFG_SCH_STOP_WM(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_DSM_SCH_STOP_WM_CFG_SCH_STOP_WM     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_DSM_SCH_STOP_WM_CFG_SCH_STOP_WM(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/**
 * \brief Transmit start fill level
 *
 * \details
 * Transmit start fill level
 *
 * Register: \a DSM:CFG:TX_START_WM_CFG
 *
 * @param ri Replicator: x_DSM_EPORTS (??), 0-31
 */
#define VTSS_DSM_TX_START_WM_CFG(ri)         VTSS_IOREG(VTSS_TO_DSM,0x116 + (ri))

/**
 * \brief
 * The number of 4-bytes words in DSM buffer required before the DSM will
 * start to transmit on the taxi bus. The fill level must above a certain
 * threshold to avoid underflow in the devices. Single cell frames will be
 * transferred immediately. If set to 0 a good default value is used.

 *
 * \details
 * The DSM will not begin transmission until the fill level is above this
 * watermark or one complete frame is present in the buffer.
 *
 * Field: ::VTSS_DSM_TX_START_WM_CFG . TX_START_WM
 */
#define  VTSS_F_DSM_TX_START_WM_CFG_TX_START_WM(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_DSM_TX_START_WM_CFG_TX_START_WM     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_DSM_TX_START_WM_CFG_TX_START_WM(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/**
 * \brief Token count tx stop watermark
 *
 * \details
 * Token count tx stop watermark
 *
 * Register: \a DSM:CFG:DEV_TX_STOP_WM_CFG
 *
 * @param ri Replicator: x_DSM_EPORTS (??), 0-31
 */
#define VTSS_DSM_DEV_TX_STOP_WM_CFG(ri)      VTSS_IOREG(VTSS_TO_DSM,0x159 + (ri))

/**
 * \brief
 * Set this to 0 to disable the fast startup of frames in the token system.
 *
 * \details
 * Field: ::VTSS_DSM_DEV_TX_STOP_WM_CFG . FAST_STARTUP_ENA
 */
#define  VTSS_F_DSM_DEV_TX_STOP_WM_CFG_FAST_STARTUP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_DSM_DEV_TX_STOP_WM_CFG_FAST_STARTUP_ENA  VTSS_BIT(9)
#define  VTSS_X_DSM_DEV_TX_STOP_WM_CFG_FAST_STARTUP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Set this to '1' when a 10G capable port runs at speeds below 10G.
 *
 * \details
 * Field: ::VTSS_DSM_DEV_TX_STOP_WM_CFG . DEV10G_SHADOW_ENA
 */
#define  VTSS_F_DSM_DEV_TX_STOP_WM_CFG_DEV10G_SHADOW_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DSM_DEV_TX_STOP_WM_CFG_DEV10G_SHADOW_ENA  VTSS_BIT(8)
#define  VTSS_X_DSM_DEV_TX_STOP_WM_CFG_DEV10G_SHADOW_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * When the token counter value for the device exceeds this value the DSM
 * will stop transmission to the device. When set to 0 a hardware
 * calculated default value is used.When a port is configured for HDX this
 * WM must be set to 1.
 *
 * \details
 * Field: ::VTSS_DSM_DEV_TX_STOP_WM_CFG . DEV_TX_STOP_WM
 */
#define  VTSS_F_DSM_DEV_TX_STOP_WM_CFG_DEV_TX_STOP_WM(x)  VTSS_ENCODE_BITFIELD(x,1,7)
#define  VTSS_M_DSM_DEV_TX_STOP_WM_CFG_DEV_TX_STOP_WM     VTSS_ENCODE_BITMASK(1,7)
#define  VTSS_X_DSM_DEV_TX_STOP_WM_CFG_DEV_TX_STOP_WM(x)  VTSS_EXTRACT_BITFIELD(x,1,7)

/**
 * \brief
 * Clears token counter.
 *
 * \details
 * Field: ::VTSS_DSM_DEV_TX_STOP_WM_CFG . DEV_TX_CNT_CLR
 */
#define  VTSS_F_DSM_DEV_TX_STOP_WM_CFG_DEV_TX_CNT_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DSM_DEV_TX_STOP_WM_CFG_DEV_TX_CNT_CLR  VTSS_BIT(0)
#define  VTSS_X_DSM_DEV_TX_STOP_WM_CFG_DEV_TX_CNT_CLR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Pause frame handling in RX direction
 *
 * \details
 * Pause frame handling in RX direction
 *
 * Register: \a DSM:CFG:RX_PAUSE_CFG
 *
 * @param ri Replicator: x_DSM_EPORTS (??), 0-31
 */
#define VTSS_DSM_RX_PAUSE_CFG(ri)            VTSS_IOREG(VTSS_TO_DSM,0x19c + (ri))

/**
 * \brief
 * Rx Pause Enable: Enables Flow Control in Rx direction:
 *
 * \details
 * '0': Flow Control Disabled
 * '1': Flow Control Enabled.
 *
 * Field: ::VTSS_DSM_RX_PAUSE_CFG . RX_PAUSE_EN
 */
#define  VTSS_F_DSM_RX_PAUSE_CFG_RX_PAUSE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DSM_RX_PAUSE_CFG_RX_PAUSE_EN  VTSS_BIT(1)
#define  VTSS_X_DSM_RX_PAUSE_CFG_RX_PAUSE_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Configures for each Ethernet port whether flow control is obeyed locally
 * in the DSM or if the flow_control information is sent to the SCH.If not
 * all priorities should obey flow control for this port, then the DSM
 * should not stop the data stream in a flow control case, but let the SCH
 * stop the traffic to avoid head of line blocking.If all priorities should
 * obey flow control for this port, then the DSM should stop the data
 * stream locally to be able to pass 802.3 conformance testing. If the data
 * stream is stopped by the SCH frames in the OQS can not be aged, thus the
 * Allocation Bitmaps in the QS must not recover lost elements.
 *
 * \details
 * '0': This Ethernet port obeys flow control locally in the DSM.
 * '1': This Ethernet port sends flow control information to the SCH and
 * does not stop traffic in the DSM.
 *
 * Field: ::VTSS_DSM_RX_PAUSE_CFG . FC_OBEY_LOCAL
 */
#define  VTSS_F_DSM_RX_PAUSE_CFG_FC_OBEY_LOCAL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DSM_RX_PAUSE_CFG_FC_OBEY_LOCAL  VTSS_BIT(0)
#define  VTSS_X_DSM_RX_PAUSE_CFG_FC_OBEY_LOCAL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief FC configuration for Ethernet ports.
 *
 * \details
 * FC configuration for Ethernet ports.
 *
 * Register: \a DSM:CFG:ETH_FC_CFG
 *
 * @param ri Replicator: x_DSM_EPORTS (??), 0-31
 */
#define VTSS_DSM_ETH_FC_CFG(ri)              VTSS_IOREG(VTSS_TO_DSM,0x1df + (ri))

/**
 * \brief
 * Obey FC status received from ANA
 *
 * \details
 * Field: ::VTSS_DSM_ETH_FC_CFG . FC_ANA_ENA
 */
#define  VTSS_F_DSM_ETH_FC_CFG_FC_ANA_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DSM_ETH_FC_CFG_FC_ANA_ENA     VTSS_BIT(1)
#define  VTSS_X_DSM_ETH_FC_CFG_FC_ANA_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Obey FC status received from QSYS
 *
 * \details
 * Field: ::VTSS_DSM_ETH_FC_CFG . FC_QS_ENA
 */
#define  VTSS_F_DSM_ETH_FC_CFG_FC_QS_ENA(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DSM_ETH_FC_CFG_FC_QS_ENA      VTSS_BIT(0)
#define  VTSS_X_DSM_ETH_FC_CFG_FC_QS_ENA(x)   VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief PFC configuration for Ethernet ports.
 *
 * \details
 * PFC configuration for Ethernet ports.
 *
 * Register: \a DSM:CFG:ETH_PFC_CFG
 *
 * @param ri Replicator: x_DSM_EPORTS (??), 0-31
 */
#define VTSS_DSM_ETH_PFC_CFG(ri)             VTSS_IOREG(VTSS_TO_DSM,0x222 + (ri))

/**
 * \brief
 * Minimum time between two PFC PDUs when PFC state changes after
 * transmission of PFC PDU.
 *
 * \details
 * Field: ::VTSS_DSM_ETH_PFC_CFG . PFC_MIN_UPDATE_TIME
 */
#define  VTSS_F_DSM_ETH_PFC_CFG_PFC_MIN_UPDATE_TIME(x)  VTSS_ENCODE_BITFIELD(x,2,15)
#define  VTSS_M_DSM_ETH_PFC_CFG_PFC_MIN_UPDATE_TIME     VTSS_ENCODE_BITMASK(2,15)
#define  VTSS_X_DSM_ETH_PFC_CFG_PFC_MIN_UPDATE_TIME(x)  VTSS_EXTRACT_BITFIELD(x,2,15)

/**
 * \brief
 * Upon sending  PFC PDU with flow control deasserted for all priorities,
 * enforce a PFC_MIN_UPDATE_TIME delay before allowing transmission of next
 * PFC PDU.
 *
 * \details
 * Field: ::VTSS_DSM_ETH_PFC_CFG . PFC_XOFF_MIN_UPDATE_ENA
 */
#define  VTSS_F_DSM_ETH_PFC_CFG_PFC_XOFF_MIN_UPDATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DSM_ETH_PFC_CFG_PFC_XOFF_MIN_UPDATE_ENA  VTSS_BIT(1)
#define  VTSS_X_DSM_ETH_PFC_CFG_PFC_XOFF_MIN_UPDATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable PFC operation for the port.
 *
 * \details
 * Field: ::VTSS_DSM_ETH_PFC_CFG . PFC_ENA
 */
#define  VTSS_F_DSM_ETH_PFC_CFG_PFC_ENA(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DSM_ETH_PFC_CFG_PFC_ENA       VTSS_BIT(0)
#define  VTSS_X_DSM_ETH_PFC_CFG_PFC_ENA(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief MAC Configuration Register.
 *
 * \details
 * Contains configuration for flow control and operation in FDX or HDX for
 * Ethernet ports connected to the DSM.
 *
 * Register: \a DSM:CFG:MAC_CFG
 *
 * @param ri Replicator: x_DSM_EPORTS (??), 0-31
 */
#define VTSS_DSM_MAC_CFG(ri)                 VTSS_IOREG(VTSS_TO_DSM,0x265 + (ri))

/**
 * \brief
 * Tx Pause Value: The pause value inserted in each Pause Control Frame in
 * the Tx direction. It is also used to schedule the transmission of Pause
 * Control Frames when Flow Control is enabled and active. If flow control
 * is enabled, the pause value must be set to a value different from 0,
 * based on the link characteristics.
 *
 * \details
 * 0x0000: 0 quanta (512-bit times)
 * 0x0001: 1 quanta
 * ...
 * 0xFFFF: 64K-1 quanta.
 *
 * Field: ::VTSS_DSM_MAC_CFG . TX_PAUSE_VAL
 */
#define  VTSS_F_DSM_MAC_CFG_TX_PAUSE_VAL(x)   VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DSM_MAC_CFG_TX_PAUSE_VAL      VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DSM_MAC_CFG_TX_PAUSE_VAL(x)   VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * Enables HDX backpressure instead of FDX FC when FC is generated.Note:
 * 10G and 24G ports can not run HDX, so for those ports this field must
 * always be set to '0'.
 *
 * \details
 * '0': FDX FC is used.
 * '1': HDX backpressure is used.
 *
 * Field: ::VTSS_DSM_MAC_CFG . HDX_BACKPRESSURE
 */
#define  VTSS_F_DSM_MAC_CFG_HDX_BACKPRESSURE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DSM_MAC_CFG_HDX_BACKPRESSURE  VTSS_BIT(2)
#define  VTSS_X_DSM_MAC_CFG_HDX_BACKPRESSURE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Defines whether or not each pause frame will be sent twice.
 *
 * \details
 * '0': Send one pause frame two times per pause period.
 * '1': Send two pause frames back to back two times per pause period.
 *
 * Field: ::VTSS_DSM_MAC_CFG . SEND_PAUSE_FRM_TWICE
 */
#define  VTSS_F_DSM_MAC_CFG_SEND_PAUSE_FRM_TWICE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DSM_MAC_CFG_SEND_PAUSE_FRM_TWICE  VTSS_BIT(1)
#define  VTSS_X_DSM_MAC_CFG_SEND_PAUSE_FRM_TWICE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * TX pause zero on deassert. Determines whether or not a pause control
 * frame with pause value zero is transmitted when flow control is
 * deasserted.
 *
 * \details
 * '0': No pause frame with value zero is transmitted.
 * '1': Pause frame with value zero is transmitted when flow control
 * becomes inactive.
 *
 * Field: ::VTSS_DSM_MAC_CFG . TX_PAUSE_XON_XOFF
 */
#define  VTSS_F_DSM_MAC_CFG_TX_PAUSE_XON_XOFF(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DSM_MAC_CFG_TX_PAUSE_XON_XOFF  VTSS_BIT(0)
#define  VTSS_X_DSM_MAC_CFG_TX_PAUSE_XON_XOFF(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief MAC Address Base Configuration Register - bits 47-24.
 *
 * \details
 * MAC base address.
 * Used when generating Pause Control Frames with the specified MAC
 * address.
 *
 * Register: \a DSM:CFG:MAC_ADDR_BASE_HIGH_CFG
 *
 * @param ri Replicator: x_DSM_NUM_PAUSE_FRM_MAC_ADDR (??), 0-29
 */
#define VTSS_DSM_MAC_ADDR_BASE_HIGH_CFG(ri)  VTSS_IOREG(VTSS_TO_DSM,0x2a8 + (ri))

/**
 * \brief
 * Bits 47-24 of MAC base address.Used when generating Pause Control Frames
 * with the specified MAC address.
 *
 * \details
 * Field: ::VTSS_DSM_MAC_ADDR_BASE_HIGH_CFG . MAC_ADDR_HIGH
 */
#define  VTSS_F_DSM_MAC_ADDR_BASE_HIGH_CFG_MAC_ADDR_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_DSM_MAC_ADDR_BASE_HIGH_CFG_MAC_ADDR_HIGH     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_DSM_MAC_ADDR_BASE_HIGH_CFG_MAC_ADDR_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief MAC Address Base Configuration Register - bits 23-0.
 *
 * \details
 * MAC base address.
 * Used when generating Pause Control Frames with the specified MAC
 * address.
 *
 * Register: \a DSM:CFG:MAC_ADDR_BASE_LOW_CFG
 *
 * @param ri Replicator: x_DSM_NUM_PAUSE_FRM_MAC_ADDR (??), 0-29
 */
#define VTSS_DSM_MAC_ADDR_BASE_LOW_CFG(ri)   VTSS_IOREG(VTSS_TO_DSM,0x2e9 + (ri))

/**
 * \brief
 * Bits 23-0 of MAC base address.Used when generating Pause Control Frames
 * with the specified MAC address.
 *
 * \details
 * Field: ::VTSS_DSM_MAC_ADDR_BASE_LOW_CFG . MAC_ADDR_LOW
 */
#define  VTSS_F_DSM_MAC_ADDR_BASE_LOW_CFG_MAC_ADDR_LOW(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_DSM_MAC_ADDR_BASE_LOW_CFG_MAC_ADDR_LOW     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_DSM_MAC_ADDR_BASE_LOW_CFG_MAC_ADDR_LOW(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief Debug control
 *
 * \details
 * Configures which events are counted in the ageing counter.
 *
 * Register: \a DSM:CFG:DBG_CTRL
 */
#define VTSS_DSM_DBG_CTRL                    VTSS_IOREG(VTSS_TO_DSM,0x32a)

/**
 * \brief
 * Controls which event the AGE counter counts. This setting is common for
 * all aging counters.
 *
 * \details
 * 0: Number of aged frames
 * 1: Number of SOF transmitted on taxi bus
 * 2: Number of EOF transmitted on taxi bus
 * 3: Number of ABORT transmitted on taxi bus
 * 4: Reserved
 * 5: Number of retransmits requests received from port status
 * 6: Reserved
 * 7: Reserved
 *
 * Field: ::VTSS_DSM_DBG_CTRL . DBG_EVENT_CTRL
 */
#define  VTSS_F_DSM_DBG_CTRL_DBG_EVENT_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_DSM_DBG_CTRL_DBG_EVENT_CTRL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_DSM_DBG_CTRL_DBG_EVENT_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Configuration register for the taxi calendar
 *
 * \details
 * Register: \a DSM:CFG:TAXI_CAL_CFG
 *
 * @param ri Replicator: x_DSM_NUM_OF_TAXI (??), 0-5
 */
#define VTSS_DSM_TAXI_CAL_CFG(ri)            VTSS_IOREG(VTSS_TO_DSM,0x32b + (ri))

/**
 * \brief
 * Indicates which calendar is currently active.
 *
 * \details
 * 0: Calendar A
 * 1: Calendar B
 *
 * Field: ::VTSS_DSM_TAXI_CAL_CFG . CAL_SEL_STAT
 */
#define  VTSS_F_DSM_TAXI_CAL_CFG_CAL_SEL_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_DSM_TAXI_CAL_CFG_CAL_SEL_STAT  VTSS_BIT(23)
#define  VTSS_X_DSM_TAXI_CAL_CFG_CAL_SEL_STAT(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Triggers a calendar switch. If calendar A was active, then calendar B
 * becomes active. If calendar B was active, calendar A becomes active.
 *
 * \details
 * Field: ::VTSS_DSM_TAXI_CAL_CFG . CAL_SWITCH
 */
#define  VTSS_F_DSM_TAXI_CAL_CFG_CAL_SWITCH(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_DSM_TAXI_CAL_CFG_CAL_SWITCH   VTSS_BIT(22)
#define  VTSS_X_DSM_TAXI_CAL_CFG_CAL_SWITCH(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * The DSM supports 2 calendars for each taxi. This field controls which
 * calendar is getting programmed when CAL_PGM_ENA is set.
 *
 * \details
 * 0: Calendar A
 * 1: Calendar B
 *
 * Field: ::VTSS_DSM_TAXI_CAL_CFG . CAL_PGM_SEL
 */
#define  VTSS_F_DSM_TAXI_CAL_CFG_CAL_PGM_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_DSM_TAXI_CAL_CFG_CAL_PGM_SEL  VTSS_BIT(21)
#define  VTSS_X_DSM_TAXI_CAL_CFG_CAL_PGM_SEL(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Calendar index.
 *
 * \details
 * Field: ::VTSS_DSM_TAXI_CAL_CFG . CAL_IDX
 */
#define  VTSS_F_DSM_TAXI_CAL_CFG_CAL_IDX(x)   VTSS_ENCODE_BITFIELD(x,15,6)
#define  VTSS_M_DSM_TAXI_CAL_CFG_CAL_IDX      VTSS_ENCODE_BITMASK(15,6)
#define  VTSS_X_DSM_TAXI_CAL_CFG_CAL_IDX(x)   VTSS_EXTRACT_BITFIELD(x,15,6)

/**
 * \brief
 * Index of last entry in calendar sequence, that is, calendar length - 1.
 *
 * \details
 * Field: ::VTSS_DSM_TAXI_CAL_CFG . CAL_CUR_LEN
 */
#define  VTSS_F_DSM_TAXI_CAL_CFG_CAL_CUR_LEN(x)  VTSS_ENCODE_BITFIELD(x,9,6)
#define  VTSS_M_DSM_TAXI_CAL_CFG_CAL_CUR_LEN     VTSS_ENCODE_BITMASK(9,6)
#define  VTSS_X_DSM_TAXI_CAL_CFG_CAL_CUR_LEN(x)  VTSS_EXTRACT_BITFIELD(x,9,6)

/**
 * \brief
 * Value of calendar slot at index CAL_IDX.
 *
 * \details
 * Field: ::VTSS_DSM_TAXI_CAL_CFG . CAL_CUR_VAL
 */
#define  VTSS_F_DSM_TAXI_CAL_CFG_CAL_CUR_VAL(x)  VTSS_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_DSM_TAXI_CAL_CFG_CAL_CUR_VAL     VTSS_ENCODE_BITMASK(5,4)
#define  VTSS_X_DSM_TAXI_CAL_CFG_CAL_CUR_VAL(x)  VTSS_EXTRACT_BITFIELD(x,5,4)

/**
 * \brief
 * Value to write into calendar at index CAL_IDX.
 *
 * \details
 * Field: ::VTSS_DSM_TAXI_CAL_CFG . CAL_PGM_VAL
 */
#define  VTSS_F_DSM_TAXI_CAL_CFG_CAL_PGM_VAL(x)  VTSS_ENCODE_BITFIELD(x,1,4)
#define  VTSS_M_DSM_TAXI_CAL_CFG_CAL_PGM_VAL     VTSS_ENCODE_BITMASK(1,4)
#define  VTSS_X_DSM_TAXI_CAL_CFG_CAL_PGM_VAL(x)  VTSS_EXTRACT_BITFIELD(x,1,4)

/**
 * \brief
 * Enable update of calendar. When the calendar is updated CAL_CUR_LEN is
 * automatically updated to the value of CAL_IDX.
 *
 * \details
 * Field: ::VTSS_DSM_TAXI_CAL_CFG . CAL_PGM_ENA
 */
#define  VTSS_F_DSM_TAXI_CAL_CFG_CAL_PGM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DSM_TAXI_CAL_CFG_CAL_PGM_ENA  VTSS_BIT(0)
#define  VTSS_X_DSM_TAXI_CAL_CFG_CAL_PGM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Preemption configuration
 *
 * \details
 * Register: \a DSM:CFG:PREEMPT_CFG
 *
 * @param ri Replicator: x_DSM_EPORTS (??), 0-31
 */
#define VTSS_DSM_PREEMPT_CFG(ri)             VTSS_IOREG(VTSS_TO_DSM,0x334 + (ri))

/**
 * \brief
 * This field indicates the minimum size of non-final fragments of a
 * P-Frame.
 *
 * \details
 * 0: 64 bytes
 * 1: 128 bytes
 * 2: 192 bytes
 * 3: 256 bytes
 *
 * Field: ::VTSS_DSM_PREEMPT_CFG . P_MIN_SIZE
 */
#define  VTSS_F_DSM_PREEMPT_CFG_P_MIN_SIZE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DSM_PREEMPT_CFG_P_MIN_SIZE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DSM_PREEMPT_CFG_P_MIN_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a DSM:STATUS
 *
 * Status registers
 */


/**
 * \brief Counts number of aged frames.
 *
 * \details
 * This counter holds the number of aged frames from this port.
 *
 * Register: \a DSM:STATUS:AGED_FRMS
 *
 * @param ri Replicator: x_DSM_CELL_BUFS (??), 0-64
 */
#define VTSS_DSM_AGED_FRMS(ri)               VTSS_IOREG(VTSS_TO_DSM,0x377 + (ri))

/**
 * \brief
 * Count number of aged frames for each port.
 *
 * \details
 * Counter can be written by SW.
 *
 * Field: ::VTSS_DSM_AGED_FRMS . AGED_FRMS_CNT
 */
#define  VTSS_F_DSM_AGED_FRMS_AGED_FRMS_CNT(x)  (x)
#define  VTSS_M_DSM_AGED_FRMS_AGED_FRMS_CNT     0xffffffff
#define  VTSS_X_DSM_AGED_FRMS_AGED_FRMS_CNT(x)  (x)


/**
 * \brief Sticky bits for the DSM cell bus interface.
 *
 * \details
 * This register holds sticky bit information for the cell bus interface of
 * the DSM.
 *
 * Register: \a DSM:STATUS:CELL_BUS_STICKY
 */
#define VTSS_DSM_CELL_BUS_STICKY             VTSS_IOREG(VTSS_TO_DSM,0x3fe)

/**
 * \brief
 * This bit is set if cells are received after an EOF and before the
 * following SOF.
 *
 * \details
 * '0': Missing SOF has not been detected.
 * '1': Missing SOF has been detected.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DSM_CELL_BUS_STICKY . CELL_BUS_MISSING_SOF_STICKY
 */
#define  VTSS_F_DSM_CELL_BUS_STICKY_CELL_BUS_MISSING_SOF_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DSM_CELL_BUS_STICKY_CELL_BUS_MISSING_SOF_STICKY  VTSS_BIT(1)
#define  VTSS_X_DSM_CELL_BUS_STICKY_CELL_BUS_MISSING_SOF_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * This bit is set if data marked as SOF is received without the current
 * frame has been terminated with EOF. The current frame will be terminated
 * by setting the abort bit and the next frame will be discarded.
 *
 * \details
 * '0': Missing EOF has not been detected.
 * '1': Missing EOF has been detected.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DSM_CELL_BUS_STICKY . CELL_BUS_MISSING_EOF_STICKY
 */
#define  VTSS_F_DSM_CELL_BUS_STICKY_CELL_BUS_MISSING_EOF_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DSM_CELL_BUS_STICKY_CELL_BUS_MISSING_EOF_STICKY  VTSS_BIT(0)
#define  VTSS_X_DSM_CELL_BUS_STICKY_CELL_BUS_MISSING_EOF_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Buffer Overflow
 *
 * \details
 * Buffer Overflow
 *
 * Register: \a DSM:STATUS:BUF_OFLW_STICKY
 *
 * @param ri Replicator: x_DSM_CELL_BUFS_DIV32_CEIL (??), 0-2
 */
#define VTSS_DSM_BUF_OFLW_STICKY(ri)         VTSS_IOREG(VTSS_TO_DSM,0x3ff + (ri))

/**
 * \brief
 * Sticky bits for detecting buffer overflow in any of the cell buffers in
 * the DSM.
 *
 * \details
 * '0': No buffer overflow detected.
 * '1': Buffer overflow detected.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DSM_BUF_OFLW_STICKY . BUF_OFLW_STICKY
 */
#define  VTSS_F_DSM_BUF_OFLW_STICKY_BUF_OFLW_STICKY(x)  (x)
#define  VTSS_M_DSM_BUF_OFLW_STICKY_BUF_OFLW_STICKY     0xffffffff
#define  VTSS_X_DSM_BUF_OFLW_STICKY_BUF_OFLW_STICKY(x)  (x)


/**
 * \brief Buffer Underrun
 *
 * \details
 * Buffer Underrun
 *
 * Register: \a DSM:STATUS:BUF_UFLW_STICKY
 *
 * @param ri Replicator: x_DSM_CELL_BUFS_DIV32_CEIL (??), 0-2
 */
#define VTSS_DSM_BUF_UFLW_STICKY(ri)         VTSS_IOREG(VTSS_TO_DSM,0x404 + (ri))

/**
 * \brief
 * Sticky bits for detecting buffer underflow in any of the cell buffers in
 * the DSM.
 *
 * \details
 * '0': No buffer underflow detected.
 * '1': Buffer underflow detected.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DSM_BUF_UFLW_STICKY . BUF_UFLW_STICKY
 */
#define  VTSS_F_DSM_BUF_UFLW_STICKY_BUF_UFLW_STICKY(x)  (x)
#define  VTSS_M_DSM_BUF_UFLW_STICKY_BUF_UFLW_STICKY     0xffffffff
#define  VTSS_X_DSM_BUF_UFLW_STICKY_BUF_UFLW_STICKY(x)  (x)


/**
 * \brief Pause Frame pre-counter overflow sticky register
 *
 * \details
 * Pause Frame pre-counter overflow sticky register
 *
 * Register: \a DSM:STATUS:PRE_CNT_OFLW_STICKY
 */
#define VTSS_DSM_PRE_CNT_OFLW_STICKY         VTSS_IOREG(VTSS_TO_DSM,0x409)

/**
 * \brief
 * Will be set if one of the statistics pre counter have an overflow.
 *
 * \details
 * '0': Pre counter overflow has not occurred
 * '1': Pre counter overflow has occurred
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DSM_PRE_CNT_OFLW_STICKY . PRE_CNT_OFLW_STICKY
 */
#define  VTSS_F_DSM_PRE_CNT_OFLW_STICKY_PRE_CNT_OFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DSM_PRE_CNT_OFLW_STICKY_PRE_CNT_OFLW_STICKY  VTSS_BIT(8)
#define  VTSS_X_DSM_PRE_CNT_OFLW_STICKY_PRE_CNT_OFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)


/**
 * \brief Max fill level of buffer
 *
 * \details
 * Register: \a DSM:STATUS:BUF_MAX_FILL
 *
 * @param ri Replicator: x_DSM_CELL_BUFS (??), 0-64
 */
#define VTSS_DSM_BUF_MAX_FILL(ri)            VTSS_IOREG(VTSS_TO_DSM,0x40a + (ri))

/**
 * \brief
 * Maximum fill level seen in DSM buffer.
 *
 * \details
 * Unit is 4 bytes.
 *
 * Field: ::VTSS_DSM_BUF_MAX_FILL . MAX_FILL
 */
#define  VTSS_F_DSM_BUF_MAX_FILL_MAX_FILL(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_DSM_BUF_MAX_FILL_MAX_FILL     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_DSM_BUF_MAX_FILL_MAX_FILL(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * Register Group: \a DSM:RATE_LIMIT_CFG
 *
 * Configuration registers for rate limit modes
 */


/**
 * \brief Configuration register for rate limit modes
 *
 * \details
 * Configuration register for rate limit modes
 *
 * Register: \a DSM:RATE_LIMIT_CFG:TX_RATE_LIMIT_MODE
 *
 * @param ri Replicator: x_DSM_EPORTS (??), 0-31
 */
#define VTSS_DSM_TX_RATE_LIMIT_MODE(ri)      VTSS_IOREG(VTSS_TO_DSM,0x491 + (ri))

/**
 * \brief
 * Scale the IPG calculated by txRateLimitFrameOverhead and/or
 * txRateLimitPayloadRate by a power of 2 to enable shaping down to lower
 * BW.Note: For txRateLimitPayloadRate only the additional overhead
 * excluding the standard 12 byte IPG is scaled whereas for
 * txRateLimitFrameOverhead the complete value is scaled.
 *
 * \details
 * 0: Don't scale
 * 1: Multiply by 2
 * 2: Multiply by 4
 * (...)
 * 10: Multiply by 1024
 * 11-15: Reserved
 *
 * Field: ::VTSS_DSM_TX_RATE_LIMIT_MODE . IPG_SCALE_VAL
 */
#define  VTSS_F_DSM_TX_RATE_LIMIT_MODE_IPG_SCALE_VAL(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DSM_TX_RATE_LIMIT_MODE_IPG_SCALE_VAL     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DSM_TX_RATE_LIMIT_MODE_IPG_SCALE_VAL(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Defines if what is configured as header size in
 * TX_RATE_LIMIT_HDR_CFG.TX_RATE_LIMIT_HDR_SIZE is subtracted form the
 * payload in txRateLimitPayloadRate and txRateLimitFrameRate mode.
 *
 * \details
 * 0: Nothing is subtracted from payload
 * 1: TX_RATE_LIMIT_HDR_CFG.TX_RATE_LIMIT_HDR_SIZE is subtracted from
 * payload
 *
 * Field: ::VTSS_DSM_TX_RATE_LIMIT_MODE . PAYLOAD_CFG
 */
#define  VTSS_F_DSM_TX_RATE_LIMIT_MODE_PAYLOAD_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_DSM_TX_RATE_LIMIT_MODE_PAYLOAD_CFG  VTSS_BIT(9)
#define  VTSS_X_DSM_TX_RATE_LIMIT_MODE_PAYLOAD_CFG(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * This bitgroup defines whether the preamble is counted as payload in
 * txRateLimitPayloadRate and txRateLimitFrameRate mode.
 *
 * \details
 * '0': Preamble is not counted as payload
 * '1': Preamble is counted as payload
 *
 * Field: ::VTSS_DSM_TX_RATE_LIMIT_MODE . PAYLOAD_PREAM_CFG
 */
#define  VTSS_F_DSM_TX_RATE_LIMIT_MODE_PAYLOAD_PREAM_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DSM_TX_RATE_LIMIT_MODE_PAYLOAD_PREAM_CFG  VTSS_BIT(8)
#define  VTSS_X_DSM_TX_RATE_LIMIT_MODE_PAYLOAD_PREAM_CFG(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Enable for accumulated rate limit mode.Instead of taking the maximum
 * IPG of txRateLimitFrameOverhead, txRateLimitPayloadRate and
 * txRateLimitFrameRate. The resulting IPG is the sum of
 * txRateLimitFrameOverhead and txRateLimitPayloadRate.
 * txRateLimitFrameRate must be disabled.
 *
 * \details
 * '0': Accumulated rate limit mode is disabled
 * '1': Accumulated rate limit mode is enabled
 *
 * Field: ::VTSS_DSM_TX_RATE_LIMIT_MODE . TX_RATE_LIMIT_ACCUM_MODE_ENA
 */
#define  VTSS_F_DSM_TX_RATE_LIMIT_MODE_TX_RATE_LIMIT_ACCUM_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DSM_TX_RATE_LIMIT_MODE_TX_RATE_LIMIT_ACCUM_MODE_ENA  VTSS_BIT(4)
#define  VTSS_X_DSM_TX_RATE_LIMIT_MODE_TX_RATE_LIMIT_ACCUM_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable for IPG reduction to allow adaptation to clock frequency
 * offsets.When this mode is enabled, all other TX_RATE_LIMIT modes must be
 * disabled.
 *
 * \details
 * '0': tx IPG reduction test feature disabled
 * '1': tx IPG reduction test feature enabled
 *
 * Field: ::VTSS_DSM_TX_RATE_LIMIT_MODE . TX_RATE_IPG_PPM_ADAPT_ENA
 */
#define  VTSS_F_DSM_TX_RATE_LIMIT_MODE_TX_RATE_IPG_PPM_ADAPT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DSM_TX_RATE_LIMIT_MODE_TX_RATE_IPG_PPM_ADAPT_ENA  VTSS_BIT(3)
#define  VTSS_X_DSM_TX_RATE_LIMIT_MODE_TX_RATE_IPG_PPM_ADAPT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable txRateLimitFrameRate mode.IPG is extended so that frame_size +
 * IPG result in the value configured in
 * TX_FRAME_RATE_START_CFG.TX_FRAME_RATE_START
 *
 * \details
 * '0': txRateLimitFrameRate disabled
 * '1': txRateLimitFrameRate enabled
 *
 * Field: ::VTSS_DSM_TX_RATE_LIMIT_MODE . TX_RATE_LIMIT_FRAME_RATE_ENA
 */
#define  VTSS_F_DSM_TX_RATE_LIMIT_MODE_TX_RATE_LIMIT_FRAME_RATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DSM_TX_RATE_LIMIT_MODE_TX_RATE_LIMIT_FRAME_RATE_ENA  VTSS_BIT(2)
#define  VTSS_X_DSM_TX_RATE_LIMIT_MODE_TX_RATE_LIMIT_FRAME_RATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable txRateLimitPayloadRate mode.IPG is increased relative to payload
 * size.
 *
 * \details
 * '0': txRateLimitPayloadRate disabled
 * '1': txRateLimitPayloadRate enable
 *
 * Field: ::VTSS_DSM_TX_RATE_LIMIT_MODE . TX_RATE_LIMIT_PAYLOAD_RATE_ENA
 */
#define  VTSS_F_DSM_TX_RATE_LIMIT_MODE_TX_RATE_LIMIT_PAYLOAD_RATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DSM_TX_RATE_LIMIT_MODE_TX_RATE_LIMIT_PAYLOAD_RATE_ENA  VTSS_BIT(1)
#define  VTSS_X_DSM_TX_RATE_LIMIT_MODE_TX_RATE_LIMIT_PAYLOAD_RATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable txRateLimitFrameOverhead mode.IPG is increased by a fixed value
 * specified in RATE_CTRL.FRM_GAP_COMP
 *
 * \details
 * '0': txRateLimitFrameOverhead disabled
 * '1': txRateLimitFrameOverhead enabled
 *
 * Field: ::VTSS_DSM_TX_RATE_LIMIT_MODE . TX_RATE_LIMIT_FRAME_OVERHEAD_ENA
 */
#define  VTSS_F_DSM_TX_RATE_LIMIT_MODE_TX_RATE_LIMIT_FRAME_OVERHEAD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DSM_TX_RATE_LIMIT_MODE_TX_RATE_LIMIT_FRAME_OVERHEAD_ENA  VTSS_BIT(0)
#define  VTSS_X_DSM_TX_RATE_LIMIT_MODE_TX_RATE_LIMIT_FRAME_OVERHEAD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configuration register for txFineIpgStretchRatio
 *
 * \details
 * Configuration register for txFineIpgStretchRatio
 *
 * Register: \a DSM:RATE_LIMIT_CFG:TX_IPG_STRETCH_RATIO_CFG
 *
 * @param ri Replicator: x_DSM_EPORTS (??), 0-31
 */
#define VTSS_DSM_TX_IPG_STRETCH_RATIO_CFG(ri)  VTSS_IOREG(VTSS_TO_DSM,0x4d4 + (ri))

/**
 * \brief
 * Determines the extent of the interPacketGap extension, when
 * txRateLimitPayloadRate mode is enabled. It may be considered as the
 * number of bits in a packet that would require 32 octets of
 * interPacketGap extension. Note that each interPacketGap is increased by
 * an integer number of octets, the average increase is (frame length in
 * bits) * 32) / txFineIpgStretchRatio.Note: fractions left at frame border
 * will be carried on to the next frame.Example:Packet length = 64 bytes +
 * 8 bytes preamble value = 2048IPG increase = 9 bytesMaximum IPG increase
 * is 255 bytes.
 *
 * \details
 * IPG increase = frame length in bits * 32 / value.
 *
 * values below 2048 and above 518143 are reserved for arithmetic
 * processing  reasons.
 *
 * Field: ::VTSS_DSM_TX_IPG_STRETCH_RATIO_CFG . TX_FINE_IPG_STRETCH_RATIO
 */
#define  VTSS_F_DSM_TX_IPG_STRETCH_RATIO_CFG_TX_FINE_IPG_STRETCH_RATIO(x)  VTSS_ENCODE_BITFIELD(x,0,19)
#define  VTSS_M_DSM_TX_IPG_STRETCH_RATIO_CFG_TX_FINE_IPG_STRETCH_RATIO     VTSS_ENCODE_BITMASK(0,19)
#define  VTSS_X_DSM_TX_IPG_STRETCH_RATIO_CFG_TX_FINE_IPG_STRETCH_RATIO(x)  VTSS_EXTRACT_BITFIELD(x,0,19)


/**
 * \brief Configuration register for txFrameRateStart
 *
 * \details
 * Configuration register for txFrameRateStart
 *
 * Register: \a DSM:RATE_LIMIT_CFG:TX_FRAME_RATE_START_CFG
 *
 * @param ri Replicator: x_DSM_EPORTS (??), 0-31
 */
#define VTSS_DSM_TX_FRAME_RATE_START_CFG(ri)  VTSS_IOREG(VTSS_TO_DSM,0x517 + (ri))

/**
 * \brief
 * Value loaded into the txFrameRateTimer at the start of each packet, when
 * TX_RATE_LIMIT_FRAME_RATE mode is enabled.Timer is decremented with each
 * byte transmitted.IPG is set to timer value at EOF.Note: If resulting IPG
 * is smaller than the minimum IPG of 12 bytes, it will be set to 12 bytes.
 *
 * \details
 * Timer start value in bytes.
 * To take effect, value must be above 84. (64byte min frame size, 8 byte
 * preamble, 12 byte minimum IFG).
 *
 * Field: ::VTSS_DSM_TX_FRAME_RATE_START_CFG . TX_FRAME_RATE_START
 */
#define  VTSS_F_DSM_TX_FRAME_RATE_START_CFG_TX_FRAME_RATE_START(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DSM_TX_FRAME_RATE_START_CFG_TX_FRAME_RATE_START     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DSM_TX_FRAME_RATE_START_CFG_TX_FRAME_RATE_START(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Header size configuration register for txRateLimitPayloadRate mode
 *
 * \details
 * Header size configuration register for txRateLimitPayloadRate mode
 *
 * Register: \a DSM:RATE_LIMIT_CFG:TX_RATE_LIMIT_HDR_CFG
 */
#define VTSS_DSM_TX_RATE_LIMIT_HDR_CFG       VTSS_IOREG(VTSS_TO_DSM,0x55a)

/**
 * \brief
 * Defines how much of the frame is seen as header and not counted as
 * payload in txRateLimitPayloadRate and txRateLimitFrameRate mode when
 * TX_RATE_LIMIT_MODE.PAYLOAD_CFG is set to 1.
 *
 * \details
 * 0: 32 bytes are counted as header
 * 1-31: 1-31 bytes are counted as header
 *
 * Field: ::VTSS_DSM_TX_RATE_LIMIT_HDR_CFG . TX_RATE_LIMIT_HDR_SIZE
 */
#define  VTSS_F_DSM_TX_RATE_LIMIT_HDR_CFG_TX_RATE_LIMIT_HDR_SIZE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DSM_TX_RATE_LIMIT_HDR_CFG_TX_RATE_LIMIT_HDR_SIZE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DSM_TX_RATE_LIMIT_HDR_CFG_TX_RATE_LIMIT_HDR_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * Register Group: \a DSM:RATE_LIMIT_STATUS
 *
 * Status registers for rate limit modes
 */


/**
 * \brief Sticky bit register for rate limit modes
 *
 * \details
 * Sticky bit register for rate limit modes
 *
 * Register: \a DSM:RATE_LIMIT_STATUS:TX_RATE_LIMIT_STICKY
 */
#define VTSS_DSM_TX_RATE_LIMIT_STICKY        VTSS_IOREG(VTSS_TO_DSM,0x55b)

/**
 * \brief
 * Sticky bit set when one of the three tx rate limitation modes has
 * increased the IPG. I.e. when a tx rate limit mode was enabled an DSM has
 * requested the device to use a IPG different from 12 byte.
 *
 * \details
 * '0': Tx Rate Limitation has not occurred.
 * '1': Tx Rate Limitation has occurred.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DSM_TX_RATE_LIMIT_STICKY . TX_RATE_LIMIT_STICKY
 */
#define  VTSS_F_DSM_TX_RATE_LIMIT_STICKY_TX_RATE_LIMIT_STICKY(x)  (x)
#define  VTSS_M_DSM_TX_RATE_LIMIT_STICKY_TX_RATE_LIMIT_STICKY     0xffffffff
#define  VTSS_X_DSM_TX_RATE_LIMIT_STICKY_TX_RATE_LIMIT_STICKY(x)  (x)


#endif /* _VTSS_LAGUNA_REGS_DSM_H_ */
