// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_SWITCH_API_WIS_
#define _MICROCHIP_ETHERNET_SWITCH_API_WIS_

#include <microchip/ethernet/phy/api/types.h>
#include <microchip/ethernet/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

/* ================================================================= *
 *  Data structures / types
 * ================================================================= */

/** \brief Trail Trace Identifier mode types */
typedef enum {
    MESA_EWIS_TTI_MODE_1,     /**< one byte trace identifier */
    MESA_EWIS_TTI_MODE_16,    /**< 16 bytes trace identifier */
    MESA_EWIS_TTI_MODE_64,    /**< 64 bytes trace identifier */
    MESA_WEIS_TTI_MODE_MAX
} mesa_ewis_tti_mode_t CAP(PHY_10G);

/** \brief Trail Trace Identifier type */
typedef struct mesa_ewis_tti_s {
    mesa_ewis_tti_mode_t mode;    /**< trace identifier mode (1,16,64 bytes) */
    uint8_t              tti[64]; /**< trace identifier value */
    mesa_bool_t          valid;   /**< Identifies the Accepted valid TTI */
} mesa_ewis_tti_t CAP(PHY_10G);

/** \brief eWIS fault mask configuration, i.e set up which defects trigger the Fault condition */
typedef struct mesa_ewis_fault_cons_act_s {
    mesa_bool_t fault_on_feplmp;   /**< TRUE = enable fault condition on far-end PLM-P */
    mesa_bool_t fault_on_feaisp;   /**< TRUE = enable fault condition on far-end AIS-P */
    mesa_bool_t fault_on_rdil;     /**< TRUE = enable fault condition on RDI-L */
    mesa_bool_t fault_on_sef;      /**< TRUE = enable fault condition on SEF */
    mesa_bool_t fault_on_lof;      /**< TRUE = enable fault condition on LOF */
    mesa_bool_t fault_on_los;      /**< TRUE = enable fault condition on LOS */
    mesa_bool_t fault_on_aisl;     /**< TRUE = enable fault condition on AIS-L*/
    mesa_bool_t fault_on_lcdp;     /**< TRUE = enable fault condition on LCD-P*/
    mesa_bool_t fault_on_plmp;     /**< TRUE = enable fault condition on PLM-P*/
    mesa_bool_t fault_on_aisp;     /**< TRUE = enable fault condition on AIS-P*/
    mesa_bool_t fault_on_lopp;     /**< TRUE = enable fault condition on LOP-P*/
} mesa_ewis_fault_cons_act_t CAP(PHY_10G);

/** \brief eWIS AIS-L consequent actions */
typedef struct mesa_ewis_aisl_cons_act_s {
    mesa_bool_t ais_on_los;    /**< TRUE = enable for AIS-L insertion on LOS */
    mesa_bool_t ais_on_lof;    /**< TRUE = enable for AIS-L insertion on LOF */
} mesa_ewis_aisl_cons_act_t CAP(PHY_10G);

/** \brief eWIS RDI-L consequent actions */
typedef struct mesa_ewis_rdil_cons_act_s {
    mesa_bool_t rdil_on_los;   /**< TRUE = enable for RDI-L backreporting on LOS */
    mesa_bool_t rdil_on_lof;   /**< TRUE = enable for RDI-L backreporting on LOF */
    mesa_bool_t rdil_on_lopc;  /**< TRUE = enable for RDI-L backreporting on LOPC */
    mesa_bool_t rdil_on_ais_l; /**< TRUE = enable for RDI-L backreporting on AIS_L */
} mesa_ewis_rdil_cons_act_t CAP(PHY_10G);

/** \brief eWIS consequent actions */
typedef struct mesa_ewis_cons_act_s {
    mesa_ewis_aisl_cons_act_t aisl;    /**< AIS-L consequent action configuration */
    mesa_ewis_rdil_cons_act_t rdil;    /**< RDI-L consequent action configuration */
    mesa_ewis_fault_cons_act_t fault;  /**< FAULT condition consequent action configuration */
} mesa_ewis_cons_act_t CAP(PHY_10G);

/** \brief eWIS line force mode */
typedef struct mesa_ewis_line_force_mode_s {
    mesa_bool_t force_ais;    /**<  Force AIS-L configuration */
    mesa_bool_t force_rdi;    /**<  Force RDI-L configuration */
} mesa_ewis_line_force_mode_t CAP(PHY_10G);

/** \brief eWIS line TX force mode */
typedef struct mesa_ewis_line_tx_force_mode_s {
    mesa_bool_t force_ais;    /**<  Force transmission of AIS-L in the K2 byte */
    mesa_bool_t force_rdi;    /**<  Force transmission of RDI-L in the K2 byte */
} mesa_ewis_line_tx_force_mode_t CAP(PHY_10G);

/** \brief eWIS path force modes */
typedef struct mesa_ewis_path_force_mode_s {
    mesa_bool_t force_uneq;  /**< Force UNEQ-P configuration */
    mesa_bool_t force_rdi;   /**< Force RDI-P configuration */
} mesa_ewis_path_force_mode_t CAP(PHY_10G);

