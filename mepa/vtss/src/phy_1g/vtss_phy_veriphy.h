// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_PHY_VERIPHY_H
#define _VTSS_PHY_VERIPHY_H

#if VTSS_PHY_OPT_VERIPHY

#if defined(__C51__) || defined(__CX51__)
#define c51_idata idata
#define c51_code code
#else
#define c51_idata
#define c51_code
#endif /* __C51__ || __CX51__ */

#define ABS(x) (((x) < 0) ? -(x) : (x))

#define MAX_ABS_COEFF_ANOM_INVALID_NOISE  70
#define MAX_ABS_COEFF_LEN_INVALID_NOISE  180
#define CABLE_LEN_SEARCH_THRESH_INCR      16
#define MIN_CABLE_LEN_SEARCH_THRESH       36
#define LEN_SEARCH_COEFF_READAVG_LEN      0xf    /*   ((1 << 3) | 7)    */

#if defined(VTSS_PHY_OPT_VERIPHY_INT) && VTSS_PHY_OPT_VERIPHY_INT
extern bit VeriPHYIntFlag;
#endif

#define VTSS_VERIPHY_STATE_DONEBIT 0x80
#define DISCARD 0x80
#define VTSS_VERIPHY_STATE_IDLE 0x00
#define FFEinit4_7anomSearch   0
#define FFEinit4_7lengthSearch 1


typedef enum {
    VERIPHY_MODE_FULL,
    VERIPHY_MODE_ANOM_XPAIR,
    VERIPHY_MODE_ANOM_ONLY
} vtss_phy_veriphy_mode_t;

typedef enum {
    VERIPHY_STATE_IDLE              = VTSS_VERIPHY_STATE_IDLE,
    VERIPHY_STATE_INIT_0            = VTSS_VERIPHY_STATE_IDLE + 0x01,
    VERIPHY_STATE_INIT_1            = VTSS_VERIPHY_STATE_IDLE + 0x02,
    VERIPHY_STATE_INIT3_LINKDOWN    = VTSS_VERIPHY_STATE_IDLE + 0x03,
    VERIPHY_STATE_INIT4_LINKDOWN    = VTSS_VERIPHY_STATE_IDLE + 0x04,
    VERIPHY_STATE_INIT_ANOMSEARCH_0 = VTSS_VERIPHY_STATE_IDLE + 0x05,
    VERIPHY_STATE_INIT_ANOMSEARCH_1 = VTSS_VERIPHY_STATE_IDLE + 0x06,
    VERIPHY_STATE_ANOMSEARCH_0      = VTSS_VERIPHY_STATE_IDLE + 0x07,
    VERIPHY_STATE_ANOMSEARCH_1      = VTSS_VERIPHY_STATE_IDLE + 0x08,
    VERIPHY_STATE_ANOMSEARCH_2      = VTSS_VERIPHY_STATE_IDLE + 0x09,
    VERIPHY_STATE_ANOMSEARCH_3      = VTSS_VERIPHY_STATE_IDLE + 0x0a,
    VERIPHY_STATE_INIT_CABLELEN     = VTSS_VERIPHY_STATE_IDLE + 0x0b,
    VERIPHY_STATE_INIT_CABLELEN2    = VTSS_VERIPHY_STATE_IDLE + 0x0c,
    VERIPHY_STATE_GETCABLELEN_0     = VTSS_VERIPHY_STATE_IDLE + 0x0d,
    VERIPHY_STATE_GETCABLELEN_1     = VTSS_VERIPHY_STATE_IDLE + 0x0e,
    VERIPHY_STATE_PAIRSWAP          = VTSS_VERIPHY_STATE_IDLE + 0x0f,
    VERIPHY_STATE_HALT              = (VTSS_VERIPHY_STATE_DONEBIT | 0x10),  // 0x90
    VERIPHY_STATE_ABORT             = (VTSS_VERIPHY_STATE_DONEBIT | 0x20),  // 0xa0
    VERIPHY_STATE_FINISH            = (VTSS_VERIPHY_STATE_DONEBIT | 0x40)   // 0xc0
} vtss_veriphy_task_state_t;

#define VERIPHY_FLAGS_UNRELIABLEPTR    0x08
#define VERIPHY_FLAGS_GETCBLLENDONE    0x04
#define VERIPHY_FLAGS_VALID            0x02
#define VERIPHY_FLAGS_LINKUP           0x01

