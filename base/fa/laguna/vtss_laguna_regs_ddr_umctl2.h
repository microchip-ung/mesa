// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_DDR_UMCTL2_H_
#define _VTSS_LAGUNA_REGS_DDR_UMCTL2_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a DDR_UMCTL2
 *
 * DWC_ddr_umctl2 Memory Map
 *
 ***********************************************************************/

/**
 * Register Group: \a DDR_UMCTL2:UMCTL2_REGS
 *
 * uMCTL2 DDRC Registers
 */


/**
 * \brief Master Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:MSTR
 */
#define VTSS_DDR_UMCTL2_MSTR                 VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x0)

/**
 * \brief
 * Selects DDR3 SDRAM.
 *   Present only in designs configured to support DDR3.
 * Programming Mode: Static
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_MSTR . DDR3
 */
#define  VTSS_F_DDR_UMCTL2_MSTR_DDR3(x)       VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_MSTR_DDR3          VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_MSTR_DDR3(x)       VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Selects DDR4 SDRAM.
 *   Present only in designs configured to support DDR4.
 * Programming Mode: Static
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_MSTR . DDR4
 */
#define  VTSS_F_DDR_UMCTL2_MSTR_DDR4(x)       VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_MSTR_DDR4          VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_MSTR_DDR4(x)       VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enables Burst Chop(BC4 or 8 on-the-fly) in DDR3/DDR4.
 * Burst Chop for reads is exercised only:
 *  - In HIF configurations (UMCTL2_INCL_ARB not set)
 *  - If in full bus width mode (MSTR.data_bus_width = 00)
 *  - If MEMC_BURST_LENGTH=8 or 16
 * Burst Chop for writes is exercised only:
 *  - If CRC is disabled (CRCPARCTL1.crc_enable = 0)
 * BC4 (fixed) mode is not supported.
 * Programming Mode: Static
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_MSTR . BURSTCHOP
 */
#define  VTSS_F_DDR_UMCTL2_MSTR_BURSTCHOP(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_DDR_UMCTL2_MSTR_BURSTCHOP     VTSS_BIT(9)
#define  VTSS_X_DDR_UMCTL2_MSTR_BURSTCHOP(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Sets uMCTL2 timing mode.
 * In 2T timing, all command signals (except chip select) are held for 2
 * clocks on the SDRAM bus. Chip select is asserted on the second cycle of
 * the command.
 * Note:
 *  - 2T timing is not supported in LPDDR2/LPDDR3/LPDDR4 mode
 *  - 2T timing is not supported if the configuration parameter
 * MEMC_CMD_RTN2IDLE is set
 *  - 2T timing is not supported in DDR4 geardown mode
 *  - 2T timing is not supported in Shared-AC dual channel mode and the
 * register value is don't care
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_MSTR . EN_2T_TIMING_MODE
 */
#define  VTSS_F_DDR_UMCTL2_MSTR_EN_2T_TIMING_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_DDR_UMCTL2_MSTR_EN_2T_TIMING_MODE  VTSS_BIT(10)
#define  VTSS_X_DDR_UMCTL2_MSTR_EN_2T_TIMING_MODE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Indicates the DRAM in geardown mode.
 *
 *  This register can be changed, only when the controller is in the
 * self-refresh mode.
 * This signal must be set the same value as MR3 bit A3.
 *
 * Note:
 *  - Geardown mode is not supported if the configuration parameter
 * MEMC_CMD_RTN2IDLE is set
 *  - Geardown mode is not supported if the configuration parameter
 * UMCTL2_SHARED_AC is set (in Shared-AC mode) and the register value is
 * don't care
 * Programming Mode: Quasi-dynamic Group 2
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_MSTR . GEARDOWN_MODE
 */
#define  VTSS_F_DDR_UMCTL2_MSTR_GEARDOWN_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_DDR_UMCTL2_MSTR_GEARDOWN_MODE  VTSS_BIT(11)
#define  VTSS_X_DDR_UMCTL2_MSTR_GEARDOWN_MODE(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Selects proportion of DQ bus width that is used by the SDRAM.
 *
 *   Note that half bus width mode is only supported when the SDRAM bus
 * width is a multiple of 16, and quarter bus width mode is only supported
 * when the SDRAM bus width is a multiple of 32 and the configuration
 * parameter MEMC_QBUS_SUPPORT is set. Bus width refers to DQ bus width
 * (excluding any ECC width).
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h3:

 *
 * Field: ::VTSS_DDR_UMCTL2_MSTR . DATA_BUS_WIDTH
 */
#define  VTSS_F_DDR_UMCTL2_MSTR_DATA_BUS_WIDTH(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_DDR_UMCTL2_MSTR_DATA_BUS_WIDTH     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_DDR_UMCTL2_MSTR_DATA_BUS_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * Sets DLL-off mode.
 * If DDR4 CRC/parity retry is enabled (CRCPARCTL1.crc_parity_retry_enable
 * = 1), dll_off_mode is not supported, and this bit must be set to '0'.
 * Programming Mode: Quasi-dynamic Group 2
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_MSTR . DLL_OFF_MODE
 */
#define  VTSS_F_DDR_UMCTL2_MSTR_DLL_OFF_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_DDR_UMCTL2_MSTR_DLL_OFF_MODE  VTSS_BIT(15)
#define  VTSS_X_DDR_UMCTL2_MSTR_DLL_OFF_MODE(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Indicates SDRAM burst length used.
 *
 *   All other values are reserved.(See "Values" section)
 * This bit controls the burst size used to access the SDRAM. This must
 * match the burst length mode register setting in the SDRAM. (For BC4/8
 * on-the-fly mode of DDR3 and DDR4, set this field to 0x0100) Burst length
 * of 2 is not supported with AXI ports when MEMC_BURST_LENGTH is 8.
 * Burst length of 2 is only supported when the controller is operating in
 * 1:1 frequency mode.
 * For DDR3, DDR4 and LPDDR3, this must be set to 0x0100 (BL8).
 * For LPDDR4, this must be set to 0x1000 (BL16).
 * Programming Mode: Static
 *
 * \details
 * 'h8:
 * 'h1:
 * 'h2:
 * 'h4:

 *
 * Field: ::VTSS_DDR_UMCTL2_MSTR . BURST_RDWR
 */
#define  VTSS_F_DDR_UMCTL2_MSTR_BURST_RDWR(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DDR_UMCTL2_MSTR_BURST_RDWR     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DDR_UMCTL2_MSTR_BURST_RDWR(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Only present for multi-rank configurations.
 * Each bit represents one rank. For two-rank configurations, only
 * bits[25:24] are present.
 *  - 1 - Populated
 *  - 0 - Unpopulated
 * LSB is the lowest rank number.
 * For two ranks only the following values are legal:
 *  - OneRank
 *  - Tworanks
 *  - Others
 *  - Reserved
 * For four ranks following combinations are legal:
 *  - 0001 - One rank
 *  - 0011 - Two ranks
 *  - 1111 - Four ranks
 *
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_MSTR . ACTIVE_RANKS
 */
#define  VTSS_F_DDR_UMCTL2_MSTR_ACTIVE_RANKS(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_DDR_UMCTL2_MSTR_ACTIVE_RANKS     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_DDR_UMCTL2_MSTR_ACTIVE_RANKS(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * Indicates the configuration of the device used in the system.
 * Programming Mode: Static
 *
 * \details
 * 'h2:
 * 'h3:
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_MSTR . DEVICE_CONFIG
 */
#define  VTSS_F_DDR_UMCTL2_MSTR_DEVICE_CONFIG(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_DDR_UMCTL2_MSTR_DEVICE_CONFIG     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_DDR_UMCTL2_MSTR_DEVICE_CONFIG(x)  VTSS_EXTRACT_BITFIELD(x,30,2)


/**
 * \brief Operating Mode Status Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:STAT
 */
#define VTSS_DDR_UMCTL2_STAT                 VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x1)

/**
 * \brief
 * This is 3-bits wide in configurations with
 * mDDR/LPDDR2/LPDDR3/LPDDR4/DDR4 support and 2-bits in all other
 * configurations.
 * non-mDDR/LPDDR2/LPDDR3/LPDDR4 and non-DDR4 designs:
 *  - 00 - Init
 *  - 01 - Normal
 *  - 10 - Power-down
 *  - 11 - Self-refresh
 * mDDR/LPDDR2/LPDDR3 or DDR4 designs:
 *  - 000 - Init
 *  - 001 - Normal
 *  - 010 - Power-down
 *  - 011 - Self-refresh
 *  - 1XX - Deep power-down/Maximum Power Saving Mode
 * LPDDR4 designs:
 *  - 000 - Init
 *  - 001 - Normal
 *  - 010 - Power-down
 *  - 011 - Self-refresh/Self-refresh power-down
 *
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_STAT . OPERATING_MODE
 */
#define  VTSS_F_DDR_UMCTL2_STAT_OPERATING_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_DDR_UMCTL2_STAT_OPERATING_MODE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_DDR_UMCTL2_STAT_OPERATING_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Flags if self-refresh (except LPDDR4), or SR-Powerdown (LPDDR4) is
 * entered, and if it is under automatic self-refresh control only or not.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h3:
 * 'h2:

 *
 * Field: ::VTSS_DDR_UMCTL2_STAT . SELFREF_TYPE
 */
#define  VTSS_F_DDR_UMCTL2_STAT_SELFREF_TYPE(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_DDR_UMCTL2_STAT_SELFREF_TYPE     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_DDR_UMCTL2_STAT_SELFREF_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * Self-refresh with CAMs not empty.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_STAT . SELFREF_CAM_NOT_EMPTY
 */
#define  VTSS_F_DDR_UMCTL2_STAT_SELFREF_CAM_NOT_EMPTY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DDR_UMCTL2_STAT_SELFREF_CAM_NOT_EMPTY  VTSS_BIT(12)
#define  VTSS_X_DDR_UMCTL2_STAT_SELFREF_CAM_NOT_EMPTY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)


/**
 * \brief Mode Register Read/Write Control Register 0.
Note: Do not enable more than one of the following fields simultaneously:
 - sw_init_int
 - pda_en
 - mpr_en
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:MRCTRL0
 */
#define VTSS_DDR_UMCTL2_MRCTRL0              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x4)

/**
 * \brief
 * Indicates whether the mode register operation is read or write. Only
 * used for LPDDR2/LPDDR3/LPDDR4/DDR4.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_MRCTRL0 . MR_TYPE
 */
#define  VTSS_F_DDR_UMCTL2_MRCTRL0_MR_TYPE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_MRCTRL0_MR_TYPE    VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_MRCTRL0_MR_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Indicates whether the mode register operation is MRS or WR/RD for MPR
 * (only supported for DDR4).
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_MRCTRL0 . MPR_EN
 */
#define  VTSS_F_DDR_UMCTL2_MRCTRL0_MPR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_MRCTRL0_MPR_EN     VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_MRCTRL0_MPR_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Indicates whether the mode register operation is MRS in PDA mode or not.
 *   Note that when pba_mode=1, PBA access is initiated instead of PDA
 * access.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_MRCTRL0 . PDA_EN
 */
#define  VTSS_F_DDR_UMCTL2_MRCTRL0_PDA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_UMCTL2_MRCTRL0_PDA_EN     VTSS_BIT(2)
#define  VTSS_X_DDR_UMCTL2_MRCTRL0_PDA_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Indicates whether software intervention is allowed through
 * MRCTRL0/MRCTRL1 before automatic SDRAM initialization routine or not.
 * For DDR4, this bit can be used to initialize the DDR4 RCD (MR7) before
 * automatic SDRAM initialization.
 * For LPDDR4, this bit can be used to program additional mode registers
 * before automatic SDRAM initialization if necessary.
 * In LPDDR4 dual channel mode, note that this must be programmed to both
 * channels beforehand.
 * Note that this must be cleared to 0 after completing Software operation.
 * Otherwise, SDRAM initialization routine does not re-start.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_MRCTRL0 . SW_INIT_INT
 */
#define  VTSS_F_DDR_UMCTL2_MRCTRL0_SW_INIT_INT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_UMCTL2_MRCTRL0_SW_INIT_INT  VTSS_BIT(3)
#define  VTSS_X_DDR_UMCTL2_MRCTRL0_SW_INIT_INT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Controls which rank is accessed by MRCTRL0.mr_wr.
 * Normally, it is desired to access all ranks, so all bits must be set to
 * 1. However, for multi-rank UDIMMs/RDIMMs/LRDIMMs which implement address
 * mirroring, it might be necessary to access ranks individually.
 * Examples (assuming uMCTL2 is configured for 4 ranks):
 *  - 0x1 - Select rank 0 only
 *  - 0x2 - Select rank 1 only
 *  - 0x5 - Select ranks 0 and 2
 *  - 0xA - Select ranks 1 and 3
 *  - 0xF - Select ranks 0, 1, 2 and 3
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_MRCTRL0 . MR_RANK
 */
#define  VTSS_F_DDR_UMCTL2_MRCTRL0_MR_RANK(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_DDR_UMCTL2_MRCTRL0_MR_RANK     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_DDR_UMCTL2_MRCTRL0_MR_RANK(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * Address of the mode register that is to be written to.
 *
 *   Don't Care for LPDDR2/LPDDR3/LPDDR4 (see MRCTRL1.mr_data for mode
 * register addressing in LPDDR2/LPDDR3/LPDDR4).
 * This signal is also used for writing to control words of the register
 * chip on RDIMMs/LRDIMMs. In this case, it corresponds to the bank address
 * bits sent to the RDIMM/LRDIMM.
 * In case of DDR4, the bit[3:2] corresponds to the bank group bits.
 * Therefore, the bit[3] as well as the bit[2:0] must be set to an
 * appropriate value which is considered both the Address Mirroring of
 * UDIMMs/RDIMMs/LRDIMMs and the Output Inversion of RDIMMs/LRDIMMs.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h3:
 * 'h4:
 * 'h5:
 * 'h6:
 * 'h7:

 *
 * Field: ::VTSS_DDR_UMCTL2_MRCTRL0 . MR_ADDR
 */
#define  VTSS_F_DDR_UMCTL2_MRCTRL0_MR_ADDR(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_DDR_UMCTL2_MRCTRL0_MR_ADDR     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_DDR_UMCTL2_MRCTRL0_MR_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * Indicates whether PBA access is executed. When setting this bit to 1
 * along with setting pda_en to 1, uMCTL2 initiates PBA access instead of
 * PDA access.
 *   The completion of PBA access is confirmed by MRSTAT.pda_done in the
 * same way as PDA.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_MRCTRL0 . PBA_MODE
 */
#define  VTSS_F_DDR_UMCTL2_MRCTRL0_PBA_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_UMCTL2_MRCTRL0_PBA_MODE   VTSS_BIT(30)
#define  VTSS_X_DDR_UMCTL2_MRCTRL0_PBA_MODE(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Triggers a Mode Register Read or Write operation.
 *
 *   The other fields of this register must be written in a separate APB
 * transaction, before setting this mr_wr bit.
 * It is recommended NOT to set this signal if in Init, Deep power-down, or
 * MPSM operating modes.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_MRCTRL0 . MR_WR
 */
#define  VTSS_F_DDR_UMCTL2_MRCTRL0_MR_WR(x)   VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_UMCTL2_MRCTRL0_MR_WR      VTSS_BIT(31)
#define  VTSS_X_DDR_UMCTL2_MRCTRL0_MR_WR(x)   VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief Mode Register Read/Write Control Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:MRCTRL1
 */
#define VTSS_DDR_UMCTL2_MRCTRL1              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x5)

/**
 * \brief
 * Mode register write data for all non-LPDDR2/non-LPDDR3/non-LPDDR4 modes.
 * For LPDDR2/LPDDR3/LPDDR4, MRCTRL1[15:0] are interpreted as:
 *  - [15:8] - MR Address
 *  - [7:0] - MR data for writes, don't care for reads
 *  This is 18-bits wide in configurations with DDR4 support and 16-bits in
 * all other configurations.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_MRCTRL1 . MR_DATA
 */
#define  VTSS_F_DDR_UMCTL2_MRCTRL1_MR_DATA(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_DDR_UMCTL2_MRCTRL1_MR_DATA     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_DDR_UMCTL2_MRCTRL1_MR_DATA(x)  VTSS_EXTRACT_BITFIELD(x,0,18)


/**
 * \brief Mode Register Read/Write Status Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:MRSTAT
 */
#define VTSS_DDR_UMCTL2_MRSTAT               VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x6)

/**
 * \brief
 * The SoC might initiate a MR write operation only if this signal is low.
 * This signal goes:
 *  - High in the clock after the uMCTL2 accepts the MRW/MRR request
 *  - Low when the MRW/MRR command is issued to the SDRAM
 * It is recommended not to perform MRW/MRR commands when
 * 'MRSTAT.mr_wr_busy' is high.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_MRSTAT . MR_WR_BUSY
 */
#define  VTSS_F_DDR_UMCTL2_MRSTAT_MR_WR_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_MRSTAT_MR_WR_BUSY  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_MRSTAT_MR_WR_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * The SoC might initiate a MR write operation in PDA/PBA mode only if this
 * signal is low.
 * This signal goes:
 *  - High when three consecutive MRS commands related to the PDA/PBA mode
 * are issued to the SDRAM
 *  - Low when MRCTRL0.pda_en becomes 0
 *  Therefore, it is recommended to write MRCTRL0.pda_en to 0 after this
 * signal goes high in order to prepare to perform PDA operation next time.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_MRSTAT . PDA_DONE
 */
#define  VTSS_F_DDR_UMCTL2_MRSTAT_PDA_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DDR_UMCTL2_MRSTAT_PDA_DONE    VTSS_BIT(8)
#define  VTSS_X_DDR_UMCTL2_MRSTAT_PDA_DONE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)


/**
 * \brief Mode Register Read/Write Control Register 2
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:MRCTRL2
 */
#define VTSS_DDR_UMCTL2_MRCTRL2              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x7)

/**
 * \brief
 * Indicates the devices to be selected during the MRS that happens in PDA
 * mode.
 * Each bit is associated with one device. For example, bit[0] corresponds
 * to Device 0, bit[1] to Device 1 and so on.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_MRCTRL2 . MR_DEVICE_SEL
 */
#define  VTSS_F_DDR_UMCTL2_MRCTRL2_MR_DEVICE_SEL(x)  (x)
#define  VTSS_M_DDR_UMCTL2_MRCTRL2_MR_DEVICE_SEL     0xffffffff
#define  VTSS_X_DDR_UMCTL2_MRCTRL2_MR_DEVICE_SEL(x)  (x)


/**
 * \brief Low Power Control Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:PWRCTL
 */
#define VTSS_DDR_UMCTL2_PWRCTL               VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xc)

/**
 * \brief
 * Sets Self-refresh.
 * This register bit may be re-programmed during the course of normal
 * operation.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PWRCTL . SELFREF_EN
 */
#define  VTSS_F_DDR_UMCTL2_PWRCTL_SELFREF_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_PWRCTL_SELFREF_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_PWRCTL_SELFREF_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Sets Power-down mode.
 * This register bit may be re-programmed during the course of normal
 * operation.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PWRCTL . POWERDOWN_EN
 */
#define  VTSS_F_DDR_UMCTL2_PWRCTL_POWERDOWN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_PWRCTL_POWERDOWN_EN  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_PWRCTL_POWERDOWN_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enables the assertion of dfi_dram_clk_disable whenever a clock is not
 * required by the SDRAM.
 * Assertion of dfi_dram_clk_disable is as follows:
 * In DDR2/DDR3, can only be asserted in self-refresh.
 * In DDR4, can be asserted in following:
 *  - In Self-refresh
 *  - In Maximum Power Saving Mode
 * In mDDR/LPDDR2/LPDDR3, can be asserted in following:
 *  - In Self-refresh
 *  - In Power Down
 *  - In Deep Power Down
 *  - During Normal operation (Clock Stop)
 * In LPDDR4, can be asserted in following:
 *  - In Self-refresh Power Down
 *  - In Power Down
 *  - During Normal operation (Clock Stop)
 *
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PWRCTL . EN_DFI_DRAM_CLK_DISABLE
 */
#define  VTSS_F_DDR_UMCTL2_PWRCTL_EN_DFI_DRAM_CLK_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_UMCTL2_PWRCTL_EN_DFI_DRAM_CLK_DISABLE  VTSS_BIT(3)
#define  VTSS_X_DDR_UMCTL2_PWRCTL_EN_DFI_DRAM_CLK_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Sets Maximum powersaving mode.
 * Present only in designs configured to support DDR4. For non-DDR4, this
 * register must not be set to 1.
 * Note that MPSM is not supported when using a Synopsys DWC DDR PHY, if
 * the PHY parameter DWC_AC_CS_USE is disabled, as the MPSM exit sequence
 * requires the chip-select signal to toggle.
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PWRCTL . MPSM_EN
 */
#define  VTSS_F_DDR_UMCTL2_PWRCTL_MPSM_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_PWRCTL_MPSM_EN     VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_PWRCTL_MPSM_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * A value of 1 to this register causes system to move to self-refresh
 * state immediately, as long as it is not in INIT or DPD/MPSM
 * operating_mode.
 * This is referred to as Software Entry/Exit to self-refresh.
 *
 * Programming Mode: Dynamic
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_PWRCTL . SELFREF_SW
 */
#define  VTSS_F_DDR_UMCTL2_PWRCTL_SELFREF_SW(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_UMCTL2_PWRCTL_SELFREF_SW  VTSS_BIT(5)
#define  VTSS_X_DDR_UMCTL2_PWRCTL_SELFREF_SW(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Indicates whether skipping CAM draining is allowed when entering
 * self-refresh.
 * This register field cannot be modified while PWRCTL.selfref_sw == 1.
 *
 *   Note, PWRCTL.dis_cam_drain_selfref=1 is unsupported in this release.
 * PWRCTL.dis_cam_drain_selfref=0 is required.
 *
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PWRCTL . DIS_CAM_DRAIN_SELFREF
 */
#define  VTSS_F_DDR_UMCTL2_PWRCTL_DIS_CAM_DRAIN_SELFREF(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DDR_UMCTL2_PWRCTL_DIS_CAM_DRAIN_SELFREF  VTSS_BIT(7)
#define  VTSS_X_DDR_UMCTL2_PWRCTL_DIS_CAM_DRAIN_SELFREF(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/**
 * \brief Low Power Timing Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:PWRTMG
 */
#define VTSS_DDR_UMCTL2_PWRTMG               VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xd)

/**
 * \brief
 * After this many clocks of the DDRC command channel being idle the uMCTL2
 * automatically puts the SDRAM into power-down.
 * The DDRC command channel is considered idle when there are no HIF
 * commands outstanding. This must be enabled in the PWRCTL.powerdown_en.
 * FOR PERFORMANCE ONLY.
 * Unit: Multiples of 32 DFI clock cycles.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Quasi-dynamic Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PWRTMG . POWERDOWN_TO_X32
 */
#define  VTSS_F_DDR_UMCTL2_PWRTMG_POWERDOWN_TO_X32(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_UMCTL2_PWRTMG_POWERDOWN_TO_X32     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_UMCTL2_PWRTMG_POWERDOWN_TO_X32(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * After this many clocks of the DDRC command channel being idle the uMCTL2
 * automatically puts the SDRAM into self-refresh.
 * The DDRC command channel is considered idle when there are no HIF
 * commands outstanding. This must be enabled in the PWRCTL.selfref_en.
 * FOR PERFORMANCE ONLY.
 * Unit: Multiples of 32 DFI clock cycles.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Quasi-dynamic Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PWRTMG . SELFREF_TO_X32
 */
#define  VTSS_F_DDR_UMCTL2_PWRTMG_SELFREF_TO_X32(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_UMCTL2_PWRTMG_SELFREF_TO_X32     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_UMCTL2_PWRTMG_SELFREF_TO_X32(x)  VTSS_EXTRACT_BITFIELD(x,16,8)


/**
 * \brief Hardware Low Power Control Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:HWLPCTL
 */
#define VTSS_DDR_UMCTL2_HWLPCTL              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xe)

/**
 * \brief
 * Enabled for Hardware Low Power Interface.
 *
 * Programming Mode: Quasi-dynamic Group 2
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_HWLPCTL . HW_LP_EN
 */
#define  VTSS_F_DDR_UMCTL2_HWLPCTL_HW_LP_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_HWLPCTL_HW_LP_EN   VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_HWLPCTL_HW_LP_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Allows use of cactive_in_ddrc to exit from the automatic clock stop,
 * automatic power down or automatic self-refresh modes.
 * Note, it does not cause exit of self-refresh that was caused by Hardware
 * Low Power Interface and/or Software (PWRCTL.selfref_sw).
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_HWLPCTL . HW_LP_EXIT_IDLE_EN
 */
#define  VTSS_F_DDR_UMCTL2_HWLPCTL_HW_LP_EXIT_IDLE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_HWLPCTL_HW_LP_EXIT_IDLE_EN  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_HWLPCTL_HW_LP_EXIT_IDLE_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Hardware idle period.
 * The cactive_ddrc output is driven low if the DDRC command channel is
 * idle for hw_lp_idle * 32 cycles if not in INIT or DPD/MPSM
 * operating_mode.
 * The DDRC command channel is considered idle when there are no HIF
 * commands outstanding. The hardware idle function is disabled when
 * hw_lp_idle_x32=0. hw_lp_idle_x32=1 is an illegal value.
 * FOR PERFORMANCE ONLY.
 * Unit: Multiples of 32 DFI clock cycles.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_HWLPCTL . HW_LP_IDLE_X32
 */
#define  VTSS_F_DDR_UMCTL2_HWLPCTL_HW_LP_IDLE_X32(x)  VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_DDR_UMCTL2_HWLPCTL_HW_LP_IDLE_X32     VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_DDR_UMCTL2_HWLPCTL_HW_LP_IDLE_X32(x)  VTSS_EXTRACT_BITFIELD(x,16,12)


/**
 * \brief Refresh Control Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:RFSHCTL0
 */
#define VTSS_DDR_UMCTL2_RFSHCTL0             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x14)

/**
 * \brief
 * The programmed value + 1 is the number of refresh timeouts that is
 * allowed to accumulate before traffic is blocked and the refreshes are
 * forced to execute.
 * Closing pages to perform a refresh is a one-time penalty that must be
 * paid for each group of refreshes. Therefore, performing refreshes in a
 * burst reduces the per-refresh penalty of these page closings.
 * Higher numbers for RFSHCTL.refresh_burst slightly increases utilization;
 * lower numbers decreases the worst-case latency associated with
 * refreshes.
 *  - 0 - Single refresh
 *  - 1 - Burst-of-2 refresh
 *  - 7 - Burst-of-8 refresh
 * For more information on burst refresh feature, see section 3.9 of DDR2
 * JEDEC specification - JESD79-2F.pdf.
 * For DDR2/3, the refresh is always per-rank and not per-bank. The rank
 * refresh can be accumulated over 8*tREFI cycles using the burst refresh
 * feature.
 * In DDR4 mode, according to Fine Granularity feature, 8 refreshes can be
 * postponed in 1X mode, 16 refreshes in 2X mode and 32 refreshes in 4X
 * mode.
 * If using PHY-initiated updates, care must be taken in the setting of
 * RFSHCTL0.refresh_burst, to ensure that tRFCmax is not violated due to a
 * PHY-initiated update occurring shortly before a refresh burst is due.
 * In this situation, the refresh burst is delayed until the PHY-initiated
 * update is complete.
 * In per-bank refresh mode of LPDDR2/LPDDR3/LPDDR4
 * (RFSHCTL0.per_bank_refresh = 1), 64 refreshes can be postponed.
 * In LPDDR4 mode, if per-bank refresh is enabled
 * (RFSHCTL0.per_bank_refresh = 1), and automatic switching from per-bank
 * to all-bank refresh is enabled (RFSHCTL0.auto_refab_en = 2'b01 or
 * RFSHCTL0.auto_refab_en = 2'b10), the uCMTL2 divides this value by 8 when
 * it switches automatically from per-bank to all-bank refresh.
 * Programming Mode: Dynamic - Refresh Related
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_RFSHCTL0 . REFRESH_BURST
 */
#define  VTSS_F_DDR_UMCTL2_RFSHCTL0_REFRESH_BURST(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_DDR_UMCTL2_RFSHCTL0_REFRESH_BURST     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_DDR_UMCTL2_RFSHCTL0_REFRESH_BURST(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/**
 * \brief
 * If the refresh timer (tRFCnom, also known as tREFI) has expired at least
 * once, then a speculative refresh may be performed.
 * A speculative refresh is a refresh performed at a time when refresh
 * would be useful. When the SDRAM bus is idle for a period of time
 * determined by this RFSHCTL0.refresh_to_x1_x32 and the refresh timer has
 * expired at least once since the last refresh, then a speculative refresh
 * is performed.
 * Speculative refreshes continues successively until there are no
 * refreshes pending or until new reads or writes are issued to the uMCTL2.
 * FOR PERFORMANCE ONLY.
 * Unit: DFI clock cycles or multiples of 32 DFI clock cycles, depending on
 * RFSHTMG.t_rfc_nom_x1_sel.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Dynamic - Refresh Related
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_RFSHCTL0 . REFRESH_TO_X1_X32
 */
#define  VTSS_F_DDR_UMCTL2_RFSHCTL0_REFRESH_TO_X1_X32(x)  VTSS_ENCODE_BITFIELD(x,12,5)
#define  VTSS_M_DDR_UMCTL2_RFSHCTL0_REFRESH_TO_X1_X32     VTSS_ENCODE_BITMASK(12,5)
#define  VTSS_X_DDR_UMCTL2_RFSHCTL0_REFRESH_TO_X1_X32(x)  VTSS_EXTRACT_BITFIELD(x,12,5)

/**
 * \brief
 * Threshold value in number of DFI clock cycles before the critical
 * refresh or page timer expires.
 * A critical refresh is to be issued before this threshold is reached.
 * It is recommended that this not be changed from the default value,
 * currently shown as 0x2.
 * It must always be less than internally used t_rfc_nom/32.
 * Note that internally used t_rfc_nom is equal to RFSHTMG.t_rfc_nom_x1_x32
 * * 32 if RFSHTMG.t_rfc_nom_x1_sel=0.
 * If RFSHTMG.t_rfc_nom_x1_sel=1 (for LPDDR2/LPDDR3/LPDDR4 per-bank refresh
 * only), internally used t_rfc_nom is equal to RFSHTMG.t_rfc_nom_x1_x32.
 * Note that, in LPDDR2/LPDDR3/LPDDR4, internally used t_rfc_nom may be
 * divided by four if derating is enabled (DERATEEN.derate_enable=1).
 * Unit: Multiples of 32 DFI clock cycles.
 * Programming Mode: Dynamic - Refresh Related
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_RFSHCTL0 . REFRESH_MARGIN
 */
#define  VTSS_F_DDR_UMCTL2_RFSHCTL0_REFRESH_MARGIN(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_DDR_UMCTL2_RFSHCTL0_REFRESH_MARGIN     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_DDR_UMCTL2_RFSHCTL0_REFRESH_MARGIN(x)  VTSS_EXTRACT_BITFIELD(x,20,4)


/**
 * \brief Refresh Control Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:RFSHCTL1
 */
#define VTSS_DDR_UMCTL2_RFSHCTL1             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x15)

/**
 * \brief
 * Refresh timer start for rank 0 (only present in multi-rank
 * configurations).
 * This is useful in staggering the refreshes to multiple ranks to help
 * traffic to proceed.
 * This is explained in Refresh Controls section of the Architecture
 * chapter.
 * FOR PERFORMANCE ONLY.
 * Unit: Multiples of 32 DFI clock cycles.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Dynamic - Refresh Related
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_RFSHCTL1 . REFRESH_TIMER0_START_VALUE_X32
 */
#define  VTSS_F_DDR_UMCTL2_RFSHCTL1_REFRESH_TIMER0_START_VALUE_X32(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_UMCTL2_RFSHCTL1_REFRESH_TIMER0_START_VALUE_X32     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_UMCTL2_RFSHCTL1_REFRESH_TIMER0_START_VALUE_X32(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Refresh timer start for rank 1 (only present in multi-rank
 * configurations).
 * This is useful in staggering the refreshes to multiple ranks to help
 * traffic to proceed.
 * This is explained in Refresh Controls section of the Architecture
 * chapter.
 * FOR PERFORMANCE ONLY.
 * Unit: Multiples of 32 DFI clock cycles.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Dynamic - Refresh Related
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_RFSHCTL1 . REFRESH_TIMER1_START_VALUE_X32
 */
#define  VTSS_F_DDR_UMCTL2_RFSHCTL1_REFRESH_TIMER1_START_VALUE_X32(x)  VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_DDR_UMCTL2_RFSHCTL1_REFRESH_TIMER1_START_VALUE_X32     VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_DDR_UMCTL2_RFSHCTL1_REFRESH_TIMER1_START_VALUE_X32(x)  VTSS_EXTRACT_BITFIELD(x,16,12)


/**
 * \brief Refresh Control Register 3
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:RFSHCTL3
 */
#define VTSS_DDR_UMCTL2_RFSHCTL3             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x18)

/**
 * \brief
 * Disables auto-refresh generated by the uMCTL2.
 * When auto-refresh is disabled, the SoC must generate refreshes using the
 * registers DBGCMD.rankn_refresh.
 * When dis_auto_refresh transitions from 0 to 1, any pending refreshes are
 * immediately scheduled by the uMCTL2.
 * If DDR4 CRC/parity retry is enabled (CRCPARCTL1.crc_parity_retry_enable
 * = 1), disable auto-refresh is not supported, and this bit must be set to
 * '0'.
 * (DDR4 only) If FGR mode is enabled (RFSHCTL3.refresh_mode > 0), disable
 * auto-refresh is not supported, and this bit must be set to '0'.
 * This register field is changeable on the fly.
 * Programming Mode: Dynamic - Refresh Related
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_RFSHCTL3 . DIS_AUTO_REFRESH
 */
#define  VTSS_F_DDR_UMCTL2_RFSHCTL3_DIS_AUTO_REFRESH(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_RFSHCTL3_DIS_AUTO_REFRESH  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_RFSHCTL3_DIS_AUTO_REFRESH(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Toggle this signal (either from 0 to 1 or from 1 to 0) to indicate that
 * the refresh registers have been updated.
 * refresh_update_level must not be toggled when the DDRC is in reset
 * (core_ddrc_rstn = 0).
 * The refresh registers are automatically updated when exiting reset.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_RFSHCTL3 . REFRESH_UPDATE_LEVEL
 */
#define  VTSS_F_DDR_UMCTL2_RFSHCTL3_REFRESH_UPDATE_LEVEL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_RFSHCTL3_REFRESH_UPDATE_LEVEL  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_RFSHCTL3_REFRESH_UPDATE_LEVEL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Indicates fine granularity refresh mode.
 * Everything not described in "Values" section is reserved.
 *
 * Note:
 *  - Only Fixed 1x mode is supported if RFSHCTL3.dis_auto_refresh = 1
 *  - The on-the-fly modes are not supported in this version of the uMCTL2
 *  - This must be set up while the controller is in reset or while the
 * controller is in self-refresh mode. Changing this during normal
 * operation is not allowed. Making this a dynamic register is supported in
 * future version of the uMCTL2
 *  - This register field has effect only if a DDR4 SDRAM device is in use
 * (MSTR.ddr4 = 1)
 * Programming Mode: Quasi-dynamic Group 2
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h5:
 * 'h6:

 *
 * Field: ::VTSS_DDR_UMCTL2_RFSHCTL3 . REFRESH_MODE
 */
#define  VTSS_F_DDR_UMCTL2_RFSHCTL3_REFRESH_MODE(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_DDR_UMCTL2_RFSHCTL3_REFRESH_MODE     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_DDR_UMCTL2_RFSHCTL3_REFRESH_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/**
 * \brief Refresh Timing Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:RFSHTMG
 */
#define VTSS_DDR_UMCTL2_RFSHTMG              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x19)

/**
 * \brief
 * tRFC (min): Minimum time from refresh to refresh or activate.
 * When the controller is operating in 1:1 mode, t_rfc_min must be set to
 * RoundUp(tRFCmin/tCK).
 * When the controller is operating in 1:2 mode, t_rfc_min must be set to
 * RoundUp(RoundUp(tRFCmin/tCK)/2).
 * In LPDDR2/LPDDR3/LPDDR4 mode:
 *  - If using all-bank refreshes, the tRFCmin value in the previous
 * equations is equal to tRFCab
 *  - If using per-bank refreshes, the tRFCmin value in the previous
 * equations is equal to tRFCpb
 * In DDR4 mode, the tRFCmin value in the previous equations is different
 * depending on the refresh mode (fixed 1X,2X,4X) and the device density.
 * You must program the appropriate value from the spec based on the
 * 'refresh_mode' and the device density that is used.
 * Unit: DFI clock cycles.
 * Programming Mode: Dynamic - Refresh Related
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_RFSHTMG . T_RFC_MIN
 */
#define  VTSS_F_DDR_UMCTL2_RFSHTMG_T_RFC_MIN(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_DDR_UMCTL2_RFSHTMG_T_RFC_MIN     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_DDR_UMCTL2_RFSHTMG_T_RFC_MIN(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * \brief
 * Average time interval between refreshes per rank (Specification: 7.8us
 * for DDR2, DDR3 and DDR4. See JEDEC specification for mDDR, LPDDR2,
 * LPDDR3 and LPDDR4).
 * When the controller is operating in 1:1 mode, set this register to
 * RoundDown(tREFI/tCK)
 * When the controller is operating in 1:2 mode, set this register to
 * RoundDown(RoundDown(tREFI/tCK)/2)
 * In both the previous cases, if RFSHTMG.t_rfc_nom_x1_sel = 0, divide the
 * previous result by 32 and round down.
 * For LPDDR2/LPDDR3/LPDDR4:
 *  - If using all-bank refreshes (RFSHCTL0.per_bank_refresh = 0), use
 * tREFIab in the previous calculations
 *  - If using per-bank refreshes (RFSHCTL0.per_bank_refresh = 1), use
 * tREFIpb in the previous calculations
 * For DDR4 mode, tREFI value is different depending on the refresh mode.
 * You must program appropriate value from the spec based on the value
 * programmed in the refresh mode register.
 * Note:
 *  - RFSHTMG.t_rfc_nom_x1_x32 must be greater than 0x1
 *  - If RFSHTMG.t_rfc_nom_x1_sel == 1, RFSHTMG.t_rfc_nom_x1_x32 must be
 * greater than RFSHTMG.t_rfc_min
 *  - If RFSHTMG.t_rfc_nom_x1_sel == 0, RFSHTMG.t_rfc_nom_x1_x32 * 32 must
 * be greater than RFSHTMG.t_rfc_min
 *  - In non-DDR4 or DDR4 Fixed 1x mode: RFSHTMG.t_rfc_nom_x1_x32 must be
 * less than or equal to 0xFFE
 *  - In DDR4 Fixed 2x mode: RFSHTMG.t_rfc_nom_x1_x32 must be less than or
 * equal to 0x7FF
 *  - In DDR4 Fixed 4x mode: RFSHTMG.t_rfc_nom_x1_x32 must be less than or
 * equal to 0x3FF
 * Unit: DFI clock cycles or multiples of 32 DFI clock cycles, depending on
 * RFSHTMG.t_rfc_nom_x1_sel.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Dynamic - Refresh Related
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_RFSHTMG . T_RFC_NOM_X1_X32
 */
