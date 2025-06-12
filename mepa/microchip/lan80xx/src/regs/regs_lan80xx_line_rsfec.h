// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _LAN80XX_MALIBU25G_REGS_LINE_RSFEC_H_
#define _LAN80XX_MALIBU25G_REGS_LINE_RSFEC_H_

#include "regs_lan8042_common.h"

/***********************************************************************
 *
 * Target: \a LINE_RSFEC
 *
 * PCS Control, Configuration and Status Registers; All registers are 16-bit
 * wide only.
 *
 ***********************************************************************/

/**
 * Register Group: \a LINE_RSFEC:RS_FEC
 *
 * RS_FEC Sub-module Configuration, Control and Status Registers; All registers are 16-bit wide.
 */


/**
 * \brief Control register for enabling FEC functions.
 *
 * \details
 * Register: \a LINE_RSFEC:RS_FEC:RS_FEC_CONTROL
 */
#define LAN80XX_LINE_RSFEC_RS_FEC_CONTROL       LAN80XX_IOREG(MMD_ID_LINE_RSFEC, 0, 0xc8)

/**
 * \brief
 * When 1, bypass the decoder's correction function for reduced latency;
 * When
 * 0, normal FEC operation; Bit is writeable only if capability in
 * FEC_STATUS indicates this feature.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_CONTROL . RS_FEC_CONTROL_BYPASS_CORRECTION
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_CONTROL_RS_FEC_CONTROL_BYPASS_CORRECTION(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_CONTROL_RS_FEC_CONTROL_BYPASS_CORRECTION  LAN80XX_BIT(0)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_CONTROL_RS_FEC_CONTROL_BYPASS_CORRECTION(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * When 1, configure the FEC decoder to not indicate errors to the PCS
 * layer; When
 *  0, the FEC decoder indicates errors to the PCS layer; Bit is writeable
 * only if capability in FEC_STATUS indicates this feature.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_CONTROL . BYPASS_ERROR_INDICATION
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_CONTROL_BYPASS_ERROR_INDICATION(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_CONTROL_BYPASS_ERROR_INDICATION  LAN80XX_BIT(1)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_CONTROL_BYPASS_ERROR_INDICATION(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Set the FEC91 Padding bit fo FEC91 transcoder[256]; When1, padding bit
 * is 1; When 0, padding bit is 0
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_CONTROL . FEC91_TC_PADDING_VALUE
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_CONTROL_FEC91_TC_PADDING_VALUE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),9,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_CONTROL_FEC91_TC_PADDING_VALUE  LAN80XX_BIT(9)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_CONTROL_FEC91_TC_PADDING_VALUE(x)  LAN80XX_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * When 1, FEC91 Padding Value is toggling; When 0, padding bit is keep
 * unchange
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_CONTROL . FEC91_TC_PAD_ALTER
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_CONTROL_FEC91_TC_PAD_ALTER(x)  LAN80XX_ENCODE_BITFIELD(!!(x),10,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_CONTROL_FEC91_TC_PAD_ALTER  LAN80XX_BIT(10)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_CONTROL_FEC91_TC_PAD_ALTER(x)  LAN80XX_EXTRACT_BITFIELD(x,10,1)


/**
 * \brief RS FEC Status register.
 *
 * \details
 * Register: \a LINE_RSFEC:RS_FEC:RS_FEC_STATUS
 */
#define LAN80XX_LINE_RSFEC_RS_FEC_STATUS        LAN80XX_IOREG(MMD_ID_LINE_RSFEC, 0, 0xc9)

