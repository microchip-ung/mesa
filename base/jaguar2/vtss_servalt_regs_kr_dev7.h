// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_SERVALT_REGS_KR_DEV7_H_
#define _VTSS_SERVALT_REGS_KR_DEV7_H_


#include "vtss_servalt_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a KR_DEV7
 *
 * \see vtss_target_KR_DEV7_e
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a KR_DEV7:KR_7X0000
 *
 * Not documented
 */


/** 
 * \brief AN control
 *
 * \details
 * Register: \a KR_DEV7:KR_7X0000:KR_7X0000
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_KR_7X0000_KR_7X0000(target)  VTSS_IOREG(target,0x4)

/** 
 * \brief
 * AN reset   (SC)
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR_7X0000_KR_7X0000 . AN_RESET
 */
#define  VTSS_F_KR_DEV7_KR_7X0000_KR_7X0000_AN_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_KR_DEV7_KR_7X0000_KR_7X0000_AN_RESET  VTSS_BIT(15)
#define  VTSS_X_KR_DEV7_KR_7X0000_KR_7X0000_AN_RESET(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Extended next page control
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR_7X0000_KR_7X0000 . NPCTL
 */
#define  VTSS_F_KR_DEV7_KR_7X0000_KR_7X0000_NPCTL(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_KR_DEV7_KR_7X0000_KR_7X0000_NPCTL  VTSS_BIT(13)
#define  VTSS_X_KR_DEV7_KR_7X0000_KR_7X0000_NPCTL(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * AN enable
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR_7X0000_KR_7X0000 . AN_ENABLE
 */
#define  VTSS_F_KR_DEV7_KR_7X0000_KR_7X0000_AN_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_KR_DEV7_KR_7X0000_KR_7X0000_AN_ENABLE  VTSS_BIT(12)
#define  VTSS_X_KR_DEV7_KR_7X0000_KR_7X0000_AN_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * AN restart (SC)
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR_7X0000_KR_7X0000 . AN_RESTART
 */
#define  VTSS_F_KR_DEV7_KR_7X0000_KR_7X0000_AN_RESTART(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_KR_DEV7_KR_7X0000_KR_7X0000_AN_RESTART  VTSS_BIT(9)
#define  VTSS_X_KR_DEV7_KR_7X0000_KR_7X0000_AN_RESTART(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * Register Group: \a KR_DEV7:KR_7X0001
 *
 * Not documented
 */


/** 
 * \brief AN status
 *
 * \details
 * Register: \a KR_DEV7:KR_7X0001:KR_7X0001
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_KR_7X0001_KR_7X0001(target)  VTSS_IOREG(target,0x5)

/** 
 * \brief
 * Parallel detection fault (LH)
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR_7X0001_KR_7X0001 . PARDETFLT
 */
#define  VTSS_F_KR_DEV7_KR_7X0001_KR_7X0001_PARDETFLT(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_KR_DEV7_KR_7X0001_KR_7X0001_PARDETFLT  VTSS_BIT(9)
#define  VTSS_X_KR_DEV7_KR_7X0001_KR_7X0001_PARDETFLT(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Extended next page status
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR_7X0001_KR_7X0001 . NPSTAT
 */
#define  VTSS_F_KR_DEV7_KR_7X0001_KR_7X0001_NPSTAT(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_KR_DEV7_KR_7X0001_KR_7X0001_NPSTAT  VTSS_BIT(7)
#define  VTSS_X_KR_DEV7_KR_7X0001_KR_7X0001_NPSTAT(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Page received (LH)
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR_7X0001_KR_7X0001 . PG_RCVD
 */
#define  VTSS_F_KR_DEV7_KR_7X0001_KR_7X0001_PG_RCVD(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_KR_DEV7_KR_7X0001_KR_7X0001_PG_RCVD  VTSS_BIT(6)
#define  VTSS_X_KR_DEV7_KR_7X0001_KR_7X0001_PG_RCVD(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * AN complete
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR_7X0001_KR_7X0001 . AN_COMPLETE
 */
#define  VTSS_F_KR_DEV7_KR_7X0001_KR_7X0001_AN_COMPLETE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_KR_DEV7_KR_7X0001_KR_7X0001_AN_COMPLETE  VTSS_BIT(5)
#define  VTSS_X_KR_DEV7_KR_7X0001_KR_7X0001_AN_COMPLETE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Remote fault (LH)
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR_7X0001_KR_7X0001 . REM_FLT
 */
#define  VTSS_F_KR_DEV7_KR_7X0001_KR_7X0001_REM_FLT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_KR_DEV7_KR_7X0001_KR_7X0001_REM_FLT  VTSS_BIT(4)
#define  VTSS_X_KR_DEV7_KR_7X0001_KR_7X0001_REM_FLT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * AN ability
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR_7X0001_KR_7X0001 . AN_ABLE
 */
