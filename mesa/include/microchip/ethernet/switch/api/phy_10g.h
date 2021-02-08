// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

// Microchip is aware that some terminology used in this technical document is
// antiquated and inappropriate. As a result of the complex nature of software
// where seemingly simple changes have unpredictable, and often far-reaching
// negative results on the software's functionality (requiring extensive
// retesting and revalidation) we are unable to make the desired changes in all
// legacy systems without compromising our product or our clients' products.


#ifndef _MICROCHIP_ETHERNET_SWITCH_API_PHY_10G_
#define _MICROCHIP_ETHERNET_SWITCH_API_PHY_10G_

#include <microchip/ethernet/switch/api/misc.h>
#include <microchip/ethernet/switch/api/types.h>
#include <microchip/ethernet/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

/** \brief 10G Phy operating mode enum type */
typedef enum {
    MESA_PHY_LAN_MODE,          /**< LAN mode: Single clock (XREFCK=156,25 MHz), no recovered clock output  */
    MESA_PHY_WAN_MODE,          /**< WAN mode:\n */
                                /**< 848X:   Dual clock (XREFCK=156,25 MHz, WREFCK=155,52 MHz), no recovered clock output\n */
                                /**< Venice: Single clock (XREFCK), no recovered clock output\n */
    MESA_PHY_1G_MODE,           /**< 8488:   1G pass-through mode\n */
    /**< Venice: 1G mode, Single clock (XREFCK=156,25 MHz), no recovered clock output */
    MESA_PHY_LAN_SYNCE_MODE,    /**< LAN SyncE:\n */
                                /**< if hl_clk_synth == 1:\n */
                                /**< 8488:   Single clock (XREFCK=156,25 MHz), recovered clock output enabled\n */
                                /**< Venice: Single clock (XREFCK=156,25 MHz), recovered clock output enabled\n */
                                /**< if hl_clk_synth == 0:\n */
                                /**< 8488:   Dual clock (XREFCK=156,25 MHz, SREFCK=156,25 MHz), recovered clock output enabled\n */
                                /**< Venice: Dual clock (XREFCK=156,25 MHz, SREFCK=156,25 MHz), recovered clock output enabled\n */
    MESA_PHY_WAN_SYNCE_MODE,    /**< WAN SyncE:\n */
                                /**< if hl_clk_synth == 1:\n */
                                /**< 8488:   Single clock (WREFCK=155,52 MHz or 622,08 MHz), recovered clock output enabled\n */
                                /**< Venice: Single clock (XREFCK=156,25 MHz), recovered clock output enabled\n */
                                /**< if hl_clk_synth == 0:\n */
                                /**< 8488:   Dual clock (WREFCK=155,52 MHz or 622,08 MHz, SREFCK=155,52 MHz), recovered clock output enabled\n */
                                /**< Venice: Dual clock (XREFCK=156,25 MHz, SREFCK=155,52 MHz), recovered clock output enabled\n */
    MESA_PHY_LAN_MIXED_SYNCE_MODE, /**< 8488:   Channels are in different modes, channel being configured is in LAN\n */
                                   /**< Venice: Same as MESA_PHY_LAN_SYNCE_MODE */
    MESA_PHY_WAN_MIXED_SYNCE_MODE, /**< 8488:   Channels are in different modes, channel being configured is in WAN\n */
                                   /**< Venice: Same as MESA_PHY_WAN_SYNCE_MODE */
    MESA_PHY_REPEATER_MODE,    /**< Malibu: Repeater mode,better jitter performance  */
} mesa_oper_mode_t CAP(PHY_10G);

/** \brief Modes for WAN reference clock */
typedef enum {
    MESA_WREFCLK_155_52, /**< WREFCLK = 155.52Mhz - WAN ref clock */
    MESA_WREFCLK_622_08  /**< WREFCLK = 622.08Mhz - WAN ref clock */
} mesa_wrefclk_t CAP(PHY_10G);

/** \brief 10G Phy link and fault status */
typedef struct {
    mesa_bool_t  rx_link;   /**< The rx link status  */
    mesa_event_t link_down; /**< Link down event status. Clear on read  */
    mesa_bool_t  rx_fault;  /**< Rx fault event status.  Clear on read */
    mesa_bool_t  tx_fault;  /**< Tx fault event status.  Clear on read */
} mesa_sublayer_status_t CAP(PHY_10G);

/** \brief Phy Interface modes */
typedef enum {
    MESA_PHY_XAUI_XFI,         /**< XAUI  <-> XFI - Interface mode. */
    MESA_PHY_XGMII_XFI,        /**< XGMII <-> XFI - Interface mode. Only for VSC8486 */
    MESA_PHY_RXAUI_XFI,        /**< RXAUI <-> XFI - Interface mode. Only for Venice */
    MESA_PHY_SGMII_LANE_0_XFI, /**< SGMII <-> XFI - LANE 0. Only for Venice */
    MESA_PHY_SGMII_LANE_3_XFI, /**< SGMII <-> XFI - LANE 3. Only for Venice */
    MESA_PHY_SFI_XFI,          /**< SFI   <-> XFI - Interface mode. Only for Malibu*/
} mesa_phy_interface_mode;

/** \brief Modes for recovered clock */
typedef enum {
    MESA_RECVRD_RXCLKOUT, /**< RXCLKOUT is used for recovered clock */
    MESA_RECVRD_TXCLKOUT, /**< TXCLKOUT is used for recovered clock */
} mesa_recvrd_t CAP(PHY_10G); /**< RXCLKOUT/TXCLKOUT used as recovered clock */

/** \brief Modes for recovered clock divisor */
typedef enum {
    MESA_RECVRDCLK_CDR_DIV_64, /**< recovered clock is /64 */
    MESA_RECVRDCLK_CDR_DIV_66, /**< recovered clock is /66 */
} mesa_recvrdclk_cdr_div_t CAP(PHY_10G); /**< 8488 only: recovered clock's divisor */

/** \brief Modes for Synch-E recovered clock */
typedef enum {
    MESA_SREFCLK_DIV_64, /**< SREFCLK/64 ,valid for LAN,WAN */
    MESA_SREFCLK_DIV_66, /**< SREFCLK/66 ,valid for LAN */
    MESA_SREFCLK_DIV_16, /**< SREFCLK/16 ,valid for WAN */
} mesa_srefclk_div_t CAP(PHY_10G); /**< 8488 only: SRERCLK divisor, If one channel gets SREF clock,  */
                                   /**< then other channel has to use external hitless clock for SYNCE support */

/** \brief Modes for WREFCLK clock divisor */
typedef enum {
    MESA_WREFCLK_NONE,   /**< NA */
    MESA_WREFCLK_DIV_16, /**< WREFCLK/16 */
} mesa_wref_clk_div_t CAP(PHY_10G); /**< 8488 only: WREFCLK divisor */
                                    /**< This should be of same value for both the channels if they are configured in MIXED mode */

/** \brief APC Rx regulator mode  */
typedef enum {
    MESA_APC_IB_SFP_PLUS_ZR, /**< SFP+ ZR module.                                                  */
    MESA_APC_IB_BACKPLANE,   /**< Backplane application.                                           */
} mesa_apc_ib_regulator_t CAP(PHY_10G); /**< Analog Parameter Control / IB equalizer  (only for Venice family)*/

/** \brief Interleave mode */
typedef enum {
    MESA_DDR_MODE_A, /**< Interleave mode with A alignment symbol based byte re-ordering */
    MESA_DDR_MODE_K, /**< Interleave mode with K coma based byte re-ordering             */
    MESA_DDR_MODE_M, /**< Interleave mode with A alignment and 8b10b decoding disabled   */
} mesa_ddr_mode_t CAP(PHY_10G);              /**< Interleave mode combinations supported.                        */

/** \brief Clock Primary */
typedef enum {
    MESA_CLK_MSTR_INTERNAL, /**< Primary clock is internal */
    MESA_CLK_MSTR_EXTERNAL, /**< Primary clock is external */
} mesa_clk_mstr_t CAP(PHY_10G);

/** \brief Repeater Data rate */
typedef enum {
    MESA_RPTR_RATE_NONE,    /**< None                              */
    MESA_RPTR_RATE_10_3125, /**< LAN rate=10.3125 Gbps,            */
    MESA_RPTR_RATE_9_9532,  /**< WAN rate=9.9532 Gbps              */
    MESA_RPTR_RATE_11_3,    /**< rate=11.3 Gbps,clock 171Mhz       */
    MESA_RPTR_RATE_10_5187, /**< Fiber channel rate=10.51875 Gbps, */
    MESA_RPTR_RATE_1_25,    /**< 1G rate=1.25Gbps                  */
    MESA_RPTR_RATE_10_709,  /**< OTU2 rate= 10.709 Gbps            */
    MESA_RPTR_RATE_11_095727, /**< OTU2E rate = 11.095727 Gbps       */
    MESA_RPTR_RATE_11_05,     /**< OTU1E rate = 11.05 Gbps           */
} mesa_rptr_rate_t CAP(PHY_10G);

/** \brief 10G Phy Polarity inversion */
typedef struct {
    mesa_bool_t line_rx; /**< Line side Receive path*/
    mesa_bool_t line_tx; /**< Line side Transmit path*/
    mesa_bool_t host_rx; /**< Host side Receive path*/
    mesa_bool_t host_tx; /**< Host side Transmit path*/
} mesa_phy_10g_polarity_inv_t CAP(PHY_10G);

/** \brief 10G Phy Media type */
typedef enum {
    MESA_MEDIA_TYPE_SR,     /**< SR,10GBASE-SR */
    MESA_MEDIA_TYPE_SR2,    /**< SR,10GBASE-SR */
    MESA_MEDIA_TYPE_DAC,    /**< DAC,Direct attach cable */
    MESA_MEDIA_TYPE_ZR,     /**< ZR,10GBASE-ZR */
    MESA_MEDIA_TYPE_KR,     /**< KR,10GBASE-KR */
    MESA_MEDIA_TYPE_SR_SC,  /**< SR,10GBASE-SR with software control*/
    MESA_MEDIA_TYPE_SR2_SC, /**< SR,10GBASE-SR with software control*/
    MESA_MEDIA_TYPE_DAC_SC, /**< DAC,Direct attach cable with software control*/
    MESA_MEDIA_TYPE_ZR_SC,  /**< ZR,10GBASE-ZR with software control*/
    MESA_MEDIA_TYPE_ZR2_SC, /**< ZR,10GBASE-ZR with software control with ld_lev_ini:40*/
    MESA_MEDIA_TYPE_KR_SC,  /**< KR,10GBASE-KR with software control*/
    MESA_MEDIA_TYPE_NONE,   /**< None          */
} mesa_phy_10g_media_t CAP(PHY_10G);

/** \brief 6G serdes link partner distance selection */
typedef enum {
    MESA_6G_LINK_SHORT_RANGE, /**<distance between 6G macro and serdes macro of link partner is less (direct connection)*/
    MESA_6G_LINK_LONG_RANGE,  /**<distance between 6G macro and serdes macro of link parter is more (connection via backplanes) */
} mesa_phy_6g_link_partner_distance_t CAP(PHY_10G);

/** \brief 10G Phy CLOCK Source Selection */
typedef struct {
    mesa_bool_t is_high_amp; /**< Amplitude selection HIGH or LOW     */
} mesa_phy_10g_clk_src_t CAP(PHY_10G);

/** \brief 10G SERDES APC operation */
typedef enum {
    MESA_IB_APC_AUTO,    /**< AUTO Operation    */
    MESA_IB_APC_MANUAL,  /**< Manual operation  */
    MESA_IB_APC_FREEZE,  /**< Freeze  */
    MESA_IB_APC_RESET,   /**< Reset   */
    MESA_IB_APC_RESTART, /**< Restart APC  */
    MESA_IB_APC_NONE,    /**< None    */
} mesa_phy_10g_ib_apc_op_mode_t CAP(PHY_10G);

/** \brief Generalized data structure for IB parameters */
typedef struct {
    uint16_t value; /**< value to be configured */
    uint16_t min;   /**< Minimum value */
    uint16_t max;   /**< Maximum value */
} mesa_ib_par_cfg_t CAP(PHY_10G);

/** \brief 10G Phy IB configuration */
typedef struct {
    mesa_ib_par_cfg_t offs;             /**< Equalizer offset value */
    mesa_ib_par_cfg_t gain;             /**< Equalizer gain value   */
    mesa_ib_par_cfg_t gainadj;          /**< IB gain adjustment */
    mesa_ib_par_cfg_t l;                /**< Equalizer L value */
    mesa_ib_par_cfg_t c;                /**< Equalizer C value */
    mesa_ib_par_cfg_t agc;              /**< AGC value*/
    mesa_ib_par_cfg_t dfe1;             /**< DFE1 active value */
    mesa_ib_par_cfg_t dfe2;             /**< DFE2 active value */
    mesa_ib_par_cfg_t dfe3;             /**< DFE3 active value */
    mesa_ib_par_cfg_t dfe4;             /**< DFE4 active value */
    uint8_t           ld;               /**< level detect */
    uint8_t           prbs;             /**< PRBS RX pattern selected */
    mesa_bool_t       prbs_inv;         /**< PRBS inversions selected */
    uint32_t          apc_bit_mask;     /**< Bit mask that has the information of the all the parameters whether they are being controlled by APC */
    uint32_t          freeze_bit_mask;  /**< Bit mask that has the information of the all parameters that are frozen to the value */
    uint32_t          config_bit_mask;  /**< Bit mask that has the information of the all parameters that are to be configured */
    mesa_bool_t       is_host;          /**< Configuration is on Host or line */
} mesa_phy_10g_ib_conf_t CAP(PHY_10G);

/** \brief 10G Phy IB configuration */
typedef struct {
    mesa_phy_10g_ib_conf_t ib_conf;    /**< Current status of IB configuraion */
    mesa_bool_t            sig_det;    /**< Signal detect */
    uint16_t               bit_errors; /**< Bit errors if PRBS is enabled */
} mesa_phy_10g_ib_status_t CAP(PHY_10G);

/** \brief 10G Phy APC configuration */
typedef struct {
    mesa_phy_10g_ib_apc_op_mode_t op_mode;      /**< APC operation */
    mesa_bool_t                   op_mode_flag; /**< APC operation flag,eg: TRUE= APC_RESET,FALSE = APC_RESET clear */
}mesa_phy_10g_apc_conf_t CAP(PHY_10G);

/** \brief 10G Phy APC status */
typedef struct {
    mesa_bool_t reset;  /**< APC reset status  */
    mesa_bool_t freeze; /**< APC freeze status */
}mesa_phy_10g_apc_status_t CAP(PHY_10G);

/** \brief 10G Phy SERDES status */
typedef struct {
    uint8_t rcomp ; /**< Measured Resistor value */

    /* Host PLL status */
    mesa_bool_t    h_pll5g_lock_status; /**<  TRUE value says its locked    */
    mesa_bool_t    h_pll5g_fsm_lock;    /**<  TRUE value says fsm is locked */
    uint8_t        h_pll5g_fsm_stat;    /**<  FSM status                    */
    uint8_t        h_pll5g_gain ;       /**<  Gain                          */

    /* Line PLL status */
    mesa_bool_t    l_pll5g_lock_status; /**<  TRUE value says its locked    */
    mesa_bool_t    l_pll5g_fsm_lock;    /**<  TRUE value says fsm is locked */
    uint8_t        l_pll5g_fsm_stat;    /**<  FSM status                    */
    uint8_t        l_pll5g_gain ;       /**<  Gain                          */

    /* RX RCPLL status */
    mesa_bool_t    h_rx_rcpll_lock_status; /**< TRUE value says its locked    */
    uint8_t        h_rx_rcpll_range;       /**< TRUE value says with in range */
    uint8_t        h_rx_rcpll_vco_load;    /**< Actual value of VCV load      */
    uint8_t        h_rx_rcpll_fsm_status;  /**< Actual value of FSM stage     */
    mesa_bool_t    l_rx_rcpll_lock_status; /**< TRUE value says its locked    */
    uint8_t        l_rx_rcpll_range;       /**< TRUE value says with in range */
    uint8_t        l_rx_rcpll_vco_load;    /**< Actual value of VCV load      */
    uint8_t        l_rx_rcpll_fsm_status;  /**< Actual value of FSM stage     */

    /* TX RCPLL status */
    mesa_bool_t    h_tx_rcpll_lock_status; /**< TRUE value says its locked    */
    uint8_t        h_tx_rcpll_range;       /**< TRUE value says with in range */
    uint8_t        h_tx_rcpll_vco_load;    /**< Actual value of VCV load      */
    uint8_t        h_tx_rcpll_fsm_status;  /**< Actual value of FSM stage     */
    mesa_bool_t    l_tx_rcpll_lock_status; /**< TRUE value says its locked    */
    uint8_t        l_tx_rcpll_range;       /**< TRUE value says with in range */
    uint8_t        l_tx_rcpll_vco_load;    /**< Actual value of VCV load      */
    uint8_t        l_tx_rcpll_fsm_status;  /**< Actual value of FSM stage     */

    /* Host PMA,PCS status */
    mesa_sublayer_status_t h_pma; /**< Host pma status */
    mesa_sublayer_status_t h_pcs; /**< Host pcs status */

    /* Line PMA,PCS status */
    mesa_sublayer_status_t l_pma; /**< Line pma status */
    mesa_sublayer_status_t l_pcs; /**< Line pcs status */

    /* WIS status */
    mesa_sublayer_status_t wis;   /**< WIS status */

}mesa_phy_10g_serdes_status_t CAP(PHY_10G);

/** \brief 10G Phy Optimisation of jitter performance */
typedef struct {
    mesa_bool_t    incr_levn; /**< Increase LevN          */
    uint8_t        levn;      /**< LevN configuration     */
    uint8_t        vtail;     /**< Vtail configuration    */
} mesa_phy_10g_jitter_conf_t CAP(PHY_10G);

/** \brief Channel modes - Auto is recommended */
typedef enum {
    /** Automatically detects the channel id based on the phy order. The phys be
     * setup in the consecutive order, from the lowest MDIO to highest MDIO
     * address */
    MESA_CHANNEL_AUTO,
    MESA_CHANNEL_0,      /**< Channel id is hardcoded to 0  */
    MESA_CHANNEL_1,      /**< Channel id is hardcoded to 1  */
    MESA_CHANNEL_2,      /**< Channel id is hardcoded to 2  */
    MESA_CHANNEL_3,      /**< Channel id is hardcoded to 3  */
} mesa_channel_t CAP(PHY_10G);