#define  VTSS_F_DDR_UMCTL2_RFSHTMG_T_RFC_NOM_X1_X32(x)  VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_DDR_UMCTL2_RFSHTMG_T_RFC_NOM_X1_X32     VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_DDR_UMCTL2_RFSHTMG_T_RFC_NOM_X1_X32(x)  VTSS_EXTRACT_BITFIELD(x,16,12)


/**
 * \brief ECC Configuration Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCCFG0
 */
#define VTSS_DDR_UMCTL2_ECCCFG0              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x1c)

/**
 * \brief
 * ECC mode indicator.
 * Everything not described in "Values" section is reserved.
 * Programming Mode: Static
 *
 * \details
 * 'h5:
 * 'h0:
 * 'h4:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCFG0 . ECC_MODE
 */
#define  VTSS_F_DDR_UMCTL2_ECCCFG0_ECC_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_DDR_UMCTL2_ECCCFG0_ECC_MODE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_DDR_UMCTL2_ECCCFG0_ECC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Disables ECC scrubs.
 * Valid only when ECCCFG0.ecc_mode = 3'b100 or 3'b101 and MEMC_USE_RMW is
 * defined.
 * Note: Scrub is not supported in inline ECC mode and the register value
 * is don't care.
 *
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCFG0 . DIS_SCRUB
 */
#define  VTSS_F_DDR_UMCTL2_ECCCFG0_DIS_SCRUB(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_ECCCFG0_DIS_SCRUB  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_ECCCFG0_DIS_SCRUB(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enables address protection feature.
 * Only supported when inline ECC is enabled.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCFG0 . ECC_AP_EN
 */
#define  VTSS_F_DDR_UMCTL2_ECCCFG0_ECC_AP_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DDR_UMCTL2_ECCCFG0_ECC_AP_EN  VTSS_BIT(6)
#define  VTSS_X_DDR_UMCTL2_ECCCFG0_ECC_AP_EN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Enables remapping ECC region feature.
 * Only supported when inline ECC is enabled.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCFG0 . ECC_REGION_REMAP_EN
 */
#define  VTSS_F_DDR_UMCTL2_ECCCFG0_ECC_REGION_REMAP_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DDR_UMCTL2_ECCCFG0_ECC_REGION_REMAP_EN  VTSS_BIT(7)
#define  VTSS_X_DDR_UMCTL2_ECCCFG0_ECC_REGION_REMAP_EN(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Selectable Protected Region setting.
 * Memory space is divided to 8/16/32/64 regions which is determined by
 * ECCCFG0.ecc_region_map_granu.
 * Note: Highest 1/8 memory space is always ECC region.
 * Lowest 7 regions are Selectable Protected Regions. The Selectable
 * Protected Regions can be protected/non-protected selectively by
 * ECCCFG0.ecc_region_map[6:0]. Other upper regions are non-protected
 * region if any. Each bit of ECCCFG0.ecc_region_map[6:0] correspond to
 * each of lowest 7 regions respectively.
 * In order to protect a region with ECC, set the corresponding bit to 1,
 * otherwise set to 0. All "0"s is invalid - there must be at least one
 * protected region if inline ECC is enabled through ECCCFG0.ecc_mode
 * register.
 * All regions are protected with the following setting.
 *  - ecc_region_map=7'b1111111
 *  - ecc_region_map_granu=0
 * Only first 1/64 region is protected with the following setting.
 *  - ecc_region_map=7'b0000001
 *  - ecc_region_map_granu=3
 *
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCCFG0 . ECC_REGION_MAP
 */
#define  VTSS_F_DDR_UMCTL2_ECCCFG0_ECC_REGION_MAP(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_DDR_UMCTL2_ECCCFG0_ECC_REGION_MAP     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_DDR_UMCTL2_ECCCFG0_ECC_REGION_MAP(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/**
 * \brief
 * Indicates the number of cycles on HIF interface with no access to
 * protected regions which causes flush of all the block channels.
 * In order to flush block channel, uMCTL2 injects write ECC command (when
 * there is no incoming HIF command) if there is any write in the block and
 * then stop tracking the block address.
 *  - 0 - Indicates no timeout (feature is disabled, not supported with
 * this version)
 *  - 1 - Indicates 32 cycles
 *  - 2 - Indicates 2*32 cycles, and so on
 *  Unit: Multiples of 32 DFI clock cycles.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCCFG0 . BLK_CHANNEL_IDLE_TIME_X32
 */
#define  VTSS_F_DDR_UMCTL2_ECCCFG0_BLK_CHANNEL_IDLE_TIME_X32(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_DDR_UMCTL2_ECCCFG0_BLK_CHANNEL_IDLE_TIME_X32     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_DDR_UMCTL2_ECCCFG0_BLK_CHANNEL_IDLE_TIME_X32(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * Sets threshold for address parity error.
 * ECCAPSTAT.ecc_ap_err is asserted if number of ECC errors
 * (correctable/uncorrectable) within one burst exceeds this threshold.
 * This register value must be less than "Total number of ECC checks within
 * one burst" when this feature is used,
 * "Total number of ECC check within one burst" is calculated by (DRAM Data
 * width) x (DRAM BL) / 64.
 *
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCCFG0 . ECC_AP_ERR_THRESHOLD
 */
#define  VTSS_F_DDR_UMCTL2_ECCCFG0_ECC_AP_ERR_THRESHOLD(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_DDR_UMCTL2_ECCCFG0_ECC_AP_ERR_THRESHOLD  VTSS_BIT(24)
#define  VTSS_X_DDR_UMCTL2_ECCCFG0_ECC_AP_ERR_THRESHOLD(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * When ECCCFG0.ecc_region_map_granu>0, there is a region which is not
 * controlled by ecc_region_map.
 * This register defines the region to be protected or non-protected for
 * Inline ECC.
 *
 *   This register is valid only when ECCCFG0.ecc_region_map_granu>0 &&
 * ECCCFG0.ecc_mode=4.
 *
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCFG0 . ECC_REGION_MAP_OTHER
 */
#define  VTSS_F_DDR_UMCTL2_ECCCFG0_ECC_REGION_MAP_OTHER(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_DDR_UMCTL2_ECCCFG0_ECC_REGION_MAP_OTHER  VTSS_BIT(29)
#define  VTSS_X_DDR_UMCTL2_ECCCFG0_ECC_REGION_MAP_OTHER(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Indicates granularity of selectable protected region.
 * Define one region size for ECCCFG0.ecc_region_map.
 * Programming Mode: Static
 *
 * \details
 * 'h1:
 * 'h0:
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCFG0 . ECC_REGION_MAP_GRANU
 */
#define  VTSS_F_DDR_UMCTL2_ECCCFG0_ECC_REGION_MAP_GRANU(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_DDR_UMCTL2_ECCCFG0_ECC_REGION_MAP_GRANU     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_DDR_UMCTL2_ECCCFG0_ECC_REGION_MAP_GRANU(x)  VTSS_EXTRACT_BITFIELD(x,30,2)


/**
 * \brief ECC Configuration Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCCFG1
 */
#define VTSS_DDR_UMCTL2_ECCCFG1              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x1d)

/**
 * \brief
 * Enables ECC data poisoning - introduces ECC errors on writes to address
 * specified by the ECCPOISONADDR0/1 registers.
 * This field must be set to 0 if ECC is disabled (ECCCFG0.ecc_mode = 0).
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCFG1 . DATA_POISON_EN
 */
#define  VTSS_F_DDR_UMCTL2_ECCCFG1_DATA_POISON_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_ECCCFG1_DATA_POISON_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_ECCCFG1_DATA_POISON_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Selects whether to poison 1 or 2 bits.
 *   Valid only when MEMC_ECC_SUPPORT==1 (SECDED ECC mode)
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCFG1 . DATA_POISON_BIT
 */
#define  VTSS_F_DDR_UMCTL2_ECCCFG1_DATA_POISON_BIT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_ECCCFG1_DATA_POISON_BIT  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_ECCCFG1_DATA_POISON_BIT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Locks the parity section of the ECC region (hole) which is the highest
 * system address part of the memory that stores ECC parity for protected
 * region.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCFG1 . ECC_REGION_PARITY_LOCK
 */
#define  VTSS_F_DDR_UMCTL2_ECCCFG1_ECC_REGION_PARITY_LOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_ECCCFG1_ECC_REGION_PARITY_LOCK  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_ECCCFG1_ECC_REGION_PARITY_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Locks the remaining waste parts of the ECC region (hole) that are not
 * locked by ecc_region_parity_lock.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCFG1 . ECC_REGION_WASTE_LOCK
 */
#define  VTSS_F_DDR_UMCTL2_ECCCFG1_ECC_REGION_WASTE_LOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_UMCTL2_ECCCFG1_ECC_REGION_WASTE_LOCK  VTSS_BIT(5)
#define  VTSS_X_DDR_UMCTL2_ECCCFG1_ECC_REGION_WASTE_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * If enabled, block channel is terminated when full block write or full
 * block read is performed (all address within block are written or read).
 *   This is debug register, and this must be set to 1 for normal
 * operation.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCFG1 . BLK_CHANNEL_ACTIVE_TERM
 */
#define  VTSS_F_DDR_UMCTL2_ECCCFG1_BLK_CHANNEL_ACTIVE_TERM(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DDR_UMCTL2_ECCCFG1_BLK_CHANNEL_ACTIVE_TERM  VTSS_BIT(7)
#define  VTSS_X_DDR_UMCTL2_ECCCFG1_BLK_CHANNEL_ACTIVE_TERM(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Indicated the number of active block channels.
 * Total number of ECC block channels are defined by MEMC_NO_OF_BLK_CHANNEL
 * hardware parameter.
 * This register can limit the number of available channels.
 * For example, if set to 0, only one channel is active and therefore block
 * interleaving is disabled.
 * The valid range is from 0 to MEMC_NO_OF_BLK_CHANNEL-1.
 *
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCCFG1 . ACTIVE_BLK_CHANNEL
 */
#define  VTSS_F_DDR_UMCTL2_ECCCFG1_ACTIVE_BLK_CHANNEL(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_DDR_UMCTL2_ECCCFG1_ACTIVE_BLK_CHANNEL     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_DDR_UMCTL2_ECCCFG1_ACTIVE_BLK_CHANNEL(x)  VTSS_EXTRACT_BITFIELD(x,8,5)


/**
 * \brief SECDED ECC Status Register (Valid only in MEMC_ECC_SUPPORT==1 (SECDED ECC mode))
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCSTAT
 */
#define VTSS_DDR_UMCTL2_ECCSTAT              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x1e)

/**
 * \brief
 * Indicates the bit number corrected by single-bit ECC error.
 * For encoding of this field, see ECC section in the Architecture chapter.
 * If more than one data lane has an error, the lower data lane is
 * selected.
 * This register is 7 bits wide in order to handle 72 bits of the data
 * present in a single lane.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCSTAT . ECC_CORRECTED_BIT_NUM
 */
#define  VTSS_F_DDR_UMCTL2_ECCSTAT_ECC_CORRECTED_BIT_NUM(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_DDR_UMCTL2_ECCSTAT_ECC_CORRECTED_BIT_NUM     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_DDR_UMCTL2_ECCSTAT_ECC_CORRECTED_BIT_NUM(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/**
 * \brief
 * Single-bit error indicator.
 * In sideband ECC mode, 1 bit per ECC lane. When the controller is
 * operating in 1:1 frequency ratio mode, there are only two lanes, so only
 * the lower two bits are used.
 * In inline ECC mode, the register is always 1 bit to indicate correctable
 * error on any lane.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCSTAT . ECC_CORRECTED_ERR
 */
#define  VTSS_F_DDR_UMCTL2_ECCSTAT_ECC_CORRECTED_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DDR_UMCTL2_ECCSTAT_ECC_CORRECTED_ERR  VTSS_BIT(8)
#define  VTSS_X_DDR_UMCTL2_ECCSTAT_ECC_CORRECTED_ERR(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Double-bit error indicator.
 * In sideband ECC mode, 1 bit per ECC lane. When the controller is
 * operating in 1:1 frequency ratio mode, there are only two lanes, so only
 * the lower two bits are used.
 * In inline ECC mode, the register is always 1 bit to indicate
 * uncorrectable error on any lane.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCSTAT . ECC_UNCORRECTED_ERR
 */
#define  VTSS_F_DDR_UMCTL2_ECCSTAT_ECC_UNCORRECTED_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DDR_UMCTL2_ECCSTAT_ECC_UNCORRECTED_ERR  VTSS_BIT(16)
#define  VTSS_X_DDR_UMCTL2_ECCSTAT_ECC_UNCORRECTED_ERR(x)  VTSS_EXTRACT_BITFIELD(x,16,1)


/**
 * \brief ECC Clear Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCCTL
 */
#define VTSS_DDR_UMCTL2_ECCCTL               VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x1f)

/**
 * \brief
 * Setting this register bit to 1 clears the currently stored corrected ECC
 * error. uMCTL2 automatically clears this bit.
 * The following registers are cleared:
 *  - ECCSTAT.ecc_corrected_err
 *  - ADVECCSTAT.advecc_corrected_err
 *  - ADVECCSTAT.advecc_num_err_symbol
 *  - ADVECCSTAT.advecc_err_symbol_pos
 *  - ADVECCSTAT.advecc_err_symbol_bits
 *  - ECCCSYN0
 *  - ECCCSYN1
 *  - ECCCSYN2
 *  - ECCBITMASK0
 *  - ECCBITMASK1
 *  - ECCBITMASK2
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCTL . ECC_CORRECTED_ERR_CLR
 */
#define  VTSS_F_DDR_UMCTL2_ECCCTL_ECC_CORRECTED_ERR_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_ECCCTL_ECC_CORRECTED_ERR_CLR  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_ECCCTL_ECC_CORRECTED_ERR_CLR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Setting this register bit to 1 clears the currently stored uncorrected
 * ECC error. uMCTL2 automatically clears this bit.
 * The following registers are cleared:
 *  - ECCSTAT.ecc_uncorrected_err
 *  - ADVECCSTAT.advecc_uncorrected_err
 *  - ECCUSYN0
 *  - ECCUSYN1
 *  - ECCUSYN2
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCTL . ECC_UNCORRECTED_ERR_CLR
 */
#define  VTSS_F_DDR_UMCTL2_ECCCTL_ECC_UNCORRECTED_ERR_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_ECCCTL_ECC_UNCORRECTED_ERR_CLR  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_ECCCTL_ECC_UNCORRECTED_ERR_CLR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Clears the currently stored corrected ECC error count. The uMCTL2
 * automatically clears this bit.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCTL . ECC_CORR_ERR_CNT_CLR
 */
#define  VTSS_F_DDR_UMCTL2_ECCCTL_ECC_CORR_ERR_CNT_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_UMCTL2_ECCCTL_ECC_CORR_ERR_CNT_CLR  VTSS_BIT(2)
#define  VTSS_X_DDR_UMCTL2_ECCCTL_ECC_CORR_ERR_CNT_CLR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Clears currently stored uncorrected ECC error count. The uMCTL2
 * automatically clears this bit.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCTL . ECC_UNCORR_ERR_CNT_CLR
 */
#define  VTSS_F_DDR_UMCTL2_ECCCTL_ECC_UNCORR_ERR_CNT_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_UMCTL2_ECCCTL_ECC_UNCORR_ERR_CNT_CLR  VTSS_BIT(3)
#define  VTSS_X_DDR_UMCTL2_ECCCTL_ECC_UNCORR_ERR_CNT_CLR(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Interrupt clear bit for ecc_ap_err. The uMCTL2 automatically clears this
 * bit.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCTL . ECC_AP_ERR_INTR_CLR
 */
#define  VTSS_F_DDR_UMCTL2_ECCCTL_ECC_AP_ERR_INTR_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_ECCCTL_ECC_AP_ERR_INTR_CLR  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_ECCCTL_ECC_AP_ERR_INTR_CLR(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Interrupt enable bit for ecc_corrected_err_intr.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCTL . ECC_CORRECTED_ERR_INTR_EN
 */
#define  VTSS_F_DDR_UMCTL2_ECCCTL_ECC_CORRECTED_ERR_INTR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DDR_UMCTL2_ECCCTL_ECC_CORRECTED_ERR_INTR_EN  VTSS_BIT(8)
#define  VTSS_X_DDR_UMCTL2_ECCCTL_ECC_CORRECTED_ERR_INTR_EN(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Interrupt enable bit for ecc_uncorrected_err_intr.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCTL . ECC_UNCORRECTED_ERR_INTR_EN
 */
#define  VTSS_F_DDR_UMCTL2_ECCCTL_ECC_UNCORRECTED_ERR_INTR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_DDR_UMCTL2_ECCCTL_ECC_UNCORRECTED_ERR_INTR_EN  VTSS_BIT(9)
#define  VTSS_X_DDR_UMCTL2_ECCCTL_ECC_UNCORRECTED_ERR_INTR_EN(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Interrupt enable bit for ecc_ap_err_intr.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCTL . ECC_AP_ERR_INTR_EN
 */
#define  VTSS_F_DDR_UMCTL2_ECCCTL_ECC_AP_ERR_INTR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_DDR_UMCTL2_ECCCTL_ECC_AP_ERR_INTR_EN  VTSS_BIT(10)
#define  VTSS_X_DDR_UMCTL2_ECCCTL_ECC_AP_ERR_INTR_EN(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Interrupt force bit for ecc_corrected_err_intr.
 * There is no interaction between functionally triggering an interrupt and
 * forcing an interrupt (they are mutually exclusive).
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCTL . ECC_CORRECTED_ERR_INTR_FORCE
 */
#define  VTSS_F_DDR_UMCTL2_ECCCTL_ECC_CORRECTED_ERR_INTR_FORCE(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DDR_UMCTL2_ECCCTL_ECC_CORRECTED_ERR_INTR_FORCE  VTSS_BIT(16)
#define  VTSS_X_DDR_UMCTL2_ECCCTL_ECC_CORRECTED_ERR_INTR_FORCE(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Interrupt force bit for ecc_uncorrected_err_intr.
 * There is no interaction between functionally triggering an interrupt and
 * forcing an interrupt (they are mutually exclusive).
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCTL . ECC_UNCORRECTED_ERR_INTR_FORCE
 */
#define  VTSS_F_DDR_UMCTL2_ECCCTL_ECC_UNCORRECTED_ERR_INTR_FORCE(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_DDR_UMCTL2_ECCCTL_ECC_UNCORRECTED_ERR_INTR_FORCE  VTSS_BIT(17)
#define  VTSS_X_DDR_UMCTL2_ECCCTL_ECC_UNCORRECTED_ERR_INTR_FORCE(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Interrupt force bit for ecc_ap_err_intr.
 * There is no interaction between functionally triggering an interrupt and
 * forcing an interrupt (they are mutually exclusive).
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCCTL . ECC_AP_ERR_INTR_FORCE
 */
#define  VTSS_F_DDR_UMCTL2_ECCCTL_ECC_AP_ERR_INTR_FORCE(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_DDR_UMCTL2_ECCCTL_ECC_AP_ERR_INTR_FORCE  VTSS_BIT(18)
#define  VTSS_X_DDR_UMCTL2_ECCCTL_ECC_AP_ERR_INTR_FORCE(x)  VTSS_EXTRACT_BITFIELD(x,18,1)


/**
 * \brief ECC Error Counter Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCERRCNT
 */
#define VTSS_DDR_UMCTL2_ECCERRCNT            VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x20)

/**
 * \brief
 * Indicates the number of correctable ECC errors detected.
 * Note that the saturation behavior of this register is different,
 * depending on the type of ECC.
 * For advanced ECC or Inline ECC, it saturates at 0xFFFF, while for
 * Side-band ECC with SECDED ECC, it saturates at 0xFFFC or above.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCERRCNT . ECC_CORR_ERR_CNT
 */
#define  VTSS_F_DDR_UMCTL2_ECCERRCNT_ECC_CORR_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_UMCTL2_ECCERRCNT_ECC_CORR_ERR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_UMCTL2_ECCERRCNT_ECC_CORR_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Indicates the number of uncorrectable ECC errors detected.
 * Note that the saturation behavior of this register is different,
 * depending on the type of ECC.
 * For advanced ECC or Inline ECC, it saturates at 0xFFFF, while for
 * Side-band ECC with SECDED ECC, it saturates at 0xFFFC or above.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCERRCNT . ECC_UNCORR_ERR_CNT
 */
#define  VTSS_F_DDR_UMCTL2_ECCERRCNT_ECC_UNCORR_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DDR_UMCTL2_ECCERRCNT_ECC_UNCORR_ERR_CNT     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DDR_UMCTL2_ECCERRCNT_ECC_UNCORR_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief ECC Corrected Error Address Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCCADDR0
 */
#define VTSS_DDR_UMCTL2_ECCCADDR0            VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x21)

/**
 * \brief
 * Indicates the page/row number of a read resulting in a corrected ECC
 * error.
 * This is 18-bits wide in configurations with DDR4 support and 16-bits in
 * all other configurations.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCCADDR0 . ECC_CORR_ROW
 */
#define  VTSS_F_DDR_UMCTL2_ECCCADDR0_ECC_CORR_ROW(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_DDR_UMCTL2_ECCCADDR0_ECC_CORR_ROW     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_DDR_UMCTL2_ECCCADDR0_ECC_CORR_ROW(x)  VTSS_EXTRACT_BITFIELD(x,0,18)

/**
 * \brief
 * Indicates the rank number of a read resulting in a corrected ECC error.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCCADDR0 . ECC_CORR_RANK
 */
#define  VTSS_F_DDR_UMCTL2_ECCCADDR0_ECC_CORR_RANK(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_DDR_UMCTL2_ECCCADDR0_ECC_CORR_RANK  VTSS_BIT(24)
#define  VTSS_X_DDR_UMCTL2_ECCCADDR0_ECC_CORR_RANK(x)  VTSS_EXTRACT_BITFIELD(x,24,1)


/**
 * \brief ECC Corrected Error Address Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCCADDR1
 */
#define VTSS_DDR_UMCTL2_ECCCADDR1            VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x22)

/**
 * \brief
 * Indicates the block number of a read resulting in a corrected ECC error
 * (lowest bit not assigned here).
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCCADDR1 . ECC_CORR_COL
 */
#define  VTSS_F_DDR_UMCTL2_ECCCADDR1_ECC_CORR_COL(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_UMCTL2_ECCCADDR1_ECC_CORR_COL     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_UMCTL2_ECCCADDR1_ECC_CORR_COL(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Indicates the bank number of a read resulting in a corrected ECC error.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCCADDR1 . ECC_CORR_BANK
 */
#define  VTSS_F_DDR_UMCTL2_ECCCADDR1_ECC_CORR_BANK(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_DDR_UMCTL2_ECCCADDR1_ECC_CORR_BANK     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_DDR_UMCTL2_ECCCADDR1_ECC_CORR_BANK(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * Indicates the bank group number of a read resulting in a corrected ECC
 * error.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCCADDR1 . ECC_CORR_BG
 */
#define  VTSS_F_DDR_UMCTL2_ECCCADDR1_ECC_CORR_BG(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_DDR_UMCTL2_ECCCADDR1_ECC_CORR_BG     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_DDR_UMCTL2_ECCCADDR1_ECC_CORR_BG(x)  VTSS_EXTRACT_BITFIELD(x,24,2)


/**
 * \brief ECC Corrected Syndrome Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCCSYN0
 */
#define VTSS_DDR_UMCTL2_ECCCSYN0             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x23)

/**
 * \brief
 * Indicates the data pattern that resulted in a corrected error.
 * For 16-bit ECC, only bits [15:0] are used.
 * This field can be masked by setting the dis_regs_ecc_syndrome input to
 * value 1.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCCSYN0 . ECC_CORR_SYNDROMES_31_0
 */
#define  VTSS_F_DDR_UMCTL2_ECCCSYN0_ECC_CORR_SYNDROMES_31_0(x)  (x)
#define  VTSS_M_DDR_UMCTL2_ECCCSYN0_ECC_CORR_SYNDROMES_31_0     0xffffffff
#define  VTSS_X_DDR_UMCTL2_ECCCSYN0_ECC_CORR_SYNDROMES_31_0(x)  (x)


/**
 * \brief ECC Corrected Syndrome Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCCSYN1
 */
#define VTSS_DDR_UMCTL2_ECCCSYN1             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x24)

/**
 * \brief
 * Indicates the data pattern that resulted in a corrected error.
 * For 32-bit ECC and 16-bit ECC, this register is not used.
 * This field can be masked by setting the dis_regs_ecc_syndrome input to
 * value 1.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCCSYN1 . ECC_CORR_SYNDROMES_63_32
 */
#define  VTSS_F_DDR_UMCTL2_ECCCSYN1_ECC_CORR_SYNDROMES_63_32(x)  (x)
#define  VTSS_M_DDR_UMCTL2_ECCCSYN1_ECC_CORR_SYNDROMES_63_32     0xffffffff
#define  VTSS_X_DDR_UMCTL2_ECCCSYN1_ECC_CORR_SYNDROMES_63_32(x)  (x)


/**
 * \brief ECC Corrected Syndrome Register 2
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCCSYN2
 */
#define VTSS_DDR_UMCTL2_ECCCSYN2             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x25)

/**
 * \brief
 * Indicates the data pattern that resulted in a corrected error one for
 * each ECC lane, all concatenated together.
 * This register refers to the ECC byte, which is bits [71:64] for 64-bit
 * ECC, [39:32] for 32-bit ECC, or [23:16] for 16-bit ECC.
 * This field can be masked by setting the dis_regs_ecc_syndrome input to
 * value 1.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCCSYN2 . ECC_CORR_SYNDROMES_71_64
 */
#define  VTSS_F_DDR_UMCTL2_ECCCSYN2_ECC_CORR_SYNDROMES_71_64(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_UMCTL2_ECCCSYN2_ECC_CORR_SYNDROMES_71_64     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_UMCTL2_ECCCSYN2_ECC_CORR_SYNDROMES_71_64(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief ECC Corrected Data Bit Mask Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCBITMASK0
 */
#define VTSS_DDR_UMCTL2_ECCBITMASK0          VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x26)

/**
 * \brief
 * Indicates the mask for the corrected data portion.
 *  - 1 on any bit indicates that the bit has been corrected by the ECC
 * logic
 *  - 0 on any bit indicates that the bit has not been corrected by the ECC
 * logic
 * This register accumulates data over multiple ECC errors, to give an
 * overall indication of which bits are being fixed.
 * It is cleared by writing a 1 to ECCCTL.ecc_corrected_err_clr.
 * For 16-bit ECC, only bits [15:0] are used.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCBITMASK0 . ECC_CORR_BIT_MASK_31_0
 */
#define  VTSS_F_DDR_UMCTL2_ECCBITMASK0_ECC_CORR_BIT_MASK_31_0(x)  (x)
#define  VTSS_M_DDR_UMCTL2_ECCBITMASK0_ECC_CORR_BIT_MASK_31_0     0xffffffff
#define  VTSS_X_DDR_UMCTL2_ECCBITMASK0_ECC_CORR_BIT_MASK_31_0(x)  (x)


/**
 * \brief ECC Corrected Data Bit Mask Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCBITMASK1
 */
#define VTSS_DDR_UMCTL2_ECCBITMASK1          VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x27)

/**
 * \brief
 * Indicates the mask for the corrected data portion.
 *  - 1 on any bit indicates that the bit has been corrected by the ECC
 * logic
 *  - 0 on any bit indicates that the bit has not been corrected by the ECC
 * logic
 * This register accumulates data over multiple ECC errors, to give an
 * overall indication of which bits are being fixed.
 * It is cleared by writing a 1 to ECCCTL.ecc_corrected_err_clr.
 * For 32-bit ECC and 16-bit ECC, this register is not used.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCBITMASK1 . ECC_CORR_BIT_MASK_63_32
 */
#define  VTSS_F_DDR_UMCTL2_ECCBITMASK1_ECC_CORR_BIT_MASK_63_32(x)  (x)
#define  VTSS_M_DDR_UMCTL2_ECCBITMASK1_ECC_CORR_BIT_MASK_63_32     0xffffffff
#define  VTSS_X_DDR_UMCTL2_ECCBITMASK1_ECC_CORR_BIT_MASK_63_32(x)  (x)


/**
 * \brief ECC Corrected Data Bit Mask Register 2
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCBITMASK2
 */
#define VTSS_DDR_UMCTL2_ECCBITMASK2          VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x28)

/**
 * \brief
 * Indicates the mask for the corrected data portion.
 *  - 1 on any bit indicates that the bit has been corrected by the ECC
 * logic
 *  - 0 on any bit indicates that the bit has not been corrected by the ECC
 * logic
 * This register accumulates data over multiple ECC errors, to give an
 * overall indication of which bits are being fixed.
 * It is cleared by writing a 1 to ECCCTL.ecc_corrected_err_clr.
 * This register refers to the ECC byte, which is bits [71:64] for 64-bit
 * ECC, [39:32] for 32-bit ECC, or [23:16] for 16-bit ECC.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCBITMASK2 . ECC_CORR_BIT_MASK_71_64
 */
#define  VTSS_F_DDR_UMCTL2_ECCBITMASK2_ECC_CORR_BIT_MASK_71_64(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_UMCTL2_ECCBITMASK2_ECC_CORR_BIT_MASK_71_64     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_UMCTL2_ECCBITMASK2_ECC_CORR_BIT_MASK_71_64(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief ECC Uncorrected Error Address Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCUADDR0
 */
#define VTSS_DDR_UMCTL2_ECCUADDR0            VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x29)

/**
 * \brief
 * Indicates the page/row number of a read resulting in an uncorrected ECC
 * error.
 * This is 18-bits wide in configurations with DDR4 support and 16-bits in
 * all other configurations.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCUADDR0 . ECC_UNCORR_ROW
 */
#define  VTSS_F_DDR_UMCTL2_ECCUADDR0_ECC_UNCORR_ROW(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_DDR_UMCTL2_ECCUADDR0_ECC_UNCORR_ROW     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_DDR_UMCTL2_ECCUADDR0_ECC_UNCORR_ROW(x)  VTSS_EXTRACT_BITFIELD(x,0,18)

/**
 * \brief
 * Indicates the rank number of a read resulting in an uncorrected ECC
 * error.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCUADDR0 . ECC_UNCORR_RANK
 */
#define  VTSS_F_DDR_UMCTL2_ECCUADDR0_ECC_UNCORR_RANK(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_DDR_UMCTL2_ECCUADDR0_ECC_UNCORR_RANK  VTSS_BIT(24)
#define  VTSS_X_DDR_UMCTL2_ECCUADDR0_ECC_UNCORR_RANK(x)  VTSS_EXTRACT_BITFIELD(x,24,1)


/**
 * \brief ECC Uncorrected Error Address Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCUADDR1
 */
#define VTSS_DDR_UMCTL2_ECCUADDR1            VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x2a)

/**
 * \brief
 * Indicates the block number of a read resulting in an uncorrected ECC
 * error (lowest bit not assigned here).
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCUADDR1 . ECC_UNCORR_COL
 */
#define  VTSS_F_DDR_UMCTL2_ECCUADDR1_ECC_UNCORR_COL(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_UMCTL2_ECCUADDR1_ECC_UNCORR_COL     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_UMCTL2_ECCUADDR1_ECC_UNCORR_COL(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Indicates the bank number of a read resulting in an uncorrected ECC
 * error.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCUADDR1 . ECC_UNCORR_BANK
 */
#define  VTSS_F_DDR_UMCTL2_ECCUADDR1_ECC_UNCORR_BANK(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_DDR_UMCTL2_ECCUADDR1_ECC_UNCORR_BANK     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_DDR_UMCTL2_ECCUADDR1_ECC_UNCORR_BANK(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * Indicates the bank group number of a read resulting in an uncorrected
 * ECC error.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCUADDR1 . ECC_UNCORR_BG
 */
#define  VTSS_F_DDR_UMCTL2_ECCUADDR1_ECC_UNCORR_BG(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_DDR_UMCTL2_ECCUADDR1_ECC_UNCORR_BG     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_DDR_UMCTL2_ECCUADDR1_ECC_UNCORR_BG(x)  VTSS_EXTRACT_BITFIELD(x,24,2)


/**
 * \brief ECC Uncorrected Syndrome Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCUSYN0
 */
#define VTSS_DDR_UMCTL2_ECCUSYN0             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x2b)

/**
 * \brief
 * Indicates the data pattern that resulted in an uncorrected error, one
 * for each ECC lane, all concatenated together.
 * For 16-bit ECC, only bits [15:0] are used.
 * This field can be masked by setting the dis_regs_ecc_syndrome input to
 * value 1.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCUSYN0 . ECC_UNCORR_SYNDROMES_31_0
 */
#define  VTSS_F_DDR_UMCTL2_ECCUSYN0_ECC_UNCORR_SYNDROMES_31_0(x)  (x)
#define  VTSS_M_DDR_UMCTL2_ECCUSYN0_ECC_UNCORR_SYNDROMES_31_0     0xffffffff
#define  VTSS_X_DDR_UMCTL2_ECCUSYN0_ECC_UNCORR_SYNDROMES_31_0(x)  (x)


/**
 * \brief ECC Uncorrected Syndrome Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCUSYN1
 */
#define VTSS_DDR_UMCTL2_ECCUSYN1             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x2c)

/**
 * \brief
 * Indicates the data pattern that resulted in an uncorrected error, one
 * for each ECC lane, all concatenated together.
 * For 32-bit ECC and 16-bit ECC, this register is not used.
 * This field can be masked by setting the dis_regs_ecc_syndrome input to
 * value 1.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCUSYN1 . ECC_UNCORR_SYNDROMES_63_32
 */
#define  VTSS_F_DDR_UMCTL2_ECCUSYN1_ECC_UNCORR_SYNDROMES_63_32(x)  (x)
#define  VTSS_M_DDR_UMCTL2_ECCUSYN1_ECC_UNCORR_SYNDROMES_63_32     0xffffffff
#define  VTSS_X_DDR_UMCTL2_ECCUSYN1_ECC_UNCORR_SYNDROMES_63_32(x)  (x)


/**
 * \brief ECC Uncorrected Syndrome Register 2
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCUSYN2
 */
#define VTSS_DDR_UMCTL2_ECCUSYN2             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x2d)

/**
 * \brief
 * Indicates the data pattern that resulted in an uncorrected error one for
 * each ECC lane, all concatenated together.
 * This register refers to the ECC byte, which is bits [71:64] for 64-bit
 * ECC, [39:32] for 32-bit ECC, or [23:16] for 16-bit ECC.
 * This field can be masked by setting the dis_regs_ecc_syndrome input to
 * value 1.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCUSYN2 . ECC_UNCORR_SYNDROMES_71_64
 */
#define  VTSS_F_DDR_UMCTL2_ECCUSYN2_ECC_UNCORR_SYNDROMES_71_64(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_UMCTL2_ECCUSYN2_ECC_UNCORR_SYNDROMES_71_64     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_UMCTL2_ECCUSYN2_ECC_UNCORR_SYNDROMES_71_64(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief ECC Data Poisoning Address Register 0. If a HIF write data beat matches the address specified in this register, an ECC error is introduced on that transaction (write/RMW), if ECCCFG1.data_poison_en=1.
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCPOISONADDR0
 */
#define VTSS_DDR_UMCTL2_ECCPOISONADDR0       VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x2e)

/**
 * \brief
 * Indicates the column address for ECC poisoning.
 * Note that this column address must be burst aligned:
 * - In full bus width mode, ecc_poison_col[2:0] must be set to 0
 * - In half bus width mode, ecc_poison_col[3:0] must be set to 0
 * - In quarter bus width mode, ecc_poison_col[4:0] must be set to 0
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCPOISONADDR0 . ECC_POISON_COL
 */
#define  VTSS_F_DDR_UMCTL2_ECCPOISONADDR0_ECC_POISON_COL(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_UMCTL2_ECCPOISONADDR0_ECC_POISON_COL     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_UMCTL2_ECCPOISONADDR0_ECC_POISON_COL(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Indicates the rank address for ECC poisoning.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCPOISONADDR0 . ECC_POISON_RANK
 */
#define  VTSS_F_DDR_UMCTL2_ECCPOISONADDR0_ECC_POISON_RANK(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_DDR_UMCTL2_ECCPOISONADDR0_ECC_POISON_RANK  VTSS_BIT(24)
#define  VTSS_X_DDR_UMCTL2_ECCPOISONADDR0_ECC_POISON_RANK(x)  VTSS_EXTRACT_BITFIELD(x,24,1)


/**
 * \brief ECC Data Poisoning Address Register 1. If a HIF write data beat matches the address specified in this register, an ECC error is introduced on that transaction (write/RMW), if ECCCFG1.data_poison_en=1.
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCPOISONADDR1
 */
#define VTSS_DDR_UMCTL2_ECCPOISONADDR1       VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x2f)

/**
 * \brief
 * Row address for ECC poisoning. This is 18-bits wide in configurations
 * with DDR4 support and 16-bits in all other configurations.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCPOISONADDR1 . ECC_POISON_ROW
 */
#define  VTSS_F_DDR_UMCTL2_ECCPOISONADDR1_ECC_POISON_ROW(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_DDR_UMCTL2_ECCPOISONADDR1_ECC_POISON_ROW     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_DDR_UMCTL2_ECCPOISONADDR1_ECC_POISON_ROW(x)  VTSS_EXTRACT_BITFIELD(x,0,18)

/**
 * \brief
 * Bank address for ECC poisoning.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h3:
 * 'h4:
 * 'h5:
 * 'h6:
 * 'h7:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCPOISONADDR1 . ECC_POISON_BANK
 */
#define  VTSS_F_DDR_UMCTL2_ECCPOISONADDR1_ECC_POISON_BANK(x)  VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_DDR_UMCTL2_ECCPOISONADDR1_ECC_POISON_BANK     VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_DDR_UMCTL2_ECCPOISONADDR1_ECC_POISON_BANK(x)  VTSS_EXTRACT_BITFIELD(x,24,3)

/**
 * \brief
 * Bank Group address for ECC poisoning.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h3:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCPOISONADDR1 . ECC_POISON_BG
 */
#define  VTSS_F_DDR_UMCTL2_ECCPOISONADDR1_ECC_POISON_BG(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_DDR_UMCTL2_ECCPOISONADDR1_ECC_POISON_BG     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_DDR_UMCTL2_ECCPOISONADDR1_ECC_POISON_BG(x)  VTSS_EXTRACT_BITFIELD(x,28,2)


/**
 * \brief CRC Parity Control Register 0.
Note: Do not perform any APB access to CRCPARCTL0 within 32 pclk cycles of previous access to CRCPARCTL0, as this might lead to data loss.
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:CRCPARCTL0
 */
#define VTSS_DDR_UMCTL2_CRCPARCTL0           VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x30)

/**
 * \brief
 * Interrupt enable bit for DFI alert error.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_CRCPARCTL0 . DFI_ALERT_ERR_INT_EN
 */
#define  VTSS_F_DDR_UMCTL2_CRCPARCTL0_DFI_ALERT_ERR_INT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_CRCPARCTL0_DFI_ALERT_ERR_INT_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_CRCPARCTL0_DFI_ALERT_ERR_INT_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Interrupt clear bit for DFI alert error. uMCTL2 automatically clears
 * this bit.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_CRCPARCTL0 . DFI_ALERT_ERR_INT_CLR
 */
