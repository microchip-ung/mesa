#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

EVENT_PERIOD    = 1
EVENT_PRIORITY = 2
EVENT_ZERO_PERIO = 3
EVENT_RDI = 4
EVENT_LOC = 5
EVENT_MEP = 6
EVENT_MEG = 7
EVENT_LEVEL = 8
EVENT_PORT_MOVE = 9
EVENT_TLV_PORT = 10
EVENT_TLV_IF = 11
EVENT_NONE = 12
EVENT_NONE_LOC = 13
EVENT_CLEAR = 14
EVENT_LOC_ALONE = 15

EVENT_MASK_NONE                = 0,
EVENT_MASK_CCM_PERIOD          = 1 << 0,
EVENT_MASK_CCM_ZERO_PERIOD     = 1 << 1,
EVENT_MASK_CCM_PRIORITY        = 1 << 2,
EVENT_MASK_CCM_LOC             = 1 << 3,
EVENT_MASK_CCM_MEP_ID          = 1 << 4,
EVENT_MASK_CCM_MEG_ID          = 1 << 5,
EVENT_MASK_CCM_MEG_LEVEL       = 1 << 6,
EVENT_MASK_CCM_RX_RDI          = 1 << 7,
EVENT_MASK_CCM_SRC_PORT_MOVE   = 1 << 8,
EVENT_MASK_CCM_TLV_PORT_STATUS = 1 << 9,
EVENT_MASK_CCM_TLV_IF_STATUS   = 1 << 10,
EVENT_MASK_ALL                 = 0xFFF

CAUSE_LOC = 1
CAUSE_LEVEL = 2
CAUSE_PRIO = 3
CAUSE_NO_PRIO = 4
CAUSE_NONE = 5

PDU_CCM = 1
PDU_CCM_SEQ = 2
PDU_CCM_TLV = 3
PDU_LOW_LEVEL = 4
PDU_LAPS = 5
PDU_LBM = 6
PDU_LBR = 7
PDU_LTM = 8
PDU_LTR = 9
PDU_VERSION = 10
PDU_DMAC = 11
PDU_OPCODE = 12
PDU_HIGH_LEVEL = 13
PDU_TX_LOW_LEVEL = 14
PDU_LBR_TRANS = 15
PDU_NONE = 100
PDU_CLEAR = 101

TLV_NONE = 1
TLV_PORT = 2
TLV_IF = 3

REQUEST_MANUEL_SWITCH = 0x07

OAM_CNT_ALL = 1

ISDX_NONE = 0xFFFFFFFF #Allocate no ISDX
ISDX_NEW  = 0xFFFFFFFE #Allocate new ISDX
IFLOW_ID_NONE = 0
VOE_IDX_NONE = 0xFFFFFFFF
VOI_IDX_NONE = 0xFFFFFFFF
PORT_NO_NONE = 0xFFFFFFFF
VCE_ID_LAST = 0
TCE_ID_LAST = 0
COUNTER_NONE = 0xFFFFFFFF
LBM_TRANSACTION_ID_NONE = 0xFFFFFFFF
IGNORE = 0xFFFFFFFF

FAMILY_UNKNOWN = 0
FAMILY_CARACAL = 2
FAMILY_SERVAL  = 4
FAMILY_SERVALT = 6
FAMILY_JAGUAR2 = 7
FAMILY_OCELOT  = 8
FAMILY_SPARX5  = 9
FAMILY_LAN966X = 10

MC_ADDR = [0x01,0x80,0xC2,0x00,0x00,0x30]
MC_ADDR_INV = [0x01,0x80,0xC3,0x00,0x00,0x30]
UC_ADDR = [0,0,0,0,5,6]
UC_ADDR_INV = [0,0,0,4,5,6]
MC_STRING = "01:80:C2:00:00:30"
MC_STRING_INV = "01:80:C3:00:00:30"
UC_STRING = "00:00:00:00:05:06"
UC_STRING_INV = "00:00:00:04:05:06"
SC_STRING = "00:00:00:00:05:07"
MC_TEST = "01:15:4E:00:00:01"
MC_CONTROL = "01:15:4E:00:00:02"
MC_ITEST = "01:15:4E:00:00:03"
MC_ICONTROL = "01:15:4E:00:00:04"

$cap_event_supported = 0
$cap_oam_v1 = false
$cap_oam_v2 = false
$cap_cosid = false
$cap_vstax = false
$cap_epid = 0
$ts = 0
$cap_tx_ifh_size = 0

def vop_config(cpu_queue)
    test "vop_config  cpu_queue #{cpu_queue}" do

    conf = $ts.dut.call("mesa_vop_conf_get")

    conf["multicast_dmac"]["addr"] = MC_ADDR
    conf["auto_copy_period"][0] = 4*1000*1000
    conf["auto_copy_period"][1] = 1000*1000
    conf["voe_queue_ccm"] = cpu_queue
    conf["voe_queue_lt"] = cpu_queue
    conf["voe_queue_lbm"] = cpu_queue
    conf["voe_queue_lbr"] = cpu_queue
    conf["voe_queue_aps"] = cpu_queue
    conf["voe_queue_err"] = cpu_queue
    conf["voi_queue"] = cpu_queue
    conf["mrp_queue"] = cpu_queue

    $ts.dut.call("mesa_vop_conf_set", conf)
    end
end

