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

#ifndef _MSCC_ETHERNET_SWITCH_API_MISC_
#define _MSCC_ETHERNET_SWITCH_API_MISC_

#include <stdarg.h>
#include <mscc/ethernet/switch/api/types.h>
#include <mscc/ethernet/switch/api/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

/** \brief Trace group layer */
typedef enum
{
    MESA_TRACE_LAYER_AIL,   /**< Application Interface Layer */
    MESA_TRACE_LAYER_CIL,   /**< Chip Interface Layer */

    MESA_TRACE_LAYER_COUNT  /**< Number of layers */
} mesa_trace_layer_t;

/** \brief Trace groups */
typedef enum
{
    MESA_TRACE_GROUP_DEFAULT,       /**< Default trace group */
    MESA_TRACE_GROUP_PORT,          /**< Port control */
    MESA_TRACE_GROUP_PHY,           /**< PHY control */
    MESA_TRACE_GROUP_PACKET,        /**< Packet control */
    MESA_TRACE_GROUP_AFI,           /**< AFI */
    MESA_TRACE_GROUP_QOS,           /**< Quality of Service */
    MESA_TRACE_GROUP_L2,            /**< Layer 2 */
    MESA_TRACE_GROUP_L3,            /**< Layer 3 */
    MESA_TRACE_GROUP_SECURITY,      /**< Security */
    MESA_TRACE_GROUP_EVC,           /**< Ethernet Virtual Connections */
    MESA_TRACE_GROUP_FDMA_NORMAL,   /**< (Obsoleted group) */
    MESA_TRACE_GROUP_FDMA_IRQ,      /**< (Obsoleted group) */
    MESA_TRACE_GROUP_REG_CHECK,     /**< (Obsoleted group) */
    MESA_TRACE_GROUP_MPLS,          /**< MPLS */
    MESA_TRACE_GROUP_HW_PROT,       /**< HW Protection */
    MESA_TRACE_GROUP_HQOS,          /**< Hierarchical Quality of Service */
    MESA_TRACE_GROUP_MACSEC,        /**< MACSEC control */
    MESA_TRACE_GROUP_VCAP,          /**< VCAP */
    MESA_TRACE_GROUP_OAM,           /**< OAM */
    MESA_TRACE_GROUP_TS,            /**< Timestamping */
    MESA_TRACE_GROUP_CLOCK,         /**< Synce Clock */
    MESA_TRACE_GROUP_EMUL,          /**< Emulation */

    MESA_TRACE_GROUP_COUNT          /**< Number of trace groups */
} mesa_trace_group_t;

/** \brief Trace levels */
typedef enum
{
    MESA_TRACE_LEVEL_NONE,  /**< No trace */
    MESA_TRACE_LEVEL_ERROR, /**< Error trace */
    MESA_TRACE_LEVEL_INFO,  /**< Information trace */
    MESA_TRACE_LEVEL_DEBUG, /**< Debug trace */
    MESA_TRACE_LEVEL_NOISE, /**< More debug information */

    MESA_TRACE_LEVEL_COUNT  /**< Number of trace levels */
} mesa_trace_level_t;

/** \brief Trace group configuration */
typedef struct
{
    mesa_trace_level_t level[MESA_TRACE_LAYER_COUNT]; /**< Trace level per layer */
} mesa_trace_conf_t;

/**
 * \brief Get trace configuration
 *
 * \param group [IN]  Trace group
 * \param conf [OUT]  Trace group configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_trace_conf_get(const mesa_trace_group_t  group,
                            mesa_trace_conf_t         *const conf);


/**
 * \brief Set trace configuration
 *
 * \param group [IN]  Trace group
 * \param conf [IN]   Trace group configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_trace_conf_set(const mesa_trace_group_t  group,
                            const mesa_trace_conf_t   *const conf);


#if defined(__GNUC__) && (__GNUC__ > 2)
#define MESA_ATTR_PRINTF(X, Y) __attribute__ ((format(printf,X,Y)))
#else
#define MESA_ATTR_PRINTF(X, Y)
#endif


/**
 * \brief Trace callout function
 *
 * \param layer [IN]     Trace layer
 * \param group [IN]     Trace group
 * \param level [IN]     Trace level
 * \param file [IN]      File name string
 * \param line [IN]      Line number in file
 * \param function [IN]  Function name string
 * \param format [IN]    Print format string
 *
 * \return Nothing.
 **/
void mesa_callout_trace_printf(const mesa_trace_layer_t  layer,
                               const mesa_trace_group_t  group,
                               const mesa_trace_level_t  level,
                               const char                *file,
                               const int                 line,
                               const char                *function,
                               const char                *format,
                               va_list                   args);

/**
 * \brief Trace hex-dump callout function
 *
 * \param layer [IN]     Trace layer
 * \param group [IN]     Trace group
 * \param level [IN]     Trace level
 * \param file [IN]      The file from where the trace were called.
 * \param line [IN]      The line from where the trace were called.
 * \param function [IN]  The function from where the trace were called.
 * \param byte_p [IN]    Pointer to start of area to print
 * \param byte_cnt [IN]  Number of bytes to print
 *
 * \return Nothing.
 **/
void mesa_callout_trace_hex_dump(const mesa_trace_layer_t layer,
                                 const mesa_trace_group_t group,
                                 const mesa_trace_level_t level,
                                 const char               *file,
                                 const int                line,
                                 const char               *function,
                                 const uint8_t            *byte_p,
                                 const int                byte_cnt);

/** \brief Debug layer */
/* Debug layer */
typedef enum {
    MESA_DEBUG_LAYER_ALL, /**< All layers */
    MESA_DEBUG_LAYER_AIL, /**< Application Interface Layer */
    MESA_DEBUG_LAYER_CIL  /**< Chip Interface Layer */
} mesa_debug_layer_t;

