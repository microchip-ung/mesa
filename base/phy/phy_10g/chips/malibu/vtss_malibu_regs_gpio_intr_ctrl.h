// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU_REGS_GPIO_INTR_CTRL_H_
#define _VTSS_MALIBU_REGS_GPIO_INTR_CTRL_H_


#include "vtss_malibu_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a GPIO_INTR_CTRL
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a GPIO_INTR_CTRL:GPIO_INTR
 *
 * Not documented
 */


/** 
 * \brief GPIO Output selection
 *
 * \details
 * Selects which internal signal is routed to the corresponding output line
 *
 * Register: \a GPIO_INTR_CTRL:GPIO_INTR:GPIO0_OUT
 */
#define VTSS_GPIO_INTR_CTRL_GPIO_INTR_GPIO0_OUT  VTSS_IOREG(0x01, 0, 0xc010)

/** 
 * \brief
 * Selects which internal signal is routed to the corresponding output line
 *
 * \details 
 * 
 * 0   =  i2c_mstr_module_dataout_o
 * 1   =  i2c_mstr_module_clkout_o
 * 2   =  led_tx_o
 * 3   =  led_rx_o
 * 4   =  rxalarm_o
 * 5   =  txalarm_o
 * 6   =  host_link_up_o
 * 7   =  line_link_up_o
 * 8   =  line_kr_sync8b10b_2gpio
 * 9   =  line_kr_sync10g_2gpio
 * 10  =  rosi_frm_pulse_o
 * 11  =  rosi_sdat_o
 * 12  =  rosi_sclk_o
 * 13  =  tosi_frm_pulse_o
 * 14  =  tosi_sclk_o
 * 15  =  line_pcs1g_link_status
 * 16  =  line_pcs_rx_status_o
 * 17  =  client_pcs1g_link_status
 * 18  =  host_pcs_rx_status
 * 19  =  host_sd10g_ib_signal_detect_i
 * 20  =  line_sd10g_ib_signal_detect_i
 * 21  =  hpcs10g_intr
 * 22  =  lpcs10g_intr
 * 23  =  client_pcs1g_intr
 * 24  =  line_pcs1g_intr
 * 25  =  wis_interrupt0
 * 26  =  host_pmaint_intr
 * 27  =  line_pmaint_intr
 * 28  =  data_activity_tx
 * 29  =  data_activity_rx
 * 30  =  host_data_activity_tx
 * 31  =  host_data_activity_rx
 * 32  =  xgmii_pause_egr_bist_exp4_o
 * 33  =  xgmii_pause_igr_bist_exp4_o
 * 34  =  rx_pcs_pause_o
 * 35  =  tx_pcs_pause_o
 * 36  =  rx_wis_pause_o
 * 37  =  tx_wis_pause_o
 * 38  =  eth_channel_dis_o
 * 39  =  msec_ip1588_sfd_lane_o
 * 40  =  line_s_tx_fault
 * 41  =  (eth_1g_ena ? line_pcs1g_ass_latency_o[0] : ewis_fr_bitpos_o[0])
 * ;
 * 42  =  (eth_1g_ena ? line_pcs1g_ass_latency_o[1] : ewis_fr_bitpos_o[1])
 * ;
 * 43  =  (eth_1g_ena ? line_pcs1g_char_pos_o[0]    : ewis_fr_bitpos_o[2])
 * ;
 * 44  =  (eth_1g_ena ? line_pcs1g_char_pos_o[1]    : ewis_fr_wordpos_o[0])
 * ;
 * 45  =  (eth_1g_ena ? line_pcs1g_char_pos_o[2]    : ewis_fr_wordpos_o[1])
 * ;
 * 46  =  (eth_1g_ena ? line_pcs1g_char_pos_o[3]    : ewis_fr_wordpos_o[2])
 * ;
 * 47  =  macsec_igr_pred_var_lat_o[0]
 * 48  =  macsec_igr_pred_var_lat_o[1]
 * 49  =  kr_active_2gpio
 * 50  =  dft_tx_ena_2gpio
 * 51  =  reserved
 * 52  =  exe_last_2gpio[0]
 * 53  =  exe_last_2gpio[1]
 * 54  =  exe_last_2gpio[2]
 * 55  =  exe_last_2gpio[3]
 * 56  =  exe_last_2gpio[4]
 * 57  =  link_hcd_2gpio[0]
 * 58  =  link_hcd_2gpio[1]
 * 59  =  link_hcd_2gpio[2]
 * 60  =  eth_1g_ena
 * 61  =  host_kr_sync8b10b_2gpio
 * 62  =  host_kr_sync10g_2gpio
 * 63  =  host_kr_active_2gpio

 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_GPIO0_OUT . SEL0
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_GPIO0_OUT_SEL0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_INTR_CTRL_GPIO_INTR_GPIO0_OUT_SEL0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_INTR_CTRL_GPIO_INTR_GPIO0_OUT_SEL0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief GPIO Output selection
 *
 * \details
 * Selects which internal signal is routed to the corresponding output line
 *
 * Register: \a GPIO_INTR_CTRL:GPIO_INTR:GPIO1_OUT
 */
#define VTSS_GPIO_INTR_CTRL_GPIO_INTR_GPIO1_OUT  VTSS_IOREG(0x01, 0, 0xc011)

