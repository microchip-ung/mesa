// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LAN80XX_MALIBU25G_REGS_MCU_IO_MNGT_MISC_H_
#define LAN80XX_MALIBU25G_REGS_MCU_IO_MNGT_MISC_H_

#include "regs_lan80xx_common.h"

/***********************************************************************
 *
 * Target: \a MCU_IO_MNGT_MISC
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a MCU_IO_MNGT_MISC:DEVICE_INFO
 *
 * Device Info
 */


/**
 * \brief Device ID register
 *
 * \details
 * Device ID register
 *
 * Register: \a MCU_IO_MNGT_MISC:DEVICE_INFO:DEVICE_ID_REG
 */
#define LAN80XX_MCU_IO_MNGT_MISC_DEVICE_ID_REG                                                      (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x0))

/**
 * \brief
 * This is the device ID register.
 *
 * \details
 * LAN8042:  0x8042
 * LAN8022:  0x8022
 * LAN8041:  0x8041
 * LAN8021:  0x8021
 * LAN8043:  0x8043
 * LAN8044:  0x8044
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DEVICE_ID_REG . DEVICE_ID
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DEVICE_ID_REG_DEVICE_ID(x)                                      (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DEVICE_ID_REG_DEVICE_ID                                         (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DEVICE_ID_REG_DEVICE_ID(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Device OTP revision register
 *
 * \details
 * Device OTP revision register
 *
 * Register: \a MCU_IO_MNGT_MISC:DEVICE_INFO:DEVICE_OTP_REVISION_REG
 */
#define LAN80XX_MCU_IO_MNGT_MISC_DEVICE_OTP_REVISION_REG                                            (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1))

/**
 * \brief
 * The value of this register comes from the REV_ID field of the OTP
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DEVICE_OTP_REVISION_REG . DEVICE_OTP_REVISION
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DEVICE_OTP_REVISION_REG_DEVICE_OTP_REVISION(x)                  (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DEVICE_OTP_REVISION_REG_DEVICE_OTP_REVISION                     (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DEVICE_OTP_REVISION_REG_DEVICE_OTP_REVISION(x)                  (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief Device revision register
 *
 * \details
 * Device revision register
 *
 * Register: \a MCU_IO_MNGT_MISC:DEVICE_INFO:DEVICE_SILICON_REVISION_REG
 */
#define LAN80XX_MCU_IO_MNGT_MISC_DEVICE_SILICON_REVISION_REG                                        (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x2))

/**
 * \brief
 * The value of this register tracks the mask set and metal revision within
 * the mask set.
 *
 * \details
 * Bit[7:4] track the mask set
 * Bit[3:0] track the mask set metal revision
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DEVICE_SILICON_REVISION_REG . DEVICE_SILICON_REVISION
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DEVICE_SILICON_REVISION_REG_DEVICE_SILICON_REVISION(x)          (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DEVICE_SILICON_REVISION_REG_DEVICE_SILICON_REVISION             (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DEVICE_SILICON_REVISION_REG_DEVICE_SILICON_REVISION(x)          (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief Device feature disable register
 *
 * \details
 * Device feature disable register
 *
 * Register: \a MCU_IO_MNGT_MISC:DEVICE_INFO:DEVICE_FEATURE_DISABLE_REG
 */
#define LAN80XX_MCU_IO_MNGT_MISC_DEVICE_FEATURE_DISABLE_REG                                         (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x3))

/**
 * \brief
 * the value of this register comes from the FEAT_DIS field of the OTP
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DEVICE_FEATURE_DISABLE_REG . DEVICE_FEATURE_DISABLE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DEVICE_FEATURE_DISABLE_REG_DEVICE_FEATURE_DISABLE(x)            (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DEVICE_FEATURE_DISABLE_REG_DEVICE_FEATURE_DISABLE               (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DEVICE_FEATURE_DISABLE_REG_DEVICE_FEATURE_DISABLE(x)            (LAN80XX_EXTRACT_BITFIELD(x,0,8))

/**
 * Register Group: \a MCU_IO_MNGT_MISC:MIM_SPARE_RW_REG
 *
 * spare read/write registers
 */


/**
 * \brief spare read/write registers
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:MIM_SPARE_RW_REG:MIM_SPARE_RW_REG
 *
 * @param ri Register: MIM_SPARE_RW_REG (??), 0-3
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MIM_SPARE_RW_REG(ri)                                               (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x4 + (ri)))

/**
 * \brief
 * spare read/write registers
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MIM_SPARE_RW_REG . MIM_SPARE_RW_REG
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MIM_SPARE_RW_REG_MIM_SPARE_RW_REG(x)                            (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MIM_SPARE_RW_REG_MIM_SPARE_RW_REG                               (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MIM_SPARE_RW_REG_MIM_SPARE_RW_REG(x)                            (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a MCU_IO_MNGT_MISC:MIM_SPARE_STS_REG
 *
 * spare status registers
 */


/**
 * \brief spare status registers
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:MIM_SPARE_STS_REG:MIM_SPARE_STS_REG
 *
 * @param ri Register: MIM_SPARE_STS_REG (??), 0-1
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MIM_SPARE_STS_REG(ri)                                              (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x8 + (ri)))

/**
 * \brief
 * spare status registers
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MIM_SPARE_STS_REG . MIM_SPARE_STS_REG
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MIM_SPARE_STS_REG_MIM_SPARE_STS_REG(x)                          (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MIM_SPARE_STS_REG_MIM_SPARE_STS_REG                             (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MIM_SPARE_STS_REG_MIM_SPARE_STS_REG(x)                          (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a MCU_IO_MNGT_MISC:MCU_RESET_INFO
 *
 * MCU reset information registers
 */


/**
 * \brief the reason of MCU RESET
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:MCU_RESET_INFO:MCU_RESET_REASON_STATUS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS                                            (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0xa))

/**
 * \brief
 * This bit is a status bit reflects the value of
 * MCU_MISC_REG:MIM_MISC_REG_REGS:MCU_RESET_REASON.IS_POR
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS . MCU_RESET_REASON_5
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS_MCU_RESET_REASON_5(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS_MCU_RESET_REASON_5                      (LAN80XX_BIT(5))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS_MCU_RESET_REASON_5(x)                   (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * This bit is a status bit reflects the value of
 * MCU_MISC_REG:MIM_MISC_REG_REGS:MCU_RESET_REASON.IS_GLBL_FAST_CHIP_SW_RES
 * ET
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS . MCU_RESET_REASON_4
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS_MCU_RESET_REASON_4(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS_MCU_RESET_REASON_4                      (LAN80XX_BIT(4))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS_MCU_RESET_REASON_4(x)                   (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * This bit is a status bit reflects the value of
 * MCU_MISC_REG:MIM_MISC_REG_REGS:MCU_RESET_REASON.IS_GLBL_CHIP_SW_RESET
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS . MCU_RESET_REASON_3
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS_MCU_RESET_REASON_3(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS_MCU_RESET_REASON_3                      (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS_MCU_RESET_REASON_3(x)                   (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * This bit is a status bit reflects the value of
 * MCU_MISC_REG:MIM_MISC_REG_REGS:MCU_RESET_REASON.IS_GLBL_MCU_SW_RESET
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS . MCU_RESET_REASON_2
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS_MCU_RESET_REASON_2(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS_MCU_RESET_REASON_2                      (LAN80XX_BIT(2))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS_MCU_RESET_REASON_2(x)                   (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * This bit is a status bit reflects the value of
 * MCU_MISC_REG:MIM_MISC_REG_REGS:MCU_RESET_REASON.IS_WDT
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS . MCU_RESET_REASON_1
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS_MCU_RESET_REASON_1(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS_MCU_RESET_REASON_1                      (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS_MCU_RESET_REASON_1(x)                   (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * This bit is a status bit reflects the value of
 * MCU_MISC_REG:MIM_MISC_REG_REGS:MCU_RESET_REASON.IS_SYSRESETREQ
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS . MCU_RESET_REASON_0
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS_MCU_RESET_REASON_0(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS_MCU_RESET_REASON_0                      (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MCU_RESET_REASON_STATUS_MCU_RESET_REASON_0(x)                   (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a MCU_IO_MNGT_MISC:MCU_WDT_STS
 *
 * MCU Watchdog Timer Status
 */


/**
 * \brief MCU Watchdog Timer Status
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:MCU_WDT_STS:MCU_WDT_STS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MCU_WDT_STS                                                        (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x10))

/**
 * \brief
 * indicates the WDT event occurred.
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MCU_WDT_STS . MCU_WDT_STS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MCU_WDT_STS_MCU_WDT_STS(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MCU_WDT_STS_MCU_WDT_STS                                         (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MCU_WDT_STS_MCU_WDT_STS(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a MCU_IO_MNGT_MISC:MCU_WDT_INTR_CFG
 *
 * MCU Watchdog Timer Interrupt Configuration register
 */


/**
 * \brief MCU Watchdog Timer Interrupt Enable register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:MCU_WDT_INTR_CFG:MCU_WDT_INTR_EN_REG
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MCU_WDT_INTR_EN_REG                                                (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x11))

/**
 * \brief
 * enable the watchdog timer interrupt propagation
 *
 * \details
 * 0: disable
 * 1: enable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MCU_WDT_INTR_EN_REG . MCU_WDT_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MCU_WDT_INTR_EN_REG_MCU_WDT_INTR_EN(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MCU_WDT_INTR_EN_REG_MCU_WDT_INTR_EN                             (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MCU_WDT_INTR_EN_REG_MCU_WDT_INTR_EN(x)                          (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a MCU_IO_MNGT_MISC:BIST0_REG
 *
 * BIST0 registers
 */


/**
 * \brief Software Memory BIST Start/Go Register
 *
 * \details
 * This register can be used to initiate BIST on specific memories
 * associated with POST0.
 * This register is meant to be used by only by the host or external test
 * entity.
 * MCU core must be put in reset if BIST is run on any of the BIST0
 * memories.
 * Multiple bits may be written as a one in this register but all bits must
 * be written concurrently.
 * Once all corresponding bits in the BIST_DONE register are read as set
 * the BIST_GO register must be written to zero.
 * Additional BIST tests may be performed only after all prior requested
 * tests are finished and prior BIST_GO bits are cleared.
 * In case of BIST timeout, the BIST_GO register should be written as zero
 * and the problematic block reset.
 *
 * Register: \a MCU_IO_MNGT_MISC:BIST0_REG:BIST0_GO
 */
#define LAN80XX_MCU_IO_MNGT_MISC_BIST0_GO                                                           (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x20))