/** \brief EDC modes */
typedef enum {
    MESA_EDC_FW_LOAD_MDIO,    /**< Load EDC FW through MDIO to iCPU */
    MESA_EDC_FW_LOAD_NOTHING, /**< Do not load FW to iCPU */
} mesa_edc_fw_load_t CAP(PHY_10G);

/** \brief 10G Phy operating mode */
typedef struct {
    mesa_oper_mode_t         oper_mode;         /**< Phy operational mode */

    mesa_phy_interface_mode  interface;         /**< Interface mode. */

    mesa_wrefclk_t           wrefclk;           /**< 848X only: WAN ref clock */

    mesa_bool_t              high_input_gain;   /**< Disable=0 (default), Enable=1. Should not be enabled unless needed */
    mesa_bool_t              xfi_pol_invert;    /**< Selects polarity ot the TX XFI data. 1:Invert 0:Normal */
    mesa_bool_t              xaui_lane_flip;    /**< Swaps lane 0 <--> 3 and 1 <--> 2 for both RX and TX */

    mesa_channel_t           channel_id;        /**< Channel id of this instance of the Phy  */

    mesa_bool_t              hl_clk_synth;      /**< 0: Free running clock  1: Hitless clock   */
    mesa_recvrd_t            rcvrd_clk;         /**< RXCLKOUT/TXCLKOUT used as recovered clock */
                                                /**< (not used any more, instead use the api functions: */
                                                /**< mesa_phy_10g_rxckout_set and mesa_phy_10g_txckout_set */
    mesa_recvrdclk_cdr_div_t rcvrd_clk_div;     /**< 8488 only: recovered clock's divisor      */
    mesa_srefclk_div_t       sref_clk_div;      /**< 8488 only: SRERCLK divisor                */
    mesa_wref_clk_div_t      wref_clk_div;      /**< 8488 only: WREFCLK divisor                */

    mesa_edc_fw_load_t       edc_fw_load;       /**< EDC Firmware load */

    /** \brief Serdes parameters  */
    struct {
        mesa_bool_t use_conf;             /**< Use this configuration instead of default(only for setting 'd_filter'in Venice) */
        mesa_bool_t ob_conf;              /**< Configuration for SD10F OB  instead of default  (only for Venice family) */
        mesa_bool_t ib_conf;              /**< Configuration for SD6G ib_ini_lp, ib_min_lp & ib_max_lp (only for Venice family) */
        mesa_bool_t dig_offset_reg;       /**< Digital offset regulation for SD6G IB. Default is Analog(only for Venice family) */
        mesa_bool_t apc_offs_ctrl;        /**< Parameter used to control APC offset */
        mesa_bool_t apc_line_ld_ctrl;     /**< Parameter used to control APC Line LD Ctrl */
        mesa_bool_t apc_host_ld_ctrl;     /**< Parameter used to control APC Host LD Ctrl */
        uint32_t    d_filter;             /**< SD10G Transmit filter coefficients for FIR taps (default 0x7DF820)  */
        uint32_t    cfg0;                 /**< SD10G OB CFG0 value, configurable by USER (only for Venice family)  */
        uint32_t    ib_ini_lp;            /**< SD6G Init force value for low-pass gain regulation (default 1 )     */
        uint32_t    ib_min_lp;            /**< SD6G Min value for low-pass gain regulation (default 0)             */
        uint32_t    ib_max_lp;            /**< SD6G Max value for low-pass gain regulation (default 63)            */
        uint32_t    apc_eqz_offs_par_cfg; /**< APC EQZ_OFFS Parameter control                                  */
        uint32_t    apc_line_eqz_ld_ctrl; /**< APC EQZ Line LD control                                         */
        uint32_t    apc_host_eqz_ld_ctrl; /**< APC EQZ Host LD control                                         */
        mesa_bool_t l_offset_guard;       /**< Line offset control */
        mesa_bool_t h_offset_guard;       /**< Host offset control */
    } serdes_conf; /**< Serdes configuration                                                */

    mesa_apc_ib_regulator_t apc_ib_regulator; /**< Analog Parameter Control / IB equalizer  (only for Venice family)*/

    uint16_t  pma_txratecontrol;   /**< Normal pma_txratecontrol value to be restored when loopback is disabled */
    mesa_bool_t venice_rev_a_los_detection_workaround;  /**< TRUE => LOS detection woak around enabled. Requires interrupt handling */
    mesa_ddr_mode_t ddr_mode; /**< DDR Interleave mode */
    mesa_clk_mstr_t master;   /**< Clock Primary */
    mesa_rptr_rate_t rate;    /**< Data rate in repeater mode */
    mesa_phy_10g_polarity_inv_t polarity; /**< polarity inversion configuration */
    mesa_bool_t is_host_wan;   /**< Flag that gives information of WAN rate is supported at host interface */
    mesa_phy_10g_clk_src_t h_clk_src;   /**< Host side clock configuration*/
    mesa_phy_10g_clk_src_t l_clk_src;   /**< Line side clock configuration*/
    mesa_bool_t lref_for_host;  /**< Clock source selection HREF or LREF on HOST side*/
    mesa_phy_6g_link_partner_distance_t link_6g_distance; /**<Gives information of link partner distance from 6G macro */
    mesa_phy_10g_media_t h_media; /**< Gives information of media type connected on HOST direction */
    mesa_phy_10g_media_t l_media; /**< Gives information of media type connected on LINE direction */
    mesa_phy_10g_ib_conf_t h_ib_conf; /**< Host Input buffer configuration */
    mesa_phy_10g_ib_conf_t l_ib_conf; /**< Line Input buffer configuration */
    mesa_phy_10g_apc_conf_t h_apc_conf; /**< HOST APC configuration */
    mesa_phy_10g_apc_conf_t l_apc_conf; /**< LINE APC configuration */
    mesa_bool_t enable_pass_thru;              /**< Enables Pass through mode in VENICE */
    mesa_bool_t is_init;         /**< To identify intialization Phase */
    mesa_bool_t sd6g_calib_done; /**<to identify initialization Phase for ib calibration */
    mesa_bool_t alternate_port_ena; /**<to enable cross-connect functionality in Malibu */
} mesa_phy_10g_mode_t CAP(PHY_10G);

typedef uint16_t mesa_gpio_10g_no_t CAP(PHY_10G); /**< GPIO type for 10G ports*/

/** \brief 10G Phy Initialization configuration */
typedef struct {
    mesa_channel_t channel_conf;
} mesa_phy_10g_init_parm_t;

/**
 * \brief Identify PHY,Initialize software accordingly .
 * \brief It is first API to be executed before using device
 * \brief It is mandatory requirement that the API is to be called in order of,
 * \brief base_port first followed by alternate ports
 *
 * \param inst      [IN]  Target instance reference.
 * \param port_no   [IN]  Port number.
 * \param init_conf [IN]  Initialization configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_init (const mesa_inst_t inst,
                           const mesa_port_no_t port_no,
                           const mesa_phy_10g_init_parm_t *const init_conf)
    CAP(PHY_10G);

/**
 * \brief Get the Phy operating mode.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param mode [IN]     Mode configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/

mesa_rc mesa_phy_10g_mode_get(const mesa_inst_t    inst,
                              const mesa_port_no_t port_no,
                              mesa_phy_10g_mode_t  *const mode)
    CAP(PHY_10G);


/**
 * \brief Identify, Reset and set the operating mode of the PHY.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param mode [IN]     Mode configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_mode_set(const mesa_inst_t         inst,
                              const mesa_port_no_t      port_no,
                              const mesa_phy_10g_mode_t *const mode)
    CAP(PHY_10G);

/**
 * \brief Configure Input buffer .
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param ib_conf [IN]  IB configuration.
 * \param is_host [IN]  Direction to be configured.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_ib_conf_set(const mesa_inst_t            inst,
                                 const mesa_port_no_t         port_no,
                                 const mesa_phy_10g_ib_conf_t *const ib_conf,
                                 mesa_bool_t                  is_host)
    CAP(PHY_10G);

/**
 * \brief Get configuration of Input buffer .
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param is_host [IN]  Direction to be configured.
 * \param ib_conf [OUT] IB configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_ib_conf_get(const mesa_inst_t      inst,
                                 const mesa_port_no_t   port_no,
                                 const mesa_bool_t      is_host,
                                 mesa_phy_10g_ib_conf_t *const ib_conf)
    CAP(PHY_10G);

/**
 * \brief Get status of Input buffer .
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param ib_status [OUT]  IB status.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_ib_status_get(const mesa_inst_t        inst,
                                   const mesa_port_no_t     port_no,
                                   mesa_phy_10g_ib_status_t *const ib_status)
    CAP(PHY_10G);

/**
 * \brief Configure APC .
 *
 * \param inst     [IN] Target instance reference.
 * \param port_no  [IN] Port number.
 * \param apc_conf [IN] APC configuration.
 * \param is_host  [IN] Configuration side.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_apc_conf_set(const mesa_inst_t             inst,
                                  const mesa_port_no_t          port_no,
                                  const mesa_phy_10g_apc_conf_t *const apc_conf,
                                  const mesa_bool_t             is_host)
    CAP(PHY_10G);

/**
 * \brief Get configuration of APC .
 *
 * \param inst     [IN]  Target instance reference.
 * \param port_no  [IN]  Port number.
 * \param is_host  [IN]  Configuration side.
 * \param apc_conf [OUT] APC configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_apc_conf_get(const mesa_inst_t       inst,
                                  const mesa_port_no_t    port_no,
                                  const mesa_bool_t       is_host,
                                  mesa_phy_10g_apc_conf_t *const apc_conf)
    CAP(PHY_10G);

/**
 * \brief Get status of APC.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param is_host [IN]  Configuration side.
 * \param apc_status [OUT]  APC status.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_apc_status_get(const mesa_inst_t         inst,
                                    const mesa_port_no_t      port_no,
                                    const mesa_bool_t         is_host,
                                    mesa_phy_10g_apc_status_t *const apc_status)
    CAP(PHY_10G);

/**
 * \brief Restart of APC - Debug function only.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param is_host [IN]  Configuration side.
 *
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_apc_restart (const mesa_inst_t inst,
                                  const mesa_port_no_t port_no,
                                  const mesa_bool_t is_host)
    CAP(PHY_10G);

/**
 * \brief Configure optimised jitter
 *
 * \param inst         [IN]  Target instance reference.
 * \param port_no      [IN]  Port number.
 * \param jitter_conf  [IN]  Jitter configuration.
 * \param is_host      [IN]  Direction to be configured.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_jitter_conf_set(const mesa_inst_t                inst,
                                     const mesa_port_no_t             port_no,
                                     const mesa_phy_10g_jitter_conf_t *const jitter_conf,
                                     mesa_bool_t                      is_host)
    CAP(PHY_10G);

/**
 * \brief Gets current Jitter configuration
 *
 * \param inst         [IN]  Target instance reference.
 * \param port_no      [IN]  Port number.
 * \param jitter_conf  [IN]  Jitter configuration.
 * \param is_host      [IN]  Direction to be configured.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_jitter_conf_get(const mesa_inst_t          inst,
                                     const mesa_port_no_t       port_no,
                                     mesa_phy_10g_jitter_conf_t *jitter_conf,
                                     mesa_bool_t                is_host)
    CAP(PHY_10G);

/**
 * \brief Jitter status
 *
 * \param inst         [IN]  Target instance reference.
 * \param port_no      [IN]  Port number.
 * \param jitter_conf  [IN]  Jitter configuration status.
 * \param is_host      [IN]  Direction.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_jitter_status_get(const mesa_inst_t          inst,
                                       const mesa_port_no_t       port_no,
                                       mesa_phy_10g_jitter_conf_t *const jitter_conf,
                                       mesa_bool_t                is_host)
    CAP(PHY_10G);

/**
 * \brief debug function for PHY 10G FC buffer reset
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Any phy port with the chip
 *
 * \return MSCC_RC_OK - success of fc buffer reset
 **/
mesa_rc mesa_phy_10g_fc_buffer_reset(const mesa_inst_t inst,
        const mesa_port_no_t  port_no)
    CAP(PHY_10G);

/**
 * \brief Get the status of recovered clock from PHY. (recommended to use mesa_phy_10g_rxckout_get instead)
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       Port number.
 * \param synce_clkout [IN]  Recovered clock configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_synce_clkout_get(const mesa_inst_t    inst,
                                      const mesa_port_no_t port_no,
                                      mesa_bool_t          *const synce_clkout)
    CAP(PHY_10G);

/**
 * \brief Enable or Disable the recovered clock from PHY. (recommended to use mesa_phy_10g_rxckout_set instead)
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param synce_clkout [IN]  Recovered clock to be enabled or disabled.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_synce_clkout_set(const mesa_inst_t    inst,
                                      const mesa_port_no_t port_no,
                                      const mesa_bool_t    synce_clkout)
    CAP(PHY_10G);

/**
 * \brief Get the status of RXCLKOUT/TXCLKOUT from PHY. (recommended to use mesa_phy_10g_txckout_get instead)
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       Port number.
 * \param xfp_clkout [IN]    XFP clock configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_xfp_clkout_get(const mesa_inst_t    inst,
                                    const mesa_port_no_t port_no,
                                    mesa_bool_t          *const xfp_clkout)
    CAP(PHY_10G);

/**
 * \brief Enable or Disable the RXCLKOUT/TXCLKOUT from PHY. (recommended to use mesa_phy_10g_txckout_set instead)
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param xfp_clkout [IN]  XFP clock to be enabled or disabled.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_xfp_clkout_set(const mesa_inst_t    inst,
                                    const mesa_port_no_t port_no,
                                    const mesa_bool_t    xfp_clkout)
    CAP(PHY_10G);

/** \brief Modes for (rx/tx) recovered clock output*/
typedef enum {
    MESA_RECVRD_CLKOUT_DISABLE,             /**< recovered clock output is disabled */
    MESA_RECVRD_CLKOUT_LINE_SIDE_RX_CLOCK,  /**< recovered clock output is derived from Lineside Rx clock */
    MESA_RECVRD_CLKOUT_LINE_SIDE_TX_CLOCK,  /**< recovered clock output is derived from Lineside Tx clock */
} mesa_recvrd_clkout_t CAP(PHY_10G);

/** \brief 10G Phy RXCKOUT config data */
typedef struct {
    mesa_recvrd_clkout_t   mode;                 /**< RXCKOUT output mode (DISABLE/RX_CLK/TX_CLK) */
    mesa_bool_t            squelch_on_pcs_fault; /**< Enable squelching on PCS_FAULT (Venice family only) */
    mesa_bool_t            squelch_on_lopc;      /**< Enable squelching on LOPC (Venice family only) */
} mesa_phy_10g_rxckout_conf_t CAP(PHY_10G);

/**
 * \brief Get the rx recovered clock output configuration.
 *
 * \param inst [IN]         Target instance reference.
 * \param port_no [IN]      Port number.
 * \param rxckout [OUT]     RXCKOUT clock configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_rxckout_get(const mesa_inst_t           inst,
                                 const mesa_port_no_t        port_no,
                                 mesa_phy_10g_rxckout_conf_t *const rxckout)
    CAP(PHY_10G);

/**
 * \brief Set the rx recovered clock output configuration.
 *
 * \param inst [IN]         Target instance reference.
 * \param port_no [IN]      Port number.
 * \param rxckout [IN]      RXCKOUT clock configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_rxckout_set(const mesa_inst_t                 inst,
                                 const mesa_port_no_t              port_no,
                                 const mesa_phy_10g_rxckout_conf_t *const rxckout)
    CAP(PHY_10G);

/** \brief 10G Phy TXCKOUT config data */
typedef struct {
    mesa_recvrd_clkout_t mode; /**< TXCKOUT output mode (DISABLE/RX_CLK/TX_CLK) */
} mesa_phy_10g_txckout_conf_t CAP(PHY_10G);

/**
 * \brief Get the status of tx recovered clock output configuration.
 *
 * \param inst [IN]         Target instance reference.
 * \param port_no [IN]      Port number.
 * \param txckout [OUT]     TXCKOUT clock configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_txckout_get(const mesa_inst_t           inst,
                                 const mesa_port_no_t        port_no,
                                 mesa_phy_10g_txckout_conf_t *const txckout)
    CAP(PHY_10G);

/**
 * \brief Set the tx recovered clock output configuration.
 *
 * \param inst [IN]         Target instance reference.
 * \param port_no [IN]      Port number.
 * \param txckout [IN]      TXCKOUT clock configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_txckout_set(const mesa_inst_t                 inst,
                                 const mesa_port_no_t              port_no,
                                 const mesa_phy_10g_txckout_conf_t *const txckout)
    CAP(PHY_10G);


/** \brief 10G Phy sref clock input frequency */
typedef enum {
    MESA_PHY_10G_SREFCLK_156_25,  /**< 156,25 MHz */
    MESA_PHY_10G_SREFCLK_125_00,  /**< 125,00 MHz */
    MESA_PHY_10G_SREFCLK_155_52,  /**< 155,52 MHz */
    MESA_PHY_10G_SREFCLK_INVALID  /**< Other values are not allowed*/
} mesa_phy_10g_srefclk_freq_t CAP(PHY_10G);

/** \brief 10G Phy srefclk config data */
typedef struct {
    mesa_bool_t                 enable; /**< Enable locking line tx clock to srefclk input  */
    mesa_phy_10g_srefclk_freq_t freq;   /**< The srefclk input frequency */
} mesa_phy_10g_srefclk_mode_t CAP(PHY_10G);

/**
 * \brief Get the configuration of srefclk setting\n
 *  Avaliable for PHY family VENICE\n
 *           This function should not be used any more, instead use the API function mesa_phy_10g_mode_get,
 *           see the parameter documentation for that function.
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       Port number.
 * \param srefclk [OUT]      srefclk configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_srefclk_conf_get(const mesa_inst_t           inst,
                                      const mesa_port_no_t        port_no,
                                      mesa_phy_10g_srefclk_mode_t *const srefclk)
    CAP(PHY_10G);

/**
 * \brief Set the configuration of srefclk setting.
 * Avaliable for PHY family VENICE\n
 *           This function should not be used any more, instead use the API function mesa_phy_10g_mode_set,
 *           see the parameter documentation for that function.
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       Port number.
 * \param srefclk [IN]       srefclk configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_srefclk_conf_set(const mesa_inst_t                 inst,
                                      const mesa_port_no_t              port_no,
                                      const mesa_phy_10g_srefclk_mode_t *const srefclk)
    CAP(PHY_10G);

/**
 * Malibu only
 * \brief 10G Phy clock frequency */
