// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <vtss_phy_api.h>

/**
 * \file vtss_wis_api.h
 * \brief eWIS layer API
 */

#ifndef _VTSS_WIS_API_H_
#define _VTSS_WIS_API_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ================================================================= *
 *  Data structures / types
 * ================================================================= */

/** \brief Trail Trace Identifier mode types */
typedef enum {
    VTSS_EWIS_TTI_MODE_1,     /**< one byte trace identifier */
    VTSS_EWIS_TTI_MODE_16,    /**< 16 bytes trace identifier */
    VTSS_EWIS_TTI_MODE_64,    /**< 64 bytes trace identifier */
    VTSS_EWIS_TTI_MODE_MAX
} vtss_ewis_tti_mode_t;

#define TTI_MODE_1   VTSS_EWIS_TTI_MODE_1   /**< Backward compatibility */
#define TTI_MODE_16  VTSS_EWIS_TTI_MODE_16  /**< Backward compatibility */
#define TTI_MODE_64  VTSS_EWIS_TTI_MODE_64  /**< Backward compatibility */
#define TTI_MODE_MAX VTSS_EWIS_TTI_MODE_MAX /**< Backward compatibility */

/** \brief Trail Trace Identifier type */
typedef struct vtss_ewis_tti_s {
    vtss_ewis_tti_mode_t mode;    /**< trace identifier mode (1,16,64 bytes) */
    u8                   tti[64]; /**< trace identifier value */
    BOOL                 valid;   /**< Identifies the Accepted valid TTI */
} vtss_ewis_tti_t;

/** \brief eWIS fault mask configuration, i.e set up which defects trigger the Fault condition */
typedef struct vtss_ewis_fault_cons_act_s {
    BOOL fault_on_feplmp;   /**< TRUE = enable fault condition on far-end PLM-P */
    BOOL fault_on_feaisp;   /**< TRUE = enable fault condition on far-end AIS-P */
    BOOL fault_on_rdil;     /**< TRUE = enable fault condition on RDI-L */
    BOOL fault_on_sef;      /**< TRUE = enable fault condition on SEF */
    BOOL fault_on_lof;      /**< TRUE = enable fault condition on LOF */
    BOOL fault_on_los;      /**< TRUE = enable fault condition on LOS */
    BOOL fault_on_aisl;     /**< TRUE = enable fault condition on AIS-L*/
    BOOL fault_on_lcdp;     /**< TRUE = enable fault condition on LCD-P*/
    BOOL fault_on_plmp;     /**< TRUE = enable fault condition on PLM-P*/
    BOOL fault_on_aisp;     /**< TRUE = enable fault condition on AIS-P*/
    BOOL fault_on_lopp;     /**< TRUE = enable fault condition on LOP-P*/
} vtss_ewis_fault_cons_act_t;

/** \brief eWIS AIS-L consequent actions */
typedef struct vtss_ewis_aisl_cons_act_s {
    BOOL ais_on_los;    /**< TRUE = enable for AIS-L insertion on LOS */
    BOOL ais_on_lof;    /**< TRUE = enable for AIS-L insertion on LOF */
} vtss_ewis_aisl_cons_act_t;

/** \brief eWIS RDI-L consequent actions */
typedef struct vtss_ewis_rdil_cons_act_s {
    BOOL rdil_on_los;   /**< TRUE = enable for RDI-L backreporting on LOS */
    BOOL rdil_on_lof;   /**< TRUE = enable for RDI-L backreporting on LOF */
    BOOL rdil_on_lopc;  /**< TRUE = enable for RDI-L backreporting on LOPC */
    BOOL rdil_on_ais_l; /**< TRUE = enable for RDI-L backreporting on AIS_L */
} vtss_ewis_rdil_cons_act_t;

/** \brief eWIS consequent actions */
typedef struct vtss_ewis_cons_act_s {
    vtss_ewis_aisl_cons_act_t aisl;    /**< AIS-L consequent action configuration */
    vtss_ewis_rdil_cons_act_t rdil;    /**< RDI-L consequent action configuration */
    vtss_ewis_fault_cons_act_t fault;  /**< FAULT condition consequent action configuration */
} vtss_ewis_cons_act_t;

/** \brief eWIS line force mode */
typedef struct vtss_ewis_line_force_mode_s {
    BOOL force_ais;    /**<  Force AIS-L configuration */
    BOOL force_rdi;    /**<  Force RDI-L configuration */
} vtss_ewis_line_force_mode_t;

