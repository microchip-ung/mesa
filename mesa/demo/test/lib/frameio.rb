# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'bit-struct'
require 'socket'
require 'hexdump'

ET_LLC  = 0x0000 # Pseudo value
ET_SNAP = 0x0001 # Pseudo value
ET_ARP  = 0x0806
ET_IPv4 = 0x0800
ET_IPv6 = 0x86dd
IP_NO_ICMP = 1

IP_PROTO_ICMP = 1
IP_PROTO_IGMP = 2
IP_PROTO_TCP  = 6
IP_PROTO_UDP  = 17

DHCP_SERVER_PORT = 67
DHCP_CLIENT_PORT = 68


class Frame < BitStruct
    hex_octets  :dmac,    48,    "Destination mac address"
    hex_octets  :smac,    48,    "Source mac address"
    rest        :data,           "Data"
end

class FrameHdr < BitStruct
    hex_octets  :mac_dst,    48,    "Destination mac address"
    hex_octets  :mac_src,    48,    "Source mac address"
    unsigned    :ether_type, 16,    "Ether type"
    rest        :data,              "Data"
end

class VlanTag < BitStruct
    unsigned    :tpid,    16,    "Tag Protocol ID"
    unsigned    :pcp,      3,    "Priority Code Point"
    unsigned    :dei,      1,    "Drop Eligble Indicator"
    unsigned    :vid,     12,    "VLAN Identifier"
    rest        :data,           "Data"
end

class EtherType < BitStruct
    unsigned    :etype,   16,    "Ether type"
    rest        :data,           "Data"
end

class Payload < BitStruct
    rest        :data,              "Data"
end

class Crc32 < BitStruct
    unsigned    :crc,        32,    "CRC"
end

# IEEE 802.3ah PDUs {
class Dot3ahPdu < BitStruct
    unsigned    :subtype,   8, "Slow protocol subtype"
    unsigned    :flags,    16, "Various flags as defined in IEEE 802.3ah"
    unsigned    :code,      8, "OAMPDU code which identifies the TLVs code"
    rest        :data,         "Data"
end

class Dot3ahTlv < BitStruct
    unsigned    :tlvType,   8, "Identifies the TLV type"
    unsigned    :tlvLen,    8, "TLV Length"
    unsigned    :tlvVer,    8, "TLV version"
    unsigned    :tlvRev,   16, "TLV revision"
    rest        :data,         "Data"
end

class Dot3ahLocalInfoTlv < BitStruct
    unsigned    :states,    8, "OAM DTE State of the Mux and the parser"
    unsigned    :config,    8, "OAM configuration"
    unsigned    :maxPduSz, 16, "OAM PDU max size"
    hex_octets  :Oui,      24, "OUI"
    hex_octets  :Vsi,      24, "Vendor specific information"
    rest        :data,         "Data"
end
# IEEE 802.3ah PDU }

class MplsLabel < BitStruct
    unsigned    :l,       20, "Label"
    unsigned    :tc,       3, "TC"
    unsigned    :s,        1, "S-bit"
    unsigned    :ttl,      8, "TTL"
    rest        :data,        "Data"
end

class IPv4 < BitStruct
    unsigned    :ip_v,     4,     "Version"
    unsigned    :ip_hl,    4,     "Header length"
    unsigned    :ip_tos,   8,     "TOS"
    unsigned    :ip_len,  16,     "Length"
    unsigned    :ip_id,   16,     "ID"
    unsigned    :ip_flags, 3,     "Flags"
    unsigned    :ip_off,  13,     "Frag offset"
    unsigned    :ip_ttl,   8,     "TTL"
    unsigned    :ip_proto, 8,     "Protocol"
    unsigned    :ip_sum,  16,     "Checksum"
    octets      :ip_src,  32,     "Source addr"
    octets      :ip_dst,  32,     "Dest addr"
    rest        :data,            "Data"

    initial_value.ip_v    = 4
    initial_value.ip_hl   = 5

    # Calculate and set IP header checksum
    def set_ip_checksum
        self.ip_sum = 0
        check_sum_data = to_s[0..(ip_hl*4 - 1)].unpack("S>*")
        sum = check_sum_data.inject(0) { |acc, byte| acc + byte }
        sum = sum + (sum >> 16)
        self.ip_sum = ~sum
    end
end

class IgmpV2 < BitStruct
    unsigned	:mtype,	8,	"message type"
    unsigned	:maxrt,	8,	"maximum respone time"
    unsigned	:chksum,16,	"IGMP checksum"
    octets	:grpadd,32,	"group Address"
    def set_ip_checksum
        self.chksum = 0
        check_sum_data = to_s[0..15].unpack("S>*")
        sum = check_sum_data.inject(0) { |acc, byte| acc + byte }
        sum = sum + (sum >> 16)
        self.chksum = ~sum
    end
end

class IPv4PseudoHdr < BitStruct
    octets      :ip_src,   32,     "Source addr"
    octets      :ip_dst,   32,     "Dest addr"
    unsigned    :zeroes,    8,     "Zeroes"
    unsigned    :ip_proto,  8,     "Protocol"
    unsigned    :udp_len,  16,     "UDP Length"

    initial_value.zeroes = 0
end

class UdpHdr < BitStruct
    unsigned    :sport,     16, "Source Port"
    unsigned    :dport,     16, "Destination Port"
    unsigned    :len,       16, "length"
    unsigned    :checksum,  16, "checksum"
    rest        :data,          "Data"

    def set_udp_checksum(ip_src, ip_dst)
      self.checksum = 0x0000
      # build IPv4 pseudo-header:
      iphdr = IPv4PseudoHdr.new do |u|
        u.ip_src   = ip_src
        u.ip_dst   = ip_dst
        u.zeroes   = 0
        u.ip_proto = IP_PROTO_UDP
        u.udp_len  = self.len
      end
      # build data:
      data = iphdr.to_s + self.to_s
      if (data.size % 2) != 0 then
        data += "\0"
      end
      # calculate sum:
      sum = 0
      check_sum_data = data.unpack("S>*")
      check_sum_data.each{ |x| sum += x }
      while (sum>>16 > 0)
        sum = (sum & 0xffff) + (sum >> 16);
      end
      self.checksum = ~sum & 0xffff
    end
end

