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

#ifndef _MSCC_ETHERNET_SWITCH_API_L2_
#define _MSCC_ETHERNET_SWITCH_API_L2_

#include <mscc/ethernet/switch/api/types.h>
#include <mscc/ethernet/switch/api/qos.h>
#include <mscc/ethernet/switch/api/vop.h>
#include <mscc/ethernet/switch/api/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

/* - MAC address table --------------------------------------------- */

/** \brief VStaX Unit Port Set ID (UPSID; 0-31). */
typedef int mesa_vstax_upsid_t;

#define MESA_VSTAX_UPSIDS             (32)                                         /**< Number of UPSIDs    */
#define MESA_VSTAX_UPSID_START        ( 0)                                         /**< First UPSID value   */
#define MESA_VSTAX_UPSID_MIN          MESA_VSTAX_UPSID_START                       /**< Minimum UPSID value */
#define MESA_VSTAX_UPSID_MAX          (MESA_VSTAX_UPSID_MIN+MESA_VSTAX_UPSIDS - 1) /**< Maximum UPSID value */
#define MESA_VSTAX_UPSID_LEGAL(upsid) (MESA_VSTAX_UPSID_MIN <= (upsid) && (upsid) <= MESA_VSTAX_UPSID_MAX) /**< Checks if UPSIDs is legal */
#define MESA_VSTAX_UPSID_UNDEF (-1)                                                /**< Undefined UPSID. Only applicable in selected contexts */

/** \brief Unit Port Set Port Number */
typedef uint32_t mesa_vstax_upspn_t;

#define MESA_UPSPN_CPU  0xfffffffe /**< MAC address entry is from CPU */
#define MESA_UPSPN_NONE 0xffffffff /**< Used to indicate end of GLAG list */

/** \brief MAC address entry */
typedef struct
{
    mesa_vid_mac_t   vid_mac;          /**< VLAN ID and MAC addr */
    mesa_port_list_t destination;      /**< Dest. ports */
    mesa_bool_t      copy_to_cpu;      /**< CPU copy flag for DMAC lookup */
    mesa_bool_t      copy_to_cpu_smac; /**< CPU copy flag for SMAC lookup */
    mesa_bool_t      locked;           /**< Locked/static flag */
    mesa_bool_t      aged;             /**< Age flag */
    mesa_packet_rx_queue_t cpu_queue;  /**< CPU queue */
} mesa_mac_table_entry_t;

/**
 * \brief Add MAC address entry.
 *
 * \param inst [IN]   Target instance reference.
 * \param entry [IN]  MAC address entry structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_mac_table_add(const mesa_inst_t             inst,
                           const mesa_mac_table_entry_t  *const entry);


/**
 * \brief Delete MAC address entry.
 *
 * \param inst [IN]    Target instance reference.
 * \param vid_mac [IN]  VLAN ID and MAC address structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_mac_table_del(const mesa_inst_t     inst,
                           const mesa_vid_mac_t  *const vid_mac);


/**
 * \brief Get MAC address entry.
 *
 * \param inst [IN]     Target instance reference.
 * \param vid_mac [IN]  VLAN ID and MAC address.
 * \param entry [OUT]   MAC address entry.
 *
 * \return Return code.
 **/
mesa_rc mesa_mac_table_get(const mesa_inst_t       inst,
                           const mesa_vid_mac_t    *const vid_mac,
                           mesa_mac_table_entry_t  *const entry);


/**
 * \brief Lookup next MAC address entry.
 *
 * \param inst [IN]     Target instance reference.
 * \param vid_mac [IN]  VLAN ID and MAC address.
 * \param entry [OUT]   MAC address entry.
 *
 * \return Return code.
 **/
mesa_rc mesa_mac_table_get_next(const mesa_inst_t       inst,
                                const mesa_vid_mac_t    *const vid_mac,
                                mesa_mac_table_entry_t  *const entry);


/** \brief MAC address table age time */
typedef uint32_t mesa_mac_table_age_time_t;

/**
 * \brief Get MAC address table age time.
 *
 * \param inst [IN]       Target instance reference.
 * \param age_time [OUT]  MAC age time in seconds. Value zero disables aging.
 *
 * \return Return code.
 **/
mesa_rc mesa_mac_table_age_time_get(const mesa_inst_t          inst,
                                    mesa_mac_table_age_time_t  *const age_time);


/**
 * \brief Set MAC address table age time.
 *
 * \param inst [IN]      Target instance reference.
 * \param age_time [IN]  MAC age time in seconds. Value zero disables aging.
 *
 * \return Return code.
 **/
mesa_rc mesa_mac_table_age_time_set(const mesa_inst_t                inst,
                                    const mesa_mac_table_age_time_t  age_time);

/**
 * \brief Do age scan of the MAC address table.
 * This should be done periodically with interval T/2, where T is the age timer.
 *
 * \param inst [IN]  Target instance reference.
 *
 * \return Return code.
 **/
mesa_rc mesa_mac_table_age(const mesa_inst_t  inst);


/**
 * \brief Do VLAN specific age scan of the MAC address table.
 *
 * \param inst [IN]  Target instance reference.
 * \param vid [IN]   VLAN ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_mac_table_vlan_age(const mesa_inst_t  inst,
                                const mesa_vid_t   vid);


/**
 * \brief Flush MAC address table, i.e. remove all unlocked entries.
 *
 * \param inst [IN]  Target instance reference.
 *
 * \return Return code.
 **/
mesa_rc mesa_mac_table_flush(const mesa_inst_t inst);


/**
 * \brief Delete MAC address entries learned on port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 *
 * \return Return code.
 **/
mesa_rc mesa_mac_table_port_flush(const mesa_inst_t     inst,
                                  const mesa_port_no_t  port_no);


/**
 * \brief Delete MAC address entries learned on VLAN ID.
 *
 * \param inst [IN]  Target instance reference.
 * \param vid [IN]   VLAN ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_mac_table_vlan_flush(const mesa_inst_t  inst,
                                  const mesa_vid_t   vid);


/**
 * \brief Delete MAC address entries learned on port and VLAN ID.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param vid [IN]      VLAN ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_mac_table_vlan_port_flush(const mesa_inst_t     inst,
                                       const mesa_port_no_t  port_no,
                                       const mesa_vid_t      vid);

/** \brief MAC address table status */
typedef struct
{
    mesa_event_t learned;     /**< One or more entries were learned */
    mesa_event_t replaced;    /**< One or more entries were replaced */
    mesa_event_t moved;       /**< One or more entries moved to another port */
    mesa_event_t aged;        /**< One or more entries were aged */
} mesa_mac_table_status_t;

/**
 * \brief Get MAC address table status.
 *
 * \param inst [IN]     Target instance reference.
 * \param status [OUT]  MAC address table status.
 *
 * \return Return code.
 **/
mesa_rc mesa_mac_table_status_get(const mesa_inst_t        inst,
                                  mesa_mac_table_status_t  *const status);


/** \brief Learning mode */
typedef struct
{
    mesa_bool_t automatic;  /**< Automatic learning done by switch chip (default enabled) */
    mesa_bool_t cpu;        /**< Learn frames copied to CPU (default disabled) */
    mesa_bool_t discard;    /**< Learn frames discarded (default disabled) */
} mesa_learn_mode_t;

/**
 * \brief Get the learn mode for a port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param mode [OUT]    Learn mode.
 *
 * \return Return code.
 **/
mesa_rc mesa_learn_port_mode_get(const mesa_inst_t     inst,
                                 const mesa_port_no_t  port_no,
                                 mesa_learn_mode_t     *const mode);
/**
 * \brief Set the learn mode for a port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param mode [IN]     Learn mode.
 *
 * \return Return code.
 **/
mesa_rc mesa_learn_port_mode_set(const mesa_inst_t        inst,
                                 const mesa_port_no_t     port_no,
                                 const mesa_learn_mode_t  *const mode);


/* - Operational state --------------------------------------------- */

// Get port operational state.
//
// IN:  port_no  Port number.
// OUT: state    Port state, TRUE if link is up.
mesa_rc mesa_port_state_get(const mesa_inst_t     inst,
                            const mesa_port_no_t  port_no,
                            mesa_bool_t           *const state);


/**
 * \brief Set port operational state.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param state [IN]    Port state, TRUE if link is up.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_state_set(const mesa_inst_t     inst,
                            const mesa_port_no_t  port_no,
                            mesa_bool_t           state);



/* - Spanning Tree ------------------------------------------------- */