/** \brief eWIS force modes */
typedef struct mesa_ewis_force_mode_s {
    mesa_ewis_line_force_mode_t line_rx_force;       /**< Line force configuration rx direction */
    mesa_ewis_line_tx_force_mode_t line_tx_force;    /**< Line force configuration tx direction */
    mesa_ewis_path_force_mode_t path_force;          /**< Path force configuration */
} mesa_ewis_force_mode_t CAP(PHY_10G);

/** \brief eWIS Mode(Bit/Block) for the Performence Monitoring Counters */
typedef enum {
   MESA_EWIS_PERF_MODE_BIT,   /**< Bit mode of the perf monitor counter*/
   MESA_EWIS_PERF_MODE_BLOCK, /**< Block mode of the perf monitor counter*/
} mesa_ewis_perf_cntr_mode_t CAP(PHY_10G);

/** \brief eWIS Mode(Bit/Block) for the Performence Monitoring Counters */
typedef struct mesa_ewis_perf_mode_s {
    mesa_ewis_perf_cntr_mode_t pn_ebc_mode_s;       /**< Section BIP error count (B1))*/
    mesa_ewis_perf_cntr_mode_t pn_ebc_mode_l;       /**< Near end line block (BIP) error count (B2)*/
    mesa_ewis_perf_cntr_mode_t pf_ebc_mode_l;       /**< Far end line block (BIP) error count (REI-L) */
    mesa_ewis_perf_cntr_mode_t pn_ebc_mode_p;       /**< Path block error count (B3) */
    mesa_ewis_perf_cntr_mode_t pf_ebc_mode_p;       /**< Far end path block error count (REI-P)*/
} mesa_ewis_perf_mode_t CAP(PHY_10G);

/** \brief eWIS operational mode types */
typedef enum {
    MESA_WIS_OPERMODE_DISABLE,  /** WIS mode disabled */
    MESA_WIS_OPERMODE_WIS_MODE, /** WIS mode enabled */
    MESA_WIS_OPERMODE_STS192,   /** WIS mode SONET - STS192 */
    MESA_WIS_OPERMODE_STM64,    /** WIS mode SDH - STM64 */
    MESA_WIS_OPERMODE_MAX       /** WIS mode Invalid */
} mesa_ewis_mode_t CAP(PHY_10G);

/** \brief eWIS status */
typedef struct mesa_ewis_status_s {
    mesa_bool_t fault;         /**< Fault condition (Latch on high) i.e. = true if any fault has occurred since previous read */
    mesa_bool_t link_stat;     /**< Link status condition (Latch on low) i.e. = false if any link error has occurred since previous read */
} mesa_ewis_status_t CAP(PHY_10G);

/** \brief eWIS defects */
typedef struct mesa_ewis_defects_s {
    mesa_bool_t dlos_s;        /**< Loss of signal */
    mesa_bool_t doof_s;        /**< Out of frame */
    mesa_bool_t dlof_s;        /**< Loss of frame */
    mesa_bool_t dais_l;        /**< Line alarm indication signal */
    mesa_bool_t drdi_l;        /**< Line remote defect indication */
    mesa_bool_t dais_p;        /**< Path alarm indication signal */
    mesa_bool_t dlop_p;        /**< Loss of pointer */
    mesa_bool_t duneq_p;       /**< Path Unequipped, not supported in 8487/8488 */
    mesa_bool_t drdi_p;        /**< Path Remote Defect Indication, not supported in 8487/8488 */
    mesa_bool_t dlcd_p;        /**< Path loss of code-group delineation */
    mesa_bool_t dplm_p;        /**< Path loss of code-group delineation */
    /* far end path defects */
    mesa_bool_t dfais_p;       /**< far-end AIS-P/LOP-P */
    mesa_bool_t dfplm_p;       /**< far-end PLM-P/LCD-P defect */
    mesa_bool_t dfuneq_p;      /**< Far End Path Unequipped */
} mesa_ewis_defects_t CAP(PHY_10G);


/** \brief eWIS performance primitives.
 *  These data are assumed to be read once every sec. The counters holds increments compared to previous read.
 *  The namings and definitions are taken from ITU-T rec G.783.
 */
typedef struct mesa_ewis_perf_s {
    uint32_t pn_ebc_s;       /**< Section BIP error count */
    uint32_t pn_ebc_l;       /**< Near end line block (BIP) error count */
    uint32_t pf_ebc_l;       /**< Far end line block (BIP) error count */
    uint32_t pn_ebc_p;       /**< Path block error count */
    uint32_t pf_ebc_p;       /**< Far end path block error count */
} mesa_ewis_perf_t CAP(PHY_10G);

/** \brief eWIS performance counters.
*  These counters are free running counters that wraps to zero.
*/
typedef struct mesa_ewis_counter_s {
    uint16_t pn_ebc_p;       /**< Path block error count */
    uint16_t pf_ebc_p;       /**< Far end path block error count */
    uint32_t pn_ebc_l;       /**< Near end line block (BIP) error count */
    uint32_t pf_ebc_l;       /**< Far end line block (BIP) error count */
    uint16_t pn_ebc_s;       /**< Section BIP error count */
} mesa_ewis_counter_t CAP(PHY_10G);

