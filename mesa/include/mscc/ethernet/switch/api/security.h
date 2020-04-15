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

#ifndef _MSCC_ETHERNET_SWITCH_API_SECURITY_
#define _MSCC_ETHERNET_SWITCH_API_SECURITY_

#include <mscc/ethernet/switch/api/types.h>
#include <mscc/ethernet/switch/api/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

/* - Port Based Network Access Control, 802.1X --------------------- */

/** \brief Authentication state */
typedef enum
{
    MESA_AUTH_STATE_NONE,   /**< Not authenticated */
    MESA_AUTH_STATE_EGRESS, /**< Authenticated in egress direction */
    MESA_AUTH_STATE_BOTH    /**< Authenticated in both directions */
} mesa_auth_state_t;

/**
 * \brief Get 802.1X Authentication state for a port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param state [OUT]   Authentication state.
 *
 * \return Return code.
 **/
mesa_rc mesa_auth_port_state_get(const mesa_inst_t    inst,
                                 const mesa_port_no_t port_no,
                                 mesa_auth_state_t    *const state);


/**
 * \brief Set 802.1X Authentication state for a port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param state [IN]    Authentication state.
 *
 * \return Return code.
 **/
mesa_rc mesa_auth_port_state_set(const mesa_inst_t       inst,
                                 const mesa_port_no_t    port_no,
                                 const mesa_auth_state_t state);

/* - Access Control Lists ------------------------------------------ */

/** \brief ACL policer configuration */
typedef struct {
    mesa_bool_t        bit_rate_enable; /**< Use bit rate policing instead of packet rate */
    mesa_bitrate_t     bit_rate;        /**< Bit rate */
    mesa_packet_rate_t rate;            /**< Packet rate */
} mesa_acl_policer_conf_t;


/**
 * \brief Get ACL policer configuration.
 *
 * \param inst [IN]        Target instance reference.
 * \param policer_no [IN]  ACL policer number.
 * \param conf [OUT]       ACL policer configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_acl_policer_conf_get(const mesa_inst_t           inst,
                                  const mesa_acl_policer_no_t policer_no,
                                  mesa_acl_policer_conf_t     *const conf);


/**
 * \brief Set ACL policer configuration.
 *
 * \param inst [IN]        Target instance reference.
 * \param policer_no [IN]  ACL policer number.
 * \param conf [IN]        ACL policer configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_acl_policer_conf_set(const mesa_inst_t             inst,
                                  const mesa_acl_policer_no_t   policer_no,
                                  const mesa_acl_policer_conf_t *const conf);


/** \brief ACL port action */
typedef enum
{
    MESA_ACL_PORT_ACTION_NONE,   /**< No action from port list */
    MESA_ACL_PORT_ACTION_FILTER, /**< Port list filter is used */
    MESA_ACL_PORT_ACTION_REDIR   /**< Port list redirect is used */
} mesa_acl_port_action_t;

/** \brief ACL PTP action */
typedef enum
{
    MESA_ACL_PTP_ACTION_NONE,     /**< No PTP action */
    MESA_ACL_PTP_ACTION_ONE_STEP, /**< PTP one-step time-stamping */
    MESA_ACL_PTP_ACTION_ONE_STEP_ADD_DELAY   CAP(ACL_PTP_DELAY), /**< PTP one-step time-stamping, Serval: add delay, Jr2: Add EDLY */
    MESA_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_1 CAP(ACL_PTP_DELAY), /**< PTP one-step time-stamping, Serval: subtract delay 1, Jr2: Add IDLY1 */
    MESA_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_2 CAP(ACL_PTP_DELAY), /**< PTP one-step time-stamping, Serval: subtract delay 2, Jr2: Add IDLY2 */
    MESA_ACL_PTP_ACTION_ONE_AND_TWO_STEP     CAP(ACL_PTP_ONE_AND_TWO_STEP), /**< PTP one-step and two-step time-stamping */
    MESA_ACL_PTP_ACTION_TWO_STEP /**< PTP two-step time-stamping */
} mesa_acl_ptp_action_t;

/** \brief ACL Source IP index. For IPv6 entries, it must be divisible by 4 and consumes 4 rules **/
typedef uint8_t mesa_acl_sip_idx_t CAP(ACL_SIP_CNT);

/** \brief ACL Source IP configuration */
typedef struct {
    mesa_ip_addr_t sip; /**< Source IP address */
} mesa_acl_sip_conf_t;

