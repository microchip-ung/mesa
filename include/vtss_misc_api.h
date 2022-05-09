// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/**
 * \file
 * \brief Miscellaneous API
 * \details This header file describes miscellaneous API functions
 */

#ifndef _VTSS_MISC_API_H_
#define _VTSS_MISC_API_H_

#include <vtss/api/types.h>
#include "vtss_init_api.h"
#ifdef __cplusplus
extern "C" {
#endif

/** \brief Trace group layer */
typedef enum
{
    VTSS_TRACE_LAYER_AIL,   /**< Application Interface Layer */
    VTSS_TRACE_LAYER_CIL,   /**< Chip Interface Layer */

    VTSS_TRACE_LAYER_COUNT  /**< Number of layers */
} vtss_trace_layer_t;

/** \brief Trace groups */
typedef enum
{
    VTSS_TRACE_GROUP_DEFAULT,       /**< Default trace group */
    VTSS_TRACE_GROUP_PORT,          /**< Port control */
    VTSS_TRACE_GROUP_PHY,           /**< PHY control */
    VTSS_TRACE_GROUP_PACKET,        /**< Packet control */
    VTSS_TRACE_GROUP_AFI,           /**< AFI */
    VTSS_TRACE_GROUP_QOS,           /**< Quality of Service */
    VTSS_TRACE_GROUP_L2,            /**< Layer 2 */
    VTSS_TRACE_GROUP_L3,            /**< Layer 3 */
    VTSS_TRACE_GROUP_SECURITY,      /**< Security */
    VTSS_TRACE_GROUP_EVC,           /**< Ethernet Virtual Connections */
    VTSS_TRACE_GROUP_FDMA_NORMAL,   /**< (Obsoleted group) */
    VTSS_TRACE_GROUP_FDMA_IRQ,      /**< (Obsoleted group) */
    VTSS_TRACE_GROUP_REG_CHECK,     /**< (Obsoleted group) */
    VTSS_TRACE_GROUP_MPLS,          /**< MPLS */
    VTSS_TRACE_GROUP_HW_PROT,       /**< Hardware Protection */
    VTSS_TRACE_GROUP_HQOS,          /**< Hierarchical Quality of Service */
    VTSS_TRACE_GROUP_MACSEC,        /**< MACSEC control */
    VTSS_TRACE_GROUP_VCAP,          /**< VCAP */
    VTSS_TRACE_GROUP_OAM,           /**< OAM */
    VTSS_TRACE_GROUP_MRP,           /**< MRP */
    VTSS_TRACE_GROUP_TS,            /**< Timestamping */
    VTSS_TRACE_GROUP_CLOCK,         /**< Synce Clock */
    VTSS_TRACE_GROUP_EMUL,          /**< Emulation */

    VTSS_TRACE_GROUP_COUNT          /**< Number of trace groups */
} vtss_trace_group_t;

/** \brief Trace levels */
typedef enum
{
    VTSS_TRACE_LEVEL_NONE,  /**< No trace */
    VTSS_TRACE_LEVEL_ERROR, /**< Error trace */
    VTSS_TRACE_LEVEL_INFO,  /**< Information trace */
    VTSS_TRACE_LEVEL_DEBUG, /**< Debug trace */
    VTSS_TRACE_LEVEL_NOISE, /**< More debug information */

    VTSS_TRACE_LEVEL_COUNT  /**< Number of trace levels */
} vtss_trace_level_t;

/** \brief Trace group configuration */
typedef struct
{
    vtss_trace_level_t level[VTSS_TRACE_LAYER_COUNT]; /**< Trace level per layer */
} vtss_trace_conf_t;

/**
 * \brief Get trace configuration
 *
 * \param group [IN]  Trace group
 * \param conf [OUT]  Trace group configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_trace_conf_get(const vtss_trace_group_t  group,
                            vtss_trace_conf_t         *const conf);


/**
 * \brief Set trace configuration
 *
 * \param group [IN]  Trace group
 * \param conf [IN]   Trace group configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_trace_conf_set(const vtss_trace_group_t  group,
                            const vtss_trace_conf_t   *const conf);

/** \brief Attribute */
#if defined(__GNUC__) && (__GNUC__ > 2)
#define VTSS_ATTR_PRINTF(X, Y) __attribute__ ((format(printf,X,Y)))
#else
#define VTSS_ATTR_PRINTF(X, Y)
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
void vtss_callout_trace_printf(const vtss_trace_layer_t  layer,
                               const vtss_trace_group_t  group,
                               const vtss_trace_level_t  level,
                               const char                *file,
                               const int                 line,
                               const char                *function,
                               const char                *format,
                               ...) VTSS_ATTR_PRINTF(7, 8);

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
void vtss_callout_trace_hex_dump(const vtss_trace_layer_t  layer,
                                 const vtss_trace_group_t  group,
                                 const vtss_trace_level_t  level,
                                 const char                *file,
                                 const int                 line,
                                 const char                *function,
                                 const u8                  *byte_p,
                                 const int                 byte_cnt);

#if VTSS_OPT_DEBUG_PRINT

/** \brief Debug layer */
/* Debug layer */
typedef enum {
    VTSS_DEBUG_LAYER_ALL, /**< All layers */
    VTSS_DEBUG_LAYER_AIL, /**< Application Interface Layer */
    VTSS_DEBUG_LAYER_CIL  /**< Chip Interface Layer */
} vtss_debug_layer_t;

/** \brief Debug function group */
typedef enum {
    VTSS_DEBUG_GROUP_ALL,       /**< All groups */
    VTSS_DEBUG_GROUP_INIT,      /**< Initialization */
    VTSS_DEBUG_GROUP_MISC,      /**< Miscellaneous */
    VTSS_DEBUG_GROUP_PORT,      /**< Port configuration */
    VTSS_DEBUG_GROUP_PORT_CNT,  /**< Port counters */
    VTSS_DEBUG_GROUP_PHY,       /**< PHY */
    VTSS_DEBUG_GROUP_VLAN,      /**< VLAN */
    VTSS_DEBUG_GROUP_PVLAN,     /**< PVLAN */
    VTSS_DEBUG_GROUP_MAC_TABLE, /**< MAC address table */
    VTSS_DEBUG_GROUP_ACL,       /**< ACL */
    VTSS_DEBUG_GROUP_QOS,       /**< QoS */
    VTSS_DEBUG_GROUP_AGGR,      /**< Link aggregation */
    VTSS_DEBUG_GROUP_GLAG,      /**< Global link aggregation */
    VTSS_DEBUG_GROUP_STP,       /**< Spanning Tree */
    VTSS_DEBUG_GROUP_MIRROR,    /**< Mirroring */
    VTSS_DEBUG_GROUP_EVC,       /**< EVC */
    VTSS_DEBUG_GROUP_ERPS,      /**< ERPS */
    VTSS_DEBUG_GROUP_EPS,       /**< EPS */
    VTSS_DEBUG_GROUP_SR,        /**< Seamless Redundancy */
    VTSS_DEBUG_GROUP_PACKET,    /**< Packet control */
    VTSS_DEBUG_GROUP_FDMA,      /**< Obsoleted */
    VTSS_DEBUG_GROUP_TS,        /**< TS: TimeStamping */
    VTSS_DEBUG_GROUP_PHY_TS,    /**< PHY_TS: PHY TimeStamping */
    VTSS_DEBUG_GROUP_WM,        /**< WaterMarks */
    VTSS_DEBUG_GROUP_LRN,       /**< DEPRECATED. Use VTSS_DEBUG_GROUP_MAC_TABLE instead */
    VTSS_DEBUG_GROUP_IPMC,      /**< IP Multicast */
    VTSS_DEBUG_GROUP_STACK,     /**< Stacking */
    VTSS_DEBUG_GROUP_CMEF,      /**< Congestion Management */
    VTSS_DEBUG_GROUP_HOST,      /**< CE-MAX Host configuration */
    VTSS_DEBUG_GROUP_MPLS,      /**< MPLS */
    VTSS_DEBUG_GROUP_HW_PROT,   /**< HW Protection */
    VTSS_DEBUG_GROUP_HQOS,      /**< Hierarchical Quality of Service */
    VTSS_DEBUG_GROUP_VXLAT,     /**< VLAN Translation */
    VTSS_DEBUG_GROUP_OAM,       /**< OAM, incl. VOEs/VOP */
    VTSS_DEBUG_GROUP_MRP,       /**< Media Redundancy Protocol (MRP) */
    VTSS_DEBUG_GROUP_SER_GPIO,  /**< Serial GPIO configuration */
    VTSS_DEBUG_GROUP_L3,        /**< L3 services */
    VTSS_DEBUG_GROUP_AFI,       /**< Automatic Frame Injector */
    VTSS_DEBUG_GROUP_MACSEC,    /**< 802.1AE MacSec */
    VTSS_DEBUG_GROUP_SERDES,    /**< Serdes Macroes */
    VTSS_DEBUG_GROUP_KR,        /**< 5G/10G/25Base-KR */
    VTSS_DEBUG_GROUP_MUX,       /**< Mux mode */

    /* New groups are added above this line */
    VTSS_DEBUG_GROUP_COUNT      /**< Number of groups */
} vtss_debug_group_t;


/** \brief Special chip number value for showing information from all chips */
#define VTSS_CHIP_NO_ALL 0xffffffff

/** \brief Debug information structure */
typedef struct {
    vtss_debug_layer_t           layer;                           /**< Layer */
    vtss_debug_group_t           group;                           /**< Function group */
    vtss_chip_no_t               chip_no;                         /**< Chip number, multi-chip targets */
    BOOL                         port_list[VTSS_PORT_ARRAY_SIZE]; /**< Port list */
    BOOL                         full;                            /**< Full information dump */
    BOOL                         clear;                           /**< Clear counters */
    BOOL                         vml_format;                      /**< VML format register dump */
    BOOL                         has_action;                      /**< Action parameter is present */
    u32                          action;                          /**< Debug group depending action value */
    u32                          prm[10];                         /**< Parameters from user */
} vtss_debug_info_t;

/** \brief Debug printf function
 *
 * The signature is similar to that of printf(). However, the return value is
 * not used anywhere within the API.
 */
typedef int (*vtss_debug_printf_t)(const char *fmt, ...) VTSS_ATTR_PRINTF(1, 2);

/**
 * \brief Get default debug information structure
 *
 * \param info [OUT]  Debug information
 *
 * \return Return code.
 **/
vtss_rc vtss_debug_info_get(vtss_debug_info_t *const info);

/**
 * \brief Print default information
 *
 * \param inst [IN]   Target instance reference.
 * \param prntf [IN]  Debug printf function.
 * \param info [IN]   Debug information
 *
 * \return Return code.
 **/
vtss_rc vtss_debug_info_print(const vtss_inst_t         inst,
                              const vtss_debug_printf_t prntf,
                              const vtss_debug_info_t   *const info);
#endif // VTSS_OPT_DEBUG_PRINT

/* - API protection functions -------------------------------------- */

/** \brief API lock structure */
typedef struct {
    vtss_inst_t inst;     /**< Target instance reference */
    const char *function; /**< Function name */
    const char *file;     /**< File name */
    int        line;      /**< Line number */
} vtss_api_lock_t;

/**
 * \brief Lock API access
 *
 * \param lock [IN]  Lock information
*/
void vtss_callout_lock(const vtss_api_lock_t *const lock);

/**
 * \brief Unlock API access
 *
 * \param lock [IN]  Lock information
*/
void vtss_callout_unlock(const vtss_api_lock_t *const lock);

/** \brief API debug lock structure */
typedef struct {
    vtss_chip_no_t chip_no; /**< Chip number (if multi-chip instance). */
} vtss_debug_lock_t;

/**
 * \brief Debug lock API access
 *
 * \param inst [IN]  Target instance reference.
 * \param lock [IN]  Lock information
 *
 * \return Return code.
*/
vtss_rc vtss_debug_lock(const vtss_inst_t       inst,
                        const vtss_debug_lock_t *const lock);

/**
 * \brief Debug unlock API access
 *
 * \param inst [IN]  Target instance reference.
 * \param lock [IN]  Lock information
 *
 * \return Return code.
*/
vtss_rc vtss_debug_unlock(const vtss_inst_t inst,
                          vtss_debug_lock_t *const lock);

#if defined(VTSS_FEATURE_MISC)
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
vtss_rc vtss_reg_read(const vtss_inst_t    inst,
                      const vtss_chip_no_t chip_no,
                      const u32            addr,
                      u32                  *const value);


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
vtss_rc vtss_reg_write(const vtss_inst_t    inst,
                       const vtss_chip_no_t chip_no,
                       const u32            addr,
                       const u32            value);


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
vtss_rc vtss_reg_write_masked(const vtss_inst_t    inst,
                              const vtss_chip_no_t chip_no,
                              const u32            addr,
                              const u32            value,
                              const u32            mask);

/* - Secondary chip if ------------------- */

/**
 * \brief Clear EXT0-1 interrupt sticky bits on secondary chip.
 *
 * \param inst [IN]    Target instance reference.
 * \param ext [IN]     EXT number (0-1).
 *
 * \return Return code.
 **/
vtss_rc vtss_intr_sticky_clear(const vtss_inst_t    inst,
                               u32                  ext);

/* - Chip ID and revision ------------------------------------------ */

/** \brief Chip ID */
typedef struct
{
    u16  part_number;   /**< BCD encoded part number */
    u16  revision;      /**< Chip revision */
} vtss_chip_id_t;

/**
 * \brief Get chip ID and revision.
 *
 * \param inst [IN]     Target instance reference.
 * \param chip_id [IN]  Pointer to chip ID structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_chip_id_get(const vtss_inst_t  inst,
                         vtss_chip_id_t     *const chip_id);


/* - Polling functions ---------------------------------------- */

/**
 * \brief Polling function called every second.
 *
 * \param inst [IN]  Target instance reference.
 *
 * \return Return code.
 **/
vtss_rc vtss_poll_1sec(const vtss_inst_t  inst);

/**
 * \brief Define event (interrupt) types relatesd to PTP in the switch chips
 *
 **/
typedef enum {
    VTSS_PTP_SYNC_EV =      (1 << 0), /*< PTP Synchronization pulse update */
    VTSS_PTP_EXT_SYNC_EV =  (1 << 1), /*< PTP External Synchronization input  (Sync 0 on Serval)*/
    VTSS_PTP_CLK_ADJ_EV =   (1 << 2), /*< PTP Clock adjustment updated */
    VTSS_PTP_TX_TSTAMP_EV = (1 << 3), /*< Tx timestamp udated (Jaguar and Serval only)*/
    VTSS_PTP_EXT_1_SYNC_EV =(1 << 4), /*< PTP External Synchronization 1 input (Serval only)*/
    VTSS_PTP_PIN_0_SYNC_EV =(1 << 5), /*< PTP External pin 0 synchronization (Jaguar2 only)*/
    VTSS_PTP_PIN_1_SYNC_EV =(1 << 6), /*< PTP External pin 1 synchronization (Jaguar2 only)*/
    VTSS_PTP_PIN_2_SYNC_EV =(1 << 7), /*< PTP External pin 2 synchronization (Jaguar2 only)*/
    VTSS_PTP_PIN_3_SYNC_EV =(1 << 8), /*< PTP External pin 3 synchronization (Jaguar2 only)*/
} vtss_ptp_event_type_t;

/**
 * \brief PTP polling function called at by interrupt or periodicly
 *
 * \param inst       [IN]  Target instance reference.
 * \param ev_mask    [OUT] Event type mask of active events
 *
 * \note The \e ev_mask parameter can be either a single event_type or
 * multiple event types (or \e VTSS_EVTYPE_ALL). If invoked by a
 * processor interrupt signal, the type of event to check for may be
 * narrowed in to specific events.
 *
 * \return Return code.
 **/
vtss_rc vtss_ptp_event_poll(const vtss_inst_t      inst,
                            vtss_ptp_event_type_t  *const ev_mask);

/**
 * \brief Enable PTP event generation for a specific event type
 *
 * \param inst     [IN] Target instance reference.
 * \param enable   [IN] Enable or disable events
 * \param ev_mask  [IN] Event type(s) to control (mask)
 *
 * \return Return code.
 **/
vtss_rc vtss_ptp_event_enable(const vtss_inst_t            inst,
                              const vtss_ptp_event_type_t  ev_mask,
                              const BOOL                   enable);

/**
 * \brief Define the dev_all event (interrupt) types
 *
 **/
typedef enum {
    VTSS_DEV_ALL_TX_TSTAMP_EV = (1 << 0), /*< Tx timestamp udated */
    VTSS_DEV_ALL_LINK_EV =      (1 << 1), /*< Link state changed */
} vtss_dev_all_event_type_t;

/**
 * \brief Define the dev_all polling types
 *
 **/
typedef enum {
    VTSS_DEV_ALL_POLL_ALL,          /*< Polling all chip */
    VTSS_DEV_ALL_POLL_PRIMARY,      /*< Polling primary chip */
    VTSS_DEV_ALL_POLL_SECONDARY,    /*< Polling secondary chip */
} vtss_dev_all_event_poll_t;

/**
 * \brief DEV_ALL polling function called at by interrupt or periodically
 *
 * \param inst      [IN] Target instance reference.
 * \param poll_type [IN] Polling type
 * \param ev_mask   [OUT] Event type mask array of active events for all ports - must be of size VTSS_PORT_ARRAY_SIZE
 *
 * \note The \e ev_mask parameter can be either a single event_type or
 * multiple event types (or \e VTSS_EVTYPE_ALL). If invoked by a
 * processor interrupt signal, the type of event to check for may be
 * narrowed in to specific events.
 *
 * \return Return code.
 **/
vtss_rc vtss_dev_all_event_poll(const vtss_inst_t                 inst,
                                const vtss_dev_all_event_poll_t   poll_type,
                                vtss_dev_all_event_type_t         *const ev_mask);

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
vtss_rc vtss_dev_all_event_enable(const vtss_inst_t                inst,
                                  const vtss_port_no_t             port_no,
                                  const vtss_dev_all_event_type_t  ev_mask,
                                  const BOOL                       enable);

#endif /* VTSS_FEATURE_MISC */

/* - GPIOs --------------------------------------------------------- */

#if defined(VTSS_ARCH_LUTON26) || defined(VTSS_ARCH_OCELOT)
/** \brief Number of GPIOs */
#undef VTSS_GPIOS
#define VTSS_GPIOS         32
#endif /* VTSS_ARCH_LUTON26/SERVAL */

#if defined(VTSS_ARCH_JAGUAR_2)
/** \brief Number of GPIOs */
#undef VTSS_GPIOS
#define VTSS_GPIOS         64
#endif /* VTSS_ARCH_JAGUAR_2 */

#if defined(VTSS_ARCH_SPARX5)
/** \brief Number of GPIOs */
#undef VTSS_GPIOS
#define VTSS_GPIOS         64
#endif /* VTSS_ARCH_SPARX5 */

#if defined(VTSS_ARCH_LAN966X)
/** \brief Number of GPIOs */
#undef VTSS_GPIOS
#define VTSS_GPIOS         78
#endif /* VTSS_ARCH_LAN966X */

/** \brief GPIO number */
typedef u32 vtss_gpio_no_t;

#if defined(VTSS_GPIOS)
/** \brief GPIO start number */
#define VTSS_GPIO_NO_START 0

/** \brief GPIO end number */
#define VTSS_GPIO_NO_END   (VTSS_GPIO_NO_START+VTSS_GPIOS)

/**
 * \brief GPIO configured mode
 **/
typedef enum
{
    VTSS_GPIO_OUT,    /**< Output enabled */
    VTSS_GPIO_IN,     /**< Input enabled */
    VTSS_GPIO_IN_INT, /**< Input enabled, IRQ gated */
    VTSS_GPIO_ALT_0,  /**< Alternate function 0 */
    VTSS_GPIO_ALT_1,  /**< Alternate function 1 */
    VTSS_GPIO_ALT_2,  /**< Alternate function 2 */
    VTSS_GPIO_ALT_3,  /**< Alternate function 3 */
    VTSS_GPIO_ALT_4,  /**< Alternate function 4 */
    VTSS_GPIO_ALT_5,  /**< Alternate function 5 */
} vtss_gpio_mode_t;

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
vtss_rc vtss_gpio_mode_set(const vtss_inst_t      inst,
                           const vtss_chip_no_t   chip_no,
                           const vtss_gpio_no_t   gpio_no,
                           const vtss_gpio_mode_t mode);

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
 * \em DEPRECATED. Use vtss_gpio_mode_set() instead.
 **/
vtss_rc vtss_gpio_direction_set(const vtss_inst_t     inst,
                                const vtss_chip_no_t  chip_no,
                                const vtss_gpio_no_t  gpio_no,
                                const BOOL            output);



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
vtss_rc vtss_gpio_read(const vtss_inst_t     inst,
                       const vtss_chip_no_t  chip_no,
                       const vtss_gpio_no_t  gpio_no,
                       BOOL                  *const value);



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
vtss_rc vtss_gpio_write(const vtss_inst_t     inst,
                        const vtss_chip_no_t  chip_no,
                        const vtss_gpio_no_t  gpio_no,
                        const BOOL            value);

/**
 * \brief Get GPIO event indication
 *
 * \param inst [IN]         Target instance reference.
 * \param chip_no [IN]      Chip number (if multi-chip instance).
 * \param events [OUT]      Event indication for each GPIO pin - must point to VTSS_GPIOS of BOOL.
 *
 * \return Return code.
 **/
vtss_rc vtss_gpio_event_poll(const vtss_inst_t        inst,
                             const vtss_chip_no_t     chip_no,
                             BOOL                     *const events);

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
vtss_rc vtss_gpio_event_enable(const vtss_inst_t       inst,
                               const vtss_chip_no_t    chip_no,
                               const vtss_gpio_no_t    gpio_no,
                               BOOL                    enable);

// The GPIO functionality identifier
typedef enum {
    VTSS_GPIO_FUNC_PTP_0,   // PTP 0 GPIO functionality
    VTSS_GPIO_FUNC_PTP_1,   // PTP 1 GPIO functionality
    VTSS_GPIO_FUNC_PTP_2,   // PTP 2 GPIO functionality
    VTSS_GPIO_FUNC_PTP_3,   // PTP 3 GPIO functionality
    VTSS_GPIO_FUNC_PTP_4    // PTP 4 GPIO functionality
} vtss_gpio_func_t;

// GPIO functionality ALT mode
typedef enum
{
    VTSS_GPIO_FUNC_ALT_0,  // Alternate function 0
    VTSS_GPIO_FUNC_ALT_1,  // Alternate function 1
    VTSS_GPIO_FUNC_ALT_2   // Alternate function 2
} vtss_gpio_func_alt_t;

// GPIO functionality information
typedef struct {
    vtss_gpio_no_t       gpio_no;    // GPIO pin number.
    vtss_gpio_func_alt_t alt;        // GPIO ALT function.
} vtss_gpio_func_info_t;

/**
 * \brief Get the GPIO information that is board specific for this GPIO functionality
 *
 * \param gpio_func [IN]    GPIO functionality identifier.
 * \param info [OUT]        GPIO pin functionality information.
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_gpio_func_info_get_t)(const vtss_inst_t       inst,
                                             const vtss_gpio_func_t  gpio_func,
                                             vtss_gpio_func_info_t   *const info);

#endif /* GPIOS */

/* - Serial GPIO control ---------------------------------------------------- */

#if defined(VTSS_FEATURE_SERIAL_GPIO)

#if defined(VTSS_ARCH_LUTON26) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_LAN966X)
/** \brief Number of serial GPIO groups */
#define VTSS_SGPIO_GROUPS 1
#endif /* VTSS_ARCH_LUTON26/SERVAL/SERVAL_T */

#if defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C)
/** \brief Number of serial GPIO groups */
#define VTSS_SGPIO_GROUPS 3
#endif /* VTSS_ARCH_JAGUAR_2_B/C */

#if defined(VTSS_ARCH_SPARX5)
/** \brief Number of serial GPIO groups */
#define VTSS_SGPIO_GROUPS  3
#endif /* VTSS_ARCH_SPARX5 */

/** \brief Serial GPIO group */
typedef u32 vtss_sgpio_group_t;

/** \brief Number of serial GPIO ports */
#define VTSS_SGPIO_PORTS 32

/** \brief SGPIO output mode */
typedef enum
{
    VTSS_SGPIO_MODE_OFF,            /**< Off */
    VTSS_SGPIO_MODE_ON,             /**< On */
    VTSS_SGPIO_MODE_0,              /**< Mode 0 */
    VTSS_SGPIO_MODE_1,              /**< Mode 1 */
    VTSS_SGPIO_MODE_0_ACTIVITY,     /**< Mode 0 when link activity */
    VTSS_SGPIO_MODE_1_ACTIVITY,     /**< Mode 1 when link activity */
    VTSS_SGPIO_MODE_0_ACTIVITY_INV, /**< Mode 0 when link activity, inversed polarity */
    VTSS_SGPIO_MODE_1_ACTIVITY_INV, /**< Mode 1 when link activity, inversed polarity */
    VTSS_SGPIO_MODE_NO_CHANGE       /**< Do not change the SGPIO mode (the mode is controlled elsewhere) */
} vtss_sgpio_mode_t;

/** \brief SGPIO blink mode */
typedef enum
{
    VTSS_SGPIO_BMODE_TOGGLE, /**< Burst toggle (mode 1 only) */
    VTSS_SGPIO_BMODE_0_625,  /**< 0.625 Hz (mode 0 only) */
    VTSS_SGPIO_BMODE_1_25,   /**< 1.25 Hz */
    VTSS_SGPIO_BMODE_2_5,    /**< 2.5 Hz */
    VTSS_SGPIO_BMODE_5       /**< 5 Hz */
} vtss_sgpio_bmode_t;

/** \brief SGPIO port configuration */
typedef struct
{
    BOOL              enabled; /**< Port enabled/disabled */
    vtss_sgpio_mode_t mode[4]; /**< Mode for each bit */
    BOOL              int_pol_high[4];  /**< SGPIO interrupt polarity for each bit - TRUE - Interrupt when SGPIO pin high, FALSE - Interrupt when SGPIO pin low. */
} vtss_sgpio_port_conf_t;

/** \brief SGPIO configuration for a group */
typedef struct
{
    vtss_sgpio_bmode_t     bmode[2];                     /**< Blink mode 0 and 1 */
    u8                     bit_count;                    /**< Bits enabled per port, 1-4 */
    vtss_sgpio_port_conf_t port_conf[VTSS_SGPIO_PORTS];  /**< Port configuration */
} vtss_sgpio_conf_t;

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
vtss_rc vtss_sgpio_conf_get(const vtss_inst_t        inst,
                            const vtss_chip_no_t     chip_no,
                            const vtss_sgpio_group_t group,
                            vtss_sgpio_conf_t        *const conf);

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
vtss_rc vtss_sgpio_conf_set(const vtss_inst_t        inst,
                            const vtss_chip_no_t     chip_no,
                            const vtss_sgpio_group_t group,
                            const vtss_sgpio_conf_t  *const conf);

/** \brief SGPIO read data for a port */
typedef struct
{
    BOOL value[4]; /**< Data for each and bit */
} vtss_sgpio_port_data_t;

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
vtss_rc vtss_sgpio_read(const vtss_inst_t        inst,
                        const vtss_chip_no_t     chip_no,
                        const vtss_sgpio_group_t group,
                        vtss_sgpio_port_data_t   data[VTSS_SGPIO_PORTS]);
/**
 * \brief Get SGPIO event indication
 *
 * \param inst [IN]          Target instance reference.
 * \param chip_no [IN]       Chip number (if multi-chip instance).
 * \param group [IN]         SGPIO group.
 * \param bit [IN]           SGPIO port bit (0-3).
 * \param events [OUT]       Event indication for each port for the selected bit - must point to VTSS_SGPIO_PORTS of BOOL.
 *
 * \return Return code.
 **/
vtss_rc vtss_sgpio_event_poll(const vtss_inst_t        inst,
                              const vtss_chip_no_t     chip_no,
                              const vtss_sgpio_group_t group,
                              const u32                bit,
                              BOOL                     *const events);

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
vtss_rc vtss_sgpio_event_enable(const vtss_inst_t        inst,
                                const vtss_chip_no_t     chip_no,
                                const vtss_sgpio_group_t group,
                                const vtss_port_no_t     port,
                                const u32                bit,
                                BOOL                     enable);

#endif /* VTSS_FEATURE_SERIAL_GPIO */


#if defined(VTSS_FEATURE_INTERRUPTS)

/**
 * \brief Configure interrupt.
 * \param inst [IN] Target instance reference.
 * \param mask [IN] Interrupt mask - Configures the interrupts for the bits set in the mask.
 * \param polarity [IN] Polarity - Interrupt polarity.
 * \param enable [IN] Enable   - 1 = enable, 0 = disable.
 *
 * \return Return code.
**/
vtss_rc vtss_intr_cfg(const vtss_inst_t       inst,
                      const u32               mask,
                      const BOOL              polarity,
                      const BOOL              enable);


/**
\brief Interrupt source structure.
*/
typedef struct {
    BOOL  link_change[VTSS_PORT_ARRAY_SIZE]; /**< Applies to XAUI, 100FX and 1000X ports */
} vtss_intr_t;

/**
 * \brief Set the interrupt mask.
 * \param inst [IN] Target instance reference.
 * \param mask [IN] Pointer to mask structure.
 *
 * \return Return code.
**/
vtss_rc vtss_intr_mask_set(const vtss_inst_t             inst,
                           vtss_intr_t *mask);

/**
 * \brief Get the interrupt status for all enabled sources.
 *        The interrupt status bit is cleared by the function
 *
 * \param inst [IN] Target instance reference.
 * \param status [OUT] Pointer to a structure with status of all enabled interrupt sources.
 *
 * \return Return code.
 **/
vtss_rc vtss_intr_status_get(const vtss_inst_t             inst,
                             vtss_intr_t *status);

/**
 * \brief This vil negate polarity on fast link fail detection signals when active
 *        This is only intended to be used on Luton26 RevB as a work around for the
 *        Atom PHY interrupt always active problem
 *
 * \param inst [IN] Target instance reference.
 *
 * \return Return code.
 **/
vtss_rc  vtss_intr_pol_negation(const vtss_inst_t   inst);

#endif /* VTSS_FEATURE_INTERRUPTS */

#ifdef VTSS_FEATURE_IRQ_CONTROL

/**
 * \brief Interrupt sources.
 */
typedef enum
{
    VTSS_IRQ_XTR,               /**< Frame Extraction Ready (register-based) */
    VTSS_IRQ_FDMA_XTR,          /**< Frame Extraction Ready (manual DMA-based) */
    VTSS_IRQ_SOFTWARE,          /**< Software IRQ */
    VTSS_IRQ_PTP_RDY,           /**< PTP Timestamp Ready */
    VTSS_IRQ_PTP_SYNC,          /**< PTP Synchronization IRQ */
    VTSS_IRQ_EXT0,              /**< EXT0 IRQ */
    VTSS_IRQ_EXT1,              /**< EXT1 IRQ */
    VTSS_IRQ_OAM,               /**< OAM IRQ */
    VTSS_IRQ_SGPIO,             /**< Serial GPIO IRQ */
    VTSS_IRQ_SGPIO2,            /**< Serial GPIO2 IRQ */
    VTSS_IRQ_DPLL,              /**< DPLL */
    VTSS_IRQ_GPIO,              /**< GPIO */
    VTSS_IRQ_DEV_ALL,           /**< Device (port) IRQ */
    VTSS_IRQ_CU_PHY_0,          /**< LAN966X internal PHY 0 */
    VTSS_IRQ_CU_PHY_1,          /**< LAN966X internal PHY 1 */
    VTSS_IRQ_KR_SD10G_0,        /**< KR IRQ 0 */
    VTSS_IRQ_KR_SD10G_1,        /**< KR IRQ 1 */
    VTSS_IRQ_KR_SD10G_2,        /**< KR IRQ 2 */
    VTSS_IRQ_KR_SD10G_3,        /**< KR IRQ 3 */
    VTSS_IRQ_KR_SD10G_4,        /**< KR IRQ 4 */
    VTSS_IRQ_KR_SD10G_5,        /**< KR IRQ 5 */
    VTSS_IRQ_KR_SD10G_6,        /**< KR IRQ 6 */
    VTSS_IRQ_KR_SD10G_7,        /**< KR IRQ 7 */
    VTSS_IRQ_KR_SD10G_8,        /**< KR IRQ 8 */
    VTSS_IRQ_KR_SD10G_9,        /**< KR IRQ 9 */
    VTSS_IRQ_KR_SD10G_10,       /**< KR IRQ 10 */
    VTSS_IRQ_KR_SD10G_11,       /**< KR IRQ 11 */
    VTSS_IRQ_KR_SD10G_12,       /**< KR IRQ 12 */
    VTSS_IRQ_KR_SD10G_13,       /**< KR IRQ 13 */
    VTSS_IRQ_KR_SD10G_14,       /**< KR IRQ 14 */
    VTSS_IRQ_KR_SD10G_15,       /**< KR IRQ 15 */
    VTSS_IRQ_KR_SD10G_16,       /**< KR IRQ 16 */
    VTSS_IRQ_KR_SD10G_17,       /**< KR IRQ 17 */
    VTSS_IRQ_KR_SD10G_18,       /**< KR IRQ 18 */
    VTSS_IRQ_KR_SD10G_19,       /**< KR IRQ 19 */

    VTSS_IRQ_MAX,               /**< Maximum IRQ Source - MUST be the last in this enum*/
} vtss_irq_t;

/**
 * \brief Interrupt configuration options.
 */
typedef struct {
    BOOL external;               /**< Redirect to external IRQ */
    u8   destination;            /**< IRQ destination index */
} vtss_irq_conf_t;

/**
 * \brief Interrupt status structure.
 */
typedef struct {
    u32 active;         /**< Bitmap for pending IRQs (VTSS_IRQ_xxx) */
    u32 raw_ident;      /**< RAW (target dependentant) bitmap for active pending IRQs */
    u32 raw_status;     /**< RAW (target dependentant) bitmap for all pending IRQs */
    u32 raw_mask;       /**< RAW (target dependentant) bitmap for IRQs mask */
} vtss_irq_status_t;

/**
 * \brief Get IRQ configuration
 *
 * \param inst [IN]     Target instance reference.
 * \param irq  [IN]     Interrupt source.
 * \param conf [OUT]    IRQ configuration.
 *
 * \return Return code.
 **/
vtss_rc  vtss_irq_conf_get(const vtss_inst_t inst,
                           const vtss_irq_t irq,
                           vtss_irq_conf_t *conf);

/**
 * \brief Set IRQ configuration
 *
 * \param inst [IN]     Target instance reference.
 * \param irq  [IN]     Interrupt source.
 * \param conf [IN]     IRQ configuration.
 *
 * \return Return code.
 **/
vtss_rc  vtss_irq_conf_set(const vtss_inst_t inst,
                           const vtss_irq_t irq,
                           const vtss_irq_conf_t *const conf);

/**
 * \brief Get IRQ status (active sources), mask current sources
 *
 * \param inst   [IN]   Target instance reference.
 * \param status [OUT]  IRQ status.
 *
 * \return Return code.
 **/
vtss_rc  vtss_irq_status_get_and_mask(const vtss_inst_t inst,
                                      vtss_irq_status_t *status);

/**
 * \brief Control a specific interrupt source
 *
 * \param inst   [IN]   Target instance reference.
 * \param irq    [IN]   Interrupt source.
 * \param enable [IN]   Enable or disable source.
 *
 * \return Return code.
 **/
vtss_rc  vtss_irq_enable(const vtss_inst_t inst,
                         const vtss_irq_t irq,
                         BOOL enable);

#endif /* VTSS_FEATURE_IRQ_CONTROL */


/* - API tod functions -------------------------------------- */

/**
 * \brief Get the current hw nanosec time
 *  This function is called from interrupt
 * \returns actual ns counter
 */
u32 vtss_tod_get_ns_cnt(void);

/**
 * \brief If the actual HW does not support time stamping, an external callback
 * function can be set up to do the work.
 * \returns actual ns counter.
 */
typedef u32 (*tod_get_ns_cnt_cb_t)(void);  /* Get ns Counter callback  */

/**
 * \brief Set an external hw nanosec read function.
 *
 * \param cb pointer to callback function
 */
void vtss_tod_set_ns_cnt_cb(tod_get_ns_cnt_cb_t cb);

/**
 * vtss_os_timestamp_t
 * VTSS_OS_TIMESTAMP()
 *   These two provides a mean to have the API timestamp events for use
 *   by the application. It is up to the platform specific code to
 *   implement the actual functions to obtain the timestamp.
 *   The implementation *must* be callable from interrupt context, so no
 *   implicit waits or sleeps are allowed.
 */
typedef struct {
    u32 hw_cnt; /**< hardware counter */
} vtss_os_timestamp_t;
#define VTSS_OS_TIMESTAMP(timestamp)                                    \
  do {                                                                  \
    /* Currently no need to lock scheduler, since it's only          */ \
    /* called from a function, where the sceduler is already locked. */ \
    /* cyg_scheduler_lock(__FILE__, __LINE__); */                                         \
    (timestamp)->hw_cnt = vtss_tod_get_ns_cnt();                        \
    /* cyg_scheduler_unlock(__FILE__, __LINE__); */                                       \
  } while(0); /**< VTSS_OS_TIMESTAMP() provides the implementation that will fill in the timestamp. */


/* - Fan control functions -------------------------------------- */
#if defined(VTSS_FEATURE_FAN)

#if defined(VTSS_FEATURE_TEMP_SENSOR)
/**
 * \brief Initialize the temperature sensor
 *
 * \param inst [IN]        Target instance reference
 * \param enable [IN]       Set to true if sensor shall be active else false
 *
 * \return Return code.
 **/
vtss_rc vtss_temp_sensor_init(const vtss_inst_t inst,
                              const BOOL enable);

/**
 * \brief Read temperature sensor value
 *
 * \param inst [IN]        Target instance reference
 * \param temperature [OUT]      Temperature from sensor (range from -46 to 135 degC)
 *
 * \return Return code.
 **/

vtss_rc vtss_temp_sensor_get(const vtss_inst_t     inst,
                             i16                   *temperature);
#endif

/** \brief FAN PWM frequency */
typedef enum
{
    VTSS_FAN_PWM_FREQ_25KHZ,
    VTSS_FAN_PWM_FREQ_120HZ,
    VTSS_FAN_PWM_FREQ_100HZ,
    VTSS_FAN_PWM_FREQ_80HZ,
    VTSS_FAN_PWM_FREQ_60HZ,
    VTSS_FAN_PWM_FREQ_40HZ,
    VTSS_FAN_PWM_FREQ_20HZ,
    VTSS_FAN_PWM_FREQ_10HZ
} vtss_fan_pwd_freq_t;

/** \brief FAN Types  */
typedef enum
{
    VTSS_FAN_2_WIRE_TYPE,
    VTSS_FAN_3_WIRE_TYPE,
    VTSS_FAN_4_WIRE_TYPE
} vtss_fan_type_t;


/** \brief Maximum fan speed level (Fan runs at full speed) */
#define VTSS_FAN_SPEED_MAX 0x255
/** \brief Minimum fan speed level (Fan is OFF) */
#define VTSS_FAN_SPEED_MIN 0x0


/** \brief Fan specifications */
typedef struct
{
    vtss_fan_pwd_freq_t fan_pwm_freq;      /**< Fan PWM frequency*/
    BOOL                fan_low_pol;       /**< Fan polarity of the PWM output. TRUE = PWM is logic 0 when on. FALSE = PWM is logic 1 when on */
    BOOL                fan_open_col;      /**< PWM output is open collector if TRUE.*/
    vtss_fan_type_t     type;              /**< 2,3 or 4 wire fan type*/
    u32                 ppr;               /**< Pulses per rotation. Only valid for 3 and 4 wire fans */
} vtss_fan_conf_t;


/**
 * \brief Get the number of fan rotations
 *
 * \param inst [IN]       Target instance reference
 * \param fan_spec [IN]   Fan specification
 * \param rotation_count [OUT] Number of fan rotation countered for the last second.
 *
 * \return Return code.
 **/
vtss_rc vtss_fan_rotation_get(const vtss_inst_t inst,
                              vtss_fan_conf_t   *const fan_spec,
                              u32               *rotation_count);



/**
 * \brief Set fan cool level (Duty cycle)
 *
 * \param inst [IN]       Target instance reference
 * \param lvl  [IN]       Level. 0 = Fan off, 255 = fan fully on
 *
 * \return Return code.
**/
vtss_rc vtss_fan_cool_lvl_set(const vtss_inst_t     inst,
                              u8 lvl);


/**
 * \brief Initialise fan controller)
 *
 * \param inst [IN]    Target instance reference
 * \param spec [IN]    Fan specifications
 *
 * \return Return code.
**/
vtss_rc vtss_fan_controller_init(const vtss_inst_t     inst,
                                 const vtss_fan_conf_t *const spec);



/**
 * \brief Get fan cool level (Duty cycle)
 *
 * \param inst [IN]       Target instance reference
 * \param lvl  [IN]       Level. 0 = Fan off, 255 = fan fully on
 *
 * \return Return code.
**/
vtss_rc vtss_fan_cool_lvl_get(const vtss_inst_t     inst,
                              u8 * lvl);


#endif /* VTSS_FEATURE_FAN */

/* - EEE functions -------------------------------------- */
#ifdef VTSS_FEATURE_EEE
/** \brief EEE port configuration */
typedef struct
{
    BOOL eee_ena;          /**< Enable EEE                                                                                                                                                       */
    u8   eee_fast_queues;  /**< Queues set in this mask will activate egress path as soon as any data is available. Vector for enabling fast queues. bit 0 = queue 0, bit 1 = queue 1 and so on. */
    u16  tx_tw;            /**< Time from path is activated until frame transmission restarted.                                                                                                  */
    u8   lp_advertisement; /**< Link partner EEE advertisement. Bit 0 = Link partner advertises 100BASE-T capability. Bit 1 = Link partner advertises 1000BASE-T capability.                     */

    BOOL optimized_for_power; /**< EEE can be optimized for either most power savings or least traffic latency */
} vtss_eee_port_conf_t;

/**
 * \brief Set EEE configuration
 *
 * \param inst     [IN] Target instance reference
 * \param port_no  [IN] Port number
 * \param eee_conf [IN] EEE configuration
 *
 * \return Return code.
 **/
vtss_rc vtss_eee_port_conf_set(const vtss_inst_t          inst,
                               const vtss_port_no_t       port_no,
                               const vtss_eee_port_conf_t *const eee_conf);

#endif /* VTSS_FEATURE_EEE */

/**
 * \brief Get general purpose data pointer
 *
 * \param inst       [IN]  Target instance reference.
 * \param data       [OUT] Pointer data

 * \return Return code.
 *
 **/
vtss_rc vtss_misc_appdata_get(const vtss_inst_t        inst,
                              void **data);


/**
 * \brief Set general purpose data pointer
 *
 * \param inst       [IN]  Target instance reference.
 * \param data       [IN]  Pointer data

 * \return Return code.
 *
 **/
vtss_rc vtss_misc_appdata_set(const vtss_inst_t        inst,
                              void *data);

/**
 * ============================================================================
 * Symreg
 * ============================================================================
 **/

/** \brief Symbolic descriptiopn of a register. */
typedef struct {
    const char      *name;       /**< Name of register */
    unsigned long   addr;        /**< Address of register */
    unsigned long   repl_cnt;    /**< Replication count of register */
    unsigned long   repl_width;  /**< Replication width of register */
} vtss_symreg_reg_t;

/** \brief Symbolic descriptiopn of a register group. */
typedef struct {
    const char         *name;       /**< Name of register group */
    unsigned long      base_addr;   /**< Base address of register group */
    unsigned long      repl_cnt;    /**< Replication count of register group */
    unsigned long      repl_width;  /**< Replication width of register group */
    vtss_symreg_reg_t const *regs;  /**< Pointer to symbolic registers (null terminated) */
} vtss_symreg_reggrp_t;

/** \brief Symbolic descriptiopn of a register target. */
typedef struct {
    const char            *name;          /**< Name of register target */
    int                   repl_number;    /**< Target instance number */
    unsigned long         tgt_id;         /**< Target ID */
    unsigned long         base_addr;      /**< Base address */
    vtss_symreg_reggrp_t const *reggrps;  /**< Pointer to symbolic register groups (null terminated) */
} vtss_symreg_target_t;

/** \brief Symbolic register base data. */
typedef struct {
    const vtss_symreg_target_t *targets;           /**< Pointer to targets (not null terminated) */
    unsigned long               targets_cnt;       /**< Number of targets */
    unsigned long               io_origin1_offset; /**< IO register offset */
    unsigned long               repl_cnt_max;      /**< Highest number of replications */
    unsigned long               name_len_max;      /**< Max name length */
} vtss_symreg_data_t;

/**
 * \brief Get symbolic register data.
 *
 * \param inst       [IN]  Target instance reference.
 * \param data       [OUT] data

 * \return Return code.
 *
 **/
vtss_rc vtss_symreg_data_get(const vtss_inst_t   inst,
                             vtss_symreg_data_t *const data);

#ifdef __cplusplus
}
#endif
#endif /* VTSS_MISC_API_H_ */
