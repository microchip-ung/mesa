/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#ifndef _VTSS_LAGUNA_REGS_HICM_H_
#define _VTSS_LAGUNA_REGS_HICM_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a HICM
 *
 * The Integrity Check Monitor (ICM) is a DMA controller that performs hash
 * calculation over
 * multiple memory regions through the use of transfer descriptors located
 * in memory (ICM
 * Descriptor Area). The Hash function is based on the Secure Hash
 * Algorithm (SHA). The ICM
 * controller integrates two modes of operation. The first one is used to
 * hash a list of memory
 * regions and save the digests to memory (ICM Hash Area). The second
 * operation mode is an
 * active monitoring of the memory. In that mode, the hash function is
 * evaluated and compared
 * to the digest located at a predefined memory address (ICM Hash Area). If
 * a mismatch occurs,
 * an interrupt is raised.
 *
 ***********************************************************************/

/**
 * Register Group: \a HICM:HICM_REGS
 *
 * Not documented
 */


/**
 * \brief ICM Configuration Register
 *
 * \details
 * Register: \a HICM:HICM_REGS:ICM_CFG
 */
#define VTSS_HICM_ICM_CFG                    VTSS_IOREG(VTSS_TO_HICM,0x0)

/**
 * \brief
 * DAPROT: Region Descriptor Area ProtectionThis field does not require
 * modifications.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_CFG . DAPROT
 */
#define  VTSS_F_HICM_ICM_CFG_DAPROT(x)        VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_HICM_ICM_CFG_DAPROT           VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_HICM_ICM_CFG_DAPROT(x)        VTSS_EXTRACT_BITFIELD(x,24,6)

/**
 * \brief
 * HAPROT: Region Hash Area ProtectionThis field does not require
 * modifications.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_CFG . HAPROT
 */
#define  VTSS_F_HICM_ICM_CFG_HAPROT(x)        VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_HICM_ICM_CFG_HAPROT           VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_HICM_ICM_CFG_HAPROT(x)        VTSS_EXTRACT_BITFIELD(x,16,6)

/**
 * \brief
 * UALGO: User SHA Algorithm
 *
 * \details
 * 0: SHA1 SHA1 algorithm processed
 * 1: SHA256 SHA256 algorithm processed
 * 4: SHA224 SHA224 algorithm processed

 *
 * Field: ::VTSS_HICM_ICM_CFG . UALGO
 */
#define  VTSS_F_HICM_ICM_CFG_UALGO(x)         VTSS_ENCODE_BITFIELD(x,13,3)
#define  VTSS_M_HICM_ICM_CFG_UALGO            VTSS_ENCODE_BITMASK(13,3)
#define  VTSS_X_HICM_ICM_CFG_UALGO(x)         VTSS_EXTRACT_BITFIELD(x,13,3)

/**
 * \brief
 * UIHASH: User Initial Hash Value
 *
 * \details
 * 0: The secure hash standard provides the initial hash value.
 * 1: The initial hash value is programmable. Field UALGO provides the SHA
 * algorithm. The ALGO field of the ICM_RCFG
 * structure member has no effect.
 *
 * Field: ::VTSS_HICM_ICM_CFG . UIHASH
 */
#define  VTSS_F_HICM_ICM_CFG_UIHASH(x)        VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_HICM_ICM_CFG_UIHASH           VTSS_BIT(12)
#define  VTSS_X_HICM_ICM_CFG_UIHASH(x)        VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * DUALBUFF: Dual Input Buffer
 *
 * \details
 * 0: Dual Input buffer mode is disabled.
 * 1: Dual Input buffer mode is enabled (Better performances, higher
 * bandwidth required on system bus).
 *
 * Field: ::VTSS_HICM_ICM_CFG . DUALBUFF
 */
#define  VTSS_F_HICM_ICM_CFG_DUALBUFF(x)      VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_HICM_ICM_CFG_DUALBUFF         VTSS_BIT(9)
#define  VTSS_X_HICM_ICM_CFG_DUALBUFF(x)      VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * ASCD: Automatic Switch To Compare Digest
 *
 * \details
 * 0: Automatic mode is disabled.
 * 1: When this mode is enabled, the ICM controller automatically switches
 * to active monitoring after the first Main List pass.
 * Both CDWBN and WBDIS bits have no effect. A one must be written to the
 * EOM bit in ICM_RCFG to terminate the
 * monitoring.
 *
 * Field: ::VTSS_HICM_ICM_CFG . ASCD
 */
#define  VTSS_F_HICM_ICM_CFG_ASCD(x)          VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_HICM_ICM_CFG_ASCD             VTSS_BIT(8)
#define  VTSS_X_HICM_ICM_CFG_ASCD(x)          VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * BBC: Bus Burden ControlThis field is used to control the burden of the
 * ICM system bus. The number of system clock cycles between the end of
 * thecurrent processing and the next block transfer is set to 2BBC. Up to
 * 32,768 cycles can be inserted.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_CFG . BBC
 */
#define  VTSS_F_HICM_ICM_CFG_BBC(x)           VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HICM_ICM_CFG_BBC              VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HICM_ICM_CFG_BBC(x)           VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * SLBDIS: Secondary List Branching Disable
 *
 * \details
 * 0: Branching to the Secondary List is permitted.
 * 1: Branching to the Secondary List is forbidden. The NEXT field of the
 * ICM_RNEXT structure member has no effect and is
 * always considered as zero.
 *
 * Field: ::VTSS_HICM_ICM_CFG . SLBDIS
 */
#define  VTSS_F_HICM_ICM_CFG_SLBDIS(x)        VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HICM_ICM_CFG_SLBDIS           VTSS_BIT(2)
#define  VTSS_X_HICM_ICM_CFG_SLBDIS(x)        VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * EOMDIS: End of Monitoring Disable
 *
 * \details
 * 0: End of Monitoring is permitted
 * 1: End of Monitoring is forbidden. The EOM bit of the ICM_RCFG structure
 * member has no effect.
 *
 * Field: ::VTSS_HICM_ICM_CFG . EOMDIS
 */
