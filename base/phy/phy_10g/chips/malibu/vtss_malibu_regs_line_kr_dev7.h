// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU_REGS_LINE_KR_DEV7_H_
#define _VTSS_MALIBU_REGS_LINE_KR_DEV7_H_


#include "vtss_malibu_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a LINE_KR_DEV7
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a LINE_KR_DEV7:KR_7x0000
 *
 * Not documented
 */


/** 
 * \brief AN control
 *
 * \details
 * Register: \a LINE_KR_DEV7:KR_7x0000:KR_7x0000
 */
#define VTSS_LINE_KR_DEV7_KR_7x0000_KR_7x0000  VTSS_IOREG(0x07, 0, 0x0000)

/** 
 * \brief
 * AN reset   (SC)
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_KR_7x0000_KR_7x0000 . an_reset
 */
#define  VTSS_F_LINE_KR_DEV7_KR_7x0000_KR_7x0000_an_reset  VTSS_BIT(15)

/** 
 * \brief
 * Extended next page control
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_KR_7x0000_KR_7x0000 . npctl
 */
#define  VTSS_F_LINE_KR_DEV7_KR_7x0000_KR_7x0000_npctl  VTSS_BIT(13)

/** 
 * \brief
 * AN enable
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_KR_7x0000_KR_7x0000 . an_enable
 */
#define  VTSS_F_LINE_KR_DEV7_KR_7x0000_KR_7x0000_an_enable  VTSS_BIT(12)

/** 
 * \brief
 * AN restart (SC)
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_KR_7x0000_KR_7x0000 . an_restart
 */
#define  VTSS_F_LINE_KR_DEV7_KR_7x0000_KR_7x0000_an_restart  VTSS_BIT(9)

/**
 * Register Group: \a LINE_KR_DEV7:KR_7x0001
 *
 * Not documented
 */


/** 
 * \brief AN status
 *
 * \details
 * Register: \a LINE_KR_DEV7:KR_7x0001:KR_7x0001
 */
#define VTSS_LINE_KR_DEV7_KR_7x0001_KR_7x0001  VTSS_IOREG(0x07, 0, 0x0001)

/** 
 * \brief
 * Parallel detection fault (LH)
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_KR_7x0001_KR_7x0001 . pardetflt
 */
#define  VTSS_F_LINE_KR_DEV7_KR_7x0001_KR_7x0001_pardetflt  VTSS_BIT(9)

/** 
 * \brief
 * Extended next page status
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_KR_7x0001_KR_7x0001 . npstat
 */
#define  VTSS_F_LINE_KR_DEV7_KR_7x0001_KR_7x0001_npstat  VTSS_BIT(7)

/** 
 * \brief
 * Page received (LH)
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_KR_7x0001_KR_7x0001 . pg_rcvd
 */
#define  VTSS_F_LINE_KR_DEV7_KR_7x0001_KR_7x0001_pg_rcvd  VTSS_BIT(6)

/** 
 * \brief
 * AN complete
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_KR_7x0001_KR_7x0001 . an_complete
 */
#define  VTSS_F_LINE_KR_DEV7_KR_7x0001_KR_7x0001_an_complete  VTSS_BIT(5)

/** 
 * \brief
 * Remote fault (LH)
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_KR_7x0001_KR_7x0001 . rem_flt
 */
#define  VTSS_F_LINE_KR_DEV7_KR_7x0001_KR_7x0001_rem_flt  VTSS_BIT(4)

/** 
 * \brief
 * AN ability
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_KR_7x0001_KR_7x0001 . an_able
 */
#define  VTSS_F_LINE_KR_DEV7_KR_7x0001_KR_7x0001_an_able  VTSS_BIT(3)

/** 
 * \brief
 * Link status (LL)
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_KR_7x0001_KR_7x0001 . linkstat
 */
#define  VTSS_F_LINE_KR_DEV7_KR_7x0001_KR_7x0001_linkstat  VTSS_BIT(2)

/** 
 * \brief
 * LP AN ability
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_KR_7x0001_KR_7x0001 . an_lp_able
 */
#define  VTSS_F_LINE_KR_DEV7_KR_7x0001_KR_7x0001_an_lp_able  VTSS_BIT(0)

/**
 * Register Group: \a LINE_KR_DEV7:LD_adv
 *
 * Not documented
 */


/** 
 * \brief LD advertised abilities 15-0
 *
 * \details
 * Register: \a LINE_KR_DEV7:LD_adv:KR_7x0010
 */
#define VTSS_LINE_KR_DEV7_LD_adv_KR_7x0010   VTSS_IOREG(0x07, 0, 0x0010)