/** \brief Spanning Tree state */
typedef enum
{
    MESA_STP_STATE_DISCARDING,  /**< STP state discarding (admin/operational down) */
    MESA_STP_STATE_LEARNING,    /**< STP state learning */
    MESA_STP_STATE_FORWARDING   /**< STP state forwarding */
} mesa_stp_state_t;

/**
 * \brief Get Spanning Tree state for a port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param state [OUT]   STP state.
 *
 * \return Return code.
 **/
mesa_rc mesa_stp_port_state_get(const mesa_inst_t     inst,
                                const mesa_port_no_t  port_no,
                                mesa_stp_state_t      *const state);



/**
 * \brief Set Spanning Tree state for a port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param state [IN]    STP state.
 *
 * \return Return code.
 **/
mesa_rc mesa_stp_port_state_set(const mesa_inst_t       inst,
                                const mesa_port_no_t    port_no,
                                const mesa_stp_state_t  state);



/** \brief MSTP instance number */
typedef uint32_t mesa_msti_t;

#define MESA_MSTIS           (65)                         /**<  Number of MSTP instances */
#define MESA_MSTI_START      (0)                          /**< MSTI start number */
#define MESA_MSTI_END        (MESA_MSTI_START+MESA_MSTIS) /**< MSTI end number */
#define MESA_MSTI_ARRAY_SIZE MESA_MSTI_END                /**< MSTI array size */


/**
 * \brief Get MSTP instance mapping for a VLAN.
 *
 * \param inst [IN]   Target instance reference.
 * \param vid [IN]    VLAN ID.
 * \param msti [OUT]  MSTP instance.
 *
 * \return Return code.
 **/
mesa_rc mesa_mstp_vlan_msti_get(const mesa_inst_t  inst,
                                const mesa_vid_t   vid,
                                mesa_msti_t        *const msti);


/**
 * \brief Set MSTP instance mapping for a VLAN.
 *
 * \param inst [IN]  Target instance reference.
 * \param vid [IN]   VLAN ID.
 * \param msti [IN]  MSTP instance.
 *
 * \return Return code.
 **/
mesa_rc mesa_mstp_vlan_msti_set(const mesa_inst_t  inst,
                                const mesa_vid_t   vid,
                                const mesa_msti_t  msti);


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
mesa_rc mesa_mstp_port_msti_state_get(const mesa_inst_t     inst,
                                      const mesa_port_no_t  port_no,
                                      const mesa_msti_t     msti,
                                      mesa_stp_state_t      *const state);


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
mesa_rc mesa_mstp_port_msti_state_set(const mesa_inst_t       inst,
                                      const mesa_port_no_t    port_no,
                                      const mesa_msti_t       msti,
                                      const mesa_stp_state_t  state);


/* - VLAN ---------------------------------------------------------- */

/** \brief VLAN configuration */
typedef struct {
    mesa_etype_t s_etype; /**< Alternative S-tag Ethernet Type */
} mesa_vlan_conf_t;

/**
 * \brief Get VLAN configuration.
 *
 * \param inst [IN]   Target instance reference.
 * \param conf [OUT]  VLAN configuration structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_vlan_conf_get(const mesa_inst_t inst,
                           mesa_vlan_conf_t  *const conf);

/**
 * \brief Set VLAN configuration.
 *
 * \param inst [IN]  Target instance reference.
 * \param conf [IN]  VLAN configuration structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_vlan_conf_set(const mesa_inst_t      inst,
                           const mesa_vlan_conf_t *const conf);

/** \brief VLAN port type configuration */
typedef enum
{
    MESA_VLAN_PORT_TYPE_UNAWARE, /**< VLAN unaware port */
    MESA_VLAN_PORT_TYPE_C,       /**< C-port */
    MESA_VLAN_PORT_TYPE_S,       /**< S-port */
    MESA_VLAN_PORT_TYPE_S_CUSTOM /**< S-port using alternative Ethernet Type */
} mesa_vlan_port_type_t;

/** \brief VLAN port configuration */
typedef struct
{
    mesa_vlan_port_type_t port_type;      /**< Port type (ingress and egress) */
    mesa_vid_t            pvid;           /**< Port VLAN ID (PVID, ingress) */
    mesa_vid_t            untagged_vid;   /**< Port untagged VLAN ID (UVID, egress) */
    mesa_vlan_frame_t     frame_type;     /**< Acceptable frame type (ingress) */
    mesa_bool_t           ingress_filter; /**< Ingress filtering */
} mesa_vlan_port_conf_t;

/**
 * \brief Get VLAN mode for port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    VLAN port configuration structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_vlan_port_conf_get(const mesa_inst_t      inst,
                                const mesa_port_no_t   port_no,
                                mesa_vlan_port_conf_t  *const conf);



/**
 * \brief Set VLAN mode for port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     VLAN port configuration structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_vlan_port_conf_set(const mesa_inst_t            inst,
                                const mesa_port_no_t         port_no,
                                const mesa_vlan_port_conf_t  *const conf);


/**
 * \brief Get VLAN membership.
 *
 * \param inst [IN]     Target instance reference.
 * \param vid [IN]      VLAN ID.
 * \param member [OUT]  VLAN port member list.
 *
 * \return Return code.
 **/
mesa_rc mesa_vlan_port_members_get(const mesa_inst_t inst,
                                   const mesa_vid_t  vid,
                                   mesa_port_list_t  *port_list);



/**
 * \brief Set VLAN membership.
 *
 * \param inst [IN]    Target instance reference.
 * \param vid [IN]     VLAN ID.
 * \param member [IN]  VLAN port member list.
 *
 * \return Return code.
 **/
mesa_rc mesa_vlan_port_members_set(const mesa_inst_t      inst,
                                   const mesa_vid_t       vid,
                                   const mesa_port_list_t *port_list);

/** \brief VLAN ID configuration */
typedef struct
{
    mesa_bool_t learning;        /**< Enable/disable learning */
    mesa_bool_t mirror;          /**< Enable/disable mirroring */
    mesa_vid_t  fid CAP(L2_SVL); /**< Forwarding ID for SVL/IVL control */
} mesa_vlan_vid_conf_t;

/**
 * \brief Get VLAN ID configuration
 *
 * \param inst [IN]   Target instance reference.
 * \param vid [IN]    VLAN ID.
 * \param conf [OUT]  VLAN configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_vlan_vid_conf_get(const mesa_inst_t    inst,
                               const mesa_vid_t     vid,
                               mesa_vlan_vid_conf_t *const conf);

/**
 * \brief Set VLAN ID configuration
 *
 * \param inst [IN]  Target instance reference.
 * \param vid [IN]   VLAN ID.
 * \param conf [IN]  VLAN configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_vlan_vid_conf_set(const mesa_inst_t          inst,
                               const mesa_vid_t           vid,
                               const mesa_vlan_vid_conf_t *const conf);

/** \brief VLAN Tx tag type */
typedef enum
{
    MESA_VLAN_TX_TAG_PORT,    /**< Egress tagging determined by VLAN port configuration */
    MESA_VLAN_TX_TAG_DISABLE, /**< Egress tagging disabled */
    MESA_VLAN_TX_TAG_ENABLE,  /**< Egress tagging enabled */
} mesa_vlan_tx_tag_t;

/**
 * \brief Get VLAN Tx tagging configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param vid [IN]      VLAN ID.
 * \param tx_tag [OUT]  Tx tagging list.
 *
 * \return Return code.
 **/
mesa_rc mesa_vlan_tx_tag_get(const mesa_inst_t  inst,
                             const mesa_vid_t   vid,
                             const uint32_t     cnt,
                             mesa_vlan_tx_tag_t *const tx_tag);

/**
 * \brief Get VLAN Tx tagging configuration.
 *
 * \param inst [IN]    Target instance reference.
 * \param vid [IN]     VLAN ID.
 * \param tx_tag [IN]  Tx tagging list.
 *
 * \return Return code.
 **/
mesa_rc mesa_vlan_tx_tag_set(const mesa_inst_t        inst,
                             const mesa_vid_t         vid,
                             const uint32_t           cnt,
                             const mesa_vlan_tx_tag_t *const tx_tag);

/** \brief Container for VLAN counters */
typedef struct {
    uint64_t frames; /**< Number of frames */
    uint64_t bytes;  /**< Number of bytes */
} mesa_vlan_counter_types_t CAP(L2_VLAN_COUNTERS);