#define  VTSS_F_KR_DEV7_KR_7X0001_KR_7X0001_AN_ABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_KR_DEV7_KR_7X0001_KR_7X0001_AN_ABLE  VTSS_BIT(3)
#define  VTSS_X_KR_DEV7_KR_7X0001_KR_7X0001_AN_ABLE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Link status (LL)
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR_7X0001_KR_7X0001 . LINKSTAT
 */
#define  VTSS_F_KR_DEV7_KR_7X0001_KR_7X0001_LINKSTAT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_KR_DEV7_KR_7X0001_KR_7X0001_LINKSTAT  VTSS_BIT(2)
#define  VTSS_X_KR_DEV7_KR_7X0001_KR_7X0001_LINKSTAT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * LP AN ability
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR_7X0001_KR_7X0001 . AN_LP_ABLE
 */
#define  VTSS_F_KR_DEV7_KR_7X0001_KR_7X0001_AN_LP_ABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_KR_DEV7_KR_7X0001_KR_7X0001_AN_LP_ABLE  VTSS_BIT(0)
#define  VTSS_X_KR_DEV7_KR_7X0001_KR_7X0001_AN_LP_ABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a KR_DEV7:LD_ADV
 *
 * Not documented
 */


/** 
 * \brief LD advertised abilities 15-0
 *
 * \details
 * Register: \a KR_DEV7:LD_ADV:KR_7X0010
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_LD_ADV_KR_7X0010(target)  VTSS_IOREG(target,0xb)

/** 
 * \brief
 * Local advertised abilities D[15:0]
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_LD_ADV_KR_7X0010 . ADV0
 */
#define  VTSS_F_KR_DEV7_LD_ADV_KR_7X0010_ADV0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_LD_ADV_KR_7X0010_ADV0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_LD_ADV_KR_7X0010_ADV0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief LD advertised abilities 31-16
 *
 * \details
 * Register: \a KR_DEV7:LD_ADV:KR_7X0011
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_LD_ADV_KR_7X0011(target)  VTSS_IOREG(target,0xc)

/** 
 * \brief
 * Local advertised abilities D[31:16]
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_LD_ADV_KR_7X0011 . ADV1
 */
#define  VTSS_F_KR_DEV7_LD_ADV_KR_7X0011_ADV1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_LD_ADV_KR_7X0011_ADV1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_LD_ADV_KR_7X0011_ADV1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief LD advertised abilities 47-32
 *
 * \details
 * Register: \a KR_DEV7:LD_ADV:KR_7X0012
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_LD_ADV_KR_7X0012(target)  VTSS_IOREG(target,0xd)

/** 
 * \brief
 * Local advertised abilities D[47:32]
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_LD_ADV_KR_7X0012 . ADV2
 */
#define  VTSS_F_KR_DEV7_LD_ADV_KR_7X0012_ADV2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_LD_ADV_KR_7X0012_ADV2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_LD_ADV_KR_7X0012_ADV2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV7:LP_BASE_PAGE_0
 *
 * Not documented
 */


/** 
 * \brief LP base page advertised abilities 15-0
 *
 * \details
 * Register: \a KR_DEV7:LP_BASE_PAGE_0:KR_7X0013
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_LP_BASE_PAGE_0_KR_7X0013(target)  VTSS_IOREG(target,0x6)

/** 
 * \brief
 * LP advertised abilities D[15:0]
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_LP_BASE_PAGE_0_KR_7X0013 . LP_BP_ADV0
 */
#define  VTSS_F_KR_DEV7_LP_BASE_PAGE_0_KR_7X0013_LP_BP_ADV0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_LP_BASE_PAGE_0_KR_7X0013_LP_BP_ADV0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_LP_BASE_PAGE_0_KR_7X0013_LP_BP_ADV0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV7:LP_BASE_PAGE_1
 *
 * Not documented
 */


/** 
 * \brief LP base page advertised abilities 31-16
 *
 * \details
 * Register: \a KR_DEV7:LP_BASE_PAGE_1:KR_7X0014
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_LP_BASE_PAGE_1_KR_7X0014(target)  VTSS_IOREG(target,0x7)

/** 
 * \brief
 * LP advertised abilities D[31:16]
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_LP_BASE_PAGE_1_KR_7X0014 . LP_BP_ADV1
 */
#define  VTSS_F_KR_DEV7_LP_BASE_PAGE_1_KR_7X0014_LP_BP_ADV1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_LP_BASE_PAGE_1_KR_7X0014_LP_BP_ADV1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_LP_BASE_PAGE_1_KR_7X0014_LP_BP_ADV1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV7:LP_BASE_PAGE_2
 *
 * Not documented
 */