/** \brief eWIS test pattern mode types.
 */
typedef enum mesa_ewis_test_pattern_s {
    MESA_WIS_TEST_MODE_DISABLE,         /**< Disable test */
    MESA_WIS_TEST_MODE_SQUARE_WAVE,     /**< Enable squarevave generator, Only valid for test generator */
    MESA_WIS_TEST_MODE_PRBS31,          /**< Enable prbs31 generator/analyzer */
    MESA_WIS_TEST_MODE_MIXED_FREQUENCY, /**< Enable mixed frequency generator / analyzer */
    MESA_WIS_TEST_MODE_MAX              /**< Test mode Invalid */
} mesa_ewis_test_pattern_t CAP(PHY_10G);

/** \brief eWIS test configuration */
typedef struct mesa_ewis_test_conf_s {
    mesa_bool_t              loopback;           /**< loop output from Tx to Rx              */
    mesa_ewis_test_pattern_t test_pattern_gen;   /**< test pattern generation configuration  */
    mesa_ewis_test_pattern_t test_pattern_ana;   /**< test pattern analyzer configuration    */
} mesa_ewis_test_conf_t CAP(PHY_10G);

/** \brief eWIS test status */
typedef struct mesa_ewis_test_status_s {
    uint16_t    tstpat_cnt; /**< PRBS31 test pattern error counter. */
    mesa_bool_t ana_sync;   /**< PRBS31 pattern checker is synchronized to the data. */
} mesa_ewis_test_status_t CAP(PHY_10G);

/** \brief WIS transmitted overhead data.
 *         only a few oh bytes can be set dynamically. These OH bytes are not configurable from the API:
 *         H4 : multiframe indicator
 *         M0/M1: STS-1 Line Remote Error Indication (REI)
 *         G1: Path status
 */
typedef struct mesa_ewis_tx_oh_s {
    /**< Section Overhead: */
    uint8_t         tx_dcc_s [3];    /**< Section Data Communications Channel(DCC) D1-D3*/
    uint8_t         tx_e1;           /**< Orderwire */
    uint8_t         tx_f1;           /**< Section User Channel */
    uint8_t         tx_z0;           /**< Reserved for Section growth */
    /**< line overhead: */
    uint8_t         tx_dcc_l [9];    /**< Line Data Communications Channel (DCC) D4-D12 */
    uint8_t         tx_e2;           /**< Orderwire */
    uint16_t        tx_k1_k2;        /**< Automatic protection switch (APS) channel and Line Remote Defect Identifier (RDI-L) */
    uint8_t         tx_s1;           /**< Synchronization messaging */
    uint16_t        tx_z1_z2;        /**< Reserved for Line growth  */
    /**< path overhead: */
    uint8_t         tx_c2;           /**< Transmitted C2 path label */
    uint8_t         tx_f2;           /**< Path User Channel  */
    uint8_t         tx_n1;           /**< Tandem connection maintenance/Path data channel */
    uint16_t        tx_z3_z4;        /**< Reserved for Path growth  */
} mesa_ewis_tx_oh_t CAP(PHY_10G);

/** \brief eWIS overhead passthru configuration.
  */
typedef struct mesa_ewis_tx_passthru_s {
    /**< Section Overhead: */
    mesa_bool_t       tx_j0;           /**< j0 Section TTI  passthrough */
    mesa_bool_t       tx_z0;           /**< z0 Section growth passthrough */
    mesa_bool_t       tx_b1;           /**< b1 BIP passthrough */
    mesa_bool_t       tx_e1;           /**< e1 order wire passthrough */
    mesa_bool_t       tx_f1;           /**< f1 Section user channel */
    mesa_bool_t       tx_dcc_s;        /**< Section Data communication channel passthrough D1-D3 */
    mesa_bool_t       tx_soh;          /**< Section Reserved National and unused bytes passthrough */

    /**< line overhead: */
    mesa_bool_t       tx_b2;           /**< b2 BIP passthrough */
    mesa_bool_t       tx_k1;           /**< k1 passthrough */
    mesa_bool_t       tx_k2;           /**< k2 passthrough */
    mesa_bool_t       tx_reil;         /**< reil passthrough */
    mesa_bool_t       tx_dcc_l;        /**< Section Data communication channel passthrough D4-D12*/
    mesa_bool_t       tx_s1;           /**< Synchronization messaging passthrough */
    mesa_bool_t       tx_e2;           /**< order wire passthrough */
    mesa_bool_t       tx_z1_z2;        /**< Reserved for path growth passthrough */
    mesa_bool_t       tx_loh;          /**< Line Reserved National and unused bytes passthrough */
} mesa_ewis_tx_oh_passthru_t CAP(PHY_10G);