/** 
 * \brief
 * Selects which internal signal is routed to the corresponding output line
 *
 * \details 
 * 
 * 0   =  i2c_mstr_module_dataout_o
 * 1   =  i2c_mstr_module_clkout_o
 * 2   =  led_tx_o
 * 3   =  led_rx_o
 * 4   =  rxalarm_o
 * 5   =  txalarm_o
 * 6   =  host_link_up_o
 * 7   =  line_link_up_o
 * 8   =  line_kr_sync8b10b_2gpio
 * 9   =  line_kr_sync10g_2gpio
 * 10  =  rosi_frm_pulse_o
 * 11  =  rosi_sdat_o
 * 12  =  rosi_sclk_o
 * 13  =  tosi_frm_pulse_o
 * 14  =  tosi_sclk_o
 * 15  =  line_pcs1g_link_status
 * 16  =  line_pcs_rx_status_o
 * 17  =  client_pcs1g_link_status
 * 18  =  host_pcs_rx_status
 * 19  =  host_sd10g_ib_signal_detect_i
 * 20  =  line_sd10g_ib_signal_detect_i
 * 21  =  hpcs10g_intr
 * 22  =  lpcs10g_intr
 * 23  =  client_pcs1g_intr
 * 24  =  line_pcs1g_intr
 * 25  =  wis_interrupt0
 * 26  =  host_pmaint_intr
 * 27  =  line_pmaint_intr
 * 28  =  data_activity_tx
 * 29  =  data_activity_rx
 * 30  =  host_data_activity_tx
 * 31  =  host_data_activity_rx
 * 32  =  xgmii_pause_egr_bist_exp4_o
 * 33  =  xgmii_pause_igr_bist_exp4_o
 * 34  =  rx_pcs_pause_o
 * 35  =  tx_pcs_pause_o
 * 36  =  rx_wis_pause_o
 * 37  =  tx_wis_pause_o
 * 38  =  eth_channel_dis_o
 * 39  =  msec_ip1588_sfd_lane_o
 * 40  =  line_s_tx_fault
 * 41  =  (eth_1g_ena ? line_pcs1g_ass_latency_o[0] : ewis_fr_bitpos_o[0])
 * ;
 * 42  =  (eth_1g_ena ? line_pcs1g_ass_latency_o[1] : ewis_fr_bitpos_o[1])
 * ;
 * 43  =  (eth_1g_ena ? line_pcs1g_char_pos_o[0]    : ewis_fr_bitpos_o[2])
 * ;
 * 44  =  (eth_1g_ena ? line_pcs1g_char_pos_o[1]    : ewis_fr_wordpos_o[0])
 * ;
 * 45  =  (eth_1g_ena ? line_pcs1g_char_pos_o[2]    : ewis_fr_wordpos_o[1])
 * ;
 * 46  =  (eth_1g_ena ? line_pcs1g_char_pos_o[3]    : ewis_fr_wordpos_o[2])
 * ;
 * 47  =  macsec_igr_pred_var_lat_o[0]
 * 48  =  macsec_igr_pred_var_lat_o[1]
 * 49  =  kr_active_2gpio
 * 50  =  dft_tx_ena_2gpio
 * 51  =  reserved
 * 52  =  exe_last_2gpio[0]
 * 53  =  exe_last_2gpio[1]
 * 54  =  exe_last_2gpio[2]
 * 55  =  exe_last_2gpio[3]
 * 56  =  exe_last_2gpio[4]
 * 57  =  link_hcd_2gpio[0]

 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_GPIO1_OUT . SEL1
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_GPIO1_OUT_SEL1(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_INTR_CTRL_GPIO_INTR_GPIO1_OUT_SEL1     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_INTR_CTRL_GPIO_INTR_GPIO1_OUT_SEL1(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief GPIO Output selection
 *
 * \details
 * Selects which internal signal is routed to the corresponding output line
 *
 * Register: \a GPIO_INTR_CTRL:GPIO_INTR:GPIO2_OUT
 */
#define VTSS_GPIO_INTR_CTRL_GPIO_INTR_GPIO2_OUT  VTSS_IOREG(0x01, 0, 0xc012)

/** 
 * \brief
 * Selects which internal signal is routed to the corresponding output line
 *
 * \details 
 * 
 * 0   =  i2c_mstr_module_dataout_o
 * 1   =  i2c_mstr_module_clkout_o
 * 2   =  led_tx_o
 * 3   =  led_rx_o
 * 4   =  rxalarm_o
 * 5   =  txalarm_o
 * 6   =  host_link_up_o
 * 7   =  line_link_up_o
 * 8   =  line_kr_sync8b10b_2gpio
 * 9   =  line_kr_sync10g_2gpio
 * 10  =  rosi_frm_pulse_o
 * 11  =  rosi_sdat_o
 * 12  =  rosi_sclk_o
 * 13  =  tosi_frm_pulse_o
 * 14  =  tosi_sclk_o
 * 15  =  line_pcs1g_link_status
 * 16  =  line_pcs_rx_status_o
 * 17  =  client_pcs1g_link_status
 * 18  =  host_pcs_rx_status
 * 19  =  host_sd10g_ib_signal_detect_i
 * 20  =  line_sd10g_ib_signal_detect_i
 * 21  =  hpcs10g_intr
 * 22  =  lpcs10g_intr
 * 23  =  client_pcs1g_intr
 * 24  =  line_pcs1g_intr
 * 25  =  wis_interrupt0
 * 26  =  host_pmaint_intr
 * 27  =  line_pmaint_intr
 * 28  =  data_activity_tx
 * 29  =  data_activity_rx
 * 30  =  host_data_activity_tx
 * 31  =  host_data_activity_rx
 * 32  =  xgmii_pause_egr_bist_exp4_o
 * 33  =  xgmii_pause_igr_bist_exp4_o
 * 34  =  rx_pcs_pause_o
 * 35  =  tx_pcs_pause_o
 * 36  =  rx_wis_pause_o
 * 37  =  tx_wis_pause_o
 * 38  =  eth_channel_dis_o
 * 39  =  msec_ip1588_sfd_lane_o
 * 40  =  line_s_tx_fault
 * 41  =  (eth_1g_ena ? line_pcs1g_ass_latency_o[0] : ewis_fr_bitpos_o[0])
 * ;
 * 42  =  (eth_1g_ena ? line_pcs1g_ass_latency_o[1] : ewis_fr_bitpos_o[1])
 * ;
 * 43  =  (eth_1g_ena ? line_pcs1g_char_pos_o[0]    : ewis_fr_bitpos_o[2])
 * ;
 * 44  =  (eth_1g_ena ? line_pcs1g_char_pos_o[1]    : ewis_fr_wordpos_o[0])
 * ;
 * 45  =  (eth_1g_ena ? line_pcs1g_char_pos_o[2]    : ewis_fr_wordpos_o[1])
 * ;
 * 46  =  (eth_1g_ena ? line_pcs1g_char_pos_o[3]    : ewis_fr_wordpos_o[2])
 * ;
 * 47  =  macsec_igr_pred_var_lat_o[0]
 * 48  =  macsec_igr_pred_var_lat_o[1]
 * 49  =  kr_active_2gpio
 * 50  =  dft_tx_ena_2gpio
 * 51  =  reserved
 * 52  =  exe_last_2gpio[0]
 * 53  =  exe_last_2gpio[1]
 * 54  =  exe_last_2gpio[2]
 * 55  =  exe_last_2gpio[3]
 * 56  =  exe_last_2gpio[4]
 * 57  =  link_hcd_2gpio[0]

 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_GPIO2_OUT . SEL2
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_GPIO2_OUT_SEL2(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_INTR_CTRL_GPIO_INTR_GPIO2_OUT_SEL2     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_INTR_CTRL_GPIO_INTR_GPIO2_OUT_SEL2(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief GPIO Output selection
 *
 * \details
 * Selects which internal signal is routed to the corresponding output line
 *
 * Register: \a GPIO_INTR_CTRL:GPIO_INTR:GPIO3_OUT
 */
