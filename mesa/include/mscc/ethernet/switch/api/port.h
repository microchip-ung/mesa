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

#ifndef _MSCC_ETHERNET_SWITCH_API_PORT_
#define _MSCC_ETHERNET_SWITCH_API_PORT_

#include <mscc/ethernet/switch/api/types.h>
#include <mscc/ethernet/switch/api/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

/******************************************************************************/
/* Port Speed                                                                 */
/******************************************************************************/

/** \brief Port speed */
typedef enum
{
    MESA_SPEED_UNDEFINED,   /**< Undefined */
    MESA_SPEED_10M,         /**< 10 M */
    MESA_SPEED_100M,        /**< 100 M */
    MESA_SPEED_1G,          /**< 1 G */
    MESA_SPEED_2500M,       /**< 2.5G */
    MESA_SPEED_5G,          /**< 5G or 2x2.5G */
    MESA_SPEED_10G,         /**< 10 G */
    MESA_SPEED_12G,         /**< 12G */
    MESA_SPEED_25G,         /**< 25G */
    MESA_SPEED_AUTO
} mesa_port_speed_t;

/** \brief Fiber Port speed */
typedef enum
{
    MESA_SPEED_FIBER_NOT_SUPPORTED_OR_DISABLED = 0, /**< Fiber not supported/ Fiber port disabled */
    MESA_SPEED_FIBER_100FX = 2,       /**< 100BASE-FX*/
    MESA_SPEED_FIBER_1000X = 3,       /**< 1000BASE-X*/
    MESA_SPEED_FIBER_AUTO = 4,        /**< Auto detection - AMS mode*/
    MESA_SPEED_FIBER_DISABLED = 5,    /**< Obsolete - use MESA_SPEED_FIBER_NOT_SUPPORTED_OR_DISABLED instead*/
    MESA_SPEED_FIBER_ONLY_AUTO = 6,   /**< Auto detection - Fiber only (no RJ45)*/
} mesa_fiber_port_speed_t;

/******************************************************************************/
/* Port status                                                                */
/******************************************************************************/

/** \brief Port status parameter struct */
typedef struct
{
    mesa_event_t      link_down;       /**< Link down event occurred since last call */
    mesa_bool_t       link;            /**< Link is up. Remaining fields only valid if TRUE */
    mesa_port_speed_t speed;           /**< Speed */
    mesa_bool_t       fdx;             /**< Full duplex */
    mesa_bool_t       remote_fault;    /**< Remote fault signalled */
    mesa_bool_t       aneg_complete;   /**< Autoneg completed (for clause_37 and Cisco aneg) */
    mesa_bool_t       unidirectional_ability; /**<TRUE: PHY able to transmit from media independent interface regardless of whether the PHY has
                                                 determined that a valid link has been established.FALSE: PHY able to transmit from media
                                                 independent interface only when the PHY has determined that a valid link has been established.
                                                 Note This bit is only applicable to 100BASE-FX and 1000BASE-X fiber media modes.*/
    mesa_aneg_t       aneg;                  /**< Auto negotiation result */
    mesa_bool_t       mdi_cross;             /**< Indication of if Auto-MDIX crossover is performed */
    mesa_bool_t       fiber;                 /**< Indication of if the link is a fiber link, TRUE if link is a fiber link. FALSE if link is cu link or No Media */
    mesa_bool_t       copper;                /**< Indication of if the link is a copper link, TRUE if link is a copper link. FALSE if link is fiber link or No Media */
} mesa_port_status_t;

/** \brief MII management controller */
typedef enum
{
    MESA_MIIM_CONTROLLER_0    = 0,  /**< MIIM controller 0 */
    MESA_MIIM_CONTROLLER_1    = 1,  /**< MIIM controller 1 */
    MESA_MIIM_CONTROLLER_2    = 2,  /**< MIIM controller 2 */
    MESA_MIIM_CONTROLLER_3    = 3,  /**< MIIM controller 3 */
    MESA_MIIM_CONTROLLERS,          /**< Number of MIIM controllers */
    MESA_MIIM_CONTROLLER_NONE = -1  /**< Unassigned MIIM controller */
} mesa_miim_controller_t;


/** \brief The internal bandwidth allocated for the port */
typedef enum
{
    MESA_BW_DEFAULT,     /**< Default to max port speed */
    MESA_BW_1G,          /**< Max 1G */
    MESA_BW_2G5,         /**< Max 2.5G */
    MESA_BW_5G,          /**< Max 5G */
    MESA_BW_10G,         /**< Max 10G */
    MESA_BW_25G,         /**< Max 10G */
    MESA_BW_UNDEFINED,   /**< Undefined */
} mesa_internal_bw_t;

#define CHIP_PORT_UNUSED -1 /**< Signifies an unused chip port */