class TcpHdr < BitStruct
    unsigned    :sport,     16, "Source Port"
    unsigned    :dport,     16, "Destination Port"
    unsigned    :seq,       32, "Sequence number"
    unsigned    :ack,       32, "Acknowledge number"
    unsigned    :offs,      4,  "Data offset"
    unsigned    :resv,      3,  "Reserved"
    unsigned    :flags,     9,  "Reserved"
    unsigned    :win,       16, "Window size"
    unsigned    :checksum,  16, "Checksum"
    unsigned    :urg,       16, "Urgent pointer"
    rest        :data,          "Data"

    def set_tcp_checksum(ip_src, ip_dst, len)
      self.checksum = 0x0000
      # build IPv4 pseudo-header:
      iphdr = IPv4PseudoHdr.new do |t|
        t.ip_src   = ip_src
        t.ip_dst   = ip_dst
        t.zeroes   = 0
        t.ip_proto = IP_PROTO_TCP
        t.udp_len  = len
      end
      # build data:
      data = iphdr.to_s + self.to_s
      if (data.size % 2) != 0 then
        data += "\0"
      end
      # calculate sum:
      sum = 0
      check_sum_data = data.unpack("S>*")
      check_sum_data.each{ |x| sum += x }
      while (sum>>16 > 0)
        sum = (sum & 0xffff) + (sum >> 16);
      end
      self.checksum = ~sum & 0xffff
    end
end

class DnsHdr < BitStruct
    unsigned    :id,         16, "Identification"
    unsigned    :qr,          1, "Query/Response"
    unsigned    :opcode,      4, "Opcode"
    unsigned    :aa,          1, "Authoritative Answer"
    unsigned    :tc,          1, "Truncated"
    unsigned    :rd,          1, "Recursion desired"
    unsigned    :ra,          1, "Recursion available"
    unsigned    :z,           1, "Z"
    unsigned    :ad,          1, "Authenticated Data"
    unsigned    :cd,          1, "Checkin Disabled"
    unsigned    :rcode,       4, "Return Code"
    unsigned    :tot_ques,   16, "Total Questions"
    unsigned    :tot_answer, 16, "Total Answers RRs"
    unsigned    :tot_author, 16, "Total Additional RRs"
    unsigned    :tot_addit,  16, "Total Additional RRs"
    rest        :data,           "Data"
end

class ArpHdr < BitStruct
    unsigned   :hw_type,        16, "Hardware type (HTYPE)"
    unsigned   :proto_type,     16, "Protocol type (PTYPE)"
    unsigned   :hw_addr_len,     8, "Hardware address length (HLEN)"
    unsigned   :proto_addr_len,  8, "Protocol address length (PLEN)"
    unsigned   :operation,      16, "Operation (OPER)"
    hex_octets :hw_src_addr,    48, "Sender hardware address (SHA)"
    octets     :proto_src_addr, 32, "Sender protocol address (SPA)"
    hex_octets :hw_dst_addr,    48, "Target hardware address (THA)"
    octets     :proto_dst_addr, 32, "Target protocol address (TPA)"
    rest       :data,               "Data"

    initial_value.hw_type        = 1
    initial_value.proto_type     = ET_IPv4
    initial_value.hw_addr_len    = 6
    initial_value.proto_addr_len = 4
    #initial_value.operation = 1
end

class Icmp < BitStruct
    unsigned :type, 8
    unsigned :code, 8
    unsigned :checksum, 16
    rest     :data
end

class IcmpEcho < BitStruct
    unsigned :type,      8
    unsigned :code,      8
    unsigned :checksum, 16
    unsigned :id,       16
    unsigned :seq,      16
    rest     :data
end

class IPv6 < BitStruct
    unsigned    :ip_v,       4,     "Version"
    unsigned    :ip_tc,      8,     "Traffic class"
    unsigned    :ip_fl,     20,     "Flow label"
    unsigned    :ip_len,    16,     "Length"
    unsigned    :ip_p,       8,     "Next header"
    unsigned    :ip_hop_lim, 8,     "Flags"
    octets      :ip_src,   128,     "Source address"
    octets      :ip_dst,   128,     "Destination address"
    rest        :data,              "Data"

    initial_value.ip_v       = 6
    initial_value.ip_tc      = 0
    initial_value.ip_fl      = 0
    initial_value.ip_hop_lim = 64
end

class Icmpv6 < BitStruct
    unsigned :type, 8
    unsigned :code, 8
    unsigned :checksum, 16
    rest     :data
end

class Llc < BitStruct
    unsigned    :dsap,                   8,     "Length/ethertype"
    unsigned    :ssap,                   8,     "Priority Code Point"
    unsigned    :control,                8,     "Drop Eligble Indicator"
    rest        :data,                          "Data"
end

class RstBpdu < BitStruct
    unsigned    :protocol_id,           16,     "Protocol ID"
    unsigned    :version_id,             8,     "Version ID"
    unsigned    :bpdu_type,              8,     "BPDU Type"
    unsigned    :flag_topo_chg_ack,      1,     "BPDU Flag: Topology Change Ack"
    unsigned    :flag_agreement,         1,     "BPDU Flag: Agreement"
    unsigned    :flag_forwarding,        1,     "BPDU Flag: Forwarding"
    unsigned    :flag_learning,          1,     "BPDU Flag: Learning"
    unsigned    :flag_port_role,         2,     "BPDU Flag: Port Role"
    unsigned    :flag_proposal,          1,     "BPDU Flag: Proposal"
    unsigned    :flag_topo_chg,          1,     "BPDU Flag: Topology Change"
    unsigned    :root_prio,             16,     "Root Identifier: Priority"
    hex_octets  :root_mac,              48,     "Root Identifier: MAC Address"
    unsigned    :root_path_cost,        32,     "Root Path Cost"
    unsigned    :reg_prio,              16,     "Bridge Identifier: Priority"
    hex_octets  :reg_mac,               48,     "Bridge Identifier: MAC Address"
    unsigned    :port_id,               16,     "Port Identifier"
    unsigned    :msg_age,               16,     "Message Age"   # number of 1/256 seconds
    unsigned    :max_age,               16,     "Max Age"       # number of 1/256 seconds
    unsigned    :hello_time,            16,     "Hello Time"    # number of 1/256 seconds
    unsigned    :forward_delay,         16,     "Forward Delay" # number of 1/256 seconds
    unsigned    :version1_length,        8,     "Version 1 length = 0"
    rest        :data,                          "Data"
end