/** 
 * \brief LP base page advertised abilities 47-32
 *
 * \details
 * Register: \a KR_DEV7:LP_BASE_PAGE_2:KR_7X0015
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_LP_BASE_PAGE_2_KR_7X0015(target)  VTSS_IOREG(target,0x8)

/** 
 * \brief
 * LP advertised abilities D[47:32]
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_LP_BASE_PAGE_2_KR_7X0015 . LP_BP_ADV2
 */
#define  VTSS_F_KR_DEV7_LP_BASE_PAGE_2_KR_7X0015_LP_BP_ADV2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_LP_BASE_PAGE_2_KR_7X0015_LP_BP_ADV2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_LP_BASE_PAGE_2_KR_7X0015_LP_BP_ADV2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV7:LD_NEXT_PAGE
 *
 * Not documented
 */


/** 
 * \brief NxtPg transmit 15-0
 *
 * \details
 * Register: \a KR_DEV7:LD_NEXT_PAGE:KR_7X0016
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_LD_NEXT_PAGE_KR_7X0016(target)  VTSS_IOREG(target,0xe)

/** 
 * \brief
 * Next page to transmit D[15:0]
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_LD_NEXT_PAGE_KR_7X0016 . NP_TX0
 */
#define  VTSS_F_KR_DEV7_LD_NEXT_PAGE_KR_7X0016_NP_TX0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_LD_NEXT_PAGE_KR_7X0016_NP_TX0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_LD_NEXT_PAGE_KR_7X0016_NP_TX0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief NxtPg transmit 31-16
 *
 * \details
 * Register: \a KR_DEV7:LD_NEXT_PAGE:KR_7X0017
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_LD_NEXT_PAGE_KR_7X0017(target)  VTSS_IOREG(target,0xf)

/** 
 * \brief
 * Next page to transmit D[31:16]
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_LD_NEXT_PAGE_KR_7X0017 . NP_TX1
 */
#define  VTSS_F_KR_DEV7_LD_NEXT_PAGE_KR_7X0017_NP_TX1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_LD_NEXT_PAGE_KR_7X0017_NP_TX1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_LD_NEXT_PAGE_KR_7X0017_NP_TX1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief NxtPg transmit 47-32
 *
 * \details
 * Register: \a KR_DEV7:LD_NEXT_PAGE:KR_7X0018
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_LD_NEXT_PAGE_KR_7X0018(target)  VTSS_IOREG(target,0x10)

/** 
 * \brief
 * Next page to transmit D[47:32]
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_LD_NEXT_PAGE_KR_7X0018 . NP_TX2
 */
#define  VTSS_F_KR_DEV7_LD_NEXT_PAGE_KR_7X0018_NP_TX2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_LD_NEXT_PAGE_KR_7X0018_NP_TX2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_LD_NEXT_PAGE_KR_7X0018_NP_TX2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV7:LP_NEXT_PAGE
 *
 * Not documented
 */


/** 
 * \brief LP next page ability 15-0
 *
 * \details
 * Register: \a KR_DEV7:LP_NEXT_PAGE:KR_7X0019
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_LP_NEXT_PAGE_KR_7X0019(target)  VTSS_IOREG(target,0x0)

/** 
 * \brief
 * LP next page  ability D[15:0]
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_LP_NEXT_PAGE_KR_7X0019 . LP_NP_ADV0
 */
#define  VTSS_F_KR_DEV7_LP_NEXT_PAGE_KR_7X0019_LP_NP_ADV0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_LP_NEXT_PAGE_KR_7X0019_LP_NP_ADV0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_LP_NEXT_PAGE_KR_7X0019_LP_NP_ADV0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief LP next page ability 31-16
 *
 * \details
 * Register: \a KR_DEV7:LP_NEXT_PAGE:KR_7X001A
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_LP_NEXT_PAGE_KR_7X001A(target)  VTSS_IOREG(target,0x1)

/** 
 * \brief
 * LP next page ability D[31:16]
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_LP_NEXT_PAGE_KR_7X001A . LP_NP_ADV1
 */
#define  VTSS_F_KR_DEV7_LP_NEXT_PAGE_KR_7X001A_LP_NP_ADV1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_LP_NEXT_PAGE_KR_7X001A_LP_NP_ADV1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_LP_NEXT_PAGE_KR_7X001A_LP_NP_ADV1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief LP next page ability 47-32
 *
 * \details
 * Register: \a KR_DEV7:LP_NEXT_PAGE:KR_7X001B
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_LP_NEXT_PAGE_KR_7X001B(target)  VTSS_IOREG(target,0x2)

/** 
 * \brief
 * LP next page ability D[47:32]
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_LP_NEXT_PAGE_KR_7X001B . LP_NP_ADV2
 */
#define  VTSS_F_KR_DEV7_LP_NEXT_PAGE_KR_7X001B_LP_NP_ADV2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_LP_NEXT_PAGE_KR_7X001B_LP_NP_ADV2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_LP_NEXT_PAGE_KR_7X001B_LP_NP_ADV2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV7:KR_7X0030
 *
 * Not documented
 */