/** \brief eWIS performance counter thresholds.
*/
typedef struct mesa_ewis_counter_threshold_s {
    uint32_t n_ebc_thr_s;       /**< Section error count (B1) threshold */
    uint32_t n_ebc_thr_l;       /**< Near end line error count (B2) threshold */
    uint32_t f_ebc_thr_l;       /**< Far end line error count threshold */
    uint32_t n_ebc_thr_p;       /**< Path block error count (B3) threshold */
    uint32_t f_ebc_thr_p;       /**< Far end path error count threshold */
} mesa_ewis_counter_threshold_t CAP(PHY_10G);

/** \brief test error injection types */
typedef enum {
    MESA_EWIS_PRBS31_SINGLE_ERR, /**< Inject a single bit error (=> error counter incrementing by 3 */
    MESA_EWIS_PRBS31_SAT_ERR,    /**< Force the PRBS31 pattern error counter to a value of 65528 (close to saturation) */
    MESA_EWIS_PRBS31_MODE_MAX
} mesa_ewis_prbs31_err_inj_t CAP(PHY_10G);

/** \brief eWIS static configuration data, 
 *  \note This is specific to 8487/8488-15.
 */
typedef struct mesa_ewis_static_conf_s {
    uint16_t        ewis_txctrl1;           /**< WIS Vendor Specific Tx Control 1 */
    uint16_t        ewis_txctrl2;           /**< WIS Vendor Specific Tx Control 2 */
    uint16_t        ewis_rx_ctrl1;          /**< E-WIS Rx Control 1 */
    uint16_t        ewis_mode_ctrl;         /**< E-WIS Mode Control (incl expected C2 Path label) */
    uint16_t        ewis_tx_a1_a2;          /**< E-WIS Tx A1/A2 Octets (frame alignment)*/
    uint16_t        ewis_tx_c2_h1;          /**< E-WIS Tx C2/H1 Octets */
    uint16_t        ewis_tx_h2_h3;          /**< E-WIS Tx H2/H3 Octets */
    uint16_t        ewis_tx_z0_e1;          /**< E-WIS Tx Z0/E1 Octets */
    uint16_t        ewis_rx_frm_ctrl1;      /**< E-WIS Rx Framer Control 1 */
    uint16_t        ewis_rx_frm_ctrl2;      /**< E-WIS Rx Framer Control 2 */
    uint16_t        ewis_lof_ctrl1;         /**< E-WIS Loss of Frame Control 1 */
    uint16_t        ewis_lof_ctrl2;         /**< E-WIS Loss of Frame Control 2 */
    uint16_t        ewis_rx_err_frc1;       /**< E-WIS Rx Error Force Control 1 (incl RXLOF_ON_LOPC and APS_THRES configuration)*/
    uint16_t        ewis_pmtick_ctrl;       /**< E-WIS Performance Monitor Control (define how PMTICK works)*/
    uint16_t        ewis_cnt_cfg;           /**< E-WIS Counter Configuration (bit/block mode)*/
} mesa_ewis_static_conf_t CAP(PHY_10G);

/** \brief signal label configuration */
typedef struct mesa_ewis_sl_conf_s {
        uint8_t   exsl;           /**< expected signal label value */
} mesa_ewis_sl_conf_t CAP(PHY_10G);

/** \brief eWIS configuration primitives, 
 *         used to hold all the configuration parameters in the internal state in the API.
 */
typedef struct mesa_ewis_conf_s {
    mesa_bool_t                   ewis_init_done;        /**< Indicate WIS mode is enabled */
    mesa_ewis_static_conf_t       static_conf;           /**< Static configuration */
    mesa_ewis_mode_t              ewis_mode;             /**< EWIS mode configuration */
    mesa_ewis_cons_act_t          section_cons_act;      /**< Section consequent action configuraiton */
    mesa_ewis_tti_t               section_txti;          /**< Section Trail Trace Identifier configuration */
    mesa_ewis_force_mode_t        force_mode;            /**< Force mode configuration */
    mesa_ewis_tti_t               path_txti;             /**< Path Trail Trace Identifier Configuration */
    mesa_ewis_tx_oh_t             tx_oh;                 /**< Transmit Overhead */
    mesa_ewis_tx_oh_passthru_t    tx_oh_passthru;        /**< Transmit Overhead Passthru Configuration */
    mesa_ewis_sl_conf_t           exp_sl;                /**< Expected Signal Label */
    mesa_ewis_test_conf_t         test_conf;             /**< EWIS Test Mode configuration */
    mesa_ewis_counter_threshold_t ewis_cntr_thresh_conf; /**< EWIS counter threshold configuration */
    mesa_ewis_perf_mode_t         perf_mode;             /**< EWIS mode configuration */
} mesa_ewis_conf_t CAP(PHY_10G);

/* ================================================================= *
 *  Defects/Events
 * ================================================================= */
/**
 * \brief WIS interrupt events 
 * \note These interrupts are not used for 8487-15/8488-15.
 *  There are seperate type mesa_phy_10g_event_t defined in mesa_phy_10g_api.h for these chips.
 **/
