// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LAN80XX_MALIBU25G_REGS_SFP_TWS_H_
#define LAN80XX_MALIBU25G_REGS_SFP_TWS_H_

#include "regs_lan80xx_common.h"

/***********************************************************************
 *
 * Target: \a SFP_TWS
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a SFP_TWS:TWI_CFG
 *
 * Configuration Registers for TWI Host for optical module management
 */


/**
 * \brief TWI CLIENT ID
 *
 * \details
 * TWI CLIENT ID
 *
 * Register: \a SFP_TWS:TWI_CFG:TWI_CLIENT_ID
 */
#define LAN80XX_SFP_TWS_TWI_CLIENT_ID                                                               (LAN80XX_IOREG(MMD_ID_SFP_TWS, 0, 0xc000))

/**
 * \brief
 * TWI Client ID
 *
 * \details
 * Field: ::LAN80XX_SFP_TWS_TWI_CLIENT_ID . CLIENT_ID
 */
#define  LAN80XX_F_SFP_TWS_TWI_CLIENT_ID_CLIENT_ID(x)                                               (LAN80XX_ENCODE_BITFIELD(x,0,7))
#define  LAN80XX_M_SFP_TWS_TWI_CLIENT_ID_CLIENT_ID                                                  (LAN80XX_ENCODE_BITMASK(0,7))
#define  LAN80XX_X_SFP_TWS_TWI_CLIENT_ID_CLIENT_ID(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,0,7))


/**
 * \brief TWI Prescale (TWI Speed)
 *
 * \details
 * TWI Prescale (TWI Speed)
 *
 * Register: \a SFP_TWS:TWI_CFG:TWI_PRESCALE
 */
#define LAN80XX_SFP_TWS_TWI_PRESCALE                                                                (LAN80XX_IOREG(MMD_ID_SFP_TWS, 0, 0xc001))

/**
 * \brief
 * SCL Frequency = 300 MHz/5*(Prescale+1).0 to 0x3A are invalid settings.
 *
 * \details
 * Field: ::LAN80XX_SFP_TWS_TWI_PRESCALE . PRESCALE
 */
#define  LAN80XX_F_SFP_TWS_TWI_PRESCALE_PRESCALE(x)                                                 (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_SFP_TWS_TWI_PRESCALE_PRESCALE                                                    (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_SFP_TWS_TWI_PRESCALE_PRESCALE(x)                                                 (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a SFP_TWS:TWI_WRITE
 *
 * TWI Write Control Register
 */


/**
 * \brief TWI Write Control Register
 *
 * \details
 * TWI Write Control Register
 *
 * Register: \a SFP_TWS:TWI_WRITE:TWI_WRITE_CTRL
 */
#define LAN80XX_SFP_TWS_TWI_WRITE_CTRL                                                              (LAN80XX_IOREG(MMD_ID_SFP_TWS, 0, 0xc002))

/**
 * \brief
 * TWI Write Data. A write to the TWI_WRITE_CTRL register will trigger the
 * TWI Host to write the value in the WRITE_DATA register to the address
 * and Client ID specified in the WRITE_ADDR register and the TWI_CLIENT_ID
 * register.
 *
 * \details
 * Field: ::LAN80XX_SFP_TWS_TWI_WRITE_CTRL . WRITE_DATA
 */
#define  LAN80XX_F_SFP_TWS_TWI_WRITE_CTRL_WRITE_DATA(x)                                             (LAN80XX_ENCODE_BITFIELD(x,8,8))
#define  LAN80XX_M_SFP_TWS_TWI_WRITE_CTRL_WRITE_DATA                                                (LAN80XX_ENCODE_BITMASK(8,8))
#define  LAN80XX_X_SFP_TWS_TWI_WRITE_CTRL_WRITE_DATA(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,8,8))

/**
 * \brief
 * TWI Write Address. A write to the TWI_WRITE_CTRL register will trigger
 * the TWI Host to write the value in the WRITE_DATA register to the
 * address and Client ID specified in the WRITE_ADDR register and the
 * TWI_CLIENT_ID register.
 *
 * \details
 * Field: ::LAN80XX_SFP_TWS_TWI_WRITE_CTRL . WRITE_ADDR
 */
#define  LAN80XX_F_SFP_TWS_TWI_WRITE_CTRL_WRITE_ADDR(x)                                             (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_SFP_TWS_TWI_WRITE_CTRL_WRITE_ADDR                                                (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_SFP_TWS_TWI_WRITE_CTRL_WRITE_ADDR(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,0,8))

/**
 * Register Group: \a SFP_TWS:TWI_BUS_STAT
 *
 * TWI Bus Status
 */


/**
 * \brief TWI Bus Status
 *
 * \details
 * TWI Bus Status
 *
 * Register: \a SFP_TWS:TWI_BUS_STAT:TWI_BUS_STATUS
 */
#define LAN80XX_SFP_TWS_TWI_BUS_STATUS                                                              (LAN80XX_IOREG(MMD_ID_SFP_TWS, 0, 0xc003))

/**
 * \brief
 * TWI Write Acknowledge
 *
 * \details
 * 0: Idle
 * 1: Write Acknowledge
 *
 * Field: ::LAN80XX_SFP_TWS_TWI_BUS_STATUS . TWI_WRITE_ACK
 */
