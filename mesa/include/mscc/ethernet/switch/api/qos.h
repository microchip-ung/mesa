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

#ifndef _MSCC_ETHERNET_SWITCH_API_QOS_
#define _MSCC_ETHERNET_SWITCH_API_QOS_

#include <mscc/ethernet/switch/api/types.h>
#include <mscc/ethernet/switch/api/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

// QoS configuration per (DSCP, DPL)
typedef struct {
    mesa_dscp_t dscp; /**< Egress: Remap one DSCP to another */
} mesa_qos_dscp_dpl_conf_t;

mesa_rc mesa_qos_dscp_dpl_conf_get(const mesa_inst_t        inst,
                                   const uint32_t           dpl_cnt,
                                   mesa_qos_dscp_dpl_conf_t *const conf);

mesa_rc mesa_qos_dscp_dpl_conf_set(const mesa_inst_t              inst,
                                   const uint32_t                 dpl_cnt,
                                   const mesa_qos_dscp_dpl_conf_t *const conf);

// QoS configuration per DPL
typedef struct {
    mesa_dscp_t dscp[MESA_PRIO_ARRAY_SIZE]; /**< Ingress: Mapping from QoS class and DPL to DSCP */
} mesa_qos_dpl_conf_t;

mesa_rc mesa_qos_dpl_conf_get(const mesa_inst_t   inst,
                              const uint32_t      dpl_cnt,
                              mesa_qos_dpl_conf_t *const conf);

mesa_rc mesa_qos_dpl_conf_set(const mesa_inst_t         inst,
                              const uint32_t            dpl_cnt,
                              const mesa_qos_dpl_conf_t *const conf);

/**
 * \brief Select if max means max drop probability or max fill level
 **/
typedef enum {
    MESA_WRED_MAX_DP, /**< Unit for max is drop probability */
    MESA_WRED_MAX_FL  /**< Unit for max is fill level */
} mesa_wred_max_t CAP(QOS_WRED);

/**
 * \brief Weighted Random Early Detection configuration
 **/
typedef struct {
    mesa_bool_t     enable;   /**< Enable/disable RED */
    mesa_pct_t      min_fl;   /**< Minimum fill level */
    mesa_pct_t      max;      /**< Maximum drop probability or fill level - selected by max_unit */
    mesa_wred_max_t max_unit; /**< Selects the unit for max */
} mesa_wred_conf_t CAP(QOS_WRED);

// QoS configuration per (DPL, GROUP)
typedef struct {
    mesa_wred_conf_t wred[MESA_QUEUE_ARRAY_SIZE] CAP(QOS_WRED); /**< Random Early Detection */
} mesa_qos_dpl_group_conf_t;

mesa_rc mesa_qos_dpl_group_conf_get(const mesa_inst_t         inst,
                                    const uint32_t            dpl_cnt,
                                    const uint32_t            group_cnt,
                                    mesa_qos_dpl_group_conf_t *const conf);

mesa_rc mesa_qos_dpl_group_conf_set(const mesa_inst_t               inst,
                                    const uint32_t                  dpl_cnt,
                                    const uint32_t                  group_cnt,
                                    const mesa_qos_dpl_group_conf_t *const conf);

// QoS configuration per DSCP
typedef struct {
    mesa_bool_t     trust;  /**< Ingress: Only trusted DSCP values are used for QOS class and DP level classification  */
    mesa_prio_t     prio;   /**< Ingress: Mapping from DSCP value to QOS class  */
    mesa_dp_level_t dpl;    /**< Ingress: Mapping from DSCP value to DP level */
    mesa_bool_t     remark; /**< Ingress: DSCP remarking enable. Used when port.dscp_mode = MESA_DSCP_MODE_SEL */
    mesa_dscp_t     dscp;   /**< Ingress: Translated DSCP value. Used when port.dscp_translate = TRUE) */
} mesa_qos_dscp_conf_t;

// QoS storm policer configuration
typedef struct {
    mesa_packet_rate_t        rate;       /**< Policer rate */
    mesa_bool_t               frame_rate; /**< FALSE: Unit is kbps. TRUE: Unit is fps */
    mesa_storm_policer_mode_t mode;       /**< Unicast packet storm policer mode */
} mesa_qos_storm_policer_conf_t;

/**
 * \brief All parameters below are defined per chip
 **/
typedef struct {
    mesa_prio_t                   prios;      /**< Number of priorities (1/2/4/8) */
    mesa_qos_dscp_conf_t          dscp[64];   /**< DSCP configuration */
    mesa_qos_storm_policer_conf_t policer_uc; /**< Unicast storm policer */
    mesa_qos_storm_policer_conf_t policer_mc; /**< Multicast storm policer */
    mesa_qos_storm_policer_conf_t policer_bc; /**< Broadcast storm policer */
} mesa_qos_conf_t;

/**
 * \brief Get QoS setup for switch.
 *
 * \param inst [IN]   Target instance reference.
 * \param conf [OUT]  QoS setup structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_conf_get(const mesa_inst_t inst,
                          mesa_qos_conf_t   *const conf);

/**
 * \brief Set QoS setup for switch.
 *
 * \param inst [IN]  Target instance reference.
 * \param conf [IN]  QoS setup structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_conf_set(const mesa_inst_t     inst,
                          const mesa_qos_conf_t *const conf);

/** \brief QoS status  **/
typedef struct {
    mesa_event_t        storm; /**< Storm policing active since last call. */
} mesa_qos_status_t;

/**
* \brief Get QoS status for switch.
*
* \param inst [IN]     Target instance reference.
* \param status [OUT]  QoS status structure.
*
* \return Return code.
**/
mesa_rc mesa_qos_status_get(const mesa_inst_t inst,
                            mesa_qos_status_t *const status);

/**
 * \brief Policer
 **/
typedef struct {
    mesa_burst_level_t level;       /**< Burst level */
    mesa_bitrate_t     rate;        /**< Maximum rate */
} mesa_policer_t;

/** \brief Dual leaky buckets policer configuration */
typedef struct {
    mesa_policer_type_t type;      /**< Policer type */
    mesa_bool_t         enable;    /**< Enable/disable policer */
    mesa_bool_t         cm CAP(QOS_DLB_CM); /**< Colour Mode (TRUE means colour aware) */
    mesa_bool_t         cf;        /**< Coupling Flag */
    mesa_bool_t         line_rate; /**< Line rate policing (default is data rate policing) */
    mesa_bitrate_t      cir;       /**< Committed Information Rate */
    mesa_burst_level_t  cbs;       /**< Committed Burst Size */
    mesa_bitrate_t      eir;       /**< Excess Information Rate */
    mesa_burst_level_t  ebs;       /**< Excess Burst Size */
} mesa_dlb_policer_conf_t;

/**
 * \brief Shaper Accounting Mode
 **/
typedef enum {
    MESA_SHAPER_MODE_LINE, /**< Use line-rate for the shaper */
    MESA_SHAPER_MODE_DATA  /**< Use data-rate for the shaper */
} mesa_shaper_mode_t CAP(QOS_EGRESS_SHAPERS_RT);

/**
 * \brief Shaper
 **/
