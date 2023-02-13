// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MICROCHIP_ETHERNET_BOARD_SFP_DRIVER_H_
#define _MICROCHIP_ETHERNET_BOARD_SFP_DRIVER_H_

#include <microchip/ethernet/phy/api.h>
#include <microchip/ethernet/switch/api.h>
#include <microchip/ethernet/board/api/base.h>
#include <microchip/ethernet/board/api/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

// SFP_DRIVER
//
// This API defines the interface used by the switch application
// to interact wit the SFP. Using this interface the switch application
// should not know which SFP it is using.
//
// Each SFP driver needs to implement the following methods for a
// minimum configuration:
//  meba_sfp_driver_delete_t
//  meba_sfp_driver_probe_t
//  meba_sfp_driver_poll_t
//  meba_sfp_driver_conf_set_t

// Contains methods that are specific to each sfp module.
struct meba_sfp_driver;

// Represents an instance of the meba_sfp_driver.
struct meba_sfp_device;

/**  Address mode that is specific for all sfp modules.
 * Contains the values that are specific to an address mode. */
typedef struct {
    mesa_inst_t inst;       // Mesa instance
    mesa_port_no_t port_no; // Port number
    struct meba_inst *meba_inst;  // Meba instance
} mscc_sfp_driver_address_t;

//  Enumeration of all possible address modes
typedef enum {
    mscc_sfp_driver_address_mode, // Mscc address mode
} meba_sfp_driver_address_mode_t;

// Union that contains all the values for address modes.  Enumeration
// meba_sfp_driver_address_mode_t decides which address type to be used.
typedef union { mscc_sfp_driver_address_t mscc_address; // Mscc address value.
} meba_sfp_driver_address_val_t;

// Main structure that contains the address mode and the addres value.
typedef struct meba_sfp_driver_address {
    meba_sfp_driver_address_mode_t mode; // Mode to access sfp
    meba_sfp_driver_address_val_t val;   // Address values
} meba_sfp_driver_address_t;

//  Represents the status of the SFP, that is read from SFP module.
typedef struct sfp_driver_status {
    mesa_bool_t link;        // Link is up
    mesa_port_speed_t speed; // Speed
    mesa_bool_t fdx;         // Full duplex
    mesa_bool_t los;         // Loss of signal
    mesa_aneg_t aneg;        // Auto-negotiation result
} meba_sfp_driver_status_t;

// Represents the configuration that is applied to SFP module.
typedef struct sfp_driver_conf {
    mesa_port_speed_t speed;       // Speed
    meba_port_admin_state_t admin; // Admin state
    mesa_bool_t flow_control;      // Flow control (Standard 802.3x)
} meba_sfp_driver_conf_t;

// SFP transceiver types.
typedef enum {
    MEBA_SFP_TRANSRECEIVER_NONE,          // No SFP
    MEBA_SFP_TRANSRECEIVER_NOT_SUPPORTED, // SFP not supported for this interface
    MEBA_SFP_TRANSRECEIVER_100FX,         // 100M Fiber SFP
    MEBA_SFP_TRANSRECEIVER_100BASE_LX,    // 100M Cu SFP
    MEBA_SFP_TRANSRECEIVER_100BASE_ZX,    // 100M Cu SFP
    MEBA_SFP_TRANSRECEIVER_100BASE_SX,    // 100M Cu SFP
    MEBA_SFP_TRANSRECEIVER_100BASE_BX10,  // Not supported
    MEBA_SFP_TRANSRECEIVER_100BASE_T,     // Not supported
    MEBA_SFP_TRANSRECEIVER_1000BASE_BX10, // Not supported
    MEBA_SFP_TRANSRECEIVER_1000BASE_T,    // Cu SFP
    MEBA_SFP_TRANSRECEIVER_1000BASE_CX,   // 1G Fiber CX SFP
    MEBA_SFP_TRANSRECEIVER_1000BASE_SX,   // 1G Fiber SX SFP
    MEBA_SFP_TRANSRECEIVER_1000BASE_LX,   // 1G Fiber LX SFP
    MEBA_SFP_TRANSRECEIVER_1000BASE_ZX,   // 1G Fiber ZX SFP
    MEBA_SFP_TRANSRECEIVER_1000BASE_LR,   // 1G Fiber LR SFP
    MEBA_SFP_TRANSRECEIVER_1000BASE_X,    // 1G Fiber X SFP
    MEBA_SFP_TRANSRECEIVER_2G5,           // 2.5G Fiber SFP
    MEBA_SFP_TRANSRECEIVER_5G,            // 5G Fiber SFP
    MEBA_SFP_TRANSRECEIVER_10G,           // 10G Fiber SFP+
    MEBA_SFP_TRANSRECEIVER_10G_SR,        // 10G Fiber SFP+ short range (400m)
    MEBA_SFP_TRANSRECEIVER_10G_LR,        // 10G Fiber SFP+ long range (10km)
    MEBA_SFP_TRANSRECEIVER_10G_LRM,       // 10G Fiber SFP+ long range multimode (220m)
    MEBA_SFP_TRANSRECEIVER_10G_ER,        // 10G Fiber SFP+ extended range (40km)
    MEBA_SFP_TRANSRECEIVER_10G_DAC,       // 10G DAC SFP+ Cu
    MEBA_SFP_TRANSRECEIVER_25G,           // 25G Fiber SFP+
    MEBA_SFP_TRANSRECEIVER_25G_SR,        // 25G Fiber SFP+ short range (400m)
    MEBA_SFP_TRANSRECEIVER_25G_LR,        // 25G Fiber SFP+ long range (10km)
    MEBA_SFP_TRANSRECEIVER_25G_LRM,       // 25G Fiber SFP+ long range multimode (220m)
    MEBA_SFP_TRANSRECEIVER_25G_ER,        // 25G Fiber SFP+ extended range (40km)
    MEBA_SFP_TRANSRECEIVER_25G_DAC,       // 25G CR (DAC) SFP+ Cu
} meba_sfp_transreceiver_t;