/** 
 * \brief
 * Local advertised abilities D[15:0]
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_LD_adv_KR_7x0010 . adv0
 */
#define  VTSS_F_LINE_KR_DEV7_LD_adv_KR_7x0010_adv0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_LD_adv_KR_7x0010_adv0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_LD_adv_KR_7x0010_adv0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief LD advertised abilities 31-16
 *
 * \details
 * Register: \a LINE_KR_DEV7:LD_adv:KR_7x0011
 */
#define VTSS_LINE_KR_DEV7_LD_adv_KR_7x0011   VTSS_IOREG(0x07, 0, 0x0011)

/** 
 * \brief
 * Local advertised abilities D[31:16]
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_LD_adv_KR_7x0011 . adv1
 */
#define  VTSS_F_LINE_KR_DEV7_LD_adv_KR_7x0011_adv1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_LD_adv_KR_7x0011_adv1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_LD_adv_KR_7x0011_adv1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief LD advertised abilities 47-32
 *
 * \details
 * Register: \a LINE_KR_DEV7:LD_adv:KR_7x0012
 */
#define VTSS_LINE_KR_DEV7_LD_adv_KR_7x0012   VTSS_IOREG(0x07, 0, 0x0012)

/** 
 * \brief
 * Local advertised abilities D[47:32]
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_LD_adv_KR_7x0012 . adv2
 */
#define  VTSS_F_LINE_KR_DEV7_LD_adv_KR_7x0012_adv2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_LD_adv_KR_7x0012_adv2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_LD_adv_KR_7x0012_adv2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_KR_DEV7:LP_base_page_0
 *
 * Not documented
 */


/** 
 * \brief LP base page advertised abilities 15-0
 *
 * \details
 * Register: \a LINE_KR_DEV7:LP_base_page_0:KR_7x0013
 */
#define VTSS_LINE_KR_DEV7_LP_base_page_0_KR_7x0013  VTSS_IOREG(0x07, 0, 0x0013)

/** 
 * \brief
 * LP advertised abilities D[15:0]
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_LP_base_page_0_KR_7x0013 . lp_bp_adv0
 */
#define  VTSS_F_LINE_KR_DEV7_LP_base_page_0_KR_7x0013_lp_bp_adv0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_LP_base_page_0_KR_7x0013_lp_bp_adv0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_LP_base_page_0_KR_7x0013_lp_bp_adv0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_KR_DEV7:LP_base_page_1
 *
 * Not documented
 */


/** 
 * \brief LP base page advertised abilities 31-16
 *
 * \details
 * Register: \a LINE_KR_DEV7:LP_base_page_1:KR_7x0014
 */
#define VTSS_LINE_KR_DEV7_LP_base_page_1_KR_7x0014  VTSS_IOREG(0x07, 0, 0x0014)

/** 
 * \brief
 * LP advertised abilities D[31:16]
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_LP_base_page_1_KR_7x0014 . lp_bp_adv1
 */
#define  VTSS_F_LINE_KR_DEV7_LP_base_page_1_KR_7x0014_lp_bp_adv1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_LP_base_page_1_KR_7x0014_lp_bp_adv1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_LP_base_page_1_KR_7x0014_lp_bp_adv1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_KR_DEV7:LP_base_page_2
 *
 * Not documented
 */


/** 
 * \brief LP base page advertised abilities 47-32
 *
 * \details
 * Register: \a LINE_KR_DEV7:LP_base_page_2:KR_7x0015
 */
#define VTSS_LINE_KR_DEV7_LP_base_page_2_KR_7x0015  VTSS_IOREG(0x07, 0, 0x0015)

/** 
 * \brief
 * LP advertised abilities D[47:32]
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_LP_base_page_2_KR_7x0015 . lp_bp_adv2
 */
#define  VTSS_F_LINE_KR_DEV7_LP_base_page_2_KR_7x0015_lp_bp_adv2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_LP_base_page_2_KR_7x0015_lp_bp_adv2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_LP_base_page_2_KR_7x0015_lp_bp_adv2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_KR_DEV7:LD_next_page
 *
 * Not documented
 */


/** 
 * \brief NxtPg transmit 15-0
 *
 * \details
 * Register: \a LINE_KR_DEV7:LD_next_page:KR_7x0016
 */
#define VTSS_LINE_KR_DEV7_LD_next_page_KR_7x0016  VTSS_IOREG(0x07, 0, 0x0016)

/** 
 * \brief
 * Next page to transmit D[15:0]
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_LD_next_page_KR_7x0016 . np_tx0
 */