/**
 * \brief Set ACL Source IP configuration for index.
 *
 * \param inst [IN]  Target instance reference.
 * \param idx  [IN]  Entry index.
 * \param conf [IN]  Source IP configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_acl_sip_conf_set(const mesa_inst_t          inst,
                              const mesa_acl_sip_idx_t   idx,
                              const mesa_acl_sip_conf_t  *const conf)
    CAP(ACL_SIP_CNT);

/** \brief ACL PTP response action */
typedef enum
{
    MESA_ACL_PTP_RSP_NONE,               /**< No response action */
    MESA_ACL_PTP_RSP_DLY_REQ_RSP_TS_UPD, /**< Auto response to Delay_Req, includes receiveTimestamp update */
    MESA_ACL_PTP_RSP_DLY_REQ_RSP_NO_TS   /**< Auto response to Delay_Req, exludes receiveTimestamp update */
} mesa_acl_ptp_rsp_t CAP(ACL_SIP_CNT);

/** \brief ACL PTP action configuration */
typedef struct {
    mesa_acl_ptp_rsp_t response;             /**< PTP Delay_Req/Response action */
    int8_t             log_message_interval; /**< PTP logMessageInterval [-8,7] returned in the Delay_Resp message */
    mesa_bool_t        copy_smac_to_dmac;    /**< PTP DMAC operation */
    mesa_bool_t        set_smac_to_port_mac; /**< PTP SMAC operation */
    uint8_t            dom_sel;              /**< PTP domain selector. PTP_DOM_SEL indexes the PTP configuration */
    mesa_udp_tcp_t     sport;                /**< UDP source port */
    mesa_udp_tcp_t     dport;                /**< UDP destination port */
} mesa_acl_ptp_action_conf_t CAP(ACL_SIP_CNT);

/** \brief ACL address update */
typedef enum {
    MESA_ACL_ADDR_UPDATE_NONE,             /**< No SMAC/DMAC change */
    MESA_ACL_ADDR_UPDATE_MAC_SWAP,         /**< Swap SMAC and DMAC */
    MESA_ACL_ADDR_UPDATE_DMAC_REPLACE,     /**< Replace DMAC */
    MESA_ACL_ADDR_UPDATE_DMAC_REPLACE_MSB, /**< Replace 40 MSB of DMAC */
    MESA_ACL_ADDR_UPDATE_MAC_IP_SWAP_UC    /**< Swap MAC addresses if DMAC is unicast. Replace SMAC if DMAC is multicast. Same for SIP/DIP */
} mesa_acl_addr_update_t CAP(ACL_SIP_CNT);

/** \brief ACL address action configuration */
typedef struct {
    mesa_acl_addr_update_t update;  /**< Address update */
    mesa_mac_t             mac;     /**< MAC address used for replace operations */
    mesa_acl_sip_idx_t     sip_idx; /**< Source IP index */
} mesa_acl_addr_action_t CAP(ACL_SIP_CNT);

/** \brief ACL Action */
typedef struct
{
    mesa_bool_t                cpu;            /**< Forward to CPU */
    mesa_bool_t                cpu_once;       /**< Only first frame forwarded to CPU */
    mesa_packet_rx_queue_t     cpu_queue;      /**< CPU queue */
    mesa_bool_t                police;         /**< Enable policer */
    mesa_acl_policer_no_t      policer_no;     /**< Policer number */
    mesa_bool_t                evc_police     CAP(ACL_EVC_POLICER); /**< Enable EVC policer */
    mesa_evc_policer_id_t      evc_policer_id CAP(ACL_EVC_POLICER); /**< EVC policer ID */
    mesa_bool_t                learn;          /**< Allow learning */
    mesa_acl_port_action_t     port_action;    /**< Port action */
    mesa_port_list_t           port_list;      /**< Egress port list */
    mesa_bool_t                mirror;         /**< Enable mirroring */
    mesa_acl_ptp_action_t      ptp_action;     /**< PTP action */
    mesa_acl_ptp_action_conf_t ptp  CAP(ACL_SIP_CNT); /**< PTP configuration */
    mesa_acl_addr_action_t     addr CAP(ACL_SIP_CNT); /**< Address update configuration */
    mesa_bool_t                lm_cnt_disable CAP(ACL_LM_CNT_CTRL); /**< Disable OAM LM Tx counting */
    mesa_bool_t                mac_swap CAP(ACL_MAC_SWAP); /**< Swap SMAC and DMAC */
    mesa_bool_t                ifh_flag CAP(ACL_IFH_FLAG); /**< Control one target specific bit in IFH */
} mesa_acl_action_t;