typedef struct {
    mesa_burst_level_t level;          /**< CBS (Committed Burst Size). Unit: bytes */
    mesa_bitrate_t     rate;           /**< CIR (Committed Information Rate). Unit: kbps. Use MESA_BITRATE_DISABLED to disable shaper */
    mesa_burst_level_t ebs CAP(QOS_EGRESS_SHAPERS_DLB); /**< EBS (Excess Burst Size).  Unit: bytes */
    mesa_bitrate_t     eir CAP(QOS_EGRESS_SHAPERS_DLB); /**< EIR (Excess Information Rate). Unit: kbps. Use MESA_BITRATE_DISABLED to disable DLB */
    mesa_shaper_mode_t mode CAP(QOS_EGRESS_SHAPERS_RT); /**< RT (Rate type) */
} mesa_shaper_t;

// QoS configuration per (port, policer)
typedef struct {
    mesa_policer_t  policer;     /**< Basic policer config */
    mesa_bool_t     frame_rate;  /**< Measure rates in frames per seconds instead of bits per second */
    mesa_dp_level_t dp_bypass_level CAP(QOS_PORT_POLICER_EXT_DPBL); /**< Drop Predence bypass level */

    mesa_bool_t known_unicast         CAP(QOS_PORT_POLICER_EXT_TTM); /**< Known unicast frames are policed */
    mesa_bool_t known_multicast       CAP(QOS_PORT_POLICER_EXT_TTM); /**< Known multicast frames are policed */
    mesa_bool_t known_broadcast       CAP(QOS_PORT_POLICER_EXT_TTM); /**< Known broadcast frames are policed */
    mesa_bool_t unknown_unicast       CAP(QOS_PORT_POLICER_EXT_TTM); /**< Unknown unicast frames are policed */
    mesa_bool_t unknown_multicast     CAP(QOS_PORT_POLICER_EXT_TTM); /**< Unknown multicast frames are policed */
    mesa_bool_t unknown_broadcast     CAP(QOS_PORT_POLICER_EXT_TTM); /**< Unknown broadcast frames are policed */
    mesa_bool_t learning              CAP(QOS_PORT_POLICER_EXT_TTM); /**< Learning frames are policed */
    mesa_bool_t limit_noncpu_traffic  CAP(QOS_PORT_POLICER_EXT_TTM); /**< Remove the front ports from the destination set for a policed frame */
    mesa_bool_t limit_cpu_traffic     CAP(QOS_PORT_POLICER_EXT_TTM); /**< Remove the CPU ports from the destination set for a policed frame */

    mesa_bool_t flow_control;         /**< Flow control is enabled */
} mesa_qos_port_policer_conf_t;

mesa_rc mesa_qos_port_policer_conf_get(const mesa_inst_t            inst,
                                       const mesa_port_no_t         port_no,
                                       const uint32_t               cnt,
                                       mesa_qos_port_policer_conf_t *const conf);

mesa_rc mesa_qos_port_policer_conf_set(const mesa_inst_t                  inst,
                                       const mesa_port_no_t               port_no,
                                       const uint32_t                     cnt,
                                       const mesa_qos_port_policer_conf_t *const conf);

// QoS configuration per (port, queue)
typedef struct {
    mesa_policer_t policer; /**< Ingress queue policer */
    mesa_shaper_t  shaper;  /**< Egress queue shapers */
    mesa_pct_t     pct;     /**< Queue percentage */
    mesa_bool_t    excess_enable           CAP(QOS_EGRESS_QUEUE_SHAPERS_EB);  /**< Allow this queue to use excess bandwidth */
    mesa_bool_t    cut_through_enable      CAP(QOS_EGRESS_QUEUE_CUT_THROUGH); /**< Allow this queue to use cut through feature */
} mesa_qos_port_queue_conf_t;

/** \brief Tag Remark Mode */
typedef enum {
    MESA_TAG_REMARK_MODE_CLASSIFIED = 0, /**< Use classified PCP/DEI values */
    MESA_TAG_REMARK_MODE_DEFAULT    = 2, /**< Use default (configured) PCP/DEI values */
    MESA_TAG_REMARK_MODE_MAPPED     = 3  /**< Use mapped versions of classified QOS class and DP level */
} mesa_tag_remark_mode_t;

/**
 * \brief DSCP mode for ingress port
 **/
typedef enum {
    MESA_DSCP_MODE_NONE,   /**< DSCP not remarked */
    MESA_DSCP_MODE_ZERO,   /**< DSCP value zero remarked */
    MESA_DSCP_MODE_SEL,    /**< DSCP values selected above (dscp_remark) are remarked */
    MESA_DSCP_MODE_ALL     /**< DSCP remarked for all values */
} mesa_dscp_mode_t;

/**
 * \brief DSCP mode for egress port
 **/
typedef enum {
    MESA_DSCP_EMODE_DISABLE,   /**< DSCP not remarked */
    MESA_DSCP_EMODE_REMARK,    /**< DSCP remarked with DSCP value from analyzer */
    MESA_DSCP_EMODE_REMAP,     /**< DSCP remarked with DSCP value from analyzer remapped through global remap table  */
    MESA_DSCP_EMODE_REMAP_DPA CAP(QOS_DSCP_REMARK_DP_AWARE) /**< DSCP remarked with DSCP value from analyzer remapped through global remap dp aware tables */
} mesa_dscp_emode_t;

// QoS configuration per (PORT, DPL)
typedef struct {
    mesa_tagprio_t pcp[MESA_PRIO_ARRAY_SIZE]; /**< Egress mapping from QOS class and (1 bit) DP level to PCP */
    mesa_dei_t     dei[MESA_PRIO_ARRAY_SIZE]; /**< Egress mapping from QOS class and (1 bit) DP level to DEI */
} mesa_qos_port_dpl_conf_t;

mesa_rc mesa_qos_port_dpl_conf_get(const mesa_inst_t        inst,
                                   const mesa_port_no_t     port_no,
                                   const uint32_t           dpl_cnt,
                                   mesa_qos_port_dpl_conf_t *const conf);

mesa_rc mesa_qos_port_dpl_conf_set(const mesa_inst_t              inst,
                                   const mesa_port_no_t           port_no,
                                   const uint32_t                 dpl_cnt,
                                   const mesa_qos_port_dpl_conf_t *const conf);

// QoS configuration per (PORT, PCP, DEI)
typedef struct {
    mesa_prio_t     prio; /**< Ingress mapping for tagged frames from PCP and DEI to QOS class  */
    mesa_dp_level_t dpl;  /**< Ingress mapping for tagged frames from PCP and DEI to DP level */
} mesa_qos_port_pcp_dei_conf_t;

// QoS VLAN tag configuration per PORT
typedef struct {
    mesa_tagprio_t         pcp;          /**< Default ingress PCP */
    mesa_dei_t             dei;          /**< Default ingress DEI */
    mesa_bool_t            class_enable; /**< Ingress classification of QoS class and DP level based PCP and DEI */
    mesa_qos_port_pcp_dei_conf_t pcp_dei_map[MESA_PCP_ARRAY_SIZE][MESA_DEI_ARRAY_SIZE]; /**< Ingress mapping for tagged frames from PCP and DEI */
    mesa_tag_remark_mode_t remark_mode;  /**< Egress tag remark mode */
    mesa_tagprio_t         egress_pcp;   /**< Default egress PCP */
    mesa_dei_t             egress_dei;   /**< Default egress DEI */
} mesa_qos_port_tag_conf_t;

