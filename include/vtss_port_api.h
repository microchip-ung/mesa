// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/**
 * \file vtss_port_api.h
 * \brief Port API
 */

#ifndef _VTSS_PORT_API_H_
#define _VTSS_PORT_API_H_

#include <vtss/api/port.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \brief MII management controller */
typedef enum
{
#if defined(VTSS_FEATURE_LAYER2)
    VTSS_MIIM_CONTROLLER_0    = 0,  /**< MIIM controller 0 */
    VTSS_MIIM_CONTROLLER_1    = 1,  /**< MIIM controller 1 */
#endif
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    VTSS_MIIM_CONTROLLER_2    = 2,  /**< MIIM controller 2 */
#endif
#if defined(VTSS_ARCH_SPARX5)
    VTSS_MIIM_CONTROLLER_3    = 3,  /**< MIIM controller 3 */
#endif
    VTSS_MIIM_CONTROLLERS,          /**< Number of MIIM controllers */
    VTSS_MIIM_CONTROLLER_NONE = -1  /**< Unassigned MIIM controller */
} vtss_miim_controller_t;

#if defined(VTSS_FEATURE_PORT_CONTROL)

/** \brief The internal bandwidth allocated for the port */
typedef enum
{
    VTSS_BW_DEFAULT,     /**< Default to max port speed */
    VTSS_BW_1G,          /**< Max 1G */
    VTSS_BW_2G5,         /**< Max 2.5G */
    VTSS_BW_5G,          /**< Max 5G */
    VTSS_BW_10G,         /**< Max 10G */
    VTSS_BW_25G,         /**< Max 25G */
    VTSS_BW_UNDEFINED,   /**< Undefined */
} vtss_internal_bw_t;

#define CHIP_PORT_UNUSED -1 /**< Signifies an unused chip port */

/** \brief Port map structure */
typedef struct
{
    i32                    chip_port;        /**< Set to -1 if not used */
    vtss_chip_no_t         chip_no;          /**< Chip number, multi-chip targets */
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    vtss_internal_bw_t     max_bw;           /**< Max internal bandwidth reserved for the port */
#endif /* VTSS_ARCH_JAGUAR_2 || VTSS_ARCH_SPARX5 */
    vtss_miim_controller_t miim_controller;  /**< MII management controller */
    u8                     miim_addr;        /**< PHY address, ignored for VTSS_MIIM_CONTROLLER_NONE */
    vtss_chip_no_t         miim_chip_no;     /**< MII management chip number, multi-chip targets */
} vtss_port_map_t;

/**
 * \brief Set port map.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_map [IN]  Port map array.
 *
 * \return Return code.
 **/
 vtss_rc vtss_port_map_set(const vtss_inst_t     inst,
                           const vtss_port_map_t port_map[VTSS_PORT_ARRAY_SIZE]);

/**
 * \brief Get port map.
 *
 * \param inst [IN]       Target instance reference.
 * \param port_map [OUT]  Port map.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_map_get(const vtss_inst_t  inst,
                          vtss_port_map_t    port_map[VTSS_PORT_ARRAY_SIZE]);

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
    VTSS_PORT_CLAUSE_37_RF_LINK_OK       = ((0<<1) | (0<<0)),   /**< Link OK */
    VTSS_PORT_CLAUSE_37_RF_OFFLINE       = ((1<<1) | (0<<0)),   /**< Off line */
    VTSS_PORT_CLAUSE_37_RF_LINK_FAILURE  = ((0<<1) | (1<<0)),   /**< Link failure */
    VTSS_PORT_CLAUSE_37_RF_AUTONEG_ERROR = ((1<<1) | (1<<0))    /**< Autoneg error */
} vtss_port_clause_37_remote_fault_t;

/** \brief Advertisement control data for Clause 37 aneg */
typedef struct
{
    BOOL                               fdx;               /**< (FD) */
    BOOL                               hdx;               /**< (HD) */
    BOOL                               symmetric_pause;   /**< (PS1) */
    BOOL                               asymmetric_pause;  /**< (PS2) */
    vtss_port_clause_37_remote_fault_t remote_fault;      /**< (RF1) + (RF2) */
    BOOL                               acknowledge;       /**< (Ack) */
    BOOL                               next_page;         /**< (NP) */
} vtss_port_clause_37_adv_t;