/**
 * \brief
 * Setting this bit holds MCU core in reset.This bit must be set if any of
 * the BIST_GO bits are set.This bit must be cleared only after the
 * memories on which BIST is run have been initialized.Note: In order to
 * initialize the memories the BIST_GO bits must be cleared, however, this
 * bit must remain set.
 *
 * \details
 * 1 - Hold MCU core in reset
 * 0 - Bring MCU core out of reset
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_BIST0_GO . MCU_CORE_RESET
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_BIST0_GO_MCU_CORE_RESET(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_BIST0_GO_MCU_CORE_RESET                                         (LAN80XX_BIT(7))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_BIST0_GO_MCU_CORE_RESET(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,7,1))

/**
 * \brief
 * Setting this bit will initiate BIST on Mailbox RAM.This bit must be
 * cleared when associated DONE bit reads one.
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_BIST0_GO . MAILBOX_BIST_GO
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_BIST0_GO_MAILBOX_BIST_GO(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_BIST0_GO_MAILBOX_BIST_GO                                        (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_BIST0_GO_MAILBOX_BIST_GO(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Setting this bit will initiate BIST on MCU Data RAM (DRAM).This bit must
 * be cleared when associated DONE bit reads one.
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_BIST0_GO . DRAM_BIST_GO
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_BIST0_GO_DRAM_BIST_GO(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_BIST0_GO_DRAM_BIST_GO                                           (LAN80XX_BIT(2))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_BIST0_GO_DRAM_BIST_GO(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Setting this bit will initiate BIST on MCU Instruction RAM (IRAM).This
 * bit must be cleared when associated DONE bit reads one.
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_BIST0_GO . IRAM_BIST_GO
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_BIST0_GO_IRAM_BIST_GO(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_BIST0_GO_IRAM_BIST_GO                                           (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_BIST0_GO_IRAM_BIST_GO(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Setting this bit will initiate BIST on MCU Read Only Memory (ROM).This
 * bit must be cleared when associated DONE bit reads one.
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_BIST0_GO . ROM_BIST_GO
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_BIST0_GO_ROM_BIST_GO(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_BIST0_GO_ROM_BIST_GO                                            (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_BIST0_GO_ROM_BIST_GO(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief Memory BIST Done Status Register
 *
 * \details
 * This register is not updated when hardware based POST0 is run.
 *
 * Register: \a MCU_IO_MNGT_MISC:BIST0_REG:BIST0_STATUS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_BIST0_STATUS                                                       (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x21))

/**
 * \brief
 * BIST on Mailbox memory is done.Only valid if corresponding GO bit was
 * set.
 *
 * \details
 * 1 - BIST finished
 * 0 - BIST did not finish
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_BIST0_STATUS . MAILBOX_BIST_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_BIST0_STATUS_MAILBOX_BIST_DONE(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_BIST0_STATUS_MAILBOX_BIST_DONE                                  (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_BIST0_STATUS_MAILBOX_BIST_DONE(x)                               (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * BIST on DRAM is done.Only valid if corresponding GO bit was set.
 *
 * \details
 * 1 - BIST finished
 * 0 - BIST did not finish
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_BIST0_STATUS . DRAM_BIST_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_BIST0_STATUS_DRAM_BIST_DONE(x)                                  (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_BIST0_STATUS_DRAM_BIST_DONE                                     (LAN80XX_BIT(2))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_BIST0_STATUS_DRAM_BIST_DONE(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * BIST on IRAM is done.Only valid if corresponding GO bit was set.
 *
 * \details
 * 1 - BIST finished
 * 0 - BIST did not finish
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_BIST0_STATUS . IRAM_BIST_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_BIST0_STATUS_IRAM_BIST_DONE(x)                                  (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_BIST0_STATUS_IRAM_BIST_DONE                                     (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_BIST0_STATUS_IRAM_BIST_DONE(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * BIST on ROM is done.Only valid if corresponding GO bit was set.
 *
 * \details
 * 1 - BIST finished
 * 0 - BIST did not finish
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_BIST0_STATUS . ROM_BIST_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_BIST0_STATUS_ROM_BIST_DONE(x)                                   (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_BIST0_STATUS_ROM_BIST_DONE                                      (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_BIST0_STATUS_ROM_BIST_DONE(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief Memory BIST Result Register
 *
 * \details
 * This register is not updated when hardware based POST0 is run.
 *
 * Register: \a MCU_IO_MNGT_MISC:BIST0_REG:BIST0_RESULT
 */
#define LAN80XX_MCU_IO_MNGT_MISC_BIST0_RESULT                                                       (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x22))

/**
 * \brief
 * Mailbox memory BIST Result.Only valid if corresponding GO bit was set.
 *
 * \details
 * 1 - BIST pass
 * 0 - BIST fail
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_BIST0_RESULT . MAILBOX_BIST_RESULT
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_BIST0_RESULT_MAILBOX_BIST_RESULT(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_BIST0_RESULT_MAILBOX_BIST_RESULT                                (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_BIST0_RESULT_MAILBOX_BIST_RESULT(x)                             (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * DRAM BIST Result.Only valid if corresponding GO bit was set.
 *
 * \details
 * 1 - BIST pass
 * 0 - BIST fail
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_BIST0_RESULT . DRAM_BIST_RESULT
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_BIST0_RESULT_DRAM_BIST_RESULT(x)                                (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_BIST0_RESULT_DRAM_BIST_RESULT                                   (LAN80XX_BIT(2))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_BIST0_RESULT_DRAM_BIST_RESULT(x)                                (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * IRAM BIST Result.Only valid if corresponding GO bit was set.
 *
 * \details
 * 1 - BIST pass
 * 0 - BIST fail
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_BIST0_RESULT . IRAM_BIST_RESULT
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_BIST0_RESULT_IRAM_BIST_RESULT(x)                                (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_BIST0_RESULT_IRAM_BIST_RESULT                                   (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_BIST0_RESULT_IRAM_BIST_RESULT(x)                                (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * ROM BIST Result.Only valid if corresponding GO bit was set.
 *
 * \details
 * 1 - BIST pass
 * 0 - BIST fail
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_BIST0_RESULT . ROM_BIST_RESULT
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_BIST0_RESULT_ROM_BIST_RESULT(x)                                 (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_BIST0_RESULT_ROM_BIST_RESULT                                    (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_BIST0_RESULT_ROM_BIST_RESULT(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a MCU_IO_MNGT_MISC:POST0_REG
 *
 * POST0 registers
 */


/**
 * \brief POST0 Status Register
 *
 * \details
 * This register is cleared by any MCU reset.
 *
 * Register: \a MCU_IO_MNGT_MISC:POST0_REG:POST0_STATUS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_POST0_STATUS                                                       (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x40))

/**
 * \brief
 * Reflects state of BIST_BYPASS_STRAP.P0_BIST_STATUS and P0_BIST_RESULT
 * registers are meaningless if this bit is set.
 *
 * \details
 * 1 = BIST was bypassed during POST0
 * 0 = Normal BIST run during POST0
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST0_STATUS . P0_BIST_BYPASS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST0_STATUS_P0_BIST_BYPASS(x)                                  (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST0_STATUS_P0_BIST_BYPASS                                     (LAN80XX_BIT(7))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST0_STATUS_P0_BIST_BYPASS(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,7,1))

/**
 * \brief
 * POST0 Result.This bit has meaning only when P0_POST_DONE is set.
 *
 * \details
 * 1 = POST0 Passed. All memory BISTs passed or BIST was bypassed. RAMs
 * successfully initialized.
 * 0 = POST0 BIST or RAM initialization failed
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST0_STATUS . P0_POST_PASS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST0_STATUS_P0_POST_PASS(x)                                    (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST0_STATUS_P0_POST_PASS                                       (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST0_STATUS_P0_POST_PASS(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * POST0 done status.This bit must be set for other POST0 registers to have
 * any meaning.
 *
 * \details
 * 1 = POST0 finished. All memory BISTs are done or BIST was bypassed.
 * RAMs have been initialized.
 * 0 = POST0 is not finished.
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST0_STATUS . P0_POST_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST0_STATUS_P0_POST_DONE(x)                                    (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST0_STATUS_P0_POST_DONE                                       (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST0_STATUS_P0_POST_DONE(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief POST0 Memory BIST Done Status Register
 *
 * \details
 * This register is cleared by any MCU reset.
 *
 * Register: \a MCU_IO_MNGT_MISC:POST0_REG:P0_BIST_STATUS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_P0_BIST_STATUS                                                     (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x41))

/**
 * \brief
 * POST0 BIST Timeout
 *
 * \details
 * 1 - BIST timeout occurred on one of the memories
 * 0 - Normal BIST completion
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_P0_BIST_STATUS . P0_BIST_TO
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_P0_BIST_STATUS_P0_BIST_TO(x)                                    (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_P0_BIST_STATUS_P0_BIST_TO                                       (LAN80XX_BIT(7))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_P0_BIST_STATUS_P0_BIST_TO(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,7,1))

/**
 * \brief
 * BIST on Mailbox (MB) memory is done
 *
 * \details
 * 1 - BIST finished
 * 0 - BIST did not finish
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_P0_BIST_STATUS . P0_MB_BIST_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_P0_BIST_STATUS_P0_MB_BIST_DONE(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_P0_BIST_STATUS_P0_MB_BIST_DONE                                  (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_P0_BIST_STATUS_P0_MB_BIST_DONE(x)                               (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * BIST on DRAM is done
 *
 * \details
 * 1 - BIST finished
 * 0 - BIST did not finish
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_P0_BIST_STATUS . P0_DRAM_BIST_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_P0_BIST_STATUS_P0_DRAM_BIST_DONE(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_P0_BIST_STATUS_P0_DRAM_BIST_DONE                                (LAN80XX_BIT(2))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_P0_BIST_STATUS_P0_DRAM_BIST_DONE(x)                             (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * BIST on IRAM is done
 *
 * \details
 * 1 - BIST finished
 * 0 - BIST did not finish
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_P0_BIST_STATUS . P0_IRAM_BIST_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_P0_BIST_STATUS_P0_IRAM_BIST_DONE(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_P0_BIST_STATUS_P0_IRAM_BIST_DONE                                (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_P0_BIST_STATUS_P0_IRAM_BIST_DONE(x)                             (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * BIST on ROM is done
 *
 * \details
 * 1 - BIST finished
 * 0 - BIST did not finish
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_P0_BIST_STATUS . P0_ROM_BIST_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_P0_BIST_STATUS_P0_ROM_BIST_DONE(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_P0_BIST_STATUS_P0_ROM_BIST_DONE                                 (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_P0_BIST_STATUS_P0_ROM_BIST_DONE(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief POST0 Memory BIST Result Register
 *
 * \details
 * This register is cleared by any MCU reset.
 *
 * Register: \a MCU_IO_MNGT_MISC:POST0_REG:P0_BIST_RESULT
 */
#define LAN80XX_MCU_IO_MNGT_MISC_P0_BIST_RESULT                                                     (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x42))