#define MESA_EWIS_SEF_EV                    0x00000001  /**< SEF has changed state */
#define MESA_EWIS_FPLM_EV                   0x00000002  /**< far-end (PLM-P) / (LCDP) */
#define MESA_EWIS_FAIS_EV                   0x00000004  /**< far-end (AIS-P) / (LOP) */
#define MESA_EWIS_LOF_EV                    0x00000008  /**< Loss of Frame (LOF) */
#define MESA_EWIS_LOS_EV                    0x00000010  /**< Loss of Signal (LOS) */
#define MESA_EWIS_RDIL_EV                   0x00000020  /**< Line Remote Defect Indication (RDI-L) */
#define MESA_EWIS_AISL_EV                   0x00000040  /**< Line Alarm Indication Signal (AIS-L) */
#define MESA_EWIS_LCDP_EV                   0x00000080  /**< Loss of Code-group Delineation (LCD-P) */
#define MESA_EWIS_PLMP_EV                   0x00000100  /**< Path Label Mismatch (PLMP) */
#define MESA_EWIS_AISP_EV                   0x00000200  /**< Path Alarm Indication Signal (AIS-P) */
#define MESA_EWIS_LOPP_EV                   0x00000400  /**< Path Loss of Pointer (LOP-P) */
#define MESA_EWIS_MODULE_EV                 0x00000800  /**< GPIO pin state being driven by optics module */
#define MESA_EWIS_TXLOL_EV                  0x00001000  /**< PMA CMU Loss of Lock */
#define MESA_EWIS_RXLOL_EV                  0x00002000  /**< PMA CRU Loss of Lock */
#define MESA_EWIS_LOPC_EV                   0x00004000  /**< Loss of Optical Carrier (LOPC) */
#define MESA_EWIS_UNEQP_EV                  0x00008000  /**< Unequiped Path (UNEQ-P) */
#define MESA_EWIS_FEUNEQP_EV                0x00010000  /**< Far-end Unequiped Path (UNEQ-P) */
#define MESA_EWIS_FERDIP_EV                 0x00020000  /**< Far-end Path Remote Defect Identifier (RDI-P) */
#define MESA_EWIS_REIL_EV                   0x00040000  /**< Line Remote Error Indication (REI-L) */
#define MESA_EWIS_REIP_EV                   0x00080000  /**< Path Remote Error Indication (REI-P) */
#define MESA_EWIS_HIGH_BER_EV               0x00100000  /**< PCS high bit error rate (BER) */

#define MESA_EWIS_PCS_RECEIVE_FAULT_PEND    0x00200000  /**< PCS Receive fault */

#define MESA_EWIS_B1_NZ_EV                  0x00400000  /**< PMTICK B1 BIP (B1_ERR_CNT) not zero */
#define MESA_EWIS_B2_NZ_EV                  0x00800000  /**< PMTICK B2 BIP (B1_ERR_CNT) not zero */
#define MESA_EWIS_B3_NZ_EV                  0x01000000  /**< PMTICK B3 BIP (B1_ERR_CNT) not zero */
#define MESA_EWIS_REIL_NZ_EV                0x02000000  /**< PMTICK REI-L (REIL_ERR_CNT) not zero */
#define MESA_EWIS_REIP_NZ_EV                0x04000000  /**< PMTICK REI-P (REIP_ERR_CNT) not zero */

#define MESA_EWIS_B1_THRESH_EV              0x08000000  /**< B1_THRESH_ERR */
#define MESA_EWIS_B2_THRESH_EV              0x10000000  /**< B2_THRESH_ERR */
#define MESA_EWIS_B3_THRESH_EV              0x20000000  /**< B3_THRESH_ERR */
#define MESA_EWIS_REIL_THRESH_EV            0x40000000  /**< REIL_THRESH_ERR */
#define MESA_EWIS_REIP_THRESH_EV            0x80000000  /**< REIp_THRESH_ERR */

typedef uint64_t mesa_ewis_event_t CAP(PHY_10G); /**< Int events: Single event or 'OR' multiple events above */

/**
 * \brief Enable event generation for a specific event type or group of events
 * \note Not applicable for 8487/8488-15
 *
 * \param inst    [IN]   Target instance reference.
 * \param port_no [IN]   Port number
 * \param enable  [IN]   Enable or disable events
 * \param ev_mask [IN]   Event type(s) to control (mask)
 *
 * \return Return code.
 **/

mesa_rc mesa_ewis_event_enable(const mesa_inst_t       inst,
                               const mesa_port_no_t    port_no,
                               const mesa_bool_t       enable,
                               const mesa_ewis_event_t ev_mask)
    CAP(PHY_10G);

/**
 * \brief Polling function called at by interrupt or periodically
 * \note Interrupt status will be cleared on read.
 * Not applicable for 8487/8488-15
 *
 * \param inst    [IN]   Target instance reference.
 * \param port_no [IN]   Port number
 * \param status  [OUT]  Event status, bit set indicates corresponding
 *                       event/interrupt has detected
 *
 * \return Return code.
 **/

mesa_rc mesa_ewis_event_poll(const mesa_inst_t    inst,
                             const mesa_port_no_t port_no,
                             mesa_ewis_event_t    *const status)
    CAP(PHY_10G);