#define  VTSS_F_LINE_KR_DEV7_LD_next_page_KR_7x0016_np_tx0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_LD_next_page_KR_7x0016_np_tx0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_LD_next_page_KR_7x0016_np_tx0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief NxtPg transmit 31-16
 *
 * \details
 * Register: \a LINE_KR_DEV7:LD_next_page:KR_7x0017
 */
#define VTSS_LINE_KR_DEV7_LD_next_page_KR_7x0017  VTSS_IOREG(0x07, 0, 0x0017)

/** 
 * \brief
 * Next page to transmit D[31:16]
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_LD_next_page_KR_7x0017 . np_tx1
 */
#define  VTSS_F_LINE_KR_DEV7_LD_next_page_KR_7x0017_np_tx1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_LD_next_page_KR_7x0017_np_tx1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_LD_next_page_KR_7x0017_np_tx1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief NxtPg transmit 47-32
 *
 * \details
 * Register: \a LINE_KR_DEV7:LD_next_page:KR_7x0018
 */
#define VTSS_LINE_KR_DEV7_LD_next_page_KR_7x0018  VTSS_IOREG(0x07, 0, 0x0018)

/** 
 * \brief
 * Next page to transmit D[47:32]
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_LD_next_page_KR_7x0018 . np_tx2
 */
#define  VTSS_F_LINE_KR_DEV7_LD_next_page_KR_7x0018_np_tx2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_LD_next_page_KR_7x0018_np_tx2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_LD_next_page_KR_7x0018_np_tx2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_KR_DEV7:LP_next_page
 *
 * Not documented
 */


/** 
 * \brief LP next page ability 15-0
 *
 * \details
 * Register: \a LINE_KR_DEV7:LP_next_page:KR_7x0019
 */
#define VTSS_LINE_KR_DEV7_LP_next_page_KR_7x0019  VTSS_IOREG(0x07, 0, 0x0019)

/** 
 * \brief
 * LP next page  ability D[15:0]
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_LP_next_page_KR_7x0019 . lp_np_adv0
 */
#define  VTSS_F_LINE_KR_DEV7_LP_next_page_KR_7x0019_lp_np_adv0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_LP_next_page_KR_7x0019_lp_np_adv0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_LP_next_page_KR_7x0019_lp_np_adv0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief LP next page ability 31-16
 *
 * \details
 * Register: \a LINE_KR_DEV7:LP_next_page:KR_7x001A
 */
#define VTSS_LINE_KR_DEV7_LP_next_page_KR_7x001A  VTSS_IOREG(0x07, 0, 0x001a)

/** 
 * \brief
 * LP next page ability D[31:16]
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_LP_next_page_KR_7x001A . lp_np_adv1
 */
#define  VTSS_F_LINE_KR_DEV7_LP_next_page_KR_7x001A_lp_np_adv1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_LP_next_page_KR_7x001A_lp_np_adv1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_LP_next_page_KR_7x001A_lp_np_adv1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief LP next page ability 47-32
 *
 * \details
 * Register: \a LINE_KR_DEV7:LP_next_page:KR_7x001B
 */
#define VTSS_LINE_KR_DEV7_LP_next_page_KR_7x001B  VTSS_IOREG(0x07, 0, 0x001b)

/** 
 * \brief
 * LP next page ability D[47:32]
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_LP_next_page_KR_7x001B . lp_np_adv2
 */
#define  VTSS_F_LINE_KR_DEV7_LP_next_page_KR_7x001B_lp_np_adv2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_LP_next_page_KR_7x001B_lp_np_adv2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_LP_next_page_KR_7x001B_lp_np_adv2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_KR_DEV7:KR_7x0030
 *
 * Not documented
 */


/** 
 * \brief Backplane ethernet status
 *
 * \details
 * Register: \a LINE_KR_DEV7:KR_7x0030:KR_7x0030
 */
#define VTSS_LINE_KR_DEV7_KR_7x0030_KR_7x0030  VTSS_IOREG(0x07, 0, 0x0030)

/** 
 * \brief
 * 10G CR10   negotiated
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_KR_7x0030_KR_7x0030 . an_neg_cr10
 */
#define  VTSS_F_LINE_KR_DEV7_KR_7x0030_KR_7x0030_an_neg_cr10  VTSS_BIT(8)

/** 
 * \brief
 * 10G CR4    negotiated
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_KR_7x0030_KR_7x0030 . an_neg_cr4
 */
#define  VTSS_F_LINE_KR_DEV7_KR_7x0030_KR_7x0030_an_neg_cr4  VTSS_BIT(6)

/** 
 * \brief
 * 10G KR4    negotiated
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_KR_7x0030_KR_7x0030 . an_neg_kr4
 */