def voe_alloc(type, port)
    $voe_idx = 0

    test "voe_alloc  type: #{type}  port: #{port}" do

    conf = {"type"=>0, "port"=>0, "direction"=>0}

    conf["type"] = type
    conf["direction"] = "MESA_OAM_DIRECTION_DOWN"
    conf["port"] = port

    $voe_idx = $ts.dut.call("mesa_voe_alloc", conf)
    end

    $voe_idx
end

def voe_config(voe_idx, meg_level, iflow_id)
    test "voe_config  voe_idx: #{voe_idx}  meg_level: #{meg_level}  iflow_id: #{iflow_id}" do

    conf = $ts.dut.call("mesa_voe_conf_get", voe_idx)

    conf["enable"] = true
    conf["unicast_mac"]["addr"] = UC_ADDR
    conf["meg_level"] = meg_level
    conf["dmac_check_type"] = "MESA_VOE_DMAC_CHECK_BOTH"
    if ($cap_vop_cfm)
        conf["loop_iflow_id"] = iflow_id
    end
    conf["block_mel_high"] = false

    $ts.dut.call("mesa_voe_conf_set", voe_idx, conf)
    end
end

def voe_config_change(voe_idx, dmac_check, mel_high)
    test "voe_config_change  voe_idx: #{voe_idx}  dmac_check: #{dmac_check}  mel_high: #{mel_high}" do

    conf = $ts.dut.call("mesa_voe_conf_get", voe_idx)

    conf["dmac_check_type"] = dmac_check
    conf["block_mel_high"] = mel_high

    $ts.dut.call("mesa_voe_conf_set", voe_idx, conf)
    end
end

def voi_alloc(direction, port)
    $voe_idx = 0

    test "voi_alloc  direction: #{direction}  port: #{port}" do

    conf = {"direction"=>0, "port"=>0}

    conf["direction"] = direction
    conf["port"] = port

    $voe_idx = $ts.dut.call("mesa_voi_alloc", conf)
    end

    $voe_idx
end

def voi_config(voi_idx, meg_level)
    test "voi_config  voi_idx: #{voi_idx}  meg_level: #{meg_level}" do

    conf = $ts.dut.call("mesa_voi_conf_get", voi_idx)

    conf["enable"] = true
    conf["unicast_mac"]["addr"] = UC_ADDR
    conf["meg_level"] = meg_level
    conf["lbm_cpu_redir"] = false
    conf["ltm_cpu_redir"] = false
    conf["raps_handling"] = "MESA_OAM_RAPS_HANDLING_NONE"

    $ts.dut.call("mesa_voi_conf_set", voi_idx, conf)
    end
end

def voe_cc_config(voe_idx, enable, peer_mepid, megid, prio, period, cpu_copy="MESA_OAM_CPU_COPY_ALL", seq_no=false, selected=false)
    test "voe_cc_config  voe_idx: #{voe_idx}  enable: #{enable}  peer_mepid: #{peer_mepid}  megid: #{megid}  prio: #{prio}  period: #{period}  cpu_copy: #{cpu_copy}  seq_no: #{seq_no}  selected: #{selected}" do

    conf = $ts.dut.call("mesa_voe_cc_conf_get", voe_idx)

    conf_megid = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    megid.each_with_index {|val, index| 
        conf_megid[index] = val
    }

    conf["enable"] = enable
    conf["cpu_copy"] = "MESA_OAM_CPU_COPY_NONE"
    conf["seq_no_update"] = false
    conf["count_as_selected"] = false
    if (enable)
        conf["cpu_copy"] = cpu_copy
        conf["seq_no_update"] = seq_no
        conf["count_as_selected"] = selected
        conf["expected_period"] = period
        conf["expected_priority"] = prio
        conf["expected_megid"] = conf_megid
        conf["expected_peer_mepid"] = peer_mepid
    end

    $ts.dut.call("mesa_voe_cc_conf_set", voe_idx, conf)

    events = EVENT_MASK_ALL
    $ts.dut.call("mesa_voe_event_mask_set", voe_idx, events, enable)
    end
end

def voe_cc_change(voe_idx, period)
    test "voe_cc_change  voe_idx: #{voe_idx}  period: #{period}" do

    conf = $ts.dut.call("mesa_voe_cc_conf_get", voe_idx)

    conf["expected_period"] = period

    $ts.dut.call("mesa_voe_cc_conf_set", voe_idx, conf)
    end
end

def voe_laps_config(voe_idx, enable, count_as_selected)
    test "voe_laps_config  voe_idx: #{voe_idx}  enable: #{enable}  count_as_selected: #{count_as_selected}" do

    conf = $ts.dut.call("mesa_voe_laps_conf_get", voe_idx)

    conf["enable"] = enable
    if (enable)
        conf["cpu_copy"] = true
        conf["count_as_selected"] = count_as_selected
    end

    $ts.dut.call("mesa_voe_laps_conf_set", voe_idx, conf)
    end
end

def voe_lb_config(voe_idx, enable, count_as_selected, trans_id, lbm_copy = false)
    test "voe_lb_config  voe_idx: #{voe_idx}  enable: #{enable}  count_as_selected: #{count_as_selected}  trans_id: #{trans_id}  lbm_copy: #{lbm_copy}" do

    conf = $ts.dut.call("mesa_voe_lb_conf_get", voe_idx)

    conf["enable"] = enable
    if (enable)
        conf["count_as_selected"] = count_as_selected
        conf["lbm_cpu_copy"] = lbm_copy
        conf["lbr_cpu_copy"] = "MESA_OAM_CPU_COPY_ALL"
        conf["trans_id"] = trans_id
    end

    $ts.dut.call("mesa_voe_lb_conf_set", voe_idx, conf)
    end
end

