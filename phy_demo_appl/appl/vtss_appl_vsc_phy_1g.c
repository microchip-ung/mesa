// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "vtss_api.h"   // For board initialization
#include "vtss_appl.h"  // For vtsss_board_t
#include "vtss_port_api.h"
#include "vtss_appl_cu_phy.h" // For board init
#include "vtss_macsec_api.h"
#include <netdb.h>  // For socket
#include <stdarg.h> // For va_list
#include <unistd.h>

#ifdef VTSS_FEATURE_PHY_TIMESTAMP
#include "vtss_phy_ts_api.h"
#include "vtss_appl_ts_demo.h"
#endif

#ifdef VTSS_FEATURE_MACSEC
#include "vtss_macsec_api.h"
#include <openssl/aes.h>
#include "vtss_appl_macsec_demo.h"
#endif

// byte order is handled by the API
#define ETHERTYPE_IEEE_IPV4       0x0800
#define ETHERTYPE_IEEE_ARP        0x0806
#define ETHERTYPE_IEEE_WOL        0x0842
#define ETHERTYPE_IEEE_VLAN_TAG   0x8100
#define ETHERTYPE_IEEE_IPV6       0x86DD
#define ETHERTYPE_IEEE_MPLS_UNI   0x8847
#define ETHERTYPE_IEEE_MPLS_MULTI 0x8848
#define ETHERTYPE_IEEE_JUMBO      0x8870
#define ETHERTYPE_IEEE_802_1_AG   0x8902
#define ETHERTYPE_IEEE_802_1_X    0x888E
#define ETHERTYPE_IEEE_802_1_AE   0x88E5
#define ETHERTYPE_IEEE_802_1_AH   0x88E7
#define ETHERTYPE_IEEE_PTP_1588   0x88F7
#define ETHERTYPE_IEEE_802_1_AD   0x88A8


#ifdef _INCLUDE_DEBUG_FILE_PRINT_
FILE   *fp;
#endif

/* ================================================================= *
 *  Board init.
 * ================================================================= */

#define MAX_BOARD_INSTANCES    (2)
/* Board specifics */
static vtss_appl_board_t board_table[MAX_BOARD_INSTANCES];

#ifdef _INCLUDE_DEBUG_TERM_PRINT_
static BOOL live_debug_enable = TRUE;
#endif

// Only ONE of these EVAL boards can be defined at one time
// These functions are in the header file vtss_appl_cu_phy.h
// These Definitions are set in the build_xxxxx_eval.bat file ..
// To compile, simply do:  bash build_tesla_eval.bat and
// the .bat file defines TESLA_EVAL_BOARD
#ifdef  _DEFINED_IN_BAT_FILE_
#undef  ATOM12_EVAL_BOARD
#undef  TESLA_EVAL_BOARD
#undef  ELISE_EVAL_BOARD
#undef  NANO_EVAL_BOARD
#undef  VIPER_EVAL_BOARD
#endif

#undef  EVAL_BOARD_1588_CAPABLE
#undef  EVAL_BOARD_MACSEC_CAPABLE

#define EXTENDED_LOOPBACK    // Enable SerDes Loopback
#undef  CHANGE_PHY_BASE_PORT // Eval Board has the Base Port Addr set to something other than 0

// Function defining the board
//
// In : Pointer to the board definition
void vtss_board_phy_init(vtss_appl_board_t *board)
{
    board->descr = "PHY"; // Description
    board->target = VTSS_TARGET_CU_PHY; // Target

// Please select which EVAL board you are using.
// The miim_read, miim_write,... fuctions are defined for the particular EVAL board you are using.
#if defined (ATOM12_EVAL_BOARD)
    board->board_init = atom12_board_init; // Pointer to function initializing the board
#endif
#if defined (TESLA_EVAL_BOARD)
    board->board_init = tesla_board_init; // Pointer to function initializing the board
//#define EVAL_BOARD_1588_CAPABLE
#endif
#if defined (ELISE_EVAL_BOARD)
    board->board_init = elise_board_init; // Pointer to function initializing the board
#endif
#if defined (NANO_EVAL_BOARD)
    board->board_init = nano_board_init; // Pointer to function initializing the board
#endif
#if defined (VIPER_EVAL_BOARD)
    board->board_init = viper_board_init; // Pointer to function initializing the board
//#define EVAL_BOARD_MACSEC_CAPABLE
//#define EVAL_BOARD_1588_CAPABLE
#endif
}

#if defined (VTSS_OPT_PHY_TIMESTAMP) && (defined (VIPER_EVAL_BOARD) || defined (TESLA_EVAL_BOARD))
#define EVAL_BOARD_1588_CAPABLE
#else
#undef EVAL_BOARD_1588_CAPABLE
#endif

#if defined (VTSS_FEATURE_MACSEC) && defined (VIPER_EVAL_BOARD)
#define EVAL_BOARD_MACSEC_CAPABLE
#else
#undef EVAL_BOARD_MACSEC_CAPABLE
#endif

#define VTSS_RC_TEST(X)           \
{                                 \
    if ((X) != VTSS_RC_OK) {      \
        printf("Failed: "#X"\n"); \
        abort();                  \
    }                             \
}

#define VTSS_RC_NTEST(X)          \
{                                 \
    if ((X) == VTSS_RC_OK) {      \
        printf("Failed: "#X"\n"); \
        abort();                  \
    }                             \
}

#define VTSS_INT_HEX_TEST(A, B)   \
{                                 \
    if (A != B) {                 \
        printf("Failed: "#A" != "#B" (0x%08x != 0x%08x)\n", (u32)A, (u32)B); \
        abort();                  \
    }                             \
}

/* ================================================================= *
 *  API lock/unlock functions - If the Application support threads
 *  the API must be protected via Mutexes
 * ================================================================= */
BOOL api_locked = FALSE;

// Function call by the API, when the API shall do mutex lock.
void vtss_callout_lock(const vtss_api_lock_t *const lock)
{
    // For testing we don't get a deadlock. The API must be unlocked before "locking"
    if (api_locked) {
        T_E("API lock problem");
    }
    api_locked = TRUE;
}

// Function call by the API, when the API shall do mutex unlock.
void vtss_callout_unlock(const vtss_api_lock_t *const lock)
{
    // For testing we don't get a deadlock. vtss_callout_lock must have been called before vtss_callout_unlock is called.
    if (!api_locked) {
        T_E("API unlock problem");
    }
    api_locked = FALSE;
}

/* ================================================================= *
 *  Debug trace
 * ================================================================= */
vtss_trace_conf_t vtss_appl_trace_conf = {
    //.level[0] = VTSS_TRACE_LEVEL_NONE
    .level[0] = VTSS_TRACE_LEVEL_ERROR
    //.level[0] = VTSS_TRACE_LEVEL_INFO
    //.level[0] = VTSS_TRACE_LEVEL_DEBUG
    //.level[0] = VTSS_TRACE_LEVEL_NOISE
};

// Trace callout function - This function is called for printing out debug information from the API
// Different levels of trace are support. The level are :
// 1) VTSS_TRACE_LEVEL_NONE   - No information from the API will be printed
// 2) VTSS_TRACE_LEVEL_ERROR  - Printout of T_E/VTSS_E trace. Error messages for malfunctioning API
// 3) VTSS_TRACE_LEVEL_WARNING- Printout of T_W/VTSS_W trace. Warning messages for unexpected API behavior.
// 4) VTSS_TRACE_LEVEL_INFO   - Printout of T_I/VTSS_I trace. Debug messages.
// 5) VTSS_TRACE_LEVEL_DEBUG  - Printout of T_D/VTSS_D trace. Even more debug messages.
// 6) VTSS_TRACE_LEVEL_NOISE  - Printout of T_N/VTSS_N trace. Even more debug messages.
void vtss_callout_trace_printf(const vtss_trace_layer_t layer,
                               const vtss_trace_group_t group,
                               const vtss_trace_level_t level,
                               const char *file,
                               const int line,
                               const char *function,
                               const char *format,
                               ...)
{
    va_list va;

#if 0
#ifdef _INCLUDE_DEBUG_FILE_PRINT_
// Output to a FILE pointed to by fp
        fprintf(fp,"Lvl:%s file:%s func:%s line:%d - ",
               level == VTSS_TRACE_LEVEL_ERROR ? "Error" :
               level == VTSS_TRACE_LEVEL_INFO ? "Info " :
               level == VTSS_TRACE_LEVEL_DEBUG ? "Debug" :
               level == VTSS_TRACE_LEVEL_NOISE ? "Noise" : "?????",
               file,
               function,
               line);

    va_start(va, format);
    vfprintf(fp, format, va);
    va_end(va);
    fprintf(fp,"\n");
#endif
#endif

#ifdef _INCLUDE_DEBUG_TERM_PRINT_
    if (live_debug_enable) {
        printf("Lvl:%s file:%s func:%s line:%d - ",
               level == VTSS_TRACE_LEVEL_ERROR ? "Error" :
               level == VTSS_TRACE_LEVEL_INFO ? "Info " :
               level == VTSS_TRACE_LEVEL_DEBUG ? "Debug" :
               level == VTSS_TRACE_LEVEL_NOISE ? "Noise" : "?????",
               file,
               function,
               line);

        va_start(va, format);
        vprintf(format, va);
        va_end(va);
        printf("\n");
    }
#endif
}

/* ================================================================= *
 *  // Example of how to use the loop back function
 * ================================================================= */
void phy_loop_back(void) {
    vtss_phy_loopback_t loopback;
    vtss_port_no_t port_no;

    // Setup the loopback
   for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS; port_no++) {
       // Getting the current loopback settings
       vtss_phy_loopback_get(NULL, port_no, &loopback);

       loopback.near_end_enable = FALSE;  // Set to TRUE for enabling Near End loopback
       loopback.far_end_enable  = FALSE;  // Set to TRUE for enabling Far End loopback
#ifdef EXTENDED_LOOPBACK
       loopback.connector_enable = FALSE;
       loopback.mac_serdes_input_enable = FALSE;
       loopback.mac_serdes_facility_enable = FALSE;
       loopback.mac_serdes_equipment_enable = FALSE;
       loopback.media_serdes_input_enable = FALSE;
       loopback.media_serdes_facility_enable = FALSE;
       loopback.media_serdes_equipment_enable = FALSE;
#endif

       // Setting the loopback settings
       vtss_phy_loopback_set(NULL, port_no, loopback);
   }

#if 0
    // Example of getting the current loopback settings
   for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS; port_no++) {
       vtss_phy_loopback_get(NULL, port_no, &loopback);
#ifdef EXTENDED_LOOPBACK
       T_I("loopback for port:%d near=%d, far= %d, connector=%d \n",
           port_no, loopback.near_end_enable, loopback.far_end_enable, loopback.connector_enable);
       T_I("loopback for port:%d mac_serd_input=%d, mac_serd_fac= %d, mac_serd_equip=%d \n",
           port_no, loopback.mac_serdes_input_enable, loopback.mac_serdes_facility_enable, loopback.mac_serdes_equipment_enable);
       T_I("loopback for port:%d media_serd_input=%d, media_serd_fac= %d, media_serd_equip=%d \n",
           port_no, loopback.media_serdes_input_enable, loopback.media_serdes_facility_enable, loopback.media_serdes_equipment_enable);
#else
       T_I("loopback for port:%d near=%d, far= %d \n", port_no, loopback.near_end_enable, loopback.far_end_enable);
#endif
   }
#endif

}

// Example of how to use the loop back function
// This function sets up FAR-END Loopback for the PHY port specified
void phy_single_port_loopback(vtss_port_no_t port_no, vtss_phy_loopback_t loopback) {

    // Setup the loopback
   if (port_no >= VTSS_PORT_NO_START && port_no < VTSS_PORT_NO_END) {
       // Example of getting the current loopback settings
       vtss_phy_loopback_get(NULL, port_no, &loopback);

       // Set to TRUE for enabling Far End loopback
       loopback.far_end_enable  = TRUE;

       // Save the Settings and Enable the desired loopback
       vtss_phy_loopback_set(NULL, port_no, loopback);

       // Example of getting the current loopback settings
       vtss_phy_loopback_get(NULL, port_no, &loopback);
       T_I("loopback for port:%d near=%d, far= %d, connector=%d \n",
           port_no, loopback.near_end_enable, loopback.far_end_enable, loopback.connector_enable);
       T_I("loopback for port:%d mac_serd_input=%d, mac_serd_fac= %d, mac_serd_equip=%d \n",
           port_no, loopback.mac_serdes_input_enable, loopback.mac_serdes_facility_enable, loopback.mac_serdes_equipment_enable);
       T_I("loopback for port:%d media_serd_input=%d, media_serd_fac= %d, media_serd_equip=%d \n",
           port_no, loopback.media_serdes_input_enable, loopback.media_serdes_facility_enable, loopback.media_serdes_equipment_enable);
   }
}

// Scan in a Valid Port Number that is within Range for this device
BOOL get_valid_port_no(vtss_port_no_t *  port_no, char port_no_str[])
{
        scanf("%s", &port_no_str[0]);
        *port_no = atoi(port_no_str);

        // Validate the Port Number, ensure it is in range
        if (*port_no >= VTSS_PORT_NO_START && *port_no < VTSS_PORT_NO_END) {
            return TRUE;
        }
        printf ("Error - Invalid Port Number: %d  Valid Range: %d - %d \n",
              *port_no, VTSS_PORT_NO_START, (VTSS_PORT_NO_END-1));

   return FALSE;
}

#if defined(VTSS_CHIP_10G_PHY)
BOOL port_is_10g_phy(vtss_port_no_t port_no)
{
    u16                 model;
    if (mmd_read(board->inst, port_no, 30, 0, &model) == VTSS_RC_OK) {
        if (model == 0x8484 ||
            model == 0x8487 ||
            model == 0x8488 ||
            model == 0x8489 ||
            model == 0x8490 ||
            model == 0x8491) {
            return TRUE;
        }
    }
    return FALSE;
}
#endif


void dump_port_status(vtss_port_status_t * p_status) {

    if (p_status->link) {
        printf("Link is UP!\n" );
    } else {
        printf("Link is DOWN!\n" );
    }

    switch (p_status->speed) {
    case VTSS_SPEED_UNDEFINED:
        printf("Speed Selection: Undefined - ");
        break;
    case VTSS_SPEED_10M:
        printf("Speed Selection: 10M - ");
        break;
    case VTSS_SPEED_100M:
        printf("Speed Selection: 100M - ");
        break;
    case VTSS_SPEED_1G:
        printf("Speed Selection: 1G - ");
        break;
    case VTSS_SPEED_2500M:
        printf("Speed Selection: 2.5G - ");
        break;
    case VTSS_SPEED_5G:
        printf("Speed Selection: 5G - ");
        break;
    case VTSS_SPEED_10G:
        printf("Speed Selection: 10G - ");
        break;
    case VTSS_SPEED_12G:
        printf("Speed Selection: 12G - ");
        break;
    default :
        printf("Speed Selection: Undefined: x%x -  ", p_status->speed);
        break;
    }

    // Example for PHY Duplex (non-auto neg.)
    if (p_status->fdx) {
        printf("Full Duplex Mode\n");
    } else {
        printf("Half Duplex Mode\n");
    }

    if (p_status->remote_fault) {
        printf("Remote Fault Signalled \n");
    }

    if (p_status->aneg_complete) {
        printf("Auto-Negotiation Complete \n");
    } else {
        printf("Auto-Negotiation NOT Complete \n");
    }

    if (p_status->unidirectional_ability) {
        printf("Unidirectional_ability  \n");
    } else {
        printf("NO Unidirectional_ability  \n");
    }

    if (p_status->mdi_cross) {
        printf("Auto-MDIX Crossover is performed  \n");
    } else {
        printf("Auto-MDIX Crossover is NOT performed  \n");
    }

    if (p_status->aneg.obey_pause) {
        printf("ANEG: This Port should Obey Pause  \n");
    }

    if (p_status->aneg.generate_pause) {
        printf("ANEG: Link Partner should Obey Pause \n");
    }
}

// Scan in a Valid Port Number that is within Range for this device
char * convert_veriphy_status(vtss_phy_veriphy_status_t status)
{
    switch(status) {
    case VTSS_VERIPHY_STATUS_OK:
        return(" OK ");
        break;
    case VTSS_VERIPHY_STATUS_OPEN:
        return(" OPEN ");
        break;
    case VTSS_VERIPHY_STATUS_SHORT:
        return(" SHORT ");
        break;
    case VTSS_VERIPHY_STATUS_ABNORM:
        return(" ABNORMAL ");
        break;
    case VTSS_VERIPHY_STATUS_SHORT_A:
        return(" SHORT_A ");
        break;
    case VTSS_VERIPHY_STATUS_SHORT_B:
        return(" SHORT_B ");
        break;
    case VTSS_VERIPHY_STATUS_SHORT_C:
        return(" SHORT_C ");
        break;
    case VTSS_VERIPHY_STATUS_SHORT_D:
        return(" SHORT_D ");
        break;
    case VTSS_VERIPHY_STATUS_COUPL_A:
        return(" COUPL_A ");
        break;
    case VTSS_VERIPHY_STATUS_COUPL_B:
        return(" COUPL_B ");
        break;
    case VTSS_VERIPHY_STATUS_COUPL_C:
        return(" COUPL_C ");
        break;
    case VTSS_VERIPHY_STATUS_COUPL_D:
        return(" COUPL_D ");
        break;
    case VTSS_VERIPHY_STATUS_UNKNOWN:
        return(" UNKNOWN ");
        break;
    default:
        return(" UNHANDLED ");
        break;
    }
}


char * get_mac_if_name( char * value_str, vtss_port_interface_t  * mac_if)
{
    char * p_mac_if_name = NULL;

    if ((strcmp(value_str, "rgmii")  == 0) || (strcmp(value_str, "RGMII")  == 0)) {
       *mac_if = VTSS_PORT_INTERFACE_RGMII;
        p_mac_if_name = "RGMII";
    } else if ((strcmp(value_str, "gmii")  == 0) || (strcmp(value_str, "GMII")  == 0)) {
       *mac_if = VTSS_PORT_INTERFACE_GMII;
        p_mac_if_name = "GMII";
    } else if ((strcmp(value_str, "sgmii")  == 0) || (strcmp(value_str, "SGMII")  == 0)) {
       *mac_if = VTSS_PORT_INTERFACE_SGMII;
        p_mac_if_name = "SGMII";
    } else if ((strcmp(value_str, "qsgmii")  == 0) || (strcmp(value_str, "QSGMII")  == 0)) {
       *mac_if = VTSS_PORT_INTERFACE_QSGMII;
        p_mac_if_name = "QSGMII";
    }
    return (p_mac_if_name);
}

char * get_mac_if_name_by_mac_id( vtss_port_interface_t  mac_if)
{
    char * p_mac_if_name = NULL;

    if (mac_if == VTSS_PORT_INTERFACE_RGMII) {
        p_mac_if_name = "RGMII";
    } else if (mac_if == VTSS_PORT_INTERFACE_GMII) {
        p_mac_if_name = "GMII";
    } else if (mac_if == VTSS_PORT_INTERFACE_SGMII) {
        p_mac_if_name = "SGMII";
    } else if (mac_if == VTSS_PORT_INTERFACE_QSGMII) {
        p_mac_if_name = "QSGMII";
    }
    return (p_mac_if_name);
}

char * get_media_if_name( char * value_str, vtss_phy_media_interface_t * media_if)
{
    char * p_media_if_name = NULL;

    if (strcmp(value_str, "cu")  == 0) {
       *media_if = VTSS_PHY_MEDIA_IF_CU;
        p_media_if_name = "COPPER_I/F";
    } else if (strcmp(value_str, "sfppass")  == 0) {
       *media_if= VTSS_PHY_MEDIA_IF_SFP_PASSTHRU;
        p_media_if_name = "SFP_PASSTHRU_I/F";
    } else if (strcmp(value_str, "fi1000bx")  == 0) {
       *media_if = VTSS_PHY_MEDIA_IF_FI_1000BX;
        p_media_if_name = "FI_1000BX_I/F";
    } else if (strcmp(value_str, "fi100fx")  == 0) {
       *media_if = VTSS_PHY_MEDIA_IF_FI_100FX;
        p_media_if_name = "FI_100FX_I/F";
    } else if (strcmp(value_str, "amscupass")  == 0) {
       *media_if = VTSS_PHY_MEDIA_IF_AMS_CU_PASSTHRU;
        p_media_if_name = "AMS_CU_PASSTHRU_I/F";
    } else if (strcmp(value_str, "amsfipass")  == 0) {
       *media_if = VTSS_PHY_MEDIA_IF_AMS_FI_PASSTHRU;
        p_media_if_name = "AMS_FI_PASSTHRU_I/F";
    } else if (strcmp(value_str, "amscu1000bx")  == 0) {
       *media_if = VTSS_PHY_MEDIA_IF_AMS_CU_1000BX;
        p_media_if_name = "AMS_CU_1000BX_I/F";
    } else if (strcmp(value_str, "amsfi1000bx")  == 0) {
       *media_if = VTSS_PHY_MEDIA_IF_AMS_FI_1000BX;
        p_media_if_name = "AMS_FI_1000BX_I/F";
    } else if (strcmp(value_str, "amscu100fx")  == 0) {
       *media_if = VTSS_PHY_MEDIA_IF_AMS_CU_100FX;
        p_media_if_name = "AMS_CU_100FX_I/F";
    } else if (strcmp(value_str, "amsfi100fx")  == 0) {
       *media_if = VTSS_PHY_MEDIA_IF_AMS_FI_100FX;
        p_media_if_name = "AMS_FI_100FX_I/F";
    }

    return (p_media_if_name);
}

char * get_media_if_name_by_media_id( vtss_phy_media_interface_t media_if)
{
    char * p_media_if_name = NULL;

    if (media_if == VTSS_PHY_MEDIA_IF_CU) {
        p_media_if_name = "COPPER_I/F";
    } else if (media_if == VTSS_PHY_MEDIA_IF_SFP_PASSTHRU) {
        p_media_if_name = "SFP_PASSTHRU_I/F";
    } else if (media_if == VTSS_PHY_MEDIA_IF_FI_1000BX) {
        p_media_if_name = "FI_1000BX_I/F";
    } else if (media_if == VTSS_PHY_MEDIA_IF_FI_100FX) {
        p_media_if_name = "FI_100FX_I/F";
    } else if (media_if == VTSS_PHY_MEDIA_IF_AMS_CU_PASSTHRU) {
        p_media_if_name = "AMS_CU_PASSTHRU_I/F";
    } else if (media_if == VTSS_PHY_MEDIA_IF_AMS_FI_PASSTHRU) {
        p_media_if_name = "AMS_FI_PASSTHRU_I/F";
    } else if (media_if == VTSS_PHY_MEDIA_IF_AMS_CU_1000BX) {
        p_media_if_name = "AMS_CU_1000BX_I/F";
    } else if (media_if == VTSS_PHY_MEDIA_IF_AMS_FI_1000BX) {
        p_media_if_name = "AMS_FI_1000BX_I/F";
    } else if (media_if == VTSS_PHY_MEDIA_IF_AMS_CU_100FX) {
        p_media_if_name = "AMS_CU_100FX_I/F";
    } else if (media_if == VTSS_PHY_MEDIA_IF_AMS_FI_100FX) {
        p_media_if_name = "AMS_FI_100FX_I/F";
    }

    return (p_media_if_name);
}

void phy_process_event_poll(vtss_port_no_t  port_no, vtss_phy_event_t  event)
{
    if (event & VTSS_PHY_LINK_LOS_EV) {
        printf("Event: VTSS_PHY_LINK_LOS_EV \n");
    }
    if (event & VTSS_PHY_LINK_FFAIL_EV) {
        printf("Event: VTSS_PHY_LINK_FFAIL_EV \n");
    }
    if (event & VTSS_PHY_LINK_AMS_EV) {
        printf("Event: VTSS_PHY_LINK_AMS_EV \n");
    }
    if (event & VTSS_PHY_LINK_SPEED_STATE_CHANGE_EV) {
        printf("Event: VTSS_PHY_LINK_SPEED_STATE_CHANGE_EV \n");
    }
    if (event & VTSS_PHY_LINK_FDX_STATE_CHANGE_EV) {
        printf("Event: VTSS_PHY_LINK_FDX_STATE_CHANGE_EV \n");
    }
    if (event & VTSS_PHY_LINK_AUTO_NEG_ERROR_EV) {
        printf("Event: VTSS_PHY_LINK_AUTO_NEG_ERROR_EV \n");
    }
    if (event & VTSS_PHY_LINK_AUTO_NEG_COMPLETE_EV) {
        printf("Event: VTSS_PHY_LINK_AUTO_NEG_COMPLETE_EV \n");
    }
    if (event & VTSS_PHY_LINK_INLINE_POW_DEV_DETECT_EV) {
        printf("Event: VTSS_PHY_LINK_INLINE_POW_DEV_DETECT_EV \n");
    }
    if (event & VTSS_PHY_LINK_SYMBOL_ERR_INT_EV) {
        printf("Event: VTSS_PHY_LINK_SYMBOL_ERR_INT_EV \n");
    }
    if (event & VTSS_PHY_LINK_TX_FIFO_OVERFLOW_INT_EV) {
        printf("Event: VTSS_PHY_LINK_TX_FIFO_OVERFLOW_INT_EV \n");
    }
    if (event & VTSS_PHY_LINK_RX_FIFO_OVERFLOW_INT_EV) {
        printf("Event: VTSS_PHY_LINK_RX_FIFO_OVERFLOW_INT_EV \n");
    }
    if (event & VTSS_PHY_LINK_FALSE_CARRIER_INT_EV) {
        printf("Event: VTSS_PHY_LINK_FALSE_CARRIER_INT_EV \n");
    }
    if (event & VTSS_PHY_LINK_LINK_SPEED_DS_DETECT_EV) {
        printf("Event: VTSS_PHY_LINK_LINK_SPEED_DS_DETECT_EV \n");
    }
    if (event & VTSS_PHY_LINK_MASTER_SLAVE_RES_ERR_EV) {
        printf("Event: VTSS_PHY_LINK_MASTER_SLAVE_RES_ERR_EV \n");
    }
    if (event & VTSS_PHY_LINK_RX_ER_INT_EV) {
        printf("Event: VTSS_PHY_LINK_RX_ER_INT_EV \n");
    }
    if (event & VTSS_PHY_LINK_EXTENDED_REG_INT_EV) {
        printf("Event: VTSS_PHY_LINK_EXTENDED_REG_INT_EV \n");
    }
    if (event & VTSS_PHY_LINK_WAKE_ON_LAN_INT_EV) {
        printf("Event: VTSS_PHY_LINK_WAKE_ON_LAN_INT_EV \n");
    }
    if (event & VTSS_PHY_LINK_EXT_EEE_WAKE_ERR_EV) {
        printf("Event: VTSS_PHY_LINK_EXT_EEE_WAKE_ERR_EV  \n");
    }
    if (event & VTSS_PHY_LINK_EXT_EEE_WAIT_TS_EV) {
        printf("Event: VTSS_PHY_LINK_EXT_EEE_WAIT_TS_EV   \n");
    }
    if (event & VTSS_PHY_LINK_EXT_EEE_WAIT_RX_TQ_EV) {
        printf("Event: VTSS_PHY_LINK_EXT_EEE_WAIT_RX_TQ_EV\n");
    }
    if (event & VTSS_PHY_LINK_EXT_EEE_LINKFAIL_EV) {
        printf("Event: VTSS_PHY_LINK_EXT_EEE_LINKFAIL_EV  \n");
    }
    if (event & VTSS_PHY_LINK_EXT_RR_SW_COMPL_EV ) {
        printf("Event: VTSS_PHY_LINK_EXT_RR_SW_COMPL_EV   \n");
    }
    if (event & VTSS_PHY_LINK_EXT_MACSEC_HOST_MAC_EV) {
        printf("Event: VTSS_PHY_LINK_EXT_MACSEC_HOST_MAC_EV  \n");
    }
    if (event & VTSS_PHY_LINK_EXT_MACSEC_LINE_MAC_EV) {
        printf("Event: VTSS_PHY_LINK_EXT_MACSEC_LINE_MAC_EV  \n");
    }
    if (event & VTSS_PHY_LINK_EXT_MACSEC_FC_BUFF_EV ) {
        printf("Event: VTSS_PHY_LINK_EXT_MACSEC_FC_BUFF_EV   \n");
    }
    if (event & VTSS_PHY_LINK_EXT_MACSEC_INGRESS_EV ) {
        printf("Event: VTSS_PHY_LINK_EXT_MACSEC_INGRESS_EV   \n");
    }
    if (event & VTSS_PHY_LINK_EXT_MACSEC_EGRESS_EV ) {
        printf("Event: VTSS_PHY_LINK_EXT_MACSEC_EGRESS_EV   \n");
    }
    if (event & VTSS_PHY_LINK_EXT_MEM_INT_RING_EV) {
        printf("Event: VTSS_PHY_LINK_EXT_MEM_INT_RING_EV  \n");
    }
}


void phy_ams_setup(vtss_appl_board_t * board) {
    vtss_port_no_t          port_no;
    vtss_phy_conf_t         phy;
    vtss_phy_reset_conf_t   phy_reset;
    vtss_init_conf_t        init_conf;
    vtss_port_interface_t   mac_if;
    vtss_phy_media_interface_t media_if;
    u16 value;
    int addr;
    vtss_rc                 rc;

    memset (&phy, 0, sizeof(vtss_phy_conf_t));
    memset (&phy_reset, 0, sizeof(vtss_phy_reset_conf_t));
    // Example for PHY moode
    //phy.mode = VTSS_PHY_MODE_FORCED;
    phy.mode = VTSS_PHY_MODE_ANEG;

    // Example for PHY speed support for auto-neg
    phy.aneg.speed_10m_hdx = 1;
    phy.aneg.speed_10m_fdx = 1;
    phy.aneg.speed_100m_hdx = 1;
    phy.aneg.speed_100m_fdx = 1;
    phy.aneg.speed_1g_hdx = 0;
    phy.aneg.speed_1g_fdx = 1;

    // Example for PHY flow control settings
    phy.aneg.symmetric_pause =  1;

    // Example for PHY speed (non-auto neg.)
    //phy.forced.speed = VTSS_SPEED_10M;
    phy.forced.speed = VTSS_SPEED_100M;
    //phy.forced.speed = VTSS_SPEED_1G;
    phy.forced.fdx = 1;
    phy.mdi = VTSS_PHY_MDIX_AUTO; // always enable auto detection of crossed/non-crossed cables

    // Do PHY port reset + Port setup
    printf ("//Comment: PHY port reset\n");
    mac_if = VTSS_PORT_INTERFACE_SGMII;
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS; port_no++) {
        if (port_no == 0) {
           phy.mode = VTSS_PHY_MODE_ANEG;
           media_if = VTSS_PHY_MEDIA_IF_AMS_FI_100FX;
           printf("Mode: ANEG, Media_if = VTSS_PHY_MEDIA_IF_AMS_FI_100FX for port: %d \n", port_no);
        } else if (port_no == 1) {
           phy.mode = VTSS_PHY_MODE_FORCED;
           phy.forced.speed = VTSS_SPEED_10M;
           media_if = VTSS_PHY_MEDIA_IF_CU;
           printf("Mode: Forced, Media_if = VTSS_PHY_MEDIA_IF_CU for port: %d \n", port_no);
        } else if (port_no == 2) {
           phy.mode = VTSS_PHY_MODE_ANEG;
           media_if = VTSS_PHY_MEDIA_IF_CU;
           printf("Mode: ANEG, Media_if = VTSS_PHY_MEDIA_IF_CU for port: %d \n", port_no);
           continue;
        } else if (port_no == 3) {
           phy.mode = VTSS_PHY_MODE_ANEG;
           media_if = VTSS_PHY_MEDIA_IF_FI_100FX;
           printf("Mode: ANEG, Media_if = VTSS_PHY_MEDIA_IF_FI_100FX for port: %d \n", port_no);
        } else {
           phy.mode = VTSS_PHY_MODE_ANEG;
           media_if = VTSS_PHY_MEDIA_IF_CU;
           printf("Mode: ANEG, Media_if = VTSS_PHY_MEDIA_IF_CU for port: %d \n", port_no);
        }

        addr=19;
        value = 0;
        miim_write(board->inst, port_no, 31, 0x1); /* Setup Page, Ext1 */
        miim_write(board->inst, port_no, addr, 0x0);
        miim_read(board->inst, port_no, addr, &value);
        miim_write(board->inst, port_no, 31, 0x0); /* Setup Page, Std */
        printf("\nSetting SigDet, Writing Addr:%02dE1 : Value:0x%04X \n", addr, value);

        phy_reset.mac_if = mac_if;             // Set the port MAC interface
        phy_reset.media_if = media_if;         // Set media interface
        vtss_phy_reset(board->inst, port_no, &phy_reset); // Do port reset
        vtss_phy_conf_set(board->inst, port_no, &phy);

        if (phy.mode == VTSS_PHY_MODE_ANEG) {
            printf ("//Default Setup: PHY Mode: ANEG Enabled for port: %d \n", port_no );
        } else if (phy.mode == VTSS_PHY_MODE_FORCED) {
            printf ("//Default Setup: PHY Mode: FORCED Speed Enabled for port: %d \n", port_no );
        } else if (phy.mode == VTSS_PHY_MODE_POWER_DOWN) {
            printf ("//Default Setup: PHY Mode: PHY Power Down Enabled for port: %d \n", port_no );
        } else {
            printf ("//Default Setup: PHY Mode: Unknown for port: %d \n", port_no );
        }
    }
}