typedef enum {
    MESA_PHY_10G_CLK_FULL_RATE,   /**< LAN:332.25 MHz, WAN:311.04MHz, 1G:125MHz */
    MESA_PHY_10G_CLK_DIVIDE_BY_2, /**< LAN:161.12 MHz, WAN:155.52MHz, 1G:62.5MHz */
    MESA_PHY_10G_CLK_INVALID      /**< Other values are not allowed*/
} mesa_phy_10g_ckout_freq_t CAP(PHY_10G);

/**
 * Applicable to Malibu only
 * \brief Modes for recovered clock output
 **/
typedef enum {
    MESA_CKOUT_LINE0_TX_CLOCK,     /**< Line0 Transmit clock */
    MESA_CKOUT_LINE1_TX_CLOCK,     /**< Line1 Transmit clock */
    MESA_CKOUT_LINE2_TX_CLOCK,     /**< Line2 Transmit clock */
    MESA_CKOUT_LINE3_TX_CLOCK,     /**< Line3 Transmit clock */
    MESA_CKOUT_HOST0_TX_CLOCK,     /**< Host0 Transmit clock */
    MESA_CKOUT_HOST1_TX_CLOCK,     /**< Host1 Transmit clock */
    MESA_CKOUT_HOST2_TX_CLOCK,     /**< Host2 Transmit clock */
    MESA_CKOUT_HOST3_TX_CLOCK,     /**< Host3 Transmit clock */
    MESA_CKOUT_LINE0_RECVRD_CLOCK, /**< Line0 Recovered clock */
    MESA_CKOUT_LINE1_RECVRD_CLOCK, /**< Line1 Recovered clock */
    MESA_CKOUT_LINE2_RECVRD_CLOCK, /**< Line2 Recovered clock */
    MESA_CKOUT_LINE3_RECVRD_CLOCK, /**< Line3 Recovered clock */
    MESA_CKOUT_HOST0_RECVRD_CLOCK, /**< Host0 Recovered clock */
    MESA_CKOUT_HOST1_RECVRD_CLOCK, /**< Host1 Recovered clock */
    MESA_CKOUT_HOST2_RECVRD_CLOCK, /**< Host2 Recovered clock */
    MESA_CKOUT_HOST3_RECVRD_CLOCK, /**< Host3 Recovered clock */
    MESA_CKOUT_HOST_PLL_CLOCK,     /**< Host PLL clock */
    MESA_CKOUT_LINE_PLL_CLOCK,     /**< Line PLL clock */
    MESA_CKOUT_CSR_CLOCK,          /**< CSR clock */
    MESA_CKOUT_LTC_CLOCK,          /**< LTC clock */
    MESA_CKOUT_DF2F_CLOCK,         /**< Df2f clock */
    MESA_CKOUT_F2DF_CLOCK,         /**< F2df clock */
    MESA_CKOUT_DEBUG1,             /**< Debug1 */
    MESA_CKOUT_DEBUG2,             /**< Debug2 */
    MESA_CKOUT_OSCILLATOR_OUTPUT,  /**< Oscillator output */
} mesa_ckout_data_sel_t CAP(PHY_10G);

/**
 * Applicable to Malibu only
 * \brief squelch control source
 **/
typedef enum {
    MESA_CKOUT_SQUELCH_SRC_GPIO0,         /**< GPIO0 as source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_GPIO1,         /**< GPIO1 as source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_GPIO2,         /**< GPIO2 as source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_GPIO3,         /**< GPIO3 as source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_GPIO4,         /**< GPIO4 as source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_GPIO5,         /**< GPIO5 as source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_GPIO6,         /**< GPIO6 as source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_GPIO7,         /**< GPIO7 as source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LINK_LINE0,    /**< Link status from Line0 source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LINK_LINE1,    /**< Link status from Line1 source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LINK_LINE2,    /**< Link status from Line2 source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LINK_LINE3,    /**< Link status from Line3 source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LINK_HOST0,    /**< Link status from Host0 source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LINK_HOST1,    /**< Link status from Host1 source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LINK_HOST2,    /**< Link status from Host2 source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LINK_HOST3,    /**< Link status from Host3 source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LOS_LINE0,     /**< Serdes LOS from Line0 as source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LOS_LINE1,     /**< Serdes LOS from Line1 as source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LOS_LINE2,     /**< Serdes LOS from Line2 as source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LOS_LINE3,     /**< Serdes LOS from Line3 as source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LOS_HOST0,     /**< Serdes LOS from Host0 as source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LOS_HOST1,     /**< Serdes LOS from Host1 as source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LOS_HOST2,     /**< Serdes LOS from Host2 as source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LOS_HOST3,     /**< Serdes LOS from Host3 as source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LINK_LINE0_KR, /**< Link status from Line0 KR source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LINK_LINE1_KR, /**< Link status from Line1 KR source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LINK_LINE2_KR, /**< Link status from Line2 KR source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LINK_LINE3_KR, /**< Link status from Line3 KR source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LINK_HOST0_KR, /**< Link status from Host0 KR source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LINK_HOST1_KR, /**< Link status from Host1 KR source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LINK_HOST2_KR, /**< Link status from Host2 KR source of auto squelch */
    MESA_CKOUT_SQUELCH_SRC_LINK_HOST3_KR, /**< Link status from Host3 KR source of auto squelch */
    MESA_CKOUT_NO_SQUELCH                 /**< No squelch(32-63) */
} mesa_phy_10g_squelch_src_t CAP(PHY_10G);

/**
 * Applicable to Malibu only
 * \brief Modes of recovered
 * clocks for ckout and sckout pins
 **/
typedef enum {
    MESA_PHY_10G_LINE0_RECVRD_CLOCK, /**< Line0 Recovered clock */
    MESA_PHY_10G_LINE1_RECVRD_CLOCK, /**< Line1 Recovered clock */
    MESA_PHY_10G_LINE2_RECVRD_CLOCK, /**< Line2 Recovered clock */
    MESA_PHY_10G_LINE3_RECVRD_CLOCK, /**< Line3 Recovered clock */
    MESA_PHY_10G_HOST0_RECVRD_CLOCK, /**< Host0 Recovered clock */
    MESA_PHY_10G_HOST1_RECVRD_CLOCK, /**< Host1 Recovered clock */
    MESA_PHY_10G_HOST2_RECVRD_CLOCK, /**< Host2 Recovered clock */
    MESA_PHY_10G_HOST3_RECVRD_CLOCK, /**< Host3 Recovered clock */
    MESA_PHY_10G_SREFCLK,            /**< SREFCLK */
    MESA_PHY_10G_SYNC_DISABLE = 15   /**< Sync Disable 9-15 */
} mesa_phy_10g_clk_sel_t CAP(PHY_10G);

/**
 * Applicable to Malibu only
 * \brief Modes of recovered
 * clock selection
 **/
typedef enum {
    MESA_PHY_10G_USE_LINE0_RECVRD_CLOCK,  /**< All lines using Line0 Recovered clock */
    MESA_PHY_10G_USE_LINE1_RECVRD_CLOCK,  /**< All lines using Line1 Recovered clock */
    MESA_PHY_10G_USE_LINE2_RECVRD_CLOCK,  /**< All lines using Line2 Recovered clock */
    MESA_PHY_10G_USE_LINE3_RECVRD_CLOCK,  /**< All lines using Line3 Recovered clock */
    MESA_PHY_10G_USE_HOST0_RECVRD_CLOCK,  /**< All lines using Host0 Recovered clock */
    MESA_PHY_10G_USE_HOST1_RECVRD_CLOCK,  /**< All lines using Host1 Recovered clock */
    MESA_PHY_10G_USE_HOST2_RECVRD_CLOCK,  /**< All lines using Host2 Recovered clock */
    MESA_PHY_10G_USE_HOST3_RECVRD_CLOCK,  /**< All lines using Host3 Recovered clock */
    MESA_PHY_10G_USE_SREFCLK_CLOCK,       /**< All lines using SREFCLK */
    MESA_PHY_10G_USE_DEFAULT_RECVRD_CLOCK /**< Use Recvrd Clk from the respcective line
                                            *  LineX Uses recovered clock from LineX only */
} mesa_phy_10g_recvrd_clk_sel_t CAP(PHY_10G);

/**
 * Malibu Only
 * \brief 10G Phy CKOUTs Enum
 **/
typedef enum {
    MESA_CKOUT0,
    MESA_CKOUT1,
    MESA_CKOUT2,
    MESA_CKOUT3,
} mesa_ckout_sel_t CAP(PHY_10G);

/**
 * Malibu Only
 * \brief 10G Phy CKOUT config data
 **/
typedef struct {
    mesa_ckout_data_sel_t      mode;        /**< CKOUT output clock mode */
    mesa_phy_10g_squelch_src_t src;         /**< CKOUT squelch source */
    mesa_phy_10g_ckout_freq_t  freq;        /**< CKOUT clock frequency*/
    mesa_bool_t                squelch_inv; /**< '0'- Use squelch source src as is, '1'-Invert */
    mesa_bool_t                enable;      /**< '1'- Enable  CKOUT, '0'-Disable */
    mesa_ckout_sel_t           ckout_sel;   /**< CKOUT sel eg-'0' for CKOUT0, '1' for CKOUT1 */
} mesa_phy_10g_ckout_conf_t CAP(PHY_10G);

/** \brief 10G Phy sckout clock input frequency */
typedef enum {
    MESA_PHY_10G_SCKOUT_156_25, /**< 156,25 MHz */
    MESA_PHY_10G_SCKOUT_125_00, /**< 125,00 MHz */
    MESA_PHY_10G_SCKOUT_INVALID /**< Other values are not allowed*/
} mesa_phy_10g_sckout_freq_t CAP(PHY_10G);

/**
 * Malibu Only
 * \brief 10G Phy SCKOUT config data
 **/
typedef struct {
    mesa_phy_10g_clk_sel_t     mode;        /**< SCKOUT output clock mode */
    mesa_phy_10g_squelch_src_t src;         /**< SCKOUT squelch source */
    mesa_phy_10g_sckout_freq_t freq;        /**< SCKOUT freq(156.25MHz, 125MHz only) */
    mesa_bool_t                squelch_inv; /**< '0'- Use squelch source src as is, '1'-Invert */
    mesa_bool_t                enable;      /**< Enable/Disable SCKOUT */
} mesa_phy_10g_sckout_conf_t CAP(PHY_10G);

/**
 * \brief Set the configuration of sckout setting.
 * Avaliable for PHY family MALIBU\n
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       Port number.
 * \param sckout [IN]        sckout configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_sckout_conf_set(const mesa_inst_t                inst,
                                     const mesa_port_no_t             port_no,
                                     const mesa_phy_10g_sckout_conf_t *const sckout)
    CAP(PHY_10G);

/**
 * \brief Set the configuration of ckout setting.
 * Avaliable for PHY family MALIBU\n
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       Port number.
 * \param ckout [IN]       ckout configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_ckout_conf_set(const mesa_inst_t               inst,
                                    const mesa_port_no_t            port_no,
                                    const mesa_phy_10g_ckout_conf_t *const ckout)
    CAP(PHY_10G);

/**
 * Malibu Only
 * \brief 10G Phy Line clock config data
 **/
typedef struct {
    mesa_phy_10g_clk_sel_t        mode;           /**< Line side output clock mode */
    mesa_phy_10g_recvrd_clk_sel_t recvrd_clk_sel; /**< Recovered clock selection */
    uint8_t                       clk_sel_no;     /**< Line clock select No(0-3) */
} mesa_phy_10g_line_clk_conf_t CAP(PHY_10G);

/**
 * \brief Set the configuration of sckout setting.
 * Avaliable for PHY family MALIBU\n
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       Port number.
 * \param line_clk [IN]       line_clk configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_line_clk_conf_set(const mesa_inst_t                  inst,
                                       const mesa_port_no_t               port_no,
                                       const mesa_phy_10g_line_clk_conf_t *const line_clk)
    CAP(PHY_10G);

/**
 * Malibu Only
 * \brief 10G Phy Host clock config data
 **/
typedef struct {
    mesa_phy_10g_clk_sel_t        mode;           /**< Host side output clock mode */
    mesa_phy_10g_recvrd_clk_sel_t recvrd_clk_sel; /**< Recovered clock selection */
    uint8_t                       clk_sel_no;    /**< Host clock select No(0-3) */
} mesa_phy_10g_host_clk_conf_t CAP(PHY_10G);

/**
 * \brief Set the configuration of sckout setting.
 * Avaliable for PHY family MALIBU\n
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       Port number.
 * \param host_clk [IN]      host_clk configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_host_clk_conf_set(const mesa_inst_t                  inst,
                                       const mesa_port_no_t               port_no,
                                       const mesa_phy_10g_host_clk_conf_t *const host_clk)
    CAP(PHY_10G);

/**
 * \brief Set the configuration of line clk recovered  setting.
 * Avaliable for PHY family MALIBU\n
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       Port number.
 * \param line_clk [IN]       line_recvrd_clk configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_line_recvrd_clk_conf_set(const mesa_inst_t                  inst,
                                              const mesa_port_no_t               port_no,
                                              const mesa_phy_10g_line_clk_conf_t *const line_clk)
    CAP(PHY_10G);

/**
 * \brief Set the configuration of host clk recovered  setting.
 * Avaliable for PHY family MALIBU\n
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       Port number.
 * \param host_clk [IN]       host_clk configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_host_recvrd_clk_conf_set(const mesa_inst_t                  inst,
                                              const mesa_port_no_t               port_no,
                                              const mesa_phy_10g_host_clk_conf_t *const host_clk)
    CAP(PHY_10G);

/**
 * Malibu Only
 * \brief 10G Phy Rx MACRO Configuration
 **/
typedef enum {
    MESA_PHY_10G_RX_MACRO_LINE,    /**< Rx MACRO Line */
    MESA_PHY_10G_RX_MACRO_HOST,    /**< Rx MACRO Host */
    MESA_PHY_10G_RX_MACRO_SREFCLK, /**< Rx MACRO SREFCLK */
} mesa_phy_10g_rx_macro_t CAP(PHY_10G);

/**
 * Malibu Only
 * \brief 10G Phy tx MACRO Configuration
 **/
typedef enum {
    MESA_PHY_10G_TX_MACRO_LINE,   /**< Tx MACRO Line */
    MESA_PHY_10G_TX_MACRO_HOST,   /**< Tx MACRO Host */
    MESA_PHY_10G_TX_MACRO_SCKOUT, /**< Tx MACRO SREFCLK */
} mesa_phy_10g_tx_macro_t CAP(PHY_10G);

/**
 * Malibu Only
 * \brief 10G Phy Lane SYNC Configuration
 **/
typedef struct {
    mesa_bool_t             enable;   /**< Enable/Disable LANE SYNC */
    mesa_phy_10g_tx_macro_t tx_macro; /**< Tx Macro to lane sync to */
    mesa_phy_10g_rx_macro_t rx_macro; /**< Rx Macro to lane sync to */
    uint8_t                 rx_ch;    /**< 0[Default] to 3- NA If rx_macro is SREFCLK */
    uint8_t                 tx_ch;    /**< 0[Default] to 3- NA If tx_macro is SCKOUT */
} mesa_phy_10g_lane_sync_conf_t CAP(PHY_10G);

/**
 * \brief Set the configuration of lane sync setting.
 * Avaliable for PHY family MALIBU\n
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       Port number.
 * \param lane_sync [IN]       ckout configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_lane_sync_set(const mesa_inst_t                   inst,
                                   const mesa_port_no_t                port_no,
                                   const mesa_phy_10g_lane_sync_conf_t *const lane_sync)
    CAP(PHY_10G);

/**
 * \brief Set the configuration of 10G PHY Dump setting.
 * Avaliable for PHY family Venice & Malibu \n
 *
 * \param inst [IN]          Target instance reference.
 * \param pr [IN]            Print function.
 * \param clear [IN]         set for clearing the counters
 * \param port_no [IN]       Port number.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_debug_register_dump(const mesa_inst_t         inst,
                                         const mesa_debug_printf_t pr,
                                         mesa_bool_t               clear,
                                         const mesa_port_no_t      port_no)
    CAP(PHY_10G);

/** \brief 10G Phy OB status*/
typedef struct {
    uint8_t      r_ctrl;  /**< slew rate r active value */
    uint8_t      c_ctrl;  /**< slew rate c active value */
    uint8_t      slew;    /**< slew rate       */
    uint8_t      levn;    /**< amplitude       */
    uint32_t     d_fltr;  /**< d-filter value  */
    int          v3;      /**< d_filter tap v3 */
    int          vp;      /**< d_filter tap vp */
    int          v4;      /**< d_filter tap v4 */
    int          v5;      /**< d_filter tap v5 */
    mesa_bool_t  is_host; /**< flag that says host/line */
} mesa_phy_10g_ob_status_t CAP(PHY_10G);

/** \brief Slew rate ctrl of OB  */
#define MESA_SLEWRATE_25PS    0          /**< Slewrate = 25ps */
#define MESA_SLEWRATE_35PS    1          /**< Slewrate = 35ps */
#define MESA_SLEWRATE_55PS    2          /**< Slewrate = 55ps */
#define MESA_SLEWRATE_70PS    3          /**< Slewrate = 70ps */
#define MESA_SLEWRATE_120PS   4          /**< Slewrate = 120ps */
#define MESA_SLEWRATE_INVALID 5          /**< Slewrate is invalid */

/** \brief 10G Phy 10f_base_kr_conf config data according to 802.3-2008 clause 72.7 Figure 72-11*/

typedef struct {
    int32_t      cm1;      /**< The minus 1 coefficient c(-1). Range: -32..31 */
    int32_t      c0;       /**< The 0 coefficient c(0).        Range: -32..31 */
    int32_t      c1;       /**< The plus 1 coefficient c(1).   Range: -32..31 */
    uint32_t     ampl;     /**< The Amplitude value in nVpp. Range: 300..1275 */
    uint32_t     slewrate; /**< Slew rate ctrl of OB */
    mesa_bool_t  en_ob;    /**< Enable output buffer and serializer */
    mesa_bool_t  ser_inv;  /**< Invert input to serializer */
} mesa_phy_10g_base_kr_conf_t CAP(PHY_10G);

/** \brief 10G Phy Base KR Autoneg config*/

typedef struct {
    mesa_bool_t an_restart; /**< Autoneg restart */
    mesa_bool_t an_enable;  /**< Autoneg enable */
    mesa_bool_t an_reset;   /**< Autoneg reset */
} mesa_phy_10g_base_kr_autoneg_t CAP(PHY_10GBASE_KR);