/** 
 * \brief Backplane ethernet status
 *
 * \details
 * Register: \a KR_DEV7:KR_7X0030:KR_7X0030
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_KR_7X0030_KR_7X0030(target)  VTSS_IOREG(target,0x11)

/** 
 * \brief
 * 10G CR10   negotiated
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR_7X0030_KR_7X0030 . AN_NEG_CR10
 */
#define  VTSS_F_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_CR10(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_CR10  VTSS_BIT(8)
#define  VTSS_X_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_CR10(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * 10G CR4    negotiated
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR_7X0030_KR_7X0030 . AN_NEG_CR4
 */
#define  VTSS_F_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_CR4(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_CR4  VTSS_BIT(6)
#define  VTSS_X_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_CR4(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * 10G KR4    negotiated
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR_7X0030_KR_7X0030 . AN_NEG_KR4
 */
#define  VTSS_F_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_KR4(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_KR4  VTSS_BIT(5)
#define  VTSS_X_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_KR4(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * 10G KR FEC negotiated
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR_7X0030_KR_7X0030 . AN_NEG_FEC
 */
#define  VTSS_F_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_FEC(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_FEC  VTSS_BIT(4)
#define  VTSS_X_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_FEC(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * 10G KR     negotiated
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR_7X0030_KR_7X0030 . AN_NEG_KR
 */
#define  VTSS_F_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_KR(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_KR  VTSS_BIT(3)
#define  VTSS_X_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_KR(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * 10G KX4    negotiated
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR_7X0030_KR_7X0030 . AN_NEG_KX4
 */
#define  VTSS_F_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_KX4(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_KX4  VTSS_BIT(2)
#define  VTSS_X_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_KX4(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * 1G  KX     negotiated
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR_7X0030_KR_7X0030 . AN_NEG_KX
 */
#define  VTSS_F_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_KX(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_KX  VTSS_BIT(1)
#define  VTSS_X_KR_DEV7_KR_7X0030_KR_7X0030_AN_NEG_KX(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * BP AN ability
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR_7X0030_KR_7X0030 . AN_BP_ABLE
 */
#define  VTSS_F_KR_DEV7_KR_7X0030_KR_7X0030_AN_BP_ABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_KR_DEV7_KR_7X0030_KR_7X0030_AN_BP_ABLE  VTSS_BIT(0)
#define  VTSS_X_KR_DEV7_KR_7X0030_KR_7X0030_AN_BP_ABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a KR_DEV7:AN_CFG0
 *
 * Not documented
 */


/** 
 * \brief VS AN config 0
 *
 * \details
 * Register: \a KR_DEV7:AN_CFG0:AN_CFG0
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_AN_CFG0_AN_CFG0(target)  VTSS_IOREG(target,0x12)

/** 
 * \brief
 * Clear AN state machine history
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_AN_CFG0_AN_CFG0 . AN_SM_HIST_CLR
 */
#define  VTSS_F_KR_DEV7_AN_CFG0_AN_CFG0_AN_SM_HIST_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_KR_DEV7_AN_CFG0_AN_CFG0_AN_SM_HIST_CLR  VTSS_BIT(5)
#define  VTSS_X_KR_DEV7_AN_CFG0_AN_CFG0_AN_SM_HIST_CLR(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Disable clock gating
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_AN_CFG0_AN_CFG0 . CLKG_DISABLE
 */
#define  VTSS_F_KR_DEV7_AN_CFG0_AN_CFG0_CLKG_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_KR_DEV7_AN_CFG0_AN_CFG0_CLKG_DISABLE  VTSS_BIT(4)
#define  VTSS_X_KR_DEV7_AN_CFG0_AN_CFG0_CLKG_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Bypass training if 10G negotiated
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_AN_CFG0_AN_CFG0 . TR_DISABLE
 */
#define  VTSS_F_KR_DEV7_AN_CFG0_AN_CFG0_TR_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_KR_DEV7_AN_CFG0_AN_CFG0_TR_DISABLE  VTSS_BIT(3)
#define  VTSS_X_KR_DEV7_AN_CFG0_AN_CFG0_TR_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Select source of 10G sync signal   
 *
 * \details 
 * 0: KR internal 
 * 1: External
 *
 * Field: ::VTSS_KR_DEV7_AN_CFG0_AN_CFG0 . SYNC10G_SEL
 */
#define  VTSS_F_KR_DEV7_AN_CFG0_AN_CFG0_SYNC10G_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_KR_DEV7_AN_CFG0_AN_CFG0_SYNC10G_SEL  VTSS_BIT(2)
#define  VTSS_X_KR_DEV7_AN_CFG0_AN_CFG0_SYNC10G_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Select source of 3G and 1G sync signal 
 *
 * \details 
 * 0: KR internal 
 * 1: External
 *
 * Field: ::VTSS_KR_DEV7_AN_CFG0_AN_CFG0 . SYNC8B10B_SEL
 */