def voe_lt_config(voe_idx, enable, count_as_selected)
    test "voe_lt_config  voe_idx: #{voe_idx}  enable: #{enable}  count_as_selected: #{count_as_selected}" do

    conf = $ts.dut.call("mesa_voe_lt_conf_get", voe_idx)

    conf["enable"] = enable
    if (enable)
        conf["count_as_selected"] = count_as_selected
        conf["ltm_cpu_copy"] = true
        conf["ltr_cpu_copy"] = true
    end

    $ts.dut.call("mesa_voe_lt_conf_set", voe_idx, conf)
    end
end

def voi_raps_config(voi_idx, handling)
    test "voi_raps_config  voi_idx: #{voi_idx}  handling: #{handling}" do

    conf = $ts.dut.call("mesa_voi_conf_get", voi_idx)

    conf["raps_handling"] = handling

    $ts.dut.call("mesa_voi_conf_set", voi_idx, conf)
    end
end

def voi_lbm_config(voi_idx, redir)
    test "voi_lbm_config  voi_idx: #{voi_idx}  redir: #{redir}" do

    conf = $ts.dut.call("mesa_voi_conf_get", voi_idx)

    conf["lbm_cpu_redir"] = redir

    $ts.dut.call("mesa_voi_conf_set", voi_idx, conf)
    end
end

def voi_ltm_config(voi_idx, redir)
    test "voi_ltm_config  voi_idx: #{voi_idx}  redir: #{redir}" do

    conf = $ts.dut.call("mesa_voi_conf_get", voi_idx)

    conf["ltm_cpu_redir"] = redir

    $ts.dut.call("mesa_voi_conf_set", voi_idx, conf)
    end
end

def vce_level_mask(l_level, h_level)
    t_i("vce_level_mask  l_level: #{l_level}  h_level: #{h_level}")

    mask = (0x01 << (h_level - l_level)) - 1;   # "don't care" mask value is calculated
    mask <<= l_level;                           # mask is rotated to cover levels
    mask = ~mask;                               # Mask is complimented as "don't care" is '0'
    mask = mask & 0xFF
    mask
end

def vce_level_value(l_level)
    t_i("vce_level_value  l_level: #{l_level}")

    value = (0x01 << l_level) - 1;
    value
end

def vce_config(id, port_list, vid, level_val, level_mask, flow_id, oam_detect, before_id=VCE_ID_LAST)
    test "vce_config  id: #{id}  port_list: #{port_list}  vid: #{vid}  level_val: #{level_val}  level_mask: #{level_mask}  flow_id: #{flow_id}  oam_detect: #{oam_detect}" do

    vce = $ts.dut.call("mesa_vce_init", "MESA_VCE_TYPE_ETYPE")

    vce["id"] = id

    key = vce["key"]
    key["port_list"] = port_list
    key["type"] = "MESA_VCE_TYPE_ETYPE"
    tag = key["tag"]
    tag["tagged"] = (vid != 0) ? "MESA_VCAP_BIT_1" : "MESA_VCAP_BIT_0"
    tag["s_tag"] = "MESA_VCAP_BIT_ANY"
    tag["vid"]["value"] = vid
    tag["vid"]["mask"] = (vid != 0) ? 0xFFFF : 0
    tag["dei"] = "MESA_VCAP_BIT_ANY"
    tag["pcp"]["mask"] = 0
    frame = key["frame"]["etype"]
    frame["etype"]["value"][0] = 0x89
    frame["etype"]["value"][1] = 0x02
    frame["etype"]["mask"][0] = 0xFF
    frame["etype"]["mask"][1] = 0xFF
    frame["mel"]["value"] = level_val
    frame["mel"]["mask"] = level_mask

    action = vce["action"]
    action["flow_id"] = flow_id
    action["oam_detect"] = oam_detect

    $ts.dut.call("mesa_vce_add", before_id, vce)
    end
end

def tce_config(id, port, vid, iflow_id, eflow_id)
    test "tce_config  id: #{id}  port: #{port}  vid: #{vid}  iflow_id: #{iflow_id}  eflow_id: #{eflow_id}" do

    tce = $ts.dut.call("mesa_tce_init")

    tce["id"] = id

    key = tce["key"]
    key["port_list"] = "#{port}"
    key["vid"] = (iflow_id == IFLOW_ID_NONE) ? vid : 0
    key["flow_enable"] = (iflow_id != IFLOW_ID_NONE) ? true : false
    key["flow_id"] = iflow_id

    action = tce["action"]
    action["flow_id"] = eflow_id
    action["tag"]["tpid"] = (vid != 0) ? "MESA_TPID_SEL_PORT" : "MESA_TPID_SEL_NONE"

    $ts.dut.call("mesa_tce_add", VCE_ID_LAST, tce)
    end
end

def iflow_config(flow_id, voe_idx, voi_idx)
    test "iflow_config  flow_id: #{flow_id}  voe_idx: #{voe_idx}  voi_idx: #{voi_idx}" do

    iflow = $ts.dut.call("mesa_iflow_conf_get", flow_id)

    iflow["voe_idx"] = voe_idx
    iflow["voi_idx"] = voi_idx

    $ts.dut.call("mesa_iflow_conf_set", flow_id, iflow)
    end
end

def eflow_config(flow_id, voe_idx, voi_idx)
    test "eflow_config  flow_id: #{flow_id}  voe_idx: #{voe_idx}  voi_idx: #{voi_idx}" do

    eflow = $ts.dut.call("mesa_eflow_conf_get", flow_id)

    eflow["voe_idx"] = voe_idx
    eflow["voi_idx"] = voi_idx

    $ts.dut.call("mesa_eflow_conf_set", flow_id, eflow)
    end