#define  VTSS_F_LINE_KR_DEV7_KR_7x0030_KR_7x0030_an_neg_kr4  VTSS_BIT(5)

/** 
 * \brief
 * 10G KR FEC negotiated
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_KR_7x0030_KR_7x0030 . an_neg_fec
 */
#define  VTSS_F_LINE_KR_DEV7_KR_7x0030_KR_7x0030_an_neg_fec  VTSS_BIT(4)

/** 
 * \brief
 * 10G KR     negotiated
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_KR_7x0030_KR_7x0030 . an_neg_kr
 */
#define  VTSS_F_LINE_KR_DEV7_KR_7x0030_KR_7x0030_an_neg_kr  VTSS_BIT(3)

/** 
 * \brief
 * 10G KX4    negotiated
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_KR_7x0030_KR_7x0030 . an_neg_kx4
 */
#define  VTSS_F_LINE_KR_DEV7_KR_7x0030_KR_7x0030_an_neg_kx4  VTSS_BIT(2)

/** 
 * \brief
 * 1G  KX     negotiated
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_KR_7x0030_KR_7x0030 . an_neg_kx
 */
#define  VTSS_F_LINE_KR_DEV7_KR_7x0030_KR_7x0030_an_neg_kx  VTSS_BIT(1)

/** 
 * \brief
 * BP AN ability
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_KR_7x0030_KR_7x0030 . an_bp_able
 */
#define  VTSS_F_LINE_KR_DEV7_KR_7x0030_KR_7x0030_an_bp_able  VTSS_BIT(0)

/**
 * Register Group: \a LINE_KR_DEV7:an_cfg0
 *
 * Not documented
 */


/** 
 * \brief VS AN config 0
 *
 * \details
 * Register: \a LINE_KR_DEV7:an_cfg0:an_cfg0
 */
#define VTSS_LINE_KR_DEV7_an_cfg0_an_cfg0    VTSS_IOREG(0x07, 0, 0x8000)

/** 
 * \brief
 * Clear AN state machine history
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_an_cfg0_an_cfg0 . an_sm_hist_clr
 */
#define  VTSS_F_LINE_KR_DEV7_an_cfg0_an_cfg0_an_sm_hist_clr  VTSS_BIT(5)

/** 
 * \brief
 * Disable clock gating
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_an_cfg0_an_cfg0 . clkg_disable
 */
#define  VTSS_F_LINE_KR_DEV7_an_cfg0_an_cfg0_clkg_disable  VTSS_BIT(4)

/** 
 * \brief
 * Bypass training if 10G negotiated
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_an_cfg0_an_cfg0 . tr_disable
 */
#define  VTSS_F_LINE_KR_DEV7_an_cfg0_an_cfg0_tr_disable  VTSS_BIT(3)

/** 
 * \brief
 * Select source of 10G sync signal   
 *
 * \details 
 * 0: KR internal 
 * 1: External
 *
 * Field: VTSS_LINE_KR_DEV7_an_cfg0_an_cfg0 . sync10g_sel
 */
#define  VTSS_F_LINE_KR_DEV7_an_cfg0_an_cfg0_sync10g_sel  VTSS_BIT(2)

/** 
 * \brief
 * Select source of 3G and 1G sync signal 
 *
 * \details 
 * 0: KR internal 
 * 1: External
 *
 * Field: VTSS_LINE_KR_DEV7_an_cfg0_an_cfg0 . sync8b10b_sel
 */
#define  VTSS_F_LINE_KR_DEV7_an_cfg0_an_cfg0_sync8b10b_sel  VTSS_BIT(1)

/**
 * Register Group: \a LINE_KR_DEV7:bl_tmr
 *
 * Not documented
 */


/** 
 * \brief VS AN break_link timer lsw
 *
 * \details
 * Register: \a LINE_KR_DEV7:bl_tmr:bl_lsw
 */
#define VTSS_LINE_KR_DEV7_bl_tmr_bl_lsw      VTSS_IOREG(0x07, 0, 0x8010)

/** 
 * \brief
 * break_link_timer setting
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_bl_tmr_bl_lsw . bl_tmr_lsw
 */
#define  VTSS_F_LINE_KR_DEV7_bl_tmr_bl_lsw_bl_tmr_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_bl_tmr_bl_lsw_bl_tmr_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_bl_tmr_bl_lsw_bl_tmr_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS AN break_link timer msw
 *
 * \details
 * Register: \a LINE_KR_DEV7:bl_tmr:bl_msw
 */
#define VTSS_LINE_KR_DEV7_bl_tmr_bl_msw      VTSS_IOREG(0x07, 0, 0x8011)

/** 
 * \brief
 * break_link_timer setting
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_bl_tmr_bl_msw . bl_tmr_msw
 */
