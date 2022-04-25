// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

// Microchip is aware that some terminology used in this technical document is
// antiquated and inappropriate. As a result of the complex nature of software
// where seemingly simple changes have unpredictable, and often far-reaching
// negative results on the software's functionality (requiring extensive
// retesting and revalidation) we are unable to make the desired changes in all
// legacy systems without compromising our product or our clients' products.

#ifndef _MICROCHIP_ETHERNET_SWITCH_API_INIT_
#define _MICROCHIP_ETHERNET_SWITCH_API_INIT_

#include <microchip/ethernet/switch/api/misc.h>
#include <microchip/ethernet/switch/api/types.h>
#include <microchip/ethernet/switch/api/port.h>
#include <microchip/ethernet/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

// Target chip type
typedef enum {
    MESA_TARGET_CU_PHY,                  // Cu PHY family
    MESA_TARGET_10G_PHY,                 // 10G PHY family
    MESA_TARGET_CARACAL_LITE  = 0x7423,  // Caracal-Lite CE switch
    MESA_TARGET_SPARX_III_10  = 0x7424,  // SparxIII-10 switch
    MESA_TARGET_SPARX_III_18  = 0x7425,  // SparxIII-18 switch
    MESA_TARGET_SPARX_III_24  = 0x7426,  // SparxIII-24 switch
    MESA_TARGET_SPARX_III_26  = 0x7427,  // SparxIII-26 switch
    MESA_TARGET_CARACAL_1     = 0x7428,  // Caracal-1 CE switch
    MESA_TARGET_CARACAL_2     = 0x7429,  // Caracal-2 CE switch
    MESA_TARGET_SPARX_IV_52   = 0x7442,  // Sparx-IV-52 switch
    MESA_TARGET_SPARX_IV_44   = 0x7444,  // Sparx-IV-44 switch
    MESA_TARGET_SPARX_IV_80   = 0x7448,  // Sparx-IV-80 switch
    MESA_TARGET_SPARX_IV_90   = 0x7449,  // Sparx-IV-90 switch
    MESA_TARGET_SERVAL_2      = 0x7438,  // Serval-2 CE switch
    MESA_TARGET_LYNX_2        = 0x7464,  // LynX-2 CE switch
    MESA_TARGET_JAGUAR_2      = 0x7468,  // Jaguar-2 CE switch
    MESA_TARGET_SERVAL_T      = 0x7410,  // Serval-T switch
    MESA_TARGET_SERVAL_TP     = 0x7415,  // Serval-TP switch
    MESA_TARGET_SERVAL_TE     = 0x7430,  // Serval-TE switch
    MESA_TARGET_SERVAL_TEP    = 0x7435,  // Serval-TEP switch
    MESA_TARGET_SERVAL_2_LITE = 0x7436,  // Serval-2 Lite switch
    MESA_TARGET_SERVAL_TE10   = 0x7437,  // Serval-TE10 switch
    MESA_TARGET_SPARX_IV_34   = 0x7440,  // Sparx-IV-34 switch
    MESA_TARGET_7511          = 0x7511,  // VSC7511 unmgd switch
    MESA_TARGET_7512          = 0x7512,  // VSC7512 unmgd switch
    MESA_TARGET_7513          = 0x7513,  // VSC7513 switch
    MESA_TARGET_7514          = 0x7514,  // VSC7514 switch
    MESA_TARGET_7546          = 0x7546,  // SparX-5-64  Enterprise Switch
    MESA_TARGET_7549          = 0x7549,  // SparX-5-90  Enterprise Switch
    MESA_TARGET_7552          = 0x7552,  // SparX-5-128 Enterprise Switch
    MESA_TARGET_7556          = 0x7556,  // SparX-5-160 Enterprise Switch
    MESA_TARGET_7558          = 0x7558,  // SparX-5-200 Enterprise Switch
    MESA_TARGET_7546TSN       = 0x47546, // SparX-5-64i Industrial Switch
    MESA_TARGET_7549TSN       = 0x47549, // SparX-5-90i Industrial Switch
    MESA_TARGET_7552TSN       = 0x47552, // SparX-5-128i Industrial Switch
    MESA_TARGET_7556TSN       = 0x47556, // SparX-5-160i Industrial Switch
    MESA_TARGET_7558TSN       = 0x47558, // SparX-5-200i Industrial Switch
    MESA_TARGET_LAN9662       = 0x9662,  // LAN9662 switch
    MESA_TARGET_LAN9668       = 0x9668,  // LAN9668 switch
} mesa_target_type_t;

