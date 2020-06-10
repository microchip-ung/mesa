#!/usr/bin/env ruby

require "pp"
require "json"
require_relative 'libeasy/et'

meta = {
    "owner" => "rs",
    "desc"  => "RTE basic working verification",
}

$ts = get_test_setup("switchdev_pc_b2b_4x")

test "bridge_init" do
  basic_br_init
  sleep 5

end

test "rte_config" do
     $ts.dut.run "symreg RTE_OUTB_RTP_STATE                0xFFFFFFFF"    # 1 for Active state and 0 for stopped state
     $ts.dut.run "symreg RTE_RTE_CFG.RTE_ENA               0x01"    # Enabling RTE

     $ts.dut.run "symreg RTE_OUTB_RTP_MISC[5].RTP_ENA         0x01"    # Enable Outbound RTP for RTP ID 5
     $ts.dut.run "symreg RTE_OUTB_RTP_MISC[5].RTP_GRP_ID      0x00"    # No grouping of RTPID
     $ts.dut.run "symreg RTE_OUTB_RTP_MISC[5].RTP_GRP_STATE_STOPPED_MODE    0x01"  # 1 to accept received PDU in RTP stopped state, 0 to Skip received  PDU in RTP stopped state

    # $ts.dut.run "symreg RTE_OUTB_WR_ACTION_ADDR[1].WR_ACTION_ADDR 0x00"  # 0 to indicate no write action to RAI is triggered. Needed only when DG memory to AXI write is required.
     $ts.dut.run "symreg RTE_OUTB_RTP_MISC[5].PDU_TYPE             0x00"    # 0 to specify Profinet PDU type
     $ts.dut.run "symreg RTE_OUTB_RTP_PDU_CHKS[5].PDU_LEN          238"    # Total length of PDU excluding FCS after 0x8892. Set to 0 to disable PDU length check

     $ts.dut.run "symreg RTE_OUTB_RTP_PDU_CHKS[5].PN_CC_INIT          0x01"   #initialize the cycle counter from the received frame.
     $ts.dut.run "symreg RTE_OUTB_RTP_PN_MISC[5].PN_DATA_STATUS_VAL   0x35" #Set the expected data status value as 0x35.
     $ts.dut.run "symreg RTE_OUTB_PN_PDU_MISC[5].PN_DATA_STATUS_MASK  0xFF"   #Set the mask value for the data status fields

     $ts.dut.run "symreg RTE_OUTB_PN_PDU_MISC[5].PN_DATA_STATUS_VALID_CHK_ENA 0x01"  # 00 to disable data status check
     $ts.dut.run "symreg RTE_OUTB_PN_PDU_MISC[5].PN_TRANSFER_STATUS_CHK_ENA   0x01"  # 0 to disable transfer status field check.
     $ts.dut.run "symreg RTE_OUTB_RTP_PN_MISC[5].PN_CC_CHK_ENA                0x01"  # Set to 0 to disable Cycle counter check

     $ts.dut.run "symreg RTE_OUTB_DG_ADDR[5,0].DG_ADDR       0x01"   # Program the DG Data pointers
     $ts.dut.run "symreg RTE_OUTB_DG_ADDR[5,1].DG_ADDR       0x00"   #
     $ts.dut.run "symreg RTE_OUTB_DG_ADDR[5,2].DG_ADDR       0x00"   #
end


