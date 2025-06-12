
// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT
#ifndef __LAN_STUBS__
#define __LAN_STUBS__

#include "mepa_driver.h"
#include <stdint.h>
#include <microchip/ethernet/phy/api.h>
#include "microchip/lan80xx.h"
#include "microchip/lan80xx_mcu.h"
#include "microchip/lan80xx_ts.h"

#ifndef MEPA_HAS_LAN80XX
mepa_rc lan80xx_operating_mode_set(const mepa_device_t *dev,
                                   const mepa_port_no_t port_no,
                                   phy25g_oper_mode_t phy_mode)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_flow_control_set(const mepa_device_t     *dev,
                                 mepa_port_no_t          port_no,
                                 mepa_bool_t             enable)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_rckout_conf_set(mepa_device_t *dev,
                                const mepa_port_no_t port_no,
                                const phy_25g_rckout_conf_t *rckout_conf)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_rckout_conf_get(mepa_device_t *dev,
                                const mepa_port_no_t port_no,
                                phy_25g_rckout_conf_t *const rckout_conf_a,
                                phy_25g_rckout_conf_t *const rckout_conf_b)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_status_get(const mepa_device_t *dev,
                           const mepa_port_no_t port_no,
                           phy25g_status_t *const status)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_rx_eye_scan_conf_set (const mepa_device_t          *dev,
                                      const mepa_port_no_t         port_no,
                                      mepa_bool_t                  is_line,
                                      const phy25g_rx_eye_scan_t   conf)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_rx_eye_scan_status_get (const mepa_device_t                *dev,
                                        const mepa_port_no_t               port_no,
                                        const phy25g_rx_eye_scan_t         scan,
                                        phy25g_rx_eye_scan_status_t        *const status)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_phy_tx_rx_equalization_status_get(const mepa_device_t       *dev,
                                                  const mepa_port_no_t      port_no,
                                                  mepa_bool_t               is_line,
                                                  phy25g_tx_rx_equ_status_t *const status)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_phy_tx_rx_equalization_set(const mepa_device_t             *dev,
                                           const mepa_port_no_t            port_no,
                                           mepa_bool_t                     is_line,
                                           const phy25g_tx_rx_equa_conf_t  *const conf)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_phy_i2c_init(mepa_device_t *dev,
                             const mepa_port_no_t port_no,
                             const u8 client_id,
                             const u16 prescalar)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_phy_loopback_conf_set(mepa_device_t *dev,
                                      const mepa_port_no_t port_no,
                                      const phy25g_lp_types_t *loopback)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_phy_loopback_conf_get(mepa_device_t *dev,
                                      const mepa_port_no_t port_no,
                                      phy25g_lp_get_t *const loopback)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_temp_sensor_init(mepa_device_t *dev,
                                 const mepa_port_no_t port_no,
                                 u8 threshold,
                                 mepa_bool_t enable)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_pkt_gen_conf(const mepa_device_t *dev,
                             const mepa_port_no_t port_no,
                             const phy25g_pkt_gen_conf_t  *const conf)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_pkt_mon_conf(const mepa_device_t *dev,
                             const mepa_port_no_t  port_no,
                             mepa_bool_t mon_enable,
                             phy25g_pkt_mon_rst_t reset_cnt)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_pkt_mon_get(const mepa_device_t   *dev,
                            const mepa_port_no_t  port_no,
                            mepa_bool_t           *const mon_enable,
                            phy25g_pkt_mon_rst_t  *const reset_cnt)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_pkt_mon_counters_get(const mepa_device_t *dev,
                                     const mepa_port_no_t port_no,
                                     mepa_bool_t ts_rd,
                                     phy25g_pkt_mon_counters_t *const pkt_counters,
                                     phy25g_timestamp_val_t *const ts_packet)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_temp_sensor_get(mepa_device_t *dev,
                                const mepa_port_no_t  port_no,
                                i16 *const value)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_ext_event_conf_set(mepa_device_t *dev,
                                   const mepa_port_no_t port_no,
                                   phy25g_ext_event_conf_t ext_evt)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_ext_event_conf_get(mepa_device_t          *dev,
                                   const mepa_port_no_t   port_no,
                                   phy25g_ext_events_t    *const ext_evt)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_ext_event_poll(mepa_device_t          *dev,
                               const mepa_port_no_t   port_no,
                               phy25g_ext_events_t    *const ext_evt)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_event_conf_get(mepa_device_t *dev,
                               const mepa_port_no_t port_no,
                               phy25g_events_t *const evt)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_event_poll(mepa_device_t *dev,
                           const mepa_port_no_t port_no,
                           phy25g_events_t *const evt)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_event_conf_set(mepa_device_t *dev,
                               const mepa_port_no_t port_no,
                               const phy25g_event_conf_t  evt_set)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_pmac_counters_get(mepa_device_t                  *dev,
                                  const mepa_port_no_t           port_no,
                                  mepa_bool_t                    is_host,
                                  phy25g_pmac_counters_t         *const counters)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}