void phy_ams_test(vtss_appl_board_t * board) {
    vtss_port_no_t     port_no;
    vtss_port_status_t status;
    vtss_phy_event_t   ev_mask;
    vtss_phy_event_t   event;
    BOOL               enable = TRUE;
    u16                value = 0;
    u16                reg0 = 0;
    u16                reg1 = 0;
    int                addr = 0;
    vtss_rc            rc;

    ev_mask = 0xffff;
    enable = TRUE;
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS; port_no++) {
        printf("Port %d - Setting/Enabling Event Mask: 0x%x  \n", port_no, ev_mask);
        rc = vtss_phy_event_enable_set(board->inst, port_no, ev_mask, enable);

        rc = vtss_phy_event_poll(board->inst, port_no, &event);
        if (rc == VTSS_RC_OK) {
            printf("Port %d - Getting Events: 0x%x  \n", port_no, event);
            phy_process_event_poll(port_no, event);
        } else {
            printf("Port %d - Getting Events: FAILURE!  \n", port_no);
        }
    }

    port_no = 0;
    addr=0;
    miim_read(board->inst, port_no, addr, &reg0);
    port_no = 0;
    addr=1;
    miim_read(board->inst, port_no, addr, &reg1);
    printf("Port: %d, Reg0 Value: 0x%x   Reg1 Value: 0x%x\n", port_no, reg0, reg1);


    port_no = 0;
    addr=19;
    value = 0x0000;
    miim_write(board->inst, port_no, 31, 0x1); /* Setup Page, Ext1 to read 19E1*/
    miim_write(board->inst, port_no, addr, value);
    value = 0;
    miim_read(board->inst, port_no, addr, &value);
    miim_write(board->inst, port_no, 31, 0x0); /* Setup Page, Std */
    printf("Test#1: AMS Port %d SigDet=Lo, (SFP-Active), Writing Addr:%02dE1 : Value:0x%x   -----  Getting Status \n", port_no, addr, value);
    printf("Test#1: Port 0 - AMS;  Port 0 and Port 3 should be Link UP \n");
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS; port_no++) {
        vtss_phy_status_get(board->inst, port_no, &status);
        if (status.link_down == 0) {
            printf("Link UP!  (status=%d) \n", status.link_down);
        } else if (status.link_down == 1) {
            printf("Link DOWN!  (status=%d) \n", status.link_down);
        } else {
            printf("Link Status Unknown!  (status=%d) \n", status.link_down);
        }
    }

    port_no = 0;
    addr=0;
    miim_read(board->inst, port_no, addr, &reg0);
    port_no = 0;
    addr=1;
    miim_read(board->inst, port_no, addr, &reg1);
    printf("Test#1: ###### Port: %d, Reg0 Value: 0x%x   Reg1 Value: 0x%x\n", port_no, reg0, reg1);

    printf("\n\n");
    port_no = 0;
    addr=19;
    value = 0x0001;
    miim_write(board->inst, port_no, 31, 0x1); /* Setup Page, Ext1 */
    miim_write(board->inst, port_no, addr, value);
    value = 0;
    miim_read(board->inst, port_no, addr, &value);
    miim_write(board->inst, port_no, 31, 0x0); /* Setup Page, Std */
    printf("Test#2: AMS Port %d SigDet=Hi, (Copper-Active), Writing Addr:%02dE1 : Value:0x%x   -----  Getting Status \n", port_no, addr, value);
    printf("Test#2: Port 0 - AMS;  Port 0 and Port 1 should be Link UP \n");

// Order of Events as they come in
//Event Detected: VTSS_PHY_LINK_LOS_EV
//Event Detected: VTSS_PHY_LINK_AMS_EV
//Event Detected: VTSS_PHY_LINK_LOS_EV
//Event Detected: VTSS_PHY_LINK_SPEED_STATE_CHANGE_EV
//Event Detected: VTSS_PHY_LINK_FDX_STATE_CHANGE_EV
//Event Detected: VTSS_PHY_LINK_AUTO_NEG_COMPLETE_EV

    int max_loops = 100; // 100msecs per loop
    int loops = 0;
    BOOL ams_rcvd = FALSE;
    while ( loops < max_loops )
    {
        port_no = 0;
        event = 0;
        rc = vtss_phy_event_poll(board->inst, port_no, &event);
        if (rc == VTSS_RC_OK) {
            if (event != 0) {
                printf("Port %d - Getting Events: 0x%x  \n", port_no, event);
                phy_process_event_poll(port_no, event);
            }
        } else {
            printf("Port %d - Getting Events: FAILURE!  \n", port_no);
        }

        if (ams_rcvd) {
            if (event & VTSS_PHY_LINK_SPEED_STATE_CHANGE_EV) {
                printf("Port %d - LoopCnt: %d \n", port_no, loops);
                break;
            }
        }

        if (event & VTSS_PHY_LINK_AMS_EV) {
            ams_rcvd = TRUE;
            printf("Port %d - LoopCnt: %d \n", port_no, loops);
            if (event & VTSS_PHY_LINK_SPEED_STATE_CHANGE_EV) {
                break;
            }
        }

        usleep(100000); // Sleep for 100000 usec or 100 msec
        loops++;
    }

    usleep(100000); // Sleep for 100000 usec or 100 msec
    port_no = 0;
    addr=0;
    miim_read(board->inst, port_no, addr, &reg0);
    port_no = 0;
    addr=1;
    miim_read(board->inst, port_no, addr, &reg1);
    printf("Test#2: ###### Port: %d, Reg0 Value: 0x%x   Reg1 Value: 0x%x\n", port_no, reg0, reg1);


    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS; port_no++) {
        vtss_phy_status_get(board->inst, port_no, &status);
        if (status.link_down == 0) {
            printf("Link UP!  (status=%d) \n", status.link_down);
        } else if (status.link_down == 1) {
            printf("Link DOWN!  (status=%d) \n", status.link_down);
        } else {
            printf("Link Status Unknown!  (status=%d) \n", status.link_down);
        }
    }

    printf("\n\n");
    port_no = 0;
    addr=19;
    value = 0;
    miim_write(board->inst, port_no, 31, 0x1); /* Setup Page, Ext1 */
    miim_write(board->inst, port_no, addr, value);
    value = 0;
    miim_read(board->inst, port_no, addr, &value);
    miim_write(board->inst, port_no, 31, 0x0); /* Setup Page, Std */
    printf("Test#3: AMS Port %d SigDet=Lo, (SFP-Active), Writing Addr:%02dE1 : Value:0x%x   -----  Getting Status \n", port_no, addr, value);
    printf("Test#3: Port 0 - AMS;  Port 0 and Port 3 should be Link UP \n");

    loops = 0;
    ams_rcvd = FALSE;
    while ( loops < max_loops )
    {
        port_no = 0;
        event = 0;
        rc = vtss_phy_event_poll(board->inst, port_no, &event);
        if (rc == VTSS_RC_OK) {
            if (event != 0) {
                printf("Port %d - Getting Events: 0x%x  \n", port_no, event);
                phy_process_event_poll(port_no, event);
            }
        } else {
            printf("Port %d - Getting Events: FAILURE!  \n", port_no);
        }

        if (ams_rcvd) {
            if (event & VTSS_PHY_LINK_SPEED_STATE_CHANGE_EV) {
                printf("Port %d - LoopCnt: %d \n", port_no, loops);
                break;
            }
        }

        if (event & VTSS_PHY_LINK_AMS_EV) {
            ams_rcvd = TRUE;
            printf("Port %d - LoopCnt: %d \n", port_no, loops);
            if (event & VTSS_PHY_LINK_SPEED_STATE_CHANGE_EV) {
                break;
            }
        }

        usleep(100000); // Sleep for 100000 usec or 100 msec
        loops++;
    }

    usleep(100000); // Sleep for 100000 usec or 100 msec
    port_no = 0;
    addr=0;
    miim_read(board->inst, port_no, addr, &reg0);
    port_no = 0;
    addr=1;
    miim_read(board->inst, port_no, addr, &reg1);
    printf("Test#3: ###### Port: %d, Reg0 Value: 0x%x   Reg1 Value: 0x%x\n", port_no, reg0, reg1);

    printf("Port 0 - AMS;  SigDet = 0, SFP Active  \n");
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS; port_no++) {
        vtss_phy_status_get(board->inst, port_no, &status);
        if (status.link_down == 0) {
            printf("Link UP!  (status=%d) \n", status.link_down);
        } else if (status.link_down == 1) {
            printf("Link DOWN!  (status=%d) \n", status.link_down);
        } else {
            printf("Link Status Unknown!  (status=%d) \n", status.link_down);
        }
    }
}

void disp_6g_serdes_reg(void) {
            printf (" Select the MAC SerDes MACRO Register:  \n");
            printf (" PLL5G  - Controlled on Per Port Basis:\n");
            printf (" SERDES1G_CSR_REG_PLL5G_CFG0  = 0x06, SERDES1G_CSR_REG_PLL5G_CFG1     = 0x07,\n");
            printf (" SERDES1G_CSR_REG_PLL5G_CFG2  = 0x08, SERDES1G_CSR_REG_PLL5G_CFG3     = 0x09,\n");
            printf (" SERDES1G_CSR_REG_PLL5G_CFG4  = 0x0a, SERDES1G_CSR_REG_PLL5G_CFG5     = 0x0b,\n");
            printf (" SERDES1G_CSR_REG_PLL5G_STAT0 = 0x0c, SERDES1G_CSR_REG_PLL5G_STAT1    = 0x0d,\n");
            printf (" SERDES1G_CSR_REG_RCOMP_CFG0  = 0x0e, SERDES1G_CSR_REG_RCOMP_STATUS   = 0x0f,\n");
            printf (" SERDES1G_CSR_REG_SYNCE_CFG0  = 0x10 \n\n");
            printf (" MAC SIDE - 1G SERDES  - Controlled on Per Port Basis:\n");
            printf (" SERDES1G_CSR_REG_DESER_CFG   = 0x12, SERDES1G_CSR_REG_INPUTBUFF_CFG  = 0x13,\n");
            printf (" SERDES1G_CSR_REG_OUTBUFF_CFG = 0x14, SERDES1G_CSR_REG_SERIALIZER_CFG = 0x15,\n");
            printf (" SERDES1G_CSR_REG_COMMON_CFG  = 0x16, SERDES1G_CSR_REG_PLL_CFG        = 0x17,\n");
            printf (" SERDES1G_CSR_REG_PLL_STATUS  = 0x18, SERDES1G_CSR_REG_DFT_CFG0       = 0x19,\n");
            printf (" SERDES1G_CSR_REG_DFT_CFG1    = 0x1a, SERDES1G_CSR_REG_DFT_CFG2       = 0x1b,\n");
            printf (" SERDES1G_CSR_REG_TESTPAT_CFG = 0x1c, SERDES1G_CSR_REG_RCPLL_BIST_CFG = 0x1d,\n");
            printf (" SERDES1G_CSR_REG_MISC_CFG    = 0x1e, SERDES1G_CSR_REG_DFT_STATUS     = 0x1f \n\n");
            printf (" 6G SERDES - Controlled on Per PHY Basis:\n");
            printf (" SERDES6G_CSR_REG_DES_CFG        = 0x21, SERDES6G_CSR_REG_IB_CFG0     = 0x22,\n");
            printf (" SERDES6G_CSR_REG_IB_CFG1        = 0x23, SERDES6G_CSR_REG_IB_CFG2     = 0x24,\n");
            printf (" SERDES6G_CSR_REG_IB_CFG3        = 0x25, SERDES6G_CSR_REG_IB_CFG4     = 0x26,\n");
            printf (" SERDES6G_CSR_REG_IB_CFG5        = 0x27, SERDES6G_CSR_REG_OB_CFG      = 0x28,\n");
            printf (" SERDES6G_CSR_REG_OB_CFG1        = 0x29, SERDES6G_CSR_REG_SER_CFG     = 0x2a,\n");
            printf (" SERDES6G_CSR_REG_PLL_CFG        = 0x2b, SERDES6G_CSR_REG_CMN_CFG     = 0x2c,\n");
            printf (" SERDES6G_CSR_REG_GP_CFG         = 0x2e, SERDES6G_CSR_REG_IB_STAT0    = 0x2f,\n");
            printf (" SERDES6G_CSR_REG_IB_STAT1       = 0x30, SERDES6G_CSR_REG_PLL_STAT    = 0x31,\n");
            printf (" SERDES6G_CSR_REG_ACJTAG         = 0x32, SERDES6G_CSR_REG_REV_ID      = 0x33,\n");
            printf (" SERDES6G_CSR_REG_DIG_CFG        = 0x34, SERDES6G_CSR_REG_DFT_CFG0    = 0x35,\n");
            printf (" SERDES6G_CSR_REG_DFT_CFG1       = 0x36, SERDES6G_CSR_REG_DFT_CFG2    = 0x37,\n");
            printf (" SERDES6G_CSR_REG_TSTPAT_CFG0    = 0x38, SERDES6G_CSR_REG_TSTPAT_CFG1 = 0x39,\n");
            printf (" SERDES6G_CSR_REG_RCPLL_BIST_CFG = 0x3a, SERDES6G_CSR_REG_MISC_CFG    = 0x3b,\n");
            printf (" SERDES6G_CSR_REG_OB_ANEG_CFG    = 0x3c, SERDES6G_CSR_REG_DFT_STAT0   = 0x3d,\n");
            printf (" SERDES6G_CSR_REG_DFT_STAT1      = 0x3e, SERDES6G_CSR_REG_MCB_ADDR_CFG = 0x3f\n\n");
}



void get_phy_default_config(vtss_phy_conf_t  *phy) {

    // Example for PHY mode; Note: Last entry is one selected
    //phy->mode = VTSS_PHY_MODE_FORCED;   // VTSS_PHY_MODE_ANEG; VTSS_PHY_MODE_FORCED
    phy->mode = VTSS_PHY_MODE_ANEG;   // VTSS_PHY_MODE_ANEG; VTSS_PHY_MODE_FORCED

    // Example for PHY speed support for auto-neg
    phy->aneg.speed_10m_hdx = 1;
    phy->aneg.speed_10m_fdx = 1;
    phy->aneg.speed_100m_hdx = 1;
    phy->aneg.speed_100m_fdx = 1;
    phy->aneg.speed_1g_hdx = 0;
    phy->aneg.speed_1g_fdx = 1;

    // Example for PHY flow control settings
    phy->aneg.symmetric_pause =  0;
    phy->aneg.tx_remote_fault =  0;

    // Example for PHY speed (non-auto neg.) Note: Last Entry is one selected
    //phy->forced.speed = VTSS_SPEED_10M;    // VTSS_SPEED_10M; VTSS_SPEED_100M; VTSS_SPEED_1G;
    //phy->forced.speed = VTSS_SPEED_100M;   // VTSS_SPEED_10M; VTSS_SPEED_100M; VTSS_SPEED_1G;
    phy->forced.speed = VTSS_SPEED_1G;   // VTSS_SPEED_10M; VTSS_SPEED_100M; VTSS_SPEED_1G;
    phy->forced.fdx = 1;

    phy->mdi = VTSS_PHY_MDIX_AUTO; // always enable auto detection of crossed/non-crossed cables
    //phy->force_ams_sel = VTSS_PHY_MEDIA_FORCE_AMS_SEL_SERDES; // FORCE PHY AMS Media Selection to always be SERDES
    //phy->force_ams_sel = VTSS_PHY_MEDIA_FORCE_AMS_SEL_COPPER; // FORCE PHY AMS Media Selection to always be COPPER
    phy->force_ams_sel = VTSS_PHY_MEDIA_FORCE_AMS_SEL_NORMAL; // Let PHY Determine Media Selection based on Link Status

    //phy->skip_coma = TRUE;  // Skip COMA Mode config in vtss_phy_post_reset
    phy->skip_coma = FALSE; // COMA Mode config = Default, Apply Default COMA Mode in vtss_phy_post_reset

    //phy->flf = VTSS_PHY_FAST_LINK_FAIL_DISABLE;
    phy->flf = VTSS_PHY_FAST_LINK_FAIL_ENABLE;

    //phy->.sigdet = VTSS_PHY_SIGDET_POLARITY_ACT_LOW;
    phy->sigdet = VTSS_PHY_SIGDET_POLARITY_ACT_HIGH;

    //phy->unidir = VTSS_PHY_UNIDIRECTIONAL_ENABLE;
    phy->unidir = VTSS_PHY_UNIDIRECTIONAL_DISABLE;

/*  Setup the MAC Interface PCS Parameters */
    phy->mac_if_pcs.disable = 0;
    phy->mac_if_pcs.restart = 0;
    phy->mac_if_pcs.pd_enable = 1;
    phy->mac_if_pcs.aneg_restart = 0;
    phy->mac_if_pcs.force_adv_ability = 0;
    //phy->mac_if_pcs.sgmii_in_pre = VTSS_PHY_MAC_SERD_PCS_SGMII_IN_PRE_ONE;
    //phy->mac_if_pcs.sgmii_in_pre = VTSS_PHY_MAC_SERD_PCS_SGMII_IN_PRE_TWO;
    phy->mac_if_pcs.sgmii_in_pre = VTSS_PHY_MAC_SERD_PCS_SGMII_IN_PRE_NONE;
    phy->mac_if_pcs.sgmii_out_pre = 0;
    phy->mac_if_pcs.serdes_aneg_ena = 0;
    phy->mac_if_pcs.serdes_pol_inv_in = 0;
    phy->mac_if_pcs.serdes_pol_inv_out = 0;
    phy->mac_if_pcs.fast_link_stat_ena = 0;
    phy->mac_if_pcs.inhibit_odd_start = 0;

/*  Setup the MEDIA Interface PCS Parameters */
    //phy->media_if_pcs.remote_fault = VTSS_PHY_MEDIA_SERD_PCS_REM_FAULT_OFFLINE;
    //phy->media_if_pcs.remote_fault = VTSS_PHY_MEDIA_SERD_PCS_REM_FAULT_LINK_FAIL;
    //phy->media_if_pcs.remote_fault = VTSS_PHY_MEDIA_SERD_PCS_REM_FAULT_ANEG_ERROR;
    phy->media_if_pcs.remote_fault = VTSS_PHY_MEDIA_SERD_PCS_REM_FAULT_NO_ERROR;
    phy->media_if_pcs.aneg_pd_detect = 0;
    phy->media_if_pcs.force_adv_ability = 0;
    phy->media_if_pcs.serdes_pol_inv_in = 0;
    phy->media_if_pcs.serdes_pol_inv_out = 0;
    phy->media_if_pcs.inhibit_odd_start = 0;
    phy->media_if_pcs.force_hls = 0;
    phy->media_if_pcs.force_fefi = 0;
    phy->media_if_pcs.force_fefi_value = 0;

    return;
}