/** \brief VLAN counters */
typedef struct {
    mesa_vlan_counter_types_t rx_vlan_unicast;   /**< Number of received unicast frames or bytes */
    mesa_vlan_counter_types_t rx_vlan_multicast; /**< Number of received multicast frames or bytes */
    mesa_vlan_counter_types_t rx_vlan_broadcast; /**< Number of received broadcast frames or bytes */
} mesa_vlan_counters_t CAP(L2_VLAN_COUNTERS);

/**
 * \brief Get VLAN Counters.
 *
 * \param inst [IN]      Target instance reference.
 * \param vid [IN]       VLAN ID.
 * \param counters [OUT] VLAN counters.
 *
 * \return Return code.
 **/

mesa_rc mesa_vlan_counters_get(const mesa_inst_t    inst,
                               const mesa_vid_t     vid,
                               mesa_vlan_counters_t *const counters)
    CAP(L2_VLAN_COUNTERS);

/**
 * \brief Clear VLAN Counters.
 *
 * \param inst [IN]      Target instance reference.
 * \param vid [IN]       VLAN ID.
 *
 * \return Return code.
 **/

mesa_rc mesa_vlan_counters_clear(const mesa_inst_t    inst,
                                 const mesa_vid_t     vid)
    CAP(L2_VLAN_COUNTERS);

/* - VCL ----------------------------------------------------------- */

/** \brief VCL port configuration */
typedef struct {
    mesa_bool_t          dmac_dip; /**< Enable DMAC/DIP matching (default SMAC/SIP) */
    mesa_vcap_key_type_t key_type; /**< Key type for VCL lookup */
} mesa_vcl_port_conf_t;

/**
 * \brief Get VCL port configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    VCL port configuration structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_vcl_port_conf_get(const mesa_inst_t    inst,
                               const mesa_port_no_t port_no,
                               mesa_vcl_port_conf_t *const conf);

/**
 * \brief Get VCL port configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     VCL port configuration structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_vcl_port_conf_set(const mesa_inst_t          inst,
                               const mesa_port_no_t       port_no,
                               const mesa_vcl_port_conf_t *const conf);

/** \brief VCE frame type */
typedef enum
{
    MESA_VCE_TYPE_ANY,     /**< Any frame type */
    MESA_VCE_TYPE_ETYPE,   /**< Ethernet Type */
    MESA_VCE_TYPE_LLC,     /**< LLC */
    MESA_VCE_TYPE_SNAP,    /**< SNAP */
    MESA_VCE_TYPE_IPV4,    /**< IPv4 */
    MESA_VCE_TYPE_IPV6     /**< IPv6 */
} mesa_vce_type_t;

/** \brief VCE ID type */
typedef uint32_t mesa_vce_id_t;

#define MESA_VCL_IDS        256                              /**< Number of VCLs */
#define MESA_VCL_ID_START   0                                /**< VCL ID start number */
#define MESA_VCL_ID_END     (MESA_VCL_ID_START+MESA_VCL_IDS) /**< VCL ID end number */
#define MESA_VCL_ARRAY_SIZE MESA_VCL_ID_END                  /**< VCL ID array size */

#define MESA_VCE_ID_LAST 0 /**< Special value used to add last in list */

/** \brief VCE MAC header information */
typedef struct
{
    mesa_vcap_bit_t dmac_mc; /**< Multicast DMAC */
    mesa_vcap_bit_t dmac_bc; /**< Broadcast DMAC */
    mesa_vcap_u48_t smac;    /**< SMAC */
} mesa_vce_mac_t;

/** \brief VCE tag information */
typedef struct
{
    mesa_vcap_vid_t vid;    /**< VLAN ID (12 bit) */
    mesa_vcap_u8_t  pcp;    /**< PCP (3 bit) */
    mesa_vcap_bit_t dei;    /**< DEI */
    mesa_vcap_bit_t tagged; /**< Tagged/untagged frame */
    mesa_vcap_bit_t s_tag;  /**< S-tag type */
} mesa_vce_tag_t;

/** \brief Frame data for MESA_VCE_TYPE_ETYPE */
typedef struct
{
    mesa_vcap_u16_t etype; /**< Ethernet Type value */
    mesa_vcap_u32_t data;  /**< MAC data */
    mesa_vcap_u8_t  mel;   /**< MEG level (7 bit) */
} mesa_vce_frame_etype_t;

/** \brief Frame data for MESA_VCE_TYPE_LLC */
typedef struct
{
    mesa_vcap_u48_t data; /**< Data */
} mesa_vce_frame_llc_t;

/** \brief Frame data for MESA_VCE_TYPE_SNAP */
typedef struct
{
    mesa_vcap_u48_t data; /**< Data */
} mesa_vce_frame_snap_t;

/** \brief Frame data for MESA_VCE_TYPE_IPV4 */
typedef struct
{
    mesa_vcap_bit_t fragment; /**< Fragment */
    mesa_vcap_bit_t options;  /**< Header options */
    mesa_vcap_vr_t  dscp;     /**< DSCP field (6 bit) */
    mesa_vcap_u8_t  proto;    /**< Protocol */
    mesa_vcap_ip_t  sip;      /**< Source IP address */
    mesa_vcap_vr_t  dport;    /**< UDP/TCP: Destination port */
} mesa_vce_frame_ipv4_t;

/** \brief Frame data for MESA_VCE_TYPE_IPV6 */
typedef struct
{
    mesa_vcap_vr_t  dscp;  /**< DSCP field (6 bit) */
    mesa_vcap_u8_t  proto; /**< Protocol */
    mesa_vcap_u32_t sip;   /**< Source IP address (32 LSB) */
    mesa_vcap_vr_t  dport; /**< UDP/TCP: Destination port */
} mesa_vce_frame_ipv6_t;

/** \brief VCE Key*/
typedef struct
{
    mesa_port_list_t port_list; /**< Port list */
    mesa_vce_mac_t   mac;       /**< MAC header */
    mesa_vce_tag_t   tag;       /**< Outer tag */
    mesa_vce_tag_t   inner_tag; /**< Inner tag */
    mesa_vce_type_t  type;      /**< VCE frame type */

    union
    {
        /* MESA_VCE_TYPE_ANY: No specific fields */
        mesa_vce_frame_etype_t etype; /**< MESA_VCE_TYPE_ETYPE */
        mesa_vce_frame_llc_t   llc;   /**< MESA_VCE_TYPE_LLC */
        mesa_vce_frame_snap_t  snap;  /**< MESA_VCE_TYPE_SNAP */
        mesa_vce_frame_ipv4_t  ipv4;  /**< MESA_VCE_TYPE_IPV4 */
        mesa_vce_frame_ipv6_t  ipv6;  /**< MESA_VCE_TYPE_IPV6 */
    } frame;  /**< Frame type specific data */
} mesa_vce_key_t;

/** \brief Ingress map selection */
typedef enum {
    MESA_IMAP_SEL_DISABLE, /**< Ingress map not used */
    MESA_IMAP_SEL_OUTER,   /**< Ingress map used for outer tag */
    MESA_IMAP_SEL_INNER,   /**< Ingress map used for inner tag */
} mesa_imap_sel_t;

/** \brief OAM detection signalled to VOE */
typedef enum {
    MESA_OAM_DETECT_NONE,                     /**< No OAM detection */
    MESA_OAM_DETECT_UNTAGGED,                 /**< Untagged OAM detection */
    MESA_OAM_DETECT_SINGLE_TAGGED,            /**< Single tagged OAM detection */
    MESA_OAM_DETECT_DOUBLE_TAGGED,            /**< Double tagged OAM detection */
    MESA_OAM_DETECT_TRIPLE_TAGGED CAP(OAM_V2) /**< Triple tagged OAM detection */
} mesa_oam_detect_t CAP(OAM);

/** \brief VCE Action */
typedef struct
{
    mesa_vid_t                vid;        /**< Classified VLAN ID */
    mesa_acl_policy_no_t      policy_no;  /**< ACL policy number */
    mesa_bool_t               pop_enable; /**< Tag pop enable */
    uint8_t                   pop_cnt;    /**< Tag pop count */
    mesa_imap_sel_t           map_sel;    /**< Ingress map selection */
    mesa_qos_ingress_map_id_t map_id;     /**< Ingress map to use for classification */
    mesa_iflow_id_t           flow_id;    /**< Ingress flow ID */
    mesa_oam_detect_t         oam_detect; /**< OAM detection */
} mesa_vce_action_t;