/** \brief Debug function group */
typedef enum {
    MESA_DEBUG_GROUP_ALL,       /**< All groups */
    MESA_DEBUG_GROUP_INIT,      /**< Initialization */
    MESA_DEBUG_GROUP_MISC,      /**< Miscellaneous */
    MESA_DEBUG_GROUP_PORT,      /**< Port configuration */
    MESA_DEBUG_GROUP_PORT_CNT,  /**< Port counters */
    MESA_DEBUG_GROUP_PHY,       /**< PHY */
    MESA_DEBUG_GROUP_VLAN,      /**< VLAN */
    MESA_DEBUG_GROUP_PVLAN,     /**< PVLAN */
    MESA_DEBUG_GROUP_MAC_TABLE, /**< MAC address table */
    MESA_DEBUG_GROUP_ACL,       /**< ACL */
    MESA_DEBUG_GROUP_QOS,       /**< QoS */
    MESA_DEBUG_GROUP_AGGR,      /**< Link aggregation */
    MESA_DEBUG_GROUP_GLAG,      /**< Global link aggregation */
    MESA_DEBUG_GROUP_STP,       /**< Spanning Tree */
    MESA_DEBUG_GROUP_MIRROR,    /**< Mirroring */
    MESA_DEBUG_GROUP_EVC,       /**< EVC */
    MESA_DEBUG_GROUP_ERPS,      /**< ERPS */
    MESA_DEBUG_GROUP_EPS,       /**< EPS */
    MESA_DEBUG_GROUP_SR,        /**< Seamless Redundancy */
    MESA_DEBUG_GROUP_PACKET,    /**< Packet control */
    MESA_DEBUG_GROUP_FDMA,      /**< Obsoleted */
    MESA_DEBUG_GROUP_TS,        /**< TS: TimeStamping */
    MESA_DEBUG_GROUP_PHY_TS,    /**< PHY_TS: PHY TimeStamping */
    MESA_DEBUG_GROUP_WM,        /**< WaterMarks */
    MESA_DEBUG_GROUP_LRN,       /**< DEPRECATED. Use MESA_DEBUG_GROUP_MAC_TABLE instead */
    MESA_DEBUG_GROUP_IPMC,      /**< IP Multicast */
    MESA_DEBUG_GROUP_STACK,     /**< Stacking */
    MESA_DEBUG_GROUP_CMEF,      /**< Congestion Management */
    MESA_DEBUG_GROUP_HOST,      /**< CE-MAX Host configuration */
    MESA_DEBUG_GROUP_MPLS,      /**< MPLS */
    MESA_DEBUG_GROUP_HW_PROT,   /**< Hardware Protection */
    MESA_DEBUG_GROUP_HQOS,      /**< Hierarchical Quality of Service */
    MESA_DEBUG_GROUP_VXLAT,     /**< VLAN Translation */
    MESA_DEBUG_GROUP_OAM,       /**< OAM, incl. VOEs/VOP */
    MESA_DEBUG_GROUP_SER_GPIO,  /**< Serial GPIO configuration */
    MESA_DEBUG_GROUP_L3,        /**< L3 services */
    MESA_DEBUG_GROUP_AFI,       /**< Automatic Frame Injector */
    MESA_DEBUG_GROUP_MACSEC,    /**< 802.1AE MacSec */

    /* New groups are added above this line */
    MESA_DEBUG_GROUP_COUNT      /**< Number of groups */
} mesa_debug_group_t;


/** \brief Special chip number value for showing information from all chips */
#define MESA_CHIP_NO_ALL 0xffffffff

/** \brief Debug information structure */
typedef struct {
    mesa_debug_layer_t layer;      /**< Layer */
    mesa_debug_group_t group;      /**< Function group */
    mesa_chip_no_t     chip_no;    /**< Chip number, multi-chip targets */
    mesa_port_list_t   port_list;  /**< Port list */
    mesa_bool_t        full;       /**< Full information dump */
    mesa_bool_t        clear;      /**< Clear counters */
    mesa_bool_t        vml_format; /**< VML format register dump */
    mesa_bool_t        has_action; /**< Action parameter is present */
    uint32_t           action;     /**< Debug group depending action value */
} mesa_debug_info_t;

/** \brief Debug printf function
 *
 * The signature is similar to that of printf(). However, the return value is
 * not used anywhere within MESA.
 */
typedef int (*mesa_debug_printf_t)(const char *fmt, ...) MESA_ATTR_PRINTF(1, 2);

/**
 * \brief Get default debug information structure
 *
 * \param info [OUT]  Debug information
 *
 * \return Return code.
 **/
mesa_rc mesa_debug_info_get(mesa_debug_info_t *const info);

/**
 * \brief Print default information
 *
 * \param inst [IN]   Target instance reference.
 * \param prntf [IN]  Debug printf function.
 * \param info [IN]   Debug information
 *
 * \return Return code.
 **/
mesa_rc mesa_debug_info_print(const mesa_inst_t         inst,
                              const mesa_debug_printf_t prntf,
                              const mesa_debug_info_t   *const info);

/* - API protection functions -------------------------------------- */

/** \brief API lock structure */
typedef struct {
    mesa_inst_t inst;     /**< Target instance reference */
    const char *function; /**< Function name */
    const char *file;     /**< File name */
    int        line;      /**< Line number */
} mesa_api_lock_t;

/**
 * \brief Lock API access
 *
 * \param lock [IN]  Lock information
*/
void mesa_callout_lock(const mesa_api_lock_t *const lock);

/**
 * \brief Unlock API access
 *
 * \param lock [IN]  Lock information
*/
void mesa_callout_unlock(const mesa_api_lock_t *const lock);