/** \brief Advertisement control data for SGMII aneg */
typedef struct
{
    BOOL                               link;              /**< LP link status               */
    BOOL                               fdx;               /**< FD                           */
    BOOL                               hdx;               /**< HD                           */
    BOOL                               speed_10M;         /**< speed 10 advertised          */
    BOOL                               speed_100M;        /**< speed 100 advertised         */
    BOOL                               speed_1G;          /**< speed 1G advertised          */
    BOOL                               aneg_complete;     /**< Aneg process completed       */
} vtss_port_sgmii_aneg_t;


/** \brief Auto-negotiation control parameter struct */
typedef struct
{
    BOOL                      enable;           /**< Enable of Autoneg */
    vtss_port_clause_37_adv_t advertisement;    /**< Clause 37 Advertisement control data */
} vtss_port_clause_37_control_t;

/**
 * \brief Get clause 37 auto-negotiation Control word.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param control [OUT]  Control structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_clause_37_control_get(const vtss_inst_t              inst,
                                        const vtss_port_no_t           port_no,
                                        vtss_port_clause_37_control_t  *const control);



/**
 * \brief Set clause 37 auto-negotiation Control word.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param control [IN]  Control structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_clause_37_control_set(const vtss_inst_t                    inst,
                                        const vtss_port_no_t                 port_no,
                                        const vtss_port_clause_37_control_t  *const control);


/** \brief Flow control setup */
typedef struct
{
    BOOL       obey;            /**< TRUE if 802.3x PAUSE frames should be obeyed */
    BOOL       generate;        /**< TRUE if 802.3x PAUSE frames should generated */
    vtss_mac_t smac;            /**< Port MAC address used as SMAC in PAUSE frames */
#if defined(VTSS_FEATURE_QOS)
    BOOL       pfc[VTSS_PRIOS]; /**< TRUE if 802.1Qbb Priority Flow Control should be generated and obeyed.
                                     Cannot be enabled together with 802.3x Flowcontrol */
#endif
} vtss_port_flow_control_conf_t;

#define VTSS_FRAME_GAP_DEFAULT 0 /**< Default frame gap used */

/** \brief Inter frame gap structure */
typedef struct
{
    u32 hdx_gap_1;      /**< Half duplex: First part of Rx to Tx gap */
    u32 hdx_gap_2;      /**< Half duplex: Second part of Rx to Tx gap */
    u32 fdx_gap;        /**< Full duplex: Tx to Tx gap */
} vtss_port_frame_gaps_t;

/* A selection of max frame lengths */
#define VTSS_MAX_FRAME_LENGTH_STANDARD  1518  /**< IEEE 802.3 standard */
#define VTSS_MAX_FRAME_LENGTH_MAX      10240  /**< Maximum frame length supported */

#if defined(VTSS_ARCH_LUTON26)
#undef VTSS_MAX_FRAME_LENGTH_MAX
#define VTSS_MAX_FRAME_LENGTH_MAX      9600  /**< Maximum frame length supported */
#endif /* VTSS_ARCH_LUTON26 */

#if defined(VTSS_ARCH_SERVAL)
#undef VTSS_MAX_FRAME_LENGTH_MAX
#define VTSS_MAX_FRAME_LENGTH_MAX      10240 /**< Maximum frame length supported */
#endif /* VTSS_ARCH_SERVAL */

#if defined(VTSS_ARCH_JAGUAR_2)
#undef VTSS_MAX_FRAME_LENGTH_MAX
#define VTSS_MAX_FRAME_LENGTH_MAX      10240 /**< Maximum frame length supported */
#endif /* VTSS_ARCH_JAGUAR_2 */

/** \brief VLAN awareness for frame length check */
typedef enum
{
    VTSS_PORT_MAX_TAGS_NONE,  /**< No extra tags allowed */
    VTSS_PORT_MAX_TAGS_ONE,   /**< Single tag allowed */
    VTSS_PORT_MAX_TAGS_TWO    /**< Single and double tag allowed */
} vtss_port_max_tags_t;

/** \brief Port loop back configuration */
typedef enum
{
    VTSS_PORT_LOOP_DISABLE,   /**< No port loop */
    VTSS_PORT_LOOP_PCS_HOST,  /**< PCS host port loop */
} vtss_port_loop_t;