/** \brief eWIS line TX force mode */
typedef struct vtss_ewis_line_tx_force_mode_s {
    BOOL force_ais;    /**<  Force transmission of AIS-L in the K2 byte */
    BOOL force_rdi;    /**<  Force transmission of RDI-L in the K2 byte */
} vtss_ewis_line_tx_force_mode_t;

/** \brief eWIS path force modes */
typedef struct vtss_ewis_path_force_mode_s {
    BOOL force_uneq;  /**< Force UNEQ-P configuration */
    BOOL force_rdi;   /**< Force RDI-P configuration */
} vtss_ewis_path_force_mode_t;

/** \brief eWIS force modes */
typedef struct vtss_ewis_force_mode_s {
    vtss_ewis_line_force_mode_t line_rx_force;       /**< Line force configuration rx direction */
    vtss_ewis_line_tx_force_mode_t line_tx_force;    /**< Line force configuration tx direction */
    vtss_ewis_path_force_mode_t path_force;          /**< Path force configuration */
} vtss_ewis_force_mode_t;

/** \brief eWIS Mode(Bit/Block) for the Performence Monitoring Counters */
typedef enum {
   VTSS_EWIS_PERF_MODE_BIT,   /**< Bit mode of the perf monitor counter*/
   VTSS_EWIS_PERF_MODE_BLOCK, /**< Block mode of the perf monitor counter*/
} vtss_ewis_perf_cntr_mode_t;

/** \brief eWIS Mode(Bit/Block) for the Performence Monitoring Counters */
typedef struct vtss_ewis_perf_mode_s {
    vtss_ewis_perf_cntr_mode_t pn_ebc_mode_s;       /**< Section BIP error count (B1))*/
    vtss_ewis_perf_cntr_mode_t pn_ebc_mode_l;       /**< Near end line block (BIP) error count (B2)*/
    vtss_ewis_perf_cntr_mode_t pf_ebc_mode_l;       /**< Far end line block (BIP) error count (REI-L) */
    vtss_ewis_perf_cntr_mode_t pn_ebc_mode_p;       /**< Path block error count (B3) */
    vtss_ewis_perf_cntr_mode_t pf_ebc_mode_p;       /**< Far end path block error count (REI-P)*/
} vtss_ewis_perf_mode_t;

/** \brief eWIS operational mode types */
typedef enum {
    VTSS_WIS_OPERMODE_DISABLE,  /** WIS mode disabled */
    VTSS_WIS_OPERMODE_WIS_MODE, /** WIS mode enabled */
    VTSS_WIS_OPERMODE_STS192,   /** WIS mode SONET - STS192 */
    VTSS_WIS_OPERMODE_STM64,    /** WIS mode SDH - STM64 */
    VTSS_WIS_OPERMODE_MAX       /** WIS mode Invalid */
} vtss_ewis_mode_t;

/** \brief eWIS status */
typedef struct vtss_ewis_status_s {
    BOOL fault;         /**< Fault condition (Latch on high) i.e. = true if any fault has occurred since previous read */
    BOOL link_stat;     /**< Link status condition (Latch on low) i.e. = false if any link error has occurred since previous read */
} vtss_ewis_status_t;

/** \brief eWIS defects */
typedef struct vtss_ewis_defects_s {
    BOOL dlos_s;        /**< Loss of signal */
    BOOL doof_s;        /**< Out of frame */
    BOOL dlof_s;        /**< Loss of frame */
    BOOL dais_l;        /**< Line alarm indication signal */
    BOOL drdi_l;        /**< Line remote defect indication */
    BOOL dais_p;        /**< Path alarm indication signal */
    BOOL dlop_p;        /**< Loss of pointer */
    BOOL duneq_p;       /**< Path Unequipped, not supported in 8487/8488 */
    BOOL drdi_p;        /**< Path Remote Defect Indication, not supported in 8487/8488 */
    BOOL dlcd_p;        /**< Path loss of code-group delineation */
    BOOL dplm_p;        /**< Path loss of code-group delineation */
    /* far end path defects */
    BOOL dfais_p;       /**< far-end AIS-P/LOP-P */
    BOOL dfplm_p;       /**< far-end PLM-P/LCD-P defect */
    BOOL dfuneq_p;      /**< Far End Path Unequipped */
} vtss_ewis_defects_t;