#define VTSS_GPIO_INTR_CTRL_GPIO_INTR_GPIO3_OUT  VTSS_IOREG(0x01, 0, 0xc013)

/** 
 * \brief
 * Selects which internal signal is routed to the corresponding output line
 *
 * \details 
 * 
 * 0   =  i2c_mstr_module_dataout_o
 * 1   =  i2c_mstr_module_clkout_o
 * 2   =  led_tx_o
 * 3   =  led_rx_o
 * 4   =  rxalarm_o
 * 5   =  txalarm_o
 * 6   =  host_link_up_o
 * 7   =  line_link_up_o
 * 8   =  line_kr_sync8b10b_2gpio
 * 9   =  line_kr_sync10g_2gpio
 * 10  =  rosi_frm_pulse_o
 * 11  =  rosi_sdat_o
 * 12  =  rosi_sclk_o
 * 13  =  tosi_frm_pulse_o
 * 14  =  tosi_sclk_o
 * 15  =  line_pcs1g_link_status
 * 16  =  line_pcs_rx_status_o
 * 17  =  client_pcs1g_link_status
 * 18  =  host_pcs_rx_status
 * 19  =  host_sd10g_ib_signal_detect_i
 * 20  =  line_sd10g_ib_signal_detect_i
 * 21  =  hpcs10g_intr
 * 22  =  lpcs10g_intr
 * 23  =  client_pcs1g_intr
 * 24  =  line_pcs1g_intr
 * 25  =  wis_interrupt0
 * 26  =  host_pmaint_intr
 * 27  =  line_pmaint_intr
 * 28  =  data_activity_tx
 * 29  =  data_activity_rx
 * 30  =  host_data_activity_tx
 * 31  =  host_data_activity_rx
 * 32  =  xgmii_pause_egr_bist_exp4_o
 * 33  =  xgmii_pause_igr_bist_exp4_o
 * 34  =  rx_pcs_pause_o
 * 35  =  tx_pcs_pause_o
 * 36  =  rx_wis_pause_o
 * 37  =  tx_wis_pause_o
 * 38  =  eth_channel_dis_o
 * 39  =  msec_ip1588_sfd_lane_o
 * 40  =  line_s_tx_fault
 * 41  =  (eth_1g_ena ? line_pcs1g_ass_latency_o[0] : ewis_fr_bitpos_o[0])
 * ;
 * 42  =  (eth_1g_ena ? line_pcs1g_ass_latency_o[1] : ewis_fr_bitpos_o[1])
 * ;
 * 43  =  (eth_1g_ena ? line_pcs1g_char_pos_o[0]    : ewis_fr_bitpos_o[2])
 * ;
 * 44  =  (eth_1g_ena ? line_pcs1g_char_pos_o[1]    : ewis_fr_wordpos_o[0])
 * ;
 * 45  =  (eth_1g_ena ? line_pcs1g_char_pos_o[2]    : ewis_fr_wordpos_o[1])
 * ;
 * 46  =  (eth_1g_ena ? line_pcs1g_char_pos_o[3]    : ewis_fr_wordpos_o[2])
 * ;
 * 47  =  macsec_igr_pred_var_lat_o[0]
 * 48  =  macsec_igr_pred_var_lat_o[1]
 * 49  =  kr_active_2gpio
 * 50  =  dft_tx_ena_2gpio
 * 51  =  reserved
 * 52  =  exe_last_2gpio[0]
 * 53  =  exe_last_2gpio[1]
 * 54  =  exe_last_2gpio[2]
 * 55  =  exe_last_2gpio[3]
 * 56  =  exe_last_2gpio[4]
 * 57  =  link_hcd_2gpio[0]

 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_GPIO3_OUT . SEL3
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_GPIO3_OUT_SEL3(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_INTR_CTRL_GPIO_INTR_GPIO3_OUT_SEL3     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_INTR_CTRL_GPIO_INTR_GPIO3_OUT_SEL3(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief GPIO Output selection
 *
 * \details
 * Selects which internal signal is routed to the corresponding output line
 *
 * Register: \a GPIO_INTR_CTRL:GPIO_INTR:GPIO4_OUT
 */
#define VTSS_GPIO_INTR_CTRL_GPIO_INTR_GPIO4_OUT  VTSS_IOREG(0x01, 0, 0xc014)