#define  LAN80XX_F_SFP_TWS_TWI_BUS_STATUS_TWI_WRITE_ACK(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_SFP_TWS_TWI_BUS_STATUS_TWI_WRITE_ACK                                             (LAN80XX_BIT(1))
#define  LAN80XX_X_SFP_TWS_TWI_BUS_STATUS_TWI_WRITE_ACK(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * TWI Bus Busy
 *
 * \details
 * 0: TWI bus is not busy
 * 1: TWI bus is busy
 *
 * Field: ::LAN80XX_SFP_TWS_TWI_BUS_STATUS . TWI_BUS_BUSY
 */
#define  LAN80XX_F_SFP_TWS_TWI_BUS_STATUS_TWI_BUS_BUSY(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_SFP_TWS_TWI_BUS_STATUS_TWI_BUS_BUSY                                              (LAN80XX_BIT(0))
#define  LAN80XX_X_SFP_TWS_TWI_BUS_STATUS_TWI_BUS_BUSY(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a SFP_TWS:TWI_READ_ADDRESS
 *
 * TWI Read Address Register
 */


/**
 * \brief TWI Read Address Register
 *
 * \details
 * TWI Read Address Register
 *
 * Register: \a SFP_TWS:TWI_READ_ADDRESS:TWI_READ_ADDR
 */
#define LAN80XX_SFP_TWS_TWI_READ_ADDR                                                               (LAN80XX_IOREG(MMD_ID_SFP_TWS, 0, 0xc004))

/**
 * \brief
 * TWI Read Address. A write to the READ_ADDR register will trigger the TWI
 * Host to read the value from the address and Client ID specified  in the
 * READ_ADDR register and the TWI_CLIENT_ID register, and store the value
 * in the READ_DATA register.
 *
 * \details
 * Field: ::LAN80XX_SFP_TWS_TWI_READ_ADDR . READ_ADDR
 */
#define  LAN80XX_F_SFP_TWS_TWI_READ_ADDR_READ_ADDR(x)                                               (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_SFP_TWS_TWI_READ_ADDR_READ_ADDR                                                  (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_SFP_TWS_TWI_READ_ADDR_READ_ADDR(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,0,8))

/**
 * Register Group: \a SFP_TWS:TWI_READ_STATUS_AND_DATA
 *
 * TWI Read Status And Data
 */


/**
 * \brief TWI Read Status And Data
 *
 * \details
 * TWI Read Status And Data
 *
 * Register: \a SFP_TWS:TWI_READ_STATUS_AND_DATA:TWI_READ_STATUS_DATA
 */
#define LAN80XX_SFP_TWS_TWI_READ_STATUS_DATA                                                        (LAN80XX_IOREG(MMD_ID_SFP_TWS, 0, 0xc005))

/**
 * \brief
 * TWI Bus Busy
 *
 * \details
 * 0: TWI bus is not busy, data updated
 * 1: TWI bus is busy, data not updated
 *
 * Field: ::LAN80XX_SFP_TWS_TWI_READ_STATUS_DATA . TWI_BUS_BUSY
 */
#define  LAN80XX_F_SFP_TWS_TWI_READ_STATUS_DATA_TWI_BUS_BUSY(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_SFP_TWS_TWI_READ_STATUS_DATA_TWI_BUS_BUSY                                        (LAN80XX_BIT(15))
#define  LAN80XX_X_SFP_TWS_TWI_READ_STATUS_DATA_TWI_BUS_BUSY(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 * TWI Read Data. The data in this register is the result of performing an
 * TWI Read operation, initiated by writing to the READ_ADDR register.
 *
 * \details
 * Field: ::LAN80XX_SFP_TWS_TWI_READ_STATUS_DATA . READ_DATA
 */
#define  LAN80XX_F_SFP_TWS_TWI_READ_STATUS_DATA_READ_DATA(x)                                        (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_SFP_TWS_TWI_READ_STATUS_DATA_READ_DATA                                           (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_SFP_TWS_TWI_READ_STATUS_DATA_READ_DATA(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,0,8))

/**
 * Register Group: \a SFP_TWS:TWI_RESET_SEQUENCE
 *
 * TWI Reset Sequence
 */


/**
 * \brief TWI Reset Sequence
 *
 * \details
 * TWI Reset Sequence
 *
 * Register: \a SFP_TWS:TWI_RESET_SEQUENCE:TWI_RESET_SEQ
 */
#define LAN80XX_SFP_TWS_TWI_RESET_SEQ                                                               (LAN80XX_IOREG(MMD_ID_SFP_TWS, 0, 0xc006))

/**
 * \brief
 * TWI Reset Sequence. A write to RESET_SEQ register (any value) will
 * trigger TWI Host to issue a Reset Sequence.
 *
 * \details
 * Field: ::LAN80XX_SFP_TWS_TWI_RESET_SEQ . RESET_SEQ
 */
#define  LAN80XX_F_SFP_TWS_TWI_RESET_SEQ_RESET_SEQ(x)                                               (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_SFP_TWS_TWI_RESET_SEQ_RESET_SEQ                                                  (LAN80XX_BIT(0))
#define  LAN80XX_X_SFP_TWS_TWI_RESET_SEQ_RESET_SEQ(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,0,1))


#endif /* _LAN80XX_MALIBU25G_REGS_SFP_TWS_H_ */