/** \brief eWIS performance primitives.
 *  These data are assumed to be read once every sec. The counters holds increments compared to previous read.
 *  The namings and definitions are taken from ITU-T rec G.783.
 */
typedef struct vtss_ewis_perf_s {
    u32 pn_ebc_s;       /**< Section BIP error count */
    u32 pn_ebc_l;       /**< Near end line block (BIP) error count */
    u32 pf_ebc_l;       /**< Far end line block (BIP) error count */
    u32 pn_ebc_p;       /**< Path block error count */
    u32 pf_ebc_p;       /**< Far end path block error count */
} vtss_ewis_perf_t;

/** \brief eWIS performance counters.
*  These counters are free running counters that wraps to zero.
*/
typedef struct vtss_ewis_counter_s {
    u16 pn_ebc_p;       /**< Path block error count */
    u16 pf_ebc_p;       /**< Far end path block error count */
    u32 pn_ebc_l;       /**< Near end line block (BIP) error count */
    u32 pf_ebc_l;       /**< Far end line block (BIP) error count */
    u16 pn_ebc_s;       /**< Section BIP error count */
} vtss_ewis_counter_t;

/** \brief eWIS test pattern mode types.
 */
typedef enum vtss_ewis_test_pattern_s {
    VTSS_WIS_TEST_MODE_DISABLE,         /**< Disable test */
    VTSS_WIS_TEST_MODE_SQUARE_WAVE,     /**< Enable squarevave generator, Only valid for test generator */
    VTSS_WIS_TEST_MODE_PRBS31,          /**< Enable prbs31 generator/analyzer */
    VTSS_WIS_TEST_MODE_MIXED_FREQUENCY, /**< Enable mixed frequency generator / analyzer */
    VTSS_WIS_TEST_MODE_MAX              /**< Test mode Invalid */
} vtss_ewis_test_pattern_t;

/** \brief eWIS test configuration */
typedef struct vtss_ewis_test_conf_s {
    BOOL loopback;                              /**< loop output from Tx to Rx              */
    vtss_ewis_test_pattern_t test_pattern_gen;   /**< test pattern generation configuration  */
    vtss_ewis_test_pattern_t test_pattern_ana;   /**< test pattern analyzer configuration    */
} vtss_ewis_test_conf_t;

/** \brief eWIS test status */
typedef struct vtss_ewis_test_status_s {
    u16 tstpat_cnt;       /**< PRBS31 test pattern error counter. */
    BOOL  ana_sync;       /**< PRBS31 pattern checker is synchronized to the data. */
} vtss_ewis_test_status_t;

/** \brief WIS transmitted overhead data.
 *         only a few oh bytes can be set dynamically. These OH bytes are not configurable from the API:
 *         H4 : multiframe indicator
 *         M0/M1: STS-1 Line Remote Error Indication (REI)
 *         G1: Path status
 */
typedef struct vtss_ewis_tx_oh_s {
    /**< Section Overhead: */
    u8         tx_dcc_s [3];    /**< Section Data Communications Channel(DCC) D1-D3*/
    u8         tx_e1;           /**< Orderwire */
    u8         tx_f1;           /**< Section User Channel */
    u8         tx_z0;           /**< Reserved for Section growth */
    /**< line overhead: */
    u8         tx_dcc_l [9];    /**< Line Data Communications Channel (DCC) D4-D12 */
    u8         tx_e2;           /**< Orderwire */
    u16        tx_k1_k2;        /**< Automatic protection switch (APS) channel and Line Remote Defect Identifier (RDI-L) */
    u8         tx_s1;           /**< Synchronization messaging */
    u16        tx_z1_z2;        /**< Reserved for Line growth  */
    /**< path overhead: */
    u8         tx_c2;           /**< Transmitted C2 path label */
    u8         tx_f2;           /**< Path User Channel  */
    u8         tx_n1;           /**< Tandem connection maintenance/Path data channel */
    u16        tx_z3_z4;        /**< Reserved for Path growth  */
} vtss_ewis_tx_oh_t;

/** \brief eWIS overhead passthru configuration.
  */
