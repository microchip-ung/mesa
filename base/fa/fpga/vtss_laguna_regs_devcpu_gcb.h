// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_DEVCPU_GCB_H_
#define _VTSS_LAGUNA_REGS_DEVCPU_GCB_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a DEVCPU_GCB
 *
 * General Configuration Block
 *
 ***********************************************************************/

/**
 * Register Group: \a DEVCPU_GCB:CHIP_REGS
 *
 * Not documented
 */


/**
 * \brief Reset control register
 *
 * \details
 * Register: \a DEVCPU_GCB:CHIP_REGS:SOFT_RST
 */
#define VTSS_DEVCPU_GCB_SOFT_RST             VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x0)

/**
 * \brief
 * Set this field to reset the switch core (everything except the SERDES IO
 * and PLL blocks.) This field is automatically cleared by the reset.Note:
 * It is possible for the VCore to protect itself from this soft-reset, for
 * more info see CPU::RESET_PROT_STAT.SYS_RST_PROT_VCORE.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_SOFT_RST . SOFT_SWC_RST
 */
#define  VTSS_F_DEVCPU_GCB_SOFT_RST_SOFT_SWC_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEVCPU_GCB_SOFT_RST_SOFT_SWC_RST  VTSS_BIT(1)
#define  VTSS_X_DEVCPU_GCB_SOFT_RST_SOFT_SWC_RST(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Set this field to reset the whole chip. This field is automatically
 * cleared by the reset.Note: It is possible for the VCore to protect
 * itself from this soft-reset, for more info see
 * CPU::RESET_PROT_STAT.SYS_RST_PROT_VCORE.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_SOFT_RST . SOFT_CHIP_RST
 */
#define  VTSS_F_DEVCPU_GCB_SOFT_RST_SOFT_CHIP_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEVCPU_GCB_SOFT_RST_SOFT_CHIP_RST  VTSS_BIT(0)
#define  VTSS_X_DEVCPU_GCB_SOFT_RST_SOFT_CHIP_RST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SGPIO to Signal Detect map
 *
 * \details
 * Register: \a DEVCPU_GCB:CHIP_REGS:HW_SGPIO_TO_SD_MAP_CFG
 *
 * @param ri Replicator: x_FFL_DEVCPU_FPORT_CNT (??), 0-29
 */
#define VTSS_DEVCPU_GCB_HW_SGPIO_TO_SD_MAP_CFG(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x1 + (ri))

/**
 * \brief
 * Select which SGPIO provides the Signal Detect for this port.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_HW_SGPIO_TO_SD_MAP_CFG . SGPIO_TO_SD_SEL
 */
#define  VTSS_F_DEVCPU_GCB_HW_SGPIO_TO_SD_MAP_CFG_SGPIO_TO_SD_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_DEVCPU_GCB_HW_SGPIO_TO_SD_MAP_CFG_SGPIO_TO_SD_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_DEVCPU_GCB_HW_SGPIO_TO_SD_MAP_CFG_SGPIO_TO_SD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief SGPIO to SerDes Signal Detect map
 *
 * \details
 * Register: \a DEVCPU_GCB:CHIP_REGS:HW_SGPIO_TO_SERDES_SD_MAP_CFG
 *
 * @param ri Replicator: x_FFL_DEVCPU_SERDES_CNT (??), 0-9
 */
#define VTSS_DEVCPU_GCB_HW_SGPIO_TO_SERDES_SD_MAP_CFG(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x1f + (ri))

/**
 * \brief
 * Select which SGPIO provides the Signal Detect for this SerDes.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_HW_SGPIO_TO_SERDES_SD_MAP_CFG . SGPIO_TO_SERDES_SD_SEL
 */
#define  VTSS_F_DEVCPU_GCB_HW_SGPIO_TO_SERDES_SD_MAP_CFG_SGPIO_TO_SERDES_SD_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_DEVCPU_GCB_HW_SGPIO_TO_SERDES_SD_MAP_CFG_SGPIO_TO_SERDES_SD_SEL     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_DEVCPU_GCB_HW_SGPIO_TO_SERDES_SD_MAP_CFG_SGPIO_TO_SERDES_SD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief Disable of features
 *
 * \details
 * Register: \a DEVCPU_GCB:CHIP_REGS:FEA_DIS
 */
#define VTSS_DEVCPU_GCB_FEA_DIS              VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x29)

/**
 * \brief
 * Efuse force values. These bits are or'ed together with the corresponding
 * efuse fields - setting bits here corresponds to burning efuses and can
 * be used for validation purposes.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_FEA_DIS . FEA_DIS
 */
#define  VTSS_F_DEVCPU_GCB_FEA_DIS_FEA_DIS(x)  (x)
#define  VTSS_M_DEVCPU_GCB_FEA_DIS_FEA_DIS     0xffffffff
#define  VTSS_X_DEVCPU_GCB_FEA_DIS_FEA_DIS(x)  (x)

/**
 * Register Group: \a DEVCPU_GCB:SI_REGS
 *
 * Serial interface registers
 */


/**
 * \brief Physical interface control
 *
 * \details
 * Register: \a DEVCPU_GCB:SI_REGS:IF_CTRL
 */
#define VTSS_DEVCPU_GCB_IF_CTRL              VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x2a)

/**
 * \brief
 * This register configures critical interface parameters, it is
 * constructed so that it can always be written correctly no matter the
 * current state of the interface. When initializing a physical interface,
 * then this is the first register that must be written, the state of the
 * interface at that point may be unknown and therefore the following
 * scheme is required to bring the interface to a known state:When writing
 * a 4-bit value to this field construct a 32-bit data-word as follows: a)
 * copy the 4-bit value into bits 3:0, 11:8, 19:16, and 27:24. b) reverse
 * the 4-bit value and copy into bits 7:4, 15:12, 23:20, and 31:28.
 * Example: To write the value 2 to this field; the 32-bit data-word to
 * write is "0x42424242".Bit 0 configures endianness, 0:Little-Endian,
 * 1:Big-Endian (default).Bit 1 configures bit-order, 0:MSB-first
 * (default), 1:LSB-first.Bit 2,3 are reserved and should be kept 0.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_IF_CTRL . IF_CTRL
 */
