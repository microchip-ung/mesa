// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include "lan80xx_private.h"
#include "lan80xx_regs_util.h"
#include "regs_lan80xx.h"
#include "lan80xx.h"


/* MACROs to Configure "GPIO_CTRL.INTR_SRC_EN" Register  (x = Channel id)*/
#define LAN80XX_GPIO_INTR0_LINE_SRC_SELECT(x)   ((1U << 8) << (x * 2U))  /* Enable INTR0 of Channel Level LINE Interrupts */
#define LAN80XX_GPIO_INTR1_LINE_SRC_SELECT(x)   ((1U << 9) << (x * 2U))  /* Enable INTR1 of Channel Level LINE Interrupts */
#define LAN80XX_GPIO_INTR1_HOST_SRC_SELECT(x)   ((1U << 1) << (x * 2U))  /* Enable INTR1 of Channel Level HOST side Interrupts */
#define LAN80XX_GPIO_INTR0_HOST_SRC_SELECT(x)    (1U << (x * 2U))        /* Enable INTR0 of channel Level HOST Side Interrupts */

#define LAN80XX_ENABLE_GPIO_INTERRUPT_FOR_EVENT(port, sel, intr) \
            LAN80XX_CSR_WRM(port, LAN80XX_GPIO_CTRL_INTR_SRC_EN(sel), intr, intr)

#define LAN80XX_DISABLE_GPIO_INTERRUPT_FOR_EVENT(port, sel, intr) \
            LAN80XX_CSR_WRM(port, LAN80XX_GPIO_CTRL_INTR_SRC_EN(sel), 0U, intr)

#define LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(port, sel, ch, line) \
        line ? (LAN80XX_CSR_WRM(port, LAN80XX_GPIO_CTRL_INTR_SRC_EN(sel), \
        sel ? LAN80XX_GPIO_INTR1_LINE_SRC_SELECT(ch) : LAN80XX_GPIO_INTR0_LINE_SRC_SELECT(ch), \
        sel ? LAN80XX_GPIO_INTR1_LINE_SRC_SELECT(ch) : LAN80XX_GPIO_INTR0_LINE_SRC_SELECT(ch))) : \
        (LAN80XX_CSR_WRM(port, LAN80XX_GPIO_CTRL_INTR_SRC_EN(sel), \
        sel ? LAN80XX_GPIO_INTR1_HOST_SRC_SELECT(ch) : LAN80XX_GPIO_INTR0_HOST_SRC_SELECT(ch), \
        sel ? LAN80XX_GPIO_INTR1_HOST_SRC_SELECT(ch) : LAN80XX_GPIO_INTR0_HOST_SRC_SELECT(ch)))

#define LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(port, sel, ch, line) \
        line ? (LAN80XX_CSR_WRM(port, LAN80XX_GPIO_CTRL_INTR_SRC_EN(sel), \
        0U, sel ? LAN80XX_GPIO_INTR1_LINE_SRC_SELECT(ch) : LAN80XX_GPIO_INTR0_LINE_SRC_SELECT(ch))) : \
        (LAN80XX_CSR_WRM(port, LAN80XX_GPIO_CTRL_INTR_SRC_EN(sel), \
        0U, sel ? LAN80XX_GPIO_INTR1_HOST_SRC_SELECT(ch) : LAN80XX_GPIO_INTR0_HOST_SRC_SELECT(ch)))