/** 
 * \brief
 * Selects which internal signal is routed to the corresponding output line
 *
 * \details 
 * 
 * 0   =  i2c_mstr_module_dataout_o
 * 1   =  i2c_mstr_module_clkout_o
 * 2   =  led_tx_o
 * 3   =  led_rx_o
 * 4   =  rxalarm_o
 * 5   =  txalarm_o
 * 6   =  host_link_up_o
 * 7   =  line_link_up_o
 * 8   =  line_kr_sync8b10b_2gpio
 * 9   =  line_kr_sync10g_2gpio
 * 10  =  rosi_frm_pulse_o
 * 11  =  rosi_sdat_o
 * 12  =  rosi_sclk_o
 * 13  =  tosi_frm_pulse_o
 * 14  =  tosi_sclk_o
 * 15  =  line_pcs1g_link_status
 * 16  =  line_pcs_rx_status_o
 * 17  =  client_pcs1g_link_status
 * 18  =  host_pcs_rx_status
 * 19  =  host_sd10g_ib_signal_detect_i
 * 20  =  line_sd10g_ib_signal_detect_i
 * 21  =  hpcs10g_intr
 * 22  =  lpcs10g_intr
 * 23  =  client_pcs1g_intr
 * 24  =  line_pcs1g_intr
 * 25  =  wis_interrupt0
 * 26  =  host_pmaint_intr
 * 27  =  line_pmaint_intr
 * 28  =  data_activity_tx
 * 29  =  data_activity_rx
 * 30  =  host_data_activity_tx
 * 31  =  host_data_activity_rx
 * 32  =  xgmii_pause_egr_bist_exp4_o
 * 33  =  xgmii_pause_igr_bist_exp4_o
 * 34  =  rx_pcs_pause_o
 * 35  =  tx_pcs_pause_o
 * 36  =  rx_wis_pause_o
 * 37  =  tx_wis_pause_o
 * 38  =  eth_channel_dis_o
 * 39  =  msec_ip1588_sfd_lane_o
 * 40  =  line_s_tx_fault
 * 41  =  (eth_1g_ena ? line_pcs1g_ass_latency_o[0] : ewis_fr_bitpos_o[0])
 * ;
 * 42  =  (eth_1g_ena ? line_pcs1g_ass_latency_o[1] : ewis_fr_bitpos_o[1])
 * ;
 * 43  =  (eth_1g_ena ? line_pcs1g_char_pos_o[0]    : ewis_fr_bitpos_o[2])
 * ;
 * 44  =  (eth_1g_ena ? line_pcs1g_char_pos_o[1]    : ewis_fr_wordpos_o[0])
 * ;
 * 45  =  (eth_1g_ena ? line_pcs1g_char_pos_o[2]    : ewis_fr_wordpos_o[1])
 * ;
 * 46  =  (eth_1g_ena ? line_pcs1g_char_pos_o[3]    : ewis_fr_wordpos_o[2])
 * ;
 * 47  =  macsec_igr_pred_var_lat_o[0]
 * 48  =  macsec_igr_pred_var_lat_o[1]
 * 49  =  kr_active_2gpio
 * 50  =  dft_tx_ena_2gpio
 * 51  =  reserved
 * 52  =  exe_last_2gpio[0]
 * 53  =  exe_last_2gpio[1]
 * 54  =  exe_last_2gpio[2]
 * 55  =  exe_last_2gpio[3]
 * 56  =  exe_last_2gpio[4]
 * 57  =  link_hcd_2gpio[0]

 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_GPIO4_OUT . SEL4
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_GPIO4_OUT_SEL4(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_INTR_CTRL_GPIO_INTR_GPIO4_OUT_SEL4     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_INTR_CTRL_GPIO_INTR_GPIO4_OUT_SEL4(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief GPIO Output selection
 *
 * \details
 * Selects which internal signal is routed to the corresponding output line
 *
 * Register: \a GPIO_INTR_CTRL:GPIO_INTR:GPIO5_OUT
 */
#define VTSS_GPIO_INTR_CTRL_GPIO_INTR_GPIO5_OUT  VTSS_IOREG(0x01, 0, 0xc015)

/** 
 * \brief
 * Selects which internal signal is routed to the corresponding output line
 *
 * \details 
 * 
 * 0   =  i2c_mstr_module_dataout_o
 * 1   =  i2c_mstr_module_clkout_o
 * 2   =  led_tx_o
 * 3   =  led_rx_o
 * 4   =  rxalarm_o
 * 5   =  txalarm_o
 * 6   =  host_link_up_o
 * 7   =  line_link_up_o
 * 8   =  line_kr_sync8b10b_2gpio
 * 9   =  line_kr_sync10g_2gpio
 * 10  =  rosi_frm_pulse_o
 * 11  =  rosi_sdat_o
 * 12  =  rosi_sclk_o
 * 13  =  tosi_frm_pulse_o
 * 14  =  tosi_sclk_o
 * 15  =  line_pcs1g_link_status
 * 16  =  line_pcs_rx_status_o
 * 17  =  client_pcs1g_link_status
 * 18  =  host_pcs_rx_status
 * 19  =  host_sd10g_ib_signal_detect_i
 * 20  =  line_sd10g_ib_signal_detect_i
 * 21  =  hpcs10g_intr
 * 22  =  lpcs10g_intr
 * 23  =  client_pcs1g_intr
 * 24  =  line_pcs1g_intr
 * 25  =  wis_interrupt0
 * 26  =  host_pmaint_intr
 * 27  =  line_pmaint_intr
 * 28  =  data_activity_tx
 * 29  =  data_activity_rx
 * 30  =  host_data_activity_tx
 * 31  =  host_data_activity_rx
 * 32  =  xgmii_pause_egr_bist_exp4_o
 * 33  =  xgmii_pause_igr_bist_exp4_o
 * 34  =  rx_pcs_pause_o
 * 35  =  tx_pcs_pause_o
 * 36  =  rx_wis_pause_o
 * 37  =  tx_wis_pause_o
 * 38  =  eth_channel_dis_o
 * 39  =  msec_ip1588_sfd_lane_o
 * 40  =  line_s_tx_fault
 * 41  =  (eth_1g_ena ? line_pcs1g_ass_latency_o[0] : ewis_fr_bitpos_o[0])
 * ;
 * 42  =  (eth_1g_ena ? line_pcs1g_ass_latency_o[1] : ewis_fr_bitpos_o[1])
 * ;
 * 43  =  (eth_1g_ena ? line_pcs1g_char_pos_o[0]    : ewis_fr_bitpos_o[2])
 * ;
 * 44  =  (eth_1g_ena ? line_pcs1g_char_pos_o[1]    : ewis_fr_wordpos_o[0])
 * ;
 * 45  =  (eth_1g_ena ? line_pcs1g_char_pos_o[2]    : ewis_fr_wordpos_o[1])
 * ;
 * 46  =  (eth_1g_ena ? line_pcs1g_char_pos_o[3]    : ewis_fr_wordpos_o[2])
 * ;
 * 47  =  macsec_igr_pred_var_lat_o[0]
 * 48  =  macsec_igr_pred_var_lat_o[1]
 * 49  =  kr_active_2gpio
 * 50  =  dft_tx_ena_2gpio
 * 51  =  reserved
 * 52  =  exe_last_2gpio[0]
 * 53  =  exe_last_2gpio[1]
 * 54  =  exe_last_2gpio[2]
 * 55  =  exe_last_2gpio[3]
 * 56  =  exe_last_2gpio[4]
 * 57  =  link_hcd_2gpio[0]

 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_GPIO5_OUT . SEL5
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_GPIO5_OUT_SEL5(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_INTR_CTRL_GPIO_INTR_GPIO5_OUT_SEL5     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_INTR_CTRL_GPIO_INTR_GPIO5_OUT_SEL5(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief GPIO Output selection
 *
 * \details
 * Selects which internal signal is routed to the corresponding output line
 *
 * Register: \a GPIO_INTR_CTRL:GPIO_INTR:GPIO6_OUT
 */