/** \brief 10G Phy Base KR Training config*/
typedef struct {
    mesa_bool_t    enable;    /**< Enable KR training */
    uint8_t        trmthd_cp; /**< Training method c(+1), 0-BER is supported*/
    uint8_t        trmthd_c0; /**< Training method c(0) , 0-BER,1-GAIN are supported*/
    uint8_t        trmthd_cm; /**< Training method c(-1), 0-BER is supported*/
    mesa_bool_t    ld_pre_init; /**< Set local taps starting point 0-initialize,1-preset */
} mesa_phy_10g_base_kr_training_t CAP(PHY_10GBASE_KR);

/** \brief 10G Phy Base Link Advertisement capability config*/
typedef struct {
    uint8_t adv_1g;   /**<Advertise 1G ,not supported */
    uint8_t adv_10g;  /**<Advertise 10G,by default choosen by API */
    uint8_t fec_abil; /**<Set FEC ability ,by default choosen by API*/
    uint8_t fec_req;  /**<Set FEC request ,the only configurable option*/
} mesa_phy_10g_base_kr_ld_adv_abil_t CAP(PHY_10GBASE_KR);

/** \brief 10G Phy Base KR Training & Autoneg config*/
typedef struct {
    mesa_phy_10g_base_kr_training_t    training; /**< KR Training params */
    mesa_phy_10g_base_kr_autoneg_t     autoneg;  /**< KR Autoneg params */
    mesa_phy_10g_base_kr_ld_adv_abil_t ld_abil;  /**< KR LD ADV Ability params */
    mesa_bool_t                        host_kr;  /**< Host side KR operation */
    mesa_bool_t                        line_kr;  /**< Line side KR operation */
} mesa_phy_10g_base_kr_train_aneg_t CAP(PHY_10GBASE_KR);

/** \brief 10G Phy Base KR Autoneg status*/
typedef struct {
    mesa_bool_t complete;              /**< Aneg completed successfully */
    mesa_bool_t active;                /**< Aneg is running between LD and LP */
    mesa_bool_t request_10g;           /**< LP's 10G rate negotiated  */
    mesa_bool_t request_1g;            /**< LP's 1G rate negotiated   */
    mesa_bool_t request_fec_change;    /**< LP's FEC request          */
    mesa_bool_t fec_enable;            /**< LP's FEC ability          */
    uint32_t   sm;                     /**< Aneg state machine(debug) */
    mesa_bool_t lp_aneg_able;          /**< Link partner(LP) aneg ability */
    mesa_bool_t block_lock;            /**< PCS block lock            */
} mesa_phy_10g_kr_status_aneg_t CAP(PHY_10GBASE_KR);

/** \brief 10G Phy Base KR Training status*/
typedef struct {
    mesa_bool_t complete;              /**< Training completed successfully               */
    uint8_t cm_ob_tap_result;        /**< The minus 1 coefficient c(-1).     Range: -32..31 */
    uint8_t cp_ob_tap_result;        /**< The 0 coefficient c(0).            Range: -32..31 */
    uint8_t c0_ob_tap_result;        /**< The plus 1 coefficient c(1).       Range: -32..31 */
} mesa_phy_10g_kr_status_train_t CAP(PHY_10GBASE_KR);

/** \brief 10G Phy Base KR FEC status*/
typedef struct {
    mesa_bool_t enable;                  /**< FEC Enabled               */
    uint32_t corrected_block_cnt;        /**< Corrected block count     */
    uint32_t uncorrected_block_cnt;      /**< Un-corrected block count  */
} mesa_phy_10g_kr_status_fec_t CAP(PHY_10GBASE_KR);

/** \brief 10G Phy Base KR Training & Autoneg status*/
typedef struct {
    mesa_phy_10g_kr_status_aneg_t aneg;    /**< Aneg structure      */
    mesa_phy_10g_kr_status_train_t train;  /**< Training structure  */
    mesa_phy_10g_kr_status_fec_t fec;      /**< FEC structure       */
} mesa_phy_10g_base_kr_status_t CAP(PHY_10GBASE_KR);

/**
 * \brief Get the configuration of 10g_base_kr_tr_aneg setting.
 * Avaliable for PHY family Malibu,venice-c
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       Port number.
 * \param kr_tr_aneg [OUT]      10g_base_kr_tr_aneg configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_base_kr_train_aneg_get(const mesa_inst_t inst,
                                        const mesa_port_no_t port_no,
                                        mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
    CAP(PHY_10GBASE_KR);

/**
 * \brief Set the configuration of 10g_base_kr_tr_aneg setting.
 * Avaliable for PHY family Malibu
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       Port number.
 * \param kr_tr_aneg [IN]   10g_base_kr_tr_aneg configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_base_kr_train_aneg_set(const mesa_inst_t                       inst,
                                            const mesa_port_no_t                    port_no,
                                            const mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
    CAP(PHY_10GBASE_KR);

/**
 * \brief Set the configuration of Host 10g_base_kr_tr_aneg setting.
 * Avaliable for PHY family Malibu
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       Port number.
 * \param kr_tr_aneg [IN]   10g_base_kr_tr_aneg configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_base_host_kr_train_aneg_set(const mesa_inst_t inst,
            const mesa_port_no_t port_no,
            const mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
    CAP(PHY_10GBASE_KR);

/**
 * \brief Get status of KR autonegotiation and training.
 * Avaliable for PHY family Malibu,Venice-c
 *
 * \param inst      [IN]       Target instance reference.
 * \param port_no   [IN]       Port number.
 * \param direction [IN]       Direction line or host.
 * \param kr_status [OUT]      10g_base_kr status(aneg,trainging,fec).
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_kr_status_get(const mesa_inst_t inst,
        const mesa_port_no_t port_no,
        mesa_bool_t direction,
        mesa_phy_10g_base_kr_status_t *const kr_status)
    CAP(PHY_10GBASE_KR);

/**
 * \brief Get the configuration of 10f_base_kr setting.
 * Avaliable for PHY family VENICE
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       Port number.
 * \param kr_conf [OUT]      10f_base_kr configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_base_kr_conf_get(const mesa_inst_t           inst,
                                      const mesa_port_no_t        port_no,
                                      mesa_phy_10g_base_kr_conf_t *const kr_conf)
    CAP(PHY_10G);

/**
 * \brief Set the configuration of 10f_base_kr setting.
 * Avaliable for PHY family VENICE:
 * Note: The parameters cm1,c0, c1 have a range of -32..31. The Output signal from the KR circuit is symmetric,
 *       I.e. the voltage output is configured value + 1/2lsb. (ex: -1 => -1/2lsb voltage level, 0 => +1/2lsb voltage level
 *       The parameter ampl is set in steps of 25 mV, therefore the setting is rounded up to a multiplum og 25 mV,
 *       I.e. 1101..1125 => 1125 mVppd
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       Port number.
 * \param kr_conf [IN]       10f_base_kr configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERR_KR_CONF_NOT_SUPPORTED if the PHY on the port does not support 10GBASE_KR configuration
 *   MESA_RC_ERR_KR_CONF_INVALID_PARAMETER if one of the parameter values are invalid or (|cm1|+ |c0| + |c1|) > 31
 *   MESA_RC_ERROR on other errors.
 **/
mesa_rc mesa_phy_10g_base_kr_conf_set(const mesa_inst_t                 inst,
                                      const mesa_port_no_t              port_no,
                                      const mesa_phy_10g_base_kr_conf_t *const kr_conf)
    CAP(PHY_10G);

/**
 * \brief Get the configuration of 10f_base_kr setting.
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       Port number.
 * \param kr_conf [OUT]      host 10f_base_kr configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_base_kr_host_conf_get(const mesa_inst_t           inst,
                                           const mesa_port_no_t        port_no,
                                           mesa_phy_10g_base_kr_conf_t *const kr_conf)
    CAP(PHY_10G);

/**
 * \brief Set the configuration of host 10f_base_kr setting.
 * Note: The parameters cm1,c0, c1 have a range of -32..31. The Output signal from the KR circuit is symmetric,
 *       I.e. the voltage output is configured value + 1/2lsb. (ex: -1 => -1/2lsb voltage level, 0 => +1/2lsb voltage level
 *       The parameter ampl is set in steps of 25 mV, therefore the setting is rounded up to a multiplum og 25 mV,
 *       I.e. 1101..1125 => 1125 mVppd
 *
 * \param inst [IN]          Target instance reference.
 * \param port_no [IN]       Port number.
 * \param kr_conf [IN]       host 10f_base_kr configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERR_KR_CONF_NOT_SUPPORTED if the PHY on the port does not support 10GBASE_KR configuration
 *   MESA_RC_ERR_KR_CONF_INVALID_PARAMETER if one of the parameter values are invalid or (|cm1|+ |c0| + |c1|) > 31
 *   MESA_RC_ERROR on other errors.
 **/
mesa_rc mesa_phy_10g_base_kr_host_conf_set(const mesa_inst_t                 inst,
                                           const mesa_port_no_t              port_no,
                                           const mesa_phy_10g_base_kr_conf_t *const kr_conf)
    CAP(PHY_10G);

/**
 * \brief Get the status of Output Buffer.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param ob_status [OUT]   Status of output buffer
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_ob_status_get(const mesa_inst_t        inst,
                                   const mesa_port_no_t     port_no,
                                   mesa_phy_10g_ob_status_t *const ob_status)
    CAP(PHY_10G);

/** \brief 10G Phy link and fault status for all sublayers */
typedef struct {
    mesa_sublayer_status_t pma;        /**< Status for Line PMA sublayer */
    mesa_sublayer_status_t hpma;       /**< Status for Host PMA sublayer */
    mesa_sublayer_status_t wis;        /**< Status for WIS sublayer */
    mesa_sublayer_status_t pcs;        /**< Status for Line PCS sublayer */
    mesa_sublayer_status_t hpcs;       /**< Status for HOST PCS sublayer,pcs xaui in case of venice */
    mesa_sublayer_status_t xs;         /**< Status for XAUI sublayer */
    mesa_bool_t            lpcs_1g;    /**< Status for Line 1G_PCS sublayer */
    mesa_bool_t            hpcs_1g;    /**< Status for Host 1G_PCS sublayer */
    mesa_bool_t            status;     /**< Status of whole PHY , based on operation mode and PHY type*/
    mesa_bool_t            block_lock; /**< Gives block lock information */
    mesa_bool_t            lopc_stat;  /**< LOPC status */
} mesa_phy_10g_status_t CAP(PHY_10G);

/**
 * \brief Get the link and fault status of the PHY sublayers.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param status [IN]   Status of all sublayers
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/

mesa_rc mesa_phy_10g_status_get(const mesa_inst_t     inst,
                                const mesa_port_no_t  port_no,
                                mesa_phy_10g_status_t *const status)
    CAP(PHY_10G);

/**
 * \brief Get the status of PHY including sub layers
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param status [IN]   Status of PLL,SUB layers
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_serdes_status_get(const mesa_inst_t            inst,
                                       const mesa_port_no_t         port_no,
                                       mesa_phy_10g_serdes_status_t *const status)
    CAP(PHY_10G);

/**
 * \brief Reset the phy.  Phy is reset to default values.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_reset(const mesa_inst_t    inst,
                           const mesa_port_no_t port_no)
    CAP(PHY_10G);

/**
 * Advertisement Word (Refer to IEEE 802.3 Clause 37):
 *  MSB                                                                         LSB
 *  D15  D14  D13  D12  D11  D10   D9   D8   D7   D6   D5   D4   D3   D2   D1   D0
 * +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
 * | NP | Ack| RF2| RF1|rsvd|rsvd|rsvd| PS2| PS1| HD | FD |rsvd|rsvd|rsvd|rsvd|rsvd|
 * +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
 **/

/** \brief Auto-negotiation remote fault type */
typedef enum
{
    MESA_PHY_10G_CLAUSE_37_RF_LINK_OK,        /**< Link OK */
    MESA_PHY_10G_CLAUSE_37_RF_OFFLINE,        /**< Off line */
    MESA_PHY_10G_CLAUSE_37_RF_LINK_FAILURE,   /**< Link failure */
    MESA_PHY_10G_CLAUSE_37_RF_AUTONEG_ERROR   /**< Autoneg error */
} mesa_phy_10g_clause_37_remote_fault_t CAP(PHY_10G);


/** \brief Advertisement control data for Clause 37 aneg */
typedef struct
{
    mesa_bool_t                           fdx;               /**< (FD) */
    mesa_bool_t                           hdx;               /**< (HD) */
    mesa_bool_t                           symmetric_pause;   /**< (PS1) */
    mesa_bool_t                           asymmetric_pause;  /**< (PS2) */
    mesa_phy_10g_clause_37_remote_fault_t remote_fault;      /**< (RF1) + (RF2) */
    mesa_bool_t                           acknowledge;       /**< (Ack) */
    mesa_bool_t                           next_page;         /**< (NP) */
} mesa_phy_10g_clause_37_adv_t CAP(PHY_10G);

/** \brief Clause 37 Auto-negotiation status */
typedef struct
{
    mesa_bool_t link;                                             /**< FALSE if link has been down since last status read */
    struct {
        mesa_bool_t                  complete;             /**< Aneg completion status */
        mesa_phy_10g_clause_37_adv_t partner_advertisement;/**< Clause 37 Advertisement control data */
    } autoneg;                                             /**< Autoneg status */
} mesa_phy_10g_clause_37_status_t CAP(PHY_10G);

/** \brief Clause 37 Auto-negotiation status for line and host */
typedef struct
{
    mesa_phy_10g_clause_37_status_t line;  /**< Line clause 37 status */
    mesa_phy_10g_clause_37_status_t host;  /**< Host clause 37 status */
} mesa_phy_10g_clause_37_cmn_status_t CAP(PHY_10G);


/** \brief Clause 37 control struct */
typedef struct
{
    mesa_bool_t                  enable;        /**< Enable of Autoneg */
    mesa_phy_10g_clause_37_adv_t advertisement; /**< Clause 37 Advertisement data */
    mesa_bool_t                  enable_pass_thru; /**< Enables pass through mode in VENICE */
    mesa_bool_t                  line;           /**< Line:TRUE for line side */
    mesa_bool_t                  host;           /**< Host:True for host side */
    mesa_bool_t                  l_h;           /**< Both Host and line side */
} mesa_phy_10g_clause_37_control_t CAP(PHY_10G);


/**
 * \brief Get clause 37 status.
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param status  [OUT] Clause 37 status of the line and host link.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_clause_37_status_get(const mesa_inst_t                          inst,
                                          mesa_port_no_t                             port_no,
                                          mesa_phy_10g_clause_37_cmn_status_t *const status)
    CAP(PHY_10G);


/**
 * \brief Get clause 37 control configuration.
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param control [OUT] Clause 37 configuration.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_clause_37_control_get(const mesa_inst_t                inst,
                                           const mesa_port_no_t             port_no,
                                           mesa_phy_10g_clause_37_control_t *const control)
    CAP(PHY_10G);

/**
 * \brief Set clause 37 control configuration.
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param control [OUT] Clause 37 configuration.
 *  Same configuration is applied to Host and Line interface.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_clause_37_control_set(const mesa_inst_t                      inst,
                                           const mesa_port_no_t                   port_no,
                                           const mesa_phy_10g_clause_37_control_t *const control)
    CAP(PHY_10G);

/** \brief 10G loopback types */
typedef enum {
    MESA_LB_NONE,                /**< No looback   */
    MESA_LB_SYSTEM_XS_SHALLOW,   /**< System Loopback B,  XAUI -> XS -> XAUI   4x800E.13,  Venice: H2  */
    MESA_LB_SYSTEM_XS_DEEP,      /**< System Loopback C,  XAUI -> XS -> XAUI   4x800F.2,  Venice: N.A.     */
    MESA_LB_SYSTEM_PCS_SHALLOW,  /**< System Loopback E,  XAUI -> PCS FIFO -> XAUI 3x8005.2,  Venice: N.A. */
    MESA_LB_SYSTEM_PCS_DEEP,     /**< System Loopback G,  XAUI -> PCS -> XAUI  3x0000.14,  Venice: H3    */
    MESA_LB_SYSTEM_PMA,          /**< System Loopback J,  XAUI -> PMA -> XAUI  1x0000.0,  Venice: H4     */
    MESA_LB_NETWORK_XS_SHALLOW,  /**< Network Loopback D,  XFI -> XS -> XFI   4x800F.1,  Venice: N.A.       */
    MESA_LB_NETWORK_XS_DEEP,     /**< Network Loopback A,  XFI -> XS -> XFI   4x0000.1  4x800E.13=0,  Venice: L1  */
    MESA_LB_NETWORK_PCS,         /**< Network Loopback F,  XFI -> PCS -> XFI  3x8005.3,  Venice: L2       */
    MESA_LB_NETWORK_WIS,         /**< Network Loopback H,  XFI -> WIS -> XFI  2xE600.0,  Venice: N.A.       */
    MESA_LB_NETWORK_PMA,         /**< Network Loopback K,  XFI -> PMA -> XFI  1x8000.8,  Venice: L3       */
    /* Venice specific loopbacks, the Venice implementation is different, and therefore the loopbacks are not exactly the same */
    MESA_LB_H2,                  /**< Host Loopback 2, 40-bit XAUI-PHY interface Mirror XAUI data */
    MESA_LB_H3,                  /**< Host Loopback 3, 64-bit PCS after the gearbox FF00 repeating IEEE PCS system loopback */
    MESA_LB_H4,                  /**< Host Loopback 4, 64-bit WIS FF00 repeating IEEE WIS system loopback */
    MESA_LB_H5,                  /**< Host Loopback 5, 1-bit SFP+ after SerDes Mirror XAUI data IEEE PMA system loopback */
    MESA_LB_H6,                  /**< Host Loopback 6, 32-bit XAUI-PHY interface Mirror XAUI data */
    MESA_LB_L0,                  /**< Line Loopback 0, 4-bit XAUI before SerDes Mirror SFP+ data */
    MESA_LB_L1,                  /**< Line Loopback 1, 4-bit XAUI after SerDes Mirror SFP+ data IEEE PHY-XS network loopback */
    MESA_LB_L2,                  /**< Line Loopback 2, 64-bit XGMII after FIFO Mirror SFP+ data */
    MESA_LB_L3,                  /**< Line Loopback 3, 64-bit PMA interface Mirror SFP+ data */
    MESA_LB_L2C,                 /* Line loopback 4 after cross connect*/
} mesa_lb_type_t CAP(PHY_10G);


