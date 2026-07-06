// Copyright (c) 2026 Vincent Jardin, Vincent Cruz, Free Mobile
// SPDX-License-Identifier: MIT

// PHY-only mode: runtime support for boards that carry MEPA PHYs (e.g. a
// LAN80xx reached over SPI) but no MESA switch chip. main.c enters this
// mode when no switch UIO device is found; the demo then serves only the
// MEPA PHY slots plus the CLI/JSON-RPC sockets, so
//   mepa-cmd Dev Create/Attach/conf
// keeps working on switch-less boards.

#ifndef _PHY_ONLY_H_
#define _PHY_ONLY_H_

#include "microchip/ethernet/switch/api.h"
#include "main.h"

// Set once by phy_only_enter()
extern mesa_bool_t phy_only_mode;

// Enter PHY-only mode (called when uio_reg_io_init() finds no switch).
void phy_only_enter(void);

// Switch-register stubs handed to MEBA instead of the UIO accessors:
// there is no switch, every access fails.
mesa_rc phy_only_reg_read(const mesa_chip_no_t chip_no,
                          const uint32_t addr,
                          uint32_t *const value);
mesa_rc phy_only_reg_write(const mesa_chip_no_t chip_no,
                           const uint32_t addr,
                           const uint32_t value);

// board_conf_get() backend: canned answers replacing the
// MESA-capability-based board detection (which needs a switch instance).
mesa_rc phy_only_board_conf_get(const char *tag, char *buf,
                                size_t bufsize, size_t *buflen);

// The subset of init_modules() that does not require the MESA switch
// instance.
void phy_only_init_modules(mscc_appl_init_t *init);

// Configurable PHY slots:
//   -P <spidev>[@pad[@freq]][:ports]
// once per SPI-attached PHY package.
// Without -P the stock slot devices (/dev/spidev0.1, /dev/spidev0.2) apply
// unchanged;
// with -P, it is forced into PHY-only mode and SPI access for the
// ports is routed directly to the devices.
void phy_only_opt_reg(void);          // register -P (call at option-REG time)
int phy_only_slots_configured(void);  // number of -P slots given
mesa_rc phy_only_slots_open(void);    // open the configured spidev nodes
mesa_rc phy_only_spi_rw(mepa_port_no_t port_no, mesa_bool_t read,
                        uint8_t mmd, uint16_t reg_num, uint32_t *const data);

// LAN80xx mailbox host-interrupt (MDINT) over a host GPIO line (board-portable):
// bind the MEPA gpio callback to a GPIO chardev edge-event line, so the mailbox
// waits on the real INTR instead of polling the flag over SPI. The INTR pin is
// board-specific:
//   gpiochip_line = a DTS line name (gpio-line-names, e.g. "lan8023-mdint"),
//                   probed across every gpiochip, or an explicit
//                   "<chip-path>:<line>" (e.g. "/dev/gpiochip2:0").
//   NULL          -> use $LAN80XX_MDINT, else the built-in default.
struct mepa_device;
mesa_rc phy_only_mdint_register(const struct mepa_device *dev,
                                const char *gpiochip_line);

#endif /* _PHY_ONLY_H_ */