typedef struct vtss_ewis_tx_passthru_s {
    /**< Section Overhead: */
    BOOL       tx_j0;           /**< j0 Section TTI  passthrough */
    BOOL       tx_z0;           /**< z0 Section growth passthrough */
    BOOL       tx_b1;           /**< b1 BIP passthrough */
    BOOL       tx_e1;           /**< e1 order wire passthrough */
    BOOL       tx_f1;           /**< f1 Section user channel */
    BOOL       tx_dcc_s;        /**< Section Data communication channel passthrough D1-D3 */
    BOOL       tx_soh;          /**< Section Reserved National and unused bytes passthrough */

    /**< line overhead: */
    BOOL       tx_b2;           /**< b2 BIP passthrough */
    BOOL       tx_k1;           /**< k1 passthrough */
    BOOL       tx_k2;           /**< k2 passthrough */
    BOOL       tx_reil;         /**< reil passthrough */
    BOOL       tx_dcc_l;        /**< Section Data communication channel passthrough D4-D12*/
    BOOL       tx_s1;           /**< Synchronization messaging passthrough */
    BOOL       tx_e2;           /**< order wire passthrough */
    BOOL       tx_z1_z2;        /**< Reserved for path growth passthrough */
    BOOL       tx_loh;          /**< Line Reserved National and unused bytes passthrough */
} vtss_ewis_tx_oh_passthru_t;

/** \brief eWIS performance counter thresholds.
*/
typedef struct vtss_ewis_counter_threshold_s {
    u32 n_ebc_thr_s;       /**< Section error count (B1) threshold */
    u32 n_ebc_thr_l;       /**< Near end line error count (B2) threshold */
    u32 f_ebc_thr_l;       /**< Far end line error count threshold */
    u32 n_ebc_thr_p;       /**< Path block error count (B3) threshold */
    u32 f_ebc_thr_p;       /**< Far end path error count threshold */
} vtss_ewis_counter_threshold_t;

/** \brief test error injection types */
typedef enum {
    VTSS_EWIS_PRBS31_SINGLE_ERR, /**< Inject a single bit error (=> error counter incrementing by 3 */
    VTSS_EWIS_PRBS31_SAT_ERR,    /**< Force the PRBS31 pattern error counter to a value of 65528 (close to saturation) */
    VTSS_EWIS_PRBS31_MODE_MAX
} vtss_ewis_prbs31_err_inj_t;

#define EWIS_PRBS31_SINGLE_ERR VTSS_EWIS_PRBS31_SINGLE_ERR /**< Backward compatibility */
#define EWIS_PRBS31_SAT_ERR    VTSS_EWIS_PRBS31_SAT_ERR    /**< Backward compatibility */
#define EWIS_PRBS31_MODE_MAX   VTSS_EWIS_PRBS31_MODE_MAX   /**< Backward compatibility */

/** \brief eWIS static configuration data, 
 *  \note This is specific to 8487/8488-15.
 */
typedef struct vtss_ewis_static_conf_s {
    u16        ewis_txctrl1;           /**< WIS Vendor Specific Tx Control 1 */
    u16        ewis_txctrl2;           /**< WIS Vendor Specific Tx Control 2 */
    u16        ewis_rx_ctrl1;          /**< E-WIS Rx Control 1 */
    u16        ewis_mode_ctrl;         /**< E-WIS Mode Control (incl expected C2 Path label) */
    u16        ewis_tx_a1_a2;          /**< E-WIS Tx A1/A2 Octets (frame alignment)*/
    u16        ewis_tx_c2_h1;          /**< E-WIS Tx C2/H1 Octets */
    u16        ewis_tx_h2_h3;          /**< E-WIS Tx H2/H3 Octets */
    u16        ewis_tx_z0_e1;          /**< E-WIS Tx Z0/E1 Octets */
    u16        ewis_rx_frm_ctrl1;      /**< E-WIS Rx Framer Control 1 */
    u16        ewis_rx_frm_ctrl2;      /**< E-WIS Rx Framer Control 2 */
    u16        ewis_lof_ctrl1;         /**< E-WIS Loss of Frame Control 1 */
    u16        ewis_lof_ctrl2;         /**< E-WIS Loss of Frame Control 2 */
    u16        ewis_rx_err_frc1;       /**< E-WIS Rx Error Force Control 1 (incl RXLOF_ON_LOPC and APS_THRES configuration)*/
    u16        ewis_pmtick_ctrl;       /**< E-WIS Performance Monitor Control (define how PMTICK works)*/
    u16        ewis_cnt_cfg;           /**< E-WIS Counter Configuration (bit/block mode)*/
} vtss_ewis_static_conf_t;

