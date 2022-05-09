// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/**
 * \file
 * \brief Layer 2 API
 * \details This header file describes Layer 2 switching functions
 */

#ifndef _VTSS_L2_API_H_
#define _VTSS_L2_API_H_

#include <vtss/api/types.h>
#include <vtss/api/l2_types.h> /* For vtss_aggr_mode_t and vtss_vid_mac_t */
#include <vtss_port_api.h>
#include <vtss_packet_api.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(VTSS_FEATURE_LAYER2)

/** \page layer2 Layer 2

    The Layer 2 functions are used to control basic switching features.
*/

/* - MAC address table --------------------------------------------- */

/** \page layer2

    \section mac_table MAC Address Table

    The MAC address table functions are used to control the Layer 2 forwarding database.
    Each entry is identified by VLAN ID and MAC address (::vtss_vid_mac_t).
    The following MAC address table functions are available:
    - vtss_mac_table_add() is used to add a static entry.
    - vtss_mac_table_del() is used to delete a static entry.
    - vtss_mac_table_get() is used to lookup a specific entry.
    - vtss_mac_table_get_next() is used to get the next entry for table traversal.
    - vtss_mac_table_age_time_get() is used to get the age time.
    - vtss_mac_table_age_time_set() is used to set the age time.
    - vtss_mac_table_age() is used for manual age scan.
    - vtss_mac_table_vlan_age() is used for manual age scan per VLAN.
    - vtss_mac_table_flush() is used to flush all dynamic entries.
    - vtss_mac_table_port_flush() is used to flush dynamic entries per port.
    - vtss_mac_table_vlan_flush() is used to flush dynamic entries per VLAN.
    - vtss_mac_table_vlan_port_flush() is used to flush dynamic entries per VLAN and port.
    - vtss_mac_table_status_get() is used to poll for MAC address table change events.
    - vtss_learn_port_mode_get() is used to get the learn mode per port.
    - vtss_learn_port_mode_set() is used to set the learn mode per port.

    By default, automatic learning and ageing is enabled.
*/
#if VTSS_OPT_LIGHT
#define VTSS_MAC_ADDRS     128    /**< Number of MAC addresses */
#elif defined(VTSS_ARCH_JAGUAR_2)
#define VTSS_MAC_ADDRS     32768  /**< Number of MAC addresses */
#else
#define VTSS_MAC_ADDRS     8192   /**< Number of MAC addresses */
#endif

#if defined(VTSS_FEATURE_VSTAX)
#define VTSS_VSTAX_UPSIDS             (32)                                         /**< Number of UPSIDs    */
#define VTSS_VSTAX_UPSID_START        ( 0)                                         /**< First UPSID value   */
#define VTSS_VSTAX_UPSID_MIN          VTSS_VSTAX_UPSID_START                       /**< Minimum UPSID value */
#define VTSS_VSTAX_UPSID_MAX          (VTSS_VSTAX_UPSID_MIN+VTSS_VSTAX_UPSIDS - 1) /**< Maximum UPSID value */
#define VTSS_VSTAX_UPSID_LEGAL(upsid) (VTSS_VSTAX_UPSID_MIN <= (upsid) && (upsid) <= VTSS_VSTAX_UPSID_MAX) /**< Checks if UPSIDs is legal */
#define VTSS_VSTAX_UPSID_UNDEF (-1)                                                /**< Undefined UPSID. Only applicable in selected contexts */

#define VTSS_UPSPN_CPU  0xfffffffe /**< MAC address entry is from CPU */
#define VTSS_UPSPN_NONE 0xffffffff /**< Used to indicate end of GLAG list */
#endif /* VTSS_FEATURE_VSTAX */

/** \brief MAC address entry */
typedef struct
{
    vtss_vid_mac_t vid_mac;                            /**< VLAN ID and MAC addr */
    BOOL           destination[VTSS_PORT_ARRAY_SIZE];  /**< Dest. ports */
    BOOL           copy_to_cpu;                        /**< CPU copy flag for DMAC lookup */
    BOOL           copy_to_cpu_smac;                   /**< CPU copy flag for SMAC lookup */
    BOOL           locked;                             /**< Locked/static flag */
#if defined(VTSS_FEATURE_MAC_INDEX_TABLE)
    BOOL           index_table;                        /**< Index table used */
#endif
    BOOL           aged;                               /**< Age flag */
    vtss_packet_rx_queue_t cpu_queue;                  /**< CPU queue */
} vtss_mac_table_entry_t;

/**
 * \brief Add MAC address entry. 
 *
 * \param inst [IN]   Target instance reference.
 * \param entry [IN]  MAC address entry structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_mac_table_add(const vtss_inst_t             inst,
                           const vtss_mac_table_entry_t  *const entry);


/**
 * \brief Delete MAC address entry. 
 *
 * \param inst [IN]    Target instance reference.
 * \param vid_mac [IN]  VLAN ID and MAC address structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_mac_table_del(const vtss_inst_t     inst,
                           const vtss_vid_mac_t  *const vid_mac);


/**
 * \brief Get MAC address entry.
 *
 * \param inst [IN]     Target instance reference.
 * \param vid_mac [IN]  VLAN ID and MAC address.
 * \param entry [OUT]   MAC address entry.
 *
 * \return Return code.
 **/
vtss_rc vtss_mac_table_get(const vtss_inst_t       inst,
                           const vtss_vid_mac_t    *const vid_mac,
                           vtss_mac_table_entry_t  *const entry);


/**
 * \brief Lookup next MAC address entry.
 *
 * \param inst [IN]     Target instance reference.
 * \param vid_mac [IN]  VLAN ID and MAC address.
 * \param entry [OUT]   MAC address entry.
 *
 * \return Return code.
 **/
vtss_rc vtss_mac_table_get_next(const vtss_inst_t       inst,
                                const vtss_vid_mac_t    *const vid_mac,
                                vtss_mac_table_entry_t  *const entry);


/** \brief MAC address table age time */
typedef u32 vtss_mac_table_age_time_t;

/**
 * \brief Get MAC address table age time.
 *
 * \param inst [IN]       Target instance reference.
 * \param age_time [OUT]  MAC age time in seconds. Value zero disables aging. 
 *
 * \return Return code.
 **/
vtss_rc vtss_mac_table_age_time_get(const vtss_inst_t          inst,
                                    vtss_mac_table_age_time_t  *const age_time);


/**
 * \brief Set MAC address table age time.
 *
 * \param inst [IN]      Target instance reference.
 * \param age_time [IN]  MAC age time in seconds. Value zero disables aging. 
 *
 * \return Return code.
 **/
vtss_rc vtss_mac_table_age_time_set(const vtss_inst_t                inst,
                                    const vtss_mac_table_age_time_t  age_time);

/**
 * \brief Do age scan of the MAC address table.
 * This should be done periodically with interval T/2, where T is the age timer.
 *
 * \param inst [IN]  Target instance reference.
 *
 * \return Return code.
 **/
vtss_rc vtss_mac_table_age(const vtss_inst_t  inst);


/**
 * \brief Do VLAN specific age scan of the MAC address table.
 *
 * \param inst [IN]  Target instance reference.
 * \param vid [IN]   VLAN ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_mac_table_vlan_age(const vtss_inst_t  inst,
                                const vtss_vid_t   vid);


/**
 * \brief Flush MAC address table, i.e. remove all unlocked entries.
 * 
 * \param inst [IN]  Target instance reference.
 *
 * \return Return code.
 **/
vtss_rc vtss_mac_table_flush(const vtss_inst_t inst);


/**
 * \brief Delete MAC address entries learned on port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 *
 * \return Return code.
 **/
vtss_rc vtss_mac_table_port_flush(const vtss_inst_t     inst,
                                  const vtss_port_no_t  port_no);


/**
 * \brief Delete MAC address entries learned on VLAN ID.
 *
 * \param inst [IN]  Target instance reference.
 * \param vid [IN]   VLAN ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_mac_table_vlan_flush(const vtss_inst_t  inst,
                                  const vtss_vid_t   vid);


/**
 * \brief Delete MAC address entries learned on port and VLAN ID.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param vid [IN]      VLAN ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_mac_table_vlan_port_flush(const vtss_inst_t     inst,
                                       const vtss_port_no_t  port_no,
                                       const vtss_vid_t      vid);

/** \brief MAC address table status */
typedef struct
{
    vtss_event_t learned;     /**< One or more entries were learned */
    vtss_event_t replaced;    /**< One or more entries were replaced */
    vtss_event_t moved;       /**< One or more entries moved to another port */
    vtss_event_t aged;        /**< One or more entries were aged */
} vtss_mac_table_status_t;

/**
 * \brief Get MAC address table status.
 *
 * \param inst [IN]     Target instance reference.
 * \param status [OUT]  MAC address table status. 
 *
 * \return Return code.
 **/
vtss_rc vtss_mac_table_status_get(const vtss_inst_t        inst,
                                  vtss_mac_table_status_t  *const status);


/** \brief Learning mode */
typedef struct 
{
    BOOL automatic;  /**< Automatic learning done by switch chip (default enabled) */
    BOOL cpu;        /**< Learn frames copied to CPU (default disabled) */
    BOOL discard;    /**< Learn frames discarded (default disabled) */
} vtss_learn_mode_t;

/**
 * \brief Get the learn mode for a port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param mode [OUT]    Learn mode.
 *
 * \return Return code.
 **/
vtss_rc vtss_learn_port_mode_get(const vtss_inst_t     inst,
                                 const vtss_port_no_t  port_no,
                                 vtss_learn_mode_t     *const mode);
/**
 * \brief Set the learn mode for a port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param mode [IN]     Learn mode.
 *
 * \return Return code.
 **/
vtss_rc vtss_learn_port_mode_set(const vtss_inst_t        inst,
                                 const vtss_port_no_t     port_no,
                                 const vtss_learn_mode_t  *const mode);


/* - Operational state --------------------------------------------- */

/** \page layer2

    \section oper_state Operational State

    When the application detects link state changes, the operational port state must be setup.
    This ensures that frames are forwarded to operational ports only. The following functions are available:
    - vtss_port_state_get() is used to get the forwarding state for each port.
    - vtss_port_state_set() is used to set the forwarding state for each port.

    By default, all ports are down.
*/

/**
 * \brief Get port operational state.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param state [OUT]   Port state, TRUE if link is up.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_state_get(const vtss_inst_t     inst,
                            const vtss_port_no_t  port_no,
                            BOOL                  *const state);


/**
 * \brief Set port operational state.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param state [IN]    Port state, TRUE if link is up.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_state_set(const vtss_inst_t     inst,
                            const vtss_port_no_t  port_no,
                            BOOL                  state);



/* - Spanning Tree ------------------------------------------------- */

/** \page layer2

    \section stp Spanning Tree

    The following Spanning Tree functions are available:
    - vtss_stp_port_state_get() is used to get the STP state for a port.
    - vtss_stp_port_state_set() is used to set the STP state for a port.
    - vtss_mstp_vlan_msti_get() is used to get the mapping from VLAN to MSTP instance.
    - vtss_mstp_vlan_msti_set() is used to set the mapping from VLAN to MSTP instance.
    - vtss_mstp_port_msti_state_get() is used to get the MSTP state per MSTP instance and port. 
    - vtss_mstp_port_msti_state_set() is used to set the MSTP state per MSTP instance and port. 

    By default, all ports are in STP forwarding mode.\n
    By default, all VLANs map to the first MSTP instance and all ports are forwarding for that instance.
*/

/** \brief Spanning Tree state */
typedef enum
{
    VTSS_STP_STATE_DISCARDING,  /**< STP state discarding (admin/operational down) */
    VTSS_STP_STATE_LEARNING,    /**< STP state learning */
    VTSS_STP_STATE_FORWARDING   /**< STP state forwarding */
} vtss_stp_state_t;

/**
 * \brief Get Spanning Tree state for a port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param state [OUT]   STP state.
 *
 * \return Return code.
 **/
vtss_rc vtss_stp_port_state_get(const vtss_inst_t     inst,
                                const vtss_port_no_t  port_no,
                                vtss_stp_state_t      *const state);



/**
 * \brief Set Spanning Tree state for a port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param state [IN]    STP state.
 *
 * \return Return code.
 **/