#define  VTSS_F_HICM_ICM_CFG_EOMDIS(x)        VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HICM_ICM_CFG_EOMDIS           VTSS_BIT(1)
#define  VTSS_X_HICM_ICM_CFG_EOMDIS(x)        VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * WBDIS: Write Back DisableWhen ASCD bit of the ICM_CFG register is set,
 * WBDIS bit value has no effect.
 *
 * \details
 * 0: Write Back Operations are permitted.
 * 1: Write Back Operations are forbidden. Context register CDWBN bit is
 * internally set to one and cannot be modified by a
 * linked list element. The CDWBN bit of the ICM_RCFG structure member has
 * no effect.
 *
 * Field: ::VTSS_HICM_ICM_CFG . WBDIS
 */
#define  VTSS_F_HICM_ICM_CFG_WBDIS(x)         VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HICM_ICM_CFG_WBDIS            VTSS_BIT(0)
#define  VTSS_X_HICM_ICM_CFG_WBDIS(x)         VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief ICM Control Register
 *
 * \details
 * Write_Only
 *
 * Register: \a HICM:HICM_REGS:ICM_CTRL
 */
#define VTSS_HICM_ICM_CTRL                   VTSS_IOREG(VTSS_TO_HICM,0x1)

/**
 * \brief
 * RMEN: Region Monitoring EnableMonitoring is activated by default.
 *
 * \details
 * 0: No effect
 * 1: When bit RMEN[i] is set to one, the monitoring of region with
 * identifier i is activated.
 *
 * Field: ::VTSS_HICM_ICM_CTRL . RMEN
 */
#define  VTSS_F_HICM_ICM_CTRL_RMEN(x)         VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HICM_ICM_CTRL_RMEN            VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HICM_ICM_CTRL_RMEN(x)         VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * RMDIS: Region Monitoring Disable
 *
 * \details
 * 0: No effect
 * 1: When bit RMDIS[i] is set to one, the monitoring of region with
 * identifier i is disabled.
 *
 * Field: ::VTSS_HICM_ICM_CTRL . RMDIS
 */
#define  VTSS_F_HICM_ICM_CTRL_RMDIS(x)        VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HICM_ICM_CTRL_RMDIS           VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HICM_ICM_CTRL_RMDIS(x)        VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * REHASH: Recompute Internal Hash
 *
 * \details
 * 0: No effect
 * 1: When REHASH[i] is set to one, Region i digest is re-computed. This
 * bit is only available when region monitoring is
 * disabled.
 *
 * Field: ::VTSS_HICM_ICM_CTRL . REHASH
 */
#define  VTSS_F_HICM_ICM_CTRL_REHASH(x)       VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HICM_ICM_CTRL_REHASH          VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HICM_ICM_CTRL_REHASH(x)       VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * SWRST: Software Reset
 *
 * \details
 * 0: No effect
 * 1: Resets the ICM controller.
 *
 * Field: ::VTSS_HICM_ICM_CTRL . SWRST
 */
#define  VTSS_F_HICM_ICM_CTRL_SWRST(x)        VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HICM_ICM_CTRL_SWRST           VTSS_BIT(2)
#define  VTSS_X_HICM_ICM_CTRL_SWRST(x)        VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * DISABLE: ICM Disable Register
 *
 * \details
 * 0: No effect
 * 1: The ICM controller is disabled. If a region is active, this region is
 * terminated.
 *
 * Field: ::VTSS_HICM_ICM_CTRL . DISABLE
 */
#define  VTSS_F_HICM_ICM_CTRL_DISABLE(x)      VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HICM_ICM_CTRL_DISABLE         VTSS_BIT(1)
#define  VTSS_X_HICM_ICM_CTRL_DISABLE(x)      VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * ENABLE: ICM Enable
 *
 * \details
 * 0: No effect
 * 1: When set to one, the ICM controller is activated.
 *
 * Field: ::VTSS_HICM_ICM_CTRL . ENABLE
 */
#define  VTSS_F_HICM_ICM_CTRL_ENABLE(x)       VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HICM_ICM_CTRL_ENABLE          VTSS_BIT(0)
#define  VTSS_X_HICM_ICM_CTRL_ENABLE(x)       VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief ICM Status Register
 *
 * \details
 * Write_Only
 *
 * Register: \a HICM:HICM_REGS:ICM_SR
 */
#define VTSS_HICM_ICM_SR                     VTSS_IOREG(VTSS_TO_HICM,0x2)

/**
 * \brief
 * RMDIS: Region Monitoring Disabled Status
 *
 * \details
 * 0: Region i is being monitored (occurs after integrity check value has
 * been calculated and written to Hash area)
 * 1: Region i monitoring is not being monitored
 *
 * Field: ::VTSS_HICM_ICM_SR . RMDIS_SR
 */
#define  VTSS_F_HICM_ICM_SR_RMDIS_SR(x)       VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HICM_ICM_SR_RMDIS_SR          VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HICM_ICM_SR_RMDIS_SR(x)       VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * RAWRMDIS: Region Monitoring Disabled Raw Status
 *
 * \details
 * 0: Region i monitoring has been activated by writing a 1 in RMEN[i] of
 * ICM_CTRL
 * 1: Region i monitoring has been deactivated by writing a 1 in RMDIS[i]
 * of ICM_CTRL
 *
 * Field: ::VTSS_HICM_ICM_SR . RAWRMDIS
 */
#define  VTSS_F_HICM_ICM_SR_RAWRMDIS(x)       VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HICM_ICM_SR_RAWRMDIS          VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HICM_ICM_SR_RAWRMDIS(x)       VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * ENABLE: ICM Controller Enable Register
 *
 * \details
 * 0: ICM controller is disabled
 * 1: ICM controller is activated
 *
 * Field: ::VTSS_HICM_ICM_SR . ENABLE_SR
 */