/**
 * \brief
 * Mailbox (MB) memory BIST Result
 *
 * \details
 * 1 - BIST pass
 * 0 - BIST fail
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_P0_BIST_RESULT . P0_MB_BIST_RESULT
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_P0_BIST_RESULT_P0_MB_BIST_RESULT(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_P0_BIST_RESULT_P0_MB_BIST_RESULT                                (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_P0_BIST_RESULT_P0_MB_BIST_RESULT(x)                             (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * DRAM BIST Result
 *
 * \details
 * 1 - BIST pass
 * 0 - BIST fail
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_P0_BIST_RESULT . P0_DRAM_BIST_RESULT
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_P0_BIST_RESULT_P0_DRAM_BIST_RESULT(x)                           (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_P0_BIST_RESULT_P0_DRAM_BIST_RESULT                              (LAN80XX_BIT(2))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_P0_BIST_RESULT_P0_DRAM_BIST_RESULT(x)                           (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * IRAM BIST Result
 *
 * \details
 * 1 - BIST pass
 * 0 - BIST fail
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_P0_BIST_RESULT . P0_IRAM_BIST_RESULT
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_P0_BIST_RESULT_P0_IRAM_BIST_RESULT(x)                           (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_P0_BIST_RESULT_P0_IRAM_BIST_RESULT                              (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_P0_BIST_RESULT_P0_IRAM_BIST_RESULT(x)                           (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * ROM BIST Result
 *
 * \details
 * 1 - BIST pass
 * 0 - BIST fail
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_P0_BIST_RESULT . P0_ROM_BIST_RESULT
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_P0_BIST_RESULT_P0_ROM_BIST_RESULT(x)                            (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_P0_BIST_RESULT_P0_ROM_BIST_RESULT                               (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_P0_BIST_RESULT_P0_ROM_BIST_RESULT(x)                            (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief POST0 Memory Initialization Status Register
 *
 * \details
 * This register is cleared by any MCU reset.
 *
 * Register: \a MCU_IO_MNGT_MISC:POST0_REG:P0_INIT_STATUS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_P0_INIT_STATUS                                                     (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x43))

/**
 * \brief
 * POST0 Memory Initialization Timeout
 *
 * \details
 * 1 - INIT timeout occurred on one of the memories
 * 0 - Normal INIT completion
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_P0_INIT_STATUS . P0_INIT_TO
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_P0_INIT_STATUS_P0_INIT_TO(x)                                    (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_P0_INIT_STATUS_P0_INIT_TO                                       (LAN80XX_BIT(7))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_P0_INIT_STATUS_P0_INIT_TO(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,7,1))

/**
 * \brief
 * Mailbox (MB) memory initialization is done
 *
 * \details
 * 1 - INIT finished
 * 0 - INIT did not finish
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_P0_INIT_STATUS . P0_MB_INIT_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_P0_INIT_STATUS_P0_MB_INIT_DONE(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_P0_INIT_STATUS_P0_MB_INIT_DONE                                  (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_P0_INIT_STATUS_P0_MB_INIT_DONE(x)                               (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * DRAM initialization is done
 *
 * \details
 * 1 - INIT finished
 * 0 - INIT did not finish
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_P0_INIT_STATUS . P0_DRAM_INIT_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_P0_INIT_STATUS_P0_DRAM_INIT_DONE(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_P0_INIT_STATUS_P0_DRAM_INIT_DONE                                (LAN80XX_BIT(2))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_P0_INIT_STATUS_P0_DRAM_INIT_DONE(x)                             (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * IRAM initialization is done
 *
 * \details
 * 1 - INIT finished
 * 0 - INIT did not finish
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_P0_INIT_STATUS . P0_IRAM_INIT_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_P0_INIT_STATUS_P0_IRAM_INIT_DONE(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_P0_INIT_STATUS_P0_IRAM_INIT_DONE                                (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_P0_INIT_STATUS_P0_IRAM_INIT_DONE(x)                             (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * Register Group: \a MCU_IO_MNGT_MISC:POST1_REG
 *
 * POST1 registers
 */


/**
 * \brief POST1 Configuration and Status register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:POST1_REG:POST1_POST_STATUS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_POST1_POST_STATUS                                                  (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x80))

/**
 * \brief
 * Reflects state of BIST_BYPASS_STRAP.POST1_SLICE[0-3]_BIST_STATUS and
 * POST1_SLICE[0-3]_BIST_RESULT registers are meaningless if this bit is
 * set.
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_POST_STATUS . P1_BIST_BYPASS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_BIST_BYPASS(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_BIST_BYPASS                                (LAN80XX_BIT(15))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_BIST_BYPASS(x)                             (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 * A 1 indicates all slice 3 RAM BISTs pass or BIST was bypassed, RAM
 * initialization is done
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_POST_STATUS . P1_POST_SLICE3_PASS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_POST_SLICE3_PASS(x)                        (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_POST_SLICE3_PASS                           (LAN80XX_BIT(4))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_POST_SLICE3_PASS(x)                        (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * A 1 indicates all slice 2 RAM BISTs pass or BIST was bypassed, RAM
 * initialization is done
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_POST_STATUS . P1_POST_SLICE2_PASS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_POST_SLICE2_PASS(x)                        (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_POST_SLICE2_PASS                           (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_POST_SLICE2_PASS(x)                        (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * A 1 indicates all slice 1 RAM BISTs pass or BIST was bypassed, RAM
 * initialization is done
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_POST_STATUS . P1_POST_SLICE1_PASS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_POST_SLICE1_PASS(x)                        (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_POST_SLICE1_PASS                           (LAN80XX_BIT(2))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_POST_SLICE1_PASS(x)                        (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * A 1 indicates all slice 0 RAM BISTs pass or BIST was bypassed, RAM
 * initialization is done
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_POST_STATUS . P1_POST_SLICE0_PASS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_POST_SLICE0_PASS(x)                        (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_POST_SLICE0_PASS                           (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_POST_SLICE0_PASS(x)                        (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * A 1 indicates all RAM BISTs are done or BIST was bypassed, RAM
 * initialization is done
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_POST_STATUS . P1_POST_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_POST_DONE(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_POST_DONE                                  (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_POST_DONE(x)                               (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief Slice 0 BIST Status register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:POST1_REG:POST1_SLICE0_BIST_STATUS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE0_BIST_STATUS                                           (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x81))

/**
 * \brief
 * A 1 indicates the BIST of the slice timed out
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE0_BIST_STATUS . P1_SLICE0_BIST_TO
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_SLICE0_BIST_STATUS_P1_SLICE0_BIST_TO(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE0_BIST_STATUS_P1_SLICE0_BIST_TO                      (LAN80XX_BIT(15))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_SLICE0_BIST_STATUS_P1_SLICE0_BIST_TO(x)                   (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 * One bit per ram in the sliceA 1 indicates the BIST of the RAM is done
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE0_BIST_STATUS . P1_SLICE0_RAM_BIST_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_SLICE0_BIST_STATUS_P1_SLICE0_RAM_BIST_DONE(x)             (LAN80XX_ENCODE_BITFIELD(x,0,11))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE0_BIST_STATUS_P1_SLICE0_RAM_BIST_DONE                (LAN80XX_ENCODE_BITMASK(0,11))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_SLICE0_BIST_STATUS_P1_SLICE0_RAM_BIST_DONE(x)             (LAN80XX_EXTRACT_BITFIELD(x,0,11))


/**
 * \brief Slice 1 BIST Status register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:POST1_REG:POST1_SLICE1_BIST_STATUS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE1_BIST_STATUS                                           (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x82))

/**
 * \brief
 * A 1 indicates the BIST of the slice timed out
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE1_BIST_STATUS . P1_SLICE1_BIST_TO
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_SLICE1_BIST_STATUS_P1_SLICE1_BIST_TO(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE1_BIST_STATUS_P1_SLICE1_BIST_TO                      (LAN80XX_BIT(15))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_SLICE1_BIST_STATUS_P1_SLICE1_BIST_TO(x)                   (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 * One bit per ram in the sliceA 1 indicates the BIST of the RAM is done
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE1_BIST_STATUS . P1_SLICE1_RAM_BIST_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_SLICE1_BIST_STATUS_P1_SLICE1_RAM_BIST_DONE(x)             (LAN80XX_ENCODE_BITFIELD(x,0,11))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE1_BIST_STATUS_P1_SLICE1_RAM_BIST_DONE                (LAN80XX_ENCODE_BITMASK(0,11))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_SLICE1_BIST_STATUS_P1_SLICE1_RAM_BIST_DONE(x)             (LAN80XX_EXTRACT_BITFIELD(x,0,11))


/**
 * \brief Slice 2 BIST Status register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:POST1_REG:POST1_SLICE2_BIST_STATUS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE2_BIST_STATUS                                           (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x83))

/**
 * \brief
 * A 1 indicates the BIST of the slice timed out
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE2_BIST_STATUS . P1_SLICE2_BIST_TO
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_SLICE2_BIST_STATUS_P1_SLICE2_BIST_TO(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE2_BIST_STATUS_P1_SLICE2_BIST_TO                      (LAN80XX_BIT(15))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_SLICE2_BIST_STATUS_P1_SLICE2_BIST_TO(x)                   (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 * One bit per ram in the sliceA 1 indicates the BIST of the RAM is done
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE2_BIST_STATUS . P1_SLICE2_RAM_BIST_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_SLICE2_BIST_STATUS_P1_SLICE2_RAM_BIST_DONE(x)             (LAN80XX_ENCODE_BITFIELD(x,0,11))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE2_BIST_STATUS_P1_SLICE2_RAM_BIST_DONE                (LAN80XX_ENCODE_BITMASK(0,11))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_SLICE2_BIST_STATUS_P1_SLICE2_RAM_BIST_DONE(x)             (LAN80XX_EXTRACT_BITFIELD(x,0,11))


/**
 * \brief Slice 3 BIST Status register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:POST1_REG:POST1_SLICE3_BIST_STATUS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE3_BIST_STATUS                                           (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x84))

/**
 * \brief
 * A 1 indicates the BIST of the slice timed out
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE3_BIST_STATUS . P1_SLICE3_BIST_TO
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_SLICE3_BIST_STATUS_P1_SLICE3_BIST_TO(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE3_BIST_STATUS_P1_SLICE3_BIST_TO                      (LAN80XX_BIT(15))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_SLICE3_BIST_STATUS_P1_SLICE3_BIST_TO(x)                   (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 * One bit per ram in the sliceA 1 indicates the BIST of the RAM is done
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE3_BIST_STATUS . P1_SLICE3_RAM_BIST_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_SLICE3_BIST_STATUS_P1_SLICE3_RAM_BIST_DONE(x)             (LAN80XX_ENCODE_BITFIELD(x,0,11))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE3_BIST_STATUS_P1_SLICE3_RAM_BIST_DONE                (LAN80XX_ENCODE_BITMASK(0,11))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_SLICE3_BIST_STATUS_P1_SLICE3_RAM_BIST_DONE(x)             (LAN80XX_EXTRACT_BITFIELD(x,0,11))


/**
 * \brief Slice 0 BIST result register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:POST1_REG:POST1_SLICE0_BIST_RESULT
 */