end

def qos_port_config(port, def_qosid)
    test "qos_port_config  def_qosid: #{def_qosid}" do

    conf = $ts.dut.call("mesa_qos_port_conf_get", port)

    conf["cosid"] = def_qosid   # This only works for V2 platform with COSID. Not Serval.
    conf["default_prio"] = def_qosid
    conf["tag"]["pcp"] = def_qosid  # This is for untagged frames on Serval. Classified PCP is the priority.
    conf["tag"]["class_enable"] = true
    conf["tag"]["pcp_dei_map"][0][0]["prio"] =  def_qosid

    $ts.dut.call("mesa_qos_port_conf_set", port, conf)
    end
end

def frame_tx(frame, port, frame0, frame1, frame2, framenpi)
    cmd = "ef name f1 " + frame + "tx #{$ts.pc.p[port]} name f1 "

    if (frame0 != " ")  # Frame with a space means that no receive check should be done
        cmd += "rx #{$ts.pc.p[$port0]} "   # This means the no received frame is expected
        if (frame0 != "")   # This means that frame0 received is expected
            cmd += frame0
        end
    end

    if (frame1 != " ")  # Frame with a space means that no receive check should be done
        cmd += "rx #{$ts.pc.p[$port1]} "   # This means the no received frame is expected
        if (frame1 != "")   # This means that frame1 received is expected
            cmd += frame1
        end
    end

    if (frame2 != " ")  # Frame with a space means that no receive check should be done
        cmd += "rx #{$ts.pc.p[$port2]} "   # This means the no received frame is expected
        if (frame2 != "")   # This means that frame2 received is expected
            cmd += frame2
        end
    end

    if (framenpi != " ")  # Frame with a space means that no receive check should be done
        cmd += "rx #{$ts.pc.p[$npi_port]} "   # This means the no received frame is expected
        if (framenpi != "")   # This means that framenpi received is expected
            cmd += framenpi
        end
    end

    $ts.pc.run cmd
end

def ccm_pdu_create(level, period, sequence, mepid, megid, rdi=0, version=0, tlv=TLV_NONE)
    $ccm_pdu = ""

    test "ccm_pdu_create  level #{level}  period #{period}  sequence #{sequence}  mepid #{mepid}  megid #{megid}  rdi: #{rdi}  version: #{version}, tlv: #{tlv}" do

    peri = 0
    if (period == "MESA_VOE_CCM_PERIOD_3_3_MS")
        peri = 1
    end
    if (period == "MESA_VOE_CCM_PERIOD_1_SEC")
        peri = 4
    end


    # MEG ID in CC PDU is a hex_octet element meaning that the 'megid' array of uint must be converted to a hexadecimal values separated by ':'
    megid_hex = ""
    megid.each_with_index {|val, index| 
        megid_hex = megid_hex + "#{val.to_s(16)}"
        if (index != (megid.length-1))
            megid_hex = megid_hex + ":"
        end
    }

    end_tlv = (tlv==TLV_NONE) ? 0 : (tlv==TLV_PORT) ? 2 : (tlv==TLV_IF) ? 4 : 0

    if (end_tlv == 0)
        $ccm_pdu = "oam-ccm mel #{level} version #{version} rdi #{rdi} period #{peri} seq_num #{sequence} mep_id #{mepid} meg_id #{megid_hex} "
    else
        $ccm_pdu = "oam-ccm mel #{level} version #{version} rdi #{rdi} period #{peri} seq_num #{sequence} mep_id #{mepid} meg_id #{megid_hex} end_tlv #{end_tlv}  tlv_length #{1} tlv_value #{2} "
    end
    end

    return $ccm_pdu
end

def mrp_tst_pdu_create(sequence=0)
    $pdu = ""

    test "mrp_tst_pdu_create  sequence #{sequence}" do
    $pdu = "mrp_tst c_seq_num #{sequence} "
    end

    return $pdu
end

def mrp_mrp_pdu_create(sequence=0)
    $pdu = ""

    test "mrp_mrp_pdu_create" do
    $pdu = "mrp_prop "
    end

    return $pdu
end

def unexpected_pdu_create(level, opcode, version=0)
    $lb_pdu = ""

    test "unexpected_pdu_create  level #{level}  opcode #{opcode}  version #{version}" do

    $lb_pdu = "oam-lb mel #{level} version #{version} opcode #{opcode} "
    end

    return $lb_pdu
end

def laps_pdu_create(level, request)
    $laps_pdu = ""

    test "laps_pdu_create  level #{level}  request #{request}" do

    $laps_pdu = "oam-laps mel #{level} req_sta #{request} "
    end

    return $laps_pdu
end

def raps_pdu_create(level, request)
    $raps_pdu

    test "raps_pdu_create  level #{level}  request #{request}" do

    $raps_pdu = "oam-raps mel #{level} req_sta #{request} "
    end

    return $raps_pdu
end

def lb_pdu_create(level, opcode, trans_id)
    $lb_pdu

    test "lb_pdu_create  level #{level}  opcode #{opcode}  trans_id #{trans_id}" do

    $lb_pdu = "oam-lb mel #{level} opcode #{opcode} trans_id #{trans_id} "
    end

    return $lb_pdu
end