/**
 * \brief
 * Indicates existence of the receive correction bypass option; The bypass
 * function allows a reduced latency operation.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_STATUS . RS_FEC_STATUS_BYPASS_CORRECTION
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_STATUS_RS_FEC_STATUS_BYPASS_CORRECTION(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_STATUS_RS_FEC_STATUS_BYPASS_CORRECTION  LAN80XX_BIT(0)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_STATUS_RS_FEC_STATUS_BYPASS_CORRECTION(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Indicates the ability to disable error propagation to the PCS layer.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_STATUS . BYPASS_INDICATION
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_STATUS_BYPASS_INDICATION(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_STATUS_BYPASS_INDICATION  LAN80XX_BIT(1)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_STATUS_BYPASS_INDICATION(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Asserts when error indication bypass is enabled and high symbol error
 * rate is found;
 *  Clear on read.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_STATUS . HIGH_SER
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_STATUS_HIGH_SER(x)  LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_STATUS_HIGH_SER  LAN80XX_BIT(2)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_STATUS_HIGH_SER(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * RS_FEC receive lane locked and aligned; One bit per lane: bit 8 = lane
 * 0, bits 9-11 reserved.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_STATUS . RS_FEC_STATUS_AMPS_LOCK
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_STATUS_RS_FEC_STATUS_AMPS_LOCK(x)  LAN80XX_ENCODE_BITFIELD(x,8,4)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_STATUS_RS_FEC_STATUS_AMPS_LOCK     LAN80XX_ENCODE_BITMASK(8,4)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_STATUS_RS_FEC_STATUS_AMPS_LOCK(x)  LAN80XX_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * Indicates, when 1 that the RS-FEC receiver has locked on incoming data
 * and deskew completed.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_STATUS . FEC_ALIGN_STATUS
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_STATUS_FEC_ALIGN_STATUS(x)  LAN80XX_ENCODE_BITFIELD(!!(x),14,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_STATUS_FEC_ALIGN_STATUS  LAN80XX_BIT(14)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_STATUS_FEC_ALIGN_STATUS(x)  LAN80XX_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Always 1.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_STATUS . PCS_ALIGN_STATUS
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_STATUS_PCS_ALIGN_STATUS(x)  LAN80XX_ENCODE_BITFIELD(!!(x),15,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_STATUS_PCS_ALIGN_STATUS  LAN80XX_BIT(15)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_STATUS_PCS_ALIGN_STATUS(x)  LAN80XX_EXTRACT_BITFIELD(x,15,1)


/**
 * \brief Counts number of corrected FEC codewords lower 16-bits; Non roll-over when upper 16-bits are 0xffff.
 *
 * \details
 * Register: \a LINE_RSFEC:RS_FEC:RS_FEC_CCW_LO
 */
#define LAN80XX_LINE_RSFEC_RS_FEC_CCW_LO        LAN80XX_IOREG(MMD_ID_LINE_RSFEC, 0, 0xca)

/**
 * \brief
 * Counts number of corrected FEC codewords lower 16-bits; Must be read
 * before upper 16-bits; Non roll-over when upper 16-bits are 0xffff. When
 * this register is read bits 31:16 of the internal RS_FEC_CCW counter are
 * latched for reading from RS_FEC_CCW_HI and the entire 32-bit internal
 * RS_FEC_CCW counter is reset
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_CCW_LO . RS_FEC_CCW_LO_COUNTER
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_CCW_LO_RS_FEC_CCW_LO_COUNTER(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_CCW_LO_RS_FEC_CCW_LO_COUNTER     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_CCW_LO_RS_FEC_CCW_LO_COUNTER(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Counts number of corrected FEC codewords upper 16-bits; Clears on read; Non roll-over.
 *
 * \details
 * Register: \a LINE_RSFEC:RS_FEC:RS_FEC_CCW_HI
 */
#define LAN80XX_LINE_RSFEC_RS_FEC_CCW_HI        LAN80XX_IOREG(MMD_ID_LINE_RSFEC, 0, 0xcb)

/**
 * \brief
 * Counts number of corrected FEC codewords upper 16-bits; Non roll-over;
 * When RS_FEC_CCW_LO is read bits 31:16 of the internal RS_FEC_CCW counter
 * are latched for reading from this register and the entire 32-bit
 * internal RS_FEC_CCW counter is reset
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_CCW_HI . RS_FEC_CCW_HI_COUNTER_HI
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_CCW_HI_RS_FEC_CCW_HI_COUNTER_HI(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_CCW_HI_RS_FEC_CCW_HI_COUNTER_HI     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_CCW_HI_RS_FEC_CCW_HI_COUNTER_HI(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Counts number of uncorrected FEC codewords lower 16-bits; Non roll-over when upper 16-bits are 0xffff.
 *
 * \details
 * Register: \a LINE_RSFEC:RS_FEC:RS_FEC_NCCW_LO
 */
