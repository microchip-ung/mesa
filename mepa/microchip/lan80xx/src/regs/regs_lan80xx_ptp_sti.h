// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LAN80XX_MALIBU25G_REGS_PTP_STI_H_
#define LAN80XX_MALIBU25G_REGS_PTP_STI_H_

#include "regs_lan80xx_common.h"

/***********************************************************************
 *
 * Target: \a PTP_STI
 *
 * The registers comprise the configuration and status for the timestamp
 * serial interface in the implementation of the 1588 IP block.
 *
 ***********************************************************************/

/**
 * Register Group: \a PTP_STI:TS_FIFO_SI
 *
 * Timestamp FIFO serial interface registers
 */


/**
 * \brief Timestamp FIFO serial interface configuration register
 *
 * \details
 * Polarity and cycle counts are configurable from port 0 only
 *
 * Register: \a PTP_STI:TS_FIFO_SI:TS_FIFO_SI_CFG
 */
#define LAN80XX_PTP_STI_TS_FIFO_SI_CFG                                                              (LAN80XX_IOREG(MMD_ID_PTP_LTC, 1, 0xd200))

/**
 * \brief
 * Enables a debug mode that causes a fixed debug pattern of continuous
 * writes to the interface. Configurable from port 0 only.
 *
 * \details
 * 0: Disabled
 * 1: Enabled
 *
 * Field: ::LAN80XX_PTP_STI_TS_FIFO_SI_CFG . SI_DEBUG_MODE
 */
#define  LAN80XX_F_PTP_STI_TS_FIFO_SI_CFG_SI_DEBUG_MODE(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),31,1))
#define  LAN80XX_M_PTP_STI_TS_FIFO_SI_CFG_SI_DEBUG_MODE                                             (LAN80XX_BIT(31))
#define  LAN80XX_X_PTP_STI_TS_FIFO_SI_CFG_SI_DEBUG_MODE(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,31,1))

/**
 * \brief
 * SI clock phase control
 *
 * \details
 * 0: SI_CLK falling edge changes output data
 * 1: SI_CLK rising edge changes output data
 *
 * Field: ::LAN80XX_PTP_STI_TS_FIFO_SI_CFG . SI_CLK_PHA
 */
#define  LAN80XX_F_PTP_STI_TS_FIFO_SI_CFG_SI_CLK_PHA(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),25,1))
#define  LAN80XX_M_PTP_STI_TS_FIFO_SI_CFG_SI_CLK_PHA                                                (LAN80XX_BIT(25))
#define  LAN80XX_X_PTP_STI_TS_FIFO_SI_CFG_SI_CLK_PHA(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,25,1))

/**
 * \brief
 * SI clock polarity control
 *
 * \details
 * 0: SI_CLK starts and ends (idles) low
 * 1: SI_CLK starts and ends (idles) high
 *
 * Field: ::LAN80XX_PTP_STI_TS_FIFO_SI_CFG . SI_CLK_POL
 */
#define  LAN80XX_F_PTP_STI_TS_FIFO_SI_CFG_SI_CLK_POL(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),24,1))
#define  LAN80XX_M_PTP_STI_TS_FIFO_SI_CFG_SI_CLK_POL                                                (LAN80XX_BIT(24))
#define  LAN80XX_X_PTP_STI_TS_FIFO_SI_CFG_SI_CLK_POL(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,24,1))

/**
 * \brief
 * Number of CSR clock periods SI_EN negates between writes (deselected).
 * The CSR clock period is one-half the REFCLK pin's period.
 *
 * \details
 * Field: ::LAN80XX_PTP_STI_TS_FIFO_SI_CFG . SI_EN_DES_CYCS
 */
#define  LAN80XX_F_PTP_STI_TS_FIFO_SI_CFG_SI_EN_DES_CYCS(x)                                         (LAN80XX_ENCODE_BITFIELD(x,20,4))
#define  LAN80XX_M_PTP_STI_TS_FIFO_SI_CFG_SI_EN_DES_CYCS                                            (LAN80XX_ENCODE_BITMASK(20,4))
#define  LAN80XX_X_PTP_STI_TS_FIFO_SI_CFG_SI_EN_DES_CYCS(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,20,4))

/**
 * \brief
 * Number of extra CSR clock periods after SI_EN asserts before the first
 * SI_CLK
 *
 * \details
 * Field: ::LAN80XX_PTP_STI_TS_FIFO_SI_CFG . SI_EN_ON_CYCS
 */