#define  VTSS_F_LINE_KR_DEV7_bl_tmr_bl_msw_bl_tmr_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_bl_tmr_bl_msw_bl_tmr_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_bl_tmr_bl_msw_bl_tmr_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_KR_DEV7:aw_tmr
 *
 * Not documented
 */


/** 
 * \brief VS AN aneg_wait timer lsw
 *
 * \details
 * Register: \a LINE_KR_DEV7:aw_tmr:aw_lsw
 */
#define VTSS_LINE_KR_DEV7_aw_tmr_aw_lsw      VTSS_IOREG(0x07, 0, 0x8020)

/** 
 * \brief
 * an_wait_timer setting
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_aw_tmr_aw_lsw . aw_tmr_lsw
 */
#define  VTSS_F_LINE_KR_DEV7_aw_tmr_aw_lsw_aw_tmr_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_aw_tmr_aw_lsw_aw_tmr_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_aw_tmr_aw_lsw_aw_tmr_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS AN aneg_wait timer msw
 *
 * \details
 * Register: \a LINE_KR_DEV7:aw_tmr:aw_msw
 */
#define VTSS_LINE_KR_DEV7_aw_tmr_aw_msw      VTSS_IOREG(0x07, 0, 0x8021)

/** 
 * \brief
 * an_wait_timer setting
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_aw_tmr_aw_msw . aw_tmr_msw
 */
#define  VTSS_F_LINE_KR_DEV7_aw_tmr_aw_msw_aw_tmr_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_aw_tmr_aw_msw_aw_tmr_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_aw_tmr_aw_msw_aw_tmr_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_KR_DEV7:lflong_tmr
 *
 * Not documented
 */


/** 
 * \brief VS AN link_fail_inhibit timer lsw
 *
 * \details
 * Register: \a LINE_KR_DEV7:lflong_tmr:lflong_lsw
 */
#define VTSS_LINE_KR_DEV7_lflong_tmr_lflong_lsw  VTSS_IOREG(0x07, 0, 0x8030)

/** 
 * \brief
 * 10g link_fail_inhibit_timer setting
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_lflong_tmr_lflong_lsw . lflong_tmr_lsw
 */
#define  VTSS_F_LINE_KR_DEV7_lflong_tmr_lflong_lsw_lflong_tmr_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_lflong_tmr_lflong_lsw_lflong_tmr_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_lflong_tmr_lflong_lsw_lflong_tmr_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS AN link_fail_inhibit_long timer msw
 *
 * \details
 * Register: \a LINE_KR_DEV7:lflong_tmr:lflong_msw
 */
#define VTSS_LINE_KR_DEV7_lflong_tmr_lflong_msw  VTSS_IOREG(0x07, 0, 0x8031)

/** 
 * \brief
 * 10g link_fail_inhibit_timer setting
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_lflong_tmr_lflong_msw . lflong_tmr_msw
 */
#define  VTSS_F_LINE_KR_DEV7_lflong_tmr_lflong_msw_lflong_tmr_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_lflong_tmr_lflong_msw_lflong_tmr_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_lflong_tmr_lflong_msw_lflong_tmr_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_KR_DEV7:lfshort_tmr
 *
 * Not documented
 */


/** 
 * \brief VS AN link_fail_inhibit_short timer lsw
 *
 * \details
 * Register: \a LINE_KR_DEV7:lfshort_tmr:lfshort_lsw
 */
#define VTSS_LINE_KR_DEV7_lfshort_tmr_lfshort_lsw  VTSS_IOREG(0x07, 0, 0x8040)

/** 
 * \brief
 * 1g link_fail_inhibit_timer setting
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_lfshort_tmr_lfshort_lsw . lfshort_tmr_lsw
 */
#define  VTSS_F_LINE_KR_DEV7_lfshort_tmr_lfshort_lsw_lfshort_tmr_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_lfshort_tmr_lfshort_lsw_lfshort_tmr_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_lfshort_tmr_lfshort_lsw_lfshort_tmr_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS AN link_fail_inhibit_short timer msw
 *
 * \details
 * Register: \a LINE_KR_DEV7:lfshort_tmr:lfshort_msw
 */
#define VTSS_LINE_KR_DEV7_lfshort_tmr_lfshort_msw  VTSS_IOREG(0x07, 0, 0x8041)

/** 
 * \brief
 * 1g link_fail_inhibit_timer setting
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_lfshort_tmr_lfshort_msw . lfshort_tmr_msw
 */