/** \brief 10G Phy system and network loopbacks */
typedef struct {
    mesa_lb_type_t lb_type;          /**< Looback types                                          */
    mesa_bool_t    enable;                     /**< Enable/Disable loopback given in \<lb_type\>           */
} mesa_phy_10g_loopback_t CAP(PHY_10G);

/**
 * \brief Enable/Disable a phy network or system loopback. \n
 * Only one loopback mode can be active at the same time.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param loopback [IN] Loopback settings. When disabling a loopback, the lb_type is ignored, i.e. the active loopback is disabled.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.\n
 *       Error conditions:
 *           Loopback not supported for the PHY
 *           Attempt to enable loopback while loopback is already active
 *           Attempt to disable loopback while no loopback is active
 **/
mesa_rc mesa_phy_10g_loopback_set(const mesa_inst_t             inst,
                                  const mesa_port_no_t          port_no,
                                  const mesa_phy_10g_loopback_t *const loopback)
    CAP(PHY_10G);

/**
 * \brief Get loopback settings.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param loopback [OUT] Current loopback settings.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_loopback_get(const mesa_inst_t       inst,
                                  const mesa_port_no_t    port_no,
                                  mesa_phy_10g_loopback_t *const loopback)
    CAP(PHY_10G);

/** \brief 10G Phy PCS counters */
typedef struct {
    mesa_bool_t block_lock_latched; /**< Latched block status      */
    mesa_bool_t high_ber_latched;   /**< Lathced high ber status   */
    uint8_t     ber_cnt;            /**< BER counter. Saturating, clear on read */
    uint8_t     err_blk_cnt;        /**< ERROR block counter. Saturating, clear on read */
} mesa_phy_pcs_cnt_t CAP(PHY_10G);

/** \brief 10G Phy Sublayer counters */
typedef struct {
//  mesa_phy_pma_cnt_t pma;
//  mesa_phy_wis_cnt_t wis;
    mesa_phy_pcs_cnt_t pcs;  /**< PCS counters */
//  mesa_phy_xs_cnt_t xs;
} mesa_phy_10g_cnt_t CAP(PHY_10G);

/**
 * \brief Get counters.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param cnt [OUT] Phy counters
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_cnt_get(const mesa_inst_t    inst,
                             const mesa_port_no_t port_no,
                             mesa_phy_10g_cnt_t   *const cnt)
    CAP(PHY_10G);

/** \brief 10G Phy power setting */
typedef enum {
    MESA_PHY_10G_POWER_ENABLE,  /**< Enable Phy power for all sublayers */
    MESA_PHY_10G_POWER_DISABLE  /**< Disable Phy power for all sublayers*/
} mesa_phy_10g_power_t CAP(PHY_10G);


/**
 * \brief Get the power settings
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param power [OUT] power settings
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_power_get(const mesa_inst_t    inst,
                               const mesa_port_no_t port_no,
                               mesa_phy_10g_power_t *const power)
    CAP(PHY_10G);

/**
 * \brief Set the power settings.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param power [IN] power settings
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_power_set(const mesa_inst_t          inst,
                               const mesa_port_no_t       port_no,
                               const mesa_phy_10g_power_t *const power)
    CAP(PHY_10G);

/**
 * \brief Gives a True/False value if the Phy is supported by the API\n
 *  Only Vitesse phys are supported.  mesa_phy_10g_mode_set() must be applied.
 *
 * \param inst [IN] Target instance reference.
 * \param port_no [IN]  Port number.
 *
 * \return
 *   TRUE  : Phy is supported.\n
 *   FALSE : Phy is not supported.
 **/
mesa_bool_t mesa_phy_10G_is_valid(const mesa_inst_t    inst,
                                  const mesa_port_no_t port_no)
    CAP(PHY_10G);

/** \brief 10G Phy Failover Mode Setting */
typedef enum {
    MESA_PHY_10G_PMA_TO_FROM_XAUI_NORMAL,         /**< PMA_0/1 to XAUI_0/1. 8487: XAUI 0 to PMA 0 */
    MESA_PHY_10G_PMA_TO_FROM_XAUI_CROSSED,        /**< PMA_0/1 to XAUI_1/0. 8487: XAUI 1 to PMA 0 */
    MESA_PHY_10G_PMA_0_TO_FROM_XAUI_0_TO_XAUI_1,  /**< PMA 0 to/from XAUI 0 and to XAUI 1 */
    MESA_PHY_10G_PMA_0_TO_FROM_XAUI_1_TO_XAUI_0,  /**< PMA 0 to/from XAUI 1 and to XAUI 0 */
    MESA_PHY_10G_PMA_1_TO_FROM_XAUI_0_TO_XAUI_1,  /**< PMA 1 to/from XAUI 0 and to XAUI 1.      VSC8487:N/A */
    MESA_PHY_10G_PMA_1_TO_FROM_XAUI_1_TO_XAUI_0,  /**< PMA 1 to/from XAUI 1 and to XAUI 0.      VSC8487:N/A */
} mesa_phy_10g_failover_mode_t CAP(PHY_10G);

/**
 * \brief Set the failover mode
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number. (Use any port within the phy).
 * \param mode [IN]     Failover mode
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_failover_set(const mesa_inst_t            inst,
                                  const mesa_port_no_t         port_no,
                                  mesa_phy_10g_failover_mode_t *const mode)
    CAP(PHY_10G);

/**
 * \brief Get the failover mode
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param mode [OUT] failover mode
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_failover_get(const mesa_inst_t            inst,
                                  const mesa_port_no_t         port_no,
                                  mesa_phy_10g_failover_mode_t *const mode)
    CAP(PHY_10G);

/** \brief 10G Phy Automatic Failover Event Setting */
typedef enum {
    MESA_PHY_10G_AUTO_FAILOVER_EVENT_PCS_LINK_STATUS, /**< PCS link status            */
    MESA_PHY_10G_AUTO_FAILOVER_EVENT_SERDES_LOS,      /**< LOS from SERDES            */
    MESA_PHY_10G_AUTO_FAILOVER_EVENT_WIS_LOF,         /**< LOF from Line WIS          */
    MESA_PHY_10G_AUTO_FAILOVER_EVENT_GPIO,            /**< External GPIO input        */
    MESA_PHY_10G_AUTO_FAILOVER_EVENT_NONE,            /**< Manual switching to be done*/
} mesa_phy_10g_auto_failover_event_t CAP(PHY_10G);


/** \brief 10G PHY Automatic Failover Filter */
typedef enum {
    MESA_PHY_10G_AUTO_FAILOVER_FILTER_NONE,      /**< No filter configuration    */
    MESA_PHY_10G_AUTO_FAILOVER_FILTER_CNT_B2316, /**< False condition, upper 8 bits of 24-bit threshold*/
    MESA_PHY_10G_AUTO_FAILOVER_FILTER_CNT_B70,   /**< False condition, lower 8 bits of 24-bit threshold*/
    MESA_PHY_10G_AUTO_FAILOVER_FILTER_CNT_A2316, /**< True condition, upper 8 bits of 24-bit threshold */
    MESA_PHY_10G_AUTO_FAILOVER_FILTER_CNT_A70,   /**< True condition, lower 8 bits of 24-bit threshold */
} mesa_phy_10g_auto_failover_filter_t CAP(PHY_10G);

/** \brief 10G PHY Automatic Failover configuration */
typedef struct {
    mesa_port_no_t   port_no;               /**< port number         */
    mesa_phy_10g_auto_failover_event_t evnt;/**< Auto failover event */
    uint16_t trig_ch_id;                        /**< Channel ID that triggers event  */
    mesa_bool_t is_host_side;                   /**< Protection switch configuration is on line or host side */
    uint16_t channel_id;                        /**< channel to be switched.         */
    uint16_t chip_no;                           /**< Represents chip id incase of multiple PHYs              */
    mesa_gpio_10g_no_t v_gpio;              /**< virtual GPIO pin to be triggering the event */
    mesa_gpio_10g_no_t a_gpio;              /**< actual GPIO pin to be triggering the event */
    mesa_bool_t enable;                            /**< Enable or disable auto failover */
    mesa_phy_10g_auto_failover_filter_t filter; /**< Number of CSR clock cycles */
    uint16_t fltr_val;                           /**< value of filter if chosen */
} mesa_phy_10g_auto_failover_conf_t CAP(PHY_10G);

/**
 * \brief Set the automatic failover mode
 *
 * \param inst [IN]     Target instance reference.
 * \param mode [IN]     Automatic Failover mode
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_auto_failover_set(const mesa_inst_t                 inst,
                                       mesa_phy_10g_auto_failover_conf_t *const mode)
    CAP(PHY_10G);

/**
 * \brief Get the Automatic failover mode Configuration
 *
 * \param inst [IN]     Target instance reference.
 * \param mode [OUT] failover mode
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_auto_failover_get(const mesa_inst_t                 inst,
                                       mesa_phy_10g_auto_failover_conf_t *const mode)
    CAP(PHY_10G);

/** \brief VSCOPE scan types */
typedef enum {
	MESA_PHY_10G_FAST_SCAN, /**<selects the fast scan feature */
	MESA_PHY_10G_FAST_SCAN_PLUS, /**<selects the fast scan feature with diagonal points */
	MESA_PHY_10G_QUICK_SCAN, /**<selects the quick scan feature */
	MESA_PHY_10G_FULL_SCAN, /**<selects the full scan freature */
} mesa_phy_10g_vscope_scan_t CAP(PHY_10G);

/** \ brief VSCOPE scan configuration */
typedef struct {
    mesa_phy_10g_vscope_scan_t scan_type;   /**<selects the type of scan to be implemented */
    mesa_bool_t                line;        /**<select line side or host side, TRUE for line side */
    mesa_bool_t                enable;      /**<enable or disable vscope fast scan*/
    uint32_t                   error_thres; /**<error_threshold for vscope calculations */
} mesa_phy_10g_vscope_conf_t CAP(PHY_10G);

/**
 * \brief set VSCOPE fast scan configuration
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number
 * \param conf    [IN]  VSCOPE fast scan configuration
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
**/
mesa_rc mesa_phy_10g_vscope_conf_set(const mesa_inst_t                inst,
                                     const mesa_port_no_t             port_no,
                                     const mesa_phy_10g_vscope_conf_t *const conf)
    CAP(PHY_10G);

/**
 * \brief get VSCOPE fast scan configuration
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number
 * \param conf    [OUT]  VSCOPE fast scan configuration
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
**/
mesa_rc mesa_phy_10g_vscope_conf_get(const mesa_inst_t          inst,
                                     const mesa_port_no_t       port_no,
                                     mesa_phy_10g_vscope_conf_t *const conf)
    CAP(PHY_10G);

#define BOOLEAN_STORAGE_COUNT  6    /**<mesa_bool_t parameters to be stored during Vscope Scan */
#define UNSIGNED_STORAGE_COUNT 5    /**<UNSIGNED parameters to be stored during Vscope Scan */

/** \brief VSCOPE fast scan storage */
typedef struct {
    mesa_bool_t  ib_storage_bool[BOOLEAN_STORAGE_COUNT]; /**<boolean values to be stored in mesa_state during vscope fast scan configuration */
    uint32_t     ib_storage[UNSIGNED_STORAGE_COUNT];     /**<uint8_t values to be stored in mesa_state during vscope fast scan configuration */
} mesa_phy_10g_ib_storage_t CAP(PHY_10G);

/**\brief VSCOPE scan configuration */
typedef struct{
    mesa_bool_t     line;    /**<selects line or host side, 1 for line */
    uint32_t        x_start; /**<start value for x (0-127)*/
    uint32_t        y_start; /**<start value for y (0-63)*/
    uint32_t        x_incr;  /**<increment value for x during the scan */
    uint32_t        y_incr;  /**<increment value for y during the scan */
    uint32_t        x_count; /**<max value for x ( upto which scan is to be performed) */
    uint32_t        y_count; /**<max value for y ( upto which scan is to be performed) */
    uint32_t        ber;     /**<bit error rate */
} mesa_phy_10g_vscope_scan_conf_t CAP(PHY_10G);

#define PHASE_POINTS 128 /**<phase points range from 0-127 */
#define AMPLITUDE_POINTS 64 /**<amplitude points range from 0-63 */

/**\ brief Vscope eye scan status*/
typedef struct {
    mesa_phy_10g_vscope_scan_conf_t scan_conf; /**<scan configuration data */
    int32_t  error_free_x;	/**<error free x values in case of fast eye scan */
    int32_t  error_free_y;	/**<error free y values in case of fast eye scan */
    int32_t  amp_range;		/**<amp range in case of fast eye scan */
    uint32_t errors[PHASE_POINTS][AMPLITUDE_POINTS];	/**<error matrix in full scan mode */
} mesa_phy_10g_vscope_scan_status_t CAP(PHY_10G);

/** \brief VSCOPE fast scan status
 * Set VSCOPE fast scan configuration
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number
 * \param conf    [IN]  VSCOPE fast scan configuration
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_vscope_scan_status_get(const mesa_inst_t                 inst,
                                            const mesa_port_no_t              port_no,
                                            mesa_phy_10g_vscope_scan_status_t *const conf)
    CAP(PHY_10G);

/* 10G PHY PRBS implementation */

/** \brief 10G PHY direction */
typedef enum {
    MESA_PHY_10G_DIRECTION_HOST, /**< To configure HOST PRBS */
    MESA_PHY_10G_DIRECTION_LINE, /**< To configure LINE PRBS */
    MESA_PHY_10G_DIRECTION_CNT,  /**< ENUM Count             */
} mesa_phy_10g_direction_t CAP(PHY_10G);

/** \brief 10G PHY PRBS type */
typedef enum {
    MESA_PHY_10G_PRBS_TYPE_SERDES, /**< Configure SERDES prbs */
    MESA_PHY_10G_PRBS_TYPE_PCS,    /**< Configure PCS prbs    */
    MESA_PHY_10G_PRBS_TYPE_CNT,    /**< ENUM Count            */
} mesa_phy_10g_prbs_type_t CAP(PHY_10G);

/** \brief 10G PHY prbs generator configuration */
typedef struct {
    /**
     * Enable or disable prbs generator.
     */
    mesa_bool_t enable;

    /**
     * Selects the prbs to be implemented.
     * Minimum is 0 and maximum is 5.
     * Only used if prbs type is MESA_PHY_10G_PRBS_TYPE_SERDES.
     */
    uint32_t prbsn_sel;

    /**
     * Set to TRUE to invert PRBS TX pattern.
     */
    mesa_bool_t prbsn_tx_io;

    /**
     * Select the prbs interface width.
     * Range 0-5
     */
    uint8_t prbsn_tx_iw;

    /**
     * Enable or disable PCS-prbs.
     * Only used if prbs type is MESA_PHY_10G_PRBS_TYPE_PCS.
     */
    mesa_bool_t prbs_gen_pcs;
} mesa_phy_10g_prbs_generator_conf_t CAP(PHY_10G);

/**
 * \brief Get prbs generator configuration
 * \param inst      [IN]  Target instance reference
 * \param port_no   [IN]  Port number
 * \param type      [IN]  Prbs type
 * \param direction [IN]  Direction of configuration
 * \param conf      [OUT] Prbs generator configuration
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_prbs_generator_conf_get(const mesa_inst_t                  inst,
                                             const mesa_port_no_t               port_no,
                                             const mesa_phy_10g_prbs_type_t     type,
                                             const mesa_phy_10g_direction_t     direction,
                                             mesa_phy_10g_prbs_generator_conf_t *const conf) CAP(PHY_10G);

/**
 * \brief Set prbs generator configuration
 * \param inst      [IN] Target instance reference
 * \param port_no   [IN] Port number
 * \param type      [IN] Prbs type
 * \param direction [IN] Direction of configuration
 * \param conf      [IN] Prbs generator configuration
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_prbs_generator_conf_set(const mesa_inst_t                        inst,
                                             const mesa_port_no_t                     port_no,
                                             const mesa_phy_10g_prbs_type_t           type,
                                             const mesa_phy_10g_direction_t           direction,
                                             const mesa_phy_10g_prbs_generator_conf_t *const conf) CAP(PHY_10G);

/** \brief 10G PHY prbs analyzer/monitor configuration */
typedef struct {
    /**
     * Enable or disable the prbs monitor
     */
    mesa_bool_t enable;

    /**
     * Threshold to iterate counter for max_bist_frames [15:0]
     */
    uint16_t max_bist_frames;

    /**
     * States in which error counting is enabled.
     *   0:wait_stable + stable + check
     *   1:stable + check
     *   2:check
     *   3:all but IDLE
     */
    uint16_t error_states;

    /**
     * DES interface width.
     *   0:  8
     *   1: 10
     *   2: 16
     *   3: 20
     *   4: 32
     *   5: 40 (default)
     */
    uint16_t des_interface_width;

    /**
     * Selects the prbs to be implemented.
     * Minimum is 0 and maximum is 5.
     * Only used if prbs type is MESA_PHY_10G_PRBS_TYPE_SERDES.
     */
    uint16_t prbsn_sel;

    /**
     * Set to TRUE to enable PRBS checker input inversion
     */
    mesa_bool_t prbs_check_input_invert;

    /**
     * Number of consecutive errors/non-errors before transitioning to
     * respective state.
     * value = number-of-40-bits-words + 1
     */
    uint16_t no_of_errors;

    /**
     * Select BIST mode.
     *   0: off
     *   1: BIST
     *   2: BER
     *   3: CONT(infinite mode)
     */
    uint16_t bist_mode;

    /**
     * Enable or diable PCS-prbs test pattern mode on RX path.
     * Only used if prbs type is MESA_PHY_10G_PRBS_TYPE_PCS.
     */
    mesa_bool_t prbs_mon_pcs;
} mesa_phy_10g_prbs_monitor_conf_t CAP(PHY_10G);

