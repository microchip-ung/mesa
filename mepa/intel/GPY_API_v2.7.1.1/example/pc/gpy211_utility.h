/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

#ifndef _SWITCH_UTILITY_H_
#define _SWITCH_UTILITY_H_

/* Config Options */
#define GPHY_ADDR          	0x0F
#define SMDIO_ADDR          0x1F
#define MAX_BUSY_RETRY		100
#define RETURN_FROM_FUNC	1
//Delete later
#define GPY211_PC_TEST		1
#define F24S_READ_REGS      1
#define P31G_READ_REGS      1
//#define DEBUG_P31G_UART     1

#if (defined(GPY211_PC_TEST) && GPY211_PC_TEST)
#define UART_INTERFACE         1
#define uC8051_BP 0		//Bypass uC8051
#define uC8051_NBP 1	//No bypass uC8051
#endif /* GPY211_PC_TEST */

#define TOOL_VERSION		"0.0.2" //"0.0.1" - Initial version
//"0.0.2" - WoL update & new SENSOR API add
#define SYS_BUFFER_SIZE		100
#define SERIAL_BUFFER_SIZE	256
#define TEMP_BUFFRE_SIZE	16
#define CMD_LINE_BUFFER_SIZE	1000
#define MAX_PARAM		200
#define ULONG_MAX_X    4294967295UL

#ifdef SWITCH_SERVER
#define PRINTM(ft,...)	do { fprintf(ft,__VA_ARGS__);} while (0)
#else
#define PRINTM(ft,...)	do { printf(__VA_ARGS__);} while (0)
#endif

/*variable to store uart handle*/
//extern HANDLE hComm;

/*variable to enable/disable debug prints*/
extern unsigned char debugenable;

/* MDIO Bus read/write function implemented per board */
extern int gpy211_mdio_read(void *busdata, u16 phyaddr, u32 regnum);
extern int gpy211_mdio_write(void *busdata, u16 phyaddr, u32 regnum, u16 data);
extern int mac_sec_main(int argc, char *argv[]);

#endif /* _SWITCH_UTILITY_H_ */