def lbr_test_tlv_pdu_create(level, trans_id, error)
    $lbr_pdu

    test "lbr_test_tlv_pdu_create  level #{level}  trans_id #{trans_id}  error #{error}" do

    $lbr_pdu = "oam-lb mel #{level} opcode #{2} trans_id #{trans_id} type 32 tlv_length 12 pattern_type 1 crc32 #{error ? 0xb1cd85c8 : 0xb1cd85c7} "
    end

    return $lbr_pdu
end

def lt_pdu_create(level, opcode, trans_id)
    $lt_pdu

    test "ltm_pdu_create  level #{level}  opcode #{opcode}  trans_id #{trans_id}" do

    $lt_pdu = "oam-lt mel #{level} opcode #{opcode} tlv_off #{opcode == 5 ? 17 : 6} trans_id #{trans_id} "
    end

    return $lt_pdu
end

def frame_create(dmac, smac, vid=0, pcp=0, type="oam")
    $frame = ""

    test "frame_create.  dmac = #{dmac}  smac = #{smac}  vid = #{vid}  pcp = #{pcp}" do

    $frame = "eth dmac #{dmac} smac #{smac}"

    if (vid != 0)
        $frame += " ctag vid #{vid} pcp #{pcp}"
    end

    if (type == "oam")
        $frame += " et 0x8902 "
    end
    if (type == "mrp")
        $frame += " et 0x88E3 "
    end
    end

    $frame
end

def tx_ifh_create(vid, port = 0, oam_type = "MESA_PACKET_OAM_TYPE_NONE", voi = false, up = false, iflow = IFLOW_ID_NONE, pcp = 0)
    $tx_ifh = ""

    test "tx_ifh_create.  vid = #{vid}  port = #{port}  oam_type = #{oam_type}  voi #{voi}  up #{up}  iflow #{iflow}  pcp #{pcp}" do

    tx_info = $ts.dut.call("mesa_packet_tx_info_init")
    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5"))
        tx_info["dst_port"] = port
    else
        tx_info["dst_port_mask"] = up ? 0 : (0x01 << port)
    end
    tx_info["switch_frm"] = up ? true : false
    tx_info["masquerade_port"] = up ? port : PORT_NO_NONE
    tx_info["pdu_offset"] = 14
    tx_info["sequence_idx"] = 0
    tx_info["oam_type"] = oam_type
    tx_info["pipeline_pt"] = voi ? (up ? "MESA_PACKET_PIPELINE_PT_ANA_IN_VOI" : "MESA_PACKET_PIPELINE_PT_REW_IN_VOI") : "MESA_PACKET_PIPELINE_PT_REW_IN_VOE"
    tx_info["tag"]["vid"] = vid
    tx_info["iflow_id"] = up ? IFLOW_ID_NONE : iflow

    if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_SPARX5"))
        ifh = $ts.dut.call("mesa_packet_tx_hdr_encode", tx_info, 36)
    else
        if ($cap_family == chip_family_to_id("MESA_CHIP_FAMILY_LAN966X"))
            ifh = $ts.dut.call("mesa_packet_tx_hdr_encode", tx_info, 28)
        else
            ifh = $ts.dut.call("mesa_packet_tx_hdr_encode", tx_info, 32)
        end
    end

    $tx_ifh = "sp-jr2 dmac ff:ff:ff:ff:ff:ff smac fe:ff:ff:ff:ff:ff id #{$cap_epid} data hex #{ifh[0].take(ifh[1]).pack("c*").unpack("H*").first} "   #sp-jr2 is the same as lp-oc1
    end

    $tx_ifh
end

def rx_ifh_create(isdx=IGNORE, port=IGNORE)
    $ifh = ""

    test "rx_ifh_create" do

    $ifh = "sp-jr2 ign id #{$cap_epid} "    #sp-jr2 is the same as lp-oc1
    if (($cap_family == FAMILY_SERVALT) || ($cap_family == FAMILY_JAGUAR2) || ($cap_family == FAMILY_SPARX5))
        $ifh += ($cap_family != FAMILY_SPARX5) ? "ifh-jr2 ign " : "ifh-fa ign "
        if (isdx != IGNORE)
            $ifh += "vm1-isdx #{isdx} "
        end
        if (port != IGNORE)
            $ifh += "f-src-port #{$port_map[port]["chip_port"]} "
        end
    end
    if (($cap_family == FAMILY_SERVAL) || ($cap_family == FAMILY_OCELOT))
        $ifh += "efh-oc1 ign "
    end
    if ($cap_family == FAMILY_LAN966X)
        $ifh += "ifh-mas ign "
        if (port != IGNORE)
            $ifh += "src-port #{$port_map[port]["chip_port"]} "
        end
    end
    end

    $ifh
end

