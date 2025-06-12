// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _LAN80XX_MALIBU25G_REGS_HOST_INTR_CTRL_H_
#define _LAN80XX_MALIBU25G_REGS_HOST_INTR_CTRL_H_

#include "regs_lan8042_common.h"

/***********************************************************************
 *
 * Target: \a HOST_INTR_CTRL
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a HOST_INTR_CTRL:H_INTR_CTRL
 *
 *  Host Interrupt Control Registers
 */


/**
 * \brief Host Interrupt Enables
 *
 * \details
 * Register: \a HOST_INTR_CTRL:H_INTR_CTRL:HOST_INTR_EN
 *
 * @param ri Register: HOST_INTR_EN (??), 0-1
 */
#define LAN80XX_HOST_INTR_CTRL_HOST_INTR_EN(ri)  LAN80XX_IOREG(MMD_ID_HOST_INTR_CTL, 0, 0xc010 + (ri))

/**
 * \brief
 * Host PMA (SD25G) interrupt enable.  Enables Host PMA interrupt to
 * propagate to corresponding slice host interrupt
 *
 * \details
 * 0 = Interrupt will not affect the corresponding slice host interrupt
 * 1 = Interrupt will propagate to the corresponding slice host interrupt
 *
 * Field: ::LAN80XX_HOST_INTR_CTRL_HOST_INTR_EN . HPMA_INTR_EN
 */
#define  LAN80XX_F_HOST_INTR_CTRL_HOST_INTR_EN_HPMA_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),5,1)
#define  LAN80XX_M_HOST_INTR_CTRL_HOST_INTR_EN_HPMA_INTR_EN  LAN80XX_BIT(5)
#define  LAN80XX_X_HOST_INTR_CTRL_HOST_INTR_EN_HPMA_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Host KR interrupt enable.  Enables Host KR interrupt to propagate to
 * corresponding slice host interrupt
 *
 * \details
 * 0 = Interrupt will not affect the corresponding slice host interrupt
 * 1 = Interrupt will propagate to the corresponding slice host interrupt
 *
 * Field: ::LAN80XX_HOST_INTR_CTRL_HOST_INTR_EN . HKR_INTR_EN
 */
#define  LAN80XX_F_HOST_INTR_CTRL_HOST_INTR_EN_HKR_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_INTR_CTRL_HOST_INTR_EN_HKR_INTR_EN  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_INTR_CTRL_HOST_INTR_EN_HKR_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * XGMII H2L FIFO interrupt enable.  Enables XGMII H2L FIFO interrupt to
 * propagate to corresponding slice host interrupt
 *
 * \details
 * 0 = Interrupt will not affect the corresponding slice host interrupt
 * 1 = Interrupt will propagate to the corresponding slice host interrupt
 *
 * Field: ::LAN80XX_HOST_INTR_CTRL_HOST_INTR_EN . XGMII_H2L_FIFO_INTR_EN
 */
#define  LAN80XX_F_HOST_INTR_CTRL_HOST_INTR_EN_XGMII_H2L_FIFO_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_HOST_INTR_CTRL_HOST_INTR_EN_XGMII_H2L_FIFO_INTR_EN  LAN80XX_BIT(3)
#define  LAN80XX_X_HOST_INTR_CTRL_HOST_INTR_EN_XGMII_H2L_FIFO_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Host CWM RA FIFO interrupt enable.  Enables Host CWM RA FIFO interrupt
 * to propagate to corresponding slice host interrupt
 *
 * \details
 * 0 = Interrupt will not affect the corresponding slice host interrupt
 * 1 = Interrupt will propagate to the corresponding slice host interrupt
 *
 * Field: ::LAN80XX_HOST_INTR_CTRL_HOST_INTR_EN . HCWM_RA_FIFO_INTR_EN
 */
#define  LAN80XX_F_HOST_INTR_CTRL_HOST_INTR_EN_HCWM_RA_FIFO_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_HOST_INTR_CTRL_HOST_INTR_EN_HCWM_RA_FIFO_INTR_EN  LAN80XX_BIT(2)
#define  LAN80XX_X_HOST_INTR_CTRL_HOST_INTR_EN_HCWM_RA_FIFO_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Host PCS1G interrupt enable.  Enables Host PCS1G interrupt to propagate
 * to corresponding slice host interrupt
 *
 * \details
 * 0 = Interrupt will not affect the corresponding slice host interrupt
 * 1 = Interrupt will propagate to the corresponding slice host interrupt
 *
 * Field: ::LAN80XX_HOST_INTR_CTRL_HOST_INTR_EN . HPCS1G_INTR_EN
 */
#define  LAN80XX_F_HOST_INTR_CTRL_HOST_INTR_EN_HPCS1G_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_HOST_INTR_CTRL_HOST_INTR_EN_HPCS1G_INTR_EN  LAN80XX_BIT(1)
#define  LAN80XX_X_HOST_INTR_CTRL_HOST_INTR_EN_HPCS1G_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Host PCS25G interrupt enable.  Enables Host PCS25G interrupt to
 * propagate to corresponding slice host interrupt
 *
 * \details
 * 0 = Interrupt will not affect the corresponding slice host interrupt
 * 1 = Interrupt will propagate to the corresponding slice host interrupt
 *
 * Field: ::LAN80XX_HOST_INTR_CTRL_HOST_INTR_EN . HPCS25G_INTR_EN
 */
