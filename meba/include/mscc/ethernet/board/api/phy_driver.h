/*
 Copyright (c) 2004-2018 Microsemi Corporation "Microsemi".

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

#ifndef _MSCC_ETHERNET_BOARD_PHY_DRIVER_H_
#define _MSCC_ETHERNET_BOARD_PHY_DRIVER_H_

#include <mscc/ethernet/board/api/base.h>
#include <mscc/ethernet/switch/api.h>

/**
 * \file
 * \brief PHY DRIVER
 *
 * \details This API defines the interface used by the switch application
 * to interact with the PHY. Using this interface the switch application
 * should not know which PHY it is using.
 *
 * Each PHY driver needs to implement the following methods for a minimum
 * configuration:
 *  meba_phy_driver_delete_t
 *  meba_phy_driver_probe_t
 *  meba_phy_driver_poll_t
 *  meba_phy_driver_conf_set_t
 **/

/** \brief Contains methods that are specific to each phy. */
struct meba_phy_driver;
/** \brief Represents an instance of the meba_phy_driver. */
struct meba_phy_device;

/** \brief Function prototype for MMD read */
typedef mesa_rc (*mmd_read_t)(const mesa_inst_t  inst,
                           const mesa_port_no_t  port_no,
                           const uint8_t         mmd,
                           const uint16_t        addr,
                           uint16_t              *const value);

/** \brief Function prototype for MMD write */
typedef mesa_rc (*mmd_write_t)(const mesa_inst_t  inst,
                            const mesa_port_no_t  port_no,
                            const uint8_t         mmd,
                            const uint16_t        addr,
                            const uint16_t        value);

/** \brief Function prototype for MIIM read */
typedef mesa_rc (*miim_read_t)(const mesa_inst_t    inst,
                       const mesa_chip_no_t         chip_no,
                       const mesa_miim_controller_t miim_controller,
                       const uint8_t                miim_addr,
                       const uint8_t                addr,
                       uint16_t                     *const value);

/** \brief Function prototype for MIIM write */
typedef mesa_rc (*miim_write_t)(const mesa_inst_t    inst,
                        const mesa_chip_no_t         chip_no,
                        const mesa_miim_controller_t miim_controller,
                        const uint8_t                miim_addr,
                        const uint8_t                addr,
                        const uint16_t               value);

/** \brief Function prototype for debug trace */
typedef void (*debug_func_t)(meba_trace_level_t level,
                        const char              *location,
                        uint32_t                line_no,
                        const char              *fmt,
                        ...);

/** \brief Address mode that is specific for mscc phy. */
typedef struct {
    mmd_read_t mmd_read;        /**< MMD read function pointer */
    mmd_write_t mmd_write;      /**< MMD write function pointer */
    miim_read_t miim_read;      /**< MIIM read function pointer */
    miim_write_t miim_write;    /**< MIIM write function pointer */
    mesa_inst_t inst;           /**< Mesa instance */
    mesa_port_no_t port_no;     /**< Port no */
    meba_inst_t meba_inst;      /**< Meba instance */
    debug_func_t debug_func;    /**< Debug function */
} mscc_phy_driver_address_t;

/** \brief Union that contains all the values for address mode.
 * Enumeration meba_phy_driver_address_mode_t decides which
 * address type to be used. */
typedef union {
    mscc_phy_driver_address_t mscc_address;     /**< Address mode for mscc */
} meba_phy_driver_address_val_t;

/** \brief Enumeration of all possible address modes. */
typedef enum {
    mscc_phy_driver_address_mode,  /**< Mscc address mode */
} meba_phy_driver_address_mode_t;

/** \brief Main structure that contains the address mode and the address value,
 * these values has to be filled up by the switch application. */
typedef struct meba_phy_driver_address {
    meba_phy_driver_address_mode_t mode; /**< Decides which val to be used */
    meba_phy_driver_address_val_t val;   /**< Contains one address value */
} meba_phy_driver_address_t;

/** \brief Represents the status of the PHY. */
typedef struct {
    mesa_bool_t link;        /**< Link is up */
    mesa_port_speed_t speed; /**< Speed */
    mesa_bool_t fdx;         /**< Full duplex */
    mesa_aneg_t aneg;        /**< Auto-negotiation */
    mesa_bool_t copper;      /**< For dual-media ports */
    mesa_bool_t fiber;       /**< For dual-media ports */
} meba_phy_driver_status_t;