// QoS DSCP configuration per PORT
typedef struct {
    mesa_bool_t       class_enable; /**< Ingress classification of QoS class and DP level based on DSCP */
    mesa_dscp_mode_t  mode;         /**< Ingress DSCP mode */
    mesa_dscp_emode_t emode;        /**< Egress DSCP mode */
    mesa_bool_t       translate;    /**< Ingress: Translate DSCP value before use */
} mesa_qos_port_dscp_conf_t;

/** \brief QoS setup per port **/
typedef struct {
    mesa_shaper_t              shaper;       /**< Egress port shaper */
    mesa_prio_t                default_prio; /**< Default port priority (QoS class) */
    mesa_dp_level_t            default_dpl;  /**< Default Ingress Drop Precedence level */
    mesa_qos_port_tag_conf_t   tag;          /**< VLAN tag configuration */
    mesa_qos_port_dscp_conf_t  dscp;         /**< DSCP configuration */
    mesa_bool_t                dwrr_enable;                          /**< Enable Weighted fairness queueing */
    uint8_t                    dwrr_cnt CAP(QOS_SCHEDULER_CNT_DWRR); /**< Number of queues, starting from queue 0, running in DWRR mode */
    mesa_bool_t                dmac_dip CAP(QOS_QCL_DMAC_DIP);       /**< Enable DMAC/DIP matching in QCLs (default SMAC/SIP) */
    mesa_vcap_key_type_t       key_type CAP(QOS_QCL_KEY_TYPE);       /**< Key type for received frames */
    mesa_wred_group_t          wred_group CAP(QOS_WRED_GROUP_CNT);   /**< WRED group number - zero based */
    mesa_cosid_t               cosid CAP(QOS_COSID_CLASSIFICATION);  /**< Default COSID */
    mesa_qos_ingress_map_id_t  ingress_map CAP(QOS_INGRESS_MAP_CNT); /**< Ingress map to use for classification. Default is none. */
    mesa_qos_egress_map_id_t   egress_map CAP(QOS_EGRESS_MAP_CNT);   /**< Egress map to use for remarking. Default is none. */
    mesa_qos_port_queue_conf_t queue[MESA_QUEUE_ARRAY_SIZE];         /**< Queue configuration */
} mesa_qos_port_conf_t;

/**
 * \brief Get QoS setup for port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    QoS setup structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_port_conf_get(const mesa_inst_t    inst,
                               const mesa_port_no_t port_no,
                               mesa_qos_port_conf_t *const conf);

/**
 * \brief Set QoS setup for port.
 *
 * \param inst [IN]    Target instance reference.
 * \param port_no [IN] Port number.
 * \param conf [IN]    QoS setup structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_port_conf_set(const mesa_inst_t          inst,
                               const mesa_port_no_t       port_no,
                               const mesa_qos_port_conf_t *const conf);

#define MESA_QCE_ID_LAST 0 /**< Special value used to add last in list */

/** \brief QoS Control Entry type */
typedef enum {
    MESA_QCE_TYPE_ANY,     /**< Any frame type */
    MESA_QCE_TYPE_ETYPE,   /**< Ethernet Type */
    MESA_QCE_TYPE_LLC,     /**< LLC */
    MESA_QCE_TYPE_SNAP,    /**< SNAP */
    MESA_QCE_TYPE_IPV4,    /**< IPv4 */
    MESA_QCE_TYPE_IPV6     /**< IPv6 */
} mesa_qce_type_t;

/** \brief QCE MAC information */
typedef struct {
    mesa_vcap_bit_t dmac_mc; /**< Multicast DMAC */
    mesa_vcap_bit_t dmac_bc; /**< Broadcast DMAC */
    mesa_vcap_u48_t dmac CAP(QOS_QCL_KEY_DMAC); /**< DMAC - Serval: key_type = mac_ip_addr */
    mesa_vcap_u48_t smac;    /**< SMAC - Only the 24 most significant bits (OUI) are supported on Jaguar1, rest are wildcards */
} mesa_qce_mac_t;

/** \brief QCE tag information */
typedef struct {
    mesa_vcap_vr_t  vid;    /**< VLAN ID (12 bit) */
    mesa_vcap_u8_t  pcp;    /**< PCP (3 bit) */
    mesa_vcap_bit_t dei;    /**< DEI */
    mesa_vcap_bit_t tagged; /**< Tagged/untagged frame */
    mesa_vcap_bit_t s_tag;  /**< S-tagged/C-tagged frame */
} mesa_qce_tag_t;

/** \brief Frame data for MESA_QCE_TYPE_ETYPE */
typedef struct {
    mesa_vcap_u16_t etype; /**< Ethernet Type value */
    mesa_vcap_u32_t data;  /**< MAC data */
} mesa_qce_frame_etype_t;

/** \brief Frame data for MESA_QCE_TYPE_LLC */
typedef struct {
    mesa_vcap_u48_t data; /**< Data */
} mesa_qce_frame_llc_t;

/** \brief Frame data for MESA_QCE_TYPE_SNAP */
typedef struct {
    mesa_vcap_u48_t data; /**< Data */
} mesa_qce_frame_snap_t;

/** \brief Frame data for MESA_QCE_TYPE_IPV4 */
typedef struct {
    mesa_vcap_bit_t fragment; /**< Fragment */
    mesa_vcap_vr_t  dscp;     /**< DSCP field (6 bit) */
    mesa_vcap_u8_t  proto;    /**< Protocol */
    mesa_vcap_ip_t  sip;      /**< Source IP address - Serval: key_type = normal, ip_addr and mac_ip_addr */
    mesa_vcap_ip_t  dip CAP(QOS_QCL_KEY_DIP); /**< Destination IP address - Serval: key_type = ip_addr and mac_ip_addr */
    mesa_vcap_vr_t  sport;    /**< UDP/TCP: Source port - Serval: key_type = normal, ip_addr and mac_ip_addr */
    mesa_vcap_vr_t  dport;    /**< UDP/TCP: Destination port - Serval: key_type = double_tag, ip_addr and mac_ip_addr */
} mesa_qce_frame_ipv4_t;

/** \brief Frame data for MESA_QCE_TYPE_IPV6 */
typedef struct {
    mesa_vcap_vr_t   dscp;    /**< DSCP field (6 bit) */
    mesa_vcap_u8_t   proto;   /**< Protocol */
    mesa_vcap_u128_t sip;     /**< Source IP address (32 LSB on L26 and J1, 64 LSB on Serval when key_type = mac_ip_addr) */
    mesa_vcap_u128_t dip CAP(QOS_QCL_KEY_DIP); /**< Destination IP address - 64 LSB on Serval when key_type = mac_ip_addr */
    mesa_vcap_vr_t   sport;   /**< UDP/TCP: Source port - Serval: key_type = normal, ip_addr and mac_ip_addr */
    mesa_vcap_vr_t   dport;   /**< UDP/TCP: Destination port - Serval: key_type = double_tag, ip_addr and mac_ip_addr */
} mesa_qce_frame_ipv6_t;

/**
 * \brief QCE key
 **/