vtss_rc vtss_stp_port_state_set(const vtss_inst_t       inst,
                                const vtss_port_no_t    port_no,
                                const vtss_stp_state_t  state);



#if defined(VTSS_FEATURE_L2_MSTP)

/** \brief MSTP instance number */
typedef u32 vtss_msti_t;

#define VTSS_MSTIS           (65)                         /**<  Number of MSTP instances */
#define VTSS_MSTI_START      (0)                          /**< MSTI start number */
#define VTSS_MSTI_END        (VTSS_MSTI_START+VTSS_MSTIS) /**< MSTI end number */
#define VTSS_MSTI_ARRAY_SIZE VTSS_MSTI_END                /**< MSTI array size */


/**
 * \brief Get MSTP instance mapping for a VLAN.
 *
 * \param inst [IN]   Target instance reference.
 * \param vid [IN]    VLAN ID.
 * \param msti [OUT]  MSTP instance.
 *
 * \return Return code.
 **/
vtss_rc vtss_mstp_vlan_msti_get(const vtss_inst_t  inst,
                                const vtss_vid_t   vid, 
                                vtss_msti_t        *const msti);


/**
 * \brief Set MSTP instance mapping for a VLAN.
 *
 * \param inst [IN]  Target instance reference.
 * \param vid [IN]   VLAN ID.
 * \param msti [IN]  MSTP instance.
 *
 * \return Return code.
 **/
vtss_rc vtss_mstp_vlan_msti_set(const vtss_inst_t  inst,
                                const vtss_vid_t   vid, 
                                const vtss_msti_t  msti);


/**
 * \brief Get MSTP state for a port and MSTP instance.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param msti [IN]     MSTP instance.
 * \param state [OUT]   MSTP state.
 *
 * \return Return code.
 **/
vtss_rc vtss_mstp_port_msti_state_get(const vtss_inst_t     inst,
                                      const vtss_port_no_t  port_no, 
                                      const vtss_msti_t     msti, 
                                      vtss_stp_state_t      *const state);


/**
 * \brief Set MSTP state for a port and MSTP instance.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param msti [IN]     MSTP instance.
 * \param state [IN]    MSTP state.
 *
 * \return Return code.
 **/
vtss_rc vtss_mstp_port_msti_state_set(const vtss_inst_t       inst,
                                      const vtss_port_no_t    port_no, 
                                      const vtss_msti_t       msti, 
                                      const vtss_stp_state_t  state);
#endif // VTSS_FEATURE_L2_MSTP

/* - VLAN ---------------------------------------------------------- */

/** \page layer2

    \section vlan VLAN

    Basic VLAN classification and tag preservation works as follows:\n
    - Untagged and priority-tagged frames received on a port are classified to the Port VLAN ID (PVID).\n
    - VLAN-tagged frames received on a VLAN unaware port are classified to the PVID and the tag is preserved.\n
    - VLAN-tagged frames received on a VLAN aware port are classified to the VLAN ID in the
    tag and the tag is stripped.

    In the egress direction, a tag with the classified VID will be added if the Untagged 
    VID (UVID) of the port is not #VTSS_VID_ALL and the classified VID is different from the
    UVID of the port. Setting the UVID to #VTSS_VID_NULL will cause all frames to have a 
    tag added.\n

    The following VLAN functions are available:
    - vtss_vlan_conf_get() is used to get the global VLAN configuration.
    - vtss_vlan_conf_set() is used to set the global VLAN configuration.
    - vtss_vlan_port_conf_get() is used to get the VLAN port configuration.
    - vtss_vlan_port_conf_set() is used to set the VLAN port configuration.
    - vtss_vlan_tx_tag_get() is used to get the advanced tagging configuration for a VLAN.
    - vtss_vlan_tx_tag_set() is used to set the advanced tagging configuration for a VLAN.
    - vtss_vlan_port_members_get() is used to get the VLAN port members.
    - vtss_vlan_port_members_set() is used to set the VLAN port members.
    - vtss_vlan_vid_conf_get() is used to get VLAN configuration.
    - vtss_vlan_vid_conf_set() is used to set VLAN configuration.
*/

#if defined(VTSS_FEATURE_VLAN_COUNTERS)
/** \page layer2

    - vtss_vlan_counters_get is used to get counters for a VLAN
    - vtss_vlan_counters_clear is used to clear counters for a VLAN
*/
#endif /* VTSS_FEATURE_VLAN_COUNTERS */

/** \page layer2

    By default, all ports are VLAN unaware with port VLAN ID 1 and members of VLAN 1 only.
*/

/** \brief VLAN configuration */
typedef struct {
    vtss_etype_t s_etype; /**< Alternative S-tag Ethernet Type */
} vtss_vlan_conf_t;

/**
 * \brief Get VLAN configuration.
 *
 * \param inst [IN]   Target instance reference.
 * \param conf [OUT]  VLAN configuration structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_vlan_conf_get(const vtss_inst_t inst,
                           vtss_vlan_conf_t  *const conf);

/**
 * \brief Set VLAN configuration.
 *
 * \param inst [IN]  Target instance reference.
 * \param conf [IN]  VLAN configuration structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_vlan_conf_set(const vtss_inst_t      inst,
                           const vtss_vlan_conf_t *const conf);

/** \brief VLAN port type configuration */
typedef enum
{
    VTSS_VLAN_PORT_TYPE_UNAWARE, /**< VLAN unaware port */
    VTSS_VLAN_PORT_TYPE_C,       /**< C-port */
    VTSS_VLAN_PORT_TYPE_S,       /**< S-port */
    VTSS_VLAN_PORT_TYPE_S_CUSTOM /**< S-port using alternative Ethernet Type */
} vtss_vlan_port_type_t;

/** \brief VLAN port configuration */
typedef struct
{
    vtss_vlan_port_type_t port_type;      /**< Port type (ingress and egress) */
    vtss_vid_t            pvid;           /**< Port VLAN ID (PVID, ingress) */
    vtss_vid_t            untagged_vid;   /**< Port untagged VLAN ID (UVID, egress) */
    vtss_vlan_frame_t     frame_type;     /**< Acceptable frame type (ingress) */
    BOOL                  ingress_filter; /**< Ingress filtering */
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
    vtss_etype_t          s_etype;        /**< Alternative S-tag Ethernet Type, if non-zero */
#endif
} vtss_vlan_port_conf_t;

/**
 * \brief Get VLAN mode for port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    VLAN port configuration structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_vlan_port_conf_get(const vtss_inst_t      inst,
                                const vtss_port_no_t   port_no,
                                vtss_vlan_port_conf_t  *const conf);



/**
 * \brief Set VLAN mode for port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     VLAN port configuration structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_vlan_port_conf_set(const vtss_inst_t            inst,
                                const vtss_port_no_t         port_no,
                                const vtss_vlan_port_conf_t  *const conf);


/**
 * \brief Get VLAN membership.
 *
 * \param inst [IN]     Target instance reference.
 * \param vid [IN]      VLAN ID.
 * \param member [OUT]  VLAN port member list.
 *
 * \return Return code.
 **/
vtss_rc vtss_vlan_port_members_get(const vtss_inst_t  inst,
                                   const vtss_vid_t   vid,
                                   BOOL               member[VTSS_PORT_ARRAY_SIZE]);



/**
 * \brief Set VLAN membership.
 *
 * \param inst [IN]    Target instance reference.
 * \param vid [IN]     VLAN ID.
 * \param member [IN]  VLAN port member list.
 *
 * \return Return code.
 **/
vtss_rc vtss_vlan_port_members_set(const vtss_inst_t  inst,
                                   const vtss_vid_t   vid,
                                   const BOOL         member[VTSS_PORT_ARRAY_SIZE]);

/** \brief VLAN ID configuration */
typedef struct
{
    BOOL       learning; /**< Enable/disable learning */
    BOOL       flooding; /**< Enable/disable flooding */
    BOOL       mirror;   /**< Enable/disable mirroring */
    BOOL       ingress_filter; /**< Ingress filtering */
#if defined(VTSS_FEATURE_VLAN_SVL)
    vtss_vid_t fid;      /**< Forwarding ID for SVL/IVL control */
#endif /* VTSS_FEATURE_VLAN_SVL */
} vtss_vlan_vid_conf_t;

/**
 * \brief Get VLAN ID configuration
 *
 * \param inst [IN]   Target instance reference.
 * \param vid [IN]    VLAN ID.
 * \param conf [OUT]  VLAN configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_vlan_vid_conf_get(const vtss_inst_t    inst,
                               const vtss_vid_t     vid,
                               vtss_vlan_vid_conf_t *const conf);

/**
 * \brief Set VLAN ID configuration
 *
 * \param inst [IN]  Target instance reference.
 * \param vid [IN]   VLAN ID.
 * \param conf [IN]  VLAN configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_vlan_vid_conf_set(const vtss_inst_t          inst,
                               const vtss_vid_t           vid,
                               const vtss_vlan_vid_conf_t *const conf);

/** \brief VLAN Tx tag type */
typedef enum
{
    VTSS_VLAN_TX_TAG_PORT,    /**< Egress tagging determined by VLAN port configuration */
    VTSS_VLAN_TX_TAG_DISABLE, /**< Egress tagging disabled */
    VTSS_VLAN_TX_TAG_ENABLE,  /**< Egress tagging enabled */
} vtss_vlan_tx_tag_t;

/**
 * \brief Get VLAN Tx tagging configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param vid [IN]      VLAN ID.
 * \param tx_tag [OUT]  Tx tagging list.
 *
 * \return Return code.
 **/
vtss_rc vtss_vlan_tx_tag_get(const vtss_inst_t  inst,
                             const vtss_vid_t   vid,
                             vtss_vlan_tx_tag_t tx_tag[VTSS_PORT_ARRAY_SIZE]);

/**
 * \brief Get VLAN Tx tagging configuration.
 *
 * \param inst [IN]    Target instance reference.
 * \param vid [IN]     VLAN ID.
 * \param tx_tag [IN]  Tx tagging list.
 *
 * \return Return code.
 **/
vtss_rc vtss_vlan_tx_tag_set(const vtss_inst_t        inst,
                             const vtss_vid_t         vid,
                             const vtss_vlan_tx_tag_t tx_tag[VTSS_PORT_ARRAY_SIZE]);

#if defined(VTSS_FEATURE_VLAN_COUNTERS)
/** \brief Container for VLAN counters */
typedef struct {
    u64 frames; /**< Number of frames */
    u64 bytes;  /**< Number of bytes */
} vtss_vlan_counter_types_t;

/** \brief VLAN counters */
typedef struct {
    vtss_vlan_counter_types_t rx_vlan_unicast;   /**< Number of received unicast frames or bytes */
    vtss_vlan_counter_types_t rx_vlan_multicast; /**< Number of received multicast frames or bytes */
    vtss_vlan_counter_types_t rx_vlan_broadcast; /**< Number of received broadcast frames or bytes */
} vtss_vlan_counters_t;

/**
 * \brief Get VLAN Counters.
 *
 * \param inst [IN]      Target instance reference.
 * \param vid [IN]       VLAN ID.
 * \param counters [OUT] VLAN counters.
 *
 * \return Return code.
 **/

vtss_rc vtss_vlan_counters_get(const vtss_inst_t    inst,
                               const vtss_vid_t     vid,
                               vtss_vlan_counters_t *const counters);
/**
 * \brief Clear VLAN Counters.
 *
 * \param inst [IN]      Target instance reference.
 * \param vid [IN]       VLAN ID.
 *
 * \return Return code.
 **/

vtss_rc vtss_vlan_counters_clear(const vtss_inst_t    inst,
                                 const vtss_vid_t     vid);

#endif /* VTSS_FEATURE_VLAN_COUNTERS */

#if defined(VTSS_FEATURE_VCAP)

/* - VCL ----------------------------------------------------------- */