def check_voe_event(voe_idx, events)
    test "check_voe_event  voe_idx #{voe_idx}  events #{events}" do

    mask = $ts.dut.call("mesa_voe_event_get", voe_idx)
    t_i("mask #{mask}")

    events.each_index do |index|
        if events[index] == EVENT_PERIOD
            if (mask & EVENT_MASK_CCM_PERIOD) == 0
                t_e("Period event not found")
            end
        elsif events[index] == EVENT_PRIORITY
            if (mask & EVENT_MASK_CCM_PRIORITY) == 0
                t_e("Priority event not found")
            end
        elsif events[index] == EVENT_PORT_MOVE
            if ($cap_oam_v2 && ((mask & EVENT_MASK_CCM_SRC_PORT_MOVE) == 0))
                t_e("Port move event not found")
            end
        elsif events[index] == EVENT_TLV_PORT
            if ($cap_oam_v2 && ((mask & EVENT_MASK_CCM_TLV_PORT_STATUS) == 0))
                t_e("Port TLV event not found")
            end
        elsif events[index] == EVENT_TLV_IF
            if ($cap_oam_v2 && ((mask & EVENT_MASK_CCM_TLV_IF_STATUS) == 0))
                t_e("Interface TLV event not found")
            end
        elsif events[index] == EVENT_ZERO_PERIO
            if (mask & EVENT_MASK_CCM_ZERO_PERIOD) == 0
                t_e("Zero period event not found")
            end
        elsif events[index] == EVENT_RDI
            if (mask & EVENT_MASK_CCM_RX_RDI) == 0
                t_e("Rdi event not found")
            end
        elsif events[index] == EVENT_LOC
            if (mask & EVENT_MASK_CCM_LOC) == 0
                t_e("Loc event not found")
            end
        elsif events[index] == EVENT_MEP
            if (mask & EVENT_MASK_CCM_MEP_ID) == 0
                t_e("Mep event not found")
            end
        elsif events[index] == EVENT_MEG
            if (mask & EVENT_MASK_CCM_MEG_ID) == 0
                t_e("Meg event not found")
            end
        elsif events[index] == EVENT_LEVEL
            if ($cap_oam_v2 && ((mask & EVENT_MASK_CCM_MEG_LEVEL) == 0))
                t_e("Level event not found")
            end
        elsif events[index] == EVENT_NONE
            if (mask != 0)
                t_e("NONE event not found")
            end
        elsif events[index] == EVENT_CLEAR
        else
            t_e("Unknown events")
        end
    end
    end
end


def check_cc_status_values(voe_idx, rx_port, port_tlv, if_tlv)
    test "check_cc_status_values  voe_idx: #{voe_idx}  rx_port: #{rx_port}  port_tlv: #{port_tlv}  if_tlv: #{if_tlv}" do

    status = $ts.dut.call("mesa_voe_cc_status_get", voe_idx)

    if ($cap_oam_v2)
        if (status["rx_port"] != rx_port)
            t_e("Unexpected rx_port. expected #{rx_port} received #{status["rx_port"]}")
        end
        if (status["port_status_tlv"] != port_tlv)
            t_e("Unexpected port_status_tlv. expected #{port_tlv} received #{status["port_status_tlv"]}")
        end
        if (status["if_status_tlv"] != if_tlv)
            t_e("Unexpected if_status_tlv. expected #{if_tlv} received #{status["if_status_tlv"]}")
        end
    end
    end
end

def check_cc_status(voe_idx, status)
    test "check_cc_status  voe_idx: #{voe_idx}  status: #{status}" do

    cc_status = $ts.dut.call("mesa_voe_cc_status_get", voe_idx)

    status.each_index do |index|
        if status[index] == EVENT_PERIOD
            if (cc_status["period_unexp"] != true)
                t_e("Period status not found")
            end
        elsif status[index] == EVENT_PRIORITY
            if (cc_status["priority_unexp"] != true)
                t_e("Priority status not found")
            end
        elsif status[index] == EVENT_ZERO_PERIO
            if (cc_status["zero_period"] != true)
                t_e("Zero status event not found")
            end
        elsif status[index] == EVENT_RDI
            if (cc_status["rdi"] != true)
                t_e("Rdi status not found")
            end
        elsif status[index] == EVENT_LOC
            if (cc_status["loc"] != true)
                t_e("Loc status not found")
            end
        elsif status[index] == EVENT_MEP
            if (cc_status["mep_id_unexp"] != true)
                t_e("Mep status not found")
            end
        elsif status[index] == EVENT_MEG
            if (cc_status["meg_id_unexp"] != true)
                t_e("Meg status not found")
            end
        elsif status[index] == EVENT_LEVEL
            if ($cap_oam_v2 && (cc_status["mel_unexp"] != true))
                t_e("Level status not found")
            end
        elsif status[index] == EVENT_NONE_LOC
            if (cc_status["loc"] == true)
                t_e("None Loc status not found")
            end
        elsif status[index] == EVENT_NONE
            if ((cc_status["period_unexp"] == true) ||
                (cc_status["priority_unexp"] == true) ||
                (cc_status["zero_period"] == true) ||
                (cc_status["rdi"] == true) ||
                (cc_status["loc"] == true) ||
                (cc_status["mep_id_unexp"] == true) ||
                (cc_status["meg_id_unexp"] == true) ||
                ($cap_oam_v2 && (cc_status["mel_unexp"] == true)))
                t_e("NONE status not found")
            end
        elsif status[index] == EVENT_LOC_ALONE
            if ((cc_status["loc"] == false) ||
                (cc_status["period_unexp"] == true) ||
                (cc_status["priority_unexp"] == true) ||
                (cc_status["zero_period"] == true) ||
                (cc_status["rdi"] == true) ||
                (cc_status["mep_id_unexp"] == true) ||
                (cc_status["meg_id_unexp"] == true) ||
                ($cap_oam_v2 && (cc_status["mel_unexp"] == true)))
                t_e("LOC_ALONE status not found")
            end
        else
            t_e("Unknown status")
        end
    end
    end
end