/** \brief VLAN Control Entry */
typedef struct
{
    mesa_vce_id_t     id;     /**< VCE ID */
    mesa_vce_key_t    key;    /**< VCE Key */
    mesa_vce_action_t action; /**< VCE Action */
} mesa_vce_t;

/**
 * \brief Initialize VCE to default values.
 *
 * \param inst [IN]  Target instance reference.
 * \param type [IN]  VCE type.
 * \param vce [OUT]  VCE structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_vce_init(const mesa_inst_t      inst,
                      const mesa_vce_type_t  type,
                      mesa_vce_t             *const vce);


/**
 * \brief Add/modify VCE.
 *
 * \param inst [IN]    Target instance reference.
 * \param vce_id [IN]  VCE ID. The VCE will be added before the entry with this ID.
 *                     MESA_VCE_ID_LAST is reserved for inserting last.
 * \param vce [IN]     VCE structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_vce_add(const mesa_inst_t    inst,
                     const mesa_vce_id_t  vce_id,
                     const mesa_vce_t     *const vce);



/**
 * \brief Delete VCE.
 *
 * \param inst [IN]    Target instance reference.
 * \param vce_id [IN]  VCE ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_vce_del(const mesa_inst_t    inst,
                     const mesa_vce_id_t  vce_id);

/* - Ingress counters ---------------------------------------------- */

/** \brief Class/COSID count */
typedef uint8_t mesa_class_cnt_t;

/** \brief Ingress counter ID */
typedef uint16_t mesa_ingress_cnt_id_t;

/**
 * \brief Allocate ingress counters.
 *
 * \param inst [IN]  Target instance reference.
 * \param cnt [IN]   Number of classes/COSIDs
 * \param id [OUT]   Ingress counter ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_ingress_cnt_alloc(const mesa_inst_t      inst,
                               const mesa_class_cnt_t cnt,
                               mesa_ingress_cnt_id_t  *const id);

/**
 * \brief Free ingress counters.
 *
 * \param inst [IN]  Target instance reference.
 * \param id [IN]    Ingress counter ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_ingress_cnt_free(const mesa_inst_t           inst,
                              const mesa_ingress_cnt_id_t id);

/** \brief Ingress counters */
typedef struct {
    mesa_counter_pair_t rx_green;   /**< Rx green frames/bytes */
    mesa_counter_pair_t rx_yellow;  /**< Rx yellow frames/bytes */
    mesa_counter_pair_t rx_red;     /**< Rx red frames/bytes */
    mesa_counter_pair_t rx_discard; /**< Rx discarded frames/bytes */
    mesa_counter_pair_t tx_discard; /**< Tx discarded frames/bytes */
} mesa_ingress_counters_t;

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
mesa_rc mesa_ingress_cnt_get(const mesa_inst_t           inst,
                             const mesa_ingress_cnt_id_t id,
                             const mesa_cosid_t          cosid,
                             mesa_ingress_counters_t     *counters);

/**
 * \brief Clear ingress counters.
 *
 * \param inst [IN]   Target instance reference.
 * \param id [IN]     Ingress counter ID.
 * \param cosid [IN]  COSID.
 *
 * \return Return code.
 **/
mesa_rc mesa_ingress_cnt_clear(const mesa_inst_t           inst,
                               const mesa_ingress_cnt_id_t id,
                               const mesa_cosid_t          cosid);

/* - Dual Leaky Bucket policers ------------------------------------ */

/** \brief DLB policer ID */
typedef uint16_t mesa_dlb_policer_id_t;

/**
 * \brief Allocate DLB policers.
 *
 * \param inst [IN]  Target instance reference.
 * \param cnt [IN]   Number of classes/COSIDs
 * \param id [OUT]   DLB policer ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_dlb_policer_alloc(const mesa_inst_t      inst,
                               const mesa_class_cnt_t cnt,
                               mesa_dlb_policer_id_t  *const id);

/**
 * \brief Free DLB policers.
 *
 * \param inst [IN]  Target instance reference.
 * \param id [IN]    DLB policer ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_dlb_policer_free(const mesa_inst_t           inst,
                              const mesa_dlb_policer_id_t id);

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
mesa_rc mesa_dlb_policer_conf_get(const mesa_inst_t           inst,
                                  const mesa_dlb_policer_id_t id,
                                  const mesa_cosid_t          cosid,
                                  mesa_dlb_policer_conf_t     *const conf);

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
mesa_rc mesa_dlb_policer_conf_set(const mesa_inst_t             inst,
                                  const mesa_dlb_policer_id_t   id,
                                  const mesa_cosid_t            cosid,
                                  const mesa_dlb_policer_conf_t *const conf);

/* - Ingress flow -------------------------------------------------- */

/**
 * \brief Allocate ingress flow.
 *
 * \param inst [IN]  Target instance reference.
 * \param id [OUT]   Ingress flow ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_iflow_alloc(const mesa_inst_t inst,
                         mesa_iflow_id_t   *const id);

/**
 * \brief Free ingress flow.
 *
 * \param inst [IN]  Target instance reference.
 * \param id [IN]    Ingress flow ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_iflow_free(const mesa_inst_t     inst,
                        const mesa_iflow_id_t id);

/** \brief Ingress flow configuration */
typedef struct
{
    mesa_bool_t           cnt_enable;          /**< Enable ingress counter mapping */
    mesa_ingress_cnt_id_t cnt_id;              /**< Ingress counter ID */
    mesa_bool_t           dlb_enable;          /**< Enable DLB policer */
    mesa_dlb_policer_id_t dlb_id;              /**< DLB policer ID */
    mesa_voe_idx_t        voe_idx CAP(OAM);    /**< VOE index or MESA_VOE_IDX_NONE */
    mesa_voi_idx_t        voi_idx CAP(OAM);    /**< VOI index or MESA_VOI_IDX_NONE */
} mesa_iflow_conf_t;

/**
 * \brief Get ingress flow configuration.
 *
 * \param inst [IN]   Target instance reference.
 * \param id [IN]     Ingress flow ID.
 * \param conf [OUT]  Ingress flow configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_iflow_conf_get(const mesa_inst_t     inst,
                            const mesa_iflow_id_t id,
                            mesa_iflow_conf_t     *const conf);

/**
 * \brief Set ingress flow configuration.
 *
 * \param inst [IN]  Target instance reference.
 * \param id [IN]    Ingress flow ID.
 * \param conf [IN]  Ingress flow configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_iflow_conf_set(const mesa_inst_t      inst,
                            const mesa_iflow_id_t   id,
                            const mesa_iflow_conf_t *const conf);

/* - Tag Control List ---------------------------------------------- */

/** \brief TCE ID type */
typedef uint32_t mesa_tce_id_t;

#define MESA_TCE_ID_LAST 0 /**< Special value used to add last in list */

/** \brief Egress flow ID */
typedef uint16_t mesa_eflow_id_t;

#define MESA_EFLOW_ID_NONE 0      /**< No flow ID allocated */

/** \brief TCE Key */
typedef struct
{
    mesa_port_list_t port_list;   /**< Port list */
    mesa_vid_t       vid;         /**< Classified VLAN ID (zero means any VID) */
    mesa_bool_t      flow_enable; /**< Enable ingress flow ID instead of VLAN ID */
    mesa_iflow_id_t  flow_id;     /**< Ingress flow ID */
} mesa_tce_key_t;

/** \brief TCE TPID selection */
typedef enum {
    MESA_TPID_SEL_PORT,    /**< Tag pushed according to port VLAN configuration */
    MESA_TPID_SEL_NONE,    /**< No tag pushed */
    MESA_TPID_SEL_C,       /**< C-tag pushed */
    MESA_TPID_SEL_S,       /**< S-tag pushed */
    MESA_TPID_SEL_S_CUSTOM /**< S-custom tag pushed */
} mesa_tpid_sel_t;

/** \brief TCE PCP selection */
typedef enum {
    MESA_PCP_SEL_PORT,       /**< PCP selected according to port QoS configuration */
    MESA_PCP_SEL_FIXED,      /**< Fixed PCP value */
    MESA_PCP_SEL_CLASSIFIED, /**< Classified PCP value */
    MESA_PCP_SEL_MAPPED      /**< Mapped PCP value */
} mesa_pcp_sel_t;