/** \brief signal label configuration */
typedef struct vtss_ewis_sl_conf_s {
        u8   exsl;           /**< expected signal label value */
} vtss_ewis_sl_conf_t;

/** \brief eWIS configuration primitives, 
 *         used to hold all the configuration parameters in the internal state in the API.
 */
typedef struct vtss_ewis_conf_s {
    BOOL                          ewis_init_done;        /**< Indicate WIS mode is enabled */
    vtss_ewis_static_conf_t       static_conf;           /**< Static configuration */
    vtss_ewis_mode_t              ewis_mode;             /**< EWIS mode configuration */
    vtss_ewis_cons_act_t          section_cons_act;      /**< Section consequent action configuraiton */
    vtss_ewis_tti_t               section_txti;          /**< Section Trail Trace Identifier configuration */
    vtss_ewis_force_mode_t        force_mode;            /**< Force mode configuration */
    vtss_ewis_tti_t               path_txti;             /**< Path Trail Trace Identifier Configuration */
    vtss_ewis_tx_oh_t             tx_oh;                 /**< Transmit Overhead */
    vtss_ewis_tx_oh_passthru_t    tx_oh_passthru;        /**< Transmit Overhead Passthru Configuration */
    vtss_ewis_sl_conf_t           exp_sl;                /**< Expected Signal Label */
    vtss_ewis_test_conf_t         test_conf;             /**< EWIS Test Mode configuration */
    vtss_ewis_counter_threshold_t ewis_cntr_thresh_conf; /**< EWIS counter threshold configuration */
    vtss_ewis_perf_mode_t         perf_mode;             /**< EWIS mode configuration */
} vtss_ewis_conf_t;

/* ================================================================= *
 *  Defects/Events
 * ================================================================= */
/**
 * \brief WIS interrupt events 
 * \note These interrupts are not used for 8487-15/8488-15.
 *  There are seperate type vtss_phy_10g_event_t defined in vtss_phy_10g_api.h for these chips.
 **/
#define VTSS_EWIS_SEF_EV                    0x00000001  /**< SEF has changed state */
#define VTSS_EWIS_FPLM_EV                   0x00000002  /**< far-end (PLM-P) / (LCDP) */
#define VTSS_EWIS_FAIS_EV                   0x00000004  /**< far-end (AIS-P) / (LOP) */
#define VTSS_EWIS_LOF_EV                    0x00000008  /**< Loss of Frame (LOF) */
#define VTSS_EWIS_LOS_EV                    0x00000010  /**< Loss of Signal (LOS) */
#define VTSS_EWIS_RDIL_EV                   0x00000020  /**< Line Remote Defect Indication (RDI-L) */
#define VTSS_EWIS_AISL_EV                   0x00000040  /**< Line Alarm Indication Signal (AIS-L) */
#define VTSS_EWIS_LCDP_EV                   0x00000080  /**< Loss of Code-group Delineation (LCD-P) */
#define VTSS_EWIS_PLMP_EV                   0x00000100  /**< Path Label Mismatch (PLMP) */
#define VTSS_EWIS_AISP_EV                   0x00000200  /**< Path Alarm Indication Signal (AIS-P) */
#define VTSS_EWIS_LOPP_EV                   0x00000400  /**< Path Loss of Pointer (LOP-P) */
#define VTSS_EWIS_MODULE_EV                 0x00000800  /**< GPIO pin state being driven by optics module */
#define VTSS_EWIS_TXLOL_EV                  0x00001000  /**< PMA CMU Loss of Lock */
#define VTSS_EWIS_RXLOL_EV                  0x00002000  /**< PMA CRU Loss of Lock */
#define VTSS_EWIS_LOPC_EV                   0x00004000  /**< Loss of Optical Carrier (LOPC) */
#define VTSS_EWIS_UNEQP_EV                  0x00008000  /**< Unequiped Path (UNEQ-P) */
#define VTSS_EWIS_FEUNEQP_EV                0x00010000  /**< Far-end Unequiped Path (UNEQ-P) */
#define VTSS_EWIS_FERDIP_EV                 0x00020000  /**< Far-end Path Remote Defect Identifier (RDI-P) */
#define VTSS_EWIS_REIL_EV                   0x00040000  /**< Line Remote Error Indication (REI-L) */
#define VTSS_EWIS_REIP_EV                   0x00080000  /**< Path Remote Error Indication (REI-P) */
#define VTSS_EWIS_HIGH_BER_EV               0x00100000  /**< PCS high bit error rate (BER) */