#define  VTSS_F_KR_DEV7_AN_CFG0_AN_CFG0_SYNC8B10B_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_KR_DEV7_AN_CFG0_AN_CFG0_SYNC8B10B_SEL  VTSS_BIT(1)
#define  VTSS_X_KR_DEV7_AN_CFG0_AN_CFG0_SYNC8B10B_SEL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * Register Group: \a KR_DEV7:BL_TMR
 *
 * Not documented
 */


/** 
 * \brief VS AN break_link timer lsw
 *
 * \details
 * Register: \a KR_DEV7:BL_TMR:BL_LSW
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_BL_TMR_BL_LSW(target)   VTSS_IOREG(target,0x13)

/** 
 * \brief
 * break_link_timer setting
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_BL_TMR_BL_LSW . BL_TMR_LSW
 */
#define  VTSS_F_KR_DEV7_BL_TMR_BL_LSW_BL_TMR_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_BL_TMR_BL_LSW_BL_TMR_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_BL_TMR_BL_LSW_BL_TMR_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS AN break_link timer msw
 *
 * \details
 * Register: \a KR_DEV7:BL_TMR:BL_MSW
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_BL_TMR_BL_MSW(target)   VTSS_IOREG(target,0x14)

/** 
 * \brief
 * break_link_timer setting
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_BL_TMR_BL_MSW . BL_TMR_MSW
 */
#define  VTSS_F_KR_DEV7_BL_TMR_BL_MSW_BL_TMR_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_BL_TMR_BL_MSW_BL_TMR_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_BL_TMR_BL_MSW_BL_TMR_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV7:AW_TMR
 *
 * Not documented
 */


/** 
 * \brief VS AN aneg_wait timer lsw
 *
 * \details
 * Register: \a KR_DEV7:AW_TMR:AW_LSW
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_AW_TMR_AW_LSW(target)   VTSS_IOREG(target,0x15)

/** 
 * \brief
 * an_wait_timer setting
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_AW_TMR_AW_LSW . AW_TMR_LSW
 */
#define  VTSS_F_KR_DEV7_AW_TMR_AW_LSW_AW_TMR_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_AW_TMR_AW_LSW_AW_TMR_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_AW_TMR_AW_LSW_AW_TMR_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS AN aneg_wait timer msw
 *
 * \details
 * Register: \a KR_DEV7:AW_TMR:AW_MSW
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_AW_TMR_AW_MSW(target)   VTSS_IOREG(target,0x16)

/** 
 * \brief
 * an_wait_timer setting
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_AW_TMR_AW_MSW . AW_TMR_MSW
 */
#define  VTSS_F_KR_DEV7_AW_TMR_AW_MSW_AW_TMR_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_AW_TMR_AW_MSW_AW_TMR_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_AW_TMR_AW_MSW_AW_TMR_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV7:LFLONG_TMR
 *
 * Not documented
 */


/** 
 * \brief VS AN link_fail_inhibit timer lsw
 *
 * \details
 * Register: \a KR_DEV7:LFLONG_TMR:LFLONG_LSW
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_LFLONG_TMR_LFLONG_LSW(target)  VTSS_IOREG(target,0x17)

/** 
 * \brief
 * 10g link_fail_inhibit_timer setting
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_LFLONG_TMR_LFLONG_LSW . LFLONG_TMR_LSW
 */
#define  VTSS_F_KR_DEV7_LFLONG_TMR_LFLONG_LSW_LFLONG_TMR_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_LFLONG_TMR_LFLONG_LSW_LFLONG_TMR_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_LFLONG_TMR_LFLONG_LSW_LFLONG_TMR_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS AN link_fail_inhibit_long timer msw
 *
 * \details
 * Register: \a KR_DEV7:LFLONG_TMR:LFLONG_MSW
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_LFLONG_TMR_LFLONG_MSW(target)  VTSS_IOREG(target,0x18)

/** 
 * \brief
 * 10g link_fail_inhibit_timer setting
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_LFLONG_TMR_LFLONG_MSW . LFLONG_TMR_MSW
 */
#define  VTSS_F_KR_DEV7_LFLONG_TMR_LFLONG_MSW_LFLONG_TMR_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_LFLONG_TMR_LFLONG_MSW_LFLONG_TMR_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_LFLONG_TMR_LFLONG_MSW_LFLONG_TMR_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV7:LFSHORT_TMR
 *
 * Not documented
 */


/** 
 * \brief VS AN link_fail_inhibit_short timer lsw
 *
 * \details
 * Register: \a KR_DEV7:LFSHORT_TMR:LFSHORT_LSW
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_LFSHORT_TMR_LFSHORT_LSW(target)  VTSS_IOREG(target,0x19)

/** 
 * \brief
 * 1g link_fail_inhibit_timer setting
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_LFSHORT_TMR_LFSHORT_LSW . LFSHORT_TMR_LSW
 */