/** \page layer2

    \section vcl VLAN Classification List

    Advanced VLAN classification rules can be done using the VLAN Classification List (VCL).
    Each VLAN Classification Entry (VCE) is identified by a VCE ID (::vtss_vce_id_t).
    The following VCL functions are available:
    - vtss_vcl_port_conf_get() is used to get the VCL port configuration.
    - vtss_vcl_port_conf_set() is used to set the VCL port configuration.
    - vtss_vce_init() is used to initialize a VCE to default values.
    - vtss_vce_add() is used to add or modify a VCE.
    - vtss_vce_del() is used to delete a VCE.

    The VCEs are ordered in a list of rules based on the VCE IDs. When adding a rule,
    the VCE ID of the rule and the VCE ID of the next rule in the list must be specified.
    A special value #VTSS_VCE_ID_LAST is used to specify that the rule must be added at the
    end of the list.\n
    Each VCE includes a key structure (::vtss_vce_key_t) with fields used for matching
    received frames and an action structure (::vtss_vce_action_t) with the classified VLAN ID.\n
    By default, no VCE rules are setup.
*/    

/** \brief VCL port configuration */
typedef struct {
    BOOL                 dmac_dip; /**< Enable DMAC/DIP matching (default SMAC/SIP) */
    vtss_vcap_key_type_t key_type; /**< Key type for VCL lookup */
} vtss_vcl_port_conf_t;

/**
 * \brief Get VCL port configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    VCL port configuration structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_vcl_port_conf_get(const vtss_inst_t    inst,
                               const vtss_port_no_t port_no,
                               vtss_vcl_port_conf_t *const conf);

/**
 * \brief Get VCL port configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     VCL port configuration structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_vcl_port_conf_set(const vtss_inst_t          inst,
                               const vtss_port_no_t       port_no,
                               const vtss_vcl_port_conf_t *const conf);

/** \brief VCE frame type */
typedef enum
{
    VTSS_VCE_TYPE_ANY,     /**< Any frame type */
    VTSS_VCE_TYPE_ETYPE,   /**< Ethernet Type */
    VTSS_VCE_TYPE_LLC,     /**< LLC */
    VTSS_VCE_TYPE_SNAP,    /**< SNAP */
    VTSS_VCE_TYPE_IPV4,    /**< IPv4 */
    VTSS_VCE_TYPE_IPV6     /**< IPv6 */
} vtss_vce_type_t;

/** \brief VCE ID type */
typedef u32 vtss_vce_id_t;

#define VTSS_VCL_IDS        256                              /**< Number of VCLs */
#define VTSS_VCL_ID_START   0                                /**< VCL ID start number */
#define VTSS_VCL_ID_END     (VTSS_VCL_ID_START+VTSS_VCL_IDS) /**< VCL ID end number */
#define VTSS_VCL_ARRAY_SIZE VTSS_VCL_ID_END                  /**< VCL ID array size */

#define VTSS_VCE_ID_LAST 0 /**< Special value used to add last in list */

/** \brief VCE MAC header information */
typedef struct 
{
    vtss_vcap_bit_t dmac_mc; /**< Multicast DMAC */
    vtss_vcap_bit_t dmac_bc; /**< Broadcast DMAC */
#if defined(VTSS_FEATURE_VCL_KEY_DMAC)
    vtss_vcap_u48_t dmac;    /**< DMAC */
#endif
    vtss_vcap_u48_t smac;    /**< SMAC */
} vtss_vce_mac_t;

/** \brief VCE tag information */
typedef struct 
{
    vtss_vcap_vid_t vid;    /**< VLAN ID (12 bit) */
    vtss_vcap_u8_t  pcp;    /**< PCP (3 bit) */
    vtss_vcap_bit_t dei;    /**< DEI */
    vtss_vcap_bit_t tagged; /**< Tagged/untagged frame */
    vtss_vcap_bit_t s_tag;  /**< S-tag type */
} vtss_vce_tag_t;

/** \brief Frame data for VTSS_VCE_TYPE_ETYPE */
typedef struct 
{
    vtss_vcap_u16_t etype; /**< Ethernet Type value */
    vtss_vcap_u32_t data;  /**< MAC data */ 
    vtss_vcap_u8_t  mel;   /**< MEG level (7 bit) */
} vtss_vce_frame_etype_t;

/** \brief Frame data for VTSS_VCE_TYPE_LLC */
typedef struct 
{
    vtss_vcap_u48_t data; /**< Data */
} vtss_vce_frame_llc_t;

/** \brief Frame data for VTSS_VCE_TYPE_SNAP */
typedef struct 
{
    vtss_vcap_u48_t data; /**< Data */
} vtss_vce_frame_snap_t;

/** \brief Frame data for VTSS_VCE_TYPE_IPV4 */
typedef struct 
{
    vtss_vcap_bit_t fragment; /**< Fragment */
    vtss_vcap_bit_t options;  /**< Header options */
    vtss_vcap_vr_t  dscp;     /**< DSCP field (6 bit) */
    vtss_vcap_u8_t  proto;    /**< Protocol */
    vtss_vcap_ip_t  sip;      /**< Source IP address */
#if defined(VTSS_FEATURE_VCL_KEY_DIP)
    vtss_vcap_ip_t  dip;      /**< Destination IP address */
#endif
    vtss_vcap_vr_t  sport;    /**< UDP/TCP: Source port */
    vtss_vcap_vr_t  dport;    /**< UDP/TCP: Destination port */
} vtss_vce_frame_ipv4_t;

/** \brief Frame data for VTSS_VCE_TYPE_IPV6 */
typedef struct 
{
    vtss_vcap_vr_t   dscp;  /**< DSCP field (6 bit) */
    vtss_vcap_u8_t   proto; /**< Protocol */
    vtss_vcap_u128_t sip;   /**< Source IP address */
#if defined(VTSS_FEATURE_VCL_KEY_DIP)
    vtss_vcap_u128_t dip;   /**< Destination IP address */
#endif
    vtss_vcap_vr_t  sport; /**< UDP/TCP: Source port */
    vtss_vcap_vr_t  dport; /**< UDP/TCP: Destination port */
} vtss_vce_frame_ipv6_t;

/** \brief VCE Key*/
typedef struct
{
    BOOL            port_list[VTSS_PORT_ARRAY_SIZE]; /**< Port list */ 
    vtss_vce_mac_t  mac;                             /**< MAC header */
    vtss_vce_tag_t  tag;                             /**< Outer tag */
#if defined(VTSS_FEATURE_QCL_KEY_INNER_TAG)
    vtss_vce_tag_t  inner_tag;                       /**< Inner Tag */
#endif
    vtss_vce_type_t type;                            /**< VCE frame type */
    
    union
    {
        /* VTSS_VCE_TYPE_ANY: No specific fields */
        vtss_vce_frame_etype_t etype; /**< VTSS_VCE_TYPE_ETYPE */
        vtss_vce_frame_llc_t   llc;   /**< VTSS_VCE_TYPE_LLC */
        vtss_vce_frame_snap_t  snap;  /**< VTSS_VCE_TYPE_SNAP */
        vtss_vce_frame_ipv4_t  ipv4;  /**< VTSS_VCE_TYPE_IPV4 */
        vtss_vce_frame_ipv6_t  ipv6;  /**< VTSS_VCE_TYPE_IPV6 */
    } frame;  /**< Frame type specific data */
} vtss_vce_key_t;

/** \brief Ingress map selection */
typedef enum {
    VTSS_IMAP_SEL_DISABLE, /**< Ingress map not used */
    VTSS_IMAP_SEL_OUTER,   /**< Ingress map used for outer tag */
    VTSS_IMAP_SEL_INNER,   /**< Ingress map used for inner tag */
} vtss_imap_sel_t;

typedef enum {
    VTSS_OAM_DETECT_NONE,              /**< No OAM detection */
    VTSS_OAM_DETECT_UNTAGGED,          /**< Untagged OAM detection */
    VTSS_OAM_DETECT_SINGLE_TAGGED,     /**< Single tagged OAM detection */
    VTSS_OAM_DETECT_DOUBLE_TAGGED,     /**< Double tagged OAM detection */
    VTSS_OAM_DETECT_TRIPLE_TAGGED      /**< Triple tagged OAM detection */
} vtss_oam_detect_t;

/** \brief VCE Action */
typedef struct
{
    vtss_vid_t                vid;        /**< Classified VLAN ID */
    vtss_acl_policy_no_t      policy_no;  /**< ACL policy number */
    BOOL                      pop_enable; /**< Tag pop enable */
    u8                        pop_cnt;    /**< Tag pop count */
#if defined(VTSS_FEATURE_QOS_INGRESS_MAP)
    vtss_imap_sel_t           map_sel;    /**< Ingress map selection */
    vtss_qos_ingress_map_id_t map_id;     /**< Ingress map to use for classification */
#endif
#if defined(VTSS_FEATURE_XFLOW)
    vtss_iflow_id_t           flow_id;    /**< Ingress flow ID */
    vtss_oam_detect_t         oam_detect; /**< OAM detection. Mark this frame as containing OAM behind a number of tags. */
#endif
    BOOL                      prio_enable; // Enable priority classification
    vtss_prio_t               prio;        // Priority value
    BOOL                      dp_enable;   // Enable DP classification
    vtss_dp_level_t           dp;          // DP value
    BOOL                      dscp_enable; // Enable DSCP classification
    vtss_dscp_t               dscp;        // DSCP value
    BOOL                      pcp_enable;  // Enable PCP classification
    vtss_pcp_t                pcp;         // PCP value
    BOOL                      dei_enable;  // Enable DEI classification
    vtss_dei_t                dei;         // DEI value
} vtss_vce_action_t;

/** \brief VLAN Control Entry */
typedef struct
{
    vtss_vce_id_t     id;     /**< VCE ID */
    vtss_vce_key_t    key;    /**< VCE Key */
    vtss_vce_action_t action; /**< VCE Action */
} vtss_vce_t;

/**
 * \brief Initialize VCE to default values.
 *
 * \param inst [IN]  Target instance reference.
 * \param type [IN]  VCE type.
 * \param vce [OUT]  VCE structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_vce_init(const vtss_inst_t      inst,
                      const vtss_vce_type_t  type,
                      vtss_vce_t             *const vce);


/**
 * \brief Add/modify VCE.
 *
 * \param inst [IN]    Target instance reference.
 * \param vce_id [IN]  VCE ID. The VCE will be added before the entry with this ID. 
 *                     VTSS_VCE_ID_LAST is reserved for inserting last.
 * \param vce [IN]     VCE structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_vce_add(const vtss_inst_t    inst,
                     const vtss_vce_id_t  vce_id,
                     const vtss_vce_t     *const vce);



/**
 * \brief Delete VCE.
 *
 * \param inst [IN]    Target instance reference.
 * \param vce_id [IN]  VCE ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_vce_del(const vtss_inst_t    inst,
                     const vtss_vce_id_t  vce_id);
#endif // VTSS_FEATURE_VCAP

/** \brief Class/COSID count */
typedef u8 vtss_class_cnt_t;

#if defined(VTSS_FEATURE_XSTAT)

/* - Ingress counters ---------------------------------------------- */

/** \brief Ingress counter ID */
typedef u16 vtss_ingress_cnt_id_t;

/**
 * \brief Allocate ingress counters.
 *
 * \param inst [IN]  Target instance reference.
 * \param cnt [IN]   Number of classes/COSIDs
 * \param id [OUT]   Ingress counter ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_ingress_cnt_alloc(const vtss_inst_t      inst,
                               const vtss_class_cnt_t cnt,
                               vtss_ingress_cnt_id_t  *const id);

/**
 * \brief Free ingress counters.
 *
 * \param inst [IN]  Target instance reference.
 * \param id [IN]    Ingress counter ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_ingress_cnt_free(const vtss_inst_t           inst,
                              const vtss_ingress_cnt_id_t id);

/** \brief Ingress counters */
typedef struct {
    // For the following counter pairs, only the frame counters are valid in PSFP mode
    vtss_counter_pair_t rx_green;        // Rx green frames/bytes
    vtss_counter_pair_t rx_yellow;       // Rx yellow frames/bytes
    vtss_counter_pair_t rx_red;          // Rx red frames/bytes

    // The following counters are only valid in PSFP mode
#if defined(VTSS_FEATURE_PSFP)
    vtss_counter_t      rx_match;        // MatchingFramesCount: Rx matching frames
    vtss_counter_t      rx_gate_pass;    // PassingFramesCount: Rx passed gate
    vtss_counter_t      rx_gate_discard; // NotPassingFramesCount: Rx discarded by gate
    vtss_counter_t      rx_sdu_pass;     // PassingSDUCount: Rx passed maximum SDU size filter
    vtss_counter_t      rx_sdu_discard;  // NotPassingSDUCount: Rx discarded by maximum SDU size filter
#endif

    // The following counters are valid in any mode
    vtss_counter_pair_t rx_discard;      // Rx discarded frames/bytes
    vtss_counter_pair_t tx_discard;      // Tx discarded frames/bytes
} vtss_ingress_counters_t;