def check_pdu_seen(voe_idx, pdu_type)
    test "check_pdu_seen  voe_idx: #{voe_idx}  pdu_type: #{pdu_type}" do

    voe_status = $ts.dut.call("mesa_voe_status_get", voe_idx)
    cc_status = $ts.dut.call("mesa_voe_cc_status_get", voe_idx)
    if ($cap_vop_cfm)
        lt_status = $ts.dut.call("mesa_voe_lt_status_get", voe_idx)
        lb_status = $ts.dut.call("mesa_voe_lb_status_get", voe_idx)
        laps_status = $ts.dut.call("mesa_voe_laps_status_get", voe_idx)
    end

    if (pdu_type == PDU_CCM)
        if (cc_status["seen"] != true)
            t_e("CCM pdu not found")
        end
        if ($cap_oam_v2 && (voe_status["rx_level_low_seen"] == true))
            t_e("PDU-LOW pdu unexpectedly found")
        end
    elsif (pdu_type == PDU_CCM_SEQ)
        if ($cap_oam_v2 && (cc_status["seq_unexp_seen"] != true))
            t_e("CCM-SEQ pdu not found")
        end
    elsif (pdu_type == PDU_CCM_TLV)
        if ($cap_oam_v2 && (cc_status["tlv_seen"] != true))
            t_e("CCM-TLV pdu not found")
        end
    elsif ((pdu_type == PDU_LAPS) && $cap_vop_cfm)
        if (laps_status["seen"] != true)
            t_e("LAPS pdu not found")
        end
    elsif ((pdu_type == PDU_LBM) && $cap_vop_cfm)
        if (lb_status["lbm_seen"] != true)
            t_e("LBM pdu not found")
        end
        if (lb_status["lbr_seen"] == true)
            t_e("LBR pdu unexpectedly found")
        end
    elsif ((pdu_type == PDU_LBR) && $cap_vop_cfm)
        if (lb_status["lbr_seen"] != true)
            t_e("LBR pdu not found")
        end
        if (lb_status["lbm_seen"] == true)
            t_e("LBM pdu unexpectedly found")
        end
    elsif ((pdu_type == PDU_LBR_TRANS) && $cap_vop_cfm)
        if ($cap_oam_v2 && (lb_status["trans_unexp_seen"] != true))
            t_e("LBR-TRANSACTION pdu not found")
        end
    elsif ((pdu_type == PDU_LTM) && $cap_vop_cfm)
        if (lt_status["ltm_seen"] != true)
            t_e("LTM pdu not found")
        end
        if (lt_status["ltr_seen"] == true)
            t_e("LTR pdu unexpectedly found")
        end
    elsif ((pdu_type == PDU_LTR) && $cap_vop_cfm)
        if (lt_status["ltr_seen"] != true)
            t_e("LTR pdu not found")
        end
        if (lt_status["ltm_seen"] == true)
            t_e("LTM pdu unexpectedly found")
        end
    elsif (pdu_type == PDU_DMAC)
        if (voe_status["dmac_unexp_seen"] != true)
            t_e("DMAC unexpected pdu not found")
        end
    elsif (pdu_type == PDU_OPCODE)
        if (voe_status["opcode_unexp_seen"] != true)
            t_e("Opcode unexpected pdu not found")
        end
    elsif (pdu_type == PDU_TX_LOW_LEVEL)
        if ($cap_vop_cfm && (voe_status["tx_level_low_seen"] != true))
            t_e("TX LOW-LEVEL pdu not found")
        end
    elsif (pdu_type == PDU_VERSION)
        if ($cap_oam_v2 && (voe_status["version_unexp_seen"] != true))
            t_e("Version unexpected pdu not found")
        end
    elsif (pdu_type == PDU_HIGH_LEVEL)
        if ($cap_oam_v2 && (voe_status["rx_level_high_seen"] != true))
            t_e("HIGH-LEVEL pdu not found")
        end
    elsif (pdu_type == PDU_LOW_LEVEL)
        if ($cap_oam_v2 && (voe_status["rx_level_low_seen"] != true))
            t_e("LOW-LEVEL pdu not found")
        end
    elsif (pdu_type == PDU_NONE)
        if ((cc_status["seen"] == true) ||
            ($cap_oam_v2 && (cc_status["tlv_seen"] == true)) ||
            ($cap_oam_v2 && (cc_status["seq_unexp_seen"] == true)) ||
            (voe_status["opcode_unexp_seen"] == true) ||
            (voe_status["dmac_unexp_seen"] == true) ||
            ($cap_oam_v2 && (voe_status["version_unexp_seen"] == true)) ||
            ($cap_oam_v2 && (voe_status["rx_level_low_seen"] == true)) ||
            ($cap_oam_v2 && (voe_status["rx_level_high_seen"] == true)) ||
            ($cap_vop_cfm && voe_status["tx_level_low_seen"] == true) ||
            ($cap_vop_cfm && (lt_status["ltm_seen"] == true)) ||
            ($cap_vop_cfm && (lt_status["ltr_seen"] == true)) ||
            ($cap_vop_cfm && (lb_status["lbm_seen"] == true)) ||
            ($cap_vop_cfm && (lb_status["lbr_seen"] == true)) ||
            ($cap_oam_v2 && (lb_status["trans_unexp_seen"] == true)) ||
            ($cap_vop_cfm && (laps_status["seen"] == true)))
            t_e("NONE pdu not found")
        end
    elsif pdu_type == PDU_CLEAR
    else
        t_e("Unknown pdu_type")
    end
    end
end

