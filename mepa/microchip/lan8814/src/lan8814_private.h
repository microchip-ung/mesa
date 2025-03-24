// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_LAN8814_PRIVATE_H_
#define _MEPA_LAN8814_PRIVATE_H_

#include <stdint.h>
#include <microchip/ethernet/phy/api/types.h>
#include <microchip/ethernet/phy/api/phy_ts.h>
#include <microchip/lan8814_cs.h>

#define MEPA_RC(expr) { mesa_rc __rc__ = (expr); if (__rc__ < MESA_RC_OK) return __rc__; }
#define MEPA_RC_ERR(expr, str) { mesa_rc __rc__ = (expr); if (__rc__ < MESA_RC_OK) {T_E(MEPA_TRACE_GRP_GEN, str); return __rc__; }}
#define MEPA_ASSERT(x) if((x)) { return MESA_RC_ERROR;}

#define TRUE  1
#define FALSE 0
#define EXT_PAGE 1 // extended page access
#define MMD_DEV  2 // MMD device access

// cable diagnostics constants
#define LAN8814_CABLE_MODE_POWER_DOWN 2

#define LAN8814_CABLE_NORMAL 0
#define LAN8814_CABLE_OPEN   1
#define LAN8814_CABLE_SHORT  2
#define LAN8814_CABLE_FAIL   3

// register access functions
mepa_rc lan8814_direct_reg_rd(mepa_device_t *dev, uint16_t addr, uint16_t *value);
mepa_rc lan8814_direct_reg_wr(mepa_device_t *dev, uint16_t addr, uint16_t value, uint16_t mask);
mepa_rc lan8814_ext_reg_rd(mepa_device_t *dev, uint16_t page, uint16_t addr, uint16_t *value);
mepa_rc lan8814_ext_reg_wr(mepa_device_t *dev, uint16_t page, uint16_t addr, uint16_t value, uint16_t mask);
mepa_rc lan8814_ext_incr_reg_rd(mepa_device_t *dev, uint16_t page, uint16_t addr, uint16_t *value, mepa_bool_t start_addr);

mepa_rc lan8814_mmd_reg_rd(mepa_device_t *dev, uint16_t mmd, uint16_t addr, uint16_t *value);
mepa_rc lan8814_mmd_reg_wr(mepa_device_t *dev, uint16_t mmd, uint16_t addr, uint16_t value, uint16_t mask);
mepa_rc lan8814_ts_debug_info_dump(struct mepa_device *dev,
                                const mepa_debug_print_t pr,
                                const mepa_debug_info_t   *const info);

//Direct register access macros
#define RD(dev, addr, value) lan8814_direct_reg_rd(dev, addr, value)
#define WR(dev, addr, value) lan8814_direct_reg_wr(dev, addr, value, 0xffff)
#define WRM(dev, addr, val, mask) lan8814_direct_reg_wr(dev, addr, val, mask)

//Extended page register access macros
#define EP_RD(dev, page_addr, value) lan8814_ext_reg_rd(dev, page_addr, value)
#define EP_WR(dev, page_addr, value) lan8814_ext_reg_wr(dev, page_addr, value, 0xffff)
#define EP_WRM(dev, page_addr, value, mask) lan8814_ext_reg_wr(dev, page_addr, value, mask)
#define EP_RD_INCR(dev, page_addr, value, start) lan8814_ext_incr_reg_rd(dev, page_addr, value, start);

//MMD device register access macros
#define MMD_RD(dev, mmd_addr, value) lan8814_mmd_reg_rd(dev, mmd_addr, value)
#define MMD_WR(dev, mmd_addr, value) lan8814_mmd_reg_wr(dev, mmd_addr, value, 0xffff)
#define MMD_WRM(dev, mmd_addr, val, mask) lan8814_mmd_reg_wr(dev, mmd_addr, val, mask)

#define T_D(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_DEBUG, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_I(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_INFO, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_W(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_WARNING, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_E(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_ERROR, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);


// Locking Macros
// The variable 'dev' is passed as macro argument to obtain callback pointers and call actual lock functions. It does not indicate locks per port.
#define MEPA_ENTER(dev) {                            \
    mepa_lock_t lock;                                \
    lock.function = __FUNCTION__;                    \
    lock.file = __FILE__;                            \
    lock.line = __LINE__;                            \
    if (dev->callout->lock_enter) {                  \
        dev->callout->lock_enter(&lock);             \
    }                                                \
}

#define MEPA_EXIT(dev) {                             \
    mepa_lock_t lock;                                \
    lock.function = __FUNCTION__;                    \
    lock.file = __FILE__;                            \
    lock.line = __LINE__;                            \
    if (dev->callout->lock_exit) {                   \
        dev->callout->lock_exit(&lock);              \
    }                                                \
}

typedef struct {
    uint8_t  model;
    uint8_t  rev;
} phy_dev_info_t;