#define VTSS_EWIS_PCS_RECEIVE_FAULT_PEND    0x00200000  /**< PCS Receive fault */

#define VTSS_EWIS_B1_NZ_EV                  0x00400000  /**< PMTICK B1 BIP (B1_ERR_CNT) not zero */
#define VTSS_EWIS_B2_NZ_EV                  0x00800000  /**< PMTICK B2 BIP (B1_ERR_CNT) not zero */
#define VTSS_EWIS_B3_NZ_EV                  0x01000000  /**< PMTICK B3 BIP (B1_ERR_CNT) not zero */
#define VTSS_EWIS_REIL_NZ_EV                0x02000000  /**< PMTICK REI-L (REIL_ERR_CNT) not zero */
#define VTSS_EWIS_REIP_NZ_EV                0x04000000  /**< PMTICK REI-P (REIP_ERR_CNT) not zero */

#define VTSS_EWIS_B1_THRESH_EV              0x08000000  /**< B1_THRESH_ERR */
#define VTSS_EWIS_B2_THRESH_EV              0x10000000  /**< B2_THRESH_ERR */
#define VTSS_EWIS_B3_THRESH_EV              0x20000000  /**< B3_THRESH_ERR */
#define VTSS_EWIS_REIL_THRESH_EV            0x40000000  /**< REIL_THRESH_ERR */
#define VTSS_EWIS_REIP_THRESH_EV            0x80000000  /**< REIp_THRESH_ERR */

typedef u64 vtss_ewis_event_t; /**< Int events: Single event or 'OR' multiple events above */

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

vtss_rc vtss_ewis_event_enable(const vtss_inst_t         inst,
                               const vtss_port_no_t      port_no,
                               const BOOL                enable,
                               const vtss_ewis_event_t   ev_mask);

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

vtss_rc vtss_ewis_event_poll(const vtss_inst_t     inst,
                             const vtss_port_no_t  port_no,
                             vtss_ewis_event_t     *const status);


/**
 * \brief Polling function called at by interrupt or periodically
 * \note Interrupt status will be cleared on read.
 * Not applicable for 8487/8488-15
 *
 * \param inst    [IN]   Target instance reference.
 * \param port_no [IN]   Port number
 * \param status  [OUT]  Event status, bit set indicates corresponding
 *                       event/interrupt has detected irrespective of the mask register
 *
 * \return Return code.
 **/

vtss_rc vtss_ewis_event_poll_without_mask(const vtss_inst_t     inst,
                                          const vtss_port_no_t  port_no,
                                          vtss_ewis_event_t     *const status);


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

vtss_rc vtss_ewis_event_force(const vtss_inst_t         inst,
                              const vtss_port_no_t      port_no,
                              const BOOL                enable,
                              const vtss_ewis_event_t   ev_force);


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

vtss_rc vtss_ewis_static_conf_get(const vtss_inst_t inst,
                                  const vtss_port_no_t port_no,
                                  vtss_ewis_static_conf_t *const stat_conf);

/**
 * \brief Set WIS force mode configuration.
 * The WIS can be forced to induce a particular condition, These can be configured
 * in vtss_ewis_force_mode_t.
 * AIS,RDI can be forced in Tx and Rx directions and force UNEQ and RDI in path layer. 
 *
 * \param inst [IN]       Target instance reference.
 * \param port_no [IN]    Port number.
 * \param force_conf [IN] Set force mode.
 *
 * \return Return code.
 **/
vtss_rc vtss_ewis_force_conf_set(const vtss_inst_t inst,
                                 const vtss_port_no_t port_no,
                                 const vtss_ewis_force_mode_t *const force_conf);


/**
 * \brief Get WIS force mode configuration.
 *
 * \param inst [IN]        Target instance reference.
 * \param port_no [IN]     Port number.
 * \param force_conf [OUT] Get force mode configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_ewis_force_conf_get(const vtss_inst_t inst,
                                 const vtss_port_no_t port_no,
                                 vtss_ewis_force_mode_t *const force_conf);

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
vtss_rc vtss_ewis_tx_oh_set(const vtss_inst_t inst,
                           const vtss_port_no_t port_no,
                           const vtss_ewis_tx_oh_t *const tx_oh);

/**
 * \brief Get configured WIS transmitted overhead bytes.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param tx_oh [OUT]    Transmitted overhead byte values
 *
 * \return Return code.
 **/