#define  VTSS_F_HICM_ICM_SR_ENABLE_SR(x)      VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HICM_ICM_SR_ENABLE_SR         VTSS_BIT(0)
#define  VTSS_X_HICM_ICM_SR_ENABLE_SR(x)      VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief ICM Interrupt Enable Register
 *
 * \details
 * Write_Only
 *
 * Register: \a HICM:HICM_REGS:ICM_IER
 */
#define VTSS_HICM_ICM_IER                    VTSS_IOREG(VTSS_TO_HICM,0x4)

/**
 * \brief
 * URAD: Undefined Register Access Detection Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: The Undefined Register Access interrupt is enabled.
 *
 * Field: ::VTSS_HICM_ICM_IER . URAD
 */
#define  VTSS_F_HICM_ICM_IER_URAD(x)          VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_HICM_ICM_IER_URAD             VTSS_BIT(24)
#define  VTSS_X_HICM_ICM_IER_URAD(x)          VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * RSU: Region Status Updated Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: When RSU[i] is set to one, the region i Status Updated interrupt is
 * enabled.
 *
 * Field: ::VTSS_HICM_ICM_IER . RSU
 */
#define  VTSS_F_HICM_ICM_IER_RSU(x)           VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HICM_ICM_IER_RSU              VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HICM_ICM_IER_RSU(x)           VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * REC: Region End bit Condition Detected Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: When REC[i] is set to one, the region i End bit Condition interrupt
 * is enabled.
 *
 * Field: ::VTSS_HICM_ICM_IER . REC
 */
#define  VTSS_F_HICM_ICM_IER_REC(x)           VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HICM_ICM_IER_REC              VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HICM_ICM_IER_REC(x)           VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * RWC: Region Wrap Condition detected Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: When RWC[i] is set to one, the Region i Wrap Condition interrupt is
 * enabled.
 *
 * Field: ::VTSS_HICM_ICM_IER . RWC
 */
#define  VTSS_F_HICM_ICM_IER_RWC(x)           VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HICM_ICM_IER_RWC              VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HICM_ICM_IER_RWC(x)           VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * RBE: Region Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: When RBE[i] is set to one, the Region i Bus Error interrupt is
 * enabled.
 *
 * Field: ::VTSS_HICM_ICM_IER . RBE
 */
#define  VTSS_F_HICM_ICM_IER_RBE(x)           VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HICM_ICM_IER_RBE              VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HICM_ICM_IER_RBE(x)           VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * RDM: Region Digest Mismatch Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: When RDM[i] is set to one, the Region i Digest Mismatch interrupt is
 * enabled.
 *
 * Field: ::VTSS_HICM_ICM_IER . RDM
 */
#define  VTSS_F_HICM_ICM_IER_RDM(x)           VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HICM_ICM_IER_RDM              VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HICM_ICM_IER_RDM(x)           VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * RHC: Region Hash Completed Interrupt Enable
 *
 * \details
 * 0: No effect
 * 1: When RHC[i] is set to one, the Region i Hash Completed interrupt is
 * enabled.
 *
 * Field: ::VTSS_HICM_ICM_IER . RHC
 */
#define  VTSS_F_HICM_ICM_IER_RHC(x)           VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HICM_ICM_IER_RHC              VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HICM_ICM_IER_RHC(x)           VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief ICM Interrupt Disable Register
 *
 * \details
 * Write_Only
 *
 * Register: \a HICM:HICM_REGS:ICM_IDR
 */
#define VTSS_HICM_ICM_IDR                    VTSS_IOREG(VTSS_TO_HICM,0x5)

/**
 * \brief
 * URAD: Undefined Register Access Detection Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: Undefined Register Access Detection interrupt is disabled.
 *
 * Field: ::VTSS_HICM_ICM_IDR . URAD_IDR
 */
#define  VTSS_F_HICM_ICM_IDR_URAD_IDR(x)      VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_HICM_ICM_IDR_URAD_IDR         VTSS_BIT(24)
#define  VTSS_X_HICM_ICM_IDR_URAD_IDR(x)      VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * RSU: Region Status Updated Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: When RSU[i] is set to one, the region i Status Updated interrupt is
 * disabled.
 *
 * Field: ::VTSS_HICM_ICM_IDR . RSU_IDR
 */
#define  VTSS_F_HICM_ICM_IDR_RSU_IDR(x)       VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HICM_ICM_IDR_RSU_IDR          VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HICM_ICM_IDR_RSU_IDR(x)       VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * REC: Region End bit Condition detected Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: When REC[i] is set to one, the region i End bit Condition interrupt
 * is disabled.
 *
 * Field: ::VTSS_HICM_ICM_IDR . REC_IDR
 */
#define  VTSS_F_HICM_ICM_IDR_REC_IDR(x)       VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HICM_ICM_IDR_REC_IDR          VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HICM_ICM_IDR_REC_IDR(x)       VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * RWC: Region Wrap Condition Detected Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: When RWC[i] is set to one, the Region i Wrap Condition interrupt is
 * disabled.
 *
 * Field: ::VTSS_HICM_ICM_IDR . RWC_IDR
 */
#define  VTSS_F_HICM_ICM_IDR_RWC_IDR(x)       VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HICM_ICM_IDR_RWC_IDR          VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HICM_ICM_IDR_RWC_IDR(x)       VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * RBE: Region Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: When RBE[i] is set to one, the Region i Bus Error interrupt is
 * disabled.
 *
 * Field: ::VTSS_HICM_ICM_IDR . RBE_IDR
 */
#define  VTSS_F_HICM_ICM_IDR_RBE_IDR(x)       VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HICM_ICM_IDR_RBE_IDR          VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HICM_ICM_IDR_RBE_IDR(x)       VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * RDM: Region Digest Mismatch Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: When RDM[i] is set to one, the Region i Digest Mismatch interrupt is
 * disabled.
 *
 * Field: ::VTSS_HICM_ICM_IDR . RDM_IDR
 */