/**
 * \brief Get ingress counters.
 *
 * \param inst [IN]       Target instance reference.
 * \param id [IN]         Ingress counter ID.
 * \param cosid [IN]      COSID.
 * \param counters [OUT]  Counters.
 *
 * \return Return code.
 **/
vtss_rc vtss_ingress_cnt_get(const vtss_inst_t           inst,
                             const vtss_ingress_cnt_id_t id,
                             const vtss_cosid_t          cosid,
                             vtss_ingress_counters_t     *counters);

/**
 * \brief Clear ingress counters.
 *
 * \param inst [IN]   Target instance reference.
 * \param id [IN]     Ingress counter ID.
 * \param cosid [IN]  COSID.
 *
 * \return Return code.
 **/
vtss_rc vtss_ingress_cnt_clear(const vtss_inst_t           inst,
                               const vtss_ingress_cnt_id_t id,
                               const vtss_cosid_t          cosid);

#endif /* VTSS_FEATURE_XSTAT */

#if defined(VTSS_FEATURE_XDLB)

/* - Dual Leaky Bucket policers ------------------------------------ */

/** \brief DLB policer ID */
typedef u16 vtss_dlb_policer_id_t;

/**
 * \brief Allocate DLB policers.
 *
 * \param inst [IN]  Target instance reference.
 * \param cnt [IN]   Number of classes/COSIDs
 * \param id [OUT]   DLB policer ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_dlb_policer_alloc(const vtss_inst_t      inst,
                               const vtss_class_cnt_t cnt,
                               vtss_dlb_policer_id_t  *const id);

/**
 * \brief Free DLB policers.
 *
 * \param inst [IN]  Target instance reference.
 * \param id [IN]    DLB policer ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_dlb_policer_free(const vtss_inst_t           inst,
                              const vtss_dlb_policer_id_t id);

/**
 * \brief Get DLB policer configuration.
 *
 * \param inst [IN]   Target instance reference.
 * \param id [IN]     DLB policer ID.
 * \param cosid [IN]  COSID.
 * \param conf [OUT]  Policer configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_dlb_policer_conf_get(const vtss_inst_t           inst,
                                  const vtss_dlb_policer_id_t id,
                                  const vtss_cosid_t          cosid,
                                  vtss_dlb_policer_conf_t     *const conf);

/**
 * \brief Set DLB policer configuration.
 *
 * \param inst [IN]   Target instance reference.
 * \param id [IN]     DLB policer ID.
 * \param cosid [IN]  COSID.
 * \param conf [IN]   Policer configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_dlb_policer_conf_set(const vtss_inst_t             inst,
                                  const vtss_dlb_policer_id_t   id,
                                  const vtss_cosid_t            cosid,
                                  const vtss_dlb_policer_conf_t *const conf);
#if defined(VTSS_FEATURE_PSFP)
// DLB policer status
typedef struct {
    BOOL mark_all_red; // MarkAllFramesRed: Discard all frames if red frame seen
} vtss_dlb_policer_status_t;

// Get DLB policer status.
// id [IN]       DLB policer ID.
// cosid [IN]    COSID.
// status [OUT]  DLB policer status.
vtss_rc vtss_dlb_policer_status_get(const vtss_inst_t           inst,
                                    const vtss_dlb_policer_id_t id,
                                    const vtss_cosid_t          cosid,
                                    vtss_dlb_policer_status_t   *const status);
#endif /* VTSS_FEATURE_PSFP */

#endif /* VTSS_FEATURE_XDLB */

#if defined(VTSS_FEATURE_XFLOW)

/* - Ingress flow -------------------------------------------------- */

/**
 * \brief Allocate ingress flow.
 *
 * \param inst [IN]  Target instance reference.
 * \param id [OUT]   Ingress flow ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_iflow_alloc(const vtss_inst_t inst,
                         vtss_iflow_id_t   *const id);

/**
 * \brief Free ingress flow.
 *
 * \param inst [IN]  Target instance reference.
 * \param id [IN]    Ingress flow ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_iflow_free(const vtss_inst_t     inst,
                        const vtss_iflow_id_t id);

/** \brief Ingress flow configuration */
typedef struct
{
#if defined(VTSS_FEATURE_XSTAT)
    BOOL                  cnt_enable; /**< Enable ingress counter mapping */
    vtss_ingress_cnt_id_t cnt_id;     /**< Ingress counter ID */
#endif
#if defined(VTSS_FEATURE_XDLB)
    BOOL                  dlb_enable; /**< Enable DLB policer */
    vtss_dlb_policer_id_t dlb_id;     /**< DLB policer ID */
#endif
#if defined(VTSS_FEATURE_VOP)
    vtss_voe_idx_t        voe_idx;    /**< VOE index or VTSS_VOE_IDX_NONE */
#endif
#if defined(VTSS_FEATURE_VOP_V2)
    vtss_voi_idx_t        voi_idx;    /**< VOI (MIP) index or VTSS_VOI_IDX_NONE */
#endif
#if defined(VTSS_FEATURE_FRER)
    vtss_frer_iflow_conf_t frer;      // FRER ingress flow configuration
#endif
#if defined(VTSS_FEATURE_PSFP)
    vtss_psfp_iflow_conf_t psfp;      // PSFP ingress flow configuration
#endif
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_CUT_THROUGH)
    BOOL                   cut_through_disable; // Force store-and-forward
#endif
} vtss_iflow_conf_t;

/**
 * \brief Get ingress flow configuration.
 *
 * \param inst [IN]   Target instance reference.
 * \param id [IN]     Ingress flow ID.
 * \param conf [OUT]  Ingress flow configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_iflow_conf_get(const vtss_inst_t     inst,
                            const vtss_iflow_id_t id,
                            vtss_iflow_conf_t     *const conf);

/**
 * \brief Set ingress flow configuration.
 *
 * \param inst [IN]  Target instance reference.
 * \param id [IN]    Ingress flow ID.
 * \param conf [IN]  Flow configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_iflow_conf_set(const vtss_inst_t       inst,
                            const vtss_iflow_id_t   id,
                            const vtss_iflow_conf_t *const conf);

#endif /* VTSS_FEATURE_XFLOW */

#if defined(VTSS_FEATURE_VCAP)

/* - Tag Control List ---------------------------------------------- */

/** \brief TCE ID type */
typedef u32 vtss_tce_id_t;

#define VTSS_TCE_ID_LAST 0 /**< Special value used to add last in list */

/** \brief Egress flow ID */
typedef u16 vtss_eflow_id_t;

#define VTSS_EFLOW_ID_NONE 0      /**< No flow ID allocated */

/** \brief TCE Key */
typedef struct
{
    BOOL            port_list[VTSS_PORT_ARRAY_SIZE]; /**< Port list */
    vtss_vid_t      vid;                             /**< Classified VLAN ID (zero means any VID) */
#if defined(VTSS_FEATURE_XFLOW)
    BOOL            flow_enable;                     /**< Enable ingress flow ID instead of VLAN ID */
    vtss_iflow_id_t flow_id;                         /**< Ingress flow ID */
#endif
} vtss_tce_key_t;

/** \brief TCE TPID selection */
typedef enum {
    VTSS_TPID_SEL_PORT,    /**< Tag pushed according to port VLAN configuration */
    VTSS_TPID_SEL_NONE,    /**< No tag pushed */
    VTSS_TPID_SEL_C,       /**< C-tag pushed */
    VTSS_TPID_SEL_S,       /**< S-tag pushed */
    VTSS_TPID_SEL_S_CUSTOM /**< S-custom tag pushed */
} vtss_tpid_sel_t;

/** \brief TCE PCP selection */
typedef enum {
    VTSS_PCP_SEL_PORT,       /**< PCP selected according to port QoS configuration */
    VTSS_PCP_SEL_FIXED,      /**< Fixed PCP value */
    VTSS_PCP_SEL_CLASSIFIED, /**< Classified PCP value */
    VTSS_PCP_SEL_MAPPED      /**< Mapped PCP value */
} vtss_pcp_sel_t;

/** \brief TCE DEI selection */
typedef enum {
    VTSS_DEI_SEL_PORT,       /**< DEI selected according to port QoS configuration */
    VTSS_DEI_SEL_FIXED,      /**< Fixed DEI value */
    VTSS_DEI_SEL_CLASSIFIED, /**< Classified DEI value */
    VTSS_DEI_SEL_MAPPED      /**< Mapped DEI value */
} vtss_dei_sel_t;

/** \brief TCE tag information */
typedef struct
{
    vtss_tpid_sel_t          tpid;    /**< TPID selection */
    vtss_vid_t               vid;     /**< VLAN ID, value zero means classified */
    vtss_pcp_sel_t           pcp_sel; /**< PCP selection */
    vtss_pcp_t               pcp;     /**< PCP value */
    vtss_dei_sel_t           dei_sel; /**< DEI selection */
    vtss_dei_t               dei;     /**< DEI value */
#if defined(VTSS_FEATURE_QOS_EGRESS_MAP)
    vtss_qos_egress_map_id_t map_id;  /**< Egress QoS map */
#endif
} vtss_tce_tag_t;

#if defined(VTSS_FEATURE_FRER)
// R-tag selection
typedef enum {
    VTSS_RTAG_SEL_NONE,  // No R-tag pushed
    VTSS_RTAG_SEL_OUTER, // Outer R-tag pushed
    VTSS_RTAG_SEL_INNER, // Inner R-tag pushed
} vtss_rtag_sel_t;

// TCE R-tag information
typedef struct {
    vtss_rtag_sel_t sel; // R-tag push selection
    BOOL            pop; // R-tag popping
} vtss_tce_rtag_t;
#endif

/** \brief TCE Action */
typedef struct
{
    vtss_tce_tag_t  tag;       /**< Outer tag */
    vtss_tce_tag_t  inner_tag; /**< Inner tag */
    u8              pop_cnt;   /**< Tag pop count */
#if defined(VTSS_FEATURE_XFLOW)
    vtss_eflow_id_t flow_id;   /**< Egress flow ID */
#endif
#if defined(VTSS_FEATURE_FRER)
    vtss_tce_rtag_t rtag;      // R-tag
#endif
} vtss_tce_action_t;

/** \brief Tag Control Entry */
typedef struct
{
    vtss_tce_id_t     id;     /**< TCE ID */
    vtss_tce_key_t    key;    /**< TCE Key */
    vtss_tce_action_t action; /**< TCE Action */
} vtss_tce_t;

/**
 * \brief Initialize TCE to default values.
 *
 * \param inst [IN]  Target instance reference.
 * \param tce [OUT]  TCE structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_tce_init(const vtss_inst_t inst,
                      vtss_tce_t        *const tce);

/**
 * \brief Add/modify TCE.
 *
 * \param inst [IN]    Target instance reference.
 * \param tce_id [IN]  TCE ID. The TCE will be added before the entry with this ID.
 *                     VTSS_TCE_ID_LAST is reserved for inserting last.
 * \param tce [IN]     TCE structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_tce_add(const vtss_inst_t   inst,
                     const vtss_tce_id_t tce_id,
                     const vtss_tce_t    *const tce);

/**
 * \brief Delete VCE.
 *
 * \param inst [IN]    Target instance reference.
 * \param tce_id [IN]  TCE ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_tce_del(const vtss_inst_t   inst,
                     const vtss_tce_id_t tce_id);
#endif // VTSS_FEATURE_VCAP

#if defined(VTSS_FEATURE_XSTAT)

/* - Egress counters ----------------------------------------------- */

/** \brief Egress counter ID */
typedef u16 vtss_egress_cnt_id_t;