/** \brief Different media/cable types attached to the 10G Serdes */
typedef enum {
    VTSS_SD10G_MEDIA_PR_NONE,    /**< No preset > */
    VTSS_SD10G_MEDIA_SR,         /**< SR, Short Range > */
    VTSS_SD10G_MEDIA_ZR,         /**< ZR, Long Range > */
    VTSS_SD10G_MEDIA_DAC,        /**< DAC (Direct attached copper) cable, unspecified lenght > */
    VTSS_SD10G_MEDIA_DAC_1M,     /**< 1m DAC > */
    VTSS_SD10G_MEDIA_DAC_2M,     /**< 2m DAC > */
    VTSS_SD10G_MEDIA_DAC_3M,     /**< 3m DAC > */
    VTSS_SD10G_MEDIA_DAC_5M,     /**< 5m DAC > */
    VTSS_SD10G_MEDIA_BP,         /**< Backplane > */
    VTSS_SD10G_MEDIA_B2B,        /**< Bord to Board > */
    VTSS_SD10G_MEDIA_10G_KR,     /**< 10G Base KR > */
} vtss_sd10g_media_type_t;

/** \brief SFI Serdes configuration */
typedef struct
{
    BOOL                     sfp_dac;                /**< obsolete (use media_10g)        */
    vtss_sd10g_media_type_t  media_type;             /**< The 10G Serdes media/cable type */
    BOOL                     rx_invert;              /**< Invert the RX Serdes signal (1) */
    BOOL                     tx_invert;              /**< Invert the TX Serdes signal (1) */
} vtss_port_serdes_conf_t;

#if defined(VTSS_FEATURE_PORT_PCS_CONF)
/** \brief 1G PCS specific configuration */
typedef enum
{
    VTSS_PORT_PCS_NORMAL,     /**< Normal 1G PCS configuration    */
    VTSS_PORT_PCS_ENABLE,     /**< Only Enable 1G PCS and return  */
    VTSS_PORT_PCS_DISABLE,    /**< Only Disable 1G PCS and return */
    VTSS_PORT_PCS_IGNORE      /**< Skip any PCS settings          */
} vtss_port_pcs_conf_t;
#endif /* VTSS_FEATURE_PORT_PCS_CONF */

/** \brief Port configuration structure */
typedef struct
{
    vtss_port_interface_t         if_type;           /**< Interface type */
    BOOL                          sd_enable;         /**< Signal detect enable */
    BOOL                          sd_active_high;    /**< External signal detect polarity */
    BOOL                          sd_internal;       /**< Internal signal detect selection */
    vtss_port_frame_gaps_t        frame_gaps;        /**< Inter frame gaps */
    BOOL                          power_down;        /**< Disable and power down the port */
    vtss_port_speed_t             speed;             /**< Port speed */
    BOOL                          fdx;               /**< Full duplex mode */
    vtss_port_flow_control_conf_t flow_control;      /**< Flow control setup */
    u32                           max_frame_length;  /**< Maximum frame length */
    BOOL                          frame_length_chk;  /**< Enforce 802.3 frame length check (from ethertype field) */
    vtss_port_max_tags_t          max_tags;          /**< VLAN awareness for length check */
    BOOL                          exc_col_cont;      /**< Excessive collision continuation */
    BOOL                          xaui_rx_lane_flip; /**< Xaui Rx lane flip */
    BOOL                          xaui_tx_lane_flip; /**< Xaui Tx lane flip */
    vtss_port_loop_t              loop;              /**< Enable/disable of port loop back */
    vtss_port_serdes_conf_t       serdes;            /**< Serdes settings (for SFI interface) */
#if defined(VTSS_FEATURE_PORT_PCS_CONF)
    vtss_port_pcs_conf_t          pcs;               /**< Special 1G PCS settings, only supported for L26 */
#endif
} vtss_port_conf_t;

/**
 * \brief Set port configuration.
 *  Note: If if_type in the vtss_port_conf_t/vtss_port_interface_t definition is set to VTSS_PORT_INTERFACE_QSGMII, the ports are mapped together in groups of four. If one of the four ports is used, all four ports in the group must always be configured, but the four ports doesn't need to configured with the same configuration.
 * This is needed in order to achieve correct comma alignment at the QSGMII interface. Which ports that are mapped together can be found in the chip data-sheet.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     Port setup structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_conf_set(const vtss_inst_t       inst,
                           const vtss_port_no_t    port_no,
                           const vtss_port_conf_t  *const conf);



/**
 * \brief Get port setup.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    Port configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_conf_get(const vtss_inst_t     inst,
                           const vtss_port_no_t  port_no,
                           vtss_port_conf_t      *const conf);


/**
 * \brief Get port status.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param status [OUT]  Status structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_status_get(const vtss_inst_t     inst,
                             const vtss_port_no_t  port_no,
                             vtss_port_status_t    *const status);



/**
 * \brief Update counters for port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_counters_update(const vtss_inst_t     inst,
                                  const vtss_port_no_t  port_no);



/**
 * \brief Clear counters for port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port/aggregation number.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_counters_clear(const vtss_inst_t     inst,
                                 const vtss_port_no_t  port_no);


/**
 * \brief Get counters for port.
 *
 * \param inst [IN]       Target instance reference.
 * \param port_no [IN]    Port/aggregation number.
 * \param counters [OUT]  Counter structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_counters_get(const vtss_inst_t     inst,
                               const vtss_port_no_t  port_no,
                               vtss_port_counters_t  *const counters);


/** \brief Basic counters structure */
typedef struct
{
    u32 rx_frames; /**< Rx frames */
    u32 tx_frames; /**< Tx frames */
} vtss_basic_counters_t;

