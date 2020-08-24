sudo insmod Kernel/linux-4.19.49/drivers/phy/lantiq/gpy211/gpy211.ko
JuneLog06^
sudo insmod Kernel/linux-4.19.49/drivers/net/macsec.ko


gmudepa@linux:~$ ip link help macsec
Usage: ... macsec [ [ address <lladdr> ] port { 1..2^16-1 } | sci <u64> ]
                  [ cipher { default | gcm-aes-128 } ]
                  [ icvlen { 8..16 } ]
                  [ encrypt { on | off } ]
                  [ send_sci { on | off } ]
                  [ end_station { on | off } ]
                  [ scb { on | off } ]
                  [ protect { on | off } ]
                  [ replay { on | off} window { 0..2^32-1 } ]
                  [ validate { strict | check | disabled } ]
                  [ encodingsa { 0..3 } ]

gmudepa@linux:~$ ip link add link DEVICE name NAME type macsec adress ......

gmudepa@linux:~$ ip macsec help
Usage: ip macsec add DEV tx sa { 0..3 } [ OPTS ] key ID KEY
       ip macsec set DEV tx sa { 0..3 } [ OPTS ]
       ip macsec del DEV tx sa { 0..3 }
       ip macsec add DEV rx SCI [ on | off ]
       ip macsec set DEV rx SCI [ on | off ]
       ip macsec del DEV rx SCI
       ip macsec add DEV rx SCI sa { 0..3 } [ OPTS ] key ID KEY
       ip macsec set DEV rx SCI sa { 0..3 } [ OPTS ]
       ip macsec del DEV rx SCI sa { 0..3 }
       ip macsec show
       ip macsec show DEV
where  OPTS := [ pn <u32> ] [ on | off ]
       ID   := 128-bit hex string
       KEY  := 128-bit hex string
       SCI  := { sci <u64> | port { 1..2^16-1 } address <lladdr> }

-------------------------------------------------------------------------------

sudo ifconfig eth0 0.0.0.0

sudo ip link add link eth0 name msec_if type macsec address 00:90:fb:66:02:06 port 1 cipher gcm-aes-128 icvlen 8 encrypt off send_sci on end_station off scb off protect off replay off window 5 validate strict encodingsa 0

sudo ip macsec add msec_if rx address 00:90:fb:66:02:06 port 1 on

sudo ip macsec add msec_if rx address 00:90:fb:66:02:06 port 1 sa 0 pn 1 on key 02 AD7A2BD03EAC835A6F620FDCB506B345

sudo ip macsec add msec_if tx sa 0 pn 1 on key 01 AD7A2BD03EAC835A6F620FDCB506B345

-------------------------------------------------------------------------------

sudo ifconfig eth0 0.0.0.0

sudo ip link add link eth0 name msec_if type macsec sci 12153524C0895E81 cipher gcm-aes-128 icvlen 8 encrypt off send_sci on end_station off scb off protect off replay off window 5 validate strict encodingsa 2

sudo ip macsec add msec_if rx sci 12153524C0895E81 on

sudo ip macsec add msec_if rx sci 12153524C0895E81 sa 2 pn 0xB2C28464 on key 02 AD7A2BD03EAC835A6F620FDCB506B345

sudo ip macsec add msec_if tx sa 2 pn 0xB2C28464 on key 01 AD7A2BD03EAC835A6F620FDCB506B345

-------------------------------------------------------------------------------
sudo ip link set dev msec_if up

sudo ifconfig msec_if 192.168.2.2

sudo ip -s macsec show

-------------------------------------------------------------------------------

gmudepa@linux:~$ ip -s macsec show
4: msec_if: protect on validate strict sc off sa off encrypt on send_sci on end_station off scb off replay off
    cipher suite: GCM-AES-128, using ICV length 16
    TXSC: f01faf38e0d30001 on SA 0
    stats: OutPktsUntagged InPktsUntagged OutPktsTooLong InPktsNoTag InPktsBadTag InPktsUnknownSCI InPktsNoSCI InPktsOverrun
                         0              0              0          10            0                0           0             0
    stats: OutPktsProtected OutPktsEncrypted OutOctetsProtected OutOctetsEncrypted
                         94              164              16532              30932
        0: PN 358, state on, key 01000000000000000000000000000000
           OutPktsProtected OutPktsEncrypted
                         94              164
    RXSC: 0020da8623780001, state on
    stats: InOctetsValidated InOctetsDecrypted InPktsUnchecked InPktsDelayed InPktsOK InPktsInvalid InPktsLate InPktsNotValid InPktsNotUsingSA InPktsUnusedSA
                        1076              3618               0            43        0             0          0              0                0              0
        0: PN 200, state on, key 02000000000000000000000000000000
           InPktsOK InPktsInvalid InPktsNotValid InPktsNotUsingSA InPktsUnusedSA
                  0             0              0                0              0

-------------------------------------------------------------------------------

gmudepa@linux:~$ ip link help
Usage: ip link add [link DEV] [ name ] NAME
                   [ txqueuelen PACKETS ]
                   [ address LLADDR ]
                   [ broadcast LLADDR ]
                   [ mtu MTU ] [index IDX ]
                   [ numtxqueues QUEUE_COUNT ]
                   [ numrxqueues QUEUE_COUNT ]
                   type TYPE [ ARGS ]

       ip link delete { DEVICE | dev DEVICE | group DEVGROUP } type TYPE [ ARGS ]

       ip link set { DEVICE | dev DEVICE | group DEVGROUP }
	                  [ { up | down } ]
	                  [ type TYPE ARGS ]
	                  [ arp { on | off } ]
	                  [ dynamic { on | off } ]
	                  [ multicast { on | off } ]
	                  [ allmulticast { on | off } ]
	                  [ promisc { on | off } ]
	                  [ trailers { on | off } ]
	                  [ carrier { on | off } ]
	                  [ txqueuelen PACKETS ]
	                  [ name NEWNAME ]
	                  [ address LLADDR ]
	                  [ broadcast LLADDR ]
	                  [ mtu MTU ]
	                  [ netns { PID | NAME } ]
	                  [ link-netnsid ID ]
			  [ alias NAME ]
	                  [ vf NUM [ mac LLADDR ]
				   [ vlan VLANID [ qos VLAN-QOS ] [ proto VLAN-PROTO ] ]
				   [ rate TXRATE ]
				   [ max_tx_rate TXRATE ]
				   [ min_tx_rate TXRATE ]
				   [ spoofchk { on | off} ]
				   [ query_rss { on | off} ]
				   [ state { auto | enable | disable} ] ]
				   [ trust { on | off} ] ]
				   [ node_guid { eui64 } ]
				   [ port_guid { eui64 } ]
			  [ xdp { off |
				  object FILE [ section NAME ] [ verbose ] |
				  pinned FILE } ]
			  [ master DEVICE ][ vrf NAME ]
			  [ nomaster ]
			  [ addrgenmode { eui64 | none | stable_secret | random } ]
	                  [ protodown { on | off } ]

       ip link show [ DEVICE | group GROUP ] [up] [master DEV] [vrf NAME] [type TYPE]

       ip link xstats type TYPE [ ARGS ]

       ip link afstats [ dev DEVICE ]

       ip link help [ TYPE ]

TYPE := { vlan | veth | vcan | vxcan | dummy | ifb | macvlan | macvtap |
          bridge | bond | team | ipoib | ip6tnl | ipip | sit | vxlan |
          gre | gretap | erspan | ip6gre | ip6gretap | ip6erspan |
          vti | nlmon | team_slave | bond_slave | ipvlan | geneve |
          bridge_slave | vrf | macsec }