#define  VTSS_F_DDR_UMCTL2_CRCPARCTL0_DFI_ALERT_ERR_INT_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_CRCPARCTL0_DFI_ALERT_ERR_INT_CLR  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_CRCPARCTL0_DFI_ALERT_ERR_INT_CLR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Indicates the clear bit for DFI alert error counter. uMCTL2
 * automatically clears this bit.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_CRCPARCTL0 . DFI_ALERT_ERR_CNT_CLR
 */
#define  VTSS_F_DDR_UMCTL2_CRCPARCTL0_DFI_ALERT_ERR_CNT_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_UMCTL2_CRCPARCTL0_DFI_ALERT_ERR_CNT_CLR  VTSS_BIT(2)
#define  VTSS_X_DDR_UMCTL2_CRCPARCTL0_DFI_ALERT_ERR_CNT_CLR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


/**
 * \brief CRC Parity Control Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:CRCPARCTL1
 */
#define VTSS_DDR_UMCTL2_CRCPARCTL1           VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x31)

/**
 * \brief
 * C/A Parity enable register.
 *
 *   If RCD's parity error detection or SDRAM's parity detection is
 * enabled, this register must be 1.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_CRCPARCTL1 . PARITY_ENABLE
 */
#define  VTSS_F_DDR_UMCTL2_CRCPARCTL1_PARITY_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_CRCPARCTL1_PARITY_ENABLE  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_CRCPARCTL1_PARITY_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * CRC enable Register.
 *
 *   The setting of this register must match the CRC mode register setting
 * in the DRAM.
 * Programming Mode: Quasi-dynamic Group 2
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_CRCPARCTL1 . CRC_ENABLE
 */
#define  VTSS_F_DDR_UMCTL2_CRCPARCTL1_CRC_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_CRCPARCTL1_CRC_ENABLE  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_CRCPARCTL1_CRC_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * CRC calculation setting register.
 *
 *   Present only in designs configured to support DDR4.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_CRCPARCTL1 . CRC_INC_DM
 */
#define  VTSS_F_DDR_UMCTL2_CRCPARCTL1_CRC_INC_DM(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DDR_UMCTL2_CRCPARCTL1_CRC_INC_DM  VTSS_BIT(7)
#define  VTSS_X_DDR_UMCTL2_CRCPARCTL1_CRC_INC_DM(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * If DDR4-SDRAM's CA parity is enabled by INIT6.mr5[2:0]!=0 and this
 * register is set to 1, CA parity is automatically disabled before
 * self-refresh entry, and enabled after self-refresh exit by issuing MR5.
 *
 *   If Geardown is used by MSTR.geardown_mode=1, this register must be set
 * to 1.
 * If this register set to 0, DRAMTMG5.t_ckesr and DRAMTMG5.t_cksre must be
 * increased by PL(Parity latency).
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_CRCPARCTL1 . CAPARITY_DISABLE_BEFORE_SR
 */
#define  VTSS_F_DDR_UMCTL2_CRCPARCTL1_CAPARITY_DISABLE_BEFORE_SR(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DDR_UMCTL2_CRCPARCTL1_CAPARITY_DISABLE_BEFORE_SR  VTSS_BIT(12)
#define  VTSS_X_DDR_UMCTL2_CRCPARCTL1_CAPARITY_DISABLE_BEFORE_SR(x)  VTSS_EXTRACT_BITFIELD(x,12,1)


/**
 * \brief CRC Parity Status Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:CRCPARSTAT
 */
#define VTSS_DDR_UMCTL2_CRCPARSTAT           VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x33)

/**
 * \brief
 * DFI alert error count.
 * If a parity/CRC error is detected on dfi_alert_n, this counter be
 * incremented. This is independent of the setting of
 * CRCPARCTL0.dfi_alert_err_int_en. It saturates at 0xFFFF, and can be
 * cleared by asserting CRCPARCTL0.dfi_alert_err_cnt_clr.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_CRCPARSTAT . DFI_ALERT_ERR_CNT
 */
#define  VTSS_F_DDR_UMCTL2_CRCPARSTAT_DFI_ALERT_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_UMCTL2_CRCPARSTAT_DFI_ALERT_ERR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_UMCTL2_CRCPARSTAT_DFI_ALERT_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * DFI alert error interrupt.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_CRCPARSTAT . DFI_ALERT_ERR_INT
 */
#define  VTSS_F_DDR_UMCTL2_CRCPARSTAT_DFI_ALERT_ERR_INT(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DDR_UMCTL2_CRCPARSTAT_DFI_ALERT_ERR_INT  VTSS_BIT(16)
#define  VTSS_X_DDR_UMCTL2_CRCPARSTAT_DFI_ALERT_ERR_INT(x)  VTSS_EXTRACT_BITFIELD(x,16,1)


/**
 * \brief SDRAM Initialization Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:INIT0
 */
#define VTSS_DDR_UMCTL2_INIT0                VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x34)

/**
 * \brief
 * Indicates the number of cycles to wait after reset before driving CKE
 * high to start the SDRAM initialization sequence.
 * DDR2 specifications typically require this to be programmed for a delay
 * of >= 200 us.
 * LPDDR2/LPDDR3: tINIT1 of 100 ns (min)
 * LPDDR4: tINIT3 of 2 ms (min)
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to JEDEC spec value divided by 2, and round it up to the next
 * integer value.
 * For DDR3/DDR4 RDIMMs, this must include the time needed to satisfy
 * tSTAB.
 * Unit: Multiples of 1024 DFI clock cycles.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_INIT0 . PRE_CKE_X1024
 */
#define  VTSS_F_DDR_UMCTL2_INIT0_PRE_CKE_X1024(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_UMCTL2_INIT0_PRE_CKE_X1024     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_UMCTL2_INIT0_PRE_CKE_X1024(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Indicates the number of cycles to wait after driving CKE high to start
 * the SDRAM initialization sequence.
 * DDR2 typically requires a 400 ns delay, requiring this value to be
 * programmed to 2 at all clock speeds.
 * LPDDR2/LPDDR3 typically requires this to be programmed for a delay of
 * 200 us.
 * LPDDR4 typically requires this to be programmed for a delay of 2 us.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to JEDEC spec value divided by 2, and round it up to the next
 * integer value.
 * Unit: Multiples of 1024 DFI clock cycles.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_INIT0 . POST_CKE_X1024
 */
#define  VTSS_F_DDR_UMCTL2_INIT0_POST_CKE_X1024(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_DDR_UMCTL2_INIT0_POST_CKE_X1024     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_DDR_UMCTL2_INIT0_POST_CKE_X1024(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/**
 * \brief
 * If lower bit is enabled the SDRAM initialization routine is skipped. The
 * upper bit decides what state the controller starts up in when reset is
 * removed. Value "10" is reserved.
 * Programming Mode: Quasi-dynamic Group 2
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h3:

 *
 * Field: ::VTSS_DDR_UMCTL2_INIT0 . SKIP_DRAM_INIT
 */
#define  VTSS_F_DDR_UMCTL2_INIT0_SKIP_DRAM_INIT(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_DDR_UMCTL2_INIT0_SKIP_DRAM_INIT     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_DDR_UMCTL2_INIT0_SKIP_DRAM_INIT(x)  VTSS_EXTRACT_BITFIELD(x,30,2)


/**
 * \brief SDRAM Initialization Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:INIT1
 */
#define VTSS_DDR_UMCTL2_INIT1                VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x35)

/**
 * \brief
 * Indicates the wait period before driving the OCD complete command to
 * SDRAM.
 * There is no known specific requirement for this; it may be set to zero.
 * Unit: Multiples of 32 DFI clock cycles.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_INIT1 . PRE_OCD_X32
 */
#define  VTSS_F_DDR_UMCTL2_INIT1_PRE_OCD_X32(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_INIT1_PRE_OCD_X32     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_INIT1_PRE_OCD_X32(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Indicates the number of cycles to assert SDRAM reset signal during init
 * sequence.
 * This is only present for designs supporting DDR3, DDR4 or LPDDR4
 * devices. For use with a Synopsys DDR PHY, this must be set to a minimum
 * of 1.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to JEDEC spec value divided by 2, and round it up to the next
 * integer value.
 * Unit: Multiples of 1024 DFI clock cycles.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_INIT1 . DRAM_RSTN_X1024
 */
#define  VTSS_F_DDR_UMCTL2_INIT1_DRAM_RSTN_X1024(x)  VTSS_ENCODE_BITFIELD(x,16,9)
#define  VTSS_M_DDR_UMCTL2_INIT1_DRAM_RSTN_X1024     VTSS_ENCODE_BITMASK(16,9)
#define  VTSS_X_DDR_UMCTL2_INIT1_DRAM_RSTN_X1024(x)  VTSS_EXTRACT_BITFIELD(x,16,9)


/**
 * \brief SDRAM Initialization Register 3
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:INIT3
 */
#define VTSS_DDR_UMCTL2_INIT3                VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x37)

/**
 * \brief
 * DDR2: Indicates the value to write to EMR register. Bits 9:7 are for OCD
 * and the setting in this register is ignored. The uMCTL2 sets those bits
 * appropriately.
 * DDR3/DDR4: Value to write to MR1 register Set bit 7 to 0.
 * mDDR: Value to write to EMR register.
 * LPDDR2/LPDDR3/LPDDR4 - Value to write to MR2 register.
 * Programming Mode: Quasi-dynamic Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_INIT3 . EMR
 */
#define  VTSS_F_DDR_UMCTL2_INIT3_EMR(x)       VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_UMCTL2_INIT3_EMR          VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_UMCTL2_INIT3_EMR(x)       VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * DDR2:Indicates the value to write to MR register. Bit 8 is for DLL and
 * the setting here is ignored. The uMCTL2 sets this bit appropriately.
 * DDR3/DDR4: Value loaded into MR0 register.
 * mDDR: Value to write to MR register.
 * LPDDR2/LPDDR3/LPDDR4 - Value to write to MR1 register
 * Programming Mode: Quasi-dynamic Group 1, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_INIT3 . MR
 */
#define  VTSS_F_DDR_UMCTL2_INIT3_MR(x)        VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DDR_UMCTL2_INIT3_MR           VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DDR_UMCTL2_INIT3_MR(x)        VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief SDRAM Initialization Register 4
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:INIT4
 */
#define VTSS_DDR_UMCTL2_INIT4                VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x38)

/**
 * \brief
 * DDR2: Indicates the value to write to EMR3 register.
 * DDR3/DDR4: Value to write to MR3 register.
 * mDDR/LPDDR2/LPDDR3: Unused.
 * LPDDR4: Value to write to MR13 register.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_INIT4 . EMR3
 */
#define  VTSS_F_DDR_UMCTL2_INIT4_EMR3(x)      VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_UMCTL2_INIT4_EMR3         VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_UMCTL2_INIT4_EMR3(x)      VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * DDR2: Indicates the value to write to EMR2 register.
 * DDR3/DDR4: Value to write to MR2 register.
 * LPDDR2/LPDDR3/LPDDR4: Value to write to MR3 register.
 * mDDR: Unused.
 * Programming Mode: Quasi-dynamic Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_INIT4 . EMR2
 */
#define  VTSS_F_DDR_UMCTL2_INIT4_EMR2(x)      VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DDR_UMCTL2_INIT4_EMR2         VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DDR_UMCTL2_INIT4_EMR2(x)      VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief SDRAM Initialization Register 5
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:INIT5
 */
#define VTSS_DDR_UMCTL2_INIT5                VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x39)

/**
 * \brief
 * ZQ initial calibration, tZQINIT.
 * Present only in designs configured to support DDR3 or DDR4 or
 * LPDDR2/LPDDR3.
 * DDR3 typically requires 512 SDRAM clock cycles.
 * DDR4 requires 1024 SDRAM clock cycles.
 * LPDDR2/LPDDR3 requires 1 us.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to JEDEC spec value divided by 2, and round it up to the next
 * integer value.
 * Unit: Multiples of 32 DFI clock cycles.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_INIT5 . DEV_ZQINIT_X32
 */
#define  VTSS_F_DDR_UMCTL2_INIT5_DEV_ZQINIT_X32(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_UMCTL2_INIT5_DEV_ZQINIT_X32     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_UMCTL2_INIT5_DEV_ZQINIT_X32(x)  VTSS_EXTRACT_BITFIELD(x,16,8)


/**
 * \brief SDRAM Initialization Register 6
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:INIT6
 */
#define VTSS_DDR_UMCTL2_INIT6                VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3a)

/**
 * \brief
 * DDR4 - Indicates the value to be loaded into SDRAM MR5 registers.
 * LPDDR4- Value to be loaded into SDRAM MR12 registers.
 * Programming Mode: Quasi-dynamic Group 1, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_INIT6 . MR5
 */
#define  VTSS_F_DDR_UMCTL2_INIT6_MR5(x)       VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_UMCTL2_INIT6_MR5          VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_UMCTL2_INIT6_MR5(x)       VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * DDR4 - Indicates the value to be loaded into SDRAM MR4 registers.
 * LPDDR4- Value to be loaded into SDRAM MR11 registers.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_INIT6 . MR4
 */
#define  VTSS_F_DDR_UMCTL2_INIT6_MR4(x)       VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DDR_UMCTL2_INIT6_MR4          VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DDR_UMCTL2_INIT6_MR4(x)       VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief SDRAM Initialization Register 7
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:INIT7
 */
#define VTSS_DDR_UMCTL2_INIT7                VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3b)

/**
 * \brief
 * DDR4 - Indicates the value to be loaded into SDRAM MR6 registers.
 * LPDDR4- Value to be loaded into SDRAM MR14 registers.
 * Programming Mode: Quasi-dynamic Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_INIT7 . MR6
 */
#define  VTSS_F_DDR_UMCTL2_INIT7_MR6(x)       VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_UMCTL2_INIT7_MR6          VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_UMCTL2_INIT7_MR6(x)       VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief DIMM Control Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DIMMCTL
 */
#define VTSS_DDR_UMCTL2_DIMMCTL              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3c)

/**
 * \brief
 * Staggering enable for multi-rank accesses (for multi-rank UDIMM, RDIMM
 * and LRDIMM implementations only).
 * This is not supported for mDDR, LPDDR2, LPDDR3 or LPDDR4 SDRAMs.
 * Note: Even if this bit is set it does not take care of software driven
 * MR commands (through MRCTRL0/MRCTRL1), where software is responsible to
 * send them to seperate ranks as appropriate.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DIMMCTL . DIMM_STAGGER_CS_EN
 */
#define  VTSS_F_DDR_UMCTL2_DIMMCTL_DIMM_STAGGER_CS_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_DIMMCTL_DIMM_STAGGER_CS_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_DIMMCTL_DIMM_STAGGER_CS_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Enables address mirroring (for multi-rank UDIMM implementations and
 * multi-rank DDR4 RDIMM/LRDIMM implementations).
 * Some UDIMMs and DDR4 RDIMMs/LRDIMMs implement address mirroring for odd
 * ranks, which means that the following address, bank address and bank
 * group bits are swapped: (A3, A4), (A5, A6), (A7, A8), (BA0, BA1) and
 * also (A11, A13), (BG0, BG1) for the DDR4.
 * Setting this bit ensures that, for mode register accesses during the
 * automatic initialization routine, these bits are swapped within the
 * uMCTL2 to compensate for this UDIMM/RDIMM/LRDIMM swapping. In addition
 * to the automatic initialization routine, in case of DDR4
 * UDIMM/RDIMM/LRDIMM, they are swapped during the automatic MRS access to
 * enable/disable of a particular DDR4 feature.
 * Note: This has no effect on the address of any other memory accesses, or
 * of software-driven mode register accesses.
 * This is not supported for mDDR, LPDDR2, LPDDR3 or LPDDR4 SDRAMs.
 * Note: In case of x16 DDR4 DIMMs, BG1 output of MRS for the odd ranks is
 * same as BG0 because BG1 is invalid, hence dimm_dis_bg_mirroring register
 * must be set to 1.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DIMMCTL . DIMM_ADDR_MIRR_EN
 */
#define  VTSS_F_DDR_UMCTL2_DIMMCTL_DIMM_ADDR_MIRR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_DIMMCTL_DIMM_ADDR_MIRR_EN  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_DIMMCTL_DIMM_ADDR_MIRR_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enables output inversion (for DDR4 RDIMM/LRDIMM implementations only).
 * DDR4 RDIMM/LRDIMM implements the Output Inversion feature by default,
 * which means that the following address, bank address, and bank group
 * bits of B-side DRAMs are inverted: A3-A9, A11, A13, A17, BA0-BA1,
 * BG0-BG1.
 * Setting this bit ensures that, for mode register accesses generated by
 * the uMCTL2 during the automatic initialization routine and enabling of a
 * particular DDR4 feature, separate A-side and B-side mode register
 * accesses are generated.
 * For B-side mode register accesses, these bits are inverted within the
 * uMCTL2 to compensate for this RDIMM/LRDIMM inversion. It is recommended
 * to set this bit always, if using DDR4 RDIMMs/LRDIMMs.
 * Note: This has no effect on the address of any other memory accesses, or
 * of software-driven mode register accesses.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DIMMCTL . DIMM_OUTPUT_INV_EN
 */
#define  VTSS_F_DDR_UMCTL2_DIMMCTL_DIMM_OUTPUT_INV_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_UMCTL2_DIMMCTL_DIMM_OUTPUT_INV_EN  VTSS_BIT(2)
#define  VTSS_X_DDR_UMCTL2_DIMMCTL_DIMM_OUTPUT_INV_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable this field for A17 bit of MRS command.
 * A17 bit of the mode register address is specified as RFU (Reserved for
 * Future Use) and must be programmed to 0 during MRS.
 * In case where DRAMs that do not have A17 are attached as DDR4
 * RDIMM/LRDIMM, and the output inversion is enabled, this must be set to
 * 0, so that the calculation of CA parity does not include A17 bit.
 * To keep consistency with the RCD, DA[3] in F0RC08 of the RCD also needs
 * to be set to 1 (that is, Disabled).
 * Note: This has no effect on the address of any other memory accesses, or
 * of software-driven mode register accesses.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DIMMCTL . MRS_A17_EN
 */
#define  VTSS_F_DDR_UMCTL2_DIMMCTL_MRS_A17_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_UMCTL2_DIMMCTL_MRS_A17_EN  VTSS_BIT(3)
#define  VTSS_X_DDR_UMCTL2_DIMMCTL_MRS_A17_EN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable this field for BG1 bit of MRS command.
 * BG1 bit of the mode register address is specified as RFU (Reserved for
 * Future Use) and must be programmed to 0 during MRS.
 * In case where DRAMs that do not have BG1 are attached, and both the CA
 * parity and the output inversion are enabled, this must be set to 0, so
 * that the calculation of CA parity does not include BG1 bit.
 * Note: This has no effect on the address of any other memory accesses, or
 * of software-driven mode register accesses.
 * If address mirroring is enabled, this is applied to BG1 of even ranks
 * and BG0 of odd ranks.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DIMMCTL . MRS_BG1_EN
 */
#define  VTSS_F_DDR_UMCTL2_DIMMCTL_MRS_BG1_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_DIMMCTL_MRS_BG1_EN  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_DIMMCTL_MRS_BG1_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Disables address mirroring for BG bits.
 * When this is set to 1, BG0 and BG1 are NOT swapped even if Address
 * Mirroring is enabled. This is required for DDR4 DIMMs with x16 devices.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DIMMCTL . DIMM_DIS_BG_MIRRORING
 */
#define  VTSS_F_DDR_UMCTL2_DIMMCTL_DIMM_DIS_BG_MIRRORING(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_UMCTL2_DIMMCTL_DIMM_DIS_BG_MIRRORING  VTSS_BIT(5)
#define  VTSS_X_DDR_UMCTL2_DIMMCTL_DIMM_DIS_BG_MIRRORING(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Protects the timing restrictions (tBCW/tMRC) between consecutive BCOM
 * commands defined in the Data Buffer specification.
 * When using DDR4 LRDIMM, this bit must be set to 1. Otherwise, this bit
 * must be set to 0.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DIMMCTL . LRDIMM_BCOM_CMD_PROT
 */
#define  VTSS_F_DDR_UMCTL2_DIMMCTL_LRDIMM_BCOM_CMD_PROT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DDR_UMCTL2_DIMMCTL_LRDIMM_BCOM_CMD_PROT  VTSS_BIT(6)
#define  VTSS_X_DDR_UMCTL2_DIMMCTL_LRDIMM_BCOM_CMD_PROT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Indicates the weak drive mode to be set to the RCD.
 * This field is used only when the uMCTL2 disables CAL mode.
 * When weak drive mode in the RCD is enabled during initialization, this
 * field must be set to 1.
 * When RCD is not used, this field must be set to 0.
 * Programming Mode: Static
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_DIMMCTL . RCD_WEAK_DRIVE
 */
#define  VTSS_F_DDR_UMCTL2_DIMMCTL_RCD_WEAK_DRIVE(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DDR_UMCTL2_DIMMCTL_RCD_WEAK_DRIVE  VTSS_BIT(12)
#define  VTSS_X_DDR_UMCTL2_DIMMCTL_RCD_WEAK_DRIVE(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Disables RCD outputs to A-side DRAMs.
 * This field is used only when the uMCTL2 disables CAL mode.
 * This value is written to F0RC0 DA[2] before and after disabling CAL
 * mode. It is recommended to set it to 0 except for debug.
 * Programming Mode: Static
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_DIMMCTL . RCD_A_OUTPUT_DISABLED
 */
#define  VTSS_F_DDR_UMCTL2_DIMMCTL_RCD_A_OUTPUT_DISABLED(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DDR_UMCTL2_DIMMCTL_RCD_A_OUTPUT_DISABLED  VTSS_BIT(13)
#define  VTSS_X_DDR_UMCTL2_DIMMCTL_RCD_A_OUTPUT_DISABLED(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Disables RCD outputs to B-side DRAMs.
 * This field is used only when the uMCTL2 disables CAL mode.
 * This value is written to F0RC0 DA[3] before and after disabling CAL
 * mode. It is recommended to set it to ~DIMMCTL.dimm_output_inv_en except
 * for debug.
 * Programming Mode: Static
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_DIMMCTL . RCD_B_OUTPUT_DISABLED
 */
#define  VTSS_F_DDR_UMCTL2_DIMMCTL_RCD_B_OUTPUT_DISABLED(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_DDR_UMCTL2_DIMMCTL_RCD_B_OUTPUT_DISABLED  VTSS_BIT(14)
#define  VTSS_X_DDR_UMCTL2_DIMMCTL_RCD_B_OUTPUT_DISABLED(x)  VTSS_EXTRACT_BITFIELD(x,14,1)


/**
 * \brief Rank Control Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:RANKCTL
 */
#define VTSS_DDR_UMCTL2_RANKCTL              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3d)

/**
 * \brief
 * Only present for multi-rank configurations.
 * Background: Reads to the same rank can be performed back-to-back. Reads
 * to different ranks require additional gap dictated by the register
 * RANKCTL.diff_rank_rd_gap.
 * This is to avoid possible data bus contention as well as to give PHY
 * enough time to switch the delay when changing ranks.
 * The uMCTL2 arbitrates for bus access on a cycle-by-cycle basis;
 * therefore after a read is scheduled, there are few clock cycles
 * (determined by the value on RANKCTL.diff_rank_rd_gap register) in which
 * only reads from the same rank are eligible to be scheduled.
 * This prevents reads from other ranks from having fair access to the data
 * bus.
 * This parameter represents the maximum number of reads that can be
 * scheduled consecutively to the same rank.
 * After this number is reached, a delay equal to RANKCTL.diff_rank_rd_gap
 * is inserted by the scheduler to allow all ranks a fair opportunity to be
 * scheduled.
 * Higher numbers increase bandwidth utilization, lower numbers increase
 * fairness.
 * This feature can be DISABLED by setting this register to 0. When set to
 * 0, the controller stays on the same rank as long as commands are
 * available for it.
 * Minimum programmable value is 0 (feature disabled) and maximum
 * programmable value is 0xF.
 * For uPCTL2, this register field must be set to 0 (feature disabled)
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_RANKCTL . MAX_RANK_RD
 */
#define  VTSS_F_DDR_UMCTL2_RANKCTL_MAX_RANK_RD(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_RANKCTL_MAX_RANK_RD     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_RANKCTL_MAX_RANK_RD(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Only present for multi-rank configurations.
 * Indicates the number of clocks of gap in data responses when performing
 * consecutive reads to different ranks.
 * This is used to switch the delays in the PHY to match the rank
 * requirements.
 * This value must consider both PHY requirement and ODT requirement.
 *  - PHY requirement:tphy_rdcsgap (For more information on value of
 * tphy_rdcsgap, see PHY databook)
 * If read preamble is set to 2tCK(DDR4 only), must be increased by 1.
 * If read postamble is set to 1.5tCK(LPDDR4 only), must be increased by 1.
 *  - ODT requirement: The value programmed in this register takes care of
 * the ODT switch off timing requirement when switching ranks during reads:
 * diff_rank_rd_gap must be a minimum of ODTCFG.rd_odt_hold - BL/2
 * when the controller is operating in 1:1 mode, program this to the larger
 * of PHY requirement or ODT requirement.
 * When the controller is operating in 1:2 mode, program this to the larger
 * value divided by two and round it up to the next integer.
 * After PHY has completed training the value programmed may need to be
 * increased. For more information, see relevant PHY documentation.
 * Note that, if using DDR4-LRDIMM, refer to TRDRD timing requirements in
 * JEDEC DDR4 Data Buffer (DDR4DB01) Specification.If a value greater than
 * 0xF is needed, the RANKCTL.diff_rank_rd_gap_msb field must be used as
 * extension. For DFI 1:2 mode, a maximum value of
 * {diff_rank_rd_gap_msb,diff_rank_rd_gap} < 'h11 is supported. For DFI 1:1
 * mode a maximum value of {diff_rank_rd_gap_msb,diff_rank_rd_gap} <= 'h1F
 * is supported.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_RANKCTL . DIFF_RANK_RD_GAP
 */
#define  VTSS_F_DDR_UMCTL2_RANKCTL_DIFF_RANK_RD_GAP(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_DDR_UMCTL2_RANKCTL_DIFF_RANK_RD_GAP     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_DDR_UMCTL2_RANKCTL_DIFF_RANK_RD_GAP(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * Only present for multi-rank configurations.
 * Indicates the number of clocks of gap in data responses when performing
 * consecutive writes to different ranks.
 * This is used to switch the delays in the PHY to match the rank
 * requirements. This value must consider both PHY requirement and ODT
 * requirement.
 *  - PHY requirement - tphy_wrcsgap (For more information on value of
 * tphy_wrcsgap, see PHY databook)
 * If CRC feature is enabled, must be increased by 1.
 * If write preamble is set to 2tCK(DDR4 only), must be increased by 1.
 * Write preamble is always set to 2tCK for LPDDR4, refer to PHY databook
 * to see if this is already factored into tphy_wrcsgap value or if it
 * needs to be increased by 1.
 * If write postamble is set to 1.5tCK(LPDDR4 only), must be increased by
 * 1.
 *  - ODT requirement - The value programmed in this register takes care of
 * the ODT switch off timing requirement when switching ranks during
 * writes.
 * For LPDDR4, with DQ ODT enabled, diff_rank_wr_gap must be a minimum of
 * ODTLoff - ODTLon - BL/2 + 1
 * For other cases, diff_rank_wr_gap must be a minimum of
 * ODTCFG.wr_odt_hold - BL/2
 * When the controller is operating in 1:1 mode, program this to the larger
 * of PHY requirement or ODT requirement.
 * If CRC is enabled, the value can be decreased by 2 because the
 * programmed value is internally increased by 1 (it is always 2 in terms
 * of DFI PHY clock cycle as CRC is supported only with 1:2 frequency
 * ratio).
 * When the controller is operating in 1:2 mode, program this to the larger
 * value divided by two and round it up to the next integer.
 * After PHY has completed training the value programmed may need to be
 * increased. For more information, see relevant PHY documentation.
 * Note that, if using DDR4-LRDIMM, refer to TWRWR timing requirements in
 * JEDEC DDR4 Data Buffer (DDR4DB01) Specification.
 * If a value greater than 0xF is needed, the RANKCTL.diff_rank_wr_gap_msb
 * field must be used as extension. For DFI 1:2 mode, a maximum value of
 * {diff_rank_wr_gap_msb,diff_rank_wr_gap} < 'h11 is supported. For DFI 1:1
 * mode a maximum value of {diff_rank_wr_gap_msb,diff_rank_wr_gap} <= 'h1F
 * is supported.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_RANKCTL . DIFF_RANK_WR_GAP
 */
#define  VTSS_F_DDR_UMCTL2_RANKCTL_DIFF_RANK_WR_GAP(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_RANKCTL_DIFF_RANK_WR_GAP     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_RANKCTL_DIFF_RANK_WR_GAP(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * Only present for multi-rank configurations.
 * Background: Writes to the same rank can be performed back-to-back.
 * Writes to different ranks require additional gap dictated by the
 * register RANKCTL.diff_rank_wr_gap.
 * This is to avoid possible data bus contention as well as to give PHY
 * enough time to switch the delay when changing ranks.
 * The uMCTL2 arbitrates for bus access on a cycle-by-cycle basis;
 * therefore after a write is scheduled, there are few clock cycles
 * (determined by the value on RANKCTL.diff_rank_wr_gap register) in which
 * only writes from the same rank are eligible to be scheduled.
 * This prevents writes from other ranks from having fair access to the
 * data bus.
 * This parameter represents the maximum number of writes that can be
 * scheduled consecutively to the same rank. After this number is reached,
 * a delay equal to RANKCTL.diff_rank_wr_gap is inserted by the scheduler
 * to allow all ranks a fair opportunity to be scheduled. Higher numbers
 * increase bandwidth utilization, lower numbers increase fairness.
 * This feature can be DISABLED by setting this register to 0. When set to
 * 0, the controller stays on the same rank as long as commands are
 * available for it.
 * Minimum programmable value is 0 (feature disabled) and maximum
 * programmable value is 0xF.
 * For uPCTL2, this register field must be set to 0 (feature disabled)
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_RANKCTL . MAX_RANK_WR
 */
#define  VTSS_F_DDR_UMCTL2_RANKCTL_MAX_RANK_WR(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_DDR_UMCTL2_RANKCTL_MAX_RANK_WR     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_DDR_UMCTL2_RANKCTL_MAX_RANK_WR(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * This is only present for multi-rank configurations.
 * Programming Mode: Quasi-dynamic Group 2
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_RANKCTL . DIFF_RANK_RD_GAP_MSB
 */
#define  VTSS_F_DDR_UMCTL2_RANKCTL_DIFF_RANK_RD_GAP_MSB(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_DDR_UMCTL2_RANKCTL_DIFF_RANK_RD_GAP_MSB  VTSS_BIT(24)
#define  VTSS_X_DDR_UMCTL2_RANKCTL_DIFF_RANK_RD_GAP_MSB(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Only present for multi-rank configurations.
 * Programming Mode: Quasi-dynamic Group 2
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_RANKCTL . DIFF_RANK_WR_GAP_MSB
 */
#define  VTSS_F_DDR_UMCTL2_RANKCTL_DIFF_RANK_WR_GAP_MSB(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_DDR_UMCTL2_RANKCTL_DIFF_RANK_WR_GAP_MSB  VTSS_BIT(26)
#define  VTSS_X_DDR_UMCTL2_RANKCTL_DIFF_RANK_WR_GAP_MSB(x)  VTSS_EXTRACT_BITFIELD(x,26,1)


/**
 * \brief SDRAM Timing Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG0
 */
#define VTSS_DDR_UMCTL2_DRAMTMG0             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x40)

/**
 * \brief
 * tRAS(min) - Specifies the minimum time between activate and precharge to
 * the same bank.
 * When the controller is operating in 1:1 frequency ratio mode, t_ras_min
 * must be set to RoundUp(tRASmin/tCK)
 * When the controller is operating in 1:2 frequency ratio mode, 1T mode,
 * t_ras_min must be set to RoundDown(RoundUp(tRASmin/tCK)/2)
 * When the controller is operating in 1:2 frequency ratio mode, 2T mode,
 * geardown mode or LPDDR4 mode, t_ras min must be set to
 * RoundUp(RoundUp(tRASmin/tCK)/2)
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG0 . T_RAS_MIN
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG0_T_RAS_MIN(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG0_T_RAS_MIN     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG0_T_RAS_MIN(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * tRAS(max) - Specifies the maximum time between activate and precharge to
 * same bank. This is the maximum time that a page can be kept open
 * Minimum value of this register is 1. Zero is invalid.
 * When the controller is operating in 1:1 frequency ratio mode, t_ras_max
 * must be set to RoundDown(tRAS(max)/tCK/1024).
 * When the controller is operating in 1:2 frequency ratio mode, t_ras_max
 * must be set to RoundDown((RoundDown(tRAS(max)/tCK/1024)-1)/2).
 * Unit: Multiples of 1024 DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG0 . T_RAS_MAX
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG0_T_RAS_MAX(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG0_T_RAS_MAX     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG0_T_RAS_MAX(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/**
 * \brief
 * tFAW - valid only when 8 or more banks(or banks x bank groups) are
 * present.
 * In 8-bank design, at most 4 banks must be activated in a rolling window
 * of tFAW cycles.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tFAW/2) and round up to next integer value.
 * In a 4-bank design, set this register to 0x1 independent of the 1:1/1:2
 * frequency mode.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG0 . T_FAW
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG0_T_FAW(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG0_T_FAW     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG0_T_FAW(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * Specifies the minimum time between write and precharge to same bank.
 * Specifications: WL + BL/2 + tWR = approximately 8 cycles + 15 ns = 14
 * clocks @400MHz and less for lower frequencies.
 * where:
 *  - WL: Write latency
 *  - BL: Burst length. This must match the value programmed in the BL bit
 * of the mode register to the SDRAM. BST (burst terminate) is not
 * supported at present
 *  - tWR: Write recovery time. This comes directly from the SDRAM
 * specification
 * Add one extra cycle for LPDDR2/LPDDR3/LPDDR4 for this parameter.
 * When the controller is operating in 1:2 frequency ratio mode, 1T mode,
 * divide the previous value by 2. No rounding up.
 * When the controller is operating in 1:2 frequency ratio mode, 2T mode,
 * geardown mode or LPDDR4 mode, divide the previous value by 2 and round
 * it up to the next integer value.
 * Note that, depending on the PHY, if using LRDIMM, it may be necessary to
 * adjust the value of this parameter to compensate for the extra cycle of
 * latency through the LRDIMM.
 * For DDR4, LPDDR4, LPDDR3, using nWR(WR) instead of tWR to calculate the
 * value of this parameter.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 1, Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG0 . WR2PRE
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG0_WR2PRE(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG0_WR2PRE     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG0_WR2PRE(x)  VTSS_EXTRACT_BITFIELD(x,24,7)


/**
 * \brief SDRAM Timing Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG1
 */
#define VTSS_DDR_UMCTL2_DRAMTMG1             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x41)

/**
 * \brief
 * tRC - Specifies the minimum time between activates to same bank.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tRC/2) and round up to next integer value.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG1 . T_RC
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG1_T_RC(x)   VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG1_T_RC      VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG1_T_RC(x)   VTSS_EXTRACT_BITFIELD(x,0,7)

/**
 * \brief
 * tRTP - Specifies the minimum time from read to precharge of same bank.
 *  - DDR2 - tAL + BL/2 + max(RoundUp(tRTP/tCK), 2) - 2
 *  - DDR3 - tAL + max (RoundUp(tRTP/tCK), 4)
 *  - DDR4 - Max of following two equations:  tAL + max (RoundUp(tRTP/tCK),
 * 4) or, RL + BL/2 - tRP (*).
 *  - mDDR - BL/2
 *  - LPDDR2 - Depends on if it is LPDDR2-S2 or LPDDR2-S4: LPDDR2-S2: BL/2
 * + RoundUp(tRTP/tCK) - 1. LPDDR2-S4: BL/2 + max(RoundUp(tRTP/tCK),2) - 2.
 *  - LPDDR3 - BL/2 + max(RoundUp(tRTP/tCK),4) - 4
 *  - LPDDR4 - BL/2 + max(RoundUp(tRTP/tCK),8) - 8
 * (*) When both DDR4 SDRAM and ST-MRAM are used simultaneously, use
 * SDRAM's tRP value for calculation.
 * When the controller is operating in 1:2 mode, 1T mode, divide the
 * previous value by 2. No rounding up.
 * When the controller is operating in 1:2 mode, 2T mode, geardown mode or
 * LPDDR4 mode, divide the previous value by 2 and round it up to the next
 * integer value.
 * For DDR4, using RTP instead of tRTP to calculate the value of this
 * parameter.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 1, Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG1 . RD2PRE
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG1_RD2PRE(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG1_RD2PRE     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG1_RD2PRE(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/**
 * \brief
 * tXP - Specifies the minimum time after power-down exit to any operation.
 * For DDR3, this must be programmed to tXPDLL if slow powerdown exit is
 * selected in MR0[12].
 * If C/A parity for DDR4 is used, set to (tXP+PL) instead.
 * If LPDDR4 is selected and its spec has tCKELPD parameter, set to the
 * larger of tXP and tCKELPD instead.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tXP/2) and round it up to the next integer value.
 * Units: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG1 . T_XP
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG1_T_XP(x)   VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG1_T_XP      VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG1_T_XP(x)   VTSS_EXTRACT_BITFIELD(x,16,5)


/**
 * \brief SDRAM Timing Register 2
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG2
 */
#define VTSS_DDR_UMCTL2_DRAMTMG2             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x42)