#define LAN80XX_LINE_RSFEC_RS_FEC_NCCW_LO       LAN80XX_IOREG(MMD_ID_LINE_RSFEC, 0, 0xcc)

/**
 * \brief
 * Counts number of uncorrected FEC codewords lower 16-bits; Must be read
 * before upper 16-bits; Non roll-over when upper 16-bits are 0xffff. When
 * this register is read bits 31:16 of the internal RS_FEC_NCCW counter are
 * latched for reading from RS_FEC_NCCW_HI and the entire 32-bit internal
 * RS_FEC_NCCW counter is reset
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_NCCW_LO . RS_FEC_NCCW_LO_COUNTER
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_NCCW_LO_RS_FEC_NCCW_LO_COUNTER(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_NCCW_LO_RS_FEC_NCCW_LO_COUNTER     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_NCCW_LO_RS_FEC_NCCW_LO_COUNTER(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Counts number of uncorrected FEC codewords upper 16-bits; Clears on read; Non roll-over.
 *
 * \details
 * Register: \a LINE_RSFEC:RS_FEC:RS_FEC_NCCW_HI
 */
#define LAN80XX_LINE_RSFEC_RS_FEC_NCCW_HI       LAN80XX_IOREG(MMD_ID_LINE_RSFEC, 0, 0xcd)

/**
 * \brief
 * Counts number of uncorrected FEC codewords upper 16-bits; Non roll-over;
 * When RS_FEC_NCCW_LO is read bits 31:16 of the internal RS_FEC_NCCW
 * counter are latched for reading from this register and the entire 32-bit
 * internal RS_FEC_NCCW counter is reset
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_NCCW_HI . RS_FEC_NCCW_HI_COUNTER_HI
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_NCCW_HI_RS_FEC_NCCW_HI_COUNTER_HI(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_NCCW_HI_RS_FEC_NCCW_HI_COUNTER_HI     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_NCCW_HI_RS_FEC_NCCW_HI_COUNTER_HI(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief FEC alignment status and lane mappings.
 *
 * \details
 * Register: \a LINE_RSFEC:RS_FEC:RS_FEC_LANEMAP
 */
#define LAN80XX_LINE_RSFEC_RS_FEC_LANEMAP       LAN80XX_IOREG(MMD_ID_LINE_RSFEC, 0, 0xce)

/**
 * \brief
 * FEC lane mapped to PMA lane 0.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_LANEMAP . PMA_LANE_0
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_LANEMAP_PMA_LANE_0(x)  LAN80XX_ENCODE_BITFIELD(x,0,2)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_LANEMAP_PMA_LANE_0     LAN80XX_ENCODE_BITMASK(0,2)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_LANEMAP_PMA_LANE_0(x)  LAN80XX_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Counts number of (corrected) 10-bit symbol errors found in lane 0; Non roll-over when upper 16-bits are 0xffff.
 *
 * \details
 * Register: \a LINE_RSFEC:RS_FEC:RS_FEC_SYMBLERR0_LO
 */
#define LAN80XX_LINE_RSFEC_RS_FEC_SYMBLERR0_LO  LAN80XX_IOREG(MMD_ID_LINE_RSFEC, 0, 0xd2)

/**
 * \brief
 * Counts number of (corrected) 10-bit symbol errors found in lane 0 for
 * correctable codewords only; Lower 16-bit of counter; Must be read first;
 * Non roll-over when upper word is 0xffff. When this register is read bits
 * 31:16 of the internal RS_FEC_SYMBLERRO counter are latched for reading
 * from RS_FEC_SYMBLERRO_HI and the entire 32-bit internal RS_FEC_SYMBLERRO
 * counter is reset
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_SYMBLERR0_LO . RS_FEC_SYMBLERR0_LO_SYMBOL_ERRORS
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_SYMBLERR0_LO_RS_FEC_SYMBLERR0_LO_SYMBOL_ERRORS(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_SYMBLERR0_LO_RS_FEC_SYMBLERR0_LO_SYMBOL_ERRORS     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_SYMBLERR0_LO_RS_FEC_SYMBLERR0_LO_SYMBOL_ERRORS(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Upper 16-bit of counter (with above register); Clears on read; Non roll-over.
 *
 * \details
 * Register: \a LINE_RSFEC:RS_FEC:RS_FEC_SYMBLERR0_HI
 */