static mepa_rc lan80xx_gpio_intr_event_poll(mepa_device_t         *dev,
                                            const mepa_port_no_t  port_no,
                                            u64                   intr,
                                            phy25g_events_t       *const evt)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask0 = 0xFFFFFFFF, mask1 = 0x000000F0, reg_val0 = 0, reg_val1 = 0;

    LAN80XX_CSR_RD(dev, port_no,  LAN80XX_GPIO_CTRL_GPIO_CHANGEX_SLOT(1U), &reg_val0);
    LAN80XX_CSR_RD(dev, port_no,  LAN80XX_GPIO_CTRL_GPIO_CHANGEX_SLOT(0U), &reg_val1);
    if (((reg_val0 & mask0) == 0U) && ((reg_val1 & mask1) == 0U)) {
        return MEPA_RC_OK;
    }
    LAN80XX_CSR_WRM(port_no, LAN80XX_GPIO_CTRL_GPIO_CHANGEX_SLOT(1U), reg_val0, mask0);
    LAN80XX_CSR_WRM(port_no, LAN80XX_GPIO_CTRL_GPIO_CHANGEX_SLOT(0U), (reg_val1 & mask1), mask0);
    *evt = (*evt | intr);

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_xconnect_ext_event_poll(mepa_device_t   *dev,
                                               const mepa_port_no_t  port_no,
                                               u64                   intr,
                                               mepa_bool_t           is_intr2,
                                               phy25g_ext_events_t   *const evt)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0, val = 0;
    ioreg_blk *io_reg;

    if (is_intr2 == 1U) {
        /* Crossconnect INTR */
        mask = ((intr == LAN80XX_WPS1_FC_ACK_TIMER_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR2_WPS1_FC_ACK_TIMER_STICKY : 0U) |
               ((intr == LAN80XX_WPS0_FC_ACK_TIMER_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR2_WPS0_FC_ACK_TIMER_STICKY : 0U) |
               ((intr == LAN80XX_WPS1_CONN_FAULT_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR2_WPS1_CONN_FAULT_STICKY : 0U) |
               ((intr == LAN80XX_WPS0_CONN_FAULT_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR2_WPS0_CONN_FAULT_STICKY : 0U) |
               ((intr == LAN80XX_WPS1_FAILOVER_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR2_WPS1_FAILOVER_STICKY : 0U) |
               ((intr == LAN80XX_WPS0_FAILOVER_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR2_WPS0_FAILOVER_STICKY : 0U);

        io_reg = LAN80XX_CROSS_CONNECT_INTR2;
    } else {
        /* Crossconnect INTR */
        mask = ((intr == LAN80XX_H0_SWITCH_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H0_SWITCH_STICKY : 0U) |
               ((intr == LAN80XX_H1_SWITCH_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H1_SWITCH_STICKY : 0U) |
               ((intr == LAN80XX_H2_SWITCH_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H2_SWITCH_STICKY : 0U) |
               ((intr == LAN80XX_H3_SWITCH_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H3_SWITCH_STICKY : 0U) |
               ((intr == LAN80XX_L0_SWITCH_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L0_SWITCH_STICKY : 0U) |
               ((intr == LAN80XX_L1_SWITCH_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L1_SWITCH_STICKY : 0U) |
               ((intr == LAN80XX_L2_SWITCH_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L2_SWITCH_STICKY : 0U) |
               ((intr == LAN80XX_L3_SWITCH_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L3_SWITCH_STICKY : 0U) |
               ((intr == LAN80XX_H0_COND_ALT_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H0_COND_ALT_DET_STICKY : 0U) |
               ((intr == LAN80XX_H1_COND_ALT_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H1_COND_ALT_DET_STICKY : 0U) |
               ((intr == LAN80XX_H2_COND_ALT_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H2_COND_ALT_DET_STICKY : 0U) |
               ((intr == LAN80XX_H3_COND_ALT_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H3_COND_ALT_DET_STICKY : 0U) |
               ((intr == LAN80XX_L0_COND_ALT_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L0_COND_ALT_DET_STICKY : 0U) |
               ((intr == LAN80XX_L1_COND_ALT_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L1_COND_ALT_DET_STICKY : 0U) |
               ((intr == LAN80XX_L2_COND_ALT_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L2_COND_ALT_DET_STICKY : 0U) |
               ((intr == LAN80XX_L3_COND_ALT_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L3_COND_ALT_DET_STICKY : 0U) |
               ((intr == LAN80XX_H0_COND_ALT_UNF_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H0_COND_ALT_UNF_DET_STICKY : 0U) |
               ((intr == LAN80XX_H1_COND_ALT_UNF_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H1_COND_ALT_UNF_DET_STICKY : 0U) |
               ((intr == LAN80XX_H2_COND_ALT_UNF_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H2_COND_ALT_UNF_DET_STICKY : 0U) |
               ((intr == LAN80XX_H3_COND_ALT_UNF_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H3_COND_ALT_UNF_DET_STICKY : 0U) |
               ((intr == LAN80XX_L0_COND_ALT_UNF_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L0_COND_ALT_UNF_DET_STICKY : 0U) |
               ((intr == LAN80XX_L1_COND_ALT_UNF_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L1_COND_ALT_UNF_DET_STICKY : 0U) |
               ((intr == LAN80XX_L2_COND_ALT_UNF_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L2_COND_ALT_UNF_DET_STICKY : 0U) |
               ((intr == LAN80XX_L3_COND_ALT_UNF_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L3_COND_ALT_UNF_DET_STICKY : 0U) |
               ((intr == LAN80XX_H0_FIFO_ERROR_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H0_FIFO_ERROR_STICKY : 0U) |
               ((intr == LAN80XX_H1_FIFO_ERROR_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H1_FIFO_ERROR_STICKY : 0U) |
               ((intr == LAN80XX_H2_FIFO_ERROR_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H2_FIFO_ERROR_STICKY : 0U) |
               ((intr == LAN80XX_H3_FIFO_ERROR_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H3_FIFO_ERROR_STICKY : 0U) |
               ((intr == LAN80XX_L0_FIFO_ERROR_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L0_FIFO_ERROR_STICKY : 0U) |
               ((intr == LAN80XX_L1_FIFO_ERROR_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L1_FIFO_ERROR_STICKY : 0U) |
               ((intr == LAN80XX_L2_FIFO_ERROR_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L2_FIFO_ERROR_STICKY : 0U) |
               ((intr == LAN80XX_L3_FIFO_ERROR_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L3_FIFO_ERROR_STICKY : 0U);

        io_reg = LAN80XX_CROSS_CONNECT_INTR;
    }
    LAN80XX_CSR_RD(dev, port_no, io_reg, &val);
    if ((val & mask) == 0U) {
        return MEPA_RC_OK;
    }
    *evt = (*evt | intr);
    LAN80XX_CSR_WRM(port_no, io_reg, mask, mask);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_1g_pcs_event_poll(mepa_device_t         *dev,
                                         const mepa_port_no_t  port_no,
                                         u64                   intr,
                                         mepa_bool_t           is_line,
                                         phy25g_events_t       *const evt)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0, val = 0;
    ioreg_blk *io_reg;
    if (is_line == 1U) {
        /* 1G LINE PCS Interrupt */
        mask = (intr == LAN80XX_LINE_PCS1G_LINK_DOWN_INTR) ? LAN80XX_M_LINE_PCS_CFG_PCS1G_STICKY_LINK_DOWN_STICKY :
               LAN80XX_M_LINE_PCS_CFG_PCS1G_STICKY_OUT_OF_SYNC_STICKY;

        io_reg = LAN80XX_LINE_PCS_CFG_PCS1G_STICKY;
    } else {
        mask = (intr == LAN80XX_HOST_PCS1G_LINK_DOWN_INTR) ? LAN80XX_M_HOST_PCS_CFG_PCS1G_STICKY_LINK_DOWN_STICKY :
               LAN80XX_M_HOST_PCS_CFG_PCS1G_STICKY_OUT_OF_SYNC_STICKY;

        io_reg = LAN80XX_HOST_PCS_CFG_PCS1G_STICKY;
    }
    LAN80XX_CSR_RD(dev, port_no, io_reg, &val);
    if ((val & mask) == 0U) {
        return MEPA_RC_OK;
    }
    *evt = (*evt | intr);
    LAN80XX_CSR_WRM(port_no, io_reg, mask, mask);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_pma_event_poll(mepa_device_t         *dev,
                                      const mepa_port_no_t  port_no,
                                      u64                   intr,
                                      mepa_bool_t           is_line,
                                      phy25g_ext_events_t   *const evt)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0, val = 0;
    ioreg_blk *io_reg;
    if (is_line == 1U) {
        /* LINE PMA Interrupt */
        mask = ((intr == LAN80XX_LINE_PMA_RXEI_FILTERED_INTR) ? LAN80XX_M_LINE_PMA_PMA_IRQ_VEC_PMA_RXEI_FILTERED_INT : 0U) |
               ((intr == LAN80XX_LINE_PMA_RESET_DONE_INTR) ? LAN80XX_M_LINE_PMA_PMA_IRQ_VEC_PMA_RESET_DONE : 0U );

        io_reg = LAN80XX_LINE_PMA_PMA_IRQ_VEC;
    } else {
        /* HOST PMA Interrupt */
        mask = ((intr == LAN80XX_HOST_PMA_RXEI_FILTERED_INTR) ? LAN80XX_M_HOST_PMA_PMA_IRQ_VEC_PMA_RXEI_FILTERED_INT : 0U) |
               ((intr == LAN80XX_HOST_PMA_RESET_DONE_INTR) ? LAN80XX_M_HOST_PMA_PMA_IRQ_VEC_PMA_RESET_DONE : 0U );

        io_reg = LAN80XX_HOST_PMA_PMA_IRQ_VEC;
    }
    LAN80XX_CSR_RD(dev, port_no, io_reg, &val);
    if ((val & mask) == 0U) {
        return MEPA_RC_OK;
    }
    *evt = (*evt | intr);
    LAN80XX_CSR_WRM(port_no, io_reg, mask, mask);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_pma_event_conf(mepa_device_t         *dev,
                                      const mepa_port_no_t  port_no,
                                      u64                   intr,
                                      mepa_bool_t           is_line,
                                      mepa_bool_t           enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0;

    if (is_line == 1U) {
        /* LINE PMA */
        mask = ((intr == LAN80XX_LINE_PMA_RESET_DONE_INTR) ?  LAN80XX_M_LINE_PMA_PMA_IRQ_MASK_PMA_RESET_DONE_INT_EN : 0U)    |
               ((intr == LAN80XX_LINE_PMA_RXEI_FILTERED_INTR) ? LAN80XX_M_LINE_PMA_PMA_IRQ_MASK_PMA_RXEI_FILTERED_INT_EN : 0U);
    } else {
        /* HOST PMA */
        mask = ((intr == LAN80XX_HOST_PMA_RESET_DONE_INTR) ?  LAN80XX_M_HOST_PMA_PMA_IRQ_MASK_PMA_RESET_DONE_INT_EN : 0U)    |
               ((intr == LAN80XX_HOST_PMA_RXEI_FILTERED_INTR) ? LAN80XX_M_HOST_PMA_PMA_IRQ_MASK_PMA_RXEI_FILTERED_INT_EN : 0U);
    }
    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_PMA_IRQ_MASK),
                    LAN80XX_HOST_LINE_REG(LAN80XX_F, is_line, PMA_PMA_IRQ_MASK_PMA_RESET_DONE_INT_EN(enable)) |
                    LAN80XX_HOST_LINE_REG(LAN80XX_F, is_line, PMA_PMA_IRQ_MASK_PMA_RXEI_FILTERED_INT_EN(enable)),
                    mask);
    /* Clear the Interrupt */
    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_PMA_IRQ_VEC), mask, mask);

    if (is_line == 1U) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN(0U),
                        LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_LPMA_INTR_EN(enable),
                        LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_LPMA_INTR_EN);
    } else {
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_INTR_CTRL_HOST_INTR_EN(0U),
                        LAN80XX_F_HOST_INTR_CTRL_HOST_INTR_EN_HPMA_INTR_EN(enable),
                        LAN80XX_M_HOST_INTR_CTRL_HOST_INTR_EN_HPMA_INTR_EN);
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_mac_nm_event_poll(mepa_device_t         *dev,
                                         const mepa_port_no_t  port_no,
                                         u64                   intr,
                                         mepa_bool_t           is_line,
                                         phy25g_ext_events_t   *const evt)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0, val = 0;
    ioreg_blk *io_reg;
    if (is_line == 1U) {
        mask = ((intr == LAN80XX_LINE_MAC_MM_PRMPT_UNEXP_TX_PFRM_INTR) ?  LAN80XX_M_LINE_MAC_LINE_MAC_MM_STATUS_UNEXP_TX_PFRM_STICKY : 0U) |
               ((intr == LAN80XX_LINE_MAC_MM_PRMPT_UNEXP_RX_PFRM_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MM_STATUS_UNEXP_RX_PFRM_STICKY : 0U) |
               ((intr == LAN80XX_LINE_MAC_MM_PRMPT_ACTIVE_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MM_STATUS_PRMPT_ACTIVE_STICKY : 0U);

        io_reg = LAN80XX_LINE_MAC_LINE_MAC_MM_STATUS;
    } else {
        mask = ((intr == LAN80XX_HOST_MAC_MM_PRMPT_UNEXP_TX_PFRM_INTR) ?  LAN80XX_M_HOST_MAC_HOST_MAC_MM_STATUS_UNEXP_TX_PFRM_STICKY : 0U) |
               ((intr == LAN80XX_HOST_MAC_MM_PRMPT_UNEXP_RX_PFRM_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MM_STATUS_UNEXP_RX_PFRM_STICKY : 0U) |
               ((intr == LAN80XX_HOST_MAC_MM_PRMPT_ACTIVE_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MM_STATUS_PRMPT_ACTIVE_STICKY : 0U);

        io_reg = LAN80XX_HOST_MAC_HOST_MAC_MM_STATUS;
    }
    LAN80XX_CSR_RD(dev, port_no, io_reg, &val);
    if ((val & mask) == 0U) {
        return MEPA_RC_OK;
    }
    *evt = (*evt | intr);
    LAN80XX_CSR_WRM(port_no, io_reg, mask, mask);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_mac_nm_event_conf(mepa_device_t         *dev,
                                         const mepa_port_no_t  port_no,
                                         u64                   intr,
                                         mepa_bool_t           is_host,
                                         mepa_bool_t           enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0, sticky = 0;

    if (is_host == 0U) {
        /* LINE MM MAC */
        mask = ((intr == LAN80XX_LINE_MAC_MM_PRMPT_UNEXP_TX_PFRM_INTR) ?  LAN80XX_M_LINE_MAC_LINE_MAC_MM_STATUS_UNEXP_TX_PFRM_STICKY_MASK : 0U) |
               ((intr == LAN80XX_LINE_MAC_MM_PRMPT_UNEXP_RX_PFRM_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MM_STATUS_UNEXP_RX_PFRM_STICKY_MASK : 0U) |
               ((intr == LAN80XX_LINE_MAC_MM_PRMPT_ACTIVE_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MM_STATUS_PRMPT_ACTIVE_STICKY_MASK : 0U);

        sticky = ((intr == LAN80XX_LINE_MAC_MM_PRMPT_UNEXP_TX_PFRM_INTR) ?  LAN80XX_M_LINE_MAC_LINE_MAC_MM_STATUS_UNEXP_TX_PFRM_STICKY : 0U) |
                 ((intr == LAN80XX_LINE_MAC_MM_PRMPT_UNEXP_RX_PFRM_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MM_STATUS_UNEXP_RX_PFRM_STICKY : 0U) |
                 ((intr == LAN80XX_LINE_MAC_MM_PRMPT_ACTIVE_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MM_STATUS_PRMPT_ACTIVE_STICKY : 0U);

    } else {
        /* HOST MM MAC */
        mask = ((intr == LAN80XX_HOST_MAC_MM_PRMPT_UNEXP_TX_PFRM_INTR) ?  LAN80XX_M_HOST_MAC_HOST_MAC_MM_STATUS_UNEXP_TX_PFRM_STICKY_MASK : 0U)    |
               ((intr == LAN80XX_HOST_MAC_MM_PRMPT_UNEXP_RX_PFRM_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MM_STATUS_UNEXP_RX_PFRM_STICKY_MASK : 0U) |
               ((intr == LAN80XX_HOST_MAC_MM_PRMPT_ACTIVE_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MM_STATUS_PRMPT_ACTIVE_STICKY_MASK : 0U);

        sticky = ((intr == LAN80XX_HOST_MAC_MM_PRMPT_UNEXP_TX_PFRM_INTR) ?  LAN80XX_M_HOST_MAC_HOST_MAC_MM_STATUS_UNEXP_TX_PFRM_STICKY : 0U) |
                 ((intr == LAN80XX_HOST_MAC_MM_PRMPT_UNEXP_RX_PFRM_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MM_STATUS_UNEXP_RX_PFRM_STICKY : 0U) |
                 ((intr == LAN80XX_HOST_MAC_MM_PRMPT_ACTIVE_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MM_STATUS_PRMPT_ACTIVE_STICKY : 0U);
    }
    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, MM_STATUS),
                    LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX_F, is_host, MM_STATUS_UNEXP_TX_PFRM_STICKY_MASK(enable)) |
                    LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX_F, is_host, MM_STATUS_UNEXP_RX_PFRM_STICKY_MASK(enable)) |
                    LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX_F, is_host, MM_STATUS_PRMPT_ACTIVE_STICKY_MASK(enable)),
                    mask);

    /* Clear the Interrupt */
    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, MM_STATUS), sticky, sticky);

    if (is_host == 0U) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN(0U),
                        LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_LMAC_INTR_EN(enable),
                        LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_LMAC_INTR_EN);
    } else {
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_INTR_CTRL_HOST_INTR_EN(0U),
                        LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_HMAC_INTR_EN(enable),
                        LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_HMAC_INTR_EN);
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_pmac_block_event_poll(mepa_device_t         *dev,
                                             const mepa_port_no_t  port_no,
                                             u64                   intr,
                                             mepa_bool_t           is_line,
                                             phy25g_ext_events_t   *const evt)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0, val = 0;
    ioreg_blk *io_reg;
    if (is_line == 1U) {
        /* LINE P-MAC */
        mask = ((intr == LAN80XX_LINE_PMAC_RX_PREAMBLE_SHRINK) ?  LAN80XX_M_LINE_MAC_LINE_MAC_PMAC_STICKY_PMAC_RX_PREAM_SHRINK_STICKY : 0U)    |
               ((intr == LAN80XX_LINE_PMAC_RX_PREAMBLE_MISMATCH) ? LAN80XX_M_LINE_MAC_LINE_MAC_PMAC_STICKY_PMAC_RX_PREAM_MISMATCH_STICKY : 0U) |
               ((intr == LAN80XX_LINE_PMAC_RX_PREAMBLE_ERR) ?  LAN80XX_M_LINE_MAC_LINE_MAC_PMAC_STICKY_PMAC_RX_PREAM_ERR_STICKY : 0U)    |
               ((intr == LAN80XX_LINE_PMAC_RX_NON_STD_PREAMBLE_INTR) ?  LAN80XX_M_LINE_MAC_LINE_MAC_PMAC_STICKY_PMAC_RX_NON_STD_PREAM_STICKY : 0U)    |
               ((intr == LAN80XX_LINE_PMAC_RX_MPLS_MC_INTR) ?  LAN80XX_M_LINE_MAC_LINE_MAC_PMAC_STICKY_PMAC_RX_MPLS_MC_STICKY : 0U)    |
               ((intr == LAN80XX_LINE_PMAC_RX_MPLS_UC_INTR) ?  LAN80XX_M_LINE_MAC_LINE_MAC_PMAC_STICKY_PMAC_RX_MPLS_UC_STICKY : 0U)    |
               ((intr == LAN80XX_LINE_PMAC_TX_UNDERFLOW_INTR) ?  LAN80XX_M_LINE_MAC_LINE_MAC_PMAC_STICKY_PMAC_TX_UFLW_STICKY : 0U)    |
               ((intr == LAN80XX_LINE_PMAC_TX_ABORT_INTR) ?  LAN80XX_M_LINE_MAC_LINE_MAC_PMAC_STICKY_PMAC_TX_ABORT_STICKY : 0U);

        io_reg = LAN80XX_LINE_MAC_LINE_MAC_PMAC_STICKY;
    } else {
        /* HOST P-MAC */
        mask = ((intr == LAN80XX_HOST_PMAC_RX_PREAMBLE_SHRINK) ?  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_PREAM_SHRINK_STICKY : 0U)    |
               ((intr == LAN80XX_HOST_PMAC_RX_PREAMBLE_MISMATCH) ? LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_PREAM_MISMATCH_STICKY : 0U) |
               ((intr == LAN80XX_HOST_PMAC_RX_PREAMBLE_ERR) ?  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_PREAM_ERR_STICKY : 0U)    |
               ((intr == LAN80XX_HOST_PMAC_RX_NON_STD_PREAMBLE_INTR) ?  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_NON_STD_PREAM_STICKY : 0U)    |
               ((intr == LAN80XX_HOST_PMAC_RX_MPLS_MC_INTR) ?  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_MPLS_MC_STICKY : 0U)    |
               ((intr == LAN80XX_HOST_PMAC_RX_MPLS_UC_INTR) ?  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_RX_MPLS_UC_STICKY : 0U)    |
               ((intr == LAN80XX_HOST_PMAC_TX_UNDERFLOW_INTR) ?  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_TX_UFLW_STICKY : 0U)    |
               ((intr == LAN80XX_HOST_PMAC_TX_ABORT_INTR) ?  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_STICKY_PMAC_TX_ABORT_STICKY : 0U);

        io_reg = LAN80XX_HOST_MAC_HOST_MAC_PMAC_STICKY;
    }
    LAN80XX_CSR_RD(dev, port_no, io_reg, &val);
    if ((val & mask) == 0U) {
        return MEPA_RC_OK;
    }
    *evt = (*evt | intr);
    LAN80XX_CSR_WRM(port_no, io_reg, mask, mask);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_pmac_block_event_conf(mepa_device_t         *dev,
                                             const mepa_port_no_t  port_no,
                                             u64                   intr,
                                             mepa_bool_t           is_host,
                                             mepa_bool_t           enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0;
    if (is_host == 0U) {
        /* LINE P-MAC */
        mask = ((intr == LAN80XX_LINE_PMAC_RX_PREAMBLE_SHRINK) ?  LAN80XX_M_LINE_MAC_LINE_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_PREAM_SHRINK_STICKY_MASK : 0U)    |
               ((intr == LAN80XX_LINE_PMAC_RX_PREAMBLE_MISMATCH) ? LAN80XX_M_LINE_MAC_LINE_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_PREAM_MISMATCH_STICKY_MASK : 0U) |
               ((intr == LAN80XX_LINE_PMAC_RX_PREAMBLE_ERR) ?  LAN80XX_M_LINE_MAC_LINE_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_PREAM_ERR_STICKY_MASK : 0U)    |
               ((intr == LAN80XX_LINE_PMAC_RX_NON_STD_PREAMBLE_INTR) ?  LAN80XX_M_LINE_MAC_LINE_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_NON_STD_PREAM_STICKY_MASK : 0U)    |
               ((intr == LAN80XX_LINE_PMAC_RX_MPLS_MC_INTR) ?  LAN80XX_M_LINE_MAC_LINE_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_MPLS_MC_STICKY_MASK : 0U)    |
               ((intr == LAN80XX_LINE_PMAC_RX_MPLS_UC_INTR) ?  LAN80XX_M_LINE_MAC_LINE_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_MPLS_UC_STICKY_MASK : 0U)    |
               ((intr == LAN80XX_LINE_PMAC_TX_UNDERFLOW_INTR) ?  LAN80XX_M_LINE_MAC_LINE_MAC_PMAC_MAC_STICKY_MASK_PMAC_TX_UFLW_STICKY_MASK : 0U)    |
               ((intr == LAN80XX_LINE_PMAC_TX_ABORT_INTR) ?  LAN80XX_M_LINE_MAC_LINE_MAC_PMAC_MAC_STICKY_MASK_PMAC_TX_ABORT_STICKY_MASK : 0U);
    } else {
        /* HOST P-MAC */
        mask = ((intr == LAN80XX_HOST_PMAC_RX_PREAMBLE_SHRINK) ?  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_PREAM_SHRINK_STICKY_MASK : 0U)    |
               ((intr == LAN80XX_HOST_PMAC_RX_PREAMBLE_MISMATCH) ? LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_PREAM_MISMATCH_STICKY_MASK : 0U) |
               ((intr == LAN80XX_HOST_PMAC_RX_PREAMBLE_ERR) ?  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_PREAM_ERR_STICKY_MASK : 0U)    |
               ((intr == LAN80XX_HOST_PMAC_RX_NON_STD_PREAMBLE_INTR) ?  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_NON_STD_PREAM_STICKY_MASK : 0U)    |
               ((intr == LAN80XX_HOST_PMAC_RX_MPLS_MC_INTR) ?  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_MPLS_MC_STICKY_MASK : 0U)    |
               ((intr == LAN80XX_HOST_PMAC_RX_MPLS_UC_INTR) ?  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_RX_MPLS_UC_STICKY_MASK : 0U)    |
               ((intr == LAN80XX_HOST_PMAC_TX_UNDERFLOW_INTR) ?  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_TX_UFLW_STICKY_MASK : 0U)    |
               ((intr == LAN80XX_HOST_PMAC_TX_ABORT_INTR) ?  LAN80XX_M_HOST_MAC_HOST_MAC_PMAC_MAC_STICKY_MASK_PMAC_TX_ABORT_STICKY_MASK : 0U);
    }
    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_MAC_STICKY_MASK),
                    LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX_F, is_host, PMAC_MAC_STICKY_MASK_PMAC_RX_PREAM_SHRINK_STICKY_MASK(enable)) |
                    LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX_F, is_host, PMAC_MAC_STICKY_MASK_PMAC_RX_PREAM_MISMATCH_STICKY_MASK(enable)) |
                    LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX_F, is_host, PMAC_MAC_STICKY_MASK_PMAC_RX_PREAM_ERR_STICKY_MASK(enable)) |
                    LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX_F, is_host, PMAC_MAC_STICKY_MASK_PMAC_RX_NON_STD_PREAM_STICKY_MASK(enable)) |
                    LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX_F, is_host, PMAC_MAC_STICKY_MASK_PMAC_RX_MPLS_MC_STICKY_MASK(enable)) |
                    LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX_F, is_host, PMAC_MAC_STICKY_MASK_PMAC_RX_MPLS_UC_STICKY_MASK(enable)) |
                    LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX_F, is_host, PMAC_MAC_STICKY_MASK_PMAC_TX_UFLW_STICKY_MASK(enable)) |
                    LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX_F, is_host, PMAC_MAC_STICKY_MASK_PMAC_TX_ABORT_STICKY_MASK(enable)),
                    mask);

    /* Clear the Interrupt */
    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_STICKY), mask, mask);

    if (is_host == 0U) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN(0U),
                        LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_LMAC_INTR_EN(enable),
                        LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_LMAC_INTR_EN);
    } else {
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_INTR_CTRL_HOST_INTR_EN(0U),
                        LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_HMAC_INTR_EN(enable),
                        LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_HMAC_INTR_EN);
    }

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_xconnect_ext_event_conf(mepa_device_t         *dev,
                                               const mepa_port_no_t  port_no,
                                               u64                   intr,
                                               mepa_bool_t           is_intr2,
                                               mepa_bool_t           enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0;

    if (is_intr2 == 1U) {
        /* Crossconnect INTR */
        mask = ((intr == LAN80XX_WPS1_FC_ACK_TIMER_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR2_WPS1_FC_ACK_TIMER_STICKY : 0U) |
               ((intr == LAN80XX_WPS0_FC_ACK_TIMER_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR2_WPS0_FC_ACK_TIMER_STICKY : 0U) |
               ((intr == LAN80XX_WPS1_CONN_FAULT_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR2_WPS1_CONN_FAULT_STICKY : 0U) |
               ((intr == LAN80XX_WPS0_CONN_FAULT_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR2_WPS0_CONN_FAULT_STICKY : 0U) |
               ((intr == LAN80XX_WPS1_FAILOVER_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR2_WPS1_FAILOVER_STICKY : 0U) |
               ((intr == LAN80XX_WPS0_FAILOVER_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR2_WPS0_FAILOVER_STICKY : 0U);

        LAN80XX_CSR_WRM(port_no, LAN80XX_CROSS_CONNECT_INTR_EN2,
                        LAN80XX_F_CROSS_CONNECT_INTR_EN2_WPS1_FC_ACK_TIMER_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN2_WPS0_FC_ACK_TIMER_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN2_WPS1_CONN_FAULT_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN2_WPS0_CONN_FAULT_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN2_WPS1_FAILOVER_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN2_WPS0_FAILOVER_INTR_EN(enable),
                        mask);

        /* Clear the Interrupt */
        LAN80XX_CSR_WRM(port_no, LAN80XX_CROSS_CONNECT_INTR2, mask, mask);
    } else {
        /* Crossconnect INTR */
        mask = ((intr == LAN80XX_H0_SWITCH_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H0_SWITCH_STICKY : 0U) |
               ((intr == LAN80XX_H1_SWITCH_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H1_SWITCH_STICKY : 0U) |
               ((intr == LAN80XX_H2_SWITCH_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H2_SWITCH_STICKY : 0U) |
               ((intr == LAN80XX_H3_SWITCH_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H3_SWITCH_STICKY : 0U) |
               ((intr == LAN80XX_L0_SWITCH_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L0_SWITCH_STICKY : 0U) |
               ((intr == LAN80XX_L1_SWITCH_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L1_SWITCH_STICKY : 0U) |
               ((intr == LAN80XX_L2_SWITCH_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L2_SWITCH_STICKY : 0U) |
               ((intr == LAN80XX_L3_SWITCH_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L3_SWITCH_STICKY : 0U) |
               ((intr == LAN80XX_H0_COND_ALT_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H0_COND_ALT_DET_STICKY : 0U) |
               ((intr == LAN80XX_H1_COND_ALT_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H1_COND_ALT_DET_STICKY : 0U) |
               ((intr == LAN80XX_H2_COND_ALT_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H2_COND_ALT_DET_STICKY : 0U) |
               ((intr == LAN80XX_H3_COND_ALT_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H3_COND_ALT_DET_STICKY : 0U) |
               ((intr == LAN80XX_L0_COND_ALT_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L0_COND_ALT_DET_STICKY : 0U) |
               ((intr == LAN80XX_L1_COND_ALT_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L1_COND_ALT_DET_STICKY : 0U) |
               ((intr == LAN80XX_L2_COND_ALT_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L2_COND_ALT_DET_STICKY : 0U) |
               ((intr == LAN80XX_L3_COND_ALT_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L3_COND_ALT_DET_STICKY : 0U) |
               ((intr == LAN80XX_H0_COND_ALT_UNF_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H0_COND_ALT_UNF_DET_STICKY : 0U) |
               ((intr == LAN80XX_H1_COND_ALT_UNF_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H1_COND_ALT_UNF_DET_STICKY : 0U) |
               ((intr == LAN80XX_H2_COND_ALT_UNF_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H2_COND_ALT_UNF_DET_STICKY : 0U) |
               ((intr == LAN80XX_H3_COND_ALT_UNF_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H3_COND_ALT_UNF_DET_STICKY : 0U) |
               ((intr == LAN80XX_L0_COND_ALT_UNF_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L0_COND_ALT_UNF_DET_STICKY : 0U) |
               ((intr == LAN80XX_L1_COND_ALT_UNF_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L1_COND_ALT_UNF_DET_STICKY : 0U) |
               ((intr == LAN80XX_L2_COND_ALT_UNF_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L2_COND_ALT_UNF_DET_STICKY : 0U) |
               ((intr == LAN80XX_L3_COND_ALT_UNF_DET_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L3_COND_ALT_UNF_DET_STICKY : 0U) |
               ((intr == LAN80XX_H0_FIFO_ERROR_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H0_FIFO_ERROR_STICKY : 0U) |
               ((intr == LAN80XX_H1_FIFO_ERROR_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H1_FIFO_ERROR_STICKY : 0U) |
               ((intr == LAN80XX_H2_FIFO_ERROR_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H2_FIFO_ERROR_STICKY : 0U) |
               ((intr == LAN80XX_H3_FIFO_ERROR_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_H3_FIFO_ERROR_STICKY : 0U) |
               ((intr == LAN80XX_L0_FIFO_ERROR_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L0_FIFO_ERROR_STICKY : 0U) |
               ((intr == LAN80XX_L1_FIFO_ERROR_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L1_FIFO_ERROR_STICKY : 0U) |
               ((intr == LAN80XX_L2_FIFO_ERROR_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L2_FIFO_ERROR_STICKY : 0U) |
               ((intr == LAN80XX_L3_FIFO_ERROR_INTR) ? LAN80XX_M_CROSS_CONNECT_INTR_L3_FIFO_ERROR_STICKY : 0U);

        LAN80XX_CSR_WRM(port_no, LAN80XX_CROSS_CONNECT_INTR_EN,
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_H0_SWITCH_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_H1_SWITCH_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_H2_SWITCH_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_H3_SWITCH_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_L0_SWITCH_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_L1_SWITCH_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_L2_SWITCH_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_L3_SWITCH_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_H0_COND_ALT_DET_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_H1_COND_ALT_DET_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_H2_COND_ALT_DET_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_H3_COND_ALT_DET_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_L0_COND_ALT_DET_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_L1_COND_ALT_DET_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_L2_COND_ALT_DET_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_L3_COND_ALT_DET_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_H0_COND_ALT_UNF_DET_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_H1_COND_ALT_UNF_DET_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_H2_COND_ALT_UNF_DET_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_H3_COND_ALT_UNF_DET_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_L0_COND_ALT_UNF_DET_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_L1_COND_ALT_UNF_DET_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_L2_COND_ALT_UNF_DET_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_L3_COND_ALT_UNF_DET_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_H0_FIFO_ERROR_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_H1_FIFO_ERROR_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_H2_FIFO_ERROR_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_H3_FIFO_ERROR_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_L0_FIFO_ERROR_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_L1_FIFO_ERROR_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_L2_FIFO_ERROR_INTR_EN(enable) |
                        LAN80XX_F_CROSS_CONNECT_INTR_EN_L3_FIFO_ERROR_INTR_EN(enable),
                        mask);

        /* Clear the Interrupt */
        LAN80XX_CSR_WRM(port_no, LAN80XX_CROSS_CONNECT_INTR, mask, mask);
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_1g_pcs_event_conf(mepa_device_t         *dev,
                                         const mepa_port_no_t  port_no,
                                         u64                   intr,
                                         mepa_bool_t           is_line,
                                         mepa_bool_t           enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0;

    if (is_line == 1U) {
        /* LINE PCS 1G */
        mask = ((intr == LAN80XX_LINE_PCS1G_LINK_DOWN_INTR) ? LAN80XX_M_LINE_PCS_CFG_PCS1G_STICKY_MASK_LINK_DOWN_STICKY_INTR_EN : 0U)    |
               ((intr == LAN80XX_LINE_PCS1G_OUT_OF_SYNC_INTR) ? LAN80XX_M_LINE_PCS_CFG_PCS1G_STICKY_MASK_OUT_OF_SYNC_STICKY_INTR_EN : 0U);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS_CFG_PCS1G_STICKY_MASK,
                        LAN80XX_F_LINE_PCS_CFG_PCS1G_STICKY_MASK_LINK_DOWN_STICKY_INTR_EN(enable) |
                        LAN80XX_F_LINE_PCS_CFG_PCS1G_STICKY_MASK_OUT_OF_SYNC_STICKY_INTR_EN(enable),
                        mask);


        mask = ((intr == LAN80XX_LINE_PCS1G_LINK_DOWN_INTR) ? LAN80XX_M_LINE_PCS_CFG_PCS1G_STICKY_LINK_DOWN_STICKY : LAN80XX_M_LINE_PCS_CFG_PCS1G_STICKY_OUT_OF_SYNC_STICKY);

        /* Clear the Interrupt */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS_CFG_PCS1G_STICKY, mask, mask);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN(0U),
                        LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_LPCS1G_INTR_EN(enable),
                        LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_LPCS1G_INTR_EN);
        return MEPA_RC_OK;
    }

    /* HOST PCS1G */
    mask = ((intr == LAN80XX_HOST_PCS1G_LINK_DOWN_INTR) ? LAN80XX_M_HOST_PCS_CFG_PCS1G_STICKY_MASK_LINK_DOWN_STICKY_INTR_EN : 0U) |
           ((intr == LAN80XX_HOST_PCS1G_OUT_OF_SYNC_INTR) ?  LAN80XX_M_HOST_PCS_CFG_PCS1G_STICKY_MASK_OUT_OF_SYNC_STICKY_INTR_EN : 0U);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS_CFG_PCS1G_STICKY_MASK,
                    LAN80XX_F_HOST_PCS_CFG_PCS1G_STICKY_MASK_LINK_DOWN_STICKY_INTR_EN(enable) |
                    LAN80XX_F_HOST_PCS_CFG_PCS1G_STICKY_MASK_OUT_OF_SYNC_STICKY_INTR_EN(enable),
                    mask);

    mask = ((intr == LAN80XX_HOST_PCS1G_LINK_DOWN_INTR) ? LAN80XX_M_HOST_PCS_CFG_PCS1G_STICKY_LINK_DOWN_STICKY : LAN80XX_M_HOST_PCS_CFG_PCS1G_STICKY_OUT_OF_SYNC_STICKY);
    /* Clear the Interrupt */
    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS_CFG_PCS1G_STICKY, mask, mask);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_INTR_CTRL_HOST_INTR_EN(0U),
                    LAN80XX_F_HOST_INTR_CTRL_HOST_INTR_EN_HPCS1G_INTR_EN(enable),
                    LAN80XX_M_HOST_INTR_CTRL_HOST_INTR_EN_HPCS1G_INTR_EN);

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_25g_pcs_event_poll(mepa_device_t         *dev,
                                          const mepa_port_no_t  port_no,
                                          u64                   intr,
                                          mepa_bool_t           is_line,
                                          phy25g_events_t       *const evt)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0, val = 0;
    ioreg_blk *io_reg;

    if (is_line == 1U) {
        mask = (((intr == LAN80XX_LINE_PCS25G_ALIGN_DONE_INTR) ? LAN80XX_M_LINE_PCS_CFG_PCS25G_STICKY_SIG_ALIGN_DONE_STICKY : 0U) |
                ((intr  == LAN80XX_LINE_PCS25G_BLOCK_LOCK_INTR) ? LAN80XX_M_LINE_PCS_CFG_PCS25G_STICKY_SIG_BLOCK_LOCK_STICKY : 0U) |
                ((intr  == LAN80XX_LINE_PCS25G_HI_BER_INTR) ? LAN80XX_M_LINE_PCS_CFG_PCS25G_STICKY_SIG_HI_BER_STICKY  : 0U));

        io_reg = LAN80XX_LINE_PCS_CFG_PCS25G_STICKY_SIG;
    } else {
        mask = (((intr == LAN80XX_HOST_PCS25G_ALIGN_DONE_INTR) ? LAN80XX_M_HOST_PCS_CFG_PCS25G_STICKY_SIG_ALIGN_DONE_STICKY : 0U) |
                ((intr  == LAN80XX_HOST_PCS25G_BLOCK_LOCK_INTR) ? LAN80XX_M_HOST_PCS_CFG_PCS25G_STICKY_SIG_BLOCK_LOCK_STICKY : 0U) |
                ((intr  == LAN80XX_HOST_PCS25G_HI_BER_INTR) ? LAN80XX_M_HOST_PCS_CFG_PCS25G_STICKY_SIG_HI_BER_STICKY : 0U));

        io_reg = LAN80XX_HOST_PCS_CFG_PCS25G_STICKY_SIG;
    }
    LAN80XX_CSR_RD(dev, port_no, io_reg, &val);
    if ((val & mask) == 0U) {
        return MEPA_RC_OK;
    }
    *evt = (*evt | intr);
    LAN80XX_CSR_WRM(port_no, io_reg, mask, mask);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_25g_pcs_event_conf(mepa_device_t         *dev,
                                          const mepa_port_no_t  port_no,
                                          u64                   intr,
                                          mepa_bool_t           is_line,
                                          mepa_bool_t           enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0;

    if (is_line == 1U) {
        /* Line PCS 25G */
        mask = ((intr == LAN80XX_LINE_PCS25G_ALIGN_DONE_INTR) ? LAN80XX_M_LINE_PCS_CFG_PCS25G_STICKY_SIG_MASK_ALIGN_DONE_STICKY_MASK : 0U) |
               ((intr == LAN80XX_LINE_PCS25G_BLOCK_LOCK_INTR) ? LAN80XX_M_LINE_PCS_CFG_PCS25G_STICKY_SIG_MASK_BLOCK_LOCK_STICKY_MASK : 0U) |
               ((intr == LAN80XX_LINE_PCS25G_HI_BER_INTR) ? LAN80XX_M_LINE_PCS_CFG_PCS25G_STICKY_SIG_MASK_HI_BER_STICKY_MASK : 0U);

        LAN80XX_CSR_EVENT_WRM(port_no, LAN80XX_LINE_PCS_CFG_PCS25G_STICKY_SIG_MASK, LAN80XX_LINE_PCS_CFG_PCS25G_STICKY_SIG,
                              LAN80XX_F_LINE_PCS_CFG_PCS25G_STICKY_SIG_MASK_ALIGN_DONE_STICKY_MASK(enable) |
                              LAN80XX_F_LINE_PCS_CFG_PCS25G_STICKY_SIG_MASK_BLOCK_LOCK_STICKY_MASK(enable) |
                              LAN80XX_F_LINE_PCS_CFG_PCS25G_STICKY_SIG_MASK_HI_BER_STICKY_MASK(enable),
                              mask);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN(0U),
                        LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_LPCS25G_INTR_EN(enable),
                        LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_LPCS25G_INTR_EN);

        return MEPA_RC_OK;
    }
    /* HOST PCS 25G */
    mask = ((intr == LAN80XX_HOST_PCS25G_ALIGN_DONE_INTR) ? LAN80XX_M_HOST_PCS_CFG_PCS25G_STICKY_SIG_MASK_ALIGN_DONE_STICKY_MASK : 0U) |
           ((intr == LAN80XX_HOST_PCS25G_BLOCK_LOCK_INTR) ? LAN80XX_M_HOST_PCS_CFG_PCS25G_STICKY_SIG_MASK_BLOCK_LOCK_STICKY_MASK : 0U) |
           ((intr == LAN80XX_HOST_PCS25G_HI_BER_INTR) ? LAN80XX_M_HOST_PCS_CFG_PCS25G_STICKY_SIG_MASK_HI_BER_STICKY_MASK : 0U);

    LAN80XX_CSR_EVENT_WRM(port_no, LAN80XX_HOST_PCS_CFG_PCS25G_STICKY_SIG_MASK, LAN80XX_HOST_PCS_CFG_PCS25G_STICKY_SIG,
                          LAN80XX_F_HOST_PCS_CFG_PCS25G_STICKY_SIG_MASK_ALIGN_DONE_STICKY_MASK(enable) |
                          LAN80XX_F_HOST_PCS_CFG_PCS25G_STICKY_SIG_MASK_BLOCK_LOCK_STICKY_MASK(enable) |
                          LAN80XX_F_HOST_PCS_CFG_PCS25G_STICKY_SIG_MASK_HI_BER_STICKY_MASK(enable),
                          mask);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_INTR_CTRL_HOST_INTR_EN(0U),
                    LAN80XX_F_HOST_INTR_CTRL_HOST_INTR_EN_HPCS25G_INTR_EN(enable),
                    LAN80XX_M_HOST_INTR_CTRL_HOST_INTR_EN_HPCS25G_INTR_EN);

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_mac_event_poll(mepa_device_t         *dev,
                                      const mepa_port_no_t  port_no,
                                      u64                   intr,
                                      mepa_bool_t           is_line,
                                      phy25g_events_t       *const evt)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0, val = 0;
    ioreg_blk *io_reg;

    if (is_line == 1U) {
        mask = (((intr == LAN80XX_LINE_MAC_TX_ABORT_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_STICKY_TX_ABORT_STICKY : 0U)     |
                ((intr == LAN80XX_LINE_MAC_TX_UNDERFLOW_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_STICKY_TX_UFLW_STICKY : 0U)   |
                ((intr == LAN80XX_LINE_MAC_RX_TAG_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_STICKY_RX_TAG_STICKY : 0U)          |
                ((intr == LAN80XX_LINE_MAC_RX_MPLS_UC_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_STICKY_RX_MPLS_UC_STICKY : 0U)  |
                ((intr == LAN80XX_LINE_MAC_RX_MPLS_MC_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_STICKY_RX_MPLS_MC_STICKY : 0U)  |
                ((intr == LAN80XX_LINE_MAC_RX_NON_STD_PREAMBLE_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_STICKY_RX_NON_STD_PREAM_STICKY : 0U)   |
                ((intr == LAN80XX_LINE_MAC_RX_PREAM_ERR_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_STICKY_RX_PREAM_ERR_STICKY : 0U)              |
                ((intr == LAN80XX_LINE_MAC_RX_PREAMBLE_MISMATCH_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_STICKY_RX_PREAM_MISMATCH_STICKY : 0U) |
                ((intr == LAN80XX_LINE_MAC_RX_PREAMBLE_SHRINK_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_STICKY_RX_PREAM_SHRINK_STICKY : 0U)     |
                ((intr == LAN80XX_LINE_MAC_RX_IPG_SHRINK_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_STICKY_RX_IPG_SHRINK_STICKY : 0U));

        io_reg = LAN80XX_LINE_MAC_LINE_MAC_MAC_STICKY;
    } else {
        mask = (((intr == LAN80XX_HOST_MAC_TX_ABORT_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_TX_ABORT_STICKY : 0U)       |
                ((intr == LAN80XX_HOST_MAC_TX_UNDERFLOW_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_TX_UFLW_STICKY : 0U)    |
                ((intr == LAN80XX_HOST_MAC_RX_TAG_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_RX_TAG_STICKY : 0U)           |
                ((intr == LAN80XX_HOST_MAC_RX_MPLS_UC_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_RX_MPLS_UC_STICKY : 0U)   |
                ((intr == LAN80XX_HOST_MAC_RX_MPLS_MC_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_RX_MPLS_MC_STICKY : 0U)   |
                ((intr == LAN80XX_HOST_MAC_RX_NON_STD_PREAMBLE_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_RX_NON_STD_PREAM_STICKY : 0U)   |
                ((intr == LAN80XX_HOST_MAC_RX_PREAM_ERR_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_RX_PREAM_ERR_STICKY : 0U)              |
                ((intr == LAN80XX_HOST_MAC_RX_PREAMBLE_MISMATCH_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_RX_PREAM_MISMATCH_STICKY : 0U) |
                ((intr == LAN80XX_HOST_MAC_RX_PREAMBLE_SHRINK_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_RX_PREAM_SHRINK_STICKY : 0U)     |
                ((intr == LAN80XX_HOST_MAC_RX_IPG_SHRINK_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_RX_IPG_SHRINK_STICKY : 0U));

        io_reg =  LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY;
    }
    LAN80XX_CSR_RD(dev, port_no, io_reg, &val);
    if ((val & mask) == 0U) {
        return MEPA_RC_OK;
    }
    *evt = (*evt | intr);
    LAN80XX_CSR_WRM(port_no, io_reg, mask, mask);
    return MEPA_RC_OK;
}


static mepa_rc lan80xx_mac_event_conf(mepa_device_t         *dev,
                                      const mepa_port_no_t  port_no,
                                      u64                   intr,
                                      mepa_bool_t           is_line,
                                      mepa_bool_t           enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0;

    if (is_line == 1U) {
        /* LINE MAC Interrupts */
        mask = ((intr == LAN80XX_LINE_MAC_TX_ABORT_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_STICKY_MASK_TX_ABORT_STICKY_MASK : 0U)         |
               ((intr == LAN80XX_LINE_MAC_TX_UNDERFLOW_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_STICKY_MASK_TX_UFLW_STICKY_MASK : 0U)      |
               ((intr == LAN80XX_LINE_MAC_RX_TAG_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_STICKY_MASK_RX_TAG_STICKY_MASK : 0U)             |
               ((intr == LAN80XX_LINE_MAC_RX_MPLS_UC_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_STICKY_MASK_RX_MPLS_UC_STICKY_MASK : 0U)     |
               ((intr == LAN80XX_LINE_MAC_RX_MPLS_MC_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_STICKY_MASK_RX_MPLS_MC_STICKY_MASK : 0U)     |
               ((intr == LAN80XX_LINE_MAC_RX_NON_STD_PREAMBLE_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_STICKY_MASK_RX_NON_STD_PREAM_STICKY_MASK : 0U)   |
               ((intr == LAN80XX_LINE_MAC_RX_PREAM_ERR_INTR) ?  LAN80XX_M_LINE_MAC_LINE_MAC_MAC_STICKY_MASK_RX_PREAM_ERR_STICKY_MASK : 0U)             |
               ((intr == LAN80XX_LINE_MAC_RX_PREAMBLE_MISMATCH_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_STICKY_MASK_RX_PREAM_MISMATCH_STICKY_MASK : 0U) |
               ((intr == LAN80XX_LINE_MAC_RX_PREAMBLE_SHRINK_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_STICKY_MASK_RX_PREAM_SHRINK_STICKY_MASK : 0U)     |
               ((intr == LAN80XX_LINE_MAC_RX_IPG_SHRINK_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_STICKY_MASK_RX_IPG_SHRINK_STICKY_MASK : 0U);

        LAN80XX_CSR_EVENT_WRM(port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_STICKY_MASK, LAN80XX_LINE_MAC_LINE_MAC_MAC_STICKY,
                              LAN80XX_F_LINE_MAC_LINE_MAC_MAC_STICKY_MASK_TX_ABORT_STICKY_MASK(enable) |
                              LAN80XX_F_LINE_MAC_LINE_MAC_MAC_STICKY_MASK_TX_UFLW_STICKY_MASK(enable)  |
                              LAN80XX_F_LINE_MAC_LINE_MAC_MAC_STICKY_MASK_RX_TAG_STICKY_MASK(enable) |
                              LAN80XX_F_LINE_MAC_LINE_MAC_MAC_STICKY_MASK_RX_MPLS_UC_STICKY_MASK(enable) |
                              LAN80XX_F_LINE_MAC_LINE_MAC_MAC_STICKY_MASK_RX_MPLS_MC_STICKY_MASK(enable) |
                              LAN80XX_F_LINE_MAC_LINE_MAC_MAC_STICKY_MASK_RX_NON_STD_PREAM_STICKY_MASK(enable) |
                              LAN80XX_F_LINE_MAC_LINE_MAC_MAC_STICKY_MASK_RX_PREAM_ERR_STICKY_MASK(enable) |
                              LAN80XX_F_LINE_MAC_LINE_MAC_MAC_STICKY_MASK_RX_PREAM_MISMATCH_STICKY_MASK(enable) |
                              LAN80XX_F_LINE_MAC_LINE_MAC_MAC_STICKY_MASK_RX_PREAM_SHRINK_STICKY_MASK(enable) |
                              LAN80XX_F_LINE_MAC_LINE_MAC_MAC_STICKY_MASK_RX_IPG_SHRINK_STICKY_MASK(enable),
                              mask);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN(0U),
                        LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_LMAC_INTR_EN(enable),
                        LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_LMAC_INTR_EN);
        return MEPA_RC_OK;
    }
    /* HOST MAC Interrupts */
    mask = ((intr == LAN80XX_HOST_MAC_TX_ABORT_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_TX_ABORT_STICKY_MASK : 0U)         |
           ((intr == LAN80XX_HOST_MAC_TX_UNDERFLOW_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_TX_UFLW_STICKY_MASK : 0U)      |
           ((intr == LAN80XX_HOST_MAC_RX_TAG_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_TAG_STICKY_MASK : 0U)             |
           ((intr == LAN80XX_HOST_MAC_RX_MPLS_UC_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_MPLS_UC_STICKY_MASK : 0U)     |
           ((intr == LAN80XX_HOST_MAC_RX_MPLS_MC_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_MPLS_MC_STICKY_MASK : 0U)     |
           ((intr == LAN80XX_HOST_MAC_RX_NON_STD_PREAMBLE_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_NON_STD_PREAM_STICKY_MASK : 0U)   |
           ((intr == LAN80XX_HOST_MAC_RX_PREAM_ERR_INTR) ?  LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_PREAM_ERR_STICKY_MASK : 0U)             |
           ((intr == LAN80XX_HOST_MAC_RX_PREAMBLE_MISMATCH_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_PREAM_MISMATCH_STICKY_MASK : 0U) |
           ((intr == LAN80XX_HOST_MAC_RX_PREAMBLE_SHRINK_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_PREAM_SHRINK_STICKY_MASK : 0U)     |
           ((intr == LAN80XX_HOST_MAC_RX_IPG_SHRINK_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_IPG_SHRINK_STICKY_MASK : 0U);

    /* HOST MAC Interrupts */
    LAN80XX_CSR_EVENT_WRM(port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY_MASK, LAN80XX_HOST_MAC_HOST_MAC_MAC_STICKY,
                          LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_TX_ABORT_STICKY_MASK(enable) |
                          LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_TX_UFLW_STICKY_MASK(enable)  |
                          LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_TAG_STICKY_MASK(enable) |
                          LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_MPLS_UC_STICKY_MASK(enable) |
                          LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_MPLS_MC_STICKY_MASK(enable) |
                          LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_NON_STD_PREAM_STICKY_MASK(enable) |
                          LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_PREAM_ERR_STICKY_MASK(enable) |
                          LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_PREAM_MISMATCH_STICKY_MASK(enable) |
                          LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_PREAM_SHRINK_STICKY_MASK(enable) |
                          LAN80XX_F_HOST_MAC_HOST_MAC_MAC_STICKY_MASK_RX_IPG_SHRINK_STICKY_MASK(enable),
                          mask);

    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN(0U),
                    LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_HMAC_INTR_EN(enable),
                    LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_HMAC_INTR_EN);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_mac_tx_monitor_event_poll(mepa_device_t         *dev,
                                                 const mepa_port_no_t  port_no,
                                                 u64                   intr,
                                                 mepa_bool_t           is_line,
                                                 phy25g_events_t       *const evt)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0, val = 0;
    ioreg_blk *io_reg;

    if (is_line == 1U) {
        mask = ((intr == LAN80XX_LINE_MAC_DIS_STATE_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_TX_MONITOR_STICKY_DIS_STATE_STICKY : 0U)       |
               ((intr == LAN80XX_LINE_MAC_IDLE_STATE_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY : 0U)     |
               ((intr == LAN80XX_LINE_MAC_REMOTE_ERR_STATE_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_TX_MONITOR_STICKY_REMOTE_ERR_STATE_STICKY : 0U) |
               ((intr == LAN80XX_LINE_MAC_LOCAL_ERR_STATE_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_TX_MONITOR_STICKY_LOCAL_ERR_STATE_STICKY : 0U);

        io_reg = LAN80XX_LINE_MAC_LINE_MAC_MAC_TX_MONITOR_STICKY;
    } else {
        mask = ((intr == LAN80XX_HOST_MAC_DIS_STATE_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_DIS_STATE_STICKY : 0U)       |
               ((intr == LAN80XX_HOST_MAC_IDLE_STATE_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_IDLE_STATE_STICKY : 0U)     |
               ((intr == LAN80XX_HOST_MAC_REMOTE_ERR_STATE_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_REMOTE_ERR_STATE_STICKY : 0U) |
               ((intr == LAN80XX_HOST_MAC_LOCAL_ERR_STATE_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_LOCAL_ERR_STATE_STICKY : 0U);
        io_reg = LAN80XX_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY;
    }
    LAN80XX_CSR_RD(dev, port_no, io_reg, &val);
    if ((val & mask) == 0U) {
        return MEPA_RC_OK;
    }
    *evt = (*evt | intr);
    LAN80XX_CSR_WRM(port_no, io_reg, mask, mask);
    return MEPA_RC_OK;
}


static mepa_rc lan80xx_mac_tx_monitor_event_conf(mepa_device_t         *dev,
                                                 const mepa_port_no_t  port_no,
                                                 u64                   intr,
                                                 mepa_bool_t           is_line,
                                                 mepa_bool_t           enable)

{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0;

    if (is_line == 1U) {

        /* LINE MAC Tx Monitor Interrupts */
        mask = ((intr == LAN80XX_LINE_MAC_DIS_STATE_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_TX_MONITOR_STICKY_MASK_DIS_STATE_STICKY_MASK : 0U) |
               ((intr == LAN80XX_LINE_MAC_IDLE_STATE_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_TX_MONITOR_STICKY_MASK_IDLE_STATE_STICKY_MASK : 0U) |
               ((intr == LAN80XX_LINE_MAC_REMOTE_ERR_STATE_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_TX_MONITOR_STICKY_MASK_REMOTE_ERR_STATE_STICKY_MASK : 0U) |
               ((intr == LAN80XX_LINE_MAC_LOCAL_ERR_STATE_INTR) ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_TX_MONITOR_STICKY_MASK_LOCAL_ERR_STATE_STICKY_MASK : 0U);

        LAN80XX_CSR_EVENT_WRM(port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_TX_MONITOR_STICKY_MASK, LAN80XX_LINE_MAC_LINE_MAC_MAC_TX_MONITOR_STICKY,
                              LAN80XX_F_LINE_MAC_LINE_MAC_MAC_TX_MONITOR_STICKY_MASK_DIS_STATE_STICKY_MASK(enable)        |
                              LAN80XX_F_LINE_MAC_LINE_MAC_MAC_TX_MONITOR_STICKY_MASK_IDLE_STATE_STICKY_MASK(enable)       |
                              LAN80XX_F_LINE_MAC_LINE_MAC_MAC_TX_MONITOR_STICKY_MASK_REMOTE_ERR_STATE_STICKY_MASK(enable) |
                              LAN80XX_F_LINE_MAC_LINE_MAC_MAC_TX_MONITOR_STICKY_MASK_LOCAL_ERR_STATE_STICKY_MASK(enable),
                              mask);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN(0U),
                        LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_LMAC_INTR_EN(enable),
                        LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_LMAC_INTR_EN);

        return MEPA_RC_OK;

    }
    mask = ((intr == LAN80XX_HOST_MAC_DIS_STATE_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK_DIS_STATE_STICKY_MASK : 0U) |
           ((intr == LAN80XX_HOST_MAC_IDLE_STATE_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK_IDLE_STATE_STICKY_MASK : 0U) |
           ((intr == LAN80XX_HOST_MAC_REMOTE_ERR_STATE_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK_REMOTE_ERR_STATE_STICKY_MASK : 0U) |
           ((intr == LAN80XX_HOST_MAC_LOCAL_ERR_STATE_INTR) ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK_LOCAL_ERR_STATE_STICKY_MASK : 0U);

    LAN80XX_CSR_EVENT_WRM(port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK, LAN80XX_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY,
                          LAN80XX_F_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK_DIS_STATE_STICKY_MASK(enable)        |
                          LAN80XX_F_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK_IDLE_STATE_STICKY_MASK(enable)       |
                          LAN80XX_F_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK_REMOTE_ERR_STATE_STICKY_MASK(enable) |
                          LAN80XX_F_HOST_MAC_HOST_MAC_MAC_TX_MONITOR_STICKY_MASK_LOCAL_ERR_STATE_STICKY_MASK(enable),
                          mask);

    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN(0U),
                    LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_HMAC_INTR_EN(enable),
                    LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_HMAC_INTR_EN);

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_ra_fifo_event_poll(mepa_device_t         *dev,
                                          const mepa_port_no_t  port_no,
                                          u64                   intr,
                                          mepa_bool_t           is_l2h,
                                          phy25g_events_t       *const evt)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0, val = 0;
    ioreg_blk *io_reg;

    if (is_l2h == 1U) {
        mask = (((intr == LAN80XX_L2H_RA_FIFO_UNDERFLOW_INTR) ? LAN80XX_M_LINE_SLICE_L2H_RA_FIFO_STATUS_L2H_RA_FIFO_UNDERFLOW : 0U) |
                ((intr == LAN80XX_L2H_RA_FIFO_OVERFLOW_INTR) ? LAN80XX_M_LINE_SLICE_L2H_RA_FIFO_STATUS_L2H_RA_FIFO_OVERFLOW : 0U));

        io_reg = LAN80XX_LINE_SLICE_L2H_RA_FIFO_STATUS;
    } else {
        mask = (((intr == LAN80XX_H2L_RA_FIFO_UNDERFLOW_INTR) ? LAN80XX_M_LINE_SLICE_H2L_RA_FIFO_STATUS_H2L_RA_FIFO_UNDERFLOW : 0U) |
                ((intr == LAN80XX_H2L_RA_FIFO_OVERFLOW_INTR) ? LAN80XX_M_LINE_SLICE_H2L_RA_FIFO_STATUS_H2L_RA_FIFO_OVERFLOW : 0U));
        io_reg = LAN80XX_LINE_SLICE_H2L_RA_FIFO_STATUS;
    }
    LAN80XX_CSR_RD(dev, port_no, io_reg, &val);
    if ((val & mask) == 0U) {
        return MEPA_RC_OK;
    }
    *evt = (*evt | intr);
    LAN80XX_CSR_WRM(port_no, io_reg, mask, mask);
    return MEPA_RC_OK;
}


static mepa_rc lan80xx_ra_fifo_event_conf(mepa_device_t         *dev,
                                          const mepa_port_no_t  port_no,
                                          u64                   intr,
                                          mepa_bool_t           is_l2h,
                                          mepa_bool_t           enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0;
    if (is_l2h == 1U) {
        /* L2H Interrupt */
        mask = ((intr == LAN80XX_L2H_RA_FIFO_UNDERFLOW_INTR) ? LAN80XX_M_LINE_SLICE_L2H_RA_FIFO_INT_MASK_L2H_RA_FIFO_UNDERFLOW_INTR_EN : 0U) |
               ((intr == LAN80XX_L2H_RA_FIFO_OVERFLOW_INTR) ? LAN80XX_M_LINE_SLICE_L2H_RA_FIFO_INT_MASK_L2H_RA_FIFO_OVERFLOW_INTR_EN : 0U);

        LAN80XX_CSR_EVENT_WRM(port_no, LAN80XX_LINE_SLICE_L2H_RA_FIFO_INT_MASK, LAN80XX_LINE_SLICE_L2H_RA_FIFO_STATUS,
                              LAN80XX_F_LINE_SLICE_L2H_RA_FIFO_INT_MASK_L2H_RA_FIFO_UNDERFLOW_INTR_EN(enable) |
                              LAN80XX_F_LINE_SLICE_L2H_RA_FIFO_INT_MASK_L2H_RA_FIFO_OVERFLOW_INTR_EN(enable),
                              mask);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN(1),
                        LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_L2H_RA_FIFO_INTR_EN(enable),
                        LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_L2H_RA_FIFO_INTR_EN);
        return MEPA_RC_OK;
    }
    mask = ((intr == LAN80XX_H2L_RA_FIFO_UNDERFLOW_INTR) ? LAN80XX_M_LINE_SLICE_H2L_RA_FIFO_INT_MASK_H2L_RA_FIFO_UNDERFLOW_INTR_EN : 0U) |
           ((intr == LAN80XX_H2L_RA_FIFO_OVERFLOW_INTR) ? LAN80XX_M_LINE_SLICE_H2L_RA_FIFO_INT_MASK_H2L_RA_FIFO_OVERFLOW_INTR_EN : 0U);

    LAN80XX_CSR_EVENT_WRM(port_no, LAN80XX_LINE_SLICE_H2L_RA_FIFO_INT_MASK, LAN80XX_LINE_SLICE_H2L_RA_FIFO_STATUS,
                          LAN80XX_F_LINE_SLICE_H2L_RA_FIFO_INT_MASK_H2L_RA_FIFO_UNDERFLOW_INTR_EN(enable) |
                          LAN80XX_F_LINE_SLICE_H2L_RA_FIFO_INT_MASK_H2L_RA_FIFO_OVERFLOW_INTR_EN(enable),
                          mask);

    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN(1),
                    LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_H2L_RA_FIFO_INTR_EN(enable),
                    LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_H2L_RA_FIFO_INTR_EN);

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_mac_fc_buff_event_poll(mepa_device_t         *dev,
                                              const mepa_port_no_t  port_no,
                                              u64                   intr,
                                              phy25g_events_t       *const evt)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0, val = 0;

    mask = ((intr == LAN80XX_XOFF_PAUSE_GEN_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_XOFF_PAUSE_GEN_STICKY_MASK : 0U) |
           ((intr == LAN80XX_XON_PAUSE_GEN_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_XON_PAUSE_GEN_STICKY_MASK : 0U)   |
           ((intr == LAN80XX_TX_UNCORRECTED_FRM_DROP_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_TX_UNCORRECTED_FRM_DROP_STICKY_MASK : 0U) |
           ((intr == LAN80XX_RX_UNCORRECTED_FRM_DROP_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_RX_UNCORRECTED_FRM_DROP_STICKY_MASK : 0U) |
           ((intr == LAN80XX_TX_CTRL_QUEUE_OVERFLOW_DROP_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_TX_CTRL_QUEUE_OVERFLOW_DROP_STICKY_MASK : 0U) |
           ((intr == LAN80XX_TX_CTRL_QUEUE_UNDERFLOW_DROP_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_TX_CTRL_QUEUE_UNDERFLOW_DROP_STICKY_MASK : 0U) |
           ((intr == LAN80XX_TX_DATA_QUEUE_OVERFLOW_DROP_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_TX_DATA_QUEUE_OVERFLOW_DROP_STICKY_MASK : 0U) |
           ((intr == LAN80XX_TX_DATA_QUEUE_UNDERFLOW_DROP_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_TX_DATA_QUEUE_UNDERFLOW_DROP_STICKY_MASK : 0U) |
           ((intr == LAN80XX_RX_OVERFLOW_DROP_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_RX_OVERFLOW_DROP_STICKY_MASK : 0U)              |
           ((intr == LAN80XX_RX_UNDERFLOW_DROP_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_RX_UNDERFLOW_DROP_STICKY_MASK : 0U)            |
           ((intr == LAN80XX_INGR_ECC_INTERRUPT_STATUS_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_INGR_ECC_INTERRUPT_STATUS_MASK : 0U)   |
           ((intr == LAN80XX_EGR_ECC_INTERRUPT_STATUS_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_EGR_ECC_INTERRUPT_STATUS_MASK : 0U);

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY, &val);
    if ((val & mask) == 0U) {
        return MEPA_RC_OK;
    }
    *evt = (*evt | intr);
    LAN80XX_CSR_WRM(port_no, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY, mask, mask);
    return MEPA_RC_OK;
}


static mepa_rc lan80xx_mac_fc_buffer_event_conf(mepa_device_t         *dev,
                                                const mepa_port_no_t  port_no,
                                                u64                   intr,
                                                mepa_bool_t           enable)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0;

    mask = ((intr == LAN80XX_XOFF_PAUSE_GEN_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_XOFF_PAUSE_GEN_STICKY_MASK : 0U) |
           ((intr == LAN80XX_XON_PAUSE_GEN_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_XON_PAUSE_GEN_STICKY_MASK : 0U)   |
           ((intr == LAN80XX_TX_UNCORRECTED_FRM_DROP_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_TX_UNCORRECTED_FRM_DROP_STICKY_MASK : 0U) |
           ((intr == LAN80XX_RX_UNCORRECTED_FRM_DROP_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_RX_UNCORRECTED_FRM_DROP_STICKY_MASK : 0U) |
           ((intr == LAN80XX_TX_CTRL_QUEUE_OVERFLOW_DROP_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_TX_CTRL_QUEUE_OVERFLOW_DROP_STICKY_MASK : 0U) |
           ((intr == LAN80XX_TX_CTRL_QUEUE_UNDERFLOW_DROP_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_TX_CTRL_QUEUE_UNDERFLOW_DROP_STICKY_MASK : 0U);

    LAN80XX_CSR_EVENT_WRM(port_no, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY,
                          LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_XOFF_PAUSE_GEN_STICKY_MASK(enable) |
                          LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_XON_PAUSE_GEN_STICKY_MASK(enable) |
                          LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_TX_UNCORRECTED_FRM_DROP_STICKY_MASK(enable) |
                          LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_RX_UNCORRECTED_FRM_DROP_STICKY_MASK(enable) |
                          LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_TX_CTRL_QUEUE_OVERFLOW_DROP_STICKY_MASK(enable) |
                          LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_TX_CTRL_QUEUE_UNDERFLOW_DROP_STICKY_MASK(enable),
                          mask);

    mask = ((intr == LAN80XX_TX_DATA_QUEUE_OVERFLOW_DROP_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_TX_DATA_QUEUE_OVERFLOW_DROP_STICKY_MASK : 0U) |
           ((intr == LAN80XX_TX_DATA_QUEUE_UNDERFLOW_DROP_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_TX_DATA_QUEUE_UNDERFLOW_DROP_STICKY_MASK : 0U) |
           ((intr == LAN80XX_RX_OVERFLOW_DROP_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_RX_OVERFLOW_DROP_STICKY_MASK : 0U)              |
           ((intr == LAN80XX_RX_UNDERFLOW_DROP_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_RX_UNDERFLOW_DROP_STICKY_MASK : 0U)            |
           ((intr == LAN80XX_INGR_ECC_INTERRUPT_STATUS_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_INGR_ECC_INTERRUPT_STATUS_MASK : 0U)   |
           ((intr == LAN80XX_EGR_ECC_INTERRUPT_STATUS_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_EGR_ECC_INTERRUPT_STATUS_MASK : 0U);

    LAN80XX_CSR_EVENT_WRM(port_no, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY,
                          LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_TX_DATA_QUEUE_OVERFLOW_DROP_STICKY_MASK(enable) |
                          LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_TX_DATA_QUEUE_UNDERFLOW_DROP_STICKY_MASK(enable) |
                          LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_RX_OVERFLOW_DROP_STICKY_MASK(enable)            |
                          LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_RX_UNDERFLOW_DROP_STICKY_MASK(enable)           |
                          LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_INGR_ECC_INTERRUPT_STATUS_MASK(enable)          |
                          LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY_MASK_EGR_ECC_INTERRUPT_STATUS_MASK(enable),
                          mask);

    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN(0U),
                    LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_FCBUF_INTR_EN(enable),
                    LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_FCBUF_INTR_EN);

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_mac_fc_ecc_event_poll(mepa_device_t         *dev,
                                             const mepa_port_no_t  port_no,
                                             u64                   intr,
                                             mepa_bool_t           is_egr,
                                             phy25g_events_t       *const evt)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0, val = 0;
    ioreg_blk *io_reg;
    if (is_egr == 1U) {
        mask = ((intr == LAN80XX_EGR_FC_BUFFER_FAULT_READ) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INTR_STS_EGR_FC_BUFFER_FAULT_READ_INTR_STICKY : 0U) |
               ((intr == LAN80XX_EGR_FC_BUFFER_SEC_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INTR_STS_EGR_FC_BUFFER_SEC_INTR_STICKY : 0U)   |
               ((intr == LAN80XX_EGR_FC_BUFFER_DED_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INTR_STS_EGR_FC_BUFFER_DED_INTR_STICKY : 0U);

        io_reg = LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INTR_STS;
    } else {
        mask = ((intr == LAN80XX_INGR_FC_BUFFER_FAULT_READ_INTR) ?
                LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INTR_STS_INGR_FC_BUFFER_FAULT_READ_INTR_STICKY : 0U) |
               ((intr == LAN80XX_INGR_FC_BUFFER_SEC_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INTR_STS_INGR_FC_BUFFER_SEC_INTR_STICKY : 0U) |
               ((intr == LAN80XX_INGR_FC_BUFFER_DED_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INTR_STS_INGR_FC_BUFFER_DED_INTR_STICKY : 0U);

        io_reg = LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INTR_STS;
    }
    LAN80XX_CSR_RD(dev, port_no, io_reg, &val);
    if ((val & mask) == 0U) {
        return MEPA_RC_OK;
    }
    *evt = (*evt | intr);
    LAN80XX_CSR_WRM(port_no, io_reg, mask, mask);
    return MEPA_RC_OK;
}


static mepa_rc lan80xx_mac_fc_ecc_event_conf(mepa_device_t         *dev,
                                             const mepa_port_no_t  port_no,
                                             u64                   intr,
                                             mepa_bool_t           is_egr,
                                             mepa_bool_t           enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0;

    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN(0U),
                    LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_FCBUF_INTR_EN(enable),
                    LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_FCBUF_INTR_EN);

    if (is_egr == 1U) {
        mask = ((intr == LAN80XX_EGR_FC_BUFFER_FAULT_READ) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INTR_EN_EGR_FC_BUFFER_FAULT_READ_INTR_EN : 0U) |
               ((intr == LAN80XX_EGR_FC_BUFFER_SEC_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INTR_EN_EGR_FC_BUFFER_SEC_INTR_EN : 0U)   |
               ((intr == LAN80XX_EGR_FC_BUFFER_DED_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INTR_EN_EGR_FC_BUFFER_DED_INTR_EN : 0U);

        LAN80XX_CSR_EVENT_WRM(port_no, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INTR_EN,
                              LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INTR_STS,
                              LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INTR_EN_EGR_FC_BUFFER_FAULT_READ_INTR_EN(enable) |
                              LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INTR_EN_EGR_FC_BUFFER_SEC_INTR_EN(enable)        |
                              LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INTR_EN_EGR_FC_BUFFER_DED_INTR_EN(enable),
                              mask);
        return MEPA_RC_OK;
    }

    mask = ((intr == LAN80XX_INGR_FC_BUFFER_FAULT_READ_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INTR_EN_INGR_FC_BUFFER_FAULT_READ_INTR_EN : 0U) |
           ((intr == LAN80XX_INGR_FC_BUFFER_SEC_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INTR_EN_INGR_FC_BUFFER_SEC_INTR_EN : 0U) |
           ((intr == LAN80XX_INGR_FC_BUFFER_DED_INTR) ? LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INTR_EN_INGR_FC_BUFFER_DED_INTR_EN : 0U);

    LAN80XX_CSR_EVENT_WRM(port_no, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INTR_EN,
                          LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INTR_STS,
                          LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INTR_EN_INGR_FC_BUFFER_FAULT_READ_INTR_EN(enable) |
                          LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INTR_EN_INGR_FC_BUFFER_SEC_INTR_EN(enable) |
                          LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INTR_EN_INGR_FC_BUFFER_DED_INTR_EN(enable),
                          mask);

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_fc_buf_init_event_poll(mepa_device_t         *dev,
                                              const mepa_port_no_t  port_no,
                                              u64                   intr,
                                              mepa_bool_t           is_egr,
                                              phy25g_events_t       *const evt)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask = 0, val = 0;
    ioreg_blk *io_reg;
    if (is_egr == 1U) {
        mask = LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INIT_DONE_INTR_STS_EGR_FC_BUFFER_INIT_DONE_INTR_STICKY;
        io_reg = LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INIT_DONE_INTR_STS;
    } else {
        mask = LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INIT_DONE_INTR_STS_INGR_FC_BUFFER_INIT_DONE_INTR_STICKY;
        io_reg = LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INIT_DONE_INTR_STS;
    }
    LAN80XX_CSR_RD(dev, port_no, io_reg, &val);
    if ((val & mask) == 0U) {
        return MEPA_RC_OK;
    }
    *evt = (*evt | intr);
    LAN80XX_CSR_WRM(port_no, io_reg, mask, mask);
    return MEPA_RC_OK;
}


static mepa_rc lan80xx_fc_buf_init_event_conf(mepa_device_t         *dev,
                                              const mepa_port_no_t  port_no,
                                              u64                   intr,
                                              mepa_bool_t           is_egr,
                                              mepa_bool_t           enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;

    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN(0U),
                    LAN80XX_F_LINE_INTR_CTRL_LINE_INTR_EN_FCBUF_INTR_EN(enable),
                    LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_FCBUF_INTR_EN);

    if (is_egr == 1U) {
        LAN80XX_CSR_EVENT_WRM(port_no, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INIT_DONE_INTR_EN,
                              LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INIT_DONE_INTR_STS,
                              LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INIT_DONE_INTR_EN_EGR_FC_BUFFER_INIT_DONE_INTR_EN(enable),
                              LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_EGR_FC_BUFFER_ECC_INIT_DONE_INTR_EN_EGR_FC_BUFFER_INIT_DONE_INTR_EN);
        return MEPA_RC_OK;
    }
    LAN80XX_CSR_EVENT_WRM(port_no, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INIT_DONE_INTR_EN,
                          LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INIT_DONE_INTR_STS,
                          LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INIT_DONE_INTR_EN_INGR_FC_BUFFER_INIT_DONE_INTR_EN(enable),
                          LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_INGR_FC_BUFFER_ECC_INIT_DONE_INTR_EN_INGR_FC_BUFFER_INIT_DONE_INTR_EN);

    return MEPA_RC_OK;
}


mepa_rc lan80xx_event_conf_set_priv(mepa_device_t          *dev,
                                    const mepa_port_no_t   port_no,
                                    const phy25g_event_conf_t  evt_conf)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_device_t *base_dev;
    phy25g_phy_state_t  *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    u64 bit = 0, num = 0;
    u64 intr = 0;
    phy25g_events_t evt = evt_conf.evt_set;
    data->events = evt_conf.enable ? (data->events | evt) : (data->events & (evt));
    T_I(MEPA_TRACE_GRP_GEN, "\n Events Configured on Port : %d is 0x%lx \n", port_no, data->events);
    while (evt) {

        num = ((evt >> bit) & 1);
        intr = LAN80XX_EVENT_BIT(bit);
        bit++;
        if (num == 0U) {
            continue;
        }
        switch (intr) {
        case LAN80XX_LINE_PCS1G_LINK_DOWN_INTR:
        case LAN80XX_LINE_PCS1G_OUT_OF_SYNC_INTR:
            /* LINE PCS1G */
            MEPA_RC(lan80xx_1g_pcs_event_conf(dev, port_no, intr, TRUE, evt_conf.enable));
            if (evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            }
            break;

        case LAN80XX_HOST_PCS1G_LINK_DOWN_INTR:
        case LAN80XX_HOST_PCS1G_OUT_OF_SYNC_INTR:
            /* HOST PCS1G */
            MEPA_RC(lan80xx_1g_pcs_event_conf(dev, port_no, intr, FALSE, evt_conf.enable));
            if (evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, FALSE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, FALSE);
            }
            break;

        case LAN80XX_LINE_PCS25G_ALIGN_DONE_INTR:
        case LAN80XX_LINE_PCS25G_BLOCK_LOCK_INTR:
        case LAN80XX_LINE_PCS25G_HI_BER_INTR:
            /* Line PCS 25G */
            MEPA_RC(lan80xx_25g_pcs_event_conf(dev, port_no, intr, TRUE, evt_conf.enable));
            if (evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            }
            break;

        case LAN80XX_HOST_PCS25G_ALIGN_DONE_INTR:
        case LAN80XX_HOST_PCS25G_BLOCK_LOCK_INTR:
        case LAN80XX_HOST_PCS25G_HI_BER_INTR:
            /* Host PCS 25G */
            MEPA_RC(lan80xx_25g_pcs_event_conf(dev, port_no, intr, FALSE, evt_conf.enable));
            if (evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, FALSE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, FALSE);
            }
            break;

        case LAN80XX_XOFF_PAUSE_GEN_INTR:
        case LAN80XX_XON_PAUSE_GEN_INTR:
        case LAN80XX_TX_UNCORRECTED_FRM_DROP_INTR:
        case LAN80XX_RX_UNCORRECTED_FRM_DROP_INTR:
        case LAN80XX_TX_CTRL_QUEUE_OVERFLOW_DROP_INTR:
        case LAN80XX_TX_CTRL_QUEUE_UNDERFLOW_DROP_INTR:
        case LAN80XX_TX_DATA_QUEUE_OVERFLOW_DROP_INTR:
        case LAN80XX_TX_DATA_QUEUE_UNDERFLOW_DROP_INTR:
        case LAN80XX_RX_OVERFLOW_DROP_INTR:
        case LAN80XX_RX_UNDERFLOW_DROP_INTR:
        case LAN80XX_INGR_ECC_INTERRUPT_STATUS_INTR:
        case LAN80XX_EGR_ECC_INTERRUPT_STATUS_INTR:
            /* MAC FC Buffer */
            MEPA_RC(lan80xx_mac_fc_buffer_event_conf(dev, port_no, intr, evt_conf.enable));
            if (evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            }
            break;
        case LAN80XX_EGR_FC_BUFFER_FAULT_READ:
        case LAN80XX_EGR_FC_BUFFER_SEC_INTR:
        case LAN80XX_EGR_FC_BUFFER_DED_INTR:
            /* FC Buffer ECC */
            MEPA_RC(lan80xx_mac_fc_ecc_event_conf(dev, port_no, intr, TRUE, evt_conf.enable));
            if (evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            }
            break;

        case LAN80XX_INGR_FC_BUFFER_FAULT_READ_INTR:
        case LAN80XX_INGR_FC_BUFFER_SEC_INTR:
        case LAN80XX_INGR_FC_BUFFER_DED_INTR:
            /* FC Buffer ECC */
            MEPA_RC(lan80xx_mac_fc_ecc_event_conf(dev, port_no, intr, FALSE, evt_conf.enable));
            if (evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            }
            break;

        case LAN80XX_EGR_FC_BUFFER_INIT_DONE_INTR:
            /* FC Buffer ECC Init */
            MEPA_RC(lan80xx_fc_buf_init_event_conf(dev, port_no, intr, TRUE, evt_conf.enable));
            if (evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            }
            break;

        case LAN80XX_INGR_FC_BUFFER_INIT_DONE_INTR:
            /* FC Buffer ECC Init */
            MEPA_RC(lan80xx_fc_buf_init_event_conf(dev, port_no, intr, FALSE, evt_conf.enable));
            if (evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            }
            break;

        case LAN80XX_H2L_RA_FIFO_UNDERFLOW_INTR:
        case LAN80XX_H2L_RA_FIFO_OVERFLOW_INTR:
            /* H2L Interrupt */
            MEPA_RC(lan80xx_ra_fifo_event_conf(dev, port_no, intr, FALSE, evt_conf.enable));
            if (evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            }
            break;

        case LAN80XX_L2H_RA_FIFO_UNDERFLOW_INTR:
        case LAN80XX_L2H_RA_FIFO_OVERFLOW_INTR:
            /* L2H Interrupt */
            MEPA_RC(lan80xx_ra_fifo_event_conf(dev, port_no, intr, TRUE, evt_conf.enable));
            if (evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            }
            break;

        case LAN80XX_HOST_MAC_TX_ABORT_INTR:
        case LAN80XX_HOST_MAC_TX_UNDERFLOW_INTR:
        case LAN80XX_HOST_MAC_RX_TAG_INTR:
        case LAN80XX_HOST_MAC_RX_MPLS_UC_INTR:
        case LAN80XX_HOST_MAC_RX_MPLS_MC_INTR:
        case LAN80XX_HOST_MAC_RX_NON_STD_PREAMBLE_INTR:
        case LAN80XX_HOST_MAC_RX_PREAM_ERR_INTR:
        case LAN80XX_HOST_MAC_RX_PREAMBLE_MISMATCH_INTR:
        case LAN80XX_HOST_MAC_RX_PREAMBLE_SHRINK_INTR:
        case LAN80XX_HOST_MAC_RX_IPG_SHRINK_INTR:
            /* HOST MAC */
            MEPA_RC(lan80xx_mac_event_conf(dev, port_no, intr, FALSE, evt_conf.enable));
            if (evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, FALSE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, FALSE);
            }
            break;

        case LAN80XX_LINE_MAC_TX_ABORT_INTR:
        case LAN80XX_LINE_MAC_TX_UNDERFLOW_INTR:
        case LAN80XX_LINE_MAC_RX_TAG_INTR:
        case LAN80XX_LINE_MAC_RX_MPLS_UC_INTR:
        case LAN80XX_LINE_MAC_RX_MPLS_MC_INTR:
        case LAN80XX_LINE_MAC_RX_NON_STD_PREAMBLE_INTR:
        case LAN80XX_LINE_MAC_RX_PREAM_ERR_INTR:
        case LAN80XX_LINE_MAC_RX_PREAMBLE_MISMATCH_INTR:
        case LAN80XX_LINE_MAC_RX_PREAMBLE_SHRINK_INTR:
        case LAN80XX_LINE_MAC_RX_IPG_SHRINK_INTR:
            /* LINE MAC */
            MEPA_RC(lan80xx_mac_event_conf(dev, port_no, intr, TRUE, evt_conf.enable));
            if (evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            }
            break;

        case LAN80XX_HOST_MAC_DIS_STATE_INTR :
        case LAN80XX_HOST_MAC_IDLE_STATE_INTR:
        case LAN80XX_HOST_MAC_REMOTE_ERR_STATE_INTR:
        case LAN80XX_HOST_MAC_LOCAL_ERR_STATE_INTR:
            /* HOST MAC TX Monitor Interrupts */
            MEPA_RC(lan80xx_mac_tx_monitor_event_conf(dev, port_no, intr, FALSE, evt_conf.enable));
            if (evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, FALSE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, FALSE);
            }
            break;

        case LAN80XX_LINE_MAC_DIS_STATE_INTR:
        case LAN80XX_LINE_MAC_IDLE_STATE_INTR:
        case LAN80XX_LINE_MAC_REMOTE_ERR_STATE_INTR:
        case LAN80XX_LINE_MAC_LOCAL_ERR_STATE_INTR:
            /* LINE MAC Tx Monitor Interrupts */
            MEPA_RC(lan80xx_mac_tx_monitor_event_conf(dev, port_no, intr, TRUE, evt_conf.enable));
            if (evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, data->channel_id, TRUE);
            }
            break;
        case LAN80XX_GPIO_INTR_0:
            /* GPIO INTR 0 */
            if (evt_conf.enable) {
                LAN80XX_ENABLE_GPIO_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_GPIO_INTR0_EN);
            } else {
                LAN80XX_DISABLE_GPIO_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_GPIO_INTR0_EN);
            }
            break;
        case LAN80XX_GPIO_INTR_1:
            /* GPIO INTR 1 */
            if (evt_conf.enable) {
                LAN80XX_ENABLE_GPIO_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_GPIO_INTR1_EN);
            } else {
                LAN80XX_DISABLE_GPIO_INTERRUPT_FOR_EVENT(base_data->port_no, evt_conf.intr_sel, LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_GPIO_INTR1_EN);
            }
            break;
        }
        evt = evt & (evt - 1);
    }
    return MEPA_RC_OK;
}


mepa_rc lan80xx_event_conf_get_priv(mepa_device_t          *dev,
                                    const mepa_port_no_t   port_no,
                                    phy25g_events_t  *const evt)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    *evt = data->events;
    return MEPA_RC_OK;
}



mepa_rc lan80xx_event_poll_priv(mepa_device_t          *dev,
                                const mepa_port_no_t   port_no,
                                phy25g_events_t   *const evt)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_events_t evt_get;
    evt_get = data->events;
    u64 bit = 0, num = 0;
    *evt = 0;
    u64 intr = 0;
    while (evt_get) {

        num = ((evt_get >> bit) & 1);
        intr = LAN80XX_EVENT_BIT(bit);
        bit++;
        if (num == 0) {
            continue;
        }
        switch (intr) {
        case LAN80XX_LINE_PCS1G_LINK_DOWN_INTR:
        case LAN80XX_LINE_PCS1G_OUT_OF_SYNC_INTR:

            /* LINE PCS1G */
            MEPA_RC(lan80xx_1g_pcs_event_poll(dev, port_no, intr, TRUE, evt));
            break;
        case LAN80XX_HOST_PCS1G_LINK_DOWN_INTR:
        case LAN80XX_HOST_PCS1G_OUT_OF_SYNC_INTR:
            /* HOST PCS1G */
            MEPA_RC(lan80xx_1g_pcs_event_poll(dev, port_no, intr, FALSE, evt));
            break;

        case LAN80XX_LINE_PCS25G_ALIGN_DONE_INTR:
        case LAN80XX_LINE_PCS25G_BLOCK_LOCK_INTR:
        case LAN80XX_LINE_PCS25G_HI_BER_INTR:
            /* LINE PCS25G Interrupt */
            MEPA_RC(lan80xx_25g_pcs_event_poll(dev, port_no, intr, TRUE, evt));
            break;

        case LAN80XX_HOST_PCS25G_ALIGN_DONE_INTR:
        case LAN80XX_HOST_PCS25G_BLOCK_LOCK_INTR:
        case LAN80XX_HOST_PCS25G_HI_BER_INTR:
            /* HOST PCS25G Interrupt */
            MEPA_RC(lan80xx_25g_pcs_event_poll(dev, port_no, intr, FALSE, evt));
            break;

        case LAN80XX_H2L_RA_FIFO_UNDERFLOW_INTR:
        case LAN80XX_H2L_RA_FIFO_OVERFLOW_INTR:
            /* H2L Interrupt */
            MEPA_RC(lan80xx_ra_fifo_event_poll(dev, port_no, intr, FALSE, evt));
            break;

        case LAN80XX_L2H_RA_FIFO_UNDERFLOW_INTR:
        case LAN80XX_L2H_RA_FIFO_OVERFLOW_INTR:
            /* Ingress Rate Adaption FIFO */
            MEPA_RC(lan80xx_ra_fifo_event_poll(dev, port_no, intr, TRUE, evt));
            break;

        case LAN80XX_HOST_MAC_TX_ABORT_INTR:
        case LAN80XX_HOST_MAC_TX_UNDERFLOW_INTR:
        case LAN80XX_HOST_MAC_RX_TAG_INTR:
        case LAN80XX_HOST_MAC_RX_MPLS_UC_INTR:
        case LAN80XX_HOST_MAC_RX_MPLS_MC_INTR:
        case LAN80XX_HOST_MAC_RX_NON_STD_PREAMBLE_INTR:
        case LAN80XX_HOST_MAC_RX_PREAM_ERR_INTR:
        case LAN80XX_HOST_MAC_RX_PREAMBLE_MISMATCH_INTR:
        case LAN80XX_HOST_MAC_RX_PREAMBLE_SHRINK_INTR:
        case LAN80XX_HOST_MAC_RX_IPG_SHRINK_INTR:

            /* HOST MAC Interrupts */
            MEPA_RC(lan80xx_mac_event_poll(dev, port_no, intr, FALSE, evt));
            break;
        case LAN80XX_LINE_MAC_TX_ABORT_INTR:
        case LAN80XX_LINE_MAC_TX_UNDERFLOW_INTR:
        case LAN80XX_LINE_MAC_RX_TAG_INTR:
        case LAN80XX_LINE_MAC_RX_MPLS_UC_INTR:
        case LAN80XX_LINE_MAC_RX_MPLS_MC_INTR:
        case LAN80XX_LINE_MAC_RX_NON_STD_PREAMBLE_INTR:
        case LAN80XX_LINE_MAC_RX_PREAM_ERR_INTR:
        case LAN80XX_LINE_MAC_RX_PREAMBLE_MISMATCH_INTR:
        case LAN80XX_LINE_MAC_RX_PREAMBLE_SHRINK_INTR:
        case LAN80XX_LINE_MAC_RX_IPG_SHRINK_INTR:
            /* LINE MAC Interrupts */
            MEPA_RC(lan80xx_mac_event_poll(dev, port_no, intr, TRUE, evt));
            break;

        case LAN80XX_HOST_MAC_DIS_STATE_INTR :
        case LAN80XX_HOST_MAC_IDLE_STATE_INTR:
        case LAN80XX_HOST_MAC_REMOTE_ERR_STATE_INTR:
        case LAN80XX_HOST_MAC_LOCAL_ERR_STATE_INTR:
            /* HOST MAC TX Monitor Interrupts */
            MEPA_RC(lan80xx_mac_tx_monitor_event_poll(dev, port_no, intr, FALSE, evt));
            break;

        case LAN80XX_LINE_MAC_DIS_STATE_INTR :
        case LAN80XX_LINE_MAC_IDLE_STATE_INTR:
        case LAN80XX_LINE_MAC_REMOTE_ERR_STATE_INTR:
        case LAN80XX_LINE_MAC_LOCAL_ERR_STATE_INTR:
            /* LINE MAC TX Monitor Interrupts */
            MEPA_RC(lan80xx_mac_tx_monitor_event_poll(dev, port_no, intr, TRUE, evt));
            break;

        case LAN80XX_XOFF_PAUSE_GEN_INTR:
        case LAN80XX_XON_PAUSE_GEN_INTR:
        case LAN80XX_TX_UNCORRECTED_FRM_DROP_INTR:
        case LAN80XX_RX_UNCORRECTED_FRM_DROP_INTR:
        case LAN80XX_TX_CTRL_QUEUE_OVERFLOW_DROP_INTR:
        case LAN80XX_TX_CTRL_QUEUE_UNDERFLOW_DROP_INTR:
        case LAN80XX_TX_DATA_QUEUE_OVERFLOW_DROP_INTR:
        case LAN80XX_TX_DATA_QUEUE_UNDERFLOW_DROP_INTR:
        case LAN80XX_RX_OVERFLOW_DROP_INTR:
        case LAN80XX_RX_UNDERFLOW_DROP_INTR:
        case LAN80XX_INGR_ECC_INTERRUPT_STATUS_INTR:
        case LAN80XX_EGR_ECC_INTERRUPT_STATUS_INTR:
            /* FC Buffer Interrupt */
            MEPA_RC(lan80xx_mac_fc_buff_event_poll(dev, port_no, intr, evt));
            break;

        case LAN80XX_EGR_FC_BUFFER_FAULT_READ:
        case LAN80XX_EGR_FC_BUFFER_SEC_INTR:
        case LAN80XX_EGR_FC_BUFFER_DED_INTR:
            /* FC Buffer Interrupt */
            MEPA_RC(lan80xx_mac_fc_ecc_event_poll(dev, port_no, intr, TRUE, evt));
            break;

        case LAN80XX_INGR_FC_BUFFER_FAULT_READ_INTR:
        case LAN80XX_INGR_FC_BUFFER_SEC_INTR:
        case LAN80XX_INGR_FC_BUFFER_DED_INTR:
            /* FC Buffer Interrupt */
            MEPA_RC(lan80xx_mac_fc_ecc_event_poll(dev, port_no, intr, FALSE, evt));
            break;

        case LAN80XX_EGR_FC_BUFFER_INIT_DONE_INTR:
            /* FC Buffer Interrupt */
            MEPA_RC(lan80xx_fc_buf_init_event_poll(dev, port_no, intr, TRUE, evt));
            break;

        case LAN80XX_INGR_FC_BUFFER_INIT_DONE_INTR:
            /* FC Buffer Interrupt */
            MEPA_RC(lan80xx_fc_buf_init_event_poll(dev, port_no, intr, FALSE, evt));
            break;
        case LAN80XX_GPIO_INTR_0:
        case LAN80XX_GPIO_INTR_1:
            /* GPIO INTR 0/1 */
            MEPA_RC(lan80xx_gpio_intr_event_poll(dev, port_no, intr, evt));
            break;
        default:
            break;
        }
        evt_get = evt_get & (evt_get - 1);
    }
    T_I(MEPA_TRACE_GRP_GEN, "\nEvent Triggered : %ld on Port : %d \n", *evt, port_no);
    return MEPA_RC_OK;
}


mepa_rc lan80xx_ext_event_conf_set_priv(mepa_device_t                *dev,
                                        const mepa_port_no_t          port_no,
                                        const phy25g_ext_event_conf_t     ext_evt_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_device_t *base_dev;
    phy25g_phy_state_t  *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    u64 bit = 0, num = 0, intr = 0;
    phy25g_ext_events_t ext_evt_set = ext_evt_conf.ext_evt_set;
    data->ext_events = ext_evt_conf.enable ? (data->ext_events | ext_evt_set) : (data->ext_events & (ext_evt_set));
    T_I(MEPA_TRACE_GRP_GEN, "\n Extended Events Configured on Port : %d is 0x%lx \n", port_no, data->ext_events);
    while (ext_evt_set) {
        num = ((ext_evt_set >> bit) & 1);
        intr = LAN80XX_EVENT_BIT(bit);
        bit++;
        if (num == 0) {
            continue;
        }
        switch (intr) {
        case LAN80XX_LINE_PMA_RXEI_FILTERED_INTR:
        case LAN80XX_LINE_PMA_RESET_DONE_INTR:
            /* LINE PMA */
            MEPA_RC(lan80xx_pma_event_conf(dev, port_no, intr, TRUE, ext_evt_conf.enable));
            if (ext_evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, ext_evt_conf.intr_sel, data->channel_id, TRUE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, ext_evt_conf.intr_sel, data->channel_id, TRUE);
            }
            break;
        case LAN80XX_HOST_PMA_RXEI_FILTERED_INTR:
        case LAN80XX_HOST_PMA_RESET_DONE_INTR:
            /* HOST PMA */
            MEPA_RC(lan80xx_pma_event_conf(dev, port_no, intr, FALSE, ext_evt_conf.enable));
            if (ext_evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, ext_evt_conf.intr_sel, data->channel_id, FALSE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, ext_evt_conf.intr_sel, data->channel_id, FALSE);
            }
            break;
        case LAN80XX_LINE_PMAC_RX_PREAMBLE_SHRINK:
        case LAN80XX_LINE_PMAC_RX_PREAMBLE_MISMATCH:
        case LAN80XX_LINE_PMAC_RX_PREAMBLE_ERR:
        case LAN80XX_LINE_PMAC_RX_NON_STD_PREAMBLE_INTR:
        case LAN80XX_LINE_PMAC_RX_MPLS_MC_INTR:
        case LAN80XX_LINE_PMAC_RX_MPLS_UC_INTR:
        case LAN80XX_LINE_PMAC_TX_UNDERFLOW_INTR:
        case LAN80XX_LINE_PMAC_TX_ABORT_INTR:
            /* LINE P-MAC */
            MEPA_RC(lan80xx_pmac_block_event_conf(dev, port_no, intr, FALSE, ext_evt_conf.enable));
            if (ext_evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, ext_evt_conf.intr_sel, data->channel_id, TRUE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, ext_evt_conf.intr_sel, data->channel_id, TRUE);
            }
            break;
        case LAN80XX_HOST_PMAC_RX_PREAMBLE_SHRINK:
        case LAN80XX_HOST_PMAC_RX_PREAMBLE_MISMATCH:
        case LAN80XX_HOST_PMAC_RX_PREAMBLE_ERR:
        case LAN80XX_HOST_PMAC_RX_NON_STD_PREAMBLE_INTR:
        case LAN80XX_HOST_PMAC_RX_MPLS_MC_INTR:
        case LAN80XX_HOST_PMAC_RX_MPLS_UC_INTR:
        case LAN80XX_HOST_PMAC_TX_UNDERFLOW_INTR:
        case LAN80XX_HOST_PMAC_TX_ABORT_INTR:
            /* HOST P-MAC */
            MEPA_RC(lan80xx_pmac_block_event_conf(dev, port_no, intr, TRUE, ext_evt_conf.enable));
            if (ext_evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, ext_evt_conf.intr_sel, data->channel_id, FALSE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, ext_evt_conf.intr_sel, data->channel_id, FALSE);
            }
            break;
        case LAN80XX_LINE_MAC_MM_PRMPT_UNEXP_TX_PFRM_INTR:
        case LAN80XX_LINE_MAC_MM_PRMPT_UNEXP_RX_PFRM_INTR:
        case LAN80XX_LINE_MAC_MM_PRMPT_ACTIVE_INTR:
            /* LINE NM MAC */
            MEPA_RC(lan80xx_mac_nm_event_conf(dev, port_no, intr, FALSE, ext_evt_conf.enable));
            if (ext_evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, ext_evt_conf.intr_sel, data->channel_id, TRUE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, ext_evt_conf.intr_sel, data->channel_id, TRUE);
            }
            break;
        case LAN80XX_HOST_MAC_MM_PRMPT_UNEXP_TX_PFRM_INTR:
        case LAN80XX_HOST_MAC_MM_PRMPT_UNEXP_RX_PFRM_INTR:
        case LAN80XX_HOST_MAC_MM_PRMPT_ACTIVE_INTR:
            /* HOST NM MAC */
            MEPA_RC(lan80xx_mac_nm_event_conf(dev, port_no, intr, TRUE, ext_evt_conf.enable));
            if (ext_evt_conf.enable) {
                LAN80XX_ENABLE_INTERRUPT_FOR_EVENT(base_data->port_no, ext_evt_conf.intr_sel, data->channel_id, FALSE);
            } else {
                LAN80XX_DISABLE_INTERRUPT_FOR_EVENT(base_data->port_no, ext_evt_conf.intr_sel, data->channel_id, FALSE);
            }
            break;
        case LAN80XX_WPS1_FC_ACK_TIMER_INTR:
        case LAN80XX_WPS0_FC_ACK_TIMER_INTR:
        case LAN80XX_WPS1_CONN_FAULT_INTR:
        case LAN80XX_WPS0_CONN_FAULT_INTR:
        case LAN80XX_WPS1_FAILOVER_INTR:
        case LAN80XX_WPS0_FAILOVER_INTR:
            /* Cross connect INTR2 */
            MEPA_RC(lan80xx_xconnect_ext_event_conf(dev, port_no, intr, TRUE, ext_evt_conf.enable));
            if (ext_evt_conf.enable) {
                LAN80XX_ENABLE_GPIO_INTERRUPT_FOR_EVENT(base_data->port_no, ext_evt_conf.intr_sel, LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CROSS_CONNECT_INTR_EN);
            } else {
                LAN80XX_DISABLE_GPIO_INTERRUPT_FOR_EVENT(base_data->port_no, ext_evt_conf.intr_sel, LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CROSS_CONNECT_INTR_EN);
            }
            break;
        case LAN80XX_H0_SWITCH_INTR:
        case LAN80XX_H1_SWITCH_INTR:
        case LAN80XX_H2_SWITCH_INTR:
        case LAN80XX_H3_SWITCH_INTR:
        case LAN80XX_L0_SWITCH_INTR:
        case LAN80XX_L1_SWITCH_INTR:
        case LAN80XX_L2_SWITCH_INTR:
        case LAN80XX_L3_SWITCH_INTR:
        case LAN80XX_H0_COND_ALT_DET_INTR:
        case LAN80XX_H1_COND_ALT_DET_INTR:
        case LAN80XX_H2_COND_ALT_DET_INTR:
        case LAN80XX_H3_COND_ALT_DET_INTR:
        case LAN80XX_L0_COND_ALT_DET_INTR:
        case LAN80XX_L1_COND_ALT_DET_INTR:
        case LAN80XX_L2_COND_ALT_DET_INTR:
        case LAN80XX_L3_COND_ALT_DET_INTR:
        case LAN80XX_H0_COND_ALT_UNF_DET_INTR:
        case LAN80XX_H1_COND_ALT_UNF_DET_INTR:
        case LAN80XX_H2_COND_ALT_UNF_DET_INTR:
        case LAN80XX_H3_COND_ALT_UNF_DET_INTR:
        case LAN80XX_L0_COND_ALT_UNF_DET_INTR:
        case LAN80XX_L1_COND_ALT_UNF_DET_INTR:
        case LAN80XX_L2_COND_ALT_UNF_DET_INTR:
        case LAN80XX_L3_COND_ALT_UNF_DET_INTR:
        case LAN80XX_H0_FIFO_ERROR_INTR:
        case LAN80XX_H1_FIFO_ERROR_INTR:
        case LAN80XX_H2_FIFO_ERROR_INTR:
        case LAN80XX_H3_FIFO_ERROR_INTR:
        case LAN80XX_L0_FIFO_ERROR_INTR:
        case LAN80XX_L1_FIFO_ERROR_INTR:
        case LAN80XX_L2_FIFO_ERROR_INTR:
        case LAN80XX_L3_FIFO_ERROR_INTR:
            /* Cross connect INTR */
            MEPA_RC(lan80xx_xconnect_ext_event_conf(dev, port_no, intr, FALSE, ext_evt_conf.enable));
            if (ext_evt_conf.enable) {
                LAN80XX_ENABLE_GPIO_INTERRUPT_FOR_EVENT(base_data->port_no, ext_evt_conf.intr_sel, LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CROSS_CONNECT_INTR_EN);
            } else {
                LAN80XX_DISABLE_GPIO_INTERRUPT_FOR_EVENT(base_data->port_no, ext_evt_conf.intr_sel, LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CROSS_CONNECT_INTR_EN);
            }
            break;
        default:
            T_E(MEPA_TRACE_GRP_GEN, "\n Extended Event configuration not Supported on Port : %d \n", port_no);
            return MEPA_RC_ERROR;
        }
        ext_evt_set = ext_evt_set & (ext_evt_set - 1);
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_ext_event_conf_get_priv(mepa_device_t          *dev,
                                        const mepa_port_no_t   port_no,
                                        phy25g_ext_events_t    *const ext_evt)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    *ext_evt = data->ext_events;
    return MEPA_RC_OK;
}

mepa_rc lan80xx_ext_event_poll_priv(mepa_device_t          *dev,
                                    const mepa_port_no_t   port_no,
                                    phy25g_ext_events_t    *const ext_evt)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_ext_events_t evt_get;
    evt_get = data->ext_events;
    u64 bit = 0, num = 0, intr = 0;
    *ext_evt = 0;
    while (evt_get) {
        num = ((evt_get >> bit) & 1);
        intr = LAN80XX_EVENT_BIT(bit);
        bit++;
        if (num == 0) {
            continue;
        }
        switch (intr) {
        case LAN80XX_LINE_PMA_RXEI_FILTERED_INTR:
        case LAN80XX_LINE_PMA_RESET_DONE_INTR:
            /* LINE PMA */
            MEPA_RC(lan80xx_pma_event_poll(dev, port_no, intr, TRUE, ext_evt));
            break;
        case LAN80XX_HOST_PMA_RXEI_FILTERED_INTR:
        case LAN80XX_HOST_PMA_RESET_DONE_INTR:
            /* HOST PMA */
            MEPA_RC(lan80xx_pma_event_poll(dev, port_no, intr, FALSE, ext_evt));
            break;
        case LAN80XX_LINE_PMAC_RX_PREAMBLE_SHRINK:
        case LAN80XX_LINE_PMAC_RX_PREAMBLE_MISMATCH:
        case LAN80XX_LINE_PMAC_RX_PREAMBLE_ERR:
        case LAN80XX_LINE_PMAC_RX_NON_STD_PREAMBLE_INTR:
        case LAN80XX_LINE_PMAC_RX_MPLS_MC_INTR:
        case LAN80XX_LINE_PMAC_RX_MPLS_UC_INTR:
        case LAN80XX_LINE_PMAC_TX_UNDERFLOW_INTR:
        case LAN80XX_LINE_PMAC_TX_ABORT_INTR:
            /* LINE P-MAC */
            MEPA_RC(lan80xx_pmac_block_event_poll(dev, port_no, intr, TRUE, ext_evt));
            break;
        case LAN80XX_HOST_PMAC_RX_PREAMBLE_SHRINK:
        case LAN80XX_HOST_PMAC_RX_PREAMBLE_MISMATCH:
        case LAN80XX_HOST_PMAC_RX_PREAMBLE_ERR:
        case LAN80XX_HOST_PMAC_RX_NON_STD_PREAMBLE_INTR:
        case LAN80XX_HOST_PMAC_RX_MPLS_MC_INTR:
        case LAN80XX_HOST_PMAC_RX_MPLS_UC_INTR:
        case LAN80XX_HOST_PMAC_TX_UNDERFLOW_INTR:
        case LAN80XX_HOST_PMAC_TX_ABORT_INTR:
            /* HOST P-MAC */
            MEPA_RC(lan80xx_pmac_block_event_poll(dev, port_no, intr, FALSE, ext_evt));
            break;
        case LAN80XX_LINE_MAC_MM_PRMPT_UNEXP_TX_PFRM_INTR:
        case LAN80XX_LINE_MAC_MM_PRMPT_UNEXP_RX_PFRM_INTR:
        case LAN80XX_LINE_MAC_MM_PRMPT_ACTIVE_INTR:
            /* LINE NM MAC */
            MEPA_RC(lan80xx_mac_nm_event_poll(dev, port_no, intr, TRUE, ext_evt));
            break;
        case LAN80XX_HOST_MAC_MM_PRMPT_UNEXP_TX_PFRM_INTR:
        case LAN80XX_HOST_MAC_MM_PRMPT_UNEXP_RX_PFRM_INTR:
        case LAN80XX_HOST_MAC_MM_PRMPT_ACTIVE_INTR:
            /* HOST NM MAC */
            MEPA_RC(lan80xx_mac_nm_event_poll(dev, port_no, intr, FALSE, ext_evt));
            break;
        case LAN80XX_WPS1_FC_ACK_TIMER_INTR:
        case LAN80XX_WPS0_FC_ACK_TIMER_INTR:
        case LAN80XX_WPS1_CONN_FAULT_INTR:
        case LAN80XX_WPS0_CONN_FAULT_INTR:
        case LAN80XX_WPS1_FAILOVER_INTR:
        case LAN80XX_WPS0_FAILOVER_INTR:
            /* Cross connect INTR2 */
            MEPA_RC(lan80xx_xconnect_ext_event_poll(dev, port_no, intr, TRUE, ext_evt));
            break;
        case LAN80XX_H0_SWITCH_INTR:
        case LAN80XX_H1_SWITCH_INTR:
        case LAN80XX_H2_SWITCH_INTR:
        case LAN80XX_H3_SWITCH_INTR:
        case LAN80XX_L0_SWITCH_INTR:
        case LAN80XX_L1_SWITCH_INTR:
        case LAN80XX_L2_SWITCH_INTR:
        case LAN80XX_L3_SWITCH_INTR:
        case LAN80XX_H0_COND_ALT_DET_INTR:
        case LAN80XX_H1_COND_ALT_DET_INTR:
        case LAN80XX_H2_COND_ALT_DET_INTR:
        case LAN80XX_H3_COND_ALT_DET_INTR:
        case LAN80XX_L0_COND_ALT_DET_INTR:
        case LAN80XX_L1_COND_ALT_DET_INTR:
        case LAN80XX_L2_COND_ALT_DET_INTR:
        case LAN80XX_L3_COND_ALT_DET_INTR:
        case LAN80XX_H0_COND_ALT_UNF_DET_INTR:
        case LAN80XX_H1_COND_ALT_UNF_DET_INTR:
        case LAN80XX_H2_COND_ALT_UNF_DET_INTR:
        case LAN80XX_H3_COND_ALT_UNF_DET_INTR:
        case LAN80XX_L0_COND_ALT_UNF_DET_INTR:
        case LAN80XX_L1_COND_ALT_UNF_DET_INTR:
        case LAN80XX_L2_COND_ALT_UNF_DET_INTR:
        case LAN80XX_L3_COND_ALT_UNF_DET_INTR:
        case LAN80XX_H0_FIFO_ERROR_INTR:
        case LAN80XX_H1_FIFO_ERROR_INTR:
        case LAN80XX_H2_FIFO_ERROR_INTR:
        case LAN80XX_H3_FIFO_ERROR_INTR:
        case LAN80XX_L0_FIFO_ERROR_INTR:
        case LAN80XX_L1_FIFO_ERROR_INTR:
        case LAN80XX_L2_FIFO_ERROR_INTR:
        case LAN80XX_L3_FIFO_ERROR_INTR:
            /* Cross connect INTR */
            MEPA_RC(lan80xx_xconnect_ext_event_poll(dev, port_no, intr, FALSE, ext_evt));
            break;
        }
        evt_get = evt_get & (evt_get - 1);
    }
    T_I(MEPA_TRACE_GRP_GEN, "\nExtended Event Triggered : %ld on Port : %d \n", *ext_evt, port_no);
    return MEPA_RC_OK;
}