/** \brief Port map structure */
typedef struct
{
    int32_t                chip_port;        /**< Set to -1 if not used */
    mesa_chip_no_t         chip_no;          /**< Chip number, multi-chip targets */
    mesa_internal_bw_t     max_bw CAP(PORT_BW); /**< Max internal bandwidth reserved for the port */
    mesa_miim_controller_t miim_controller;  /**< MII management controller */
    uint8_t                miim_addr;        /**< PHY address, ignored for MESA_MIIM_CONTROLLER_NONE */
    mesa_chip_no_t         miim_chip_no;     /**< MII management chip number, multi-chip targets */
} mesa_port_map_t;

/**
 * \brief Set port map.
 *
 * \param inst [IN]      Target instance reference.
 * \param cnt [IN]       Number of entries in port_map. Must be equal to the configured port count.
 * \param port_map [IN]  Port map array.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_map_set(const mesa_inst_t     inst,
                          uint32_t              cnt,
                          const mesa_port_map_t *port_map);

/**
 * \brief Get port map.
 *
 * \param inst [IN]       Target instance reference.
 * \param cnt [IN]        Number of entries in port_map. Must be equal to the configured port count.
 * \param port_map [OUT]  Port map.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_map_get(const mesa_inst_t  inst,
                          uint32_t           cnt,
                          mesa_port_map_t    *port_map);

/**
 * Advertisement Word (Refer to IEEE 802.3 Clause 37):
 *  MSB                                                                         LSB
 *  D15  D14  D13  D12  D11  D10   D9   D8   D7   D6   D5   D4   D3   D2   D1   D0
 * +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
 * | NP | Ack| RF2| RF1|rsvd|rsvd|rsvd| PS2| PS1| HD | FD |rsvd|rsvd|rsvd|rsvd|rsvd|
 * +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
 **/

/** \brief Auto-negotiation remote fault type */
typedef enum                      /* RF2      RF1 */
{
    MESA_PORT_CLAUSE_37_RF_LINK_OK       = ((0<<1) | (0<<0)),   /**< Link OK */
    MESA_PORT_CLAUSE_37_RF_OFFLINE       = ((1<<1) | (0<<0)),   /**< Off line */
    MESA_PORT_CLAUSE_37_RF_LINK_FAILURE  = ((0<<1) | (1<<0)),   /**< Link failure */
    MESA_PORT_CLAUSE_37_RF_AUTONEG_ERROR = ((1<<1) | (1<<0))    /**< Autoneg error */
} mesa_port_clause_37_remote_fault_t;

// TODO, flags
/** \brief Advertisement control data for Clause 37 aneg */
typedef struct
{
    mesa_bool_t                        fdx;               /**< (FD) */
    mesa_bool_t                        hdx;               /**< (HD) */
    mesa_bool_t                        symmetric_pause;   /**< (PS1) */
    mesa_bool_t                        asymmetric_pause;  /**< (PS2) */
    mesa_port_clause_37_remote_fault_t remote_fault;      /**< (RF1) + (RF2) */
    mesa_bool_t                        acknowledge;       /**< (Ack) */
    mesa_bool_t                        next_page;         /**< (NP) */
} mesa_port_clause_37_adv_t;

// TODO, flags
/** \brief Advertisement control data for SGMII aneg */
typedef struct
{
    mesa_bool_t                        link;              /**< LP link status               */
    mesa_bool_t                        fdx;               /**< FD                           */
    mesa_bool_t                        hdx;               /**< HD                           */
    mesa_bool_t                        speed_10M;         /**< speed 10 advertised          */
    mesa_bool_t                        speed_100M;        /**< speed 100 advertised         */
    mesa_bool_t                        speed_1G;          /**< speed 1G advertised          */
    mesa_bool_t                        aneg_complete;     /**< Aneg process completed       */
} mesa_port_sgmii_aneg_t;


/** \brief Auto-negotiation control parameter struct */
typedef struct
{
    mesa_bool_t               enable;           /**< Enable of Autoneg */
    mesa_port_clause_37_adv_t advertisement;    /**< Clause 37 Advertisement control data */
} mesa_port_clause_37_control_t;

/**
 * \brief Get clause 37 auto-negotiation Control word.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param control [OUT]  Control structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_clause_37_control_get(const mesa_inst_t              inst,
                                        const mesa_port_no_t           port_no,
                                        mesa_port_clause_37_control_t  *const control);



/**
 * \brief Set clause 37 auto-negotiation Control word.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param control [IN]  Control structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_clause_37_control_set(const mesa_inst_t                    inst,
                                        const mesa_port_no_t                 port_no,
                                        const mesa_port_clause_37_control_t  *const control);
// TODO, flags
/** \brief Flow control setup */
typedef struct
{
    mesa_bool_t       obey;            /**< TRUE if 802.3x PAUSE frames should be obeyed */
    mesa_bool_t       generate;        /**< TRUE if 802.3x PAUSE frames should generated */
    mesa_mac_t        smac;            /**< Port MAC address used as SMAC in PAUSE frames */
    mesa_bool_t       pfc[MESA_PRIO_ARRAY_SIZE]; /**< TRUE if 802.1Qbb Priority Flow Control should be generated and obeyed.
                                               Cannot be enabled together with 802.3x Flowcontrol */
} mesa_port_flow_control_conf_t;