#define VTSS_GPIO_INTR_CTRL_GPIO_INTR_GPIO6_OUT  VTSS_IOREG(0x01, 0, 0xc016)

/** 
 * \brief
 * Selects which internal signal is routed to the corresponding output line
 *
 * \details 
 * 
 * 0   =  i2c_mstr_module_dataout_o
 * 1   =  i2c_mstr_module_clkout_o
 * 2   =  led_tx_o
 * 3   =  led_rx_o
 * 4   =  rxalarm_o
 * 5   =  txalarm_o
 * 6   =  host_link_up_o
 * 7   =  line_link_up_o
 * 8   =  line_kr_sync8b10b_2gpio
 * 9   =  line_kr_sync10g_2gpio
 * 10  =  rosi_frm_pulse_o
 * 11  =  rosi_sdat_o
 * 12  =  rosi_sclk_o
 * 13  =  tosi_frm_pulse_o
 * 14  =  tosi_sclk_o
 * 15  =  line_pcs1g_link_status
 * 16  =  line_pcs_rx_status_o
 * 17  =  client_pcs1g_link_status
 * 18  =  host_pcs_rx_status
 * 19  =  host_sd10g_ib_signal_detect_i
 * 20  =  line_sd10g_ib_signal_detect_i
 * 21  =  hpcs10g_intr
 * 22  =  lpcs10g_intr
 * 23  =  client_pcs1g_intr
 * 24  =  line_pcs1g_intr
 * 25  =  wis_interrupt0
 * 26  =  host_pmaint_intr
 * 27  =  line_pmaint_intr
 * 28  =  data_activity_tx
 * 29  =  data_activity_rx
 * 30  =  host_data_activity_tx
 * 31  =  host_data_activity_rx
 * 32  =  xgmii_pause_egr_bist_exp4_o
 * 33  =  xgmii_pause_igr_bist_exp4_o
 * 34  =  rx_pcs_pause_o
 * 35  =  tx_pcs_pause_o
 * 36  =  rx_wis_pause_o
 * 37  =  tx_wis_pause_o
 * 38  =  eth_channel_dis_o
 * 39  =  msec_ip1588_sfd_lane_o
 * 40  =  line_s_tx_fault
 * 41  =  (eth_1g_ena ? line_pcs1g_ass_latency_o[0] : ewis_fr_bitpos_o[0])
 * ;
 * 42  =  (eth_1g_ena ? line_pcs1g_ass_latency_o[1] : ewis_fr_bitpos_o[1])
 * ;
 * 43  =  (eth_1g_ena ? line_pcs1g_char_pos_o[0]    : ewis_fr_bitpos_o[2])
 * ;
 * 44  =  (eth_1g_ena ? line_pcs1g_char_pos_o[1]    : ewis_fr_wordpos_o[0])
 * ;
 * 45  =  (eth_1g_ena ? line_pcs1g_char_pos_o[2]    : ewis_fr_wordpos_o[1])
 * ;
 * 46  =  (eth_1g_ena ? line_pcs1g_char_pos_o[3]    : ewis_fr_wordpos_o[2])
 * ;
 * 47  =  macsec_igr_pred_var_lat_o[0]
 * 48  =  macsec_igr_pred_var_lat_o[1]
 * 49  =  kr_active_2gpio
 * 50  =  dft_tx_ena_2gpio
 * 51  =  reserved
 * 52  =  exe_last_2gpio[0]
 * 53  =  exe_last_2gpio[1]
 * 54  =  exe_last_2gpio[2]
 * 55  =  exe_last_2gpio[3]
 * 56  =  exe_last_2gpio[4]
 * 57  =  link_hcd_2gpio[0]

 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_GPIO6_OUT . SEL6
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_GPIO6_OUT_SEL6(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_INTR_CTRL_GPIO_INTR_GPIO6_OUT_SEL6     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_INTR_CTRL_GPIO_INTR_GPIO6_OUT_SEL6(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief GPIO Output selection
 *
 * \details
 * Selects which internal signal is routed to the corresponding output line
 *
 * Register: \a GPIO_INTR_CTRL:GPIO_INTR:GPIO7_OUT
 */
#define VTSS_GPIO_INTR_CTRL_GPIO_INTR_GPIO7_OUT  VTSS_IOREG(0x01, 0, 0xc017)