#define  VTSS_F_KR_DEV7_LFSHORT_TMR_LFSHORT_LSW_LFSHORT_TMR_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_LFSHORT_TMR_LFSHORT_LSW_LFSHORT_TMR_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_LFSHORT_TMR_LFSHORT_LSW_LFSHORT_TMR_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS AN link_fail_inhibit_short timer msw
 *
 * \details
 * Register: \a KR_DEV7:LFSHORT_TMR:LFSHORT_MSW
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_LFSHORT_TMR_LFSHORT_MSW(target)  VTSS_IOREG(target,0x1a)

/** 
 * \brief
 * 1g link_fail_inhibit_timer setting
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_LFSHORT_TMR_LFSHORT_MSW . LFSHORT_TMR_MSW
 */
#define  VTSS_F_KR_DEV7_LFSHORT_TMR_LFSHORT_MSW_LFSHORT_TMR_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_LFSHORT_TMR_LFSHORT_MSW_LFSHORT_TMR_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_LFSHORT_TMR_LFSHORT_MSW_LFSHORT_TMR_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV7:LP_TMR
 *
 * Not documented
 */


/** 
 * \brief VS AN link_pass_inhibit timer lsw
 *
 * \details
 * Register: \a KR_DEV7:LP_TMR:LP_LSW
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_LP_TMR_LP_LSW(target)   VTSS_IOREG(target,0x1b)

/** 
 * \brief
 * link_pass_inhibit_timer setting
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_LP_TMR_LP_LSW . LP_TMR_LSW
 */
#define  VTSS_F_KR_DEV7_LP_TMR_LP_LSW_LP_TMR_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_LP_TMR_LP_LSW_LP_TMR_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_LP_TMR_LP_LSW_LP_TMR_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS AN link_pass_inhibit timer msw
 *
 * \details
 * Register: \a KR_DEV7:LP_TMR:LP_MSW
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_LP_TMR_LP_MSW(target)   VTSS_IOREG(target,0x1c)

/** 
 * \brief
 * link_pass_inhibit_timer setting
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_LP_TMR_LP_MSW . LP_TMR_MSW
 */
#define  VTSS_F_KR_DEV7_LP_TMR_LP_MSW_LP_TMR_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_LP_TMR_LP_MSW_LP_TMR_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_LP_TMR_LP_MSW_LP_TMR_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV7:TR_TMR
 *
 * Not documented
 */


/** 
 * \brief VS AN training state timer lsw
 *
 * \details
 * Register: \a KR_DEV7:TR_TMR:TR_LSW
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_TR_TMR_TR_LSW(target)   VTSS_IOREG(target,0x1d)

/** 
 * \brief
 * training_state_timer setting
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_TR_TMR_TR_LSW . TR_TMR_LSW
 */
#define  VTSS_F_KR_DEV7_TR_TMR_TR_LSW_TR_TMR_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_TR_TMR_TR_LSW_TR_TMR_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_TR_TMR_TR_LSW_TR_TMR_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS AN training state timer msw
 *
 * \details
 * Register: \a KR_DEV7:TR_TMR:TR_MSW
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_TR_TMR_TR_MSW(target)   VTSS_IOREG(target,0x1e)

/** 
 * \brief
 * training_state_timer setting
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_TR_TMR_TR_MSW . TR_TMR_MSW
 */
#define  VTSS_F_KR_DEV7_TR_TMR_TR_MSW_TR_TMR_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_TR_TMR_TR_MSW_TR_TMR_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_TR_TMR_TR_MSW_TR_TMR_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV7:PD_TMR
 *
 * Not documented
 */


/** 
 * \brief VS AN page_detect timer lsw
 *
 * \details
 * Register: \a KR_DEV7:PD_TMR:PD_LSW
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_PD_TMR_PD_LSW(target)   VTSS_IOREG(target,0x1f)

/** 
 * \brief
 * page_detect_timer setting
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_PD_TMR_PD_LSW . PD_TMR_LSW
 */
#define  VTSS_F_KR_DEV7_PD_TMR_PD_LSW_PD_TMR_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_PD_TMR_PD_LSW_PD_TMR_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_PD_TMR_PD_LSW_PD_TMR_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS AN page_detect timer msw
 *
 * \details
 * Register: \a KR_DEV7:PD_TMR:PD_MSW
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_PD_TMR_PD_MSW(target)   VTSS_IOREG(target,0x20)

/** 
 * \brief
 * page_detect_timer setting
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_PD_TMR_PD_MSW . PD_TMR_MSW
 */