/**
 * \brief Allocate egress counters.
 *
 * \param inst [IN]  Target instance reference.
 * \param cnt [IN]   Number of classes/COSIDs
 * \param id [OUT]   Egress counter ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_egress_cnt_alloc(const vtss_inst_t      inst,
                              const vtss_class_cnt_t cnt,
                              vtss_egress_cnt_id_t   *const id);

/**
 * \brief Free egress counters.
 *
 * \param inst [IN]  Target instance reference.
 * \param id [IN]    Egress counter ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_egress_cnt_free(const vtss_inst_t          inst,
                             const vtss_egress_cnt_id_t id);

/** \brief Egress counters */
typedef struct {
    vtss_counter_pair_t tx_green;   /**< Tx green frames/bytes */
    vtss_counter_pair_t tx_yellow;  /**< Tx yellow frames/bytes */
} vtss_egress_counters_t;

/**
 * \brief Get egress counters.
 *
 * \param inst [IN]       Target instance reference.
 * \param id [IN]         Egress counter ID.
 * \param cosid [IN]      COSID.
 * \param counters [OUT]  Counters.
 *
 * \return Return code.
 **/
vtss_rc vtss_egress_cnt_get(const vtss_inst_t          inst,
                            const vtss_egress_cnt_id_t id,
                            const vtss_cosid_t         cosid,
                            vtss_egress_counters_t     *counters);

/**
 * \brief Clear egress counters.
 *
 * \param inst [IN]   Target instance reference.
 * \param id [IN]     Egress counter ID.
 * \param cosid [IN]  COSID.
 *
 * \return Return code.
 **/
vtss_rc vtss_egress_cnt_clear(const vtss_inst_t          inst,
                              const vtss_egress_cnt_id_t id,
                              const vtss_cosid_t         cosid);

#endif /* VTSS_FEATURE_XSTAT */

#if defined(VTSS_FEATURE_XFLOW)

/* - Egress flow --------------------------------------------------- */

/**
 * \brief Allocate egress flow.
 *
 * \param inst [IN]  Target instance reference.
 * \param id [OUT]   Egress flow ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_eflow_alloc(const vtss_inst_t inst,
                         vtss_eflow_id_t   *const id);

/**
 * \brief Free egress flow.
 *
 * \param inst [IN]  Target instance reference.
 * \param id [IN]    Egress flow ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_eflow_free(const vtss_inst_t     inst,
                        const vtss_eflow_id_t id);

/** \brief Egress flow configuration */
typedef struct
{
#if defined(VTSS_FEATURE_XSTAT)
    BOOL                 cnt_enable; /**< Enable ingress counter mapping */
    vtss_egress_cnt_id_t cnt_id;     /**< Ingress counter ID */
#endif
#if defined(VTSS_FEATURE_VOP)
    vtss_voe_idx_t   voe_idx;        /**< VOE index or VTSS_VOE_IDX_NONE */
#endif
#if defined(VTSS_FEATURE_VOP_V2)
    vtss_voi_idx_t   voi_idx;        /**< VOI (MIP) index or VTSS_VOI_IDX_NONE */
#endif
} vtss_eflow_conf_t;

/**
 * \brief Get egress flow configuration.
 *
 * \param inst [IN]   Target instance reference.
 * \param id [IN]     Egress flow ID.
 * \param conf [OUT]  Egress flow configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_eflow_conf_get(const vtss_inst_t     inst,
                            const vtss_eflow_id_t id,
                            vtss_eflow_conf_t     *const conf);

/**
 * \brief Set egress flow configuration.
 *
 * \param inst [IN]  Target instance reference.
 * \param id [IN]    Egress flow ID.
 * \param conf [IN]  Egress flow configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_eflow_conf_set(const vtss_inst_t       inst,
                            const vtss_eflow_id_t   id,
                            const vtss_eflow_conf_t *const conf);

#endif /* VTSS_FEATURE_XFLOW */

#if defined(VTSS_FEATURE_VCAP)

/* - VLAN translation ---------------------------------------------- */

/** \page layer2

    \section vlan_translation VLAN Translation

    VLAN translation can be used on ports connecting two VLAN domains. If multiple ports are used
    for the connection (e.g. link aggregation), the ports can be grouped. VLAN translation rules
    can be added to each group. The following functions are available:
    - vtss_vlan_trans_group_to_port_get() is used to get the ports of a translation group.
    - vtss_vlan_trans_group_to_port_set() is used to set the ports of a translation group.
    - vtss_vlan_trans_group_add() is used to add a VLAN translation to a group.
    - vtss_vlan_trans_group_del() is used to delete a VLAN translation from a group.

    By default, no VLAN translation rules are setup.
*/  
#define     VTSS_VLAN_TRANS_GROUP_MAX_CNT               VTSS_PORTS     /**< Maximum VLAN Translation Groups count          */
#define     VTSS_VLAN_TRANS_MAX_CNT                     256            /**< Maximum VLAN Translations per group count      */
#define     VTSS_VLAN_TRANS_NULL_GROUP_ID               0              /**< Special value for group ID                     */
#define     VTSS_VLAN_TRANS_FIRST_GROUP_ID              1              /**< First Group ID                                 */
#define     VTSS_VLAN_TRANS_VID_START                   1              /**< First valid VLAN ID                            */
#define     VTSS_VLAN_TRANS_MAX_VLAN_ID                 4095           /**< Last valid VLAN ID                             */
#define     VTSS_VLAN_TRANS_LAST_GROUP_ID               (VTSS_VLAN_TRANS_FIRST_GROUP_ID + VTSS_VLAN_TRANS_GROUP_MAX_CNT - 1)    /**< Last valid Group ID */

#define     VTSS_VLAN_TRANS_VALID_GROUP_CHECK(grp_id)   (((grp_id < VTSS_VLAN_TRANS_FIRST_GROUP_ID) || \
                                                          (grp_id > VTSS_VLAN_TRANS_LAST_GROUP_ID)) ? FALSE : TRUE) /**< Macro to check valid group */
#define     VTSS_VLAN_TRANS_VALID_VLAN_CHECK(vid)       (((vid < VTSS_VLAN_TRANS_VID_START) || (vid > VTSS_VLAN_TRANS_MAX_VLAN_ID)) \
                                                         ? FALSE : TRUE)    /**< Macro to check valid VLAN ID  */
#define     VTSS_VLAN_TRANS_NULL_CHECK(ptr)             ((ptr == NULL) ? FALSE : TRUE)  /**< Macro to check NULL Pointer */
#define     VTSS_VLAN_TRANS_PORT_BF_SIZE                ((VTSS_PORTS + 7)/8)    /**< Macro Same as VTSS_PORT_BF_SIZE */
typedef u64 vtss_vt_id_t;   /**< VLAN Translation ID */

/** \brief VLAN translation port-to-group configuration */
typedef struct {
    u16          group_id;                              /**< Group ID                        */
    u8           ports[VTSS_VLAN_TRANS_PORT_BF_SIZE];   /**< Ports Bitfield                  */
} vtss_vlan_trans_port2grp_conf_t;

/** \brief VLAN translation direction */
typedef enum {
    VTSS_VLAN_TRANS_DIR_BOTH,     /**< Bidirectional translation */
    VTSS_VLAN_TRANS_DIR_INGRESS,  /**< Ingress translation */
    VTSS_VLAN_TRANS_DIR_EGRESS    /**< Egress translation */
} vtss_vlan_trans_dir_t;

/** \brief VLAN translation group-to-VLAN configuration */
typedef struct {
    u16                   group_id;  /**< Group ID */
    vtss_vid_t            vid;       /**< External VLAN ID (ingress key, egress data) */
    vtss_vid_t            trans_vid; /**< Internal VLAN ID (egress key, ingress data) */
    vtss_vlan_trans_dir_t dir;       /**< Direction */
} vtss_vlan_trans_grp2vlan_conf_t;

/**
 * \brief Create VLAN Translation Group entry
 *
 * \param inst [IN] Target instance reference.
 * \param conf [IN] Translation configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_vlan_trans_group_conf_add(const vtss_inst_t                     inst,
                                       const vtss_vlan_trans_grp2vlan_conf_t *const conf);

/**
 * \brief Delete VLAN Translation Group entry
 *
 * \param inst [IN] Target instance reference.
 * \param conf [IN] Translation configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_vlan_trans_group_conf_del(const vtss_inst_t                     inst,
                                       const vtss_vlan_trans_grp2vlan_conf_t *const conf);

/**
 * \brief Create VLAN Translation Group entry.   
 *
 * \param inst      [IN]        Target instance reference.
 * \param group_id  [IN]        Group ID.
 * \param vid       [IN]        VLAN ID.
 * \param trans_vid [IN]        Translated VLAN ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_vlan_trans_group_add(const vtss_inst_t     inst,
                                  const u16             group_id,
                                  const vtss_vid_t      vid,
                                  const vtss_vid_t      trans_vid);

/**
 * \brief Delete VLAN Translation Group entry.   
 *
 * \param inst      [IN]        Target instance reference.
 * \param group_id  [IN]        Group ID.
 * \param vid       [IN]        VLAN ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_vlan_trans_group_del(const vtss_inst_t     inst,
                                  const u16             group_id,
                                  const vtss_vid_t      vid);

/**
 * \brief Get VLAN Translation Group entry.   
 *
 * \param inst      [IN]        Target instance reference.
 * \param conf      [INOUT]     Pointer to vtss_vlan_trans_grp2vlan_conf_t. Input group_id in the conf structure
 * \param next      [IN]        Flag to indicate next entry.
 *
 * \return Return code.
 **/
vtss_rc vtss_vlan_trans_group_get(const vtss_inst_t               inst,
                                  vtss_vlan_trans_grp2vlan_conf_t *conf,
                                  BOOL                            next);

/**
 * \brief Associate VLAN Translation Group entries to a port_list. Only one port can be part 
          of one group not multiple groups.
 *
 * \param inst      [IN]        Target instance reference. 
 * \param conf      [IN]        Pointer to vtss_vlan_trans_port2grp_conf_t. 
 *
 * \return Return code.
 **/
vtss_rc vtss_vlan_trans_group_to_port_set(const vtss_inst_t                     inst,
                                          const vtss_vlan_trans_port2grp_conf_t *conf);

/**
 * \brief VLAN Translation function to fetch all ports for a group.   
 *
 * \param inst      [IN]        Target instance reference. 
 * \param conf      [INOUT]     Pointer to vtss_vlan_trans_port2grp_conf_t.
 * \param next      [IN]        Flag to indicate next entry.
 *
 * \return Return code.
 **/
vtss_rc vtss_vlan_trans_group_to_port_get(const vtss_inst_t                     inst,
                                          vtss_vlan_trans_port2grp_conf_t       *conf,
                                          BOOL                                  next);

#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
/** \brief VCAP port configuration */
typedef struct {
    vtss_vcap_key_type_t key_type_is1_1; /**< Key type for second IS1 lookup */
    BOOL dmac_dip_1;                     /**< Enable DMAC/DIP matching in second lookup (default SMAC/SIP) */
} vtss_vcap_port_conf_t;

/**
 * \brief Get VCAP port configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    VCAP port configuration structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_vcap_port_conf_get(const vtss_inst_t     inst,
                                const vtss_port_no_t  port_no,
                                vtss_vcap_port_conf_t *const conf);

/**
 * \brief Get VCAP port configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     VCAP port configuration structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_vcap_port_conf_set(const vtss_inst_t           inst,
                                const vtss_port_no_t        port_no,
                                const vtss_vcap_port_conf_t *const conf);
#endif /* VTSS_ARCH_OCELOT */

#endif // VTSS_FEATURE_VCAP

/* - Port Isolation------------------------------------------------- */

/** \page layer2

    \section port_iso Port Isolation

    Port isolation can be used to restrict forwarding between ports.
    If isolation is enabled for both the ingress port and the classified VLAN of a frame,
    the frame can not be forwarded to other isolated ports.
    The following functions are available:

    - vtss_isolated_vlan_get() is used to get the isolation mode for a VLAN.
    - vtss_isolated_vlan_set() is used to set the isolation mode for a VLAN.
    - vtss_isolated_port_members_get() is used to get the isolated port members.
    - vtss_isolated_port_members_set() is used to get the isolated port members.

    By default, port isolation is disabled for all ports and VLANs.
*/