/** \brief TCE DEI selection */
typedef enum {
    MESA_DEI_SEL_PORT,       /**< DEI selected according to port QoS configuration */
    MESA_DEI_SEL_FIXED,      /**< Fixed DEI value */
    MESA_DEI_SEL_CLASSIFIED, /**< Classified DEI value */
    MESA_DEI_SEL_MAPPED      /**< Mapped DEI value */
} mesa_dei_sel_t;

/** \brief TCE tag information */
typedef struct
{
    mesa_tpid_sel_t          tpid;    /**< TPID selection */
    mesa_vid_t               vid;     /**< VLAN ID, value zero means classified */
    mesa_pcp_sel_t           pcp_sel; /**< PCP selection */
    mesa_pcp_t               pcp;     /**< PCP value */
    mesa_dei_sel_t           dei_sel; /**< DEI selection */
    mesa_dei_t               dei;     /**< DEI value */
    mesa_qos_egress_map_id_t map_id;  /**< Egress QoS map */
} mesa_tce_tag_t;

/** \brief TCE Action */
typedef struct
{
    mesa_tce_tag_t  tag;       /**< Outer tag */
    mesa_tce_tag_t  inner_tag; /**< Inner tag */
    uint8_t         pop_cnt;   /**< Tag pop count */
    mesa_eflow_id_t flow_id;   /**< Egress flow ID */
} mesa_tce_action_t;

/** \brief Tag Control Entry */
typedef struct
{
    mesa_tce_id_t     id;     /**< TCE ID */
    mesa_tce_key_t    key;    /**< TCE Key */
    mesa_tce_action_t action; /**< TCE Action */
} mesa_tce_t;

/**
 * \brief Initialize TCE to default values.
 *
 * \param inst [IN]  Target instance reference.
 * \param tce [OUT]  TCE structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_tce_init(const mesa_inst_t inst,
                      mesa_tce_t        *const tce);

/**
 * \brief Add/modify TCE.
 *
 * \param inst [IN]    Target instance reference.
 * \param tce_id [IN]  TCE ID. The TCE will be added before the entry with this ID.
 *                     MESA_TCE_ID_LAST is reserved for inserting last.
 * \param tce [IN]     TCE structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_tce_add(const mesa_inst_t   inst,
                     const mesa_tce_id_t tce_id,
                     const mesa_tce_t    *const tce);

/**
 * \brief Delete VCE.
 *
 * \param inst [IN]    Target instance reference.
 * \param tce_id [IN]  TCE ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_tce_del(const mesa_inst_t   inst,
                     const mesa_tce_id_t tce_id);

/* - Egress counters ----------------------------------------------- */

/** \brief Egress counter ID */
typedef uint16_t mesa_egress_cnt_id_t;

/**
 * \brief Allocate egress counters.
 *
 * \param inst [IN]  Target instance reference.
 * \param cnt [IN]   Number of classes/COSIDs
 * \param id [OUT]   Egress counter ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_egress_cnt_alloc(const mesa_inst_t      inst,
                              const mesa_class_cnt_t cnt,
                              mesa_egress_cnt_id_t   *const id);

/**
 * \brief Free egress counters.
 *
 * \param inst [IN]  Target instance reference.
 * \param id [IN]    Egress counter ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_egress_cnt_free(const mesa_inst_t          inst,
                             const mesa_egress_cnt_id_t id);

/** \brief Egress counters */
typedef struct {
    mesa_counter_pair_t tx_green;   /**< Tx green frames/bytes */
    mesa_counter_pair_t tx_yellow;  /**< Tx yellow frames/bytes */
} mesa_egress_counters_t;

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
mesa_rc mesa_egress_cnt_get(const mesa_inst_t          inst,
                            const mesa_egress_cnt_id_t id,
                            const mesa_cosid_t         cosid,
                            mesa_egress_counters_t     *counters);

/**
 * \brief Clear egress counters.
 *
 * \param inst [IN]   Target instance reference.
 * \param id [IN]     Egress counter ID.
 * \param cosid [IN]  COSID.
 *
 * \return Return code.
 **/
mesa_rc mesa_egress_cnt_clear(const mesa_inst_t          inst,
                              const mesa_egress_cnt_id_t id,
                              const mesa_cosid_t         cosid);

/* - Egress flow --------------------------------------------------- */

/**
 * \brief Allocate egress flow.
 *
 * \param inst [IN]  Target instance reference.
 * \param id [OUT]   Egress flow ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_eflow_alloc(const mesa_inst_t inst,
                         mesa_eflow_id_t   *const id);

/**
 * \brief Free egress flow.
 *
 * \param inst [IN]  Target instance reference.
 * \param id [IN]    Egress flow ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_eflow_free(const mesa_inst_t     inst,
                        const mesa_eflow_id_t id);

/** \brief Egress flow configuration */
typedef struct
{
    mesa_bool_t          cnt_enable;          /**< Enable ingress counter mapping */
    mesa_egress_cnt_id_t cnt_id;              /**< Ingress counter ID */
    mesa_voe_idx_t       voe_idx CAP(OAM);    /**< VOE index or MESA_VOE_IDX_NONE */
    mesa_voi_idx_t       voi_idx CAP(OAM_V2); /**< VOI index or MESA_VOI_IDX_NONE */
} mesa_eflow_conf_t;

/**
 * \brief Get egress flow configuration.
 *
 * \param inst [IN]   Target instance reference.
 * \param id [IN]     Egress flow ID.
 * \param conf [OUT]  Egress flow configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_eflow_conf_get(const mesa_inst_t     inst,
                            const mesa_eflow_id_t id,
                            mesa_eflow_conf_t     *const conf);

/**
 * \brief Set egress flow configuration.
 *
 * \param inst [IN]  Target instance reference.
 * \param id [IN]    Egress flow ID.
 * \param conf [IN]  Egress flow configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_eflow_conf_set(const mesa_inst_t       inst,
                            const mesa_eflow_id_t   id,
                            const mesa_eflow_conf_t *const conf);

/* - VLAN translation ---------------------------------------------- */

/** \brief VLAN translation port-to-group configuration */
typedef struct {
    uint16_t         group_id;  /**< Group ID */
    mesa_port_list_t port_list; /**< Port list */
} mesa_vlan_trans_port2grp_conf_t;

/** \brief VLAN translation direction */
typedef enum {
    MESA_VLAN_TRANS_DIR_BOTH,     /**< Bidirectional translation */
    MESA_VLAN_TRANS_DIR_INGRESS,  /**< Ingress translation */
    MESA_VLAN_TRANS_DIR_EGRESS    /**< Egress translation */
} mesa_vlan_trans_dir_t;

/** \brief VLAN translation group-to-VLAN configuration */
typedef struct {
    uint16_t              group_id;  /**< Group ID */
    mesa_vid_t            vid;       /**< External VLAN ID (ingress key, egress data) */
    mesa_vid_t            trans_vid; /**< Internal VLAN ID (egress key, ingress data) */
    mesa_vlan_trans_dir_t dir;       /**< Direction */
} mesa_vlan_trans_grp2vlan_conf_t;

/**
 * \brief Add VLAN Translation Group entry.
 *
 * \param inst      [IN]  Target instance reference.
 * \param conf      [IN]  Translation configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_vlan_trans_group_add(const mesa_inst_t                     inst,
                                  const mesa_vlan_trans_grp2vlan_conf_t *const conf);

/**
 * \brief Delete VLAN Translation Group entry.
 *
 * \param inst [IN] Target instance reference.
 * \param conf [IN] Translation configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_vlan_trans_group_del(const mesa_inst_t                     inst,
                                  const mesa_vlan_trans_grp2vlan_conf_t *const conf);

/**
 * \brief Get VLAN Translation Group entry.
 *
 * \param inst [IN]  Target instance reference.
 * \param in   [IN]  Translation configuration.
 * \param conf [OUT] Translation configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_vlan_trans_group_get(const mesa_inst_t                     inst,
                                  const mesa_vlan_trans_grp2vlan_conf_t *const in,
                                  mesa_vlan_trans_grp2vlan_conf_t       *const conf);

/**
 * \brief Get next VLAN Translation Group entry.
 *
 * \param inst [IN]  Target instance reference.
 * \param in   [IN]  Translation configuration.
 * \param conf [OUT] Translation configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_vlan_trans_group_get_next(const mesa_inst_t                     inst,
                                       const mesa_vlan_trans_grp2vlan_conf_t *const in,
                                       mesa_vlan_trans_grp2vlan_conf_t       *conf);

/**
 * \brief Associate VLAN Translation Group entries to a port_list. Only one port can be part
          of one group not multiple groups.
 *
 * \param inst [IN] Target instance reference.
 * \param conf [IN] Pointer to mesa_vlan_trans_port2grp_conf_t.
 *
 * \return Return code.
 **/