#define  VTSS_F_LINE_KR_DEV7_lfshort_tmr_lfshort_msw_lfshort_tmr_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_lfshort_tmr_lfshort_msw_lfshort_tmr_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_lfshort_tmr_lfshort_msw_lfshort_tmr_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_KR_DEV7:lp_tmr
 *
 * Not documented
 */


/** 
 * \brief VS AN link_pass_inhibit timer lsw
 *
 * \details
 * Register: \a LINE_KR_DEV7:lp_tmr:lp_lsw
 */
#define VTSS_LINE_KR_DEV7_lp_tmr_lp_lsw      VTSS_IOREG(0x07, 0, 0x8042)

/** 
 * \brief
 * link_pass_inhibit_timer setting
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_lp_tmr_lp_lsw . lp_tmr_lsw
 */
#define  VTSS_F_LINE_KR_DEV7_lp_tmr_lp_lsw_lp_tmr_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_lp_tmr_lp_lsw_lp_tmr_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_lp_tmr_lp_lsw_lp_tmr_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS AN link_pass_inhibit timer msw
 *
 * \details
 * Register: \a LINE_KR_DEV7:lp_tmr:lp_msw
 */
#define VTSS_LINE_KR_DEV7_lp_tmr_lp_msw      VTSS_IOREG(0x07, 0, 0x8043)

/** 
 * \brief
 * link_pass_inhibit_timer setting
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_lp_tmr_lp_msw . lp_tmr_msw
 */
#define  VTSS_F_LINE_KR_DEV7_lp_tmr_lp_msw_lp_tmr_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_lp_tmr_lp_msw_lp_tmr_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_lp_tmr_lp_msw_lp_tmr_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_KR_DEV7:tr_tmr
 *
 * Not documented
 */


/** 
 * \brief VS AN training state timer lsw
 *
 * \details
 * Register: \a LINE_KR_DEV7:tr_tmr:tr_lsw
 */
#define VTSS_LINE_KR_DEV7_tr_tmr_tr_lsw      VTSS_IOREG(0x07, 0, 0x8044)

/** 
 * \brief
 * training_state_timer setting
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_tr_tmr_tr_lsw . tr_tmr_lsw
 */
#define  VTSS_F_LINE_KR_DEV7_tr_tmr_tr_lsw_tr_tmr_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_tr_tmr_tr_lsw_tr_tmr_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_tr_tmr_tr_lsw_tr_tmr_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS AN training state timer msw
 *
 * \details
 * Register: \a LINE_KR_DEV7:tr_tmr:tr_msw
 */
#define VTSS_LINE_KR_DEV7_tr_tmr_tr_msw      VTSS_IOREG(0x07, 0, 0x8045)

/** 
 * \brief
 * training_state_timer setting
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_tr_tmr_tr_msw . tr_tmr_msw
 */
#define  VTSS_F_LINE_KR_DEV7_tr_tmr_tr_msw_tr_tmr_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_tr_tmr_tr_msw_tr_tmr_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_tr_tmr_tr_msw_tr_tmr_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_KR_DEV7:pd_tmr
 *
 * Not documented
 */


/** 
 * \brief VS AN page_detect timer lsw
 *
 * \details
 * Register: \a LINE_KR_DEV7:pd_tmr:pd_lsw
 */
#define VTSS_LINE_KR_DEV7_pd_tmr_pd_lsw      VTSS_IOREG(0x07, 0, 0x8050)

/** 
 * \brief
 * page_detect_timer setting
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_pd_tmr_pd_lsw . pd_tmr_lsw
 */
#define  VTSS_F_LINE_KR_DEV7_pd_tmr_pd_lsw_pd_tmr_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_pd_tmr_pd_lsw_pd_tmr_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_pd_tmr_pd_lsw_pd_tmr_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS AN page_detect timer msw
 *
 * \details
 * Register: \a LINE_KR_DEV7:pd_tmr:pd_msw
 */
#define VTSS_LINE_KR_DEV7_pd_tmr_pd_msw      VTSS_IOREG(0x07, 0, 0x8051)

/** 
 * \brief
 * page_detect_timer setting
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_pd_tmr_pd_msw . pd_tmr_msw
 */
#define  VTSS_F_LINE_KR_DEV7_pd_tmr_pd_msw_pd_tmr_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_pd_tmr_pd_msw_pd_tmr_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_pd_tmr_pd_msw_pd_tmr_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_KR_DEV7:kr10g_tmr
 *
 * Not documented
 */


/** 
 * \brief VS AN rate_detect_10g timer lsw
 *
 * \details
 * Register: \a LINE_KR_DEV7:kr10g_tmr:kr10g_lsw
 */
#define VTSS_LINE_KR_DEV7_kr10g_tmr_kr10g_lsw  VTSS_IOREG(0x07, 0, 0x8060)