/** \brief API debug lock structure */
typedef struct {
    mesa_chip_no_t chip_no; /**< Chip number (if multi-chip instance). */
} mesa_debug_lock_t;

/**
 * \brief Debug lock API access
 *
 * \param inst [IN]  Target instance reference.
 * \param lock [IN]  Lock information
 *
 * \return Return code.
*/
mesa_rc mesa_debug_lock(const mesa_inst_t       inst,
                        const mesa_debug_lock_t *const lock);

/**
 * \brief Debug unlock API access
 *
 * \param inst [IN]  Target instance reference.
 * \param lock [IN]  Lock information
 *
 * \return Return code.
*/
mesa_rc mesa_debug_unlock(const mesa_inst_t inst,
                          mesa_debug_lock_t *const lock);

/* - Direct register access (for debugging only) ------------------- */

/**
 * \brief Read value from target register.
 *
 * \param inst [IN]     Target instance reference.
 * \param chip_no [IN]  Chip number (if multi-chip instance).
 * \param addr [IN]     Address to read. Format depends on target.
 * \param value [OUT]   Register value.
 *
 * \return Return code.
 **/
mesa_rc mesa_reg_read(const mesa_inst_t    inst,
                      const mesa_chip_no_t chip_no,
                      const uint32_t       addr,
                      uint32_t             *const value);


/**
 * \brief Write value to target register.
 *
 * \param inst [IN]     Target instance reference.
 * \param chip_no [IN]  Chip number (if multi-chip instance).
 * \param addr [IN]     Address to read. Format depends on target.
 * \param value [IN]    Register value.
 *
 * \return Return code.
 **/
mesa_rc mesa_reg_write(const mesa_inst_t    inst,
                       const mesa_chip_no_t chip_no,
                       const uint32_t       addr,
                       const uint32_t       value);


/**
 * \brief Read, modify and write value to target register.
 *
 * \param inst [IN]     Target instance reference.
 * \param chip_no [IN]  Chip number (if multi-chip instance).
 * \param addr [IN]     Address to read. Format depends on target.
 * \param value [IN]    Register value.
 * \param mask [IN]     Register mask, only bits enabled are changed.
 *
 * \return Return code.
 **/
mesa_rc mesa_reg_write_masked(const mesa_inst_t    inst,
                              const mesa_chip_no_t chip_no,
                              const uint32_t       addr,
                              const uint32_t       value,
                              const uint32_t       mask);

/* - Secondary chip if ------------------- */

/**
 * \brief Clear EXT0-1 interrupt sticky bits on secondary chip.
 *
 * \param inst [IN]    Target instance reference.
 * \param ext [IN]     EXT number (0-1).
 *
 * \return Return code.
 **/
mesa_rc mesa_intr_sticky_clear(const mesa_inst_t inst,
                               uint32_t          ext);

/* - Chip ID and revision ------------------------------------------ */

/** \brief Chip ID */
typedef struct
{
    uint16_t part_number; /**< BCD encoded part number */
    uint16_t revision;    /**< Chip revision */
} mesa_chip_id_t;

/**
 * \brief Get chip ID and revision.
 *
 * \param inst [IN]     Target instance reference.
 * \param chip_id [IN]  Pointer to chip ID structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_chip_id_get(const mesa_inst_t  inst,
                         mesa_chip_id_t     *const chip_id);


/* - Polling functions ---------------------------------------- */

/**
 * \brief Polling function called every second.
 *
 * \param inst [IN]  Target instance reference.
 *
 * \return Return code.
 **/
mesa_rc mesa_poll_1sec(const mesa_inst_t inst);

/**
 * \brief Define event (interrupt) types relatesd to PTP in the switch chips
 *
 **/
typedef enum {
    MESA_PTP_SYNC_EV =      (1 << 0), /*< PTP Synchronization pulse update */
    MESA_PTP_EXT_SYNC_EV =  (1 << 1), /*< PTP External Synchronization input  (Sync 0 on Serval)*/
    MESA_PTP_CLK_ADJ_EV =   (1 << 2), /*< PTP Clock adjustment updated */
    MESA_PTP_TX_TSTAMP_EV = (1 << 3), /*< Tx timestamp udated (Jaguar and Serval only)*/
    MESA_PTP_EXT_1_SYNC_EV =(1 << 4), /*< PTP External Synchronization 1 input (Serval only)*/
    MESA_PTP_PIN_0_SYNC_EV =(1 << 5), /*< PTP External pin 0 synchronization (Jaguar2 only)*/
    MESA_PTP_PIN_1_SYNC_EV =(1 << 6), /*< PTP External pin 1 synchronization (Jaguar2 only)*/
    MESA_PTP_PIN_2_SYNC_EV =(1 << 7), /*< PTP External pin 2 synchronization (Jaguar2 only)*/
    MESA_PTP_PIN_3_SYNC_EV =(1 << 8), /*< PTP External pin 3 synchronization (Jaguar2 only)*/
} mesa_ptp_event_type_t;

/**
 * \brief PTP polling function called at by interrupt or periodicly
 *
 * \param inst       [IN]  Target instance reference.
 * \param ev_mask    [OUT] Event type mask of active events
 *
 * \note The \e ev_mask parameter can be either a single event_type or
 * multiple event types (or \e MESA_EVTYPE_ALL). If invoked by a
 * processor interrupt signal, the type of event to check for may be
 * narrowed in to specific events.
 *
 * \return Return code.
 **/
mesa_rc mesa_ptp_event_poll(const mesa_inst_t      inst,
                            mesa_ptp_event_type_t  *const ev_mask);

/**
 * \brief Enable PTP event generation for a specific event type
 *
 * \param inst     [IN] Target instance reference.
 * \param enable   [IN] Enable or disable events
 * \param ev_mask  [IN] Event type(s) to control (mask)
 *
 * \return Return code.
 **/