/** \brief ACL port configuration */
typedef struct
{
    mesa_acl_policy_no_t policy_no; /**< Policy number */
    mesa_acl_action_t    action;    /**< Action */
} mesa_acl_port_conf_t;

/**
 * \brief Get ACL configuration for port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    Port configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_acl_port_conf_get(const mesa_inst_t     inst,
                               const mesa_port_no_t  port_no,
                               mesa_acl_port_conf_t  *const conf);

/**
 * \brief Set ACL configuration for port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     Port configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_acl_port_conf_set(const mesa_inst_t           inst,
                               const mesa_port_no_t        port_no,
                               const mesa_acl_port_conf_t  *const conf);


/** \brief ACL port counter */
typedef uint32_t mesa_acl_port_counter_t;

/**
 * \brief Get default action counter for port.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param counter [OUT]  Default action counter for port.
 *
 * \return Return code.
 **/
mesa_rc mesa_acl_port_counter_get(const mesa_inst_t        inst,
                                  const mesa_port_no_t     port_no,
                                  mesa_acl_port_counter_t  *const counter);

/**
 * \brief Clear default action counter for port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 *
 * \return Return code.
 **/
mesa_rc mesa_acl_port_counter_clear(const mesa_inst_t     inst,
                                    const mesa_port_no_t  port_no);


/** \brief ACE frame type */
typedef enum
{
    MESA_ACE_TYPE_ANY,     /**< Any frame type */
    MESA_ACE_TYPE_ETYPE,   /**< Ethernet Type */
    MESA_ACE_TYPE_LLC,     /**< LLC */
    MESA_ACE_TYPE_SNAP,    /**< SNAP */
    MESA_ACE_TYPE_ARP,     /**< ARP/RARP */
    MESA_ACE_TYPE_IPV4,    /**< IPv4 */
    MESA_ACE_TYPE_IPV6     /**< IPv6 */
} mesa_ace_type_t;

/** \brief ACE ID type */
typedef uint32_t mesa_ace_id_t;

#define MESA_ACE_ID_LAST 0 /**< Special value used to add last in list */

/** \brief ACE 1 bit */
typedef enum
{
    MESA_ACE_BIT_ANY, /**< Value 0 or 1 */
    MESA_ACE_BIT_0,   /**< Value 0 */
    MESA_ACE_BIT_1    /**< Value 1 */
} mesa_ace_bit_t;

/** \brief ACE 8 bit value and mask */
typedef mesa_vcap_u8_t mesa_ace_u8_t;

/** \brief ACE 16 bit value and mask */
typedef mesa_vcap_u16_t mesa_ace_u16_t;

/** \brief ACE 32 bit value and mask */
typedef mesa_vcap_u32_t mesa_ace_u32_t;

/** \brief ACE 40 bit value and mask */
typedef mesa_vcap_u40_t mesa_ace_u40_t;

/** \brief ACE 48 bit value and mask */
typedef mesa_vcap_u48_t mesa_ace_u48_t;

/** \brief ACE 128 bit value and mask */
typedef mesa_vcap_u128_t mesa_ace_u128_t;

/** \brief ACE VLAN ID value and mask */
typedef mesa_vcap_vid_t mesa_ace_vid_t;

/** \brief ACE IP address value and mask */
typedef mesa_vcap_ip_t mesa_ace_ip_t;

/** \brief ACE UDP/TCP port range */
typedef mesa_vcap_udp_tcp_t mesa_ace_udp_tcp_t;

/** \brief PTP header filtering */
typedef struct
{
    mesa_bool_t    enable; /**< Enable PTP header filtering */
    mesa_ace_u32_t header; /**< PTP header byte 0, 1, 4 and 6 */
} mesa_ace_ptp_t;

/** \brief SIP/SMAC filtering */
typedef struct
{
    mesa_bool_t enable; /**< Enable SIP/SMAC filtering */
    mesa_ip_t   sip;    /**< SIP */
    mesa_mac_t  smac;   /**< SMAC */
} mesa_ace_sip_smac_t;

/** \brief ACE VLAN information */
typedef struct
{
    mesa_ace_vid_t   vid;      /**< VLAN ID (12 bit) */
    mesa_ace_u8_t    usr_prio; /**< User priority/PCP (3 bit) */
    mesa_ace_bit_t   cfi;      /**< CFI/DEI */
    mesa_ace_bit_t   tagged;   /**< Tagged/untagged frame */
} mesa_ace_vlan_t;