/** \brief Inter frame gap structure */
typedef struct
{
    uint32_t hdx_gap_1;      /**< Half duplex: First part of Rx to Tx gap */
    uint32_t hdx_gap_2;      /**< Half duplex: Second part of Rx to Tx gap */
    uint32_t fdx_gap;        /**< Full duplex: Tx to Tx gap */
} mesa_port_frame_gaps_t;

#define MESA_MAX_FRAME_LENGTH_STANDARD 1518  /**< IEEE 802.3 standard */

/** \brief VLAN awareness for frame length check */
typedef enum
{
    MESA_PORT_MAX_TAGS_NONE,  /**< No extra tags allowed */
    MESA_PORT_MAX_TAGS_ONE,   /**< Single tag allowed */
    MESA_PORT_MAX_TAGS_TWO    /**< Single and double tag allowed */
} mesa_port_max_tags_t;

/** \brief Port loop back configuration */
typedef enum
{
    MESA_PORT_LOOP_DISABLE,   /**< No port loop */
    MESA_PORT_LOOP_PCS_HOST,  /**< PCS host port loop */
} mesa_port_loop_t;

/** \brief Different media/cable types attached to the 10G Serdes */
typedef enum {
    MESA_SD10G_MEDIA_SR,         /**< Short Range > */
    MESA_SD10G_MEDIA_ZR,         /**< ZR with APC hardware algorithm > */
    MESA_SD10G_MEDIA_DAC,        /**< DAC (Direct attached copper) with APC hardware algorithm > */
    MESA_SD10G_MEDIA_BP,         /**< Backplane > */
    MESA_SD10G_MEDIA_B2B,        /**< Bord to Board > */
    MESA_SD10G_MEDIA_10G_KR,     /**< 10G Base KR > */
    MESA_SD10G_MEDIA_PR_NONE     /**< No preset > */
} mesa_sd10g_media_type_t;

// TODO, flags
/** \brief SFI Serdes configuration */
typedef struct
{
    mesa_bool_t              sfp_dac;                /**< obsolete (use media_10g)        */
    mesa_sd10g_media_type_t  media_type;             /**< The 10G Serdes media/cable type */
    mesa_bool_t              rx_invert;              /**< Invert the RX Serdes signal (1) */
    mesa_bool_t              tx_invert;              /**< Invert the TX Serdes signal (1) */
} mesa_port_serdes_conf_t;

/** \brief 1G PCS specific configuration */
typedef enum
{
    MESA_PORT_PCS_NORMAL,     /**< Normal 1G PCS configuration    */
    MESA_PORT_PCS_ENABLE,     /**< Only Enable 1G PCS and return  */
    MESA_PORT_PCS_DISABLE,    /**< Only Disable 1G PCS and return */
    MESA_PORT_PCS_IGNORE      /**< Skip any PCS settings          */
} mesa_port_pcs_conf_t CAP(PORT_PCS_CONF);

// TODO, flags
/** \brief Port configuration structure */
typedef struct
{
    mesa_port_interface_t   if_type;           /**< Interface type */
    mesa_bool_t             sd_enable;         /**< Signal detect enable */
    mesa_bool_t             sd_active_high;    /**< External signal detect polarity */
    mesa_bool_t             sd_internal;       /**< Internal signal detect selection */
    mesa_port_frame_gaps_t  frame_gaps;        /**< Inter frame gaps */
    mesa_bool_t             power_down;        /**< Disable and power down the port */
    mesa_port_speed_t       speed;             /**< Port speed */
    mesa_bool_t             fdx;               /**< Full duplex mode */
    mesa_port_flow_control_conf_t flow_control;      /**< Flow control setup */
    uint32_t                max_frame_length;  /**< Maximum frame length */
    mesa_bool_t             frame_length_chk;  /**< Enforce 802.3 frame length check (from ethertype field) */
    mesa_port_max_tags_t    max_tags;          /**< VLAN awareness for length check */
    mesa_bool_t             exc_col_cont;      /**< Excessive collision continuation */
    mesa_bool_t             xaui_rx_lane_flip; /**< Xaui Rx lane flip */
    mesa_bool_t             xaui_tx_lane_flip; /**< Xaui Tx lane flip */
    mesa_port_loop_t        loop;              /**< Enable/disable of port loop back */
    mesa_port_serdes_conf_t serdes;            /**< Serdes settings (for SFI interface) */
    mesa_port_pcs_conf_t    pcs CAP(PORT_PCS_CONF); /**< Special 1G PCS settings, only supported for L26 */
} mesa_port_conf_t;