/** 
 * \brief
 * rate_detect_10g_timer setting
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_kr10g_tmr_kr10g_lsw . kr10g_tmr_lsw
 */
#define  VTSS_F_LINE_KR_DEV7_kr10g_tmr_kr10g_lsw_kr10g_tmr_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_kr10g_tmr_kr10g_lsw_kr10g_tmr_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_kr10g_tmr_kr10g_lsw_kr10g_tmr_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS AN rate_detect_10g timer msw
 *
 * \details
 * Register: \a LINE_KR_DEV7:kr10g_tmr:kr10g_msw
 */
#define VTSS_LINE_KR_DEV7_kr10g_tmr_kr10g_msw  VTSS_IOREG(0x07, 0, 0x8061)

/** 
 * \brief
 * rate_detect_10g_timer setting
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_kr10g_tmr_kr10g_msw . kr10g_tmr_msw
 */
#define  VTSS_F_LINE_KR_DEV7_kr10g_tmr_kr10g_msw_kr10g_tmr_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_kr10g_tmr_kr10g_msw_kr10g_tmr_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_kr10g_tmr_kr10g_msw_kr10g_tmr_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_KR_DEV7:kr3g_tmr
 *
 * Not documented
 */


/** 
 * \brief VS AN rate_detect_3g timer lsw
 *
 * \details
 * Register: \a LINE_KR_DEV7:kr3g_tmr:kr3g_lsw
 */
#define VTSS_LINE_KR_DEV7_kr3g_tmr_kr3g_lsw  VTSS_IOREG(0x07, 0, 0x8070)

/** 
 * \brief
 * rate_detect_3g_timer setting
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_kr3g_tmr_kr3g_lsw . kr3g_tmr_lsw
 */
#define  VTSS_F_LINE_KR_DEV7_kr3g_tmr_kr3g_lsw_kr3g_tmr_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_kr3g_tmr_kr3g_lsw_kr3g_tmr_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_kr3g_tmr_kr3g_lsw_kr3g_tmr_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS AN rate_detect_3g timer msw
 *
 * \details
 * Register: \a LINE_KR_DEV7:kr3g_tmr:kr3g_msw
 */
#define VTSS_LINE_KR_DEV7_kr3g_tmr_kr3g_msw  VTSS_IOREG(0x07, 0, 0x8071)

/** 
 * \brief
 * rate_detect_3g_timer setting
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_kr3g_tmr_kr3g_msw . kr3g_tmr_msw
 */
#define  VTSS_F_LINE_KR_DEV7_kr3g_tmr_kr3g_msw_kr3g_tmr_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_kr3g_tmr_kr3g_msw_kr3g_tmr_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_kr3g_tmr_kr3g_msw_kr3g_tmr_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_KR_DEV7:kr1g_tmr
 *
 * Not documented
 */


/** 
 * \brief VS AN rate_detect_1g timer lsw
 *
 * \details
 * Register: \a LINE_KR_DEV7:kr1g_tmr:kr1g_lsw
 */
#define VTSS_LINE_KR_DEV7_kr1g_tmr_kr1g_lsw  VTSS_IOREG(0x07, 0, 0x8080)

/** 
 * \brief
 * rate_detect_1g_timer setting
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_kr1g_tmr_kr1g_lsw . kr1g_tmr_lsw
 */
#define  VTSS_F_LINE_KR_DEV7_kr1g_tmr_kr1g_lsw_kr1g_tmr_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_kr1g_tmr_kr1g_lsw_kr1g_tmr_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_kr1g_tmr_kr1g_lsw_kr1g_tmr_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS AN rate_detect_1g timer msw
 *
 * \details
 * Register: \a LINE_KR_DEV7:kr1g_tmr:kr1g_msw
 */
#define VTSS_LINE_KR_DEV7_kr1g_tmr_kr1g_msw  VTSS_IOREG(0x07, 0, 0x8081)

/** 
 * \brief
 * rate_detect_1g_timer setting
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_kr1g_tmr_kr1g_msw . kr1g_tmr_msw
 */
#define  VTSS_F_LINE_KR_DEV7_kr1g_tmr_kr1g_msw_kr1g_tmr_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_KR_DEV7_kr1g_tmr_kr1g_msw_kr1g_tmr_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_KR_DEV7_kr1g_tmr_kr1g_msw_kr1g_tmr_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_KR_DEV7:an_hist
 *
 * Not documented
 */


/** 
 * \brief VS AN arb state mach history
 *
 * \details
 * Register: \a LINE_KR_DEV7:an_hist:an_hist
 */