def check_voe_counters(voe_idx, rx, tx, rx_sel, tx_sel, rx_discard, tx_discard)
    test "check_voe_counters  voe_idx: #{voe_idx}  rx #{rx}  tx #{tx}  rx_sel #{rx_sel}  tx_sel #{tx_sel}  rx_discard #{rx_discard}  tx_discard #{tx_discard}" do

    status = $ts.dut.call("mesa_voe_counters_get", voe_idx)

    if ((rx != COUNTER_NONE) && (status["rx_counter"] != rx))
        t_e("Unexpected rx. expected #{rx} counted #{status["rx_counter"]}")
    end
    if ((tx != COUNTER_NONE) && (status["tx_counter"] != tx) && $cap_vop_cfm)
        t_e("Unexpected tx. expected #{tx} counted #{status["tx_counter"]}")
    end

    if ($cap_vop_cfm && (rx_sel != COUNTER_NONE) && status["rx_selected_counter"] != rx_sel)
        t_e("Unexpected Select rx. expected #{rx_sel} counted #{status["rx_selected_counter"]}")
    end
    if ($cap_vop_cfm && (tx_sel != COUNTER_NONE) && status["tx_selected_counter"] != tx_sel)
        t_e("Unexpected Select tx. expected #{tx_sel} counted #{status["tx_selected_counter"]}")
    end

    if ($cap_oam_v2 && (rx_discard != COUNTER_NONE) && status["rx_discard_counter"] != rx_discard)
        t_e("Unexpected Discard rx. expected #{rx_discard} counted #{status["rx_discard_counter"]}")
    end
    if ($cap_oam_v2 && (tx_discard != COUNTER_NONE) && status["tx_discard_counter"] != tx_discard)
        t_e("Unexpected Discard tx. expected #{tx_discard} counted #{status["tx_discard_counter"]}")
    end
    end
end

def check_ccm_counters(voe_idx, ccm_rx_valid, ccm_rx_invalid, ccm_rx_seq, ccm_tx)
    test "check_ccm_counters  voe_idx: #{voe_idx}  ccm_rx_valid: #{ccm_rx_valid}  ccm_rx_invalid: #{ccm_rx_invalid}  ccm_rx_seq: #{ccm_rx_seq}  ccm_tx: #{ccm_tx}" do

    status = $ts.dut.call("mesa_voe_cc_counters_get", voe_idx)

    if (status["rx_valid_counter"] != ccm_rx_valid)
        t_e("Unexpected CCM rx valid.  Expected = #{ccm_rx_valid}  counted = #{status["rx_valid_counter"]}")
    end
    if (status["rx_invalid_counter"] != ccm_rx_invalid)
        t_e("Unexpected CCM rx invalid.  Expected = #{ccm_rx_invalid}  counted = #{status["rx_invalid_counter"]} ")
    end
    if (status["rx_oo_counter"] != ccm_rx_seq)
        t_e("Unexpected CCM rx sequence error.  Expected = #{ccm_rx_seq}  counted = #{status["rx_oo_counter"]} ")
    end
    if ((status["tx_counter"] != ccm_tx))
        t_e("Unexpected CCM tx.  Expected = #{ccm_tx}  counted = #{status["tx_counter"]}")
    end
    end
end

def check_voe_lb_counters(voe_idx, rx_lbr, rx_oo, tx_lbr, tx_lbm, tx_trans=LBM_TRANSACTION_ID_NONE, rx_trans=LBM_TRANSACTION_ID_NONE, rx_crc=0)
    test "check_voe_lb_counters  voe_idx: #{voe_idx}  rx_lbr: #{rx_lbr}  rx_oo: #{rx_oo}  tx_lbr: #{tx_lbr}  tx_lbm: #{tx_lbm}  tx_trans: #{tx_trans}  rx_trans: #{rx_trans}" do

    status = $ts.dut.call("mesa_voe_lb_counters_get", voe_idx)

    if (status["rx_lbr_counter"] != rx_lbr)
        t_e("Unexpected LBR rx valid.  Expected #{rx_lbr}  Counted #{status["rx_lbr_counter"]}")
    end
    if (status["rx_lbr_oo_counter"] != rx_oo)
        t_e("Unexpected LBR OO.  Expected #{rx_oo}  Counted #{status["rx_lbr_oo_counter"]}")
    end
    if ($cap_oam_v2 && (status["rx_lbr_crc_counter"] != rx_crc))
        t_e("Unexpected LBR rx CRC.  Expected #{rx_crc}  Counted #{status["rx_lbr_crc_counter"]}")
    end
    if ($cap_oam_v2 && (status["tx_lbr_counter"] != tx_lbr))
        t_e("Unexpected LBR tx.  Expected #{tx_lbr}  Counted #{status["tx_lbr_counter"]}")
    end
    if (status["tx_lbm_counter"] != tx_lbm)
        t_e("Unexpected LBM tx.  Expected #{tx_lbm}  Counted #{status["tx_lbm_counter"]}")
    end

    status = $ts.dut.call("mesa_voe_lb_status_get", voe_idx)

    if ((tx_trans != LBM_TRANSACTION_ID_NONE) && (status["tx_trans_id"] != tx_trans))
        t_e("Unexpected tx trans id.  Expected #{tx_trans}  Counted #{status["tx_trans_id"]}")
    end
    if ((rx_trans != LBM_TRANSACTION_ID_NONE) && (status["rx_trans_id"] != rx_trans))
        t_e("Unexpected rx trans id.  Expected #{rx_trans}  Counted #{status["rx_trans_id"]}")
    end
    end
end

def clear_all_counters(voe_idx, mask)
    test "clear_all_counters  voe_idx: #{voe_idx}" do

    $ts.dut.call("mesa_voe_counters_clear", voe_idx)
    $ts.dut.call("mesa_voe_cc_counters_clear", voe_idx)
    if ($cap_vop_cfm)
        $ts.dut.call("mesa_voe_lb_counters_clear", voe_idx)
    end
    end
end

