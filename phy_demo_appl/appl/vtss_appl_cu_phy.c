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
#include "vtss_api.h"   // For board initialization
#include "vtss_appl.h"  // For vtsss_board_t
#include "vtss_port_api.h"
#include "vtss_appl_cu_phy.h" // For board init
#include "vtss_macsec_api.h"
#include <netdb.h>  // For socket
#include <stdarg.h> // For va_list

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

#ifdef VTSS_OPT_PHY_TIMESTAMP
#include "vtss_phy_ts_api.h"
#endif

#ifdef VTSS_FEATURE_MACSEC
#include "vtss_macsec_api.h"
#include <openssl/aes.h>

typedef struct explicit_sci_struct {
    BOOL                 explicit_sci_flag;
    vtss_macsec_sci_t    explicit_sci;
} vtss_explicit_sci_t;

void vtss_basic_secy(vtss_inst_t          inst,
                     vtss_port_no_t       macsec_physical_port,
                     vtss_macsec_port_t  *_macsec_port,
                     vtss_mac_t          *_port_macaddress,
                     vtss_explicit_sci_t *explicit_sci_rx,
                     BOOL                 encrypt_256
);

void vtss_basic_secy_destroy(
    vtss_inst_t               inst,
    const vtss_macsec_port_t *macsec_port
);

void vtss_single_secy_sample_system_create(
    vtss_inst_t          inst,
    vtss_port_no_t       port_no,
    vtss_macsec_port_t  *_macsec_port,
    vtss_mac_t          *_port_macaddress,
    vtss_macsec_sci_t   *_peer_sci,
    vtss_explicit_sci_t *explicit_sci_rx,
    BOOL                 encrypt_256,
    BOOL                 confidentiality
);

void vtss_single_secy_sample_system_destroy(
    vtss_inst_t               inst,
    const vtss_macsec_port_t *macsec_port,
    const vtss_mac_t         *port_macaddress,
    const vtss_macsec_sci_t  *peer_sci
);

vtss_rc sak_update_hash_key(vtss_macsec_sak_t * sak);

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

#ifdef VTSS_OPT_PHY_TIMESTAMP 
#define EVAL_BOARD_1588_CAPABLE
#else
#undef EVAL_BOARD_1588_CAPABLE
#endif

#ifdef VTSS_FEATURE_MACSEC
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

#ifdef EVAL_BOARD_1588_CAPABLE

/* ********************************************************** */
/* *** Example of init of SPI for Timestamp Push Out  ******* */
/* ********************************************************** */

vtss_rc vtss_1588_init_for_spi (const vtss_inst_t inst,  const vtss_port_no_t port_no )
{
    vtss_phy_ts_init_conf_t conf;
    vtss_rc rc;

    do {
        /* reference clock frequency */
        conf.clk_freq     = VTSS_PHY_TS_CLOCK_FREQ_15625M;
        /* Clock Source */
        conf.clk_src      = VTSS_PHY_TS_CLOCK_SRC_EXTERNAL;
        /* 10byte Full Tx timestamp */
        conf.tx_ts_len    = VTSS_PHY_TS_FIFO_TIMESTAMP_LEN_10BYTE;
        /*  Timestamps to pushed out on the SPI interface */
        conf.tx_fifo_mode = VTSS_PHY_TS_FIFO_MODE_SPI;
        /*  Rx timestamp in PTP reserved bytes */
        conf.rx_ts_pos    = VTSS_PHY_TS_RX_TIMESTAMP_POS_IN_PTP;
        /*  Rx timestamp update nano seconds part */
        conf.rx_ts_len    = VTSS_PHY_TS_RX_TIMESTAMP_LEN_30BIT;
        /* TC operating mode is Mode C */
        conf.tc_op_mode   = VTSS_PHY_TS_TC_OP_MODE_A;

        rc = vtss_phy_ts_init(inst, port_no, &conf);
        if (rc == VTSS_RC_OK) {
            printf("PHY TS Init Success  \n");
        } else {
            printf("PHY TS Init Failed  \n");
            break;
        }

        rc = vtss_phy_ts_mode_set (inst, port_no, TRUE);
        if (rc != VTSS_RC_OK) {
            printf("PHY TS Block Enable Failed \n");
            break;
        }
    } while (0);

    return rc;
}


/* ********************************************************** */
/* *************     MULTIPLE ENCAPS - PTP TIME STAMP ******* */
/* ********************************************************** */
/* Vtss Sample Application for BC
  --->P1-->S1  --->  S2-->P1  (P:Port S: Switch)

If we pass same ing_port_no and egr_port_no to this application that port
will be configured for both ing and egr functionalities of BC App,
and needs be called on both switches.
Application: Ordinary/Boundary clock, 1 step
Delay method: End-to-End delay measurement method
*/
/* ETH-PTP Encapsulation */
vtss_rc vtss_1588_sample_flows_ep(const vtss_inst_t inst, 
                                  const vtss_port_no_t ing_port_no, 
                                  const vtss_port_no_t egr_port_no, 
	                          const vtss_phy_ts_engine_t eng_id,
                                  int   numflows, 
                                  u8    in_flow)
{
    vtss_rc rc = VTSS_RC_ERROR;
    u8      flow_id = 0;
    vtss_phy_ts_engine_flow_conf_t *flow_conf;
    char value_str[20] = {0};
    unsigned char vlan_n=0;
    unsigned char vlan_check = FALSE;

	if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
		printf("Engine flow_conf memory allocation Failed!\n");
		return -1;
	}
	memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

	printf("Ingress:: Port:%d : Engine#%d  Flow_id:%d, numFlows:%d :: Encapsulation: ETH/PTP \n", 
                          ing_port_no, eng_id, in_flow, numflows);
        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

        do {
                printf ("Number of Vlans (0 / 1 / 2 / Any # above 2 = NO_VLAN):");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                vlan_n = strtol(value_str, NULL, 10);
                if (vlan_n == 0 ) {
                        printf ("Number VLANs :%d        Selected!!  vlan_check = TRUE but NO VLAN ID!\n ", vlan_n);
                        vlan_check = TRUE;
                        break;
                } else if ((vlan_n <= 2 ) && (vlan_n > 0)) {
                        printf ("Number VLANs : %d       Selected!!  vlan_check = TRUE    VLAN_VALUE = %d \n ", vlan_n, 1);
                        vlan_check = TRUE;
                        break;
                } else {
                        printf ("INVALID OPTION Selected: %d!! Options are: 0/1/2 -  Setting vlan_check = FALSE\n", vlan_n);
                        vlan_check = FALSE;
                        break;
                }

        } while (!(vlan_n > 2 ));


	do {
                /* ALWAYS perform a "Get" before performing modifications and calling a "Set" */
		rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
			break;
		}

		/* engine enable */
		flow_conf->eng_mode = TRUE;
                /* This is an Auto-configuration of flows based upon the FLOW_ID and NumFlows for DEMO Purposes ONLY */
                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
		    /* Map each flow to the channel which already mapped to the port */
		    flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;

		    /* Enable the MAC flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;

		    /* Options are: VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT if Eth_Addr to be matched, */
                    /* VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST if only matching on UNICAST bit,  */
                    /* or  VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST if MULTICAST bit is set */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;

		    /* Notify the engine which mac address needs to be matched(dest/src/both) */
                    /* Options are: VTSS_PHY_TS_ETH_MATCH_DEST_ADDR, VTSS_PHY_TS_ETH_MATCH_SRC_ADDR, VTSS_PHY_TS_ETH_MATCH_SRC_OR_DEST */ 
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;

		    /* Notify the engine if it is VLAN flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = vlan_check;
                    /* Config for Checking Specific VLAN Tagging  */
                    if (vlan_check) {
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].num_tag = vlan_n;
                        if (vlan_n == 0) {
                        } else if (vlan_n == 1) {
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag_type = VTSS_PHY_TS_TAG_TYPE_S;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag_type = VTSS_PHY_TS_TAG_TYPE_C;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].tag_range_mode = VTSS_PHY_TS_TAG_RANGE_NONE;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag.value.val = 1;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag.value.mask = 0xFFFF;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag.value.val = 1;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag.value.mask = 0xFFFF;
                        } else if (vlan_n == 2) {
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag_type = VTSS_PHY_TS_TAG_TYPE_S;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag_type = VTSS_PHY_TS_TAG_TYPE_C;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].tag_range_mode = VTSS_PHY_TS_TAG_RANGE_NONE;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag.value.val = 0x88A8;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag.value.mask = 0xFFFF;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag.value.val = 1;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag.value.mask = 0xFFFF;
                        }
                    }

		    /* Configure the MAC address of the flow, needs to be time stamped */
		    /* This is only applicable if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT */
		    /* if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST or */
                    /* if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST, then mac_addr is not used i- Zero'd */
                    if (flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode == VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT) { 
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                    } else {
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x00;
                    }
                    
                    /* ************************************************************************* */
                    /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                    /* if not in Multi-Cast or Uni-Cast                                          */
                    /* ************************************************************************* */
		
	            printf("flow_id: %d::ETHERTYPE_IEEE_PTP_1588:: MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);
                }

                /* Set the Ethernet Type to be matched  */
		flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_PTP_1588; 	//0x8847; 

                /* Set the INGRESS Engine Config - for ETH-PTP, all other comparitors are skipped  */
		rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
		if (rc == VTSS_RC_OK) {
			 printf("PHY TS Engine %d  Conf_set Success \n", eng_id);
		} else {
			 printf("PHY TS Engine %d  Conf_set Failed! \n", eng_id);
			 break;
		}
	        printf("Egress:: Port:%d : Engine#%d  Flow_id:%d, numFlows:%d :: ETH/PTP\n", 
                          egr_port_no, eng_id, flow_id, numflows);
		
                /* Set the EGRESS Engine Config - for ETH-PTP, all other comparitors are skipped  */
                /* This config is Symmetric since INGRESS and EGRESS are being configured identically  */
		rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		} else {
			printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			break;
		}
	} while (0);
	
}

/* ETH-OAM Encapsulation */
vtss_rc vtss_1588_sample_flows_eoam(const vtss_inst_t inst,
                                  const vtss_port_no_t ing_port_no,
                                  const vtss_port_no_t egr_port_no,
                                  const vtss_phy_ts_engine_t eng_id,
                                  int   numflows,
                                  u8    in_flow)
{
        vtss_rc rc = VTSS_RC_ERROR;
        u8      flow_id = 0;
        vtss_phy_ts_engine_flow_conf_t *flow_conf;

        if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
                printf("Engine flow_conf memory allocation Failed!\n");
                return -1;
        }
        memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

        printf("Ingress:: Port:%d : Engine#%d  Flow_id:%d, numFlows:%d :: Encapsulation: ETH/OAM \n",
                          ing_port_no, eng_id, in_flow, numflows);

        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

        do {
               /* ALWAYS perform a "Get" before performing modifications and calling a "Set" */
                rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
                if (rc != VTSS_RC_OK) {
                        printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
                        break;
                }

                /* engine enable */
                flow_conf->eng_mode = TRUE;
                /* This is an Auto-configuration of flows based upon the FLOW_ID and NumFlows for DEMO Purposes ONLY */
                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
                    /* Map each flow to the channel which already mapped to the port */
                    flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;

                    /* Enable the MAC flow */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
                    /* Options are: VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT if Eth_Addr to be matched, */
                    /* VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST if only matching on UNICAST bit,  */
                    /* or  VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST if MULTICAST bit is set */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
                    /* Notify the engine which mac address needs to be matched(dest/src/both) */
                    /* Options are: VTSS_PHY_TS_ETH_MATCH_DEST_ADDR, VTSS_PHY_TS_ETH_MATCH_SRC_ADDR, VTSS_PHY_TS_ETH_MATCH_SRC_OR_DEST */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
                    /* Notify the engine if it is VLAN flow */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = FALSE;
                    /* Configure the MAC address of the flow, needs to be time stamped */
                    /* This is only applicable if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT */
                    /* if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST or */
                    /* if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST, then mac_addr is not used i- Zero'd */
                    if (flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode == VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT) {
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                    } else {
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x00;
                    }

                    /* ************************************************************************* */
                    /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                    /* ************************************************************************* */
                    printf("flow_id: %d::ETHERTYPE_IEEE_PTP_1588:: MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);
                }

                /* Set the Ethernet Type to be matched  */
                flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_802_1_AG;      //0x8902
                /* Set the INGRESS Engine Config - for ETH-OAM, all other comparitors are skipped  */
                rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
                if (rc == VTSS_RC_OK) {
                         printf("PHY TS Engine %d  Conf_set Success \n", eng_id);
                } else {
                         printf("PHY TS Engine %d  Conf_set Failed! \n", eng_id);
                         break;
                }
                printf("Egress:: Port:%d : Engine#%d  Flow_id:%d, numFlows:%d :: ETH/OAM\n",
                          egr_port_no, eng_id, flow_id, numflows);

                /* Set the EGRESS Engine Config - for ETH-PTP, all other comparitors are skipped  */
                /* This config is Symmetric since INGRESS and EGRESS are being configured identically  */
                rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
                if (rc == VTSS_RC_OK) {
                        printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
                } else {
                        printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
                        break;
                }
        } while (0);

}


/* ETH-IP-PTP Encapsulation */
/* This is Really ETH-IP-UDP-PTP Encapsulation and you can select IPv4 or IPv6 */
vtss_rc vtss_1588_sample_flows_eip(const vtss_inst_t inst, 
                                  const vtss_port_no_t ing_port_no, 
                                  const vtss_port_no_t egr_port_no, 
	                          const vtss_phy_ts_engine_t eng_id,
                                  int   numflows, 
                                  const u8 in_flow)
{
    vtss_rc rc = VTSS_RC_ERROR;
    vtss_phy_ts_engine_flow_conf_t *flow_conf;
    u8   flow_id = 0;
    char value_str[20] = {0};
    unsigned char ipver=0;
    unsigned char vlan_n=0;
    unsigned char vlan_check = FALSE;
	
	if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
		printf("Engine flow_conf memory allocation Failed!\n");
		return -1;
	}
	memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

	printf("Ingress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/IP/PTP \n", 
                    ing_port_no, eng_id, flow_id, numflows);

        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

	do {
		printf ("Number of Vlans (0 / 1 / 2 / Any # above 2 = NO_VLAN):");
		memset (&value_str[0], 0, sizeof(value_str));
		scanf("%s", &value_str[0]);
		vlan_n = strtol(value_str, NULL, 10);
		if (vlan_n == 0 ) {
			printf ("Number VLANs :%d        Selected!!  vlan_check = TRUE but NO VLAN ID!\n ", vlan_n);
                        vlan_check = TRUE;
                        break;
		} else if ((vlan_n <= 2 ) && (vlan_n > 0)) {
			printf ("Number VLANs : %d	 Selected!!  vlan_check = TRUE    VLAN_VALUE = %d \n ", vlan_n, vlan_n);
                        vlan_check = TRUE;
                        break;
		} else {
			printf ("INVALID OPTION Selected: %d!! Options are: 0/1/2 -  Setting vlan_check = FALSE\n", vlan_n);
                        vlan_check = FALSE;
                        break;
		}
		
        } while (!(vlan_n > 2 ));

	do {

		printf ("Select IP version Mode (0 = IPv4; 1 = IPv6):");
		memset (&value_str[0], 0, sizeof(value_str));
		scanf("%s", &value_str[0]);
		ipver = strtol(value_str, NULL, 10);
		if ((ipver == 0) || (ipver == 1)) {
			printf ("IP Version : %d  : %s   Selected!!\n ", ipver, (ipver == 1 ? "IPv6" : "IPv4"));
		} else {
			printf ("INVALID OPTION Selected!!	Options are: 0/1\n");
		}
		
	} while (!((ipver == 0) || (ipver == 1)));

	do {
                /* ALWAYS perform a "Get" before performing modifications and calling a "Set" */
		rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
			break;
		}

		/* engine enable */
		flow_conf->eng_mode = TRUE;

               /* This is an Auto-configuration of flows based upon the FLOW_ID and NumFlows for DEMO Purposes ONLY */
                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
		    /* Map each flow to the channel which already mapped to the port */
		    flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;

                    /* Enable the MAC flow */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
                    /* Options are: VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT if Eth_Addr to be matched, */
                    /* VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST if only matching on UNICAST bit,  */
                    /* or  VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST if MULTICAST bit is set */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
                    /* Notify the engine which mac address needs to be matched(dest/src/both) */
                    /* Options are: VTSS_PHY_TS_ETH_MATCH_DEST_ADDR, VTSS_PHY_TS_ETH_MATCH_SRC_ADDR, VTSS_PHY_TS_ETH_MATCH_SRC_OR_DEST */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		    /* Notify the engine if it is VLAN flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = vlan_check;

		    /* Config for Checking Specific VLAN Tagging  */
                    if (vlan_check) {
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].num_tag = vlan_n;
                        if (vlan_n == 0) {
                        } else if (vlan_n == 1) {
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag_type = VTSS_PHY_TS_TAG_TYPE_S;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag_type = VTSS_PHY_TS_TAG_TYPE_C;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].tag_range_mode = VTSS_PHY_TS_TAG_RANGE_NONE;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag.value.val = 1;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag.value.mask = 0xFFFF;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag.value.val = 1;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag.value.mask = 0xFFFF;
                        } else if (vlan_n == 2) {
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag_type = VTSS_PHY_TS_TAG_TYPE_S;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag_type = VTSS_PHY_TS_TAG_TYPE_C;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].tag_range_mode = VTSS_PHY_TS_TAG_RANGE_NONE;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag.value.val = 0x88A8;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag.value.mask = 0xFFFF;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag.value.val = 1;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag.value.mask = 0xFFFF;
                        }
                    }

                    /* Configure the MAC address of the flow, needs to be time stamped */
                    /* This is only applicable if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT */
                    /* if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST or */
                    /* if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST, then mac_addr is not used i- Zero'd */
                    if (flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode == VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT) {
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                    } else {
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x00;
                    }

                    /* ************************************************************************* */
                    /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                    /* For Demo Purpose ONLY, Modify ip1 IP_Addr for each flow to be different */
                    /* ************************************************************************* */

                     /* ipver == 0 is IPv4;   ipver != 0 is IPv6 */
		     if(ipver == 0 ){
		         /* match 1st IPv4 address - Depends on SRC or DEST Flag*/
			 flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_IPV4;    //0x0800; 
	                 /* Set IP Version to IPv4 */
	                 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_4;
                         /* Note: To completely SKIP IPv4 Matching, set the ip_addr.ipv4.mask = 0x0 */
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.mask = 0xffffffff;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.addr = 0x0a0a0a0a+flow_id;	/* 153.136.119.102	<<<< FLow_Diff */
	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV4:: IP1: 0x%08x  Mask:0x%08x\n", flow_id,
			       flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.addr,
			       flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.mask);
		     } else {
		         /* match 1st IPv6 address - Depends on SRC or DEST Flag*/
			 flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_IPV6;	//0x86DD; 
		         /* Set IP Version to IPv6 */
		         flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_6;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3] = 0xA000000A;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2] = 0xB000000B;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1] = 0xC000000C;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0] = 0x1+flow_id; 
			 
                         /* Note: To completely SKIP IPv6 Matching, set the ip_addr.ipv6.mask[0..3] = 0x0 */
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0] = 0xFFFFFFFF;

	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: IP1: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0]);
	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: MSK: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0]);
		     }

		     /* Enable the IP flow */
		     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].flow_en = TRUE;
		     /* match 1st IP address - Depends on SRC or DEST or BOTH Flag*/
                     /* Options are: VTSS_PHY_TS_IP_MATCH_SRC; VTSS_PHY_TS_IP_MATCH_DEST; VTSS_PHY_TS_IP_MATCH_SRC_OR_DEST */
		     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].match_mode = VTSS_PHY_TS_IP_MATCH_DEST;

	             printf("flow_id: %d::ETH1 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);
                 }

		 /* Set dest port to 319 to receive PTP event messages */
		 /* If setup for Tesla OOS Recovery, EPG can only support one of the following: */
                 /* dport_val = 319; dport_mask = 0xffff; sport_val=0; sport_mask=0  */
                 /* dport_val = 319; dport_mask = 0xffff; sport_val=319; sport_mask=0xffff  */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val = 319; 	 /* UDP Dest Port 319/320 */
		 /* Set dest port mask 0 means any port 0xFFFF means exact match to given port */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_mask = 0xffff;  /* UDP Dest Port Mask	*/
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val = 1;		/* UDP Source Port */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_mask = 0xffff; 	  /* UDP Source Port Mask */
                 printf("Flow: %d  IP1: UDP_dport: %d;   UDP_Sport: %d\n", flow_id,
		     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val,
		     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val);

                 /* Set the INGRESS Engine Config - for ETH-PTP, all other comparitors are skipped  */
		 rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
		 if (rc == VTSS_RC_OK) {
			 printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		 } else {
			 printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			 break;
		 }
	         printf("Egress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/IP/PTP \n", 
                    egr_port_no, eng_id, flow_id, numflows);
		
                /* Set the EGRESS Engine Config - for ETH-PTP, all other comparitors are skipped  */
                /* This config is Symmetric since INGRESS and EGRESS are being configured identically  */
		rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		} else {
			printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			break;
		}
	} while (0);

}

/* ETH-IP-IP-PTP Encapsulation */
/* This is Really ETH-IP-IP-UDP-PTP Encapsulation and you can select IPv4 or IPv6 */
vtss_rc vtss_1588_sample_flows_eiip(const vtss_inst_t inst, 
                                    const vtss_port_no_t ing_port_no, 
                                    const vtss_port_no_t egr_port_no, 
	                            const vtss_phy_ts_engine_t eng_id,
                                    int   numflows, 
                                    const u8 in_flow)
{
	vtss_rc rc = VTSS_RC_ERROR;
	vtss_phy_ts_engine_flow_conf_t *flow_conf;
        u8   flow_id = 0;
        char value_str[20] = {0};
	unsigned char ipver=0;
	unsigned char vlan_n=0;
        unsigned char vlan_check = FALSE;

	if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
		printf("Engine flow_conf memory allocation Failed!\n");
		return -1;
	}
	memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

	printf("Ingress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/IP/IP/PTP \n", 
                    ing_port_no, eng_id, flow_id, numflows);

        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

        do {
                printf ("Number of Vlans (0 / 1 / 2):");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                vlan_n = strtol(value_str, NULL, 10);
                if (vlan_n == 0 ) {
                        printf ("Number VLANs :%d        Selected!!  vlan_check = FALSE\n ", vlan_n);
                        vlan_check = FALSE;
                        break;
                } else if ((vlan_n <= 2 ) && (vlan_n > 0)) {
                        printf ("Number VLANs : %d       Selected!!  vlan_check = TRUE\n ", vlan_n);
                        vlan_check = TRUE;
                        break;
                } else {
                        printf ("INVALID OPTION Selected!!      Options are: 0/1/2\n");
                        vlan_check = FALSE;
                        break;
                }

        } while (!(vlan_n > 2 ));

        do {
                printf ("Select IP version Mode (0 = IPv4; 1 = IPv6):");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                ipver = strtol(value_str, NULL, 10);
                if ((ipver == 0) || (ipver == 1)) {
                        printf ("IP Version : %d  : %s   Selected!!\n ", ipver, (ipver == 1 ? "IPv6" : "IPv4"));
                } else {
                        printf ("INVALID OPTION Selected!!      Options are: 0/1\n");
                }

	} while (!((ipver == 0) || (ipver == 1)));

	do {

		rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
			break;
		}

		/* engine enable */
		flow_conf->eng_mode = TRUE;

                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
		    /* Map each flow to the channel which already mapped to the port */
		    flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
		    /* Enable the MAC flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
		    /* Notify the engine which mac address needs to be matched(dest/src) */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		    /* Notify the engine if it is VLAN flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = FALSE;
		    /* Configure the MAC address of the flow, needs to be time stamped */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
	             printf("flow_id: %d::ETH1 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);
		     /* Enable the IP flow */
		     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].flow_en = TRUE;
		     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].match_mode = VTSS_PHY_TS_IP_MATCH_DEST;

                     if(ipver == 0 ){
		         /* Set IP Version to IPv4 */
		         flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_4;
		         /* match 1st IP address - Depends on SRC or DEST Flag*/
                         flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_IPV4;    //0x0800; 
                         flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.mask = 0xffffffff;
                         flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.addr = 0x0a0a0a0a+flow_id;     /* 153.136.119.102      <<<< FLow_Diff */
                         printf("flow_id: %d::ETHERTYPE_IEEE_IPV4:: IP1: 0x%08x  Mask:0x%08x\n", flow_id,
                               flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.addr,
                               flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.mask);
                     } else {
		         /* Set IP Version to IPv6 */
		         flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_6;
		         /* match 1st IP address - Depends on SRC or DEST Flag*/
                         flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_IPV6;        //0x86DD
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3] = 0xA000000A;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2] = 0xB000000B;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1] = 0xC000000C;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0] = 0x1+flow_id; 
			 
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0] = 0xFFFFFFFF;

	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: IP1: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0]);
	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: MSK: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0]);
		     }
		 
		     flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].flow_en = TRUE;
		     /* match 1st IP address - Depends on SRC or DEST Flag*/
		     flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].match_mode = VTSS_PHY_TS_IP_MATCH_DEST;

                     if(ipver == 0 ){
                         /* Set IP Version to IPv4 */
                         flow_conf->flow_conf.ptp.ip2_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_4;
                         /* match 1st IP address - Depends on SRC or DEST Flag*/
                         flow_conf->flow_conf.ptp.eth2_opt.comm_opt.etype = ETHERTYPE_IEEE_IPV4;    //0x0800; 
                         flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv4.mask = 0xffffffff;
                         flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv4.addr = 0x0a0a0a0a+flow_id;     /* 153.136.119.102      <<<< FLow_Diff */
                         printf("flow_id: %d::ETHERTYPE_IEEE_IPV4:: IP2: 0x%08x  Mask:0x%08x\n", flow_id,
                               flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv4.addr,
                               flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv4.mask);
                     } else {
		         /* Set IP Version to IPv6 */
		         flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_6;
		         /* match 1st IP address - Depends on SRC or DEST Flag*/
                         flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_IPV6;        //0x86DD
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3] = 0xA000000A;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2] = 0xB000000B;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1] = 0xC000000C;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0] = 0x1+flow_id; 
			 
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0] = 0xFFFFFFFF;

	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: IP1: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0]);
	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: MSK: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0]);
                     }
                 }
                 /* IP1 */
		 /* Set dest port to 319 to receive PTP event messages */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val = 319; 	 /* UDP Dest Port 319/320 */
		 /* Set dest port mask 0 means any port 0xFFFF means exact match to given port */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_mask = 0xffff;  /* UDP Dest Port Mask	*/
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val = 1;		/* UDP Source Port */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_mask = 0xffff; 	  /* UDP Source Port Mask */
                 printf("Flow: %d  IP1: UDP_dport: %d;   UDP_Sport: %d\n", flow_id,
		     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val,
		     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val);

                 /* IP2 */
		 /* Set dest port to 319 to receive PTP event messages */
		 flow_conf->flow_conf.ptp.ip2_opt.comm_opt.dport_val = 319; 	 /* UDP Dest Port 319/320 */
		 /* Set dest port mask 0 means any port 0xFFFF means exact match to given port */
		 flow_conf->flow_conf.ptp.ip2_opt.comm_opt.dport_mask = 0xffff;  /* UDP Dest Port Mask	*/
		 flow_conf->flow_conf.ptp.ip2_opt.comm_opt.sport_val = 1;		/* UDP Source Port */
		 flow_conf->flow_conf.ptp.ip2_opt.comm_opt.sport_mask = 0xffff; 	  /* UDP Source Port Mask */
                 printf("Flow: %d  IP2: UDP_dport: %d;   UDP_Sport: %d\n", flow_id,
		     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val,
		     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val);

		 rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
		 if (rc == VTSS_RC_OK) {
			 printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		 } else {
			 printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			 break;
		 }
	         printf("Egress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/IP/IP/PTP \n", 
                    egr_port_no, eng_id, flow_id, numflows);
		
		rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		} else {
			printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			break;
		}
	} while (0);
}

