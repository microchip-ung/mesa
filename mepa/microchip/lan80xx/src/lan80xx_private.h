// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef MEPA_LAN80XX_PRIVATE_H_
#define MEPA_LAN80XX_PRIVATE_H_

#include <microchip/ethernet/phy/api/types.h>
#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include "lan80xx_types.h"

#define MEPA_RC(expr) { mesa_rc __rc__ = (expr); if (__rc__ < MESA_RC_OK) return __rc__; }
#define MEPA_ASSERT(x) if((x)) { return MESA_RC_ERROR;}

#define T_N(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_NOISE, __FUNCTION__, __LINE__, __FILE__, format, ##__VA_ARGS__);
#define T_D(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_DEBUG, __FUNCTION__, __LINE__, __FILE__, format, ##__VA_ARGS__);
#define T_I(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_INFO, __FUNCTION__, __LINE__, __FILE__, format, ##__VA_ARGS__);
#define T_W(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_WARNING, __FUNCTION__, __LINE__, __FILE__, format, ##__VA_ARGS__);
#define T_E(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_ERROR, __FUNCTION__, __LINE__, __FILE__, format, ##__VA_ARGS__);

#define T_DM(port_no, format, ...) \
    do { \
        uint32_t val = 0; \
        LAN80XX_CSR_RD(dev, port_no, \
                        LAN80XX_MCU_IO_MNGT_MISC_MCU_BOOT_STATUS_REG, &val);\
        T_D(MEPA_TRACE_GRP_GEN, "[MCU_STS:0x%X] " format, val, ##__VA_ARGS__); \
    } while (0)

#define T_EM(port_no, format, ...) \
    do { \
        uint32_t val = 0; \
        LAN80XX_CSR_RD(dev, port_no, \
                        LAN80XX_MCU_IO_MNGT_MISC_MCU_BOOT_STATUS_REG, &val);\
        T_E(MEPA_TRACE_GRP_GEN, "[MCU_STS:0x%X] " format, val, ##__VA_ARGS__); \
    } while (0)

#define T_IM(port_no, format, ...) \
    do { \
        uint32_t val = 0; \
        LAN80XX_CSR_RD(dev, port_no, \
                        LAN80XX_MCU_IO_MNGT_MISC_MCU_BOOT_STATUS_REG, &val);\
        T_I(MEPA_TRACE_GRP_GEN, "[MCU_STS:0x%X] " format, val, ##__VA_ARGS__); \
    } while (0)

#define LAN80XX_UINT_8_MAX_VALUE                (255U)

/* Polling to eye scan status bit for 500 ms */
#define LAN80XX_EYE_SCAN_POLL_DELAY_10MS        (10U)
/* Eye scan reference voltage amplitude */
#define LAN80XX_EYE_SCAN_MAX_VREF_AMPLITUDE     (127U)
/* Eye scan results are stored in registers LANE_D0 to D8 */
#define LAN80XX_EYE_SCAN_RESULT_REG_COUNT       (8U)
#define LAN80XX_PHY_TS_FIFO_MAX_ENTRIES         (16U)
#define LAN80XX_DFE_NUM_OF_TAP                  (5U)
#define LAN80XX_DFE_ADAPTIVE_MODE_ENA           (1U)
#define LAN80XX_DFE_MANUAL_MODE_ENABLE          (0x3FU)
#define LAN80XX_DFE_ADAP_TAP_ENABLE             (0x1FU)
#define LAN80XX_GPIO_PINS_SLOT_0                (32U)
#define LAN80XX_I2C_SCL_PRESCALAR_INVALID       (0x003BU)

#define MCU_TEMP_THRESHOLD_REG_ADDR             (0x00080056U)
#define MCU_TEMP_THRESHOLD_BYTE_LEN             (4U)
/* Default Temperature threshold Value when User not configures the Threshold: 105 degree Celsius */
#define MCU_DEFAULT_TEMP_THRESHOLD              (105U)

/* PVT temperature sensor constants from Silicon DOS B.6 */
#define LAN80XX_PVT_CONST_Y                     (352.3)
/* If you want to enforce float/double, use (352.3F) or (352.3) as needed */
#define LAN80XX_PVT_CONST_K                     (109.4)
#define LAN80XX_PVT_RESOL                       (4096U)

/* GPIO Numbers */
#define LAN80XX_GPIO_6                          (6U)
#define LAN80XX_GPIO_7                          (7U)
#define LAN80XX_GPIO_14                         (14U)
#define LAN80XX_GPIO_15                         (15U)
#define LAN80XX_GPIO_22                         (22U)
#define LAN80XX_GPIO_23                         (23U)
#define LAN80XX_GPIO_30                         (30U)
#define LAN80XX_GPIO_31                         (31U)
#define LAN80XX_GPIO_34                         (34U)
#define LAN80XX_GPIO_35                         (35U)
#define LAN80XX_GPIO_36                         (36U)
#define LAN80XX_GPIO_37                         (37U)
#define LAN80XX_GPIO_38                         (38U)
#define LAN80XX_GPIO_39                         (39U)
#define LAN80XX_GPIO_2                          (2U)
#define LAN80XX_GPIO_3                          (3U)
#define LAN80XX_GPIO_10                         (10U)
#define LAN80XX_GPIO_11                         (11U)
#define LAN80XX_GPIO_18                         (18U)
#define LAN80XX_GPIO_19                         (19U)
#define LAN80XX_GPIO_26                         (26U)
#define LAN80XX_GPIO_27                         (27U)

#define LAN80XX_CLAUSE37_ADV_1G_FDX_BIT        (5U)
#define LAN80XX_CLAUSE37_ADV_1G_HDX_BIT        (6U)
#define LAN80XX_CLAUSE37_ADV_SYMMETRIC_PAUSE   (7U)
#define LAN80XX_CLAUSE37_ADV_ASYMMETRIC_PAUSE  (8U)
#define LAN80XX_CLAUSE37_ADV_REMOTE_FAULT      (12U)
#define LAN80XX_CLAUSE37_ADV_ACK               (14U)
#define LAN80XX_CLAUSE37_ADV_NEXT_PAGE         (15U)

/* MAC block Config values */
#define LAN80XX_MAC_FC_BUFF_STICY_MASK         (0xFFFFFFU)
#define LAN80XX_LINE_MAC_ADDRESS_LSB           (0x31FD42CCUL)
#define LAN80XX_LINE_MAC_ADDRESS_MSB           (0x3E67U)
#define LAN80XX_HOST_MAC_ADDRESS_LSB           (0xEAAB6628UL)
#define LAN80XX_HOST_MAC_ADDRESS_MSB           (0xA6C4U)
#define LAN80XX_MAC_MAXLEN                     (65280U)
#define LAN80XX_LINE_MAC_TAGS_CFG_0            (0x10U)
#define LAN80XX_LINE_MAC_TAGS_CFG_1            (0x91999919UL)
#define LAN80XX_LINE_MAC_TAGS_CFG_2            (0x92000010UL)
#define LAN80XX_HOST_MAC_TAGS_CFG_0            (0x88180010UL)
#define LAN80XX_HOST_MAC_TAGS_CFG_1            (0x91000010UL)
#define LAN80XX_HOST_MAC_TAGS_CFG_2            (0x92000010UL)
#define LAN80XX_LINE_MAC_TX_FRM_CTRL           (0x24290000UL)
#define LAN80XX_LINE_MAC_TX_FRM_CTRL_2         (0xFFFFU)
#define LAN80XX_HOST_MAC_TX_FRM_CTRL           (0x34C60000UL)
#define LAN80XX_HOST_MAC_TX_FRM_CTRL_2         (0xFFFFU)

#define LAN80XX_PMA_DATA_WIDTH_10BIT           (0U)
#define LAN80XX_PMA_DATA_WIDTH_40BIT           (4U)

/* Selecting the INTR 0 or INTR 1 for Channel Level Interrupts */
/* Line Interrupts Routing through INTR 0 */
#define LAN80XX_LINE_INTRUPT_INTR0             (0x3FC00U)
/* Line Interrupts Routing through INTR 1 */
#define LAN80XX_LINE_INTRUPT_INTR1             (0xC03C0U)
/* Host Interrupt Routing through INTR 0 */
#define LAN80XX_HOST_INTRUPT_INTR0             (0x3CU)
/* Host Interrupts Routing through INTR 1 */
#define LAN80XX_HOST_INTRUPT_INTR1             (0x3U)

#define LAN80XX_BIST_BYPASS_STRAP              ((1U) << 3)
#define LAN80XX_POST1_SLICE0_INIT_STATUS_ADDR  (0x89U)
#define LAN80XX_POST1_TRIGGER                  (0x7FFU)
#define LAN80XX_POST1_SLICE0_BIST_STATUS_ADDR  (0x81U)
#define LAN80XX_POST1_SLICE0_BIST_RESULT_ADDR  (0x85U)
#define LAN80XX_POST1_STATUS_P1_POST_DONE      (0x1U)

extern mepa_ts_driver_t lan80xx_ts_drivers;
extern mepa_macsec_driver_t lan80xx_macsec_drivers;

typedef struct {
    u8     r_dwidthctrl_from_hwt;
    u8     r_reg_manual;
    u8     cfg_common_reserve;
    u8     cfg_en_dummy;
    u8     cfg_pll_reserve_3_0;
    u8     l0_cfg_txcal_en;
    u8     l0_cfg_tx_reserve_15_8;
    u8     l0_cfg_tx_reserve_7_0;
    u8     cfg_pll_lol_set;
    u8     cfg_i_vco_3_0;
    u8     cfg_icp_base_sel_3_0;
    u8     cfg_icp_sel_2_0;
    u8     cfg_rsel_2_0;
    u8     r_dwidthctrl_2_0;
    u8     r_txfifo_ck_div_pmad_2_0;
    u8     r_rxfifo_ck_div_pmad_2_0;
    u8     cfg_vco_div_mode_1_0;
    u8     cfg_pre_divsel_1_0;
    u8     cfg_sel_div_3_0;
    u8     r_multi_lane_mode;
    u8     ln_cfg_pma_tx_ck_bitwidth_2_0;
    u8     ln_cfg_tx_prediv_1_0;
    u8     ln_cfg_rxdiv_sel_2_0;
    u8     ln_cfg_tx_subrate_2_0;
    u8     ln_cfg_rx_subrate_2_0;
    u8     ln_cfg_erramp_pd ;
    u8     ln_cfg_ecdr_pd;
    u8     ln_cfg_itx_ipdriver_base_2_0;
    u8     ln_cfg_dmux_pd;
    u8     ln_cfg_pd_cml;
    u8     ln_cfg_pd_driver;
    u8     ln_cfg_rx_reg_pu;
    u8     ln_cfg_pd_rms_det;
    u8     ln_cfg_dcdr_pd;
    u8     ln_cfg_pd_sq;
    u8     ln_cfg_iscan_en;
    u8     ln_cfg_en_fast_iscan;
    u8     ln_cfg_dmux_clk_pd;
    u8     ln_cfg_pi_en;
    u8     ln_cfg_pd_ctle;
    u8     ln_cfg_summer_en;
    u8     ln_cfg_pmad_ck_pd;
    u8     ln_cfg_pd_clk;
    u8     ln_cfg_filter2nd_yz_6_0;
    u8     ln_cfg_tx_reserve_15_8;
    u8     ln_cfg_tx_reserve_7_0;
    u8     ln_cfg_bw_1_0;
    u8     ln_cfg_txcal_man_en;
    u8     ln_cfg_txcal_shift_code_5_0;
    u8     ln_cfg_txcal_valid_sel_3_0;
    u8     ln_cfg_cdr_kf_2_0;
    u8     ln_cfg_cdr_m_7_0;
    u8     ln_cfg_pi_bw_3_0;
    u8     ln_cfg_dis_2ndorder;
    u8     ln_cfg_ctle_rstn;
    u8     ln_cfg_rx_reserve_7_0;
    u8     ln_cfg_rx_reserve_15_8;
    u8     ln_cfg_rxterm_2_0;
    u8     ln_cfg_sum_setcm_en;
    u8     ln_cfg_init_pos_iscan_6_0;
    u8     ln_cfg_init_pos_ipi_6_0;
    u8     ln_cfg_dfedig_m_2_0;
    u8     ln_cfg_en_dfedig;
    u8     ln_cfg_rstn_dfedig;
    u8     ln_cfg_cdrck_en;
} phy25g_serdes_conf_data_t;

mepa_rc  lan80xx_serdes_data_init(mepa_device_t  *dev, mepa_port_speed_t speed, phy25g_serdes_conf_data_t *serdes_data);

ioreg_blk *_lan80xx_ioreg(ioreg_blk *io, uint16_t dev, mepa_bool_t is32, uint32_t off);


mepa_rc lan80xx_csr_rd(const mepa_device_t            *dev,
                       const mepa_port_no_t        port_no,
                       const uint32_t              mmd_dev,
                       mepa_bool_t                  is32,
                       const uint32_t              addr,
                       uint32_t                    *const value);

mepa_rc lan80xx_csr_rd_64(const mepa_device_t         *dev,
                          const mepa_port_no_t        port_no,
                          const uint32_t              mmd_dev,
                          mepa_bool_t                 is32,
                          const uint32_t              addr,
                          uint64_t                    *const value);

mepa_rc lan80xx_csr_wr(const mepa_device_t         *dev,
                       const mepa_port_no_t        port_no,
                       const uint32_t              mmd_dev,
                       mepa_bool_t                 is32,
                       const uint32_t              addr,
                       uint32_t                    const value);

mepa_rc _lan80xx_csr_read(const mepa_device_t *dev,
                          const mepa_port_no_t        port_no,
                          ioreg_blk                   *io_reg,
                          uint32_t                    *const value);

mepa_rc _lan80xx_csr_rd_64(const mepa_device_t     *dev,
                           const mepa_port_no_t    port_no,
                           ioreg_blk               *reg,
                           u64                     *value);

mepa_rc _lan80xx_csr_write(const mepa_device_t *dev,
                           const mepa_port_no_t        port_no,
                           ioreg_blk                   *io_reg,
                           uint32_t                    const value);

mepa_rc _lan80xx_csr_warm_wrm(const mepa_device_t *dev,
                              const mepa_port_no_t port_no,
                              ioreg_blk *io,
                              uint32_t value,
                              uint32_t mask,
                              uint32_t chk_mask,
                              const char *function,
                              const uint16_t line);

mepa_rc _lan80xx_csr_wrm(const mepa_device_t          *dev,
                         const mepa_port_no_t        port_no,
                         ioreg_blk                   *io_reg,
                         uint32_t                    const value,
                         uint32_t                    mask);


mepa_rc _lan80xx_csr_warm_wr(const mepa_device_t *dev,
                             const mepa_port_no_t port_no,
                             ioreg_blk *io_reg,
                             uint32_t value,
                             const char *function,
                             const uint16_t line);




#define LAN80XX_BASE_DEV(data, base_dev, base_data ) \
    { \
        if (!data->base_dev) {         \
            return MEPA_RC_ERROR;      \
        }                              \
        base_dev = data->base_dev; \
        base_data =  (phy25g_phy_state_t *)base_dev->data; \
     }\
 
#define LAN80XX_CSR_RD(dev,port, io_reg, value)                      \
    {                                                                \
       mepa_rc __rc = lan80xx_csr_rd(dev,port, io_reg->mmd, io_reg->is32, io_reg->addr, value);\
        if (__rc != MEPA_RC_OK)                                       \
            return __rc;                                               \
    }                                                           \
 
#define LAN80XX_CSR_WR(dev,port, io_reg, value)                 \
    {                                                              \
      mepa_rc __rc = lan80xx_csr_wr(dev, port, io_reg->mmd, io_reg->is32, io_reg->addr, value); \
        if (__rc != MEPA_RC_OK)           \
            return __rc;                  \
    }

#define LAN80XX_CSR_WRM(p, io_reg, value, mask) \
    { \
        mepa_rc __rc = _lan80xx_csr_wrm(dev, p, io_reg, value, mask); \
        if (__rc != MEPA_RC_OK)                  \
            return __rc;                         \
    }

#define LAN80XX_CSR_EVENT_WRM(p, io_reg_mask, io_reg_sticky, value, mask) \
    { \
        mepa_rc __rc = _lan80xx_csr_wrm(dev, p, io_reg_mask, value, mask); \
        if (__rc != MEPA_RC_OK)                  \
            return __rc;                         \
        __rc = _lan80xx_csr_wrm(dev, p, io_reg_sticky, value, mask); \
        if (__rc != MEPA_RC_OK)                  \
            return __rc;                         \
    }

#define LAN80XX_CSR_COLD_WR(p, io_reg, value)                 \
    {\
    mepa_rc __rc;\
      mepa_device_t *dev_temp = (io_reg->mmd == 0x1e) ? data->base_dev : dev; \
      if (!data->sync_calling_private) {\
          __rc = lan80xx_csr_wr(dev_temp, p, io_reg->mmd, io_reg->is32, io_reg->addr, value); \
          if (__rc != MEPA_RC_OK)                                 \
            return __rc;                  \
      } \
    }

#define LAN80XX_CSR_COLD_WRM(p, io_reg, value, mask) \
    { \
        mepa_rc __rc;\
      if (!data->sync_calling_private) {\
         __rc = _lan80xx_csr_wrm(dev, p, io_reg, value, mask); \
        if (__rc != MEPA_RC_OK)                  \
            return __rc;                         \
      } \
    }


#define LAN80XX_MACSEC_CNT64_RD(dev,port_no, reg, value)                       \
    do {                                                                       \
       mepa_rc __rc = _lan80xx_csr_rd_64(dev, port_no, reg, value);            \
       if (__rc != MEPA_RC_OK) {                                               \
           return __rc;                                                        \
       }                                                                       \
    } while (0)

/* ================================================================= *
 *  Warm Start Functions
 * ================================================================= */

#define LAN80XX_CSR_WARM_WR(p, io_reg, value)                 \
    {\
        mepa_rc __rc = _lan80xx_csr_warm_wr(dev, p, io_reg, value, __FUNCTION__, __LINE__); \
        if (__rc != MEPA_RC_OK)           \
            return __rc;                  \
    }

#define LAN80XX_CSR_WARM_WRM(p, io_reg, value, mask) \
    { \
        mepa_rc __rc = _lan80xx_csr_warm_wrm(dev, p, io_reg, value, mask, 0xFFFFFFFF, __FUNCTION__, __LINE__); \
        if (__rc != MEPA_RC_OK)                  \
            return __rc;                         \
    }

/* ================================================================= *
 *  Other Helper MACROS
 * ================================================================= */

/* Call function in cold start mode only */
#define LAN80XX_RC_COLD(expr) (data->warm_start_cur ? MEPA_RC_OK : (expr))


// Locking Macros
// The variable 'dev' is passed as macro argument to obtain callback pointers and call actual
//lock functions. It does not indicate locks per port.

#define MEPA_ENTER(dev) {                            \
    mepa_lock_t lock;                                \
    lock.function = __FUNCTION__;                    \
    lock.file = __FILE__;                            \
    lock.line = __LINE__;                            \
    if ((dev)->callout->lock_enter != NULL) {          \
        (dev)->callout->lock_enter(&lock);             \
    }                                                \
}

#define MEPA_EXIT(dev) {                             \
    mepa_lock_t lock;                                \
    lock.function = __FUNCTION__;                    \
    lock.file = __FILE__;                            \
    lock.line = __LINE__;                            \
    if ((dev)->callout->lock_exit != NULL) {           \
        (dev)->callout->lock_exit(&lock);              \
    }                                                \
}


mepa_rc lan80xx_phy_mac_conf_set(const mepa_device_t  *dev, mepa_port_no_t port_no, mepa_bool_t enable);

mepa_bool_t lan80xx_target_reg_width(uint16_t target, uint32_t addr);

mepa_rc lan80xx_kr_aneg_enable(mepa_device_t *dev, mepa_port_no_t port_no, const mepa_conf_t *config);

mepa_rc lan80xx_identify_phy(mepa_device_t *dev, mepa_port_no_t port_no);

mepa_rc lan80xx_set_opertaing_mode(mepa_device_t *dev, mepa_port_no_t port, phy25g_port_mode_t  mode);


mepa_rc lan80xx_prbs_generator_conf_set(mepa_device_t *dev, mepa_bool_t enable, mepa_phy_prbs_type_t type, mepa_phy_prbs_direction_t direction,
                                        const mepa_phy_prbs_generator_conf_t *const prbs_conf);

mepa_rc lan80xx_prbs_monitor_conf_set(mepa_device_t *dev, mepa_phy_prbs_type_t type, mepa_phy_prbs_direction_t direction,
                                      const mepa_phy_prbs_monitor_conf_t *const conf_value);

mepa_rc lan80xx_prbs_monitor_status_get(mepa_device_t *dev, mepa_phy_prbs_type_t type, mepa_phy_prbs_direction_t direction,
                                        mepa_phy_prbs_monitor_conf_t *const mon_status);


mepa_rc lan80xx_gpio_mode_set_priv(mepa_device_t                 *dev,
                                   const mepa_port_no_t            port_no,
                                   const mepa_gpio_conf_t         *gpio_conf);

mepa_rc lan80xx_gpio_read_priv(mepa_device_t        *dev,
                               mepa_port_no_t       port_no,
                               uint8_t              gpio_no,
                               mepa_bool_t          *const value);

mepa_rc lan80xx_gpio_write_priv(mepa_device_t   *dev,
                                mepa_port_no_t  port_no,
                                uint8_t         gpio_no,
                                mepa_bool_t     value);

mepa_rc lan80xx_phy_i2c_write_priv(mepa_device_t  *dev,
                                   const mepa_port_no_t  port_no,
                                   const uint8_t         reg_addr,
                                   uint8_t               cnt,
                                   const uint8_t         *const value);

mepa_rc lan80xx_phy_i2c_read_priv(mepa_device_t         *dev,
                                  const mepa_port_no_t  port_no,
                                  const uint8_t         reg_addr,
                                  uint8_t               cnt,
                                  uint8_t               *const value);

mepa_rc lan80xx_loopback_set_priv(mepa_device_t         *dev,
                                  const mepa_port_no_t  port_no,
                                  const mepa_loopback_t *loopback);

mepa_rc lan80xx_power_set_priv(mepa_device_t           *dev,
                               const mepa_port_no_t    port_no,
                               const phy25g_power_t    power);


mepa_rc lan80xx_block_reset_priv(mepa_device_t *dev);

mepa_rc lan80xx_kr_reg_dump(mepa_device_t            *dev,
                            const mepa_port_no_t     port_no,
                            const mepa_debug_print_t pr);

mepa_rc lan80xx_pma_reg_dump(mepa_device_t            *dev,
                             const mepa_port_no_t     port_no,
                             const mepa_debug_print_t pr);

mepa_rc lan80xx_pcs_reg_dump(mepa_device_t            *dev,
                             const mepa_port_no_t     port_no,
                             const mepa_debug_print_t pr);

mepa_rc lan80xx_gpio_glb_slice_reg_dump(mepa_device_t            *dev,
                                        const mepa_port_no_t     port_no,
                                        const mepa_debug_print_t pr);

mepa_rc lan80xx_mac_reg_dump(mepa_device_t            *dev,
                             const mepa_port_no_t     port_no,
                             const mepa_debug_print_t pr);

mepa_rc lan80xx_pmac_config(const mepa_device_t *dev, mepa_port_no_t port_no, const mepa_bool_t enable);

mepa_rc lan80xx_ptp_block_preempt_conf(mepa_device_t *dev, mepa_port_no_t port_no, const mepa_bool_t enable);

mepa_rc lan80xx_reset_point(mepa_device_t *dev, const mepa_reset_param_t *rst_conf);

mepa_rc lan80xx_glb_workarround(mepa_device_t *dev, mepa_port_no_t port_no);

mepa_rc lan80xx_channel_workarround(mepa_device_t *dev, mepa_port_no_t port_no);

mepa_rc lan80xx_warmrestart_conf_get_priv(mepa_device_t *dev);

mepa_rc lan80xx_restart_type_set(mepa_device_t *dev);

mepa_rc lan80xx_operating_mode_set_priv(const mepa_device_t *dev,
                                        const mepa_port_no_t port_no,
                                        phy25g_oper_mode_t phy_mode);

mepa_rc lan80xx_status_get_priv(const mepa_device_t     *dev,
                                const mepa_port_no_t    port_no,
                                phy25g_status_t         *const status);

mepa_rc lan80xx_temp_sensor_get_priv(mepa_device_t          *dev,
                                     const mepa_port_no_t   port_no,
                                     i16                    *const value);

mepa_rc lan80xx_rckout_conf_get_priv(mepa_device_t     *dev,
                                     const mepa_port_no_t    port_no,
                                     phy_25g_rckout_conf_t *const rckout_conf_a,
                                     phy_25g_rckout_conf_t *const rckout_conf_b);

mepa_rc lan80xx_rckout_conf_set_priv(mepa_device_t *dev,
                                     const mepa_port_no_t port_no,
                                     const phy_25g_rckout_conf_t *rckout_conf);


mepa_rc lan80xx_rx_eye_scan_conf_set_priv (const mepa_device_t          *dev,
                                           const mepa_port_no_t         port_no,
                                           mepa_bool_t                  is_line,
                                           const phy25g_rx_eye_scan_t   conf);

mepa_rc lan80xx_rx_eye_scan_status_get_priv (const mepa_device_t                *dev,
                                             const mepa_port_no_t               port_no,
                                             const phy25g_rx_eye_scan_t         scan,
                                             phy25g_rx_eye_scan_status_t        *const status);

mepa_rc lan80xx_phy_tx_rx_equalization_status_get_priv(const mepa_device_t        *dev,
                                                       const mepa_port_no_t       port_no,
                                                       mepa_bool_t                is_line,
                                                       phy25g_tx_rx_equ_status_t  *const status);

mepa_rc lan80xx_phy_tx_rx_equalization_set_priv(const mepa_device_t              *dev,
                                                const mepa_port_no_t             port_no,
                                                mepa_bool_t                      is_line,
                                                const phy25g_tx_rx_equa_conf_t   *const conf);

mepa_rc lan80xx_phy_i2c_init_priv(mepa_device_t         *dev,
                                  const mepa_port_no_t  port_no,
                                  const u8              client_id,
                                  const u16             prescalar);

mepa_rc lan80xx_phy_loopback_conf_set_priv(mepa_device_t            *dev,
                                           const mepa_port_no_t     port_no,
                                           const phy25g_lp_types_t  *loopback);

mepa_rc lan80xx_phy_loopback_conf_get_priv(mepa_device_t         *dev,
                                           const mepa_port_no_t  port_no,
                                           phy25g_lp_get_t       *const loopback);

mepa_rc lan80xx_pkt_gen_conf_priv(const mepa_device_t    *dev,
                                  const mepa_port_no_t   port_no,
                                  const phy25g_pkt_gen_conf_t  *const conf);

mepa_rc lan80xx_pkt_mon_conf_priv(const mepa_device_t   *dev,
                                  const mepa_port_no_t  port_no,
                                  mepa_bool_t           mon_enable,
                                  phy25g_pkt_mon_rst_t  reset_cnt);

mepa_rc lan80xx_pkt_mon_get_priv(const mepa_device_t   *dev,
                                 const mepa_port_no_t  port_no,
                                 mepa_bool_t           *const mon_enable,
                                 phy25g_pkt_mon_rst_t  *const reset_cnt);

mepa_rc lan80xx_pkt_mon_counters_get_priv(const mepa_device_t        *dev,
                                          const mepa_port_no_t       port_no,
                                          mepa_bool_t                ts_rd,
                                          phy25g_pkt_mon_counters_t  *const pkt_counters,
                                          phy25g_timestamp_val_t     *const ts_packet);

mepa_rc lan80xx_temp_sensor_get_priv(mepa_device_t          *dev,
                                     const mepa_port_no_t   port_no,
                                     i16                    *const value);

mepa_rc lan80xx_event_conf_set_priv(mepa_device_t          *dev,
                                    const mepa_port_no_t   port_no,
                                    const phy25g_event_conf_t evt_conf);

mepa_rc lan80xx_event_conf_get_priv(mepa_device_t          *dev,
                                    const mepa_port_no_t   port_no,
                                    phy25g_events_t   *const evt);

mepa_rc lan80xx_event_poll_priv(mepa_device_t          *dev,
                                const mepa_port_no_t   port_no,
                                phy25g_events_t        *const evt);

mepa_rc lan80xx_phy_csr_write_priv(mepa_device_t               *dev,
                                   const mepa_port_no_t        port_no,
                                   const u32                   mmd,
                                   const u32                   addr,
                                   const u32                   value);

mepa_rc lan80xx_phy_csr_read_priv(mepa_device_t               *dev,
                                  const mepa_port_no_t        port_no,
                                  const u16                   mmd,
                                  const u32                   addr,
                                  u32                         *const value);

mepa_rc lan80xx_pmac_counters_get_priv(mepa_device_t                  *dev,
                                       const mepa_port_no_t           port_no,
                                       mepa_bool_t                    is_host,
                                       phy25g_pmac_counters_t         *const counters);


mepa_rc lan80xx_pmac_counters_clear_priv(mepa_device_t                  *dev,
                                         const mepa_port_no_t           port_no,
                                         mepa_bool_t                    is_host);

mepa_rc lan80xx_ext_event_conf_set_priv(mepa_device_t                 *dev,
                                        const mepa_port_no_t          port_no,
                                        const phy25g_ext_event_conf_t     ext_evt_conf);

mepa_rc lan80xx_ext_event_conf_get_priv(mepa_device_t          *dev,
                                        const mepa_port_no_t   port_no,
                                        phy25g_ext_events_t    *const ext_evt);

mepa_rc lan80xx_ext_event_poll_priv(mepa_device_t          *dev,
                                    const mepa_port_no_t   port_no,
                                    phy25g_ext_events_t    *const ext_evt);

mepa_rc lan80xx_conf_set_priv(struct mepa_device *dev, const mepa_conf_t *config);

mepa_rc lan80xx_mamcsec_mem_free(mepa_device_t *dev);

uint32_t lan80xx_phy_capability_priv(struct mepa_device *dev, uint32_t capability);

mepa_rc lan80xx_flow_control_set_priv(const mepa_device_t     *dev,
                                      mepa_port_no_t          port_no,
                                      mepa_bool_t             enable);

mepa_rc lan80xx_serdes_configuration(mepa_device_t *dev, mepa_port_no_t port_no, mepa_port_speed_t speed, phy25g_port_mode_t  *mode);

mepa_rc lan80xx_check_mcu_rdy_priv(mepa_device_t *dev);

mepa_rc lan80xx_post1_init_priv(mepa_device_t   *dev, mepa_port_no_t port_no);

mepa_bool_t lan80xx_driver_check(const mepa_device_t   *dev);

mepa_rc lan80xx_xconnect_conf_get_priv(mepa_device_t  *dev, mepa_port_no_t port_no, phy25g_xconnect_get_conf_t  *const conf);

mepa_rc lan80xx_fw_update_priv(mepa_device_t *dev);

mepa_rc lan80xx_mcu_reset_priv(const mepa_device_t *dev);

mepa_rc lan80xx_mcu_mailbox_init_priv(const mepa_device_t *dev, u32 u32McuIntMask, u32 u32HostIntMask);

typedef struct DeviceInfo DEVICE_INFO;

typedef struct OTPRAMUpdatedDB OTPRAMUpdatedDB_t;

typedef enum OTP_Key_Counter enOTP_ACTIVE_KEY;

typedef enum SD_CFG_SPEED_IDX SD_CFG_SPEED_IDX_t;

typedef enum SERDES_CFG eSERDES_CFG_T;

typedef struct SERDES_CONFIG __SERDES_CONFIG_T;

mepa_rc lan80xx_get_fw_info_priv(const mepa_device_t *dev, DEVICE_INFO *psDevInfo);

uint16_t lan80xx_CreatePacket(uint8_t u8PacketId, uint16_t u16CmdParamLen, uint8_t *pu8PktBuf, uint8_t *pu8CmdData, uint8_t u8Reserved);
mepa_rc lan80xx_MB_SendRequest(const mepa_device_t *dev, uint8_t *au8CmdPkt, uint16_t u16DataLen);
mepa_rc lan80xx_MB_ReadResponse(const mepa_device_t *dev, uint8_t *u8ResponsePkt, uint16_t *u16PayloadLen, uint16_t u16MailboxTimeout);
mepa_rc lan80xx_ValidatePacket(uint8_t *u8PktBuf);

mepa_rc lan80xx_memory_read_priv(const mepa_device_t *dev, uint32_t u32Addres, uint8_t *pu8Data, const uint16_t u16Len);
mepa_rc lan80xx_memory_write_priv(const mepa_device_t *dev, uint32_t u16Addres, uint8_t *pu8Data, const u16 u16Len);

mepa_rc lan80xx_otp_cfg_program_priv(const mepa_device_t  *dev, u8 *pu8OTPBuffer, OTPRAMUpdatedDB_t *pCfgUpdates, u8 u8UpdateCnt);

mepa_rc lan80xx_otp_cfg_read_priv(const mepa_device_t  *dev, u8 u8RecIdx, u8 *pu8Cfg, u16 *pu16Len);

mepa_rc lan80xx_otp_prog_RepKey_priv(const mepa_device_t  *dev, u8 *pu8SignedKey, u8 *pu8OTPBuffer, OTPRAMUpdatedDB_t *pCfgUpdates, u8 u8UpdateCnt);

mepa_rc lan80xx_otp_revoke_ROTKey_priv(const mepa_device_t  *dev, u8 *pu8OTPBuffer, OTPRAMUpdatedDB_t *pCfgUpdates, u8 u8UpdateCnt);

mepa_rc lan80xx_otp_revoke_AllKeys_priv(const mepa_device_t  *dev, u8 *pu8OTPBuffer, OTPRAMUpdatedDB_t *pCfgUpdates, u8 u8UpdateCnt);

mepa_rc lan80xx_otp_getKey_Status_priv(const mepa_device_t  *dev, enOTP_ACTIVE_KEY *pKey);

mepa_rc lan80xx_otp_read_priv(const mepa_device_t  *dev, u8 *pu8Data, u16 u16Offset, const u16 u16Len);

mepa_rc lan80xx_otp_write_priv(const mepa_device_t  *dev,
                               u8 *pu8Data,
                               u16 u16Offset,
                               const u16 u16Len,
                               u8 u8WriteMode);

mepa_rc lan80xx_get_serdes_config_priv(const mepa_device_t *dev,
                                       SD_CFG_SPEED_IDX_t speed,
                                       eSERDES_CFG_T cfgType,
                                       __SERDES_CONFIG_T *const data);

mepa_rc lan80xx_set_serdes_config_priv(const mepa_device_t *dev,
                                       SD_CFG_SPEED_IDX_t speed,
                                       eSERDES_CFG_T cfgType,
                                       const __SERDES_CONFIG_T *data);

mepa_rc lan80xx_KRLog_Enable_priv(const mepa_device_t *dev,
                                  mepa_bool_t bkrlog_enable,
                                  mepa_bool_t bline_port_en,
                                  mepa_bool_t  bhost_port_en);

mepa_rc lan80xx_KRLog_Reset_priv(const mepa_device_t *dev,
                                 uint32_t u32KRLogOffset,
                                 uint16_t u16Len);

mepa_rc lan80xx_clause37_conf_set_priv(mepa_device_t        *dev,
                                       mepa_port_no_t       port_no,
                                       mepa_cl37_conf_t     *cl37_conf);

#endif //_MEPA_LAN80XX_PRIVATE_H_
