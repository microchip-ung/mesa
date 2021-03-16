// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_INDY_PRIVATE_H_
#define _MEPA_INDY_PRIVATE_H_

#include <unistd.h>

#define MEPA_RC(expr) { mesa_rc __rc__ = (expr); if (__rc__ < MESA_RC_OK) return __rc__; }
#define TRUE  1
#define FALSE 1
#define EXT_PAGE 1 // extended page access
#define MMD_DEV  2 // MMD device access
//Direct register access macros
#define RD(dev, addr, value) indy_direct_reg_rd(dev, addr, value)
#define WR(dev, addr, value) indy_direct_reg_wr(dev, addr, value, 0xffff)
#define WRM(dev, addr, val, mask) indy_direct_reg_wr(dev, addr, val, mask)

//Extended page register access macros
#define EP_RD(dev, page_addr, value) indy_ext_reg_rd(dev, page_addr, value)
#define EP_WR(dev, page_addr, value) indy_ext_reg_wr(dev, page_addr, value, 0xffff)
#define EP_WRM(dev, page_addr, value, mask) indy_ext_reg_wr(dev, page_addr, value, mask)

//MMD device register access macros
#define MMD_RD(dev, mmd_addr, value) indy_mmd_reg_rd(dev, mmd_addr, value)
#define MMD_WR(dev, mmd_addr, value) indy_mmd_reg_wr(dev, mmd_addr, value, 0xffff)
#define MMD_WRM(dev, mmd_addr, val, mask) indy_mmd_reg_wr(dev, mmd_addr, val, mask)

#define PHY_MSLEEP(m) usleep((m)*1000)

// Locking Macros
// TODO, still using MESA callouts - should be safe from a thread/lock
// persepctive, but needs to be changed to make MEPA self-contained
#define MEPA_ENTER(...) {         \
    mesa_api_lock_t lock;         \
    lock.function = __FUNCTION__; \
    lock.file = __FILE__;         \
    lock.line = __LINE__;         \
    mesa_callout_lock(&lock);     \
}

#define MEPA_EXIT(...) {          \
    mesa_api_lock_t lock;         \
    lock.function = __FUNCTION__; \
    lock.file = __FILE__;         \
    lock.line = __LINE__;         \
    mesa_callout_unlock(&lock);   \
}

// register access functions
mepa_rc indy_direct_reg_rd(mepa_device_t *dev, uint16_t addr, uint16_t *value);
mepa_rc indy_direct_reg_wr(mepa_device_t *dev, uint16_t addr, uint16_t value, uint16_t mask);
mepa_rc indy_ext_reg_rd(mepa_device_t *dev, uint16_t page, uint16_t addr, uint16_t *value);
mepa_rc indy_ext_reg_wr(mepa_device_t *dev, uint16_t page, uint16_t addr, uint16_t value, uint16_t mask);
mepa_rc indy_mmd_reg_rd(mepa_device_t *dev, uint16_t mmd, uint16_t addr, uint16_t *value);
mepa_rc indy_mmd_reg_wr(mepa_device_t *dev, uint16_t mmd, uint16_t addr, uint16_t value, uint16_t mask);

#endif