mesa_rc mesa_vlan_trans_group_to_port_set(const mesa_inst_t                     inst,
                                          const mesa_vlan_trans_port2grp_conf_t *const conf);

/**
 * \brief VLAN Translation function to fetch all ports for a group.
 *
 * \param inst     [IN]  Target instance reference.
 * \param group_id [IN]  Group ID.
 * \param conf     [OUT] Pointer to mesa_vlan_trans_port2grp_conf_t.
 *
 * \return Return code.
 **/
mesa_rc mesa_vlan_trans_group_to_port_get(const mesa_inst_t               inst,
                                          const uint16_t                  group_id,
                                          mesa_vlan_trans_port2grp_conf_t *conf);

/**
 * \brief VLAN Translation function to fetch all ports for next group.
 *
 * \param inst     [IN]  Target instance reference.
 * \param group_id [IN]  Group ID.
 * \param conf     [OUT] Pointer to mesa_vlan_trans_port2grp_conf_t.
 *
 * \return Return code.
 **/
mesa_rc mesa_vlan_trans_group_to_port_get_next(const mesa_inst_t               inst,
                                               const uint16_t                  group_id,
                                               mesa_vlan_trans_port2grp_conf_t *conf);

/** \brief VCAP port configuration */
typedef struct {
    mesa_vcap_key_type_t key_type_is1_1; /**< Key type for second IS1 lookup */
    mesa_bool_t          dmac_dip_1;     /**< Enable DMAC/DIP matching in second lookup (default SMAC/SIP) */
} mesa_vcap_port_conf_t CAP(L2_VCAP_PORT_CONF);

/**
 * \brief Get VCAP port configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    VCAP port configuration structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_vcap_port_conf_get(const mesa_inst_t     inst,
                                const mesa_port_no_t  port_no,
                                mesa_vcap_port_conf_t *const conf)
    CAP(L2_VCAP_PORT_CONF);

/**
 * \brief Set VCAP port configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     VCAP port configuration structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_vcap_port_conf_set(const mesa_inst_t           inst,
                                const mesa_port_no_t        port_no,
                                const mesa_vcap_port_conf_t *const conf)
    CAP(L2_VCAP_PORT_CONF);

/* - Port Isolation------------------------------------------------- */

/**
 * \brief Get enable/disable port isolation for VLAN.
 *
 * \param inst [IN]       Target instance reference.
 * \param vid [IN]        VLAN ID.
 * \param isolated [OUT]  VLAN isolation enable/disable option.
 *
 * \return Return code.
 **/
mesa_rc mesa_isolated_vlan_get(const mesa_inst_t  inst,
                               const mesa_vid_t   vid,
                               mesa_bool_t        *const isolated);


/**
 * \brief Set enable/disable port isolation for VLAN.
 *
 * \param inst [IN]      Target instance reference.
 * \param vid [IN]       VLAN ID.
 * \param isolated [IN]  VLAN isolation enable/disable option.
 *
 * \return Return code.
 **/
mesa_rc mesa_isolated_vlan_set(const mesa_inst_t  inst,
                               const mesa_vid_t   vid,
                               const mesa_bool_t  isolated);



/**
 * \brief Get the isolated port member set.
 *
 * \param inst [IN]     Target instance reference.
 * \param member [OUT]  Isolated port member list.
 *
 * \return Return code.
 **/
mesa_rc mesa_isolated_port_members_get(const mesa_inst_t inst,
                                       mesa_port_list_t  *port_list);


/**
 * \brief Set the isolated port member set.
 *
 * \param inst [IN]    Target instance reference.
 * \param member [IN]  Isolated port member list.
 *
 * \return Return code.
 **/
mesa_rc mesa_isolated_port_members_set(const mesa_inst_t      inst,
                                       const mesa_port_list_t *port_list);


/* - Private VLAN (PVLAN) ------------------------------------------ */

/** \brief Private VLAN Number */
typedef uint32_t mesa_pvlan_no_t;

/**
 * \brief Get Private VLAN membership.
 *
 * \param inst [IN]      Target instance reference.
 * \param pvlan_no [IN]  Private VLAN group number.
 * \param member [OUT]   Private VLAN port member list.
 *
 * \return Return code.
 **/
mesa_rc mesa_pvlan_port_members_get(const mesa_inst_t     inst,
                                    const mesa_pvlan_no_t pvlan_no,
                                    mesa_port_list_t      *port_list);


/**
 * \brief Set Private VLAN membership.
 *
 * \param inst [IN]      Target instance reference.
 * \param pvlan_no [IN]  Private VLAN group number.
 * \param member [IN]    Private VLAN port member list.
 *
 * \return Return code.
 **/
mesa_rc mesa_pvlan_port_members_set(const mesa_inst_t      inst,
                                    const mesa_pvlan_no_t  pvlan_no,
                                    const mesa_port_list_t *port_list);


/**
* \brief Get Asymmetric Private VLAN membership.
*
* \param inst [IN]     Target instance reference.
* \param port_no [IN]  Ingress port.
* \param member [OUT]  Asymmetric Private VLAN port member list.
*
* \return Return code.
**/
mesa_rc mesa_apvlan_port_members_get(const mesa_inst_t    inst,
                                     const mesa_port_no_t port_no,
                                     mesa_port_list_t     *port_list);


/**
* \brief Set Asymmetric Private VLAN membership.
*
* \param inst [IN]     Target instance reference.
* \param port_no [IN]  Ingress port.
* \param member [IN]   Asymmetric Private VLAN port member list.
*
* \return Return code.
**/
mesa_rc mesa_apvlan_port_members_set(const mesa_inst_t      inst,
                                     const mesa_port_no_t   port_no,
                                     const mesa_port_list_t *port_list);


/** \brief EVC policer configuration */
typedef mesa_port_no_t mesa_dgroup_no_t;

/** \brief Destination group port configuration */
typedef struct {
    mesa_dgroup_no_t dgroup_no; /**< Destination port group */
} mesa_dgroup_port_conf_t;

/**
 * \brief Get Destination Group configuration for port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    Destination group port configuration structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_dgroup_port_conf_get(const mesa_inst_t       inst,
                                  const mesa_port_no_t    port_no,
                                  mesa_dgroup_port_conf_t *const conf);

/**
 * \brief Set Destination Group configuration for port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     Destination group port configuration structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_dgroup_port_conf_set(const mesa_inst_t             inst,
                                  const mesa_port_no_t          port_no,
                                  const mesa_dgroup_port_conf_t *const conf);


/* - SFLOW --------------------------------------------------------- */

/**
 * \brief sFlow configuration structure.
 *
 * Not all sampling rates are supported.
 * Since the sFlow standard mandates that returned sample rates are
 * actual sample rates and not desired sample rates, it is recommended
 * to call mesa_sflow_sampling_rate_convert() to obtain the actual
 * sample rate given a desired sample rate.
 * mesa_sflow_port_conf_set() will auto-convert the requested sample rate
 * to an actual sample rate, which will be returned in subsequent calls
 * to mesa_sflow_port_conf_get().
 */

/**
 * \brief sFlow sampler type.
 *
 * The API supports sampling ingress and egress separately, as well
 * as simultaneously.
 */
typedef enum {
    MESA_SFLOW_TYPE_NONE = 0, /**< Sampler is not enabled on the port.                         */
    MESA_SFLOW_TYPE_RX,       /**< Sampler is enabled for ingress on the port.                 */
    MESA_SFLOW_TYPE_TX,       /**< Sampler is enabled for egress on the port.                  */
    MESA_SFLOW_TYPE_ALL       /**< Sampler is enabled for both ingress and egress on the port. */
} mesa_sflow_type_t;

typedef struct {
    mesa_sflow_type_t type;          /**< Sample direction. Also used to turn off sampling.                             */
    uint32_t          sampling_rate; /**< A value of N means: sample on average 1 out of N frames. 0 disables sampling. */
} mesa_sflow_port_conf_t;