/**
 * \brief Set port configuration.
 *  Note: If if_type in the mesa_port_conf_t/mesa_port_interface_t definition is set to MESA_PORT_INTERFACE_QSGMII, the ports are mapped together in groups of four. If one of the four ports is used, all four ports in the group must always be configured, but the four ports doesn't need to configured with the same configuration.
 * This is needed in order to achieve correct comma alignment at the QSGMII interface. Which ports that are mapped together can be found in the chip data-sheet.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     Port setup structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_conf_set(const mesa_inst_t       inst,
                           const mesa_port_no_t    port_no,
                           const mesa_port_conf_t  *const conf);



/**
 * \brief Get port setup.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    Port configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_conf_get(const mesa_inst_t     inst,
                           const mesa_port_no_t  port_no,
                           mesa_port_conf_t      *const conf);


/**
 * \brief Get port status.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param status [OUT]  Status structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_status_get(const mesa_inst_t     inst,
                             const mesa_port_no_t  port_no,
                             mesa_port_status_t    *const status);



/******************************************************************************/
/* Port Counters                                                              */
/******************************************************************************/

/** \brief Counter type */
typedef uint64_t mesa_port_counter_t;

/** \brief RMON counter structure (RFC 2819) */
typedef struct {
    mesa_port_counter_t rx_etherStatsDropEvents;           /**< Rx drop events */
    mesa_port_counter_t rx_etherStatsOctets;               /**< Rx octets */
    mesa_port_counter_t rx_etherStatsPkts;                 /**< Rx packets */
    mesa_port_counter_t rx_etherStatsBroadcastPkts;        /**< Rx broadcasts */
    mesa_port_counter_t rx_etherStatsMulticastPkts;        /**< Rx multicasts */
    mesa_port_counter_t rx_etherStatsCRCAlignErrors;       /**< Rx CRC/alignment errors */
    mesa_port_counter_t rx_etherStatsUndersizePkts;        /**< Rx undersize packets */
    mesa_port_counter_t rx_etherStatsOversizePkts;         /**< Rx oversize packets */
    mesa_port_counter_t rx_etherStatsFragments;            /**< Rx fragments */
    mesa_port_counter_t rx_etherStatsJabbers;              /**< Rx jabbers */
    mesa_port_counter_t rx_etherStatsPkts64Octets;         /**< Rx 64 byte packets */
    mesa_port_counter_t rx_etherStatsPkts65to127Octets;    /**< Rx 65-127 byte packets */
    mesa_port_counter_t rx_etherStatsPkts128to255Octets;   /**< Rx 128-255 byte packets */
    mesa_port_counter_t rx_etherStatsPkts256to511Octets;   /**< Rx 256-511 byte packets */
    mesa_port_counter_t rx_etherStatsPkts512to1023Octets;  /**< Rx 512-1023 byte packet */
    mesa_port_counter_t rx_etherStatsPkts1024to1518Octets; /**< Rx 1024-1518 byte packets */
    mesa_port_counter_t rx_etherStatsPkts1519toMaxOctets;  /**< Rx 1519- byte packets */

    mesa_port_counter_t tx_etherStatsDropEvents;           /**< Tx drop events */
    mesa_port_counter_t tx_etherStatsOctets;               /**< Tx octets */
    mesa_port_counter_t tx_etherStatsPkts;                 /**< Tx packets */
    mesa_port_counter_t tx_etherStatsBroadcastPkts;        /**< Tx broadcasts */
    mesa_port_counter_t tx_etherStatsMulticastPkts;        /**< Tx multicasts */
    mesa_port_counter_t tx_etherStatsCollisions;           /**< Tx collisions */
    mesa_port_counter_t tx_etherStatsPkts64Octets;         /**< Tx 64 byte packets */
    mesa_port_counter_t tx_etherStatsPkts65to127Octets;    /**< Tx 65-127 byte packets */
    mesa_port_counter_t tx_etherStatsPkts128to255Octets;   /**< Tx 128-255 byte packets */
    mesa_port_counter_t tx_etherStatsPkts256to511Octets;   /**< Tx 256-511 byte packets */
    mesa_port_counter_t tx_etherStatsPkts512to1023Octets;  /**< Tx 512-1023 byte packet */
    mesa_port_counter_t tx_etherStatsPkts1024to1518Octets; /**< Tx 1024-1518 byte packets */
    mesa_port_counter_t tx_etherStatsPkts1519toMaxOctets;  /**< Tx 1519- byte packets */
} mesa_port_rmon_counters_t;

/** \brief Interfaces Group counter structure (RFC 2863) */
typedef struct {
    mesa_port_counter_t ifInOctets;          /**< Rx octets */
    mesa_port_counter_t ifInUcastPkts;       /**< Rx unicasts */
    mesa_port_counter_t ifInMulticastPkts;   /**< Rx multicasts */
    mesa_port_counter_t ifInBroadcastPkts;   /**< Rx broadcasts */
    mesa_port_counter_t ifInNUcastPkts;      /**< Rx non-unicasts */
    mesa_port_counter_t ifInDiscards;        /**< Rx discards */
    mesa_port_counter_t ifInErrors;          /**< Rx errors */

    mesa_port_counter_t ifOutOctets;         /**< Tx octets */
    mesa_port_counter_t ifOutUcastPkts;      /**< Tx unicasts */
    mesa_port_counter_t ifOutMulticastPkts;  /**< Tx multicasts */
    mesa_port_counter_t ifOutBroadcastPkts;  /**< Tx broadcasts */
    mesa_port_counter_t ifOutNUcastPkts;     /**< Tx non-unicasts */
    mesa_port_counter_t ifOutDiscards;       /**< Tx discards */
    mesa_port_counter_t ifOutErrors;         /**< Tx errors */
} mesa_port_if_group_counters_t;