#define LAN80XX_LINE_RSFEC_RS_FEC_SYMBLERR0_HI  LAN80XX_IOREG(MMD_ID_LINE_RSFEC, 0, 0xd3)

/**
 * \brief
 * Upper 16-bits of the 32-bit Symbol error counter for lane 0; Clears on
 * read; Non roll-over. When RS_FEC_SYMBLERRO_LO is read bit 31:16 of
 * internal RS_FEC_SYMBLERRO counter are latched for reading from this
 * register and the entire 32-bit internal RS_FEC_SYMBLERRO counter is
 * reset
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_SYMBLERR0_HI . RS_FEC_SYMBLERR0_HI_SYMBOL_ERROR_HI
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_SYMBLERR0_HI_RS_FEC_SYMBLERR0_HI_SYMBOL_ERROR_HI(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_SYMBLERR0_HI_RS_FEC_SYMBLERR0_HI_SYMBOL_ERROR_HI     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_SYMBLERR0_HI_RS_FEC_SYMBLERR0_HI_SYMBOL_ERROR_HI(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_RSFEC:RS_FEC_VENDOR
 *
 * RS_FEC VENDOR Control and Status Registers; All registers are 16-bit wide.
 */


/**
 * \brief Additional control to enable RS-FEC operation.
 *
 * \details
 * Register: \a LINE_RSFEC:RS_FEC_VENDOR:RS_FEC_VENDOR_CONTROL
 */
#define LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_CONTROL  LAN80XX_IOREG(MMD_ID_LINE_RSFEC, 0, 0x8200)

/**
 * \brief
 * When 1, enable RS-FEC datapath of Channel 0; This is a legacy bit only,
 * ORed with Channel 0 RS_FEC_CONTROL bit 2. Should not be used any more.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_CONTROL . RS_FEC_ENABLE0
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_VENDOR_CONTROL_RS_FEC_ENABLE0(x)  LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_VENDOR_CONTROL_RS_FEC_ENABLE0  LAN80XX_BIT(2)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_VENDOR_CONTROL_RS_FEC_ENABLE0(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Channel 0; When 1 use RS-FEC over single lane 0 (25G); When 0 use RS-FEC
 * over 2 lanes 0,1 (50G). This bit must be kept 1
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_CONTROL . CH0_1LANE_MODE
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_VENDOR_CONTROL_CH0_1LANE_MODE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_VENDOR_CONTROL_CH0_1LANE_MODE  LAN80XX_BIT(3)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_VENDOR_CONTROL_CH0_1LANE_MODE(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Channel 0; When 1 use RS-FEC over single lane 0 (25G) is selected; When
 * 0 use RS-FEC over 2 lanes 0,1 (50G).This bit must be kept 1
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_CONTROL . CH0_1LANE_MODE_SEL
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_VENDOR_CONTROL_CH0_1LANE_MODE_SEL(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_VENDOR_CONTROL_CH0_1LANE_MODE_SEL  LAN80XX_BIT(4)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_VENDOR_CONTROL_CH0_1LANE_MODE_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Indicates per channel if RS-FEC is currently enabled (1) or not (0).
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_CONTROL . CH0_1LANE_MODE_STATUS
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_VENDOR_CONTROL_CH0_1LANE_MODE_STATUS(x)  LAN80XX_ENCODE_BITFIELD(!!(x),13,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_VENDOR_CONTROL_CH0_1LANE_MODE_STATUS  LAN80XX_BIT(13)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_VENDOR_CONTROL_CH0_1LANE_MODE_STATUS(x)  LAN80XX_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Indicates per channel if RS-FEC is currently enabled (1) or not (0).
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_CONTROL . CH0_1LANE_MODE_SEL_STATUS
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_VENDOR_CONTROL_CH0_1LANE_MODE_SEL_STATUS(x)  LAN80XX_ENCODE_BITFIELD(!!(x),14,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_VENDOR_CONTROL_CH0_1LANE_MODE_SEL_STATUS  LAN80XX_BIT(14)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_VENDOR_CONTROL_CH0_1LANE_MODE_SEL_STATUS(x)  LAN80XX_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Indicates per channel if RS-FEC is currently enabled (1) or not (0).
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_CONTROL . RS_FEC_STATUS
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_VENDOR_CONTROL_RS_FEC_STATUS(x)  LAN80XX_ENCODE_BITFIELD(!!(x),15,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_VENDOR_CONTROL_RS_FEC_STATUS  LAN80XX_BIT(15)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_VENDOR_CONTROL_RS_FEC_STATUS(x)  LAN80XX_EXTRACT_BITFIELD(x,15,1)


/**
 * \brief Implementation specific information that may be useful for debugging link problems; Clears on read.
 *
 * \details
 * Register: \a LINE_RSFEC:RS_FEC_VENDOR:RS_FEC_VENDOR_INFO1
 */