#define  LAN80XX_F_HOST_INTR_CTRL_HOST_INTR_EN_HPCS25G_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_INTR_CTRL_HOST_INTR_EN_HPCS25G_INTR_EN  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_INTR_CTRL_HOST_INTR_EN_HPCS25G_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Host Interrupt Statuses
 *
 * \details
 * Register: \a HOST_INTR_CTRL:H_INTR_CTRL:HOST_INTR_STAT
 *
 * @param ri Register: HOST_INTR_STAT (??), 0-1
 */
#define LAN80XX_HOST_INTR_CTRL_HOST_INTR_STAT(ri)  LAN80XX_IOREG(MMD_ID_HOST_INTR_CTL, 0, 0xc012 + (ri))

/**
 * \brief
 * Host PMA (SD25G) interrupt status.  Indicates Host PMA interrupt is
 * pending or is masked.
 *
 * \details
 * 0 = Host PMA interrupt not pending or corresponding INTR_EN is cleared
 * 1 = Host PMA interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_HOST_INTR_CTRL_HOST_INTR_STAT . HPMA_INTR_STAT
 */
#define  LAN80XX_F_HOST_INTR_CTRL_HOST_INTR_STAT_HPMA_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),5,1)
#define  LAN80XX_M_HOST_INTR_CTRL_HOST_INTR_STAT_HPMA_INTR_STAT  LAN80XX_BIT(5)
#define  LAN80XX_X_HOST_INTR_CTRL_HOST_INTR_STAT_HPMA_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Host KR interrupt status.  Indicates Host KR interrupt is pending or is
 * masked.
 *
 * \details
 * 0 = Host KR interrupt not pending or corresponding INTR_EN is cleared
 * 1 = Host KR interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_HOST_INTR_CTRL_HOST_INTR_STAT . HKR_INTR_STAT
 */
#define  LAN80XX_F_HOST_INTR_CTRL_HOST_INTR_STAT_HKR_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_HOST_INTR_CTRL_HOST_INTR_STAT_HKR_INTR_STAT  LAN80XX_BIT(4)
#define  LAN80XX_X_HOST_INTR_CTRL_HOST_INTR_STAT_HKR_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * XGMII H2L FIFO interrupt status.  Indicates XGMII H2L FIFO interrupt is
 * pending or is masked
 *
 * \details
 * 0 = XGMII H2L FIFO interrupt not pending or corresponding INTR_EN is
 * cleared
 * 1 = XGMII H2L FIFO interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_HOST_INTR_CTRL_HOST_INTR_STAT . XGMII_H2L_FIFO_INTR_STAT
 */
#define  LAN80XX_F_HOST_INTR_CTRL_HOST_INTR_STAT_XGMII_H2L_FIFO_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_HOST_INTR_CTRL_HOST_INTR_STAT_XGMII_H2L_FIFO_INTR_STAT  LAN80XX_BIT(3)
#define  LAN80XX_X_HOST_INTR_CTRL_HOST_INTR_STAT_XGMII_H2L_FIFO_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Host CWM RA FIFO interrupt status.  Indicates Host CWM RA FIFO interrupt
 * is pending or is masked
 *
 * \details
 * 0 = Host CWM RA FIFO interrupt not pending or corresponding INTR_EN is
 * cleared
 * 1 = Host CWM RA FIFO pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_HOST_INTR_CTRL_HOST_INTR_STAT . HCWM_RA_FIFO_INTR_STAT
 */
#define  LAN80XX_F_HOST_INTR_CTRL_HOST_INTR_STAT_HCWM_RA_FIFO_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_HOST_INTR_CTRL_HOST_INTR_STAT_HCWM_RA_FIFO_INTR_STAT  LAN80XX_BIT(2)
#define  LAN80XX_X_HOST_INTR_CTRL_HOST_INTR_STAT_HCWM_RA_FIFO_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Host PCS1G interrupt status.  Indicates Host PCS1G interrupt is pending
 * or is masked
 *
 * \details
 * 0 = Host PCS1G interrupt not pending or corresponding INTR_EN is cleared
 * 1 = Host PCS1G interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_HOST_INTR_CTRL_HOST_INTR_STAT . HPCS1G_INTR_STAT
 */
#define  LAN80XX_F_HOST_INTR_CTRL_HOST_INTR_STAT_HPCS1G_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_HOST_INTR_CTRL_HOST_INTR_STAT_HPCS1G_INTR_STAT  LAN80XX_BIT(1)
#define  LAN80XX_X_HOST_INTR_CTRL_HOST_INTR_STAT_HPCS1G_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Host PCS25G interrupt status.  Indicates Host PCS25G interrupt is
 * pending or is masked
 *
 * \details
 * 0 = Host PCS25G interrupt not pending or corresponding INTR_EN is
 * cleared
 * 1 = Host PCS25G interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_HOST_INTR_CTRL_HOST_INTR_STAT . HPCS25G_INTR_STAT
 */
#define  LAN80XX_F_HOST_INTR_CTRL_HOST_INTR_STAT_HPCS25G_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_INTR_CTRL_HOST_INTR_STAT_HPCS25G_INTR_STAT  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_INTR_CTRL_HOST_INTR_STAT_HPCS25G_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


#endif /* _LAN80XX_MALIBU25G_REGS_HOST_INTR_CTRL_H_ */
