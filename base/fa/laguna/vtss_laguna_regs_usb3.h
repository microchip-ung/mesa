// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_USB3_H_
#define _VTSS_LAGUNA_REGS_USB3_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a USB3
 *
 * DWC USB3 Memory Map
 *
 ***********************************************************************/

/**
 * Register Group: \a USB3:DWC_USB3_BLOCK_GBL
 *
 * USB 3.0 Global Register Block
 */


/**
 * \brief Global SoC Bus Configuration Register 0

This register configures system bus DMA options for the master bus, which may be configured as AHB, AXI, or Native. Options include burst length and cache type (bufferable/posted, cacheable/snoop, and so on). The application can program this register upon power-on, or a change in mode of operation after the DMA engine is halted.

xHCI Register Power-On Value:

If you are using a standard xHCI host driver, make sure to set the register's power-on value during coreConsultant configuration (DWC_USB3_GSBUSCFG0_INIT parameter) because the standard xHCI driver does not access this register.

For more details on this register, refer to the following sections:
 - "Usage of Global SoC Bus Configuration Register 0 (GSBUSCFG0)" section in the Programming Guide
 - "System Bus Interface" section in the Databook
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GSBUSCFG0
 */
#define VTSS_USB3_GSBUSCFG0                  VTSS_IOREG(VTSS_TO_USB3,0x3040)

/**
 * \brief
 * Undefined Length INCR Burst Type Enable (INCRBrstEna)
 *
 * Input to BUS-GM; This bit determines the set of burst lengths the master
 * interface uses. It works in conjunction with the GSBUSCFG0[7:1] enables
 * (INCR256/128/64/32/16/8/4).
 *
 * 0: INCRX burst mode
 *
 * HBURST (for AHB configurations) and ARLEN/AWLEN (for AXI configurations)
 * do not use INCR except in case of non-aligned burst transfers. In the
 * case of address-aligned transfers, they use only the following burst
 * lengths:
 *  - 1
 *  - 2, 4 (if GSBUSCFG0.INCR4BrstEna = 1)
 *  - 8 (if GSBUSCFG0.INCR8BrstEna = 1)
 *  - 16 (if GSBUSCFG0.INCR16BrstEna = 1)
 *  - 32 (if GSBUSCFG0.INCR32BrstEna = 1)
 *  - 64 (if GSBUSCFG0.INCR64BrstEna = 1)
 *  - 128 (if GSBUSCFG0.INCR128BrstEna = 1)
 *  - 256 (if GSBUSCFG0.INCR256BrstEna = 1)
 * Note:
 *  - In case of non-address-aligned transfers, INCR may get generated at
 * the beginning and end of the transfers to align the address boundaries,
 * even though INCR is disabled.
 *  - In AHB mode, if INCRX burst mode is enabled, but none of the
 * supported INCRx bursts bits are enabled, then the controller will
 * perform (undefined length) INCR bursts.
 * 1: INCR (undefined length) burst mode
 *  - AHB configurations: HBURST uses SINGLE or INCR of any length with
 * handling 1KB boundary breakup.
 *  - AXI configurations: ARLEN/AWLEN uses any length less than or equal to
 * the largest-enabled burst length of INCR32/64/128/256.
 * For cache line-aligned applications, this bit is typically set to 0 to
 * ensure that the master interface uses only power-of-2 burst lengths (as
 * enabled via GSBUSCFG0[7:0]).
 *
 * \details
 * Field: ::VTSS_USB3_GSBUSCFG0 . INCRBRSTENA
 */
#define  VTSS_F_USB3_GSBUSCFG0_INCRBRSTENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_USB3_GSBUSCFG0_INCRBRSTENA    VTSS_BIT(0)
#define  VTSS_X_USB3_GSBUSCFG0_INCRBRSTENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * INCR4 Burst Type Enable
 *
 * Input to BUS-GM; For the AXI configuration, when this bit is enabled the
 * controller is allowed to do bursts of beat length 1, 2, and 4. It is
 * highly recommended that this bit is enabled to prevent descriptor reads
 * and writes from being broken up into separate transfers.
 *
 * \details
 * Field: ::VTSS_USB3_GSBUSCFG0 . INCR4BRSTENA
 */
#define  VTSS_F_USB3_GSBUSCFG0_INCR4BRSTENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_USB3_GSBUSCFG0_INCR4BRSTENA   VTSS_BIT(1)
#define  VTSS_X_USB3_GSBUSCFG0_INCR4BRSTENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * INCR8 Burst Type Enable
 *
 * Input to BUS-GM; For the AHB/AXI configuration, if software set this bit
 * to "1", the AHB/AXI master uses INCR to do the 8-beat burst.
 *
 * \details
 * Field: ::VTSS_USB3_GSBUSCFG0 . INCR8BRSTENA
 */
#define  VTSS_F_USB3_GSBUSCFG0_INCR8BRSTENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_USB3_GSBUSCFG0_INCR8BRSTENA   VTSS_BIT(2)
#define  VTSS_X_USB3_GSBUSCFG0_INCR8BRSTENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * INCR16 Burst Type Enable
 *
 * Input to BUS-GM. For the AHB/AXI configuration, if software set this bit
 * to '1', the AHB/AXI master uses INCR to do the 16-beat burst.
 *
 * \details
 * Field: ::VTSS_USB3_GSBUSCFG0 . INCR16BRSTENA
 */
#define  VTSS_F_USB3_GSBUSCFG0_INCR16BRSTENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_USB3_GSBUSCFG0_INCR16BRSTENA  VTSS_BIT(3)
#define  VTSS_X_USB3_GSBUSCFG0_INCR16BRSTENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * INCR32 Burst Type Enable
 *
 * Input to BUS-GM;
 * For the AHB/AXI configuration, if software set this bit to 1, the
 * AHB/AXI master uses INCR to do the 32-beat burst.
 *
 * \details
 * Field: ::VTSS_USB3_GSBUSCFG0 . INCR32BRSTENA
 */
#define  VTSS_F_USB3_GSBUSCFG0_INCR32BRSTENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_USB3_GSBUSCFG0_INCR32BRSTENA  VTSS_BIT(4)
#define  VTSS_X_USB3_GSBUSCFG0_INCR32BRSTENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * INCR64 Burst Type Enable
 *  - Input to BUS-GM;
 * For the AHB/AXI configuration, if software set this bit to 1, the
 * AHB/AXI master uses INCR to do the 64-beat burst.
 *
 * \details
 * Field: ::VTSS_USB3_GSBUSCFG0 . INCR64BRSTENA
 */
#define  VTSS_F_USB3_GSBUSCFG0_INCR64BRSTENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_USB3_GSBUSCFG0_INCR64BRSTENA  VTSS_BIT(5)
#define  VTSS_X_USB3_GSBUSCFG0_INCR64BRSTENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * INCR128 Burst Type Enable
 *
 * Input to BUS-GM;
 *
 * For the AHB/AXI configuration, if software set this bit to 1, the
 * AHB/AXI master uses INCR to do the 128-beat burst.
 *
 * \details
 * Field: ::VTSS_USB3_GSBUSCFG0 . INCR128BRSTENA
 */
#define  VTSS_F_USB3_GSBUSCFG0_INCR128BRSTENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_USB3_GSBUSCFG0_INCR128BRSTENA  VTSS_BIT(6)
#define  VTSS_X_USB3_GSBUSCFG0_INCR128BRSTENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * INCR256 Burst Type Enable
 *
 * Input to BUS-GM.
 *
 * For the AHB/AXI configuration, if software set this bit to 1, the
 * AHB/AXI master uses INCR to do the 256-beat burst.
 *
 * \details
 * Field: ::VTSS_USB3_GSBUSCFG0 . INCR256BRSTENA
 */
#define  VTSS_F_USB3_GSBUSCFG0_INCR256BRSTENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_USB3_GSBUSCFG0_INCR256BRSTENA  VTSS_BIT(7)
#define  VTSS_X_USB3_GSBUSCFG0_INCR256BRSTENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GSBUSCFG0 . RESERVED_9_8
 */
#define  VTSS_F_USB3_GSBUSCFG0_RESERVED_9_8(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_USB3_GSBUSCFG0_RESERVED_9_8     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_USB3_GSBUSCFG0_RESERVED_9_8(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * Descriptor Access is Big Endian
 *
 * This bit controls the endian mode for descriptor accesses.
 *  - Little-endian (default)
 *  - Big-endian
 * In big-endian mode, DMA access (both read and write) for descriptors
 * uses a Byte Invariant Big-Endian mode (see "Little-Endian and
 * Big-Endian" section	in the User Guide.
 *
 * Data is considered as 'embedded data' in the descriptors in the
 * following cases:
 *  - Device mode: The buffer pointer of a Setup TRB points to the Setup
 * TRB itself.
 *  - Host mode: The Immediate Data (IDT) bit in a Transfer TRB is set to
 * 1.
 * In device mode, if the system uses different endian modes for descriptor
 * and data, software must not use 'embedded' data.
 *
 * In host mode, if the system uses different endian modes for data and
 * descriptors, the controller treats 'embedded data' as descriptor (not as
 * data) in terms of endian mode handling. If this is not the expectation
 * of the system, the software must manipulate the 'embedded data'
 * accordingly.
 *
 * Note: Since AXI requires byte invariant endianness, setting DescBigend
 * and DatBigEnd to one causes an address invariant transform to be
 * applied, which is not appropriate. See section 9.3 and 9.4 of the AMBA
 * AXI Specification. Hence for an AXI master (DWC_USB3_MBUS_TYPE=1), this
 * bit must be set to zero.
 *
 * \details
 * Field: ::VTSS_USB3_GSBUSCFG0 . DESBIGEND
 */
#define  VTSS_F_USB3_GSBUSCFG0_DESBIGEND(x)   VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_USB3_GSBUSCFG0_DESBIGEND      VTSS_BIT(10)
#define  VTSS_X_USB3_GSBUSCFG0_DESBIGEND(x)   VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Data Access is Big Endian
 *
 *  This bit controls the endian mode for data accesses.
 *  - Little-endian (default);
 *  - Big-endian;
 * In big-endian mode, DMA access (both read and write) for packet data a
 * Byte Invariant Big-Endian mode (see "Little-Endian and Big-Endian"
 * section  in the User Guide).
 *
 * Note: Since AXI requires byte invariant endianness, setting DescBigend
 * and DatBigEnd to one causes an address invariant transform to be
 * applied, which is not appropriate. See section 9.3 and 9.4 of the AMBA
 * AXI Specification. Hence for an AXI master (DWC_USB3_MBUS_TYPE=1), this
 * bit must be set to zero.
 *
 * \details
 * Field: ::VTSS_USB3_GSBUSCFG0 . DATBIGEND
 */
#define  VTSS_F_USB3_GSBUSCFG0_DATBIGEND(x)   VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_USB3_GSBUSCFG0_DATBIGEND      VTSS_BIT(11)
#define  VTSS_X_USB3_GSBUSCFG0_DATBIGEND(x)   VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Reserved for future use
 *
 * \details
 * Field: ::VTSS_USB3_GSBUSCFG0 . RESERVED_15_12
 */
#define  VTSS_F_USB3_GSBUSCFG0_RESERVED_15_12(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_USB3_GSBUSCFG0_RESERVED_15_12     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_USB3_GSBUSCFG0_RESERVED_15_12(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * DESWRREQINFO
 *
 * AHB-prot/AXI-cache/OCP-ReqInfo for Descriptor Write (DesWrReqInfo)
 *
 * Input to BUS-GM.
 *
 * \details
 * Field: ::VTSS_USB3_GSBUSCFG0 . DESWRREQINFO
 */
#define  VTSS_F_USB3_GSBUSCFG0_DESWRREQINFO(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_USB3_GSBUSCFG0_DESWRREQINFO     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_USB3_GSBUSCFG0_DESWRREQINFO(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * DATWRREQINFO
 *
 * AHB-prot/AXI-cache/OCP-ReqInfo for Data Write (DatWrReqInfo).
 *
 * Input to BUS-GM.
 *
 * \details
 * Field: ::VTSS_USB3_GSBUSCFG0 . DATWRREQINFO
 */
#define  VTSS_F_USB3_GSBUSCFG0_DATWRREQINFO(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_USB3_GSBUSCFG0_DATWRREQINFO     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_USB3_GSBUSCFG0_DATWRREQINFO(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * DESRDREQINFO
 *
 * AHB-prot/AXI-cache/OCP-ReqInfo for Descriptor Read (DesRdReqInfo).
 *
 * Input to BUS-GM.
 *
 * \details
 * Field: ::VTSS_USB3_GSBUSCFG0 . DESRDREQINFO
 */
#define  VTSS_F_USB3_GSBUSCFG0_DESRDREQINFO(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_USB3_GSBUSCFG0_DESRDREQINFO     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_USB3_GSBUSCFG0_DESRDREQINFO(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * DATRDREQINFO
 *
 * AHB-prot/AXI-cache/OCP-ReqInfo for Data Read (DatRdReqInfo)
 *
 * Input to BUS-GM.
 *
 * \details
 * Field: ::VTSS_USB3_GSBUSCFG0 . DATRDREQINFO
 */
#define  VTSS_F_USB3_GSBUSCFG0_DATRDREQINFO(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_USB3_GSBUSCFG0_DATRDREQINFO     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_USB3_GSBUSCFG0_DATRDREQINFO(x)  VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief Global SoC Bus Configuration Register 1

xHCI Register Power-On Value:

If you are using a standard xHCI host driver, make sure to set the register's power-on value during coreConsultant configuration (DWC_USB3_GSBUSCFG1_INIT parameter) because the standard xHCI driver does not access this register.

For more details on this register, refer to "System Bus Interface" section in the Databook.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GSBUSCFG1
 */
#define VTSS_USB3_GSBUSCFG1                  VTSS_IOREG(VTSS_TO_USB3,0x3041)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GSBUSCFG1 . RESERVED_7_0
 */
#define  VTSS_F_USB3_GSBUSCFG1_RESERVED_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_USB3_GSBUSCFG1_RESERVED_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_USB3_GSBUSCFG1_RESERVED_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * AXI Pipelined Transfers Burst Request Limit
 *
 * The field controls the number of outstanding pipelined transfer requests
 * the AXI master pushes to the AXI slave.
 *
 * When the AXI master reaches this limit, it does not make any more
 * requests on the AXI ARADDR and AWADDR buses until the associated data
 * phases complete.
 *
 * This field is encoded as follows:
 *  - 'h0: 1 request
 *  - 'h1: 2 requests
 *  - 'h2: 3 requests
 *  - 'h3: 4 requests
 *  -  ...
 *  - 'hF: 16 requests
 *
 * \details
 * Field: ::VTSS_USB3_GSBUSCFG1 . PIPETRANSLIMIT
 */
#define  VTSS_F_USB3_GSBUSCFG1_PIPETRANSLIMIT(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_USB3_GSBUSCFG1_PIPETRANSLIMIT     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_USB3_GSBUSCFG1_PIPETRANSLIMIT(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * 1k Page Boundary Enable
 *
 * By default (this bit is disabled) the AXI breaks transfers at the 4k
 * page boundary. When this bit is enabled, the AXI master (DMA data)
 * breaks transfers at the 1k page boundary.
 *
 * \details
 * Field: ::VTSS_USB3_GSBUSCFG1 . EN1KPAGE
 */
#define  VTSS_F_USB3_GSBUSCFG1_EN1KPAGE(x)    VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_USB3_GSBUSCFG1_EN1KPAGE       VTSS_BIT(12)
#define  VTSS_X_USB3_GSBUSCFG1_EN1KPAGE(x)    VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GSBUSCFG1 . GSBUSCFG1_RESERVED_31_13
 */
#define  VTSS_F_USB3_GSBUSCFG1_GSBUSCFG1_RESERVED_31_13(x)  VTSS_ENCODE_BITFIELD(x,13,19)
#define  VTSS_M_USB3_GSBUSCFG1_GSBUSCFG1_RESERVED_31_13     VTSS_ENCODE_BITMASK(13,19)
#define  VTSS_X_USB3_GSBUSCFG1_GSBUSCFG1_RESERVED_31_13(x)  VTSS_EXTRACT_BITFIELD(x,13,19)


/**
 * \brief Global Tx Threshold Control Register

For more information on
 - Using this register, refer to "Packet Threshold and Burst Features for High Latency Systems" section in the Databook.
 - Selecting values for the fields of this register, see the "TX/RX Data FIFO Sizes and TX/RX Threshold Control Register Settings" section in the User Guide.
Note:
 - GTXTHRCFG register is not applicable for Debug Target.
 - GTXTHRCFG register is not applicable in USB 2.0-only mode.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GTXTHRCFG
 */
#define VTSS_USB3_GTXTHRCFG                  VTSS_IOREG(VTSS_TO_USB3,0x3042)

/**
 * \brief
 * Reserved for future use
 *
 * \details
 * Field: ::VTSS_USB3_GTXTHRCFG . RESERVED_10_0
 */
#define  VTSS_F_USB3_GTXTHRCFG_RESERVED_10_0(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_USB3_GTXTHRCFG_RESERVED_10_0     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_USB3_GTXTHRCFG_RESERVED_10_0(x)  VTSS_EXTRACT_BITFIELD(x,0,11)

/**
 * \brief
 * Reserved (Rsvd/Rs)
 *
 * The register field must write only 0 by the application. The read value
 * must be treated as X (unknown).
 *
 * \details
 * Field: ::VTSS_USB3_GTXTHRCFG . RESERVED_13_11
 */
#define  VTSS_F_USB3_GTXTHRCFG_RESERVED_13_11(x)  VTSS_ENCODE_BITFIELD(x,11,3)
#define  VTSS_M_USB3_GTXTHRCFG_RESERVED_13_11     VTSS_ENCODE_BITMASK(11,3)
#define  VTSS_X_USB3_GTXTHRCFG_RESERVED_13_11(x)  VTSS_EXTRACT_BITFIELD(x,11,3)

/**
 * \brief
 * Reserved1(Rsvd/Rs)
 *
 * Register field must write only 0 by the application. The read value must
 * be treated as X (unknown).
 *
 * \details
 * Field: ::VTSS_USB3_GTXTHRCFG . GTXTHRCFG_RESERVED_14
 */
#define  VTSS_F_USB3_GTXTHRCFG_GTXTHRCFG_RESERVED_14(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_USB3_GTXTHRCFG_GTXTHRCFG_RESERVED_14  VTSS_BIT(14)
#define  VTSS_X_USB3_GTXTHRCFG_GTXTHRCFG_RESERVED_14(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Reserved_15
 *
 * \details
 * Field: ::VTSS_USB3_GTXTHRCFG . GTXTHRCFG_RESERVED_15
 */
#define  VTSS_F_USB3_GTXTHRCFG_GTXTHRCFG_RESERVED_15(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_USB3_GTXTHRCFG_GTXTHRCFG_RESERVED_15  VTSS_BIT(15)
#define  VTSS_X_USB3_GTXTHRCFG_GTXTHRCFG_RESERVED_15(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * USB Maximum TX Burst Size
 *
 *  When UsbTxPktCntSel is one, this field specifies the Maximum Bulk OUT
 * burst the controller can do. When the system bus is slower than the USB,
 * TX FIFO can underrun during a long burst. User can program a smaller
 * value to this field to limit the TX burst size that the controller can
 * do.
 *
 *  Host mode: It only applies to SS Bulk, Isochronous, and Interrupt OUT
 * endpoints.
 *
 *  Device mode: This value is not used in device mode, but users need to
 * program a value when using the TX threshold feature to make sure that
 * the value programmed in UsbTxPktCnt is less than this value.
 *
 * Valid values are from 1 to 16.
 *
 * \details
 * Field: ::VTSS_USB3_GTXTHRCFG . USBMAXTXBURSTSIZE
 */
#define  VTSS_F_USB3_GTXTHRCFG_USBMAXTXBURSTSIZE(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_USB3_GTXTHRCFG_USBMAXTXBURSTSIZE     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_USB3_GTXTHRCFG_USBMAXTXBURSTSIZE(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * USB Transmit Packet Count
 *
 * This field specifies the number of packets that must be in the TXFIFO
 * before the controller can start transmission for the corresponding USB
 * transaction (burst). This field is only valid when the USB Transmit
 * Packet Count Enable field is set to one. Valid values are from 1 to 15.
 *
 * Note:
 *  - In device mode, if device controller does not have the TRBs for the
 * number of packets or if it cannot fetch the TRBs because of high latency
 * or switching between other endpoints, then it does not wait for the
 * threshold number of packets. The threshold number of packets will be
 * honored only when the TRBs are available in the controller for the
 * number of packets before it starts the data fetch.
 *  -  This field must be less than or equal to the USB Maximum TX Burst
 * Size field.
 *
 * \details
 * Field: ::VTSS_USB3_GTXTHRCFG . USBTXPKTCNT
 */
#define  VTSS_F_USB3_GTXTHRCFG_USBTXPKTCNT(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_USB3_GTXTHRCFG_USBTXPKTCNT     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_USB3_GTXTHRCFG_USBTXPKTCNT(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GTXTHRCFG . GTXTHRCFG_RESERVED_28
 */
#define  VTSS_F_USB3_GTXTHRCFG_GTXTHRCFG_RESERVED_28(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_USB3_GTXTHRCFG_GTXTHRCFG_RESERVED_28  VTSS_BIT(28)
#define  VTSS_X_USB3_GTXTHRCFG_GTXTHRCFG_RESERVED_28(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * USB Transmit Packet Count Enable
 *
 * This field enables/disables the USB transmission multi-packet
 * thresholding:
 *  - 0: USB transmission multi-packet thresholding is disabled; the
 * controller can start transmission on the USB after the entire (one full)
 * packet has been fetched into the corresponding TXFIFO.
 *  - 1: USB transmission multi-packet thresholding is enabled. The
 * controller can only start transmission on the USB after USB Transmit
 * Packet Count amount of packets for the USB transaction (burst) are
 * already in the corresponding TXFIFO. This mode is valid in both host and
 * device modes. It is only used for SuperSpeed operation.
 *
 * \details
 * Field: ::VTSS_USB3_GTXTHRCFG . USBTXPKTCNTSEL
 */
#define  VTSS_F_USB3_GTXTHRCFG_USBTXPKTCNTSEL(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_USB3_GTXTHRCFG_USBTXPKTCNTSEL  VTSS_BIT(29)
#define  VTSS_X_USB3_GTXTHRCFG_USBTXPKTCNTSEL(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GTXTHRCFG . RESERVED_30
 */
#define  VTSS_F_USB3_GTXTHRCFG_RESERVED_30(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_USB3_GTXTHRCFG_RESERVED_30    VTSS_BIT(30)
#define  VTSS_X_USB3_GTXTHRCFG_RESERVED_30(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GTXTHRCFG . RESERVED_31
 */
#define  VTSS_F_USB3_GTXTHRCFG_RESERVED_31(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_USB3_GTXTHRCFG_RESERVED_31    VTSS_BIT(31)
#define  VTSS_X_USB3_GTXTHRCFG_RESERVED_31(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief Global Rx Threshold Control Register

In a normal case, a Tx burst starts as soon as one packet is prefetched; an Rx burst starts as soon as 1-packet space is available. This works well as long as the system bus is faster than the USB 3.0 bus (a 1024-bytes packet takes ~2.2 microseconds on the USB bus in SS mode).

If the system bus latency is larger than 2.2 microseconds to access a 1024-byte packet, then starting a burst on 1-packet condition leads to an early abort of the burst causing unnecessary performance reduction.

To avoid underrun and overrun during the burst, in a high-latency bus system (like USB), threshold and burst size control is provided through GTXTHRCFG and GRXTHRCFG registers. Bit [29] of the GTXTHRCFG and GRXTHRCFG registers enables this feature.

For more information on
 - Using this register, refer to "Packet Threshold and Burst Features for High Latency Systems" section in the Databook.
 - Selecting values for the fields of this register, see the "TX/RX Data FIFO Sizes and TX/RX Threshold Control Register Settings" section in the User Guide.
Note:
 - GRXTHRCFG register is not applicable for Debug Target.
 - There is an issue when ACK TP with NumP=0 followed by ACK TP with NumP=1 without ERDY TP sent by the device controller during a burst bulk OUT transfer. This may cause third-party USB 3.0 host controllers to keep waiting for the ERDY TP.
The USB 3.0 specification states that "When an endpoint is not in a flow control condition, it shall not send an ERDY TP unless the endpoint is a Bulk endpoint that supports streams." In this case, after the device sent the ACK TP (nump=1), the endpoint was not in the flow control, so it did not send an ERDY.
The device would have sent ERDY if the next OUT packet was not received. When the next OUT packet was received, at that time there was enough buffer space to accept it, so the device accepted the packet by informing host that it is not no longer in the flow control. The Host should wait for the responses for all the OUT packets to return and then decide if the endpoint is still in flow control or not.
The USB 3.1 specification supersedes all the USB 3.0 specification. The errata states that "If the host continues, or resumes, transactions to an endpoint, the endpoint shall re-evaluate its flow control state and respond appropriately." However, there are no ECNs on the USB 3.0 for this issue.
To work around this issue, the Global Rx Threshold mode must be disable by setting GRXTHRCFG.UsbRxPktCntSel=0. Instead, software can program the DCFG.NUMP mode (where fixed NUMP is transmitted always) instead of the RX threshold based nump mode to prevent the device from sending ACK TP with NumP=0. The NUMP in the ACK TP is the minimum value of (DCFG.NUMP, bMaxBurstSize) for each endpoint.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GRXTHRCFG
 */
#define VTSS_USB3_GRXTHRCFG                  VTSS_IOREG(VTSS_TO_USB3,0x3043)

/**
 * \brief
 * Space reserved in Rx FIFO for ISOC OUT
 *
 * In host mode, this field is not applicable and must be programmed to 0.
 *
 * In device mode, this value represents the amount of space to be reserved
 * for ISOC OUT packets.
 *
 * The value to be programmed should be chosen so as to ensure that non
 * ISOC packets are not completely dropped.
 *
 * If no space needs to be reserved for ISOC OUT packets, program this
 * field to 0.
 *
 * This field is valid only in device mode. The maximum configurable depth
 * of RX FIFO is 8192. Therefore, this field is 13 bits wide.
 *
 * The value of space reserved is in terms of DWC_USB3_MDWIDTH.
 *
 * For SS, the space reservation is always rounded off to the nearest
 * packet boundary. Therefore, it is always recommended to program a value
 * corresponding to MPS or its multiples.
 *
 * For HS/FS, the space reservation is the actual value.
 *
 * Note: For SS, reserve space for ISOC when the Rx FIFO space can
 * accommodate two MPS or more. Otherwise, this may result in degraded
 * performance for non-ISOC packets. If the space is entirely allocated for
 * ISOC, the non-ISOC packets will be completely dropped. To help you
 * decide during the time of configuring the controller, refer to the
 * "Device-Mode Receive Path" section in the Databook.
 *
 * \details
 * Field: ::VTSS_USB3_GRXTHRCFG . RESVISOCOUTSPC
 */
#define  VTSS_F_USB3_GRXTHRCFG_RESVISOCOUTSPC(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_USB3_GRXTHRCFG_RESVISOCOUTSPC     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_USB3_GRXTHRCFG_RESVISOCOUTSPC(x)  VTSS_EXTRACT_BITFIELD(x,0,13)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GRXTHRCFG . GRXTHRCFG_RESERVED_14_13
 */
#define  VTSS_F_USB3_GRXTHRCFG_GRXTHRCFG_RESERVED_14_13(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_USB3_GRXTHRCFG_GRXTHRCFG_RESERVED_14_13     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_USB3_GRXTHRCFG_GRXTHRCFG_RESERVED_14_13(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GRXTHRCFG . GRXTHRCFG_RESERVED_15
 */
#define  VTSS_F_USB3_GRXTHRCFG_GRXTHRCFG_RESERVED_15(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_USB3_GRXTHRCFG_GRXTHRCFG_RESERVED_15  VTSS_BIT(15)
#define  VTSS_X_USB3_GRXTHRCFG_GRXTHRCFG_RESERVED_15(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GRXTHRCFG . RESERVED_18_16
 */
#define  VTSS_F_USB3_GRXTHRCFG_RESERVED_18_16(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_USB3_GRXTHRCFG_RESERVED_18_16     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_USB3_GRXTHRCFG_RESERVED_18_16(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * USB Maximum Receive Burst Size
 *
 * In host mode, this field specifies the Maximum Bulk IN burst the
 * DWC_usb3 controller can perform.
 *
 * When the system bus is slower than the USB, RX FIFO can overrun during a
 * long burst.
 *
 * You can program a smaller value to this field to limit the RX burst size
 * that the controller can perform. It only applies to SS Bulk,
 * Isochronous, and Interrupt IN endpoints in the host mode.
 *
 * In device mode, this field specifies the NUMP value that is sent in ERDY
 * for an OUT endpoint. The programmed value should not exceed the RXFIFO
 * size.
 *
 * This field is valid only when UsbRxPktCntSel is one. The valid values
 * for this field are from 1 to 16.
 *
 * \details
 * Field: ::VTSS_USB3_GRXTHRCFG . USBMAXRXBURSTSIZE
 */
#define  VTSS_F_USB3_GRXTHRCFG_USBMAXRXBURSTSIZE(x)  VTSS_ENCODE_BITFIELD(x,19,5)
#define  VTSS_M_USB3_GRXTHRCFG_USBMAXRXBURSTSIZE     VTSS_ENCODE_BITMASK(19,5)
#define  VTSS_X_USB3_GRXTHRCFG_USBMAXRXBURSTSIZE(x)  VTSS_EXTRACT_BITFIELD(x,19,5)

/**
 * \brief
 * USB Receive Packet Count
 *
 * In host mode, this field specifies the space (in terms of the number of
 * packets) that must be available in the RX FIFO before the controller can
 * start the corresponding USB RX transaction (burst).
 *
 * In device mode, this field specifies the space (in terms of the number
 * of packets) that must be available in the RX FIFO before the controller
 * can send ERDY for a flow-controlled endpoint.
 *
 * This field is valid only when the USB Receive Packet Count Enable field
 * is set to 1. The valid values for this field are from 1 to 15.
 *
 * Note: This field must be less than or equal to the USB Maximum Receive
 * Burst Size field.
 *
 * \details
 * Field: ::VTSS_USB3_GRXTHRCFG . USBRXPKTCNT
 */
#define  VTSS_F_USB3_GRXTHRCFG_USBRXPKTCNT(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_USB3_GRXTHRCFG_USBRXPKTCNT     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_USB3_GRXTHRCFG_USBRXPKTCNT(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GRXTHRCFG . GRXTHRCFG_RESERVED_28
 */
#define  VTSS_F_USB3_GRXTHRCFG_GRXTHRCFG_RESERVED_28(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_USB3_GRXTHRCFG_GRXTHRCFG_RESERVED_28  VTSS_BIT(28)
#define  VTSS_X_USB3_GRXTHRCFG_GRXTHRCFG_RESERVED_28(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * USB Receive Packet Count Enable
 *
 * This field enables/disables the USB reception multi-packet thresholding:
 *  - 0: The controller can only start reception on the USB when the RX
 * FIFO has space for at least one packet.
 *  - 1: The controller can only start reception on the USB when the RX
 * FIFO has space for at least UsbRxPktCnt amount of packets. This mode is
 * valid in both host and device mode. It is only used for SuperSpeed.
 * In device mode,
 *  - Setting this bit to 1 also enables the functionality of reporting
 * NUMP in the ACK TP based on the RX FIFO space instead of reporting a
 * fixed NUMP derived from DCFG.NUMP for non-control endpoints.
 *  - If you are using external buffer control (EBC) feature, disable this
 * mode by setting UsbRxPktCntSel to 0.
 *
 * \details
 * Field: ::VTSS_USB3_GRXTHRCFG . USBRXPKTCNTSEL
 */
#define  VTSS_F_USB3_GRXTHRCFG_USBRXPKTCNTSEL(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_USB3_GRXTHRCFG_USBRXPKTCNTSEL  VTSS_BIT(29)
#define  VTSS_X_USB3_GRXTHRCFG_USBRXPKTCNTSEL(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GRXTHRCFG . RESERVED_31_30
 */
#define  VTSS_F_USB3_GRXTHRCFG_RESERVED_31_30(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_USB3_GRXTHRCFG_RESERVED_31_30     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_USB3_GRXTHRCFG_RESERVED_31_30(x)  VTSS_EXTRACT_BITFIELD(x,30,2)


/**
 * \brief Global Core Control Register

Refer to <workspace>/src/DWC_usb3_params.v for details on `DWC_USB3_GCTL_INIT.

Note:

When Hibernation is not enabled, you can write any value to GblHibernationEn. It always returns 0 when read.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GCTL
 */
#define VTSS_USB3_GCTL                       VTSS_IOREG(VTSS_TO_USB3,0x3044)

/**
 * \brief
 * Disable Clock Gating (DsblClkGtng)
 *
 * This bit is set to 1 and the controller is in Low Power mode, internal
 * clock gating is disabled.
 *
 * You can set this bit to 1'b1 after Power On Reset.
 *
 * \details
 * Field: ::VTSS_USB3_GCTL . DSBLCLKGTNG
 */
#define  VTSS_F_USB3_GCTL_DSBLCLKGTNG(x)      VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_USB3_GCTL_DSBLCLKGTNG         VTSS_BIT(0)
#define  VTSS_X_USB3_GCTL_DSBLCLKGTNG(x)      VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * GblHibernationEn
 *
 * This bit enables hibernation at the global level. If hibernation is not
 * enabled through this bit, the PMU immediately accepts the D0->D3 and
 * D3->D0 power state change requests, but does not save or restore any
 * controller state.
 *
 * In addition, the PMUs never drive the PHY interfaces and let the
 * controller continue to drive the PHY interfaces.
 *
 * \details
 * Field: ::VTSS_USB3_GCTL . GBLHIBERNATIONEN
 */
#define  VTSS_F_USB3_GCTL_GBLHIBERNATIONEN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_USB3_GCTL_GBLHIBERNATIONEN    VTSS_BIT(1)
#define  VTSS_X_USB3_GCTL_GBLHIBERNATIONEN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * U2EXIT_LFPS
 *
 * If this bit is,
 *  - 0: the link treats 248ns LFPS as a valid U2 exit.
 *  - 1: the link waits for 8us of LFPS before it detects a valid U2 exit.
 * This bit is added to improve interoperability with a third-party
 * host/device controller. This host/device controller in U2 state while
 * performing receiver detection generates an LFPS glitch of about 4ms
 * duration. This causes the host/device to exit from U2 state because the
 * LFPS filter value is 248ns. With the new functionality enabled, the
 * host/device can stay in U2 while ignoring this glitch from the
 * host/device controller.
 *
 * This bit is applicable for both host and device controller.
 *
 * This bit is added to improve interoperability with a third party host
 * controller. This host controller in U2 state while performing receiver
 * detection generates an LFPS glitch of about 4ms duration. This causes
 * the device to exit from U2 state because the LFPS filter value is 248ns.
 * With the new functionality enabled, the device can stay in U2 while
 * ignoring this glitch from the host controller.
 *
 * \details
 * Field: ::VTSS_USB3_GCTL . U2EXIT_LFPS
 */
#define  VTSS_F_USB3_GCTL_U2EXIT_LFPS(x)      VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_USB3_GCTL_U2EXIT_LFPS         VTSS_BIT(2)
#define  VTSS_X_USB3_GCTL_U2EXIT_LFPS(x)      VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Disable Scrambling (DisScramble)
 *
 *  Transmit request to Link Partner on next transition to Recovery or
 * Polling.
 *
 * \details
 * Field: ::VTSS_USB3_GCTL . DISSCRAMBLE
 */
#define  VTSS_F_USB3_GCTL_DISSCRAMBLE(x)      VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_USB3_GCTL_DISSCRAMBLE         VTSS_BIT(3)
#define  VTSS_X_USB3_GCTL_DISSCRAMBLE(x)      VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Scale-Down Mode (ScaleDown)
 *
 * When Scale-Down mode is enabled for simulation, the controller uses
 * scaled-down timing values, resulting in faster simulations.
 *
 * When Scale-Down mode is disabled, actual timing values are used. This is
 * required for hardware operation.
 *
 * HS/FS/LS Modes
 *  - 2'b00: Disables all scale-downs. Actual timing values are used.
 *  - 2'b01: Enables scale-down of all timing values except Device mode
 * suspend and resume. These include Speed enumeration, HNP/SRP, and Host
 * mode suspend and resume
 *  - 2'b10: Enables scale-down of Device mode suspend and resume timing
 * values only.
 *  - 2'b11: Enables bit 0 and bit 1 scale-down timing values.
 * SS Mode
 *  - 2'b00: Disables all scale-downs. Actual timing values are used.
 *  - 2'b01: Enables scaled down SS timing and repeat values including: (1)
 * Number of TxEq training sequences reduce to 8; (2) LFPS polling burst
 * time reduce to 256 nS; (3) LFPS warm reset receive reduce to 30 uS.
 * Refer to the rtl_vip_scaledown_mapping.xls file under
 * <workspace>/sim/SoC_sim directory for the complete list.
 *  - 2'b10: No TxEq training sequences are sent. Overrides Bit 4.
 *  - 2'b11: Enables bit 0 and bit 1 scale-down timing values.
 *
 * \details
 * Field: ::VTSS_USB3_GCTL . SCALEDOWN
 */
#define  VTSS_F_USB3_GCTL_SCALEDOWN(x)        VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_USB3_GCTL_SCALEDOWN           VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_USB3_GCTL_SCALEDOWN(x)        VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * RAM Clock Select (RAMClkSel)
 *  - 2'b00: bus clock
 *  - 2'b01: pipe clock (Only used in device mode)
 *  - 2'b10: In device mode , pipe/2 clock.In Host mode, controller
 * switches ram_clk between pipe/2 clock, mac2_clk and bus_clk based on the
 * status of the U2/U3 ports
 *  - 2'b11: In device mode, selects mac2_clk as ram_clk (when 8-bit UTMI
 * or ULPI used. Not supported in 16-bit UTMI mode) In Host mode,
 * controller switches ram_clk between pipe_clk, mac2_clk and bus_clk based
 * on the status of the U2/U3 ports.
 * In device mode, upon a USB reset and USB disconnect, the hardware clears
 * these bits to 2'b00. For more information on how to select the RAM
 * clock, see the "Clock Generation and Clock Tree Synthesis (CTS)
 * Requirements" section in the Databook.
 *
 * Note:
 *  - In device mode, if you set RAMClkSel to 2'b11 (mac2_clk), the
 * controller internally switches the ram_clk to bus_clk when the link
 * state changes to Suspend (L2 or L3), and switches the ram_clk back to
 * mac2_clk when the link state changes to resume or U2.
 *  - In host mode, if a value of 2/3 is chosen, then controller switches
 * ram_clk between bus_clk, mac2_clk and pipe_clk, pipe_clk/2, based on the
 * state of the U2/U3 ports. For example, if only the U2 port is active and
 * the U3 ports are suspended, then the ram_clk is switched to mac2_clk.
 * When only the U3 ports are active and the U2 ports are suspended, the
 * controller internally switches the ram_clk to pipe3 clock and when all
 * U2 and U3 ports are suspended, it switches the ram_clk to bus_clk. This
 * allows decoupling the ram_clk from the bus_clk, and depending on the
 * bandwidth requirement allows the bus_clk to be run at a lower frequency
 * than the ram_clk requirements. The bus_clk frequency still cannot be
 * less than 60MHz in host mode, and this is not verified.
 * A value of 2 can be chosen only if the pipe data width is 8 or 16 bits.
 * In this case the when the ram_clk is switched to pipe_clk, it uses
 * pipe_clk/2 instead of pipe_clk. If a value of 3 is chosen for RAMClkSel,
 * then when ram_clk is switched to pipe_clk, then pipe_clk is used without
 * any divider.
 *  - In device mode, when RAMClkSel != 2'b00, the bus_clk_early frequency
 * can be a minimum of 1 MHz. This is tested in simulation and also in
 * hardware with Linux, Microsoft Windows 8, and MCCI Windows7 host
 * drivers. Only control and non periodic transfers are supported when
 * bus_clk is 1 MHz. For periodic applications, the bus_clk_early minimum
 * frequency is higher depending on your application and SoC bus. Even
 * though 1 MHz has been tested with standard host drivers, Synopsys
 * recommends 5 MHz minimum for ASIC designs to provide a margin or at
 * least have a backup option to increase the bus_clk frequency to 5 MHz if
 * needed.
 * Programming this field with random data will cause side effect. Bit Bash
 * register testing is not recommended.
 *
 * \details
 * Field: ::VTSS_USB3_GCTL . RAMCLKSEL
 */
#define  VTSS_F_USB3_GCTL_RAMCLKSEL(x)        VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_USB3_GCTL_RAMCLKSEL           VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_USB3_GCTL_RAMCLKSEL(x)        VTSS_EXTRACT_BITFIELD(x,6,2)

/**
 * \brief
 * Debug Attach
 *
 * When this bit is set,
 *  - SS Link proceeds directly to the Polling link state (after RUN/STOP
 * in the DCTL register is asserted) without checking remote termination;
 *  - Link LFPS polling timeout is infinite;
 *  - Polling timeout during TS1 is infinite (in case link is waiting for
 * TXEQ to finish).
 *
 * \details
 * Field: ::VTSS_USB3_GCTL . DEBUGATTACH
 */
#define  VTSS_F_USB3_GCTL_DEBUGATTACH(x)      VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_USB3_GCTL_DEBUGATTACH         VTSS_BIT(8)
#define  VTSS_X_USB3_GCTL_DEBUGATTACH(x)      VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Disable U1/U2 timer Scaledown (U1U2TimerScale).
 *
 * If set to '1' along with GCTL[5:4] (ScaleDown) = 2'bX1, disables the
 * scale down of U1/U2 inactive timer values. This is for simulation mode
 * only.
 *
 * \details
 * Field: ::VTSS_USB3_GCTL . U1U2TIMERSCALE
 */
#define  VTSS_F_USB3_GCTL_U1U2TIMERSCALE(x)   VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_USB3_GCTL_U1U2TIMERSCALE      VTSS_BIT(9)
#define  VTSS_X_USB3_GCTL_U1U2TIMERSCALE(x)   VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * SOFITPSYNC
 *
 * If this bit is set to '0' operating in host mode, the controller keeps
 * the UTMI/ULPI PHY on the first port in a non-suspended state whenever
 * there is a SuperSpeed port that is not in Rx.Detect, SS.Disable and U3.
 *
 * If this bit is set to '1' operating in host mode, the controller keeps
 * the UTMI/ULPI PHY on the first port in a non-suspended state whenever
 * the other non-SuperSpeed ports are not in a suspended state. This
 * feature is useful because it saves power by suspending UTMI/ULPI when
 * SuperSpeed only is active, and it helps resolve when the PHY does not
 * transmit a host resume unless it is placed in suspend state. This bit
 * must be programmed as a part of initialization at power-on reset, and
 * must not be dynamically changed afterwards.
 *
 * Note:
 *  - USB2PHYCFGn[6].PhySusp eventually decides to put the UTMI/ULPI PHY in
 * to suspend state. In addition, when this bit is set to '1', the
 * controller generates ITP from the ref_clk based counter. Otherwise, ITP
 * and SOF are generated from utmi/ulpi_clk[0] based counter. To program
 * the reference clock period inside the controller, refer to
 * GUCTL[31:22].REFCLKPER.
 *  - This feature is valid in Host and DRD configurations and used only in
 * Host mode operation.
 *  - If you never use this feature or the GFLADJ.GFLADJ_REFCLK_LPM_SEL,
 * the minimum frequency for the ref_clk can be as low as 32KHz. You can
 * connect the suspend_clk (as low as 32 KHz) to the ref_clk.
 *  - If you plan to enable hardware-based LPM or software-based LPM
 * (PORTPMSC. HLE=1), then you cannot use this feature. Turn off this
 * feature by setting this bit to '0' and use the
 * GFLADJ.GFLADJ_REFCLK_LPM_SEL feature.
 *  - If you set this bit to '1', the GUSB2PHYCFG.U2_FREECLK_EXISTS bit and
 * the DWC_USB3_FREECLK_USB2_EXIST parameter must be set to '0'.
 * Program this bit to 0 if the controller is intended to be operated in
 * USB 3.0 mode.
 *
 * \details
 * Field: ::VTSS_USB3_GCTL . SOFITPSYNC
 */
#define  VTSS_F_USB3_GCTL_SOFITPSYNC(x)       VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_USB3_GCTL_SOFITPSYNC          VTSS_BIT(10)
#define  VTSS_X_USB3_GCTL_SOFITPSYNC(x)       VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Core Soft Reset (CoreSoftReset)
 *  - 1'b0 - No soft reset
 *  - 1'b1 - Soft reset to controller
 * Clears the interrupts and all the CSRs except the following registers:
 *  - GCTL
 *  - GUCTL
 *  - GSTS
 *  - GSNPSID
 *  - GGPIO
 *  - GUID
 *  - GUSB2PHYCFGn registers
 *  - GUSB3PIPECTLn registers
 *  - DCFG
 *  - DCTL
 *  - DEVTEN
 *  - DSTS
 * When you reset PHYs (using GUBS3PHYCFG or GUSB3PIPECTL registers), you
 * must keep the controller in reset state until PHY clocks are stable.
 * This controls the bus, ram, and mac domain resets. Refer to the "Reset
 * Generation" section in the Databook.
 *
 * Note: This bit is for debug purposes only. Use USBCMD.HCRESET in xHCI
 * Mode and DCTL.SoftReset in device mode for soft reset.
 *
 *  Programming this field with random data will reset the internal logic
 * of the host controller. Due to this side effect Bit Bash register
 * testing is not recommended.
 *
 * \details
 * Field: ::VTSS_USB3_GCTL . CORESOFTRESET
 */
#define  VTSS_F_USB3_GCTL_CORESOFTRESET(x)    VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_USB3_GCTL_CORESOFTRESET       VTSS_BIT(11)
#define  VTSS_X_USB3_GCTL_CORESOFTRESET(x)    VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * PRTCAPDIR: Port Capability Direction (PrtCapDir)
 *  - 2'b01: for Host configurations
 *  - 2'b10: for Device configurations
 * Note: For static Host-only/Device-only applications, use DRD Host or DRD
 * Device mode. The combination of GCTL.PrtCapDir=2'b11 with SRP and
 * HNP/RSP disabled is not recommended for these applications.
 *
 * The sequence for switching modes in DRD configuration is as follows:
 *
 * Switching from Device to Host:
 *
 * 1. Reset the controller using GCTL[11] (CoreSoftReset).
 *
 * 2. Set GCTL[13:12] (PrtCapDir) to 2'b01 (Host mode).
 *
 * 3. Reset the host using USBCMD.HCRESET.
 *
 * 4. Follow the steps in "Initializing Host Registers" section of the
 * Programming Guide.
 *
 * Switching from Host to Device:
 *
 * 1. Reset the controller using GCTL[11] (CoreSoftReset).
 *
 * 2. Set GCTL[13:12] (PrtCapDir) to 2'b10 (Device mode).
 *
 * 3. Reset the device by setting DCTL[30] (CSftRst).
 *
 * 4. Follow the steps in "Register Initialization" section of the
 * Programming Guide.
 *
 * Programming this field with random data causes the controller to keep
 * toggling between the host mode and the device mode . Bit Bash register
 * testing is not recommended.
 *
 * \details
 * Field: ::VTSS_USB3_GCTL . PRTCAPDIR
 */
#define  VTSS_F_USB3_GCTL_PRTCAPDIR(x)        VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_USB3_GCTL_PRTCAPDIR           VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_USB3_GCTL_PRTCAPDIR(x)        VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * FRMSCLDWN
 *
 * This field scales down device view of a SOF/USOF/ITP duration.
 *
 * For SS/HS mode:
 *  - Value of 2'h3 implements interval to be 15.625 us
 *  - Value of 2'h2 implements interval to be 31.25 us
 *  - Value of 2'h1 implements interval to be 62.5 us
 *  - Value of 2'h0 implements interval to be 125us
 * For FS mode, the scale-down value is multiplied by 8.
 *
 * When xHCI Debug Capability is enabled, this field also scales down the
 * MaxPacketSize of the IN and OUT bulk endpoint to allow more traffic
 * during simulation. It can only be changed from a non-zero value during
 * simulation.
 *  - 2'h0: 1024 bytes
 *  - 2'h1: 512 bytes
 *  - 2'h2: 256 bytes
 *  - 2'h3: 128 bytes
 *
 * \details
 * Field: ::VTSS_USB3_GCTL . FRMSCLDWN
 */
#define  VTSS_F_USB3_GCTL_FRMSCLDWN(x)        VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_USB3_GCTL_FRMSCLDWN           VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_USB3_GCTL_FRMSCLDWN(x)        VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * U2RSTECN
 *
 * If the SuperSpeed connection fails during POLL or LMP exchange, the
 * device connects at non-SS mode.
 *
 * If this bit is set, then device attempts three more times to connect at
 * SS, even if it previously failed to operate in SS mode. For each
 * attempt, the device checks receiver termination eight times.
 *
 * From 2.60a release, this bit controls whether to check for Rx.Detect
 * eight times or one time for every attempt. Device controller on USB 2.0
 * reset checks for receiver termination eight times per attempt if this
 * bit is set to zero, or only once per attempt if the bit is set to one.
 *
 * Note: This bit is applicable only in device mode.
 *
 * \details
 * Field: ::VTSS_USB3_GCTL . U2RSTECN
 */
#define  VTSS_F_USB3_GCTL_U2RSTECN(x)         VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_USB3_GCTL_U2RSTECN            VTSS_BIT(16)
#define  VTSS_X_USB3_GCTL_U2RSTECN(x)         VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Bypass SetAddress in Device Mode.
 *
 * When BYPSSETADDR bit is set, the device controller uses the value in the
 * DCFG[DevAddr] bits directly for comparing the device address in the
 * tokens.
 *
 * For simulation, you can use this feature to avoid sending an actual SET
 * ADDRESS control transfer on the USB, and make the device controller
 * respond to a new address.
 *
 * When the xHCI Debug capability is enabled and this bit is set, the Debug
 * Target immediately enters the configured state without requiring the
 * Debug Host to send a SetAddress or SetConfig request.
 *
 * Note: You can set this bit for simulation purposes only. In the actual
 * hardware, this bit must be set to 1'b0.
 *
 * \details
 * Field: ::VTSS_USB3_GCTL . BYPSSETADDR
 */
#define  VTSS_F_USB3_GCTL_BYPSSETADDR(x)      VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_USB3_GCTL_BYPSSETADDR         VTSS_BIT(17)
#define  VTSS_X_USB3_GCTL_BYPSSETADDR(x)      VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Master Filter Bypass
 *
 * When this bit is set to 1'b1, irrespective of the parameter
 * `DWC_USB3_EN_BUS_FILTERS chosen, all the filters in the DWC_usb3_filter
 * module are bypassed.
 *
 * The double synchronizers to mac_clk preceding the filters are also
 * bypassed. For enabling the filters, this bit must be 1'b0.
 *
 * \details
 * Field: ::VTSS_USB3_GCTL . MASTERFILTBYPASS
 */
#define  VTSS_F_USB3_GCTL_MASTERFILTBYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_USB3_GCTL_MASTERFILTBYPASS    VTSS_BIT(18)
#define  VTSS_X_USB3_GCTL_MASTERFILTBYPASS(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Power Down Scale (PwrDnScale)
 *
 * The USB3 suspend_clk input replaces pipe3_rx_pclk as a clock source to a
 * small part of the USB3 controller that operates when the SS PHY is in
 * its lowest power (P3) state, and therefore does not provide a clock.
 *
 * The Power Down Scale field specifies how many suspend_clk periods fit
 * into a 16 kHz clock period. When performing the division, round up the
 * remainder.
 *
 * For example, when using an 8-bit/16-bit/32-bit PHY and 25-MHz Suspend
 * clock,
 *
 * Power Down Scale = 25000 kHz/16 kHz = 13'd1563 (rounder up)
 *
 * Note:
 *  - Minimum Suspend clock frequency is 32 kHz
 *  - Maximum Suspend clock frequency is 125 MHz
 * The LTSSM uses Suspend clock for 12-ms and 100-ms timers during suspend
 * mode. According to the USB 3.0 specification, the accuracy on these
 * timers is 0% to +50%.
 *  - 12 ms + 0~+50% accuracy = 18 ms (Range is 12 ms - 18 ms)
 *  - 100 ms + 0~+50% accuracy = 150 ms (Range is 100 ms - 150 ms).
 * The suspend clock accuracy requirement is:
 *  - (12,000/62.5) * (GCTL[31:19]) * actual suspend_clk_period must be
 * between 12,000 and 18,000
 *  - (100,0000/62.5) * (GCTL[31:19]) * actual suspend_clk_period must be
 * between 100,000 and 150,000
 * For example, if your suspend_clk frequency varies from 7.5 MHz to
 * 10.5MHz, then the value needs to programmed is:
 *
 * Power Down Scale = 10500/16 = 657 (rounded up; and fastest frequency
 * used).
 *
 * \details
 * Field: ::VTSS_USB3_GCTL . PWRDNSCALE
 */
#define  VTSS_F_USB3_GCTL_PWRDNSCALE(x)       VTSS_ENCODE_BITFIELD(x,19,13)
#define  VTSS_M_USB3_GCTL_PWRDNSCALE          VTSS_ENCODE_BITMASK(19,13)
#define  VTSS_X_USB3_GCTL_PWRDNSCALE(x)       VTSS_EXTRACT_BITFIELD(x,19,13)


/**
 * \brief Global Power Management Status Register

This debug register gives information on which event caused the hibernation exit. It provides internal status and state machine information, and is for Synopsys use only for debugging purposes.

This register is not applicable in USB 2.0-only mode.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GPMSTS
 */
#define VTSS_USB3_GPMSTS                     VTSS_IOREG(VTSS_TO_USB3,0x3045)

/**
 * \brief
 * U2Wakeup
 *
 * This field indicates the following USB 2.0 port wakeup conditions:
 *  - Bit [0]: Overcurrent Detected
 *  - Bit [1]: Resume Detected
 *  - Bit [2]: Connect Detected
 *  - Bit [3]: Disconnect Detected
 *  - Bit [4]: Last Connection State
 *  - Bit [5]: ID Change Detected
 *  - Bit [6]: SRP Request Detected
 *  - Bit [7]: ULPI Interrupt Detected
 *  - Bit [8]: USB Reset Detected
 *  - Bit [9]: Resume Detected Changed
 *
 * \details
 * Field: ::VTSS_USB3_GPMSTS . U2WAKEUP
 */
#define  VTSS_F_USB3_GPMSTS_U2WAKEUP(x)       VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_USB3_GPMSTS_U2WAKEUP          VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_USB3_GPMSTS_U2WAKEUP(x)       VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GPMSTS . RESERVED_10_11
 */
#define  VTSS_F_USB3_GPMSTS_RESERVED_10_11(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_USB3_GPMSTS_RESERVED_10_11     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_USB3_GPMSTS_RESERVED_10_11(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/**
 * \brief
 * U3Wakeup
 *
 * This field gives the following USB 3.0 port wakeup conditions:
 *  - Bit [12]: Overcurrent Detected
 *  - Bit [13]: Resume Detected
 *  - Bit [14]: Connect Detected
 *  - Bit [15]: Disconnect Detected
 *  - Bit [16]: Last Connection State
 *
 * \details
 * Field: ::VTSS_USB3_GPMSTS . U3WAKEUP
 */
#define  VTSS_F_USB3_GPMSTS_U3WAKEUP(x)       VTSS_ENCODE_BITFIELD(x,12,5)
#define  VTSS_M_USB3_GPMSTS_U3WAKEUP          VTSS_ENCODE_BITMASK(12,5)
#define  VTSS_X_USB3_GPMSTS_U3WAKEUP(x)       VTSS_EXTRACT_BITFIELD(x,12,5)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GPMSTS . RESERVED_27_17
 */
#define  VTSS_F_USB3_GPMSTS_RESERVED_27_17(x)  VTSS_ENCODE_BITFIELD(x,17,11)
#define  VTSS_M_USB3_GPMSTS_RESERVED_27_17     VTSS_ENCODE_BITMASK(17,11)
#define  VTSS_X_USB3_GPMSTS_RESERVED_27_17(x)  VTSS_EXTRACT_BITFIELD(x,17,11)

/**
 * \brief
 * Global Power Management Status Register, PortSel
 *
 * This field selects the port number.
 *
 * \details
 * Field: ::VTSS_USB3_GPMSTS . PORTSEL
 */
#define  VTSS_F_USB3_GPMSTS_PORTSEL(x)        VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_USB3_GPMSTS_PORTSEL           VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_USB3_GPMSTS_PORTSEL(x)        VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief Global Status Register
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GSTS
 */
#define VTSS_USB3_GSTS                       VTSS_IOREG(VTSS_TO_USB3,0x3046)

/**
 * \brief
 * Current Mode of Operation (CurMod)
 *
 * Indicates the current mode of operation:
 *  - 2'b00: Device mode
 *  - 2'b01: Host mode

 *
 * \details
 * Field: ::VTSS_USB3_GSTS . CURMOD
 */
#define  VTSS_F_USB3_GSTS_CURMOD(x)           VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_USB3_GSTS_CURMOD              VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_USB3_GSTS_CURMOD(x)           VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GSTS . RESERVED_3_2
 */
#define  VTSS_F_USB3_GSTS_RESERVED_3_2(x)     VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_USB3_GSTS_RESERVED_3_2        VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_USB3_GSTS_RESERVED_3_2(x)     VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * Bus Error Address Valid (BusErrAddrVld)
 *
 * Indicates that the GBUSERRADDR register is valid and reports the first
 * bus address that encounters a bus error.
 *
 * Note: Only supported in AHB and AXI configurations.
 *
 * \details
 * Field: ::VTSS_USB3_GSTS . BUSERRADDRVLD
 */
#define  VTSS_F_USB3_GSTS_BUSERRADDRVLD(x)    VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_USB3_GSTS_BUSERRADDRVLD       VTSS_BIT(4)
#define  VTSS_X_USB3_GSTS_BUSERRADDRVLD(x)    VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * CSR Timeout
 *
 * When this bit is 1'b1, it indicates that the software performed a write
 * or read to a controller register that could not be completed within
 * `DWC_USB3_CSR_ACCESS_TIMEOUT bus clock cycles (default: h1FFFF).
 *
 * \details
 * Field: ::VTSS_USB3_GSTS . CSRTIMEOUT
 */
#define  VTSS_F_USB3_GSTS_CSRTIMEOUT(x)       VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_USB3_GSTS_CSRTIMEOUT          VTSS_BIT(5)
#define  VTSS_X_USB3_GSTS_CSRTIMEOUT(x)       VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Device Interrupt Pending
 *
 * This field indicates that there is a pending interrupt pertaining to
 * peripheral (device) operation in the Device event queue.

 *
 * \details
 * Field: ::VTSS_USB3_GSTS . DEVICE_IP
 */
#define  VTSS_F_USB3_GSTS_DEVICE_IP(x)        VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_USB3_GSTS_DEVICE_IP           VTSS_BIT(6)
#define  VTSS_X_USB3_GSTS_DEVICE_IP(x)        VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Host Interrupt Pending:
 *
 * This field indicates that there is a pending interrupt pertaining to xHC
 * in the Host event queue.
 *
 * \details
 * Field: ::VTSS_USB3_GSTS . HOST_IP
 */
#define  VTSS_F_USB3_GSTS_HOST_IP(x)          VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_USB3_GSTS_HOST_IP             VTSS_BIT(7)
#define  VTSS_X_USB3_GSTS_HOST_IP(x)          VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * This field is not used.
 *
 * \details
 * Field: ::VTSS_USB3_GSTS . ADP_IP
 */
#define  VTSS_F_USB3_GSTS_ADP_IP(x)           VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_USB3_GSTS_ADP_IP              VTSS_BIT(8)
#define  VTSS_X_USB3_GSTS_ADP_IP(x)           VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Battery Charger Interrupt Pending
 *
 * This field indicates that there is a pending interrupt pertaining to BC
 * in BCEVT register.
 *
 * \details
 * Field: ::VTSS_USB3_GSTS . BC_IP
 */
#define  VTSS_F_USB3_GSTS_BC_IP(x)            VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_USB3_GSTS_BC_IP               VTSS_BIT(9)
#define  VTSS_X_USB3_GSTS_BC_IP(x)            VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * This field is not used.
 *
 * \details
 * Field: ::VTSS_USB3_GSTS . OTG_IP
 */
#define  VTSS_F_USB3_GSTS_OTG_IP(x)           VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_USB3_GSTS_OTG_IP              VTSS_BIT(10)
#define  VTSS_X_USB3_GSTS_OTG_IP(x)           VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * This field is not used.
 *
 * \details
 * Field: ::VTSS_USB3_GSTS . SSIC_IP
 */
#define  VTSS_F_USB3_GSTS_SSIC_IP(x)          VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_USB3_GSTS_SSIC_IP             VTSS_BIT(11)
#define  VTSS_X_USB3_GSTS_SSIC_IP(x)          VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GSTS . RESERVED_19_12
 */
#define  VTSS_F_USB3_GSTS_RESERVED_19_12(x)   VTSS_ENCODE_BITFIELD(x,12,8)
#define  VTSS_M_USB3_GSTS_RESERVED_19_12      VTSS_ENCODE_BITMASK(12,8)
#define  VTSS_X_USB3_GSTS_RESERVED_19_12(x)   VTSS_EXTRACT_BITFIELD(x,12,8)

/**
 * \brief
 * Current BELT Value
 *
 * In Host mode, this field indicates the minimum value of all received
 * device BELT values and the BELT value that is set by the Set Latency
 * Tolerance Value command.
 *
 * \details
 * Field: ::VTSS_USB3_GSTS . CBELT
 */
#define  VTSS_F_USB3_GSTS_CBELT(x)            VTSS_ENCODE_BITFIELD(x,20,12)
#define  VTSS_M_USB3_GSTS_CBELT               VTSS_ENCODE_BITMASK(20,12)
#define  VTSS_X_USB3_GSTS_CBELT(x)            VTSS_EXTRACT_BITFIELD(x,20,12)


/**
 * \brief Global User Control Register 1
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GUCTL1
 */
#define VTSS_USB3_GUCTL1                     VTSS_IOREG(VTSS_TO_USB3,0x3047)

/**
 * \brief
 * LOA_FILTER_EN
 *
 * If this bit is set, the USB 2.0 port babble is checked at least three
 * consecutive times before the port is disabled. This prevents false
 * triggering of the babble condition when using low quality cables.
 *
 * Note: This bit is valid only in host mode.

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . LOA_FILTER_EN
 */
#define  VTSS_F_USB3_GUCTL1_LOA_FILTER_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_USB3_GUCTL1_LOA_FILTER_EN     VTSS_BIT(0)
#define  VTSS_X_USB3_GUCTL1_LOA_FILTER_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * OVRLD_L1_SUSP_COM
 *
 * If this bit is set, the utmi_l1_suspend_com_n is overloaded with the
 * utmi_sleep_n signal. This bit is usually set if the PHY stops the port
 * clock during L1 sleep condition.
 *
 * Note: The recommended connection for the SUSPENDM/SLEEPM signals to the
 * PHY with respect to this bit is as follows.
 *
 * For non-zero ports:
 *
 * Connect:
 *  - utmi_sleep_n[n] to SLEEPM[n]
 *  - (utmi_suspend_n[n] & utmi_l1_suspend_n[n]) to SUSPENDM[n]
 *  - USB2 PHYCLK[n] to utmi_clk[n]
 * GUCTL1.OVRLD_L1_SUSP_COM impacts only Port0.
 *
 * For Port0:
 *
 * For Synopsys PHY,
 *
 * GUSB2PHYCFGn.U2_FREECLK_EXISTS=1; With this connection, the PHY keeps
 * PLL active so that FREECLK is always available irrespective of
 * suspend/sleep.
 *  - Connect USB2 PHY COMMONONN to 0.
 *  - Connect utmi_sleep_n[0] to SLEEPM[0].
 *  - Connect (utmi_suspend_n[0] & utmi_l1_suspend_n[0]) to SUSPENDM[0].
 *  - Connect USB2 PHY FREECLK to utmi_clk[0].
 *  - Leave utmi_suspend_com_n, utmi_l1_suspend_com_n unconnected.
 *  - GUCTL1.OVRLD_L1_SUSP_COM can be set to any value.
 * For Third Party PHY,
 *
 * GUSB2PHYCFGn.U2_FREECLK_EXISTS=0; With this connection the PHY can shut
 * off all the clocks when the required conditions are met (like,
 * GUSB2PHYCFGn[8,6], GUCTL1[1], GFLADJ[23], GCTL[10], Suspend condition,
 * HW LPM enable etc).
 *  - Connect -utmi_suspend_com_n to SUSPENDM[0] (or equivalent).
 *  - Connect -utmi_l1_suspend_com_n to SLEEPM[0] (or equivalent).
 *  - Connect PHYCLK0 (first port clock) to utmi_clk[0].
 *  - Leave utmi_suspend_n[0], utmi_l1_suspend_ n[0], utmi_sleep_n[0]
 * unconnected.
 *  - Set GUCTL1.OVRLD_L1_SUSP_COM to 1'b1.
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . OVRLD_L1_SUSP_COM
 */
#define  VTSS_F_USB3_GUCTL1_OVRLD_L1_SUSP_COM(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_USB3_GUCTL1_OVRLD_L1_SUSP_COM  VTSS_BIT(1)
#define  VTSS_X_USB3_GUCTL1_OVRLD_L1_SUSP_COM(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Host Parameter Check Disable (HParChkDisable)
 *
 * When this bit is set to '0' (by default), the xHC checks that the input
 * slot/EP context fields comply to the xHCI Specification. Upon detection
 * of a parameter error during command execution, the xHC generates an
 * event TRB with completion code indicating 'PARAMETER ERROR'.
 *
 * When the bit is set to '1', the xHC does not perform parameter checks
 * and does not generate 'PARAMETER ERROR' completion code.
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . HC_PARCHK_DISABLE
 */
#define  VTSS_F_USB3_GUCTL1_HC_PARCHK_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_USB3_GUCTL1_HC_PARCHK_DISABLE  VTSS_BIT(2)
#define  VTSS_X_USB3_GUCTL1_HC_PARCHK_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Host ELD Enable (HELDEn)
 *
 * When this bit is set to 1, it enables the Exit Latency Delta (ELD)
 * support defined in the xHCI 1.0 Errata.
 *
 * This bit is used only in the host mode. This bit has to be set to 1 in
 * Host mode.
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . HC_ERRATA_ENABLE
 */
#define  VTSS_F_USB3_GUCTL1_HC_ERRATA_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_USB3_GUCTL1_HC_ERRATA_ENABLE  VTSS_BIT(3)
#define  VTSS_X_USB3_GUCTL1_HC_ERRATA_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * L1_SUSP_THRLD_FOR_HOST
 *
 * This field is effective only when the L1_SUSP_THRLD_EN_FOR_HOST bit is
 * set to 1. For more details, refer to the description of the
 * L1_SUSP_THRLD_EN_FOR_HOST bit.
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . L1_SUSP_THRLD_FOR_HOST
 */
#define  VTSS_F_USB3_GUCTL1_L1_SUSP_THRLD_FOR_HOST(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_USB3_GUCTL1_L1_SUSP_THRLD_FOR_HOST     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_USB3_GUCTL1_L1_SUSP_THRLD_FOR_HOST(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * L1_SUSP_THRLD_EN_FOR_HOST
 *
 * This bit is used only in host mode.
 *
 * The host controller asserts the utmi_l1_suspend_n and utmi_sleep_n
 * output signals (see "LPM Interface Signals" table in the Databook) as
 * follows:
 *
 * The controller asserts the utmi_l1_suspend_n signal to put the PHY into
 * deep low-power mode in L1 when both of the following are true:
 *  - The HIRD/BESL value used is greater than or equal to the value in
 * L1_SUSP_THRLD_FOR_HOST field.
 *  - The L1_SUSP_THRLD_EN_FOR_HOST bit is set to 1'b1.
 * The controller asserts utmi_sleep_n on L1 when one of the following is
 * true:
 *  - The HIRD/BESL value used is less than the value in
 * L1_SUSP_THRLD_FOR_HOST field.
 *  - The L1_SUSP_THRLD_EN_FOR_HOST bit is set to 1'b0.
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . L1_SUSP_THRLD_EN_FOR_HOST
 */
#define  VTSS_F_USB3_GUCTL1_L1_SUSP_THRLD_EN_FOR_HOST(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_USB3_GUCTL1_L1_SUSP_THRLD_EN_FOR_HOST  VTSS_BIT(8)
#define  VTSS_X_USB3_GUCTL1_L1_SUSP_THRLD_EN_FOR_HOST(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * DEV_HS_NYET_BULK_SPR
 *  - 0: Default behavior, no change in device response
 *  - 1: Feature enabled, HS bulk OUT short packet gets NYET response
 * This bit is applicable for device mode only (and ignored in host mode)
 * to be used in 2.0 operation.
 *
 * If this bit is set, the device controller sends NYET response instead of
 * ACK response for a successfully received bulk OUT short packet.
 * If NYET is sent after receiving short packet, then the host would PING
 * before sending the next OUT; this improves the performance as well as
 * clears up the buffer/cache on the host side. Internal to the device
 * controller, short packet (SPR=1) processing takes some time, and during
 * this time, the USB is flow controlled. With NYET response instead of ACK
 * on short packet, the host does not send another OUT-DATA without pinging
 * in HS mode.
 *
 * This bit is quasi-static, that is, it must not be changed during device
 * operation.

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . DEV_HS_NYET_BULK_SPR
 */
#define  VTSS_F_USB3_GUCTL1_DEV_HS_NYET_BULK_SPR(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_USB3_GUCTL1_DEV_HS_NYET_BULK_SPR  VTSS_BIT(9)
#define  VTSS_X_USB3_GUCTL1_DEV_HS_NYET_BULK_SPR(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * RESUME_OPMODE_HS_HOST
 *
 * This bit is used only in host mode, and is for USB 2.0 opmode behavior
 * in HS Resume.
 *  - When this bit is set to '1', the UTMI/ULPI opmode will be changed to
 * "normal" along with HS terminations after EOR. This option is to support
 * certain legacy UTMI/ULPI PHYs.
 *  - When this bit is set to '0', the UTMI/ULPI opmode will be changed to
 * "normal" 2us after HS terminations change after EOR. This is the default
 * behavior.
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . RESUME_OPMODE_HS_HOST
 */
#define  VTSS_F_USB3_GUCTL1_RESUME_OPMODE_HS_HOST(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_USB3_GUCTL1_RESUME_OPMODE_HS_HOST  VTSS_BIT(10)
#define  VTSS_X_USB3_GUCTL1_RESUME_OPMODE_HS_HOST(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Disable ref_clk gating (DisRefClkGtng)
 *
 * If the ref_clk gating is disabled then input ref_clk cannot be turned
 * off to SSPHY and controller. This is independent of GCTL[DisClkGtng]
 * setting.
 *  - 1'b0: ref_clk gating Enabled for SSPHY
 *  - 1'b1: ref_clk gating Disabled for SSPHY
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . DISREFCLKGTNG
 */
#define  VTSS_F_USB3_GUCTL1_DISREFCLKGTNG(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_USB3_GUCTL1_DISREFCLKGTNG     VTSS_BIT(11)
#define  VTSS_X_USB3_GUCTL1_DISREFCLKGTNG(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Disable ref_clk gating for 2.0 PHY (DisUSB2RefClkGtng)
 *
 * If ref_clk gating is disabled, then the ref_clk input cannot be turned
 * off to the USB 2.0 PHY and controller. This is independent of the
 * GCTL[DisClkGtng] setting.
 *  - 1'b0: ref_clk gating enabled for USB 2.0 PHY
 *  - 1'b1: ref_clk gating disabled for USB 2.0 PHY
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . DISUSB2REFCLKGTNG
 */
#define  VTSS_F_USB3_GUCTL1_DISUSB2REFCLKGTNG(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_USB3_GUCTL1_DISUSB2REFCLKGTNG  VTSS_BIT(12)
#define  VTSS_X_USB3_GUCTL1_DISUSB2REFCLKGTNG(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . GUCTL1_RESERVED_14_13
 */
#define  VTSS_F_USB3_GUCTL1_GUCTL1_RESERVED_14_13(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_USB3_GUCTL1_GUCTL1_RESERVED_14_13     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_USB3_GUCTL1_GUCTL1_RESERVED_14_13(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/**
 * \brief
 * PARKMODE_DISABLE_FSLS
 *
 * This bit is used only in host mode, and is for debug purpose only.
 *
 * When this bit is set to '1' all FS/LS bus instances in park mode
 * disabled.
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . PARKMODE_DISABLE_FSLS
 */
#define  VTSS_F_USB3_GUCTL1_PARKMODE_DISABLE_FSLS(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_USB3_GUCTL1_PARKMODE_DISABLE_FSLS  VTSS_BIT(15)
#define  VTSS_X_USB3_GUCTL1_PARKMODE_DISABLE_FSLS(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * PARKMODE_DISABLE_HS
 *
 * This bit is used only in host mode.
 *
 * When this bit is set to '1' all HS bus instances park mode are disabled.
 *
 * To improve performance in park mode, the xHCI scheduler queues in three
 * requests of 4 packets each for High Speed asynchronous endpoints in a
 * micro-frame. But if a device is slow and if it NAKs more than 3 times,
 * then it is rescheduled only in the next micro-frame. This could decrease
 * the performance of a slow device even further.
 *
 * In a few high speed devices (such as Sandisk Cruzer Blade 4GB VID:1921,
 * PID:21863 and Flex Drive VID:3744, PID:8552) when an IN request is sent
 * within 900ns of the ACK of the previous packet, these devices send a
 * NAK. When connected to these devices, if required, the software can
 * disable the park mode if you see performance drop in your system. When
 * park mode is disabled, pipelining of multiple packet is disabled and
 * instead one packet at a time is requested by the scheduler. This allows
 * up to 12 NAKs in a micro-frame and improves performance of these slow
 * devices.
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . PARKMODE_DISABLE_HS
 */
#define  VTSS_F_USB3_GUCTL1_PARKMODE_DISABLE_HS(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_USB3_GUCTL1_PARKMODE_DISABLE_HS  VTSS_BIT(16)
#define  VTSS_X_USB3_GUCTL1_PARKMODE_DISABLE_HS(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * PARKMODE_DISABLE_SS
 *
 * This bit is used only in host mode, and is for debug purpose only.
 *
 * When this bit is set to '1' all SS bus instances in park mode are
 * disabled.
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . PARKMODE_DISABLE_SS
 */
#define  VTSS_F_USB3_GUCTL1_PARKMODE_DISABLE_SS(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_USB3_GUCTL1_PARKMODE_DISABLE_SS  VTSS_BIT(17)
#define  VTSS_X_USB3_GUCTL1_PARKMODE_DISABLE_SS(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * NAK_PER_ENH_HS
 *  - 1: Enables performance enhancement for HS async endpoints in the
 * presence of NAKs
 *  - 0: Enhancement not applied
 * If a periodic endpoint is present, and if a bulk endpoint which is also
 * active is being NAKed by the device, then this could result in
 * decrease in performance of other High Speed bulk endpoint which is ACked
 * by the device.
 * Setting this bit to 1, will enable the host controller to schedule more
 * transactions
 * to the async endpoints ( bulk/ control) and hence will improve the
 * performance of the
 * bulk endpoint.
 * This control bit should be enabled only if the existing performance with
 * the default
 * setting is not sufficient for your HighSpeed application. Setting this
 * bit will only
 * control, and is only required for High Speed transfers.

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . NAK_PER_ENH_HS
 */
#define  VTSS_F_USB3_GUCTL1_NAK_PER_ENH_HS(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_USB3_GUCTL1_NAK_PER_ENH_HS    VTSS_BIT(18)
#define  VTSS_X_USB3_GUCTL1_NAK_PER_ENH_HS(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * NAK_PER_ENH_FS
 *  - 1: Enables performance enhancement for FS async endpoints in the
 * presence of NAKs
 *  - 0: Enhancement not applied
 * If a periodic endpoint is present , and if a bulk endpoint which is also
 * active is being NAKed by the device, then this could result in a
 * decrease in performance of other Full Speed bulk endpoint which is ACked
 * by the device.
 * Setting this bit to 1, will enable the host controller to schedule more
 * transactions
 * to the async endpoints (bulk/ control) and hence will improve the
 * performance of the
 * bulk endpoint.
 * This control bit should be enabled only if the existing performance with
 * the default
 * setting is not sufficient for your FullSpeed application. Setting this
 * bit will only
 * control, and is only required for Full Speed transfers.

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . NAK_PER_ENH_FS
 */
#define  VTSS_F_USB3_GUCTL1_NAK_PER_ENH_FS(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_USB3_GUCTL1_NAK_PER_ENH_FS    VTSS_BIT(19)
#define  VTSS_X_USB3_GUCTL1_NAK_PER_ENH_FS(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * DEV_LSP_TAIL_LOCK_DIS
 *  - 0: Default behavior, enables device lsp lock logic for tail TRB
 * update
 *  - 1: Fix disabled
 * This is a bug fix for STAR 9000716195 that affects the CSP mode for OUT
 * endpoints in device mode. The issue is that tail TRB index is not
 * synchronized with the cache Scratchpad bytecount update.
 * If the fast-forward request comes in-between the bytecount update on a
 * newly fetched TRB and the tail-index write update in TPF,
 * the RDP works on an incorrect tail index and misses the byte count
 * decrement for the newly fetched TRB in the fast-forwarding process.
 * This fix needs to be present all the times.

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . DEV_LSP_TAIL_LOCK_DIS
 */
#define  VTSS_F_USB3_GUCTL1_DEV_LSP_TAIL_LOCK_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_USB3_GUCTL1_DEV_LSP_TAIL_LOCK_DIS  VTSS_BIT(20)
#define  VTSS_X_USB3_GUCTL1_DEV_LSP_TAIL_LOCK_DIS(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * This register field is used to add on to the default inter packet gap
 * setting in the USB 2.0 MAC.
 * This should be programmed to a non zero value only in case where you
 * need to increase the default inter packet delay calculations in the USB
 * 2.0 MAC module DWC_usb3_u2mac.v

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . IP_GAP_ADD_ON
 */
#define  VTSS_F_USB3_GUCTL1_IP_GAP_ADD_ON(x)  VTSS_ENCODE_BITFIELD(x,21,3)
#define  VTSS_M_USB3_GUCTL1_IP_GAP_ADD_ON     VTSS_ENCODE_BITMASK(21,3)
#define  VTSS_X_USB3_GUCTL1_IP_GAP_ADD_ON(x)  VTSS_EXTRACT_BITFIELD(x,21,3)

/**
 * \brief
 * DEV_L1_EXIT_BY_HW
 *  - 0: Default behavior, disables device L1 hardware exit logic
 *  - 1: feature enabled
 * This bit is applicable for device mode (2.0) only. This field enables
 * device controller sending remote wakeup for L1 if the device becomes
 * ready for sending/accepting data when in L1 state.
 * If the host expects the device to send remote wakeup signaling to resume
 * after going into L1 in flow controlled state, then this bit can be set
 * to send the remote wake signal automatically when the device controller
 * becomes ready.
 * This hardware remote wake feature is applicable only to bulk and
 * interrupt transfers, and not for Isoch/Control
 *  - When control transfers are in progress, the LPM will be rejected
 * (NYET response).  Only after control transfers are completed (either
 * with ACK/STALL), LPM will be accepted
 *  - For Isoch transfers, the host needs to do the wake-up  and start the
 * transfer. Device controller will not do remote-wakeup when Isoch
 * endpoints get ready. The device SW needs to keep the
 * GUSB2PHYCFG[EnblSlpM] reset in order to keep the PHY clock to be running
 * for keeping track of SOF intervals.
 *  - When L1 hibernation is enabled, the controller will not do automatic
 * exit for hibernation requests thru L1.
 * This bit is quasi-static, that is, it must not be changed during device
 * operation.

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . DEV_L1_EXIT_BY_HW
 */
#define  VTSS_F_USB3_GUCTL1_DEV_L1_EXIT_BY_HW(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_USB3_GUCTL1_DEV_L1_EXIT_BY_HW  VTSS_BIT(24)
#define  VTSS_X_USB3_GUCTL1_DEV_L1_EXIT_BY_HW(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * P3_IN_U2
 *  - 0: Default behavior, When SuperSpeed link is in U2, PowerState P2 is
 * attempted on the PIPE Interface.
 *  - 1: When SuperSpeed link is in U2, PowerState P3 is attempted if
 * GUSB3PIPECTL[17] is set.
 * Setting this bit enables P3 Power State when the SuperSpeed link is in
 * U2. Another Power Saving option. Check with your PHY vendor before
 * enabling this option.When setting this bit to 1 to enable P3 in P2,
 * GUSB3PIPECTL[27] should be set to 0 to make sure that the U2 exit is
 * attempted in P0. This bit should be set only when GCTL.SOFITPSYNC=1 or
 * GFLADJ.GFLADJ_REFCLK_LPM_SEL=1.

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . P3_IN_U2
 */
#define  VTSS_F_USB3_GUCTL1_P3_IN_U2(x)       VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_USB3_GUCTL1_P3_IN_U2          VTSS_BIT(25)
#define  VTSS_X_USB3_GUCTL1_P3_IN_U2(x)       VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * DEV_FORCE_20_CLK_FOR_30_CLK
 *  - 0: Default behavior, Uses 3.0 clock when operating in 2.0 mode
 *  - 1: Feature enabled
 * This bit is applicable (and to be set) for device mode (DCFG.Speed !=
 * SS) only. In the 3.0 device controller, if the controller is  programmed
 * to operate in 2.0 only (that is, Device Speed is programmed to 2.0
 * speeds in DCFG[Speed]),
 * then setting this bit makes the internal 2.0 (utmi/ulpi) clock to be
 * routed as the 3.0 (pipe) clock. Enabling this feature allows the pipe3
 * clock to be not-running when forcibly operating in 2.0 device mode.
 *
 * Note:
 *  - When using this feature, all pipe3 inputs must be in inactive mode.
 * In particular, the pipe3 clocks must not be running and the
 * pipe3_phystatus_async must be tied to 0. This bit should not be set if
 * the controller is programmed to operate in SuperSpeed mode (even when it
 * falls back to 2.0).
 *  - This bit is quasi-static, that is, it must not be changed during
 * operation.
 *  - If the parameter "DWC_USB3_REMOVE_PIPE_CLK_MUX_FOR_20_MODE" is
 * enabled, then muxing 2.0 clock/signals to pipe_clk/signals have to be
 * done outside the controller for this feature to work.

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . DEV_FORCE_20_CLK_FOR_30_CLK
 */
#define  VTSS_F_USB3_GUCTL1_DEV_FORCE_20_CLK_FOR_30_CLK(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_USB3_GUCTL1_DEV_FORCE_20_CLK_FOR_30_CLK  VTSS_BIT(26)
#define  VTSS_X_USB3_GUCTL1_DEV_FORCE_20_CLK_FOR_30_CLK(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * DEV_TRB_OUT_SPR_IND
 *  - 0: Default behavior, no change in TRB status dword
 *  - 1: Feature enabled, OUT TRB status indicates Short Packet
 * This bit is applicable for device mode only (and ignored in host mode).
 * If the device application (software/hardware) wants to know if a short
 * packet was received for an OUT in the TRB status itself, then this
 * feature can be enabled, so that a bit is set in the TRB writeback in the
 * buf_size dword. Bit[26] - SPR of the {trbstatus, RSVD, SPR, PCM1,
 * bufsize} dword will be set during an OUT transfer TRB write back if this
 * is the last TRB used for that transfer descriptor. This bit is
 * quasi-static, that is, it must not be changed during device operation.

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . DEV_TRB_OUT_SPR_IND
 */
#define  VTSS_F_USB3_GUCTL1_DEV_TRB_OUT_SPR_IND(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_USB3_GUCTL1_DEV_TRB_OUT_SPR_IND  VTSS_BIT(27)
#define  VTSS_X_USB3_GUCTL1_DEV_TRB_OUT_SPR_IND(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * TX_IPGAP_LINECHECK_DIS
 *  - 0: Default behavior, no change in Linestate check
 *  - 1: Feature enabled, 2.0 MAC disables Linestate check during HS
 * transmit
 * This bit is applicable for HS operation of u2mac. If this feature is
 * enabled, then the 2.0 mac operating in HS ignores the UTMI/ULPI
 * Linestate during the transmit of a token (during token-to-token and
 * token-to-data IPGAP). When enabled, the controller implements a fixed
 * 40-bit TxEndDelay after the packet is given on UTMI and ignores the
 * Linestate during this time. This feature is applicable only in HS mode
 * of operation.
 *
 * Device mode: If GUCTL1.TX_IPGAP_LINECHECK_DIS is set, then for device
 * LPM handshake, the controller will ignore the linestate after TX and
 * wait for fixed clocks (40 bit times equivalent) after transmitting ACK
 * on utmi.
 *
 * Host mode: If GUCTL1.TX_IPGAP_LINECHECK_DIS is set, then the ipgap
 * between (tkn to tkn/data) is added by 40 bit times of TXENDDELAY, and
 * linestate is ignored during this 40 bit times delay.
 *
 * Enable this bit if the LineState will not reflect the expected line
 * state (J) during transmission. This bit is quasi-static, that is, it
 * must not be changed during device operation.

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . TX_IPGAP_LINECHECK_DIS
 */
#define  VTSS_F_USB3_GUCTL1_TX_IPGAP_LINECHECK_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_USB3_GUCTL1_TX_IPGAP_LINECHECK_DIS  VTSS_BIT(28)
#define  VTSS_X_USB3_GUCTL1_TX_IPGAP_LINECHECK_DIS(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * FILTER_SE0_FSLS_EOP
 *  - 0: Default behavior, no change in Linestate check for SE0 detection
 * in FS/LS
 *  - 1: Feature enabled, FS/LS SE0 is filtered for 2 clocks for detecting
 * EOP
 * This bit is applicable for FS/LS operation. If this feature is enabled,
 * then SE0 on the linestate is validated for 2 consecutive utmi/ulpi clock
 * edges for EOP detection. This feature is applicable only in FS in device
 * mode and FS/LS mode of operation in host mode.
 *
 * Device mode: FS -  If GUCTL1.FILTER_SE0_FSLS_EOP is set, then for device
 * LPM handshake, the controller will ignore single SE0 glitch on the
 * linestate during transmit. Only 2 or more SE0 is considered as a valid
 * EOP on FS.
 *
 * Host mode: FS/LS - If GUCTL1.FILTER_SE0_FSLS_EOP is set, then the
 * controller will ignore single SE0 glitch on the linestate during
 * transmit. Only 2 or more SE0 is considered as a valid EOP on FS/LS port.
 *
 * Enable this feature if the LineState has SE0 glitches during
 * transmission. This bit is quasi-static, that is, it must not be changed
 * during device operation.

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . FILTER_SE0_FSLS_EOP
 */
#define  VTSS_F_USB3_GUCTL1_FILTER_SE0_FSLS_EOP(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_USB3_GUCTL1_FILTER_SE0_FSLS_EOP  VTSS_BIT(29)
#define  VTSS_X_USB3_GUCTL1_FILTER_SE0_FSLS_EOP(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * DS_RXDET_MAX_TOUT_CTRL
 *
 * This bit is used to control the tRxDetectTimeoutDFP timer for the
 * SuperSpeed link.
 *  - 0: Default behavior; 12ms is used as tRxDetectTimeoutDFP.
 *  - 1: 120ms is used as the tRxDetectTimeoutDFP.
 * This bit is used only in host mode. For more details, refer to ECN020
 * for USB 3.0 Specification.

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . DS_RXDET_MAX_TOUT_CTRL
 */
#define  VTSS_F_USB3_GUCTL1_DS_RXDET_MAX_TOUT_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_USB3_GUCTL1_DS_RXDET_MAX_TOUT_CTRL  VTSS_BIT(30)
#define  VTSS_X_USB3_GUCTL1_DS_RXDET_MAX_TOUT_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * DEV_DECOUPLE_L1L2_EVT
 *  - 0: Default behavior, no change in device events L1/L2U3 events are
 * not decoupled (old behavior of v2.90a and before)
 *  - 1: Feature enabled, L1 and L2 events are separated when operating in
 * 2.0 mode. Separate event enable bits for L1 suspend and wake events.
 * This bit is applicable for device mode only. If this feature is enabled,
 * L1 suspend and wake events have individual controls to enable/mask them.
 * Enable this feature if you want to get L1 (LPM) events separtely and not
 * combined with L2 events when operating in 2.0 speeds.

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL1 . DEV_DECOUPLE_L1L2_EVT
 */
#define  VTSS_F_USB3_GUCTL1_DEV_DECOUPLE_L1L2_EVT(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_USB3_GUCTL1_DEV_DECOUPLE_L1L2_EVT  VTSS_BIT(31)
#define  VTSS_X_USB3_GUCTL1_DEV_DECOUPLE_L1L2_EVT(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief Global Synopsys ID Register

This is a read-only register that contains the release number of the controller.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GSNPSID
 */
#define VTSS_USB3_GSNPSID                    VTSS_IOREG(VTSS_TO_USB3,0x3048)

/**
 * \brief
 * Synopsys ID
 *  - SynopsysID[31:16] indicates Core Identification Number. 0x5533 is
 * ASCII for U3 (DWC_usb3).
 *  - SynopsysID[15:0] indicates the release number. Current Release is
 * 3.30a.
 * Software uses this register to configure release-specific features in
 * the driver.
 *
 * \details
 * Field: ::VTSS_USB3_GSNPSID . SYNOPSYSID
 */
#define  VTSS_F_USB3_GSNPSID_SYNOPSYSID(x)    (x)
#define  VTSS_M_USB3_GSNPSID_SYNOPSYSID       0xffffffff
#define  VTSS_X_USB3_GSNPSID_SYNOPSYSID(x)    (x)


/**
 * \brief Global General Purpose Input/Output Register

The application can use this register for general purpose input and output ports or for debugging.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GGPIO
 */
#define VTSS_USB3_GGPIO                      VTSS_IOREG(VTSS_TO_USB3,0x3049)

/**
 * \brief
 * General Purpose Input
 *
 * The read value of this field reflects the gp_in[15:0] input signal
 * value.
 *
 * Note: Register bit-bash test should not check for reset value of this
 * field since its not predictable; depends on the gp_in port.
 *
 * \details
 * Field: ::VTSS_USB3_GGPIO . GPI
 */
#define  VTSS_F_USB3_GGPIO_GPI(x)             VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_USB3_GGPIO_GPI                VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_USB3_GGPIO_GPI(x)             VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * General Purpose Output
 *
 * The value of this field is driven out on the gp_out[15:0] output port.
 *
 * \details
 * Field: ::VTSS_USB3_GGPIO . GPO
 */
#define  VTSS_F_USB3_GGPIO_GPO(x)             VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_GGPIO_GPO                VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_GGPIO_GPO(x)             VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Global User ID Register

This is a read/write register containing the User ID. The power-on value for this register is specified as the User Identification Register. Power-on value during coreConsultant configuration (parameter DWC_USB3_USERID). This register can be used in the following ways:
 - To store the version or revision of your system;
 - To store hardware configurations that are outside the controller;
 - As a scratch register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GUID
 */
#define VTSS_USB3_GUID                       VTSS_IOREG(VTSS_TO_USB3,0x304a)

/**
 * \brief
 * USERID
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GUID . USERID
 */
#define  VTSS_F_USB3_GUID_USERID(x)           (x)
#define  VTSS_M_USB3_GUID_USERID              0xffffffff
#define  VTSS_X_USB3_GUID_USERID(x)           (x)


/**
 * \brief Global User Control Register:

This register provides a few options for the software to control the controller behavior in the Host mode. Most of the options are used to improve host inter-operability with different devices.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GUCTL
 */
#define VTSS_USB3_GUCTL                      VTSS_IOREG(VTSS_TO_USB3,0x304b)

/**
 * \brief
 * Device Timeout Fine Tuning (DTFT)
 *
 * This field is a Host mode parameter which determines how long the host
 * waits for a response from device before considering a timeout.
 *
 * For the DTFT field to take effect, DTCT must be set to 2'b00.
 *
 * The DTFT value is the number of 125 MHz clocks * 256 to count before
 * considering a device timeout.
 *
 * The minimum value of DTFT is 2.
 *
 * For example, if the mac3_clk is 125 MHz clk (8 ns period), this is
 * calculated as follows:
 *
 * (DTFT value) * 256 * (8 ns)
 *
 * Quick Reference:
 *  - if DTFT = 0x2, 2*256*8 = 4usec timeout
 *  - if DTFT = 0x5, 5*256*8 = 10usec timeout
 *  - if DTFT = 0xA, 10*256*8 = 20usec timeout
 *  - if DTFT = 0x10, 16*256*8 = 32usec timeout
 *  - if DTFT = 0x19, 25*256*8 = 51usec timeout
 *  - if DTFT = 0x31, 49*256*8 = 100usec timeout
 *  - if DTFT = 0x62, 98*256*8 = 200usec timeout
 * Note:
 * When the system latency is larger than the programmed DTCT/DTFT value,
 * if the host controller is not able to accept certain transactions on the
 * bus (because of system bus delays), the controller may not release
 * header credits which in turn can cause the host to report a transaction
 * error. Therefore, program this value to be larger than your system
 * delay.
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL . DTFT
 */
#define  VTSS_F_USB3_GUCTL_DTFT(x)            VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_USB3_GUCTL_DTFT               VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_USB3_GUCTL_DTFT(x)            VTSS_EXTRACT_BITFIELD(x,0,9)

/**
 * \brief
 * Device Timeout Coarse Tuning (DTCT)
 *
 * This field is a Host mode parameter which determines how long the host
 * waits for a response from device before considering a timeout.
 *
 * The controller first checks the DTCT value. If it is 0, then the timeout
 * value is defined by the DTFT. If it is non-zero, then it uses the
 * following timeout values:
 *  - 2'b00: 0 usec -> use DTFT value instead
 *  - 2'b01: 500 usec
 *  - 2'b10: 1.5 msec
 *  - 2'b11: 6.5 msec
 * Note: When the system latency is larger than the programmed DTCT/DTFT
 * value, if the host controller is not able to accept certain transactions
 * on the bus (because of system bus delays), the controller may not
 * release header credits which in turn can cause the host to report a
 * transaction error. Therefore, program this value to be larger than your
 * system delay.
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL . DTCT
 */
#define  VTSS_F_USB3_GUCTL_DTCT(x)            VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_USB3_GUCTL_DTCT               VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_USB3_GUCTL_DTCT(x)            VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * Insert Extra Delay Between FS Bulk OUT Transactions (InsrtExtrFSBODl).
 *
 * Some FS devices are slow to receive Bulk OUT data and can get stuck when
 * there are consecutive Bulk OUT transactions with short inter-transaction
 * delays. This bit is used to control whether the host inserts extra delay
 * between consecutive Bulk OUT transactions to a FS Endpoint.
 *  - 1'b0: Host doesn't insert extra delay between consecutive Bulk OUT
 * transactions to a FS Endpoint.
 *  - 1'b1: Host inserts about 12us extra delay between consecutive Bulk
 * OUT transactions to a FS Endpoint to work around the device issue.
 * Note: Setting this bit to one will reduce the Bulk OUT transfer
 * performance for most of the FS devices.

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL . INSRTEXTRFSBODI
 */
#define  VTSS_F_USB3_GUCTL_INSRTEXTRFSBODI(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_USB3_GUCTL_INSRTEXTRFSBODI    VTSS_BIT(11)
#define  VTSS_X_USB3_GUCTL_INSRTEXTRFSBODI(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * External Extended Capability Support Enable (ExtCapSuptEN)
 *
 * When set, this field enables extended capabilities to be implemented
 * outside the controller.
 *
 * When the ExtCapSupEN is set and the Debug Capability is enabled, the
 * Next Capability pointer in "Debug Capability" returns 16.
 *
 * A read to the first DWORD of the last internal extended capability (the
 * "xHCI Supported Protocol Capability for USB 3.0" when the Debug
 * Capability is not enabled) returns a value of 4 in the Next Capability
 * Pointer field.
 *
 * This indicates to software that there is another capability four DWORDs
 * after this capability (for example, at address N+16 where N is the
 * address of this DWORD).
 * If enabled, an external address decoder that snoops the xHC slave
 * interface must be implemented.   If it sees an access to N+16 or
 * greater, the slave access is re-routed to a piece of hardware which
 * returns the external capability pointer register of the new capability
 * and also handles reads/writes to this new capability and the side
 * effects.
 *
 * If disabled, a read to the first DWORD of the last internal extended
 * capability returns 0 in the 'Next Capability Pointer field. This
 * indicates there are no more capabilities.

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL . EXTCAPSUPPTEN
 */
#define  VTSS_F_USB3_GUCTL_EXTCAPSUPPTEN(x)   VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_USB3_GUCTL_EXTCAPSUPPTEN      VTSS_BIT(12)
#define  VTSS_X_USB3_GUCTL_EXTCAPSUPPTEN(x)   VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Enable Check for LFPS Overlap During Remote Ux Exit:
 *
 * If this bit is set to,
 *  - 1'b1: The SuperSpeed link when exiting U1/U2/U3 waits for either the
 * remote link LFPS or TS1/TS2 training symbols before it confirms that the
 * LFPS handshake is complete. This is done to handle the case where the
 * LFPS glitch causes the link to start exiting from the low power state.
 * Looking for the LFPS overlap makes sure that the link partner also sees
 * the LFPS.
 *  - 1'b0: When the link exists U1/U2/U3 because of a remote exit, it does
 * not look for an LFPS overlap.
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL . ENOVERLAPCHK
 */
#define  VTSS_F_USB3_GUCTL_ENOVERLAPCHK(x)    VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_USB3_GUCTL_ENOVERLAPCHK       VTSS_BIT(13)
#define  VTSS_X_USB3_GUCTL_ENOVERLAPCHK(x)    VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Host IN Auto Retry (USBHstInAutoRetryEn)
 *
 * When set, this field enables the Auto Retry feature. For IN transfers
 * (non-isochronous) that encounter data packets with CRC errors or
 * internal overrun scenarios, the auto retry feature causes the Host
 * controller to reply to the device with a non-terminating retry ACK (that
 * is, an ACK transaction packet with Retry = 1 and NumP != 0).
 *
 * If the Auto Retry feature is disabled (default), the controller will
 * respond with a terminating retry ACK (that is, an ACK transaction packet
 * with Retry = 1 and NumP = 0).
 *  - 1'b0: Auto Retry Disabled
 *  - 1'b1: Auto Retry Enabled
 * Note: When enabling Auto Retry feature, if the system latency is large
 * enough to cause the internal PSQ full (PSQ can be full as the result of
 * messages not being processed because of pending fetches before flushing
 * the TxQ due to NRDY/ERDY conditions), then the host controller can
 * generate a transaction error.

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL . USBHSTINAUTORETRYEN
 */
#define  VTSS_F_USB3_GUCTL_USBHSTINAUTORETRYEN(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_USB3_GUCTL_USBHSTINAUTORETRYEN  VTSS_BIT(14)
#define  VTSS_X_USB3_GUCTL_USBHSTINAUTORETRYEN(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL . GUCTL_RESERVED_15
 */
#define  VTSS_F_USB3_GUCTL_GUCTL_RESERVED_15(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_USB3_GUCTL_GUCTL_RESERVED_15  VTSS_BIT(15)
#define  VTSS_X_USB3_GUCTL_GUCTL_RESERVED_15(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Reserving 85% Bandwidth for HS Periodic EPs (ResBwHSEPS)
 *
 * By default, HC reserves 80% of the bandwidth for periodic EPs. If this
 * bit is set, the bandwidth is relaxed to 85% to accommodate two high
 * speed, high bandwidth ISOC EPs.
 *
 * USB 2.0 required 80% bandwidth allocated for ISOC traffic. If two
 * High-bandwidth ISOC devices (HD Webcams) are connected, and if each
 * requires 1024-bytes X 3 packets per Micro-Frame, then the bandwidth
 * required is around 82%. If this bit is set, then it is possible to
 * connect two Webcams of 1024bytes X 3 paylod per Micro-Frame each.
 * Otherwise, you may have to reduce the resolution of the Webcams.
 *
 * This bit is valid in Host and DRD configuration and is used in host mode
 * operation only. Ignore this bit in device mode.
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL . RESBWHSEPS
 */
#define  VTSS_F_USB3_GUCTL_RESBWHSEPS(x)      VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_USB3_GUCTL_RESBWHSEPS         VTSS_BIT(16)
#define  VTSS_X_USB3_GUCTL_RESBWHSEPS(x)      VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Sparse Control Transaction Enable
 *
 * Some devices are slow in responding to Control transfers. Scheduling
 * multiple transactions in one microframe/frame can cause these devices to
 * misbehave.
 *
 * If this bit is set to 1'b1, the host controller schedules transactions
 * for a Control transfer in different microframes/frames.

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL . SPRSCTRLTRANSEN
 */
#define  VTSS_F_USB3_GUCTL_SPRSCTRLTRANSEN(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_USB3_GUCTL_SPRSCTRLTRANSEN    VTSS_BIT(17)
#define  VTSS_X_USB3_GUCTL_SPRSCTRLTRANSEN(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL . RESERVED_20_18
 */
#define  VTSS_F_USB3_GUCTL_RESERVED_20_18(x)  VTSS_ENCODE_BITFIELD(x,18,3)
#define  VTSS_M_USB3_GUCTL_RESERVED_20_18     VTSS_ENCODE_BITMASK(18,3)
#define  VTSS_X_USB3_GUCTL_RESERVED_20_18(x)  VTSS_EXTRACT_BITFIELD(x,18,3)

/**
 * \brief
 * No Extra Delay Between SOF and the First Packet(NoExtrDl)
 *
 * Some HS devices misbehave when the host sends a packet immediately after
 * a SOF. However, adding an extra delay between a SOF and the first packet
 * can reduce the USB data rate and performance.
 *
 * This bit is used to control whether the host must wait for 2
 * microseconds before it sends the first packet after a SOF, or not. User
 * can set this bit to one to improve the performance if those problematic
 * devices are not a concern in the user's host environment.
 *  - 1'b0: Host waits for 2 microseconds after a SOF before it sends the
 * first USB packet.
 *  - 1'b1: Host doesn't wait after a SOF before it sends the first USB
 * packet.
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL . NOEXTRDL
 */
#define  VTSS_F_USB3_GUCTL_NOEXTRDL(x)        VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_USB3_GUCTL_NOEXTRDL           VTSS_BIT(21)
#define  VTSS_X_USB3_GUCTL_NOEXTRDL(x)        VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * REFCLKPER
 *
 * This field indicates in terms of nano seconds the period of ref_clk. The
 * default value of this register is set to 'h8 (8ns/125 MHz).
 *
 * This field needs to be updated during power-on initialization, if
 * GCTL.SOFITPSYNC or GFLADJ.GFLADJ_REFCLK_LPM_SEL is set to '1'. The
 * programmable maximum value is 62ns, and the minimum value is 8ns.
 *
 * You must use a reference clock with a period that is an integer
 * multiple, so that ITP can meet the jitter margin of 32ns. The allowable
 * ref_clk frequencies whose period is not integer multiples are
 * 16/17/19.2/24/39.7MHz.
 *
 * This field must not be set to '0' at any time. If you never plan to use
 * this feature, then set this field to 'h8, the default value.
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL . REFCLKPER
 */
#define  VTSS_F_USB3_GUCTL_REFCLKPER(x)       VTSS_ENCODE_BITFIELD(x,22,10)
#define  VTSS_M_USB3_GUCTL_REFCLKPER          VTSS_ENCODE_BITMASK(22,10)
#define  VTSS_X_USB3_GUCTL_REFCLKPER(x)       VTSS_EXTRACT_BITFIELD(x,22,10)


/**
 * \brief Gobal SoC Bus Error Address Register - Low

This is an alternate register for the GBUSERRADDR register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GBUSERRADDRLO
 */
#define VTSS_USB3_GBUSERRADDRLO              VTSS_IOREG(VTSS_TO_USB3,0x304c)

/**
 * \brief
 * Bus Address - Low (BusAddrLo)
 * This register contains the lower 32 bits of the first bus address that
 * encountered a SoC bus error. It is valid when the GSTS.BusErrAddrVld
 * field is 1.
 * It can only be cleared by resetting the controller.
 *
 * Note: Only supported in AHB and AXI configurations.
 *
 * \details
 * Field: ::VTSS_USB3_GBUSERRADDRLO . GBUSERRADDRLO_BUSERRADDR
 */
#define  VTSS_F_USB3_GBUSERRADDRLO_GBUSERRADDRLO_BUSERRADDR(x)  (x)
#define  VTSS_M_USB3_GBUSERRADDRLO_GBUSERRADDRLO_BUSERRADDR     0xffffffff
#define  VTSS_X_USB3_GBUSERRADDRLO_GBUSERRADDRLO_BUSERRADDR(x)  (x)


/**
 * \brief Gobal SoC Bus Error Address Register - High

This is an alternate register for the GBUSERRADDR register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GBUSERRADDRHI
 */
#define VTSS_USB3_GBUSERRADDRHI              VTSS_IOREG(VTSS_TO_USB3,0x304d)

/**
 * \brief
 * Bus Address - High (BusAddrHi)
 * This register contains the higher 32 bits of the first bus address that
 * encountered a SoC bus error. It is valid when the GSTS.BusErrAddrVld
 * field is 1.
 * It can only be cleared by resetting the controller.
 *
 * Note: Only supported in AHB and AXI configurations.
 *
 * \details
 * Field: ::VTSS_USB3_GBUSERRADDRHI . GBUSERRADDRHI_BUSERRADDR
 */
#define  VTSS_F_USB3_GBUSERRADDRHI_GBUSERRADDRHI_BUSERRADDR(x)  (x)
#define  VTSS_M_USB3_GBUSERRADDRHI_GBUSERRADDRHI_BUSERRADDR     0xffffffff
#define  VTSS_X_USB3_GBUSERRADDRHI_GBUSERRADDRHI_BUSERRADDR(x)  (x)


/**
 * \brief Global SS Port to Bus Instance Mapping Register - Low

This is an alternate register for the GPRTBIMAP register.

Register fields are read-write with respect to number of port instantiated. writeAsRead constraint is added to limit side effects for unused fields.

For a configuration with number of USB 3.0 ports same as number of SS Bus Instances, do not remap during debug session. If you remap for some reason, then the debug host must be connected to a port which has a dedicated SS Bus Instance.

For example, if DWC_USB3_NUM_U3_ROOT_PORTS =3 and DWC_USB3_NUM_SS_USB_INSTANCES=3, and software maps the first SS port to the first SS BI and the second/third port to the second BI, then the debug host can be connected to the first port only.

Note: For reset values, refer to the corresponding values in the GPRTBIMAP register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GPRTBIMAPLO
 */
#define VTSS_USB3_GPRTBIMAPLO                VTSS_IOREG(VTSS_TO_USB3,0x304e)

/**
 * \brief
 * BINUM1: SS USB Instance Number for Port 1.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAPLO . GPRTBIMAPLO_BINUM1
 */
#define  VTSS_F_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * BINUM2: SS USB Instance Number for Port 2.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAPLO . GPRTBIMAPLO_BINUM2
 */
#define  VTSS_F_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM2(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM2     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM2(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * BINUM3: SS USB Instance Number for Port 3.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAPLO . GPRTBIMAPLO_BINUM3
 */
#define  VTSS_F_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM3(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM3     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM3(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * BINUM4: SS USB Instance Number for Port 4.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAPLO . GPRTBIMAPLO_BINUM4
 */
#define  VTSS_F_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM4(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM4     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM4(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * BINUM5: SS USB Instance Number for Port 5.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAPLO . GPRTBIMAPLO_BINUM5
 */
#define  VTSS_F_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM5(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM5     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM5(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * BINUM6: SS USB Instance Number for Port 6.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAPLO . GPRTBIMAPLO_BINUM6
 */
#define  VTSS_F_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM6(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM6     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM6(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * BINUM7: SS USB Instance Number for Port 7.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAPLO . GPRTBIMAPLO_BINUM7
 */
#define  VTSS_F_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM7(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM7     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM7(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * BINUM8: SS USB Instance Number for Port 8.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAPLO . GPRTBIMAPLO_BINUM8
 */
#define  VTSS_F_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM8(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM8     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_USB3_GPRTBIMAPLO_GPRTBIMAPLO_BINUM8(x)  VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief Global SS Port to Bus Instance Mapping Register - High

This is an alternate register for the GPRTBIMAP register.

For a configuration with number of USB 3.0 ports same as number of SS Bus Instances, do not remap during debug session. If you remap for some reason, then the debug host must be connected to a port which has a dedicated SS Bus Instance.

For example, if DWC_USB3_NUM_U3_ROOT_PORTS =3 and DWC_USB3_NUM_SS_USB_INSTANCES=3, and software maps the first SS port to the first SS BI and the second/third port to the second BI, then the debug host can be connected to the first port only.

Note: For reset values, refer to the corresponding values in the GPRTBIMAP register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GPRTBIMAPHI
 */
#define VTSS_USB3_GPRTBIMAPHI                VTSS_IOREG(VTSS_TO_USB3,0x304f)

/**
 * \brief
 * BINUM9: SS USB Instance Number for Port 9.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAPHI . GPRTBIMAPHI_BINUM9
 */
#define  VTSS_F_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM9(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM9     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM9(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * BINUM10: SS USB Instance Number for Port 10.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAPHI . GPRTBIMAPHI_BINUM10
 */
#define  VTSS_F_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM10(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM10     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM10(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * BINUM11: SS USB Instance Number for Port 11.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAPHI . GPRTBIMAPHI_BINUM11
 */
#define  VTSS_F_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM11(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM11     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM11(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * BINUM12: SS USB Instance Number for Port 12.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAPHI . GPRTBIMAPHI_BINUM12
 */
#define  VTSS_F_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM12(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM12     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM12(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * BINUM13: SS USB Instance Number for Port 13.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAPHI . GPRTBIMAPHI_BINUM13
 */
#define  VTSS_F_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM13(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM13     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM13(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * BINUM14: SS USB Instance Number for Port 14.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAPHI . GPRTBIMAPHI_BINUM14
 */
#define  VTSS_F_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM14(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM14     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM14(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * BINUM15: SS USB Instance Number for Port 15.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAPHI . GPRTBIMAPHI_BINUM15
 */
#define  VTSS_F_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM15(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM15     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_USB3_GPRTBIMAPHI_GPRTBIMAPHI_BINUM15(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAPHI . GPRTBIMAPHI_RESERVED_31_28
 */
#define  VTSS_F_USB3_GPRTBIMAPHI_GPRTBIMAPHI_RESERVED_31_28(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_USB3_GPRTBIMAPHI_GPRTBIMAPHI_RESERVED_31_28     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_USB3_GPRTBIMAPHI_GPRTBIMAPHI_RESERVED_31_28(x)  VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief Global Hardware Parameters Register 0

This register contains the hardware configuration options that you can select in the coreConsultant GUI.

For a description of each parameter, refer to the "Parameter Descriptions" chapter in the Databook. This information is also available in coreConsultant by right-clicking the parameter label and selecting "What's This" or by clicking the Help tab.

Note:

Some of the global hardware parameters are not currently modifiable in coreConsultant. These settings are in the  <workspace>/src/DWC_usb3_params.v file; you must not change them.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GHWPARAMS0
 */
#define VTSS_USB3_GHWPARAMS0                 VTSS_IOREG(VTSS_TO_USB3,0x3050)

/**
 * \brief
 * `DWC_USB3_MODE
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS0 . GHWPARAMS0_2_0
 */
#define  VTSS_F_USB3_GHWPARAMS0_GHWPARAMS0_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_USB3_GHWPARAMS0_GHWPARAMS0_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_USB3_GHWPARAMS0_GHWPARAMS0_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * `DWC_USB3_MBUS_TYPE
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS0 . GHWPARAMS0_5_3
 */
#define  VTSS_F_USB3_GHWPARAMS0_GHWPARAMS0_5_3(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_USB3_GHWPARAMS0_GHWPARAMS0_5_3     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_USB3_GHWPARAMS0_GHWPARAMS0_5_3(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * `DWC_USB3_SBUS_TYPE
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS0 . GHWPARAMS0_7_6
 */
#define  VTSS_F_USB3_GHWPARAMS0_GHWPARAMS0_7_6(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_USB3_GHWPARAMS0_GHWPARAMS0_7_6     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_USB3_GHWPARAMS0_GHWPARAMS0_7_6(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/**
 * \brief
 * `DWC_USB3_MDWIDTH
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS0 . GHWPARAMS0_15_8
 */
#define  VTSS_F_USB3_GHWPARAMS0_GHWPARAMS0_15_8(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_USB3_GHWPARAMS0_GHWPARAMS0_15_8     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_USB3_GHWPARAMS0_GHWPARAMS0_15_8(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * `DWC_USB3_SDWIDTH
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS0 . GHWPARAMS0_23_16
 */
#define  VTSS_F_USB3_GHWPARAMS0_GHWPARAMS0_23_16(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_USB3_GHWPARAMS0_GHWPARAMS0_23_16     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_USB3_GHWPARAMS0_GHWPARAMS0_23_16(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * `DWC_USB3_AWIDTH
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS0 . GHWPARAMS0_31_24
 */
#define  VTSS_F_USB3_GHWPARAMS0_GHWPARAMS0_31_24(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_USB3_GHWPARAMS0_GHWPARAMS0_31_24     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_USB3_GHWPARAMS0_GHWPARAMS0_31_24(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief Global Hardware Parameters Register 1

This register contains the hardware configuration options that you can select in the coreConsultant GUI.

For a description of each parameter, refer to the "Parameter Descriptions" chapter in the Databook. This information is also available in coreConsultant by right-clicking the parameter label and selecting "What's This" or by clicking the Help tab.

Note:

Some of the global hardware parameters are not currently modifiable in coreConsultant. These settings are in the  <workspace>/src/DWC_usb3_params.v file; you must not change them.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GHWPARAMS1
 */
#define VTSS_USB3_GHWPARAMS1                 VTSS_IOREG(VTSS_TO_USB3,0x3051)

/**
 * \brief
 * `DWC_USB3_IDWIDTH-1
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS1 . GHWPARAMS1_2_0
 */
#define  VTSS_F_USB3_GHWPARAMS1_GHWPARAMS1_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_USB3_GHWPARAMS1_GHWPARAMS1_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_USB3_GHWPARAMS1_GHWPARAMS1_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * `DWC_USB3_BURSTWIDTH-1
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS1 . GHWPARAMS1_5_3
 */
#define  VTSS_F_USB3_GHWPARAMS1_GHWPARAMS1_5_3(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_USB3_GHWPARAMS1_GHWPARAMS1_5_3     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_USB3_GHWPARAMS1_GHWPARAMS1_5_3(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * `DWC_USB3_DATAINFOWIDTH
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS1 . GHWPARAMS1_8_6
 */
#define  VTSS_F_USB3_GHWPARAMS1_GHWPARAMS1_8_6(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_USB3_GHWPARAMS1_GHWPARAMS1_8_6     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_USB3_GHWPARAMS1_GHWPARAMS1_8_6(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \brief
 * `DWC_USB3_REQINFOWIDTH
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS1 . GHWPARAMS1_11_9
 */
#define  VTSS_F_USB3_GHWPARAMS1_GHWPARAMS1_11_9(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_USB3_GHWPARAMS1_GHWPARAMS1_11_9     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_USB3_GHWPARAMS1_GHWPARAMS1_11_9(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * `DWC_USB3_ASPACEWIDTH
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS1 . GHWPARAMS1_14_12
 */
#define  VTSS_F_USB3_GHWPARAMS1_GHWPARAMS1_14_12(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_USB3_GHWPARAMS1_GHWPARAMS1_14_12     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_USB3_GHWPARAMS1_GHWPARAMS1_14_12(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * `DWC_USB3_DEVICE_NUM_INT
 *
 * For details on `DWC_USB3_DEVICE_NUM_INT, refer to
 * <workspace>/src/DWC_usb3_params.v file.
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS1 . GHWPARAMS1_20_15
 */
#define  VTSS_F_USB3_GHWPARAMS1_GHWPARAMS1_20_15(x)  VTSS_ENCODE_BITFIELD(x,15,6)
#define  VTSS_M_USB3_GHWPARAMS1_GHWPARAMS1_20_15     VTSS_ENCODE_BITMASK(15,6)
#define  VTSS_X_USB3_GHWPARAMS1_GHWPARAMS1_20_15(x)  VTSS_EXTRACT_BITFIELD(x,15,6)

/**
 * \brief
 * `DWC_USB3_NUM_RAMS
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS1 . GHWPARAMS1_22_21
 */
#define  VTSS_F_USB3_GHWPARAMS1_GHWPARAMS1_22_21(x)  VTSS_ENCODE_BITFIELD(x,21,2)
#define  VTSS_M_USB3_GHWPARAMS1_GHWPARAMS1_22_21     VTSS_ENCODE_BITMASK(21,2)
#define  VTSS_X_USB3_GHWPARAMS1_GHWPARAMS1_22_21(x)  VTSS_EXTRACT_BITFIELD(x,21,2)

/**
 * \brief
 * `DWC_USB3_SPRAM_TYP
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS1 . GHWPARAMS1_23
 */
#define  VTSS_F_USB3_GHWPARAMS1_GHWPARAMS1_23(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_USB3_GHWPARAMS1_GHWPARAMS1_23  VTSS_BIT(23)
#define  VTSS_X_USB3_GHWPARAMS1_GHWPARAMS1_23(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * `DWC_USB3_EN_PWROPT
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS1 . GHWPARAMS1_25_24
 */
#define  VTSS_F_USB3_GHWPARAMS1_GHWPARAMS1_25_24(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_USB3_GHWPARAMS1_GHWPARAMS1_25_24     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_USB3_GHWPARAMS1_GHWPARAMS1_25_24(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * `DWC_USB3_MAC_PHY_CLKS_SYNC
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS1 . GHWPARAMS1_26
 */
#define  VTSS_F_USB3_GHWPARAMS1_GHWPARAMS1_26(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_USB3_GHWPARAMS1_GHWPARAMS1_26  VTSS_BIT(26)
#define  VTSS_X_USB3_GHWPARAMS1_GHWPARAMS1_26(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * `DWC_USB3_MAC_RAM_CLKS_SYNC
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS1 . GHWPARAMS1_27
 */
#define  VTSS_F_USB3_GHWPARAMS1_GHWPARAMS1_27(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_USB3_GHWPARAMS1_GHWPARAMS1_27  VTSS_BIT(27)
#define  VTSS_X_USB3_GHWPARAMS1_GHWPARAMS1_27(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * `DWC_USB3_RAM_BUS_CLKS_SYNC
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS1 . GHWPARAMS1_28
 */
#define  VTSS_F_USB3_GHWPARAMS1_GHWPARAMS1_28(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_USB3_GHWPARAMS1_GHWPARAMS1_28  VTSS_BIT(28)
#define  VTSS_X_USB3_GHWPARAMS1_GHWPARAMS1_28(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Reserved1
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS1 . GHWPARAMS1_29
 */
#define  VTSS_F_USB3_GHWPARAMS1_GHWPARAMS1_29(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_USB3_GHWPARAMS1_GHWPARAMS1_29  VTSS_BIT(29)
#define  VTSS_X_USB3_GHWPARAMS1_GHWPARAMS1_29(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * `DWC_USB3_RM_OPT_FEATURES
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS1 . GHWPARAMS1_30
 */
#define  VTSS_F_USB3_GHWPARAMS1_GHWPARAMS1_30(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_USB3_GHWPARAMS1_GHWPARAMS1_30  VTSS_BIT(30)
#define  VTSS_X_USB3_GHWPARAMS1_GHWPARAMS1_30(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * `DWC_USB3_EN_DBC
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS1 . GHWPARAMS1_31
 */
#define  VTSS_F_USB3_GHWPARAMS1_GHWPARAMS1_31(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_USB3_GHWPARAMS1_GHWPARAMS1_31  VTSS_BIT(31)
#define  VTSS_X_USB3_GHWPARAMS1_GHWPARAMS1_31(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief Global Hardware Parameters Register 2

This register contains the hardware configuration options that you can select in the coreConsultant GUI.

For a description of each parameter, refer to the "Parameter Descriptions" chapter in the Databook. This information is also available in coreConsultant by right-clicking the parameter label and selecting "What's This" or by clicking the Help tab.

Note:

Some of the global hardware parameters are not currently modifiable in coreConsultant. These settings are in the  <workspace>/src/DWC_usb3_params.v file; you must not change them.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GHWPARAMS2
 */
#define VTSS_USB3_GHWPARAMS2                 VTSS_IOREG(VTSS_TO_USB3,0x3052)

/**
 * \brief
 * `DWC_USB3_USERID
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS2 . GHWPARAMS2_31_0
 */
#define  VTSS_F_USB3_GHWPARAMS2_GHWPARAMS2_31_0(x)  (x)
#define  VTSS_M_USB3_GHWPARAMS2_GHWPARAMS2_31_0     0xffffffff
#define  VTSS_X_USB3_GHWPARAMS2_GHWPARAMS2_31_0(x)  (x)


/**
 * \brief Global Hardware Parameters Register 3

This register contains the hardware configuration options that you can select in the coreConsultant GUI.

For a description of each parameter, refer to the "Parameter Descriptions" chapter in the Databook. This information is also available in coreConsultant by right-clicking the parameter label and selecting "What's This" or by clicking the Help tab.

Note:

Some of the global hardware parameters are not currently modifiable in coreConsultant. These settings are in the  <workspace>/src/DWC_usb3_params.v file; you must not change them.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GHWPARAMS3
 */
#define VTSS_USB3_GHWPARAMS3                 VTSS_IOREG(VTSS_TO_USB3,0x3053)

/**
 * \brief
 * `DWC_USB3_SSPHY_INTERFACE
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS3 . GHWPARAMS3_1_0
 */
#define  VTSS_F_USB3_GHWPARAMS3_GHWPARAMS3_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_USB3_GHWPARAMS3_GHWPARAMS3_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_USB3_GHWPARAMS3_GHWPARAMS3_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * `DWC_USB3_HSPHY_INTERFACE
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS3 . GHWPARAMS3_3_2
 */
#define  VTSS_F_USB3_GHWPARAMS3_GHWPARAMS3_3_2(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_USB3_GHWPARAMS3_GHWPARAMS3_3_2     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_USB3_GHWPARAMS3_GHWPARAMS3_3_2(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * `DWC_USB3_FSPHY_INTERFACE
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS3 . GHWPARAMS3_5_4
 */
#define  VTSS_F_USB3_GHWPARAMS3_GHWPARAMS3_5_4(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_USB3_GHWPARAMS3_GHWPARAMS3_5_4     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_USB3_GHWPARAMS3_GHWPARAMS3_5_4(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * `DWC_USB3_HSPHY_DWIDTH
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS3 . GHWPARAMS3_7_6
 */
#define  VTSS_F_USB3_GHWPARAMS3_GHWPARAMS3_7_6(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_USB3_GHWPARAMS3_GHWPARAMS3_7_6     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_USB3_GHWPARAMS3_GHWPARAMS3_7_6(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS3 . GHWPARAMS3_9_8
 */
#define  VTSS_F_USB3_GHWPARAMS3_GHWPARAMS3_9_8(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_USB3_GHWPARAMS3_GHWPARAMS3_9_8     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_USB3_GHWPARAMS3_GHWPARAMS3_9_8(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * `DWC_USB3_VENDOR_CTL_INTERFACE
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS3 . GHWPARAMS3_10
 */
#define  VTSS_F_USB3_GHWPARAMS3_GHWPARAMS3_10(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_USB3_GHWPARAMS3_GHWPARAMS3_10  VTSS_BIT(10)
#define  VTSS_X_USB3_GHWPARAMS3_GHWPARAMS3_10(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * `DWC_USB3_ULPI_CARKIT
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS3 . GHWPARAMS3_11
 */
#define  VTSS_F_USB3_GHWPARAMS3_GHWPARAMS3_11(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_USB3_GHWPARAMS3_GHWPARAMS3_11  VTSS_BIT(11)
#define  VTSS_X_USB3_GHWPARAMS3_GHWPARAMS3_11(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * `DWC_USB3_NUM_EPS
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS3 . GHWPARAMS3_17_12
 */
#define  VTSS_F_USB3_GHWPARAMS3_GHWPARAMS3_17_12(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_USB3_GHWPARAMS3_GHWPARAMS3_17_12     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_USB3_GHWPARAMS3_GHWPARAMS3_17_12(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/**
 * \brief
 * `DWC_USB3_NUM_IN_EPS
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS3 . GHWPARAMS3_22_18
 */
#define  VTSS_F_USB3_GHWPARAMS3_GHWPARAMS3_22_18(x)  VTSS_ENCODE_BITFIELD(x,18,5)
#define  VTSS_M_USB3_GHWPARAMS3_GHWPARAMS3_22_18     VTSS_ENCODE_BITMASK(18,5)
#define  VTSS_X_USB3_GHWPARAMS3_GHWPARAMS3_22_18(x)  VTSS_EXTRACT_BITFIELD(x,18,5)

/**
 * \brief
 * `DWC_USB3_CACHE_TOTAL_XFER_RESOURCES
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS3 . GHWPARAMS3_30_23
 */
#define  VTSS_F_USB3_GHWPARAMS3_GHWPARAMS3_30_23(x)  VTSS_ENCODE_BITFIELD(x,23,8)
#define  VTSS_M_USB3_GHWPARAMS3_GHWPARAMS3_30_23     VTSS_ENCODE_BITMASK(23,8)
#define  VTSS_X_USB3_GHWPARAMS3_GHWPARAMS3_30_23(x)  VTSS_EXTRACT_BITFIELD(x,23,8)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS3 . GHWPARAMS3_31
 */
#define  VTSS_F_USB3_GHWPARAMS3_GHWPARAMS3_31(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_USB3_GHWPARAMS3_GHWPARAMS3_31  VTSS_BIT(31)
#define  VTSS_X_USB3_GHWPARAMS3_GHWPARAMS3_31(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief Global Hardware Parameters Register 4

This register contains the hardware configuration options that you can select in the coreConsultant GUI.

For a description of each parameter, refer to the "Parameter Descriptions" chapter in the Databook. This information is also available in coreConsultant by right-clicking the parameter label and selecting "What's This" or by clicking the Help tab.

Note:

Some of the global hardware parameters are not currently modifiable in coreConsultant. These settings are in the  <workspace>/src/DWC_usb3_params.v file; you must not change them.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GHWPARAMS4
 */
#define VTSS_USB3_GHWPARAMS4                 VTSS_IOREG(VTSS_TO_USB3,0x3054)

/**
 * \brief
 * `DWC_USB3_CACHE_TRBS_PER_TRANSFER
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS4 . GHWPARAMS4_5_0
 */
#define  VTSS_F_USB3_GHWPARAMS4_GHWPARAMS4_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_USB3_GHWPARAMS4_GHWPARAMS4_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_USB3_GHWPARAMS4_GHWPARAMS4_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS4 . GHWPARAMS4_6
 */
#define  VTSS_F_USB3_GHWPARAMS4_GHWPARAMS4_6(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_USB3_GHWPARAMS4_GHWPARAMS4_6  VTSS_BIT(6)
#define  VTSS_X_USB3_GHWPARAMS4_GHWPARAMS4_6(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS4 . GHWPARAMS4_8_7
 */
#define  VTSS_F_USB3_GHWPARAMS4_GHWPARAMS4_8_7(x)  VTSS_ENCODE_BITFIELD(x,7,2)
#define  VTSS_M_USB3_GHWPARAMS4_GHWPARAMS4_8_7     VTSS_ENCODE_BITMASK(7,2)
#define  VTSS_X_USB3_GHWPARAMS4_GHWPARAMS4_8_7(x)  VTSS_EXTRACT_BITFIELD(x,7,2)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS4 . GHWPARAMS4_10_9
 */
#define  VTSS_F_USB3_GHWPARAMS4_GHWPARAMS4_10_9(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_USB3_GHWPARAMS4_GHWPARAMS4_10_9     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_USB3_GHWPARAMS4_GHWPARAMS4_10_9(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS4 . GHWPARAMS4_11
 */
#define  VTSS_F_USB3_GHWPARAMS4_GHWPARAMS4_11(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_USB3_GHWPARAMS4_GHWPARAMS4_11  VTSS_BIT(11)
#define  VTSS_X_USB3_GHWPARAMS4_GHWPARAMS4_11(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS4 . GHWPARAMS4_12
 */
#define  VTSS_F_USB3_GHWPARAMS4_GHWPARAMS4_12(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_USB3_GHWPARAMS4_GHWPARAMS4_12  VTSS_BIT(12)
#define  VTSS_X_USB3_GHWPARAMS4_GHWPARAMS4_12(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * `DWC_USB3_HIBER_SCRATCHBUFS
 *
 * Number of external scratchpad buffers the controller requires to save
 * its internal state in the device mode. Each buffer is assumed to be 4KB.
 * The scratchpad buffer array must have this many buffer pointers.
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS4 . GHWPARAMS4_16_13
 */
#define  VTSS_F_USB3_GHWPARAMS4_GHWPARAMS4_16_13(x)  VTSS_ENCODE_BITFIELD(x,13,4)
#define  VTSS_M_USB3_GHWPARAMS4_GHWPARAMS4_16_13     VTSS_ENCODE_BITMASK(13,4)
#define  VTSS_X_USB3_GHWPARAMS4_GHWPARAMS4_16_13(x)  VTSS_EXTRACT_BITFIELD(x,13,4)

/**
 * \brief
 * `DWC_USB3_NUM_SS_USB_INSTANCES
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS4 . GHWPARAMS4_20_17
 */
#define  VTSS_F_USB3_GHWPARAMS4_GHWPARAMS4_20_17(x)  VTSS_ENCODE_BITFIELD(x,17,4)
#define  VTSS_M_USB3_GHWPARAMS4_GHWPARAMS4_20_17     VTSS_ENCODE_BITMASK(17,4)
#define  VTSS_X_USB3_GHWPARAMS4_GHWPARAMS4_20_17(x)  VTSS_EXTRACT_BITFIELD(x,17,4)

/**
 * \brief
 * `DWC_USB3_EXT_BUFF_CONTROL
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS4 . GHWPARAMS4_21
 */
#define  VTSS_F_USB3_GHWPARAMS4_GHWPARAMS4_21(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_USB3_GHWPARAMS4_GHWPARAMS4_21  VTSS_BIT(21)
#define  VTSS_X_USB3_GHWPARAMS4_GHWPARAMS4_21(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS4 . GHWPARAMS4_22
 */
#define  VTSS_F_USB3_GHWPARAMS4_GHWPARAMS4_22(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_USB3_GHWPARAMS4_GHWPARAMS4_22  VTSS_BIT(22)
#define  VTSS_X_USB3_GHWPARAMS4_GHWPARAMS4_22(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * `DWC_USB3_EN_ISOC_SUPT
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS4 . GHWPARAMS4_23
 */
#define  VTSS_F_USB3_GHWPARAMS4_GHWPARAMS4_23(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_USB3_GHWPARAMS4_GHWPARAMS4_23  VTSS_BIT(23)
#define  VTSS_X_USB3_GHWPARAMS4_GHWPARAMS4_23(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * `DWC_USB3_BMU_PTL_DEPTH-1
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS4 . GHWPARAMS4_27_24
 */
#define  VTSS_F_USB3_GHWPARAMS4_GHWPARAMS4_27_24(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_USB3_GHWPARAMS4_GHWPARAMS4_27_24     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_USB3_GHWPARAMS4_GHWPARAMS4_27_24(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * `DWC_USB3_BMU_LSP_DEPTH
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS4 . GHWPARAMS4_31_28
 */
#define  VTSS_F_USB3_GHWPARAMS4_GHWPARAMS4_31_28(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_USB3_GHWPARAMS4_GHWPARAMS4_31_28     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_USB3_GHWPARAMS4_GHWPARAMS4_31_28(x)  VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief Global Hardware Parameters Register 5

This register contains the hardware configuration options that you can select in the coreConsultant GUI.

For a description of each parameter, refer to the "Parameter Descriptions" chapter in the Databook. This information is also available in coreConsultant by right-clicking the parameter label and selecting "What's This" or by clicking the Help tab.

Note:

Some of the global hardware parameters are not currently modifiable in coreConsultant. These settings are in the  <workspace>/src/DWC_usb3_params.v file; you must not change them.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GHWPARAMS5
 */
#define VTSS_USB3_GHWPARAMS5                 VTSS_IOREG(VTSS_TO_USB3,0x3055)

/**
 * \brief
 * `DWC_USB3_BMU_BUSGM_DEPTH
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS5 . GHWPARAMS5_3_0
 */
#define  VTSS_F_USB3_GHWPARAMS5_GHWPARAMS5_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_USB3_GHWPARAMS5_GHWPARAMS5_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_USB3_GHWPARAMS5_GHWPARAMS5_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * `DWC_USB3_RXQ_FIFO_DEPTH
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS5 . GHWPARAMS5_9_4
 */
#define  VTSS_F_USB3_GHWPARAMS5_GHWPARAMS5_9_4(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_USB3_GHWPARAMS5_GHWPARAMS5_9_4     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_USB3_GHWPARAMS5_GHWPARAMS5_9_4(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/**
 * \brief
 * `DWC_USB3_TXQ_FIFO_DEPTH
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS5 . GHWPARAMS5_15_10
 */
#define  VTSS_F_USB3_GHWPARAMS5_GHWPARAMS5_15_10(x)  VTSS_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_USB3_GHWPARAMS5_GHWPARAMS5_15_10     VTSS_ENCODE_BITMASK(10,6)
#define  VTSS_X_USB3_GHWPARAMS5_GHWPARAMS5_15_10(x)  VTSS_EXTRACT_BITFIELD(x,10,6)

/**
 * \brief
 * `DWC_USB3_DWQ_FIFO_DEPTH
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS5 . GHWPARAMS5_21_16
 */
#define  VTSS_F_USB3_GHWPARAMS5_GHWPARAMS5_21_16(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_USB3_GHWPARAMS5_GHWPARAMS5_21_16     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_USB3_GHWPARAMS5_GHWPARAMS5_21_16(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * `DWC_USB3_DFQ_FIFO_DEPTH
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS5 . GHWPARAMS5_27_22
 */
#define  VTSS_F_USB3_GHWPARAMS5_GHWPARAMS5_27_22(x)  VTSS_ENCODE_BITFIELD(x,22,6)
#define  VTSS_M_USB3_GHWPARAMS5_GHWPARAMS5_27_22     VTSS_ENCODE_BITMASK(22,6)
#define  VTSS_X_USB3_GHWPARAMS5_GHWPARAMS5_27_22(x)  VTSS_EXTRACT_BITFIELD(x,22,6)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS5 . GHWPARAMS5_31_28
 */
#define  VTSS_F_USB3_GHWPARAMS5_GHWPARAMS5_31_28(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_USB3_GHWPARAMS5_GHWPARAMS5_31_28     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_USB3_GHWPARAMS5_GHWPARAMS5_31_28(x)  VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief Global Hardware Parameters Register 6

This register contains the hardware configuration options that you can select in the coreConsultant GUI.

For a description of each parameter, refer to the "Parameter Descriptions" chapter in the Databook. This information is also available in coreConsultant by right-clicking the parameter label and selecting "What's This" or by clicking the Help tab.

Note:

Some of the global hardware parameters are not currently modifiable in coreConsultant. These settings are in the  <workspace>/src/DWC_usb3_params.v file; you must not change them.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GHWPARAMS6
 */
#define VTSS_USB3_GHWPARAMS6                 VTSS_IOREG(VTSS_TO_USB3,0x3056)

/**
 * \brief
 * `DWC_USB3_PSQ_FIFO_DEPTH
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS6 . GHWPARAMS6_5_0
 */
#define  VTSS_F_USB3_GHWPARAMS6_GHWPARAMS6_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_USB3_GHWPARAMS6_GHWPARAMS6_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_USB3_GHWPARAMS6_GHWPARAMS6_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * `DWC_USB3_EN_DBG_PORTS
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS6 . GHWPARAMS6_6
 */
#define  VTSS_F_USB3_GHWPARAMS6_GHWPARAMS6_6(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_USB3_GHWPARAMS6_GHWPARAMS6_6  VTSS_BIT(6)
#define  VTSS_X_USB3_GHWPARAMS6_GHWPARAMS6_6(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * `DWC_USB3_EN_FPGA
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS6 . GHWPARAMS6_7
 */
#define  VTSS_F_USB3_GHWPARAMS6_GHWPARAMS6_7(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_USB3_GHWPARAMS6_GHWPARAMS6_7  VTSS_BIT(7)
#define  VTSS_X_USB3_GHWPARAMS6_GHWPARAMS6_7(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS6 . GHWPARAMS6_9_8
 */
#define  VTSS_F_USB3_GHWPARAMS6_GHWPARAMS6_9_8(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_USB3_GHWPARAMS6_GHWPARAMS6_9_8     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_USB3_GHWPARAMS6_GHWPARAMS6_9_8(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS6 . SRPSUPPORT
 */
#define  VTSS_F_USB3_GHWPARAMS6_SRPSUPPORT(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_USB3_GHWPARAMS6_SRPSUPPORT    VTSS_BIT(10)
#define  VTSS_X_USB3_GHWPARAMS6_SRPSUPPORT(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS6 . HNPSUPPORT
 */
#define  VTSS_F_USB3_GHWPARAMS6_HNPSUPPORT(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_USB3_GHWPARAMS6_HNPSUPPORT    VTSS_BIT(11)
#define  VTSS_X_USB3_GHWPARAMS6_HNPSUPPORT(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * `DWC_USB3_EN_ADP
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS6 . ADPSUPPORT
 */
#define  VTSS_F_USB3_GHWPARAMS6_ADPSUPPORT(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_USB3_GHWPARAMS6_ADPSUPPORT    VTSS_BIT(12)
#define  VTSS_X_USB3_GHWPARAMS6_ADPSUPPORT(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS6 . OTG_SS_SUPPORT
 */
#define  VTSS_F_USB3_GHWPARAMS6_OTG_SS_SUPPORT(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_USB3_GHWPARAMS6_OTG_SS_SUPPORT  VTSS_BIT(13)
#define  VTSS_X_USB3_GHWPARAMS6_OTG_SS_SUPPORT(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * `DWC_USB3_EN_BC
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS6 . BCSUPPORT
 */
#define  VTSS_F_USB3_GHWPARAMS6_BCSUPPORT(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_USB3_GHWPARAMS6_BCSUPPORT     VTSS_BIT(14)
#define  VTSS_X_USB3_GHWPARAMS6_BCSUPPORT(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * `DWC_USB3_EN_BUS_FILTERS
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS6 . BUSFLTRSSUPPORT
 */
#define  VTSS_F_USB3_GHWPARAMS6_BUSFLTRSSUPPORT(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_USB3_GHWPARAMS6_BUSFLTRSSUPPORT  VTSS_BIT(15)
#define  VTSS_X_USB3_GHWPARAMS6_BUSFLTRSSUPPORT(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * `DWC_USB3_RAM0_DEPTH
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS6 . GHWPARAMS6_31_16
 */
#define  VTSS_F_USB3_GHWPARAMS6_GHWPARAMS6_31_16(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_GHWPARAMS6_GHWPARAMS6_31_16     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_GHWPARAMS6_GHWPARAMS6_31_16(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Global Hardware Parameters Register 7

This register contains the hardware configuration options that you can select in the coreConsultant GUI.

For a description of each parameter, refer to the "Parameter Descriptions" chapter in the Databook. This information is also available in coreConsultant by right-clicking the parameter label and selecting "What's This" or by clicking the Help tab.

Note:

Some of the global hardware parameters are not currently modifiable in coreConsultant. These settings are in the  <workspace>/src/DWC_usb3_params.v file; you must not change them.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GHWPARAMS7
 */
#define VTSS_USB3_GHWPARAMS7                 VTSS_IOREG(VTSS_TO_USB3,0x3057)

/**
 * \brief
 * `DWC_USB3_RAM1_DEPTH
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS7 . GHWPARAMS7_15_0
 */
#define  VTSS_F_USB3_GHWPARAMS7_GHWPARAMS7_15_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_USB3_GHWPARAMS7_GHWPARAMS7_15_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_USB3_GHWPARAMS7_GHWPARAMS7_15_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * `DWC_USB3_RAM2_DEPTH
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS7 . GHWPARAMS7_31_16
 */
#define  VTSS_F_USB3_GHWPARAMS7_GHWPARAMS7_31_16(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_GHWPARAMS7_GHWPARAMS7_31_16     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_GHWPARAMS7_GHWPARAMS7_31_16(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Global Debug Queue/FIFO Space Available Register

Bit Bash test should not be done on this debug register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GDBGFIFOSPACE
 */
#define VTSS_USB3_GDBGFIFOSPACE              VTSS_IOREG(VTSS_TO_USB3,0x3058)

/**
 * \brief
 * FIFO/Queue Select (or) Port-Select
 *  - FIFO/Queue Select[8:5] indicates the FIFO/Queue Type
 *  - FIFO/Queue Select[4:0] indicates the FIFO/Queue Number
 * For example, 9'b0_0010_0001 refers to RxFIFO_1 and 9'b0_0101_1110 refers
 * to TxReqQ_30.
 *  - 9'b0_0001_1111 to 9'b0_0000_0000: TxFIFO_31 to TxFIFO_0
 *  - 9'b0_0011_1111 to 9'b0_0010_0000: RxFIFO_31 to RxFIFO_0
 *  - 9'b0_0101_1111 to 9'b0_0100_0000: TxReqQ_31 to TxReqQ_0
 *  - 9'b0_0111_1111 to 9'b0_0110_0000: RxReqQ_31 to RxReqQ_0
 *  - 9'b0_1001_1111 to 9'b0_1000_0000: RxInfoQ_31 to RxInfoQ_0
 *  - 9'b0_1010_0000: DescFetchQ_0 (for backwards compatibility)
 *  - 9'b0_1010_0001: EventQ_0 (for backwards compatibility)
 *  - 9'b0_1010_0010: ProtocolStatusQ_0
 *  - 9'b0_1101_1111 to 9'b0_1110_0000: DescFetchQ_31 to DescFetchQ_0
 *  - 9'b0_1111_1111 to 9'b0_1110_0000: WriteBack/EventQ_31 to
 * WriteBack/EventQ_0
 *  - 9'b1_0000_0111 to 9'b1_0000_0000: AuxEventQ_7 to AuxEventQ_0 (if
 * EN_SEPARATE_DESC_QUEUES=1)
 * Port-Select[3:0] selects the port-number when accessing GDBGLTSSM
 * register.
 *
 * \details
 * Field: ::VTSS_USB3_GDBGFIFOSPACE . FIFO_QUEUE_SELECT
 */
#define  VTSS_F_USB3_GDBGFIFOSPACE_FIFO_QUEUE_SELECT(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_USB3_GDBGFIFOSPACE_FIFO_QUEUE_SELECT     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_USB3_GDBGFIFOSPACE_FIFO_QUEUE_SELECT(x)  VTSS_EXTRACT_BITFIELD(x,0,9)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GDBGFIFOSPACE . RESERVED_15_9
 */
#define  VTSS_F_USB3_GDBGFIFOSPACE_RESERVED_15_9(x)  VTSS_ENCODE_BITFIELD(x,9,7)
#define  VTSS_M_USB3_GDBGFIFOSPACE_RESERVED_15_9     VTSS_ENCODE_BITMASK(9,7)
#define  VTSS_X_USB3_GDBGFIFOSPACE_RESERVED_15_9(x)  VTSS_EXTRACT_BITFIELD(x,9,7)

/**
 * \brief
 * SPACE_AVAILABLE
 *
 * \details
 * Field: ::VTSS_USB3_GDBGFIFOSPACE . SPACE_AVAILABLE
 */
#define  VTSS_F_USB3_GDBGFIFOSPACE_SPACE_AVAILABLE(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_GDBGFIFOSPACE_SPACE_AVAILABLE     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_GDBGFIFOSPACE_SPACE_AVAILABLE(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Global Debug LTSSM Register

In multi-port host configuration, the port-number is defined by Port-Select[3:0] field in the GDBGFIFOSPACE register.

Note:
 - GDBGLTSSM register is not applicable for USB 2.0-only mode.
 - Bit Bash test should not be done on this debug register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GDBGLTSSM
 */
#define VTSS_USB3_GDBGLTSSM                  VTSS_IOREG(VTSS_TO_USB3,0x3059)

/**
 * \brief
 * Tx Ones/Zeros (TxOnesZeros)
 *
 * For field definition, refer to Table 5-3 of the PIPE3 specification.
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLTSSM . TXONESZEROS
 */
#define  VTSS_F_USB3_GDBGLTSSM_TXONESZEROS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_USB3_GDBGLTSSM_TXONESZEROS    VTSS_BIT(0)
#define  VTSS_X_USB3_GDBGLTSSM_TXONESZEROS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Rx Termination (RxTermination)
 *
 * For details on `DWC_USB3_PIPE_RXTERM_RESET_VAL, refer to
 * <workspace>/src/DWC_usb3_params.v
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLTSSM . RXTERMINATION
 */
#define  VTSS_F_USB3_GDBGLTSSM_RXTERMINATION(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_USB3_GDBGLTSSM_RXTERMINATION  VTSS_BIT(1)
#define  VTSS_X_USB3_GDBGLTSSM_RXTERMINATION(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Tx Swing (TxSwing)
 *
 * For field definition, refer to Table 5-3 of the PIPE3 specification.
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLTSSM . TXSWING
 */
#define  VTSS_F_USB3_GDBGLTSSM_TXSWING(x)     VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_USB3_GDBGLTSSM_TXSWING        VTSS_BIT(2)
#define  VTSS_X_USB3_GDBGLTSSM_TXSWING(x)     VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LTSSM Clock State (LTDBClkState)
 *
 * In multi-port host configuration, the port number is defined by
 * Port-Select[3:0] field in the GDBGFIFOSPACE register.  Note: GDBGLTSSM
 * register is not applicable for USB 2.0-only mode.
 *  - 000: CLK_NORM (PHY is in non-P3 state and PCLK is running)
 *  - 001: CLK_TO_P3 (P3 entry request to PHY);
 *  - 010: CLK_WAIT1 (Wait for Phy_Status (P3 request));
 *  - 011: CLK_P3 (PHY is in P3 and PCLK is not running);
 *  - 100: CLK_TO_P0 (P3 exit request to PHY);
 *  - 101: CLK_WAIT2 (Wait for Phy_Status (P3 exit request))
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLTSSM . LTDBCLKSTATE
 */
#define  VTSS_F_USB3_GDBGLTSSM_LTDBCLKSTATE(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_USB3_GDBGLTSSM_LTDBCLKSTATE     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_USB3_GDBGLTSSM_LTDBCLKSTATE(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * TXDEEMPHASIS (TxDeemphasis)
 *
 * For field definition, refer to Table 5-3 of the PIPE3 specification.
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLTSSM . TXDEEMPHASIS
 */
#define  VTSS_F_USB3_GDBGLTSSM_TXDEEMPHASIS(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_USB3_GDBGLTSSM_TXDEEMPHASIS     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_USB3_GDBGLTSSM_TXDEEMPHASIS(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/**
 * \brief
 * RxEq Train
 *
 * For field definition, refer to Table 5-3 of the PIPE3 specification.
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLTSSM . RXEQTRAIN
 */
#define  VTSS_F_USB3_GDBGLTSSM_RXEQTRAIN(x)   VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_USB3_GDBGLTSSM_RXEQTRAIN      VTSS_BIT(8)
#define  VTSS_X_USB3_GDBGLTSSM_RXEQTRAIN(x)   VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * POWERDOWN (PowerDown)
 *
 * For field definition, refer to Table 5-3 of the PIPE3 specification.
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLTSSM . POWERDOWN
 */
#define  VTSS_F_USB3_GDBGLTSSM_POWERDOWN(x)   VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_USB3_GDBGLTSSM_POWERDOWN      VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_USB3_GDBGLTSSM_POWERDOWN(x)   VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * LTSSM PHY command State (LTDBPhyCmdState)
 *  - 000: PHY_IDLE (PHY command state is in IDLE. No PHY request pending)
 *  - 001: PHY_DET (Request to start Receiver detection)
 *  - 010: PHY_DET_3 (Wait for Phy_Status (Receiver detection))
 *  - 011: PHY_PWR_DLY (Delay Pipe3_PowerDown P0 -> P1/P2/P3 request)
 *  - 100: PHY_PWR_A (Delay for internal logic)
 *  - 101: PHY_PWR_B (Wait for Phy_Status(Power state change request))
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLTSSM . LTDBPHYCMDSTATE
 */
#define  VTSS_F_USB3_GDBGLTSSM_LTDBPHYCMDSTATE(x)  VTSS_ENCODE_BITFIELD(x,11,3)
#define  VTSS_M_USB3_GDBGLTSSM_LTDBPHYCMDSTATE     VTSS_ENCODE_BITMASK(11,3)
#define  VTSS_X_USB3_GDBGLTSSM_LTDBPHYCMDSTATE(x)  VTSS_EXTRACT_BITFIELD(x,11,3)

/**
 * \brief
 * Tx Detect Rx/Loopback (TxDetRxLoopback)
 *
 * For field definition, refer to Table 5-3 of the PIPE3 specification.
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLTSSM . TXDETRXLOOPBACK
 */
#define  VTSS_F_USB3_GDBGLTSSM_TXDETRXLOOPBACK(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_USB3_GDBGLTSSM_TXDETRXLOOPBACK  VTSS_BIT(14)
#define  VTSS_X_USB3_GDBGLTSSM_TXDETRXLOOPBACK(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Rx Polarity (RxPolarity)
 *
 * For field definition, refer to Table 5-3 of the PIPE3 specification.
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLTSSM . RXPOLARITY
 */
#define  VTSS_F_USB3_GDBGLTSSM_RXPOLARITY(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_USB3_GDBGLTSSM_RXPOLARITY     VTSS_BIT(15)
#define  VTSS_X_USB3_GDBGLTSSM_RXPOLARITY(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Tx Elec Idle (TxElecIdle)
 *
 * For field definition, refer to Table 5-3 of the PIPE3 specification.
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLTSSM . TXELECLDLE
 */
#define  VTSS_F_USB3_GDBGLTSSM_TXELECLDLE(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_USB3_GDBGLTSSM_TXELECLDLE     VTSS_BIT(16)
#define  VTSS_X_USB3_GDBGLTSSM_TXELECLDLE(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Elastic Buffer Mode (ElasticBufferMode)
 *
 * For field definition, refer to Table 5-3 of the PIPE3 specification.
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLTSSM . ELASTICBUFFERMODE
 */
#define  VTSS_F_USB3_GDBGLTSSM_ELASTICBUFFERMODE(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_USB3_GDBGLTSSM_ELASTICBUFFERMODE  VTSS_BIT(17)
#define  VTSS_X_USB3_GDBGLTSSM_ELASTICBUFFERMODE(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * LTDB Sub-State (LTDBSubState)
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLTSSM . LTDBSUBSTATE
 */
#define  VTSS_F_USB3_GDBGLTSSM_LTDBSUBSTATE(x)  VTSS_ENCODE_BITFIELD(x,18,4)
#define  VTSS_M_USB3_GDBGLTSSM_LTDBSUBSTATE     VTSS_ENCODE_BITMASK(18,4)
#define  VTSS_X_USB3_GDBGLTSSM_LTDBSUBSTATE(x)  VTSS_EXTRACT_BITFIELD(x,18,4)

/**
 * \brief
 * LTDB Link State (LTDBLinkState)
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLTSSM . LTDBLINKSTATE
 */
#define  VTSS_F_USB3_GDBGLTSSM_LTDBLINKSTATE(x)  VTSS_ENCODE_BITFIELD(x,22,4)
#define  VTSS_M_USB3_GDBGLTSSM_LTDBLINKSTATE     VTSS_ENCODE_BITMASK(22,4)
#define  VTSS_X_USB3_GDBGLTSSM_LTDBLINKSTATE(x)  VTSS_EXTRACT_BITFIELD(x,22,4)

/**
 * \brief
 * LTDB Timeout (LTDBTimeout)
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLTSSM . LTDBTIMEOUT
 */
#define  VTSS_F_USB3_GDBGLTSSM_LTDBTIMEOUT(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_USB3_GDBGLTSSM_LTDBTIMEOUT    VTSS_BIT(26)
#define  VTSS_X_USB3_GDBGLTSSM_LTDBTIMEOUT(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLTSSM . PRTDIRECTION
 */
#define  VTSS_F_USB3_GDBGLTSSM_PRTDIRECTION(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_USB3_GDBGLTSSM_PRTDIRECTION   VTSS_BIT(27)
#define  VTSS_X_USB3_GDBGLTSSM_PRTDIRECTION(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLTSSM . X3_DS_HOST_SHUTDOWN
 */
#define  VTSS_F_USB3_GDBGLTSSM_X3_DS_HOST_SHUTDOWN(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_USB3_GDBGLTSSM_X3_DS_HOST_SHUTDOWN  VTSS_BIT(28)
#define  VTSS_X_USB3_GDBGLTSSM_X3_DS_HOST_SHUTDOWN(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLTSSM . X3_XS_SWAPPING
 */
#define  VTSS_F_USB3_GDBGLTSSM_X3_XS_SWAPPING(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_USB3_GDBGLTSSM_X3_XS_SWAPPING  VTSS_BIT(29)
#define  VTSS_X_USB3_GDBGLTSSM_X3_XS_SWAPPING(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * RxElecidle
 *
 * For description of RxElecIdle, see table 5-4, "Status Interface Signals"
 * of the PIPE3 Specification.
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLTSSM . RXELECIDLE
 */
#define  VTSS_F_USB3_GDBGLTSSM_RXELECIDLE(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_USB3_GDBGLTSSM_RXELECIDLE     VTSS_BIT(30)
#define  VTSS_X_USB3_GDBGLTSSM_RXELECIDLE(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLTSSM . RESERVED_31_31
 */
#define  VTSS_F_USB3_GDBGLTSSM_RESERVED_31_31(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_USB3_GDBGLTSSM_RESERVED_31_31  VTSS_BIT(31)
#define  VTSS_X_USB3_GDBGLTSSM_RESERVED_31_31(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief Global Debug LNMCC Register

Bit Bash test should not be done on this debug register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GDBGLNMCC
 */
#define VTSS_USB3_GDBGLNMCC                  VTSS_IOREG(VTSS_TO_USB3,0x305a)

/**
 * \brief
 * This field indicates the bit error rate information for the port
 * selected in the GDBGFIFOSPACE.PortSelect field.
 *
 * This field is for debug purposes only.
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLNMCC . LNMCC_BERC
 */
#define  VTSS_F_USB3_GDBGLNMCC_LNMCC_BERC(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_USB3_GDBGLNMCC_LNMCC_BERC     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_USB3_GDBGLNMCC_LNMCC_BERC(x)  VTSS_EXTRACT_BITFIELD(x,0,9)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLNMCC . RESERVED_31_9
 */
#define  VTSS_F_USB3_GDBGLNMCC_RESERVED_31_9(x)  VTSS_ENCODE_BITFIELD(x,9,23)
#define  VTSS_M_USB3_GDBGLNMCC_RESERVED_31_9     VTSS_ENCODE_BITMASK(9,23)
#define  VTSS_X_USB3_GDBGLNMCC_RESERVED_31_9(x)  VTSS_EXTRACT_BITFIELD(x,9,23)


/**
 * \brief Global Debug BMU Register

Bit Bash test should not be done on this debug register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GDBGBMU
 */
#define VTSS_USB3_GDBGBMU                    VTSS_IOREG(VTSS_TO_USB3,0x305b)

/**
 * \brief
 * BMU_CCU Debug information
 *
 * \details
 * Field: ::VTSS_USB3_GDBGBMU . BMU_CCU
 */
#define  VTSS_F_USB3_GDBGBMU_BMU_CCU(x)       VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_USB3_GDBGBMU_BMU_CCU          VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_USB3_GDBGBMU_BMU_CCU(x)       VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * BMU_DCU Debug information
 *
 * \details
 * Field: ::VTSS_USB3_GDBGBMU . BMU_DCU
 */
#define  VTSS_F_USB3_GDBGBMU_BMU_DCU(x)       VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_USB3_GDBGBMU_BMU_DCU          VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_USB3_GDBGBMU_BMU_DCU(x)       VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * BMU_BCU Debug information
 *
 * \details
 * Field: ::VTSS_USB3_GDBGBMU . BMU_BCU
 */
#define  VTSS_F_USB3_GDBGBMU_BMU_BCU(x)       VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_USB3_GDBGBMU_BMU_BCU          VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_USB3_GDBGBMU_BMU_BCU(x)       VTSS_EXTRACT_BITFIELD(x,8,24)


/**
 * \brief Global Debug LSP MUX Register - Host

This register is for internal use only.

If DWC_USB3_PRESERVE_LOGIC_ANALYZER_SELECT is enabled during controller configuration, then the default values readout is X (Undefined).

Bit Bash test should not be done on this debug register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GDBGLSPMUX_HST
 */
#define VTSS_USB3_GDBGLSPMUX_HST             VTSS_IOREG(VTSS_TO_USB3,0x305c)

/**
 * \brief
 * Device LSP Select
 *
 * Selects the LSP debug information presented in the GDBGLSP register in
 * host mode.

 *
 * \details
 * Field: ::VTSS_USB3_GDBGLSPMUX_HST . GDBGLSPMUX_HST_HOSTSELECT
 */
#define  VTSS_F_USB3_GDBGLSPMUX_HST_GDBGLSPMUX_HST_HOSTSELECT(x)  VTSS_ENCODE_BITFIELD(x,0,14)
#define  VTSS_M_USB3_GDBGLSPMUX_HST_GDBGLSPMUX_HST_HOSTSELECT     VTSS_ENCODE_BITMASK(0,14)
#define  VTSS_X_USB3_GDBGLSPMUX_HST_GDBGLSPMUX_HST_HOSTSELECT(x)  VTSS_EXTRACT_BITFIELD(x,0,14)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLSPMUX_HST . RESERVED_15_14
 */
#define  VTSS_F_USB3_GDBGLSPMUX_HST_RESERVED_15_14(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_USB3_GDBGLSPMUX_HST_RESERVED_15_14     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_USB3_GDBGLSPMUX_HST_RESERVED_15_14(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * logic_analyzer_trace Port MUX Select
 *
 * Currently only bits[21:16] are used. For details on how the mux controls
 * the debug traces, refer to the "assign logic_analyzer_trace =" code
 * section in the DWC_usb3.v file.
 *
 * A value of 6'h3F drives 0s on the logic_analyzer_trace signal. If you
 * plan to OR (instead using a mux) this signal with other trace signals in
 * your system to generate a common trace signal, you can use this feature.

 *
 * \details
 * Field: ::VTSS_USB3_GDBGLSPMUX_HST . GDBGLSPMUX_HST_LOGIC_ANALYZER_TRACE
 */
#define  VTSS_F_USB3_GDBGLSPMUX_HST_GDBGLSPMUX_HST_LOGIC_ANALYZER_TRACE(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_USB3_GDBGLSPMUX_HST_GDBGLSPMUX_HST_LOGIC_ANALYZER_TRACE     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_USB3_GDBGLSPMUX_HST_GDBGLSPMUX_HST_LOGIC_ANALYZER_TRACE(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLSPMUX_HST . GDBGLSPMUX_HST_RESERVED_31_24
 */
#define  VTSS_F_USB3_GDBGLSPMUX_HST_GDBGLSPMUX_HST_RESERVED_31_24(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_USB3_GDBGLSPMUX_HST_GDBGLSPMUX_HST_RESERVED_31_24     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_USB3_GDBGLSPMUX_HST_GDBGLSPMUX_HST_RESERVED_31_24(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief Global Debug LSP MUX Register - Device

This register is for internal use only.

If DWC_USB3_PRESERVE_LOGIC_ANALYZER_SELECT is enabled during controller configuration, then the default values readout is X (Undefined).

Bit Bash test should not be done on this debug register.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GDBGLSPMUX_DEV
 */
#define VTSS_USB3_GDBGLSPMUX_DEV             VTSS_IOREG(VTSS_TO_USB3,0x305c)

/**
 * \brief
 * Device Endpoint Select
 *
 * Selects the Endpoint debug information presented in the GDBGEPINFO
 * registers in device mode.

 *
 * \details
 * Field: ::VTSS_USB3_GDBGLSPMUX_DEV . EPSELECT
 */
#define  VTSS_F_USB3_GDBGLSPMUX_DEV_EPSELECT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_USB3_GDBGLSPMUX_DEV_EPSELECT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_USB3_GDBGLSPMUX_DEV_EPSELECT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Device LSP Select
 *
 * Selects the LSP debug information presented in the GDBGLSP register in
 * device mode.

 *
 * \details
 * Field: ::VTSS_USB3_GDBGLSPMUX_DEV . DEVSELECT
 */
#define  VTSS_F_USB3_GDBGLSPMUX_DEV_DEVSELECT(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_USB3_GDBGLSPMUX_DEV_DEVSELECT     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_USB3_GDBGLSPMUX_DEV_DEVSELECT(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * Device LSP Select

 *
 * \details
 * Field: ::VTSS_USB3_GDBGLSPMUX_DEV . GDBGLSPMUX_DEV_HOSTSELECT
 */
#define  VTSS_F_USB3_GDBGLSPMUX_DEV_GDBGLSPMUX_DEV_HOSTSELECT(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_USB3_GDBGLSPMUX_DEV_GDBGLSPMUX_DEV_HOSTSELECT     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_USB3_GDBGLSPMUX_DEV_GDBGLSPMUX_DEV_HOSTSELECT(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLSPMUX_DEV . GDBGLSPMUX_DEV_RESERVED_14
 */
#define  VTSS_F_USB3_GDBGLSPMUX_DEV_GDBGLSPMUX_DEV_RESERVED_14(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_USB3_GDBGLSPMUX_DEV_GDBGLSPMUX_DEV_RESERVED_14  VTSS_BIT(14)
#define  VTSS_X_USB3_GDBGLSPMUX_DEV_GDBGLSPMUX_DEV_RESERVED_14(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Enable debugging of Debug capablity LSP in Host mode.  Use HostSelect to
 * select DbC LSP debug information presented in the GDBGLSP register.
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLSPMUX_DEV . ENDBC
 */
#define  VTSS_F_USB3_GDBGLSPMUX_DEV_ENDBC(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_USB3_GDBGLSPMUX_DEV_ENDBC     VTSS_BIT(15)
#define  VTSS_X_USB3_GDBGLSPMUX_DEV_ENDBC(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Logic Analyzer Trace Port MUX Select
 *
 * Currently only bits[21:16] are used. For details on how the mux controls
 * the debug traces, refer to "assign logic_analyzer_trace =" code section
 * in the DWC_usb3.v file.
 *
 * A value of 6'h3F drives "0"s on the logic_analyzer_trace signal. If you
 * plan to OR (instead using a mux) this signal with other trace signals in
 * your system to generate a common trace signal, you can use this feature.

 *
 * \details
 * Field: ::VTSS_USB3_GDBGLSPMUX_DEV . GDBGLSPMUX_DEV_LOGIC_ANALYZER_TRACE
 */
#define  VTSS_F_USB3_GDBGLSPMUX_DEV_GDBGLSPMUX_DEV_LOGIC_ANALYZER_TRACE(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_USB3_GDBGLSPMUX_DEV_GDBGLSPMUX_DEV_LOGIC_ANALYZER_TRACE     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_USB3_GDBGLSPMUX_DEV_GDBGLSPMUX_DEV_LOGIC_ANALYZER_TRACE(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLSPMUX_DEV . GDBGLSPMUX_DEV_RESERVED_31_24
 */
#define  VTSS_F_USB3_GDBGLSPMUX_DEV_GDBGLSPMUX_DEV_RESERVED_31_24(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_USB3_GDBGLSPMUX_DEV_GDBGLSPMUX_DEV_RESERVED_31_24     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_USB3_GDBGLSPMUX_DEV_GDBGLSPMUX_DEV_RESERVED_31_24(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief Global Debug LSP Register

This register is for internal debug purposes only.

This register is for internal use only.

If DWC_USB3_PRESERVE_LOGIC_ANALYZER_SELECT is enabled during controller configuration, then the default values readout is X (Undefined).

Bit Bash test should not be done on this debug register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GDBGLSP
 */
#define VTSS_USB3_GDBGLSP                    VTSS_IOREG(VTSS_TO_USB3,0x305d)

/**
 * \brief
 * LSP Debug Information
 *
 * \details
 * Field: ::VTSS_USB3_GDBGLSP . LSPDEBUG
 */
#define  VTSS_F_USB3_GDBGLSP_LSPDEBUG(x)      (x)
#define  VTSS_M_USB3_GDBGLSP_LSPDEBUG         0xffffffff
#define  VTSS_X_USB3_GDBGLSP_LSPDEBUG(x)      (x)


/**
 * \brief Global Debug Endpoint Information Register 0

This register is for internal use only.

If DWC_USB3_PRESERVE_LOGIC_ANALYZER_SELECT is enabled during controller configuration, then the default values readout is X (Undefined).

Bit Bash test should not be done on this debug register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GDBGEPINFO0
 */
#define VTSS_USB3_GDBGEPINFO0                VTSS_IOREG(VTSS_TO_USB3,0x305e)

/**
 * \brief
 * Endpoint Debug Information, bits[31:0]
 *
 * \details
 * Field: ::VTSS_USB3_GDBGEPINFO0 . GDBGEPINFO0_EPDEBUG
 */
#define  VTSS_F_USB3_GDBGEPINFO0_GDBGEPINFO0_EPDEBUG(x)  (x)
#define  VTSS_M_USB3_GDBGEPINFO0_GDBGEPINFO0_EPDEBUG     0xffffffff
#define  VTSS_X_USB3_GDBGEPINFO0_GDBGEPINFO0_EPDEBUG(x)  (x)


/**
 * \brief Global Debug Endpoint Information Register 1

This register is for internal use only.

If DWC_USB3_PRESERVE_LOGIC_ANALYZER_SELECT is enabled during controller configuration, then the default values readout is X (Undefined).

Bit Bash test should not be done on this debug register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GDBGEPINFO1
 */
#define VTSS_USB3_GDBGEPINFO1                VTSS_IOREG(VTSS_TO_USB3,0x305f)

/**
 * \brief
 * Endpoint Debug Information, bits[63:32]
 *
 * \details
 * Field: ::VTSS_USB3_GDBGEPINFO1 . GDBGEPINFO1_EPDEBUG
 */
#define  VTSS_F_USB3_GDBGEPINFO1_GDBGEPINFO1_EPDEBUG(x)  (x)
#define  VTSS_M_USB3_GDBGEPINFO1_GDBGEPINFO1_EPDEBUG     0xffffffff
#define  VTSS_X_USB3_GDBGEPINFO1_GDBGEPINFO1_EPDEBUG(x)  (x)


/**
 * \brief Global High-Speed Port to Bus Instance Mapping Register - Low

This is an alternate register for the GPRTBIMAP_HS register.

 - Register fields are read-write with respect to number of port instantiated. writeAsRead constraint is added to limit side effects for unused fields.

Note: For reset values, refer to the corresponding values in the GPRTBIMAP_HS register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GPRTBIMAP_HSLO
 */
#define VTSS_USB3_GPRTBIMAP_HSLO             VTSS_IOREG(VTSS_TO_USB3,0x3060)

/**
 * \brief
 * BINUM1: HS USB Instance Number for Port 1.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_HSLO . GPRTBIMAP_HSLO_BINUM1
 */
#define  VTSS_F_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * BINUM2: HS USB Instance Number for Port 2.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_HSLO . GPRTBIMAP_HSLO_BINUM2
 */
#define  VTSS_F_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM2(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM2     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM2(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * BINUM3: HS USB Instance Number for Port 3.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_HSLO . GPRTBIMAP_HSLO_BINUM3
 */
#define  VTSS_F_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM3(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM3     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM3(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * BINUM4: HS USB Instance Number for Port 4.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_HSLO . GPRTBIMAP_HSLO_BINUM4
 */
#define  VTSS_F_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM4(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM4     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM4(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * BINUM5: HS USB Instance Number for Port 5.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_HSLO . GPRTBIMAP_HSLO_BINUM5
 */
#define  VTSS_F_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM5(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM5     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM5(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * BINUM6 USB Instance Number for Port 6.
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_HSLO . GPRTBIMAP_HSLO_BINUM6
 */
#define  VTSS_F_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM6(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM6     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM6(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * BINUM7: HS USB Instance Number for Port 7.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_HSLO . GPRTBIMAP_HSLO_BINUM7
 */
#define  VTSS_F_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM7(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM7     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM7(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * BINUM8: HS USB Instance Number for Port 8.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_HSLO . GPRTBIMAP_HSLO_BINUM8
 */
#define  VTSS_F_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM8(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM8     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_USB3_GPRTBIMAP_HSLO_GPRTBIMAP_HSLO_BINUM8(x)  VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief Global High-Speed Port to Bus Instance Mapping Register - High

This is an alternate register for the GPRTBIMAP_HS register.

 - Register fields are read-write with respect to number of port instantiated. writeAsRead constraint is added to limit side effects for unused fields.

Note: For reset values, refer to the corresponding values in the GPRTBIMAP register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GPRTBIMAP_HSHI
 */
#define VTSS_USB3_GPRTBIMAP_HSHI             VTSS_IOREG(VTSS_TO_USB3,0x3061)

/**
 * \brief
 * BINUM9: HS USB Instance Number for Port 9.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_HSHI . GPRTBIMAP_HSHI_BINUM9
 */
#define  VTSS_F_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM9(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM9     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM9(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * BINUM10: HS USB Instance Number for Port 10.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_HSHI . GPRTBIMAP_HSHI_BINUM10
 */
#define  VTSS_F_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM10(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM10     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM10(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * BINUM11: HS USB Instance Number for 11.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_HSHI . GPRTBIMAP_HSHI_BINUM11
 */
#define  VTSS_F_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM11(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM11     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM11(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * BINUM12: HS USB Instance Number for Port 12.
 *
 * SApplication-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_HSHI . GPRTBIMAP_HSHI_BINUM12
 */
#define  VTSS_F_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM12(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM12     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM12(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * BINUM13: HS USB Instance Number for Port 13.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_HSHI . GPRTBIMAP_HSHI_BINUM13
 */
#define  VTSS_F_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM13(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM13     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM13(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * BINUM14: HS USB Instance Number for Port 14.
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_HSHI . GPRTBIMAP_HSHI_BINUM14
 */
#define  VTSS_F_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM14(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM14     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM14(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * BINUM15: HS USB Instance Number for Port 15.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_HSHI . GPRTBIMAP_HSHI_BINUM15
 */
#define  VTSS_F_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM15(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM15     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_BINUM15(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_HSHI . GPRTBIMAP_HSHI_RESERVED_31_28
 */
#define  VTSS_F_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_RESERVED_31_28(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_RESERVED_31_28     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_USB3_GPRTBIMAP_HSHI_GPRTBIMAP_HSHI_RESERVED_31_28(x)  VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief Global Full-Speed Port to Bus Instance Mapping Register - Low

This is an alternate register for the GPRTBIMAP_FS register.

 - Register fields are read-write with respect to number of port instantiated. writeAsRead constraint is added to limit side effects for unused fields.

Note: For reset values, refer to the corresponding values in the GPRTBIMAP_FS register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GPRTBIMAP_FSLO
 */
#define VTSS_USB3_GPRTBIMAP_FSLO             VTSS_IOREG(VTSS_TO_USB3,0x3062)

/**
 * \brief
 * BINUM1: FS USB Instance Number for Port 1.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_FSLO . GPRTBIMAP_FSLO_BINUM1
 */
#define  VTSS_F_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * BINUM2: FS USB Instance Number for Port 2.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_FSLO . GPRTBIMAP_FSLO_BINUM2
 */
#define  VTSS_F_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM2(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM2     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM2(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * BINUM3: FS USB Instance Number for Port 3.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_FSLO . GPRTBIMAP_FSLO_BINUM3
 */
#define  VTSS_F_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM3(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM3     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM3(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * BINUM4: FS USB Instance Number for Port 4.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_FSLO . GPRTBIMAP_FSLO_BINUM4
 */
#define  VTSS_F_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM4(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM4     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM4(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * BINUM5: FS USB Instance Number for Port 5.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_FSLO . GPRTBIMAP_FSLO_BINUM5
 */
#define  VTSS_F_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM5(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM5     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM5(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * BINUM6: FS USB Instance Number for Port 6.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_FSLO . GPRTBIMAP_FSLO_BINUM6
 */
#define  VTSS_F_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM6(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM6     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM6(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * BINUM7: FS USB Instance Number for Port 7.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_FSLO . GPRTBIMAP_FSLO_BINUM7
 */
#define  VTSS_F_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM7(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM7     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM7(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * BINUM8: FS USB Instance Number for Port 8.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_FSLO . GPRTBIMAP_FSLO_BINUM8
 */
#define  VTSS_F_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM8(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM8     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_USB3_GPRTBIMAP_FSLO_GPRTBIMAP_FSLO_BINUM8(x)  VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief Global Full-Speed Port to Bus Instance Mapping Register - High

This is an alternate register for the GPRTBIMAP_FS register.

 - Register fields are read-write with respect to number of port instantiated. writeAsRead constraint is added to limit side effects for unused fields.

Note: For reset values, refer to the corresponding values in the GPRTBIMAP_FS register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GPRTBIMAP_FSHI
 */
#define VTSS_USB3_GPRTBIMAP_FSHI             VTSS_IOREG(VTSS_TO_USB3,0x3063)

/**
 * \brief
 * BINUM9: FS USB Instance Number for Port 9.
 *
 * Application-programmable ID field.
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_FSHI . GPRTBIMAP_FSHI_BINUM9
 */
#define  VTSS_F_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM9(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM9     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM9(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * BINUM10: FS USB Instance Number for Port 10.
 *
 * Application-programmable ID field
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_FSHI . GPRTBIMAP_FSHI_BINUM10
 */
#define  VTSS_F_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM10(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM10     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM10(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * BINUM11: FS USB Instance Number for Port 11.
 *
 * Application-programmable ID field
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_FSHI . GPRTBIMAP_FSHI_BINUM11
 */
#define  VTSS_F_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM11(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM11     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM11(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * BINUM12: FS USB Instance Number for Port 12.
 *
 * Application-programmable ID field
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_FSHI . GPRTBIMAP_FSHI_BINUM12
 */
#define  VTSS_F_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM12(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM12     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM12(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * BINUM13: FS USB Instance Number for Port 13.
 *
 * Application-programmable ID field
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_FSHI . GPRTBIMAP_FSHI_BINUM13
 */
#define  VTSS_F_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM13(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM13     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM13(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * BINUM14: FS USB Instance Number for Port 14.
 *
 * Application-programmable ID field
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_FSHI . GPRTBIMAP_FSHI_BINUM14
 */
#define  VTSS_F_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM14(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM14     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM14(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * BINUM15: FS USB Instance Number for Port 15.
 *
 * Application-programmable ID field
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_FSHI . GPRTBIMAP_FSHI_BINUM15
 */
#define  VTSS_F_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM15(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM15     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_BINUM15(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GPRTBIMAP_FSHI . GPRTBIMAP_FSHI_RESERVED_31_28
 */
#define  VTSS_F_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_RESERVED_31_28(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_RESERVED_31_28     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_USB3_GPRTBIMAP_FSHI_GPRTBIMAP_FSHI_RESERVED_31_28(x)  VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief Future Reserved Register at offset 0x94
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:RESERVED_94
 */
#define VTSS_USB3_RESERVED_94                VTSS_IOREG(VTSS_TO_USB3,0x3065)

/**
 * \brief
 * Future use Register field
 *
 * \details
 * Field: ::VTSS_USB3_RESERVED_94 . RESERVED_94_RESERVED_31_0
 */
#define  VTSS_F_USB3_RESERVED_94_RESERVED_94_RESERVED_31_0(x)  (x)
#define  VTSS_M_USB3_RESERVED_94_RESERVED_94_RESERVED_31_0     0xffffffff
#define  VTSS_X_USB3_RESERVED_94_RESERVED_94_RESERVED_31_0(x)  (x)


/**
 * \brief Future Reserved Register at offset 0x98
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:RESERVED_98
 */
#define VTSS_USB3_RESERVED_98                VTSS_IOREG(VTSS_TO_USB3,0x3066)

/**
 * \brief
 * Field for future use
 *
 * \details
 * Field: ::VTSS_USB3_RESERVED_98 . RESERVED_98_RESERVED_31_0
 */
#define  VTSS_F_USB3_RESERVED_98_RESERVED_98_RESERVED_31_0(x)  (x)
#define  VTSS_M_USB3_RESERVED_98_RESERVED_98_RESERVED_31_0     0xffffffff
#define  VTSS_X_USB3_RESERVED_98_RESERVED_98_RESERVED_31_0(x)  (x)


/**
 * \brief Global User Control Register 2:

This register provides a few options for the software to control the controller behavior in the Host and device mode. Most of the options are used to improve inter-operability with different hosts and devices.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GUCTL2
 */
#define VTSS_USB3_GUCTL2                     VTSS_IOREG(VTSS_TO_USB3,0x3067)

/**
 * \brief
 * Transmit Ping Maximum Duration
 *
 * This field is relevant to Device mode and controls the maximum duration
 * for which the controller should instruct the PHY to transmit a Ping
 * LFPS. The duration of the Ping LFPS is controlled by programming this
 * value and is in terms of 8 ns granularity. Eg: A value of 13 indicates
 * 104 ns.

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL2 . TXPINGDURATION
 */
#define  VTSS_F_USB3_GUCTL2_TXPINGDURATION(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_USB3_GUCTL2_TXPINGDURATION     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_USB3_GUCTL2_TXPINGDURATION(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * Recieve Ping Maximum Duration
 *
 * This field is relevant to Host mode and controls the maximum duration of
 * received LFPS to be treated as a Ping LFPS. The Max duration of the Ping
 * LFPS is controlled by programming this value and is in terms of 8 ns
 * granularity. Eg: A value of 32 indicates 256 ns.

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL2 . RXPINGDURATION
 */
#define  VTSS_F_USB3_GUCTL2_RXPINGDURATION(x)  VTSS_ENCODE_BITFIELD(x,5,6)
#define  VTSS_M_USB3_GUCTL2_RXPINGDURATION     VTSS_ENCODE_BITMASK(5,6)
#define  VTSS_X_USB3_GUCTL2_RXPINGDURATION(x)  VTSS_EXTRACT_BITFIELD(x,5,6)

/**
 * \brief
 * Disable xHCI Errata Feature Contiguous Frame ID Capability
 *
 * This field controls the xHCI Errata feature Contiguous FrameID
 * capability. When set, the xHCI HCCPARAMS1 bit 11 will be set to 0
 * indicating that CFC is not supported. Disable this feature only if your
 * application cannot tolerate Misssed Service Error events for Isoc
 * transfers, and your system latencies are large to cause Missed Service
 * errors even if the software is following the Isochronous Thresholding
 * rules.
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL2 . DISABLECFC
 */
#define  VTSS_F_USB3_GUCTL2_DISABLECFC(x)     VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_USB3_GUCTL2_DISABLECFC        VTSS_BIT(11)
#define  VTSS_X_USB3_GUCTL2_DISABLECFC(x)     VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Enable Evicting Endpoint cache after Flow Control for bulk endpoints.
 *
 * In 3.00a release, a performance enhancement was done to keep the
 * non-stream capable bulk IN endpoint in cache after flow control. Setting
 * this bit will disable this enhancement. This should be set only for
 * debug purpose.
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL2 . ENABLEEPCACHEEVICT
 */
#define  VTSS_F_USB3_GUCTL2_ENABLEEPCACHEEVICT(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_USB3_GUCTL2_ENABLEEPCACHEEVICT  VTSS_BIT(12)
#define  VTSS_X_USB3_GUCTL2_ENABLEEPCACHEEVICT(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Reserved for future use
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL2 . RESERVED_13
 */
#define  VTSS_F_USB3_GUCTL2_RESERVED_13(x)    VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_USB3_GUCTL2_RESERVED_13       VTSS_BIT(13)
#define  VTSS_X_USB3_GUCTL2_RESERVED_13(x)    VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Enable clearing of the command active bit for the ENDXFER command after
 * the command execution is completed.
 *
 *  This bit is valid in device mode only.
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL2 . RST_ACTBITLATER
 */
#define  VTSS_F_USB3_GUCTL2_RST_ACTBITLATER(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_USB3_GUCTL2_RST_ACTBITLATER   VTSS_BIT(14)
#define  VTSS_X_USB3_GUCTL2_RST_ACTBITLATER(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * No Low Power Duration (NOLOWPWRDUR)
 *
 * This bit is applicable for device mode only and is ignored in host mode.
 *
 * After starting a transfer on a SS ISOC endpoint, the application must
 * program these bits  to prevent the device to lose frame synchronization
 * over a period of time.
 * Based on this count-down counter, the device will wake itself from U1/U2
 * low power states. After entering to U0 state and receiving two ITPs
 * (which will sync-up the host and the device), U1/U2 low power entry is
 * allowed.
 *
 * Each count represents the duration in terms of milliseconds. For
 * example, a value of 3 represents 3ms.
 *
 * Note:
 *  - To disable this feature, set this field to 4'b0.
 *  - These bits are applicable only in device mode and ignored in host
 * mode.
 *  - Some xHCI hosts do not send ITPs when performing ISOC transfers when
 * the link enters U1/U2 low power states. This causes the device to lose
 * frame synchronization over a period of time resulting in ISOC packets
 * being dropped.

 *
 * \details
 * Field: ::VTSS_USB3_GUCTL2 . NOLOWPWRDUR
 */
#define  VTSS_F_USB3_GUCTL2_NOLOWPWRDUR(x)    VTSS_ENCODE_BITFIELD(x,15,4)
#define  VTSS_M_USB3_GUCTL2_NOLOWPWRDUR       VTSS_ENCODE_BITMASK(15,4)
#define  VTSS_X_USB3_GUCTL2_NOLOWPWRDUR(x)    VTSS_EXTRACT_BITFIELD(x,15,4)

/**
 * \brief
 * This register field is used to set new HP and PM timers.
 *  - To enable PM timer, set GUCTL2[19] bit as 1.
 *  - To enable HP timer, set GUCTL2[20] bit as 1. Default value of HP
 * timer is 4us when HP PM timer is not enabled; when new HP timer is
 * enabled default value is 12us.
 * Use GUCTL2[25:21] to specify HP timer value in microseconds.
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL2 . EN_HP_PM_TIMER
 */
#define  VTSS_F_USB3_GUCTL2_EN_HP_PM_TIMER(x)  VTSS_ENCODE_BITFIELD(x,19,7)
#define  VTSS_M_USB3_GUCTL2_EN_HP_PM_TIMER     VTSS_ENCODE_BITMASK(19,7)
#define  VTSS_X_USB3_GUCTL2_EN_HP_PM_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,19,7)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL2 . RESERVED_31_26
 */
#define  VTSS_F_USB3_GUCTL2_RESERVED_31_26(x)  VTSS_ENCODE_BITFIELD(x,26,6)
#define  VTSS_M_USB3_GUCTL2_RESERVED_31_26     VTSS_ENCODE_BITMASK(26,6)
#define  VTSS_X_USB3_GUCTL2_RESERVED_31_26(x)  VTSS_EXTRACT_BITFIELD(x,26,6)


/**
 * \brief Global Hardware Parameters Register 8

This register contains the hardware configuration options that you can select in the coreConsultant GUI.

For a description of each parameter, refer to the "Parameter Descriptions" chapter in the Databook. This information is also available in coreConsultant by right-clicking the parameter label and selecting "What's This" or by clicking the Help tab.

Note:

Some of the global hardware parameters are not currently modifiable in coreConsultant. These settings are in the  <workspace>/src/DWC_usb3_params.v file; you must not change them.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GHWPARAMS8
 */
#define VTSS_USB3_GHWPARAMS8                 VTSS_IOREG(VTSS_TO_USB3,0x3180)

/**
 * \brief
 * `DWC_USB3_DCACHE_DEPTH_INFO
 *
 * \details
 * Field: ::VTSS_USB3_GHWPARAMS8 . GHWPARAMS8_32_0
 */
#define  VTSS_F_USB3_GHWPARAMS8_GHWPARAMS8_32_0(x)  (x)
#define  VTSS_M_USB3_GHWPARAMS8_GHWPARAMS8_32_0     0xffffffff
#define  VTSS_X_USB3_GHWPARAMS8_GHWPARAMS8_32_0(x)  (x)


/**
 * \brief Global User Control Register 3

This register provides a few options for the software to control the controller behavior in the Host mode. Most of the options are used to improve host inter-operability with different devices.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GUCTL3
 */
#define VTSS_USB3_GUCTL3                     VTSS_IOREG(VTSS_TO_USB3,0x3183)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL3 . RESERVED_15_0
 */
#define  VTSS_F_USB3_GUCTL3_RESERVED_15_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_USB3_GUCTL3_RESERVED_15_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_USB3_GUCTL3_RESERVED_15_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Enable SuperSpeed Ping Transaction Packet scheduling early in the
 * microframe.
 *
 * This bit is valid in Host mode only.
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL3 . SCH_PING_EARLY
 */
#define  VTSS_F_USB3_GUCTL3_SCH_PING_EARLY(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_USB3_GUCTL3_SCH_PING_EARLY    VTSS_BIT(16)
#define  VTSS_X_USB3_GUCTL3_SCH_PING_EARLY(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GUCTL3 . RESERVED_31_17
 */
#define  VTSS_F_USB3_GUCTL3_RESERVED_31_17(x)  VTSS_ENCODE_BITFIELD(x,17,15)
#define  VTSS_M_USB3_GUCTL3_RESERVED_31_17     VTSS_ENCODE_BITMASK(17,15)
#define  VTSS_X_USB3_GUCTL3_RESERVED_31_17(x)  VTSS_EXTRACT_BITFIELD(x,17,15)


/**
 * \brief Global Device TX FIFO DMA Priority Register

This register specifies the relative DMA priority level among the Device TXFIFOs (one per IN endpoint). Each register bit[n] controls the priority (1: high, 0: low) of each TXFIFO[n]. When multiple TXFIFOs compete for DMA service at a given time (that is, multiple TXQs contain TX DMA requests and their corresponding TXFIFOs have space available), the TX DMA arbiter grants access on a packet-basis in the following manner:
 - 1. High-priority TXFIFOs are granted access using round-robin arbitration
 - 2. Low-priority TXFIFOs are granted access using round-robin arbitration only after the high-priority TXFIFOs have no further processing to do (that is, either the TXQs are empty or the corresponding TXFIFOs are full).
For scatter-gather packets, the arbiter grants successive DMA requests to the same FIFO until the entire packet is completed.

When configuring periodic IN endpoints, software must set register bit[n]=1, where n is the TXFIFO assignment. This ensures that the DMA for isochronous or interrupt IN endpoints are prioritized over bulk or control IN endpoints.

This register is present only when the controller is configured to operate in the device mode (includes DRD mode). The register size corresponds to the number of Device IN endpoints.

Note
 - Since the device mode uses only one RXFIFO, there is no Device RXFIFO DMA Priority Register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GTXFIFOPRIDEV
 */
#define VTSS_USB3_GTXFIFOPRIDEV              VTSS_IOREG(VTSS_TO_USB3,0x3184)

/**
 * \brief
 * Device TxFIFO priority
 *
 * \details
 * Field: ::VTSS_USB3_GTXFIFOPRIDEV . GTXFIFOPRIDEV
 */
#define  VTSS_F_USB3_GTXFIFOPRIDEV_GTXFIFOPRIDEV(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_USB3_GTXFIFOPRIDEV_GTXFIFOPRIDEV     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_USB3_GTXFIFOPRIDEV_GTXFIFOPRIDEV(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GTXFIFOPRIDEV . RESERVED_31_N
 */
#define  VTSS_F_USB3_GTXFIFOPRIDEV_RESERVED_31_N(x)  VTSS_ENCODE_BITFIELD(x,4,28)
#define  VTSS_M_USB3_GTXFIFOPRIDEV_RESERVED_31_N     VTSS_ENCODE_BITMASK(4,28)
#define  VTSS_X_USB3_GTXFIFOPRIDEV_RESERVED_31_N(x)  VTSS_EXTRACT_BITFIELD(x,4,28)


/**
 * \brief Global Host TX FIFO DMA Priority Register

This register specifies the relative DMA priority level among the Host TXFIFOs (one per USB bus instance) within the associated speed group (SS or HS/FSLS). Each register bit[n] controls the priority (1: high, 0: low) of TXFIFO[n] within a speed group. When multiple TXFIFOs compete for DMA service at a given time (i.e., multiple TXQs contain TX DMA requests and their corresponding TXFIFOs have space available), the TX DMA arbiter grants access on a packet-basis in the following manner:
 - 1. Among the FIFOs in the same speed group (SS or HS/FSLS):
 a. High-priority TXFIFOs are granted access using round-robin arbitration
 b. Low-priority TXFIFOs are granted access using round-robin arbitration only after the high-priority TXFIFOs have no further processing to do (that is, either the TXQs are empty or the corresponding TXFIFOs are full).
 - 2. The TX DMA arbiter prioritizes the SS speed group or HS/FSLS speed group according to the ratio programmed in the GDMAHLRATIO register.
For scatter-gather packets, the arbiter grants successive DMA requests to the same FIFO until the entire packet is completed.

This register is present only when the controller is configured to operate in the host mode (includes DRD mode). The register size corresponds to the number of configured USB bus instances; for example, in the default configuration, there are 3 USB bus instances (1 SS, 1 HS, and 1 FSLS).
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GTXFIFOPRIHST
 */
#define VTSS_USB3_GTXFIFOPRIHST              VTSS_IOREG(VTSS_TO_USB3,0x3186)

/**
 * \brief
 * Host TxFIFO priority
 *
 * \details
 * Field: ::VTSS_USB3_GTXFIFOPRIHST . GTXFIFOPRIHST
 */
#define  VTSS_F_USB3_GTXFIFOPRIHST_GTXFIFOPRIHST(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_USB3_GTXFIFOPRIHST_GTXFIFOPRIHST     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_USB3_GTXFIFOPRIHST_GTXFIFOPRIHST(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GTXFIFOPRIHST . GTXFIFOPRIHST_RESERVED_31_16
 */
#define  VTSS_F_USB3_GTXFIFOPRIHST_GTXFIFOPRIHST_RESERVED_31_16(x)  VTSS_ENCODE_BITFIELD(x,3,29)
#define  VTSS_M_USB3_GTXFIFOPRIHST_GTXFIFOPRIHST_RESERVED_31_16     VTSS_ENCODE_BITMASK(3,29)
#define  VTSS_X_USB3_GTXFIFOPRIHST_GTXFIFOPRIHST_RESERVED_31_16(x)  VTSS_EXTRACT_BITFIELD(x,3,29)


/**
 * \brief Global Host RX FIFO DMA Priority Register

This register specifies the relative DMA priority level among the Host RXFIFOs (one per USB bus instance) within the associated speed group (SS or HS/FSLS). Each register bit[n] controls the priority (1: high, 0: low) of RXFIFO[n] within a speed group. When multiple RXFIFOs compete for DMA service at a given time (i.e., multiple RXQs contain RX DMA requests and their corresponding RXFIFOs have data available), the RX DMA arbiter grants access on a packet-basis in the following manner:
 - 1. Among the FIFOs in the same speed group (SS or HS/FSLS):
 a. High-priority RXFIFOs are granted access using round-robin arbitration
 b. Low-priority RXFIFOs are granted access using round-robin arbitration only after high-priority RXFIFOs have no further processing to do (that is, either the RXQs are empty or the corresponding RXFIFOs do not have the required data).
 - 2. The RX DMA arbiter prioritizes the SS speed group or HS/FSLS speed group according to the ratio programmed in the GDMAHLRATIO register.
For scatter-gather packets, the arbiter grants successive DMA requests to the same FIFO until the entire packet is completed.

This register is present only when the controller is configured to operate in the host mode (includes DRD mode). The register size corresponds to the number of configured USB bus instances; for example, in the default configuration, there are 3 USB bus instances (1 SS, 1 HS, and 1 FSLS).
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GRXFIFOPRIHST
 */
#define VTSS_USB3_GRXFIFOPRIHST              VTSS_IOREG(VTSS_TO_USB3,0x3187)

/**
 * \brief
 * Host RxFIFO priority
 *
 * \details
 * Field: ::VTSS_USB3_GRXFIFOPRIHST . GRXFIFOPRIHST
 */
#define  VTSS_F_USB3_GRXFIFOPRIHST_GRXFIFOPRIHST(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_USB3_GRXFIFOPRIHST_GRXFIFOPRIHST     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_USB3_GRXFIFOPRIHST_GRXFIFOPRIHST(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GRXFIFOPRIHST . GRXFIFOPRIHST_RESERVED_31_16
 */
#define  VTSS_F_USB3_GRXFIFOPRIHST_GRXFIFOPRIHST_RESERVED_31_16(x)  VTSS_ENCODE_BITFIELD(x,3,29)
#define  VTSS_M_USB3_GRXFIFOPRIHST_GRXFIFOPRIHST_RESERVED_31_16     VTSS_ENCODE_BITMASK(3,29)
#define  VTSS_X_USB3_GRXFIFOPRIHST_GRXFIFOPRIHST_RESERVED_31_16(x)  VTSS_EXTRACT_BITFIELD(x,3,29)


/**
 * \brief Global Host FIFO DMA High-Low Priority Ratio Register

This register specifies the relative priority of the SS FIFOs with respect to the HS/FSLS FIFOs. The DMA arbiter prioritizes the HS/FSLS round-robin arbiter group every DMA High-Low Priority Ratio grants as indicated in the register separately for TX and RX.

To illustrate, consider that all FIFOs are requesting access simultaneously, and the ratio is 4. SS gets priority for 4 packets, HS/FSLS gets priority for 1 packet, SS gets priority for 4 packets, HS/FSLS gets priority for 1 packet, and so on.

If FIFOs from both speed groups are not requesting access simultaneously then,
 - if SS got grants 4 out of the last 4 times, then HS/FSLS get the priority on any future request.
 - if HS/FSLS got the grant last time, SS gets the priority on the next request.
 - if there is a valid request on either SS or HS/FSLS, a grant is always awarded; there is no idle.
This register is present if the controller is configured to operate in host mode (includes DRD).
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GDMAHLRATIO
 */
#define VTSS_USB3_GDMAHLRATIO                VTSS_IOREG(VTSS_TO_USB3,0x3189)

/**
 * \brief
 * Host TXFIFO DMA High-Low Priority
 *
 * \details
 * Field: ::VTSS_USB3_GDMAHLRATIO . HSTTXFIFO
 */
#define  VTSS_F_USB3_GDMAHLRATIO_HSTTXFIFO(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_USB3_GDMAHLRATIO_HSTTXFIFO     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_USB3_GDMAHLRATIO_HSTTXFIFO(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GDMAHLRATIO . RESERVED_7_5
 */
#define  VTSS_F_USB3_GDMAHLRATIO_RESERVED_7_5(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_USB3_GDMAHLRATIO_RESERVED_7_5     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_USB3_GDMAHLRATIO_RESERVED_7_5(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * Host RXFIFO DMA High-Low Priority
 *
 * \details
 * Field: ::VTSS_USB3_GDMAHLRATIO . HSTRXFIFO
 */
#define  VTSS_F_USB3_GDMAHLRATIO_HSTRXFIFO(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_USB3_GDMAHLRATIO_HSTRXFIFO     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_USB3_GDMAHLRATIO_HSTRXFIFO(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GDMAHLRATIO . GDMAHLRATIO_RESERVED_31_13
 */
#define  VTSS_F_USB3_GDMAHLRATIO_GDMAHLRATIO_RESERVED_31_13(x)  VTSS_ENCODE_BITFIELD(x,13,19)
#define  VTSS_M_USB3_GDMAHLRATIO_GDMAHLRATIO_RESERVED_31_13     VTSS_ENCODE_BITMASK(13,19)
#define  VTSS_X_USB3_GDMAHLRATIO_GDMAHLRATIO_RESERVED_31_13(x)  VTSS_EXTRACT_BITFIELD(x,13,19)


/**
 * \brief Global Frame Length Adjustment Register

This register provides options for the software to control the controller behavior with respect to SOF (Start of Frame) and ITP (Isochronous Timestamp Packet) timers and frame timer functionality. It provides an option to override the fladj_30mhz_reg sideband signal. In addition, it enables running SOF or ITP frame timer counters completely from the ref_clk. This facilitates hardware LPM in host mode with the SOF or ITP counters being run from the ref_clk signal.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GFLADJ
 */
#define VTSS_USB3_GFLADJ                     VTSS_IOREG(VTSS_TO_USB3,0x318c)

/**
 * \brief
 * GFLADJ_30MHZ
 *
 * This field indicates the value that is used for frame length adjustment
 * instead of considering from the sideband input signal fladj_30mhz_reg.
 *
 * This enables post-silicon frame length adjustment in case the input
 * signal fladj_30mhz_reg is connected to a wrong value or is not valid.
 *
 * For details on how to set this value, refer to section 5.2.4, "Frame
 * Length Adjustment Register (FLADJ)," of the	xHCI Specification.
 *
 * \details
 * Field: ::VTSS_USB3_GFLADJ . GFLADJ_30MHZ
 */
#define  VTSS_F_USB3_GFLADJ_GFLADJ_30MHZ(x)   VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_USB3_GFLADJ_GFLADJ_30MHZ      VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_USB3_GFLADJ_GFLADJ_30MHZ(x)   VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * Reserved for future use
 *
 * \details
 * Field: ::VTSS_USB3_GFLADJ . RESERVED_6
 */
#define  VTSS_F_USB3_GFLADJ_RESERVED_6(x)     VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_USB3_GFLADJ_RESERVED_6        VTSS_BIT(6)
#define  VTSS_X_USB3_GFLADJ_RESERVED_6(x)     VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * GFLADJ_30MHZ_SDBND_SEL
 *
 * This field selects whether to use the input signal fladj_30mhz_reg or
 * the GFLADJ.GFLADJ_30MHZ to adjust the frame length for the SOF/ITP.
 * When this bit is set to,
 *  - 1, the controller uses the register field GFLADJ.GFLADJ_30MHZ value
 *  - 0, the controller uses the input signal fladj_30mhz_reg value
 *
 * \details
 * Field: ::VTSS_USB3_GFLADJ . GFLADJ_30MHZ_SDBND_SEL
 */
#define  VTSS_F_USB3_GFLADJ_GFLADJ_30MHZ_SDBND_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_USB3_GFLADJ_GFLADJ_30MHZ_SDBND_SEL  VTSS_BIT(7)
#define  VTSS_X_USB3_GFLADJ_GFLADJ_30MHZ_SDBND_SEL(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * This field indicates the frame length adjustment to be applied when
 * SOF/ITP counter is running on the ref_clk.
 *
 * This register value is used to adjust the ITP interval when
 * GCTL[SOFITPSYNC] is set to '1'; SOF and ITP interval when
 * GLADJ.GFLADJ_REFCLK_LPM_SEL is set to '1'.
 *
 * This field must be programmed to a non-zero value only if
 * GFLADJ_REFCLK_LPM_SEL is set to '1' or GCTL.SOFITPSYNC is set to '1'.
 *
 * The value is derived as follows:
 *
 * FLADJ_REF_CLK_FLADJ=((125000/ref_clk_period_integer)-(125000/ref_clk_per
 * iod)) * ref_clk_period
 * where
 *  - the ref_clk_period_integer is the integer value of the ref_clk period
 * got by truncating the decimal (fractional) value that is programmed in
 * the GUCTL.REF_CLK_PERIOD field.
 *  - the ref_clk_period is the ref_clk period including the fractional
 * value.
 * Examples:
 * If the ref_clk is 24 MHz then
 *  - GUCTL.REF_CLK_PERIOD = 41
 *  - GFLADJ.GLADJ_REFCLK_FLADJ = ((125000/41)-(125000/41.6666))*41.6666 =
 * 2032 (ignoring the fractional value)
 * If the ref_clk is 48 MHz then
 *  - GUCTL.REF_CLK_PERIOD = 20
 *  - GFLADJ.GLADJ_REFCLK_FLADJ = ((125000/20)-(125000/20.8333))*20.8333 =
 * 5208 (ignoring the fractional value)
 *
 * \details
 * Field: ::VTSS_USB3_GFLADJ . GFLADJ_REFCLK_FLADJ
 */
#define  VTSS_F_USB3_GFLADJ_GFLADJ_REFCLK_FLADJ(x)  VTSS_ENCODE_BITFIELD(x,8,14)
#define  VTSS_M_USB3_GFLADJ_GFLADJ_REFCLK_FLADJ     VTSS_ENCODE_BITMASK(8,14)
#define  VTSS_X_USB3_GFLADJ_GFLADJ_REFCLK_FLADJ(x)  VTSS_EXTRACT_BITFIELD(x,8,14)

/**
 * \brief
 * Reserved for future use
 *
 * \details
 * Field: ::VTSS_USB3_GFLADJ . RESERVED_22
 */
#define  VTSS_F_USB3_GFLADJ_RESERVED_22(x)    VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_USB3_GFLADJ_RESERVED_22       VTSS_BIT(22)
#define  VTSS_X_USB3_GFLADJ_RESERVED_22(x)    VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * This bit enables the functionality of running SOF/ITP counters on the
 * ref_clk.
 *
 * This bit must not be set to '1' if GCTL.SOFITPSYNC bit is set to '1'.
 *
 * Similarly, if GFLADJ_REFCLK_LPM_SEL set to '1', GCTL.SOFITPSYNC must not
 * be set to '1'.
 *
 *  In device mode, setting this bit to '1' enables SOF tracking using
 * ref_clk.
 *
 * When GFLADJ_REFCLK_LPM_SEL is set to '1' the overloading of the suspend
 * control of the USB 2.0 first port PHY (UTMI/ULPI) with USB 3.0 port
 * states is removed.
 *
 * For example, for Synopsys PHY, the COMMONONN signal can be tied to '1'.
 *
 * Note that the ref_clk frequencies supported in this mode are
 * 16/17/19.2/20/24/39.7/40 MHz. The utmi_clk[0] signal of the controller
 * must be connected to the FREECLK of the PHY.
 *
 * Note: If you set this bit to '1', the GUSB2PHYCFG.U2_FREECLK_EXISTS bit
 * must be set to '0'.

 *
 * \details
 * Field: ::VTSS_USB3_GFLADJ . GFLADJ_REFCLK_LPM_SEL
 */
#define  VTSS_F_USB3_GFLADJ_GFLADJ_REFCLK_LPM_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_USB3_GFLADJ_GFLADJ_REFCLK_LPM_SEL  VTSS_BIT(23)
#define  VTSS_X_USB3_GFLADJ_GFLADJ_REFCLK_LPM_SEL(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * This field indicates the decrement value that the controller applies for
 * each ref_clk in order to derive a frame timer in terms of a 240-MHz
 * clock.
 *
 * This field must be programmed to a non-zero value only if
 * GFLADJ_REFCLK_LPM_SEL is set to '1'.
 *
 * The value is derived as follows:
 *
 * GFLADJ_REFCLK_240MHZ_DECR = 240/ref_clk_frequency
 *
 * Examples:
 * If the ref_clk is 24 MHz then
 *  - GUCTL.REF_CLK_PERIOD = 41
 *  - GFLADJ.GFLADJ_REFCLK_240MHZ_DECR = 240/24 = 10
 * If the ref_clk is 48 MHz then
 *  - GUCTL.REF_CLK_PERIOD = 20
 *  - GFLADJ.GFLADJ_REFCLK_240MHZ_DECR = 240/48 = 5
 * If the ref_clk is 17 MHz then
 *  - GUCTL.REF_CLK_PERIOD = 58
 *  - GFLADJ.GFLADJ_REFCLK_240MHZ_DECR = 240/17 = 14
 *
 * \details
 * Field: ::VTSS_USB3_GFLADJ . GFLADJ_REFCLK_240MHZ_DECR
 */
#define  VTSS_F_USB3_GFLADJ_GFLADJ_REFCLK_240MHZ_DECR(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_USB3_GFLADJ_GFLADJ_REFCLK_240MHZ_DECR     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_USB3_GFLADJ_GFLADJ_REFCLK_240MHZ_DECR(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * GFLADJ_REFCLK_240MHZDECR_PLS1
 *
 * This field indicates that the decrement value that the controller
 * applies for each ref_clk  must be GFLADJ_REFCLK_240MHZ_DECR and
 * GFLADJ_REFCLK_240MHZ_DECR +1 alternatively on each ref_clk.
 *
 * Set this bit to a '1' only if GFLADJ_REFCLK_LPM_SEL is set to '1' and
 * the fractional component of 240/ref_frequency is greater than or equal
 * to 0.5.
 *
 * Examples:
 *
 * If the ref_clk is 19.2 MHz then
 *  - GUCTL.REF_CLK_PERIOD = 52
 *  - GFLADJ.GFLADJ_REFCLK_240MHZ_DECR = (240/19.2) = 12.5
 *  - GFLADJ.GFLADJ_REFCLK_240MHZDECR_PLS1 = 1
 * If the ref_clk is 24 MHz then
 *  - GUCTL.REF_CLK_PERIOD = 41
 *  - GFLADJ.GFLADJ_REFCLK_240MHZ_DECR = (240/24) = 10
 *  - GFLADJ.GFLADJ_REFCLK_240MHZDECR_PLS1 = 0
 *
 * \details
 * Field: ::VTSS_USB3_GFLADJ . GFLADJ_REFCLK_240MHZDECR_PLS1
 */
#define  VTSS_F_USB3_GFLADJ_GFLADJ_REFCLK_240MHZDECR_PLS1(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_USB3_GFLADJ_GFLADJ_REFCLK_240MHZDECR_PLS1  VTSS_BIT(31)
#define  VTSS_X_USB3_GFLADJ_GFLADJ_REFCLK_240MHZDECR_PLS1(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief Global USB2 PHY Configuration Register

The application must program this register before starting any transactions on either the SoC bus or the USB.

In Device-only configurations, only one register is needed.
In Host mode, per-port registers are implemented.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GUSB2PHYCFG
 */
#define VTSS_USB3_GUSB2PHYCFG                VTSS_IOREG(VTSS_TO_USB3,0x3080)

/**
 * \brief
 * HS/FS Timeout Calibration (TOutCal)
 *
 * The number of PHY clocks, as indicated by the application in this field,
 * is multiplied by a bit-time factor; this factor is added to the
 * high-speed/full-speed interpacket timeout duration in the controller to
 * account for additional delays introduced by the PHY. This may be
 * required, since the delay introduced by the PHY in generating the
 * linestate condition may vary among PHYs.
 *
 * The USB standard timeout value for high-speed operation is 736 to 816
 * (inclusive) bit times. The USB standard timeout value for full-speed
 * operation is 16 to 18 (inclusive) bit times. The application must
 * program this field based on the speed of connection. The number of bit
 * times added per PHY clock are:
 *
 * High-speed operation:
 *  - One 30-MHz PHY clock = 16 bit times
 *  - One 60-MHz PHY clock = 8 bit times
 * Full-speed operation:
 *  - One 30-MHz PHY clock = 0.4 bit times
 *  - One 60-MHz PHY clock = 0.2 bit times
 *  - One 48-MHz PHY clock = 0.25 bit times
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . TOUTCAL
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_TOUTCAL(x)   VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_USB3_GUSB2PHYCFG_TOUTCAL      VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_USB3_GUSB2PHYCFG_TOUTCAL(x)   VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * PHY Interface (PHYIf)
 *
 * If UTMI+ is selected, the application uses this bit to configure the
 * controller to support a UTMI+ PHY with an 8- or 16-bit interface.
 *  - 1'b0: 8 bits
 *  - 1'b1: 16 bits
 * ULPI Mode: 1'b0
 *
 * Note:
 *  - All the enabled 2.0 ports must have the same clock frequency as Port0
 * clock frequency (utmi_clk[0]).
 *  - The UTMI 8-bit and 16-bit modes cannot be used together for different
 * ports at the same time (that is, all the ports must be in 8-bit mode, or
 * all of them must be in 16-bit mode, at a time).
 *  - If any of the USB 2.0 ports is selected as ULPI port for operation,
 * then all the USB 2.0 ports must be operating at 60 MHz.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . PHYIF
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_PHYIF(x)     VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_USB3_GUSB2PHYCFG_PHYIF        VTSS_BIT(3)
#define  VTSS_X_USB3_GUSB2PHYCFG_PHYIF(x)     VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * ULPI or UTMI+ Select (ULPI_UTMI_Sel)
 *
 * The application uses this bit to select a UTMI+ or ULPI Interface.
 *  - 1'b0: UTMI+ Interface
 *  - 1'b1: ULPI Interface
 * This bit is writable only if UTMI+ and ULPI is specified for High-Speed
 * PHY Interface(s) in coreConsultant configuration
 * (DWC_USB3_HSPHY_INTERFACE = 3).
 * Otherwise, this bit is read-only and the value depends on the interface
 * selected through DWC_USB3_HSPHY_INTERFACE.

 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . ULPI_UTMI_SEL
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_ULPI_UTMI_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_USB3_GUSB2PHYCFG_ULPI_UTMI_SEL  VTSS_BIT(4)
#define  VTSS_X_USB3_GUSB2PHYCFG_ULPI_UTMI_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Full-Speed Serial Interface Select (FSIntf)
 *
 * The application uses this bit to select a unidirectional or
 * bidirectional USB 1.1 full-speed serial transceiver interface.
 *  - 1'b0: 6-pin unidirectional full-speed serial interface. This bit is
 * set to 0 with Read Only access.
 *  - 1'b1: 3-pin bidirectional full-speed serial interface. This bit is
 * set to 0 with Read Only access.
 * Note: USB 1.1 full-speed serial interface is not supported. This bit
 * always reads as 1'b0.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . FSINTF
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_FSINTF(x)    VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_USB3_GUSB2PHYCFG_FSINTF       VTSS_BIT(5)
#define  VTSS_X_USB3_GUSB2PHYCFG_FSINTF(x)    VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Suspend USB2.0 HS/FS/LS PHY (SusPHY)
 *
 * When set, USB2.0 PHY enters Suspend mode if Suspend conditions are
 * valid.
 *
 * For DRD configurations, it is recommended that this bit is set to 0
 * during coreConsultant configuration. If it is set to 1, then the
 * application must  clear this bit after power-on reset. Application needs
 * to set it to 1 after the controller initialization completes.
 *
 * For all other configurations, this bit can be set to 1 during controller
 * configuration.
 *
 * Note:
 *  - In host mode, on reset, this bit is set to 1. Software can override
 * this bit after reset.
 *  - In device mode, before issuing any device endpoint command when
 * operating in 2.0 speeds, disable this bit and enable it after the
 * command completes. If you issue a command without disabling this bit
 * when the device is in L2 state and if mac2_clk (utmi_clk/ulpi_clk) is
 * gated off, the command will not get completed.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . SUSPENDUSB20
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_SUSPENDUSB20(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_USB3_GUSB2PHYCFG_SUSPENDUSB20  VTSS_BIT(6)
#define  VTSS_X_USB3_GUSB2PHYCFG_SUSPENDUSB20(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * USB 2.0 High-Speed PHY or USB 1.1 Full-Speed Serial Transceiver Select
 *
 * The application uses this bit to select a high-speed PHY or a full-speed
 * transceiver.
 *  - 1'b0: USB 2.0 high-speed UTMI+ or ULPI PHY. This bit is always 0,
 * with Write Only access.
 *  - 1'b1: USB 1.1 full-speed serial transceiver. This bit is always 1,
 * with Write Only access.
 * If both interface types are selected in coreConsultant (that is,
 * parameters' values are not zero), the application uses this bit to
 * select the active interface is active, with Read-Write bit access.
 *
 * Note: USB 1.1 full-serial transceiver is not supported. This bit always
 * reads as 1'b0.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . PHYSEL
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_PHYSEL(x)    VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_USB3_GUSB2PHYCFG_PHYSEL       VTSS_BIT(7)
#define  VTSS_X_USB3_GUSB2PHYCFG_PHYSEL(x)    VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Enable utmi_sleep_n and utmi_l1_suspend_n (EnblSlpM)
 *
 * The application uses this bit to control utmi_sleep_n and
 * utmi_l1_suspend_n assertion to the PHY in the L1 state.
 *  - 1'b0: utmi_sleep_n and utmi_l1_suspend_n assertion from the
 * controller is not transferred to the external PHY.
 *  - 1'b1: utmi_sleep_n and utmi_l1_suspend_n assertion from the
 * controller is transferred to the external PHY.
 * Note: This bit must be set high for Port0 if Synopsys PHY is used.
 *
 * Note: In Device mode - Before issuing any device endpoint command when
 * operating in 2.0 speeds, disable this bit and enable it after the
 * command completes. Without disabling this bit, if a command is issued
 * when the device is in L1 state and if mac2_clk (utmi_clk/ulpi_clk) is
 * gated off, the command will not get completed.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . ENBLSLPM
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_ENBLSLPM(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_USB3_GUSB2PHYCFG_ENBLSLPM     VTSS_BIT(8)
#define  VTSS_X_USB3_GUSB2PHYCFG_ENBLSLPM(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Transceiver Delay:
 *
 * Enables a delay between the assertion of the UTMI/ULPI Transceiver
 * Select signal (for HS) and the assertion of the TxValid signal during a
 * HS Chirp.
 *
 * When this bit is set to 1, a delay (of approximately 2.5 us) is
 * introduced from the time when the Transceiver Select is set to 2'b00
 * (HS) to the time the TxValid is driven to 0 for sending the chirp-K.
 * This delay is required for some UTMI/ULPI PHYs.
 *
 * Note:
 *  - If you enable the hibernation feature when the device controller
 * comes out of power-off, you must re-initialize this bit with the
 * appropriate value because the controller does not save and restore this
 * bit value during hibernation.
 *  - This bit is valid only in device mode.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . XCVRDLY
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_XCVRDLY(x)   VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_USB3_GUSB2PHYCFG_XCVRDLY      VTSS_BIT(9)
#define  VTSS_X_USB3_GUSB2PHYCFG_XCVRDLY(x)   VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * USB 2.0 Turnaround Time (USBTrdTim)
 *
 * Sets the turnaround time in PHY clocks.
 *
 * Specifies the response time for a MAC request to the Packet FIFO
 * Controller (PFC) to fetch data from the DFIFO (SPRAM).
 *
 * The following are the required values for the minimum SoC bus frequency
 * of 60 MHz. USB turnaround time is a critical certification criteria when
 * using long cables and five hub levels.
 *
 * The required values for this field:
 *  - 4'h5: When the MAC interface is 16-bit UTMI+.
 *  - 4'h9: When the MAC interface is 8-bit UTMI+/ULPI.
 * If SoC bus clock is less than 60 MHz, and USB turnaround time is not
 * critical, this field can be set to a larger value.
 *
 * Note: This field is valid only in device mode.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . USBTRDTIM
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_USBTRDTIM(x)  VTSS_ENCODE_BITFIELD(x,10,4)
#define  VTSS_M_USB3_GUSB2PHYCFG_USBTRDTIM     VTSS_ENCODE_BITMASK(10,4)
#define  VTSS_X_USB3_GUSB2PHYCFG_USBTRDTIM(x)  VTSS_EXTRACT_BITFIELD(x,10,4)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . GUSB2PHYCFG_RESERVED_14
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_GUSB2PHYCFG_RESERVED_14(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_USB3_GUSB2PHYCFG_GUSB2PHYCFG_RESERVED_14  VTSS_BIT(14)
#define  VTSS_X_USB3_GUSB2PHYCFG_GUSB2PHYCFG_RESERVED_14(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * ULPI Auto Resume (ULPIAutoRes)
 *
 * Sets the AutoResume bit in Interface Control register on the ULPI PHY.
 *  - 1'b0: PHY does not use the AutoResume feature.
 *  - 1'b1: PHY uses the AutoResume feature.
 * Valid only when RTL parameter DWC_USB3_HSPHY_INTERFACE = 2 or 3
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . ULPIAUTORES
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_ULPIAUTORES(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_USB3_GUSB2PHYCFG_ULPIAUTORES  VTSS_BIT(15)
#define  VTSS_X_USB3_GUSB2PHYCFG_ULPIAUTORES(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . RESERVED_16
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_RESERVED_16(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_USB3_GUSB2PHYCFG_RESERVED_16  VTSS_BIT(16)
#define  VTSS_X_USB3_GUSB2PHYCFG_RESERVED_16(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * ULPI External VBUS Drive (ULPIExtVbusDrv)
 *
 * Selects supply source to drive 5V on VBUS, in the ULPI PHY.
 *  - 1'b0: PHY drives VBUS with internal charge pump (default).
 *  - 1'b1: PHY drives VBUS with an external supply.
 * (Only when RTL parameter DWC_USB3_HSPHY_INTERFACE = 2 or 3)
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . ULPIEXTVBUSDRV
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_ULPIEXTVBUSDRV(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_USB3_GUSB2PHYCFG_ULPIEXTVBUSDRV  VTSS_BIT(17)
#define  VTSS_X_USB3_GUSB2PHYCFG_ULPIEXTVBUSDRV(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * ULPI External VBUS Indicator (ULPIExtVbusIndicator)
 *
 * Indicates the ULPI PHY VBUS over-current indicator.
 *  - 1'b0: PHY uses an internal VBUS valid comparator.
 *  - 1'b1: PHY uses an external VBUS valid comparator.
 * Valid only when RTL parameter DWC_USB3_HSPHY_INTERFACE = 2 or 3
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . ULPIEXTVBUSINDIACTOR
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_ULPIEXTVBUSINDIACTOR(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_USB3_GUSB2PHYCFG_ULPIEXTVBUSINDIACTOR  VTSS_BIT(18)
#define  VTSS_X_USB3_GUSB2PHYCFG_ULPIEXTVBUSINDIACTOR(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * LS Inter-Packet Time (LSIPD)
 *
 * This field indicates the value of Tx-to-Tx packet gap for LS devices.
 * The encoding is as follows:
 *  - 0: 2 bit times
 *  - 1: 2.5 bit times
 *  - 2: 3 bit times
 *  - 3: 3.5 bit times
 *  - 4: 4 bit times
 *  - 5: 4.5 bit times
 *  - 6: 5 bit times
 *  - 7: 5.5 bit times
 * Note:
 *  - This field is applicable only in Host mode.
 *  - For normal operation (to work with most LS devices), set the default
 * value of this field to 3'h2 (3 bit times).
 *  - The programmable LS device inter-packet gap and turnaround delays are
 * provided to support some legacy LS devices that might require different
 * delays than the default/fixed ones. For instance, the AOpen LS mouse
 * requires 3 bit times of inter-packet gap to work correctly.
 *  - Include your PHY delays when programming the LSIPD/LSTRDTIM values.
 * For example, if your PHY's TxEndDelay in LS mode is 30 UTMI/ULPI CLKs,
 * then subtract this delay (~1 LS bit time) from the device's delay
 * requirement.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . LSIPD
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_LSIPD(x)     VTSS_ENCODE_BITFIELD(x,19,3)
#define  VTSS_M_USB3_GUSB2PHYCFG_LSIPD        VTSS_ENCODE_BITMASK(19,3)
#define  VTSS_X_USB3_GUSB2PHYCFG_LSIPD(x)     VTSS_EXTRACT_BITFIELD(x,19,3)

/**
 * \brief
 * LS Turnaround Time (LSTRDTIM)
 *
 * This field indicates the value of the Rx-to-Tx packet gap for LS
 * devices. The encoding is as follows:
 *  - 0: 2 bit times
 *  - 1: 2.5 bit times
 *  - 2: 3 bit times
 *  - 3: 3.5 bit times
 *  - 4: 4 bit times
 *  - 5: 4.5 bit times
 *  - 6: 5 bit times
 *  - 7: 5.5 bit times
 * Note:
 *  - This field is applicable only in Host mode.
 *  - For normal operation (to work with most LS devices), set the default
 * value of this field to 3'h0 (2 bit times).
 *  - The programmable LS device inter-packet gap and turnaround delays are
 * provided to support some legacy LS devices that might require different
 * delays than the default/fixed ones. For instance, the Open LS mouse
 * requires 3 bit times of inter-packet gap to work correctly.
 *  - Include your PHY delays when programming the LSIPD/LSTRDTIM values.
 * For example, if your PHY's TxEndDelay in LS mode is 30 UTMI/ULPI CLKs,
 * then subtract this delay (~1 LS bit time) from the device's delay
 * requirement.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . LSTRD
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_LSTRD(x)     VTSS_ENCODE_BITFIELD(x,22,3)
#define  VTSS_M_USB3_GUSB2PHYCFG_LSTRD        VTSS_ENCODE_BITMASK(22,3)
#define  VTSS_X_USB3_GUSB2PHYCFG_LSTRD(x)     VTSS_EXTRACT_BITFIELD(x,22,3)

/**
 * \brief
 * Overriding the FS/LS disconnect time to 32us.
 *  - If this value is 0, the FS/LS disconnect time is set to 2.5us as per
 * the USB specification.
 *  - If this value is non-0, the disconnect detection time is set to 32us.
 * Normally, this value is set to 0. However, if the USB 2.0 PHYs introduce
 * noise on the UTMI linestate and cause SE0 glitches longer than 2.5us,
 * then a false disconnect condition may get triggered. To avoid
 * interoperability issues with these PHYs, this bit can be set to 1.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . OVRD_FSLS_DISC_TIME
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_OVRD_FSLS_DISC_TIME(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_USB3_GUSB2PHYCFG_OVRD_FSLS_DISC_TIME  VTSS_BIT(25)
#define  VTSS_X_USB3_GUSB2PHYCFG_OVRD_FSLS_DISC_TIME(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * INV_SEL_HSIC
 *
 * The application driver uses this bit to control the HSIC enable/disable
 * function. When set to '1', this bit overrides and functionally inverts
 * the "if_select_hsic" input signal.
 * If {INV_SEL_HSIC, if_select_hsic} is:
 *  - 00: HSIC Capability is disabled.
 *  - 01: HSIC Capability is enabled.
 *  - 10: HSIC Capability is enabled.
 *  - 11: HSIC Capability is disabled.
 * If the controller operates as non-HSIC-capable, it can only connect to
 * non-HSIC-capable PHYs. If it operates as HSIC-capable, it can connect to
 * HSIC-capable PHYs.
 *
 * This bit is reserved if the DWC_USB3_ENABLE_HSIC parameter is set to
 * '0'. When selecting the HSIC feature, set the host side to HSIC mode
 * first, then set the device mode side. If the device side is set to HSIC
 * mode first and if the host does not see a connection in HSIC mode, then
 * you must de-select the device HSIC mode and select it again using the
 * if_select_hsic setting or register bit GUSB2PHYCFGn[26] to ensure that
 * the device can connect to the host.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . INV_SEL_HSIC
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_INV_SEL_HSIC(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_USB3_GUSB2PHYCFG_INV_SEL_HSIC  VTSS_BIT(26)
#define  VTSS_X_USB3_GUSB2PHYCFG_INV_SEL_HSIC(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * HSIC_CON_WIDTH_ADJ
 *
 * This bit is used in the HSIC device mode of operation. By default, the
 * connect duration for the HSIC device controller is thrice the strobe
 * period. You can change this duration to 4, 5, or 6 times the strobe
 * period by setting the value of this field to 1, 2, or 3. This value is
 * added to the default connect duration.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . HSIC_CON_WIDTH_ADJ
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_HSIC_CON_WIDTH_ADJ(x)  VTSS_ENCODE_BITFIELD(x,27,2)
#define  VTSS_M_USB3_GUSB2PHYCFG_HSIC_CON_WIDTH_ADJ     VTSS_ENCODE_BITMASK(27,2)
#define  VTSS_X_USB3_GUSB2PHYCFG_HSIC_CON_WIDTH_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,27,2)

/**
 * \brief
 * ULPI_LPM_WITH_OPMODE_CHK
 *
 * Support the LPM over ULPI without NOPID token to the ULPI PHY.
 *
 * If this bit is set, the ULPI PHY is expected to qualify the EXT PID with
 * OPMODE=2'b00 for LPM and not treat it as a NOPID. Check with your PHY
 * vendor about your PHY behavior. This bit is valid only when the
 * DWC_USB3_HSPHY_INTERFACE parameter is 2 or 3.
 *  - 1'b0: A NOPID is sent before sending an EXTPID for LPM;
 *  - 1'b1: An EXTPID is sent without previously sending a NOPID;
 * Note: This bit is valid only in host mode. This bit should be '0' for
 * Synopsys PHY.

 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . ULPI_LPM_WITH_OPMODE_CHK
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_ULPI_LPM_WITH_OPMODE_CHK(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_USB3_GUSB2PHYCFG_ULPI_LPM_WITH_OPMODE_CHK  VTSS_BIT(29)
#define  VTSS_X_USB3_GUSB2PHYCFG_ULPI_LPM_WITH_OPMODE_CHK(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * U2_FREECLK_EXISTS
 *
 * Specifies whether your USB 2.0 PHY provides a free-running PHY clock,
 * which is active when the clock control input is active.
 *
 * If your USB 2.0 PHY provides a free-running PHY clock, it must be
 * connected to the utmi_clk[0] input. The remaining utmi_clk[n] must be
 * connected to the respective port clocks. The controller uses the Port-0
 * clock for generating the internal mac2 clock.
 *  - 1'b0: USB 2.0 free clock does not exist
 *  - 1'b1: USB 2.0 free clock exists
 * Note: When the controller is configured as device-only (DWC_USB3_MODE =
 * 0), do not set this bit to 1.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . U2_FREECLK_EXISTS
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_U2_FREECLK_EXISTS(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_USB3_GUSB2PHYCFG_U2_FREECLK_EXISTS  VTSS_BIT(30)
#define  VTSS_X_USB3_GUSB2PHYCFG_U2_FREECLK_EXISTS(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * UTMI PHY Soft Reset (PHYSoftRst)
 *
 * Causes the usb2phy_reset signal to be asserted to reset a UTMI PHY. Not
 * applicable to ULPI because ULPI PHYs are reset via their
 * FunctionControl.Reset register, and the controller automatically writes
 * to this register when the controller is reset (vcc_reset_n,
 * USBCMD.HCRST, DCTL.SoftReset, or GCTL.SoftReset)
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYCFG . GUSB2PHYCFG_PHYSOFTRST
 */
#define  VTSS_F_USB3_GUSB2PHYCFG_GUSB2PHYCFG_PHYSOFTRST(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_USB3_GUSB2PHYCFG_GUSB2PHYCFG_PHYSOFTRST  VTSS_BIT(31)
#define  VTSS_X_USB3_GUSB2PHYCFG_GUSB2PHYCFG_PHYSOFTRST(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief Reserved Register

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GUSB2I2CCTL
 */
#define VTSS_USB3_GUSB2I2CCTL                VTSS_IOREG(VTSS_TO_USB3,0x3090)

/**
 * \brief
 * Reserved for future use
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2I2CCTL . GUSB2I2CCTL_RESERVED_31_0
 */
#define  VTSS_F_USB3_GUSB2I2CCTL_GUSB2I2CCTL_RESERVED_31_0(x)  (x)
#define  VTSS_M_USB3_GUSB2I2CCTL_GUSB2I2CCTL_RESERVED_31_0     0xffffffff
#define  VTSS_X_USB3_GUSB2I2CCTL_GUSB2I2CCTL_RESERVED_31_0(x)  (x)


/**
 * \brief Global USB 2.0 ULPI PHY Vendor Control Register

The application uses this register to access the PHY registers. This register is always implemented when the ULPI PHY Interface is enabled during coreConsultant configuration (parameter DWC_USB3_HSPHY_INTERFACE = 2 or 3).

For an ULPI PHY, the controller uses the ULPI interface for PHY register access.

The application sets the Vendor Control register for PHY register access and times the PHY register access. The application polls the VStatus Done bit in this register for the completion of the PHY register access.

In Device-only configurations, only one register is needed. In Host mode, per-port registers are implemented.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GUSB2PHYACC_ULPI
 */
#define VTSS_USB3_GUSB2PHYACC_ULPI           VTSS_IOREG(VTSS_TO_USB3,0x30a0)

/**
 * \brief
 * REGDATA
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYACC_ULPI . GUSB2PHYACC_ULPI_REGDATA
 */
#define  VTSS_F_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_REGDATA(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_REGDATA     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_REGDATA(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * EXTREGADDR
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYACC_ULPI . EXTREGADDR
 */
#define  VTSS_F_USB3_GUSB2PHYACC_ULPI_EXTREGADDR(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_USB3_GUSB2PHYACC_ULPI_EXTREGADDR     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_USB3_GUSB2PHYACC_ULPI_EXTREGADDR(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Register Address
 *
 * The 6-bit PHY register address for immediate PHY Register Set access.
 *
 * Set to 6'h2F for Extended PHY Register Set access.
 *
 * Note: These bits are applicable for ULPI only.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYACC_ULPI . GUSB2PHYACC_ULPI_REGADDR
 */
#define  VTSS_F_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_REGADDR(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_REGADDR     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_REGADDR(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * Register Write
 *
 * The application sets this bit for register writes and clears it for
 * register reads.
 *
 * Note: This bit is applicable for ULPI register read/write access only.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYACC_ULPI . GUSB2PHYACC_ULPI_REGWR
 */
#define  VTSS_F_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_REGWR(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_REGWR  VTSS_BIT(22)
#define  VTSS_X_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_REGWR(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * VSTSBSY
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYACC_ULPI . GUSB2PHYACC_ULPI_VSTSBSY
 */
#define  VTSS_F_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_VSTSBSY(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_VSTSBSY  VTSS_BIT(23)
#define  VTSS_X_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_VSTSBSY(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * VSTSDONE
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYACC_ULPI . GUSB2PHYACC_ULPI_VSTSDONE
 */
#define  VTSS_F_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_VSTSDONE(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_VSTSDONE  VTSS_BIT(24)
#define  VTSS_X_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_VSTSDONE(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * New Register Request
 *
 * The application sets this bit for a new vendor control access.
 *
 * Setting this bit to 1 asserts the utmi_vcontrolload_n (1'b0) on the UTMI
 * interface.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYACC_ULPI . GUSB2PHYACC_ULPI_NEWREGREQ
 */
#define  VTSS_F_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_NEWREGREQ(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_NEWREGREQ  VTSS_BIT(25)
#define  VTSS_X_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_NEWREGREQ(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * DISUIPIDRVR
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYACC_ULPI . GUSB2PHYACC_ULPI_DISUIPIDRVR
 */
#define  VTSS_F_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_DISUIPIDRVR(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_DISUIPIDRVR  VTSS_BIT(26)
#define  VTSS_X_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_DISUIPIDRVR(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYACC_ULPI . GUSB2PHYACC_ULPI_RESERVED_31_27
 */
#define  VTSS_F_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_RESERVED_31_27(x)  VTSS_ENCODE_BITFIELD(x,27,5)
#define  VTSS_M_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_RESERVED_31_27     VTSS_ENCODE_BITMASK(27,5)
#define  VTSS_X_USB3_GUSB2PHYACC_ULPI_GUSB2PHYACC_ULPI_RESERVED_31_27(x)  VTSS_EXTRACT_BITFIELD(x,27,5)


/**
 * \brief Global USB 2.0 UTMI PHY Vendor Control Register

The application uses this register to access PHY registers. It is implemented only if both UTMI PHY Interface and PHY Vendor Control Interface are enabled during coreConsultant configuration (parameter DWC_USB3_HSPHY_INTERFACE = 1 or 3, and DWC_USB3_VENDOR_CTL_INTERFACE = 1).

In UTMI mode of operation, the functionality of this register can be used only if UTMI Vendor Control Interface is enabled.

For an UTMI+ PHY, the controller uses the UTMI+ Vendor Control interface for PHY register access. There is no read/write differentiation for UTMI+. It is just a vendor control access.
The application sets the Vendor Control register for PHY register access and times the PHY register access. The application polls the VStatus Done bit in this register for the completion of the PHY register access.

In Device-only configurations, only one register is needed. In Host mode, per-port registers are implemented.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GUSB2PHYACC_UTMI
 */
#define VTSS_USB3_GUSB2PHYACC_UTMI           VTSS_IOREG(VTSS_TO_USB3,0x30a0)

/**
 * \brief
 * REGDATA
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYACC_UTMI . GUSB2PHYACC_UTMI_REGDATA
 */
#define  VTSS_F_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_REGDATA(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_REGDATA     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_REGDATA(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * VCTRL
 *
 * This field contains the 4-bit register address, and the vendor-defined
 * 4-bit parallel output bus. Bits [11:8] of this field are also placed on
 * bits [3:0] of the utmi_vcontrol output signal.

 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYACC_UTMI . VCTRL
 */
#define  VTSS_F_USB3_GUSB2PHYACC_UTMI_VCTRL(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_USB3_GUSB2PHYACC_UTMI_VCTRL     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_USB3_GUSB2PHYACC_UTMI_VCTRL(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * REGADDR
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYACC_UTMI . GUSB2PHYACC_UTMI_REGADDR
 */
#define  VTSS_F_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_REGADDR(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_REGADDR     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_REGADDR(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * REGWR
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYACC_UTMI . GUSB2PHYACC_UTMI_REGWR
 */
#define  VTSS_F_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_REGWR(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_REGWR  VTSS_BIT(22)
#define  VTSS_X_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_REGWR(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * VSTSBSY
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYACC_UTMI . GUSB2PHYACC_UTMI_VSTSBSY
 */
#define  VTSS_F_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_VSTSBSY(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_VSTSBSY  VTSS_BIT(23)
#define  VTSS_X_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_VSTSBSY(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * VSTSDONE:
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYACC_UTMI . GUSB2PHYACC_UTMI_VSTSDONE
 */
#define  VTSS_F_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_VSTSDONE(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_VSTSDONE  VTSS_BIT(24)
#define  VTSS_X_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_VSTSDONE(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * NEWREGREQ
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYACC_UTMI . GUSB2PHYACC_UTMI_NEWREGREQ
 */
#define  VTSS_F_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_NEWREGREQ(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_NEWREGREQ  VTSS_BIT(25)
#define  VTSS_X_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_NEWREGREQ(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * DISUIPIDRVR
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYACC_UTMI . GUSB2PHYACC_UTMI_DISUIPIDRVR
 */
#define  VTSS_F_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_DISUIPIDRVR(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_DISUIPIDRVR  VTSS_BIT(26)
#define  VTSS_X_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_DISUIPIDRVR(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2PHYACC_UTMI . GUSB2PHYACC_UTMI_RESERVED_31_27
 */
#define  VTSS_F_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_RESERVED_31_27(x)  VTSS_ENCODE_BITFIELD(x,27,5)
#define  VTSS_M_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_RESERVED_31_27     VTSS_ENCODE_BITMASK(27,5)
#define  VTSS_X_USB3_GUSB2PHYACC_UTMI_GUSB2PHYACC_UTMI_RESERVED_31_27(x)  VTSS_EXTRACT_BITFIELD(x,27,5)


/**
 * \brief Global USB 3.0 PIPE Control Register

The application uses this register to configure the USB3 PHY and PIPE interface.

Device-only configuration requires only one register. In Host mode, registers are implemented for each port.

For more details on GUSB3PIPECTL(#n) bits, refer to section "GUSB3PIPECTLn Register" in the User Guide.

Note:
 - GUSB3PIPECTLn registers are not applicable for USB 2.0-only mode.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GUSB3PIPECTL
 */
#define VTSS_USB3_GUSB3PIPECTL               VTSS_IOREG(VTSS_TO_USB3,0x30b0)

/**
 * \brief
 * Elastic Buffer Mode (ElasticBufferMode)
 *
 * (Refer to Table 5-3 of the PIPE3 specification.)
 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . ELASTIC_BUFFER_MODE
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_ELASTIC_BUFFER_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_ELASTIC_BUFFER_MODE  VTSS_BIT(0)
#define  VTSS_X_USB3_GUSB3PIPECTL_ELASTIC_BUFFER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Tx Deemphasis (TxDeemphasis)
 *
 * The value driven to the PHY is controlled by the LTSSM during USB3
 * Compliance mode.
 *
 * (Refer to Table 5-3 of the PIPE3 specification.)
 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . SS_TX_DE_EMPHASIS
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_SS_TX_DE_EMPHASIS(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_USB3_GUSB3PIPECTL_SS_TX_DE_EMPHASIS     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_USB3_GUSB3PIPECTL_SS_TX_DE_EMPHASIS(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * Tx Margin[2:0] (TxMargin)
 *
 * Refer to Table 5-3 of the PIPE3 Specification.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . TX_MARGIN
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_TX_MARGIN(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_USB3_GUSB3PIPECTL_TX_MARGIN     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_USB3_GUSB3PIPECTL_TX_MARGIN(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * Tx Swing (TxSwing)
 *
 * Refer to the PIPE3 specification.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . TX_SWING
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_TX_SWING(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_TX_SWING    VTSS_BIT(6)
#define  VTSS_X_USB3_GUSB3PIPECTL_TX_SWING(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * This field is not used.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . SSICEN
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_SSICEN(x)   VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_SSICEN      VTSS_BIT(7)
#define  VTSS_X_USB3_GUSB3PIPECTL_SSICEN(x)   VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * RX_DETECT to Polling.LFPS Control
 *  - 1'b0 (Default): Enables a 400us delay to start Polling LFPS after
 * RX_DETECT. This allows VCM offset to settle to a proper level.
 *  - 1'b1: Disables the 400us delay to start Polling LFPS after RX_DETECT.
 * During controller certification with third party PHY it is observed that
 * the PHY is not able to meet the Tx AC common mode voltage active
 * (VTX-CM-ACPP_ACTIVE <100mv) if the link starts polling within 80us from
 * the time rx.detect is performed.
 *
 * To meet this VTX-CM-ACPP_ACTIVE specification, the polling must be
 * delayed further. If the PHY does not have issue then they can set this
 * bit to 1 which allows polling to start within 80us.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . RX_DETECT_TO_POLLING_LFPS_CONTROL
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_RX_DETECT_TO_POLLING_LFPS_CONTROL(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_RX_DETECT_TO_POLLING_LFPS_CONTROL  VTSS_BIT(8)
#define  VTSS_X_USB3_GUSB3PIPECTL_RX_DETECT_TO_POLLING_LFPS_CONTROL(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * LFPS Filter (LFPSFilt)
 *
 * When set, filter LFPS reception with pipe3_RxValid in PHY power state
 * P0, that is, ignore LFPS reception from the PHY unless both
 * pipe3_Rxelecidle and pipe3_RxValid are deasserted.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . LFPSFILTER
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_LFPSFILTER(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_LFPSFILTER  VTSS_BIT(9)
#define  VTSS_X_USB3_GUSB3PIPECTL_LFPSFILTER(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * P3 Exit Signal in P2 (P3ExSigP2)
 *
 * When this bit is set, the controller always changes the PHY power state
 * to P2, before attempting a U3 exit handshake. This bit is used only for
 * some non-Synopsys PHYs that cannot do LFPS in P3.
 *
 * Note: This bit is used by third-party SS PHY. It must be set to '0' for
 * Synopsys PHY.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . P3EXSIGP2
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_P3EXSIGP2(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_P3EXSIGP2   VTSS_BIT(10)
#define  VTSS_X_USB3_GUSB3PIPECTL_P3EXSIGP2(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * P3 P2 Transitions OK (P3P2TranOK)
 *
 * When set, the controller transitions directly from Phy power state P2 to
 * P3 or from state P3 to P2.
 * When not set, P0 is always entered as an intermediate state during
 * transitions between P2 and P3, as defined in the PIPE3 Specification.
 *
 * According to the PIPE3 Specification, any direct transition between P3
 * and P2 is illegal.
 *
 * Note: This bit is used by third-party SS PHY. It must be set to '0' for
 * Synopsys PHY.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . P3P2TRANOK
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_P3P2TRANOK(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_P3P2TRANOK  VTSS_BIT(11)
#define  VTSS_X_USB3_GUSB3PIPECTL_P3P2TRANOK(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * LFPS P0 Align:
 * When set,
 *  - The controller deasserts LFPS transmission on the clock edge that it
 * requests Phy power state 0 when exiting U1, U2, or U3 low power states.
 * Otherwise, LFPS transmission is asserted one clock earlier.
 *  - The controller requests symbol transmission two pipe3_rx_pclks
 * periods after the PHY asserts PhyStatus as a result of the PHY switching
 * from P1 or P2 state to P0 state.
 * Currently, this bit is only used in USB 3.0 HUB with Synopsys PHY. For
 * other USB 3.0 Host, Device, and DRD cores, this bit is not required.

 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . LFPSP0ALGN
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_LFPSP0ALGN(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_LFPSP0ALGN  VTSS_BIT(12)
#define  VTSS_X_USB3_GUSB3PIPECTL_LFPSP0ALGN(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Skip Rx Detect:
 *
 * When set, the controller skips Rx Detection if pipe3_RxElecIdle is low.
 *
 * Skip is defined as waiting for the appropriate timeout, then repeating
 * the operation.

 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . SKIPRXDET
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_SKIPRXDET(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_SKIPRXDET   VTSS_BIT(13)
#define  VTSS_X_USB3_GUSB3PIPECTL_SKIPRXDET(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Abort Rx Detect in U2 (AbortRxDetInU2)
 *
 * When set and the link state is U2, the controller will abort receiver
 * detection if it receives U2 exit LFPS from the remote link partner. This
 * bit is for the downstream port only.
 *
 * Note: This bit is used by third-party SS PHY. It must be set to '0' for
 * Synopsys PHY.

 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . ABORTRXDETINU2
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_ABORTRXDETINU2(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_ABORTRXDETINU2  VTSS_BIT(14)
#define  VTSS_X_USB3_GUSB3PIPECTL_ABORTRXDETINU2(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * PIPE Data Width (DatWidth)
 *  - 2'b00: 32 bits
 *  - 2'b01: 16 bits
 * One clock after reset, these bits receive the value seen on the
 * pipe3_DataBusWidth. The simulation testbench uses the coreConsultant
 * parameter to configure the VIP. These bits in the coreConsultant
 * parameter must match your PHY data width and the pipe3_DataBusWidth
 * port.
 *
 * Note: 8-bit data width is not supported.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . DATWIDTH
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_DATWIDTH(x)  VTSS_ENCODE_BITFIELD(x,15,2)
#define  VTSS_M_USB3_GUSB3PIPECTL_DATWIDTH     VTSS_ENCODE_BITMASK(15,2)
#define  VTSS_X_USB3_GUSB3PIPECTL_DATWIDTH(x)  VTSS_EXTRACT_BITFIELD(x,15,2)

/**
 * \brief
 * Suspend USB3.0 SS PHY (Suspend_en)
 *
 * When set, and if Suspend conditions are valid, the USB 3.0 PHY enters
 * Suspend mode.
 *
 * For DRD configurations, it is recommended that this bit is set to '0'
 * during coreConsultant configuration. If it is set to '1', then the
 * application must clear this bit after power-on reset. Application needs
 * to set it to '1' after the controller initialization is completed.
 *
 * For all other configurations, this bit can be set to '1' during
 * controller configuration.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . SUSPENDENABLE
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_SUSPENDENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_SUSPENDENABLE  VTSS_BIT(17)
#define  VTSS_X_USB3_GUSB3PIPECTL_SUSPENDENABLE(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Delay PHY power change from P0 to P1/P2/P3 when link state changing from
 * U0 to U1/U2/U3 respectively.
 *  - 1'b1: When entering U1/U2/U3, delay the transition to P1/P2/P3 until
 * the pipe3 signals, Pipe3_RxElecIdle is 1 and pipe3_RxValid is 0
 *  - 1'b0: When entering U1/U2/U3, transition to P1/P2/P3 without checking
 * for Pipe3_RxElecIdle and pipe3_RxValid.
 * Note:
 *  - If you are using Synopsys PHY, contact Synopsys Customer Support for
 * recommendation on setting this bit because it is node dependent.
 *  - If you are using a third-party SS PHY, check with your PHY vendor for
 * recommendation on setting this bit.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . DELAYP1TRANS
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_DELAYP1TRANS(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_DELAYP1TRANS  VTSS_BIT(18)
#define  VTSS_X_USB3_GUSB3PIPECTL_DELAYP1TRANS(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Delay P1P2P3
 *
 * Delay P0 to P1/P2/P3 request when entering U1/U2/U3 until
 * (DWC_USB3_GUSB3PIPECTL_INIT[21:19]*8) 8B10B error occurs, or
 * Pipe3_RxValid drops to 0.
 *
 * DWC_USB3_GUSB3PIPECTL_INIT[18] must be 1 to enable this functionality.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . DELAYP1P2P3
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_DELAYP1P2P3(x)  VTSS_ENCODE_BITFIELD(x,19,3)
#define  VTSS_M_USB3_GUSB3PIPECTL_DELAYP1P2P3     VTSS_ENCODE_BITMASK(19,3)
#define  VTSS_X_USB3_GUSB3PIPECTL_DELAYP1P2P3(x)  VTSS_EXTRACT_BITFIELD(x,19,3)

/**
 * \brief
 * Disable Receiver Detection in U3/Rx.Det
 *
 * When set, the controller does not handle receiver detection in either U3
 * or Rx.Detect states. DWC_USB3_GUSB3PIPECTL_INIT[23] must be used to
 * start receiver detection manually. This bit can only be used for the
 * downstream port. This bit must be set to "0" for Upstream ports. This
 * feature must not be enabled for normal operation. If you have to use
 * this feature, contact Synopsys.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . DISRXDETU3RXDET
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_DISRXDETU3RXDET(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_DISRXDETU3RXDET  VTSS_BIT(22)
#define  VTSS_X_USB3_GUSB3PIPECTL_DISRXDETU3RXDET(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Start Receiver Detection in U3/Rx.Detect (StartRxdetU3RxDet)
 *
 * If DWC_USB3_GUSB3PIPECTL_INIT[22] is set, and the link is in either U3
 * or Rx.Detect state, the controller starts receiver detection on the
 * rising edge of this bit. This can only be used for Downstream ports.
 * This bit must be set to '0' for Upstream ports. This feature must not be
 * enabled for normal operation. If have to use this feature, contact
 * Synopsys.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . STARTRXDETU3RXDET
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_STARTRXDETU3RXDET(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_STARTRXDETU3RXDET  VTSS_BIT(23)
#define  VTSS_X_USB3_GUSB3PIPECTL_STARTRXDETU3RXDET(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Always Request P1/P2/P3 for U1/U2/U3 (request_p1p2p3)
 *
 * When set, the controller always requests PHY power change from P0 to
 * P1/P2/P3 during U0 to U1/U2/U3 transition.
 *
 * If this bit is 0, and immediate Ux exit (remotely initiated, or locally
 * initiated) happens, the controller does not request P1/P2/P3 power state
 * change.
 *
 * Note: This bit must be set to '1' for Synopsys PHY. For third-party SS
 * PHY, check with your PHY vendor.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . REQUEST_P1P2P3
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_REQUEST_P1P2P3(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_REQUEST_P1P2P3  VTSS_BIT(24)
#define  VTSS_X_USB3_GUSB3PIPECTL_REQUEST_P1P2P3(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * U1U2exitfail to Recovery (u1u2exitfail_to_recov)
 *
 * When set, and U1/U2 LFPS handshake fails, the LTSSM transitions from
 * U1/U2 to Recovery instead of SS Inactive. If Recovery fails, then the
 * LTSSM can enter SS.Inactive. This is an enhancement only. It prevents
 * interoperability issue if the remote link does not do proper handshake.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . U1U2EXITFAIL_TO_RECOV
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_U1U2EXITFAIL_TO_RECOV(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_U1U2EXITFAIL_TO_RECOV  VTSS_BIT(25)
#define  VTSS_X_USB3_GUSB3PIPECTL_U1U2EXITFAIL_TO_RECOV(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Ping Enhancement Enable (ping_enhancement_en)
 *
 * When set, the Downstream port U1 ping receive timeout becomes 500 ms
 * instead of 300 ms. Minimum Ping.LFPS receive duration is 8 ns (one
 * mac3_clk). This field is valid for the downstream port only.
 *
 * Note: This bit is used by third-party SS PHY. It must be set to '0' for
 * Synopsys PHY.

 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . PING_ENHANCEMENT_EN
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_PING_ENHANCEMENT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_PING_ENHANCEMENT_EN  VTSS_BIT(26)
#define  VTSS_X_USB3_GUSB3PIPECTL_PING_ENHANCEMENT_EN(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * Ux Exit in Px (Ux_exit_in_Px)
 *  - 0: The controller does U1/U2/U3 exit in PHY power state P0 (default
 * behavior).
 *  - 1: The controller does U1/U2/U3 exit in PHY power state P1/P2/P3
 * respectively.
 * Note: This bit is used by third-party SS PHY. It must be set to '0' for
 * Synopsys PHY.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . UX_EXIT_IN_PX
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_UX_EXIT_IN_PX(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_UX_EXIT_IN_PX  VTSS_BIT(27)
#define  VTSS_X_USB3_GUSB3PIPECTL_UX_EXIT_IN_PX(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Disabled receiver detection in P3 (DisRxDetP3)
 *  - 0: If PHY is in P3 and controller needs to perform receiver
 * detection, The controller performs receiver detection in P3. (Default)
 *  - 1: If PHY is in P3 and controller needs to perform receiver
 * detection, The controller changes the PHY power state to P2 and then
 * performs receiver detection. After receiver detection, the cores changes
 * PHY power state to P3.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . DISRXDETP3
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_DISRXDETP3(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_DISRXDETP3  VTSS_BIT(28)
#define  VTSS_X_USB3_GUSB3PIPECTL_DISRXDETP3(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * P3 OK for SSInactive (SSIP3ok)
 *  - 0: During link state SS.Inactive, put PHY in P2 (Default)
 *  - 1: During link state SS.Inactive, put PHY in P3.
 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . U2P3OK
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_U2P3OK(x)   VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_U2P3OK      VTSS_BIT(29)
#define  VTSS_X_USB3_GUSB3PIPECTL_U2P3OK(x)   VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * HstPrtCmpl
 *
 * This feature tests the PIPE PHY compliance patterns without having to
 * have a test fixture on the USB 3.0 cable.
 *
 * This bit enables placing the SS port link into a compliance state. By
 * default, this bit must be set to 1'b0.
 *
 * In compliance lab testing, the SS port link enters compliance after
 * failing the first polling sequence after power on. Set this bit to 0,
 * when you run compliance tests.
 *
 * The sequence for using this functionality is as follows:
 *  - 1. Disconnect any plugged in devices.
 *  - 2. Perform USBCMD.HCRST or power-on-chip reset.
 *  - 3. Set PORTSC.PLS=0xA.
 *  - 4. Set PORTSC.PP=0.
 *  - 5. Set GUSB3PIPECTL. HstPrtCmpl=1. This places the link into
 * compliance state.
 * To advance the compliance pattern, follow this sequence (toggle the set
 * GUSB3PIPECTL. HstPrtCmpl):
 *  - 1. Set GUSB3PIPECTL.HstPrtCmpl=0.
 *  - 2. Set GUSB3PIPECTL.HstPrtCmpl=1. This advances the link to the next
 * compliance pattern.
 * To exit from the compliance state perform USBCMD.HCRST or power-on-chip
 * reset.

 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . HSTPRTCMPL
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_HSTPRTCMPL(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_HSTPRTCMPL  VTSS_BIT(30)
#define  VTSS_X_USB3_GUSB3PIPECTL_HSTPRTCMPL(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * USB3 PHY Soft Reset
 *
 * After setting this bit to '1', the software needs to clear this bit. For
 * more information, refer to Figure "Software Resets and PHY Clock
 * Sequencing and Requirements" in the Databook.

 *
 * \details
 * Field: ::VTSS_USB3_GUSB3PIPECTL . GUSB3PIPECTL_PHYSOFTRST
 */
#define  VTSS_F_USB3_GUSB3PIPECTL_GUSB3PIPECTL_PHYSOFTRST(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_USB3_GUSB3PIPECTL_GUSB3PIPECTL_PHYSOFTRST  VTSS_BIT(31)
#define  VTSS_X_USB3_GUSB3PIPECTL_GUSB3PIPECTL_PHYSOFTRST(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief Global Transmit FIFO Size Register

This register specifies the RAM start address and depth (both in MDWIDTH-bit words) for each implemented TxFIFO. The number of TxFIFOs depends on the configuration parameters including the number of Device IN Endpoints, number of Host Bus Instances, and presence of Debug Capability.

The register default values for each mode are assigned in coreConsultant based on the maximum packet size, number of packets to be buffered, speed of host bus instance, bus latency, and mode of operation (host, device, or, DBC). Upon reset and mode transitions, hardware automatically programs these registers to the default values. Consequently, there is typically no need for the software to modify the pre-defined default values.

For the debug capability mode, the currently mapped EP0 IN and EP1 IN TxFIFO numbers can be read from the GFIFOPRIDBC register.

For more details on the usage of the GTXFIFOSIZn and GRXFIFOSIZn registers for different modes of operation, refer to "Memory Requirements" chapter in the Databook.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GTXFIFOSIZ0
 */
#define VTSS_USB3_GTXFIFOSIZ0                VTSS_IOREG(VTSS_TO_USB3,0x30c0)

/**
 * \brief
 * TxFIFO Depth
 *
 * This field contains the depth of TxFIFOn in MDWIDTH-bit words.
 *  - Minimum value: 32
 *  - Maximum value: 32,768
 * For more information, see "Integrating the Controller" chapter in the
 * User Guide.
 *
 * \details
 * Field: ::VTSS_USB3_GTXFIFOSIZ0 . GTXFIFOSIZ0_TXFDEP_N
 */
#define  VTSS_F_USB3_GTXFIFOSIZ0_GTXFIFOSIZ0_TXFDEP_N(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_USB3_GTXFIFOSIZ0_GTXFIFOSIZ0_TXFDEP_N     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_USB3_GTXFIFOSIZ0_GTXFIFOSIZ0_TXFDEP_N(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Transmit FIFOn RAM Start Address
 *
 * This field contains the memory start address for TxFIFOn in MDWIDTH-bit
 * words.
 *
 * \details
 * Field: ::VTSS_USB3_GTXFIFOSIZ0 . GTXFIFOSIZ0_TXFSTADDR_N
 */
#define  VTSS_F_USB3_GTXFIFOSIZ0_GTXFIFOSIZ0_TXFSTADDR_N(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_GTXFIFOSIZ0_GTXFIFOSIZ0_TXFSTADDR_N     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_GTXFIFOSIZ0_GTXFIFOSIZ0_TXFSTADDR_N(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Register GTXFIFOSIZ 1
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GTXFIFOSIZ1
 */
#define VTSS_USB3_GTXFIFOSIZ1                VTSS_IOREG(VTSS_TO_USB3,0x30c1)

/**
 * \brief
 * TXFDEP_N
 *
 * \details
 * Field: ::VTSS_USB3_GTXFIFOSIZ1 . GTXFIFOSIZ1_TXFDEP_N
 */
#define  VTSS_F_USB3_GTXFIFOSIZ1_GTXFIFOSIZ1_TXFDEP_N(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_USB3_GTXFIFOSIZ1_GTXFIFOSIZ1_TXFDEP_N     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_USB3_GTXFIFOSIZ1_GTXFIFOSIZ1_TXFDEP_N(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Transmit FIFOn RAM Start Address
 *
 * This field contains the memory start address for TxFIFOn in MDWIDTH-bit
 * words.
 *
 * \details
 * Field: ::VTSS_USB3_GTXFIFOSIZ1 . GTXFIFOSIZ1_TXFSTADDR_N
 */
#define  VTSS_F_USB3_GTXFIFOSIZ1_GTXFIFOSIZ1_TXFSTADDR_N(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_GTXFIFOSIZ1_GTXFIFOSIZ1_TXFSTADDR_N     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_GTXFIFOSIZ1_GTXFIFOSIZ1_TXFSTADDR_N(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Transmit FIFOn RAM Start Address

This field contains the memory start address for TxFIFOn in MDWIDTH-bit words.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GTXFIFOSIZ2
 */
#define VTSS_USB3_GTXFIFOSIZ2                VTSS_IOREG(VTSS_TO_USB3,0x30c2)

/**
 * \brief
 * TxFIFO Depth
 *
 * This field contains the depth of TxFIFOn in MDWIDTH-bit words.
 *  - Minimum value: 32
 *  - Maximum value: 32,768
 * For more information, see "Integrating the Controller" chapter in the
 * User Guide.
 *
 * \details
 * Field: ::VTSS_USB3_GTXFIFOSIZ2 . GTXFIFOSIZ2_TXFDEP_N
 */
#define  VTSS_F_USB3_GTXFIFOSIZ2_GTXFIFOSIZ2_TXFDEP_N(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_USB3_GTXFIFOSIZ2_GTXFIFOSIZ2_TXFDEP_N     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_USB3_GTXFIFOSIZ2_GTXFIFOSIZ2_TXFDEP_N(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Transmit FIFOn RAM Start Address
 *
 * This field contains the memory start address for TxFIFOn in MDWIDTH-bit
 * words.
 *
 * \details
 * Field: ::VTSS_USB3_GTXFIFOSIZ2 . GTXFIFOSIZ2_TXFSTADDR_N
 */
#define  VTSS_F_USB3_GTXFIFOSIZ2_GTXFIFOSIZ2_TXFSTADDR_N(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_GTXFIFOSIZ2_GTXFIFOSIZ2_TXFSTADDR_N     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_GTXFIFOSIZ2_GTXFIFOSIZ2_TXFSTADDR_N(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Register GTXFIFOSIZ 3
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GTXFIFOSIZ3
 */
#define VTSS_USB3_GTXFIFOSIZ3                VTSS_IOREG(VTSS_TO_USB3,0x30c3)

/**
 * \brief
 * TXFDEP_N:  TxFIFO Depth (TxFDep_n)
 *
 * This field contains the depth of TxFIFOn in MDWIDTH-bit words.
 *  - Minimum value: 32
 *  - Maximum value: 32,768
 * For more information, see "Integrating the Controller" chapter in the
 * User Guide.
 *
 * \details
 * Field: ::VTSS_USB3_GTXFIFOSIZ3 . GTXFIFOSIZ3_TXFDEP_N
 */
#define  VTSS_F_USB3_GTXFIFOSIZ3_GTXFIFOSIZ3_TXFDEP_N(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_USB3_GTXFIFOSIZ3_GTXFIFOSIZ3_TXFDEP_N     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_USB3_GTXFIFOSIZ3_GTXFIFOSIZ3_TXFDEP_N(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Transmit FIFOn RAM Start Address
 *
 * This field contains the memory start address for TxFIFOn in MDWIDTH-bit
 * words.
 *
 * \details
 * Field: ::VTSS_USB3_GTXFIFOSIZ3 . GTXFIFOSIZ3_TXFSTADDR_N
 */
#define  VTSS_F_USB3_GTXFIFOSIZ3_GTXFIFOSIZ3_TXFSTADDR_N(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_GTXFIFOSIZ3_GTXFIFOSIZ3_TXFSTADDR_N     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_GTXFIFOSIZ3_GTXFIFOSIZ3_TXFSTADDR_N(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Global Receive FIFO Size Register

This register specifies the RAM start address and depth (both in MDWIDTH-bit words) for each implemented RxFIFO. The number of RxFIFOs depends on the configuration parameters including the number of Host Bus Instances and presence of Debug Capability; device mode requires only one RxFIFO.

The register default values for each mode are assigned in coreConsultant based on the maximum packet size, number of packets to be buffered, speed of the host bus instance, bus latency, and mode of operation (host, device, or DBC). Upon reset and mode transitions, hardware automatically programs these registers to the default values. Consequently, there is typically no need for the software to modify the pre-defined default values.

For the debug capability mode, the currently mapped RxFIFO number can be read from the GFIFOPRIDBC register.

For more details on the usage of the GTXFIFOSIZn and GRXFIFOSIZn registers for different modes of operation, refer to "Memory Requirements" chapter in the Databook.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GRXFIFOSIZ0
 */
#define VTSS_USB3_GRXFIFOSIZ0                VTSS_IOREG(VTSS_TO_USB3,0x30e0)

/**
 * \brief
 * RxFIFO Depth (RxFDep_n)
 *
 * This field contains the depth of RxFIFOn in MDWIDTH-bit words.
 *  - Minimum value: 32
 *  - Maximum value: 16,384
 *
 * \details
 * Field: ::VTSS_USB3_GRXFIFOSIZ0 . GRXFIFOSIZ0_RXFDEP_N
 */
#define  VTSS_F_USB3_GRXFIFOSIZ0_GRXFIFOSIZ0_RXFDEP_N(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_USB3_GRXFIFOSIZ0_GRXFIFOSIZ0_RXFDEP_N     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_USB3_GRXFIFOSIZ0_GRXFIFOSIZ0_RXFDEP_N(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * RxFIFOn RAM Start Address (RxFStAddr_n)
 *
 * This field contains the memory start address for RxFIFOn in MDWIDTH-bit
 * words.
 *
 * \details
 * Field: ::VTSS_USB3_GRXFIFOSIZ0 . GRXFIFOSIZ0_RXFSTADDR_N
 */
#define  VTSS_F_USB3_GRXFIFOSIZ0_GRXFIFOSIZ0_RXFSTADDR_N(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_GRXFIFOSIZ0_GRXFIFOSIZ0_RXFSTADDR_N     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_GRXFIFOSIZ0_GRXFIFOSIZ0_RXFSTADDR_N(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Register
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GRXFIFOSIZ1
 */
#define VTSS_USB3_GRXFIFOSIZ1                VTSS_IOREG(VTSS_TO_USB3,0x30e1)

/**
 * \brief
 * RxFIFO Depth
 *
 * This field contains the depth of RxFIFOn in MDWIDTH-bit words.
 *  - Minimum value: 32
 *  - Maximum value: 16,384
 *
 * \details
 * Field: ::VTSS_USB3_GRXFIFOSIZ1 . GRXFIFOSIZ1_RXFDEP_N
 */
#define  VTSS_F_USB3_GRXFIFOSIZ1_GRXFIFOSIZ1_RXFDEP_N(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_USB3_GRXFIFOSIZ1_GRXFIFOSIZ1_RXFDEP_N     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_USB3_GRXFIFOSIZ1_GRXFIFOSIZ1_RXFDEP_N(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * RXFSTADDR_N
 *
 * \details
 * Field: ::VTSS_USB3_GRXFIFOSIZ1 . GRXFIFOSIZ1_RXFSTADDR_N
 */
#define  VTSS_F_USB3_GRXFIFOSIZ1_GRXFIFOSIZ1_RXFSTADDR_N(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_GRXFIFOSIZ1_GRXFIFOSIZ1_RXFSTADDR_N     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_GRXFIFOSIZ1_GRXFIFOSIZ1_RXFSTADDR_N(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Register
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GRXFIFOSIZ2
 */
#define VTSS_USB3_GRXFIFOSIZ2                VTSS_IOREG(VTSS_TO_USB3,0x30e2)

/**
 * \brief
 * RxFIFO Depth
 *
 * This field contains the depth of RxFIFOn in MDWIDTH-bit words.
 *  - Minimum value: 32
 *  - Maximum value: 16,384
 *
 * \details
 * Field: ::VTSS_USB3_GRXFIFOSIZ2 . GRXFIFOSIZ2_RXFDEP_N
 */
#define  VTSS_F_USB3_GRXFIFOSIZ2_GRXFIFOSIZ2_RXFDEP_N(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_USB3_GRXFIFOSIZ2_GRXFIFOSIZ2_RXFDEP_N     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_USB3_GRXFIFOSIZ2_GRXFIFOSIZ2_RXFDEP_N(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * RAM Start Address
 *
 * This field contains the memory start address for RxFIFOn in MDWIDTH-bit
 * words.

 *
 * \details
 * Field: ::VTSS_USB3_GRXFIFOSIZ2 . GRXFIFOSIZ2_RXFSTADDR_N
 */
#define  VTSS_F_USB3_GRXFIFOSIZ2_GRXFIFOSIZ2_RXFSTADDR_N(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_GRXFIFOSIZ2_GRXFIFOSIZ2_RXFSTADDR_N     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_GRXFIFOSIZ2_GRXFIFOSIZ2_RXFSTADDR_N(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Global Event Buffer Address (Low) Register

This is an alternate register for the GEVNTADRn register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GEVNTADRLO
 */
#define VTSS_USB3_GEVNTADRLO                 VTSS_IOREG(VTSS_TO_USB3,0x3100)

/**
 * \brief
 * Event Buffer Address (EvntAdrLo)
 *
 * Holds the lower 32 bits of start address of the external memory for the
 * Event Buffer. During operation, hardware does not update this address.
 *
 * \details
 * Field: ::VTSS_USB3_GEVNTADRLO . EVNTADRLO
 */
#define  VTSS_F_USB3_GEVNTADRLO_EVNTADRLO(x)  (x)
#define  VTSS_M_USB3_GEVNTADRLO_EVNTADRLO     0xffffffff
#define  VTSS_X_USB3_GEVNTADRLO_EVNTADRLO(x)  (x)


/**
 * \brief Global Event Buffer Address (High) Register

This is an alternate register for the GEVNTADRn register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GEVNTADRHI
 */
#define VTSS_USB3_GEVNTADRHI                 VTSS_IOREG(VTSS_TO_USB3,0x3101)

/**
 * \brief
 * Event Buffer Address (EvntAdrHi)
 *
 * Holds the higher 32 bits of start address of the external memory for the
 * Event Buffer. During operation, hardware does not update this address.
 *
 * \details
 * Field: ::VTSS_USB3_GEVNTADRHI . EVNTADRHI
 */
#define  VTSS_F_USB3_GEVNTADRHI_EVNTADRHI(x)  (x)
#define  VTSS_M_USB3_GEVNTADRHI_EVNTADRHI     0xffffffff
#define  VTSS_X_USB3_GEVNTADRHI_EVNTADRHI(x)  (x)


/**
 * \brief Global Event Buffer Size Register

This register holds the Event Buffer Size and the Event Interrupt Mask bit. During power-on initialization, software must initialize the size with the number of bytes allocated for the Event Buffer. The Event Interrupt Mask will mask the interrupt, but events are still queued. After configuration, software must preserve the Event Buffer Size value when changing the Event Interrupt Mask.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GEVNTSIZ
 */
#define VTSS_USB3_GEVNTSIZ                   VTSS_IOREG(VTSS_TO_USB3,0x3102)

/**
 * \brief
 * Event Buffer Size in bytes (EVNTSiz)
 *
 * Holds the size of the Event Buffer in bytes; must be a multiple of four.
 * This is programmed by software once during initialization.
 * The minimum size of the event buffer is 32 bytes.
 *
 * \details
 * Field: ::VTSS_USB3_GEVNTSIZ . EVENTSIZ
 */
#define  VTSS_F_USB3_GEVNTSIZ_EVENTSIZ(x)     VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_USB3_GEVNTSIZ_EVENTSIZ        VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_USB3_GEVNTSIZ_EVENTSIZ(x)     VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GEVNTSIZ . GEVNTSIZ_RESERVED_30_16
 */
#define  VTSS_F_USB3_GEVNTSIZ_GEVNTSIZ_RESERVED_30_16(x)  VTSS_ENCODE_BITFIELD(x,16,15)
#define  VTSS_M_USB3_GEVNTSIZ_GEVNTSIZ_RESERVED_30_16     VTSS_ENCODE_BITMASK(16,15)
#define  VTSS_X_USB3_GEVNTSIZ_GEVNTSIZ_RESERVED_30_16(x)  VTSS_EXTRACT_BITFIELD(x,16,15)

/**
 * \brief
 * Event Interrupt Mask (EvntIntMask).
 *
 * When set to '1', this prevents the interrupt from being generated.
 * However, even when the mask is set, the events are queued.
 *
 * \details
 * Field: ::VTSS_USB3_GEVNTSIZ . EVNTINTRPTMASK
 */
#define  VTSS_F_USB3_GEVNTSIZ_EVNTINTRPTMASK(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_USB3_GEVNTSIZ_EVNTINTRPTMASK  VTSS_BIT(31)
#define  VTSS_X_USB3_GEVNTSIZ_EVNTINTRPTMASK(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief Global Event Buffer Count Register

This register holds the number of valid bytes in the Event Buffer. During initialization, software must initialize the count by writing 0 to the Event Count field. Each time the hardware writes a new event to the Event Buffer, it increments this count. Most events are four bytes, but some events may span over multiple four byte entries. Whenever the count is greater than zero and if enabled, conditions for interrupt moderation are satisfied, the hardware raises the corresponding interrupt line (depending on the EvntIntMask bit in the GEVNTSIZn register). On an interrupt, software processes one or more events out of the Event Buffer. Afterwards, software must write the Event Count field with the number of bytes it processed. If Interrupt Moderation is enabled, then software needs to clear EVNT_HANDLER_BUSY bit.

Clock crossing delays may result in the continuous assertion of the interrupt after software acknowledges the last event. Therefore, when the interrupt line is asserted, software must read the GEVNTCOUNT register and only process events if the GEVNTCOUNT is greater than 0.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GEVNTCOUNT
 */
#define VTSS_USB3_GEVNTCOUNT                 VTSS_IOREG(VTSS_TO_USB3,0x3103)

/**
 * \brief
 * Event Count (EVNTCount)
 *
 * When read, returns the number of valid events in the Event Buffer (in
 * bytes).
 *
 * When written, hardware decrements the count by the value written.
 *
 * When Interrupt moderation is enabled (that is, DEVICE_IMODI!= 0), the
 * interrupt line gets de-asserted when the first write happens on this
 * register to decrement the count. When Interrupt moderation is disabled
 * (that is, DEVICE_IMODI = 0), the Interrupt line continues to get
 * asserted until the event count becomes zero (no-moderation behavior).
 *
 * \details
 * Field: ::VTSS_USB3_GEVNTCOUNT . EVNTCOUNT
 */
#define  VTSS_F_USB3_GEVNTCOUNT_EVNTCOUNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_USB3_GEVNTCOUNT_EVNTCOUNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_USB3_GEVNTCOUNT_EVNTCOUNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GEVNTCOUNT . GEVNTCOUNT_RESERVED_30_16
 */
#define  VTSS_F_USB3_GEVNTCOUNT_GEVNTCOUNT_RESERVED_30_16(x)  VTSS_ENCODE_BITFIELD(x,16,15)
#define  VTSS_M_USB3_GEVNTCOUNT_GEVNTCOUNT_RESERVED_30_16     VTSS_ENCODE_BITMASK(16,15)
#define  VTSS_X_USB3_GEVNTCOUNT_GEVNTCOUNT_RESERVED_30_16(x)  VTSS_EXTRACT_BITFIELD(x,16,15)

/**
 * \brief
 * Event Handler Busy
 *
 * Device software event handler busy indication. The controller sets this
 * bit when the interrupt line is asserted due to pending events. Software
 * clears this bit (with 1'b1) when it has finished processing the events
 * (along with updating the EVNTCOUNT in this register). The controller
 * does not raise the interrupt line for a new event unless this bit is
 * cleared.
 *
 * Note: When Interrupt moderation is disabled (that is, DEVICE_IMODI = 0),
 * this bit is ignored.
 *
 * \details
 * Field: ::VTSS_USB3_GEVNTCOUNT . EVNT_HANDLER_BUSY
 */
#define  VTSS_F_USB3_GEVNTCOUNT_EVNT_HANDLER_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_USB3_GEVNTCOUNT_EVNT_HANDLER_BUSY  VTSS_BIT(31)
#define  VTSS_X_USB3_GEVNTCOUNT_EVNT_HANDLER_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief Global USB 2.0 Root Hub Control Register

The application must program this register before starting any transactions on the USB if a non-default value is desired.

In Host mode, per-port registers are implemented.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_GBL:GUSB2RHBCTL
 */
#define VTSS_USB3_GUSB2RHBCTL                VTSS_IOREG(VTSS_TO_USB3,0x3190)

/**
 * \brief
 * Overriding the driver programmed L1TIMEOUT value.
 *
 * If this value is 0, the L1 Timeout value is taken from the xHCI
 * PORTHLPMC register. If this value is non-0, then this will override the
 * L1 Timeout value programmed in the xHCI PORTHLPMC register. In that case
 * the actual L1 Timeout would be 2 ^ <OVRD_L1TIMEOUT-1> * 8us. (1=8us,
 * 2=16us, 3=32us etc)
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2RHBCTL . OVRD_L1TIMEOUT
 */
#define  VTSS_F_USB3_GUSB2RHBCTL_OVRD_L1TIMEOUT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_USB3_GUSB2RHBCTL_OVRD_L1TIMEOUT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_USB3_GUSB2RHBCTL_OVRD_L1TIMEOUT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_GUSB2RHBCTL . RESERVED_31_4
 */
#define  VTSS_F_USB3_GUSB2RHBCTL_RESERVED_31_4(x)  VTSS_ENCODE_BITFIELD(x,4,28)
#define  VTSS_M_USB3_GUSB2RHBCTL_RESERVED_31_4     VTSS_ENCODE_BITMASK(4,28)
#define  VTSS_X_USB3_GUSB2RHBCTL_RESERVED_31_4(x)  VTSS_EXTRACT_BITFIELD(x,4,28)

/**
 * Register Group: \a USB3:DWC_USB3_BLOCK_DEV
 *
 * USB 3.0 Device Register Block
 */


/**
 * \brief Device Configuration Register.

This register configures the controller in Device mode after power-on or after certain control commands or enumeration. Do not make changes to this register after initial programming.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_DEV:DCFG
 */
#define VTSS_USB3_DCFG                       VTSS_IOREG(VTSS_TO_USB3,0x31c0)

/**
 * \brief
 * Device Speed.
 *
 * Indicates the speed at which the application requires the controller to
 * connect, or the maximum speed the application can support.
 *
 * However, the actual bus speed is determined only after the chirp
 * sequence is completed, and is based on the speed of the USB host to
 * which the controller is connected.
 *  - 3'b100: SuperSpeed (USB 3.0 PHY clock is 125 MHz or 250 MHz)
 *  - 3'b000: High-speed (USB 2.0 PHY clock is 30 MHz or 60 MHz)
 *  - 3'b001: Full-speed (USB 2.0 PHY clock is 30 MHz or 60 MHz)
 *
 * \details
 * 'h1: Full-speed (USB 2.0 PHY clock is 30 MHz or 60 MHz)
 * 'h0: High-speed (USB 2.0 PHY clock is 30 MHz or 60 MHz)
 * 'h4: SuperSpeed (USB 3.0 PHY clock is 125 MHz or 250 MHz)

 *
 * Field: ::VTSS_USB3_DCFG . DEVSPD
 */
#define  VTSS_F_USB3_DCFG_DEVSPD(x)           VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_USB3_DCFG_DEVSPD              VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_USB3_DCFG_DEVSPD(x)           VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Device Address.
 *
 * The application must perform the following:
 *  - Program this field after every SetAddress request.
 *  - Reset this field to zero after USB reset.
 *
 * \details
 * Field: ::VTSS_USB3_DCFG . DEVADDR
 */
#define  VTSS_F_USB3_DCFG_DEVADDR(x)          VTSS_ENCODE_BITFIELD(x,3,7)
#define  VTSS_M_USB3_DCFG_DEVADDR             VTSS_ENCODE_BITMASK(3,7)
#define  VTSS_X_USB3_DCFG_DEVADDR(x)          VTSS_EXTRACT_BITFIELD(x,3,7)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_DCFG . RESERVED_10_11
 */
#define  VTSS_F_USB3_DCFG_RESERVED_10_11(x)   VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_USB3_DCFG_RESERVED_10_11      VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_USB3_DCFG_RESERVED_10_11(x)   VTSS_EXTRACT_BITFIELD(x,10,2)

/**
 * \brief
 * Interrupt number
 *
 * Indicates interrupt/EventQ number on which non-endpoint-specific
 * device-related interrupts (see DEVT) are generated.
 *
 * \details
 * Field: ::VTSS_USB3_DCFG . INTRNUM
 */
#define  VTSS_F_USB3_DCFG_INTRNUM(x)          VTSS_ENCODE_BITFIELD(x,12,5)
#define  VTSS_M_USB3_DCFG_INTRNUM             VTSS_ENCODE_BITMASK(12,5)
#define  VTSS_X_USB3_DCFG_INTRNUM(x)          VTSS_EXTRACT_BITFIELD(x,12,5)

/**
 * \brief
 * Number of Receive Buffers.
 *
 * This bit indicates the number of receive buffers to be reported in the
 * ACK TP.
 *
 * The DWC_usb3 controller uses this field for non-control endpoints if
 * GRXTHRCFG.UsbRxPktCntSel is set to '0'. The application can program this
 * value based on RxFIFO size, buffer sizes programmed in descriptors, and
 * system latency.
 *
 * For an OUT endpoint, this field controls the number of receive buffers
 * reported in the NumP field of the ACK TP transmitted by the controller.
 *
 * Note: This bit is used in host mode when Debug Capability is enabled.
 *
 * \details
 * Field: ::VTSS_USB3_DCFG . NUMP
 */
#define  VTSS_F_USB3_DCFG_NUMP(x)             VTSS_ENCODE_BITFIELD(x,17,5)
#define  VTSS_M_USB3_DCFG_NUMP                VTSS_ENCODE_BITMASK(17,5)
#define  VTSS_X_USB3_DCFG_NUMP(x)             VTSS_EXTRACT_BITFIELD(x,17,5)

/**
 * \brief
 * LPM Capable
 *
 * The application uses this bit to control the LPM capabilities of the
 * DWC_usb3 controller. If the controller operates as a non-LPM-capable
 * device, it cannot respond to LPM transactions.
 *  - 1'b0: LPM capability is not enabled.
 *  - 1'b1: LPM capability is enabled.
 *
 * \details
 * Field: ::VTSS_USB3_DCFG . LPMCAP
 */
#define  VTSS_F_USB3_DCFG_LPMCAP(x)           VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_USB3_DCFG_LPMCAP              VTSS_BIT(22)
#define  VTSS_X_USB3_DCFG_LPMCAP(x)           VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * IgnoreStreamPP
 * This bit only affects stream-capable bulk endpoints.
 *
 * When this bit is set to '0' and the controller receives a Data Packet
 * with the Packet Pending (PP) bit set to 0 for OUT endpoints, or it
 * receives an ACK with the NumP field set to 0 and PP set to 0 for IN
 * endpoints, the controller attempts to search for another stream
 * (CStream) to initiate to the host. However, there are two situations
 * where this behavior is not optimal:
 *  - When the host is setting PP=0 even though it has not finished the
 * stream, or
 *  - When the endpoint on the device is configured with one transfer
 * resource and therefore does not have any other streams to initiate to
 * the host.
 * When this bit is set to '1', the controller ignores the Packet Pending
 * bit for the purposes of stream selection and does not search for another
 * stream when it receives DP(PP=0) or ACK(NumP=0, PP=0). This can enhance
 * the performance when the device system bus bandwidth is low or the host
 * responds to the controller's ERDY transmission very quickly.
 *
 * \details
 * Field: ::VTSS_USB3_DCFG . IGNSTRMPP
 */
#define  VTSS_F_USB3_DCFG_IGNSTRMPP(x)        VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_USB3_DCFG_IGNSTRMPP           VTSS_BIT(23)
#define  VTSS_X_USB3_DCFG_IGNSTRMPP(x)        VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * reserved
 *
 * \details
 * Field: ::VTSS_USB3_DCFG . RESERVED_24
 */
#define  VTSS_F_USB3_DCFG_RESERVED_24(x)      VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_USB3_DCFG_RESERVED_24         VTSS_BIT(24)
#define  VTSS_X_USB3_DCFG_RESERVED_24(x)      VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_DCFG . RESERVED_31_25
 */
#define  VTSS_F_USB3_DCFG_RESERVED_31_25(x)   VTSS_ENCODE_BITFIELD(x,25,7)
#define  VTSS_M_USB3_DCFG_RESERVED_31_25      VTSS_ENCODE_BITMASK(25,7)
#define  VTSS_X_USB3_DCFG_RESERVED_31_25(x)   VTSS_EXTRACT_BITFIELD(x,25,7)


/**
 * \brief Device Control Register

Note:

When Hibernation is not enabled using GCTL.GblHibernationEn field,
 - you can write any value to CSS, CRS, L1HibernationEn, and KeepConnect fields
 - L1HibernationEn, and KeepConnect fields always return 0 when read in this hibernation-disabled state
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_DEV:DCTL
 */
#define VTSS_USB3_DCTL                       VTSS_IOREG(VTSS_TO_USB3,0x31c1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_DCTL . RESERVED_0
 */
#define  VTSS_F_USB3_DCTL_RESERVED_0(x)       VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_USB3_DCTL_RESERVED_0          VTSS_BIT(0)
#define  VTSS_X_USB3_DCTL_RESERVED_0(x)       VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Test Control
 *  - 4'b000: Test mode disabled
 *  - 4'b001: Test_J mode
 *  - 4'b010: Test_K mode
 *  - 4'b011: Test_SE0_NAK mode
 *  - 4'b100: Test_Packet mode
 *  - 4'b101: Test_Force_Enable
 *  - Others: Reserved
 *
 * \details
 * Field: ::VTSS_USB3_DCTL . TSTCTL
 */
#define  VTSS_F_USB3_DCTL_TSTCTL(x)           VTSS_ENCODE_BITFIELD(x,1,4)
#define  VTSS_M_USB3_DCTL_TSTCTL              VTSS_ENCODE_BITMASK(1,4)
#define  VTSS_X_USB3_DCTL_TSTCTL(x)           VTSS_EXTRACT_BITFIELD(x,1,4)

/**
 * \brief
 * ULSTCHNGREQ
 *
 * Software writes this field to issue a USB/Link state change request. A
 * change in this field indicates a new request to the controller.
 *
 * If software wants to issue the same request back-to-back, it must write
 * a 0 to this field between the two requests. The result of the state
 * change request is reflected in the USB/Link State in DSTS. These bits
 * are self-cleared on the MAC Layer exiting suspended state.
 *
 * If software is updating other fields of the DCTL register and not
 * intending to force any link state change, then it must write a 0 to this
 * field.
 *
 * SS Compliance mode is normally entered and controlled by the remote link
 * partner. Refer to the USB 3.0 specification.
 *
 * Alternatively, you can force the local link directly into compliance
 * mode, by resetting the SS link with the RUN/STOP bit set to zero.
 *
 * If you then write '10' to the USB/Link State Change field and '1' to
 * RUN/STOP, the link goes to compliance mode.
 *
 * Once you are in compliance, you may alternately write zero and '10' to
 * this field to advance the compliance pattern.
 *
 * In SS mode:
 *  - Value Requested Link State Transition/Action
 *  - 0  No Action
 *  - 4  SS.Disabled
 *  - 5  Rx.Detect
 *  - 6  SS.Inactive
 *  - 8  U3 exit request
 *  - 10  Compliance
 *  - Others:  Reserved
 * In HS/FS/LS mode:
 *  - ValueRequested USB state transition
 *  - 8  Remote wakeup request
 *  - Others: Reserved
 * The Remote wakeup request must be issued 2us after the device goes into
 * suspend state (DSTS[21:18] is 3 - refer to Table "Fields for Register:
 * DSTS").
 *
 * Note: After coming out of hibernation, software must write 8 (Recovery)
 * into this field to confirm exit from the suspended state.
 *
 * \details
 * Field: ::VTSS_USB3_DCTL . ULSTCHNGREQ
 */
#define  VTSS_F_USB3_DCTL_ULSTCHNGREQ(x)      VTSS_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_USB3_DCTL_ULSTCHNGREQ         VTSS_ENCODE_BITMASK(5,4)
#define  VTSS_X_USB3_DCTL_ULSTCHNGREQ(x)      VTSS_EXTRACT_BITFIELD(x,5,4)

/**
 * \brief
 * Accept U1 Enable
 *  - 1'b0: Controller rejects U1 except when Force_LinkPM_Accept bit is
 * set (default)
 *  - 1'b1: Controller accepts transition to U1 state if nothing is pending
 * on the application side.
 *
 * On USB reset, hardware clears this bit to 0. Software sets this bit
 * after receiving a SetConfiguration command.
 *
 * \details
 * Field: ::VTSS_USB3_DCTL . ACCEPTU1ENA
 */
#define  VTSS_F_USB3_DCTL_ACCEPTU1ENA(x)      VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_USB3_DCTL_ACCEPTU1ENA         VTSS_BIT(9)
#define  VTSS_X_USB3_DCTL_ACCEPTU1ENA(x)      VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Initiate U1 Enable
 *  - 1'b0: May not initiate U1 (default);
 *  - 1'b1: May initiate U1.
 *
 * On USB reset, hardware clears this bit to 0. Software sets this bit
 * after receiving SetFeature(U1_ENABLE), and clears this bit when
 * ClearFeature(U1_ENABLE) is received.
 *
 * If DCTL[9] (AcceptU1Ena) is 0, the link immediately exits U1 state.
 *
 * \details
 * Field: ::VTSS_USB3_DCTL . INITU1ENA
 */
#define  VTSS_F_USB3_DCTL_INITU1ENA(x)        VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_USB3_DCTL_INITU1ENA           VTSS_BIT(10)
#define  VTSS_X_USB3_DCTL_INITU1ENA(x)        VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Accept U2 Enable
 *  - 1'b0: Reject U2 except when Force_LinkPM_Accept bit is set (default)
 *  - 1'b1: Controller accepts transition to U2 state if nothing is pending
 * on the application side.
 *
 * On USB reset, hardware clears this bit to 0. Software sets this bit
 * after receiving a SetConfiguration command.
 *
 * \details
 * Field: ::VTSS_USB3_DCTL . ACCEPTU2ENA
 */
#define  VTSS_F_USB3_DCTL_ACCEPTU2ENA(x)      VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_USB3_DCTL_ACCEPTU2ENA         VTSS_BIT(11)
#define  VTSS_X_USB3_DCTL_ACCEPTU2ENA(x)      VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Initiate U2 Enable
 *  - 1'b0: May not initiate U2 (default)
 *  - 1'b1: May initiate U2
 *
 * On USB reset, hardware clears this bit to 0. Software sets this bit
 * after receiving SetFeature(U2_ENABLE), and clears this bit when
 * ClearFeature(U2_ENABLE) is received.
 *
 * If DCTL[11] (AcceptU2Ena) is 0, the link immediately exits U2 state.
 *
 * \details
 * Field: ::VTSS_USB3_DCTL . INITU2ENA
 */
#define  VTSS_F_USB3_DCTL_INITU2ENA(x)        VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_USB3_DCTL_INITU2ENA           VTSS_BIT(12)
#define  VTSS_X_USB3_DCTL_INITU2ENA(x)        VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_DCTL . RESERVED_15_13
 */
#define  VTSS_F_USB3_DCTL_RESERVED_15_13(x)   VTSS_ENCODE_BITFIELD(x,13,3)
#define  VTSS_M_USB3_DCTL_RESERVED_15_13      VTSS_ENCODE_BITMASK(13,3)
#define  VTSS_X_USB3_DCTL_RESERVED_15_13(x)   VTSS_EXTRACT_BITFIELD(x,13,3)

/**
 * \brief
 * Controller Save State (CSS)
 *
 * This command is similar to the USBCMD.CSS bit in host mode and initiates
 * the save process. When software sets this bit to '1', the controller
 * immediately sets DSTS.SSS to '1'. When the controller has finished the
 * save process, it sets DSTS.SSS to '0'.
 *
 * Note: When read, this field always returns '0'.
 *
 * \details
 * Field: ::VTSS_USB3_DCTL . CSS
 */
#define  VTSS_F_USB3_DCTL_CSS(x)              VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_USB3_DCTL_CSS                 VTSS_BIT(16)
#define  VTSS_X_USB3_DCTL_CSS(x)              VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Controller Restore State (CRS)
 *
 * This command is similar to the USBCMD.CRS bit in host mode and initiates
 * the restore process. When software sets this bit to '1', the controller
 * immediately sets DSTS.RSS to '1'. When the controller has finished the
 * restore process, it sets DSTS.RSS to '0'.
 *
 * Note: When read, this field always returns '0'.
 *
 * \details
 * Field: ::VTSS_USB3_DCTL . CRS
 */
#define  VTSS_F_USB3_DCTL_CRS(x)              VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_USB3_DCTL_CRS                 VTSS_BIT(17)
#define  VTSS_X_USB3_DCTL_CRS(x)              VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * L1HibernationEn
 *
 * When this bit is set along with KeepConnect, the device controller
 * generates a Hibernation Request Event if L1 is enabled and the HIRD
 * value in the LPM token is larger than the threshold programmed in
 * DCTL.HIRD_Thres.
 *
 * The controller does not exit the LPM L1 state until software writes
 * Recovery into the DCTL.ULStChngReq field.
 *
 * This prevents corner cases where the device is entering hibernation at
 * the same time the host is attempting to exit L1.
 *
 * Note: If Hibernation is disabled, that is, GCTL[1].GblHibernationEn = 0,
 * this bit is tied to zero.

 *
 * \details
 * Field: ::VTSS_USB3_DCTL . L1HIBERNATIONEN
 */
#define  VTSS_F_USB3_DCTL_L1HIBERNATIONEN(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_USB3_DCTL_L1HIBERNATIONEN     VTSS_BIT(18)
#define  VTSS_X_USB3_DCTL_L1HIBERNATIONEN(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Keep Connect
 *
 * When '1', this bit enables the save and restore programming model by
 * preventing the controller from disconnecting from the host when
 * DCTL.RunStop is set to '0'.
 *
 * It also enables the Hibernation Request Event to be generated when the
 * link goes to U3 or L2.
 *
 * The device controller disconnects from the host when DCTL.RunStop is set
 * to '0'.
 *
 * This bit indicates whether to preserve this behavior ('0'), or if the
 * controller must not disconnect when RunStop is set to 0 ('1').
 *
 * This bit also prevents the LTSSM from automatically going to U0/L0 when
 * the host requests resume from U3/L2.
 *
 * Note: If Hibernation is disabled, that is, GCTL[1].GblHibernationEn = 0,
 * this bit is tied to zero.

 *
 * \details
 * Field: ::VTSS_USB3_DCTL . KEEPCONNECT
 */
#define  VTSS_F_USB3_DCTL_KEEPCONNECT(x)      VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_USB3_DCTL_KEEPCONNECT         VTSS_BIT(19)
#define  VTSS_X_USB3_DCTL_KEEPCONNECT(x)      VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * LPM NYET Threshold
 *
 * When LPM Errata is enabled:
 *
 * Bits [23:20]: LPM NYET Response Threshold (LPM_NYET_thres)
 *
 * Handshake response to LPM token specified by device application.
 * Response depends on DCFG.LPMCap.
 *  - DCFG.LPMCap is 1'b0 - The controller always responds with Timeout
 * (that is, no response).
 *  - DCFG.LPMCap is 1'b1 - The controller responds with an ACK on
 * successful LPM transaction, which requires that all of the following are
 * satisfied:
 *  - There are no PID or CRC5 errors in both the EXT token and the LPM
 * token (if not true, inactivity results in a timeout ERROR).
 *  - No data is pending in the TxFIFO and RxFIFO is empty (else NYET).
 *  - The BESL value in the LPM token is less than or equal to
 * LPM_NYET_thres[3:0]
 *
 * \details
 * Field: ::VTSS_USB3_DCTL . LPM_NYET_THRES
 */
#define  VTSS_F_USB3_DCTL_LPM_NYET_THRES(x)   VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_USB3_DCTL_LPM_NYET_THRES      VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_USB3_DCTL_LPM_NYET_THRES(x)   VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * HIRD Threshold (HIRD_Thres)
 *
 * The controller asserts output signals utmi_l1_suspend_n and utmi_sleep_n
 * (see "LPM Interface Signals" table in the Databook) on the basis of this
 * signal:
 *
 * The controller asserts utmi_l1_suspend_n to put the PHY into Deep
 * Low-Power mode in L1 when both of the following are true:
 *  - HIRD value is greater than or equal to the value in
 * DCTL.HIRD_Thres[3:0]
 *  - HIRD_Thres[4] is set to 1'b1.
 * The controller asserts utmi_sleep_n on L1 when one of the following is
 * true:
 *  - If the HIRD value is less than HIRD_Thres[3:0] or
 *  - HIRD_Thres[4] is set to 1'b0.
 * Note: This field must be set to '0' during SuperSpeed mode of operation.
 *
 * \details
 * Field: ::VTSS_USB3_DCTL . HIRDTHRES
 */
#define  VTSS_F_USB3_DCTL_HIRDTHRES(x)        VTSS_ENCODE_BITFIELD(x,24,5)
#define  VTSS_M_USB3_DCTL_HIRDTHRES           VTSS_ENCODE_BITMASK(24,5)
#define  VTSS_X_USB3_DCTL_HIRDTHRES(x)        VTSS_EXTRACT_BITFIELD(x,24,5)

/**
 * \brief
 * Reserved1
 *
 * \details
 * Field: ::VTSS_USB3_DCTL . RESERVED_29
 */
#define  VTSS_F_USB3_DCTL_RESERVED_29(x)      VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_USB3_DCTL_RESERVED_29         VTSS_BIT(29)
#define  VTSS_X_USB3_DCTL_RESERVED_29(x)      VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Core Soft Reset
 *
 * Resets the all clock domains as follows:
 *  - This bit clears the interrupts and all the CSRs except GSTS, GSNPSID,
 * GGPIO, GUID, GUSB2PHYCFGn registers, GUSB3PIPECTLn registers, DCFG,
 * DCTL, DEVTEN, and DSTS registers.
 *  - All module state machines (except the SoC Bus Slave Unit) are reset
 * to the IDLE state, and all the TxFIFOs and the RxFIFO are flushed.
 *  - Any transactions on the SoC bus Master are terminated as soon as
 * possible, after gracefully completing the last data phase of a SoC bus
 * transfer. Any transactions on the USB are terminated immediately.
 * The application can write this bit at any time to reset the controller.
 * This is a self-clearing bit; the controller clears this bit after all
 * necessary logic is reset in the controller, which may take several
 * clocks depending on the current state of the controller. Once this bit
 * is cleared, the software must wait at least 3 PHY clocks before
 * accessing the PHY domain (synchronization delay). Typically, software
 * reset is used during software development and also when you dynamically
 * change the PHY selection bits in the USB configuration registers listed
 * above. When you change the PHY, the corresponding clock for the PHY is
 * selected and used in the PHY domain. Once a new clock is selected, the
 * PHY domain must be reset for proper operation.
 *
 * Note: Programming this field with random data causes side effect . Bit
 * Bash register testing is not recommended.
 *
 * \details
 * Field: ::VTSS_USB3_DCTL . CSFTRST
 */
#define  VTSS_F_USB3_DCTL_CSFTRST(x)          VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_USB3_DCTL_CSFTRST             VTSS_BIT(30)
#define  VTSS_X_USB3_DCTL_CSFTRST(x)          VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Run/Stop
 *
 * The software writes 1 to this bit to start the device controller
 * operation.
 *
 * To stop the device controller operation, the software must remove any
 * active transfers and write 0 to this bit. When the controller is
 * stopped, it sets the DSTS.DevCtrlHlt bit when the controller is idle and
 * the lower layer finishes the disconnect process.
 *
 * The Run/Stop bit must be used in following cases as specified:
 *  - After power-on reset and CSR initialization, the software must write
 * 1 to this bit to start the device controller. The controller does not
 * signal connect to the host until this bit is set.
 *  - The software uses this bit to control the device controller to
 * perform a soft disconnect. When the software writes 0 to this bit, the
 * host does not see that the device is connected. The device controller
 * stays in the disconnected state until the software writes 1 to this bit.
 * The minimum duration of keeping this bit cleared is specified in the
 * Note below. If the software attempts a connect after the soft disconnect
 * or detects a disconnect event, it must set DCTL[8:5] to 5 before
 * reasserting the Run/Stop bit.
 *  - When the USB or Link is in a lower power state and the Two Power
 * Rails configuration is selected, software writes 0 to this bit to
 * indicate that it is going to turn off the Core Power Rail. After the
 * software turns on the Core Power Rail again and re-initializes the
 * device controller, it must set this bit to start the device controller.
 * For more details, see "Low Power Operation" section of the Databook.
 * Note: The following is the minimum duration under various conditions for
 * which the soft disconnect (SftDiscon) bit must be set for the USB host
 * to detect a device disconnect:
 *
 * 30ms:
 *  - For SuperSpeed, when the device state is Suspended, Idle, Transmit,
 * or Receive.
 * 10ms:
 *  - For high-speed, when the device state is Suspended, Idle, or not
 * Idle/Suspended (performing transactions)
 *  - For full-speed/low-speed, when the device state is Suspended, Idle,
 * or not Idle/Supended (performing transactions)
 * To accommodate clock jitter, it is recommended that the application add
 * extra delay to the specified minimum duration.

 *
 * \details
 * Field: ::VTSS_USB3_DCTL . RUN_STOP
 */
#define  VTSS_F_USB3_DCTL_RUN_STOP(x)         VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_USB3_DCTL_RUN_STOP            VTSS_BIT(31)
#define  VTSS_X_USB3_DCTL_RUN_STOP(x)         VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief Device Event Enable Register

This register controls the generation of device-specific events (see "Event Buffer Content for Device-Specific Events (DEVT)" section). If an enable bit is set to 0, the event will not be generated.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_DEV:DEVTEN
 */
#define VTSS_USB3_DEVTEN                     VTSS_IOREG(VTSS_TO_USB3,0x31c2)

/**
 * \brief
 * Disconnect Detected Event Enable
 *
 * \details
 * Field: ::VTSS_USB3_DEVTEN . DISSCONNEVTEN
 */
#define  VTSS_F_USB3_DEVTEN_DISSCONNEVTEN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_USB3_DEVTEN_DISSCONNEVTEN     VTSS_BIT(0)
#define  VTSS_X_USB3_DEVTEN_DISSCONNEVTEN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * USB Reset Enable
 *
 * \details
 * Field: ::VTSS_USB3_DEVTEN . USBRSTEVTEN
 */
#define  VTSS_F_USB3_DEVTEN_USBRSTEVTEN(x)    VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_USB3_DEVTEN_USBRSTEVTEN       VTSS_BIT(1)
#define  VTSS_X_USB3_DEVTEN_USBRSTEVTEN(x)    VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Connection Done Enable
 *
 * \details
 * Field: ::VTSS_USB3_DEVTEN . CONNECTDONEEVTEN
 */
#define  VTSS_F_USB3_DEVTEN_CONNECTDONEEVTEN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_USB3_DEVTEN_CONNECTDONEEVTEN  VTSS_BIT(2)
#define  VTSS_X_USB3_DEVTEN_CONNECTDONEEVTEN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * USB/Link State Change Event Enable
 *
 * \details
 * Field: ::VTSS_USB3_DEVTEN . ULSTCNGEN
 */
#define  VTSS_F_USB3_DEVTEN_ULSTCNGEN(x)      VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_USB3_DEVTEN_ULSTCNGEN         VTSS_BIT(3)
#define  VTSS_X_USB3_DEVTEN_ULSTCNGEN(x)      VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * U3/L2 or U3/L2L1 Resume Detected Event Enable.
 *
 * Note:
 *  - If GUCTL1[DEV_DECOUPLE_L1L2_EVT] is enabled, then this bit is for
 * U3/L2 Resume Detected Event Enable.
 *  - If GUCTL1[DEV_DECOUPLE_L1L2_EVT] is not enabled, then this bit is for
 * U3/L2L1 Resume Detected Event Enable.
 *
 * \details
 * Field: ::VTSS_USB3_DEVTEN . WKUPEVTEN
 */
#define  VTSS_F_USB3_DEVTEN_WKUPEVTEN(x)      VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_USB3_DEVTEN_WKUPEVTEN         VTSS_BIT(4)
#define  VTSS_X_USB3_DEVTEN_WKUPEVTEN(x)      VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * This bit enables/disables the generation of the Hibernation Request
 * Event.

 *
 * \details
 * Field: ::VTSS_USB3_DEVTEN . HIBERNATIONREQEVTEN
 */
#define  VTSS_F_USB3_DEVTEN_HIBERNATIONREQEVTEN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_USB3_DEVTEN_HIBERNATIONREQEVTEN  VTSS_BIT(5)
#define  VTSS_X_USB3_DEVTEN_HIBERNATIONREQEVTEN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * U3/L2 or U3/L2L1 Suspend Event Enable.
 *
 * Note:
 *  - If GUCTL1[DEV_DECOUPLE_L1L2_EVT] is enabled, then this bit is for
 * U3/L2 Suspend Event Enable.
 *  - If GUCTL1[DEV_DECOUPLE_L1L2_EVT] is not enabled, then this bit is for
 * U3/L2L1 Suspend Event Enable.
 *
 * \details
 * Field: ::VTSS_USB3_DEVTEN . U3L2L1SUSPEN
 */
#define  VTSS_F_USB3_DEVTEN_U3L2L1SUSPEN(x)   VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_USB3_DEVTEN_U3L2L1SUSPEN      VTSS_BIT(6)
#define  VTSS_X_USB3_DEVTEN_U3L2L1SUSPEN(x)   VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Start of (u)frame
 *
 * \details
 * Field: ::VTSS_USB3_DEVTEN . SOFTEVTEN
 */
#define  VTSS_F_USB3_DEVTEN_SOFTEVTEN(x)      VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_USB3_DEVTEN_SOFTEVTEN         VTSS_BIT(7)
#define  VTSS_X_USB3_DEVTEN_SOFTEVTEN(x)      VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * L1 Suspend Event Enable
 *
 * Note: Only if GUCTL1[DEV_DECOUPLE_L1L2_EVT] is enabled, this bit is for
 * L1 Suspend Event Enable.
 *
 * \details
 * Field: ::VTSS_USB3_DEVTEN . L1SUSPEN
 */
#define  VTSS_F_USB3_DEVTEN_L1SUSPEN(x)       VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_USB3_DEVTEN_L1SUSPEN          VTSS_BIT(8)
#define  VTSS_X_USB3_DEVTEN_L1SUSPEN(x)       VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Erratic Error Event Enable
 *
 * \details
 * Field: ::VTSS_USB3_DEVTEN . ERRTICERREVTEN
 */
#define  VTSS_F_USB3_DEVTEN_ERRTICERREVTEN(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_USB3_DEVTEN_ERRTICERREVTEN    VTSS_BIT(9)
#define  VTSS_X_USB3_DEVTEN_ERRTICERREVTEN(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_DEVTEN . RESERVED_10
 */
#define  VTSS_F_USB3_DEVTEN_RESERVED_10(x)    VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_USB3_DEVTEN_RESERVED_10       VTSS_BIT(10)
#define  VTSS_X_USB3_DEVTEN_RESERVED_10(x)    VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_DEVTEN . DEVTEN_RESERVED_11
 */
#define  VTSS_F_USB3_DEVTEN_DEVTEN_RESERVED_11(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_USB3_DEVTEN_DEVTEN_RESERVED_11  VTSS_BIT(11)
#define  VTSS_X_USB3_DEVTEN_DEVTEN_RESERVED_11(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Vendor Device Test LMP Received Event (VndrDevTstRcvedEn)
 *
 * \details
 * Field: ::VTSS_USB3_DEVTEN . VENDEVTSTRCVDEN
 */
#define  VTSS_F_USB3_DEVTEN_VENDEVTSTRCVDEN(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_USB3_DEVTEN_VENDEVTSTRCVDEN   VTSS_BIT(12)
#define  VTSS_X_USB3_DEVTEN_VENDEVTSTRCVDEN(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * L1 Resume Detected Event Enable.
 *
 * Note: If GUCTL1[DEV_DECOUPLE_L1L2_EVT] is enabled, then this bit is for
 * L1 Resume Detected Event Enable.
 *
 * \details
 * Field: ::VTSS_USB3_DEVTEN . L1WKUPEVTEN
 */
#define  VTSS_F_USB3_DEVTEN_L1WKUPEVTEN(x)    VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_USB3_DEVTEN_L1WKUPEVTEN       VTSS_BIT(14)
#define  VTSS_X_USB3_DEVTEN_L1WKUPEVTEN(x)    VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_DEVTEN . RESERVED_15
 */
#define  VTSS_F_USB3_DEVTEN_RESERVED_15(x)    VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_USB3_DEVTEN_RESERVED_15       VTSS_BIT(15)
#define  VTSS_X_USB3_DEVTEN_RESERVED_15(x)    VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * ECC Error Enable.
 *
 * If this bit is set to 1, the controller reports an ECC error to the
 * software when an uncorrectable ECC occurs internally.
 *
 * \details
 * Field: ::VTSS_USB3_DEVTEN . ECCERREN
 */
#define  VTSS_F_USB3_DEVTEN_ECCERREN(x)       VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_USB3_DEVTEN_ECCERREN          VTSS_BIT(16)
#define  VTSS_X_USB3_DEVTEN_ECCERREN(x)       VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_DEVTEN . RESERVED_31_17
 */
#define  VTSS_F_USB3_DEVTEN_RESERVED_31_17(x)  VTSS_ENCODE_BITFIELD(x,17,15)
#define  VTSS_M_USB3_DEVTEN_RESERVED_31_17     VTSS_ENCODE_BITMASK(17,15)
#define  VTSS_X_USB3_DEVTEN_RESERVED_31_17(x)  VTSS_EXTRACT_BITFIELD(x,17,15)


/**
 * \brief Device Status Register

This register indicates the status of the device controller with respect to USB-related events.

Note:

When Hibernation is not enabled, RSS and SSS fields always return 0 when read.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_DEV:DSTS
 */
#define VTSS_USB3_DSTS                       VTSS_IOREG(VTSS_TO_USB3,0x31c3)

/**
 * \brief
 * Connected Speed (ConnectSpd)
 *
 * Indicates the speed at which the DWC_usb3 controller has come up after
 * speed detection through a chirp sequence.
 *  - 3'b100: SuperSpeed (PHY clock is running at 125 or 250 MHz)
 *  - 3'b000: High-speed (PHY clock is running at 30 or 60 MHz)
 *  - 3'b001: Full-speed (PHY clock is running at 30 or 60 MHz)
 * Low-speed is not supported for devices using a UTMI+ PHY.
 *
 * \details
 * 'h1: Full-speed (PHY clock is running at 30 or 60 MHz)
 * 'h0: High-speed (PHY clock is running at 30 or 60 MHz)
 * 'h4: SuperSpeed (PHY clock is running at 125 or 250 MHz)

 *
 * Field: ::VTSS_USB3_DSTS . CONNECTSPD
 */
#define  VTSS_F_USB3_DSTS_CONNECTSPD(x)       VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_USB3_DSTS_CONNECTSPD          VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_USB3_DSTS_CONNECTSPD(x)       VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Frame/Microframe Number of the Received SOF.
 *
 * When the controller is operating at SuperSpeed,
 *  - [16:3] indicates the uframe/ITP number
 * When the controller is operating at high-speed,
 *  - [16:6] indicates the frame number
 *  - [5:3] indicates the microframe number
 * When the controller is operating at full-speed,
 *  - [16:14] is not used. Software can ignore these 3 bits
 *  - [13:3] indicates the frame number
 * Note: After power-on reset, the controller generates the microframe
 * number internally for every 125us if the USB host has not issued SOF/ITP
 * yet. During P3 state, the duration of SOFFN is based on the suspend_clk
 * frequency.
 *
 * \details
 * Field: ::VTSS_USB3_DSTS . SOFFN
 */
#define  VTSS_F_USB3_DSTS_SOFFN(x)            VTSS_ENCODE_BITFIELD(x,3,14)
#define  VTSS_M_USB3_DSTS_SOFFN               VTSS_ENCODE_BITMASK(3,14)
#define  VTSS_X_USB3_DSTS_SOFFN(x)            VTSS_EXTRACT_BITFIELD(x,3,14)

/**
 * \brief
 * RxFIFO Empty.
 *
 * \details
 * Field: ::VTSS_USB3_DSTS . RXFIFOEMPTY
 */
#define  VTSS_F_USB3_DSTS_RXFIFOEMPTY(x)      VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_USB3_DSTS_RXFIFOEMPTY         VTSS_BIT(17)
#define  VTSS_X_USB3_DSTS_RXFIFOEMPTY(x)      VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * USBLNKST.
 *
 * USB/Link State
 *
 * In SS mode: LTSSM State
 *  - 4'h0: U0
 *  - 4'h1: U1
 *  - 4'h2: U2
 *  - 4'h3: U3
 *  - 4'h4: SS_DIS
 *  - 4'h5: RX_DET
 *  - 4'h6: SS_INACT
 *  - 4'h7: POLL
 *  - 4'h8: RECOV
 *  - 4'h9: HRESET
 *  - 4'ha: CMPLY
 *  - 4'hb: LPBK
 *  - 4'hf: Resume/Reset
 * In HS/FS/LS mode:
 *  - 4'h0: On state
 *  - 4'h2: Sleep (L1) state
 *  - 4'h3: Suspend (L2) state
 *  - 4'h4: Disconnected state (Default state)
 *  - 4'h5: Early Suspend state (valid only when Hibernation is disabled,
 * GCTL[1].GblHibernationEn = 0)
 *  - 4'he: Reset (valid only when Hibernation is enabled,
 * GCTL[1].GblHibernationEn = 1)
 *  - 4'hf: Resume (valid only when Hibernation is enabled,
 * GCTL[1].GblHibernationEn = 1)
 * The link state Resume/Reset indicates that the controller received a
 * resume or USB reset request from the host while the link was in
 * hibernation. Software must write '8' (Recovery) to the DCTL.ULStChngReq
 * field to acknowledge the resume/reset request.
 *
 * When Hibernation is enabled, GCTL[1].GblHibernationEn = 1, this field
 * USBLnkSt is valid only when DCTL[31].Run/Stop set to '1' and
 * DSTS[29].DCNRD = 0.
 *
 * The Early Suspend link state is an early indication of device suspend in
 * HS/FS. The link state changes to Early Suspend after detecting bus idle
 * for 3ms.
 *  - In HS operation, this is an indication that the USB bus (that is,
 * LineState) has been in idle (SE0) for 3ms. However, it does not confirm
 * whether the next process is Suspend or Reset. The device checks the bus
 * again after pull up enable delay and if the line state indicates Suspend
 * (full speed J), then the device waits for an additional time (~3ms) to
 * indicate the actual Suspend state.
 *  - In FS operation, this is an indication that the USB bus (that is,
 * LineState) has been in idle (J) for 3ms. The device waits for an
 * additional time (~3ms of Idle) to indicate the actual Suspend state.

 *
 * \details
 * Field: ::VTSS_USB3_DSTS . USBLNKST
 */
#define  VTSS_F_USB3_DSTS_USBLNKST(x)         VTSS_ENCODE_BITFIELD(x,18,4)
#define  VTSS_M_USB3_DSTS_USBLNKST            VTSS_ENCODE_BITMASK(18,4)
#define  VTSS_X_USB3_DSTS_USBLNKST(x)         VTSS_EXTRACT_BITFIELD(x,18,4)

/**
 * \brief
 * Device Controller Halted
 *
 * This bit is set to 0 when the Run/Stop bit in the DCTL register is set
 * to 1.
 *
 * The controller sets this bit to 1 when, after SW sets Run/Stop to 0, the
 * controller is idle and the lower layer finishes the disconnect process.
 *
 * When Halted=1, the controller does not generate Device events.
 *
 * Note:
 *  - The controller does not set this bit to 1 if GEVNTCOUNTn has some
 * valid value. Software needs to acknowledge the events that are generated
 * (by writing to GEVNTCOUNTn) while it is waiting for this bit to be set
 * to 1.
 *  - When Interrupt Moderation is enabled, there could be delay in raising
 * the interrupt line when the event count is non-zero. Software should
 * read the GEVNTCOUNT register directly and acknowledge them.
 *
 * \details
 * Field: ::VTSS_USB3_DSTS . DEVCTRLHLT
 */
#define  VTSS_F_USB3_DSTS_DEVCTRLHLT(x)       VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_USB3_DSTS_DEVCTRLHLT          VTSS_BIT(22)
#define  VTSS_X_USB3_DSTS_DEVCTRLHLT(x)       VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Core Idle
 *
 * The bit indicates that the controller finished transferring all RxFIFO
 * data to system memory, writing out all completed descriptors, and all
 * Event Counts are zero.
 *
 * Note: While testing for Reset values, mask out the read value. This bit
 * represents the changing state of the controller and does not hold a
 * static value.
 *
 * \details
 * Field: ::VTSS_USB3_DSTS . COREIDLE
 */
#define  VTSS_F_USB3_DSTS_COREIDLE(x)         VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_USB3_DSTS_COREIDLE            VTSS_BIT(23)
#define  VTSS_X_USB3_DSTS_COREIDLE(x)         VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * SSS Save State Status
 *
 * This bit is similar to the USBSTS.SSS in host mode.
 *
 * When the controller has finished the save process, it completes the
 * command by setting DSTS.SSS to '0'.
 *
 * \details
 * Field: ::VTSS_USB3_DSTS . SSS
 */
#define  VTSS_F_USB3_DSTS_SSS(x)              VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_USB3_DSTS_SSS                 VTSS_BIT(24)
#define  VTSS_X_USB3_DSTS_SSS(x)              VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * RSS Restore State Status
 *
 * This bit is similar to the USBSTS.RSS in host mode.
 *
 * When the controller finishes the restore process, it completes the
 * command by setting DSTS.RSS to '0'.
 *
 * \details
 * Field: ::VTSS_USB3_DSTS . RSS
 */
#define  VTSS_F_USB3_DSTS_RSS(x)              VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_USB3_DSTS_RSS                 VTSS_BIT(25)
#define  VTSS_X_USB3_DSTS_RSS(x)              VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_DSTS . RESERVED_27_26
 */
#define  VTSS_F_USB3_DSTS_RESERVED_27_26(x)   VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_USB3_DSTS_RESERVED_27_26      VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_USB3_DSTS_RESERVED_27_26(x)   VTSS_EXTRACT_BITFIELD(x,26,2)

/**
 * \brief
 * Save Restore Error. Currently not supported.
 *
 * \details
 * Field: ::VTSS_USB3_DSTS . SRE
 */
#define  VTSS_F_USB3_DSTS_SRE(x)              VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_USB3_DSTS_SRE                 VTSS_BIT(28)
#define  VTSS_X_USB3_DSTS_SRE(x)              VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Device Controller Not Ready
 *
 * The bit indicates that the controller is in the process of completing
 * the state transitions after exiting from hibernation.
 *
 * To complete the state transitions, it takes 256 bus clock cycles from
 * the time DCTL[31].Run/Stop is set. During hibernation, if the UTMI/ULPI
 * PHY is in suspended state, then the 256-bus clock cycle delay starts
 * after the PHY exited suspended state. Software must set
 * DCTL[31].Run/Stop to '1' and wait for this bit to be de-asserted to zero
 * before processing DSTS.USBLnkSt.
 *
 * This bit is valid only when DWC_USB3_EN_PWROPT is set to 2 and
 * GCTL[1].GblHibernationEn =1.

 *
 * \details
 * Field: ::VTSS_USB3_DSTS . DCNRD
 */
#define  VTSS_F_USB3_DSTS_DCNRD(x)            VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_USB3_DSTS_DCNRD               VTSS_BIT(29)
#define  VTSS_X_USB3_DSTS_DCNRD(x)            VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_DSTS . RESERVED_31_30
 */
#define  VTSS_F_USB3_DSTS_RESERVED_31_30(x)   VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_USB3_DSTS_RESERVED_31_30      VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_USB3_DSTS_RESERVED_31_30(x)   VTSS_EXTRACT_BITFIELD(x,30,2)


/**
 * \brief Device Generic Command Parameter Register

This register indicates the device command parameter. This must be programmed before or along with the device command. The available device commands are listed in DGCMD register.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_DEV:DGCMDPAR
 */
#define VTSS_USB3_DGCMDPAR                   VTSS_IOREG(VTSS_TO_USB3,0x31c4)

/**
 * \brief
 * PARAMETER
 *
 * \details
 * Field: ::VTSS_USB3_DGCMDPAR . DGCMDPAR_PARAMETER
 */
#define  VTSS_F_USB3_DGCMDPAR_DGCMDPAR_PARAMETER(x)  (x)
#define  VTSS_M_USB3_DGCMDPAR_DGCMDPAR_PARAMETER     0xffffffff
#define  VTSS_X_USB3_DGCMDPAR_DGCMDPAR_PARAMETER(x)  (x)


/**
 * \brief Device Generic Command Register

This register enables software to program the controller using a single generic command interface to send link management packets and notifications. This register contains command, control, and status fields relevant to the current generic command, while the DGCMDPAR register provides the command parameter.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_DEV:DGCMD
 */
#define VTSS_USB3_DGCMD                      VTSS_IOREG(VTSS_TO_USB3,0x31c5)

/**
 * \brief
 * CMDTYP
 *
 * Generic Command Type
 *
 * Specifies the type of generic command the software driver is requesting
 * the controller to perform.
 *  - 02h: Set Periodic Parameters
 *  - 04h: Set Scratchpad Buffer Array Address Lo
 *  - 05h: Set Scratchpad Buffer Array Address Hi
 *  - 07h: Transmit Device Notification
 *  - 09h: Selected FIFO Flush
 *  - 0Ah: All FIFO Flush
 *  - 0Ch: Set Endpoint NRDY
 *  - 10h: Run SoC Bus LoopBack Test
 *  - 11h: Restart After Disconnect
 * All other values are reserved.
 *
 * \details
 * Field: ::VTSS_USB3_DGCMD . DGCMD_CMDTYP
 */
#define  VTSS_F_USB3_DGCMD_DGCMD_CMDTYP(x)    VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_USB3_DGCMD_DGCMD_CMDTYP       VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_USB3_DGCMD_DGCMD_CMDTYP(x)    VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Command Interrupt on Complete
 *
 * When this bit is set, the device controller issues a Generic Command
 * Completion event after executing the command.
 *
 * Note that this interrupt is mapped to DCFG.IntrNum.
 *
 * Note: This field must not set to '1' if the DCTL.RunStop field is '0'.
 *
 * \details
 * Field: ::VTSS_USB3_DGCMD . DGCMD_CMDIOC
 */
#define  VTSS_F_USB3_DGCMD_DGCMD_CMDIOC(x)    VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_USB3_DGCMD_DGCMD_CMDIOC       VTSS_BIT(8)
#define  VTSS_X_USB3_DGCMD_DGCMD_CMDIOC(x)    VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_DGCMD . DGCMD_RESERVED_9
 */
#define  VTSS_F_USB3_DGCMD_DGCMD_RESERVED_9(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_USB3_DGCMD_DGCMD_RESERVED_9   VTSS_BIT(9)
#define  VTSS_X_USB3_DGCMD_DGCMD_RESERVED_9(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Command Active
 *
 * The software sets this bit to 1 to enable the device controller to
 * execute the generic command.
 *
 * The device controller sets this bit to 0 after executing the command.
 *
 * \details
 * Field: ::VTSS_USB3_DGCMD . DGCMD_CMDACT
 */
#define  VTSS_F_USB3_DGCMD_DGCMD_CMDACT(x)    VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_USB3_DGCMD_DGCMD_CMDACT       VTSS_BIT(10)
#define  VTSS_X_USB3_DGCMD_DGCMD_CMDACT(x)    VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_DGCMD . DGCMD_RESERVED_11
 */
#define  VTSS_F_USB3_DGCMD_DGCMD_RESERVED_11(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_USB3_DGCMD_DGCMD_RESERVED_11  VTSS_BIT(11)
#define  VTSS_X_USB3_DGCMD_DGCMD_RESERVED_11(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Command Status
 *  - 1: CmdErr:  Indicates that the device controller encountered an error
 * while processing the command.
 *  - 0: Indicates command success
 *
 * \details
 * Field: ::VTSS_USB3_DGCMD . DGCMD_CMDSTATUS
 */
#define  VTSS_F_USB3_DGCMD_DGCMD_CMDSTATUS(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_USB3_DGCMD_DGCMD_CMDSTATUS     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_USB3_DGCMD_DGCMD_CMDSTATUS(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_DGCMD . RESERVED_31_16
 */
#define  VTSS_F_USB3_DGCMD_RESERVED_31_16(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_DGCMD_RESERVED_31_16     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_DGCMD_RESERVED_31_16(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Device Active USB Endpoint Enable Register.

This register indicates whether a USB endpoint is active in a given configuration or interface.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_DEV:DALEPENA
 */
#define VTSS_USB3_DALEPENA                   VTSS_IOREG(VTSS_TO_USB3,0x31c8)

/**
 * \brief
 * USBACTEP
 *
 * USB Active Endpoints (USBActEP)
 *
 * This field indicates if a USB endpoint is active in the current
 * configuration and interface. It applies to USB IN endpoints 0.15 and OUT
 * endpoints 0.15, with one bit for each of the 32 possible endpoints. Even
 * numbers are for USB OUT endpoints, and odd numbers are for USB IN
 * endpoints, as follows:
 *  - Bit[0]: USB EP0-OUT
 *  - Bit[1]: USB EP0-IN
 *  - Bit[2]: USB EP1-OUT
 *  - Bit[3]: USB EP1-IN
 * The entity programming this register must set bits 0 and 1 because they
 * enable control endpoints that map to physical endpoints (resources)
 * after USBReset.
 *
 * Hardware clears these bits for all endpoints (other than EP0-OUT and
 * EP0-IN) after detecting a USB reset event. After receiving
 * SetConfiguration and SetInterface requests, the application must program
 * endpoint registers accordingly and set these bits.
 *
 * For more information, see "Flexible Endpoint Mapping" section in the
 * Databook.

 *
 * \details
 * Field: ::VTSS_USB3_DALEPENA . USBACTEP
 */
#define  VTSS_F_USB3_DALEPENA_USBACTEP(x)     (x)
#define  VTSS_M_USB3_DALEPENA_USBACTEP        0xffffffff
#define  VTSS_X_USB3_DALEPENA_USBACTEP(x)     (x)


/**
 * \brief Reserved
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_DEV:RSVD
 *
 * @param ri Register: RSVD (??), 0-31
 */
#define VTSS_USB3_RSVD(ri)                   VTSS_IOREG(VTSS_TO_USB3,0x31c9 + (ri))

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_RSVD . RESERVED_31_0
 */
#define  VTSS_F_USB3_RSVD_RESERVED_31_0(x)    (x)
#define  VTSS_M_USB3_RSVD_RESERVED_31_0       0xffffffff
#define  VTSS_X_USB3_RSVD_RESERVED_31_0(x)    (x)


/**
 * \brief Device Physical Endpoint-n Command Parameter 2 Register (DEPCMDPAR2n)

This register indicates the physical endpoint command Parameter 2. It must be programmed before issuing the command.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_DEV:DEPCMDPAR2
 *
 * @param ri Register: DEPCMDPAR2 (??), 0-7
 */
#define VTSS_USB3_DEPCMDPAR2(ri)             VTSS_IOREG(VTSS_TO_USB3,0x3200 + (ri))

/**
 * \brief
 * PARAMETER
 *
 * \details
 * Field: ::VTSS_USB3_DEPCMDPAR2 . DEPCMDPAR2_PARAMETER
 */
#define  VTSS_F_USB3_DEPCMDPAR2_DEPCMDPAR2_PARAMETER(x)  (x)
#define  VTSS_M_USB3_DEPCMDPAR2_DEPCMDPAR2_PARAMETER     0xffffffff
#define  VTSS_X_USB3_DEPCMDPAR2_DEPCMDPAR2_PARAMETER(x)  (x)


/**
 * \brief Device Physical Endpoint-n Command Parameter 1 Register (DEPCMDPAR1n)
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_DEV:DEPCMDPAR1
 *
 * @param ri Register: DEPCMDPAR1 (??), 0-7
 */
#define VTSS_USB3_DEPCMDPAR1(ri)             VTSS_IOREG(VTSS_TO_USB3,0x3201 + (ri))

/**
 * \brief
 * PARAMETER
 *
 * \details
 * Field: ::VTSS_USB3_DEPCMDPAR1 . DEPCMDPAR1_PARAMETER
 */
#define  VTSS_F_USB3_DEPCMDPAR1_DEPCMDPAR1_PARAMETER(x)  (x)
#define  VTSS_M_USB3_DEPCMDPAR1_DEPCMDPAR1_PARAMETER     0xffffffff
#define  VTSS_X_USB3_DEPCMDPAR1_DEPCMDPAR1_PARAMETER(x)  (x)


/**
 * \brief Device Physical Endpoint-n Command Parameter 0 Register (DEPCMDPAR0n)
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_DEV:DEPCMDPAR0
 *
 * @param ri Register: DEPCMDPAR0 (??), 0-7
 */
#define VTSS_USB3_DEPCMDPAR0(ri)             VTSS_IOREG(VTSS_TO_USB3,0x3202 + (ri))

/**
 * \brief
 * PARAMETER
 *
 * \details
 * Field: ::VTSS_USB3_DEPCMDPAR0 . DEPCMDPAR0_PARAMETER
 */
#define  VTSS_F_USB3_DEPCMDPAR0_DEPCMDPAR0_PARAMETER(x)  (x)
#define  VTSS_M_USB3_DEPCMDPAR0_DEPCMDPAR0_PARAMETER     0xffffffff
#define  VTSS_X_USB3_DEPCMDPAR0_DEPCMDPAR0_PARAMETER(x)  (x)


/**
 * \brief Device Physical Endpoint-n Command Register

This register enables software to issue physical endpoint-specific commands. This register contains command, control, and status fields relevant to the current generic command, while the DEPCMDPAR[2:0]n registers provide command parameters and return status information.

Several fields (including Command Type) are write-only, so their read values are undefined. After power-on, prior to issuing the first endpoint command, the read value of this register is undefined. In particular, the CmdAct bit may be set after power-on. In this case, it is safe to issue an endpoint command.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_DEV:DEPCMD
 *
 * @param ri Register: DEPCMD (??), 0-7
 */
#define VTSS_USB3_DEPCMD(ri)                 VTSS_IOREG(VTSS_TO_USB3,0x3203 + (ri))

/**
 * \brief
 * Command Type
 *
 * Specifies the type of command the software driver is requesting the
 * controller to perform.
 *  - 00h: Reserved
 *  - 01h: Set Endpoint Configuration - -64 or 96-bit Parameter
 *  - 02h: Set Endpoint Transfer Resource Configuration - 32-bit Parameter
 *  - 03h: Get Endpoint State - No Parameter Needed
 *  - 04h: Set Stall - No Parameter Needed
 *  - 05h: Clear Stall (see Set Stall) - No Parameter Needed
 *  - 06h: Start Transfer - 64-bit Parameter
 *  - 07h: Update Transfer - No Parameter Needed
 *  - 08h: End Transfer - No Parameter Needed
 *  - 09h: Start New Configuration - No Parameter Needed
 *
 * \details
 * Field: ::VTSS_USB3_DEPCMD . DEPCMD_CMDTYP
 */
#define  VTSS_F_USB3_DEPCMD_DEPCMD_CMDTYP(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_USB3_DEPCMD_DEPCMD_CMDTYP     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_USB3_DEPCMD_DEPCMD_CMDTYP(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_DEPCMD . RESERVED_7_4
 */
#define  VTSS_F_USB3_DEPCMD_RESERVED_7_4(x)   VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_USB3_DEPCMD_RESERVED_7_4      VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_USB3_DEPCMD_RESERVED_7_4(x)   VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * CMDIOC
 *
 * Command Interrupt on Complete (CmdIOC)
 *
 * When this bit is set, the device controller issues a generic Endpoint
 * Command Complete event after executing the command.
 *
 * Note that this interrupt is mapped to DEPCFG.IntrNum.
 * When the DEPCFG command is executed, the command interrupt on completion
 * goes to the interrupt pointed by the DEPCFG.IntrNum in the current
 * command.
 *
 * Note: This field must not set to 1 if the DCTL.RunStop field is 0.

 *
 * \details
 * Field: ::VTSS_USB3_DEPCMD . DEPCMD_CMDIOC
 */
#define  VTSS_F_USB3_DEPCMD_DEPCMD_CMDIOC(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_USB3_DEPCMD_DEPCMD_CMDIOC     VTSS_BIT(8)
#define  VTSS_X_USB3_DEPCMD_DEPCMD_CMDIOC(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_DEPCMD . DEPCMD_RESERVED_9
 */
#define  VTSS_F_USB3_DEPCMD_DEPCMD_RESERVED_9(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_USB3_DEPCMD_DEPCMD_RESERVED_9  VTSS_BIT(9)
#define  VTSS_X_USB3_DEPCMD_DEPCMD_RESERVED_9(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Command Active (CmdAct)
 *
 * Software sets this bit to 1 to enable the device endpoint controller to
 * execute the generic command.
 *
 * The device controller sets this bit to 0 when the CmdStatus field is
 * valid and the endpoint is ready to accept another command. This does not
 * imply that all the effects of the previously-issued command have taken
 * place.
 *
 * \details
 * Field: ::VTSS_USB3_DEPCMD . DEPCMD_CMDACT
 */
#define  VTSS_F_USB3_DEPCMD_DEPCMD_CMDACT(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_USB3_DEPCMD_DEPCMD_CMDACT     VTSS_BIT(10)
#define  VTSS_X_USB3_DEPCMD_DEPCMD_CMDACT(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * HighPriority/ForceRM (HiPri_ForceRM)
 *  - HighPriority: Only valid for Start Transfer command
 *  - ForceRM: Only valid for End Transfer command
 *  - ClearPendIN: Only valid for Clear Stall command . Software sets this
 * bit to clear any pending IN transaction (on that endpoint) stuck at the
 * lower layers when a Clear Stall command is issued.
 *
 * \details
 * Field: ::VTSS_USB3_DEPCMD . HIPRI_FORCERM
 */
#define  VTSS_F_USB3_DEPCMD_HIPRI_FORCERM(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_USB3_DEPCMD_HIPRI_FORCERM     VTSS_BIT(11)
#define  VTSS_X_USB3_DEPCMD_HIPRI_FORCERM(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Command Completion Status (CmdStatus)
 *
 * Additional information about the completion of this command is available
 * in this field. The information is in the same format as bits 15:12 of
 * the Endpoint Command Complete event, see "Device Endpoint-n Events:
 * DEPEVT" table in the Programming Guide.
 *
 * \details
 * Field: ::VTSS_USB3_DEPCMD . DEPCMD_CMDSTATUS
 */
#define  VTSS_F_USB3_DEPCMD_DEPCMD_CMDSTATUS(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_USB3_DEPCMD_DEPCMD_CMDSTATUS     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_USB3_DEPCMD_DEPCMD_CMDSTATUS(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * Command Parameters or Event Parameters
 *
 * Command Parameters (CommandParam), when this register is written:
 *
 * For Start Transfer command:
 *  -  [31:16]: StreamID. The USB StreamID assigned to this transfer
 * For Start Transfer command applied to an isochronous endpoint
 *  - [31:16]: StartMicroFramNum: Indicates the (micro)frame number to
 * which the first TRB applies.
 * For Update Transfer, End Transfer, and Start New Configuration commands
 *  - [22:16]: Transfer Resource Index (XferRscIdx). The hardware-assigned
 * transfer resource index for the transfer, which was returned in response
 * to the Start Transfer command. The application software-assigned
 * transfer resource index for a Start New Configuration command.
 * Event Parameters (EventParam), when this register is read. Refer to bits
 * [31:16] in Table "Device Endpoint-n Events: DEPEVT".
 *
 * \details
 * Field: ::VTSS_USB3_DEPCMD . COMMANDPARAM
 */
#define  VTSS_F_USB3_DEPCMD_COMMANDPARAM(x)   VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_DEPCMD_COMMANDPARAM      VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_DEPCMD_COMMANDPARAM(x)   VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Device Interrupt Moderation Register (DEV_IMOD)

This register controls the Interrupt Moderation feature that allows the device software to throttle the interrupt rate.

Key Functions:
 - Interrupt Moderation is enabled only when the IMOD Interval is programmed to a non-zero value.
 - Interrupt is asserted whenever the IMOD (down) counter is 0, EVNT_HANDLER_BUSY is 0, and there are pending events (that is, event count is non-zero)
 - GEVNTCOUNT[EVNT_HANDLER_BUSY] is set by hardware when interrupt is asserted, and cleared by software when interrupt processing is completed.
 - The Interrupt line is de-asserted after the first write to the event count.
 - IMOD counter is loaded with IMOD interval whenever the Interrupt line is de-asserted.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_DEV:DEV_IMOD
 */
#define VTSS_USB3_DEV_IMOD                   VTSS_IOREG(VTSS_TO_USB3,0x3280)

/**
 * \brief
 * Moderation Interval (DEVICE_IMODI)
 *
 * This field holds the minimum inter-interrupt interval between events.
 * The interval is specified in terms of 250ns increments.
 *
 * A value of 0 disables the interrupt throttling logic and interrupts are
 * generated immediately if event count becomes non-zero.
 *
 * In scaledown simulation mode, 4 ram clocks are used to time 250ns.
 *
 * \details
 * Field: ::VTSS_USB3_DEV_IMOD . DEVICE_IMODI
 */
#define  VTSS_F_USB3_DEV_IMOD_DEVICE_IMODI(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_USB3_DEV_IMOD_DEVICE_IMODI     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_USB3_DEV_IMOD_DEVICE_IMODI(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Interrupt Moderation Down Counter
 *
 * Loaded with the DEVICE_IMODI value, whenever the hardware interrupt(n)
 * line is de-asserted from the asserted state, counts down to 0, and
 * stops.
 *
 * The interrupt(n) is signaled whenever this counter is 0,
 * EVNT_HANDLER_BUSY is 0, and there are pending events (that is, event
 * count is non-zero).
 *
 * This counter may be directly written by software at any time to alter
 * the interrupt rate.
 *
 * \details
 * Field: ::VTSS_USB3_DEV_IMOD . DEVICE_IMODC
 */
#define  VTSS_F_USB3_DEV_IMOD_DEVICE_IMODC(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_DEV_IMOD_DEVICE_IMODC     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_DEV_IMOD_DEVICE_IMODC(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * Register Group: \a USB3:DWC_USB3_BLOCK_LINK
 *
 * USB 3.0 Link Register Block
 */


/**
 * \brief U1/U2 LFPS Rx Timer Register
 - Link Layer Register for U1/U2 LFPS RX Timers.
 - This register is common for all SS ports.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_LINK:LU1LFPSRXTIM
 */
#define VTSS_USB3_LU1LFPSRXTIM               VTSS_IOREG(VTSS_TO_USB3,0x3400)

/**
 * \brief
 * Programmable U1U2 EXIT RESP RX CLKS
 *  - Applicable to locally initiated Ux exit: Minimum LFPS reception from
 * remote to consider Ux exit handshake is successful.
 *  - This field is encoded as the pipe clk (8ns) count for the LFPS.
 *  -- 1: 8ns
 *  -- 2: 16ns
 *  -- 3: 24ns, and so on
 *
 * \details
 * Field: ::VTSS_USB3_LU1LFPSRXTIM . U1U2_EXIT_RSP_RX_CLK
 */
#define  VTSS_F_USB3_LU1LFPSRXTIM_U1U2_EXIT_RSP_RX_CLK(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_USB3_LU1LFPSRXTIM_U1U2_EXIT_RSP_RX_CLK     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_USB3_LU1LFPSRXTIM_U1U2_EXIT_RSP_RX_CLK(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Programmable U1U2 LFPS EXIT RX CLKS
 *  - Applicable to Remote Partner initiated Ux exit: Time to recognize
 * valid Ux exit request from the remote partner.
 *  - This field is encoded as the pipe clk (8ns) count for the LFPS.
 *  -- 1: 8ns
 *  -- 2: 16ns
 *  -- 3: 24ns, and so on
 *
 * \details
 * Field: ::VTSS_USB3_LU1LFPSRXTIM . U1U2_LFPS_EXIT_RX_CLK
 */
#define  VTSS_F_USB3_LU1LFPSRXTIM_U1U2_LFPS_EXIT_RX_CLK(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_USB3_LU1LFPSRXTIM_U1U2_LFPS_EXIT_RX_CLK     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_USB3_LU1LFPSRXTIM_U1U2_LFPS_EXIT_RX_CLK(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_LU1LFPSRXTIM . RESERVED_16_31
 */
#define  VTSS_F_USB3_LU1LFPSRXTIM_RESERVED_16_31(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_LU1LFPSRXTIM_RESERVED_16_31     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_LU1LFPSRXTIM_RESERVED_16_31(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Link Setting Register
 - Link Layer User Control Register for enabling Link/PHY-specific options.
 - This register is common for all SS ports.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_LINK:LINK_SETTINGS
 */
#define VTSS_USB3_LINK_SETTINGS              VTSS_IOREG(VTSS_TO_USB3,0x3408)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_LINK_SETTINGS . RESERVED_0_19
 */
#define  VTSS_F_USB3_LINK_SETTINGS_RESERVED_0_19(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_USB3_LINK_SETTINGS_RESERVED_0_19     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_USB3_LINK_SETTINGS_RESERVED_0_19(x)  VTSS_EXTRACT_BITFIELD(x,0,20)

/**
 * \brief
 * Programmable PM_ENTRY_TIMER
 *
 * This field specifies PM_ENTRY_TIMER value in us.
 *
 * \details
 * Field: ::VTSS_USB3_LINK_SETTINGS . PM_ENTRY_TIMER_US
 */
#define  VTSS_F_USB3_LINK_SETTINGS_PM_ENTRY_TIMER_US(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_USB3_LINK_SETTINGS_PM_ENTRY_TIMER_US     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_USB3_LINK_SETTINGS_PM_ENTRY_TIMER_US(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * Programmable PM_LC_TIMER
 *
 * This field specifies PM_LC_TIMER value in us.
 *
 * \details
 * Field: ::VTSS_USB3_LINK_SETTINGS . PM_LC_TIMER_US
 */
#define  VTSS_F_USB3_LINK_SETTINGS_PM_LC_TIMER_US(x)  VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_USB3_LINK_SETTINGS_PM_LC_TIMER_US     VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_USB3_LINK_SETTINGS_PM_LC_TIMER_US(x)  VTSS_EXTRACT_BITFIELD(x,24,3)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_LINK_SETTINGS . RESERVED_27
 */
#define  VTSS_F_USB3_LINK_SETTINGS_RESERVED_27(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_USB3_LINK_SETTINGS_RESERVED_27  VTSS_BIT(27)
#define  VTSS_X_USB3_LINK_SETTINGS_RESERVED_27(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Programmable U1 MIN RESIDENCY TIMER
 *
 * This field specifies U1 MIN RESIDENCY TIMER value in us. Set to 0 to
 * disable the timer.
 *
 * \details
 * Field: ::VTSS_USB3_LINK_SETTINGS . U1_RESID_TIMER_US
 */
#define  VTSS_F_USB3_LINK_SETTINGS_U1_RESID_TIMER_US(x)  VTSS_ENCODE_BITFIELD(x,28,3)
#define  VTSS_M_USB3_LINK_SETTINGS_U1_RESID_TIMER_US     VTSS_ENCODE_BITMASK(28,3)
#define  VTSS_X_USB3_LINK_SETTINGS_U1_RESID_TIMER_US(x)  VTSS_EXTRACT_BITFIELD(x,28,3)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_LINK_SETTINGS . RESERVED_31
 */
#define  VTSS_F_USB3_LINK_SETTINGS_RESERVED_31(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_USB3_LINK_SETTINGS_RESERVED_31  VTSS_BIT(31)
#define  VTSS_X_USB3_LINK_SETTINGS_RESERVED_31(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief Link User Control Register
 - Link Layer User Control Register for enabling Link/PHY-specific options.
 - This register is common for all SS ports.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_LINK:LLUCTL
 */
#define VTSS_USB3_LLUCTL                     VTSS_IOREG(VTSS_TO_USB3,0x3409)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_LLUCTL . RESERVED_0_4
 */
#define  VTSS_F_USB3_LLUCTL_RESERVED_0_4(x)   VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_USB3_LLUCTL_RESERVED_0_4      VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_USB3_LLUCTL_RESERVED_0_4(x)   VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * no_ux_exit_p0_trans.
 *
 * Link LTSSM detects Ux_exit LFPS when P0 transition is on-going by
 * default. If this bit is set, Link LTSSM may miss Ux_exit LFPS when P0
 * transition is happening.
 *
 * \details
 * Field: ::VTSS_USB3_LLUCTL . NO_UX_EXIT_P0_TRANS
 */
#define  VTSS_F_USB3_LLUCTL_NO_UX_EXIT_P0_TRANS(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_USB3_LLUCTL_NO_UX_EXIT_P0_TRANS  VTSS_BIT(5)
#define  VTSS_X_USB3_LLUCTL_NO_UX_EXIT_P0_TRANS(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_LLUCTL . RESERVED_6
 */
#define  VTSS_F_USB3_LLUCTL_RESERVED_6(x)     VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_USB3_LLUCTL_RESERVED_6        VTSS_BIT(6)
#define  VTSS_X_USB3_LLUCTL_RESERVED_6(x)     VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Mask pipe reset.
 *
 * If this bit is set, controller blocks pipe_reset_n from going to the PHY
 * when DisRxDetU3RxDet=1.
 *
 * \details
 * Field: ::VTSS_USB3_LLUCTL . MASK_PIPE_RESET
 */
#define  VTSS_F_USB3_LLUCTL_MASK_PIPE_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_USB3_LLUCTL_MASK_PIPE_RESET   VTSS_BIT(7)
#define  VTSS_X_USB3_LLUCTL_MASK_PIPE_RESET(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_LLUCTL . RESERVED_8_10
 */
#define  VTSS_F_USB3_LLUCTL_RESERVED_8_10(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_USB3_LLUCTL_RESERVED_8_10     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_USB3_LLUCTL_RESERVED_8_10(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * en_reset_pipe_after_phy_mux.
 *
 * The controller issues USB 3.0 PHY reset after DisRxDetU3RxDet is
 * de-asserted.
 *
 * \details
 * Field: ::VTSS_USB3_LLUCTL . EN_RESET_PIPE_AFTER_PHY_MUX
 */
#define  VTSS_F_USB3_LLUCTL_EN_RESET_PIPE_AFTER_PHY_MUX(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_USB3_LLUCTL_EN_RESET_PIPE_AFTER_PHY_MUX  VTSS_BIT(11)
#define  VTSS_X_USB3_LLUCTL_EN_RESET_PIPE_AFTER_PHY_MUX(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * P3CPM OK for U2/SSInactive (U2P3CPMok)
 *  - 0: During link state U2/SS.Inactive, put PHY in P2 (Default)
 *  - 1: During link state U2/SS.Inactive, put PHY in P3CPM.
 * Note: For a port, if both GUCTL1[25]=1 and LUCTL[12]=1, LUCTL[12]=1
 * takes priority.
 *
 * \details
 * Field: ::VTSS_USB3_LLUCTL . U2P3CPMOK
 */
#define  VTSS_F_USB3_LLUCTL_U2P3CPMOK(x)      VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_USB3_LLUCTL_U2P3CPMOK         VTSS_BIT(12)
#define  VTSS_X_USB3_LLUCTL_U2P3CPMOK(x)      VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_LLUCTL . RESERVED_13_22
 */
#define  VTSS_F_USB3_LLUCTL_RESERVED_13_22(x)  VTSS_ENCODE_BITFIELD(x,13,10)
#define  VTSS_M_USB3_LLUCTL_RESERVED_13_22     VTSS_ENCODE_BITMASK(13,10)
#define  VTSS_X_USB3_LLUCTL_RESERVED_13_22(x)  VTSS_EXTRACT_BITFIELD(x,13,10)

/**
 * \brief
 * DisRxDet_LTSSM_Timer_Ovrrd.
 *
 * When DisRxDetU3RxDet is asserted in Polling or U1, the timeout expires
 * immediately.
 *
 * \details
 * Field: ::VTSS_USB3_LLUCTL . DISRXDET_LTSSM_TIMER_OVRRD
 */
#define  VTSS_F_USB3_LLUCTL_DISRXDET_LTSSM_TIMER_OVRRD(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_USB3_LLUCTL_DISRXDET_LTSSM_TIMER_OVRRD  VTSS_BIT(23)
#define  VTSS_X_USB3_LLUCTL_DISRXDET_LTSSM_TIMER_OVRRD(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_LLUCTL . RESERVED_24_27
 */
#define  VTSS_F_USB3_LLUCTL_RESERVED_24_27(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_USB3_LLUCTL_RESERVED_24_27     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_USB3_LLUCTL_RESERVED_24_27(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * Support PHY P3.CPM and P4 Power States.
 *
 * When this bit is set, the controller puts  the PHY in P3.CPM or P4 in
 * certain states. This bit is used only for Synopsys PHY.
 *
 * \details
 * Field: ::VTSS_USB3_LLUCTL . SUPPORT_P4
 */
#define  VTSS_F_USB3_LLUCTL_SUPPORT_P4(x)     VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_USB3_LLUCTL_SUPPORT_P4        VTSS_BIT(28)
#define  VTSS_X_USB3_LLUCTL_SUPPORT_P4(x)     VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * PHY P4 Power gate mode (PG) is enabled.
 *
 * Set this bit if the PHY supports PG mode in P4. This bit is used only
 * for Synopsys PHY.
 *
 * \details
 * Field: ::VTSS_USB3_LLUCTL . SUPPORT_P4_PG
 */
#define  VTSS_F_USB3_LLUCTL_SUPPORT_P4_PG(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_USB3_LLUCTL_SUPPORT_P4_PG     VTSS_BIT(29)
#define  VTSS_X_USB3_LLUCTL_SUPPORT_P4_PG(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_LLUCTL . RESERVED_30_31
 */
#define  VTSS_F_USB3_LLUCTL_RESERVED_30_31(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_USB3_LLUCTL_RESERVED_30_31     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_USB3_LLUCTL_RESERVED_30_31(x)  VTSS_EXTRACT_BITFIELD(x,30,2)


/**
 * \brief Link Datapath Delay Register
 - Link Layer Timer Register for P3CPM/P4 Residency.
 - This register is common for all SS ports.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_LINK:LPTMDPDELAY
 */
#define VTSS_USB3_LPTMDPDELAY                VTSS_IOREG(VTSS_TO_USB3,0x340a)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_LPTMDPDELAY . RESERVED_0_9
 */
#define  VTSS_F_USB3_LPTMDPDELAY_RESERVED_0_9(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_USB3_LPTMDPDELAY_RESERVED_0_9     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_USB3_LPTMDPDELAY_RESERVED_0_9(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * \brief
 * p3cpmp4 residency timer value.
 *
 * Minimum number of suspend_clk periods that the controller needs to stay
 * in P3.CPM or P4 before exiting P3.CPM or P4. This field is used only for
 * Synopsys PHY.
 *
 * \details
 * Field: ::VTSS_USB3_LPTMDPDELAY . P3CPMP4_RESIDENCY
 */
#define  VTSS_F_USB3_LPTMDPDELAY_P3CPMP4_RESIDENCY(x)  VTSS_ENCODE_BITFIELD(x,10,12)
#define  VTSS_M_USB3_LPTMDPDELAY_P3CPMP4_RESIDENCY     VTSS_ENCODE_BITMASK(10,12)
#define  VTSS_X_USB3_LPTMDPDELAY_P3CPMP4_RESIDENCY(x)  VTSS_EXTRACT_BITFIELD(x,10,12)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_LPTMDPDELAY . RESERVED_22_31
 */
#define  VTSS_F_USB3_LPTMDPDELAY_RESERVED_22_31(x)  VTSS_ENCODE_BITFIELD(x,22,10)
#define  VTSS_M_USB3_LPTMDPDELAY_RESERVED_22_31     VTSS_ENCODE_BITMASK(22,10)
#define  VTSS_X_USB3_LPTMDPDELAY_RESERVED_22_31(x)  VTSS_EXTRACT_BITFIELD(x,22,10)

/**
 * Register Group: \a USB3:DWC_USB3_BLOCK_DEBUG
 *
 * USB 3.0 Debug Register Block
 */


/**
 * \brief U3 Root Hub Debug Register
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_DEBUG:U3RHBDBG
 */
#define VTSS_USB3_U3RHBDBG                   VTSS_IOREG(VTSS_TO_USB3,0x3600)

/**
 * \brief
 * Reserved_0_2
 *
 * \details
 * Field: ::VTSS_USB3_U3RHBDBG . RESERVED_0_2
 */
#define  VTSS_F_USB3_U3RHBDBG_RESERVED_0_2(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_USB3_U3RHBDBG_RESERVED_0_2     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_USB3_U3RHBDBG_RESERVED_0_2(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * tpcfg_tout_ctrl
 *
 *  This bit controls the USB 3.0 port configuration timeout duration.
 *  - 1: The port configuration timeout counter resets when the link is not
 * in U0.
 *  - 0: The port configuration timeout counter does not reset if the link
 * enters recovery or exits U0.
 *
 * \details
 * Field: ::VTSS_USB3_U3RHBDBG . TPCFG_TOUT_CTRL
 */
#define  VTSS_F_USB3_U3RHBDBG_TPCFG_TOUT_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_USB3_U3RHBDBG_TPCFG_TOUT_CTRL  VTSS_BIT(3)
#define  VTSS_X_USB3_U3RHBDBG_TPCFG_TOUT_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Reserved_1
 *
 * \details
 * Field: ::VTSS_USB3_U3RHBDBG . RESERVED_1
 */
#define  VTSS_F_USB3_U3RHBDBG_RESERVED_1(x)   VTSS_ENCODE_BITFIELD(x,4,28)
#define  VTSS_M_USB3_U3RHBDBG_RESERVED_1      VTSS_ENCODE_BITMASK(4,28)
#define  VTSS_X_USB3_U3RHBDBG_RESERVED_1(x)   VTSS_EXTRACT_BITFIELD(x,4,28)

/**
 * Register Group: \a USB3:DWC_USB3_BLOCK_EXTENSIBLE_HOST_CNTRL_CAP_REGS
 *
 * USB 3.0 eXtensible Host Controller Capability Register Block
 */


/**
 * \brief Capability Registers Length

Host Controller Operational Registers = Base address + CAPLENGTH

where CAPLENGTH is `DWC_USB3_HOST_CAP_REG_LEN whose default value is 20h.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_EXTENSIBLE_HOST_CNTRL_CAP_REGS:CAPLENGTH
 */
#define VTSS_USB3_CAPLENGTH                  VTSS_IOREG(VTSS_TO_USB3,0x0)

/**
 * \brief
 * Capability Registers Length (CAPLENGTH)
 *
 * \details
 * Field: ::VTSS_USB3_CAPLENGTH . CAPLENGTH
 */
#define  VTSS_F_USB3_CAPLENGTH_CAPLENGTH(x)   VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_USB3_CAPLENGTH_CAPLENGTH      VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_USB3_CAPLENGTH_CAPLENGTH(x)   VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_CAPLENGTH . CAPLENGTH_RESERVED_15_8
 */
#define  VTSS_F_USB3_CAPLENGTH_CAPLENGTH_RESERVED_15_8(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_USB3_CAPLENGTH_CAPLENGTH_RESERVED_15_8     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_USB3_CAPLENGTH_CAPLENGTH_RESERVED_15_8(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * HC Interface Version Number (HCIVERSION)
 *
 * \details
 * Field: ::VTSS_USB3_CAPLENGTH . HCIVERSION
 */
#define  VTSS_F_USB3_CAPLENGTH_HCIVERSION(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_CAPLENGTH_HCIVERSION     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_CAPLENGTH_HCIVERSION(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Structural Parameters 1 Register

For register definitions, refer to the xHCI specification.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_EXTENSIBLE_HOST_CNTRL_CAP_REGS:HCSPARAMS1
 */
#define VTSS_USB3_HCSPARAMS1                 VTSS_IOREG(VTSS_TO_USB3,0x1)

/**
 * \brief
 * Number of device slots (MaxSlots)
 *
 * Defined by configurable parameter `DWC_USB3_NUM_DEVICE_SUPT
 *
 * \details
 * Field: ::VTSS_USB3_HCSPARAMS1 . MAXSLOTS
 */
#define  VTSS_F_USB3_HCSPARAMS1_MAXSLOTS(x)   VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_USB3_HCSPARAMS1_MAXSLOTS      VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_USB3_HCSPARAMS1_MAXSLOTS(x)   VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Number of Interrupters (MaxIntrs)
 *
 * Defined by the configurable parameter
 * `DWC_USB3_HOST_NUM_INTERRUPTER_SUPT
 *
 * \details
 * Field: ::VTSS_USB3_HCSPARAMS1 . MAXINTRS
 */
#define  VTSS_F_USB3_HCSPARAMS1_MAXINTRS(x)   VTSS_ENCODE_BITFIELD(x,8,11)
#define  VTSS_M_USB3_HCSPARAMS1_MAXINTRS      VTSS_ENCODE_BITMASK(8,11)
#define  VTSS_X_USB3_HCSPARAMS1_MAXINTRS(x)   VTSS_EXTRACT_BITFIELD(x,8,11)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_HCSPARAMS1 . RESERVED_23_19
 */
#define  VTSS_F_USB3_HCSPARAMS1_RESERVED_23_19(x)  VTSS_ENCODE_BITFIELD(x,19,5)
#define  VTSS_M_USB3_HCSPARAMS1_RESERVED_23_19     VTSS_ENCODE_BITMASK(19,5)
#define  VTSS_X_USB3_HCSPARAMS1_RESERVED_23_19(x)  VTSS_EXTRACT_BITFIELD(x,19,5)

/**
 * \brief
 * Number of Ports (MaxPorts)
 *  - Number of ports implemented is defined by the parameter
 * (`DWC_USB3_HOST_NUM_U2_ROOT_PORTS + `DWC_USB3_HOST_NUM_U3_ROOT_PORTS)
 *  - Number of ports enabled is controlled by the controller input signals
 * host_num_u2_port[3:0]+host_num_u3_port[3:0]
 * Note:
 *
 * In USB 2.0-only mode, the host_num_u3_port signal is zero.
 *
 * \details
 * Field: ::VTSS_USB3_HCSPARAMS1 . MAXPORTS
 */
#define  VTSS_F_USB3_HCSPARAMS1_MAXPORTS(x)   VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_USB3_HCSPARAMS1_MAXPORTS      VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_USB3_HCSPARAMS1_MAXPORTS(x)   VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief Structural Parameters 2 Register

For register definitions, refer to the xHCI specification.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_EXTENSIBLE_HOST_CNTRL_CAP_REGS:HCSPARAMS2
 */
#define VTSS_USB3_HCSPARAMS2                 VTSS_IOREG(VTSS_TO_USB3,0x2)

/**
 * \brief
 * Isochronous Scheduling Threshold (IST)
 *
 * \details
 * Field: ::VTSS_USB3_HCSPARAMS2 . IST
 */
#define  VTSS_F_USB3_HCSPARAMS2_IST(x)        VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_USB3_HCSPARAMS2_IST           VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_USB3_HCSPARAMS2_IST(x)        VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Event Ring Segment Table Max (ERST Max)
 *
 * \details
 * Field: ::VTSS_USB3_HCSPARAMS2 . ERSTMAX
 */
#define  VTSS_F_USB3_HCSPARAMS2_ERSTMAX(x)    VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_USB3_HCSPARAMS2_ERSTMAX       VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_USB3_HCSPARAMS2_ERSTMAX(x)    VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_HCSPARAMS2 . RESERVED_20_8
 */
#define  VTSS_F_USB3_HCSPARAMS2_RESERVED_20_8(x)  VTSS_ENCODE_BITFIELD(x,8,13)
#define  VTSS_M_USB3_HCSPARAMS2_RESERVED_20_8     VTSS_ENCODE_BITMASK(8,13)
#define  VTSS_X_USB3_HCSPARAMS2_RESERVED_20_8(x)  VTSS_EXTRACT_BITFIELD(x,8,13)

/**
 * \brief
 * Max Scratchpad Bufs HI
 *
 * The controller automatically updates this field.
 *
 * \details
 * Field: ::VTSS_USB3_HCSPARAMS2 . MAXSCRATCHPADBUFS_HI
 */
#define  VTSS_F_USB3_HCSPARAMS2_MAXSCRATCHPADBUFS_HI(x)  VTSS_ENCODE_BITFIELD(x,21,5)
#define  VTSS_M_USB3_HCSPARAMS2_MAXSCRATCHPADBUFS_HI     VTSS_ENCODE_BITMASK(21,5)
#define  VTSS_X_USB3_HCSPARAMS2_MAXSCRATCHPADBUFS_HI(x)  VTSS_EXTRACT_BITFIELD(x,21,5)

/**
 * \brief
 * Scratchpad Restore (SPR)
 *
 * \details
 * Field: ::VTSS_USB3_HCSPARAMS2 . SPR
 */
#define  VTSS_F_USB3_HCSPARAMS2_SPR(x)        VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_USB3_HCSPARAMS2_SPR           VTSS_BIT(26)
#define  VTSS_X_USB3_HCSPARAMS2_SPR(x)        VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * Max Scratchpad Bufs Lo
 * The value is calculated based on chosen configuration parameter values.
 * Possible values are 1-4.
 *
 * \details
 * Field: ::VTSS_USB3_HCSPARAMS2 . MAXSCRATCHPADBUFS
 */
#define  VTSS_F_USB3_HCSPARAMS2_MAXSCRATCHPADBUFS(x)  VTSS_ENCODE_BITFIELD(x,27,5)
#define  VTSS_M_USB3_HCSPARAMS2_MAXSCRATCHPADBUFS     VTSS_ENCODE_BITMASK(27,5)
#define  VTSS_X_USB3_HCSPARAMS2_MAXSCRATCHPADBUFS(x)  VTSS_EXTRACT_BITFIELD(x,27,5)


/**
 * \brief Structural Parameters 3 Register

For register definitions, refer to the xHCI specification.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_EXTENSIBLE_HOST_CNTRL_CAP_REGS:HCSPARAMS3
 */
#define VTSS_USB3_HCSPARAMS3                 VTSS_IOREG(VTSS_TO_USB3,0x3)

/**
 * \brief
 * U1 Device Exit Latency
 *
 * \details
 * Field: ::VTSS_USB3_HCSPARAMS3 . U1_DEVICE_EXIT_LAT
 */
#define  VTSS_F_USB3_HCSPARAMS3_U1_DEVICE_EXIT_LAT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_USB3_HCSPARAMS3_U1_DEVICE_EXIT_LAT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_USB3_HCSPARAMS3_U1_DEVICE_EXIT_LAT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_HCSPARAMS3 . HCSPARAMS3_RESERVED_15_8
 */
#define  VTSS_F_USB3_HCSPARAMS3_HCSPARAMS3_RESERVED_15_8(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_USB3_HCSPARAMS3_HCSPARAMS3_RESERVED_15_8     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_USB3_HCSPARAMS3_HCSPARAMS3_RESERVED_15_8(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * U2 Device Exit Latency
 *
 * \details
 * Field: ::VTSS_USB3_HCSPARAMS3 . U2_DEVICE_EXIT_LAT
 */
#define  VTSS_F_USB3_HCSPARAMS3_U2_DEVICE_EXIT_LAT(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_HCSPARAMS3_U2_DEVICE_EXIT_LAT     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_HCSPARAMS3_U2_DEVICE_EXIT_LAT(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Capability Parameters 1 Register

For register definitions, refer to the xHCI specification.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_EXTENSIBLE_HOST_CNTRL_CAP_REGS:HCCPARAMS1
 */
#define VTSS_USB3_HCCPARAMS1                 VTSS_IOREG(VTSS_TO_USB3,0x4)

/**
 * \brief
 * 64-bit Addressing Capability (AC64)
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS1 . AC64
 */
#define  VTSS_F_USB3_HCCPARAMS1_AC64(x)       VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_USB3_HCCPARAMS1_AC64          VTSS_BIT(0)
#define  VTSS_X_USB3_HCCPARAMS1_AC64(x)       VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * BW Negotiation Capability (BNC)
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS1 . BNC
 */
#define  VTSS_F_USB3_HCCPARAMS1_BNC(x)        VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_USB3_HCCPARAMS1_BNC           VTSS_BIT(1)
#define  VTSS_X_USB3_HCCPARAMS1_BNC(x)        VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Context Size (CSZ)
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS1 . CSZ
 */
#define  VTSS_F_USB3_HCCPARAMS1_CSZ(x)        VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_USB3_HCCPARAMS1_CSZ           VTSS_BIT(2)
#define  VTSS_X_USB3_HCCPARAMS1_CSZ(x)        VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Port Power Control
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS1 . PPC
 */
#define  VTSS_F_USB3_HCCPARAMS1_PPC(x)        VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_USB3_HCCPARAMS1_PPC           VTSS_BIT(3)
#define  VTSS_X_USB3_HCCPARAMS1_PPC(x)        VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Port Indicators (PIND)
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS1 . PIND
 */
#define  VTSS_F_USB3_HCCPARAMS1_PIND(x)       VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_USB3_HCCPARAMS1_PIND          VTSS_BIT(4)
#define  VTSS_X_USB3_HCCPARAMS1_PIND(x)       VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Light HC Reset Capability
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS1 . LHRC
 */
#define  VTSS_F_USB3_HCCPARAMS1_LHRC(x)       VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_USB3_HCCPARAMS1_LHRC          VTSS_BIT(5)
#define  VTSS_X_USB3_HCCPARAMS1_LHRC(x)       VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Latency Tolerance Messaging Capability (LTC)
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS1 . LTC
 */
#define  VTSS_F_USB3_HCCPARAMS1_LTC(x)        VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_USB3_HCCPARAMS1_LTC           VTSS_BIT(6)
#define  VTSS_X_USB3_HCCPARAMS1_LTC(x)        VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * No Secondary SID Support (NSS)
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS1 . NSS
 */
#define  VTSS_F_USB3_HCCPARAMS1_NSS(x)        VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_USB3_HCCPARAMS1_NSS           VTSS_BIT(7)
#define  VTSS_X_USB3_HCCPARAMS1_NSS(x)        VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Parse All Event Data (PAE)
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS1 . PAE
 */
#define  VTSS_F_USB3_HCCPARAMS1_PAE(x)        VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_USB3_HCCPARAMS1_PAE           VTSS_BIT(8)
#define  VTSS_X_USB3_HCCPARAMS1_PAE(x)        VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Short Packet Capability (SPC)
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS1 . SPC
 */
#define  VTSS_F_USB3_HCCPARAMS1_SPC(x)        VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_USB3_HCCPARAMS1_SPC           VTSS_BIT(9)
#define  VTSS_X_USB3_HCCPARAMS1_SPC(x)        VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Stopped EDLTA Capability (SEC)
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS1 . SEC
 */
#define  VTSS_F_USB3_HCCPARAMS1_SEC(x)        VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_USB3_HCCPARAMS1_SEC           VTSS_BIT(10)
#define  VTSS_X_USB3_HCCPARAMS1_SEC(x)        VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Contiguous Frame ID Capability (CFC)
 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS1 . CFC
 */
#define  VTSS_F_USB3_HCCPARAMS1_CFC(x)        VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_USB3_HCCPARAMS1_CFC           VTSS_BIT(11)
#define  VTSS_X_USB3_HCCPARAMS1_CFC(x)        VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Maximum Primary Stream Array Size (MaxPSASize)
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS1 . MAXPSASIZE
 */
#define  VTSS_F_USB3_HCCPARAMS1_MAXPSASIZE(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_USB3_HCCPARAMS1_MAXPSASIZE     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_USB3_HCCPARAMS1_MAXPSASIZE(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * xHCI Extended Capabilities Pointer (xECP)
 *
 * Based on configuration, controller automatically updates it.
 *
 * Refer to <workspace>/src/DWC_usb3_params.v for details on
 * DWC_USB3_HC_XECP.

 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS1 . XECP
 */
#define  VTSS_F_USB3_HCCPARAMS1_XECP(x)       VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_HCCPARAMS1_XECP          VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_HCCPARAMS1_XECP(x)       VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Doorbell Offset Register

For register definitions, refer to the xHCI specification.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_EXTENSIBLE_HOST_CNTRL_CAP_REGS:DBOFF
 */
#define VTSS_USB3_DBOFF                      VTSS_IOREG(VTSS_TO_USB3,0x5)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_DBOFF . RESERVED_1_0
 */
#define  VTSS_F_USB3_DBOFF_RESERVED_1_0(x)    VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_USB3_DBOFF_RESERVED_1_0       VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_USB3_DBOFF_RESERVED_1_0(x)    VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * Doorbell Array Offset - RO
 *
 * Based on configuration, the controller automatically updates it.
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_DBOFF . DOORBELL_ARRAY_OFFSET
 */
#define  VTSS_F_USB3_DBOFF_DOORBELL_ARRAY_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_USB3_DBOFF_DOORBELL_ARRAY_OFFSET     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_USB3_DBOFF_DOORBELL_ARRAY_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,2,30)


/**
 * \brief Runtime Register Space Offset Register
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_EXTENSIBLE_HOST_CNTRL_CAP_REGS:RTSOFF
 */
#define VTSS_USB3_RTSOFF                     VTSS_IOREG(VTSS_TO_USB3,0x6)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_RTSOFF . RESERVED_4_0
 */
#define  VTSS_F_USB3_RTSOFF_RESERVED_4_0(x)   VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_USB3_RTSOFF_RESERVED_4_0      VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_USB3_RTSOFF_RESERVED_4_0(x)   VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * Runtime Register Space Offset
 *
 * Based on configuration, the controller automatically updates it.
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_RTSOFF . RUNTIME_REG_SPACE_OFFSET
 */
#define  VTSS_F_USB3_RTSOFF_RUNTIME_REG_SPACE_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,5,27)
#define  VTSS_M_USB3_RTSOFF_RUNTIME_REG_SPACE_OFFSET     VTSS_ENCODE_BITMASK(5,27)
#define  VTSS_X_USB3_RTSOFF_RUNTIME_REG_SPACE_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,5,27)


/**
 * \brief Host Controller Capability Parameters 2

For register definitions, refer to the xHCI specification.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_EXTENSIBLE_HOST_CNTRL_CAP_REGS:HCCPARAMS2
 */
#define VTSS_USB3_HCCPARAMS2                 VTSS_IOREG(VTSS_TO_USB3,0x7)

/**
 * \brief
 * U3 Entry Capability (U3C)
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller I
 * nterface for Universal Serial Bus (USB) Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS2 . U3C
 */
#define  VTSS_F_USB3_HCCPARAMS2_U3C(x)        VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_USB3_HCCPARAMS2_U3C           VTSS_BIT(0)
#define  VTSS_X_USB3_HCCPARAMS2_U3C(x)        VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Configure Endpoint Command Max Exit Latency Too Large Capability (CMC)
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller I
 * nterface for Universal Serial Bus (USB) Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS2 . CMC
 */
#define  VTSS_F_USB3_HCCPARAMS2_CMC(x)        VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_USB3_HCCPARAMS2_CMC           VTSS_BIT(1)
#define  VTSS_X_USB3_HCCPARAMS2_CMC(x)        VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Force Save Context Capability (FSC)
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller I
 * nterface for Universal Serial Bus (USB) Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS2 . FSC
 */
#define  VTSS_F_USB3_HCCPARAMS2_FSC(x)        VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_USB3_HCCPARAMS2_FSC           VTSS_BIT(2)
#define  VTSS_X_USB3_HCCPARAMS2_FSC(x)        VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Compliance Transition Capability (CTC)
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller I
 * nterface for Universal Serial Bus (USB) Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS2 . CTC
 */
#define  VTSS_F_USB3_HCCPARAMS2_CTC(x)        VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_USB3_HCCPARAMS2_CTC           VTSS_BIT(3)
#define  VTSS_X_USB3_HCCPARAMS2_CTC(x)        VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Large ESIT Payload Capability (LEC)
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller I
 * nterface for Universal Serial Bus (USB) Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS2 . LEC
 */
#define  VTSS_F_USB3_HCCPARAMS2_LEC(x)        VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_USB3_HCCPARAMS2_LEC           VTSS_BIT(4)
#define  VTSS_X_USB3_HCCPARAMS2_LEC(x)        VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Configuration Information Capability (CIC)
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller I
 * nterface for Universal Serial Bus (USB) Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS2 . CIC
 */
#define  VTSS_F_USB3_HCCPARAMS2_CIC(x)        VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_USB3_HCCPARAMS2_CIC           VTSS_BIT(5)
#define  VTSS_X_USB3_HCCPARAMS2_CIC(x)        VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_HCCPARAMS2 . RESERVED_31_6
 */
#define  VTSS_F_USB3_HCCPARAMS2_RESERVED_31_6(x)  VTSS_ENCODE_BITFIELD(x,6,26)
#define  VTSS_M_USB3_HCCPARAMS2_RESERVED_31_6     VTSS_ENCODE_BITMASK(6,26)
#define  VTSS_X_USB3_HCCPARAMS2_RESERVED_31_6(x)  VTSS_EXTRACT_BITFIELD(x,6,26)

/**
 * Register Group: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_OPER_REGS
 *
 * USB3 Host Cntrl Oper Regs Block
 */


/**
 * \brief USB Command Register

For a description of this standard USB register field see the eXtensible Host Controller Interface for Universal Serial Bus (USB) Specification 3.0.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_OPER_REGS:USBCMD
 */
#define VTSS_USB3_USBCMD                     VTSS_IOREG(VTSS_TO_USB3,0x8)

/**
 * \brief
 * R_S
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * Due to side-effects this reguster field is not recommended for Bit-Bash
 * testing.
 *
 * \details
 * Field: ::VTSS_USB3_USBCMD . R_S
 */
#define  VTSS_F_USB3_USBCMD_R_S(x)            VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_USB3_USBCMD_R_S               VTSS_BIT(0)
#define  VTSS_X_USB3_USBCMD_R_S(x)            VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * HCRST
 *
 * The following bits reset the internal logic of the host controller.
 * Under soft reset, some CSR accesses may fail (Timeout).
 *  - HCRST
 *  - LHCRST
 *
 * Bit Bash register testing is not recommended.

 *
 * \details
 * Field: ::VTSS_USB3_USBCMD . HCRST
 */
#define  VTSS_F_USB3_USBCMD_HCRST(x)          VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_USB3_USBCMD_HCRST             VTSS_BIT(1)
#define  VTSS_X_USB3_USBCMD_HCRST(x)          VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * INTE
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_USBCMD . INTE
 */
#define  VTSS_F_USB3_USBCMD_INTE(x)           VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_USB3_USBCMD_INTE              VTSS_BIT(2)
#define  VTSS_X_USB3_USBCMD_INTE(x)           VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * HSEE
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_USBCMD . HSEE
 */
#define  VTSS_F_USB3_USBCMD_HSEE(x)           VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_USB3_USBCMD_HSEE              VTSS_BIT(3)
#define  VTSS_X_USB3_USBCMD_HSEE(x)           VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_USBCMD . RESERVED_6_4
 */
#define  VTSS_F_USB3_USBCMD_RESERVED_6_4(x)   VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_USB3_USBCMD_RESERVED_6_4      VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_USB3_USBCMD_RESERVED_6_4(x)   VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \brief
 * Light Host Controller Reset
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * The following bits reset the internal logic of the host controller.
 * Under soft reset, some CSR accesses may fail (Timeout).
 *  - HCRST
 *  - LHCRST
 *
 * Bit Bash register testing is not recommended.

 *
 * \details
 * Field: ::VTSS_USB3_USBCMD . LHCRST
 */
#define  VTSS_F_USB3_USBCMD_LHCRST(x)         VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_USB3_USBCMD_LHCRST            VTSS_BIT(7)
#define  VTSS_X_USB3_USBCMD_LHCRST(x)         VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Controller Save State
 *
 * This command is similar to the USBCMD.CSS bit in host mode and initiates
 * the save process. When software sets this bit to '1', the controller
 * immediately sets DSTS.SSS to '1'.
 * When the controller has finished the save process, it sets DSTS.SSS to
 * '0'.
 *
 * Note: When read, this field always returns '0'.

 *
 * \details
 * Field: ::VTSS_USB3_USBCMD . CSS
 */
#define  VTSS_F_USB3_USBCMD_CSS(x)            VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_USB3_USBCMD_CSS               VTSS_BIT(8)
#define  VTSS_X_USB3_USBCMD_CSS(x)            VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Controller Restore State
 *
 * This command is similar to the USBCMD.CRS bit in host mode and initiates
 * the restore process. When software sets this bit to '1', the controller
 * immediately sets DSTS.RSS to '1'. When the controller has finished the
 * restore process, it sets DSTS.RSS to '0'.
 *
 * Note: When read, this field always returns '0'.

 *
 * \details
 * Field: ::VTSS_USB3_USBCMD . CRS
 */
#define  VTSS_F_USB3_USBCMD_CRS(x)            VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_USB3_USBCMD_CRS               VTSS_BIT(9)
#define  VTSS_X_USB3_USBCMD_CRS(x)            VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * EWE
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_USBCMD . EWE
 */
#define  VTSS_F_USB3_USBCMD_EWE(x)            VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_USB3_USBCMD_EWE               VTSS_BIT(10)
#define  VTSS_X_USB3_USBCMD_EWE(x)            VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * EU3S
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_USBCMD . EU3S
 */
#define  VTSS_F_USB3_USBCMD_EU3S(x)           VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_USB3_USBCMD_EU3S              VTSS_BIT(11)
#define  VTSS_X_USB3_USBCMD_EU3S(x)           VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_USBCMD . RESERVED_12
 */
#define  VTSS_F_USB3_USBCMD_RESERVED_12(x)    VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_USB3_USBCMD_RESERVED_12       VTSS_BIT(12)
#define  VTSS_X_USB3_USBCMD_RESERVED_12(x)    VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * CEM Enable
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_USBCMD . CME
 */
#define  VTSS_F_USB3_USBCMD_CME(x)            VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_USB3_USBCMD_CME               VTSS_BIT(13)
#define  VTSS_X_USB3_USBCMD_CME(x)            VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_USBCMD . RESERVED_31_14
 */
#define  VTSS_F_USB3_USBCMD_RESERVED_31_14(x)  VTSS_ENCODE_BITFIELD(x,14,18)
#define  VTSS_M_USB3_USBCMD_RESERVED_31_14     VTSS_ENCODE_BITMASK(14,18)
#define  VTSS_X_USB3_USBCMD_RESERVED_31_14(x)  VTSS_EXTRACT_BITFIELD(x,14,18)


/**
 * \brief USB Status Register Bit Definitions

For a description of this standard USB register field, see the eXtensible Host Controller Interface for Universal Serial Bus (USB) Specification 3.0.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_OPER_REGS:USBSTS
 */
#define VTSS_USB3_USBSTS                     VTSS_IOREG(VTSS_TO_USB3,0x9)

/**
 * \brief
 * HCH
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_USBSTS . HCH
 */
#define  VTSS_F_USB3_USBSTS_HCH(x)            VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_USB3_USBSTS_HCH               VTSS_BIT(0)
#define  VTSS_X_USB3_USBSTS_HCH(x)            VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_USBSTS . RESERVED_1
 */
#define  VTSS_F_USB3_USBSTS_RESERVED_1(x)     VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_USB3_USBSTS_RESERVED_1        VTSS_BIT(1)
#define  VTSS_X_USB3_USBSTS_RESERVED_1(x)     VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * HSE
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0..
 *
 * \details
 * Field: ::VTSS_USB3_USBSTS . HSE
 */
#define  VTSS_F_USB3_USBSTS_HSE(x)            VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_USB3_USBSTS_HSE               VTSS_BIT(2)
#define  VTSS_X_USB3_USBSTS_HSE(x)            VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Reset Value for EINT
 *
 * \details
 * Field: ::VTSS_USB3_USBSTS . EINT
 */
#define  VTSS_F_USB3_USBSTS_EINT(x)           VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_USB3_USBSTS_EINT              VTSS_BIT(3)
#define  VTSS_X_USB3_USBSTS_EINT(x)           VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Reset Value for PCD
 *
 * \details
 * Field: ::VTSS_USB3_USBSTS . PCD
 */
#define  VTSS_F_USB3_USBSTS_PCD(x)            VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_USB3_USBSTS_PCD               VTSS_BIT(4)
#define  VTSS_X_USB3_USBSTS_PCD(x)            VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_USBSTS . RESERVED_7_5
 */
#define  VTSS_F_USB3_USBSTS_RESERVED_7_5(x)   VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_USB3_USBSTS_RESERVED_7_5      VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_USB3_USBSTS_RESERVED_7_5(x)   VTSS_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * Save State Status
 *
 * This bit is similar to the USBSTS.SSS in host mode.
 *
 * When the controller has finished the save process, it completes the
 * command by setting DSTS.SSS to '0'.

 *
 * \details
 * Field: ::VTSS_USB3_USBSTS . SSS
 */
#define  VTSS_F_USB3_USBSTS_SSS(x)            VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_USB3_USBSTS_SSS               VTSS_BIT(8)
#define  VTSS_X_USB3_USBSTS_SSS(x)            VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Restore State Status
 *
 * This bit is similar to the USBSTS.RSS in host mode.
 *
 * When the controller has finished the restore process, it completes the
 * command by setting DSTS.RSS to '0'.

 *
 * \details
 * Field: ::VTSS_USB3_USBSTS . RSS
 */
#define  VTSS_F_USB3_USBSTS_RSS(x)            VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_USB3_USBSTS_RSS               VTSS_BIT(9)
#define  VTSS_X_USB3_USBSTS_RSS(x)            VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Save/Restore Error
 *
 * This bit is currently not supported.

 *
 * \details
 * Field: ::VTSS_USB3_USBSTS . SRE
 */
#define  VTSS_F_USB3_USBSTS_SRE(x)            VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_USB3_USBSTS_SRE               VTSS_BIT(10)
#define  VTSS_X_USB3_USBSTS_SRE(x)            VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Controller Not Ready (CNR) - RO
 *
 * Default = '1'.
 *
 * '0' = Ready and
 *
 * '1' = Not Ready.
 *
 * Software must not write to thes Doorbell or Operational register of the
 * xHC, other than the USBSTS register, until CNR = '0'. This flag is set
 * by the xHC after a Chip Hardware Reset and cleared when the xHC is ready
 * to begin accepting register writes. This flag remains cleared ('0')
 * until the next Chip Hardware Reset.

 *
 * \details
 * Field: ::VTSS_USB3_USBSTS . CNR
 */
#define  VTSS_F_USB3_USBSTS_CNR(x)            VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_USB3_USBSTS_CNR               VTSS_BIT(11)
#define  VTSS_X_USB3_USBSTS_CNR(x)            VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Host Controller Error (HCE) - RO
 *
 * Default = 0.
 *
 * '0' = No internal xHC error conditions exist and '1' = Internal xHC
 * error condition. This flag must be set to indicate that an internal
 * error condition has been detected which requires software to reset and
 * reinitialize the xHC. Refer to section 4.24.1 of the Databook for more
 * information.
 *
 * \details
 * Field: ::VTSS_USB3_USBSTS . HCE
 */
#define  VTSS_F_USB3_USBSTS_HCE(x)            VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_USB3_USBSTS_HCE               VTSS_BIT(12)
#define  VTSS_X_USB3_USBSTS_HCE(x)            VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_USBSTS . RESERVED_31_13
 */
#define  VTSS_F_USB3_USBSTS_RESERVED_31_13(x)  VTSS_ENCODE_BITFIELD(x,13,19)
#define  VTSS_M_USB3_USBSTS_RESERVED_31_13     VTSS_ENCODE_BITMASK(13,19)
#define  VTSS_X_USB3_USBSTS_RESERVED_31_13(x)  VTSS_EXTRACT_BITFIELD(x,13,19)


/**
 * \brief Page Size Register Bit Definitions

Use this register to enable or disable the reporting of specific USB Device Notification Transaction Packets being received.

A Notification Enable (Nx, where x = 0 to 15) flag is defined for each of the 16 possible device notification types. If a flag is set for a specific notification type, a Device Notification Event is generated when the respective notification packet is received. After reset, all notifications are disabled. Refer to section 6.4.2.7 of the Databook for more information.

This register is written as a Dword. Byte writes produce undefined results.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_OPER_REGS:PAGESIZE
 */
#define VTSS_USB3_PAGESIZE                   VTSS_IOREG(VTSS_TO_USB3,0xa)

/**
 * \brief
 * PAGE_SIZE
 *
 * \details
 * Field: ::VTSS_USB3_PAGESIZE . PAGE_SIZE
 */
#define  VTSS_F_USB3_PAGESIZE_PAGE_SIZE(x)    VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_USB3_PAGESIZE_PAGE_SIZE       VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_USB3_PAGESIZE_PAGE_SIZE(x)    VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_PAGESIZE . PAGESIZE_RESERVED_31_16
 */
#define  VTSS_F_USB3_PAGESIZE_PAGESIZE_RESERVED_31_16(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_PAGESIZE_PAGESIZE_RESERVED_31_16     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_PAGESIZE_PAGESIZE_RESERVED_31_16(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Device Notification Register Bit Definitions

For a description of this standard USB register field see the eXtensible Host Controller Interface for Universal Serial Bus (USB) Specification 3.0.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_OPER_REGS:DNCTRL
 */
#define VTSS_USB3_DNCTRL                     VTSS_IOREG(VTSS_TO_USB3,0xd)

/**
 * \brief
 * N0_N15
 *
 * For a description of this standard USB register field see the eXtensible
 * Host Controller Interface for Universal Serial Bus (USB) Specification
 * 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_DNCTRL . N0_N15
 */
#define  VTSS_F_USB3_DNCTRL_N0_N15(x)         VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_USB3_DNCTRL_N0_N15            VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_USB3_DNCTRL_N0_N15(x)         VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_DNCTRL . DNCTRL_RESERVED_31_16
 */
#define  VTSS_F_USB3_DNCTRL_DNCTRL_RESERVED_31_16(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_DNCTRL_DNCTRL_RESERVED_31_16     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_DNCTRL_DNCTRL_RESERVED_31_16(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief CRCR_LO

For a description of this standard USB register field, see the eXtensible Host Controller Interface for Universal Serial Bus (USB) Specification 3.0.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_OPER_REGS:CRCR_LO
 */
#define VTSS_USB3_CRCR_LO                    VTSS_IOREG(VTSS_TO_USB3,0xe)

/**
 * \brief
 * RCS
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_CRCR_LO . RCS
 */
#define  VTSS_F_USB3_CRCR_LO_RCS(x)           VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_USB3_CRCR_LO_RCS              VTSS_BIT(0)
#define  VTSS_X_USB3_CRCR_LO_RCS(x)           VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * CS
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_CRCR_LO . CS
 */
#define  VTSS_F_USB3_CRCR_LO_CS(x)            VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_USB3_CRCR_LO_CS               VTSS_BIT(1)
#define  VTSS_X_USB3_CRCR_LO_CS(x)            VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * CA
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_CRCR_LO . CA
 */
#define  VTSS_F_USB3_CRCR_LO_CA(x)            VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_USB3_CRCR_LO_CA               VTSS_BIT(2)
#define  VTSS_X_USB3_CRCR_LO_CA(x)            VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * CRR
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_CRCR_LO . CRR
 */
#define  VTSS_F_USB3_CRCR_LO_CRR(x)           VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_USB3_CRCR_LO_CRR              VTSS_BIT(3)
#define  VTSS_X_USB3_CRCR_LO_CRR(x)           VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_CRCR_LO . RESERVED_5_4
 */
#define  VTSS_F_USB3_CRCR_LO_RESERVED_5_4(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_USB3_CRCR_LO_RESERVED_5_4     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_USB3_CRCR_LO_RESERVED_5_4(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * CMD_RING_PNTR
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_CRCR_LO . CRCR_LO_CMD_RING_PNTR
 */
#define  VTSS_F_USB3_CRCR_LO_CRCR_LO_CMD_RING_PNTR(x)  VTSS_ENCODE_BITFIELD(x,6,26)
#define  VTSS_M_USB3_CRCR_LO_CRCR_LO_CMD_RING_PNTR     VTSS_ENCODE_BITMASK(6,26)
#define  VTSS_X_USB3_CRCR_LO_CRCR_LO_CMD_RING_PNTR(x)  VTSS_EXTRACT_BITFIELD(x,6,26)


/**
 * \brief CRCR_HI
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_OPER_REGS:CRCR_HI
 */
#define VTSS_USB3_CRCR_HI                    VTSS_IOREG(VTSS_TO_USB3,0xf)

/**
 * \brief
 * COMMAND_RING_POINTER
 *
 *  Reading this field always returns '0'.
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_CRCR_HI . CRCR_HI_CMD_RING_PNTR
 */
#define  VTSS_F_USB3_CRCR_HI_CRCR_HI_CMD_RING_PNTR(x)  (x)
#define  VTSS_M_USB3_CRCR_HI_CRCR_HI_CMD_RING_PNTR     0xffffffff
#define  VTSS_X_USB3_CRCR_HI_CRCR_HI_CMD_RING_PNTR(x)  (x)


/**
 * \brief DCBAAP_LO
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_OPER_REGS:DCBAAP_LO
 */
#define VTSS_USB3_DCBAAP_LO                  VTSS_IOREG(VTSS_TO_USB3,0x14)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_DCBAAP_LO . RESERVED_5_0
 */
#define  VTSS_F_USB3_DCBAAP_LO_RESERVED_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_USB3_DCBAAP_LO_RESERVED_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_USB3_DCBAAP_LO_RESERVED_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * DEVICE_CONTEXT_BAAP
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_DCBAAP_LO . DCBAAP_LO_DEVICE_CONTEXT_BAAP
 */
#define  VTSS_F_USB3_DCBAAP_LO_DCBAAP_LO_DEVICE_CONTEXT_BAAP(x)  VTSS_ENCODE_BITFIELD(x,6,26)
#define  VTSS_M_USB3_DCBAAP_LO_DCBAAP_LO_DEVICE_CONTEXT_BAAP     VTSS_ENCODE_BITMASK(6,26)
#define  VTSS_X_USB3_DCBAAP_LO_DCBAAP_LO_DEVICE_CONTEXT_BAAP(x)  VTSS_EXTRACT_BITFIELD(x,6,26)


/**
 * \brief DCBAAP_HI

For a description of this standard USB register field, see the eXtensible Host Controller Interface for Universal Serial Bus (USB) Specification 3.0.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_OPER_REGS:DCBAAP_HI
 */
#define VTSS_USB3_DCBAAP_HI                  VTSS_IOREG(VTSS_TO_USB3,0x15)

/**
 * \brief
 * DEVICE_CONTEXT_BAAP
 *
 * \details
 * Field: ::VTSS_USB3_DCBAAP_HI . DCBAAP_HI_DEVICE_CONTEXT_BAAP
 */
#define  VTSS_F_USB3_DCBAAP_HI_DCBAAP_HI_DEVICE_CONTEXT_BAAP(x)  (x)
#define  VTSS_M_USB3_DCBAAP_HI_DCBAAP_HI_DEVICE_CONTEXT_BAAP     0xffffffff
#define  VTSS_X_USB3_DCBAAP_HI_DCBAAP_HI_DEVICE_CONTEXT_BAAP(x)  (x)


/**
 * \brief Configure Register Bit Definitions

 This register is in the Aux Power well. It is only reset by platform hardware during a cold reset or in response to a Host Controller Reset (HCRST). The initial conditions of a port are described in section 4.19 of the Databook.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_OPER_REGS:CONFIG
 */
#define VTSS_USB3_CONFIG                     VTSS_IOREG(VTSS_TO_USB3,0x16)

/**
 * \brief
 * MAXSLOTSEN
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_CONFIG . MAXSLOTSEN
 */
#define  VTSS_F_USB3_CONFIG_MAXSLOTSEN(x)     VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_USB3_CONFIG_MAXSLOTSEN        VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_USB3_CONFIG_MAXSLOTSEN(x)     VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * U3 Entry Enable
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_CONFIG . U3E
 */
#define  VTSS_F_USB3_CONFIG_U3E(x)            VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_USB3_CONFIG_U3E               VTSS_BIT(8)
#define  VTSS_X_USB3_CONFIG_U3E(x)            VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Configuration Information Enable
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_CONFIG . CIE
 */
#define  VTSS_F_USB3_CONFIG_CIE(x)            VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_USB3_CONFIG_CIE               VTSS_BIT(9)
#define  VTSS_X_USB3_CONFIG_CIE(x)            VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_CONFIG . RESERVED_31_10
 */
#define  VTSS_F_USB3_CONFIG_RESERVED_31_10(x)  VTSS_ENCODE_BITFIELD(x,10,22)
#define  VTSS_M_USB3_CONFIG_RESERVED_31_10     VTSS_ENCODE_BITMASK(10,22)
#define  VTSS_X_USB3_CONFIG_RESERVED_31_10(x)  VTSS_EXTRACT_BITFIELD(x,10,22)

/**
 * Register Group: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_PORT_REG_SET
 *
 * USB3 Host Cntrl Port Reg Set Block
 */


/**
 * \brief Port Status and Control Register Bit Definitions

The PORTSC Register Access fails (Timeout) if the UTMI/ULPI clock is not running or one of the following bits is asserted.
 - PR
 - ORC
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_PORT_REG_SET:PORTSC_20
 */
#define VTSS_USB3_PORTSC_20                  VTSS_IOREG(VTSS_TO_USB3,0x108)

/**
 * \brief
 * CCS
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . CCS
 */
#define  VTSS_F_USB3_PORTSC_20_CCS(x)         VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_USB3_PORTSC_20_CCS            VTSS_BIT(0)
#define  VTSS_X_USB3_PORTSC_20_CCS(x)         VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * PED
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . PED
 */
#define  VTSS_F_USB3_PORTSC_20_PED(x)         VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_USB3_PORTSC_20_PED            VTSS_BIT(1)
#define  VTSS_X_USB3_PORTSC_20_PED(x)         VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . RESERVED_2
 */
#define  VTSS_F_USB3_PORTSC_20_RESERVED_2(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_USB3_PORTSC_20_RESERVED_2     VTSS_BIT(2)
#define  VTSS_X_USB3_PORTSC_20_RESERVED_2(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * OCA
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . OCA
 */
#define  VTSS_F_USB3_PORTSC_20_OCA(x)         VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_USB3_PORTSC_20_OCA            VTSS_BIT(3)
#define  VTSS_X_USB3_PORTSC_20_OCA(x)         VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * PR
 * set_register_field_attribute
 * DWC_usb3_map/DWC_usb3_block_Host_Cntrl_Port_Reg_Set/PORTSC_20_REGS/PORTS
 * C_20/PR VolatileMemory 1
 *
 *  Programming this field with random data will cause side effect. Bit
 * Bash register testing is not recommended.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . PR
 */
#define  VTSS_F_USB3_PORTSC_20_PR(x)          VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_USB3_PORTSC_20_PR             VTSS_BIT(4)
#define  VTSS_X_USB3_PORTSC_20_PR(x)          VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * PLS
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . PLS
 */
#define  VTSS_F_USB3_PORTSC_20_PLS(x)         VTSS_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_USB3_PORTSC_20_PLS            VTSS_ENCODE_BITMASK(5,4)
#define  VTSS_X_USB3_PORTSC_20_PLS(x)         VTSS_EXTRACT_BITFIELD(x,5,4)

/**
 * \brief
 * PP
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . PP
 */
#define  VTSS_F_USB3_PORTSC_20_PP(x)          VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_USB3_PORTSC_20_PP             VTSS_BIT(9)
#define  VTSS_X_USB3_PORTSC_20_PP(x)          VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * PORTSPEED
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . PORTSPEED
 */
#define  VTSS_F_USB3_PORTSC_20_PORTSPEED(x)   VTSS_ENCODE_BITFIELD(x,10,4)
#define  VTSS_M_USB3_PORTSC_20_PORTSPEED      VTSS_ENCODE_BITMASK(10,4)
#define  VTSS_X_USB3_PORTSC_20_PORTSPEED(x)   VTSS_EXTRACT_BITFIELD(x,10,4)

/**
 * \brief
 * PIC
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . PIC
 */
#define  VTSS_F_USB3_PORTSC_20_PIC(x)         VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_USB3_PORTSC_20_PIC            VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_USB3_PORTSC_20_PIC(x)         VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * LWS
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . LWS
 */
#define  VTSS_F_USB3_PORTSC_20_LWS(x)         VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_USB3_PORTSC_20_LWS            VTSS_BIT(16)
#define  VTSS_X_USB3_PORTSC_20_LWS(x)         VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * CSC
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . CSC
 */
#define  VTSS_F_USB3_PORTSC_20_CSC(x)         VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_USB3_PORTSC_20_CSC            VTSS_BIT(17)
#define  VTSS_X_USB3_PORTSC_20_CSC(x)         VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * PEC
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . PEC
 */
#define  VTSS_F_USB3_PORTSC_20_PEC(x)         VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_USB3_PORTSC_20_PEC            VTSS_BIT(18)
#define  VTSS_X_USB3_PORTSC_20_PEC(x)         VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * WRC
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . RESERVED_19
 */
#define  VTSS_F_USB3_PORTSC_20_RESERVED_19(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_USB3_PORTSC_20_RESERVED_19    VTSS_BIT(19)
#define  VTSS_X_USB3_PORTSC_20_RESERVED_19(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * OCC
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . OCC
 */
#define  VTSS_F_USB3_PORTSC_20_OCC(x)         VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_USB3_PORTSC_20_OCC            VTSS_BIT(20)
#define  VTSS_X_USB3_PORTSC_20_OCC(x)         VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * PRC
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * Programming this field with random data will cause side effect. Bit Bash
 * register testing is not recommended.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . PRC
 */
#define  VTSS_F_USB3_PORTSC_20_PRC(x)         VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_USB3_PORTSC_20_PRC            VTSS_BIT(21)
#define  VTSS_X_USB3_PORTSC_20_PRC(x)         VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * PLC
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . PLC
 */
#define  VTSS_F_USB3_PORTSC_20_PLC(x)         VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_USB3_PORTSC_20_PLC            VTSS_BIT(22)
#define  VTSS_X_USB3_PORTSC_20_PLC(x)         VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Reserved
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . RESERVED_23
 */
#define  VTSS_F_USB3_PORTSC_20_RESERVED_23(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_USB3_PORTSC_20_RESERVED_23    VTSS_BIT(23)
#define  VTSS_X_USB3_PORTSC_20_RESERVED_23(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Cold Attach Status
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . CAS
 */
#define  VTSS_F_USB3_PORTSC_20_CAS(x)         VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_USB3_PORTSC_20_CAS            VTSS_BIT(24)
#define  VTSS_X_USB3_PORTSC_20_CAS(x)         VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * WCE
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . WCE
 */
#define  VTSS_F_USB3_PORTSC_20_WCE(x)         VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_USB3_PORTSC_20_WCE            VTSS_BIT(25)
#define  VTSS_X_USB3_PORTSC_20_WCE(x)         VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * WDE
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . WDE
 */
#define  VTSS_F_USB3_PORTSC_20_WDE(x)         VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_USB3_PORTSC_20_WDE            VTSS_BIT(26)
#define  VTSS_X_USB3_PORTSC_20_WDE(x)         VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * WOE
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . WOE
 */
#define  VTSS_F_USB3_PORTSC_20_WOE(x)         VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_USB3_PORTSC_20_WOE            VTSS_BIT(27)
#define  VTSS_X_USB3_PORTSC_20_WOE(x)         VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . RESERVED_29_28
 */
#define  VTSS_F_USB3_PORTSC_20_RESERVED_29_28(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_USB3_PORTSC_20_RESERVED_29_28     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_USB3_PORTSC_20_RESERVED_29_28(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * Reset Value
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . DR
 */
#define  VTSS_F_USB3_PORTSC_20_DR(x)          VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_USB3_PORTSC_20_DR             VTSS_BIT(30)
#define  VTSS_X_USB3_PORTSC_20_DR(x)          VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Reserved
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * Programming this field with random data will cause side effect i.e.
 * Register Access will fail (Timeout) if the pipe clock is not running or
 * reset is asserted . Bit Bash register testing is not recommended.
 *
 * \details
 * Field: ::VTSS_USB3_PORTSC_20 . RESERVED_31
 */
#define  VTSS_F_USB3_PORTSC_20_RESERVED_31(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_USB3_PORTSC_20_RESERVED_31    VTSS_BIT(31)
#define  VTSS_X_USB3_PORTSC_20_RESERVED_31(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief USB3 Port Power Management Status and Control Register Bit Definitions

This register is in the Aux Power well. It is only reset by platform hardware during a cold reset or in response to a Host Controller Reset (HCRST).

Programming this field with random data will cause side effect i.e. Register Access will fail (Timeout) if the pipe clock is not running or reset is asserted . Bit Bash register testing is not recommended.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_PORT_REG_SET:PORTPMSC_20
 */
#define VTSS_USB3_PORTPMSC_20                VTSS_IOREG(VTSS_TO_USB3,0x109)

/**
 * \brief
 * L1 Status (L1S) - RO. Default = 0.
 *
 * This field is used by software to determine whether an L1-based suspend
 * request (LMP transaction) was successful, specifically:
 *
 * Value Meaning 0 Invalid - This field is ignored by software.
 *  - 1 Success - Port successfully transitioned to L1 (ACK)
 *  - 2 Not Yet - Device is unable to enter L1 at this time (NYET)
 *  - 3 Not Supported -Device does not support L1 transitions (STALL)
 *  - 4 Timeout/Error -Device failed to respond to the LPM Transaction or
 * an error occurred
 *  - 5-7 Reserved The value of this field is only valid when the port
 * resides in the L0 or L1 state (PLS = '0' or '2').
 *
 * Refer to section 4.23.5.1.1 for more information.
 *
 * \details
 * Field: ::VTSS_USB3_PORTPMSC_20 . L1S
 */
#define  VTSS_F_USB3_PORTPMSC_20_L1S(x)       VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_USB3_PORTPMSC_20_L1S          VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_USB3_PORTPMSC_20_L1S(x)       VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * RWE Port Test Control
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_PORTPMSC_20 . RWE
 */
#define  VTSS_F_USB3_PORTPMSC_20_RWE(x)       VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_USB3_PORTPMSC_20_RWE          VTSS_BIT(3)
#define  VTSS_X_USB3_PORTPMSC_20_RWE(x)       VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Host Initiated Resume Duration (HIRD) - RW.
 *
 * Default = '0'. System software sets this field to indicate to the
 * recipient device how long the xHC will drive resume if it (the xHC)
 * initiates an exit from L1.
 *
 * The HIRD value is encoded as follows: Value Description 0h 50us.
 * (default) 1h 125us. 2h 200us.  Fh 1.175 ms. The value of 0000b is
 * interpreted as 50us. Each incrementing value up adds 75us. to the
 * previous value.
 *
 * For example, 0001b is 125us, 0010b is 200us and so on. Based on this
 * rule, the maximum value resume drive time is at encoding value 1111b
 * which represents 1.2ms.
 *
 * Note that the HIRD field is used by both software and hardware
 * controlled LPM.
 *
 * Refer to section 4.23.5.1.1 for more information on HIRD use. Refer to
 * Section 4.1 of the USB2 LPM spec for more information on the use of the
 * HIRD field.

 *
 * \details
 * Field: ::VTSS_USB3_PORTPMSC_20 . HIRD
 */
#define  VTSS_F_USB3_PORTPMSC_20_HIRD(x)      VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_USB3_PORTPMSC_20_HIRD         VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_USB3_PORTPMSC_20_HIRD(x)      VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * L1DSLOT
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTPMSC_20 . L1DSLOT
 */
#define  VTSS_F_USB3_PORTPMSC_20_L1DSLOT(x)   VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_USB3_PORTPMSC_20_L1DSLOT      VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_USB3_PORTPMSC_20_L1DSLOT(x)   VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Port Test Control
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_PORTPMSC_20 . HLE
 */
#define  VTSS_F_USB3_PORTPMSC_20_HLE(x)       VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_USB3_PORTPMSC_20_HLE          VTSS_BIT(16)
#define  VTSS_X_USB3_PORTPMSC_20_HLE(x)       VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_PORTPMSC_20 . RESERVED_27_17
 */
#define  VTSS_F_USB3_PORTPMSC_20_RESERVED_27_17(x)  VTSS_ENCODE_BITFIELD(x,17,11)
#define  VTSS_M_USB3_PORTPMSC_20_RESERVED_27_17     VTSS_ENCODE_BITMASK(17,11)
#define  VTSS_X_USB3_PORTPMSC_20_RESERVED_27_17(x)  VTSS_EXTRACT_BITFIELD(x,17,11)

/**
 * \brief
 * Port Test Control
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTPMSC_20 . PRTTSTCTRL
 */
#define  VTSS_F_USB3_PORTPMSC_20_PRTTSTCTRL(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_USB3_PORTPMSC_20_PRTTSTCTRL     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_USB3_PORTPMSC_20_PRTTSTCTRL(x)  VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief Port Link Info Register

Programming this field with random data will cause side effect i.e. Register Access will fail (Timeout) if the pipe clock is not running or reset is asserted . Bit Bash register testing is not recommended.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_PORT_REG_SET:PORTLI_20
 */
#define VTSS_USB3_PORTLI_20                  VTSS_IOREG(VTSS_TO_USB3,0x10a)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_PORTLI_20 . PORTLI_20_RESERVED_31_0
 */
#define  VTSS_F_USB3_PORTLI_20_PORTLI_20_RESERVED_31_0(x)  (x)
#define  VTSS_M_USB3_PORTLI_20_PORTLI_20_RESERVED_31_0     0xffffffff
#define  VTSS_X_USB3_PORTLI_20_PORTLI_20_RESERVED_31_0(x)  (x)


/**
 * \brief USB2 Port Hardware LPM Control Register Bit Definitions

For a description of this standard USB register field, see the eXtensible Host Controller Interface for Universal Serial Bus (USB) Specification 3.0.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_PORT_REG_SET:PORTHLPMC_20
 */
#define VTSS_USB3_PORTHLPMC_20               VTSS_IOREG(VTSS_TO_USB3,0x10b)

/**
 * \brief
 * Host Initiated Resume Duration Mode (HIRDM)
 *
 * - RWS. Default = 0h.
 *
 * Indicates which HIRD value must be used.
 *
 * The following are permissible values:
 *
 *	     Value Description
 *
 *	       0   Initiate L1 using HIRD only on timeout.
 *
 * (default)   1   Initiate L1 using HIRDD on timeout.
 *
 *		   If rejected by device, initiate L1 using HIRD.
 *
 *	      3-2  Reserved.

 *
 * \details
 * Field: ::VTSS_USB3_PORTHLPMC_20 . HIRDM
 */
#define  VTSS_F_USB3_PORTHLPMC_20_HIRDM(x)    VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_USB3_PORTHLPMC_20_HIRDM       VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_USB3_PORTHLPMC_20_HIRDM(x)    VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * PORTHLPMC_20 L1_TIMEOUT.
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTHLPMC_20 . L1_TIMEOUT
 */
#define  VTSS_F_USB3_PORTHLPMC_20_L1_TIMEOUT(x)  VTSS_ENCODE_BITFIELD(x,2,8)
#define  VTSS_M_USB3_PORTHLPMC_20_L1_TIMEOUT     VTSS_ENCODE_BITMASK(2,8)
#define  VTSS_X_USB3_PORTHLPMC_20_L1_TIMEOUT(x)  VTSS_EXTRACT_BITFIELD(x,2,8)

/**
 * \brief
 * PORTHLPMC_20 HIRDD
 *
 * \details
 * Field: ::VTSS_USB3_PORTHLPMC_20 . HIRDD
 */
#define  VTSS_F_USB3_PORTHLPMC_20_HIRDD(x)    VTSS_ENCODE_BITFIELD(x,10,4)
#define  VTSS_M_USB3_PORTHLPMC_20_HIRDD       VTSS_ENCODE_BITMASK(10,4)
#define  VTSS_X_USB3_PORTHLPMC_20_HIRDD(x)    VTSS_EXTRACT_BITFIELD(x,10,4)

/**
 * \brief
 * Reserved
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_PORTHLPMC_20 . RESERVED_31_14
 */
#define  VTSS_F_USB3_PORTHLPMC_20_RESERVED_31_14(x)  VTSS_ENCODE_BITFIELD(x,14,18)
#define  VTSS_M_USB3_PORTHLPMC_20_RESERVED_31_14     VTSS_ENCODE_BITMASK(14,18)
#define  VTSS_X_USB3_PORTHLPMC_20_RESERVED_31_14(x)  VTSS_EXTRACT_BITFIELD(x,14,18)


/**
 * \brief USB3 Port Power Management Status and Control Register Bit Definitions

This register is in the Aux Power well. It is only reset by platform hardware during a cold reset or in response to a Host Controller Reset (HCRST).

Programming this field with random data will cause side effect i.e. Register Access will fail (Timeout) if the pipe clock is not running or reset is asserted . Bit Bash register testing is not recommended.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_PORT_REG_SET:PORTPMSC_30
 */
#define VTSS_USB3_PORTPMSC_30                VTSS_IOREG(VTSS_TO_USB3,0x10d)

/**
 * \brief
 * U1_TIMEOUT
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTPMSC_30 . U1_TIMEOUT
 */
#define  VTSS_F_USB3_PORTPMSC_30_U1_TIMEOUT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_USB3_PORTPMSC_30_U1_TIMEOUT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_USB3_PORTPMSC_30_U1_TIMEOUT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * U2_TIMEOUT
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTPMSC_30 . U2_TIMEOUT
 */
#define  VTSS_F_USB3_PORTPMSC_30_U2_TIMEOUT(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_USB3_PORTPMSC_30_U2_TIMEOUT     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_USB3_PORTPMSC_30_U2_TIMEOUT(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * FLA
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTPMSC_30 . FLA
 */
#define  VTSS_F_USB3_PORTPMSC_30_FLA(x)       VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_USB3_PORTPMSC_30_FLA          VTSS_BIT(16)
#define  VTSS_X_USB3_PORTPMSC_30_FLA(x)       VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_PORTPMSC_30 . RESERVED_31_17
 */
#define  VTSS_F_USB3_PORTPMSC_30_RESERVED_31_17(x)  VTSS_ENCODE_BITFIELD(x,17,15)
#define  VTSS_M_USB3_PORTPMSC_30_RESERVED_31_17     VTSS_ENCODE_BITMASK(17,15)
#define  VTSS_X_USB3_PORTPMSC_30_RESERVED_31_17(x)  VTSS_EXTRACT_BITFIELD(x,17,15)


/**
 * \brief Port Link Info Register

Programming this field with random data will cause side effect i.e. Register Access will fail (Timeout) if the pipe clock is not running or reset is asserted . Bit Bash register testing is not recommended.
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_PORT_REG_SET:PORTLI_30
 */
#define VTSS_USB3_PORTLI_30                  VTSS_IOREG(VTSS_TO_USB3,0x10e)

/**
 * \brief
 * LINK_ERROR_COUNT
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTLI_30 . LINK_ERROR_COUNT
 */
#define  VTSS_F_USB3_PORTLI_30_LINK_ERROR_COUNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_USB3_PORTLI_30_LINK_ERROR_COUNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_USB3_PORTLI_30_LINK_ERROR_COUNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_PORTLI_30 . RESERVED_31_16
 */
#define  VTSS_F_USB3_PORTLI_30_RESERVED_31_16(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_PORTLI_30_RESERVED_31_16     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_PORTLI_30_RESERVED_31_16(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief USB2 Port Hardware LPM Control Register Bit Definitions

For a description of this standard USB register field, see the eXtensible Host Controller Interface for Universal Serial Bus (USB) Specification 3.0.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_PORT_REG_SET:PORTHLPMC_30
 */
#define VTSS_USB3_PORTHLPMC_30               VTSS_IOREG(VTSS_TO_USB3,0x10f)

/**
 * \brief
 * Reserved
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_PORTHLPMC_30 . PORTHLPMC_30_RESERVED_31_0
 */
#define  VTSS_F_USB3_PORTHLPMC_30_PORTHLPMC_30_RESERVED_31_0(x)  (x)
#define  VTSS_M_USB3_PORTHLPMC_30_PORTHLPMC_30_RESERVED_31_0     0xffffffff
#define  VTSS_X_USB3_PORTHLPMC_30_PORTHLPMC_30_RESERVED_31_0(x)  (x)

/**
 * Register Group: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_RUNTIME_REGS
 *
 * USB3 Host Cntrl Runtime Regs Block
 */


/**
 * \brief Microframe Index Register Bit Definitions

For a description of this standard USB register field, see the eXtensible Host Controller Interface for Universal Serial Bus (USB) Specification 3.0.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_RUNTIME_REGS:MFINDEX
 */
#define VTSS_USB3_MFINDEX                    VTSS_IOREG(VTSS_TO_USB3,0x110)

/**
 * \brief
 * MICROFRAME_INDEX
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_MFINDEX . MICROFRAME_INDEX
 */
#define  VTSS_F_USB3_MFINDEX_MICROFRAME_INDEX(x)  VTSS_ENCODE_BITFIELD(x,0,14)
#define  VTSS_M_USB3_MFINDEX_MICROFRAME_INDEX     VTSS_ENCODE_BITMASK(0,14)
#define  VTSS_X_USB3_MFINDEX_MICROFRAME_INDEX(x)  VTSS_EXTRACT_BITFIELD(x,0,14)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_MFINDEX . RESERVED_31_14
 */
#define  VTSS_F_USB3_MFINDEX_RESERVED_31_14(x)  VTSS_ENCODE_BITFIELD(x,14,18)
#define  VTSS_M_USB3_MFINDEX_RESERVED_31_14     VTSS_ENCODE_BITMASK(14,18)
#define  VTSS_X_USB3_MFINDEX_RESERVED_31_14(x)  VTSS_EXTRACT_BITFIELD(x,14,18)


/**
 * \brief RsvdZ

For a description of this standard USB register field, see the eXtensible Host Controller Interface for Universal Serial Bus (USB) Specification 3.0.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_HOST_CNTRL_RUNTIME_REGS:RSVDZ
 */
#define VTSS_USB3_RSVDZ                      VTSS_IOREG(VTSS_TO_USB3,0x111)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_RSVDZ . RESERVED_31_0
 */
#define  VTSS_F_USB3_RSVDZ_RESERVED_31_0(x)   (x)
#define  VTSS_M_USB3_RSVDZ_RESERVED_31_0      0xffffffff
#define  VTSS_X_USB3_RSVDZ_RESERVED_31_0(x)   (x)

/**
 * Register Group: \a USB3:DWC_USB3_BLOCK_INTERRUPTER_REGS
 *
 * USB3 Interrupter Regs Block
 */


/**
 * \brief Interrupter Management Register Bit Definitions

For a description of this standard USB register field, see the eXtensible Host Controller Interface for Universal Serial Bus (USB) Specification 3.0.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_INTERRUPTER_REGS:IMAN
 */
#define VTSS_USB3_IMAN                       VTSS_IOREG(VTSS_TO_USB3,0x118)

/**
 * \brief
 * IP Interrupt Pending
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_IMAN . IP
 */
#define  VTSS_F_USB3_IMAN_IP(x)               VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_USB3_IMAN_IP                  VTSS_BIT(0)
#define  VTSS_X_USB3_IMAN_IP(x)               VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * IE
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_IMAN . IE
 */
#define  VTSS_F_USB3_IMAN_IE(x)               VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_USB3_IMAN_IE                  VTSS_BIT(1)
#define  VTSS_X_USB3_IMAN_IE(x)               VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_IMAN . RESERVED_31_2
 */
#define  VTSS_F_USB3_IMAN_RESERVED_31_2(x)    VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_USB3_IMAN_RESERVED_31_2       VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_USB3_IMAN_RESERVED_31_2(x)    VTSS_EXTRACT_BITFIELD(x,2,30)


/**
 * \brief Interrupter Moderation Register

The software may use this register to pace (or even out) the delivery of interrupts to the host CPU.

This register provides a guaranteed inter-interrupt delay between interrupts asserted by the xHC, regardless of USB traffic conditions.

To independently validate configuration settings, software may use the following algorithm to convert the inter-interrupt Interval value to the common 'interrupts/sec' performance metric.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_INTERRUPTER_REGS:IMOD
 */
#define VTSS_USB3_IMOD                       VTSS_IOREG(VTSS_TO_USB3,0x119)

/**
 * \brief
 * Interrupt Moderation Interval (IMODI) - RW.
 *
 * Default = '4000' (~1ms). Minimum inter-interrupt interval. The interval
 * is specified in 250ns increments.
 *
 * A value of '0' disables interrupt throttling logic and interrupts is
 * generated immediately if IP = '0', EHB = '0', and the Event Ring is not
 * empty.

 *
 * \details
 * Field: ::VTSS_USB3_IMOD . IMODI
 */
#define  VTSS_F_USB3_IMOD_IMODI(x)            VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_USB3_IMOD_IMODI               VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_USB3_IMOD_IMODI(x)            VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Interrupt Moderation Counter (IMODC)
 *
 * - RW.
 *
 * Default = undefined. Down counter.
 *
 * Loaded with the IMODI value whenever IP is cleared to '0', counts down
 * to '0', and stops. The associated interrupt is signaled whenever this
 * counter is '0', the Event Ring is not empty, the IE and IP flags = '1',
 * and EHB = '0'. This counter may be directly written by software at any
 * time to alter the interrupt rate.

 *
 * \details
 * Field: ::VTSS_USB3_IMOD . IMODC
 */
#define  VTSS_F_USB3_IMOD_IMODC(x)            VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_IMOD_IMODC               VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_IMOD_IMODC(x)            VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief Event Ring Segment Table Size Register Bit Definitions

For a description of this standard USB register field, see the eXtensible Host Controller Interface for Universal Serial Bus (USB) Specification 3.0.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_INTERRUPTER_REGS:ERSTSZ
 */
#define VTSS_USB3_ERSTSZ                     VTSS_IOREG(VTSS_TO_USB3,0x11a)

/**
 * \brief
 * ERS_TABLE_SIZE
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_ERSTSZ . ERS_TABLE_SIZE
 */
#define  VTSS_F_USB3_ERSTSZ_ERS_TABLE_SIZE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_USB3_ERSTSZ_ERS_TABLE_SIZE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_USB3_ERSTSZ_ERS_TABLE_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_ERSTSZ . RESERVED_31_16
 */
#define  VTSS_F_USB3_ERSTSZ_RESERVED_31_16(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_ERSTSZ_RESERVED_31_16     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_ERSTSZ_RESERVED_31_16(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/**
 * \brief RsvdP
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_INTERRUPTER_REGS:RSVDP
 */
#define VTSS_USB3_RSVDP                      VTSS_IOREG(VTSS_TO_USB3,0x11b)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_RSVDP . RESERVED_31_0
 */
#define  VTSS_F_USB3_RSVDP_RESERVED_31_0(x)   (x)
#define  VTSS_M_USB3_RSVDP_RESERVED_31_0      0xffffffff
#define  VTSS_X_USB3_RSVDP_RESERVED_31_0(x)   (x)


/**
 * \brief ERSTBA_LO
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_INTERRUPTER_REGS:ERSTBA_LO
 */
#define VTSS_USB3_ERSTBA_LO                  VTSS_IOREG(VTSS_TO_USB3,0x11c)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_ERSTBA_LO . RESERVED_5_0
 */
#define  VTSS_F_USB3_ERSTBA_LO_RESERVED_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_USB3_ERSTBA_LO_RESERVED_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_USB3_ERSTBA_LO_RESERVED_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * ERS_TABLE_BAR
 *
 * \details
 * Field: ::VTSS_USB3_ERSTBA_LO . ERSTBA_LO_ERS_TABLE_BAR
 */
#define  VTSS_F_USB3_ERSTBA_LO_ERSTBA_LO_ERS_TABLE_BAR(x)  VTSS_ENCODE_BITFIELD(x,6,26)
#define  VTSS_M_USB3_ERSTBA_LO_ERSTBA_LO_ERS_TABLE_BAR     VTSS_ENCODE_BITMASK(6,26)
#define  VTSS_X_USB3_ERSTBA_LO_ERSTBA_LO_ERS_TABLE_BAR(x)  VTSS_EXTRACT_BITFIELD(x,6,26)


/**
 * \brief ERSTBA_HI
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_INTERRUPTER_REGS:ERSTBA_HI
 */
#define VTSS_USB3_ERSTBA_HI                  VTSS_IOREG(VTSS_TO_USB3,0x11d)

/**
 * \brief
 * ERS_TABLE_BAR
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_ERSTBA_HI . ERSTBA_HI_ERS_TABLE_BAR
 */
#define  VTSS_F_USB3_ERSTBA_HI_ERSTBA_HI_ERS_TABLE_BAR(x)  (x)
#define  VTSS_M_USB3_ERSTBA_HI_ERSTBA_HI_ERS_TABLE_BAR     0xffffffff
#define  VTSS_X_USB3_ERSTBA_HI_ERSTBA_HI_ERS_TABLE_BAR(x)  (x)


/**
 * \brief ERDP_LO

For a description of this standard USB register field, see the eXtensible Host Controller Interface for Universal Serial Bus (USB) Specification 3.0.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_INTERRUPTER_REGS:ERDP_LO
 */
#define VTSS_USB3_ERDP_LO                    VTSS_IOREG(VTSS_TO_USB3,0x11e)

/**
 * \brief
 * DESI
 *  - For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_ERDP_LO . DESI
 */
#define  VTSS_F_USB3_ERDP_LO_DESI(x)          VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_USB3_ERDP_LO_DESI             VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_USB3_ERDP_LO_DESI(x)          VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * HC OS Owned SemaphoreERS_TABLE_SIZEHC BIOS Owned Semaphore
 *  USB SMI Enable
 *  SMI on Host System Error Enable
 *  - SMI on OS Ownership Enable
 *  - SMI on PCI Command Enable
 *  - SMI on BAR Enable
 *  - SMI on Event Interrupt
 *  - SMI on Host System Error
 *  - SMI on OS Ownership Change
 *  - SMI on PCI Command
 *  - SMI on BAR
 *  - Compatible Port Count
 *  - HC OS Owned Semaphore
 *  - HC BIOS Owned Semaphore
 *  - USB SMI Enable
 *  - SMI on Host System Error Enable
 *  - SMI on OS Ownership Enable
 *  - SMI on PCI Command Enable
 *  - SMI on BAR Enable
 *  - SMI on Event Interrupt
 *  - SMI on Host System Error
 *  - SMI on OS Ownership Change
 *  - SMI on PCI Command
 *  - SMI on BAR
 *  - Compatible Port Count

 *
 * \details
 * Field: ::VTSS_USB3_ERDP_LO . EHB
 */
#define  VTSS_F_USB3_ERDP_LO_EHB(x)           VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_USB3_ERDP_LO_EHB              VTSS_BIT(3)
#define  VTSS_X_USB3_ERDP_LO_EHB(x)           VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * ERD_PNTR
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_ERDP_LO . ERDP_LO_ERD_PNTR
 */
#define  VTSS_F_USB3_ERDP_LO_ERDP_LO_ERD_PNTR(x)  VTSS_ENCODE_BITFIELD(x,4,28)
#define  VTSS_M_USB3_ERDP_LO_ERDP_LO_ERD_PNTR     VTSS_ENCODE_BITMASK(4,28)
#define  VTSS_X_USB3_ERDP_LO_ERDP_LO_ERD_PNTR(x)  VTSS_EXTRACT_BITFIELD(x,4,28)


/**
 * \brief ERDP_HI
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_INTERRUPTER_REGS:ERDP_HI
 */
#define VTSS_USB3_ERDP_HI                    VTSS_IOREG(VTSS_TO_USB3,0x11f)

/**
 * \brief
 * ERD_PNTR
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_ERDP_HI . ERDP_HI_ERD_PNTR
 */
#define  VTSS_F_USB3_ERDP_HI_ERDP_HI_ERD_PNTR(x)  (x)
#define  VTSS_M_USB3_ERDP_HI_ERDP_HI_ERD_PNTR     0xffffffff
#define  VTSS_X_USB3_ERDP_HI_ERDP_HI_ERD_PNTR(x)  (x)

/**
 * Register Group: \a USB3:DWC_USB3_BLOCK_DOORBELL_REGISTER
 *
 * USB3 Doorbell Reg Block
 */


/**
 * \brief Doorbell Register Bit Field Definitions

For a description of this standard USB register field, see the eXtensible Host Controller Interface for Universal Serial Bus (USB) Specification 3.0.

Programming this field with random data will cause side effect i.e. Register Access will fail (Timeout) if the pipe clock is not running or reset is asserted . Bit Bash register testing is not recommended.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_DOORBELL_REGISTER:DB
 *
 * @param ri Register: DB (??), 0-64
 */
#define VTSS_USB3_DB(ri)                     VTSS_IOREG(VTSS_TO_USB3,0x120 + (ri))

/**
 * \brief
 * DB_TARGET
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_DB . DB_TARGET
 */
#define  VTSS_F_USB3_DB_DB_TARGET(x)          VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_USB3_DB_DB_TARGET             VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_USB3_DB_DB_TARGET(x)          VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_DB . RESERVED_15_8
 */
#define  VTSS_F_USB3_DB_RESERVED_15_8(x)      VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_USB3_DB_RESERVED_15_8         VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_USB3_DB_RESERVED_15_8(x)      VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * DB_STREAM_ID
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_DB . DB_STREAM_ID
 */
#define  VTSS_F_USB3_DB_DB_STREAM_ID(x)       VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_USB3_DB_DB_STREAM_ID          VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_USB3_DB_DB_STREAM_ID(x)       VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * Register Group: \a USB3:DWC_USB3_BLOCK_HC_EXTENDED_CAPABILITY_REGISTER
 *
 * USB3 HC Extended Capability Register Block
 */


/**
 * \brief USBLEGSUP
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_HC_EXTENDED_CAPABILITY_REGISTER:USBLEGSUP
 */
#define VTSS_USB3_USBLEGSUP                  VTSS_IOREG(VTSS_TO_USB3,0x220)

/**
 * \brief
 * CAPABILITY_ID
 * set_register_field_attribute
 * DWC_usb3_map/DWC_usb3_block_HC_Extended_Capability_Register/USBLEGSUP/CA
 * PABILITY_ID RegisterResetValue 0x1
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.
 *
 * \details
 * Field: ::VTSS_USB3_USBLEGSUP . CAPABILITY_ID
 */
#define  VTSS_F_USB3_USBLEGSUP_CAPABILITY_ID(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_USB3_USBLEGSUP_CAPABILITY_ID     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_USB3_USBLEGSUP_CAPABILITY_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * NEXT_CAPABILITY_POINTER
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_USBLEGSUP . NEXT_CAPABILITY_POINTER
 */
#define  VTSS_F_USB3_USBLEGSUP_NEXT_CAPABILITY_POINTER(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_USB3_USBLEGSUP_NEXT_CAPABILITY_POINTER     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_USB3_USBLEGSUP_NEXT_CAPABILITY_POINTER(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * HC_BIOS_OWNED SEMAPHORE
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_USBLEGSUP . HC_BIOS_OWNED
 */
#define  VTSS_F_USB3_USBLEGSUP_HC_BIOS_OWNED(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_USB3_USBLEGSUP_HC_BIOS_OWNED  VTSS_BIT(16)
#define  VTSS_X_USB3_USBLEGSUP_HC_BIOS_OWNED(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_USBLEGSUP . RESERVED_23_17
 */
#define  VTSS_F_USB3_USBLEGSUP_RESERVED_23_17(x)  VTSS_ENCODE_BITFIELD(x,17,7)
#define  VTSS_M_USB3_USBLEGSUP_RESERVED_23_17     VTSS_ENCODE_BITMASK(17,7)
#define  VTSS_X_USB3_USBLEGSUP_RESERVED_23_17(x)  VTSS_EXTRACT_BITFIELD(x,17,7)

/**
 * \brief
 * HC_OS_OWNED SEMAPHORE
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_USBLEGSUP . HC_OS_OWNED
 */
#define  VTSS_F_USB3_USBLEGSUP_HC_OS_OWNED(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_USB3_USBLEGSUP_HC_OS_OWNED    VTSS_BIT(24)
#define  VTSS_X_USB3_USBLEGSUP_HC_OS_OWNED(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_USBLEGSUP . RESERVED_31_25
 */
#define  VTSS_F_USB3_USBLEGSUP_RESERVED_31_25(x)  VTSS_ENCODE_BITFIELD(x,25,7)
#define  VTSS_M_USB3_USBLEGSUP_RESERVED_31_25     VTSS_ENCODE_BITMASK(25,7)
#define  VTSS_X_USB3_USBLEGSUP_RESERVED_31_25(x)  VTSS_EXTRACT_BITFIELD(x,25,7)


/**
 * \brief USBLEGCTLSTS
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_HC_EXTENDED_CAPABILITY_REGISTER:USBLEGCTLSTS
 */
#define VTSS_USB3_USBLEGCTLSTS               VTSS_IOREG(VTSS_TO_USB3,0x221)

/**
 * \brief
 * USB_SMI_ENABLE
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_USBLEGCTLSTS . USB_SMI_ENABLE
 */
#define  VTSS_F_USB3_USBLEGCTLSTS_USB_SMI_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_USB3_USBLEGCTLSTS_USB_SMI_ENABLE  VTSS_BIT(0)
#define  VTSS_X_USB3_USBLEGCTLSTS_USB_SMI_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_USBLEGCTLSTS . RESERVED_3_1
 */
#define  VTSS_F_USB3_USBLEGCTLSTS_RESERVED_3_1(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_USB3_USBLEGCTLSTS_RESERVED_3_1     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_USB3_USBLEGCTLSTS_RESERVED_3_1(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/**
 * \brief
 * SMI_ON_HOST SYSTEM ERROR ENABLE
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_USBLEGCTLSTS . SMI_ON_HOST_E
 */
#define  VTSS_F_USB3_USBLEGCTLSTS_SMI_ON_HOST_E(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_USB3_USBLEGCTLSTS_SMI_ON_HOST_E  VTSS_BIT(4)
#define  VTSS_X_USB3_USBLEGCTLSTS_SMI_ON_HOST_E(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_USBLEGCTLSTS . RESERVED_12_5
 */
#define  VTSS_F_USB3_USBLEGCTLSTS_RESERVED_12_5(x)  VTSS_ENCODE_BITFIELD(x,5,8)
#define  VTSS_M_USB3_USBLEGCTLSTS_RESERVED_12_5     VTSS_ENCODE_BITMASK(5,8)
#define  VTSS_X_USB3_USBLEGCTLSTS_RESERVED_12_5(x)  VTSS_EXTRACT_BITFIELD(x,5,8)

/**
 * \brief
 * SMI_ON_OS OWNERSHIP ENABLE
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_USBLEGCTLSTS . SMI_ON_OS_E
 */
#define  VTSS_F_USB3_USBLEGCTLSTS_SMI_ON_OS_E(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_USB3_USBLEGCTLSTS_SMI_ON_OS_E  VTSS_BIT(13)
#define  VTSS_X_USB3_USBLEGCTLSTS_SMI_ON_OS_E(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * SMI_ON_PCI COMMAND ENABLE
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_USBLEGCTLSTS . SMI_ON_PCI_E
 */
#define  VTSS_F_USB3_USBLEGCTLSTS_SMI_ON_PCI_E(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_USB3_USBLEGCTLSTS_SMI_ON_PCI_E  VTSS_BIT(14)
#define  VTSS_X_USB3_USBLEGCTLSTS_SMI_ON_PCI_E(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * SMI_ON_BAR ENABLE
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_USBLEGCTLSTS . SMI_ON_BAR_E
 */
#define  VTSS_F_USB3_USBLEGCTLSTS_SMI_ON_BAR_E(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_USB3_USBLEGCTLSTS_SMI_ON_BAR_E  VTSS_BIT(15)
#define  VTSS_X_USB3_USBLEGCTLSTS_SMI_ON_BAR_E(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * SMI_ON_EVENT INTERRUPT
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_USBLEGCTLSTS . SMI_ON_EVENT
 */
#define  VTSS_F_USB3_USBLEGCTLSTS_SMI_ON_EVENT(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_USB3_USBLEGCTLSTS_SMI_ON_EVENT  VTSS_BIT(16)
#define  VTSS_X_USB3_USBLEGCTLSTS_SMI_ON_EVENT(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_USBLEGCTLSTS . RESERVED_19_17
 */
#define  VTSS_F_USB3_USBLEGCTLSTS_RESERVED_19_17(x)  VTSS_ENCODE_BITFIELD(x,17,3)
#define  VTSS_M_USB3_USBLEGCTLSTS_RESERVED_19_17     VTSS_ENCODE_BITMASK(17,3)
#define  VTSS_X_USB3_USBLEGCTLSTS_RESERVED_19_17(x)  VTSS_EXTRACT_BITFIELD(x,17,3)

/**
 * \brief
 * SMI_ON_HOST SYSTEM ERROR
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_USBLEGCTLSTS . SMI_ON_HOST
 */
#define  VTSS_F_USB3_USBLEGCTLSTS_SMI_ON_HOST(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_USB3_USBLEGCTLSTS_SMI_ON_HOST  VTSS_BIT(20)
#define  VTSS_X_USB3_USBLEGCTLSTS_SMI_ON_HOST(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_USBLEGCTLSTS . RESERVED_28_21
 */
#define  VTSS_F_USB3_USBLEGCTLSTS_RESERVED_28_21(x)  VTSS_ENCODE_BITFIELD(x,21,8)
#define  VTSS_M_USB3_USBLEGCTLSTS_RESERVED_28_21     VTSS_ENCODE_BITMASK(21,8)
#define  VTSS_X_USB3_USBLEGCTLSTS_RESERVED_28_21(x)  VTSS_EXTRACT_BITFIELD(x,21,8)

/**
 * \brief
 * SMI_ON_OS OWNERSHIP CHANGE
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_USBLEGCTLSTS . SMI_ON_OS
 */
#define  VTSS_F_USB3_USBLEGCTLSTS_SMI_ON_OS(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_USB3_USBLEGCTLSTS_SMI_ON_OS   VTSS_BIT(29)
#define  VTSS_X_USB3_USBLEGCTLSTS_SMI_ON_OS(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * SMI_ON_PCI COMMAND
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_USBLEGCTLSTS . SMI_ON_PCI
 */
#define  VTSS_F_USB3_USBLEGCTLSTS_SMI_ON_PCI(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_USB3_USBLEGCTLSTS_SMI_ON_PCI  VTSS_BIT(30)
#define  VTSS_X_USB3_USBLEGCTLSTS_SMI_ON_PCI(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * SMI_ON_BAR
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_USBLEGCTLSTS . SMI_ON_BAR
 */
#define  VTSS_F_USB3_USBLEGCTLSTS_SMI_ON_BAR(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_USB3_USBLEGCTLSTS_SMI_ON_BAR  VTSS_BIT(31)
#define  VTSS_X_USB3_USBLEGCTLSTS_SMI_ON_BAR(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * Register Group: \a USB3:DWC_USB3_BLOCK_XHCI_SUPT_USB20_PRT_CAP
 *
 * USB3 xHCI Supported Protocol Capability (USB 2.0) Block
 */


/**
 * \brief SUPTPRT2_DW0
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_XHCI_SUPT_USB20_PRT_CAP:SUPTPRT2_DW0
 */
#define VTSS_USB3_SUPTPRT2_DW0               VTSS_IOREG(VTSS_TO_USB3,0x224)

/**
 * \brief
 * CAPABILITY_ID
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT2_DW0 . CAPABILITY_ID
 */
#define  VTSS_F_USB3_SUPTPRT2_DW0_CAPABILITY_ID(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_USB3_SUPTPRT2_DW0_CAPABILITY_ID     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_USB3_SUPTPRT2_DW0_CAPABILITY_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * NEXT_CAPABILITY_POINTER
 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT2_DW0 . NEXT_CAPABILITY_POINTER
 */
#define  VTSS_F_USB3_SUPTPRT2_DW0_NEXT_CAPABILITY_POINTER(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_USB3_SUPTPRT2_DW0_NEXT_CAPABILITY_POINTER     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_USB3_SUPTPRT2_DW0_NEXT_CAPABILITY_POINTER(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * MINOR_REVISION
 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT2_DW0 . MINOR_REVISION
 */
#define  VTSS_F_USB3_SUPTPRT2_DW0_MINOR_REVISION(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_USB3_SUPTPRT2_DW0_MINOR_REVISION     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_USB3_SUPTPRT2_DW0_MINOR_REVISION(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * MAJOR_REVISION
 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT2_DW0 . MAJOR_REVISION
 */
#define  VTSS_F_USB3_SUPTPRT2_DW0_MAJOR_REVISION(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_USB3_SUPTPRT2_DW0_MAJOR_REVISION     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_USB3_SUPTPRT2_DW0_MAJOR_REVISION(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief Register SUPTPRT2_DW1
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_XHCI_SUPT_USB20_PRT_CAP:SUPTPRT2_DW1
 */
#define VTSS_USB3_SUPTPRT2_DW1               VTSS_IOREG(VTSS_TO_USB3,0x225)

/**
 * \brief
 * NAME_STRING
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT2_DW1 . NAME_STRING
 */
#define  VTSS_F_USB3_SUPTPRT2_DW1_NAME_STRING(x)  (x)
#define  VTSS_M_USB3_SUPTPRT2_DW1_NAME_STRING     0xffffffff
#define  VTSS_X_USB3_SUPTPRT2_DW1_NAME_STRING(x)  (x)


/**
 * \brief xHCI Supported Protocol Capability_ Data Word 2

For a description of other register fields, see section 7.2 of the eXtensible Host Controller Interface for Universal Serial Bus (USB) Specification 3.0.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_XHCI_SUPT_USB20_PRT_CAP:SUPTPRT2_DW2
 */
#define VTSS_USB3_SUPTPRT2_DW2               VTSS_IOREG(VTSS_TO_USB3,0x226)

/**
 * \brief
 * COMPATIBLE_PORT_OFFSET
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT2_DW2 . COMPATIBLE_PORT_OFFSET
 */
#define  VTSS_F_USB3_SUPTPRT2_DW2_COMPATIBLE_PORT_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_USB3_SUPTPRT2_DW2_COMPATIBLE_PORT_OFFSET     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_USB3_SUPTPRT2_DW2_COMPATIBLE_PORT_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * COMPATIBLE_PORT_COUNT
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT2_DW2 . COMPATIBLE_PORT_COUNT
 */
#define  VTSS_F_USB3_SUPTPRT2_DW2_COMPATIBLE_PORT_COUNT(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_USB3_SUPTPRT2_DW2_COMPATIBLE_PORT_COUNT     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_USB3_SUPTPRT2_DW2_COMPATIBLE_PORT_COUNT(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * HSO
 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT2_DW2 . HSO
 */
#define  VTSS_F_USB3_SUPTPRT2_DW2_HSO(x)      VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_USB3_SUPTPRT2_DW2_HSO         VTSS_BIT(17)
#define  VTSS_X_USB3_SUPTPRT2_DW2_HSO(x)      VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * IHI
 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT2_DW2 . IHI
 */
#define  VTSS_F_USB3_SUPTPRT2_DW2_IHI(x)      VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_USB3_SUPTPRT2_DW2_IHI         VTSS_BIT(18)
#define  VTSS_X_USB3_SUPTPRT2_DW2_IHI(x)      VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Compatible Port Offset.
 *
 * Compatible Port Count
 *
 * Refer to Table 7-3 in the Databook.

 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT2_DW2 . HLC
 */
#define  VTSS_F_USB3_SUPTPRT2_DW2_HLC(x)      VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_USB3_SUPTPRT2_DW2_HLC         VTSS_BIT(19)
#define  VTSS_X_USB3_SUPTPRT2_DW2_HLC(x)      VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * BESL LPM Capability.
 * When this bit is set to:
 *  - 1: The ports described by this xHCI Supported Protocol Capability
 * applies BESL timing to the BESL and BESLD fields of the PORTPMSC and
 * PORTHLPMC registers.
 *  - 0: The ports described by this xHCI Supported Protocol Capability
 * applies HIRD timing to the BESL and BESLD fields of the PORTPMSC and
 * PORTHLPMC registers.

 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT2_DW2 . BLC
 */
#define  VTSS_F_USB3_SUPTPRT2_DW2_BLC(x)      VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_USB3_SUPTPRT2_DW2_BLC         VTSS_BIT(20)
#define  VTSS_X_USB3_SUPTPRT2_DW2_BLC(x)      VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT2_DW2 . RESERVED_24_21
 */
#define  VTSS_F_USB3_SUPTPRT2_DW2_RESERVED_24_21(x)  VTSS_ENCODE_BITFIELD(x,21,4)
#define  VTSS_M_USB3_SUPTPRT2_DW2_RESERVED_24_21     VTSS_ENCODE_BITMASK(21,4)
#define  VTSS_X_USB3_SUPTPRT2_DW2_RESERVED_24_21(x)  VTSS_EXTRACT_BITFIELD(x,21,4)

/**
 * \brief
 * Hub Depth
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT2_DW2 . MHD
 */
#define  VTSS_F_USB3_SUPTPRT2_DW2_MHD(x)      VTSS_ENCODE_BITFIELD(x,25,3)
#define  VTSS_M_USB3_SUPTPRT2_DW2_MHD         VTSS_ENCODE_BITMASK(25,3)
#define  VTSS_X_USB3_SUPTPRT2_DW2_MHD(x)      VTSS_EXTRACT_BITFIELD(x,25,3)

/**
 * \brief
 * PSIC
 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT2_DW2 . PSIC
 */
#define  VTSS_F_USB3_SUPTPRT2_DW2_PSIC(x)     VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_USB3_SUPTPRT2_DW2_PSIC        VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_USB3_SUPTPRT2_DW2_PSIC(x)     VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief Register SUPTPRT2_DW3
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_XHCI_SUPT_USB20_PRT_CAP:SUPTPRT2_DW3
 */
#define VTSS_USB3_SUPTPRT2_DW3               VTSS_IOREG(VTSS_TO_USB3,0x227)

/**
 * \brief
 * Protocol Slot Type
 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT2_DW3 . PROTCL_SLT_TY
 */
#define  VTSS_F_USB3_SUPTPRT2_DW3_PROTCL_SLT_TY(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_USB3_SUPTPRT2_DW3_PROTCL_SLT_TY     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_USB3_SUPTPRT2_DW3_PROTCL_SLT_TY(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT2_DW3 . RESERVED_31_5
 */
#define  VTSS_F_USB3_SUPTPRT2_DW3_RESERVED_31_5(x)  VTSS_ENCODE_BITFIELD(x,5,27)
#define  VTSS_M_USB3_SUPTPRT2_DW3_RESERVED_31_5     VTSS_ENCODE_BITMASK(5,27)
#define  VTSS_X_USB3_SUPTPRT2_DW3_RESERVED_31_5(x)  VTSS_EXTRACT_BITFIELD(x,5,27)

/**
 * Register Group: \a USB3:DWC_USB3_BLOCK_XHCI_SUPT_USB30_PRT_CAP
 *
 * USB3 xHCI Supported Protocol Capability (USB 3.0) Block
 */


/**
 * \brief Register SUPTPRT3_DW0
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_XHCI_SUPT_USB30_PRT_CAP:SUPTPRT3_DW0
 */
#define VTSS_USB3_SUPTPRT3_DW0               VTSS_IOREG(VTSS_TO_USB3,0x228)

/**
 * \brief
 * CAPABILITY_ID
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT3_DW0 . CAPABILITY_ID
 */
#define  VTSS_F_USB3_SUPTPRT3_DW0_CAPABILITY_ID(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_USB3_SUPTPRT3_DW0_CAPABILITY_ID     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_USB3_SUPTPRT3_DW0_CAPABILITY_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * NEXT_CAPABILITY_POINTER
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT3_DW0 . NEXT_CAPABILITY_POINTER
 */
#define  VTSS_F_USB3_SUPTPRT3_DW0_NEXT_CAPABILITY_POINTER(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_USB3_SUPTPRT3_DW0_NEXT_CAPABILITY_POINTER     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_USB3_SUPTPRT3_DW0_NEXT_CAPABILITY_POINTER(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * MINOR_REVISION
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT3_DW0 . MINOR_REVISION
 */
#define  VTSS_F_USB3_SUPTPRT3_DW0_MINOR_REVISION(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_USB3_SUPTPRT3_DW0_MINOR_REVISION     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_USB3_SUPTPRT3_DW0_MINOR_REVISION(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * MAJOR_REVISION
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT3_DW0 . MAJOR_REVISION
 */
#define  VTSS_F_USB3_SUPTPRT3_DW0_MAJOR_REVISION(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_USB3_SUPTPRT3_DW0_MAJOR_REVISION     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_USB3_SUPTPRT3_DW0_MAJOR_REVISION(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief Register SUPTPRT3_DW1
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_XHCI_SUPT_USB30_PRT_CAP:SUPTPRT3_DW1
 */
#define VTSS_USB3_SUPTPRT3_DW1               VTSS_IOREG(VTSS_TO_USB3,0x229)

/**
 * \brief
 * NAME_STRING
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT3_DW1 . NAME_STRING
 */
#define  VTSS_F_USB3_SUPTPRT3_DW1_NAME_STRING(x)  (x)
#define  VTSS_M_USB3_SUPTPRT3_DW1_NAME_STRING     0xffffffff
#define  VTSS_X_USB3_SUPTPRT3_DW1_NAME_STRING(x)  (x)


/**
 * \brief SUPTPRT3_DW2

For a description of this standard USB register field, see the eXtensible Host Controller Interface for Universal Serial Bus (USB) Specification 3.0.

 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_XHCI_SUPT_USB30_PRT_CAP:SUPTPRT3_DW2
 */
#define VTSS_USB3_SUPTPRT3_DW2               VTSS_IOREG(VTSS_TO_USB3,0x22a)

/**
 * \brief
 * COMPATIBLE_PORT_OFFSET
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT3_DW2 . COMPATIBLE_PORT_OFFSET
 */
#define  VTSS_F_USB3_SUPTPRT3_DW2_COMPATIBLE_PORT_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_USB3_SUPTPRT3_DW2_COMPATIBLE_PORT_OFFSET     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_USB3_SUPTPRT3_DW2_COMPATIBLE_PORT_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * COMPATIBLE_PORT_COUNT
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT3_DW2 . COMPATIBLE_PORT_COUNT
 */
#define  VTSS_F_USB3_SUPTPRT3_DW2_COMPATIBLE_PORT_COUNT(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_USB3_SUPTPRT3_DW2_COMPATIBLE_PORT_COUNT     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_USB3_SUPTPRT3_DW2_COMPATIBLE_PORT_COUNT(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Hub Depth
 *
 * For a description of this standard USB register field, see the
 * eXtensible Host Controller Interface for Universal Serial Bus (USB)
 * Specification 3.0.

 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT3_DW2 . MHD
 */
#define  VTSS_F_USB3_SUPTPRT3_DW2_MHD(x)      VTSS_ENCODE_BITFIELD(x,25,3)
#define  VTSS_M_USB3_SUPTPRT3_DW2_MHD         VTSS_ENCODE_BITMASK(25,3)
#define  VTSS_X_USB3_SUPTPRT3_DW2_MHD(x)      VTSS_EXTRACT_BITFIELD(x,25,3)

/**
 * \brief
 * PSIC
 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT3_DW2 . PSIC
 */
#define  VTSS_F_USB3_SUPTPRT3_DW2_PSIC(x)     VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_USB3_SUPTPRT3_DW2_PSIC        VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_USB3_SUPTPRT3_DW2_PSIC(x)     VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief SUPTPRT3_DW3
 *
 * \details
 * Register: \a USB3:DWC_USB3_BLOCK_XHCI_SUPT_USB30_PRT_CAP:SUPTPRT3_DW3
 */
#define VTSS_USB3_SUPTPRT3_DW3               VTSS_IOREG(VTSS_TO_USB3,0x22b)

/**
 * \brief
 * Protocol Slot Type
 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT3_DW3 . PROTCL_SLT_TY
 */
#define  VTSS_F_USB3_SUPTPRT3_DW3_PROTCL_SLT_TY(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_USB3_SUPTPRT3_DW3_PROTCL_SLT_TY     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_USB3_SUPTPRT3_DW3_PROTCL_SLT_TY(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_USB3_SUPTPRT3_DW3 . RESERVED_31_5
 */
#define  VTSS_F_USB3_SUPTPRT3_DW3_RESERVED_31_5(x)  VTSS_ENCODE_BITFIELD(x,5,27)
#define  VTSS_M_USB3_SUPTPRT3_DW3_RESERVED_31_5     VTSS_ENCODE_BITMASK(5,27)
#define  VTSS_X_USB3_SUPTPRT3_DW3_RESERVED_31_5(x)  VTSS_EXTRACT_BITFIELD(x,5,27)


#endif /* _VTSS_LAGUNA_REGS_USB3_H_ */