mesa_rc mesa_ptp_event_enable(const mesa_inst_t            inst,
                              const mesa_ptp_event_type_t  ev_mask,
                              const mesa_bool_t            enable);

/**
 * \brief Define the dev_all event (interrupt) types
 *
 **/
typedef enum {
    MESA_DEV_ALL_TX_TSTAMP_EV = (1 << 0), /*< Tx timestamp udated */
    MESA_DEV_ALL_LINK_EV =      (1 << 1), /*< Link state changed */
} mesa_dev_all_event_type_t;

/**
 * \brief Define the dev_all polling types
 *
 **/
typedef enum {
    MESA_DEV_ALL_POLL_ALL,          /*< Polling all chip */
    MESA_DEV_ALL_POLL_PRIMARY,      /*< Polling primary chip */
    MESA_DEV_ALL_POLL_SECONDARY,    /*< Polling secondary chip */
} mesa_dev_all_event_poll_t;

/**
 * \brief DEV_ALL polling function called at by interrupt or periodically
 *
 * \param inst      [IN] Target instance reference.
 * \param poll_type [IN] Polling type
 * \param ev_mask   [OUT] Event type mask array of active events for all ports - must be of size MESA_PORT_ARRAY_SIZE
 *
 * \note The \e ev_mask parameter can be either a single event_type or
 * multiple event types (or \e MESA_EVTYPE_ALL). If invoked by a
 * processor interrupt signal, the type of event to check for may be
 * narrowed in to specific events.
 *
 * \return Return code.
 **/
mesa_rc mesa_dev_all_event_poll(const mesa_inst_t                 inst,
                                const mesa_dev_all_event_poll_t   poll_type,
                                mesa_dev_all_event_type_t         *const ev_mask);

/**
 * \brief Enable DEV_ALL event generation for a specific event type
 *
 * \param inst     [IN] Target instance reference.
 * \param port_no  [IN] Port number.
 * \param enable   [IN] Enable or disable events.
 * \param ev_mask  [IN] Event type(s) to control (mask).
 *
 * \return Return code.
 **/
mesa_rc mesa_dev_all_event_enable(const mesa_inst_t                inst,
                                  const mesa_port_no_t             port_no,
                                  const mesa_dev_all_event_type_t  ev_mask,
                                  const mesa_bool_t                enable);

/* - GPIOs --------------------------------------------------------- */

/** \brief GPIO number */
typedef uint32_t mesa_gpio_no_t;

/** \brief GPIO start number */
#define MESA_GPIO_NO_START 0

/** \brief GPIO end number */
#define MESA_GPIO_NO_END   (MESA_GPIO_NO_START+MESA_GPIOS)

/**
 * \brief GPIO configured mode
 **/
typedef enum
{
    MESA_GPIO_OUT,    /**< Output enabled */
    MESA_GPIO_IN,     /**< Input enabled */
    MESA_GPIO_IN_INT, /**< Input enabled, IRQ gated */
    MESA_GPIO_ALT_0,  /**< Alternate function 0 */
    MESA_GPIO_ALT_1,  /**< Alternate function 1 */
    MESA_GPIO_ALT_2,  /**< Alternate function 2 */
} mesa_gpio_mode_t;

/**
 * \brief Set GPIO mode.
 *
 * \param inst [IN]     Target instance reference.
 * \param chip_no [IN]  Chip number (if multi-chip instance).
 * \param gpio_no [IN]  GPIO pin number.
 * \param mode [IN]     GPIO mode.
 *
 * \return Return code.
 **/
mesa_rc mesa_gpio_mode_set(const mesa_inst_t      inst,
                           const mesa_chip_no_t   chip_no,
                           const mesa_gpio_no_t   gpio_no,
                           const mesa_gpio_mode_t mode);

/**
 * \brief Set GPIO direction to input or output.
 *
 * \param inst [IN]     Target instance reference.
 * \param chip_no [IN]  Chip number (if multi-chip instance).
 * \param gpio_no [IN]  GPIO pin number.
 * \param output [IN]   TRUE if output, FALSE if input.
 *
 * \return Return code.
 *
 * \em DEPRECATED. Use mesa_gpio_mode_set() instead.
 **/
mesa_rc mesa_gpio_direction_set(const mesa_inst_t     inst,
                                const mesa_chip_no_t  chip_no,
                                const mesa_gpio_no_t  gpio_no,
                                const mesa_bool_t     output);



/**
 * \brief Read from GPIO input pin.
 *
 * \param inst [IN]     Target instance reference.
 * \param chip_no [IN]  Chip number (if multi-chip instance).
 * \param gpio_no [IN]  GPIO pin number.
 * \param value [OUT]   TRUE if pin is high, FALSE if it is low.
 *
 * \return Return code.
 **/
mesa_rc mesa_gpio_read(const mesa_inst_t     inst,
                       const mesa_chip_no_t  chip_no,
                       const mesa_gpio_no_t  gpio_no,
                       mesa_bool_t           *const value);



/**
 * \brief Write to GPIO output pin.
 *
 * \param inst [IN]     Target instance reference.
 * \param chip_no [IN]  Chip number (if multi-chip instance).
 * \param gpio_no [IN]  GPIO pin number.
 * \param value [IN]    TRUE to set pin high, FALSE to set pin low.
 *
 * \return Return code.
 **/
mesa_rc mesa_gpio_write(const mesa_inst_t     inst,
                        const mesa_chip_no_t  chip_no,
                        const mesa_gpio_no_t  gpio_no,
                        const mesa_bool_t     value);

/**
 * \brief Get GPIO event indication
 *
 * \param inst [IN]         Target instance reference.
 * \param chip_no [IN]      Chip number (if multi-chip instance).
 * \param events [OUT]      Event indication for each GPIO pin - must point to MESA_GPIOS of mesa_bool_t.
 *
 * \return Return code.
 **/