typedef struct {
    mesa_port_list_t port_list;                       /**< Port list */
    mesa_qce_mac_t   mac;                             /**< MAC */
    mesa_qce_tag_t   tag;                             /**< Tag */
    mesa_qce_tag_t   inner_tag CAP(QOS_QCL_KEY_INNER_TAG); /**< Inner tag */
    mesa_qce_type_t  type;                            /**< Frame type */

    union {
        /* MESA_QCE_TYPE_ANY: No specific fields */
        mesa_qce_frame_etype_t etype; /**< MESA_QCE_TYPE_ETYPE */
        mesa_qce_frame_llc_t   llc;   /**< MESA_QCE_TYPE_LLC */
        mesa_qce_frame_snap_t  snap;  /**< MESA_QCE_TYPE_SNAP */
        mesa_qce_frame_ipv4_t  ipv4;  /**< MESA_QCE_TYPE_IPV4 */
        mesa_qce_frame_ipv6_t  ipv6;  /**< MESA_QCE_TYPE_IPV6 */
    } frame; /**< Frame type specific data */
} mesa_qce_key_t;

/**
 * \brief QCE action
 **/
typedef struct {
    mesa_bool_t               prio_enable;      /**< Enable priority classification */
    mesa_prio_t               prio;             /**< Priority value */
    mesa_bool_t               dp_enable;        /**< Enable DP classification */
    mesa_dp_level_t           dp;               /**< DP value */
    mesa_bool_t               dscp_enable;      /**< Enable DSCP classification */
    mesa_dscp_t               dscp;             /**< DSCP value */
    mesa_bool_t               pcp_dei_enable;   /**< Enable PCP and DEI classification */
    mesa_tagprio_t            pcp;              /**< PCP value */
    mesa_dei_t                dei;              /**< DEI value */
    mesa_bool_t               policy_no_enable; /**< Enable ACL policy classification */
    mesa_acl_policy_no_t      policy_no;        /**< ACL policy number */
    mesa_bool_t               map_id_enable CAP(QOS_INGRESS_MAP_CNT); /**< Enable classification via ingress map */
    mesa_qos_ingress_map_id_t map_id        CAP(QOS_INGRESS_MAP_CNT); /**< Ingress map to use for classification */
} mesa_qce_action_t;

/**
 * \brief QoS Control Entry
 **/
typedef struct {
    mesa_qce_id_t     id;         /**< Entry ID */
    mesa_qce_key_t    key;        /**< QCE key */
    mesa_qce_action_t action;     /**< QCE action */
} mesa_qce_t;

/**
 * \brief Initialize QCE to default values.
 *
 * \param inst [IN]  Target instance reference.
 * \param type [IN]  QCE type.
 * \param qce [OUT]  QCE structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_qce_init(const mesa_inst_t     inst,
                      const mesa_qce_type_t type,
                      mesa_qce_t            *const qce);

/**
 * \brief Add QCE to QCL.
 *
 * \param inst [IN]    Target instance reference.
 * \param qcl_id [IN]  QCL ID.
 * \param qce_id [IN]  QCE ID. The QCE will be added before the entry with this ID.
 *                     MESA_QCE_ID_LAST is reserved for inserting last.
 * \param qce [IN]     QCE structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_qce_add(const mesa_inst_t   inst,
                     const mesa_qce_id_t qce_id,
                     const mesa_qce_t    *const qce);

/**
 * \brief Delete QCE from QCL.
 *
 * \param inst [IN]    Target instance reference.
 * \param qcl_id [IN]  QCL ID.
 * \param qce_id [IN]  QCE ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_qce_del(const mesa_inst_t   inst,
                     const mesa_qce_id_t qce_id);

/** \brief Key that determines what to match */
typedef enum {
    MESA_QOS_INGRESS_MAP_KEY_PCP,                   /**< Use PCP for tagged frames and none for the rest */
    MESA_QOS_INGRESS_MAP_KEY_PCP_DEI,               /**< Use PCP/DEI for tagged frames and none for the rest */
    MESA_QOS_INGRESS_MAP_KEY_DSCP,                  /**< Use DSCP as key for IP frames and none for the rest */
    MESA_QOS_INGRESS_MAP_KEY_DSCP_PCP_DEI,          /**< Use DSCP as key for IP frames, PCP/DEI for tagged frames and none for the rest */
    MESA_QOS_INGRESS_MAP_KEY_MPLS_TC                /**< Use MPLS TC as key for MPLS frames and none for the rest */
} mesa_qos_ingress_map_key_t CAP(QOS_INGRESS_MAP_CNT);

/** \brief Actions that can be applied to classified values if the entry is matched */
typedef struct {
    mesa_bool_t cos;                                /**< If TRUE, then replace the classified COS */
    mesa_bool_t dpl;                                /**< If TRUE, then replace the classified DPL */
    mesa_bool_t pcp;                                /**< If TRUE, then replace the classified PCP */
    mesa_bool_t dei;                                /**< If TRUE, then replace the classified DEI */
    mesa_bool_t dscp;                               /**< If TRUE, then replace the classified DSCP */
    mesa_bool_t cosid;                              /**< If TRUE, then replace the classified COS ID */
    mesa_bool_t path;                               /**< If TRUE, then replace the classified path COS ID */
    mesa_bool_t mpls_tc;                            /**< If TRUE, then replace the classified MPLS TC */
} mesa_qos_ingress_map_action_t CAP(QOS_INGRESS_MAP_CNT);

/** \brief Mapped values that can be applied to classified values if the entry is matched */
typedef struct {
    mesa_cos_t     cos;                             /**< The classified COS is set to cos if action.cos is TRUE */
    mesa_dpl_t     dpl;                             /**< The classified DPL is set to dpl if action.dpl is TRUE */
    mesa_pcp_t     pcp;                             /**< The classified PCP is set to pcp if action.pcp is TRUE */
    mesa_dei_t     dei;                             /**< The classified DEI is set to dei if action.dei is TRUE */
    mesa_dscp_t    dscp;                            /**< The classified DSCP is set to dscp if action.dscp is TRUE */
    mesa_cosid_t   cosid;                           /**< The classified COS ID is set to cosid if action.cosid is TRUE */
    mesa_cosid_t   path_cosid;                      /**< Path COS ID value used by OAM MEP if action.path is TRUE */
    mesa_mpls_tc_t mpls_tc;                         /**< The classified TC is set to mpls_tc if action.mpls_tc is TRUE */
} mesa_qos_ingress_map_values_t CAP(QOS_INGRESS_MAP_CNT);

/** \brief Values for a combination of DSCP, PCP and DEI */
typedef struct {
    mesa_qos_ingress_map_values_t dscp[64];         /**< Mapped values for each DSCP value */
    mesa_qos_ingress_map_values_t pcp_dei[8][2];    /**< Mapped values for each PCP/DEI value */
} mesa_qos_ingress_map_dpd_t CAP(QOS_INGRESS_MAP_CNT);