void get_phy_default_reset_config(vtss_phy_reset_conf_t  *phy_reset) {
    phy_reset->mac_if = VTSS_PORT_INTERFACE_SGMII;      // Set the port MAC interface
    phy_reset->media_if = VTSS_PHY_MEDIA_IF_CU;  // Set media interface
    phy_reset->rgmii.rx_clk_skew_ps = rgmii_skew_delay_200_psec;
    phy_reset->rgmii.tx_clk_skew_ps = rgmii_skew_delay_200_psec;
    phy_reset->tbi.aneg_enable = FALSE;  // Set to Enable tbi
    phy_reset->force = VTSS_PHY_NOFORCE_RESET;   // Set to VTSS_PHY_NOFORCE_RESET or to Force PHY Reset VTSS_PHY_FORCE_RESET for Viper and Tesla
    phy_reset->pkt_mode = VTSS_PHY_PKT_MODE_IEEE_1_5_KB; //  (default)VTSS_PHY_PKT_MODE_IEEE_1_5_KB, VTSS_PHY_PKT_MODE_JUMBO_9_KB, VTSS_PHY_PKT_MODE_JUMBO_12_KB
    phy_reset->i_cpu_en = 0;         // Set to TRUE to enable internal 8051 CPU for Enzo and Spyder Family Only

    return;
}


/* ================================================================= *
 *  START_OF_MAIN
 * ================================================================= */
int main(int argc, const char **argv) {
    u16 value;
    vtss_rc                 rc;
    vtss_appl_board_t       *board;
    vtss_inst_create_t      create;
    vtss_port_no_t          port_no=0;
    vtss_port_no_t          phy_base_port=0;
    vtss_phy_conf_t         phy;
    vtss_phy_conf_t         phy_default_config;
    vtss_phy_conf_1g_t      phy_1g;
    vtss_phy_reset_conf_t   phy_reset;
    vtss_init_conf_t        init_conf;
    vtss_phy_loopback_t     loopback;
    vtss_port_interface_t   mac_if;
    vtss_phy_media_interface_t media_if;
    char value_str[255] = {0};
    char *p_mac_if_name = (char *)NULL;
    char *p_media_if_name = (char *)NULL;
    vtss_phy_mode_t         prev_mode[4];
#if defined (NANO_EVAL_BOARD)
    vtss_phy_wol_conf_t     wol_config;
#endif
#if defined (VTSS_API_INIT_SEQ_NORMAL)
        vtss_phy_conf_t vtss_phy_default_conf;
#endif
    char command[255] = {0};
    char port_no_str[255] = {0};
    char addr_str[255] = {0};
    char ext_page_str[255] = {0};
    u16  rx_clk_skew_ps = 0;
    u16  tx_clk_skew_ps = 0;
    BOOL set_hdx = FALSE;
    BOOL set_fdx = FALSE;
    BOOL read_ext = FALSE;
    BOOL write_ext = FALSE;
    BOOL read_cmd = TRUE;
    BOOL run_pre_reset = TRUE;
    BOOL run_reset = TRUE;
    BOOL run_post_reset = TRUE;
    BOOL run_phy_config = TRUE;
    BOOL skip_to_main_menu = FALSE;
    BOOL enable_1588 = FALSE;
    BOOL enable_macsec[4] = {0};
    int addr=0;
    int ext_page=0;
    vtss_phy_eee_conf_t      eee_conf;
    vtss_port_no_t ing_port_no = 0;
    vtss_port_no_t egr_port_no = 0;

    // Setup trace level for PHY group
    // VTSS_TRACE_LEVEL_NONE
    // VTSS_TRACE_LEVEL_ERROR
    // VTSS_TRACE_LEVEL_INFO
    // VTSS_TRACE_LEVEL_DEBUG
    // VTSS_TRACE_LEVEL_NOISE
    vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_AIL] = VTSS_TRACE_LEVEL_ERROR;
    vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_CIL] = VTSS_TRACE_LEVEL_ERROR;
    printf ("//Default AIL TRACE Level : VTSS_TRACE_LEVEL_ERROR\n" );
    printf ("//Default CIL TRACE Level : VTSS_TRACE_LEVEL_ERROR\n" );

    printf ("Change TRACE Logging to TERM Output? (Y/N)  \n");
    memset (&value_str[0], 0, sizeof(value_str));
    scanf("%s", &value_str[0]);

    if (value_str[0] == 'y' || value_str[0] == 'Y' ) {
        printf ("Enter AIL TRACE Logging Config (Options: 0=None/1=Error/2=Info/3=Debug/4=Noise) \n");
        memset (&value_str[0], 0, sizeof(value_str));
        scanf("%s", &value_str[0]);
        if (value_str[0] == '0') vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_AIL] = VTSS_TRACE_LEVEL_NONE;
        if (value_str[0] == '1') vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_AIL] = VTSS_TRACE_LEVEL_ERROR;
        if (value_str[0] == '2') vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_AIL] = VTSS_TRACE_LEVEL_INFO;
        if (value_str[0] == '3') vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_AIL] = VTSS_TRACE_LEVEL_DEBUG;
        if (value_str[0] == '4') vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_AIL] = VTSS_TRACE_LEVEL_NOISE;

        printf ("Enter CIL TRACE Logging Config (Options: 0=None/1=Error/2=Info/3=Debug/4=Noise) \n");
        memset (&value_str[0], 0, sizeof(value_str));
        scanf("%s", &value_str[0]);
        if (value_str[0] == '0') vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_CIL] = VTSS_TRACE_LEVEL_NONE;
        if (value_str[0] == '1') vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_CIL] = VTSS_TRACE_LEVEL_ERROR;
        if (value_str[0] == '2') vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_CIL] = VTSS_TRACE_LEVEL_INFO;
        if (value_str[0] == '3') vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_CIL] = VTSS_TRACE_LEVEL_DEBUG;
        if (value_str[0] == '4') vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_CIL] = VTSS_TRACE_LEVEL_NOISE;
    }

    // Setup trace level for PHY group - vtss_appl_trace_conf is a global
    vtss_trace_conf_set(VTSS_TRACE_GROUP_PHY, &vtss_appl_trace_conf);


#ifdef _INCLUDE_DEBUG_FILE_PRINT_
    fp = fopen("phyeval.log", "w");
#endif

#if defined (NANO_EVAL_BOARD)
    memset (&wol_config, 0, sizeof(vtss_phy_wol_conf_t));
#endif

    memset (&loopback, 0, sizeof(vtss_phy_loopback_t));
    memset (&phy, 0, sizeof(vtss_phy_conf_t));

    // In this case we only have one board. Assign point to the board definition
    board = &board_table[0];

    memset (&board_table[0], 0, (sizeof(vtss_appl_board_t) * MAX_BOARD_INSTANCES));

    printf ("//Default Setup Assumptions: \n" );
    printf ("//Eval Board has Power Applied prior to Demo start \n" );
    printf ("//The PHY Initialization Timing delays have been satisfied \n" );
    printf ("//Pwr Supply/Voltages Stable, Ref Clk Stable, Ref & PLL Stable \n\n" );
#ifdef  ATOM12_EVAL_BOARD
    printf ("\n//Comment: <<< Did you perform H/W RESET on ATOM12 Eval Board?  >>> \n\n");
#endif

#ifdef _INCLUDE_DEBUG_TERM_PRINT_
    printf ("Enable Live Debug TERM Output? (Y/N)  \n");
    memset (&value_str[0], 0, sizeof(value_str));
    scanf("%s", &value_str[0]);

    if (value_str[0] == 'y' || value_str[0] == 'Y' ) {
        live_debug_enable = TRUE;
    }
#endif

#ifdef CHANGE_PHY_BASE_PORT
    printf ("Compilation definition: -DVTSS_OPT_PORT_COUNT= %d  \n\n", VTSS_OPT_PORT_COUNT);
    printf ("Compiled Min Addr VTSS_PORT_NO_START: %d  \n", VTSS_PORT_NO_START);
    printf ("Compiled Number of Ports: VTSS_PORTS: %d  \n\n", VTSS_PORTS);
    printf ("Compiled Max Addr of VTSS_PORTS: %d  \n\n", VTSS_PORTS);

#if 0
    printf ("Enter the Base Address of the PHY (Default: 0):  \n");
    memset (&port_no_str[0], 0, sizeof(value_str));
    scanf("%s", &port_no_str[0]);
    phy_base_port = atoi(port_no_str);
#endif
    printf ("Base Address of the PHY: %d  \n", phy_base_port);
#endif

    // Initialize
    vtss_board_phy_init(board);

    // "Create" the board
    vtss_inst_get(board->target, &create);
    vtss_inst_create(&create, &board->inst);
    vtss_init_conf_get(board->inst, &init_conf);

    board->init.init_conf = &init_conf;
    if (board->board_init(argc, argv, board)) {
        T_E("Could not initialize board");
        return 1;
    } else {
#ifdef  ATOM12_EVAL_BOARD
    printf ("\n//Comment: <<< Please be patient, Loading ATOM12 Eval Board may take several minutes!!! >>> \n\n");
#endif
        printf ("//Comment: Board being initialized\n");
    }

#if defined VTSS_API_INIT_SEQ_WARM
        init_conf.warm_start_enable = TRUE;
        init_conf.restart_info_src = VTSS_RESTART_INFO_SRC_CU_PHY;
#endif

    if (vtss_init_conf_set(board->inst, &init_conf) == VTSS_RC_ERROR) {
        T_E("Could not initialize");
        return 1;
    }

/* ========================================================================= *
 *  Must get the Pre-Initialized Config for this Instance before populating
 * ========================================================================= */
    printf ("//Comment: Step 1: GET the Default PHY Config from the Instance for Port: %d\n", port_no);
    vtss_phy_conf_get(board->inst, port_no, &phy);

    get_phy_default_config(&phy);

    // Reset stuff needed before PHY port reset, any port will do (Only at start-up initialization)

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
    fprintf (fp,"PHY PRE-RESET\n");
#endif
    printf ("//Comment: Step 2: Running PHY vtss_phy_pre_reset on base port of PHY\n");
    rc = vtss_phy_pre_reset(board->inst, phy_base_port);
    if (rc != VTSS_RC_OK) {
        printf ("//>>>>>> ERROR DETECTED <<<<<<<< During PHY pre-reset, rc = %d\n", rc);
    }


    rc = vtss_phy_reset_get(board->inst, port_no, &phy_reset);
    if (rc != VTSS_RC_OK) {
        printf ("//>>>>>> ERROR DETECTED <<<<<<<< During PHY phy_reset, rc = %d\n", rc);
    }

    get_phy_default_reset_config(&phy_reset);


/* ****************************************************** */
/* FINAL CONFIGURATION Over-rides for EVAL BOARD          */
/* ****************************************************** */
#ifdef  ATOM12_EVAL_BOARD
        printf ("//Comment: Setup of VSC8522 - ATOM12 Eval Board \n");
        mac_if = VTSS_PORT_INTERFACE_QSGMII;
        media_if = VTSS_PHY_MEDIA_IF_CU;
#endif
#ifdef  TESLA_EVAL_BOARD
        printf ("//Comment: Setup of VSC8574 - Tesla Eval Board \n");
        //mac_if = VTSS_PORT_INTERFACE_QSGMII;
        mac_if = VTSS_PORT_INTERFACE_SGMII;
        //mac_if = VTSS_PORT_INTERFACE_RGMII;
        media_if = VTSS_PHY_MEDIA_IF_CU;
#endif
#ifdef  ELISE_EVAL_BOARD
        printf ("//Comment: Setup of VSC8514 - Elise Eval Board \n");
        mac_if = VTSS_PORT_INTERFACE_QSGMII;
        media_if = VTSS_PHY_MEDIA_IF_CU;
#endif
#ifdef  NANO_EVAL_BOARD
        printf ("//Comment: Setup of VSC8502 - Nano Eval Board \n");
        mac_if = VTSS_PORT_INTERFACE_RGMII;
        media_if = VTSS_PHY_MEDIA_IF_CU;
        tx_clk_skew_ps = rgmii_skew_delay_800_psec;
        rx_clk_skew_ps = rgmii_skew_delay_800_psec;
#endif
#ifdef  VIPER_EVAL_BOARD
        printf ("//Comment: Setup of VSC8584 - Viper Eval Board \n");
        //mac_if = VTSS_PORT_INTERFACE_QSGMII;
        mac_if = VTSS_PORT_INTERFACE_SGMII;
        media_if = VTSS_PHY_MEDIA_IF_CU;
#endif


        if (phy.mode == VTSS_PHY_MODE_ANEG) {
            printf ("//Current Setup: PHY Mode: ANEG Enabled: 1G_FDX: 0x%x;  1G_HDX: 0x%x \n", phy.aneg.speed_1g_fdx, phy.aneg.speed_1g_hdx);
        } else if (phy.mode == VTSS_PHY_MODE_FORCED) {
            printf ("//Current Setup: PHY Mode: FORCED Speed Enabled: 1G_FDX: 0x%x;  1G_HDX: 0x%x \n", phy.aneg.speed_1g_fdx, phy.aneg.speed_1g_hdx);
        } else if (phy.mode == VTSS_PHY_MODE_POWER_DOWN) {
            printf ("//Current Setup: PHY Mode: PHY Power Down Enabled \n" );
        } else {
            printf ("//Default Setup: PHY Mode: Unknown \n" );
        }



/* ****************************************************** */
/* Over-rides for MAC/MEDIA Setup                         */
/* ****************************************************** */
    // Example for MAC interfaces; Note: Last entry is one selected
    //mac_if = VTSS_PORT_INTERFACE_SERDES;
    //mac_if = VTSS_PORT_INTERFACE_RGMII;
    //mac_if = VTSS_PORT_INTERFACE_QSGMII;
    //mac_if = VTSS_PORT_INTERFACE_SGMII;


    // Example for Media interfaces; Note: Last entry is one selected
    //media_if = VTSS_PHY_MEDIA_IF_AMS_FI_100FX;
    //media_if = VTSS_PHY_MEDIA_IF_AMS_CU_100FX;
    //media_if = VTSS_PHY_MEDIA_IF_AMS_FI_1000BX;
    //media_if = VTSS_PHY_MEDIA_IF_AMS_CU_1000BX;
    //media_if = VTSS_PHY_MEDIA_IF_AMS_FI_PASSTHRU;
    //media_if = VTSS_PHY_MEDIA_IF_AMS_CU_PASSTHRU;
    //media_if = VTSS_PHY_MEDIA_IF_FI_100FX;
    //media_if = VTSS_PHY_MEDIA_IF_FI_1000BX;
    //media_if = VTSS_PHY_MEDIA_IF_SFP_PASSTHRU;
    //media_if = VTSS_PHY_MEDIA_IF_CU;


/* ****************************************************** */
/*  Over-rides for PHY Config Setup                       */
/* ****************************************************** */
       //phy.mode = VTSS_PHY_MODE_FORCED;
       //phy.mode = VTSS_PHY_MODE_ANEG;  // Mode ANEG means forced mode settings irrelevant
       //phy.forced.speed = VTSS_SPEED_100M;
       //phy.sigdet = VTSS_PHY_SIGDET_POLARITY_ACT_HIGH;
       //phy.unidir = VTSS_PHY_UNIDIRECTIONAL_DISABLE;

#if defined (TESLA_EVAL_BOARD) || defined (VIPER_EVAL_BOARD) || defined (ELISE_EVAL_BOARD)

/*  Setup the MAC Interface PCS Parameters */
        //phy->mac_if_pcs.disable = 0;
        //phy->mac_if_pcs.restart = 0;
        //phy->mac_if_pcs.pd_enable = 1;
        //phy->mac_if_pcs.aneg_restart = 0;
        //phy->mac_if_pcs.force_adv_ability = 0;
        //phy->mac_if_pcs.sgmii_in_pre = VTSS_PHY_MAC_SERD_PCS_SGMII_IN_PRE_ONE;
        //phy->mac_if_pcs.sgmii_in_pre = VTSS_PHY_MAC_SERD_PCS_SGMII_IN_PRE_TWO;
        //phy->mac_if_pcs.sgmii_in_pre = VTSS_PHY_MAC_SERD_PCS_SGMII_IN_PRE_NONE;
        //phy->mac_if_pcs.sgmii_out_pre = 0;
        //phy->mac_if_pcs.serdes_aneg_ena = 0;
        //phy->mac_if_pcs.serdes_pol_inv_in = 0;
        //phy->mac_if_pcs.serdes_pol_inv_out = 0;
        //phy->mac_if_pcs.fast_link_stat_ena = 0;
        //phy->mac_if_pcs.inhibit_odd_start = 0;

#endif

#if defined (TESLA_EVAL_BOARD) || defined (VIPER_EVAL_BOARD)
/*  Setup the MEDIA Interface PCS Parameters */
        //phy->media_if_pcs.remote_fault = VTSS_PHY_MEDIA_SERD_PCS_REM_FAULT_OFFLINE;
        //phy->media_if_pcs.remote_fault = VTSS_PHY_MEDIA_SERD_PCS_REM_FAULT_LINK_FAIL;
        //phy->media_if_pcs.remote_fault = VTSS_PHY_MEDIA_SERD_PCS_REM_FAULT_ANEG_ERROR;
        //phy->media_if_pcs.remote_fault = VTSS_PHY_MEDIA_SERD_PCS_REM_FAULT_NO_ERROR;
        //phy->media_if_pcs.aneg_pd_detect = 0;
        //phy->media_if_pcs.force_adv_ability = 0;
        //phy->media_if_pcs.serdes_pol_inv_in = 0;
        //phy->media_if_pcs.serdes_pol_inv_out = 0;
        //phy->media_if_pcs.inhibit_odd_start = 0;
        //phy->media_if_pcs.force_hls = 0;
        //phy->media_if_pcs.force_fefi = 0;
        //phy->media_if_pcs.force_fefi_value = 0;

#endif


        if (phy.mode == VTSS_PHY_MODE_ANEG) {
            printf ("// Config: PHY Mode: ANEG Enabled: FDX: 0x%x;  HDX: 0x%x \n", phy.aneg.speed_1g_fdx, phy.aneg.speed_1g_hdx);
        } else if (phy.mode == VTSS_PHY_MODE_FORCED) {
            printf ("// Config: PHY Mode: FORCED FDX: 0x%x; HDX: 0x%x  \n", (phy.forced.fdx == 0x1), (phy.forced.fdx == 0x0));
            printf ("// Config: FORCED Speed: 1G: 0x%x; 100M: 0x%x; 10M: 0x%x  \n", (phy.forced.speed == VTSS_SPEED_1G),
                    (phy.forced.speed == VTSS_SPEED_1G), (phy.forced.speed == VTSS_SPEED_1G));
        } else if (phy.mode == VTSS_PHY_MODE_POWER_DOWN) {
            printf ("//Default Setup: PHY Mode: PHY Power Down Enabled \n" );
        } else {
            printf ("//Default Setup: PHY Mode: Unknown \n" );
        }

        printf ("\n//Comment: miim_read format  : miim_read(port_number, address) \n");
        printf ("//Comment: miim_write format : miim_write(port_number, address, value(hex)) \n");
        printf ("\n\n");
/* ****************************************************** */
/* ****************************************************** */
/* USER CONFIGURATION OF EVAL BOARD                       */
/* ****************************************************** */

        p_mac_if_name = get_mac_if_name_by_mac_id( mac_if );
        p_media_if_name = get_media_if_name_by_media_id( media_if );
        printf ("ALL MAC I/F defaulted to: %s \n", p_mac_if_name);
        printf ("ALL MEDIA I/F defaulted to: %s \n", p_media_if_name);

#if 0
        printf ("Are Default MAC I/F and MEDIA I/F for ALL Ports Ok ? (Y/N)  \n");
        memset (&value_str[0], 0, sizeof(value_str));
        scanf("%s", &value_str[0]);

        if (value_str[0] == 'n' || value_str[0] == 'N' ) {
            printf ("Enter Default  MEDIA I/F  for ALL Ports  \n");
            printf ("Copper Options: cu/sfppass/amscupass/amscu1000bx/amscu100fx \n");
            printf ("Fiber Options: fi1000bx/fi100fx/amsfipass/amsfi1000bx/amsfi100fx \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            if (value_str[0] != 0) {
                p_media_if_name = get_media_if_name( value_str, &media_if);
                p_media_if_name = get_media_if_name_by_media_id( media_if );
            }

            printf ("Enter Default  MAC I/F  for ALL Ports  \n");
            printf ("Options: gmii/rgmii/sgmii/qsgmii \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            if (value_str[0] != 0) {
                p_mac_if_name = get_mac_if_name( value_str, &mac_if);
                p_mac_if_name = get_mac_if_name_by_mac_id( mac_if );
            }
        }
#endif

#if 0
        // SmartBits defaults to Forced mode for Fibre - Make life easier for setups
        if (media_if == VTSS_PHY_MEDIA_IF_FI_1000BX) {
            //phy.mode = VTSS_PHY_MODE_FORCED;
            phy.forced.speed = VTSS_SPEED_1G;
            printf ("VTSS_PHY_MEDIA_IF_FI_1000BX Selected,  Fibre, Setting Speed to 1G\n");
        } else if (media_if == VTSS_PHY_MEDIA_IF_FI_100FX) {
            //phy.mode = VTSS_PHY_MODE_FORCED;
            phy.forced.speed = VTSS_SPEED_100M;
            printf ("VTSS_PHY_MEDIA_IF_FI_100FX Selected,  Fibre, Setting Speed to 100M\n");
        } else if (media_if == VTSS_PHY_MEDIA_IF_AMS_CU_1000BX) {
            phy.forced.speed = VTSS_SPEED_1G;
            printf ("VTSS_PHY_MEDIA_IF_AMS_CU_1000BX Selected,  AMS-Cu Preferred, Setting Speed to 1G \n");
        } else if (media_if == VTSS_PHY_MEDIA_IF_AMS_FI_1000BX) {
            phy.forced.speed = VTSS_SPEED_1G;
            printf ("VTSS_PHY_MEDIA_IF_AMS_FI_1000BX Selected,  AMS-Fibre Preferred, Setting Speed to 1G \n");
        } else if (media_if == VTSS_PHY_MEDIA_IF_AMS_CU_100FX) {
            phy.forced.speed = VTSS_SPEED_100M;
            printf ("VTSS_PHY_MEDIA_IF_AMS_CU_100FX Selected,  AMS-Cu Preferred, Setting Speed to 100M\n");
        } else if (media_if == VTSS_PHY_MEDIA_IF_AMS_FI_100FX) {
            phy.forced.speed = VTSS_SPEED_100M;
            printf ("VTSS_PHY_MEDIA_IF_AMS_FI_100FX Selected, AMS-Fibre Preferred, Setting Speed to 100M\n");
        } else if (media_if == VTSS_PHY_MEDIA_IF_SFP_PASSTHRU) {
            printf ("VTSS_PHY_MEDIA_IF_SFP_PASSTHRU Selected, Setting PHY into Protocol Transfer Mode \n");
            printf ("Note Following: Reg0.12=1, Reg23.12=0, Reg23.10:8=001, Reg16E3.7=1, Also check SigDet polarity and LOS\n");
        }

        printf ("ALL MAC I/F defaulted to: %s \n", p_mac_if_name);
        printf ("ALL MEDIA I/F defaulted to: %s \n", p_media_if_name);
        if (phy.mode == VTSS_PHY_MODE_FORCED) {
            if (phy.forced.speed == VTSS_SPEED_1G) {
                printf ("ALL PHY Port MODE defaulted to: FORCED - 1G; Unidirectional: %x \n", phy.unidir);
                rc = vtss_phy_conf_1g_get(board->inst, port_no, &phy_1g);
                printf ("Port %d, Curr: Manual Enable(1=enable/0=disable): 0x%x;  Master/Slave(1=master, 0=slave): 0x%x\n\n", port_no, phy_1g.master.cfg, phy_1g.master.val);

                printf ("Port %d, Modify Current Values? (Y/N)\n", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == 'Y' || value_str[0] == 'y')
                {
                    printf ("Port %d, Enter Manual Enable(1=enable, 0=disable): ", port_no);
                    memset (&value_str[0], 0, sizeof(value_str));
                    scanf("%s", &value_str[0]);
                    if (value_str[0] == '1') {
                        phy_1g.master.cfg = 1;
                        printf ("Port %d, Manual Setting Enabled, Enter Master/Slave Config (1=Master, 0=Slave): ", port_no);
                        memset (&value_str[0], 0, sizeof(value_str));
                        scanf("%s", &value_str[0]);
                        if (value_str[0] == '1') {
                            phy_1g.master.val = 1;
                        } else {
                            phy_1g.master.val = 0;
                        }
                    }
                }
                rc = vtss_phy_conf_1g_set(board->inst, port_no, &phy_1g);

            } else if (phy.forced.speed == VTSS_SPEED_100M) {
                printf ("ALL PHY Port MODE defaulted to: FORCED - 100M; Unidirectional: %x \n", phy.unidir);
            } else if (phy.forced.speed == VTSS_SPEED_10M) {
                printf ("ALL PHY Port MODE defaulted to: FORCED - 10M; Unidirectional: %x \n", phy.unidir);
            } else {
                printf ("ALL PHY Port MODE defaulted to: FORCED - UNKNOWN SPEED; Unidirectional: %x \n", phy.unidir);
            }
        } else if (phy.mode == VTSS_PHY_MODE_ANEG) {
            printf ("ALL PHY Ports ANEG defaulted to Enabled: FDX: 0x%x;  HDX: 0x%x \n", phy.aneg.speed_1g_fdx, phy.aneg.speed_1g_hdx);
        } else if (phy.mode == VTSS_PHY_MODE_POWER_DOWN) {
                printf ("ALL PHY Port Mode defaulted to: PHY Power Down \n");
        } else{
            printf ("ALL MEDIA mode defaulted to: UNKNOWN \n");
        }

        printf ("\n\nAre Default AMS Force Settings for ALL Ports Ok ? (Y/N)  \n");
        memset (&value_str[0], 0, sizeof(value_str));
        scanf("%s", &value_str[0]);

        if (value_str[0] == 'n' || value_str[0] == 'N' ) {
            printf ("Enter Default  FORCE_AMS_SELECTION for ALL Ports to:   0=Normal AMS/1=Force SerDes/2=Force Copper\n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == '0') {
                phy.force_ams_sel = VTSS_PHY_MEDIA_FORCE_AMS_SEL_NORMAL;
            } else  if (value_str[0] == '1') {
                phy.force_ams_sel = VTSS_PHY_MEDIA_FORCE_AMS_SEL_SERDES;
            } else  if (value_str[0] == '2') {
                phy.force_ams_sel = VTSS_PHY_MEDIA_FORCE_AMS_SEL_COPPER;
            } else {
                phy.force_ams_sel = VTSS_PHY_MEDIA_FORCE_AMS_SEL_NORMAL;
            }
        }

