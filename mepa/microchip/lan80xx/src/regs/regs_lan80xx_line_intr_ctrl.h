// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _LAN80XX_MALIBU25G_REGS_LINE_INTR_CTRL_H_
#define _LAN80XX_MALIBU25G_REGS_LINE_INTR_CTRL_H_

#include "regs_lan8042_common.h"

/***********************************************************************
 *
 * Target: \a LINE_INTR_CTRL
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a LINE_INTR_CTRL:L_INTR_CTRL
 *
 *  Line Interrupt Control Registers
 */


/**
 * \brief  Line Interrupt Enables
 *
 * \details
 * Register: \a LINE_INTR_CTRL:L_INTR_CTRL:LINE_INTR_EN
 *
 * @param ri Register: LINE_INTR_EN (??), 0-1
 */
#define LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN(ri)  LAN80XX_IOREG(MMD_ID_LINE_INTR_CTL, 0, 0xc010 + (ri))

/**
 * \brief
 * Line PMA interrupt enable.  Enables Line PMA interrupt to propagate to
 * corresponding slice line interrupt
 *
 * \details
 * 0 = Line PMA interrupt will not affect the corresponding slice line
 * interrupt
 * 1 = Line PMA interrupt will propagate to the corresponding slice line
 * interrupt
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN . LPMA_INTR_EN
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_LPMA_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),13,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_LPMA_INTR_EN  LAN80XX_BIT(13)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_EN_LPMA_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Line KR interrupt enable.  Enables Line KR interrupt to propagate to
 * corresponding slice line interrupt
 *
 * \details
 * 0 = Line KR interrupt will not affect the corresponding slice line
 * interrupt
 * 1 = Line KR interrupt will propagate to the corresponding slice line
 * interrupt
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN . LKR_INTR_EN
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_LKR_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),12,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_LKR_INTR_EN  LAN80XX_BIT(12)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_EN_LKR_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Line CWM RA FIFO interrupt enable.  Enables Line CWM RA FIFO interrupt
 * to propagate to corresponding slice line interrupt
 *
 * \details
 * 0 = Line CWM RA FIFO interrupt will not affect the corresponding slice
 * line interrupt
 * 1 = Line CWM RA FIFO interrupt will propagate to the corresponding slice
 * line interrupt
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN . LCWM_RA_FIFO_INTR_EN
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_LCWM_RA_FIFO_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),11,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_LCWM_RA_FIFO_INTR_EN  LAN80XX_BIT(11)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_EN_LCWM_RA_FIFO_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Flow Control Buffer interrupt enable.  Enables Flow Control Buffer
 * interrupt to propagate to corresponding slice line interrupt. Includes
 * both Ingress and Egress FC Buffer events.
 *
 * \details
 * 0 = Flow Control Buffer interrupt will not affect the corresponding
 * slice line interrupt
 * 1 = Flow Control Buffer interrupt will propagate to the corresponding
 * slice line interrupt
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN . FCBUF_INTR_EN
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_FCBUF_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),10,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_FCBUF_INTR_EN  LAN80XX_BIT(10)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_EN_FCBUF_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Host MAC interrupt enable.  Enables Host MAC interrupt to propagate to
 * corresponding slice line interrupt
 *
 * \details
 * 0 = Host MAC interrupt will not affect the corresponding slice line
 * interrupt
 * 1 = Host MAC interrupt will propagate to the corresponding slice line
 * interrupt
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN . HMAC_INTR_EN
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_HMAC_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),9,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_HMAC_INTR_EN  LAN80XX_BIT(9)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_EN_HMAC_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Line MAC interrupt enable.  Enables Line MAC interrupt to propagate to
 * corresponding slice line interrupt
 *
 * \details
 * 0 = Line MAC interrupt will not affect the corresponding slice line
 * interrupt
 * 1 = Line MAC interrupt will propagate to the corresponding slice line
 * interrupt
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN . LMAC_INTR_EN
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_LMAC_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_LMAC_INTR_EN  LAN80XX_BIT(8)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_EN_LMAC_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * MACSEC Ingress interrupt enable.  Enables MACSEC Ingress interrupt to
 * propagate to corresponding slice line interrupt
 *
 * \details
 * 0 = MACSEC Ingress interrupt will not affect the corresponding slice
 * line interrupt
 * 1 = MACSEC Ingress interrupt will propagate to the corresponding slice
 * line interrupt
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN . MSEC_IGR_INTR_EN
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_MSEC_IGR_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),7,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_MSEC_IGR_INTR_EN  LAN80XX_BIT(7)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_EN_MSEC_IGR_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * MACSEC Egress interrupt enable.  Enables MACSEC Egress interrupt to
 * propagate to corresponding slice line interrupt
 *
 * \details
 * 0 = MACSEC Egress interrupt will not affect the corresponding slice line
 * interrupt
 * 1 = MACSEC Egress interrupt will propagate to the corresponding slice
 * line interrupt
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN . MSEC_EGR_INTR_EN
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_MSEC_EGR_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),6,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_MSEC_EGR_INTR_EN  LAN80XX_BIT(6)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_EN_MSEC_EGR_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Line PCS1G interrupt enable.  Enables Line PCS1G interrupt to propagate
 * to corresponding slice line interrupt
 *
 * \details
 * 0 = Line PCS1G interrupt will not affect the corresponding slice line
 * interrupt
 * 1 = Line PCS1G interrupt will propagate to the corresponding slice line
 * interrupt
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN . LPCS1G_INTR_EN
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_LPCS1G_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),5,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_LPCS1G_INTR_EN  LAN80XX_BIT(5)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_EN_LPCS1G_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Line PCS25G interrupt enable.  Enables Line PCS25G interrupt to
 * propagate to corresponding slice line interrupt
 *
 * \details
 * 0 = Line PCS25G interrupt will not affect the corresponding slice line
 * interrupt
 * 1 = Line PCS25G interrupt will propagate to the corresponding slice line
 * interrupt
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN . LPCS25G_INTR_EN
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_LPCS25G_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_LPCS25G_INTR_EN  LAN80XX_BIT(4)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_EN_LPCS25G_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * PTP TSU Ingress interrupt enable.  Enables PTP TSU Ingress interrupt to
 * propagate to corresponding slice line interrupt
 *
 * \details
 * 0 = PTP TSU Ingress interrupt will not affect the corresponding slice
 * line interrupt
 * 1 = PTP TSU Ingress interrupt will propagate to the corresponding slice
 * line interrupt
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN . PTP_TSU_IGR_INTR_EN
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_PTP_TSU_IGR_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_PTP_TSU_IGR_INTR_EN  LAN80XX_BIT(3)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_EN_PTP_TSU_IGR_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * PTP TSU Egress interrupt enable.  Enables PTP TSU Egress interrupt to
 * propagate to corresponding slice line interrupt
 *
 * \details
 * 0 = PTP TSU Egress interrupt will not affect the corresponding slice
 * line interrupt
 * 1 = PTP TSU Egress interrupt will propagate to the corresponding slice
 * line interrupt
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN . PTP_TSU_EGR_INTR_EN
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_PTP_TSU_EGR_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_PTP_TSU_EGR_INTR_EN  LAN80XX_BIT(2)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_EN_PTP_TSU_EGR_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * PCS Retimer H2L RA FIFO interrupt enable.  Enables PCS Retimer H2L RA
 * FIFO interrupt to propagate to corresponding slice line i terrupt
 *
 * \details
 * 0 = PCS Retimer H2L RA FIFO interrupt will not affect the corresponding
 * slice line interrupt
 * 1 = PCS Retimer H2L RA FIFO interrupt will propagate to the
 * corresponding slice line interrupt
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN . H2L_RA_FIFO_INTR_EN
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_H2L_RA_FIFO_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_H2L_RA_FIFO_INTR_EN  LAN80XX_BIT(1)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_EN_H2L_RA_FIFO_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * PCS Retimer L2H RA FIFO interrupt enable.  Enables PCS Retimer L2H RA
 * FIFO interrupt to propagate to corresponding slice line interrupt
 *
 * \details
 * 0 = PCS Retimer L2H RA FIFO interrupt will not affect the corresponding
 * slice line interrupt
 * 1 = PCS Retimer L2H RA FIFO interrupt will propagate to the
 * corresponding slice line interrupt
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN . L2H_RA_FIFO_INTR_EN
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_L2H_RA_FIFO_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_L2H_RA_FIFO_INTR_EN  LAN80XX_BIT(0)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_EN_L2H_RA_FIFO_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief  Line Interrupt Statuses
 *
 * \details
 * Register: \a LINE_INTR_CTRL:L_INTR_CTRL:LINE_INTR_STAT
 *
 * @param ri Register: LINE_INTR_STAT (??), 0-1
 */