vtss_rc vtss_1588_sample_flows_eep(const vtss_inst_t inst, 
                                    const vtss_port_no_t ing_port_no, 
                                    const vtss_port_no_t egr_port_no, 
	                            const vtss_phy_ts_engine_t eng_id,
                                    int   numflows, 
                                    const u8 in_flow)
{
	vtss_rc rc = VTSS_RC_ERROR;
	vtss_phy_ts_engine_flow_conf_t *flow_conf;
        u8 flow_id = 0;

	if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
		printf("Engine flow_conf memory allocation Failed!\n");
		return -1;
	}
	memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

        printf("Ingress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/ETH/PTP \n",
                    ing_port_no, eng_id, flow_id, numflows);

        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

	do {
		rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
			break;
                }

                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
		    /* Map each flow to the channel which already mapped to the port */
		    flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
		    /* Enable the MAC flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
		    /* Notify the engine which mac address needs to be matched(dest/src) */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		    /* Notify the engine if it is VLAN flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = FALSE;
		    /* Configure the MAC address of the flow, needs to be time stamped */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
	             printf("flow_id: %d::ETH1 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);
		
		    /* Enable the MAC flow */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].flow_en = TRUE;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
		     /* Notify the engine which mac address needs to be matched(dest/src) */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		     /* Notify the engine if it is VLAN flow */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].vlan_check = FALSE;
		     /* Configure the MAC address of the flow, needs to be time stamped */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5] = 0x21+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
	             printf("flow_id: %d::ETH2 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5]);
                }

		flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_802_1_AD;	//0x88A8; 
		flow_conf->flow_conf.ptp.eth2_opt.comm_opt.etype = ETHERTYPE_IEEE_PTP_1588; 	//0x0800; 

		rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
		if (rc == VTSS_RC_OK) {
		    printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		} else {
		    printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
		    break;
		}
                printf("Egress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/ETH/PTP \n",
                    egr_port_no, eng_id, flow_id, numflows);
		
		rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		} else {
			printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			break;
		}

	} while (0);
}

vtss_rc vtss_1588_sample_flows_eeip(const vtss_inst_t inst, 
                                    const vtss_port_no_t ing_port_no, 
                                    const vtss_port_no_t egr_port_no, 
	                            const vtss_phy_ts_engine_t eng_id,
                                    int   numflows, 
                                    const u8 in_flow)
{
	vtss_rc rc = VTSS_RC_ERROR;
	vtss_phy_ts_engine_flow_conf_t *flow_conf;
        u8   flow_id = 0;
        char value_str[20] = {0};
	unsigned char ipver=0;

	if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
		printf("Engine flow_conf memory allocation Failed!\n");
		return -1;
	}
	memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

	printf("Ingress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/ETH/IP/PTP \n", 
                    ing_port_no, eng_id, flow_id, numflows);

        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

        do {
                printf ("Select IP version Mode (0 = IPv4; 1 = IPv6):");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                ipver = strtol(value_str, NULL, 10);
                if ((ipver == 0) || (ipver == 1)) {
                        printf ("IP Version : %d  : %s   Selected!!\n ", ipver, (ipver == 1 ? "IPv6" : "IPv4"));
                } else {
                        printf ("INVALID OPTION Selected!!      Options are: 0/1\n");
                }

        } while (!((ipver == 0) || (ipver == 1)));

	do {

		rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
			break;
		}

		/* engine enable */
		flow_conf->eng_mode = TRUE;
                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
		    /* Map each flow to the channel which already mapped to the port */
		    flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;

		    /* Enable the MAC flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
		    /* Notify the engine which mac address needs to be matched(dest/src) */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		    /* Notify the engine if it is VLAN flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = FALSE;
		    /* Configure the MAC address of the flow, needs to be time stamped */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
	             printf("flow_id: %d::ETH1 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);

		     flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_802_1_AD;	//0x88A8; 
		     flow_conf->flow_conf.ptp.eth2_opt.comm_opt.etype = ETHERTYPE_IEEE_IPV4; 		//0x0800; 

		    /* Enable the ETH-2 flow */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].flow_en = TRUE;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
		     /* Notify the engine which mac address needs to be matched(dest/src) */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		     /* Notify the engine if it is VLAN flow */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].vlan_check = FALSE;
		     /* Configure the MAC address of the flow, needs to be time stamped */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5] = 0x21+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */

	             printf("flow_id: %d::ETH2 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5]);

		     /* Enable the IP flow */
		     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].flow_en = TRUE;
		 
		     /* match 1st IP address - Depends on SRC or DEST Flag*/
		     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].match_mode = VTSS_PHY_TS_IP_MATCH_DEST;
                     if(ipver == 0 ){
                         /* Set IP Version to IPv4 */
                         flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_4;
                         /* match 1st IP address - Depends on SRC or DEST Flag*/
                         flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.mask = 0xffffffff;
                         flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.addr = 0x0a0a0a0a+flow_id;     /* 153.136.119.102      <<<< FLow_Diff */
                         printf("flow_id: %d::ETHERTYPE_IEEE_IPV4:: IP1: 0x%08x  Mask:0x%08x\n", flow_id,
                               flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.addr,
                               flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.mask);
                     } else {
		         /* Set IP Version to IPv6 */
		         flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_6;
		         /* match 1st IP address - Depends on SRC or DEST Flag*/
                         flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_IPV6;        //0x86DD
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3] = 0xA000000A;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2] = 0xB000000B;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1] = 0xC000000C;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0] = 0x1+flow_id; 
			 
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0] = 0xFFFFFFFF;

	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: IP1: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0]);
	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: MSK: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0]);
                     }
                 }
		 /* Set dest port to 319 to receive PTP event messages */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val = 319; 	 /* UDP Dest Port 319/320 */
		 /* Set dest port mask 0 means any port 0xFFFF means exact match to given port */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_mask = 0xffff;  /* UDP Dest Port Mask	*/
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val = 1;		/* UDP Source Port */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_mask = 0xffff; 	  /* UDP Source Port Mask */

                 printf("Flow: %d  IP1: UDP_dport: %d;   UDP_Sport: %d\n", flow_id,
		     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val,
		     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val);

		 rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
		 if (rc == VTSS_RC_OK) {
			 printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		 } else {
			 printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			 break;
		 }
	        printf("Egress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/ETH/IP/PTP \n", 
                    egr_port_no, eng_id, flow_id, numflows);
		
		rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		} else {
			printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			break;
		}
	} while (0);
}

vtss_rc vtss_1588_sample_flows_emip(const vtss_inst_t inst, 
                                    const vtss_port_no_t ing_port_no, 
                                    const vtss_port_no_t egr_port_no, 
	                            const vtss_phy_ts_engine_t eng_id,
                                    int   numflows, 
                                    const u8 in_flow)
{
	vtss_rc rc = VTSS_RC_ERROR;
	vtss_phy_ts_engine_flow_conf_t *flow_conf;
        u8   flow_id = 0;
        char value_str[20] = {0};
	unsigned char ipver=0;

	if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
		printf("Engine flow_conf memory allocation Failed!\n");
		return -1;
	}
	memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

        printf("Ingress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/MPLS/IP/PTP \n",
                    ing_port_no, eng_id, flow_id, numflows);

        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

        do {
                printf ("Select IP version Mode (0 = IPv4; 1 = IPv6):");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                ipver = strtol(value_str, NULL, 10);
                if ((ipver == 0) || (ipver == 1)) {
                        printf ("IP Version : %d  : %s   Selected!!\n ", ipver, (ipver == 1 ? "IPv6" : "IPv4"));
                } else {
                        printf ("INVALID OPTION Selected!!      Options are: 0/1\n");
                }

        } while (!((ipver == 0) || (ipver == 1)));

	do {

		rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
			break;
		}

		/* engine enable */
		flow_conf->eng_mode = TRUE;
                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
		    /* Map each flow to the channel which already mapped to the port */
		    flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
		    /* Enable the MAC flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
		    /* Notify the engine which mac address needs to be matched(dest/src) */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		    /* Notify the engine if it is VLAN flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = FALSE;
		    /* Configure the MAC address of the flow, needs to be time stamped */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
	             printf("flow_id: %d::ETH1 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);

		    flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_MPLS_UNI; 	//0x8847; 
		
		    /* Enable the MPLS flow */
		    flow_conf->flow_conf.ptp.mpls_opt.comm_opt.cw_en = FALSE;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].flow_en = TRUE;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_depth = VTSS_PHY_TS_MPLS_STACK_DEPTH_1;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_ref_point = VTSS_PHY_TS_MPLS_STACK_REF_POINT_END;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.top.upper = 0xFFFFF;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.top.lower = 0xF;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.frst_lvl_after_top.upper = 0xFFFFF;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.frst_lvl_after_top.lower =0xF;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.snd_lvl_after_top.upper = 0xFFFFF;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.snd_lvl_after_top.lower = 0xF;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.thrd_lvl_after_top.upper = 0xFFFFF;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.thrd_lvl_after_top.lower = 0xF;
		
		    /* Enable the IP flow */
		    flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].flow_en = TRUE;
		    /* match 1st IP address - Depends on SRC or DEST Flag*/
		    flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].match_mode = VTSS_PHY_TS_IP_MATCH_DEST;
                    if(ipver == 0 ){
                         /* Set IP Version to IPv4 */
                         flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_4;
                         /* match 1st IP address - Depends on SRC or DEST Flag*/
                         flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.mask = 0xffffffff;
                         flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.addr = 0x0a0a0a0a+flow_id;     /* 153.136.119.102      <<<< FLow_Diff */
                         printf("flow_id: %d::ETHERTYPE_IEEE_IPV4:: IP1: 0x%08x  Mask:0x%08x\n", flow_id,
                               flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.addr,
                               flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.mask);
                    } else {
		         /* Set IP Version to IPv6 */
		         flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_6;
		         /* match 1st IP address - Depends on SRC or DEST Flag*/
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3] = 0xA000000A;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2] = 0xB000000B;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1] = 0xC000000C;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0] = 0x1+flow_id; 
			 
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0] = 0xFFFFFFFF;

	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: IP1: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0]);
	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: MSK: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0]);
                    }
                 }
		 /* Set dest port to 319 to receive PTP event messages */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val = 319; 	 /* UDP Dest Port 319/320 */
		 /* Set dest port mask 0 means any port 0xFFFF means exact match to given port */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_mask = 0xffff;  /* UDP Dest Port Mask	*/
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val = 1;		/* UDP Source Port */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_mask = 0xffff; 	  /* UDP Source Port Mask */

                 printf("Flow: %d  IP1: UDP_dport: %d;   UDP_Sport: %d\n", flow_id,
		     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val,
		     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val);

		 rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
		 if (rc == VTSS_RC_OK) {
			 printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		 } else {
			 printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			 break;
		 }
                printf("Engress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/MPLS/IP/PTP \n",
                    egr_port_no, eng_id, flow_id, numflows);
		
		rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		} else {
			printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			break;
		}

	} while (0);

	
}

vtss_rc vtss_1588_sample_flows_emep(const vtss_inst_t inst, 
                                    const vtss_port_no_t ing_port_no, 
                                    const vtss_port_no_t egr_port_no, 
	                            const vtss_phy_ts_engine_t eng_id,
                                    int   numflows, 
                                    const u8 in_flow)
{
	vtss_rc rc = VTSS_RC_ERROR;
	vtss_phy_ts_engine_flow_conf_t *flow_conf;
        u8   flow_id = 0;

	if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
		printf("Engine flow_conf memory allocation Failed!\n");
		return -1;
	}
	memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

        printf("Ingress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/MPLS/ETH/PTP \n",
                    ing_port_no, eng_id, flow_id, numflows);

        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

	do {

		rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
			break;
		}

		/* engine enable */
		flow_conf->eng_mode = TRUE;
                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
		    /* Map each flow to the channel which already mapped to the port */
		    flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
		    /* Enable the MAC flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
		    /* Notify the engine which mac address needs to be matched(dest/src) */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		    /* Notify the engine if it is VLAN flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = FALSE;
		    /* Configure the MAC address of the flow, needs to be time stamped */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
	            printf("flow_id: %d::ETH1 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);

		     flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_MPLS_UNI; 	//0x8847; 
		     flow_conf->flow_conf.ptp.eth2_opt.comm_opt.etype = ETHERTYPE_IEEE_PTP_1588; 	//0x0800; 
		
		    /* Enable the MPLS flow */
		     flow_conf->flow_conf.ptp.mpls_opt.comm_opt.cw_en = FALSE;
		     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].flow_en = TRUE;
		     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_depth = VTSS_PHY_TS_MPLS_STACK_DEPTH_1;
		     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_ref_point = VTSS_PHY_TS_MPLS_STACK_REF_POINT_END;
		     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.top.upper = 0xFFFFF;
		     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.top.lower = 0xF;
		     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.frst_lvl_after_top.upper = 0xFFFFF;
		     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.frst_lvl_after_top.lower =0xF;
		     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.snd_lvl_after_top.upper = 0xFFFFF;
		     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.snd_lvl_after_top.lower = 0xF;
		     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.thrd_lvl_after_top.upper = 0xFFFFF;
                     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.thrd_lvl_after_top.lower = 0xF;
	 	
		    /* Enable the MAC flow */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].flow_en = TRUE;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
		     /* Notify the engine which mac address needs to be matched(dest/src) */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		     /* Notify the engine if it is VLAN flow */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].vlan_check = FALSE;
		     /* Configure the MAC address of the flow, needs to be time stamped */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5] = 0x21+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
	            printf("flow_id: %d::ETH2 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5]);
                 }


		 rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
		 if (rc == VTSS_RC_OK) {
			 printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		 } else {
			 printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			 break;
		 }
                printf("Egress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/MPLS/ETH/PTP \n",
                    egr_port_no, eng_id, flow_id, numflows);
		
		rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		} else {
			printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			break;
		}

	} while (0);
	
}

vtss_rc vtss_1588_sample_flows_emeip(const vtss_inst_t inst, 
                                    const vtss_port_no_t ing_port_no, 
                                    const vtss_port_no_t egr_port_no, 
	                            const vtss_phy_ts_engine_t eng_id,
                                    int   numflows, 
                                    const u8 in_flow)
{
	vtss_rc rc = VTSS_RC_ERROR;
	vtss_phy_ts_engine_flow_conf_t *flow_conf;
        u8   flow_id = 0;
        char value_str[20] = {0};
	unsigned char ipver=0;

	if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
		printf("Engine flow_conf memory allocation Failed!\n");
		return -1;
	}
	memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

        printf("Ingress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/MPLS/ETH/IP/PTP \n",
                    ing_port_no, eng_id, flow_id, numflows);

        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

        do {
                printf ("Select IP version Mode (0 = IPv4; 1 = IPv6):");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                ipver = strtol(value_str, NULL, 10);
                if ((ipver == 0) || (ipver == 1)) {
                        printf ("IP Version : %d  : %s   Selected!!\n ", ipver, (ipver == 1 ? "IPv6" : "IPv4"));
                } else {
                        printf ("INVALID OPTION Selected!!      Options are: 0/1\n");
                }

        } while (!((ipver == 0) || (ipver == 1)));

	do {

		rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
			break;
		}

		/* engine enable */
		flow_conf->eng_mode = TRUE;
                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
		   /* Map each flow to the channel which already mapped to the port */
		   flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
		   /* Enable the MAC flow */
		   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
		   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
		   /* Notify the engine which mac address needs to be matched(dest/src) */
		   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		   /* Notify the engine if it is VLAN flow */
		   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = FALSE;
		   /* Configure the MAC address of the flow, needs to be time stamped */
		   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
	           printf("flow_id: %d::ETH1 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);

		
		   flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_MPLS_UNI; 	//0x8847; 
		   /* Enable the IP flow */
		
		   /* Enable the MPLS flow */
		   flow_conf->flow_conf.ptp.mpls_opt.comm_opt.cw_en = FALSE;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].flow_en = TRUE;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_depth = VTSS_PHY_TS_MPLS_STACK_DEPTH_1;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_ref_point = VTSS_PHY_TS_MPLS_STACK_REF_POINT_END;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.top.upper = 0xFFFFF;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.top.lower = 0xF;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.frst_lvl_after_top.upper = 0xFFFFF;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.frst_lvl_after_top.lower =0xF;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.snd_lvl_after_top.upper = 0xFFFFF;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.snd_lvl_after_top.lower = 0xF;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.thrd_lvl_after_top.upper = 0xFFFFF;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.thrd_lvl_after_top.lower = 0xF;
		
		   /* Enable the MAC flow */
		   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].flow_en = TRUE;
		   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
		   /* Notify the engine which mac address needs to be matched(dest/src) */
		   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		   /* Notify the engine if it is VLAN flow */
		   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].vlan_check = FALSE;
		   /* Configure the MAC address of the flow, needs to be time stamped */
		   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5] = 0x21+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
	           printf("flow_id: %d::ETH2 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5]);

		    /* Enable the IP1 flow */
		    flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].flow_en = TRUE;
		    /* match 1st IP address - Depends on SRC or DEST Flag*/
		    flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].match_mode = VTSS_PHY_TS_IP_MATCH_DEST;
                    if(ipver == 0 ){
                         /* match 1st IP address - Depends on SRC or DEST Flag*/
                         flow_conf->flow_conf.ptp.eth2_opt.comm_opt.etype = ETHERTYPE_IEEE_IPV4;    //0x0800; 
                         /* Set IP Version to IPv4 */
                         flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_4;
                         flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.mask = 0xffffffff;
                         flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.addr = 0x0a0a0a0a+flow_id;     /* 153.136.119.102      <<<< FLow_Diff */
                         printf("flow_id: %d::ETHERTYPE_IEEE_IPV4:: IP1: 0x%08x  Mask:0x%08x\n", flow_id,
                               flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.addr,
                               flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.mask);
                    } else {
                         flow_conf->flow_conf.ptp.eth2_opt.comm_opt.etype = ETHERTYPE_IEEE_IPV6;    //0x0800; 
		         /* Set IP Version to IPv6 */
		         flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_6;
		         /* match 1st IP address - Depends on SRC or DEST Flag*/
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3] = 0xA000000A;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2] = 0xB000000B;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1] = 0xC000000C;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0] = 0x1+flow_id; 
			 
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0] = 0xFFFFFFFF;

	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: IP1: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0]);
	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: MSK: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0]);
                    }
                 }
		 /* Set dest port to 319 to receive PTP event messages */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val = 319; 	 /* UDP Dest Port 319/320 */
		 /* Set dest port mask 0 means any port 0xFFFF means exact match to given port */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_mask = 0xffff;  /* UDP Dest Port Mask	*/
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val = 1;		/* UDP Source Port */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_mask = 0xffff; 	  /* UDP Source Port Mask */

                 printf("Flow: %d  IP1: UDP_dport: %d;   UDP_Sport: %d\n", flow_id,
		     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val,
		     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val);

		 rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
		 if (rc == VTSS_RC_OK) {
			 printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		 } else {
			 printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			 break;
		 }
                printf("Egress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/MPLS/ETH/IP/PTP \n",
                    egr_port_no, eng_id, flow_id, numflows);
		
		rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		} else {
			printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			break;
		}

	} while (0);

	
}


vtss_rc vtss_1588_sample_flows_eeoam(const vtss_inst_t inst,
                                  const vtss_port_no_t ing_port_no,
                                  const vtss_port_no_t egr_port_no,
                                  const vtss_phy_ts_engine_t eng_id,
                                  int   numflows,
                                  u8    in_flow)
{
        vtss_rc rc = VTSS_RC_ERROR;
        u8      flow_id = 0;
        vtss_phy_ts_engine_flow_conf_t *flow_conf;

        if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
                printf("Engine flow_conf memory allocation Failed!\n");
                return -1;
        }
        memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

        printf("Ingress:: Port:%d : Engine#%d  Flow_id:%d, numFlows:%d :: Encapsulation: ETH/OAM \n",
                          ing_port_no, eng_id, in_flow, numflows);

        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

        do {
                rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
                if (rc != VTSS_RC_OK) {
                        printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
                        break;
                }

                /* engine enable */
                flow_conf->eng_mode = TRUE;
                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
                    /* Map each flow to the channel which already mapped to the port */
                    flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;

                    /* Enable the MAC flow */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
                    /* Notify the engine which mac address needs to be matched(dest/src) */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
                    /* Notify the engine if it is VLAN flow */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = FALSE;
                    /* Configure the MAC address of the flow, needs to be time stamped */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                    /* ************************************************************************* */
                    /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                    /* ************************************************************************* */

                   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].num_tag = 2;
                   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag_type = VTSS_PHY_TS_TAG_TYPE_B;
                   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag_type = VTSS_PHY_TS_TAG_TYPE_I;
                   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].tag_range_mode = VTSS_PHY_TS_TAG_RANGE_NONE;
                   printf ("VLAN num_tags: %d, TagRange: 0x%04X;   OuterTagType: 0x%04X;  InnerTagType: 0x%04X \n",
                       flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].num_tag,
                       flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].tag_range_mode,
                       flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag_type,
                       flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag_type);

		   flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_802_1_AD;  //0x88A8; 
                   /* Enable the IP flow */
                   printf("flow_id: %d::ETHERTYPE: 0x%04X:: MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
                        flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype,
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);

                   /* Enable the MAC flow */
                   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].flow_en = TRUE;
                   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
                   /* Notify the engine which mac address needs to be matched(dest/src) */
                   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
                   /* Notify the engine if it is VLAN flow */
                   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].vlan_check = FALSE;
                   /* Configure the MAC address of the flow, needs to be time stamped */
                   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
                   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
                   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
                   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
                   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
                   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5] = 0x21+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
                   flow_conf->flow_conf.ptp.eth2_opt.comm_opt.etype = ETHERTYPE_IEEE_802_1_AG;    // 0x8902

                   printf("flow_id: %d::ETH2-ETHERTYPE: 0x%04X:: MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
                     flow_conf->flow_conf.ptp.eth2_opt.comm_opt.etype,
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0],
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1],
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2],
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3],
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4],
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5]);

               }

                rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
                if (rc == VTSS_RC_OK) {
                         printf("PHY TS Engine %d  Conf_set Success \n", eng_id);
                } else {
                         printf("PHY TS Engine %d  Conf_set Failed! \n", eng_id);
                         break;
                }
                printf("Egress:: Port:%d : Engine#%d  Flow_id:%d, numFlows:%d :: ETH/OAM\n",
                          egr_port_no, eng_id, flow_id, numflows);

                rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
                if (rc == VTSS_RC_OK) {
                        printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
                } else {
                        printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
                        break;
                }
        } while (0);

}