/** \brief Frame data for MESA_ACE_TYPE_ETYPE */
typedef struct
{
    mesa_ace_u48_t dmac;  /**< DMAC */
    mesa_ace_u48_t smac;  /**< SMAC */
    mesa_ace_u16_t etype; /**< Ethernet Type value */
    mesa_ace_u16_t data;  /**< MAC data */
    mesa_ace_ptp_t ptp;   /**< PTP header filtering (overrides smac byte 2,4 and data fields) */
} mesa_ace_frame_etype_t;

/** \brief Frame data for MESA_ACE_TYPE_LLC */
typedef struct
{
    mesa_ace_u48_t dmac; /**< DMAC */
    mesa_ace_u48_t smac; /**< SMAC */
    mesa_ace_u32_t llc;  /**< LLC header: DSAP at byte 0, SSAP at byte 1, Control at byte 2 */
} mesa_ace_frame_llc_t;

/** \brief Frame data for MESA_ACE_TYPE_SNAP */
typedef struct
{
    mesa_ace_u48_t dmac; /**< DMAC */
    mesa_ace_u48_t smac; /**< SMAC */
    mesa_ace_u40_t snap; /**< SNAP header: Organization Code at byte 0, Type at byte 3 */
} mesa_ace_frame_snap_t;

/** \brief Frame data for MESA_ACE_TYPE_ARP */
typedef struct
{
    mesa_ace_u48_t smac;       /**< SMAC */
    mesa_ace_bit_t arp;        /**< Opcode ARP/RARP */
    mesa_ace_bit_t req;        /**< Opcode request/reply */
    mesa_ace_bit_t unknown;    /**< Opcode unknown */
    mesa_ace_bit_t smac_match; /**< Sender MAC matches SMAC */
    mesa_ace_bit_t dmac_match; /**< Target MAC matches DMAC */
    mesa_ace_bit_t length;     /**< Protocol addr. length 4, hardware length 6 */
    mesa_ace_bit_t ip;         /**< Protocol address type IP */
    mesa_ace_bit_t ethernet;   /**< Hardware address type Ethernet */
    mesa_ace_ip_t  sip;        /**< Sender IP address */
    mesa_ace_ip_t  dip;        /**< Target IP address */
} mesa_ace_frame_arp_t;

/** \brief Frame data for MESA_ACE_TYPE_IPV4 */
typedef struct
{
    mesa_ace_bit_t      ttl;            /**< TTL zero */
    mesa_ace_bit_t      fragment;       /**< Fragment */
    mesa_ace_bit_t      options;        /**< Header options */
    mesa_ace_u8_t       ds;             /**< DS field */
    mesa_ace_u8_t       proto;          /**< Protocol */
    mesa_ace_ip_t       sip;            /**< Source IP address */
    mesa_ace_ip_t       dip;            /**< Destination IP address */
    mesa_ace_u48_t      data;           /**< Not UDP/TCP: IP data */
    mesa_ace_udp_tcp_t  sport;          /**< UDP/TCP: Source port */
    mesa_ace_udp_tcp_t  dport;          /**< UDP/TCP: Destination port */
    mesa_ace_bit_t      tcp_fin;        /**< TCP FIN */
    mesa_ace_bit_t      tcp_syn;        /**< TCP SYN */
    mesa_ace_bit_t      tcp_rst;        /**< TCP RST */
    mesa_ace_bit_t      tcp_psh;        /**< TCP PSH */
    mesa_ace_bit_t      tcp_ack;        /**< TCP ACK */
    mesa_ace_bit_t      tcp_urg;        /**< TCP URG */
    mesa_ace_bit_t      sip_eq_dip;     /**< SIP equals DIP  */
    mesa_ace_bit_t      sport_eq_dport; /**< SPORT equals DPORT  */
    mesa_ace_bit_t      seq_zero;       /**< TCP sequence number is zero */
    mesa_ace_ptp_t      ptp;            /**< PTP filtering (overrides sip field) */
    mesa_ace_sip_smac_t sip_smac;       /**< SIP/SMAC matching (overrides sip field) */
} mesa_ace_frame_ipv4_t;