vtss_rc vtss_ewis_tx_oh_get(const vtss_inst_t inst,
                            const vtss_port_no_t port_no,
                            vtss_ewis_tx_oh_t *const tx_oh);

/**
 * \brief Set eWIS overhead passthru configuration.
 *
 * \param inst [IN]           Target instance reference.
 * \param port_no [IN]        Port number.
 * \param tx_oh_passthru [IN] Transmitted overhead passthrough configuration
 *
 * \return Return code.
 **/
vtss_rc vtss_ewis_tx_oh_passthru_set(const vtss_inst_t inst,
                                     const vtss_port_no_t port_no,
                                     const vtss_ewis_tx_oh_passthru_t *const tx_oh_passthru);

/**
 * \brief Get eWIS overhead passthru configuration.
 *
 * \param inst [IN]              Target instance reference.
 * \param port_no [IN]           Port number.
 * \param tx_oh_passthru [OUT]   Transmitted overhead passthrough configuration
 *
 * \return Return code.
 **/
vtss_rc vtss_ewis_tx_oh_passthru_get(const vtss_inst_t inst,
                                     const vtss_port_no_t port_no,
                                     vtss_ewis_tx_oh_passthru_t *const tx_oh_passthru);

/* ================================================================= *
 *  Dynamic Config
 * ================================================================= */


/**
 * \brief Set eWIS mode.
 * \note Should not used for 8487-15/8488-15.
 * The mode configuration is enabled by calling vtss_phy_10g_mode_set in the case of 8487-15.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param mode [IN]      Set WIS mode (Disable, WIS, STS192, STM64).
 *                       sts192
 *
 * \return Return code.
 **/
vtss_rc vtss_ewis_mode_set(const vtss_inst_t inst,
                           const vtss_port_no_t port_no,
                           const vtss_ewis_mode_t *const mode);

/**
 * \brief Get WIS mode.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param mode [OUT]     Get WIS mode (Disable, WIS, STS192, STM64).
 *
 * \return Return code.
 **/
vtss_rc vtss_ewis_mode_get(const vtss_inst_t inst,
                           const vtss_port_no_t port_no,
                           vtss_ewis_mode_t *const mode);


/**
 * \brief   Reset WIS block.
 * \note    Useful only for 8487-17/8488-15.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 *
 * \return Return code.
 **/
vtss_rc vtss_ewis_reset(const vtss_inst_t inst,
                        const vtss_port_no_t port_no);

/**
 * \brief Set consequent actions, i.e. how to handle AIS-L insertion and RDI_L backreporting.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param cons_act [IN]  pointer to consequent actions.
 *
 * \return Return code.
 **/
vtss_rc vtss_ewis_cons_act_set(const vtss_inst_t inst,
                               const vtss_port_no_t port_no,
                               const vtss_ewis_cons_act_t *const cons_act);

/**
 * \brief Get the configured consequent actions.
 *
 * \param inst [IN]       Target instance reference.
 * \param port_no [IN]    Port number.
 * \param cons_act [OUT]  pointer to consequent actions.
 *
 * \return Return code.
 **/
vtss_rc vtss_ewis_cons_act_get(const vtss_inst_t inst,
                               const vtss_port_no_t port_no,
                               vtss_ewis_cons_act_t *const cons_act);


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
vtss_rc vtss_ewis_section_txti_set(const vtss_inst_t inst,
                                   const vtss_port_no_t port_no,
                                   const vtss_ewis_tti_t *const txti);

/**
 * \brief Get the configured section transmitted Trail Trace Identifier.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param txti [OUT]     pointer to transmitted tti.
 *
 * \return Return code.
 **/
vtss_rc vtss_ewis_section_txti_get(const vtss_inst_t inst,
                                   const vtss_port_no_t port_no,
                                   vtss_ewis_tti_t *const txti);

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
vtss_rc vtss_ewis_exp_sl_set (const vtss_inst_t inst,
                              const vtss_port_no_t port_no,
                              const vtss_ewis_sl_conf_t * const sl);


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
vtss_rc vtss_ewis_path_txti_set(const vtss_inst_t inst,
                                const vtss_port_no_t port_no,
                                const vtss_ewis_tti_t *const txti);