// SFP connector types.
// Aligned with SFF-8024, rev 4.7, table 4-3.
typedef enum {
    MEBA_SFP_CONNECTOR_NONE       = 0x00, // Unknown or unspecified
    MEBA_SFP_CONNECTOR_SC         = 0x01, // Subscriber Conector
    MEBA_SFP_CONNECTOR_FC_STYLE_1 = 0x02, // Fiber Channel Style 1 Cu
    MEBA_SFP_CONNECTOR_FC_STYLE_2 = 0x03, // Fiber Channel Style 2 Cu
    MEBA_SFP_CONNECTOR_BNC_TNC    = 0x04, // Bayonet/Threaded Neill-Concelman
    MEBA_SFP_CONNECTOR_FC_COAX    = 0x05, // Fiber Channel Coax headers
    MEBA_SFP_CONNECTOR_FJ         = 0x06, // Fiber Jack
    MEBA_SFP_CONNECTOR_LC         = 0x07, // Lucent Connector
    MEBA_SFP_CONNECTOR_MT_RJ      = 0x08, // Mechanical transfer - Registered Jack
    MEBA_SFP_CONNECTOR_MU         = 0x09, // MUltiple Optical
    MEBA_SFP_CONNECTOR_SG         = 0x0A, // SG
    MEBA_SFP_CONNECTOR_OP         = 0x0B, // Optical Pigtail
    MEBA_SFP_CONNECTOR_MPO_1X12   = 0x0C, // Multifiber Parallel Optic 1x12
    MEBA_SFP_CONNECTOR_MPO_2X16   = 0x0D, // Multifiber Parallel Optic 2x16
    MEBA_SFP_CONNECTOR_HSSDC_II   = 0x20, // High Speed Serial Data Connector
    MEBA_SFP_CONNECTOR_CP         = 0x21, // Copper Pigtail (DAC)
    MEBA_SFP_CONNECTOR_RJ45       = 0x22, // Registered Jack
    MEBA_SFP_CONNECTOR_NO_SEP     = 0x23, // No separable connector
    MEBA_SFP_CONNECTOR_MXC_2X16   = 0x24, // MXC 2x16
    MEBA_SFP_CONNECTOR_CS         = 0x25, // CS optical connector
    MEBA_SFP_CONNECTOR_SN         = 0x26, // SN (previously Mini CS) optical connector
    MEBA_SFP_CONNECTOR_MPO_2X12   = 0x27, // Multifiber Parallel Optic 2x12
    MEBA_SFP_CONNECTOR_MPO_1X16   = 0x28, // Multifiber Parallel Optic 1x16
} meba_sfp_connector_t;

// Information about the SFP module
typedef struct sfp_device_info {
    char                     vendor_name[20]; // Vendor name
    char                     vendor_pn[20];   // Product name
    char                     vendor_rev[6];   // Revision number
    char                     vendor_sn[20];   // Serial number
    char                     date_code[9];    // Date code
    meba_sfp_transreceiver_t transceiver;     // Transceiver type
    meba_sfp_connector_t     connector;       // Connector type
} meba_sfp_device_info_t;

// Clears up the data allocated in the probe function.
typedef mesa_rc (*meba_sfp_driver_delete_t)(struct meba_sfp_device *dev);

// Resets SFP.
typedef mesa_rc (*meba_sfp_driver_reset_t)(struct meba_sfp_device *dev);

// Get the current status of the SFP.
// status        [OUT] SFP status.
typedef mesa_rc (*meba_sfp_driver_poll_t)(struct meba_sfp_device *dev,
                                          meba_sfp_driver_status_t *status);

// Set the configuration to the SFP.
// conf          [IN] Apply this configuration.
typedef mesa_rc (*meba_sfp_driver_conf_set_t)(
    struct meba_sfp_device *dev, const meba_sfp_driver_conf_t *conf);

