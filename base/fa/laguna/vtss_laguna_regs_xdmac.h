// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_XDMAC_H_
#define _VTSS_LAGUNA_REGS_XDMAC_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a XDMAC
 *
 * The DMA Controller (XDMAC) is an AXI protocol central direct memory access
 * controller. It performs peripheral data transfer and memory move
 * operations over one or two bus ports through the unidirectional
 * communication channel. Each channel is fully programmable and provides
 * both peripheral or memory-to-memory transfers. The channel features are
 * configurable at implementation.
 *
 ***********************************************************************/

/**
 * Register Group: \a XDMAC:XDMAC_REG
 *
 * Extensible DMA Controller
 */


/**
 * \brief Global Type Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GTYPE
 */
#define VTSS_XDMAC_XDMAC_GTYPE               VTSS_IOREG(VTSS_TO_XDMAC,0x0)

/**
 * \brief
 * Number of Peripheral Requests Minus One
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_GTYPE . NB_REQ
 */
#define  VTSS_F_XDMAC_XDMAC_GTYPE_NB_REQ(x)   VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_XDMAC_XDMAC_GTYPE_NB_REQ      VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_XDMAC_XDMAC_GTYPE_NB_REQ(x)   VTSS_EXTRACT_BITFIELD(x,16,7)

/**
 * \brief
 * Number of Bytes
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_GTYPE . FIFO_SZ
 */
#define  VTSS_F_XDMAC_XDMAC_GTYPE_FIFO_SZ(x)  VTSS_ENCODE_BITFIELD(x,5,11)
#define  VTSS_M_XDMAC_XDMAC_GTYPE_FIFO_SZ     VTSS_ENCODE_BITMASK(5,11)
#define  VTSS_X_XDMAC_XDMAC_GTYPE_FIFO_SZ(x)  VTSS_EXTRACT_BITFIELD(x,5,11)

/**
 * \brief
 * Number of Channels Minus One
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_GTYPE . NB_CH
 */
#define  VTSS_F_XDMAC_XDMAC_GTYPE_NB_CH(x)    VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_XDMAC_XDMAC_GTYPE_NB_CH       VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_XDMAC_XDMAC_GTYPE_NB_CH(x)    VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief Global Configuration Register
 *
 * \details
 * Notes:
 * 1. WRxP fields: to maximize system performance and avoid system head of
 * line blocking, verify that
 * (WRHP+1)+(WRMP+1)+(WRLP+1) is less than or equal to the system buffering
 * capability (i.e., the size of addresses and
 * write data buffer in the system bus interconnect).
 * 2. RDSG/RDxP fields: to maximize system performance and avoid system
 * head of line blocking, verify that
 * (RDSG+1)(RDHP+1)(RDMP+1)+(RDLP+1) is less than or equal to the system
 * read buffering capability (i.e., the size of
 * addresses buffer in the system bus interconnect).
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GCFG
 */
#define VTSS_XDMAC_XDMAC_GCFG                VTSS_IOREG(VTSS_TO_XDMAC,0x1)

/**
 * \brief
 * Read Queue Scatter Gather Outstanding LimitRDSG+1 is the maximum number
 * of active transactions for descriptor read access.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_GCFG . RDSG
 */
#define  VTSS_F_XDMAC_XDMAC_GCFG_RDSG(x)      VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_XDMAC_XDMAC_GCFG_RDSG         VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_XDMAC_XDMAC_GCFG_RDSG(x)      VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \brief
 * Read Queue Low Priority Outstanding LimitRDLP+1 is the maximum number of
 * active transactions for read access (memory) of a memory-to-memory
 * transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_GCFG . RDLP
 */
#define  VTSS_F_XDMAC_XDMAC_GCFG_RDLP(x)      VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_XDMAC_XDMAC_GCFG_RDLP         VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_XDMAC_XDMAC_GCFG_RDLP(x)      VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * Read Queue Medium Priority Outstanding LimitRDMP+1 is the maximum number
 * of active transactions for read access (memory) of a
 * memory-to-peripheral transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_GCFG . RDMP
 */
#define  VTSS_F_XDMAC_XDMAC_GCFG_RDMP(x)      VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_XDMAC_XDMAC_GCFG_RDMP         VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_XDMAC_XDMAC_GCFG_RDMP(x)      VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * Read Queue High Priority Outstanding LimitRDHP+1 is the maximum number
 * of active transactions for read access (peripheral) of a
 * peripheral-to-memory transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_GCFG . RDHP
 */
#define  VTSS_F_XDMAC_XDMAC_GCFG_RDHP(x)      VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_XDMAC_XDMAC_GCFG_RDHP         VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_XDMAC_XDMAC_GCFG_RDHP(x)      VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Write Queue Low Priority Outstanding LimitWRLP+1 is the maximum number
 * of active transactions for write access (memory) of a memory-to-memory
 * transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_GCFG . WRLP
 */
#define  VTSS_F_XDMAC_XDMAC_GCFG_WRLP(x)      VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_XDMAC_XDMAC_GCFG_WRLP         VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_XDMAC_XDMAC_GCFG_WRLP(x)      VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * Write Queue Medium Priority Outstanding LimitWRMP+1 is the maximum
 * number of active transactions for write access (memory) of
 * peripheral-to-memory transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_GCFG . WRMP
 */
#define  VTSS_F_XDMAC_XDMAC_GCFG_WRMP(x)      VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_XDMAC_XDMAC_GCFG_WRMP         VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_XDMAC_XDMAC_GCFG_WRMP(x)      VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * Write Queue High Priority Outstanding LimitWRHP+1 is the maximum number
 * of active transactions for write access (peripheral) of a
 * memory-to-peripheral transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_GCFG . WRHP
 */
#define  VTSS_F_XDMAC_XDMAC_GCFG_WRHP(x)      VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_XDMAC_XDMAC_GCFG_WRHP         VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_XDMAC_XDMAC_GCFG_WRHP(x)      VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * Bus Interface Clock Gating Disable
 *
 * \details
 * 0: The automatic clock gating is enabled for the system bus interface.
 * 1: The automatic clock gating is disabled for the system bus interface.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GCFG . CGDISIF
 */
#define  VTSS_F_XDMAC_XDMAC_GCFG_CGDISIF(x)   VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_GCFG_CGDISIF      VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_GCFG_CGDISIF(x)   VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * FIFO Clock Gating Disable
 *
 * \details
 * 0: The automatic clock gating is enabled for the main FIFO.
 * 1: The automatic clock gating is disabled for the main FIFO.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GCFG . CGDISFIFO
 */
#define  VTSS_F_XDMAC_XDMAC_GCFG_CGDISFIFO(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_GCFG_CGDISFIFO    VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_GCFG_CGDISFIFO(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Pipeline Clock Gating Disable
 *
 * \details
 * 0: The automatic clock gating is enabled for the main pipeline.
 * 1: The automatic clock gating is disabled for the main pipeline.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GCFG . CGDISPIPE
 */
#define  VTSS_F_XDMAC_XDMAC_GCFG_CGDISPIPE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_GCFG_CGDISPIPE    VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_GCFG_CGDISPIPE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Configuration Registers Clock Gating Disable
 *
 * \details
 * 0: The automatic clock gating is enabled for the configuration
 * registers.
 * 1: The automatic clock gating is disabled for the configuration
 * registers.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GCFG . CGDISREG
 */
#define  VTSS_F_XDMAC_XDMAC_GCFG_CGDISREG(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_GCFG_CGDISREG     VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_GCFG_CGDISREG(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Global Weighted Arbiter Configuration Register
 *
 * \details
 * Notes:
 * 1. PW0/1: when a memory-to-peripheral transaction occurs, the peripheral
 * write transaction may be asserted at the same time
 * as a memory write transaction. The write port arbiter grants bus access
 * to the highest transaction weight first, then the internal
 * weight counter is decremented. When the internal weight counter reaches
 * 0, it is reloaded with PWx. If PW0=0 and PW1
 * = 0, the arbitration method is round-robin.
 * 2. PW2/3: When a peripheral-to-memory transaction occurs, the peripheral
 * read transaction may be asserted at the same time
 * as a memory read transaction. The Read Port Arbiter grants bus access to
 * the highest transaction weight first, then the internal
 * weight counter is decremented. When the internal weight counter reaches
 * 0, it is reloaded with PWx. If PW2=0 and PW3
 * = 0, the arbitration method is round-robin.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GWAC
 */
#define VTSS_XDMAC_XDMAC_GWAC                VTSS_IOREG(VTSS_TO_XDMAC,0x2)

/**
 * \brief
 * PW3: Pool Weight 3Memory transaction weight for read port arbiter. This
 * is exactly the peripheral read transaction weight of a memory-to-memory
 * transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_GWAC . PW3
 */
#define  VTSS_F_XDMAC_XDMAC_GWAC_PW3(x)       VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_XDMAC_XDMAC_GWAC_PW3          VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_XDMAC_XDMAC_GWAC_PW3(x)       VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * PW2: Pool Weight 2Peripheral transaction weight for read port arbiter.
 * This is exactly the peripheral read transaction weight of a
 * peripheral-to-memory transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_GWAC . PW2
 */
#define  VTSS_F_XDMAC_XDMAC_GWAC_PW2(x)       VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_XDMAC_XDMAC_GWAC_PW2          VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_XDMAC_XDMAC_GWAC_PW2(x)       VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * PW1: Pool Weight 1Memory transaction weight for write port arbiter. This
 * is exactly the memory write transaction weight of a memory-to-memory
 * transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_GWAC . PW1
 */
#define  VTSS_F_XDMAC_XDMAC_GWAC_PW1(x)       VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_XDMAC_XDMAC_GWAC_PW1          VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_XDMAC_XDMAC_GWAC_PW1(x)       VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * Pool Weight 0Peripheral transaction weight for write port arbiter. This
 * is exactly the peripheral write transaction weight of a
 * memory-to-peripheral transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_GWAC . PW0
 */
#define  VTSS_F_XDMAC_XDMAC_GWAC_PW0(x)       VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_XDMAC_XDMAC_GWAC_PW0          VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_XDMAC_XDMAC_GWAC_PW0(x)       VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Global Interrupt Enable Regsiter
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GIE
 */
#define VTSS_XDMAC_XDMAC_GIE                 VTSS_IOREG(VTSS_TO_XDMAC,0x3)

/**
 * \brief
 * IEx: XDMAC Channel x Interrupt Enable
 *
 * \details
 * 0: This bit has no effect. The Channel x Interrupt Mask bit
 * (XDMAC_GIM.IMx) is not modified.
 * 1: The corresponding mask bit is set. The XDMAC Channel x Interrupt
 * Status register (XDMAC_GIS) can generate an interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GIE . IEX
 */
#define  VTSS_F_XDMAC_XDMAC_GIE_IEX(x)        VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_GIE_IEX           VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_GIE_IEX(x)        VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Global Interrupt Disable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GID
 */
#define VTSS_XDMAC_XDMAC_GID                 VTSS_IOREG(VTSS_TO_XDMAC,0x4)

/**
 * \brief
 * IDx: XDMAC Channel x Interrupt Disable
 *
 * \details
 * 0: This bit has no effect. The Channel x Interrupt Mask bit
 * (XDMAC_GIM.IMx) is not modified.
 * 1: The corresponding mask bit is reset. The Channel x Interrupt Status
 * register interrupt (XDMAC_GIS) is masked.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GID . IDX
 */
#define  VTSS_F_XDMAC_XDMAC_GID_IDX(x)        VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_GID_IDX           VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_GID_IDX(x)        VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Global Interrupt Mask Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GIM
 */
#define VTSS_XDMAC_XDMAC_GIM                 VTSS_IOREG(VTSS_TO_XDMAC,0x5)

/**
 * \brief
 * IMx: XDMAC Channel x Interrupt Mask
 *
 * \details
 * 0: This bit indicates that the channel x interrupt source is masked. The
 * interrupt line is not raised.
 * 1: This bit indicates that the channel x interrupt source is unmasked.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GIM . IMX
 */
#define  VTSS_F_XDMAC_XDMAC_GIM_IMX(x)        VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_GIM_IMX           VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_GIM_IMX(x)        VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Global Interrupt Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GIS
 */
#define VTSS_XDMAC_XDMAC_GIS                 VTSS_IOREG(VTSS_TO_XDMAC,0x6)

/**
 * \brief
 * ISx: XDMAC Channel x Interrupt Status
 *
 * \details
 * 0: This bit indicates that either the interrupt source is masked at the
 * channel level or no interrupt is pending for channel x.
 * 1: This bit indicates that an interrupt is pending for the channel x.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GIS . ISX
 */
#define  VTSS_F_XDMAC_XDMAC_GIS_ISX(x)        VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_GIS_ISX           VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_GIS_ISX(x)        VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Global Channel Enable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GE
 */
#define VTSS_XDMAC_XDMAC_GE                  VTSS_IOREG(VTSS_TO_XDMAC,0x7)

/**
 * \brief
 * ENx: XDMAC Channel x Enable
 *
 * \details
 * 0: This bit has no effect.
 * 1: Enables channel x. This operation is permitted if the Channel x
 * Status bit (XDMAC_GS.STx) was read as 0.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GE . ENX
 */
#define  VTSS_F_XDMAC_XDMAC_GE_ENX(x)         VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_GE_ENX            VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_GE_ENX(x)         VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Global Channel Disable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GD
 */
#define VTSS_XDMAC_XDMAC_GD                  VTSS_IOREG(VTSS_TO_XDMAC,0x8)

/**
 * \brief
 * DIx: XDMAC Channel x Disable
 *
 * \details
 * 0: This bit has no effect.
 * 1: Disables channel x.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GD . DIX
 */
#define  VTSS_F_XDMAC_XDMAC_GD_DIX(x)         VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_GD_DIX            VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_GD_DIX(x)         VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Global Channel Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GS
 */
#define VTSS_XDMAC_XDMAC_GS                  VTSS_IOREG(VTSS_TO_XDMAC,0x9)

/**
 * \brief
 * STx: XDMAC Channel x Status
 *
 * \details
 * 0: This bit indicates that the channel x is disabled.
 * 1: This bit indicates that the channel x is enabled. If a channel
 * disable request is issued, this bit remains asserted until pending
 * transaction is completed.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GS . STX
 */
#define  VTSS_F_XDMAC_XDMAC_GS_STX(x)         VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_GS_STX            VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_GS_STX(x)         VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Global Channel Read Suspend Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GRSS
 */
#define VTSS_XDMAC_XDMAC_GRSS                VTSS_IOREG(VTSS_TO_XDMAC,0xa)

/**
 * \brief
 * RSSx: XDMAC Channel x Read Suspend Status
 *
 * \details
 * 0: The read channel is not suspended.
 * 1: The source requests for channel x are no longer serviced by the
 * system scheduler.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GRSS . RSSX
 */
#define  VTSS_F_XDMAC_XDMAC_GRSS_RSSX(x)      VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_GRSS_RSSX         VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_GRSS_RSSX(x)      VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Global Channel Write Suspend Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GWSS
 */
#define VTSS_XDMAC_XDMAC_GWSS                VTSS_IOREG(VTSS_TO_XDMAC,0xb)

/**
 * \brief
 * WSSx: XDMAC Channel x Write Suspend Status
 *
 * \details
 * 0: The write channel is not suspended.
 * 1: Destination requests for channel x are no longer routed to the
 * scheduler.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GWSS . WSSX
 */
#define  VTSS_F_XDMAC_XDMAC_GWSS_WSSX(x)      VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_GWSS_WSSX         VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_GWSS_WSSX(x)      VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Global Channel Read Suspend Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GRS
 */
#define VTSS_XDMAC_XDMAC_GRS                 VTSS_IOREG(VTSS_TO_XDMAC,0xc)

/**
 * \brief
 * RSx: XDMAC Channel x Read Suspend
 *
 * \details
 * 0: The read channel is not suspended.
 * 1: The source requests for channel x are no longer serviced by the
 * system scheduler.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GRS . RSX
 */
#define  VTSS_F_XDMAC_XDMAC_GRS_RSX(x)        VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_GRS_RSX           VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_GRS_RSX(x)        VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Global Channel Read Resume Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GRR
 */
#define VTSS_XDMAC_XDMAC_GRR                 VTSS_IOREG(VTSS_TO_XDMAC,0xd)

/**
 * \brief
 * RRx: XDMAC Channel x Read Resume
 *
 * \details
 * 0: No effect.
 * 1: The source requests for channel x are serviced by the system
 * scheduler.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GRR . RRX
 */
#define  VTSS_F_XDMAC_XDMAC_GRR_RRX(x)        VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_GRR_RRX           VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_GRR_RRX(x)        VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Global Channel Write Suspend Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GWS
 */
#define VTSS_XDMAC_XDMAC_GWS                 VTSS_IOREG(VTSS_TO_XDMAC,0xe)

/**
 * \brief
 * WSx: XDMAC Channel x Write Suspend
 *
 * \details
 * 0: The write channel is not suspended.
 * 1: Destination requests are no longer routed to the scheduler.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GWS . WSX
 */
#define  VTSS_F_XDMAC_XDMAC_GWS_WSX(x)        VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_GWS_WSX           VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_GWS_WSX(x)        VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Global Channel Write Resume Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GWR
 */
#define VTSS_XDMAC_XDMAC_GWR                 VTSS_IOREG(VTSS_TO_XDMAC,0xf)

/**
 * \brief
 * WRx: XDMAC Channel x Write Resume
 *
 * \details
 * 0: No effect
 * 1: Destination requests are serviced and routed to the scheduler.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GWR . WRX
 */
#define  VTSS_F_XDMAC_XDMAC_GWR_WRX(x)        VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_GWR_WRX           VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_GWR_WRX(x)        VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Global Channel Read Write Suspend Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GRWS
 */
#define VTSS_XDMAC_XDMAC_GRWS                VTSS_IOREG(VTSS_TO_XDMAC,0x10)

/**
 * \brief
 * RWSx: XDMAC Channel x Read Write Suspend
 *
 * \details
 * 0: No effect.
 * 1: Read and write requests are suspended.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GRWS . RWSX
 */
#define  VTSS_F_XDMAC_XDMAC_GRWS_RWSX(x)      VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_GRWS_RWSX         VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_GRWS_RWSX(x)      VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Global Channel Read Write Resume Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GRWR
 */
#define VTSS_XDMAC_XDMAC_GRWR                VTSS_IOREG(VTSS_TO_XDMAC,0x11)

/**
 * \brief
 * RWRx: XDMAC Channel x Read Write Resume
 *
 * \details
 * 0: No effect.
 * 1: Read and write requests are serviced.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GRWR . RWRX
 */
#define  VTSS_F_XDMAC_XDMAC_GRWR_RWRX(x)      VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_GRWR_RWRX         VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_GRWR_RWRX(x)      VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Global Channel Software Request Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GSWR
 */
#define VTSS_XDMAC_XDMAC_GSWR                VTSS_IOREG(VTSS_TO_XDMAC,0x12)

/**
 * \brief
 * SWREQx: XDMAC Channel x Software Request
 *
 * \details
 * 0: No effect.
 * 1: Requests a DMA transfer for channel x.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GSWR . SWREQX
 */
#define  VTSS_F_XDMAC_XDMAC_GSWR_SWREQX(x)    VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_GSWR_SWREQX       VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_GSWR_SWREQX(x)    VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Global Channel Software Request Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GSWS
 */
#define VTSS_XDMAC_XDMAC_GSWS                VTSS_IOREG(VTSS_TO_XDMAC,0x13)

/**
 * \brief
 * SWRSx: XDMAC Channel x Software Request Status
 *
 * \details
 * 0: Channel x source request is serviced.
 * 1: Channel x source request is pending.
 *
 * Field: ::VTSS_XDMAC_XDMAC_GSWS . SWRSX
 */
#define  VTSS_F_XDMAC_XDMAC_GSWS_SWRSX(x)     VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_GSWS_SWRSX        VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_GSWS_SWRSX(x)     VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Global Channel Software Flush Request Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_GSWF
 */
#define VTSS_XDMAC_XDMAC_GSWF                VTSS_IOREG(VTSS_TO_XDMAC,0x14)

/**
 * \brief
 * SWFx: XDMAC Channel x Software Flush Request
 *
 * \details
 * 0: No effect.
 * 1: Requests a DMA transfer flush for channel x. This bit is only
 * relevant when the transfer is source peripheral synchronized
 * (peripheral-to-memory).
 *
 * Field: ::VTSS_XDMAC_XDMAC_GSWF . SWFX
 */
#define  VTSS_F_XDMAC_XDMAC_GSWF_SWFX(x)      VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_GSWF_SWFX         VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_GSWF_SWFX(x)      VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief XDMAC Channel 0 Interrupt Enable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIE_CH0
 */
#define VTSS_XDMAC_XDMAC_CIE_CH0             VTSS_IOREG(VTSS_TO_XDMAC,0x18)

/**
 * \brief
 * TCIE_CH0: Transfer Count Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH0 . TCIE_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH0_TCIE_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH0_TCIE_CH0  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH0_TCIE_CH0(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIE_CH0: Request Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH0 . ROIE_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH0_ROIE_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH0_ROIE_CH0  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH0_ROIE_CH0(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBIE_CH0: Write Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables write bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH0 . WBIE_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH0_WBIE_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH0_WBIE_CH0  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH0_WBIE_CH0(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBIE_CH0: Read Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables read bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH0 . RBIE_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH0_RBIE_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH0_RBIE_CH0  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH0_RBIE_CH0(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIE_CH0: End of Flush Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH0 . FIE_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH0_FIE_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH0_FIE_CH0   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH0_FIE_CH0(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIE_CH0: End of Disable Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH0 . DIE_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH0_DIE_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH0_DIE_CH0   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH0_DIE_CH0(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIE_CH0: End of Linked List Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH0 . LIE_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH0_LIE_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH0_LIE_CH0   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH0_LIE_CH0(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIE_CH0: End of Block Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH0 . BIE_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH0_BIE_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH0_BIE_CH0   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH0_BIE_CH0(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 0 Interrupt Disable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CID_CH0
 */
#define VTSS_XDMAC_XDMAC_CID_CH0             VTSS_IOREG(VTSS_TO_XDMAC,0x19)

/**
 * \brief
 * TCID_CH0: Transfer Count Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH0 . TCID_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH0_TCID_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH0_TCID_CH0  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CID_CH0_TCID_CH0(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROID_CH0: Request Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH0 . ROID_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH0_ROID_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH0_ROID_CH0  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CID_CH0_ROID_CH0(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEID_CH0: Write Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH0 . WBEID_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH0_WBEID_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH0_WBEID_CH0  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CID_CH0_WBEID_CH0(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEID_CH0: Read Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH0 . RBEID_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH0_RBEID_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH0_RBEID_CH0  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CID_CH0_RBEID_CH0(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FID_CH0: End of Flush Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH0 . FID_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH0_FID_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH0_FID_CH0   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CID_CH0_FID_CH0(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DID_CH0: End of Disable Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH0 . DID_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH0_DID_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH0_DID_CH0   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CID_CH0_DID_CH0(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LID_CH0: End of Linked List Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH0 . LID_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH0_LID_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH0_LID_CH0   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CID_CH0_LID_CH0(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BID_CH0: End of Block Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH0 . BID_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH0_BID_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH0_BID_CH0   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CID_CH0_BID_CH0(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 0 Interrupt Mask Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIM_CH0
 */
#define VTSS_XDMAC_XDMAC_CIM_CH0             VTSS_IOREG(VTSS_TO_XDMAC,0x1a)

/**
 * \brief
 * TCIM_CH0: Transfer Count Overflow Error Interrupt Mask
 *
 * \details
 * 0: Transfer count overflow interrupt is masked.
 * 1: Transfer count overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH0 . TCIM_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH0_TCIM_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH0_TCIM_CH0  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH0_TCIM_CH0(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIM_CH0: Request Overflow Error Interrupt Mask
 *
 * \details
 * 0: Request overflow interrupt is masked.
 * 1: Request overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH0 . ROIM_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH0_ROIM_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH0_ROIM_CH0  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH0_ROIM_CH0(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIM_CH0: Write Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH0 . WBEIM_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH0_WBEIM_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH0_WBEIM_CH0  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH0_WBEIM_CH0(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIM_CH0: Read Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH0 . RBEIM_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH0_RBEIM_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH0_RBEIM_CH0  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH0_RBEIM_CH0(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIM_CH0: End of Flush Interrupt Mask
 *
 * \details
 * 0: End of flush interrupt is masked.
 * 1: End of flush interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH0 . FIM_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH0_FIM_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH0_FIM_CH0   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH0_FIM_CH0(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIM_CH0: End of Disable Interrupt Mask
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH0 . DIM_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH0_DIM_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH0_DIM_CH0   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH0_DIM_CH0(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIM_CH0: End of Linked List Interrupt Mask
 *
 * \details
 * 0: End of linked list interrupt is masked.
 * 1: End of linked list interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH0 . LIM_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH0_LIM_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH0_LIM_CH0   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH0_LIM_CH0(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIM_CH0: End of Block Interrupt Mask
 *
 * \details
 * 0: Block interrupt is masked.
 * 1: Block interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH0 . BIM_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH0_BIM_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH0_BIM_CH0   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH0_BIM_CH0(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 0 Interrupt Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIS_CH0
 */
#define VTSS_XDMAC_XDMAC_CIS_CH0             VTSS_IOREG(VTSS_TO_XDMAC,0x1b)

/**
 * \brief
 * TCIS_CH0: Transfer Count Overflow Interrupt Status
 *
 * \details
 * 0: Transfer count overflow has not occurred.
 * 1: At least one transfer count overflow has been detected since the last
 * read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH0 . TCIS_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH0_TCIS_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH0_TCIS_CH0  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH0_TCIS_CH0(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIS_CH0: Request Overflow Error Interrupt Status
 *
 * \details
 * 0: Overflow condition has not occurred.
 * 1: Overflow condition has occurred at least once. (This information is
 * only relevant for peripheral synchronized transfers.)
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH0 . ROIS_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH0_ROIS_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH0_ROIS_CH0  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH0_ROIS_CH0(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIS_CH0: Write Bus Error Interrupt Status
 *
 * \details
 * 0: Write bus error condition has not occurred.
 * 1: At least one bus error has been detected in a write access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH0 . WBEIS_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH0_WBEIS_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH0_WBEIS_CH0  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH0_WBEIS_CH0(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIS_CH0: Read Bus Error Interrupt Status
 *
 * \details
 * 0: Read bus error condition has not occurred.
 * 1: At least one bus error has been detected in a read access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH0 . RBEIS_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH0_RBEIS_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH0_RBEIS_CH0  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH0_RBEIS_CH0(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIS_CH0: End of Flush Interrupt Status
 *
 * \details
 * 0: End of flush condition has not occurred.
 * 1: End of flush condition has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH0 . FIS_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH0_FIS_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH0_FIS_CH0   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH0_FIS_CH0(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIS_CH0: End of Disable Interrupt Status
 *
 * \details
 * 0: End of disable condition has not occurred.
 * 1: End of disable condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH0 . DIS_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH0_DIS_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH0_DIS_CH0   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH0_DIS_CH0(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIS_CH0: End of Linked List Interrupt Status
 *
 * \details
 * 0: End of linked list condition has not occurred.
 * 1: End of linked list condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH0 . LIS_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH0_LIS_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH0_LIS_CH0   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH0_LIS_CH0(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIS_CH0: End of Block Interrupt Status
 *
 * \details
 * 0: End of block interrupt has not occurred.
 * 1: End of block interrupt has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH0 . BIS_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH0_BIS_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH0_BIS_CH0   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH0_BIS_CH0(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 0 Source Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSA_CH0
 */
#define VTSS_XDMAC_XDMAC_CSA_CH0             VTSS_IOREG(VTSS_TO_XDMAC,0x1c)

/**
 * \brief
 * SA_CH0: Source AddressProgram this register with the source address of
 * the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSA_CH0 . SA_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CSA_CH0_SA_CH0(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CSA_CH0_SA_CH0     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CSA_CH0_SA_CH0(x)  (x)


/**
 * \brief XDMAC Channel 0 Destination Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDA_CH0
 */
#define VTSS_XDMAC_XDMAC_CDA_CH0             VTSS_IOREG(VTSS_TO_XDMAC,0x1d)

/**
 * \brief
 * DA_CH0: Destination AddressProgram this register with the destination
 * address of the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDA_CH0 . DA_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CDA_CH0_DA_CH0(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CDA_CH0_DA_CH0     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CDA_CH0_DA_CH0(x)  (x)


/**
 * \brief XDMAC Channel 0 Next Descriptor Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDA_CH0
 */
#define VTSS_XDMAC_XDMAC_CNDA_CH0            VTSS_IOREG(VTSS_TO_XDMAC,0x1e)

/**
 * \brief
 * NDA_CH0: Next Descriptor AddressThe 30-bit width of the NDA field
 * represents the next descriptor address range 31:2. The descriptor is
 * word-aligned and the two least significant register bits 1:0 are
 * ignored.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDA_CH0 . NDA_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CNDA_CH0_NDA_CH0(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_XDMAC_XDMAC_CNDA_CH0_NDA_CH0     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_XDMAC_XDMAC_CNDA_CH0_NDA_CH0(x)  VTSS_EXTRACT_BITFIELD(x,2,30)


/**
 * \brief XDMAC Channel 0 Next Descriptor Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDC_CH0
 */
#define VTSS_XDMAC_XDMAC_CNDC_CH0            VTSS_IOREG(VTSS_TO_XDMAC,0x1f)

/**
 * \brief
 * QOS_CH0: Channel Quality Of Service LevelThis field indicates the
 * current quality of service level for the channel.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH0 . QOS_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH0_QOS_CH0(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH0_QOS_CH0     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH0_QOS_CH0(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * NDVIEW_CH0: Next Descriptor View
 *
 * \details
 * 0 (NDV0): Next Descriptor View 0
 * 1 (NDV0): Next Descriptor View 1
 * 2 (NDV0): Next Descriptor View 2
 * 3 (NDV0): Next Descriptor View 3
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH0 . NDVIEW_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH0_NDVIEW_CH0(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH0_NDVIEW_CH0     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH0_NDVIEW_CH0(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * NDDUP_CH0: Next Descriptor Destination Update
 *
 * \details
 * 0 (DST_PARAMS_UNCHANGED): Destination parameters remain unchanged.
 * 1 (DST_PARAMS_UPDATED): Destination parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH0 . NDDUP_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH0_NDDUP_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH0_NDDUP_CH0  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH0_NDDUP_CH0(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * NDSUP_CH0: Next Descriptor Source Update
 *
 * \details
 * 0 (SRC_PARAMS_UNCHANGED): Source parameters remain unchanged.
 * 1 (SRC_PARAMS_UPDATED): Source parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH0 . NDSUP_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH0_NDSUP_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH0_NDSUP_CH0  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH0_NDSUP_CH0(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * NDE_CH0: Next Descriptor Enable
 *
 * \details
 * 0 (DSCR_FETCH_DIS): Descriptor fetch is disabled.
 * 1 (DSCR_FETCH_EN): Descriptor fetch is enabled.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH0 . NDE_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH0_NDE_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH0_NDE_CH0  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH0_NDE_CH0(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 0 Microblock Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CUBC_CH0
 */
#define VTSS_XDMAC_XDMAC_CUBC_CH0            VTSS_IOREG(VTSS_TO_XDMAC,0x20)

/**
 * \brief
 * UBLEN_CH0: Microblock LengthThis field indicates the number of data in
 * the microblock. The microblock contains UBLEN data.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CUBC_CH0 . UBLEN_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CUBC_CH0_UBLEN_CH0(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CUBC_CH0_UBLEN_CH0     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CUBC_CH0_UBLEN_CH0(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 0 Block Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CBC_CH0
 */
#define VTSS_XDMAC_XDMAC_CBC_CH0             VTSS_IOREG(VTSS_TO_XDMAC,0x21)

/**
 * \brief
 * BLEN_CH0: Block LengthThe length of the block is (BLEN+1) microblocks.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CBC_CH0 . BLEN_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CBC_CH0_BLEN_CH0(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_XDMAC_XDMAC_CBC_CH0_BLEN_CH0     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_XDMAC_XDMAC_CBC_CH0_BLEN_CH0(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief XDMAC Channel 0 Configuration Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CC_CH0
 */
#define VTSS_XDMAC_XDMAC_CC_CH0              VTSS_IOREG(VTSS_TO_XDMAC,0x22)

/**
 * \brief
 * PERID_CH0: Peripheral Hardware Request Line IdentifierThis field
 * contains the peripheral hardware request line identifier.Note: When a
 * memory-to-memory transfer is performed, configure PERID to an unused
 * peripheral ID.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH0 . PERID_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH0_PERID_CH0(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_XDMAC_XDMAC_CC_CH0_PERID_CH0     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH0_PERID_CH0(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * WRIP_CH0: Write in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active write transaction on the bus.
 * 1 (IN_PROGRESS): A write transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH0 . WRIP_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH0_WRIP_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH0_WRIP_CH0   VTSS_BIT(23)
#define  VTSS_X_XDMAC_XDMAC_CC_CH0_WRIP_CH0(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * RDIP_CH0: Read in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active read transaction on the bus.
 * 1 (IN_PROGRESS): A read transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH0 . RDIP_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH0_RDIP_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH0_RDIP_CH0   VTSS_BIT(22)
#define  VTSS_X_XDMAC_XDMAC_CC_CH0_RDIP_CH0(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * INITD_CH0: Channel Initialization Done (this bit is read-only)Note: When
 * set to 0, XDMAC_CUBC_CH0.UBLEN_CH0 and XDMAC_CNDA_CH0.NDA_CH0 field
 * values are unreliable each time a descriptor is being updated.
 *
 * \details
 * 0 (IN_PROGRESS): Channel initialization is in progress.
 * 1 (TERMINATED): Channel initialization is completed.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH0 . INITD_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH0_INITD_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH0_INITD_CH0  VTSS_BIT(21)
#define  VTSS_X_XDMAC_XDMAC_CC_CH0_INITD_CH0(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * DAM_CH0: Destination Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH0 . DAM_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH0_DAM_CH0(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH0_DAM_CH0     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH0_DAM_CH0(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * SAM_CH0: Source Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH0 . SAM_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH0_SAM_CH0(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH0_SAM_CH0     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH0_SAM_CH0(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * DWIDTH_CH0: Data Width
 *
 * \details
 * 0 (BYTE): The data size is set to 8 bits.
 * 1 (HALFWORD): The data size is set to 16 bits.
 * 2 (WORD): The data size is set to 32 bits.
 * 3 (DWORD): The data size is set to 64 bits.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH0 . DWIDTH_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH0_DWIDTH_CH0(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH0_DWIDTH_CH0     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH0_DWIDTH_CH0(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * CSIZE_CH0: Chunk Size
 *
 * \details
 * 0 (CHK_1): 1 data transferred
 * 2 (CHK_2): 2 data transferred
 * 4 (CHK_4): 4 data transferred
 * 8 (CHK_8): 8 data transferred
 * 16 (CHK_16): 16 data transferred
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH0 . CSIZE_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH0_CSIZE_CH0(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_XDMAC_XDMAC_CC_CH0_CSIZE_CH0     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_XDMAC_XDMAC_CC_CH0_CSIZE_CH0(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * MEMSET_CH0: Fill Block of Memory
 *
 * \details
 * 0 (NORMAL_MODE): Memset is not activated.
 * 1 (HW_MODE): Sets the block of memory pointed by DA field to the
 * specified value. This operation is performed on 8-, 16- or 32-bit basis.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH0 . MEMSET_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH0_MEMSET_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH0_MEMSET_CH0  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH0_MEMSET_CH0(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * SWREQ_CH0: Software Request Trigger
 *
 * \details
 * 0 (HWR_CONNECTED): Hardware request line is connected to the peripheral
 * request line.
 * 1 (SWR_CONNECTED): Software request is connected to the peripheral
 * request line.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH0 . SWREQ_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH0_SWREQ_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH0_SWREQ_CH0  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CC_CH0_SWREQ_CH0(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * PROT_CH0: Channel Protection
 *
 * \details
 * 0 (SEC): Channel is secured.
 * 1 (UNSEC): Channel is unsecured.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH0 . PROT_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH0_PROT_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH0_PROT_CH0   VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CC_CH0_PROT_CH0(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DSYNC_CH0: Channel Synchronization (Peripheral Transfer Direction)
 *
 * \details
 * 0 (PER2MEM): Peripheral-to-memory transfer.
 * 1 (MEM2PER): Memory-to-peripheral transfer.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH0 . DSYNC_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH0_DSYNC_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH0_DSYNC_CH0  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CC_CH0_DSYNC_CH0(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * MBSIZE_CH0: Memory Burst Size
 *
 * \details
 * 0 (SINGLE): The memory burst size is set to one.
 * 1 (FOUR): The memory burst size is set to four.
 * 2 (EIGHT): The memory burst size is set to eight.
 * 3 (SIXTEEN): The memory burst size is set to sixteen.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH0 . MBSIZE_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH0_MBSIZE_CH0(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH0_MBSIZE_CH0     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH0_MBSIZE_CH0(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * TYPE_CH0: Transfer Type
 *
 * \details
 * 0 (MEM_TRAN): Self-triggered mode (memory-to-memory transfer).
 * 1 (PER_TRAN): Synchronized mode (peripheral-to-memory or
 * memory-to-peripheral transfer).
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH0 . TYPE_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH0_TYPE_CH0(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH0_TYPE_CH0   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CC_CH0_TYPE_CH0(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 0 Data Stride Memory Set Pattern Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDS_MSP_CH0
 */
#define VTSS_XDMAC_XDMAC_CDS_MSP_CH0         VTSS_IOREG(VTSS_TO_XDMAC,0x23)

/**
 * \brief
 * DDS_MSP_CH0: Destination Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the destination data
 * stride.Number of bytes for the data stride of channel x (two's
 * complement). If the field is set to zero the data is contiguous.The
 * DDS_MSP_CHx field is only relevant when XDMAC_CCx.DAM=UBS_DS_AM.When
 * XDMAC_CCx.MEMSET = 1, this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH0 . DDS_MSP_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH0_DDS_MSP_CH0(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH0_DDS_MSP_CH0     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH0_DDS_MSP_CH0(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * SDS_MSP_CH0: Source Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the source data stride.Number
 * of bytes for the data stride of channel x (two's complement). If the
 * field is set to zero the data is contiguous.The SDS_MSP_CHx field is
 * only relevant when XDMAC_CCx.SAM=UBS_DS_AM.When XDMAC_CCx.MEMSET = 1,
 * this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH0 . SDS_MSP_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH0_SDS_MSP_CH0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH0_SDS_MSP_CH0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH0_SDS_MSP_CH0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief XDMAC Channel 0 Source Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSUS_CH0
 */
#define VTSS_XDMAC_XDMAC_CSUS_CH0            VTSS_IOREG(VTSS_TO_XDMAC,0x24)

/**
 * \brief
 * SUBS_CH0: Source Microblock StrideNumber of bytes for the microblock
 * stride for channel x (two's comlpement). If the field is set to zero the
 * data is contiguous.SUBS_CHx field is only relevant when
 * XDMAC_CCx.SAM=UBS_AM or XDMAC_CCx.SAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSUS_CH0 . SUBS_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CSUS_CH0_SUBS_CH0(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CSUS_CH0_SUBS_CH0     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CSUS_CH0_SUBS_CH0(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 0 Destination Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDUS_CH0
 */
#define VTSS_XDMAC_XDMAC_CDUS_CH0            VTSS_IOREG(VTSS_TO_XDMAC,0x25)

/**
 * \brief
 * DUBS_CH0: Destination Microblock StrideNumber of bytes for the
 * microblock stride for channel x (two's comlpement). If the field is set
 * to zero the data is contiguous.DUBS_CHx field is only relevant when
 * XDMAC_CCx.DAM=UBS_AM or XDMAC_CCx.DAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDUS_CH0 . DUBS_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CDUS_CH0_DUBS_CH0(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CDUS_CH0_DUBS_CH0     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CDUS_CH0_DUBS_CH0(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 0 Transfer Count Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CTCS_CH0
 */
#define VTSS_XDMAC_XDMAC_CTCS_CH0            VTSS_IOREG(VTSS_TO_XDMAC,0x26)

/**
 * \brief
 * TC_CH0: Transfer CountNumber of bytes written by the XDMA since the last
 * read of the Transfer Count Status register. The field does not indicate
 * the number of bytes written to memory.To get the number of bytes already
 * written in memory at any time during peripheral-to-memory transfer, use
 * the following software procedure:1. Read the XDMAC_CTCSx.TC field to
 * sample the number of bytes received by the XDMA.2. Perform a software
 * flush of the channel by writing one to the XDMAC_GSWF register. This
 * will push bytes from the internal DMA FIFO to the external memory and
 * return an interrupt when the bytes can be read by the CPU.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CTCS_CH0 . TC_CH0
 */
#define  VTSS_F_XDMAC_XDMAC_CTCS_CH0_TC_CH0(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CTCS_CH0_TC_CH0     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CTCS_CH0_TC_CH0(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 1 Interrupt Enable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIE_CH1
 */
#define VTSS_XDMAC_XDMAC_CIE_CH1             VTSS_IOREG(VTSS_TO_XDMAC,0x28)

/**
 * \brief
 * TCIE_CH1: Transfer Count Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH1 . TCIE_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH1_TCIE_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH1_TCIE_CH1  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH1_TCIE_CH1(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIE_CH1: Request Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH1 . ROIE_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH1_ROIE_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH1_ROIE_CH1  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH1_ROIE_CH1(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBIE_CH1: Write Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables write bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH1 . WBIE_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH1_WBIE_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH1_WBIE_CH1  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH1_WBIE_CH1(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBIE_CH1: Read Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables read bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH1 . RBIE_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH1_RBIE_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH1_RBIE_CH1  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH1_RBIE_CH1(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIE_CH1: End of Flush Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH1 . FIE_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH1_FIE_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH1_FIE_CH1   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH1_FIE_CH1(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIE_CH1: End of Disable Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH1 . DIE_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH1_DIE_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH1_DIE_CH1   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH1_DIE_CH1(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIE_CH1: End of Linked List Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH1 . LIE_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH1_LIE_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH1_LIE_CH1   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH1_LIE_CH1(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIE_CH1: End of Block Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH1 . BIE_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH1_BIE_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH1_BIE_CH1   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH1_BIE_CH1(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 1 Interrupt Disable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CID_CH1
 */
#define VTSS_XDMAC_XDMAC_CID_CH1             VTSS_IOREG(VTSS_TO_XDMAC,0x29)

/**
 * \brief
 * TCID_CH1: Transfer Count Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH1 . TCID_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH1_TCID_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH1_TCID_CH1  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CID_CH1_TCID_CH1(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROID_CH1: Request Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH1 . ROID_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH1_ROID_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH1_ROID_CH1  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CID_CH1_ROID_CH1(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEID_CH1: Write Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH1 . WBEID_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH1_WBEID_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH1_WBEID_CH1  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CID_CH1_WBEID_CH1(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEID_CH1: Read Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH1 . RBEID_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH1_RBEID_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH1_RBEID_CH1  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CID_CH1_RBEID_CH1(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FID_CH1: End of Flush Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH1 . FID_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH1_FID_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH1_FID_CH1   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CID_CH1_FID_CH1(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DID_CH1: End of Disable Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH1 . DID_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH1_DID_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH1_DID_CH1   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CID_CH1_DID_CH1(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LID_CH1: End of Linked List Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH1 . LID_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH1_LID_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH1_LID_CH1   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CID_CH1_LID_CH1(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BID_CH1: End of Block Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH1 . BID_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH1_BID_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH1_BID_CH1   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CID_CH1_BID_CH1(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 1 Interrupt Mask Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIM_CH1
 */
#define VTSS_XDMAC_XDMAC_CIM_CH1             VTSS_IOREG(VTSS_TO_XDMAC,0x2a)

/**
 * \brief
 * TCIM_CH1: Transfer Count Overflow Error Interrupt Mask
 *
 * \details
 * 0: Transfer count overflow interrupt is masked.
 * 1: Transfer count overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH1 . TCIM_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH1_TCIM_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH1_TCIM_CH1  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH1_TCIM_CH1(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIM_CH1: Request Overflow Error Interrupt Mask
 *
 * \details
 * 0: Request overflow interrupt is masked.
 * 1: Request overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH1 . ROIM_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH1_ROIM_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH1_ROIM_CH1  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH1_ROIM_CH1(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIM_CH1: Write Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH1 . WBEIM_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH1_WBEIM_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH1_WBEIM_CH1  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH1_WBEIM_CH1(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIM_CH1: Read Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH1 . RBEIM_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH1_RBEIM_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH1_RBEIM_CH1  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH1_RBEIM_CH1(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIM_CH1: End of Flush Interrupt Mask
 *
 * \details
 * 0: End of flush interrupt is masked.
 * 1: End of flush interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH1 . FIM_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH1_FIM_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH1_FIM_CH1   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH1_FIM_CH1(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIM_CH1: End of Disable Interrupt Mask
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH1 . DIM_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH1_DIM_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH1_DIM_CH1   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH1_DIM_CH1(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIM_CH1: End of Linked List Interrupt Mask
 *
 * \details
 * 0: End of linked list interrupt is masked.
 * 1: End of linked list interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH1 . LIM_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH1_LIM_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH1_LIM_CH1   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH1_LIM_CH1(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIM_CH1: End of Block Interrupt Mask
 *
 * \details
 * 0: Block interrupt is masked.
 * 1: Block interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH1 . BIM_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH1_BIM_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH1_BIM_CH1   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH1_BIM_CH1(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 1 Interrupt Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIS_CH1
 */
#define VTSS_XDMAC_XDMAC_CIS_CH1             VTSS_IOREG(VTSS_TO_XDMAC,0x2b)

/**
 * \brief
 * TCIS_CH1: Transfer Count Overflow Interrupt Status
 *
 * \details
 * 0: Transfer count overflow has not occurred.
 * 1: At least one transfer count overflow has been detected since the last
 * read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH1 . TCIS_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH1_TCIS_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH1_TCIS_CH1  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH1_TCIS_CH1(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIS_CH1: Request Overflow Error Interrupt Status
 *
 * \details
 * 0: Overflow condition has not occurred.
 * 1: Overflow condition has occurred at least once. (This information is
 * only relevant for peripheral synchronized transfers.)
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH1 . ROIS_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH1_ROIS_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH1_ROIS_CH1  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH1_ROIS_CH1(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIS_CH1: Write Bus Error Interrupt Status
 *
 * \details
 * 0: Write bus error condition has not occurred.
 * 1: At least one bus error has been detected in a write access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH1 . WBEIS_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH1_WBEIS_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH1_WBEIS_CH1  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH1_WBEIS_CH1(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIS_CH1: Read Bus Error Interrupt Status
 *
 * \details
 * 0: Read bus error condition has not occurred.
 * 1: At least one bus error has been detected in a read access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH1 . RBEIS_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH1_RBEIS_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH1_RBEIS_CH1  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH1_RBEIS_CH1(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIS_CH1: End of Flush Interrupt Status
 *
 * \details
 * 0: End of flush condition has not occurred.
 * 1: End of flush condition has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH1 . FIS_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH1_FIS_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH1_FIS_CH1   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH1_FIS_CH1(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIS_CH1: End of Disable Interrupt Status
 *
 * \details
 * 0: End of disable condition has not occurred.
 * 1: End of disable condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH1 . DIS_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH1_DIS_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH1_DIS_CH1   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH1_DIS_CH1(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIS_CH1: End of Linked List Interrupt Status
 *
 * \details
 * 0: End of linked list condition has not occurred.
 * 1: End of linked list condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH1 . LIS_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH1_LIS_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH1_LIS_CH1   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH1_LIS_CH1(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIS_CH1: End of Block Interrupt Status
 *
 * \details
 * 0: End of block interrupt has not occurred.
 * 1: End of block interrupt has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH1 . BIS_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH1_BIS_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH1_BIS_CH1   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH1_BIS_CH1(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 1 Source Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSA_CH1
 */
#define VTSS_XDMAC_XDMAC_CSA_CH1             VTSS_IOREG(VTSS_TO_XDMAC,0x2c)

/**
 * \brief
 * SA_CH1: Source AddressProgram this register with the source address of
 * the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSA_CH1 . SA_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CSA_CH1_SA_CH1(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CSA_CH1_SA_CH1     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CSA_CH1_SA_CH1(x)  (x)


/**
 * \brief XDMAC Channel 1 Destination Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDA_CH1
 */
#define VTSS_XDMAC_XDMAC_CDA_CH1             VTSS_IOREG(VTSS_TO_XDMAC,0x2d)

/**
 * \brief
 * DA_CH1: Destination AddressProgram this register with the destination
 * address of the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDA_CH1 . DA_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CDA_CH1_DA_CH1(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CDA_CH1_DA_CH1     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CDA_CH1_DA_CH1(x)  (x)


/**
 * \brief XDMAC Channel 1 Next Descriptor Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDA_CH1
 */
#define VTSS_XDMAC_XDMAC_CNDA_CH1            VTSS_IOREG(VTSS_TO_XDMAC,0x2e)

/**
 * \brief
 * NDA_CH1: Next Descriptor AddressThe 30-bit width of the NDA field
 * represents the next descriptor address range 31:2. The descriptor is
 * word-aligned and the two least significant register bits 1:0 are
 * ignored.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDA_CH1 . NDA_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CNDA_CH1_NDA_CH1(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_XDMAC_XDMAC_CNDA_CH1_NDA_CH1     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_XDMAC_XDMAC_CNDA_CH1_NDA_CH1(x)  VTSS_EXTRACT_BITFIELD(x,2,30)


/**
 * \brief XDMAC Channel 1 Next Descriptor Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDC_CH1
 */
#define VTSS_XDMAC_XDMAC_CNDC_CH1            VTSS_IOREG(VTSS_TO_XDMAC,0x2f)

/**
 * \brief
 * QOS_CH1: Channel Quality Of Service LevelThis field indicates the
 * current quality of service level for the channel.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH1 . QOS_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH1_QOS_CH1(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH1_QOS_CH1     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH1_QOS_CH1(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * NDVIEW_CH1: Next Descriptor View
 *
 * \details
 * 0 (NDV0): Next Descriptor View 0
 * 1 (NDV0): Next Descriptor View 1
 * 2 (NDV0): Next Descriptor View 2
 * 3 (NDV0): Next Descriptor View 3
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH1 . NDVIEW_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH1_NDVIEW_CH1(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH1_NDVIEW_CH1     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH1_NDVIEW_CH1(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * NDDUP_CH1: Next Descriptor Destination Update
 *
 * \details
 * 0 (DST_PARAMS_UNCHANGED): Destination parameters remain unchanged.
 * 1 (DST_PARAMS_UPDATED): Destination parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH1 . NDDUP_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH1_NDDUP_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH1_NDDUP_CH1  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH1_NDDUP_CH1(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * NDSUP_CH1: Next Descriptor Source Update
 *
 * \details
 * 0 (SRC_PARAMS_UNCHANGED): Source parameters remain unchanged.
 * 1 (SRC_PARAMS_UPDATED): Source parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH1 . NDSUP_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH1_NDSUP_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH1_NDSUP_CH1  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH1_NDSUP_CH1(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * NDE_CH1: Next Descriptor Enable
 *
 * \details
 * 0 (DSCR_FETCH_DIS): Descriptor fetch is disabled.
 * 1 (DSCR_FETCH_EN): Descriptor fetch is enabled.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH1 . NDE_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH1_NDE_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH1_NDE_CH1  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH1_NDE_CH1(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 1 Microblock Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CUBC_CH1
 */
#define VTSS_XDMAC_XDMAC_CUBC_CH1            VTSS_IOREG(VTSS_TO_XDMAC,0x30)

/**
 * \brief
 * UBLEN_CH1: Microblock LengthThis field indicates the number of data in
 * the microblock. The microblock contains UBLEN data.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CUBC_CH1 . UBLEN_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CUBC_CH1_UBLEN_CH1(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CUBC_CH1_UBLEN_CH1     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CUBC_CH1_UBLEN_CH1(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 1 Block Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CBC_CH1
 */
#define VTSS_XDMAC_XDMAC_CBC_CH1             VTSS_IOREG(VTSS_TO_XDMAC,0x31)

/**
 * \brief
 * BLEN_CH1: Block LengthThe length of the block is (BLEN+1) microblocks.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CBC_CH1 . BLEN_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CBC_CH1_BLEN_CH1(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_XDMAC_XDMAC_CBC_CH1_BLEN_CH1     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_XDMAC_XDMAC_CBC_CH1_BLEN_CH1(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief XDMAC Channel 1 Configuration Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CC_CH1
 */
#define VTSS_XDMAC_XDMAC_CC_CH1              VTSS_IOREG(VTSS_TO_XDMAC,0x32)

/**
 * \brief
 * PERID_CH1: Peripheral Hardware Request Line IdentifierThis field
 * contains the peripheral hardware request line identifier.Note: When a
 * memory-to-memory transfer is performed, configure PERID to an unused
 * peripheral ID.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH1 . PERID_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH1_PERID_CH1(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_XDMAC_XDMAC_CC_CH1_PERID_CH1     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH1_PERID_CH1(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * WRIP_CH1: Write in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active write transaction on the bus.
 * 1 (IN_PROGRESS): A write transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH1 . WRIP_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH1_WRIP_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH1_WRIP_CH1   VTSS_BIT(23)
#define  VTSS_X_XDMAC_XDMAC_CC_CH1_WRIP_CH1(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * RDIP_CH1: Read in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active read transaction on the bus.
 * 1 (IN_PROGRESS): A read transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH1 . RDIP_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH1_RDIP_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH1_RDIP_CH1   VTSS_BIT(22)
#define  VTSS_X_XDMAC_XDMAC_CC_CH1_RDIP_CH1(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * INITD_CH1: Channel Initialization Done (this bit is read-only)Note: When
 * set to 0, XDMAC_CUBC_CH1.UBLEN_CH1 and XDMAC_CNDA_CH1.NDA_CH1 field
 * values are unreliable each time a descriptor is being updated.
 *
 * \details
 * 0 (IN_PROGRESS): Channel initialization is in progress.
 * 1 (TERMINATED): Channel initialization is completed.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH1 . INITD_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH1_INITD_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH1_INITD_CH1  VTSS_BIT(21)
#define  VTSS_X_XDMAC_XDMAC_CC_CH1_INITD_CH1(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * DAM_CH1: Destination Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH1 . DAM_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH1_DAM_CH1(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH1_DAM_CH1     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH1_DAM_CH1(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * SAM_CH1: Source Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH1 . SAM_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH1_SAM_CH1(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH1_SAM_CH1     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH1_SAM_CH1(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * DWIDTH_CH1: Data Width
 *
 * \details
 * 0 (BYTE): The data size is set to 8 bits.
 * 1 (HALFWORD): The data size is set to 16 bits.
 * 2 (WORD): The data size is set to 32 bits.
 * 3 (DWORD): The data size is set to 64 bits.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH1 . DWIDTH_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH1_DWIDTH_CH1(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH1_DWIDTH_CH1     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH1_DWIDTH_CH1(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * CSIZE_CH1: Chunk Size
 *
 * \details
 * 0 (CHK_1): 1 data transferred
 * 2 (CHK_2): 2 data transferred
 * 4 (CHK_4): 4 data transferred
 * 8 (CHK_8): 8 data transferred
 * 16 (CHK_16): 16 data transferred
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH1 . CSIZE_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH1_CSIZE_CH1(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_XDMAC_XDMAC_CC_CH1_CSIZE_CH1     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_XDMAC_XDMAC_CC_CH1_CSIZE_CH1(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * MEMSET_CH1: Fill Block of Memory
 *
 * \details
 * 0 (NORMAL_MODE): Memset is not activated.
 * 1 (HW_MODE): Sets the block of memory pointed by DA field to the
 * specified value. This operation is performed on 8-, 16- or 32-bit basis.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH1 . MEMSET_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH1_MEMSET_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH1_MEMSET_CH1  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH1_MEMSET_CH1(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * SWREQ_CH1: Software Request Trigger
 *
 * \details
 * 0 (HWR_CONNECTED): Hardware request line is connected to the peripheral
 * request line.
 * 1 (SWR_CONNECTED): Software request is connected to the peripheral
 * request line.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH1 . SWREQ_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH1_SWREQ_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH1_SWREQ_CH1  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CC_CH1_SWREQ_CH1(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * PROT_CH1: Channel Protection
 *
 * \details
 * 0 (SEC): Channel is secured.
 * 1 (UNSEC): Channel is unsecured.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH1 . PROT_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH1_PROT_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH1_PROT_CH1   VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CC_CH1_PROT_CH1(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DSYNC_CH1: Channel Synchronization (Peripheral Transfer Direction)
 *
 * \details
 * 0 (PER2MEM): Peripheral-to-memory transfer.
 * 1 (MEM2PER): Memory-to-peripheral transfer.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH1 . DSYNC_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH1_DSYNC_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH1_DSYNC_CH1  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CC_CH1_DSYNC_CH1(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * MBSIZE_CH1: Memory Burst Size
 *
 * \details
 * 0 (SINGLE): The memory burst size is set to one.
 * 1 (FOUR): The memory burst size is set to four.
 * 2 (EIGHT): The memory burst size is set to eight.
 * 3 (SIXTEEN): The memory burst size is set to sixteen.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH1 . MBSIZE_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH1_MBSIZE_CH1(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH1_MBSIZE_CH1     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH1_MBSIZE_CH1(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * TYPE_CH1: Transfer Type
 *
 * \details
 * 0 (MEM_TRAN): Self-triggered mode (memory-to-memory transfer).
 * 1 (PER_TRAN): Synchronized mode (peripheral-to-memory or
 * memory-to-peripheral transfer).
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH1 . TYPE_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH1_TYPE_CH1(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH1_TYPE_CH1   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CC_CH1_TYPE_CH1(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 1 Data Stride Memory Set Pattern Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDS_MSP_CH1
 */
#define VTSS_XDMAC_XDMAC_CDS_MSP_CH1         VTSS_IOREG(VTSS_TO_XDMAC,0x33)

/**
 * \brief
 * DDS_MSP_CH1: Destination Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the destination data
 * stride.Number of bytes for the data stride of channel x (two's
 * complement). If the field is set to zero the data is contiguous.The
 * DDS_MSP_CHx field is only relevant when XDMAC_CCx.DAM=UBS_DS_AM.When
 * XDMAC_CCx.MEMSET = 1, this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH1 . DDS_MSP_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH1_DDS_MSP_CH1(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH1_DDS_MSP_CH1     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH1_DDS_MSP_CH1(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * SDS_MSP_CH1: Source Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the source data stride.Number
 * of bytes for the data stride of channel x (two's complement). If the
 * field is set to zero the data is contiguous.The SDS_MSP_CHx field is
 * only relevant when XDMAC_CCx.SAM=UBS_DS_AM.When XDMAC_CCx.MEMSET = 1,
 * this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH1 . SDS_MSP_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH1_SDS_MSP_CH1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH1_SDS_MSP_CH1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH1_SDS_MSP_CH1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief XDMAC Channel 1 Source Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSUS_CH1
 */
#define VTSS_XDMAC_XDMAC_CSUS_CH1            VTSS_IOREG(VTSS_TO_XDMAC,0x34)

/**
 * \brief
 * SUBS_CH1: Source Microblock StrideNumber of bytes for the microblock
 * stride for channel x (two's comlpement). If the field is set to zero the
 * data is contiguous.SUBS_CHx field is only relevant when
 * XDMAC_CCx.SAM=UBS_AM or XDMAC_CCx.SAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSUS_CH1 . SUBS_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CSUS_CH1_SUBS_CH1(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CSUS_CH1_SUBS_CH1     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CSUS_CH1_SUBS_CH1(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 1 Destination Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDUS_CH1
 */
#define VTSS_XDMAC_XDMAC_CDUS_CH1            VTSS_IOREG(VTSS_TO_XDMAC,0x35)

/**
 * \brief
 * DUBS_CH1: Destination Microblock StrideNumber of bytes for the
 * microblock stride for channel x (two's comlpement). If the field is set
 * to zero the data is contiguous.DUBS_CHx field is only relevant when
 * XDMAC_CCx.DAM=UBS_AM or XDMAC_CCx.DAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDUS_CH1 . DUBS_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CDUS_CH1_DUBS_CH1(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CDUS_CH1_DUBS_CH1     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CDUS_CH1_DUBS_CH1(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 1 Transfer Count Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CTCS_CH1
 */
#define VTSS_XDMAC_XDMAC_CTCS_CH1            VTSS_IOREG(VTSS_TO_XDMAC,0x36)

/**
 * \brief
 * TC_CH1: Transfer CountNumber of bytes written by the XDMA since the last
 * read of the Transfer Count Status register. The field does not indicate
 * the number of bytes written to memory.To get the number of bytes already
 * written in memory at any time during peripheral-to-memory transfer, use
 * the following software procedure:1. Read the XDMAC_CTCSx.TC field to
 * sample the number of bytes received by the XDMA.2. Perform a software
 * flush of the channel by writing one to the XDMAC_GSWF register. This
 * will push bytes from the internal DMA FIFO to the external memory and
 * return an interrupt when the bytes can be read by the CPU.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CTCS_CH1 . TC_CH1
 */
#define  VTSS_F_XDMAC_XDMAC_CTCS_CH1_TC_CH1(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CTCS_CH1_TC_CH1     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CTCS_CH1_TC_CH1(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 2 Interrupt Enable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIE_CH2
 */
#define VTSS_XDMAC_XDMAC_CIE_CH2             VTSS_IOREG(VTSS_TO_XDMAC,0x38)

/**
 * \brief
 * TCIE_CH2: Transfer Count Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH2 . TCIE_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH2_TCIE_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH2_TCIE_CH2  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH2_TCIE_CH2(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIE_CH2: Request Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH2 . ROIE_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH2_ROIE_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH2_ROIE_CH2  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH2_ROIE_CH2(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBIE_CH2: Write Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables write bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH2 . WBIE_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH2_WBIE_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH2_WBIE_CH2  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH2_WBIE_CH2(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBIE_CH2: Read Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables read bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH2 . RBIE_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH2_RBIE_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH2_RBIE_CH2  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH2_RBIE_CH2(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIE_CH2: End of Flush Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH2 . FIE_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH2_FIE_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH2_FIE_CH2   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH2_FIE_CH2(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIE_CH2: End of Disable Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH2 . DIE_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH2_DIE_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH2_DIE_CH2   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH2_DIE_CH2(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIE_CH2: End of Linked List Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH2 . LIE_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH2_LIE_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH2_LIE_CH2   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH2_LIE_CH2(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIE_CH2: End of Block Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH2 . BIE_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH2_BIE_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH2_BIE_CH2   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH2_BIE_CH2(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 2 Interrupt Disable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CID_CH2
 */
#define VTSS_XDMAC_XDMAC_CID_CH2             VTSS_IOREG(VTSS_TO_XDMAC,0x39)

/**
 * \brief
 * TCID_CH2: Transfer Count Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH2 . TCID_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH2_TCID_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH2_TCID_CH2  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CID_CH2_TCID_CH2(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROID_CH2: Request Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH2 . ROID_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH2_ROID_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH2_ROID_CH2  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CID_CH2_ROID_CH2(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEID_CH2: Write Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH2 . WBEID_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH2_WBEID_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH2_WBEID_CH2  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CID_CH2_WBEID_CH2(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEID_CH2: Read Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH2 . RBEID_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH2_RBEID_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH2_RBEID_CH2  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CID_CH2_RBEID_CH2(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FID_CH2: End of Flush Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH2 . FID_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH2_FID_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH2_FID_CH2   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CID_CH2_FID_CH2(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DID_CH2: End of Disable Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH2 . DID_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH2_DID_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH2_DID_CH2   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CID_CH2_DID_CH2(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LID_CH2: End of Linked List Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH2 . LID_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH2_LID_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH2_LID_CH2   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CID_CH2_LID_CH2(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BID_CH2: End of Block Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH2 . BID_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH2_BID_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH2_BID_CH2   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CID_CH2_BID_CH2(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 2 Interrupt Mask Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIM_CH2
 */
#define VTSS_XDMAC_XDMAC_CIM_CH2             VTSS_IOREG(VTSS_TO_XDMAC,0x3a)

/**
 * \brief
 * TCIM_CH2: Transfer Count Overflow Error Interrupt Mask
 *
 * \details
 * 0: Transfer count overflow interrupt is masked.
 * 1: Transfer count overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH2 . TCIM_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH2_TCIM_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH2_TCIM_CH2  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH2_TCIM_CH2(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIM_CH2: Request Overflow Error Interrupt Mask
 *
 * \details
 * 0: Request overflow interrupt is masked.
 * 1: Request overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH2 . ROIM_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH2_ROIM_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH2_ROIM_CH2  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH2_ROIM_CH2(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIM_CH2: Write Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH2 . WBEIM_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH2_WBEIM_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH2_WBEIM_CH2  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH2_WBEIM_CH2(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIM_CH2: Read Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH2 . RBEIM_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH2_RBEIM_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH2_RBEIM_CH2  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH2_RBEIM_CH2(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIM_CH2: End of Flush Interrupt Mask
 *
 * \details
 * 0: End of flush interrupt is masked.
 * 1: End of flush interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH2 . FIM_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH2_FIM_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH2_FIM_CH2   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH2_FIM_CH2(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIM_CH2: End of Disable Interrupt Mask
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH2 . DIM_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH2_DIM_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH2_DIM_CH2   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH2_DIM_CH2(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIM_CH2: End of Linked List Interrupt Mask
 *
 * \details
 * 0: End of linked list interrupt is masked.
 * 1: End of linked list interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH2 . LIM_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH2_LIM_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH2_LIM_CH2   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH2_LIM_CH2(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIM_CH2: End of Block Interrupt Mask
 *
 * \details
 * 0: Block interrupt is masked.
 * 1: Block interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH2 . BIM_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH2_BIM_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH2_BIM_CH2   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH2_BIM_CH2(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 2 Interrupt Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIS_CH2
 */
#define VTSS_XDMAC_XDMAC_CIS_CH2             VTSS_IOREG(VTSS_TO_XDMAC,0x3b)

/**
 * \brief
 * TCIS_CH2: Transfer Count Overflow Interrupt Status
 *
 * \details
 * 0: Transfer count overflow has not occurred.
 * 1: At least one transfer count overflow has been detected since the last
 * read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH2 . TCIS_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH2_TCIS_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH2_TCIS_CH2  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH2_TCIS_CH2(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIS_CH2: Request Overflow Error Interrupt Status
 *
 * \details
 * 0: Overflow condition has not occurred.
 * 1: Overflow condition has occurred at least once. (This information is
 * only relevant for peripheral synchronized transfers.)
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH2 . ROIS_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH2_ROIS_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH2_ROIS_CH2  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH2_ROIS_CH2(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIS_CH2: Write Bus Error Interrupt Status
 *
 * \details
 * 0: Write bus error condition has not occurred.
 * 1: At least one bus error has been detected in a write access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH2 . WBEIS_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH2_WBEIS_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH2_WBEIS_CH2  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH2_WBEIS_CH2(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIS_CH2: Read Bus Error Interrupt Status
 *
 * \details
 * 0: Read bus error condition has not occurred.
 * 1: At least one bus error has been detected in a read access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH2 . RBEIS_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH2_RBEIS_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH2_RBEIS_CH2  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH2_RBEIS_CH2(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIS_CH2: End of Flush Interrupt Status
 *
 * \details
 * 0: End of flush condition has not occurred.
 * 1: End of flush condition has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH2 . FIS_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH2_FIS_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH2_FIS_CH2   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH2_FIS_CH2(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIS_CH2: End of Disable Interrupt Status
 *
 * \details
 * 0: End of disable condition has not occurred.
 * 1: End of disable condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH2 . DIS_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH2_DIS_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH2_DIS_CH2   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH2_DIS_CH2(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIS_CH2: End of Linked List Interrupt Status
 *
 * \details
 * 0: End of linked list condition has not occurred.
 * 1: End of linked list condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH2 . LIS_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH2_LIS_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH2_LIS_CH2   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH2_LIS_CH2(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIS_CH2: End of Block Interrupt Status
 *
 * \details
 * 0: End of block interrupt has not occurred.
 * 1: End of block interrupt has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH2 . BIS_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH2_BIS_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH2_BIS_CH2   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH2_BIS_CH2(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 2 Source Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSA_CH2
 */
#define VTSS_XDMAC_XDMAC_CSA_CH2             VTSS_IOREG(VTSS_TO_XDMAC,0x3c)

/**
 * \brief
 * SA_CH2: Source AddressProgram this register with the source address of
 * the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSA_CH2 . SA_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CSA_CH2_SA_CH2(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CSA_CH2_SA_CH2     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CSA_CH2_SA_CH2(x)  (x)


/**
 * \brief XDMAC Channel 2 Destination Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDA_CH2
 */
#define VTSS_XDMAC_XDMAC_CDA_CH2             VTSS_IOREG(VTSS_TO_XDMAC,0x3d)

/**
 * \brief
 * DA_CH2: Destination AddressProgram this register with the destination
 * address of the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDA_CH2 . DA_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CDA_CH2_DA_CH2(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CDA_CH2_DA_CH2     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CDA_CH2_DA_CH2(x)  (x)


/**
 * \brief XDMAC Channel 2 Next Descriptor Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDA_CH2
 */
#define VTSS_XDMAC_XDMAC_CNDA_CH2            VTSS_IOREG(VTSS_TO_XDMAC,0x3e)

/**
 * \brief
 * NDA_CH2: Next Descriptor AddressThe 30-bit width of the NDA field
 * represents the next descriptor address range 31:2. The descriptor is
 * word-aligned and the two least significant register bits 1:0 are
 * ignored.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDA_CH2 . NDA_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CNDA_CH2_NDA_CH2(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_XDMAC_XDMAC_CNDA_CH2_NDA_CH2     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_XDMAC_XDMAC_CNDA_CH2_NDA_CH2(x)  VTSS_EXTRACT_BITFIELD(x,2,30)


/**
 * \brief XDMAC Channel 2 Next Descriptor Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDC_CH2
 */
#define VTSS_XDMAC_XDMAC_CNDC_CH2            VTSS_IOREG(VTSS_TO_XDMAC,0x3f)

/**
 * \brief
 * QOS_CH2: Channel Quality Of Service LevelThis field indicates the
 * current quality of service level for the channel.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH2 . QOS_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH2_QOS_CH2(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH2_QOS_CH2     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH2_QOS_CH2(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * NDVIEW_CH2: Next Descriptor View
 *
 * \details
 * 0 (NDV0): Next Descriptor View 0
 * 1 (NDV0): Next Descriptor View 1
 * 2 (NDV0): Next Descriptor View 2
 * 3 (NDV0): Next Descriptor View 3
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH2 . NDVIEW_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH2_NDVIEW_CH2(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH2_NDVIEW_CH2     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH2_NDVIEW_CH2(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * NDDUP_CH2: Next Descriptor Destination Update
 *
 * \details
 * 0 (DST_PARAMS_UNCHANGED): Destination parameters remain unchanged.
 * 1 (DST_PARAMS_UPDATED): Destination parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH2 . NDDUP_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH2_NDDUP_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH2_NDDUP_CH2  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH2_NDDUP_CH2(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * NDSUP_CH2: Next Descriptor Source Update
 *
 * \details
 * 0 (SRC_PARAMS_UNCHANGED): Source parameters remain unchanged.
 * 1 (SRC_PARAMS_UPDATED): Source parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH2 . NDSUP_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH2_NDSUP_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH2_NDSUP_CH2  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH2_NDSUP_CH2(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * NDE_CH2: Next Descriptor Enable
 *
 * \details
 * 0 (DSCR_FETCH_DIS): Descriptor fetch is disabled.
 * 1 (DSCR_FETCH_EN): Descriptor fetch is enabled.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH2 . NDE_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH2_NDE_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH2_NDE_CH2  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH2_NDE_CH2(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 2 Microblock Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CUBC_CH2
 */
#define VTSS_XDMAC_XDMAC_CUBC_CH2            VTSS_IOREG(VTSS_TO_XDMAC,0x40)

/**
 * \brief
 * UBLEN_CH2: Microblock LengthThis field indicates the number of data in
 * the microblock. The microblock contains UBLEN data.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CUBC_CH2 . UBLEN_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CUBC_CH2_UBLEN_CH2(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CUBC_CH2_UBLEN_CH2     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CUBC_CH2_UBLEN_CH2(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 2 Block Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CBC_CH2
 */
#define VTSS_XDMAC_XDMAC_CBC_CH2             VTSS_IOREG(VTSS_TO_XDMAC,0x41)

/**
 * \brief
 * BLEN_CH2: Block LengthThe length of the block is (BLEN+1) microblocks.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CBC_CH2 . BLEN_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CBC_CH2_BLEN_CH2(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_XDMAC_XDMAC_CBC_CH2_BLEN_CH2     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_XDMAC_XDMAC_CBC_CH2_BLEN_CH2(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief XDMAC Channel 2 Configuration Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CC_CH2
 */
#define VTSS_XDMAC_XDMAC_CC_CH2              VTSS_IOREG(VTSS_TO_XDMAC,0x42)

/**
 * \brief
 * PERID_CH2: Peripheral Hardware Request Line IdentifierThis field
 * contains the peripheral hardware request line identifier.Note: When a
 * memory-to-memory transfer is performed, configure PERID to an unused
 * peripheral ID.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH2 . PERID_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH2_PERID_CH2(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_XDMAC_XDMAC_CC_CH2_PERID_CH2     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH2_PERID_CH2(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * WRIP_CH2: Write in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active write transaction on the bus.
 * 1 (IN_PROGRESS): A write transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH2 . WRIP_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH2_WRIP_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH2_WRIP_CH2   VTSS_BIT(23)
#define  VTSS_X_XDMAC_XDMAC_CC_CH2_WRIP_CH2(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * RDIP_CH2: Read in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active read transaction on the bus.
 * 1 (IN_PROGRESS): A read transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH2 . RDIP_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH2_RDIP_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH2_RDIP_CH2   VTSS_BIT(22)
#define  VTSS_X_XDMAC_XDMAC_CC_CH2_RDIP_CH2(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * INITD_CH2: Channel Initialization Done (this bit is read-only)Note: When
 * set to 0, XDMAC_CUBC_CH2.UBLEN_CH2 and XDMAC_CNDA_CH2.NDA_CH2 field
 * values are unreliable each time a descriptor is being updated.
 *
 * \details
 * 0 (IN_PROGRESS): Channel initialization is in progress.
 * 1 (TERMINATED): Channel initialization is completed.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH2 . INITD_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH2_INITD_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH2_INITD_CH2  VTSS_BIT(21)
#define  VTSS_X_XDMAC_XDMAC_CC_CH2_INITD_CH2(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * DAM_CH2: Destination Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH2 . DAM_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH2_DAM_CH2(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH2_DAM_CH2     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH2_DAM_CH2(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * SAM_CH2: Source Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH2 . SAM_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH2_SAM_CH2(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH2_SAM_CH2     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH2_SAM_CH2(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * DWIDTH_CH2: Data Width
 *
 * \details
 * 0 (BYTE): The data size is set to 8 bits.
 * 1 (HALFWORD): The data size is set to 16 bits.
 * 2 (WORD): The data size is set to 32 bits.
 * 3 (DWORD): The data size is set to 64 bits.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH2 . DWIDTH_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH2_DWIDTH_CH2(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH2_DWIDTH_CH2     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH2_DWIDTH_CH2(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * CSIZE_CH2: Chunk Size
 *
 * \details
 * 0 (CHK_1): 1 data transferred
 * 2 (CHK_2): 2 data transferred
 * 4 (CHK_4): 4 data transferred
 * 8 (CHK_8): 8 data transferred
 * 16 (CHK_16): 16 data transferred
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH2 . CSIZE_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH2_CSIZE_CH2(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_XDMAC_XDMAC_CC_CH2_CSIZE_CH2     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_XDMAC_XDMAC_CC_CH2_CSIZE_CH2(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * MEMSET_CH2: Fill Block of Memory
 *
 * \details
 * 0 (NORMAL_MODE): Memset is not activated.
 * 1 (HW_MODE): Sets the block of memory pointed by DA field to the
 * specified value. This operation is performed on 8-, 16- or 32-bit basis.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH2 . MEMSET_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH2_MEMSET_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH2_MEMSET_CH2  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH2_MEMSET_CH2(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * SWREQ_CH2: Software Request Trigger
 *
 * \details
 * 0 (HWR_CONNECTED): Hardware request line is connected to the peripheral
 * request line.
 * 1 (SWR_CONNECTED): Software request is connected to the peripheral
 * request line.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH2 . SWREQ_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH2_SWREQ_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH2_SWREQ_CH2  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CC_CH2_SWREQ_CH2(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * PROT_CH2: Channel Protection
 *
 * \details
 * 0 (SEC): Channel is secured.
 * 1 (UNSEC): Channel is unsecured.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH2 . PROT_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH2_PROT_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH2_PROT_CH2   VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CC_CH2_PROT_CH2(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DSYNC_CH2: Channel Synchronization (Peripheral Transfer Direction)
 *
 * \details
 * 0 (PER2MEM): Peripheral-to-memory transfer.
 * 1 (MEM2PER): Memory-to-peripheral transfer.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH2 . DSYNC_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH2_DSYNC_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH2_DSYNC_CH2  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CC_CH2_DSYNC_CH2(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * MBSIZE_CH2: Memory Burst Size
 *
 * \details
 * 0 (SINGLE): The memory burst size is set to one.
 * 1 (FOUR): The memory burst size is set to four.
 * 2 (EIGHT): The memory burst size is set to eight.
 * 3 (SIXTEEN): The memory burst size is set to sixteen.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH2 . MBSIZE_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH2_MBSIZE_CH2(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH2_MBSIZE_CH2     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH2_MBSIZE_CH2(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * TYPE_CH2: Transfer Type
 *
 * \details
 * 0 (MEM_TRAN): Self-triggered mode (memory-to-memory transfer).
 * 1 (PER_TRAN): Synchronized mode (peripheral-to-memory or
 * memory-to-peripheral transfer).
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH2 . TYPE_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH2_TYPE_CH2(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH2_TYPE_CH2   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CC_CH2_TYPE_CH2(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 2 Data Stride Memory Set Pattern Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDS_MSP_CH2
 */
#define VTSS_XDMAC_XDMAC_CDS_MSP_CH2         VTSS_IOREG(VTSS_TO_XDMAC,0x43)

/**
 * \brief
 * DDS_MSP_CH2: Destination Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the destination data
 * stride.Number of bytes for the data stride of channel x (two's
 * complement). If the field is set to zero the data is contiguous.The
 * DDS_MSP_CHx field is only relevant when XDMAC_CCx.DAM=UBS_DS_AM.When
 * XDMAC_CCx.MEMSET = 1, this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH2 . DDS_MSP_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH2_DDS_MSP_CH2(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH2_DDS_MSP_CH2     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH2_DDS_MSP_CH2(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * SDS_MSP_CH2: Source Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the source data stride.Number
 * of bytes for the data stride of channel x (two's complement). If the
 * field is set to zero the data is contiguous.The SDS_MSP_CHx field is
 * only relevant when XDMAC_CCx.SAM=UBS_DS_AM.When XDMAC_CCx.MEMSET = 1,
 * this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH2 . SDS_MSP_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH2_SDS_MSP_CH2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH2_SDS_MSP_CH2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH2_SDS_MSP_CH2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief XDMAC Channel 2 Source Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSUS_CH2
 */
#define VTSS_XDMAC_XDMAC_CSUS_CH2            VTSS_IOREG(VTSS_TO_XDMAC,0x44)

/**
 * \brief
 * SUBS_CH2: Source Microblock StrideNumber of bytes for the microblock
 * stride for channel x (two's comlpement). If the field is set to zero the
 * data is contiguous.SUBS_CHx field is only relevant when
 * XDMAC_CCx.SAM=UBS_AM or XDMAC_CCx.SAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSUS_CH2 . SUBS_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CSUS_CH2_SUBS_CH2(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CSUS_CH2_SUBS_CH2     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CSUS_CH2_SUBS_CH2(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 2 Destination Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDUS_CH2
 */
#define VTSS_XDMAC_XDMAC_CDUS_CH2            VTSS_IOREG(VTSS_TO_XDMAC,0x45)

/**
 * \brief
 * DUBS_CH2: Destination Microblock StrideNumber of bytes for the
 * microblock stride for channel x (two's comlpement). If the field is set
 * to zero the data is contiguous.DUBS_CHx field is only relevant when
 * XDMAC_CCx.DAM=UBS_AM or XDMAC_CCx.DAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDUS_CH2 . DUBS_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CDUS_CH2_DUBS_CH2(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CDUS_CH2_DUBS_CH2     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CDUS_CH2_DUBS_CH2(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 2 Transfer Count Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CTCS_CH2
 */
#define VTSS_XDMAC_XDMAC_CTCS_CH2            VTSS_IOREG(VTSS_TO_XDMAC,0x46)

/**
 * \brief
 * TC_CH2: Transfer CountNumber of bytes written by the XDMA since the last
 * read of the Transfer Count Status register. The field does not indicate
 * the number of bytes written to memory.To get the number of bytes already
 * written in memory at any time during peripheral-to-memory transfer, use
 * the following software procedure:1. Read the XDMAC_CTCSx.TC field to
 * sample the number of bytes received by the XDMA.2. Perform a software
 * flush of the channel by writing one to the XDMAC_GSWF register. This
 * will push bytes from the internal DMA FIFO to the external memory and
 * return an interrupt when the bytes can be read by the CPU.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CTCS_CH2 . TC_CH2
 */
#define  VTSS_F_XDMAC_XDMAC_CTCS_CH2_TC_CH2(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CTCS_CH2_TC_CH2     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CTCS_CH2_TC_CH2(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 3 Interrupt Enable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIE_CH3
 */
#define VTSS_XDMAC_XDMAC_CIE_CH3             VTSS_IOREG(VTSS_TO_XDMAC,0x48)

/**
 * \brief
 * TCIE_CH3: Transfer Count Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH3 . TCIE_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH3_TCIE_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH3_TCIE_CH3  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH3_TCIE_CH3(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIE_CH3: Request Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH3 . ROIE_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH3_ROIE_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH3_ROIE_CH3  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH3_ROIE_CH3(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBIE_CH3: Write Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables write bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH3 . WBIE_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH3_WBIE_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH3_WBIE_CH3  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH3_WBIE_CH3(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBIE_CH3: Read Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables read bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH3 . RBIE_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH3_RBIE_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH3_RBIE_CH3  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH3_RBIE_CH3(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIE_CH3: End of Flush Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH3 . FIE_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH3_FIE_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH3_FIE_CH3   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH3_FIE_CH3(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIE_CH3: End of Disable Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH3 . DIE_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH3_DIE_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH3_DIE_CH3   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH3_DIE_CH3(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIE_CH3: End of Linked List Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH3 . LIE_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH3_LIE_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH3_LIE_CH3   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH3_LIE_CH3(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIE_CH3: End of Block Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH3 . BIE_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH3_BIE_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH3_BIE_CH3   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH3_BIE_CH3(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 3 Interrupt Disable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CID_CH3
 */
#define VTSS_XDMAC_XDMAC_CID_CH3             VTSS_IOREG(VTSS_TO_XDMAC,0x49)

/**
 * \brief
 * TCID_CH3: Transfer Count Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH3 . TCID_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH3_TCID_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH3_TCID_CH3  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CID_CH3_TCID_CH3(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROID_CH3: Request Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH3 . ROID_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH3_ROID_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH3_ROID_CH3  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CID_CH3_ROID_CH3(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEID_CH3: Write Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH3 . WBEID_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH3_WBEID_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH3_WBEID_CH3  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CID_CH3_WBEID_CH3(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEID_CH3: Read Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH3 . RBEID_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH3_RBEID_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH3_RBEID_CH3  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CID_CH3_RBEID_CH3(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FID_CH3: End of Flush Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH3 . FID_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH3_FID_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH3_FID_CH3   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CID_CH3_FID_CH3(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DID_CH3: End of Disable Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH3 . DID_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH3_DID_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH3_DID_CH3   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CID_CH3_DID_CH3(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LID_CH3: End of Linked List Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH3 . LID_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH3_LID_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH3_LID_CH3   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CID_CH3_LID_CH3(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BID_CH3: End of Block Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH3 . BID_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH3_BID_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH3_BID_CH3   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CID_CH3_BID_CH3(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 3 Interrupt Mask Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIM_CH3
 */
#define VTSS_XDMAC_XDMAC_CIM_CH3             VTSS_IOREG(VTSS_TO_XDMAC,0x4a)

/**
 * \brief
 * TCIM_CH3: Transfer Count Overflow Error Interrupt Mask
 *
 * \details
 * 0: Transfer count overflow interrupt is masked.
 * 1: Transfer count overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH3 . TCIM_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH3_TCIM_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH3_TCIM_CH3  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH3_TCIM_CH3(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIM_CH3: Request Overflow Error Interrupt Mask
 *
 * \details
 * 0: Request overflow interrupt is masked.
 * 1: Request overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH3 . ROIM_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH3_ROIM_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH3_ROIM_CH3  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH3_ROIM_CH3(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIM_CH3: Write Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH3 . WBEIM_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH3_WBEIM_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH3_WBEIM_CH3  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH3_WBEIM_CH3(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIM_CH3: Read Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH3 . RBEIM_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH3_RBEIM_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH3_RBEIM_CH3  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH3_RBEIM_CH3(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIM_CH3: End of Flush Interrupt Mask
 *
 * \details
 * 0: End of flush interrupt is masked.
 * 1: End of flush interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH3 . FIM_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH3_FIM_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH3_FIM_CH3   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH3_FIM_CH3(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIM_CH3: End of Disable Interrupt Mask
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH3 . DIM_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH3_DIM_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH3_DIM_CH3   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH3_DIM_CH3(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIM_CH3: End of Linked List Interrupt Mask
 *
 * \details
 * 0: End of linked list interrupt is masked.
 * 1: End of linked list interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH3 . LIM_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH3_LIM_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH3_LIM_CH3   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH3_LIM_CH3(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIM_CH3: End of Block Interrupt Mask
 *
 * \details
 * 0: Block interrupt is masked.
 * 1: Block interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH3 . BIM_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH3_BIM_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH3_BIM_CH3   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH3_BIM_CH3(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 3 Interrupt Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIS_CH3
 */
#define VTSS_XDMAC_XDMAC_CIS_CH3             VTSS_IOREG(VTSS_TO_XDMAC,0x4b)

/**
 * \brief
 * TCIS_CH3: Transfer Count Overflow Interrupt Status
 *
 * \details
 * 0: Transfer count overflow has not occurred.
 * 1: At least one transfer count overflow has been detected since the last
 * read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH3 . TCIS_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH3_TCIS_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH3_TCIS_CH3  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH3_TCIS_CH3(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIS_CH3: Request Overflow Error Interrupt Status
 *
 * \details
 * 0: Overflow condition has not occurred.
 * 1: Overflow condition has occurred at least once. (This information is
 * only relevant for peripheral synchronized transfers.)
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH3 . ROIS_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH3_ROIS_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH3_ROIS_CH3  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH3_ROIS_CH3(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIS_CH3: Write Bus Error Interrupt Status
 *
 * \details
 * 0: Write bus error condition has not occurred.
 * 1: At least one bus error has been detected in a write access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH3 . WBEIS_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH3_WBEIS_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH3_WBEIS_CH3  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH3_WBEIS_CH3(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIS_CH3: Read Bus Error Interrupt Status
 *
 * \details
 * 0: Read bus error condition has not occurred.
 * 1: At least one bus error has been detected in a read access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH3 . RBEIS_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH3_RBEIS_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH3_RBEIS_CH3  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH3_RBEIS_CH3(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIS_CH3: End of Flush Interrupt Status
 *
 * \details
 * 0: End of flush condition has not occurred.
 * 1: End of flush condition has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH3 . FIS_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH3_FIS_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH3_FIS_CH3   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH3_FIS_CH3(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIS_CH3: End of Disable Interrupt Status
 *
 * \details
 * 0: End of disable condition has not occurred.
 * 1: End of disable condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH3 . DIS_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH3_DIS_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH3_DIS_CH3   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH3_DIS_CH3(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIS_CH3: End of Linked List Interrupt Status
 *
 * \details
 * 0: End of linked list condition has not occurred.
 * 1: End of linked list condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH3 . LIS_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH3_LIS_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH3_LIS_CH3   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH3_LIS_CH3(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIS_CH3: End of Block Interrupt Status
 *
 * \details
 * 0: End of block interrupt has not occurred.
 * 1: End of block interrupt has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH3 . BIS_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH3_BIS_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH3_BIS_CH3   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH3_BIS_CH3(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 3 Source Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSA_CH3
 */
#define VTSS_XDMAC_XDMAC_CSA_CH3             VTSS_IOREG(VTSS_TO_XDMAC,0x4c)

/**
 * \brief
 * SA_CH3: Source AddressProgram this register with the source address of
 * the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSA_CH3 . SA_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CSA_CH3_SA_CH3(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CSA_CH3_SA_CH3     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CSA_CH3_SA_CH3(x)  (x)


/**
 * \brief XDMAC Channel 3 Destination Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDA_CH3
 */
#define VTSS_XDMAC_XDMAC_CDA_CH3             VTSS_IOREG(VTSS_TO_XDMAC,0x4d)

/**
 * \brief
 * DA_CH3: Destination AddressProgram this register with the destination
 * address of the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDA_CH3 . DA_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CDA_CH3_DA_CH3(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CDA_CH3_DA_CH3     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CDA_CH3_DA_CH3(x)  (x)


/**
 * \brief XDMAC Channel 3 Next Descriptor Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDA_CH3
 */
#define VTSS_XDMAC_XDMAC_CNDA_CH3            VTSS_IOREG(VTSS_TO_XDMAC,0x4e)

/**
 * \brief
 * NDA_CH3: Next Descriptor AddressThe 30-bit width of the NDA field
 * represents the next descriptor address range 31:2. The descriptor is
 * word-aligned and the two least significant register bits 1:0 are
 * ignored.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDA_CH3 . NDA_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CNDA_CH3_NDA_CH3(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_XDMAC_XDMAC_CNDA_CH3_NDA_CH3     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_XDMAC_XDMAC_CNDA_CH3_NDA_CH3(x)  VTSS_EXTRACT_BITFIELD(x,2,30)


/**
 * \brief XDMAC Channel 3 Next Descriptor Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDC_CH3
 */
#define VTSS_XDMAC_XDMAC_CNDC_CH3            VTSS_IOREG(VTSS_TO_XDMAC,0x4f)

/**
 * \brief
 * QOS_CH3: Channel Quality Of Service LevelThis field indicates the
 * current quality of service level for the channel.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH3 . QOS_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH3_QOS_CH3(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH3_QOS_CH3     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH3_QOS_CH3(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * NDVIEW_CH3: Next Descriptor View
 *
 * \details
 * 0 (NDV0): Next Descriptor View 0
 * 1 (NDV0): Next Descriptor View 1
 * 2 (NDV0): Next Descriptor View 2
 * 3 (NDV0): Next Descriptor View 3
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH3 . NDVIEW_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH3_NDVIEW_CH3(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH3_NDVIEW_CH3     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH3_NDVIEW_CH3(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * NDDUP_CH3: Next Descriptor Destination Update
 *
 * \details
 * 0 (DST_PARAMS_UNCHANGED): Destination parameters remain unchanged.
 * 1 (DST_PARAMS_UPDATED): Destination parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH3 . NDDUP_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH3_NDDUP_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH3_NDDUP_CH3  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH3_NDDUP_CH3(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * NDSUP_CH3: Next Descriptor Source Update
 *
 * \details
 * 0 (SRC_PARAMS_UNCHANGED): Source parameters remain unchanged.
 * 1 (SRC_PARAMS_UPDATED): Source parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH3 . NDSUP_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH3_NDSUP_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH3_NDSUP_CH3  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH3_NDSUP_CH3(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * NDE_CH3: Next Descriptor Enable
 *
 * \details
 * 0 (DSCR_FETCH_DIS): Descriptor fetch is disabled.
 * 1 (DSCR_FETCH_EN): Descriptor fetch is enabled.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH3 . NDE_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH3_NDE_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH3_NDE_CH3  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH3_NDE_CH3(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 3 Microblock Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CUBC_CH3
 */
#define VTSS_XDMAC_XDMAC_CUBC_CH3            VTSS_IOREG(VTSS_TO_XDMAC,0x50)

/**
 * \brief
 * UBLEN_CH3: Microblock LengthThis field indicates the number of data in
 * the microblock. The microblock contains UBLEN data.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CUBC_CH3 . UBLEN_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CUBC_CH3_UBLEN_CH3(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CUBC_CH3_UBLEN_CH3     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CUBC_CH3_UBLEN_CH3(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 3 Block Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CBC_CH3
 */
#define VTSS_XDMAC_XDMAC_CBC_CH3             VTSS_IOREG(VTSS_TO_XDMAC,0x51)

/**
 * \brief
 * BLEN_CH3: Block LengthThe length of the block is (BLEN+1) microblocks.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CBC_CH3 . BLEN_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CBC_CH3_BLEN_CH3(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_XDMAC_XDMAC_CBC_CH3_BLEN_CH3     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_XDMAC_XDMAC_CBC_CH3_BLEN_CH3(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief XDMAC Channel 3 Configuration Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CC_CH3
 */
#define VTSS_XDMAC_XDMAC_CC_CH3              VTSS_IOREG(VTSS_TO_XDMAC,0x52)

/**
 * \brief
 * PERID_CH3: Peripheral Hardware Request Line IdentifierThis field
 * contains the peripheral hardware request line identifier.Note: When a
 * memory-to-memory transfer is performed, configure PERID to an unused
 * peripheral ID.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH3 . PERID_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH3_PERID_CH3(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_XDMAC_XDMAC_CC_CH3_PERID_CH3     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH3_PERID_CH3(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * WRIP_CH3: Write in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active write transaction on the bus.
 * 1 (IN_PROGRESS): A write transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH3 . WRIP_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH3_WRIP_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH3_WRIP_CH3   VTSS_BIT(23)
#define  VTSS_X_XDMAC_XDMAC_CC_CH3_WRIP_CH3(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * RDIP_CH3: Read in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active read transaction on the bus.
 * 1 (IN_PROGRESS): A read transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH3 . RDIP_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH3_RDIP_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH3_RDIP_CH3   VTSS_BIT(22)
#define  VTSS_X_XDMAC_XDMAC_CC_CH3_RDIP_CH3(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * INITD_CH3: Channel Initialization Done (this bit is read-only)Note: When
 * set to 0, XDMAC_CUBC_CH3.UBLEN_CH3 and XDMAC_CNDA_CH3.NDA_CH3 field
 * values are unreliable each time a descriptor is being updated.
 *
 * \details
 * 0 (IN_PROGRESS): Channel initialization is in progress.
 * 1 (TERMINATED): Channel initialization is completed.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH3 . INITD_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH3_INITD_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH3_INITD_CH3  VTSS_BIT(21)
#define  VTSS_X_XDMAC_XDMAC_CC_CH3_INITD_CH3(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * DAM_CH3: Destination Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH3 . DAM_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH3_DAM_CH3(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH3_DAM_CH3     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH3_DAM_CH3(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * SAM_CH3: Source Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH3 . SAM_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH3_SAM_CH3(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH3_SAM_CH3     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH3_SAM_CH3(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * DWIDTH_CH3: Data Width
 *
 * \details
 * 0 (BYTE): The data size is set to 8 bits.
 * 1 (HALFWORD): The data size is set to 16 bits.
 * 2 (WORD): The data size is set to 32 bits.
 * 3 (DWORD): The data size is set to 64 bits.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH3 . DWIDTH_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH3_DWIDTH_CH3(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH3_DWIDTH_CH3     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH3_DWIDTH_CH3(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * CSIZE_CH3: Chunk Size
 *
 * \details
 * 0 (CHK_1): 1 data transferred
 * 2 (CHK_2): 2 data transferred
 * 4 (CHK_4): 4 data transferred
 * 8 (CHK_8): 8 data transferred
 * 16 (CHK_16): 16 data transferred
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH3 . CSIZE_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH3_CSIZE_CH3(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_XDMAC_XDMAC_CC_CH3_CSIZE_CH3     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_XDMAC_XDMAC_CC_CH3_CSIZE_CH3(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * MEMSET_CH3: Fill Block of Memory
 *
 * \details
 * 0 (NORMAL_MODE): Memset is not activated.
 * 1 (HW_MODE): Sets the block of memory pointed by DA field to the
 * specified value. This operation is performed on 8-, 16- or 32-bit basis.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH3 . MEMSET_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH3_MEMSET_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH3_MEMSET_CH3  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH3_MEMSET_CH3(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * SWREQ_CH3: Software Request Trigger
 *
 * \details
 * 0 (HWR_CONNECTED): Hardware request line is connected to the peripheral
 * request line.
 * 1 (SWR_CONNECTED): Software request is connected to the peripheral
 * request line.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH3 . SWREQ_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH3_SWREQ_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH3_SWREQ_CH3  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CC_CH3_SWREQ_CH3(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * PROT_CH3: Channel Protection
 *
 * \details
 * 0 (SEC): Channel is secured.
 * 1 (UNSEC): Channel is unsecured.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH3 . PROT_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH3_PROT_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH3_PROT_CH3   VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CC_CH3_PROT_CH3(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DSYNC_CH3: Channel Synchronization (Peripheral Transfer Direction)
 *
 * \details
 * 0 (PER2MEM): Peripheral-to-memory transfer.
 * 1 (MEM2PER): Memory-to-peripheral transfer.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH3 . DSYNC_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH3_DSYNC_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH3_DSYNC_CH3  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CC_CH3_DSYNC_CH3(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * MBSIZE_CH3: Memory Burst Size
 *
 * \details
 * 0 (SINGLE): The memory burst size is set to one.
 * 1 (FOUR): The memory burst size is set to four.
 * 2 (EIGHT): The memory burst size is set to eight.
 * 3 (SIXTEEN): The memory burst size is set to sixteen.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH3 . MBSIZE_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH3_MBSIZE_CH3(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH3_MBSIZE_CH3     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH3_MBSIZE_CH3(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * TYPE_CH3: Transfer Type
 *
 * \details
 * 0 (MEM_TRAN): Self-triggered mode (memory-to-memory transfer).
 * 1 (PER_TRAN): Synchronized mode (peripheral-to-memory or
 * memory-to-peripheral transfer).
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH3 . TYPE_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH3_TYPE_CH3(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH3_TYPE_CH3   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CC_CH3_TYPE_CH3(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 3 Data Stride Memory Set Pattern Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDS_MSP_CH3
 */
#define VTSS_XDMAC_XDMAC_CDS_MSP_CH3         VTSS_IOREG(VTSS_TO_XDMAC,0x53)

/**
 * \brief
 * DDS_MSP_CH3: Destination Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the destination data
 * stride.Number of bytes for the data stride of channel x (two's
 * complement). If the field is set to zero the data is contiguous.The
 * DDS_MSP_CHx field is only relevant when XDMAC_CCx.DAM=UBS_DS_AM.When
 * XDMAC_CCx.MEMSET = 1, this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH3 . DDS_MSP_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH3_DDS_MSP_CH3(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH3_DDS_MSP_CH3     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH3_DDS_MSP_CH3(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * SDS_MSP_CH3: Source Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the source data stride.Number
 * of bytes for the data stride of channel x (two's complement). If the
 * field is set to zero the data is contiguous.The SDS_MSP_CHx field is
 * only relevant when XDMAC_CCx.SAM=UBS_DS_AM.When XDMAC_CCx.MEMSET = 1,
 * this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH3 . SDS_MSP_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH3_SDS_MSP_CH3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH3_SDS_MSP_CH3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH3_SDS_MSP_CH3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief XDMAC Channel 3 Source Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSUS_CH3
 */
#define VTSS_XDMAC_XDMAC_CSUS_CH3            VTSS_IOREG(VTSS_TO_XDMAC,0x54)

/**
 * \brief
 * SUBS_CH3: Source Microblock StrideNumber of bytes for the microblock
 * stride for channel x (two's comlpement). If the field is set to zero the
 * data is contiguous.SUBS_CHx field is only relevant when
 * XDMAC_CCx.SAM=UBS_AM or XDMAC_CCx.SAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSUS_CH3 . SUBS_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CSUS_CH3_SUBS_CH3(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CSUS_CH3_SUBS_CH3     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CSUS_CH3_SUBS_CH3(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 3 Destination Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDUS_CH3
 */
#define VTSS_XDMAC_XDMAC_CDUS_CH3            VTSS_IOREG(VTSS_TO_XDMAC,0x55)

/**
 * \brief
 * DUBS_CH3: Destination Microblock StrideNumber of bytes for the
 * microblock stride for channel x (two's comlpement). If the field is set
 * to zero the data is contiguous.DUBS_CHx field is only relevant when
 * XDMAC_CCx.DAM=UBS_AM or XDMAC_CCx.DAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDUS_CH3 . DUBS_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CDUS_CH3_DUBS_CH3(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CDUS_CH3_DUBS_CH3     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CDUS_CH3_DUBS_CH3(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 3 Transfer Count Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CTCS_CH3
 */
#define VTSS_XDMAC_XDMAC_CTCS_CH3            VTSS_IOREG(VTSS_TO_XDMAC,0x56)

/**
 * \brief
 * TC_CH3: Transfer CountNumber of bytes written by the XDMA since the last
 * read of the Transfer Count Status register. The field does not indicate
 * the number of bytes written to memory.To get the number of bytes already
 * written in memory at any time during peripheral-to-memory transfer, use
 * the following software procedure:1. Read the XDMAC_CTCSx.TC field to
 * sample the number of bytes received by the XDMA.2. Perform a software
 * flush of the channel by writing one to the XDMAC_GSWF register. This
 * will push bytes from the internal DMA FIFO to the external memory and
 * return an interrupt when the bytes can be read by the CPU.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CTCS_CH3 . TC_CH3
 */
#define  VTSS_F_XDMAC_XDMAC_CTCS_CH3_TC_CH3(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CTCS_CH3_TC_CH3     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CTCS_CH3_TC_CH3(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 4 Interrupt Enable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIE_CH4
 */
#define VTSS_XDMAC_XDMAC_CIE_CH4             VTSS_IOREG(VTSS_TO_XDMAC,0x58)

/**
 * \brief
 * TCIE_CH4: Transfer Count Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH4 . TCIE_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH4_TCIE_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH4_TCIE_CH4  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH4_TCIE_CH4(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIE_CH4: Request Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH4 . ROIE_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH4_ROIE_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH4_ROIE_CH4  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH4_ROIE_CH4(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBIE_CH4: Write Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables write bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH4 . WBIE_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH4_WBIE_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH4_WBIE_CH4  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH4_WBIE_CH4(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBIE_CH4: Read Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables read bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH4 . RBIE_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH4_RBIE_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH4_RBIE_CH4  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH4_RBIE_CH4(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIE_CH4: End of Flush Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH4 . FIE_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH4_FIE_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH4_FIE_CH4   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH4_FIE_CH4(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIE_CH4: End of Disable Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH4 . DIE_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH4_DIE_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH4_DIE_CH4   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH4_DIE_CH4(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIE_CH4: End of Linked List Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH4 . LIE_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH4_LIE_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH4_LIE_CH4   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH4_LIE_CH4(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIE_CH4: End of Block Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH4 . BIE_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH4_BIE_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH4_BIE_CH4   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH4_BIE_CH4(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 4 Interrupt Disable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CID_CH4
 */
#define VTSS_XDMAC_XDMAC_CID_CH4             VTSS_IOREG(VTSS_TO_XDMAC,0x59)

/**
 * \brief
 * TCID_CH4: Transfer Count Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH4 . TCID_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH4_TCID_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH4_TCID_CH4  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CID_CH4_TCID_CH4(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROID_CH4: Request Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH4 . ROID_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH4_ROID_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH4_ROID_CH4  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CID_CH4_ROID_CH4(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEID_CH4: Write Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH4 . WBEID_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH4_WBEID_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH4_WBEID_CH4  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CID_CH4_WBEID_CH4(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEID_CH4: Read Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH4 . RBEID_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH4_RBEID_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH4_RBEID_CH4  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CID_CH4_RBEID_CH4(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FID_CH4: End of Flush Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH4 . FID_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH4_FID_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH4_FID_CH4   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CID_CH4_FID_CH4(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DID_CH4: End of Disable Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH4 . DID_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH4_DID_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH4_DID_CH4   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CID_CH4_DID_CH4(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LID_CH4: End of Linked List Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH4 . LID_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH4_LID_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH4_LID_CH4   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CID_CH4_LID_CH4(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BID_CH4: End of Block Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH4 . BID_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH4_BID_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH4_BID_CH4   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CID_CH4_BID_CH4(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 4 Interrupt Mask Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIM_CH4
 */
#define VTSS_XDMAC_XDMAC_CIM_CH4             VTSS_IOREG(VTSS_TO_XDMAC,0x5a)

/**
 * \brief
 * TCIM_CH4: Transfer Count Overflow Error Interrupt Mask
 *
 * \details
 * 0: Transfer count overflow interrupt is masked.
 * 1: Transfer count overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH4 . TCIM_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH4_TCIM_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH4_TCIM_CH4  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH4_TCIM_CH4(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIM_CH4: Request Overflow Error Interrupt Mask
 *
 * \details
 * 0: Request overflow interrupt is masked.
 * 1: Request overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH4 . ROIM_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH4_ROIM_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH4_ROIM_CH4  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH4_ROIM_CH4(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIM_CH4: Write Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH4 . WBEIM_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH4_WBEIM_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH4_WBEIM_CH4  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH4_WBEIM_CH4(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIM_CH4: Read Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH4 . RBEIM_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH4_RBEIM_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH4_RBEIM_CH4  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH4_RBEIM_CH4(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIM_CH4: End of Flush Interrupt Mask
 *
 * \details
 * 0: End of flush interrupt is masked.
 * 1: End of flush interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH4 . FIM_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH4_FIM_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH4_FIM_CH4   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH4_FIM_CH4(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIM_CH4: End of Disable Interrupt Mask
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH4 . DIM_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH4_DIM_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH4_DIM_CH4   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH4_DIM_CH4(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIM_CH4: End of Linked List Interrupt Mask
 *
 * \details
 * 0: End of linked list interrupt is masked.
 * 1: End of linked list interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH4 . LIM_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH4_LIM_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH4_LIM_CH4   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH4_LIM_CH4(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIM_CH4: End of Block Interrupt Mask
 *
 * \details
 * 0: Block interrupt is masked.
 * 1: Block interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH4 . BIM_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH4_BIM_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH4_BIM_CH4   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH4_BIM_CH4(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 4 Interrupt Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIS_CH4
 */
#define VTSS_XDMAC_XDMAC_CIS_CH4             VTSS_IOREG(VTSS_TO_XDMAC,0x5b)

/**
 * \brief
 * TCIS_CH4: Transfer Count Overflow Interrupt Status
 *
 * \details
 * 0: Transfer count overflow has not occurred.
 * 1: At least one transfer count overflow has been detected since the last
 * read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH4 . TCIS_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH4_TCIS_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH4_TCIS_CH4  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH4_TCIS_CH4(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIS_CH4: Request Overflow Error Interrupt Status
 *
 * \details
 * 0: Overflow condition has not occurred.
 * 1: Overflow condition has occurred at least once. (This information is
 * only relevant for peripheral synchronized transfers.)
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH4 . ROIS_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH4_ROIS_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH4_ROIS_CH4  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH4_ROIS_CH4(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIS_CH4: Write Bus Error Interrupt Status
 *
 * \details
 * 0: Write bus error condition has not occurred.
 * 1: At least one bus error has been detected in a write access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH4 . WBEIS_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH4_WBEIS_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH4_WBEIS_CH4  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH4_WBEIS_CH4(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIS_CH4: Read Bus Error Interrupt Status
 *
 * \details
 * 0: Read bus error condition has not occurred.
 * 1: At least one bus error has been detected in a read access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH4 . RBEIS_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH4_RBEIS_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH4_RBEIS_CH4  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH4_RBEIS_CH4(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIS_CH4: End of Flush Interrupt Status
 *
 * \details
 * 0: End of flush condition has not occurred.
 * 1: End of flush condition has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH4 . FIS_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH4_FIS_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH4_FIS_CH4   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH4_FIS_CH4(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIS_CH4: End of Disable Interrupt Status
 *
 * \details
 * 0: End of disable condition has not occurred.
 * 1: End of disable condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH4 . DIS_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH4_DIS_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH4_DIS_CH4   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH4_DIS_CH4(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIS_CH4: End of Linked List Interrupt Status
 *
 * \details
 * 0: End of linked list condition has not occurred.
 * 1: End of linked list condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH4 . LIS_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH4_LIS_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH4_LIS_CH4   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH4_LIS_CH4(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIS_CH4: End of Block Interrupt Status
 *
 * \details
 * 0: End of block interrupt has not occurred.
 * 1: End of block interrupt has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH4 . BIS_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH4_BIS_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH4_BIS_CH4   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH4_BIS_CH4(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 4 Source Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSA_CH4
 */
#define VTSS_XDMAC_XDMAC_CSA_CH4             VTSS_IOREG(VTSS_TO_XDMAC,0x5c)

/**
 * \brief
 * SA_CH4: Source AddressProgram this register with the source address of
 * the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSA_CH4 . SA_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CSA_CH4_SA_CH4(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CSA_CH4_SA_CH4     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CSA_CH4_SA_CH4(x)  (x)


/**
 * \brief XDMAC Channel 4 Destination Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDA_CH4
 */
#define VTSS_XDMAC_XDMAC_CDA_CH4             VTSS_IOREG(VTSS_TO_XDMAC,0x5d)

/**
 * \brief
 * DA_CH4: Destination AddressProgram this register with the destination
 * address of the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDA_CH4 . DA_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CDA_CH4_DA_CH4(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CDA_CH4_DA_CH4     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CDA_CH4_DA_CH4(x)  (x)


/**
 * \brief XDMAC Channel 4 Next Descriptor Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDA_CH4
 */
#define VTSS_XDMAC_XDMAC_CNDA_CH4            VTSS_IOREG(VTSS_TO_XDMAC,0x5e)

/**
 * \brief
 * NDA_CH4: Next Descriptor AddressThe 30-bit width of the NDA field
 * represents the next descriptor address range 31:2. The descriptor is
 * word-aligned and the two least significant register bits 1:0 are
 * ignored.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDA_CH4 . NDA_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CNDA_CH4_NDA_CH4(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_XDMAC_XDMAC_CNDA_CH4_NDA_CH4     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_XDMAC_XDMAC_CNDA_CH4_NDA_CH4(x)  VTSS_EXTRACT_BITFIELD(x,2,30)


/**
 * \brief XDMAC Channel 4 Next Descriptor Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDC_CH4
 */
#define VTSS_XDMAC_XDMAC_CNDC_CH4            VTSS_IOREG(VTSS_TO_XDMAC,0x5f)

/**
 * \brief
 * QOS_CH4: Channel Quality Of Service LevelThis field indicates the
 * current quality of service level for the channel.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH4 . QOS_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH4_QOS_CH4(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH4_QOS_CH4     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH4_QOS_CH4(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * NDVIEW_CH4: Next Descriptor View
 *
 * \details
 * 0 (NDV0): Next Descriptor View 0
 * 1 (NDV0): Next Descriptor View 1
 * 2 (NDV0): Next Descriptor View 2
 * 3 (NDV0): Next Descriptor View 3
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH4 . NDVIEW_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH4_NDVIEW_CH4(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH4_NDVIEW_CH4     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH4_NDVIEW_CH4(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * NDDUP_CH4: Next Descriptor Destination Update
 *
 * \details
 * 0 (DST_PARAMS_UNCHANGED): Destination parameters remain unchanged.
 * 1 (DST_PARAMS_UPDATED): Destination parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH4 . NDDUP_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH4_NDDUP_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH4_NDDUP_CH4  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH4_NDDUP_CH4(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * NDSUP_CH4: Next Descriptor Source Update
 *
 * \details
 * 0 (SRC_PARAMS_UNCHANGED): Source parameters remain unchanged.
 * 1 (SRC_PARAMS_UPDATED): Source parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH4 . NDSUP_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH4_NDSUP_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH4_NDSUP_CH4  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH4_NDSUP_CH4(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * NDE_CH4: Next Descriptor Enable
 *
 * \details
 * 0 (DSCR_FETCH_DIS): Descriptor fetch is disabled.
 * 1 (DSCR_FETCH_EN): Descriptor fetch is enabled.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH4 . NDE_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH4_NDE_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH4_NDE_CH4  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH4_NDE_CH4(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 4 Microblock Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CUBC_CH4
 */
#define VTSS_XDMAC_XDMAC_CUBC_CH4            VTSS_IOREG(VTSS_TO_XDMAC,0x60)

/**
 * \brief
 * UBLEN_CH4: Microblock LengthThis field indicates the number of data in
 * the microblock. The microblock contains UBLEN data.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CUBC_CH4 . UBLEN_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CUBC_CH4_UBLEN_CH4(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CUBC_CH4_UBLEN_CH4     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CUBC_CH4_UBLEN_CH4(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 4 Block Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CBC_CH4
 */
#define VTSS_XDMAC_XDMAC_CBC_CH4             VTSS_IOREG(VTSS_TO_XDMAC,0x61)

/**
 * \brief
 * BLEN_CH4: Block LengthThe length of the block is (BLEN+1) microblocks.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CBC_CH4 . BLEN_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CBC_CH4_BLEN_CH4(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_XDMAC_XDMAC_CBC_CH4_BLEN_CH4     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_XDMAC_XDMAC_CBC_CH4_BLEN_CH4(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief XDMAC Channel 4 Configuration Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CC_CH4
 */
#define VTSS_XDMAC_XDMAC_CC_CH4              VTSS_IOREG(VTSS_TO_XDMAC,0x62)

/**
 * \brief
 * PERID_CH4: Peripheral Hardware Request Line IdentifierThis field
 * contains the peripheral hardware request line identifier.Note: When a
 * memory-to-memory transfer is performed, configure PERID to an unused
 * peripheral ID.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH4 . PERID_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH4_PERID_CH4(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_XDMAC_XDMAC_CC_CH4_PERID_CH4     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH4_PERID_CH4(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * WRIP_CH4: Write in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active write transaction on the bus.
 * 1 (IN_PROGRESS): A write transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH4 . WRIP_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH4_WRIP_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH4_WRIP_CH4   VTSS_BIT(23)
#define  VTSS_X_XDMAC_XDMAC_CC_CH4_WRIP_CH4(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * RDIP_CH4: Read in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active read transaction on the bus.
 * 1 (IN_PROGRESS): A read transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH4 . RDIP_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH4_RDIP_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH4_RDIP_CH4   VTSS_BIT(22)
#define  VTSS_X_XDMAC_XDMAC_CC_CH4_RDIP_CH4(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * INITD_CH4: Channel Initialization Done (this bit is read-only)Note: When
 * set to 0, XDMAC_CUBC_CH4.UBLEN_CH4 and XDMAC_CNDA_CH4.NDA_CH4 field
 * values are unreliable each time a descriptor is being updated.
 *
 * \details
 * 0 (IN_PROGRESS): Channel initialization is in progress.
 * 1 (TERMINATED): Channel initialization is completed.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH4 . INITD_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH4_INITD_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH4_INITD_CH4  VTSS_BIT(21)
#define  VTSS_X_XDMAC_XDMAC_CC_CH4_INITD_CH4(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * DAM_CH4: Destination Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH4 . DAM_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH4_DAM_CH4(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH4_DAM_CH4     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH4_DAM_CH4(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * SAM_CH4: Source Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH4 . SAM_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH4_SAM_CH4(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH4_SAM_CH4     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH4_SAM_CH4(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * DWIDTH_CH4: Data Width
 *
 * \details
 * 0 (BYTE): The data size is set to 8 bits.
 * 1 (HALFWORD): The data size is set to 16 bits.
 * 2 (WORD): The data size is set to 32 bits.
 * 3 (DWORD): The data size is set to 64 bits.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH4 . DWIDTH_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH4_DWIDTH_CH4(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH4_DWIDTH_CH4     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH4_DWIDTH_CH4(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * CSIZE_CH4: Chunk Size
 *
 * \details
 * 0 (CHK_1): 1 data transferred
 * 2 (CHK_2): 2 data transferred
 * 4 (CHK_4): 4 data transferred
 * 8 (CHK_8): 8 data transferred
 * 16 (CHK_16): 16 data transferred
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH4 . CSIZE_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH4_CSIZE_CH4(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_XDMAC_XDMAC_CC_CH4_CSIZE_CH4     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_XDMAC_XDMAC_CC_CH4_CSIZE_CH4(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * MEMSET_CH4: Fill Block of Memory
 *
 * \details
 * 0 (NORMAL_MODE): Memset is not activated.
 * 1 (HW_MODE): Sets the block of memory pointed by DA field to the
 * specified value. This operation is performed on 8-, 16- or 32-bit basis.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH4 . MEMSET_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH4_MEMSET_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH4_MEMSET_CH4  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH4_MEMSET_CH4(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * SWREQ_CH4: Software Request Trigger
 *
 * \details
 * 0 (HWR_CONNECTED): Hardware request line is connected to the peripheral
 * request line.
 * 1 (SWR_CONNECTED): Software request is connected to the peripheral
 * request line.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH4 . SWREQ_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH4_SWREQ_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH4_SWREQ_CH4  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CC_CH4_SWREQ_CH4(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * PROT_CH4: Channel Protection
 *
 * \details
 * 0 (SEC): Channel is secured.
 * 1 (UNSEC): Channel is unsecured.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH4 . PROT_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH4_PROT_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH4_PROT_CH4   VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CC_CH4_PROT_CH4(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DSYNC_CH4: Channel Synchronization (Peripheral Transfer Direction)
 *
 * \details
 * 0 (PER2MEM): Peripheral-to-memory transfer.
 * 1 (MEM2PER): Memory-to-peripheral transfer.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH4 . DSYNC_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH4_DSYNC_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH4_DSYNC_CH4  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CC_CH4_DSYNC_CH4(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * MBSIZE_CH4: Memory Burst Size
 *
 * \details
 * 0 (SINGLE): The memory burst size is set to one.
 * 1 (FOUR): The memory burst size is set to four.
 * 2 (EIGHT): The memory burst size is set to eight.
 * 3 (SIXTEEN): The memory burst size is set to sixteen.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH4 . MBSIZE_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH4_MBSIZE_CH4(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH4_MBSIZE_CH4     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH4_MBSIZE_CH4(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * TYPE_CH4: Transfer Type
 *
 * \details
 * 0 (MEM_TRAN): Self-triggered mode (memory-to-memory transfer).
 * 1 (PER_TRAN): Synchronized mode (peripheral-to-memory or
 * memory-to-peripheral transfer).
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH4 . TYPE_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH4_TYPE_CH4(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH4_TYPE_CH4   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CC_CH4_TYPE_CH4(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 4 Data Stride Memory Set Pattern Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDS_MSP_CH4
 */
#define VTSS_XDMAC_XDMAC_CDS_MSP_CH4         VTSS_IOREG(VTSS_TO_XDMAC,0x63)

/**
 * \brief
 * DDS_MSP_CH4: Destination Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the destination data
 * stride.Number of bytes for the data stride of channel x (two's
 * complement). If the field is set to zero the data is contiguous.The
 * DDS_MSP_CHx field is only relevant when XDMAC_CCx.DAM=UBS_DS_AM.When
 * XDMAC_CCx.MEMSET = 1, this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH4 . DDS_MSP_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH4_DDS_MSP_CH4(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH4_DDS_MSP_CH4     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH4_DDS_MSP_CH4(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * SDS_MSP_CH4: Source Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the source data stride.Number
 * of bytes for the data stride of channel x (two's complement). If the
 * field is set to zero the data is contiguous.The SDS_MSP_CHx field is
 * only relevant when XDMAC_CCx.SAM=UBS_DS_AM.When XDMAC_CCx.MEMSET = 1,
 * this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH4 . SDS_MSP_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH4_SDS_MSP_CH4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH4_SDS_MSP_CH4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH4_SDS_MSP_CH4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief XDMAC Channel 4 Source Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSUS_CH4
 */
#define VTSS_XDMAC_XDMAC_CSUS_CH4            VTSS_IOREG(VTSS_TO_XDMAC,0x64)

/**
 * \brief
 * SUBS_CH4: Source Microblock StrideNumber of bytes for the microblock
 * stride for channel x (two's comlpement). If the field is set to zero the
 * data is contiguous.SUBS_CHx field is only relevant when
 * XDMAC_CCx.SAM=UBS_AM or XDMAC_CCx.SAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSUS_CH4 . SUBS_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CSUS_CH4_SUBS_CH4(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CSUS_CH4_SUBS_CH4     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CSUS_CH4_SUBS_CH4(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 4 Destination Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDUS_CH4
 */
#define VTSS_XDMAC_XDMAC_CDUS_CH4            VTSS_IOREG(VTSS_TO_XDMAC,0x65)

/**
 * \brief
 * DUBS_CH4: Destination Microblock StrideNumber of bytes for the
 * microblock stride for channel x (two's comlpement). If the field is set
 * to zero the data is contiguous.DUBS_CHx field is only relevant when
 * XDMAC_CCx.DAM=UBS_AM or XDMAC_CCx.DAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDUS_CH4 . DUBS_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CDUS_CH4_DUBS_CH4(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CDUS_CH4_DUBS_CH4     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CDUS_CH4_DUBS_CH4(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 4 Transfer Count Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CTCS_CH4
 */
#define VTSS_XDMAC_XDMAC_CTCS_CH4            VTSS_IOREG(VTSS_TO_XDMAC,0x66)

/**
 * \brief
 * TC_CH4: Transfer CountNumber of bytes written by the XDMA since the last
 * read of the Transfer Count Status register. The field does not indicate
 * the number of bytes written to memory.To get the number of bytes already
 * written in memory at any time during peripheral-to-memory transfer, use
 * the following software procedure:1. Read the XDMAC_CTCSx.TC field to
 * sample the number of bytes received by the XDMA.2. Perform a software
 * flush of the channel by writing one to the XDMAC_GSWF register. This
 * will push bytes from the internal DMA FIFO to the external memory and
 * return an interrupt when the bytes can be read by the CPU.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CTCS_CH4 . TC_CH4
 */
#define  VTSS_F_XDMAC_XDMAC_CTCS_CH4_TC_CH4(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CTCS_CH4_TC_CH4     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CTCS_CH4_TC_CH4(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 5 Interrupt Enable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIE_CH5
 */
#define VTSS_XDMAC_XDMAC_CIE_CH5             VTSS_IOREG(VTSS_TO_XDMAC,0x68)

/**
 * \brief
 * TCIE_CH5: Transfer Count Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH5 . TCIE_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH5_TCIE_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH5_TCIE_CH5  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH5_TCIE_CH5(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIE_CH5: Request Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH5 . ROIE_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH5_ROIE_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH5_ROIE_CH5  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH5_ROIE_CH5(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBIE_CH5: Write Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables write bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH5 . WBIE_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH5_WBIE_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH5_WBIE_CH5  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH5_WBIE_CH5(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBIE_CH5: Read Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables read bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH5 . RBIE_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH5_RBIE_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH5_RBIE_CH5  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH5_RBIE_CH5(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIE_CH5: End of Flush Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH5 . FIE_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH5_FIE_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH5_FIE_CH5   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH5_FIE_CH5(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIE_CH5: End of Disable Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH5 . DIE_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH5_DIE_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH5_DIE_CH5   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH5_DIE_CH5(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIE_CH5: End of Linked List Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH5 . LIE_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH5_LIE_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH5_LIE_CH5   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH5_LIE_CH5(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIE_CH5: End of Block Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH5 . BIE_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH5_BIE_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH5_BIE_CH5   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH5_BIE_CH5(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 5 Interrupt Disable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CID_CH5
 */
#define VTSS_XDMAC_XDMAC_CID_CH5             VTSS_IOREG(VTSS_TO_XDMAC,0x69)

/**
 * \brief
 * TCID_CH5: Transfer Count Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH5 . TCID_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH5_TCID_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH5_TCID_CH5  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CID_CH5_TCID_CH5(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROID_CH5: Request Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH5 . ROID_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH5_ROID_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH5_ROID_CH5  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CID_CH5_ROID_CH5(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEID_CH5: Write Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH5 . WBEID_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH5_WBEID_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH5_WBEID_CH5  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CID_CH5_WBEID_CH5(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEID_CH5: Read Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH5 . RBEID_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH5_RBEID_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH5_RBEID_CH5  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CID_CH5_RBEID_CH5(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FID_CH5: End of Flush Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH5 . FID_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH5_FID_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH5_FID_CH5   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CID_CH5_FID_CH5(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DID_CH5: End of Disable Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH5 . DID_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH5_DID_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH5_DID_CH5   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CID_CH5_DID_CH5(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LID_CH5: End of Linked List Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH5 . LID_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH5_LID_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH5_LID_CH5   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CID_CH5_LID_CH5(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BID_CH5: End of Block Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH5 . BID_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH5_BID_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH5_BID_CH5   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CID_CH5_BID_CH5(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 5 Interrupt Mask Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIM_CH5
 */
#define VTSS_XDMAC_XDMAC_CIM_CH5             VTSS_IOREG(VTSS_TO_XDMAC,0x6a)

/**
 * \brief
 * TCIM_CH5: Transfer Count Overflow Error Interrupt Mask
 *
 * \details
 * 0: Transfer count overflow interrupt is masked.
 * 1: Transfer count overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH5 . TCIM_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH5_TCIM_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH5_TCIM_CH5  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH5_TCIM_CH5(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIM_CH5: Request Overflow Error Interrupt Mask
 *
 * \details
 * 0: Request overflow interrupt is masked.
 * 1: Request overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH5 . ROIM_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH5_ROIM_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH5_ROIM_CH5  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH5_ROIM_CH5(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIM_CH5: Write Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH5 . WBEIM_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH5_WBEIM_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH5_WBEIM_CH5  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH5_WBEIM_CH5(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIM_CH5: Read Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH5 . RBEIM_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH5_RBEIM_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH5_RBEIM_CH5  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH5_RBEIM_CH5(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIM_CH5: End of Flush Interrupt Mask
 *
 * \details
 * 0: End of flush interrupt is masked.
 * 1: End of flush interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH5 . FIM_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH5_FIM_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH5_FIM_CH5   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH5_FIM_CH5(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIM_CH5: End of Disable Interrupt Mask
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH5 . DIM_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH5_DIM_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH5_DIM_CH5   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH5_DIM_CH5(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIM_CH5: End of Linked List Interrupt Mask
 *
 * \details
 * 0: End of linked list interrupt is masked.
 * 1: End of linked list interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH5 . LIM_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH5_LIM_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH5_LIM_CH5   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH5_LIM_CH5(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIM_CH5: End of Block Interrupt Mask
 *
 * \details
 * 0: Block interrupt is masked.
 * 1: Block interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH5 . BIM_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH5_BIM_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH5_BIM_CH5   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH5_BIM_CH5(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 5 Interrupt Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIS_CH5
 */
#define VTSS_XDMAC_XDMAC_CIS_CH5             VTSS_IOREG(VTSS_TO_XDMAC,0x6b)

/**
 * \brief
 * TCIS_CH5: Transfer Count Overflow Interrupt Status
 *
 * \details
 * 0: Transfer count overflow has not occurred.
 * 1: At least one transfer count overflow has been detected since the last
 * read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH5 . TCIS_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH5_TCIS_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH5_TCIS_CH5  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH5_TCIS_CH5(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIS_CH5: Request Overflow Error Interrupt Status
 *
 * \details
 * 0: Overflow condition has not occurred.
 * 1: Overflow condition has occurred at least once. (This information is
 * only relevant for peripheral synchronized transfers.)
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH5 . ROIS_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH5_ROIS_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH5_ROIS_CH5  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH5_ROIS_CH5(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIS_CH5: Write Bus Error Interrupt Status
 *
 * \details
 * 0: Write bus error condition has not occurred.
 * 1: At least one bus error has been detected in a write access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH5 . WBEIS_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH5_WBEIS_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH5_WBEIS_CH5  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH5_WBEIS_CH5(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIS_CH5: Read Bus Error Interrupt Status
 *
 * \details
 * 0: Read bus error condition has not occurred.
 * 1: At least one bus error has been detected in a read access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH5 . RBEIS_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH5_RBEIS_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH5_RBEIS_CH5  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH5_RBEIS_CH5(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIS_CH5: End of Flush Interrupt Status
 *
 * \details
 * 0: End of flush condition has not occurred.
 * 1: End of flush condition has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH5 . FIS_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH5_FIS_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH5_FIS_CH5   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH5_FIS_CH5(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIS_CH5: End of Disable Interrupt Status
 *
 * \details
 * 0: End of disable condition has not occurred.
 * 1: End of disable condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH5 . DIS_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH5_DIS_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH5_DIS_CH5   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH5_DIS_CH5(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIS_CH5: End of Linked List Interrupt Status
 *
 * \details
 * 0: End of linked list condition has not occurred.
 * 1: End of linked list condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH5 . LIS_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH5_LIS_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH5_LIS_CH5   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH5_LIS_CH5(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIS_CH5: End of Block Interrupt Status
 *
 * \details
 * 0: End of block interrupt has not occurred.
 * 1: End of block interrupt has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH5 . BIS_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH5_BIS_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH5_BIS_CH5   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH5_BIS_CH5(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 5 Source Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSA_CH5
 */
#define VTSS_XDMAC_XDMAC_CSA_CH5             VTSS_IOREG(VTSS_TO_XDMAC,0x6c)

/**
 * \brief
 * SA_CH5: Source AddressProgram this register with the source address of
 * the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSA_CH5 . SA_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CSA_CH5_SA_CH5(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CSA_CH5_SA_CH5     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CSA_CH5_SA_CH5(x)  (x)


/**
 * \brief XDMAC Channel 5 Destination Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDA_CH5
 */
#define VTSS_XDMAC_XDMAC_CDA_CH5             VTSS_IOREG(VTSS_TO_XDMAC,0x6d)

/**
 * \brief
 * DA_CH5: Destination AddressProgram this register with the destination
 * address of the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDA_CH5 . DA_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CDA_CH5_DA_CH5(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CDA_CH5_DA_CH5     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CDA_CH5_DA_CH5(x)  (x)


/**
 * \brief XDMAC Channel 5 Next Descriptor Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDA_CH5
 */
#define VTSS_XDMAC_XDMAC_CNDA_CH5            VTSS_IOREG(VTSS_TO_XDMAC,0x6e)

/**
 * \brief
 * NDA_CH5: Next Descriptor AddressThe 30-bit width of the NDA field
 * represents the next descriptor address range 31:2. The descriptor is
 * word-aligned and the two least significant register bits 1:0 are
 * ignored.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDA_CH5 . NDA_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CNDA_CH5_NDA_CH5(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_XDMAC_XDMAC_CNDA_CH5_NDA_CH5     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_XDMAC_XDMAC_CNDA_CH5_NDA_CH5(x)  VTSS_EXTRACT_BITFIELD(x,2,30)


/**
 * \brief XDMAC Channel 5 Next Descriptor Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDC_CH5
 */
#define VTSS_XDMAC_XDMAC_CNDC_CH5            VTSS_IOREG(VTSS_TO_XDMAC,0x6f)

/**
 * \brief
 * QOS_CH5: Channel Quality Of Service LevelThis field indicates the
 * current quality of service level for the channel.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH5 . QOS_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH5_QOS_CH5(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH5_QOS_CH5     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH5_QOS_CH5(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * NDVIEW_CH5: Next Descriptor View
 *
 * \details
 * 0 (NDV0): Next Descriptor View 0
 * 1 (NDV0): Next Descriptor View 1
 * 2 (NDV0): Next Descriptor View 2
 * 3 (NDV0): Next Descriptor View 3
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH5 . NDVIEW_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH5_NDVIEW_CH5(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH5_NDVIEW_CH5     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH5_NDVIEW_CH5(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * NDDUP_CH5: Next Descriptor Destination Update
 *
 * \details
 * 0 (DST_PARAMS_UNCHANGED): Destination parameters remain unchanged.
 * 1 (DST_PARAMS_UPDATED): Destination parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH5 . NDDUP_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH5_NDDUP_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH5_NDDUP_CH5  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH5_NDDUP_CH5(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * NDSUP_CH5: Next Descriptor Source Update
 *
 * \details
 * 0 (SRC_PARAMS_UNCHANGED): Source parameters remain unchanged.
 * 1 (SRC_PARAMS_UPDATED): Source parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH5 . NDSUP_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH5_NDSUP_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH5_NDSUP_CH5  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH5_NDSUP_CH5(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * NDE_CH5: Next Descriptor Enable
 *
 * \details
 * 0 (DSCR_FETCH_DIS): Descriptor fetch is disabled.
 * 1 (DSCR_FETCH_EN): Descriptor fetch is enabled.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH5 . NDE_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH5_NDE_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH5_NDE_CH5  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH5_NDE_CH5(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 5 Microblock Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CUBC_CH5
 */
#define VTSS_XDMAC_XDMAC_CUBC_CH5            VTSS_IOREG(VTSS_TO_XDMAC,0x70)

/**
 * \brief
 * UBLEN_CH5: Microblock LengthThis field indicates the number of data in
 * the microblock. The microblock contains UBLEN data.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CUBC_CH5 . UBLEN_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CUBC_CH5_UBLEN_CH5(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CUBC_CH5_UBLEN_CH5     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CUBC_CH5_UBLEN_CH5(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 5 Block Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CBC_CH5
 */
#define VTSS_XDMAC_XDMAC_CBC_CH5             VTSS_IOREG(VTSS_TO_XDMAC,0x71)

/**
 * \brief
 * BLEN_CH5: Block LengthThe length of the block is (BLEN+1) microblocks.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CBC_CH5 . BLEN_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CBC_CH5_BLEN_CH5(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_XDMAC_XDMAC_CBC_CH5_BLEN_CH5     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_XDMAC_XDMAC_CBC_CH5_BLEN_CH5(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief XDMAC Channel 5 Configuration Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CC_CH5
 */
#define VTSS_XDMAC_XDMAC_CC_CH5              VTSS_IOREG(VTSS_TO_XDMAC,0x72)

/**
 * \brief
 * PERID_CH5: Peripheral Hardware Request Line IdentifierThis field
 * contains the peripheral hardware request line identifier.Note: When a
 * memory-to-memory transfer is performed, configure PERID to an unused
 * peripheral ID.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH5 . PERID_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH5_PERID_CH5(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_XDMAC_XDMAC_CC_CH5_PERID_CH5     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH5_PERID_CH5(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * WRIP_CH5: Write in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active write transaction on the bus.
 * 1 (IN_PROGRESS): A write transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH5 . WRIP_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH5_WRIP_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH5_WRIP_CH5   VTSS_BIT(23)
#define  VTSS_X_XDMAC_XDMAC_CC_CH5_WRIP_CH5(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * RDIP_CH5: Read in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active read transaction on the bus.
 * 1 (IN_PROGRESS): A read transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH5 . RDIP_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH5_RDIP_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH5_RDIP_CH5   VTSS_BIT(22)
#define  VTSS_X_XDMAC_XDMAC_CC_CH5_RDIP_CH5(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * INITD_CH5: Channel Initialization Done (this bit is read-only)Note: When
 * set to 0, XDMAC_CUBC_CH5.UBLEN_CH5 and XDMAC_CNDA_CH5.NDA_CH5 field
 * values are unreliable each time a descriptor is being updated.
 *
 * \details
 * 0 (IN_PROGRESS): Channel initialization is in progress.
 * 1 (TERMINATED): Channel initialization is completed.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH5 . INITD_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH5_INITD_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH5_INITD_CH5  VTSS_BIT(21)
#define  VTSS_X_XDMAC_XDMAC_CC_CH5_INITD_CH5(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * DAM_CH5: Destination Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH5 . DAM_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH5_DAM_CH5(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH5_DAM_CH5     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH5_DAM_CH5(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * SAM_CH5: Source Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH5 . SAM_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH5_SAM_CH5(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH5_SAM_CH5     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH5_SAM_CH5(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * DWIDTH_CH5: Data Width
 *
 * \details
 * 0 (BYTE): The data size is set to 8 bits.
 * 1 (HALFWORD): The data size is set to 16 bits.
 * 2 (WORD): The data size is set to 32 bits.
 * 3 (DWORD): The data size is set to 64 bits.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH5 . DWIDTH_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH5_DWIDTH_CH5(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH5_DWIDTH_CH5     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH5_DWIDTH_CH5(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * CSIZE_CH5: Chunk Size
 *
 * \details
 * 0 (CHK_1): 1 data transferred
 * 2 (CHK_2): 2 data transferred
 * 4 (CHK_4): 4 data transferred
 * 8 (CHK_8): 8 data transferred
 * 16 (CHK_16): 16 data transferred
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH5 . CSIZE_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH5_CSIZE_CH5(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_XDMAC_XDMAC_CC_CH5_CSIZE_CH5     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_XDMAC_XDMAC_CC_CH5_CSIZE_CH5(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * MEMSET_CH5: Fill Block of Memory
 *
 * \details
 * 0 (NORMAL_MODE): Memset is not activated.
 * 1 (HW_MODE): Sets the block of memory pointed by DA field to the
 * specified value. This operation is performed on 8-, 16- or 32-bit basis.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH5 . MEMSET_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH5_MEMSET_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH5_MEMSET_CH5  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH5_MEMSET_CH5(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * SWREQ_CH5: Software Request Trigger
 *
 * \details
 * 0 (HWR_CONNECTED): Hardware request line is connected to the peripheral
 * request line.
 * 1 (SWR_CONNECTED): Software request is connected to the peripheral
 * request line.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH5 . SWREQ_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH5_SWREQ_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH5_SWREQ_CH5  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CC_CH5_SWREQ_CH5(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * PROT_CH5: Channel Protection
 *
 * \details
 * 0 (SEC): Channel is secured.
 * 1 (UNSEC): Channel is unsecured.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH5 . PROT_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH5_PROT_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH5_PROT_CH5   VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CC_CH5_PROT_CH5(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DSYNC_CH5: Channel Synchronization (Peripheral Transfer Direction)
 *
 * \details
 * 0 (PER2MEM): Peripheral-to-memory transfer.
 * 1 (MEM2PER): Memory-to-peripheral transfer.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH5 . DSYNC_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH5_DSYNC_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH5_DSYNC_CH5  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CC_CH5_DSYNC_CH5(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * MBSIZE_CH5: Memory Burst Size
 *
 * \details
 * 0 (SINGLE): The memory burst size is set to one.
 * 1 (FOUR): The memory burst size is set to four.
 * 2 (EIGHT): The memory burst size is set to eight.
 * 3 (SIXTEEN): The memory burst size is set to sixteen.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH5 . MBSIZE_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH5_MBSIZE_CH5(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH5_MBSIZE_CH5     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH5_MBSIZE_CH5(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * TYPE_CH5: Transfer Type
 *
 * \details
 * 0 (MEM_TRAN): Self-triggered mode (memory-to-memory transfer).
 * 1 (PER_TRAN): Synchronized mode (peripheral-to-memory or
 * memory-to-peripheral transfer).
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH5 . TYPE_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH5_TYPE_CH5(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH5_TYPE_CH5   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CC_CH5_TYPE_CH5(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 5 Data Stride Memory Set Pattern Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDS_MSP_CH5
 */
#define VTSS_XDMAC_XDMAC_CDS_MSP_CH5         VTSS_IOREG(VTSS_TO_XDMAC,0x73)

/**
 * \brief
 * DDS_MSP_CH5: Destination Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the destination data
 * stride.Number of bytes for the data stride of channel x (two's
 * complement). If the field is set to zero the data is contiguous.The
 * DDS_MSP_CHx field is only relevant when XDMAC_CCx.DAM=UBS_DS_AM.When
 * XDMAC_CCx.MEMSET = 1, this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH5 . DDS_MSP_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH5_DDS_MSP_CH5(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH5_DDS_MSP_CH5     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH5_DDS_MSP_CH5(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * SDS_MSP_CH5: Source Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the source data stride.Number
 * of bytes for the data stride of channel x (two's complement). If the
 * field is set to zero the data is contiguous.The SDS_MSP_CHx field is
 * only relevant when XDMAC_CCx.SAM=UBS_DS_AM.When XDMAC_CCx.MEMSET = 1,
 * this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH5 . SDS_MSP_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH5_SDS_MSP_CH5(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH5_SDS_MSP_CH5     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH5_SDS_MSP_CH5(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief XDMAC Channel 5 Source Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSUS_CH5
 */
#define VTSS_XDMAC_XDMAC_CSUS_CH5            VTSS_IOREG(VTSS_TO_XDMAC,0x74)

/**
 * \brief
 * SUBS_CH5: Source Microblock StrideNumber of bytes for the microblock
 * stride for channel x (two's comlpement). If the field is set to zero the
 * data is contiguous.SUBS_CHx field is only relevant when
 * XDMAC_CCx.SAM=UBS_AM or XDMAC_CCx.SAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSUS_CH5 . SUBS_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CSUS_CH5_SUBS_CH5(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CSUS_CH5_SUBS_CH5     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CSUS_CH5_SUBS_CH5(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 5 Destination Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDUS_CH5
 */
#define VTSS_XDMAC_XDMAC_CDUS_CH5            VTSS_IOREG(VTSS_TO_XDMAC,0x75)

/**
 * \brief
 * DUBS_CH5: Destination Microblock StrideNumber of bytes for the
 * microblock stride for channel x (two's comlpement). If the field is set
 * to zero the data is contiguous.DUBS_CHx field is only relevant when
 * XDMAC_CCx.DAM=UBS_AM or XDMAC_CCx.DAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDUS_CH5 . DUBS_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CDUS_CH5_DUBS_CH5(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CDUS_CH5_DUBS_CH5     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CDUS_CH5_DUBS_CH5(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 5 Transfer Count Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CTCS_CH5
 */
#define VTSS_XDMAC_XDMAC_CTCS_CH5            VTSS_IOREG(VTSS_TO_XDMAC,0x76)

/**
 * \brief
 * TC_CH5: Transfer CountNumber of bytes written by the XDMA since the last
 * read of the Transfer Count Status register. The field does not indicate
 * the number of bytes written to memory.To get the number of bytes already
 * written in memory at any time during peripheral-to-memory transfer, use
 * the following software procedure:1. Read the XDMAC_CTCSx.TC field to
 * sample the number of bytes received by the XDMA.2. Perform a software
 * flush of the channel by writing one to the XDMAC_GSWF register. This
 * will push bytes from the internal DMA FIFO to the external memory and
 * return an interrupt when the bytes can be read by the CPU.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CTCS_CH5 . TC_CH5
 */
#define  VTSS_F_XDMAC_XDMAC_CTCS_CH5_TC_CH5(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CTCS_CH5_TC_CH5     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CTCS_CH5_TC_CH5(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 6 Interrupt Enable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIE_CH6
 */
#define VTSS_XDMAC_XDMAC_CIE_CH6             VTSS_IOREG(VTSS_TO_XDMAC,0x78)

/**
 * \brief
 * TCIE_CH6: Transfer Count Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH6 . TCIE_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH6_TCIE_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH6_TCIE_CH6  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH6_TCIE_CH6(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIE_CH6: Request Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH6 . ROIE_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH6_ROIE_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH6_ROIE_CH6  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH6_ROIE_CH6(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBIE_CH6: Write Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables write bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH6 . WBIE_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH6_WBIE_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH6_WBIE_CH6  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH6_WBIE_CH6(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBIE_CH6: Read Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables read bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH6 . RBIE_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH6_RBIE_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH6_RBIE_CH6  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH6_RBIE_CH6(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIE_CH6: End of Flush Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH6 . FIE_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH6_FIE_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH6_FIE_CH6   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH6_FIE_CH6(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIE_CH6: End of Disable Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH6 . DIE_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH6_DIE_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH6_DIE_CH6   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH6_DIE_CH6(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIE_CH6: End of Linked List Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH6 . LIE_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH6_LIE_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH6_LIE_CH6   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH6_LIE_CH6(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIE_CH6: End of Block Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH6 . BIE_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH6_BIE_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH6_BIE_CH6   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH6_BIE_CH6(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 6 Interrupt Disable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CID_CH6
 */
#define VTSS_XDMAC_XDMAC_CID_CH6             VTSS_IOREG(VTSS_TO_XDMAC,0x79)

/**
 * \brief
 * TCID_CH6: Transfer Count Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH6 . TCID_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH6_TCID_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH6_TCID_CH6  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CID_CH6_TCID_CH6(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROID_CH6: Request Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH6 . ROID_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH6_ROID_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH6_ROID_CH6  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CID_CH6_ROID_CH6(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEID_CH6: Write Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH6 . WBEID_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH6_WBEID_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH6_WBEID_CH6  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CID_CH6_WBEID_CH6(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEID_CH6: Read Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH6 . RBEID_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH6_RBEID_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH6_RBEID_CH6  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CID_CH6_RBEID_CH6(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FID_CH6: End of Flush Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH6 . FID_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH6_FID_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH6_FID_CH6   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CID_CH6_FID_CH6(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DID_CH6: End of Disable Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH6 . DID_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH6_DID_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH6_DID_CH6   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CID_CH6_DID_CH6(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LID_CH6: End of Linked List Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH6 . LID_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH6_LID_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH6_LID_CH6   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CID_CH6_LID_CH6(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BID_CH6: End of Block Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH6 . BID_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH6_BID_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH6_BID_CH6   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CID_CH6_BID_CH6(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 6 Interrupt Mask Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIM_CH6
 */
#define VTSS_XDMAC_XDMAC_CIM_CH6             VTSS_IOREG(VTSS_TO_XDMAC,0x7a)

/**
 * \brief
 * TCIM_CH6: Transfer Count Overflow Error Interrupt Mask
 *
 * \details
 * 0: Transfer count overflow interrupt is masked.
 * 1: Transfer count overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH6 . TCIM_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH6_TCIM_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH6_TCIM_CH6  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH6_TCIM_CH6(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIM_CH6: Request Overflow Error Interrupt Mask
 *
 * \details
 * 0: Request overflow interrupt is masked.
 * 1: Request overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH6 . ROIM_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH6_ROIM_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH6_ROIM_CH6  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH6_ROIM_CH6(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIM_CH6: Write Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH6 . WBEIM_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH6_WBEIM_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH6_WBEIM_CH6  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH6_WBEIM_CH6(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIM_CH6: Read Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH6 . RBEIM_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH6_RBEIM_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH6_RBEIM_CH6  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH6_RBEIM_CH6(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIM_CH6: End of Flush Interrupt Mask
 *
 * \details
 * 0: End of flush interrupt is masked.
 * 1: End of flush interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH6 . FIM_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH6_FIM_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH6_FIM_CH6   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH6_FIM_CH6(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIM_CH6: End of Disable Interrupt Mask
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH6 . DIM_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH6_DIM_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH6_DIM_CH6   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH6_DIM_CH6(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIM_CH6: End of Linked List Interrupt Mask
 *
 * \details
 * 0: End of linked list interrupt is masked.
 * 1: End of linked list interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH6 . LIM_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH6_LIM_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH6_LIM_CH6   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH6_LIM_CH6(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIM_CH6: End of Block Interrupt Mask
 *
 * \details
 * 0: Block interrupt is masked.
 * 1: Block interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH6 . BIM_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH6_BIM_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH6_BIM_CH6   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH6_BIM_CH6(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 6 Interrupt Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIS_CH6
 */
#define VTSS_XDMAC_XDMAC_CIS_CH6             VTSS_IOREG(VTSS_TO_XDMAC,0x7b)

/**
 * \brief
 * TCIS_CH6: Transfer Count Overflow Interrupt Status
 *
 * \details
 * 0: Transfer count overflow has not occurred.
 * 1: At least one transfer count overflow has been detected since the last
 * read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH6 . TCIS_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH6_TCIS_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH6_TCIS_CH6  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH6_TCIS_CH6(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIS_CH6: Request Overflow Error Interrupt Status
 *
 * \details
 * 0: Overflow condition has not occurred.
 * 1: Overflow condition has occurred at least once. (This information is
 * only relevant for peripheral synchronized transfers.)
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH6 . ROIS_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH6_ROIS_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH6_ROIS_CH6  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH6_ROIS_CH6(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIS_CH6: Write Bus Error Interrupt Status
 *
 * \details
 * 0: Write bus error condition has not occurred.
 * 1: At least one bus error has been detected in a write access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH6 . WBEIS_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH6_WBEIS_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH6_WBEIS_CH6  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH6_WBEIS_CH6(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIS_CH6: Read Bus Error Interrupt Status
 *
 * \details
 * 0: Read bus error condition has not occurred.
 * 1: At least one bus error has been detected in a read access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH6 . RBEIS_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH6_RBEIS_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH6_RBEIS_CH6  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH6_RBEIS_CH6(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIS_CH6: End of Flush Interrupt Status
 *
 * \details
 * 0: End of flush condition has not occurred.
 * 1: End of flush condition has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH6 . FIS_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH6_FIS_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH6_FIS_CH6   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH6_FIS_CH6(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIS_CH6: End of Disable Interrupt Status
 *
 * \details
 * 0: End of disable condition has not occurred.
 * 1: End of disable condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH6 . DIS_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH6_DIS_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH6_DIS_CH6   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH6_DIS_CH6(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIS_CH6: End of Linked List Interrupt Status
 *
 * \details
 * 0: End of linked list condition has not occurred.
 * 1: End of linked list condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH6 . LIS_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH6_LIS_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH6_LIS_CH6   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH6_LIS_CH6(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIS_CH6: End of Block Interrupt Status
 *
 * \details
 * 0: End of block interrupt has not occurred.
 * 1: End of block interrupt has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH6 . BIS_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH6_BIS_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH6_BIS_CH6   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH6_BIS_CH6(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 6 Source Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSA_CH6
 */
#define VTSS_XDMAC_XDMAC_CSA_CH6             VTSS_IOREG(VTSS_TO_XDMAC,0x7c)

/**
 * \brief
 * SA_CH6: Source AddressProgram this register with the source address of
 * the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSA_CH6 . SA_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CSA_CH6_SA_CH6(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CSA_CH6_SA_CH6     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CSA_CH6_SA_CH6(x)  (x)


/**
 * \brief XDMAC Channel 6 Destination Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDA_CH6
 */
#define VTSS_XDMAC_XDMAC_CDA_CH6             VTSS_IOREG(VTSS_TO_XDMAC,0x7d)

/**
 * \brief
 * DA_CH6: Destination AddressProgram this register with the destination
 * address of the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDA_CH6 . DA_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CDA_CH6_DA_CH6(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CDA_CH6_DA_CH6     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CDA_CH6_DA_CH6(x)  (x)


/**
 * \brief XDMAC Channel 6 Next Descriptor Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDA_CH6
 */
#define VTSS_XDMAC_XDMAC_CNDA_CH6            VTSS_IOREG(VTSS_TO_XDMAC,0x7e)

/**
 * \brief
 * NDA_CH6: Next Descriptor AddressThe 30-bit width of the NDA field
 * represents the next descriptor address range 31:2. The descriptor is
 * word-aligned and the two least significant register bits 1:0 are
 * ignored.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDA_CH6 . NDA_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CNDA_CH6_NDA_CH6(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_XDMAC_XDMAC_CNDA_CH6_NDA_CH6     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_XDMAC_XDMAC_CNDA_CH6_NDA_CH6(x)  VTSS_EXTRACT_BITFIELD(x,2,30)


/**
 * \brief XDMAC Channel 6 Next Descriptor Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDC_CH6
 */
#define VTSS_XDMAC_XDMAC_CNDC_CH6            VTSS_IOREG(VTSS_TO_XDMAC,0x7f)

/**
 * \brief
 * QOS_CH6: Channel Quality Of Service LevelThis field indicates the
 * current quality of service level for the channel.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH6 . QOS_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH6_QOS_CH6(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH6_QOS_CH6     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH6_QOS_CH6(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * NDVIEW_CH6: Next Descriptor View
 *
 * \details
 * 0 (NDV0): Next Descriptor View 0
 * 1 (NDV0): Next Descriptor View 1
 * 2 (NDV0): Next Descriptor View 2
 * 3 (NDV0): Next Descriptor View 3
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH6 . NDVIEW_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH6_NDVIEW_CH6(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH6_NDVIEW_CH6     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH6_NDVIEW_CH6(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * NDDUP_CH6: Next Descriptor Destination Update
 *
 * \details
 * 0 (DST_PARAMS_UNCHANGED): Destination parameters remain unchanged.
 * 1 (DST_PARAMS_UPDATED): Destination parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH6 . NDDUP_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH6_NDDUP_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH6_NDDUP_CH6  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH6_NDDUP_CH6(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * NDSUP_CH6: Next Descriptor Source Update
 *
 * \details
 * 0 (SRC_PARAMS_UNCHANGED): Source parameters remain unchanged.
 * 1 (SRC_PARAMS_UPDATED): Source parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH6 . NDSUP_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH6_NDSUP_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH6_NDSUP_CH6  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH6_NDSUP_CH6(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * NDE_CH6: Next Descriptor Enable
 *
 * \details
 * 0 (DSCR_FETCH_DIS): Descriptor fetch is disabled.
 * 1 (DSCR_FETCH_EN): Descriptor fetch is enabled.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH6 . NDE_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH6_NDE_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH6_NDE_CH6  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH6_NDE_CH6(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 6 Microblock Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CUBC_CH6
 */
#define VTSS_XDMAC_XDMAC_CUBC_CH6            VTSS_IOREG(VTSS_TO_XDMAC,0x80)

/**
 * \brief
 * UBLEN_CH6: Microblock LengthThis field indicates the number of data in
 * the microblock. The microblock contains UBLEN data.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CUBC_CH6 . UBLEN_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CUBC_CH6_UBLEN_CH6(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CUBC_CH6_UBLEN_CH6     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CUBC_CH6_UBLEN_CH6(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 6 Block Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CBC_CH6
 */
#define VTSS_XDMAC_XDMAC_CBC_CH6             VTSS_IOREG(VTSS_TO_XDMAC,0x81)

/**
 * \brief
 * BLEN_CH6: Block LengthThe length of the block is (BLEN+1) microblocks.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CBC_CH6 . BLEN_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CBC_CH6_BLEN_CH6(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_XDMAC_XDMAC_CBC_CH6_BLEN_CH6     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_XDMAC_XDMAC_CBC_CH6_BLEN_CH6(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief XDMAC Channel 6 Configuration Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CC_CH6
 */
#define VTSS_XDMAC_XDMAC_CC_CH6              VTSS_IOREG(VTSS_TO_XDMAC,0x82)

/**
 * \brief
 * PERID_CH6: Peripheral Hardware Request Line IdentifierThis field
 * contains the peripheral hardware request line identifier.Note: When a
 * memory-to-memory transfer is performed, configure PERID to an unused
 * peripheral ID.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH6 . PERID_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH6_PERID_CH6(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_XDMAC_XDMAC_CC_CH6_PERID_CH6     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH6_PERID_CH6(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * WRIP_CH6: Write in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active write transaction on the bus.
 * 1 (IN_PROGRESS): A write transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH6 . WRIP_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH6_WRIP_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH6_WRIP_CH6   VTSS_BIT(23)
#define  VTSS_X_XDMAC_XDMAC_CC_CH6_WRIP_CH6(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * RDIP_CH6: Read in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active read transaction on the bus.
 * 1 (IN_PROGRESS): A read transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH6 . RDIP_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH6_RDIP_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH6_RDIP_CH6   VTSS_BIT(22)
#define  VTSS_X_XDMAC_XDMAC_CC_CH6_RDIP_CH6(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * INITD_CH6: Channel Initialization Done (this bit is read-only)Note: When
 * set to 0, XDMAC_CUBC_CH6.UBLEN_CH6 and XDMAC_CNDA_CH6.NDA_CH6 field
 * values are unreliable each time a descriptor is being updated.
 *
 * \details
 * 0 (IN_PROGRESS): Channel initialization is in progress.
 * 1 (TERMINATED): Channel initialization is completed.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH6 . INITD_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH6_INITD_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH6_INITD_CH6  VTSS_BIT(21)
#define  VTSS_X_XDMAC_XDMAC_CC_CH6_INITD_CH6(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * DAM_CH6: Destination Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH6 . DAM_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH6_DAM_CH6(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH6_DAM_CH6     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH6_DAM_CH6(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * SAM_CH6: Source Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH6 . SAM_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH6_SAM_CH6(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH6_SAM_CH6     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH6_SAM_CH6(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * DWIDTH_CH6: Data Width
 *
 * \details
 * 0 (BYTE): The data size is set to 8 bits.
 * 1 (HALFWORD): The data size is set to 16 bits.
 * 2 (WORD): The data size is set to 32 bits.
 * 3 (DWORD): The data size is set to 64 bits.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH6 . DWIDTH_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH6_DWIDTH_CH6(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH6_DWIDTH_CH6     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH6_DWIDTH_CH6(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * CSIZE_CH6: Chunk Size
 *
 * \details
 * 0 (CHK_1): 1 data transferred
 * 2 (CHK_2): 2 data transferred
 * 4 (CHK_4): 4 data transferred
 * 8 (CHK_8): 8 data transferred
 * 16 (CHK_16): 16 data transferred
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH6 . CSIZE_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH6_CSIZE_CH6(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_XDMAC_XDMAC_CC_CH6_CSIZE_CH6     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_XDMAC_XDMAC_CC_CH6_CSIZE_CH6(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * MEMSET_CH6: Fill Block of Memory
 *
 * \details
 * 0 (NORMAL_MODE): Memset is not activated.
 * 1 (HW_MODE): Sets the block of memory pointed by DA field to the
 * specified value. This operation is performed on 8-, 16- or 32-bit basis.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH6 . MEMSET_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH6_MEMSET_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH6_MEMSET_CH6  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH6_MEMSET_CH6(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * SWREQ_CH6: Software Request Trigger
 *
 * \details
 * 0 (HWR_CONNECTED): Hardware request line is connected to the peripheral
 * request line.
 * 1 (SWR_CONNECTED): Software request is connected to the peripheral
 * request line.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH6 . SWREQ_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH6_SWREQ_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH6_SWREQ_CH6  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CC_CH6_SWREQ_CH6(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * PROT_CH6: Channel Protection
 *
 * \details
 * 0 (SEC): Channel is secured.
 * 1 (UNSEC): Channel is unsecured.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH6 . PROT_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH6_PROT_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH6_PROT_CH6   VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CC_CH6_PROT_CH6(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DSYNC_CH6: Channel Synchronization (Peripheral Transfer Direction)
 *
 * \details
 * 0 (PER2MEM): Peripheral-to-memory transfer.
 * 1 (MEM2PER): Memory-to-peripheral transfer.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH6 . DSYNC_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH6_DSYNC_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH6_DSYNC_CH6  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CC_CH6_DSYNC_CH6(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * MBSIZE_CH6: Memory Burst Size
 *
 * \details
 * 0 (SINGLE): The memory burst size is set to one.
 * 1 (FOUR): The memory burst size is set to four.
 * 2 (EIGHT): The memory burst size is set to eight.
 * 3 (SIXTEEN): The memory burst size is set to sixteen.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH6 . MBSIZE_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH6_MBSIZE_CH6(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH6_MBSIZE_CH6     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH6_MBSIZE_CH6(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * TYPE_CH6: Transfer Type
 *
 * \details
 * 0 (MEM_TRAN): Self-triggered mode (memory-to-memory transfer).
 * 1 (PER_TRAN): Synchronized mode (peripheral-to-memory or
 * memory-to-peripheral transfer).
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH6 . TYPE_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH6_TYPE_CH6(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH6_TYPE_CH6   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CC_CH6_TYPE_CH6(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 6 Data Stride Memory Set Pattern Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDS_MSP_CH6
 */
#define VTSS_XDMAC_XDMAC_CDS_MSP_CH6         VTSS_IOREG(VTSS_TO_XDMAC,0x83)

/**
 * \brief
 * DDS_MSP_CH6: Destination Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the destination data
 * stride.Number of bytes for the data stride of channel x (two's
 * complement). If the field is set to zero the data is contiguous.The
 * DDS_MSP_CHx field is only relevant when XDMAC_CCx.DAM=UBS_DS_AM.When
 * XDMAC_CCx.MEMSET = 1, this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH6 . DDS_MSP_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH6_DDS_MSP_CH6(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH6_DDS_MSP_CH6     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH6_DDS_MSP_CH6(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * SDS_MSP_CH6: Source Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the source data stride.Number
 * of bytes for the data stride of channel x (two's complement). If the
 * field is set to zero the data is contiguous.The SDS_MSP_CHx field is
 * only relevant when XDMAC_CCx.SAM=UBS_DS_AM.When XDMAC_CCx.MEMSET = 1,
 * this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH6 . SDS_MSP_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH6_SDS_MSP_CH6(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH6_SDS_MSP_CH6     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH6_SDS_MSP_CH6(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief XDMAC Channel 6 Source Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSUS_CH6
 */
#define VTSS_XDMAC_XDMAC_CSUS_CH6            VTSS_IOREG(VTSS_TO_XDMAC,0x84)

/**
 * \brief
 * SUBS_CH6: Source Microblock StrideNumber of bytes for the microblock
 * stride for channel x (two's comlpement). If the field is set to zero the
 * data is contiguous.SUBS_CHx field is only relevant when
 * XDMAC_CCx.SAM=UBS_AM or XDMAC_CCx.SAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSUS_CH6 . SUBS_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CSUS_CH6_SUBS_CH6(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CSUS_CH6_SUBS_CH6     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CSUS_CH6_SUBS_CH6(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 6 Destination Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDUS_CH6
 */
#define VTSS_XDMAC_XDMAC_CDUS_CH6            VTSS_IOREG(VTSS_TO_XDMAC,0x85)

/**
 * \brief
 * DUBS_CH6: Destination Microblock StrideNumber of bytes for the
 * microblock stride for channel x (two's comlpement). If the field is set
 * to zero the data is contiguous.DUBS_CHx field is only relevant when
 * XDMAC_CCx.DAM=UBS_AM or XDMAC_CCx.DAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDUS_CH6 . DUBS_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CDUS_CH6_DUBS_CH6(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CDUS_CH6_DUBS_CH6     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CDUS_CH6_DUBS_CH6(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 6 Transfer Count Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CTCS_CH6
 */
#define VTSS_XDMAC_XDMAC_CTCS_CH6            VTSS_IOREG(VTSS_TO_XDMAC,0x86)

/**
 * \brief
 * TC_CH6: Transfer CountNumber of bytes written by the XDMA since the last
 * read of the Transfer Count Status register. The field does not indicate
 * the number of bytes written to memory.To get the number of bytes already
 * written in memory at any time during peripheral-to-memory transfer, use
 * the following software procedure:1. Read the XDMAC_CTCSx.TC field to
 * sample the number of bytes received by the XDMA.2. Perform a software
 * flush of the channel by writing one to the XDMAC_GSWF register. This
 * will push bytes from the internal DMA FIFO to the external memory and
 * return an interrupt when the bytes can be read by the CPU.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CTCS_CH6 . TC_CH6
 */
#define  VTSS_F_XDMAC_XDMAC_CTCS_CH6_TC_CH6(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CTCS_CH6_TC_CH6     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CTCS_CH6_TC_CH6(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 7 Interrupt Enable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIE_CH7
 */
#define VTSS_XDMAC_XDMAC_CIE_CH7             VTSS_IOREG(VTSS_TO_XDMAC,0x88)

/**
 * \brief
 * TCIE_CH7: Transfer Count Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH7 . TCIE_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH7_TCIE_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH7_TCIE_CH7  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH7_TCIE_CH7(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIE_CH7: Request Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH7 . ROIE_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH7_ROIE_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH7_ROIE_CH7  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH7_ROIE_CH7(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBIE_CH7: Write Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables write bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH7 . WBIE_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH7_WBIE_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH7_WBIE_CH7  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH7_WBIE_CH7(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBIE_CH7: Read Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables read bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH7 . RBIE_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH7_RBIE_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH7_RBIE_CH7  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH7_RBIE_CH7(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIE_CH7: End of Flush Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH7 . FIE_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH7_FIE_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH7_FIE_CH7   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH7_FIE_CH7(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIE_CH7: End of Disable Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH7 . DIE_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH7_DIE_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH7_DIE_CH7   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH7_DIE_CH7(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIE_CH7: End of Linked List Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH7 . LIE_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH7_LIE_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH7_LIE_CH7   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH7_LIE_CH7(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIE_CH7: End of Block Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH7 . BIE_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH7_BIE_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH7_BIE_CH7   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH7_BIE_CH7(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 7 Interrupt Disable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CID_CH7
 */
#define VTSS_XDMAC_XDMAC_CID_CH7             VTSS_IOREG(VTSS_TO_XDMAC,0x89)

/**
 * \brief
 * TCID_CH7: Transfer Count Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH7 . TCID_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH7_TCID_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH7_TCID_CH7  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CID_CH7_TCID_CH7(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROID_CH7: Request Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH7 . ROID_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH7_ROID_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH7_ROID_CH7  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CID_CH7_ROID_CH7(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEID_CH7: Write Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH7 . WBEID_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH7_WBEID_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH7_WBEID_CH7  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CID_CH7_WBEID_CH7(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEID_CH7: Read Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH7 . RBEID_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH7_RBEID_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH7_RBEID_CH7  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CID_CH7_RBEID_CH7(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FID_CH7: End of Flush Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH7 . FID_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH7_FID_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH7_FID_CH7   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CID_CH7_FID_CH7(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DID_CH7: End of Disable Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH7 . DID_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH7_DID_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH7_DID_CH7   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CID_CH7_DID_CH7(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LID_CH7: End of Linked List Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH7 . LID_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH7_LID_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH7_LID_CH7   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CID_CH7_LID_CH7(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BID_CH7: End of Block Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH7 . BID_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH7_BID_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH7_BID_CH7   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CID_CH7_BID_CH7(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 7 Interrupt Mask Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIM_CH7
 */
#define VTSS_XDMAC_XDMAC_CIM_CH7             VTSS_IOREG(VTSS_TO_XDMAC,0x8a)

/**
 * \brief
 * TCIM_CH7: Transfer Count Overflow Error Interrupt Mask
 *
 * \details
 * 0: Transfer count overflow interrupt is masked.
 * 1: Transfer count overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH7 . TCIM_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH7_TCIM_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH7_TCIM_CH7  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH7_TCIM_CH7(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIM_CH7: Request Overflow Error Interrupt Mask
 *
 * \details
 * 0: Request overflow interrupt is masked.
 * 1: Request overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH7 . ROIM_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH7_ROIM_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH7_ROIM_CH7  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH7_ROIM_CH7(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIM_CH7: Write Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH7 . WBEIM_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH7_WBEIM_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH7_WBEIM_CH7  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH7_WBEIM_CH7(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIM_CH7: Read Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH7 . RBEIM_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH7_RBEIM_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH7_RBEIM_CH7  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH7_RBEIM_CH7(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIM_CH7: End of Flush Interrupt Mask
 *
 * \details
 * 0: End of flush interrupt is masked.
 * 1: End of flush interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH7 . FIM_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH7_FIM_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH7_FIM_CH7   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH7_FIM_CH7(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIM_CH7: End of Disable Interrupt Mask
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH7 . DIM_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH7_DIM_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH7_DIM_CH7   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH7_DIM_CH7(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIM_CH7: End of Linked List Interrupt Mask
 *
 * \details
 * 0: End of linked list interrupt is masked.
 * 1: End of linked list interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH7 . LIM_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH7_LIM_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH7_LIM_CH7   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH7_LIM_CH7(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIM_CH7: End of Block Interrupt Mask
 *
 * \details
 * 0: Block interrupt is masked.
 * 1: Block interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH7 . BIM_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH7_BIM_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH7_BIM_CH7   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH7_BIM_CH7(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 7 Interrupt Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIS_CH7
 */
#define VTSS_XDMAC_XDMAC_CIS_CH7             VTSS_IOREG(VTSS_TO_XDMAC,0x8b)

/**
 * \brief
 * TCIS_CH7: Transfer Count Overflow Interrupt Status
 *
 * \details
 * 0: Transfer count overflow has not occurred.
 * 1: At least one transfer count overflow has been detected since the last
 * read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH7 . TCIS_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH7_TCIS_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH7_TCIS_CH7  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH7_TCIS_CH7(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIS_CH7: Request Overflow Error Interrupt Status
 *
 * \details
 * 0: Overflow condition has not occurred.
 * 1: Overflow condition has occurred at least once. (This information is
 * only relevant for peripheral synchronized transfers.)
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH7 . ROIS_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH7_ROIS_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH7_ROIS_CH7  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH7_ROIS_CH7(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIS_CH7: Write Bus Error Interrupt Status
 *
 * \details
 * 0: Write bus error condition has not occurred.
 * 1: At least one bus error has been detected in a write access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH7 . WBEIS_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH7_WBEIS_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH7_WBEIS_CH7  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH7_WBEIS_CH7(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIS_CH7: Read Bus Error Interrupt Status
 *
 * \details
 * 0: Read bus error condition has not occurred.
 * 1: At least one bus error has been detected in a read access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH7 . RBEIS_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH7_RBEIS_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH7_RBEIS_CH7  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH7_RBEIS_CH7(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIS_CH7: End of Flush Interrupt Status
 *
 * \details
 * 0: End of flush condition has not occurred.
 * 1: End of flush condition has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH7 . FIS_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH7_FIS_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH7_FIS_CH7   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH7_FIS_CH7(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIS_CH7: End of Disable Interrupt Status
 *
 * \details
 * 0: End of disable condition has not occurred.
 * 1: End of disable condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH7 . DIS_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH7_DIS_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH7_DIS_CH7   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH7_DIS_CH7(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIS_CH7: End of Linked List Interrupt Status
 *
 * \details
 * 0: End of linked list condition has not occurred.
 * 1: End of linked list condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH7 . LIS_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH7_LIS_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH7_LIS_CH7   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH7_LIS_CH7(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIS_CH7: End of Block Interrupt Status
 *
 * \details
 * 0: End of block interrupt has not occurred.
 * 1: End of block interrupt has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH7 . BIS_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH7_BIS_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH7_BIS_CH7   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH7_BIS_CH7(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 7 Source Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSA_CH7
 */
#define VTSS_XDMAC_XDMAC_CSA_CH7             VTSS_IOREG(VTSS_TO_XDMAC,0x8c)

/**
 * \brief
 * SA_CH7: Source AddressProgram this register with the source address of
 * the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSA_CH7 . SA_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CSA_CH7_SA_CH7(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CSA_CH7_SA_CH7     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CSA_CH7_SA_CH7(x)  (x)


/**
 * \brief XDMAC Channel 7 Destination Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDA_CH7
 */
#define VTSS_XDMAC_XDMAC_CDA_CH7             VTSS_IOREG(VTSS_TO_XDMAC,0x8d)

/**
 * \brief
 * DA_CH7: Destination AddressProgram this register with the destination
 * address of the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDA_CH7 . DA_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CDA_CH7_DA_CH7(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CDA_CH7_DA_CH7     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CDA_CH7_DA_CH7(x)  (x)


/**
 * \brief XDMAC Channel 7 Next Descriptor Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDA_CH7
 */
#define VTSS_XDMAC_XDMAC_CNDA_CH7            VTSS_IOREG(VTSS_TO_XDMAC,0x8e)

/**
 * \brief
 * NDA_CH7: Next Descriptor AddressThe 30-bit width of the NDA field
 * represents the next descriptor address range 31:2. The descriptor is
 * word-aligned and the two least significant register bits 1:0 are
 * ignored.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDA_CH7 . NDA_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CNDA_CH7_NDA_CH7(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_XDMAC_XDMAC_CNDA_CH7_NDA_CH7     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_XDMAC_XDMAC_CNDA_CH7_NDA_CH7(x)  VTSS_EXTRACT_BITFIELD(x,2,30)


/**
 * \brief XDMAC Channel 7 Next Descriptor Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDC_CH7
 */
#define VTSS_XDMAC_XDMAC_CNDC_CH7            VTSS_IOREG(VTSS_TO_XDMAC,0x8f)

/**
 * \brief
 * QOS_CH7: Channel Quality Of Service LevelThis field indicates the
 * current quality of service level for the channel.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH7 . QOS_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH7_QOS_CH7(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH7_QOS_CH7     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH7_QOS_CH7(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * NDVIEW_CH7: Next Descriptor View
 *
 * \details
 * 0 (NDV0): Next Descriptor View 0
 * 1 (NDV0): Next Descriptor View 1
 * 2 (NDV0): Next Descriptor View 2
 * 3 (NDV0): Next Descriptor View 3
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH7 . NDVIEW_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH7_NDVIEW_CH7(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH7_NDVIEW_CH7     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH7_NDVIEW_CH7(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * NDDUP_CH7: Next Descriptor Destination Update
 *
 * \details
 * 0 (DST_PARAMS_UNCHANGED): Destination parameters remain unchanged.
 * 1 (DST_PARAMS_UPDATED): Destination parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH7 . NDDUP_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH7_NDDUP_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH7_NDDUP_CH7  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH7_NDDUP_CH7(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * NDSUP_CH7: Next Descriptor Source Update
 *
 * \details
 * 0 (SRC_PARAMS_UNCHANGED): Source parameters remain unchanged.
 * 1 (SRC_PARAMS_UPDATED): Source parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH7 . NDSUP_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH7_NDSUP_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH7_NDSUP_CH7  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH7_NDSUP_CH7(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * NDE_CH7: Next Descriptor Enable
 *
 * \details
 * 0 (DSCR_FETCH_DIS): Descriptor fetch is disabled.
 * 1 (DSCR_FETCH_EN): Descriptor fetch is enabled.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH7 . NDE_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH7_NDE_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH7_NDE_CH7  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH7_NDE_CH7(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 7 Microblock Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CUBC_CH7
 */
#define VTSS_XDMAC_XDMAC_CUBC_CH7            VTSS_IOREG(VTSS_TO_XDMAC,0x90)

/**
 * \brief
 * UBLEN_CH7: Microblock LengthThis field indicates the number of data in
 * the microblock. The microblock contains UBLEN data.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CUBC_CH7 . UBLEN_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CUBC_CH7_UBLEN_CH7(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CUBC_CH7_UBLEN_CH7     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CUBC_CH7_UBLEN_CH7(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 7 Block Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CBC_CH7
 */
#define VTSS_XDMAC_XDMAC_CBC_CH7             VTSS_IOREG(VTSS_TO_XDMAC,0x91)

/**
 * \brief
 * BLEN_CH7: Block LengthThe length of the block is (BLEN+1) microblocks.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CBC_CH7 . BLEN_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CBC_CH7_BLEN_CH7(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_XDMAC_XDMAC_CBC_CH7_BLEN_CH7     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_XDMAC_XDMAC_CBC_CH7_BLEN_CH7(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief XDMAC Channel 7 Configuration Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CC_CH7
 */
#define VTSS_XDMAC_XDMAC_CC_CH7              VTSS_IOREG(VTSS_TO_XDMAC,0x92)

/**
 * \brief
 * PERID_CH7: Peripheral Hardware Request Line IdentifierThis field
 * contains the peripheral hardware request line identifier.Note: When a
 * memory-to-memory transfer is performed, configure PERID to an unused
 * peripheral ID.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH7 . PERID_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH7_PERID_CH7(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_XDMAC_XDMAC_CC_CH7_PERID_CH7     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH7_PERID_CH7(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * WRIP_CH7: Write in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active write transaction on the bus.
 * 1 (IN_PROGRESS): A write transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH7 . WRIP_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH7_WRIP_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH7_WRIP_CH7   VTSS_BIT(23)
#define  VTSS_X_XDMAC_XDMAC_CC_CH7_WRIP_CH7(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * RDIP_CH7: Read in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active read transaction on the bus.
 * 1 (IN_PROGRESS): A read transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH7 . RDIP_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH7_RDIP_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH7_RDIP_CH7   VTSS_BIT(22)
#define  VTSS_X_XDMAC_XDMAC_CC_CH7_RDIP_CH7(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * INITD_CH7: Channel Initialization Done (this bit is read-only)Note: When
 * set to 0, XDMAC_CUBC_CH7.UBLEN_CH7 and XDMAC_CNDA_CH7.NDA_CH7 field
 * values are unreliable each time a descriptor is being updated.
 *
 * \details
 * 0 (IN_PROGRESS): Channel initialization is in progress.
 * 1 (TERMINATED): Channel initialization is completed.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH7 . INITD_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH7_INITD_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH7_INITD_CH7  VTSS_BIT(21)
#define  VTSS_X_XDMAC_XDMAC_CC_CH7_INITD_CH7(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * DAM_CH7: Destination Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH7 . DAM_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH7_DAM_CH7(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH7_DAM_CH7     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH7_DAM_CH7(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * SAM_CH7: Source Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH7 . SAM_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH7_SAM_CH7(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH7_SAM_CH7     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH7_SAM_CH7(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * DWIDTH_CH7: Data Width
 *
 * \details
 * 0 (BYTE): The data size is set to 8 bits.
 * 1 (HALFWORD): The data size is set to 16 bits.
 * 2 (WORD): The data size is set to 32 bits.
 * 3 (DWORD): The data size is set to 64 bits.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH7 . DWIDTH_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH7_DWIDTH_CH7(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH7_DWIDTH_CH7     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH7_DWIDTH_CH7(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * CSIZE_CH7: Chunk Size
 *
 * \details
 * 0 (CHK_1): 1 data transferred
 * 2 (CHK_2): 2 data transferred
 * 4 (CHK_4): 4 data transferred
 * 8 (CHK_8): 8 data transferred
 * 16 (CHK_16): 16 data transferred
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH7 . CSIZE_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH7_CSIZE_CH7(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_XDMAC_XDMAC_CC_CH7_CSIZE_CH7     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_XDMAC_XDMAC_CC_CH7_CSIZE_CH7(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * MEMSET_CH7: Fill Block of Memory
 *
 * \details
 * 0 (NORMAL_MODE): Memset is not activated.
 * 1 (HW_MODE): Sets the block of memory pointed by DA field to the
 * specified value. This operation is performed on 8-, 16- or 32-bit basis.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH7 . MEMSET_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH7_MEMSET_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH7_MEMSET_CH7  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH7_MEMSET_CH7(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * SWREQ_CH7: Software Request Trigger
 *
 * \details
 * 0 (HWR_CONNECTED): Hardware request line is connected to the peripheral
 * request line.
 * 1 (SWR_CONNECTED): Software request is connected to the peripheral
 * request line.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH7 . SWREQ_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH7_SWREQ_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH7_SWREQ_CH7  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CC_CH7_SWREQ_CH7(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * PROT_CH7: Channel Protection
 *
 * \details
 * 0 (SEC): Channel is secured.
 * 1 (UNSEC): Channel is unsecured.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH7 . PROT_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH7_PROT_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH7_PROT_CH7   VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CC_CH7_PROT_CH7(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DSYNC_CH7: Channel Synchronization (Peripheral Transfer Direction)
 *
 * \details
 * 0 (PER2MEM): Peripheral-to-memory transfer.
 * 1 (MEM2PER): Memory-to-peripheral transfer.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH7 . DSYNC_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH7_DSYNC_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH7_DSYNC_CH7  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CC_CH7_DSYNC_CH7(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * MBSIZE_CH7: Memory Burst Size
 *
 * \details
 * 0 (SINGLE): The memory burst size is set to one.
 * 1 (FOUR): The memory burst size is set to four.
 * 2 (EIGHT): The memory burst size is set to eight.
 * 3 (SIXTEEN): The memory burst size is set to sixteen.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH7 . MBSIZE_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH7_MBSIZE_CH7(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH7_MBSIZE_CH7     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH7_MBSIZE_CH7(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * TYPE_CH7: Transfer Type
 *
 * \details
 * 0 (MEM_TRAN): Self-triggered mode (memory-to-memory transfer).
 * 1 (PER_TRAN): Synchronized mode (peripheral-to-memory or
 * memory-to-peripheral transfer).
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH7 . TYPE_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH7_TYPE_CH7(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH7_TYPE_CH7   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CC_CH7_TYPE_CH7(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 7 Data Stride Memory Set Pattern Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDS_MSP_CH7
 */
#define VTSS_XDMAC_XDMAC_CDS_MSP_CH7         VTSS_IOREG(VTSS_TO_XDMAC,0x93)

/**
 * \brief
 * DDS_MSP_CH7: Destination Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the destination data
 * stride.Number of bytes for the data stride of channel x (two's
 * complement). If the field is set to zero the data is contiguous.The
 * DDS_MSP_CHx field is only relevant when XDMAC_CCx.DAM=UBS_DS_AM.When
 * XDMAC_CCx.MEMSET = 1, this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH7 . DDS_MSP_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH7_DDS_MSP_CH7(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH7_DDS_MSP_CH7     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH7_DDS_MSP_CH7(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * SDS_MSP_CH7: Source Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the source data stride.Number
 * of bytes for the data stride of channel x (two's complement). If the
 * field is set to zero the data is contiguous.The SDS_MSP_CHx field is
 * only relevant when XDMAC_CCx.SAM=UBS_DS_AM.When XDMAC_CCx.MEMSET = 1,
 * this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH7 . SDS_MSP_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH7_SDS_MSP_CH7(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH7_SDS_MSP_CH7     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH7_SDS_MSP_CH7(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief XDMAC Channel 7 Source Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSUS_CH7
 */
#define VTSS_XDMAC_XDMAC_CSUS_CH7            VTSS_IOREG(VTSS_TO_XDMAC,0x94)

/**
 * \brief
 * SUBS_CH7: Source Microblock StrideNumber of bytes for the microblock
 * stride for channel x (two's comlpement). If the field is set to zero the
 * data is contiguous.SUBS_CHx field is only relevant when
 * XDMAC_CCx.SAM=UBS_AM or XDMAC_CCx.SAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSUS_CH7 . SUBS_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CSUS_CH7_SUBS_CH7(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CSUS_CH7_SUBS_CH7     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CSUS_CH7_SUBS_CH7(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 7 Destination Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDUS_CH7
 */
#define VTSS_XDMAC_XDMAC_CDUS_CH7            VTSS_IOREG(VTSS_TO_XDMAC,0x95)

/**
 * \brief
 * DUBS_CH7: Destination Microblock StrideNumber of bytes for the
 * microblock stride for channel x (two's comlpement). If the field is set
 * to zero the data is contiguous.DUBS_CHx field is only relevant when
 * XDMAC_CCx.DAM=UBS_AM or XDMAC_CCx.DAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDUS_CH7 . DUBS_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CDUS_CH7_DUBS_CH7(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CDUS_CH7_DUBS_CH7     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CDUS_CH7_DUBS_CH7(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 7 Transfer Count Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CTCS_CH7
 */
#define VTSS_XDMAC_XDMAC_CTCS_CH7            VTSS_IOREG(VTSS_TO_XDMAC,0x96)

/**
 * \brief
 * TC_CH7: Transfer CountNumber of bytes written by the XDMA since the last
 * read of the Transfer Count Status register. The field does not indicate
 * the number of bytes written to memory.To get the number of bytes already
 * written in memory at any time during peripheral-to-memory transfer, use
 * the following software procedure:1. Read the XDMAC_CTCSx.TC field to
 * sample the number of bytes received by the XDMA.2. Perform a software
 * flush of the channel by writing one to the XDMAC_GSWF register. This
 * will push bytes from the internal DMA FIFO to the external memory and
 * return an interrupt when the bytes can be read by the CPU.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CTCS_CH7 . TC_CH7
 */
#define  VTSS_F_XDMAC_XDMAC_CTCS_CH7_TC_CH7(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CTCS_CH7_TC_CH7     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CTCS_CH7_TC_CH7(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 8 Interrupt Enable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIE_CH8
 */
#define VTSS_XDMAC_XDMAC_CIE_CH8             VTSS_IOREG(VTSS_TO_XDMAC,0x98)

/**
 * \brief
 * TCIE_CH8: Transfer Count Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH8 . TCIE_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH8_TCIE_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH8_TCIE_CH8  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH8_TCIE_CH8(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIE_CH8: Request Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH8 . ROIE_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH8_ROIE_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH8_ROIE_CH8  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH8_ROIE_CH8(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBIE_CH8: Write Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables write bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH8 . WBIE_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH8_WBIE_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH8_WBIE_CH8  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH8_WBIE_CH8(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBIE_CH8: Read Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables read bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH8 . RBIE_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH8_RBIE_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH8_RBIE_CH8  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH8_RBIE_CH8(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIE_CH8: End of Flush Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH8 . FIE_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH8_FIE_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH8_FIE_CH8   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH8_FIE_CH8(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIE_CH8: End of Disable Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH8 . DIE_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH8_DIE_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH8_DIE_CH8   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH8_DIE_CH8(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIE_CH8: End of Linked List Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH8 . LIE_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH8_LIE_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH8_LIE_CH8   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH8_LIE_CH8(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIE_CH8: End of Block Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH8 . BIE_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH8_BIE_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH8_BIE_CH8   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH8_BIE_CH8(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 8 Interrupt Disable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CID_CH8
 */
#define VTSS_XDMAC_XDMAC_CID_CH8             VTSS_IOREG(VTSS_TO_XDMAC,0x99)

/**
 * \brief
 * TCID_CH8: Transfer Count Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH8 . TCID_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH8_TCID_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH8_TCID_CH8  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CID_CH8_TCID_CH8(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROID_CH8: Request Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH8 . ROID_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH8_ROID_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH8_ROID_CH8  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CID_CH8_ROID_CH8(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEID_CH8: Write Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH8 . WBEID_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH8_WBEID_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH8_WBEID_CH8  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CID_CH8_WBEID_CH8(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEID_CH8: Read Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH8 . RBEID_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH8_RBEID_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH8_RBEID_CH8  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CID_CH8_RBEID_CH8(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FID_CH8: End of Flush Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH8 . FID_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH8_FID_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH8_FID_CH8   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CID_CH8_FID_CH8(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DID_CH8: End of Disable Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH8 . DID_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH8_DID_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH8_DID_CH8   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CID_CH8_DID_CH8(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LID_CH8: End of Linked List Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH8 . LID_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH8_LID_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH8_LID_CH8   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CID_CH8_LID_CH8(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BID_CH8: End of Block Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH8 . BID_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH8_BID_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH8_BID_CH8   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CID_CH8_BID_CH8(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 8 Interrupt Mask Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIM_CH8
 */
#define VTSS_XDMAC_XDMAC_CIM_CH8             VTSS_IOREG(VTSS_TO_XDMAC,0x9a)

/**
 * \brief
 * TCIM_CH8: Transfer Count Overflow Error Interrupt Mask
 *
 * \details
 * 0: Transfer count overflow interrupt is masked.
 * 1: Transfer count overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH8 . TCIM_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH8_TCIM_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH8_TCIM_CH8  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH8_TCIM_CH8(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIM_CH8: Request Overflow Error Interrupt Mask
 *
 * \details
 * 0: Request overflow interrupt is masked.
 * 1: Request overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH8 . ROIM_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH8_ROIM_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH8_ROIM_CH8  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH8_ROIM_CH8(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIM_CH8: Write Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH8 . WBEIM_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH8_WBEIM_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH8_WBEIM_CH8  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH8_WBEIM_CH8(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIM_CH8: Read Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH8 . RBEIM_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH8_RBEIM_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH8_RBEIM_CH8  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH8_RBEIM_CH8(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIM_CH8: End of Flush Interrupt Mask
 *
 * \details
 * 0: End of flush interrupt is masked.
 * 1: End of flush interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH8 . FIM_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH8_FIM_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH8_FIM_CH8   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH8_FIM_CH8(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIM_CH8: End of Disable Interrupt Mask
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH8 . DIM_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH8_DIM_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH8_DIM_CH8   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH8_DIM_CH8(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIM_CH8: End of Linked List Interrupt Mask
 *
 * \details
 * 0: End of linked list interrupt is masked.
 * 1: End of linked list interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH8 . LIM_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH8_LIM_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH8_LIM_CH8   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH8_LIM_CH8(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIM_CH8: End of Block Interrupt Mask
 *
 * \details
 * 0: Block interrupt is masked.
 * 1: Block interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH8 . BIM_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH8_BIM_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH8_BIM_CH8   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH8_BIM_CH8(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 8 Interrupt Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIS_CH8
 */
#define VTSS_XDMAC_XDMAC_CIS_CH8             VTSS_IOREG(VTSS_TO_XDMAC,0x9b)

/**
 * \brief
 * TCIS_CH8: Transfer Count Overflow Interrupt Status
 *
 * \details
 * 0: Transfer count overflow has not occurred.
 * 1: At least one transfer count overflow has been detected since the last
 * read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH8 . TCIS_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH8_TCIS_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH8_TCIS_CH8  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH8_TCIS_CH8(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIS_CH8: Request Overflow Error Interrupt Status
 *
 * \details
 * 0: Overflow condition has not occurred.
 * 1: Overflow condition has occurred at least once. (This information is
 * only relevant for peripheral synchronized transfers.)
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH8 . ROIS_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH8_ROIS_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH8_ROIS_CH8  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH8_ROIS_CH8(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIS_CH8: Write Bus Error Interrupt Status
 *
 * \details
 * 0: Write bus error condition has not occurred.
 * 1: At least one bus error has been detected in a write access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH8 . WBEIS_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH8_WBEIS_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH8_WBEIS_CH8  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH8_WBEIS_CH8(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIS_CH8: Read Bus Error Interrupt Status
 *
 * \details
 * 0: Read bus error condition has not occurred.
 * 1: At least one bus error has been detected in a read access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH8 . RBEIS_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH8_RBEIS_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH8_RBEIS_CH8  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH8_RBEIS_CH8(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIS_CH8: End of Flush Interrupt Status
 *
 * \details
 * 0: End of flush condition has not occurred.
 * 1: End of flush condition has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH8 . FIS_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH8_FIS_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH8_FIS_CH8   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH8_FIS_CH8(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIS_CH8: End of Disable Interrupt Status
 *
 * \details
 * 0: End of disable condition has not occurred.
 * 1: End of disable condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH8 . DIS_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH8_DIS_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH8_DIS_CH8   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH8_DIS_CH8(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIS_CH8: End of Linked List Interrupt Status
 *
 * \details
 * 0: End of linked list condition has not occurred.
 * 1: End of linked list condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH8 . LIS_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH8_LIS_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH8_LIS_CH8   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH8_LIS_CH8(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIS_CH8: End of Block Interrupt Status
 *
 * \details
 * 0: End of block interrupt has not occurred.
 * 1: End of block interrupt has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH8 . BIS_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH8_BIS_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH8_BIS_CH8   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH8_BIS_CH8(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 8 Source Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSA_CH8
 */
#define VTSS_XDMAC_XDMAC_CSA_CH8             VTSS_IOREG(VTSS_TO_XDMAC,0x9c)

/**
 * \brief
 * SA_CH8: Source AddressProgram this register with the source address of
 * the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSA_CH8 . SA_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CSA_CH8_SA_CH8(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CSA_CH8_SA_CH8     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CSA_CH8_SA_CH8(x)  (x)


/**
 * \brief XDMAC Channel 8 Destination Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDA_CH8
 */
#define VTSS_XDMAC_XDMAC_CDA_CH8             VTSS_IOREG(VTSS_TO_XDMAC,0x9d)

/**
 * \brief
 * DA_CH8: Destination AddressProgram this register with the destination
 * address of the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDA_CH8 . DA_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CDA_CH8_DA_CH8(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CDA_CH8_DA_CH8     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CDA_CH8_DA_CH8(x)  (x)


/**
 * \brief XDMAC Channel 8 Next Descriptor Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDA_CH8
 */
#define VTSS_XDMAC_XDMAC_CNDA_CH8            VTSS_IOREG(VTSS_TO_XDMAC,0x9e)

/**
 * \brief
 * NDA_CH8: Next Descriptor AddressThe 30-bit width of the NDA field
 * represents the next descriptor address range 31:2. The descriptor is
 * word-aligned and the two least significant register bits 1:0 are
 * ignored.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDA_CH8 . NDA_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CNDA_CH8_NDA_CH8(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_XDMAC_XDMAC_CNDA_CH8_NDA_CH8     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_XDMAC_XDMAC_CNDA_CH8_NDA_CH8(x)  VTSS_EXTRACT_BITFIELD(x,2,30)


/**
 * \brief XDMAC Channel 8 Next Descriptor Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDC_CH8
 */
#define VTSS_XDMAC_XDMAC_CNDC_CH8            VTSS_IOREG(VTSS_TO_XDMAC,0x9f)

/**
 * \brief
 * QOS_CH8: Channel Quality Of Service LevelThis field indicates the
 * current quality of service level for the channel.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH8 . QOS_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH8_QOS_CH8(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH8_QOS_CH8     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH8_QOS_CH8(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * NDVIEW_CH8: Next Descriptor View
 *
 * \details
 * 0 (NDV0): Next Descriptor View 0
 * 1 (NDV0): Next Descriptor View 1
 * 2 (NDV0): Next Descriptor View 2
 * 3 (NDV0): Next Descriptor View 3
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH8 . NDVIEW_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH8_NDVIEW_CH8(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH8_NDVIEW_CH8     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH8_NDVIEW_CH8(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * NDDUP_CH8: Next Descriptor Destination Update
 *
 * \details
 * 0 (DST_PARAMS_UNCHANGED): Destination parameters remain unchanged.
 * 1 (DST_PARAMS_UPDATED): Destination parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH8 . NDDUP_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH8_NDDUP_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH8_NDDUP_CH8  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH8_NDDUP_CH8(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * NDSUP_CH8: Next Descriptor Source Update
 *
 * \details
 * 0 (SRC_PARAMS_UNCHANGED): Source parameters remain unchanged.
 * 1 (SRC_PARAMS_UPDATED): Source parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH8 . NDSUP_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH8_NDSUP_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH8_NDSUP_CH8  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH8_NDSUP_CH8(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * NDE_CH8: Next Descriptor Enable
 *
 * \details
 * 0 (DSCR_FETCH_DIS): Descriptor fetch is disabled.
 * 1 (DSCR_FETCH_EN): Descriptor fetch is enabled.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH8 . NDE_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH8_NDE_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH8_NDE_CH8  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH8_NDE_CH8(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 8 Microblock Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CUBC_CH8
 */
#define VTSS_XDMAC_XDMAC_CUBC_CH8            VTSS_IOREG(VTSS_TO_XDMAC,0xa0)

/**
 * \brief
 * UBLEN_CH8: Microblock LengthThis field indicates the number of data in
 * the microblock. The microblock contains UBLEN data.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CUBC_CH8 . UBLEN_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CUBC_CH8_UBLEN_CH8(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CUBC_CH8_UBLEN_CH8     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CUBC_CH8_UBLEN_CH8(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 8 Block Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CBC_CH8
 */
#define VTSS_XDMAC_XDMAC_CBC_CH8             VTSS_IOREG(VTSS_TO_XDMAC,0xa1)

/**
 * \brief
 * BLEN_CH8: Block LengthThe length of the block is (BLEN+1) microblocks.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CBC_CH8 . BLEN_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CBC_CH8_BLEN_CH8(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_XDMAC_XDMAC_CBC_CH8_BLEN_CH8     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_XDMAC_XDMAC_CBC_CH8_BLEN_CH8(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief XDMAC Channel 8 Configuration Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CC_CH8
 */
#define VTSS_XDMAC_XDMAC_CC_CH8              VTSS_IOREG(VTSS_TO_XDMAC,0xa2)

/**
 * \brief
 * PERID_CH8: Peripheral Hardware Request Line IdentifierThis field
 * contains the peripheral hardware request line identifier.Note: When a
 * memory-to-memory transfer is performed, configure PERID to an unused
 * peripheral ID.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH8 . PERID_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH8_PERID_CH8(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_XDMAC_XDMAC_CC_CH8_PERID_CH8     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH8_PERID_CH8(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * WRIP_CH8: Write in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active write transaction on the bus.
 * 1 (IN_PROGRESS): A write transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH8 . WRIP_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH8_WRIP_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH8_WRIP_CH8   VTSS_BIT(23)
#define  VTSS_X_XDMAC_XDMAC_CC_CH8_WRIP_CH8(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * RDIP_CH8: Read in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active read transaction on the bus.
 * 1 (IN_PROGRESS): A read transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH8 . RDIP_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH8_RDIP_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH8_RDIP_CH8   VTSS_BIT(22)
#define  VTSS_X_XDMAC_XDMAC_CC_CH8_RDIP_CH8(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * INITD_CH8: Channel Initialization Done (this bit is read-only)Note: When
 * set to 0, XDMAC_CUBC_CH8.UBLEN_CH8 and XDMAC_CNDA_CH8.NDA_CH8 field
 * values are unreliable each time a descriptor is being updated.
 *
 * \details
 * 0 (IN_PROGRESS): Channel initialization is in progress.
 * 1 (TERMINATED): Channel initialization is completed.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH8 . INITD_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH8_INITD_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH8_INITD_CH8  VTSS_BIT(21)
#define  VTSS_X_XDMAC_XDMAC_CC_CH8_INITD_CH8(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * DAM_CH8: Destination Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH8 . DAM_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH8_DAM_CH8(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH8_DAM_CH8     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH8_DAM_CH8(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * SAM_CH8: Source Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH8 . SAM_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH8_SAM_CH8(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH8_SAM_CH8     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH8_SAM_CH8(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * DWIDTH_CH8: Data Width
 *
 * \details
 * 0 (BYTE): The data size is set to 8 bits.
 * 1 (HALFWORD): The data size is set to 16 bits.
 * 2 (WORD): The data size is set to 32 bits.
 * 3 (DWORD): The data size is set to 64 bits.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH8 . DWIDTH_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH8_DWIDTH_CH8(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH8_DWIDTH_CH8     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH8_DWIDTH_CH8(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * CSIZE_CH8: Chunk Size
 *
 * \details
 * 0 (CHK_1): 1 data transferred
 * 2 (CHK_2): 2 data transferred
 * 4 (CHK_4): 4 data transferred
 * 8 (CHK_8): 8 data transferred
 * 16 (CHK_16): 16 data transferred
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH8 . CSIZE_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH8_CSIZE_CH8(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_XDMAC_XDMAC_CC_CH8_CSIZE_CH8     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_XDMAC_XDMAC_CC_CH8_CSIZE_CH8(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * MEMSET_CH8: Fill Block of Memory
 *
 * \details
 * 0 (NORMAL_MODE): Memset is not activated.
 * 1 (HW_MODE): Sets the block of memory pointed by DA field to the
 * specified value. This operation is performed on 8-, 16- or 32-bit basis.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH8 . MEMSET_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH8_MEMSET_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH8_MEMSET_CH8  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH8_MEMSET_CH8(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * SWREQ_CH8: Software Request Trigger
 *
 * \details
 * 0 (HWR_CONNECTED): Hardware request line is connected to the peripheral
 * request line.
 * 1 (SWR_CONNECTED): Software request is connected to the peripheral
 * request line.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH8 . SWREQ_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH8_SWREQ_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH8_SWREQ_CH8  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CC_CH8_SWREQ_CH8(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * PROT_CH8: Channel Protection
 *
 * \details
 * 0 (SEC): Channel is secured.
 * 1 (UNSEC): Channel is unsecured.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH8 . PROT_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH8_PROT_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH8_PROT_CH8   VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CC_CH8_PROT_CH8(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DSYNC_CH8: Channel Synchronization (Peripheral Transfer Direction)
 *
 * \details
 * 0 (PER2MEM): Peripheral-to-memory transfer.
 * 1 (MEM2PER): Memory-to-peripheral transfer.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH8 . DSYNC_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH8_DSYNC_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH8_DSYNC_CH8  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CC_CH8_DSYNC_CH8(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * MBSIZE_CH8: Memory Burst Size
 *
 * \details
 * 0 (SINGLE): The memory burst size is set to one.
 * 1 (FOUR): The memory burst size is set to four.
 * 2 (EIGHT): The memory burst size is set to eight.
 * 3 (SIXTEEN): The memory burst size is set to sixteen.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH8 . MBSIZE_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH8_MBSIZE_CH8(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH8_MBSIZE_CH8     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH8_MBSIZE_CH8(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * TYPE_CH8: Transfer Type
 *
 * \details
 * 0 (MEM_TRAN): Self-triggered mode (memory-to-memory transfer).
 * 1 (PER_TRAN): Synchronized mode (peripheral-to-memory or
 * memory-to-peripheral transfer).
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH8 . TYPE_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH8_TYPE_CH8(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH8_TYPE_CH8   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CC_CH8_TYPE_CH8(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 8 Data Stride Memory Set Pattern Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDS_MSP_CH8
 */
#define VTSS_XDMAC_XDMAC_CDS_MSP_CH8         VTSS_IOREG(VTSS_TO_XDMAC,0xa3)

/**
 * \brief
 * DDS_MSP_CH8: Destination Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the destination data
 * stride.Number of bytes for the data stride of channel x (two's
 * complement). If the field is set to zero the data is contiguous.The
 * DDS_MSP_CHx field is only relevant when XDMAC_CCx.DAM=UBS_DS_AM.When
 * XDMAC_CCx.MEMSET = 1, this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH8 . DDS_MSP_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH8_DDS_MSP_CH8(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH8_DDS_MSP_CH8     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH8_DDS_MSP_CH8(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * SDS_MSP_CH8: Source Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the source data stride.Number
 * of bytes for the data stride of channel x (two's complement). If the
 * field is set to zero the data is contiguous.The SDS_MSP_CHx field is
 * only relevant when XDMAC_CCx.SAM=UBS_DS_AM.When XDMAC_CCx.MEMSET = 1,
 * this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH8 . SDS_MSP_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH8_SDS_MSP_CH8(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH8_SDS_MSP_CH8     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH8_SDS_MSP_CH8(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief XDMAC Channel 8 Source Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSUS_CH8
 */
#define VTSS_XDMAC_XDMAC_CSUS_CH8            VTSS_IOREG(VTSS_TO_XDMAC,0xa4)

/**
 * \brief
 * SUBS_CH8: Source Microblock StrideNumber of bytes for the microblock
 * stride for channel x (two's comlpement). If the field is set to zero the
 * data is contiguous.SUBS_CHx field is only relevant when
 * XDMAC_CCx.SAM=UBS_AM or XDMAC_CCx.SAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSUS_CH8 . SUBS_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CSUS_CH8_SUBS_CH8(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CSUS_CH8_SUBS_CH8     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CSUS_CH8_SUBS_CH8(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 8 Destination Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDUS_CH8
 */
#define VTSS_XDMAC_XDMAC_CDUS_CH8            VTSS_IOREG(VTSS_TO_XDMAC,0xa5)

/**
 * \brief
 * DUBS_CH8: Destination Microblock StrideNumber of bytes for the
 * microblock stride for channel x (two's comlpement). If the field is set
 * to zero the data is contiguous.DUBS_CHx field is only relevant when
 * XDMAC_CCx.DAM=UBS_AM or XDMAC_CCx.DAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDUS_CH8 . DUBS_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CDUS_CH8_DUBS_CH8(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CDUS_CH8_DUBS_CH8     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CDUS_CH8_DUBS_CH8(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 8 Transfer Count Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CTCS_CH8
 */
#define VTSS_XDMAC_XDMAC_CTCS_CH8            VTSS_IOREG(VTSS_TO_XDMAC,0xa6)

/**
 * \brief
 * TC_CH8: Transfer CountNumber of bytes written by the XDMA since the last
 * read of the Transfer Count Status register. The field does not indicate
 * the number of bytes written to memory.To get the number of bytes already
 * written in memory at any time during peripheral-to-memory transfer, use
 * the following software procedure:1. Read the XDMAC_CTCSx.TC field to
 * sample the number of bytes received by the XDMA.2. Perform a software
 * flush of the channel by writing one to the XDMAC_GSWF register. This
 * will push bytes from the internal DMA FIFO to the external memory and
 * return an interrupt when the bytes can be read by the CPU.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CTCS_CH8 . TC_CH8
 */
#define  VTSS_F_XDMAC_XDMAC_CTCS_CH8_TC_CH8(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CTCS_CH8_TC_CH8     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CTCS_CH8_TC_CH8(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 9 Interrupt Enable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIE_CH9
 */
#define VTSS_XDMAC_XDMAC_CIE_CH9             VTSS_IOREG(VTSS_TO_XDMAC,0xa8)

/**
 * \brief
 * TCIE_CH9: Transfer Count Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH9 . TCIE_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH9_TCIE_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH9_TCIE_CH9  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH9_TCIE_CH9(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIE_CH9: Request Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH9 . ROIE_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH9_ROIE_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH9_ROIE_CH9  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH9_ROIE_CH9(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBIE_CH9: Write Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables write bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH9 . WBIE_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH9_WBIE_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH9_WBIE_CH9  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH9_WBIE_CH9(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBIE_CH9: Read Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables read bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH9 . RBIE_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH9_RBIE_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH9_RBIE_CH9  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH9_RBIE_CH9(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIE_CH9: End of Flush Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH9 . FIE_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH9_FIE_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH9_FIE_CH9   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH9_FIE_CH9(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIE_CH9: End of Disable Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH9 . DIE_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH9_DIE_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH9_DIE_CH9   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH9_DIE_CH9(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIE_CH9: End of Linked List Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH9 . LIE_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH9_LIE_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH9_LIE_CH9   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH9_LIE_CH9(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIE_CH9: End of Block Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH9 . BIE_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH9_BIE_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH9_BIE_CH9   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH9_BIE_CH9(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 9 Interrupt Disable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CID_CH9
 */
#define VTSS_XDMAC_XDMAC_CID_CH9             VTSS_IOREG(VTSS_TO_XDMAC,0xa9)

/**
 * \brief
 * TCID_CH9: Transfer Count Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH9 . TCID_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH9_TCID_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH9_TCID_CH9  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CID_CH9_TCID_CH9(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROID_CH9: Request Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH9 . ROID_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH9_ROID_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH9_ROID_CH9  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CID_CH9_ROID_CH9(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEID_CH9: Write Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH9 . WBEID_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH9_WBEID_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH9_WBEID_CH9  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CID_CH9_WBEID_CH9(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEID_CH9: Read Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH9 . RBEID_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH9_RBEID_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH9_RBEID_CH9  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CID_CH9_RBEID_CH9(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FID_CH9: End of Flush Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH9 . FID_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH9_FID_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH9_FID_CH9   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CID_CH9_FID_CH9(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DID_CH9: End of Disable Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH9 . DID_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH9_DID_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH9_DID_CH9   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CID_CH9_DID_CH9(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LID_CH9: End of Linked List Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH9 . LID_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH9_LID_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH9_LID_CH9   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CID_CH9_LID_CH9(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BID_CH9: End of Block Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH9 . BID_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH9_BID_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH9_BID_CH9   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CID_CH9_BID_CH9(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 9 Interrupt Mask Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIM_CH9
 */
#define VTSS_XDMAC_XDMAC_CIM_CH9             VTSS_IOREG(VTSS_TO_XDMAC,0xaa)

/**
 * \brief
 * TCIM_CH9: Transfer Count Overflow Error Interrupt Mask
 *
 * \details
 * 0: Transfer count overflow interrupt is masked.
 * 1: Transfer count overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH9 . TCIM_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH9_TCIM_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH9_TCIM_CH9  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH9_TCIM_CH9(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIM_CH9: Request Overflow Error Interrupt Mask
 *
 * \details
 * 0: Request overflow interrupt is masked.
 * 1: Request overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH9 . ROIM_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH9_ROIM_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH9_ROIM_CH9  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH9_ROIM_CH9(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIM_CH9: Write Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH9 . WBEIM_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH9_WBEIM_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH9_WBEIM_CH9  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH9_WBEIM_CH9(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIM_CH9: Read Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH9 . RBEIM_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH9_RBEIM_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH9_RBEIM_CH9  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH9_RBEIM_CH9(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIM_CH9: End of Flush Interrupt Mask
 *
 * \details
 * 0: End of flush interrupt is masked.
 * 1: End of flush interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH9 . FIM_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH9_FIM_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH9_FIM_CH9   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH9_FIM_CH9(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIM_CH9: End of Disable Interrupt Mask
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH9 . DIM_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH9_DIM_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH9_DIM_CH9   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH9_DIM_CH9(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIM_CH9: End of Linked List Interrupt Mask
 *
 * \details
 * 0: End of linked list interrupt is masked.
 * 1: End of linked list interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH9 . LIM_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH9_LIM_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH9_LIM_CH9   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH9_LIM_CH9(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIM_CH9: End of Block Interrupt Mask
 *
 * \details
 * 0: Block interrupt is masked.
 * 1: Block interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH9 . BIM_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH9_BIM_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH9_BIM_CH9   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH9_BIM_CH9(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 9 Interrupt Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIS_CH9
 */
#define VTSS_XDMAC_XDMAC_CIS_CH9             VTSS_IOREG(VTSS_TO_XDMAC,0xab)

/**
 * \brief
 * TCIS_CH9: Transfer Count Overflow Interrupt Status
 *
 * \details
 * 0: Transfer count overflow has not occurred.
 * 1: At least one transfer count overflow has been detected since the last
 * read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH9 . TCIS_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH9_TCIS_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH9_TCIS_CH9  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH9_TCIS_CH9(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIS_CH9: Request Overflow Error Interrupt Status
 *
 * \details
 * 0: Overflow condition has not occurred.
 * 1: Overflow condition has occurred at least once. (This information is
 * only relevant for peripheral synchronized transfers.)
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH9 . ROIS_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH9_ROIS_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH9_ROIS_CH9  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH9_ROIS_CH9(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIS_CH9: Write Bus Error Interrupt Status
 *
 * \details
 * 0: Write bus error condition has not occurred.
 * 1: At least one bus error has been detected in a write access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH9 . WBEIS_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH9_WBEIS_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH9_WBEIS_CH9  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH9_WBEIS_CH9(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIS_CH9: Read Bus Error Interrupt Status
 *
 * \details
 * 0: Read bus error condition has not occurred.
 * 1: At least one bus error has been detected in a read access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH9 . RBEIS_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH9_RBEIS_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH9_RBEIS_CH9  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH9_RBEIS_CH9(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIS_CH9: End of Flush Interrupt Status
 *
 * \details
 * 0: End of flush condition has not occurred.
 * 1: End of flush condition has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH9 . FIS_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH9_FIS_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH9_FIS_CH9   VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH9_FIS_CH9(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIS_CH9: End of Disable Interrupt Status
 *
 * \details
 * 0: End of disable condition has not occurred.
 * 1: End of disable condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH9 . DIS_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH9_DIS_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH9_DIS_CH9   VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH9_DIS_CH9(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIS_CH9: End of Linked List Interrupt Status
 *
 * \details
 * 0: End of linked list condition has not occurred.
 * 1: End of linked list condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH9 . LIS_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH9_LIS_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH9_LIS_CH9   VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH9_LIS_CH9(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIS_CH9: End of Block Interrupt Status
 *
 * \details
 * 0: End of block interrupt has not occurred.
 * 1: End of block interrupt has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH9 . BIS_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH9_BIS_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH9_BIS_CH9   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH9_BIS_CH9(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 9 Source Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSA_CH9
 */
#define VTSS_XDMAC_XDMAC_CSA_CH9             VTSS_IOREG(VTSS_TO_XDMAC,0xac)

/**
 * \brief
 * SA_CH9: Source AddressProgram this register with the source address of
 * the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSA_CH9 . SA_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CSA_CH9_SA_CH9(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CSA_CH9_SA_CH9     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CSA_CH9_SA_CH9(x)  (x)


/**
 * \brief XDMAC Channel 9 Destination Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDA_CH9
 */
#define VTSS_XDMAC_XDMAC_CDA_CH9             VTSS_IOREG(VTSS_TO_XDMAC,0xad)

/**
 * \brief
 * DA_CH9: Destination AddressProgram this register with the destination
 * address of the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDA_CH9 . DA_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CDA_CH9_DA_CH9(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CDA_CH9_DA_CH9     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CDA_CH9_DA_CH9(x)  (x)


/**
 * \brief XDMAC Channel 9 Next Descriptor Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDA_CH9
 */
#define VTSS_XDMAC_XDMAC_CNDA_CH9            VTSS_IOREG(VTSS_TO_XDMAC,0xae)

/**
 * \brief
 * NDA_CH9: Next Descriptor AddressThe 30-bit width of the NDA field
 * represents the next descriptor address range 31:2. The descriptor is
 * word-aligned and the two least significant register bits 1:0 are
 * ignored.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDA_CH9 . NDA_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CNDA_CH9_NDA_CH9(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_XDMAC_XDMAC_CNDA_CH9_NDA_CH9     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_XDMAC_XDMAC_CNDA_CH9_NDA_CH9(x)  VTSS_EXTRACT_BITFIELD(x,2,30)


/**
 * \brief XDMAC Channel 9 Next Descriptor Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDC_CH9
 */
#define VTSS_XDMAC_XDMAC_CNDC_CH9            VTSS_IOREG(VTSS_TO_XDMAC,0xaf)

/**
 * \brief
 * QOS_CH9: Channel Quality Of Service LevelThis field indicates the
 * current quality of service level for the channel.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH9 . QOS_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH9_QOS_CH9(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH9_QOS_CH9     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH9_QOS_CH9(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * NDVIEW_CH9: Next Descriptor View
 *
 * \details
 * 0 (NDV0): Next Descriptor View 0
 * 1 (NDV0): Next Descriptor View 1
 * 2 (NDV0): Next Descriptor View 2
 * 3 (NDV0): Next Descriptor View 3
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH9 . NDVIEW_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH9_NDVIEW_CH9(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH9_NDVIEW_CH9     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH9_NDVIEW_CH9(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * NDDUP_CH9: Next Descriptor Destination Update
 *
 * \details
 * 0 (DST_PARAMS_UNCHANGED): Destination parameters remain unchanged.
 * 1 (DST_PARAMS_UPDATED): Destination parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH9 . NDDUP_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH9_NDDUP_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH9_NDDUP_CH9  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH9_NDDUP_CH9(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * NDSUP_CH9: Next Descriptor Source Update
 *
 * \details
 * 0 (SRC_PARAMS_UNCHANGED): Source parameters remain unchanged.
 * 1 (SRC_PARAMS_UPDATED): Source parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH9 . NDSUP_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH9_NDSUP_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH9_NDSUP_CH9  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH9_NDSUP_CH9(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * NDE_CH9: Next Descriptor Enable
 *
 * \details
 * 0 (DSCR_FETCH_DIS): Descriptor fetch is disabled.
 * 1 (DSCR_FETCH_EN): Descriptor fetch is enabled.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH9 . NDE_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH9_NDE_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH9_NDE_CH9  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH9_NDE_CH9(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 9 Microblock Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CUBC_CH9
 */
#define VTSS_XDMAC_XDMAC_CUBC_CH9            VTSS_IOREG(VTSS_TO_XDMAC,0xb0)

/**
 * \brief
 * UBLEN_CH9: Microblock LengthThis field indicates the number of data in
 * the microblock. The microblock contains UBLEN data.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CUBC_CH9 . UBLEN_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CUBC_CH9_UBLEN_CH9(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CUBC_CH9_UBLEN_CH9     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CUBC_CH9_UBLEN_CH9(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 9 Block Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CBC_CH9
 */
#define VTSS_XDMAC_XDMAC_CBC_CH9             VTSS_IOREG(VTSS_TO_XDMAC,0xb1)

/**
 * \brief
 * BLEN_CH9: Block LengthThe length of the block is (BLEN+1) microblocks.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CBC_CH9 . BLEN_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CBC_CH9_BLEN_CH9(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_XDMAC_XDMAC_CBC_CH9_BLEN_CH9     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_XDMAC_XDMAC_CBC_CH9_BLEN_CH9(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief XDMAC Channel 9 Configuration Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CC_CH9
 */
#define VTSS_XDMAC_XDMAC_CC_CH9              VTSS_IOREG(VTSS_TO_XDMAC,0xb2)

/**
 * \brief
 * PERID_CH9: Peripheral Hardware Request Line IdentifierThis field
 * contains the peripheral hardware request line identifier.Note: When a
 * memory-to-memory transfer is performed, configure PERID to an unused
 * peripheral ID.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH9 . PERID_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH9_PERID_CH9(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_XDMAC_XDMAC_CC_CH9_PERID_CH9     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH9_PERID_CH9(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * WRIP_CH9: Write in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active write transaction on the bus.
 * 1 (IN_PROGRESS): A write transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH9 . WRIP_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH9_WRIP_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH9_WRIP_CH9   VTSS_BIT(23)
#define  VTSS_X_XDMAC_XDMAC_CC_CH9_WRIP_CH9(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * RDIP_CH9: Read in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active read transaction on the bus.
 * 1 (IN_PROGRESS): A read transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH9 . RDIP_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH9_RDIP_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH9_RDIP_CH9   VTSS_BIT(22)
#define  VTSS_X_XDMAC_XDMAC_CC_CH9_RDIP_CH9(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * INITD_CH9: Channel Initialization Done (this bit is read-only)Note: When
 * set to 0, XDMAC_CUBC_CH9.UBLEN_CH9 and XDMAC_CNDA_CH9.NDA_CH9 field
 * values are unreliable each time a descriptor is being updated.
 *
 * \details
 * 0 (IN_PROGRESS): Channel initialization is in progress.
 * 1 (TERMINATED): Channel initialization is completed.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH9 . INITD_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH9_INITD_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH9_INITD_CH9  VTSS_BIT(21)
#define  VTSS_X_XDMAC_XDMAC_CC_CH9_INITD_CH9(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * DAM_CH9: Destination Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH9 . DAM_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH9_DAM_CH9(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH9_DAM_CH9     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH9_DAM_CH9(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * SAM_CH9: Source Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH9 . SAM_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH9_SAM_CH9(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH9_SAM_CH9     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH9_SAM_CH9(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * DWIDTH_CH9: Data Width
 *
 * \details
 * 0 (BYTE): The data size is set to 8 bits.
 * 1 (HALFWORD): The data size is set to 16 bits.
 * 2 (WORD): The data size is set to 32 bits.
 * 3 (DWORD): The data size is set to 64 bits.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH9 . DWIDTH_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH9_DWIDTH_CH9(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH9_DWIDTH_CH9     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH9_DWIDTH_CH9(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * CSIZE_CH9: Chunk Size
 *
 * \details
 * 0 (CHK_1): 1 data transferred
 * 2 (CHK_2): 2 data transferred
 * 4 (CHK_4): 4 data transferred
 * 8 (CHK_8): 8 data transferred
 * 16 (CHK_16): 16 data transferred
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH9 . CSIZE_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH9_CSIZE_CH9(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_XDMAC_XDMAC_CC_CH9_CSIZE_CH9     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_XDMAC_XDMAC_CC_CH9_CSIZE_CH9(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * MEMSET_CH9: Fill Block of Memory
 *
 * \details
 * 0 (NORMAL_MODE): Memset is not activated.
 * 1 (HW_MODE): Sets the block of memory pointed by DA field to the
 * specified value. This operation is performed on 8-, 16- or 32-bit basis.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH9 . MEMSET_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH9_MEMSET_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH9_MEMSET_CH9  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH9_MEMSET_CH9(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * SWREQ_CH9: Software Request Trigger
 *
 * \details
 * 0 (HWR_CONNECTED): Hardware request line is connected to the peripheral
 * request line.
 * 1 (SWR_CONNECTED): Software request is connected to the peripheral
 * request line.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH9 . SWREQ_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH9_SWREQ_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH9_SWREQ_CH9  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CC_CH9_SWREQ_CH9(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * PROT_CH9: Channel Protection
 *
 * \details
 * 0 (SEC): Channel is secured.
 * 1 (UNSEC): Channel is unsecured.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH9 . PROT_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH9_PROT_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH9_PROT_CH9   VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CC_CH9_PROT_CH9(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DSYNC_CH9: Channel Synchronization (Peripheral Transfer Direction)
 *
 * \details
 * 0 (PER2MEM): Peripheral-to-memory transfer.
 * 1 (MEM2PER): Memory-to-peripheral transfer.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH9 . DSYNC_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH9_DSYNC_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH9_DSYNC_CH9  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CC_CH9_DSYNC_CH9(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * MBSIZE_CH9: Memory Burst Size
 *
 * \details
 * 0 (SINGLE): The memory burst size is set to one.
 * 1 (FOUR): The memory burst size is set to four.
 * 2 (EIGHT): The memory burst size is set to eight.
 * 3 (SIXTEEN): The memory burst size is set to sixteen.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH9 . MBSIZE_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH9_MBSIZE_CH9(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH9_MBSIZE_CH9     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH9_MBSIZE_CH9(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * TYPE_CH9: Transfer Type
 *
 * \details
 * 0 (MEM_TRAN): Self-triggered mode (memory-to-memory transfer).
 * 1 (PER_TRAN): Synchronized mode (peripheral-to-memory or
 * memory-to-peripheral transfer).
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH9 . TYPE_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH9_TYPE_CH9(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH9_TYPE_CH9   VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CC_CH9_TYPE_CH9(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 9 Data Stride Memory Set Pattern Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDS_MSP_CH9
 */
#define VTSS_XDMAC_XDMAC_CDS_MSP_CH9         VTSS_IOREG(VTSS_TO_XDMAC,0xb3)

/**
 * \brief
 * DDS_MSP_CH9: Destination Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the destination data
 * stride.Number of bytes for the data stride of channel x (two's
 * complement). If the field is set to zero the data is contiguous.The
 * DDS_MSP_CHx field is only relevant when XDMAC_CCx.DAM=UBS_DS_AM.When
 * XDMAC_CCx.MEMSET = 1, this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH9 . DDS_MSP_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH9_DDS_MSP_CH9(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH9_DDS_MSP_CH9     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH9_DDS_MSP_CH9(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * SDS_MSP_CH9: Source Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the source data stride.Number
 * of bytes for the data stride of channel x (two's complement). If the
 * field is set to zero the data is contiguous.The SDS_MSP_CHx field is
 * only relevant when XDMAC_CCx.SAM=UBS_DS_AM.When XDMAC_CCx.MEMSET = 1,
 * this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH9 . SDS_MSP_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH9_SDS_MSP_CH9(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH9_SDS_MSP_CH9     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH9_SDS_MSP_CH9(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief XDMAC Channel 9 Source Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSUS_CH9
 */
#define VTSS_XDMAC_XDMAC_CSUS_CH9            VTSS_IOREG(VTSS_TO_XDMAC,0xb4)

/**
 * \brief
 * SUBS_CH9: Source Microblock StrideNumber of bytes for the microblock
 * stride for channel x (two's comlpement). If the field is set to zero the
 * data is contiguous.SUBS_CHx field is only relevant when
 * XDMAC_CCx.SAM=UBS_AM or XDMAC_CCx.SAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSUS_CH9 . SUBS_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CSUS_CH9_SUBS_CH9(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CSUS_CH9_SUBS_CH9     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CSUS_CH9_SUBS_CH9(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 9 Destination Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDUS_CH9
 */
#define VTSS_XDMAC_XDMAC_CDUS_CH9            VTSS_IOREG(VTSS_TO_XDMAC,0xb5)

/**
 * \brief
 * DUBS_CH9: Destination Microblock StrideNumber of bytes for the
 * microblock stride for channel x (two's comlpement). If the field is set
 * to zero the data is contiguous.DUBS_CHx field is only relevant when
 * XDMAC_CCx.DAM=UBS_AM or XDMAC_CCx.DAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDUS_CH9 . DUBS_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CDUS_CH9_DUBS_CH9(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CDUS_CH9_DUBS_CH9     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CDUS_CH9_DUBS_CH9(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 9 Transfer Count Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CTCS_CH9
 */
#define VTSS_XDMAC_XDMAC_CTCS_CH9            VTSS_IOREG(VTSS_TO_XDMAC,0xb6)

/**
 * \brief
 * TC_CH9: Transfer CountNumber of bytes written by the XDMA since the last
 * read of the Transfer Count Status register. The field does not indicate
 * the number of bytes written to memory.To get the number of bytes already
 * written in memory at any time during peripheral-to-memory transfer, use
 * the following software procedure:1. Read the XDMAC_CTCSx.TC field to
 * sample the number of bytes received by the XDMA.2. Perform a software
 * flush of the channel by writing one to the XDMAC_GSWF register. This
 * will push bytes from the internal DMA FIFO to the external memory and
 * return an interrupt when the bytes can be read by the CPU.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CTCS_CH9 . TC_CH9
 */
#define  VTSS_F_XDMAC_XDMAC_CTCS_CH9_TC_CH9(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CTCS_CH9_TC_CH9     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CTCS_CH9_TC_CH9(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 10 Interrupt Enable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIE_CH10
 */
#define VTSS_XDMAC_XDMAC_CIE_CH10            VTSS_IOREG(VTSS_TO_XDMAC,0xb8)

/**
 * \brief
 * TCIE_CH10: Transfer Count Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH10 . TCIE_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH10_TCIE_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH10_TCIE_CH10  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH10_TCIE_CH10(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIE_CH10: Request Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH10 . ROIE_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH10_ROIE_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH10_ROIE_CH10  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH10_ROIE_CH10(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBIE_CH10: Write Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables write bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH10 . WBIE_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH10_WBIE_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH10_WBIE_CH10  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH10_WBIE_CH10(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBIE_CH10: Read Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables read bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH10 . RBIE_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH10_RBIE_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH10_RBIE_CH10  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH10_RBIE_CH10(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIE_CH10: End of Flush Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH10 . FIE_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH10_FIE_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH10_FIE_CH10  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH10_FIE_CH10(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIE_CH10: End of Disable Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH10 . DIE_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH10_DIE_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH10_DIE_CH10  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH10_DIE_CH10(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIE_CH10: End of Linked List Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH10 . LIE_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH10_LIE_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH10_LIE_CH10  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH10_LIE_CH10(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIE_CH10: End of Block Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH10 . BIE_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH10_BIE_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH10_BIE_CH10  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH10_BIE_CH10(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 10 Interrupt Disable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CID_CH10
 */
#define VTSS_XDMAC_XDMAC_CID_CH10            VTSS_IOREG(VTSS_TO_XDMAC,0xb9)

/**
 * \brief
 * TCID_CH10: Transfer Count Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH10 . TCID_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH10_TCID_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH10_TCID_CH10  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CID_CH10_TCID_CH10(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROID_CH10: Request Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH10 . ROID_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH10_ROID_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH10_ROID_CH10  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CID_CH10_ROID_CH10(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEID_CH10: Write Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH10 . WBEID_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH10_WBEID_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH10_WBEID_CH10  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CID_CH10_WBEID_CH10(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEID_CH10: Read Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH10 . RBEID_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH10_RBEID_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH10_RBEID_CH10  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CID_CH10_RBEID_CH10(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FID_CH10: End of Flush Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH10 . FID_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH10_FID_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH10_FID_CH10  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CID_CH10_FID_CH10(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DID_CH10: End of Disable Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH10 . DID_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH10_DID_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH10_DID_CH10  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CID_CH10_DID_CH10(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LID_CH10: End of Linked List Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH10 . LID_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH10_LID_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH10_LID_CH10  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CID_CH10_LID_CH10(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BID_CH10: End of Block Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH10 . BID_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH10_BID_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH10_BID_CH10  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CID_CH10_BID_CH10(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 10 Interrupt Mask Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIM_CH10
 */
#define VTSS_XDMAC_XDMAC_CIM_CH10            VTSS_IOREG(VTSS_TO_XDMAC,0xba)

/**
 * \brief
 * TCIM_CH10: Transfer Count Overflow Error Interrupt Mask
 *
 * \details
 * 0: Transfer count overflow interrupt is masked.
 * 1: Transfer count overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH10 . TCIM_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH10_TCIM_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH10_TCIM_CH10  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH10_TCIM_CH10(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIM_CH10: Request Overflow Error Interrupt Mask
 *
 * \details
 * 0: Request overflow interrupt is masked.
 * 1: Request overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH10 . ROIM_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH10_ROIM_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH10_ROIM_CH10  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH10_ROIM_CH10(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIM_CH10: Write Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH10 . WBEIM_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH10_WBEIM_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH10_WBEIM_CH10  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH10_WBEIM_CH10(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIM_CH10: Read Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH10 . RBEIM_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH10_RBEIM_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH10_RBEIM_CH10  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH10_RBEIM_CH10(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIM_CH10: End of Flush Interrupt Mask
 *
 * \details
 * 0: End of flush interrupt is masked.
 * 1: End of flush interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH10 . FIM_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH10_FIM_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH10_FIM_CH10  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH10_FIM_CH10(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIM_CH10: End of Disable Interrupt Mask
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH10 . DIM_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH10_DIM_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH10_DIM_CH10  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH10_DIM_CH10(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIM_CH10: End of Linked List Interrupt Mask
 *
 * \details
 * 0: End of linked list interrupt is masked.
 * 1: End of linked list interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH10 . LIM_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH10_LIM_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH10_LIM_CH10  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH10_LIM_CH10(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIM_CH10: End of Block Interrupt Mask
 *
 * \details
 * 0: Block interrupt is masked.
 * 1: Block interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH10 . BIM_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH10_BIM_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH10_BIM_CH10  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH10_BIM_CH10(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 10 Interrupt Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIS_CH10
 */
#define VTSS_XDMAC_XDMAC_CIS_CH10            VTSS_IOREG(VTSS_TO_XDMAC,0xbb)

/**
 * \brief
 * TCIS_CH10: Transfer Count Overflow Interrupt Status
 *
 * \details
 * 0: Transfer count overflow has not occurred.
 * 1: At least one transfer count overflow has been detected since the last
 * read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH10 . TCIS_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH10_TCIS_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH10_TCIS_CH10  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH10_TCIS_CH10(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIS_CH10: Request Overflow Error Interrupt Status
 *
 * \details
 * 0: Overflow condition has not occurred.
 * 1: Overflow condition has occurred at least once. (This information is
 * only relevant for peripheral synchronized transfers.)
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH10 . ROIS_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH10_ROIS_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH10_ROIS_CH10  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH10_ROIS_CH10(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIS_CH10: Write Bus Error Interrupt Status
 *
 * \details
 * 0: Write bus error condition has not occurred.
 * 1: At least one bus error has been detected in a write access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH10 . WBEIS_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH10_WBEIS_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH10_WBEIS_CH10  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH10_WBEIS_CH10(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIS_CH10: Read Bus Error Interrupt Status
 *
 * \details
 * 0: Read bus error condition has not occurred.
 * 1: At least one bus error has been detected in a read access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH10 . RBEIS_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH10_RBEIS_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH10_RBEIS_CH10  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH10_RBEIS_CH10(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIS_CH10: End of Flush Interrupt Status
 *
 * \details
 * 0: End of flush condition has not occurred.
 * 1: End of flush condition has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH10 . FIS_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH10_FIS_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH10_FIS_CH10  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH10_FIS_CH10(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIS_CH10: End of Disable Interrupt Status
 *
 * \details
 * 0: End of disable condition has not occurred.
 * 1: End of disable condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH10 . DIS_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH10_DIS_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH10_DIS_CH10  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH10_DIS_CH10(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIS_CH10: End of Linked List Interrupt Status
 *
 * \details
 * 0: End of linked list condition has not occurred.
 * 1: End of linked list condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH10 . LIS_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH10_LIS_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH10_LIS_CH10  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH10_LIS_CH10(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIS_CH10: End of Block Interrupt Status
 *
 * \details
 * 0: End of block interrupt has not occurred.
 * 1: End of block interrupt has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH10 . BIS_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH10_BIS_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH10_BIS_CH10  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH10_BIS_CH10(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 10 Source Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSA_CH10
 */
#define VTSS_XDMAC_XDMAC_CSA_CH10            VTSS_IOREG(VTSS_TO_XDMAC,0xbc)

/**
 * \brief
 * SA_CH10: Source AddressProgram this register with the source address of
 * the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSA_CH10 . SA_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CSA_CH10_SA_CH10(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CSA_CH10_SA_CH10     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CSA_CH10_SA_CH10(x)  (x)


/**
 * \brief XDMAC Channel 10 Destination Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDA_CH10
 */
#define VTSS_XDMAC_XDMAC_CDA_CH10            VTSS_IOREG(VTSS_TO_XDMAC,0xbd)

/**
 * \brief
 * DA_CH10: Destination AddressProgram this register with the destination
 * address of the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDA_CH10 . DA_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CDA_CH10_DA_CH10(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CDA_CH10_DA_CH10     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CDA_CH10_DA_CH10(x)  (x)


/**
 * \brief XDMAC Channel 10 Next Descriptor Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDA_CH10
 */
#define VTSS_XDMAC_XDMAC_CNDA_CH10           VTSS_IOREG(VTSS_TO_XDMAC,0xbe)

/**
 * \brief
 * NDA_CH10: Next Descriptor AddressThe 30-bit width of the NDA field
 * represents the next descriptor address range 31:2. The descriptor is
 * word-aligned and the two least significant register bits 1:0 are
 * ignored.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDA_CH10 . NDA_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CNDA_CH10_NDA_CH10(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_XDMAC_XDMAC_CNDA_CH10_NDA_CH10     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_XDMAC_XDMAC_CNDA_CH10_NDA_CH10(x)  VTSS_EXTRACT_BITFIELD(x,2,30)


/**
 * \brief XDMAC Channel 10 Next Descriptor Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDC_CH10
 */
#define VTSS_XDMAC_XDMAC_CNDC_CH10           VTSS_IOREG(VTSS_TO_XDMAC,0xbf)

/**
 * \brief
 * QOS_CH10: Channel Quality Of Service LevelThis field indicates the
 * current quality of service level for the channel.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH10 . QOS_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH10_QOS_CH10(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH10_QOS_CH10     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH10_QOS_CH10(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * NDVIEW_CH10: Next Descriptor View
 *
 * \details
 * 0 (NDV0): Next Descriptor View 0
 * 1 (NDV0): Next Descriptor View 1
 * 2 (NDV0): Next Descriptor View 2
 * 3 (NDV0): Next Descriptor View 3
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH10 . NDVIEW_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH10_NDVIEW_CH10(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH10_NDVIEW_CH10     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH10_NDVIEW_CH10(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * NDDUP_CH10: Next Descriptor Destination Update
 *
 * \details
 * 0 (DST_PARAMS_UNCHANGED): Destination parameters remain unchanged.
 * 1 (DST_PARAMS_UPDATED): Destination parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH10 . NDDUP_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH10_NDDUP_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH10_NDDUP_CH10  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH10_NDDUP_CH10(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * NDSUP_CH10: Next Descriptor Source Update
 *
 * \details
 * 0 (SRC_PARAMS_UNCHANGED): Source parameters remain unchanged.
 * 1 (SRC_PARAMS_UPDATED): Source parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH10 . NDSUP_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH10_NDSUP_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH10_NDSUP_CH10  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH10_NDSUP_CH10(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * NDE_CH10: Next Descriptor Enable
 *
 * \details
 * 0 (DSCR_FETCH_DIS): Descriptor fetch is disabled.
 * 1 (DSCR_FETCH_EN): Descriptor fetch is enabled.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH10 . NDE_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH10_NDE_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH10_NDE_CH10  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH10_NDE_CH10(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 10 Microblock Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CUBC_CH10
 */
#define VTSS_XDMAC_XDMAC_CUBC_CH10           VTSS_IOREG(VTSS_TO_XDMAC,0xc0)

/**
 * \brief
 * UBLEN_CH10: Microblock LengthThis field indicates the number of data in
 * the microblock. The microblock contains UBLEN data.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CUBC_CH10 . UBLEN_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CUBC_CH10_UBLEN_CH10(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CUBC_CH10_UBLEN_CH10     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CUBC_CH10_UBLEN_CH10(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 10 Block Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CBC_CH10
 */
#define VTSS_XDMAC_XDMAC_CBC_CH10            VTSS_IOREG(VTSS_TO_XDMAC,0xc1)

/**
 * \brief
 * BLEN_CH10: Block LengthThe length of the block is (BLEN+1) microblocks.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CBC_CH10 . BLEN_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CBC_CH10_BLEN_CH10(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_XDMAC_XDMAC_CBC_CH10_BLEN_CH10     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_XDMAC_XDMAC_CBC_CH10_BLEN_CH10(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief XDMAC Channel 10 Configuration Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CC_CH10
 */
#define VTSS_XDMAC_XDMAC_CC_CH10             VTSS_IOREG(VTSS_TO_XDMAC,0xc2)

/**
 * \brief
 * PERID_CH10: Peripheral Hardware Request Line IdentifierThis field
 * contains the peripheral hardware request line identifier.Note: When a
 * memory-to-memory transfer is performed, configure PERID to an unused
 * peripheral ID.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH10 . PERID_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH10_PERID_CH10(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_XDMAC_XDMAC_CC_CH10_PERID_CH10     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH10_PERID_CH10(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * WRIP_CH10: Write in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active write transaction on the bus.
 * 1 (IN_PROGRESS): A write transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH10 . WRIP_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH10_WRIP_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH10_WRIP_CH10  VTSS_BIT(23)
#define  VTSS_X_XDMAC_XDMAC_CC_CH10_WRIP_CH10(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * RDIP_CH10: Read in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active read transaction on the bus.
 * 1 (IN_PROGRESS): A read transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH10 . RDIP_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH10_RDIP_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH10_RDIP_CH10  VTSS_BIT(22)
#define  VTSS_X_XDMAC_XDMAC_CC_CH10_RDIP_CH10(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * INITD_CH10: Channel Initialization Done (this bit is read-only)Note:
 * When set to 0, XDMAC_CUBC_CH10.UBLEN_CH10 and XDMAC_CNDA_CH10.NDA_CH10
 * field values are unreliable each time a descriptor is being updated.
 *
 * \details
 * 0 (IN_PROGRESS): Channel initialization is in progress.
 * 1 (TERMINATED): Channel initialization is completed.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH10 . INITD_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH10_INITD_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH10_INITD_CH10  VTSS_BIT(21)
#define  VTSS_X_XDMAC_XDMAC_CC_CH10_INITD_CH10(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * DAM_CH10: Destination Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH10 . DAM_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH10_DAM_CH10(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH10_DAM_CH10     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH10_DAM_CH10(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * SAM_CH10: Source Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH10 . SAM_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH10_SAM_CH10(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH10_SAM_CH10     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH10_SAM_CH10(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * DWIDTH_CH10: Data Width
 *
 * \details
 * 0 (BYTE): The data size is set to 8 bits.
 * 1 (HALFWORD): The data size is set to 16 bits.
 * 2 (WORD): The data size is set to 32 bits.
 * 3 (DWORD): The data size is set to 64 bits.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH10 . DWIDTH_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH10_DWIDTH_CH10(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH10_DWIDTH_CH10     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH10_DWIDTH_CH10(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * CSIZE_CH10: Chunk Size
 *
 * \details
 * 0 (CHK_1): 1 data transferred
 * 2 (CHK_2): 2 data transferred
 * 4 (CHK_4): 4 data transferred
 * 8 (CHK_8): 8 data transferred
 * 16 (CHK_16): 16 data transferred
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH10 . CSIZE_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH10_CSIZE_CH10(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_XDMAC_XDMAC_CC_CH10_CSIZE_CH10     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_XDMAC_XDMAC_CC_CH10_CSIZE_CH10(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * MEMSET_CH10: Fill Block of Memory
 *
 * \details
 * 0 (NORMAL_MODE): Memset is not activated.
 * 1 (HW_MODE): Sets the block of memory pointed by DA field to the
 * specified value. This operation is performed on 8-, 16- or 32-bit basis.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH10 . MEMSET_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH10_MEMSET_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH10_MEMSET_CH10  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH10_MEMSET_CH10(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * SWREQ_CH10: Software Request Trigger
 *
 * \details
 * 0 (HWR_CONNECTED): Hardware request line is connected to the peripheral
 * request line.
 * 1 (SWR_CONNECTED): Software request is connected to the peripheral
 * request line.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH10 . SWREQ_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH10_SWREQ_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH10_SWREQ_CH10  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CC_CH10_SWREQ_CH10(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * PROT_CH10: Channel Protection
 *
 * \details
 * 0 (SEC): Channel is secured.
 * 1 (UNSEC): Channel is unsecured.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH10 . PROT_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH10_PROT_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH10_PROT_CH10  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CC_CH10_PROT_CH10(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DSYNC_CH10: Channel Synchronization (Peripheral Transfer Direction)
 *
 * \details
 * 0 (PER2MEM): Peripheral-to-memory transfer.
 * 1 (MEM2PER): Memory-to-peripheral transfer.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH10 . DSYNC_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH10_DSYNC_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH10_DSYNC_CH10  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CC_CH10_DSYNC_CH10(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * MBSIZE_CH10: Memory Burst Size
 *
 * \details
 * 0 (SINGLE): The memory burst size is set to one.
 * 1 (FOUR): The memory burst size is set to four.
 * 2 (EIGHT): The memory burst size is set to eight.
 * 3 (SIXTEEN): The memory burst size is set to sixteen.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH10 . MBSIZE_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH10_MBSIZE_CH10(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH10_MBSIZE_CH10     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH10_MBSIZE_CH10(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * TYPE_CH10: Transfer Type
 *
 * \details
 * 0 (MEM_TRAN): Self-triggered mode (memory-to-memory transfer).
 * 1 (PER_TRAN): Synchronized mode (peripheral-to-memory or
 * memory-to-peripheral transfer).
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH10 . TYPE_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH10_TYPE_CH10(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH10_TYPE_CH10  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CC_CH10_TYPE_CH10(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 10 Data Stride Memory Set Pattern Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDS_MSP_CH10
 */
#define VTSS_XDMAC_XDMAC_CDS_MSP_CH10        VTSS_IOREG(VTSS_TO_XDMAC,0xc3)

/**
 * \brief
 * DDS_MSP_CH10: Destination Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the destination data
 * stride.Number of bytes for the data stride of channel x (two's
 * complement). If the field is set to zero the data is contiguous.The
 * DDS_MSP_CHx field is only relevant when XDMAC_CCx.DAM=UBS_DS_AM.When
 * XDMAC_CCx.MEMSET = 1, this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH10 . DDS_MSP_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH10_DDS_MSP_CH10(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH10_DDS_MSP_CH10     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH10_DDS_MSP_CH10(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * SDS_MSP_CH10: Source Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the source data stride.Number
 * of bytes for the data stride of channel x (two's complement). If the
 * field is set to zero the data is contiguous.The SDS_MSP_CHx field is
 * only relevant when XDMAC_CCx.SAM=UBS_DS_AM.When XDMAC_CCx.MEMSET = 1,
 * this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH10 . SDS_MSP_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH10_SDS_MSP_CH10(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH10_SDS_MSP_CH10     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH10_SDS_MSP_CH10(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief XDMAC Channel 10 Source Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSUS_CH10
 */
#define VTSS_XDMAC_XDMAC_CSUS_CH10           VTSS_IOREG(VTSS_TO_XDMAC,0xc4)

/**
 * \brief
 * SUBS_CH10: Source Microblock StrideNumber of bytes for the microblock
 * stride for channel x (two's comlpement). If the field is set to zero the
 * data is contiguous.SUBS_CHx field is only relevant when
 * XDMAC_CCx.SAM=UBS_AM or XDMAC_CCx.SAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSUS_CH10 . SUBS_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CSUS_CH10_SUBS_CH10(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CSUS_CH10_SUBS_CH10     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CSUS_CH10_SUBS_CH10(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 10 Destination Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDUS_CH10
 */
#define VTSS_XDMAC_XDMAC_CDUS_CH10           VTSS_IOREG(VTSS_TO_XDMAC,0xc5)

/**
 * \brief
 * DUBS_CH10: Destination Microblock StrideNumber of bytes for the
 * microblock stride for channel x (two's comlpement). If the field is set
 * to zero the data is contiguous.DUBS_CHx field is only relevant when
 * XDMAC_CCx.DAM=UBS_AM or XDMAC_CCx.DAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDUS_CH10 . DUBS_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CDUS_CH10_DUBS_CH10(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CDUS_CH10_DUBS_CH10     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CDUS_CH10_DUBS_CH10(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 10 Transfer Count Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CTCS_CH10
 */
#define VTSS_XDMAC_XDMAC_CTCS_CH10           VTSS_IOREG(VTSS_TO_XDMAC,0xc6)

/**
 * \brief
 * TC_CH10: Transfer CountNumber of bytes written by the XDMA since the
 * last read of the Transfer Count Status register. The field does not
 * indicate the number of bytes written to memory.To get the number of
 * bytes already written in memory at any time during peripheral-to-memory
 * transfer, use the following software procedure:1. Read the
 * XDMAC_CTCSx.TC field to sample the number of bytes received by the
 * XDMA.2. Perform a software flush of the channel by writing one to the
 * XDMAC_GSWF register. This will push bytes from the internal DMA FIFO to
 * the external memory and return an interrupt when the bytes can be read
 * by the CPU.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CTCS_CH10 . TC_CH10
 */
#define  VTSS_F_XDMAC_XDMAC_CTCS_CH10_TC_CH10(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CTCS_CH10_TC_CH10     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CTCS_CH10_TC_CH10(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 11 Interrupt Enable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIE_CH11
 */
#define VTSS_XDMAC_XDMAC_CIE_CH11            VTSS_IOREG(VTSS_TO_XDMAC,0xc8)

/**
 * \brief
 * TCIE_CH11: Transfer Count Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH11 . TCIE_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH11_TCIE_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH11_TCIE_CH11  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH11_TCIE_CH11(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIE_CH11: Request Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH11 . ROIE_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH11_ROIE_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH11_ROIE_CH11  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH11_ROIE_CH11(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBIE_CH11: Write Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables write bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH11 . WBIE_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH11_WBIE_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH11_WBIE_CH11  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH11_WBIE_CH11(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBIE_CH11: Read Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables read bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH11 . RBIE_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH11_RBIE_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH11_RBIE_CH11  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH11_RBIE_CH11(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIE_CH11: End of Flush Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH11 . FIE_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH11_FIE_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH11_FIE_CH11  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH11_FIE_CH11(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIE_CH11: End of Disable Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH11 . DIE_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH11_DIE_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH11_DIE_CH11  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH11_DIE_CH11(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIE_CH11: End of Linked List Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH11 . LIE_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH11_LIE_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH11_LIE_CH11  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH11_LIE_CH11(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIE_CH11: End of Block Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH11 . BIE_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH11_BIE_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH11_BIE_CH11  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH11_BIE_CH11(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 11 Interrupt Disable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CID_CH11
 */
#define VTSS_XDMAC_XDMAC_CID_CH11            VTSS_IOREG(VTSS_TO_XDMAC,0xc9)

/**
 * \brief
 * TCID_CH11: Transfer Count Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH11 . TCID_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH11_TCID_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH11_TCID_CH11  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CID_CH11_TCID_CH11(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROID_CH11: Request Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH11 . ROID_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH11_ROID_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH11_ROID_CH11  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CID_CH11_ROID_CH11(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEID_CH11: Write Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH11 . WBEID_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH11_WBEID_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH11_WBEID_CH11  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CID_CH11_WBEID_CH11(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEID_CH11: Read Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH11 . RBEID_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH11_RBEID_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH11_RBEID_CH11  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CID_CH11_RBEID_CH11(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FID_CH11: End of Flush Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH11 . FID_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH11_FID_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH11_FID_CH11  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CID_CH11_FID_CH11(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DID_CH11: End of Disable Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH11 . DID_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH11_DID_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH11_DID_CH11  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CID_CH11_DID_CH11(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LID_CH11: End of Linked List Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH11 . LID_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH11_LID_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH11_LID_CH11  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CID_CH11_LID_CH11(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BID_CH11: End of Block Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH11 . BID_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH11_BID_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH11_BID_CH11  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CID_CH11_BID_CH11(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 11 Interrupt Mask Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIM_CH11
 */
#define VTSS_XDMAC_XDMAC_CIM_CH11            VTSS_IOREG(VTSS_TO_XDMAC,0xca)

/**
 * \brief
 * TCIM_CH11: Transfer Count Overflow Error Interrupt Mask
 *
 * \details
 * 0: Transfer count overflow interrupt is masked.
 * 1: Transfer count overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH11 . TCIM_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH11_TCIM_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH11_TCIM_CH11  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH11_TCIM_CH11(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIM_CH11: Request Overflow Error Interrupt Mask
 *
 * \details
 * 0: Request overflow interrupt is masked.
 * 1: Request overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH11 . ROIM_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH11_ROIM_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH11_ROIM_CH11  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH11_ROIM_CH11(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIM_CH11: Write Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH11 . WBEIM_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH11_WBEIM_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH11_WBEIM_CH11  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH11_WBEIM_CH11(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIM_CH11: Read Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH11 . RBEIM_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH11_RBEIM_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH11_RBEIM_CH11  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH11_RBEIM_CH11(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIM_CH11: End of Flush Interrupt Mask
 *
 * \details
 * 0: End of flush interrupt is masked.
 * 1: End of flush interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH11 . FIM_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH11_FIM_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH11_FIM_CH11  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH11_FIM_CH11(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIM_CH11: End of Disable Interrupt Mask
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH11 . DIM_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH11_DIM_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH11_DIM_CH11  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH11_DIM_CH11(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIM_CH11: End of Linked List Interrupt Mask
 *
 * \details
 * 0: End of linked list interrupt is masked.
 * 1: End of linked list interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH11 . LIM_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH11_LIM_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH11_LIM_CH11  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH11_LIM_CH11(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIM_CH11: End of Block Interrupt Mask
 *
 * \details
 * 0: Block interrupt is masked.
 * 1: Block interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH11 . BIM_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH11_BIM_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH11_BIM_CH11  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH11_BIM_CH11(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 11 Interrupt Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIS_CH11
 */
#define VTSS_XDMAC_XDMAC_CIS_CH11            VTSS_IOREG(VTSS_TO_XDMAC,0xcb)

/**
 * \brief
 * TCIS_CH11: Transfer Count Overflow Interrupt Status
 *
 * \details
 * 0: Transfer count overflow has not occurred.
 * 1: At least one transfer count overflow has been detected since the last
 * read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH11 . TCIS_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH11_TCIS_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH11_TCIS_CH11  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH11_TCIS_CH11(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIS_CH11: Request Overflow Error Interrupt Status
 *
 * \details
 * 0: Overflow condition has not occurred.
 * 1: Overflow condition has occurred at least once. (This information is
 * only relevant for peripheral synchronized transfers.)
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH11 . ROIS_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH11_ROIS_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH11_ROIS_CH11  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH11_ROIS_CH11(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIS_CH11: Write Bus Error Interrupt Status
 *
 * \details
 * 0: Write bus error condition has not occurred.
 * 1: At least one bus error has been detected in a write access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH11 . WBEIS_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH11_WBEIS_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH11_WBEIS_CH11  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH11_WBEIS_CH11(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIS_CH11: Read Bus Error Interrupt Status
 *
 * \details
 * 0: Read bus error condition has not occurred.
 * 1: At least one bus error has been detected in a read access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH11 . RBEIS_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH11_RBEIS_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH11_RBEIS_CH11  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH11_RBEIS_CH11(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIS_CH11: End of Flush Interrupt Status
 *
 * \details
 * 0: End of flush condition has not occurred.
 * 1: End of flush condition has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH11 . FIS_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH11_FIS_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH11_FIS_CH11  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH11_FIS_CH11(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIS_CH11: End of Disable Interrupt Status
 *
 * \details
 * 0: End of disable condition has not occurred.
 * 1: End of disable condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH11 . DIS_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH11_DIS_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH11_DIS_CH11  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH11_DIS_CH11(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIS_CH11: End of Linked List Interrupt Status
 *
 * \details
 * 0: End of linked list condition has not occurred.
 * 1: End of linked list condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH11 . LIS_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH11_LIS_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH11_LIS_CH11  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH11_LIS_CH11(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIS_CH11: End of Block Interrupt Status
 *
 * \details
 * 0: End of block interrupt has not occurred.
 * 1: End of block interrupt has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH11 . BIS_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH11_BIS_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH11_BIS_CH11  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH11_BIS_CH11(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 11 Source Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSA_CH11
 */
#define VTSS_XDMAC_XDMAC_CSA_CH11            VTSS_IOREG(VTSS_TO_XDMAC,0xcc)

/**
 * \brief
 * SA_CH11: Source AddressProgram this register with the source address of
 * the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSA_CH11 . SA_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CSA_CH11_SA_CH11(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CSA_CH11_SA_CH11     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CSA_CH11_SA_CH11(x)  (x)


/**
 * \brief XDMAC Channel 11 Destination Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDA_CH11
 */
#define VTSS_XDMAC_XDMAC_CDA_CH11            VTSS_IOREG(VTSS_TO_XDMAC,0xcd)

/**
 * \brief
 * DA_CH11: Destination AddressProgram this register with the destination
 * address of the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDA_CH11 . DA_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CDA_CH11_DA_CH11(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CDA_CH11_DA_CH11     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CDA_CH11_DA_CH11(x)  (x)


/**
 * \brief XDMAC Channel 11 Next Descriptor Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDA_CH11
 */
#define VTSS_XDMAC_XDMAC_CNDA_CH11           VTSS_IOREG(VTSS_TO_XDMAC,0xce)

/**
 * \brief
 * NDA_CH11: Next Descriptor AddressThe 30-bit width of the NDA field
 * represents the next descriptor address range 31:2. The descriptor is
 * word-aligned and the two least significant register bits 1:0 are
 * ignored.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDA_CH11 . NDA_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CNDA_CH11_NDA_CH11(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_XDMAC_XDMAC_CNDA_CH11_NDA_CH11     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_XDMAC_XDMAC_CNDA_CH11_NDA_CH11(x)  VTSS_EXTRACT_BITFIELD(x,2,30)


/**
 * \brief XDMAC Channel 11 Next Descriptor Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDC_CH11
 */
#define VTSS_XDMAC_XDMAC_CNDC_CH11           VTSS_IOREG(VTSS_TO_XDMAC,0xcf)

/**
 * \brief
 * QOS_CH11: Channel Quality Of Service LevelThis field indicates the
 * current quality of service level for the channel.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH11 . QOS_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH11_QOS_CH11(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH11_QOS_CH11     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH11_QOS_CH11(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * NDVIEW_CH11: Next Descriptor View
 *
 * \details
 * 0 (NDV0): Next Descriptor View 0
 * 1 (NDV0): Next Descriptor View 1
 * 2 (NDV0): Next Descriptor View 2
 * 3 (NDV0): Next Descriptor View 3
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH11 . NDVIEW_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH11_NDVIEW_CH11(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH11_NDVIEW_CH11     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH11_NDVIEW_CH11(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * NDDUP_CH11: Next Descriptor Destination Update
 *
 * \details
 * 0 (DST_PARAMS_UNCHANGED): Destination parameters remain unchanged.
 * 1 (DST_PARAMS_UPDATED): Destination parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH11 . NDDUP_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH11_NDDUP_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH11_NDDUP_CH11  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH11_NDDUP_CH11(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * NDSUP_CH11: Next Descriptor Source Update
 *
 * \details
 * 0 (SRC_PARAMS_UNCHANGED): Source parameters remain unchanged.
 * 1 (SRC_PARAMS_UPDATED): Source parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH11 . NDSUP_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH11_NDSUP_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH11_NDSUP_CH11  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH11_NDSUP_CH11(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * NDE_CH11: Next Descriptor Enable
 *
 * \details
 * 0 (DSCR_FETCH_DIS): Descriptor fetch is disabled.
 * 1 (DSCR_FETCH_EN): Descriptor fetch is enabled.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH11 . NDE_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH11_NDE_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH11_NDE_CH11  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH11_NDE_CH11(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 11 Microblock Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CUBC_CH11
 */
#define VTSS_XDMAC_XDMAC_CUBC_CH11           VTSS_IOREG(VTSS_TO_XDMAC,0xd0)

/**
 * \brief
 * UBLEN_CH11: Microblock LengthThis field indicates the number of data in
 * the microblock. The microblock contains UBLEN data.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CUBC_CH11 . UBLEN_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CUBC_CH11_UBLEN_CH11(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CUBC_CH11_UBLEN_CH11     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CUBC_CH11_UBLEN_CH11(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 11 Block Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CBC_CH11
 */
#define VTSS_XDMAC_XDMAC_CBC_CH11            VTSS_IOREG(VTSS_TO_XDMAC,0xd1)

/**
 * \brief
 * BLEN_CH11: Block LengthThe length of the block is (BLEN+1) microblocks.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CBC_CH11 . BLEN_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CBC_CH11_BLEN_CH11(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_XDMAC_XDMAC_CBC_CH11_BLEN_CH11     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_XDMAC_XDMAC_CBC_CH11_BLEN_CH11(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief XDMAC Channel 11 Configuration Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CC_CH11
 */
#define VTSS_XDMAC_XDMAC_CC_CH11             VTSS_IOREG(VTSS_TO_XDMAC,0xd2)

/**
 * \brief
 * PERID_CH11: Peripheral Hardware Request Line IdentifierThis field
 * contains the peripheral hardware request line identifier.Note: When a
 * memory-to-memory transfer is performed, configure PERID to an unused
 * peripheral ID.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH11 . PERID_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH11_PERID_CH11(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_XDMAC_XDMAC_CC_CH11_PERID_CH11     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH11_PERID_CH11(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * WRIP_CH11: Write in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active write transaction on the bus.
 * 1 (IN_PROGRESS): A write transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH11 . WRIP_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH11_WRIP_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH11_WRIP_CH11  VTSS_BIT(23)
#define  VTSS_X_XDMAC_XDMAC_CC_CH11_WRIP_CH11(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * RDIP_CH11: Read in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active read transaction on the bus.
 * 1 (IN_PROGRESS): A read transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH11 . RDIP_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH11_RDIP_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH11_RDIP_CH11  VTSS_BIT(22)
#define  VTSS_X_XDMAC_XDMAC_CC_CH11_RDIP_CH11(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * INITD_CH11: Channel Initialization Done (this bit is read-only)Note:
 * When set to 0, XDMAC_CUBC_CH11.UBLEN_CH11 and XDMAC_CNDA_CH11.NDA_CH11
 * field values are unreliable each time a descriptor is being updated.
 *
 * \details
 * 0 (IN_PROGRESS): Channel initialization is in progress.
 * 1 (TERMINATED): Channel initialization is completed.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH11 . INITD_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH11_INITD_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH11_INITD_CH11  VTSS_BIT(21)
#define  VTSS_X_XDMAC_XDMAC_CC_CH11_INITD_CH11(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * DAM_CH11: Destination Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH11 . DAM_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH11_DAM_CH11(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH11_DAM_CH11     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH11_DAM_CH11(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * SAM_CH11: Source Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH11 . SAM_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH11_SAM_CH11(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH11_SAM_CH11     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH11_SAM_CH11(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * DWIDTH_CH11: Data Width
 *
 * \details
 * 0 (BYTE): The data size is set to 8 bits.
 * 1 (HALFWORD): The data size is set to 16 bits.
 * 2 (WORD): The data size is set to 32 bits.
 * 3 (DWORD): The data size is set to 64 bits.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH11 . DWIDTH_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH11_DWIDTH_CH11(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH11_DWIDTH_CH11     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH11_DWIDTH_CH11(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * CSIZE_CH11: Chunk Size
 *
 * \details
 * 0 (CHK_1): 1 data transferred
 * 2 (CHK_2): 2 data transferred
 * 4 (CHK_4): 4 data transferred
 * 8 (CHK_8): 8 data transferred
 * 16 (CHK_16): 16 data transferred
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH11 . CSIZE_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH11_CSIZE_CH11(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_XDMAC_XDMAC_CC_CH11_CSIZE_CH11     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_XDMAC_XDMAC_CC_CH11_CSIZE_CH11(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * MEMSET_CH11: Fill Block of Memory
 *
 * \details
 * 0 (NORMAL_MODE): Memset is not activated.
 * 1 (HW_MODE): Sets the block of memory pointed by DA field to the
 * specified value. This operation is performed on 8-, 16- or 32-bit basis.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH11 . MEMSET_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH11_MEMSET_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH11_MEMSET_CH11  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH11_MEMSET_CH11(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * SWREQ_CH11: Software Request Trigger
 *
 * \details
 * 0 (HWR_CONNECTED): Hardware request line is connected to the peripheral
 * request line.
 * 1 (SWR_CONNECTED): Software request is connected to the peripheral
 * request line.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH11 . SWREQ_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH11_SWREQ_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH11_SWREQ_CH11  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CC_CH11_SWREQ_CH11(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * PROT_CH11: Channel Protection
 *
 * \details
 * 0 (SEC): Channel is secured.
 * 1 (UNSEC): Channel is unsecured.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH11 . PROT_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH11_PROT_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH11_PROT_CH11  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CC_CH11_PROT_CH11(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DSYNC_CH11: Channel Synchronization (Peripheral Transfer Direction)
 *
 * \details
 * 0 (PER2MEM): Peripheral-to-memory transfer.
 * 1 (MEM2PER): Memory-to-peripheral transfer.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH11 . DSYNC_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH11_DSYNC_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH11_DSYNC_CH11  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CC_CH11_DSYNC_CH11(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * MBSIZE_CH11: Memory Burst Size
 *
 * \details
 * 0 (SINGLE): The memory burst size is set to one.
 * 1 (FOUR): The memory burst size is set to four.
 * 2 (EIGHT): The memory burst size is set to eight.
 * 3 (SIXTEEN): The memory burst size is set to sixteen.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH11 . MBSIZE_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH11_MBSIZE_CH11(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH11_MBSIZE_CH11     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH11_MBSIZE_CH11(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * TYPE_CH11: Transfer Type
 *
 * \details
 * 0 (MEM_TRAN): Self-triggered mode (memory-to-memory transfer).
 * 1 (PER_TRAN): Synchronized mode (peripheral-to-memory or
 * memory-to-peripheral transfer).
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH11 . TYPE_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH11_TYPE_CH11(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH11_TYPE_CH11  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CC_CH11_TYPE_CH11(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 11 Data Stride Memory Set Pattern Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDS_MSP_CH11
 */
#define VTSS_XDMAC_XDMAC_CDS_MSP_CH11        VTSS_IOREG(VTSS_TO_XDMAC,0xd3)

/**
 * \brief
 * DDS_MSP_CH11: Destination Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the destination data
 * stride.Number of bytes for the data stride of channel x (two's
 * complement). If the field is set to zero the data is contiguous.The
 * DDS_MSP_CHx field is only relevant when XDMAC_CCx.DAM=UBS_DS_AM.When
 * XDMAC_CCx.MEMSET = 1, this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH11 . DDS_MSP_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH11_DDS_MSP_CH11(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH11_DDS_MSP_CH11     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH11_DDS_MSP_CH11(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * SDS_MSP_CH11: Source Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the source data stride.Number
 * of bytes for the data stride of channel x (two's complement). If the
 * field is set to zero the data is contiguous.The SDS_MSP_CHx field is
 * only relevant when XDMAC_CCx.SAM=UBS_DS_AM.When XDMAC_CCx.MEMSET = 1,
 * this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH11 . SDS_MSP_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH11_SDS_MSP_CH11(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH11_SDS_MSP_CH11     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH11_SDS_MSP_CH11(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief XDMAC Channel 11 Source Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSUS_CH11
 */
#define VTSS_XDMAC_XDMAC_CSUS_CH11           VTSS_IOREG(VTSS_TO_XDMAC,0xd4)

/**
 * \brief
 * SUBS_CH11: Source Microblock StrideNumber of bytes for the microblock
 * stride for channel x (two's comlpement). If the field is set to zero the
 * data is contiguous.SUBS_CHx field is only relevant when
 * XDMAC_CCx.SAM=UBS_AM or XDMAC_CCx.SAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSUS_CH11 . SUBS_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CSUS_CH11_SUBS_CH11(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CSUS_CH11_SUBS_CH11     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CSUS_CH11_SUBS_CH11(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 11 Destination Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDUS_CH11
 */
#define VTSS_XDMAC_XDMAC_CDUS_CH11           VTSS_IOREG(VTSS_TO_XDMAC,0xd5)

/**
 * \brief
 * DUBS_CH11: Destination Microblock StrideNumber of bytes for the
 * microblock stride for channel x (two's comlpement). If the field is set
 * to zero the data is contiguous.DUBS_CHx field is only relevant when
 * XDMAC_CCx.DAM=UBS_AM or XDMAC_CCx.DAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDUS_CH11 . DUBS_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CDUS_CH11_DUBS_CH11(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CDUS_CH11_DUBS_CH11     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CDUS_CH11_DUBS_CH11(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 11 Transfer Count Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CTCS_CH11
 */
#define VTSS_XDMAC_XDMAC_CTCS_CH11           VTSS_IOREG(VTSS_TO_XDMAC,0xd6)

/**
 * \brief
 * TC_CH11: Transfer CountNumber of bytes written by the XDMA since the
 * last read of the Transfer Count Status register. The field does not
 * indicate the number of bytes written to memory.To get the number of
 * bytes already written in memory at any time during peripheral-to-memory
 * transfer, use the following software procedure:1. Read the
 * XDMAC_CTCSx.TC field to sample the number of bytes received by the
 * XDMA.2. Perform a software flush of the channel by writing one to the
 * XDMAC_GSWF register. This will push bytes from the internal DMA FIFO to
 * the external memory and return an interrupt when the bytes can be read
 * by the CPU.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CTCS_CH11 . TC_CH11
 */
#define  VTSS_F_XDMAC_XDMAC_CTCS_CH11_TC_CH11(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CTCS_CH11_TC_CH11     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CTCS_CH11_TC_CH11(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 12 Interrupt Enable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIE_CH12
 */
#define VTSS_XDMAC_XDMAC_CIE_CH12            VTSS_IOREG(VTSS_TO_XDMAC,0xd8)

/**
 * \brief
 * TCIE_CH12: Transfer Count Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH12 . TCIE_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH12_TCIE_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH12_TCIE_CH12  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH12_TCIE_CH12(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIE_CH12: Request Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH12 . ROIE_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH12_ROIE_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH12_ROIE_CH12  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH12_ROIE_CH12(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBIE_CH12: Write Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables write bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH12 . WBIE_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH12_WBIE_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH12_WBIE_CH12  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH12_WBIE_CH12(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBIE_CH12: Read Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables read bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH12 . RBIE_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH12_RBIE_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH12_RBIE_CH12  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH12_RBIE_CH12(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIE_CH12: End of Flush Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH12 . FIE_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH12_FIE_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH12_FIE_CH12  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH12_FIE_CH12(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIE_CH12: End of Disable Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH12 . DIE_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH12_DIE_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH12_DIE_CH12  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH12_DIE_CH12(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIE_CH12: End of Linked List Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH12 . LIE_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH12_LIE_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH12_LIE_CH12  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH12_LIE_CH12(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIE_CH12: End of Block Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH12 . BIE_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH12_BIE_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH12_BIE_CH12  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH12_BIE_CH12(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 12 Interrupt Disable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CID_CH12
 */
#define VTSS_XDMAC_XDMAC_CID_CH12            VTSS_IOREG(VTSS_TO_XDMAC,0xd9)

/**
 * \brief
 * TCID_CH12: Transfer Count Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH12 . TCID_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH12_TCID_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH12_TCID_CH12  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CID_CH12_TCID_CH12(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROID_CH12: Request Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH12 . ROID_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH12_ROID_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH12_ROID_CH12  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CID_CH12_ROID_CH12(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEID_CH12: Write Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH12 . WBEID_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH12_WBEID_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH12_WBEID_CH12  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CID_CH12_WBEID_CH12(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEID_CH12: Read Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH12 . RBEID_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH12_RBEID_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH12_RBEID_CH12  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CID_CH12_RBEID_CH12(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FID_CH12: End of Flush Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH12 . FID_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH12_FID_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH12_FID_CH12  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CID_CH12_FID_CH12(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DID_CH12: End of Disable Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH12 . DID_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH12_DID_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH12_DID_CH12  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CID_CH12_DID_CH12(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LID_CH12: End of Linked List Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH12 . LID_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH12_LID_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH12_LID_CH12  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CID_CH12_LID_CH12(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BID_CH12: End of Block Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH12 . BID_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH12_BID_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH12_BID_CH12  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CID_CH12_BID_CH12(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 12 Interrupt Mask Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIM_CH12
 */
#define VTSS_XDMAC_XDMAC_CIM_CH12            VTSS_IOREG(VTSS_TO_XDMAC,0xda)

/**
 * \brief
 * TCIM_CH12: Transfer Count Overflow Error Interrupt Mask
 *
 * \details
 * 0: Transfer count overflow interrupt is masked.
 * 1: Transfer count overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH12 . TCIM_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH12_TCIM_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH12_TCIM_CH12  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH12_TCIM_CH12(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIM_CH12: Request Overflow Error Interrupt Mask
 *
 * \details
 * 0: Request overflow interrupt is masked.
 * 1: Request overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH12 . ROIM_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH12_ROIM_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH12_ROIM_CH12  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH12_ROIM_CH12(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIM_CH12: Write Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH12 . WBEIM_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH12_WBEIM_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH12_WBEIM_CH12  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH12_WBEIM_CH12(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIM_CH12: Read Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH12 . RBEIM_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH12_RBEIM_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH12_RBEIM_CH12  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH12_RBEIM_CH12(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIM_CH12: End of Flush Interrupt Mask
 *
 * \details
 * 0: End of flush interrupt is masked.
 * 1: End of flush interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH12 . FIM_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH12_FIM_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH12_FIM_CH12  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH12_FIM_CH12(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIM_CH12: End of Disable Interrupt Mask
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH12 . DIM_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH12_DIM_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH12_DIM_CH12  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH12_DIM_CH12(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIM_CH12: End of Linked List Interrupt Mask
 *
 * \details
 * 0: End of linked list interrupt is masked.
 * 1: End of linked list interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH12 . LIM_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH12_LIM_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH12_LIM_CH12  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH12_LIM_CH12(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIM_CH12: End of Block Interrupt Mask
 *
 * \details
 * 0: Block interrupt is masked.
 * 1: Block interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH12 . BIM_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH12_BIM_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH12_BIM_CH12  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH12_BIM_CH12(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 12 Interrupt Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIS_CH12
 */
#define VTSS_XDMAC_XDMAC_CIS_CH12            VTSS_IOREG(VTSS_TO_XDMAC,0xdb)

/**
 * \brief
 * TCIS_CH12: Transfer Count Overflow Interrupt Status
 *
 * \details
 * 0: Transfer count overflow has not occurred.
 * 1: At least one transfer count overflow has been detected since the last
 * read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH12 . TCIS_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH12_TCIS_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH12_TCIS_CH12  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH12_TCIS_CH12(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIS_CH12: Request Overflow Error Interrupt Status
 *
 * \details
 * 0: Overflow condition has not occurred.
 * 1: Overflow condition has occurred at least once. (This information is
 * only relevant for peripheral synchronized transfers.)
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH12 . ROIS_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH12_ROIS_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH12_ROIS_CH12  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH12_ROIS_CH12(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIS_CH12: Write Bus Error Interrupt Status
 *
 * \details
 * 0: Write bus error condition has not occurred.
 * 1: At least one bus error has been detected in a write access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH12 . WBEIS_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH12_WBEIS_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH12_WBEIS_CH12  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH12_WBEIS_CH12(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIS_CH12: Read Bus Error Interrupt Status
 *
 * \details
 * 0: Read bus error condition has not occurred.
 * 1: At least one bus error has been detected in a read access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH12 . RBEIS_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH12_RBEIS_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH12_RBEIS_CH12  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH12_RBEIS_CH12(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIS_CH12: End of Flush Interrupt Status
 *
 * \details
 * 0: End of flush condition has not occurred.
 * 1: End of flush condition has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH12 . FIS_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH12_FIS_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH12_FIS_CH12  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH12_FIS_CH12(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIS_CH12: End of Disable Interrupt Status
 *
 * \details
 * 0: End of disable condition has not occurred.
 * 1: End of disable condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH12 . DIS_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH12_DIS_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH12_DIS_CH12  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH12_DIS_CH12(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIS_CH12: End of Linked List Interrupt Status
 *
 * \details
 * 0: End of linked list condition has not occurred.
 * 1: End of linked list condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH12 . LIS_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH12_LIS_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH12_LIS_CH12  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH12_LIS_CH12(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIS_CH12: End of Block Interrupt Status
 *
 * \details
 * 0: End of block interrupt has not occurred.
 * 1: End of block interrupt has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH12 . BIS_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH12_BIS_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH12_BIS_CH12  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH12_BIS_CH12(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 12 Source Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSA_CH12
 */
#define VTSS_XDMAC_XDMAC_CSA_CH12            VTSS_IOREG(VTSS_TO_XDMAC,0xdc)

/**
 * \brief
 * SA_CH12: Source AddressProgram this register with the source address of
 * the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSA_CH12 . SA_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CSA_CH12_SA_CH12(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CSA_CH12_SA_CH12     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CSA_CH12_SA_CH12(x)  (x)


/**
 * \brief XDMAC Channel 12 Destination Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDA_CH12
 */
#define VTSS_XDMAC_XDMAC_CDA_CH12            VTSS_IOREG(VTSS_TO_XDMAC,0xdd)

/**
 * \brief
 * DA_CH12: Destination AddressProgram this register with the destination
 * address of the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDA_CH12 . DA_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CDA_CH12_DA_CH12(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CDA_CH12_DA_CH12     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CDA_CH12_DA_CH12(x)  (x)


/**
 * \brief XDMAC Channel 12 Next Descriptor Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDA_CH12
 */
#define VTSS_XDMAC_XDMAC_CNDA_CH12           VTSS_IOREG(VTSS_TO_XDMAC,0xde)

/**
 * \brief
 * NDA_CH12: Next Descriptor AddressThe 30-bit width of the NDA field
 * represents the next descriptor address range 31:2. The descriptor is
 * word-aligned and the two least significant register bits 1:0 are
 * ignored.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDA_CH12 . NDA_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CNDA_CH12_NDA_CH12(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_XDMAC_XDMAC_CNDA_CH12_NDA_CH12     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_XDMAC_XDMAC_CNDA_CH12_NDA_CH12(x)  VTSS_EXTRACT_BITFIELD(x,2,30)


/**
 * \brief XDMAC Channel 12 Next Descriptor Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDC_CH12
 */
#define VTSS_XDMAC_XDMAC_CNDC_CH12           VTSS_IOREG(VTSS_TO_XDMAC,0xdf)

/**
 * \brief
 * QOS_CH12: Channel Quality Of Service LevelThis field indicates the
 * current quality of service level for the channel.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH12 . QOS_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH12_QOS_CH12(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH12_QOS_CH12     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH12_QOS_CH12(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * NDVIEW_CH12: Next Descriptor View
 *
 * \details
 * 0 (NDV0): Next Descriptor View 0
 * 1 (NDV0): Next Descriptor View 1
 * 2 (NDV0): Next Descriptor View 2
 * 3 (NDV0): Next Descriptor View 3
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH12 . NDVIEW_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH12_NDVIEW_CH12(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH12_NDVIEW_CH12     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH12_NDVIEW_CH12(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * NDDUP_CH12: Next Descriptor Destination Update
 *
 * \details
 * 0 (DST_PARAMS_UNCHANGED): Destination parameters remain unchanged.
 * 1 (DST_PARAMS_UPDATED): Destination parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH12 . NDDUP_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH12_NDDUP_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH12_NDDUP_CH12  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH12_NDDUP_CH12(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * NDSUP_CH12: Next Descriptor Source Update
 *
 * \details
 * 0 (SRC_PARAMS_UNCHANGED): Source parameters remain unchanged.
 * 1 (SRC_PARAMS_UPDATED): Source parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH12 . NDSUP_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH12_NDSUP_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH12_NDSUP_CH12  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH12_NDSUP_CH12(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * NDE_CH12: Next Descriptor Enable
 *
 * \details
 * 0 (DSCR_FETCH_DIS): Descriptor fetch is disabled.
 * 1 (DSCR_FETCH_EN): Descriptor fetch is enabled.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH12 . NDE_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH12_NDE_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH12_NDE_CH12  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH12_NDE_CH12(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 12 Microblock Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CUBC_CH12
 */
#define VTSS_XDMAC_XDMAC_CUBC_CH12           VTSS_IOREG(VTSS_TO_XDMAC,0xe0)

/**
 * \brief
 * UBLEN_CH12: Microblock LengthThis field indicates the number of data in
 * the microblock. The microblock contains UBLEN data.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CUBC_CH12 . UBLEN_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CUBC_CH12_UBLEN_CH12(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CUBC_CH12_UBLEN_CH12     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CUBC_CH12_UBLEN_CH12(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 12 Block Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CBC_CH12
 */
#define VTSS_XDMAC_XDMAC_CBC_CH12            VTSS_IOREG(VTSS_TO_XDMAC,0xe1)

/**
 * \brief
 * BLEN_CH12: Block LengthThe length of the block is (BLEN+1) microblocks.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CBC_CH12 . BLEN_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CBC_CH12_BLEN_CH12(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_XDMAC_XDMAC_CBC_CH12_BLEN_CH12     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_XDMAC_XDMAC_CBC_CH12_BLEN_CH12(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief XDMAC Channel 12 Configuration Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CC_CH12
 */
#define VTSS_XDMAC_XDMAC_CC_CH12             VTSS_IOREG(VTSS_TO_XDMAC,0xe2)

/**
 * \brief
 * PERID_CH12: Peripheral Hardware Request Line IdentifierThis field
 * contains the peripheral hardware request line identifier.Note: When a
 * memory-to-memory transfer is performed, configure PERID to an unused
 * peripheral ID.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH12 . PERID_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH12_PERID_CH12(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_XDMAC_XDMAC_CC_CH12_PERID_CH12     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH12_PERID_CH12(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * WRIP_CH12: Write in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active write transaction on the bus.
 * 1 (IN_PROGRESS): A write transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH12 . WRIP_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH12_WRIP_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH12_WRIP_CH12  VTSS_BIT(23)
#define  VTSS_X_XDMAC_XDMAC_CC_CH12_WRIP_CH12(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * RDIP_CH12: Read in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active read transaction on the bus.
 * 1 (IN_PROGRESS): A read transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH12 . RDIP_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH12_RDIP_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH12_RDIP_CH12  VTSS_BIT(22)
#define  VTSS_X_XDMAC_XDMAC_CC_CH12_RDIP_CH12(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * INITD_CH12: Channel Initialization Done (this bit is read-only)Note:
 * When set to 0, XDMAC_CUBC_CH12.UBLEN_CH12 and XDMAC_CNDA_CH12.NDA_CH12
 * field values are unreliable each time a descriptor is being updated.
 *
 * \details
 * 0 (IN_PROGRESS): Channel initialization is in progress.
 * 1 (TERMINATED): Channel initialization is completed.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH12 . INITD_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH12_INITD_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH12_INITD_CH12  VTSS_BIT(21)
#define  VTSS_X_XDMAC_XDMAC_CC_CH12_INITD_CH12(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * DAM_CH12: Destination Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH12 . DAM_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH12_DAM_CH12(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH12_DAM_CH12     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH12_DAM_CH12(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * SAM_CH12: Source Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH12 . SAM_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH12_SAM_CH12(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH12_SAM_CH12     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH12_SAM_CH12(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * DWIDTH_CH12: Data Width
 *
 * \details
 * 0 (BYTE): The data size is set to 8 bits.
 * 1 (HALFWORD): The data size is set to 16 bits.
 * 2 (WORD): The data size is set to 32 bits.
 * 3 (DWORD): The data size is set to 64 bits.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH12 . DWIDTH_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH12_DWIDTH_CH12(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH12_DWIDTH_CH12     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH12_DWIDTH_CH12(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * CSIZE_CH12: Chunk Size
 *
 * \details
 * 0 (CHK_1): 1 data transferred
 * 2 (CHK_2): 2 data transferred
 * 4 (CHK_4): 4 data transferred
 * 8 (CHK_8): 8 data transferred
 * 16 (CHK_16): 16 data transferred
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH12 . CSIZE_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH12_CSIZE_CH12(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_XDMAC_XDMAC_CC_CH12_CSIZE_CH12     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_XDMAC_XDMAC_CC_CH12_CSIZE_CH12(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * MEMSET_CH12: Fill Block of Memory
 *
 * \details
 * 0 (NORMAL_MODE): Memset is not activated.
 * 1 (HW_MODE): Sets the block of memory pointed by DA field to the
 * specified value. This operation is performed on 8-, 16- or 32-bit basis.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH12 . MEMSET_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH12_MEMSET_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH12_MEMSET_CH12  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH12_MEMSET_CH12(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * SWREQ_CH12: Software Request Trigger
 *
 * \details
 * 0 (HWR_CONNECTED): Hardware request line is connected to the peripheral
 * request line.
 * 1 (SWR_CONNECTED): Software request is connected to the peripheral
 * request line.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH12 . SWREQ_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH12_SWREQ_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH12_SWREQ_CH12  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CC_CH12_SWREQ_CH12(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * PROT_CH12: Channel Protection
 *
 * \details
 * 0 (SEC): Channel is secured.
 * 1 (UNSEC): Channel is unsecured.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH12 . PROT_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH12_PROT_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH12_PROT_CH12  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CC_CH12_PROT_CH12(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DSYNC_CH12: Channel Synchronization (Peripheral Transfer Direction)
 *
 * \details
 * 0 (PER2MEM): Peripheral-to-memory transfer.
 * 1 (MEM2PER): Memory-to-peripheral transfer.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH12 . DSYNC_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH12_DSYNC_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH12_DSYNC_CH12  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CC_CH12_DSYNC_CH12(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * MBSIZE_CH12: Memory Burst Size
 *
 * \details
 * 0 (SINGLE): The memory burst size is set to one.
 * 1 (FOUR): The memory burst size is set to four.
 * 2 (EIGHT): The memory burst size is set to eight.
 * 3 (SIXTEEN): The memory burst size is set to sixteen.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH12 . MBSIZE_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH12_MBSIZE_CH12(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH12_MBSIZE_CH12     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH12_MBSIZE_CH12(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * TYPE_CH12: Transfer Type
 *
 * \details
 * 0 (MEM_TRAN): Self-triggered mode (memory-to-memory transfer).
 * 1 (PER_TRAN): Synchronized mode (peripheral-to-memory or
 * memory-to-peripheral transfer).
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH12 . TYPE_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH12_TYPE_CH12(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH12_TYPE_CH12  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CC_CH12_TYPE_CH12(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 12 Data Stride Memory Set Pattern Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDS_MSP_CH12
 */
#define VTSS_XDMAC_XDMAC_CDS_MSP_CH12        VTSS_IOREG(VTSS_TO_XDMAC,0xe3)

/**
 * \brief
 * DDS_MSP_CH12: Destination Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the destination data
 * stride.Number of bytes for the data stride of channel x (two's
 * complement). If the field is set to zero the data is contiguous.The
 * DDS_MSP_CHx field is only relevant when XDMAC_CCx.DAM=UBS_DS_AM.When
 * XDMAC_CCx.MEMSET = 1, this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH12 . DDS_MSP_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH12_DDS_MSP_CH12(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH12_DDS_MSP_CH12     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH12_DDS_MSP_CH12(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * SDS_MSP_CH12: Source Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the source data stride.Number
 * of bytes for the data stride of channel x (two's complement). If the
 * field is set to zero the data is contiguous.The SDS_MSP_CHx field is
 * only relevant when XDMAC_CCx.SAM=UBS_DS_AM.When XDMAC_CCx.MEMSET = 1,
 * this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH12 . SDS_MSP_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH12_SDS_MSP_CH12(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH12_SDS_MSP_CH12     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH12_SDS_MSP_CH12(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief XDMAC Channel 12 Source Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSUS_CH12
 */
#define VTSS_XDMAC_XDMAC_CSUS_CH12           VTSS_IOREG(VTSS_TO_XDMAC,0xe4)

/**
 * \brief
 * SUBS_CH12: Source Microblock StrideNumber of bytes for the microblock
 * stride for channel x (two's comlpement). If the field is set to zero the
 * data is contiguous.SUBS_CHx field is only relevant when
 * XDMAC_CCx.SAM=UBS_AM or XDMAC_CCx.SAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSUS_CH12 . SUBS_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CSUS_CH12_SUBS_CH12(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CSUS_CH12_SUBS_CH12     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CSUS_CH12_SUBS_CH12(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 12 Destination Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDUS_CH12
 */
#define VTSS_XDMAC_XDMAC_CDUS_CH12           VTSS_IOREG(VTSS_TO_XDMAC,0xe5)

/**
 * \brief
 * DUBS_CH12: Destination Microblock StrideNumber of bytes for the
 * microblock stride for channel x (two's comlpement). If the field is set
 * to zero the data is contiguous.DUBS_CHx field is only relevant when
 * XDMAC_CCx.DAM=UBS_AM or XDMAC_CCx.DAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDUS_CH12 . DUBS_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CDUS_CH12_DUBS_CH12(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CDUS_CH12_DUBS_CH12     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CDUS_CH12_DUBS_CH12(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 12 Transfer Count Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CTCS_CH12
 */
#define VTSS_XDMAC_XDMAC_CTCS_CH12           VTSS_IOREG(VTSS_TO_XDMAC,0xe6)

/**
 * \brief
 * TC_CH12: Transfer CountNumber of bytes written by the XDMA since the
 * last read of the Transfer Count Status register. The field does not
 * indicate the number of bytes written to memory.To get the number of
 * bytes already written in memory at any time during peripheral-to-memory
 * transfer, use the following software procedure:1. Read the
 * XDMAC_CTCSx.TC field to sample the number of bytes received by the
 * XDMA.2. Perform a software flush of the channel by writing one to the
 * XDMAC_GSWF register. This will push bytes from the internal DMA FIFO to
 * the external memory and return an interrupt when the bytes can be read
 * by the CPU.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CTCS_CH12 . TC_CH12
 */
#define  VTSS_F_XDMAC_XDMAC_CTCS_CH12_TC_CH12(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CTCS_CH12_TC_CH12     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CTCS_CH12_TC_CH12(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 13 Interrupt Enable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIE_CH13
 */
#define VTSS_XDMAC_XDMAC_CIE_CH13            VTSS_IOREG(VTSS_TO_XDMAC,0xe8)

/**
 * \brief
 * TCIE_CH13: Transfer Count Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH13 . TCIE_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH13_TCIE_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH13_TCIE_CH13  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH13_TCIE_CH13(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIE_CH13: Request Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH13 . ROIE_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH13_ROIE_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH13_ROIE_CH13  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH13_ROIE_CH13(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBIE_CH13: Write Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables write bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH13 . WBIE_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH13_WBIE_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH13_WBIE_CH13  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH13_WBIE_CH13(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBIE_CH13: Read Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables read bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH13 . RBIE_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH13_RBIE_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH13_RBIE_CH13  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH13_RBIE_CH13(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIE_CH13: End of Flush Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH13 . FIE_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH13_FIE_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH13_FIE_CH13  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH13_FIE_CH13(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIE_CH13: End of Disable Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH13 . DIE_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH13_DIE_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH13_DIE_CH13  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH13_DIE_CH13(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIE_CH13: End of Linked List Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH13 . LIE_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH13_LIE_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH13_LIE_CH13  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH13_LIE_CH13(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIE_CH13: End of Block Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH13 . BIE_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH13_BIE_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH13_BIE_CH13  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH13_BIE_CH13(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 13 Interrupt Disable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CID_CH13
 */
#define VTSS_XDMAC_XDMAC_CID_CH13            VTSS_IOREG(VTSS_TO_XDMAC,0xe9)

/**
 * \brief
 * TCID_CH13: Transfer Count Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH13 . TCID_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH13_TCID_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH13_TCID_CH13  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CID_CH13_TCID_CH13(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROID_CH13: Request Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH13 . ROID_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH13_ROID_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH13_ROID_CH13  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CID_CH13_ROID_CH13(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEID_CH13: Write Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH13 . WBEID_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH13_WBEID_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH13_WBEID_CH13  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CID_CH13_WBEID_CH13(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEID_CH13: Read Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH13 . RBEID_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH13_RBEID_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH13_RBEID_CH13  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CID_CH13_RBEID_CH13(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FID_CH13: End of Flush Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH13 . FID_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH13_FID_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH13_FID_CH13  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CID_CH13_FID_CH13(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DID_CH13: End of Disable Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH13 . DID_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH13_DID_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH13_DID_CH13  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CID_CH13_DID_CH13(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LID_CH13: End of Linked List Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH13 . LID_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH13_LID_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH13_LID_CH13  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CID_CH13_LID_CH13(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BID_CH13: End of Block Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH13 . BID_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH13_BID_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH13_BID_CH13  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CID_CH13_BID_CH13(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 13 Interrupt Mask Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIM_CH13
 */
#define VTSS_XDMAC_XDMAC_CIM_CH13            VTSS_IOREG(VTSS_TO_XDMAC,0xea)

/**
 * \brief
 * TCIM_CH13: Transfer Count Overflow Error Interrupt Mask
 *
 * \details
 * 0: Transfer count overflow interrupt is masked.
 * 1: Transfer count overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH13 . TCIM_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH13_TCIM_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH13_TCIM_CH13  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH13_TCIM_CH13(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIM_CH13: Request Overflow Error Interrupt Mask
 *
 * \details
 * 0: Request overflow interrupt is masked.
 * 1: Request overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH13 . ROIM_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH13_ROIM_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH13_ROIM_CH13  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH13_ROIM_CH13(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIM_CH13: Write Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH13 . WBEIM_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH13_WBEIM_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH13_WBEIM_CH13  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH13_WBEIM_CH13(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIM_CH13: Read Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH13 . RBEIM_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH13_RBEIM_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH13_RBEIM_CH13  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH13_RBEIM_CH13(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIM_CH13: End of Flush Interrupt Mask
 *
 * \details
 * 0: End of flush interrupt is masked.
 * 1: End of flush interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH13 . FIM_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH13_FIM_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH13_FIM_CH13  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH13_FIM_CH13(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIM_CH13: End of Disable Interrupt Mask
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH13 . DIM_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH13_DIM_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH13_DIM_CH13  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH13_DIM_CH13(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIM_CH13: End of Linked List Interrupt Mask
 *
 * \details
 * 0: End of linked list interrupt is masked.
 * 1: End of linked list interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH13 . LIM_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH13_LIM_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH13_LIM_CH13  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH13_LIM_CH13(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIM_CH13: End of Block Interrupt Mask
 *
 * \details
 * 0: Block interrupt is masked.
 * 1: Block interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH13 . BIM_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH13_BIM_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH13_BIM_CH13  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH13_BIM_CH13(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 13 Interrupt Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIS_CH13
 */
#define VTSS_XDMAC_XDMAC_CIS_CH13            VTSS_IOREG(VTSS_TO_XDMAC,0xeb)

/**
 * \brief
 * TCIS_CH13: Transfer Count Overflow Interrupt Status
 *
 * \details
 * 0: Transfer count overflow has not occurred.
 * 1: At least one transfer count overflow has been detected since the last
 * read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH13 . TCIS_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH13_TCIS_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH13_TCIS_CH13  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH13_TCIS_CH13(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIS_CH13: Request Overflow Error Interrupt Status
 *
 * \details
 * 0: Overflow condition has not occurred.
 * 1: Overflow condition has occurred at least once. (This information is
 * only relevant for peripheral synchronized transfers.)
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH13 . ROIS_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH13_ROIS_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH13_ROIS_CH13  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH13_ROIS_CH13(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIS_CH13: Write Bus Error Interrupt Status
 *
 * \details
 * 0: Write bus error condition has not occurred.
 * 1: At least one bus error has been detected in a write access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH13 . WBEIS_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH13_WBEIS_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH13_WBEIS_CH13  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH13_WBEIS_CH13(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIS_CH13: Read Bus Error Interrupt Status
 *
 * \details
 * 0: Read bus error condition has not occurred.
 * 1: At least one bus error has been detected in a read access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH13 . RBEIS_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH13_RBEIS_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH13_RBEIS_CH13  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH13_RBEIS_CH13(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIS_CH13: End of Flush Interrupt Status
 *
 * \details
 * 0: End of flush condition has not occurred.
 * 1: End of flush condition has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH13 . FIS_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH13_FIS_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH13_FIS_CH13  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH13_FIS_CH13(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIS_CH13: End of Disable Interrupt Status
 *
 * \details
 * 0: End of disable condition has not occurred.
 * 1: End of disable condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH13 . DIS_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH13_DIS_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH13_DIS_CH13  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH13_DIS_CH13(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIS_CH13: End of Linked List Interrupt Status
 *
 * \details
 * 0: End of linked list condition has not occurred.
 * 1: End of linked list condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH13 . LIS_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH13_LIS_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH13_LIS_CH13  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH13_LIS_CH13(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIS_CH13: End of Block Interrupt Status
 *
 * \details
 * 0: End of block interrupt has not occurred.
 * 1: End of block interrupt has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH13 . BIS_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH13_BIS_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH13_BIS_CH13  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH13_BIS_CH13(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 13 Source Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSA_CH13
 */
#define VTSS_XDMAC_XDMAC_CSA_CH13            VTSS_IOREG(VTSS_TO_XDMAC,0xec)

/**
 * \brief
 * SA_CH13: Source AddressProgram this register with the source address of
 * the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSA_CH13 . SA_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CSA_CH13_SA_CH13(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CSA_CH13_SA_CH13     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CSA_CH13_SA_CH13(x)  (x)


/**
 * \brief XDMAC Channel 13 Destination Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDA_CH13
 */
#define VTSS_XDMAC_XDMAC_CDA_CH13            VTSS_IOREG(VTSS_TO_XDMAC,0xed)

/**
 * \brief
 * DA_CH13: Destination AddressProgram this register with the destination
 * address of the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDA_CH13 . DA_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CDA_CH13_DA_CH13(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CDA_CH13_DA_CH13     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CDA_CH13_DA_CH13(x)  (x)


/**
 * \brief XDMAC Channel 13 Next Descriptor Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDA_CH13
 */
#define VTSS_XDMAC_XDMAC_CNDA_CH13           VTSS_IOREG(VTSS_TO_XDMAC,0xee)

/**
 * \brief
 * NDA_CH13: Next Descriptor AddressThe 30-bit width of the NDA field
 * represents the next descriptor address range 31:2. The descriptor is
 * word-aligned and the two least significant register bits 1:0 are
 * ignored.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDA_CH13 . NDA_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CNDA_CH13_NDA_CH13(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_XDMAC_XDMAC_CNDA_CH13_NDA_CH13     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_XDMAC_XDMAC_CNDA_CH13_NDA_CH13(x)  VTSS_EXTRACT_BITFIELD(x,2,30)


/**
 * \brief XDMAC Channel 13 Next Descriptor Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDC_CH13
 */
#define VTSS_XDMAC_XDMAC_CNDC_CH13           VTSS_IOREG(VTSS_TO_XDMAC,0xef)

/**
 * \brief
 * QOS_CH13: Channel Quality Of Service LevelThis field indicates the
 * current quality of service level for the channel.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH13 . QOS_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH13_QOS_CH13(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH13_QOS_CH13     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH13_QOS_CH13(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * NDVIEW_CH13: Next Descriptor View
 *
 * \details
 * 0 (NDV0): Next Descriptor View 0
 * 1 (NDV0): Next Descriptor View 1
 * 2 (NDV0): Next Descriptor View 2
 * 3 (NDV0): Next Descriptor View 3
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH13 . NDVIEW_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH13_NDVIEW_CH13(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH13_NDVIEW_CH13     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH13_NDVIEW_CH13(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * NDDUP_CH13: Next Descriptor Destination Update
 *
 * \details
 * 0 (DST_PARAMS_UNCHANGED): Destination parameters remain unchanged.
 * 1 (DST_PARAMS_UPDATED): Destination parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH13 . NDDUP_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH13_NDDUP_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH13_NDDUP_CH13  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH13_NDDUP_CH13(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * NDSUP_CH13: Next Descriptor Source Update
 *
 * \details
 * 0 (SRC_PARAMS_UNCHANGED): Source parameters remain unchanged.
 * 1 (SRC_PARAMS_UPDATED): Source parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH13 . NDSUP_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH13_NDSUP_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH13_NDSUP_CH13  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH13_NDSUP_CH13(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * NDE_CH13: Next Descriptor Enable
 *
 * \details
 * 0 (DSCR_FETCH_DIS): Descriptor fetch is disabled.
 * 1 (DSCR_FETCH_EN): Descriptor fetch is enabled.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH13 . NDE_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH13_NDE_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH13_NDE_CH13  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH13_NDE_CH13(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 13 Microblock Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CUBC_CH13
 */
#define VTSS_XDMAC_XDMAC_CUBC_CH13           VTSS_IOREG(VTSS_TO_XDMAC,0xf0)

/**
 * \brief
 * UBLEN_CH13: Microblock LengthThis field indicates the number of data in
 * the microblock. The microblock contains UBLEN data.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CUBC_CH13 . UBLEN_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CUBC_CH13_UBLEN_CH13(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CUBC_CH13_UBLEN_CH13     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CUBC_CH13_UBLEN_CH13(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 13 Block Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CBC_CH13
 */
#define VTSS_XDMAC_XDMAC_CBC_CH13            VTSS_IOREG(VTSS_TO_XDMAC,0xf1)

/**
 * \brief
 * BLEN_CH13: Block LengthThe length of the block is (BLEN+1) microblocks.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CBC_CH13 . BLEN_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CBC_CH13_BLEN_CH13(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_XDMAC_XDMAC_CBC_CH13_BLEN_CH13     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_XDMAC_XDMAC_CBC_CH13_BLEN_CH13(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief XDMAC Channel 13 Configuration Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CC_CH13
 */
#define VTSS_XDMAC_XDMAC_CC_CH13             VTSS_IOREG(VTSS_TO_XDMAC,0xf2)

/**
 * \brief
 * PERID_CH13: Peripheral Hardware Request Line IdentifierThis field
 * contains the peripheral hardware request line identifier.Note: When a
 * memory-to-memory transfer is performed, configure PERID to an unused
 * peripheral ID.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH13 . PERID_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH13_PERID_CH13(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_XDMAC_XDMAC_CC_CH13_PERID_CH13     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH13_PERID_CH13(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * WRIP_CH13: Write in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active write transaction on the bus.
 * 1 (IN_PROGRESS): A write transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH13 . WRIP_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH13_WRIP_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH13_WRIP_CH13  VTSS_BIT(23)
#define  VTSS_X_XDMAC_XDMAC_CC_CH13_WRIP_CH13(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * RDIP_CH13: Read in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active read transaction on the bus.
 * 1 (IN_PROGRESS): A read transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH13 . RDIP_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH13_RDIP_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH13_RDIP_CH13  VTSS_BIT(22)
#define  VTSS_X_XDMAC_XDMAC_CC_CH13_RDIP_CH13(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * INITD_CH13: Channel Initialization Done (this bit is read-only)Note:
 * When set to 0, XDMAC_CUBC_CH13.UBLEN_CH13 and XDMAC_CNDA_CH13.NDA_CH13
 * field values are unreliable each time a descriptor is being updated.
 *
 * \details
 * 0 (IN_PROGRESS): Channel initialization is in progress.
 * 1 (TERMINATED): Channel initialization is completed.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH13 . INITD_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH13_INITD_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH13_INITD_CH13  VTSS_BIT(21)
#define  VTSS_X_XDMAC_XDMAC_CC_CH13_INITD_CH13(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * DAM_CH13: Destination Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH13 . DAM_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH13_DAM_CH13(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH13_DAM_CH13     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH13_DAM_CH13(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * SAM_CH13: Source Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH13 . SAM_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH13_SAM_CH13(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH13_SAM_CH13     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH13_SAM_CH13(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * DWIDTH_CH13: Data Width
 *
 * \details
 * 0 (BYTE): The data size is set to 8 bits.
 * 1 (HALFWORD): The data size is set to 16 bits.
 * 2 (WORD): The data size is set to 32 bits.
 * 3 (DWORD): The data size is set to 64 bits.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH13 . DWIDTH_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH13_DWIDTH_CH13(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH13_DWIDTH_CH13     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH13_DWIDTH_CH13(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * CSIZE_CH13: Chunk Size
 *
 * \details
 * 0 (CHK_1): 1 data transferred
 * 2 (CHK_2): 2 data transferred
 * 4 (CHK_4): 4 data transferred
 * 8 (CHK_8): 8 data transferred
 * 16 (CHK_16): 16 data transferred
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH13 . CSIZE_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH13_CSIZE_CH13(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_XDMAC_XDMAC_CC_CH13_CSIZE_CH13     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_XDMAC_XDMAC_CC_CH13_CSIZE_CH13(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * MEMSET_CH13: Fill Block of Memory
 *
 * \details
 * 0 (NORMAL_MODE): Memset is not activated.
 * 1 (HW_MODE): Sets the block of memory pointed by DA field to the
 * specified value. This operation is performed on 8-, 16- or 32-bit basis.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH13 . MEMSET_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH13_MEMSET_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH13_MEMSET_CH13  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH13_MEMSET_CH13(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * SWREQ_CH13: Software Request Trigger
 *
 * \details
 * 0 (HWR_CONNECTED): Hardware request line is connected to the peripheral
 * request line.
 * 1 (SWR_CONNECTED): Software request is connected to the peripheral
 * request line.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH13 . SWREQ_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH13_SWREQ_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH13_SWREQ_CH13  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CC_CH13_SWREQ_CH13(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * PROT_CH13: Channel Protection
 *
 * \details
 * 0 (SEC): Channel is secured.
 * 1 (UNSEC): Channel is unsecured.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH13 . PROT_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH13_PROT_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH13_PROT_CH13  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CC_CH13_PROT_CH13(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DSYNC_CH13: Channel Synchronization (Peripheral Transfer Direction)
 *
 * \details
 * 0 (PER2MEM): Peripheral-to-memory transfer.
 * 1 (MEM2PER): Memory-to-peripheral transfer.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH13 . DSYNC_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH13_DSYNC_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH13_DSYNC_CH13  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CC_CH13_DSYNC_CH13(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * MBSIZE_CH13: Memory Burst Size
 *
 * \details
 * 0 (SINGLE): The memory burst size is set to one.
 * 1 (FOUR): The memory burst size is set to four.
 * 2 (EIGHT): The memory burst size is set to eight.
 * 3 (SIXTEEN): The memory burst size is set to sixteen.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH13 . MBSIZE_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH13_MBSIZE_CH13(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH13_MBSIZE_CH13     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH13_MBSIZE_CH13(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * TYPE_CH13: Transfer Type
 *
 * \details
 * 0 (MEM_TRAN): Self-triggered mode (memory-to-memory transfer).
 * 1 (PER_TRAN): Synchronized mode (peripheral-to-memory or
 * memory-to-peripheral transfer).
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH13 . TYPE_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH13_TYPE_CH13(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH13_TYPE_CH13  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CC_CH13_TYPE_CH13(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 13 Data Stride Memory Set Pattern Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDS_MSP_CH13
 */
#define VTSS_XDMAC_XDMAC_CDS_MSP_CH13        VTSS_IOREG(VTSS_TO_XDMAC,0xf3)

/**
 * \brief
 * DDS_MSP_CH13: Destination Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the destination data
 * stride.Number of bytes for the data stride of channel x (two's
 * complement). If the field is set to zero the data is contiguous.The
 * DDS_MSP_CHx field is only relevant when XDMAC_CCx.DAM=UBS_DS_AM.When
 * XDMAC_CCx.MEMSET = 1, this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH13 . DDS_MSP_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH13_DDS_MSP_CH13(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH13_DDS_MSP_CH13     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH13_DDS_MSP_CH13(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * SDS_MSP_CH13: Source Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the source data stride.Number
 * of bytes for the data stride of channel x (two's complement). If the
 * field is set to zero the data is contiguous.The SDS_MSP_CHx field is
 * only relevant when XDMAC_CCx.SAM=UBS_DS_AM.When XDMAC_CCx.MEMSET = 1,
 * this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH13 . SDS_MSP_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH13_SDS_MSP_CH13(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH13_SDS_MSP_CH13     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH13_SDS_MSP_CH13(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief XDMAC Channel 13 Source Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSUS_CH13
 */
#define VTSS_XDMAC_XDMAC_CSUS_CH13           VTSS_IOREG(VTSS_TO_XDMAC,0xf4)

/**
 * \brief
 * SUBS_CH13: Source Microblock StrideNumber of bytes for the microblock
 * stride for channel x (two's comlpement). If the field is set to zero the
 * data is contiguous.SUBS_CHx field is only relevant when
 * XDMAC_CCx.SAM=UBS_AM or XDMAC_CCx.SAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSUS_CH13 . SUBS_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CSUS_CH13_SUBS_CH13(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CSUS_CH13_SUBS_CH13     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CSUS_CH13_SUBS_CH13(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 13 Destination Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDUS_CH13
 */
#define VTSS_XDMAC_XDMAC_CDUS_CH13           VTSS_IOREG(VTSS_TO_XDMAC,0xf5)

/**
 * \brief
 * DUBS_CH13: Destination Microblock StrideNumber of bytes for the
 * microblock stride for channel x (two's comlpement). If the field is set
 * to zero the data is contiguous.DUBS_CHx field is only relevant when
 * XDMAC_CCx.DAM=UBS_AM or XDMAC_CCx.DAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDUS_CH13 . DUBS_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CDUS_CH13_DUBS_CH13(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CDUS_CH13_DUBS_CH13     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CDUS_CH13_DUBS_CH13(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 13 Transfer Count Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CTCS_CH13
 */
#define VTSS_XDMAC_XDMAC_CTCS_CH13           VTSS_IOREG(VTSS_TO_XDMAC,0xf6)

/**
 * \brief
 * TC_CH13: Transfer CountNumber of bytes written by the XDMA since the
 * last read of the Transfer Count Status register. The field does not
 * indicate the number of bytes written to memory.To get the number of
 * bytes already written in memory at any time during peripheral-to-memory
 * transfer, use the following software procedure:1. Read the
 * XDMAC_CTCSx.TC field to sample the number of bytes received by the
 * XDMA.2. Perform a software flush of the channel by writing one to the
 * XDMAC_GSWF register. This will push bytes from the internal DMA FIFO to
 * the external memory and return an interrupt when the bytes can be read
 * by the CPU.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CTCS_CH13 . TC_CH13
 */
#define  VTSS_F_XDMAC_XDMAC_CTCS_CH13_TC_CH13(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CTCS_CH13_TC_CH13     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CTCS_CH13_TC_CH13(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 14 Interrupt Enable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIE_CH14
 */
#define VTSS_XDMAC_XDMAC_CIE_CH14            VTSS_IOREG(VTSS_TO_XDMAC,0xf8)

/**
 * \brief
 * TCIE_CH14: Transfer Count Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH14 . TCIE_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH14_TCIE_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH14_TCIE_CH14  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH14_TCIE_CH14(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIE_CH14: Request Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH14 . ROIE_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH14_ROIE_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH14_ROIE_CH14  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH14_ROIE_CH14(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBIE_CH14: Write Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables write bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH14 . WBIE_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH14_WBIE_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH14_WBIE_CH14  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH14_WBIE_CH14(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBIE_CH14: Read Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables read bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH14 . RBIE_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH14_RBIE_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH14_RBIE_CH14  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH14_RBIE_CH14(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIE_CH14: End of Flush Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH14 . FIE_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH14_FIE_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH14_FIE_CH14  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH14_FIE_CH14(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIE_CH14: End of Disable Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH14 . DIE_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH14_DIE_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH14_DIE_CH14  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH14_DIE_CH14(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIE_CH14: End of Linked List Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH14 . LIE_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH14_LIE_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH14_LIE_CH14  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH14_LIE_CH14(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIE_CH14: End of Block Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH14 . BIE_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH14_BIE_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH14_BIE_CH14  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH14_BIE_CH14(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 14 Interrupt Disable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CID_CH14
 */
#define VTSS_XDMAC_XDMAC_CID_CH14            VTSS_IOREG(VTSS_TO_XDMAC,0xf9)

/**
 * \brief
 * TCID_CH14: Transfer Count Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH14 . TCID_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH14_TCID_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH14_TCID_CH14  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CID_CH14_TCID_CH14(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROID_CH14: Request Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH14 . ROID_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH14_ROID_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH14_ROID_CH14  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CID_CH14_ROID_CH14(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEID_CH14: Write Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH14 . WBEID_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH14_WBEID_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH14_WBEID_CH14  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CID_CH14_WBEID_CH14(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEID_CH14: Read Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH14 . RBEID_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH14_RBEID_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH14_RBEID_CH14  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CID_CH14_RBEID_CH14(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FID_CH14: End of Flush Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH14 . FID_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH14_FID_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH14_FID_CH14  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CID_CH14_FID_CH14(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DID_CH14: End of Disable Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH14 . DID_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH14_DID_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH14_DID_CH14  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CID_CH14_DID_CH14(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LID_CH14: End of Linked List Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH14 . LID_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH14_LID_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH14_LID_CH14  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CID_CH14_LID_CH14(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BID_CH14: End of Block Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH14 . BID_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH14_BID_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH14_BID_CH14  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CID_CH14_BID_CH14(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 14 Interrupt Mask Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIM_CH14
 */
#define VTSS_XDMAC_XDMAC_CIM_CH14            VTSS_IOREG(VTSS_TO_XDMAC,0xfa)

/**
 * \brief
 * TCIM_CH14: Transfer Count Overflow Error Interrupt Mask
 *
 * \details
 * 0: Transfer count overflow interrupt is masked.
 * 1: Transfer count overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH14 . TCIM_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH14_TCIM_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH14_TCIM_CH14  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH14_TCIM_CH14(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIM_CH14: Request Overflow Error Interrupt Mask
 *
 * \details
 * 0: Request overflow interrupt is masked.
 * 1: Request overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH14 . ROIM_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH14_ROIM_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH14_ROIM_CH14  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH14_ROIM_CH14(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIM_CH14: Write Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH14 . WBEIM_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH14_WBEIM_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH14_WBEIM_CH14  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH14_WBEIM_CH14(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIM_CH14: Read Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH14 . RBEIM_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH14_RBEIM_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH14_RBEIM_CH14  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH14_RBEIM_CH14(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIM_CH14: End of Flush Interrupt Mask
 *
 * \details
 * 0: End of flush interrupt is masked.
 * 1: End of flush interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH14 . FIM_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH14_FIM_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH14_FIM_CH14  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH14_FIM_CH14(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIM_CH14: End of Disable Interrupt Mask
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH14 . DIM_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH14_DIM_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH14_DIM_CH14  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH14_DIM_CH14(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIM_CH14: End of Linked List Interrupt Mask
 *
 * \details
 * 0: End of linked list interrupt is masked.
 * 1: End of linked list interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH14 . LIM_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH14_LIM_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH14_LIM_CH14  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH14_LIM_CH14(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIM_CH14: End of Block Interrupt Mask
 *
 * \details
 * 0: Block interrupt is masked.
 * 1: Block interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH14 . BIM_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH14_BIM_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH14_BIM_CH14  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH14_BIM_CH14(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 14 Interrupt Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIS_CH14
 */
#define VTSS_XDMAC_XDMAC_CIS_CH14            VTSS_IOREG(VTSS_TO_XDMAC,0xfb)

/**
 * \brief
 * TCIS_CH14: Transfer Count Overflow Interrupt Status
 *
 * \details
 * 0: Transfer count overflow has not occurred.
 * 1: At least one transfer count overflow has been detected since the last
 * read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH14 . TCIS_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH14_TCIS_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH14_TCIS_CH14  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH14_TCIS_CH14(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIS_CH14: Request Overflow Error Interrupt Status
 *
 * \details
 * 0: Overflow condition has not occurred.
 * 1: Overflow condition has occurred at least once. (This information is
 * only relevant for peripheral synchronized transfers.)
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH14 . ROIS_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH14_ROIS_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH14_ROIS_CH14  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH14_ROIS_CH14(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIS_CH14: Write Bus Error Interrupt Status
 *
 * \details
 * 0: Write bus error condition has not occurred.
 * 1: At least one bus error has been detected in a write access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH14 . WBEIS_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH14_WBEIS_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH14_WBEIS_CH14  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH14_WBEIS_CH14(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIS_CH14: Read Bus Error Interrupt Status
 *
 * \details
 * 0: Read bus error condition has not occurred.
 * 1: At least one bus error has been detected in a read access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH14 . RBEIS_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH14_RBEIS_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH14_RBEIS_CH14  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH14_RBEIS_CH14(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIS_CH14: End of Flush Interrupt Status
 *
 * \details
 * 0: End of flush condition has not occurred.
 * 1: End of flush condition has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH14 . FIS_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH14_FIS_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH14_FIS_CH14  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH14_FIS_CH14(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIS_CH14: End of Disable Interrupt Status
 *
 * \details
 * 0: End of disable condition has not occurred.
 * 1: End of disable condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH14 . DIS_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH14_DIS_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH14_DIS_CH14  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH14_DIS_CH14(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIS_CH14: End of Linked List Interrupt Status
 *
 * \details
 * 0: End of linked list condition has not occurred.
 * 1: End of linked list condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH14 . LIS_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH14_LIS_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH14_LIS_CH14  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH14_LIS_CH14(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIS_CH14: End of Block Interrupt Status
 *
 * \details
 * 0: End of block interrupt has not occurred.
 * 1: End of block interrupt has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH14 . BIS_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH14_BIS_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH14_BIS_CH14  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH14_BIS_CH14(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 14 Source Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSA_CH14
 */
#define VTSS_XDMAC_XDMAC_CSA_CH14            VTSS_IOREG(VTSS_TO_XDMAC,0xfc)

/**
 * \brief
 * SA_CH14: Source AddressProgram this register with the source address of
 * the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSA_CH14 . SA_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CSA_CH14_SA_CH14(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CSA_CH14_SA_CH14     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CSA_CH14_SA_CH14(x)  (x)


/**
 * \brief XDMAC Channel 14 Destination Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDA_CH14
 */
#define VTSS_XDMAC_XDMAC_CDA_CH14            VTSS_IOREG(VTSS_TO_XDMAC,0xfd)

/**
 * \brief
 * DA_CH14: Destination AddressProgram this register with the destination
 * address of the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDA_CH14 . DA_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CDA_CH14_DA_CH14(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CDA_CH14_DA_CH14     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CDA_CH14_DA_CH14(x)  (x)


/**
 * \brief XDMAC Channel 14 Next Descriptor Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDA_CH14
 */
#define VTSS_XDMAC_XDMAC_CNDA_CH14           VTSS_IOREG(VTSS_TO_XDMAC,0xfe)

/**
 * \brief
 * NDA_CH14: Next Descriptor AddressThe 30-bit width of the NDA field
 * represents the next descriptor address range 31:2. The descriptor is
 * word-aligned and the two least significant register bits 1:0 are
 * ignored.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDA_CH14 . NDA_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CNDA_CH14_NDA_CH14(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_XDMAC_XDMAC_CNDA_CH14_NDA_CH14     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_XDMAC_XDMAC_CNDA_CH14_NDA_CH14(x)  VTSS_EXTRACT_BITFIELD(x,2,30)


/**
 * \brief XDMAC Channel 14 Next Descriptor Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDC_CH14
 */
#define VTSS_XDMAC_XDMAC_CNDC_CH14           VTSS_IOREG(VTSS_TO_XDMAC,0xff)

/**
 * \brief
 * QOS_CH14: Channel Quality Of Service LevelThis field indicates the
 * current quality of service level for the channel.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH14 . QOS_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH14_QOS_CH14(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH14_QOS_CH14     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH14_QOS_CH14(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * NDVIEW_CH14: Next Descriptor View
 *
 * \details
 * 0 (NDV0): Next Descriptor View 0
 * 1 (NDV0): Next Descriptor View 1
 * 2 (NDV0): Next Descriptor View 2
 * 3 (NDV0): Next Descriptor View 3
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH14 . NDVIEW_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH14_NDVIEW_CH14(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH14_NDVIEW_CH14     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH14_NDVIEW_CH14(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * NDDUP_CH14: Next Descriptor Destination Update
 *
 * \details
 * 0 (DST_PARAMS_UNCHANGED): Destination parameters remain unchanged.
 * 1 (DST_PARAMS_UPDATED): Destination parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH14 . NDDUP_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH14_NDDUP_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH14_NDDUP_CH14  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH14_NDDUP_CH14(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * NDSUP_CH14: Next Descriptor Source Update
 *
 * \details
 * 0 (SRC_PARAMS_UNCHANGED): Source parameters remain unchanged.
 * 1 (SRC_PARAMS_UPDATED): Source parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH14 . NDSUP_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH14_NDSUP_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH14_NDSUP_CH14  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH14_NDSUP_CH14(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * NDE_CH14: Next Descriptor Enable
 *
 * \details
 * 0 (DSCR_FETCH_DIS): Descriptor fetch is disabled.
 * 1 (DSCR_FETCH_EN): Descriptor fetch is enabled.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH14 . NDE_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH14_NDE_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH14_NDE_CH14  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH14_NDE_CH14(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 14 Microblock Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CUBC_CH14
 */
#define VTSS_XDMAC_XDMAC_CUBC_CH14           VTSS_IOREG(VTSS_TO_XDMAC,0x100)

/**
 * \brief
 * UBLEN_CH14: Microblock LengthThis field indicates the number of data in
 * the microblock. The microblock contains UBLEN data.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CUBC_CH14 . UBLEN_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CUBC_CH14_UBLEN_CH14(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CUBC_CH14_UBLEN_CH14     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CUBC_CH14_UBLEN_CH14(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 14 Block Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CBC_CH14
 */
#define VTSS_XDMAC_XDMAC_CBC_CH14            VTSS_IOREG(VTSS_TO_XDMAC,0x101)

/**
 * \brief
 * BLEN_CH14: Block LengthThe length of the block is (BLEN+1) microblocks.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CBC_CH14 . BLEN_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CBC_CH14_BLEN_CH14(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_XDMAC_XDMAC_CBC_CH14_BLEN_CH14     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_XDMAC_XDMAC_CBC_CH14_BLEN_CH14(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief XDMAC Channel 14 Configuration Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CC_CH14
 */
#define VTSS_XDMAC_XDMAC_CC_CH14             VTSS_IOREG(VTSS_TO_XDMAC,0x102)

/**
 * \brief
 * PERID_CH14: Peripheral Hardware Request Line IdentifierThis field
 * contains the peripheral hardware request line identifier.Note: When a
 * memory-to-memory transfer is performed, configure PERID to an unused
 * peripheral ID.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH14 . PERID_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH14_PERID_CH14(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_XDMAC_XDMAC_CC_CH14_PERID_CH14     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH14_PERID_CH14(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * WRIP_CH14: Write in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active write transaction on the bus.
 * 1 (IN_PROGRESS): A write transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH14 . WRIP_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH14_WRIP_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH14_WRIP_CH14  VTSS_BIT(23)
#define  VTSS_X_XDMAC_XDMAC_CC_CH14_WRIP_CH14(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * RDIP_CH14: Read in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active read transaction on the bus.
 * 1 (IN_PROGRESS): A read transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH14 . RDIP_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH14_RDIP_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH14_RDIP_CH14  VTSS_BIT(22)
#define  VTSS_X_XDMAC_XDMAC_CC_CH14_RDIP_CH14(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * INITD_CH14: Channel Initialization Done (this bit is read-only)Note:
 * When set to 0, XDMAC_CUBC_CH14.UBLEN_CH14 and XDMAC_CNDA_CH14.NDA_CH14
 * field values are unreliable each time a descriptor is being updated.
 *
 * \details
 * 0 (IN_PROGRESS): Channel initialization is in progress.
 * 1 (TERMINATED): Channel initialization is completed.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH14 . INITD_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH14_INITD_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH14_INITD_CH14  VTSS_BIT(21)
#define  VTSS_X_XDMAC_XDMAC_CC_CH14_INITD_CH14(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * DAM_CH14: Destination Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH14 . DAM_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH14_DAM_CH14(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH14_DAM_CH14     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH14_DAM_CH14(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * SAM_CH14: Source Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH14 . SAM_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH14_SAM_CH14(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH14_SAM_CH14     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH14_SAM_CH14(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * DWIDTH_CH14: Data Width
 *
 * \details
 * 0 (BYTE): The data size is set to 8 bits.
 * 1 (HALFWORD): The data size is set to 16 bits.
 * 2 (WORD): The data size is set to 32 bits.
 * 3 (DWORD): The data size is set to 64 bits.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH14 . DWIDTH_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH14_DWIDTH_CH14(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH14_DWIDTH_CH14     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH14_DWIDTH_CH14(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * CSIZE_CH14: Chunk Size
 *
 * \details
 * 0 (CHK_1): 1 data transferred
 * 2 (CHK_2): 2 data transferred
 * 4 (CHK_4): 4 data transferred
 * 8 (CHK_8): 8 data transferred
 * 16 (CHK_16): 16 data transferred
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH14 . CSIZE_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH14_CSIZE_CH14(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_XDMAC_XDMAC_CC_CH14_CSIZE_CH14     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_XDMAC_XDMAC_CC_CH14_CSIZE_CH14(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * MEMSET_CH14: Fill Block of Memory
 *
 * \details
 * 0 (NORMAL_MODE): Memset is not activated.
 * 1 (HW_MODE): Sets the block of memory pointed by DA field to the
 * specified value. This operation is performed on 8-, 16- or 32-bit basis.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH14 . MEMSET_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH14_MEMSET_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH14_MEMSET_CH14  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH14_MEMSET_CH14(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * SWREQ_CH14: Software Request Trigger
 *
 * \details
 * 0 (HWR_CONNECTED): Hardware request line is connected to the peripheral
 * request line.
 * 1 (SWR_CONNECTED): Software request is connected to the peripheral
 * request line.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH14 . SWREQ_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH14_SWREQ_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH14_SWREQ_CH14  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CC_CH14_SWREQ_CH14(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * PROT_CH14: Channel Protection
 *
 * \details
 * 0 (SEC): Channel is secured.
 * 1 (UNSEC): Channel is unsecured.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH14 . PROT_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH14_PROT_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH14_PROT_CH14  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CC_CH14_PROT_CH14(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DSYNC_CH14: Channel Synchronization (Peripheral Transfer Direction)
 *
 * \details
 * 0 (PER2MEM): Peripheral-to-memory transfer.
 * 1 (MEM2PER): Memory-to-peripheral transfer.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH14 . DSYNC_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH14_DSYNC_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH14_DSYNC_CH14  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CC_CH14_DSYNC_CH14(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * MBSIZE_CH14: Memory Burst Size
 *
 * \details
 * 0 (SINGLE): The memory burst size is set to one.
 * 1 (FOUR): The memory burst size is set to four.
 * 2 (EIGHT): The memory burst size is set to eight.
 * 3 (SIXTEEN): The memory burst size is set to sixteen.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH14 . MBSIZE_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH14_MBSIZE_CH14(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH14_MBSIZE_CH14     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH14_MBSIZE_CH14(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * TYPE_CH14: Transfer Type
 *
 * \details
 * 0 (MEM_TRAN): Self-triggered mode (memory-to-memory transfer).
 * 1 (PER_TRAN): Synchronized mode (peripheral-to-memory or
 * memory-to-peripheral transfer).
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH14 . TYPE_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH14_TYPE_CH14(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH14_TYPE_CH14  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CC_CH14_TYPE_CH14(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 14 Data Stride Memory Set Pattern Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDS_MSP_CH14
 */
#define VTSS_XDMAC_XDMAC_CDS_MSP_CH14        VTSS_IOREG(VTSS_TO_XDMAC,0x103)

/**
 * \brief
 * DDS_MSP_CH14: Destination Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the destination data
 * stride.Number of bytes for the data stride of channel x (two's
 * complement). If the field is set to zero the data is contiguous.The
 * DDS_MSP_CHx field is only relevant when XDMAC_CCx.DAM=UBS_DS_AM.When
 * XDMAC_CCx.MEMSET = 1, this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH14 . DDS_MSP_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH14_DDS_MSP_CH14(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH14_DDS_MSP_CH14     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH14_DDS_MSP_CH14(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * SDS_MSP_CH14: Source Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the source data stride.Number
 * of bytes for the data stride of channel x (two's complement). If the
 * field is set to zero the data is contiguous.The SDS_MSP_CHx field is
 * only relevant when XDMAC_CCx.SAM=UBS_DS_AM.When XDMAC_CCx.MEMSET = 1,
 * this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH14 . SDS_MSP_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH14_SDS_MSP_CH14(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH14_SDS_MSP_CH14     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH14_SDS_MSP_CH14(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief XDMAC Channel 14 Source Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSUS_CH14
 */
#define VTSS_XDMAC_XDMAC_CSUS_CH14           VTSS_IOREG(VTSS_TO_XDMAC,0x104)

/**
 * \brief
 * SUBS_CH14: Source Microblock StrideNumber of bytes for the microblock
 * stride for channel x (two's comlpement). If the field is set to zero the
 * data is contiguous.SUBS_CHx field is only relevant when
 * XDMAC_CCx.SAM=UBS_AM or XDMAC_CCx.SAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSUS_CH14 . SUBS_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CSUS_CH14_SUBS_CH14(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CSUS_CH14_SUBS_CH14     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CSUS_CH14_SUBS_CH14(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 14 Destination Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDUS_CH14
 */
#define VTSS_XDMAC_XDMAC_CDUS_CH14           VTSS_IOREG(VTSS_TO_XDMAC,0x105)

/**
 * \brief
 * DUBS_CH14: Destination Microblock StrideNumber of bytes for the
 * microblock stride for channel x (two's comlpement). If the field is set
 * to zero the data is contiguous.DUBS_CHx field is only relevant when
 * XDMAC_CCx.DAM=UBS_AM or XDMAC_CCx.DAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDUS_CH14 . DUBS_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CDUS_CH14_DUBS_CH14(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CDUS_CH14_DUBS_CH14     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CDUS_CH14_DUBS_CH14(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 14 Transfer Count Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CTCS_CH14
 */
#define VTSS_XDMAC_XDMAC_CTCS_CH14           VTSS_IOREG(VTSS_TO_XDMAC,0x106)

/**
 * \brief
 * TC_CH14: Transfer CountNumber of bytes written by the XDMA since the
 * last read of the Transfer Count Status register. The field does not
 * indicate the number of bytes written to memory.To get the number of
 * bytes already written in memory at any time during peripheral-to-memory
 * transfer, use the following software procedure:1. Read the
 * XDMAC_CTCSx.TC field to sample the number of bytes received by the
 * XDMA.2. Perform a software flush of the channel by writing one to the
 * XDMAC_GSWF register. This will push bytes from the internal DMA FIFO to
 * the external memory and return an interrupt when the bytes can be read
 * by the CPU.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CTCS_CH14 . TC_CH14
 */
#define  VTSS_F_XDMAC_XDMAC_CTCS_CH14_TC_CH14(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CTCS_CH14_TC_CH14     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CTCS_CH14_TC_CH14(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 15 Interrupt Enable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIE_CH15
 */
#define VTSS_XDMAC_XDMAC_CIE_CH15            VTSS_IOREG(VTSS_TO_XDMAC,0x108)

/**
 * \brief
 * TCIE_CH15: Transfer Count Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH15 . TCIE_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH15_TCIE_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH15_TCIE_CH15  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH15_TCIE_CH15(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIE_CH15: Request Overflow Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH15 . ROIE_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH15_ROIE_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH15_ROIE_CH15  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH15_ROIE_CH15(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBIE_CH15: Write Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables write bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH15 . WBIE_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH15_WBIE_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH15_WBIE_CH15  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH15_WBIE_CH15(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBIE_CH15: Read Bus Error Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables read bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH15 . RBIE_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH15_RBIE_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH15_RBIE_CH15  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH15_RBIE_CH15(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIE_CH15: End of Flush Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH15 . FIE_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH15_FIE_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH15_FIE_CH15  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH15_FIE_CH15(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIE_CH15: End of Disable Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH15 . DIE_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH15_DIE_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH15_DIE_CH15  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH15_DIE_CH15(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIE_CH15: End of Linked List Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH15 . LIE_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH15_LIE_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH15_LIE_CH15  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH15_LIE_CH15(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIE_CH15: End of Block Interrupt Enable
 *
 * \details
 * 0: No effect.
 * 1: Enables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIE_CH15 . BIE_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIE_CH15_BIE_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIE_CH15_BIE_CH15  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIE_CH15_BIE_CH15(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 15 Interrupt Disable Register
 *
 * \details
 * Note: This register has Write-only access.
 *
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CID_CH15
 */
#define VTSS_XDMAC_XDMAC_CID_CH15            VTSS_IOREG(VTSS_TO_XDMAC,0x109)

/**
 * \brief
 * TCID_CH15: Transfer Count Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables transfer count overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH15 . TCID_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH15_TCID_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH15_TCID_CH15  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CID_CH15_TCID_CH15(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROID_CH15: Request Overflow Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables request overflow error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH15 . ROID_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH15_ROID_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH15_ROID_CH15  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CID_CH15_ROID_CH15(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEID_CH15: Write Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH15 . WBEID_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH15_WBEID_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH15_WBEID_CH15  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CID_CH15_WBEID_CH15(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEID_CH15: Read Bus Error Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables bus error interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH15 . RBEID_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH15_RBEID_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH15_RBEID_CH15  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CID_CH15_RBEID_CH15(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FID_CH15: End of Flush Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of flush interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH15 . FID_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH15_FID_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH15_FID_CH15  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CID_CH15_FID_CH15(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DID_CH15: End of Disable Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of disable interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH15 . DID_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH15_DID_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH15_DID_CH15  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CID_CH15_DID_CH15(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LID_CH15: End of Linked List Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of linked list interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH15 . LID_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH15_LID_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH15_LID_CH15  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CID_CH15_LID_CH15(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BID_CH15: End of Block Interrupt Disable
 *
 * \details
 * 0: No effect.
 * 1: Disables end of block interrupt.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CID_CH15 . BID_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CID_CH15_BID_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CID_CH15_BID_CH15  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CID_CH15_BID_CH15(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 15 Interrupt Mask Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIM_CH15
 */
#define VTSS_XDMAC_XDMAC_CIM_CH15            VTSS_IOREG(VTSS_TO_XDMAC,0x10a)

/**
 * \brief
 * TCIM_CH15: Transfer Count Overflow Error Interrupt Mask
 *
 * \details
 * 0: Transfer count overflow interrupt is masked.
 * 1: Transfer count overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH15 . TCIM_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH15_TCIM_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH15_TCIM_CH15  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH15_TCIM_CH15(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIM_CH15: Request Overflow Error Interrupt Mask
 *
 * \details
 * 0: Request overflow interrupt is masked.
 * 1: Request overflow interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH15 . ROIM_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH15_ROIM_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH15_ROIM_CH15  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH15_ROIM_CH15(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIM_CH15: Write Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH15 . WBEIM_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH15_WBEIM_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH15_WBEIM_CH15  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH15_WBEIM_CH15(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIM_CH15: Read Bus Error Interrupt Mask
 *
 * \details
 * 0: Bus error interrupt is masked.
 * 1: Bus error interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH15 . RBEIM_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH15_RBEIM_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH15_RBEIM_CH15  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH15_RBEIM_CH15(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIM_CH15: End of Flush Interrupt Mask
 *
 * \details
 * 0: End of flush interrupt is masked.
 * 1: End of flush interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH15 . FIM_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH15_FIM_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH15_FIM_CH15  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH15_FIM_CH15(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIM_CH15: End of Disable Interrupt Mask
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH15 . DIM_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH15_DIM_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH15_DIM_CH15  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH15_DIM_CH15(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIM_CH15: End of Linked List Interrupt Mask
 *
 * \details
 * 0: End of linked list interrupt is masked.
 * 1: End of linked list interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH15 . LIM_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH15_LIM_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH15_LIM_CH15  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH15_LIM_CH15(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIM_CH15: End of Block Interrupt Mask
 *
 * \details
 * 0: Block interrupt is masked.
 * 1: Block interrupt is activated.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIM_CH15 . BIM_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIM_CH15_BIM_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIM_CH15_BIM_CH15  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIM_CH15_BIM_CH15(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 15 Interrupt Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CIS_CH15
 */
#define VTSS_XDMAC_XDMAC_CIS_CH15            VTSS_IOREG(VTSS_TO_XDMAC,0x10b)

/**
 * \brief
 * TCIS_CH15: Transfer Count Overflow Interrupt Status
 *
 * \details
 * 0: Transfer count overflow has not occurred.
 * 1: At least one transfer count overflow has been detected since the last
 * read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH15 . TCIS_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH15_TCIS_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH15_TCIS_CH15  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH15_TCIS_CH15(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * ROIS_CH15: Request Overflow Error Interrupt Status
 *
 * \details
 * 0: Overflow condition has not occurred.
 * 1: Overflow condition has occurred at least once. (This information is
 * only relevant for peripheral synchronized transfers.)
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH15 . ROIS_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH15_ROIS_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH15_ROIS_CH15  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH15_ROIS_CH15(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * WBEIS_CH15: Write Bus Error Interrupt Status
 *
 * \details
 * 0: Write bus error condition has not occurred.
 * 1: At least one bus error has been detected in a write access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH15 . WBEIS_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH15_WBEIS_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH15_WBEIS_CH15  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH15_WBEIS_CH15(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RBEIS_CH15: Read Bus Error Interrupt Status
 *
 * \details
 * 0: Read bus error condition has not occurred.
 * 1: At least one bus error has been detected in a read access since the
 * last read of the Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH15 . RBEIS_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH15_RBEIS_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH15_RBEIS_CH15  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH15_RBEIS_CH15(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * FIS_CH15: End of Flush Interrupt Status
 *
 * \details
 * 0: End of flush condition has not occurred.
 * 1: End of flush condition has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH15 . FIS_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH15_FIS_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH15_FIS_CH15  VTSS_BIT(3)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH15_FIS_CH15(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * DIS_CH15: End of Disable Interrupt Status
 *
 * \details
 * 0: End of disable condition has not occurred.
 * 1: End of disable condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH15 . DIS_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH15_DIS_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH15_DIS_CH15  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH15_DIS_CH15(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * LIS_CH15: End of Linked List Interrupt Status
 *
 * \details
 * 0: End of linked list condition has not occurred.
 * 1: End of linked list condition has occurred since the last read of the
 * Status register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH15 . LIS_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH15_LIS_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH15_LIS_CH15  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH15_LIS_CH15(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIS_CH15: End of Block Interrupt Status
 *
 * \details
 * 0: End of block interrupt has not occurred.
 * 1: End of block interrupt has occurred since the last read of the Status
 * register.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CIS_CH15 . BIS_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CIS_CH15_BIS_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CIS_CH15_BIS_CH15  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CIS_CH15_BIS_CH15(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 15 Source Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSA_CH15
 */
#define VTSS_XDMAC_XDMAC_CSA_CH15            VTSS_IOREG(VTSS_TO_XDMAC,0x10c)

/**
 * \brief
 * SA_CH15: Source AddressProgram this register with the source address of
 * the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSA_CH15 . SA_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CSA_CH15_SA_CH15(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CSA_CH15_SA_CH15     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CSA_CH15_SA_CH15(x)  (x)


/**
 * \brief XDMAC Channel 15 Destination Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDA_CH15
 */
#define VTSS_XDMAC_XDMAC_CDA_CH15            VTSS_IOREG(VTSS_TO_XDMAC,0x10d)

/**
 * \brief
 * DA_CH15: Destination AddressProgram this register with the destination
 * address of the DMA transfer.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDA_CH15 . DA_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CDA_CH15_DA_CH15(x)  (x)
#define  VTSS_M_XDMAC_XDMAC_CDA_CH15_DA_CH15     0xffffffff
#define  VTSS_X_XDMAC_XDMAC_CDA_CH15_DA_CH15(x)  (x)


/**
 * \brief XDMAC Channel 15 Next Descriptor Address Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDA_CH15
 */
#define VTSS_XDMAC_XDMAC_CNDA_CH15           VTSS_IOREG(VTSS_TO_XDMAC,0x10e)

/**
 * \brief
 * NDA_CH15: Next Descriptor AddressThe 30-bit width of the NDA field
 * represents the next descriptor address range 31:2. The descriptor is
 * word-aligned and the two least significant register bits 1:0 are
 * ignored.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDA_CH15 . NDA_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CNDA_CH15_NDA_CH15(x)  VTSS_ENCODE_BITFIELD(x,2,30)
#define  VTSS_M_XDMAC_XDMAC_CNDA_CH15_NDA_CH15     VTSS_ENCODE_BITMASK(2,30)
#define  VTSS_X_XDMAC_XDMAC_CNDA_CH15_NDA_CH15(x)  VTSS_EXTRACT_BITFIELD(x,2,30)


/**
 * \brief XDMAC Channel 15 Next Descriptor Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CNDC_CH15
 */
#define VTSS_XDMAC_XDMAC_CNDC_CH15           VTSS_IOREG(VTSS_TO_XDMAC,0x10f)

/**
 * \brief
 * QOS_CH15: Channel Quality Of Service LevelThis field indicates the
 * current quality of service level for the channel.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH15 . QOS_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH15_QOS_CH15(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH15_QOS_CH15     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH15_QOS_CH15(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * NDVIEW_CH15: Next Descriptor View
 *
 * \details
 * 0 (NDV0): Next Descriptor View 0
 * 1 (NDV0): Next Descriptor View 1
 * 2 (NDV0): Next Descriptor View 2
 * 3 (NDV0): Next Descriptor View 3
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH15 . NDVIEW_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH15_NDVIEW_CH15(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH15_NDVIEW_CH15     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH15_NDVIEW_CH15(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * NDDUP_CH15: Next Descriptor Destination Update
 *
 * \details
 * 0 (DST_PARAMS_UNCHANGED): Destination parameters remain unchanged.
 * 1 (DST_PARAMS_UPDATED): Destination parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH15 . NDDUP_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH15_NDDUP_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH15_NDDUP_CH15  VTSS_BIT(2)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH15_NDDUP_CH15(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * NDSUP_CH15: Next Descriptor Source Update
 *
 * \details
 * 0 (SRC_PARAMS_UNCHANGED): Source parameters remain unchanged.
 * 1 (SRC_PARAMS_UPDATED): Source parameters are updated when the
 * descriptor is retrieved.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH15 . NDSUP_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH15_NDSUP_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH15_NDSUP_CH15  VTSS_BIT(1)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH15_NDSUP_CH15(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * NDE_CH15: Next Descriptor Enable
 *
 * \details
 * 0 (DSCR_FETCH_DIS): Descriptor fetch is disabled.
 * 1 (DSCR_FETCH_EN): Descriptor fetch is enabled.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CNDC_CH15 . NDE_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CNDC_CH15_NDE_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CNDC_CH15_NDE_CH15  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CNDC_CH15_NDE_CH15(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 15 Microblock Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CUBC_CH15
 */
#define VTSS_XDMAC_XDMAC_CUBC_CH15           VTSS_IOREG(VTSS_TO_XDMAC,0x110)

/**
 * \brief
 * UBLEN_CH15: Microblock LengthThis field indicates the number of data in
 * the microblock. The microblock contains UBLEN data.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CUBC_CH15 . UBLEN_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CUBC_CH15_UBLEN_CH15(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CUBC_CH15_UBLEN_CH15     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CUBC_CH15_UBLEN_CH15(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 15 Block Control Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CBC_CH15
 */
#define VTSS_XDMAC_XDMAC_CBC_CH15            VTSS_IOREG(VTSS_TO_XDMAC,0x111)

/**
 * \brief
 * BLEN_CH15: Block LengthThe length of the block is (BLEN+1) microblocks.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CBC_CH15 . BLEN_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CBC_CH15_BLEN_CH15(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_XDMAC_XDMAC_CBC_CH15_BLEN_CH15     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_XDMAC_XDMAC_CBC_CH15_BLEN_CH15(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief XDMAC Channel 15 Configuration Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CC_CH15
 */
#define VTSS_XDMAC_XDMAC_CC_CH15             VTSS_IOREG(VTSS_TO_XDMAC,0x112)

/**
 * \brief
 * PERID_CH15: Peripheral Hardware Request Line IdentifierThis field
 * contains the peripheral hardware request line identifier.Note: When a
 * memory-to-memory transfer is performed, configure PERID to an unused
 * peripheral ID.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH15 . PERID_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH15_PERID_CH15(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_XDMAC_XDMAC_CC_CH15_PERID_CH15     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH15_PERID_CH15(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * WRIP_CH15: Write in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active write transaction on the bus.
 * 1 (IN_PROGRESS): A write transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH15 . WRIP_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH15_WRIP_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH15_WRIP_CH15  VTSS_BIT(23)
#define  VTSS_X_XDMAC_XDMAC_CC_CH15_WRIP_CH15(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * RDIP_CH15: Read in Progress (this bit is read-only)
 *
 * \details
 * 0 (DONE): No active read transaction on the bus.
 * 1 (IN_PROGRESS): A read transaction is in progress.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH15 . RDIP_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH15_RDIP_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH15_RDIP_CH15  VTSS_BIT(22)
#define  VTSS_X_XDMAC_XDMAC_CC_CH15_RDIP_CH15(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * INITD_CH15: Channel Initialization Done (this bit is read-only)Note:
 * When set to 0, XDMAC_CUBC_CH15.UBLEN_CH15 and XDMAC_CNDA_CH15.NDA_CH15
 * field values are unreliable each time a descriptor is being updated.
 *
 * \details
 * 0 (IN_PROGRESS): Channel initialization is in progress.
 * 1 (TERMINATED): Channel initialization is completed.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH15 . INITD_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH15_INITD_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH15_INITD_CH15  VTSS_BIT(21)
#define  VTSS_X_XDMAC_XDMAC_CC_CH15_INITD_CH15(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * DAM_CH15: Destination Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH15 . DAM_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH15_DAM_CH15(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH15_DAM_CH15     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH15_DAM_CH15(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * SAM_CH15: Source Addressing Mode
 *
 * \details
 * 0 (FIXED_AM): The address remains unchanged.
 * 1 (INCREMENT_AM): The addressing mode is incremented (the increment size
 * is set to the data size).
 * 2 (UBS_AM): The microblock stride is added at the microblock boundary.
 * 3 (UBS_DS_AM): The microblock stride is added at the microblock
 * boundary, the data stride is added at the data boundary.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH15 . SAM_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH15_SAM_CH15(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH15_SAM_CH15     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH15_SAM_CH15(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * DWIDTH_CH15: Data Width
 *
 * \details
 * 0 (BYTE): The data size is set to 8 bits.
 * 1 (HALFWORD): The data size is set to 16 bits.
 * 2 (WORD): The data size is set to 32 bits.
 * 3 (DWORD): The data size is set to 64 bits.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH15 . DWIDTH_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH15_DWIDTH_CH15(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH15_DWIDTH_CH15     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH15_DWIDTH_CH15(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * CSIZE_CH15: Chunk Size
 *
 * \details
 * 0 (CHK_1): 1 data transferred
 * 2 (CHK_2): 2 data transferred
 * 4 (CHK_4): 4 data transferred
 * 8 (CHK_8): 8 data transferred
 * 16 (CHK_16): 16 data transferred
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH15 . CSIZE_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH15_CSIZE_CH15(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_XDMAC_XDMAC_CC_CH15_CSIZE_CH15     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_XDMAC_XDMAC_CC_CH15_CSIZE_CH15(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * MEMSET_CH15: Fill Block of Memory
 *
 * \details
 * 0 (NORMAL_MODE): Memset is not activated.
 * 1 (HW_MODE): Sets the block of memory pointed by DA field to the
 * specified value. This operation is performed on 8-, 16- or 32-bit basis.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH15 . MEMSET_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH15_MEMSET_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH15_MEMSET_CH15  VTSS_BIT(7)
#define  VTSS_X_XDMAC_XDMAC_CC_CH15_MEMSET_CH15(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * SWREQ_CH15: Software Request Trigger
 *
 * \details
 * 0 (HWR_CONNECTED): Hardware request line is connected to the peripheral
 * request line.
 * 1 (SWR_CONNECTED): Software request is connected to the peripheral
 * request line.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH15 . SWREQ_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH15_SWREQ_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH15_SWREQ_CH15  VTSS_BIT(6)
#define  VTSS_X_XDMAC_XDMAC_CC_CH15_SWREQ_CH15(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * PROT_CH15: Channel Protection
 *
 * \details
 * 0 (SEC): Channel is secured.
 * 1 (UNSEC): Channel is unsecured.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH15 . PROT_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH15_PROT_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH15_PROT_CH15  VTSS_BIT(5)
#define  VTSS_X_XDMAC_XDMAC_CC_CH15_PROT_CH15(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * DSYNC_CH15: Channel Synchronization (Peripheral Transfer Direction)
 *
 * \details
 * 0 (PER2MEM): Peripheral-to-memory transfer.
 * 1 (MEM2PER): Memory-to-peripheral transfer.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH15 . DSYNC_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH15_DSYNC_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH15_DSYNC_CH15  VTSS_BIT(4)
#define  VTSS_X_XDMAC_XDMAC_CC_CH15_DSYNC_CH15(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * MBSIZE_CH15: Memory Burst Size
 *
 * \details
 * 0 (SINGLE): The memory burst size is set to one.
 * 1 (FOUR): The memory burst size is set to four.
 * 2 (EIGHT): The memory burst size is set to eight.
 * 3 (SIXTEEN): The memory burst size is set to sixteen.
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH15 . MBSIZE_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH15_MBSIZE_CH15(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_XDMAC_XDMAC_CC_CH15_MBSIZE_CH15     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_XDMAC_XDMAC_CC_CH15_MBSIZE_CH15(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * TYPE_CH15: Transfer Type
 *
 * \details
 * 0 (MEM_TRAN): Self-triggered mode (memory-to-memory transfer).
 * 1 (PER_TRAN): Synchronized mode (peripheral-to-memory or
 * memory-to-peripheral transfer).
 *
 * Field: ::VTSS_XDMAC_XDMAC_CC_CH15 . TYPE_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CC_CH15_TYPE_CH15(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XDMAC_XDMAC_CC_CH15_TYPE_CH15  VTSS_BIT(0)
#define  VTSS_X_XDMAC_XDMAC_CC_CH15_TYPE_CH15(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief XDMAC Channel 15 Data Stride Memory Set Pattern Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDS_MSP_CH15
 */
#define VTSS_XDMAC_XDMAC_CDS_MSP_CH15        VTSS_IOREG(VTSS_TO_XDMAC,0x113)

/**
 * \brief
 * DDS_MSP_CH15: Destination Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the destination data
 * stride.Number of bytes for the data stride of channel x (two's
 * complement). If the field is set to zero the data is contiguous.The
 * DDS_MSP_CHx field is only relevant when XDMAC_CCx.DAM=UBS_DS_AM.When
 * XDMAC_CCx.MEMSET = 1, this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH15 . DDS_MSP_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH15_DDS_MSP_CH15(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH15_DDS_MSP_CH15     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH15_DDS_MSP_CH15(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * SDS_MSP_CH15: Source Data Stride or Memory Set PatternWhen
 * XDMAC_CCx.MEMSET = 0, this field indicates the source data stride.Number
 * of bytes for the data stride of channel x (two's complement). If the
 * field is set to zero the data is contiguous.The SDS_MSP_CHx field is
 * only relevant when XDMAC_CCx.SAM=UBS_DS_AM.When XDMAC_CCx.MEMSET = 1,
 * this field indicates the memory set pattern.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDS_MSP_CH15 . SDS_MSP_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CDS_MSP_CH15_SDS_MSP_CH15(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_XDMAC_XDMAC_CDS_MSP_CH15_SDS_MSP_CH15     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_XDMAC_XDMAC_CDS_MSP_CH15_SDS_MSP_CH15(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief XDMAC Channel 15 Source Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CSUS_CH15
 */
#define VTSS_XDMAC_XDMAC_CSUS_CH15           VTSS_IOREG(VTSS_TO_XDMAC,0x114)

/**
 * \brief
 * SUBS_CH15: Source Microblock StrideNumber of bytes for the microblock
 * stride for channel x (two's comlpement). If the field is set to zero the
 * data is contiguous.SUBS_CHx field is only relevant when
 * XDMAC_CCx.SAM=UBS_AM or XDMAC_CCx.SAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CSUS_CH15 . SUBS_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CSUS_CH15_SUBS_CH15(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CSUS_CH15_SUBS_CH15     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CSUS_CH15_SUBS_CH15(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 15 Destination Microblock Stride Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CDUS_CH15
 */
#define VTSS_XDMAC_XDMAC_CDUS_CH15           VTSS_IOREG(VTSS_TO_XDMAC,0x115)

/**
 * \brief
 * DUBS_CH15: Destination Microblock StrideNumber of bytes for the
 * microblock stride for channel x (two's comlpement). If the field is set
 * to zero the data is contiguous.DUBS_CHx field is only relevant when
 * XDMAC_CCx.DAM=UBS_AM or XDMAC_CCx.DAM=UBS_DS_AM.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CDUS_CH15 . DUBS_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CDUS_CH15_DUBS_CH15(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CDUS_CH15_DUBS_CH15     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CDUS_CH15_DUBS_CH15(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Channel 15 Transfer Count Status Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_CTCS_CH15
 */
#define VTSS_XDMAC_XDMAC_CTCS_CH15           VTSS_IOREG(VTSS_TO_XDMAC,0x116)

/**
 * \brief
 * TC_CH15: Transfer CountNumber of bytes written by the XDMA since the
 * last read of the Transfer Count Status register. The field does not
 * indicate the number of bytes written to memory.To get the number of
 * bytes already written in memory at any time during peripheral-to-memory
 * transfer, use the following software procedure:1. Read the
 * XDMAC_CTCSx.TC field to sample the number of bytes received by the
 * XDMA.2. Perform a software flush of the channel by writing one to the
 * XDMAC_GSWF register. This will push bytes from the internal DMA FIFO to
 * the external memory and return an interrupt when the bytes can be read
 * by the CPU.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_CTCS_CH15 . TC_CH15
 */
#define  VTSS_F_XDMAC_XDMAC_CTCS_CH15_TC_CH15(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_XDMAC_XDMAC_CTCS_CH15_TC_CH15     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_XDMAC_XDMAC_CTCS_CH15_TC_CH15(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief XDMAC Version Register
 *
 * \details
 * Register: \a XDMAC:XDMAC_REG:XDMAC_VERSION
 */
#define VTSS_XDMAC_XDMAC_VERSION             VTSS_IOREG(VTSS_TO_XDMAC,0x3ff)

/**
 * \brief
 * MFN: Metal Fix NumberReserved. Value subject to change. No functionality
 * associated.Note: Reset value for this field varies with the version of
 * the IP block imlpementation.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_VERSION . MFN
 */
#define  VTSS_F_XDMAC_XDMAC_VERSION_MFN(x)    VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_XDMAC_XDMAC_VERSION_MFN       VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_XDMAC_XDMAC_VERSION_MFN(x)    VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * VERSION: Version of the Hardware ModuleReserved. Value subject to
 * change. No functionality associated. This is the internal version of the
 * macrocell.Note: Reset value for this field varies with the version of
 * the IP block imlpementation.
 *
 * \details
 * Field: ::VTSS_XDMAC_XDMAC_VERSION . VERSION
 */
#define  VTSS_F_XDMAC_XDMAC_VERSION_VERSION(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_XDMAC_XDMAC_VERSION_VERSION     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_XDMAC_XDMAC_VERSION_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


#endif /* _VTSS_LAGUNA_REGS_XDMAC_H_ */