#define  VTSS_F_HICM_ICM_IDR_RDM_IDR(x)       VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HICM_ICM_IDR_RDM_IDR          VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HICM_ICM_IDR_RDM_IDR(x)       VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * RHC: Region Hash Completed Interrupt Disable
 *
 * \details
 * 0: No effect
 * 1: When RHC[i] is set to one, the Region i Hash Completed interrupt is
 * disabled.
 *
 * Field: ::VTSS_HICM_ICM_IDR . RHC_IDR
 */
#define  VTSS_F_HICM_ICM_IDR_RHC_IDR(x)       VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HICM_ICM_IDR_RHC_IDR          VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HICM_ICM_IDR_RHC_IDR(x)       VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief ICM Interrupt Mask Register
 *
 * \details
 * Register: \a HICM:HICM_REGS:ICM_IMR
 */
#define VTSS_HICM_ICM_IMR                    VTSS_IOREG(VTSS_TO_HICM,0x6)

/**
 * \brief
 * URAD: Undefined Register Access Detection Interrupt Mask
 *
 * \details
 * 0: Interrupt is disabled
 * 1: Interrupt is enabled.
 *
 * Field: ::VTSS_HICM_ICM_IMR . URAD_IMR
 */
#define  VTSS_F_HICM_ICM_IMR_URAD_IMR(x)      VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_HICM_ICM_IMR_URAD_IMR         VTSS_BIT(24)
#define  VTSS_X_HICM_ICM_IMR_URAD_IMR(x)      VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * RSU: Region Status Updated Interrupt Mask
 *
 * \details
 * 0: When RSU[i] is set to zero, the interrupt is disabled for region i.
 * 1: When RSU[i] is set to one, the interrupt is enabled for region i.
 *
 * Field: ::VTSS_HICM_ICM_IMR . RSU_IMR
 */
#define  VTSS_F_HICM_ICM_IMR_RSU_IMR(x)       VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HICM_ICM_IMR_RSU_IMR          VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HICM_ICM_IMR_RSU_IMR(x)       VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * REC: Region End bit Condition Detected Interrupt Mask
 *
 * \details
 * 0: When REC[i] is set to zero, the interrupt is disabled for region i.
 * 1: When REC[i] is set to one, the interrupt is enabled for region i.
 *
 * Field: ::VTSS_HICM_ICM_IMR . REC_IMR
 */
#define  VTSS_F_HICM_ICM_IMR_REC_IMR(x)       VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HICM_ICM_IMR_REC_IMR          VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HICM_ICM_IMR_REC_IMR(x)       VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * RWC: Region Wrap Condition Detected Interrupt Mask
 *
 * \details
 * 0: When RWC[i] is set to zero, the interrupt is disabled for region i.
 * 1: When RWC[i] is set to one, the interrupt is enabled for region i.
 *
 * Field: ::VTSS_HICM_ICM_IMR . RWC_IMR
 */
#define  VTSS_F_HICM_ICM_IMR_RWC_IMR(x)       VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HICM_ICM_IMR_RWC_IMR          VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HICM_ICM_IMR_RWC_IMR(x)       VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * RBE: Region Bus Error Interrupt Mask
 *
 * \details
 * 0: When RBE[i] is set to zero, the interrupt is disabled for region i.
 * 1: When RBE[i] is set to one, the interrupt is enabled for region i.
 *
 * Field: ::VTSS_HICM_ICM_IMR . RBE_IMR
 */
#define  VTSS_F_HICM_ICM_IMR_RBE_IMR(x)       VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HICM_ICM_IMR_RBE_IMR          VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HICM_ICM_IMR_RBE_IMR(x)       VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * RDM: Region Digest Mismatch Interrupt Mask
 *
 * \details
 * 0: When RDM[i] is set to zero, the interrupt is disabled for region i.
 * 1: When RDM[i] is set to one, the interrupt is enabled for region i.
 *
 * Field: ::VTSS_HICM_ICM_IMR . RDM_IMR
 */
#define  VTSS_F_HICM_ICM_IMR_RDM_IMR(x)       VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HICM_ICM_IMR_RDM_IMR          VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HICM_ICM_IMR_RDM_IMR(x)       VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * RHC: Region Hash Completed Interrupt Mask
 *
 * \details
 * 0: When RHC[i] is set to zero, the interrupt is disabled for region i.
 * 1: When RHC[i] is set to one, the interrupt is enabled for region i.
 *
 * Field: ::VTSS_HICM_ICM_IMR . RHC_IMR
 */
#define  VTSS_F_HICM_ICM_IMR_RHC_IMR(x)       VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HICM_ICM_IMR_RHC_IMR          VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HICM_ICM_IMR_RHC_IMR(x)       VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief ICM Interrupt Disable Register
 *
 * \details
 * Register: \a HICM:HICM_REGS:ICM_ISR
 */
#define VTSS_HICM_ICM_ISR                    VTSS_IOREG(VTSS_TO_HICM,0x7)

/**
 * \brief
 * URAD: Undefined Register Access Detection StatusThe URAD bit is only
 * reset by the SWRST bit in the ICM_CTRL register.The URAT field in the
 * ICM_UASR indicates the unspecified access type.
 *
 * \details
 * 0: No undefined register access has been detected since the last SWRST.
 * 1: At least one undefined register access has been detected since the
 * last SWRST.
 *
 * Field: ::VTSS_HICM_ICM_ISR . URAD_ISR
 */
#define  VTSS_F_HICM_ICM_ISR_URAD_ISR(x)      VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_HICM_ICM_ISR_URAD_ISR         VTSS_BIT(24)
#define  VTSS_X_HICM_ICM_ISR_URAD_ISR(x)      VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * RSU: Region Status Updated DetectedWhen RSU[i] is set, it indicates that
 * a region status updated condition has been detected.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_ISR . RSU_ISR
 */