#define VTSS_LINE_KR_DEV7_an_hist_an_hist    VTSS_IOREG(0x07, 0, 0x8090)

/** 
 * \brief
 * AN state machine history
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_an_hist_an_hist . an_sm_hist
 */
#define  VTSS_F_LINE_KR_DEV7_an_hist_an_hist_an_sm_hist(x)  VTSS_ENCODE_BITFIELD(x,0,15)
#define  VTSS_M_LINE_KR_DEV7_an_hist_an_hist_an_sm_hist     VTSS_ENCODE_BITMASK(0,15)
#define  VTSS_X_LINE_KR_DEV7_an_hist_an_hist_an_sm_hist(x)  VTSS_EXTRACT_BITFIELD(x,0,15)

/**
 * Register Group: \a LINE_KR_DEV7:an_sm
 *
 * Not documented
 */


/** 
 * \brief VS AN arb state machine
 *
 * \details
 * Register: \a LINE_KR_DEV7:an_sm:an_sm
 */
#define VTSS_LINE_KR_DEV7_an_sm_an_sm        VTSS_IOREG(0x07, 0, 0x80a0)

/** 
 * \brief
 * AN state machine
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_an_sm_an_sm . an_sm
 */
#define  VTSS_F_LINE_KR_DEV7_an_sm_an_sm_an_sm(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_LINE_KR_DEV7_an_sm_an_sm_an_sm     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_LINE_KR_DEV7_an_sm_an_sm_an_sm(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a LINE_KR_DEV7:an_sts0
 *
 * Not documented
 */


/** 
 * \brief VS AN status 0
 *
 * \details
 * Register: \a LINE_KR_DEV7:an_sts0:an_sts0
 */
#define VTSS_LINE_KR_DEV7_an_sts0_an_sts0    VTSS_IOREG(0x07, 0, 0x80b0)

/** 
 * \brief
 * 1G or 3G sync status of local detector
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_an_sts0_an_sts0 . sync8b10b
 */
#define  VTSS_F_LINE_KR_DEV7_an_sts0_an_sts0_sync8b10b  VTSS_BIT(10)

/** 
 * \brief
 * 10G sync status of local detector
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_an_sts0_an_sts0 . sync10g
 */
#define  VTSS_F_LINE_KR_DEV7_an_sts0_an_sts0_sync10g  VTSS_BIT(9)

/** 
 * \brief
 * Nonce match (LH)
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_an_sts0_an_sts0 . nonce_match
 */
#define  VTSS_F_LINE_KR_DEV7_an_sts0_an_sts0_nonce_match  VTSS_BIT(8)

/** 
 * \brief
 * Incompatible link (LH)
 *
 * \details 
 * Field: VTSS_LINE_KR_DEV7_an_sts0_an_sts0 . incp_link
 */
#define  VTSS_F_LINE_KR_DEV7_an_sts0_an_sts0_incp_link  VTSS_BIT(7)

/** 
 * \brief
 * Negotiated HCD 
 *
 * \details 
 * 0: KX_1G
 * 1: KX4_10G
 * 2: KR_10G
 * 3: KR4_40G
 * 4: CR4_40G
 * 5: CR10_100G
 *
 * Field: VTSS_LINE_KR_DEV7_an_sts0_an_sts0 . link_hcd
 */
#define  VTSS_F_LINE_KR_DEV7_an_sts0_an_sts0_link_hcd(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_LINE_KR_DEV7_an_sts0_an_sts0_link_hcd     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_LINE_KR_DEV7_an_sts0_an_sts0_link_hcd(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/** 
 * \brief
 * AN link_control variable 
 *
 * \details 
 * 0: ENABLE
 * 1: DISABLE
 * 2: SCAN_FOR_CARRIER
 *
 * Field: VTSS_LINE_KR_DEV7_an_sts0_an_sts0 . link_ctl
 */
#define  VTSS_F_LINE_KR_DEV7_an_sts0_an_sts0_link_ctl(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_LINE_KR_DEV7_an_sts0_an_sts0_link_ctl     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_LINE_KR_DEV7_an_sts0_an_sts0_link_ctl(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * speed setting 
 *
 * \details 
 * 0: 10G
 * 1: 1G
 * 2: 3G
 *
 * Field: VTSS_LINE_KR_DEV7_an_sts0_an_sts0 . line_rate
 */
#define  VTSS_F_LINE_KR_DEV7_an_sts0_an_sts0_line_rate(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_LINE_KR_DEV7_an_sts0_an_sts0_line_rate     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_LINE_KR_DEV7_an_sts0_an_sts0_line_rate(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


#endif /* _VTSS_MALIBU_REGS_LINE_KR_DEV7_H_ */