#define  VTSS_F_DEVCPU_GCB_IF_CTRL_IF_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DEVCPU_GCB_IF_CTRL_IF_CTRL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DEVCPU_GCB_IF_CTRL_IF_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Physical interface configuration and status
 *
 * \details
 * Register: \a DEVCPU_GCB:SI_REGS:IF_CFGSTAT
 */
#define VTSS_DEVCPU_GCB_IF_CFGSTAT           VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x2b)

/**
 * \brief
 * SI interface: This field is set if the SI interface has read data from
 * device before it was ready (this can happen if the SI frequency is too
 * high or when too few padding bytes has been specified).
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_IF_CFGSTAT . IF_STAT
 */
#define  VTSS_F_DEVCPU_GCB_IF_CFGSTAT_IF_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DEVCPU_GCB_IF_CFGSTAT_IF_STAT  VTSS_BIT(16)
#define  VTSS_X_DEVCPU_GCB_IF_CFGSTAT_IF_STAT(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * SI interface: This is the number of padding bytes to insert before
 * read-data is shifted out of the device.This is needed when using high
 * serial interface frequencies. Minimum value is 1.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_IF_CFGSTAT . IF_CFG
 */
#define  VTSS_F_DEVCPU_GCB_IF_CFGSTAT_IF_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DEVCPU_GCB_IF_CFGSTAT_IF_CFG     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DEVCPU_GCB_IF_CFGSTAT_IF_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a DEVCPU_GCB:MIIM
 *
 * Not documented
 */


/**
 * \brief MIIM Status
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_STATUS
 *
 * @param gi Replicator: x_FFL_DEVCPU_MIIM_CNT (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MII_STATUS(gi)       VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x2c,gi,9,0,0)

/**
 * \brief
 * Indicates the current state of the MIIM controller. When read operations
 * are done (no longer busy), then read data is available via the
 * DEVCPU_GCB::MII_DATA register.
 *
 * \details
 * 0: MIIM controller is in idle state
 * 1: MIIM controller is busy performing MIIM cmd (Either read or read
 * cmd).
 *
 * Field: ::VTSS_DEVCPU_GCB_MII_STATUS . MIIM_STAT_BUSY
 */
#define  VTSS_F_DEVCPU_GCB_MII_STATUS_MIIM_STAT_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEVCPU_GCB_MII_STATUS_MIIM_STAT_BUSY  VTSS_BIT(3)
#define  VTSS_X_DEVCPU_GCB_MII_STATUS_MIIM_STAT_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * The MIIM controller has a CMD fifo of depth one. When this field is 0,
 * then it is safe to write another MIIM command to the MIIM controller.
 *
 * \details
 * 0 : Read or write not pending
 * 1 : Read or write pending.
 *
 * Field: ::VTSS_DEVCPU_GCB_MII_STATUS . MIIM_STAT_OPR_PEND
 */
#define  VTSS_F_DEVCPU_GCB_MII_STATUS_MIIM_STAT_OPR_PEND(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEVCPU_GCB_MII_STATUS_MIIM_STAT_OPR_PEND  VTSS_BIT(2)
#define  VTSS_X_DEVCPU_GCB_MII_STATUS_MIIM_STAT_OPR_PEND(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Indicates whether a read operation via the MIIM interface is in progress
 * or not.
 *
 * \details
 * 0 : Read not in progress
 * 1 : Read in progress.
 *
 * Field: ::VTSS_DEVCPU_GCB_MII_STATUS . MIIM_STAT_PENDING_RD
 */
#define  VTSS_F_DEVCPU_GCB_MII_STATUS_MIIM_STAT_PENDING_RD(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEVCPU_GCB_MII_STATUS_MIIM_STAT_PENDING_RD  VTSS_BIT(1)
#define  VTSS_X_DEVCPU_GCB_MII_STATUS_MIIM_STAT_PENDING_RD(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Indicates whether a write operation via the MIIM interface is in
 * progress or not.
 *
 * \details
 * 0 : Write not in progress
 * 1 : Write in progress.
 *
 * Field: ::VTSS_DEVCPU_GCB_MII_STATUS . MIIM_STAT_PENDING_WR
 */
#define  VTSS_F_DEVCPU_GCB_MII_STATUS_MIIM_STAT_PENDING_WR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEVCPU_GCB_MII_STATUS_MIIM_STAT_PENDING_WR  VTSS_BIT(0)
#define  VTSS_X_DEVCPU_GCB_MII_STATUS_MIIM_STAT_PENDING_WR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Signals if all PHYs have been scanned ( with auto scan ) at least once.
 *
 * \details
 * 0 : Auto scan has not scanned all PHYs.
 * 1 : Auto scan has scanned all PHY at least once.
 *
 * Field: ::VTSS_DEVCPU_GCB_MII_STATUS . MIIM_SCAN_COMPLETE
 */
#define  VTSS_F_DEVCPU_GCB_MII_STATUS_MIIM_SCAN_COMPLETE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DEVCPU_GCB_MII_STATUS_MIIM_SCAN_COMPLETE  VTSS_BIT(4)
#define  VTSS_X_DEVCPU_GCB_MII_STATUS_MIIM_SCAN_COMPLETE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/**
 * \brief MIIM Configuration
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_CFG_7226
 *
 * @param gi Replicator: x_FFL_DEVCPU_MIIM_CNT (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MII_CFG_7226(gi)     VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x2c,gi,9,0,1)

/**
 * \brief
 * Use of XAUI/XGMII translator device.
 *
 * \details
 * 0 : Disable
 * 1 : Enable.
 *
 * Field: ::VTSS_DEVCPU_GCB_MII_CFG_7226 . MIIM_7226_CFG_FIELD
 */
#define  VTSS_F_DEVCPU_GCB_MII_CFG_7226_MIIM_7226_CFG_FIELD(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_DEVCPU_GCB_MII_CFG_7226_MIIM_7226_CFG_FIELD  VTSS_BIT(9)
#define  VTSS_X_DEVCPU_GCB_MII_CFG_7226_MIIM_7226_CFG_FIELD(x)  VTSS_EXTRACT_BITFIELD(x,9,1)