/** \brief Union of mapped values for different keys */
typedef union {
    mesa_qos_ingress_map_values_t pcp[8];           /**< MESA_QOS_INGRESS_MAP_KEY_PCP */
    mesa_qos_ingress_map_values_t pcp_dei[8][2];    /**< MESA_QOS_INGRESS_MAP_KEY_PCP_DEI */
    mesa_qos_ingress_map_values_t dscp[64];         /**< MESA_QOS_INGRESS_MAP_KEY_DSCP */
    mesa_qos_ingress_map_dpd_t    dpd;              /**< MESA_QOS_INGRESS_MAP_KEY_DSCP_PCP_DEI */
    mesa_qos_ingress_map_values_t mpls_tc[8];       /**< MESA_QOS_INGRESS_MAP_KEY_MPLS_TC */
} mesa_qos_ingress_map_maps_t CAP(QOS_INGRESS_MAP_CNT);

/** \brief The complete map. There is one of these per map id */
typedef struct {
    mesa_qos_ingress_map_id_t     id;               /**< ID for this entry */
    mesa_qos_ingress_map_key_t    key;              /**< Lookup key */
    mesa_qos_ingress_map_action_t action;           /**< Action enable/disable */
    mesa_qos_ingress_map_maps_t   maps;             /**< Maps for specific key */
} mesa_qos_ingress_map_t CAP(QOS_INGRESS_MAP_CNT);

/** \brief Key that determines what to match */
typedef enum {
    MESA_QOS_EGRESS_MAP_KEY_COSID,                   /**< Use classified COS ID */
    MESA_QOS_EGRESS_MAP_KEY_COSID_DPL,               /**< Use classified COS ID and DPL */
    MESA_QOS_EGRESS_MAP_KEY_DSCP,                    /**< Use classified DSCP  */
    MESA_QOS_EGRESS_MAP_KEY_DSCP_DPL,                /**< Use classified DSCP and DPL */
    MESA_QOS_EGRESS_MAP_KEY_MPLS_TC,                 /**< Use classified TC */
    MESA_QOS_EGRESS_MAP_KEY_MPLS_TC_DPL              /**< Use classified TC and DPL */
} mesa_qos_egress_map_key_t CAP(QOS_EGRESS_MAP_CNT);

/** \brief Actions that can be applied to the frame if the entry is matched */
typedef struct {
    mesa_bool_t pcp;                                 /**< If TRUE, then replace PCP in frame */
    mesa_bool_t dei;                                 /**< If TRUE, then replace DEI in frame */
    mesa_bool_t dscp;                                /**< If TRUE, then replace DSCP in frame */
    mesa_bool_t path;                                /**< If TRUE, then replace path COS ID in frame */
    mesa_bool_t mpls_tc;                             /**< If TRUE, then replace MPLS TC in frame */
} mesa_qos_egress_map_action_t CAP(QOS_EGRESS_MAP_CNT);

/** \brief Mapped values that can be applied to classified values if the entry is matched */
typedef struct {
    mesa_pcp_t     pcp;                              /**< The classified PCP is set to pcp if action.pcp is TRUE */
    mesa_dei_t     dei;                              /**< The classified DEI is set to dei if action.dei is TRUE */
    mesa_dscp_t    dscp;                             /**< The classified DSCP is set to dscp if action.dscp is TRUE */
    mesa_cosid_t   path_cosid;                       /**< Path COS ID value used by OAM MEP if action.path is TRUE */
    mesa_mpls_tc_t mpls_tc;                          /**< The classified TC is set to mpls_tc if action.mpls_tc is TRUE */
} mesa_qos_egress_map_values_t CAP(QOS_EGRESS_MAP_CNT);

/** \brief Union of mapped values for different keys */
typedef union {
    mesa_qos_egress_map_values_t cosid[8];           /**< MESA_QOS_EGRESS_MAP_KEY_COSID */
    mesa_qos_egress_map_values_t cosid_dpl[8][4];    /**< MESA_QOS_EGRESS_MAP_KEY_COSID_DPL */
    mesa_qos_egress_map_values_t dscp[64];           /**< MESA_QOS_EGRESS_MAP_KEY_DSCP */
    mesa_qos_egress_map_values_t dscp_dpl[64][4];    /**< MESA_QOS_EGRESS_MAP_KEY_DSCP_DPL */
    mesa_qos_egress_map_values_t mpls_tc[8];         /**< MESA_QOS_EGRESS_MAP_KEY_MPLS_TC */
    mesa_qos_egress_map_values_t mpls_tc_dpl[8][4];  /**< MESA_QOS_EGRESS_MAP_KEY_MPLS_TC_DPL */
} mesa_qos_egress_map_maps_t CAP(QOS_EGRESS_MAP_CNT);

/** \brief The complete map. There is one of these per map id */
typedef struct {
    mesa_qos_egress_map_id_t     id;                 /**< ID for this entry */
    mesa_qos_egress_map_key_t    key;                /**< Lookup key */
    mesa_qos_egress_map_action_t action;             /**< Action enable/disable */
    mesa_qos_egress_map_maps_t   maps;               /**< Maps for specific key */
} mesa_qos_egress_map_t CAP(QOS_EGRESS_MAP_CNT);

/**
 * \brief Initialize an ingress map to default values.
 *
 * \param inst [IN]  Target instance reference.
 * \param key  [IN]  Initialize to this key.
 * \param map [OUT]  Ingress map structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_ingress_map_init(const mesa_inst_t                inst,
                                  const mesa_qos_ingress_map_key_t key,
                                  mesa_qos_ingress_map_t           *const map)
    CAP(QOS_INGRESS_MAP_CNT);

/**
 * \brief Add/update an ingress map.
 *
 * \param inst [IN] Target instance reference.
 * \param map  [IN] Ingress map structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_ingress_map_add(const mesa_inst_t            inst,
                                 const mesa_qos_ingress_map_t *const map)
    CAP(QOS_INGRESS_MAP_CNT);

/**
 * \brief Delete an ingress map.
 *
 * \param inst [IN]  Target instance reference.
 * \param id   [IN]  Map ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_ingress_map_del(const mesa_inst_t               inst,
                                 const mesa_qos_ingress_map_id_t id)
    CAP(QOS_INGRESS_MAP_CNT);

/**
 * \brief Delete all ingress maps.
 *
 * \param inst [IN]  Target instance reference.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_ingress_map_del_all(const mesa_inst_t inst)
    CAP(QOS_INGRESS_MAP_CNT);

/**
 * \brief Initialize an egress map to default values.
 *
 * \param inst [IN]  Target instance reference.
 * \param key  [IN]  Initialize to this key.
 * \param map [OUT]  Egress map structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_egress_map_init(const mesa_inst_t               inst,
                                 const mesa_qos_egress_map_key_t key,
                                 mesa_qos_egress_map_t           *const map)
    CAP(QOS_EGRESS_MAP_CNT);

/**
 * \brief Add/update an egress map.
 *
 * \param inst [IN] Target instance reference.
 * \param map  [IN] Egress map structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_egress_map_add(const mesa_inst_t           inst,
                                const mesa_qos_egress_map_t *const map)
    CAP(QOS_EGRESS_MAP_CNT);

/**
 * \brief Delete an egress map.
 *
 * \param inst [IN]  Target instance reference.
 * \param id   [IN]  Map ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_egress_map_del(const mesa_inst_t              inst,
                                const mesa_qos_egress_map_id_t id)
    CAP(QOS_EGRESS_MAP_CNT);

/**
 * \brief Delete all egress maps.
 *
 * \param inst [IN]  Target instance reference.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_egress_map_del_all(const mesa_inst_t inst)
    CAP(QOS_EGRESS_MAP_CNT);

/**
 * \brief Calibrate egress shaper rates.
 *
 * This function calibrates the egress port and queue shapers on MESA_ARCH_SERVAL.
 *
 * Calling this function periodically will enhance the accuracy of the egress
 * port and queue shapers.
 *
 * Recommended rate is between 1 to 50 times per second.
 *
 * \param inst [IN] Target instance reference.
 *
 * \return MESA_RC_INCOMPLETE if calibration is still needed, MESA_RC_OK if not
 * needed anymore, MESA_RC_ERROR in case of an error.
 * NOTICE: Everytime a shaper is changed, this function must be invoked again.
 **/