#define  LAN80XX_F_PTP_STI_TS_FIFO_SI_CFG_SI_EN_ON_CYCS(x)                                          (LAN80XX_ENCODE_BITFIELD(x,16,4))
#define  LAN80XX_M_PTP_STI_TS_FIFO_SI_CFG_SI_EN_ON_CYCS                                             (LAN80XX_ENCODE_BITMASK(16,4))
#define  LAN80XX_X_PTP_STI_TS_FIFO_SI_CFG_SI_EN_ON_CYCS(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,16,4))

/**
 * \brief
 * Number of extra CSR clock periods after the last SI_CLK before SI_EN
 * negates
 *
 * \details
 * Field: ::LAN80XX_PTP_STI_TS_FIFO_SI_CFG . SI_EN_OFF_CYCS
 */
#define  LAN80XX_F_PTP_STI_TS_FIFO_SI_CFG_SI_EN_OFF_CYCS(x)                                         (LAN80XX_ENCODE_BITFIELD(x,12,4))
#define  LAN80XX_M_PTP_STI_TS_FIFO_SI_CFG_SI_EN_OFF_CYCS                                            (LAN80XX_ENCODE_BITMASK(12,4))
#define  LAN80XX_X_PTP_STI_TS_FIFO_SI_CFG_SI_EN_OFF_CYCS(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,12,4))

/**
 * \brief
 * Number of CSR clock periods that the SI_CLK is high. The CSR clock
 * period is one-half the REFCLK pin's period.
 *
 * \details
 * Field: ::LAN80XX_PTP_STI_TS_FIFO_SI_CFG . SI_CLK_HI_CYCS
 */
#define  LAN80XX_F_PTP_STI_TS_FIFO_SI_CFG_SI_CLK_HI_CYCS(x)                                         (LAN80XX_ENCODE_BITFIELD(x,6,5))
#define  LAN80XX_M_PTP_STI_TS_FIFO_SI_CFG_SI_CLK_HI_CYCS                                            (LAN80XX_ENCODE_BITMASK(6,5))
#define  LAN80XX_X_PTP_STI_TS_FIFO_SI_CFG_SI_CLK_HI_CYCS(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,6,5))

/**
 * \brief
 * Number of CSR clock periods that the SI_CLK is low. The CSR clock period
 * is one-half the REFCLK pin's period.
 *
 * \details
 * Field: ::LAN80XX_PTP_STI_TS_FIFO_SI_CFG . SI_CLK_LO_CYCS
 */
#define  LAN80XX_F_PTP_STI_TS_FIFO_SI_CFG_SI_CLK_LO_CYCS(x)                                         (LAN80XX_ENCODE_BITFIELD(x,1,5))
#define  LAN80XX_M_PTP_STI_TS_FIFO_SI_CFG_SI_CLK_LO_CYCS                                            (LAN80XX_ENCODE_BITMASK(1,5))
#define  LAN80XX_X_PTP_STI_TS_FIFO_SI_CFG_SI_CLK_LO_CYCS(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,1,5))

/**
 * \brief
 * Timestamp FIFO serial interface block control
 *
 * \details
 * 0: Disable Timestamp FIFO serial interface block
 * 1: Enable Timestamp FIFO serial interface block
 *
 * Field: ::LAN80XX_PTP_STI_TS_FIFO_SI_CFG . TS_FIFO_SI_ENA
 */
#define  LAN80XX_F_PTP_STI_TS_FIFO_SI_CFG_TS_FIFO_SI_ENA(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_PTP_STI_TS_FIFO_SI_CFG_TS_FIFO_SI_ENA                                            (LAN80XX_BIT(0))
#define  LAN80XX_X_PTP_STI_TS_FIFO_SI_CFG_TS_FIFO_SI_ENA(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief Transmitted timestamp count
 *
 * \details
 * Counter for the number of timestamps transmitted to the interface
 *
 * Register: \a PTP_STI:TS_FIFO_SI:TS_FIFO_SI_TX_CNT
 *
 * @param ri Register: TS_FIFO_SI_TX_CNT (??), 0-3
 */
#define LAN80XX_PTP_STI_TS_FIFO_SI_TX_CNT(ri)                                                       (LAN80XX_IOREG(MMD_ID_PTP_LTC,0xd201 + (ri)))
/**
 * \brief
 * Counter value
 *
 * \details
 * Field: ::LAN80XX_PTP_STI_TS_FIFO_SI_TX_CNT . TS_FIFO_SI_TX_CNT
 */