/**
 * \brief MIIM Command
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_CMD
 *
 * @param gi Replicator: x_FFL_DEVCPU_MIIM_CNT (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MII_CMD(gi)          VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x2c,gi,9,0,2)

/**
 * \brief
 * Must be set for starting a new PHY access. This bit is automatically
 * cleared.
 *
 * \details
 * 0 : Write to this register is ignored.
 * 1 : Write to this register is processed.
 *
 * Field: ::VTSS_DEVCPU_GCB_MII_CMD . MIIM_CMD_VLD
 */
#define  VTSS_F_DEVCPU_GCB_MII_CMD_MIIM_CMD_VLD(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DEVCPU_GCB_MII_CMD_MIIM_CMD_VLD  VTSS_BIT(31)
#define  VTSS_X_DEVCPU_GCB_MII_CMD_MIIM_CMD_VLD(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * Indicates the addressed PHY number.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_MII_CMD . MIIM_CMD_PHYAD
 */
#define  VTSS_F_DEVCPU_GCB_MII_CMD_MIIM_CMD_PHYAD(x)  VTSS_ENCODE_BITFIELD(x,25,5)
#define  VTSS_M_DEVCPU_GCB_MII_CMD_MIIM_CMD_PHYAD     VTSS_ENCODE_BITMASK(25,5)
#define  VTSS_X_DEVCPU_GCB_MII_CMD_MIIM_CMD_PHYAD(x)  VTSS_EXTRACT_BITFIELD(x,25,5)

/**
 * \brief
 * Indicates the addressed of the register within the PHY that shall be
 * accessed.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_MII_CMD . MIIM_CMD_REGAD
 */
#define  VTSS_F_DEVCPU_GCB_MII_CMD_MIIM_CMD_REGAD(x)  VTSS_ENCODE_BITFIELD(x,20,5)
#define  VTSS_M_DEVCPU_GCB_MII_CMD_MIIM_CMD_REGAD     VTSS_ENCODE_BITMASK(20,5)
#define  VTSS_X_DEVCPU_GCB_MII_CMD_MIIM_CMD_REGAD(x)  VTSS_EXTRACT_BITFIELD(x,20,5)

/**
 * \brief
 * Data to be written in the PHY register.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_MII_CMD . MIIM_CMD_WRDATA
 */
#define  VTSS_F_DEVCPU_GCB_MII_CMD_MIIM_CMD_WRDATA(x)  VTSS_ENCODE_BITFIELD(x,4,16)
#define  VTSS_M_DEVCPU_GCB_MII_CMD_MIIM_CMD_WRDATA     VTSS_ENCODE_BITMASK(4,16)
#define  VTSS_X_DEVCPU_GCB_MII_CMD_MIIM_CMD_WRDATA(x)  VTSS_EXTRACT_BITFIELD(x,4,16)

/**
 * \brief
 * Select if scanning of the PHY shall be done once, or scanning should be
 * done continuously.
 *
 * \details
 * 0 : Do continuously PHY scanning
 * 1 : Stop once all PHY have been scanned.
 *
 * Field: ::VTSS_DEVCPU_GCB_MII_CMD . MIIM_CMD_SINGLE_SCAN
 */
#define  VTSS_F_DEVCPU_GCB_MII_CMD_MIIM_CMD_SINGLE_SCAN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DEVCPU_GCB_MII_CMD_MIIM_CMD_SINGLE_SCAN  VTSS_BIT(3)
#define  VTSS_X_DEVCPU_GCB_MII_CMD_MIIM_CMD_SINGLE_SCAN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Indicates type of operation.
 *
 * \details
 * Clause 22:
 *
 * 01 : Write
 * 10 : Read
 *
 * Clause 45:
 *
 * 00 : Address
 * 01 : Write
 * 10 : Read inc.
 * 11 : Read.
 *
 * Field: ::VTSS_DEVCPU_GCB_MII_CMD . MIIM_CMD_OPR_FIELD
 */
#define  VTSS_F_DEVCPU_GCB_MII_CMD_MIIM_CMD_OPR_FIELD(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_DEVCPU_GCB_MII_CMD_MIIM_CMD_OPR_FIELD     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_DEVCPU_GCB_MII_CMD_MIIM_CMD_OPR_FIELD(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * Indicates whether automatic scanning of PHY registers is enabled. When
 * enabled, the PHY-number for each automatic read is continuously
 * round-robined from PHY_ADDR_LOW through PHY_ADDR_HIGH. This function is
 * started upon a read operation (ACCESS_TYPE).Scan MUST be disabled when
 * doing any configuration of the MIIM controller.
 *
 * \details
 * 0 : Disabled
 * 1 : Enabled.
 *
 * Field: ::VTSS_DEVCPU_GCB_MII_CMD . MIIM_CMD_SCAN
 */
#define  VTSS_F_DEVCPU_GCB_MII_CMD_MIIM_CMD_SCAN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEVCPU_GCB_MII_CMD_MIIM_CMD_SCAN  VTSS_BIT(0)
#define  VTSS_X_DEVCPU_GCB_MII_CMD_MIIM_CMD_SCAN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief MIIM Reply Data
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_DATA
 *
 * @param gi Replicator: x_FFL_DEVCPU_MIIM_CNT (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MII_DATA(gi)         VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x2c,gi,9,0,3)

/**
 * \brief
 * Indicates whether a read operation failed or succeeded.
 *
 * \details
 * 00 : OK
 * 11 : Error
 *
 * Field: ::VTSS_DEVCPU_GCB_MII_DATA . MIIM_DATA_SUCCESS
 */
#define  VTSS_F_DEVCPU_GCB_MII_DATA_MIIM_DATA_SUCCESS(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_DEVCPU_GCB_MII_DATA_MIIM_DATA_SUCCESS     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_DEVCPU_GCB_MII_DATA_MIIM_DATA_SUCCESS(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * Data read from PHY register.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_MII_DATA . MIIM_DATA_RDDATA
 */
#define  VTSS_F_DEVCPU_GCB_MII_DATA_MIIM_DATA_RDDATA(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DEVCPU_GCB_MII_DATA_MIIM_DATA_RDDATA     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DEVCPU_GCB_MII_DATA_MIIM_DATA_RDDATA(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief MIIM Configuration
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_CFG
 *
 * @param gi Replicator: x_FFL_DEVCPU_MIIM_CNT (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MII_CFG(gi)          VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x2c,gi,9,0,4)

/**
 * \brief
 * Option to disable deadlock fix if it causes any troubles.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_MII_CFG . DEADLOCK_FIX_DIS
 */