// Create structure
typedef struct {
    mesa_target_type_t target; // Target type
} mesa_inst_create_t;

// Initialize create structure for target.
// target [IN]   Target name
// create [OUT]  Create structure
mesa_rc mesa_inst_get(const mesa_target_type_t target,
                      mesa_inst_create_t       *const create);

// Create target instance.
// create [IN] Create structure
// inst [OUT]  Target instance reference.
mesa_rc mesa_inst_create(const mesa_inst_create_t *const create,
                         mesa_inst_t              *const inst);

// Destroy target instance.
// inst [IN] Target instance reference.
mesa_rc mesa_inst_destroy(const mesa_inst_t inst);

// Register read function
// chip_no [IN] Chip number, for targets with multiple chips
// addr [IN]    Register address
// value [OUT]  Register value
typedef mesa_rc (*mesa_reg_read_t)(const mesa_chip_no_t chip_no,
                                   const uint32_t       addr,
                                   uint32_t             *const value);

// Register write function
// chip_no [IN] Chip number, for targets with multiple chips
// addr [IN]    Register address
// value [IN]   Register value
typedef mesa_rc (*mesa_reg_write_t)(const mesa_chip_no_t chip_no,
                                    const uint32_t       addr,
                                    const uint32_t       value);

// I2C read function
// port_no [IN] Port number
// i2c_addr [IN] I2C device address
// addr [IN]   Register address
// data [OUT]  Pointer the register(s) data value.
// cnt [IN]    Number of registers to read
typedef mesa_rc (*mesa_i2c_read_t)(const mesa_port_no_t port_no,
                                   const uint8_t i2c_addr,
                                   const uint8_t addr,
                                   uint8_t *const data,
                                   const uint8_t cnt);

// I2C write function
// port_no [IN] Port number
// i2c_addr [IN] I2C device address
// data [OUT]  Pointer the data to be written.
// cnt [IN]    Number of data bytes to write
typedef mesa_rc (*mesa_i2c_write_t)(const mesa_port_no_t port_no,
                                    const uint8_t i2c_addr,
                                    uint8_t *const data,
                                    const uint8_t cnt);

// Register read function for clock chip
// addr  [IN]  Register address
// value [OUT] Register value
typedef mesa_rc (*mesa_clock_read_t)(const uint32_t addr, uint32_t *const value) CAP(CLOCK);

// Register write function for clock chip
// addr  [IN] Register address
// value [IN] Register value
typedef mesa_rc (*mesa_clock_write_t)(const uint32_t addr, const uint32_t value) CAP(CLOCK);

// SPI read/write function
// inst [IN] Vitesse API instance.
// port_no [IN] Port number.
// bitsize [IN] Size (in bytes) of bitstream following this parameter.
// data [IN|OUT] Pointer to the data to be written to SPI Client, if doing write operation.
//               Pointer to the data read from SPI Client, if doing read operation.
typedef mesa_rc (*mesa_spi_read_write_t)(const mesa_inst_t inst,
                                       const mesa_port_no_t port_no,
                                       const uint8_t bitsize,
                                       uint8_t *const bitstream);

// SPI 32 bit read/write function
// port_no [IN] Port number.
// read    [IN] Read/Write.
// dev     [IN] MMD device number.
// reg_num [IN] Register offset.
// data [IN|OUT] Pointer to the data to be written to SPI Client, if doing write operation.
//               Pointer to the data read from SPI Client, if doing read operation.
typedef mesa_rc (*mesa_spi_32bit_read_write_t)(const mesa_inst_t inst,
                                               mesa_port_no_t    port_no,
                                               mesa_bool_t       read,
                                               uint8_t           dev,
                                               uint16_t          reg_num,
                                               uint32_t          *const data);

// SPI 64 bit read/write function
// port_no [IN] Port number.
// read    [IN] Read/Write.
// dev     [IN] MMD device number.
// reg_num [IN] Register offset.
// data [IN|OUT] Pointer to the data to be written to SPI Client, if doing write operation.
//               Pointer to the data read from SPI Client, if doing read operation.
typedef mesa_rc (*mesa_spi_64bit_read_write_t)(const mesa_inst_t inst,
                                               mesa_port_no_t    port_no,
                                               mesa_bool_t       read,
                                               uint8_t           dev,
                                               uint16_t          reg_num,
                                               uint64_t          *const data);

// MII management read function (IEEE 802.3 clause 22)
// port_no [IN] Port number
// addr [IN]    Register address (0-31)
// value [OUT]  Register value
typedef mesa_rc (*mesa_miim_read_t)(const mesa_inst_t    inst,
                                    const mesa_port_no_t port_no,
                                    const uint8_t        addr,
                                    uint16_t             *const value);