vtss_rc vtss_1588_sample_flows_emeoam(const vtss_inst_t inst,
                                  const vtss_port_no_t ing_port_no,
                                  const vtss_port_no_t egr_port_no,
                                  const vtss_phy_ts_engine_t eng_id,
                                  int   numflows,
                                  u8    in_flow)
{
        vtss_rc rc = VTSS_RC_ERROR;
        u8      flow_id = 0;
        vtss_phy_ts_engine_flow_conf_t *flow_conf;

        if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
                printf("Engine flow_conf memory allocation Failed!\n");
                return -1;
        }
        memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

        printf("Ingress:: Port:%d : Engine#%d  Flow_id:%d, numFlows:%d :: Encapsulation: ETH/OAM \n",
                          ing_port_no, eng_id, in_flow, numflows);

        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

        do {
                rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
                if (rc != VTSS_RC_OK) {
                        printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
                        break;
                }

                /* engine enable */
                flow_conf->eng_mode = TRUE;
                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
                    /* Map each flow to the channel which already mapped to the port */
                    flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;

                    /* Enable the MAC flow */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
                    /* Notify the engine which mac address needs to be matched(dest/src) */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
                    /* Configure the MAC address of the flow, needs to be time stamped */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                    /* ************************************************************************* */
                    /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                    /* ************************************************************************* */
                    /* Notify the engine if it is VLAN flow */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = FALSE; 
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].num_tag = 0;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag_type = VTSS_PHY_TS_TAG_TYPE_S;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag_type = VTSS_PHY_TS_TAG_TYPE_C;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].tag_range_mode = VTSS_PHY_TS_TAG_RANGE_NONE;
                    printf ("ETH1: VLAN num_tags: %d, TagRange: 0x%04X;   OuterTagType: 0x%04X;  InnerTagType: 0x%04X \n",
                       flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].num_tag,
                       flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].tag_range_mode,
                       flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag_type,
                       flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag_type);

                    flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_MPLS_UNI;  //0x8847; 
                    flow_conf->flow_conf.ptp.eth1_opt.comm_opt.pbb_en = FALSE;

                    printf("flow_id: %d::ETH1-ETHERTYPE: 0x%04X:: MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
                        flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype,
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);


                    /* Enable the MPLS flow */
                    flow_conf->flow_conf.ptp.mpls_opt.comm_opt.cw_en = FALSE;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].flow_en = TRUE;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_depth = VTSS_PHY_TS_MPLS_STACK_DEPTH_1;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_ref_point = VTSS_PHY_TS_MPLS_STACK_REF_POINT_TOP;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.top.upper = 40;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.top.lower = 30;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.frst_lvl_after_top.upper = 0xFFFFF;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.frst_lvl_after_top.lower = 0xF;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.snd_lvl_after_top.upper = 0xFFFFF;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.snd_lvl_after_top.lower = 0xF;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.thrd_lvl_after_top.upper = 0xFFFFF;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.thrd_lvl_after_top.lower = 0xF;

                    /* Enable the MAC flow */
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].flow_en = TRUE;
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
                    /* Notify the engine which mac address needs to be matched(dest/src) */
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
                    /* Notify the engine if it is VLAN flow */
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].vlan_check = TRUE; 
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].num_tag = 0;
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].outer_tag_type = VTSS_PHY_TS_TAG_TYPE_S;
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].inner_tag_type = VTSS_PHY_TS_TAG_TYPE_C;
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].tag_range_mode = VTSS_PHY_TS_TAG_RANGE_NONE;
                    printf ("ETH2: VLAN num_tags: %d, TagRange: 0x%04X;   OuterTagType: 0x%04X;  InnerTagType: 0x%04X \n",
                       flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].num_tag,
                       flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].tag_range_mode,
                       flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].outer_tag_type,
                       flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].inner_tag_type);

                    /* Configure the MAC address of the flow, needs to be time stamped */
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5] = 0x21+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
                    flow_conf->flow_conf.ptp.eth2_opt.comm_opt.etype = ETHERTYPE_IEEE_802_1_AG;      //0x8902

                    printf("flow_id: %d::ETH2-ETHERTYPE: 0x%04X:: MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
                     flow_conf->flow_conf.ptp.eth2_opt.comm_opt.etype,
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0],
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1],
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2],
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3],
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4],
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5]);
                }

                rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
                if (rc == VTSS_RC_OK) {
                         printf("PHY TS Engine %d  Conf_set Success \n", eng_id);
                } else {
                         printf("PHY TS Engine %d  Conf_set Failed! \n", eng_id);
                         break;
                }
                printf("Egress:: Port:%d : Engine#%d  Flow_id:%d, numFlows:%d :: ETH/OAM\n",
                          egr_port_no, eng_id, flow_id, numflows);

                rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
                if (rc == VTSS_RC_OK) {
                        printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
                } else {
                        printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
                        break;
                }
        } while (0);

}


vtss_rc vtss_1588_sample_actions(const vtss_inst_t inst, 
                                 const vtss_port_no_t ing_port_no, 
                                 const vtss_port_no_t egr_port_no,
	                             const vtss_phy_ts_engine_t eng_id,
                                 const u8 action_id)
{
	vtss_rc rc = VTSS_RC_ERROR;
	vtss_phy_ts_engine_action_t *ptp_action;
	vtss_phy_ts_ptp_clock_mode_t   clk_mode;
	vtss_phy_ts_ptp_delaym_type_t	delay_type = VTSS_PHY_TS_PTP_DELAYM_E2E;
    char value_str[255] = {0};
	
	printf ("\nPTP Clock configuration: BC1STEP/BC2STEP/TC1STEP/TC2STEP/DELAY_COMP_ENG\n\n");

	if ((ptp_action = (vtss_phy_ts_engine_action_t*)malloc(sizeof(vtss_phy_ts_engine_action_t))) == NULL) {
		printf("Engine ptp_action memory allocation Failed!\n");
		return -1;
	}
	memset(ptp_action, 0, sizeof(vtss_phy_ts_engine_action_t));
	do {

		printf ("Select Clock Mode (0=BC1STEP/1=BC2STEP/2=TC1STEP/3=TC2STEP/4=DELAY_COMP_ENG:");
		memset (&value_str[0], 0, sizeof(value_str));
		scanf("%s", &value_str[0]);
		clk_mode = strtol(value_str, NULL, 10);
		if ((clk_mode <= 4) && (clk_mode >= 0)) {
			printf ("Clock Mode OPTION: %d	 Selected!! \n", clk_mode);
		} else {
			printf ("INVALID OPTION Selected!!	Options are: 0/1/2/3/4 \n");
		}
		
	} while (!((clk_mode <= 4) && (clk_mode >= 0)));

	
    printf("Ingress Clock Action: Engine#%d, action_id: %d,  clk_mode: %s, Delay_Type: %s \n", eng_id, action_id, 
                    (clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_BC1STEP ? "BC1STEP" : 
                     clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_BC2STEP ? "BC2STEP" :
                     clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_TC1STEP ? "TC1STEP" :
                     clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_TC2STEP ? "TC2STEP" : 
                     clk_mode == VTSS_PHY_TS_PTP_DELAY_COMP_ENGINE  ? "DELAY_COMP_ENG" : "INVALID CLK MODE SELECTION"),
                    (delay_type == VTSS_PHY_TS_PTP_DELAYM_P2P ? "DELAY_P2P" :
                     delay_type == VTSS_PHY_TS_PTP_DELAYM_E2E ? "DELAY_E2E" : "INVALID DELAY SELECTION"));

	do {
		rc = vtss_phy_ts_ingress_engine_action_get(inst, ing_port_no, eng_id, ptp_action);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Engine Action_get Failed!\n");
			break;
		}

		ptp_action->action_ptp = TRUE;
		ptp_action->action.ptp_conf[action_id].enable = TRUE;
		ptp_action->action.ptp_conf[action_id].channel_map = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
		ptp_action->action.ptp_conf[action_id].ptp_conf.range_en = FALSE;
		ptp_action->action.ptp_conf[action_id].clk_mode = clk_mode;	    // bc1step, bc2step,  tc1step, tc2step
		ptp_action->action.ptp_conf[action_id].delaym_type = delay_type;    // P2P or E2E

		rc = vtss_phy_ts_ingress_engine_action_set(inst, ing_port_no, eng_id, ptp_action);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Engine %d  Action_set Success\n", eng_id);
		} else {
			printf("PHY TS Engine %d  Action_set Failed!\n", eng_id);
			break;
		}

		memset(ptp_action, 0, sizeof(vtss_phy_ts_engine_action_t));
		
		printf("Egress Clock Action: Engine#%d, action_id: %d,  clk_mode: %s, Delay_Type: %s \n", eng_id, action_id, 
                        (clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_BC1STEP ? "BC1STEP" : 
                         clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_BC2STEP ? "BC2STEP" :
                         clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_TC1STEP ? "TC1STEP" :
                         clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_TC2STEP ? "TC2STEP" : 
                         clk_mode == VTSS_PHY_TS_PTP_DELAY_COMP_ENGINE  ? "DELAY_COMP_ENG" : "INVALID CLK MODE SELECTION"),
                        (delay_type == VTSS_PHY_TS_PTP_DELAYM_P2P ? "DELAY_P2P" :
                         delay_type == VTSS_PHY_TS_PTP_DELAYM_E2E ? "DELAY_E2E" : "INVALID DELAY SELECTION"));

		rc = vtss_phy_ts_egress_engine_action_get(inst, egr_port_no, eng_id, ptp_action);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Engine %d  Action_get Failed!\n", eng_id);
			break;
		}

		ptp_action->action_ptp = TRUE;
		ptp_action->action.ptp_conf[action_id].enable = TRUE;
		ptp_action->action.ptp_conf[action_id].channel_map = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
		ptp_action->action.ptp_conf[action_id].ptp_conf.range_en = FALSE;
		ptp_action->action.ptp_conf[action_id].clk_mode = clk_mode;	    // bc1step, bc2step,  tc1step, tc2step
		ptp_action->action.ptp_conf[action_id].delaym_type = delay_type;    // P2P or E2E

		rc = vtss_phy_ts_egress_engine_action_set(inst, egr_port_no, eng_id, ptp_action);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Engine %d  Action_set Success\n", eng_id);
		} else {
			printf("PHY TS Engine %d  Action_set Failed!\n", eng_id);
			break;
		}
		
	} while (0);
	return rc;
}


vtss_rc vtss_oam_sample_actions(const vtss_inst_t inst,
                                 const vtss_port_no_t ing_port_no,
                                 const vtss_port_no_t egr_port_no,
                                 const vtss_phy_ts_engine_t eng_id )
{
        vtss_rc rc = VTSS_RC_ERROR;
        vtss_phy_ts_engine_action_t *ptp_action;
        vtss_phy_ts_oam_engine_action_t *oam_action;
        vtss_phy_ts_ptp_delaym_type_t   delay_type = VTSS_PHY_TS_PTP_DELAYM_E2E;
        char value_str[255] = {0};

        printf ("\n OAM Action configuration:\n\n");

        if ((ptp_action = (vtss_phy_ts_engine_action_t*)malloc(sizeof(vtss_phy_ts_engine_action_t))) == NULL) {
                printf("Engine ptp_action memory allocation Failed!\n");
                return -1;
        }
        memset(ptp_action, 0, sizeof(vtss_phy_ts_engine_action_t));

        do {
                rc = vtss_phy_ts_ingress_engine_action_get(inst, ing_port_no, eng_id, ptp_action);
                if (rc != VTSS_RC_OK) {
                        printf("PHY TS Engine Action_get Failed!\n");
                        break;
                }
                oam_action = &ptp_action->action.oam_conf[0];
                oam_action->enable = TRUE;
                oam_action->channel_map =  VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
                oam_action->version     = 0;
                oam_action->y1731_en    = TRUE;
                oam_action->oam_conf.y1731_oam_conf.delaym_type = VTSS_PHY_TS_IETF_MPLS_ACH_OAM_DELAYM_DMM;
                oam_action->oam_conf.y1731_oam_conf.delaym_type = VTSS_PHY_TS_Y1731_OAM_DELAYM_1DM;
                oam_action->oam_conf.y1731_oam_conf.range_en = TRUE;
                oam_action->oam_conf.y1731_oam_conf.meg_level.range.lower = 0;
                oam_action->oam_conf.y1731_oam_conf.meg_level.range.upper = 0xF;

                rc = vtss_phy_ts_ingress_engine_action_set(inst, ing_port_no, eng_id, ptp_action);
                if (rc == VTSS_RC_OK) {
                        printf("PHY TS Engine %d  Action_set Success\n", eng_id);
                } else {
                        printf("PHY TS Engine %d  Action_set Failed!\n", eng_id);
                        break;
                }

                memset(ptp_action, 0, sizeof(vtss_phy_ts_engine_action_t));


                rc = vtss_phy_ts_egress_engine_action_get(inst, egr_port_no, eng_id, ptp_action);
                if (rc != VTSS_RC_OK) {
                        printf("PHY TS Engine %d  Action_get Failed!\n", eng_id);
                        break;
                }

                oam_action = &ptp_action->action.oam_conf[0];
                oam_action->enable = TRUE;
                oam_action->channel_map =  VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
                oam_action->version     = 0;
                oam_action->y1731_en    = TRUE;
                oam_action->oam_conf.y1731_oam_conf.delaym_type = VTSS_PHY_TS_IETF_MPLS_ACH_OAM_DELAYM_DMM;
                oam_action->oam_conf.y1731_oam_conf.delaym_type = VTSS_PHY_TS_Y1731_OAM_DELAYM_1DM;
                oam_action->oam_conf.y1731_oam_conf.range_en = TRUE;
                oam_action->oam_conf.y1731_oam_conf.meg_level.range.lower = 0;
                oam_action->oam_conf.y1731_oam_conf.meg_level.range.upper = 0xF;

                rc = vtss_phy_ts_egress_engine_action_set(inst, egr_port_no, eng_id, ptp_action);
                if (rc == VTSS_RC_OK) {
                        printf("PHY TS Engine %d  Action_set Success\n", eng_id);
                } else {
                        printf("PHY TS Engine %d  Action_set Failed!\n", eng_id);
                        break;
                }
        } while (0);

        return rc;
}



vtss_rc vtss_ptp_get_pkt_encap(vtss_phy_ts_encap_t * encap){

        char value_str[255] = {0};
	vtss_phy_ts_encap_t pkt_encap;
	BOOL invalid_input = FALSE;
	vtss_rc rc = VTSS_RC_OK;
	do {
		printf(" Enter Encapsulation Type: \n");
		printf(" \t0 = ETH/PTP \n");
		printf(" \t1 = ETH/IP/PTP \n");
		printf(" \t2 = ETH/IP/IP/PTP \n");
		printf(" \t3 = ETH/ETH/PTP \n");
		printf(" \t4 = ETH/ETH/IP/PTP \n");
		printf(" \t5 = ETH/MPLS/IP/PTP \n");
		printf(" \t6 = ETH/MPLS/ETH/PTP \n");
		printf(" \t7 = ETH/MPLS/ETH/IP/PTP \n");
		printf(" \t8 = ETH/MPLS/ACH/PTP \n");
		printf(" \t9 = ETH/OAM \n");
		printf(" \tA = ETH/ETH/OAM \n");
		printf(" \tB = ETH/MPLS/ETH/OAM \n");
		printf(" \tC = ETH/MPLS/ACH/OAM \n");
		
		printf("\nSelect the Encapsulation Type: \n");
		memset (&value_str[0], 0, sizeof(value_str));
		scanf("%s", &value_str[0]);
		
		switch (value_str[0]) {
		case '0':
			printf("VTSS_PHY_TS_ENCAP_ETH_PTP \n");
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_PTP;
			break;
		case '1':
			printf("VTSS_PHY_TS_ENCAP_ETH_IP_PTP \n");
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_IP_PTP;
			break;
		case '2':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_IP_IP_PTP;
			printf("VTSS_PHY_TS_ENCAP_ETH_IP_IP_PTP \n");
			break;
		case '3':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_ETH_PTP;
			printf("VTSS_PHY_TS_ENCAP_ETH_ETH_PTP \n");
			break;
		case '4':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_ETH_IP_PTP;
			printf("VTSS_PHY_TS_ENCAP_ETH_ETH_IP_PTP \n");
			break;
		case '5':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_MPLS_IP_PTP;
			printf("VTSS_PHY_TS_ENCAP_ETH_MPLS_IP_PTP \n");
			break;
		case '6':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_PTP;
			printf("VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_PTP \n");
			break;
		case '7':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP;
			printf("VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP \n");
			break;
		case '8':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_MPLS_ACH_PTP;
			printf("VTSS_PHY_TS_ENCAP_ETH_MPLS_ACH_PTP\n");
			break;
		/* OAM encap */
		case '9':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_OAM;
			printf("VTSS_PHY_TS_ENCAP_ETH_OAM \n");
                        break;
		case 'A': 
		case 'a': 
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_ETH_OAM;
			printf("VTSS_PHY_TS_ENCAP_ETH_ETH_OAM \n");
			break;
		case 'B':
		case 'b':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_OAM;
			printf("VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_OAM \n");
			break;
		case 'C':
		case 'c':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_MPLS_ACH_OAM; /* MPLS-TP OAM */
			printf("VTSS_PHY_TS_ENCAP_ETH_MPLS_ACH_OAM \n");
			break;
		default:
			printf("INVALID Selection!!!! Select Encapsulation type Again\n\n\n\n");
			invalid_input = TRUE;
			break;
		}
	} while(invalid_input);

	*encap = pkt_encap;
	return rc;
	
}

/* ********************************************************** */
/* *************     BOUNDARY CLOCK   *********************** */
/* ************            or            ******************** */
/* *************     TRANSPARENT CLOCK   ******************** */
/* ********************************************************** */
/* Vtss Sample Application for BC
  --->P1-->S1  --->  S2-->P1  (P:Port S: Switch)

If we pass same ing_port_no and egr_port_no to this application that port
will be configured for both ing and egr functionalities of BC App,
and needs be called on both switches.
Application: Ordinary/Boundary clock, 1 step
Delay method: End-to-End delay measurement method
*/


/* ********************************************************** */
/* ********************************************************** */

vtss_rc vtss_ptp_sample_clock(const vtss_inst_t inst, 
                              const vtss_port_no_t ing_port_no, 
                              const vtss_port_no_t egr_port_no,
	                      	  const vtss_phy_ts_engine_t  eng_id)
{
        char value_str[255] = {0};
	vtss_phy_ts_init_conf_t conf;
	u8		flow_id = 0;
	u8		ptp_action_id = 0;
	vtss_rc rc;
	int numflows = 0;  // Change the number of flows configured
                           // Value Range 1-8 and 0xff = Configure designated flow_id Only
	int start_flow = 0;
	int end_flow = 1;
	vtss_phy_ts_encap_t pkt_encap = 0;
        vtss_phy_ts_fifo_sig_mask_t    sig_mask = VTSS_PHY_TS_FIFO_SIG_SOURCE_PORT_ID | VTSS_PHY_TS_FIFO_SIG_SEQ_ID;
	
	memset(&conf, 0, sizeof(vtss_phy_ts_init_conf_t));
	//memset(&init_conf, 0, sizeof(vtss_phy_ts_eng_init_conf_t));

	/* *****************  Setup Default Configuration for 10G *********************** */
	conf.clk_freq	   = VTSS_PHY_TS_CLOCK_FREQ_250M; 		/* reference clock frequency */
	conf.clk_src	   = VTSS_PHY_TS_CLOCK_SRC_INTERNAL;		/* Clock Source */
	conf.rx_ts_pos	   = VTSS_PHY_TS_RX_TIMESTAMP_POS_IN_PTP;	/*	Rx timestamp in PTP reserved bytes */
	conf.rx_ts_len	   = VTSS_PHY_TS_RX_TIMESTAMP_LEN_30BIT; 							/*	Rx timestamp update nano seconds part */
	conf.tx_fifo_mode  = VTSS_PHY_TS_FIFO_MODE_NORMAL; 			/*	Timestamps to pushed out on the SPI interface */
	conf.tx_ts_len	   = VTSS_PHY_TS_FIFO_TIMESTAMP_LEN_10BYTE; /* 10byte Full Tx timestamp */
	conf.tc_op_mode    = VTSS_PHY_TS_TC_OP_MODE_B;	   /* TC operating mode is Mode B*/
	conf.auto_clear_ls = FALSE; 					   /* Load and Save of LTC are auto cleared */
	conf.macsec_ena    = FALSE;				   /* MACsec is enabled or disabled */
	conf.chk_ing_modified = FALSE;					   /* True if the flag bit needs to be modified in ingress and thus in egress */

        printf("\n %s :: %s :: %s \n",
	    (conf.clk_src == VTSS_PHY_TS_CLOCK_SRC_INTERNAL ? "VTSS_PHY_TS_CLOCK_SRC_INTERNAL" :
	     conf.clk_src == VTSS_PHY_TS_CLOCK_SRC_EXTERNAL ? "VTSS_PHY_TS_CLOCK_SRC_EXTERNAL" : "INVALID SRC"),
            (conf.clk_freq == VTSS_PHY_TS_CLOCK_FREQ_125M ? "VTSS_PHY_TS_CLOCK_FREQ_125M" : 
             conf.clk_freq == VTSS_PHY_TS_CLOCK_FREQ_15625M ? "VTSS_PHY_TS_CLOCK_FREQ_15625M" : 
             conf.clk_freq == VTSS_PHY_TS_CLOCK_FREQ_200M ? "VTSS_PHY_TS_CLOCK_FREQ_200M" : 
             conf.clk_freq == VTSS_PHY_TS_CLOCK_FREQ_250M ? "VTSS_PHY_TS_CLOCK_FREQ_250M" : 
             conf.clk_freq == VTSS_PHY_TS_CLOCK_FREQ_500M ? "VTSS_PHY_TS_CLOCK_FREQ_500M" : "INVALID CLOCK Freq"),
	    (conf.rx_ts_pos == VTSS_PHY_TS_RX_TIMESTAMP_POS_IN_PTP ? "VTSS_PHY_TS_RX_TIMESTAMP_POS_IN_PTP" :
	     conf.rx_ts_pos == VTSS_PHY_TS_RX_TIMESTAMP_POS_AT_END ? "VTSS_PHY_TS_RX_TIMESTAMP_POS_AT_END" : "INVALID TS POSITION"));

        printf(" %s :: %s :: %s \n",
	    (conf.rx_ts_len == VTSS_PHY_TS_RX_TIMESTAMP_LEN_30BIT ? "VTSS_PHY_TS_RX_TIMESTAMP_LEN_30BIT" :
	     conf.rx_ts_len == VTSS_PHY_TS_RX_TIMESTAMP_LEN_32BIT ? "VTSS_PHY_TS_RX_TIMESTAMP_LEN_32BIT" : "INVALID TS LENGTH"),
	    (conf.tx_fifo_mode == VTSS_PHY_TS_FIFO_MODE_NORMAL ? "VTSS_PHY_TS_FIFO_MODE_NORMAL" :
	     conf.tx_fifo_mode == VTSS_PHY_TS_FIFO_MODE_SPI ? "VTSS_PHY_TS_FIFO_MODE_SPI" : "INVALID FIFO MODE"),
	    (conf.tx_ts_len == VTSS_PHY_TS_FIFO_TIMESTAMP_LEN_10BYTE ? "VTSS_PHY_TS_FIFO_TIMESTAMP_LEN_10BYTE" :
	     conf.tx_ts_len == VTSS_PHY_TS_FIFO_TIMESTAMP_LEN_4BYTE ? "VTSS_PHY_TS_FIFO_TIMESTAMP_LEN_4BYTE" : "INVALID FIFO TS LENGTH"));

        printf(" %s :: MACSEC_ENA: %x \n",
	    (conf.tc_op_mode == VTSS_PHY_TS_TC_OP_MODE_A ? "VTSS_PHY_TS_TC_OP_MODE_A" :
	     conf.tc_op_mode == VTSS_PHY_TS_TC_OP_MODE_B ? "VTSS_PHY_TS_TC_OP_MODE_B" :
	     conf.tc_op_mode == VTSS_PHY_TS_TC_OP_MODE_C ? "VTSS_PHY_TS_TC_OP_MODE_C" : "INVALID TC OP_MODE"),
             conf.macsec_ena);

	rc = vtss_ptp_get_pkt_encap(&pkt_encap);
        printf("\nSelect the Number of Flows to configure (1-8) -- config OOS, Flows = 8  (1-8) : ");
        memset (&value_str[0], 0, sizeof(value_str));
        scanf("%s", &value_str[0]);
        numflows = atoi(value_str);
        if (numflows == 0 || numflows > 8) {
            printf("\nInvalid Number of Flows; Values are (1-7): \n");
            return;
        }
        printf("\nSelected Number of Flows: %d  \n", numflows);

	start_flow = 0;
        end_flow = numflows-1;

#if 0
i### #ifdef _INCLUDE_DEBUG_FILE_PRINT_
        fprintf(fp, "Configure 1588: Encap: %d, Engine:%d, ptp_action_id: %d, clk_mode: %s, Delay_Type: %s \n", 
                         pkt_encap, eng_id, ptp_action_id,
                        (ptp_clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_BC1STEP ? "BC1STEP" :
                         ptp_clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_BC2STEP ? "BC2STEP" :
                         ptp_clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_TC1STEP ? "TC1STEP" :
                         ptp_clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_TC2STEP ? "TC2STEP" :
                         ptp_clk_mode == VTSS_PHY_TS_PTP_DELAY_COMP_ENGINE  ? "DELAY_COMP_ENG" : "INVALID CLK MODE SELECTION"),
                        (ptp_delay_type == VTSS_PHY_TS_PTP_DELAYM_P2P ? "DELAY_P2P" :
                         ptp_delay_type == VTSS_PHY_TS_PTP_DELAYM_E2E ? "DELAY_E2E" : "INVALID DELAY SELECTION"));
#endif

	do {
		
		rc = vtss_phy_ts_init(inst, ing_port_no, &conf);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Init Success for ing_port_no: %d\n", ing_port_no);
		} else {
			printf("PHY TS Init Failed for ing_port_no: %d\n", ing_port_no);
			break;
		}

		rc = vtss_phy_ts_mode_set (inst, ing_port_no, TRUE);
		printf("PHY TS Block Ingress Port: %d, Enabled for channel 0!\n", ing_port_no);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Block Enable Failed for channel 0!\n");
			break;
		}

		if( ing_port_no!= egr_port_no ){		
			rc = vtss_phy_ts_init(inst, egr_port_no, &conf);
			if (rc == VTSS_RC_OK) { 		   
				printf("PHY TS Init Success for egr_port_no: %d\n", egr_port_no);
			} else {
				printf("PHY TS Init Failed for egr_port_no: %d\n", egr_port_no);
				break;
			}

			rc = vtss_phy_ts_mode_set (inst, egr_port_no, TRUE);
			printf("PHY TS Block Egress Port: %d, Enabled for channel 0!\n", egr_port_no);
			if (rc != VTSS_RC_OK) {
				printf("PHY TS Block Enable Failed for channel 1!\n");
				break;
			}
		}

		rc = vtss_phy_ts_ingress_engine_init(inst, ing_port_no,
						eng_id,
						pkt_encap, // VTSS_PHY_TS_ENCAP_ETH_PTP, Simpliest Match = IEEE_PTP_1588, ie. 0x88F7
						start_flow,			 // Flow Start Index
						end_flow,			 // Flow End Index 
						VTSS_PHY_TS_ENG_FLOW_MATCH_STRICT);

		if (rc == VTSS_RC_OK) {
			printf("ing_port_no: %d, PHY TS Engine %d  Init Success\n", ing_port_no, eng_id);
		} else {
			printf("ing_port_no: %d, PHY TS Engine %d  Init Failed \n", ing_port_no, eng_id);
			break;
		}

		rc = vtss_phy_ts_egress_engine_init(inst, egr_port_no,
						eng_id,
						pkt_encap,	 
						start_flow,			 // Flow Start Index
						end_flow,			 // Flow End Index 
						VTSS_PHY_TS_ENG_FLOW_MATCH_STRICT);
		
		if (rc == VTSS_RC_OK) {
			printf("Egress Port: %d, PHY TS Engine %d  Init Success\n", egr_port_no, eng_id);
		} else {
			printf("Egress Port: %d, PHY TS Engine %d  Init Failed \n", egr_port_no, eng_id);
			break;
		}

                flow_id = start_flow; // Flow_id to configure if numflows = 0xff

                switch (pkt_encap) {
                    case VTSS_PHY_TS_ENCAP_ETH_PTP:
                        vtss_1588_sample_flows_ep(inst, ing_port_no,egr_port_no, eng_id, numflows, flow_id); 
                        break;

                    case VTSS_PHY_TS_ENCAP_ETH_IP_PTP:
                        vtss_1588_sample_flows_eip(inst, ing_port_no, egr_port_no, eng_id, numflows, flow_id); 
                        break;

                    case VTSS_PHY_TS_ENCAP_ETH_IP_IP_PTP:
                        vtss_1588_sample_flows_eiip(inst, ing_port_no,egr_port_no, eng_id, numflows, flow_id); 
                        break;

                    case VTSS_PHY_TS_ENCAP_ETH_ETH_PTP:
                        vtss_1588_sample_flows_eep(inst, ing_port_no,egr_port_no, eng_id, numflows, flow_id); 
                        break;

                    case VTSS_PHY_TS_ENCAP_ETH_ETH_IP_PTP:
                        vtss_1588_sample_flows_eeip(inst, ing_port_no,egr_port_no, eng_id, numflows, flow_id); 
                        break;

                    case VTSS_PHY_TS_ENCAP_ETH_MPLS_IP_PTP:
                        vtss_1588_sample_flows_emip(inst, ing_port_no,egr_port_no, eng_id, numflows, flow_id); 
                        break;

                    case VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_PTP:
                        vtss_1588_sample_flows_emep(inst, ing_port_no,egr_port_no, eng_id, numflows, flow_id); 
                        break;

                    case VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP:
                        vtss_1588_sample_flows_emeip(inst, ing_port_no,egr_port_no, eng_id, numflows, flow_id); 
                        break;

                    case VTSS_PHY_TS_ENCAP_ETH_MPLS_ACH_PTP:
                        printf("INVALID Encapsulation Type: 0x%x\n", pkt_encap);
                        break;
                    /* OAM encap */
                    case VTSS_PHY_TS_ENCAP_ETH_OAM:
                        vtss_1588_sample_flows_eoam(inst, ing_port_no,egr_port_no, eng_id, numflows, flow_id);
                        break;
                    case VTSS_PHY_TS_ENCAP_ETH_ETH_OAM:
                        vtss_1588_sample_flows_eeoam(inst, ing_port_no,egr_port_no, eng_id, numflows, flow_id);
                        break;
                    case VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_OAM:
                        vtss_1588_sample_flows_emeoam(inst, ing_port_no,egr_port_no, eng_id, numflows, flow_id);
                        break;
                    case VTSS_PHY_TS_ENCAP_ETH_MPLS_ACH_OAM: /* MPLS-TP OAM */
                        printf("INVALID Encapsulation Type: 0x%x\n", pkt_encap);
                        break;
                    default:
                        printf("INVALID Encapsulation Type: 0x%x\n", pkt_encap);
                        break;
                }