#define  VTSS_F_DEVCPU_GCB_MII_CFG_DEADLOCK_FIX_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_DEVCPU_GCB_MII_CFG_DEADLOCK_FIX_DIS  VTSS_BIT(11)
#define  VTSS_X_DEVCPU_GCB_MII_CFG_DEADLOCK_FIX_DIS(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Configures the MIIM clock frequency. This is computed as
 * system_clk/(2*(1+X)), where X is the value written to this register.Note
 * : Setting X to 0 is invalid and will result in the same frequency as
 * setting X to 1.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_MII_CFG . MIIM_CFG_PRESCALE
 */
#define  VTSS_F_DEVCPU_GCB_MII_CFG_MIIM_CFG_PRESCALE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEVCPU_GCB_MII_CFG_MIIM_CFG_PRESCALE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEVCPU_GCB_MII_CFG_MIIM_CFG_PRESCALE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * The ST (start-of-frame) field of the MIIM frame format adopts the value
 * of this field. This must be configured for either clause 22 or 45 MIIM
 * operation.
 *
 * \details
 * "01": Clause 22
 * "00": Clause 45
 * Other values are reserved.
 *
 * Field: ::VTSS_DEVCPU_GCB_MII_CFG . MIIM_ST_CFG_FIELD
 */
#define  VTSS_F_DEVCPU_GCB_MII_CFG_MIIM_ST_CFG_FIELD(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_DEVCPU_GCB_MII_CFG_MIIM_ST_CFG_FIELD     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_DEVCPU_GCB_MII_CFG_MIIM_ST_CFG_FIELD(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * Selects the interpretation of the BUSY_OR_IN_PROGRESS field in
 * MII_STATUS.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_MII_CFG . MIIM_CFG_DBG
 */
#define  VTSS_F_DEVCPU_GCB_MII_CFG_MIIM_CFG_DBG(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DEVCPU_GCB_MII_CFG_MIIM_CFG_DBG  VTSS_BIT(8)
#define  VTSS_X_DEVCPU_GCB_MII_CFG_MIIM_CFG_DBG(x)  VTSS_EXTRACT_BITFIELD(x,8,1)


/**
 * \brief MIIM Scan 0
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_SCAN_0
 *
 * @param gi Replicator: x_FFL_DEVCPU_MIIM_CNT (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MII_SCAN_0(gi)       VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x2c,gi,9,0,5)

/**
 * \brief
 * Indicates the high PHY number to scan during automatic scanning.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_MII_SCAN_0 . MIIM_SCAN_PHYADHI
 */
#define  VTSS_F_DEVCPU_GCB_MII_SCAN_0_MIIM_SCAN_PHYADHI(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_DEVCPU_GCB_MII_SCAN_0_MIIM_SCAN_PHYADHI     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_DEVCPU_GCB_MII_SCAN_0_MIIM_SCAN_PHYADHI(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/**
 * \brief
 * Indicates the low PHY number to scan during automatic scanning.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_MII_SCAN_0 . MIIM_SCAN_PHYADLO
 */
#define  VTSS_F_DEVCPU_GCB_MII_SCAN_0_MIIM_SCAN_PHYADLO(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DEVCPU_GCB_MII_SCAN_0_MIIM_SCAN_PHYADLO     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DEVCPU_GCB_MII_SCAN_0_MIIM_SCAN_PHYADLO(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief MIIM Scan 1
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_SCAN_1
 *
 * @param gi Replicator: x_FFL_DEVCPU_MIIM_CNT (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MII_SCAN_1(gi)       VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x2c,gi,9,0,6)

/**
 * \brief
 * Indicates the mask for comparing the PHY registers during automatic
 * scan.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_MII_SCAN_1 . MIIM_SCAN_MASK
 */
#define  VTSS_F_DEVCPU_GCB_MII_SCAN_1_MIIM_SCAN_MASK(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DEVCPU_GCB_MII_SCAN_1_MIIM_SCAN_MASK     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DEVCPU_GCB_MII_SCAN_1_MIIM_SCAN_MASK(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * Indicates the expected value for comparing the PHY registers during
 * automatic scan.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_MII_SCAN_1 . MIIM_SCAN_EXPECT
 */
#define  VTSS_F_DEVCPU_GCB_MII_SCAN_1_MIIM_SCAN_EXPECT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DEVCPU_GCB_MII_SCAN_1_MIIM_SCAN_EXPECT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DEVCPU_GCB_MII_SCAN_1_MIIM_SCAN_EXPECT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief MIIM Results
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_SCAN_LAST_RSLTS
 *
 * @param gi Replicator: x_FFL_DEVCPU_MIIM_CNT (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MII_SCAN_LAST_RSLTS(gi)  VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x2c,gi,9,0,7)

/**
 * \brief
 * Indicates for each PHY if a PHY register has matched the expected value
 * (with mask).This register reflects the value of the last reading of the
 * phy register.
 *
 * \details
 * 0 : Mismatch.
 * 1 : Match.
 *
 * Field: ::VTSS_DEVCPU_GCB_MII_SCAN_LAST_RSLTS . MIIM_LAST_RSLT
 */
#define  VTSS_F_DEVCPU_GCB_MII_SCAN_LAST_RSLTS_MIIM_LAST_RSLT(x)  (x)
#define  VTSS_M_DEVCPU_GCB_MII_SCAN_LAST_RSLTS_MIIM_LAST_RSLT     0xffffffff
#define  VTSS_X_DEVCPU_GCB_MII_SCAN_LAST_RSLTS_MIIM_LAST_RSLT(x)  (x)


/**
 * \brief MIIM Results
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_SCAN_LAST_RSLTS_VLD
 *
 * @param gi Replicator: x_FFL_DEVCPU_MIIM_CNT (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MII_SCAN_LAST_RSLTS_VLD(gi)  VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x2c,gi,9,0,8)

/**
 * \brief
 * Indicates for each PHY if a PHY register matched are valid or not.
 *
 * \details
 * 0 : Scan result not valid.
 * 1 : Scan result valid.
 *
 * Field: ::VTSS_DEVCPU_GCB_MII_SCAN_LAST_RSLTS_VLD . MIIM_LAST_RSLT_VLD
 */