typedef enum {
    LAN8814_TS_MODE_DISABLED = 0,      // PTP functions are disabled
    LAN8814_TS_MODE_STANDALONE = 1,    // PTP Standalone Mode
    LAN8814_TS_MODE_PCH = 2,           // PTP PCH Mode (MCH support disabled)
    LAN8814_TS_MODE_PCHMCH = 3,        // PTP PCH Mode (MCH support enabled)
} lan8814_ts_tsu_op_mode_t;

// Port latencies in ns
typedef struct {
    mepa_timeinterval_t  rx10mbps;
    mepa_timeinterval_t  rx100mbps;
    mepa_timeinterval_t  rx1000mbps;
    mepa_timeinterval_t  tx10mbps;
    mepa_timeinterval_t  tx100mbps;
    mepa_timeinterval_t  tx1000mbps;
} lan8814_ts_port_latencies_t;

typedef struct {
    mepa_bool_t                     tsu_en;            // Port TSU enabled/disabled
    mepa_timeinterval_t             ingress_latency;   //
    mepa_timeinterval_t             egress_latency;    //
    mepa_timeinterval_t             path_delay;        //
    mepa_timeinterval_t             delay_asym;        //
    mepa_ts_scaled_ppb_t            rate_adj;          // clock rate adjustment
    mepa_ts_event_t                 event_mask;        // interrupt mask config
    mepa_ts_pps_conf_t              pps_conf;
    mepa_ts_classifier_t            rx_pkt_conf;
    mepa_ts_classifier_t            tx_pkt_conf;
    mepa_ts_ptp_clock_conf_t        rx_clock_conf;
    mepa_ts_ptp_clock_conf_t        tx_clock_conf;
    lan8814_ts_port_latencies_t        port_latencies;
} lan8814_ts_port_conf_t;

typedef struct {
    mepa_bool_t                   ptp_en;               // Chip PTP enabled/disabled
    lan8814_ts_tsu_op_mode_t         tsu_op_mode;          // TSU operating Mode: Standalone/PCH/PCH-MCH
    mepa_ts_clock_freq_t          clk_freq;             // reference clock frequency */
    mepa_ts_clock_src_t           clk_src;              // clock source
    mepa_ts_rx_timestamp_pos_t    rx_ts_pos;            // Rx timestamp position
    mepa_ts_rx_timestamp_len_t    rx_ts_len;            // Rx timestamp length
    mepa_ts_fifo_timestamp_len_t  tx_fifo_ts_len;       // Tx TS length in FIFO
    mepa_ts_fifo_mode_t           tx_fifo_mode;         // Tx TSFIFO access mode
    lan8814_ts_port_conf_t           ts_port_conf;         // Port specific TSU data
    mepa_bool_t                   tx_spi_en;            // TS access through SPI enaled
    mepa_ts_fifo_read_t           fifo_cb;              // Fifo TS callback
    lan8814_ts_port_latencies_t      default_latencies;    // Default port latencies
    mepa_ts_pps_conf_t            pps;
    mepa_bool_t                   tx_auto_followup_ts;
    mepa_bool_t                   ts_init_done;
    mepa_ts_tc_op_mode_t          tc_op_mode;           // tc mode for correction field update
    mepa_mch_pch_t                mch_pch;
} lan8814_ts_data_t;


typedef struct {
    mepa_bool_t              init_done;
    uint8_t                  packet_idx;
    mepa_port_no_t           port_no;
    mepa_conf_t              conf;
    mepa_event_t             events;
    mepa_loopback_t          loopback;
    mepa_bool_t              qsgmii_phy_aneg_dis;
    phy_dev_info_t           dev;
    mepa_synce_clock_conf_t  synce_conf;
    mepa_device_t            *base_dev; // Pointer to the device of base port on the phy chip
    mepa_bool_t              link_status;
    mepa_port_speed_t        speed_status;
    mepa_bool_t              fdx_status;
    mepa_cable_diag_result_t cable_diag;
    mepa_start_of_frame_conf_t sof_conf;
    mepa_bool_t              framepreempt_en; // Frame Preemption
    mepa_media_mode_t        mdi_mode;
    mepa_bool_t              post_mac_rst;
    mepa_bool_t              aneg_after_link_up;
    mepa_bool_t              crc_workaround;
    lan8814_ts_data_t           ts_state;
    mepa_phy_prbs_generator_conf_t prbs_conf;
    mepa_bool_t              prbs_init;
    mepa_phy_eee_conf_t      eee_conf;
    lan8814_phy_downshift_t  dsh_conf; //Auto downshift configuration(chip specific)
    uint8_t                  loop_cnt; //variable to denote no of times status poll getting called by application when MEPA 555 or MEPA 546 occurs.
    uint8_t                  rep_cnt; //Rate at which application polls a port per sec, for ex: rep_cnt = 10 means 10 times polling will be called per port per sec.
    mepa_bool_t              dsh_complete; //flag to denote downshift operation completed.
    mepa_bool_t              aneg_flag; //flag to denote ANEG restart is completed.
} phy_data_t;

#endif