mesa_rc mesa_gpio_event_poll(const mesa_inst_t        inst,
                             const mesa_chip_no_t     chip_no,
                             mesa_bool_t              *const events);

/**
 * \brief Set GPIO event enable
 *
 * \param inst [IN]         Target instance reference.
 * \param chip_no [IN]      Chip number (if multi-chip instance).
 * \param gpio_no [IN]      GPIO pin number.
 * \param enable  [IN]      Enable or disable event.
 *
 * \return Return code.
 **/
mesa_rc mesa_gpio_event_enable(const mesa_inst_t       inst,
                               const mesa_chip_no_t    chip_no,
                               const mesa_gpio_no_t    gpio_no,
                               mesa_bool_t             enable);

/* - Serial GPIO control ---------------------------------------------------- */

/** \brief Serial GPIO group */
typedef uint32_t mesa_sgpio_group_t;

/** \brief Number of serial GPIO ports */
#define MESA_SGPIO_PORTS 32

/** \brief SGPIO output mode */
typedef enum
{
    MESA_SGPIO_MODE_OFF,            /**< Off */
    MESA_SGPIO_MODE_ON,             /**< On */
    MESA_SGPIO_MODE_0,              /**< Mode 0 */
    MESA_SGPIO_MODE_1,              /**< Mode 1 */
    MESA_SGPIO_MODE_0_ACTIVITY,     /**< Mode 0 when link activity */
    MESA_SGPIO_MODE_1_ACTIVITY,     /**< Mode 1 when link activity */
    MESA_SGPIO_MODE_0_ACTIVITY_INV, /**< Mode 0 when link activity, inversed polarity */
    MESA_SGPIO_MODE_1_ACTIVITY_INV, /**< Mode 1 when link activity, inversed polarity */
    MESA_SGPIO_MODE_NO_CHANGE       /**< Do not change the SGPIO mode (the mode is controlled elsewhere) */
} mesa_sgpio_mode_t CAP(MISC_SGPIO_CNT);

/** \brief SGPIO blink mode */
typedef enum
{
    MESA_SGPIO_BMODE_TOGGLE, /**< Burst toggle (mode 1 only) */
    MESA_SGPIO_BMODE_0_625,  /**< 0.625 Hz (mode 0 only) */
    MESA_SGPIO_BMODE_1_25,   /**< 1.25 Hz */
    MESA_SGPIO_BMODE_2_5,    /**< 2.5 Hz */
    MESA_SGPIO_BMODE_5       /**< 5 Hz */
} mesa_sgpio_bmode_t CAP(MISC_SGPIO_CNT);

/** \brief SGPIO port configuration */
typedef struct
{
    mesa_bool_t       enabled; /**< Port enabled/disabled */
    mesa_sgpio_mode_t mode[4]; /**< Mode for each bit */
    mesa_bool_t       int_pol_high[4];  /**< SGPIO interrupt polarity for each bit - TRUE - Interrupt when SGPIO pin high, FALSE - Interrupt when SGPIO pin low. */
} mesa_sgpio_port_conf_t CAP(MISC_SGPIO_CNT);

/** \brief SGPIO configuration for a group */
typedef struct
{
    mesa_sgpio_bmode_t     bmode[2];                     /**< Blink mode 0 and 1 */
    uint8_t                bit_count;                    /**< Bits enabled per port, 1-4 */
    mesa_sgpio_port_conf_t port_conf[MESA_SGPIO_PORTS];  /**< Port configuration */
} mesa_sgpio_conf_t CAP(MISC_SGPIO_CNT);

/**
 * \brief Get SGPIO configuration
 *
 * \param inst [IN]     Target instance reference.
 * \param chip_no [IN]  Chip number (if multi-chip instance).
 * \param group [IN]    SGPIO group.
 * \param conf [OUT]    SGPIO configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_sgpio_conf_get(const mesa_inst_t        inst,
                            const mesa_chip_no_t     chip_no,
                            const mesa_sgpio_group_t group,
                            mesa_sgpio_conf_t        *const conf)
    CAP(MISC_SGPIO_CNT);

/**
 * \brief Set SGPIO configuration
 *
 * \param inst [IN]     Target instance reference.
 * \param chip_no [IN]  Chip number (if multi-chip instance).
 * \param group [IN]    SGPIO group.
 * \param conf [IN]     SGPIO configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_sgpio_conf_set(const mesa_inst_t        inst,
                            const mesa_chip_no_t     chip_no,
                            const mesa_sgpio_group_t group,
                            const mesa_sgpio_conf_t  *const conf)
    CAP(MISC_SGPIO_CNT);

/** \brief SGPIO read data for a port */
typedef struct
{
    mesa_bool_t value[4]; /**< Data for each and bit */
} mesa_sgpio_port_data_t CAP(MISC_SGPIO_CNT);

/**
 * \brief Read SGPIO data
 *
 * \param inst [IN]     Target instance reference.
 * \param chip_no [IN]  Chip number (if multi-chip instance).
 * \param group [IN]    SGPIO group.
 * \param data [OUT]    SGPIO data.
 *
 * \return Return code.
 **/
mesa_rc mesa_sgpio_read(const mesa_inst_t        inst,
                        const mesa_chip_no_t     chip_no,
                        const mesa_sgpio_group_t group,
                        mesa_sgpio_port_data_t   data[MESA_SGPIO_PORTS])
     CAP(MISC_SGPIO_CNT);