/**
 * \brief
 * In DDR4, minimum time from write command to read command for same bank
 * group. In other protoocls, minimum time from write command to read
 * command.  This must include time for bus turn-around and all PHY and
 * system requirements.
 *
 * After the PHY has completed training, the value programmed may need to
 * be increased.  Please see the relevant PHY databook for details of what
 * should be included here.
 *
 * The following calculations are minimum values, and do not include the
 * PHY/system requirements mentioned above:
 *
 * DDR4: CWL + BL/2 + tWTR_L
 *
 * LPDDR2/3/4: WL + BL/2 + tWTR + 1
 *
 * Others: CWL + BL/2 + tWTR
 *
 * Where:
 *  - CWL: CAS write latency
 *  - WL: Write latency
 *  - BL: Burst length. This must match the value programmed in the BL bit
 * of the mode register to the SDRAM
 *  - tWTR_L: Internal write to read command delay for same bank group.
 * This comes directly from the SDRAM specification
 *  - tWTR: Internal write to read command delay. This comes directly from
 * the SDRAM specification
 * Add one extra cycle for LPDDR2/LPDDR3/LPDDR4 operation.
 * WTR_L must be increased by one if DDR4 2tCK write preamble is used.
 *
 * When the controller is operating in 1:2 mode, divide the value
 * calculated using the previous equation by 2, and round it up to next
 * integer.
 *
 * If your configuration has RANKCTL1.wr2rd_dr, write to read bus
 * turn-around between different physical ranks are controlled by
 * RANKCTL1.wr2rd_dr.
 *
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 1, Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG2 . WR2RD
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG2_WR2RD(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG2_WR2RD     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG2_WR2RD(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * Minimum time from read command to write command. This must include time
 * for bus turnaround (both within ranks and between ranks) and all PHY and
 * system requirements.
 *
 * After the PHY has completed training, the value programmed may need to
 * be increased.  Please see the relevant PHY databook for details of what
 * should be included here.
 *
 * The following calculations are minimum values, and do not include the
 * PHY/system requirements mentioned above:
 *
 * DDR2/3/mDDR: RL + BL/2 + 2 - WL
 *
 * DDR4: RL + BL/2 + 1 + WR_PREAMBLE - WL
 *
 * LPDDR2/LPDDR3: RL + BL/2 + RU(tDQSCKmax/tCK) + 1 - WL
 *
 * LPDDR4(DQ ODT is Disabled): RL + BL/2 + RU(tDQSCKmax/tCK) + WR_PREAMBLE
 * + RD_POSTAMBLE - WL
 *
 * LPDDR4(DQ ODT is Enabled): RL + BL/2 + RU(tDQSCKmax/tCK) + RD_POSTAMBLE
 * - ODTLon - RD(tODTon(min)/tCK) + 1
 *
 * Where:
 *  - WL: Write latency
 *  - BL: Burst length. This must match the value programmed in the BL bit
 * of the mode register to the SDRAM
 *  - RL: Read latency = CAS latency
 *  - WR_PREAMBLE: 1 (1tCK write preamble), 2 (2tCK write preamble). This
 * is unique to DDR4 and LPDDR4
 *  - RD_POSTAMBLE: 0.5 (0.5tCK read postamble), 1.5 (1.5tCK read
 * postamble). This is unique to LPDDR4
 * For LPDDR2/LPDDR3/LPDDR4, if derating is enabled
 * (DERATEEN.derate_enable=1), derated tDQSCKmax must be used.
 *
 * When the controller is operating in 1:2 frequency ratio mode, divide the
 * value calculated using the previous equation by 2, and round it up to
 * next integer.
 *
 * Note that, depending on the PHY, if using LRDIMM, it may be necessary to
 * adjust the value of this parameter to compensate for the extra cycle of
 * latency through the LRDIMM.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 1, Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG2 . RD2WR
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG2_RD2WR(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG2_RD2WR     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG2_RD2WR(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/**
 * \brief
 * Set this field to RL.
 * Indicates the time from read command to read data on SDRAM interface.
 * This must be set to RL.
 * Note that, depending on the PHY, if using RDIMM/LRDIMM, it might be
 * necessary to adjust the value of RL to compensate for the extra cycle of
 * latency through the RDIMM/LRDIMM.
 * When the controller is operating in 1:2 frequency ratio mode, divide the
 * value calculated using the previous equation by 2, and round it up to
 * next integer.
 * This register field is not required for DDR2 and DDR3, as the DFI read
 * and write latencies defined in DFITMG0 and DFITMG1 are sufficient for
 * those protocols
 * For all protocols, in addition to programming this register field, it is
 * necessary to program DFITMG0 and DFITMG1 to control the read and write
 * latencies
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 1, Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG2 . READ_LATENCY
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG2_READ_LATENCY(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG2_READ_LATENCY     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG2_READ_LATENCY(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * Set this field to WL.
 * Indicates the Time from write command to write data on SDRAM interface.
 * This must be set to WL.
 * For mDDR, it must  be set to 1.
 * Note that, depending on the PHY, if using RDIMM/LRDIMM, it might be
 * necessary to adjust the value of WL to compensate for the extra cycle of
 * latency through the RDIMM/LRDIMM.
 * When the controller is operating in 1:2 frequency ratio mode, divide the
 * value calculated using the previous equation by 2, and round it up to
 * next integer.
 * This register field is not required for DDR2 and DDR3, as the DFI read
 * and write latencies defined in DFITMG0 and DFITMG1 are sufficient for
 * those protocols
 * For all protocols, in addition to programming this register field, it is
 * necessary to program DFITMG0 and DFITMG1 to control the read and write
 * latencies
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 1, Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG2 . WRITE_LATENCY
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG2_WRITE_LATENCY(x)  VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG2_WRITE_LATENCY     VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG2_WRITE_LATENCY(x)  VTSS_EXTRACT_BITFIELD(x,24,6)


/**
 * \brief SDRAM Timing Register 3
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG3
 */
#define VTSS_DDR_UMCTL2_DRAMTMG3             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x43)

/**
 * \brief
 * tMOD - Parameter used only in DDR3 and DDR4.
 * Indicates the number of cycles between load mode command and following
 * non-load mode command.
 * If C/A parity for DDR4 is used, set to tMOD_PAR(tMOD+PL) instead.
 * If CAL mode is enabled (DFITMG1.dfi_t_cmd_lat > 0), tCAL
 * (=DFITMG1.dfi_cmd_lat) must be added to the previous calculations.
 * Set to tMOD if controller is operating in 1:1 frequency ratio mode, or
 * tMOD/2 (rounded up to next integer) if controller is operating in 1:2
 * frequency ratio mode. Note that if using RDIMM/LRDIMM, depending on the
 * PHY, it may be necessary to adjust the value of this parameter to
 * compensate for the extra cycle of latency applied to mode register
 * writes by the RDIMM/LRDIMM chip.
 * Also note that if using LRDIMM, the minimum value of this register is
 * tMRD_L2 if controller is operating in 1:1 frequency ratio mode, or
 * tMRD_L2/2 (rounded up to next integer) if controller is operating in 1:2
 * frequency ratio mode.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG3 . T_MOD
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG3_T_MOD(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG3_T_MOD     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG3_T_MOD(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * \brief
 * tMRD- Indicates the number of cycles to wait after a mode register write
 * or read.
 * Depending on the connected SDRAM, tMRD represents:
 *  - DDR2/mDDR: Time from MRS to any command
 *  - DDR3/4: Time from MRS to MRS command
 *  - LPDDR2: not used
 *  - LPDDR3/4: Time from MRS to non-MRS command
 *  When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tMRD/2) and round it up to the next integer value.
 * If C/A parity for DDR4 is used, set to tMRD_PAR(tMOD+PL) instead.
 * If CAL mode is enabled (DFITMG1.dfi_t_cmd_lat > 0), tCAL
 * (=DFITMG1.dfi_cmd_lat) must be added to the previous calculations.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG3 . T_MRD
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG3_T_MRD(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG3_T_MRD     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG3_T_MRD(x)  VTSS_EXTRACT_BITFIELD(x,12,6)


/**
 * \brief SDRAM Timing Register 4
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG4
 */
#define VTSS_DDR_UMCTL2_DRAMTMG4             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x44)

/**
 * \brief
 * tRP: Indicates the minimum time from single-bank precharge to activate
 * of same bank.
 * When the controller is operating in 1:1 frequency ratio mode, t_rp must
 * be set to RoundUp(tRP/tCK).
 * When the controller is operating in 1:2 frequency ratio mode, t_rp must
 * be set to RoundDown(RoundUp(tRP/tCK)/2) + 1.
 * When the controller is operating in 1:2 frequency ratio mode in LPDDR4,
 * t_rp must be set to RoundUp(RoundUp(tRP/tCK)/2).
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG4 . T_RP
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG4_T_RP(x)   VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG4_T_RP      VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG4_T_RP(x)   VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * DDR4: tRRD_L: This is the minimum time between activates from bank "a"
 * to bank "b" for same bank group.
 * Others: tRRD: Minimum time between activates from bank "a" to bank "b"
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tRRD_L/2 or tRRD/2) and round it up to the next integer value.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG4 . T_RRD
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG4_T_RRD(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG4_T_RRD     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG4_T_RRD(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * DDR4: tCCD_L: This is the minimum time between two reads or two writes
 * for same bank group.
 * Others: tCCD: This is the minimum time between two reads or two writes.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tCCD_L/2 or tCCD/2) and round it up to the next integer value.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG4 . T_CCD
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG4_T_CCD(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG4_T_CCD     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG4_T_CCD(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * tRCD - tAL: Indicates the minimum time from activate to read or write
 * command to same bank.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to ((tRCD - tAL)/2) and round it up to the next integer value.
 * Minimum value allowed for this register is 1, which implies minimum
 * (tRCD - tAL) value to be 2 when the controller is operating in 1:2
 * frequency ratio mode.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 1, Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG4 . T_RCD
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG4_T_RCD(x)  VTSS_ENCODE_BITFIELD(x,24,5)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG4_T_RCD     VTSS_ENCODE_BITMASK(24,5)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG4_T_RCD(x)  VTSS_EXTRACT_BITFIELD(x,24,5)


/**
 * \brief SDRAM Timing Register 5
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG5
 */
#define VTSS_DDR_UMCTL2_DRAMTMG5             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x45)

/**
 * \brief
 * Indicates the minimum number of cycles of CKE HIGH/LOW during power-down
 * and self-refresh.
 *  - LPDDR2/LPDDR3 mode - Set this to the larger of tCKE or tCKESR
 *  - LPDDR4 mode - Set this to the larger of tCKE or tSR
 *  - Non-LPDDR2/non-LPDDR3/non-LPDDR4 designs - Set this to tCKE value
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (value described above)/2 and round it up to the next integer
 * value.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG5 . T_CKE
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG5_T_CKE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG5_T_CKE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG5_T_CKE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * Indicates the minimum CKE low width for self-refresh or self-refresh
 * power down entry to exit timing in memory clock cycles.
 * Recommended settings:
 *  - mDDR - tRFC
 *  - LPDDR2 - tCKESR
 *  - LPDDR3 - tCKESR
 *  - LPDDR4 - max(tCKE, tSR)
 *  - DDR2 - tCKE
 *  - DDR3 - tCKE + 1
 *  - DDR4(No RDIMM) - tCKE + 1 (+ PL(parity latency)(*))
 *  - DDR4(RDIMM)    - t_cksre + tCKEV
 * (*)Only if CRCPARCTL1.caparity_disable_before_sr=0, this register must
 * be increased by PL.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to recommended value divided by two and round it up to next
 * integer.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG5 . T_CKESR
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG5_T_CKESR(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG5_T_CKESR     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG5_T_CKESR(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * This is the time after self-refresh Down Entry that CK is maintained as
 * a valid clock.
 * Specifies the clock disable delay after SRE.
 * Recommended settings:
 *  - mDDR - 0
 *  - LPDDR2 - 2
 *  - LPDDR3 - 2
 *  - LPDDR4 - tCKELCK
 *  - DDR2 - 1
 *  - DDR3 - Max (10 ns, 5 tCK)
 *  - DDR4(No RDIMM) - Max (10 ns, 5 tCK) (+ PL(parity latency)(*))
 *  - DDR4(RDIMM)    - Max (Max (10 ns, 5 tCK) (+ PL(parity latency)(*)),
 * tCKOff)
 * (*)Only if CRCPARCTL1.caparity_disable_before_sr=0, this register must
 * be increased by PL.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to recommended value divided by two and round it up to next
 * integer.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG5 . T_CKSRE
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG5_T_CKSRE(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG5_T_CKSRE     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG5_T_CKSRE(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * This is the time before self-refresh Exit that CK is maintained as a
 * valid clock before issuing SRX.
 * Specifies the clock stable time before SRX.
 * Recommended settings:
 *  - mDDR - 1
 *  - LPDDR2 - 2
 *  - LPDDR3 - 2
 *  - LPDDR4 - tCKCKEH
 *  - DDR2 - 1
 *  - DDR3 - tCKSRX
 *  - DDR4 - tCKSRX
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to recommended value divided by two and round it up to next
 * integer.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG5 . T_CKSRX
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG5_T_CKSRX(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG5_T_CKSRX     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG5_T_CKSRX(x)  VTSS_EXTRACT_BITFIELD(x,24,4)


/**
 * \brief SDRAM Timing Register 8
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG8
 */
#define VTSS_DDR_UMCTL2_DRAMTMG8             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x48)

/**
 * \brief
 * tXS: Exit self-refresh to commands not requiring a locked DLL.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to the previous value divided by 2 and round up to next integer
 * value.
 * Note: Used only for DDR2, DDR3 and DDR4 SDRAMs.
 * Unit: Multiples of 32 DFI clock cycles.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG8 . T_XS_X32
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG8_T_XS_X32(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG8_T_XS_X32     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG8_T_XS_X32(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/**
 * \brief
 * tXSDLL: Exit self-refresh to commands requiring a locked DLL.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to the previous value divided by 2 and round up to next integer
 * value.
 * Note: Used only for DDR2, DDR3 and DDR4 SDRAMs.
 * Unit: Multiples of 32 DFI clock cycles.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG8 . T_XS_DLL_X32
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG8_T_XS_DLL_X32(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG8_T_XS_DLL_X32     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG8_T_XS_DLL_X32(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/**
 * \brief
 * tXS_ABORT: Exit self-refresh to commands not requiring a locked DLL in
 * self-refresh Abort.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to the previous value divided by 2 and round up to next integer
 * value.
 * Note: Ensure this is less than or equal to t_xs_x32.
 * Unit: Multiples of 32 DFI clock cycles.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG8 . T_XS_ABORT_X32
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG8_T_XS_ABORT_X32(x)  VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG8_T_XS_ABORT_X32     VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG8_T_XS_ABORT_X32(x)  VTSS_EXTRACT_BITFIELD(x,16,7)

/**
 * \brief
 * tXS_FAST: Exit self-refresh to ZQCL, ZQCS and MRS (only CL, WR, RTP and
 * Geardown mode).
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to the previous value divided by 2 and round up to next integer
 * value.
 * Note: This is applicable to only ZQCL/ZQCS commands.
 * Note: Ensure this is less than or equal to t_xs_x32.
 * Unit: Multiples of 32 DFI clock cycles.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG8 . T_XS_FAST_X32
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG8_T_XS_FAST_X32(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG8_T_XS_FAST_X32     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG8_T_XS_FAST_X32(x)  VTSS_EXTRACT_BITFIELD(x,24,7)


/**
 * \brief SDRAM Timing Register 9
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG9
 */
#define VTSS_DDR_UMCTL2_DRAMTMG9             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x49)

/**
 * \brief
 * Minimum time from write command to read command for different bank
 * group.  This must include time for bus turn-around and all PHY and
 * system requirements.
 *
 * After the PHY has completed training, the value programmed may need to
 * be increased.  Please see the relevant PHY databook for details of what
 * should be included here.
 *
 * The following calculations are minimum values, and do not include the
 * PHY/system requirements mentioned above:
 *
 * CWL + BL/2 + tWTR_S
 *
 * Where:
 *  - CWL: CAS write latency
 *  - BL: Burst length. This must match the value programmed in the BL bit
 * of the mode register to the SDRAM
 *  - tWTR_S: Internal write to read command delay for different bank
 * group. This comes directly from the SDRAM specification
 * WTR_S must be increased by one if DDR4 2tCK write preamble is used.
 * When the controller is operating in 1:2 mode, divide the value
 * calculated using the previous equation by 2, and round it up to next
 * integer.
 *
 * If your configuration has RANKCTL1.wr2rd_dr, write to read bus
 * turn-around between different physical ranks are controlled by
 * RANKCTL1.wr2rd_dr.
 *
 *
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 1, Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG9 . WR2RD_S
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG9_WR2RD_S(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG9_WR2RD_S     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG9_WR2RD_S(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * tRRD_S: This is the minimum time between activates from bank "a" to bank
 * "b" for different bank group.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tRRD_S/2) and round it up to the next integer value.
 * Present only in designs configured to support DDR4.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG9 . T_RRD_S
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG9_T_RRD_S(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG9_T_RRD_S     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG9_T_RRD_S(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * tCCD_S: This is the minimum time between two reads or two writes for
 * different bank group. For bank switching (from bank "a" to bank "b"),
 * the minimum time is this value + 1.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tCCD_S/2) and round it up to the next integer value.
 * Present only in designs configured to support DDR4.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG9 . T_CCD_S
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG9_T_CCD_S(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG9_T_CCD_S     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG9_T_CCD_S(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * DDR4 Write preamble mode.
 *
 *   Present only with MEMC_FREQ_RATIO=2.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG9 . DDR4_WR_PREAMBLE
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG9_DDR4_WR_PREAMBLE(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG9_DDR4_WR_PREAMBLE  VTSS_BIT(30)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG9_DDR4_WR_PREAMBLE(x)  VTSS_EXTRACT_BITFIELD(x,30,1)


/**
 * \brief SDRAM Timing Register 10
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG10
 */
#define VTSS_DDR_UMCTL2_DRAMTMG10            VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x4a)

/**
 * \brief
 * Indicates the geardown hold time.
 * Minimum value of this register is 1. Zero is invalid.
 * For DDR4-2666 and DDR4-3200, this parameter is defined as 2 clks
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tGEAR_hold/2) and round it up to the next integer value.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * 'h1:
 * 'h2:
 * 'h3:

 *
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG10 . T_GEAR_HOLD
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG10_T_GEAR_HOLD(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG10_T_GEAR_HOLD     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG10_T_GEAR_HOLD(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * Indicates the geardown setup time.
 * Minimum value of this register is 1. Zero is invalid.
 * For DDR4-2666 and DDR4-3200, this parameter is defined as 2 clks
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tGEAR_setup/2) and round it up to the next integer value.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * 'h1:
 * 'h2:
 * 'h3:

 *
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG10 . T_GEAR_SETUP
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG10_T_GEAR_SETUP(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG10_T_GEAR_SETUP     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG10_T_GEAR_SETUP(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * Indicates a sync pulse to first valid command.
 * For DDR4-2666 and DDR4-3200, this parameter is defined as tMOD(min)
 * tMOD(min) is greater of 24nCK or 15ns
 * 15ns / .625ns = 24
 * Max value for this register is 24
 * When the controller is operating in 1:2 mode, program this to
 * (tCMD_GEAR/2) and round it up to the next integer value.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG10 . T_CMD_GEAR
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG10_T_CMD_GEAR(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG10_T_CMD_GEAR     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG10_T_CMD_GEAR(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/**
 * \brief
 * Indicates the time between MRS command and the sync pulse time.
 * This must be even number of clocks.
 * For DDR4-2666 and DDR4-3200, this parameter is defined as tMOD(min)+4nCK
 * tMOD(min) is greater of 24nCK or 15ns
 * 15ns / .625ns = 24
 * Max value for this register is 24+4 = 28
 * When the controller is operating in 1:2 mode, program this to
 * (tSYNC_GEAR/2) and round it up to the next integer value.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG10 . T_SYNC_GEAR
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG10_T_SYNC_GEAR(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG10_T_SYNC_GEAR     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG10_T_SYNC_GEAR(x)  VTSS_EXTRACT_BITFIELD(x,16,5)


/**
 * \brief SDRAM Timing Register 11
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG11
 */
#define VTSS_DDR_UMCTL2_DRAMTMG11            VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x4b)

/**
 * \brief
 * tCKMPE: This is the minimum valid clock requirement after MPSM entry.
 * Present only in designs configured to support DDR4.
 *
 * When the controller is operating in 1:2 frequency ratio mode, divide the
 * value calculated using the previous equation by 2, and round it up to
 * next integer.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG11 . T_CKMPE
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG11_T_CKMPE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG11_T_CKMPE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG11_T_CKMPE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * tMPX_S: This is the minimum time CS setup time to CKE.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tMPX_S/2) and round it up to the next integer value.
 * Present only in designs configured to support DDR4.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG11 . T_MPX_S
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG11_T_MPX_S(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG11_T_MPX_S     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG11_T_MPX_S(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * tMPX_LH: This is the minimum CS_n Low hold time to CKE rising edge.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to RoundUp(tMPX_LH/2)+1.
 * Present only in designs configured to support DDR4.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG11 . T_MPX_LH
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG11_T_MPX_LH(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG11_T_MPX_LH     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG11_T_MPX_LH(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/**
 * \brief
 * tXMPDLL: This is the minimum Exit MPSM to commands requiring a locked
 * DLL.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tXMPDLL/2) and round it up to the next integer value.
 * Present only in designs configured to support DDR4.
 * Unit: Multiples of 32 DFI clock cycles.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG11 . POST_MPSM_GAP_X32
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG11_POST_MPSM_GAP_X32(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG11_POST_MPSM_GAP_X32     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG11_POST_MPSM_GAP_X32(x)  VTSS_EXTRACT_BITFIELD(x,24,7)


/**
 * \brief SDRAM Timing Register 12
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG12
 */
#define VTSS_DDR_UMCTL2_DRAMTMG12            VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x4c)

/**
 * \brief
 * tMRD_PDA: This is the Mode Register Set command cycle time in PDA mode.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tMRD_PDA/2) and round it up to the next integer value.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG12 . T_MRD_PDA
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG12_T_MRD_PDA(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG12_T_MRD_PDA     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG12_T_MRD_PDA(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * This bit is used only in DDR4. Cycles between MPR Write and other
 * command.
 * Set this to tMOD + AL (or tMOD + PL + AL if C/A parity is also used).
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tWR_MPR/2) and round it up to the next integer value.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG12 . T_WR_MPR
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG12_T_WR_MPR(x)  VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG12_T_WR_MPR     VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG12_T_WR_MPR(x)  VTSS_EXTRACT_BITFIELD(x,24,6)


/**
 * \brief SDRAM Timing Register 15
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG15
 */
#define VTSS_DDR_UMCTL2_DRAMTMG15            VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x4f)

/**
 * \brief
 * tSTAB: Stabilization time.
 * It is required in the following two cases for DDR3/DDR4 RDIMM:
 *  - When exiting power saving mode, if the clock is stopped, after
 * re-enabling it the clock must be stable for a time specified by tSTAB
 *  - In the case of input clock frequency change (DDR4)
 *  - After issuing control words that refers to clock timing
 *   (Specification: 6us for DDR3, 5us for DDR4)
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to recommended value divided by two and round it up to next
 * integer.
 * Unit: Multiples of 32 DFI clock cycles.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG15 . T_STAB_X32
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG15_T_STAB_X32(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG15_T_STAB_X32     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG15_T_STAB_X32(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Decides if using tSTAB when exiting DFI LP.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DRAMTMG15 . EN_DFI_LP_T_STAB
 */
#define  VTSS_F_DDR_UMCTL2_DRAMTMG15_EN_DFI_LP_T_STAB(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_UMCTL2_DRAMTMG15_EN_DFI_LP_T_STAB  VTSS_BIT(31)
#define  VTSS_X_DDR_UMCTL2_DRAMTMG15_EN_DFI_LP_T_STAB(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief ZQ Control Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ZQCTL0
 */
#define VTSS_DDR_UMCTL2_ZQCTL0               VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x60)

/**
 * \brief
 * tZQCS for DDR3/DD4/LPDDR2/LPDDR3, tZQLAT for LPDDR4: Number of DFI clock
 * cycles of NOP required after a ZQCS (ZQ calibration short)/MPC(ZQ Latch)
 * command is issued to SDRAM.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to tZQCS/2 and round it up to the next integer value.
 * This is only present for designs supporting DDR3/DDR4 or
 * LPDDR2/LPDDR3/LPDDR4 devices.
 * Unit: DFI clock cycles.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ZQCTL0 . T_ZQ_SHORT_NOP
 */
#define  VTSS_F_DDR_UMCTL2_ZQCTL0_T_ZQ_SHORT_NOP(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_DDR_UMCTL2_ZQCTL0_T_ZQ_SHORT_NOP     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_DDR_UMCTL2_ZQCTL0_T_ZQ_SHORT_NOP(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * \brief
 * tZQoper for DDR3/DDR4, tZQCL for LPDDR2/LPDDR3, tZQCAL for LPDDR4:
 * Number of DFI clock cycles of NOP required after a ZQCL (ZQ calibration
 * long)/MPC(ZQ Start) command is issued to SDRAM.
 * When the controller is operating in 1:2 frequency ratio mode:
 * DDR3/DDR4: program this to tZQoper/2 and round it up to the next integer
 * value.
 * LPDDR2/LPDDR3: program this to tZQCL/2 and round it up to the next
 * integer value.
 * LPDDR4: program this to tZQCAL/2 and round it up to the next integer
 * value.
 * This is only present for designs supporting DDR3/DDR4 or
 * LPDDR2/LPDDR3/LPDDR4 devices.
 * Unit: DFI clock cycles.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ZQCTL0 . T_ZQ_LONG_NOP
 */
#define  VTSS_F_DDR_UMCTL2_ZQCTL0_T_ZQ_LONG_NOP(x)  VTSS_ENCODE_BITFIELD(x,16,11)
#define  VTSS_M_DDR_UMCTL2_ZQCTL0_T_ZQ_LONG_NOP     VTSS_ENCODE_BITMASK(16,11)
#define  VTSS_X_DDR_UMCTL2_ZQCTL0_T_ZQ_LONG_NOP(x)  VTSS_EXTRACT_BITFIELD(x,16,11)

/**
 * \brief
 * Sets ZQCL command at Maximum Power Saving Mode exit.
 *
 *   This is only present for designs supporting DDR4 devices.
 *   Note: Do not issue ZQCL command at Maximum Power Save Mode exit if the
 * UMCTL2_SHARED_AC configuration parameter is set. Program it to 1'b1. The
 * software can send ZQCS after exiting MPSM mode.
 * Programming Mode: Static
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_ZQCTL0 . DIS_MPSMX_ZQCL
 */
#define  VTSS_F_DDR_UMCTL2_ZQCTL0_DIS_MPSMX_ZQCL(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_DDR_UMCTL2_ZQCTL0_DIS_MPSMX_ZQCL  VTSS_BIT(28)
#define  VTSS_X_DDR_UMCTL2_ZQCTL0_DIS_MPSMX_ZQCL(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Sets ZQ resistor sharing.
 *
 *   This is only present for designs supporting DDR3/DDR4 or
 * LPDDR2/LPDDR3/LPDDR4 devices.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_ZQCTL0 . ZQ_RESISTOR_SHARED
 */
#define  VTSS_F_DDR_UMCTL2_ZQCTL0_ZQ_RESISTOR_SHARED(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_DDR_UMCTL2_ZQCTL0_ZQ_RESISTOR_SHARED  VTSS_BIT(29)
#define  VTSS_X_DDR_UMCTL2_ZQCTL0_ZQ_RESISTOR_SHARED(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Sets issuing of ZQCL/MPC(ZQ calibration) command at
 * self-refresh/SR-Powerdown exit.
 *
 *   This is only present for designs supporting DDR3/DDR4 or
 * LPDDR2/LPDDR3/LPDDR4 devices.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_ZQCTL0 . DIS_SRX_ZQCL
 */
#define  VTSS_F_DDR_UMCTL2_ZQCTL0_DIS_SRX_ZQCL(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_UMCTL2_ZQCTL0_DIS_SRX_ZQCL  VTSS_BIT(30)
#define  VTSS_X_DDR_UMCTL2_ZQCTL0_DIS_SRX_ZQCL(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Sets uMCTL2 generation of ZQCS/MPC(ZQ calibration) command.
 *
 *   This is only present for designs supporting DDR3/DDR4 or
 * LPDDR2/LPDDR3/LPDDR4 devices.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_ZQCTL0 . DIS_AUTO_ZQ
 */
#define  VTSS_F_DDR_UMCTL2_ZQCTL0_DIS_AUTO_ZQ(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_UMCTL2_ZQCTL0_DIS_AUTO_ZQ  VTSS_BIT(31)
#define  VTSS_X_DDR_UMCTL2_ZQCTL0_DIS_AUTO_ZQ(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief ZQ Control Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ZQCTL1
 */
#define VTSS_DDR_UMCTL2_ZQCTL1               VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x61)

/**
 * \brief
 * Indicates the average interval to wait between automatically issuing
 * ZQCS (ZQ calibration short)/MPC(ZQ calibration) commands to
 * DDR3/DDR4/LPDDR2/LPDDR3/LPDDR4 devices.
 * Meaningless, if ZQCTL0.dis_auto_zq=1.
 * This is only present for designs supporting DDR3/DDR4 or
 * LPDDR2/LPDDR3/LPDDR4 devices.
 * Unit: Multiples of 1024 DFI clock cycles.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ZQCTL1 . T_ZQ_SHORT_INTERVAL_X1024
 */
#define  VTSS_F_DDR_UMCTL2_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_DDR_UMCTL2_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_DDR_UMCTL2_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/**
 * \brief DFI Timing Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFITMG0
 */
#define VTSS_DDR_UMCTL2_DFITMG0              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x64)

/**
 * \brief
 * Write latency.
 * Number of clocks from the write command to write data enable
 * (dfi_wrdata_en). This corresponds to the DFI timing parameter
 * tphy_wrlat.
 * Refer to PHY specification for correct value.Note that, depending on the
 * PHY, if using RDIMM/LRDIMM, it may be necessary to use the adjusted
 * value of CL in the calculation of tphy_wrlat. This is to compensate for
 * the extra cycles of latency through the RDIMM/LRDIMM.
 * For LPDDR4, dfi_tphy_wrlat>60 is not supported.
 * Unit: DFI clock cycles or DFI PHY clock cycles, depending on
 * DFITMG0.dfi_wrdata_use_dfi_phy_clk.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DFITMG0 . DFI_TPHY_WRLAT
 */
#define  VTSS_F_DDR_UMCTL2_DFITMG0_DFI_TPHY_WRLAT(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_UMCTL2_DFITMG0_DFI_TPHY_WRLAT     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_UMCTL2_DFITMG0_DFI_TPHY_WRLAT(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * Specifies the number of clock cycles between when dfi_wrdata_en is
 * asserted to when the associated write data is driven on the dfi_wrdata
 * signal. This corresponds to the DFI timing parameter tphy_wrdata. For
 * more information on correct value, see PHY specification. Note, maximum
 * supported value is 8.
 * Unit: DFI clock cycles or DFI PHY clock cycles, depending on
 * DFITMG0.dfi_wrdata_use_dfi_phy_clk.
 * Programming Mode: Quasi-dynamic Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DFITMG0 . DFI_TPHY_WRDATA
 */
#define  VTSS_F_DDR_UMCTL2_DFITMG0_DFI_TPHY_WRDATA(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_DDR_UMCTL2_DFITMG0_DFI_TPHY_WRDATA     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_DDR_UMCTL2_DFITMG0_DFI_TPHY_WRDATA(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/**
 * \brief
 * Defines whether dfi_wrdata_en/dfi_wrdata/dfi_wrdata_mask is generated
 * using HDR (DFI clock) or SDR (DFI PHY clock) values.
 * Selects whether value in DFITMG0.dfi_tphy_wrlat is in terms of HDR (DFI
 * clock) or SDR (DFI PHY clock) cycles.
 * Selects whether value in DFITMG0.dfi_tphy_wrdata is in terms of HDR (DFI
 * clock) or SDR (DFI PHY clock) cycles.
 *
 *   Refer to PHY specification for correct value.
 *   If using a Synopsys DWC DDR3/2 PHY, DWC DDR2/3-Lite/mDDR PHY, DWC DDR
 * multiPHY or DWC Gen2 DDR multiPHY, this field must be set to 0;
 * otherwise:
 *  - If MEMC_PROG_FREQ_RATIO=1 and MSTR.frequency_ratio=1, this field must
 * be set to 0
 *  - Else, it must be set to 1
 *
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFITMG0 . DFI_WRDATA_USE_DFI_PHY_CLK
 */
#define  VTSS_F_DDR_UMCTL2_DFITMG0_DFI_WRDATA_USE_DFI_PHY_CLK(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_DDR_UMCTL2_DFITMG0_DFI_WRDATA_USE_DFI_PHY_CLK  VTSS_BIT(15)
#define  VTSS_X_DDR_UMCTL2_DFITMG0_DFI_WRDATA_USE_DFI_PHY_CLK(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Time from the assertion of a read command on the DFI interface to the
 * assertion of the dfi_rddata_en signal.
 * Refer to PHY specification for correct value.
 * This corresponds to the DFI parameter trddata_en. Note that, depending
 * on the PHY, if using RDIMM/LRDIMM, it may be necessary to use the
 * adjusted value of CL in the calculation of trddata_en. This is to
 * compensate for the extra cycles of latency through the RDIMM/LRDIMM.
 * Unit: DFI clock cycles or DFI PHY clock cycles, depending on
 * DFITMG0.dfi_rddata_use_dfi_phy_clk.
 * Programming Mode: Quasi-dynamic Group 1, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DFITMG0 . DFI_T_RDDATA_EN
 */
#define  VTSS_F_DDR_UMCTL2_DFITMG0_DFI_T_RDDATA_EN(x)  VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_DDR_UMCTL2_DFITMG0_DFI_T_RDDATA_EN     VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_DDR_UMCTL2_DFITMG0_DFI_T_RDDATA_EN(x)  VTSS_EXTRACT_BITFIELD(x,16,7)

/**
 * \brief
 * Defines whether dfi_rddata_en/dfi_rddata/dfi_rddata_valid is generated
 * using HDR (DFI clock) or SDR (DFI PHY clock) values.
 * Selects whether value in DFITMG0.dfi_t_rddata_en is in terms of HDR (DFI
 * clock) or SDR (DFI PHY clock) cycles.
 *
 *   Refer to PHY specification for correct value.
 * If using a Synopsys DWC DDR3/2 PHY, DWC DDR2/3-Lite/mDDR PHY, DWC DDR
 * multiPHY or DWC Gen2 DDR multiPHY, this field must be set to 0;
 * otherwise:
 *  - If MEMC_PROG_FREQ_RATIO=1 and MSTR.frequency_ratio=1, this field must
 * be set to 0
 *  - Else, it must be set to 1
 *
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFITMG0 . DFI_RDDATA_USE_DFI_PHY_CLK
 */
#define  VTSS_F_DDR_UMCTL2_DFITMG0_DFI_RDDATA_USE_DFI_PHY_CLK(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_DDR_UMCTL2_DFITMG0_DFI_RDDATA_USE_DFI_PHY_CLK  VTSS_BIT(23)
#define  VTSS_X_DDR_UMCTL2_DFITMG0_DFI_RDDATA_USE_DFI_PHY_CLK(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Specifies the number of DFI clock cycles after an assertion or
 * de-assertion of the DFI control signals that the control signals at the
 * PHY-DRAM interface reflect the assertion or de-assertion.
 * If the DFI clock and the memory clock are not phase-aligned, this timing
 * parameter must be rounded up to the next integer value. Note that if
 * using RDIMM/LRDIMM, it is necessary to increment this parameter by
 * RDIMM's/LRDIMM's extra cycle of latency in terms of DFI clock.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DFITMG0 . DFI_T_CTRL_DELAY
 */
#define  VTSS_F_DDR_UMCTL2_DFITMG0_DFI_T_CTRL_DELAY(x)  VTSS_ENCODE_BITFIELD(x,24,5)
#define  VTSS_M_DDR_UMCTL2_DFITMG0_DFI_T_CTRL_DELAY     VTSS_ENCODE_BITMASK(24,5)
#define  VTSS_X_DDR_UMCTL2_DFITMG0_DFI_T_CTRL_DELAY(x)  VTSS_EXTRACT_BITFIELD(x,24,5)


/**
 * \brief DFI Timing Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFITMG1
 */
#define VTSS_DDR_UMCTL2_DFITMG1              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x65)

/**
 * \brief
 * Specifies the number of DFI clock cycles from the de-assertion of the
 * dfi_dram_clk_disable signal on the DFI until the first valid rising edge
 * of the clock to the DRAM memory devices, at the PHY-DRAM boundary.
 * If the DFI clock and the memory clock are not phase aligned, this timing
 * parameter must be rounded up to the next integer value.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DFITMG1 . DFI_T_DRAM_CLK_ENABLE
 */
#define  VTSS_F_DDR_UMCTL2_DFITMG1_DFI_T_DRAM_CLK_ENABLE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_UMCTL2_DFITMG1_DFI_T_DRAM_CLK_ENABLE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_UMCTL2_DFITMG1_DFI_T_DRAM_CLK_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * Specifies the number of DFI clock cycles from the assertion of the
 * dfi_dram_clk_disable signal on the DFI until the clock to the DRAM
 * memory devices, at the PHY-DRAM boundary, maintains a low value.
 * If the DFI clock and the memory clock are not phase aligned, this timing
 * parameter must be rounded up to the next integer value.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DFITMG1 . DFI_T_DRAM_CLK_DISABLE
 */
#define  VTSS_F_DDR_UMCTL2_DFITMG1_DFI_T_DRAM_CLK_DISABLE(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_DDR_UMCTL2_DFITMG1_DFI_T_DRAM_CLK_DISABLE     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_DDR_UMCTL2_DFITMG1_DFI_T_DRAM_CLK_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/**
 * \brief
 * Specifies the number of DFI clock cycles between when the dfi_wrdata_en
 * signal is asserted and when the corresponding write data transfer is
 * completed on the DRAM bus.
 * This corresponds to the DFI timing parameter twrdata_delay.
 * For more information on correct value, see PHY specification.
 * For DFI 3.0 PHY, set to twrdata_delay, a new timing parameter introduced
 * in DFI 3.0.
 * For DFI 2.1 PHY, set to tphy_wrdata + (delay of DFI write data to the
 * DRAM).
 * Value to be programmed is in terms of DFI clocks, not PHY clocks.
 * In FREQ_RATIO=2, divide PHY's value by 2 and round up to next integer.
 * If using DFITMG0.dfi_wrdata_use_dfi_phy_clk=1, add 1 to the value.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DFITMG1 . DFI_T_WRDATA_DELAY
 */
#define  VTSS_F_DDR_UMCTL2_DFITMG1_DFI_T_WRDATA_DELAY(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_DDR_UMCTL2_DFITMG1_DFI_T_WRDATA_DELAY     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_DDR_UMCTL2_DFITMG1_DFI_T_WRDATA_DELAY(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/**
 * \brief
 * Specifies the number of DFI PHY clock cycles between when the dfi_cs
 * signal is asserted and when the associated dfi_parity_in signal is
 * driven.
 * Unit: DFI PHY clock cycles.
 * Programming Mode: Quasi-dynamic Group 4
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h3:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFITMG1 . DFI_T_PARIN_LAT
 */
#define  VTSS_F_DDR_UMCTL2_DFITMG1_DFI_T_PARIN_LAT(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_DDR_UMCTL2_DFITMG1_DFI_T_PARIN_LAT     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_DDR_UMCTL2_DFITMG1_DFI_T_PARIN_LAT(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * Specifies the number of DFI PHY clock cycles between when the dfi_cs
 * signal is asserted and when the associated command is driven.
 * This field is used for CAL mode, must be set to '0' or tCAL, which
 * matches the CAL mode register setting in the DRAM.
 * When enabling CAL mode with RDIMM/LRDIMM, this field must be set to
 * tCAL-CLA (Command Latency Adder). For more information on CLA, see JEDEC
 * DDR4 Register Specification.
 * If the PHY can add the latency for CAL mode, this must be set to '0'.
 * Valid Range: 0 to 8.
 * Unit: DFI PHY clock cycles.
 * Programming Mode: Quasi-dynamic Group 2, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DFITMG1 . DFI_T_CMD_LAT
 */
#define  VTSS_F_DDR_UMCTL2_DFITMG1_DFI_T_CMD_LAT(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_DDR_UMCTL2_DFITMG1_DFI_T_CMD_LAT     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_DDR_UMCTL2_DFITMG1_DFI_T_CMD_LAT(x)  VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief DFI Low Power Configuration Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFILPCFG0
 */
#define VTSS_DDR_UMCTL2_DFILPCFG0            VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x66)