/* *************     Setup:          *********************** */
/* *************       BOUNDARY CLOCK  BC1Step or BC2Step or  ** */
/* *************       TRANSPARENT CLOCK  TC1Step or TC2Step *** */
/* *************       OAM                                   *** */
/* ************************************************************* */

                if(pkt_encap < VTSS_PHY_TS_ENCAP_ETH_OAM) {
                    vtss_1588_sample_actions(inst, ing_port_no,egr_port_no, eng_id, ptp_action_id);
                } else {
                    vtss_oam_sample_actions(inst, ing_port_no,egr_port_no, eng_id);
                }

           } while (0);

    return VTSS_RC_OK;

}

#endif

#ifdef EVAL_BOARD_MACSEC_CAPABLE

/*
 * Test scenario:
 *
 * This is the simplest possible test scenario where a MACsec port is
 * communicating with a single MACsec peer.
 *
 * This test case covers the configuration of the MACsec port, while we pretend
 * that a MACsec peer is connected to the MACsec port.
 *
 *    +-----------+     +-----------+
 *    |MACsec-Peer|<--->|MACsec-port|
 *    +-----------+     +-----------+
 *
 * - One CA is created comprising the MACsec port, and the MACsec peer
 * - 802.1X frames are associated with the uncontrolled port
 * - All other traffic is treated as MACsec traffic
 * - Traffic which is not recognized as MACsec traffic or 802.1X traffic is
 *   dropped.
 * */

#ifndef KAT_TEST_ENABLE_1G // This function is defined in KAT_TEST also
vtss_rc sak_update_hash_key(vtss_macsec_sak_t * sak)
{
    // This function is forcing the usage of only 2 Keys.  It is either 128bit or 256bit, but these keys are static.
    // AES_KEY aes_key;
    // char null_data[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    // key  = 'ad7a2bd03eac835a6f620fdcb506b345'; % 128-bit key
    // hkey = '73a23d80121de2d5a850253fcf43120e';
    // key  = 'e3c08a8f06c6e3ad95a70557b23f75483ce33021a9c72b7025666204c69c0b72'; % 256-bit key
    // hkey = '286d73994ea0ba3cfd1f52bf06a8acf2';
    //rev const unsigned char aes_key_128[] = {0x45,0xb3,0x06,0xb5,0xdc,0x0f,0x62,0x6f,0x5a,0x83,0xac,0x3e,0xd0,0x2b,0x7a,0xad}; // 128-bit key
    //rev const unsigned char hash_key_128[] = {0x0e,0x12,0x43,0xcf,0x3f,0x25,0x50,0xa8,0xd5,0xe2,0x1d,0x12,0x80,0x3d,0xa2,0x73}; // Hash is 128-bits
    //const unsigned char aes_key_128[] = {0xad,0x7a,0x2b,0xd0,0x3e,0xac,0x83,0x5a,0x6f,0x62,0x0f,0xdc,0xb5,0x06,0xb3,0x45}; // 128-bit key
    //const unsigned char hash_key_128[] = {0x73,0xa2,0x3d,0x80,0x12,0x1d,0xe2,0xd5,0xa8,0x50,0x25,0x3f,0xcf,0x43,0x12,0x0e}; // Hash is 128-bits

    const unsigned char aes_key_128[] = {0xad,0x7a,0x2b,0xd0,0x3e,0xac,0x83,0x5a,0x6f,0x62,0x0f,0xdc,0xb5,0x06,0xb3,0x45}; // 128-bit key
    const unsigned char hash_key_128[] = {0x73,0xa2,0x3d,0x80,0x12,0x1d,0xe2,0xd5,0xa8,0x50,0x25,0x3f,0xcf,0x43,0x12,0x0e}; // Hash is 128-bits
    const unsigned char aes_key_256[] = {0xe3,0xc0,0x8a,0x8f,0x06,0xc6,0xe3,0xad,0x95,0xa7,0x05,0x57,0xb2,0x3f,0x75,0x48,
                                         0x3c,0xe3,0x30,0x21,0xa9,0xc7,0x2b,0x70,0x25,0x66,0x62,0x04,0xc6,0x9c,0x0b,0x72}; // 256-bit key
    const unsigned char hash_key_256[] = {0x28,0x6d,0x73,0x99,0x4e,0xa0,0xba,0x3c,0xfd,0x1f,0x52,0xbf,0x06,0xa8,0xac,0xf2}; // Hash is 128bits

    /* 128 Bit Encryption */
    if (sak->len == 16) {
        //AES_set_encrypt_key(sak->buf, 128, &aes_key);
        memcpy( sak->buf,  aes_key_128,  sak->len);  /* 128 Bit Key */
        memcpy( sak->h_buf,  hash_key_128,  sak->len);

    /* 256 Bit Encryption */
    } else if (sak->len == 32) {
        //AES_set_encrypt_key(sak->buf, 256, &aes_key);
        memcpy( sak->buf,  aes_key_256,  sak->len);  /* 128 Bit Key */
        memcpy( sak->h_buf,  hash_key_256,  16);

    } else {
        return VTSS_RC_ERROR;

    }

    // The null_data and encryption key are used to generate the h_buf, but that is already given above
    //AES_ecb_encrypt((const unsigned char *)null_data, (unsigned char *)sak->h_buf, &aes_key, AES_ENCRYPT);

    return VTSS_RC_OK;
}
#endif


/*  *************************************************************************************************** */
/*                          Initialize the PHYSCIAL Port of the PHY to process MACSEC Traffic           */
/*  *************************************************************************************************** */
// Warning uses abort as error handling strategy
void vtss_basic_secy(vtss_inst_t          inst,
                     vtss_port_no_t       macsec_physical_port,
                     vtss_macsec_port_t  *in_macsec_port,
                     vtss_mac_t          *in_port_macaddress,
                     vtss_explicit_sci_t *explicit_sci_rx,
                     BOOL                 encrypt_256
)
{
    //const vtss_macsec_vport_id_t   macsec_virtual_port  = 24193;
    const vtss_macsec_vport_id_t   macsec_virtual_port  = 1;           //jbh
    const vtss_macsec_service_id_t macsec_service_id    = 0;
    const vtss_macsec_port_t       macsec_port = {
        .port_no    = macsec_physical_port,
        .service_id = macsec_service_id,
        .port_id    = macsec_virtual_port
    };

    const vtss_mac_t port_macaddress = { .addr = {0, 0, 0, 0, 0, 0xAA}};   /* Local Port MAC Addr */
    const vtss_mac_t peer_macaddress = { .addr = {0, 0, 0, 0, 0, 0xBB}};   /* Peer MAC Addr       */

    // Initialize the MACsec block
    {
        vtss_macsec_init_t init_data = { .enable = TRUE,
                                         .dis_ing_nm_macsec_en = TRUE,
                                         .mac_conf.lmac.dis_length_validate = FALSE,
                                         .mac_conf.hmac.dis_length_validate = FALSE,
                                         .bypass = MACSEC_INIT_BYPASS_NONE }; /* MACSEC_INIT_BYPASS_ENABLE or MACSEC_INIT_BYPASS_DISABLE */

        printf(" Inst: %p, macsec_physical_port: %d, enable: %x\n", inst, macsec_physical_port, init_data.enable);

        VTSS_RC_TEST(vtss_macsec_init_set(inst, macsec_physical_port, &init_data));

        // Use the default rules to drop all non-matched traffic
        // Setup default rules to by-pass traffic classified as control frames
        vtss_macsec_default_action_policy_t default_action_policy = {
            .ingress_non_control_and_non_macsec = VTSS_MACSEC_DEFAULT_ACTION_BYPASS,
            .ingress_control_and_non_macsec     = VTSS_MACSEC_DEFAULT_ACTION_BYPASS,
            .ingress_non_control_and_macsec     = VTSS_MACSEC_DEFAULT_ACTION_BYPASS,
            .ingress_control_and_macsec         = VTSS_MACSEC_DEFAULT_ACTION_BYPASS,
            .egress_control                     = VTSS_MACSEC_DEFAULT_ACTION_BYPASS,
            .egress_non_control                 = VTSS_MACSEC_DEFAULT_ACTION_BYPASS
        };

        VTSS_RC_TEST(vtss_macsec_default_action_set(inst, macsec_physical_port,
                                                    &default_action_policy));

        printf(" Default Action Set to VTSS_MACSEC_DEFAULT_ACTION_BYPASS\n");
    }


/*  *************************************************************************************************** */
/*                               CREATE a NEW MACSEC SEC_Y                                              */
/*  *************************************************************************************************** */
    {
        vtss_macsec_secy_conf_t macsec_port_conf;
        // Start by adding a SecY
        macsec_port_conf.validate_frames        = VTSS_MACSEC_VALIDATE_FRAMES_STRICT;
        macsec_port_conf.replay_protect         = FALSE;
        macsec_port_conf.replay_window          = 10;
        macsec_port_conf.protect_frames         = TRUE;

        if (explicit_sci_rx->explicit_sci_flag) {
            macsec_port_conf.always_include_sci     = TRUE;       // Must be TRUE for Explicit SCI, adds bytes for Specific SCI

            printf(" MACSEC Sec_Y Explicit SCI = TRUE; always_include_sci = TRUE; 16 Byte SECTAG\n");
        } else {
         // _8BYTE_SECTAG_
            macsec_port_conf.always_include_sci     = FALSE;    // FALSE = Implicit SCI only, no room in pkt provided for Specifying SCI
            printf(" MACSEC Sec_Y Explicit SCI = FALSE; always_include_sci = FALSE; 8 Byte SECTAG\n");

         // _16BYTE_SECTAG_
         //   macsec_port_conf.always_include_sci     = TRUE;       // FALSE = Implicit SCI, adds bytes but SCI not specified
         //   printf(" MACSEC Sec_Y Explicit SCI = FALSE; always_include_sci = TRUE; 16 Byte SECTAG\n");
        }

	if (macsec_port_conf.always_include_sci) {
            printf(" 16 BYTE SECTAG: MACSEC Sec_Y Explicit SCI: %x; always_include_sci to: %x \n", explicit_sci_rx->explicit_sci_flag, macsec_port_conf.always_include_sci);
        } else {
            printf(" 8 BYTE SECTAG: MACSEC Sec_Y Explicit SCI: %x; always_include_sci to: %x \n", explicit_sci_rx->explicit_sci_flag, macsec_port_conf.always_include_sci);
        } 

        macsec_port_conf.use_es                 = FALSE;
        macsec_port_conf.use_scb                = FALSE;
        macsec_port_conf.confidentiality_offset = 0;
        macsec_port_conf.mac_addr               = peer_macaddress;

        if (encrypt_256) {
            macsec_port_conf.current_cipher_suite   = VTSS_MACSEC_CIPHER_SUITE_GCM_AES_256;
        } else {
            macsec_port_conf.current_cipher_suite   = VTSS_MACSEC_CIPHER_SUITE_GCM_AES_128;
        }

        VTSS_RC_TEST(vtss_macsec_secy_conf_add(inst, macsec_port, &macsec_port_conf));
        printf(" New MACSEC Sec_Y Created \n");

/*  *************************************************************************************************** */
/*                               CONTROLLED PORT SETUP - EGRESS                                         */
/*  *************************************************************************************************** */
        // No encapsulation is used. Just match everything, but keep the
        // priority lower than the rule matching traffic for the uncontrolled
        // port. In other words, if it is not control traffic, then it should
        // be considered MACsec traffic.
        vtss_macsec_match_pattern_t pattern_ctrl_egr = {
            .priority            = VTSS_MACSEC_MATCH_PRIORITY_LOW,     // 12
            .match               = VTSS_MACSEC_MATCH_ETYPE,            // 0x0004
            .is_control          = FALSE,
            .has_vlan_tag        = FALSE,
            .has_vlan_inner_tag  = FALSE,
            .etype               = ETHERTYPE_IEEE_IPV4,   // 0x0800
            .vid                 = 0,
            .vid_inner           = 0,
            .hdr                 = "",
            .hdr_mask            = 0,
            .src_mac             = port_macaddress,
            .dest_mac            = peer_macaddress 
        };


        VTSS_RC_TEST(vtss_macsec_pattern_set(inst, macsec_port, VTSS_MACSEC_DIRECTION_EGRESS,
                                                   VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT, &pattern_ctrl_egr));

        printf(" EGRESS CTRL Pattern Set Complete - Pattern Match Set to: VTSS_MACSEC_MATCH_ETYPE = 0800 \n");



/*  *************************************************************************************************** */
/*                               CONTROLLED PORT SETUP - INGRESS                                        */
/*  *************************************************************************************************** */
        // No encapsulation is used. Just match everything, but keep the
        // priority lower than the rule matching traffic for the uncontrolled
        // port. In other words, if it is not control traffic, then it should
        // be considered MACsec traffic.
        vtss_macsec_match_pattern_t pattern_ctrl_ingr = {
            .priority            = VTSS_MACSEC_MATCH_PRIORITY_LOW,        // 12
            .match               = VTSS_MACSEC_MATCH_ETYPE,               // 0x0004
            .is_control          = FALSE,
            .has_vlan_tag        = FALSE,
            .has_vlan_inner_tag  = FALSE,
            .etype               = ETHERTYPE_IEEE_802_1_AE,   // 0x88e5
            .vid                 = 0,     // Old 64
            .vid_inner           = 0,
            .hdr                 = "",
            .hdr_mask            = 0,
            .src_mac             = port_macaddress,
            .dest_mac            = peer_macaddress
        };


        // Associate the pattern with the controlled MACsec port
        VTSS_RC_TEST(vtss_macsec_pattern_set(inst, macsec_port, VTSS_MACSEC_DIRECTION_INGRESS,
                                                   VTSS_MACSEC_MATCH_ACTION_CONTROLLED_PORT, &pattern_ctrl_ingr));

        printf(" INGRESS CTRL Pattern Set Complete - Pattern Match Set to: VTSS_MACSEC_MATCH_ETYPE = 88e5 \n");


/*  *************************************************************************************************** */
/*                               UNCONTROLLED PORT SETUP - INGRESS                                      */
/*  *************************************************************************************************** */
        // All traffic which is not vlan traffic, and have ether-type 0x888E
        // must be associated with the controlled port.
        vtss_macsec_match_pattern_t pattern_unctrl_ingr = {
            .priority            = VTSS_MACSEC_MATCH_PRIORITY_HIGHEST,  // 0
            .match               = VTSS_MACSEC_MATCH_ETYPE,         // 0x0004
            .is_control          = TRUE,
            .has_vlan_tag        = FALSE,
            .has_vlan_inner_tag  = FALSE,
            .etype               = ETHERTYPE_IEEE_802_1_X,    // 0x888e
            .vid                 = 0,
            .vid_inner           = 0,
            .hdr                 = "",
            .hdr_mask            = 0,
            .src_mac             = port_macaddress,
            .dest_mac            = peer_macaddress
        };

        // Associate the pattern with the uncontrolled MACsec port
        VTSS_RC_TEST(vtss_macsec_pattern_set(inst, macsec_port,
                                             VTSS_MACSEC_DIRECTION_INGRESS,
                                             VTSS_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT,
                                             &pattern_unctrl_ingr));

        printf(" INGRESS UNCONTROLLED Pattern Set Complete - Pattern Match Set to: VTSS_MACSEC_MATCH_ETYPE = 888e \n");

/*  *************************************************************************************************** */
/*                               UNCONTROLLED PORT SETUP - EGRESS                                       */
/*  *************************************************************************************************** */
        vtss_macsec_match_pattern_t pattern_unctrl_egr = {
            .priority            = VTSS_MACSEC_MATCH_PRIORITY_HIGHEST,  // 0
            .match               = VTSS_MACSEC_MATCH_ETYPE,             // 0x0004
            .is_control          = TRUE,
            .has_vlan_tag        = FALSE,
            .has_vlan_inner_tag  = FALSE,
            .etype               = ETHERTYPE_IEEE_802_1_X,    // 0x888e
            .vid                 = 0,
            .vid_inner           = 0,
            .hdr                 = "",
            .hdr_mask            = 0,
            .src_mac             = port_macaddress,
            .dest_mac            = peer_macaddress
        };

        VTSS_RC_TEST(vtss_macsec_pattern_set(inst, macsec_port,
                                             VTSS_MACSEC_DIRECTION_EGRESS,
                                             VTSS_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT,
                                             &pattern_unctrl_egr));

        printf(" EGRESS UNCONTROLLED Pattern Set Complete - Pattern Match Set to: VTSS_MACSEC_MATCH_ETYPE = 888e \n");

        // Enable the SecY
        VTSS_RC_TEST(vtss_macsec_secy_controlled_set(inst, macsec_port, TRUE));
        printf(" Enable Sec_Y \n");
    }

    memcpy(in_macsec_port,     &macsec_port,     sizeof macsec_port);
    memcpy(in_port_macaddress, &port_macaddress, sizeof port_macaddress);
}