/**
 * \brief Get SGPIO event indication
 *
 * \param inst [IN]          Target instance reference.
 * \param chip_no [IN]       Chip number (if multi-chip instance).
 * \param group [IN]         SGPIO group.
 * \param bit [IN]           SGPIO port bit (0-3).
 * \param events [OUT]       Event indication for each port for the selected bit - must point to MESA_SGPIO_PORTS of mesa_bool_t.
 *
 * \return Return code.
 **/
mesa_rc mesa_sgpio_event_poll(const mesa_inst_t        inst,
                              const mesa_chip_no_t     chip_no,
                              const mesa_sgpio_group_t group,
                              const uint32_t           bit,
                              mesa_bool_t              *const events)
    CAP(MISC_SGPIO_CNT);

/**
 * \brief Get SGPIO event enable
 *
 * \param inst [IN]          Target instance reference.
 * \param chip_no [IN]       Chip number (if multi-chip instance).
 * \param group [IN]         SGPIO group.
 * \param port [IN]          SGPIO port (0-31).
 * \param bit [IN]           SGPIO port bit (0-3).
 * \param enable [IN]        Event for each port for the selected bit is enabled or disabled.
 *
 * \return Return code.
 **/
mesa_rc mesa_sgpio_event_enable(const mesa_inst_t        inst,
                                const mesa_chip_no_t     chip_no,
                                const mesa_sgpio_group_t group,
                                const mesa_port_no_t     port,
                                const uint32_t           bit,
                                mesa_bool_t              enable)
    CAP(MISC_SGPIO_CNT);


/**
 * \brief Configure interrupt.
 * \param inst [IN] Target instance reference.
 * \param mask [IN] Interrupt mask - Configures the interrupts for the bits set in the mask.
 * \param polarity [IN] Polarity - Interrupt polarity.
 * \param enable [IN] Enable   - 1 = enable, 0 = disable.
 *
 * \return Return code.
**/
mesa_rc mesa_intr_cfg(const mesa_inst_t inst,
                      const uint32_t    mask,
                      const mesa_bool_t polarity,
                      const mesa_bool_t enable);


/**
\brief Interrupt source structure.
*/
typedef struct {
    mesa_port_list_t link_change; /**< Applies to XAUI, 100FX and 1000X ports */
} mesa_intr_t CAP(MISC_INTERRUPTS);

/**
 * \brief Set the interrupt mask.
 * \param inst [IN] Target instance reference.
 * \param mask [IN] Pointer to mask structure.
 *
 * \return Return code.
**/
mesa_rc mesa_intr_mask_set(const mesa_inst_t inst,
                           mesa_intr_t *mask)
    CAP(MISC_INTERRUPTS);

/**
 * \brief Get the interrupt status for all enabled sources.
 *        The interrupt status bit is cleared by the function
 *
 * \param inst [IN] Target instance reference.
 * \param status [OUT] Pointer to a structure with status of all enabled interrupt sources.
 *
 * \return Return code.
 **/
mesa_rc mesa_intr_status_get(const mesa_inst_t inst,
                             mesa_intr_t *status)
    CAP(MISC_INTERRUPTS);

/**
 * \brief This vil negate polarity on fast link fail detection signals when active
 *        This is only intended to be used on Luton26 RevB as a work around for the
 *        Atom PHY interrupt always active problem
 *
 * \param inst [IN] Target instance reference.
 *
 * \return Return code.
 **/
mesa_rc mesa_intr_pol_negation(const mesa_inst_t inst)
     CAP(MISC_INTERRUPTS);

/**
 * \brief Interrupt sources.
 */
typedef enum
{
    MESA_IRQ_XTR,               /**< Frame Extraction Ready(register-based) */
    MESA_IRQ_FDMA_XTR,          /**< Frame Extraction Ready (FDMA-based) */
    MESA_IRQ_SOFTWARE,          /**< Software IRQ */
    MESA_IRQ_PTP_RDY,           /**< PTP Timestamp Ready */
    MESA_IRQ_PTP_SYNC,          /**< PTP Synchronization IRQ */
    MESA_IRQ_EXT0,              /**< EXT0 IRQ */
    MESA_IRQ_EXT1,              /**< EXT1 IRQ */
    MESA_IRQ_OAM,               /**< OAM IRQ */
    MESA_IRQ_SGPIO,             /**< Serial GPIO IRQ */
    MESA_IRQ_SGPIO2,            /**< Serial GPIO2 IRQ */
    MESA_IRQ_DPLL,              /**< DPLL */
    MESA_IRQ_GPIO,              /**< GPIO */
    MESA_IRQ_DEV_ALL,           /**< Device (port) IRQ */
    MESA_IRQ_MAX,               /**< Maximum IRQ Source - MUST be the last in this enum*/
} mesa_irq_t CAP(MISC_IRQ_CONTROL);

/**
 * \brief Interrupt configuration options.
 */
typedef struct {
    mesa_bool_t  external;    /**< Redirect to external IRQ */
    uint8_t      destination; /**< IRQ destination index */
} mesa_irq_conf_t CAP(MISC_IRQ_CONTROL);

/**
 * \brief Interrupt status structure.
 */
typedef struct {
    uint32_t active;     /**< Bitmap for pending IRQs (MESA_IRQ_xxx) */
    uint32_t raw_ident;  /**< RAW (target dependentant) bitmap for active pending IRQs */
    uint32_t raw_status; /**< RAW (target dependentant) bitmap for all pending IRQs */
    uint32_t raw_mask;   /**< RAW (target dependentant) bitmap for IRQs mask */
} mesa_irq_status_t CAP(MISC_IRQ_CONTROL);

/**
 * \brief Get IRQ configuration
 *
 * \param inst [IN]     Target instance reference.
 * \param irq  [IN]     Interrupt source.
 * \param conf [OUT]    IRQ configuration.
 *
 * \return Return code.
 **/