class MstBpdu < BitStruct
    unsigned    :protocol_id,           16,     "Protocol ID"
    unsigned    :version_id,             8,     "Version ID"
    unsigned    :bpdu_type,              8,     "BPDU Type"
    unsigned    :flag_topo_chg_ack,      1,     "BPDU Flag: Topology Change Ack"
    unsigned    :flag_agreement,         1,     "BPDU Flag: Agreement"
    unsigned    :flag_forwarding,        1,     "BPDU Flag: Forwarding"
    unsigned    :flag_learning,          1,     "BPDU Flag: Learning"
    unsigned    :flag_port_role,         2,     "BPDU Flag: Port Role"
    unsigned    :flag_proposal,          1,     "BPDU Flag: Proposal"
    unsigned    :flag_topo_chg,          1,     "BPDU Flag: Topology Change"
    unsigned    :root_id_prio,          16,     "CIST Root Identifier: Priority"
    hex_octets  :root_id_mac,           48,     "CIST Root Identifier: MAC Address"
    unsigned    :ext_path_cost,         32,     "CIST External Path Cost"
    unsigned    :reg_id_prio,           16,     "CIST Regional Root Identifier: Priority"
    hex_octets  :reg_id_mac,            48,     "CIST Regional Root Identifier: MAC Address"
    unsigned    :port_id,               16,     "CIST Port Identifier"
    unsigned    :msg_age,               16,     "Message Age"   # number of 1/256 seconds
    unsigned    :max_age,               16,     "Max Age"       # number of 1/256 seconds
    unsigned    :hello_time,            16,     "Hello Time"    # number of 1/256 seconds
    unsigned    :forward_delay,         16,     "Forward Delay" # number of 1/256 seconds
    unsigned    :version1_length,        8,     "Version 1 length = 0"
    unsigned    :version3_length,       16,     "Version 3 length"
    unsigned    :conf_fselector,         8,     "MST Config ID: format selector"
    hex_octets  :conf_name,            256,     "MST Config ID: name"
    unsigned    :conf_revision,         16,     "MST Config ID: revision"
    hex_octets  :conf_digest,          128,     "MST Config ID: digest"
    unsigned    :int_path_cost,         32,     "CIST Internal Root Path Cost"
    unsigned    :bridge_id_prio,        16,     "CIST Bridge Identifier Priority"
    hex_octets  :bridge_id_mac,         48,     "CIST Bridge Identifier"
    unsigned    :rem_hobs,               8,     "CIST Remaining Hops"
    rest        :data,                          "Data"

    initial_value.protocol_id           = 0
    initial_value.version_id            = 3
    initial_value.bpdu_type             = 2
    initial_value.root_id_prio          = 32768
    initial_value.ext_path_cost         = 0
    initial_value.reg_id_prio           = 32768
    initial_value.msg_age               = 0
    initial_value.max_age               = 5120
    initial_value.hello_time            = 512
    initial_value.forward_delay         = 3840
    initial_value.version1_length       = 0
    initial_value.version3_length       = 64
    initial_value.conf_fselector        = 0
    initial_value.conf_revision         = 0
    initial_value.int_path_cost         = 0
    initial_value.bridge_id_prio        = 32768
    initial_value.rem_hobs              = 20
end


class LinuxSockaddrLL < BitStruct
    unsigned :family,   16, :endian => :native
    unsigned :protocol, 16, :endian => :big
    unsigned :ifindex,  32, :endian => :native
    unsigned :hatype,   16, :endian => :native
    unsigned :pkttype,   8
    unsigned :halen,     8
    char     :addr,     64
end

class LinuxIfConf < BitStruct
    signed    :buf_len, 32, :endian => :native
    pad       :padding, 32
    char      :buf_ptr, 64 # TODO, this will only work on 64 bit
end

class LinuxIfreqIndex < BitStruct
    char     :name,    128
    unsigned :ifindex,  32, :endian => :native
    pad      :padding,  96

    initial_value.ifindex = 0
end

class LinuxIfreqMacAddr < BitStruct
    char       :name,    128
    unsigned   :type,     16, :endian => :native
    hex_octets :addr,     48
    pad        :padding,  64
end

class LinuxIfreqIpv4Addr < BitStruct
    char       :name,    128
    unsigned   :type,     16, :endian => :native
    pad        :padding1, 16
    octets     :addr,     32
    pad        :padding2, 64
end

class LinuxIfreqFlags < BitStruct
    char       :name,            128
    unsigned   :flags,            16, :endian => :native
    pad        :padding,         112

    initial_value.flags = 0
end

class LinuxMReq < BitStruct
    signed   :ifindex, 32, :endian => :native
    unsigned :type,    16, :endian => :native
    unsigned :alen,    16, :endian => :native
    char     :address, 64
end

class PTP_Pdu_Timestamp < BitStruct
    unsigned    :secondsField,       48,    "secondsField"
    unsigned    :nanosecondsField,   32,    "nanosecondsField"
end

class PTP_Pdu_PortId < BitStruct
    unsigned    :clockId,       64,    "clockId"
    unsigned    :portNumber,    16,    "portNumber"
end

class Ptp_Pdu_Header < BitStruct
    unsigned    :transportSpecific,               4,    "transportSpecific"
    unsigned    :messageType,                     4,    "messageType"
    unsigned    :reserved,                        4,    "reserved"
    unsigned    :versionPTP,                      4,    "versionPTP"
    unsigned    :messageLength,                  16,    "messageLength"
    unsigned    :domainNumber,                    8,    "domainNumber"
    unsigned    :reserved1,                       8,    "reserved1"
    unsigned    :flagField,                      16,    "flagField"
    unsigned    :correctionField,                64,    "correctionField"
    unsigned    :reserved2,                      32,    "reserved2"
    nest        :sourcePortIdentity, PTP_Pdu_PortId,    "sourcePortIdentity"
    unsigned    :sequenceId,                     16,    "sequenceId"
    unsigned    :controlField,                    8,    "controlField"
    unsigned    :logMessageInterval,              8,    "logMessageInterval"
end

class FRAME_Sync_Pdu < BitStruct
    nest        :header,             Ptp_Pdu_Header,    "header"
    nest        :originTimestamp, PTP_Pdu_Timestamp,    "originTimestamp"
end

class FRAME_Request_Pdu < BitStruct
    nest        :header,             Ptp_Pdu_Header,    "header"
    nest        :originTimestamp, PTP_Pdu_Timestamp,    "originTimestamp"
end

class FRAME_Responce_Pdu < BitStruct
    nest        :header,                 Ptp_Pdu_Header, "header"
    nest        :receiveTimestamp,       PTP_Pdu_Timestamp, "receiveTimestamp"
    nest        :requestingPortIdentity, PTP_Pdu_PortId, "requestingPortIdentity"
end

class Test_Tlv < BitStruct
    unsigned    :type,            8,     "Type = 32"
    unsigned    :tlv_length,      16,    "Length"
    unsigned    :pattern_type,    8,     "Pattern type"
    hex_octets  :pattern,         7*8, "Pattern"
#    unsigned    :pattern,        32,    "Pattern"
    unsigned    :crc32,           32,    "CRC-32"
end