// Warning uses abort as error handling strategy
void vtss_single_secy_sample_system_create(vtss_inst_t          inst,
                                           vtss_port_no_t       port_no,
                                           vtss_macsec_port_t  *macsec_port,
                                           vtss_mac_t          *port_macaddress,
                                           vtss_macsec_sci_t   *peer_sci,
                                           vtss_explicit_sci_t *explicit_sci_rx,
                                           BOOL                 encrypt_256,
                                           BOOL                 confidentiality
)
{
    const vtss_mac_t peer_macaddress = { .addr = {0, 0, 0, 0, 0, 0xBB}};
    const vtss_port_no_t macsec_physical_port = port_no;
    vtss_macsec_sci_t sci_rx;

    u16   assoc_no = 0;      // Assn Number  0 - 3
    u32   next_pn = 0x000001;    // Next Pkt Num
    u32   lowest_pn = 0x200000;    // Lowest Pkt Num = 2million

    vtss_basic_secy(inst, macsec_physical_port, macsec_port, port_macaddress, explicit_sci_rx, encrypt_256);

    const vtss_macsec_sci_t implicit_sci_rx = { .mac_addr = peer_macaddress,
                                                .port_id  = macsec_port->port_id};

    if (explicit_sci_rx->explicit_sci_flag) {
        // Explicit SCI - Secure Channel Identifier - Not MAC Addr+Port_id
        // Explicit SCI - '12.15.35.24.c0.89-5e.81'

        // sci_rx = explicit_sci_rx->explicit_sci;

        sci_rx = implicit_sci_rx;

        printf ("Explicit SCI_Rx MAC Addr: %02x:%02x:%02x:%02x:%02x:%02x::0x%04x\n",
                   sci_rx.mac_addr.addr[0], sci_rx.mac_addr.addr[1], sci_rx.mac_addr.addr[2],
                   sci_rx.mac_addr.addr[3], sci_rx.mac_addr.addr[4], sci_rx.mac_addr.addr[5],
                   sci_rx.port_id );
    } else {
        // Implicit SCI - Secure Channel Identifier - Mac Addr+Port_id
        sci_rx = implicit_sci_rx;

        printf ("Implicit SCI_Rx MAC Addr: %02x:%02x:%02x:%02x:%02x:%02x::0x%04x\n",
                   sci_rx.mac_addr.addr[0], sci_rx.mac_addr.addr[1], sci_rx.mac_addr.addr[2],
                   sci_rx.mac_addr.addr[3], sci_rx.mac_addr.addr[4], sci_rx.mac_addr.addr[5],
                   sci_rx.port_id );

    }

    printf ("MACsec Phys Port: %d,  Service_id: 0x%x , MACsec Virtual Port (port_id): %d\n",
                   macsec_port->port_no, macsec_port->service_id, macsec_port->port_id );

    printf ("MACsec Port: %d,  Port Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", macsec_physical_port,
                   port_macaddress->addr[0], port_macaddress->addr[1], port_macaddress->addr[2],
                   port_macaddress->addr[3], port_macaddress->addr[4], port_macaddress->addr[5] );

    printf ("Peer MACsec Port_id: %d,  Peer Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", macsec_port->port_id,
                   peer_macaddress.addr[0], peer_macaddress.addr[1], peer_macaddress.addr[2],
                   peer_macaddress.addr[3], peer_macaddress.addr[4], peer_macaddress.addr[5] );

    printf("EGRESS SETUP: Installing Key on HW on Egress Side \n");
    { // Add secure TX channels and a secure association
        vtss_macsec_sak_t sak_tx_sa_0;

        // Add a new TX secure channel
        VTSS_RC_TEST(vtss_macsec_tx_sc_set(inst, *macsec_port));

        if (encrypt_256) {
            // create a zero-key for 256bit cipher suite
            sak_tx_sa_0.len = 32;
        } else {
            // create a zero-key for 128bit cipher suite
            sak_tx_sa_0.len = 16;
        }

        // Update the hash key in the SAK before the key is installed in HW
        VTSS_RC_TEST(sak_update_hash_key(&sak_tx_sa_0));

        if ((sak_tx_sa_0.len == 16) || (sak_tx_sa_0.len == 32)) {
            printf ("SAK: Buff[0-15]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_tx_sa_0.buf[0], sak_tx_sa_0.buf[1], sak_tx_sa_0.buf[2], sak_tx_sa_0.buf[3],
                   sak_tx_sa_0.buf[4], sak_tx_sa_0.buf[5], sak_tx_sa_0.buf[6], sak_tx_sa_0.buf[7],
                   sak_tx_sa_0.buf[8], sak_tx_sa_0.buf[9], sak_tx_sa_0.buf[10], sak_tx_sa_0.buf[11],
                   sak_tx_sa_0.buf[12], sak_tx_sa_0.buf[13], sak_tx_sa_0.buf[14], sak_tx_sa_0.buf[15]);
        }
        if (sak_tx_sa_0.len == 32) {
            printf ("SAK: Buff[16-31]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_tx_sa_0.buf[16], sak_tx_sa_0.buf[17], sak_tx_sa_0.buf[18], sak_tx_sa_0.buf[19],
                   sak_tx_sa_0.buf[20], sak_tx_sa_0.buf[21], sak_tx_sa_0.buf[22], sak_tx_sa_0.buf[23],
                   sak_tx_sa_0.buf[24], sak_tx_sa_0.buf[25], sak_tx_sa_0.buf[26], sak_tx_sa_0.buf[27],
                   sak_tx_sa_0.buf[28], sak_tx_sa_0.buf[29], sak_tx_sa_0.buf[30], sak_tx_sa_0.buf[31]);
        }

        printf ("SAK: Hash_Buff[0-15]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_tx_sa_0.h_buf[0], sak_tx_sa_0.h_buf[1], sak_tx_sa_0.h_buf[2], sak_tx_sa_0.h_buf[3],
                   sak_tx_sa_0.h_buf[4], sak_tx_sa_0.h_buf[5], sak_tx_sa_0.h_buf[6], sak_tx_sa_0.h_buf[7],
                   sak_tx_sa_0.h_buf[8], sak_tx_sa_0.h_buf[9], sak_tx_sa_0.h_buf[10], sak_tx_sa_0.h_buf[11],
                   sak_tx_sa_0.h_buf[12], sak_tx_sa_0.h_buf[13], sak_tx_sa_0.h_buf[14], sak_tx_sa_0.h_buf[15]);
        // install the key in HW on the egress side

        // install the key in HW on the egress side
        VTSS_RC_TEST(vtss_macsec_tx_sa_set(inst, *macsec_port,
                                           assoc_no,        // associations number
                                           next_pn,         // next_pn,
                                           confidentiality, // confidentiality,
                                           &sak_tx_sa_0));

        // install the key in HW on the egress side
        printf("Activiating Key on HW Egress: Port_No: %d, Vir_Port_No: %d, Assoc_No: %d, Next_PN: 0x%x, Service_Id: 0x%x, confid: 0x%x \n",
                   macsec_port->port_no, macsec_port->port_id, assoc_no, next_pn, macsec_port->service_id, confidentiality );

        VTSS_RC_TEST(vtss_macsec_tx_sa_activate(inst, *macsec_port, assoc_no));
    }

    printf("INGRESS SETUP: Installing Key on HW on Ingress Side \n");
    { // Add a MACsec peer
        vtss_macsec_sak_t sak_rx_sa_0;
        vtss_macsec_sak_t sak_rx_sa_1;

      // Add a new RX secure channel
      //  printf("Adding MACsec Peer\n");
        VTSS_RC_TEST(vtss_macsec_rx_sc_add(inst, *macsec_port, &sci_rx));

        // Add two RX SA's
        if (encrypt_256) {
            sak_rx_sa_0.len = 32;
            sak_rx_sa_1.len = 32;
        } else {
            sak_rx_sa_0.len = 16;
            sak_rx_sa_1.len = 16;
        }


        // Update the hash key in the SAK before the key is installed in HW
        printf("Adding Two Hashes - Secure Association 0 and 1 \n");
        VTSS_RC_TEST(sak_update_hash_key(&sak_rx_sa_0));
        VTSS_RC_TEST(sak_update_hash_key(&sak_rx_sa_1));

        printf("Setup Key_0: Activating Key on HW on Ingress Side - Assoc: 0\n");
        //printf("SA Set \n");

        if ((sak_rx_sa_0.len == 16) || (sak_rx_sa_0.len == 32)) {
            printf ("SAK_SA0: Buff[0-15]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_rx_sa_0.buf[0], sak_rx_sa_0.buf[1], sak_rx_sa_0.buf[2], sak_rx_sa_0.buf[3],
                   sak_rx_sa_0.buf[4], sak_rx_sa_0.buf[5], sak_rx_sa_0.buf[6], sak_rx_sa_0.buf[7],
                   sak_rx_sa_0.buf[8], sak_rx_sa_0.buf[9], sak_rx_sa_0.buf[10], sak_rx_sa_0.buf[11],
                   sak_rx_sa_0.buf[12], sak_rx_sa_0.buf[13], sak_rx_sa_0.buf[14], sak_rx_sa_0.buf[15]);
        }
        if (sak_rx_sa_0.len == 32) {
            printf ("SAK_SA0: Buff[16-31]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_rx_sa_0.buf[16], sak_rx_sa_0.buf[17], sak_rx_sa_0.buf[18], sak_rx_sa_0.buf[19],
                   sak_rx_sa_0.buf[20], sak_rx_sa_0.buf[21], sak_rx_sa_0.buf[22], sak_rx_sa_0.buf[23],
                   sak_rx_sa_0.buf[24], sak_rx_sa_0.buf[25], sak_rx_sa_0.buf[26], sak_rx_sa_0.buf[27],
                   sak_rx_sa_0.buf[28], sak_rx_sa_0.buf[29], sak_rx_sa_0.buf[30], sak_rx_sa_0.buf[31]);
        }

        printf ("SAK_SA0: Hash_Buff[0-15]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_rx_sa_0.h_buf[0], sak_rx_sa_0.h_buf[1], sak_rx_sa_0.h_buf[2], sak_rx_sa_0.h_buf[3],
                   sak_rx_sa_0.h_buf[4], sak_rx_sa_0.h_buf[5], sak_rx_sa_0.h_buf[6], sak_rx_sa_0.h_buf[7],
                   sak_rx_sa_0.h_buf[8], sak_rx_sa_0.h_buf[9], sak_rx_sa_0.h_buf[10], sak_rx_sa_0.h_buf[11],
                   sak_rx_sa_0.h_buf[12], sak_rx_sa_0.h_buf[13], sak_rx_sa_0.h_buf[14], sak_rx_sa_0.h_buf[15]);

        //printf ("SCI_Rx MAC Addr: %02x:%02x:%02x:%02x:%02x:%02x::0x%04x\n",
        //           sci_rx.mac_addr.addr[0], sci_rx.mac_addr.addr[1], sci_rx.mac_addr.addr[2],
        //           sci_rx.mac_addr.addr[3], sci_rx.mac_addr.addr[4], sci_rx.mac_addr.addr[5],
        //           sci_rx.port_id );

        assoc_no = 0;      // Assn Number
        lowest_pn = 0;     // Lowest Pkt Num
        printf("Setting up RX sa_0 Assoc_No: %d, lowest_pn: %d \n", assoc_no, lowest_pn);
        VTSS_RC_TEST(vtss_macsec_rx_sa_set(inst, *macsec_port,
                                           &sci_rx, // identify which SC the SA belongs to
                                           assoc_no,       // associations number
                                           lowest_pn,       // lowest_pn,
                                           &sak_rx_sa_0));
        VTSS_RC_TEST(vtss_macsec_rx_sa_activate(inst, *macsec_port, &sci_rx, assoc_no));

        // install the key in HW on the egress side
        printf("Activiating Key_0 on HW Inress: Port_No: %d, Vir_Port_No: %d, Assoc_No: %d, Lowest_PN: 0x%x, SCI: 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x - 0x%x \n",
                   macsec_port->port_no, macsec_port->port_id, assoc_no, lowest_pn, sci_rx.mac_addr.addr[0], sci_rx.mac_addr.addr[1],
                   sci_rx.mac_addr.addr[2], sci_rx.mac_addr.addr[3], sci_rx.mac_addr.addr[4], sci_rx.mac_addr.addr[5], sci_rx.port_id );

        printf("Setup Key_1: Activating Key on HW on Ingress Side - Assoc: 1\n");

        printf("Setup Key_1: Activating Key on HW on Ingress Side - Assoc: 1\n");

        if ((sak_rx_sa_0.len == 16) || (sak_rx_sa_0.len == 32)) {
            printf ("SAK_SA1: Buff[0-15]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_rx_sa_1.buf[0], sak_rx_sa_1.buf[1], sak_rx_sa_1.buf[2], sak_rx_sa_1.buf[3],
                   sak_rx_sa_1.buf[4], sak_rx_sa_1.buf[5], sak_rx_sa_1.buf[6], sak_rx_sa_1.buf[7],
                   sak_rx_sa_1.buf[8], sak_rx_sa_1.buf[9], sak_rx_sa_1.buf[10], sak_rx_sa_1.buf[11],
                   sak_rx_sa_1.buf[12], sak_rx_sa_1.buf[13], sak_rx_sa_1.buf[14], sak_rx_sa_1.buf[15]);
        }
        if (sak_rx_sa_0.len == 32) {
            printf ("SAK_SA1: Buff[16-31]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_rx_sa_1.buf[16], sak_rx_sa_1.buf[17], sak_rx_sa_1.buf[18], sak_rx_sa_1.buf[19],
                   sak_rx_sa_1.buf[20], sak_rx_sa_1.buf[21], sak_rx_sa_1.buf[22], sak_rx_sa_1.buf[23],
                   sak_rx_sa_1.buf[24], sak_rx_sa_1.buf[25], sak_rx_sa_1.buf[26], sak_rx_sa_1.buf[27],
                   sak_rx_sa_1.buf[28], sak_rx_sa_1.buf[29], sak_rx_sa_1.buf[30], sak_rx_sa_1.buf[31]);
        }

        printf ("SAK_SA1: Hash_Buff[0-15]: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                   sak_rx_sa_1.h_buf[0], sak_rx_sa_1.h_buf[1], sak_rx_sa_1.h_buf[2], sak_rx_sa_1.h_buf[3],
                   sak_rx_sa_1.h_buf[4], sak_rx_sa_1.h_buf[5], sak_rx_sa_1.h_buf[6], sak_rx_sa_1.h_buf[7],
                   sak_rx_sa_1.h_buf[8], sak_rx_sa_1.h_buf[9], sak_rx_sa_1.h_buf[10], sak_rx_sa_1.h_buf[11],
                   sak_rx_sa_1.h_buf[12], sak_rx_sa_1.h_buf[13], sak_rx_sa_1.h_buf[14], sak_rx_sa_1.h_buf[15]);

        assoc_no = 1;         // Assn Number
       lowest_pn = 0x2000000;     // Lowest Pkt Num
        //printf("sa_1 Assoc_No: %d, lowest_pn: %d \n", assoc_no, lowest_pn);
        VTSS_RC_TEST(vtss_macsec_rx_sa_set(inst, *macsec_port,
                                           &sci_rx,      // identify which SC the SA belongs to
                                           assoc_no,     // associations number
                                           lowest_pn,    // lowest_pn,
                                           &sak_rx_sa_1));


        VTSS_RC_TEST(vtss_macsec_rx_sa_activate(inst, *macsec_port, &sci_rx, assoc_no));

        printf("Activiating Key_1 on HW Inress: Port_No: %d, Vir_Port_No: %d, Assoc_No: %d, Lowest_PN: 0x%x, SCI: 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x - 0x%x \n",
                   macsec_port->port_no, macsec_port->port_id, assoc_no, lowest_pn, sci_rx.mac_addr.addr[0], sci_rx.mac_addr.addr[1],
                   sci_rx.mac_addr.addr[2], sci_rx.mac_addr.addr[3], sci_rx.mac_addr.addr[4], sci_rx.mac_addr.addr[5], sci_rx.port_id );
    }

    memcpy(peer_sci, &sci_rx, sizeof sci_rx);
}

void vtss_basic_secy_destroy(
    vtss_inst_t               inst,
    const vtss_macsec_port_t *macsec_port
)
{
    // Delete SecY
    printf(" calling vtss_macsec_secy_conf_del \n");
    VTSS_RC_TEST(vtss_macsec_secy_conf_del(inst, *macsec_port));

    // Disable the MACsec block
    printf(" calling vtss_macsec_init_set,  Enable=False \n");
    vtss_macsec_init_t deinit_data = { .enable = FALSE };
    VTSS_RC_TEST(vtss_macsec_init_set(inst, macsec_port->port_no,
                                      &deinit_data));
}


void vtss_single_secy_sample_system_destroy(
    vtss_inst_t               inst,
    const vtss_macsec_port_t *macsec_port,
    const vtss_mac_t         *port_macaddress,
    const vtss_macsec_sci_t  *peer_sci
)
{

    // Disable the sa
    //printf ("calling vtss_macsec_rx_sa_disable:  1\n");
    //VTSS_RC_TEST(vtss_macsec_rx_sa_disable(inst,*macsec_port, peer_sci, 1));
    //printf ("calling vtss_macsec_rx_sa_disable:  0\n");
    //VTSS_RC_TEST(vtss_macsec_rx_sa_disable(inst,*macsec_port, peer_sci, 0));

    // Delete peer
    //printf ("calling vtss_macsec_rx_sa_del:  1\n");
    //VTSS_RC_TEST(vtss_macsec_rx_sa_del(inst, *macsec_port, peer_sci, 1));
    printf ("calling vtss_macsec_rx_sa_del:  0\n");
    VTSS_RC_TEST(vtss_macsec_rx_sa_del(inst, *macsec_port, peer_sci, 0));
    printf ("calling vtss_macsec_rx_sc_del\n");
    VTSS_RC_TEST(vtss_macsec_rx_sc_del(inst, *macsec_port, peer_sci));

    // Delete TX SA and SC
    //printf ("calling vtss_macsec_tx_sa_disable:  0\n");
    //VTSS_RC_TEST(vtss_macsec_tx_sa_disable(inst,*macsec_port, 0));
    printf ("calling vtss_macsec_tx_sa_del:  0\n");
    VTSS_RC_TEST(vtss_macsec_tx_sa_del(inst, *macsec_port, 0));
    printf ("calling vtss_macsec_tx_sc_del \n");
    VTSS_RC_TEST(vtss_macsec_tx_sc_del(inst, *macsec_port));

    printf ("calling vtss_basic_secy_destroy  \n");
    vtss_basic_secy_destroy(inst, macsec_port);

}


#endif

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

#if defined (VTSS_API_INIT_SEQ_NORMAL)
static vtss_phy_reset_conf_t vts_phy_init_params = {VTSS_PORT_INTERFACE_SGMII, VTSS_PHY_MEDIA_IF_FI_1000BX, {1,2},
     {FALSE},VTSS_PHY_PKT_MODE_IEEE_1_5_KB, FALSE};
#endif

#ifdef VTSS_OPT_PHY_TIMESTAMP
/* Update the internal timestamp table, from HW */
static void demo_ts_phy_fifo_read(  const vtss_inst_t              inst,
                                    const vtss_port_no_t           port_no,
                                    const vtss_phy_timestamp_t     *const fifo_ts,
                                    const vtss_phy_ts_fifo_sig_t   *const sig,
                                    void                           *cntxt,
                                    const vtss_phy_ts_fifo_status_t status)
{
    vtss_phy_ts_fifo_sig_t sig_loc;
    /* Send Message from side board to the connected Jaguar Board */
    memset(&sig_loc, 0, sizeof(sig_loc));
    memcpy(&sig_loc, sig, sizeof(vtss_phy_ts_fifo_sig_t));
    printf("port_no %u, tx signature: mask %x, type %d, domain %d, seq %d\n", port_no,
         sig->sig_mask, sig->msg_type, sig->domain_num, sig->sequence_id);
    printf("tx time:  Sec_Hi:%d, Sec_Low:%u,  Nsec: %u, Nsec (hex) ns %x\n",
         fifo_ts->seconds.high, fifo_ts->seconds.low, fifo_ts->nanoseconds, fifo_ts->nanoseconds);
}
#endif

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
#ifdef VTSS_FEATURE_MACSEC // 1588 and MACSec get #ifdef'd because they are completely seperate Modules, not in vtss_phy.c
    vtss_macsec_port_t macsec_port[4];
    vtss_mac_t         port_macaddress[4];
    vtss_macsec_sci_t  peer_sci[4];
#endif
#ifdef EVAL_BOARD_1588_CAPABLE
    vtss_phy_ts_eng_init_conf_t     ts_init_conf;
#endif
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

#ifdef VTSS_FEATURE_MACSEC // 1588 and MACSec get #ifdef'd because they are completely seperate Modules, not in vtss_phy.c
    memset (&macsec_port[0], 0, sizeof(vtss_macsec_port_t) * 4);
    memset (&port_macaddress[0], 0, sizeof(vtss_mac_t) * 4);
    memset (&peer_sci[0], 0, sizeof(vtss_macsec_sci_t) * 4);
#endif

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

    // Example for RGMII MAC interfaces; Skew Delays
    tx_clk_skew_ps = rgmii_skew_delay_200_psec;
    rx_clk_skew_ps = rgmii_skew_delay_200_psec;

    // Example for MAC interfaces; Note: Last entry is one selected
    mac_if = VTSS_PORT_INTERFACE_SERDES;
    mac_if = VTSS_PORT_INTERFACE_RGMII;
    mac_if = VTSS_PORT_INTERFACE_QSGMII;
    mac_if = VTSS_PORT_INTERFACE_SGMII;


    // Example for Media interfaces; Note: Last entry is one selected
    media_if = VTSS_PHY_MEDIA_IF_AMS_FI_100FX;
    media_if = VTSS_PHY_MEDIA_IF_AMS_CU_100FX;
    media_if = VTSS_PHY_MEDIA_IF_AMS_FI_1000BX;
    media_if = VTSS_PHY_MEDIA_IF_AMS_CU_1000BX;
    media_if = VTSS_PHY_MEDIA_IF_AMS_FI_PASSTHRU;
    media_if = VTSS_PHY_MEDIA_IF_AMS_CU_PASSTHRU;
    media_if = VTSS_PHY_MEDIA_IF_FI_100FX;
    media_if = VTSS_PHY_MEDIA_IF_FI_1000BX;
    media_if = VTSS_PHY_MEDIA_IF_SFP_PASSTHRU;
    media_if = VTSS_PHY_MEDIA_IF_CU;

    // Example for PHY moode; Note: Last entry is one selected
    phy.mode = VTSS_PHY_MODE_FORCED;
    phy.mode = VTSS_PHY_MODE_ANEG;

    // Example for PHY speed support for auto-neg
    phy.aneg.speed_10m_hdx = 1;
    phy.aneg.speed_10m_fdx = 1;
    phy.aneg.speed_100m_hdx = 1;
    phy.aneg.speed_100m_fdx = 1;
    phy.aneg.speed_1g_hdx = 0;
    phy.aneg.speed_1g_fdx = 1;

    // Example for PHY flow control settings
    phy.aneg.symmetric_pause =  0;
    phy.aneg.tx_remote_fault =  0;

    // Example for PHY speed (non-auto neg.) Note: Last Entry is one selected
    phy.forced.speed = VTSS_SPEED_10M;
    phy.forced.speed = VTSS_SPEED_100M;
    phy.forced.speed = VTSS_SPEED_1G;
    phy.forced.fdx = 1;

    phy.mdi = VTSS_PHY_MDIX_AUTO; // always enable auto detection of crossed/non-crossed cables
    phy.force_ams_sel = VTSS_PHY_MEDIA_FORCE_AMS_SEL_SERDES; // FORCE PHY AMS Media Selection to always be SERDES
    phy.force_ams_sel = VTSS_PHY_MEDIA_FORCE_AMS_SEL_COPPER; // FORCE PHY AMS Media Selection to always be COPPER
    phy.force_ams_sel = VTSS_PHY_MEDIA_FORCE_AMS_SEL_NORMAL; // Let PHY Determine Media Selection based on Link Status

    phy.skip_coma = TRUE;  // Skip COMA Mode config in vtss_phy_post_reset
    phy.skip_coma = FALSE; // COMA Mode config = Default, Apply Default COMA Mode in vtss_phy_post_reset

    phy.flf = VTSS_PHY_FAST_LINK_FAIL_DISABLE;
    phy.flf = VTSS_PHY_FAST_LINK_FAIL_ENABLE;

    phy.sigdet = VTSS_PHY_SIGDET_POLARITY_ACT_LOW;
    phy.sigdet = VTSS_PHY_SIGDET_POLARITY_ACT_HIGH;

    phy.unidir = VTSS_PHY_UNIDIRECTIONAL_ENABLE;
    phy.unidir = VTSS_PHY_UNIDIRECTIONAL_DISABLE;

/*  Setup the MAC Interface PCS Parameters */
    phy.mac_if_pcs.disable = 0;
    phy.mac_if_pcs.restart = 0;
    phy.mac_if_pcs.pd_enable = 1;
    phy.mac_if_pcs.aneg_restart = 0;
    phy.mac_if_pcs.force_adv_ability = 0;
    phy.mac_if_pcs.sgmii_in_pre = VTSS_PHY_MAC_SERD_PCS_SGMII_IN_PRE_ONE;
    phy.mac_if_pcs.sgmii_in_pre = VTSS_PHY_MAC_SERD_PCS_SGMII_IN_PRE_TWO;
    phy.mac_if_pcs.sgmii_in_pre = VTSS_PHY_MAC_SERD_PCS_SGMII_IN_PRE_NONE;
    phy.mac_if_pcs.sgmii_out_pre = 0;
    phy.mac_if_pcs.serdes_aneg_ena = 0;
    phy.mac_if_pcs.serdes_pol_inv_in = 0;
    phy.mac_if_pcs.serdes_pol_inv_out = 0;
    phy.mac_if_pcs.fast_link_stat_ena = 0;
    phy.mac_if_pcs.inhibit_odd_start = 1;