/**
 * \brief Forces one or more WIS events to occur (simulated events)
 * \note useful in debugging.
 *
 * \param inst    [IN]   Target instance reference.
 * \param port_no [IN]   Port number
 * \param enable  [IN]   Enable or disable events
 * \param ev_force  [IN]  Mask defining which events are forces
 *
 * \return Return code.
 **/

mesa_rc mesa_ewis_event_force(const mesa_inst_t       inst,
                              const mesa_port_no_t    port_no,
                              const mesa_bool_t       enable,
                              const mesa_ewis_event_t ev_force)
    CAP(PHY_10G);


/* ================================================================= *
 *  Static Config
 * ================================================================= */
/**
 * \brief Get eWIS static configuration.
 *
 * \param inst [IN]       Target instance reference.
 * \param port_no [IN]    Port number.
 * \param stat_conf [OUT] Get eWIS Static configuration, i.e configuration that is set up at initialization,
 *                        and not changed afterwards.
 *
 * \return Return code.
 **/

mesa_rc mesa_ewis_static_conf_get(const mesa_inst_t       inst,
                                  const mesa_port_no_t    port_no,
                                  mesa_ewis_static_conf_t *const stat_conf)
    CAP(PHY_10G);

/**
 * \brief Set WIS force mode configuration.
 * The WIS can be forced to induce a particular condition, These can be configured
 * in mesa_ewis_force_mode_t.
 * AIS,RDI can be forced in Tx and Rx directions and force UNEQ and RDI in path layer. 
 *
 * \param inst [IN]       Target instance reference.
 * \param port_no [IN]    Port number.
 * \param force_conf [IN] Set force mode.
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_force_conf_set(const mesa_inst_t            inst,
                                 const mesa_port_no_t         port_no,
                                 const mesa_ewis_force_mode_t *const force_conf)
    CAP(PHY_10G);


/**
 * \brief Get WIS force mode configuration.
 *
 * \param inst [IN]        Target instance reference.
 * \param port_no [IN]     Port number.
 * \param force_conf [OUT] Get force mode configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_force_conf_get(const mesa_inst_t      inst,
                                 const mesa_port_no_t   port_no,
                                 mesa_ewis_force_mode_t *const force_conf)
    CAP(PHY_10G);

/**
 * \brief Set WIS transmitted overhead bytes.
 * Supports insertion of various Section, line and path overhead Bytes.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param tx_oh [IN]     Transmitted overhead byte values
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_tx_oh_set(const mesa_inst_t      inst,
                           const mesa_port_no_t    port_no,
                           const mesa_ewis_tx_oh_t *const tx_oh)
    CAP(PHY_10G);

/**
 * \brief Get configured WIS transmitted overhead bytes.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param tx_oh [OUT]    Transmitted overhead byte values
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_tx_oh_get(const mesa_inst_t    inst,
                            const mesa_port_no_t port_no,
                            mesa_ewis_tx_oh_t    *const tx_oh)
    CAP(PHY_10G);

/**
 * \brief Set eWIS overhead passthru configuration.
 *
 * \param inst [IN]           Target instance reference.
 * \param port_no [IN]        Port number.
 * \param tx_oh_passthru [IN] Transmitted overhead passthrough configuration
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_tx_oh_passthru_set(const mesa_inst_t                inst,
                                     const mesa_port_no_t             port_no,
                                     const mesa_ewis_tx_oh_passthru_t *const tx_oh_passthru)
    CAP(PHY_10G);

/**
 * \brief Get eWIS overhead passthru configuration.
 *
 * \param inst [IN]              Target instance reference.
 * \param port_no [IN]           Port number.
 * \param tx_oh_passthru [OUT]   Transmitted overhead passthrough configuration
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_tx_oh_passthru_get(const mesa_inst_t          inst,
                                     const mesa_port_no_t       port_no,
                                     mesa_ewis_tx_oh_passthru_t *const tx_oh_passthru)
    CAP(PHY_10G);

/* ================================================================= *
 *  Dynamic Config
 * ================================================================= */


/**
 * \brief Set eWIS mode.
 * \note Should not used for 8487-15/8488-15.
 * The mode configuration is enabled by calling mesa_phy_10g_mode_set in the case of 8487-15.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param mode [IN]      Set WIS mode (Disable, WIS, STS192, STM64).
 *                       sts192
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_mode_set(const mesa_inst_t      inst,
                           const mesa_port_no_t   port_no,
                           const mesa_ewis_mode_t *const mode)
    CAP(PHY_10G);

/**
 * \brief Get WIS mode.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param mode [OUT]     Get WIS mode (Disable, WIS, STS192, STM64).
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_mode_get(const mesa_inst_t    inst,
                           const mesa_port_no_t port_no,
                           mesa_ewis_mode_t     *const mode)
    CAP(PHY_10G);


/**
 * \brief   Reset WIS block.
 * \note    Useful only for 8487-17/8488-15.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_reset(const mesa_inst_t    inst,
                        const mesa_port_no_t port_no)
    CAP(PHY_10G);

/**
 * \brief Set consequent actions, i.e. how to handle AIS-L insertion and RDI_L backreporting.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param cons_act [IN]  pointer to consequent actions.
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_cons_act_set(const mesa_inst_t          inst,
                               const mesa_port_no_t       port_no,
                               const mesa_ewis_cons_act_t *const cons_act)
    CAP(PHY_10G);

/**
 * \brief Get the configured consequent actions.
 *
 * \param inst [IN]       Target instance reference.
 * \param port_no [IN]    Port number.
 * \param cons_act [OUT]  pointer to consequent actions.
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_cons_act_get(const mesa_inst_t    inst,
                               const mesa_port_no_t port_no,
                               mesa_ewis_cons_act_t *const cons_act)
    CAP(PHY_10G);


/*
 *  Section layer
 * ================================================================= */