/**
 * \brief Get basic counters for port.
 *
 * \param inst [IN]       Target instance reference.
 * \param port_no [IN]    Port/aggregation number.
 * \param counters [OUT]  Counter structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_basic_counters_get(const vtss_inst_t     inst,
                                     const vtss_port_no_t  port_no,
                                     vtss_basic_counters_t *const counters);


/** \brief Port forwarding state */
typedef enum
{
    VTSS_PORT_FORWARD_ENABLED,   /**< Forward in both directions */
    VTSS_PORT_FORWARD_DISABLED,  /**< Forwarding and learning disabled */
    VTSS_PORT_FORWARD_INGRESS,   /**< Forward frames from port only */
    VTSS_PORT_FORWARD_EGRESS     /**< Forward frames to port only (learning disabled) */
} vtss_port_forward_t;

/**
 * \brief Get port forwarding state.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param forward [OUT]  Forwarding state.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_forward_state_get(const vtss_inst_t     inst,
                                    const vtss_port_no_t  port_no,
                                    vtss_port_forward_t   *const forward);

/**
 * \brief Set port forwarding state.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param forward [IN]  Forwarding state.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_forward_state_set(const vtss_inst_t          inst,
                                    const vtss_port_no_t       port_no,
                                    const vtss_port_forward_t  forward);

#if defined(VTSS_FEATURE_PORT_IFH)
/** \brief Port Internal Frame Header structure */
typedef struct
{
#if defined(VTSS_ARCH_SERVAL)
    BOOL ena_inj_header; /**< At ingress expect long prefix followed by an internal frame header */
    BOOL ena_xtr_header; /**< At egress prepend long prefix followed by the internal frame header */
#endif /* VTSS_ARCH_SERVAL */

#if defined(VTSS_ARCH_JAGUAR_2)
    BOOL ena_inj_header; /**< At ingress expect short prefix: DMAC:SMAC:0x8880:0007
                              followed by an internal frame header and then the frame */
    BOOL ena_xtr_header; /**< At egress prepend short prefix: DMAC:SMAC:0x8880:0007  (DMAC:SMAC from frame)
                              followed by an internal frame header and then the frame */
    BOOL ena_ifh_header; /**< Same as ena_xtr_header (for compatability with JR1) */
#endif /* VTSS_ARCH_JAGUAR_2 */
} vtss_port_ifh_t;

/**
 * \brief Set port Internal Frame Header settings.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     Port IFH structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_ifh_conf_set(const vtss_inst_t       inst,
                               const vtss_port_no_t    port_no,
                               const vtss_port_ifh_t  *const conf);

/**
 * \brief Get port Internal Frame Header settings.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    Port IFH configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_ifh_conf_get(const vtss_inst_t     inst,
                               const vtss_port_no_t  port_no,
                               vtss_port_ifh_t      *const conf);
#endif /* VTSS_FEATURE_PORT_IFH) */

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
vtss_rc vtss_miim_read(const vtss_inst_t            inst,
                       const vtss_chip_no_t         chip_no,
                       const vtss_miim_controller_t miim_controller,
                       const u8                     miim_addr,
                       const u8                     addr,
                       u16                          *const value);

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
vtss_rc vtss_miim_write(const vtss_inst_t            inst,
                        const vtss_chip_no_t         chip_no,
                        const vtss_miim_controller_t miim_controller,
                        const u8                     miim_addr,
                        const u8                     addr,
                        const u16                    value);
