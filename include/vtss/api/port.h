// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_PORT_TYPES_H_
#define _VTSS_PORT_TYPES_H_

#include <vtss/api/types.h>
#include <vtss/api/phy.h>

/**
 * \file
 * \brief Port Public API Header
 * \details This header file describes public port data-types
 */

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/* Port Counters                                                              */
/******************************************************************************/

/** \brief Counter type */
typedef u64 vtss_port_counter_t;

/** \brief RMON counter structure (RFC 2819) */
typedef struct {
    vtss_port_counter_t rx_etherStatsDropEvents;           /**< Rx drop events */
    vtss_port_counter_t rx_etherStatsOctets;               /**< Rx octets */
    vtss_port_counter_t rx_etherStatsPkts;                 /**< Rx packets */
    vtss_port_counter_t rx_etherStatsBroadcastPkts;        /**< Rx broadcasts */
    vtss_port_counter_t rx_etherStatsMulticastPkts;        /**< Rx multicasts */
    vtss_port_counter_t rx_etherStatsCRCAlignErrors;       /**< Rx CRC/alignment errors */
    vtss_port_counter_t rx_etherStatsUndersizePkts;        /**< Rx undersize packets */
    vtss_port_counter_t rx_etherStatsOversizePkts;         /**< Rx oversize packets */
    vtss_port_counter_t rx_etherStatsFragments;            /**< Rx fragments */
    vtss_port_counter_t rx_etherStatsJabbers;              /**< Rx jabbers */
    vtss_port_counter_t rx_etherStatsPkts64Octets;         /**< Rx 64 byte packets */
    vtss_port_counter_t rx_etherStatsPkts65to127Octets;    /**< Rx 65-127 byte packets */
    vtss_port_counter_t rx_etherStatsPkts128to255Octets;   /**< Rx 128-255 byte packets */
    vtss_port_counter_t rx_etherStatsPkts256to511Octets;   /**< Rx 256-511 byte packets */
    vtss_port_counter_t rx_etherStatsPkts512to1023Octets;  /**< Rx 512-1023 byte packet */
    vtss_port_counter_t rx_etherStatsPkts1024to1518Octets; /**< Rx 1024-1518 byte packets */
    vtss_port_counter_t rx_etherStatsPkts1519toMaxOctets;  /**< Rx 1519- byte packets */

    vtss_port_counter_t tx_etherStatsDropEvents;           /**< Tx drop events */
    vtss_port_counter_t tx_etherStatsOctets;               /**< Tx octets */
    vtss_port_counter_t tx_etherStatsPkts;                 /**< Tx packets */
    vtss_port_counter_t tx_etherStatsBroadcastPkts;        /**< Tx broadcasts */
    vtss_port_counter_t tx_etherStatsMulticastPkts;        /**< Tx multicasts */
    vtss_port_counter_t tx_etherStatsCollisions;           /**< Tx collisions */
    vtss_port_counter_t tx_etherStatsPkts64Octets;         /**< Tx 64 byte packets */
    vtss_port_counter_t tx_etherStatsPkts65to127Octets;    /**< Tx 65-127 byte packets */
    vtss_port_counter_t tx_etherStatsPkts128to255Octets;   /**< Tx 128-255 byte packets */
    vtss_port_counter_t tx_etherStatsPkts256to511Octets;   /**< Tx 256-511 byte packets */
    vtss_port_counter_t tx_etherStatsPkts512to1023Octets;  /**< Tx 512-1023 byte packet */
    vtss_port_counter_t tx_etherStatsPkts1024to1518Octets; /**< Tx 1024-1518 byte packets */
    vtss_port_counter_t tx_etherStatsPkts1519toMaxOctets;  /**< Tx 1519- byte packets */
} vtss_port_rmon_counters_t;

/** \brief Interfaces Group counter structure (RFC 2863) */
typedef struct {
    vtss_port_counter_t ifInOctets;          /**< Rx octets */
    vtss_port_counter_t ifInUcastPkts;       /**< Rx unicasts */
    vtss_port_counter_t ifInMulticastPkts;   /**< Rx multicasts */
    vtss_port_counter_t ifInBroadcastPkts;   /**< Rx broadcasts */
    vtss_port_counter_t ifInNUcastPkts;      /**< Rx non-unicasts */
    vtss_port_counter_t ifInDiscards;        /**< Rx discards */
    vtss_port_counter_t ifInErrors;          /**< Rx errors */

    vtss_port_counter_t ifOutOctets;         /**< Tx octets */
    vtss_port_counter_t ifOutUcastPkts;      /**< Tx unicasts */
    vtss_port_counter_t ifOutMulticastPkts;  /**< Tx multicasts */
    vtss_port_counter_t ifOutBroadcastPkts;  /**< Tx broadcasts */
    vtss_port_counter_t ifOutNUcastPkts;     /**< Tx non-unicasts */
    vtss_port_counter_t ifOutDiscards;       /**< Tx discards */
    vtss_port_counter_t ifOutErrors;         /**< Tx errors */
} vtss_port_if_group_counters_t;