// Get the SFP interface based on speed.
// speed         [IN] Speed.
// intf          [OUT] Interface that is needed to be used by the port.
typedef mesa_rc (*meba_sfp_driver_if_get_t)(struct meba_sfp_device *dev,
                                            mesa_port_speed_t speed,
                                            mesa_port_interface_t *intf);

// Get the media type used by SFP that support 10G speed.
// dev           [IN] Device.
// mt            [OUT] Media type.
typedef mesa_rc (*meba_sfp_driver_mt_get_t)(struct meba_sfp_device *dev,
                                            mesa_sd10g_media_type_t *mt);

// Get the transreceiver.
// tr            [OUT] Transreceiver type.
typedef mesa_rc (*meba_sfp_driver_tr_get_t)(struct meba_sfp_device *dev,
                                            meba_sfp_transreceiver_t *tr);

// Create an instance of the driver, and initialize the SFP module.
// dev           [IN] Device.
// addr          [IN] Address mode.
// info          [IN] Information about the SFP module
typedef struct meba_sfp_device *(*meba_sfp_driver_probe_t)(
    struct meba_sfp_driver *dev, const meba_sfp_driver_address_t *addr,
    const meba_sfp_device_info_t *info);

// Full list of the SFP driver interface
#define MEBA_LIST_OF_API_SFP_DRIVER_CALLS \
    X(meba_sfp_driver_delete)             \
    X(meba_sfp_driver_reset)              \
    X(meba_sfp_driver_poll)               \
    X(meba_sfp_driver_conf_set)           \
    X(meba_sfp_driver_if_get)             \
    X(meba_sfp_driver_mt_get)             \
    X(meba_sfp_driver_tr_get)             \
    X(meba_sfp_driver_probe)

typedef struct meba_sfp_driver {
    meba_sfp_driver_delete_t    meba_sfp_driver_delete;
    meba_sfp_driver_reset_t     meba_sfp_driver_reset;
    meba_sfp_driver_poll_t      meba_sfp_driver_poll;
    meba_sfp_driver_conf_set_t  meba_sfp_driver_conf_set;
    meba_sfp_driver_if_get_t    meba_sfp_driver_if_get;
    meba_sfp_driver_mt_get_t    meba_sfp_driver_mt_get;
    meba_sfp_driver_tr_get_t    meba_sfp_driver_tr_get;
    meba_sfp_driver_probe_t     meba_sfp_driver_probe;

    char *product_name;           // Each driver has different product name
    struct meba_sfp_driver *next; // Pointer to the next driver
} meba_sfp_driver_t;

// Represents the instance of the driver
typedef struct meba_sfp_device {
    meba_sfp_driver_t *drv;      // Pointer to the driver that creates the device
    void *data;                  // Private data, that can be different for each device
    meba_sfp_status_t sfp;       // SFP status
    meba_sfp_device_info_t info; // SFP device info from MSA ROM.
} meba_sfp_device_t;

// Wrapper over an array and counter. It is used
// by init functions to return the array of drivers
typedef struct meba_sfp_drivers {
    meba_sfp_driver_t *sfp_drv; // Pointer to an array of drivers
    unsigned int count;         // Number of entries in sfp_drv
} meba_sfp_drivers_t;

// Returns drivers for cisco SFP
meba_sfp_drivers_t meba_cisco_driver_init();

// Returns drivers for axcen SFP
meba_sfp_drivers_t meba_axcen_driver_init();

// Returns drivers for finisar SFP
meba_sfp_drivers_t meba_finisar_driver_init();

// Returns drivers for hp SFP
meba_sfp_drivers_t meba_hp_driver_init();

// Returns drivers for d_link SFP
meba_sfp_drivers_t meba_d_link_driver_init();

// Returns drivers for oem SFP
meba_sfp_drivers_t meba_oem_driver_init();

// Returns drivers for wavesplitter SFP
meba_sfp_drivers_t meba_wavesplitter_driver_init();

// Returns drivers for avago SFP
meba_sfp_drivers_t meba_avago_driver_init();

// Returns drivers for excom SFP
meba_sfp_drivers_t meba_excom_driver_init();

// Returns drivers for MAC-to-MAC connection.
meba_sfp_drivers_t meba_mac_to_mac_driver_init();

// Returns drivers for FS
meba_sfp_drivers_t meba_fs_driver_init();

// Let's the driver to detect which functions need to set based on the rom
// memory. device_info is filled with device-specific info on successful exit.
mesa_bool_t meba_fill_driver(struct meba_inst       *meba_inst,
                             mesa_port_no_t         port_no,
                             meba_sfp_driver_t      *driver,
                             meba_sfp_device_info_t *device_info);

// Read the SFP ROM and return device-specific info.
mesa_bool_t meba_sfp_device_info_get(struct meba_inst       *meba_inst,
                                     mesa_port_no_t         port_no,
                                     meba_sfp_device_info_t *device_info);

#include <microchip/ethernet/board/api/hdr_end.h>
#endif