/**
 * \brief
 * Enables DFI Low Power interface handshaking during Power Down
 * Entry/Exit.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFILPCFG0 . DFI_LP_EN_PD
 */
#define  VTSS_F_DDR_UMCTL2_DFILPCFG0_DFI_LP_EN_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_DFILPCFG0_DFI_LP_EN_PD  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_DFILPCFG0_DFI_LP_EN_PD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Indicates the value in DFI clock cycles to drive on dfi_lp_wakeup signal
 * when Power Down mode is entered.
 * Determines the DFI's tlp_wakeup time.
 *
 *   Unit: DFI clock cycles.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h3:
 * 'h4:
 * 'h5:
 * 'h6:
 * 'h7:
 * 'h8:
 * 'h9:
 * 'ha:
 * 'hb:
 * 'hc:
 * 'hd:
 * 'he:
 * 'hf:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFILPCFG0 . DFI_LP_WAKEUP_PD
 */
#define  VTSS_F_DDR_UMCTL2_DFILPCFG0_DFI_LP_WAKEUP_PD(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_DDR_UMCTL2_DFILPCFG0_DFI_LP_WAKEUP_PD     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_DDR_UMCTL2_DFILPCFG0_DFI_LP_WAKEUP_PD(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * Enables DFI Low Power interface handshaking during self-refresh
 * Entry/Exit.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFILPCFG0 . DFI_LP_EN_SR
 */
#define  VTSS_F_DDR_UMCTL2_DFILPCFG0_DFI_LP_EN_SR(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DDR_UMCTL2_DFILPCFG0_DFI_LP_EN_SR  VTSS_BIT(8)
#define  VTSS_X_DDR_UMCTL2_DFILPCFG0_DFI_LP_EN_SR(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Indicates the value in DFI clock cycles to drive on dfi_lp_wakeup signal
 * when self-refresh mode is entered.
 * Determines the DFI's tlp_wakeup time.
 *
 *   Unit: DFI clock cycles.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h3:
 * 'h4:
 * 'h5:
 * 'h6:
 * 'h7:
 * 'h8:
 * 'h9:
 * 'ha:
 * 'hb:
 * 'hc:
 * 'hd:
 * 'he:
 * 'hf:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFILPCFG0 . DFI_LP_WAKEUP_SR
 */
#define  VTSS_F_DDR_UMCTL2_DFILPCFG0_DFI_LP_WAKEUP_SR(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_DDR_UMCTL2_DFILPCFG0_DFI_LP_WAKEUP_SR     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_DDR_UMCTL2_DFILPCFG0_DFI_LP_WAKEUP_SR(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * Indicates the setting in DFI clock cycles for DFI's tlp_resp time.
 * Same value is used for both Power Down, self-refresh, Deep Power Down
 * and Maximum Power Saving modes.
 * For more information on recommended values, see PHY databook
 * Unit: DFI clock cycles.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DFILPCFG0 . DFI_TLP_RESP
 */
#define  VTSS_F_DDR_UMCTL2_DFILPCFG0_DFI_TLP_RESP(x)  VTSS_ENCODE_BITFIELD(x,24,5)
#define  VTSS_M_DDR_UMCTL2_DFILPCFG0_DFI_TLP_RESP     VTSS_ENCODE_BITMASK(24,5)
#define  VTSS_X_DDR_UMCTL2_DFILPCFG0_DFI_TLP_RESP(x)  VTSS_EXTRACT_BITFIELD(x,24,5)


/**
 * \brief DFI Low Power Configuration Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFILPCFG1
 */
#define VTSS_DDR_UMCTL2_DFILPCFG1            VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x67)

/**
 * \brief
 * Enables DFI Low Power interface handshaking during Maximum Power Saving
 * Mode Entry/Exit.
 *
 *   This is only present for designs supporting DDR4 devices.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFILPCFG1 . DFI_LP_EN_MPSM
 */
#define  VTSS_F_DDR_UMCTL2_DFILPCFG1_DFI_LP_EN_MPSM(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_DFILPCFG1_DFI_LP_EN_MPSM  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_DFILPCFG1_DFI_LP_EN_MPSM(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Indicates the value in DFI clock cycles to drive on dfi_lp_wakeup signal
 * when Maximum Power Saving Mode is entered.
 * Determines the DFI's tlp_wakeup time.
 *
 *   This is only present for designs supporting DDR4 devices.
 * Unit: DFI clock cycles.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h3:
 * 'h4:
 * 'h5:
 * 'h6:
 * 'h7:
 * 'h8:
 * 'h9:
 * 'ha:
 * 'hb:
 * 'hc:
 * 'hd:
 * 'he:
 * 'hf:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFILPCFG1 . DFI_LP_WAKEUP_MPSM
 */
#define  VTSS_F_DDR_UMCTL2_DFILPCFG1_DFI_LP_WAKEUP_MPSM(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_DDR_UMCTL2_DFILPCFG1_DFI_LP_WAKEUP_MPSM     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_DDR_UMCTL2_DFILPCFG1_DFI_LP_WAKEUP_MPSM(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief DFI Update Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFIUPD0
 */
#define VTSS_DDR_UMCTL2_DFIUPD0              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x68)

/**
 * \brief
 * Specifies the minimum number of DFI clock cycles that the
 * dfi_ctrlupd_req signal must be asserted. The uMCTL2 expects the PHY to
 * respond within this time. If the PHY does not respond, the uMCTL2
 * de-asserts dfi_ctrlupd_req after dfi_t_ctrlup_min + 2 cycles. Lowest
 * value to assign to this variable is 0x1.
 * Unit: DFI clock cycles.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DFIUPD0 . DFI_T_CTRLUP_MIN
 */
#define  VTSS_F_DDR_UMCTL2_DFIUPD0_DFI_T_CTRLUP_MIN(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_DDR_UMCTL2_DFIUPD0_DFI_T_CTRLUP_MIN     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_DDR_UMCTL2_DFIUPD0_DFI_T_CTRLUP_MIN(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * \brief
 * Specifies the maximum number of DFI clock cycles that the
 * dfi_ctrlupd_req signal can assert. Lowest value to assign to this
 * variable is 0x40.
 * Unit: DFI clock cycles.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DFIUPD0 . DFI_T_CTRLUP_MAX
 */
#define  VTSS_F_DDR_UMCTL2_DFIUPD0_DFI_T_CTRLUP_MAX(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_DDR_UMCTL2_DFIUPD0_DFI_T_CTRLUP_MAX     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_DDR_UMCTL2_DFIUPD0_DFI_T_CTRLUP_MAX(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/**
 * \brief
 * Selects dfi_ctrlupd_req requirements at SRX.
 *
 *   If DFIUPD0.dis_auto_ctrlupd_srx=1, this register has no impact,
 * because no dfi_ctrlupd_req is issued when SRX.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFIUPD0 . CTRLUPD_PRE_SRX
 */
#define  VTSS_F_DDR_UMCTL2_DFIUPD0_CTRLUPD_PRE_SRX(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_DDR_UMCTL2_DFIUPD0_CTRLUPD_PRE_SRX  VTSS_BIT(29)
#define  VTSS_X_DDR_UMCTL2_DFIUPD0_CTRLUPD_PRE_SRX(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Sets the automatic dfi_ctrlupd_req generation by the uMCTL2 at
 * self-refresh exit.
 * Programming Mode: Static
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFIUPD0 . DIS_AUTO_CTRLUPD_SRX
 */
#define  VTSS_F_DDR_UMCTL2_DFIUPD0_DIS_AUTO_CTRLUPD_SRX(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_UMCTL2_DFIUPD0_DIS_AUTO_CTRLUPD_SRX  VTSS_BIT(30)
#define  VTSS_X_DDR_UMCTL2_DFIUPD0_DIS_AUTO_CTRLUPD_SRX(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Sets the automatic dfi_ctrlupd_req generation by the uMCTL2.
 * The controller must issue the dfi_ctrlupd_req signal using register
 * DBGCMD.ctrlupd.
 *
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFIUPD0 . DIS_AUTO_CTRLUPD
 */
#define  VTSS_F_DDR_UMCTL2_DFIUPD0_DIS_AUTO_CTRLUPD(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_UMCTL2_DFIUPD0_DIS_AUTO_CTRLUPD  VTSS_BIT(31)
#define  VTSS_X_DDR_UMCTL2_DFIUPD0_DIS_AUTO_CTRLUPD(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief DFI Update Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFIUPD1
 */
#define VTSS_DDR_UMCTL2_DFIUPD1              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x69)

/**
 * \brief
 * This is the maximum amount of time between uMCTL2 initiated DFI update
 * requests.
 * This timer resets with each update request; when the timer expires
 * dfi_ctrlupd_req is sent and traffic is blocked until the
 * dfi_ctrlupd_ackx is received.
 * PHY can use this idle time to recalibrate the delay lines to the DLLs.
 * The DFI controller update is also used to reset PHY FIFO pointers in
 * case of data capture errors.
 * Updates are required to maintain calibration over PVT, but frequent
 * updates may impact performance. Minimum allowed value for this field is
 * 1.
 * Note: Value programmed for DFIUPD1.dfi_t_ctrlupd_interval_max_x1024 must
 * be greater than DFIUPD1.dfi_t_ctrlupd_interval_min_x1024.
 * Unit: Multiples of 1024 DFI clock cycles.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DFIUPD1 . DFI_T_CTRLUPD_INTERVAL_MAX_X1024
 */
#define  VTSS_F_DDR_UMCTL2_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_UMCTL2_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_UMCTL2_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * This is the minimum amount of time between uMCTL2 initiated DFI update
 * requests (which is executed whenever the uMCTL2 is idle).
 * Set this number higher to reduce the frequency of update requests, which
 * can have a small impact on the latency of the first read request when
 * the uMCTL2 is idle.
 * The minimum allowed value for this field is 1.
 * Unit: Multiples of 1024 DFI clock cycles.
 * For more information on how to program this register field, see "Note 1"
 * in the "Notes on Timing Registers" section.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DFIUPD1 . DFI_T_CTRLUPD_INTERVAL_MIN_X1024
 */
#define  VTSS_F_DDR_UMCTL2_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_UMCTL2_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_UMCTL2_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024(x)  VTSS_EXTRACT_BITFIELD(x,16,8)


/**
 * \brief DFI Update Register 2
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFIUPD2
 */
#define VTSS_DDR_UMCTL2_DFIUPD2              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x6a)

/**
 * \brief
 * Enables the support for acknowledging PHY-initiated updates.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFIUPD2 . DFI_PHYUPD_EN
 */
#define  VTSS_F_DDR_UMCTL2_DFIUPD2_DFI_PHYUPD_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_UMCTL2_DFIUPD2_DFI_PHYUPD_EN  VTSS_BIT(31)
#define  VTSS_X_DDR_UMCTL2_DFIUPD2_DFI_PHYUPD_EN(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief DFI Miscellaneous Control Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFIMISC
 */
#define VTSS_DDR_UMCTL2_DFIMISC              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x6c)

/**
 * \brief
 * PHY initialization complete enable signal.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFIMISC . DFI_INIT_COMPLETE_EN
 */
#define  VTSS_F_DDR_UMCTL2_DFIMISC_DFI_INIT_COMPLETE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_DFIMISC_DFI_INIT_COMPLETE_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_DFIMISC_DFI_INIT_COMPLETE_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * DBI implemented in DDRC or PHY.
 *
 *   Present only in designs configured to support DDR4 and LPDDR4.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFIMISC . PHY_DBI_MODE
 */
#define  VTSS_F_DDR_UMCTL2_DFIMISC_PHY_DBI_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_DFIMISC_PHY_DBI_MODE  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_DFIMISC_PHY_DBI_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Sets support of ctl_idle signal, which is non-DFI related pin specific
 * to certain Synopsys PHYs.
 * For more information on ctl_idle functionality, see signal description
 * of ctl_idle signal.
 *
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFIMISC . CTL_IDLE_EN
 */
#define  VTSS_F_DDR_UMCTL2_DFIMISC_CTL_IDLE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_DFIMISC_CTL_IDLE_EN  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_DFIMISC_CTL_IDLE_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * PHY init start request signal.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFIMISC . DFI_INIT_START
 */
#define  VTSS_F_DDR_UMCTL2_DFIMISC_DFI_INIT_START(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_UMCTL2_DFIMISC_DFI_INIT_START  VTSS_BIT(5)
#define  VTSS_X_DDR_UMCTL2_DFIMISC_DFI_INIT_START(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Sets PHY specific Dynamic Tristating.
 * This functionality works only in DFI 1:2 frequency ratio mode regardless
 * of MSTR.en_2t_timing_mode, so if either of the following condition is
 * met no special IDLE command is issued on the DFI bus:
 *  - MEMC_FREQ_RATIO==1
 *  - MEMC_PROG_FREQ_RATIO=1 and MSTR.frequency_ratio=1
 * The special IDLE command means the following codes with the case where
 * all the dfi_cs is 1:
 *  - (phase 0 and 1) dfi_ras_n=1
 *  - (phase 0 and 1) dfi_cas_n= 1
 *  - phase 0 and 1) dfi_we_n= 1
 *  - (phase 0 and 1) dfi_bank [0]= 0
 *  - (phase 0 and 1) dfi_act_n= 1
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFIMISC . DIS_DYN_ADR_TRI
 */
#define  VTSS_F_DDR_UMCTL2_DFIMISC_DIS_DYN_ADR_TRI(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DDR_UMCTL2_DFIMISC_DIS_DYN_ADR_TRI  VTSS_BIT(6)
#define  VTSS_X_DDR_UMCTL2_DFIMISC_DIS_DYN_ADR_TRI(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Indicates the operating frequency of the system. The number of supported
 * frequencies and the mapping of signal values to clock frequencies are
 * defined by the PHY.
 * Programming Mode: Quasi-dynamic Group 1
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DFIMISC . DFI_FREQUENCY
 */
#define  VTSS_F_DDR_UMCTL2_DFIMISC_DFI_FREQUENCY(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_DDR_UMCTL2_DFIMISC_DFI_FREQUENCY     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_DDR_UMCTL2_DFIMISC_DFI_FREQUENCY(x)  VTSS_EXTRACT_BITFIELD(x,8,5)


/**
 * \brief DFI Timing Register 3
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFITMG3
 */
#define VTSS_DDR_UMCTL2_DFITMG3              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x6e)

/**
 * \brief
 * The delay from dfi_geardown_en assertion to the time of the PHY being
 * ready to receive commands.
 * Refer to PHY specification for correct value.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tgeardown_delay/2) and round it up to the next integer value.
 * Unit: DFI clock cycles.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DFITMG3 . DFI_T_GEARDOWN_DELAY
 */
#define  VTSS_F_DDR_UMCTL2_DFITMG3_DFI_T_GEARDOWN_DELAY(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_UMCTL2_DFITMG3_DFI_T_GEARDOWN_DELAY     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_UMCTL2_DFITMG3_DFI_T_GEARDOWN_DELAY(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief DFI Status Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFISTAT
 */
#define VTSS_DDR_UMCTL2_DFISTAT              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x6f)

/**
 * \brief
 * This a status flag register which announces when the DFI initialization
 * has been completed. The DFI INIT triggered by dfi_init_start signal and
 * then the dfi_init_complete flag is polled to know when the
 * initialization is done.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFISTAT . DFI_INIT_COMPLETE
 */
#define  VTSS_F_DDR_UMCTL2_DFISTAT_DFI_INIT_COMPLETE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_DFISTAT_DFI_INIT_COMPLETE  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_DFISTAT_DFI_INIT_COMPLETE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Stores the value of the dfi_lp_ack input to the controller.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFISTAT . DFI_LP_ACK
 */
#define  VTSS_F_DDR_UMCTL2_DFISTAT_DFI_LP_ACK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_DFISTAT_DFI_LP_ACK  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_DFISTAT_DFI_LP_ACK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/**
 * \brief DM/DBI Control Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DBICTL
 */
#define VTSS_DDR_UMCTL2_DBICTL               VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x70)

/**
 * \brief
 * Indicates the DM enable signal in DDRC.
 *
 *   This signal must be set the same logical value as DRAM's mode
 * register.
 *  - DDR4 - Set this to same value as MR5 bit A10. When x4 devices are
 * used, this signal must be set to 0
 *  - LPDDR4 - Set this to inverted value of MR13[5] which is opposite
 * polarity from this signal
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBICTL . DM_EN
 */
#define  VTSS_F_DDR_UMCTL2_DBICTL_DM_EN(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_DBICTL_DM_EN       VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_DBICTL_DM_EN(x)    VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Write DBI enable signal in DDRC.
 *
 *   This signal must be set the same value as DRAM's mode register.
 *  - DDR4 - MR5 bit A11. When x4 devices are used, this signal must be set
 * to 0
 *  - LPDDR4 - MR3[7]
 * Programming Mode: Quasi-dynamic Group 1
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBICTL . WR_DBI_EN
 */
#define  VTSS_F_DDR_UMCTL2_DBICTL_WR_DBI_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_DBICTL_WR_DBI_EN   VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_DBICTL_WR_DBI_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Read DBI enable signal in DDRC.
 *
 *   This signal must be set the same value as DRAM's mode register.
 *  - DDR4 - MR5 bit A12. When x4 devices are used, this signal must be set
 * to 0
 *  - LPDDR4 - MR3[6]
 * Programming Mode: Quasi-dynamic Group 1
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBICTL . RD_DBI_EN
 */
#define  VTSS_F_DDR_UMCTL2_DBICTL_RD_DBI_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_UMCTL2_DBICTL_RD_DBI_EN   VTSS_BIT(2)
#define  VTSS_X_DDR_UMCTL2_DBICTL_RD_DBI_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


/**
 * \brief DFI PHY Master
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFIPHYMSTR
 */
#define VTSS_DDR_UMCTL2_DFIPHYMSTR           VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x71)

/**
 * \brief
 * Enables the PHY Master Interface.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DFIPHYMSTR . DFI_PHYMSTR_EN
 */
#define  VTSS_F_DDR_UMCTL2_DFIPHYMSTR_DFI_PHYMSTR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_DFIPHYMSTR_DFI_PHYMSTR_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_DFIPHYMSTR_DFI_PHYMSTR_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * The programmed value x32 is the maximum number of DFI clock cycles that
 * allows to send pending refreshes before starting self-refresh entry
 * process.
 * - 0x00 - 0 DFI clock cycles, no delay
 * - 0x01 - 32 DFI clock cycles
 * - ...
 * - 0xFF - 8160 DFI clock cycles
 * Unit: Multiples of 32 DFI clock cycles.
 * Note: Use as default value (0x80) unless Synopsys suggest to change
 * value.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DFIPHYMSTR . DFI_PHYMSTR_BLK_REF_X32
 */
#define  VTSS_F_DDR_UMCTL2_DFIPHYMSTR_DFI_PHYMSTR_BLK_REF_X32(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DDR_UMCTL2_DFIPHYMSTR_DFI_PHYMSTR_BLK_REF_X32     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DDR_UMCTL2_DFIPHYMSTR_DFI_PHYMSTR_BLK_REF_X32(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief Address Map Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP0
 */
#define VTSS_DDR_UMCTL2_ADDRMAP0             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x80)

/**
 * \brief
 * Selects the HIF address bit used as rank address bit 0.
 * Valid Range: 0 to 29, and 31
 * Internal Base: 6
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 31 and then rank address bit 0 is set to 0.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP0 . ADDRMAP_CS_BIT0
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP0_ADDRMAP_CS_BIT0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP0_ADDRMAP_CS_BIT0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP0_ADDRMAP_CS_BIT0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief Address Map Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP1
 */
#define VTSS_DDR_UMCTL2_ADDRMAP1             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x81)

/**
 * \brief
 * Selects the HIF address bits used as bank address bit 0.
 * Valid Range: 0 to 32, and 63
 * Internal Base: 2
 * The selected HIF address bit for each of the bank address bits is
 * determined by adding the internal base to the value of this field.
 * If unused, set to 63 and then bank address bit 0 is set to 0.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP1 . ADDRMAP_BANK_B0
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP1_ADDRMAP_BANK_B0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP1_ADDRMAP_BANK_B0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP1_ADDRMAP_BANK_B0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * Selects the HIF address bits used as bank address bit 1.
 * Valid Range: 0 to 32, and 63
 * Internal Base: 3
 * The selected HIF address bit for each of the bank address bits is
 * determined by adding the internal base to the value of this field.
 * If unused, set to 63 and then bank address bit 1 is set to 0.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP1 . ADDRMAP_BANK_B1
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP1_ADDRMAP_BANK_B1(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP1_ADDRMAP_BANK_B1     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP1_ADDRMAP_BANK_B1(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/**
 * \brief
 * Selects the HIF address bit used as bank address bit 2.
 * Valid Range: 0 to 31, and 63
 * Internal Base: 4
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 63 and then bank address bit 2 is set to 0.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP1 . ADDRMAP_BANK_B2
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP1_ADDRMAP_BANK_B2(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP1_ADDRMAP_BANK_B2     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP1_ADDRMAP_BANK_B2(x)  VTSS_EXTRACT_BITFIELD(x,16,6)


/**
 * \brief Address Map Register 2
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP2
 */
#define VTSS_DDR_UMCTL2_ADDRMAP2             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x82)

/**
 * \brief
 *
 *  - Full bus width mode - Selects the HIF address bit used as column
 * address bit 2
 *  - Half bus width mode - Selects the HIF address bit used as column
 * address bit 3
 *  - Quarter bus width mode - Selects the HIF address bit used as column
 * address bit 4
 * Valid Range: 0 to 7
 * Internal Base: 2
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * Note, if UMCTL2_INCL_ARB=1 and MEMC_BURST_LENGTH=8, it is required to
 * program this to 0 unless:
 *  - In Half or Quarter bus width (MSTR.data_bus_width!=00) and
 *  - PCCFG.bl_exp_mode==1 and either
 *  - In DDR4 and ADDRMAP8.addrmap_bg_b0==0 or
 *  - In LPDDR4 and ADDRMAP1.addrmap_bank_b0==0
 * If UMCTL2_INCL_ARB=1 and MEMC_BURST_LENGTH=16, it is required to program
 * this to 0 unless:
 *  - In Half or Quarter bus width (MSTR.data_bus_width!=00) and
 *  - PCCFG.bl_exp_mode==1 and
 *  - In DDR4 and ADDRMAP8.addrmap_bg_b0==0
 * Otherwise, if MEMC_BURST_LENGTH=8 and Full Bus Width
 * (MSTR.data_bus_width==00), it is recommended to program this to 0 so
 * that HIF[2] maps to column address bit 2.
 *
 * If MEMC_BURST_LENGTH=16 and Full Bus Width (MSTR.data_bus_width==00), it
 * is recommended to program this to 0 so that HIF[2] maps to column
 * address bit 2.
 * If MEMC_BURST_LENGTH=16 and Half Bus Width (MSTR.data_bus_width==01), it
 * is recommended to program this to 0 so that HIF[2] maps to column
 * address bit 3.
 *
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP2 . ADDRMAP_COL_B2
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP2_ADDRMAP_COL_B2(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP2_ADDRMAP_COL_B2     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP2_ADDRMAP_COL_B2(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 *
 *  - Full bus width mode - Selects the HIF address bit used as column
 * address bit 3
 *  - Half bus width mode - Selects the HIF address bit used as column
 * address bit 4
 *  - Quarter bus width mode - Selects the HIF address bit used as column
 * address bit 5
 * Valid Range: 0 to 7, x. x indicates a valid value in the inline ECC
 * configuration.
 * Internal Base: 3
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * Note, if UMCTL2_INCL_ARB=1, MEMC_BURST_LENGTH=16, Full bus width
 * (MSTR.data_bus_width=00) and BL16 (MSTR.burst_rdwr=1000), it is
 * recommended to program this to 0.
 *  In Inline ECC configuration (MEMC_INLINE_ECC=1) and Inline ECC mode is
 * enabled (ECCCFG0.ecc_mode=4), if MEMC_BURST_LENGTH is 16, number of
 * column address is 10 and work on half bus width mode, column bit 8,
 * column bit 7 and column bit 3 must map to the highest 3 valid HIF
 * address bits. This register need be set to x. (x = the highest valid HIF
 * address bit - internal base - 2)
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP2 . ADDRMAP_COL_B3
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP2_ADDRMAP_COL_B3(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP2_ADDRMAP_COL_B3     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP2_ADDRMAP_COL_B3(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/**
 * \brief
 *
 *  - Full bus width mode - Selects the HIF address bit used as column
 * address bit 4
 *  - Half bus width mode - Selects the HIF address bit used as column
 * address bit 5
 *  - Quarter bus width mode - Selects the HIF address bit used as column
 * address bit 6
 * Valid Range: 0 to 7, and 15
 * Internal Base: 4
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 15 and then this column address bit is set to 0.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP2 . ADDRMAP_COL_B4
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP2_ADDRMAP_COL_B4(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP2_ADDRMAP_COL_B4     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP2_ADDRMAP_COL_B4(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 *
 *  - Full bus width mode - Selects the HIF address bit used as column
 * address bit 5
 *  - Half bus width mode - Selects the HIF address bit used as column
 * address bit 6
 *  - Quarter bus width mode - Selects the HIF address bit used as column
 * address bit 7
 * Valid Range: 0 to 7, and 15
 * Internal Base: 5
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 15 and then this column address bit is set to 0.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP2 . ADDRMAP_COL_B5
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP2_ADDRMAP_COL_B5(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP2_ADDRMAP_COL_B5     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP2_ADDRMAP_COL_B5(x)  VTSS_EXTRACT_BITFIELD(x,24,4)


/**
 * \brief Address Map Register 3
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP3
 */
#define VTSS_DDR_UMCTL2_ADDRMAP3             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x83)

/**
 * \brief
 *
 *  - Full bus width mode - Selects the HIF address bit used as column
 * address bit 6.
 *  - Half bus width mode - Selects the HIF address bit used as column
 * address bit 7.
 *  - Quarter bus width mode - Selects the HIF address bit used as column
 * address bit 8.
 * Valid Range: 0 to 7, x and 31. x indicates a valid value in the inline
 * ECC configuration.
 * Internal Base: 6
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 31 and then this column address bit is set to 0.
 * In Inline ECC configuration (MEMC_INLINE_ECC=1) and Inline ECC mode is
 * enabled (ECCCFG0.ecc_mode=4), if MEMC_BURST_LENGTH is 8, number of
 * column address is 10 and work on half bus width mode, column bit 8,
 * column bit 7 and column bit 6 must map to the highest 3 valid HIF
 * address bits. This register need be set to x. (x = the highest valid HIF
 * address bit - internal base - 2)
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP3 . ADDRMAP_COL_B6
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP3_ADDRMAP_COL_B6(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP3_ADDRMAP_COL_B6     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP3_ADDRMAP_COL_B6(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 *
 *  - Full bus width mode - Selects the HIF address bit used as column
 * address bit 7
 *  - Half bus width mode - Selects the HIF address bit used as column
 * address bit 8
 *  - Quarter bus width mode - Selects the HIF address bit used as column
 * address bit 9
 * Valid Range: 0 to 7, x, and 31. x indicates a valid value in the inline
 * ECC configuration.
 * Internal Base: 7
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * In Inline ECC configuration (MEMC_INLINE_ECC=1) and Inline ECC mode is
 * enabled (ECCCFG0.ecc_mode=4), the highest 3 column address bits must map
 * to the highest 3 valid HIF address bits.
 * If column bit 7 is the third highest column address bit, it must map to
 * the third highest valid HIF address bit. (x = the highest valid HIF
 * address bit - 2 - internal base)
 * If unused, set to 31 and then this column address bit is set to 0.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP3 . ADDRMAP_COL_B7
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP3_ADDRMAP_COL_B7(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP3_ADDRMAP_COL_B7     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP3_ADDRMAP_COL_B7(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/**
 * \brief
 *
 *  - Full bus width mode - Selects the HIF address bit used as column
 * address bit 8
 *  - Half bus width mode - Selects the HIF address bit used as column
 * address bit 9
 *  - Quarter bus width mode - Selects the HIF address bit used as column
 * address bit 11 (10 in LPDDR2/LPDDR3 mode)
 * Valid Range: 0 to 7, x, and 31. x indicates a valid value in the inline
 * ECC configuration.
 * Internal Base: 8
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * Note: Per JEDEC DDR2/3/mDDR specification, column address bit 10 is
 * reserved for indicating auto-precharge, and hence no source address bit
 * can be mapped to column address bit 10.
 * In LPDDR2/LPDDR3, there is a dedicated bit for auto-precharge in the CA
 * bus and hence column bit 10 is used.
 * In Inline ECC configuration (MEMC_INLINE_ECC=1) and Inline ECC mode is
 * enabled (ECCCFG0.ecc_mode=4), the highest 3 column address bits must map
 * to the highest 3 valid HIF address bits.
 * If column bit 8 is the second highest column address bit, it must map to
 * the second highest valid HIF address bit. (x = the highest valid HIF
 * address bit - 1 - internal base)
 * If column bit 8 is the third highest column address bit, it must map to
 * the third highest valid HIF address bit. (x = the highest valid HIF
 * address bit - 2 - internal base)
 * If unused, set to 31 and then this column address bit is set to 0.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP3 . ADDRMAP_COL_B8
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP3_ADDRMAP_COL_B8(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP3_ADDRMAP_COL_B8     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP3_ADDRMAP_COL_B8(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/**
 * \brief
 *
 *  - Full bus width mode - Selects the HIF address bit used as column
 * address bit 9
 *  - Half bus width mode - Selects the HIF address bit used as column
 * address bit 11 (10 in LPDDR2/LPDDR3 mode)
 *  - Quarter bus width mode - Selects the HIF address bit used as column
 * address bit 13 (11 in LPDDR2/LPDDR3 mode)
 * Valid Range: 0 to 7, x, and 31. x indicates a valid value in the inline
 * ECC configuration.
 * Internal Base: 9
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * Note: Per JEDEC DDR2/3/mDDR specification, column address bit 10 is
 * reserved for indicating auto-precharge, and hence no source address bit
 * can be mapped to column address bit 10.
 * In LPDDR2/LPDDR3, there is a dedicated bit for auto-precharge in the CA
 * bus and hence column bit 10 is used.
 * In Inline ECC configuration (MEMC_INLINE_ECC=1) and Inline ECC mode is
 * enabled (ECCCFG0.ecc_mode=4), the highest 3 column address bits must map
 * to the highest 3 valid HIF address bits.
 * If column bit 9 is the highest column address bit, it must map to the
 * highest valid HIF address bit. (x = the highest valid HIF address bit -
 * internal base)
 * If column bit 9 is the second highest column address bit, it must map to
 * the second highest valid HIF address bit. (x = the highest valid HIF
 * address bit - 1 - internal base)
 * If column bit 9 is the third highest column address bit, it must map to
 * the third highest valid HIF address bit. (x = the highest valid HIF
 * address bit - 2 - internal base)
 * If unused, set to 31 and then this column address bit is set to 0.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP3 . ADDRMAP_COL_B9
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP3_ADDRMAP_COL_B9(x)  VTSS_ENCODE_BITFIELD(x,24,5)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP3_ADDRMAP_COL_B9     VTSS_ENCODE_BITMASK(24,5)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP3_ADDRMAP_COL_B9(x)  VTSS_EXTRACT_BITFIELD(x,24,5)


/**
 * \brief Address Map Register 4
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP4
 */
#define VTSS_DDR_UMCTL2_ADDRMAP4             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x84)

/**
 * \brief
 *
 *  - Full bus width mode: Selects the HIF address bit used as column
 * address bit 11 (10 in LPDDR2/LPDDR3 mode)
 *  - Half bus width mode: Selects the HIF address bit used as column
 * address bit 13 (11 in LPDDR2/LPDDR3 mode)
 *  - Quarter bus width mode: UNUSED. See later in this description for
 * value you need to set to make it unused
 * Valid Range: 0 to 7, x, and 31. x indicates a valid value in the inline
 * ECC configuration.
 * Internal Base: 10
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * Note: Per JEDEC DDR2/3/mDDR specification, column address bit 10 is
 * reserved for indicating auto-precharge, and hence no source address bit
 * can be mapped to column address bit 10.
 * In LPDDR2/LPDDR3, there is a dedicated bit for auto-precharge in the CA
 * bus and hence column bit 10 is used.
 * In Inline ECC configuration (MEMC_INLINE_ECC=1) and Inline ECC mode is
 * enabled (ECCCFG0.ecc_mode=4), the highest 3 column address bits must map
 * to the highest 3 valid HIF address bits.
 * If column bit 10 is the highest column address bit, it must map to the
 * highest valid HIF address bit. (x = the highest valid HIF address bit -
 * internal base)
 * If column bit 10 is the second highest column address bit, it must map
 * to the second highest valid HIF address bit. (x = the highest valid HIF
 * address bit - 1 - internal base)
 * If column bit 10 is the third highest column address bit, it must map to
 * the third highest valid HIF address bit. (x = the highest valid HIF
 * address bit - 2 - internal base)
 * If unused, set to 31 and then this column address bit is set to 0.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP4 . ADDRMAP_COL_B10
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP4_ADDRMAP_COL_B10(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP4_ADDRMAP_COL_B10     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP4_ADDRMAP_COL_B10(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 *
 *  - Full bus width mode - Selects the HIF address bit used as column
 * address bit 13 (11 in LPDDR2/LPDDR3 mode)
 *  - Half bus width mode - UNUSED. See later in this description for value
 * you need to set to make it unused
 *  - Quarter bus width mode - UNUSED. See later in this description for
 * value you need to set to make it unused
 * Valid Range: 0 to 7, x, and 31. x indicates a valid value in the inline
 * ECC configuration.
 * Internal Base: 11
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * Note: Per JEDEC DDR2/3/mDDR specification, column address bit 10 is
 * reserved for indicating auto-precharge, and hence no source address bit
 * can be mapped to column address bit 10.
 * In LPDDR2/LPDDR3, there is a dedicated bit for auto-precharge in the CA
 * bus and hence column bit 10 is used.
 * In Inline ECC configuration (MEMC_INLINE_ECC=1) and Inline ECC mode is
 * enabled (ECCCFG0.ecc_mode=4), the highest 3 column address bits must map
 * to the highest 3 valid HIF address bits.
 * If column bit 11 is the highest column address bit, it must map to the
 * highest valid HIF address bit. (x = the highest valid HIF address bit -
 * internal base)
 * If column bit 11 is the second highest column address bit, it must map
 * to the second highest valid HIF address bit. (x = the highest valid HIF
 * address bit - 1 - internal base)
 * If column bit 11 is the third highest column address bit, it must map to
 * the third highest valid HIF address bit. (x = the highest valid HIF
 * address bit - 2 - internal base)
 * If unused, set to 31 and then this column address bit is set to 0.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP4 . ADDRMAP_COL_B11
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP4_ADDRMAP_COL_B11(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP4_ADDRMAP_COL_B11     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP4_ADDRMAP_COL_B11(x)  VTSS_EXTRACT_BITFIELD(x,8,5)


/**
 * \brief Address Map Register 5
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP5
 */
#define VTSS_DDR_UMCTL2_ADDRMAP5             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x85)

/**
 * \brief
 * Selects the HIF address bits used as row address bit 0.
 * Valid Range: 0 to 11
 * Internal Base: 6
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP5 . ADDRMAP_ROW_B0
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP5_ADDRMAP_ROW_B0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP5_ADDRMAP_ROW_B0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP5_ADDRMAP_ROW_B0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Selects the HIF address bits used as row address bit 1.
 * Valid Range: 0 to 11
 * Internal Base: 7
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP5 . ADDRMAP_ROW_B1
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP5_ADDRMAP_ROW_B1(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP5_ADDRMAP_ROW_B1     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP5_ADDRMAP_ROW_B1(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * Selects the HIF address bits used as row address bits 2 to 10.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 8 (for row address bit 2), 9 (for row address bit 3), 10
 * (for row address bit 4) and so on, increasing to 16 (for row address bit
 * 10)
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field.
 * When set to 15, the values of row address bits 2 to 10 are defined by
 * registers ADDRMAP9, ADDRMAP10, ADDRMAP11.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP5 . ADDRMAP_ROW_B2_10
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP5_ADDRMAP_ROW_B2_10(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP5_ADDRMAP_ROW_B2_10     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP5_ADDRMAP_ROW_B2_10(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Selects the HIF address bit used as row address bit 11.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 17
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 15 and then row address bit 11 is set to 0.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP5 . ADDRMAP_ROW_B11
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP5_ADDRMAP_ROW_B11(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP5_ADDRMAP_ROW_B11     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP5_ADDRMAP_ROW_B11(x)  VTSS_EXTRACT_BITFIELD(x,24,4)


/**
 * \brief Address Map Register 6
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP6
 */
#define VTSS_DDR_UMCTL2_ADDRMAP6             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x86)

/**
 * \brief
 * Selects the HIF address bit used as row address bit 12.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 18
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 15 and then row address bit 12 is set to 0.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP6 . ADDRMAP_ROW_B12
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP6_ADDRMAP_ROW_B12(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP6_ADDRMAP_ROW_B12     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP6_ADDRMAP_ROW_B12(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Selects the HIF address bit used as row address bit 13.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 19
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 15 and then row address bit 13 is set to 0.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP6 . ADDRMAP_ROW_B13
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP6_ADDRMAP_ROW_B13(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP6_ADDRMAP_ROW_B13     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP6_ADDRMAP_ROW_B13(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * Selects the HIF address bit used as row address bit 14.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 20
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 15 and then row address bit 14 is set to 0.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP6 . ADDRMAP_ROW_B14
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP6_ADDRMAP_ROW_B14(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP6_ADDRMAP_ROW_B14     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP6_ADDRMAP_ROW_B14(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Selects the HIF address bit used as row address bit 15.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 21
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 15 and then row address bit 15 is set to 0.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP6 . ADDRMAP_ROW_B15
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP6_ADDRMAP_ROW_B15(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP6_ADDRMAP_ROW_B15     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP6_ADDRMAP_ROW_B15(x)  VTSS_EXTRACT_BITFIELD(x,24,4)


/**
 * \brief Address Map Register 7
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP7
 */
#define VTSS_DDR_UMCTL2_ADDRMAP7             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x87)

/**
 * \brief
 * Selects the HIF address bit used as row address bit 16.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 22
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 15 and then row address bit 16 is set to 0.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP7 . ADDRMAP_ROW_B16
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP7_ADDRMAP_ROW_B16(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP7_ADDRMAP_ROW_B16     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP7_ADDRMAP_ROW_B16(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Selects the HIF address bit used as row address bit 17.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 23
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 15 and then row address bit 17 is set to 0 for DDR4 or
 * set to 1 for LPDDR4 backward compability.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP7 . ADDRMAP_ROW_B17
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP7_ADDRMAP_ROW_B17(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP7_ADDRMAP_ROW_B17     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP7_ADDRMAP_ROW_B17(x)  VTSS_EXTRACT_BITFIELD(x,8,4)


/**
 * \brief Address Map Register 8
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP8
 */
#define VTSS_DDR_UMCTL2_ADDRMAP8             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x88)