/** \brief Represents the configuration that is applied to PHY. */
typedef struct {
    mesa_port_speed_t speed;       /**< Forced port speed */
    mesa_bool_t fdx;               /**< Forced duplex mode */
    mesa_bool_t flow_control;      /**< Flow control (Standard 802.3x) */
    uint32_t adv_dis;              /**< Auto neg advertisement disable */
    meba_port_admin_state_t admin; /**< Admin state */
} meba_phy_driver_conf_t;

/** \brief Advertise disable flags. */
typedef enum {
    MEBA_PHY_ADV_DIS_HDX = 0x00000001,     /**< Disable Half duplex */
    MEBA_PHY_ADV_DIS_FDX = 0x00000002,     /**< Disable Full duplex */
    MEBA_PHY_ADV_UP_MEP_LOOP = 0x00000004, /**< Use port for UP MEP loop port */
    MEBA_PHY_ADV_DIS_2500M = 0x00000008,   /**< Disable 2.5G mode */
    MEBA_PHY_ADV_DIS_1G = 0x00000010,      /**< Disable 1G mode */
    MEBA_PHY_ADV_DIS_100M = 0x00000040,    /**< Disable 100Mbit mode */
    MEBA_PHY_ADV_DIS_10M = 0x00000080,     /**< Disable 10Mbit mode */
    MEBA_PHY_ADV_DIS_5G = 0x00000100,      /**< Disable 5G mode */
    MEBA_PHY_ADV_DIS_10G = 0x00000200,     /**< Disable 10G mode */
    MEBA_PHY_ADV_DIS_RESTART_ANEG = 0x00000400, /**< Do not restart aneg */
    MEBA_PHY_ADV_DIS_SPEED =
        (MEBA_PHY_ADV_DIS_10M | MEBA_PHY_ADV_DIS_100M | MEBA_PHY_ADV_DIS_1G |
         MEBA_PHY_ADV_DIS_2500M | MEBA_PHY_ADV_DIS_5G |
         MEBA_PHY_ADV_DIS_10G), /**< All speed bits */
    MEBA_PHY_ADV_DIS_DUPLEX =
        (MEBA_PHY_ADV_DIS_HDX | MEBA_PHY_ADV_DIS_FDX), /**< All duplex bits*/
    MEBA_PHY_ADV_DIS_ALL = (MEBA_PHY_ADV_DIS_SPEED | MEBA_PHY_ADV_DIS_DUPLEX |
                            MEBA_PHY_ADV_UP_MEP_LOOP) /**< All valid bits */
} meba_phy_adv_dis_t;

/**
 * \brief Clears up the data allocated in the probe function.
 *
 * \param dev           [IN] Device.
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_phy_driver_delete_t)(struct meba_phy_device *dev);

/**
 * \brief Resets PHY.
 *
 * \param dev           [IN] Device.
 * \param intf          [IN] Interface to which to reset the phy.
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_phy_driver_reset_t)(struct meba_phy_device *dev,
                                           mesa_phy_media_interface_t intf);

/**
 * \brief Get the current status of the PHY.
 *
 * \param dev           [IN] Device.
 * \param status        [OUT] PHY status.
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_phy_driver_poll_t)(struct meba_phy_device *dev,
                                          meba_phy_driver_status_t *status);

/**
 * \brief Set the configuration to the PHY.
 *
 * \param dev           [IN] Device.
 * \param cap           [IN] Port capabilities.
 * \param conf          [IN] PHY configuration.
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_phy_driver_conf_set_t)(
    struct meba_phy_device *dev, meba_port_cap_t cap,
    const meba_phy_driver_conf_t *conf);

/**
 * \brief Ge the PHY interface bsed on speed.
 *
 * \param dev           [IN] Device.
 * \param speed         [IN] Speed.
 * \param intf          [OUT] Interface that is needed to be used by the port.
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_phy_driver_if_get_t)(struct meba_phy_device *dev,
                                            mesa_port_speed_t speed,
                                            mesa_port_interface_t *intf);

/**
 * \brief Get the media type used by PHY that supports 10G speed.
 *
 * \param dev           [IN] Device.
 * \param mt            [OUT] Media type.
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_phy_driver_mt_get_t)(struct meba_phy_device *dev,
                                            mesa_sd10g_media_type_t *mt);

/**
 * \brief Sets the power mode.
 *
 * \param dev           [IN] Device.
 * \param power         [IN] Power.
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_phy_driver_power_set_t)(struct meba_phy_device *dev,
                                               mesa_phy_power_mode_t power);

/**
 * \brief Starts veriphy.
 *
 * \param dev           [IN] Device.
 * \param mode          [IN] Mode in which to start.
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_phy_driver_veriphy_start_t)(struct meba_phy_device *,
                                                   int mode);
/**
 * \brief Gets result from veriphy.
 *
 * \param dev           [IN] Device
 * \param result        [OUT] Result from veriphy.
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_phy_driver_veriphy_get_t)(
    struct meba_phy_device *dev, mesa_phy_veriphy_result_t *result);

/**
 * \brief Sets the media type in case the port is a dual media port with
 * external phy.
 *
 * \param dev           [IN] Device.
 * \param phy_media_if  [IN] Media type.
 *
 * \return Return code.
 **/