class Oam_Pdu_Common < BitStruct

    # IEEE 802.1ag E-OAM OpCodes
    OAM_OPCODE_CCM    = 1
    OAM_OPCODE_LBR    = 2
    OAM_OPCODE_LBM    = 3
    OAM_OPCODE_LTR    = 4
    OAM_OPCODE_LTM    = 5
    OAM_OPCODE_LCK    = 35
    OAM_OPCODE_TST    = 37
    OAM_OPCODE_LAPS   = 39
    OAM_OPCODE_RAPS   = 40
    OAM_OPCODE_LMR    = 42
    OAM_OPCODE_LMM    = 43
    OAM_OPCODE_1DM    = 45
    OAM_OPCODE_DMR    = 46
    OAM_OPCODE_DMM    = 47
    OAM_OPCODE_1SL    = 53
    OAM_OPCODE_SLR    = 54
    OAM_OPCODE_SLM    = 55
    OAM_OPCODE_LLR    = 56
    OAM_OPCODE_LLM    = 57
    OAM_OPCODE_UNEXP  = 60

    unsigned    :mdlevel,   3,  'MD Level'
    unsigned    :version,   5,  'Version'
    unsigned    :opcode,    8,  'OpCode'
    unsigned    :flags,     8,  'Flags'
    unsigned    :offset,    8,  'TLV Offset'
    rest        :data,          'Data'
end

class FRAME_CC_Pdu < BitStruct
    nest        :common, Oam_Pdu_Common,    "Common"
    unsigned    :sequence_number,    32,    "Sequence number"
    unsigned    :mep_id,             16,    "MEP ID"
    hex_octets  :meg_id,           48*8,    "MEG ID reserved"
    unsigned    :txfcf,              32,    "TxFCf"
    unsigned    :rxfcb,              32,    "RxFCb"
    unsigned    :txfcb,              32,    "TxFCb"
    unsigned    :reserved,           32,    "Reserved"
    unsigned    :end_tlv,             8,    "End TLV"
    unsigned    :tlv_length,         16,    "TLV length"
    unsigned    :tlv_value,           8,    "TLV value"
end

class FRAME_LAPS_Pdu < BitStruct
    nest        :common, Oam_Pdu_Common,    "Common"

    # Request codes
    REQUEST_NONE            = 0x00
    REQUEST_MANUEL_SWITCH   = 0x07

    unsigned    :req_sta,             4,    "Request/State"
    unsigned    :prot_type,           4,    "Prot. Type"
    unsigned    :request_sig,         8,    "Requested Signal"
    unsigned    :bridge_sig,          8,    "Bridged Signal"
    unsigned    :t,                   1,    "T"
    unsigned    :reserved,            7,    "Reserved"
    hex_octets  :padding,          60*8,    "Padding"
end

class FRAME_RAPS_Pdu < BitStruct
    nest        :common, Oam_Pdu_Common,    "Common"

    # Request codes
    REQUEST_NONE            = 0x00
    REQUEST_MANUEL_SWITCH   = 0x07

    unsigned    :req_sta,             4,    "Request/State"
    unsigned    :sub_code,            4,    "Sub-code"
    unsigned    :status,              8,    "Status"
    hex_octets  :node_id,           6*8,    "Node-ID"
    hex_octets  :reserved,         24*8,    "Reserved"
    hex_octets  :padding,          30*8,    "Padding"
end

class FRAME_LTM_Pdu < BitStruct
    nest        :common, Oam_Pdu_Common,    "Common"

    unsigned    :trans_id,           32,    "Transaction ID"
    unsigned    :ttl,                 8,    "TTL"
    hex_octets  :origin_mac,        6*8,    "OriginMAC"
    hex_octets  :target_mac,        6*8,    "TargetMAC"
    hex_octets  :padding,          60*8,    "Padding"
end

class FRAME_LTR_Pdu < BitStruct
    nest        :common, Oam_Pdu_Common,    "Common"

    unsigned    :trans_id,           32,    "Transaction ID"
    unsigned    :ttl,                 8,    "TTL"
    unsigned    :relay_action,        8,    "Relay Action"
    hex_octets  :padding,          60*8,    "Padding"
end

class FRAME_LB_Pdu < BitStruct
    nest        :common, Oam_Pdu_Common,    "Common"

    unsigned    :trans_id,            32,    "Transaction ID"
    hex_octets  :padding,             60*8,  "Padding"
end

class FRAME_LB_TEST_TLV_Pdu < BitStruct
    nest        :common, Oam_Pdu_Common,    "Common"

    unsigned    :trans_id,            32,   "Transaction ID"
    nest        :test_tlv, Test_Tlv,        "Test TLV"
    hex_octets  :padding,             60*8, "Padding"
end