/** \brief Frame data for MESA_ACE_TYPE_IPV6 */
typedef struct
{
    mesa_ace_u8_t      proto;          /**< IPv6 protocol */
    mesa_ace_u128_t    sip;            /**< IPv6 source address (byte 0-7 ignored) */
    mesa_ace_bit_t     ttl;            /**< TTL zero */
    mesa_ace_u8_t      ds;             /**< DS field */
    mesa_ace_u48_t     data;           /**< Not UDP/TCP: IP data */
    mesa_ace_udp_tcp_t sport;          /**< UDP/TCP: Source port */
    mesa_ace_udp_tcp_t dport;          /**< UDP/TCP: Destination port */
    mesa_ace_bit_t     tcp_fin;        /**< TCP FIN */
    mesa_ace_bit_t     tcp_syn;        /**< TCP SYN */
    mesa_ace_bit_t     tcp_rst;        /**< TCP RST */
    mesa_ace_bit_t     tcp_psh;        /**< TCP PSH */
    mesa_ace_bit_t     tcp_ack;        /**< TCP ACK */
    mesa_ace_bit_t     tcp_urg;        /**< TCP URG */
    mesa_ace_bit_t     sip_eq_dip;     /**< SIP equals DIP  */
    mesa_ace_bit_t     sport_eq_dport; /**< SPORT equals DPORT  */
    mesa_ace_bit_t     seq_zero;       /**< TCP sequence number is zero */
    mesa_ace_ptp_t     ptp;            /**< PTP filtering (overrides sip byte 0-3) */
} mesa_ace_frame_ipv6_t;

/** \brief Access Control Entry */
typedef struct
{
    mesa_ace_id_t        id;           /**< ACE ID, must be different from MESA_ACE_ID_LAST */
    uint8_t              lookup       CAP(ACL_KEY_LOOKUP); /**< Lookup, any non-zero value means second lookup */
    mesa_bool_t          isdx_enable  CAP(ACL_KEY_ISDX);   /**< Use VID value for ISDX value */
    mesa_bool_t          isdx_disable CAP(ACL_KEY_ISDX);   /**< Match only frames with ISDX zero */
    mesa_port_list_t     port_list;    /**< Port list */
    mesa_ace_u8_t        policy;       /**< Policy number */
    mesa_ace_type_t      type;         /**< ACE frame type */
    mesa_acl_action_t    action;       /**< ACE action */

    mesa_ace_bit_t       dmac_mc;      /**< Multicast DMAC */
    mesa_ace_bit_t       dmac_bc;      /**< Broadcast DMAC */

    mesa_ace_vlan_t      vlan;         /**< VLAN Tag */

    union
    {
        /* MESA_ACE_TYPE_ANY: No specific fields */
        mesa_ace_frame_etype_t etype;  /**< MESA_ACE_TYPE_ETYPE */
        mesa_ace_frame_llc_t   llc;    /**< MESA_ACE_TYPE_LLC */
        mesa_ace_frame_snap_t  snap;   /**< MESA_ACE_TYPE_SNAP */
        mesa_ace_frame_arp_t   arp;    /**< MESA_ACE_TYPE_ARP */
        mesa_ace_frame_ipv4_t  ipv4;   /**< MESA_ACE_TYPE_IPV4 */
        mesa_ace_frame_ipv6_t  ipv6;   /**< MESA_ACE_TYPE_IPV6 */
    } frame; /**< Frame type specific data */
} mesa_ace_t;

/**
 * \brief Initialize ACE to default values.
 *
 * \param inst [IN]  Target instance reference.
 * \param type [IN]  ACE type.
 * \param ace [OUT]  ACE structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_ace_init(const mesa_inst_t      inst,
                      const mesa_ace_type_t  type,
                      mesa_ace_t             *const ace);


/**
 * \brief Add/modify ACE.
 *
 * \param inst [IN]         Target instance reference.
 * \param ace_id_next [IN]  ACE ID of next entry.
 *                          The ACE will be added before the entry with this ID.
 *                          MESA_ACE_ID_LAST is reserved for inserting last.
 * \param ace [IN]          ACE structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_ace_add(const mesa_inst_t    inst,
                     const mesa_ace_id_t  ace_id_next,
                     const mesa_ace_t     *const ace);



/**
 * \brief Delete ACE.
 *
 * \param inst [IN]    Target instance reference.
 * \param ace_id [IN]  ACE ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_ace_del(const mesa_inst_t    inst,
                     const mesa_ace_id_t  ace_id);



/** \brief ACE hit counter */
typedef uint32_t mesa_ace_counter_t;

/**
 * \brief Get ACE counter.
 *
 * \param inst [IN]      Target instance reference.
 * \param ace_id [IN]    ACE ID.
 * \param counter [OUT]  ACE counter.
 *
 * \return Return code.
 **/
mesa_rc mesa_ace_counter_get(const mesa_inst_t    inst,
                             const mesa_ace_id_t  ace_id,
                             mesa_ace_counter_t   *const counter);