test "Send Profinet Frame" do
  $ts.dut.run "symreg SYS_PORT_MODE[0].INCL_INJ_HDR     0x01"
  #$ts.dut.run "symreg sys_port_mode[2].incl_xtr_hdr     0x01"

  $ts.dut.run "symreg RTE_OUTB_CFG.OUTB_PORT               0x01"    # Set the portto be processed by O/B RTE as port 1
  $ts.dut.run "symreg RTE_OUTB_DG_MISC[1].DG_BASE_PDU_POS                  0x02"    # Set the start of the data group leaving the 1st two byte (frameid) after 0x8892
  $ts.dut.run "symreg RTE_OUTB_DG_DATA_OFFSET_PDU_POS[1].DG_DATA_OFFSET_PDU_POS 0x00"    # 1byte after dg base pdu data starts
  $ts.dut.run "symreg RTE_OUTB_DG_DATA_RTP_CTRL_ACC.DG_DATA_RTP_CTRL_ADDR  0x05"
  $ts.dut.run "symreg RTE_OUTB_DG_DATA_RTP_CTRL_ACC.RTP_WR_MASK_LATEST_IDX 0x01"     # The WR_MASK_* fields each controls one field in OUTB_DG_DATA_RTP_CTRL:
                                                                                  # - If set to 0, the field is left unchanged during write operation.
                                                                                  # - If set to 1, the field is changed during write operation.
  $ts.dut.run "symreg RTE_OUTB_DG_DATA_RTP_CTRL_ACC.RTP_WR_MASK_SW_WR_DIS  0x01"
  $ts.dut.run "symreg RTE_OUTB_DG_DATA_RTP_CTRL_ACC.RTP_WR_MASK_HW_WR_DIS  0x01"
  $ts.dut.run "symreg RTE_OUTB_DG_DATA_RTP_CTRL.SW_WR_DIS                  0x01"
  $ts.dut.run "symreg RTE_OUTB_DG_DATA_RTP_CTRL.HW_WR_DIS                  0x00" #HW writes are diabled
  $ts.dut.run "symreg RTE_OUTB_DG_DATA_RTP_CTRL.LATEST_IDX                 0x00" #Latest Data is present in section 0

  $ts.dut.run "symreg RTE_OUTB_DG_DATA_SECTION_ADDR[1].DG_DATA_SECTION_ADDR     0x00"    # Set Section Address 0
  $ts.dut.run "symreg RTE_OUTB_DG_DATA_SECTION_ADDR[1].DG_DATA_LEN              0x08"    # Data Group Length is 8 bytes
  $ts.dut.run "symreg RTE_OUTB_PN_IOPS[1].PN_IOPS_CHK_ENA                          0x01"    #Disable IOPS Check
  $ts.dut.run "symreg RTE_OUTB_PN_DG_MASKS.PN_IOPS_MASK                       0xFF"
  $ts.dut.run "symreg RTE_OUTB_PN_IOPS[1].PN_IOPS_VAL                      0x80"
  $ts.dut.run "symreg RTE_OUTB_PN_IOPS[1].PN_IOPS_OFFSET_PDU_POS                   0x06"

  test "status before frame inject" do
    $ts.dut.run "symreg RTE_OUTB_RTP_STICKY_BITS[5].*"
    $ts.dut.run "symreg RTE_OUTB_RTP_STICKY_BITS[5]"
    $ts.dut.run "symreg RTE_OUTB_DG_STICKY_BITS[1].*"
    $ts.dut.run "symreg RTE_OUTB_STICKY_BITS.*"
    $ts.dut.run "symreg RTE_OUTB_STICKY_BITS"
    $ts.dut.run "symreg RTE_OUTB_DG_DATA_RTP_CTRL.*"
    $ts.dut.run "symreg RTE_OUTB_PDU_RECV_CNT[5].*"
    $ts.dut.run "symreg rte_outb_rtp_dbg.*"
  end

  $ts.pc.try "ef tx eth_red data hex 00000000800000000000000000000000000000008000146b07d00000ffffffffffff00000000000188928002deadbeefdead80ff00000000000000000000000000000beef000000000000000000000000000000000deaddeadbeefdead80ff000000000000000000000000000000000000000000deadbeefdaadbaadcaadbaad0000000000000000aabbccddeeffaa0000000000deadbeefdead80ff00000000000000000000000000000beef000000000000000000000000000000000deaddeadbeefdead80ff000000000000000000000000000000000000000000deadbeefdaadbaadcaadbaad0000000000000000aabbccddeeffaa00000000000102030405060708090a0b0c0102030405060708090a0b0c07d03500"

  #$ts.pc.try "ef tx eth_green ifh-mas bypass 1 rtp-id 5 dest 0b000010 rtp-subid 0 pn-data-status 0x35 pn-tf-status_zero 0x01 \
  #                      pn-cc 0x07d0 eth profinet-rtc frameid 0x8002 data deadbeefdead80ff cycle 0x7d0 "
  #$ts.pc.try "ef tx eth_green ifh-mas bypass 1 rtp-id 5 dest 0b000010 rtp-subid 0 pn-data-status 0x35 pn-tf-status_zero 0x01 \
  #                      pn-cc 0x07d5 eth profinet-rtc frameid 0x8002 data deadbeefdead80ff cycle 0x7d5 "

end

test "Read Data" do
  0.upto(127) do |i|
     $ts.dut.run "symreg RTE_OUTB_DG_DATA_ADDR   #{i}"    #Read address 0x01
     $ts.dut.run "symreg RTE_OUTB_DG_DATA"
  end

end

test "Status_Verification" do
  $ts.dut.run "symreg RTE_OUTB_RTP_STICKY_BITS[5].*"
  $ts.dut.run "symreg RTE_OUTB_RTP_STICKY_BITS[5]"
  $ts.dut.run "symreg RTE_OUTB_DG_STICKY_BITS[1].*"
  $ts.dut.run "symreg RTE_OUTB_STICKY_BITS.*"
  $ts.dut.run "symreg RTE_OUTB_STICKY_BITS"
  $ts.dut.run "symreg RTE_OUTB_DG_DATA_RTP_CTRL.*"
  $ts.dut.run "symreg RTE_OUTB_PDU_RECV_CNT[5].*"
  $ts.dut.run "symreg rte_outb_rtp_dbg.*"
end