#define  VTSS_F_DEVCPU_GCB_MII_SCAN_LAST_RSLTS_VLD_MIIM_LAST_RSLT_VLD(x)  (x)
#define  VTSS_M_DEVCPU_GCB_MII_SCAN_LAST_RSLTS_VLD_MIIM_LAST_RSLT_VLD     0xffffffff
#define  VTSS_X_DEVCPU_GCB_MII_SCAN_LAST_RSLTS_VLD_MIIM_LAST_RSLT_VLD(x)  (x)

/**
 * Register Group: \a DEVCPU_GCB:MIIM_READ_SCAN
 *
 * Not documented
 */


/**
 * \brief MIIM Results
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM_READ_SCAN:MII_SCAN_RSLTS_STICKY
 *
 * @param ri Replicator: x_FFL_DEVCPU_MIIM_CNT (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MII_SCAN_RSLTS_STICKY(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x3e + (ri))

/**
 * \brief
 * Indicates for each PHY if a PHY register has had a mismatch of the
 * expected value (with mask) since last reading of
 * MIIM_SCAN_RSLTS_STICKY.Result is sticky, and result will indicate if
 * there has been a mismatch since the last reading of this register.Upon
 * reading this register, all bits are reset to '1'.
 *
 * \details
 * 0 : Mismatch
 * 1 : Match.
 *
 * Field: ::VTSS_DEVCPU_GCB_MII_SCAN_RSLTS_STICKY . MIIM_SCAN_RSLTS_STICKY
 */
#define  VTSS_F_DEVCPU_GCB_MII_SCAN_RSLTS_STICKY_MIIM_SCAN_RSLTS_STICKY(x)  (x)
#define  VTSS_M_DEVCPU_GCB_MII_SCAN_RSLTS_STICKY_MIIM_SCAN_RSLTS_STICKY     0xffffffff
#define  VTSS_X_DEVCPU_GCB_MII_SCAN_RSLTS_STICKY_MIIM_SCAN_RSLTS_STICKY(x)  (x)

/**
 * Register Group: \a DEVCPU_GCB:SIO_CTRL
 *
 * Serial IO control configuration
 */


/**
 * \brief Last value at SGPIO pins
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_INPUT_DATA
 *
 * @param ri Replicator: x_FFL_DEVCPU_SIO_IOS_PR_PORT (??), 0-3
 */
#define VTSS_DEVCPU_GCB_SIO_INPUT_DATA(ri)   VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x40 + (ri))

/**
 * \brief
 * Serial input data. Each replication, N, holds bit N from all ports - bit
 * N from port M is mapped to replication N bit M. Values of disabled gpios
 * are undefined.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_SIO_INPUT_DATA . SIO_INPUT_DATA
 */
#define  VTSS_F_DEVCPU_GCB_SIO_INPUT_DATA_SIO_INPUT_DATA(x)  (x)
#define  VTSS_M_DEVCPU_GCB_SIO_INPUT_DATA_SIO_INPUT_DATA     0xffffffff
#define  VTSS_X_DEVCPU_GCB_SIO_INPUT_DATA_SIO_INPUT_DATA(x)  (x)


/**
 * \brief General configurations
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_CFG
 */
#define VTSS_DEVCPU_GCB_SIO_CFG              VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x44)