/**
 * \brief Get port sFlow configuration.
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number (a.k.a. data source).
 * \param conf    [OUT] sFlow sampler configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_sflow_port_conf_get(const mesa_inst_t            inst,
                                 const mesa_port_no_t         port_no,
                                       mesa_sflow_port_conf_t *const conf);

/**
 * \brief Set port sFlow configuration.
 *
 * \param inst    [IN] Target instance reference.
 * \param port_no [IN] Port number (a.k.a. data source).
 * \param conf    [IN] sFlow sampler configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_sflow_port_conf_set(const mesa_inst_t            inst,
                                 const mesa_port_no_t         port_no,
                                 const mesa_sflow_port_conf_t *const conf);

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
mesa_rc mesa_sflow_sampling_rate_convert(const mesa_inst_t inst,
                                         const mesa_bool_t power2,
                                         const uint32_t    rate_in,
                                               uint32_t    *const rate_out);

/* - Aggregation --------------------------------------------------- */

/**
 * \brief Get aggregation port members.
 *
 * \param inst [IN]     Target instance reference.
 * \param aggr_no [IN]  Aggregation number.
 * \param member [OUT]  Aggregation port member list.
 *
 * \return Return code.
 **/
mesa_rc mesa_aggr_port_members_get(const mesa_inst_t    inst,
                                   const mesa_aggr_no_t aggr_no,
                                   mesa_port_list_t     *port_list);


/**
 * \brief Set aggregation port members.
 *
 * \param inst [IN]     Target instance reference.
 * \param aggr_no [IN]  Aggregation number.
 * \param member [IN]   Aggregation port member list.
 *
 * \return Return code.
 **/
mesa_rc mesa_aggr_port_members_set(const mesa_inst_t      inst,
                                   const mesa_aggr_no_t   aggr_no,
                                   const mesa_port_list_t *port_list);

/** \brief Aggregation traffic distribution mode */
typedef struct
{
    mesa_bool_t smac_enable;            /**< Source MAC address */
    mesa_bool_t dmac_enable;            /**< Destination MAC address */
    mesa_bool_t sip_dip_enable;         /**< Source and destination IP address */
    mesa_bool_t sport_dport_enable;     /**< Source and destination UDP/TCP port */
} mesa_aggr_mode_t;

/**
 * \brief Get aggregation traffic distribution mode.
 *
 * \param inst [IN]   Target instance reference.
 * \param mode [OUT]  Distribution mode structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_aggr_mode_get(const mesa_inst_t  inst,
                           mesa_aggr_mode_t   *const mode);


/**
 * \brief Set aggregation traffic distribution mode.
 *
 * \param inst [IN]  Target instance reference.
 * \param mode [IN]  Distribution mode structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_aggr_mode_set(const mesa_inst_t       inst,
                           const mesa_aggr_mode_t  *const mode);


/* - Mirroring ----------------------------------------------------- */

/** \brief Mirror port configuration */
typedef enum
{
    MESA_MIRROR_TAG_NONE,    /**< No mirror tag is added */
    MESA_MIRROR_TAG_C,       /**< C-tag is added */
    MESA_MIRROR_TAG_S,       /**< S-tag is added */
    MESA_MIRROR_TAG_S_CUSTOM /**< Custom S-tag is added */
} mesa_mirror_tag_t CAP(L2_MIRROR_TAG);

/** \brief Mirror configuration */
typedef struct
{
    mesa_port_no_t    port_no;                /**< Mirror port or MESA_PORT_NO_NONE */
    mesa_bool_t       fwd_enable;             /**< Enable normal traffic forwarding to mirror port */
    mesa_mirror_tag_t tag CAP(L2_MIRROR_TAG); /**< Mirror tag type */
    mesa_vid_t        vid CAP(L2_MIRROR_TAG); /**< Mirror tag VID */
    mesa_tagprio_t    pcp CAP(L2_MIRROR_TAG); /**< Mirror tag PCP */
    mesa_dei_t        dei CAP(L2_MIRROR_TAG); /**< Mirror tag DEI */
} mesa_mirror_conf_t;

/**
 * \brief Get the mirror configuration.
 *
 * \param inst [IN]   Target instance reference.
 * \param conf [OUT]  Mirror configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_mirror_conf_get(const mesa_inst_t  inst,
                             mesa_mirror_conf_t *const conf);

/**
 * \brief Set the mirror configuration.
 *
 * \param inst [IN]  Target instance reference.
 * \param conf [IN]  Mirror configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_mirror_conf_set(const mesa_inst_t        inst,
                             const mesa_mirror_conf_t *const conf);



/**
 * \brief Set the mirror monitor port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number or MESA_PORT_NO_NONE.
 *
 * \return Return code.
 **/
mesa_rc mesa_mirror_monitor_port_set(const mesa_inst_t     inst,
                                     const mesa_port_no_t  port_no);
mesa_rc mesa_mirror_monitor_port_get(const mesa_inst_t  inst,
                                     mesa_port_no_t     *const port_no);


/**
 * \brief Get the mirror ingress ports.
 *
 * \param inst [IN]     Target instance reference.
 * \param member [OUT]  Port member list. If a port is enabled in this array,
 *                      frames received on the port are mirrored.
 *
 * \return Return code.
 **/
mesa_rc mesa_mirror_ingress_ports_get(const mesa_inst_t inst,
                                      mesa_port_list_t  *port_list);


/**
 * \brief Set the mirror ingress ports.
 *
 * \param inst [IN]    Target instance reference.
 * \param member [IN]  Port member list. If a port is enabled in this array,
 *                     frames received on the port are mirrored.
 *
 * \return Return code.
 **/
mesa_rc mesa_mirror_ingress_ports_set(const mesa_inst_t      inst,
                                      const mesa_port_list_t *port_list);


/**
 * \brief Get the mirror egress ports.
 *
 * \param inst [IN]     Target instance reference.
 * \param member [OUT]  Port member list. If a port is enabled in this array,
 *                      frames transmitted on the port are mirrored.
 *
 * \return Return code.
 **/
mesa_rc mesa_mirror_egress_ports_get(const mesa_inst_t inst,
                                     mesa_port_list_t  *port_list);


/**
 * \brief Set the mirror egress ports.
 *
 * \param inst [IN]    Target instance reference.
 * \param member [IN]  Port member list. If a port is enabled in this array,
 *                     frames transmitted on the port are mirrored.
 *
 * \return Return code.
 **/
mesa_rc mesa_mirror_egress_ports_set(const mesa_inst_t      inst,
                                     const mesa_port_list_t *port_list);




/**
 * \brief Get the mirror CPU ingress.
 *
 * \param inst [IN]     Target instance reference.
 * \param member [OUT]  CPU  member. If a CPU is enabled,
 *                      frames received to the CPU port are mirrored.
 *
 * \return Return code.
 **/
mesa_rc mesa_mirror_cpu_ingress_get(const mesa_inst_t  inst,
                                    mesa_bool_t        *member);


/**
 * \brief Set CPU ingress mirroring.
 *
 * Enabling CPU ingress mirroring means that frames destined for the CPU
 * are mirrored to the mirror port.
 *
 * \param inst [IN]    Target instance reference.
 * \param member [IN]  CPU member. If a CPU is enabled,
 *                     frames received by the CPU port are mirrored.
 *
 * \return Return code.
 **/
mesa_rc mesa_mirror_cpu_ingress_set(const mesa_inst_t  inst,
                                    const mesa_bool_t  member);


/**
 * \brief Get the mirror CPU egress.
 *
 * \param inst [IN]     Target instance reference.
 * \param member [OUT]  CPU member. If a CPU is enabled,
 *                      frames transmitted by the CPU port are mirrored.
 *
 * \return Return code.
 **/
mesa_rc mesa_mirror_cpu_egress_get(const mesa_inst_t  inst,
                                   mesa_bool_t        *member);


/**
 * \brief Set the mirror CPU egress
 *
 * Enabling CPU egress mirroring means that frames transmitted by the CPU
 * are mirrored to the mirror port.
 *
 * \param inst [IN]    Target instance reference.
 * \param member [IN]  CPU member. If a CPU is enabled,
 *                     frames transmitted by the CPU the port are mirrored.
 *
 * \return Return code.
 **/
mesa_rc mesa_mirror_cpu_egress_set(const mesa_inst_t  inst,
                                   const mesa_bool_t  member);

/* - Flooding control ---------------------------------------------- */

// Get unicast flood members.
mesa_rc mesa_uc_flood_members_get(const mesa_inst_t inst,
                                  mesa_port_list_t  *port_list);
mesa_rc mesa_uc_flood_members_set(const mesa_inst_t      inst,
                                  const mesa_port_list_t *port_list);



mesa_rc mesa_mc_flood_members_get(const mesa_inst_t inst,
                                  mesa_port_list_t  *port_list);