// MII management write function (IEEE 802.3 clause 22)
// port_no [IN] Port number
// addr [IN]    Register address (0-31)
// value [IN]   Register value
typedef mesa_rc (*mesa_miim_write_t)(const mesa_inst_t    inst,
                                     const mesa_port_no_t port_no,
                                     const uint8_t        addr,
                                     const uint16_t       value);

// MMD management read function (IEEE 802.3 clause 45)
// port_no [IN] Port number
// mmd [IN]     MMD address (0-31)
// addr [IN]    Register address (0-65535)
// value [OUT]  Register value
typedef mesa_rc (*mesa_mmd_read_t)(const mesa_inst_t    inst,
                                   const mesa_port_no_t port_no,
                                   const uint8_t        mmd,
                                   const uint16_t       addr,
                                   uint16_t             *const value);

// MMD management read increment function (IEEE 802.3 clause 45)
// port_no [IN] Port number
// mmd [IN]     MMD address (0-31)
// addr [IN]    Start register address (0-65535)
// buf [OUT]    The register values (pointer provided by user)
// count [IN]   Number of register reads (increment register reads)
typedef mesa_rc (*mesa_mmd_read_inc_t)(const mesa_inst_t    inst,
                                       const mesa_port_no_t port_no,
                                       const uint8_t        mmd,
                                       const uint16_t       addr,
                                       uint16_t             *const buf,
                                       uint8_t              count);

// MMD management write function (IEEE 802.3 clause 45)
// port_no [IN] Port number
// mmd [IN]     MMD address (0-31)
// addr [IN]    Start register address (0-65535)
// buf [IN]     The register value
typedef mesa_rc (*mesa_mmd_write_t)(const mesa_inst_t    inst,
                                    const mesa_port_no_t port_no,
                                    const uint8_t        mmd,
                                    const uint16_t       addr,
                                    const uint16_t       value);

// Port mux_mode configuration
//
// The mux_mode is relevant for chips that allow muxing of port to SerDes macros.
// The muxing takes place inside the chip and accommodates support for multiple
// port configuration schemes. Each chip that supports muxing can use a number of
// these modes. See below for chip-specific tables of mux modes.
//
// Ocelot
// MESA_PORT_MUX_MODE_0: 4x1G Dual + 2x1G SGMII + 2.5G NPI (+ 2x2.5G SGMII for VSC7514)
// MESA_PORT_MUX_MODE_1: 4x1G Dual + 2x1G SGMII + PCIe (+ 2x2.5G SGMII for VSC7514)x
// MESA_PORT_MUX_MODE_2: 4x1G Dual + 1xQSGMII + 2.5G NPI (+ 1x1G SGMII + 1x2.5G SGMII for VSC7514)
// MESA_PORT_MUX_MODE_3: 4x1G Dual + 1xQSGMII + PCIe (+ 1x1G SGMII + 1x2.5G SGMII for VSC7514)
// MESA_PORT_MUX_MODE_4: 2x1G Dual + 2x1G CuPHY + 4x1G SGMII + 2x2.5G SGMII + 2.5G NPI (VSC7514 only)
// MESA_PORT_MUX_MODE_5: 2x1G Dual + 2x1G CuPHY + 4x1G SGMII + 2x2.5G SGMII + PCIe (VSC7514 only)
//
// LAN966X
// MESA_PORT_MUX_MODE_0: 2xQSGMII (LAN9668)
// MESA_PORT_MUX_MODE_1: 2xCu + 2x2.5G (+ 1xQSGMII for LAN9668)
// MESA_PORT_MUX_MODE_5: 2xCu + 3x1G (LAN9668)

typedef enum {
    MESA_PORT_MUX_MODE_AUTO CAP(PORT_MUX_AUTO),
    MESA_PORT_MUX_MODE_0,
    MESA_PORT_MUX_MODE_1,
    MESA_PORT_MUX_MODE_2,
    MESA_PORT_MUX_MODE_3,
    MESA_PORT_MUX_MODE_4,
    MESA_PORT_MUX_MODE_5,
} mesa_port_mux_mode_t CAP(PORT_MUX);

// Serdes fields
typedef struct {
    uint32_t ob_post0; // Trace length
    uint32_t ob_sr;    // Slew Rate
} mesa_serdes_fields_t;