#define  VTSS_F_HICM_ICM_ISR_RSU_ISR(x)       VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HICM_ICM_ISR_RSU_ISR          VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HICM_ICM_ISR_RSU_ISR(x)       VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * REC: Region End bit Condition DetectedWhen REC[i] is set, it indicates
 * that an end bit condition has been detected.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_ISR . REC_ISR
 */
#define  VTSS_F_HICM_ICM_ISR_REC_ISR(x)       VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HICM_ICM_ISR_REC_ISR          VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HICM_ICM_ISR_REC_ISR(x)       VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * RWC: Region Wrap Condition DetectedWhen RWC[i] is set, it indicates that
 * a wrap condition has been detected.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_ISR . RWC_ISR
 */
#define  VTSS_F_HICM_ICM_ISR_RWC_ISR(x)       VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HICM_ICM_ISR_RWC_ISR          VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HICM_ICM_ISR_RWC_ISR(x)       VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * RBE: Region Bus ErrorWhen RBE[i] is set, it indicates that a bus error
 * has been detected while hashing memory region i.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_ISR . RBE_ISR
 */
#define  VTSS_F_HICM_ICM_ISR_RBE_ISR(x)       VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HICM_ICM_ISR_RBE_ISR          VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HICM_ICM_ISR_RBE_ISR(x)       VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * RDM: Region Digest MismatchWhen RDM[i] is set, it indicates that there
 * is a digest comparison mismatch between the hash value of the region
 * with identifieri and the reference value located in the Hash Area.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_ISR . RDM_ISR
 */
#define  VTSS_F_HICM_ICM_ISR_RDM_ISR(x)       VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HICM_ICM_ISR_RDM_ISR          VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HICM_ICM_ISR_RDM_ISR(x)       VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * RHC: Region Hash CompletedWhen RHC[i] is set, it indicates that the ICM
 * has completed the region with identifier i.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_ISR . RHC_ISR
 */
#define  VTSS_F_HICM_ICM_ISR_RHC_ISR(x)       VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HICM_ICM_ISR_RHC_ISR          VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HICM_ICM_ISR_RHC_ISR(x)       VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief ICM Undefined Access Status Register
 *
 * \details
 * Register: \a HICM:HICM_REGS:ICM_UASR
 */
#define VTSS_HICM_ICM_UASR                   VTSS_IOREG(VTSS_TO_HICM,0x8)

/**
 * \brief
 * URAT: Undefined Register Access TraceOnly the first Undefined Register
 * Access Trace is available through the URAT field.The URAT field is only
 * reset by the SWRST bit in the ICM_CTRL register.
 *
 * \details
 * 0: UNSPEC_STRUCT_MEMBER: Unspecified structure member set to one
 * detected when the descriptor is loaded.
 * 1: ICM_CFG_MODIFIED ICM_CFG: modified during active monitoring.
 * 2: ICM_DSCR_MODIFIED ICM_DSCR: modified during active monitoring.
 * 3: ICM_HASH_MODIFIED ICM_HASH: modified during active monitoring
 * 4: READ_ACCESS: Write-only register read access
 *
 * Field: ::VTSS_HICM_ICM_UASR . URAT
 */
#define  VTSS_F_HICM_ICM_UASR_URAT(x)         VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_HICM_ICM_UASR_URAT            VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_HICM_ICM_UASR_URAT(x)         VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief ICM Descriptor Area Start Address Register
 *
 * \details
 * Register: \a HICM:HICM_REGS:ICM_DSCR
 */
#define VTSS_HICM_ICM_DSCR                   VTSS_IOREG(VTSS_TO_HICM,0xc)

/**
 * \brief
 * DASA: Descriptor Area Start AddressThe start address is a multiple of
 * the total size of the data structure (64 bytes).
 *
 * \details
 * Field: ::VTSS_HICM_ICM_DSCR . DASA
 */
#define  VTSS_F_HICM_ICM_DSCR_DASA(x)         VTSS_ENCODE_BITFIELD(x,6,26)
#define  VTSS_M_HICM_ICM_DSCR_DASA            VTSS_ENCODE_BITMASK(6,26)
#define  VTSS_X_HICM_ICM_DSCR_DASA(x)         VTSS_EXTRACT_BITFIELD(x,6,26)


/**
 * \brief ICM Hash Area Start Address Register
 *
 * \details
 * Register: \a HICM:HICM_REGS:ICM_HASH
 */
#define VTSS_HICM_ICM_HASH                   VTSS_IOREG(VTSS_TO_HICM,0xd)

/**
 * \brief
 * HASA: Hash Area Start AddressThis field points at the Hash memory
 * location. The address must be a multiple of 128 bytes.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_HASH . HASA
 */
#define  VTSS_F_HICM_ICM_HASH_HASA(x)         VTSS_ENCODE_BITFIELD(x,7,25)
#define  VTSS_M_HICM_ICM_HASH_HASA            VTSS_ENCODE_BITMASK(7,25)
#define  VTSS_X_HICM_ICM_HASH_HASA(x)         VTSS_EXTRACT_BITFIELD(x,7,25)


/**
 * \brief ICM User Initial Hash Value Register0
 *
 * \details
 * Write_Only
 *
 * Register: \a HICM:HICM_REGS:ICM_UIHVAL0
 */
#define VTSS_HICM_ICM_UIHVAL0                VTSS_IOREG(VTSS_TO_HICM,0xe)

/**
 * \brief
 * VAL: Initial Hash ValueWhen UIHASH bit of IMC_CFG register is set, the
 * Initial Hash Value is user-programmable.0x67452301 SHA1
 * algorithm0xC1059ED8 SHA224 algorithm0x6A09E667 SHA256 algorithm
 *
 * \details
 * Field: ::VTSS_HICM_ICM_UIHVAL0 . VAL0
 */
#define  VTSS_F_HICM_ICM_UIHVAL0_VAL0(x)      (x)
#define  VTSS_M_HICM_ICM_UIHVAL0_VAL0         0xffffffff
#define  VTSS_X_HICM_ICM_UIHVAL0_VAL0(x)      (x)