#define LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_INFO1  LAN80XX_IOREG(MMD_ID_LINE_RSFEC, 0, 0x8201)

/**
 * \brief
 * Per PMA lane FEC synchronization status; Bit 0=lane 0; Bits 1-3
 * reserved. Latched high; Clear on read.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_INFO1 . RS_FEC_VENDOR_INFO1_AMPS_LOCK
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_VENDOR_INFO1_RS_FEC_VENDOR_INFO1_AMPS_LOCK(x)  LAN80XX_ENCODE_BITFIELD(x,0,4)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_VENDOR_INFO1_RS_FEC_VENDOR_INFO1_AMPS_LOCK     LAN80XX_ENCODE_BITMASK(0,4)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_VENDOR_INFO1_RS_FEC_VENDOR_INFO1_AMPS_LOCK(x)  LAN80XX_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * FEC alignment status; Latched high; Clear on read.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_INFO1 . FEC_ALIGN_STATUS_LH
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_VENDOR_INFO1_FEC_ALIGN_STATUS_LH(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_VENDOR_INFO1_FEC_ALIGN_STATUS_LH  LAN80XX_BIT(4)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_VENDOR_INFO1_FEC_ALIGN_STATUS_LH(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * The marker_check function (PCS sublayer) caused an alignment restart to
 * the FEC; Latched high; Clear on read.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_INFO1 . MARKER_CHECK_RESTART
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_VENDOR_INFO1_MARKER_CHECK_RESTART(x)  LAN80XX_ENCODE_BITFIELD(!!(x),5,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_VENDOR_INFO1_MARKER_CHECK_RESTART  LAN80XX_BIT(5)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_VENDOR_INFO1_MARKER_CHECK_RESTART(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RX datapath (sync) reset occured; Latched high; Clear on read.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_INFO1 . RX_DATAPATH_RESTART
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_VENDOR_INFO1_RX_DATAPATH_RESTART(x)  LAN80XX_ENCODE_BITFIELD(!!(x),6,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_VENDOR_INFO1_RX_DATAPATH_RESTART  LAN80XX_BIT(6)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_VENDOR_INFO1_RX_DATAPATH_RESTART(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * TX datapath (sync) reset occured; Latched high; Clear on read.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_INFO1 . TX_DATAPATH_RESTART
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_VENDOR_INFO1_TX_DATAPATH_RESTART(x)  LAN80XX_ENCODE_BITFIELD(!!(x),7,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_VENDOR_INFO1_TX_DATAPATH_RESTART  LAN80XX_BIT(7)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_VENDOR_INFO1_TX_DATAPATH_RESTART(x)  LAN80XX_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * RX datapath 4x66 pacing fifo overflow fatal error; Latched high; Clear
 * on read.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_INFO1 . RX_DP_OVERFLOW
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_VENDOR_INFO1_RX_DP_OVERFLOW(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_VENDOR_INFO1_RX_DP_OVERFLOW  LAN80XX_BIT(8)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_VENDOR_INFO1_RX_DP_OVERFLOW(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * TX datapath 4x66 input fifo overflow fatal error; Latched high; Clear on
 * read.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_INFO1 . TX_DP_OVERFLOW
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_VENDOR_INFO1_TX_DP_OVERFLOW(x)  LAN80XX_ENCODE_BITFIELD(!!(x),9,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_VENDOR_INFO1_TX_DP_OVERFLOW  LAN80XX_BIT(9)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_VENDOR_INFO1_TX_DP_OVERFLOW(x)  LAN80XX_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * FEC alignment status; Latched high; Sets on read.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_INFO1 . FEC_ALIGN_STATUS_LL
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_VENDOR_INFO1_FEC_ALIGN_STATUS_LL(x)  LAN80XX_ENCODE_BITFIELD(!!(x),10,1)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_VENDOR_INFO1_FEC_ALIGN_STATUS_LL  LAN80XX_BIT(10)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_VENDOR_INFO1_FEC_ALIGN_STATUS_LL(x)  LAN80XX_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * reserved, unused.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_INFO1 . DESKEW_EMPTY
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_VENDOR_INFO1_DESKEW_EMPTY(x)  LAN80XX_ENCODE_BITFIELD(x,12,4)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_VENDOR_INFO1_DESKEW_EMPTY     LAN80XX_ENCODE_BITMASK(12,4)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_VENDOR_INFO1_DESKEW_EMPTY(x)  LAN80XX_EXTRACT_BITFIELD(x,12,4)


/**
 * \brief Implementation specific status information; Clears on read.
 *
 * \details
 * Register: \a LINE_RSFEC:RS_FEC_VENDOR:RS_FEC_VENDOR_INFO2
 */