/** 
 * \brief
 * Selects which internal signal is routed to the corresponding output line
 *
 * \details 
 * 
 * 0   =  i2c_mstr_module_dataout_o
 * 1   =  i2c_mstr_module_clkout_o
 * 2   =  led_tx_o
 * 3   =  led_rx_o
 * 4   =  rxalarm_o
 * 5   =  txalarm_o
 * 6   =  host_link_up_o
 * 7   =  line_link_up_o
 * 8   =  line_kr_sync8b10b_2gpio
 * 9   =  line_kr_sync10g_2gpio
 * 10  =  rosi_frm_pulse_o
 * 11  =  rosi_sdat_o
 * 12  =  rosi_sclk_o
 * 13  =  tosi_frm_pulse_o
 * 14  =  tosi_sclk_o
 * 15  =  line_pcs1g_link_status
 * 16  =  line_pcs_rx_status_o
 * 17  =  client_pcs1g_link_status
 * 18  =  host_pcs_rx_status
 * 19  =  host_sd10g_ib_signal_detect_i
 * 20  =  line_sd10g_ib_signal_detect_i
 * 21  =  hpcs10g_intr
 * 22  =  lpcs10g_intr
 * 23  =  client_pcs1g_intr
 * 24  =  line_pcs1g_intr
 * 25  =  wis_interrupt0
 * 26  =  host_pmaint_intr
 * 27  =  line_pmaint_intr
 * 28  =  data_activity_tx
 * 29  =  data_activity_rx
 * 30  =  host_data_activity_tx
 * 31  =  host_data_activity_rx
 * 32  =  xgmii_pause_egr_bist_exp4_o
 * 33  =  xgmii_pause_igr_bist_exp4_o
 * 34  =  rx_pcs_pause_o
 * 35  =  tx_pcs_pause_o
 * 36  =  rx_wis_pause_o
 * 37  =  tx_wis_pause_o
 * 38  =  eth_channel_dis_o
 * 39  =  msec_ip1588_sfd_lane_o
 * 40  =  line_s_tx_fault
 * 41  =  (eth_1g_ena ? line_pcs1g_ass_latency_o[0] : ewis_fr_bitpos_o[0])
 * ;
 * 42  =  (eth_1g_ena ? line_pcs1g_ass_latency_o[1] : ewis_fr_bitpos_o[1])
 * ;
 * 43  =  (eth_1g_ena ? line_pcs1g_char_pos_o[0]    : ewis_fr_bitpos_o[2])
 * ;
 * 44  =  (eth_1g_ena ? line_pcs1g_char_pos_o[1]    : ewis_fr_wordpos_o[0])
 * ;
 * 45  =  (eth_1g_ena ? line_pcs1g_char_pos_o[2]    : ewis_fr_wordpos_o[1])
 * ;
 * 46  =  (eth_1g_ena ? line_pcs1g_char_pos_o[3]    : ewis_fr_wordpos_o[2])
 * ;
 * 47  =  macsec_igr_pred_var_lat_o[0]
 * 48  =  macsec_igr_pred_var_lat_o[1]
 * 49  =  kr_active_2gpio
 * 50  =  dft_tx_ena_2gpio
 * 51  =  reserved
 * 52  =  exe_last_2gpio[0]
 * 53  =  exe_last_2gpio[1]
 * 54  =  exe_last_2gpio[2]
 * 55  =  exe_last_2gpio[3]
 * 56  =  exe_last_2gpio[4]
 * 57  =  link_hcd_2gpio[0]

 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_GPIO7_OUT . SEL7
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_GPIO7_OUT_SEL7(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_GPIO_INTR_CTRL_GPIO_INTR_GPIO7_OUT_SEL7     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_GPIO_INTR_CTRL_GPIO_INTR_GPIO7_OUT_SEL7(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a GPIO_INTR_CTRL:GPIO_INTR:INTR
 *
 * @param ri Register: INTR, 0-1
 */
#define VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR(ri)  VTSS_IOREG(0x01, 0, 0xc018 | (ri))