#endif /* VTSS_FEATURE_PORT_CONTROL */

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
vtss_rc vtss_port_mmd_read(const vtss_inst_t     inst,
                           const vtss_port_no_t  port_no,
                           const u8              mmd,
                           const u16             addr,
                           u16                   *const value);
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
vtss_rc vtss_port_mmd_read_inc(const vtss_inst_t     inst,
                               const vtss_port_no_t  port_no,
                               const u8              mmd,
                               const u16             addr,
                               u16                   *const buf,
                               u8                    count);

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
vtss_rc vtss_port_mmd_write(const vtss_inst_t     inst,
                            const vtss_port_no_t  port_no,
                            const u8              mmd,
                            const u16             addr,
                            const u16             value);


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
vtss_rc vtss_port_mmd_masked_write(const vtss_inst_t     inst,
                                   const vtss_port_no_t  port_no,
                                   const u8              mmd,
                                   const u16             addr,
                                   const u16             value,
                                   const u16             mask);

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
vtss_rc vtss_mmd_read(const vtss_inst_t            inst,
                      const vtss_chip_no_t         chip_no,
                      const vtss_miim_controller_t miim_controller,
                      const u8                     miim_addr,
                      const u8                     mmd,
                      const u16                    addr,
                      u16                          *const value);

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
vtss_rc vtss_mmd_write(const vtss_inst_t            inst,
                       const vtss_chip_no_t         chip_no,
                       const vtss_miim_controller_t miim_controller,
                       const u8                     miim_addr,
                       const u8                     mmd,
                       const u16                    addr,
                       const u16                    value);


#if defined(VTSS_FEATURE_10GBASE_KR_V2)
/**
 * ============================================================================
 * 802.3ap 10GBase KR Backplane Ethernet (version 2, JR2-RevC)
 * ============================================================================
 **/

/** \brief 10G KR Aneg status */
typedef struct {
    BOOL complete;            /**< Aneg completed successfully                      */
    BOOL active;              /**< Aneg is running between LD and LP                */
    BOOL request_10g;         /**< 10G rate is negotiated (needs to be configured)  */
    BOOL request_1g;          /**< 1G rate is negotiated (needs to be configured)   */
    BOOL request_fec_change;  /**< FEC enable is negotiated (needs to be enabled)   */
    BOOL fec_enable;          /**< FEC disable is negotiated (needs to be disabled) */
    u32  sm;                  /**< (debug) Aneg state machine                       */
    BOOL lp_aneg_able;        /**< (debug) Link partner aneg ability                */
    BOOL block_lock;          /**< (debug) PCS block lock                           */
} vtss_port_10g_kr_status_aneg_t;

/** \brief 10G KR Training status */
typedef struct {
    BOOL complete;        /**< Training completed successfully               */
    u8 cm_ob_tap_result;  /**< The minus 1 coefficient c(-1). 7-bit signed, range: -32..31 */
    u8 cp_ob_tap_result;  /**< The 0 coefficient c(0).        7-bit signed, range: -32..31 */
    u8 c0_ob_tap_result;  /**< The plus 1 coefficient c(1).   7-bit signed, range: -32..31 */
} vtss_port_10g_kr_status_train_t;

/** \brief 10G KR FEC status */
typedef struct {
    BOOL enable;                /**< FEC Enabled               */
    u32 corrected_block_cnt;    /**< Corrected block count     */
    u32 uncorrected_block_cnt;  /**< Un-corrected block count  */
} vtss_port_10g_kr_status_fec_t;

/** \brief 10G KR Aneg and Training structures */
typedef struct {
    vtss_port_10g_kr_status_aneg_t aneg;   /**< Aneg structure      */
    vtss_port_10g_kr_status_train_t train; /**< Training structure  */
    vtss_port_10g_kr_status_fec_t fec;     /**< FEC structure       */
} vtss_port_10g_kr_status_t;


/** \brief 10G KR Link Advertisement capability config */
typedef struct {
    BOOL enable;           /**< 10G KR Autoneg enable  */
    BOOL adv_10g;          /**< Advertise 10G          */
    BOOL fec_abil;         /**< Set FEC ability        */
    BOOL fec_req;          /**< Set FEC request        */
} vtss_port_10g_kr_aneg_t;

/** \brief 10G KR Training config */
typedef struct {
    BOOL enable;            /**< Enable 10G KR training, BER method used */
} vtss_port_10g_kr_train_t;

/** \brief 10G KR configuration structures */
typedef struct {
    vtss_port_10g_kr_aneg_t  aneg;    /**< 10G-KR Aneg apability, 802.3ap Clause 73      */
    vtss_port_10g_kr_train_t train;   /**< 10G-KR Training parameters, 802.3ap Clause 72 */
} vtss_port_10g_kr_conf_t;