// Serdes macro configuration
typedef struct {
    mesa_vdd_t           serdes1g_vdd; // Serdes1g supply
    mesa_vdd_t           serdes6g_vdd; // Serdes6g supply
    mesa_bool_t          ib_cterm_ena; // AC(0)/DC(1) coupled
    mesa_serdes_fields_t qsgmii;       // Appl/Board specific fields for QSGMII
} mesa_serdes_macro_conf_t;

// Restart information source
typedef enum {
    MESA_RESTART_INFO_SRC_NONE,   // Restart information not stored in PHYs
    MESA_RESTART_INFO_SRC_CU_PHY, // Restart information stored in 1G PHY
    MESA_RESTART_INFO_SRC_10G_PHY // Restart information stored in 10G PHY
} mesa_restart_info_src_t;

// Queue System modes
typedef enum {
    MESA_QS_MODE_DEFAULT,   // Defaults settings are used
    MESA_QS_MODE_QUEUE_LIM  // Queue Limitiation settings are enabled.
} mesa_qs_mode_t CAP(PORT_QS_CONF);

// Queue System settings
typedef struct {
    mesa_qs_mode_t mode; // The mode of the queue system
    uint32_t       wm1;  // Generic Watermark parameter 1
    uint32_t       wm2;  // Generic Watermark parameter 2
} mesa_qs_conf_t CAP(PORT_QS_CONF);

// Core clock frequency
typedef enum {
    MESA_CORE_CLOCK_DEFAULT,  // Defaults to the highest supported frequency
    MESA_CORE_CLOCK_250MHZ,   // 250MHZ core clock frequency
    MESA_CORE_CLOCK_500MHZ,   // 500MHZ core clock frequency
    MESA_CORE_CLOCK_625MHZ,   // 625MHZ core clock frequency
} mesa_core_clock_freq_t CAP(INIT_CORE_CLOCK);

// Core clock configuration
typedef struct {
    mesa_core_clock_freq_t freq;   // The frequency of the core clock (LC-PLL)
} mesa_core_clock_conf_t CAP(INIT_CORE_CLOCK);

// Initialization configuration.
typedef struct {
    // Register access function are not used for MESA_TARGET_CU_PHY
    mesa_reg_read_t   reg_read;     // Register read function
    mesa_reg_write_t  reg_write;    // Register write function

    mesa_clock_read_t  clock_read  CAP(CLOCK); // Clock-chip read function
    mesa_clock_write_t clock_write CAP(CLOCK); // Clock-chip write function

    // MII management access must be setup for MESA_TARGET_CU_PHY
    mesa_miim_read_t  miim_read;    // MII management read function
    mesa_miim_write_t miim_write;   // MII management write function

    // MMD management access must be setup for 10G phys
    mesa_mmd_read_t     mmd_read;     // MMD management read function
    mesa_mmd_read_inc_t mmd_read_inc; // MMD management read increment function
    mesa_mmd_write_t    mmd_write;    // MMD management write function

    // Board specific SPI read/write callout functions
    mesa_spi_read_write_t   spi_read_write;
    mesa_spi_32bit_read_write_t   spi_32bit_read_write;
    mesa_spi_64bit_read_write_t   spi_64bit_read_write;

    // GPIO functionallity information get callout function
    mesa_gpio_func_info_get_t gpio_func_info_get;

    // Serdes tap value get callout function
    mesa_port_serdes_tap_get_t serdes_tap_get;

    // Do not reset the switch core when calling vtss_init_conf_set. This
    // assumes someone else is doing the reset.
    //
    // NOTE: Only the JR2 family supports resetting. This setting has no effect
    // on non-JR2 designs.
    mesa_bool_t             skip_switch_reset;

    mesa_bool_t             spi_bus;           // Using SPI bus interface for reg_read/reg_write
    mesa_bool_t             warm_start_enable; // Allow warm start
    mesa_restart_info_src_t restart_info_src;  // Source of restart information
    mesa_port_no_t          restart_info_port; // Port used to store PHY restart information

    mesa_port_mux_mode_t mux_mode CAP(PORT_MUX); // Mux mode (port connection to Serdes Macroes)

    mesa_serdes_macro_conf_t serdes; // Serdes macro configuration

    mesa_bool_t using_ufdma; // Set to TRUE if using the uFDMA driver to Rx and Tx frames (typically used under Linux)

    // Reserve bandwidth for Up-MEPs and service activation tests.
    // Example: To get support for 10Gbps Y.1564, set loopback_bw_mbps to 10000.
    uint32_t loopback_bw_mbps;

    mesa_qs_conf_t qs_conf CAP(PORT_QS_CONF); // Queue system configuration

    mesa_bool_t vlan_counters_disable; // Disable VLAN counters (OAM uses the counter resources)
    mesa_bool_t psfp_counters_enable;  // Enable PSFP counter mode for ingress counters

    mesa_core_clock_conf_t core_clock CAP(INIT_CORE_CLOCK); // Core clock (LCPLL) configuration
    mesa_bool_t packet_init_disable; // Skip initilization of packet interface (no CPU packet support, L26/MESA-354/BZ24450)
} mesa_init_conf_t;