/*  Setup the MEDIA Interface PCS Parameters */
    phy.media_if_pcs.remote_fault = VTSS_PHY_MEDIA_SERD_PCS_REM_FAULT_OFFLINE;
    phy.media_if_pcs.remote_fault = VTSS_PHY_MEDIA_SERD_PCS_REM_FAULT_LINK_FAIL;
    phy.media_if_pcs.remote_fault = VTSS_PHY_MEDIA_SERD_PCS_REM_FAULT_ANEG_ERROR;
    phy.media_if_pcs.remote_fault = VTSS_PHY_MEDIA_SERD_PCS_REM_FAULT_NO_ERROR;
    phy.media_if_pcs.aneg_pd_detect = 0;
    phy.media_if_pcs.force_adv_ability = 0;
    phy.media_if_pcs.serdes_pol_inv_in = 0;
    phy.media_if_pcs.serdes_pol_inv_out = 0;
    phy.media_if_pcs.inhibit_odd_start = 1;
    phy.media_if_pcs.force_hls = 0;
    phy.media_if_pcs.force_fefi = 0;
    phy.media_if_pcs.force_fefi_value = 0;

    printf ("Default COMA Mode Operation? - (Y=Default/N=Skip_COMA_Mode in Post_Reset)  \n");
    memset (&value_str[0], 0, sizeof(value_str));
    scanf("%s", &value_str[0]);
    if (value_str [0] == 'y' || value_str [0] == 'Y' ) {
        phy.skip_coma = FALSE; // COMA Mode config = Default, Apply Default COMA Mode in vtss_phy_post_reset
    } else {
        phy.skip_coma = TRUE;  // Skip COMA Mode config in vtss_phy_post_reset
    }

    if (skip_to_main_menu == FALSE) {
        printf ("Run Default Pre-Reset/Reset/Post-Reset Order for ALL Ports Ok ? (Y/N)  \n");
        memset (&value_str[0], 0, sizeof(value_str));
        scanf("%s", &value_str[0]);

        if (value_str[0] == 'n' || value_str[0] == 'N' ) {
            printf ("Run Pre-Reset for ALL Ports Ok ? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            if (value_str[0] == 'n' || value_str[0] == 'N' ) {
                run_pre_reset = FALSE;
            }

            printf ("Run Reset for ALL Ports Ok ? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            if (value_str[0] == 'n' || value_str[0] == 'N' ) {
                run_reset = FALSE;
            }

            printf ("Run Post-Reset for ALL Ports Ok ? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            if (value_str[0] == 'n' || value_str[0] == 'N' ) {
                run_post_reset = FALSE;
            }

            printf ("Run PHY DEMO Config for ALL Ports After PHY_Reset Ok ? (Y=Demo/N=Default)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            if (value_str[0] == 'n' || value_str[0] == 'N' ) {
                run_phy_config = FALSE;
            }
        }

        // Reset stuff needed before PHY port reset, any port will do (Only at start-up initialization)

        if (run_pre_reset) {
#ifdef _INCLUDE_DEBUG_FILE_PRINT_
            fprintf (fp,"PHY PRE-RESET\n");
#endif
            printf ("//Comment: Step 2: Running PHY vtss_phy_pre_reset on base port of PHY\n");
            rc = vtss_phy_pre_reset(board->inst, phy_base_port);
            if (rc != VTSS_RC_OK) {
                printf ("//>>>>>> ERROR DETECTED <<<<<<<< During PHY pre-reset, rc = %d\n", rc);
            }
        }

/* ****************************************************** */
/* FINAL CONFIGURATION Over-rides for EVAL BOARD          */
/* ****************************************************** */
        mac_if = VTSS_PORT_INTERFACE_SGMII;
        media_if = VTSS_PHY_MEDIA_IF_CU;

        phy_reset.mac_if = mac_if;      // Set the port MAC interface
        phy_reset.media_if = media_if;  // Set media interface
        phy_reset.rgmii.rx_clk_skew_ps = rx_clk_skew_ps;
        phy_reset.rgmii.tx_clk_skew_ps = tx_clk_skew_ps;
        phy_reset.tbi.aneg_enable = FALSE;  // Set to Enable tbi
        phy_reset.force = VTSS_PHY_NOFORCE_RESET;   // Set to VTSS_PHY_NOFORCE_RESET or to Force PHY Reset VTSS_PHY_FORCE_RESET for Viper and Tesla
        phy_reset.pkt_mode = VTSS_PHY_PKT_MODE_IEEE_1_5_KB; //  (default)VTSS_PHY_PKT_MODE_IEEE_1_5_KB, VTSS_PHY_PKT_MODE_JUMBO_9_KB, VTSS_PHY_PKT_MODE_JUMBO_12_KB
        phy_reset.i_cpu_en = 0;         // Set to TRUE to enable internal 8051 CPU for Enzo and Spyder Family Only

        //phy.mode = VTSS_PHY_MODE_FORCED;
        phy.mode = VTSS_PHY_MODE_ANEG;  // Mode ANEG means forced mode settings irrelevant
        phy.forced.speed = VTSS_SPEED_100M;
        phy.forced.fdx = 1;
        phy.mdi = VTSS_PHY_MDIX_AUTO;
        phy.flf = VTSS_PHY_FAST_LINK_FAIL_ENABLE;
        phy.sigdet = VTSS_PHY_SIGDET_POLARITY_ACT_HIGH;
        phy.unidir = VTSS_PHY_UNIDIRECTIONAL_DISABLE;

#ifdef  ATOM12_EVAL_BOARD
        printf ("//Comment: Setup of VSC8522 - ATOM12 Eval Board \n");
        mac_if = VTSS_PORT_INTERFACE_QSGMII;
        media_if = VTSS_PHY_MEDIA_IF_CU;
#endif
#ifdef  TESLA_EVAL_BOARD
        printf ("//Comment: Setup of VSC8574 - Tesla Eval Board \n");
        mac_if = VTSS_PORT_INTERFACE_SGMII;
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

#if defined (TESLA_EVAL_BOARD) || defined (VIPER_EVAL_BOARD) || defined (ELISE_EVAL_BOARD)
        printf ("\nALL PHY MAC(16E3)/MEDIA(23E3) i/f Control defaults: MAC=PD/inhibit_odd_start Enabled, MEDIA=inhibit_odd_start Enabled \n");
        printf ("NOTE: Eval Board must be HW Reset or Pwr Cycled to Clear the MAC/MEDIA PCS Control Settings \n");
        printf ("ALL PHY MAC SerDes PCS i/f Control (16E3) defaults: MAC=PD/inhibit_odd_start Enabled \n");
        printf ("Are Default MAC i/f Default Control Selections for ALL Ports Ok ? ie. PD(16E3.13)/inhibit_odd_start Delay (16E3.2) Enabled  (Y/N) \n");
        memset (&value_str[0], 0, sizeof(value_str));
        scanf("%s", &value_str[0]);

        if (value_str[0] == 'n' || value_str[0] == 'N' ) {
         /*  Setup the MAC Interface PCS Parameters */
            phy.mac_if_pcs.disable = 0;
            printf ("MAC SerDes PCS Control: Interface Disable? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == 'y' || value_str[0] == 'Y') {
                phy.mac_if_pcs.disable = 1;
            }

            phy.mac_if_pcs.restart = 0;
            printf ("MAC SerDes PCS Control: 1000BaseX MAC Interface Restart? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == 'y' || value_str[0] == 'Y') {
                phy.mac_if_pcs.restart = 1;
            }

            phy.mac_if_pcs.pd_enable = 0;
            printf ("MAC SerDes PCS Control: PD Enable? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == 'y' || value_str[0] == 'Y') {
                phy.mac_if_pcs.pd_enable = 1;
            }

            phy.mac_if_pcs.aneg_restart = 0;
            printf ("MAC SerDes PCS Control: ANEG Restart? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == 'y' || value_str[0] == 'Y') {
                phy.mac_if_pcs.aneg_restart = 1;
            }

            phy.mac_if_pcs.force_adv_ability = 0;
            printf ("MAC SerDes PCS Control: Force ADV Ability from 18E3? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == 'y' || value_str[0] == 'Y') {
                phy.mac_if_pcs.force_adv_ability = 1;
            }

            phy.mac_if_pcs.sgmii_in_pre = VTSS_PHY_MAC_SERD_PCS_SGMII_IN_PRE_NONE;
            printf ("MAC SerDes PCS Control: SGMII Input Preamble for 100FX - 0-None; 1-1Byte; 2-2Byte? (0/1/2)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == '0') {
                phy.mac_if_pcs.sgmii_in_pre = VTSS_PHY_MAC_SERD_PCS_SGMII_IN_PRE_NONE;
            } else if (value_str[0] == '1') {
                phy.mac_if_pcs.sgmii_in_pre = VTSS_PHY_MAC_SERD_PCS_SGMII_IN_PRE_ONE;
            } else if (value_str[0] == '2') {
                phy.mac_if_pcs.sgmii_in_pre = VTSS_PHY_MAC_SERD_PCS_SGMII_IN_PRE_TWO;
            } else {
                phy.mac_if_pcs.sgmii_in_pre = VTSS_PHY_MAC_SERD_PCS_SGMII_IN_PRE_NONE;
            }

            phy.mac_if_pcs.sgmii_out_pre = 0;
            printf ("MAC SerDes PCS Control: SGMII Output Preamble? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == 'y' || value_str[0] == 'Y') {
                phy.mac_if_pcs.sgmii_out_pre = 1;
            }

            phy.mac_if_pcs.serdes_aneg_ena = 0;
            printf ("MAC SerDes PCS Control: SerDes ANEG Enable? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == 'y' || value_str[0] == 'Y') {
                phy.mac_if_pcs.serdes_aneg_ena = 1;
            }

            phy.mac_if_pcs.serdes_pol_inv_in = 0;
            printf ("MAC SerDes PCS Control: SerDes Invert Input Polarity? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == 'y' || value_str[0] == 'Y') {
                phy.mac_if_pcs.serdes_pol_inv_in = 1;
            }

            phy.mac_if_pcs.serdes_pol_inv_out = 0;
            printf ("MAC SerDes PCS Control: SerDes Invert Output Polarity? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == 'y' || value_str[0] == 'Y') {
                phy.mac_if_pcs.serdes_pol_inv_out = 1;
            }

            phy.mac_if_pcs.fast_link_stat_ena = 0;
            printf ("MAC SerDes PCS Control: Fast Link Fail Status Enable ? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == 'y' || value_str[0] == 'Y') {
                phy.mac_if_pcs.fast_link_stat_ena = 1;
            }

            phy.mac_if_pcs.inhibit_odd_start = 0;
            printf ("MAC SerDes PCS Control: Inhibit MAC Odd-Start delay ? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == 'y' || value_str[0] == 'Y') {
                phy.mac_if_pcs.inhibit_odd_start = 1;
            }
        }
#endif

#if defined (TESLA_EVAL_BOARD) || defined (VIPER_EVAL_BOARD)
        printf ("ALL PHY MEDIA SerDes i/f Control (23E3) defaults: MAC=PD/inhibit_odd_start Enabled, MEDIA=inhibit_odd_start Enabled \n");
        printf ("Are Default MEDIA i/f Default Control Selections for ALL Ports Ok ?, ie. MEDIA=inhibit_odd_start Delay(23E3.4) Enabled  (Y/N) \n");
        memset (&value_str[0], 0, sizeof(value_str));
        scanf("%s", &value_str[0]);

        if (value_str[0] == 'n' || value_str[0] == 'N' ) {

            phy.media_if_pcs.aneg_pd_detect = 0;
            printf ("MEDIA SerDes PCS Control(23E3): SerDes MEDIA ANEG parallel detect enable ? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == 'y' || value_str[0] == 'Y') {
                phy.media_if_pcs.aneg_pd_detect = 1;
            }

            phy.media_if_pcs.force_adv_ability = 0;
            printf ("MEDIA SerDes PCS Control(23E3): Force 16-bit Advertised ability from Reg 25E3.15:0 ? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == 'y' || value_str[0] == 'Y') {
                phy.media_if_pcs.force_adv_ability = 1;
            }

            phy.media_if_pcs.serdes_pol_inv_in = 0;
            printf ("MEDIA SerDes PCS Control(23E3): Invert SerDes Polarity at input of Media SerDes ? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == 'y' || value_str[0] == 'Y') {
                phy.media_if_pcs.serdes_pol_inv_in = 1;
            }

            phy.media_if_pcs.serdes_pol_inv_out = 0;
            printf ("MEDIA SerDes PCS Control(23E3): Invert SerDes Polarity at output of Media SerDes ? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == 'y' || value_str[0] == 'Y') {
                phy.media_if_pcs.serdes_pol_inv_out = 1;
            }

            phy.media_if_pcs.inhibit_odd_start = 0;
            printf ("MEDIA SerDes PCS Control(23E3): Inhibit Media Odd-Start delay ? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == 'y' || value_str[0] == 'Y') {
                phy.media_if_pcs.inhibit_odd_start = 1;
            }

            phy.media_if_pcs.force_hls = 0;
            printf ("MEDIA SerDes PCS Control(23E3): Forces 100BaseFX to Tx Halt Line State (HLS)continuously ? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == 'y' || value_str[0] == 'Y') {
                phy.media_if_pcs.force_hls = 1;
            }

            phy.media_if_pcs.force_fefi = 0;
            printf ("MEDIA SerDes PCS Control(23E3): Force 100BaseFX Far-End-Fault Indication ? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == 'y' || value_str[0] == 'Y') {
                phy.media_if_pcs.force_fefi = 1;
            }

            phy.media_if_pcs.force_fefi_value = 0;
            printf ("MEDIA SerDes PCS Control(23E3): Forces/Suppress FEFI 1=Force; 0=Suppress ? (0/1)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == '1') {
                phy.media_if_pcs.force_fefi_value = 1;
            }
        }
#endif

        printf ("//Default ANEG ADVERTISEMENTS: 1G_FDX: %x; 1G_HDX: %x; 100M_FDX: 0x%x; 100M_HDX: %x; 10M_FDX: %x; 10M_HDX: 0x%x \n",
                   phy.aneg.speed_1g_fdx, phy.aneg.speed_1g_hdx, phy.aneg.speed_100m_fdx,
                   phy.aneg.speed_100m_hdx, phy.aneg.speed_10m_fdx, phy.aneg.speed_10m_hdx);
        printf ("//  ASym_Pause: %x;  Sym_Pause: %x;   Tx_Remote_Fault: %x \n",
                   phy.aneg.asymmetric_pause, phy.aneg.symmetric_pause, phy.aneg.tx_remote_fault);

        printf ("//Default FORCED Mode: FDX: 0x%x; HDX: 0x%x  \n", (phy.forced.fdx == 0x1), (phy.forced.fdx == 0x0));
        printf ("//Default FORCED Speed: 1G: 0x%x; 100M: 0x%x; 10M: 0x%x  \n", (phy.forced.speed == VTSS_SPEED_1G),
                    (phy.forced.speed == VTSS_SPEED_1G), (phy.forced.speed == VTSS_SPEED_1G));

        set_hdx = FALSE;
        set_fdx = FALSE;
        printf ("Full-Duplex Operation?: ALL Ports (Y/N):   \n");
        memset (&value_str[0], 0, sizeof(value_str));
        scanf("%s", &value_str[0]);
        if (value_str[0] == 'y' || value_str[0] == 'Y') {
            set_fdx = TRUE;
        }

        printf ("Half-Duplex Operation?: ALL Ports (Y/N):   \n");
        memset (&value_str[0], 0, sizeof(value_str));
        scanf("%s", &value_str[0]);
        if (value_str[0] == 'y' || value_str[0] == 'Y') {
            set_hdx = TRUE;
        }

        printf ("ALL PHY Port Modes defaulted to (0=ANEG; 1=FORCED; 2=PWRDOWN): %x \n", phy.mode);
        printf ("Are Default Modes (Speed, Duplex, Force Mode, ANEG, ANEG Advertisements) for ALL Ports Ok ? (Y/N)    \n");
        memset (&value_str[0], 0, sizeof(value_str));
        scanf("%s", &value_str[0]);
        if (value_str[0] == 'n' || value_str[0] == 'N' ) {

            printf ("Set Mode for ALL Ports (0=ANEG, 1=Forced, 2=PowerDn Port), Enter Mode:   \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            value_str[0] = '0';
            if (value_str[0] == '0') {
                phy.mode = VTSS_PHY_MODE_ANEG;

                phy.flf = VTSS_PHY_FAST_LINK_FAIL_ENABLE;
                printf ("Fast-Link Fail: Fast-Link Fail is Enabled by Default, Disable Now? (Y/N):   \n");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == 'y' || value_str[0] == 'Y') {
                    phy.flf = VTSS_PHY_FAST_LINK_FAIL_DISABLE;
                }

                phy.aneg.tx_remote_fault = 0;
		printf ("ANEG ADVERTISEMENTS: Set Tx_Remote_Fault for ALL Ports (Y/N):   \n");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == 'y' || value_str[0] == 'Y') {
                    phy.aneg.tx_remote_fault = 1;
                }
                phy.aneg.asymmetric_pause = 0;
		printf ("ANEG ADVERTISEMENTS: Set Asymmetric_Pause for ALL Ports (Y/N):   \n");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == 'y' || value_str[0] == 'Y') {
                    phy.aneg.asymmetric_pause = 1;
                }
		printf ("ANEG ADVERTISEMENTS: Set Symmetric_Pause for ALL Ports (Y/N):   \n");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == 'y' || value_str[0] == 'Y') {
                    phy.aneg.symmetric_pause = 1;
                }

                phy.aneg.speed_10m_hdx = 0;
                phy.aneg.speed_10m_fdx = 0;
                phy.aneg.speed_100m_hdx = 0;
                phy.aneg.speed_100m_fdx = 0;
                phy.aneg.speed_1g_hdx = 0;
                phy.aneg.speed_1g_fdx = 0;
                printf ("ANEG ADVERTISEMENTS: Set Port Speed for ALL Ports (0=ANEG ALL Speeds OR ANEG Selected Speed: 1=1G, 2=100M, 3=10M, 4=ANEG ALL+fdx&hdx=ON), Enter Speed:   \n");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == '0') {
                    // Example for PHY speed support for auto-neg
                    // This example shows how to ANEG to lower speed selections
                    phy.aneg.speed_10m_hdx = 1;
                    phy.aneg.speed_10m_fdx = 1;
                    phy.aneg.speed_100m_hdx = 1;
                    phy.aneg.speed_100m_fdx = 1;
                    phy.aneg.speed_1g_hdx = 0;
                    phy.aneg.speed_1g_fdx = 0;
                    if (set_hdx) phy.aneg.speed_1g_hdx = 1;
                    if (set_fdx) phy.aneg.speed_1g_fdx = 1;
                } else if (value_str[0] == '1') {
                    // Example for PHY speed support for auto-neg
                    // This example shows how to ANEG to fixed speed selections
                    if (set_hdx) phy.aneg.speed_1g_hdx = 1;
                    if (set_fdx) phy.aneg.speed_1g_fdx = 1;
                } else if (value_str[0] == '2') {
                    // Example for PHY speed support for auto-neg
                    // This example shows how to ANEG to fixed speed selections
                    if (set_hdx) phy.aneg.speed_100m_hdx = 1;
                    if (set_fdx) phy.aneg.speed_100m_fdx = 1;
                } else if (value_str[0] == '3') {
                    // Example for PHY speed support for auto-neg
                    // This example shows how to ANEG to fixed speed selections
                    if (set_hdx) phy.aneg.speed_10m_hdx = 1;
                    if (set_fdx) phy.aneg.speed_10m_fdx = 1;
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
                printf ("//  ASym_Pause: %x;  Sym_Pause: %x;   Tx_Remote_Fault: %x \n",
                   phy.aneg.asymmetric_pause, phy.aneg.symmetric_pause, phy.aneg.tx_remote_fault);

            } else if (value_str[0] == '1') {
                phy.mode = VTSS_PHY_MODE_FORCED;
                printf ("Note: SmartBits Generator Defaults Forced mode to 1000 for Fibre \n");
                printf ("Set Port Speed for ALL Ports (0=1G, 1=100M, 2=10M, Enter Speed:   \n");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == '0') {
                    phy.forced.speed = VTSS_SPEED_1G;
                } else if (value_str[0] == '1') {
                    phy.forced.speed = VTSS_SPEED_100M;
                } else if (value_str[0] == '2') {
                    phy.forced.speed = VTSS_SPEED_10M;
                } else {
                    phy.forced.speed = VTSS_SPEED_1G;
                }

                if (set_hdx) phy.forced.fdx = 0;
                if (set_fdx) phy.forced.fdx = 1;
                phy.unidir = VTSS_PHY_UNIDIRECTIONAL_DISABLE;
                printf ("Set Port as UNIDIRECTIONAL for ALL Ports (N=No, Y=Yes):   \n");
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
        }

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


        // Do PHY port reset + Port setup
        printf ("//Comment: PHY port reset\n");
        for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS; port_no++) {
            phy_reset.mac_if = mac_if;             // Set the port MAC interface
            phy_reset.media_if = media_if;         // Set media interface
            phy_reset.rgmii.rx_clk_skew_ps = rx_clk_skew_ps;
            phy_reset.rgmii.tx_clk_skew_ps = tx_clk_skew_ps;
            if (run_reset) {
                printf ("//Comment: Step 3: Perform PHY port reset on PHY port: %d\n", port_no);
#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"PHY RESET\n");
#endif
                vtss_phy_reset(board->inst, port_no, &phy_reset); // Do port reset
            }

            if (run_phy_config) {  /* Over-write to use PHY Defaults ONLY */
                printf ("//Comment: Step 4: Perform PHY port config on PHY port: %d\n", port_no);
                vtss_phy_conf_set(board->inst, port_no, &phy);

#if defined (VIPER_EVAL_BOARD) || defined (TESLA_EVAL_BOARD) || defined (ELISE_EVAL_BOARD) || defined (ATOM12_EVAL_BOARD)
                // SmartBits defaults to Forced mode for Fibre - Make life easier for setups
                // For Fibre 1000BX(SFP) and 100FX(SFP), Cu(SFP) the Speed is Forced mode and the SigDet has to be cleared, ie Reg 19E1.0=0
                if (media_if != VTSS_PHY_MEDIA_IF_CU) {
                    phy.sigdet = VTSS_PHY_SIGDET_POLARITY_ACT_HIGH;
                    printf ("SFP Config DETECTED - Setting SigDet - Addr: 19E1 = 0x%x\n", value);
                }
#endif
                printf ("//Comment: Step 5: Perform PHY port 1G_config on PHY port: %d\n", port_no);
                vtss_phy_conf_1g_set(board->inst, port_no, &phy_1g);
                printf ("// PHY port %d, Reset Complete; Config Complete, Port config: Manual_Master: 0x%x, 1=Master/0=Slave: 0x%x \n", port_no, phy_1g.master.cfg, phy_1g.master.val);

            } else {
                printf ("//Comment: Running PHY DEFAULT Config after port reset for Port: %d\n", port_no);
                vtss_phy_conf_get(board->inst, port_no, &phy);
                // Example for PHY speed support for auto-neg
                phy.aneg.speed_10m_hdx = 1;
                phy.aneg.speed_10m_fdx = 1;
                phy.aneg.speed_100m_hdx = 1;
                phy.aneg.speed_100m_fdx = 1;
                phy.aneg.speed_1g_hdx = 0;
                phy.aneg.speed_1g_fdx = 1;

                printf ("//Comment: Step 4: Perform PHY port config on PHY port: %d\n", port_no);
                vtss_phy_conf_set(board->inst, port_no, &phy);
                vtss_phy_conf_1g_get(board->inst, port_no, &phy_1g);
#if 0
                phy_1g.master.cfg = 0;    /* Master/Slave config, 1=enabled, 0=disable */
                phy_1g.master.val = 0;    /* Master/Slave config, 1=Master, 0=Slave */
#endif
                printf ("//Comment: Step 5: Perform PHY port 1G_config on PHY port: %d\n", port_no);
                vtss_phy_conf_1g_set(board->inst, port_no, &phy_1g);
            }
            printf ("// PHY port %d, Reset Complete; Config Complete, Port config: Manual_Master: 0x%x, 1=Master/0=Slave: 0x%x \n", port_no, phy_1g.master.cfg, phy_1g.master.val);

            prev_mode[port_no] = phy.mode;
        }

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
        if (run_post_reset) {
            printf ("//Comment: Last_Step: Running PHY vtss_phy_post_reset on base port of PHY\n");
#ifdef _INCLUDE_DEBUG_FILE_PRINT_
            fprintf (fp,"PHY POST-RESET\n");
#endif
            rc = vtss_phy_post_reset(board->inst, phy_base_port);
            if (rc != VTSS_RC_OK) {
                printf ("//ERROR DETECTED during PHY post-reset, rc = %d\n", rc);
            }
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

#ifdef KAT_TEST_ENABLE_1G
            } else if (strcmp(command, "kat_test") == 0) {
                vtss_rc  rc;
                vtss_macsec_frame_capture_t  capture = VTSS_MACSEC_FRAME_CAPTURE_DISABLE;
                BOOL egr_fail = FALSE;
                BOOL ing_fail = FALSE;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                rc = vtss_phy_macsec_kat_test(board->inst, port_no, &egr_fail, &ing_fail);
                printf("Rtn Code for KAT Test: %d  Egress Results: %x,  Ingress_Results: %x\n", rc, egr_fail, ing_fail);
                if (egr_fail) {
                    printf("EGRESS_KAT_Results: 0x%x :: FAIL!!\n", egr_fail);
                } else {
                    printf("EGRESS_KAT_Results: 0x%x :: PASS! \n", egr_fail);
                }
                if (ing_fail) {
                    printf("INGRESS_KAT_Results: 0x%x :: FAIL!!\n", ing_fail);
                } else {
                    printf("INGRESS_KAT_Results: 0x%x :: PASS! \n", ing_fail);
                }
                continue;
#endif
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
#ifdef  EVAL_BOARD_1588_CAPABLE    // 1588 and MACSec get #ifdef'd because they are completely seperate Modules, not in vtss_phy.c
        } else if (strcmp(command, "1588") == 0) {
            vtss_phy_ts_engine_t  eng_id = 0;

          while(1) {
#ifdef _INCLUDE_DEBUG_FILE_PRINT_
            fflush(fp);
#endif
            printf (" \n\n");
            printf (" ptp_clock  <port_no> - Setup Ingress/Egress Ports for 1588v2 Boundary Clk PTP Encap\n");
            printf (" 1588_epg   <port_no> - Setup EPG to generate certain Frame \n");
            printf (" 1588_ena   <port_no> - Enable 1588 on this port - and No other actions \n");
            printf (" 1588_dis   <port_no> - Disable 1588 on this port - and No other actions \n");
            printf (" ing_eng_clr<port_no> - Clear/Release 1588 Analyzer Ingress Engine already Initialized \n");
            printf (" egr_eng_clr<port_no> - Clear/Release 1588 Analyzer Egress Engine already Initialized \n");
            printf (" int_enable <port_no> - Setup Ingress/Egress/LTC INT Enable/Disable for Port for 1588v2\n");
            printf (" event_poll <port_no> - Polling Ingress/Egress/LTC INT for Port for 1588v2\n");
            printf (" ptp_get    <port_no> - Get the PHY PTP timestamp in Secs/NanoSecs, Clear the Save Enable \n");
            printf (" ptp_arm_set <port_no> - Set the PHY timestamp in seconds and nanoseconds \n");
            printf (" arm_set_done <port_no> - Set the PHY timestamp \n");
            printf (" ptp_load   <port_no> - Get the PHY PTP load time in seconds and nanoseconds \n");
            printf (" sig_get    <port_no> - Get TS Signature Bytes  \n");
            printf (" sig_set    <port_no> - Set TS Signature Bytes  \n");
            printf (" cb_install <port_no> - Install Call-back to read FIFO \n");
            printf (" read_fifo  <port_no> - Reads the FIFO until empty and then Executes the FIFO Read Call-back \n");
            printf (" ts_reg_dump  <port_no> - Dump 1588 Registers\n");
            printf (" x - exit             - Exit to upper level menu\n");
            printf ("> ");
            rc = scanf("%s", &command[0]);

            enable_1588 = 1;

            if ((strcmp(command, "x") == 0) || (strcmp(command, "X") == 0)) {
                break;
            } else if (strcmp(command, "1588_ena") == 0) {
               if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                enable_1588 = 1;
                rc = vtss_phy_ts_mode_set (board->inst, port_no, enable_1588);
                if (rc != VTSS_RC_OK) {
                    printf("PHY TS Block Enable Failed for port: %d\n", port_no);
                }
                continue;

            } else if (strcmp(command, "1588_dis") == 0) {
               if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                enable_1588 = 0;
                rc = vtss_phy_ts_mode_set (board->inst, port_no, enable_1588);
                if (rc != VTSS_RC_OK) {
                    printf("PHY TS Block Disable Failed for port: %d\n", port_no);
                }
                continue;

            } else if (strcmp(command, "ing_eng_clr") == 0) {
               if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }
                eng_id = (port_no % 2) ? VTSS_PHY_TS_PTP_ENGINE_ID_1:VTSS_PHY_TS_PTP_ENGINE_ID_0;  // Eval Board Ports 0-3

                rc = vtss_phy_ts_ingress_engine_clear (board->inst, port_no, eng_id);
                if (rc != VTSS_RC_OK) {
                    printf("PHY TS Ingress Engine Clear Failed for port: %d\n", port_no);
                }
                continue;

            } else if (strcmp(command, "egr_eng_clr") == 0) {
               if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }
                eng_id = (port_no % 2) ? VTSS_PHY_TS_PTP_ENGINE_ID_1:VTSS_PHY_TS_PTP_ENGINE_ID_0;  // Eval Board Ports 0-3

                rc = vtss_phy_ts_egress_engine_clear (board->inst, port_no, eng_id);
                if (rc != VTSS_RC_OK) {
                    printf("PHY TS Ingress Engine Clear Failed for port: %d\n", port_no);
                }
                continue;

            } else if (strcmp(command, "ptp_clock") == 0) {
                vtss_rc  rc;
                vtss_phy_ts_engine_t  eng_id = VTSS_PHY_TS_PTP_ENGINE_ID_0;
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                printf ("Please ensure that the FRAME data has Correct EtherType for Encapsulation!!\n" ) ;
                printf ("Please ensure that Dest MAC ADDR, IP Addr, and UDP Src/Dest are set correctly !\n");
                printf ("ETH1 Dest MAC : 00-00-00-00-00-01  (+ Flow_Id (0-7) to make Flows different) \n");
                printf ("ETH2 Dest MAC : 00-00-00-00-00-21 \n");
                printf ("IP1 Dest IP: 10.10.10.10      IP2 Dest IP: 10.10.10.11 \n");
                printf ("MPLS Label Range(F ~ FFFFF) \n");
                printf ("UDP Dest Port: 319         UDP Src Port: 1 \n\n");
                ing_port_no = port_no;
                printf ("Ingress Port %d \n", port_no);
                printf ("\nPlease Enter Egress Port: ");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                egr_port_no = atoi(value_str);

                printf ("\nPlease Engine to be Configured (PTP 0/1   OAM:2a/2b): ");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == '0') {
                    printf ("PTP Eng_0 Selected \n");
                    eng_id = VTSS_PHY_TS_PTP_ENGINE_ID_0;
                } else if (value_str[0] == '1') {
                    printf ("PTP Eng_1 Selected \n");
                    eng_id = VTSS_PHY_TS_PTP_ENGINE_ID_1;
                } else if (value_str[0] == '2') {
                    printf ("OAM Eng_2 Selected \n");
                    if (value_str[1] == 'a' || value_str[1] == 'A') {
                        printf ("OAM Eng_2A Selected \n");
                        eng_id = VTSS_PHY_TS_OAM_ENGINE_ID_2A;
                    } else if (value_str[1] == 'b' || value_str[1] == 'B') {
                        printf ("OAM Eng_2B Selected \n");
                        eng_id = VTSS_PHY_TS_OAM_ENGINE_ID_2B;
                    } else {
                        printf ("Defaulting to OAM Eng_2A \n");
                        eng_id = VTSS_PHY_TS_OAM_ENGINE_ID_2A;
                    }
                } else {
                    printf ("INVALID OPTION Selected!!  Options are: 0/1/2a/2b");
                    continue;
                }

                rc = vtss_ptp_sample_clock(board->inst, ing_port_no, egr_port_no, eng_id);
                continue;
            
            } else if (strcmp(command, "ts_reg_dump") == 0) {
                vtss_rc  rc;
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

#ifdef VTSS_TS_DEBUG_REG_DUMP
                ing_port_no = port_no;
                printf ("Ingress Port %d \n", port_no);
                printf ("\nPlease Enter Egress Port: ");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                egr_port_no = atoi(value_str);
				
		printf("\n\n Register Dump:\n\n");
		rc = vtss_phy_1588_debug_reg_read(board->inst,ing_port_no, 0);
		rc = vtss_phy_1588_debug_reg_read(board->inst,ing_port_no, 4);
		rc = vtss_phy_1588_debug_reg_read(board->inst,ing_port_no, 5);
		rc = vtss_phy_1588_debug_reg_read(board->inst,ing_port_no, 6);
		rc = vtss_phy_1588_debug_reg_read(board->inst,ing_port_no, 7);
		printf("\n\n Register Dump:\n\n");
		rc = vtss_phy_1588_debug_reg_read(board->inst,egr_port_no, 1);
		rc = vtss_phy_1588_debug_reg_read(board->inst,egr_port_no, 4);
		rc = vtss_phy_1588_debug_reg_read(board->inst,egr_port_no, 5);
		rc = vtss_phy_1588_debug_reg_read(board->inst,egr_port_no, 6);
		rc = vtss_phy_1588_debug_reg_read(board->inst,egr_port_no, 7);
#endif
		continue;

            } else if (strcmp(command, "1588_epg") == 0) {
               if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }
#ifdef TESLA_ING_TS_ERRFIX
#if 0
                u32 ing_delta = 0;
                u32 egr_delta = 0;
                u16 match_mode = 0x10;  // INGRESS = 0x10; EGRESS = 0x11; BOTH = 0x12;
                printf ("\nPlease Enter Match Mode (No_Match=0/Ingress=16/Egress=17/Both=18): ");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                match_mode = atoi(value_str);
                printf ("\nMatch Mode: %d\n", match_mode);
                //match_mode = ingress ? MATCH_INGRESS : MATCH_EGRESS;
                rc = vtss_phy_ts_tesla_epg(board->inst, port_no, printf, 125, match_mode, &ing_delta, &egr_delta);
#endif
#endif
                continue;

           } else if (strcmp(command, "int_enable") == 0) {
                vtss_rc  rc;
                BOOL enable = FALSE;
                vtss_phy_ts_event_t  ev_mask=0;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"\nGet Event Enable Settings\n");
#endif
                rc = vtss_phy_ts_event_enable_get(board->inst, port_no, &ev_mask);

                printf ("VTSS_PHY_TS_INGR_ENGINE_ERR            0x01  /**< More than one engine find match */ \n");
                printf ("VTSS_PHY_TS_INGR_RW_PREAM_ERR          0x02  /**< Preamble too short to append timestamp */ \n");
                printf ("VTSS_PHY_TS_INGR_RW_FCS_ERR            0x04  /**< FCS error in ingress */ \n");
                printf ("VTSS_PHY_TS_EGR_ENGINE_ERR             0x08  /**< More than one engine find match */ \n");
                printf ("VTSS_PHY_TS_EGR_RW_FCS_ERR             0x10  /**< FCS error in egress */ \n");
                printf ("VTSS_PHY_TS_EGR_TIMESTAMP_CAPTURED     0x20  /**< Timestamp captured in Tx TSFIFO */ \n");
                printf ("VTSS_PHY_TS_EGR_FIFO_OVERFLOW          0x40  /**< Tx TSFIFO overflow */ \n");
                printf ("VTSS_PHY_TS_DATA_IN_RSRVD_FIELD        0x80  /**< Data in reserved Field */ \n");
                printf ("VTSS_PHY_TS_LTC_NEW_PPS_INTRPT         0x100 /**< New PPS pushed onto external PPS pin*/ \n");
                printf ("VTSS_PHY_TS_LTC_LOAD_SAVE_NEW_TOD      0x200 /**< New LTC value either loaded in to HW or saved into registers*/ \n");
                printf ("\n");
                printf ("Current 1588 Event Mask: 0x%x\n", ev_mask);
                printf ("\n");
                printf ("Please Enter the Desired Event Mask (Must be in Hex) for Port: %d  (0x0=Exit):", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                ev_mask = strtol(value_str, NULL, 16);

                if (ev_mask == 0) {
                    continue;
                }

                enable = FALSE;
                printf ("Event Mask: 0x%x:  Enter Disable(0)/Enable(1) for port  %d :", ev_mask, port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == '1') {
                    enable = TRUE;
                }

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"\nSet Event Enable Settings\n");
#endif
                rc = vtss_phy_ts_event_enable_set(board->inst, port_no, enable, ev_mask);
                printf ("Event Mask: 0x%x:  Enable: 0x%x;  for port  %d :", ev_mask, enable, port_no);

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"\nGet Event Enable Settings\n");
#endif
                ev_mask = 0;
                rc = vtss_phy_ts_event_enable_get(board->inst, port_no, &ev_mask);
                printf ("Current 1588 Event Mask: 0x%x\n", ev_mask);

                continue;

           } else if (strcmp(command, "event_poll") == 0) {
                vtss_rc  rc;
                vtss_phy_ts_event_t  ev_mask=0;
                int      loopCnt = 20;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"\nGet Event Enable Settings\n");
#endif
                rc = vtss_phy_ts_event_enable_get(board->inst, port_no, &ev_mask);

                printf ("VTSS_PHY_TS_INGR_ENGINE_ERR            0x01  /**< More than one engine find match */ \n");
                printf ("VTSS_PHY_TS_INGR_RW_PREAM_ERR          0x02  /**< Preamble too short to append timestamp */ \n");
                printf ("VTSS_PHY_TS_INGR_RW_FCS_ERR            0x04  /**< FCS error in ingress */ \n");
                printf ("VTSS_PHY_TS_EGR_ENGINE_ERR             0x08  /**< More than one engine find match */ \n");
                printf ("VTSS_PHY_TS_EGR_RW_FCS_ERR             0x10  /**< FCS error in egress */ \n");
                printf ("VTSS_PHY_TS_EGR_TIMESTAMP_CAPTURED     0x20  /**< Timestamp captured in Tx TSFIFO */ \n");
                printf ("VTSS_PHY_TS_EGR_FIFO_OVERFLOW          0x40  /**< Tx TSFIFO overflow */ \n");
                printf ("VTSS_PHY_TS_DATA_IN_RSRVD_FIELD        0x80  /**< Data in reserved Field */ \n");
                printf ("VTSS_PHY_TS_LTC_NEW_PPS_INTRPT         0x100 /**< New PPS pushed onto external PPS pin*/ \n");
                printf ("VTSS_PHY_TS_LTC_LOAD_SAVE_NEW_TOD      0x200 /**< New LTC value either loaded in to HW or saved into registers*/ \n");
                printf ("\n");
                printf ("Current 1588 Event Mask: 0x%x \n", ev_mask);
                printf ("\n");

                while (loopCnt > 0) {
                    miim_write(board->inst, port_no, 31, 0x10);   /* GPIO Pg */
                    miim_read(board->inst, port_no, 29, &value);  /* 29G - Global Status  */
                    miim_write(board->inst, port_no, 31, 0);      /* Std Page */
                    ev_mask = 0;
#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                    fprintf (fp,"\nPoll Event \n");
#endif
                    rc = vtss_phy_ts_event_poll(board->inst, port_no, &ev_mask);
                    printf ("Port: %d; LoopCnt: %d;  rc: 0x%x;  Polling 29G: 0x%x;  1588 INT Events: 0x%x  \n", port_no, loopCnt, rc, value, ev_mask);
                    loopCnt--;
                }
                continue;

           } else if (strcmp(command, "ptp_get") == 0) {
                vtss_rc  rc;
                vtss_phy_timestamp_t    ts;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                memset (&ts, 0, sizeof(vtss_phy_timestamp_t));

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"\nGet PTP Time \n");
#endif
                rc = vtss_phy_ts_ptptime_get(board->inst, port_no, &ts);
                printf ("Port: %d;   PTP Time:Sec_Hi: %d,  Sec_Low: %d;  NanoSecs: %d \n", port_no, ts.seconds.high, ts.seconds.low, ts.nanoseconds);

                continue;

           } else if (strcmp(command, "ptp_arm_set") == 0) {
                vtss_rc  rc;
                vtss_phy_timestamp_t    ts;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                memset (&ts, 0, sizeof(vtss_phy_timestamp_t));

                printf ("Port_No: %d, Enter PTP_TIME Sec_Hi: ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                ts.seconds.high = atoi(value_str);

                printf ("Port_No: %d, Enter PTP_TIME Sec_Low: ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                ts.seconds.low = atol(value_str);

                printf ("Port_No: %d, Enter PTP_TIME NanoSecs: ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                ts.nanoseconds = atol(value_str);

                printf ("Port: %d;   Arming and Setting PTP Time: Sec_Hi: %d,  Sec_Low: %d;  NanoSecs: %d \n", port_no, ts.seconds.high, ts.seconds.low, ts.nanoseconds);
#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"\nArm PTP_Time Trigger for Next LTC Rising Edge \n");
#endif
                rc = vtss_phy_ts_ptptime_arm(board->inst, port_no);

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"\nConfigure PTP_Time for Next LTC Rising Edge \n");
#endif
                rc = vtss_phy_ts_ptptime_set(board->inst, port_no, &ts);

                continue;

           } else if (strcmp(command, "arm_set_done") == 0) {
                vtss_rc  rc;
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                printf ("Port: %d;   Arming, Set, Done! PTP Time\n", port_no);
#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"\nArm PTP_Time Trigger for Next LTC Rising Edge \n");
#endif
                rc = vtss_phy_ts_ptptime_arm(board->inst, port_no);

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"\nPTP_Time_Set_Done  \n");
#endif
                rc = vtss_phy_ts_ptptime_set_done(board->inst, port_no);

                continue;

           } else if (strcmp(command, "ptp_load") == 0) {
                vtss_rc  rc;
                vtss_phy_timestamp_t    ts;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                memset (&ts, 0, sizeof(vtss_phy_timestamp_t));

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"\nPTP_Time_Load_Get  \n");
#endif
                rc = vtss_phy_ts_load_ptptime_get(board->inst, port_no, &ts);
                printf ("Port: %d;   LOAD Time: Sec_Hi: %d,  Sec_Low: %d;  NanoSecs: %d \n", port_no, ts.seconds.high, ts.seconds.low, ts.nanoseconds);

                continue;

           } else if (strcmp(command, "sig_get") == 0) {
                vtss_rc  rc;
                vtss_phy_ts_fifo_sig_mask_t    sig_mask=0;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                rc = vtss_phy_ts_fifo_sig_get(board->inst, port_no, &sig_mask);
                printf ("Src IP address:    VTSS_PHY_TS_FIFO_SIG_SRC_IP          = 0x01 \n");
                printf ("Dest IP address:   VTSS_PHY_TS_FIFO_SIG_DEST_IP         = 0x02 \n");
                printf ("Msg Type:          VTSS_PHY_TS_FIFO_SIG_MSG_TYPE        = 0x04 \n");
                printf ("Domain Number:     VTSS_PHY_TS_FIFO_SIG_DOMAIN_NUM      = 0x08 \n");
                printf ("Src Port ID:       VTSS_PHY_TS_FIFO_SIG_SOURCE_PORT_ID  = 0x10 \n");
                printf ("PTP Frame Seq ID:  VTSS_PHY_TS_FIFO_SIG_SEQ_ID          = 0x20 \n");
                printf ("Dest MAC Addr:     VTSS_PHY_TS_FIFO_SIG_DEST_MAC        = 0x40 \n");
                printf ("Note: Signature Masks are OR'd together, so Multiple can be chosen \n\n");
                printf ("Port: %d;   Current TS Signatgure Mask: 0x%04x \n", port_no, sig_mask);

                continue;

           } else if (strcmp(command, "sig_set") == 0) {
                vtss_rc  rc;
                vtss_phy_ts_fifo_sig_mask_t    sig_mask=0;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }
                rc = vtss_phy_ts_fifo_sig_get(board->inst, port_no, &sig_mask);
                printf ("Src IP address:    VTSS_PHY_TS_FIFO_SIG_SRC_IP          = 0x01 \n");
                printf ("Dest IP address:   VTSS_PHY_TS_FIFO_SIG_DEST_IP         = 0x02 \n");
                printf ("Msg Type:          VTSS_PHY_TS_FIFO_SIG_MSG_TYPE        = 0x04 \n");
                printf ("Domain Number:     VTSS_PHY_TS_FIFO_SIG_DOMAIN_NUM      = 0x08 \n");
                printf ("Src Port ID:       VTSS_PHY_TS_FIFO_SIG_SOURCE_PORT_ID  = 0x10 \n");
                printf ("PTP Frame Seq ID:  VTSS_PHY_TS_FIFO_SIG_SEQ_ID          = 0x20 \n");
                printf ("Dest MAC Addr:     VTSS_PHY_TS_FIFO_SIG_DEST_MAC        = 0x40 \n");
                printf ("Note: Signature Masks are OR'd together, so Multiple can be chosen \n\n");
                printf ("Port: %d;   Current TS Signatgure Mask: 0x%x \n\n", port_no, sig_mask);

                printf ("Port_No: %d, Enter Signature Mask (in Hex): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                sig_mask = strtol(value_str, NULL, 16);

                rc = vtss_phy_ts_fifo_sig_set(board->inst, port_no, sig_mask);
                printf ("Port: %d;   Setting TS Signatgure Mask to: 0x%04x \n", port_no, sig_mask);

                continue;

           } else if (strcmp(command, "cb_install") == 0) {
                vtss_rc                 rc;
                void                   *appl_cntxt = NULL;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                /* Install the callback function to the PHY_TS_API */
                rc = vtss_phy_ts_fifo_read_install(board->inst, demo_ts_phy_fifo_read, appl_cntxt);
                if (rc < 0) {
                    printf("Error in installing fifo-read func \n");
                }

                rc = vtss_phy_ts_event_enable_set(board->inst, port_no, TRUE, 0x3F);
                if (rc < 0) {
                    printf("Error in enabling the event \n\r");
                }

                continue;

           } else if (strcmp(command, "read_fifo") == 0) {
                vtss_rc                 rc;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                /* Install the callback function to the PHY_TS_API */
                rc = vtss_phy_ts_fifo_empty(board->inst, port_no);
                if (rc < 0) {
                    printf("Error in vtss_phy_ts_fifo_empty trying fifo-read func \n");
                }

                continue;

            } else {
                continue;
            }

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
            fflush(fp);
#endif

          } // End of While(1) Loop

          continue;  // Go back to top of Loop