/**
 * \brief
 * Selects the HIF address bits used as bank group address bit 0.
 * Valid Range: 0 to 32, and 63
 * Internal Base: 2
 * The selected HIF address bit for each of the bank group address bits is
 * determined by adding the internal base to the value of this field.
 * If unused, set to 63 and then bank group address bit 0 is set to 0.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP8 . ADDRMAP_BG_B0
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP8_ADDRMAP_BG_B0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP8_ADDRMAP_BG_B0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP8_ADDRMAP_BG_B0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * Selects the HIF address bits used as bank group address bit 1.
 * Valid Range: 0 to 32, and 63
 * Internal Base: 3
 * The selected HIF address bit for each of the bank group address bits is
 * determined by adding the internal base to the value of this field.
 * If unused, set to 63 and then bank group address bit 1 is set to 0.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP8 . ADDRMAP_BG_B1
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP8_ADDRMAP_BG_B1(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP8_ADDRMAP_BG_B1     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP8_ADDRMAP_BG_B1(x)  VTSS_EXTRACT_BITFIELD(x,8,6)


/**
 * \brief Address Map Register 9
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP9
 */
#define VTSS_DDR_UMCTL2_ADDRMAP9             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x89)

/**
 * \brief
 * Selects the HIF address bits used as row address bit 2.
 * Valid Range: 0 to 11
 * Internal Base: 8
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field. This
 * register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to
 * value 15.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP9 . ADDRMAP_ROW_B2
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP9_ADDRMAP_ROW_B2(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP9_ADDRMAP_ROW_B2     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP9_ADDRMAP_ROW_B2(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Selects the HIF address bits used as row address bit 3.
 * Valid Range: 0 to 11
 * Internal Base: 9
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field. This
 * register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to
 * value 15.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP9 . ADDRMAP_ROW_B3
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP9_ADDRMAP_ROW_B3(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP9_ADDRMAP_ROW_B3     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP9_ADDRMAP_ROW_B3(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * Selects the HIF address bits used as row address bit 4.
 * Valid Range: 0 to 11
 * Internal Base: 10
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field. This
 * register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to
 * value 15.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP9 . ADDRMAP_ROW_B4
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP9_ADDRMAP_ROW_B4(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP9_ADDRMAP_ROW_B4     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP9_ADDRMAP_ROW_B4(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Selects the HIF address bits used as row address bit 5.
 * Valid Range: 0 to 11
 * Internal Base: 11
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field. This
 * register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to
 * value 15.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP9 . ADDRMAP_ROW_B5
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP9_ADDRMAP_ROW_B5(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP9_ADDRMAP_ROW_B5     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP9_ADDRMAP_ROW_B5(x)  VTSS_EXTRACT_BITFIELD(x,24,4)


/**
 * \brief Address Map Register 10
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP10
 */
#define VTSS_DDR_UMCTL2_ADDRMAP10            VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x8a)

/**
 * \brief
 * Selects the HIF address bits used as row address bit 6.
 * Valid Range: 0 to 11
 * Internal Base: 12
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field. This
 * register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to
 * value 15.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP10 . ADDRMAP_ROW_B6
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP10_ADDRMAP_ROW_B6(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP10_ADDRMAP_ROW_B6     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP10_ADDRMAP_ROW_B6(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Selects the HIF address bits used as row address bit 7.
 * Valid Range: 0 to 11
 * Internal Base: 13
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field. This
 * register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to
 * value 15.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP10 . ADDRMAP_ROW_B7
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP10_ADDRMAP_ROW_B7(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP10_ADDRMAP_ROW_B7     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP10_ADDRMAP_ROW_B7(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * Selects the HIF address bits used as row address bit 8.
 * Valid Range: 0 to 11
 * Internal Base: 14
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field. This
 * register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to
 * value 15.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP10 . ADDRMAP_ROW_B8
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP10_ADDRMAP_ROW_B8(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP10_ADDRMAP_ROW_B8     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP10_ADDRMAP_ROW_B8(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Selects the HIF address bits used as row address bit 9.
 * Valid Range: 0 to 11
 * Internal Base: 15
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field. This
 * register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to
 * value 15.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP10 . ADDRMAP_ROW_B9
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP10_ADDRMAP_ROW_B9(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP10_ADDRMAP_ROW_B9     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP10_ADDRMAP_ROW_B9(x)  VTSS_EXTRACT_BITFIELD(x,24,4)


/**
 * \brief Address Map Register 11
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP11
 */
#define VTSS_DDR_UMCTL2_ADDRMAP11            VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x8b)

/**
 * \brief
 * Selects the HIF address bits used as row address bit 10.
 * Valid Range: 0 to 11
 * Internal Base: 16
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field. This
 * register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to
 * value 15.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADDRMAP11 . ADDRMAP_ROW_B10
 */
#define  VTSS_F_DDR_UMCTL2_ADDRMAP11_ADDRMAP_ROW_B10(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_ADDRMAP11_ADDRMAP_ROW_B10     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_ADDRMAP11_ADDRMAP_ROW_B10(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief ODT Configuration Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ODTCFG
 */
#define VTSS_DDR_UMCTL2_ODTCFG               VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x90)

/**
 * \brief
 * Indicates the delay, in DFI PHY clock cycles, from issuing a read
 * command to setting ODT values associated with that command. ODT setting
 * must remain constant for the entire time that DQS is driven by the
 * uMCTL2.
 * Recommended values:
 * DDR2:
 *  - CL + AL - 4 (not DDR2-1066), CL + AL - 5 (DDR2-1066)
 *    If (CL + AL - 4 < 0), uMCTL2 does not support ODT for read operation.
 * DDR3:
 *  - CL - CWL
 * DDR4:
 *  - CL - CWL - RD_PREAMBLE + WR_PREAMBLE + DFITMG1.dfi_t_cmd_lat (to
 * adjust for CAL mode)
 *    WR_PREAMBLE = 1 (1tCK write preamble), 2 (2tCK write preamble)
 * RD_PREAMBLE = 1 (1tCK read preamble), 2 (2tCK read preamble)
 * If (CL - CWL - RD_PREAMBLE + WR_PREAMBLE) < 0, uMCTL2 does not support
 * ODT for read operation.
 * LPDDR3:
 *  - RL + RD(tDQSCK(min)/tCK) - 1 - RU(tODTon(max)/tCK)
 * Unit: DFI PHY clock cycles.
 * Programming Mode: Quasi-dynamic Group 1, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ODTCFG . RD_ODT_DELAY
 */
#define  VTSS_F_DDR_UMCTL2_ODTCFG_RD_ODT_DELAY(x)  VTSS_ENCODE_BITFIELD(x,2,5)
#define  VTSS_M_DDR_UMCTL2_ODTCFG_RD_ODT_DELAY     VTSS_ENCODE_BITMASK(2,5)
#define  VTSS_X_DDR_UMCTL2_ODTCFG_RD_ODT_DELAY(x)  VTSS_EXTRACT_BITFIELD(x,2,5)

/**
 * \brief
 * DFI PHY clock cycles to hold ODT for a read command. The minimum
 * supported value is 2.
 * Recommended values:
 * DDR2:
 *  - BL8 - 0x6 (not DDR2-1066), 0x7 (DDR2-1066)
 *  - BL4 - 0x4 (not DDR2-1066), 0x5 (DDR2-1066)
 * DDR3:
 *  - BL8 - 0x6
 * DDR4:
 *  - BL8 - 5 + RD_PREAMBLE
 *    RD_PREAMBLE = 1 (1tCK read preamble), 2 (2tCK read preamble)
 * LPDDR3:
 *  - BL8 - 5 + RU(tDQSCK(max)/tCK) - RD(tDQSCK(min)/tCK) +
 * RU(tODTon(max)/tCK)
 * Unit: DFI PHY clock cycles.
 * Programming Mode: Quasi-dynamic Group 1, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ODTCFG . RD_ODT_HOLD
 */
#define  VTSS_F_DDR_UMCTL2_ODTCFG_RD_ODT_HOLD(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_ODTCFG_RD_ODT_HOLD     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_ODTCFG_RD_ODT_HOLD(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * Indicates the delay, in DFI PHY clock cycles, from issuing a write
 * command to setting ODT values associated with that command. ODT setting
 * must remain constant for the entire time that DQS is driven by the
 * uMCTL2.
 * Recommended values:
 * DDR2:
 *  - CWL + AL - 3 (DDR2-400/533/667), CWL + AL - 4 (DDR2-800), CWL + AL -
 * 5 (DDR2-1066)
 *    If (CWL + AL - 3	< 0), uMCTL2 does not support ODT for write
 * operation.
 *  DDR3:
 *  - 0x0
 *  DDR4:
 *  - DFITMG1.dfi_t_cmd_lat (to adjust for CAL mode)
 *  LPDDR3:
 *  - WL - 1 - RU(tODTon(max)/tCK))
 * Unit: DFI PHY clock cycles.
 * Programming Mode: Quasi-dynamic Group 1, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ODTCFG . WR_ODT_DELAY
 */
#define  VTSS_F_DDR_UMCTL2_ODTCFG_WR_ODT_DELAY(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_DDR_UMCTL2_ODTCFG_WR_ODT_DELAY     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_DDR_UMCTL2_ODTCFG_WR_ODT_DELAY(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/**
 * \brief
 * DFI PHY clock cycles to hold ODT for a write command. The minimum
 * supported value is 2.
 * Recommended values:
 * DDR2:
 *  - BL8 - 0x5 (DDR2-400/533/667), 0x6 (DDR2-800), 0x7 (DDR2-1066)
 *  - BL4 - 0x3 (DDR2-400/533/667), 0x4 (DDR2-800), 0x5 (DDR2-1066)
 * DDR3:
 *  - BL8 - 0x6
 * DDR4:
 *  - BL8 - 5 + WR_PREAMBLE + CRC_MODE
 *    WR_PREAMBLE = 1 (1tCK write preamble), 2 (2tCK write preamble)
 *    CRC_MODE = 0 (not CRC mode), 1 (CRC mode)
 * LPDDR3:
 *  - BL8 - 7 + RU(tODTon(max)/tCK)
 * Unit: DFI PHY clock cycles.
 * Programming Mode: Quasi-dynamic Group 1, Group 4
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ODTCFG . WR_ODT_HOLD
 */
#define  VTSS_F_DDR_UMCTL2_ODTCFG_WR_ODT_HOLD(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_UMCTL2_ODTCFG_WR_ODT_HOLD     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_UMCTL2_ODTCFG_WR_ODT_HOLD(x)  VTSS_EXTRACT_BITFIELD(x,24,4)


/**
 * \brief ODT/Rank Map Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ODTMAP
 */
#define VTSS_DDR_UMCTL2_ODTMAP               VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x91)

/**
 * \brief
 * Indicates which remote ODTs must be turned on during a write to rank 0.
 * Each rank has a remote ODT (in the SDRAM) which can be turned on by
 * setting the appropriate bit here.
 * Rank 0 is controlled by the LSB; rank 1 is controlled by bit next to the
 * LSB, and so on.
 * For each rank, set its bit to 1 to enable its ODT.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ODTMAP . RANK0_WR_ODT
 */
#define  VTSS_F_DDR_UMCTL2_ODTMAP_RANK0_WR_ODT(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DDR_UMCTL2_ODTMAP_RANK0_WR_ODT     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DDR_UMCTL2_ODTMAP_RANK0_WR_ODT(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * Indicates which remote ODTs must be turned on during a read from rank 0.
 * Each rank has a remote ODT (in the SDRAM) which can be turned on by
 * setting the appropriate bit here.
 * Rank 0 is controlled by the LSB; rank 1 is controlled by bit next to the
 * LSB, and so on.
 * For each rank, set its bit to 1 to enable its ODT.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ODTMAP . RANK0_RD_ODT
 */
#define  VTSS_F_DDR_UMCTL2_ODTMAP_RANK0_RD_ODT(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_DDR_UMCTL2_ODTMAP_RANK0_RD_ODT     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_DDR_UMCTL2_ODTMAP_RANK0_RD_ODT(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * Indicates which remote ODTs must be turned on during a write to rank 1.
 * Each rank has a remote ODT (in the SDRAM) which can be turned on by
 * setting the appropriate bit here.
 * Rank 0 is controlled by the LSB; rank 1 is controlled by bit next to the
 * LSB, and so on.
 * For each rank, set its bit to 1 to enable its ODT.
 * Present only in configurations that have 2 or more ranks.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ODTMAP . RANK1_WR_ODT
 */
#define  VTSS_F_DDR_UMCTL2_ODTMAP_RANK1_WR_ODT(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_DDR_UMCTL2_ODTMAP_RANK1_WR_ODT     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_DDR_UMCTL2_ODTMAP_RANK1_WR_ODT(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * Indicates which remote ODTs must be turned on during a read from rank 1.
 * Each rank has a remote ODT (in the SDRAM) which can be turned on by
 * setting the appropriate bit here.
 * Rank 0 is controlled by the LSB; rank 1 is controlled by bit next to the
 * LSB, and so on.
 * For each rank, set its bit to 1 to enable its ODT.
 * Present only in configurations that have 2 or more ranks.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ODTMAP . RANK1_RD_ODT
 */
#define  VTSS_F_DDR_UMCTL2_ODTMAP_RANK1_RD_ODT(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_DDR_UMCTL2_ODTMAP_RANK1_RD_ODT     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_DDR_UMCTL2_ODTMAP_RANK1_RD_ODT(x)  VTSS_EXTRACT_BITFIELD(x,12,2)


/**
 * \brief Scheduler Control Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:SCHED
 */
#define VTSS_DDR_UMCTL2_SCHED                VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x94)

/**
 * \brief
 * In this release, this register bit is required to set to 1 in software
 * unless otherwise advised by Synopsys.
 * Programming Mode: Static
 *
 * \details
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_SCHED . DIS_OPT_WRECC_COLLISION_FLUSH
 */
#define  VTSS_F_DDR_UMCTL2_SCHED_DIS_OPT_WRECC_COLLISION_FLUSH(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_SCHED_DIS_OPT_WRECC_COLLISION_FLUSH  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_SCHED_DIS_OPT_WRECC_COLLISION_FLUSH(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Sets if the bank selector prefers writes over reads.
 * FOR DEBUG ONLY.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_SCHED . PREFER_WRITE
 */
#define  VTSS_F_DDR_UMCTL2_SCHED_PREFER_WRITE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_SCHED_PREFER_WRITE  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_SCHED_PREFER_WRITE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Sets if bank is kept open only while there are page hit transactions
 * available in the CAM to that bank or if the bank remains open until
 * there is a need to close it.
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_SCHED . PAGECLOSE
 */
#define  VTSS_F_DDR_UMCTL2_SCHED_PAGECLOSE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_UMCTL2_SCHED_PAGECLOSE    VTSS_BIT(2)
#define  VTSS_X_DDR_UMCTL2_SCHED_PAGECLOSE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Selects behavior of hif_cmd_autopre if a RMW is received on HIF with
 * hif_cmd_autopre=1
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_SCHED . AUTOPRE_RMW
 */
#define  VTSS_F_DDR_UMCTL2_SCHED_AUTOPRE_RMW(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DDR_UMCTL2_SCHED_AUTOPRE_RMW  VTSS_BIT(7)
#define  VTSS_X_DDR_UMCTL2_SCHED_AUTOPRE_RMW(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Number of entries in the low priority transaction store is this value +
 * 1.
 * (MEMC_NO_OF_ENTRY - (SCHED.lpr_num_entries + 1)) is the number of
 * entries available for the high priority transaction store.
 * Setting this to maximum value allocates all entries to low priority
 * transaction store.
 * Setting this to 0 allocates 1 entry to low priority transaction store
 * and the rest to high priority transaction store.
 * Note: In ECC configurations, the numbers of write and low priority read
 * credits issued is one less than in the non-ECC case. One entry each is
 * reserved in the write and low-priority read CAMs for storing the RMW
 * requests arising out of single bit error correction RMW operation.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_SCHED . LPR_NUM_ENTRIES
 */
#define  VTSS_F_DDR_UMCTL2_SCHED_LPR_NUM_ENTRIES(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_DDR_UMCTL2_SCHED_LPR_NUM_ENTRIES     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_DDR_UMCTL2_SCHED_LPR_NUM_ENTRIES(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/**
 * \brief
 * UNUSED.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_SCHED . GO2CRITICAL_HYSTERESIS
 */
#define  VTSS_F_DDR_UMCTL2_SCHED_GO2CRITICAL_HYSTERESIS(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_UMCTL2_SCHED_GO2CRITICAL_HYSTERESIS     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_UMCTL2_SCHED_GO2CRITICAL_HYSTERESIS(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * When the preferred transaction store is empty for these many clock
 * cycles, switch to the alternate transaction store if it is non-empty.
 * The read transaction store (both high and low priority) is the default
 * preferred transaction store and the write transaction store is the
 * alternative store.
 * When prefer write over read is set this is reversed.
 * 0x0 is a legal value for this register. When set to 0x0, the transaction
 * store switching happens immediately when the switching conditions become
 * true.
 * FOR PERFORMANCE ONLY.
 * Unit: DFI clock cycles.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_SCHED . RDWR_IDLE_GAP
 */
#define  VTSS_F_DDR_UMCTL2_SCHED_RDWR_IDLE_GAP(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_DDR_UMCTL2_SCHED_RDWR_IDLE_GAP     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_DDR_UMCTL2_SCHED_RDWR_IDLE_GAP(x)  VTSS_EXTRACT_BITFIELD(x,24,7)


/**
 * \brief Scheduler Control Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:SCHED1
 */
#define VTSS_DDR_UMCTL2_SCHED1               VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x95)

/**
 * \brief
 * This field works in conjunction with SCHED.pageclose.It only has meaning
 * if SCHED.pageclose==1.
 * If SCHED.pageclose==1 and pageclose_timer==0, then an auto-precharge may
 * be scheduled for last read or write command in the CAM with a bank and
 * page hit.
 * Note, sometimes an explicit precharge is scheduled instead of the
 * auto-precharge. For more information,see SCHED.pageclose.
 * If SCHED.pageclose==1 and pageclose_timer>0, then an auto-precharge is
 * not scheduled for last read or write command in the CAM with a bank and
 * page hit.
 * Instead, a timer is started, with pageclose_timer as the initial value.
 * There is a timer on a per bank basis.
 * The timer decrements unless the next read or write in the CAM to a bank
 * is a page hit.
 * It gets reset to pageclose_timer value if the next read or write in the
 * CAM to a bank is a page hit.
 * Once the timer has reached zero, an explcit precharge is attempted to be
 * scheduled.
 * Unit: DFI clock cycles.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_SCHED1 . PAGECLOSE_TIMER
 */
#define  VTSS_F_DDR_UMCTL2_SCHED1_PAGECLOSE_TIMER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_UMCTL2_SCHED1_PAGECLOSE_TIMER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_UMCTL2_SCHED1_PAGECLOSE_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief High Priority Read CAM Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:PERFHPR1
 */
#define VTSS_DDR_UMCTL2_PERFHPR1             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x97)

/**
 * \brief
 * Indicates the number of DFI clocks that the HPR queue can be starved
 * before it goes critical.
 * The minimum valid functional value for this register is 0x1.
 * Programming it to 0x0 disables the starvation functionality.
 * During normal operation, this function must not be disabled as it causes
 * excessive latencies.
 * FOR PERFORMANCE ONLY.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PERFHPR1 . HPR_MAX_STARVE
 */
#define  VTSS_F_DDR_UMCTL2_PERFHPR1_HPR_MAX_STARVE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_UMCTL2_PERFHPR1_HPR_MAX_STARVE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_UMCTL2_PERFHPR1_HPR_MAX_STARVE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Indicates the number of transactions that are serviced once the HPR
 * queue goes critical is the smaller of:
 *  - (a) This number
 *  - (b) Number of transactions available
 *  Unit: Transaction.
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PERFHPR1 . HPR_XACT_RUN_LENGTH
 */
#define  VTSS_F_DDR_UMCTL2_PERFHPR1_HPR_XACT_RUN_LENGTH(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DDR_UMCTL2_PERFHPR1_HPR_XACT_RUN_LENGTH     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DDR_UMCTL2_PERFHPR1_HPR_XACT_RUN_LENGTH(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief Low Priority Read CAM Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:PERFLPR1
 */
#define VTSS_DDR_UMCTL2_PERFLPR1             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x99)

/**
 * \brief
 * Indicates the number of DFI clocks that the LPR queue can be starved
 * before it goes critical.
 * The minimum valid functional value for this register is 0x1.
 * Programming it to 0x0 disables the starvation functionality.
 * During normal operation, this function must not be disabled as it causes
 * excessive latencies.
 * FOR PERFORMANCE ONLY.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PERFLPR1 . LPR_MAX_STARVE
 */
#define  VTSS_F_DDR_UMCTL2_PERFLPR1_LPR_MAX_STARVE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_UMCTL2_PERFLPR1_LPR_MAX_STARVE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_UMCTL2_PERFLPR1_LPR_MAX_STARVE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Indicates the number of transactions that are serviced once the LPR
 * queue goes critical is the smaller of:
 *  - (a) This number
 *  - (b) Number of transactions available
 * Unit: Transaction.
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PERFLPR1 . LPR_XACT_RUN_LENGTH
 */
#define  VTSS_F_DDR_UMCTL2_PERFLPR1_LPR_XACT_RUN_LENGTH(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DDR_UMCTL2_PERFLPR1_LPR_XACT_RUN_LENGTH     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DDR_UMCTL2_PERFLPR1_LPR_XACT_RUN_LENGTH(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief Write CAM Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:PERFWR1
 */
#define VTSS_DDR_UMCTL2_PERFWR1              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x9b)

/**
 * \brief
 * Indicates the number of DFI clocks that the WR queue can be starved
 * before it goes critical.
 * The minimum valid functional value for this register is 0x1.
 * Programming it to 0x0 disables the starvation functionality.
 * During normal operation, this function must not be disabled as it causes
 * excessive latencies.
 * FOR PERFORMANCE ONLY.
 * Unit: DFI clock cycles.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PERFWR1 . W_MAX_STARVE
 */
#define  VTSS_F_DDR_UMCTL2_PERFWR1_W_MAX_STARVE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_UMCTL2_PERFWR1_W_MAX_STARVE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_UMCTL2_PERFWR1_W_MAX_STARVE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Indicates the number of transactions that are serviced once the WR queue
 * goes critical is the smaller of:
 *  - (a) This number
 *  - (b) Number of transactions available
 * Unit: Transaction.
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PERFWR1 . W_XACT_RUN_LENGTH
 */
#define  VTSS_F_DDR_UMCTL2_PERFWR1_W_XACT_RUN_LENGTH(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DDR_UMCTL2_PERFWR1_W_XACT_RUN_LENGTH     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DDR_UMCTL2_PERFWR1_W_XACT_RUN_LENGTH(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief Debug Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DBG0
 */
#define VTSS_DDR_UMCTL2_DBG0                 VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xc0)

/**
 * \brief
 * Disables Write combine.
 * FOR DEBUG ONLY.
 * Programming Mode: Static
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBG0 . DIS_WC
 */
#define  VTSS_F_DDR_UMCTL2_DBG0_DIS_WC(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_DBG0_DIS_WC        VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_DBG0_DIS_WC(x)     VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Sets auto-precharge for the flushed command in a collision case.
 * Collision cases are write followed by read to same address, read
 * followed by write to same address, or write followed by write to same
 * address with DBG0.dis_wc bit = 1 (where same address comparisons exclude
 * the two address bits representing critical word).
 * FOR DEBUG ONLY.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBG0 . DIS_COLLISION_PAGE_OPT
 */
#define  VTSS_F_DDR_UMCTL2_DBG0_DIS_COLLISION_PAGE_OPT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_DBG0_DIS_COLLISION_PAGE_OPT  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_DBG0_DIS_COLLISION_PAGE_OPT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Indicates the disable optimized max_rank_rd and max_logical_rank_rd
 * feature.
 * This register is for debug purpose only.
 * Programming Mode: Static
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBG0 . DIS_MAX_RANK_RD_OPT
 */
#define  VTSS_F_DDR_UMCTL2_DBG0_DIS_MAX_RANK_RD_OPT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DDR_UMCTL2_DBG0_DIS_MAX_RANK_RD_OPT  VTSS_BIT(6)
#define  VTSS_X_DDR_UMCTL2_DBG0_DIS_MAX_RANK_RD_OPT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Indicates the disable optimized max_rank_wr and max_logical_rank_wr
 * feature.
 * This register is for debug purpose only.
 * Programming Mode: Static
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBG0 . DIS_MAX_RANK_WR_OPT
 */
#define  VTSS_F_DDR_UMCTL2_DBG0_DIS_MAX_RANK_WR_OPT(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DDR_UMCTL2_DBG0_DIS_MAX_RANK_WR_OPT  VTSS_BIT(7)
#define  VTSS_X_DDR_UMCTL2_DBG0_DIS_MAX_RANK_WR_OPT(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/**
 * \brief Debug Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DBG1
 */
#define VTSS_DDR_UMCTL2_DBG1                 VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xc1)

/**
 * \brief
 * Sets uMCTL2 to not de-queue any transactions from the CAM.
 * Bypass is also disabled.
 * All transactions are queued in the CAM. No reads or writes are issued to
 * SDRAM as long as this is asserted.
 * This bit may be used to prevent reads or writes being issued by the
 * uMCTL2, which makes it safe to modify certain register fields associated
 * with reads and writes (For more information, see Programming chapter).
 * After setting this bit, it is strongly recommended to poll
 * DBGCAM.wr_data_pipeline_empty and DBGCAM.rd_data_pipeline_empty, before
 * making changes to any registers which affect reads and writes.
 * This ensures that the relevant logic in the DDRC is idle.
 * This bit is intended to be switched on-the-fly.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBG1 . DIS_DQ
 */
#define  VTSS_F_DDR_UMCTL2_DBG1_DIS_DQ(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_DBG1_DIS_DQ        VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_DBG1_DIS_DQ(x)     VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Asserts the HIF command signal hif_cmd_stall.
 * uMCTL2 ignores the hif_cmd_valid and all other associated request
 * signals.
 * This bit is intended to be switched on-the-fly.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h1:
 * 'h0:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBG1 . DIS_HIF
 */
#define  VTSS_F_DDR_UMCTL2_DBG1_DIS_HIF(x)    VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_DBG1_DIS_HIF       VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_DBG1_DIS_HIF(x)    VTSS_EXTRACT_BITFIELD(x,1,1)


/**
 * \brief CAM Debug Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DBGCAM
 */
#define VTSS_DDR_UMCTL2_DBGCAM               VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xc2)

/**
 * \brief
 * This field indicates the high priority read queue depth.
 * FOR DEBUG ONLY.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DBGCAM . DBG_HPR_Q_DEPTH
 */
#define  VTSS_F_DDR_UMCTL2_DBGCAM_DBG_HPR_Q_DEPTH(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_UMCTL2_DBGCAM_DBG_HPR_Q_DEPTH     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_UMCTL2_DBGCAM_DBG_HPR_Q_DEPTH(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * This field indicates the low priority read queue depth.
 * The last entry of Lpr queue is reserved for ECC SCRUB operation. This
 * entry is not included in the calculation of the queue depth.
 * FOR DEBUG ONLY
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DBGCAM . DBG_LPR_Q_DEPTH
 */
#define  VTSS_F_DDR_UMCTL2_DBGCAM_DBG_LPR_Q_DEPTH(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_DDR_UMCTL2_DBGCAM_DBG_LPR_Q_DEPTH     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_DDR_UMCTL2_DBGCAM_DBG_LPR_Q_DEPTH(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/**
 * \brief
 * This field indicates the Write queue depth.
 * The last entry of WR queue is reserved for ECC SCRUB operation. This
 * entry is not included in the calculation of the queue depth.
 * FOR DEBUG ONLY
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DBGCAM . DBG_W_Q_DEPTH
 */
#define  VTSS_F_DDR_UMCTL2_DBGCAM_DBG_W_Q_DEPTH(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_DDR_UMCTL2_DBGCAM_DBG_W_Q_DEPTH     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_DDR_UMCTL2_DBGCAM_DBG_W_Q_DEPTH(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * Stall.
 * FOR DEBUG ONLY.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBGCAM . DBG_STALL
 */
#define  VTSS_F_DDR_UMCTL2_DBGCAM_DBG_STALL(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_DDR_UMCTL2_DBGCAM_DBG_STALL   VTSS_BIT(24)
#define  VTSS_X_DDR_UMCTL2_DBGCAM_DBG_STALL(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * This bit indicates that all the Read command queues and Read data
 * buffers inside DDRC are empty.
 * This register is to be used for debug purpose.
 * An example use-case scenario: When the controller enters self-refresh
 * using the Low-Power entry sequence, controller is expected to have
 * executed all the commands in its queues and the write and read data
 * drained. Hence this register must be 1 at that time.
 * FOR DEBUG ONLY
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBGCAM . DBG_RD_Q_EMPTY
 */
#define  VTSS_F_DDR_UMCTL2_DBGCAM_DBG_RD_Q_EMPTY(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_DDR_UMCTL2_DBGCAM_DBG_RD_Q_EMPTY  VTSS_BIT(25)
#define  VTSS_X_DDR_UMCTL2_DBGCAM_DBG_RD_Q_EMPTY(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * This bit indicates that all the Write command queues and Write data
 * buffers inside DDRC are empty.
 * This register is to be used for debug purpose.
 * An example use-case scenario: When the controller enters self-refresh
 * using the Low-Power entry sequence, controller is expected to have
 * executed all the commands in its queues and the write and read data
 * drained. Hence this register must be 1 at that time.
 * FOR DEBUG ONLY
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBGCAM . DBG_WR_Q_EMPTY
 */
#define  VTSS_F_DDR_UMCTL2_DBGCAM_DBG_WR_Q_EMPTY(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_DDR_UMCTL2_DBGCAM_DBG_WR_Q_EMPTY  VTSS_BIT(26)
#define  VTSS_X_DDR_UMCTL2_DBGCAM_DBG_WR_Q_EMPTY(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * This bit indicates that the read data pipeline on the DFI interface is
 * empty.
 * This register is intended to be polled at least twice after setting
 * DBG1.dis_dq, to ensure that all remaining commands/data have completed.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBGCAM . RD_DATA_PIPELINE_EMPTY
 */
#define  VTSS_F_DDR_UMCTL2_DBGCAM_RD_DATA_PIPELINE_EMPTY(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_DDR_UMCTL2_DBGCAM_RD_DATA_PIPELINE_EMPTY  VTSS_BIT(28)
#define  VTSS_X_DDR_UMCTL2_DBGCAM_RD_DATA_PIPELINE_EMPTY(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * This bit indicates that the write data pipeline on the DFI interface is
 * empty.
 * This register is intended to be polled at least twice after setting
 * DBG1.dis_dq, to ensure that all remaining commands/data have completed.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBGCAM . WR_DATA_PIPELINE_EMPTY
 */
#define  VTSS_F_DDR_UMCTL2_DBGCAM_WR_DATA_PIPELINE_EMPTY(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_DDR_UMCTL2_DBGCAM_WR_DATA_PIPELINE_EMPTY  VTSS_BIT(29)
#define  VTSS_X_DDR_UMCTL2_DBGCAM_WR_DATA_PIPELINE_EMPTY(x)  VTSS_EXTRACT_BITFIELD(x,29,1)


/**
 * \brief Command Debug Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DBGCMD
 */
#define VTSS_DDR_UMCTL2_DBGCMD               VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xc3)

/**
 * \brief
 * Requests a refresh to rank 0.
 * Writing to this bit causes DBGSTAT.rank0_refresh_busy to be set.
 * When DBGSTAT.rank0_refresh_busy is cleared, the command has been stored
 * in uMCTL2.
 * For 3DS configuration, refresh is sent to rank index 0.
 * This operation can be performed only when RFSHCTL3.dis_auto_refresh=1.
 * It is recommended NOT to set this register bit if in Init or Deep
 * power-down operating modes or Maximum Power Saving Mode.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBGCMD . RANK0_REFRESH
 */
#define  VTSS_F_DDR_UMCTL2_DBGCMD_RANK0_REFRESH(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_DBGCMD_RANK0_REFRESH  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_DBGCMD_RANK0_REFRESH(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Requests a refresh to rank 1.
 * Writing to this bit causes DBGSTAT.rank1_refresh_busy to be set.
 * When DBGSTAT.rank1_refresh_busy is cleared, the command has been stored
 * in uMCTL2.
 * For 3DS configuration, refresh is sent to rank index 1.
 * This operation can be performed only when RFSHCTL3.dis_auto_refresh=1.
 * It is recommended NOT to set this register bit if in Init or Deep
 * power-down operating modes or Maximum Power Saving Mode.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBGCMD . RANK1_REFRESH
 */
#define  VTSS_F_DDR_UMCTL2_DBGCMD_RANK1_REFRESH(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_DBGCMD_RANK1_REFRESH  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_DBGCMD_RANK1_REFRESH(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Requests a ZQCS (ZQ calibration short)/MPC(ZQ calibration) command to
 * the SDRAM.
 * This operation can be performed only when ZQCTL0.dis_auto_zq=1.
 * It is recommended NOT to set this register bit if in Init, in
 * self-refresh(except LPDDR4) or SR-Powerdown(LPDDR4) or Deep power-down
 * operating modes or Maximum Power Saving Mode.
 * For self-refresh(except LPDDR4) or SR-Powerdown(LPDDR4) it is scheduled
 * after SR(except LPDDR4) or SPRD(LPDDR4) has been exited.
 * For Deep power down and Maximum Power Saving Mode, it is not scheduled,
 * although DBGSTAT.zq_calib_short_busy is de-asserted. When this request
 * is stored in the uMCTL2, the bit is automatically cleared.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBGCMD . ZQ_CALIB_SHORT
 */
#define  VTSS_F_DDR_UMCTL2_DBGCMD_ZQ_CALIB_SHORT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_DBGCMD_ZQ_CALIB_SHORT  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_DBGCMD_ZQ_CALIB_SHORT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Requests a dfi_ctrlupd_req to the PHY.
 * This operation must only be performed when DFIUPD0.dis_auto_ctrlupd=1.
 * When this request is stored in the uMCTL2, the bit is automatically
 * cleared.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBGCMD . CTRLUPD
 */
#define  VTSS_F_DDR_UMCTL2_DBGCMD_CTRLUPD(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_UMCTL2_DBGCMD_CTRLUPD     VTSS_BIT(5)
#define  VTSS_X_DDR_UMCTL2_DBGCMD_CTRLUPD(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/**
 * \brief Status Debug Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DBGSTAT
 */
#define VTSS_DDR_UMCTL2_DBGSTAT              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xc4)

/**
 * \brief
 * SoC might initiate a rank0_refresh operation (refresh operation to rank
 * 0) only if this signal is low.
 * This signal goes high in the clock after DBGCMD.rank0_refresh is set to
 * one. It goes low when the rank0_refresh operation is stored in the
 * uMCTL2.
 * It is recommended not to perform rank0_refresh operations when this
 * signal is high.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBGSTAT . RANK0_REFRESH_BUSY
 */
#define  VTSS_F_DDR_UMCTL2_DBGSTAT_RANK0_REFRESH_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_DBGSTAT_RANK0_REFRESH_BUSY  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_DBGSTAT_RANK0_REFRESH_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * SoC might initiate a rank1_refresh operation (refresh operation to rank
 * 1) only if this signal is low.
 * This signal goes high in the clock after DBGCMD.rank1_refresh is set to
 * one. It goes low when the rank1_refresh operation is stored in the
 * uMCTL2.
 * It is recommended not to perform rank1_refresh operations when this
 * signal is high.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBGSTAT . RANK1_REFRESH_BUSY
 */
#define  VTSS_F_DDR_UMCTL2_DBGSTAT_RANK1_REFRESH_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_DBGSTAT_RANK1_REFRESH_BUSY  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_DBGSTAT_RANK1_REFRESH_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * SoC might initiate a ZQCS (ZQ calibration short) operation only if this
 * signal is low.
 * This signal goes high in the clock after the uMCTL2 accepts the ZQCS
 * request.
 * It goes low when the ZQCS operation is initiated in the uMCTL2. It is
 * recommended not to perform ZQCS operations when this signal is high.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBGSTAT . ZQ_CALIB_SHORT_BUSY
 */
#define  VTSS_F_DDR_UMCTL2_DBGSTAT_ZQ_CALIB_SHORT_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_DBGSTAT_ZQ_CALIB_SHORT_BUSY  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_DBGSTAT_ZQ_CALIB_SHORT_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * SoC might initiate a ctrlupd operation only if this signal is low.
 * This signal goes high in the clock after the uMCTL2 accepts the ctrlupd
 * request.
 * It goes low when the ctrlupd operation is initiated in the uMCTL2.
 * It is recommended not to perform ctrlupd operations when this signal is
 * high.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_DBGSTAT . CTRLUPD_BUSY
 */
#define  VTSS_F_DDR_UMCTL2_DBGSTAT_CTRLUPD_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_UMCTL2_DBGSTAT_CTRLUPD_BUSY  VTSS_BIT(5)
#define  VTSS_X_DDR_UMCTL2_DBGSTAT_CTRLUPD_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/**
 * \brief CAM Debug Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DBGCAM1
 */
#define VTSS_DDR_UMCTL2_DBGCAM1              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xc6)

/**
 * \brief
 * This field indicates the write ECC queue depth.
 * FOR DEBUG ONLY.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_DBGCAM1 . DBG_WRECC_Q_DEPTH
 */
#define  VTSS_F_DDR_UMCTL2_DBGCAM1_DBG_WRECC_Q_DEPTH(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_UMCTL2_DBGCAM1_DBG_WRECC_Q_DEPTH     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_UMCTL2_DBGCAM1_DBG_WRECC_Q_DEPTH(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief Software Register Programming Control Enable
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:SWCTL
 */
#define VTSS_DDR_UMCTL2_SWCTL                VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xc8)

/**
 * \brief
 * Enables quasi-dynamic register programming outside reset.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_SWCTL . SW_DONE
 */
#define  VTSS_F_DDR_UMCTL2_SWCTL_SW_DONE(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_SWCTL_SW_DONE      VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_SWCTL_SW_DONE(x)   VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Software Register Programming Control Status
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:SWSTAT
 */
#define VTSS_DDR_UMCTL2_SWSTAT               VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xc9)

/**
 * \brief
 * Register programming done.
 * This register is the echo of SWCTL.sw_done.
 * Wait for sw_done value 1 to propagate to sw_done_ack at the end of the
 * programming sequence to ensure that the correct registers values are
 * propagated to the destination clock domains.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_SWSTAT . SW_DONE_ACK
 */
#define  VTSS_F_DDR_UMCTL2_SWSTAT_SW_DONE_ACK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_SWSTAT_SW_DONE_ACK  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_SWSTAT_SW_DONE_ACK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Static Registers Write Enable
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:SWCTLSTATIC
 */
#define VTSS_DDR_UMCTL2_SWCTLSTATIC          VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xca)

/**
 * \brief
 * Enables static register programming outside reset.
 * Note: This ability is not supported.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_SWCTLSTATIC . SW_STATIC_UNLOCK
 */
#define  VTSS_F_DDR_UMCTL2_SWCTLSTATIC_SW_STATIC_UNLOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_SWCTLSTATIC_SW_STATIC_UNLOCK  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_SWCTLSTATIC_SW_STATIC_UNLOCK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief AXI Poison Configuration Register. Common for all AXI ports.
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:POISONCFG
 */
#define VTSS_DDR_UMCTL2_POISONCFG            VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xdb)

/**
 * \brief
 * Sets SLVERR response for write transaction poisoning.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_POISONCFG . WR_POISON_SLVERR_EN
 */