/** 
 * \brief
 * Host PMA interrupt interrupt enable.  Enables Host PMA interrupt to
 * propagate to corresponding channel interrupt
 *
 * \details 
 * 0 = Host PMA interrupt will not affect the corresponding channel
 * interrupt
 * 1 = Host PMA interrupt will propagate to the corresponding channel
 * interrupt
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR . HPMA_INTR_EN
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_HPMA_INTR_EN  VTSS_BIT(15)

/** 
 * \brief
 * Line PMA interrupt interrupt enable.  Enables Line PMA interrupt to
 * propagate to corresponding channel interrupt
 *
 * \details 
 * 0 = Line PMA interrupt will not affect the corresponding channel
 * interrupt
 * 1 = Line PMA interrupt will propagate to the corresponding channel
 * interrupt
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR . LPMA_INTR_EN
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_LPMA_INTR_EN  VTSS_BIT(14)

/** 
 * \brief
 * Host Egress FIFO interrupt interrupt enable.  Enables Host Egress FIFO
 * interrupt to propagate to corresponding channel interrupt
 *
 * \details 
 * 0 = Host Egress FIFO interrupt will not affect the corresponding channel
 * interrupt
 * 1 = Host Egress FIFO interrupt will propagate to the corresponding
 * channel interrupt
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR . HEGR_FIFO_INTR_EN
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_HEGR_FIFO_INTR_EN  VTSS_BIT(13)

/** 
 * \brief
 * Line Egress FIFO interrupt interrupt enable.  Enables Line Egress FIFO
 * interrupt to propagate to corresponding channel interrupt
 *
 * \details 
 * 0 = Line Egress FIFO interrupt will not affect the corresponding channel
 * interrupt
 * 1 = Line Egress FIFO interrupt will propagate to the corresponding
 * channel interrupt
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR . LEGR_FIFO_INTR_EN
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_LEGR_FIFO_INTR_EN  VTSS_BIT(12)

/** 
 * \brief
 * Line Ingress FIFO interrupt interrupt enable.  Enables Line Ingress FIFO
 * interrupt to propagate to corresponding channel interrupt
 *
 * \details 
 * 0 = Line Ingress FIFO interrupt will not affect the corresponding
 * channel interrupt
 * 1 = Line Ingress FIFO interrupt will propagate to the corresponding
 * channel interrupt
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR . LIGR_FIFO_INTR_EN
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_LIGR_FIFO_INTR_EN  VTSS_BIT(11)

/** 
 * \brief
 * Flow Control Buffer interrupt interrupt enable.  Enables Flow Control
 * Buffer interrupt to propagate to corresponding channel interrupt
 *
 * \details 
 * 0 = Flow Control Buffer interrupt will not affect the corresponding
 * channel interrupt
 * 1 = Flow Control Buffer interrupt will propagate to the corresponding
 * channel interrupt
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR . FCBUF_INTR_EN
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_FCBUF_INTR_EN  VTSS_BIT(10)

/** 
 * \brief
 * Host MAC interrupt interrupt enable.  Enables Host MAC interrupt to
 * propagate to corresponding channel interrupt
 *
 * \details 
 * 0 = Host MAC interrupt will not affect the corresponding channel
 * interrupt
 * 1 = Host MAC interrupt will propagate to the corresponding channel
 * interrupt
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR . HMAC_INTR_EN
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_HMAC_INTR_EN  VTSS_BIT(9)

/** 
 * \brief
 * Line MAC interrupt interrupt enable.  Enables Line MAC interrupt to
 * propagate to corresponding channel interrupt
 *
 * \details 
 * 0 = Line MAC interrupt will not affect the corresponding channel
 * interrupt
 * 1 = Line MAC interrupt will propagate to the corresponding channel
 * interrupt
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR . LMAC_INTR_EN
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_LMAC_INTR_EN  VTSS_BIT(8)

/** 
 * \brief
 * MACSEC Ingress interrupt interrupt enable.  Enables MACSEC Ingress
 * interrupt to propagate to corresponding channel interrupt
 *
 * \details 
 * 0 = MACSEC Ingress interrupt will not affect the corresponding channel
 * interrupt
 * 1 = MACSEC Ingress interrupt will propagate to the corresponding channel
 * interrupt
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR . MSEC_IGR_INTR_EN
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_MSEC_IGR_INTR_EN  VTSS_BIT(7)

/** 
 * \brief
 * MACSEC Egress interrupt interrupt enable.  Enables MACSEC Egress
 * interrupt to propagate to corresponding channel interrupt
 *
 * \details 
 * 0 = MACSEC Egress interrupt will not affect the corresponding channel
 * interrupt
 * 1 = MACSEC Egress interrupt will propagate to the corresponding channel
 * interrupt
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR . MSEC_EGR_INTR_EN
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_MSEC_EGR_INTR_EN  VTSS_BIT(6)

/** 
 * \brief
 * Host PCS1G interrupt interrupt enable.  Enables Host PCS1G interrupt to
 * propagate to corresponding channel interrupt
 *
 * \details 
 * 0 = Host PCS1G interrupt will not affect the corresponding channel
 * interrupt
 * 1 = Host PCS1G interrupt will propagate to the corresponding channel
 * interrupt
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR . HPCS1G_INTR_EN
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_HPCS1G_INTR_EN  VTSS_BIT(5)

/** 
 * \brief
 * Line PCS1G interrupt interrupt enable.  Enables Line PCS1G interrupt to
 * propagate to corresponding channel interrupt
 *
 * \details 
 * 0 = Line PCS1G interrupt will not affect the corresponding channel
 * interrupt
 * 1 = Line PCS1G interrupt will propagate to the corresponding channel
 * interrupt
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR . LPCS1G_INTR_EN
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_LPCS1G_INTR_EN  VTSS_BIT(4)

/** 
 * \brief
 * Host PCS10G interrupt interrupt enable.  Enables Host PCS10G interrupt
 * to propagate to corresponding channel interrupt
 *
 * \details 
 * 0 = Host PCS10G interrupt will not affect the corresponding channel
 * interrupt
 * 1 = Host PCS10G interrupt will propagate to the corresponding channel
 * interrupt
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR . HPCS10G_INTR_EN
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_HPCS10G_INTR_EN  VTSS_BIT(3)

/** 
 * \brief
 * Line PCS10G interrupt interrupt enable.  Enables Line PCS10G interrupt
 * to propagate to corresponding channel interrupt
 *
 * \details 
 * 0 = Line PCS10G interrupt will not affect the corresponding channel
 * interrupt
 * 1 = Line PCS10G interrupt will propagate to the corresponding channel
 * interrupt
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR . LPCS10G_INTR_EN
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_LPCS10G_INTR_EN  VTSS_BIT(2)

/** 
 * \brief
 * WIS 2nd interrupt interrupt enable.	Enables WIS 2nd interrupt to
 * propagate to corresponding channel interrupt
 *
 * \details 
 * 0 = WIS 2nd interrupt will not affect the corresponding channel
 * interrupt
 * 1 = WIS 2nd interrupt will propagate to the corresponding channel
 * interrupt
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR . WIS1_INTR_EN
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_WIS1_INTR_EN  VTSS_BIT(1)

/** 
 * \brief
 * WIS first interrupt interrupt enable.  Enables WIS first interrupt to
 * propagate to corresponding channel interrupt
 *
 * \details 
 * 0 = WIS first interrupt will not affect the corresponding channel
 * interrupt
 * 1 = WIS first interrupt will propagate to the corresponding channel
 * interrupt
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR . WIS0_INTR_EN
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_WIS0_INTR_EN  VTSS_BIT(0)


/** 
 * \details
 * Register: \a GPIO_INTR_CTRL:GPIO_INTR:INTR_STAT
 *
 * @param ri Register: INTR_STAT, 0-1
 */
#define VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT(ri)  VTSS_IOREG(0x01, 0, 0xc01a | (ri))