#define LAN80XX_LINE_INTR_CTRL_LINE_INTR_STAT(ri)  LAN80XX_IOREG(MMD_ID_LINE_INTR_CTL, 0, 0xc012 + (ri))

/**
 * \brief
 * Line PMA interrupt status.  Indicates Line PMA interrupt is pending or
 * is masked
 *
 * \details
 * 0 = Line PMA interrupt not pending or corresponding INTR_EN is cleared
 * 1 = Line PMA interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_STAT . LPMA_INTR_STAT
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_STAT_LPMA_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),13,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_STAT_LPMA_INTR_STAT  LAN80XX_BIT(13)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_STAT_LPMA_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Line KR interrupt status.  Indicates Line KR interrupt is pending or is
 * masked
 *
 * \details
 * 0 = Line KR interrupt not pending or corresponding INTR_EN is cleared
 * 1 = Line KR interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_STAT . LKR_INTR_STAT
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_STAT_LKR_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),12,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_STAT_LKR_INTR_STAT  LAN80XX_BIT(12)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_STAT_LKR_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Line CWM RA FIFO interrupt status.  Indicates Line CWM RA FIFO interrupt
 * is pending or is masked
 *
 * \details
 * 0 = Line CWM RA FIFO interrupt not pending or corresponding INTR_EN is
 * cleared
 * 1 = Line CWM RA FIFO interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_STAT . LCWM_RA_FIFO_INTR_STAT
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_STAT_LCWM_RA_FIFO_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),11,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_STAT_LCWM_RA_FIFO_INTR_STAT  LAN80XX_BIT(11)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_STAT_LCWM_RA_FIFO_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Flow Control Buffer interrupt status.  Includes both Ingress and Egress
 * FC Buffer events. Indicates Flow Control Buffer interrupt is pending or
 * is masked
 *
 * \details
 * 0 = Flow Control Buffer interrupt not pending or corresponding INTR_EN
 * is cleared
 * 1 = Flow Control Buffer interrupt pending and corresponding INTR_EN is
 * set
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_STAT . FCBUF_INTR_STAT
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_STAT_FCBUF_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),10,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_STAT_FCBUF_INTR_STAT  LAN80XX_BIT(10)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_STAT_FCBUF_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Host MAC interrupt status.  Indicates Host MAC interrupt is pending or
 * is masked
 *
 * \details
 * 0 = Host MAC interrupt not pending or corresponding INTR_EN is cleared
 * 1 = Host MAC interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_STAT . HMAC_INTR_STAT
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_STAT_HMAC_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),9,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_STAT_HMAC_INTR_STAT  LAN80XX_BIT(9)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_STAT_HMAC_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Line MAC interrupt status.  Indicates Line MAC interrupt is pending or
 * is masked
 *
 * \details
 * 0 = Line MAC interrupt not pending or corresponding INTR_EN is cleared
 * 1 = Line MAC interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_STAT . LMAC_INTR_STAT
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_STAT_LMAC_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_STAT_LMAC_INTR_STAT  LAN80XX_BIT(8)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_STAT_LMAC_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * MACSEC Ingress interrupt status.  Indicates MACSEC Ingress interrupt is
 * pending or is masked
 *
 * \details
 * 0 = MACSEC Ingress interrupt not pending or corresponding INTR_EN is
 * cleared
 * 1 = MACSEC Ingress interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_STAT . MSEC_IGR_INTR_STAT
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_STAT_MSEC_IGR_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),7,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_STAT_MSEC_IGR_INTR_STAT  LAN80XX_BIT(7)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_STAT_MSEC_IGR_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * MACSEC Egress interrupt status.  Indicates MACSEC Egress interrupt is
 * pending or is masked
 *
 * \details
 * 0 = MACSEC Egress interrupt not pending or corresponding INTR_EN is
 * cleared
 * 1 = MACSEC Egress interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_STAT . MSEC_EGR_INTR_STAT
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_STAT_MSEC_EGR_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),6,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_STAT_MSEC_EGR_INTR_STAT  LAN80XX_BIT(6)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_STAT_MSEC_EGR_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Line PCS1G interrupt status.  Indicates Line PCS1G interrupt is pending
 * or is masked
 *
 * \details
 * 0 = Line PCS1G interrupt not pending or corresponding INTR_EN is cleared
 * 1 = Line PCS1G interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_STAT . LPCS1G_INTR_STAT
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_STAT_LPCS1G_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),5,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_STAT_LPCS1G_INTR_STAT  LAN80XX_BIT(5)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_STAT_LPCS1G_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Line PCS25G interrupt status.  Indicates Line PCS25G interrupt is
 * pending or is masked
 *
 * \details
 * 0 = Line PCS25G interrupt not pending or corresponding INTR_EN is
 * cleared
 * 1 = Line PCS25G interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_STAT . LPCS25G_INTR_STAT
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_STAT_LPCS25G_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_STAT_LPCS25G_INTR_STAT  LAN80XX_BIT(4)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_STAT_LPCS25G_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * PTP TSU Ingress interrupt status.  Indicates PTP TSU Ingress interrupt
 * is pending or is masked
 *
 * \details
 * 0 = PTP TSU Ingress interrupt not pending or corresponding INTR_EN is
 * cleared
 * 1 = PTP TSU Ingress interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_STAT . PTP_TSU_IGR_INTR_STAT
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_STAT_PTP_TSU_IGR_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_STAT_PTP_TSU_IGR_INTR_STAT  LAN80XX_BIT(3)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_STAT_PTP_TSU_IGR_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * PTP TSU Egress interrupt status.  Indicates PTP TSU Egress interrupt is
 * pending or is masked
 *
 * \details
 * 0 = PTP TSU Egress interrupt not pending or corresponding INTR_EN is
 * cleared
 * 1 = PTP TSU Egress interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_STAT . PTP_TSU_EGR_INTR_STAT
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_STAT_PTP_TSU_EGR_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_STAT_PTP_TSU_EGR_INTR_STAT  LAN80XX_BIT(2)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_STAT_PTP_TSU_EGR_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * PCS Retimer H2L RA FIFO interrupt status.  Indicates PCS Retimer H2L RA
 * FIFO interrupt is pending or is masked
 *
 * \details
 * 0 = PCS Retimer H2L RA FIFO interrupt not pending or corresponding
 * INTR_EN is cleared
 * 1 = PCS Retimer H2L RA FIFO interrupt pending and corresponding INTR_EN
 * is set
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_STAT . H2L_RA_FIFO_INTR_STAT
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_STAT_H2L_RA_FIFO_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_STAT_H2L_RA_FIFO_INTR_STAT  LAN80XX_BIT(1)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_STAT_H2L_RA_FIFO_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * PCS Retimer L2H RA FIFO interrupt status.  Indicates PCS Retimer L2H RA
 * FIFO interrupt is pending or is masked
 *
 * \details
 * 0 = PCS Retimer L2H RA FIFO interrupt not pending or corresponding
 * INTR_EN is cleared
 * 1 = PCS Retimer L2H RA FIFO interrupt pending and corresponding INTR_EN
 * is set
 *
 * Field: ::LAN80XX_LINE_INTR_CTRL_LINE_INTR_STAT . L2H_RA_FIFO_INTR_STAT
 */
#define  LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_STAT_L2H_RA_FIFO_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_STAT_L2H_RA_FIFO_INTR_STAT  LAN80XX_BIT(0)
#define  LAN80XX_X_LINE_INTR_CTRL_LINE_INTR_STAT_L2H_RA_FIFO_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


#endif /* _LAN80XX_MALIBU25G_REGS_LINE_INTR_CTRL_H_ */