mesa_rc mesa_qos_shaper_calibrate(const mesa_inst_t inst)
    CAP(QOS_SHAPER_CALIBRATE);

/**
 * \brief 802.1Qbv (Enhancements for Scheduled Traffic) global configuration
 **/
typedef struct {
    mesa_bool_t always_guard_band;  /**< When set a quard band is implemented even for scheduled queues
                                       * to scheduled queue transition.
                                      * 0: Guard band is implemented for non-scheduled queues to scheduled
                                      * queues transition.
                                      * 1: Guard band is implemented for any queue to scheduled
                                      * queues transition.
                                      * The value of this object MUST be retained across
                                      * reinitializations of the management system.
                                      */
} mesa_qos_qbv_conf_t CAP(QOS_QBV);

/**
 * \brief Get 802.1Qbv (Enhancements for Scheduled Traffic) global configuration.
 *
 * \param inst    [IN]  Target instance reference.
 * \param conf    [OUT] Scheduled Traffic configuration structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_qbv_conf_get(const mesa_inst_t    inst,
                              mesa_qos_qbv_conf_t  *const conf)
    CAP(QOS_QBV);

/**
 * \brief Set 802.1Qbv (Enhancements for Scheduled Traffic) global configuration.
 *
 * \param inst    [IN] Target instance reference.
 * \param conf    [IN] Scheduled Traffic configuration structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_qbv_conf_set(const mesa_inst_t         inst,
                              const mesa_qos_qbv_conf_t *const conf)
    CAP(QOS_QBV);

/**
 * \brief 802.1Qbv (Enhancements for Scheduled Traffic) Gate Control Operations
 **/
typedef enum {
    MESA_QOS_QBV_GCO_SET_GATE_STATES,     /**< Set GateState */
    MESA_QOS_QBV_GCO_SET_AND_HOLD_MAC,    /**< Set GateState and stop preemption */
    MESA_QOS_QBV_GCO_SET_AND_RELEASE_MAC  /**< Set GateState and resume preemption */
} mesa_qos_qbv_gco_t CAP(QOS_QBV);

/**
 * \brief 802.1Qbv (Enhancements for Scheduled Traffic) gate control list entry
 **/
typedef struct {
    mesa_qos_qbv_gco_t gate_operation; /**< Gate Control Operation. */
    uint8_t            gate_state;     /**< Octet represent the gate states for the
                                          * corresponding traffic classes;
                                          * The MS bit corresponds to traffic class 7.
                                          * The LS bit to traffic class 0.
                                          * A bit value of 0 indicates closed;
                                          * A bit value of 1 indicates open.
                                          */
    uint32_t           time_interval;  /**< A TimeInterval is encoded in 4 octets as a 32-bit
                                          * unsigned integer, representing a number of clock ticks.
                                          */
} mesa_qos_qbv_gcl_t CAP(QOS_QBV);

/**
 * \brief 802.1Qbv (Enhancements for Scheduled Traffic) gate control list entry
 **/
typedef struct {
    mesa_qos_qbv_gcl_t gce; /**< Gate control entry */
} mesa_qos_port_gce_conf_t CAP(QOS_QBV);

/**
 * \brief Get 802.1Qbv (Enhancements for Scheduled Traffic) port Gate Control List.
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param cnt     [IN]  Length of Gate Control List.
 * \param conf    [OUT] Scheduled Traffic Gate Control List.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_qbv_port_gce_conf_get(const mesa_inst_t        inst,
                                       const mesa_port_no_t     port_no,
                                       const uint32_t           cnt,
                                       mesa_qos_port_gce_conf_t *const conf)
    CAP(QOS_QBV);

/**
 * \brief Set 802.1Qbv (Enhancements for Scheduled Traffic) port Gate Control List.
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param cnt     [IN]  Length of Gate Control List.
 * \param conf    [IN]  Scheduled Traffic Gate Control List.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_qbv_port_gce_conf_set(const mesa_inst_t              inst,
                                       const mesa_port_no_t           port_no,
                                       const uint32_t                 cnt,
                                       const mesa_qos_port_gce_conf_t *const conf)
    CAP(QOS_QBV);

/**
 * \brief 802.1Qbv (Enhancements for Scheduled Traffic) port configuration
 **/
typedef struct {
    uint16_t         max_sdu[MESA_QUEUE_ARRAY_SIZE]; /**< Maximum SDU size supported by each queue. */
    uint8_t          sch_traffic_queues;             /**< A 8-bit vector that determines port queues which
                                                        * will allow scheduled traffic among the 8 queues.
                                                        * The bits of the octet represent the configuration
                                                        * for the corresponding traffic classes; the MS bit
                                                        * corresponds to traffic class 7, the LS bit to traffic class 0.
                                                        * A bit value of 0 indicates guard band enabled (non scheduled traffic queue);
                                                        * a bit value of 1 indicates guard band disabled (scheduled traffic queue).
                                                        * The latter can be overridden by the 'always_guard_band' global
                                                        * object, that enables guard band also for scheduled traffic queues.
                                                        * The value of this object MUST be retained across
                                                        * reinitializations of the management system.
                                                        */
    mesa_bool_t      gate_enabled;                   /**< The GateEnabled parameter determines
                                                        * whether traffic scheduling
                                                        * is active (true) or inactive (false).
                                                        * The value of this object MUST be retained across
                                                        * reinitializations of the management system.
                                                        */
    uint8_t          admin_gate_states;              /**< The administrative value of the GateStates parameter
                                                        * for the Port. The bits of the octet represent the gate
                                                        * states for the corresponding traffic classes; the MS bit
                                                        * corresponds to traffic class 7, the LS bit to traffic
                                                        * class 0. A bit value of 0 indicates closed; a bit value
                                                        * of 1 indicates open. The value of this object MUST be
                                                        * retained across reinitializations of the management system.
                                                        */
    uint32_t         admin_control_list_length;      /**< The administrative value of the ControlListLength parameter for the
                                                        * port. The integer value indicates the number of entries (TLVs)
                                                        * in the AdminControlList. The value of this object MUST be
                                                        * retained across reinitializations of the management system.
                                                        */
    uint32_t         admin_cycle_time_numerator;     /**< The administrative value of the numerator of the CycleTime
                                                        * parameter for the Port. The numerator and denominator together
                                                        * represent the cycle time as a rational number of seconds.
                                                        * The value of this object MUST be retained across
                                                        * reinitializations of the management system.
                                                        */
    uint32_t         admin_cycle_time_denominator;   /**< The administrative value of the denominator of the
                                                        * CycleTime parameter for the Port. The numerator and denominator
                                                        * together represent the cycle time as a rational number of seconds.
                                                        * The value of this object MUST be retained across
                                                        * reinitializations of the management system.
                                                        */
    uint32_t         admin_cycle_time_extension;     /**< The administrative value of the CycleTimeExtension
                                                        * parameter for the Port. The value is an unsigned integer number
                                                        * of nanoseconds. The value of this object MUST be retained across
                                                        * reinitializations of the management system.
                                                        */
    mesa_timestamp_t admin_base_time;                /**< The administrative value of the BaseTime parameter for the Port.
                                                        * The value is a representation of a PTPtime value, consisting of a
                                                        * 48-bit integer number of seconds and a 32-bit integer number of
                                                        * nanoseconds. The value of this object MUST be retained across
                                                        * reinitializations of the management system.
                                                        */
    mesa_bool_t      config_change;                  /**< The ConfigChange parameter signals the start of a configuration
                                                        * change when it is set to TRUE. This should only be done when the
                                                        * various administrative parameters are all set to appropriate
                                                        * values.
                                                        */
} mesa_qos_qbv_port_conf_t CAP(QOS_QBV);