#define LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE0_BIST_RESULT                                           (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x85))

/**
 * \brief
 * One bit per ram in the sliceA 1 indicates the BIST of the RAM is done
 * and pass
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE0_BIST_RESULT . P1_SLICE0_RAM_BIST_PASS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_SLICE0_BIST_RESULT_P1_SLICE0_RAM_BIST_PASS(x)             (LAN80XX_ENCODE_BITFIELD(x,0,11))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE0_BIST_RESULT_P1_SLICE0_RAM_BIST_PASS                (LAN80XX_ENCODE_BITMASK(0,11))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_SLICE0_BIST_RESULT_P1_SLICE0_RAM_BIST_PASS(x)             (LAN80XX_EXTRACT_BITFIELD(x,0,11))


/**
 * \brief Slice 1 BIST result register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:POST1_REG:POST1_SLICE1_BIST_RESULT
 */
#define LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE1_BIST_RESULT                                           (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x86))

/**
 * \brief
 * One bit per ram in the sliceA 1 indicates the BIST of the RAM is done
 * and pass
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE1_BIST_RESULT . P1_SLICE1_RAM_BIST_PASS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_SLICE1_BIST_RESULT_P1_SLICE1_RAM_BIST_PASS(x)             (LAN80XX_ENCODE_BITFIELD(x,0,11))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE1_BIST_RESULT_P1_SLICE1_RAM_BIST_PASS                (LAN80XX_ENCODE_BITMASK(0,11))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_SLICE1_BIST_RESULT_P1_SLICE1_RAM_BIST_PASS(x)             (LAN80XX_EXTRACT_BITFIELD(x,0,11))


/**
 * \brief Slice 2 BIST result register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:POST1_REG:POST1_SLICE2_BIST_RESULT
 */
#define LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE2_BIST_RESULT                                           (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x87))

/**
 * \brief
 * One bit per ram in the sliceA 1 indicates the BIST of the RAM is done
 * and pass
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE2_BIST_RESULT . P1_SLICE2_RAM_BIST_PASS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_SLICE2_BIST_RESULT_P1_SLICE2_RAM_BIST_PASS(x)             (LAN80XX_ENCODE_BITFIELD(x,0,11))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE2_BIST_RESULT_P1_SLICE2_RAM_BIST_PASS                (LAN80XX_ENCODE_BITMASK(0,11))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_SLICE2_BIST_RESULT_P1_SLICE2_RAM_BIST_PASS(x)             (LAN80XX_EXTRACT_BITFIELD(x,0,11))


/**
 * \brief Slice 3 BIST result register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:POST1_REG:POST1_SLICE3_BIST_RESULT
 */
#define LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE3_BIST_RESULT                                           (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x88))

/**
 * \brief
 * One bit per ram in the sliceA 1 indicates the BIST of the RAM is done
 * and pass
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE3_BIST_RESULT . P1_SLICE3_RAM_BIST_PASS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_SLICE3_BIST_RESULT_P1_SLICE3_RAM_BIST_PASS(x)             (LAN80XX_ENCODE_BITFIELD(x,0,11))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE3_BIST_RESULT_P1_SLICE3_RAM_BIST_PASS                (LAN80XX_ENCODE_BITMASK(0,11))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_SLICE3_BIST_RESULT_P1_SLICE3_RAM_BIST_PASS(x)             (LAN80XX_EXTRACT_BITFIELD(x,0,11))


/**
 * \brief Slice 0 BIST initialization status register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:POST1_REG:POST1_SLICE0_INIT_STATUS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE0_INIT_STATUS                                           (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x89))

/**
 * \brief
 * A 1 indicates the initialization for the slice timed out
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE0_INIT_STATUS . P1_SLICE0_INIT_TO
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_SLICE0_INIT_STATUS_P1_SLICE0_INIT_TO(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE0_INIT_STATUS_P1_SLICE0_INIT_TO                      (LAN80XX_BIT(15))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_SLICE0_INIT_STATUS_P1_SLICE0_INIT_TO(x)                   (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 * One bit per ram in the sliceA 1 indicates the initialization of the RAM
 * is done
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE0_INIT_STATUS . P1_SLICE0_RAM_INIT_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_SLICE0_INIT_STATUS_P1_SLICE0_RAM_INIT_DONE(x)             (LAN80XX_ENCODE_BITFIELD(x,0,11))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE0_INIT_STATUS_P1_SLICE0_RAM_INIT_DONE                (LAN80XX_ENCODE_BITMASK(0,11))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_SLICE0_INIT_STATUS_P1_SLICE0_RAM_INIT_DONE(x)             (LAN80XX_EXTRACT_BITFIELD(x,0,11))


/**
 * \brief Slice 1 BIST initialization status register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:POST1_REG:POST1_SLICE1_INIT_STATUS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE1_INIT_STATUS                                           (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x8a))

/**
 * \brief
 * A 1 indicates the initialization for the slice timed out
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE1_INIT_STATUS . P1_SLICE1_INIT_TO
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_SLICE1_INIT_STATUS_P1_SLICE1_INIT_TO(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE1_INIT_STATUS_P1_SLICE1_INIT_TO                      (LAN80XX_BIT(15))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_SLICE1_INIT_STATUS_P1_SLICE1_INIT_TO(x)                   (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 * One bit per ram in the sliceA 1 indicates the initialization of the RAM
 * is done
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE1_INIT_STATUS . P1_SLICE1_RAM_INIT_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_SLICE1_INIT_STATUS_P1_SLICE1_RAM_INIT_DONE(x)             (LAN80XX_ENCODE_BITFIELD(x,0,11))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE1_INIT_STATUS_P1_SLICE1_RAM_INIT_DONE                (LAN80XX_ENCODE_BITMASK(0,11))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_SLICE1_INIT_STATUS_P1_SLICE1_RAM_INIT_DONE(x)             (LAN80XX_EXTRACT_BITFIELD(x,0,11))


/**
 * \brief Slice 2 BIST initialization status register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:POST1_REG:POST1_SLICE2_INIT_STATUS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE2_INIT_STATUS                                           (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x8b))

/**
 * \brief
 * A 1 indicates the initialization for the slice timed out
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE2_INIT_STATUS . P1_SLICE2_INIT_TO
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_SLICE2_INIT_STATUS_P1_SLICE2_INIT_TO(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE2_INIT_STATUS_P1_SLICE2_INIT_TO                      (LAN80XX_BIT(15))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_SLICE2_INIT_STATUS_P1_SLICE2_INIT_TO(x)                   (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 * One bit per ram in the sliceA 1 indicates the initialization of the RAM
 * is done
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE2_INIT_STATUS . P1_SLICE2_RAM_INIT_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_SLICE2_INIT_STATUS_P1_SLICE2_RAM_INIT_DONE(x)             (LAN80XX_ENCODE_BITFIELD(x,0,11))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE2_INIT_STATUS_P1_SLICE2_RAM_INIT_DONE                (LAN80XX_ENCODE_BITMASK(0,11))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_SLICE2_INIT_STATUS_P1_SLICE2_RAM_INIT_DONE(x)             (LAN80XX_EXTRACT_BITFIELD(x,0,11))


/**
 * \brief Slice 3 BIST initialization status register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:POST1_REG:POST1_SLICE3_INIT_STATUS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE3_INIT_STATUS                                           (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x8c))

/**
 * \brief
 * A 1 indicates the initialization for the slice timed out
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE3_INIT_STATUS . P1_SLICE3_INIT_TO
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_SLICE3_INIT_STATUS_P1_SLICE3_INIT_TO(x)                   (LAN80XX_ENCODE_BITFIELD(!!(x),15,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE3_INIT_STATUS_P1_SLICE3_INIT_TO                      (LAN80XX_BIT(15))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_SLICE3_INIT_STATUS_P1_SLICE3_INIT_TO(x)                   (LAN80XX_EXTRACT_BITFIELD(x,15,1))

/**
 * \brief
 * One bit per ram in the sliceA 1 indicates the initialization of the RAM
 * is done
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_POST1_SLICE3_INIT_STATUS . P1_SLICE3_RAM_INIT_DONE
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_POST1_SLICE3_INIT_STATUS_P1_SLICE3_RAM_INIT_DONE(x)             (LAN80XX_ENCODE_BITFIELD(x,0,11))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE3_INIT_STATUS_P1_SLICE3_RAM_INIT_DONE                (LAN80XX_ENCODE_BITMASK(0,11))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_POST1_SLICE3_INIT_STATUS_P1_SLICE3_RAM_INIT_DONE(x)             (LAN80XX_EXTRACT_BITFIELD(x,0,11))

/**
 * Register Group: \a MCU_IO_MNGT_MISC:IRAM_ECC
 *
 * IRAM ECC registers
 */


/**
 * \brief IRAM ECC Control Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:IRAM_ECC:IRAM_ECC_CTL
 */
#define LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_CTL                                                       (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x100))

/**
 * \brief
 * Disable ECC decoder features
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_CTL . IRAM_ECC_EN_CLR
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_CTL_IRAM_ECC_EN_CLR(x)                                 (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_CTL_IRAM_ECC_EN_CLR                                    (LAN80XX_BIT(8))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_CTL_IRAM_ECC_EN_CLR(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * Reset error counters
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_CTL . IRAM_CNTRST
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_CTL_IRAM_CNTRST(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_CTL_IRAM_CNTRST                                        (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_CTL_IRAM_CNTRST(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Soft reset ECC controller core logic
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_CTL . IRAM_SWRST
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_CTL_IRAM_SWRST(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_CTL_IRAM_SWRST                                         (LAN80XX_BIT(2))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_CTL_IRAM_SWRST(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * initial SRAM with all 0s
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_CTL . IRAM_INIT
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_CTL_IRAM_INIT(x)                                       (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_CTL_IRAM_INIT                                          (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_CTL_IRAM_INIT(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Enable ECC decoder features
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_CTL . IRAM_ECC_EN_SET
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_CTL_IRAM_ECC_EN_SET(x)                                 (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_CTL_IRAM_ECC_EN_SET                                    (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_CTL_IRAM_ECC_EN_SET(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief IRAM ECC Status Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:IRAM_ECC:IRAM_ECC_SR
 */
#define LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_SR                                                        (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x101))

/**
 * \brief
 * SRAM initialization in progress
 *
 * \details
 * 1 = in progress
 * 0 = not in progress
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_SR . IRAM_INIT_BUSY
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_SR_IRAM_INIT_BUSY(x)                                   (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_SR_IRAM_INIT_BUSY                                      (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_SR_IRAM_INIT_BUSY(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * ECC decoder features are currently enabled
 *
 * \details
 * 1 = enabled
 * 0 = not enabled
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_SR . IRAM_ECC_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_SR_IRAM_ECC_EN(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_SR_IRAM_ECC_EN                                         (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_SR_IRAM_ECC_EN(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief IRAM ECC Initialization Done Interrupt Enable register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:IRAM_ECC:IRAM_ECC_INIT_DONE_INTR_EN
 */