/**
 * \brief Set 10G KR configuration incl. aneg (802.3ap Clause 73) and training (802.3ap Clause 72).
 *
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf    [IN]  Configuration structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_10g_kr_conf_set(const vtss_inst_t inst,
                                  const vtss_port_no_t port_no,
                                  const vtss_port_10g_kr_conf_t *const conf);



/**
 * \brief Get 10G KR configuration
 *
 * \param inst    [IN]   Target instance reference.
 * \param port_no [IN]   Port number.
 * \param conf    [OUT]  Configuration structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_10g_kr_conf_get(const vtss_inst_t inst,
                                  const vtss_port_no_t port_no,
                                  vtss_port_10g_kr_conf_t *const conf);

/**
 * \brief Get 10G KR aneg and training status
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param status  [OUT] KR Aneg and Training status
 *
 * \return Return code.
 **/
vtss_rc vtss_port_10g_kr_status_get(const vtss_inst_t inst,
                                    const vtss_port_no_t port_no,
                                    vtss_port_10g_kr_status_t *const status);


#endif /* VTSS_FEATURE_10GBASE_KR_V2 */


#if defined(VTSS_FEATURE_10GBASE_KR_V3)
/**
 * ============================================================================
 * 802.3ap 25G/10G Base KR Backplane Ethernet (version 3, Sparx5 and newer)
 * ============================================================================
 **/
/** \brief States of the training state machine */
typedef enum {
    VTSS_TR_INITILIZE,
    VTSS_TR_SEND_TRAINING,
    VTSS_TR_TRAIN_LOCAL,
    VTSS_TR_TRAIN_REMOTE,
    VTSS_TR_SEND_DATA,
    VTSS_TR_TRAINING_FAILURE,
    VTSS_TR_LINK_READY
} vtss_train_state_t;

/** \brief States of BER algorithm */
typedef enum {
    VTSS_BER_GO_TO_MIN,
    VTSS_BER_CALCULATE_BER,
    VTSS_BER_MOVE_TO_MID_MARK,
    VTSS_BER_LOCAL_RX_TRAINED
} vtss_ber_stage_t;

/** \brief KR TAPs involved */
typedef enum {
    VTSS_TAP_CM1,
    VTSS_TAP_C0,
    VTSS_TAP_CP1,
} vtss_kr_tap_t;

typedef struct {
    u16 cm1;
    u16 c0;
    u16 cp1;
    u16 coef;
    u16 status;
} vtss_kr_status_results_t;

/** \brief 10G KR state machine structures */
typedef struct {
    vtss_train_state_t current_state;
    vtss_ber_stage_t ber_training_stage;
    vtss_kr_tap_t current_tap;
    BOOL signal_detect;
    BOOL training_started;
    BOOL remote_rx_ready;
    BOOL local_rx_ready;
    BOOL dme_viol_handled;
    BOOL dme_viol;
    BOOL ber_busy;
    BOOL ber_busy_sw;
    BOOL tap_max_reached;
    BOOL receiver_ready_sent;
    BOOL kr_mw_done;
    BOOL ignore_fail;
    vtss_port_speed_t next_parallel_spd;
    u16  lp_tap_max_cnt[3];
    u16  lp_tap_end_cnt[3];
    u32  tap_idx;
    u16  ber_cnt[3][64];
    u16  eye_height[3][64];
    u16  decr_cnt;
    u16  ber_coef_frm;
    vtss_kr_status_results_t tr_res;
} vtss_port_kr_state_t;

/** \brief 10G KR Aneg status */
typedef struct {
    BOOL complete;            /**< Aneg completed successfully                      */
    BOOL active;              /**< Aneg is running between LD and LP                */
    BOOL request_25g;         /**< 25G rate is negotiated (needs to be configured)  */
    BOOL request_10g;         /**< 10G rate is negotiated (needs to be configured)  */
    BOOL request_5g;          /**< 5G rate is negotiated (needs to be configured)   */
    BOOL request_2g5;         /**< 2G5 rate is negotiated (needs to be configured)  */
    BOOL request_1g;          /**< 1G rate is negotiated (needs to be configured)   */
    BOOL request_fec_change;  /**< FEC enable is negotiated (needs to be enabled)   */
    BOOL fec_enable;          /**< FEC disable is negotiated (needs to be disabled) */
    u32  sts1;
    u32  sm;                  /**< (debug) Aneg state machine                       */
    BOOL lp_aneg_able;        /**< (debug) Link partner aneg ability                */
    BOOL block_lock;          /**< (debug) PCS block lock                           */
} vtss_port_kr_status_aneg_t;