#define  VTSS_F_DDR_UMCTL2_POISONCFG_WR_POISON_SLVERR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_POISONCFG_WR_POISON_SLVERR_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_POISONCFG_WR_POISON_SLVERR_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Sets interrupts for write transaction poisoning.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_POISONCFG . WR_POISON_INTR_EN
 */
#define  VTSS_F_DDR_UMCTL2_POISONCFG_WR_POISON_INTR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_POISONCFG_WR_POISON_INTR_EN  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_POISONCFG_WR_POISON_INTR_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Interrupt clear for write transaction poisoning.
 * Allow 2/3 clock cycles for correct value to propagate to controller
 * logic and clear the interrupts. uMCTL2 automatically clears this bit
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_POISONCFG . WR_POISON_INTR_CLR
 */
#define  VTSS_F_DDR_UMCTL2_POISONCFG_WR_POISON_INTR_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DDR_UMCTL2_POISONCFG_WR_POISON_INTR_CLR  VTSS_BIT(8)
#define  VTSS_X_DDR_UMCTL2_POISONCFG_WR_POISON_INTR_CLR(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Sets SLVERR response for read transaction poisoning.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_POISONCFG . RD_POISON_SLVERR_EN
 */
#define  VTSS_F_DDR_UMCTL2_POISONCFG_RD_POISON_SLVERR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DDR_UMCTL2_POISONCFG_RD_POISON_SLVERR_EN  VTSS_BIT(16)
#define  VTSS_X_DDR_UMCTL2_POISONCFG_RD_POISON_SLVERR_EN(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Sets interrupts for read transaction poisoning.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_POISONCFG . RD_POISON_INTR_EN
 */
#define  VTSS_F_DDR_UMCTL2_POISONCFG_RD_POISON_INTR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_DDR_UMCTL2_POISONCFG_RD_POISON_INTR_EN  VTSS_BIT(20)
#define  VTSS_X_DDR_UMCTL2_POISONCFG_RD_POISON_INTR_EN(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Interrupt clear for read transaction poisoning.
 * Allow 2/3 clock cycles for correct value to propagate to controller
 * logic and clear the interrupts. uMCTL2 automatically clears this bit
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_POISONCFG . RD_POISON_INTR_CLR
 */
#define  VTSS_F_DDR_UMCTL2_POISONCFG_RD_POISON_INTR_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_DDR_UMCTL2_POISONCFG_RD_POISON_INTR_CLR  VTSS_BIT(24)
#define  VTSS_X_DDR_UMCTL2_POISONCFG_RD_POISON_INTR_CLR(x)  VTSS_EXTRACT_BITFIELD(x,24,1)


/**
 * \brief AXI Poison Status Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:POISONSTAT
 */
#define VTSS_DDR_UMCTL2_POISONSTAT           VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xdc)

/**
 * \brief
 * Write transaction poisoning error interrupt for port 0.
 * This register is a APB clock copy (double register synchronizer) of the
 * interrupt asserted when a transaction is poisoned on the corresponding
 * AXI port's write address channel.
 * Bit 0 corresponds to Port 0, and so on. Interrupt is cleared by register
 * wr_poison_intr_clr, then value propagated to APB clock.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_POISONSTAT . WR_POISON_INTR_0
 */
#define  VTSS_F_DDR_UMCTL2_POISONSTAT_WR_POISON_INTR_0(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_POISONSTAT_WR_POISON_INTR_0  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_POISONSTAT_WR_POISON_INTR_0(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Write transaction poisoning error interrupt for port 1.
 * This register is a APB clock copy (double register synchronizer) of the
 * interrupt asserted when a transaction is poisoned on the corresponding
 * AXI port's write address channel.
 * Bit 0 corresponds to Port 0, and so on. Interrupt is cleared by register
 * wr_poison_intr_clr, then value propagated to APB clock.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_POISONSTAT . WR_POISON_INTR_1
 */
#define  VTSS_F_DDR_UMCTL2_POISONSTAT_WR_POISON_INTR_1(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_POISONSTAT_WR_POISON_INTR_1  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_POISONSTAT_WR_POISON_INTR_1(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Write transaction poisoning error interrupt for port 2.
 * This register is a APB clock copy (double register synchronizer) of the
 * interrupt asserted when a transaction is poisoned on the corresponding
 * AXI port's write address channel.
 * Bit 0 corresponds to Port 0, and so on. Interrupt is cleared by register
 * wr_poison_intr_clr, then value propagated to APB clock.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_POISONSTAT . WR_POISON_INTR_2
 */
#define  VTSS_F_DDR_UMCTL2_POISONSTAT_WR_POISON_INTR_2(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_UMCTL2_POISONSTAT_WR_POISON_INTR_2  VTSS_BIT(2)
#define  VTSS_X_DDR_UMCTL2_POISONSTAT_WR_POISON_INTR_2(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Read transaction poisoning error interrupt for port 0.
 * This register is a APB clock copy (double register synchronizer) of the
 * interrupt asserted when a transaction is poisoned on the corresponding
 * AXI port's read address channel.
 * Bit 0 corresponds to Port 0, and so on. Interrupt is cleared by register
 * rd_poison_intr_clr, then value propagated to APB clock.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_POISONSTAT . RD_POISON_INTR_0
 */
#define  VTSS_F_DDR_UMCTL2_POISONSTAT_RD_POISON_INTR_0(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DDR_UMCTL2_POISONSTAT_RD_POISON_INTR_0  VTSS_BIT(16)
#define  VTSS_X_DDR_UMCTL2_POISONSTAT_RD_POISON_INTR_0(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Read transaction poisoning error interrupt for port 1.
 * This register is a APB clock copy (double register synchronizer) of the
 * interrupt asserted when a transaction is poisoned on the corresponding
 * AXI port's read address channel.
 * Bit 0 corresponds to Port 0, and so on. Interrupt is cleared by register
 * rd_poison_intr_clr, then value propagated to APB clock.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_POISONSTAT . RD_POISON_INTR_1
 */
#define  VTSS_F_DDR_UMCTL2_POISONSTAT_RD_POISON_INTR_1(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_DDR_UMCTL2_POISONSTAT_RD_POISON_INTR_1  VTSS_BIT(17)
#define  VTSS_X_DDR_UMCTL2_POISONSTAT_RD_POISON_INTR_1(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Read transaction poisoning error interrupt for port 2.
 * This register is a APB clock copy (double register synchronizer) of the
 * interrupt asserted when a transaction is poisoned on the corresponding
 * AXI port's read address channel.
 * Bit 0 corresponds to Port 0, and so on. Interrupt is cleared by register
 * rd_poison_intr_clr, then value propagated to APB clock.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_POISONSTAT . RD_POISON_INTR_2
 */
#define  VTSS_F_DDR_UMCTL2_POISONSTAT_RD_POISON_INTR_2(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_DDR_UMCTL2_POISONSTAT_RD_POISON_INTR_2  VTSS_BIT(18)
#define  VTSS_X_DDR_UMCTL2_POISONSTAT_RD_POISON_INTR_2(x)  VTSS_EXTRACT_BITFIELD(x,18,1)


/**
 * \brief Advanced ECC Index Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADVECCINDEX
 */
#define VTSS_DDR_UMCTL2_ADVECCINDEX          VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xdd)

/**
 * \brief
 * Selector of which DRAM beat data output to ECCCSYN0/1/2 as well as
 * ECCUSYN.
 * In Advanced ECC, the syndrome consists of number of DRAM beats. This
 * register selects which beats of data is output to ECCCSYN0/1/2 and
 * ECCUSYN0/1/2 registers.
 * For MEMC_ECC_SUPPORT = 3, can only select the lower 64 bits data and the
 * 16bits ECC of an RS(18,16,8) code, as the higher 64 bits data are padded
 * with 64'h0, no need to read.
 * Programming Mode: Quasi-dynamic Group 1
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADVECCINDEX . ECC_SYNDROME_SEL
 */
#define  VTSS_F_DDR_UMCTL2_ADVECCINDEX_ECC_SYNDROME_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_DDR_UMCTL2_ADVECCINDEX_ECC_SYNDROME_SEL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_DDR_UMCTL2_ADVECCINDEX_ECC_SYNDROME_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Selector of which error symbol's status output to
 * ADVECCSTAT.advecc_err_symbol_pos and advecc_err_symbol_bits.
 * The default is first error symbol.
 * The value must be less than ADVECCSTAT.advecc_num_err_symbol.
 * In MEMC_ECC_SUPPORT == 2,for frequency ratio 1:1 mode, can only select
 * 0, for frequency ratio 1:2 mode, can select 0 or 1.
 * In MEMC_ECC_SUPPORT == 3,for frequency ratio 1:1 mode, can only select 0
 * or 1, for frequency ratio 1:2 mode, can select 0, 1, 2 or 3.
 * Programming Mode: Quasi-dynamic Group 1
 *
 * \details
 * 'h0:
 * 'h1:
 * 'h2:
 * 'h3:

 *
 * Field: ::VTSS_DDR_UMCTL2_ADVECCINDEX . ECC_ERR_SYMBOL_SEL
 */
#define  VTSS_F_DDR_UMCTL2_ADVECCINDEX_ECC_ERR_SYMBOL_SEL(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_DDR_UMCTL2_ADVECCINDEX_ECC_ERR_SYMBOL_SEL     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_DDR_UMCTL2_ADVECCINDEX_ECC_ERR_SYMBOL_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * Selector of which DRAM beat's poison pattern is set by ECCPOISONPAT0/1/2
 * registers.
 * For frequency ratio 1:1 mode, 2 DRAM beats can be poisoned.
 * Set ecc_poison_beats_sel to 0 and given ECCPOISONPAT0/1/2 to set 1st
 * beat's poison pattern.
 * Set ecc_poison_beats_sel to 1 and given ECCPOISONPAT0/1/2 to set 2nd
 * beat's poison pattern.
 * For frequency ratio 1:2 mode, 4 DRAM beats can be poisoned.
 * Set ecc_poison_beats_sel from 0~3 to set 1st to 4th beat's poison
 * pattern.
 * For MEMC_ECC_SUPPORT == 3, can only poison the lower 64 bits data and
 * the 16bits ECC of an RS(18,16,8) code, as the higher 64 bits data are
 * padded with 64'h0, no need to poison.
 * The other value is reserved.
 * Programming Mode: Quasi-dynamic Group 1
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ADVECCINDEX . ECC_POISON_BEATS_SEL
 */
#define  VTSS_F_DDR_UMCTL2_ADVECCINDEX_ECC_POISON_BEATS_SEL(x)  VTSS_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_DDR_UMCTL2_ADVECCINDEX_ECC_POISON_BEATS_SEL     VTSS_ENCODE_BITMASK(5,4)
#define  VTSS_X_DDR_UMCTL2_ADVECCINDEX_ECC_POISON_BEATS_SEL(x)  VTSS_EXTRACT_BITFIELD(x,5,4)


/**
 * \brief ECC Poison Pattern 0 Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCPOISONPAT0
 */
#define VTSS_DDR_UMCTL2_ECCPOISONPAT0        VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xdf)

/**
 * \brief
 * Indicates the poison pattern for DRAM data[31:0].
 * setting this bit to 1 indicates poison (invert) corresponding DRAM bit.
 * It is indirect register. Selector is ADVECCINDEX.ecc_poison_beats_sel.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCPOISONPAT0 . ECC_POISON_DATA_31_0
 */
#define  VTSS_F_DDR_UMCTL2_ECCPOISONPAT0_ECC_POISON_DATA_31_0(x)  (x)
#define  VTSS_M_DDR_UMCTL2_ECCPOISONPAT0_ECC_POISON_DATA_31_0     0xffffffff
#define  VTSS_X_DDR_UMCTL2_ECCPOISONPAT0_ECC_POISON_DATA_31_0(x)  (x)


/**
 * \brief ECC Poison Pattern 2 Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCPOISONPAT2
 */
#define VTSS_DDR_UMCTL2_ECCPOISONPAT2        VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xe1)

/**
 * \brief
 * Indicates the poison pattern for DRAM data[71:64].
 *
 *   Setting this bit to 1 indicates poison (invert) corresponding DRAM
 * bit.
 * It is indirect register. Selector is ADVECCINDEX.ecc_poison_beats_sel.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_ECCPOISONPAT2 . ECC_POISON_DATA_71_64
 */
#define  VTSS_F_DDR_UMCTL2_ECCPOISONPAT2_ECC_POISON_DATA_71_64(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_UMCTL2_ECCPOISONPAT2_ECC_POISON_DATA_71_64     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_UMCTL2_ECCPOISONPAT2_ECC_POISON_DATA_71_64(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Address protection within ECC Status Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCAPSTAT
 */
#define VTSS_DDR_UMCTL2_ECCAPSTAT            VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xe2)

/**
 * \brief
 * Indicates the number of ECC errors (correctable/uncorrectable) within
 * one burst exceeded the threshold(ECCCFG0.ecc_ap_err_threshold).
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_ECCAPSTAT . ECC_AP_ERR
 */
#define  VTSS_F_DDR_UMCTL2_ECCAPSTAT_ECC_AP_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_ECCAPSTAT_ECC_AP_ERR  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_ECCAPSTAT_ECC_AP_ERR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a DDR_UMCTL2:UMCTL2_MP
 *
 * uMCTL2 Multi-Port Registers
 */


/**
 * \brief Port Status Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PSTAT
 */
#define VTSS_DDR_UMCTL2_PSTAT                VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xff)

/**
 * \brief
 * Indicates if there are outstanding reads for AXI port 0.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PSTAT . RD_PORT_BUSY_0
 */
#define  VTSS_F_DDR_UMCTL2_PSTAT_RD_PORT_BUSY_0(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_PSTAT_RD_PORT_BUSY_0  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_PSTAT_RD_PORT_BUSY_0(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Indicates if there are outstanding reads for AXI port 1.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PSTAT . RD_PORT_BUSY_1
 */
#define  VTSS_F_DDR_UMCTL2_PSTAT_RD_PORT_BUSY_1(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_PSTAT_RD_PORT_BUSY_1  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_PSTAT_RD_PORT_BUSY_1(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Indicates if there are outstanding reads for AXI port 2.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PSTAT . RD_PORT_BUSY_2
 */
#define  VTSS_F_DDR_UMCTL2_PSTAT_RD_PORT_BUSY_2(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_UMCTL2_PSTAT_RD_PORT_BUSY_2  VTSS_BIT(2)
#define  VTSS_X_DDR_UMCTL2_PSTAT_RD_PORT_BUSY_2(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Indicates if there are outstanding writes for AXI port 0.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PSTAT . WR_PORT_BUSY_0
 */
#define  VTSS_F_DDR_UMCTL2_PSTAT_WR_PORT_BUSY_0(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DDR_UMCTL2_PSTAT_WR_PORT_BUSY_0  VTSS_BIT(16)
#define  VTSS_X_DDR_UMCTL2_PSTAT_WR_PORT_BUSY_0(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Indicates if there are outstanding writes for AXI port 1.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PSTAT . WR_PORT_BUSY_1
 */
#define  VTSS_F_DDR_UMCTL2_PSTAT_WR_PORT_BUSY_1(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_DDR_UMCTL2_PSTAT_WR_PORT_BUSY_1  VTSS_BIT(17)
#define  VTSS_X_DDR_UMCTL2_PSTAT_WR_PORT_BUSY_1(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Indicates if there are outstanding writes for AXI port 2.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PSTAT . WR_PORT_BUSY_2
 */
#define  VTSS_F_DDR_UMCTL2_PSTAT_WR_PORT_BUSY_2(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_DDR_UMCTL2_PSTAT_WR_PORT_BUSY_2  VTSS_BIT(18)
#define  VTSS_X_DDR_UMCTL2_PSTAT_WR_PORT_BUSY_2(x)  VTSS_EXTRACT_BITFIELD(x,18,1)


/**
 * \brief Port Common Configuration Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCCFG
 */
#define VTSS_DDR_UMCTL2_PCCFG                VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x100)

/**
 * \brief
 * If enabled, sets co_gs_go2critical_wr and
 * co_gs_go2critical_lpr/co_gs_go2critical_hpr signals going to DDRC based
 * on urgent input (awurgent, arurgent) coming from AXI master.
 * If disabled, co_gs_go2critical_wr and
 * co_gs_go2critical_lpr/co_gs_go2critical_hpr signals at DDRC are driven
 * to 1b'0.
 * For uPCTL2, this register field must be set to 0.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCCFG . GO2CRITICAL_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCCFG_GO2CRITICAL_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_PCCFG_GO2CRITICAL_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_PCCFG_GO2CRITICAL_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Page match four limit.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCCFG . PAGEMATCH_LIMIT
 */
#define  VTSS_F_DDR_UMCTL2_PCCFG_PAGEMATCH_LIMIT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_PCCFG_PAGEMATCH_LIMIT  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_PCCFG_PAGEMATCH_LIMIT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Burst length expansion mode.
 * This applies to both reads and writes. When MSTR.data_bus_width==00,
 * setting bl_exp_mode to 1 has no effect.
 * This can be used in order to avoid or minimize t_ccd_l penalty in DDR4
 * and t_ccd_mw penalty in LPDDR4. Hence, bl_exp_mode=1 is only recommended
 * if DDR4 or LPDDR4.
 * Note that if DBICTL.dm_en=0, functionality is not supported in the
 * following cases:
 *  - MSTR.data_bus_width=01, MEMC_BURST_LENGTH=8 and MSTR.burst_rdwr=1000
 * (LPDDR4 only)
 *  - MSTR.data_bus_width=01, MEMC_BURST_LENGTH=4 and MSTR.burst_rdwr=0100
 * (DDR4 only), with either MSTR.burstchop=0 or CRCPARCTL1.crc_enable=1
 * Functionality is also not supported if Data Channel Interleave is
 * enabled.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCCFG . BL_EXP_MODE
 */
#define  VTSS_F_DDR_UMCTL2_PCCFG_BL_EXP_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DDR_UMCTL2_PCCFG_BL_EXP_MODE  VTSS_BIT(8)
#define  VTSS_X_DDR_UMCTL2_PCCFG_BL_EXP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)


/**
 * \brief Port n Configuration Read Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGR_0
 */
#define VTSS_DDR_UMCTL2_PCFGR_0              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x101)

/**
 * \brief
 * Determines the initial load value of read aging counters.
 * These counters are parallel loaded after reset, or after each grant to
 * the corresponding port.
 *  The aging counters down-count every clock cycle where the port is
 * requesting but not granted. The higher significant 5-bits of the read
 * aging counter sets the priority of the read channel of a given port.
 * Port's priority increases as the higher significant 5-bits of the
 * counter starts to decrease.
 * When the aging counter becomes 0, the corresponding port channel has the
 * highest priority level (timeout condition - Priority0).
 * For multi-port configurations, the aging counters cannot be used to set
 * port priorities when external dynamic priority  inputs (arqos) are
 * enabled (timeout is still applicable).
 * For single port configurations, the aging counters are only used when
 * they timeout (become 0) to force read-write direction switching.
 *  In this case, external dynamic priority input, arqos (for reads only)
 * can still be used to set the DDRC read priority (2 priority levels: low
 * priority read - LPR, high priority read - HPR) on a command by command
 * basis.
 * Note: The two LSBs of this register field are tied internally to 2'b00.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGR_0 . PCFGR_0_RD_PORT_PRIORITY
 */
#define  VTSS_F_DDR_UMCTL2_PCFGR_0_PCFGR_0_RD_PORT_PRIORITY(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_DDR_UMCTL2_PCFGR_0_PCFGR_0_RD_PORT_PRIORITY     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_DDR_UMCTL2_PCFGR_0_PCFGR_0_RD_PORT_PRIORITY(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * \brief
 * Sets aging function for the read channel of the port.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCFGR_0 . PCFGR_0_RD_PORT_AGING_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCFGR_0_PCFGR_0_RD_PORT_AGING_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DDR_UMCTL2_PCFGR_0_PCFGR_0_RD_PORT_AGING_EN  VTSS_BIT(12)
#define  VTSS_X_DDR_UMCTL2_PCFGR_0_PCFGR_0_RD_PORT_AGING_EN(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Sets the AXI urgent sideband signal (arurgent). When enabled and
 * arurgent is asserted by the master, that port becomes the highest
 * priority and co_gs_go2critical_lpr/co_gs_go2critical_hpr signal to DDRC
 * is asserted if enabled in PCCFG.go2critical_en register.
 * Note that arurgent signal can be asserted anytime and as long as
 * required which is independent of address handshaking (it is not
 * associated with any particular command).
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCFGR_0 . PCFGR_0_RD_PORT_URGENT_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCFGR_0_PCFGR_0_RD_PORT_URGENT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DDR_UMCTL2_PCFGR_0_PCFGR_0_RD_PORT_URGENT_EN  VTSS_BIT(13)
#define  VTSS_X_DDR_UMCTL2_PCFGR_0_PCFGR_0_RD_PORT_URGENT_EN(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Sets the Page Match feature. If enabled, once a requesting port is
 * granted, the port is continued to be granted if the following immediate
 * commands are to the same memory page (same rank, same bank and same
 * row).
 * See also related PCCFG.pagematch_limit register.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCFGR_0 . PCFGR_0_RD_PORT_PAGEMATCH_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCFGR_0_PCFGR_0_RD_PORT_PAGEMATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_DDR_UMCTL2_PCFGR_0_PCFGR_0_RD_PORT_PAGEMATCH_EN  VTSS_BIT(14)
#define  VTSS_X_DDR_UMCTL2_PCFGR_0_PCFGR_0_RD_PORT_PAGEMATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,14,1)


/**
 * \brief Port n Configuration Write Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGW_0
 */
#define VTSS_DDR_UMCTL2_PCFGW_0              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x102)

/**
 * \brief
 * Determines the initial load value of write aging counters.
 * These counters are parallel loaded after reset, or after each grant to
 * the corresponding port.
 * The aging counters down-count every clock cycle where the port is
 * requesting but not granted.
 * The higher significant 5-bits of the write aging counter sets the
 * initial priority of the write channel of a given port.
 * Port's priority increases as the higher significant 5-bits of the
 * counter starts to decrease. When the aging counter becomes 0, the
 * corresponding port channel has the highest priority level.
 * For multi-port configurations, the aging counters cannot be used to set
 * port priorities when external dynamic priority  inputs (awqos) are
 * enabled (timeout is still applicable).
 * For single port configurations, the aging counters are only used when
 * they timeout (become 0) to force read-write direction switching.
 * Note: The two LSBs of this register field are tied internally to 2'b00.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGW_0 . PCFGW_0_WR_PORT_PRIORITY
 */
#define  VTSS_F_DDR_UMCTL2_PCFGW_0_PCFGW_0_WR_PORT_PRIORITY(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_DDR_UMCTL2_PCFGW_0_PCFGW_0_WR_PORT_PRIORITY     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_DDR_UMCTL2_PCFGW_0_PCFGW_0_WR_PORT_PRIORITY(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * \brief
 * Sets aging function for the write channel of the port.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCFGW_0 . PCFGW_0_WR_PORT_AGING_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCFGW_0_PCFGW_0_WR_PORT_AGING_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DDR_UMCTL2_PCFGW_0_PCFGW_0_WR_PORT_AGING_EN  VTSS_BIT(12)
#define  VTSS_X_DDR_UMCTL2_PCFGW_0_PCFGW_0_WR_PORT_AGING_EN(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Sets the AXI urgent sideband signal (awurgent).
 * When enabled and awurgent is asserted by the master, that port becomes
 * the highest priority and co_gs_go2critical_wr signal to DDRC is asserted
 * if enabled in PCCFG.go2critical_en register.
 * Note that awurgent signal can be asserted anytime and as long as
 * required which is independent of address handshaking (it is not
 * associated with any particular command).
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCFGW_0 . PCFGW_0_WR_PORT_URGENT_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCFGW_0_PCFGW_0_WR_PORT_URGENT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DDR_UMCTL2_PCFGW_0_PCFGW_0_WR_PORT_URGENT_EN  VTSS_BIT(13)
#define  VTSS_X_DDR_UMCTL2_PCFGW_0_PCFGW_0_WR_PORT_URGENT_EN(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Sets the Page Match feature.
 * If enabled, once a requesting port is granted, the port is continued to
 * be granted if the following immediate commands are to the same memory
 * page (same rank, same bank and same row).
 * See also related PCCFG.pagematch_limit register.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCFGW_0 . PCFGW_0_WR_PORT_PAGEMATCH_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCFGW_0_PCFGW_0_WR_PORT_PAGEMATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_DDR_UMCTL2_PCFGW_0_PCFGW_0_WR_PORT_PAGEMATCH_EN  VTSS_BIT(14)
#define  VTSS_X_DDR_UMCTL2_PCFGW_0_PCFGW_0_WR_PORT_PAGEMATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,14,1)


/**
 * \brief Port n Control Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCTRL_0
 */
#define VTSS_DDR_UMCTL2_PCTRL_0              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x124)

/**
 * \brief
 * Enables AXI port n.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCTRL_0 . PCTRL_0_PORT_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCTRL_0_PCTRL_0_PORT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_PCTRL_0_PCTRL_0_PORT_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_PCTRL_0_PCTRL_0_PORT_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Port n Read QoS Configuration Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGQOS0_0
 */
#define VTSS_DDR_UMCTL2_PCFGQOS0_0           VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x125)

/**
 * \brief
 * Separation level1 indicating the end of region0 mapping; start of
 * region0 is 0. Possible values for level1 are 0 to 13 (for dual RAQ) or 0
 * to 14 (for single RAQ) which corresponds to arqos.
 * Note that for PA, arqos values are used directly as port priorities,
 * where the higher the value corresponds to higher port priority.
 * All of the map_level* registers must be set to distinct values.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGQOS0_0 . PCFGQOS0_0_RQOS_MAP_LEVEL1
 */
#define  VTSS_F_DDR_UMCTL2_PCFGQOS0_0_PCFGQOS0_0_RQOS_MAP_LEVEL1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_PCFGQOS0_0_PCFGQOS0_0_RQOS_MAP_LEVEL1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_PCFGQOS0_0_PCFGQOS0_0_RQOS_MAP_LEVEL1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * This bit field indicates the traffic class of region 0.
 * Valid values are:
 *  - 0 - LPR
 *  - 1 - VPR
 *  - 2 - HPR
 * For dual address queue configurations, region 0 maps to the blue address
 * queue.
 * In this case, valid values are:
 * 0: LPR and 1: VPR only.
 * When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of
 * region0 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGQOS0_0 . PCFGQOS0_0_RQOS_MAP_REGION0
 */
#define  VTSS_F_DDR_UMCTL2_PCFGQOS0_0_PCFGQOS0_0_RQOS_MAP_REGION0(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_DDR_UMCTL2_PCFGQOS0_0_PCFGQOS0_0_RQOS_MAP_REGION0     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_DDR_UMCTL2_PCFGQOS0_0_PCFGQOS0_0_RQOS_MAP_REGION0(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * This bit field indicates the traffic class of region 1.
 * Valid values are:
 *  - 0 - LPR
 *  - 1 - VPR
 *  - 2 - HPR
 *  For dual address queue configurations, region1 maps to the blue address
 * queue.
 * In this case, valid values are
 *  - 0 - LPR
 *  - 1 - VPR only
 *  When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of
 * region 1 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGQOS0_0 . PCFGQOS0_0_RQOS_MAP_REGION1
 */
#define  VTSS_F_DDR_UMCTL2_PCFGQOS0_0_PCFGQOS0_0_RQOS_MAP_REGION1(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_DDR_UMCTL2_PCFGQOS0_0_PCFGQOS0_0_RQOS_MAP_REGION1     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_DDR_UMCTL2_PCFGQOS0_0_PCFGQOS0_0_RQOS_MAP_REGION1(x)  VTSS_EXTRACT_BITFIELD(x,20,2)


/**
 * \brief Port n Read QoS Configuration Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGQOS1_0
 */
#define VTSS_DDR_UMCTL2_PCFGQOS1_0           VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x126)

/**
 * \brief
 * Specifies the timeout value for transactions mapped to the blue address
 * queue.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGQOS1_0 . PCFGQOS1_0_RQOS_MAP_TIMEOUTB
 */
#define  VTSS_F_DDR_UMCTL2_PCFGQOS1_0_PCFGQOS1_0_RQOS_MAP_TIMEOUTB(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_DDR_UMCTL2_PCFGQOS1_0_PCFGQOS1_0_RQOS_MAP_TIMEOUTB     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_DDR_UMCTL2_PCFGQOS1_0_PCFGQOS1_0_RQOS_MAP_TIMEOUTB(x)  VTSS_EXTRACT_BITFIELD(x,0,11)

/**
 * \brief
 * Specifies the timeout value for transactions mapped to the red address
 * queue.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGQOS1_0 . PCFGQOS1_0_RQOS_MAP_TIMEOUTR
 */
#define  VTSS_F_DDR_UMCTL2_PCFGQOS1_0_PCFGQOS1_0_RQOS_MAP_TIMEOUTR(x)  VTSS_ENCODE_BITFIELD(x,16,11)
#define  VTSS_M_DDR_UMCTL2_PCFGQOS1_0_PCFGQOS1_0_RQOS_MAP_TIMEOUTR     VTSS_ENCODE_BITMASK(16,11)
#define  VTSS_X_DDR_UMCTL2_PCFGQOS1_0_PCFGQOS1_0_RQOS_MAP_TIMEOUTR(x)  VTSS_EXTRACT_BITFIELD(x,16,11)


/**
 * \brief Port n Write QoS Configuration Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGWQOS0_0
 */
#define VTSS_DDR_UMCTL2_PCFGWQOS0_0          VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x127)

/**
 * \brief
 * Separation level indicating the end of region0 mapping; start of region0
 * is 0.
 * Possible values for level1 are 0 to 13 which corresponds to awqos.
 * Note that for PA, awqos values are used directly as port priorities,
 * where the higher the value corresponds to higher port priority.
 * All of the map_level* registers must be set to distinct values.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS0_0 . PCFGWQOS0_0_WQOS_MAP_LEVEL1
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS0_0_PCFGWQOS0_0_WQOS_MAP_LEVEL1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS0_0_PCFGWQOS0_0_WQOS_MAP_LEVEL1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS0_0_PCFGWQOS0_0_WQOS_MAP_LEVEL1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Separation level2 indicating the end of region1 mapping; start of
 * region1 is (level1 + 1).
 * Possible values for level2 are (level1 + 1) to 14 which corresponds to
 * awqos.
 * Region2 starts from (level2 + 1) up to 15.
 * Note that for PA, awqos values are used directly as port priorities,
 * where the higher the value corresponds to higher port priority.
 * All of the map_level* registers must be set to distinct values.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS0_0 . PCFGWQOS0_0_WQOS_MAP_LEVEL2
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS0_0_PCFGWQOS0_0_WQOS_MAP_LEVEL2(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS0_0_PCFGWQOS0_0_WQOS_MAP_LEVEL2     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS0_0_PCFGWQOS0_0_WQOS_MAP_LEVEL2(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * This bit field indicates the traffic class of region 0.
 * Valid values are:
 *  - 0 - NPW
 *  - 1 - VPW
 * When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of
 * region 0 is set to 1 (VPW), VPW traffic is aliased to NPW traffic.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS0_0 . PCFGWQOS0_0_WQOS_MAP_REGION0
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS0_0_PCFGWQOS0_0_WQOS_MAP_REGION0(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS0_0_PCFGWQOS0_0_WQOS_MAP_REGION0     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS0_0_PCFGWQOS0_0_WQOS_MAP_REGION0(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * This bit field indicates the traffic class of region 1.
 * Valid values are:
 * 0: NPW, 1: VPW.
 * When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of
 * region 1 is set to 1 (VPW), VPW traffic is aliased to NPW traffic.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS0_0 . PCFGWQOS0_0_WQOS_MAP_REGION1
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS0_0_PCFGWQOS0_0_WQOS_MAP_REGION1(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS0_0_PCFGWQOS0_0_WQOS_MAP_REGION1     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS0_0_PCFGWQOS0_0_WQOS_MAP_REGION1(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * This bit field indicates the traffic class of region 2.
 * Valid values are:
 *  - 0 - NPW
 *  - 1 - VPW
 * When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of
 * region 2 is set to 1 (VPW), VPW traffic is aliased to NPW traffic.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS0_0 . PCFGWQOS0_0_WQOS_MAP_REGION2
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS0_0_PCFGWQOS0_0_WQOS_MAP_REGION2(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS0_0_PCFGWQOS0_0_WQOS_MAP_REGION2     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS0_0_PCFGWQOS0_0_WQOS_MAP_REGION2(x)  VTSS_EXTRACT_BITFIELD(x,24,2)


/**
 * \brief Port n Write QoS Configuration Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGWQOS1_0
 */
#define VTSS_DDR_UMCTL2_PCFGWQOS1_0          VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x128)

/**
 * \brief
 * Specifies the timeout value for write transactions in region 0 and 1.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS1_0 . PCFGWQOS1_0_WQOS_MAP_TIMEOUT1
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS1_0_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS1_0_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS1_0_PCFGWQOS1_0_WQOS_MAP_TIMEOUT1(x)  VTSS_EXTRACT_BITFIELD(x,0,11)

/**
 * \brief
 * Specifies the timeout value for write transactions in region 2.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS1_0 . PCFGWQOS1_0_WQOS_MAP_TIMEOUT2
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS1_0_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2(x)  VTSS_ENCODE_BITFIELD(x,16,11)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS1_0_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2     VTSS_ENCODE_BITMASK(16,11)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS1_0_PCFGWQOS1_0_WQOS_MAP_TIMEOUT2(x)  VTSS_EXTRACT_BITFIELD(x,16,11)


/**
 * \brief Port n Configuration Read Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGR_1
 */
#define VTSS_DDR_UMCTL2_PCFGR_1              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x12d)

/**
 * \brief
 * Determines the initial load value of read aging counters.
 * These counters are parallel loaded after reset, or after each grant to
 * the corresponding port.
 *  The aging counters down-count every clock cycle where the port is
 * requesting but not granted. The higher significant 5-bits of the read
 * aging counter sets the priority of the read channel of a given port.
 * Port's priority increases as the higher significant 5-bits of the
 * counter starts to decrease.
 * When the aging counter becomes 0, the corresponding port channel has the
 * highest priority level (timeout condition - Priority0).
 * For multi-port configurations, the aging counters cannot be used to set
 * port priorities when external dynamic priority  inputs (arqos) are
 * enabled (timeout is still applicable).
 * For single port configurations, the aging counters are only used when
 * they timeout (become 0) to force read-write direction switching.
 *  In this case, external dynamic priority input, arqos (for reads only)
 * can still be used to set the DDRC read priority (2 priority levels: low
 * priority read - LPR, high priority read - HPR) on a command by command
 * basis.
 * Note: The two LSBs of this register field are tied internally to 2'b00.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGR_1 . PCFGR_1_RD_PORT_PRIORITY
 */
#define  VTSS_F_DDR_UMCTL2_PCFGR_1_PCFGR_1_RD_PORT_PRIORITY(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_DDR_UMCTL2_PCFGR_1_PCFGR_1_RD_PORT_PRIORITY     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_DDR_UMCTL2_PCFGR_1_PCFGR_1_RD_PORT_PRIORITY(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * \brief
 * Sets aging function for the read channel of the port.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCFGR_1 . PCFGR_1_RD_PORT_AGING_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCFGR_1_PCFGR_1_RD_PORT_AGING_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DDR_UMCTL2_PCFGR_1_PCFGR_1_RD_PORT_AGING_EN  VTSS_BIT(12)
#define  VTSS_X_DDR_UMCTL2_PCFGR_1_PCFGR_1_RD_PORT_AGING_EN(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Sets the AXI urgent sideband signal (arurgent). When enabled and
 * arurgent is asserted by the master, that port becomes the highest
 * priority and co_gs_go2critical_lpr/co_gs_go2critical_hpr signal to DDRC
 * is asserted if enabled in PCCFG.go2critical_en register.
 * Note that arurgent signal can be asserted anytime and as long as
 * required which is independent of address handshaking (it is not
 * associated with any particular command).
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCFGR_1 . PCFGR_1_RD_PORT_URGENT_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCFGR_1_PCFGR_1_RD_PORT_URGENT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DDR_UMCTL2_PCFGR_1_PCFGR_1_RD_PORT_URGENT_EN  VTSS_BIT(13)
#define  VTSS_X_DDR_UMCTL2_PCFGR_1_PCFGR_1_RD_PORT_URGENT_EN(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Sets the Page Match feature. If enabled, once a requesting port is
 * granted, the port is continued to be granted if the following immediate
 * commands are to the same memory page (same rank, same bank and same
 * row).
 * See also related PCCFG.pagematch_limit register.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCFGR_1 . PCFGR_1_RD_PORT_PAGEMATCH_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCFGR_1_PCFGR_1_RD_PORT_PAGEMATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_DDR_UMCTL2_PCFGR_1_PCFGR_1_RD_PORT_PAGEMATCH_EN  VTSS_BIT(14)
#define  VTSS_X_DDR_UMCTL2_PCFGR_1_PCFGR_1_RD_PORT_PAGEMATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,14,1)


/**
 * \brief Port n Configuration Write Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGW_1
 */
#define VTSS_DDR_UMCTL2_PCFGW_1              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x12e)

/**
 * \brief
 * Determines the initial load value of write aging counters.
 * These counters are parallel loaded after reset, or after each grant to
 * the corresponding port.
 * The aging counters down-count every clock cycle where the port is
 * requesting but not granted.
 * The higher significant 5-bits of the write aging counter sets the
 * initial priority of the write channel of a given port.
 * Port's priority increases as the higher significant 5-bits of the
 * counter starts to decrease. When the aging counter becomes 0, the
 * corresponding port channel has the highest priority level.
 * For multi-port configurations, the aging counters cannot be used to set
 * port priorities when external dynamic priority  inputs (awqos) are
 * enabled (timeout is still applicable).
 * For single port configurations, the aging counters are only used when
 * they timeout (become 0) to force read-write direction switching.
 * Note: The two LSBs of this register field are tied internally to 2'b00.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGW_1 . PCFGW_1_WR_PORT_PRIORITY
 */
#define  VTSS_F_DDR_UMCTL2_PCFGW_1_PCFGW_1_WR_PORT_PRIORITY(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_DDR_UMCTL2_PCFGW_1_PCFGW_1_WR_PORT_PRIORITY     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_DDR_UMCTL2_PCFGW_1_PCFGW_1_WR_PORT_PRIORITY(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * \brief
 * Sets aging function for the write channel of the port.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCFGW_1 . PCFGW_1_WR_PORT_AGING_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCFGW_1_PCFGW_1_WR_PORT_AGING_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DDR_UMCTL2_PCFGW_1_PCFGW_1_WR_PORT_AGING_EN  VTSS_BIT(12)