/**
 * \brief Clear ACE counter.
 *
 * \param inst [IN]    Target instance reference.
 * \param ace_id [IN]  ACE ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_ace_counter_clear(const mesa_inst_t    inst,
                               const mesa_ace_id_t  ace_id);

#define MESA_ACE_IDX_NONE 0xffff /**< ACE index not valid */

/** \brief ACE status */
typedef struct {
    uint16_t idx[2]; /**< ACE hardware index table */
} mesa_ace_status_t CAP(ACL_ACE_STATUS);

/**
 * \brief Get ACE status.
 *
 * \param inst [IN]     Target instance reference.
 * \param ace_id [IN]   ACE ID.
 * \param status [OUT]  ACE status.
 *
 * \return Return code.
 **/
mesa_rc mesa_ace_status_get(const mesa_inst_t    inst,
                            const mesa_ace_id_t  ace_id,
                            mesa_ace_status_t    *const status)
    CAP(ACL_ACE_STATUS);

/** \brief Hierarchical ACL type */
typedef enum {
    MESA_HACL_TYPE_IPACL,   /**< Ingress port ACL (I-PACL) */
    MESA_HACL_TYPE_IVACL,   /**< Ingress VLAN ACL (I-VACL) */
    MESA_HACL_TYPE_IRACL,   /**< Ingress router ACL (I-RACL) */
    MESA_HACL_TYPE_ERACL,   /**< Egress router ACL (E-RACL) */
    MESA_HACL_TYPE_EVACL,   /**< Egress VLAN ACL (E-VACL) */
    MESA_HACL_TYPE_EPACL,   /**< Egress port ACL (E-PACL) */
} mesa_hacl_type_t CAP(ACL_HACL);

#define MESA_RLEG_LIST_ARRAY_SIZE 64 /**< Router leg list */

/** \brief Router leg list */
typedef struct {
    uint8_t _private[MESA_RLEG_LIST_ARRAY_SIZE]; /**< Router leg list, access using utilities below */
} mesa_rleg_list_t;

/**
 * \brief Set router leg in router leg list.
 *
 * \param l     [IN]  Router leg list.
 * \param rleg  [IN]  Router leg ID.
 * \param val   [IN]  Value.
 *
 **/
void mesa_rleg_list_set(mesa_rleg_list_t *l, mesa_l3_rleg_id_t rleg, mesa_bool_t val);

/**
 * \brief Get router leg value from router leg list.
 *
 * \param l     [IN]  Router leg list.
 * \param rleg  [IN]  Router leg ID.
 *
 * \return TRUE if router leg is included in list.
 *
 **/
mesa_bool_t mesa_rleg_list_get(const mesa_rleg_list_t *l, mesa_l3_rleg_id_t rleg);

/** \brief Frame data for MESA_ACE_TYPE_ETYPE */
typedef struct {
    mesa_ace_u16_t etype; /**< Ethernet Type value */
    mesa_ace_u16_t data;  /**< MAC data */
} mesa_hace_frame_etype_t CAP(ACL_HACL);

/** \brief Frame data for MESA_ACE_TYPE_LLC */
typedef struct {
    mesa_ace_u32_t llc;  /**< LLC header: DSAP at byte 0, SSAP at byte 1, Control at byte 2 */
} mesa_hace_frame_llc_t CAP(ACL_HACL);

/** \brief Frame data for MESA_ACE_TYPE_SNAP */
typedef struct {
    mesa_ace_u40_t snap; /**< SNAP header: Organization Code at byte 0, Type at byte 3 */
} mesa_hace_frame_snap_t CAP(ACL_HACL);

/** \brief Frame data for MESA_ACE_TYPE_ARP */
typedef struct {
    mesa_ace_bit_t arp;        /**< Opcode ARP/RARP */
    mesa_ace_bit_t req;        /**< Opcode request/reply */
    mesa_ace_bit_t unknown;    /**< Opcode unknown */
    mesa_ace_bit_t smac_match; /**< Sender MAC matches SMAC */
    mesa_ace_bit_t dmac_match; /**< Target MAC matches DMAC */
    mesa_ace_bit_t length;     /**< Protocol addr. length 4, hardware length 6 */
    mesa_ace_bit_t ip;         /**< Protocol address type IP */
    mesa_ace_bit_t ethernet;   /**< Hardware address type Ethernet */
    mesa_ace_ip_t  sip;        /**< Sender IP address */
    mesa_ace_ip_t  dip;        /**< Target IP address */
} mesa_hace_frame_arp_t CAP(ACL_HACL);