#define LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_INIT_DONE_INTR_EN                                         (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x104))

/**
 * \brief
 * initialization done interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_INIT_DONE_INTR_EN . IRAM_INIT_DONE_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_INIT_DONE_INTR_EN_IRAM_INIT_DONE_INTR_EN(x)            (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_INIT_DONE_INTR_EN_IRAM_INIT_DONE_INTR_EN               (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_INIT_DONE_INTR_EN_IRAM_INIT_DONE_INTR_EN(x)            (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief IRAM ECC Initialization Done Interrupt Status register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:IRAM_ECC:IRAM_ECC_INIT_DONE_INTR_STS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_INIT_DONE_INTR_STS                                        (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x105))

/**
 * \brief
 * initialization done status bit
 *
 * \details
 * this bit is set by initialization done event, write 1 will clear this
 * bit
 * 0 = interrupt not pending
 * 1 = interrupt pending

 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_INIT_DONE_INTR_STS . IRAM_INIT_DONE_INTR_STICKY
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_INIT_DONE_INTR_STS_IRAM_INIT_DONE_INTR_STICKY(x)       (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_INIT_DONE_INTR_STS_IRAM_INIT_DONE_INTR_STICKY          (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_INIT_DONE_INTR_STS_IRAM_INIT_DONE_INTR_STICKY(x)       (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief IRAM ECC Interrupt Enable Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:IRAM_ECC:IRAM_ECC_INTR_EN
 */
#define LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_EN                                                   (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x106))

/**
 * \brief
 * Lane 3 interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_EN . IRAM_LN3_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_EN_IRAM_LN3_INTR_EN(x)                            (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_EN_IRAM_LN3_INTR_EN                               (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_EN_IRAM_LN3_INTR_EN(x)                            (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Lane 2 interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_EN . IRAM_LN2_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_EN_IRAM_LN2_INTR_EN(x)                            (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_EN_IRAM_LN2_INTR_EN                               (LAN80XX_BIT(2))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_EN_IRAM_LN2_INTR_EN(x)                            (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Lane 1 interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_EN . IRAM_LN1_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_EN_IRAM_LN1_INTR_EN(x)                            (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_EN_IRAM_LN1_INTR_EN                               (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_EN_IRAM_LN1_INTR_EN(x)                            (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Lane 0 interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_EN . IRAM_LN0_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_EN_IRAM_LN0_INTR_EN(x)                            (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_EN_IRAM_LN0_INTR_EN                               (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_EN_IRAM_LN0_INTR_EN(x)                            (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief IRAM ECC Interrupt Status Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:IRAM_ECC:IRAM_ECC_INTR_STS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_STS                                                  (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x107))

/**
 * \brief
 * Lane 3 interrupt status
 *
 * \details
 * 1 = interrupt is pending
 * 0 = interrupt is not pending
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_STS . IRAM_LN3_INTR_STS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_STS_IRAM_LN3_INTR_STS(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_STS_IRAM_LN3_INTR_STS                             (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_STS_IRAM_LN3_INTR_STS(x)                          (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Lane 2 interrupt status
 *
 * \details
 * 1 = interrupt is pending
 * 0 = interrupt is not pending
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_STS . IRAM_LN2_INTR_STS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_STS_IRAM_LN2_INTR_STS(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_STS_IRAM_LN2_INTR_STS                             (LAN80XX_BIT(2))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_STS_IRAM_LN2_INTR_STS(x)                          (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Lane 1 interrupt status
 *
 * \details
 * 1 = interrupt is pending
 * 0 = interrupt is not pending
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_STS . IRAM_LN1_INTR_STS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_STS_IRAM_LN1_INTR_STS(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_STS_IRAM_LN1_INTR_STS                             (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_STS_IRAM_LN1_INTR_STS(x)                          (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Lane 0 interrupt status
 *
 * \details
 * 1 = interrupt is pending
 * 0 = interrupt is not pending
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_STS . IRAM_LN0_INTR_STS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_STS_IRAM_LN0_INTR_STS(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_STS_IRAM_LN0_INTR_STS                             (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_INTR_STS_IRAM_LN0_INTR_STS(x)                          (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief IRAM ECC Lane Fault Configuration Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:IRAM_ECC:IRAM_ECC_LANE_FCR
 *
 * @param ri Register: IRAM_ECC_LANE_FCR (??), 0-3
 */
#define LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_FCR(ri)                                              (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x110 + (ri)))

/**
 * \brief
 * Select double bit or single bit fault injection
 *
 * \details
 * if corresponding IRAM_LN_FAULT_EN is set
 * 1 = inject double bit fault
 * 0 = inject single bit fault
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_FCR . IRAM_FAULT_DBL
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_FCR_IRAM_FAULT_DBL(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_FCR_IRAM_FAULT_DBL                                (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_FCR_IRAM_FAULT_DBL(x)                             (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * enable fault injection controller
 *
 * \details
 * 1 = enabled
 * 0 = not enabled
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_FCR . IRAM_FAULT_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_FCR_IRAM_FAULT_EN(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_FCR_IRAM_FAULT_EN                                 (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_FCR_IRAM_FAULT_EN(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief IRAM ECC Lane Error Address Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:IRAM_ECC:IRAM_ECC_LANE_EADDR
 *
 * @param ri Register: IRAM_ECC_LANE_EADDR (??), 0-3
 */
#define LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_EADDR(ri)                                            (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x114 + (ri)))

/**
 * \brief
 * address of last error (sec or ded) occurred
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_EADDR . IRAM_ERR_ADDR
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_EADDR_IRAM_ERR_ADDR(x)                            (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_EADDR_IRAM_ERR_ADDR                               (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_EADDR_IRAM_ERR_ADDR(x)                            (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief IRAM ECC Lane Error Data Pointer Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:IRAM_ECC:IRAM_ECC_LANE_EDPTR
 *
 * @param ri Register: IRAM_ECC_LANE_EDPTR (??), 0-3
 */
#define LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_EDPTR(ri)                                            (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x115 + (ri)))

/**
 * \brief
 * bit number of corrected bit, read back 0 if DED.
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_EDPTR . IRAM_ERR_DPTR
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_EDPTR_IRAM_ERR_DPTR(x)                            (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_EDPTR_IRAM_ERR_DPTR                               (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_EDPTR_IRAM_ERR_DPTR(x)                            (LAN80XX_EXTRACT_BITFIELD(x,0,4))


/**
 * \brief IRAM ECC Lane SEC Count Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:IRAM_ECC:IRAM_ECC_LANE_SCNT
 *
 * @param ri Register: IRAM_ECC_LANE_SCNT (??), 0-3
 */
#define LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_SCNT(ri)                                             (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x116 + (ri)))

/**
 * \brief
 * number of single bit errors.this counter can be cleared by IRAM_SWRST or
 * IRAM_CNTRST
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_SCNT . IRAM_SEC_CNT
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_SCNT_IRAM_SEC_CNT(x)                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_SCNT_IRAM_SEC_CNT                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_SCNT_IRAM_SEC_CNT(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief IRAM ECC Lane DED Count Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:IRAM_ECC:IRAM_ECC_LANE_DCNT
 *
 * @param ri Register: IRAM_ECC_LANE_DCNT (??), 0-3
 */
#define LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_DCNT(ri)                                             (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x117 + (ri)))

/**
 * \brief
 * number of double bit errors.this counter can be cleared by IRAM_SWRST or
 * IRAM_CNTRST
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_DCNT . IRAM_DED_CNT
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_DCNT_IRAM_DED_CNT(x)                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_DCNT_IRAM_DED_CNT                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_DCNT_IRAM_DED_CNT(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief IRAM ECC Lane Interrupt Enable Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:IRAM_ECC:IRAM_ECC_LANE_INTR_EN
 *
 * @param ri Register: IRAM_ECC_LANE_INTR_EN (??), 0-3
 */
#define LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_EN(ri)                                          (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x118 + (ri)))

/**
 * \brief
 * fault read interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_EN . IRAM_FAULT_READ_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_EN_IRAM_FAULT_READ_INTR_EN(x)                (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_EN_IRAM_FAULT_READ_INTR_EN                   (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_EN_IRAM_FAULT_READ_INTR_EN(x)                (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Double Error Detection interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_EN . IRAM_DED_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_EN_IRAM_DED_INTR_EN(x)                       (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_EN_IRAM_DED_INTR_EN                          (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_EN_IRAM_DED_INTR_EN(x)                       (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Single Error Correction interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_EN . IRAM_SEC_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_EN_IRAM_SEC_INTR_EN(x)                       (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_EN_IRAM_SEC_INTR_EN                          (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_EN_IRAM_SEC_INTR_EN(x)                       (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief IRAM ECC Lane Interrupt Status Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:IRAM_ECC:IRAM_ECC_LANE_INTR_STS
 *
 * @param ri Register: IRAM_ECC_LANE_INTR_STS (??), 0-3
 */
#define LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_STS(ri)                                         (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x119 + (ri)))

/**
 * \brief
 * fault read interrupt status
 *
 * \details
 * this bit is set by fault read event, write 1 will clear this bit
 * 1 = interrupt is pending
 * 0 = no interrupt is pending
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_STS . IRAM_FAULT_READ_INTR_STICKY
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_STS_IRAM_FAULT_READ_INTR_STICKY(x)           (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_STS_IRAM_FAULT_READ_INTR_STICKY              (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_STS_IRAM_FAULT_READ_INTR_STICKY(x)           (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Double Error Detection interrupt status
 *
 * \details
 * this bit is set by double-bit detect event, write 1 will clear this bit
 * 1 = interrupt is pending
 * 0 = no interrupt is pending
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_STS . IRAM_DED_INTR_STICKY
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_STS_IRAM_DED_INTR_STICKY(x)                  (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_STS_IRAM_DED_INTR_STICKY                     (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_STS_IRAM_DED_INTR_STICKY(x)                  (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Single Error Correction interrupt status
 *
 * \details
 * this bit is set by single-bit error event, write 1 will clear this bit
 * 1 = interrupt is pending
 * 0 = no interrupt is pending
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_STS . IRAM_SEC_INTR_STICKY
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_STS_IRAM_SEC_INTR_STICKY(x)                  (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_STS_IRAM_SEC_INTR_STICKY                     (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_INTR_STS_IRAM_SEC_INTR_STICKY(x)                  (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief IRAM ECC Lane Fault Address Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:IRAM_ECC:IRAM_ECC_LANE_FADDR
 *
 * @param ri Register: IRAM_ECC_LANE_FADDR (??), 0-3
 */