/**
 * \brief Set section transmitted Trail Trace Identifier.
 *  The transmitted trace identifier is aligned according to the specification, i.e
 *  16 byte mode: In the first byte MSB = 1, and all other bytes MSB = 0.
 *  64 byte mode: this is a text string terminated with CR/LF.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param txti [IN]      pointer to transmitted tti.
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_section_txti_set(const mesa_inst_t     inst,
                                   const mesa_port_no_t  port_no,
                                   const mesa_ewis_tti_t *const txti)
    CAP(PHY_10G);

/**
 * \brief Get the configured section transmitted Trail Trace Identifier.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param txti [OUT]     pointer to transmitted tti.
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_section_txti_get(const mesa_inst_t    inst,
                                   const mesa_port_no_t port_no,
                                   mesa_ewis_tti_t      *const txti)
    CAP(PHY_10G);

/**
  * \brief Set expected Signal label.
  *  The signal label is only configurable in SONET/SDH mode, in this mode the
  *  path overhead is not terminated, it is only monitored, i.e. only expected 
  *  signal label is configurable.
  *
  * \param inst [IN]      Target instance reference.
  * \param port_no [IN]   Port number.
  * \param sl [IN]        pointer to expected signal label.
  *
  * \return Return code.
  **/ 
mesa_rc mesa_ewis_exp_sl_set (const mesa_inst_t         inst,
                              const mesa_port_no_t      port_no,
                              const mesa_ewis_sl_conf_t *const sl)
    CAP(PHY_10G);


/*
 *  Path layer
 * ================================================================= */

/**
 * \brief Set Path Transmitted Trail Trace Identifier.
 *  The transmitted trace identifier is aligned according to the specification, i.e
 *  16 byte mode: In the first byte MSB = 1, and all other bytes MSB = 0.
 *  64 byte mode: this is a text string terminated with CR/LF. *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param txti [IN]      pointer to transmitted tti.
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_path_txti_set(const mesa_inst_t     inst,
                                const mesa_port_no_t  port_no,
                                const mesa_ewis_tti_t *const txti)
    CAP(PHY_10G);

/**
 * \brief Get the configured Path Transmitted Trail Trace Identifier.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param txti [OUT]     pointer to transmitted tti.
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_path_txti_get(const mesa_inst_t    inst,
                                const mesa_port_no_t port_no,
                                mesa_ewis_tti_t      *const txti)
    CAP(PHY_10G);

/* ================================================================= *
 *  Test Config/status
 * ================================================================= */


/**
 * \brief Set WIS test mode.
 * \note  This is useful for debugging purpose.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param test_mode [IN] Set WIS test mode (loopback and test patterns).
 *
 * \return Return code.
 *
 * Test pattern setup is applied to both TX (test generator) and RX (test analyzer)
 **/
mesa_rc mesa_ewis_test_mode_set(const mesa_inst_t           inst,
                                const mesa_port_no_t        port_no,
                                const mesa_ewis_test_conf_t *const test_mode)
    CAP(PHY_10G);

/**
 * \brief Get eWIS test mode.
 * \note  This is useful for debugging purpose.
 *
 * \param inst [IN]       Target instance reference.
 * \param port_no [IN]    Port number.
 * \param test_mode [OUT] Get eWIS test mode (loopback and test patterns).
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_test_mode_get(const mesa_inst_t     inst,
                                const mesa_port_no_t  port_no,
                                mesa_ewis_test_conf_t *const test_mode)
    CAP(PHY_10G);

/**
 * \brief Inject eWIS PRBS31 errors.
 * \note  This is useful for debugging purpose.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param inj [IN]       Defines the type of error injected.
 *
 * \return Return code.
 *
 * Test pattern setup is applied to both TX (test generator) and RX (test analyzer)
 **/
mesa_rc mesa_ewis_prbs31_err_inj_set(const mesa_inst_t                inst,
                                     const mesa_port_no_t             port_no,
                                     const mesa_ewis_prbs31_err_inj_t *const inj)
    CAP(PHY_10G);

/**
 * \brief Get eWIS test counter.
 * \note  This is useful for debugging purpose.
 *
 * \param inst [IN]         Target instance reference.
 * \param port_no [IN]      Port number.
 * \param test_status [OUT] Get eWIS test status (test pattern error counter, clear on read).
 *
 * \return Return code.
 *
 * Test pattern error counter is only used in prbs31 mode. In mixed frequency mode, the normal performance counters
 * are maintained.
 **/