#define LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_INFO2  LAN80XX_IOREG(MMD_ID_LINE_RSFEC, 0, 0x8202)

/**
 * \brief
 * Per PMA lane FEC synchronization status; Realtime updates;
 *  Bit 0 = lane 0; Bits 1-3 reserved;
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_INFO2 . RS_FEC_VENDOR_INFO2_AMPS_LOCK
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_VENDOR_INFO2_RS_FEC_VENDOR_INFO2_AMPS_LOCK(x)  LAN80XX_ENCODE_BITFIELD(x,0,4)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_VENDOR_INFO2_RS_FEC_VENDOR_INFO2_AMPS_LOCK     LAN80XX_ENCODE_BITMASK(0,4)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_VENDOR_INFO2_RS_FEC_VENDOR_INFO2_AMPS_LOCK(x)  LAN80XX_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * RSFEC decoder internal error; Latched-high; Bits 5-7 reserved.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_INFO2 . RS_DECODER_WRITE_ERR
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_VENDOR_INFO2_RS_DECODER_WRITE_ERR(x)  LAN80XX_ENCODE_BITFIELD(x,4,4)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_VENDOR_INFO2_RS_DECODER_WRITE_ERR     LAN80XX_ENCODE_BITMASK(4,4)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_VENDOR_INFO2_RS_DECODER_WRITE_ERR(x)  LAN80XX_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief version information
 *
 * \details
 * Register: \a LINE_RSFEC:RS_FEC_VENDOR:RS_FEC_VENDOR_REVISION
 */
#define LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_REVISION  LAN80XX_IOREG(MMD_ID_LINE_RSFEC, 0, 0x8203)

/**
 * \brief
 * version information.
 *
 * \details
 * Field: ::LAN80XX_LINE_RSFEC_RS_FEC_VENDOR_REVISION . REVISION
 */
#define  LAN80XX_F_LINE_RSFEC_RS_FEC_VENDOR_REVISION_REVISION(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_LINE_RSFEC_RS_FEC_VENDOR_REVISION_REVISION     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_LINE_RSFEC_RS_FEC_VENDOR_REVISION_REVISION(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


#endif /* _LAN80XX_MALIBU25G_REGS_LINE_RSFEC_H_ */