/**
 * \brief ICM User Initial Hash Value Register1
 *
 * \details
 * Write_Only
 *
 * Register: \a HICM:HICM_REGS:ICM_UIHVAL1
 */
#define VTSS_HICM_ICM_UIHVAL1                VTSS_IOREG(VTSS_TO_HICM,0xf)

/**
 * \brief
 * VAL: Initial Hash ValueWhen UIHASH bit of IMC_CFG register is set, the
 * Initial Hash Value is user-programmable.0xEFCDAB89 SHA1
 * algorithm0x367CD507 SHA224 algorithm0xBB67AE85 SHA256 algorithm
 *
 * \details
 * Field: ::VTSS_HICM_ICM_UIHVAL1 . VAL1
 */
#define  VTSS_F_HICM_ICM_UIHVAL1_VAL1(x)      (x)
#define  VTSS_M_HICM_ICM_UIHVAL1_VAL1         0xffffffff
#define  VTSS_X_HICM_ICM_UIHVAL1_VAL1(x)      (x)


/**
 * \brief ICM User Initial Hash Value Register2
 *
 * \details
 * Write_Only
 *
 * Register: \a HICM:HICM_REGS:ICM_UIHVAL2
 */
#define VTSS_HICM_ICM_UIHVAL2                VTSS_IOREG(VTSS_TO_HICM,0x10)

/**
 * \brief
 * VAL: Initial Hash ValueWhen UIHASH bit of IMC_CFG register is set, the
 * Initial Hash Value is user-programmable.0x98BADCFE SHA1
 * algorithm0x3070DD17 SHA224 algorithm0x3C6EF372 SHA256 algorithm
 *
 * \details
 * Field: ::VTSS_HICM_ICM_UIHVAL2 . VAL2
 */
#define  VTSS_F_HICM_ICM_UIHVAL2_VAL2(x)      (x)
#define  VTSS_M_HICM_ICM_UIHVAL2_VAL2         0xffffffff
#define  VTSS_X_HICM_ICM_UIHVAL2_VAL2(x)      (x)


/**
 * \brief ICM User Initial Hash Value Register3
 *
 * \details
 * Write_Only
 *
 * Register: \a HICM:HICM_REGS:ICM_UIHVAL3
 */
#define VTSS_HICM_ICM_UIHVAL3                VTSS_IOREG(VTSS_TO_HICM,0x11)

/**
 * \brief
 * VAL: Initial Hash ValueWhen UIHASH bit of IMC_CFG register is set, the
 * Initial Hash Value is user-programmable.0x10325476 SHA1
 * algorithm0xF70E5939 SHA224 algorithm0xA54FF53A SHA256 algorithm
 *
 * \details
 * Field: ::VTSS_HICM_ICM_UIHVAL3 . VAL3
 */
#define  VTSS_F_HICM_ICM_UIHVAL3_VAL3(x)      (x)
#define  VTSS_M_HICM_ICM_UIHVAL3_VAL3         0xffffffff
#define  VTSS_X_HICM_ICM_UIHVAL3_VAL3(x)      (x)


/**
 * \brief ICM User Initial Hash Value Register4
 *
 * \details
 * Write_Only
 *
 * Register: \a HICM:HICM_REGS:ICM_UIHVAL4
 */
#define VTSS_HICM_ICM_UIHVAL4                VTSS_IOREG(VTSS_TO_HICM,0x12)

/**
 * \brief
 * VAL: Initial Hash ValueWhen UIHASH bit of IMC_CFG register is set, the
 * Initial Hash Value is user-programmable.0xC3D2E1F0 SHA1
 * algorithm0xFFC00B31 SHA224 algorithm0x510E527F SHA256 algorithm
 *
 * \details
 * Field: ::VTSS_HICM_ICM_UIHVAL4 . VAL4
 */
#define  VTSS_F_HICM_ICM_UIHVAL4_VAL4(x)      (x)
#define  VTSS_M_HICM_ICM_UIHVAL4_VAL4         0xffffffff
#define  VTSS_X_HICM_ICM_UIHVAL4_VAL4(x)      (x)


/**
 * \brief ICM User Initial Hash Value Register5
 *
 * \details
 * Write_Only
 *
 * Register: \a HICM:HICM_REGS:ICM_UIHVAL5
 */
#define VTSS_HICM_ICM_UIHVAL5                VTSS_IOREG(VTSS_TO_HICM,0x13)

/**
 * \brief
 * VAL: Initial Hash ValueWhen UIHASH bit of IMC_CFG register is set, the
 * Initial Hash Value is user-programmable.0x68581511 SHA224
 * algorithm0x9B05688C SHA256 algorithm
 *
 * \details
 * Field: ::VTSS_HICM_ICM_UIHVAL5 . VAL5
 */
#define  VTSS_F_HICM_ICM_UIHVAL5_VAL5(x)      (x)
#define  VTSS_M_HICM_ICM_UIHVAL5_VAL5         0xffffffff
#define  VTSS_X_HICM_ICM_UIHVAL5_VAL5(x)      (x)


/**
 * \brief ICM User Initial Hash Value Register6
 *
 * \details
 * Write_Only
 *
 * Register: \a HICM:HICM_REGS:ICM_UIHVAL6
 */
#define VTSS_HICM_ICM_UIHVAL6                VTSS_IOREG(VTSS_TO_HICM,0x14)

/**
 * \brief
 * VAL: Initial Hash ValueWhen UIHASH bit of IMC_CFG register is set, the
 * Initial Hash Value is user-programmable.0x64F98FA7 SHA224
 * algorithm0x1F83D9AB SHA256 algorithm
 *
 * \details
 * Field: ::VTSS_HICM_ICM_UIHVAL6 . VAL6
 */
#define  VTSS_F_HICM_ICM_UIHVAL6_VAL6(x)      (x)
#define  VTSS_M_HICM_ICM_UIHVAL6_VAL6         0xffffffff
#define  VTSS_X_HICM_ICM_UIHVAL6_VAL6(x)      (x)