/**
 * \brief Get prbs monitor/analyzer configuration
 * \param inst      [IN]  Target instance reference
 * \param port_no   [IN]  Port number
 * \param type      [IN]  Prbs type
 * \param direction [IN]  Direction of configuration
 * \param conf      [OUT] Prbs monitor configuration
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_prbs_monitor_conf_get(const mesa_inst_t                inst,
                                           const mesa_port_no_t             port_no,
                                           const mesa_phy_10g_prbs_type_t   type,
                                           const mesa_phy_10g_direction_t   direction,
                                           mesa_phy_10g_prbs_monitor_conf_t *const conf) CAP(PHY_10G);

/**
 * \brief Set prbs monitor/analyzer configuration
 * \param inst      [IN] Target instance reference
 * \param port_no   [IN] Port number
 * \param type      [IN] Prbs type
 * \param direction [IN] Direction of configuration
 * \param conf      [IN] Prbs monitor configuration
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_prbs_monitor_conf_set(const mesa_inst_t                      inst,
                                           const mesa_port_no_t                   port_no,
                                           const mesa_phy_10g_prbs_type_t         type,
                                           const mesa_phy_10g_direction_t         direction,
                                           const mesa_phy_10g_prbs_monitor_conf_t *const conf) CAP(PHY_10G);

/** \brief 10G PHY prbs analyzer/monitor status */
typedef struct {
    /**
     * Error stautus of PRBS
     */
    uint32_t error_status;

    /**
     * PRBS status
     */
    uint32_t prbs_status;

    /**
     * Main status
     */
    uint32_t main_status;

    /**
     * Data input is unchanged for all 40 parallel bits for at least 7 clock
     * cycles.
     */
    mesa_bool_t stuck_at_par;

    /**
     * Data input is constantly 0 or constantly 1 for all
     * 40 parallel bits for at least 7 clock cycles cycles.
     */
    mesa_bool_t stuck_at_01;

    /**
     * TRUE if no sync found since BIST enabled
     */
    mesa_bool_t no_sync;

    /**
     * TRUE if BIST input data not stable
     */
    mesa_bool_t instable;

    /**
     * TRUE if BIST not complete yet, that is, it has not reached a stable
     * state.
     */
    mesa_bool_t incomplete;

    /**
     * TRUE if BIST is active but has not entered a final state
     */
    mesa_bool_t active;

    /**
     * Capture PCS-PRBS status on RX path.
     * Only used if prbs type is MESA_PHY_10G_PRBS_TYPE_PCS.
     */
    uint32_t prbs_error_count_pcs;
} mesa_phy_10g_prbs_monitor_status_t CAP(PHY_10G);

/**
 * \brief Get prbs monitor/analyzer status
 * Status is retrieved after a possible monitor reset (when reset == TRUE).
 * \param inst       [IN]  Target instance reference
 * \param port_no    [IN]  Port number
 * \param type       [IN]  Prbs type
 * \param direction  [IN]  Direction of monitor status
 * \param reset      [IN]  Reset monitor state
 * \param mon_status [OUT] Prbs Monitor status
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_prbs_monitor_status_get(const mesa_inst_t                  inst,
                                             const mesa_port_no_t               port_no,
                                             const mesa_phy_10g_prbs_type_t     type,
                                             const mesa_phy_10g_direction_t     direction,
                                             const mesa_bool_t                  reset,
                                             mesa_phy_10g_prbs_monitor_status_t *const mon_status) CAP(PHY_10G);

/**
 * \brief 10G PHY prbs generator configuration
 * This structure is obsolete.
 * Use mesa_phy_10g_prbs_generator_conf_t instead.
 */
typedef struct {
    mesa_bool_t enable;    /**< Enable or disable prbs generator                      */
    uint32_t    prbsn_sel; /**< Select the prbs to be implemented, min == 0, max == 5 */
    mesa_bool_t line;      /**< Select the line side or host side, 1 for line side    */
} mesa_phy_10g_prbs_gen_conf_t CAP(PHY_10G);

/**
 * \brief Get prbs generator configuration
 * This API is obsolete. Use mesa_phy_10g_prbs_generator_conf_get() instead.
 * \param inst    [IN]    Target instance reference
 * \param port_no [IN]    Port number
 * \param conf    [INOUT] Prbs configuration (line member is an [IN]
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MEsA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_prbs_gen_conf_get(const mesa_inst_t            inst,
                                       const mesa_port_no_t         port_no,
                                       mesa_phy_10g_prbs_gen_conf_t *const conf) CAP(PHY_10G);

/**
 * \brief Set prbs generator configuration
 * This API is obsolete. Use mesa_phy_10g_prbs_generator_conf_set() instead.
 * \param inst    [IN] Target instance reference
 * \param port_no [IN] Port number
 * \param conf    [IN] Prbs configuration
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_prbs_gen_conf(const mesa_inst_t            inst,
                                   const mesa_port_no_t         port_no,
                                   mesa_phy_10g_prbs_gen_conf_t *const conf) CAP(PHY_10G);

/**
 * \brief 10G PHY prbs monitor status and configuration
 * This structure is obsolete.
 * Use mesa_phy_10g_prbs_monitor_conf_t instead.
 */
typedef struct {
    mesa_bool_t enable;                  /**< Enable or disable the prbs monitor */
    mesa_bool_t line;                    /**< Select line side or host side, 1 for line side */
    uint16_t    max_bist_frames;         /**< Threshold to iterate counter for max_bist_frames [15:0] */
    uint16_t    error_states;            /**< States in which error counting is enabled3:all but IDLE; 2:check 1:stable+check,0:wait_stable+stable+check */
    uint16_t    des_interface_width;     /**< DES interface width 0:8,1:10,2:16,3:20,4:32,5:40 (default) */
    uint16_t    prbsn_sel;               /**< select the prbs to be implemented, min=0, max=5> */
    mesa_bool_t prbs_check_input_invert; /**< Snables PRBS checker input inversion */
    uint16_t    no_of_errors;            /**< Number of consecutive errors/non-errors before transitioning to respective state , value = num-40-bits-words + 1 */
    uint16_t    bist_mode;               /**< 0: off, 1: BIST, 2: BER, 3:CONT(infinite mode) */
    uint32_t    error_status;            /**< Error stautus of PRBS */
    uint32_t    PRBS_status;             /**< PRBS status */
    uint32_t    main_status;             /**< Main stauts */
    mesa_bool_t stuck_at_par;            /**< Data input is unchanged for all 40 parallel bits for at least 7 clock cycles */
    mesa_bool_t stuck_at_01;             /**< Data input is unchanged for all 40 parallel bits for at least 7 clock cycles */
    mesa_bool_t no_sync;                 /**< no sync found since BIST enabled */
    mesa_bool_t instable;                /**< BIST input data not stable */
    mesa_bool_t incomplete;              /**< BIST not complete  i.e. it has not reached a stable state */
    mesa_bool_t active;                  /**< BIST is active but has not entered a final state */
} mesa_phy_10g_prbs_mon_conf_t CAP(PHY_10G);

/**
 * \brief Get prbs monitor configuration and status
 * This API is obsolete. Use mesa_phy_10g_prbs_monitor_conf_get() and
 * mesa_phy_10g_prbs_monitor_status_get() instead.
 * \param inst    [IN]    Target instance reference
 * \param port_no [IN]    Port number
 * \param conf    [INOUT] Prbs Monitor configuration (line member is an IN)
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_prbs_mon_conf_get(const mesa_inst_t            inst,
                                       const mesa_port_no_t         port_no,
                                       mesa_phy_10g_prbs_mon_conf_t *const conf) CAP(PHY_10G);

/**
 * \brief Set prbs monitor configuration
 * This API is obsolete. Use mesa_phy_10g_prbs_monitor_conf_set() instead.
 * \param inst    [IN] Target instance reference
 * \param port_no [IN] Port number
 * \param conf    [IN] Prbs monitor configuration
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_prbs_mon_conf(const mesa_inst_t            inst,
                                   const mesa_port_no_t         port_no,
                                   mesa_phy_10g_prbs_mon_conf_t *const conf) CAP(PHY_10G);

/** \brief 10G PHY sgmii mode lane select configuration */
typedef enum{
    MESA_PHY_10G_SGMII_MODE_LANE_3,   /**<selects lane 3 as the datapath for SGMII */
    MESA_PHY_10G_SGMII_MODE_LANE_0,   /**<selects lane 0 as the datapath for SGMII */
}mesa_phy_10g_sgmii_lane_select_t CAP(PHY_10G);

/** \brief 10G PHY Packet generator configuration */
typedef struct {
    mesa_bool_t     enable;         /**< Enable or disable packet generator */
    mesa_bool_t     ptp;            /**< PTP or standard frame              */
    mesa_bool_t     ingress;        /**< Ingress or egress                  */
    mesa_bool_t     frames ;        /**< frames or idles                    */
    mesa_bool_t     frame_single;   /**< Generate single frame              */
    uint16_t        etype;          /**< Ethertype                          */
    uint8_t         pkt_len;        /**< Packet length,min=64,max=16KB      */
    uint32_t        ipg_len;        /**< Inter Packet Gap                   */
    mesa_mac_addr_t smac;           /**< Source MAC address                 */
    mesa_mac_addr_t dmac;           /**< Destination MAC address            */
    uint8_t         ptp_ts_sec;     /**< Seconds part of timestamp value    */
    uint8_t         ptp_ts_ns;      /**< NanoSeconds part of ts value       */
    uint8_t         srate;          /**< Srate for ptp frames               */
} mesa_phy_10g_pkt_gen_conf_t CAP(PHY_10G);

/**
 * \brief Set Packet generation Configuration
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number
 * \param conf    [IN]  Packet generator configuration
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_pkt_gen_conf(const mesa_inst_t           inst,
                                  const mesa_port_no_t        port_no,
                                  mesa_phy_10g_pkt_gen_conf_t *const conf)
    CAP(PHY_10G);

/** \brief 10G PHY Packet monitor configuration */
typedef enum {
    MESA_PHY_10G_PKT_MON_RST_ALL,    /**< Reset all counters        */
    MESA_PHY_10G_PKT_MON_RST_GOOD,   /**< Reset good crc counter    */
    MESA_PHY_10G_PKT_MON_RST_BAD,    /**< Reset bad crc counter     */
    MESA_PHY_10G_PKT_MON_RST_FRAG,   /**< Reset Fragment counter    */
    MESA_PHY_10G_PKT_MON_RST_LFAULT, /**< Reset local fault counter */
    MESA_PHY_10G_PKT_MON_RST_BER,    /**< Reset Ber counter         */
    MESA_PHY_10G_PKT_MON_RST_NONE,   /**< None                      */
} mesa_phy_10g_pkt_mon_rst_t CAP(PHY_10G);

typedef uint32_t mesa_32_cntr_t CAP(PHY_10G);  /**< 32-bit counter         */

/** \brief 10G PHY Packet Monitor configuration */
typedef struct {
    mesa_bool_t enable;             /**< Enable or disable packet monitor  */
    mesa_bool_t update;             /**< update and reads monitor counters */
    mesa_phy_10g_pkt_mon_rst_t reset;  /**< resets all monitor counters       */
    mesa_32_cntr_t good_crc; /**< Good CRC packet count             */
    mesa_32_cntr_t bad_crc;  /**< Bad CRC packet count              */
    mesa_32_cntr_t frag;     /**< Fragmented packet count           */
    mesa_32_cntr_t lfault;   /**< Local fault packet count          */
    mesa_32_cntr_t ber;      /**< B-errored packet count            */
} mesa_phy_10g_pkt_mon_conf_t CAP(PHY_10G);

/** \brief 10G PHY timestamp value array(holder) */
typedef struct {
    uint16_t timestamp[10][5];      /**< 5 bytes each of 10 timestamp values */
} mesa_phy_10g_timestamp_val_t CAP(PHY_10G);

/**
 * \brief Set Packet Monitor Configuration
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number
 * \param ts_rd   [IN]  Flag to indicate that timestamp fifo is also to be read.
 * \param conf          Packet monitor configuration
 * \param conf_ts [OUT] Timestamp value array.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/


mesa_rc mesa_phy_10g_pkt_mon_conf(const mesa_inst_t            inst,
                                  const mesa_port_no_t         port_no,
                                  mesa_bool_t                  ts_rd,
                                  mesa_phy_10g_pkt_mon_conf_t  *const conf,
                                  mesa_phy_10g_timestamp_val_t *const conf_ts)
    CAP(PHY_10G);

/**
 * \brief Set/Get Packet mon Counters
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number
 * \param conf          Packet monitor configuration
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/


mesa_rc mesa_phy_10g_pkt_mon_counters_get(const mesa_inst_t           inst,
                                          const mesa_port_no_t        port_no,
                                          mesa_phy_10g_pkt_mon_conf_t *const conf)
    CAP(PHY_10G);


/** \brief 10g PHY type */
typedef enum {
    MESA_PHY_TYPE_10G_NONE = 0,/* Unknown  */
    MESA_PHY_TYPE_8484 = 8484, /* VSC8484  */
    MESA_PHY_TYPE_8486 = 8486, /* VSC8486  */
    MESA_PHY_TYPE_8487 = 8487, /* VSC8487  */
    MESA_PHY_TYPE_8488 = 8488, /* VSC8488  */
    MESA_PHY_TYPE_8489 = 8489, /* VSC8489  */
    MESA_PHY_TYPE_8489_15 = 848915, /* VSC8489-15 1-channel   */
    MESA_PHY_TYPE_8490 = 8490, /* VSC8490  */
    MESA_PHY_TYPE_8491 = 8491, /* VSC8491  */
    MESA_PHY_TYPE_8256 = 8256, /* VSC8256  */
    MESA_PHY_TYPE_8257 = 8257, /* VSC8257  */
    MESA_PHY_TYPE_8258 = 8258, /* VSC8258  */
    MESA_PHY_TYPE_8254 = 8254, /* VSC8254  */
} mesa_phy_10g_type_t CAP(PHY_10G);

/** \brief 10G PHY family */
typedef enum {
    MESA_PHY_FAMILY_10G_NONE,        /* Unknown */
    MESA_PHY_FAMILY_XAUI_XGMII_XFI,  /* VSC8486 */
    MESA_PHY_FAMILY_XAUI_XFI,        /* VSC8484, VSC8487, VSC8488 */
    MESA_PHY_FAMILY_VENICE,          /* VSC8489, VSC8490, VSC8491 */
    MESA_PHY_FAMILY_MALIBU,          /* VSC8256, VSC8257, VSC8258 */
} mesa_phy_10g_family_t CAP(PHY_10G);

#define MESA_PHY_10G_ONE_LINE_ACTIVE 0x08    /**< Bit indicating PHY vith only one line interface */
#define MESA_PHY_10G_MACSEC_DISABLED 0x04    /**< Bit indicating that macsec is disabled */
#define MESA_PHY_10G_TIMESTAMP_DISABLED 0x02 /**< Bit indicating that timestamp feature is disabled */
#define MESA_PHY_10G_MACSEC_KEY_128 0x01     /**< Bit indicating that only 128 bit macsec encryption key is supported, otherwise it is 128/256 key */


/** \brief 10G Phy part number and revision */
typedef struct
{
    uint16_t              part_number;    /**< Part number (Hex)  */
    uint16_t              revision;       /**< Chip revision      */
    uint16_t              channel_id;     /**< Channel id         */
    mesa_phy_10g_family_t family;         /**< Phy Family         */
    mesa_phy_10g_type_t   type;           /**< Phy id (Decimal)   */
    mesa_port_no_t        phy_api_base_no;/**< First API no within this phy (in case of multiple channels) */
    uint16_t              device_feature_status; /**< Device features depending on EFUSE */
} mesa_phy_10g_id_t CAP(PHY_10G);

/**
 * \brief Read the Phy Id
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param phy_id [OUT] The part number and revision.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_id_get(const mesa_inst_t    inst,
                            const mesa_port_no_t port_no,
                            mesa_phy_10g_id_t    *const phy_id)
    CAP(PHY_10G);

/* - GPIOs ------------------------------------------------------- */
/**
 * \brief GPIO configured mode
 **/

typedef enum {
    MESA_10G_PHY_GPIO_NOT_INITIALIZED,   /**< This GPIO pin has has been initialized by a call to API from application. aregisters contain power-up default value */
    MESA_10G_PHY_GPIO_OUT,               /**< Output enabled */
    MESA_10G_PHY_GPIO_IN,                /**< Input enabled */
    MESA_10G_PHY_GPIO_WIS_INT,           /**< Output WIS interrupt channel 0 or 1 (depending on port_no) enabled */
    /*    MESA_10G_PHY_GPIO_INT_FALLING,*/   /**< Input interrupt generated on falling edge */
    /*    MESA_10G_PHY_GPIO_INT_RAISING,*/   /**< Input interrupt generated on raising edge */
    /*    MESA_10G_PHY_GPIO_INT_CHANGED,*/   /**< Input interrupt generated on raising and falling edge */
    MESA_10G_PHY_GPIO_1588_LOAD_SAVE,    /**< Input 1588 load/save function */
    MESA_10G_PHY_GPIO_1588_1PPS_0,       /**< Output 1588 1PPS from channel 0 function */
    MESA_10G_PHY_GPIO_1588_1PPS_1,       /**< Output 1588 1PPS from channel 1 function */
    MESA_10G_PHY_GPIO_1588_1PPS_2,       /**< Output 1588 1PPS from channel 2 function */
    MESA_10G_PHY_GPIO_1588_1PPS_3,       /**< Output 1588 1PPS from channel 3 function */
    MESA_10G_PHY_GPIO_PCS_RX_FAULT,      /**< PCS_RX_FAULT (from channel 0 or 1) is transmitted on GPIO */
    MESA_10G_PHY_GPIO_SET_I2C_MASTER,    /**< Used in communicating with I2C client, like SPP+ */
    MESA_10G_PHY_GPIO_TX_ENABLE,         /**< Transmit enable           , MALIBU */
    MESA_10G_PHY_GPIO_LINE_PLL_STATUS,   /**< Line PLL Status           , MALIBU */
    MESA_10G_PHY_GPIO_HOST_PLL_STATUS,   /**< Host PLL Status           , MALIBU */
    MESA_10G_PHY_GPIO_RCOMP_BUSY,        /**< RCOMP busy Status         , MALIBU */
    MESA_10G_PHY_GPIO_CHAN_INT_0,        /**< Interrupt 0 from channel  , MALIBU */
    MESA_10G_PHY_GPIO_CHAN_INT_1,        /**< Interrupt 1 from channel  , MALIBU */
    MESA_10G_PHY_GPIO_1588_INT,          /**< 1588 Interrupt            , MALIBU */
    MESA_10G_PHY_GPIO_TS_FIFO_EMPTY,     /**< TS FIFO empty             , MALIBU */
    MESA_10G_PHY_GPIO_AGG_INT_0,         /**< Aggregated interrupt 0    , MALIBU */
    MESA_10G_PHY_GPIO_AGG_INT_1,         /**< Aggregated interrupt 1    , MALIBU */
    MESA_10G_PHY_GPIO_AGG_INT_2,         /**< Aggregated interrupt 2    , MALIBU */
    MESA_10G_PHY_GPIO_AGG_INT_3,         /**< Aggregated interrupt 3    , MALIBU */
    MESA_10G_PHY_GPIO_PLL_INT_0,         /**< Interrupt 0 from PLL      , MALIBU */
    MESA_10G_PHY_GPIO_PLL_INT_1,         /**< Interrupt 0 from PLL      , MALIBU */
    MESA_10G_PHY_GPIO_SET_I2C_SLAVE,     /**< I2C client set            , MALIBU */
    MESA_10G_PHY_GPIO_CRSS_INT,          /**< Cross Connect Interrupt   , MALIBU */
    MESA_10G_PHY_GPIO_LED,               /**< LED Setting               , MALIBU */
    MESA_10G_PHY_GPIO_DRIVE_LOW,         /**< GPIO output to LOW        , MALIBU */
    MESA_10G_PHY_GPIO_DRIVE_HIGH,        /**< GPIO output to HIGH       , MALIBU */
    /* More to come.. */
} mesa_10g_phy_gpio_t CAP(PHY_10G);                                  /**< Mode of this GPIO pin ,need to take care of source field too*/