/** \brief Ethernet-like Interface counter structure (RFC 3635) */
typedef struct {
    mesa_port_counter_t dot3StatsAlignmentErrors          CAP(PORT_CNT_ETHER_LIKE); /**< Rx alignment errors */
    mesa_port_counter_t dot3StatsFCSErrors                CAP(PORT_CNT_ETHER_LIKE); /**< Rx FCS errors */
    mesa_port_counter_t dot3StatsFrameTooLongs            CAP(PORT_CNT_ETHER_LIKE); /**< Rx too long */
    mesa_port_counter_t dot3StatsSymbolErrors             CAP(PORT_CNT_ETHER_LIKE); /**< Rx symbol errors */
    mesa_port_counter_t dot3ControlInUnknownOpcodes       CAP(PORT_CNT_ETHER_LIKE); /**< Rx unknown opcodes */
    mesa_port_counter_t dot3InPauseFrames;                 /**< Rx pause */

    mesa_port_counter_t dot3StatsSingleCollisionFrames    CAP(PORT_CNT_ETHER_LIKE); /**< Tx single collisions */
    mesa_port_counter_t dot3StatsMultipleCollisionFrames  CAP(PORT_CNT_ETHER_LIKE); /**< Tx multiple collisions */
    mesa_port_counter_t dot3StatsDeferredTransmissions    CAP(PORT_CNT_ETHER_LIKE); /**< Tx deferred */
    mesa_port_counter_t dot3StatsLateCollisions           CAP(PORT_CNT_ETHER_LIKE); /**< Tx late collisions */
    mesa_port_counter_t dot3StatsExcessiveCollisions      CAP(PORT_CNT_ETHER_LIKE); /**< Tx excessive collisions */
    mesa_port_counter_t dot3StatsCarrierSenseErrors       CAP(PORT_CNT_ETHER_LIKE); /**< Tx carrier sense errors */
    mesa_port_counter_t dot3OutPauseFrames;                /**< Tx pause */
} mesa_port_ethernet_like_counters_t;

/** \brief Port bridge counter structure (RFC 4188) */
typedef struct
{
    mesa_port_counter_t dot1dTpPortInDiscards; /**< Rx bridge discards */
} mesa_port_bridge_counters_t;

// Port counters per (PORT, PRIO)
typedef struct {
    mesa_port_counter_t rx; /**< Rx frames */
    mesa_port_counter_t tx; /**< Tx frames */
    mesa_port_counter_t rx_green          CAP(PORT_CNT_EVC); /**< Rx green frames */
    mesa_port_counter_t rx_yellow         CAP(PORT_CNT_EVC); /**< Rx yellow frames */
    mesa_port_counter_t rx_red            CAP(PORT_CNT_EVC); /**< Rx red frames */
    mesa_port_counter_t rx_green_discard  CAP(PORT_CNT_EVC); /**< Rx green discarded frames */
    mesa_port_counter_t rx_yellow_discard CAP(PORT_CNT_EVC); /**< Rx yellow discarded frames */
    mesa_port_counter_t tx_green          CAP(PORT_CNT_EVC); /**< Tx green frames */
    mesa_port_counter_t tx_yellow         CAP(PORT_CNT_EVC); /**< Tx yellow frames */
} mesa_port_prio_counters_t;

/** \brief Port 802.3br counter structure */
typedef struct
{
    mesa_port_counter_t aMACMergeFrameAssErrorCount; /**< Rx counter */
    mesa_port_counter_t aMACMergeFrameSmdErrorCount; /**< Rx counter */
    mesa_port_counter_t aMACMergeFrameAssOkCount;    /**< Rx counter */
    mesa_port_counter_t aMACMergeFragCountRx;        /**< Rx counter */
    mesa_port_counter_t aMACMergeFragCountTx;        /**< Tx counter */
    mesa_port_counter_t aMACMergeHoldCount;          /**< Tx counter */
} mesa_port_dot3br_counters_t;

/** \brief Port counter structure */
typedef struct
{
    mesa_port_rmon_counters_t          rmon;                             /**< RMON counters  */
    mesa_port_if_group_counters_t      if_group;                         /**< Interfaces Group counters  */
    mesa_port_ethernet_like_counters_t ethernet_like;                    /**< Ethernet-like Interface counters */
    mesa_port_bridge_counters_t        bridge;                           /**< Bridge counters */
    mesa_port_prio_counters_t          prio[MESA_PRIO_ARRAY_SIZE];       /**< Priority counters */
    mesa_port_dot3br_counters_t        dot3br CAP(QOS_FRAME_PREEMPTION); /**< 802.3br counters */
} mesa_port_counters_t;