/**
 * \brief
 * Configure the size of the PWM window.
 *
 * \details
 * 0 : 255 cycles
 * 1-254 : 2-255 cycles
 * 255 : Reserved.
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CFG . SIO_PWM_WINDOW
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CFG_SIO_PWM_WINDOW(x)  VTSS_ENCODE_BITFIELD(x,20,8)
#define  VTSS_M_DEVCPU_GCB_SIO_CFG_SIO_PWM_WINDOW     VTSS_ENCODE_BITMASK(20,8)
#define  VTSS_X_DEVCPU_GCB_SIO_CFG_SIO_PWM_WINDOW(x)  VTSS_EXTRACT_BITFIELD(x,20,8)

/**
 * \brief
 * When set, the SIO_BURST_GAP is divided by 32.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_SIO_CFG . SIO_REDUCED_GAP
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CFG_SIO_REDUCED_GAP(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_DEVCPU_GCB_SIO_CFG_SIO_REDUCED_GAP  VTSS_BIT(19)
#define  VTSS_X_DEVCPU_GCB_SIO_CFG_SIO_REDUCED_GAP(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Configuration for blink mode 1.Supports three different blink modes and
 * a "burst toggle" mode in which blink mode 1 will alternate for each
 * burst.
 *
 * \details
 * 0: Blink freq appr. 20Hz
 * 1: Blink freq appr. 10Hz
 * 2: Blink freq appr. 5Hz
 * 3: Burst toggle
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CFG . SIO_BMODE_1
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CFG_SIO_BMODE_1(x)  VTSS_ENCODE_BITFIELD(x,17,2)
#define  VTSS_M_DEVCPU_GCB_SIO_CFG_SIO_BMODE_1     VTSS_ENCODE_BITMASK(17,2)
#define  VTSS_X_DEVCPU_GCB_SIO_CFG_SIO_BMODE_1(x)  VTSS_EXTRACT_BITFIELD(x,17,2)

/**
 * \brief
 * Configuration of blink mode 0. Supports four different blink modes.
 *
 * \details
 * 0 : Blink freq appr. 5Hz.
 * 1 : Blink freq appr. 2.5Hz.
 * 2 : Blink freq appr. 1.25Hz.
 * 3 : Blink freq appr. 0.625Hz.
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CFG . SIO_BMODE_0
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CFG_SIO_BMODE_0(x)  VTSS_ENCODE_BITFIELD(x,15,2)
#define  VTSS_M_DEVCPU_GCB_SIO_CFG_SIO_BMODE_0     VTSS_ENCODE_BITMASK(15,2)
#define  VTSS_X_DEVCPU_GCB_SIO_CFG_SIO_BMODE_0(x)  VTSS_EXTRACT_BITFIELD(x,15,2)

/**
 * \brief
 * Reset the blink counters. Used to synchronize the blink modes between
 * different chips.
 *
 * \details
 * 0: Blink counter is running
 * 1: Blink counter is reset until sio_blink_reset is unset again
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CFG . SIO_BLINK_RESET
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CFG_SIO_BLINK_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_DEVCPU_GCB_SIO_CFG_SIO_BLINK_RESET  VTSS_BIT(14)
#define  VTSS_X_DEVCPU_GCB_SIO_CFG_SIO_BLINK_RESET(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Set to disable burst gap.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_SIO_CFG . SIO_BURST_GAP_DIS
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CFG_SIO_BURST_GAP_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DEVCPU_GCB_SIO_CFG_SIO_BURST_GAP_DIS  VTSS_BIT(13)
#define  VTSS_X_DEVCPU_GCB_SIO_CFG_SIO_BURST_GAP_DIS(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Configures the length of burst gap in steps. Burst gap can be disabled
 * by setting DEVCPU_GCB::SIO_CFG.SIO_BURST_GAP_DIS. For smaller burst gap
 * set DEVCPU_GCB::SIO_CFG.SIO_REDUCED_GAP. The gap is calculated by
 * (Value+1) * (2^18) * (system clock period).
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_SIO_CFG . SIO_BURST_GAP
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CFG_SIO_BURST_GAP(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_DEVCPU_GCB_SIO_CFG_SIO_BURST_GAP     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_DEVCPU_GCB_SIO_CFG_SIO_BURST_GAP(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/**
 * \brief
 * Use this to output a single burst. Will be cleared by hardware when the
 * burst has finished.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_SIO_CFG . SIO_SINGLE_SHOT
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CFG_SIO_SINGLE_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DEVCPU_GCB_SIO_CFG_SIO_SINGLE_SHOT  VTSS_BIT(7)
#define  VTSS_X_DEVCPU_GCB_SIO_CFG_SIO_SINGLE_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Use this to output repeated bursts interleaved with burst gaps. Must be
 * manually reset again to stop output of bursts.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_SIO_CFG . SIO_AUTO_REPEAT
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CFG_SIO_AUTO_REPEAT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DEVCPU_GCB_SIO_CFG_SIO_AUTO_REPEAT  VTSS_BIT(6)
#define  VTSS_X_DEVCPU_GCB_SIO_CFG_SIO_AUTO_REPEAT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Polarity of the "Ld" signal
 *
 * \details
 * 0: load signal is active low
 * 1: load signal is active high
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CFG . SIO_LD_POLARITY
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CFG_SIO_LD_POLARITY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DEVCPU_GCB_SIO_CFG_SIO_LD_POLARITY  VTSS_BIT(5)
#define  VTSS_X_DEVCPU_GCB_SIO_CFG_SIO_LD_POLARITY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Number of SGPIOs pr. port.
 *
 * \details
 * 0: 1 gpio pr. port
 * 1: 2 gpios pr. port
 * 2: 3 gpios pr. port
 * 3: 4 gpios pr. port
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CFG . SIO_PORT_WIDTH
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CFG_SIO_PORT_WIDTH(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_DEVCPU_GCB_SIO_CFG_SIO_PORT_WIDTH     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_DEVCPU_GCB_SIO_CFG_SIO_PORT_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * Reverse the output bitstream.The default order of the output bit stream
 * is (displayed in transmitted order):(portN bit3, portN bit2, ...., port0
 * bit1, port0 bit0)The reverse order of the output bit stream is
 * (displayed in transmitted order):(port0 bit0, port0 bit1, ...., portN
 * bit2, portN bit3)
 *
 * \details
 * 0: Do not reverse
 * 1: Reverse
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CFG . SIO_REVERSE_OUTPUT
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CFG_SIO_REVERSE_OUTPUT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEVCPU_GCB_SIO_CFG_SIO_REVERSE_OUTPUT  VTSS_BIT(2)
#define  VTSS_X_DEVCPU_GCB_SIO_CFG_SIO_REVERSE_OUTPUT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Reverse the input bitstream.The default order of the input bit stream is
 * (displayed in received order):(port0 bit0, port0 bit1, ...., portN bit2,
 * portN bit3)The reverse order of the input bit stream is (displayed in
 * received order):(portN bit3, portN bit2, ...., port0 bit1, port0 bit0)
 *
 * \details
 * 0: Do not reverse
 * 1: Reverse
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CFG . SIO_REVERSE_INPUT
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CFG_SIO_REVERSE_INPUT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEVCPU_GCB_SIO_CFG_SIO_REVERSE_INPUT  VTSS_BIT(1)
#define  VTSS_X_DEVCPU_GCB_SIO_CFG_SIO_REVERSE_INPUT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Global interrupt enable. Enables interrupts. Is applied to all sgpios on
 * all ports. This field only has effect on the interrupt output signal of
 * the sio_ctrl block. It has no effect on the interrupt registers.
 *
 * \details
 * 0: Interrupt is disabled for all bits for all ports
 * 1: Interrupt is enabled for all bits for all ports
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CFG . SIO_GLOB_INTR_ENA
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CFG_SIO_GLOB_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEVCPU_GCB_SIO_CFG_SIO_GLOB_INTR_ENA  VTSS_BIT(0)
#define  VTSS_X_DEVCPU_GCB_SIO_CFG_SIO_GLOB_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SGPIO shift clock frequency
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_CLOCK
 */
#define VTSS_DEVCPU_GCB_SIO_CLOCK            VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x45)

/**
 * \brief
 * SIO controller clock frequency. Divides the system clk with the value of
 * this field.
 *
 * \details
 * 0: Disable clock
 * 1: Reserved, do not use
 * Others : Clock divider value.
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CLOCK . SIO_CLK_FREQ
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CLOCK_SIO_CLK_FREQ(x)  VTSS_ENCODE_BITFIELD(x,8,12)
#define  VTSS_M_DEVCPU_GCB_SIO_CLOCK_SIO_CLK_FREQ     VTSS_ENCODE_BITMASK(8,12)
#define  VTSS_X_DEVCPU_GCB_SIO_CLOCK_SIO_CLK_FREQ(x)  VTSS_EXTRACT_BITFIELD(x,8,12)

/**
 * \brief
 * The system clock period given in the clock period in PS divided by 100.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_SIO_CLOCK . SYS_CLK_PERIOD
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CLOCK_SYS_CLK_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEVCPU_GCB_SIO_CLOCK_SYS_CLK_PERIOD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEVCPU_GCB_SIO_CLOCK_SYS_CLK_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Output configuration
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_PORT_CFG
 *
 * @param ri Replicator: x_FFL_DEVCPU_SIO_PORT_CNT (??), 0-31
 */