/** \brief Frame data for MESA_ACE_TYPE_IPV4 */
typedef struct
{
    mesa_ace_bit_t      ttl;      /**< TTL zero */
    mesa_ace_bit_t      fragment; /**< Fragment */
    mesa_ace_bit_t      options;  /**< Header options */
    mesa_ace_u8_t       ds;       /**< DS field */
    mesa_ace_u8_t       proto;    /**< Protocol */
    mesa_ace_ip_t       sip;      /**< Source IP address */
    mesa_ace_ip_t       dip;      /**< Destination IP address */
    mesa_ace_u48_t      data;     /**< Not UDP/TCP: IP data */
    mesa_ace_udp_tcp_t  sport;    /**< UDP/TCP: Source port */
    mesa_ace_udp_tcp_t  dport;    /**< UDP/TCP: Destination port */
    mesa_ace_bit_t      tcp_fin;  /**< TCP FIN */
    mesa_ace_bit_t      tcp_syn;  /**< TCP SYN */
    mesa_ace_bit_t      tcp_rst;  /**< TCP RST */
    mesa_ace_bit_t      tcp_psh;  /**< TCP PSH */
    mesa_ace_bit_t      tcp_ack;  /**< TCP ACK */
    mesa_ace_bit_t      tcp_urg;  /**< TCP URG */
    mesa_ace_sip_smac_t sip_smac; /**< SIP/SMAC matching (overrides sip field) */
} mesa_hace_frame_ipv4_t CAP(ACL_HACL);

/** \brief Frame data for MESA_ACE_TYPE_IPV6 */
typedef struct
{
    mesa_ace_bit_t     ttl;     /**< TTL zero */
    mesa_ace_u8_t      ds;      /**< DS field */
    mesa_ace_u8_t      proto;   /**< IPv6 protocol */
    mesa_ace_u128_t    sip;     /**< IPv6 source address */
    mesa_ace_u128_t    dip;     /**< IPv6 destination address */
    mesa_ace_u48_t     data;    /**< Not UDP/TCP: IP data */
    mesa_ace_udp_tcp_t sport;   /**< UDP/TCP: Source port */
    mesa_ace_udp_tcp_t dport;   /**< UDP/TCP: Destination port */
    mesa_ace_bit_t     tcp_fin; /**< TCP FIN */
    mesa_ace_bit_t     tcp_syn; /**< TCP SYN */
    mesa_ace_bit_t     tcp_rst; /**< TCP RST */
    mesa_ace_bit_t     tcp_psh; /**< TCP PSH */
    mesa_ace_bit_t     tcp_ack; /**< TCP ACK */
    mesa_ace_bit_t     tcp_urg; /**< TCP URG */
} mesa_hace_frame_ipv6_t CAP(ACL_HACL);

/** \brief Hierarchical ACL key */
typedef struct {
    mesa_port_list_t        port_list; /**< Ingress/egress port list (unused for RACLs) */
    mesa_rleg_list_t        rleg_list; /**< Ingress/egress router leg list (RACLs only) */
    mesa_ace_u8_t           policy;    /**< Policy number */
    mesa_ace_type_t         type;      /**< ACE frame type */
    mesa_ace_vlan_t         vlan;      /**< Classified VLAN tag values (unused for RACLs) */
    mesa_ace_ptp_t          ptp;       /**< PTP header filtering for EType/IPv4/IPv6 (unused for RACLs) */
    mesa_ace_bit_t          dmac_mc;   /**< Multicast DMAC (unused for RACLs) */
    mesa_ace_bit_t          dmac_bc;   /**< Broadcast DMAC (unused for RACLs) */
    mesa_ace_u48_t          dmac;      /**< DMAC (unused for RACLs) */
    mesa_ace_u48_t          smac;      /**< SMAC (unused for RACLs) */
    mesa_hace_frame_etype_t etype;     /**< MESA_ACE_TYPE_ETYPE (unused for RACLs) */
    mesa_hace_frame_llc_t   llc;       /**< MESA_ACE_TYPE_LLC (unused for RACLs) */
    mesa_hace_frame_snap_t  snap;      /**< MESA_ACE_TYPE_SNAP (unused for RACLs) */
    mesa_hace_frame_arp_t   arp;       /**< MESA_ACE_TYPE_ARP (unused for VACLS/RACLs) */
    mesa_hace_frame_ipv4_t  ipv4;      /**< MESA_ACE_TYPE_IPV4 (unused for VACLs) */
    mesa_hace_frame_ipv6_t  ipv6;      /**< MESA_ACE_TYPE_IPV6 (unused for VACLs) */
} mesa_hace_key_t CAP(ACL_HACL);