/**
 * \brief Update counters for port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_counters_update(const mesa_inst_t     inst,
                                  const mesa_port_no_t  port_no);



/**
 * \brief Clear counters for port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port/aggregation number.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_counters_clear(const mesa_inst_t     inst,
                                 const mesa_port_no_t  port_no);


/**
 * \brief Get counters for port.
 *
 * \param inst [IN]       Target instance reference.
 * \param port_no [IN]    Port/aggregation number.
 * \param counters [OUT]  Counter structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_counters_get(const mesa_inst_t     inst,
                               const mesa_port_no_t  port_no,
                               mesa_port_counters_t  *const counters);


/** \brief Basic counters structure */
typedef struct
{
    uint32_t rx_frames; /**< Rx frames */
    uint32_t tx_frames; /**< Tx frames */
} mesa_basic_counters_t;

/**
 * \brief Get basic counters for port.
 *
 * \param inst [IN]       Target instance reference.
 * \param port_no [IN]    Port/aggregation number.
 * \param counters [OUT]  Counter structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_basic_counters_get(const mesa_inst_t     inst,
                                     const mesa_port_no_t  port_no,
                                     mesa_basic_counters_t *const counters);


/** \brief Port forwarding state */
typedef enum
{
    MESA_PORT_FORWARD_ENABLED,   /**< Forward in both directions */
    MESA_PORT_FORWARD_DISABLED,  /**< Forwarding and learning disabled */
    MESA_PORT_FORWARD_INGRESS,   /**< Forward frames from port only */
    MESA_PORT_FORWARD_EGRESS     /**< Forward frames to port only (learning disabled) */
} mesa_port_forward_t;

/**
 * \brief Get port forwarding state.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param forward [OUT]  Forwarding state.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_forward_state_get(const mesa_inst_t     inst,
                                    const mesa_port_no_t  port_no,
                                    mesa_port_forward_t   *const forward);

/**
 * \brief Set port forwarding state.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param forward [IN]  Forwarding state.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_forward_state_set(const mesa_inst_t          inst,
                                    const mesa_port_no_t       port_no,
                                    const mesa_port_forward_t  forward);

/** \brief Port Internal Frame Header structure */
typedef struct
{
    /**
     * MESA_ARCH_SERVAL: At ingress expect long prefix followed by an internal
     * frame header
     *
     * MESA_ARCH_JAGUAR_2: At ingress expect short prefix: DMAC:SMAC:0x8880:0007
     * followed by an internal frame header and then the frame
     **/
    mesa_bool_t ena_inj_header CAP(PORT_INJ_HDR);

    /**
     * MESA_ARCH_SERVAL: At egress prepend short prefix: DMAC:SMAC:0x8880:0007
     * (DMAC:SMAC from frame) followed by an internal frame header and then the
     * frame
     * MESA_ARCH_JAGUAR_2: At egress prepend long prefix followed by the
     * internal frame header */
    mesa_bool_t ena_xtr_header CAP(PORT_XTR_HDR);

    /** Same as ena_xtr_header (for compatability with JR1) */
    mesa_bool_t ena_ifh_header CAP(PORT_XTR_HDR);
} mesa_port_ifh_t CAP(PORT_IFH);

/**
 * \brief Set port Internal Frame Header settings.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     Port IFH structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_ifh_conf_set(const mesa_inst_t       inst,
                               const mesa_port_no_t    port_no,
                               const mesa_port_ifh_t  *const conf)
    CAP(PORT_IFH);

/**
 * \brief Get port Internal Frame Header settings.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    Port IFH configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_ifh_conf_get(const mesa_inst_t     inst,
                               const mesa_port_no_t  port_no,
                               mesa_port_ifh_t      *const conf)
    CAP(PORT_IFH);

/**
 * \brief Direct MIIM read (bypassing port map)
 *
 * \param inst            [IN]  Target instance reference.
 * \param chip_no         [IN]  Chip number (if multi-chip instance).
 * \param miim_controller [IN]  MIIM Controller Instance
 * \param miim_addr       [IN]  MIIM Device Address
 * \param addr            [IN]  MIIM Register Address
 * \param value           [OUT] Register value read
 *
 * \return Return code.
 **/
mesa_rc mesa_miim_read(const mesa_inst_t            inst,
                       const mesa_chip_no_t         chip_no,
                       const mesa_miim_controller_t miim_controller,
                       const uint8_t                miim_addr,
                       const uint8_t                addr,
                       uint16_t                     *const value);

/**
 * \brief Direct MIIM write (bypassing port map)
 *
 * \param inst            [IN]  Target instance reference.
 * \param chip_no         [IN]  Chip number (if multi-chip instance).
 * \param miim_controller [IN]  MIIM Controller Instance
 * \param miim_addr       [IN]  MIIM Device Address
 * \param addr            [IN]  MIIM Register Address
 * \param value           [IN]  Register value to write
 *
 * \return Return code.
 **/