#define LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_FADDR(ri)                                            (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x11c + (ri)))

/**
 * \brief
 * the address to inject the fault
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_FADDR . IRAM_FAULT_ADDR
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_FADDR_IRAM_FAULT_ADDR(x)                          (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_FADDR_IRAM_FAULT_ADDR                             (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_FADDR_IRAM_FAULT_ADDR(x)                          (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief IRAM ECC Lane Fault Data Pointer Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:IRAM_ECC:IRAM_ECC_LANE_FDPTR
 *
 * @param ri Register: IRAM_ECC_LANE_FDPTR (??), 0-3
 */
#define LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_FDPTR(ri)                                            (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x11d + (ri)))

/**
 * \brief
 * the bit number to inject the fault
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_FDPTR . IRAM_FAULT_DPTR
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_FDPTR_IRAM_FAULT_DPTR(x)                          (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_FDPTR_IRAM_FAULT_DPTR                             (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_IRAM_ECC_LANE_FDPTR_IRAM_FAULT_DPTR(x)                          (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * Register Group: \a MCU_IO_MNGT_MISC:DRAM_ECC
 *
 * DRAM ECC registers
 */


/**
 * \brief DRAM ECC Control Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:DRAM_ECC:DRAM_ECC_CTL
 */
#define LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_CTL                                                       (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x150))

/**
 * \brief
 * Disable ECC decoder features
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_CTL . DRAM_ECC_EN_CLR
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_CTL_DRAM_ECC_EN_CLR(x)                                 (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_CTL_DRAM_ECC_EN_CLR                                    (LAN80XX_BIT(8))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_CTL_DRAM_ECC_EN_CLR(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * Reset error counters
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_CTL . DRAM_CNTRST
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_CTL_DRAM_CNTRST(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_CTL_DRAM_CNTRST                                        (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_CTL_DRAM_CNTRST(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Soft reset ECC controller core logic
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_CTL . DRAM_SWRST
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_CTL_DRAM_SWRST(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_CTL_DRAM_SWRST                                         (LAN80XX_BIT(2))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_CTL_DRAM_SWRST(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * initial SRAM with all 0s
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_CTL . DRAM_INIT
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_CTL_DRAM_INIT(x)                                       (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_CTL_DRAM_INIT                                          (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_CTL_DRAM_INIT(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Enable ECC decoder features
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_CTL . DRAM_ECC_EN_SET
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_CTL_DRAM_ECC_EN_SET(x)                                 (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_CTL_DRAM_ECC_EN_SET                                    (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_CTL_DRAM_ECC_EN_SET(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief DRAM ECC Status Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:DRAM_ECC:DRAM_ECC_SR
 */
#define LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_SR                                                        (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x151))

/**
 * \brief
 * SRAM initialization in progress
 *
 * \details
 * 1 = in progress
 * 0 = not in progress
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_SR . DRAM_INIT_BUSY
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_SR_DRAM_INIT_BUSY(x)                                   (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_SR_DRAM_INIT_BUSY                                      (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_SR_DRAM_INIT_BUSY(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * ECC decoder features are currently enabled
 *
 * \details
 * 1 = enabled
 * 0 = not enabled
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_SR . DRAM_ECC_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_SR_DRAM_ECC_EN(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_SR_DRAM_ECC_EN                                         (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_SR_DRAM_ECC_EN(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief DRAM ECC Initialization Done Interrupt Enable register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:DRAM_ECC:DRAM_ECC_INIT_DONE_INTR_EN
 */
#define LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_INIT_DONE_INTR_EN                                         (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x154))

/**
 * \brief
 * initialization done interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_INIT_DONE_INTR_EN . DRAM_INIT_DONE_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_INIT_DONE_INTR_EN_DRAM_INIT_DONE_INTR_EN(x)            (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_INIT_DONE_INTR_EN_DRAM_INIT_DONE_INTR_EN               (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_INIT_DONE_INTR_EN_DRAM_INIT_DONE_INTR_EN(x)            (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief DRAM ECC Initialization Done Interrupt Status register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:DRAM_ECC:DRAM_ECC_INIT_DONE_INTR_STS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_INIT_DONE_INTR_STS                                        (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x155))

/**
 * \brief
 * initialization done status bit
 *
 * \details
 * this bit is set by initialization done event, write 1 will clear this
 * bit
 * 0 = interrupt not pending
 * 1 = interrupt pending

 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_INIT_DONE_INTR_STS . DRAM_INIT_DONE_INTR_STICKY
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_INIT_DONE_INTR_STS_DRAM_INIT_DONE_INTR_STICKY(x)       (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_INIT_DONE_INTR_STS_DRAM_INIT_DONE_INTR_STICKY          (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_INIT_DONE_INTR_STS_DRAM_INIT_DONE_INTR_STICKY(x)       (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief DRAM ECC Interrupt Enable Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:DRAM_ECC:DRAM_ECC_INTR_EN
 */
#define LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_EN                                                   (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x156))

/**
 * \brief
 * Lane 3 interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_EN . DRAM_LN3_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_EN_DRAM_LN3_INTR_EN(x)                            (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_EN_DRAM_LN3_INTR_EN                               (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_EN_DRAM_LN3_INTR_EN(x)                            (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Lane 2 interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_EN . DRAM_LN2_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_EN_DRAM_LN2_INTR_EN(x)                            (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_EN_DRAM_LN2_INTR_EN                               (LAN80XX_BIT(2))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_EN_DRAM_LN2_INTR_EN(x)                            (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Lane 1 interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_EN . DRAM_LN1_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_EN_DRAM_LN1_INTR_EN(x)                            (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_EN_DRAM_LN1_INTR_EN                               (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_EN_DRAM_LN1_INTR_EN(x)                            (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Lane 0 interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_EN . DRAM_LN0_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_EN_DRAM_LN0_INTR_EN(x)                            (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_EN_DRAM_LN0_INTR_EN                               (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_EN_DRAM_LN0_INTR_EN(x)                            (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief DRAM ECC Interrupt Status Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:DRAM_ECC:DRAM_ECC_INTR_STS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_STS                                                  (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x157))

/**
 * \brief
 * Lane 3 interrupt status
 *
 * \details
 * 1 = interrupt is pending
 * 0 = interrupt is not pending
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_STS . DRAM_LN3_INTR_STS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_STS_DRAM_LN3_INTR_STS(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_STS_DRAM_LN3_INTR_STS                             (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_STS_DRAM_LN3_INTR_STS(x)                          (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Lane 2 interrupt status
 *
 * \details
 * 1 = interrupt is pending
 * 0 = interrupt is not pending
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_STS . DRAM_LN2_INTR_STS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_STS_DRAM_LN2_INTR_STS(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_STS_DRAM_LN2_INTR_STS                             (LAN80XX_BIT(2))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_STS_DRAM_LN2_INTR_STS(x)                          (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Lane 1 interrupt status
 *
 * \details
 * 1 = interrupt is pending
 * 0 = interrupt is not pending
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_STS . DRAM_LN1_INTR_STS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_STS_DRAM_LN1_INTR_STS(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_STS_DRAM_LN1_INTR_STS                             (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_STS_DRAM_LN1_INTR_STS(x)                          (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Lane 0 interrupt status
 *
 * \details
 * 1 = interrupt is pending
 * 0 = interrupt is not pending
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_STS . DRAM_LN0_INTR_STS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_STS_DRAM_LN0_INTR_STS(x)                          (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_STS_DRAM_LN0_INTR_STS                             (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_INTR_STS_DRAM_LN0_INTR_STS(x)                          (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief DRAM ECC Lane Fault Configuration Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:DRAM_ECC:DRAM_ECC_LANE_FCR
 *
 * @param ri Register: DRAM_ECC_LANE_FCR (??), 0-3
 */
#define LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_FCR(ri)                                              (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x160 + (ri)))

/**
 * \brief
 * Select double bit or single bit fault injection
 *
 * \details
 * if corresponding DRAM_LN_FAULT_EN is set
 * 1 = inject double bit fault
 * 0 = inject single bit fault
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_FCR . DRAM_FAULT_DBL
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_FCR_DRAM_FAULT_DBL(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_FCR_DRAM_FAULT_DBL                                (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_FCR_DRAM_FAULT_DBL(x)                             (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * enable fault injection controller
 *
 * \details
 * 1 = enabled
 * 0 = not enabled
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_FCR . DRAM_FAULT_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_FCR_DRAM_FAULT_EN(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_FCR_DRAM_FAULT_EN                                 (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_FCR_DRAM_FAULT_EN(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief DRAM ECC Lane Error Address Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:DRAM_ECC:DRAM_ECC_LANE_EADDR
 *
 * @param ri Register: DRAM_ECC_LANE_EADDR (??), 0-3
 */
#define LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_EADDR(ri)                                            (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x164 + (ri)))

/**
 * \brief
 * address of last error (sec or ded) occurred
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_EADDR . DRAM_ERR_ADDR
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_EADDR_DRAM_ERR_ADDR(x)                            (LAN80XX_ENCODE_BITFIELD(x,0,14))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_EADDR_DRAM_ERR_ADDR                               (LAN80XX_ENCODE_BITMASK(0,14))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_EADDR_DRAM_ERR_ADDR(x)                            (LAN80XX_EXTRACT_BITFIELD(x,0,14))


/**
 * \brief DRAM ECC Lane Error Data Pointer Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:DRAM_ECC:DRAM_ECC_LANE_EDPTR
 *
 * @param ri Register: DRAM_ECC_LANE_EDPTR (??), 0-3
 */
#define LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_EDPTR(ri)                                            (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x165 + (ri)))

/**
 * \brief
 * bit number of corrected bit, read back 0 if DED.
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_EDPTR . DRAM_ERR_DPTR
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_EDPTR_DRAM_ERR_DPTR(x)                            (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_EDPTR_DRAM_ERR_DPTR                               (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_EDPTR_DRAM_ERR_DPTR(x)                            (LAN80XX_EXTRACT_BITFIELD(x,0,4))


/**
 * \brief DRAM ECC Lane SEC Count Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:DRAM_ECC:DRAM_ECC_LANE_SCNT
 *
 * @param ri Register: DRAM_ECC_LANE_SCNT (??), 0-3
 */
#define LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_SCNT(ri)                                             (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x166 + (ri)))

/**
 * \brief
 * number of single bit errors.this counter can be cleared by DRAM_SWRST or
 * DRAM_CNTRST
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_SCNT . DRAM_SEC_CNT
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_SCNT_DRAM_SEC_CNT(x)                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_SCNT_DRAM_SEC_CNT                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_SCNT_DRAM_SEC_CNT(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief DRAM ECC Lane DED Count Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:DRAM_ECC:DRAM_ECC_LANE_DCNT
 *
 * @param ri Register: DRAM_ECC_LANE_DCNT (??), 0-3
 */