#endif // End of 1588
#ifdef EVAL_BOARD_MACSEC_CAPABLE  // 1588 and MACSec get #ifdef'd because they are completely seperate Modules, not in vtss_phy.c
        } else if (strcmp(command, "macsec") == 0) {
          while(1) { 
            printf (" \n\n");
            printf (" macsec128Exp   <port_no> - Enable MACSEC Operation: 128-bit Encryption, Explicit SCI with Static Key \n");
            printf (" macsec128Imp   <port_no> - Enable MACSEC Operation: 128-bit Encryption, Implicit SCI with Static Key \n");
            printf (" macsec256Exp   <port_no> - Enable MACSEC Operation: 256-bit Encryption, Explicit SCI with Static Key \n");
            printf (" macsec256Imp   <port_no> - Enable MACSEC Operation: 256-bit Encryption, Implicit SCI with Static Key \n");
            printf (" macsec_off     <port_no> - Disable Port for MACsec Operation \n");
            printf (" macsec_ena     <port_no> - Enable MACSEC on Port and Enable/Disable ByPass for MACsec Operation \n");
            printf (" macsec_en_event   <port_no> - Enable ALL events (Thresh & Rollover) on Port for MACsec Operation \n");
            printf (" macsec_dis_event  <port_no> - Disable ALL events (Thresh & Rollover) on Port for MACsec Operation \n");
            printf (" macsec_poll_event <port_no> - Poll for Event (Thresh or Rollover) on Port for MACsec Operation \n");
            printf (" macsec_get_thresh <port_no> - Get Seq Threshold Setting on Port for MACsec Operation \n");
            printf (" macsec_set_thresh <port_no> - Set Seq Threshold Setting on Port for MACsec Operation \n");
            printf (" macsec_frmcap     <port_no> - Enable INGRESS/EGRESS or Disable MACSEC Frame Capture \n");
            printf (" ctrl_cnt    <port_no> - Get the Sec_Y Control Counters  \n");
            printf (" unctrl_cnt  <port_no> - Get the Sec_Y Uncontrolled Counters  \n");
            printf (" cmn_cnt     <port_no> - Get the Sec_Y Common Counters  \n");
            printf (" hmac_count  <port_no> - Get the MACSEC Host MAC Counters  \n");
            printf (" lmac_count  <port_no> - Get the MACSEC Line MAC Counters  \n");
            printf (" dbg_count   <port_no> - Get the MACSEC Debug Counters  \n");
            printf (" dbg_reg_dump<port_no> - Get the MACSEC Debug Reg Dump  \n");
            printf (" fcb_dump    <port_no> - Get the MACSEC FC Buffer Reg Dump  \n");
            printf (" frm_ctl_dump<port_no> - Get the MACSEC Frame Match Handling CTRL Reg Dump  \n");
#ifdef KAT_TEST_ENABLE_1G
            printf (" kat_test <port_no> - Run KAT Test  \n");
#endif
            printf (" x - exit              - Exit to upper level menu\n");
            printf ("> ");
            rc = scanf("%s", &command[0]);

            if ((strcmp(command, "x") == 0) || (strcmp(command, "X") == 0)) {
                break;

            } else if (strcmp(command, "macsec_ena") == 0) {
                vtss_macsec_init_t    init_data;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }
                rc = vtss_macsec_init_get(board->inst, port_no, &init_data);
                printf(" Port_no: %d, Current Settings: MACSEC enable: %x,   MACSEC ByPass (0=None; 1=bypassEN; 2=bypassDIS): 0x%x\n",
                         port_no, init_data.enable, init_data.bypass);

                printf ("\nPort_No: %d, MACSEC Enable/Disable? (0=Disable/1=Enable): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == 1) {
                    init_data.enable = TRUE;
                } else {
                    init_data.enable = FALSE;
                }
                init_data.dis_ing_nm_macsec_en = TRUE;

                printf ("\nPort_No: %d, MACSEC ByPass None/Enable/Disable? (0=None/1=ByPass Enable/2=ByPass Disable): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == '2') {
                    init_data.bypass = MACSEC_INIT_BYPASS_DISABLE;
                } else if (value_str[0] == '1') {
                    init_data.bypass = MACSEC_INIT_BYPASS_ENABLE;
                } else {
                    init_data.bypass = MACSEC_INIT_BYPASS_NONE;
                }

                rc = vtss_macsec_init_set(board->inst, port_no, &init_data);

                continue;

            } else if (strcmp(command, "macsec_frmcap") == 0) {
                vtss_rc  rc;
                vtss_macsec_frame_capture_t  capture;
                u32 frm_len = 0;                                    // Length of the frame captured
                u32 idx = 0;
                u8 frm_buffer[VTSS_MACSEC_FRAME_CAPTURE_SIZE_MAX];  // Buffer for storing the frame 

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                printf ("\nPort_No: %d, Enter DIRECTION (0=Disable / 1=INGRESS / 2=EGRESS) (0/1/2)): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == '2') {
                    printf ("Port_No: %d, EGRESS DIRECTION Selected \n", port_no);
                    capture = VTSS_MACSEC_FRAME_CAPTURE_EGRESS;
                } else if (value_str[0] == '1') {
                    printf ("Port_No: %d, INGRESS DIRECTION Selected \n", port_no);
                    capture = VTSS_MACSEC_FRAME_CAPTURE_INGRESS;
                } else {
                    printf ("Port_No: %d, DISABLE Selected - Also dumping Capture Data \n", port_no);
                    capture = VTSS_MACSEC_FRAME_CAPTURE_DISABLE;
                }

                // Setup capturing of egress frame
                vtss_macsec_frame_capture_set(board->inst, port_no, capture); 

                if (capture == VTSS_MACSEC_FRAME_CAPTURE_DISABLE) {
                    // Get the captured frame
                    vtss_macsec_frame_get(board->inst, port_no, VTSS_MACSEC_FRAME_CAPTURE_SIZE_MAX, &frm_len, &frm_buffer[0]);
                    printf ("Port_No: %d, Capture Disabled - Dumping Capture Data -Frame Len: %d \n", port_no, frm_len);
                    for (idx=0; idx<=frm_len; idx++) {
                        printf ("frame_Buff[%d]:0x%x \n", idx, frm_buffer[idx]);
                    }
                } else {
                    printf ("Port_No: %d, Start Traffic to be Captured - Enable Loopbacks if required \n", port_no);
                }

                continue;

            } else if (strcmp(command, "macsec128Exp") == 0) {
                vtss_rc  rc;
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                vtss_port_no_t           macsec_physical_port = port_no;
                vtss_macsec_vport_id_t   macsec_virtual_port  = 0;
                vtss_macsec_service_id_t macsec_service_id    = 0;
                BOOL                     encrypt_256 = FALSE;
                BOOL                     confidentiality = TRUE;

                vtss_explicit_sci_t explicit_sci_rx = { .explicit_sci_flag = TRUE,
                                                        .explicit_sci.mac_addr = { .addr = {0x00, 0x00, 0x00, 0x00, 0x00, 0xAA}},
                                                        .explicit_sci.port_id  = 0x0001 };

                printf ("Port %d Config for Traffic - Explicit SCI: %x;  128bit Encryption\n", 
                   port_no, explicit_sci_rx.explicit_sci_flag);

                printf ("\nPort_No: %d, Enter Confidentiality (0=No Encrypt/1=Encrypt): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                confidentiality = atoi(value_str);

                if (confidentiality) {
                    printf ("\nPort %d Config for Traffic - Explicit SCI: %x;  128bit Encryption=ON; Confidentiality: %x\n", 
                          port_no, explicit_sci_rx.explicit_sci_flag, confidentiality);
                } else {
                    printf ("\nPort %d Config for Traffic - Explicit SCI: %x;  128bit Encryption=OFF; Confidentiality: %x\n", 
                          port_no, explicit_sci_rx.explicit_sci_flag, confidentiality);
                }


                vtss_single_secy_sample_system_create(board->inst,
                                                  port_no,
                                                 &macsec_port[port_no],
                                                 &port_macaddress[port_no],
                                                 &peer_sci[port_no],
                                                 &explicit_sci_rx,
                                                  encrypt_256,
                                                  confidentiality );

                if (encrypt_256) {
                    printf ("MACsec PHY Port %d Configured for MACSEC 256-bit Encryption, Static Key, Ingress & Egress \n", port_no);
                } else {
                    printf ("MACsec PHY Port %d Configured for MACSEC 128-bit Encryption, Static Key, Ingress & Egress \n", port_no);
                }
                if (!confidentiality) {
                    printf("Confidentiality=FALSE; Therefore SECTAG and ICV Added, but Packet NOT ENCRYPTED \n");
                }
                printf ("Port %d Ready for Traffic - Encrypt on data Egress;  Decrypt on data Ingress\n", port_no);
                printf ("Unencrypted Data IEEE_IPv4(etherType=0x0800),  Encrypted Data IEEE_802.1AE(etherType=0x88e5)\n");
                enable_macsec[port_no] = TRUE;
    // TODO, inject traffic here, and verify traffic and counters
                continue;

            } else if (strcmp(command, "macsec128Imp") == 0) {
                vtss_rc  rc;
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                vtss_port_no_t           macsec_physical_port = port_no;
                vtss_macsec_vport_id_t   macsec_virtual_port  = 0;
                vtss_macsec_service_id_t macsec_service_id    = 0;
                BOOL                     encrypt_256 = FALSE;
                BOOL                     confidentiality = TRUE;

                vtss_explicit_sci_t explicit_sci_rx = { .explicit_sci_flag = FALSE,
                                                        .explicit_sci.mac_addr = { .addr = {0x00, 0x00, 0x00, 0x00, 0x00, 0xAA}},
                                                        .explicit_sci.port_id  = 0x0001 };


                printf ("Port %d Config for Traffic - Explicit SCI: %x;  128bit Encryption\n",
                   port_no, explicit_sci_rx.explicit_sci_flag);

                printf ("\nPort_No: %d, Enter Confidentiality (0=No Encrypt/1=Encrypt): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                confidentiality = atoi(value_str);

                if (confidentiality) {
                    printf ("\nPort %d Config for Traffic - Explicit SCI: %x;  128bit Encryption=ON; Confidentiality: %x\n",
                          port_no, explicit_sci_rx.explicit_sci_flag, confidentiality);
                } else {
                    printf ("\nPort %d Config for Traffic - Explicit SCI: %x;  128bit Encryption=OFF; Confidentiality: %x\n",
                          port_no, explicit_sci_rx.explicit_sci_flag, confidentiality);
                }

                vtss_single_secy_sample_system_create(board->inst,
                                                  port_no,
                                                 &macsec_port[port_no],
                                                 &port_macaddress[port_no],
                                                 &peer_sci[port_no],
                                                 &explicit_sci_rx,
                                                  encrypt_256,
                                                  confidentiality );

                if (encrypt_256) {
                    printf ("MACsec PHY Port %d Configured for MACSEC 256-bit Encryption, Static Key, Ingress & Egress \n", port_no);
                } else {
                    printf ("MACsec PHY Port %d Configured for MACSEC 128-bit Encryption, Static Key, Ingress & Egress \n", port_no);
                }
                if (!confidentiality) {
                    printf("Confidentiality=FALSE; Therefore SECTAG and ICV Added, but Packet NOT ENCRYPTED \n");
                }
                printf ("Port %d Ready for Traffic - Encrypt on data Egress;  Decrypt on data Ingress\n", port_no);
                printf ("Unencrypted Data IEEE_IPv4(etherType=0x0800),  Encrypted Data IEEE_802.1AE(etherType=0x88e5)\n");
                enable_macsec[port_no] = TRUE;
    // TODO, inject traffic here, and verify traffic and counters
                continue;

            } else if (strcmp(command, "macsec256Exp") == 0) {
                vtss_rc  rc;
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                vtss_port_no_t           macsec_physical_port = port_no;
                vtss_macsec_vport_id_t   macsec_virtual_port  = 0;
                vtss_macsec_service_id_t macsec_service_id    = 0;
                BOOL                     encrypt_256 = TRUE;
                BOOL                     confidentiality = TRUE;

                vtss_explicit_sci_t explicit_sci_rx = { .explicit_sci_flag = TRUE,
                                                        .explicit_sci.mac_addr = { .addr = {0x00, 0x00, 0x00, 0x00, 0x00, 0xAA}},
                                                        .explicit_sci.port_id  = 0x0001 };


                printf ("Port %d Config for Traffic - Explicit SCI: %x;  256bit Encryption\n",
                   port_no, explicit_sci_rx.explicit_sci_flag);

                printf ("\nPort_No: %d, Enter Confidentiality (0=No Encrypt/1=Encrypt): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                confidentiality = atoi(value_str);

                if (confidentiality) {
                    printf ("\nPort %d Config for Traffic - Explicit SCI: %x;  256bit Encryption=ON; Confidentiality: %x\n",
                          port_no, explicit_sci_rx.explicit_sci_flag, confidentiality);
                } else {
                    printf ("\nPort %d Config for Traffic - Explicit SCI: %x;  256bit Encryption=OFF; Confidentiality: %x\n",
                          port_no, explicit_sci_rx.explicit_sci_flag, confidentiality);
                }

                vtss_single_secy_sample_system_create(board->inst,
                                                  port_no,
                                                 &macsec_port[port_no],
                                                 &port_macaddress[port_no],
                                                 &peer_sci[port_no],
                                                 &explicit_sci_rx,
                                                  encrypt_256,
                                                  confidentiality );

                if (encrypt_256) {
                    printf ("MACsec PHY Port %d Configured for MACSEC 256-bit Encryption, Static Key, Ingress & Egress \n", port_no);
                } else {
                    printf ("MACsec PHY Port %d Configured for MACSEC 128-bit Encryption, Static Key, Ingress & Egress \n", port_no);
                }

                if (!confidentiality) {
                    printf("Confidentiality=FALSE; Therefore SECTAG and ICV Added, but Packet NOT ENCRYPTED \n");
                }
                printf ("Port %d Ready for Traffic - Encrypt on data Egress;  Decrypt on data Ingress\n", port_no);
                printf ("Unencrypted Data IEEE_IPv4(etherType=0x0800),  Encrypted Data IEEE_802.1AE(etherType=0x88e5)\n");
                enable_macsec[port_no] = TRUE;
    // TODO, inject traffic here, and verify traffic and counters
                continue;

            } else if (strcmp(command, "macsec256Imp") == 0) {
                vtss_rc  rc;
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                vtss_port_no_t           macsec_physical_port = port_no;
                vtss_macsec_vport_id_t   macsec_virtual_port  = 0;
                vtss_macsec_service_id_t macsec_service_id    = 0;
                BOOL                     encrypt_256 = TRUE;
                BOOL                     confidentiality = TRUE;

                vtss_explicit_sci_t explicit_sci_rx = { .explicit_sci_flag = FALSE,
                                                        .explicit_sci.mac_addr = { .addr = {0x00, 0x00, 0x00, 0x00, 0x00, 0xAA}},
                                                        .explicit_sci.port_id  = 0x0001 };


                printf ("Port %d Config for Traffic - Explicit SCI: %x;  256bit Encryption\n",
                   port_no, explicit_sci_rx.explicit_sci_flag);

                printf ("\nPort_No: %d, Enter Confidentiality (0=No Encrypt/1=Encrypt): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                confidentiality = atoi(value_str);

                if (confidentiality) {
                    printf ("\nPort %d Config for Traffic - Explicit SCI: %x;  256bit Encryption=ON; Confidentiality: %x\n",
                          port_no, explicit_sci_rx.explicit_sci_flag, confidentiality);
                } else {
                    printf ("\nPort %d Config for Traffic - Explicit SCI: %x;  256bit Encryption=OFF; Confidentiality: %x\n",
                          port_no, explicit_sci_rx.explicit_sci_flag, confidentiality);
                }

                vtss_single_secy_sample_system_create(board->inst,
                                                  port_no,
                                                 &macsec_port[port_no],
                                                 &port_macaddress[port_no],
                                                 &peer_sci[port_no],
                                                 &explicit_sci_rx,
                                                  encrypt_256,
                                                  confidentiality );

                if (encrypt_256) {
                    printf ("MACsec PHY Port %d Configured for MACSEC 256-bit Encryption, Static Key, Ingress & Egress \n", port_no);
                } else {
                    printf ("MACsec PHY Port %d Configured for MACSEC 128-bit Encryption, Static Key, Ingress & Egress \n", port_no);
                }

                if (!confidentiality) {
                    printf("Confidentiality=FALSE; Therefore SECTAG and ICV Added, but Packet NOT ENCRYPTED \n");
                }
                printf ("Port %d Ready for Traffic - Encrypt on data Egress;  Decrypt on data Ingress\n", port_no);
                printf ("Unencrypted Data IEEE_IPv4(etherType=0x0800),  Encrypted Data IEEE_802.1AE(etherType=0x88e5)\n");
                enable_macsec[port_no] = TRUE;
    // TODO, inject traffic here, and verify traffic and counters
                continue;


            } else if (strcmp(command, "macsec_off") == 0) {
                vtss_rc  rc;
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                // Tear-Down MACSec setup
                vtss_single_secy_sample_system_destroy(board->inst,
                                                   &macsec_port[port_no],
                                                   &port_macaddress[port_no],
                                                   &peer_sci[port_no]);

                //printf ("Please Remove Power from Eval Board and Re-Initialize Board\n");
                enable_macsec[port_no] = FALSE; 
                continue;

           } else if (strcmp(command, "macsec_en_event") == 0) {
                vtss_rc  rc = 0;
                vtss_macsec_event_t   ev_mask;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }


                rc = vtss_macsec_event_enable_get(board->inst, port_no, &ev_mask);

                printf ("Getting MACSEC INT Event Mask: %x, rc = %d\n", ev_mask, rc);
                //ev_mask = VTSS_MACSEC_SEQ_NONE;
                //ev_mask = VTSS_MACSEC_SEQ_THRESHOLD_EVENT;
                //ev_mask = VTSS_MACSEC_SEQ_ROLLOVER_EVENT;
                ev_mask = VTSS_MACSEC_SEQ_ALL;

                rc = vtss_macsec_event_enable_set(board->inst, port_no, ev_mask, TRUE);

                printf ("Setting MACSEC INT Event Mask: %x, rc = %d\n", ev_mask, rc);
                continue;

           } else if (strcmp(command, "macsec_dis_event") == 0) {
                vtss_rc  rc = 0;
                vtss_macsec_event_t   ev_mask;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                rc = vtss_macsec_event_enable_get(board->inst, port_no, &ev_mask);
                printf ("Getting MACSEC INT Event Mask: %x, rc = %d\n", ev_mask, rc);
                // Disable specific Event or just disable everything that is enabled?
                //ev_mask = VTSS_MACSEC_SEQ_NONE;
                //ev_mask = VTSS_MACSEC_SEQ_THRESHOLD_EVENT;
                //ev_mask = VTSS_MACSEC_SEQ_ROLLOVER_EVENT;
                //ev_mask = VTSS_MACSEC_SEQ_ALL;

                rc = vtss_macsec_event_enable_set(board->inst, port_no, ev_mask, FALSE);

                printf ("Clearing MACSEC INT Event Mask: %x, \n", ev_mask);
                continue;

           } else if (strcmp(command, "macsec_poll_event") == 0) {
                vtss_rc  rc = 0;
                vtss_macsec_event_t   ev_mask;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                rc = vtss_macsec_event_enable_get(board->inst, port_no, &ev_mask);
                printf ("Getting MACSEC Enabled INT Events: %x, rc = %d\n", ev_mask, rc);

                ev_mask = 0;

                rc = vtss_macsec_event_poll(board->inst, port_no, &ev_mask);

                printf ("Polling MACSEC INT Event: 0x%x, rc = %d\n", ev_mask, rc);

                if (ev_mask == VTSS_MACSEC_SEQ_NONE) {
                    printf ("MACSEC INT Event: VTSS_MACSEC_SEQ_NONE \n");
                } else if (ev_mask == VTSS_MACSEC_SEQ_THRESHOLD_EVENT) {
                    printf ("MACSEC INT Event: VTSS_MACSEC_SEQ_THRESHOLD_EVENT \n");
                } else if (ev_mask == VTSS_MACSEC_SEQ_ROLLOVER_EVENT) {
                    printf ("MACSEC INT Event: VTSS_MACSEC_SEQ_ROLLOVER_EVENT \n");
                } else if (ev_mask == VTSS_MACSEC_SEQ_ALL) {
                    printf ("MACSEC INT Event: VTSS_MACSEC_SEQ_ALL \n");
                } else {
                    printf ("MACSEC INT Event: Unknown: 0x%x \n", ev_mask);
                }

                continue;

           } else if (strcmp(command, "macsec_get_thresh") == 0) {
                vtss_rc  rc = 0;
                u32      threshold = 0;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                rc = vtss_macsec_event_seq_threshold_get(board->inst, port_no, &threshold);

                printf ("Current MACSEC Seq Threshold for Port: %d    Thresh: %d;   rc = %d\n", port_no, threshold, rc);

                continue;

          } else if (strcmp(command, "macsec_set_thresh") == 0) {
                vtss_rc  rc = 0;
                u32      threshold = 0;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                rc = vtss_macsec_event_seq_threshold_get(board->inst, port_no, &threshold);
                printf ("Current MACSEC Seq Threshold for Port: %d    Thresh: %d;   rc = %d\n", port_no, threshold, rc);

                printf ("Please Enter the Desired MACSEC Seq Threshold for Port: %d:  ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                threshold = strtol(value_str, NULL, 10);

                rc = vtss_macsec_event_seq_threshold_set(board->inst, port_no, threshold);
                printf ("\nSetting MACSEC Seq Threshold for Port: %d    Thresh: %d;   rc = %d\n", port_no, threshold, rc);

                continue;

            } else if (strcmp(command, "ctrl_cnt") == 0) {
                vtss_rc  rc;
                vtss_macsec_secy_port_counters_t     cntrs;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                memset(&cntrs, 0, sizeof(vtss_macsec_secy_port_counters_t));

                rc = vtss_macsec_controlled_counters_get(board->inst, macsec_port[port_no], &cntrs);

                printf("\n PORT Sec_Y IN COUNTERS: Port_no: %d\n", port_no);
                printf(" if_in_octets: 0x%llx \n", (long long unsigned int) cntrs.if_in_octets);
                printf(" if_in_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_in_pkts);
                printf(" if_in_discards: 0x%llx \n", (long long unsigned int)cntrs.if_in_discards);
                printf(" if_in_errors: 0x%llx \n", (long long unsigned int)cntrs.if_in_errors);
                printf("\n PORT Sec_Y OUT COUNTERS: \n");
                printf(" if_out_octets: 0x%llx \n", (long long unsigned int)cntrs.if_out_octets);
                printf(" if_out_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_out_pkts);
                printf(" if_out_errors: 0x%llx \n", (long long unsigned int)cntrs.if_out_errors);
                printf(" if_out_ucast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_out_ucast_pkts);
                printf(" if_out_multicast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_out_multicast_pkts);
                printf(" if_out_broadcast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_out_broadcast_pkts);

                continue;

            } else if (strcmp(command, "unctrl_cnt") == 0) {
                vtss_rc  rc;
                vtss_macsec_uncontrolled_counters_t  cntrs;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                memset(&cntrs, 0, sizeof(vtss_macsec_secy_port_counters_t));

                rc = vtss_macsec_uncontrolled_counters_get(board->inst, port_no, &cntrs);

                printf("\n UNCONTROLLED IN-COUNTERS: Port_no: %d\n", port_no);
                printf(" if_in_octets: 0x%llx \n", (long long unsigned int)cntrs.if_in_octets);
                printf(" if_in_ucast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_in_ucast_pkts);
                printf(" if_in_multicast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_in_multicast_pkts);
                printf(" if_in_broadcast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_in_broadcast_pkts);
                printf(" if_in_discards: 0x%llx \n", (long long unsigned int)cntrs.if_in_discards);
                printf(" if_in_errors: 0x%llx \n", (long long unsigned int)cntrs.if_in_errors);
                printf("\n UNCONTROLLED OUT-COUNTERS: Port_no: %d\n", port_no);
                printf(" if_out_octets: 0x%llx \n", (long long unsigned int)cntrs.if_out_octets);
                printf(" if_out_ucast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_out_ucast_pkts);
                printf(" if_out_multicast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_out_multicast_pkts);
                printf(" if_out_broadcast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_out_broadcast_pkts);
                printf(" if_out_errors: 0x%llx \n", (long long unsigned int)cntrs.if_out_errors);

                continue;

            } else if (strcmp(command, "cmn_cnt") == 0) {
                vtss_rc  rc;
                vtss_macsec_common_counters_t        cntrs;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                memset(&cntrs, 0, sizeof(vtss_macsec_common_counters_t));

                rc = vtss_macsec_common_counters_get(board->inst, port_no, &cntrs);

                printf("\n COMMON IN-COUNTERS: Port_no: %d\n", port_no);
                printf(" if_in_octets: 0x%llx \n", (long long unsigned int)cntrs.if_in_octets);
                printf(" if_in_ucast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_in_ucast_pkts);
                printf(" if_in_multicast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_in_multicast_pkts);
                printf(" if_in_broadcast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_in_broadcast_pkts);
                printf(" if_in_discards: 0x%llx \n", (long long unsigned int)cntrs.if_in_discards);
                printf(" if_in_errors: 0x%llx \n", (long long unsigned int)cntrs.if_in_errors);
                printf("\n COMMON OUT-COUNTERS: Port_no: %d\n", port_no);
                printf(" if_out_octets: 0x%llx \n", (long long unsigned int)cntrs.if_out_octets);
                printf(" if_out_ucast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_out_ucast_pkts);
                printf(" if_out_multicast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_out_multicast_pkts);
                printf(" if_out_broadcast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_out_broadcast_pkts);
                printf(" if_out_errors: 0x%llx \n", (long long unsigned int)cntrs.if_out_errors);

                continue;

            } else if (strcmp(command, "hmac_count") == 0) {
                vtss_rc  rc;
                BOOL                           clear_cntrs = FALSE;
                vtss_macsec_mac_counters_t     cntrs;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                memset(&cntrs, 0, sizeof(vtss_macsec_mac_counters_t));

                rc = vtss_macsec_hmac_counters_get(board->inst, port_no, &cntrs, clear_cntrs);

                printf("\n HOST MAC RX COUNTERS: Port_no: %d\n", port_no);
                printf(" if_rx_octets: 0x%llx \n", (long long unsigned int)cntrs.if_rx_octets);
                printf(" if_rx_in_bytes: 0x%llx \n", (long long unsigned int)cntrs.if_rx_in_bytes);
                printf(" if_rx_ucast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_rx_ucast_pkts);
                printf(" if_rx_multicast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_rx_multicast_pkts);
                printf(" if_rx_broadcast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_rx_broadcast_pkts);
                printf(" if_rx_discards: 0x%llx \n", (long long unsigned int)cntrs.if_rx_discards);
                printf(" if_rx_CRCAlignErrors: 0x%llx \n", (long long unsigned int)cntrs.if_rx_CRCAlignErrors);
                printf(" if_rx_UndersizePkts: 0x%llx \n", (long long unsigned int)cntrs.if_rx_UndersizePkts);
                printf(" if_rx_Fragments: 0x%llx \n", (long long unsigned int)cntrs.if_rx_Fragments);
                printf(" if_rx_Jabbers: 0x%llx \n", (long long unsigned int)cntrs.if_rx_Jabbers);
                printf(" if_rx_errors: 0x%llx \n", (long long unsigned int)cntrs.if_rx_errors);
                printf("\n HOST MAC TX COUNTERS: \n");
                printf(" if_tx_octets: 0x%llx \n", (long long unsigned int)cntrs.if_tx_octets);
                printf(" if_tx_ucast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_tx_ucast_pkts);
                printf(" if_tx_multicast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_tx_multicast_pkts);
                printf(" if_tx_broadcast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_tx_broadcast_pkts);
                printf(" if_tx_errors: 0x%llx \n", (long long unsigned int)cntrs.if_tx_errors);

                continue;

            } else if (strcmp(command, "lmac_count") == 0) {
                vtss_rc  rc;
                BOOL                           clear_cntrs = FALSE;
                vtss_macsec_mac_counters_t     cntrs;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                memset(&cntrs, 0, sizeof(vtss_macsec_mac_counters_t));

                rc = vtss_macsec_lmac_counters_get(board->inst, port_no, &cntrs, clear_cntrs);

                printf("\n LINE MAC RX COUNTERS: Port_no: %d\n", port_no);
                printf(" if_rx_octets: 0x%llx \n", (long long unsigned int)cntrs.if_rx_octets);
                printf(" if_rx_in_bytes: 0x%llx \n", (long long unsigned int)cntrs.if_rx_in_bytes);
                printf(" if_rx_ucast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_rx_ucast_pkts);
                printf(" if_rx_multicast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_rx_multicast_pkts);
                printf(" if_rx_broadcast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_rx_broadcast_pkts);
                printf(" if_rx_discards: 0x%llx \n", (long long unsigned int)cntrs.if_rx_discards);
                printf(" if_rx_CRCAlignErrors: 0x%llx \n", (long long unsigned int)cntrs.if_rx_CRCAlignErrors);
                printf(" if_rx_UndersizePkts: 0x%llx \n", (long long unsigned int)cntrs.if_rx_UndersizePkts);
                printf(" if_rx_Fragments: 0x%llx \n", (long long unsigned int)cntrs.if_rx_Fragments);
                printf(" if_rx_Jabbers: 0x%llx \n", (long long unsigned int)cntrs.if_rx_Jabbers);
                printf(" if_rx_errors: 0x%llx \n", (long long unsigned int)cntrs.if_rx_errors);
                printf("\n LINE MAC TX COUNTERS: \n");
                printf(" if_tx_octets: 0x%llx \n", (long long unsigned int)cntrs.if_tx_octets);
                printf(" if_tx_ucast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_tx_ucast_pkts);
                printf(" if_tx_multicast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_tx_multicast_pkts);
                printf(" if_tx_broadcast_pkts: 0x%llx \n", (long long unsigned int)cntrs.if_tx_broadcast_pkts);
                printf(" if_tx_errors: 0x%llx \n", (long long unsigned int)cntrs.if_tx_errors);

                continue;

            } else if (strcmp(command, "dbg_count") == 0) {
                vtss_rc  rc;
                vtss_macsec_rc_dbg_counters_t  cntrs;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                memset(&cntrs, 0, sizeof(vtss_macsec_rc_dbg_counters_t));

                rc = vtss_macsec_dbg_counter_get(board->inst, port_no, &cntrs);

                printf("\n MACSEC DEBUG COUNTERS: Port_no: %d\n", port_no);
                printf(" invalid_sci_macaddr: %d \n", cntrs.invalid_sci_macaddr); /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_INVALID_SCI_MACADDR*/
                printf(" macsec_not_enabled: %d \n", cntrs.macsec_not_enabled);   /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_NOT_ENABLED*/
                printf(" secy_already_in_use: %d \n", cntrs.secy_already_in_use); /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_SECY_ALREADY_IN_USE*/
                printf(" no_secy_found: %d \n", cntrs.no_secy_found);           /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_NO_SECY_FOUND*/
                printf(" no_secy_vacancy: %d \n", cntrs.no_secy_vacency);         /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_NO_SECY_VACANCY*/
                printf(" invalid_validate_frm: %d \n", cntrs.invalid_validate_frm);    /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_INVALID_VALIDATE_FRM*/
                printf(" invalid_hdr_bypass_len: %d \n", cntrs.invalid_hdr_bypass_len);  /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_INVALID_BYPASS_HDR_LEN*/
                printf(" sc_not_found: %d \n", cntrs.sc_not_found);            /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_SC_NOT_FOUND*/
                printf(" could_not_prg_sa_match: %d \n", cntrs.could_not_prg_sa_match);  /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH*/
                printf(" could_not_prg_sa_flow: %d \n", cntrs.could_not_prg_sa_flow);   /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_SA_FLOW*/
                printf(" could_not_ena_sa: %d \n", cntrs.could_not_ena_sa);        /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_ENA_SA*/
                printf(" could_not_set_sa: %d \n", cntrs.could_not_set_sa);        /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_SET_SA*/
                printf(" no_ctrl_frm_match: %d \n", cntrs.no_ctrl_frm_match);       /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_NO_CTRL_FRM_MATCH*/
                printf(" could_not_set_pattern: %d \n", cntrs.could_not_set_pattern);   /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_SET_PATTERN*/
                printf(" timeout_issue: %d \n", cntrs.timeout_issue);           /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_TIMEOUT_ISSUE*/
                printf(" could_not_empty_egress: %d \n", cntrs.could_not_empty_egress);  /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_EMPTY_EGRESS*/
                printf(" an_not_created: %d \n", cntrs.an_not_created);          /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_AN_NOT_CREATED*/
                printf(" counld_not_empty_ingress: %d \n", cntrs.could_not_empty_ingress); /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_EMPTY_INGRESS*/
                printf(" tx_sc_not_exist: %d \n", cntrs.tx_sc_not_exist);         /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_TX_SC_NOT_EXIST*/
                printf(" could_not_disable_sa: %d \n", cntrs.could_not_disable_sa);    /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA*/
                printf(" could_not_del_rx_sa: %d \n", cntrs.could_not_del_rx_sa);     /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_DEL_RX_SA*/
                printf(" could_not_del_tx_sa: %d \n", cntrs.could_not_del_tx_sa);     /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_DEL_TX_SA*/
                printf(" pattern_not_set: %d \n", cntrs.pattern_not_set);         /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_PATTERN_NOT_SET*/
                printf(" hw_resource_exhausted: %d \n", cntrs.hw_resource_exhusted);    /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_HW_RESOURCE_EXHUSTED*/
                printf(" sci_already_exists: %d \n", cntrs.sci_already_exist);       /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_SCI_ALREADY_EXISTS*/
                printf(" sc_resource_not_found: %d \n", cntrs.sc_resource_not_found);   /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_SC_RESOURCE_NOT_FOUND*/
                printf(" rx_an_already_in_use: %d \n", cntrs.rx_an_already_in_use);    /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_RX_AN_ALREADY_IN_USE*/
                printf(" empty_record: %d \n", cntrs.empty_record);            /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_EMPTY_RECORD*/
                printf(" could_not_prg_xform: %d \n", cntrs.could_not_prg_xform);     /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_PRG_XFORM*/
                printf(" could_not_toggle_sa: %d \n", cntrs.could_not_toggle_sa);     /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_TOGGLE_SA*/
                printf(" tx_an_already_in_use: %d \n", cntrs.tx_an_already_in_use);    /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_TX_AN_ALREADY_IN_USE*/
                printf(" all_avail_sa_in_use: %d \n", cntrs.all_available_sa_in_use); /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_ALL_AVAILABLE_SA_IN_USE*/
                printf(" match_disable: %d \n", cntrs.match_disable);           /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_MATCH_DISABLE*/
                printf(" all_cp_rules_in_use: %d \n", cntrs.all_cp_rules_in_use);     /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_ALL_CP_RULES_IN_USE*/
                printf(" pattern_prio_not_valid: %d \n", cntrs.pattern_prio_not_valid);  /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_PATTERN_PRIO_NOT_VALID*/
                printf(" buffer_too_small: %d \n", cntrs.buffer_too_small);        /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_BUFFER_TOO_SMALL*/
                printf(" frm_too_long: %d \n", cntrs.frm_too_long);            /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_FRAME_TOO_LONG*/
                printf(" frm_truncated: %d \n", cntrs.frm_truncated);           /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_FRAME_TRUNCATED*/
                printf(" phy_powered_down: %d \n", cntrs.phy_powered_down);        /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_PHY_POWERED_DOWN*/
                printf(" phy_not_macsec_capable: %d \n", cntrs.phy_not_macsec_capable);  /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_PHY_NOT_MACSEC_CAPABLE*/
                printf(" an_not_exist: %d \n", cntrs.an_not_exist);            /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_AN_NOT_EXIST*/
                printf(" no_pattern_cfg: %d \n", cntrs.no_pattern_cfg);          /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_NO_PATTERN_CFG*/
                printf(" unexpected_speed: %d \n", cntrs.unexpected_speed);        /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_UNEXPECT_SPEED*/
                printf(" max_mtu: %d \n", cntrs.max_mtu);                 /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_MAX_MTU*/
                printf(" unexpected_cp_mode: %d \n", cntrs.unexpected_cp_mode);      /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_UNEXPECT_CP_MODE*/
                printf(" could_not_disable_an: %d \n", cntrs.could_not_disable_an);    /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_COULD_NOT_DISABLE_AN*/
                printf(" rule_out_of_range: %d \n", cntrs.rule_out_of_range);       /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_RULE_OUT_OF_RANGE*/
                printf(" rule_not_exist: %d \n", cntrs.rule_not_exit);           /**< Number of errors happen with error code VTSS_RC_ERR_MACSEC_RULE_NOT_EXIT*/
                printf(" csr_read: %d \n", cntrs.csr_read);                /**< Number of errors happen with error code VTSS_RC_ERR_CSR_READ*/
                printf(" csr_write: %d \n", cntrs.csr_write);               /**< Number of errors happen with error code VTSS_RC_ERR_CSR_WRITE*/
                printf(" unknown_rc_code: %d \n", cntrs.unknown_rc_code);         /**< Number of errors happen with unknown error code*/

                continue;

            } else if (strcmp(command, "dbg_reg_dump") == 0) {
                vtss_rc  rc;
                vtss_macsec_secy_port_counters_t     cntrs;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                rc = vtss_macsec_dbg_reg_dump(board->inst, port_no, printf);

                continue;

            } else if (strcmp(command, "fcb_dump") == 0) {
                vtss_rc  rc;
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                rc = vtss_macsec_dbg_fcb_block_reg_dump(board->inst, port_no, printf);

                continue;

            } else if (strcmp(command, "frm_ctl_dump") == 0) {
                vtss_rc  rc;
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                rc = vtss_macsec_dbg_frm_match_handling_ctrl_reg_dump(board->inst, port_no, printf);

                continue;

#ifdef KAT_TEST_ENABLE_1G
            } else if (strcmp(command, "kat_test") == 0) {
                vtss_rc  rc;
                vtss_macsec_frame_capture_t  capture = VTSS_MACSEC_FRAME_CAPTURE_DISABLE;
                BOOL egr_fail = FALSE;
                BOOL ing_fail = FALSE;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                rc = vtss_phy_macsec_kat_test(board->inst, port_no, &egr_fail, &ing_fail);
                printf("Rtn Code for KAT Test: %d  Egress Results: %x,  Ingress_Results: %x\n", rc, egr_fail, ing_fail);
                if (egr_fail) {
                    printf("EGRESS_KAT_Results: FAIL:  %x\n", egr_fail);
                } else {
                    printf("EGRESS_KAT_Results: PASS:  %x\n", egr_fail);
                }
                if (ing_fail) {
                    printf("INGRESS_KAT_Results: FAIL:  %x\n", ing_fail);
                } else {
                    printf("INGRESS_KAT_Results: PASS:  %x\n", ing_fail);
                }
                continue;
#endif
            } else {
                continue;
            }

          }
          continue;  // Go back to top of Loop

#endif  // End of MACSEC

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