/** \brief Hierarchical ACL action */
typedef struct {
    mesa_acl_port_action_t     port_action; /**< Port action */
    mesa_port_list_t           port_list;   /**< Egress port list (I-PACL/I-VACL only) */
    mesa_bool_t                cpu;         /**< Forward to CPU (I-PACL/I-VACL only) */
    mesa_bool_t                cpu_once;    /**< Only first frame forwarded to CPU (I-PACL/I-VACL only) */
    mesa_packet_rx_queue_t     cpu_queue;   /**< CPU queue (I-PACL/I-VACL only) */
    mesa_bool_t                police;      /**< Enable policer (I-PACL/I-VACL only) */
    mesa_acl_policer_no_t      policer_no;  /**< Policer number (I-PACL/I-VACL only) */
    mesa_bool_t                mirror;      /**< Enable mirroring (I-PACL/I-VACL only) */
    mesa_acl_ptp_action_t      ptp_action;  /**< PTP action (I-PACL/I-VACL only) */
    mesa_acl_ptp_action_conf_t ptp;         /**< PTP configuration (I-PACL/I-VACL only) */
    mesa_acl_addr_action_t     addr;        /**< Address update configuration (I-PACL/I-VACL only) */
    mesa_bool_t                ifh_flag;    /**< Control one target specific bit in IFH (I-PACL/I-VACL only) */
} mesa_hacl_action_t CAP(ACL_HACL);

/** \brief Hierarchical ACL Entry */
typedef struct {
    mesa_ace_id_t      id;     /**< Entry ID */
    mesa_hace_key_t    key;    /**< ACE key */
    mesa_hacl_action_t action; /**< ACE action */
} mesa_hace_t CAP(ACL_HACL);

/**
 * \brief Initialize Hierarchical ACE to default values.
 *
 * \param inst [IN]   Target instance reference.
 * \param type [IN]   ACE type.
 * \param hace [OUT]  ACE structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_hace_init(const mesa_inst_t     inst,
                       const mesa_ace_type_t type,
                       mesa_hace_t           *const hace)
    CAP(ACL_HACL);

/**
 * \brief Add/modify Hierarchical ACE.
 *
 * \param inst [IN]         Target instance reference.
 * \param type [IN]         Hierarcical ACL type.
 * \param ace_id_next [IN]  ACE ID of next entry.
 *                          The ACE will be added before the entry with this ID.
 *                          MESA_ACE_ID_LAST is reserved for inserting last.
 * \param hace [IN]         ACE structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_hace_add(const mesa_inst_t      inst,
                      const mesa_hacl_type_t type,
                      const mesa_ace_id_t    ace_id_next,
                      const mesa_hace_t      *const hace)
    CAP(ACL_HACL);

/**
 * \brief Delete Hierarchical ACE.
 *
 * \param inst [IN]    Target instance reference.
 * \param type [IN]    Hierarcical ACL type.
 * \param ace_id [IN]  ACE ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_hace_del(const mesa_inst_t      inst,
                      const mesa_hacl_type_t type,
                      const mesa_ace_id_t    ace_id)
    CAP(ACL_HACL);

/**
 * \brief Get Hierarchical ACE counter.
 *
 * \param inst [IN]      Target instance reference.
 * \param type [IN]      Hierarcical ACL type.
 * \param ace_id [IN]    ACE ID.
 * \param counter [OUT]  ACE counter.
 *
 * \return Return code.
 **/
mesa_rc mesa_hace_counter_get(const mesa_inst_t      inst,
                              const mesa_hacl_type_t type,
                              const mesa_ace_id_t    ace_id,
                              mesa_ace_counter_t     *const counter)
    CAP(ACL_HACL);

/**
 * \brief Clear Hierarchical ACE counter.
 *
 * \param inst [IN]    Target instance reference.
 * \param type [IN]    Hierarcical ACL type.
 * \param ace_id [IN]  ACE ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_hace_counter_clear(const mesa_inst_t      inst,
                                const mesa_hacl_type_t type,
                                const mesa_ace_id_t    ace_id)
    CAP(ACL_HACL);

#include <mscc/ethernet/switch/api/hdr_end.h>
#endif // _MSCC_ETHERNET_SWITCH_API_SECURITY_