/**
 * \brief Get the configured Path Transmitted Trail Trace Identifier.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param txti [OUT]     pointer to transmitted tti.
 *
 * \return Return code.
 **/
vtss_rc vtss_ewis_path_txti_get(const vtss_inst_t inst,
                                const vtss_port_no_t port_no,
                                vtss_ewis_tti_t *const txti);

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
vtss_rc vtss_ewis_test_mode_set(const vtss_inst_t inst,
                                const vtss_port_no_t port_no,
                                const vtss_ewis_test_conf_t *const test_mode);

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
vtss_rc vtss_ewis_test_mode_get(const vtss_inst_t inst,
                                const vtss_port_no_t port_no,
                                vtss_ewis_test_conf_t *const test_mode);
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
vtss_rc vtss_ewis_prbs31_err_inj_set(const vtss_inst_t inst,
                                     const vtss_port_no_t port_no,
                                     const vtss_ewis_prbs31_err_inj_t *const inj);

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
vtss_rc vtss_ewis_test_counter_get(const vtss_inst_t inst,
                                   const vtss_port_no_t port_no,
                                   vtss_ewis_test_status_t *const test_status);


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
vtss_rc vtss_ewis_defects_get(const vtss_inst_t inst,
                              const vtss_port_no_t port_no,
                              vtss_ewis_defects_t *const def);

/**
 * \brief Get eWIS fault and link status.
 *
 * \param inst [IN]      Target instance reference.
 * \param port_no [IN]   Port number.
 * \param status [OUT]   pointer to status structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_ewis_status_get(const vtss_inst_t inst,
                             const vtss_port_no_t port_no,
                             vtss_ewis_status_t *const status);

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
vtss_rc vtss_ewis_section_acti_get(const vtss_inst_t inst,
                                   const vtss_port_no_t port_no,
                                   vtss_ewis_tti_t *const acti);

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
vtss_rc vtss_ewis_path_acti_get(const vtss_inst_t inst,
                                const vtss_port_no_t port_no,
                                vtss_ewis_tti_t *const acti);

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
vtss_rc vtss_ewis_counter_get(const vtss_inst_t inst,
                           const vtss_port_no_t port_no,
                           vtss_ewis_counter_t *const counter);

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
vtss_rc vtss_ewis_perf_get(const vtss_inst_t inst,
                           const vtss_port_no_t port_no,
                           vtss_ewis_perf_t *const perf);


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
vtss_rc vtss_ewis_counter_threshold_set(const vtss_inst_t inst,
                                        const vtss_port_no_t port_no,
                                        const vtss_ewis_counter_threshold_t *const threshold);

/**
 * \brief Get the configured eWIS error counter thresholds.
 *
 * \param inst [IN]        Target instance reference.
 * \param port_no [IN]     Port number.
 * \param threshold [OUT]  pointer to eWIS error counters threshold structure.
 *
 * \return Return code.
 **/
vtss_rc vtss_ewis_counter_threshold_get(const vtss_inst_t inst,
                                        const vtss_port_no_t port_no,
                                        vtss_ewis_counter_threshold_t *const threshold);

/**
 * \brief Set the eWIS performance block counter modes.
 *
 * \param inst      [IN] Target instance reference.
 * \param port_no   [IN] Port number.
 * \param perf_mode [IN] Pointer to the modes of the all performance counters.
 *
 * \return Return code.
 **/
vtss_rc vtss_ewis_perf_mode_set(const vtss_inst_t inst,
                                const vtss_port_no_t port_no,
                                const vtss_ewis_perf_mode_t *const perf_mode);

/**
 * \brief Get the eWIS performance block counter modes.
 *
 * \param inst      [IN]  Target instance reference.
 * \param port_no   [IN]  Port number.
 * \param perf_mode [OUT] Pointer to the modes of the all performance counters.
 *
 * \return Return code.
 **/
vtss_rc vtss_ewis_perf_mode_get(const vtss_inst_t inst,
                                const vtss_port_no_t port_no,
                                vtss_ewis_perf_mode_t *const perf_mode);

#ifdef __cplusplus
}
#endif
#endif /* _VTSS_WIS_API_H_ */