/**
 * \brief GPIO internal signal types
 **/
typedef enum
{
    MESA_10G_GPIO_INTR_SGNL_I2C_MSTR_DATA_OUT,              /** GPIO outupt I2C server data out */
    MESA_10G_GPIO_INTR_SGNL_I2C_MSTR_CLK_OUT,               /** GPIO outupt I2C server clock out */
    MESA_10G_GPIO_INTR_SGNL_LED_TX,                         /** LED transmit*/
    MESA_10G_GPIO_INTR_SGNL_LED_RX,                         /** LED receive*/
    MESA_10G_GPIO_INTR_SGNL_RX_ALARM,                       /** RX Alarm*/
    MESA_10G_GPIO_INTR_SGNL_TX_ALARM,                       /** TX Alarm*/
    MESA_10G_GPIO_INTR_SGNL_HOST_LINK,                      /** Host Link status*/
    MESA_10G_GPIO_INTR_SGNL_LINE_LINK,                      /** Line Link status*/
    MESA_10G_GPIO_INTR_SGNL_LINE_KR_8b10b_2GPIO,            /** KR 8b10b */
    MESA_10G_GPIO_INTR_SGNL_LINE_KR_10b_2GPIO,              /** KR 10b*/
    MESA_10G_GPIO_INTR_SGNL_ROSI_PULSE,                     /** ROSI Pulse*/
    MESA_10G_GPIO_INTR_SGNL_ROSI_SDATA,                     /** ROSI sdata*/
    MESA_10G_GPIO_INTR_SGNL_ROSI_SCLK,                      /** ROSI sclock*/
    MESA_10G_GPIO_INTR_SGNL_TOSI_PULSE,                     /** TOSI Pulse*/
    MESA_10G_GPIO_INTR_SGNL_TOSI_SCLK,                      /** TOSI sclock*/
    MESA_10G_GPIO_INTR_SGNL_LINE_PCS1G_LINK,                /** Line PCS1G link status*/
    MESA_10G_GPIO_INTR_SGNL_LINE_PCS_RX_STAT,               /** Line PCS RX link status*/
    MESA_10G_GPIO_INTR_SGNL_CLIENT_PCS1G_LINK,              /** Client PCS1G link status*/
    MESA_10G_GPIO_INTR_SGNL_HOST_PCS_RX_STAT,               /** Host PCS RX status*/
    MESA_10G_GPIO_INTR_SGNL_HOST_SD10G_IB_SIG,              /** Host SERDES 10G 1B signal*/
    MESA_10G_GPIO_INTR_SGNL_LINE_SD10G_IB_SIG,              /** Line SERDES 10G 1B signal*/
    MESA_10G_GPIO_INTR_SGNL_HPCS_INTR,                      /** HPCS interrupt*/
    MESA_10G_GPIO_INTR_SGNL_LPCS_INTR,                      /** LPCS interrupt*/
    MESA_10G_GPIO_INTR_SGNL_CLIENT_PCS1G_INTR,              /** Client PCS1G interrupt*/
    MESA_10G_GPIO_INTR_SGNL_LINE_PCS1G_INTR,                /** Line PCS1G interrupt*/
    MESA_10G_GPIO_INTR_SGNL_WIS_INT0,                       /** WIS interrupt 0*/
    MESA_10G_GPIO_INTR_SGNL_HOST_PMA_INT,                   /** Host PMA interrupt*/
    MESA_10G_GPIO_INTR_SGNL_LINE_PMA_INT,                   /** Line PMA interrupt*/
    MESA_10G_GPIO_INTR_SGNL_DATA_ACT_TX,                    /** TX data activity*/
    MESA_10G_GPIO_INTR_SGNL_DATA_ACT_RX,                    /** RX data activity*/
    MESA_10G_GPIO_INTR_SGNL_HDATA_ACT_TX,                   /** Host TX data activity*/
    MESA_10G_GPIO_INTR_SGNL_HDATA_ACT_RX,                   /** Host RX data activity*/
    MESA_10G_GPIO_INTR_SGNL_XGMII_PAUS_EGR,                 /** XGMI pause egress*/
    MESA_10G_GPIO_INTR_SGNL_XGMII_PAUS_ING,                 /** XGMI pause ingress*/
    MESA_10G_GPIO_INTR_SGNL_RX_PCS_PAUS,                    /** PCS RX Pause*/
    MESA_10G_GPIO_INTR_SGNL_TX_PCS_PAUS,                    /** PCS TX Pause*/
    MESA_10G_GPIO_INTR_SGNL_RX_WIS_PAUS,                    /** WIS RX Pause*/
    MESA_10G_GPIO_INTR_SGNL_TX_WIS_PAUS,                    /** WIS TX Pause*/
    MESA_10G_GPIO_INTR_SGNL_ETH_CHAN_DIS,                   /** Ethernet channel disable*/
    MESA_10G_GPIO_INTR_SGNL_MACSEC_1588_SFD_LANE,           /** MACSEC,1588 SFD lane*/
    MESA_10G_GPIO_INTR_SGNL_LINE_S_TX_FAULT,                /** TX fault*/
    MESA_10G_GPIO_INTR_SGNL_LPCS1G_LATENCY0_OR_EWIS_BIT0,   /** LPCS1G latency 0 in case of 1G mode or EWIS BIT 0*/
    MESA_10G_GPIO_INTR_SGNL_LPCS1G_LATENCY1_OR_EWIS_BIT1,   /** LPCS1G latency 0 in case of 1G mode or EWIS BIT 1*/
    MESA_10G_GPIO_INTR_SGNL_LPCS1G_CHAR_POS0_OR_EWIS_BIT2,  /** LPCS1G Char pos 0 in case of 1G mode or EWIS BIT 2*/
    MESA_10G_GPIO_INTR_SGNL_LPCS1G_CHAR_POS1_OR_EWIS_WORD0, /** LPCS1G Char pos 1 in case of 1G mode or EWIS word 0*/
    MESA_10G_GPIO_INTR_SGNL_LPCS1G_CHAR_POS2_OR_EWIS_WORD1, /** LPCS1G Char pos 2 in case of 1G mode or EWIS word 1*/
    MESA_10G_GPIO_INTR_SGNL_LPCS1G_CHAR_POS3_OR_EWIS_WORD2, /** LPCS1G Char pos 3 in case of 1G mode or EWIS word 2*/
    MESA_10G_GPIO_INTR_SGNL_MACSEC_IGR_PRED_VAR0,           /** Macsec ingress predictor var 0*/
    MESA_10G_GPIO_INTR_SGNL_MACSEC_IGR_PRED_VAR1,           /** Macsec ingress predictor var 1*/
    MESA_10G_GPIO_INTR_SGNL_KR_ACTV_2GPIO,                  /** KR activity*/
    MESA_10G_GPIO_INTR_SGNL_DFT_TX_2GPIO,                   /** DFT transmit*/
    MESA_10G_GPIO_INTR_SGNL_RESERVED,                       /** Reserved for future use*/
    MESA_10G_GPIO_INTR_SGNL_EXE_LST_2GPIO_0,                /** EXE LST to GPIO 0 */
    MESA_10G_GPIO_INTR_SGNL_EXE_LST_2GPIO_1,                /** EXE LST to GPIO 1 */
    MESA_10G_GPIO_INTR_SGNL_EXE_LST_2GPIO_2,                /** EXE LST to GPIO 2 */
    MESA_10G_GPIO_INTR_SGNL_EXE_LST_2GPIO_3,                /** EXE LST to GPIO 3 */
    MESA_10G_GPIO_INTR_SGNL_EXE_LST_2GPIO_4,                /** EXE LST to GPIO 4 */
    MESA_10G_GPIO_INTR_SGNL_LINK_HCD_2GPIO_0,               /** Link HCD to GPIO 0*/
    MESA_10G_GPIO_INTR_SGNL_LINK_HCD_2GPIO_1,               /** Link HCD to GPIO 1*/
    MESA_10G_GPIO_INTR_SGNL_LINK_HCD_2GPIO_2,               /** Link HCD to GPIO 2*/
    MESA_10G_GPIO_INTR_SGNL_ETH_1G_ENA,                     /** Ethernet 1G enable*/
    MESA_10G_GPIO_INTR_SGNL_H_KR_8b10b_2GIPO,               /** KR 8b10b to GPIO*/
    MESA_10G_GPIO_INTR_SGNL_H_KR_10Gb_2GPIO,                /** KR10Gb to GPIO*/
    MESA_10G_GPIO_INTR_SGNL_H_KR_ACTV_2GPIO,                /** KR activity to GPIO*/
    MESA_10G_GPIO_INTR_SGNL_NONE,                           /** None of the internal signal is chosen */
} mesa_gpio_10g_gpio_intr_sgnl_t CAP(PHY_10G); /** Internal signals supported on Malibu*/

/**
 * \brief GPIO Channel level interrupts
 **/
typedef enum
{
    MESA_10G_GPIO_INTRPT_WIS0,      /** WIS interrupt 0 */
    MESA_10G_GPIO_INTRPT_WIS1,      /** WIS interrupt 1 */
    MESA_10G_GPIO_INTRPT_LPCS10G,   /** LPCS 10G interrupt */
    MESA_10G_GPIO_INTRPT_HPCS10G,   /** HPCS 10G interrupt */
    MESA_10G_GPIO_INTRPT_LPCS1G,    /** LPCS 1G interrupt */
    MESA_10G_GPIO_INTRPT_HPCS1G,    /** HPCS 1G interrupt */
    MESA_10G_GPIO_INTRPT_MSEC_EGR,  /** Macsec Egress interrupt*/
    MESA_10G_GPIO_INTRPT_MSEC_IGR,  /** Macsec Ingress interrupt*/
    MESA_10G_GPIO_INTRPT_LMAC,      /** Line MAC interrupt */
    MESA_10G_GPIO_INTRPT_HMAC,      /** Host MAC interrupt */
    MESA_10G_GPIO_INTRPT_FCBUF,     /** FC Buffer interrupt */
    MESA_10G_GPIO_INTRPT_LIGR_FIFO, /** Line ingress FIFO interrupt*/
    MESA_10G_GPIO_INTRPT_LEGR_FIFO, /** Line egress FIFO interrupt */
    MESA_10G_GPIO_INTRPT_HEGR_FIFO, /** Host egress FIFO interrupt */
    MESA_10G_GPIO_INTRPT_LPMA,      /** Line PMA interrupt */
    MESA_10G_GPIO_INTRPT_HPMA,      /** Host PMA interrupt */
} mesa_gpio_10g_chan_intrpt_t CAP(PHY_10G);      /** Channel Level Interrupts */

/**
 * \brief GPIO Channel level interrupts
 **/
typedef enum
{
    MESA_10G_GPIO_AGGR_INTRPT_CH0_INTR0_EN,      /** CH0_INTR0_EN */
    MESA_10G_GPIO_AGGR_INTRPT_CH0_INTR1_EN,      /** CH0_INTR1_EN */
    MESA_10G_GPIO_AGGR_INTRPT_CH1_INTR0_EN,      /** CH1_INTR0_EN */
    MESA_10G_GPIO_AGGR_INTRPT_CH1_INTR1_EN,      /** CH1_INTR1_EN */
    MESA_10G_GPIO_AGGR_INTRPT_CH2_INTR0_EN,      /** CH2_INTR0_EN */
    MESA_10G_GPIO_AGGR_INTRPT_CH2_INTR1_EN,      /** CH2_INTR1_EN */
    MESA_10G_GPIO_AGGR_INTRPT_CH3_INTR0_EN,      /** CH3_INTR0_EN */
    MESA_10G_GPIO_AGGR_INTRPT_CH3_INTR1_EN,      /** CH3_INTR1_EN */
    MESA_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR0_EN, /** IP1588_0_INTR0_EN */
    MESA_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR1_EN, /** IP1588_0_INTR1_EN */
    MESA_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR2_EN, /** IP1588_0_INTR2_EN */
    MESA_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR3_EN, /** IP1588_0_INTR3_EN */
    MESA_10G_GPIO_AGGR_INTRPT_IP1588_1_INTR0_EN, /** TS_FIFO empty channel 0 */
    MESA_10G_GPIO_AGGR_INTRPT_IP1588_1_INTR1_EN, /** TS_FIFO empty channel 1 */
    MESA_10G_GPIO_AGGR_INTRPT_IP1588_1_INTR2_EN, /** TS_FIFO empty channel 2 */
    MESA_10G_GPIO_AGGR_INTRPT_IP1588_1_INTR3_EN, /** TS_FIFO empty channel 3 */
    MESA_10G_GPIO_AGGR_INTRPT_LCPLL_0_INTR_EN,   /** LCPLL_0_INTR_EN */
    MESA_10G_GPIO_AGGR_INTRPT_LCPLL_1_INTR_EN,   /** LCPLL_1_INTR_EN */
    MESA_10G_GPIO_AGGR_INTRPT_EXP4_INTR_EN,      /** EXP4_INTR_EN */
    MESA_10G_GPIO_AGGR_INTRPT_CLK_MUX_INTR_EN,   /** CLK_MUX_INTR_EN */
    MESA_10G_GPIO_AGGR_INTRPT_GPIO_INTR_EN,      /** GPIO_INTR_EN */
} mesa_gpio_10g_aggr_intrpt_t CAP(PHY_10G);      /** Aggregated Interrupts */

/**
 * \brief GPIO Channel level interrupts
 **/
typedef enum
{
    MESA_10G_GPIO_INPUT_NONE,          /** Input that doesn't need any extra configuration */
    MESA_10G_GPIO_INPUT_LINE_LOPC,     /** LOPC from SFP on LINE */
    MESA_10G_GPIO_INPUT_HOST_LOPC,     /** LOPC from SFP on HOST */
    MESA_10G_GPIO_INPUT_SFP_MOD_DET,   /** SFP Module detect */
} mesa_gpio_10g_input_t CAP(PHY_10G);       /** GPIO input modes */

/**
 * \brief LED Modes
 **/
typedef enum
{
    MESA_10G_GPIO_LED_NONE = 0,                     /**< Disable LED configuration on given GPIO             */
    MESA_10G_GPIO_LED_TX_LINK_STATUS = 1,           /**< Display LINE Tx link status                         */
    MESA_10G_GPIO_LED_TX_LINK_TX_DATA = 3,          /**< Display LINE Tx link status and Tx data activity    */
    MESA_10G_GPIO_LED_TX_LINK_TX_RX_DATA = 4,       /**< Display LINE Tx link status and Tx,Rx data activity */
    MESA_10G_GPIO_LED_RX_LINK_STATUS = 5,           /**< Display LINE Rx link status                         */
    MESA_10G_GPIO_LED_RX_LINK_RX_DATA = 7,          /**< Display LINE Rx link status and Rx data activity    */
    MESA_10G_GPIO_LED_RX_LINK_TX_RX_DATA = 8,       /**< Display LINE Rx link status and Tx,Rx data activity */
} mesa_gpio_10g_led_mode_t;                         /**< GPIO LED modes */

/**
 * \brief LED Blink Interval
 **/
typedef enum
{
    MESA_10G_GPIO_LED_BLINK_50MS,          /**< Led Blink interval is 5o ms */
    MESA_10G_GPIO_LED_BLINK_100MS,         /**< Led Blink interval is 100ms */
    MESA_10G_GPIO_LED_BLINK_NONE,          /**< None */
} mesa_gpio_10g_led_blink_t;

/**
 * \brief LED Mode selection
 **/

typedef struct {
    mesa_gpio_10g_led_mode_t mode;         /**< Led mode selection */
    mesa_gpio_10g_led_blink_t blink;       /**< Led blink interval */
} mesa_gpio_10g_led_conf_t;

/**
 * \brief GPIO configured mode
 **/
typedef struct
{
    mesa_10g_phy_gpio_t            mode;          /**< Mode of this GPIO pin */
    mesa_port_no_t                 port;          /**< In case of MESA_PHY_10G_GPIO_WIS_INT mode, this is the interrupt port number that is related to this GPIO In case of MESA_PHY_10G_GPIO_PCS_RX_FAULT  mode, this is the PCS status port number that is related to this GPIO */
    mesa_gpio_10g_input_t          input;         /**< GPIO input modes */
    mesa_gpio_10g_gpio_intr_sgnl_t in_sig;        /**< Internal signal that to be routed through GPIO */
    mesa_gpio_10g_no_t             p_gpio;        /**< Per channel GPIO number*/
    mesa_gpio_10g_chan_intrpt_t    c_intrpt;      /**< Per Channel interrupt, */
    uint16_t                       source;        /**< source of GPIO,approriate value from GPIO_OUT_CFG_X register field GPIO_X_SEL */
    uint32_t                       aggr_intrpt;   /**< Bitmask corresponds to aggregated interrupt*/
    mesa_bool_t                    use_as_intrpt; /**< Change in GPIO generates GPIO interrupt ,supported on MALIBU */
    mesa_bool_t                    p_gpio_intrpt; /**< Port GPIO Change interrupt*/
    mesa_gpio_10g_led_conf_t       led_conf;      /**< Led mode configuration */
} mesa_gpio_10g_gpio_mode_t CAP(PHY_10G);


#define MESA_PHY_10G_GPIO_MAX   12  /**< Max value of gpio_no parameter */

#define MESA_PHY_10G_GPIO_MAL_MAX   40  /**< Max value of gpio_no parameter,Malibu */