/**
 * \brief Get 802.1Qbv (Enhancements for Scheduled Traffic) port configuration.
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf    [OUT] Scheduled Traffic configuration structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_qbv_port_conf_get(const mesa_inst_t       inst,
                                   const mesa_port_no_t    port_no,
                                   mesa_qos_qbv_port_conf_t *const conf)
    CAP(QOS_QBV);

/**
 * \brief Set 802.1Qbv (Enhancements for Scheduled Traffic) port configuration.
 *
 * \param inst    [IN] Target instance reference.
 * \param port_no [IN] Port number.
 * \param conf    [IN] Scheduled Traffic configuration structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_qbv_port_conf_set(const mesa_inst_t             inst,
                                   const mesa_port_no_t          port_no,
                                   const mesa_qos_qbv_port_conf_t *const conf)
    CAP(QOS_QBV);

/**
 * \brief 802.1Qbv (Enhancements for Scheduled Traffic) gate control list entry.
 **/
typedef struct {
    mesa_qos_qbv_gcl_t gce; /**< Gate control entry */
} mesa_qos_qbv_port_gce_status_t CAP(QOS_QBV);

/**
 * \brief Get 802.1Qbv (Enhancements for Scheduled Traffic) port Gate OperControlList.
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param cnt     [IN]  Length of Gate Control List.
 * \param conf    [OUT] Scheduled Traffic Gate Control List.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_qbv_port_gce_status_get(const mesa_inst_t              inst,
                                         const mesa_port_no_t           port_no,
                                         const uint32_t                 cnt,
                                         mesa_qos_qbv_port_gce_status_t *const status)
    CAP(QOS_QBV);

/**
 * \brief 802.1Qbv (Enhancements for Scheduled Traffic) port status.
 **/
typedef struct {
    uint64_t         transmission_overrun[MESA_QUEUE_ARRAY_SIZE]; /**< Counter of transmission overrun events per queue. */
    uint8_t          oper_gate_states;                            /**< The operational value of the GateStates parameter for
                                                                     * the Port. The bits of the octet represent the gate states
                                                                     * for the corresponding traffic classes;the MS bit corresponds
                                                                     * to traffic class 7, the LS bit to traffic class 0. A bit
                                                                     * value of 0 indicates closed; a bit value of 1 indicates open.
                                                                     */
    uint32_t         oper_control_list_length;                    /**< The operational value of the ControlListLength parameter for the
                                                                     * Port. The integer value indicates the number of entries
                                                                     * (TLVs) in the OperControlList.
                                                                     */
    uint32_t         oper_cycle_time_numerator;                   /**< The operational value of the numerator of the
                                                                     * CycleTime parameter for the Port. The numerator
                                                                     * and denominator together represent the cycle
                                                                     * time as a rational number of seconds.
                                                                     */
    uint32_t         oper_cycle_time_denominator;                 /**< The operational value of the denominator of the
                                                                     * CycleTime parameter for the Port. The numerator and
                                                                     * denominator together represent the cycle time as a rational
                                                                     * number of seconds.
                                                                     */
    uint32_t         oper_cycle_time_extension;                   /**< The operational value of the CycleTimeExtension parameter
                                                                     * for the Port. The value is an unsigned integer number of
                                                                    * nanoseconds.
                                                                    */
    mesa_timestamp_t oper_base_time;                              /**< The operational value of the BaseTime parameter for the Port.
                                                                     * The value is a representation of a PTPtime value,
                                                                     * consisting of a 48-bit integer number of seconds and a 32-bit
                                                                     * integer number of nanoseconds.
                                                                     */
    mesa_timestamp_t config_change_time;                          /**< The PTPtime at which the next config change is scheduled to occur.
                                                                     * The value is a representation of a PTPtime value,
                                                                     * consisting of a 48-bit integer
                                                                     * number of seconds and a 32-bit integer number of nanoseconds.
                                                                     * The value of this object MUST be retained across
                                                                     * reinitializations of the management system.
                                                                     */
    uint32_t         tick_granularity;                            /**< The granularity of the cycle time clock, represented as an
                                                                     * unsigned number of tenths of nanoseconds.
                                                                     * The value of this object MUST be retained across
                                                                     * reinitializations of the management system.
                                                                     */
    mesa_timestamp_t current_time;                                /**< The current time, in PTPtime, as maintained by the local system.
                                                                     * The value is a representation of a PTPtime value,
                                                                     * consisting of a 48-bit integer
                                                                     * number of seconds and a 32-bit integer number of nanoseconds.
                                                                     */
    mesa_bool_t      config_pending;                              /**< The value of the ConfigPending state machine variable.
                                                                     * The value is TRUE if a configuration change is in progress
                                                                     * but has not yet completed.
                                                                     */
    uint64_t         config_change_error;                         /**< A counter of the number of times that a re-configuration
                                                                     * of the traffic schedule has been requested with the old
                                                                     * schedule still running and the requested base time was
                                                                     * in the past.
                                                                     */
    uint32_t         supported_list_max;                          /**< The maximum value supported by this Port of the
                                                                     * AdminControlListLength and OperControlListLength
                                                                     * parameters.
                                                                     */
} mesa_qos_qbv_port_status_t CAP(QOS_QBV);

/**
 * \brief Get 802.1Qbv (Enhancements for Scheduled Traffic) status for port.
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param status  [OUT] Scheduled Traffic status structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_qbv_port_status_get(const mesa_inst_t          inst,
                                     const mesa_port_no_t       port_no,
                                     mesa_qos_qbv_port_status_t *const status)
    CAP(QOS_QBV);

/**
 * \brief 802.1Qbu and 802.3br (Frame Preemption) port configuration
 **/