mesa_rc mesa_miim_write(const mesa_inst_t            inst,
                        const mesa_chip_no_t         chip_no,
                        const mesa_miim_controller_t miim_controller,
                        const uint8_t                miim_addr,
                        const uint8_t                addr,
                        const uint16_t               value);

/**
 * \brief Read value from MMD register.
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number connected to MMD.
 * \param mmd     [IN]  MMD number.
 * \param addr    [IN]  PHY register address.
 * \param value   [OUT] PHY register value.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_mmd_read(const mesa_inst_t     inst,
                           const mesa_port_no_t  port_no,
                           const uint8_t         mmd,
                           const uint16_t        addr,
                           uint16_t              *const value)
    CAP(PORT_10G);

/**
 * \brief Read values (a number of 16 bit values) from MMD register.
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number connected to MMD.
 * \param mmd     [IN]  MMD number.
 * \param addr    [IN]  PHY register address.
 * \param buf     [OUT] PHY register values.
 * \param count   [IN]  number of values to read.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_mmd_read_inc(const mesa_inst_t     inst,
                               const mesa_port_no_t  port_no,
                               const uint8_t         mmd,
                               const uint16_t        addr,
                               uint16_t              *const buf,
                               uint8_t               count)
    CAP(PORT_10G);

/**
 * \brief Write value to MMD register.
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number connected to MMD.
 * \param mmd     [IN]  MMD number.
 * \param addr    [IN]  PHY register address.
 * \param value   [IN]  PHY register value.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_mmd_write(const mesa_inst_t     inst,
                            const mesa_port_no_t  port_no,
                            const uint8_t         mmd,
                            const uint16_t        addr,
                            const uint16_t        value)
    CAP(PORT_10G);


/**
 * \brief Read, modify and write value to MMD register.
 *
 * \param inst     [IN]  Target instance reference.
 * \param port_no  [IN]  Port number connected to MMD.
 * \param mmd      [IN]  MMD number.
 * \param addr     [IN]  PHY register address.
 * \param value    [IN]  PHY register value.
 * \param mask     [IN]  PHY register mask, only enabled bits are changed.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_mmd_masked_write(const mesa_inst_t     inst,
                                   const mesa_port_no_t  port_no,
                                   const uint8_t         mmd,
                                   const uint16_t        addr,
                                   const uint16_t        value,
                                   const uint16_t        mask)
    CAP(PORT_10G);

/**
 * \brief Direct MMD read (Clause 45, bypassing port map)
 *
 * \param inst            [IN]  Target instance reference.
 * \param chip_no         [IN]  Chip number (if multi-chip instance).
 * \param miim_controller [IN]  MIIM Controller Instance
 * \param miim_addr       [IN]  MIIM Device Address
 * \param mmd             [IN]  MMD number.
 * \param addr            [IN]  MIIM Register Address
 * \param value           [OUT] Register value read
 *
 * \return Return code.
 **/
mesa_rc mesa_mmd_read(const mesa_inst_t            inst,
                      const mesa_chip_no_t         chip_no,
                      const mesa_miim_controller_t miim_controller,
                      const uint8_t                miim_addr,
                      const uint8_t                mmd,
                      const uint16_t               addr,
                      uint16_t                     *const value)
    CAP(PORT_10G);

/**
 * \brief Direct MMD write (Clause 45, bypassing port map)
 *
 * \param inst            [IN]  Target instance reference.
 * \param chip_no         [IN]  Chip number (if multi-chip instance).
 * \param miim_controller [IN]  MIIM Controller Instance
 * \param miim_addr       [IN]  MIIM Device Address
 * \param mmd             [IN]  MMD number.
 * \param addr            [IN]  MIIM Register Address
 * \param value           [IN]  Register value to write
 *
 * \return Return code.
 **/
mesa_rc mesa_mmd_write(const mesa_inst_t            inst,
                       const mesa_chip_no_t         chip_no,
                       const mesa_miim_controller_t miim_controller,
                       const uint8_t                miim_addr,
                       const uint8_t                mmd,
                       const uint16_t               addr,
                       const uint16_t               value)
    CAP(PORT_10G);




/******************************************************************************/
/* 10G KR Backplane Ethernet (version 2, JR2-C and newer)                     */
/******************************************************************************/

/** \brief 10G KR Aneg status */
typedef struct {
    mesa_bool_t complete;            /**< Aneg completed successfully                     */
    mesa_bool_t active;              /**< Aneg is running                                 */
    mesa_bool_t request_10g;         /**< 10G rate is negotiated (needs to be configured) */
    mesa_bool_t request_1g;          /**< 1G rate is negotiated (needs to be configured)  */
    mesa_bool_t request_fec_change;  /**< FEC state change is negotiated (needs to be configured) */
    mesa_bool_t fec_enable;          /**< FEC must be enabled/disabled                    */
    uint32_t    sm;                  /**< (debug) Aneg state machine                      */
    mesa_bool_t lp_aneg_able;        /**< (debug) LP aneg ability                         */
    mesa_bool_t block_lock;          /**< (debug) PCS block lock                          */
} mesa_port_10g_kr_status_aneg_t CAP(PORT_10GBASE_KR_V2);