#define  VTSS_F_KR_DEV7_PD_TMR_PD_MSW_PD_TMR_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_PD_TMR_PD_MSW_PD_TMR_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_PD_TMR_PD_MSW_PD_TMR_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV7:KR10G_TMR
 *
 * Not documented
 */


/** 
 * \brief VS AN rate_detect_10g timer lsw
 *
 * \details
 * Register: \a KR_DEV7:KR10G_TMR:KR10G_LSW
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_KR10G_TMR_KR10G_LSW(target)  VTSS_IOREG(target,0x21)

/** 
 * \brief
 * rate_detect_10g_timer setting
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR10G_TMR_KR10G_LSW . KR10G_TMR_LSW
 */
#define  VTSS_F_KR_DEV7_KR10G_TMR_KR10G_LSW_KR10G_TMR_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_KR10G_TMR_KR10G_LSW_KR10G_TMR_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_KR10G_TMR_KR10G_LSW_KR10G_TMR_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS AN rate_detect_10g timer msw
 *
 * \details
 * Register: \a KR_DEV7:KR10G_TMR:KR10G_MSW
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_KR10G_TMR_KR10G_MSW(target)  VTSS_IOREG(target,0x22)

/** 
 * \brief
 * rate_detect_10g_timer setting
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR10G_TMR_KR10G_MSW . KR10G_TMR_MSW
 */
#define  VTSS_F_KR_DEV7_KR10G_TMR_KR10G_MSW_KR10G_TMR_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_KR10G_TMR_KR10G_MSW_KR10G_TMR_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_KR10G_TMR_KR10G_MSW_KR10G_TMR_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV7:KR3G_TMR
 *
 * Not documented
 */


/** 
 * \brief VS AN rate_detect_3g timer lsw
 *
 * \details
 * Register: \a KR_DEV7:KR3G_TMR:KR3G_LSW
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_KR3G_TMR_KR3G_LSW(target)  VTSS_IOREG(target,0x23)

/** 
 * \brief
 * rate_detect_3g_timer setting
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR3G_TMR_KR3G_LSW . KR3G_TMR_LSW
 */
#define  VTSS_F_KR_DEV7_KR3G_TMR_KR3G_LSW_KR3G_TMR_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_KR3G_TMR_KR3G_LSW_KR3G_TMR_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_KR3G_TMR_KR3G_LSW_KR3G_TMR_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS AN rate_detect_3g timer msw
 *
 * \details
 * Register: \a KR_DEV7:KR3G_TMR:KR3G_MSW
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_KR3G_TMR_KR3G_MSW(target)  VTSS_IOREG(target,0x24)

/** 
 * \brief
 * rate_detect_3g_timer setting
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR3G_TMR_KR3G_MSW . KR3G_TMR_MSW
 */
#define  VTSS_F_KR_DEV7_KR3G_TMR_KR3G_MSW_KR3G_TMR_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_KR3G_TMR_KR3G_MSW_KR3G_TMR_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_KR3G_TMR_KR3G_MSW_KR3G_TMR_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV7:KR1G_TMR
 *
 * Not documented
 */


/** 
 * \brief VS AN rate_detect_1g timer lsw
 *
 * \details
 * Register: \a KR_DEV7:KR1G_TMR:KR1G_LSW
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_KR1G_TMR_KR1G_LSW(target)  VTSS_IOREG(target,0x25)

/** 
 * \brief
 * rate_detect_1g_timer setting
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR1G_TMR_KR1G_LSW . KR1G_TMR_LSW
 */
#define  VTSS_F_KR_DEV7_KR1G_TMR_KR1G_LSW_KR1G_TMR_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_KR1G_TMR_KR1G_LSW_KR1G_TMR_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_KR1G_TMR_KR1G_LSW_KR1G_TMR_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VS AN rate_detect_1g timer msw
 *
 * \details
 * Register: \a KR_DEV7:KR1G_TMR:KR1G_MSW
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_KR1G_TMR_KR1G_MSW(target)  VTSS_IOREG(target,0x26)

/** 
 * \brief
 * rate_detect_1g_timer setting
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_KR1G_TMR_KR1G_MSW . KR1G_TMR_MSW
 */
#define  VTSS_F_KR_DEV7_KR1G_TMR_KR1G_MSW_KR1G_TMR_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_KR_DEV7_KR1G_TMR_KR1G_MSW_KR1G_TMR_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_KR_DEV7_KR1G_TMR_KR1G_MSW_KR1G_TMR_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a KR_DEV7:AN_HIST
 *
 * Not documented
 */


/** 
 * \brief VS AN arb state mach history
 *
 * \details
 * Register: \a KR_DEV7:AN_HIST:AN_HIST
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_AN_HIST_AN_HIST(target)  VTSS_IOREG(target,0x27)

/** 
 * \brief
 * AN state machine history
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_AN_HIST_AN_HIST . AN_SM_HIST
 */