#define VTSS_DEVCPU_GCB_SIO_PORT_CFG(ri)     VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x46 + (ri))

/**
 * \brief
 * Output source select for the four outputs from each port.The source
 * select is encoded using three bits for each output bit: Output bit0 is
 * defined by (2 down to 0), output bit1 is defined by (5 down to 3),
 * output bit2 is defined by (8 down to 6), and output bit3 is defined by
 * (11 down to 9).
 *
 * \details
 * 0: Forced 0
 * 1: Forced 1
 * 2: Blink mode 0
 * 3: Blink mode 1
 * 4: Link activity blink mode 0
 * 5: Link activity blink mode 1
 * 6: Reserved
 * 7: Reserved
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_PORT_CFG . BIT_SOURCE
 */
#define  VTSS_F_DEVCPU_GCB_SIO_PORT_CFG_BIT_SOURCE(x)  VTSS_ENCODE_BITFIELD(x,12,12)
#define  VTSS_M_DEVCPU_GCB_SIO_PORT_CFG_BIT_SOURCE     VTSS_ENCODE_BITMASK(12,12)
#define  VTSS_X_DEVCPU_GCB_SIO_PORT_CFG_BIT_SOURCE(x)  VTSS_EXTRACT_BITFIELD(x,12,12)

/**
 * \brief
 * PWM source select for the four outputs from each port.The PWM source
 * select is encoded using two bits for each output bit: Output bit0 is
 * defined by (1 down to 0), output bit1 is defined by (3 down to 2),
 * output bit2 is defined by (5 down to 4), and output bit3 is defined by
 * (7 down to 6).
 *
 * \details
 * 0: PWM disabled
 * 1: PWM 0 used
 * 2: PWM 1 used
 * 3: PWM 2 used
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_PORT_CFG . PWM_SOURCE
 */
#define  VTSS_F_DEVCPU_GCB_SIO_PORT_CFG_PWM_SOURCE(x)  VTSS_ENCODE_BITFIELD(x,4,8)
#define  VTSS_M_DEVCPU_GCB_SIO_PORT_CFG_PWM_SOURCE     VTSS_ENCODE_BITMASK(4,8)
#define  VTSS_X_DEVCPU_GCB_SIO_PORT_CFG_PWM_SOURCE(x)  VTSS_EXTRACT_BITFIELD(x,4,8)

/**
 * \brief
 * Output polarity select for the four outputs from each port.The polarity
 * select is encoded using one bit for each output bit.
 *
 * \details
 * 0: Normal polarity
 * 1: Inversed polarity
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_PORT_CFG . BIT_POLARITY
 */
#define  VTSS_F_DEVCPU_GCB_SIO_PORT_CFG_BIT_POLARITY(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DEVCPU_GCB_SIO_PORT_CFG_BIT_POLARITY     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DEVCPU_GCB_SIO_PORT_CFG_BIT_POLARITY(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Port enable
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_PORT_ENA
 */
#define VTSS_DEVCPU_GCB_SIO_PORT_ENA         VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x66)

/**
 * \brief
 * Port enable vector with one enable bit for each port.Port order: (portN
 * down to port0)
 *
 * \details
 * 0: Port is disabled
 * 1: Port is enabled
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_PORT_ENA . SIO_PORT_ENA
 */
#define  VTSS_F_DEVCPU_GCB_SIO_PORT_ENA_SIO_PORT_ENA(x)  (x)
#define  VTSS_M_DEVCPU_GCB_SIO_PORT_ENA_SIO_PORT_ENA     0xffffffff
#define  VTSS_X_DEVCPU_GCB_SIO_PORT_ENA_SIO_PORT_ENA(x)  (x)


/**
 * \brief Pulse-width modulation configuration
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_PWM_CFG
 *
 * @param ri Register: SIO_PWM_CFG (??), 0-2
 */
#define VTSS_DEVCPU_GCB_SIO_PWM_CFG(ri)      VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x67 + (ri))

/**
 * \brief
 * Define the duty cycle for the PWMs.
 *
 * \details
 * 0x00: Always "off"
 * 0xFF: Always "on"
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_PWM_CFG . PWM_DUTY_CYCLE
 */
#define  VTSS_F_DEVCPU_GCB_SIO_PWM_CFG_PWM_DUTY_CYCLE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEVCPU_GCB_SIO_PWM_CFG_PWM_DUTY_CYCLE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEVCPU_GCB_SIO_PWM_CFG_PWM_DUTY_CYCLE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief SGPIO interrupt polarity
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_INTR_POL
 *
 * @param ri Replicator: x_FFL_DEVCPU_SIO_IOS_PR_PORT (??), 0-3
 */
#define VTSS_DEVCPU_GCB_SIO_INTR_POL(ri)     VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x6a + (ri))

/**
 * \brief
 * Interrupt polarity. This register defines at which logic value an
 * interrupt is generated. For bit0 this register is also used to define
 * the polarity of the "loss of signal" output.
 *
 * \details
 * 0: interrupt and "loss of signal" is active high
 * 1: interrupt and "loss of signal" is active low
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_INTR_POL . SIO_INTR_POL
 */
#define  VTSS_F_DEVCPU_GCB_SIO_INTR_POL_SIO_INTR_POL(x)  (x)
#define  VTSS_M_DEVCPU_GCB_SIO_INTR_POL_SIO_INTR_POL     0xffffffff
#define  VTSS_X_DEVCPU_GCB_SIO_INTR_POL_SIO_INTR_POL(x)  (x)


/**
 * \brief Interrupt raw status
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_INTR_RAW
 *
 * @param ri Replicator: x_FFL_DEVCPU_SIO_IOS_PR_PORT (??), 0-3
 */
#define VTSS_DEVCPU_GCB_SIO_INTR_RAW(ri)     VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x6e + (ri))

/**
 * \brief
 * Shows the current value of individual interrupts. All interrupts are
 * active high (but has been corrected for polarity as configured in
 * SIO_INTR_POL).
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_SIO_INTR_RAW . SIO_INTR_RAW
 */
#define  VTSS_F_DEVCPU_GCB_SIO_INTR_RAW_SIO_INTR_RAW(x)  (x)
#define  VTSS_M_DEVCPU_GCB_SIO_INTR_RAW_SIO_INTR_RAW     0xffffffff
#define  VTSS_X_DEVCPU_GCB_SIO_INTR_RAW_SIO_INTR_RAW(x)  (x)