/**
 * \brief Get enable/disable port isolation for VLAN.   
 *
 * \param inst [IN]       Target instance reference.
 * \param vid [IN]        VLAN ID.
 * \param isolated [OUT]  VLAN isolation enable/disable option.
 *
 * \return Return code.
 **/
vtss_rc vtss_isolated_vlan_get(const vtss_inst_t  inst,
                               const vtss_vid_t   vid,
                               BOOL               *const isolated);


/**
 * \brief Set enable/disable port isolation for VLAN.   
 *
 * \param inst [IN]      Target instance reference.
 * \param vid [IN]       VLAN ID.
 * \param isolated [IN]  VLAN isolation enable/disable option.
 *
 * \return Return code.
 **/
vtss_rc vtss_isolated_vlan_set(const vtss_inst_t  inst,
                               const vtss_vid_t   vid,
                               const BOOL         isolated);



/**
 * \brief Get the isolated port member set.   
 *
 * \param inst [IN]     Target instance reference.
 * \param member [OUT]  Isolated port member list.
 *
 * \return Return code.
 **/
vtss_rc vtss_isolated_port_members_get(const vtss_inst_t  inst,
                                       BOOL               member[VTSS_PORT_ARRAY_SIZE]);


/**
 * \brief Set the isolated port member set.   
 *
 * \param inst [IN]    Target instance reference.
 * \param member [IN]  Isolated port member list.
 *
 * \return Return code.
 **/
vtss_rc vtss_isolated_port_members_set(const vtss_inst_t  inst,
                                       const BOOL         member[VTSS_PORT_ARRAY_SIZE]);


/* - Private VLAN (PVLAN) ------------------------------------------ */

/** \page layer2

    \section pvlan Private VLAN

    Private VLANs can be used to divide ports into groups and restrict forwarding
    independently of traditional VLANs. Each PVLAN is idendified by a PVLAN number (::vtss_pvlan_no_t).
    Forwarding between two ports is only possible if both ports are included in at least one PVLAN.
    The following functions are available:
    - vtss_pvlan_port_members_get() is used to get the port members of PVLAN.
    - vtss_pvlan_port_members_set() is used to set the port members of PVLAN.

    By default, all ports are included in PVLAN 1.
    
*/

/** \brief Private VLAN Number */
typedef u32 vtss_pvlan_no_t;

#define VTSS_PVLANS            (VTSS_PORTS)                      /**< Number of PVLANs */
#define VTSS_PVLAN_NO_START    (0)                               /**< PVLAN start number */
#define VTSS_PVLAN_NO_END      (VTSS_PVLAN_NO_START+VTSS_PVLANS) /**< PVLAN end number */
#define VTSS_PVLAN_ARRAY_SIZE  VTSS_PVLAN_NO_END                 /**< PVLAN array size */
#define VTSS_PVLAN_NO_DEFAULT  (0)                               /**< Default PVLAN */


/**
 * \brief Get Private VLAN membership.
 *
 * \param inst [IN]      Target instance reference.
 * \param pvlan_no [IN]  Private VLAN group number.
 * \param member [OUT]   Private VLAN port member list.
 *
 * \return Return code.
 **/
vtss_rc vtss_pvlan_port_members_get(const vtss_inst_t      inst,
                                    const vtss_pvlan_no_t  pvlan_no,
                                    BOOL                   member[VTSS_PORT_ARRAY_SIZE]);


/**
 * \brief Set Private VLAN membership.
 *
 * \param inst [IN]      Target instance reference.
 * \param pvlan_no [IN]  Private VLAN group number.
 * \param member [IN]    Private VLAN port member list.
 *
 * \return Return code.
 **/
vtss_rc vtss_pvlan_port_members_set(const vtss_inst_t      inst,
                                    const vtss_pvlan_no_t  pvlan_no,
                                    const BOOL             member[VTSS_PORT_ARRAY_SIZE]);

/** \page layer2

    \section apvlan Asymmetric Private VLAN

    Asymmetric Private VLANs can be used to restrict forwarding independently of traditional VLANs.
    For each ingress port it is possible to define which other egress ports it is allowed to forward to.
    The following functions are available:
    - vtss_apvlan_port_members_get() is used to get the egress port members for an ingress port.
    - vtss_apvlan_port_members_set() is used to set the egress port members for an ingress port.

    By default, all ports are allowed to forward to all other ports.    
*/

/**
* \brief Get Asymmetric Private VLAN membership.
*
* \param inst [IN]     Target instance reference.
* \param port_no [IN]  Ingress port.
* \param member [OUT]  Asymmetric Private VLAN port member list.
*
* \return Return code.
**/
vtss_rc vtss_apvlan_port_members_get(const vtss_inst_t    inst,
                                     const vtss_port_no_t port_no,
                                     BOOL                 member[VTSS_PORT_ARRAY_SIZE]);


/**
* \brief Set Asymmetric Private VLAN membership.
*
* \param inst [IN]     Target instance reference.
* \param port_no [IN]  Ingress port.
* \param member [IN]   Asymmetric Private VLAN port member list.
*
* \return Return code.
**/
vtss_rc vtss_apvlan_port_members_set(const vtss_inst_t    inst,
                                     const vtss_port_no_t port_no,
                                     const BOOL           member[VTSS_PORT_ARRAY_SIZE]);

/** \page layer2

    \section dgroup Destination Port Groups

    Destination Port Groups can be used to ensure that frames are forwarded to all ports in the same group.
    - vtss_dgroup_port_conf_get() is used to get the destination group for a port.
    - vtss_dgroup_port_conf_set() is used to set the destination group for a port.

    By default, each port is in a destination group identical to the port number.
*/

/** \brief EVC policer configuration */
typedef vtss_port_no_t vtss_dgroup_no_t;

/** \brief Destination group port configuration */
typedef struct {
    vtss_dgroup_no_t dgroup_no; /**< Destination port group */
} vtss_dgroup_port_conf_t;

/**
 * \brief Get Destination Group configuration for port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    Destination group port configuration structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_dgroup_port_conf_get(const vtss_inst_t       inst,
                                  const vtss_port_no_t    port_no,
                                  vtss_dgroup_port_conf_t *const conf);

/**
 * \brief Set Destination Group configuration for port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     Destination group port configuration structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_dgroup_port_conf_set(const vtss_inst_t             inst,
                                  const vtss_port_no_t          port_no,
                                  const vtss_dgroup_port_conf_t *const conf);


/* - SFLOW --------------------------------------------------------- */

/** \page layer2

    \section sFlow

    The sFlow functions can be used to sample frame flows.
    - vtss_sflow_port_conf_get() is used to get the sFlow port configuration.
    - vtss_sflow_port_conf_set() is used to set the sFlow port configuration.
    - vtss_sflow_sampling_rate_convert() convers desired sampling rate to actual sampling rate.

    By default, sFlow is disabled on all ports.
 */

/**
 * \brief sFlow configuration structure.
 *
 * Not all sampling rates are supported.
 * Since the sFlow standard mandates that returned sample rates are
 * actual sample rates and not desired sample rates, it is recommended
 * to call vtss_sflow_sampling_rate_convert() to obtain the actual
 * sample rate given a desired sample rate.
 * vtss_sflow_port_conf_set() will auto-convert the requested sample rate
 * to an actual sample rate, which will be returned in subsequent calls
 * to vtss_sflow_port_conf_get().
 */
typedef struct {
    vtss_sflow_type_t type;          /**< Sample direction. Also used to turn off sampling.                             */
    u32               sampling_rate; /**< A value of N means: sample on average 1 out of N frames. 0 disables sampling. */
} vtss_sflow_port_conf_t;

/**
 * \brief Get port sFlow configuration.
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number (a.k.a. data source).
 * \param conf    [OUT] sFlow sampler configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_sflow_port_conf_get(const vtss_inst_t            inst,
                                 const vtss_port_no_t         port_no,
                                       vtss_sflow_port_conf_t *const conf);

/**
 * \brief Set port sFlow configuration.
 *
 * \param inst    [IN] Target instance reference.
 * \param port_no [IN] Port number (a.k.a. data source).
 * \param conf    [IN] sFlow sampler configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_sflow_port_conf_set(const vtss_inst_t            inst,
                                 const vtss_port_no_t         port_no,
                                 const vtss_sflow_port_conf_t *const conf);

/**
 * \brief Convert desired sample rate to supported sample rate
 *
 * Since it may not be possible to realize all desired sample rates
 * in H/W, this function can be used to query for an actual
 * sample rate given a desired sample rate.
 *
 * If the sFlow application code wishes to support more than one
 * sampler instance per port, it will have to use only powers of
 * two for the sampling rate. To obtain powers of two sampling
 * rates, given an arbitrary input sampling rate, set power2 to TRUE,
 * otherwise set it to FALSE.
 *
 * \param inst     [IN]  Target instance reference.
 * \param power2   [IN]  Only return sampling rates in powers of two.
 * \param rate_in  [IN]  Desired sample rate
 * \param rate_out [OUT] Realizable sample rate
 *
 * \return Return code.
 **/
vtss_rc vtss_sflow_sampling_rate_convert(const vtss_inst_t  inst,
                                         const BOOL         power2,
                                         const u32          rate_in,
                                               u32          *const rate_out);

/* - Aggregation --------------------------------------------------- */

/** \page layer2

    \section aggr Link Aggregation

    A link aggregation forms one logical link based on multiple physical ports.
    Each link aggregation is identified by an aggregation number (::vtss_aggr_no_t).
    The aggregation mode of the switch determines how traffic forwarded to link aggregations
    is distributed on the physical ports. The following functions are available:
    - vtss_aggr_port_members_get() is used to get the aggregation port members.
    - vtss_aggr_port_members_set() is used to set the aggregation port members.
    - vtss_aggr_mode_get() is used to get the aggregation mode.
    - vtss_aggr_mode_set() is used to set the aggregation mode.

    By default, no link aggregations exist.
*/

/**
 * \brief Get aggregation port members.
 *
 * \param inst [IN]     Target instance reference.
 * \param aggr_no [IN]  Aggregation number.
 * \param member [OUT]  Aggregation port member list.
 *
 * \return Return code.
 **/
vtss_rc vtss_aggr_port_members_get(const vtss_inst_t     inst,
                                   const vtss_aggr_no_t  aggr_no,
                                   BOOL                  member[VTSS_PORT_ARRAY_SIZE]);


/**
 * \brief Set aggregation port members.
 *
 * \param inst [IN]     Target instance reference.
 * \param aggr_no [IN]  Aggregation number.
 * \param member [IN]   Aggregation port member list.
 *
 * \return Return code.
 **/
vtss_rc vtss_aggr_port_members_set(const vtss_inst_t     inst,
                                   const vtss_aggr_no_t  aggr_no,
                                   const BOOL            member[VTSS_PORT_ARRAY_SIZE]);

/**
 * \brief Get aggregation traffic distribution mode.
 *
 * \param inst [IN]   Target instance reference.
 * \param mode [OUT]  Distribution mode structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_aggr_mode_get(const vtss_inst_t  inst,
                           vtss_aggr_mode_t   *const mode);    


/**
 * \brief Set aggregation traffic distribution mode.
 *
 * \param inst [IN]  Target instance reference.
 * \param mode [IN]  Distribution mode structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_aggr_mode_set(const vtss_inst_t       inst,
                           const vtss_aggr_mode_t  *const mode);    


/* - Mirroring ----------------------------------------------------- */

/** \page layer2

    \section mirror Mirroring

    Mirroring can be used to copy frames to a monitor port for network troubleshooting purposes.
    The following functions are available:
    - vtss_mirror_conf_get() is used to get the mirror configuration.
    - vtss_mirror_conf_set() is used to set the mirror configuration.
    - vtss_mirror_monitor_port_get() is used to get the mirror monitor port.
    - vtss_mirror_monitor_port_set() is used to set the mirror monitor port.
    - vtss_mirror_ingress_ports_get() is used to get the ingress mirroring port members.
    - vtss_mirror_ingress_ports_set() is used to set the ingress mirroring port members.
    - vtss_mirror_egress_ports_get() is used to get the egress mirroring port members.
    - vtss_mirror_egress_ports_set() is used to set the egress mirroring port members.
    - vtss_mirror_cpu_ingress_get() is used to get the CPU ingress mirror mode.
    - vtss_mirror_cpu_ingress_set() is used to set the CPU ingress mirror mode.
    - vtss_mirror_cpu_egress_get() is used to get the CPU egress mirror mode.
    - vtss_mirror_cpu_egress_set() is used to set the CPU egress mirror mode.

    By default, mirroring is disabled for all ports.
*/