#define  LAN80XX_F_PTP_STI_TS_FIFO_SI_TX_CNT_TS_FIFO_SI_TX_CNT(x)                                   (x)
#define  LAN80XX_M_PTP_STI_TS_FIFO_SI_TX_CNT_TS_FIFO_SI_TX_CNT     (0xFFFFFFFFU)
#define  LAN80XX_X_PTP_STI_TS_FIFO_SI_TX_CNT_TS_FIFO_SI_TX_CNT(x)                                   (x)

/**
 * Register Group: \a PTP_STI:STI_SPARE_REG
 *
 * STI spare register
 */


/**
 * \brief STI space register configuration
 *
 * \details
 * Register: \a PTP_STI:STI_SPARE_REG:STI_SPARE_REG_CFG
 */
#define LAN80XX_PTP_STI_STI_SPARE_REG_CFG                                                           (LAN80XX_IOREG(MMD_ID_PTP_STI,0xd205))

/**
 * \brief
 * STI 32-bit spare register default FF00_0000
 *
 * \details
 * Field: ::LAN80XX_PTP_STI_STI_SPARE_REG_CFG . STI_SPACE_REGS
 */
#define  LAN80XX_F_PTP_STI_STI_SPARE_REG_CFG_STI_SPACE_REGS(x)                                      (x)
#define  LAN80XX_M_PTP_STI_STI_SPARE_REG_CFG_STI_SPACE_REGS     (0xFFFFFFFFU)
#define  LAN80XX_X_PTP_STI_STI_SPARE_REG_CFG_STI_SPACE_REGS(x)                                      (x)

/**
 * Register Group: \a PTP_STI:STI_DEBUG
 *
 * STI Debug register
 */


/**
 * \brief STI debug 0 configuration
 *
 * \details
 * Register: \a PTP_STI:STI_DEBUG:STI_DEBUG0_CFG
 */
#define LAN80XX_PTP_STI_STI_DEBUG0_CFG                                                              (LAN80XX_IOREG(MMD_ID_PTP_STI,0xd2f8))

/**
 * \brief
 * STI debug 0 register
 *
 * \details
 * Field: ::LAN80XX_PTP_STI_STI_DEBUG0_CFG . STI_DEBUG0
 */
#define  LAN80XX_F_PTP_STI_STI_DEBUG0_CFG_STI_DEBUG0(x)                                             (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PTP_STI_STI_DEBUG0_CFG_STI_DEBUG0                                                (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PTP_STI_STI_DEBUG0_CFG_STI_DEBUG0(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief STI debug 1 configuration
 *
 * \details
 * Register: \a PTP_STI:STI_DEBUG:STI_DEBUG1_CFG
 */
#define LAN80XX_PTP_STI_STI_DEBUG1_CFG                                                              (LAN80XX_IOREG(MMD_ID_PTP_STI,0xd2f9))

/**
 * \brief
 * STI debug 1 register
 *
 * \details
 * Field: ::LAN80XX_PTP_STI_STI_DEBUG1_CFG . STI_DEBUG1
 */
#define  LAN80XX_F_PTP_STI_STI_DEBUG1_CFG_STI_DEBUG1(x)                                             (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PTP_STI_STI_DEBUG1_CFG_STI_DEBUG1                                                (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PTP_STI_STI_DEBUG1_CFG_STI_DEBUG1(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief STI debug 2 configuration
 *
 * \details
 * Register: \a PTP_STI:STI_DEBUG:STI_DEBUG2_CFG
 */
#define LAN80XX_PTP_STI_STI_DEBUG2_CFG                                                              (LAN80XX_IOREG(MMD_ID_PTP_STI,0xd2fa))

/**
 * \brief
 * STI debug 2 register
 *
 * \details
 * Field: ::LAN80XX_PTP_STI_STI_DEBUG2_CFG . STI_DEBUG2
 */
#define  LAN80XX_F_PTP_STI_STI_DEBUG2_CFG_STI_DEBUG2(x)                                             (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PTP_STI_STI_DEBUG2_CFG_STI_DEBUG2                                                (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PTP_STI_STI_DEBUG2_CFG_STI_DEBUG2(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief STI debug 3 configuration
 *
 * \details
 * Register: \a PTP_STI:STI_DEBUG:STI_DEBUG3_CFG
 */
#define LAN80XX_PTP_STI_STI_DEBUG3_CFG                                                              (LAN80XX_IOREG(MMD_ID_PTP_STI,0xd2fb))

/**
 * \brief
 * STI debug 3 register
 *
 * \details
 * Field: ::LAN80XX_PTP_STI_STI_DEBUG3_CFG . STI_DEBUG3
 */