typedef mesa_rc (*meba_phy_driver_media_set_t)(
    struct meba_phy_device *dev, mesa_phy_media_interface_t phy_media_if);

/**
 * \brief Create an instance of the driver and initialize the PHY.
 *
 * \param dev            [IN] Device.
 * \param mode           [IN] Address mode.
 *
 * \return Return code.
 **/
typedef struct meba_phy_device *(*meba_phy_driver_probe_t)(
    struct meba_phy_driver *dev, const meba_phy_driver_address_t *mode);

/**
 * \brief Gets PHY 1G status.
 * 
 * \param dev            [IN] Device.
 * \param mode           [IN] PHY 1G status.
 * 
 * \return Return code.
 **/
typedef mesa_rc (*meba_phy_driver_status_1g_get_t)(
    struct meba_phy_device *dev, mesa_phy_status_1g_t *status);

/**
 * \brief Full list of PHY driver interface
 **/
#define MEBA_LIST_OF_API_PHY_DRIVER_CALLS \
    X(meba_phy_driver_delete)             \
    X(meba_phy_driver_reset)              \
    X(meba_phy_driver_poll)               \
    X(meba_phy_driver_conf_set)           \
    X(meba_phy_driver_if_get)             \
    X(meba_phy_driver_mt_get)             \
    X(meba_phy_driver_power_set)          \
    X(meba_phy_driver_veriphy_start)      \
    X(meba_phy_driver_veriphy_get)        \
    X(meba_phy_driver_media_set)          \
    X(meba_phy_driver_probe)              \
    X(meba_phy_driver_status_1g_get)    

/**
 * \brief Driver functions struct
 **/
typedef struct meba_phy_driver {
/**
 * \brief Fill up the struct with function pointers
 **/
#define X(name) name##_t name;
    MEBA_LIST_OF_API_PHY_DRIVER_CALLS
#undef X

    uint32_t id;                  /**< Id of the driver */
    uint32_t mask;                /**< Mask of the driver */
    struct meba_phy_driver *next; /**< Pointer to the next driver */
} meba_phy_driver_t;

/**
 * \brief Represents the instance of the driver
 **/
typedef struct meba_phy_device {
    /** Pointer to the driver that creates the device */
    meba_phy_driver_t *drv;

    /** Private data */
    void *data;
} meba_phy_device_t;

/**
 * \brief Wrapper over an array and counter. It is used
 * by init functions to return the array of drivers
 **/
typedef struct meba_phy_drivers {
    meba_phy_driver_t *phy_drv; /**< Pointer to an array of drivers */
    unsigned int count;         /**< Number of entries in phy_drv */
} meba_phy_drivers_t;

/**
 * \brief Default driver that match any PHY
 */
meba_phy_drivers_t meba_default_phy_driver_init();

/**
 * \brief Returns drivers for mscc PHY
 */
meba_phy_drivers_t meba_mscc_driver_init();

/**
 * \brief Returns drivers for malibu PHY
 */
meba_phy_drivers_t meba_malibu_driver_init();

/**
 * \brief Returns drivers for venice PHY
 */
meba_phy_drivers_t meba_venice_driver_init();

#endif
