// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MSCC_APPL_MAIN_H_
#define _MSCC_APPL_MAIN_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "microchip/ethernet/switch/api.h"

typedef enum {
    MSCC_INIT_CMD_REG,         // Register trace and startup options
    MSCC_INIT_CMD_INIT,        // Initialize module
    MSCC_INIT_CMD_INIT_WARM,   // Initialize module after warm start
    MSCC_INIT_CMD_POLL,        // Poll module every second
    MSCC_INIT_CMD_POLL_FAST,   // Poll module fast
    MSCC_INIT_CMD_POLL_FASTEST // Poll module even faster
} mscc_appl_init_cmd_t;

// Startup option
typedef struct mscc_appl_opt_t {
    char *option;                // Option character, e.g "t:"
    char *parm;                  // Option parameter, e.g. "<module>:<group>:<level>
    char *descr;                 // Description
    mesa_rc (*func)(char *parm); // Command function

    // Internal fields
    struct mscc_appl_opt_t *next; /* Next in registration list */
} mscc_appl_opt_t;

void mscc_appl_opt_reg(mscc_appl_opt_t *opt);

typedef struct {
    mscc_appl_init_cmd_t cmd;
    struct meba_inst    *board_inst;
} mscc_appl_init_t;

// Module init functions
void mscc_appl_port_init(mscc_appl_init_t *init);
void mscc_appl_sfp_init(mscc_appl_init_t *init);
void mscc_appl_mac_init(mscc_appl_init_t *init);
void mscc_appl_vlan_init(mscc_appl_init_t *init);
void mscc_appl_packet_init(mscc_appl_init_t *init);
void mscc_appl_ip_init(mscc_appl_init_t *init);
void mscc_appl_json_rpc_init(mscc_appl_init_t *init);
void mscc_appl_debug_init(mscc_appl_init_t *init);
void mscc_appl_symreg_init(mscc_appl_init_t *init);
void mscc_appl_trace_init(mscc_appl_init_t *init);
void mscc_appl_test_init(mscc_appl_init_t *init);
void mscc_appl_kr_init(mscc_appl_init_t *init);
void mscc_appl_example_init(mscc_appl_init_t *init);
void mscc_appl_uio_init(mscc_appl_init_t *init);
void mscc_appl_spi_init(mscc_appl_init_t *init);
void mscc_appl_intr_init(mscc_appl_init_t *init);

typedef enum {
    SPI_USER_REG,  // Switch register access
    SPI_USER_FPGA, // FPGA register access

    SPI_USER_CNT // Number of users
} spi_user_t;

// Register access functions
mesa_rc spi_reg_read(const mesa_chip_no_t chip_no, const uint32_t addr, uint32_t *const value);
mesa_rc spi_reg_write(const mesa_chip_no_t chip_no, const uint32_t addr, const uint32_t value);
mesa_rc spi_io_init(spi_user_t user, const char *device, int freq, int padding);
mesa_rc spi_read(spi_user_t user, const uint32_t addr, uint32_t *const value);
mesa_rc spi_write(spi_user_t user, const uint32_t addr, const uint32_t value);
mesa_rc uio_reg_read(const mesa_chip_no_t chip_no, const uint32_t addr, uint32_t *const value);
mesa_rc uio_reg_write(const mesa_chip_no_t chip_no, const uint32_t addr, const uint32_t value);
mesa_rc uio_reg_io_init(void);

typedef mesa_rc (*reg_read_t)(const mesa_chip_no_t chip_no,
                              const uint32_t       addr,
                              uint32_t *const      value);

typedef mesa_rc (*reg_write_t)(const mesa_chip_no_t chip_no,
                               const uint32_t       addr,
                               const uint32_t       value);

// Management port (0-based) owned by IP module
extern mesa_port_no_t ip_port;

// File descriptor read activity callback registration
typedef void (*fd_read_callback_t)(int fd, void *ref);
int fd_read_register(int fd, fd_read_callback_t callback, void *ref);

void get_mac_addr(uint8_t *mac);
void ip_mac_setup(mesa_vid_t vid, mesa_bool_t add);

#ifdef __cplusplus
}
#endif

// MEBA API wrapper
#define MEBA_WRAP(_name_, _inst_, _args_...)                                                       \
    ({                                                                                             \
        mesa_rc rc;                                                                                \
        if (_inst_->api._name_) {                                                                  \
            _inst_->iface.debug(MEBA_TRACE_LVL_RACKET, __FUNCTION__, __LINE__, "Calling %s",       \
                                #_name_);                                                          \
            rc = _inst_->api._name_(_inst_, _args_);                                               \
            _inst_->iface.debug(MEBA_TRACE_LVL_NOISE, __FUNCTION__, __LINE__, "%s returns %d",     \
                                #_name_, rc);                                                      \
        } else {                                                                                   \
            rc = MESA_RC_NOT_IMPLEMENTED;                                                          \
        }                                                                                          \
        rc;                                                                                        \
    })

#endif /* _MSCC_APPL_MAIN_H_ */