#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
/** \brief Mirror port configuration */
typedef enum
{
    VTSS_MIRROR_TAG_NONE,    /**< No mirror tag is added */
    VTSS_MIRROR_TAG_C,       /**< C-tag is added */
    VTSS_MIRROR_TAG_S,       /**< S-tag is added */
    VTSS_MIRROR_TAG_S_CUSTOM /**< Custom S-tag is added */
} vtss_mirror_tag_t;
#endif /* VTSS_ARCH_JAGUAR_2 */

/** \brief Mirror configuration */
typedef struct
{
    vtss_port_no_t    port_no;    /**< Mirror port or VTSS_PORT_NO_NONE */
    BOOL              fwd_enable; /**< Enable normal traffic forwarding to mirror port */
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    vtss_mirror_tag_t tag;        /**< Mirror tag type */
    vtss_vid_t        vid;        /**< Mirror tag VID */
    vtss_tagprio_t    pcp;        /**< Mirror tag PCP */
    vtss_dei_t        dei;        /**< Mirror tag DEI */
#endif /* VTSS_ARCH_JAGUAR_2 */
} vtss_mirror_conf_t;

/**
 * \brief Get the mirror configuration.
 *
 * \param inst [IN]   Target instance reference.
 * \param conf [OUT]  Mirror configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_mirror_conf_get(const vtss_inst_t  inst,
                             vtss_mirror_conf_t *const conf);

/**
 * \brief Set the mirror configuration.
 *
 * \param inst [IN]  Target instance reference.
 * \param conf [IN]  Mirror configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_mirror_conf_set(const vtss_inst_t        inst,
                             const vtss_mirror_conf_t *const conf);

/**
 * \brief Get the mirror monitor port.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [OUT]  Port number.
 *
 * \return Return code.
 **/
vtss_rc vtss_mirror_monitor_port_get(const vtss_inst_t  inst,
                                     vtss_port_no_t     *const port_no);


/**
 * \brief Set the mirror monitor port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number or VTSS_PORT_NO_NONE.
 *
 * \return Return code.
 **/
vtss_rc vtss_mirror_monitor_port_set(const vtss_inst_t     inst,
                                     const vtss_port_no_t  port_no);


/**
 * \brief Get the mirror ingress ports.
 *
 * \param inst [IN]     Target instance reference.
 * \param member [OUT]  Port member list. If a port is enabled in this array, 
 *                      frames received on the port are mirrored.
 *
 * \return Return code.
 **/
vtss_rc vtss_mirror_ingress_ports_get(const vtss_inst_t  inst,
                                      BOOL               member[VTSS_PORT_ARRAY_SIZE]);


/**
 * \brief Set the mirror ingress ports.
 *
 * \param inst [IN]    Target instance reference.
 * \param member [IN]  Port member list. If a port is enabled in this array, 
 *                     frames received on the port are mirrored.
 *
 * \return Return code.
 **/
vtss_rc vtss_mirror_ingress_ports_set(const vtss_inst_t  inst,
                                      const BOOL         member[VTSS_PORT_ARRAY_SIZE]);


/**
 * \brief Get the mirror egress ports.
 *
 * \param inst [IN]     Target instance reference.
 * \param member [OUT]  Port member list. If a port is enabled in this array, 
 *                      frames transmitted on the port are mirrored.
 *
 * \return Return code.
 **/
vtss_rc vtss_mirror_egress_ports_get(const vtss_inst_t  inst,
                                     BOOL               member[VTSS_PORT_ARRAY_SIZE]);


/**
 * \brief Set the mirror egress ports.
 *
 * \param inst [IN]    Target instance reference.
 * \param member [IN]  Port member list. If a port is enabled in this array, 
 *                     frames transmitted on the port are mirrored.
 *
 * \return Return code.
 **/
vtss_rc vtss_mirror_egress_ports_set(const vtss_inst_t  inst,
                                     const BOOL         member[VTSS_PORT_ARRAY_SIZE]);




/**
 * \brief Get the mirror CPU ingress.
 *
 * \param inst [IN]     Target instance reference.
 * \param member [OUT]  CPU member. If this is enabled,
 *                      frames received by the CPU port are mirrored.
 *
 * \return Return code.
 **/
vtss_rc vtss_mirror_cpu_ingress_get(const vtss_inst_t  inst,
                                    BOOL               *member);


/**
 * \brief Set CPU ingress mirroring.
 *
 * Enabling CPU ingress mirroring means that frames transmitted by the CPU
 * are mirrored to the mirror port.
 *
 * \param inst [IN]    Target instance reference.
 * \param member [IN]  CPU member. If this is enabled,
 *                     frames received by the CPU port are mirrored.
 *
 * \return Return code.
 **/
vtss_rc vtss_mirror_cpu_ingress_set(const vtss_inst_t  inst,
                                    const BOOL         member);


/**
 * \brief Get the mirror CPU egress.
 *
 * \param inst [IN]     Target instance reference.
 * \param member [OUT]  CPU member. If this is enabled,
 *                      frames transmitted by the CPU port are mirrored.
 *
 * \return Return code.
 **/
vtss_rc vtss_mirror_cpu_egress_get(const vtss_inst_t  inst,
                                   BOOL               *member);


/**
 * \brief Set the mirror CPU egress
 *
 * Enabling CPU egress mirroring means that frames destined for the CPU
 * are mirrored to the mirror port.
 *
 * \param inst [IN]    Target instance reference.
 * \param member [IN]  CPU member. If this is enabled,
 *                     frames transmitted by the CPU port are mirrored.
 *
 * \return Return code.
 **/
vtss_rc vtss_mirror_cpu_egress_set(const vtss_inst_t  inst,
                                   const BOOL         member);


/* - Flooding control ---------------------------------------------- */

/** \page layer2

    \section flooding Flooding Control

    Forwarding of frames with unknown destination MAC addresses can be controlled per egress port:
    - vtss_uc_flood_members_get() is used to get the unicast flooding port members.
    - vtss_uc_flood_members_set() is used to set the unicast flooding port members.
    - vtss_mc_flood_members_get() is used to get the non-IP multicast flooding port members.
    - vtss_mc_flood_members_set() is used to set the non-IP multicast flooding port members.

    By default, unicast and non-IP multicast flooding is enabled for all ports.
*/

/**
 * \brief Get unicast flood members.
 *
 * \param inst [IN]     Target instance reference.
 * \param member [OUT]  Port member list.
 *
 * \return Return code.
 **/
vtss_rc vtss_uc_flood_members_get(const vtss_inst_t  inst,
                                  BOOL               member[VTSS_PORT_ARRAY_SIZE]);


/**
 * \brief Set unicast flood members.
 *
 * \param inst [IN]    Target instance reference.
 * \param member [IN]  Port member list.
 *
 * \return Return code.
 **/
vtss_rc vtss_uc_flood_members_set(const vtss_inst_t  inst,
                                  const BOOL         member[VTSS_PORT_ARRAY_SIZE]);


/**
 * \brief Get multicast flood members.
 *
 * \param inst [IN]     Target instance reference.
 * \param member [OUT]  Port member list.
 *
 * \return Return code.
 **/
vtss_rc vtss_mc_flood_members_get(const vtss_inst_t  inst,
                                  BOOL               member[VTSS_PORT_ARRAY_SIZE]);


/**
 * \brief Set multicast flood members.
 *
 * \param inst [IN]    Target instance reference.
 * \param member [IN]  Port member list.
 *
 * \return Return code.
 **/
vtss_rc vtss_mc_flood_members_set(const vtss_inst_t  inst,
                                  const BOOL         member[VTSS_PORT_ARRAY_SIZE]);


/* - IGMP ---------------------------------------------------- */

/** \page layer2

    \section ipv4_mc IPv4 Multicast

    Forwarding of IPv4 multicast frames may be restricted based on IGMP snooping:
    - vtss_ipv4_mc_flood_members_get() is used to get IPv4 multicast flooding port members.
    - vtss_ipv4_mc_flood_members_set() is used to set IPv4 multicast flooding port members.
*/

#if defined(VTSS_FEATURE_IPV4_MC_SIP)
/** \page layer2

    - vtss_ipv4_mc_add() is used to add a source specific IPv4 multicast entry.
    - vtss_ipv4_mc_del() is used to delete a source specific IPv4 multicast entry.
*/
#endif /* VTSS_FEATURE_IPV4_MC_SIP */

/** \page layer2

    By default, IPv4 multicast flooding is enabled for all ports.
*/

/**
 * \brief Get IPv4 multicast flood members.
 *
 * \param inst [IN]     Target instance reference.
 * \param member [OUT]  Port member list.
 *                      Ports connected to IPv4 multicast routers should be enabled.
 *
 * \return Return code.
 **/
vtss_rc vtss_ipv4_mc_flood_members_get(const vtss_inst_t  inst,
                                       BOOL               member[VTSS_PORT_ARRAY_SIZE]);


/**
 * \brief Set IPv4 multicast flood members.
 *
 * \param inst [IN]    Target instance reference.
 * \param member [IN]  Port member list.
 *                     Ports connected to IPv4 multicast routers should be enabled.
 *
 * \return Return code.
 **/
vtss_rc vtss_ipv4_mc_flood_members_set(const vtss_inst_t  inst,
                                       const BOOL         member[VTSS_PORT_ARRAY_SIZE]);


#if defined(VTSS_FEATURE_IPV4_MC_SIP)

/**
 * \brief Add IPv4 multicast entry.
 *
 * \param inst [IN]    Target instance reference.
 * \param vid [IN]     VLAN ID.
 * \param sip [IN]     Source IP address.
 * \param dip [IN]     Destination IP address.
 * \param member [IN]  Port member list. 
 *
 * \return Return code.
 **/
vtss_rc vtss_ipv4_mc_add(const vtss_inst_t inst,
                         const vtss_vid_t  vid,
                         const vtss_ip_t   sip,
                         const vtss_ip_t   dip,
                         const BOOL        member[VTSS_PORT_ARRAY_SIZE]);

/**
 * \brief Delete IPv4 multicast entry.
 *
 * \param inst [IN]    Target instance reference.
 * \param vid [IN]     VLAN ID.
 * \param sip [IN]     Source IP address.
 * \param dip [IN]     Destination IP address.
 *
 * \return Return code.
 **/
vtss_rc vtss_ipv4_mc_del(const vtss_inst_t inst,
                         const vtss_vid_t  vid,
                         const vtss_ip_t   sip,
                         const vtss_ip_t   dip);

#endif /* VTSS_FEATURE_IPV4_MC_SIP */

/* - MLD  ----------------------------------------------------- */

/** \page layer2

    \section ipv6_mc IPv6 Multicast

    Forwarding of IPv6 multicast frames may be restricted based on MLD snooping:
    - vtss_ipv6_mc_flood_members_get() is used to get the IPv6 multicast flooding port members.
    - vtss_ipv6_mc_flood_members_set() is used to set the IPv6 multicast flooding port members.
    - vtss_ipv6_mc_ctrl_flood_get() is used to get the IPv6 multicast control flooding mode.
    - vtss_ipv6_mc_ctrl_flood_set() is used to set the IPv6 multicast control flooding mode.
*/

#if defined(VTSS_FEATURE_IPV6_MC_SIP)
/** \page layer2

    - vtss_ipv6_mc_add() is used to add a source specific IPv6 multicast entry.
    - vtss_ipv6_mc_del() is used to delete a source specific IPv6 multicast entry.
*/
#endif /* VTSS_FEATURE_IPV6_MC_SIP */

/** \page layer2

    By default, IPv6 multicast flooding is enabled for all ports.
*/

/**
 * \brief Get IPv6 multicast flood members.
 *
 * \param inst [IN]     Target instance reference.
 * \param member [OUT]  Port member list.
 *                      Ports connected to IPv6 multicast routers should be enabled.
 *
 * \return Return code.
 **/
vtss_rc vtss_ipv6_mc_flood_members_get(const vtss_inst_t  inst,
                                       BOOL               member[VTSS_PORT_ARRAY_SIZE]);