/** \brief 10G KR Training status */
typedef struct {
    mesa_bool_t complete;            /**< Training completed successfully, tap settings applied.      */
    uint8_t cm_ob_tap_result;        /**< The minus 1 coefficient c(-1). 7-bit signed, range: -32..31 */
    uint8_t cp_ob_tap_result;        /**< The 0 coefficient c(0).        7-bit signed, range: -32..31 */
    uint8_t c0_ob_tap_result;        /**< The plus 1 coefficient c(1).   7-bit signed, range: -32..31 */
} mesa_port_10g_kr_status_train_t CAP(PORT_10GBASE_KR_V2);

typedef struct {
    mesa_bool_t enable;               /**< FEC enabled */
    uint32_t    corrected_block_cnt;  /**< Corrected block count     */
    uint32_t    uncorrected_block_cnt;/**< Un-corrected block count  */
} mesa_port_10g_kr_status_fec_t CAP(PORT_10GBASE_KR_V2);

/** \brief 10G KR Aneg and Training structures */
typedef struct {
    mesa_port_10g_kr_status_aneg_t  aneg;  /**< Aneg structure      */
    mesa_port_10g_kr_status_train_t train; /**< Training structure  */
    mesa_port_10g_kr_status_fec_t   fec;   /**< FEC structure       */
} mesa_port_10g_kr_status_t CAP(PORT_10GBASE_KR_V2);


/** \brief 10G KR Link Advertisement capability config */
typedef struct {
    mesa_bool_t enable;              /**< 10G KR Autoneg enable  */
    mesa_bool_t adv_10g;             /**< Advertise 10G          */
    mesa_bool_t fec_abil;            /**< Advertise FEC ability  */
    mesa_bool_t fec_req;             /**< Advertise FEC request  */
} mesa_port_10g_kr_aneg_t CAP(PORT_10GBASE_KR_V2);

/** \brief 10G KR Training config */
typedef struct {
    mesa_bool_t enable;              /**< Enable 10G KR training, BER method used */
} mesa_port_10g_kr_train_t CAP(PORT_10GBASE_KR_V2);

/** \brief 10G KR configuration structures */
typedef struct {
    mesa_port_10g_kr_aneg_t  aneg;   /**< 10G-KR Aneg capability, 802.3ap Clause 73     */
    mesa_port_10g_kr_train_t train;  /**< 10G-KR Training parameters, 802.3ap Clause 72 */
} mesa_port_10g_kr_conf_t CAP(PORT_10GBASE_KR_V2);


/**
 * \brief Set 10G KR configuration incl. aneg (802.3ap Clause 73) and training (802.3ap Clause 72).
 *  Aneg is started which starts the training process.  The results can be read through mesa_port_10g_kr_status_get().
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]  Configuration structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_10g_kr_conf_set(const mesa_inst_t inst,
                                  const mesa_port_no_t port_no,
                                  const mesa_port_10g_kr_conf_t *const conf)
    CAP(PORT_10GBASE_KR_V2);


/**
 * \brief Get 10G KR configuration
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param conf [OUT]  Configuration structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_10g_kr_conf_get(const mesa_inst_t inst,
                                  const mesa_port_no_t port_no,
                                  mesa_port_10g_kr_conf_t *const conf)
    CAP(PORT_10GBASE_KR_V2);

/**
 * \brief Get 10G KR Aneg and training status
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param status [OUT]  KR Aneg and Training status
 *
 * \return Return code.
 **/
mesa_rc mesa_port_10g_kr_status_get(const mesa_inst_t inst,
                                    const mesa_port_no_t port_no,
                                    mesa_port_10g_kr_status_t *const status)
    CAP(PORT_10GBASE_KR_V2);

/** \brief Port loopback */
typedef enum
{
    MESA_PORT_LB_DISABLED, /**< Loopback disabled */
    MESA_PORT_LB_NEAR_END, /**< Near-end loopback */
    MESA_PORT_LB_FAR_END,  /**< Far-end loopback */
    MESA_PORT_LB_FACILITY, /**< Facility loopback */
    MESA_PORT_LB_EQUIPMENT /**< Equipment loopback */
} mesa_port_lb_t;

/** \brief Port test configuration structure */
typedef struct
{
    mesa_port_lb_t loopback; /**< Loopback type */
} mesa_port_test_conf_t;

/**
 * \brief Get port test configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    Port test configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_test_conf_get(const mesa_inst_t      inst,
                                const mesa_port_no_t   port_no,
                                mesa_port_test_conf_t  *const conf);

/**
 * \brief Set port test configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     Port test configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_port_test_conf_set(const mesa_inst_t            inst,
                                const mesa_port_no_t         port_no,
                                const mesa_port_test_conf_t  *const conf);


#include <mscc/ethernet/switch/api/hdr_end.h>
#endif // _MSCC_ETHERNET_SWITCH_API_PORT_