#define  VTSS_X_DDR_UMCTL2_PCFGW_1_PCFGW_1_WR_PORT_AGING_EN(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Sets the AXI urgent sideband signal (awurgent).
 * When enabled and awurgent is asserted by the master, that port becomes
 * the highest priority and co_gs_go2critical_wr signal to DDRC is asserted
 * if enabled in PCCFG.go2critical_en register.
 * Note that awurgent signal can be asserted anytime and as long as
 * required which is independent of address handshaking (it is not
 * associated with any particular command).
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCFGW_1 . PCFGW_1_WR_PORT_URGENT_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCFGW_1_PCFGW_1_WR_PORT_URGENT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DDR_UMCTL2_PCFGW_1_PCFGW_1_WR_PORT_URGENT_EN  VTSS_BIT(13)
#define  VTSS_X_DDR_UMCTL2_PCFGW_1_PCFGW_1_WR_PORT_URGENT_EN(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Sets the Page Match feature.
 * If enabled, once a requesting port is granted, the port is continued to
 * be granted if the following immediate commands are to the same memory
 * page (same rank, same bank and same row).
 * See also related PCCFG.pagematch_limit register.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCFGW_1 . PCFGW_1_WR_PORT_PAGEMATCH_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCFGW_1_PCFGW_1_WR_PORT_PAGEMATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_DDR_UMCTL2_PCFGW_1_PCFGW_1_WR_PORT_PAGEMATCH_EN  VTSS_BIT(14)
#define  VTSS_X_DDR_UMCTL2_PCFGW_1_PCFGW_1_WR_PORT_PAGEMATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,14,1)


/**
 * \brief Port n Control Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCTRL_1
 */
#define VTSS_DDR_UMCTL2_PCTRL_1              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x150)

/**
 * \brief
 * Enables AXI port n.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCTRL_1 . PCTRL_1_PORT_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCTRL_1_PCTRL_1_PORT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_PCTRL_1_PCTRL_1_PORT_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_PCTRL_1_PCTRL_1_PORT_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Port n Read QoS Configuration Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGQOS0_1
 */
#define VTSS_DDR_UMCTL2_PCFGQOS0_1           VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x151)

/**
 * \brief
 * Separation level1 indicating the end of region0 mapping; start of
 * region0 is 0. Possible values for level1 are 0 to 13 (for dual RAQ) or 0
 * to 14 (for single RAQ) which corresponds to arqos.
 * Note that for PA, arqos values are used directly as port priorities,
 * where the higher the value corresponds to higher port priority.
 * All of the map_level* registers must be set to distinct values.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGQOS0_1 . PCFGQOS0_1_RQOS_MAP_LEVEL1
 */
#define  VTSS_F_DDR_UMCTL2_PCFGQOS0_1_PCFGQOS0_1_RQOS_MAP_LEVEL1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_PCFGQOS0_1_PCFGQOS0_1_RQOS_MAP_LEVEL1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_PCFGQOS0_1_PCFGQOS0_1_RQOS_MAP_LEVEL1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * This bit field indicates the traffic class of region 0.
 * Valid values are:
 *  - 0 - LPR
 *  - 1 - VPR
 *  - 2 - HPR
 * For dual address queue configurations, region 0 maps to the blue address
 * queue.
 * In this case, valid values are:
 * 0: LPR and 1: VPR only.
 * When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of
 * region0 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGQOS0_1 . PCFGQOS0_1_RQOS_MAP_REGION0
 */
#define  VTSS_F_DDR_UMCTL2_PCFGQOS0_1_PCFGQOS0_1_RQOS_MAP_REGION0(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_DDR_UMCTL2_PCFGQOS0_1_PCFGQOS0_1_RQOS_MAP_REGION0     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_DDR_UMCTL2_PCFGQOS0_1_PCFGQOS0_1_RQOS_MAP_REGION0(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * This bit field indicates the traffic class of region 1.
 * Valid values are:
 *  - 0 - LPR
 *  - 1 - VPR
 *  - 2 - HPR
 *  For dual address queue configurations, region1 maps to the blue address
 * queue.
 * In this case, valid values are
 *  - 0 - LPR
 *  - 1 - VPR only
 *  When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of
 * region 1 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGQOS0_1 . PCFGQOS0_1_RQOS_MAP_REGION1
 */
#define  VTSS_F_DDR_UMCTL2_PCFGQOS0_1_PCFGQOS0_1_RQOS_MAP_REGION1(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_DDR_UMCTL2_PCFGQOS0_1_PCFGQOS0_1_RQOS_MAP_REGION1     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_DDR_UMCTL2_PCFGQOS0_1_PCFGQOS0_1_RQOS_MAP_REGION1(x)  VTSS_EXTRACT_BITFIELD(x,20,2)


/**
 * \brief Port n Read QoS Configuration Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGQOS1_1
 */
#define VTSS_DDR_UMCTL2_PCFGQOS1_1           VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x152)

/**
 * \brief
 * Specifies the timeout value for transactions mapped to the blue address
 * queue.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGQOS1_1 . PCFGQOS1_1_RQOS_MAP_TIMEOUTB
 */
#define  VTSS_F_DDR_UMCTL2_PCFGQOS1_1_PCFGQOS1_1_RQOS_MAP_TIMEOUTB(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_DDR_UMCTL2_PCFGQOS1_1_PCFGQOS1_1_RQOS_MAP_TIMEOUTB     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_DDR_UMCTL2_PCFGQOS1_1_PCFGQOS1_1_RQOS_MAP_TIMEOUTB(x)  VTSS_EXTRACT_BITFIELD(x,0,11)

/**
 * \brief
 * Specifies the timeout value for transactions mapped to the red address
 * queue.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGQOS1_1 . PCFGQOS1_1_RQOS_MAP_TIMEOUTR
 */
#define  VTSS_F_DDR_UMCTL2_PCFGQOS1_1_PCFGQOS1_1_RQOS_MAP_TIMEOUTR(x)  VTSS_ENCODE_BITFIELD(x,16,11)
#define  VTSS_M_DDR_UMCTL2_PCFGQOS1_1_PCFGQOS1_1_RQOS_MAP_TIMEOUTR     VTSS_ENCODE_BITMASK(16,11)
#define  VTSS_X_DDR_UMCTL2_PCFGQOS1_1_PCFGQOS1_1_RQOS_MAP_TIMEOUTR(x)  VTSS_EXTRACT_BITFIELD(x,16,11)


/**
 * \brief Port n Write QoS Configuration Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGWQOS0_1
 */
#define VTSS_DDR_UMCTL2_PCFGWQOS0_1          VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x153)

/**
 * \brief
 * Separation level indicating the end of region0 mapping; start of region0
 * is 0.
 * Possible values for level1 are 0 to 13 which corresponds to awqos.
 * Note that for PA, awqos values are used directly as port priorities,
 * where the higher the value corresponds to higher port priority.
 * All of the map_level* registers must be set to distinct values.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS0_1 . PCFGWQOS0_1_WQOS_MAP_LEVEL1
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS0_1_PCFGWQOS0_1_WQOS_MAP_LEVEL1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS0_1_PCFGWQOS0_1_WQOS_MAP_LEVEL1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS0_1_PCFGWQOS0_1_WQOS_MAP_LEVEL1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Separation level2 indicating the end of region1 mapping; start of
 * region1 is (level1 + 1).
 * Possible values for level2 are (level1 + 1) to 14 which corresponds to
 * awqos.
 * Region2 starts from (level2 + 1) up to 15.
 * Note that for PA, awqos values are used directly as port priorities,
 * where the higher the value corresponds to higher port priority.
 * All of the map_level* registers must be set to distinct values.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS0_1 . PCFGWQOS0_1_WQOS_MAP_LEVEL2
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS0_1_PCFGWQOS0_1_WQOS_MAP_LEVEL2(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS0_1_PCFGWQOS0_1_WQOS_MAP_LEVEL2     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS0_1_PCFGWQOS0_1_WQOS_MAP_LEVEL2(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * This bit field indicates the traffic class of region 0.
 * Valid values are:
 *  - 0 - NPW
 *  - 1 - VPW
 * When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of
 * region 0 is set to 1 (VPW), VPW traffic is aliased to NPW traffic.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS0_1 . PCFGWQOS0_1_WQOS_MAP_REGION0
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS0_1_PCFGWQOS0_1_WQOS_MAP_REGION0(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS0_1_PCFGWQOS0_1_WQOS_MAP_REGION0     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS0_1_PCFGWQOS0_1_WQOS_MAP_REGION0(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * This bit field indicates the traffic class of region 1.
 * Valid values are:
 * 0: NPW, 1: VPW.
 * When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of
 * region 1 is set to 1 (VPW), VPW traffic is aliased to NPW traffic.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS0_1 . PCFGWQOS0_1_WQOS_MAP_REGION1
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS0_1_PCFGWQOS0_1_WQOS_MAP_REGION1(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS0_1_PCFGWQOS0_1_WQOS_MAP_REGION1     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS0_1_PCFGWQOS0_1_WQOS_MAP_REGION1(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * This bit field indicates the traffic class of region 2.
 * Valid values are:
 *  - 0 - NPW
 *  - 1 - VPW
 * When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of
 * region 2 is set to 1 (VPW), VPW traffic is aliased to NPW traffic.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS0_1 . PCFGWQOS0_1_WQOS_MAP_REGION2
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS0_1_PCFGWQOS0_1_WQOS_MAP_REGION2(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS0_1_PCFGWQOS0_1_WQOS_MAP_REGION2     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS0_1_PCFGWQOS0_1_WQOS_MAP_REGION2(x)  VTSS_EXTRACT_BITFIELD(x,24,2)


/**
 * \brief Port n Write QoS Configuration Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGWQOS1_1
 */
#define VTSS_DDR_UMCTL2_PCFGWQOS1_1          VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x154)

/**
 * \brief
 * Specifies the timeout value for write transactions in region 0 and 1.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS1_1 . PCFGWQOS1_1_WQOS_MAP_TIMEOUT1
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS1_1_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS1_1_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS1_1_PCFGWQOS1_1_WQOS_MAP_TIMEOUT1(x)  VTSS_EXTRACT_BITFIELD(x,0,11)

/**
 * \brief
 * Specifies the timeout value for write transactions in region 2.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS1_1 . PCFGWQOS1_1_WQOS_MAP_TIMEOUT2
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS1_1_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2(x)  VTSS_ENCODE_BITFIELD(x,16,11)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS1_1_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2     VTSS_ENCODE_BITMASK(16,11)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS1_1_PCFGWQOS1_1_WQOS_MAP_TIMEOUT2(x)  VTSS_EXTRACT_BITFIELD(x,16,11)


/**
 * \brief Port n Configuration Read Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGR_2
 */
#define VTSS_DDR_UMCTL2_PCFGR_2              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x159)

/**
 * \brief
 * Determines the initial load value of read aging counters.
 * These counters are parallel loaded after reset, or after each grant to
 * the corresponding port.
 *  The aging counters down-count every clock cycle where the port is
 * requesting but not granted. The higher significant 5-bits of the read
 * aging counter sets the priority of the read channel of a given port.
 * Port's priority increases as the higher significant 5-bits of the
 * counter starts to decrease.
 * When the aging counter becomes 0, the corresponding port channel has the
 * highest priority level (timeout condition - Priority0).
 * For multi-port configurations, the aging counters cannot be used to set
 * port priorities when external dynamic priority  inputs (arqos) are
 * enabled (timeout is still applicable).
 * For single port configurations, the aging counters are only used when
 * they timeout (become 0) to force read-write direction switching.
 *  In this case, external dynamic priority input, arqos (for reads only)
 * can still be used to set the DDRC read priority (2 priority levels: low
 * priority read - LPR, high priority read - HPR) on a command by command
 * basis.
 * Note: The two LSBs of this register field are tied internally to 2'b00.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGR_2 . PCFGR_2_RD_PORT_PRIORITY
 */
#define  VTSS_F_DDR_UMCTL2_PCFGR_2_PCFGR_2_RD_PORT_PRIORITY(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_DDR_UMCTL2_PCFGR_2_PCFGR_2_RD_PORT_PRIORITY     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_DDR_UMCTL2_PCFGR_2_PCFGR_2_RD_PORT_PRIORITY(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * \brief
 * Sets aging function for the read channel of the port.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCFGR_2 . PCFGR_2_RD_PORT_AGING_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCFGR_2_PCFGR_2_RD_PORT_AGING_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DDR_UMCTL2_PCFGR_2_PCFGR_2_RD_PORT_AGING_EN  VTSS_BIT(12)
#define  VTSS_X_DDR_UMCTL2_PCFGR_2_PCFGR_2_RD_PORT_AGING_EN(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Sets the AXI urgent sideband signal (arurgent). When enabled and
 * arurgent is asserted by the master, that port becomes the highest
 * priority and co_gs_go2critical_lpr/co_gs_go2critical_hpr signal to DDRC
 * is asserted if enabled in PCCFG.go2critical_en register.
 * Note that arurgent signal can be asserted anytime and as long as
 * required which is independent of address handshaking (it is not
 * associated with any particular command).
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCFGR_2 . PCFGR_2_RD_PORT_URGENT_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCFGR_2_PCFGR_2_RD_PORT_URGENT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DDR_UMCTL2_PCFGR_2_PCFGR_2_RD_PORT_URGENT_EN  VTSS_BIT(13)
#define  VTSS_X_DDR_UMCTL2_PCFGR_2_PCFGR_2_RD_PORT_URGENT_EN(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Sets the Page Match feature. If enabled, once a requesting port is
 * granted, the port is continued to be granted if the following immediate
 * commands are to the same memory page (same rank, same bank and same
 * row).
 * See also related PCCFG.pagematch_limit register.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCFGR_2 . PCFGR_2_RD_PORT_PAGEMATCH_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCFGR_2_PCFGR_2_RD_PORT_PAGEMATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_DDR_UMCTL2_PCFGR_2_PCFGR_2_RD_PORT_PAGEMATCH_EN  VTSS_BIT(14)
#define  VTSS_X_DDR_UMCTL2_PCFGR_2_PCFGR_2_RD_PORT_PAGEMATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,14,1)


/**
 * \brief Port n Configuration Write Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGW_2
 */
#define VTSS_DDR_UMCTL2_PCFGW_2              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x15a)

/**
 * \brief
 * Determines the initial load value of write aging counters.
 * These counters are parallel loaded after reset, or after each grant to
 * the corresponding port.
 * The aging counters down-count every clock cycle where the port is
 * requesting but not granted.
 * The higher significant 5-bits of the write aging counter sets the
 * initial priority of the write channel of a given port.
 * Port's priority increases as the higher significant 5-bits of the
 * counter starts to decrease. When the aging counter becomes 0, the
 * corresponding port channel has the highest priority level.
 * For multi-port configurations, the aging counters cannot be used to set
 * port priorities when external dynamic priority  inputs (awqos) are
 * enabled (timeout is still applicable).
 * For single port configurations, the aging counters are only used when
 * they timeout (become 0) to force read-write direction switching.
 * Note: The two LSBs of this register field are tied internally to 2'b00.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGW_2 . PCFGW_2_WR_PORT_PRIORITY
 */
#define  VTSS_F_DDR_UMCTL2_PCFGW_2_PCFGW_2_WR_PORT_PRIORITY(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_DDR_UMCTL2_PCFGW_2_PCFGW_2_WR_PORT_PRIORITY     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_DDR_UMCTL2_PCFGW_2_PCFGW_2_WR_PORT_PRIORITY(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * \brief
 * Sets aging function for the write channel of the port.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCFGW_2 . PCFGW_2_WR_PORT_AGING_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCFGW_2_PCFGW_2_WR_PORT_AGING_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DDR_UMCTL2_PCFGW_2_PCFGW_2_WR_PORT_AGING_EN  VTSS_BIT(12)
#define  VTSS_X_DDR_UMCTL2_PCFGW_2_PCFGW_2_WR_PORT_AGING_EN(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Sets the AXI urgent sideband signal (awurgent).
 * When enabled and awurgent is asserted by the master, that port becomes
 * the highest priority and co_gs_go2critical_wr signal to DDRC is asserted
 * if enabled in PCCFG.go2critical_en register.
 * Note that awurgent signal can be asserted anytime and as long as
 * required which is independent of address handshaking (it is not
 * associated with any particular command).
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCFGW_2 . PCFGW_2_WR_PORT_URGENT_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCFGW_2_PCFGW_2_WR_PORT_URGENT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DDR_UMCTL2_PCFGW_2_PCFGW_2_WR_PORT_URGENT_EN  VTSS_BIT(13)
#define  VTSS_X_DDR_UMCTL2_PCFGW_2_PCFGW_2_WR_PORT_URGENT_EN(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Sets the Page Match feature.
 * If enabled, once a requesting port is granted, the port is continued to
 * be granted if the following immediate commands are to the same memory
 * page (same rank, same bank and same row).
 * See also related PCCFG.pagematch_limit register.
 * Programming Mode: Static
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCFGW_2 . PCFGW_2_WR_PORT_PAGEMATCH_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCFGW_2_PCFGW_2_WR_PORT_PAGEMATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_DDR_UMCTL2_PCFGW_2_PCFGW_2_WR_PORT_PAGEMATCH_EN  VTSS_BIT(14)
#define  VTSS_X_DDR_UMCTL2_PCFGW_2_PCFGW_2_WR_PORT_PAGEMATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,14,1)


/**
 * \brief Port n Control Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCTRL_2
 */
#define VTSS_DDR_UMCTL2_PCTRL_2              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x17c)

/**
 * \brief
 * Enables AXI port n.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_PCTRL_2 . PCTRL_2_PORT_EN
 */
#define  VTSS_F_DDR_UMCTL2_PCTRL_2_PCTRL_2_PORT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_PCTRL_2_PCTRL_2_PORT_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_PCTRL_2_PCTRL_2_PORT_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Port n Read QoS Configuration Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGQOS0_2
 */
#define VTSS_DDR_UMCTL2_PCFGQOS0_2           VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x17d)

/**
 * \brief
 * Separation level1 indicating the end of region0 mapping; start of
 * region0 is 0. Possible values for level1 are 0 to 13 (for dual RAQ) or 0
 * to 14 (for single RAQ) which corresponds to arqos.
 * Note that for PA, arqos values are used directly as port priorities,
 * where the higher the value corresponds to higher port priority.
 * All of the map_level* registers must be set to distinct values.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGQOS0_2 . PCFGQOS0_2_RQOS_MAP_LEVEL1
 */
#define  VTSS_F_DDR_UMCTL2_PCFGQOS0_2_PCFGQOS0_2_RQOS_MAP_LEVEL1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_PCFGQOS0_2_PCFGQOS0_2_RQOS_MAP_LEVEL1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_PCFGQOS0_2_PCFGQOS0_2_RQOS_MAP_LEVEL1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * This bit field indicates the traffic class of region 0.
 * Valid values are:
 *  - 0 - LPR
 *  - 1 - VPR
 *  - 2 - HPR
 * For dual address queue configurations, region 0 maps to the blue address
 * queue.
 * In this case, valid values are:
 * 0: LPR and 1: VPR only.
 * When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of
 * region0 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGQOS0_2 . PCFGQOS0_2_RQOS_MAP_REGION0
 */
#define  VTSS_F_DDR_UMCTL2_PCFGQOS0_2_PCFGQOS0_2_RQOS_MAP_REGION0(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_DDR_UMCTL2_PCFGQOS0_2_PCFGQOS0_2_RQOS_MAP_REGION0     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_DDR_UMCTL2_PCFGQOS0_2_PCFGQOS0_2_RQOS_MAP_REGION0(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * This bit field indicates the traffic class of region 1.
 * Valid values are:
 *  - 0 - LPR
 *  - 1 - VPR
 *  - 2 - HPR
 *  For dual address queue configurations, region1 maps to the blue address
 * queue.
 * In this case, valid values are
 *  - 0 - LPR
 *  - 1 - VPR only
 *  When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of
 * region 1 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGQOS0_2 . PCFGQOS0_2_RQOS_MAP_REGION1
 */
#define  VTSS_F_DDR_UMCTL2_PCFGQOS0_2_PCFGQOS0_2_RQOS_MAP_REGION1(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_DDR_UMCTL2_PCFGQOS0_2_PCFGQOS0_2_RQOS_MAP_REGION1     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_DDR_UMCTL2_PCFGQOS0_2_PCFGQOS0_2_RQOS_MAP_REGION1(x)  VTSS_EXTRACT_BITFIELD(x,20,2)


/**
 * \brief Port n Read QoS Configuration Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGQOS1_2
 */
#define VTSS_DDR_UMCTL2_PCFGQOS1_2           VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x17e)

/**
 * \brief
 * Specifies the timeout value for transactions mapped to the blue address
 * queue.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGQOS1_2 . PCFGQOS1_2_RQOS_MAP_TIMEOUTB
 */
#define  VTSS_F_DDR_UMCTL2_PCFGQOS1_2_PCFGQOS1_2_RQOS_MAP_TIMEOUTB(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_DDR_UMCTL2_PCFGQOS1_2_PCFGQOS1_2_RQOS_MAP_TIMEOUTB     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_DDR_UMCTL2_PCFGQOS1_2_PCFGQOS1_2_RQOS_MAP_TIMEOUTB(x)  VTSS_EXTRACT_BITFIELD(x,0,11)

/**
 * \brief
 * Specifies the timeout value for transactions mapped to the red address
 * queue.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGQOS1_2 . PCFGQOS1_2_RQOS_MAP_TIMEOUTR
 */
#define  VTSS_F_DDR_UMCTL2_PCFGQOS1_2_PCFGQOS1_2_RQOS_MAP_TIMEOUTR(x)  VTSS_ENCODE_BITFIELD(x,16,11)
#define  VTSS_M_DDR_UMCTL2_PCFGQOS1_2_PCFGQOS1_2_RQOS_MAP_TIMEOUTR     VTSS_ENCODE_BITMASK(16,11)
#define  VTSS_X_DDR_UMCTL2_PCFGQOS1_2_PCFGQOS1_2_RQOS_MAP_TIMEOUTR(x)  VTSS_EXTRACT_BITFIELD(x,16,11)


/**
 * \brief Port n Write QoS Configuration Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGWQOS0_2
 */
#define VTSS_DDR_UMCTL2_PCFGWQOS0_2          VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x17f)

/**
 * \brief
 * Separation level indicating the end of region0 mapping; start of region0
 * is 0.
 * Possible values for level1 are 0 to 13 which corresponds to awqos.
 * Note that for PA, awqos values are used directly as port priorities,
 * where the higher the value corresponds to higher port priority.
 * All of the map_level* registers must be set to distinct values.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS0_2 . PCFGWQOS0_2_WQOS_MAP_LEVEL1
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS0_2_PCFGWQOS0_2_WQOS_MAP_LEVEL1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS0_2_PCFGWQOS0_2_WQOS_MAP_LEVEL1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS0_2_PCFGWQOS0_2_WQOS_MAP_LEVEL1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Separation level2 indicating the end of region1 mapping; start of
 * region1 is (level1 + 1).
 * Possible values for level2 are (level1 + 1) to 14 which corresponds to
 * awqos.
 * Region2 starts from (level2 + 1) up to 15.
 * Note that for PA, awqos values are used directly as port priorities,
 * where the higher the value corresponds to higher port priority.
 * All of the map_level* registers must be set to distinct values.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS0_2 . PCFGWQOS0_2_WQOS_MAP_LEVEL2
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS0_2_PCFGWQOS0_2_WQOS_MAP_LEVEL2(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS0_2_PCFGWQOS0_2_WQOS_MAP_LEVEL2     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS0_2_PCFGWQOS0_2_WQOS_MAP_LEVEL2(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * This bit field indicates the traffic class of region 0.
 * Valid values are:
 *  - 0 - NPW
 *  - 1 - VPW
 * When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of
 * region 0 is set to 1 (VPW), VPW traffic is aliased to NPW traffic.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS0_2 . PCFGWQOS0_2_WQOS_MAP_REGION0
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS0_2_PCFGWQOS0_2_WQOS_MAP_REGION0(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS0_2_PCFGWQOS0_2_WQOS_MAP_REGION0     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS0_2_PCFGWQOS0_2_WQOS_MAP_REGION0(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * This bit field indicates the traffic class of region 1.
 * Valid values are:
 * 0: NPW, 1: VPW.
 * When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of
 * region 1 is set to 1 (VPW), VPW traffic is aliased to NPW traffic.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS0_2 . PCFGWQOS0_2_WQOS_MAP_REGION1
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS0_2_PCFGWQOS0_2_WQOS_MAP_REGION1(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS0_2_PCFGWQOS0_2_WQOS_MAP_REGION1     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS0_2_PCFGWQOS0_2_WQOS_MAP_REGION1(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * This bit field indicates the traffic class of region 2.
 * Valid values are:
 *  - 0 - NPW
 *  - 1 - VPW
 * When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of
 * region 2 is set to 1 (VPW), VPW traffic is aliased to NPW traffic.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS0_2 . PCFGWQOS0_2_WQOS_MAP_REGION2
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS0_2_PCFGWQOS0_2_WQOS_MAP_REGION2(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS0_2_PCFGWQOS0_2_WQOS_MAP_REGION2     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS0_2_PCFGWQOS0_2_WQOS_MAP_REGION2(x)  VTSS_EXTRACT_BITFIELD(x,24,2)


/**
 * \brief Port n Write QoS Configuration Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGWQOS1_2
 */
#define VTSS_DDR_UMCTL2_PCFGWQOS1_2          VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x180)

/**
 * \brief
 * Specifies the timeout value for write transactions in region 0 and 1.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS1_2 . PCFGWQOS1_2_WQOS_MAP_TIMEOUT1
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS1_2_PCFGWQOS1_2_WQOS_MAP_TIMEOUT1(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS1_2_PCFGWQOS1_2_WQOS_MAP_TIMEOUT1     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS1_2_PCFGWQOS1_2_WQOS_MAP_TIMEOUT1(x)  VTSS_EXTRACT_BITFIELD(x,0,11)

/**
 * \brief
 * Specifies the timeout value for write transactions in region 2.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_PCFGWQOS1_2 . PCFGWQOS1_2_WQOS_MAP_TIMEOUT2
 */
#define  VTSS_F_DDR_UMCTL2_PCFGWQOS1_2_PCFGWQOS1_2_WQOS_MAP_TIMEOUT2(x)  VTSS_ENCODE_BITFIELD(x,16,11)
#define  VTSS_M_DDR_UMCTL2_PCFGWQOS1_2_PCFGWQOS1_2_WQOS_MAP_TIMEOUT2     VTSS_ENCODE_BITMASK(16,11)
#define  VTSS_X_DDR_UMCTL2_PCFGWQOS1_2_PCFGWQOS1_2_WQOS_MAP_TIMEOUT2(x)  VTSS_EXTRACT_BITFIELD(x,16,11)


/**
 * \brief SAR Base Address Register n
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:SARBASE0
 */
#define VTSS_DDR_UMCTL2_SARBASE0             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3c1)

/**
 * \brief
 * Base address for address region n specified as
 * awaddr[UMCTL2_A_ADDRW-1:x] and araddr[UMCTL2_A_ADDRW-1:x],
 * where x is determined by the minimum block size parameter
 * UMCTL2_SARMINSIZE: (x=log2(block size)).
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_SARBASE0 . BASE_ADDR
 */
#define  VTSS_F_DDR_UMCTL2_SARBASE0_BASE_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_DDR_UMCTL2_SARBASE0_BASE_ADDR     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_DDR_UMCTL2_SARBASE0_BASE_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief SAR Size Register n
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:SARSIZE0
 */
#define VTSS_DDR_UMCTL2_SARSIZE0             VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3c2)

/**
 * \brief
 * Number of blocks for address region n.
 * This register determines the total size of the region in multiples of
 * minimum block size as specified by the hardware parameter
 * UMCTL2_SARMINSIZE. The register value is encoded as number of blocks =
 * nblocks + 1. For example, if register is programmed to 0, region can
 * have 1 block.
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_SARSIZE0 . NBLOCKS
 */
#define  VTSS_F_DDR_UMCTL2_SARSIZE0_NBLOCKS(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_UMCTL2_SARSIZE0_NBLOCKS     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_UMCTL2_SARSIZE0_NBLOCKS(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Scrubber Control Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:SBRCTL
 */
#define VTSS_DDR_UMCTL2_SBRCTL               VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3c9)

/**
 * \brief
 * Enables ECC scrubber.
 * (Enabled)Enables the scrubber to generate background read commands after
 * the memories are initialized.
 * (Disabled)Disables the scrubber, resets the address generator to 0 and
 * clears the scrubber status.
 * This bitfield must be accessed separately from the other bitfields in
 * this register.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_SBRCTL . SCRUB_EN
 */
#define  VTSS_F_DDR_UMCTL2_SBRCTL_SCRUB_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_SBRCTL_SCRUB_EN    VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_SBRCTL_SCRUB_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Continue scrubbing during low power.
 * If enabled, burst of scrubs is issued in hardware controlled low power
 * modes. There are two such modes: automatically initiated by idleness or
 * initiated by Hardware low power interface.
 * If disabled, the scrubber does not attempt to send commands while the
 * DDRC is in HW controlled low power modes. In this case, the scrubber
 * remembers the last address issued and automatically continues from there
 * when the DDRC exits the low power mode.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_SBRCTL . SCRUB_DURING_LOWPOWER
 */
#define  VTSS_F_DDR_UMCTL2_SBRCTL_SCRUB_DURING_LOWPOWER(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_SBRCTL_SCRUB_DURING_LOWPOWER  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_SBRCTL_SCRUB_DURING_LOWPOWER(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Sets scrub_mode.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_SBRCTL . SCRUB_MODE
 */
#define  VTSS_F_DDR_UMCTL2_SBRCTL_SCRUB_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_UMCTL2_SBRCTL_SCRUB_MODE  VTSS_BIT(2)
#define  VTSS_X_DDR_UMCTL2_SBRCTL_SCRUB_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Scrub burst count.
 * Determines the number of back-to-back scrub read commands that can be
 * issued together when the controller is in one of the HW controlled low
 * power modes with Sideband ECC, both normal operation mode and low-power
 * mode with Inline ECC.
 * During these modes, the period of the scrub burst becomes
 * "scrub_burst*scrub_interval" cycles.
 * During normal operation mode of the controller with Sideband ECC (not in
 * power-down or self-refresh), scrub_burst is ignored and only one scrub
 * command is generated.
 * Valid values are (Sideband ECC): 1: 1 read, 2: 4 reads, 3: 16 reads, 4:
 * 64 reads, 5: 256 reads, 6: 1024 reads. (Inline ECC): 1: 8 reads, 2: 16
 * reads, 3: 32 reads.
 * New programmed value takes effect only after scrubber is disabled by
 * programming scrub_en to 0.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_SBRCTL . SCRUB_BURST
 */
#define  VTSS_F_DDR_UMCTL2_SBRCTL_SCRUB_BURST(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_DDR_UMCTL2_SBRCTL_SCRUB_BURST     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_DDR_UMCTL2_SBRCTL_SCRUB_BURST(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \brief
 * Scrub interval.
 * (512 x scrub_interval) number of clock cycles between two scrub read
 * commands.
 * If set to 0, scrub commands are issued back-to-back.
 * This mode of operation (scrub_interval=0) can typically be used for
 * scrubbing the full range of memory at once before or after SW controlled
 * low power operations.
 * After completing the full range of scrub while scrub_interval=0,
 * scrub_done register is set and sbr_done_intr interrupt signal is
 * asserted.
 * This mode can not be used with Inline ECC: If MEMC_INLINE_ECC is 1 and
 * scrub_interval is programme to 0, then RMW logic inside scrubber is
 * disabled. New programmed value takes effect only after scrubber is
 * disabled by programming scrub_en to 0.
 * Unit: Multiples of 512 sbr_clk cycles.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_SBRCTL . SCRUB_INTERVAL
 */
#define  VTSS_F_DDR_UMCTL2_SBRCTL_SCRUB_INTERVAL(x)  VTSS_ENCODE_BITFIELD(x,8,13)
#define  VTSS_M_DDR_UMCTL2_SBRCTL_SCRUB_INTERVAL     VTSS_ENCODE_BITMASK(8,13)
#define  VTSS_X_DDR_UMCTL2_SBRCTL_SCRUB_INTERVAL(x)  VTSS_EXTRACT_BITFIELD(x,8,13)


/**
 * \brief Scrubber Status Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:SBRSTAT
 */
#define VTSS_DDR_UMCTL2_SBRSTAT              VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3ca)

/**
 * \brief
 * Scrubber busy.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_SBRSTAT . SCRUB_BUSY
 */
#define  VTSS_F_DDR_UMCTL2_SBRSTAT_SCRUB_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_SBRSTAT_SCRUB_BUSY  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_SBRSTAT_SCRUB_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Scrubber done.
 * The controller sets this bit to 1, after full range of addresses are
 * scrubbed once while scrub_interval is set to 0.
 * Cleared if scrub_en is set to 0 (scrubber disabled) or scrub_interval is
 * set to a non-zero value for normal scrub operation.
 * The interrupt signal, sbr_done_intr, is equivalent to this status
 * bitfield.
 * Programming Mode: Dynamic
 *
 * \details
 * 'h0:
 * 'h1:

 *
 * Field: ::VTSS_DDR_UMCTL2_SBRSTAT . SCRUB_DONE
 */
#define  VTSS_F_DDR_UMCTL2_SBRSTAT_SCRUB_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_SBRSTAT_SCRUB_DONE  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_SBRSTAT_SCRUB_DONE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/**
 * \brief Scrubber Write Data Pattern 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:SBRWDATA0
 */
#define VTSS_DDR_UMCTL2_SBRWDATA0            VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3cb)

/**
 * \brief
 * ECC Scrubber write data pattern for data bus[31:0]
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_SBRWDATA0 . SCRUB_PATTERN0
 */
#define  VTSS_F_DDR_UMCTL2_SBRWDATA0_SCRUB_PATTERN0(x)  (x)
#define  VTSS_M_DDR_UMCTL2_SBRWDATA0_SCRUB_PATTERN0     0xffffffff
#define  VTSS_X_DDR_UMCTL2_SBRWDATA0_SCRUB_PATTERN0(x)  (x)


/**
 * \brief Scrubber Start Address Mask Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:SBRSTART0
 */
#define VTSS_DDR_UMCTL2_SBRSTART0            VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3ce)

/**
 * \brief
 * sbr_address_start_mask_0 holds the bits [31:0] of the starting address
 * the ECC scrubber generates. The register must be programmed as explained
 * in Address Configuration in ECC Scrub and Scrubber. The scrubber address
 * registers are changed only when the scrubber is disabled
 * (SBRCTL.scrub_en = 0) and there are no scrubber commands in progress
 * (SBRSTAT.scrub_busy = 0). It is HIF address.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_SBRSTART0 . SBR_ADDRESS_START_MASK_0
 */
#define  VTSS_F_DDR_UMCTL2_SBRSTART0_SBR_ADDRESS_START_MASK_0(x)  (x)
#define  VTSS_M_DDR_UMCTL2_SBRSTART0_SBR_ADDRESS_START_MASK_0     0xffffffff
#define  VTSS_X_DDR_UMCTL2_SBRSTART0_SBR_ADDRESS_START_MASK_0(x)  (x)


/**
 * \brief Scrubber Start Address Mask Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:SBRSTART1
 */
#define VTSS_DDR_UMCTL2_SBRSTART1            VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3cf)

/**
 * \brief
 * sbr_address_start_mask_1 holds bits [MEMC_HIF_ADDR_WIDTH_MAX-1:32] of
 * the starting address the ECC scrubber generates. The register must be
 * programmed as explained in Address Configuration in ECC Scrub and
 * Scrubber. The scrubber address registers are changed only when the
 * scrubber is disabled (SBRCTL.scrub_en = 0) and there are no scrubber
 * commands in progress (SBRSTAT.scrub_busy = 0). It is HIF address.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_SBRSTART1 . SBR_ADDRESS_START_MASK_1
 */
#define  VTSS_F_DDR_UMCTL2_SBRSTART1_SBR_ADDRESS_START_MASK_1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_SBRSTART1_SBR_ADDRESS_START_MASK_1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_SBRSTART1_SBR_ADDRESS_START_MASK_1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Scrubber Address Range Mask Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:SBRRANGE0
 */
#define VTSS_DDR_UMCTL2_SBRRANGE0            VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3d0)

/**
 * \brief
 * sbr_address_range_mask_0 holds the bits [31:0] of the scrubber address
 * range mask. The scrubber address range mask limits the address range
 * that the ECC scrubber can generate. The register must be programmed as
 * explained in Address Configuration in ECC Scrub and Scrubber. The
 * scrubber address registers are changed only when the scrubber is
 * disabled (SBRCTL.scrub_en = 0) and there are no scrubber commands in
 * progress (SBRSTAT.scrub_busy = 0). It is HIF address.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_SBRRANGE0 . SBR_ADDRESS_RANGE_MASK_0
 */
#define  VTSS_F_DDR_UMCTL2_SBRRANGE0_SBR_ADDRESS_RANGE_MASK_0(x)  (x)
#define  VTSS_M_DDR_UMCTL2_SBRRANGE0_SBR_ADDRESS_RANGE_MASK_0     0xffffffff
#define  VTSS_X_DDR_UMCTL2_SBRRANGE0_SBR_ADDRESS_RANGE_MASK_0(x)  (x)


/**
 * \brief Scrubber Address Range Mask Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:SBRRANGE1
 */
#define VTSS_DDR_UMCTL2_SBRRANGE1            VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3d1)

/**
 * \brief
 * sbr_address_range_mask_1 holds the bits [MEMC_HIF_ADDR_WIDTH_MAX-1:32]
 * of the scrubber address range mask. The scrubber address range mask
 * limits the address range that the ECC scrubber can generate. The
 * register must be programmed as explained in Address Configuration in ECC
 * Scrub and Scrubber. The scrubber address registers are changed only when
 * the scrubber is disabled (SBRCTL.scrub_en = 0) and there are no scrubber
 * commands in progress (SBRSTAT.scrub_busy = 0). It is HIF address.
 * Programming Mode: Dynamic
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_SBRRANGE1 . SBR_ADDRESS_RANGE_MASK_1
 */
#define  VTSS_F_DDR_UMCTL2_SBRRANGE1_SBR_ADDRESS_RANGE_MASK_1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_SBRRANGE1_SBR_ADDRESS_RANGE_MASK_1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_SBRRANGE1_SBR_ADDRESS_RANGE_MASK_1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief UMCTL2 Version Number Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:UMCTL2_VER_NUMBER
 */
#define VTSS_DDR_UMCTL2_UMCTL2_VER_NUMBER    VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3fc)

/**
 * \brief
 * Indicates the Device Version Number value.  This is in ASCII format,
 * with each byte corresponding to a character of the version number
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_VER_NUMBER . VER_NUMBER
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_VER_NUMBER_VER_NUMBER(x)  (x)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_VER_NUMBER_VER_NUMBER     0xffffffff
#define  VTSS_X_DDR_UMCTL2_UMCTL2_VER_NUMBER_VER_NUMBER(x)  (x)


/**
 * \brief UMCTL2 Version Type Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:UMCTL2_VER_TYPE
 */
#define VTSS_DDR_UMCTL2_UMCTL2_VER_TYPE      VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3fd)

/**
 * \brief
 * Indicates the Device Version Type value.  This is in ASCII format, with
 * each byte corresponding to a character of the version type
 * Programming Mode: Static
 *
 * \details
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_VER_TYPE . VER_TYPE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_VER_TYPE_VER_TYPE(x)  (x)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_VER_TYPE_VER_TYPE     0xffffffff
#define  VTSS_X_DDR_UMCTL2_UMCTL2_VER_TYPE_VER_TYPE(x)  (x)


#endif /* _VTSS_LAGUNA_REGS_DDR_UMCTL2_H_ */