#define LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_DCNT(ri)                                             (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x167 + (ri)))

/**
 * \brief
 * number of double bit errors.this counter can be cleared by DRAM_SWRST or
 * DRAM_CNTRST
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_DCNT . DRAM_DED_CNT
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_DCNT_DRAM_DED_CNT(x)                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_DCNT_DRAM_DED_CNT                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_DCNT_DRAM_DED_CNT(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief DRAM ECC Lane Interrupt Enable Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:DRAM_ECC:DRAM_ECC_LANE_INTR_EN
 *
 * @param ri Register: DRAM_ECC_LANE_INTR_EN (??), 0-3
 */
#define LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_EN(ri)                                          (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x168 + (ri)))

/**
 * \brief
 * fault read interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_EN . DRAM_FAULT_READ_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_EN_DRAM_FAULT_READ_INTR_EN(x)                (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_EN_DRAM_FAULT_READ_INTR_EN                   (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_EN_DRAM_FAULT_READ_INTR_EN(x)                (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Double Error Detection interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_EN . DRAM_DED_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_EN_DRAM_DED_INTR_EN(x)                       (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_EN_DRAM_DED_INTR_EN                          (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_EN_DRAM_DED_INTR_EN(x)                       (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Single Error Correction interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_EN . DRAM_SEC_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_EN_DRAM_SEC_INTR_EN(x)                       (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_EN_DRAM_SEC_INTR_EN                          (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_EN_DRAM_SEC_INTR_EN(x)                       (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief DRAM ECC Lane Interrupt Status Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:DRAM_ECC:DRAM_ECC_LANE_INTR_STS
 *
 * @param ri Register: DRAM_ECC_LANE_INTR_STS (??), 0-3
 */
#define LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_STS(ri)                                         (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x169 + (ri)))

/**
 * \brief
 * fault read interrupt status
 *
 * \details
 * this bit is set by fault read event, write 1 will clear this bit
 * 1 = interrupt is pending
 * 0 = no interrupt is pending
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_STS . DRAM_FAULT_READ_INTR_STICKY
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_STS_DRAM_FAULT_READ_INTR_STICKY(x)           (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_STS_DRAM_FAULT_READ_INTR_STICKY              (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_STS_DRAM_FAULT_READ_INTR_STICKY(x)           (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Double Error Detection interrupt status
 *
 * \details
 * this bit is set by double-bit detect event, write 1 will clear this bit
 * 1 = interrupt is pending
 * 0 = no interrupt is pending
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_STS . DRAM_DED_INTR_STICKY
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_STS_DRAM_DED_INTR_STICKY(x)                  (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_STS_DRAM_DED_INTR_STICKY                     (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_STS_DRAM_DED_INTR_STICKY(x)                  (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Single Error Correction interrupt status
 *
 * \details
 * this bit is set by single-bit error event, write 1 will clear this bit
 * 1 = interrupt is pending
 * 0 = no interrupt is pending
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_STS . DRAM_SEC_INTR_STICKY
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_STS_DRAM_SEC_INTR_STICKY(x)                  (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_STS_DRAM_SEC_INTR_STICKY                     (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_INTR_STS_DRAM_SEC_INTR_STICKY(x)                  (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief DRAM ECC Lane Fault Address Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:DRAM_ECC:DRAM_ECC_LANE_FADDR
 *
 * @param ri Register: DRAM_ECC_LANE_FADDR (??), 0-3
 */
#define LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_FADDR(ri)                                            (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x16c + (ri)))

/**
 * \brief
 * the address to inject the fault
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_FADDR . DRAM_FAULT_ADDR
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_FADDR_DRAM_FAULT_ADDR(x)                          (LAN80XX_ENCODE_BITFIELD(x,0,14))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_FADDR_DRAM_FAULT_ADDR                             (LAN80XX_ENCODE_BITMASK(0,14))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_FADDR_DRAM_FAULT_ADDR(x)                          (LAN80XX_EXTRACT_BITFIELD(x,0,14))


/**
 * \brief DRAM ECC Lane Fault Data Pointer Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:DRAM_ECC:DRAM_ECC_LANE_FDPTR
 *
 * @param ri Register: DRAM_ECC_LANE_FDPTR (??), 0-3
 */
#define LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_FDPTR(ri)                                            (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x16d + (ri)))

/**
 * \brief
 * the bit number to inject the fault
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_FDPTR . DRAM_FAULT_DPTR
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_FDPTR_DRAM_FAULT_DPTR(x)                          (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_FDPTR_DRAM_FAULT_DPTR                             (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_DRAM_ECC_LANE_FDPTR_DRAM_FAULT_DPTR(x)                          (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * Register Group: \a MCU_IO_MNGT_MISC:MBOX_ECC
 *
 * MBOX ECC registers
 */


/**
 * \brief MBOX ECC Control Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:MBOX_ECC:MBOX_ECC_CTL
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_CTL                                                       (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1a0))

/**
 * \brief
 * Disable ECC decoder features
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_CTL . MBOX_ECC_EN_CLR
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_CTL_MBOX_ECC_EN_CLR(x)                                 (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_CTL_MBOX_ECC_EN_CLR                                    (LAN80XX_BIT(8))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_CTL_MBOX_ECC_EN_CLR(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * Reset error counters
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_CTL . MBOX_CNTRST
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_CTL_MBOX_CNTRST(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_CTL_MBOX_CNTRST                                        (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_CTL_MBOX_CNTRST(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Soft reset ECC controller core logic
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_CTL . MBOX_SWRST
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_CTL_MBOX_SWRST(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_CTL_MBOX_SWRST                                         (LAN80XX_BIT(2))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_CTL_MBOX_SWRST(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * initial SRAM with all 0s
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_CTL . MBOX_INIT
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_CTL_MBOX_INIT(x)                                       (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_CTL_MBOX_INIT                                          (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_CTL_MBOX_INIT(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Enable ECC decoder features
 *
 * \details
 * Write 1 cause event
 * Write 0  no effect
 * always read 0
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_CTL . MBOX_ECC_EN_SET
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_CTL_MBOX_ECC_EN_SET(x)                                 (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_CTL_MBOX_ECC_EN_SET                                    (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_CTL_MBOX_ECC_EN_SET(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief MBOX ECC Status Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:MBOX_ECC:MBOX_ECC_SR
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_SR                                                        (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1a1))

/**
 * \brief
 * SRAM initialization in progress
 *
 * \details
 * 1 = in progress
 * 0 = not in progress
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_SR . MBOX_INIT_BUSY
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_SR_MBOX_INIT_BUSY(x)                                   (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_SR_MBOX_INIT_BUSY                                      (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_SR_MBOX_INIT_BUSY(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * ECC decoder features are currently enabled
 *
 * \details
 * 1 = enabled
 * 0 = not enabled
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_SR . MBOX_ECC_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_SR_MBOX_ECC_EN(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_SR_MBOX_ECC_EN                                         (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_SR_MBOX_ECC_EN(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief MBOX ECC Initialization Done Interrupt Enable register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:MBOX_ECC:MBOX_ECC_INIT_DONE_INTR_EN
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_INIT_DONE_INTR_EN                                         (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1a4))

/**
 * \brief
 * initialization done interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_INIT_DONE_INTR_EN . MBOX_INIT_DONE_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_INIT_DONE_INTR_EN_MBOX_INIT_DONE_INTR_EN(x)            (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_INIT_DONE_INTR_EN_MBOX_INIT_DONE_INTR_EN               (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_INIT_DONE_INTR_EN_MBOX_INIT_DONE_INTR_EN(x)            (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief MBOX ECC Initialization Done Interrupt Status register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:MBOX_ECC:MBOX_ECC_INIT_DONE_INTR_STS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_INIT_DONE_INTR_STS                                        (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1a5))

/**
 * \brief
 * initialization done status bit
 *
 * \details
 * this bit is set by initialization done event, write 1 will clear this
 * bit
 * 0 = interrupt not pending
 * 1 = interrupt pending

 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_INIT_DONE_INTR_STS . MBOX_INIT_DONE_INTR_STICKY
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_INIT_DONE_INTR_STS_MBOX_INIT_DONE_INTR_STICKY(x)       (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_INIT_DONE_INTR_STS_MBOX_INIT_DONE_INTR_STICKY          (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_INIT_DONE_INTR_STS_MBOX_INIT_DONE_INTR_STICKY(x)       (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief MBOX ECC Fault Configuration Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:MBOX_ECC:MBOX_ECC_FCR
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_FCR                                                       (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1b0))

/**
 * \brief
 * Select double bit or single bit fault injection
 *
 * \details
 * if corresponding MBOX_LN_FAULT_EN is set
 * 1 = inject double bit fault
 * 0 = inject single bit fault
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_FCR . MBOX_FAULT_DBL
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_FCR_MBOX_FAULT_DBL(x)                                  (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_FCR_MBOX_FAULT_DBL                                     (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_FCR_MBOX_FAULT_DBL(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * enable fault injection controller
 *
 * \details
 * 1 = enabled
 * 0 = not enabled
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_FCR . MBOX_FAULT_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_FCR_MBOX_FAULT_EN(x)                                   (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_FCR_MBOX_FAULT_EN                                      (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_FCR_MBOX_FAULT_EN(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief MBOX ECC Error Address Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:MBOX_ECC:MBOX_ECC_EADDR
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_EADDR                                                     (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1b4))

/**
 * \brief
 * address of last error (sec or ded) occurred
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_EADDR . MBOX_ERR_ADDR
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_EADDR_MBOX_ERR_ADDR(x)                                 (LAN80XX_ENCODE_BITFIELD(x,0,9))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_EADDR_MBOX_ERR_ADDR                                    (LAN80XX_ENCODE_BITMASK(0,9))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_EADDR_MBOX_ERR_ADDR(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,0,9))


/**
 * \brief MBOX ECC Error Data Pointer Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:MBOX_ECC:MBOX_ECC_EDPTR
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_EDPTR                                                     (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1b5))

/**
 * \brief
 * bit number of corrected bit, read back 0 if DED.
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_EDPTR . MBOX_ERR_DPTR
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_EDPTR_MBOX_ERR_DPTR(x)                                 (LAN80XX_ENCODE_BITFIELD(x,0,6))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_EDPTR_MBOX_ERR_DPTR                                    (LAN80XX_ENCODE_BITMASK(0,6))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_EDPTR_MBOX_ERR_DPTR(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,0,6))


/**
 * \brief MBOX ECC SEC Count Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:MBOX_ECC:MBOX_ECC_SCNT
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_SCNT                                                      (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1b6))

/**
 * \brief
 * number of single bit errors.this counter can be cleared by MBOX_SWRST or
 * MBOX_CNTRST
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_SCNT . MBOX_SEC_CNT
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_SCNT_MBOX_SEC_CNT(x)                                   (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_SCNT_MBOX_SEC_CNT                                      (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_SCNT_MBOX_SEC_CNT(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief MBOX ECC DED Count Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:MBOX_ECC:MBOX_ECC_DCNT
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_DCNT                                                      (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1b7))

/**
 * \brief
 * number of double bit errors.this counter can be cleared by MBOX_SWRST or
 * MBOX_CNTRST
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_DCNT . MBOX_DED_CNT
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_DCNT_MBOX_DED_CNT(x)                                   (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_DCNT_MBOX_DED_CNT                                      (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_DCNT_MBOX_DED_CNT(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief MBOX ECC Interrupt Enable Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:MBOX_ECC:MBOX_ECC_INTR_EN
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_EN                                                   (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1b8))

/**
 * \brief
 * fault read interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_EN . MBOX_FAULT_READ_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_EN_MBOX_FAULT_READ_INTR_EN(x)                     (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_EN_MBOX_FAULT_READ_INTR_EN                        (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_EN_MBOX_FAULT_READ_INTR_EN(x)                     (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Double Error Detection interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_EN . MBOX_DED_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_EN_MBOX_DED_INTR_EN(x)                            (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_EN_MBOX_DED_INTR_EN                               (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_EN_MBOX_DED_INTR_EN(x)                            (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Single Error Correction interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_EN . MBOX_SEC_INTR_EN
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_EN_MBOX_SEC_INTR_EN(x)                            (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_EN_MBOX_SEC_INTR_EN                               (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_EN_MBOX_SEC_INTR_EN(x)                            (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief MBOX ECC Interrupt Status Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:MBOX_ECC:MBOX_ECC_INTR_STS
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_STS                                                  (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1b9))

/**
 * \brief
 * fault read interrupt status
 *
 * \details
 * this bit is set by fault read event, write 1 will clear this bit
 * 1 = interrupt is pending
 * 0 = no interrupt is pending
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_STS . MBOX_FAULT_READ_INTR_STICKY
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_STS_MBOX_FAULT_READ_INTR_STICKY(x)                (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_STS_MBOX_FAULT_READ_INTR_STICKY                   (LAN80XX_BIT(3))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_STS_MBOX_FAULT_READ_INTR_STICKY(x)                (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Double Error Detection interrupt status
 *
 * \details
 * this bit is set by double-bit detect event, write 1 will clear this bit
 * 1 = interrupt is pending
 * 0 = no interrupt is pending
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_STS . MBOX_DED_INTR_STICKY
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_STS_MBOX_DED_INTR_STICKY(x)                       (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_STS_MBOX_DED_INTR_STICKY                          (LAN80XX_BIT(1))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_STS_MBOX_DED_INTR_STICKY(x)                       (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Single Error Correction interrupt status
 *
 * \details
 * this bit is set by single-bit error event, write 1 will clear this bit
 * 1 = interrupt is pending
 * 0 = no interrupt is pending
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_STS . MBOX_SEC_INTR_STICKY
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_STS_MBOX_SEC_INTR_STICKY(x)                       (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_STS_MBOX_SEC_INTR_STICKY                          (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_INTR_STS_MBOX_SEC_INTR_STICKY(x)                       (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief MBOX ECC Fault Address Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:MBOX_ECC:MBOX_ECC_FADDR
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_FADDR                                                     (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1bc))

/**
 * \brief
 * the address to inject the fault
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_FADDR . MBOX_FAULT_ADDR
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_FADDR_MBOX_FAULT_ADDR(x)                               (LAN80XX_ENCODE_BITFIELD(x,0,9))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_FADDR_MBOX_FAULT_ADDR                                  (LAN80XX_ENCODE_BITMASK(0,9))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_FADDR_MBOX_FAULT_ADDR(x)                               (LAN80XX_EXTRACT_BITFIELD(x,0,9))


/**
 * \brief MBOX ECC Fault Data Pointer Register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:MBOX_ECC:MBOX_ECC_FDPTR
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_FDPTR                                                     (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1bd))

/**
 * \brief
 * the bit number to inject the fault
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MBOX_ECC_FDPTR . MBOX_FAULT_DPTR
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MBOX_ECC_FDPTR_MBOX_FAULT_DPTR(x)                               (LAN80XX_ENCODE_BITFIELD(x,0,6))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MBOX_ECC_FDPTR_MBOX_FAULT_DPTR                                  (LAN80XX_ENCODE_BITMASK(0,6))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MBOX_ECC_FDPTR_MBOX_FAULT_DPTR(x)                               (LAN80XX_EXTRACT_BITFIELD(x,0,6))

/**
 * Register Group: \a MCU_IO_MNGT_MISC:MCU_BOOT_INFO
 *
 * MCU Boot Status register
 */