/** 
 * \brief
 * Host PMA interrupt status.  Indicates Host PMA interrupt is pending or
 * is masked.
 *
 * \details 
 * 0 = Host PMA interrupt not pending or corresponding INTR_EN is cleared
 * 1 = Host PMA interrupt pending and corresponding INTR_EN is set
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT . HPMA_INTR_STAT
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT_HPMA_INTR_STAT  VTSS_BIT(15)

/** 
 * \brief
 * Line PMA interrupt status.  Indicates Line PMA interrupt is pending or
 * is masked
 *
 * \details 
 * 0 = Line PMA interrupt not pending or corresponding INTR_EN is cleared
 * 1 = Line PMA interrupt pending and corresponding INTR_EN is set
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT . LPMA_INTR_STAT
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT_LPMA_INTR_STAT  VTSS_BIT(14)

/** 
 * \brief
 * Host Egress FIFO interrupt status.  Indicates Host Egress FIFO interrupt
 * is pending or is masked
 *
 * \details 
 * 0 = Host Egress FIFO interrupt not pending or corresponding INTR_EN is
 * cleared
 * 1 = Host Egress FIFO interrupt pending and corresponding INTR_EN is set
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT . HEGR_FIFO_INTR_STAT
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT_HEGR_FIFO_INTR_STAT  VTSS_BIT(13)

/** 
 * \brief
 * Line Egress interrupt status.  Indicates Line Egress interrupt is
 * pending or is masked
 *
 * \details 
 * 0 = Line Egress interrupt not pending or corresponding INTR_EN is
 * cleared
 * 1 = Line Egress interrupt pending and corresponding INTR_EN is set
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT . LEGR_FIFO_INTR_STAT
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT_LEGR_FIFO_INTR_STAT  VTSS_BIT(12)

/** 
 * \brief
 * Line Ingress interrupt status.  Indicates Line Ingress interrupt is
 * pending or is masked
 *
 * \details 
 * 0 = Line Ingress interrupt not pending or corresponding INTR_EN is
 * cleared
 * 1 = Line Ingress interrupt pending and corresponding INTR_EN is set
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT . LIGR_FIFO_INTR_STAT
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT_LIGR_FIFO_INTR_STAT  VTSS_BIT(11)

/** 
 * \brief
 * Flow Control Buffer interrupt status.  Indicates Flow Control Buffer
 * interrupt is pending or is masked
 *
 * \details 
 * 0 = Flow Control Buffer interrupt not pending or corresponding INTR_EN
 * is cleared
 * 1 = Flow Control Buffer interrupt pending and corresponding INTR_EN is
 * set
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT . FCBUF_INTR_STAT
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT_FCBUF_INTR_STAT  VTSS_BIT(10)

/** 
 * \brief
 * Host MAC interrupt status.  Indicates Host MAC interrupt is pending or
 * is masked
 *
 * \details 
 * 0 = Host MAC interrupt not pending or corresponding INTR_EN is cleared
 * 1 = Host MAC interrupt pending and corresponding INTR_EN is set
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT . HMAC_INTR_STAT
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT_HMAC_INTR_STAT  VTSS_BIT(9)

/** 
 * \brief
 * Line MAC interrupt status.  Indicates Line MAC interrupt is pending or
 * is masked
 *
 * \details 
 * 0 = Line MAC interrupt not pending or corresponding INTR_EN is cleared
 * 1 = Line MAC interrupt pending and corresponding INTR_EN is set
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT . LMAC_INTR_STAT
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT_LMAC_INTR_STAT  VTSS_BIT(8)

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
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT . MSEC_IGR_INTR_STAT
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT_MSEC_IGR_INTR_STAT  VTSS_BIT(7)

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
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT . MSEC_EGR_INTR_STAT
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT_MSEC_EGR_INTR_STAT  VTSS_BIT(6)

/** 
 * \brief
 * Host PCS1G interrupt status.  Indicates Host PCS1G interrupt is pending
 * or is masked
 *
 * \details 
 * 0 = Host PCS1G interrupt not pending or corresponding INTR_EN is cleared
 * 1 = Host PCS1G interrupt pending and corresponding INTR_EN is set
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT . HPCS1G_INTR_STAT
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT_HPCS1G_INTR_STAT  VTSS_BIT(5)

/** 
 * \brief
 * Line PCS1G interrupt status.  Indicates Line PCS1G interrupt is pending
 * or is masked
 *
 * \details 
 * 0 = Line PCS1G interrupt not pending or corresponding INTR_EN is cleared
 * 1 = Line PCS1G interrupt pending and corresponding INTR_EN is set
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT . LPCS1G_INTR_STAT
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT_LPCS1G_INTR_STAT  VTSS_BIT(4)

/** 
 * \brief
 * Host PCS10G interrupt status.  Indicates Host PCS10G interrupt is
 * pending or is masked
 *
 * \details 
 * 0 = Host PCS10G interrupt not pending or corresponding INTR_EN is
 * cleared
 * 1 = Host PCS10G interrupt pending and corresponding INTR_EN is set
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT . HPCS10G_INTR_STAT
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT_HPCS10G_INTR_STAT  VTSS_BIT(3)

/** 
 * \brief
 * Line PCS10G interrupt status.  Indicates Line PCS10G interrupt is
 * pending or is masked
 *
 * \details 
 * 0 = Line PCS10G interrupt not pending or corresponding INTR_EN is
 * cleared
 * 1 = Line PCS10G interrupt pending and corresponding INTR_EN is set
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT . LPCS10G_INTR_STAT
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT_LPCS10G_INTR_STAT  VTSS_BIT(2)

/** 
 * \brief
 * 2nd WIS interrupt status.  Indicates 2nd WIS interrupt is pending or is
 * masked
 *
 * \details 
 * 0 = 2nd WIS interrupt not pending or corresponding INTR_EN is cleared
 * 1 = 2nd WIS interrupt pending and corresponding INTR_EN is set
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT . WIS1_INTR_STAT
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT_WIS1_INTR_STAT  VTSS_BIT(1)

/** 
 * \brief
 * 1st WIS interrupt status.  Indicates 1st WIS interrupt is pending or is
 * masked
 *
 * \details 
 * 0 = 1st WIS interrupt not pending or corresponding INTR_EN is cleared
 * 1 = 1st WIS interrupt pending and corresponding INTR_EN is set
 *
 * Field: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT . WIS0_INTR_STAT
 */
#define  VTSS_F_GPIO_INTR_CTRL_GPIO_INTR_INTR_STAT_WIS0_INTR_STAT  VTSS_BIT(0)


#endif /* _VTSS_MALIBU_REGS_GPIO_INTR_CTRL_H_ */