/**
 * \brief Set IPv6 multicast flood members.
 *
 * \param inst [IN]    Target instance reference.
 * \param member [IN]  Port member list.
 *                     Ports connected to IPv6 multicast routers should be enabled.
 *
 * \return Return code.
 **/
vtss_rc vtss_ipv6_mc_flood_members_set(const vtss_inst_t  inst,
                                       const BOOL         member[VTSS_PORT_ARRAY_SIZE]);


/**
 * \brief Get IPv6 multicast control flooding mode.
 *
 * \param inst [IN]    Target instance reference.
 * \param scope [OUT]  IPv6 multicast control flood.
 *                     0: Flood to all ports.
 *                     1: Flood to IPv6 multicast flood members.
 *
 * \return Return code.
 **/
vtss_rc vtss_ipv6_mc_ctrl_flood_get(const vtss_inst_t  inst,
                                    BOOL               *const scope);

/**
 * \brief Set IPv6 multicast control flooding mode.
 * This controls whether unknown Link-Local scope IPv6 multicasts (FF02::/16) are flooded
 * to all ports or to the ports in the IPv6 multicast flood mask.
 *
 * \param inst [IN]   Target instance reference.
 * \param scope [IN]  IPv6 multicast control flood.
 *                    0: Flood to all ports.
 *                    1: Flood to IPv6 multicast flood members.
 *
 * \return Return code.
 **/
vtss_rc vtss_ipv6_mc_ctrl_flood_set(const vtss_inst_t  inst,
                                    const BOOL         scope);

#if defined(VTSS_FEATURE_IPV6_MC_SIP)

/**
 * \brief Add IPv6 multicast entry.
 *
 * \param inst [IN]    Target instance reference.
 * \param vid [IN]     VLAN ID.
 * \param sip [IN]     Source IP address.
 * \param dip [IN]     Destination IP address.
 * \param member [IN]  Port member list. 
 *
 * \return Return code.
 **/
vtss_rc vtss_ipv6_mc_add(const vtss_inst_t inst,
                         const vtss_vid_t  vid,
                         const vtss_ipv6_t sip,
                         const vtss_ipv6_t dip,
                         const BOOL        member[VTSS_PORT_ARRAY_SIZE]);

/**
 * \brief Delete IPv6 multicast entry.
 *
 * \param inst [IN]    Target instance reference.
 * \param vid [IN]     VLAN ID.
 * \param sip [IN]     Source IP address.
 * \param dip [IN]     Destination IP address.
 *
 * \return Return code.
 **/
vtss_rc vtss_ipv6_mc_del(const vtss_inst_t inst,
                         const vtss_vid_t  vid,
                         const vtss_ipv6_t sip,
                         const vtss_ipv6_t dip);

#endif /* VTSS_FEATURE_IPV6_MC_SIP */


/* - Ethernet Protection Switching ---------------------------------- */

/** \page layer2

    \section eps Ethernet Protection Switching

    Linear Ethernet Protection Switching can be controlled using EPS functions.
    Ports may be setup with 1:1 or 1+1 protection.
    - vtss_eps_port_conf_get() is used to get the EPS port configuration.
    - vtss_eps_port_conf_set() is used to set the EPS port configuration.
    - vtss_eps_port_selector_get() is used to get the protection selector state.
    - vtss_eps_port_selector_set() is used to set the protection selector state.

    By default, all ports are unprotected.
*/

/** \brief Port protection type */
typedef enum
{
    VTSS_EPS_PORT_1_PLUS_1,  /**< 1+1 protection */
    VTSS_EPS_PORT_1_FOR_1    /**< 1:1 protection */
} vtss_eps_port_type_t;

/** \brief Port protection configuration */
typedef struct
{
    vtss_eps_port_type_t type;     /**< Protection type */
    vtss_port_no_t       port_no;  /**< Protection port or VTSS_PORT_NO_NONE */
} vtss_eps_port_conf_t;

/**
 * \brief Get EPS port configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Working port.
 * \param conf [OUT]    Protection configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_eps_port_conf_get(const vtss_inst_t     inst,
                               const vtss_port_no_t  port_no, 
                               vtss_eps_port_conf_t  *const conf);


/**
 * \brief Set EPS port configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Working port.
 * \param conf [IN]     Protection configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_eps_port_conf_set(const vtss_inst_t           inst,
                               const vtss_port_no_t        port_no, 
                               const vtss_eps_port_conf_t  *const conf);


/** \brief EPS selector */
typedef enum
{
    VTSS_EPS_SELECTOR_WORKING,    /**< Select working port */
    VTSS_EPS_SELECTOR_PROTECTION  /**< Select protection port */
} vtss_eps_selector_t;

/**
 * \brief Get EPS port selector.
 *
 * \param inst [IN]       Target instance reference.
 * \param port_no [IN]    Working port.
 * \param selector [OUT]  Selector.
 *
 * \return Return code.
 **/
vtss_rc vtss_eps_port_selector_get(const vtss_inst_t     inst,
                                   const vtss_port_no_t  port_no, 
                                   vtss_eps_selector_t   *const selector);

/**
 * \brief Set EPS port selector.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Working port.
 * \param selector [IN]  Selector.
 *
 * \return Return code.
 **/
vtss_rc vtss_eps_port_selector_set(const vtss_inst_t          inst,
                                   const vtss_port_no_t       port_no, 
                                   const vtss_eps_selector_t  selector);

#if defined(VTSS_FEATURE_L2_ERPS)

/* - Ethernet Ring Protection Swiching ----------------------------- */

/** \page layer2

    \section erps Ethernet Ring Protection Switching

    Ethernet Ring Protection Switching can be controlled using ERPS functions.
    Each ring is identified by an ERPS instance number. Each VLAN can be enabled for one or multiple ERPS instances.
    The forwarding mode can be controlled per ERPS instance and port.
    - vtss_erps_vlan_member_get() is used to get the ERPS member mode for a VLAN.
    - vtss_erps_vlan_member_set() is used to set the ERPS member mode for a VLAN.
    - vtss_erps_port_state_get() is used to get the forwarding state for an ERPS instance and port.
    - vtss_erps_port_state_set() is used to set the forwarding state for an ERPS instance and port.

    By default, all VLANs are disabled for all rings and all ports are discarding for all rings.
*/

/** \brief ERPS instance number */
typedef u32 vtss_erpi_t;

#define VTSS_ERPIS           (64)                         /**< Number of ERPS instances */
#define VTSS_ERPI_START      (0)                          /**< ERPI start number */
#define VTSS_ERPI_END        (VTSS_ERPI_START+VTSS_ERPIS) /**< ERPI end number */
#define VTSS_ERPI_ARRAY_SIZE VTSS_ERPI_END                /**< ERPI array size */

/**
 * \brief Get ERPS member state for a VLAN.
 *
 * \param inst [IN]     Target instance reference.
 * \param erpi [IN]     ERPS instance.
 * \param vid [IN]      VLAN ID.
 * \param member [OUT]  Membership, TRUE if VLAN is included in ERPS instance.
 *
 * \return Return code.
 **/
vtss_rc vtss_erps_vlan_member_get(const vtss_inst_t inst,
                                  const vtss_erpi_t erpi,
                                  const vtss_vid_t  vid, 
                                  BOOL              *const member);


/**
 * \brief Set ERPS member state for a VLAN.
 *
 * \param inst [IN]    Target instance reference.
 * \param erpi [IN]    ERPS instance.
 * \param vid [IN]     VLAN ID.
 * \param member [IN]  Membership, TRUE if VLAN is included in ERPS instance.
 *
 * \return Return code.
 **/
vtss_rc vtss_erps_vlan_member_set(const vtss_inst_t inst,
                                  const vtss_erpi_t erpi,
                                  const vtss_vid_t  vid, 
                                  const BOOL        member);


/** \brief ERPS state */
typedef enum {
    VTSS_ERPS_STATE_FORWARDING, /**< Forwarding */
    VTSS_ERPS_STATE_DISCARDING, /**< Discarding */
} vtss_erps_state_t;

/**
 * \brief Get ERPS state for ERPS instance and port.
 *
 * \param inst [IN]     Target instance reference.
 * \param erpi [IN]     ERPS instance.
 * \param port_no [IN]  Port number.
 * \param state [OUT]   ERPS state.
 *
 * \return Return code.
 **/
vtss_rc vtss_erps_port_state_get(const vtss_inst_t    inst,
                                 const vtss_erpi_t    erpi, 
                                 const vtss_port_no_t port_no, 
                                 vtss_erps_state_t    *const state);


/**
 * \brief Set ERPS state for ERPS instance and port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param erpi [IN]     ERPS instance.
 * \param state [IN]    ERPS state.
 *
 * \return Return code.
 **/
vtss_rc vtss_erps_port_state_set(const vtss_inst_t       inst,
                                 const vtss_erpi_t       erpi, 
                                 const vtss_port_no_t    port_no, 
                                 const vtss_erps_state_t state);

#endif // VTSS_FEATURE_L2_ERPS

#endif /* VTSS_FEATURE_LAYER2 */

#if defined(VTSS_FEATURE_RCL)

/* - Real-time Control List ---------------------------------------- */

// RCL VID configuration
typedef struct {
    BOOL pcp[VTSS_PCPS]; // PCP values
} vtss_rcl_vid_conf_t;

// Add/enable RCL VID classification
vtss_rc vtss_rcl_vid_add(const vtss_inst_t         inst,
                         const vtss_vid_t          vid,
                         const vtss_rcl_vid_conf_t *const conf);

// Delete/disable RCL VID classification
vtss_rc vtss_rcl_vid_del(const vtss_inst_t inst,
                         const vtss_vid_t  vid);

// RCL Ethernet Type
typedef enum {
    VTSS_RCL_ETYPE_ANY,      // Any Ethernet Type
    VTSS_RCL_ETYPE_PROFINET, // Ethernet Type 0x8892
    VTSS_RCL_ETYPE_OPC_UA,   // Ethernet Type 0xB62C
} vtss_rcl_etype_t;

// RCE key
typedef struct
{
    vtss_port_no_t   port_no;         // Ingress port
    vtss_vid_t       vid;             // VID or zero for untagged/priority-tagged
    vtss_vcap_bit_t  tagged;          // Outer tag
    BOOL             smac;            // SMAC/DMAC lookup selection
    vtss_vcap_u48_t  mac;             // SMAC/DMAC value
    vtss_rcl_etype_t etype;           // Ethernet type
    vtss_vcap_u16_t  frame_id;        // FrameId
    vtss_vcap_u16_t  publisher_id;    // PublisherId
    vtss_vcap_u16_t  writer_group_id; // WriterGroupId
} vtss_rce_key_t;

// RCE action
typedef struct
{
    u16            rtp_id;                // RTP identifier
    BOOL           rtp_sub_id;            // RTP sub-identifier
    BOOL           rtp_inbound;           // RTP inbound processing
    BOOL           port_enable;           // Enable port forwarding to egress port list
    BOOL           port_list[VTSS_PORTS]; // Egress port list
    BOOL           llct_enable;           // Enable Low-Latency Cut-Through
    vtss_port_no_t llct_port_no;          // LLCT egress port
} vtss_rce_action_t;

// RCE ID
typedef u32 vtss_rce_id_t;

#define VTSS_RCE_ID_LAST 0 // Special value used to add last in list

// Real-time Control Entry
typedef struct
{
    vtss_rce_id_t     id;     // RCE ID
    vtss_rce_key_t    key;    // RCE Key
    vtss_rce_action_t action; // RCE Action
} vtss_rce_t;

// Initialize RCE to default values
vtss_rc vtss_rce_init(const vtss_inst_t inst,
                      vtss_rce_t        *const rce);

// Add/modify RCE
vtss_rc vtss_rce_add(const vtss_inst_t   inst,
                     const vtss_rce_id_t rce_id,
                     const vtss_rce_t    *const rce);

// Delete RCE
vtss_rc vtss_rce_del(const vtss_inst_t   inst,
                     const vtss_rce_id_t rce_id);

#endif /* VTSS_FEATURE_RCL */

#ifdef __cplusplus
}
#endif
#endif /* _VTSS_L2_API_H_ */