/**
 * \brief MCU Boot Status register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:MCU_BOOT_INFO:MCU_BOOT_STATUS_REG
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MCU_BOOT_STATUS_REG                                                (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1e0))

/**
 * \brief
 * This register is intended to be written by the BootROM FW as the boot
 * sequence progresses, culminating with a final value of "done".The
 * register is read by the Host for status. The values in this register are
 * defined by the FW.This register is reset on any MCU reset.
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MCU_BOOT_STATUS_REG . MCU_BOOT_STATUS
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MCU_BOOT_STATUS_REG_MCU_BOOT_STATUS(x)                          (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MCU_BOOT_STATUS_REG_MCU_BOOT_STATUS                             (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MCU_BOOT_STATUS_REG_MCU_BOOT_STATUS(x)                          (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a MCU_IO_MNGT_MISC:MCU_CONFIG
 *
 * MCU Configuration register
 */


/**
 * \brief MCU Clock Configuration register
 *
 * \details
 * Register: \a MCU_IO_MNGT_MISC:MCU_CONFIG:MCU_SS_CLK_CFG
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MCU_SS_CLK_CFG                                                     (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1f0))

/**
 * \brief
 * This register is used for host to gate off all MCU clocks.This register
 * is reset to 1 on any MCU reset.Note: this register should not be cleared
 * until the POST and OTP loading is done
 *
 * \details
 * 1 - Clocks enabled
 * 0 - Clocks disabled
 *
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MCU_SS_CLK_CFG . MCU_SS_CLK_ENA
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MCU_SS_CLK_CFG_MCU_SS_CLK_ENA(x)                                (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MCU_SS_CLK_CFG_MCU_SS_CLK_ENA                                   (LAN80XX_BIT(0))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MCU_SS_CLK_CFG_MCU_SS_CLK_ENA(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * Register Group: \a MCU_IO_MNGT_MISC:MIM_DEBUG
 *
 * MCU_IO_MNGT debug registers
 */


/**
 * \brief Debug registers
 *
 * \details
 * MCU_IO_MNGT debug register 7
 *
 * Register: \a MCU_IO_MNGT_MISC:MIM_DEBUG:MIM_DEBUG_REG_7
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_7                                                    (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1f8))

/**
 * \brief
 * MCU_IO_MNGT debug register 7
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_7 . MIM_DBG_REG_7
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_7_MIM_DBG_REG_7(x)                                (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_7_MIM_DBG_REG_7                                   (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_7_MIM_DBG_REG_7(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Debug registers
 *
 * \details
 * MCU_IO_MNGT debug register 6
 *
 * Register: \a MCU_IO_MNGT_MISC:MIM_DEBUG:MIM_DEBUG_REG_6
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_6                                                    (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1f9))

/**
 * \brief
 * MCU_IO_MNGT debug register 6
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_6 . MIM_DBG_REG_6
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_6_MIM_DBG_REG_6(x)                                (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_6_MIM_DBG_REG_6                                   (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_6_MIM_DBG_REG_6(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Debug registers
 *
 * \details
 * MCU_IO_MNGT debug register 5
 *
 * Register: \a MCU_IO_MNGT_MISC:MIM_DEBUG:MIM_DEBUG_REG_5
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_5                                                    (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1fa))

/**
 * \brief
 * MCU_IO_MNGT debug register 5
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_5 . MIM_DBG_REG_5
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_5_MIM_DBG_REG_5(x)                                (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_5_MIM_DBG_REG_5                                   (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_5_MIM_DBG_REG_5(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Debug registers
 *
 * \details
 * MCU_IO_MNGT debug register 4
 *
 * Register: \a MCU_IO_MNGT_MISC:MIM_DEBUG:MIM_DEBUG_REG_4
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_4                                                    (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1fb))

/**
 * \brief
 * MCU_IO_MNGT debug register 4
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_4 . MIM_DBG_REG_4
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_4_MIM_DBG_REG_4(x)                                (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_4_MIM_DBG_REG_4                                   (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_4_MIM_DBG_REG_4(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Debug registers
 *
 * \details
 * MCU_IO_MNGT debug register 3
 *
 * Register: \a MCU_IO_MNGT_MISC:MIM_DEBUG:MIM_DEBUG_REG_3
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_3                                                    (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1fc))

/**
 * \brief
 * MCU_IO_MNGT debug register 3
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_3 . MIM_DBG_REG_3
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_3_MIM_DBG_REG_3(x)                                (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_3_MIM_DBG_REG_3                                   (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_3_MIM_DBG_REG_3(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Debug registers
 *
 * \details
 * MCU_IO_MNGT debug register 2
 *
 * Register: \a MCU_IO_MNGT_MISC:MIM_DEBUG:MIM_DEBUG_REG_2
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_2                                                    (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1fd))

/**
 * \brief
 * MCU_IO_MNGT debug register 2
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_2 . MIM_DBG_REG_2
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_2_MIM_DBG_REG_2(x)                                (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_2_MIM_DBG_REG_2                                   (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_2_MIM_DBG_REG_2(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Debug registers
 *
 * \details
 * MCU_IO_MNGT debug register 1
 *
 * Register: \a MCU_IO_MNGT_MISC:MIM_DEBUG:MIM_DEBUG_REG_1
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_1                                                    (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1fe))

/**
 * \brief
 * MCU_IO_MNGT debug register 1
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_1 . MIM_DBG_REG_1
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_1_MIM_DBG_REG_1(x)                                (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_1_MIM_DBG_REG_1                                   (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_1_MIM_DBG_REG_1(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Debug registers
 *
 * \details
 * MCU_IO_MNGT debug register 0
 *
 * Register: \a MCU_IO_MNGT_MISC:MIM_DEBUG:MIM_DEBUG_REG_0
 */
#define LAN80XX_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_0                                                    (LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, 0x1ff))

/**
 * \brief
 * MCU_IO_MNGT debug register 0
 *
 * \details
 * Field: ::LAN80XX_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_0 . MIM_DBG_REG_0
 */
#define  LAN80XX_F_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_0_MIM_DBG_REG_0(x)                                (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_0_MIM_DBG_REG_0                                   (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_MCU_IO_MNGT_MISC_MIM_DEBUG_REG_0_MIM_DBG_REG_0(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,16))


#endif /* _LAN80XX_MALIBU25G_REGS_MCU_IO_MNGT_MISC_H_ */