// Get default initialization configuration
// conf [OUT] Initialization configuration
mesa_rc mesa_init_conf_get(const mesa_inst_t inst,
                           mesa_init_conf_t  *const conf);

// Set initialization configuration.
// conf [IN] Initialization configuration
mesa_rc mesa_init_conf_set(const mesa_inst_t      inst,
                           const mesa_init_conf_t *const conf);

// Change access interface to either use SPI or another interface.
//
// Registers in the VCore register space are not directly accessible when using
// the SPI interface, so multiple chip-accesses are required in order to read
// and write registers in that space when using SPI, whereas such registers are
// directly accessible when using PCI-E or the internal CPU.
//
// When this function is invoked with \p spi_bus set to TRUE, the API will
// detect register accesses to the VCore register space and make the required
// indirect access through multiple calls to the application-installed register
// read/write functions.
//
// When \p spi_bus is set to FALSE, the API will perform any type of access in
// one single call to the application-installed register read/write functions.
//
// Normally, you will control the access mode once at API instantiation time
// through the mesa_init_conf_t::spi_bus member, but in certain applications
// it might be desirable to be able to change it dynamically - hence this
// function.
//
// spi_bus [IN] Control the access mode.
mesa_rc mesa_register_access_mode_set(const mesa_inst_t inst, mesa_bool_t spi_bus);

// Get current way of accessing registers.
// spi_bus [OUT] Pointer to a mesa_bool_t receiving current access mode.
mesa_rc mesa_register_access_mode_get(const mesa_inst_t inst, mesa_bool_t *spi_bus);

// SPI Client endian configuration
typedef enum {
    MESA_SPI_ENDIAN_LITTLE, // Use little endian
    MESA_SPI_ENDIAN_BIG     // Use big endian
} mesa_spi_endian_t;

// SPI Client bit order configuration
typedef enum {
    MESA_SPI_BIT_ORDER_MSB_FIRST, // Transfer MSB first
    MESA_SPI_BIT_ORDER_LSB_FIRST  // Transfer LSB first
} mesa_spi_bit_order_t;

// SPI Client initialization configuration.
typedef struct {
    mesa_reg_write_t     reg_write; // Register write function
    mesa_reg_read_t      reg_read;  // Register read function
    mesa_spi_endian_t    endian;    // Endian configuration
    mesa_spi_bit_order_t bit_order; // Bit order configuration
    uint8_t              padding;   // Number of padding bytes to insert before read-data is shifted out
} mesa_spi_slave_init_t;

// Initialize SPI Client interface when using an external CPU.
// This must always be the first call into the API.
// conf [IN] Initialization configuration
mesa_rc mesa_spi_slave_init(const mesa_spi_slave_init_t *const conf);

// Indicate configuration end.
// If a warm start has been done, the stored configuration will be applied.
mesa_rc mesa_restart_conf_end(const mesa_inst_t inst);

// API version
typedef uint16_t mesa_version_t;

// Restart type
typedef enum {
    MESA_RESTART_COLD = 0, // Cold: Chip and CPU restart, e.g. power cycling
    MESA_RESTART_COOL,     // Cool: Chip and CPU restart done by CPU
    MESA_RESTART_WARM      // Warm: CPU restart only
} mesa_restart_t;

// Restart status
typedef struct {
    mesa_restart_t restart;      // Previous restart mode
    mesa_version_t prev_version; // Previous API version
    mesa_version_t cur_version;  // Current API version
} mesa_restart_status_t;

// Get restart status
// status [OUT] Restart status
mesa_rc mesa_restart_status_get(const mesa_inst_t inst,
                                mesa_restart_status_t *const status);

// Get restart configuration (next restart mode)
// restart [OUT] Restart mode
mesa_rc mesa_restart_conf_get(const mesa_inst_t inst,
                              mesa_restart_t *const restart);

// Set restart configuration (next restart mode)
// restart [IN] Restart mode
mesa_rc mesa_restart_conf_set(const mesa_inst_t inst,
                              const mesa_restart_t restart);

#include <microchip/ethernet/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_SWITCH_API_INIT_