typedef struct {
    mesa_bool_t admin_status[MESA_QUEUE_ARRAY_SIZE]; /**< This parameter is the administrative value of the preemption
                                                        * status for the priority. It takes the value express (0) or
                                                        * preemptable (1). This parameter corresponds to the
                                                        * framePreemptionStatusTable managed object in 802.1Qbu.
                                                        **/
    mesa_bool_t enable_rx;                           /**< The enable_rx parameter determines whether the
                                                        * MAC Merge layer is enabled (true) or disabled (false)
                                                        * in the receive direction.
                                                        **/
    mesa_bool_t enable_tx;                           /**< The enable_tx parameter determines whether the
                                                        * MAC Merge layer is enabled (true) or disabled (false)
                                                        * in the transmit direction.
                                                        * This parameter corresponds to the aMACMergeEnableTx
                                                        * attribute in 802.3br.
                                                        **/
    mesa_bool_t verify_disable_tx;                   /**< The verify_disable_tx parameter determines whether the
                                                        * verification of preemption capabilities is disabled (true)
                                                        * or enabled (false).
                                                        * This parameter corresponds to the aMACMergeVerifyDisableTx
                                                        * attribute in 802.3br.
                                                        **/
    uint8_t     verify_time;                         /**< The verify_time parameter defines the nominal wait time
                                                        * between verification attempts in milliseconds.
                                                        * Valid range is 1 to 128 inclusive. The default value is 10.
                                                        * This parameter corresponds to the aMACMergeVerifyTime
                                                        * attribute in 802.3br.
                                                        **/
} mesa_qos_fp_port_conf_t CAP(QOS_FRAME_PREEMPTION);

/**
 * \brief Get 802.1Qbu and 802.3br (Frame Preemption) port configuration.
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf    [OUT] Frame Preemption configuration structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_fp_port_conf_get(const mesa_inst_t       inst,
                                  const mesa_port_no_t    port_no,
                                  mesa_qos_fp_port_conf_t *const conf)
    CAP(QOS_FRAME_PREEMPTION);

/**
 * \brief Set 802.1Qbu and 802.3br (Frame Preemption) port configuration.
 *
 * \param inst    [IN] Target instance reference.
 * \param port_no [IN] Port number.
 * \param conf    [IN] Frame Preemption configuration structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_fp_port_conf_set(const mesa_inst_t             inst,
                                  const mesa_port_no_t          port_no,
                                  const mesa_qos_fp_port_conf_t *const conf)
    CAP(QOS_FRAME_PREEMPTION);

/**
 * \brief MAC Merge Status Verify (aMACMergeStatusVerify in 802.3br)
 **/
typedef enum {
    MESA_MM_STATUS_VERIFY_INITIAL,             /**< Verify state diagram in state INIT_VERIFICATION */
    MESA_MM_STATUS_VERIFY_VERIFYING,           /**< Verify state diagram in state VERIFICATION_IDLE,
                                                  * SEND_VERIFY or WAIT_FOR_RESPONSE.
                                                  */
    MESA_MM_STATUS_VERIFY_SUCCEEDED,           /**< Verify state diagram in state VERIFIED */
    MESA_MM_STATUS_VERIFY_FAILED,              /**< Verify state diagram in state VERIFY_FAIL */
    MESA_MM_STATUS_VERIFY_DISABLED             /**< Verification process is disabled */
} mesa_mm_status_verify_t CAP(QOS_FRAME_PREEMPTION);

/**
 * \brief 802.1Qbu and 802.3br (Frame Preemption) port status
 **/
typedef struct {
    uint32_t                hold_advance;      /**< The value of the holdAdvance parameter
                                                *   for the port in nanoseconds.
                                                *   There is no default value; the holdAdvance is
                                                *   a property of the underlying MAC.
                                                *   This parameter corresponds to the holdAdvance
                                                *   parameter in 802.1Qbu.
                                                */
    uint32_t                release_advance;   /**< The value of the releaseAdvance parameter
                                                *   for the port in nanoseconds.
                                                *   There is no default value; the releaseAdvance is
                                                *   a property of the underlying MAC.
                                                *   This parameter corresponds to the releaseAdvance
                                                *   parameter in 802.1Qbu.
                                                */
    mesa_bool_t             preemption_active; /**< The value is active (TRUE) when preemption is operationally
                                                *   active for the port, and idle (FALSE) otherwise.
                                                *   This parameter corresponds to the preemptionActive
                                                *   parameter in 802.1Qbu.
                                                */
    uint8_t                 hold_request;      /**< The value is hold (1) when the sequence of gate operations
                                                *   for the port has executed a Set-And-Hold-MAC operation,
                                                *   and release (2) when the sequence of gate operations has
                                                *   executed a Set-And-Release-MAC operation. The
                                                *   value of this object is release (2) on system
                                                *   initialization.
                                                *   This parameter corresponds to the holdRequest
                                                *   parameter in 802.1Qbu.
                                                */
    mesa_mm_status_verify_t status_verify;     /**< Status of MAC Merge sublayer verification.
                                                *   This parameter corresponds to the aMACMergeStatusVerify
                                                *   attribute in 802.3br.
                                                */
    mesa_bool_t             status_tx;         /**< Status of the MAC Merge sublayer in the transmit direction.
                                                *   This parameter corresponds to the aMACMergeStatusTx
                                                *   attribute in IEEE 802.3br-2016.
                                                */
    uint8_t                 add_frag_size;     /**< The value of the 802.3br LocAddFragSize
                                                *   parameter for the port.
                                                *   The minimum size of non-final fragments supported by the
                                                *   receiver on the local port. This value is expressed in units
                                                *   of 64 octets of additional fragment length.
                                                *   The minimum non-final fragment size is:
                                                *   (LocAddFragSize + 1) * 64 octets.
                                                **/
} mesa_qos_fp_port_status_t CAP(QOS_FRAME_PREEMPTION);

/**
 * \brief Get 802.1Qbu and 802.3br (Frame Preemption) port status.
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param status  [OUT] Frame Preemption status structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_qos_fp_port_status_get(const mesa_inst_t         inst,
                                    const mesa_port_no_t      port_no,
                                    mesa_qos_fp_port_status_t *const status)
    CAP(QOS_FRAME_PREEMPTION);


/** \brief EVC policer configuration */
typedef mesa_dlb_policer_conf_t mesa_evc_policer_conf_t;

#define MESA_EVC_POLICER_ID_DISCARD 4094 /**< EVC/ECE: Policer discards all frames */
#define MESA_EVC_POLICER_ID_NONE    4095 /**< EVC/ECE: Policer forwards all frames */
#define MESA_EVC_POLICER_ID_EVC     4096 /**< ECE only: Use EVC policer */

/**
 * \brief Get EVC policer configuration.
 *
 * \param inst [IN]        Target instance reference.
 * \param policer_id [IN]  Policer ID.
 * \param conf [OUT]       Policer configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_evc_policer_conf_get(const mesa_inst_t           inst,
                                  const mesa_evc_policer_id_t policer_id,
                                  mesa_evc_policer_conf_t     *const conf)
    CAP(EVC_POLICER_CNT);

/**
 * \brief Set EVC policer configuration.
 *
 * \param inst [IN]        Target instance reference.
 * \param policer_id [IN]  Policer ID.
 * \param conf [IN]        Policer configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_evc_policer_conf_set(const mesa_inst_t             inst,
                                  const mesa_evc_policer_id_t   policer_id,
                                  const mesa_evc_policer_conf_t *const conf)
    CAP(EVC_POLICER_CNT);


#include <mscc/ethernet/switch/api/hdr_end.h>
#endif // _MSCC_ETHERNET_SWITCH_API_QOS_