/**
 * \brief Set GPIO mode. There is only one set og GPIO per PHY chip - not per port.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number that identify the PHY chip.
 * \param gpio_no [IN]  GPIO pin number < MESA_PHY_10G_GPIO_MAX.
 * \param mode [IN]     GPIO mode.
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_10g_gpio_mode_set(const mesa_inst_t               inst,
                                   const mesa_port_no_t            port_no,
                                   const mesa_gpio_10g_no_t        gpio_no,
                                   const mesa_gpio_10g_gpio_mode_t *const mode)
    CAP(PHY_10G);

/**
 * \brief Get GPIO mode.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number that identify the PHY chip.
 * \param gpio_no [IN]  GPIO pin number.
 * \param mode [OUT]    GPIO mode.
 *
 * \return Return code.
 **/

mesa_rc mesa_phy_10g_gpio_mode_get(const mesa_inst_t         inst,
                                   const mesa_port_no_t      port_no,
                                   const mesa_gpio_10g_no_t  gpio_no,
                                   mesa_gpio_10g_gpio_mode_t *const mode)
    CAP(PHY_10G);

/**
 * \brief Read from GPIO input pin.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param gpio_no [IN]  GPIO pin number.
 * \param value [OUT]   TRUE if pin is high, FALSE if it is low.
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_10g_gpio_read(const mesa_inst_t        inst,
                               const mesa_port_no_t     port_no,
                               const mesa_gpio_10g_no_t gpio_no,
                               mesa_bool_t              *const value)
    CAP(PHY_10G);

/**
 * \brief Write to GPIO output pin.
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number.
 * \param gpio_no [IN]  GPIO pin number.
 * \param value [IN]    TRUE to set pin high, FALSE to set pin low.
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_10g_gpio_write(const mesa_inst_t        inst,
                                const mesa_port_no_t     port_no,
                                const mesa_gpio_10g_no_t gpio_no,
                                const mesa_bool_t        value)
    CAP(PHY_10G);

/* - Events ------------------------------------------------------- */

/** \brief Event source identification mask values */
#define    MESA_PHY_10G_LINK_LOS_EV            0x00000001 /**< PHY Link Los interrupt - only on 8486 */
#define    MESA_PHY_10G_RX_LOL_EV              0x00000002 /**< PHY RXLOL interrupt - only on 8488 */
#define    MESA_PHY_10G_TX_LOL_EV              0x00000004 /**< PHY TXLOL interrupt - only on 8488 */
#define    MESA_PHY_10G_LOPC_EV                0x00000008 /**< PHY LOPC interrupt - only on 8488 */
#define    MESA_PHY_10G_HIGH_BER_EV            0x00000010 /**< PHY HIGH_BER interrupt - only on 8488 */
#define    MESA_PHY_10G_MODULE_STAT_EV         0x00000020 /**< PHY MODULE_STAT interrupt - only on 8488 */
#define    MESA_PHY_10G_PCS_RECEIVE_FAULT_EV   0x00000040 /**< PHY PCS_RECEIVE_FAULT interrupt - only on 8488 */
#define    MESA_PHY_EWIS_SEF_EV                0x00000080 /**< SEF has changed state - only for 8488 */
#define    MESA_PHY_EWIS_FPLM_EV               0x00000100 /**< far-end (PLM-P) / (LCDP) - only for 8488 */
#define    MESA_PHY_EWIS_FAIS_EV               0x00000200 /**< far-end (AIS-P) / (LOP) - only for 8488 */
#define    MESA_PHY_EWIS_LOF_EV                0x00000400 /**< Loss of Frame (LOF) - only for 8488 */
#define    MESA_PHY_EWIS_RDIL_EV               0x00000800 /**< Line Remote Defect Indication (RDI-L) - only for 8488 */
#define    MESA_PHY_EWIS_AISL_EV               0x00001000 /**< Line Alarm Indication Signal (AIS-L) - only for 8488 */
#define    MESA_PHY_EWIS_LCDP_EV               0x00002000 /**< Loss of Code-group Delineation (LCD-P) - only for 8488 */
#define    MESA_PHY_EWIS_PLMP_EV               0x00004000 /**< Path Label Mismatch (PLMP) - only for 8488 */
#define    MESA_PHY_EWIS_AISP_EV               0x00008000 /**< Path Alarm Indication Signal (AIS-P) - only for 8488 */
#define    MESA_PHY_EWIS_LOPP_EV               0x00010000 /**< Path Loss of Pointer (LOP-P) - only for 8488 */
#define    MESA_PHY_EWIS_UNEQP_EV              0x00020000 /**< Unequiped Path (UNEQ-P) - only for 8488 */
#define    MESA_PHY_EWIS_FEUNEQP_EV            0x00040000 /**< Far-end Unequiped Path (UNEQ-P) - only for 8488 */
#define    MESA_PHY_EWIS_FERDIP_EV             0x00080000 /**< Far-end Path Remote Defect Identifier (RDI-P) - only for 8488 */
#define    MESA_PHY_EWIS_REIL_EV               0x00100000 /**< Line Remote Error Indication (REI-L) - only for 8488 */
#define    MESA_PHY_EWIS_REIP_EV               0x00200000 /**< Path Remote Error Indication (REI-P) - only for 8488 */
#define    MESA_PHY_EWIS_B1_NZ_EV              0x00400000 /**< PMTICK B1 BIP (B1_ERR_CNT) not zero - only for 8488 */
#define    MESA_PHY_EWIS_B2_NZ_EV              0x00800000 /**< PMTICK B2 BIP (B1_ERR_CNT) not zero - only for 8488 */
#define    MESA_PHY_EWIS_B3_NZ_EV              0x01000000 /**< PMTICK B3 BIP (B1_ERR_CNT) not zero - only for 8488 */
#define    MESA_PHY_EWIS_REIL_NZ_EV            0x02000000 /**< PMTICK REI-L (REIL_ERR_CNT) not zero - only for 8488 */
#define    MESA_PHY_EWIS_REIP_NZ_EV            0x04000000 /**< PMTICK REI-P (REIP_ERR_CNT) not zero - only for 8488 */
#define    MESA_PHY_EWIS_B1_THRESH_EV          0x08000000 /**< B1_THRESH_ERR - only for 8488 */
#define    MESA_PHY_EWIS_B2_THRESH_EV          0x10000000 /**< B2_THRESH_ERR - only for 8488 */
#define    MESA_PHY_EWIS_B3_THRESH_EV          0x20000000 /**< B3_THRESH_ERR - only for 8488 */
#define    MESA_PHY_EWIS_REIL_THRESH_EV        0x40000000 /**< REIL_THRESH_ERR - only for 8488 */
#define    MESA_PHY_EWIS_REIP_THRESH_EV        0x80000000 /**< REIp_THRESH_ERR - only for 8488 */

typedef uint32_t mesa_phy_10g_event_t CAP(PHY_10G);   /**< The type definition to contain the above defined evant mask */


/*--Events changed in Malibu */
/* PMA block interupts */
#define    MESA_PHY_10G_RX_LOS_EV                  0x00000001 /**< PHY RX LOS interrupt - 8256 specific */
#define    MESA_PHY_10G_RX_LOL_EV                  0x00000002 /**< PHY RX LOL interrupt - 8256 specific*/
#define    MESA_PHY_10G_TX_LOL_EV                  0x00000004 /**< PHY TX LOL interrupt - 8256 specific */
/* PCS block interrupts */
#define MESA_PHY_10G_RX_CHAR_DEC_CNT_THRESH_EV     0x00000010 /**< PHY RX character decode error - 8256 specific */
#define MESA_PHY_10G_TX_CHAR_ENC_CNT_THRESH_EV     0x00000020 /**< PHY TX character encode error count  - 8256 specific */
#define MESA_PHY_10G_RX_BLK_DEC_CNT_THRESH_EV      0x00000040 /**< PHY RX block decode error count  - 8256 specific */
#define MESA_PHY_10G_TX_BLK_ENC_CNT_THRESH_EV      0x00000080 /**< PHY TX block encode error count- 8256 specific */
#define MESA_PHY_10G_RX_SEQ_CNT_THRESH_EV          0x00000100 /**< PHY RX sequencing error count - 8256 specific */
#define MESA_PHY_10G_TX_SEQ_CNT_THRESH_EV          0x00000200 /**< PHY TX sequencing error count - 8256 specific */
#define MESA_PHY_10G_FEC_UNFIXED_CNT_THRESH_EV     0x00000400 /**< PHY KR-FEC uncorrectable block count interrupt - 8256 specific */
#define MESA_PHY_10G_FEC_FIXED_CNT_THRESH_EV       0x00000800 /**< PHY KR-FEC corrected threshold - 8256 specific */
#define MESA_PHY_10G_HIGHBER_EV                    0x00001000 /**< PHY high bit Error - 8256 specific */
#define MESA_PHY_10G_RX_LINK_STAT_EV               0x00002000 /**< PHY Link status up/down interrupt - 8256 specific */
#define MESA_PHY_10G_RX_LINK_STAT_EV               0x00002000 /**< PHY Link status up/down interrupt - 8256 specific */
#define  MESA_PHY_10G_GPIO_INT_AGG0_EV             0x00004000 /**< PHY GPIO interrupt on Aggregator0  - 8256 specific */
#define  MESA_PHY_10G_GPIO_INT_AGG1_EV             0x00008000 /**< PHY GPIO interrupt on Aggregator1  - 8256 specific */
#define  MESA_PHY_10G_GPIO_INT_AGG2_EV             0x00010000 /**< PHY GPIO interrupt on Aggregator2  - 8256 specific */
#define  MESA_PHY_10G_GPIO_INT_AGG3_EV             0x00020000 /**< PHY GPIO interrupt on Aggregator3  - 8256 specific */
#define  MESA_PHY_1G_LINE_AUTONEG_RESTART_EV       0x00040000 /**< PHY 1G Line side Autoneg restart event */
#define  MESA_PHY_1G_HOST_AUTONEG_RESTART_EV       0x00080000 /**< PHY 1G Host side Autoneg restart event  - 8256 specific */

/* more  to come */
typedef uint32_t mesa_phy_10g_extnd_event_t CAP(PHY_10G);   /**< The type definition to contain the above defined extended event mask */

/**
 * \brief Enabling / Disabling of events
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number
 * \param ev_mask [IN]  Mask containing events that are enabled/disabled
 * \param enable [IN]   Enable/disable of event
 *
 * \return Return code.
 **/

mesa_rc mesa_phy_10g_event_enable_set(const mesa_inst_t          inst,
                                      const mesa_port_no_t       port_no,
                                      const mesa_phy_10g_event_t ev_mask,
                                      const mesa_bool_t          enable)
    CAP(PHY_10G);

/**
 * \brief Get Enabling of events
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number
 * \param ev_mask [OUT]  Mask containing events that are enabled
 *
 * \return Return code.
 **/

mesa_rc mesa_phy_10g_event_enable_get(const mesa_inst_t    inst,
                                      const mesa_port_no_t port_no,
                                      mesa_phy_10g_event_t *const ev_mask)
    CAP(PHY_10G);

/**
 * \brief Get Enabling of events
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number
 * \param ex_ev_mask [OUT]  Mask containing extended events that are enabled
 *
 * \return Return code.
 **/

mesa_rc mesa_phy_10g_extended_event_enable_get(const mesa_inst_t          inst,
                                               const mesa_port_no_t       port_no,
                                               mesa_phy_10g_extnd_event_t *const ex_ev_mask)
    CAP(PHY_10G);

/**
 * \brief Polling for active events
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number
 * \param ev_mask [OUT] Mask containing events that are active
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_10g_event_poll(const mesa_inst_t    inst,
                                const mesa_port_no_t port_no,
                                mesa_phy_10g_event_t *const ev_mask)
    CAP(PHY_10G);

/**
 * \brief poll and clear PCS STICKY Register
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number
 * \param ex_events [OUT] Event mask containing events that are active
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_10g_pcs_status_get(const mesa_inst_t          inst,
                                    const mesa_port_no_t       port_no,
                                    mesa_phy_10g_extnd_event_t *const ex_events)
    CAP(PHY_10G);

/**
 * \brief Polling for active events
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number
 * \param ex_events [OUT] Event mask containing events that are active
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_10g_extended_event_poll(const mesa_inst_t          inst,
                                         const mesa_port_no_t       port_no,
                                         mesa_phy_10g_extnd_event_t *const ex_events)
    CAP(PHY_10G);

/**
 * \brief Enabling / Disabling of events
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number
 * \param ex_ev_mask [IN]  Mask containing exetnded events that are enabled/disabled
 * \param extnd_enable [IN]   Enable/disable of event
 *
 * \return Return code.
 **/

mesa_rc mesa_phy_10g_extended_event_enable_set(const mesa_inst_t                inst,
                                               const mesa_port_no_t             port_no,
                                               const mesa_phy_10g_extnd_event_t ex_ev_mask,
                                               const mesa_bool_t                extnd_enable)
    CAP(PHY_10G);

/**
 * \brief Function is called once a second
 *
 * \param inst [IN]     Target instance reference.
 * \return Return code.
 **/
mesa_rc mesa_phy_10g_poll_1sec(const mesa_inst_t inst)
    CAP(PHY_10G);

/** \brief Firmware status */
typedef struct {
    uint16_t             edc_fw_rev;      /**< FW revision */
    mesa_bool_t          edc_fw_chksum;   /**< FW chksum.    Fail=0, Pass=1*/
    mesa_bool_t          icpu_activity;   /**< iCPU activity.  Not Running=0, Running=1   */
    mesa_bool_t          edc_fw_api_load; /**< EDC FW is loaded through API No=0, Yes=1  */
} mesa_phy_10g_fw_status_t CAP(PHY_10G);

/**
 * \brief Internal microprocessor status
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Port number
 * \param status [OUT]  Status of the EDC FW running on the internal CPU
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_10g_edc_fw_status_get(const mesa_inst_t        inst,
                                       const mesa_port_no_t     port_no,
                                       mesa_phy_10g_fw_status_t *const status)
    CAP(PHY_10G);

/**
 * \brief CSR register read
 *
 * \param inst    [IN]   Target instance reference.
 * \param port_no [IN]   Port number
 * \param dev     [IN]   Device id (or MMD)
 * \param addr    [IN]   Addr of the register, 16 or 32 bit
 * \param value   [OUT]  Return value of the register
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_10g_csr_read(const mesa_inst_t    inst,
                              const mesa_port_no_t port_no,
                              const uint32_t       dev,
                              const uint32_t       addr,
                              uint32_t             *const value)
    CAP(PHY_10G);

/**
 * \brief CSR register write
 *
 * \param inst    [IN]   Target instance reference.
 * \param port_no [IN]   Port number
 * \param dev     [IN]   Device id (or MMD)
 * \param addr    [IN]   Addr of the register, 16 or 32 bit
 * \param value   [IN]   Value to be written
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_10g_csr_write(const mesa_inst_t    inst,
                               const mesa_port_no_t port_no,
                               const uint32_t       dev,
                               const uint32_t       addr,
                               const uint32_t       value)
    CAP(PHY_10G);

/**
 * \brief Function for checking if any issue were seen during warm-start
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  The port in question.
 * \return Return code. MESA_RC_OK if not errors ware seen during warm-start else MESA_RC_ERROR.*/
mesa_rc mesa_phy_warm_start_10g_failed_get(const mesa_inst_t    inst,
                                           const mesa_port_no_t port_no)
    CAP(PHY_10G);

/**
 * \brief Enables Pass through mode in 10G PHY.
 *
 * \param inst    [IN]  Target instance reference.
 * \param port_no [IN]  Port number.
 * \param enable  [IN]  Enables SGMII mode.
 *
 * \return
 *   MESA_RC_OK on success.\n
 *   MESA_RC_ERROR on error.
 **/
mesa_rc mesa_phy_10g_sgmii_mode_set(const mesa_inst_t    inst,
                                    const mesa_port_no_t port_no,
                                    mesa_bool_t          enable)
    CAP(PHY_10G);

/**
 * \brief  read from i2c device
 *
 * \param inst    [IN]   Target instance reference.
 * \param port_no [IN]   Port number
 * \param addr    [IN]   Addr of the SFP ROM register
 * \param value   [OUT]  Return Value of the register
 *
 * \return Return code.
 **/

mesa_rc mesa_phy_10g_i2c_read(const mesa_inst_t    inst,
                              const mesa_port_no_t port_no,
                              const uint16_t       addr,
                              uint16_t             *value)
    CAP(PHY_10G);

/**
 * \brief  Write to i2c device
 *
 * \param inst    [IN]   Target instance reference.
 * \param port_no [IN]   Port number
 * \param addr    [IN]   Addr of the SFP ROM register
 * \param value   [IN]   value to be writter to register
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_10g_i2c_write(const mesa_inst_t    inst,
                               const mesa_port_no_t port_no,
                               const uint16_t       addr,
                               const uint16_t       *value)
    CAP(PHY_10G);

/** \brief 10G Phy I2C server Interface for SFP Module Configuration */
typedef struct {
    uint8_t  slave_id; /**< I2C client ID */
    uint16_t prescale; /**< SCL frequency = 156.25 MHZ/5*(Prescale + 1), 0 to 0x4C are invalid settings. */
} mesa_phy_10g_i2c_slave_conf_t;

/**
 * \brief Sets the configuration for the I2C client
 *
 * \param inst       [IN]  Target instance reference
 * \param port_no    [IN]  Port number
 * \param i2c_conf   [IN]  Sets configuration for client
 *
 * \return Return code.
 **/

mesa_rc mesa_phy_10g_i2c_slave_conf_set(const mesa_inst_t                          inst,
                                        const mesa_port_no_t                       port_no,
                                        mesa_phy_10g_i2c_slave_conf_t *const       i2c_conf)
    CAP(PHY_10G);

/**
 * \brief  Gets the I2C configuration parameters
 *
 * \param inst         [IN]    Target instance reference.
 * \param port_no      [IN]    Port number
 * \param i2c_conf     [OUT]   Gets configuration for client
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_10g_i2c_slave_conf_get(const mesa_inst_t                          inst,
                                        const mesa_port_no_t                       port_no,
                                        mesa_phy_10g_i2c_slave_conf_t              *i2c_conf)
    CAP(PHY_10G);

/**
 * \brief  Gets generic pointer in mesa_state structure
 *
 * \param inst        [IN]   Target instance reference.
 * \param port_no     [IN]   Port number
 * \param user_data   [OUT]   Gets value in generic pointer
 *
 * \return Return code.
 **/
mesa_rc mesa_phy_10g_get_user_data(const mesa_inst_t    inst,
                                   const mesa_port_no_t port_no,
                                   void                 **user_data)
    CAP(PHY_10G);

#include <microchip/ethernet/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_SWITCH_API_PHY_10G_