mesa_rc  mesa_irq_conf_get(const mesa_inst_t inst,
                           const mesa_irq_t irq,
                           mesa_irq_conf_t *conf)
    CAP(MISC_IRQ_CONTROL);

/**
 * \brief Set IRQ configuration
 *
 * \param inst [IN]     Target instance reference.
 * \param irq  [IN]     Interrupt source.
 * \param conf [IN]     IRQ configuration.
 *
 * \return Return code.
 **/
mesa_rc  mesa_irq_conf_set(const mesa_inst_t inst,
                           const mesa_irq_t irq,
                           const mesa_irq_conf_t *const conf)
    CAP(MISC_IRQ_CONTROL);

/**
 * \brief Get IRQ status (active sources), mask current sources
 *
 * \param inst   [IN]   Target instance reference.
 * \param status [OUT]  IRQ status.
 *
 * \return Return code.
 **/
mesa_rc  mesa_irq_status_get_and_mask(const mesa_inst_t inst,
                                      mesa_irq_status_t *status)
    CAP(MISC_IRQ_CONTROL);

/**
 * \brief Control a specific interrupt source
 *
 * \param inst   [IN]   Target instance reference.
 * \param irq    [IN]   Interrupt source.
 * \param enable [IN]   Enable or disable source.
 *
 * \return Return code.
 **/
mesa_rc  mesa_irq_enable(const mesa_inst_t inst,
                         const mesa_irq_t irq,
                         mesa_bool_t enable)
    CAP(MISC_IRQ_CONTROL);

/* - API tod functions -------------------------------------- */

/**
 * \brief Get the current hw nanosec time
 *  This function is called from interrupt
 * \returns actual ns counter
 */
uint32_t mesa_tod_get_ns_cnt(void);

/**
 * \brief If the actual HW does not support time stamping, an external callback
 * function can be set up to do the work.
 * \returns actual ns counter.
 */
typedef uint32_t (*tod_get_ns_cnt_cb_t)(void);  /* Get ns Counter callback  */

/**
 * \brief Set an external hw nanosec read function.
 *
 * \param cb pointer to callback function
 */
void mesa_tod_set_ns_cnt_cb(tod_get_ns_cnt_cb_t cb);

/**
 * mesa_os_timestamp_t
 * MESA_OS_TIMESTAMP()
 *   These two provides a mean to have the API timestamp events for use
 *   by the application. It is up to the platform specific code to
 *   implement the actual functions to obtain the timestamp.
 *   The implementation *must* be callable from interrupt context, so no
 *   implicit waits or sleeps are allowed.
 */
typedef struct {
    uint32_t hw_cnt; /**< hardware counter */
} mesa_os_timestamp_t;
#define MESA_OS_TIMESTAMP(timestamp)                                    \
  do {                                                                  \
    /* Currently no need to lock scheduler, since it's only          */ \
    /* called from a function, where the sceduler is already locked. */ \
    /* cyg_scheduler_lock(__FILE__, __LINE__); */                                         \
    (timestamp)->hw_cnt = mesa_tod_get_ns_cnt();                        \
    /* cyg_scheduler_unlock(__FILE__, __LINE__); */                                       \
  } while(0); /**< MESA_OS_TIMESTAMP() provides the implementation that will fill in the timestamp. */


/* - Fan control functions -------------------------------------- */

/**
 * \brief Initialize the temperature sensor
 *
 * \param inst [IN]        Target instance reference
 * \param enable [IN]       Set to true if sensor shall be active else false
 *
 * \return Return code.
 **/
mesa_rc mesa_temp_sensor_init(const mesa_inst_t inst,
                              const mesa_bool_t enable)
    CAP(MISC_FAN);

/**
 * \brief Read temperature sensor value
 *
 * \param inst [IN]        Target instance reference
 * \param temperature [OUT]      Temperature from sensor (range from -46 to 135 degC)
 *
 * \return Return code.
 **/

mesa_rc mesa_temp_sensor_get(const mesa_inst_t     inst,
                             int16_t               *temperature)
    CAP(MISC_FAN);

/** \brief FAN PWM frequency */
typedef enum
{
    MESA_FAN_PWM_FREQ_25KHZ,
    MESA_FAN_PWM_FREQ_120HZ,
    MESA_FAN_PWM_FREQ_100HZ,
    MESA_FAN_PWM_FREQ_80HZ,
    MESA_FAN_PWM_FREQ_60HZ,
    MESA_FAN_PWM_FREQ_40HZ,
    MESA_FAN_PWM_FREQ_20HZ,
    MESA_FAN_PWM_FREQ_10HZ
} mesa_fan_pwd_freq_t CAP(MISC_FAN);

/** \brief FAN Types  */
typedef enum
{
    MESA_FAN_2_WIRE_TYPE,
    MESA_FAN_3_WIRE_TYPE,
    MESA_FAN_4_WIRE_TYPE
} mesa_fan_type_t CAP(MISC_FAN);

/** \brief Maximum fan speed level (Fan runs at full speed) */
#define MESA_FAN_SPEED_MAX 0x255
/** \brief Minimum fan speed level (Fan is OFF) */
#define MESA_FAN_SPEED_MIN 0x0

/** \brief Fan specifications */
typedef struct
{
    mesa_fan_pwd_freq_t fan_pwm_freq;      /**< Fan PWM frequency*/
    mesa_bool_t         fan_low_pol;       /**< Fan polarity of the PWM output. TRUE = PWM is logic 0 when on. FALSE = PWM is logic 1 when on */
    mesa_bool_t         fan_open_col;      /**< PWM output is open collector if TRUE.*/
    mesa_fan_type_t     type;              /**< 2,3 or 4 wire fan type*/
    uint32_t            ppr;               /**< Pulses per rotation. Only valid for 3 and 4 wire fans */
} mesa_fan_conf_t CAP(MISC_FAN);