mesa_rc mesa_ewis_test_counter_get(const mesa_inst_t       inst,
                                   const mesa_port_no_t    port_no,
                                   mesa_ewis_test_status_t *const test_status)
    CAP(PHY_10G);


/* ================================================================= *
 *  State Reporting
 * ================================================================= */

/**
 * \brief Get eWIS defects.
 * Reports the currect status of the defects.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param def [OUT]      pointer to defect status structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_defects_get(const mesa_inst_t    inst,
                              const mesa_port_no_t port_no,
                              mesa_ewis_defects_t  *const def)
    CAP(PHY_10G);

/**
 * \brief Get eWIS fault and link status.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param status [OUT]   pointer to status structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_status_get(const mesa_inst_t    inst,
                             const mesa_port_no_t port_no,
                             mesa_ewis_status_t   *const status)
    CAP(PHY_10G);

/**
 * \brief Get section received (accepted) Trail Trace Identifier.
 *  The received trace identifier is aligned according to the specification, i.e
 *  16 byte mode: In the first byte MSB = 1, and all other bytes MSB = 0. (see G.707 section 9.2.2.2)
 *  No CRC checksum verification is done in the API.
 *  64 byte mode: this is a text string terminated with CR/LF.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param acti [OUT]     pointer to accepted tti.
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_section_acti_get(const mesa_inst_t    inst,
                                   const mesa_port_no_t port_no,
                                   mesa_ewis_tti_t      *const acti)
    CAP(PHY_10G);

/**
 * \brief Get path received (accepted) Trail Trace Identifier.
 *
 *  The received trace identifier is aligned according to the specification, i.e
 *  16 byte mode: In the first byte MSB = 1, and all other bytes MSB = 0. (see G.707 section 9.2.2.2)
 *  No CRC checksum verification is done in the API.
 *  64 byte mode: this is a text string terminated with CR/LF.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param acti [OUT]     pointer to accepted TTI.
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_path_acti_get(const mesa_inst_t    inst,
                                const mesa_port_no_t port_no,
                                mesa_ewis_tti_t      *const acti)
    CAP(PHY_10G);

/* ================================================================= *
 *  Performance Primitives
 * ================================================================= */

/**
 * \brief Get free running eWIS counters.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param counter [OUT]  pointer to counter structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_counter_get(const mesa_inst_t    inst,
                              const mesa_port_no_t port_no,
                              mesa_ewis_counter_t  *const counter)
    CAP(PHY_10G);

/**
 * \brief Get eWIS counters per second (performance primitives).
 * By default the source of PMTICK event (generation of 1 second) is configured to be internal.
 * The values are accumulate for a period of 1 second and are then updated in the associated registers.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param perf [OUT]     pointer to performance primitive structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_perf_get(const mesa_inst_t    inst,
                           const mesa_port_no_t port_no,
                           mesa_ewis_perf_t     *const perf)
    CAP(PHY_10G);


/**
 * \brief Set eWIS error counter thresholds per second.
 * The PHY generates an interrupt once the error counter exceeds the configured threshold values.
 * The units is frames per second.
 * The threshold value configuration is possible for B1,B2,B3,REIP,REIL errors.
 * Eg: a threshold value of 0 gives one interrupt for every 1 second if the error
 * counter is atleast 1.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param threshold [IN] pointer to counter threshold structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_counter_threshold_set(const mesa_inst_t                   inst,
                                        const mesa_port_no_t                port_no,
                                        const mesa_ewis_counter_threshold_t *const threshold)
    CAP(PHY_10G);

/**
 * \brief Get the configured eWIS error counter thresholds.
 *
 * \param inst [IN]        Target instance reference.
 * \param port_no [IN]     Port number.
 * \param threshold [OUT]  pointer to eWIS error counters threshold structure.
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_counter_threshold_get(const mesa_inst_t             inst,
                                        const mesa_port_no_t          port_no,
                                        mesa_ewis_counter_threshold_t *const threshold)
    CAP(PHY_10G);

/**
 * \brief Set the eWIS performance block counter modes.
 *
 * \param inst      [IN] Target instance reference.
 * \param port_no   [IN] Port number.
 * \param perf_mode [IN] Pointer to the modes of the all performance counters.
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_perf_mode_set(const mesa_inst_t           inst,
                                const mesa_port_no_t        port_no,
                                const mesa_ewis_perf_mode_t *const perf_mode)
    CAP(PHY_10G);

/**
 * \brief Get the eWIS performance block counter modes.
 *
 * \param inst      [IN]  Target instance reference.
 * \param port_no   [IN]  Port number.
 * \param perf_mode [OUT] Pointer to the modes of the all performance counters.
 *
 * \return Return code.
 **/
mesa_rc mesa_ewis_perf_mode_get(const mesa_inst_t     inst,
                                const mesa_port_no_t  port_no,
                                mesa_ewis_perf_mode_t *const perf_mode)
    CAP(PHY_10G);

#include <microchip/ethernet/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_SWITCH_API_WIS_
