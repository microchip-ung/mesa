#!/bin/sh

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT


#---------- Functions called --------------------------------------------------
# mesa_packet_rx_conf_get
# mesa_packet_rx_conf_set
# mesa_npi_conf_get
# mesa_npi_conf_set
# mesa_mac_table_add
# mesa_mac_table_del

# mesa_ptp_get_timestamp
# mesa_ts_timeofday_get
# mesa_ts_timeofday_set
# mesa_ts_domain_timeofday_get
# mesa_ts_domain_timeofday_set
# mesa_ts_operation_mode_get
# mesa_ts_operation_mode_set
# mesa_ts_timeofday_set_delta
# mesa_ts_domain_timeofday_set_delta
# mesa_ts_timeofday_offset_set
# mesa_ts_domain_timeofday_offset_set
# mesa_ts_external_clock_mode_set
# mesa_ts_external_clock_mode_get
# mesa_ts_adjtimer_one_sec
# mesa_ts_ongoing_adjustment
# mesa_ts_timeofday_prev_pps_get
# mesa_ts_timeofday_next_pps_get
# mesa_ts_domain_timeofday_next_pps_get
# mesa_ts_egress_latency_get
# mesa_ts_egress_latency_set
# mesa_ts_ingress_latency_get
# mesa_ts_ingress_latency_set
# mesa_ts_delay_asymmetry_get
# mesa_ts_delay_asymmetry_set
# mesa_ts_p2p_delay_get
# mesa_ts_p2p_delay_set
# mesa_ts_status_change
# mesa_ts_autoresp_dom_cfg_get
# mesa_ts_autoresp_dom_cfg_set
# mesa_ts_external_io_mode_get
# mesa_ts_external_io_mode_set
# mesa_ts_saved_timeofday_get                   This function name should have included _external_io_ as it has the io parameter and operates per io
# mesa_ts_smac_set
# mesa_ts_smac_get
# mesa_ts_seq_cnt_get
# mesa_tx_timestamp_update
# mesa_tx_timestamp_idx_alloc
# mesa_timestamp_age
# mesa_ts_alt_clock_saved_get                   The name of this function indicate that this is part of the _alt_ interface that generally is not called
#                                               by application on Jaguar2. But this specific function is implemented and also called by application on jaguar2.
#                                               The mesa_ts_saved_timeofday_get function should be used instead on Jaguar22 as this is also an _io_ function
#                                               even though it is not named so
# mesa_ts_adjtimer_set
# mesa_ts_adjtimer_get
# mesa_ts_domain_adjtimer_set
# mesa_ts_domain_adjtimer_get
# mesa_ts_internal_mode_get
# mesa_ts_internal_mode_set



#---------- Functions not testet --------------------------------------------------
# mesa_rx_timestamp_get                         No RX FIFO on Jaguar 2
# mesa_rx_timestamp_id_release                  No RX FIFO on Jaguar 2
# mesa_rx_master_timestamp_get                  No RX FIFO on Jaguar 2

# mesa_oam_timestamp_get                        Only on Serval

# mesa_ts_alt_clock_saved_timeofday_get         Only on Serval
# mesa_ts_alt_clock_mode_get                    Not called by application on any platform
# mesa_ts_alt_clock_mode_set                    Not called by application on Jaguar2. Function is implemented but possibly faulty
# mesa_ts_timeofday_next_pps_set                Not called by application on any platform

# mesa_ts_external_clock_saved_get              Not implemented in Jaguar2 CIL
# mesa_ts_freq_offset_get                       Not implemented on Jaguar 2

#------------- TS test execution ---------------------------


echo '---------------------------------------------------------'
echo 'ts_test_all.rb TS test execution'
echo '---------------------------------------------------------'
# Preconditions are a Jaguar2 DUT with four ports connected to Test PC and a loop between port 7 and 8. also the external clock SMA in and out must be looped
echo 'ts_tod_domain.rb TS test execution'
sudo ./ts_tod_domain.rb $1 > ts_test_all_output.txt
echo 'ts_tod_domain_offset.rb TS test execution'
sudo ./ts_tod_domain_offset.rb --no-startup >> ts_test_all_output.txt
echo 'ts_sequence_id.rb TS test execution'
sudo ./ts_sequence_id.rb --no-startup >> ts_test_all_output.txt
echo 'ts_external_clock_frequence.rb TS test execution'
sudo ./ts_external_clock_frequence.rb --no-startup >> ts_test_all_output.txt
echo 'ts_tod_latency.rb TS test execution'
sudo ./ts_tod_latency.rb --no-startup >> ts_test_all_output.txt
echo 'ts_asymmetry_p2p_delay.rb TS test execution'
sudo ./ts_asymmetry_p2p_delay.rb --no-startup >> ts_test_all_output.txt
echo 'ts_auto_responce.rb TS test execution'
sudo ./ts_auto_responce.rb --no-startup >> ts_test_all_output.txt
echo 'ts_external_clock_1pps.rb TS test execution'
sudo ./ts_external_clock_1pps.rb --no-startup >> ts_test_all_output.txt
echo 'ts_external_io_1pps.rb TS test execution'
sudo ./ts_external_io_1pps.rb --no-startup >> ts_test_all_output.txt
echo 'ts_tx_fifo.rb TS test execution'
sudo ./ts_tx_fifo.rb --no-startup >> ts_test_all_output.txt
echo 'ts_external_io_rs422_1pps.rb TS test execution'
sudo ./ts_external_io_rs422_1pps.rb --no-startup >> ts_test_all_output.txt
echo 'ts_adj_timer.rb TS test execution'
sudo ./ts_adj_timer.rb --no-startup >> ts_test_all_output.txt
echo 'ts_internal_mode.rb TS test execution'
sudo ./ts_internal_mode.rb --no-startup >> ts_test_all_output.txt

grep " error " ts_test_all_output.txt