/** \brief 10G KR Training status */
typedef struct {
    BOOL complete;        /**< Training completed successfully               */
    u8 cm_ob_tap_result;  /**< The minus 1 coefficient c(-1). 7-bit signed, range: -32..31 */
    u8 cp_ob_tap_result;  /**< The 0 coefficient c(0).        7-bit signed, range: -32..31 */
    u8 c0_ob_tap_result;  /**< The plus 1 coefficient c(1).   7-bit signed, range: -32..31 */
    u32 frame_sent;
    u16 frame_errors;
} vtss_port_kr_status_train_t;

/** \brief 10G KR FEC status */
typedef struct {
    BOOL enable;                /**< FEC Enabled               */
    u32 corrected_block_cnt;    /**< Corrected block count     */
    u32 uncorrected_block_cnt;  /**< Un-corrected block count  */
} vtss_port_kr_status_fec_t;

typedef struct {
    u32 vector;
} vtss_port_kr_status_irq_t;

/** \brief 10G KR Aneg and Training structures */
typedef struct {
    vtss_port_kr_status_aneg_t aneg;   /**< Aneg structure      */
    vtss_port_kr_status_train_t train; /**< Training structure  */
    vtss_port_kr_status_fec_t fec;     /**< FEC structure       */
    vtss_port_kr_status_irq_t irq;     /**< IRQ Vector         */
} vtss_port_kr_status_t;


/** \brief 10G KR Link Advertisement capability config */
typedef struct {
    BOOL enable;           /**< 10G KR Autoneg enable  */
    BOOL adv_25g;          /**< Advertise 25G          */
    BOOL adv_10g;          /**< Advertise 10G          */
    BOOL adv_5g;           /**< Advertise 5G           */
    BOOL adv_2g5;          /**< Advertise 2G5          */
    BOOL adv_1g;           /**< Advertise 1G           */
    BOOL fec_abil;         /**< Set FEC ability        */
    BOOL fec_req;          /**< Set FEC request        */
} vtss_port_kr_aneg_t;

/** \brief 10G KR Training config */
typedef struct {
    BOOL enable;            /**< Enable 10G KR training, BER method used */
    BOOL eye_diag;          /**< Use eye diagram for calculation if height instead of chip calculation */
} vtss_port_kr_train_t;

/** \brief 10G KR configuration structures */
typedef struct {
    vtss_port_kr_aneg_t   aneg;    /**< 10G-KR Aneg apability, 802.3ap Clause 73      */
    vtss_port_kr_train_t  train;   /**< 10G-KR Training parameters, 802.3ap Clause 72 */
} vtss_port_kr_conf_t;

#define KR_ACTV            (1 << 29)
#define KR_LPSVALID        (1 << 28)
#define KR_LPCVALID        (1 << 27)
#define KR_WT_DONE         (1 << 26)
#define KR_MW_DONE         (1 << 25)
#define KR_BER_BUSY_0      (1 << 24)
#define KR_BER_BUSY_1      (1 << 23)
#define KR_REM_RDY_0       (1 << 22)
#define KR_REM_RDY_1       (1 << 21)
#define KR_FRLOCK_0        (1 << 20)
#define KR_FRLOCK_1        (1 << 19)
#define KR_DME_VIOL_0      (1 << 18)
#define KR_DME_VIOL_1      (1 << 17)
#define KR_AN_XMIT_DISABLE (1 << 16)
#define KR_TRAIN           (1 << 15)
#define KR_RATE_DET        (1 << 14)
#define KR_CMPL_ACK        (1 << 13)
#define KR_AN_GOOD         (1 << 12)
#define KR_LINK_FAIL       (1 << 11)
#define KR_ABD_FAIL        (1 << 10)
#define KR_ACK_FAIL        (1 << 9)
#define KR_NP_FAIL         (1 << 8)
#define KR_NP_RX           (1 << 7)
#define KR_INCP_LINK       (1 << 6)
#define KR_GEN0_DONE       (1 << 5)
#define KR_GEN1_DONE       (1 << 4)
#define KR_AN_RATE         (0xF)