mepa_rc lan80xx_pmac_counters_clear(mepa_device_t                  *dev,
                                    const mepa_port_no_t           port_no,
                                    mepa_bool_t                    is_host)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_phy_csr_write(mepa_device_t               *dev,
                              const mepa_port_no_t        port_no,
                              const u32                   mmd,
                              const u32                   addr,
                              const u32                   value)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_phy_csr_read(mepa_device_t               *dev,
                             const mepa_port_no_t        port_no,
                             const u16                   mmd,
                             const u32                   addr,
                             u32                         *const value)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_xconnect_anylinetoanyhost(mepa_device_t *dev, mepa_port_no_t port_no, mepa_bool_t xconnect_enable, u8 LineDefaultCh[MAX_PORTS])
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_xconnect_hostfailover_Protection(mepa_device_t  *dev, mepa_port_no_t port_no, const phy25g_autofailover_t *conf)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_xconnect_failover(mepa_device_t *dev, const mepa_port_no_t port_no)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_xconnect_force_failover(mepa_device_t *dev, const mepa_port_no_t port_no)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_xconnect_conf_get(mepa_device_t *dev, const mepa_port_no_t port_no, phy25g_xconnect_get_conf_t *const get_conf)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_mpls_config_set(mepa_device_t *dev,
                                const mepa_port_no_t  port_no,
                                BOOL ingress_flow, uint16_t flow_index,
                                BOOL in_cw_en, const phy25g_ts_mpls_flow_conf_t *const mpls_conf)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_phy_ts_pps_input_confset(mepa_device_t *dev, const mepa_port_no_t    port_no, const  phy25g_pps_input_conf_t *const pin_conf)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_phy_ts_load_store_contoller_set(mepa_device_t *dev, const mepa_port_no_t  port_no, uint8_t  ls_controller_sel)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_phy_ts_pps_ouput_conf_set(mepa_device_t *dev, const mepa_port_no_t  port_no, const phy25g_pps_output_conf_t *const pps_out_conf)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_phy_ts_sertod_input_confset(mepa_device_t *dev, const mepa_port_no_t    port_no, const  phy25g_ts_sertod_input_conf_t *const sertod_conf)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_phy_ts_sertod_output_confset(mepa_device_t *dev, const mepa_port_no_t    port_no, const  phy25g_ts_sertod_output_conf_t *const sertod_conf)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_phy_ts_epps_conf_set(mepa_device_t *dev, const mepa_port_no_t    port_no, const  phy25g_ts_epps_conf_t *const epps_conf)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_phy_ts_ptptime_adj_delta(mepa_device_t  *dev, const mepa_port_no_t  port_no, phy25g_ts_ltc_delta_adj_cfg *const phy25g_ltc_tod_adj)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_MB_INTR_register_callback(const mepa_device_t *dev,
                                          gpio_callback_t gpio_cb)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_mcu_mailbox_init(const mepa_device_t *dev,
                                 u32 u32McuIntMask,
                                 u32 u32HostIntMask)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_otp_cfg_program(const mepa_device_t  *dev,
                                u8 *pu8OTPBuffer,
                                OTPRAMUpdatedDB_t *pCfgUpdates,
                                u8 u8UpdateCnt)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_otp_cfg_read(const mepa_device_t  *dev,
                             u8 u8RecIdx,
                             u8 *pu8Cfg,
                             u16 *pu16Len)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}