#endif

        // Do PHY port reset + Port setup
        printf ("//Comment: PHY port reset\n");
        for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS; port_no++) {
            phy_reset.mac_if = mac_if;             // Set the port MAC interface
            phy_reset.media_if = media_if;         // Set media interface
            //phy_reset.rgmii.rx_clk_skew_ps = rx_clk_skew_ps;
            //phy_reset.rgmii.tx_clk_skew_ps = tx_clk_skew_ps;

#if defined (VIPER_EVAL_BOARD) || defined (TESLA_EVAL_BOARD) || defined (ELISE_EVAL_BOARD) || defined (ATOM12_EVAL_BOARD)
                // SmartBits defaults to Forced mode for Fibre - Make life easier for setups
                // For Fibre 1000BX(SFP) and 100FX(SFP), Cu(SFP) the Speed is Forced mode and the SigDet has to be cleared, ie Reg 19E1.0=0
            if (media_if != VTSS_PHY_MEDIA_IF_CU) {
                phy.sigdet = VTSS_PHY_SIGDET_POLARITY_ACT_HIGH;
                printf ("SFP Config DETECTED - Setting SigDet - Addr: 19E1 = 0x%x\n", value);
            }
#endif

            printf ("//Comment: Step 3: Perform PHY port config on PHY port: %d\n", port_no);
            vtss_phy_conf_set(board->inst, port_no, &phy);

            vtss_phy_conf_1g_get(board->inst, port_no, &phy_1g);
            printf ("//Comment: Step 4: Perform PHY port 1G_config on PHY port: %d\n", port_no);
#if 0
                phy_1g.master.cfg = 0;    /* Master/Slave config, 1=enabled, 0=disable */
                phy_1g.master.val = 0;    /* Master/Slave config, 1=Master, 0=Slave */
#endif

            vtss_phy_conf_1g_set(board->inst, port_no, &phy_1g);
            printf ("// PHY port %d, Reset Complete; Config Complete, Port config: Manual_Master: 0x%x, 1=Master/0=Slave: 0x%x \n", port_no, phy_1g.master.cfg, phy_1g.master.val);

            printf ("//Comment: Step 5: Perform PHY port reset on PHY port: %d\n", port_no);
#ifdef _INCLUDE_DEBUG_FILE_PRINT_
            fprintf (fp,"PHY RESET\n");
#endif
            vtss_phy_reset(board->inst, port_no, &phy_reset); // Do port reset

        }

        printf ("// PHY port %d, Reset Complete; Config Complete, Port config: Manual_Master: 0x%x, 1=Master/0=Slave: 0x%x \n", port_no, phy_1g.master.cfg, phy_1g.master.val);


#if 0
#if defined (NANO_EVAL_BOARD)
        for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS; port_no++) {
            addr=20;
            value = 0x0011;
            miim_write(board->inst, port_no, 31, 0x2); /* Setup Page, Ext2, 20E2 */
            miim_write(board->inst, port_no, addr, value);
            printf ("Setting NANO MII/GMII/RGMII Skews - Addr: 20E1 = 0x%x\n", value);
            miim_write(board->inst, port_no, 31, 0x0); /* Setup Page, Std */
        }
#endif
#endif

    // Do reset stuff that is needed after port reset,
    // any port will do (Only at start-up initialization)
        printf ("//Comment: Last_Step: Running PHY vtss_phy_post_reset on base port of PHY\n");
#ifdef _INCLUDE_DEBUG_FILE_PRINT_
        fprintf (fp,"PHY POST-RESET\n");
#endif
        rc = vtss_phy_post_reset(board->inst, phy_base_port);
        if (rc != VTSS_RC_OK) {
            printf ("//ERROR DETECTED during PHY post-reset, rc = %d\n", rc);
        }

#if defined(VTSS_CHIP_10G_PHY)
        vtss_phy_10g_mode_t     oper_mode;
        for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS; port_no++) {
            if(port_is_10g_phy(port_no)) {
                if (vtss_phy_10g_mode_set(board->inst, port_no, &oper_mode) == VTSS_RC_ERROR) {
                    T_E("Could not initialize 10G phy");
                    return 1;
                }
            }
        }