mesa_rc mesa_mc_flood_members_set(const mesa_inst_t      inst,
                                  const mesa_port_list_t *port_list);



/* - Flooding control ---------------------------------------------- */

/**
 * \brief Get unicast flood members.
 *
 * \param inst [IN]     Target instance reference.
 * \param member [OUT]  Port member list.
 *
 * \return Return code.
 **/
mesa_rc mesa_uc_flood_members_get(const mesa_inst_t inst,
                                  mesa_port_list_t  *port_list);


/**
 * \brief Set unicast flood members.
 *
 * \param inst [IN]    Target instance reference.
 * \param member [IN]  Port member list.
 *
 * \return Return code.
 **/
mesa_rc mesa_uc_flood_members_set(const mesa_inst_t      inst,
                                  const mesa_port_list_t *port_list);


/**
 * \brief Get multicast flood members.
 *
 * \param inst [IN]     Target instance reference.
 * \param member [OUT]  Port member list.
 *
 * \return Return code.
 **/
mesa_rc mesa_mc_flood_members_get(const mesa_inst_t inst,
                                  mesa_port_list_t  *port_list);


/**
 * \brief Set multicast flood members.
 *
 * \param inst [IN]    Target instance reference.
 * \param member [IN]  Port member list.
 *
 * \return Return code.
 **/
mesa_rc mesa_mc_flood_members_set(const mesa_inst_t      inst,
                                  const mesa_port_list_t *port_list);


/* - IGMP ---------------------------------------------------- */

/**
 * \brief Get IPv4 multicast flood members.
 *
 * \param inst [IN]     Target instance reference.
 * \param member [OUT]  Port member list.
 *                      Ports connected to IPv4 multicast routers should be enabled.
 *
 * \return Return code.
 **/
mesa_rc mesa_ipv4_mc_flood_members_get(const mesa_inst_t inst,
                                       mesa_port_list_t  *port_list);


/**
 * \brief Set IPv4 multicast flood members.
 *
 * \param inst [IN]    Target instance reference.
 * \param member [IN]  Port member list.
 *                     Ports connected to IPv4 multicast routers should be enabled.
 *
 * \return Return code.
 **/
mesa_rc mesa_ipv4_mc_flood_members_set(const mesa_inst_t      inst,
                                       const mesa_port_list_t *port_list);


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
mesa_rc mesa_ipv4_mc_add(const mesa_inst_t      inst,
                         const mesa_vid_t       vid,
                         const mesa_ip_t        sip,
                         const mesa_ip_t        dip,
                         const mesa_port_list_t *port_list)
    CAP(L2_IPV4_MC_SIP);

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
mesa_rc mesa_ipv4_mc_del(const mesa_inst_t inst,
                         const mesa_vid_t  vid,
                         const mesa_ip_t   sip,
                         const mesa_ip_t   dip)
    CAP(L2_IPV4_MC_SIP);

/* - MLD  ----------------------------------------------------- */

/**
 * \brief Get IPv6 multicast flood members.
 *
 * \param inst [IN]     Target instance reference.
 * \param member [OUT]  Port member list.
 *                      Ports connected to IPv6 multicast routers should be enabled.
 *
 * \return Return code.
 **/
mesa_rc mesa_ipv6_mc_flood_members_get(const mesa_inst_t inst,
                                       mesa_port_list_t  *port_list);


/**
 * \brief Set IPv6 multicast flood members.
 *
 * \param inst [IN]    Target instance reference.
 * \param member [IN]  Port member list.
 *                     Ports connected to IPv6 multicast routers should be enabled.
 *
 * \return Return code.
 **/
mesa_rc mesa_ipv6_mc_flood_members_set(const mesa_inst_t      inst,
                                       const mesa_port_list_t *port_list);


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
mesa_rc mesa_ipv6_mc_ctrl_flood_get(const mesa_inst_t  inst,
                                    mesa_bool_t        *const scope);

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
mesa_rc mesa_ipv6_mc_ctrl_flood_set(const mesa_inst_t  inst,
                                    const mesa_bool_t  scope);

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
mesa_rc mesa_ipv6_mc_add(const mesa_inst_t      inst,
                         const mesa_vid_t       vid,
                         const mesa_ipv6_t      sip,
                         const mesa_ipv6_t      dip,
                         const mesa_port_list_t *port_list)
    CAP(L2_IPV6_MC_SIP);

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
mesa_rc mesa_ipv6_mc_del(const mesa_inst_t inst,
                         const mesa_vid_t  vid,
                         const mesa_ipv6_t sip,
                         const mesa_ipv6_t dip)
    CAP(L2_IPV6_MC_SIP);


/* - Ethernet Protection Switching ---------------------------------- */

/** \brief Port protection type */
typedef enum
{
    MESA_EPS_PORT_1_PLUS_1,  /**< 1+1 protection */
    MESA_EPS_PORT_1_FOR_1    /**< 1:1 protection */
} mesa_eps_port_type_t;

/** \brief Port protection configuration */
typedef struct
{
    mesa_eps_port_type_t type;     /**< Protection type */
    mesa_port_no_t       port_no;  /**< Protection port or MESA_PORT_NO_NONE */
} mesa_eps_port_conf_t;

/**
 * \brief Get EPS port configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Working port.
 * \param conf [OUT]    Protection configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_eps_port_conf_get(const mesa_inst_t     inst,
                               const mesa_port_no_t  port_no,
                               mesa_eps_port_conf_t  *const conf);


/**
 * \brief Set EPS port configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Working port.
 * \param conf [IN]     Protection configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_eps_port_conf_set(const mesa_inst_t           inst,
                               const mesa_port_no_t        port_no,
                               const mesa_eps_port_conf_t  *const conf);


/** \brief EPS selector */
typedef enum
{
    MESA_EPS_SELECTOR_WORKING,    /**< Select working port */
    MESA_EPS_SELECTOR_PROTECTION  /**< Select protection port */
} mesa_eps_selector_t;

/**
 * \brief Get EPS port selector.
 *
 * \param inst [IN]       Target instance reference.
 * \param port_no [IN]    Working port.
 * \param selector [OUT]  Selector.
 *
 * \return Return code.
 **/
mesa_rc mesa_eps_port_selector_get(const mesa_inst_t     inst,
                                   const mesa_port_no_t  port_no,
                                   mesa_eps_selector_t   *const selector);

/**
 * \brief Set EPS port selector.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Working port.
 * \param selector [IN]  Selector.
 *
 * \return Return code.
 **/
mesa_rc mesa_eps_port_selector_set(const mesa_inst_t          inst,
                                   const mesa_port_no_t       port_no,
                                   const mesa_eps_selector_t  selector);

/* - Ethernet Ring Protection Swiching ----------------------------- */

/** \brief ERPS instance number */
typedef uint32_t mesa_erpi_t;

#define MESA_ERPIS           (64)                         /**< Number of ERPS instances */
#define MESA_ERPI_START      (0)                          /**< ERPI start number */
#define MESA_ERPI_END        (MESA_ERPI_START+MESA_ERPIS) /**< ERPI end number */
#define MESA_ERPI_ARRAY_SIZE MESA_ERPI_END                /**< ERPI array size */

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
mesa_rc mesa_erps_vlan_member_get(const mesa_inst_t inst,
                                  const mesa_erpi_t erpi,
                                  const mesa_vid_t  vid,
                                  mesa_bool_t       *const member);


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
mesa_rc mesa_erps_vlan_member_set(const mesa_inst_t inst,
                                  const mesa_erpi_t erpi,
                                  const mesa_vid_t  vid,
                                  const mesa_bool_t member);


/** \brief ERPS state */
typedef enum {
    MESA_ERPS_STATE_FORWARDING, /**< Forwarding */
    MESA_ERPS_STATE_DISCARDING, /**< Discarding */
} mesa_erps_state_t;

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
mesa_rc mesa_erps_port_state_get(const mesa_inst_t    inst,
                                 const mesa_erpi_t    erpi,
                                 const mesa_port_no_t port_no,
                                 mesa_erps_state_t    *const state);


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
mesa_rc mesa_erps_port_state_set(const mesa_inst_t       inst,
                                 const mesa_erpi_t       erpi,
                                 const mesa_port_no_t    port_no,
                                 const mesa_erps_state_t state);

#include <mscc/ethernet/switch/api/hdr_end.h>
#endif // _MSCC_ETHERNET_SWITCH_API_L2_