mepa_rc lan80xx_otp_prog_RepKey(const mepa_device_t  *dev,
                                u8 *pu8SignedKey,
                                u8 *pu8OTPBuffer,
                                OTPRAMUpdatedDB_t *pCfgUpdates,
                                u8 u8UpdateCnt)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_otp_revoke_ROTKey(const mepa_device_t  *dev,
                                  u8 *pu8OTPBuffer,
                                  OTPRAMUpdatedDB_t *pCfgUpdates,
                                  u8 u8UpdateCnt)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_otp_revoke_AllKeys(const mepa_device_t  *dev,
                                   u8 *pu8OTPBuffer,
                                   OTPRAMUpdatedDB_t *pCfgUpdates,
                                   u8 u8UpdateCnt)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_otp_getKey_Status(const mepa_device_t  *dev,
                                  enOTP_ACTIVE_KEY *pKey)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_otp_read(const mepa_device_t  *dev,
                         u8 *pu8Data,
                         u16 u16Offset,
                         const u16 u16Len)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_mcu_reset(const mepa_device_t *dev)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_get_fw_info(const mepa_device_t *dev,
                            DEVICE_INFO *psDevInfo)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}


mepa_rc lan80xx_memory_read(const mepa_device_t *dev,
                            uint32_t u32Addres,
                            uint8_t *pu8Data,
                            const uint16_t u16Len)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_memory_write(const mepa_device_t *dev,
                             uint32_t u16Addres,
                             uint8_t *pu8Data,
                             const u16 u16Len)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_fw_update(mepa_device_t *dev)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_get_serdes_config(const mepa_device_t *dev,
                                  SD_CFG_SPEED_IDX_t speed,
                                  eSERDES_CFG_T      cfgType,
                                  __SERDES_CONFIG_T *const data)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_set_serdes_config(const mepa_device_t *dev,
                                  SD_CFG_SPEED_IDX_t   speed,
                                  eSERDES_CFG_T        cfgType,
                                  const __SERDES_CONFIG_T *data)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_phy_ts_fifo_get(mepa_device_t *dev, const mepa_port_no_t    port_no,
                                phy25g_ts_fifo_entry_t ts_list[], const size_t   size, uint32_t   *const num)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_phy_ts_fifo_sig_set(mepa_device_t *dev, const mepa_port_no_t  port_no,
                                    const phy25g_ts_fifo_sig_mask_t sig_mask)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}
mepa_rc lan80xx_xconnect_failover_conf_get(mepa_device_t  *dev,
                                           const mepa_port_no_t   port_no,
                                           phy25g_autofailover_t  *const conf)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}
#if 0
mepa_rc lan80xx_ANEG_GetConfig(const mepa_device_t  *dev,
                               KR_PORT_CONF *psConfig)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_ANEG_SetConfig(const mepa_device_t  *dev,
                               KR_PORT sPort,
                               KR_PORT_CONF sConfig)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_ANEG_Enable(const mepa_device_t  *dev)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_ANEG_Disable(const mepa_device_t  *dev)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_KRLog_Enable(const mepa_device_t  *dev,
                             KR_PORT sPort)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_KRLog_Reset(const mepa_device_t  *dev)
{

    return MEPA_RC_NOT_IMPLEMENTED;
}
#endif
#endif
#endif