/** \brief Ethernet-like Interface counter structure (RFC 3635) */
typedef struct {
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    vtss_port_counter_t dot3StatsAlignmentErrors;          /**< Rx alignment errors */
    vtss_port_counter_t dot3StatsFCSErrors;                /**< Rx FCS errors */
    vtss_port_counter_t dot3StatsFrameTooLongs;            /**< Rx too long */
    vtss_port_counter_t dot3StatsSymbolErrors;             /**< Rx symbol errors */
    vtss_port_counter_t dot3ControlInUnknownOpcodes;       /**< Rx unknown opcodes */
#endif /* VTSS_FEATURE_PORT_CNT_ETHER_LIKE */
    vtss_port_counter_t dot3InPauseFrames;                 /**< Rx pause */

#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    vtss_port_counter_t dot3StatsSingleCollisionFrames;    /**< Tx single collisions */
    vtss_port_counter_t dot3StatsMultipleCollisionFrames;  /**< Tx multiple collisions */
    vtss_port_counter_t dot3StatsDeferredTransmissions;    /**< Tx deferred */
    vtss_port_counter_t dot3StatsLateCollisions;           /**< Tx late collisions */
    vtss_port_counter_t dot3StatsExcessiveCollisions;      /**< Tx excessive collisions */
    vtss_port_counter_t dot3StatsCarrierSenseErrors;       /**< Tx carrier sense errors */
#endif /* VTSS_FEATURE_PORT_CNT_ETHER_LIKE */
    vtss_port_counter_t dot3OutPauseFrames;                /**< Tx pause */
} vtss_port_ethernet_like_counters_t;

#if defined(VTSS_ARCH_CARACAL)
/** \brief EVC counters */
typedef struct
{
#if defined(VTSS_FEATURE_QOS)
    vtss_port_counter_t rx_green[VTSS_PRIOS];          /**< Rx green frames */
    vtss_port_counter_t rx_yellow[VTSS_PRIOS];         /**< Rx yellow frames */
    vtss_port_counter_t rx_red[VTSS_PRIOS];            /**< Rx red frames */
    vtss_port_counter_t rx_green_discard[VTSS_PRIOS];  /**< Rx green discarded frames */
    vtss_port_counter_t rx_yellow_discard[VTSS_PRIOS]; /**< Rx yellow discarded frames */
    vtss_port_counter_t tx_green[VTSS_PRIOS];          /**< Tx green frames */
    vtss_port_counter_t tx_yellow[VTSS_PRIOS];         /**< Tx yellow frames */
#endif
} vtss_port_evc_counters_t;
#endif /* VTSS_ARCH_CARACAL */

/** \brief Port bridge counter structure (RFC 4188) */
typedef struct
{
    vtss_port_counter_t dot1dTpPortInDiscards; /**< Rx bridge discards */
} vtss_port_bridge_counters_t;

/** \brief Port proprietary counter structure */
typedef struct
{
#if defined(VTSS_FEATURE_PORT_CONTROL)
    vtss_port_counter_t rx_prio[VTSS_PRIOS];        /**< Rx frames */
    vtss_port_counter_t tx_prio[VTSS_PRIOS];        /**< Tx frames */
#endif
} vtss_port_proprietary_counters_t;

/** \brief Port 802.3br counter structure */
typedef struct
{
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    vtss_port_counter_t aMACMergeFrameAssErrorCount; /**< Rx counter */
    vtss_port_counter_t aMACMergeFrameSmdErrorCount; /**< Rx counter */
    vtss_port_counter_t aMACMergeFrameAssOkCount;    /**< Rx counter */
    vtss_port_counter_t aMACMergeFragCountRx;        /**< Rx counter */
    vtss_port_counter_t aMACMergeFragCountTx;        /**< Tx counter */
    vtss_port_counter_t aMACMergeHoldCount;          /**< Tx counter */
#endif /* VTSS_FEATURE_QOS_FRAME_PREEMPTION */
} vtss_port_dot3br_counters_t;