typedef struct {
    /* Variables common to all tasks */
    mepa_mtimer_t timeout;      /**< Absolute timeout */
    unsigned char task_state;   /**< Task State   */
    /* 0x00 ==> idle (but still serviced) */
    /* 0x01 - 0x7f ==> task-defined, */
    /* bit [7]: 1 ==> abort requested */

    /* VeriPHY public variables */
    unsigned char port;         /**< PHY on which VeriPHY is running/last run on */
    unsigned char flags;        /**< VeriPHY Flags to indicate Operating Modes */
    /* bit [7:6] = VeriPHY operating mode */
    /*        00 ==> full VeriPHY algorithm */
    /*        01 ==> anomaly-search only */
    /*        10 ==> anomaly-search w/o x-pair only */
    /*        11 ==> reserved */
    /* bit [5:4] = unreliablePtr (if bit [3] == 1) */
    /* bit [3]   = unreliablePtr presence flag */
    /* bit [2]   = getCableLength done flag */
    /* bit [1]   = valid */
    /* bit [0]   = linkup-mode */
    unsigned char flags2;       /**< VeriPHY Flags2,  more Operating Modes */
    /* bits [7:2] - reserved */
    /* bits [1:0] - ams_force_cu, ams_force_fi on entry (Spyder) */
    /* bits [1:0] - reserved, ActiPHY-enabled on entry (Luton) */
    /********************************/
    /* flg_phy is for 65nm products */
    unsigned char flg_phy;      /**< PHY Flags2,  more Operating Modes - 65nm only */
    /* bits [7:6] - ams_force_cu, ams_force_fi on entry */
    /* bit  [5]   - state of eee_1000tx_inhibit on entry */
    /* bits [4:0] - PHY */
    /********************************/
    unsigned long saveReg;      /**< TP[5.4:3], MII [28.2], MII[9.12:11], MII[0] - 21 bits */
    unsigned long tokenReg;     /**<  Token Ring Registers 29 bits */
    unsigned char stat[4];      /**< status for pairs A-D (0-3), 4-bit unsigned number */
    /** \brief VeriPHY status, which is an enumeration defined in include/vtss/api/phy.h */
    /** VTSS_VERIPHY_STATUS_OK      = 0,   Correctly terminated pair */
    /** VTSS_VERIPHY_STATUS_OPEN    = 1,   Open pair */
    /** VTSS_VERIPHY_STATUS_SHORT   = 2,   Short pair */
    /** VTSS_VERIPHY_STATUS_ABNORM  = 4,   Abnormal termination */
    /** VTSS_VERIPHY_STATUS_SHORT_A = 8,   Cross-pair short to pair A */
    /** VTSS_VERIPHY_STATUS_SHORT_B = 9,   Cross-pair short to pair B */
    /** VTSS_VERIPHY_STATUS_SHORT_C = 10,  Cross-pair short to pair C */
    /** VTSS_VERIPHY_STATUS_SHORT_D = 11,  Cross-pair short to pair D */
    /** VTSS_VERIPHY_STATUS_COUPL_A = 12,  Abnormal cross-pair coupling, pair A */
    /** VTSS_VERIPHY_STATUS_COUPL_B = 13,  Abnormal cross-pair coupling, pair B */
    /** VTSS_VERIPHY_STATUS_COUPL_C = 14,  Abnormal cross-pair coupling, pair C */
    /** VTSS_VERIPHY_STATUS_COUPL_D = 15,  Abnormal cross-pair coupling, pair D */
    /** VTSS_VERIPHY_STATUS_UNKNOWN = 16,  Unknown - VeriPhy never started ? */
    /** VTSS_VERIPHY_STATUS_RUNNING = 17   VeriPhy is still running - No result yet */
    /**<    most signiciant 4-bits represents prev. status */
    unsigned char loc[4];       /**< length/fault location for pairs A-D (0-3), 8-bit unsgn */

    /* VeriPHY private variables */
    signed char subchan;        /**< SubChannel - ie PHY physical Port A,B,C,D */
    signed char nc;             /**< Next Cancellor */
    unsigned char numCoeffs;    /**< Number of Coeffecients */
    unsigned char firstCoeff;   /**< First Coeff */
    short strength[4];          /**< fault strength for pairs A-D (0-3), 14-bit signed int. */
    short thresh[4];            /**< threshold (used in different places), 13-bit unsgn */
    short log2VGAx256;          /**< log2(VGA gain scalefactor)*256 (0 for link-down case) */
    signed char  signFlip;      /**< count used to improve location accuracy */
    long tr_raw0188;            /**< Token Ring RAW Data, only uses lower 3 bytes, wastes one byte */
} vtss_veriphy_task_t;

/******************************************************************************
 * \brief function used to prepare for VeriPHY to start
 * Purpose     : Prepare for VeriPHY
 * \param vtss_state [IN] Target Instance State reference.
 * \param port_no    [IN] Port in question
 * \param mode       [IN] VeriPHY mode as described below:
 *                0 ==> full VeriPHY algorithm
 *                1 ==> anomaly-search and x-pair (no cable length search)
 *                2 ==> anomaly-search  (no cable length search and no x-pair search)
 * \return Return code. VTSS_RC_OK if no errors.
 * Restrictions:
 * See also    :
 * Example     :
 * ************************************************************************ */
vtss_rc vtss_phy_veriphy_task_start(struct vtss_state_s *vtss_state, vtss_port_no_t port_no, u8 mode);

/******************************************************************************
 * \brief function used to Perform VeriPHY on a specific port
 * Purpose     : Peform VeriPHY on a specific port
 * \param vtss_state [IN] Target Instance State reference.
 * \param tsk        [IN] Pointer to the veriphy task that is running
 *               Results of operation is returned in structure pointed to
 *               by *result.
 * \return Return code. VTSS_RC_OK if no errors.
 * Remarks     :
 * Restrictions:
 * See also    :
 * Example     :
 * ************************************************************************ */
vtss_rc vtss_phy_veriphy(struct vtss_state_s *vtss_state, vtss_veriphy_task_t c51_idata *tsk);

#endif /* VTSS_PHY_OPT_VERIPHY */
#endif /* _VTSS_PHY_VERIPHY_H */