/**
 * \brief Set 10G KR configuration incl. aneg (802.3ap Clause 73) and training (802.3ap Clause 72).
 *
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf    [IN]  Configuration structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_kr_conf_set(const vtss_inst_t inst,
                                  const vtss_port_no_t port_no,
                                  const vtss_port_kr_conf_t *const conf);

/**
 * \brief Get 10G KR configuration
 *
 * \param inst    [IN]   Target instance reference.
 * \param port_no [IN]   Port number.
 * \param conf    [OUT]  Configuration structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_kr_conf_get(const vtss_inst_t inst,
                                  const vtss_port_no_t port_no,
                                  vtss_port_kr_conf_t *const conf);

/**
 * \brief Get 10G KR aneg and training status
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param status  [OUT] KR Aneg and Training status
 *
 * \return Return code.
 **/
vtss_rc vtss_port_kr_status_get(const vtss_inst_t inst,
                                    const vtss_port_no_t port_no,
                                    vtss_port_kr_status_t *const status);

/**
 * \brief Get 10G KR state machine status
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param status  [OUT] KR Aneg and Training status
 *
 * \return Return code.
 **/
vtss_rc vtss_port_kr_state_get(const vtss_inst_t inst,
                               const vtss_port_no_t port_no,
                               vtss_port_kr_state_t *const state);


/**
 * \brief Apply KR interrupt 
 *
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param irq    [IN]  interrupt id.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_kr_irq_apply(const vtss_inst_t inst,
                               const vtss_port_no_t port_no,
                               const u32 *const irq);


/**
 * ============================================================================
 * 802.3ap 25G/10G Base KR Backplane Ethernet - End
 * ============================================================================
 **/

#endif /* VTSS_FEATURE_10GBASE_KR_V3 */

/** \brief Port loopback */
typedef enum
{
    VTSS_PORT_LB_DISABLED, /**< Loopback disabled */
    VTSS_PORT_LB_NEAR_END, /**< Near-end loopback */
    VTSS_PORT_LB_FAR_END,  /**< Far-end loopback */
    VTSS_PORT_LB_FACILITY, /**< Facility loopback */
    VTSS_PORT_LB_EQUIPMENT /**< Equipment loopback */
} vtss_port_lb_t;

/** \brief Port test configuration structure */
typedef struct
{
    vtss_port_lb_t loopback; /**< Loopback type */
} vtss_port_test_conf_t;

/**
 * \brief Get port test configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [OUT]    Port test configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_test_conf_get(const vtss_inst_t      inst,
                                const vtss_port_no_t   port_no,
                                vtss_port_test_conf_t  *const conf);

/**
 * \brief Set port test configuration.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     Port test configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_test_conf_set(const vtss_inst_t            inst,
                                const vtss_port_no_t         port_no,
                                const vtss_port_test_conf_t  *const conf);

/** \brief Serdes Tx taps */
typedef enum
{
    VTSS_SERDES_PRE_CURSOR,
    VTSS_SERDES_MAIN_CURSOR,
    VTSS_SERDES_POST_CURSOR,
} vtss_port_serdes_tap_enum_t;


/**
 * \brief Function pointer for API callout.
          This function will typically be implemented in MEBA were the board specifics are known.
          The purpose is to get the tap value for a specific port/speed/tap.
 * \param port_no [IN]  Port number.
 * \param speed [IN]    Port speed.
 * \param tap [IN]      Pre/main/post tap.
 * \param value [OUT]   The register value to be written.

 * \return Return code.
 *
 **/
typedef vtss_rc (*vtss_port_serdes_tap_get_t)(const vtss_inst_t                 inst,
                                              const vtss_port_no_t              port_no,
                                              const vtss_port_speed_t           speed,
                                              const vtss_port_serdes_tap_enum_t tap,
                                              u32                               *const value);

/** \brief Serdes debug parameters */
typedef enum
{
    VTSS_SERDES_DFE_PRM,  /**< DFE prms. in this order : h1,h2,h3,h4,h5,dlev */
    VTSS_SERDES_CTLE_PRM, /**< CTLE prms. in this order: r,c,vga */
    VTSS_SERDES_TXEQ_PRM, /**< TxEQ prms. in this order: tap_dly, tap_adv, amplitude */
} vtss_serdes_debug_type_t;

/** \brief Serdes debug configuration structure */
typedef struct
{
    vtss_serdes_debug_type_t debug_type;
    u32                      serdes_prm[10]; /**< Depends on debug_type */
} vtss_port_serdes_debug_t;

/**
 * \brief Used for Serdes debugging.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param conf [IN]     Serdes test configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_port_serdes_debug_set(const vtss_inst_t              inst,
                                   const vtss_port_no_t           port_no,
                                   const vtss_port_serdes_debug_t *const conf);




#ifdef __cplusplus
}
#endif
#endif /* _VTSS_PORT_API_H_ */