#define  VTSS_F_KR_DEV7_AN_HIST_AN_HIST_AN_SM_HIST(x)  VTSS_ENCODE_BITFIELD(x,0,15)
#define  VTSS_M_KR_DEV7_AN_HIST_AN_HIST_AN_SM_HIST     VTSS_ENCODE_BITMASK(0,15)
#define  VTSS_X_KR_DEV7_AN_HIST_AN_HIST_AN_SM_HIST(x)  VTSS_EXTRACT_BITFIELD(x,0,15)

/**
 * Register Group: \a KR_DEV7:AN_SM
 *
 * Not documented
 */


/** 
 * \brief VS AN arb state machine
 *
 * \details
 * Register: \a KR_DEV7:AN_SM:AN_SM
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_AN_SM_AN_SM(target)     VTSS_IOREG(target,0x9)

/** 
 * \brief
 * AN state machine
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_AN_SM_AN_SM . AN_SM
 */
#define  VTSS_F_KR_DEV7_AN_SM_AN_SM_AN_SM(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_KR_DEV7_AN_SM_AN_SM_AN_SM     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_KR_DEV7_AN_SM_AN_SM_AN_SM(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a KR_DEV7:AN_STS0
 *
 * Not documented
 */


/** 
 * \brief VS AN status 0
 *
 * \details
 * Register: \a KR_DEV7:AN_STS0:AN_STS0
 *
 * @param target A \a ::vtss_target_KR_DEV7_e target
 */
#define VTSS_KR_DEV7_AN_STS0_AN_STS0(target)  VTSS_IOREG(target,0xa)

/** 
 * \brief
 * 1G or 3G sync status of local detector
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_AN_STS0_AN_STS0 . SYNC8B10B
 */
#define  VTSS_F_KR_DEV7_AN_STS0_AN_STS0_SYNC8B10B(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_KR_DEV7_AN_STS0_AN_STS0_SYNC8B10B  VTSS_BIT(10)
#define  VTSS_X_KR_DEV7_AN_STS0_AN_STS0_SYNC8B10B(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * 10G sync status of local detector
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_AN_STS0_AN_STS0 . SYNC10G
 */
#define  VTSS_F_KR_DEV7_AN_STS0_AN_STS0_SYNC10G(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_KR_DEV7_AN_STS0_AN_STS0_SYNC10G  VTSS_BIT(9)
#define  VTSS_X_KR_DEV7_AN_STS0_AN_STS0_SYNC10G(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Nonce match (LH)
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_AN_STS0_AN_STS0 . NONCE_MATCH
 */
#define  VTSS_F_KR_DEV7_AN_STS0_AN_STS0_NONCE_MATCH(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_KR_DEV7_AN_STS0_AN_STS0_NONCE_MATCH  VTSS_BIT(8)
#define  VTSS_X_KR_DEV7_AN_STS0_AN_STS0_NONCE_MATCH(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Incompatible link (LH)
 *
 * \details 
 * Field: ::VTSS_KR_DEV7_AN_STS0_AN_STS0 . INCP_LINK
 */
#define  VTSS_F_KR_DEV7_AN_STS0_AN_STS0_INCP_LINK(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_KR_DEV7_AN_STS0_AN_STS0_INCP_LINK  VTSS_BIT(7)
#define  VTSS_X_KR_DEV7_AN_STS0_AN_STS0_INCP_LINK(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

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
 * Field: ::VTSS_KR_DEV7_AN_STS0_AN_STS0 . LINK_HCD
 */
#define  VTSS_F_KR_DEV7_AN_STS0_AN_STS0_LINK_HCD(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_KR_DEV7_AN_STS0_AN_STS0_LINK_HCD     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_KR_DEV7_AN_STS0_AN_STS0_LINK_HCD(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/** 
 * \brief
 * AN link_control variable 
 *
 * \details 
 * 0: ENABLE
 * 1: DISABLE
 * 2: SCAN_FOR_CARRIER
 *
 * Field: ::VTSS_KR_DEV7_AN_STS0_AN_STS0 . LINK_CTL
 */
#define  VTSS_F_KR_DEV7_AN_STS0_AN_STS0_LINK_CTL(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_KR_DEV7_AN_STS0_AN_STS0_LINK_CTL     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_KR_DEV7_AN_STS0_AN_STS0_LINK_CTL(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * speed setting 
 *
 * \details 
 * 0: 10G
 * 1: 1G
 * 2: 3G
 *
 * Field: ::VTSS_KR_DEV7_AN_STS0_AN_STS0 . LINE_RATE
 */
#define  VTSS_F_KR_DEV7_AN_STS0_AN_STS0_LINE_RATE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_KR_DEV7_AN_STS0_AN_STS0_LINE_RATE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_KR_DEV7_AN_STS0_AN_STS0_LINE_RATE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


#endif /* _VTSS_SERVALT_REGS_KR_DEV7_H_ */