/**
 * \brief Get the number of fan rotations
 *
 * \param inst [IN]       Target instance reference
 * \param rotation_count [OUT] Number of fan rotation countered for the last second.
 *
 * \return Return code.
 **/
mesa_rc mesa_fan_rotation_get(const mesa_inst_t inst,
                              uint32_t          *rotation_count)
    CAP(MISC_FAN);

/**
 * \brief Set fan cool level (Duty cycle)
 *
 * \param inst [IN]       Target instance reference
 * \param lvl  [IN]       Level. 0 = Fan off, 255 = fan fully on
 *
 * \return Return code.
**/
mesa_rc mesa_fan_cool_lvl_set(const mesa_inst_t inst,
                              uint8_t lvl)
    CAP(MISC_FAN);

/**
 * \brief Initialise fan controller)
 *
 * \param inst [IN]    Target instance reference
 * \param spec [IN]    Fan specifications
 *
 * \return Return code.
**/
mesa_rc mesa_fan_controller_init(const mesa_inst_t     inst,
                                 const mesa_fan_conf_t *const spec)
    CAP(MISC_FAN);

/**
 * \brief Get fan cool level (Duty cycle)
 *
 * \param inst [IN]       Target instance reference
 * \param lvl  [IN]       Level. 0 = Fan off, 255 = fan fully on
 *
 * \return Return code.
**/
mesa_rc mesa_fan_cool_lvl_get(const mesa_inst_t inst,
                              uint8_t *lvl)
    CAP(MISC_FAN);

/* - EEE functions -------------------------------------- */
/** \brief EEE port configuration */
typedef struct
{
    mesa_bool_t eee_ena;          /**< Enable EEE                                                                                                                                                       */
    uint8_t     eee_fast_queues;  /**< Queues set in this mask will activate egress path as soon as any data is available. Vector for enabling fast queues. bit 0 = queue 0, bit 1 = queue 1 and so on. */
    uint16_t    tx_tw;            /**< Time from path is activated until frame transmission restarted.                                                                                                  */
    uint8_t     lp_advertisement; /**< Link partner EEE advertisement. Bit 0 = Link partner advertises 100BASE-T capability. Bit 1 = Link partner advertises 1000BASE-T capability.                     */

    mesa_bool_t optimized_for_power; /**< EEE can be optimized for either most power savings or least traffic latency */
} mesa_eee_port_conf_t;

/**
 * \brief Set EEE configuration
 *
 * \param inst     [IN] Target instance reference
 * \param port_no  [IN] Port number
 * \param eee_conf [IN] EEE configuration
 *
 * \return Return code.
 **/
mesa_rc mesa_eee_port_conf_set(const mesa_inst_t          inst,
                               const mesa_port_no_t       port_no,
                               const mesa_eee_port_conf_t *const eee_conf);

/** \brief RS422 specifications */
typedef struct
{
    uint32_t     gpio_rs422_1588_mstoen;    /**< IO pin used for RS422 master output enable/disable */
    uint32_t     gpio_rs422_1588_slvoen;    /**< IO pin used for RS422 slave output enable/disable */
    uint32_t     ptp_pin_ldst;              /**< PTP_IO pin used for RS422 Load/store input */
    uint32_t     ptp_pin_ppso;              /**< PTP_IO pin used for RS422 1 PPS output */
    uint32_t     ptp_rs422_pps_int_id;      /**< Interrupt id for RS422 1PPS interrupt */
    uint32_t     ptp_rs422_ldsv_int_id;     /**< Interrupt id for RS422 Load/Save input interrupt */
} meba_ptp_rs422_conf_t CAP(TS_PTP_RS422);

/* - Symreg ----------------------------------------------------------------- */

/** \brief Symbolic descriptiopn of a register. */
typedef struct {
    const char      *name;       /**< Name of register */
    unsigned long   addr;        /**< Address of register */
    unsigned long   repl_cnt;    /**< Replication count of register */
    unsigned long   repl_width;  /**< Replication width of register */
} mesa_symreg_reg_t;

/** \brief Symbolic descriptiopn of a register group. */
typedef struct {
    const char         *name;       /**< Name of register group */
    unsigned long      base_addr;   /**< Base address of register group */
    unsigned long      repl_cnt;    /**< Replication count of register group */
    unsigned long      repl_width;  /**< Replication width of register group */
    mesa_symreg_reg_t const *regs;  /**< Pointer to symbolic registers (null terminated) */
} mesa_symreg_reggrp_t;

/** \brief Symbolic descriptiopn of a register target. */
typedef struct {
    const char            *name;          /**< Name of register target */
    int                   repl_number;    /**< Target instance number */
    unsigned long         tgt_id;         /**< Target ID */
    unsigned long         base_addr;      /**< Base address */
    mesa_symreg_reggrp_t const *reggrps;  /**< Pointer to symbolic register groups (null terminated) */
} mesa_symreg_target_t;

/** \brief Symbolic register base data. */
typedef struct {
    const mesa_symreg_target_t *targets;           /**< Pointer to targets (not null terminated) */
    unsigned long               targets_cnt;       /**< Number of targets */
    unsigned long               io_origin1_offset; /**< IO register offset */
    unsigned long               repl_cnt_max;      /**< Highest number of replications */
    unsigned long               name_len_max;      /**< Max name length */
} mesa_symreg_data_t;

/**
 * \brief Get symbolic register data.
 *
 * \param inst       [IN]  Target instance reference.
 * \param data       [OUT] data

 * \return Return code.
 *
 **/
mesa_rc mesa_symreg_data_get(const mesa_inst_t   inst,
                             mesa_symreg_data_t *const data);

#include <mscc/ethernet/switch/api/hdr_end.h>
#endif // _MSCC_ETHERNET_SWITCH_API_MISC_