class RawSocket < Socket
    PF_PACKET             = 17         # linux/socket.h
    AF_INET               =  2
    AF_INET6              = 10
    AF_PACKET             = 17         # linux/socket.h
    ETH_P_ALL             = 0x00_03    # linux/if_ether.h (but in network byte order)

    SIOCGIFNAME           = 0x89_10    # get name
    SIOCGIFCONF           = 0x89_12
    SIOCGIFFLAGS          = 0x89_13    # set flags
    SIOCSIFFLAGS          = 0x89_14    # get flags
    SIOCGIFHWADDR         = 0x89_27    # get hw address
    SIOCGIFINDEX          = 0x89_33    # get interface index
    SIOCDIFADDR           = 0x89_36    # delete interface address

    PACKET_ADD_MEMBERSHIP = 1          # linux/if_packet.h
    PACKET_MR_PROMISC     = 1          # linux/if_packet.h
    PACKET_OUTGOING       = 4          # linux/if_packet.h
    SOL_PACKET            = 263        # linux/socket.h

    IFF_UP                =    0x1 # interface is up
    IFF_BROADCAST         =    0x2 # broadcast address valid
    IFF_DEBUG             =    0x4 # turn on debugging
    IFF_LOOPBACK          =    0x8 # is a loopback net
    IFF_POINTOPOINT       =   0x10 # interface is has p-p link
    IFF_NOTRAILERS        =   0x20 # avoid use of trailers
    IFF_RUNNING           =   0x40 # interface RFC2863 OPER_UP
    IFF_NOARP             =   0x80 # no ARP protocol
    IFF_PROMISC           =  0x100 # receive all packets
    IFF_ALLMULTI          =  0x200 # receive all multicast packets
    IFF_MASTER            =  0x400 # master of a load balancer
    IFF_SLAVE             =  0x800 # slave of a load balancer
    IFF_MULTICAST         = 0x1000 # Supports multicast
    IFF_PORTSEL           = 0x2000 # can set media type
    IFF_AUTOMEDIA         = 0x4000 # auto media select active
    IFF_DYNAMIC           = 0x8000 # dialup device with changing addresses

    attr_reader :name
    alias :super_recv :recv
    alias :super_send :send

    def initialize(ifname)
        @subscribers    = []
        @cached_ifindex = nil
        @name           = ifname
        @cached_mac     = nil

        super PF_PACKET, Socket::SOCK_RAW, ETH_P_ALL
        `sudo ethtool -K #{ifname} rxvlan off`
        `sudo ethtool -K #{ifname} txvlan off`
        `/sbin/ip link set up dev #{ifname}`

        # bind socket to a given interface
        sll = LinuxSockaddrLL.new do |s|
            s.family   = AF_PACKET
            s.protocol = ETH_P_ALL
            s.ifindex  = ifindex
        end
        bind sll

        @saved_flags = self.flags

        # set interface in promiscuous mode
        mreq = LinuxMReq.new do |s|
            s.ifindex = ifindex
            s.type = PACKET_MR_PROMISC
            s.alen = 0
            s.address = 0
        end
        setsockopt(SOL_PACKET, PACKET_ADD_MEMBERSHIP, mreq) 

        # set various flags on interface
       self.flags=([:IF_FLAG_UP, :IF_FLAG_NOARP, :IF_FLAG_PROMISC])
    end

    def ifindex(poll = false)
        if poll || !@cached_ifindex
            ifr = LinuxIfreqIndex.new
            ifr.name = @name
            ioctl(SIOCGIFINDEX, ifr)
            @cached_ifindex = ifr.ifindex
        end
        @cached_ifindex
    end

    def mac(poll = false)
        if poll || !@cached_mac
            ifr = LinuxIfreqMacAddr.new
            ifr.name = @name
            ioctl(SIOCGIFHWADDR, ifr)
            @cached_mac = ifr.addr
        end
        @cached_mac
    end

    def flags
        ifr = LinuxIfreqFlags.new
        ifr.name = @name
        ifr.flags = 0
        ioctl(SIOCGIFFLAGS, ifr)
        f = ifr.flags

        flags = []
        flags << :IF_FLAG_UP          if f & IFF_UP          != 0
        flags << :IF_FLAG_BROADCAST   if f & IFF_BROADCAST   != 0
        flags << :IF_FLAG_DEBUG       if f & IFF_DEBUG       != 0
        flags << :IF_FLAG_LOOPBACK    if f & IFF_LOOPBACK    != 0
        flags << :IF_FLAG_POINTOPOINT if f & IFF_POINTOPOINT != 0
        flags << :IF_FLAG_NOTRAILERS  if f & IFF_NOTRAILERS  != 0
        flags << :IF_FLAG_RUNNING     if f & IFF_RUNNING     != 0
        flags << :IF_FLAG_NOARP       if f & IFF_NOARP       != 0
        flags << :IF_FLAG_PROMISC     if f & IFF_PROMISC     != 0
        flags << :IF_FLAG_ALLMULTI    if f & IFF_ALLMULTI    != 0
        flags << :IF_FLAG_MASTER      if f & IFF_MASTER      != 0
        flags << :IF_FLAG_SLAVE       if f & IFF_SLAVE       != 0
        flags << :IF_FLAG_MULTICAST   if f & IFF_MULTICAST   != 0
        flags << :IF_FLAG_PORTSEL     if f & IFF_PORTSEL     != 0
        flags << :IF_FLAG_AUTOMEDIA   if f & IFF_AUTOMEDIA   != 0
        flags << :IF_FLAG_DYNAMIC     if f & IFF_DYNAMIC     != 0

        return flags
    end

    def flags= flags
        flags_val = flags.inject(0) do |acc, f|
            val = case f
                when :IF_FLAG_UP          then IFF_UP
                when :IF_FLAG_BROADCAST   then IFF_BROADCAST
                when :IF_FLAG_DEBUG       then IFF_DEBUG
                when :IF_FLAG_LOOPBACK    then IFF_LOOPBACK
                when :IF_FLAG_POINTOPOINT then IFF_POINTOPOINT
                when :IF_FLAG_NOTRAILERS  then IFF_NOTRAILERS
                when :IF_FLAG_RUNNING     then IFF_RUNNING
                when :IF_FLAG_NOARP       then IFF_NOARP
                when :IF_FLAG_PROMISC     then IFF_PROMISC
                when :IF_FLAG_ALLMULTI    then IFF_ALLMULTI
                when :IF_FLAG_MASTER      then IFF_MASTER
                when :IF_FLAG_SLAVE       then IFF_SLAVE
                when :IF_FLAG_MULTICAST   then IFF_MULTICAST
                when :IF_FLAG_PORTSEL     then IFF_PORTSEL
                when :IF_FLAG_AUTOMEDIA   then IFF_AUTOMEDIA
                when :IF_FLAG_DYNAMIC     then IFF_DYNAMIC
                else 0
            end
            acc | val
        end

        ifr = LinuxIfreqFlags.new
        ifr.name = @name
        ifr.flags = flags_val
        ioctl(SIOCSIFFLAGS, ifr)
    end

    def restore_saved_flags
        self.flags = @saved_flags
    end

    def clear_addr
        # warning hack hack hack, do not expect this to work on
        # anything else than 64 bit linux 2.6+ with 64bit ruby
        buf_len = 65536
        buf = " " * buf_len 
        ifr = LinuxIfConf.new
        ifr.buf_len = buf_len
        ifr.buf_ptr = [ buf ].pack("p")
        ioctl(SIOCGIFCONF, ifr)

        #buf.hexdump
        i = 0
        while i < ifr.buf_len
            rec = buf[i..i+39]
            #STDOUT.puts ">#{rec.unpack("C*")}<"
            ip = LinuxIfreqIpv4Addr.new rec
            if ip.type == AF_INET && ip.name.strip == @name
                %x(ip addr del #{ip.addr} dev #{@name})
            end

            i += 40
        end
    end

    def add_subscriber(s)
        @subscribers << s
    end

    def recv_raw
        # Packets transmitted from the host will also be "received" here, so we need to look at the ("C" API) addrinfo.sll_pkttype field
        # and discard packets that are outgoing
        p = nil
        loop do
            p, addr_info = recvfrom 10240
            sa = LinuxSockaddrLL.new(addr_info.to_sockaddr)
            break if sa.pkttype != PACKET_OUTGOING
        end
        #STDOUT.puts "#{Time.now.to_f}.#{self.object_id}.#{Thread.current.object_id} Recv raw frame on #{name}"
        #STDOUT.puts p.hexdump
        @subscribers.each do |s| s.recv_frame(p, []) end
        p
    end

    def send(payload)
        #STDOUT.puts "Send raw frame on #{name}"
        #STDOUT.puts payload.hexdump
        super_send(payload, 0)
    end
end

class HostInterface
    attr_accessor :sock
    attr_accessor :tx_counter

    def initialize(ifname, options={})
        @sock = RawSocket.new(ifname)
        @rx_counter  = 0
        @rx_filtered = 0
        @tx_counter  = 0
        @mutex       = Mutex.new
        @rx_buffer   = []    # Array means do buffer; nil means do not buffer
        @rx_filters  = []

        @rx_thr = Thread.new do
            filters = nil
            while true
                begin
                    frame = @sock.recv_raw
                    @mutex.synchronize do
                        filters = @rx_filters
                    end
                    case filters.length
                    when 0
                        # do nothing
                    when 1
                        frame = filters[0].call(frame)  # RX filter may alter or kill (nil) frame
                    else
                        keep = filters.inject(false) { |k, flt|
                            res = flt.call(frame)
                            (res != nil) || k           # Keep frame if just one filter wants to
                        }
                    end
                    @mutex.synchronize do
                        if frame
                            if @rx_buffer
                                raise "You should empty the RX buffer on occasion. You have a bug!" if @rx_buffer.length > 100
                                @rx_buffer << frame
                            end
                            @rx_counter += 1
                        else
                            @rx_filtered += 1
                        end
                    end
                rescue => msg
                    Log.warn("HostInterface: Caught: #{msg.to_s}")
                    Log.backtrace(msg)
                end
            end
        end # of thread

        self
    end

    def tx(frame, count = 1)
        1.upto(count) do |i|
            if block_given?
                frame = yield frame
            end
            @sock.send(frame)
            @mutex.synchronize do
                @tx_counter += 1
            end
        end
        self
    end

    def rx_counters_clear
        @mutex.synchronize do
            @rx_counter  = 0
            @rx_filtered = 0
        end
        self
    end

    def rx_counter
        @mutex.synchronize do
            return @rx_counter
        end
    end

    # Increments by one if any filter returns nil. So packets are only counted once, no matter
    # how many filters reject them
    def rx_filtered
        @mutex.synchronize do
            return @rx_filtered
        end
    end

    def rx_buffer=(val)
        @mutex.synchronize do
            @rx_buffer = val ? (val.kind_of?(Array) ? val : []) : nil
        end
    end

    # Note: Hands over buffer, i.e. clears internal state
    def rx_buffer
        v = nil
        @mutex.synchronize do
            v = @rx_buffer
            @rx_buffer = [] if @rx_buffer
        end
        v
    end

    # Wait until either rx_counter == n_packets or timeout
    def rx_waitfor(n_packets, timeout_seconds = 1.0)
      t0 = Time.now.to_f
      while true
        rxc = rx_counter
        return rxc if rxc >= n_packets
        return nil if (Time.now.to_f - t0) >= timeout_seconds
        sleep(1.0/25)
      end
    end

    # Frame RX filtering:
    #
    # flt: Proc that takes a BitStruct and where the exit value is either a
    # BitStruct (usually the same as the input) or nil if the frame is killed
    # by filtering.
    #
    # OBSERVE: Filters are called one-by-one in the order they're appended,
    #          each filter receiving the original frame.
    #
    #          Also note that when more than one filter is installed, buffering
    #          happens on the original frame, not the output from the filter.
    #
    # The reasoning behind this scheme is that various receivers may have different
    # needs, so the filters can't make up a pipeline.

    # Set one specific filter
    def rx_filter=(flt)
        @mutex.synchronize do
            @rx_filters = (flt == nil) ? [] : [flt]
        end
    end

    # Append one filter
    def append_rx_filter(flt)
        @mutex.synchronize do
            raise "Rx filter already added" if @rx_filters.include?(flt)
            @rx_filters << flt
        end
    end

    # Remove one filter
    def remove_rx_filter(flt)
        @mutex.synchronize do
            raise "No such RX filter" unless @rx_filters.delete(flt)
        end
    end

    def ifname
        @sock.name
    end

    def ifindex
        @sock.ifindex
    end

    def mac
        @sock.mac
    end

    def close
        return if @sock == nil
        @rx_thr.kill
        @rx_thr.join
        @sock.restore_saved_flags
        @sock = nil
    end
end

# This is a simple factory for creating and destroying Linux bridge interfaces.
# These are mainly interesting when trying to loop traffic or when sniffing it;
# as such there is no explicit topology support for them; each script has to
# build the bridge(s) as it sees fit.

class LinuxBridgeIfFactory
    @@created = []

    def LinuxBridgeIfFactory.capable?
        File.exist?(BRCTL) && File.executable?(BRCTL)
    end

    def LinuxBridgeIfFactory.exists?(ifname)
        out = run("show #{ifname}").grep(Regexp.new(ifname))
        return !(out[0] =~ /No such device/)
    end

    def LinuxBridgeIfFactory.create(ifname, slaves)
        return if exists?(ifname)
        run("addbr #{ifname}")
        @@created << ifname
        slaves.each { |s| run("addif #{ifname} #{s}") }
        `sudo ifconfig #{ifname} up`
    end

    def LinuxBridgeIfFactory.destroy(ifname)
        return unless exists?(ifname)
        `sudo ifconfig #{ifname} down`
        run("delbr #{ifname}")
        @@created.delete(ifname)
    end

    def LinuxBridgeIfFactory.destroy_created
        all = @@created.clone
        all.each { |ifname| destroy(ifname) }
    end

    def LinuxBridgeIfFactory.destroy_all
        out = run("show")[1..-1].map { |line| line.split(/\s+/)[0] }
        out.each { |ifname| destroy(ifname) }
    end

private

    BRCTL = '/sbin/brctl'

    def LinuxBridgeIfFactory.run(cmd)
        raise "#{BRCTL} not installed, can't work with Linux bridges" unless capable?
        out = `sudo #{BRCTL} #{cmd} 2>&1`
        exit_code = $?
        raise "#{BRCTL} #{cmd} failed: #{exit_code}" if exit_code != 0
        return out.split(/\n/)
    end
end

at_exit do
    begin
        LinuxBridgeIfFactory.destroy_created
    rescue
        # Ignore any warnings
    end
end

#---------- Frame testing -----------------------------------------------------

class FrameProps
    attr_accessor :dmac
    attr_accessor :smac
    attr_accessor :ot
    attr_accessor :it
    attr_accessor :etype
    attr_accessor :llc
    attr_accessor :arp
    attr_accessor :ipv4
    attr_accessor :ipv6
    attr_accessor :udp
    attr_accessor :tcp
    attr_accessor :data_offs
    attr_accessor :tx_info
    attr_accessor :data     #Expected format is a binary sequence. 

    def initialize(tx_info = false)
        @dmac = "ff:ff:ff:ff:ff:ff"
        @smac = "00:00:00:00:00:0a"
        @ot = VlanTag.new({ tpid: 0, vid: 0, pcp: 0, dei: 0 })
        @it = VlanTag.new({ tpid: 0, vid: 0, pcp: 0, dei: 0 })
        @etype = 0xaaaa
        @llc = Llc.new({ dsap: 1, ssap: 2, control: 3 })
        @arp = ArpHdr.new
        @ipv4 = IPv4.new({ ip_ttl: 64, ip_proto: 17 })
        @ipv6 = IPv6.new({ ip_p: 17 })
        @udp = UdpHdr.new({ sport: 1, dport: 2 })
        @tcp = TcpHdr.new({ sport: 1, dport: 2 })
        @data_offs = 0
        @tx_info = (tx_info ? get_req("mesa_packet_tx_info_init") : nil)
        @data = [0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xcd,0xae,0xaf,
                 0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,
                 0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,
                 0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf].pack("c*")    #This generates a binary sequence, that is the data format
    end

    def dup
        f = FrameProps.new
        f.dmac = @dmac
        f.smac = @smac
        f.ot = @ot.dup
        f.it = @it.dup
        f.etype = @etype
        f.llc = @llc
        f.arp = @arp
        f.ipv4 = @ipv4.dup
        f.ipv6 = @ipv6.dup
        f.udp = @udp.dup
        f.tcp = @tcp.dup
        f.data = data
        f.tx_info = @tx_info
        f.data_offs = data_offs
        f
    end

    def create_frame
        f = Frame.new
        if (@tx_info.nil?)
            f.dmac = @dmac
            f.smac = @smac
        else
            # Add MAC header and IFH
            mac_len = ifh_len_get(1)
            ifh_len = ifh_len_get(2)
            ifh = get_req("mesa_packet_tx_hdr_encode", @tx_info, 32)
            if (mac_len > 0)
                f.dmac = "ff:ff:ff:ff:ff:ff"
                f.smac = "fe:ff:ff:ff:ff:ff"
                f << EtherType.new({etype: 0x8880})
                f << EtherType.new({etype: cap_get("PACKET_IFH_EPID")})
                for i in 0..(ifh_len - 1)
                    f << ifh[i]
                end
                f << [@dmac.split(":").join("")].pack('H*')
            else
                # Luton26, no MAC header, 8 bytes IFH
                dmac = ""
                smac = ""
                for i in 0..7
                    str = (format("%02x", ifh[i]) + (i == 5 ? "" : ":"))
                    if (i < 6)
                        dmac += str
                    else
                        smac += str
                    end
                end
                f.dmac = dmac
                dmac = @dmac.split(":")
                smac += dmac[0..3].join(":")
                f.smac = smac
                f << [dmac[4..5].join("")].pack('H*')
            end
            f << [@smac.split(":").join("")].pack('H*')
            if (@tx_info["switch_frm"] && (@tx_info["masquerade_port"] == "MESA_PORT_NO_NONE")) # Only insert the VLAN tag when frame is not injected masqueraded
                tag = @tx_info["tag"]
                f << VlanTag.new({ tpid: 0x8100, vid: tag["vid"], pcp: tag["pcp"], dei: (tag["dei"] ? 1 : 0) })
            end
        end
        if (@ot.tpid != 0)
            f << ot
            if (@it.tpid != 0)
                f << it
            end
        end

        # EtherType zero indicates LLC encapsulation
        data_len = @data.length
        f << EtherType.new({etype: (@etype < 2 ? (data_len + 3) : @etype) })

        case @etype
        when ET_LLC
            f << @llc
        when ET_SNAP
            @llc.dsap = 0xaa
            @llc.ssap = 0xaa
            @llc.control = 0x03
            f << @llc
        when ET_ARP
            f << @arp
        when ET_IPv4
            len = data_len
            proto = @ipv4.ip_proto
            if (proto == IP_PROTO_UDP)
                len += 8
            end
            if (proto == IP_PROTO_TCP)
                len += 20
            end
            @ipv4.ip_len = (@ipv4.ip_hl * 4 + len)
            @ipv4.set_ip_checksum
            f << @ipv4
            if (proto == IP_PROTO_UDP)
                @udp.len = len
                @udp.set_udp_checksum(@ipv4.ip_src, @ipv4.ip_dst)
                f << @udp
            end
            if (proto == IP_PROTO_TCP)
                @tcp.set_tcp_checksum(@ipv4.ip_src, @ipv4.ip_dst, len)
                f << @tcp
            end
        when ET_IPv6
            len = data_len
            proto = @ipv6.ip_p
            if (proto == IP_PROTO_UDP)
                len += 8
            end
            if (proto == IP_PROTO_TCP)
                len += 20
            end
            @ipv6.ip_len = len
            f << @ipv6
            if (proto == IP_PROTO_UDP)
                # UDP checksum not supported currently
                @udp.len = len
                f << @udp
            end
            if (proto == IP_PROTO_TCP)
                # TCP checksum not supported currently
                f << @tcp
            end
        else
        end
        f << @data
        # Padding
        while (f.data.size < 48)
            f << [0].pack("c*")
        end
        f
    end
end

class FrameExp
    attr_accessor :idx_rx      # Host Interface index for Rx (switch Tx)
    attr_accessor :frame_table # Frame table

    def initialize(idx_rx)
        @idx_rx = idx_rx
        @frame_table = []
    end
end

$dut.hp_list.each do |hp|
    Log.info "Create host interface and rx_filter on #{hp}"
    if_rx = HostInterface.new(hp)
    if_rx.rx_filter = Proc.new do |frame|
        frame
    end
    if_rx.rx_buffer = true
    dummy = if_rx.rx_buffer
    $dut.if_list << if_rx
end

def frame_log(error, txt, idx, f, cnt = 32)
    ifx = $dut.if_list[idx]
    if_name = format("%-10s", ifx.ifname)
    len_str = format("%4u", 12 + f.data.size)
    Log.msg("#{txt} #{len_str} bytes frame on #{if_name}, DMAC: #{f.dmac}, SMAC: #{f.smac}, Data: #{f.data.unpack('H*')[0][0..(cnt * 2 - 1)]}", error)
end

# Create and Tx frame
def frame_tx(frame, idx_tx, cnt = 32)
    tx_f = frame.create_frame
    if_tx = $dut.if_list[idx_tx]
    frame_log(false, "Tx", idx_tx, tx_f, cnt)
    if_tx.tx(tx_f)
    sleep(0.1)
end

def frame_forward(rx_frame, idx_tx, cnt = 32)
    if_tx = $dut.if_list[idx_tx]
    frame_log(false, "Tx", idx_tx, rx_frame.frame, cnt)
    if_tx.tx(rx_frame.frame)
    sleep(0.1)
end

# Class for holding frame with optional IFH information
class FrameRx
    attr_accessor :frame
    attr_accessor :info

    def initialize
        @frame = nil
        @info = nil
    end
end

# Rx one frame, optionally extract IFH information
def frame_rx(idx_rx, extract = false, cnt = 32)
    if_rx = $dut.if_list[idx_rx]
    rx_buf = if_rx.rx_buffer[0]
    rx_f = FrameRx.new
    if (rx_buf.nil?)
        Log.info("No frame on #{if_rx.ifname}")
    else
        offset = 0
        if (extract)
            mac_len = ifh_len_get(1)
            ifh_len = ifh_len_get(2)
            offset = (mac_len + ifh_len)
            ifh = rx_buf[(mac_len..(offset - 1))].unpack('C*')
            for i in ifh_len..39
                ifh << 0
            end
            meta = {
                no_wait: false,
                chip_no: 0,
                xtr_qu: 0,
                etype: 0,
                fcs: 0,
                sw_tstamp: { hw_cnt: 0 },
                length: 0
            }
            rx_f.info = get_req("mesa_packet_rx_hdr_decode", meta, ifh)
        end
        f = Frame.new(rx_buf[offset..-1])
        frame_log(false, "Rx", idx_rx, f, cnt)
        rx_f.frame = f
    end
    rx_f
end

# Send one frame to a port and test reception on a list of ports
def frame_test(frame, idx_tx, exp, cnt = 32)
    # Create and Tx frame
    frame_tx(frame, idx_tx, cnt)
    
    # Check frame
    exp.each do |e|
        if_rx = $dut.if_list[e.idx_rx]
        if_rx.rx_buffer.each do |rx_buf|
            error = true
            e.frame_table.each do |f|
                fr = f.create_frame
                rx_f = Frame.new(rx_buf[f.data_offs..-1])
                if (rx_f.dmac == fr.dmac and rx_f.smac == fr.smac && rx_f.data == fr.data)
                    # Expected frame, remove it from frame table
                    e.frame_table -= [f]
                    error = false
                    break
                end
            end
            frame_log(error, "Rx", e.idx_rx, Frame.new(rx_buf), cnt)
        end

        # All frames in the table must be received
        e.frame_table.each do |f|
            frame_log(true, "No", e.idx_rx, f.create_frame, cnt)
        end
    end
end

# Send one frame to a port and expect the same frame on a list of ports
def frame_test_if_list(frame, idx_tx, idx_list, cnt = 32)
    exp = []
    $dut.if_list.each_index do |idx_rx|
        e = FrameExp.new(idx_rx)
        if (idx_list.include?(idx_rx))
            e.frame_table << frame
        end
        exp << e
    end
    frame_test(frame, idx_tx, exp, cnt)
end

# Send frame on one port and check counters on another port
def frame_test_counters(frame, idx_tx, idx_rx, cnt_tx = 1000000, cnt_rx = cnt_tx, prio = 0)
    tx_frame = frame.create_frame
    if_tx = $dut.if_list[idx_tx]      # Host Tx
    if_rx = $dut.if_list[idx_rx]      # Host Rx
    port_rx = $dut.port_list[idx_tx]  # Switch Rx
    port_tx = $dut.port_list[idx_rx]  # Switch Tx
    if_tx.tx_counter = 0
    if_rx.rx_buffer = false
    if_rx.rx_counters_clear
    obj = MesaJson.new("port_counters")
    rx_cnt = obj.get(port_rx)["prio"][prio]["rx"]
    tx_cnt = obj.get(port_tx)["prio"][prio]["tx"]

    # Send frames
    Log.info("Sending #{cnt_tx} frames on #{if_tx.ifname}")
    for i in 1..cnt_tx do
        if ((i % 100000) == 0)
            Log.info("Sent #{i} frames")
        end
        if_tx.tx(tx_frame)
    end
    sleep(1)

    # Check counters
    Log.info("Checking counters")
    rx_cnt = (obj.get(port_rx)["prio"][prio]["rx"] - rx_cnt)
    tx_cnt = (obj.get(port_tx)["prio"][prio]["tx"] - tx_cnt)
    Log.info("Tx frames: #{if_tx.tx_counter} on #{if_tx.ifname}")
    Log.info("Rx frames: #{rx_cnt} on port #{port_rx}, priority #{prio}")
    Log.info("Tx frames: #{tx_cnt} on port #{port_tx}, priority #{prio}")
    rx_cnt = if_rx.rx_counter
    Log.info("Rx frames: #{rx_cnt} on #{if_rx.ifname}")
    if (rx_cnt != cnt_rx)
        # Host counters are not fully reliable, so a warning is given
        Log.warning("Rx expected #{cnt_rx} frames, got #{rx_cnt} frames on #{if_rx.ifname}")
    end
    Log.msg("Tx expected #{cnt_rx} frames, got #{tx_cnt} frames on port #{port_tx}, priority #{prio}", tx_cnt != cnt_rx)
end

#---------- Self testing ------------------------------------------------------

def frame_example
    idx_host = 1
    idx_npi = 3

    # IGMP registration
    queue = 7
    obj = MesaJson.new("packet_rx_conf")
    conf = obj.get
    conf["queue"][queue]["npi"]["enable"] = true
    conf["reg"]["igmp_cpu_only"] = true
    conf["map"]["igmp_queue"] = queue
    obj.set(conf)

    # NPI port
    obj = MesaJson.new("npi_conf")
    conf = obj.get
    conf["enable"] = true
    conf["port_no"] = $dut.port_list[idx_npi]
    obj.set(conf)

    # IGMP redirect
    Log.info("Frame extraction (IGMP)")
    tx_f = FrameProps.new
    tx_f.dmac = "01:00:5e:01:02:03"
    tx_f.etype = ET_IPv4
    tx_f.ipv4.ip_dst = "225.1.2.3"
    tx_f.ipv4.ip_proto = IP_PROTO_IGMP
    frame_tx(tx_f, idx_host)
    rx_f = frame_rx(idx_npi, true)
    # rx_f.frame now holds the frame without IFH
    Log.info("info : #{rx_f.info}")

    # Frame injection
    Log.info("Frame injection")
    tx_f = FrameProps.new(1)
    tx_f.tx_info["dst_port_mask"] = (1 << $dut.port_list[idx_host])
    frame_tx(tx_f, idx_npi)
    rx_f = frame_rx(idx_host)
end

def self.__test_frameio
    h = HostInterface.new("eth1")
    h2 = HostInterface.new("eth2")

    f = Frame.new
    f.dmac = h2.mac
    f.smac = h.mac
    f.payload = "00000000"

    h2.rx_counters_clear
    h2.rx_buffer = true
    h2.rx_filter = Proc.new do |frm|
        puts "Filter invoked"
        in_f = Frame.new(frm)
        in_f.dmac == h2.mac ? frm : nil
    end

    1.upto(5) do |i|
        h.tx(f)
        sleep(i == 5 ? 1 : 0)
        puts "h  tx: #{h.tx_counter} rx: #{h.rx_counter} rx_filtered: #{h.rx_filtered}, rx buffer: #{h.rx_buffer.length}"
        puts "h2 tx: #{h2.tx_counter} rx: #{h2.rx_counter} rx_filtered: #{h2.rx_filtered}, rx buffer: #{h2.rx_buffer.length}"
        puts
    end
    puts "Done"
end
