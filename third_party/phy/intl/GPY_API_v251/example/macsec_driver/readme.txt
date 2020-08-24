Project
===============================================================================
The GPY212 is a Gigabit Ethernet (GbE) Ethernet Network Connection device
with one Ethernet PHY, supporting speeds of 10, 100, 1000 and 2500 Mbps.
It also supports a four-speed (10/100/1000/2500 Mbps) SGMII interface for
connecting with an external chip.

Starting
===============================================================================
This will give you the sequence of steps for integrating and developing MACSec
driver for Intel's GPY212 PHY.

Prerequisites
===============================================================================
This sample MACSec driver was developed & testing without ACTUAL target preset.
It was tested on a linux PC with Ubuntu OS 18.04 LTS installed.

Integrating
===============================================================================
1.Download kernel source code version 4.49.49.
2.Apply the patch or modify/create/add files as from the diff file
  'kernel_patch.diff' located at GPY211\src\api\macsec\linux.
3.Make all and install the kernel.
4.Load the gpy211.ko and macsec.ko modules.
5.Install iproute2 package and call MACSec commands and check the debug prints.

	sudo ifconfig eth0 0.0.0.0
	sudo ip link add link eth0 name msec_if type macsec sci 12153524C0895E81 cipher gcm-aes-128 icvlen 8 encrypt off send_sci on end_station off scb off protect off replay off window 5 validate strict encodingsa 2
	sudo ip macsec add msec_if rx sci 12153524C0895E81 on
	sudo ip macsec add msec_if rx sci 12153524C0895E81 sa 2 pn 0xB2C28464 on key 02 AD7A2BD03EAC835A6F620FDCB506B345
	sudo ip macsec add msec_if tx sa 2 pn 0xB2C28464 on key 01 AD7A2BD03EAC835A6F620FDCB506B345

Authors
===============================================================================
Govindaiah Mudepalli

License
===============================================================================
This project is licensed under the BSD-3-Clause OR GPL-2.0-only - see the file for details.