#define  LAN80XX_F_PTP_STI_STI_DEBUG3_CFG_STI_DEBUG3(x)                                             (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PTP_STI_STI_DEBUG3_CFG_STI_DEBUG3                                                (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PTP_STI_STI_DEBUG3_CFG_STI_DEBUG3(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief STI debug 4 configuration
 *
 * \details
 * Register: \a PTP_STI:STI_DEBUG:STI_DEBUG4_CFG
 */
#define LAN80XX_PTP_STI_STI_DEBUG4_CFG                                                              (LAN80XX_IOREG(MMD_ID_PTP_STI,0xd2fc))

/**
 * \brief
 * STI debug 4 register
 *
 * \details
 * Field: ::LAN80XX_PTP_STI_STI_DEBUG4_CFG . STI_DEBUG4
 */
#define  LAN80XX_F_PTP_STI_STI_DEBUG4_CFG_STI_DEBUG4(x)                                             (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PTP_STI_STI_DEBUG4_CFG_STI_DEBUG4                                                (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PTP_STI_STI_DEBUG4_CFG_STI_DEBUG4(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief STI debug 5 configuration
 *
 * \details
 * Register: \a PTP_STI:STI_DEBUG:STI_DEBUG5_CFG
 */
#define LAN80XX_PTP_STI_STI_DEBUG5_CFG                                                              (LAN80XX_IOREG(MMD_ID_PTP_STI,0xd2fd))

/**
 * \brief
 * STI debug 5 register
 *
 * \details
 * Field: ::LAN80XX_PTP_STI_STI_DEBUG5_CFG . STI_DEBUG5
 */
#define  LAN80XX_F_PTP_STI_STI_DEBUG5_CFG_STI_DEBUG5(x)                                             (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PTP_STI_STI_DEBUG5_CFG_STI_DEBUG5                                                (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PTP_STI_STI_DEBUG5_CFG_STI_DEBUG5(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief STI debug 6 configuration
 *
 * \details
 * Register: \a PTP_STI:STI_DEBUG:STI_DEBUG6_CFG
 */
#define LAN80XX_PTP_STI_STI_DEBUG6_CFG                                                              (LAN80XX_IOREG(MMD_ID_PTP_STI,0xd2fe))

/**
 * \brief
 * STI debug 6 register
 *
 * \details
 * Field: ::LAN80XX_PTP_STI_STI_DEBUG6_CFG . STI_DEBUG6
 */
#define  LAN80XX_F_PTP_STI_STI_DEBUG6_CFG_STI_DEBUG6(x)                                             (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PTP_STI_STI_DEBUG6_CFG_STI_DEBUG6                                                (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PTP_STI_STI_DEBUG6_CFG_STI_DEBUG6(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief STI debug 7 configuration
 *
 * \details
 * Register: \a PTP_STI:STI_DEBUG:STI_DEBUG7_CFG
 */
#define LAN80XX_PTP_STI_STI_DEBUG7_CFG                                                              (LAN80XX_IOREG(MMD_ID_PTP_STI,0xd2ff))

/**
 * \brief
 * STI debug 7 register
 *
 * \details
 * bit[1:0]: select 1 out of  4 sub-groups for STI_DEBUG0
 * bit[3;2]: select 1 out of  4 sub-groups for STI_DEBUG1
 * bit[5:4]: select 1 out of  4 sub-groups for STI_DEBUG2
 * bit[7:6]: select 1 out of  4 sub-groups for STI_DEBUG3
 * bit[9:8]: select 1 out of  4 sub-groups for STI_DEBUG4
 * bit[12:10]: select 1 out of 8 sub-groups for STI_DEBUG5    [note:
 * bit[12] may not be used when only 4 sub-groups are provided.]
 * bit[15:13]: select 1 out of 8 sub-groups for STI_DEBUG6    [note:
 * bit[15] may not be used when only 4 sub-groups are provided.]
 *
 * Field: ::LAN80XX_PTP_STI_STI_DEBUG7_CFG . STI_DEBUG7
 */
#define  LAN80XX_F_PTP_STI_STI_DEBUG7_CFG_STI_DEBUG7(x)                                             (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_PTP_STI_STI_DEBUG7_CFG_STI_DEBUG7                                                (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_PTP_STI_STI_DEBUG7_CFG_STI_DEBUG7(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,0,16))


#endif /* _LAN80XX_MALIBU25G_REGS_PTP_STI_H_ */