#endif /* VTSS_CHIP_10G_PHY */

        phy_loop_back(); // Example for loopbacks - This also Initializes ALL Loopbacks to OFF

        {
            vtss_port_status_t status;
            for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS; port_no++) {
                rc = vtss_phy_chip_temp_init (board->inst, port_no);
                printf ("Temp Init RC:x%X \n", rc);

                // Get the Status so that fields get populated
                printf ("Initial Status after Init, populating API fields \n");
                vtss_phy_status_get(board->inst, port_no, &status);
                if (status.link_down == 0) {
                    printf("Link UP!  (status=%d) \n", status.link_down);
                    if (status.link) {
                        printf("Link: 0x%x, Speed: 0x%x, FDX: 0x%x, Remote_Fault: 0x%x, ANEG_Complete: 0x%x, Fiber: 0x%x, MDI_Cross: 0x%x  \n",
                         status.link, status.speed, status.fdx, status.remote_fault, status.aneg_complete, status.fiber, status.mdi_cross);
                    }
                    } else if (status.link_down == 1) {
                        printf("Link DOWN!  (status=%d) \n", status.link_down);
                        printf("Link: 0x%x, Speed: 0x%x, FDX: 0x%x, Remote_Fault: 0x%x, ANEG_Complete: 0x%x, Fiber: 0x%x, MDI_Cross: 0x%x  \n",
                         status.link, status.speed, status.fdx, status.remote_fault, status.aneg_complete, status.fiber, status.mdi_cross);
                } else {
                    printf("Link Status Unknown!  (status=%d) \n", status.link_down);
                }
            }
        }
    printf ("\n\nReady - Enter ? for Help \n");

    while (1) {
       {
            read_ext = FALSE;
            write_ext = FALSE;
            printf (" *************************************\n");
            printf (" The following commands are supported:\n");
#ifdef _INCLUDE_DEBUG_TERM_PRINT_
            printf (" debug  <port_no>  - Sets PHY API to output Debug \n");
#endif
            printf (" dump <port_no> - Dump Reg 0-31 Pages:std/ext1/ext2/ext3/gpio/1588/macsec/1588_rng/macsec_rng/ext_rng for Port \n");
            printf (" rdext <port_no> <page> <addr> - Read Extended Page - where page=1,2,3,4,0x10,0x1588,0x2A30,0x52B5 - <addr> 0-31 \n");
            printf (" wrext <port_no> <page> <addr> <value> - Write Ext Page - page=1,2,3,4,0x10,0x1588,0x2A30,0x52B5 - <addr> 0-31 - Value MUST be in hex \n");
            printf (" ----------------------------------------  |  ------------------------------------------------------- \n");
            printf (" rd       <port_no> <addr>                 |  wr          <port_no> <addr> <value> - Value MUST be in hex\n");
            printf (" status   <port_no>  - Rtn PHY Link status |  stats       <port_no>  - Return PHY API Statistics \n");
            printf (" getmedia <port_no> - Get Media i/f        |  setmedia    <port_no> - Set Media I/F for port \n");
            printf (" getmac   <port_no> - Get MAC i/f          |  setmac      <port_no> - Set MAC I/F for port \n");
            printf (" loopback <port_no> - Loopback Mode        |  veriphy     <port_no> - VeriPhy cable Diags \n");
            printf (" temp     <port_no> - Temperature          |  setrecovclk <port_no> - Set Recovered Clock \n");
            printf (" powerdn  <port_no> - Set Port to Pwr Dn   |  powerup     <port_no> - Set Port to Power UP State \n");
            printf (" ms_config <port_no> - Master/Slave Config |  rst_lcpll   <port_no> - Reset LCPLL for Port - Base Port of PHY \n");
            printf (" intmask  <port_no> - Set Int Mask (Reg 25)|  intstat     <port_no> - Read Port Int Status (Reg 26) by calling event_poll (same as ISR) \n");
            printf (" prereset <port_no> - Run PHY Pre-Reset    |  phyreset    <port_no>  - Run PHY Reset on Port\n");
            printf (" postreset <port_no> - Run PHY Post-Reset  |  powercfg    <port_no> - Adjust PHY Power Settings, ActiPHY, PerfectReach\n");
            printf (" mse100m   <port_no> - Get PHY 100m MSE    |  mse1000m    <port_no> - Get PHY 1000m MSE Values for each Twisted Pair\n");
            printf (" fefi      <port_no> - Far End Fail Ind    |  config_port <port_no> - Change the configuration for the port\n");
            printf (" rd_1588   <port_no> - CSR_Read 1588 MACRO |  wr_1588     <port_no> - CSR_Write 1588 MACRO \n");
            printf (" rd_macsec <port_no> - CSR_Read MACSEC CSR |  wr_macsec   <port_no> - CSR_Write MACSEC CSR MACRO \n");
            printf (" getserdes <port_no> - Get the SerDes Cfg  |                                                     \n");

#ifndef NANO_EVAL_BOARD
            printf (" ob_post  <port_no> - ob_post SerDes Macro |  ob_level    <port_no> - Run ob_level SerDes Macro \n");
            printf (" odd_start <port_no> - MAC-MEDIA Odd Start |  warmstart   <port_no> Execute Warm-Start Sequence \n");
#endif
#ifdef VIPER_SERDES_CSR_DEBUG
            printf (" csr_rd   <port_no> Read SerDes MACRO Reg  |  csr_wr      <port_no> Write SerDes MACRO Register \n");
#endif
#if defined (NANO_EVAL_BOARD)
            printf (" wol       Enter Sub-Menu to access Wake-On-LAN (WoL) functions\n");
#endif
#if defined (VTSS_FEATURE_EEE) && defined (VTSS_SW_OPTION_EEE)
            printf (" eee       Enter Sub-Menu to access EEE functions\n");
#endif
#ifdef  EVAL_BOARD_1588_CAPABLE
            printf (" 1588      Enter Sub-Menu to Setup 1588 Ingress/Egress Ports for 1588v2\n");
#endif
#ifdef  EVAL_BOARD_MACSEC_CAPABLE
            printf (" macsec    Enter sub-menu to Setup MACSEC Operation \n");
#endif
            printf (" amssetup <port_no>  - Setup Port 0 as AMS port, Port 1 as Cu, Port 3 as 100FX Fibre (Must have 100FX SFP)\n");
            printf (" amstest  <port_no>  - Test  Port 0 as AMS port, Port 1 as Cu, Port 3 as 100FX Fibre (Must have 100FX SFP)\n");
            printf (" lpstat   <port_no>  - Test which loops over vtss_phy_status_get() a given number of iterations\n");

            printf ("\n exit - Exit Program \n");
            printf (" \n");
            printf ("> ");
        }

        rc = scanf("%s", &command[0]);

        if (strcmp(command, "?")  == 0) {
            printf (" *************************************\n");
            printf ("*************** Help *****************\n");
            printf (" The following commands are supported: \n");
            printf (" rd <port_no> <addr> - Read contents of address \n");
            printf (" wr <port_no> <addr> <value> - Write Value to address:Value MUST be in HEX\n");
            printf (" rdext <port_no> <page> <addr> - Read Extended Page - where page=1,2,3,4,0x10,0x1588,0x2A30,0x52B5 - <addr> 0-31 \n");
            printf (" wrext <port_no> <page> <addr> <value> - Write Ext Page - page=1,2,3,4,0x10,0x1588,0x2A30,0x52B5 - <addr> 0-31 - Value MUST be in hex \n");
            printf (" dump <port_no> - Dump Reg 0-31 for selected Page/Port \n");
            printf ("            std - Dump Std Reg 0-31 for port \n");
            printf ("           ext1 - Dump Extended Pg 1 Reg 16E1-30E1 for port \n");
            printf ("           ext2 - Dump Extended Pg 2 Reg 16E2-30E2 for port \n");
            printf ("           ext3 - Dump Extended Pg 3 Reg 16E3-30E3 for port \n");
            printf ("           gpio - Dump GPIO Page Reg 13G-30G for port \n");
            printf ("           1588 - Dump 1588 Page Reg for port\n");
            printf ("         macsec - Dump MACSec Page Reg for port\n");
            printf ("           test - Dump TEST Page Reg for port\n");
            printf ("             tr - Dump Token Ring Page Reg for port\n");
            printf ("       1588_rng - Dump Range of Registers for 1588 Page for port\n");
            printf ("    macseci_rng - Dump Range of Registers for MACSec Page for port\n");
            printf ("        ext_rng - Dump Range of Registers for Desired Ext Page for port\n");
            printf (" status <port_no>  - Return PHY API status \n");
            printf (" stats  <port_no>  - Return PHY API Statistics \n");
#ifdef _INCLUDE_DEBUG_TERM_PRINT_
            printf (" debug  <port_no>  - Sets PHY API to output Debug \n");
#endif
            printf (" rst_lcpll <port_no> - Reset LCPLL for Port - Note: only works for Base Port of PHY \n");
            printf (" getmedia  <port_no> - Get Media I/F for port \n");
            printf (" setmedia  <port_no> - Set Media I/F for port \n");
            printf (" getmac    <port_no> - Get MAC I/F for port \n");
            printf (" setmac    <port_no> - Set MAC I/F for port \n");
            printf (" ms_config <port_no> - Get/Set Master/Slave Config for port \n");
            printf (" loopback <port_no> - Enable/Disable Loopback Mode \n");
            printf ("       NEAR-end Loopback Mode: Data looped back in PCS Block \n");
            printf ("       FAR-end Loopback Mode: Data looped back in MAC \n");
            printf ("       EXTernal Mode: External Connector Loopback \n");
            printf ("       SERDes Mode: Loopback in SerDes, Types: \n");
            printf ("          NO_LOOP, PAD_LOOP, INPUT_LOOP, FACILITY_LOOP, EQUIPMENT_LOOP \n");
            printf (" veriphy  <port_no> - VeriPhy cable Diagnostics \n");
            printf (" temp     <port_no> - Temperature Reading \n");
            printf (" setrecovclk <port_no> - Set Recovered Clock \n");
            printf (" powerdn  <port_no> - Set Port to Power Down State \n");
            printf (" powerup  <port_no> - Set Port to Power UP State \n");
            printf (" intmask  <port_no> - Set Int Mask (Reg 25) for Port to 0xffff \n");
            printf (" intstat  <port_no> - Read Port Int Status (Reg 26)\n");
            printf (" getserdes <port_no> - Get the SerDes Cfg         \n");
            printf (" amssetup <port_no>  - Setup Port 0 as AMS port, Port 1 as Cu, Port 3 as 100FX Fibre (Must have 100FX SFP)\n");
            printf ("       Non-100FX SFP will cause Link Issues (Reg0=0x3000) and Link UP may not be achieved \n");
            printf (" amstest  <port_no>  - Test  Port 0 as AMS port, Port 1 as Cu, Port 3 as 100FX Fibre (Must have 100FX SFP)\n");
            printf ("       Non-100FX SFP will cause Link Issues (Reg0=0x3000) and Link UP may not be achieved \n");
            printf (" prereset <port_no>  - Run PHY Pre-Reset on Port, For ALL Ports, port_no = -1\n");
            printf (" phyreset <port_no>  - Run PHY Reset on Port\n");
            printf (" postreset <port_no> - Run PHY Post-Reset on Port, For ALL Ports, port_no = -1\n");
            printf (" powercfg  <port_no> - Adjust PHY Power Settings, ActiPHY, PerfectReach, For ALL Ports, port_no = -1 \n");
            printf (" mse100m   <port_no> - Get PHY 100m MSE \n");
            printf (" mse1000m  <port_no> - Get PHY 1000m MSE Values for each Twisted Pair\n");
            printf (" fefi      <port_no> - Far End Fail Indication (FEFI)  \n");
            printf ("       Normal Operation \n");
            printf ("       Force Suppress \n");
            printf ("       Force Failure Indication \n");
#if defined (NANO_EVAL_BOARD)
            printf (" wol       Enter Sub-Menu to access Wake-On-LAN (WoL) functions\n");
            printf ("     - enwol    - Enable/Disable Wake-On-LAN for Port \n");
            printf ("     - getwol   - Get Wake-On-LAN info for Port \n");
            printf ("     - setwol   - Set Wake-On-LAN info for Port \n");
#endif
#if defined (VTSS_FEATURE_EEE) && defined (VTSS_SW_OPTION_EEE)
            printf (" eee       Enter Sub-Menu to access EEE functions\n");
            printf ("     - eee_en   - Enable EEE for Port \n");
            printf ("     - get_eee  - Get EEE Config for Port \n");
            printf ("     - set_eee  - Set EEE Config for Port \n");
#endif
#ifdef  EVAL_BOARD_1588_CAPABLE
            printf (" 1588            Setup 1588 Ingress/Egress Ports for 1588v2\n");
#endif
#ifdef  EVAL_BOARD_MACSEC_CAPABLE
            printf (" macsec          Setup MACSEC Operation\n");
            printf ("    - macsec128  - Enable MACSEC Operation: 128-bit Encryption with Static Key \n");
            printf ("    - macsec256  - Enable MACSEC Operation: 256-bit Encryption with Static Key \n");
            printf ("    - macsec_off - Disable Port for MACsec Operation \n");
            printf ("    - ctrl_cnt   - Get the Sec_Y Control Counters  \n");
            printf ("    - unctrl_cnt - Get the Sec_Y Uncontrolled Counters  \n");
            printf ("    - cmn_cnt    - Get the Sec_Y Common Counters  \n");
            printf ("    - hmac_count - Get the MACSEC Host MAC Counters  \n");
            printf ("    - lmac_count - Get the MACSEC Line MAC Counters  \n");
            printf ("    - dbg_count  - Get the MACSEC Debug Counters  \n");
#endif
#ifndef NANO_EVAL_BOARD
            printf (" ob_post  <port_no> - Run ob_post SerDes Macro \n");
            printf (" ob_level <port_no> - Run ob_level SerDes Macro \n");
            printf (" odd_start <port_no> - Enable/Disable MAC-MEDIA Inhibit Odd Start Delay \n");
#ifdef VIPER_SERDES_CSR_DEBUG
            printf (" csr_rd   <port_no> Read SerDes MACRO Register  \n");
            printf (" csr_wr   <port_no> Write SerDes MACRO Register \n");
#endif
            printf (" warmstart <port_no> Execute Warm-Start Sequence \n");
#endif
            printf ("\n");
            printf ("> ");
            continue;

        } else if (strcmp(command, "dump")  == 0) {
            BOOL     print_hdr = TRUE;
            u32      page_no = 0;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }
            printf ("Port %d, Enter Page(std/ext1/ext2/ext3/gpio/1588/macsec/test/tr/1588_rng/macsec_rng/ext_rng) \n", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            if (strcmp(value_str, "std")  == 0) {
                page_no = VTSS_PHY_PAGE_STANDARD;
                vtss_phy_debug_regdump_print(board->inst, printf, port_no, page_no, print_hdr);
            } else if (strcmp(value_str, "ext1")  == 0) {
                page_no = VTSS_PHY_PAGE_EXTENDED;
                vtss_phy_debug_regdump_print(board->inst, printf, port_no, page_no, print_hdr);
            } else if (strcmp(value_str, "ext2")  == 0) {
                page_no = VTSS_PHY_PAGE_EXTENDED_2;
                vtss_phy_debug_regdump_print(board->inst, printf, port_no, page_no, print_hdr);
            } else if (strcmp(value_str, "ext3")  == 0) {
                page_no = VTSS_PHY_PAGE_EXTENDED_3;
                vtss_phy_debug_regdump_print(board->inst, printf, port_no, page_no, print_hdr);
            } else if (strcmp(value_str, "gpio")  == 0) {
                page_no = VTSS_PHY_PAGE_GPIO;
                vtss_phy_debug_regdump_print(board->inst, printf, port_no, page_no, print_hdr);
            } else if (strcmp(value_str, "1588")  == 0) {
                page_no = VTSS_PHY_PAGE_1588;
                vtss_phy_debug_regdump_print(board->inst, printf, port_no, page_no, print_hdr);
            } else if (strcmp(value_str, "macsec")  == 0) {
                page_no = VTSS_PHY_PAGE_MACSEC;
#ifdef VTSS_FEATURE_MACSEC
                vtss_macsec_dbg_reg_dump(board->inst, port_no, printf);
#endif
            } else if (strcmp(value_str, "test")  == 0) {
                page_no = VTSS_PHY_PAGE_TEST;
                vtss_phy_debug_regdump_print(board->inst, printf, port_no, page_no, print_hdr);
            } else if (strcmp(value_str, "tr")  == 0) {
                u16   reg16=0;
                u16   reg17=0;
                u16   reg18=0;

                page_no = VTSS_PHY_PAGE_TR;
                //vtss_phy_debug_regdump_print(board->inst, printf, port_no, page_no, print_hdr);
                // Read-modify-write word containing half_comp_en
                printf ("Port %d, Enter TR Address: (MUST be in Hex): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                reg16 = strtol(value_str, NULL, 16);
                rc = vtss_phy_read_tr_addr(board->inst, port_no, reg16, &reg17, &reg18);
                printf ("Port %d, TR Address (Reg16): 0x%04x,  Upper(Reg18): 0x%04x, Lower(Reg17): 0x%04x;    rc= 0x%x \n", port_no, reg16, reg18, reg17, rc);

            } else if (strcmp(value_str, "1588_rng")  == 0) {
                u16  start_reg = 0;
                u16  end_reg = 0;

                printf("1588v2 Page Register dump for port %d \n", port_no);
                printf ("Port %d, Enter Start Reg# (MUST be in Hex): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                start_reg = strtol(value_str, NULL, 16);
                printf ("Port %d, Enter Ending Reg# (MUST be in Hex): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                end_reg = strtol(value_str, NULL, 16);

                miim_write(board->inst, port_no, 31, VTSS_PHY_PAGE_1588);  /* 1588 Page  */
                for (addr = start_reg; addr < (end_reg + 1); addr++) {
                    miim_read(board->inst, port_no, addr, &value);
                    printf("0x%04xv2: 0x%04X \n", addr, value);
                }
                miim_write(board->inst, port_no, 31, VTSS_PHY_PAGE_STANDARD);  /* Std Page 0 */

            } else if (strcmp(value_str, "macsec_rng")  == 0) {
                u16  start_reg = 0;
                u16  end_reg = 0;

                printf("MACSEC Page Register dump for port %d \n", port_no);
                printf ("Port %d, Enter Start Reg# (MUST be in Hex): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                start_reg = strtol(value_str, NULL, 16);

                printf ("Port %d, Enter Ending Reg# (MUST be in Hex): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                end_reg = strtol(value_str, NULL, 16);

                miim_write(board->inst, port_no, 31, VTSS_PHY_PAGE_MACSEC);  /* MACSEC Page  */
                for (addr = start_reg; addr < (end_reg + 1); addr++) {
                    miim_read(board->inst, port_no, addr, &value);
                    printf("0x%04xM: 0x%04X \n", addr, value);
                }
                miim_write(board->inst, port_no, 31, VTSS_PHY_PAGE_STANDARD);  /* Std Page 0 */

            } else if (strcmp(value_str, "ext_rng")  == 0) {
                u16  ext_pg = 0;
                u16  start_reg = 0;
                u16  end_reg = 0;

                printf("Extended Page Register dump for port %d \n", port_no);
                printf ("Port %d, Enter Extended Page# (MUST be in Hex): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                ext_pg = strtol(value_str, NULL, 16);

                printf ("Port %d, Enter Start Reg# (MUST be in Hex): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                start_reg = strtol(value_str, NULL, 16);

                printf ("Port %d, Enter Ending Reg# (MUST be in Hex): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                end_reg = strtol(value_str, NULL, 16);

                miim_write(board->inst, port_no, 31, ext_pg);
                for (addr = start_reg; addr < (end_reg + 1); addr++) {
                    miim_read(board->inst, port_no, addr, &value);
                    printf("0x%04x: 0x%04X \n", addr, value);
                }
                miim_write(board->inst, port_no, 31, VTSS_PHY_PAGE_STANDARD);  /* Std Page 0 */

            } else {
                printf("Invalid Selection for port: %d \n", port_no);
            }

            continue;

        } else if (strcmp(command, "status")  == 0) {
            vtss_port_status_t status;
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            memset (&status, 0, sizeof(vtss_port_status_t));

            printf ("Port %d, Read Current PHY Status = Y ; Retrieve Status from Instance = N: (Y/N)", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            if (value_str[0] == 'n' || value_str[0] == 'N' ) {
                printf ("\nPort %d, Retrieving the Current PHY Status from the Instance \n", port_no);
                vtss_phy_status_inst_poll(board->inst, port_no, &status);
            } else {
                printf ("Port %d, Reading Current PHY Status from PHY Registers \n", port_no);
                vtss_phy_status_get(board->inst, port_no, &status);
            }

            if (status.link_down == 0) {
                printf("Link UP!  (status=%d) \n", status.link_down);
                if (status.link) {
                    printf("Link: 0x%x, Speed: 0x%x, FDX: 0x%x, Remote_Fault: 0x%x, ANEG_Complete: 0x%x, Fiber: 0x%x, Copper: 0x%x, MDI_Cross: 0x%x  \n",
                         status.link, status.speed, status.fdx, status.remote_fault, status.aneg_complete, status.fiber, status.copper, status.mdi_cross);
                }
            } else if (status.link_down == 1) {
                printf("Link DOWN!  (status=%d) \n", status.link_down);
                printf("Link: 0x%x, Speed: 0x%x, FDX: 0x%x, Remote_Fault: 0x%x, ANEG_Complete: 0x%x, Fiber: 0x%x, Copper: 0x%x, MDI_Cross: 0x%x  \n",
                         status.link, status.speed, status.fdx, status.remote_fault, status.aneg_complete, status.fiber, status.copper, status.mdi_cross);
            } else {
                printf("Link Status Unknown!  (status=%d) \n", status.link_down);
            }
            continue;

        } else if (strcmp(command, "lpstat")  == 0) {
            vtss_port_status_t status;
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("Port %d, Enter number of Loops to get status: ", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            value = atoi(value_str);

            printf ("Port %d, Number of Loops to get status: %d\n", port_no, value);

            do {
                vtss_phy_status_get(board->inst, port_no, &status);
                printf("Link: 0x%x, Speed: 0x%x, FDX: 0x%x, Remote_Fault: 0x%x, ANEG_Complete: 0x%x, Fiber: 0x%x, Copper: 0x%x, MDI_Cross: 0x%x  \n",
                         status.link, status.speed, status.fdx, status.remote_fault, status.aneg_complete, status.fiber, status.copper, status.mdi_cross);
                value--;
            } while (value > 0);

            continue;

        } else if (strcmp(command, "stats")  == 0) {
            vtss_port_status_t status;
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            vtss_phy_debug_stat_print(board->inst, printf, port_no, TRUE);
            printf ("\n\n");
            vtss_phy_debug_phyinfo_print(board->inst, printf, port_no, TRUE);
            continue;
        } else if (strcmp(command, "debug")  == 0) {
            vtss_port_status_t status;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

#ifdef _INCLUDE_DEBUG_TERM_PRINT_
            printf ("Enable Live Debug TERM Output? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            if (value_str[0] == 'y' || value_str[0] == 'Y' ) {
                live_debug_enable = TRUE;
            }
#endif
            continue;

        } else if (strcmp(command, "rst_lcpll")  == 0) {
            vtss_port_status_t status;
            rc = VTSS_RC_ERROR;
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            rc = vtss_phy_reset_lcpll(board->inst, port_no);
            if (rc == VTSS_RC_OK) {
                printf ("Port No: %d, Resetting LCPLL Successful \n", port_no);
            } else if (rc == VTSS_RC_ERR_PHY_BASE_NO_NOT_FOUND) {
                printf ("Port No: %d, Resetting LCPLL UnSuccessful - Not Base Port of PHY \n", port_no);
            } else {
                printf ("Port No: %d, Resetting LCPLL Failure, rc = %d \n", port_no, rc);
            }
            continue;

        } else if (strcmp(command, "getmedia")  == 0) {
            vtss_phy_reset_conf_t   phy_resetCfg;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            vtss_phy_reset_get(board->inst, port_no, &phy_resetCfg);

            p_mac_if_name = get_mac_if_name_by_mac_id( phy_resetCfg.mac_if );
            p_media_if_name = get_media_if_name_by_media_id( phy_resetCfg.media_if);

            if ((p_mac_if_name != NULL) && (p_media_if_name != NULL)) {
                printf ("Port No: %d, MAC I/F: %s     MEDIA I/F: %s \n", port_no,
                         p_mac_if_name, p_media_if_name);
            } else {
                printf ("Port No: %d, MAC I/F: 0x%x     MEDIA I/F: 0x%x \n", port_no,
                         phy_resetCfg.mac_if, phy_resetCfg.media_if);
            }

            continue;

        } else if (strcmp(command, "setmedia")  == 0) {
            vtss_phy_reset_conf_t   phy_resetCfg;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            vtss_phy_reset_get(board->inst, port_no, &phy_resetCfg);

            p_mac_if_name = get_mac_if_name_by_mac_id( phy_resetCfg.mac_if );
            p_media_if_name = get_media_if_name_by_media_id( phy_resetCfg.media_if);

            if ((p_mac_if_name != NULL) && (p_media_if_name != NULL)) {
                printf ("Port No: %d, MAC I/F: %s     MEDIA I/F: %s \n", port_no,
                         p_mac_if_name, p_media_if_name);
            } else {
                printf ("Port No: %d, MAC I/F: 0x%x     MEDIA I/F: 0x%x \n", port_no,
                         phy_resetCfg.mac_if, phy_resetCfg.media_if);
            }

            printf ("Enter MEDIA I/F Options for Port: %d \n", port_no);
            printf ("Copper Options: cu/sfppass/amscupass/amscu1000bx/amscu100fx \n");
            printf ("Fiber Options: fi1000bx/fi100fx/amsfipass/amsfi1000bx/amsfi100fx \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            p_media_if_name = get_media_if_name( value_str, &media_if);

            if (p_media_if_name == NULL) {
                printf ("Error Detected in MEDIA I/F Selection for Port: %d - Please Retry\n", port_no);
                continue;
            }

            phy_resetCfg.media_if = media_if;         // Set media interface
            vtss_phy_reset(board->inst, port_no, &phy_resetCfg);             // Do port reset

            /* For the Eval Board, Need to set SigDet When Fibre is selected */
            if ((media_if == VTSS_PHY_MEDIA_IF_FI_1000BX) || (media_if == VTSS_PHY_MEDIA_IF_FI_100FX)) {
                u16 addr=19;
                value = 0;
                miim_write(board->inst, port_no, 31, 0x1); /* Setup Page, Ext1 */
                miim_write(board->inst, port_no, addr, 0x0);
                miim_read(board->inst, port_no, addr, &value);
                miim_write(board->inst, port_no, 31, 0x0); /* Setup Page, Std */
                printf("\nSetting SigDet, Writing Addr:%02dE1 : Value:0x%04X \n", addr, value);

            }

            vtss_phy_conf_set(board->inst, port_no, &phy);

            vtss_phy_reset_get(board->inst, port_no, &phy_resetCfg);
            p_mac_if_name = get_mac_if_name_by_mac_id( phy_resetCfg.mac_if );
            p_media_if_name = get_media_if_name_by_media_id( phy_resetCfg.media_if);

            if ((p_mac_if_name != NULL) && (p_media_if_name != NULL)) {
                printf ("Port No: %d, MAC I/F: %s     Updated MEDIA I/F: %s \n", port_no,
                         p_mac_if_name, p_media_if_name);
            } else {
                printf ("Port No: %d, MAC I/F: 0x%x    Updated MEDIA I/F: 0x%x \n", port_no,
                         phy_resetCfg.mac_if, phy_resetCfg.media_if);
            }

            continue;

        } else if (strcmp(command, "getmac")  == 0) {
            vtss_phy_reset_conf_t   phy_resetCfg;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            vtss_phy_reset_get(board->inst, port_no, &phy_resetCfg);

            p_mac_if_name = get_mac_if_name_by_mac_id( phy_resetCfg.mac_if );
            p_media_if_name = get_media_if_name_by_media_id( phy_resetCfg.media_if);

            if ((p_mac_if_name != NULL) && (p_media_if_name != NULL)) {
                printf ("Port No: %d, MAC I/F: %s     MEDIA I/F: %s \n", port_no,
                         p_mac_if_name, p_media_if_name);
            } else {
                printf ("Port No: %d, MAC I/F: 0x%x     MEDIA I/F: 0x%x \n", port_no,
                         phy_resetCfg.mac_if, phy_resetCfg.media_if);
            }

            continue;

        } else if (strcmp(command, "setmac")  == 0) {
            vtss_phy_reset_conf_t   phy_resetCfg;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            vtss_phy_reset_get(board->inst, port_no, &phy_resetCfg);

            p_mac_if_name = get_mac_if_name_by_mac_id( phy_resetCfg.mac_if );
            p_media_if_name = get_media_if_name_by_media_id( phy_resetCfg.media_if);

            if ((p_mac_if_name != NULL) && (p_media_if_name != NULL)) {
                printf ("Port No: %d, MAC I/F: %s     MEDIA I/F: %s \n", port_no,
                         p_mac_if_name, p_media_if_name);
            } else {
                printf ("Port No: %d, MAC I/F: 0x%x     MEDIA I/F: 0x%x \n", port_no,
                         phy_resetCfg.mac_if, phy_resetCfg.media_if);
            }

            printf ("Enter MAC I/F Options for Port: %d \n", port_no);
            printf ("Options: rgmii/sgmii/qsgmii \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            p_mac_if_name = get_mac_if_name( value_str, &mac_if);

            if (p_mac_if_name == NULL) {
                printf ("Error Detected in MAC I/F Selection for Port: %d - Please Retry\n", port_no);
                continue;
            }

            phy_resetCfg.mac_if = mac_if;                                 // Set mac interface
            vtss_phy_reset(board->inst, port_no, &phy_resetCfg);          // Do port reset
            vtss_phy_conf_set(board->inst, port_no, &phy);

            vtss_phy_reset_get(board->inst, port_no, &phy_resetCfg);
            p_mac_if_name = get_mac_if_name_by_mac_id( phy_resetCfg.mac_if );
            p_media_if_name = get_media_if_name_by_media_id( phy_resetCfg.media_if);

            if ((p_mac_if_name != NULL) && (p_media_if_name != NULL)) {
                printf ("Port No: %d, Updated MAC I/F: %s    MEDIA I/F: %s \n", port_no,
                         p_mac_if_name, p_media_if_name);
            } else {
                printf ("Port No: %d, Updated MAC I/F: 0x%x    MEDIA I/F: 0x%x \n", port_no,
                         phy_resetCfg.mac_if, phy_resetCfg.media_if);
            }

            continue;

        } else if (strcmp(command, "loopback")  == 0) {
            vtss_port_status_t status;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            vtss_phy_status_get(board->inst, port_no, &status);
            if (status.link_down == 0) {
                printf("port: %d: Link UP! \n", port_no);
            } else if (status.link_down == 1) {
                printf("port: %d: Link DOWN! \n", port_no);
            } else {
                printf("port: %d: Link Status UNKNOWN! \n", port_no);
            }

            vtss_phy_loopback_get(board->inst, port_no, &loopback);

#ifdef EXTENDED_LOOPBACK
            printf ("Please Enter Loopback option (near/far/ext/macserd/mediaserd/none) for port %d \n", port_no);
#else
            printf ("Please Enter Loopback option (near/far/none) for port %d \n", port_no);
#endif
            memset (&value_str[0], '\0', sizeof(value_str));
            scanf("%s", &value_str[0]);


            if (strcmp(value_str, "near")  == 0) {
                vtss_phy_reset_conf_t   phy_resetCfg;

                printf ("Port %d, NEAR-End Loopback: Option (on/off) \n", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);

                if (strcmp(value_str, "on")  == 0) {
#if 0
                    vtss_phy_reset_get(board->inst, port_no, &phy_resetCfg);
                    if (phy_resetCfg.mac_if == VTSS_PHY_MEDIA_IF_FI_1000BX) {
                        vtss_phy_conf_get(board->inst, port_no, &phy);
                        prev_mode[port_no] = phy.mode;
                        phy.mode = VTSS_PHY_MODE_FORCED;
                        vtss_phy_conf_set(board->inst, port_no, &phy);
                    }
#endif
                    loopback.near_end_enable = TRUE;  // Set to TRUE for enabling Near End loopback

                } else {
#if 0
                    vtss_phy_reset_get(board->inst, port_no, &phy_resetCfg);
                    if (phy_resetCfg.mac_if == VTSS_PHY_MEDIA_IF_FI_1000BX) {
                        vtss_phy_conf_get(board->inst, port_no, &phy);
                        phy.mode = prev_mode[port_no];
                        vtss_phy_conf_set(board->inst, port_no, &phy);
                    }
#endif
                    loopback.near_end_enable = FALSE;  // Set to TRUE for enabling Near End loopback
                }

            } else if (strcmp(value_str, "far")  == 0) {
                printf ("Port %d, FAR-End Loopback: Option (on/off) \n", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);

                if (strcmp(value_str, "on")  == 0) {
                    loopback.far_end_enable  = TRUE;   // Set to TRUE for enabling Far End loopback
                } else {
                    loopback.far_end_enable  = FALSE;   // Set to TRUE for enabling Far End loopback
                }
#ifdef EXTENDED_LOOPBACK
            } else if (strcmp(value_str, "ext")  == 0) {
                printf ("\nPort %d, EXTernal Connector Loopback: Option (on/off) \n", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);

                if (strcmp(value_str, "on")  == 0) {
                    loopback.connector_enable = TRUE;
                } else {
                    loopback.connector_enable = FALSE;
                }

            } else if (strcmp(value_str, "macserd")  == 0) {
                printf ("\nPort %d, MAC-Side SERDES Loopback Options: none/input/fac/equip \n", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);

                if (strcmp(value_str, "input")  == 0) {
                    loopback.mac_serdes_input_enable = TRUE;
                    loopback.mac_serdes_facility_enable = FALSE;
                    loopback.mac_serdes_equipment_enable = FALSE;
                } else if (strcmp(value_str, "fac")  == 0) {
                    loopback.mac_serdes_facility_enable = TRUE;
                    loopback.mac_serdes_input_enable = FALSE;
                    loopback.mac_serdes_equipment_enable = FALSE;
                } else if (strcmp(value_str, "equip")  == 0) {
                    loopback.mac_serdes_equipment_enable = TRUE;
                    loopback.mac_serdes_input_enable = FALSE;
                    loopback.mac_serdes_facility_enable = FALSE;
                } else if (strcmp(value_str, "none")  == 0) {
                    loopback.mac_serdes_input_enable = FALSE;
                    loopback.mac_serdes_facility_enable = FALSE;
                    loopback.mac_serdes_equipment_enable = FALSE;
                }

            } else if (strcmp(value_str, "mediaserd")  == 0) {
                printf ("\nPort %d, Media-Side Fibre SERDES Loopback Options: none/input/fac/equip \n", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);

                if (strcmp(value_str, "input")  == 0) {
                    loopback.media_serdes_input_enable = TRUE;
                    loopback.media_serdes_facility_enable = FALSE;
                    loopback.media_serdes_equipment_enable = FALSE;
                } else if (strcmp(value_str, "fac")  == 0) {
                    loopback.media_serdes_facility_enable = TRUE;
                    loopback.media_serdes_input_enable = FALSE;
                    loopback.media_serdes_equipment_enable = FALSE;
                } else if (strcmp(value_str, "equip")  == 0) {
                    loopback.media_serdes_equipment_enable = TRUE;
                    loopback.media_serdes_input_enable = FALSE;
                    loopback.media_serdes_facility_enable = FALSE;
                } else if (strcmp(value_str, "none")  == 0) {
                    loopback.media_serdes_input_enable = FALSE;
                    loopback.media_serdes_facility_enable = FALSE;
                    loopback.media_serdes_equipment_enable = FALSE;
                }
#endif
            } else if (strcmp(value_str, "none")  == 0) {
                memset (&loopback, 0, sizeof (loopback));
            } else {
                continue; // Did not select an option, so don't change loopback settings
            }

#ifdef EXTENDED_LOOPBACK
            printf ("loopback for port:%d near=%x, far= %x, connector=%x \n",
                port_no, loopback.near_end_enable, loopback.far_end_enable, loopback.connector_enable);
            printf("loopback for port:%d mac_serd_input=%x, mac_serd_fac= %x, mac_serd_equip=%x \n",
                port_no, loopback.mac_serdes_input_enable, loopback.mac_serdes_facility_enable, loopback.mac_serdes_equipment_enable);
            printf("loopback for port:%d media_serd_input=%x, media_serd_fac= %x, media_serd_equip=%x \n",
                port_no, loopback.media_serdes_input_enable, loopback.media_serdes_facility_enable, loopback.media_serdes_equipment_enable);
#else
            printf ("loopback for port:%d near=%x, far= %x \n", port_no, loopback.near_end_enable, loopback.far_end_enable);
#endif
            vtss_phy_loopback_set(board->inst, port_no, loopback);

            continue;

        } else if (strcmp(command, "veriphy")  == 0) {
            vtss_phy_veriphy_result_t     diagResult;
            u8                            mode = 0;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("Port %d, VeriPhy: Option (run/result) \n", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);


           // mode = VERIPHY_MODE_FULL = 0;
           // mode = VERIPHY_MODE_ANOM_XPAIR = 1;
           // mode = VERIPHY_MODE_ANOM_ONLY = 2;
           // mode = 3 - both 1 & 2
            mode = 0;

            if (strcmp(value_str, "run")  == 0) {
                int sleepCnt = 0;
                int MaxSleepCnt = 10000; // It takes about 2400 iterations with 1msec sleep for good cable with no issues
                u8  pwrdn = 0;

                printf ("Port %d, VeriPhy: Power Down PHY Port while Veriphy Running? (Y/N) \n", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);

                if (value_str[0] == 'Y' || value_str[0] == 'y') {
                    pwrdn = 1;
                }

                rc = vtss_phy_veriphy_start (board->inst, port_no, mode);
                printf("VERIPHY Started on Port: %d, rc= %d \n", port_no, rc);

                while (sleepCnt < MaxSleepCnt) // Try Once per sec, up to MaxSleepCnt
                {
                    usleep(1000); // Sleep for 1000 usec or 1 msec
                    sleepCnt++;

                    if (pwrdn > 0) {
                        vtss_phy_conf_get(board->inst, port_no, &phy);
                        prev_mode[port_no] = phy.mode;
                        phy.mode = VTSS_PHY_MODE_POWER_DOWN;

                        printf("Powering Down PHY Port: %d\n", port_no);
                        vtss_phy_conf_set(board->inst, port_no, &phy);

                        miim_read(board->inst, port_no, 0x1, &value);
                        printf("Reading Reg%02d: Value:0x%04X \n", 0x1, value);

                        printf("Powering Up PHY Port: %d\n", port_no);
                        phy.mode = prev_mode[port_no];
                        vtss_phy_conf_set(board->inst, port_no, &phy);
                        miim_read(board->inst, port_no, 0x1, &value);
                        printf("Reading Reg%02d: Value:0x%04X \n", 0x1, value);
                        pwrdn = 0;
                    }

                    rc = vtss_phy_veriphy_get (board->inst, port_no, &diagResult);
                    if (rc == VTSS_RC_INCOMPLETE) {
                        continue;
                    } else if (rc == VTSS_RC_ERROR) {
                        printf("ERROR Detected in VERIPHY \n");
                        break;
                    } else if (rc == VTSS_RC_OK) {
                        printf("VERIPHY Complete! \n");
                        break;
                    }
                }

                printf("sleepCnt: %d \n", sleepCnt);

            } else {
                rc = vtss_phy_veriphy_get (board->inst, port_no, &diagResult);
            }

            printf("********** VERIPHY RESULTS ************* \n");
            printf("Port: %d, rc: %d, link:x%x \n", port_no, rc, diagResult.link);
            printf("Port: %d, Status Pair A:%s, B:%s, C:%s, D:%s \n", port_no,
                    convert_veriphy_status(diagResult.status[0]), convert_veriphy_status(diagResult.status[1]),
                    convert_veriphy_status(diagResult.status[2]), convert_veriphy_status(diagResult.status[3]) );
            printf("Port: %d, Cable Length (meters) A:%d B:%d, C:%d, D:%d\n", port_no,
                    diagResult.length[0], diagResult.length[1], diagResult.length[2], diagResult.length[3]);

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
            fprintf(fp,"********** VERIPHY RESULTS ************* \n");
            fprintf(fp,"Port: %d, rc: %d, link:x%x \n", port_no, rc, diagResult.link);
            fprintf(fp,"Port: %d, Status Pair A:%s, B:%s, C:%s, D:%s \n", port_no,
                    convert_veriphy_status(diagResult.status[0]), convert_veriphy_status(diagResult.status[1]),
                    convert_veriphy_status(diagResult.status[2]), convert_veriphy_status(diagResult.status[3]) );
            fprintf(fp,"Port: %d, Cable Length (meters) A:%d B:%d, C:%d, D:%d\n", port_no,
                    diagResult.length[0], diagResult.length[1], diagResult.length[2], diagResult.length[3]);

            fflush(fp);
#endif
            continue;

        } else if (strcmp(command, "temp")  == 0) {
            i16 temp;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            rc = vtss_phy_chip_temp_get (board->inst, port_no, &temp);


            printf("********** PHY TEMPERATURE *********** \n");
            printf("Port: %d, rc:x%x, PHY Temp: %d \n", port_no, rc, temp);

            continue;

        } else if (strcmp(command, "setrecovclk")  == 0) {
            vtss_phy_recov_clk_t   clock_port = VTSS_PHY_RECOV_CLK1;
            vtss_phy_clock_conf_t  clk_conf;
            vtss_port_no_t         clk_src = 0;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf("Getting Recovered Clock Reg:23G-24G dump for port %d \n", port_no);

            miim_write(board->inst, port_no, 31, VTSS_PHY_PAGE_GPIO);  /* GPIO Page  */
            for (addr = 23; addr < 25; addr++) {
                miim_read(board->inst, port_no, addr, &value);
                printf("%02dG: 0x%04X \n", addr, value);
            }
            miim_write(board->inst, port_no, 31, VTSS_PHY_PAGE_STANDARD);  /* Std Page 0 */

            clock_port = VTSS_PHY_RECOV_CLK1;
            rc = vtss_phy_clock_conf_get (board->inst, port_no, clock_port, &clk_conf, &clk_src);
            printf ("clk_port=VTSS_PHY_RECOV_CLK1 (Reg23G); clk_src=0x%x; conf_clk_src=0x%x; clk_freq=0x%x; clk_squelch=0x%x \n",
                     clk_src, clk_conf.src, clk_conf.freq, clk_conf.squelch);

            clock_port = VTSS_PHY_RECOV_CLK2;
            rc = vtss_phy_clock_conf_get (board->inst, port_no, clock_port, &clk_conf, &clk_src);
            printf ("clk_port=VTSS_PHY_RECOV_CLK2 (Reg24G); clk_src=0x%x; conf_clk_src=0x%x; clk_freq=0x%x; clk_squelch=0x%x \n",
                     clk_src, clk_conf.src, clk_conf.freq, clk_conf.squelch);

            printf ("Select Recovered Clock OUT 23G=0, 24G=1 <0-1>: \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            value = atoi(value_str);
            if (value == 0) {
                clock_port = VTSS_PHY_RECOV_CLK1;
            } else if (value == 1) {
                clock_port = VTSS_PHY_RECOV_CLK2;
            } else {
                clock_port = VTSS_PHY_RECOV_CLK1;
            }

            printf ("Reset Recovered Clock Settings to Default Config? <Y/N> \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if ((value_str[0] == 'Y') || (value_str[0] == 'y' )) {
                  clk_conf.src = VTSS_PHY_CLK_DISABLED;
                  clk_conf.freq = VTSS_PHY_FREQ_25M;
                  clk_conf.squelch = VTSS_PHY_CLK_SQUELCH_MAX;
            } else {

                printf ("Select Recovered Clock SRC: <0-4> 0=Disable, 1=SERDES_MEDIA, 2=COPPER_MEDIA, 3=TXCLK_OUT, 4=LOCAL_XTAL \n");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                value = atoi(value_str);

                if (value == 0) {
                    clk_conf.src = VTSS_PHY_CLK_DISABLED;
                } else if (value == 1) {
                    clk_conf.src = VTSS_PHY_SERDES_MEDIA;
                } else if (value == 2) {
                    clk_conf.src = VTSS_PHY_COPPER_MEDIA;
                } else if (value == 3) {
                    clk_conf.src = VTSS_PHY_TCLK_OUT;
                } else if (value == 4) {
                    clk_conf.src = VTSS_PHY_LOCAL_XTAL;
                } else {
                    clk_conf.src = VTSS_PHY_CLK_DISABLED;
                }

                printf ("Select Recovered Clock FREQ: <0-2> 0=25M, 1=125M, 2=31.25M \n");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                value = atoi(value_str);

                if (value == 0) {
                    clk_conf.freq = VTSS_PHY_FREQ_25M;
                } else if (value == 1) {
                    clk_conf.freq = VTSS_PHY_FREQ_125M;
                } else if (value == 2) {
                    clk_conf.freq = VTSS_PHY_FREQ_3125M;
                } else {
                    clk_conf.freq = VTSS_PHY_FREQ_25M;
                }

                printf ("Select Recovered Clock Squelch Level: <0-3> 0=NONE, 1=MIN, 2=MED, 3=MAX \n");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                value = atoi(value_str);

                if (value == 0) {
                    clk_conf.squelch = VTSS_PHY_CLK_SQUELCH_NONE;
                } else if (value == 1) {
                    clk_conf.squelch = VTSS_PHY_CLK_SQUELCH_MIN;
                } else if (value == 2) {
                    clk_conf.squelch = VTSS_PHY_CLK_SQUELCH_MED;
                } else if (value == 3) {
                    clk_conf.squelch = VTSS_PHY_CLK_SQUELCH_MAX;
                } else {
                    clk_conf.squelch = VTSS_PHY_CLK_SQUELCH_MAX;
                }
            }

            printf(" Port: %d, Recov Clk Port: %d, Src: %d, Freq: %d, Squelch: %d \n\n",
                  port_no, clock_port, clk_conf.src, clk_conf.freq, clk_conf.squelch);

            rc = vtss_phy_clock_conf_set (board->inst, port_no, clock_port, &clk_conf);

            printf("Getting Recovered Clock Reg:23G-24G dump for port %d \n", port_no);
            miim_write(board->inst, port_no, 31, VTSS_PHY_PAGE_GPIO);  /* GPIO Page  */
            for (addr = 23; addr < 25; addr++) {
                miim_read(board->inst, port_no, addr, &value);
                printf("%02dG: 0x%04X \n", addr, value);
            }
            miim_write(board->inst, port_no, 31, VTSS_PHY_PAGE_STANDARD);  /* Std Page 0 */

            rc = vtss_phy_clock_conf_get (board->inst, port_no, clock_port, &clk_conf, &clk_src);
            printf ("clk_port=0x%x; clk_src=0x%x; conf_clk_src=0x%x; clk_freq=0x%x; clk_squelch=0x%x \n",
                     clock_port, clk_src, clk_conf.src, clk_conf.freq, clk_conf.squelch);

            continue;

        } else if (strcmp(command, "powerdn")  == 0) {

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            vtss_phy_conf_get(board->inst, port_no, &phy);
            prev_mode[port_no] = phy.mode;
            phy.mode = VTSS_PHY_MODE_POWER_DOWN;

            vtss_phy_conf_set(board->inst, port_no, &phy);

            miim_read(board->inst, port_no, 0x1, &value);
            printf("%02d: 0x%04X \n", 0x1, value);
            continue;

        } else if (strcmp(command, "powerup")  == 0) {

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            vtss_phy_conf_get(board->inst, port_no, &phy);
            phy.mode = prev_mode[port_no];
            vtss_phy_conf_set(board->inst, port_no, &phy);
            continue;

        } else if (strcmp(command, "ms_config")  == 0) {
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }
            rc = vtss_phy_conf_1g_get(board->inst, port_no, &phy_1g);
            printf ("Port %d, Curr: Manual Enable(1=enable/0=disable): 0x%x;  Master/Slave(1=master, 0=slave): 0x%x\n\n", port_no, phy_1g.master.cfg, phy_1g.master.val);

            printf ("Port %d, Modify Current Values? (Y/N)\n", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == 'Y' || value_str[0] == 'y')
            {
                printf ("Port %d, Enter Manual Enable(1=enable, 0=disable): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == '1') {
                    phy_1g.master.cfg = 1;
                    printf ("Port %d, Manual Setting Enabled, Enter Master/Slave Config (1=Master, 0=Slave): ", port_no);
                    memset (&value_str[0], 0, sizeof(value_str));
                    scanf("%s", &value_str[0]);
                    if (value_str[0] == '1') {
                        phy_1g.master.val = 1;
                    } else {
                        phy_1g.master.val = 0;
                    }
                }
            }
            rc = vtss_phy_conf_1g_set(board->inst, port_no, &phy_1g);

            continue;

        } else if (strcmp(command, "intmask")  == 0) {
            vtss_phy_event_t      ev_mask;
            BOOL                  enable = TRUE;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            addr = 26;
            ev_mask=0;
            miim_read(board->inst, port_no, addr, &value);  /* Read 26 - INT Status */
            printf("Std Reg 26 (Int Status) dump for port %d, addr: %02d, value: 0x%04x \n", port_no, addr, value);
            addr = 29;
            ev_mask=0;
            miim_write(board->inst, port_no, 31, 0x2); /* Setup Page, Ext2 */
            miim_read(board->inst, port_no, addr, &value);  /* Read 29E2 - Extended INT Status */
            miim_write(board->inst, port_no, 31, 0x0); /* Setup Page, Std */
            printf("Std Reg 29E2 (Ext Int Status) dump for port %d, addr: %02d, value: 0x%04x \n", port_no, addr, value);
            rc = vtss_phy_event_enable_get(board->inst, port_no, &ev_mask);
            printf("vtss_phy_event_enable_get dump for port %d, ev_mask_value: 0x%04x \n", port_no, ev_mask);
            phy_process_event_poll(port_no, ev_mask);

            printf ("PHY Interrupt events \n");
            printf("VTSS_PHY_LINK_LOS_EV                    (0x00000001)(0) /**< PHY link interrupt */ \n");
            printf("VTSS_PHY_LINK_FFAIL_EV                  (0x00000002)(1) /**< PHY fast failure interrupt */ \n");
            printf("VTSS_PHY_LINK_AMS_EV                    (0x00000004)(2) /**< PHY Automatic Media Sense */ \n");
            printf("VTSS_PHY_LINK_SPEED_STATE_CHANGE_EV     (0x00000008)(3) /**< PHY link state change event*/ \n");
            printf("VTSS_PHY_LINK_FDX_STATE_CHANGE_EV       (0x00000010)(4) /**< PHY FDX state change event*/ \n");
            printf("VTSS_PHY_LINK_AUTO_NEG_ERROR_EV         (0x00000020)(5) /**< PHY Autonegotiation error event*/ \n");
            printf("VTSS_PHY_LINK_AUTO_NEG_COMPLETE_EV      (0x00000040)(6) /**< PHY Autonegotiation complete event*/ \n");
            printf("VTSS_PHY_LINK_INLINE_POW_DEV_DETECT_EV  (0x00000080)(7) /**< PHY Inline powered device detect event */ \n");
            printf("VTSS_PHY_LINK_SYMBOL_ERR_INT_EV         (0x00000100)(8) /**< PHY Symbol error event */ \n");
            printf("VTSS_PHY_LINK_TX_FIFO_OVERFLOW_INT_EV   (0x00000200)(9) /**< PHY TX fifo over/underflow detect event*/ \n");
            printf("VTSS_PHY_LINK_RX_FIFO_OVERFLOW_INT_EV   (0x00000400)(10) /**< PHY RX fifo over/underflow detect event*/ \n");
            printf("VTSS_PHY_LINK_FALSE_CARRIER_INT_EV      (0x00000800)(11) /**< PHY false-carrier interrupt event*/ \n");
            printf("VTSS_PHY_LINK_LINK_SPEED_DS_DETECT_EV   (0x00001000)(12) /**< PHY Link speed downshift detect event*/ \n");
            printf("VTSS_PHY_LINK_MASTER_SLAVE_RES_ERR_EV   (0x00002000)(13) /**< PHY master/salve resolution error event*/ \n");
            printf("VTSS_PHY_LINK_RX_ER_INT_EV              (0x00004000)(14) /**< PHY RX_ER interrupt event*/ \n");
            printf("VTSS_PHY_LINK_EXTENDED_REG_INT_EV       (0x00008000)(15) /**< PHY Use Extended Reg to Access interrupt event*/ \n");
            printf(" --------------------------------------------------------------------------------------- \n");
            printf ("PHY Ext Interrupt events \n");
            printf("VTSS_PHY_LINK_WAKE_ON_LAN_INT_EV        (0x00010000)(16) /**< PHY Wake-On-LAN interrupt event*/ \n");
            printf("VTSS_PHY_LINK_EXT_EEE_WAKE_ERR_EV       (0x00020000)(17) /**< PHY EEE Wake Error interrupt event*/ \n");
            printf("VTSS_PHY_LINK_EXT_EEE_WAIT_TS_EV        (0x00040000)(18) /**< PHY EEE Wait Quit/Rx TS Timer interrupt event*/ \n");
            printf("VTSS_PHY_LINK_EXT_EEE_WAIT_RX_TQ_EV     (0x00080000)(19) /**< PHY EEE Rx TQ Timer interrupt event*/ \n");
            printf("VTSS_PHY_LINK_EXT_EEE_LINKFAIL_EV       (0x00100000)(20) /**< PHY EEE Link Fail interrupt event*/ \n");
            printf("VTSS_PHY_LINK_EXT_RR_SW_COMPL_EV        (0x00200000)(21) /**< PHY Ring Resiliancy Switchover complete interrupt event*/ \n");
            printf("VTSS_PHY_LINK_EXT_MACSEC_HOST_MAC_EV    (0x00400000)(22) /**< PHY MACSEC Host MAC interrupt event*/ \n");
            printf("VTSS_PHY_LINK_EXT_MACSEC_LINE_MAC_EV    (0x00800000)(23) /**< PHY MACSEC Line MAC interrupt event*/ \n");
            printf("VTSS_PHY_LINK_EXT_MACSEC_FC_BUFF_EV     (0x01000000)(24) /**< PHY MACSEC Flow Control Buff interrupt event*/ \n");
            printf("VTSS_PHY_LINK_EXT_MACSEC_INGRESS_EV     (0x02000000)(25) /**< PHY MACSEC Ingress interrupt event*/ \n");
            printf("VTSS_PHY_LINK_EXT_MACSEC_EGRESS_EV      (0x04000000)(26) /**< PHY MACSEC Egress interrupt event*/ \n");
            printf("VTSS_PHY_LINK_EXT_MEM_INT_RING_EV       (0x08000000)(27) /**< PHY MEM Integrity Ring Control interrupt event*/ \n");

            ev_mask=0;
            printf ("Please Enter Event_Mask Value (in Hex) to enable Event for port %d : ", port_no);
            scanf("%s", &value_str[0]);
            ev_mask = strtol(value_str, NULL, 16);

            printf ("Port_No: %d, Please Enter Disble=0/Enable=1 for EventMask: 0x%04X;  Enter 0/1: \n", port_no, ev_mask);
            scanf("%s", &value_str[0]);
            enable = atoi(value_str);

            rc = vtss_phy_event_enable_set(board->inst, port_no, ev_mask, enable);
            if (rc == VTSS_RC_OK) {
                 printf("Setting Events - Int MASK for Port:%d,  0x%08x - OK \n", port_no, ev_mask);
            } else {
                 printf("ERROR:  Setting Events - Int MASK for Port:%d,  ERROR: rc= %d\n", port_no, rc);
            }

            addr = 25;
            ev_mask=0;
            miim_read(board->inst, port_no, addr, &value);
            printf("Std Reg 25 (Int Mask) dump for port %d, addr: %02d, value: 0x%04x \n", port_no, addr, value);
            addr = 28;
            miim_write(board->inst, port_no, 31, 0x2); /* Setup Page, Ext2 */
            miim_read(board->inst, port_no, addr, &value);
            miim_write(board->inst, port_no, 31, 0x0); /* Setup Page, Std */
            printf("Ext2 Reg 28 (Ext Int Mask) dump for port %d, addr: %02d, value: 0x%04x \n", port_no, addr, value);

            rc = vtss_phy_event_enable_get(board->inst, port_no, &ev_mask);
            printf("vtss_phy_event_enable_get dump for port %d, ev_mask_value: 0x%04x \n", port_no, ev_mask);
            phy_process_event_poll(port_no, ev_mask);
            continue;

        } else if (strcmp(command, "intstat")  == 0) {
            vtss_phy_event_t      event;
            BOOL                  is_viper_revB = FALSE;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            rc = vtss_phy_event_poll(board->inst, port_no, &event);

            if (rc == VTSS_RC_OK) {
                printf("Polling Events - Int MASK for Port:%d,  OK \n", port_no);

                if (event & VTSS_PHY_LINK_LOS_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_LOS_EV \n");
                }
                if (event & VTSS_PHY_LINK_FFAIL_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_FFAIL_EV \n");
                }
                if (event & VTSS_PHY_LINK_AMS_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_AMS_EV \n");
                }
                if (event & VTSS_PHY_LINK_SPEED_STATE_CHANGE_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_SPEED_STATE_CHANGE_EV \n");
                }
                if (event & VTSS_PHY_LINK_FDX_STATE_CHANGE_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_FDX_STATE_CHANGE_EV \n");
                }
                if (event & VTSS_PHY_LINK_AUTO_NEG_ERROR_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_AUTO_NEG_ERROR_EV \n");
                }
                if (event & VTSS_PHY_LINK_AUTO_NEG_COMPLETE_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_AUTO_NEG_COMPLETE_EV \n");
                }
                if (event & VTSS_PHY_LINK_INLINE_POW_DEV_DETECT_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_INLINE_POW_DEV_DETECT_EV \n");
                }
                if (event & VTSS_PHY_LINK_SYMBOL_ERR_INT_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_SYMBOL_ERR_INT_EV \n");
                }
                if (event & VTSS_PHY_LINK_TX_FIFO_OVERFLOW_INT_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_TX_FIFO_OVERFLOW_INT_EV \n");
                }
                if (event & VTSS_PHY_LINK_RX_FIFO_OVERFLOW_INT_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_RX_FIFO_OVERFLOW_INT_EV \n");
                }
                if (event & VTSS_PHY_LINK_FALSE_CARRIER_INT_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_FALSE_CARRIER_INT_EV \n");
                }
                if (event & VTSS_PHY_LINK_LINK_SPEED_DS_DETECT_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_LINK_SPEED_DS_DETECT_EV \n");
                }
                if (event & VTSS_PHY_LINK_MASTER_SLAVE_RES_ERR_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_MASTER_SLAVE_RES_ERR_EV \n");
                }
                if (event & VTSS_PHY_LINK_RX_ER_INT_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_RX_ER_INT_EV \n");
                }
                if (event & VTSS_PHY_LINK_EXTENDED_REG_INT_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_EXTENDED_REG_INT_EV \n");
                }
                if (event & VTSS_PHY_LINK_WAKE_ON_LAN_INT_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_WAKE_ON_LAN_INT_EV \n");
                }
                if (event & VTSS_PHY_LINK_EXT_EEE_WAKE_ERR_EV) {
                    printf("Event: VTSS_PHY_LINK_EXT_EEE_WAKE_ERR_EV  \n");
                }
                if (event & VTSS_PHY_LINK_EXT_EEE_WAIT_TS_EV) {
                    printf("Event: VTSS_PHY_LINK_EXT_EEE_WAIT_TS_EV   \n");
                }
                if (event & VTSS_PHY_LINK_EXT_EEE_WAIT_RX_TQ_EV) {
                    printf("Event: VTSS_PHY_LINK_EXT_EEE_WAIT_RX_TQ_EV\n");
                }
                if (event & VTSS_PHY_LINK_EXT_EEE_LINKFAIL_EV) {
                    printf("Event: VTSS_PHY_LINK_EXT_EEE_LINKFAIL_EV  \n");
                }
                if (event & VTSS_PHY_LINK_EXT_RR_SW_COMPL_EV ) {
                    printf("Event: VTSS_PHY_LINK_EXT_RR_SW_COMPL_EV   \n");
                }
                if (event & VTSS_PHY_LINK_EXT_MACSEC_HOST_MAC_EV) {
                    printf("Event: VTSS_PHY_LINK_EXT_MACSEC_HOST_MAC_EV  \n");
                }
                if (event & VTSS_PHY_LINK_EXT_MACSEC_LINE_MAC_EV) {
                    printf("Event: VTSS_PHY_LINK_EXT_MACSEC_LINE_MAC_EV  \n");
                }
                if (event & VTSS_PHY_LINK_EXT_MACSEC_FC_BUFF_EV ) {
                    printf("Event: VTSS_PHY_LINK_EXT_MACSEC_FC_BUFF_EV   \n");
                }
                if (event & VTSS_PHY_LINK_EXT_MACSEC_INGRESS_EV ) {
                    printf("Event: VTSS_PHY_LINK_EXT_MACSEC_INGRESS_EV   \n");
                }
                if (event & VTSS_PHY_LINK_EXT_MACSEC_EGRESS_EV ) {
                    printf("Event: VTSS_PHY_LINK_EXT_MACSEC_EGRESS_EV   \n");
                }
                if (event & VTSS_PHY_LINK_EXT_MEM_INT_RING_EV) {
                    printf("Event: VTSS_PHY_LINK_EXT_MEM_INT_RING_EV  \n");
                }
            } else {
                printf("ERROR:  Polling Events - Int MASK for Port:%d,  ERROR: rc= %d\n", port_no, rc);
            }


            rc = vtss_phy_is_viper_revB(board->inst, port_no, &is_viper_revB);
            if (!is_viper_revB) {  /* For Viper Rev B, We have to Poll for the Reg29E2 Values because EXT INT is Masked OFF in Reg25 - INT MASK */
                continue;
            }


            if (rc == VTSS_RC_OK) {
                printf("Polling Events - Int MASK for Port:%d,  OK \n", port_no);

                if (event & VTSS_PHY_LINK_LOS_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_LOS_EV \n");
                }
                if (event & VTSS_PHY_LINK_FFAIL_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_FFAIL_EV \n");
                }
                if (event & VTSS_PHY_LINK_AMS_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_AMS_EV \n");
                }
                if (event & VTSS_PHY_LINK_SPEED_STATE_CHANGE_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_SPEED_STATE_CHANGE_EV \n");
                }
                if (event & VTSS_PHY_LINK_FDX_STATE_CHANGE_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_FDX_STATE_CHANGE_EV \n");
                }
                if (event & VTSS_PHY_LINK_AUTO_NEG_ERROR_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_AUTO_NEG_ERROR_EV \n");
                }
                if (event & VTSS_PHY_LINK_AUTO_NEG_COMPLETE_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_AUTO_NEG_COMPLETE_EV \n");
                }
                if (event & VTSS_PHY_LINK_INLINE_POW_DEV_DETECT_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_INLINE_POW_DEV_DETECT_EV \n");
                }
                if (event & VTSS_PHY_LINK_SYMBOL_ERR_INT_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_SYMBOL_ERR_INT_EV \n");
                }
                if (event & VTSS_PHY_LINK_TX_FIFO_OVERFLOW_INT_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_TX_FIFO_OVERFLOW_INT_EV \n");
                }
                if (event & VTSS_PHY_LINK_RX_FIFO_OVERFLOW_INT_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_RX_FIFO_OVERFLOW_INT_EV \n");
                }
                if (event & VTSS_PHY_LINK_FALSE_CARRIER_INT_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_FALSE_CARRIER_INT_EV \n");
                }
                if (event & VTSS_PHY_LINK_LINK_SPEED_DS_DETECT_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_LINK_SPEED_DS_DETECT_EV \n");
                }
                if (event & VTSS_PHY_LINK_MASTER_SLAVE_RES_ERR_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_MASTER_SLAVE_RES_ERR_EV \n");
                }
                if (event & VTSS_PHY_LINK_RX_ER_INT_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_RX_ER_INT_EV \n");
                }
                if (event & VTSS_PHY_LINK_EXTENDED_REG_INT_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_EXTENDED_REG_INT_EV \n");
                }
                if (event & VTSS_PHY_LINK_WAKE_ON_LAN_INT_EV) {
                    printf("Event Detected: VTSS_PHY_LINK_WAKE_ON_LAN_INT_EV \n");
                }
                if (event & VTSS_PHY_LINK_EXT_EEE_WAKE_ERR_EV) {
                    printf("Event: VTSS_PHY_LINK_EXT_EEE_WAKE_ERR_EV  \n");
                }
                if (event & VTSS_PHY_LINK_EXT_EEE_WAIT_TS_EV) {
                    printf("Event: VTSS_PHY_LINK_EXT_EEE_WAIT_TS_EV   \n");
                }
                if (event & VTSS_PHY_LINK_EXT_EEE_WAIT_RX_TQ_EV) {
                    printf("Event: VTSS_PHY_LINK_EXT_EEE_WAIT_RX_TQ_EV\n");
                }
                if (event & VTSS_PHY_LINK_EXT_EEE_LINKFAIL_EV) {
                    printf("Event: VTSS_PHY_LINK_EXT_EEE_LINKFAIL_EV  \n");
                }
                if (event & VTSS_PHY_LINK_EXT_RR_SW_COMPL_EV ) {
                    printf("Event: VTSS_PHY_LINK_EXT_RR_SW_COMPL_EV   \n");
                }
                if (event & VTSS_PHY_LINK_EXT_MACSEC_HOST_MAC_EV) {
                    printf("Event: VTSS_PHY_LINK_EXT_MACSEC_HOST_MAC_EV  \n");
                }
                if (event & VTSS_PHY_LINK_EXT_MACSEC_LINE_MAC_EV) {
                    printf("Event: VTSS_PHY_LINK_EXT_MACSEC_LINE_MAC_EV  \n");
                }
                if (event & VTSS_PHY_LINK_EXT_MACSEC_FC_BUFF_EV ) {
                    printf("Event: VTSS_PHY_LINK_EXT_MACSEC_FC_BUFF_EV   \n");
                }
                if (event & VTSS_PHY_LINK_EXT_MACSEC_INGRESS_EV ) {
                    printf("Event: VTSS_PHY_LINK_EXT_MACSEC_INGRESS_EV   \n");
                }
                if (event & VTSS_PHY_LINK_EXT_MACSEC_EGRESS_EV ) {
                    printf("Event: VTSS_PHY_LINK_EXT_MACSEC_EGRESS_EV   \n");
                }
                if (event & VTSS_PHY_LINK_EXT_MEM_INT_RING_EV) {
                    printf("Event: VTSS_PHY_LINK_EXT_MEM_INT_RING_EV  \n");
                }
            } else {
                printf("ERROR:  Polling Events - Int MASK for Port:%d,  ERROR: rc= %d\n", port_no, rc);
            }

            continue;

#if defined (NANO_EVAL_BOARD)
        } else if (strcmp(command, "wol")  == 0) {
            printf ("\n\n\n\n");
            printf (" enwol   <port_no> - Enable/Disable Wake-On-LAN for Port \n");
            printf (" getwol  <port_no> - Get Wake-On-LAN info for Port \n");
            printf (" setwol  <port_no> - Set Wake-On-LAN info for Port \n");
            printf ("> ");
            rc = scanf("%s", &command[0]);

            if (strcmp(command, "enwol")  == 0) {
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }
                printf ("Port %d, Enable Wake-On-LAN for Port, Enter (Y/N)) \n", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);

                if ((strcmp(value_str, "Y")  == 0) || (strcmp(value_str, "y")  == 0)) {
                    printf("Enabling Wake-On_LAN for port %d \n", port_no);
                    rc = vtss_phy_wol_enable(board->inst, port_no, TRUE);
                } else {
                    printf("Disabling Wake-On_LAN for port %d \n", port_no);
                    rc = vtss_phy_wol_enable(board->inst, port_no, FALSE);
                }
                printf("WOL: vtss_phy_wol_enable  rtn code = %d \n", rc);
                continue;

            } else if (strcmp(command, "getwol")  == 0) {
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }
                rc = vtss_phy_wol_conf_get(board->inst, port_no, &wol_config);
                printf("Secure_On_Enable:%s\n", wol_config.secure_on_enable == 0 ? "NO":"YES");
                printf("Magic Packet Cnt:%d\n", wol_config.magic_pkt_cnt);
                printf("WOL MAC Addr: %x:%x:%x:%x:%x:%x\n", wol_config.wol_mac.addr[5], wol_config.wol_mac.addr[4],
                                                        wol_config.wol_mac.addr[3], wol_config.wol_mac.addr[2],
                                                        wol_config.wol_mac.addr[1], wol_config.wol_mac.addr[0] );

                if (wol_config.wol_passwd_len == VTSS_WOL_PASSWD_LEN_6) {
                    printf("WOL PASSWORD: %x:%x:%x:%x:%x:%x\n", wol_config.wol_pass.passwd[5],
                                                            wol_config.wol_pass.passwd[4],
                                                            wol_config.wol_pass.passwd[3],
                                                            wol_config.wol_pass.passwd[2],
                                                            wol_config.wol_pass.passwd[1],
                                                            wol_config.wol_pass.passwd[0] );

                } else if (wol_config.wol_passwd_len == VTSS_WOL_PASSWD_LEN_4) {
                    printf("WOL PASSWORD: %x:%x:%x:%x\n", wol_config.wol_pass.passwd[3], wol_config.wol_pass.passwd[2],
                                                      wol_config.wol_pass.passwd[1], wol_config.wol_pass.passwd[0]);
                } else {
                    printf("WOL Passwd Len INVALID\n");
                }
                printf("WOL: vtss_phy_wol_conf_set  rtn code = %d \n", rc);
                continue;

            } else if (strcmp(command, "setwol")  == 0) {
                int    index;
                int    tmp_size = 0;
                char * token;
                const char delim[2] = ".";

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }
                printf ("Port %d, Secure_On_Enable for Wake-On-LAN for Port, Enter (Y/N) \n", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);

                if ((strcmp(value_str, "Y")  == 0) || (strcmp(value_str, "y")  == 0)) {
                    wol_config.secure_on_enable = 1;
                } else {
                    wol_config.secure_on_enable = 0;
                }

                printf ("Port %d, Enter Magic Packet Repetition Count for Wake-On-LAN for Port, (1-16) \n", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                wol_config.magic_pkt_cnt = atoi(value_str);

                printf ("Port %d, Enter MAC Address for Wake-On-LAN for Port, (uu.vv.ww.xx.yy.zz) \n", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                token = strtok(value_str, delim);

                // The WOL MAC ADDR is setup to be bits 47..0
                for (index = 0; index < MAX_WOL_MAC_ADDR_SIZE; index++)
                {
                    if (token == NULL) {
                        break;
                    }
                    wol_config.wol_mac.addr[(MAX_WOL_MAC_ADDR_SIZE-1) - index] = strtol(token, NULL, 16);
                    token = strtok(NULL, delim);
                }

                printf("WOL MAC Addr: %x:%x:%x:%x:%x:%x\n", wol_config.wol_mac.addr[5], wol_config.wol_mac.addr[4],
                                                        wol_config.wol_mac.addr[3], wol_config.wol_mac.addr[2],
                                                        wol_config.wol_mac.addr[1], wol_config.wol_mac.addr[0] );

                if (wol_config.secure_on_enable) {
                    int wol_password_sz = MAX_WOL_PASSWD_SIZE;
                    printf ("Port %d, Enter Security Password Length for Wake-On-LAN for Port, (4 or 6) \n", port_no);
                    memset (&value_str[0], 0, sizeof(value_str));
                    scanf("%s", &value_str[0]);
                    wol_config.wol_passwd_len = VTSS_WOL_PASSWD_LEN_6;
                    value = atoi(value_str);
                    if (value == 4) {
                        wol_config.wol_passwd_len = VTSS_WOL_PASSWD_LEN_4;
                        wol_password_sz = MIN_WOL_PASSWD_SIZE;
                        printf ("Port %d, Enter Security Passwd for Wake-On-LAN for Port, (ww.xx.yy.zz) \n", port_no);
                    } else {
                        printf ("Port %d, Enter Security Passwd for Wake-On-LAN for Port, (uu.vv.ww.xx.yy.zz) \n", port_no);
                    }

                    memset (&value_str[0], 0, sizeof(value_str));
                    scanf("%s", &value_str[0]);
                    token = strtok(value_str, delim);

                    // The WOL Passwd is setup to be bits 47..0, so the order has to be flipped
                    for (index = 0; index < wol_password_sz; index++)
                    {
                        if (token == NULL) {
                            break;
                        }
                        wol_config.wol_pass.passwd[(wol_password_sz-1) - index] = strtol(token, NULL, 16);
                        token = strtok(NULL, delim);
                    }

                    if (wol_config.wol_passwd_len == VTSS_WOL_PASSWD_LEN_4) {
                        printf("WOL PASSWORD: %x:%x:%x:%x\n", wol_config.wol_pass.passwd[3],
                                                          wol_config.wol_pass.passwd[2],
                                                          wol_config.wol_pass.passwd[1],
                                                          wol_config.wol_pass.passwd[0]);
                    } else {
                        printf("WOL PASSWORD: %x:%x:%x:%x:%x:%x\n", wol_config.wol_pass.passwd[5],
                                                                wol_config.wol_pass.passwd[4],
                                                                wol_config.wol_pass.passwd[3],
                                                                wol_config.wol_pass.passwd[2],
                                                                wol_config.wol_pass.passwd[1],
                                                                wol_config.wol_pass.passwd[0] );
                    }
                }
                rc = vtss_phy_wol_conf_set(board->inst, port_no, &wol_config);
                printf("SET:  vtss_phy_wol_conf_set  rtn code = %d \n", rc);

                rc = vtss_phy_wol_conf_get(board->inst, port_no, &wol_config);
                printf("GET: Secure_On_Enable:%s\n", wol_config.secure_on_enable == 0 ? "NO":"YES");
                printf("GET: Magic Packet Cnt:%d\n", wol_config.magic_pkt_cnt);
                printf("GET: WOL MAC Addr: %x:%x:%x:%x:%x:%x\n", wol_config.wol_mac.addr[5], wol_config.wol_mac.addr[4],
                                                             wol_config.wol_mac.addr[3], wol_config.wol_mac.addr[2],
                                                             wol_config.wol_mac.addr[1], wol_config.wol_mac.addr[0] );
                if (wol_config.wol_passwd_len == VTSS_WOL_PASSWD_LEN_6) {
                    printf("GET: WOL PASSWORD: %x:%x:%x:%x:%x:%x\n", wol_config.wol_pass.passwd[5],
                                                                 wol_config.wol_pass.passwd[4],
                                                                 wol_config.wol_pass.passwd[3],
                                                                 wol_config.wol_pass.passwd[2],
                                                                 wol_config.wol_pass.passwd[1],
                                                                 wol_config.wol_pass.passwd[0] );
                } else if (wol_config.wol_passwd_len == VTSS_WOL_PASSWD_LEN_4) {
                    printf("GET: WOL PASSWORD: %x:%x:%x:%x\n", wol_config.wol_pass.passwd[3],
                                                           wol_config.wol_pass.passwd[2],
                                                           wol_config.wol_pass.passwd[1],
                                                           wol_config.wol_pass.passwd[0]);
                } else {
                    printf("GET: WOL Passwd Len INVALID\n");
                }
                printf("GET: vtss_phy_wol_conf_get  rtn code = %d \n", rc);
                continue;

           } else {
                continue;
           }
#endif  // End of #if defined (NANO_EVAL_BOARD)

#if defined (VTSS_FEATURE_EEE) && defined (VTSS_SW_OPTION_EEE)
        } else if (strcmp(command, "eee")  == 0) {
            printf (" eee_en   <port_no> - Enable EEE for Port \n");
            printf (" get_eee   <port_no> - Get EEE Config for Port \n");
            printf (" set_eee   <port_no> - Set EEE Config for Port \n");
            printf ("> ");
            rc = scanf("%s", &command[0]);

            if (strcmp(command, "eee_en")  == 0) {
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }
                printf ("Port %d, Enable EEE for Port, Enter (Y/N)) \n", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);

                if ((strcmp(value_str, "Y")  == 0) || (strcmp(value_str, "y")  == 0)) {
                    printf("Enabling EEE for port %d \n", port_no);
                    rc = vtss_phy_eee_ena(board->inst, port_no, TRUE);
                } else {
                    printf("Disabling EEE for port %d \n", port_no);
                    rc = vtss_phy_eee_ena(board->inst, port_no, FALSE);
                }

                continue;

            } else if (strcmp(command, "get_eee")  == 0) {
                u8  advertisements = 0;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }
                rc = vtss_phy_eee_conf_get(board->inst, port_no, &eee_conf);
                if (eee_conf.eee_mode ==  EEE_DISABLE) {
                    printf("EEE for port %d is: DISABLED, Current State in PHY: %x \n", port_no, eee_conf.eee_ena_phy );
                } else if (eee_conf.eee_mode ==  EEE_ENABLE) {
                    printf("EEE for port %d is: ENABLED, Current State in PHY: %x  \n", port_no, eee_conf.eee_ena_phy );
                } else if (eee_conf.eee_mode ==  EEE_REG_UPDATE) {
                    printf("EEE for port %d is: REG_UPATE, Current State in PHY: %x  \n", port_no, eee_conf.eee_ena_phy );
                } else {
                    printf("EEE for port %d is: Unknown, Mode= %x;  Current State in PHY: %x\n",
                         port_no, eee_conf.eee_mode, eee_conf.eee_ena_phy );
                }

// * \param advertisement[OUT]  Advertisement bit mask.
// *                             Bit 0 = Link partner advertises 100BASE-T capability.
// *                             Bit 1 = Link partner advertises 1000BASE-T capability.

                rc = vtss_phy_eee_link_partner_advertisements_get(board->inst, port_no, &advertisements);
                printf("EEE Link Partner for port %d has Advertisements of:  0x%x\n", port_no, advertisements);

                continue;

            } else if (strcmp(command, "set_eee")  == 0) {
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }
                rc = vtss_phy_eee_conf_set(board->inst, port_no, eee_conf);

                printf("EEE Set EEE *** NOT IMPLEMENTED *** \n");

                continue;
            } else {
                continue;
            }
#endif  // End of EEE

#ifdef VTSS_FEATURE_PHY_TIMESTAMP  // Is Timestamp code compiled into the build
#ifdef  EVAL_BOARD_1588_CAPABLE    // 1588 and MACSec get #ifdef'd because they are completely seperate Modules, not in vtss_phy.c
        } else if (strcmp(command, "1588")  == 0) {
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("Port %d", port_no);
#if 1
#ifdef  EVAL_BOARD_1588_CAPABLE    // 1588 and MACSec get #ifdef'd because they are completely seperate Modules
            printf ("Configure 1588 Block? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            if (value_str [0] == 'y' || value_str [0] == 'Y' ) {
                vtss_appl_ts_demo_menu(board->inst, port_no);
            }
#endif // EVAL_BOARD_1588_CAPABLE
#endif // if 1

            continue;
#endif // EVAL_BOARD_1588_CAPABLE
#endif // VTSS_FEATURE_PHY_TIMESTAMP


#ifdef VTSS_FEATURE_MACSEC
#ifdef EVAL_BOARD_MACSEC_CAPABLE  // 1588 and MACSec get #ifdef'd because they are completely seperate Modules, not in vtss_phy.c

        } else if (strcmp(command, "macsec")  == 0) {
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("Port %d", port_no);
#if 1
            printf ("Configure MACSEC Block? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            if (value_str [0] == 'y' || value_str [0] == 'Y' ) {
                vtss_appl_macsec_demo_menu(board->inst, port_no);
            }
#endif
            continue;

#endif  // End of EVAL_BOARD_MACSEC_CAPABLE
#endif // VTSS_FEATURE_MACSEC

        } else if (strcmp(command, "amssetup") == 0) {
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }
            phy_ams_setup(board);
            continue;

        } else if (strcmp(command, "amstest") == 0) {
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }
            phy_ams_test(board);
            continue;

        } else if (strcmp(command, "prereset") == 0) {
            BOOL all_ports = FALSE;
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                all_ports = TRUE;
            }

            if (all_ports) {
                for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS; port_no++) {
                    printf ("Step 2: Running PHY vtss_phy_pre_reset on port: %d\n", port_no);
                    rc = vtss_phy_pre_reset(board->inst, port_no);
                    if (rc != VTSS_RC_OK) {
                        printf ("//>>>>>> ERROR DETECTED <<<<<<<< During PHY pre-reset, rc = %d\n", rc);
                    } else {
                        printf ("PHY pre-reset: OK, rc = %d\n", rc);
                    }
                }
            } else {
                printf ("Step 2: Running PHY vtss_phy_pre_reset on port: %d\n", port_no);
                rc = vtss_phy_pre_reset(board->inst, port_no);
                if (rc != VTSS_RC_OK) {
                    printf ("//>>>>>> ERROR DETECTED <<<<<<<< During PHY pre-reset, rc = %d\n", rc);
                } else {
                    printf ("PHY pre-reset: OK, rc = %d\n", rc);
                }
            }

            continue;

        } else if (strcmp(command, "phyreset") == 0) {
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("PHY Reset Get for Port: %d\n", port_no);
            rc = vtss_phy_reset_get(board->inst, port_no, &phy_reset); // Do port reset

            printf ("\nPort %d, PHY Reset Options: \n", port_no);
            printf ("\nPort %d, Enter Force Options: (0=force; 1=NoForce): ", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == '1') {
                phy_reset.force = VTSS_PHY_NOFORCE_RESET;
            } else {
                phy_reset.force = VTSS_PHY_FORCE_RESET;
            }

            printf ("Running PHY Reset for Port: %d\n", port_no);
            rc = vtss_phy_reset(board->inst, port_no, &phy_reset); // Do port reset
            if (rc != VTSS_RC_OK) {
                printf ("//ERROR DETECTED during PHY post-reset, rc = %d\n", rc);
            }
            continue;

       } else if (strcmp(command, "postreset") == 0) {
            BOOL all_ports = FALSE;
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                all_ports = TRUE;
            }

            if (all_ports) {
                for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS; port_no++) {
                    printf ("Last_Step: Running PHY vtss_phy_post_reset on port %d\n", port_no);
                    rc = vtss_phy_post_reset(board->inst, port_no);
                    if (rc != VTSS_RC_OK) {
                        printf ("//>>>>>> ERROR DETECTED <<<<<<<< During PHY post-reset, rc = %d\n", rc);
                    } else {
                        printf ("PHY post-reset: OK, rc = %d\n", rc);
                    }
                }
            } else {
                printf ("Last_Step: Running PHY vtss_phy_post_reset on port %d\n", port_no);
                rc = vtss_phy_post_reset(board->inst, port_no);
                if (rc != VTSS_RC_OK) {
                    printf ("//>>>>>> ERROR DETECTED <<<<<<<< During PHY post-reset, rc = %d\n", rc);
                } else {
                    printf ("PHY post-reset: OK, rc = %d\n", rc);
                }
            }

            continue;

       } else if (strcmp(command, "powercfg") == 0) {
            u32                    idx = 0;
            vtss_phy_power_conf_t  pwr_cfg;
            vtss_phy_conf_t        phy_cfg;
            vtss_port_status_t     status;
            int max_loops = 100; // 100msecs per loop
            int loops = 0;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("\nPort %d, Power Config Options: off, act=ActiPHY/perf=PerfectReach/all=ActiPHY+PerfectReach \n", port_no);
            printf ("\nPort %d, Enter Power Options: off/act/perf/all \n", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            // Must call status_get to for Link Down Event to occur
            vtss_phy_status_get(board->inst, port_no, &status);
            if (status.link_down == 0) {
                printf("Link UP! \n");
            } else if (status.link_down == 1) {
                printf("Link DOWN! \n");
            } else {
                printf("Link Status Unknown! \n");
            }

            // The Power Settings are only activated for a Link Up condition
            // So we have to power Down the port, then bring it back up in the right mode
            // Powered this port down, then power-up to cause Link-up event
            vtss_phy_conf_get(board->inst, port_no, &phy_cfg);
            prev_mode[port_no] = phy_cfg.mode;                   // Save off the previous mode
            phy_cfg.mode = VTSS_PHY_MODE_POWER_DOWN;
            vtss_phy_conf_set(board->inst, port_no, &phy_cfg);
            printf ("Port %d, Setting VTSS_PHY_MODE_POWER_DOWN, Curr Phy_Mode: 0x%x  Prev Phy_Mode: 0x%x\n", port_no, phy_cfg.mode, prev_mode[port_no]);

            // Must call status_get to for Link Down Event to occur
            vtss_phy_status_get(board->inst, port_no, &status);
            if (status.link_down == 0) {
                printf("Link UP! \n");
            } else if (status.link_down == 1) {
                printf("Link DOWN! \n");
            } else {
                printf("Link Status Unknown! \n");
            }

            rc = vtss_phy_power_conf_get(board->inst, port_no, &pwr_cfg);

            if (strcmp(value_str, "act") == 0) {
                pwr_cfg.mode = VTSS_PHY_POWER_ACTIPHY;
            } else if (strcmp(value_str, "perf") == 0) {
                pwr_cfg.mode = VTSS_PHY_POWER_DYNAMIC;
            } else if (strcmp(value_str, "all") == 0) {
                pwr_cfg.mode = VTSS_PHY_POWER_ENABLED;
            } else {
                pwr_cfg.mode = VTSS_PHY_POWER_NOMINAL;
            }

            printf ("Setting PHY Power Config for Port: %d\n", port_no);
            rc = vtss_phy_power_conf_set(board->inst, port_no, &pwr_cfg);
            if (rc != VTSS_RC_OK) {
                printf ("//>>>>>> ERROR DETECTED <<<<<<<< During PHY Power Config Set, rc = %d\n", rc);
            } else {
                printf ("PHY Power Config setup: OK, rc = %d\n", rc);
            }

            pwr_cfg.mode = VTSS_PHY_POWER_NOMINAL; // This will be over-written by the power_conf_get()

            printf ("Getting PHY Power Config for Port: %d\n", port_no);
            rc = vtss_phy_power_conf_get(board->inst, port_no, &pwr_cfg);
            if (rc != VTSS_RC_OK) {
                printf ("//>>>>>> ERROR DETECTED <<<<<<<< During PHY Power Config Get, rc = %d\n", rc);
            } else {
                if (pwr_cfg.mode == VTSS_PHY_POWER_ACTIPHY) {
                    printf ("PHY Power Config Setting: ActiPHY \n");
                } else if (pwr_cfg.mode == VTSS_PHY_POWER_DYNAMIC) {
                    printf ("PHY Power Config Setting: PerfectReach \n");
                } else if (pwr_cfg.mode == VTSS_PHY_POWER_ENABLED) {
                    printf ("PHY Power Config Setting: ActiPHY+PerfectReach \n");
                } else if (pwr_cfg.mode == VTSS_PHY_POWER_NOMINAL) {
                    printf ("PHY Power Config Setting: Nominal - No Power Savings Enabled \n");
                } else {
                    printf ("PHY Power Config Setting: Unknown \n");
                }
            }

            // Must call status_get to for Link Down Event to occur
            vtss_phy_status_get(board->inst, port_no, &status);
            if (status.link_down == 0) {
                printf("Link UP! \n");
            } else if (status.link_down == 1) {
                printf("Link DOWN! \n");
            } else {
                printf("Link Status Unknown! \n");
            }

            // The Power Settings are only activated for a Link Up condition
            // Powered this port down above, now power-up to cause Link event
            vtss_phy_conf_get(board->inst, port_no, &phy_cfg);
            printf ("Port %d, Setting VTSS_PHY_MODE_POWER_UP, Curr Phy_Mode: 0x%x  Prev Phy_Mode: 0x%x\n", port_no, phy_cfg.mode, prev_mode[port_no]);
            phy_cfg.mode = prev_mode[port_no];
            vtss_phy_conf_set(board->inst, port_no, &phy_cfg);

            loops = 0;
            while ( loops < max_loops )
            {
                // Must call status_get to get link up and allow software to scale down power settings
                vtss_phy_status_get(board->inst, port_no, &status);
                if (status.link_down == 0) {
                    printf("Link UP! \n");
                    break;
                } else if (status.link_down == 1) {
                    printf("Link DOWN! \n");
                } else {
                    printf("Link Status Unknown! \n");
                }
                usleep(100000); // Sleep for 100000 usec or 100 msec
                loops++;
            }

            continue;

        } else if (strcmp(command, "ob_post") == 0) {
            vtss_rc  rc;
            u8 ob_post0 = 0;
            u8 ob_post1 = 0;
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            rc = vtss_phy_sd6g_ob_post_rd(board->inst, port_no, &ob_post0, &ob_post1);

            printf ("Port %d, Read Values for ob_post0: %d;  ob_post1: %d \n", port_no, ob_post0, ob_post1);

            printf ("Port %d, Please Enter ob_post0 (Exit=255): \n", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            ob_post0 = strtol(value_str, NULL, 10);
            if (ob_post0 == 255) {
                continue;
            }

            printf ("Port %d, Please Enter ob_post1 (Exit=255): \n", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            ob_post1 = strtol(value_str, NULL, 10);
            if (ob_post0 == 255) {
                continue;
            }

            rc = vtss_phy_sd6g_ob_post_wr(board->inst, port_no, ob_post0, ob_post1);

            printf ("Port %d, ob_post0: %d, ob_post1: %d,    rc = %d \n", port_no, ob_post0, ob_post1, rc);

            continue;

        } else if (strcmp(command, "ob_level") == 0) {
            vtss_rc  rc;
            u8 ob_level = 0;
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            rc = vtss_phy_sd6g_ob_lev_rd(board->inst, port_no, &ob_level);
            printf ("Port %d, Read Values for ob_level: %d \n", port_no, ob_level);

            printf ("Port %d, Please Enter ob_level (Exit=255): \n", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            ob_level = strtol(value_str, NULL, 10);
            if (ob_level == 255) {
                continue;
            }

            rc = vtss_phy_sd6g_ob_lev_wr(board->inst, port_no, ob_level);

            printf ("Port %d, ob_level: %d,     rc = %d \n", port_no, ob_level, rc);

            continue;

        } else if (strcmp(command, "odd_start") == 0) {
            vtss_rc  rc;
            BOOL  mac_inhibit = FALSE;
            BOOL  media_inhibit = FALSE;
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("MAC-Side Inhibit Odd-Start (16E3.2) ? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            if (value_str[0] == 'y' || value_str[0] == 'Y' ) {
                mac_inhibit = TRUE;
            }

            printf ("MEDIA-Side Inhibit Odd-Start (23E3.4) ? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            if (value_str[0] == 'y' || value_str[0] == 'Y' ) {
                media_inhibit = TRUE;
            }

            rc = vtss_phy_mac_media_inhibit_odd_start(board->inst, port_no, mac_inhibit, media_inhibit);

            printf ("Port %d, mac_inhibit: %d,  media_inhibit: %d,   rc = %d \n", port_no, mac_inhibit, media_inhibit, rc);

            continue;
#ifdef VIPER_SERDES_CSR_DEBUG
        } else if (strcmp(command, "csr_rd") == 0) {
            vtss_rc  rc;
            u32                 csr_reg;
            u32                 csr_reg_value;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            disp_6g_serdes_reg();

            printf ("Port %d, Enter SERDES CSR REG# (MUST be in Hex): ", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            csr_reg = strtol(value_str, NULL, 16);

            printf ("\n Port %d, CSR REG# 0x%x \n", port_no, csr_reg);
            rc = vtss_phy_sd6g_csr_reg_rd(board->inst, port_no, csr_reg, &csr_reg_value);

            printf ("Port %d, CSR_REG: 0x%x,  Read Reg_Value: 0x%x  rc = %d \n", port_no, csr_reg, csr_reg_value, rc);

            continue;

        } else if (strcmp(command, "csr_wr") == 0) {
            vtss_rc  rc;
            u32                 csr_reg;
            u32                 csr_reg_value;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            disp_6g_serdes_reg();

            printf ("Port %d, Enter SERDES CSR REG# (MUST be in Hex): ", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            csr_reg = strtol(value_str, NULL, 16);

            rc = vtss_phy_sd6g_csr_reg_rd(board->inst, port_no, csr_reg, &csr_reg_value);
            printf ("\nPort %d, CSR REG# 0x%x, Read Value (in Hex): 0x%x\n\n", port_no, csr_reg, csr_reg_value);

            printf ("\nPort %d, CSR REG# 0x%x, Enter Value to be Written (in Hex): ", port_no, csr_reg);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            csr_reg_value = strtol(value_str, NULL, 16);

            rc = vtss_phy_sd6g_csr_reg_wr(board->inst, port_no, csr_reg, csr_reg_value);

            printf ("Port %d, CSR_REG: 0x%x,  Writing Reg_Value: 0x%x  rc = %d \n", port_no, csr_reg, csr_reg_value, rc);

            continue;
#endif
        } else if (strcmp(command, "warmstart") == 0) {
            int                 prt=0;
            int                 i=0;
            vtss_port_no_t              base_port_no=0;
            vtss_restart_t      	warm_restart;
            vtss_phy_loopback_t		loopback_conf[VTSS_PORTS];
            vtss_appl_board_t  		*tmp_board_table;
            vtss_phy_reset_conf_t       reset_conf[VTSS_PORTS];
            vtss_phy_conf_t             phy_setup[VTSS_PORTS];
            vtss_phy_conf_1g_t          conf_1g[VTSS_PORTS];
            vtss_phy_power_conf_t       pwr_conf[VTSS_PORTS];
            vtss_phy_event_t            ev_mask[VTSS_PORTS];
            vtss_phy_clock_conf_t       clk_conf[VTSS_PHY_RECOV_CLK_NUM];
            vtss_port_no_t              clk_source[VTSS_PHY_RECOV_CLK_NUM];

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            /* Get the existing config for ALL the ports before a warm-start so they can be re-applied to the New Instance after warm-start */
            /* This would include:       */
            /*       - phy_config        */
            /*       - phy_reset_config  */
            /*       - phy_1g_config     */
            /*       - phy_event_config  */
            /*       - phy_power_config  */
            /*       - phy_eee_config    */
            /*       - Recovered Clk config  */
            /*       - 1588 config       */
            /*       - MACSEC config     */
            /* Note: This is SAMPLE DEMO code, So not ALL configs are being retrieved/saved */
            /*       The User should examine their code and retrieve the configs applicable to their configuration */
            for (prt = VTSS_PORT_NO_START; prt < VTSS_PORTS; prt++) {
                vtss_phy_loopback_get(board->inst,prt,&loopback_conf[prt]);
                vtss_phy_reset_get(board->inst, prt, &reset_conf[prt]);
                vtss_phy_conf_get(board->inst, prt, &phy_setup[prt]);
                vtss_phy_conf_1g_get(board->inst, prt, &conf_1g[prt]);
                vtss_phy_power_conf_get(board->inst, prt, &pwr_conf[prt]);
                vtss_phy_event_enable_get(board->inst, prt, &ev_mask[prt]);
            }

            vtss_phy_clock_conf_get(board->inst, port_no, VTSS_PHY_RECOV_CLK1, &clk_conf[VTSS_PHY_RECOV_CLK1], &clk_source[VTSS_PHY_RECOV_CLK1]);
            vtss_phy_clock_conf_get(board->inst, port_no, VTSS_PHY_RECOV_CLK2, &clk_conf[VTSS_PHY_RECOV_CLK2], &clk_source[VTSS_PHY_RECOV_CLK2]);

            vtss_restart_conf_get(board->inst, &warm_restart);
            printf ("<<< Warm-Start1 >>> Getting warm_restart Instance1: %p \n", board->inst);
            warm_restart = VTSS_RESTART_WARM;
            init_conf.restart_info_port = port_no;
            init_conf.warm_start_enable = TRUE;
            init_conf.restart_info_src = VTSS_RESTART_INFO_SRC_CU_PHY;
            /* This sets the warmstart information in the Instance */
            vtss_init_conf_set(board->inst, &init_conf);
            /* This sets the EPG Values in the Chip to be read after warmstart */
            vtss_restart_conf_set(board->inst, warm_restart);
            printf ("<<< Warm-Start1 >>> Setting Initial Instance1: %p;   warm_restart: 0x%x\n", board->inst, warm_restart);

            /* Destroy the previously allocated Instance (free vtss_state);  This is POST CPU/SW Reset */
            vtss_inst_destroy(board->inst); // Note: This is only performed for DEMO Application sequence to free up previously allocated memory

            // In this case we only have one board. Assign point to the board definition
            board = &board_table[0];
            memset (&board_table[0], 0, (sizeof(vtss_appl_board_t) * MAX_BOARD_INSTANCES));
            printf ("<<< Warm-Start1 Instance Destroyed >>> PHY Configured and Ready for CPU/Software Update \n");

            // Initialize
            vtss_board_phy_init(board);

            // "Create" the board
            vtss_inst_get(board->target, &create);
            // Create the Instance (malloc vtss_state);  This is POST CPU/SW Reset
            vtss_inst_create(&create, &board->inst);
            // Setup the init_conf pointer to the allocated space within instance
            vtss_init_conf_get(board->inst, &init_conf);

            // setup Board Support Pkg to point to the allocated space within the instance for accessor functions
            // Must be done prior to board_init()
            board->init.init_conf = &init_conf;

            init_conf.restart_info_port = port_no;
            init_conf.warm_start_enable = TRUE;
            init_conf.restart_info_src = VTSS_RESTART_INFO_SRC_CU_PHY;

            // setup Board Support Pkg to point to the allocated space within the instance for accessor functions
            // Must be done prior to board_init()
            printf ("<<< Warm-Start2 >>> Creating Instance2: %p  \n", board->inst);

            /* Setup/assign Accessor functions for MIIM_Read, MIIM_Write, Num Ports, etc.  Basic I/O functions to access board */
            if (board->board_init(argc, argv, board)) {
                T_E("Could not initialize board");
                printf ("//<<< ERROR >>> Warm-Start Error: Could not initialize board (BSP)\n");
                continue;
            } else {
#ifdef  ATOM12_EVAL_BOARD
                printf ("\n//Comment: <<< Please be patient, Loading ATOM12 Eval Board may take several minutes!!! >>> \n\n");
#endif
                printf ("//Comment: Board being initialized\n");
            }

            printf ("<<< Warm-Start2 >>> restart_info_port: %d, restart_info_src (CU_PHY): 0x%x, warm_start_enable: 0x%x\n",
                    init_conf.restart_info_port, init_conf.restart_info_src, init_conf.warm_start_enable);

            printf ("<<< Warm-Start2 >>> Save Config for Instance2: %p  \n", board->inst);
            /* Save the BSP Accessor functions used to access the board */
            /* This also updates vtss_state.init_conf with the warmstart src */
            if (vtss_init_conf_set(board->inst, &init_conf) == VTSS_RC_ERROR) {
                T_E("Could not initialize: Failure in Conf_set");
                printf ("// <<< ERROR >>> Warm-Start Error: Could not initialize board (BSP): failure in conf_set \n");
                continue;
            }

            /* This sets the warmstart information in the Instance */
            printf ("<<< Warm-Start2 >>> restart_info_port: %d, restart_info_src (CU_PHY): 0x%x, warm_start_enable: 0x%x\n",
                    init_conf.restart_info_port, init_conf.restart_info_src, init_conf.warm_start_enable);


            /* NOTE: ANY Configurations Performed on the PHY Ports should be re-applied to the new insteance HERE! */
            /* Set the existing config for ALL the ports before coming out of warm-start so they get re-applied to the New Instance */
            /* Note: vtss_phy_reset() applies the config, so calling and setting up config using vtss_phy_conf_set() happens first  */
            rc = vtss_phy_pre_reset(board->inst, base_port_no);
            if (rc != VTSS_RC_OK) {
                printf ("//ERROR DETECTED during PHY WARMSTART PRE-RESET Sequence (vtss_phy_pre_reset), rc = %d\n", rc);
            }

            for (prt = VTSS_PORT_NO_START; prt < VTSS_PORTS; prt++) {
                rc = vtss_phy_loopback_set(board->inst, prt,loopback_conf[prt]);
                if (rc != VTSS_RC_OK) {
                    printf ("//ERROR DETECTED during PHY WARMSTART LOOPBACK_CONFIG (vtss_phy_loopback_set), rc = %d\n", rc);
                }
                rc = vtss_phy_conf_set(board->inst, prt, &phy_setup[prt]);
                if (rc != VTSS_RC_OK) {
                    printf ("//ERROR DETECTED during PHY WARMSTART CONFIG (vtss_phy_conf_set), rc = %d\n", rc);
                }
                rc = vtss_phy_reset(board->inst, prt, &reset_conf[prt]);
                if (rc != VTSS_RC_OK) {
                    printf ("//ERROR DETECTED during PHY WARMSTART RESET (vtss_phy_reset), rc = %d\n", rc);
                }
                rc = vtss_phy_conf_1g_set(board->inst, prt, &conf_1g[prt]);
                if (rc != VTSS_RC_OK) {
                    printf ("//ERROR DETECTED during PHY WARMSTART 1G_CONFIG (vtss_phy_conf_1g_set), rc = %d\n", rc);
                }
                rc = vtss_phy_power_conf_set(board->inst, prt, &pwr_conf[prt]);
                if (rc != VTSS_RC_OK) {
                    printf ("//ERROR DETECTED during PHY WARMSTART PWR_CONFIG (vtss_phy_power_conf_set), rc = %d\n", rc);
                }

                for (i = 0; i < 32; i++) {
                    if (ev_mask[prt] & (1 << i)) {
                        rc = vtss_phy_event_enable_set(board->inst, prt, ev_mask[prt], TRUE);
                        if (rc != VTSS_RC_OK) {
                            printf ("//ERROR DETECTED during PHY WARMSTART EVENT_CONFIG (vtss_phy_event_enable_set), rc = %d\n", rc);
                        }
                    }
                }
            }

            printf ("Last_Step: Running PHY vtss_phy_post_reset on port %d\n", base_port_no);
            rc = vtss_phy_post_reset(board->inst, base_port_no);
            if (rc != VTSS_RC_OK) {
                printf ("//ERROR DETECTED during PHY WARMSTART POST-RESET Sequence (vtss_phy_post_reset), rc = %d\n", rc);
            }

            /* NOTE: ANY Configurations Performed that requires the BASE_PORT_NO of the PHY should be re-applied to the */
            /*       new instance AFTER vtss_phy_post_reset()!  This would include:  */
            /*       - Recovered Clocks  */
            /*       - 1588  */
            /*       - MACSEC */
            rc = vtss_phy_clock_conf_set(board->inst, port_no, VTSS_PHY_RECOV_CLK1, &clk_conf[VTSS_PHY_RECOV_CLK1]);
            if (rc != VTSS_RC_OK) {
                printf ("//ERROR DETECTED during PHY WARMSTART RECOV_CLK1_CONFIG (vtss_phy_clock_conf_set), rc = %d\n", rc);
            }

            rc = vtss_phy_clock_conf_set(board->inst, port_no, VTSS_PHY_RECOV_CLK2, &clk_conf[VTSS_PHY_RECOV_CLK2]);
            if (rc != VTSS_RC_OK) {
                printf ("//ERROR DETECTED during PHY WARMSTART RECOV_CLK2_CONFIG (vtss_phy_clock_conf_set), rc = %d\n", rc);
            }

            /* This does a sync with the PHY HW, Therefore any configuration differences will be indicated */
            vtss_restart_conf_end(board->inst);

            continue;

        } else if (strcmp(command, "getserdes")  == 0) {
            vtss_phy_reset_conf_t   phy_resetCfg;
            vtss_rc                 rc;
            char                   *mac_if_descr;
            char                   *media_if_descr;
            char                   *p_mac_if_name = NULL;
            char                   *p_media_if_name = NULL;
            u16                     i;
            u8                      mcb_bus = 0;
            u8                      cfg_buf[MAX_CFG_BUF_SIZE] = {0};
            u8                      stat_buf[MAX_STAT_BUF_SIZE] = {0};

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            for (port_no = 0; port_no < 4; port_no++) {
                vtss_phy_reset_get(board->inst, port_no, &phy_resetCfg);
                p_mac_if_name = get_mac_if_name_by_mac_id( phy_resetCfg.mac_if );
                p_media_if_name = get_media_if_name_by_media_id( phy_resetCfg.media_if);

                if ((p_mac_if_name != NULL) && (p_media_if_name != NULL)) {
                    printf ("Port No: %d, MAC I/F: %s     MEDIA I/F: %s \n", port_no,
                         p_mac_if_name, p_media_if_name);
                } else {
                    printf ("Port No: %d, MAC I/F: 0x%x     MEDIA I/F: 0x%x \n", port_no,
                         phy_resetCfg.mac_if, phy_resetCfg.media_if);
                }

                mcb_bus = 0; // MAC
                rc=vtss_phy_patch_settings_get(board->inst, port_no, &mcb_bus, &cfg_buf[0], &stat_buf[0]);
                if (rc == VTSS_RC_OK) {
                    for (i = 0; i < MAX_CFG_BUF_SIZE; i++) {
                        printf("Port: %x: MAC SerDes cfg_buf[%d]: 0x%x \n", port_no, i, cfg_buf[i]);
                    }
                    printf(" \n");
                 }
                 mcb_bus = 3; // MEDIA
                 rc=vtss_phy_patch_settings_get(board->inst, port_no, &mcb_bus, &cfg_buf[0], &stat_buf[0]);
                 if (rc == VTSS_RC_OK) {
                    for (i = 0; i < MAX_CFG_BUF_SIZE; i++) {
                        printf("Port: %x: MEDIA SerDes cfg_buf[%d]: 0x%x \n", port_no, i, cfg_buf[i]);
                    }
                    printf(" \n");
                 }

                 if (port_no == 0) {
                     mcb_bus = 2; // PLL
                     rc=vtss_phy_patch_settings_get(board->inst, port_no, &mcb_bus, &cfg_buf[0], &stat_buf[0]);
                     if (rc == VTSS_RC_OK) {
                        for (i = 0; i < MAX_CFG_BUF_SIZE; i++) {
                            printf("Port: %x: PLL cfg_buf[%d]: 0x%x \n", port_no, i, cfg_buf[i]);
                        }
                        printf(" \n");
                     }
                 }
            }

            continue;

        } else if (strcmp(command, "mse100m") == 0) {
            vtss_rc  rc;
            u32                 mse;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("\nPort %d, Getting 100m Mean Square Error\n", port_no);
            rc = vtss_phy_mse_100m_get(board->inst, port_no, &mse);

            printf ("Port %d, Read 100m MSE_Value (in counts) for Chan A: %d  rc = %d \n", port_no, mse, rc);
            printf ("\nIn order to convert returned mse values to dB \n");
            printf ("mse_dbl = mse / (1024 * 2048);     Note: Convert to Double and Scale by 2^21 = 1024 * 2048; small fraction \n");
            printf ("mse_dbl = 20 * log10(mse_dbl);     Note: Convert to dB, around -31.0 \n");

            continue;

        } else if (strcmp(command, "mse1000m") == 0) {
            vtss_rc  rc;
            u32                 mseA, mseB, mseC, mseD;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("\n Port %d, Getting 1000m Mean Square Error\n", port_no);
            rc = vtss_phy_mse_1000m_get(board->inst, port_no, &mseA, &mseB, &mseC, &mseD);

            printf ("Port %d, Read 1000m MSE_Values(in counts) per pair A: %d  B: %d;  C: %d;  D: %d;  rc = %d \n",
                      port_no, mseA, mseB, mseC, mseD, rc);
            printf ("\nIn order to convert returned mse values to dB \n");
            printf ("mse_dbl = mse / (1024 * 2048);     Note: Convert to Double and Scale by 2^21 = 1024 * 2048; small fraction \n");
            printf ("mse_dbl = 20 * log10(mse_dbl);     Note: Convert to dB, around -31.0 \n");

            continue;

        } else if (strcmp(command, "fefi") == 0) {
            vtss_rc                rc;
            vtss_fefi_mode_t       fefi;
            BOOL                   fefi_detected = FALSE;
            int                    tmp;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("\nPort %d, Far-End Failure Indication (FEFI) for 100FX Operation Only \n", port_no);
            printf ("\nPort %d, Enter FEFI Option (get/set/detect) \n", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            if (strcmp(value_str, "get") == 0) {
                rc = vtss_phy_fefi_get(board->inst, port_no, &fefi);
                printf ("\n Port %d, rc: %d; Current FEFI Settings (0=Normal; 2=ForceSuppress; 3=ForceEnable): 0x%x \n", port_no, rc, fefi);
            } else if (strcmp(value_str, "set") == 0) {
                rc = vtss_phy_fefi_get(board->inst, port_no, &fefi);
                printf ("\n Port %d, rc: %d; Current FEFI Settings (0=Normal; 2=ForceSuppress; 3=ForceEnable): 0x%x \n", port_no, rc, fefi);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                fefi = (vtss_fefi_mode_t) atoi(value_str);

                rc = vtss_phy_fefi_set(board->inst, port_no, fefi);
                if (rc != VTSS_RC_OK) {
                    printf ("\n Port %d, rc: %d; ERROR Setting FEFI (0=Normal; 2=ForceSuppress; 3=ForceEnable): 0x%x \n", port_no, rc, fefi);
                }

                rc = vtss_phy_fefi_get(board->inst, port_no, &fefi);
                printf ("\n Port %d, rc: %d; Current FEFI Settings (0=Normal; 2=ForceSuppress; 3=ForceEnable): 0x%x \n", port_no, rc, fefi);
            } else {
                rc = vtss_phy_fefi_detect(board->inst, port_no, &fefi_detected);
                if (fefi_detected) {
                    printf ("\n rc: %d; FEFI Detected on Port: %d \n", rc, port_no);
                } else {
                    printf ("\n rc: %d; FEFI NOT Detected on Port: %d \n", rc, port_no);
                }
            }

            continue;

        } else if (strcmp(command, "config_port") == 0) {
            vtss_rc                rc;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            vtss_phy_conf_get(board->inst, port_no, &phy);
            vtss_phy_conf_1g_get(board->inst, port_no, &phy_1g);

            printf ("Set Mode for Port: %d;   (0=ANEG, 1=Forced, 2=PowerDn Port), Enter Mode: ", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == '0') {
                phy.mode = VTSS_PHY_MODE_ANEG;
                phy.aneg.tx_remote_fault = 0;
                printf ("ANEG ADVERTISEMENTS: Set Tx_Remote_Fault for Port: %d  (Y/N): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == 'y' || value_str[0] == 'Y') {
                    phy.aneg.tx_remote_fault = 1;
                }

                phy.aneg.asymmetric_pause = 0;
                printf ("ANEG ADVERTISEMENTS: Set Asymmetric_Pause for Port: %d  (Y/N): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == 'y' || value_str[0] == 'Y') {
                    phy.aneg.asymmetric_pause = 1;
                }

                phy.aneg.symmetric_pause = 0;
                printf ("ANEG ADVERTISEMENTS: Set Symmetric_Pause for Port: %d  (Y/N): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == 'y' || value_str[0] == 'Y') {
                    phy.aneg.symmetric_pause = 1;
                }

                phy.mdi = VTSS_PHY_MDIX_AUTO;
                printf ("Select MDI Mode for Port: %d  (0=AUTO, 1=Force MDI, 2=Force MDIX): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == '0') {
                    phy.mdi = VTSS_PHY_MDIX_AUTO;
                } else  if (value_str[0] == '1') {
                    phy.mdi = VTSS_PHY_MDI;
                } else  if (value_str[0] == '2') {
                    phy.mdi = VTSS_PHY_MDIX;
                }

                printf ("ANEG ADVERTISEMENTS: Set Port Speed for Port: %d  (0=ANEG ALL Speeds OR ANEG Selected Speed: 1=1G, 2=100M, 3=10M), Enter Speed: ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == '0') {
                    // Example for PHY speed support for auto-neg
                    // This example shows how to ANEG to lower speed selections
                    phy.aneg.speed_10m_hdx = 1;
                    phy.aneg.speed_10m_fdx = 1;
                    phy.aneg.speed_100m_hdx = 1;
                    phy.aneg.speed_100m_fdx = 1;
                    phy.aneg.speed_1g_hdx = 1;
                    phy.aneg.speed_1g_fdx = 1;
                } else if (value_str[0] == '1') {
                    // Example for PHY speed support for auto-neg
                    // This example shows how to ANEG to fixed speed selections
                    phy.aneg.speed_10m_hdx = 0;
                    phy.aneg.speed_10m_fdx = 0;
                    phy.aneg.speed_100m_hdx = 0;
                    phy.aneg.speed_100m_fdx = 0;
                    phy.aneg.speed_1g_hdx = 1;
                    phy.aneg.speed_1g_fdx = 1;
                } else if (value_str[0] == '2') {
                    // Example for PHY speed support for auto-neg
                    // This example shows how to ANEG to fixed speed selections
                    phy.aneg.speed_10m_hdx = 0;
                    phy.aneg.speed_10m_fdx = 0;
                    phy.aneg.speed_100m_hdx = 1;
                    phy.aneg.speed_100m_fdx = 1;
                    phy.aneg.speed_1g_hdx = 0;
                    phy.aneg.speed_1g_fdx = 0;
                } else if (value_str[0] == '3') {
                    // Example for PHY speed support for auto-neg
                    // This example shows how to ANEG to fixed speed selections
                    phy.aneg.speed_10m_hdx = 1;
                    phy.aneg.speed_10m_fdx = 1;
                    phy.aneg.speed_100m_hdx = 0;
                    phy.aneg.speed_100m_fdx = 0;
                    phy.aneg.speed_1g_hdx = 0;
                    phy.aneg.speed_1g_fdx = 0;
                } else {
                    // Example for PHY speed support for auto-neg
                    phy.aneg.speed_10m_hdx = 1;
                    phy.aneg.speed_10m_fdx = 1;
                    phy.aneg.speed_100m_hdx = 1;
                    phy.aneg.speed_100m_fdx = 1;
                    phy.aneg.speed_1g_hdx = 1;
                    phy.aneg.speed_1g_fdx = 1;
                }

                printf ("//ANEG ADVERTISEMENTS: 1G_FDX: %x; 1G_HDX: %x; 100M_FDX: 0x%x; 100M_HDX: %x; 10M_FDX: %x; 10M_HDX: 0x%x \n",
                   phy.aneg.speed_1g_fdx, phy.aneg.speed_1g_hdx, phy.aneg.speed_100m_fdx,
                   phy.aneg.speed_100m_hdx, phy.aneg.speed_10m_fdx, phy.aneg.speed_10m_hdx);
                printf ("//  ASym_Pause: %x;  Sym_Pause: %x;   Tx_Remote_Fault: %x;    MDI: %x\n",
                   phy.aneg.asymmetric_pause, phy.aneg.symmetric_pause, phy.aneg.tx_remote_fault, phy.mdi);

            } else if (value_str[0] == '1') {
                phy.mode = VTSS_PHY_MODE_FORCED;
                printf ("Note: SmartBits Generator Defaults Forced mode to 1000 for Fibre \n");
                printf ("Set Port Speed for Port: %d    (0=1G, 1=100M, 2=10M, Enter Speed: ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == '0') {
                    phy.forced.speed = VTSS_SPEED_1G;
                    printf ("ALL PHY Port MODE defaulted to: FORCED - 1G; Unidirectional: %x \n", phy.unidir);
                    printf ("Port %d, Curr: Manual Enable(1=enable/0=disable): 0x%x;  Master/Slave(1=master, 0=slave): 0x%x\n\n", port_no, phy_1g.master.cfg, phy_1g.master.val);

                    printf ("Port %d, Modify Current Values? (Y/N)\n", port_no);
                    memset (&value_str[0], 0, sizeof(value_str));
                    scanf("%s", &value_str[0]);
                    if (value_str[0] == 'Y' || value_str[0] == 'y')
                    {
                        printf ("Port %d, Enter Manual Enable(1=enable, 0=disable): ", port_no);
                        memset (&value_str[0], 0, sizeof(value_str));
                        scanf("%s", &value_str[0]);
                        if (value_str[0] == '1') {
                            phy_1g.master.cfg = 1;
                            printf ("Port %d, Manual Setting Enabled, Enter Master/Slave Config (1=Master, 0=Slave): ", port_no);
                            memset (&value_str[0], 0, sizeof(value_str));
                            scanf("%s", &value_str[0]);
                            if (value_str[0] == '1') {
                                phy_1g.master.val = 1;
                            } else {
                                phy_1g.master.val = 0;
                            }
                        }
                    }
                } else if (value_str[0] == '1') {
                    phy.forced.speed = VTSS_SPEED_100M;
                } else if (value_str[0] == '2') {
                    phy.forced.speed = VTSS_SPEED_10M;
                } else {
                    phy.forced.speed = VTSS_SPEED_1G;
                }

                phy.mdi = VTSS_PHY_MDIX_AUTO;
                printf ("Select MDI Mode for Port: %d  (0=AUTO, 1=Force MDI, 2=Force MDIX): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == '0') {
                    phy.mdi = VTSS_PHY_MDIX_AUTO;
                } else  if (value_str[0] == '1') {
                    phy.mdi = VTSS_PHY_MDI;
                } else  if (value_str[0] == '2') {
                    phy.mdi = VTSS_PHY_MDIX;
                }

                phy.unidir = VTSS_PHY_UNIDIRECTIONAL_DISABLE;
                printf ("Set Port as UNIDIRECTIONAL for Port: %d   (N=No, Y=Yes): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == 'y' || value_str[0] == 'Y') {
                    phy.unidir = VTSS_PHY_UNIDIRECTIONAL_ENABLE;
                }
            } else if (value_str[0] == '2') {
                phy.mode = VTSS_PHY_MODE_POWER_DOWN;
            } else {
                phy.mode = VTSS_PHY_MODE_ANEG;
            }

            if (phy.mode == VTSS_PHY_MODE_ANEG) {
                printf ("//Default Setup: PHY Mode: ANEG Enabled: FDX: 0x%x;  HDX: 0x%x \n", phy.aneg.speed_1g_fdx, phy.aneg.speed_1g_hdx);
            } else if (phy.mode == VTSS_PHY_MODE_FORCED) {
                printf ("//PHY Mode: FORCED Speed Enabled - PowerDN: FDX: 0x%x;  HDX: 0x%x \n", phy.aneg.speed_1g_fdx, phy.aneg.speed_1g_hdx);
                /* See Datasheet, Reg0 - Mode Control, NOTEs section about Forced Mode operation */
                phy.mode = VTSS_PHY_MODE_POWER_DOWN;
                vtss_phy_conf_set(board->inst, port_no, &phy);
                phy.mode = VTSS_PHY_MODE_FORCED;
                printf ("//Default Setup: PHY Mode: FORCED Speed Enabled: FDX: 0x%x;  HDX: 0x%x \n", phy.aneg.speed_1g_fdx, phy.aneg.speed_1g_hdx);
            } else if (phy.mode == VTSS_PHY_MODE_POWER_DOWN) {
                printf ("//Default Setup: PHY Mode: PHY Power Down Enabled \n" );
            } else {
                printf ("//Default Setup: PHY Mode: Unknown \n" );
            }

            vtss_phy_conf_1g_set(board->inst, port_no, &phy_1g);
            vtss_phy_conf_set(board->inst, port_no, &phy);

            continue;

        } else if (strcmp(command, "rd_1588") == 0) {
            vtss_rc    rc;
            u32   value32 = 0;
            u32   csr_reg_addr = 0;
            u16   blk_id = 0;
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("\nPort %d, Enter 1588 Blk_Addr (HEX): ", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            blk_id = (u16)strtol(value_str, NULL, 16);

            printf ("\nPort %d, Enter 1588 CSR_Register_Addr (HEX): ", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            csr_reg_addr = (u32)strtol(value_str, NULL, 16);

            rc = vtss_phy_csr_rd(board->inst, VTSS_PHY_PAGE_1588, port_no, blk_id, csr_reg_addr, &value32);

            printf ("\nPort %d, 1588_CSR_READ  Blk_id: 0x%x; CSR_Register_Addr: 0x%x; Value: 0x%x \n", port_no, blk_id, csr_reg_addr, value32);

            continue;

        } else if (strcmp(command, "wr_1588")  == 0) {
            vtss_rc    rc;
            u32   value32 = 0;
            u32   csr_reg_addr = 0;
            u16   blk_id = 0;
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("\nPort %d, Enter 1588 Blk_Addr (HEX): ", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            blk_id = (u16)strtol(value_str, NULL, 16);

            printf ("\nPort %d, Enter 1588 CSR_Register_Addr (HEX): ", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            csr_reg_addr = (u32)strtol(value_str, NULL, 16);

            rc = vtss_phy_csr_rd(board->inst, VTSS_PHY_PAGE_1588, port_no, blk_id, csr_reg_addr, &value32);
            printf ("\nPort %d, 1588_CSR_READ  Blk_id: 0x%x; CSR_Register_Addr: 0x%x; Current Value: 0x%x ", port_no, blk_id, csr_reg_addr, value32);
            printf ("\nPort %d, 1588_CSR_WRITE Blk_id: 0x%x; CSR_Register_Addr: 0x%x; Enter NEW Value (HEX): ", port_no, blk_id, csr_reg_addr);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            value32 = (u32)strtol(value_str, NULL, 16);

            rc = vtss_phy_csr_wr(board->inst, VTSS_PHY_PAGE_1588, port_no, blk_id, csr_reg_addr, value32);

            value32 = 0;
            rc = vtss_phy_csr_rd(board->inst, VTSS_PHY_PAGE_1588, port_no, blk_id, csr_reg_addr, &value32);
            printf ("\nPort %d, 1588_CSR_READ  Blk_id: 0x%x; CSR_Register_Addr: 0x%x; Value: 0x%x \n", port_no, blk_id, csr_reg_addr, value32);

            continue;

        } else if (strcmp(command, "rd_macsec") == 0) {
            vtss_rc    rc;
            u32   value32 = 0;
            u32   csr_reg_addr = 0;
            u32   addr_offset = 0;
            u16   blk_id = 0;
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("\nPort %d, Enter MACSEC Blk_Addr (HEX): ", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            blk_id = (u16)strtol(value_str, NULL, 16);

            printf ("\nPort %d, Enter MACSEC CSR_Register_Addr (HEX): ", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            csr_reg_addr = (u32)strtol(value_str, NULL, 16);

            rc = vtss_phy_csr_rd(board->inst, VTSS_PHY_PAGE_MACSEC, port_no, blk_id, csr_reg_addr, &value32);

            printf ("\nPort %d, MACSEC_CSR_READ  Blk_id: 0x%x; CSR_Register_Addr: 0x%x; Value: 0x%x \n", port_no, blk_id, csr_reg_addr, value32);

            continue;

       } else if (strcmp(command, "wr_macsec")  == 0) {
            vtss_rc    rc;
            u32   value32 = 0;
            u32   csr_reg_addr = 0;
            u32   addr_offset = 0;
            u16   blk_id = 0;
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("\nPort %d, Enter MACSEC Blk_Addr (HEX): ", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            blk_id = (u16)strtol(value_str, NULL, 16);

            printf ("\nPort %d, Enter MACSEC CSR_Register_Addr (HEX): ", port_no);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            csr_reg_addr = (u32)strtol(value_str, NULL, 16);

            rc = vtss_phy_csr_rd(board->inst, VTSS_PHY_PAGE_MACSEC, port_no, blk_id, csr_reg_addr, &value32);
            printf ("\nPort %d, MACSEC_CSR_READ  Blk_id: 0x%x; CSR_Register_Addr: 0x%x; Current Value: 0x%x ", port_no, blk_id, csr_reg_addr, value32);
            printf ("\nPort %d, MACSEC_CSR_WRITE Blk_id: 0x%x; CSR_Register_Addr: 0x%x; Enter NEW Value (HEX): ", port_no, blk_id, csr_reg_addr);
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            value32 = (u32)strtol(value_str, NULL, 16);

            rc = vtss_phy_csr_wr(board->inst, VTSS_PHY_PAGE_MACSEC, port_no, blk_id, csr_reg_addr, value32);

            value32 = 0;
            rc = vtss_phy_csr_rd(board->inst, VTSS_PHY_PAGE_MACSEC, port_no, blk_id, csr_reg_addr, &value32);
            printf ("\nPort %d, MACSEC_CSR_READ  Blk_id: 0x%x; CSR_Register_Addr: 0x%x; Value: 0x%x \n", port_no, blk_id, csr_reg_addr, value32);

            continue;

        } else if (strcmp(command, "rdext") == 0) {
            read_cmd = TRUE;
            read_ext = TRUE;
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }
        } else if (strcmp(command, "wrext")  == 0) {
            read_cmd = FALSE;
            write_ext = TRUE;
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }
        } else if (strcmp(command, "rd")  == 0) {
            read_cmd = TRUE;
            read_ext = FALSE;
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }
        } else if (strcmp(command, "wr")  == 0) {
            read_cmd = FALSE;
            write_ext = FALSE;
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }
        } else if (strcmp(command, "exit")  == 0) {
            break;
        } else if (strcmp(command, "quit")  == 0) {
            break;
        } else {
            printf ("Unknown command:%s \n", command);
            continue;
        }

        // Read / Write to Register Processing
        if (read_ext || write_ext) {
            printf ("Port %d, Enter Ext Page# (MUST be in Hex): ", port_no);
            scanf("%s", &ext_page_str[0]);
            ext_page = strtol(ext_page_str, NULL, 16);
        }

        printf ("Port %d, Enter Reg Addr (Decimal): ", port_no);
        scanf("%s", &addr_str[0]);
        addr = atoi(addr_str);

        if (read_cmd) {
            if (read_ext) {
                printf ("Port %d, Ext Page# 0x%x ", port_no, ext_page );
                miim_write(board->inst, port_no, 31, ext_page);
            }
            miim_read(board->inst, port_no, addr, &value);
            printf("addr: %02d Value: 0x%04X \n", addr, value);
            miim_write(board->inst, port_no, 31, 0);
        } else {
            if (write_ext) {
                printf ("Port %d: Ext Page# 0x%x: ", port_no, ext_page );
                miim_write(board->inst, port_no, 31, ext_page); /* Setup Page */
            }
            printf ("Port: %d, Reg: %d, Enter Value (in Hex, ie. 0x):  ", port_no, addr );
            scanf("%s", &value_str[0]);

            //value = atoi(value_str);
            value = strtol(value_str, NULL, 16);
            printf("Writing Addr:%02d : Value:0x%04X \n", addr, value);
            miim_write(board->inst, port_no, addr, value);

            value = 0;
            miim_read(board->inst, port_no, addr, &value);
            printf("Addr: %02d,  New reg value 0x%04X \n", addr, value);
            miim_write(board->inst, port_no, 31, 0);
        }

    } // end of main
    return 0; // All done

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
   fclose(fp);
#endif
} // end of main
