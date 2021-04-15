// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_SD6G40_PROCS_H_
#define _VTSS_SD6G40_PROCS_H_


#ifdef USE_TCL_STUBS
#include "ute_webstax_defines.h"
#else
#include <vtss/api/types.h>
#endif

/* ================================================================= *
 *  Data structures / types
 * ================================================================= */


/** \brief Vitesse chip development name */
typedef enum {
    VTSS_SD6G40_CHIP_MASERATI,
    VTSS_SD6G40_CHIP_LAST
} vtss_sd6g40_chip_name_t;

/** \brief SerDes mode type for differnet configurations*/
typedef enum {
        VTSS_SD6G40_MODE_QSGMII,//R;only 1G/2G5 devices are used
        VTSS_SD6G40_MODE_QUSGMII,//U;only 5G devices are used
        VTSS_SD6G40_MODE_SGMII2G5,
        VTSS_SD6G40_MODE_SGMII,
        VTSS_SD6G40_MODE_1G_LAN,
        VTSS_SD6G40_MODE_NONE
} vtss_sd6g40_mode_t;



/*TX2RX Loopbacks */
typedef enum {
  VTSS_SD6G40_TX2RX_LOOP_NONE,
  VTSS_SD6G40_LTX2RX
} vtss_sd6g40_ltx2rx_t;

/*RX2TX Loopbacks */
typedef enum {
  VTSS_SD6G40_RX2TX_LOOP_NONE,
  VTSS_SD6G40_LRX2TX
} vtss_sd6g40_lrx2tx_t;


/** \brief Parameters needed for setup function */
typedef struct {
    vtss_sd6g40_chip_name_t     chip_name;   /**< Name of the vitesse chip >                                                              */
    vtss_sd6g40_mode_t  mode;      /**< Mode parameter.                                             */
    vtss_sd6g40_lrx2tx_t rx2tx_loop;    /**< Enable input loop NA, just place holder  >                                                       */
    vtss_sd6g40_ltx2rx_t tx2rx_loop;    /**< Enable pad loop  >                                                               */
    u8                   rx_eq;
    u8                   tx_preemp;
    BOOL                 txinvert;      /**< Enable inversion of output data >                                                       */
    BOOL                 rxinvert;      /**< Enable inversion of input data >                                                       */
    BOOL                 refclk125M;   /**< refclk is 125M**/
    BOOL                 mute;        /**< Mute Output Buffer. >                                 */
} vtss_sd6g40_setup_args_t;


typedef struct {
    vtss_sd6g40_mode_t  mode;      /**< Mode parameter.                                             */
    //u32                  datarate;       /**< optional parameter; if this is specified if_width must also be specified >                                                 */
    u8 lane_10bit_sel;
    u8 mpll_multiplier;
    u8 ref_clkdiv2;
    u8 tx_rate;
    u8 rx_rate;
} vtss_sd6g40_mode_args_t;

/** \brief return values of setup function */
typedef struct {
    u8  rx_eq[1];
    u8  tx_preemp[1];
    u8  rx_term_en[1];
    u8	lane_10bit_sel[1];
    u8	tx_invert[1];
    u8	rx_invert[1];
    u8	mpll_multiplier[1];
    u8	lane_loopbk_en[1];
    u8 ref_clkdiv2[1];
    u8 tx_rate[1];
    u8 rx_rate[1];
} vtss_sd6g40_setup_struct_t;



/* ================================================================= *
 *  Function prototypes
 * ================================================================= */
vtss_rc vtss_sd6g40_get_conf_from_mode(vtss_sd6g40_mode_t  mode, BOOL ref125M,
                                        vtss_sd6g40_mode_args_t *const ret_val);


//vtss_rc vtss_sd6g40_setup_tx_args_init(vtss_sd6g40_setup_tx_args_t     *const init_val);
//vtss_rc vtss_sd6g40_setup_rx_args_init(vtss_sd6g40_setup_rx_args_t     *const init_val);

vtss_rc vtss_calc_sd6g40_setup_lane(const vtss_sd6g40_setup_args_t config,
                                     vtss_sd6g40_setup_struct_t    *const ret_val);

//vtss_rc vtss_calc_sd6g40_lane_pwr_down(vtss_sd6g40_lane_pwr_down_t *const ret_val);

#endif