/** \brief Port counter structure */
typedef struct
{
    vtss_port_rmon_counters_t          rmon;           /**< RMON counters  */
    vtss_port_if_group_counters_t      if_group;       /**< Interfaces Group counters  */
    vtss_port_ethernet_like_counters_t ethernet_like;  /**< Ethernet-like Interface counters */

#if defined(VTSS_FEATURE_PORT_CNT_BRIDGE)
    vtss_port_bridge_counters_t        bridge;         /**< Bridge counters */
#endif /* VTSS_FEATURE_PORT_CNT_BRIDGE */

    vtss_port_proprietary_counters_t   prop;           /**< Proprietary counters */

#if defined(VTSS_ARCH_CARACAL)
    vtss_port_evc_counters_t           evc;            /**< EVC counters */
#endif /* VTSS_ARCH_CARACAL */

#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    vtss_port_dot3br_counters_t        dot3br;         /**< Dot3br counters */
#endif /* VTSS_FEATURE_QOS_FRAME_PREEMPTION */

} vtss_port_counters_t;

/******************************************************************************/
/* Port Speed                                                                 */
/******************************************************************************/

/** \brief Port speed */
typedef enum
{
    VTSS_SPEED_UNDEFINED,   /**< Undefined */
    VTSS_SPEED_10M,         /**< 10 M */
    VTSS_SPEED_100M,        /**< 100 M */
    VTSS_SPEED_1G,          /**< 1 G */
    VTSS_SPEED_2500M,       /**< 2.5G */
    VTSS_SPEED_5G,          /**< 5G or 2x2.5G */
    VTSS_SPEED_10G,         /**< 10 G */
    VTSS_SPEED_12G,         /**< 12G */
    VTSS_SPEED_25G,         /**< 25G */
    VTSS_SPEED_AUTO
} vtss_port_speed_t;

/** \brief Fiber Port speed */
typedef enum
{
    VTSS_SPEED_FIBER_NOT_SUPPORTED_OR_DISABLED = 0, /**< Fiber not supported/ Fiber port disabled */
    VTSS_SPEED_FIBER_100FX = 2,       /**< 100BASE-FX*/
    VTSS_SPEED_FIBER_1000X = 3,       /**< 1000BASE-X*/
    VTSS_SPEED_FIBER_AUTO = 4,        /**< Auto detection - AMS mode*/
    VTSS_SPEED_FIBER_DISABLED = 5,    /**< Obsolete - use VTSS_SPEED_FIBER_NOT_SUPPORTED_OR_DISABLED instead*/
    VTSS_SPEED_FIBER_ONLY_AUTO = 6,   /**< Auto detection - Fiber only (no RJ45)*/
} vtss_fiber_port_speed_t;

/******************************************************************************/
/* Port configuration                                                         */
/******************************************************************************/

/******************************************************************************/
/* Port status                                                                */
/******************************************************************************/

/** \brief Port status parameter struct */
typedef struct
{
    vtss_event_t      link_down;       /**< Link down event occurred since last call */
    BOOL              link;            /**< Link is up. Remaining fields only valid if TRUE */
    vtss_port_speed_t speed;           /**< Speed */
    BOOL              fdx;             /**< Full duplex */
    BOOL              remote_fault;    /**< Remote fault signalled */
    BOOL              aneg_complete;   /**< Autoneg completed (for clause_37 and Cisco aneg) */
    BOOL              unidirectional_ability; /**<TRUE: PHY able to transmit from media independent interface regardless of whether the PHY has
                                                 determined that a valid link has been established.FALSE: PHY able to transmit from media
                                                 independent interface only when the PHY has determined that a valid link has been established.
                                                 Note This bit is only applicable to 100BASE-FX and 1000BASE-X fiber media modes.*/
    vtss_aneg_t aneg;                  /**< Auto negotiation result */
    BOOL mdi_cross;                    /**< Indication of if Auto-MDIX crossover is performed */
    BOOL fiber;                        /**< Indication of if the link is a fiber link, TRUE if link is a fiber link. FALSE if link is cu link or No Media */
    BOOL copper;                       /**< Indication of if the link is a copper link, TRUE if link is a copper link. FALSE if link is fiber link or No Media */
} vtss_port_status_t;

#ifdef __cplusplus
}
#endif

#endif /* #define _VTSS_PORT_TYPES_H_ */