/**
 * \brief ICM User Initial Hash Value Register7
 *
 * \details
 * Write_Only
 *
 * Register: \a HICM:HICM_REGS:ICM_UIHVAL7
 */
#define VTSS_HICM_ICM_UIHVAL7                VTSS_IOREG(VTSS_TO_HICM,0x15)

/**
 * \brief
 * VAL: Initial Hash ValueWhen UIHASH bit of IMC_CFG register is set, the
 * Initial Hash Value is user-programmable.0xBEFA4FA4 SHA224
 * algorithm0x5BE0CD19 SHA256 algorithm
 *
 * \details
 * Field: ::VTSS_HICM_ICM_UIHVAL7 . VAL7
 */
#define  VTSS_F_HICM_ICM_UIHVAL7_VAL7(x)      (x)
#define  VTSS_M_HICM_ICM_UIHVAL7_VAL7         0xffffffff
#define  VTSS_X_HICM_ICM_UIHVAL7_VAL7(x)      (x)


/**
 * \brief Address Size Register
 *
 * \details
 * Register: \a HICM:HICM_REGS:ICM_ADDRSIZE
 */
#define VTSS_HICM_ICM_ADDRSIZE               VTSS_IOREG(VTSS_TO_HICM,0x3b)

/**
 * \brief
 * ADDRSIZE: Peripheral Bus Address Area SizeReserved. Value subject to
 * change. No functionality associated. The returned value corresponds to
 * the number of bytesmapped into the ICM address space. It could be an
 * integer in range 16384, 8192, 4096, 2048, 1024, 512, 256.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_ADDRSIZE . ADDRSIZE
 */
#define  VTSS_F_HICM_ICM_ADDRSIZE_ADDRSIZE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HICM_ICM_ADDRSIZE_ADDRSIZE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HICM_ICM_ADDRSIZE_ADDRSIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief IP Name 1 Register
 *
 * \details
 * Register: \a HICM:HICM_REGS:ICM_IPNAME1
 */
#define VTSS_HICM_ICM_IPNAME1                VTSS_IOREG(VTSS_TO_HICM,0x3c)

/**
 * \brief
 * IPNAME: IP Name in ASCII FormatReserved. Value subject to change. No
 * functionality associated. The default in ASCII format is “HICM.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_IPNAME1 . IPNAME
 */
#define  VTSS_F_HICM_ICM_IPNAME1_IPNAME(x)    (x)
#define  VTSS_M_HICM_ICM_IPNAME1_IPNAME       0xffffffff
#define  VTSS_X_HICM_ICM_IPNAME1_IPNAME(x)    (x)


/**
 * \brief IP Name 2 Register
 *
 * \details
 * Register: \a HICM:HICM_REGS:ICM_IPNAME2
 */
#define VTSS_HICM_ICM_IPNAME2                VTSS_IOREG(VTSS_TO_HICM,0x3d)

/**
 * \brief
 * IPNAME: IP Name in ASCII FormatReserved. Value subject to change. No
 * functionality associated. The default in ASCII format is a string of
 * four blank/spacecharacters.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_IPNAME2 . IPNAME2
 */
#define  VTSS_F_HICM_ICM_IPNAME2_IPNAME2(x)   (x)
#define  VTSS_M_HICM_ICM_IPNAME2_IPNAME2      0xffffffff
#define  VTSS_X_HICM_ICM_IPNAME2_IPNAME2(x)   (x)


/**
 * \brief Feature Register
 *
 * \details
 * Register: \a HICM:HICM_REGS:ICM_FEATURES
 */
#define VTSS_HICM_ICM_FEATURES               VTSS_IOREG(VTSS_TO_HICM,0x3e)

/**
 * \brief
 * HSHA512: SHA512 Hardcoded Mode0: All SHAs can be processed or IP version
 * is 3XX.1: Indicates which ALGO is hardcoded in IP version V4XX.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_FEATURES . HSHA512
 */
#define  VTSS_F_HICM_ICM_FEATURES_HSHA512(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_HICM_ICM_FEATURES_HSHA512     VTSS_BIT(20)
#define  VTSS_X_HICM_ICM_FEATURES_HSHA512(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * HSHA384: SHA384 Hardcoded Mode0: All SHAs can be processed or IP version
 * is 3XX.1: Indicates which ALGO is hardcoded in IP version V4XX.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_FEATURES . HSHA384
 */
#define  VTSS_F_HICM_ICM_FEATURES_HSHA384(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_HICM_ICM_FEATURES_HSHA384     VTSS_BIT(19)
#define  VTSS_X_HICM_ICM_FEATURES_HSHA384(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * HSHA256: SHA256 Hardcoded Mode0: All SHAs can be processed or IP version
 * is 3XX.1: Indicates which ALGO is hardcoded in IP version V4XX
 *
 * \details
 * Field: ::VTSS_HICM_ICM_FEATURES . HSHA256
 */
#define  VTSS_F_HICM_ICM_FEATURES_HSHA256(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HICM_ICM_FEATURES_HSHA256     VTSS_BIT(18)
#define  VTSS_X_HICM_ICM_FEATURES_HSHA256(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * HSHA224: SHA224 Hardcoded Mode0: All SHAs can be processed or IP version
 * is 3XX.1: Indicates which ALGO is hardcoded in IP version V4XX.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_FEATURES . HSHA224
 */
#define  VTSS_F_HICM_ICM_FEATURES_HSHA224(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_HICM_ICM_FEATURES_HSHA224     VTSS_BIT(17)
#define  VTSS_X_HICM_ICM_FEATURES_HSHA224(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * HSHA1: SHA1 Hardcoded Mode0: All SHAs can be processed or IP version is
 * 3XX.1: Indicates which ALGO is hardcoded in IP version V4XX.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_FEATURES . HSHA1
 */