/**
 * \brief Interrupt trigger mode 0
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_INTR_TRIGGER0
 *
 * @param ri Replicator: x_FFL_DEVCPU_SIO_IOS_PR_PORT (??), 0-3
 */
#define VTSS_DEVCPU_GCB_SIO_INTR_TRIGGER0(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x72 + (ri))

/**
 * \brief
 * Configure trigger mode of individual interrupts. The trigger mode
 * determines how the value of the SIO_INTR_RAW register is transferred to
 * the SIO_INTR register.This register is the LSB of the encoding. Register
 * SIO_INTR_TRIGGER1 is the MSB of the encoding.For level-triggered
 * interrupts SIO_INTR is set when an input is received that results in a
 * high corresponding bit in SIO_INTR_RAW.For edge-triggered interrupts
 * SIO_INTR is set when an input is received that results in a change of
 * the corresponding bit in SIO_INTR_RAW.For falling-edge-triggered
 * interrupts SIO_INTR is set when an input is received that results in a
 * change from '1' to '0' of the corresponding bit in SIO_INTR_RAW.For
 * rising-edge-triggered interrupts SIO_INTR is set when an input is
 * received that results in a change from '0' to '1' of the corresponding
 * bit in SIO_INTR_RAW.
 *
 * \details
 * 00: Interrupt is level-activated
 * 01: Interrupt is edge-triggered
 * 10: Interrupt is falling-edge-triggered
 * 11: Interrupt is rising-edge-triggered
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_INTR_TRIGGER0 . SIO_INTR_TRIGGER0
 */
#define  VTSS_F_DEVCPU_GCB_SIO_INTR_TRIGGER0_SIO_INTR_TRIGGER0(x)  (x)
#define  VTSS_M_DEVCPU_GCB_SIO_INTR_TRIGGER0_SIO_INTR_TRIGGER0     0xffffffff
#define  VTSS_X_DEVCPU_GCB_SIO_INTR_TRIGGER0_SIO_INTR_TRIGGER0(x)  (x)


/**
 * \brief Interrupt trigger mode 1
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_INTR_TRIGGER1
 *
 * @param ri Replicator: x_FFL_DEVCPU_SIO_IOS_PR_PORT (??), 0-3
 */
#define VTSS_DEVCPU_GCB_SIO_INTR_TRIGGER1(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x76 + (ri))

/**
 * \brief
 * See description of SIO_INTR_TRIGGER0.
 *
 * \details
 * Field: ::VTSS_DEVCPU_GCB_SIO_INTR_TRIGGER1 . SIO_INTR_TRIGGER1
 */
#define  VTSS_F_DEVCPU_GCB_SIO_INTR_TRIGGER1_SIO_INTR_TRIGGER1(x)  (x)
#define  VTSS_M_DEVCPU_GCB_SIO_INTR_TRIGGER1_SIO_INTR_TRIGGER1     0xffffffff
#define  VTSS_X_DEVCPU_GCB_SIO_INTR_TRIGGER1_SIO_INTR_TRIGGER1(x)  (x)


/**
 * \brief Currently interrupting SGPIOs
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_INTR
 *
 * @param ri Replicator: x_FFL_DEVCPU_SIO_IOS_PR_PORT (??), 0-3
 */
#define VTSS_DEVCPU_GCB_SIO_INTR(ri)         VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x7a + (ri))

/**
 * \brief
 * Interrupt register. These sticky bits are set when an input is received
 * that are triggered by the corresponding SIO_INTR_TRIGGER configuration.
 *
 * \details
 * 0: No interrupt for given gpio
 * 1: Interrupt for given gpio
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_INTR . SIO_INTR
 */
#define  VTSS_F_DEVCPU_GCB_SIO_INTR_SIO_INTR(x)  (x)
#define  VTSS_M_DEVCPU_GCB_SIO_INTR_SIO_INTR     0xffffffff
#define  VTSS_X_DEVCPU_GCB_SIO_INTR_SIO_INTR(x)  (x)


/**
 * \brief SGPIO interrupt enable per port
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_INTR_ENA
 *
 * @param ri Register: SIO_INTR_ENA (??), 0-3
 */
#define VTSS_DEVCPU_GCB_SIO_INTR_ENA(ri)     VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x7e + (ri))

/**
 * \brief
 * Interrupt enable vector with one enable bit for each port.Port order:
 * (portN down to port0).Replicated for each SGPIO of the port.
 *
 * \details
 * 0: Interrupt is disabled for the port
 * 1: Interrupt is enabled for the port
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_INTR_ENA . SIO_INTR_ENA
 */
#define  VTSS_F_DEVCPU_GCB_SIO_INTR_ENA_SIO_INTR_ENA(x)  (x)
#define  VTSS_M_DEVCPU_GCB_SIO_INTR_ENA_SIO_INTR_ENA     0xffffffff
#define  VTSS_X_DEVCPU_GCB_SIO_INTR_ENA_SIO_INTR_ENA(x)  (x)


/**
 * \brief Currently active interrupts
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_INTR_IDENT
 *
 * @param ri Replicator: x_FFL_DEVCPU_SIO_IOS_PR_PORT (??), 0-3
 */
#define VTSS_DEVCPU_GCB_SIO_INTR_IDENT(ri)   VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x82 + (ri))

/**
 * \brief
 * Shows the currently active interrupts. This register is the result of
 * the SIO_INTR interrupts with the disabled interrupts (from SIO_INTR_ENA
 * and SIO_GPIO_INTR_ENA) removed.
 *
 * \details
 * 0: No active interrupt for given gpio
 * 1: Active interrupt for given gpio
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_INTR_IDENT . SIO_INTR_IDENT
 */
#define  VTSS_F_DEVCPU_GCB_SIO_INTR_IDENT_SIO_INTR_IDENT(x)  (x)
#define  VTSS_M_DEVCPU_GCB_SIO_INTR_IDENT_SIO_INTR_IDENT     0xffffffff
#define  VTSS_X_DEVCPU_GCB_SIO_INTR_IDENT_SIO_INTR_IDENT(x)  (x)


#endif /* _VTSS_LAGUNA_REGS_DEVCPU_GCB_H_ */