#define  VTSS_F_HICM_ICM_FEATURES_HSHA1(x)    VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_HICM_ICM_FEATURES_HSHA1       VTSS_BIT(16)
#define  VTSS_X_HICM_ICM_FEATURES_HSHA1(x)    VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * PDCOFF0C: PDC Offset is 0x0C0: The PDC Write Register Offset is 0x40.1:
 * The PDC Write Register Offset is 0x0C for an easier integration in a
 * product having many modules connected to thePDC.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_FEATURES . PDCOFF0C
 */
#define  VTSS_F_HICM_ICM_FEATURES_PDCOFF0C(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_HICM_ICM_FEATURES_PDCOFF0C    VTSS_BIT(9)
#define  VTSS_X_HICM_ICM_FEATURES_PDCOFF0C(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * BTYP: Bridge Type0: The module interfaces with an ASB2APB Atmel
 * bridge.1: The module interfaces with an AHB2APB bridge.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_FEATURES . BTYP
 */
#define  VTSS_F_HICM_ICM_FEATURES_BTYP(x)     VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_HICM_ICM_FEATURES_BTYP        VTSS_BIT(8)
#define  VTSS_X_HICM_ICM_FEATURES_BTYP(x)     VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * SI: Scan IntrusionValue subject to change. No functionality
 * associated.0: There is no possibility to access any of the URAD and URAT
 * bits.1: The URAD/URAT logic and access to these bits is possible.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_FEATURES . SI
 */
#define  VTSS_F_HICM_ICM_FEATURES_SI(x)       VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_HICM_ICM_FEATURES_SI          VTSS_BIT(7)
#define  VTSS_X_HICM_ICM_FEATURES_SI(x)       VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * EF: Embedded LFSRValue subject to change. No functionality associated.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_FEATURES . EF
 */
#define  VTSS_F_HICM_ICM_FEATURES_EF(x)       VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HICM_ICM_FEATURES_EF          VTSS_BIT(6)
#define  VTSS_X_HICM_ICM_FEATURES_EF(x)       VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * NAIS: No Access to Intermediate StateValue subject to change. No
 * functionality associated.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_FEATURES . NAIS
 */
#define  VTSS_F_HICM_ICM_FEATURES_NAIS(x)     VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_HICM_ICM_FEATURES_NAIS        VTSS_BIT(5)
#define  VTSS_X_HICM_ICM_FEATURES_NAIS(x)     VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * PDC: Peripheral DMA LogicValue subject to change. No functionality
 * associated.0: There is no possibility to trigger a PDC.1: PDC triggers
 * are generated.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_FEATURES . PDC
 */
#define  VTSS_F_HICM_ICM_FEATURES_PDC(x)      VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HICM_ICM_FEATURES_PDC         VTSS_BIT(4)
#define  VTSS_X_HICM_ICM_FEATURES_PDC(x)      VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * HDPP: Hardcoded Processing PeriodValue subject to change. No
 * functionality associated.0: CFGPP equals 1 or longest processing period
 * (326 or 265 clock cycles) is used to perform SHA when CFGPP equals 0.1:
 * CFGPP equals 0 and shortest processing period (85 or 72 clock cycles) is
 * used to perform SHA.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_FEATURES . HDPP
 */
#define  VTSS_F_HICM_ICM_FEATURES_HDPP(x)     VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HICM_ICM_FEATURES_HDPP        VTSS_BIT(3)
#define  VTSS_X_HICM_ICM_FEATURES_HDPP(x)     VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * CFGPP: Configurable Processing PeriodValue subject to change. No
 * functionality associated.0: Only one processing period can be used. The
 * ICM_RCFG has no PROCDLY configuration bit.1: Two processing periods can
 * be used. The PROCDLY bit in mode register can be written.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_FEATURES . CFGPP
 */
#define  VTSS_F_HICM_ICM_FEATURES_CFGPP(x)    VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HICM_ICM_FEATURES_CFGPP       VTSS_BIT(2)
#define  VTSS_X_HICM_ICM_FEATURES_CFGPP(x)    VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * RFU: Reserved for Future UseValue subject to change. No functionality
 * associated. May report 1 or 0.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_FEATURES . RFU
 */
#define  VTSS_F_HICM_ICM_FEATURES_RFU(x)      VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HICM_ICM_FEATURES_RFU         VTSS_BIT(1)
#define  VTSS_X_HICM_ICM_FEATURES_RFU(x)      VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * CFGALGO: Configurable AlgorithmsValue subject to change. No
 * functionality associated.0: Only one SHA algorithm can be processed. The
 * ICM_RCFG has no ALGO configuration bit.1: All SHA algorithms can be
 * processed.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_FEATURES . CFGALGO
 */
#define  VTSS_F_HICM_ICM_FEATURES_CFGALGO(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HICM_ICM_FEATURES_CFGALGO     VTSS_BIT(0)
#define  VTSS_X_HICM_ICM_FEATURES_CFGALGO(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Version Register
 *
 * \details
 * Register: \a HICM:HICM_REGS:ICM_VERSION
 */
#define VTSS_HICM_ICM_VERSION                VTSS_IOREG(VTSS_TO_HICM,0x3f)

/**
 * \brief
 * MFN: Metal Fix NumberReserved. Value subject to change. No functionality
 * associated.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_VERSION . MFN
 */
#define  VTSS_F_HICM_ICM_VERSION_MFN(x)       VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_HICM_ICM_VERSION_MFN          VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_HICM_ICM_VERSION_MFN(x)       VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * VERSION: Version of the Hardware ModuleReserved. Value subject to
 * change. No functionality associated. This is the Atmel internal version
 * of the macrocell.
 *
 * \details
 * Field: ::VTSS_HICM_ICM_VERSION . VERSION
 */
#define  VTSS_F_HICM_ICM_VERSION_VERSION(x)   VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_HICM_ICM_VERSION_VERSION      VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_HICM_ICM_VERSION_VERSION(x)   VTSS_EXTRACT_BITFIELD(x,0,12)


#endif /* _VTSS_LAGUNA_REGS_HICM_H_ */
